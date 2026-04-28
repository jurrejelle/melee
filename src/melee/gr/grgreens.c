#include "placeholder.h"

#include <platform.h>

#include <melee/gr/forward.h>

#include <dolphin/os.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/ftdevice.h>
#include <melee/ft/ftlib.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/grgreens.h>
#include <melee/gr/grlib.h>
#include <melee/gr/grmaterial.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/inlines.h>
#include <melee/gr/stage.h>
#include <melee/gr/types.h>
#include <melee/it/it_2725.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/mp/mplib.h>

#define Gr_Greens_Block_Status_None 0
#define Gr_Greens_Block_Max 30

static u8 grGr_804D6AAC;
static s8 grGr_804D6AAD;
static struct {
    int x0_blockTimerMin;
    int x4_blockTimerMax;
    int x8_blockBombChance;

    char padC[0x24 - 0xC];

    int x24;
    int x28;

    char pad2C[0x34 - 0x2C];

    int x34_windTimerMin;
    int x38_windTimerMax;

    float x3C_windSpeed;
    float x40_left;
    float x44_right;
    float x48_top;
    float x4C_bottom;
}* grGr_params;
static StageCallbacks grGr_callbacks[] = {
    {
        grGreens_8021360C,
        grGreens_802138AC,
        grGreens_802138B4,
        grGreens_802138B8,
        NULL,
    },
    {
        grGreens_80213910,
        grGreens_8021393C,
        grGreens_80213944,
        grGreens_80213948,
        NULL,
    },
    {
        grGreens_802138BC,
        grGreens_80213900,
        grGreens_80213908,
        grGreens_8021390C,
        NULL,
    },
    {
        grGreens_8021394C,
        grGreens_80213978,
        grGreens_80213980,
        grGreens_80213984,
        NULL,
    },
    {
        grGreens_80213988,
        grGreens_802139B4,
        grGreens_802139BC,
        grGreens_802139C0,
        NULL,
    },
    {
        grGreens_802139C4,
        grGreens_80213AAC,
        grGreens_80213C10,
        grGreens_80214654,
        NULL,
    },
    {
        grGreens_80214674,
        grGreens_80214794,
        grGreens_8021479C,
        grGreens_80214804,
        0xC0000000,
    },
};

static s16 grGr_803E7840[128] = {
    5,    6,    7,    8,    9,    0xA,  0xB,  0xC,  0xD,  0xE,
    0xF,  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22,
};
static u8 grGr_8049F9E0[0x20];

static inline int randrange(int min, int max);
static inline int randrange(int min, int max)
{
    int diff;
    int rng = min;
    if (max > min) {
        diff = max - min;
        if (diff != 0) {
            rng = HSD_Randi(diff);
        } else {
            rng = 0;
        }
        rng = rng + min;
    } else if (max < min) {
        diff = min - max;
        if (diff != 0) {
            rng = HSD_Randi(diff);
        } else {
            rng = 0;
        }
        rng = rng + max;
    }
    return rng;
}

static inline struct grGreens_BlockVars* getBlock(Ground* gp, int i, int j);
static inline struct grGreens_BlockVars* getBlock(Ground* gp, int i, int j)
{
    return &gp->gv.greens.x8_blocks[i * 6 + j];
}

static inline Vec* getVec(Ground* gp, int i, int j);
static inline Vec* getVec(Ground* gp, int i, int j)
{
    return &gp->gv.greens.x4[i * 6 + j];
}

void grGreens_80213458(bool arg)
{
    grGr_804D6AAC = 1;
}

void grGreens_Init(void)
{
    PAD_STACK(8);
    grGr_params = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grGreens_80213524(0);
    grGreens_80213524(2);
    grGreens_80213524(6);
    grGreens_80213524(5);
    grGreens_80213524(4);
    Ground_801C39C0();
    Ground_801C3BB4();
    grLib_801C9A10();
    grGr_804D6AAC = 0;
}

void grGreens_802134F4(void) {}

void grGreens_802134F8(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grGreens_8021351C(void)
{
    return false;
}

Ground_GObj* grGreens_80213524(int id)
{
    Ground_GObj* gobj;
    StageCallbacks* cbs = &grGr_callbacks[id];
    gobj = Ground_GetStageGObj(id);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (cbs->callback3 != NULL) {
            gp->x1C_callback = cbs->callback3;
        }
        if (cbs->callback0 != NULL) {
            cbs->callback0(gobj);
        }
        if (cbs->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, cbs->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 281, id);
    }
    return gobj;
}

