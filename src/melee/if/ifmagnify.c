#include "ifmagnify.h"

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "gm/gm_16AE.h"
#include "gm/types.h"
#include "gr/ground.h"
#include "if/ifall.h"
#include "if/if_2FC93.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "pl/player.h"
#include "sc/types.h"

#include <baselib/cobj.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/mobj.h>
#include <baselib/tobj.h>

#include <math.h>

/* 3F97E8 */ extern HSD_CameraDescPerspective ifMagnify_803F97E8;
static char ifMagnify_803F988C[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static char ifMagnify_804D57F0[] = "jobj.h";
static char ifMagnify_804D57F8[] = "jobj";
/* 4DDB08 */ extern f32 ifMagnify_804DDB08;
/* 4DDB28 */ extern f32 ifMagnify_804DDB28;
/* 4DDB2C */ extern f32 ifMagnify_804DDB2C;
/* 4DDB30 */ extern f32 ifMagnify_804DDB30;
/* 4DDB34 */ extern f32 ifMagnify_804DDB34;
/* 4DDB38 */ extern f32 ifMagnify_804DDB38;
/* 4DDB3C */ extern f32 ifMagnify_804DDB3C;
/* 4DDB40 */ extern f32 ifMagnify_804DDB40;
/* 4DDB44 */ extern f32 ifMagnify_804DDB44;
/* 4DDB48 */ extern f32 ifMagnify_804DDB48;
/* 4DDB4C */ extern f32 ifMagnify_804DDB4C;
/* 4DDB50 */ extern f64 ifMagnify_804DDB50;
/* 4DDB60 */ extern int ifMagnify_804DDB60;

ifMagnify ifMagnify_804A1DE0;

s32 ifMagnify_802FB6E8(s32 slot)
{
    if (ifMagnify_802FC998(slot) != 0) {
        return ifMagnify_804A1DE0.player[slot].state.unk;
    }
    return 0;
}

ifMagnifyPlayer* ifMagnify_802FB73C(ifMagnifyPlayer* arg0, Vec2* arg1, Vec2* arg2)
{
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_f4;

    temp_f2 = arg1->x;
    temp_f4 = arg1->y;
    if (0.0f == temp_f2) {
        if (temp_f4 > 0.0f) {
            arg2->y = ifMagnify_804DDB28;
        } else {
            arg2->y = ifMagnify_804DDB2C;
        }
        arg2->x = ifMagnify_804DDB08;
    } else {
        temp_f3 = temp_f4 / temp_f2;
        if ((temp_f3 > ifMagnify_804DDB30) || (temp_f3 < ifMagnify_804DDB34)) {
            if (temp_f4 > 0.0f) {
                arg2->y = ifMagnify_804DDB28;
            } else {
                arg2->y = ifMagnify_804DDB2C;
            }
            temp_f1 = arg2->y * temp_f2;
            temp_f1 /= temp_f4;
            if (temp_f1 < ifMagnify_804DDB38) {
                arg2->x = ifMagnify_804DDB38;
            } else if (temp_f1 > ifMagnify_804DDB3C) {
                arg2->x = ifMagnify_804DDB3C;
            } else {
                arg2->x = temp_f1;
            }
        } else {
            if (temp_f2 > 0.0f) {
                arg2->x = ifMagnify_804DDB3C;
            } else {
                arg2->x = ifMagnify_804DDB38;
            }
            temp_f1_2 = arg2->x * temp_f4;
            temp_f1_2 /= temp_f2;
            if (temp_f1_2 < ifMagnify_804DDB2C) {
                arg2->y = ifMagnify_804DDB2C;
            } else if (temp_f1_2 > ifMagnify_804DDB28) {
                arg2->y = ifMagnify_804DDB28;
            } else {
                arg2->y = temp_f1_2;
            }
        }
    }

    temp_f1_3 = arg2->x;
    if (temp_f1_3 == ifMagnify_804DDB38) {
        arg0->state.unk = 2;
        return arg0;
    }
    if (temp_f1_3 == ifMagnify_804DDB3C) {
        arg0->state.unk = 4;
        return arg0;
    }
    if (arg2->y == ifMagnify_804DDB28) {
        arg0->state.unk = 1;
        return arg0;
    }
    arg0->state.unk = 3;
    return arg0;
}

void ifMagnify_802FB8C0(HSD_GObj* arg0, s32 arg1)
{
    S32Vec2 screen_pos;
    Vec2 pos;
    Vec2 out;
    Vec3 translate;
    GXColor color;
    HSD_GObj* fighter_gobj;
    ifMagnifyPlayer* player;
    s32 slot;
    bool is_colored;
    u8 arrow_kind;
    u8 slot_type;
    u8 teams_enabled;

    if (arg1 != 0) {
        return;
    }

    player = arg0->user_data;
    slot = player - ifMagnify_804A1DE0.player;
    is_colored = false;
    if ((gm_8016AE38()->hud_enabled != 0) && !ifAll_IsHUDHidden() &&
        !Camera_80030130() && player->state.is_offscreen)
    {
        fighter_gobj = Player_GetEntity(slot);
        if (fighter_gobj != NULL) {
            ftLib_80086A58(fighter_gobj, &screen_pos);
            pos.x = screen_pos.x - 320.0f;
            pos.y = -((f32) screen_pos.y - 240.0f);

            HSD_JObjSetRotationZ(player->jobj, atan2f(pos.y, pos.x));

            ifMagnify_802FB73C(player, &pos, &out);
            translate.x = 0.09125f * out.x;
            translate.y = 0.1f * out.y;
            translate.z = 0.0f;
            HSD_JObjSetTranslate((HSD_JObj*) player->gobj->hsd_obj, &translate);

            HSD_GObj_JObjCallback(arg0, arg1);
            if ((player->state.unk == 4) || (player->state.unk == 2)) {
                slot_type = Player_GetPlayerSlotType(slot);
                teams_enabled = gm_8016B168();
                color = gm_80160968(gm_80160854((u8) slot, Player_GetTeam(slot),
                                                teams_enabled, slot_type));
                if (player->state.unk == 2) {
                    arrow_kind = 1;
                } else {
                    arrow_kind = 2;
                }
                un_802FD928((u8) slot, arrow_kind, &color);
                is_colored = true;
            }
        }
    }
    if (!is_colored) {
        un_802FD9D8((u8) slot);
    }
}

/// #ifMagnify_802FBBDC

void ifMagnify_802FC3BC(void) {}

void ifMagnify_802FC3C0(s32 slot)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_DObj* dobj;
    HSD_ImageDesc* image_descs;
    HSD_MObj* mobj;
    HSD_Material* material;
    ifMagnifyPlayer* player;
    GXColor color;
    u8 slot_type;
    u8 teams_enabled;

    player = &ifMagnify_804A1DE0.player[slot];
    if (player->gobj != NULL) {
        HSD_GObjPLink_80390228(player->gobj);
    }

    gobj = GObj_Create(0xE, 0xF, 0);
    GObj_InitUserData(gobj, 0xE, (void (*)(void*)) ifMagnify_802FC3BC, player);

    jobj = HSD_JObjLoadJoint(ifMagnify_804A1DE0.model_desc->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, (void (*)(HSD_GObj*, int)) ifMagnify_802FB8C0, 0xB,
                     0);

    lb_80011E24(jobj, &child, 2, -1);
    if (slot == 0) {
        player->idesc = child->u.dobj->next->mobj->tobj->imagedesc;
    } else {
        image_descs = (HSD_ImageDesc*) ifMagnify_804A1DE0.image_descs;
        image_descs[slot - 1] = *ifMagnify_804A1DE0.player[0].idesc;
        player->idesc = &image_descs[slot - 1];
        player->idesc->image_ptr = HSD_MemAlloc((GXGetTexBufferSize(
                                                     player->idesc->width,
                                                     player->idesc->height,
                                                     player->idesc->format, 0, 0) +
                                                 0x1F) &
                                                ~0x1F);
        child->u.dobj->next->mobj->tobj->imagedesc = player->idesc;
    }

    lb_80011E24(jobj, &player->jobj, 1, -1);

    slot_type = Player_GetPlayerSlotType(slot);
    teams_enabled = gm_8016B168();
    color = gm_80160968(
        gm_80160854((u8) slot, Player_GetTeam(slot), teams_enabled, slot_type));

    dobj = player->jobj->u.dobj;
    mobj = dobj->mobj;
    material = mobj->mat;
    material->diffuse.r = color.r;
    material->diffuse.g = color.g;
    material->diffuse.b = color.b;

    dobj = child->u.dobj;
    mobj = dobj->mobj;
    material = mobj->mat;
    material->diffuse.r = color.r;
    material->diffuse.g = color.g;
    material->diffuse.b = color.b;

    player->gobj = gobj;
    player->state.is_offscreen = 0;
    player->state.ignore_offscreen = 0;
}

