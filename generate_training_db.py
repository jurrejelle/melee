#!/usr/bin/env python3
"""
Generate a SQLite3 database of 100% matching decompiled functions for LLM training.

For every 100% matching function in the Melee decomp, stores:
  - target_asm: The original PowerPC assembly from the .s file
  - m2c_output: The initial m2c decompilation (with type context if possible)
  - m2c_output_no_ctx: The m2c decompilation without context (always available)
  - matching_c_code: The final human-written matching C code
  - context: Relevant headers, structs, inlines, types used by the function
  - git_authors: JSON list of everyone who ever touched the function
  - git_first_author: Who originally decompiled/added the function
  - git_commit_history: Full commit history with hashes, dates, messages
  - unit_name, function_name, source_path, compiler_flags, function_size, etc.

The script is resumable: it tracks which functions have been processed and
can be interrupted and restarted at any point. Progress is saved after each
unit. The m2c step is the slowest part (~150 min total), git history adds
~5 min via parallel `git log -L` calls.

Usage:
    python3 generate_training_db.py [--db PATH] [--skip-m2c] [--unit UNIT]
                                     [--rebuild-ctx] [--report PATH] [--stats]

    --db PATH       SQLite database path (default: melee_training.db)
    --skip-m2c      Skip m2c decompilation step (fill in later)
    --unit UNIT     Process only this unit (for testing)
    --rebuild-ctx   Force rebuild of ctx files
    --report PATH   Use pre-generated objdiff report JSON
    --stats         Print database statistics and exit
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import sqlite3
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
from typing import Any

# ── Project paths ─────────────────────────────────────────────────────────────

PROJECT_ROOT = Path(__file__).resolve().parent
OBJDIFF_CLI = Path("/bin/objdiff")
M2C_BIN = Path("/home/ubuntu/Desktop/Melee/.venv/bin/m2c")
ASM_DIR = PROJECT_ROOT / "build" / "GALE01" / "asm"
SRC_DIR = PROJECT_ROOT / "src"
BUILD_DIR = PROJECT_ROOT / "build" / "GALE01"

DEFAULT_DB = PROJECT_ROOT / "melee_training.db"


# ── Database setup ────────────────────────────────────────────────────────────

SCHEMA = """
CREATE TABLE IF NOT EXISTS functions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    -- Identity
    unit_name TEXT NOT NULL,
    function_name TEXT NOT NULL,
    source_path TEXT,
    function_address TEXT,
    function_size INTEGER,

    -- Compiler info
    compiler_flags TEXT,

    -- Core training data
    target_asm TEXT,              -- Original PPC assembly
    m2c_output TEXT,              -- m2c decompilation WITH context (best effort)
    m2c_output_no_ctx TEXT,       -- m2c decompilation WITHOUT context (always available)
    matching_c_code TEXT,         -- Final human-written matching C

    -- Context for understanding the code
    context_includes TEXT,        -- #include lines from .c file
    context_header TEXT,          -- The main .h header for this unit
    context_inlines TEXT,         -- Inline function definitions used
    context_structs TEXT,         -- Relevant struct/type definitions (from ctx)
    context_function_signatures TEXT,  -- Other function signatures in the unit

    -- Git authorship
    git_authors TEXT,             -- JSON list of all authors who touched this function
    git_first_author TEXT,        -- Original author who first added the function
    git_commit_history TEXT,      -- JSON list of {hash, author, date, message} per commit

    -- Metadata
    processed_at TEXT,
    m2c_processed INTEGER DEFAULT 0,   -- 1 = m2c ran successfully
    git_processed INTEGER DEFAULT 0,   -- 1 = git history extracted
    source_hash TEXT,                   -- Hash of source file for change detection

    UNIQUE(unit_name, function_name)
);

CREATE INDEX IF NOT EXISTS idx_unit ON functions(unit_name);
CREATE INDEX IF NOT EXISTS idx_func ON functions(function_name);
CREATE INDEX IF NOT EXISTS idx_m2c ON functions(m2c_processed);

CREATE TABLE IF NOT EXISTS units_progress (
    unit_name TEXT PRIMARY KEY,
    total_functions INTEGER,
    processed_functions INTEGER DEFAULT 0,
    ctx_built INTEGER DEFAULT 0,
    last_updated TEXT
);

