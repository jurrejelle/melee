#include "ft/ft_0D31.h"

#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/ftwaitanim.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Throw.h"
#include "lb/lbvector.h"

#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_AirCatch.h>
#include <melee/ft/chara/ftCommon/ftCo_AppealS.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack100.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackAir.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_EscapeAir.h>
#include <melee/ft/chara/ftCommon/ftCo_Fall.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_JumpAerial.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialAir.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/chara/ftCommon/ftCo_Squat.h>
#include <melee/ft/chara/ftCommon/ftCo_Turn.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

/* 0D4DD4 */ static void fn_800D4DD4(Fighter_GObj* gobj);

bool ftCo_800D3158(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int* temp_r29 = &p_ftCommonData->x520;

    if (fp->x222A_b1 || fp->x2228_b5 || fp->x2228_b2) {
        return false;
    }
    if (fp->x2219_b2) {
        return false;
    }
    if (fp->x2219_b1) {
        return false;
    }
    if (fp->cur_pos.x > Stage_GetBlastZoneRightOffset()) {
        ftCo_800D3950(gobj);
        return true;
    }
    if (fp->cur_pos.x < Stage_GetBlastZoneLeftOffset()) {
        ftCo_800D3680(gobj);
        return true;
    }
    if (fp->cur_pos.y > Stage_GetBlastZoneTopOffset() &&
        (fp->ground_or_air == GA_Ground || fp->x2222_b3 ||
         fp->x8c_kb_vel.y > p_ftCommonData->x4F0))
    {
        if (Player_GetMoreFlagsBit5(fp->player_id)) {
            ftCo_800D3E40(gobj);
        } else {
            int temp_r28 = HSD_Randi(100) + 1;
            if (!Camera_8003010C() && *temp_r29 >= temp_r28) {
                if (fp->motion_id == ftCo_MS_DamageIce) {
                    ftCo_800D47B8(gobj);
                } else {
                    ftCo_800D4780(gobj);
                }
            } else if (fp->motion_id == ftCo_MS_DamageIce) {
                ftCo_800D41C4(gobj);
            } else {
                ftCo_800D40B8(gobj);
            }
        }
        return true;
    }
    if (fp->cur_pos.y < Stage_GetBlastZoneBottomOffset()) {
        ftCo_800D3BC8(gobj);
        return true;
    }
    return false;
}

void ftCo_800D331C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->victim_gobj != NULL) {
        if (fp->x221B_b5) {
            Fighter* temp_r3_2 = GET_FIGHTER(fp->victim_gobj);
            if (!temp_r3_2->x221F_b4) {
                temp_r3_2->x2180 = fp->player_id;
            }
        } else if (!fp->x221F_b4) {
            pl_8004065C((u8) ftLib_80086BE0(fp->victim_gobj),
                        ftLib_800874BC(fp->victim_gobj));
        }
    }
    if (fp->x2180 != 6) {
        pl_8004065C(fp->x2180, 0);
    }
    if (fp->death2_cb != NULL) {
        fp->death2_cb(gobj);
    }
    if (fp->death3_cb != NULL) {
        fp->death3_cb(gobj);
    }
    if (fp->death1_cb != NULL) {
        fp->death1_cb(gobj);
    }
    ftCo_800DD100(gobj);
    ftCommon_8007E2FC(gobj);
    if (fp->item_gobj != NULL) {
        Item_8026A8EC(fp->item_gobj);
        fp->item_gobj = NULL;
        pl_8003EA08(fp->player_id, fp->x221F_b4);
        pl_8003EA74(fp->player_id, fp->x221F_b4);
    }
    if (fp->x197C != NULL) {
        ftCommon_8007F8E8(gobj);
        Item_8026A8EC(fp->x197C);
        ftCommon_8007F9B4(gobj);
    }
    if (fp->x1980 != NULL) {
        ftCommon_8007F8E8(gobj);
        Item_8026A8EC(fp->x1980);
        ftCommon_8007FF74(gobj);
    }
    if (fp->is_metal) {
        ftCo_800C8540(gobj);
    }
    if (fp->x2226_b4) {
        ftCo_800C8A64(gobj);
    }
    ftCommon_8007DB24(gobj);
    fp->mv.co.unk_800D331C.x6C = fp->motion_id;
    fp->mv.co.unk_800D331C.x70 = fp->x2070.x2073;
}

void ftCo_800D34E0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Player_SetFallsByIndex(
        fp->player_id, fp->x221F_b4,
        Player_GetFallsByIndex(fp->player_id, fp->x221F_b4) + 1);
    plStale_ResetStaleMoveTableForPlayer(fp->player_id);
    if ((gm_8016B094() || gm_8016B0E8()) &&
        Player_GetEntity(fp->player_id) == gobj)
    {
        Player_LoseStock(fp->player_id);
    }
    if (gm_8016B094() && Player_GetStocks(fp->player_id) <= 0) {
        Player_UpdateMatchFrameCount(fp->player_id, fp->x221F_b4);
    }
    if (fp->dmg.x18c4_source_ply != 6) {
        Player_UpdateKOsBySlot(fp->dmg.x18c4_source_ply, fp->x221F_b4,
                               fp->player_id);
    } else {
        Player_IncSuicideCount(fp->player_id, fp->x221F_b4);
    }
    pl_8003D644(fp->player_id, fp->x221F_b4, fp->mv.co.unk_800D34E0.x6C,
                fp->mv.co.unk_800D34E0.x70);
    Player_SetHPByIndex(fp->player_id, fp->x221F_b4, 0);
}