void ifMagnify_802FC618(void)
{
    u8* player0 = (u8*) &ifMagnify_804A1DE0 + 0x14;
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    HSD_ImageDesc* idesc;
    f32 half_height;
    f32 half_width;
    int pad;
    HSD_RectS16 viewport;

    gobj = GObj_Create(14, 15, 0);
    cobj = lb_80013B14(&ifMagnify_803F97E8);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, (GObj_RenderFunc) ifMagnify_802FBBDC, 0);
    gobj->gxlink_prios = 0x10;

    idesc = *(HSD_ImageDesc**) (player0 + 8);
    half_height = ifMagnify_804DDB4C * idesc->height;
    half_width = ifMagnify_804DDB4C * idesc->width;
    HSD_CObjSetOrtho(cobj, half_height, -half_height, -half_width, half_width);

    viewport.xmin = 0;
    viewport.xmax = (*(HSD_ImageDesc**) (player0 + 8))->width;
    viewport.ymin = 0;
    viewport.ymax = (*(HSD_ImageDesc**) (player0 + 8))->height;
    HSD_CObjSetViewport(cobj, &viewport);
    HSD_CObjSetScissorx4(cobj, (u16) viewport.xmin, (u16) viewport.xmax,
                         (u16) viewport.ymin, (u16) viewport.ymax);
}

