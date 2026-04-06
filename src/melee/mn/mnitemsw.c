#include "mnitemsw.h"

#include "mn/inlines.h"
#include "mn/mnmain.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

#include <melee/lb/lblanguage.h>

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
