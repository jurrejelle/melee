#include "mnmainrule.h"

#include "mnmain.h"

#include "gm/gm_1A3F.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/sc/types.h>

extern HSD_FogDesc* MenMain_fog;
extern UNK_T MenMain_lights;
extern HSD_CObjDesc* MenMain_cam;
extern StaticModelDesc MenMainBack_Top;
extern StaticModelDesc MenMainPanel_Top;
extern StaticModelDesc MenMainConTop_Top;
extern StaticModelDesc MenMainCursor_Top;
extern StaticModelDesc MenMainConRl_Top;
extern StaticModelDesc MenMainCursorRl_Top;
extern StaticModelDesc MenMainNmRl_Top;
extern StaticModelDesc MenMainCursorTr01_Top;
extern StaticModelDesc MenMainCursorTr02_Top;
extern StaticModelDesc MenMainCursorTr03_Top;
extern StaticModelDesc MenMainCursorTr04_Top;
extern StaticModelDesc MenMainCursorRl01_Top;
extern StaticModelDesc MenMainCursorRl02_Top;
extern StaticModelDesc MenMainCursorRl03_Top;
extern StaticModelDesc MenMainCursorRl04_Top;
extern StaticModelDesc MenMainCursorRl05_Top;
extern StaticModelDesc MenMainConIs_Top;
extern StaticModelDesc MenMainCursorIs_Top;
extern StaticModelDesc MenMainConSs_Top;
extern StaticModelDesc MenMainCursorSs_Top;

struct mn_803EC818_t {
    u8 x0;
    u8 pad_1[4];
};

struct mn_8022FB88_arg1_t {
    u8 pad_0[2];
    u8 x2;
    u8 x3;
    u8 pad_4[5];
    u8 x9;
    u8 pad_A[0x58 - 0x0A];
    HSD_JObj* x58[10];
    u8 pad_80[0xA8 - 0x80];
    struct mn_8022FEC8_jobj_ref_t* xA8;
    struct mn_8022FEC8_jobj_ref_t* xAC;
};

struct mn_8022FEC8_jobj_ref_t {
    u8 pad_0[0x10];
    HSD_JObj* x10;
};

typedef union {
    s32 packed;
    u8 idx[4];
} JObjIndices;

AnimLoopSettings mn_803EC734[5] = {
    { 0.0f, 3.0f, -0.1f },
    { 20.0f, 23.0f, -0.1f },
    { 40.0f, 43.0f, -0.1f },
    { 60.0f, 63.0f, -0.1f },
    { 80.0f, 83.0f, -0.1f },
};

AnimLoopSettings mn_803EC770[9] = {
    { 100.0f, 103.0f, -0.1f },
    { 120.0f, 123.0f, -0.1f },
    { 140.0f, 143.0f, -0.1f },
    { 160.0f, 163.0f, -0.1f },
    { 180.0f, 183.0f, -0.1f },
    { 30.0f, 49.0f, -0.1f },
    { 70.0f, 89.0f, -0.1f },
    { 90.0f, 109.0f, -0.1f },
    { 50.0f, 69.0f, -0.1f },
};

extern f32 mn_804D4B90;
extern f32 mn_804D6BD8;
extern s32 mn_804DBDFC;
extern f32 mn_804DBE00;
extern HSD_GObj* mn_804D6BD0;
extern u16 mn_804DBE04;
extern s32 mn_804DBE08;
extern u8 mn_804DBE0C;
extern u8 mn_803EC600[];

/// #fn_8022F538