void ftCo_800D35FC(Fighter* fp)
{
    u8 _[8];
    HSD_GObj* cur_gobj;

    ftCommon_8007EBAC(fp, 5, p_ftCommonData->x4F8);
    cur_gobj = HSD_GObj_Entities->fighters;
    while (cur_gobj != NULL) {
        Fighter* cur_fp = GET_FIGHTER(cur_gobj);
        if (cur_fp != fp && !cur_fp->x221F_b3) {
            ftCommon_8007EBAC(cur_fp, 6, p_ftCommonData->x4FC);
        }
        cur_gobj = cur_gobj->next;
    }
}

#pragma push
#pragma dont_inline on

void ftCo_800D3680(Fighter_GObj* gobj)
{
    Fighter_GObj *new_var;
    Fighter* temp_r28;
    Fighter* temp_r28_3;
    Fighter* temp_r31;
    FtSFX* temp_r28_2;
    f32 temp_f1;
    f32 temp_f31;
    int color1;
    int color2;
    Vec3 sp2C;
    s32 sp28;
    Fighter* temp_r27_2;
    Fighter* temp_r27;
    f32 sp24;
    u8 _[24];

    temp_r31 = (temp_r27 = gobj->user_data);
    ftCo_800D331C(gobj);
    temp_r27->mv.co.unk_800D3680.x40 = p_ftCommonData->x500;
    Fighter_ChangeMotionState(gobj, 1, 0U, 0.0F, 1.0F, 0.0F, NULL);
    temp_r28 = (new_var = gobj)->user_data;
    if (temp_r28->x221D_b6) {
        ft_800880D8(temp_r28);
        temp_r28->x2004 = 0;
    }
    temp_r28->x2219_b1 = 1;
    temp_r28->x221E_b1 = 1;
    temp_r28->x221E_b2 = 1;
    pl_8003DF44(temp_r27->player_id, temp_r27->x221F_b4);

    temp_r27_2 = gobj->user_data;
    temp_r28_2 = temp_r27_2->ft_data->x4C_sfx;
    temp_r27_2->invisible = true;
    temp_r27_2->x221F_b1 = 1;
    Camera_80030E44(4, &temp_r27_2->cur_pos);
    ftCo_800D35FC(temp_r27_2);
    ftCo_800D34E0(gobj);
    ft_80088C5C(gobj);
    ftCo_800D38B8(temp_r27_2, (0, temp_r28_2->x4));
    ftCo_800D38B8(temp_r27_2, temp_r28_2->x8);

    ft_PlaySFX(temp_r31, 0x88, 0x7F, 0x40);
    ft_8008805C(temp_r31, 0x88);
    sp2C = temp_r31->cur_pos;
    temp_f31 = Stage_GetBlastZoneTopOffset();
    temp_f1 = Stage_GetBlastZoneBottomOffset();
    if (sp2C.y > temp_f31) {
        sp2C.y = temp_f31;
    }
    if (sp2C.y < temp_f1) {
        sp2C.y = temp_f1;
    }
    sp24 = -1.5707964f;

    {
        s32 var_r3;
        temp_r28_3 = gobj->user_data;
        {
            int offset = Player_GetUnk45(temp_r28_3->player_id) << 2;
            u8* base1 = Fighter_804D650C + offset;
            u8* base2 = Fighter_804D6508 + offset;
            color1 = (base1[0] << 16) | (base1[1] << 8) | base1[2];
            color2 = (base2[0] << 16) | (base2[1] << 8) | base2[2];
        }
        if (gm_801693BC(temp_r28_3->player_id)) {
            var_r3 = 0x42C;
        } else {
            var_r3 = 0x42B;
        }
        efSync_Spawn(var_r3, gobj, &sp2C, &sp24, &p_ftCommonData->x4F4,
                     color1, color2);
    }
    sp2C.x = Stage_GetBlastZoneLeftOffset();
    ftCo_800D4E50(temp_r31, &sp2C, 1, 0.0F);
}

#pragma pop

void ftCo_800D38B8(Fighter* fp, int arg1)
{
    ft_800881D8(fp, arg1, 0x7F, 0x40);
    if (!fp->x2225_b6) {
        ft_8008805C(fp, arg1);
    }
}

void ftCo_DeadLeft_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadLeft_Cam(Fighter_GObj* gobj) {}

#pragma push
#pragma dont_inline on

void ftCo_800D3950(Fighter_GObj* gobj)
{
    Fighter_GObj* new_var;
    Fighter* temp_r28;
    Fighter* temp_r28_3;
    Fighter* temp_r31;
    FtSFX* temp_r28_2;
    f32 temp_f1;
    f32 temp_f31;
    int color1;
    int color2;
    Vec3 sp2C;
    s32 sp28;
    Fighter* temp_r27_2;
    Fighter* temp_r27;
    f32 sp24;
    u8 _[24];

    temp_r31 = (temp_r27 = gobj->user_data);
    ftCo_800D331C(gobj);
    temp_r27->mv.co.unk_800D3680.x40 = p_ftCommonData->x500;
    Fighter_ChangeMotionState(gobj, 2, 0U, 0.0F, 1.0F, 0.0F, NULL);
    temp_r28 = (new_var = gobj)->user_data;
    if (temp_r28->x221D_b6) {
        ft_800880D8(temp_r28);
        temp_r28->x2004 = 0;
    }
    temp_r28->x2219_b1 = 1;
    temp_r28->x221E_b1 = 1;
    temp_r28->x221E_b2 = 1;
    pl_8003DF44(temp_r27->player_id, temp_r27->x221F_b4);

    temp_r27_2 = gobj->user_data;
    temp_r28_2 = temp_r27_2->ft_data->x4C_sfx;
    temp_r27_2->invisible = true;
    temp_r27_2->x221F_b1 = 1;
    Camera_80030E44(4, &temp_r27_2->cur_pos);
    ftCo_800D35FC(temp_r27_2);
    ftCo_800D34E0(gobj);
    ft_80088C5C(gobj);
    ftCo_800D38B8(temp_r27_2, (0, temp_r28_2->x4));
    ftCo_800D38B8(temp_r27_2, temp_r28_2->x8);

    ft_PlaySFX(temp_r31, 0x89, 0x7F, 0x40);
    ft_8008805C(temp_r31, 0x89);
    sp2C = temp_r31->cur_pos;
    temp_f31 = Stage_GetBlastZoneTopOffset();
    temp_f1 = Stage_GetBlastZoneBottomOffset();
    if (sp2C.y > temp_f31) {
        sp2C.y = temp_f31;
    }
    if (sp2C.y < temp_f1) {
        sp2C.y = temp_f1;
    }
    sp24 = 1.5707964f;

    {
        s32 var_r3;
        temp_r28_3 = gobj->user_data;
        {
            int offset = Player_GetUnk45(temp_r28_3->player_id) << 2;
            u8* base1 = Fighter_804D650C + offset;
            u8* base2 = Fighter_804D6508 + offset;
            color1 = (base1[0] << 16) | (base1[1] << 8) | base1[2];
            color2 = (base2[0] << 16) | (base2[1] << 8) | base2[2];
        }
        if (gm_801693BC(temp_r28_3->player_id)) {
            var_r3 = 0x42C;
        } else {
            var_r3 = 0x42B;
        }
        efSync_Spawn(var_r3, gobj, &sp2C, &sp24, &p_ftCommonData->x4F4,
                     color1, color2);
    }
    sp2C.x = Stage_GetBlastZoneRightOffset();
    ftCo_800D4E50(temp_r31, &sp2C, 1, 3.1415927f);
}