CREATE TABLE IF NOT EXISTS metadata (
    key TEXT PRIMARY KEY,
    value TEXT
);
"""


def init_db(db_path: Path) -> sqlite3.Connection:
    conn = sqlite3.connect(str(db_path))
    conn.execute("PRAGMA journal_mode=WAL")
    conn.execute("PRAGMA synchronous=NORMAL")
    conn.executescript(SCHEMA)

    # Add columns if upgrading from older schema
    existing = {row[1] for row in conn.execute("PRAGMA table_info(functions)")}
    migrations = {
        'm2c_output_no_ctx': 'ALTER TABLE functions ADD COLUMN m2c_output_no_ctx TEXT',
        'git_authors': 'ALTER TABLE functions ADD COLUMN git_authors TEXT',
        'git_first_author': 'ALTER TABLE functions ADD COLUMN git_first_author TEXT',
        'git_commit_history': 'ALTER TABLE functions ADD COLUMN git_commit_history TEXT',
        'git_processed': 'ALTER TABLE functions ADD COLUMN git_processed INTEGER DEFAULT 0',
    }
    for col, sql in migrations.items():
        if col not in existing:
            conn.execute(sql)

    conn.commit()
    return conn


# ── objdiff report ────────────────────────────────────────────────────────────

def generate_report(report_path: Path | None = None) -> dict:
    """Generate or load the objdiff report with all function match percentages."""
    if report_path and report_path.exists():
        print(f"Loading existing report from {report_path}")
        with open(report_path) as f:
            return json.load(f)

    cache_path = PROJECT_ROOT / ".training_report_cache.json"

    if cache_path.exists():
        age = time.time() - cache_path.stat().st_mtime
        if age < 3600:
            print(f"Using cached report ({age:.0f}s old)")
            with open(cache_path) as f:
                return json.load(f)

    print("Generating objdiff report (this takes ~2s)...")
    result = subprocess.run(
        [str(OBJDIFF_CLI), "report", "generate",
         "-p", str(PROJECT_ROOT), "-f", "json", "-o", "-"],
        capture_output=True, text=True
    )
    if result.returncode != 0:
        print(f"Error generating report: {result.stderr}", file=sys.stderr)
        sys.exit(1)

    report = json.loads(result.stdout)

    with open(cache_path, 'w') as f:
        json.dump(report, f)

    return report


def load_objdiff_config() -> dict:
    """Load objdiff.json for unit metadata."""
    with open(PROJECT_ROOT / "objdiff.json") as f:
        return json.load(f)


# ── ASM extraction ────────────────────────────────────────────────────────────

def extract_all_functions_asm(asm_path: Path) -> dict[str, str]:
    """Extract all function assemblies from an asm file. Returns {name: asm}."""
    if not asm_path.exists():
        return {}

    with open(asm_path) as f:
        lines = f.readlines()

    functions = {}
    current_fn = None
    current_lines: list[str] = []

    for line in lines:
        stripped = line.strip()
        m = re.match(r"\.fn\s+(\S+?)(?:,|\s|$)", stripped)
        if m:
            current_fn = m.group(1)
            current_lines = [line]
            continue

        if current_fn:
            current_lines.append(line)
            m = re.match(r"\.endfn\s+" + re.escape(current_fn) + r"\b", stripped)
            if m:
                functions[current_fn] = "".join(current_lines)
                current_fn = None
                current_lines = []

    return functions


# ── C source extraction ───────────────────────────────────────────────────────

def extract_function_c_source(source_path: Path, func_name: str) -> str | None:
    """Extract a function's C source from a .c file using brace counting."""
    if not source_path or not source_path.exists():
        return None

    with open(source_path, errors='replace') as f:
        content = f.read()

    lines = content.split('\n')

    # Find the line containing the function definition
    # Handle both `func(` and `(func)(` patterns (the latter is for
    # functions like `(strlen)` that avoid macro expansion)
    func_start = None
    for i, line in enumerate(lines):
        has_normal = func_name + '(' in line
        has_paren = '(' + func_name + ')(' in line
        if not has_normal and not has_paren:
            continue

        stripped = line.strip()
        # Skip comments
        if stripped.startswith('//') or stripped.startswith('/*'):
            continue
        # Skip declarations (end with ;)
        if stripped.endswith(';'):
            continue
        # Check word boundary
        if has_paren:
            idx = line.index('(' + func_name + ')(')
        else:
            idx = line.index(func_name + '(')
            if idx > 0 and (line[idx - 1].isalnum() or line[idx - 1] == '_'):
                continue

        # Check if this looks like a function definition (has return type before)
        prefix = line[:idx].strip()
        if prefix and not prefix.endswith(',') and not prefix.endswith('{'):
            func_start = i
            break
        elif not prefix:
            # Could be a continuation from previous line
            if i > 0 and lines[i - 1].strip() and not lines[i - 1].strip().endswith(';'):
                func_start = i - 1
                break

    if func_start is None:
        return None

    # Capture preceding comments
    comment_start = func_start
    for j in range(func_start - 1, -1, -1):
        stripped = lines[j].strip()
        if stripped.startswith('///') or stripped.startswith('*') or \
           stripped.startswith('/*') or stripped.startswith('*/'):
            comment_start = j
        elif stripped == '':
            if j > 0 and (lines[j - 1].strip().startswith('///') or
                          lines[j - 1].strip().startswith('*/')):
                comment_start = j
            else:
                break
        else:
            break

    # Find the function body end by counting braces
    brace_count = 0
    found_open = False
    func_end = None

    for i in range(func_start, len(lines)):
        for ch in lines[i]:
            if ch == '{':
                brace_count += 1
                found_open = True
            elif ch == '}':
                brace_count -= 1
                if found_open and brace_count == 0:
                    func_end = i
                    break
        if func_end is not None:
            break

    if func_end is None:
        return None

    return '\n'.join(lines[comment_start:func_end + 1])


