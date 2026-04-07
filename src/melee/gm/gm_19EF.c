#include "gm_19EF.h"

#include "gm_1601.h"
#include "gm_1A36.h"
#include "gm_1A45.h"
#include "gm_unsplit.h"

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/sc/types.h>

static HSD_Archive* lbl_804D6698;
static struct {
    HSD_JObj* x0;
    s32 x4;
} lbl_804D66B0;
static HSD_JObj* lbl_804D66B8;
static struct {
    HSD_JObj* x0;
    s32 x4;
} lbl_804D66D0;
static struct {
    s32 x0;
    s32 x4;
} lbl_804D66E0;
static HSD_JObj* lbl_804D66E8;
static HSD_Archive* lbl_804D66F0;
static HSD_JObj* lbl_804D66F4;
static u32 lbl_804D66F8;

static struct {
    u8 x0;
    u8 pad_01[0x3];
    s32 x4;
    int x8;
    s32 xC;
    u32 x10;
    u8 pad_14;
    u8 x15;
    u8 x16;
    u8 pad_17;
    int x18;
    u16 x1C;
    u16 x1E;
    u8 x20;
    u8 pad_21;
    u16 x22;
    HSD_Text* x24;
    u8 pad_28[0x60 - 0x28];
    u8 x60;
    u8 pad_61[0x70 - 0x61];
    s32 x70;
    u8 pad_74[0x78 - 0x74];
} lbl_80479A98;

static void fn_8019EFC4(HSD_PadStatus*);
static void fn_8019F2D4(u32);

/// seems to handle "Go!" animations, based on .dat filenames

static void fn_8019F1D0(void)
{
    char sp8[28];
    u32 value;
    char* ptr;
    u32 rem;
    u8 count;

    count = 0;
    value = lbl_80479A98.x8;
    HSD_SisLib_803A7664(lbl_80479A98.x24);
    if (value != 0) {
        while (value != 0) {
            value /= 10;
            count++;
        }
        rem = lbl_80479A98.x8;
        ptr = &sp8[count];
        *ptr = '\0';
        while (count != 0) {
            *(ptr - 1) = (char) ((rem % 10) + 0x30);
            rem /= 10;
            ptr--;
            count--;
        }
    } else {
        sp8[0] = 0x30;
        sp8[1] = 0;
    }
    HSD_SisLib_803A6B98(lbl_80479A98.x24, 240.0f, 176.0f, sp8);
}

static void fn_8019F6EC(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);

    HSD_JObjReqAnimAll(jobj, (f32) lbl_804D66E0.x4);
    if (lbl_80479A98.x0 == 0) {
        if (lbl_804D66E0.x4 < 0x32) {
            lbl_804D66E0.x4 += 1;
        } else if (lbl_80479A98.x20 != 0) {
            lbAudioAx_800237A8(0x9C43, 0x7F, 0x40);
            lbAudioAx_80023F28(0x20);
            lbl_80479A98.x0 = 0xAU;
        }
    } else if (lbl_80479A98.x0 == 9) {
        if (lbl_804D66E0.x4 < 0x50) {
            lbl_804D66E0.x4 += 1;
        } else if ((u32) lbl_80479A98.x8 == (u32) lbl_80479A98.xC &&
                   lbl_80479A98.x70 == 0)
        {
            gm_801A4B60();
            lbl_80479A98.x18 = 1;
        }
    }
    HSD_JObjAnimAll(jobj);
    HSD_JObjAnimAll(lbl_804D66B8);
    HSD_JObjAnimAll(lbl_804D66E8);
}

static void fn_8019F810(void)
{
    HSD_PadStatus* pad;
    u32 trigger;
    PAD_STACK(16);

    pad = &HSD_PadCopyStatus[lbl_80479A98.x15];
    trigger = pad->trigger;
    fn_8019EFC4(pad);
    if (lbl_80479A98.x0 < 8U) {
        lbl_804D66B0.x4 += 1;
        if (lbl_804D66B0.x4 > 0x31F) {
            lbl_804D66B0.x4 = 0x190;
        }
        HSD_JObjReqAnimAll(lbl_804D66B0.x0, (f32) lbl_804D66B0.x4);
        HSD_JObjAnimAll(lbl_804D66B0.x0);
    } else {
        HSD_JObjSetFlagsAll(lbl_804D66B0.x0, 0x10U);
    }
    if (lbl_80479A98.x0 == 9) {
        if ((u32) lbl_80479A98.x8 == (u32) lbl_80479A98.xC) {
            if (lbl_80479A98.x4 < 3) {
                if (lbl_80479A98.x4 < 0) {

                } else {
                    lbl_80479A98.x18 = 1;
                }
            }
        } else {
            u32 var_r4;
            u32 temp_r0;

            fn_80168F2C();
            var_r4 = lbl_80479A98.xC;
            temp_r0 = lbl_80479A98.x8 - lbl_80479A98.x10;
            if (temp_r0 < var_r4) {

            } else {
                var_r4 = temp_r0;
            }
            lbl_80479A98.x8 = var_r4;
        }
    }
    if (lbl_80479A98.x0 == 0xA) {
        HSD_JObjReqAnimAll(lbl_804D66D0.x0, (f32) lbl_804D66D0.x4);
        HSD_JObjAnimAll(lbl_804D66D0.x0);
        if (lbl_804D66D0.x4 < 0x2B2) {
            lbl_804D66D0.x4 += 1;
        } else {
            gm_801A4B60();
            lbl_80479A98.x18 = 0;
        }
    }
    fn_8019F2D4(trigger);
    fn_8019F1D0();
}