void grGreens_8021360C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    if (grGr_804D6AAC != 0) {
        Vec v;
        grLib_801C9A70(0, &v);
        HSD_JObjSetTranslate(Ground_801C2CF4(0), &v);
        grLib_801C9A70(1, &v);
        HSD_JObjSetTranslate(Ground_801C2CF4(1), &v);
        grLib_801C9A70(2, &v);
        HSD_JObjSetTranslate(Ground_801C2CF4(2), &v);
        grLib_801C9A70(3, &v);
        HSD_JObjSetTranslate(Ground_801C2CF4(3), &v);
    }
}

bool grGreens_802138AC(Ground_GObj* arg)
{
    return false;
}

void grGreens_802138B4(Ground_GObj* arg) {}

void grGreens_802138B8(Ground_GObj* arg) {}

void grGreens_802138BC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grGreens_80213900(Ground_GObj* arg)
{
    return false;
}

void grGreens_80213908(Ground_GObj* arg) {}

void grGreens_8021390C(Ground_GObj* arg) {}

void grGreens_80213910(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grGreens_8021393C(Ground_GObj* arg)
{
    return false;
}

void grGreens_80213944(Ground_GObj* arg) {}

void grGreens_80213948(Ground_GObj* arg) {}

void grGreens_8021394C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grGreens_80213978(Ground_GObj* arg)
{
    return false;
}

void grGreens_80213980(Ground_GObj* arg) {}

void grGreens_80213984(Ground_GObj* arg) {}

void grGreens_80213988(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grGreens_802139B4(Ground_GObj* arg)
{
    return false;
}

void grGreens_802139BC(Ground_GObj* arg) {}

void grGreens_802139C0(Ground_GObj* arg) {}

void grGreens_802139C4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    ftCo_800C06E8(gobj, 9, fn_80213B1C);
    gp->gv.greens.x0_flags.whole_thing = 0;
    gp->gv.greens.x4 = NULL;
    gp->gv.greens.x8_blocks = NULL;
    gp->gv.greens.xC = randrange(grGr_params->x34_windTimerMin,
                                 grGr_params->x38_windTimerMax);
    gp->gv.greens.x10 = 1;
    gp->gv.greens.x1C = 0;
    gp->gv.greens.x14 = HSD_Randi(2);
    gp->gv.greens.x18 = 0;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grGreens_80213AAC(Ground_GObj* arg)
{
    return false;
}

bool grGreens_80213AB4(Vec* vec, f32 maxX, f32 minX, f32 maxY, f32 minY)
{
    float maxY_actual;
    float maxX_actual;
    if (maxX > minX) {
        maxX_actual = maxX;
    } else {
        maxX_actual = minX;
        minX = maxX;
    }
    if (maxY > minY) {
        maxY_actual = maxY;
    } else {
        maxY_actual = minY;
        minY = maxY;
    }
    if (minX < vec->x && vec->x < maxX_actual) {
        if (minY < vec->y && vec->y < maxY_actual) {
            return true;
        }
    }
    return false;
}

bool fn_80213B1C(Ground_GObj* ground_gobj, Fighter_GObj* fighter_gobj,
                 Vec* vec)
{
    Vec vec2;
    PAD_STACK(4);
    ftLib_80086644(fighter_gobj, &vec2);
    vec->y = 0.0f;
    vec->z = 0.0f;
    switch (GET_GROUND(ground_gobj)->gv.greens.x18) {
    case 1:
        if (grGreens_80213AB4(&vec2, -grGr_params->x40_left,
                              -grGr_params->x44_right, grGr_params->x48_top,
                              grGr_params->x4C_bottom) == true)
        {
            vec->x = -grGr_params->x3C_windSpeed;
            return true;
        }
        break;
    case 2:
        if (grGreens_80213AB4(&vec2, grGr_params->x44_right,
                              grGr_params->x40_left, grGr_params->x48_top,
                              grGr_params->x4C_bottom) == true)
        {
            vec->x = grGr_params->x3C_windSpeed;
            return true;
        }
        break;
    }
    vec->x = 0.0f;
    return false;
}

void grGreens_80213C10(Ground_GObj* gobj)
{
    // Ground_GObj* gobj2 = Ground_801C2BA4(4);
    // Ground* gp = GET_GROUND(gobj);
    // Ground* gp2 = GET_GROUND(gobj2);
    // gp->u.greens.x18 = 0;
    // if (grGr_804D6AAC == 0 && grGr_804D6AAD == 0) {
    //     gp->u.greens.x1C++;
    //     switch (gp->u.greens.x4) {}
    // }
}

void grGreens_80214654(Ground_GObj* arg)
{
    return;
}

void fn_80214658(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    gp->gv.greens.x0_flags.b0 = 0;
    grGr_804D6AAD = 0;
}

void grGreens_80214674(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    gp->gv.greens.x4 = HSD_MemAlloc(5 * 6 * sizeof(*gp->gv.greens.x4));
    memzero(gp->gv.greens.x4, 5 * 6 * sizeof(*gp->gv.greens.x4));
    gp->gv.greens.x8_blocks =
        HSD_MemAlloc(5 * 6 * sizeof(*gp->gv.greens.x8_blocks));
    memzero(gp->gv.greens.x8_blocks, 5 * 6 * sizeof(*gp->gv.greens.x8_blocks));
    grGreens_8021483C(gobj);
    if (grGr_804D6AAC == 0) {
        grGreens_80214B58(gobj);
    }
    grGr_804D6AAC = 0;
    grGreens_80214FA8(gobj);
    Ground_801C10B8(gobj, fn_80214658);
    gp->gv.greens.xC = randrange(grGr_params->x0_blockTimerMin,
                                 grGr_params->x4_blockTimerMax);
    gp->gv.greens.x0_flags.b0 = 1;
    grGr_804D6AAD = 1;
}

bool grGreens_80214794(Ground_GObj* arg)
{
    return false;
}

void grGreens_8021479C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(4);
    if (!gp->gv.greens.x0_flags.b0) {
        grGreens_802166C4(gobj);
    }
    Ground_801C2FE0(gobj);
    if (!gp->gv.greens.x0_flags.b0) {
        grGreens_80216C20(gobj);
    }
    lb_800115F4();
}

void grGreens_80214804(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    HSD_Free((void*) gp->gv.corneria.xC8);
    HSD_Free((void*) gp->gv.corneria.xCC);
}

void grGreens_8021483C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Vec vec;
    float left_max = -F32_MAX;
    float left_min = F32_MAX;
    float left_top = -F32_MAX;
    float left_bottom = F32_MAX;
    float right_max = -F32_MAX;
    float right_top = -F32_MAX;
    float right_min = F32_MAX;
    float right_bottom = F32_MAX;
    int i;

    for (i = 0; i < 30; i++) {
        HSD_JObj* jobj = Ground_801C3FA4(gobj, grGr_803E7840[i]);

        HSD_ASSERT(1014, jobj);
        lb_8000B1CC(jobj, NULL, &vec);
        if (vec.x < 0.0f) {
            if (left_max < vec.x) {
                left_max = vec.x;
            }
            if (left_min > vec.x) {
                left_min = vec.x;
            }
            if (left_top < vec.y) {
                left_top = vec.y;
            }
            if (left_bottom > vec.y) {
                left_bottom = vec.y;
            }
        } else {
            if (right_max < vec.x) {
                right_max = vec.x;
            }
            if (right_min > vec.x) {
                right_min = vec.x;
            }
            if (right_top < vec.y) {
                right_top = vec.y;
            }
            if (right_bottom > vec.y) {
                right_bottom = vec.y;
            }
        }
    }
    left_max = (left_max - left_min) * 0.5f;
    for (i = 0; i < 5; i++) {
        float y = ((left_top - left_bottom) * 0.25f * i) + left_bottom;
        Vec* row = &gp->gv.greens.x4[i * 6];

        row[0].x = (left_max * 0.0f) + left_min;
        row[0].y = y;
        row[0].z = 0.0f;
        row[1].x = (left_max * 1.0f) + left_min;
        row[1].y = y;
        row[1].z = 0.0f;
        row[2].x = (left_max * 2.0f) + left_min;
        row[2].y = y;
        row[2].z = 0.0f;
    }
    right_max = (right_max - right_min) * 0.5f;
    for (i = 0; i < 5; i++) {
        float y = ((right_top - right_bottom) * 0.25f * i) + right_bottom;
        Vec* row = &gp->gv.greens.x4[i * 6];

        row[3].x = (right_max * 0.0f) + right_min;
        row[3].y = y;
        row[3].z = 0.0f;
        row[4].x = (right_max * 1.0f) + right_min;
        row[4].y = y;
        row[4].z = 0.0f;
        row[5].x = (right_max * 2.0f) + right_min;
        row[5].y = y;
        row[5].z = 0.0f;
    }
}

