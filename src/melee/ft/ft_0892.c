#include "ft_0892.h"

#include "ft_0C88.h"
#include "ftcommon.h"
#include "ftdata.h"
#include "ftwaitanim.h"
#include "math.h"

#include "ft/chara/ftFox/ftFx_AppealS.h"
#include "ft/fighter.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ftCLink/ftCl_Init.h"
#include "ftCommon/ftCo_DownSpot.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftLink/ftLk_AttackAir.h"
#include "ftMasterHand/ftMh_Wait1_2.h"
#include "it/items/itpeachparasol.h"
#include "it/it_26B1.h"
#include "pl/plattack.h"
#include "pl/pltrick.h"

#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/// Local struct with bitfields - reversed order for MWCC big-endian
typedef struct {
    s32 x0;
    s32 x4;
    float x8;
    s32 xC;
    u8 x10_b7 : 1; // bit 7 (MSB)
    u8 x10_b6 : 1;
    u8 x10_b5 : 1;
    u8 x10_b4 : 1;
    u8 x10_b3 : 1;
    u8 x10_b2 : 1;
    u8 x10_b1 : 1;
    u8 x10_b0 : 1; // bit 0 (LSB)
    u8 x11_b7 : 1;
    u8 x11_b6 : 1;
    u8 x11_b5 : 1;
    u8 x11_b4 : 1;
    u8 x11_b3 : 1;
    u8 x11_b2 : 1;
    u8 x11_b1 : 1;
    u8 x11_b0 : 1;
} UnkStruct89768;

/// #ft_800892D4

void ft_800892D4(Fighter* arg0)
{
    union Struct2070 spC;

    spC.x2070_int = 0;
    arg0->dmg.x18d4 = *(UnkPlBonusBits*) &spC;
    arg0->x2070.x2070_int = *(s32*) &arg0->dmg.x18d4;
    *(s32*) &arg0->x2074.x2074_vec.x = 0;
    *(s32*) &arg0->x2074.x2074_vec.y = 0;
    *(f32*) &arg0->x2074.x207C.x = 0.0f;
    arg0->x2074.x207C.y = 6;
    arg0->x2074.x2084_b0 = 0;
    arg0->x2074.x2085_b3 = 0;
    arg0->x2074.x2084_b1 = 0;
    arg0->x2074.x2084_b2 = 0;
    arg0->x2074.x2084_b3 = 0;
    arg0->x2074.x2084_b4 = 0;
    arg0->x2074.x2084_b5 = 0;
    arg0->x2074.x2084_b6 = 0;
    arg0->x2074.x2084_b7 = 0;
    arg0->x2074.x2085_b0 = 0;
    arg0->x2074.x2085_b1 = 0;
    arg0->x2074.x2085_b2 = 0;
    arg0->x2074.x2085_b4 = 0;
    arg0->dmg.x18d8.x0 = 0;
    arg0->dmg.x18d8.x4 = 0;
    arg0->dmg.x18d8.kb_applied1 = 0.0f;
    arg0->dmg.x18d8.xC = 6;
    arg0->dmg.x18d8.x10_b0 = 0;
    arg0->dmg.x18d8.x11_b3 = 0;
    arg0->dmg.x18d8.x10_b1 = 0;
    arg0->dmg.x18d8.x10_b2 = 0;
    arg0->dmg.x18d8.x10_b3 = 0;
    arg0->dmg.x18d8.x10_b4 = 0;
    arg0->dmg.x18d8.x10_b5 = 0;
    arg0->dmg.x18d8.x10_b6 = 0;
    arg0->dmg.x18d8.x10_b7 = 0;
    arg0->dmg.x18d8.x11_b0 = 0;
    arg0->dmg.x18d8.x11_b1 = 0;
    arg0->dmg.x18d8.x11_b2 = 0;
    arg0->dmg.x18d8.x11_b4 = 0;
    arg0->dmg.x18ec_instancehitby = 0;
    arg0->x2074.x2088 = 0;
}

/// #ft_80089460

void ft_80089460(Fighter* fp)
{
    *(s32*) &fp->x2074.x2074_vec.x = 0;
    *(s32*) &fp->x2074.x2074_vec.y = 0;
    *(f32*) &fp->x2074.x207C.x = 0.0f;
    fp->x2074.x207C.y = 6;
    fp->x2074.x2084_b0 = 0;
    fp->x2074.x2085_b3 = 0;
    fp->x2074.x2084_b1 = 0;
    fp->x2074.x2084_b2 = 0;
    fp->x2074.x2084_b3 = 0;
    fp->x2074.x2084_b4 = 0;
    fp->x2074.x2084_b5 = 0;
    fp->x2074.x2084_b6 = 0;
    fp->x2074.x2084_b7 = 0;
    fp->x2074.x2085_b0 = 0;
    fp->x2074.x2085_b1 = 0;
    fp->x2074.x2085_b2 = 0;
    fp->x2074.x2085_b4 = 0;
    *(s32*) &fp->x2074.x2074_vec.x = (s32) fp->dmg.x1830_percent;
    if (fp->is_metal) {
        fp->x2074.x2084_b1 = 1;
    }
    if (fp->x197C != NULL) {
        fp->x2074.x2084_b2 = 1;
    }
    if (fp->x221D_b6) {
        fp->x2074.x2084_b3 = 1;
    }
    if (fp->x2226_b4) {
        fp->x2074.x2084_b4 = 1;
    }
    if (fp->x2220_b5) {
        fp->x2074.x2084_b5 = 1;
    }
    if (fp->x2220_b6) {
        fp->x2074.x2084_b6 = 1;
    }
}