#pragma pop

void ftCo_DeadRight_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadRight_Cam(Fighter_GObj* gobj) {}


#pragma push
#pragma dont_inline on

void ftCo_800D3BC8(Fighter_GObj* gobj)
{
    Fighter_GObj* new_var;
    Fighter* temp_r28;
    Fighter* temp_r28_3;
    Fighter* temp_r31;
    FtSFX* temp_r28_2;
    f32 temp_f1;
    f32 temp_f31;
    int color1;
    int color2;
    Vec3 sp30;
    s32 sp2C;
    s32 sp28;
    Fighter* temp_r27_2;
    Fighter* temp_r27;
    f32 sp24;
    u8 _[24];

    temp_r31 = (temp_r27 = gobj->user_data);
    ftCo_800D331C(gobj);
    temp_r27->mv.co.unk_800D3680.x40 = p_ftCommonData->x500;
    Fighter_ChangeMotionState(gobj, 0, 0U, 0.0F, 1.0F, 0.0F, NULL);
    temp_r28 = (new_var = gobj)->user_data;
    if (temp_r28->x221D_b6) {
        ft_800880D8(temp_r28);
        temp_r28->x2004 = 0;
    }
    temp_r28->x2219_b1 = 1;
    temp_r28->x221E_b1 = 1;
    temp_r28->x221E_b2 = 1;
    pl_8003DF44(temp_r27->player_id, temp_r27->x221F_b4);

    temp_r27_2 = gobj->user_data;
    temp_r28_2 = temp_r27_2->ft_data->x4C_sfx;
    temp_r27_2->invisible = true;
    temp_r27_2->x221F_b1 = 1;
    Camera_80030E44(4, &temp_r27_2->cur_pos);
    ftCo_800D35FC(temp_r27_2);
    ftCo_800D34E0(gobj);
    ft_80088C5C(gobj);
    ftCo_800D38B8(temp_r27_2, (0, temp_r28_2->x4));
    ftCo_800D38B8(temp_r27_2, temp_r28_2->x8);

    ft_PlaySFX(temp_r31, 0x61, 0x7F, 0x40);
    ft_8008805C(temp_r31, 0x61);
    sp30 = temp_r31->cur_pos;
    temp_f31 = Stage_GetBlastZoneRightOffset();
    temp_f1 = Stage_GetBlastZoneLeftOffset();
    if (sp30.x > temp_f31) {
        sp30.x = temp_f31;
    }
    if (sp30.x < temp_f1) {
        sp30.x = temp_f1;
    }
    sp24 = 0.0f;

    {
        s32 var_r3;
        temp_r28_3 = gobj->user_data;
        {
            int offset = Player_GetUnk45(temp_r28_3->player_id) << 2;
            u8* base1 = Fighter_804D650C + offset;
            u8* base2 = Fighter_804D6508 + offset;
            color1 = (base1[0] << 16) | (base1[1] << 8) | base1[2];
            color2 = (base2[0] << 16) | (base2[1] << 8) | base2[2];
        }
        if (gm_801693BC(temp_r28_3->player_id)) {
            var_r3 = 0x42C;
        } else {
            var_r3 = 0x42B;
        }
        efSync_Spawn(var_r3, gobj, &sp30, &sp24, &p_ftCommonData->x4F4,
                     color1, color2);
    }
    sp30.y = Stage_GetBlastZoneBottomOffset();
    ftCo_800D4E50(temp_r31, &sp30, 1, 1.5707964f);
}

#pragma pop

void ftCo_DeadDown_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadDown_Cam(Fighter_GObj* gobj) {}

#pragma push
#pragma dont_inline on