def extract_all_functions_c_source(source_path: Path,
                                    func_names: list[str]) -> dict[str, str]:
    """Extract multiple function bodies from a C source file."""
    result = {}
    for name in func_names:
        code = extract_function_c_source(source_path, name)
        if code:
            result[name] = code
    return result


# ── Context extraction ────────────────────────────────────────────────────────

def extract_includes(source_path: Path) -> str:
    """Extract all #include lines from a source file."""
    if not source_path or not source_path.exists():
        return ""
    includes = []
    with open(source_path, errors='replace') as f:
        for line in f:
            stripped = line.strip()
            if stripped.startswith('#include'):
                includes.append(stripped)
    return '\n'.join(includes)


def find_header_for_source(source_path: Path) -> Path | None:
    """Find the corresponding .h file for a .c file."""
    if not source_path:
        return None
    h_path = source_path.with_suffix('.h')
    if h_path.exists():
        return h_path
    return None


def read_header(header_path: Path | None) -> str:
    """Read a header file's content."""
    if header_path is None or not header_path.exists():
        return ""
    with open(header_path, errors='replace') as f:
        return f.read()


def extract_inlines(source_path: Path) -> str:
    """Find and read inline header files included by the source."""
    if not source_path or not source_path.exists():
        return ""

    inlines = []
    src_dir = source_path.parent

    with open(source_path, errors='replace') as f:
        for line in f:
            stripped = line.strip()
            if stripped.startswith('#include') and 'inline' in stripped.lower():
                m = re.search(r'"([^"]+)"', stripped)
                if m:
                    inc_path = m.group(1)
                    for base in [src_dir, SRC_DIR / "melee", SRC_DIR]:
                        full_path = base / inc_path
                        if full_path.exists():
                            with open(full_path, errors='replace') as hf:
                                inlines.append(
                                    f"// === {inc_path} ===\n{hf.read()}")
                            break

    return '\n\n'.join(inlines)


def extract_structs_from_ctx(ctx_path: Path, func_source: str) -> str:
    """Extract relevant struct/type definitions from the ctx file."""
    if not ctx_path or not ctx_path.exists() or not func_source:
        return ""

    with open(ctx_path, errors='replace') as f:
        ctx_content = f.read()

    # Find type names used in the function source
    type_refs = set()
    for m in re.finditer(r'\b([A-Z][A-Za-z0-9_]+)\b', func_source):
        type_refs.add(m.group(1))
    for m in re.finditer(r'\b([su](?:8|16|32|64))\b', func_source):
        type_refs.add(m.group(1))

    if not type_refs:
        return ""

    # Extract struct/union/enum/typedef definitions from ctx
    structs = []
    lines = ctx_content.split('\n')
    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()

        m = re.match(r'\s*(typedef\s+)?(struct|union|enum)\s+(\w+)', stripped)
        if m:
            type_name = m.group(3)
            if type_name in type_refs:
                brace_count = 0
                def_lines = []
                j = i
                found_open = False
                while j < len(lines):
                    def_lines.append(lines[j])
                    for ch in lines[j]:
                        if ch == '{':
                            brace_count += 1
                            found_open = True
                        elif ch == '}':
                            brace_count -= 1
                    if found_open and brace_count <= 0:
                        break
                    if not found_open and lines[j].rstrip().endswith(';'):
                        break
                    j += 1
                structs.append('\n'.join(def_lines))
        elif stripped.startswith('typedef') and \
                any(t in stripped for t in type_refs):
            if '{' not in stripped:
                structs.append(stripped)

        i += 1

    # Deduplicate
    seen = set()
    unique = []
    for s in structs:
        h = hashlib.md5(s.encode()).hexdigest()
        if h not in seen:
            seen.add(h)
            unique.append(s)

    return '\n\n'.join(unique)