/// #ft_800895E0

void ft_800895E0(Fighter* fp, int arg1)
{
    union Struct2070 val;
    union Struct2070 sp18;
    union Struct2070 sp14;
    Item_GObj* temp;
    union Struct2070 spC;

    spC.x2070_int = arg1;
    val = spC;
    if (val.x2073 == 0 || val.x2073 != fp->x2070.x2073) {
        fp->x2074.x2088 = plAttack_80037B08();
    }
    if (fp->kind == FTKIND_LUIGI && val.x2073 == 0x71) {
        sp18.x2070_int = 0x240063;
        val = sp18;
    }
    if (val.x2073 == 0x62) {
        temp = fp->item_gobj;
        if (temp != NULL && it_8026B6C8(temp) != 0) {
            sp14.x2070_int = 0x44003D;
            val = sp14;
        }
    }
    fp->x2070.x2070_int = val.x2070_int;
    ft_80089768(&fp->x2074.x2074_vec);
    *(s32*) &fp->x2074.x2074_vec.x = (s32) fp->dmg.x1830_percent;
    if (fp->is_metal) {
        fp->x2074.x2084_b1 = 1;
    }
    if (fp->x197C != NULL) {
        fp->x2074.x2084_b2 = 1;
    }
    if (fp->x221D_b6) {
        fp->x2074.x2084_b3 = 1;
    }
    if (fp->x2226_b4) {
        fp->x2074.x2084_b4 = 1;
    }
    if (fp->x2220_b5) {
        fp->x2074.x2084_b5 = 1;
    }
    if (fp->x2220_b6) {
        fp->x2074.x2084_b6 = 1;
    }
}

void ft_80089768(Vec2* ptr)
{
    UnkStruct89768* s = (UnkStruct89768*) ptr;
    s->x0 = 0;
    s->x4 = 0;
    s->x8 = 1.0f;
    s->xC = 6;
    s->x10_b7 = 0;
    s->x11_b4 = 0;
    s->x10_b6 = 0;
    s->x10_b5 = 0;
    s->x10_b4 = 0;
    s->x10_b3 = 0;
    s->x10_b2 = 0;
    s->x10_b1 = 0;
    s->x10_b0 = 0;
    s->x11_b7 = 0;
    s->x11_b6 = 0;
    s->x11_b5 = 0;
    s->x11_b3 = 0;
}

void ft_80089824(Fighter_GObj* gobj)
{
    Fighter* fp;
    s32 temp;

    fp = GET_FIGHTER(gobj);
    ((s32*) &temp)[0] = fp->x2070.x2070_int;
    fp->x2070.x2070_int = ((s32*) &temp)[0];
    ft_80089460(fp);
    fp->x2074.x2088 = plAttack_80037B08();
    pl_80037C60(gobj, 0);
}

union Struct2070* ft_80089884(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->x2070;
}

UnkPlBonusBits* ft_80089890(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->dmg.x18d4;
}

u16 ft_8008989C(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->dmg.x18ec_instancehitby;
}

struct Struct2074* ft_800898A8(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->x2074;
}

ft_800898B4_t* ft_800898B4(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->dmg.x18d8;
}

bool ft_800898C0(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->x2070.x2073 == 113 || ft->x2070.x2073 == 114 ||
         ft->x2070.x2073 == 99) ||
        ftFx_AppealS_CheckIfUsed(ft))
    {
        return true;
    }
    return false;
}

s32 ft_80089914(HSD_GObj* gobj, int msid)
{
    Fighter* fp = gobj->user_data;

    if (msid < ftCo_MS_AttackS3Hi || msid > ftCo_MS_AttackS4LwS) {
        return false;
    }

    if (fp->kind == FTKIND_FOX) {
        if ((u32) (msid - ftCo_MS_AttackS3LwS) <= 2) {
            return false;
        }
    }

    if (fp->kind == FTKIND_FALCO) {
        if ((u32) (msid - ftCo_MS_AttackS3LwS) <= 2) {
            return false;
        }
    }

    if (fp->kind == FTKIND_MEWTWO) {
        if (msid == ftCo_MS_AttackS3S) {
            return false;
        }
    }

    return true;
}
/// #fn_8008998C

#undef __FILE__
#define __FILE__ "jobj.h"