void ftCo_800D3E40(Fighter_GObj* gobj)
{
    Fighter_GObj* new_var;
    Fighter* temp_r28;
    Fighter* temp_r28_3;
    Fighter* temp_r31;
    FtSFX* temp_r28_2;
    f32 temp_f1;
    f32 temp_f31;
    int color1;
    int color2;
    Vec3 sp30;
    s32 sp2C;
    s32 sp28;
    Fighter* temp_r27_2;
    Fighter* temp_r27;
    f32 sp24;
    u8 _[24];

    temp_r31 = (temp_r27 = gobj->user_data);
    ftCo_800D331C(gobj);
    temp_r27->mv.co.unk_800D3680.x40 = p_ftCommonData->x500;
    Fighter_ChangeMotionState(gobj, 3, 0U, 0.0F, 1.0F, 0.0F, NULL);
    temp_r28 = (new_var = gobj)->user_data;
    if (temp_r28->x221D_b6) {
        ft_800880D8(temp_r28);
        temp_r28->x2004 = 0;
    }
    temp_r28->x2219_b1 = 1;
    temp_r28->x221E_b1 = 1;
    temp_r28->x221E_b2 = 1;
    pl_8003DF44(temp_r27->player_id, temp_r27->x221F_b4);

    temp_r27_2 = gobj->user_data;
    temp_r28_2 = temp_r27_2->ft_data->x4C_sfx;
    temp_r27_2->invisible = true;
    temp_r27_2->x221F_b1 = 1;
    Camera_80030E44(4, &temp_r27_2->cur_pos);
    ftCo_800D35FC(temp_r27_2);
    ftCo_800D34E0(gobj);
    ft_80088C5C(gobj);
    ftCo_800D38B8(temp_r27_2, (0, temp_r28_2->x4));
    ftCo_800D38B8(temp_r27_2, temp_r28_2->x8);

    ft_PlaySFX(temp_r31, 0x61, 0x7F, 0x40);
    ft_8008805C(temp_r31, 0x61);
    sp30 = temp_r31->cur_pos;
    temp_f31 = Stage_GetBlastZoneRightOffset();
    temp_f1 = Stage_GetBlastZoneLeftOffset();
    if (sp30.x > temp_f31) {
        sp30.x = temp_f31;
    }
    if (sp30.x < temp_f1) {
        sp30.x = temp_f1;
    }
    sp24 = 3.1415927f;

    {
        s32 var_r3;
        temp_r28_3 = gobj->user_data;
        {
            int offset = Player_GetUnk45(temp_r28_3->player_id) << 2;
            u8* base1 = Fighter_804D650C + offset;
            u8* base2 = Fighter_804D6508 + offset;
            color1 = (base1[0] << 16) | (base1[1] << 8) | base1[2];
            color2 = (base2[0] << 16) | (base2[1] << 8) | base2[2];
        }
        if (gm_801693BC(temp_r28_3->player_id)) {
            var_r3 = 0x42C;
        } else {
            var_r3 = 0x42B;
        }
        efSync_Spawn(var_r3, gobj, &sp30, &sp24, &p_ftCommonData->x4F4,
                     color1, color2);
    }
    sp30.y = Stage_GetBlastZoneTopOffset();
    ftCo_800D4E50(temp_r31, &sp30, 1, 4.712389f);
}

#pragma pop

void ftCo_DeadUp_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadUp_Cam(Fighter_GObj* gobj) {}

static inline void ftCo_800D40B8_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221D_b6) {
        ft_800880D8(fp);
        fp->x2004 = false;
    }
    fp->x2219_b1 = true;
    fp->x221E_b1 = true;
    fp->x221E_b2 = true;
    ft_80088C5C(gobj);
}

void ftCo_800D40B8(Fighter_GObj* gobj)
{
    u8 _[8];
    int *temp_r31 = (0, &p_ftCommonData->x504);
    Fighter *fp = (0, (Fighter *) HSD_GObjGetUserData(gobj));
    Fighter *new_var;
    ftCo_800D331C(gobj);
    fp->mv.co.unk_deadup.x40 = *temp_r31;
    fp->mv.co.unk_deadup.x44 = 0.0F;
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpStar, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftCo_800D40B8_inline(gobj);
    ftCommon_8007EFC0(fp, true);
    new_var = fp;
    ft_800881D8(new_var, fp->ft_data->x4C_sfx->xC, 127, 64);
    pl_8003DF44(fp->player_id, fp->x221F_b4);
    fp->mv.co.unk_deadup.x68 = 0;
}

void ftCo_800D41C4(Fighter_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2227_b6 = 1;
    {
        int* temp_r31 = &p_ftCommonData->x504;
        Fighter* fp2 = GET_FIGHTER(gobj);
        ftCo_800D331C(gobj);
        fp2->mv.co.unk_deadup.x40 = *temp_r31;
        fp2->mv.co.unk_deadup.x44 = 0;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpStarIce, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    ftCo_800D40B8_inline(gobj);
    ftCommon_8007EFC0(fp, true);
    ft_800881D8(fp, fp->ft_data->x4C_sfx->xC, 127, 64);
    pl_8003DF44(fp->player_id, fp->x221F_b4);
    ftCo_80090AC0(fp);
    ftCommon_8007EBAC(fp, 1, 0);
    fp->mv.co.unk_deadup.x68 = 1;
}

void ftCo_DeadUpStar_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32* data = (s32*) &p_ftCommonData->x504;

    if (fp->mv.co.unk_deadup.x44 == 1) {
        if (fp->mv.co.unk_deadup.x68 != 0) {
            f32 rot_speed = *(f32*)(data + 6);
            HSD_JObj* jobj =
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
            HSD_JObjAddRotationX(jobj, rot_speed);
        }
    }

    if (fp->mv.co.unk_deadup.x40 != 0) {
        fp->mv.co.unk_deadup.x40 -= 1;
    }

    if (fp->mv.co.unk_deadup.x40 == 0) {
        switch (fp->mv.co.unk_deadup.x44) {
        case 0:
            fp->self_vel.y =
                (*(f32*)(data + 4) * Stage_GetCamBoundsTopOffset() -
                 fp->cur_pos.y) /
                (f32) data[1];
            fp->self_vel.z = *(f32*)(data + 3) / (f32) data[1];
            fp->mv.co.unk_deadup.x40 = data[1];
            fp->mv.co.unk_deadup.x44 = 1;
            return;
        case 1:
            ftCommon_8007E2FC(gobj);
            if (fp->mv.co.unk_deadup.x68 != 0) {
                ftCommon_8007DB24(gobj);
            }
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                efAsync_Spawn(gobj, &fp2->x60C, 2, 0x42D, NULL,
                              &fp->cur_pos);
            }
            ftCo_800D4E50(fp, &fp->cur_pos, 0, 1.5707964f);
            fp->x221F_b1 = 1;
            fp->invisible = true;
            ft_80088C5C(gobj);
            ft_PlaySFX(fp, 0x83, 0x7F, 0x40);
            ft_8008805C(fp, 0x83);
            ftCo_800D34E0(gobj);
            fp->mv.co.unk_deadup.x40 = data[2];
            fp->mv.co.unk_deadup.x44 = 2;
            return;
        case 2:
            ftMaterial_800BFD9C(gobj);
            break;
        }
    }
}