def extract_function_signatures(source_path: Path) -> str:
    """Extract function signatures from the corresponding header file."""
    if not source_path:
        return ""
    header = find_header_for_source(source_path)
    if header is None:
        return ""

    sigs = []
    with open(header, errors='replace') as f:
        for line in f:
            stripped = line.strip()
            if '(' in stripped and stripped.endswith(';') and \
               not stripped.startswith('#') and \
               not stripped.startswith('//') and \
               not stripped.startswith('/*'):
                sigs.append(stripped)

    return '\n'.join(sigs)


# ── ctx file cleaning ─────────────────────────────────────────────────────────

def clean_ctx_for_m2c(ctx_path: Path) -> Path | None:
    """Create a cleaned version of a ctx file that m2c can parse.

    Strips preprocessor directives, macro invocations, extern "C" blocks,
    inline function bodies, and attribute annotations.
    Returns path to a temp file, or None on failure.
    """
    if not ctx_path or not ctx_path.exists():
        return None

    with open(ctx_path, errors='replace') as f:
        content = f.read()

    lines = content.split('\n')
    cleaned = []
    in_macro = False
    extern_c_depth = 0
    in_func_body = False
    brace_depth = 0

    for line in lines:
        stripped = line.rstrip()
        s = stripped.lstrip()

        # Multi-line macro continuation
        if in_macro:
            in_macro = stripped.endswith('\\')
            continue

        # Preprocessor directives
        if s.startswith('#'):
            in_macro = stripped.endswith('\\')
            continue

        # File reference comments
        if re.match(r'/\*\s*"', s):
            continue
        if re.match(r'/\*\s*end\s', s):
            continue

        # extern "C"
        if 'extern "C"' in s:
            if '{' in s:
                extern_c_depth += 1
            continue

        # Track inline/static function bodies - skip them
        if in_func_body:
            for ch in s:
                if ch == '{':
                    brace_depth += 1
                elif ch == '}':
                    brace_depth -= 1
            if brace_depth <= 0:
                in_func_body = False
                brace_depth = 0
            continue

        # Detect function body starts (inline or otherwise in context)
        if '{' in s and '(' in s and not s.startswith('typedef') and \
           not s.startswith('struct') and not s.startswith('union') and \
           not s.startswith('enum') and '=' not in s.split('{')[0]:
            # Likely a function definition with opening brace
            brace_depth = s.count('{') - s.count('}')
            if brace_depth > 0:
                in_func_body = True
                continue
            elif brace_depth == 0:
                continue

        # Standalone opening brace after function signature
        if s == '{' and cleaned:
            prev = ''
            for cl in reversed(cleaned):
                if cl.strip():
                    prev = cl.strip()
                    break
            if prev and '(' in prev and ')' in prev and \
               not prev.endswith(';') and not prev.endswith(','):
                brace_depth = 1
                in_func_body = True
                # Convert definition to declaration
                while cleaned and cleaned[-1].strip() == '':
                    cleaned.pop()
                if cleaned and not cleaned[-1].rstrip().endswith(';'):
                    cleaned[-1] = cleaned[-1].rstrip() + ';'
                continue

        # Strip attribute macros
        s_clean = s
        for attr in ['ATTRIBUTE_NORETURN', 'DOLPHIN_ATTRIBUTE_NORETURN',
                      'ATTRIBUTE_ALIGN', 'ASM', 'WEAKFUNC', 'INIT']:
            s_clean = re.sub(r'\b' + attr + r'\b', '', s_clean)
        s_clean = re.sub(r'__attribute__\s*\(\([^)]*\)\)', '', s_clean)
        s_clean = s_clean.strip()

        # Skip macro invocations: ALL_CAPS_OR_DIGITS(...)
        if re.match(r'^[A-Z_0-9]{2,}\s*\(', s_clean):
            first_word = re.match(r'^([A-Z_0-9]+)', s_clean).group(1)
            if first_word not in ('BOOL',):
                continue

        # Handle extern "C" closing braces
        if extern_c_depth > 0 and s_clean == '}':
            extern_c_depth -= 1
            continue

        cleaned.append(s_clean if s_clean else '')

    # Write to temp file
    try:
        fd, tmp_path = tempfile.mkstemp(suffix='.ctx', prefix='m2c_clean_')
        with os.fdopen(fd, 'w') as f:
            f.write('\n'.join(cleaned))
        return Path(tmp_path)
    except Exception:
        return None


# ── m2c decompilation ─────────────────────────────────────────────────────────

def build_ctx_file(unit_config: dict) -> Path | None:
    """Build the ctx file for a unit using ninja."""
    ctx_path_str = unit_config.get('scratch', {}).get('ctx_path', '')
    if not ctx_path_str:
        return None

    ctx_path = PROJECT_ROOT / ctx_path_str
    if ctx_path.exists():
        return ctx_path

    result = subprocess.run(
        ["ninja", "-j1", ctx_path_str],
        cwd=PROJECT_ROOT, capture_output=True, text=True, timeout=120
    )
    if result.returncode != 0:
        return None

    return ctx_path if ctx_path.exists() else None


