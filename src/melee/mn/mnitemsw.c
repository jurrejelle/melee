#include "mnitemsw.h"

#include "mn/inlines.h"
#include "mn/mnmain.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

#include <melee/lb/lb_00F9.h>
#include <melee/lb/lblanguage.h>
#include <melee/sc/types.h>

extern StaticModelDesc MenMainCursorIs_Top;

struct MnItemSwTable {
    /* 0x00 */ f32 x00[4][3];
    /* 0x30 */ f32 x30[18];
    /* 0x78 */ f32 items[32];
    /* 0xF8 */ u8 item_order[32];
};

static struct MnItemSwTable mnItemSw_803ED340 = {
    /* x00 */
    {
        { 0.0f, 9.0f, -0.1f },
        { 0.0f, 0.0f, -0.1f },
        { 0.0f, 0.0f, -0.1f },
        { 0.0f, 0.0f, -0.1f },
    },
    /* x30 */
    {
        0.0f, 10.0f, -0.1f, 0.0f, 199.0f, 0.0f, 10.0f, 11.0f,
        8.0f, 9.0f, 6.0f, 7.0f, 4.0f, 5.0f, 2.0f, 3.0f,
        0.0f, 1.0f,
    },
    /* items */
    {
        0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f,
        25.0f, 24.0f, 26.0f, 27.0f, 29.0f, 28.0f, 30.0f, 31.0f,
    },
    /* item_order */
    {
        0x05, 0x12, 0x0A, 0x1E, 0x0D, 0x18, 0x03, 0x0E,
        0x17, 0x1B, 0x01, 0x09, 0x08, 0x07, 0x15, 0x04,
        0x06, 0x02, 0x0F, 0x00, 0x11, 0x0B, 0x1F, 0x1A,
        0x14, 0x19, 0x10, 0x16, 0x13, 0x1D, 0x0C, 0x00,
    },
};

static f32 mnItemSw_804D4BA0[2] = { 0.0f, 1.0f };

#pragma dont_inline on
s32 mnItemSw_80233A98(s32 arg0)
{
    switch (arg0) {
    case 19:
        if (lbLang_IsSettingJP()) {
            return (s32) mnItemSw_803ED340.items[arg0];
        }
        return 0x27;
    case 17:
        if (lbLang_IsSettingJP()) {
            return (s32) mnItemSw_803ED340.items[arg0];
        }
        return 0x28;
    case 18:
    default:
        return (s32) mnItemSw_803ED340.items[arg0];
    }
}
#pragma dont_inline reset

HSD_JObj* mnItemSw_8023405C(MnItemSwData* data, u8 idx)
{
    HSD_JObj* cur;
    u8 i;

    if (idx >= 16) {
        cur = HSD_JObjGetChild(data->jobjs[6]);
        for (i = 16; i < idx; i++) {
            cur = HSD_JObjGetNext(cur);
        }
    } else {
        if (data->jobjs[4] == NULL) {
            cur = NULL;
        } else {
            cur = data->jobjs[4]->child;
        }
        for (i = 0; i < idx; i++) {
            cur = HSD_JObjGetNext(cur);
        }
    }
    return cur;
}

HSD_JObj* mnItemSw_80235020(u8 arg0, MnItemSwData* arg1)
{
    HSD_JObj* sp14;
    HSD_JObj* sp10;
    u8 hovered;
    u8 item_val;
    HSD_JObj* jobj;

    hovered = (u8) mn_804A04F0.hovered_selection;
    jobj = HSD_JObjLoadJoint(MenMainCursorIs_Top.joint);
    HSD_JObjAddAnimAll(jobj, MenMainCursorIs_Top.animjoint,
                       MenMainCursorIs_Top.matanim_joint,
                       MenMainCursorIs_Top.shapeanim_joint);
    lb_80011E24(jobj, &sp14, 3, -1);
    HSD_JObjReqAnimAll(sp14,
                       (f32) mnItemSw_80233A98(
                           (s32) mnItemSw_803ED340.item_order[arg0]));
    HSD_JObjAnimAll(sp14);
    if (arg0 == hovered) {
        HSD_JObjReqAnimAll(sp14, mnItemSw_803ED340.x30[1]);
    } else {
        HSD_JObjReqAnimAll(sp14, mnItemSw_803ED340.x30[0]);
    }
    mn_8022F3D8(sp14, 1, TOBJ_MASK);
    HSD_JObjAnimAll(sp14);
    item_val = arg1->items[arg0];
    lb_80011E24(jobj, &sp10, 2, -1);
    HSD_JObjReqAnimAll(sp10, mnItemSw_804D4BA0[item_val]);
    HSD_JObjAnimAll(sp10);
    lb_80011E24(jobj, &sp14, 8, -1);
    if (arg0 == hovered) {
        HSD_JObjReqAnimAll(sp14, mnItemSw_803ED340.x30[3]);
        HSD_JObjAnimAll(sp14);
    } else {
        HSD_JObjSetFlagsAll(sp14, 0x10);
    }
    return jobj;
}

void mnItemSw_802358C0(void)
{
    HSD_GObjProc* proc;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x10;
    mn_804A04F0.hovered_selection = 0;
    mnItemSw_804D6BEC = 1;
    mnItemSw_802351A0(1);

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_80233E10, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