void ftCo_DeadUpStar_Cam(Fighter_GObj* gobj)
{
    ftCamera_80076320(gobj);
}

/// #ftCo_800D4580

extern Quaternion lbl_803B7500;

void ftCo_800D4580(Fighter_GObj* gobj, int arg1)
{
    u8 _[24];
    Fighter* fp = gobj->user_data;
    int* datattrs = &p_ftCommonData->x520;

    ftCo_800D331C(gobj);

    fp->mv.co.unk_deadup.x40 = datattrs[1];
    fp->mv.co.unk_deadup.x44 = 0;
    fp->mv.co.unk_deadup.x50 = *(Vec3*) &datattrs[6];
    fp->mv.co.common.x24 = 0.0f;
    fp->mv.co.common.x20 = 0.0f;
    fp->mv.co.common.x1C = 0.0f;

    Fighter_ChangeMotionState(gobj, arg1, Ft_MF_None, 0.0f, 1.0f, 0.0f,
                              NULL);
    fp->x2220_b7 = true;

    {
        HSD_JObj* jobj = GET_JOBJ(gobj);
        Quaternion q = lbl_803B7500;
        if (((Fighter*) gobj->user_data)->x34_scale.z == 1.0f) {
            HSD_JObjSetRotation(jobj, &q);
        }
    }

    {
        Fighter* fp2 = gobj->user_data;
        if (fp2->x221D_b6) {
            ft_800880D8(fp2);
            fp2->x2004 = 0;
        }
        fp2->x2219_b1 = true;
        fp2->x221E_b1 = true;
        fp2->x221E_b2 = true;
    }

    ft_80088C5C(gobj);
    ftCommon_8007EFC0(fp, true);
    ftCo_800BFFD0(fp, 0x2B, 0);
    pl_8003DF44(fp->player_id, fp->x221F_b4);
}

void ftCo_800D4780(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800D4580(gobj, 6);
    fp->mv.co.unk_deadup.x68 = 0;
}

void ftCo_800D47B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2227_b6 = true;
    ftCo_800D4580(gobj, 9);
    ftCo_80090AC0(fp);
    ftCommon_8007EBAC(fp, 1, 0);
    fp->mv.co.unk_deadup.x68 = 1;
}

s32 ftCo_800D481C(Fighter_GObj* gobj, s32 arg1)
{
    Fighter* fp;
    HSD_JObj* jobj;
    u8 _[44];
    Quaternion q;

    fp = gobj->user_data;

    Fighter_ChangeMotionState(gobj, arg1,
                              Ft_MF_SkipRumble | Ft_MF_SkipColAnim, 0.0f,
                              1.0f, 0.0f, NULL);

    fp->x2220_b7 = true;

    jobj = GET_JOBJ(gobj);
    q = lbl_803B7500;

    if (((Fighter*) gobj->user_data)->x34_scale.z == 1.0f) {
        HSD_JObjSetRotation(jobj, &q);
    }

    fp->x2219_b1 = 1;
    fp->x221E_b1 = 1;
    fp->x221E_b2 = 1;
    ftCommon_8007EBAC(fp, 5, p_ftCommonData->x4F8);

    {
        HSD_GObj* cur;
        for (cur = HSD_GObj_Entities->fighters; cur != NULL;
             cur = cur->next)
        {
            Fighter* other = cur->user_data;
            if (other != fp && !other->x221F_b3) {
                ftCommon_8007EBAC(other, 6, p_ftCommonData->x4FC);
            }
        }
    }

    Camera_80030E44(4, &fp->cur_pos);
    ft_800889F4(fp, (FtSFXArr*) fp->ft_data->x4C_sfx->x20);
    ftCo_800D4E50(fp, &fp->cur_pos, 0, 1.5707964f);
    fp->accessory4_cb = fn_800D4DD4;
    return (s32) fn_800D4DD4;
}

/// #ftCo_DeadUpFall_Anim