def run_m2c(asm_path: Path, func_name: str,
            ctx_path: Path | None = None) -> str | None:
    """Run m2c on a specific function. Returns decompiled C or error string."""
    if not asm_path.exists():
        return None

    cmd = [str(M2C_BIN), "-t", "ppc-mwcc-c", "-f", func_name]

    if ctx_path and ctx_path.exists():
        cmd.extend(["--context", str(ctx_path)])

    cmd.append(str(asm_path))

    try:
        result = subprocess.run(
            cmd, capture_output=True, text=True, timeout=60
        )
        if result.returncode != 0:
            err = result.stderr.strip()[:500] if result.stderr else \
                  result.stdout.strip()[:500]
            return None  # Return None so caller knows it failed
        return result.stdout
    except subprocess.TimeoutExpired:
        return None
    except Exception:
        return None


def run_m2c_with_fallback(asm_path: Path, func_name: str,
                           cleaned_ctx: Path | None) -> tuple[str | None, str | None]:
    """Run m2c with context, falling back to without.

    Returns (m2c_with_ctx, m2c_without_ctx).
    """
    m2c_ctx = None
    m2c_no_ctx = None

    # Always try without context (reliable)
    m2c_no_ctx = run_m2c(asm_path, func_name, ctx_path=None)

    # Try with context if available
    if cleaned_ctx and cleaned_ctx.exists():
        m2c_ctx = run_m2c(asm_path, func_name, ctx_path=cleaned_ctx)

    return m2c_ctx, m2c_no_ctx


# ── Git authorship ────────────────────────────────────────────────────────────

def get_function_git_history(func_name: str,
                              source_path: str) -> dict | None:
    """Get git history for a function using `git log -L:func:file`.

    Returns dict with:
      authors: sorted list of unique "Name <email>" strings
      first_author: the author of the earliest commit (who first added it)
      commits: list of {hash, author, date, message} in reverse chronological order
    Or None on failure.
    """
    try:
        proc = subprocess.run(
            ["git", "log",
             "--format=COMMIT_LINE:%H|%an <%ae>|%aI|%s",
             f"-L:{func_name}:{source_path}"],
            capture_output=True, text=True,
            cwd=str(PROJECT_ROOT), timeout=30
        )
        if proc.returncode != 0:
            return None
    except (subprocess.TimeoutExpired, Exception):
        return None

    commits = []
    for line in proc.stdout.split('\n'):
        if line.startswith('COMMIT_LINE:'):
            parts = line[len('COMMIT_LINE:'):].split('|', 3)
            if len(parts) == 4:
                commits.append({
                    'hash': parts[0],
                    'author': parts[1],
                    'date': parts[2],
                    'message': parts[3],
                })

    if not commits:
        return None

    authors = sorted(set(c['author'] for c in commits))
    first_author = commits[-1]['author']  # Last in log = earliest commit

    return {
        'authors': authors,
        'first_author': first_author,
        'commits': commits,
    }


def batch_git_history(func_source_pairs: list[tuple[str, str]],
                       max_workers: int = 8) -> dict[str, dict | None]:
    """Run git log -L in parallel for many functions.

    Args:
        func_source_pairs: list of (function_name, source_path)
        max_workers: thread pool size

    Returns: {function_name: git_history_dict_or_None}
    """
    results: dict[str, dict | None] = {}

    def _worker(pair):
        fn, src = pair
        return fn, get_function_git_history(fn, src)

    with ThreadPoolExecutor(max_workers=max_workers) as pool:
        futures = {pool.submit(_worker, p): p[0] for p in func_source_pairs}
        for future in as_completed(futures):
            fn, hist = future.result()
            results[fn] = hist

    return results


# ── Main processing ──────────────────────────────────────────────────────────

def get_matching_functions(report: dict) -> list[dict]:
    """Get all 100% matching functions with their unit info."""
    results = []
    for unit in report.get('units', []):
        unit_name = unit.get('name', '')
        for fn in unit.get('functions', []):
            if fn.get('fuzzy_match_percent', 0) == 100.0:
                results.append({
                    'unit_name': unit_name,
                    'function_name': fn['name'],
                    'function_size': int(fn.get('size', 0)),
                    'function_address': fn.get('metadata', {}).get(
                        'virtual_address', ''),
                })
    return results


def get_unit_config(objdiff_config: dict, unit_name: str) -> dict | None:
    """Get the unit configuration from objdiff.json."""
    for unit in objdiff_config.get('units', []):
        if unit['name'] == unit_name:
            return unit
    return None