void ifMagnify_802FC750(void)
{
    ifMagnify* base = &ifMagnify_804A1DE0;
    s32 i;
    u8* ptr;
    s32 offset;
    HSD_GObj** gobj_ptr;

    ptr = (u8*) base;
    offset = 0;
    for (i = 0; i < 6; ptr += 0x10, offset += 0x10, i++) {
        if (*(HSD_GObj**) (ptr + 0x14) != NULL) {
            gobj_ptr = (HSD_GObj**) ((u8*) base + offset + 0x14);
            HSD_GObjPLink_80390228(*gobj_ptr);
            *gobj_ptr = NULL;
        }
    }
}

void ifMagnify_802FC7C0(ifMagnify* magnify)
{
    volatile int default_val = ifMagnify_804DDB60;
    GXColor* result;

    result = Ground_801C0604();
    if (result != NULL) {
        magnify->x4 = *(int*) result;
    } else {
        magnify->x4 = default_val;
    }

    result = Ground_801C0618();
    if (result != NULL) {
        magnify->x8 = *(int*) result;
    } else {
        magnify->x8 = default_val;
    }

    result = Ground_801C062C();
    if (result != NULL) {
        magnify->xC = *(int*) result;
    } else {
        magnify->xC = default_val;
    }

    result = Ground_801C0640();
    if (result != NULL) {
        magnify->x10 = *(int*) result;
    } else {
        magnify->x10 = default_val;
    }
}

void ifMagnify_802FC870(void)
{
    HSD_Archive** archive;
    s32 i;

    memzero(&ifMagnify_804A1DE0, 0x74);
    ifMagnify_802FC7C0(&ifMagnify_804A1DE0);
    archive = ifAll_802F3690();
    lbArchive_LoadSections(*archive, (void**) &ifMagnify_804A1DE0, "lupe", 0);
    i = 0;
    do {
        ifMagnify_802FC3C0(i);
        i++;
    } while (i < 6);
    ifMagnify_802FC618();
}

void ifMagnify_802FC8E8(void)
{
    ifMagnify_804A1DE0.player[0].state.ignore_offscreen = 1;
    ifMagnify_804A1DE0.player[1].state.ignore_offscreen = 1;
    ifMagnify_804A1DE0.player[2].state.ignore_offscreen = 1;
    ifMagnify_804A1DE0.player[3].state.ignore_offscreen = 1;
    ifMagnify_804A1DE0.player[4].state.ignore_offscreen = 1;
    ifMagnify_804A1DE0.player[5].state.ignore_offscreen = 1;
}

void ifMagnify_802FC940(void)
{
    ifMagnify_804A1DE0.player[0].state.ignore_offscreen = 0;
    ifMagnify_804A1DE0.player[1].state.ignore_offscreen = 0;
    ifMagnify_804A1DE0.player[2].state.ignore_offscreen = 0;
    ifMagnify_804A1DE0.player[3].state.ignore_offscreen = 0;
    ifMagnify_804A1DE0.player[4].state.ignore_offscreen = 0;
    ifMagnify_804A1DE0.player[5].state.ignore_offscreen = 0;
}

bool ifMagnify_802FC998(s32 ply_slot)
{
    return ifMagnify_804A1DE0.player[ply_slot].state.is_offscreen;
}
