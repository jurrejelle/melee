#include "ifmagnify.h"

#include "gr/ground.h"
#include "if/ifall.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"

#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/tobj.h>

/* 3F97E8 */ extern HSD_CameraDescPerspective ifMagnify_803F97E8;
/* 4DDB08 */ extern f32 ifMagnify_804DDB08;
/* 4DDB28 */ extern f32 ifMagnify_804DDB28;
/* 4DDB2C */ extern f32 ifMagnify_804DDB2C;
/* 4DDB30 */ extern f32 ifMagnify_804DDB30;
/* 4DDB34 */ extern f32 ifMagnify_804DDB34;
/* 4DDB38 */ extern f32 ifMagnify_804DDB38;
/* 4DDB3C */ extern f32 ifMagnify_804DDB3C;
/* 4DDB4C */ extern f32 ifMagnify_804DDB4C;
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

/// #ifMagnify_802FB8C0

/// #ifMagnify_802FBBDC

void ifMagnify_802FC3BC(void) {}

/// #ifMagnify_802FC3C0

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