def is_already_processed(conn: sqlite3.Connection, unit_name: str,
                          func_name: str,
                          source_hash: str | None = None) -> bool:
    """Check if a function has already been fully processed."""
    row = conn.execute(
        "SELECT source_hash, m2c_processed, git_processed FROM functions "
        "WHERE unit_name = ? AND function_name = ?",
        (unit_name, func_name)
    ).fetchone()
    if row is None:
        return False
    if source_hash and row[0] != source_hash:
        return False
    if row[1] != 1:
        return False
    if row[2] != 1:
        return False
    return True


def file_hash(path: Path) -> str:
    """Get MD5 hash of a file for change detection."""
    if not path or not path.exists():
        return ""
    h = hashlib.md5()
    with open(path, 'rb') as f:
        for chunk in iter(lambda: f.read(8192), b''):
            h.update(chunk)
    return h.hexdigest()


def process_unit(conn: sqlite3.Connection, unit_name: str,
                 functions: list[dict], objdiff_config: dict,
                 skip_m2c: bool = False,
                 rebuild_ctx: bool = False) -> tuple[int, int]:
    """Process all matching functions in a unit.

    Returns (processed_count, skipped_count).
    """
    unit_config = get_unit_config(objdiff_config, unit_name)
    if unit_config is None:
        return 0, len(functions)

    source_path_str = unit_config.get('metadata', {}).get('source_path', '')
    source_path = (PROJECT_ROOT / source_path_str) if source_path_str else None
    if source_path and not source_path.exists():
        source_path = None

    src_hash = file_hash(source_path) if source_path else ""

    # Filter to functions that need work
    to_process = []
    for fn in functions:
        if not is_already_processed(conn, unit_name, fn['function_name'],
                                     src_hash):
            to_process.append(fn)

    if not to_process:
        return 0, len(functions)

    # ASM file
    parts = unit_name.split("/")
    asm_path = ASM_DIR / ("/".join(parts[1:]) + ".s")
    if not asm_path.exists():
        return 0, len(functions)

    # Extract all function ASMs at once
    all_asm = extract_all_functions_asm(asm_path)

    # Context extraction (once per unit)
    includes = extract_includes(source_path)
    header = read_header(find_header_for_source(source_path))
    inlines = extract_inlines(source_path)
    func_sigs = extract_function_signatures(source_path)
    compiler_flags = unit_config.get('scratch', {}).get('c_flags', '')

    # Build and clean ctx for m2c
    cleaned_ctx = None
    ctx_path = None
    if not skip_m2c:
        ctx_path_str = unit_config.get('scratch', {}).get('ctx_path', '')
        if ctx_path_str:
            ctx_path = PROJECT_ROOT / ctx_path_str
            if not ctx_path.exists() or rebuild_ctx:
                try:
                    ctx_path = build_ctx_file(unit_config)
                except Exception:
                    ctx_path = None

            if ctx_path and ctx_path.exists():
                cleaned_ctx = clean_ctx_for_m2c(ctx_path)

    # Extract C source for all needed functions
    func_names = [fn['function_name'] for fn in to_process]
    c_sources = extract_all_functions_c_source(
        source_path, func_names) if source_path else {}

    # Git history (batched per unit for parallelism)
    git_data: dict[str, dict | None] = {}
    if source_path_str:
        git_pairs = [(fn['function_name'], source_path_str)
                      for fn in to_process]
        git_data = batch_git_history(git_pairs, max_workers=8)

    count = 0
    now = time.strftime('%Y-%m-%d %H:%M:%S')

    for fn in to_process:
        fn_name = fn['function_name']
        target_asm = all_asm.get(fn_name, '')
        matching_c = c_sources.get(fn_name, '')

        if not target_asm:
            continue

        # Struct context
        structs = ""
        if ctx_path and ctx_path.exists() and matching_c:
            try:
                structs = extract_structs_from_ctx(ctx_path, matching_c)
            except Exception:
                pass

        # m2c decompilation
        m2c_with_ctx = None
        m2c_no_ctx = None
        m2c_done = 0

        if not skip_m2c:
            m2c_with_ctx, m2c_no_ctx = run_m2c_with_fallback(
                asm_path, fn_name, cleaned_ctx)
            m2c_done = 1 if (m2c_with_ctx or m2c_no_ctx) else 0

        # Git authorship
        gh = git_data.get(fn_name)
        git_authors_json = json.dumps(gh['authors']) if gh else None
        git_first_author = gh['first_author'] if gh else None
        git_commits_json = json.dumps(gh['commits']) if gh else None
        git_done = 1 if gh else 0

        # Format address
        vaddr = fn.get('function_address', '')
        if vaddr and str(vaddr).isdigit():
            vaddr = hex(int(vaddr))

        conn.execute("""
            INSERT INTO functions (
                unit_name, function_name, source_path,
                function_address, function_size, compiler_flags,
                target_asm, m2c_output, m2c_output_no_ctx, matching_c_code,
                context_includes, context_header, context_inlines,
                context_structs, context_function_signatures,
                git_authors, git_first_author, git_commit_history,
                processed_at, m2c_processed, git_processed, source_hash
            ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
            ON CONFLICT(unit_name, function_name) DO UPDATE SET
                source_path = excluded.source_path,
                function_address = excluded.function_address,
                function_size = excluded.function_size,
                compiler_flags = excluded.compiler_flags,
                target_asm = excluded.target_asm,
                m2c_output = COALESCE(excluded.m2c_output, functions.m2c_output),
                m2c_output_no_ctx = COALESCE(excluded.m2c_output_no_ctx,
                                              functions.m2c_output_no_ctx),
                matching_c_code = excluded.matching_c_code,
                context_includes = excluded.context_includes,
                context_header = excluded.context_header,
                context_inlines = excluded.context_inlines,
                context_structs = excluded.context_structs,
                context_function_signatures = excluded.context_function_signatures,
                git_authors = COALESCE(excluded.git_authors, functions.git_authors),
                git_first_author = COALESCE(excluded.git_first_author,
                                             functions.git_first_author),
                git_commit_history = COALESCE(excluded.git_commit_history,
                                               functions.git_commit_history),
                processed_at = excluded.processed_at,
                m2c_processed = CASE WHEN excluded.m2c_processed = 1 THEN 1
                                     ELSE functions.m2c_processed END,
                git_processed = CASE WHEN excluded.git_processed = 1 THEN 1
                                     ELSE functions.git_processed END,
                source_hash = excluded.source_hash
        """, (
            unit_name, fn_name, source_path_str or '',
            vaddr, fn['function_size'], compiler_flags,
            target_asm, m2c_with_ctx, m2c_no_ctx, matching_c,
            includes, header, inlines,
            structs, func_sigs,
            git_authors_json, git_first_author, git_commits_json,
            now, m2c_done, git_done, src_hash
        ))
        count += 1

    # Clean up temp ctx file
    if cleaned_ctx and cleaned_ctx.exists():
        try:
            cleaned_ctx.unlink()
        except Exception:
            pass

    # Update progress
    conn.execute("""
        INSERT INTO units_progress (unit_name, total_functions,
                                     processed_functions, ctx_built,
                                     last_updated)
        VALUES (?, ?, ?, ?, ?)
        ON CONFLICT(unit_name) DO UPDATE SET
            processed_functions = processed_functions + excluded.processed_functions,
            ctx_built = excluded.ctx_built,
            last_updated = excluded.last_updated
    """, (
        unit_name, len(functions), count,
        1 if (ctx_path and ctx_path.exists()) else 0, now
    ))

    conn.commit()
    return count, len(functions) - len(to_process)


