#include "grrcruise.h"

#include "grzakogenerator.h"

#include <platform.h>

#include "cm/camera.h"

#include "forward.h"

#include "gm/gm_1A45.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "gr/stage.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
#include "sysdolphin/baselib/debug.h"
#include "sysdolphin/baselib/memory.h"

#include <math.h>
#include <baselib/archive.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <MSL/trigf.h>

S16Vec3 grRc_803E4DA8[] = {
    { 0, 1, 1 },   { 1, 1, 1 },   { 2, 1, 1 },   { 3, 1, 1 },   { 4, 1, 1 },
    { 11, 1, 7 },  { 10, 1, 17 }, { 6, 1, 7 },   { 7, 1, 7 },   { 8, 1, 7 },
    { 9, 1, 7 },   { 12, 1, 19 }, { 13, 1, 18 }, { 14, 1, 18 }, { 15, 1, 18 },
    { 16, 1, 18 }, { 17, 1, 18 }, { 18, 1, 18 }, { 19, 1, 18 }, { 20, 1, 18 },
    { 21, 1, 18 }, { 22, 1, 18 }, { 23, 1, 18 },
};

StageCallbacks grRc_803E4E34[7] = {
    { grRCruise_801FF3B4, grRCruise_801FF3E0, grRCruise_801FF3E8,
      grRCruise_801FF3EC, 0 },
    { grRCruise_801FF5B4, grRCruise_801FF6CC, grRCruise_801FF6D4,
      grRCruise_801FF738, 0xC0000000 },
    { grRCruise_801FF3F0, grRCruise_801FF434, grRCruise_801FF43C,
      grRCruise_801FF440, 0 },
    { grRCruise_801FF924, grRCruise_801FFAD4, grRCruise_801FFADC,
      grRCruise_80200070, 0 },
    { grRCruise_80200074, grRCruise_8020014C, grRCruise_80200154,
      grRCruise_8020045C, 0 },
    { grRCruise_801FF73C, grRCruise_801FF794, grRCruise_801FF79C,
      grRCruise_801FF7A0, 0 },
    { grRCruise_801FF7A4, grRCruise_801FF8DC, grRCruise_801FF8E4,
      grRCruise_801FF920, 0 },
};

char grRc_803E4EC0[] = "/GrRc.dat";

struct grRCruise_StageData {
    StageData x00;
    char x34[0x24];
};

struct grRCruise_801FF924_GroundVars {
    u8 x00;
    u8 pad_01[3];
    Vec3 x04;
    Vec3 x10;
    Vec3 x1C;
    HSD_JObj* x28[3];
    HSD_JObj* x34[3];
    HSD_JObj* x40;
};

struct grRCruise_StageData grRc_803E4ECC = {
    {
        RCRUISE,
        grRc_803E4E34,
        grRc_803E4EC0,
        grRCruise_801FF168,
        grRCruise_801FF164,
        grRCruise_801FF298,
        grRCruise_801FF29C,
        grRCruise_801FF2C0,
        grRCruise_80201C50,
        grRCruise_80201C58,
        4,
        grRc_803E4DA8,
        ARRAY_SIZE(grRc_803E4DA8),
    },
    "%s:%d: couldn t get gobj(id=%d)\n",
};


extern Vec3 grRc_803B8288;
extern s16 grRc_803E4FF0[];
extern s16 grRc_804D4790[4];

static struct {
    f32 x0;
    f32 x4;
    f32 x8;
    s32 x0C;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    s32 x3C;
    s32 x40;
    s32 x44;
}* grRc_804D6A10;

void grRCruise_801FF164(bool arg) {}