void ftCo_DeadUpFall_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32* data = (s32*) &p_ftCommonData->x520;
    u8 _[8];

    if (fp->mv.co.unk_deadup.x44 != 1) {
    } else {
        fp->mv.co.walk.middle_anim_frame +=
            fp->mv.co.walk.slow_anim_frame;
        if (fp->mv.co.unk_deadup.x68 != 0) {
            f32 rot_speed = *(f32*)(data + 16);
            HSD_JObj* jobj =
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
            HSD_JObjAddRotationX(jobj, rot_speed);
        }
    }

    if (fp->mv.co.unk_deadup.x40 != 0) {
        fp->mv.co.unk_deadup.x40 -= 1;
    }

    if (fp->mv.co.unk_deadup.x40 == 0) {
        switch (fp->mv.co.unk_deadup.x44) {
        case 0:
            fp->mv.co.walk.slow_anim_frame = 1.0f / (f32) data[2];
            fp->mv.co.walk.middle_anim_frame =
                fp->mv.co.walk.slow_anim_frame;
            fp->mv.co.unk_deadup.x40 = data[2];
            fp->mv.co.unk_deadup.x44 = 1;
            return;
        case 1:
            if (fp->mv.co.unk_deadup.x68 != 0) {
                Fighter* fp2 = GET_FIGHTER(gobj);
                ftCo_800D481C(gobj, 0xA);
                ftCo_80090AC0(fp2);
            } else if (GET_FIGHTER(gobj)->x34_scale.z != 1.0f) {
                ftCo_800D481C(gobj, 8);
            } else {
                ftCo_800D481C(gobj, 7);
            }
            fp->mv.co.unk_deadup.x40 = data[3];
            fp->mv.co.unk_deadup.x44 = 2;
            return;
        case 2:
            fp->self_vel.y = *(f32*)(data + 12);
            fp->self_vel.z = *(f32*)(data + 15);
            fp->mv.co.unk_deadup.x40 = data[4];
            fp->mv.co.unk_deadup.x44 = 3;
            return;
        case 3:
            ftCommon_8007E2FC(gobj);
            if (fp->mv.co.unk_deadup.x68 != 0) {
                ftCommon_8007DB24(gobj);
            }
            fp->x221F_b1 = 1;
            fp->invisible = true;
            ftCo_800D34E0(gobj);
            ft_80088C5C(gobj);
            ft_PlaySFX(fp, 0x61, 0x7F, 0x40);
            ft_8008805C(fp, 0x61);
            ftCommon_8007EBAC(fp, 0xD, 0);
            Camera_80030E44(4, &fp->cur_pos);
            fp->mv.co.unk_deadup.x40 = data[5];
            fp->mv.co.unk_deadup.x44 = 4;
            return;
        case 4:
            ftMaterial_800BFD9C(gobj);
            break;
        }
    }
}

void ftCo_DeadUpFall_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8* ca = (u8*) p_ftCommonData + 0x520;

    switch (fp->mv.co.unk_deadup.x44) {
    case 1:
        if (fp->x2222_b6) {
            if (!ftAnim_80070FD0(fp)) {
                break;
            }
        }
        lbVector_Lerp((Vec3*) (ca + 0x18), (Vec3*) (ca + 0x24),
                      &fp->mv.co.unk_deadup.x50, fp->mv.co.unk_deadup.x4C);
        break;
    case 3:
        ftCommon_Fall(fp, *(float*) (ca + 0x34), *(float*) (ca + 0x38));
        lbVector_Add(&fp->mv.co.unk_deadup.x5C, &fp->self_vel);
        if (fp->x2222_b6) {
            if (!ftAnim_80070FD0(fp)) {
                break;
            }
        }
        lbVector_Add(&fp->mv.co.unk_deadup.x50, &fp->mv.co.unk_deadup.x5C);
        fp->mv.co.unk_deadup.x5C.z = 0;
        fp->mv.co.unk_deadup.x5C.y = 0;
        fp->mv.co.unk_deadup.x5C.x = 0;
        break;
    }
}

void fn_800D4DD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* temp_r31 = fp;
    f32 bottom_offset;

    switch (temp_r31->mv.co.unk_deadup.x44) {
    case 3:
        bottom_offset = Stage_GetCamBoundsBottomOffset();
        if (temp_r31->cur_pos.y < bottom_offset) {
            ftCommon_8007E2FC(gobj);
        }
        break;
    default:
        break;
    }
}

void ftCo_DeadUpFall_Cam(Fighter_GObj* gobj)
{
    ftCamera_80076320(gobj);
}

void ftCo_800D4E50(Fighter* fp, Vec3* arg1, int arg2, float arg8)
{
    if (gm_8016B0B4() && !fp->x221F_b4) {
        int coins = Player_GetCoins(fp->player_id);
        int var_r31 = coins / 2;
        Player_SetCoins(fp->player_id, coins - var_r31);
        Player_SetUnk9C(fp->player_id,
                        var_r31 + Player_GetUnk9C(fp->player_id));
        if (var_r31 > p_ftCommonData->x5C8) {
            var_r31 = p_ftCommonData->x5C8;
        }
        it_802E5F8C(fp->gobj, arg1, var_r31, arg2, arg8, p_ftCommonData->x5CC);
    }
}

static inline void ftCo_800D4F24_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    if (temp_r31->x221D_b6) {
        ft_800880D8(temp_r31);
        temp_r31->x2004 = 0;
    }
    temp_r31->x2219_b1 = 1;
    temp_r31->x221E_b1 = 1;
    temp_r31->x221E_b2 = 1;
    ftMaterial_800BFD04(gobj);
}

void ftCo_800D4F24(Fighter_GObj* gobj, int index)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221F_b3) {
        return;
    }
    if (index != 0) {
        f32 sp1C = fp->ft_data->x0->x168 * fp->x34_scale.y;
        u8 _[4];
        efSync_Spawn(0x43F, 0, &fp->cur_pos, &sp1C);
    }
    ftCo_800D331C(gobj);
    ftCo_800D4F24_inline(gobj);
}