def print_stats(conn: sqlite3.Connection):
    """Print database statistics."""
    total = conn.execute("SELECT COUNT(*) FROM functions").fetchone()[0]
    m2c_done = conn.execute(
        "SELECT COUNT(*) FROM functions WHERE m2c_processed = 1"
    ).fetchone()[0]
    git_done = conn.execute(
        "SELECT COUNT(*) FROM functions WHERE git_processed = 1"
    ).fetchone()[0]
    has_source = conn.execute(
        "SELECT COUNT(*) FROM functions "
        "WHERE matching_c_code != '' AND matching_c_code IS NOT NULL"
    ).fetchone()[0]
    has_asm = conn.execute(
        "SELECT COUNT(*) FROM functions "
        "WHERE target_asm != '' AND target_asm IS NOT NULL"
    ).fetchone()[0]
    has_m2c_ctx = conn.execute(
        "SELECT COUNT(*) FROM functions "
        "WHERE m2c_output IS NOT NULL AND m2c_output != ''"
    ).fetchone()[0]
    has_m2c_no_ctx = conn.execute(
        "SELECT COUNT(*) FROM functions "
        "WHERE m2c_output_no_ctx IS NOT NULL AND m2c_output_no_ctx != ''"
    ).fetchone()[0]
    units = conn.execute(
        "SELECT COUNT(DISTINCT unit_name) FROM functions"
    ).fetchone()[0]
    complete = conn.execute(
        "SELECT COUNT(*) FROM functions "
        "WHERE m2c_processed = 1 AND git_processed = 1 "
        "AND matching_c_code IS NOT NULL AND matching_c_code != '' "
        "AND target_asm IS NOT NULL AND target_asm != ''"
    ).fetchone()[0]

    # Unique authors
    unique_authors_row = conn.execute(
        "SELECT git_authors FROM functions "
        "WHERE git_authors IS NOT NULL"
    ).fetchall()
    all_authors = set()
    for row in unique_authors_row:
        try:
            for a in json.loads(row[0]):
                all_authors.add(a)
        except Exception:
            pass

    print(f"\n{'=' * 60}")
    print(f"Database Statistics:")
    print(f"  Total function rows:     {total}")
    print(f"  With target ASM:         {has_asm}")
    print(f"  With m2c (+ context):    {has_m2c_ctx}")
    print(f"  With m2c (no context):   {has_m2c_no_ctx}")
    print(f"  With matching C code:    {has_source}")
    print(f"  m2c processed:           {m2c_done}")
    print(f"  git processed:           {git_done}")
    print(f"  Unique units:            {units}")
    print(f"  Unique contributors:     {len(all_authors)}")
    print(f"  Complete entries:         {complete}")
    print(f"  (asm + m2c + C + git)")
    print(f"{'=' * 60}")