void mn_8022FB88(u8 arg0, void* arg1)
{
    struct mn_8022FB88_arg1_t* data = arg1;
    s32 sp10;
    s32 sp14;
    HSD_JObj* temp_r27;
    HSD_JObj* temp_r28;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r29_2;
    HSD_JObj* temp_r29_3;
    HSD_JObj* temp_r31;
    s32 var_r27;
    s32 var_r28;
    u8* var_r29;
    u8* var_r29_2;
    HSD_JObj** temp_r27_2;

    sp14 = mn_804DBDFC;
    if (arg0 == 0) {
        var_r27 = 0;
        var_r29 = (u8*) &sp14;
        do {
            HSD_JObjSetFlagsAll(data->x58[*var_r29], 0x10U);
            var_r27 += 1;
            var_r29 += 1;
        } while (var_r27 < 4);
        temp_r27 = data->x58[4];
        HSD_JObjReqAnimAll(temp_r27, mn_804D4B90);
        HSD_JObjAnimAll(temp_r27);
        return;
    }
    var_r28 = 0;
    var_r29_2 = (u8*) &sp14;
    do {
        HSD_JObjClearFlagsAll(data->x58[*var_r29_2], 0x10U);
        var_r28 += 1;
        var_r29_2 += 1;
    } while (var_r28 < 4);
    temp_r28 = data->x58[4];
    HSD_JObjReqAnimAll(temp_r28, mn_804D6BD8);
    HSD_JObjAnimAll(temp_r28);
    temp_r27_2 = data->x58;
    temp_r31 = data->x58[2];
    HSD_JObjReqAnimAll(temp_r31, (f32) (u8) (arg0 / 10));
    HSD_JObjAnimAll(temp_r31);
    temp_r29 = temp_r27_2[3];
    HSD_JObjReqAnimAll(temp_r29, (f32) (u8) (arg0 % 10));
    HSD_JObjAnimAll(temp_r29);
    temp_r29_2 = temp_r27_2[5];
    HSD_JObjReqAnimAll(temp_r29_2, mn_804DBE00);
    HSD_JObjAnimAll(temp_r29_2);
    temp_r29_3 = temp_r27_2[6];
    HSD_JObjReqAnimAll(temp_r29_3, mn_804DBE00);
    HSD_JObjAnimAll(temp_r29_3);
}

/// #mn_8022FD18
void mn_8022FD18(u8 arg0)
{
    u16 sp14;
    u8 sp10;
    s32 spC;
    HSD_JObj* jobj;
    struct mn_8022FB88_arg1_t* data;
    s32 i;
    u8* ptr;
    u8 val;

    data = mn_804D6BD0->user_data;
    spC = mn_804DBE08;
    sp14 = mn_804DBE04;
    sp10 = mn_804DBE0C;
    if (arg0 != 0) {
        i = 0;
        ptr = (u8*) &sp14;
        do {
            HSD_JObjSetFlagsAll(data->x58[*ptr], 0x10U);
            i++;
            ptr++;
        } while (i < 2);
        i = 0;
        ptr = (u8*) &spC;
        do {
            HSD_JObjClearFlagsAll(data->x58[*ptr], 0x10U);
            i++;
            ptr++;
        } while (i < 5);
        mn_8022FB88(data->x3, data);
        return;
    }
    i = 0;
    ptr = (u8*) &sp14;
    do {
        HSD_JObjClearFlagsAll(data->x58[*ptr], 0x10U);
        i++;
        ptr++;
    } while (i < 2);
    i = 0;
    ptr = (u8*) &spC;
    do {
        HSD_JObjSetFlagsAll(data->x58[*ptr], 0x10U);
        i++;
        ptr++;
    } while (i < 5);
    val = data->x9;
    jobj = data->x58[7];
    HSD_JObjReqAnimAll(jobj, (f32) (u8) (data->x9 / 10));
    HSD_JObjAnimAll(jobj);
    jobj = data->x58[8];
    HSD_JObjReqAnimAll(jobj, (f32) (u8) (val % 10));
    HSD_JObjAnimAll(jobj);
}