/// #grGreens_80214B58

void grGreens_80214FA8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    unsigned int i;
    int j;
    int k;
    for (i = 0; i < 30; i++) {
        mpJointSetCb2(grGr_803E7840[i], gp, fn_80216DE4);
    }
    for (j = 0; j < 30; j++) {
        HSD_JObj* jobj = Ground_801C3FA4(gobj, grGr_803E7840[j]);
        if (jobj != NULL) {
            HSD_JObjSetFlags(jobj, JOBJ_HIDDEN);
        } else {
            HSD_ASSERT(1203, 0);
        }
    }
    for (k = 0; k < 5; k++) {
        for (j = 0; j < 6; j++) {
            switch (grGr_8049F9E0[k * 6 + j]) {
            case 1:
            case 2:
                grGreens_80215358(gobj, k, j, grGr_8049F9E0[k * 6 + j], 3);
                break;
            }
        }
    }
}

void grGreens_802150C4(Ground_GObj* gobj, int arg1, int arg2)
{
    Ground* gp = GET_GROUND(gobj);

    if (arg2 > 0 && arg1 > 0 &&
        getBlock(gp, arg2 - 1, arg1 - 1)->status == 3)
    {
        if (getBlock(gp, arg2 - 1, arg1)->status == 3) {
            mpLib_800581DC(getBlock(gp, arg2 - 1, arg1 - 1)->x18,
                           getBlock(gp, arg2 - 1, arg1)->x18);
        } else if (getBlock(gp, arg2, arg1 - 1)->status == 3) {
            mpLib_800581DC(getBlock(gp, arg2 - 1, arg1 - 1)->x18,
                           getBlock(gp, arg2, arg1 - 1)->x18);
        }
    }
    if (arg2 < 4 && arg1 > 0 &&
        getBlock(gp, arg2 + 1, arg1 - 1)->status == 3)
    {
        if (getBlock(gp, arg2 + 1, arg1)->status == 3) {
            mpLib_800581DC(getBlock(gp, arg2 + 1, arg1 - 1)->x18,
                           getBlock(gp, arg2 + 1, arg1)->x18);
        } else if (getBlock(gp, arg2, arg1 - 1)->status == 3) {
            mpLib_800581DC(getBlock(gp, arg2 + 1, arg1 - 1)->x18,
                           getBlock(gp, arg2, arg1 - 1)->x18);
        }
    }
    if (arg2 > 0 && arg1 < 5 &&
        getBlock(gp, arg2 - 1, arg1 + 1)->status == 3)
    {
        if (getBlock(gp, arg2 - 1, arg1)->status == 3) {
            mpLib_800581DC(getBlock(gp, arg2 - 1, arg1 + 1)->x18,
                           getBlock(gp, arg2 - 1, arg1)->x18);
        } else if (getBlock(gp, arg2, arg1 + 1)->status == 3) {
            mpLib_800581DC(getBlock(gp, arg2 - 1, arg1 + 1)->x18,
                           getBlock(gp, arg2, arg1 + 1)->x18);
        }
    }
    if (arg2 < 4 && arg1 < 5 &&
        getBlock(gp, arg2 + 1, arg1 + 1)->status == 3)
    {
        if (getBlock(gp, arg2 + 1, arg1)->status == 3) {
            mpLib_800581DC(getBlock(gp, arg2 + 1, arg1 + 1)->x18,
                           getBlock(gp, arg2 + 1, arg1)->x18);
            return;
        }
        if (getBlock(gp, arg2, arg1 + 1)->status == 3) {
            mpLib_800581DC(getBlock(gp, arg2 + 1, arg1 + 1)->x18,
                           getBlock(gp, arg2, arg1 + 1)->x18);
        }
    }
}

