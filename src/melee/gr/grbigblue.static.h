#ifndef __GALE01_1E57BC
#define __GALE01_1E57BC

#include <platform.h>

#include <dolphin/mtx.h>

typedef struct grBb_LineIds {
    s32 v[32];
} grBb_LineIds;

typedef struct grBb_TrackEntry {
    s16 jobj_index;
    s16 start_index;
    s16 end_index;
    s16 pad;
    Vec3 delta;
} grBb_TrackEntry;

typedef struct grBb_YakumonoParams {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
    u8 pad64[0x68 - 0x64];
    f32 x68;
    f32 x6C;
    f32 x70;
    f32 x74;
    f32 x78;
    f32 x7C;
    f32 x80;
    f32 x84;
    u8 pad88[0xCC - 0x88];
    f32 xCC;
    f32 xD0;
    f32 xD4;
    f32 xD8;
    u8 padDC[0xE4 - 0xDC];
    f32 xE4;
    f32 xE8;
    f32 xEC;
    f32 xF0;
    f32 xF4;
    f32 xF8;
    f32 xFC;
    f32 x100;
    f32 x104;
    f32 x108;
    s32 x10C;
    s32 x110;
    u8 pad114[0x124 - 0x114];
    f32 x124;
    f32 x128;
    f32 x12C;
    f32 x130;
    Vec3 x134_translate;
    f32 x140_scale;
} grBb_YakumonoParams;

#endif