void ftCo_800D4FF4(Fighter_GObj* gobj)
{
    Vec3 sp44;
    Vec3 scale_vec;
    Vec3 pos_vec;
    Vec3 sp20;
    Vec3 sp14;
    u8 _[4];
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_UnkProcessDeath_80068354(gobj);
    fp->smash_attrs.x2135 = Player_80032F30(fp->player_id);

    if ((s8) fp->smash_attrs.x2135 == -1) {
        Player_GetSpawnPlatformPos(fp->player_id, &sp44);
        fp->mv.co.turn.facing_after =
            fp->facing_dir * ftCommon_800804EC(fp) + sp44.x;
        fp->mv.co.turn.x8 = sp44.y;
        fp->mv.co.walk.middle_anim_frame = 0.0f;
    } else {
        Stage_80224E38(&sp14, (s8) fp->smash_attrs.x2135);
        Player_GetSomePos(fp->player_id, &sp20);
        fp->mv.co.turn.facing_after =
            fp->facing_dir * ftCommon_800804EC(fp) +
            (sp14.x + sp20.x);
        fp->mv.co.turn.x8 = sp14.y + sp20.y;
        fp->mv.co.walk.middle_anim_frame = 0.0f;
    }

    ftCommon_8007D5D4(fp);
    fp->mv.co.unk_deadup.x40 = (int) p_ftCommonData->x5D0;
    Fighter_ChangeMotionState(gobj, 0xC, 0x1002, 0.0f, 1.0f, -1.0f, NULL);

    fp->x221E_b2 = 1;
    fp->x2219_b1 = 1;
    fp->x221E_b1 = 1;
    fp->x2222_b7 = 1;
    fp->x221D_b5 = 1;
    ftCo_800BFFD0(fp, 0xA, 0);

    if (!fp->x221F_b4) {
        ftCommon_SetAccessory(fp, ((void**) Fighter_804D6534)[0]);
        {
            f32 s =
                fp->x34_scale.y * fp->co_attrs.respawn_platform_scale;
            scale_vec.z = s;
            scale_vec.y = s;
            scale_vec.x = s;
        }
        HSD_JObjSetScale(fp->x20A0_accessory, &scale_vec);

        ftCommon_8007E690(fp, ((void**) Fighter_804D6534)[1]);

        pos_vec.x =
            -(fp->facing_dir * ftCommon_800804EC(fp) - fp->cur_pos.x);
        pos_vec.y = fp->cur_pos.y;
        pos_vec.z = fp->cur_pos.z;
        HSD_JObjSetTranslate(fp->x20A0_accessory, &pos_vec);

        fp->accessory1_cb = fn_800D54A4;
    } else {
        fp->accessory1_cb = fn_800D55B4;
    }

    ftCommon_8007EFC0(fp, 1);
}

void ftCo_Rebirth_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_8008A7A8(gobj, fp->ft_data->x24);
    fp->mv.co.common.x0 -= 1;
    if (fp->mv.co.common.x0 == 0) {
        ftCo_800D5600(gobj);
    }
}

void ftCo_Rebirth_IASA(Fighter_GObj* gobj) {}

void ftCo_Rebirth_Phys(Fighter_GObj* gobj)
{
    Fighter* new_var;
    Vec3 cur_pos;
    Vec3 player_pos;
    Vec3 stage_pos;
    Fighter* fp = gobj->user_data;
    new_var = fp;
    if (!new_var->x221F_b4) {
        if (new_var->smash_attrs.x2135 != -1) {
            Stage_80224E38(&stage_pos, new_var->smash_attrs.x2135);
            Player_GetSomePos(new_var->player_id, &player_pos);
            new_var->mv.co.common.x4 =
                stage_pos.x + player_pos.x +
                new_var->facing_dir * ftCommon_800804EC(new_var);
            *(f32*) &new_var->mv.co.common.x8 =
                stage_pos.y + player_pos.y;
            *(f32*) &new_var->mv.co.common.xC = 0.0f;
        }
        ftCommon_8007F8B4(new_var, &cur_pos);
        {
            float inv = 1.0f / (float) new_var->mv.co.common.x0;
            new_var->self_vel.x =
                (new_var->mv.co.common.x4 - cur_pos.x) * inv;
            new_var->self_vel.y =
                (*(f32*) &new_var->mv.co.common.x8 - cur_pos.y) *
                inv;
        }
    } else {
        HSD_GObj* other_gobj =
            Player_GetEntityAtIndex(new_var->player_id, 0);
        Fighter* other_fp = other_gobj->user_data;
        new_var->self_vel.x = other_fp->self_vel.x;
        new_var->self_vel.y = other_fp->self_vel.y;
    }
    PAD_STACK(12);
}

void ftCo_Rebirth_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->smash_attrs.x2135 == -1) {
        ft_80083DCC(gobj);
    }
}
void fn_800D54A4(Fighter_GObj* gobj)
{
<<<<<<< HEAD
    Vec3 sp;
    u8 _[8];
    Fighter* fp = gobj->user_data;
    HSD_GObj* other_gobj = Player_GetEntityAtIndex(fp->player_id, 1);

    if (other_gobj != NULL) {
        Fighter* other_fp = other_gobj->user_data;
        if (!other_fp->x221F_b3) {
            f32 other_y = other_fp->cur_pos.y;
            if (other_y > fp->cur_pos.y) {
                fp->cur_pos.y = other_y;
            }
        }
    }

    sp.x = -(fp->facing_dir * ftCommon_800804EC(fp) - fp->cur_pos.x);
    sp.y = fp->cur_pos.y;
    sp.z = fp->cur_pos.z;

    HSD_JObjSetTranslate(fp->x20A0_accessory, &sp);
=======
    Vec3 translate;
    float result;
    Fighter* fp = gobj->user_data;
    HSD_GObj* other_gobj = Player_GetEntityAtIndex(fp->player_id, 1);
    if (other_gobj != NULL) {
        Fighter* other_fp = other_gobj->user_data;
        if (!other_fp->x221F_b3) {
            if (other_fp->cur_pos.y > fp->cur_pos.y) {
                fp->cur_pos.y = other_fp->cur_pos.y;
            }
        }
    }
    result = ftCommon_800804EC(fp);
    translate.x = fp->cur_pos.x - fp->facing_dir * result;
    translate.y = fp->cur_pos.y;
    translate.z = fp->cur_pos.z;
    HSD_JObjSetTranslate(fp->x20A0_accessory, &translate);
    PAD_STACK(8);
>>>>>>> master
}