/// #mn_8022FEC8
void mn_8022FEC8(HSD_GObj* arg0, HSD_JObj* arg1, u8 arg2, u8 arg3)
{
    HSD_JObj* temp_r28;
    HSD_JObj* temp_r28_2;
    HSD_JObj* var_r28;
    HSD_JObj* var_r28_2;
    f32* var_r8;
    struct mn_8022FB88_arg1_t* temp_r31;
    HSD_JObj** temp_r31_2;
    struct mn_8022FEC8_jobj_ref_t* temp_r3;
    struct mn_8022FEC8_jobj_ref_t* temp_r3_2;
    u8* base;

    temp_r31 = arg0->user_data;
    base = mn_803EC600;
    switch (arg2) {
    case 1:
        if (((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 != 1) {
            mn_8022FB88(arg3, temp_r31);
            return;
        }
        temp_r31_2 = temp_r31->x58;
        temp_r28 = temp_r31_2[7];
        HSD_JObjReqAnimAll(temp_r28, (f32) (u8) (arg3 / 10));
        HSD_JObjAnimAll(temp_r28);
        temp_r28_2 = temp_r31_2[8];
        HSD_JObjReqAnimAll(temp_r28_2, (f32) (u8) (arg3 % 10));
        HSD_JObjAnimAll(temp_r28_2);
        return;
    case 3:
        temp_r3 = temp_r31->xA8;
        if (temp_r3 == NULL) {
            var_r28 = NULL;
        } else {
            var_r28 = temp_r3->x10;
        }
        HSD_JObjReqAnimAll(var_r28, (f32) (u8) (arg3 / 10));
        HSD_JObjAnimAll(var_r28);
        temp_r3_2 = temp_r31->xAC;
        if (temp_r3_2 == NULL) {
            var_r28_2 = NULL;
        } else {
            var_r28_2 = temp_r3_2->x10;
        }
        HSD_JObjReqAnimAll(var_r28_2, (f32) (u8) (arg3 % 10));
        HSD_JObjAnimAll(var_r28_2);
        return;
    case 0:
    case 2:
    case 4:
        break;
    default:
        return;
    }

    var_r8 = NULL;
    if ((mn_804A04F0.buttons & 4) != 0) {
        var_r8 =
            (f32*) (base + 0x170 + (0xC * (base[0x1DD + (arg2 << 1)] - arg3)));
        HSD_JObjReqAnimAll(arg1, *var_r8);
    } else {
        if (arg3 == 0) {
            var_r8 = (f32*) (base + 0x134 + (0xC * base[0x1DD + (arg2 << 1)]));
        } else {
            var_r8 = (f32*) (base + 0x134 + (0xC * (arg3 - 1)));
        }
        HSD_JObjReqAnimAll(arg1, *var_r8);
    }
    HSD_JObjAnimAll(arg1);
}

void mn_80230198(HSD_GObj* gobj, HSD_JObj* jobj, u8 arg2)
{
    AnimLoopSettings* p734;
    AnimLoopSettings* settings;
    AnimLoopSettings* p770;
    f32 frame;
    s32 i;
    s32 option;

    PAD_STACK(8);

    option = arg2;

    if (option != 3) {
        if (option < 3) {
            if (option != 1) {
                if (option < 1 && option < 0) {
                    return;
                }
                goto find;
            }
            return;
        }
        if (option < 7 && option < 5) {
        find:
            frame = mn_8022F298(jobj);
            p770 = mn_803EC770;
            p734 = mn_803EC734;

            for (i = 5; i != 0; i--) {
                settings = p770;
                if (p770->start_frame <= frame && frame <= p770->end_frame) {
                    break;
                }
                settings = p734;
                if (p734->start_frame <= frame && frame <= p734->end_frame) {
                    break;
                }
                p770++;
                p734++;
            }

            mn_8022ED6C(jobj, settings);
        }
    }
}

/// #mn_80230274
extern MenuKindData mn_803EB6B0[];
extern AnimLoopSettings mn_804D4B88;

extern u8 mn_804D4B96;
extern struct mn_803EC818_t mn_803EC818[];
extern f32 mn_804DBE18;
extern f32 mn_804DBE1C;
extern f32 mn_804DBE20;
extern f32 mn_804DBE24;
extern f32 mn_804DBE28;
extern f32 mn_804DBE2C;

void mn_80230274(HSD_GObj* arg0, int arg1, int arg2)
{
    HSD_JObj* roots[17];
    u16 indices[17];
    AnimLoopSettings* settings;
    HSD_JObj* jobj;
    HSD_JObj* option_roots[8];
    s32 i;
    s32 j;
    s32 visible;
    u8 count;
    u8 selected;
    u8 hovered;
    u8* data8;
    struct mn_802307F8_t* data;

    data = arg0->user_data;
    data8 = arg0->user_data;
    count = mn_803EB6B0[15].selection_count;
    for (i = 0; i < 0x11; i++) {
        indices[i] = i;
    }

    for (i = 0; i < count; i++) {
        if (gm_801A4310() == 0x1B && (u8) i == 4) {
            continue;
        }
        visible = 0;
        for (j = 0; j < i; j++) {
            if (!(gm_801A4310() == 0x1B && (u8) j == 4)) {
                visible++;
            }
        }
        if (data->xC[indices[visible]] == NULL) {
            option_roots[i] = NULL;
        } else {
            option_roots[i] =
                ((struct mn_8022FEC8_jobj_ref_t*) data->xC[indices[visible]])
                    ->x10;
        }
    }

    if (arg1 != 0) {
        selected = data->x1;
        lb_8001204C(option_roots[selected], roots, indices, 0x11);
        HSD_JObjSetFlagsAll(roots[16], 0x10U);
        HSD_JObjSetFlagsAll(roots[13], 0x10U);
        jobj = roots[2];
        if ((u8) (selected - 5) <= 1) {
            HSD_JObjReqAnimAll(jobj, *(f32*) (mn_803EC600 + 0x78));
        } else {
            HSD_JObjReqAnimAll(jobj, *(f32*) (mn_803EC600 + 0x60));
        }
        HSD_JObjAnimAll(jobj);
        jobj = roots[7];
        if (selected == 1 &&
            ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
        {
            HSD_JObjReqAnim(jobj, mn_804D4B88.start_frame);
        } else {
            HSD_JObjReqAnim(jobj, *(f32*) (mn_803EC600 + 0x10 + selected * 8));
        }
        HSD_JObjAnim(jobj);
        HSD_JObjSetFlagsAll(roots[8], 0x10U);

        hovered = mn_804A04F0.hovered_selection;
        lb_8001204C(option_roots[hovered], roots, indices, 0x11);
        HSD_JObjClearFlagsAll(roots[16], 0x10U);
        HSD_JObjReqAnimAll(roots[16], *(f32*) (mn_803EC600 + 0x48));
        if (hovered != 5 && hovered != 6) {
            HSD_JObjClearFlagsAll(roots[13], 0x10U);
            HSD_JObjReqAnimAll(roots[13], *(f32*) (mn_803EC600 + 0x54));
            HSD_JObjReqAnimAll(roots[2], *(f32*) (mn_803EC600 + 0x6C));
            HSD_JObjAnimAll(roots[2]);
        } else {
            HSD_JObjReqAnimAll(roots[2], *(f32*) (mn_803EC600 + 0x84));
            HSD_JObjAnimAll(roots[2]);
        }
        if (hovered == 1 &&
            ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
        {
            HSD_JObjReqAnim(roots[7], mn_804D4B88.end_frame);
        } else {
            HSD_JObjReqAnim(roots[7], *(f32*) (mn_803EC600 + 0x14 + hovered * 8));
        }
        HSD_JObjAnim(roots[7]);
        if ((u8) (hovered - 5) <= 1) {
            HSD_JObjClearFlagsAll(roots[8], 0x10U);
            HSD_JObjReqAnimAll(roots[8], *(f32*) (mn_803EC600 + 0x90));
            HSD_JObjAnimAll(roots[8]);
        }
    }

    if (arg2 != 0) {
        mn_8022FEC8(arg0, data->x34[mn_804A04F0.hovered_selection].x0,
                    mn_804A04F0.hovered_selection,
                    mn_804A04F0.confirmed_selection);
    }

    for (i = 0; i < count; i++) {
        u8 focus;

        if (gm_801A4310() == 0x1B && (u8) i == 4) {
            continue;
        }
        lb_8001204C(option_roots[i], roots, indices, 0x11);
        if (arg1 != 0) {
            focus = mn_804A04F0.hovered_selection;
        } else {
            focus = data->x1;
        }
        if (i == focus) {
            mn_8022ED6C(roots[16], (AnimLoopSettings*) (mn_803EC600 + 0x48));
        }
        if (i == focus && i != 5 && i != 6) {
            mn_8022ED6C(roots[13], (AnimLoopSettings*) (mn_803EC600 + 0x54));
        }
        if ((u32) (i - 5) <= 1) {
            settings = (AnimLoopSettings*) (mn_803EC600 +
                                            (((u8) (focus == i)) * 0xC) +
                                            0x78);
        } else {
            settings = (AnimLoopSettings*) (mn_803EC600 +
                                            (((u8) (focus == i)) * 0xC) +
                                            0x60);
        }
        mn_8022ED6C(roots[2], settings);
        mn_8022ED6C(roots[8], (AnimLoopSettings*) (mn_803EC600 + 0x90));
        mn_80230198(arg0, data->x34[i].x0, i);
        if (i == 1 && arg2 != 0 && focus == 0) {
            if (mn_804A04F0.confirmed_selection == 1) {
                HSD_JObjReqAnim(roots[7], mn_804D4B88.start_frame);
            } else {
                HSD_JObjReqAnim(roots[7], *(f32*) (mn_803EC600 + 0x18));
            }
            HSD_JObjAnim(roots[7]);
            mn_8022FD18((u8) (mn_804A04F0.confirmed_selection != 1));
        }
    }
}

void mn_802307F8(struct mn_802307F8_t* arg0, s32 arg1, s32 arg2)
{
    HSD_Text* temp_r3_2;
    u8 var_r30;

    if (arg0->text != NULL) {
        HSD_SisLib_803A5CC4(arg0->text);
        arg0->text = NULL;
    }
    if ((arg1 == 1) && ((u8) arg0->x2 == 1)) {
        var_r30 = mn_804D4B96;
    } else if ((arg1 == 1) || (arg1 == 3) || ((u32) (arg1 - 5) <= 1U)) {
        var_r30 = mn_803EC818[arg1].x0;
    } else {
        var_r30 = *(&mn_803EC818[arg1].x0 + arg2);
    }
    temp_r3_2 = HSD_SisLib_803A5ACC(0, 1, mn_804DBE18, mn_804DBE1C,
                                    mn_804DBE20, mn_804DBE24, mn_804DBE28);
    arg0->text = temp_r3_2;
    temp_r3_2->font_size.y = temp_r3_2->font_size.x = mn_804DBE2C;
    HSD_SisLib_803A6368(temp_r3_2, var_r30);
}

void mn_802308F0(HSD_GObj* gobj, int arg1, int arg2)
{
    struct mn_802307F8_t* data = HSD_GObjGetUserData(gobj);
    u16 sel;
    u8 kind;

    if (arg1 != 0) {
        sel = mn_804A04F0.hovered_selection;
    } else {
        sel = data->x1;
    }
    kind = sel;

    switch (data->xA) {
    case 2:
    case 4:
        if (data->text != NULL) {
            HSD_SisLib_803A5CC4(data->text);
            data->text = NULL;
        }
        break;
    case 1:
    case 3:
        if (data->text == NULL) {
            mn_802307F8((struct mn_802307F8_t*) data, kind,
                        mn_804A04F0.confirmed_selection);
        }
        break;
    case 0:
        if (arg1 != 0 ||
            (arg2 != 0 && (kind == 0 || kind == 2 || kind == 4)))
        {
            mn_802307F8((struct mn_802307F8_t*) data, kind,
                        mn_804A04F0.confirmed_selection);
        }
        break;
    case 5:
        break;
    }
}

/// #fn_802309F0
void fn_802309F0(HSD_GObj* arg0)
{
    GameRules* rules;
    HSD_JObj* jobj;
    f32* anim;
    u8* base;
    u8* ptr;
    s32 update_menu;
    s32 update_selection;
    s32 update_value;
    u8 state;
    struct mn_802307F8_t* data;

    update_menu = 0;
    update_selection = 0;
    update_value = 0;
    data = arg0->user_data;
    base = mn_803EC600;
    if ((data->xA == 0 || data->xA == 1 || data->xA == 3) &&
        data->x0 != mn_804A04F0.cur_menu)
    {
        if ((u8) (mn_804A04F0.cur_menu - 0xF) <= 1) {
            data->xA = 4;
        } else {
            data->xA = 2;
        }
        state = data->xA;
        jobj = data->xC[2];
        switch (state) {
        case 1:
            anim = (f32*) (base + 0x1AC);
            break;
        case 2:
            anim = (f32*) (base + 0x1C4);
            break;
        case 3:
            anim = (f32*) (base + 0x1B8);
            break;
        case 4:
            anim = (f32*) (base + 0x1D0);
            break;
        default:
            anim = NULL;
            break;
        }
        HSD_JObjReqAnim(jobj, anim[0]);
        HSD_JObjAnim(jobj);
        if (data->xA == 0 || data->xA == 1 || data->xA == 3) {
            update_menu = 1;
            update_selection = 1;
            update_value = 1;
        }
    }

    state = data->xA;
    if (state != 0) {
        jobj = data->xC[2];
        switch (state) {
        case 1:
            anim = (f32*) (base + 0x1AC);
            break;
        case 2:
            anim = (f32*) (base + 0x1C4);
            break;
        case 3:
            anim = (f32*) (base + 0x1B8);
            break;
        case 4:
            anim = (f32*) (base + 0x1D0);
            break;
        default:
            anim = NULL;
            break;
        }
        if (mn_8022F298(jobj) >= anim[1]) {
            switch (data->xA) {
            case 1:
            case 3:
                data->xA = 0;
                break;
            case 2:
            case 4:
                HSD_GObjPLink_80390228(arg0);
                return;
            }
        } else {
            HSD_JObjAnim(jobj);
        }
    }

    if (data->xA == 0 || data->xA == 1 || data->xA == 3) {
        update_selection = mn_804A04F0.hovered_selection != data->x1;
        if (mn_804A04F0.hovered_selection == 1 && data->x2 == 1) {
            if (data->x9 != mn_804A04F0.confirmed_selection) {
                update_value = 1;
            }
        } else {
            ptr = (u8*) data + mn_804A04F0.hovered_selection;
            if (ptr[2] !=
                   mn_804A04F0.confirmed_selection)
            {
                update_value = 1;
            }
        }
    }

    mn_80230274(arg0, update_selection, update_value);
    mn_802308F0(arg0, update_selection, update_value);
    if (update_menu != 0) {
        data->x0 = mn_804A04F0.cur_menu;
    }
    if (update_selection != 0) {
        data->x1 = mn_804A04F0.hovered_selection;
    }
    if (update_value != 0) {
        if (data->x1 == 1 && data->x2 == 1) {
            data->x9 = mn_804A04F0.confirmed_selection;
        } else {
            ((u8*) data)[data->x1 + 2] = mn_804A04F0.confirmed_selection;
        }
        rules = gmMainLib_8015CC34();
        rules->mode = data->x2;
        rules->time_limit = data->x3;
        rules->handicap = data->x4;
        rules->damage_ratio = data->x5;
        rules->unk_x7 = data->x6;
        rules->stock_count = data->x9;
    }
}

extern s32 mn_804D6BD4;

int mn_80230D18(struct mn_802307F8_t* arg0, HSD_JObj* arg1, s8 arg2)
{
    s32 result;
    s32 i;

    arg0->x0 = mn_804A04F0.cur_menu;
    arg0->x1 = mn_804A04F0.hovered_selection;
    arg0->x4 = gmMainLib_8015CC34()->handicap;
    if (mn_804D6BD4 == 0 && arg0->x4 == 1) {
        arg0->x4 = 0;
    }
    arg0->x5 = gmMainLib_8015CC34()->damage_ratio;
    arg0->x6 = gmMainLib_8015CC34()->unk_x7;
    arg0->x2 = gmMainLib_8015CC34()->mode;
    arg0->x9 = gmMainLib_8015CC34()->stock_count;
    arg0->x3 = gmMainLib_8015CC34()->time_limit;
    if (gm_801A4310() == 0x1B && arg0->x3 == 0) {
        arg0->x3 = 0x63;
    }
    arg0->xA = arg2;
    result = 0;
    i = result;
    arg0->text = NULL;
    arg0 = (struct mn_802307F8_t*) ((u8*) arg0 + (i << 2));
    do {
        result = lb_80011E24(arg1, (HSD_JObj**) ((u8*) arg0 + 0xC), i, -1);
        i++;
        arg0 = (struct mn_802307F8_t*) ((u8*) arg0 + 4);
    } while (i < 10);
    return result;
}

/// #mn_80230E38

int mn_80231634(struct mn_80231634_t* arg0)
{
    if (arg0 == NULL) {
        return 0;
    }
    return arg0->x10;
}

void mn_8023164C(void)
{
    HSD_GObjProc* proc;
    s32 mode;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;

    switch (mn_804A04F0.prev_menu) {
    case 15:
        mn_804A04F0.hovered_selection = 6;
        mode = 3;
        break;
    case 16:
        mn_804A04F0.hovered_selection = 5;
        mode = 3;
        break;
    default:
        mn_804A04F0.hovered_selection = 0;
        mode = 1;
        break;
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(mode));
}

void mn_80231714(void)
{
    HSD_GObjProc* proc;
    s32 mode;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;

    switch (mn_804A04F0.prev_menu) {
    case 15:
        mn_804A04F0.hovered_selection = 6;
        mode = 3;
        break;
    case 16:
        mn_804A04F0.hovered_selection = 5;
        mode = 3;
        break;
    default:
        mn_804A04F0.hovered_selection = 0;
        mode = 1;
        break;
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(mode));
    mn_804D6BD4 = 1;
}

void mn_802317E4(HSD_Archive* archive, int arg1)
{
    mn_80231804(archive, arg1);
}

extern s32 mn_804D6BD4;

void mn_80231804(HSD_Archive* archive, int arg1)
{
    HSD_GObjProc* temp_r3;
    mn_804D6BC8.cooldown = 0x14;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
    mn_804A04F0.buttons = 0;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;
    mn_804A04F0.hovered_selection = 0;
    HSD_SisLib_803A5E70();

    lbArchive_LoadSections(
        archive, (void**) &MenMainBack_Top.joint, "MenMainBack_Top_joint",
        &MenMainBack_Top.animjoint, "MenMainBack_Top_animjoint",
        &MenMainBack_Top.matanim_joint, "MenMainBack_Top_matanim_joint",
        &MenMainBack_Top.shapeanim_joint, "MenMainBack_Top_shapeanim_joint",

        &MenMain_cam, "ScMenMain_cam_int1_camera", &MenMain_lights,
        "ScMenMain_scene_lights", &MenMain_fog, "ScMenMain_fog",

        &MenMainPanel_Top.joint, "MenMainPanel_Top_joint",
        &MenMainPanel_Top.animjoint, "MenMainPanel_Top_animjoint",
        &MenMainPanel_Top.matanim_joint, "MenMainPanel_Top_matanim_joint",
        &MenMainPanel_Top.shapeanim_joint, "MenMainPanel_Top_shapeanim_joint",

        &MenMainConRl_Top.joint, "MenMainConRl_Top_joint",
        &MenMainConRl_Top.animjoint, "MenMainConRl_Top_animjoint",
        &MenMainConRl_Top.matanim_joint, "MenMainConRl_Top_matanim_joint",
        &MenMainConRl_Top.shapeanim_joint, "MenMainConRl_Top_shapeanim_joint",

        &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
        &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
        &MenMainCursorRl_Top.matanim_joint,
        "MenMainCursorRl_Top_matanim_joint",
        &MenMainCursorRl_Top.shapeanim_joint,
        "MenMainCursorRl_Top_shapeanim_joint",

        &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
        &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
        &MenMainCursorRl_Top.matanim_joint,
        "MenMainCursorRl_Top_matanim_joint",
        &MenMainCursorRl_Top.shapeanim_joint,
        "MenMainCursorRl_Top_shapeanim_joint",

        &MenMainNmRl_Top.joint, "MenMainNmRl_Top_joint",
        &MenMainNmRl_Top.animjoint, "MenMainNmRl_Top_animjoint",
        &MenMainNmRl_Top.matanim_joint, "MenMainNmRl_Top_matanim_joint",
        &MenMainNmRl_Top.shapeanim_joint, "MenMainNmRl_Top_shapeanim_joint",

        &MenMainCursorTr01_Top.joint, "MenMainCursorTr01_Top_joint",
        &MenMainCursorTr01_Top.animjoint, "MenMainCursorTr01_Top_animjoint",
        &MenMainCursorTr01_Top.matanim_joint,
        "MenMainCursorTr01_Top_matanim_joint",
        &MenMainCursorTr01_Top.shapeanim_joint,
        "MenMainCursorTr01_Top_shapeanim_joint",

        &MenMainCursorTr02_Top.joint, "MenMainCursorTr02_Top_joint",
        &MenMainCursorTr02_Top.animjoint, "MenMainCursorTr02_Top_animjoint",
        &MenMainCursorTr02_Top.matanim_joint,
        "MenMainCursorTr02_Top_matanim_joint",
        &MenMainCursorTr02_Top.shapeanim_joint,
        "MenMainCursorTr02_Top_shapeanim_joint",

        &MenMainCursorTr03_Top.joint, "MenMainCursorTr03_Top_joint",
        &MenMainCursorTr03_Top.animjoint, "MenMainCursorTr03_Top_animjoint",
        &MenMainCursorTr03_Top.matanim_joint,
        "MenMainCursorTr03_Top_matanim_joint",
        &MenMainCursorTr03_Top.shapeanim_joint,
        "MenMainCursorTr03_Top_shapeanim_joint",

        &MenMainCursorTr04_Top.joint, "MenMainCursorTr04_Top_joint",
        &MenMainCursorTr04_Top.animjoint, "MenMainCursorTr04_Top_animjoint",
        &MenMainCursorTr04_Top.matanim_joint,
        "MenMainCursorTr04_Top_matanim_joint",
        &MenMainCursorTr04_Top.shapeanim_joint,
        "MenMainCursorTr04_Top_shapeanim_joint",

        &MenMainCursorRl01_Top.joint, "MenMainCursorRl01_Top_joint",
        &MenMainCursorRl01_Top.animjoint, "MenMainCursorRl01_Top_animjoint",
        &MenMainCursorRl01_Top.matanim_joint,
        "MenMainCursorRl01_Top_matanim_joint",
        &MenMainCursorRl01_Top.shapeanim_joint,
        "MenMainCursorRl01_Top_shapeanim_joint",

        &MenMainCursorRl02_Top.joint, "MenMainCursorRl02_Top_joint",
        &MenMainCursorRl02_Top.animjoint, "MenMainCursorRl02_Top_animjoint",
        &MenMainCursorRl02_Top.matanim_joint,
        "MenMainCursorRl02_Top_matanim_joint",
        &MenMainCursorRl02_Top.shapeanim_joint,
        "MenMainCursorRl02_Top_shapeanim_joint",

        &MenMainCursorRl03_Top.joint, "MenMainCursorRl03_Top_joint",
        &MenMainCursorRl03_Top.animjoint, "MenMainCursorRl03_Top_animjoint",
        &MenMainCursorRl03_Top.matanim_joint,
        "MenMainCursorRl03_Top_matanim_joint",
        &MenMainCursorRl03_Top.shapeanim_joint,
        "MenMainCursorRl03_Top_shapeanim_joint",

        &MenMainCursorRl04_Top.joint, "MenMainCursorRl04_Top_joint",
        &MenMainCursorRl04_Top.animjoint, "MenMainCursorRl04_Top_animjoint",
        &MenMainCursorRl04_Top.matanim_joint,
        "MenMainCursorRl04_Top_matanim_joint",
        &MenMainCursorRl04_Top.shapeanim_joint,
        "MenMainCursorRl04_Top_shapeanim_joint",

        &MenMainCursorRl05_Top.joint, "MenMainCursorRl05_Top_joint",
        &MenMainCursorRl05_Top.animjoint, "MenMainCursorRl05_Top_animjoint",
        &MenMainCursorRl05_Top.matanim_joint,
        "MenMainCursorRl05_Top_matanim_joint",
        &MenMainCursorRl05_Top.shapeanim_joint,
        "MenMainCursorRl05_Top_shapeanim_joint",

        &MenMainConIs_Top.joint, "MenMainConIs_Top_joint",
        &MenMainConIs_Top.animjoint, "MenMainConIs_Top_animjoint",
        &MenMainConIs_Top.matanim_joint, "MenMainConIs_Top_matanim_joint",
        &MenMainConIs_Top.shapeanim_joint, "MenMainConIs_Top_shapeanim_joint",

        &MenMainCursorIs_Top.joint, "MenMainCursorIs_Top_joint",
        &MenMainCursorIs_Top.animjoint, "MenMainCursorIs_Top_animjoint",
        &MenMainCursorIs_Top.matanim_joint,
        "MenMainCursorIs_Top_matanim_joint",
        &MenMainCursorIs_Top.shapeanim_joint,
        "MenMainCursorIs_Top_shapeanim_joint",

        &MenMainConSs_Top.joint, "MenMainConSs_Top_joint",
        &MenMainConSs_Top.animjoint, "MenMainConSs_Top_animjoint",
        &MenMainConSs_Top.matanim_joint, "MenMainConSs_Top_matanim_joint",
        &MenMainConSs_Top.shapeanim_joint, "MenMainConSs_Top_shapeanim_joint",

        &MenMainCursorSs_Top.joint, "MenMainCursorSs_Top_joint",
        &MenMainCursorSs_Top.animjoint, "MenMainCursorSs_Top_animjoint",
        &MenMainCursorSs_Top.matanim_joint,
        "MenMainCursorSs_Top_matanim_joint",
        &MenMainCursorSs_Top.shapeanim_joint,
        "MenMainCursorSs_Top_shapeanim_joint",

        0);

    mn_804D6BD4 = arg1;
    mn_8022C304();
    mn_8022BCF8();
    mn_8022BEDC(mn_8022BE34());
    mn_80229B2C();
    mn_80229DC0();
    temp_r3 = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    temp_r3->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(1));
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

bool mn_80231F80(u8 arg0)
{
    if (gm_801A4310() == 0x1B && arg0 == 1) {
        return false;
    }
    if (arg0 == 3) {
        if (gmMainLib_8015EE0C()) {
            return true;
        }
        return false;
    }
    if (arg0 == 5) {
        if (gmMainLib_8015EE44()) {
            return true;
        }
        return false;
    }
    return true;
}