s32 fn_8008998C(Fighter* fp, void* arg1, Vec3* normal)
{
    u8 _[12];
    Vec3 jobj_pos;
    u8 __[4];
    Vec3 sp20;
    f32 floor_y;
    u32 floor_flags;
    u8 ___[4];
    f32 delta_y;
    f32 pos_x;
    f32 delta_x;
    f32 slope;

    Vec3* pos = (Vec3*) ((u8*) arg1 + 0x3C);
    HSD_JObjGetTranslation2((HSD_JObj*) fp->gobj->hsd_obj, &jobj_pos);

    normal->z = 0.0f;
    normal->y = 0.0f;
    normal->x = 0.0f;

    if (mpLib_8004DD90_Floor(fp->coll_data.floor.index, pos, &floor_y,
                             &floor_flags, normal) != -1)
    {
        delta_y = (pos->y + floor_y) - jobj_pos.y;
    } else {
        mpFloorGetLeft(fp->coll_data.floor.index, &sp20);
        if (pos->x > sp20.x) {
            mpFloorGetRight(fp->coll_data.floor.index, &sp20);
        }
        delta_y = sp20.y - jobj_pos.y;
    }

    if (ABS(delta_y) < 0.0001f) {
        return 0;
    }

    pos_x = pos->x;
    if (pos_x != jobj_pos.x) {
        delta_x = pos_x - jobj_pos.x;
        slope = delta_y / delta_x;
        if (slope > 0.45f) {
            delta_y = 0.45f * delta_x;
        } else if (slope < -0.45f) {
            delta_y = -0.45f * delta_x;
        }
    } else {
        delta_y = 0.0f;
    }

    pos->y += delta_y;
    return 1;
}

#undef __FILE__

/// #ft_80089B08

void ft_8008A1B8(Fighter_GObj* gobj, int flags)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221C_u16_y = flags;
    if (!(flags & 0x4)) {
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

bool ft_8008A1FC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.lstick.x * fp->facing_dir < 0.0F) ||
        (ABS(fp->input.lstick.x) < p_ftCommonData->x24))
    {
        return true;
    }
    return false;
}

static inline bool ft_8008A244_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r4 = GET_FIGHTER(gobj);
    f32 var_f2;

    var_f2 = temp_r4->input.lstick.x;
    if ((var_f2 * temp_r4->facing_dir < 0.0F) ||
        (ABS(var_f2) < p_ftCommonData->x24))
    {
        return true;
    }
    return false;
}

bool ft_8008A244(Fighter_GObj* gobj)
{
    if (ft_8008A244_inline(gobj)) {
        ft_8008A2BC(gobj);
        return true;
    }

    return false;
}

/// Seems to be called to end many actions if no frames are remaining
void ft_8008A2BC(HSD_GObj* gobj)
{
    if (ftLib_800872A4(gobj) == FTKIND_MASTERH) {
        ftMh_MS_389_80151018(gobj);
    } else if (ftLib_800872A4(gobj) == FTKIND_CREZYH) {
        ftCh_GrabUnk1_8015BC88(gobj);
    } else {
        ft_8008A348(gobj, 0);
    }
}

void ft_8008A324(HSD_GObj* gobj)
{
    ft_8008A348(gobj, -1.0f);
}

/// Transition state to ftCo_MS_Wait or otherwise neutral state
void ft_8008A348(Fighter_GObj* fighter_gobj, float anim_blend)
{
    Fighter* fighter;
    FighterKind kind;

    fighter = GET_FIGHTER((HSD_GObj*) fighter_gobj);
    if (fighter->x2224_b2 & 1) {
        ftCo_DownSpot_Enter(fighter_gobj);
        return;
    }
    if (ftCo_800C5240(fighter_gobj) != false) {
        ftCo_800C4ED8(fighter_gobj);
        return;
    }
    if (fighter->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fighter);
    }
    if (fighter->kind == FTKIND_PEACH) {
        if ((fighter->item_gobj != NULL) &&
            (itGetKind(fighter->item_gobj) == It_Kind_Peach_Parasol))
        {
            it_802BDB94(fighter->item_gobj);
        }
    }
    Fighter_ChangeMotionState(fighter_gobj, ftCo_MS_Wait, Ft_MF_None, 0.0f,
                              1.0f, anim_blend, NULL);
    if ((ftCo_8008A698(fighter) != false) &&
        (((struct ftData_80085FD4_ret*) ftData_80085FD4(fighter,
                                                        ftCo_MS_DeadUpFall))
             ->x8 != 0U))
    {
        ftCo_8008A6D8(fighter_gobj, ftCo_MS_DeadUpFall);
    }
    ftCommon_8007EFC0(fighter, p_ftCommonData->x5F0);
    kind = fighter->kind;
    switch (kind) { /* irregular */
    case FTKIND_LINK:
        ftLk_AttackAir_800EB3BC((HSD_GObj*) fighter_gobj);
        return;
    case FTKIND_CLINK:
        ftCl_Init_8014919C((HSD_GObj*) fighter_gobj);
        return;
    }
}
