#include "gryorster.h"

#include <platform.h>

#include "forward.h"

#include "ft/ftlib.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

static s32 grYt_803B82A8[] = { 0xA, 0xB, 0xC, 0xD, 0xE,
                               0xF, 0x10, 0x11, 0x12, 0x0 };

StageCallbacks grYt_803E5198[2] = {
    { grYorster_80202124, grYorster_80202150, grYorster_80202158,
      grYorster_8020215C, NULL },
    { grYorster_802021AC, grYorster_8020224C, grYorster_80202254,
      grYorster_802022A0, 0xC0000000 }
};

StageData grYt_803E51CC = {
    YORSTER,
    grYt_803E5198,
    "/GrYt.dat",
    grYorster_80201FA4,
    grYorster_80201FA0,
    grYorster_8020200C,
    grYorster_80202010,
    grYorster_80202034,
    grYorster_80202B5C,
    grYorster_80202B64,
    (1 << 0),
    NULL,
    0,
};

typedef struct YorsterParams {
    f32 x00;
    f32 x04;
    f32 x08;
    f32 x0C;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
} YorsterParams;

typedef struct grYt_804D6A20_t {
    YorsterParams* x0;
    u8 pad_04[4];
} grYt_804D6A20_t;
grYt_804D6A20_t grYt_804D6A20;

void grYorster_80201FA0(bool unused)
{
    return;
}

void grYorster_80201FA4(void)
{
    grYt_804D6A20.x0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grYorster_8020203C(0);
    grYorster_8020203C(1);

    Ground_801C39C0();
    Ground_801C3BB4();
}

void grYorster_8020200C(void)
{
    return;
}

void grYorster_80202010(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grYorster_80202034(void)
{
    return false;
}

HSD_GObj* grYorster_8020203C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grYt_803E5198[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 221, gobj_id);
    }

    return gobj;
}

void grYorster_80202124(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grYorster_80202150(Ground_GObj* gobj)
{
    return false;
}

void grYorster_80202158(Ground_GObj* gobj)
{
    return;
}

void grYorster_8020215C(Ground_GObj* gobj)
{
    return;
}

void grYorster_80202160(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grYorster_802022A4(gobj);
    Ground_801C2FE0(gobj);
    mpLib_80058560();
    gp->gv.yorster.xC4 = 0;
}

void grYorster_802021AC(Ground_GObj* gobj)
{
    int _[2];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(GET_JOBJ(gobj), gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 4);
    grAnime_801C7FF8(gobj, 23, 7, 3, 0.0f, 1.0f);
    grAnime_801C7FF8(gobj, 26, 7, 3, 0.0f, 1.0f);
    Ground_801C10B8(gobj, grYorster_80202160);
    gp->gv.yorster.xC4 = 1;
}

bool grYorster_8020224C(Ground_GObj* gobj)
{
    return false;
}

void grYorster_80202254(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.yorster.xC4 == 0) {
        grYorster_8020266C(gobj);
    }
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grYorster_802022A0(HSD_GObj* gobj) {}

void grYorster_802022A4(HSD_GObj* gobj) {}

void grYorster_80202428(HSD_GObj* item_gobj, Ground* gp, Vec3* pos,
                        HSD_GObj* fighter_gobj, f32 value)
{
    Ground* ground = gp;
    HSD_GObj* fighter = fighter_gobj;
    int i;

    if (ftLib_80086960(fighter)) {
        ftLib_80086A4C(fighter, (f32) grYt_804D6A20.x0->x14);
    }

    for (i = 0; i < 9; i++) {
        if (ground->gv.yorster.elements[i].x1C == item_gobj) {
            ground->gv.yorster.elements[i].x04 += value;
            break;
        }
    }
}

void grYorster_802024F0(Ground* gp, s32 joint_id, CollData* coll_data,
                        s32 unused, mpLib_GroundEnum ground_kind, f32 value)
{
    HSD_GObj* gobj = coll_data->x0_gobj;
    s32 env = coll_data->x34_flags.b1234;
    s32 i;
    PAD_STACK(8);

    if ((env == 1 && !ftLib_800873F4(gobj)) || env == 2 || env == 3) {
        if (env == 1) {
            Vec3 pos;

            ftLib_80086BEC(gobj, &pos);
            value = pos.y;
            if (value >= grYt_804D6A20.x0->x00) {
                ftLib_80086A4C(gobj, (f32) grYt_804D6A20.x0->x10);
            }
        } else if (value >= grYt_804D6A20.x0->x00) {
            it_8026B718(gobj, (f32) grYt_804D6A20.x0->x10);
        }

        for (i = 0; i < 9; i++) {
            if (joint_id ==
                Ground_801C32D4(gp->map_id, gp->gv.yorster.elements[i].x14))
            {
                gp->gv.yorster.elements[i].x08 += value;
                break;
            }
        }
    }
}

/// #grYorster_8020266C

DynamicsDesc* grYorster_80202B5C(enum_t unused)
{
    return NULL;
}

bool grYorster_80202B64(Vec3* a, int _, HSD_JObj* joint)
{
    return true;
}
