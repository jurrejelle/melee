#include "gmclassic.h"

#include "gm_unsplit.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/lb/lbdvd.h>

extern UNK_T gmClassic_80470708[];
extern DebugGameOverData gmClassic_80470850;
extern UNK_T gmClassic_8047086C;
extern UNK_T gmClassic_80472AF8;
extern UNK_T gmClassic_80490880;
extern u8 gm_804908A0[];
extern UNK_T gmClassic_804D68D0;

MinorScene gm_803DDC58_MinorScenes[] = {
    {
        0x00,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x01,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x08,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x09,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x10,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x11,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x18,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x19,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x20,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x21,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x28,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x29,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x30,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x31,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x38,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x39,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x40,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x41,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x48,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x49,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x50,
        3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        0x51,
        3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x68,
        3,
        0,
        NULL,
        gmClassic_801B3F18,
        { MN_COMING_SOON, NULL, NULL },
    },
    {
        0x69,
        3,
        0,
        gmClassic_801B3D44,
        gmClassic_801B3D84,
        {
            MN_GAMEOVER,
            &gmClassic_80470850,
            &gmClassic_80470850,
        },
    },
    {
        0x70,
        3,
        0,
        gmClassic_801B3DD8,
        gmClassic_801B3E44,
        {
            MN_CSS,
            &gmClassic_80470708,
            &gmClassic_80470708,
        },
    },
    { -1 },
};

/// #gmClassic_801B2BA4

/// #gmClassic_801B2D54

/// #gmClassic_OnLoad

void gmClassic_OnInit(void)
{
    struct gmm_x0_528_t* temp_r3 = gmMainLib_8015CDC8();
    temp_r3->c_kind = 0x21;
    temp_r3->color = 0;
    temp_r3->stocks = 3;
    temp_r3->cpu_level = 0;
    temp_r3->x4 = 0x78;
    temp_r3->x5 = 0;
}

/// #gmClassic_801B3500

void gmClassic_801B3A34(MinorScene* arg0)
{
    StartMeleeData* temp_r30;
    gm_803DDEC8Struct* temp_r31;
    UnkAllstarData* temp_r29;
    u16 var_r27;
    u8 flags;
    u8 temp_r28;
    int idx_val;
    s32 sp8;
    s32 spC;

    PAD_STACK(8);

    temp_r30 = gm_801A427C(arg0);
    temp_r31 = &gmClassic_803DDEC8[(u8) gm_8017BE84(arg0->idx)];
    temp_r29 = gm_8017EB30();
    var_r27 = *(u16*) temp_r31->xC;
    if (temp_r31->x1 == 0x80 && temp_r31->x2 == 1) {
        var_r27 = gm_801647F8(temp_r29->x0.ckind);
    }
    flags = temp_r31->x1;
    if (flags == 4) {
        var_r27 = 0xAF;
    }
    temp_r29->x0.x8 = flags;
    temp_r29->x0.x9 = temp_r31->x2;
    temp_r29->x0.xB = temp_r31->x8;
    idx_val = (u16) gm_8017BE84(arg0->idx) - 1;
    temp_r28 = gm_804908A0[idx_val];
    sp8 = (s32)(u16) gm_8017BE84(arg0->idx);
    spC = (s32) temp_r28;
    gm_8017CE34(temp_r30, (UnkAdventureData*) temp_r29,
                (s8*) temp_r31->xC + 2, temp_r31->x6, 1, 0,
                temp_r31->x4, (int) var_r27, sp8, spC);
    gm_8016F088(temp_r30);
}

/// #gmClassic_801B3B40

void gmClassic_801B3D44(MinorScene* scene)
{
    struct DebugGameOverData* temp_r31 = gm_801A427C(scene);
    gm_8017C9A8(temp_r31, &gm_8017EB30()->x0, 1);
}

void gmClassic_801B3D84(MinorScene* scene)
{
    DebugGameOverData* temp_r30 = gm_801A4284(scene);
    gm_8017CA38(temp_r30, &gm_8017EB30()->x0, gmMainLib_8015CDC8(), 1);
}

void gmClassic_801B3DD8(MinorScene* scene)
{
    CSSData* css = gm_801A427C(scene);
    struct gmm_x0_528_t* temp_r31 = gmMainLib_8015CDC8();
    gm_801B06B0(css, 0xB, temp_r31->c_kind, temp_r31->stocks, temp_r31->color,
                temp_r31->x4, temp_r31->cpu_level, gm_8017EB30()->x0.slot);
    lbDvd_800174BC();
}

void gmClassic_801B3E44(MinorScene* scene)
{
    CSSData* temp_r30 = gm_801A4284(scene);
    gmm_x0_528_t* temp_r29 = gmMainLib_8015CDC8();
    UnkAllstarData* temp_r31 = gm_8017EB30();
    gm_803DDEC8Struct* r4 = gmClassic_803DDEC8;
    if (temp_r30->pending_scene_change == 2) {
        // This only happens when, instead of pressing start to begin the game,
        // we press back to exit.
        gm_801A42F8(1);
        return;
    }
    gm_801B0730(temp_r30, &temp_r29->c_kind, &temp_r29->stocks,
                &temp_r29->color, &temp_r29->x4, &temp_r29->cpu_level);
    temp_r31->x0.ckind = temp_r29->c_kind;
    temp_r31->x0.color = temp_r29->color;
    temp_r31->x0.cpu_level = temp_r29->cpu_level;
    temp_r31->x0.stocks = temp_r29->stocks;
    temp_r31->x0.x4 = temp_r29->x4;
    gmClassic_801B2D54(r4);
    gm_SetScenePendingMinor(temp_r29->x5 << 3);
    gm_80168F88();
}

void gmClassic_801B3F18(MinorScene* scene)
{
    gm_801A42E8(MJ_MENU);
    gm_801A42D4();
}