void grGreens_80215358(Ground_GObj* gobj, int i, int j, int arg3, int arg4)
{
    Ground* gp = GET_GROUND(gobj);
    struct grGreens_BlockVars* block = getBlock(gp, i, j);
    unsigned char arr[30];
    int m;
    int n;
    int num;
    int type;
    Ground_GObj* block_gobj;
    HSD_JObj* jobj;
    Item_GObj* item_gobj;
    int x24_or_x28;
    float grMaterial_801C8DE0_paramA;
    float grMaterial_801C8DE0_paramB;
    Vec vec;
    float f;
    HSD_ASSERT(1305, block->status==Gr_Greens_Block_Status_None);
    for (n = 0; n < 30; n++) {
        arr[n] = 0;
    }
    for (n = 0; n < 6; n++) {
        for (m = 0; m < 5; m++) {
            if (getBlock(gp, n, m)->status != Gr_Greens_Block_Status_None) {
                arr[getBlock(gp, n, m)->index] = 1;
            }
        }
    }
    for (num = 0; num < 30; num++) {
        if (arr[num] == 0) {
            break;
        }
    }
    HSD_ASSERT(1316, num<Gr_Greens_Block_Max);
    if (arg3 == 1) {
        type = 1;
    } else if (arg3 == 2) {
        type = 3;
    } else {
        HSD_ASSERT(1324, 0);
    }
    block_gobj = grGreens_80213524(type);
    HSD_ASSERT(1325, block_gobj);
    jobj = Ground_801C3FA4(gobj, grGr_803E7840[num]);
    HSD_JObjClearFlags(jobj, JOBJ_HIDDEN);
    item_gobj = grMaterial_801C8CFC(8, 0, gp, jobj, fn_802159B4, fn_80215B84,
                                    fn_80215D50);
    if (arg3 == 2) {
        x24_or_x28 = grGr_params->x28;
    } else {
        x24_or_x28 = grGr_params->x24;
    }
    grMaterial_801C8DE0_paramB = x24_or_x28 * Ground_801C0498();
    grMaterial_801C8DE0_paramA = 5.0f * Ground_801C0498();
    grMaterial_801C8DE0(item_gobj, 0.0f, grMaterial_801C8DE0_paramA, 0.0f,
                        0.0f, grMaterial_801C8DE0_paramA, 0.0f,
                        grMaterial_801C8DE0_paramB);
    grMaterial_801C8E08(item_gobj);
    grMaterial_801C8E68(item_gobj, GA_Ground);
    block->status = arg4;
    block->index = num;
    block->x1_1 = (arg3 == 2) ? 1 : 0;
    block->x1_2 = 0;
    block->x1_3 = 0;
    block->x8 =
        (arg4 == 1) ? Stage_GetBlastZoneTopOffset() : getVec(gp, i, j)->y;
    block->x4 = 0.0f;
    block->xC = block_gobj;
    block->x10 = item_gobj;
    block->x14 = jobj;
    block->x18 = Ground_801C32D4(6, grGr_803E7840[0]);
    block->x1C = 0;
    block->x1_4 = 0;
    block->x1_7 = 0;
    vec.x = getVec(gp, i, j)->x;
    vec.y = block->x8;
    vec.z = 0.0f;
    if (arg4 == 3) {
        block->x1_5 = 1;
    } else {
        block->x1_5 = 0;
    }
    HSD_JObjSetTranslate(block_gobj->hsd_obj, &vec);
    f = 1.0f / Ground_801C0498();
    vec.x *= f;
    vec.y *= f;
    vec.z *= f;
    HSD_JObjSetTranslate(block->x14, &vec);
    mpLib_80055E9C(block->x18);
    mpLib_80057424(block->x18);
}