/// #fn_8019F9C4

/// #gm_801A0A10_OnEnter

void gm_801A0A10_OnEnter(void* arg0_)
{
    DebugGameOverData* arg0 = arg0_;

    lbl_80479A98.x60 = 0;
    lbl_80479A98.x22 = arg0->x18;
    lbl_80479A98.x1E = (u16) (arg0->x18 / 10);
    if (lbl_80479A98.x1E > 0x3E7U) {
        lbl_80479A98.x1E = 0x3E7U;
    }
    lbl_80479A98.x1C = arg0->x16;
    if (lbl_80479A98.x1E >= lbl_80479A98.x1C) {
        lbl_80479A98.x20 = 0;
    } else {
        lbl_80479A98.x20 = 1;
    }
    lbl_80479A98.x16 = (u8) arg0->x15;
    lbl_80479A98.x4 = (s32) arg0->x8;
    lbl_80479A98.x8 = (s32) arg0->x0;
    lbl_80479A98.xC = (s32) ((s32) arg0->x0 / 2);
    lbl_80479A98.x10 = (u32) (lbl_80479A98.x8 - lbl_80479A98.xC) / 120;
    if (lbl_80479A98.x10 == 0) {
        lbl_80479A98.x10 = 1U;
    }
    lbl_80479A98.x15 = arg0->slot;
    fn_8019F9C4(arg0->ckind);
}

void gm_801A0B18_OnLeave(void* arg0_)
{
    DebugGameOverData* arg0 = arg0_;
    arg0->x4 = lbl_80479A98.x8;
    arg0->xC = lbl_80479A98.x18;
    arg0->x18 = lbl_80479A98.x22;
    lbAudioAx_800236DC();
    lbArchive_80016EFC(lbl_804D6698);
}

static void fn_801A0B60(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjReqAnimAll(jobj, lbl_804D66F8);
    HSD_JObjAnimAll(jobj);
    if (lbl_804D66F8 == 0xBD) {
        if (((u32) gm_801A36A0(4) & 0x1000) || ((u32) gm_801A36A0(4) & 0x100))
        {
            lbl_804D66F8 += 1;
        }
    } else {
        lbl_804D66F8 += 1;
    }
    if ((int) HSD_AObjGetCurrFrame(lbl_804D66F4->aobj) >=
        (int) HSD_AObjGetEndFrame(lbl_804D66F4->aobj))
    {
        gm_801A4B60();
    }
}

void gm_801A0C6C_OnEnter(void* unused)
{
    SceneDesc* sp10;
    HSD_GObj* temp_r30;
    HSD_GObj* temp_r30_2;
    HSD_GObj* temp_r30_3;
    HSD_JObj* temp_r3;
    HSD_CObj* cobj;
    HSD_LObj* lobj;
    PAD_STACK(4);

    lbl_804D66F8 = 0;
    lbl_804D66F0 =
        lbArchive_80016DBC("IfComSn.dat", &sp10, "ScComSoon_scene_data", 0);

    temp_r30 = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(sp10->cameras[0].desc);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(temp_r30, HSD_GObj_803910D8, 0);
    temp_r30->gxlink_prios = 0x801;

    temp_r30_2 = GObj_Create(0xB, 0xF, 0);
    lobj = lb_80011AC4(sp10->lights);
    HSD_GObjObject_80390A70(temp_r30_2, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(temp_r30_2, HSD_GObj_LObjCallback, 0, 0);
    temp_r30_3 = GObj_Create(0xE, 0xF, 0);
    temp_r3 = HSD_JObjLoadJoint(sp10->models[0]->joint);
    HSD_GObjObject_80390A70(temp_r30_3, HSD_GObj_804D7849, temp_r3);
    GObj_SetupGXLink(temp_r30_3, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(temp_r30_3, fn_801A0B60, 0);
    gm_8016895C(temp_r3, sp10->models[0], 0);
    HSD_JObjReqAnimAll(temp_r3, 0.0f);
    HSD_JObjAnimAll(temp_r3);
    lb_80011E24(temp_r3, &lbl_804D66F4, 1, -1);
}

extern HSD_Archive* lbl_804D66F0;

void gm_801A0E0C_OnLeave(void* unused)
{
    lbArchive_80016EFC(lbl_804D66F0);
    lbAudioAx_800236DC();
}