void grRCruise_801FF168(void)
{
    HSD_GObj* jgobj;
    HSD_GObj* grgobj;
    Ground* gp;
    Ground* gp2;
    HSD_JObj* jobj;
    HSD_GObj* gobj6;
    HSD_GObj* gobj1;
    HSD_GObj* gobj4;

    grRc_804D6A10 = Ground_801C49F8();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 0;
    jgobj = grRCruise_801FF2C8(3);
    gp = GET_GROUND(jgobj);
    gp->gv.rcruise.xC4.b0 = 1;
    jobj = GET_JOBJ(jgobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    grgobj = grRCruise_801FF2C8(3);
    gp2 = GET_GROUND(grgobj);
    gp2->gv.rcruise2.xEC = jgobj;
    grRCruise_801FF2C8(0);
    grRCruise_801FF2C8(2);
    grRCruise_801FF2C8(5);
    gobj1 = grRCruise_801FF2C8(1);
    gobj6 = grRCruise_801FF2C8(6);
    gobj4 = grRCruise_801FF2C8(4);
    Ground_801C39C0();
    Ground_801C3BB4();
    grRCruise_801FFADC(grgobj);
    Ground_801C2FE0(gobj1);
    Ground_801C32AC(1);
    Ground_801C2FE0(gobj6);
    Ground_801C32AC(6);
    Ground_801C2FE0(gobj4);
    Ground_801C32AC(4);
    mpLib_80057BC0(11);
}

void grRCruise_801FF298(void) {}

void grRCruise_801FF29C(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grRCruise_801FF2C0(void)
{
    return false;
}

HSD_GObj* grRCruise_801FF2C8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grRc_803E4E34[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport(grRc_803E4ECC.x34, "grrcruise.c", 290, gobj_id);
    }

    return gobj;
}

void grRCruise_801FF3B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grRCruise_801FF3E0(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF3E8(Ground_GObj* arg) {}

void grRCruise_801FF3EC(Ground_GObj* arg) {}

void grRCruise_801FF3F0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grRCruise_801FF434(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF43C(Ground_GObj* arg) {}

void grRCruise_801FF440(Ground_GObj* arg) {}

void grRCruise_801FF444(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    mpJointSetCb1(5, gobj, grRCruise_80200578);
    mpJointSetCb1(27, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(36, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(37, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(38, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(39, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(40, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(41, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(42, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(43, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(28, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(29, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(30, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(31, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(32, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(33, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(34, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(35, gobj, (mpLib_Callback) grRCruise_802010A4);
    gp->gv.rcruise.x10 = 0;
}

void grRCruise_801FF5B4(Ground_GObj* gobj)
{
    Vec3 pos;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.rcruise.x10 = 1;
    gp->gv.rcruise.entries = HSD_MemAlloc(0x198);
    HSD_ASSERTMSG(0x19A, gp->gv.rcruise.entries != NULL, "gp->u.map.chikuwa");
    grRCruise_80201410(gobj);
    Ground_801C10B8(gobj, grRCruise_801FF444);
    grRCruise_80200540(gobj);
    grRCruise_80200B48(gobj);
    Ground_801C2FE0(gobj);
    mpLib_80058560();
    pos = grRc_803B8288;
    gp->gv.rcruise.x04 = lb_80011A50(&pos, -1, 0.4f, 0.0f, 1.0471976f,
                                     -10000.0f, 10000.0f, 10000.0f, -10000.0f);
    gp->gv.rcruise.x08 = 0.017453292f;
    gp->gv.rcruise.x0C = 1;
}

bool grRCruise_801FF6CC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF6D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.unk.xD4 == 0) {
        grRCruise_80201588(gobj);
        grRCruise_8020071C(gobj);
        grRCruise_80200C04(gobj);
    }
    lb_800115F4();
    grRCruise_80201110(gobj);
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF738(Ground_GObj* arg) {}

void grRCruise_801FF73C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
    HSD_JObjSetFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
    HSD_JObjClearFlagsAll(Ground_801C3FA4(gobj, 31), JOBJ_HIDDEN);
}

bool grRCruise_801FF794(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF79C(Ground_GObj* arg) {}

void grRCruise_801FF7A0(Ground_GObj* arg) {}

void grRCruise_801FF7A4(Ground_GObj* gobj)
{
    Ground_GObj* stage_gobj = gobj;
    Ground* gp = stage_gobj->user_data;
    HSD_JObj* jobj = stage_gobj->hsd_obj;
    UnkArchiveStruct* archive;
    DynamicsDesc* data;
    PAD_STACK(8);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(stage_gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 30628, HSD_AObjSetFlags, 3, 0x20000000);
    archive = grDatFiles_801C6324();
    if (archive != NULL &&
        (data = HSD_ArchiveGetPublicAddress(archive->unk0, "dynamicsdata_shipflag"),
         data != NULL))
    {
        grLib_801C9B20(Ground_801C3FA4(stage_gobj, 23), data,
                       &gp->gv.rcruise2.xC4);
    } else {
        gp->gv.rcruise2.xC4.data = NULL;
    }

    jobj = Ground_801C3FA4(stage_gobj, 10);
    if (jobj != NULL) {
        Ground_801C2D0C(0, jobj);
    }
    jobj = Ground_801C3FA4(stage_gobj, 11);
    if (jobj != NULL) {
        Ground_801C2D0C(1, jobj);
    }
    jobj = Ground_801C3FA4(stage_gobj, 12);
    if (jobj != NULL) {
        Ground_801C2D0C(2, jobj);
    }
    jobj = Ground_801C3FA4(stage_gobj, 13);
    if (jobj != NULL) {
        Ground_801C2D0C(3, jobj);
    }
}

bool grRCruise_801FF8DC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF8E4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grLib_801C9B8C(&gp->gv);
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF920(Ground_GObj* arg) {}

void grRCruise_801FF924(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    struct grRCruise_801FF924_GroundVars* vars = (void*) &gp->gv;

    vars->x34[0] = Ground_801C3FA4(gobj, 4);
    vars->x34[1] = Ground_801C3FA4(gobj, 5);
    vars->x34[2] = Ground_801C3FA4(gobj, 6);
    vars->x40 = Ground_801C3FA4(gobj, 7);
    vars->x28[0] = Ground_801C3FA4(gobj, 3);
    HSD_ASSERTMSG(0x2B0, vars->x28[0] != NULL, "gp->u.scroll.int_jobj");
    vars->x28[1] = Ground_801C3FA4(gobj, 2);
    HSD_ASSERTMSG(0x2B2, vars->x28[1] != NULL, "gp->u.scroll.cam_jobj");
    vars->x28[2] = Ground_801C3FA4(gobj, 1);
    HSD_ASSERTMSG(0x2B4, vars->x28[2] != NULL, "gp->u.scroll.ctr_jobj");
    HSD_JObjGetTranslation(vars->x28[2], &vars->x04);
    vars->x10.z = 0.0f;
    vars->x10.y = 0.0f;
    vars->x10.x = 0.0f;
    vars->x1C.z = 0.0f;
    vars->x1C.y = 0.0f;
    vars->x1C.x = 0.0f;
    vars->x00 &= ~0x80;
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 30628, HSD_AObjSetFlags, 3, 0x20000000);
    gobj->render_cb = (GObj_RenderFunc) fn_80201BE0;
}

bool grRCruise_801FFAD4(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FFADC(Ground_GObj* gobj)
{
    static const s32 ids[] = { 2, 1, 5, 6, 4 };
    Ground* gp = gobj->user_data;
    HSD_GObj* hidden_gobj = gp->gv.rcruise2.xEC;
    Vec3 cam_offset;
    Vec3 translate;
    s32 i;

    Stage_UnkSetVec3TCam_Offset(&cam_offset);
    HSD_JObjGetTranslation(GET_JOBJ(hidden_gobj), &translate);
    lbVector_Sub(&translate, &cam_offset);
    HSD_JObjSetTranslate(GET_JOBJ(gobj), &translate);

    for (i = 0; i < 5; i++) {
        HSD_GObj* stage_gobj = Ground_801C2BA4(ids[i]);
        if (stage_gobj != NULL) {
            HSD_JObjSetTranslate(GET_JOBJ(stage_gobj), &translate);
        }
    }
}

void grRCruise_80200070(Ground_GObj* arg) {}

void grRCruise_80200074(Ground_GObj* gobj)
{
    int i;
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(8);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    for (i = 0; i < 3; i++) {
        grAnime_801C8098(gobj, grRc_804D4790[i], 7, 1, 0.0F, 0.0F);
        gp->gv.rcruise.x3C[i].x02 =
            Ground_801C32D4(gp->map_id, grRc_804D4790[i]);
        mpJointSetCb1(gp->gv.rcruise.x3C[i].x02, gobj,
                      (mpLib_Callback) fn_80200460);
        gp->gv.rcruise.x3C[i].x0C = Ground_801C3FA4(gobj, grRc_804D4790[i]);
        gp->gv.rcruise.x3C[i].x08 = 0;
        gp->gv.rcruise.x3C[i].x04 = 0;
        gp->gv.rcruise.x3C[i].x00 = 0;
    }
}

bool grRCruise_8020014C(Ground_GObj* arg)
{
    return false;
}

void grRCruise_80200154(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i;

    for (i = 0; i < 3; i++) {
        struct grRCruise_SubEntry* entry = &gp->gv.rcruise.x3C[i];

        switch (entry->x00) {
        case 0:
            mpJointListAdd(entry->x02);
            grRCruise_80201B60(entry->x0C->child, 1);
            entry->x08 = 0;
            entry->x00 = 1;
            break;
        case 2:
            if (entry->x04 == 0) {
                entry->x08 = 0;
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 0.0f);
                entry->x00 = 3;
            } else if (grAnime_801C83D0(gobj, grRc_804D4790[i], 7) != 0) {
                entry->x08 = 0;
                entry->x00 = 5;
            }
            break;
        case 3:
            if (entry->x08 >= grRc_804D6A10->x0C) {
                entry->x08 = 0;
                entry->pad_01 &= ~0x80;
                entry->x00 = 4;
            }
            entry->x08++;
            break;
        case 4:
            if (entry->x08 % grRc_804D6A10->x14 == 0) {
                entry->pad_01 ^= 0x80;
                if ((entry->pad_01 & 0x80) != 0) {
                    grRCruise_80201B60(entry->x0C->child, 0);
                } else {
                    grRCruise_80201B60(entry->x0C->child, 1);
                }
            }
            if (entry->x08 >= grRc_804D6A10->x10) {
                mpLib_80057BC0(entry->x02);
                grRCruise_80201B60(entry->x0C->child, 0);
                grAnime_801C7BA0(gobj, grRc_804D4790[i], 1, 0.0f);
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 0.0f);
                mpLib_80055E9C(entry->x02);
                mpLib_80057424(entry->x02);
                entry->x00 = 0;
            }
            entry->x08++;
            break;
        case 5:
            if (entry->x08 % grRc_804D6A10->x1C == 0) {
                grRCruise_80201B60(entry->x0C->child, 0);
            } else {
                grRCruise_80201B60(entry->x0C->child, 1);
            }
            if (entry->x08 >= grRc_804D6A10->x18) {
                mpLib_80057BC0(entry->x02);
                grRCruise_80201B60(entry->x0C->child, 0);
                grAnime_801C7BA0(gobj, grRc_804D4790[i], 1, 0.0f);
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 0.0f);
                mpLib_80055E9C(entry->x02);
                mpLib_80057424(entry->x02);
                entry->x00 = 0;
            }
            entry->x08++;
            break;
        }
        entry->x04 = 0;
    }
    Ground_801C2FE0(gobj);
}

void grRCruise_8020045C(Ground_GObj* arg) {}

void fn_80200460(Ground* gp_arg, s32 joint_id, CollData* cd, s32 arg3,
                 mpLib_GroundEnum arg4, f32 arg5)
{
    HSD_GObj* gobj = (HSD_GObj*) gp_arg;
    Ground* gp = HSD_GObjGetUserData(gobj);
    int i;
    PAD_STACK(16);

    if ((s32) cd->x34_flags.b1234 == 1) {
        for (i = 0; i < 3; i++) {
            if (gp->gv.rcruise.x3C[i].x02 == joint_id) {
                u8 state = gp->gv.rcruise.x3C[i].x00;
                if (state == 1 || (u8)(state - 3) <= 1u) {
                    gp->gv.rcruise.x3C[i].x04 = 0;
                    grRCruise_80201B60(gp->gv.rcruise.x3C[i].x0C->child,
                                       1);
                    grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 1.0f);
                    gp->gv.rcruise.x3C[i].x00 = 2;
                }
                gp->gv.rcruise.x3C[i].x08++;
                return;
            }
        }
    }
}

void grRCruise_80200540(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    gp->gv.rcruise.x18 = 0.0F;
    gp->gv.rcruise.x14 = 0.0F;
    gp->gv.rcruise.x1C = 0.0F;
    gp->gv.rcruise.x20 = 0.0F;
    gp->gv.rcruise.x34 = 0;
    gp->gv.rcruise.x30 = 0;
    gp->gv.rcruise.x28 = 0.0F;
    gp->gv.rcruise.x24 = 0.0F;
    gp->gv.rcruise.x38 = 0;
    gp->gv.rcruise.x2C = 0;
}

void grRCruise_80200578(Ground* gp_arg, s32 joint_id, CollData* cd, s32 arg3,
                        mpLib_GroundEnum arg4, f32 arg5)
{
    Point3d pos;
    HSD_GObj* gobj = (HSD_GObj*) gp_arg;
    Ground* gp = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 8);
    f32 dx;
    f32 dy;
    f32 dist;
    PAD_STACK(16);

    if (cd->x34_flags.b1234 == 1 || cd->x34_flags.b1234 == 2 ||
        cd->x34_flags.b1234 == 3)
    {
        if ((f32) arg3 > 1000.0f) {
            arg3 = 1000;
        }
        lb_8000B1CC(jobj, NULL, &pos);
        dx = pos.x - cd->cur_pos.x;
        dy = pos.y - cd->cur_pos.y;
        dist = dx * dx + dy * dy;
        if (dist > 0.0f) {
            dist = sqrtf(dist);
        }
        if (dist > 4.0f) {
            if (pos.x < cd->cur_pos.x) {
                gp->gv.rcruise.x24 += dist * ((f32) arg3 / 1000.0f);
            } else {
                gp->gv.rcruise.x28 += dist * ((f32) arg3 / 1000.0f);
            }
        }
        gp->gv.rcruise.x34++;
    }
}

void grRCruise_8020071C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 8);
    HSD_GObj* gobj5 = Ground_801C2BA4(5);
    HSD_JObj* jobj5 = gobj5 != NULL ? Ground_801C3FA4(gobj5, 8) : NULL;
    f32 abs_rot = gp->gv.rcruise.x14 < 0.0f ? -gp->gv.rcruise.x14
                                            : gp->gv.rcruise.x14;
    f32 wrapped = abs_rot - (360.0f * (s32) (abs_rot / 360.0f));

    switch (gp->gv.rcruise.x2C) {
    case 0:
        if (gp->gv.rcruise.x34 == 0) {
            gp->gv.rcruise.x1C = gp->gv.rcruise.x14 < 0.0f ? 1.0f : -1.0f;
            gp->gv.rcruise.x20 = grRc_804D6A10->x8 * gp->gv.rcruise.x1C;
            if (wrapped <= 0.2f) {
                gp->gv.rcruise.x20 = 0.0f;
                gp->gv.rcruise.x2C = 0;
            }
        } else if (gp->gv.rcruise.x24 < gp->gv.rcruise.x28) {
            gp->gv.rcruise.x1C = 1.0f;
            gp->gv.rcruise.x20 = grRc_804D6A10->x0 *
                                 (gp->gv.rcruise.x28 - gp->gv.rcruise.x24);
            if (gp->gv.rcruise.x20 > grRc_804D6A10->x4) {
                gp->gv.rcruise.x20 = grRc_804D6A10->x4;
            }
        } else {
            gp->gv.rcruise.x1C = -1.0f;
            gp->gv.rcruise.x20 = -grRc_804D6A10->x0 *
                                 (gp->gv.rcruise.x24 - gp->gv.rcruise.x28);
            if (gp->gv.rcruise.x20 < -grRc_804D6A10->x4) {
                gp->gv.rcruise.x20 = -grRc_804D6A10->x4;
            }
        }
        break;
    case 1:
        if (gp->gv.rcruise.x38 == 0) {
            if (gp->gv.rcruise.x34 == 0) {
                gp->gv.rcruise.x1C = gp->gv.rcruise.x14 < 0.0f ? 1.0f : -1.0f;
                gp->gv.rcruise.x20 = grRc_804D6A10->x8 * gp->gv.rcruise.x1C;
                if (wrapped <= 0.2f) {
                    gp->gv.rcruise.x20 = 0.0f;
                    gp->gv.rcruise.x2C = 0;
                }
            } else {
                gp->gv.rcruise.x2C = 0;
            }
        } else {
            gp->gv.rcruise.x38--;
            gp->gv.rcruise.x20 += 0.008f * -gp->gv.rcruise.x1C;
            if (gp->gv.rcruise.x20 < 0.0f ? -gp->gv.rcruise.x20
                                          : gp->gv.rcruise.x20 <= 0.008f)
            {
                gp->gv.rcruise.x20 = 0.0f;
            }
        }
        break;
    }
    gp->gv.rcruise.x14 += gp->gv.rcruise.x20;
    HSD_JObjSetRotationZ(jobj, 0.017453292f * gp->gv.rcruise.x14);
    if (jobj5 != NULL) {
        HSD_JObjSetRotationZ(jobj5, 0.017453292f * gp->gv.rcruise.x14);
    }
    gp->gv.rcruise.x30 = gp->gv.rcruise.x34;
    gp->gv.rcruise.x34 = 0;
    gp->gv.rcruise.x28 = 0.0f;
    gp->gv.rcruise.x24 = 0.0f;
}

void grRCruise_80200B48(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i;

    for (i = 0; i < 17; i++) {
        struct grRCruise_Entry* entry = &gp->gv.rcruise.entries[i];
        entry->x02 = Ground_801C32D4(gp->map_id, grRc_803E4FF0[i]);
        entry->x14 = Ground_801C3FA4(gobj, grRc_803E4FF0[i]);
        entry->x08 = 0;
        entry->x04 = 0;
        entry->x0C = HSD_JObjGetTranslationY(entry->x14);
        entry->x00 = 0;
    }
}

void grRCruise_80200C04(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i;

    for (i = 0; i < 17; i++) {
        struct grRCruise_Entry* entry = &gp->gv.rcruise.entries[i];

        switch (entry->x00) {
        case 1:
            if (entry->x08 == 0) {
                entry->x04 = 0;
                entry->x00 = 0;
            } else if (entry->x04 >= grRc_804D6A10->x20) {
                entry->x00 = 2;
            } else {
                entry->x04++;
            }
            break;
        case 2:
            if ((entry->x04 % grRc_804D6A10->x28) == 0) {
                s32 randi =
                    HSD_Randi((s32) (100.0f * (grRc_804D6A10->x30 -
                                               grRc_804D6A10->x2C)));
                HSD_JObjSetTranslateY(
                    entry->x14,
                    entry->x0C + (grRc_804D6A10->x2C + ((f32) randi / 100.0f)));
            }
            if (entry->x04 >= grRc_804D6A10->x24) {
                entry->x10 = 0.0f;
                entry->x00 = 3;
            }
            entry->x04++;
            break;
        case 3:
            entry->x10 -= grRc_804D6A10->x34;
            if (entry->x10 < -grRc_804D6A10->x38) {
                entry->x10 = -grRc_804D6A10->x38;
            }
            HSD_JObjAddTranslationY(entry->x14, entry->x10);
            if (entry->x14->translate.y <= Stage_GetCamBoundsBottomOffset()) {
                entry->x10 = 0.0f;
                grRCruise_80201B60(entry->x14, 0);
                mpLib_80057BC0(entry->x02);
                entry->x04 = 0;
                entry->x00 = 4;
            }
            break;
        case 4:
            if (entry->x04 >= grRc_804D6A10->x3C) {
                HSD_JObjSetTranslateY(entry->x14, entry->x0C);
                mpLib_80055E9C(entry->x02);
                mpLib_80057424(entry->x02);
                grRCruise_80201B60(entry->x14, 1);
                mpJointListAdd(entry->x02);
                entry->x04 = 0;
                entry->pad_01 &= ~0x80;
                entry->x00 = 5;
            }
            entry->x04++;
            break;
        case 5:
            if ((entry->x04 % grRc_804D6A10->x44) == 0) {
                entry->pad_01 ^= 0x80;
                if ((entry->pad_01 & 0x80) != 0) {
                    grRCruise_80201B60(entry->x14, 0);
                } else {
                    grRCruise_80201B60(entry->x14, 1);
                }
            }
            if (entry->x04 >= grRc_804D6A10->x40) {
                grRCruise_80201B60(entry->x14, 1);
                entry->x04 = 0;
                entry->x00 = 0;
            }
            entry->x04++;
            break;
        }
        entry->x08 = 0;
    }
}

// TODO: is this GET_GROUND? calling it directly didn't work.
inline Ground* grRCruise_802010A4_inline(Ground_GObj* arg0)
{
    return arg0->user_data;
}

void grRCruise_802010A4(Ground_GObj* gobj, s32 id, CollData* coll)
{
    Ground* gp = grRCruise_802010A4_inline(gobj);
    s32 i;

    if ((s32) coll->x34_flags.b1234 != 1) {
        return;
    }

    for (i = 0; i < 17; i++) {
        struct grRCruise_Entry* entry = &gp->gv.rcruise.entries[i];
        if (entry->x02 == id) {
            if (entry->x00 == 0) {
                entry->x04 = 0;
                entry->x00 = 1;
            }
            entry->x08++;
            return;
        }
    }
}

void grRCruise_80201110(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    f32 angle =
        gp->gv.rcruise.x08 +
        atan2f(gp->gv.rcruise.x04->x4.z, gp->gv.rcruise.x04->x4.x);

    if (angle > 1.0471975430846214) {
        angle = 1.0471976f;
    }
    if (angle < -1.0471975430846214) {
        angle = -1.0471976f;
    }
    gp->gv.rcruise.x04->x4.x = cosf(angle);
    gp->gv.rcruise.x04->x4.z = sinf(angle);
    if ((gp->gv.rcruise.x04->unk_angle_int % 30) == 0 && HSD_Randf() > 0.5) {
        gp->gv.rcruise.x08 = -gp->gv.rcruise.x08;
    }
    if ((gp->gv.rcruise.x04->unk_angle_int % 300) == 0) {
        if (gp->gv.rcruise.x0C != 0) {
            gp->gv.rcruise.x0C = 0;
        } else if (HSD_Randf() > 0.5) {
            gp->gv.rcruise.x0C = 1;
        }
    }
    if (gp->gv.rcruise.x0C != 0) {
        gp->gv.rcruise.x04->unk_scale = 0.3 * HSD_Randf() + 0.2;
        return;
    }
    gp->gv.rcruise.x04->unk_scale = 0.2 * HSD_Randf() + 0.1;
}

void grRCruise_80201288(HSD_JObj* jobj, void (*callback)(HSD_DObj*, u32),
                        u32 flags)
{
    if (jobj != NULL) {
        HSD_DObj* dobj = HSD_JObjGetDObj(jobj);
        if (dobj != NULL) {
            callback(dobj, flags);
        }
        if (jobj->child != NULL) {
            grRCruise_80201288(jobj->child, callback, flags);
        }
        if (jobj->next != NULL) {
            grRCruise_80201288(jobj->next, callback, flags);
        }
    }
}

void grRCruise_80201410(Ground_GObj* gobj)
{
    Ground_GObj* stage_gobj = gobj;
    Ground* gp = stage_gobj->user_data;
    struct grRCruise_VanishDesc* desc =
        (struct grRCruise_VanishDesc*) ((u8*) grRc_803E4DA8 + 0x26C);
    u32 i;

    gp->gv.rcruise.vanish = HSD_MemAlloc(0xA0);
    HSD_ASSERTMSG(0x5AD, gp->gv.rcruise.vanish != NULL, "gp->u.map.vanish");
    for (i = 0; i < 20; i++) {
        gp->gv.rcruise.vanish[i].x04 = Ground_801C3FA4(stage_gobj, desc->x00);
        HSD_ASSERTMSG(0x5B3, gp->gv.rcruise.vanish[i].x04 != NULL, "gp->u.map.vanish[i].jobj");
        if (desc->x04 != 0) {
            HSD_GObj* gobj5;
            HSD_GObj* gobj1;
            s16 joint;

            gp->gv.rcruise.vanish[i].x00 = 2;
            joint = desc->x00;
            gobj5 = Ground_801C2BA4(5);
            if (gobj5 != NULL) {
                gobj1 = Ground_801C2BA4(1);
                if (gobj1 != NULL) {
                    HSD_JObj* jobj = Ground_801C3FA4(gobj5, joint);
                    if (jobj != NULL) {
                        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
                    }
                    jobj = Ground_801C3FA4(gobj1, joint);
                    if (jobj != NULL) {
                        grRCruise_80201288(jobj, HSD_DObjSetFlags, 1);
                    }
                }
            }
            mpJointListAdd(desc->x02);
        } else {
            gp->gv.rcruise.vanish[i].x00 = 0;
            grAnime_801C7FF8(stage_gobj, desc->x00, 2, 1, 0.0f, 1.0f);
            mpLib_80057BC0(desc->x02);
        }
        desc++;
    }
}

void grRCruise_80201588(Ground_GObj* gobj)
{
    Point3d pos;
    Ground* gp = gobj->user_data;
    struct grRCruise_VanishDesc* desc =
        (struct grRCruise_VanishDesc*) ((u8*) grRc_803E4DA8 + 0x26C);
    s32 i;

    HSD_ASSERTMSG(0x5D6, gp->gv.rcruise.vanish != NULL, "gp->u.map.vanish");
    for (i = 0; i < 20; i++, desc++) {
        struct grRCruise_VanishEntry* vanish = &gp->gv.rcruise.vanish[i];

        if (desc->x04 != 0) {
            continue;
        }
        switch (vanish->x00) {
        case 0:
            lb_8000B1CC(vanish->x04, NULL, &pos);
            if (Camera_8003118C(&pos, -20.0f) != 0) {
                vanish->x00 = 1;
                grAnime_801C7FF8(gobj, desc->x00, 2, 2, 0.0f, 1.0f);
                mpJointListAdd(desc->x02);
                mpLib_80055E9C(desc->x02);
                mpLib_80057424(desc->x02);
            }
            break;
        case 1:
            if (grAnime_801C83D0(gobj, desc->x00, 2) != 0) {
                HSD_GObj* gobj5;
                HSD_GObj* gobj1;
                HSD_JObj* jobj;

                vanish->x00 = 2;
                gobj5 = Ground_801C2BA4(5);
                if (gobj5 != NULL) {
                    gobj1 = Ground_801C2BA4(1);
                    if (gobj1 != NULL) {
                        jobj = Ground_801C3FA4(gobj5, desc->x00);
                        if (jobj != NULL) {
                            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
                        }
                        jobj = Ground_801C3FA4(gobj1, desc->x00);
                        if (jobj != NULL) {
                            grRCruise_80201288(jobj, HSD_DObjSetFlags, 1);
                        }
                    }
                }
            }
            break;
        case 2:
            lb_8000B1CC(vanish->x04, NULL, &pos);
            if (Camera_8003118C(&pos, -20.0f) == 0) {
                HSD_GObj* gobj5;
                HSD_GObj* gobj1;
                HSD_JObj* jobj;

                vanish->x00 = 3;
                grAnime_801C7FF8(gobj, desc->x00, 2, 3, 0.0f, 1.0f);
                gobj5 = Ground_801C2BA4(5);
                if (gobj5 != NULL) {
                    gobj1 = Ground_801C2BA4(1);
                    if (gobj1 != NULL) {
                        jobj = Ground_801C3FA4(gobj5, desc->x00);
                        if (jobj != NULL) {
                            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                        }
                        jobj = Ground_801C3FA4(gobj1, desc->x00);
                        if (jobj != NULL) {
                            grRCruise_80201288(jobj, HSD_DObjClearFlags, 1);
                        }
                    }
                }
            }
            break;
        case 3:
            if (grAnime_801C83D0(gobj, desc->x00, 2) != 0) {
                s32 j;
                bool done = true;

                vanish->x00 = 0;
                grAnime_801C7FF8(gobj, desc->x00, 2, 1, 0.0f, 1.0f);
                for (j = 0; j < 20; j++) {
                    if (gp->gv.rcruise.vanish[j].x00 != 0 &&
                        ((struct grRCruise_VanishDesc*) ((u8*) grRc_803E4DA8 +
                                                         0x26C))[j]
                                .x02 == desc->x02)
                    {
                        done = false;
                        break;
                    }
                }
                if (done) {
                    mpLib_80057BC0(desc->x02);
                }
            }
            break;
        }
    }
}

void grRCruise_80201918(Vec3* vec)
{
    HSD_GObj* gobj = Ground_801C2BA4(3);
    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        if (gp != NULL) {
            *vec = *(Vec3*) ((u8*) gp + 0xE0);
            return;
        }
    }
    vec->x = vec->y = vec->z = 0.0f;
}

bool grRCruise_80201988(s32 line)
{
    s32 joint;
    s32 ok0 = 1;
    s32 ok1 = 1;
    s32 ok2 = 1;
    s32 ok3 = 1;
    s32 ok4 = 1;
    s32 ok5 = 1;
    s32 ok6 = 1;
    s32 ok7 = 1;
    s32 ok8 = 1;
    s32 ok9 = 1;
    s32 ok10 = 1;
    s32 ok11 = 1;
    s32 ok12 = 1;
    s32 ok13 = 1;
    s32 ok14 = 1;
    s32 ok15 = 1;

    if (stage_info.internal_stage_id != RCRUISE || line == -1) {
        return false;
    }
    joint = mpJointFromLine(line);
    if (joint != 0x1B && joint != 0x24) {
        ok15 = 0;
    }
    if (ok15 == 0 && joint != 0x25) {
        ok14 = 0;
    }
    if (ok14 == 0 && joint != 0x26) {
        ok13 = 0;
    }
    if (ok13 == 0 && joint != 0x27) {
        ok12 = 0;
    }
    if (ok12 == 0 && joint != 0x28) {
        ok11 = 0;
    }
    if (ok11 == 0 && joint != 0x29) {
        ok10 = 0;
    }
    if (ok10 == 0 && joint != 0x2A) {
        ok9 = 0;
    }
    if (ok9 == 0 && joint != 0x2B) {
        ok8 = 0;
    }
    if (ok8 == 0 && joint != 0x1C) {
        ok7 = 0;
    }
    if (ok7 == 0 && joint != 0x1D) {
        ok6 = 0;
    }
    if (ok6 == 0 && joint != 0x1E) {
        ok5 = 0;
    }
    if (ok5 == 0 && joint != 0x1F) {
        ok4 = 0;
    }
    if (ok4 == 0 && joint != 0x20) {
        ok3 = 0;
    }
    if (ok3 == 0 && joint != 0x21) {
        ok2 = 0;
    }
    if (ok2 == 0 && joint != 0x22) {
        ok1 = 0;
    }
    if (ok1 == 0 && joint != 0x23) {
        ok0 = 0;
    }
    return ok0 != 0;
}

void grRCruise_80201B60(HSD_JObj* jobj, s32 arg1)
{
    HSD_DObj* dobj;
    HSD_DObj* next;
    PAD_STACK(8);

    dobj = HSD_JObjGetDObj(jobj);
    while (dobj != NULL) {
        if (arg1 != 0) {
            HSD_DObjClearFlags(dobj, 1U);
        } else {
            HSD_DObjSetFlags(dobj, 1U);
        }
        if (dobj != NULL) {
            next = dobj->next;
        } else {
            next = NULL;
        }
        dobj = next;
    }
}

void fn_80201BE0(HSD_GObj* gobj, s32 pass)
{
    if (gm_801A45E8(1) != 0 || gm_801A45E8(2) != 0 || Camera_8003010C() != 0) {
        return;
    }
    grDisplay_801C5DB0(gobj, pass);
}

DynamicsDesc* grRCruise_80201C50(enum_t arg)
{
    return false;
}

bool grRCruise_80201C58(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