void fn_802159B4(Item_GObj* item_gobj, Ground* gp)
{
    return;
}

void grGreens_802159B8(Ground* gp, int i, int j, int value)
{
    HSD_GObj* gobj = getBlock(gp, i, j)->x10;
    Vec vec;
    float f;
    if (gobj != NULL && !getBlock(gp, i, j)->x1_7) {
        getBlock(gp, i, j)->x1_7 = 1;
        grMaterial_801C8E28(gobj);
        getBlock(gp, i, j)->x1C = value;

        if (getBlock(gp, i, j)->x1_1) {
            HSD_JObjSetFlagsAll(getBlock(gp, i, j)->xC->hsd_obj, JOBJ_HIDDEN);
            grMaterial_801C8D98(gobj, 1);
            it_80275414(gobj);
            getBlock(gp, i, j)->x1_2 = 1;
            HSD_JObjGetTranslation(gobj->hsd_obj, &vec);
            vec.y += 5.0f * Ground_801C0498();
            efSync_Spawn(1039, gobj, &vec);
        } else {
            f = 0.0f;
            getBlock(gp, i, j)->x1_3 = 1;
            Camera_80030E44(2, NULL);
            HSD_JObjGetTranslation(gobj->hsd_obj, &vec);
            vec.y += 5.0f * Ground_801C0498();
            efSync_Spawn(1032, gobj, &vec, &f);
            Ground_801C5414(430007, 186);
        }
    }
}

