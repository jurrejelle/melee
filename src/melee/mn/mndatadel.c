#include "mn/mndatadel.h"

#include "mn/mndatadel.static.h"

#include "placeholder.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "gm/gm_1601.h"
#include "gm/gm_16F1.h"
#include "gm/gm_1A3F.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "mn/mnmain.h"
#include "mn/mnmainrule.h"
#include "sc/types.h"

void mnDataDel_8024E940(void)
{
    HSD_JObj* sp18;
    f32 temp_f31;
    s32* data;
    s32 temp_ret;
    s32 var_r30;
    u8 var_r31;
    struct MnDataDelGObjUserData* temp_r31;
    PAD_STACK(24);

    temp_r31 = mnDataDel_804D6C68->user_data;
    data = &mnDataDel_803EF870.x3C;
    temp_ret = mn_80231634(temp_r31->x10[data[1]]);
    lb_80011E24((HSD_JObj*) temp_ret, &sp18, 1, -1);
    temp_f31 = mn_8022F298(sp18);
    HSD_JObjReqAnimAll(sp18, 1.0f);
    mn_8022F3D8(sp18, 0xFFU, MOBJ_MASK);
    HSD_JObjAnimAll(sp18);
    HSD_JObjReqAnimAll(sp18, temp_f31);
    mn_8022F3D8(sp18, 0xFFU, (enum _HSD_TypeMask) 0x480);
    HSD_JObjAnimAll(sp18);
    temp_r31->x4 = 1;
    gm_801647D0();
    gmMainLib_8015F490();
    var_r30 = 0;
    var_r31 = 0;
    do {
        if (gm_80164430(gm_801641CC(var_r31)) != 0 &&
            gm_80164250((u16) var_r31) != 0)
        {
            var_r30 = 1;
            break;
        }
        var_r31++;
    } while ((s32) var_r31 < 0x1D);
    if (var_r30 == 0) {
        gm_801641E4(0U, 1U);
    }
    gm_801729EC();
    lb_8001CE00();
}

void mnDataDel_8024EA6C(void)
{
    HSD_JObj* sp18;
    f32 temp_f31;
    f32 temp_f30;
    s32 temp_r0;
    s32 temp_r30;
    s32* var_r30;
    struct MnDataDelGObjUserData* temp_r31;
    s32 temp_ret;
    s32 var_r29;
    PAD_STACK(24);

    var_r29 = 0;
    var_r30 = &mnDataDel_803EF870.x3C;
    temp_f30 = 1.0f;
    temp_r31 = mnDataDel_804D6C68->user_data;
    do {
        temp_ret = mn_80231634(
            ((struct MnDataDelGObjUserData*) mnDataDel_804D6C68->user_data)
                ->x10[*var_r30]);
        lb_80011E24((HSD_JObj*) temp_ret, &sp18, 1, -1);
        temp_f31 = mn_8022F298(sp18);
        HSD_JObjReqAnimAll(sp18, temp_f30);
        mn_8022F3D8(sp18, 0xFFU, MOBJ_MASK);
        HSD_JObjAnimAll(sp18);
        HSD_JObjReqAnimAll(sp18, temp_f31);
        mn_8022F3D8(sp18, 0xFFU, (enum _HSD_TypeMask) 0x480);
        HSD_JObjAnimAll(sp18);
        temp_r0 = var_r29 + 3;
        var_r29 += 1;
        *((u8*) temp_r31 + temp_r0) = 1;
        var_r30 += 1;
    } while (var_r29 < 6);

    temp_r30 = lbLang_GetSavedLanguage();
    gmMainLib_8015FBA4();
    gm_801A3EF4();
    if (temp_r30 == lbLang_GetSavedLanguage()) {
        lbAudioAx_800237A8(0xBF, 0x7F, 0x40);
    } else {
        lbLang_SetSavedLanguage(temp_r30);
        lbAudioAx_80027AB0(0xBF);
    }
    gm_801603B0();
    gmMainLib_8015F588((s32) gmMainLib_8015F4E8());
    gm_801729EC();
    lb_8001CE00();
}

void mnDataDel_8024EBC8(HSD_JObj* arg0, u8 unused, u8 arg1, u8 arg2)
{
    HSD_JObj* sp14;
    HSD_JObj* sp10;
    f32 var_f1;
    f32 var_f1_2;

    lb_80011E24(arg0, &sp10, 4, -1);
    if (arg1 != 0) {
        var_f1 = 1.0f;
    } else {
        var_f1 = 0.0f;
    }
    HSD_JObjReqAnimAll(sp10, var_f1);
    mn_8022F3D8(sp10, 0xFFU, TOBJ_MASK);
    HSD_JObjAnimAll(sp10);
    lb_80011E24(arg0, &sp14, 1, -1);
    if (arg1 != 0) {
        if (arg2 != 0) {
            var_f1_2 = mnDataDel_803EF870.x18.end_frame;
        } else {
            var_f1_2 = mnDataDel_803EF870.x18.start_frame;
        }
    } else if (arg2 != 0) {
        var_f1_2 = mnDataDel_803EF870.x24.end_frame;
    } else {
        var_f1_2 = mnDataDel_803EF870.x24.start_frame;
    }
    HSD_JObjReqAnimAll(sp14, var_f1_2);
    mn_8022F3D8(sp14, 0xFFU, TOBJ_MASK);
    HSD_JObjAnimAll(sp14);
}