void fn_800D55B4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter* new_var;
    HSD_GObj* other_gobj = Player_GetEntityAtIndex(fp->player_id, 0);
    Fighter* other_fp = other_gobj->user_data;
    new_var = other_fp;
    if (new_var->cur_pos.y > fp->cur_pos.y) {
        fp->cur_pos.y = other_fp->cur_pos.y;
    }
}
void ftCo_800D5600(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    mpColl_80043680(&fp->coll_data, &fp->cur_pos);
    fp->self_vel.y = 0;
    fp->mv.co.common.x0 = (int) p_ftCommonData->x5D4;
    Fighter_ChangeMotionState(gobj, ftCo_MS_RebirthWait,
                              Ft_MF_KeepGfx | Ft_MF_SkipColAnim |
                                  Ft_MF_KeepAccessory | Ft_MF_SkipNametagVis,
                              0, 1, 0, NULL);
    fp->x221E_b2 = 1;
    fp->x2219_b1 = 1;
    fp->x221E_b1 = 1;
    fp->x221D_b5 = 1;
    if (!fp->x221F_b4) {
        fp->accessory1_cb = fn_800D54A4;
    } else {
        fp->accessory1_cb = fn_800D55B4;
    }
    if (fp->smash_attrs.x2135 != -1) {
        mpColl_80043680(&fp->coll_data, &fp->cur_pos);
    }
}

void ftCo_RebirthWait_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_8008A7A8(gobj, fp->ft_data->x24);
    fp->mv.co.common.x0 -= 1;
    if (fp->mv.co.common.x0 == 0) {
        ftColl_8007B7A4(gobj, p_ftCommonData->x5D8);
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_RebirthWait_IASA(Fighter_GObj* gobj)
{
    u8 _[8];
    s32 var_r30 = 0;
    Fighter* fp = gobj->user_data;

    if (!fp->x221F_b4) {
        HSD_GObj* companion = Player_GetEntityAtIndex(fp->player_id, 1);
        if (companion != NULL &&
            !((Fighter*) companion->user_data)->x221F_b3 &&
            ftLib_800873CC(companion) == 0)
        {
            var_r30 = 1;
        }
    } else {
        if (ftLib_800873CC(
                Player_GetEntityAtIndex(fp->player_id, 0)) != 0)
        {
            return;
        }
        var_r30 = 1;
    }

    if (ftCo_SpecialAir_CheckInput(gobj) ||
        ftCo_800D7100(gobj) ||
        ftCo_800C3B10(gobj) ||
        ftCo_80099A58(gobj) ||
        ftCo_AttackAir_CheckItemThrowInput(gobj) ||
        ftCo_800D705C(gobj) ||
        ftCo_800CB870(gobj))
    {
        /* priority input detected */
    } else if (ftCo_80091A2C(gobj) ||
               ftCo_800DE9B8(gobj) ||
               fn_800D5F84(gobj) ||
               ftCo_800C97A8(gobj) ||
               ftWalkCommon_800DFC70(gobj) ||
               var_r30)
    {
        ftCo_Fall_Enter(gobj);
    } else {
        return;
    }

    ftColl_8007B7A4(gobj, p_ftCommonData->x5D8);
    pl_80040374(fp->player_id, fp->x221F_b4);
}

void ftCo_RebirthWait_Phys(Fighter_GObj* gobj)
{
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    u8 _[12];
    Fighter* fp = gobj->user_data;

    if (!fp->x221F_b4) {
        if ((s8) fp->smash_attrs.x2135 != -1) {
            Stage_80224E38(&sp18, (s8) fp->smash_attrs.x2135);
            Player_GetSomePos(fp->player_id, &sp24);
            fp->mv.co.common.x4 =
                fp->facing_dir * ftCommon_800804EC(fp) +
                (sp18.x + sp24.x);
            *(f32*) &fp->mv.co.common.x8 = sp18.y + sp24.y;
            *(f32*) &fp->mv.co.common.xC = 0.0f;
        }
        ftCommon_8007F8B4(fp, &sp30);
        {
            f32 inv_timer = 1.0f / (f32) fp->mv.co.common.x0;
            fp->self_vel.x = inv_timer * (fp->mv.co.common.x4 - sp30.x);
            fp->self_vel.y =
                inv_timer * (*(f32*) &fp->mv.co.common.x8 - sp30.y);
        }
    } else {
        Fighter* other_fp =
            Player_GetEntityAtIndex(fp->player_id, 0)->user_data;
        fp->self_vel.x = other_fp->self_vel.x;
        fp->self_vel.y = other_fp->self_vel.y;
    }
}

void ftCo_RebirthWait_Coll(Fighter_GObj* gobj)
{
    ft_80083844(gobj, fn_800D5A30);
}

void fn_800D5A30(Fighter_GObj* gobj)
{
    ftColl_8007B7A4(gobj, p_ftCommonData->x5D8);
    ft_8008A2BC(gobj);
}
void ftCo_Rebirth_Cam(Fighter_GObj* gobj)
{
    UnkFloat6_Camera spC;
    Fighter* fp = GET_FIGHTER(gobj);
    CmSubject* camera_box = fp->x890_cameraBox;
    ftCamera_80076018(fp->ft_data->x3C, &spC, fp->x34_scale.y);
    camera_box->x10.x = fp->mv.co.common.x4;
    camera_box->x10.y = *(f32*) &fp->mv.co.common.x8 + spC.x0.x;
    camera_box->x10.z = 0.0f;
    ftLib_800866DC(gobj, &camera_box->x1C);
}