void fn_80215B84(Item_GObj* item_gobj, Ground* gp, Vec* arg2, HSD_GObj* gobj,
                 float arg4)
{
    int i;
    int j;
    int row = -1;
    int col = 0;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            struct grGreens_BlockVars* block = getBlock(gp, i, j);

            if (block->status != Gr_Greens_Block_Status_None &&
                block->x10 == item_gobj)
            {
                row = i;
                col = j;
                i = 5;
                break;
            }
        }
    }
    HSD_ASSERT(1465, row != -1);
    grGreens_802159B8(gp, col, row, (s32) gobj);
}

void fn_80215D50(Item_GObj* item_gobj, Ground* gp, HSD_GObj* gobj)
{
    return;
}

s32 grGreens_80215D54(Ground_GObj* gobj, int arg1, int arg2)
{
    Ground* gp = GET_GROUND(gobj);
    int row;
    int x = arg1 << 5;

    for (row = 1; row < 5; row++) {
        int offset = row * 0xC0;
        u8* blocks = (u8*) gp->gv.greens.x8_blocks;
        int status = (blocks[offset + x] >> 4) & 0xF;

        if ((status == 1 || status == 2) &&
            (((blocks[(row - 1) * 0xC0 + x] >> 4) & 0xF) == 0))
        {
            int i;
            int count = 5 - row;

            if (row < 5) {
                do {
                    struct grGreens_BlockVars temp =
                        *(struct grGreens_BlockVars*) (blocks + offset + x);
                    *(struct grGreens_BlockVars*) (blocks + offset + x) =
                        *(struct grGreens_BlockVars*) (blocks + offset + x -
                                                       0xC0);
                    *(struct grGreens_BlockVars*) (blocks + offset + x - 0xC0) =
                        temp;
                    offset += 0xC0;
                    count -= 1;
                } while (count != 0);
            }
            if ((((blocks[(row - 1) * 0xC0 + x] >> 4) & 0xF) == 2)) {
                blocks[(row - 1) * 0xC0 + x] =
                    (blocks[(row - 1) * 0xC0 + x] & ~0xF0) | 0x10;
            }
            row = 0;
        }
    }
    return (s32) gobj;
}

/// #grGreens_80215ED8

/// #grGreens_802166C4

void grGreens_80216C20(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    int i;
    int j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            struct grGreens_BlockVars* block = getBlock(gp, i, j);

            if (block->x1_6) {
                if (i > 0 && getBlock(gp, i - 1, j)->status == 3) {
                    mpLib_800581DC(block->x18, getBlock(gp, i - 1, j)->x18);
                }
                if (j > 0 && getBlock(gp, i, j - 1)->status == 3) {
                    mpLib_800581DC(block->x18, getBlock(gp, i, j - 1)->x18);
                }
                if (i < 4 && getBlock(gp, i + 1, j)->status == 3) {
                    mpLib_800581DC(block->x18, getBlock(gp, i + 1, j)->x18);
                }
                if (j < 5 && getBlock(gp, i, j + 1)->status == 3) {
                    mpLib_800581DC(block->x18, getBlock(gp, i, j + 1)->x18);
                }
                block->x1_6 = 0;
            } else if (block->x1_7) {
                grGreens_802150C4(gobj, j, i);
                block->x1_7 = 0;
            }
        }
    }
}

void fn_80216DE4(Ground* gp, s32 arg1, CollData* arg2, s32 arg3,
                 enum mpLib_GroundEnum arg4, f32 farg0)
{
    int i;
    int j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            if (getBlock(gp, i, j)->status != Gr_Greens_Block_Status_None &&
                arg1 == getBlock(gp, i, j)->x18)
            {
                getBlock(gp, i, j)->x1_4 = 1;
                i = 5;
                break;
            }
        }
    }
}

DynamicsDesc* grGreens_80216E64(enum_t arg)
{
    return false;
}

bool grGreens_80216E6C(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