/// @brief animates the warning modal
void fn_8024ECCC(HSD_GObj* arg0)
{
    HSD_JObj* root;
    HSD_JObj* panel;
    HSD_JObj* exclaim;
    HSD_JObj* cursor_no;
    HSD_JObj* cursor_yes;
    u8 _pad[10];
    f32 curr_frame;
    HSD_Text* text;
    s32 sis_id;
    u8 visible;
    u8 cursor_idx;
    struct WarnCmnData* data;

    root = GET_JOBJ(arg0);
    data = mnDataDel_804D6C68->user_data;
    lb_80011E24(root, &panel, WARN_JOINT_PANEL, -1);
    if (data->visible != 0) {
        curr_frame = mn_8022F298(root);
        if ((mnDataDel_803EF8A0.start_frame <= curr_frame) &&
            (curr_frame < mnDataDel_803EF8A0.end_frame))
        {
            curr_frame = mn_8022EFD8(panel, &mnDataDel_803EF8A0);
            lb_80011E24(root, &exclaim, WARN_JOINT_EXCLAIM, -1, curr_frame);
            mn_8022EFD8(exclaim, &mnDataDel_803EF8A0);
            if (curr_frame >= mnDataDel_803EF8A0.end_frame) {
                visible = data->visible;
                if (mnDataDel_804D6C6C != NULL) {
                    HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
                }
                if ((s32) visible == 1) {
                    sis_id = 318;
                } else {
                    sis_id = 319;
                }
                text = HSD_SisLib_803A5ACC(
                    0, 1, mnDataDel_803EF870.x64, mnDataDel_803EF870.x68,
                    mnDataDel_803EF870.x6C, 250.0f, 5.0f);
                mnDataDel_804D6C6C = text;
                text->font_size.x = 0.05f;
                text->font_size.y = 0.05f;
                text->default_alignment = 1;
                HSD_SisLib_803A6368(text, sis_id);
            }
        } else {
            cursor_idx = data->cursor_idx;
            lb_80011E24(root, &cursor_yes, WARN_JOINT_CURSOR_YES, -1);
            lb_80011E24(root, &cursor_no, WARN_JOINT_CURSOR_NO, -1);
            if ((s32) cursor_idx != 0) {
                HSD_JObjReqAnimAll(cursor_yes, 1.0f);
                HSD_JObjReqAnimAll(cursor_no, 0.0f);
            } else {
                HSD_JObjReqAnimAll(cursor_yes, 0.0f);
                HSD_JObjReqAnimAll(cursor_no, 1.0f);
            }
            HSD_JObjAnimAll(cursor_yes);
            HSD_JObjAnimAll(cursor_no);
        }
    } else {
        HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
        mnDataDel_804D6C6C = NULL;
        HSD_GObjPLink_80390228(arg0);
    }
}

/// @brief creates the warning modal
void mnDataDel_8024EEC0(void)
{
    HSD_JObj* cursor_yes;
    HSD_JObj* cursor_no;
    HSD_JObj* no;
    HSD_JObj* yes;
    HSD_JObj* root;
    f32 no_pos;
    f32 yes_pos;
    s32 is_english;
    s32 cursor;
    HSD_GObj* wrn_modal;
    struct WarnCmnData* data;
    PAD_STACK(4);

    data = mnDataDel_804D6C68->user_data;
    wrn_modal = GObj_Create(6U, 7U, 0x80U);
    root = HSD_JObjLoadJoint(mnDataDel_804A0938.joint);
    HSD_GObjObject_80390A70(wrn_modal, HSD_GObj_804D7849, root);
    GObj_SetupGXLink(wrn_modal, HSD_GObj_JObjCallback, 6U, 0x80U);
    HSD_GObj_SetupProc(wrn_modal, fn_8024ECCC, 0U);
    HSD_JObjAddAnimAll(root, mnDataDel_804A0938.animjoint,
                       mnDataDel_804A0938.matanim_joint,
                       mnDataDel_804A0938.shapeanim_joint);
    HSD_JObjReqAnimAll(root, mnDataDel_803EF8A0.start_frame);
    HSD_JObjAnimAll(root);
    // hide arrow and progress bar
    JObj_HideChildAtIdx(root, WARN_JOINT_EXCLAIM_ARROW);
    JObj_HideChildAtIdx(root, WARN_JOINT_PROGRESS_BAR);
    cursor = data->cursor_idx;
    lb_80011E24(root, &yes, WARN_JOINT_CURSOR_YES, -1);
    lb_80011E24(root, &no, WARN_JOINT_CURSOR_NO, -1);
    if (cursor != 0) {
        HSD_JObjReqAnimAll(yes, 1.0f);
        HSD_JObjReqAnimAll(no, 0.0f);
    } else {
        HSD_JObjReqAnimAll(yes, 0.0f);
        HSD_JObjReqAnimAll(no, 1.0f);
    }
    HSD_JObjAnimAll(yes);
    HSD_JObjAnimAll(no);

    is_english = lbLang_IsSavedLanguageUS();
    if (is_english != false) {
        lb_80011E24(root, &cursor_yes, WARN_JOINT_CURSOR_YES, -1);
        lb_80011E24(root, &cursor_no, WARN_JOINT_CURSOR_NO, -1);
        yes_pos = HSD_JObjGetTranslationX(cursor_yes);
        no_pos = HSD_JObjGetTranslationX(cursor_no);
        HSD_JObjSetTranslateX(cursor_yes, no_pos);
        HSD_JObjSetTranslateX(cursor_no, yes_pos);
    }
}