def main():
    parser = argparse.ArgumentParser(
        description="Generate training database from Melee decomp")
    parser.add_argument("--db", type=Path, default=DEFAULT_DB,
                        help="SQLite database path")
    parser.add_argument("--skip-m2c", action="store_true",
                        help="Skip m2c decompilation step")
    parser.add_argument("--unit", type=str, default=None,
                        help="Process only this unit")
    parser.add_argument("--rebuild-ctx", action="store_true",
                        help="Force rebuild of ctx files")
    parser.add_argument("--report", type=Path, default=None,
                        help="Path to pre-generated objdiff report JSON")
    parser.add_argument("--stats", action="store_true",
                        help="Print stats and exit")
    args = parser.parse_args()

    conn = init_db(args.db)

    if args.stats:
        print_stats(conn)
        conn.close()
        return

    # Load configs
    report = generate_report(args.report)
    objdiff_config = load_objdiff_config()

    all_matching = get_matching_functions(report)
    print(f"Found {len(all_matching)} functions at 100% match")

    # Group by unit
    units: dict[str, list[dict]] = {}
    for fn in all_matching:
        units.setdefault(fn['unit_name'], []).append(fn)

    if args.unit:
        if args.unit in units:
            units = {args.unit: units[args.unit]}
        else:
            print(f"Unit '{args.unit}' not found or has no 100% matches")
            conn.close()
            return

    print(f"Processing {len(units)} units with matching functions")
    print(f"Database: {args.db}")
    if args.skip_m2c:
        print("NOTE: Skipping m2c decompilation (run without --skip-m2c later)")
    print()

    total_processed = 0
    total_skipped = 0
    total_errors = 0
    start_time = time.time()

    sorted_units = sorted(units.items())

    for i, (unit_name, funcs) in enumerate(sorted_units):
        elapsed = time.time() - start_time
        rate = total_processed / elapsed if elapsed > 0 else 0

        # Estimate ETA
        remaining_funcs = sum(len(v) for _, v in sorted_units[i:])
        eta = remaining_funcs / rate if rate > 0 else 0

        print(f"[{i + 1}/{len(units)}] {unit_name} "
              f"({len(funcs)} funcs) "
              f"[done={total_processed} skip={total_skipped} "
              f"rate={rate:.1f}/s ETA={eta / 60:.0f}m]")

        try:
            processed, skipped = process_unit(
                conn, unit_name, funcs, objdiff_config,
                skip_m2c=args.skip_m2c, rebuild_ctx=args.rebuild_ctx)
            total_processed += processed
            total_skipped += skipped
        except KeyboardInterrupt:
            print("\n\nInterrupted! Progress has been saved.")
            print(f"Run again to continue from where you left off.")
            break
        except Exception as e:
            print(f"  ERROR: {e}")
            total_errors += 1
            continue

    elapsed = time.time() - start_time
    print(f"\nDone in {elapsed:.1f}s")
    print(f"  Processed: {total_processed}")
    print(f"  Skipped (already done): {total_skipped}")
    print(f"  Errors: {total_errors}")

    conn.execute(
        "INSERT OR REPLACE INTO metadata (key, value) VALUES (?, ?)",
        ('last_run', time.strftime('%Y-%m-%d %H:%M:%S'))
    )
    conn.execute(
        "INSERT OR REPLACE INTO metadata (key, value) VALUES (?, ?)",
        ('total_matching_functions', str(len(all_matching)))
    )
    conn.commit()

    print_stats(conn)
    conn.close()


if __name__ == "__main__":
    main()