void fn_8024F1D4(HSD_GObj* gobj)
{
    u32 buttons;
    HSD_GObjProc* proc;
    struct MnDataDelGObjUserData* user_data;
    PAD_STACK(16);

    user_data = mnDataDel_804D6C68->user_data;
    buttons = mn_80229624(4U);
    mn_804A04F0.buttons = buttons;
    if (buttons & 0x10) {
        if (user_data->x2 != 0) {
            mnDataDel_8024EA6C();
        } else {
            lbAudioAx_80024030(0);
        }
        mn_804D6BC8.cooldown = 5;
        user_data->x1 = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024F840, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804D6BC8.cooldown = 5;
        user_data->x1 = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024F840, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    if ((buttons & 8) || (buttons & 4)) {
        lbAudioAx_80024030(2);
        if (user_data->x2 != 0) {
            user_data->x2 = 0;
            return;
        }
        user_data->x2 = 1;
    }
}

/// #fn_8024F318

/// #fn_8024F840

void fn_8024FBA4(HSD_GObj* gobj)
{
    s32 i;
    f32 frame;
    struct MnDataDelData* data;
    u8* user_data;
    PAD_STACK(8);

    data = &mnDataDel_803EF870;
    user_data = gobj->user_data;
    frame = mn_8022EE84(GET_JOBJ(gobj), &data->xC, (enum _HSD_TypeMask) 0x480);
    for (i = 0; i < 6; i++) {
        mn_8022EE84(*(HSD_JObj**) (user_data +
                                   ((s32*) ((u8*) &data->x3C))[i] * 4 + 0x10),
                    &data->xC, (enum _HSD_TypeMask) 0x480);
    }
    if (frame >= data->xC.end_frame) {
        HSD_GObjPLink_80390228(gobj);
    }
}

inline HSD_JObj* fn_8024FC48_inline(int arg0);
inline HSD_JObj* fn_8024FC48_inline(int arg0)
{
    return (HSD_JObj*) arg0;
}

void fn_8024FC48(HSD_GObj* gobj)
{
    s32 i;
    HSD_JObj* jobj;
    struct MnDataDelData* data;
    u8* user_data;

    data = &mnDataDel_803EF870;
    user_data = gobj->user_data;

    if (mn_804A04F0.cur_menu != 0x18) {
        HSD_GObjProc* proc;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024FBA4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(*(HSD_Text**) (user_data + 0xC));
    } else {
        for (i = 0; i < 6; i++) {
            lb_80011E24(
                fn_8024FC48_inline(mn_80231634(
                    *(struct mn_80231634_t**) ((u8*) gobj->user_data +
                                               ((s32*) ((u8*) &data->x3C))[i] *
                                                   4 +
                                               0x10))),
                &jobj, 1, -1);
            if (user_data[0] == i) {
                mn_8022EC18(jobj, &data->x18, (HSD_TypeMask) 0x400);
            } else {
                mn_8022EC18(jobj, &data->x24, (HSD_TypeMask) 0x400);
            }
        }
    }
}

void fn_8024FD40(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    HSD_GObjProc* proc;
    f32 frame;
    s32 i;
    s32* offsets;
    struct MnDataDelGObjUserData* user_data;
    struct MnDataDelData* data;
    PAD_STACK(16);

    jobj = GET_JOBJ(gobj);
    data = &mnDataDel_803EF870;
    user_data = gobj->user_data;
    if ((u8) mn_804A04F0.cur_menu != 0x18) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024FBA4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(user_data->xC);
        return;
    }
    frame = mn_8022EE84(jobj, &data->x0, (enum _HSD_TypeMask) 0x480);
    offsets = &data->x3C;
    i = 0;
    do {
        mn_8022EE84(user_data->x10[*offsets], &data->x0,
                    (enum _HSD_TypeMask) 0x480);
        offsets++;
        i++;
    } while (i < 6);
    if (frame == data->x0.end_frame) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024FC48, 0);
        proc->flags_3 = HSD_GObj_804D783C;
    }
}

/// #mnDataDel_8024FE4C

/// #mnDataDel_80250170
