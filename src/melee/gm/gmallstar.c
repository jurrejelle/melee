#include "gmallstar.h"

#include "gm/gmallstar.static.h"

#include "gm_unsplit.h"
#include "gmregcommon.h"

#include "baselib/random.h"
#include "gr/ground.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbdvd.h>

extern CSSData gmClassic_80470708;
extern DebugGameOverData gmClassic_80470850;
extern MatchExitInfo gmClassic_8047086C;
extern StartMeleeData gmClassic_80472AF8;

MinorScene gm_803DE930_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        1,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        8,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        9,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x11,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x19,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x21,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x29,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x31,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x39,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x41,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x49,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
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
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x51,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x58,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x59,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            MN_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x60,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
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
        gm_801B607C,
        {
            MN_COMING_SOON,
            NULL,
            NULL,
        },
    },
    {
        0x69,
        3,
        0,
        gm_801B5EB4,
        gm_801B5EE4,
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
        gm_801B5F50,
        gm_801B5FB4,
        {
            MN_CSS,
            &gmClassic_80470708,
            &gmClassic_80470708,
        },
    },
    {
        -1,
    },
};

static gm_803DEBE8_t gm_803DEBE8[52] = {
    { 0xB1, 0xB1, 0, 8 },
    { 0xB2, 0xB2, 0, 1 },
    { 0xB3, 0xB3, 0, 6 },
    { 0xB4, 0xB4, 0, 0x10 },
    { 0xB5, 0xB5, 0, 0x11 },
    { 0xB6, 0xB6, 0, 4 },
    { 0xB7, 0xB7, 0, 2 },
    { 0xB8, 0xB8, 0, 0xD },
    { 0xB9, 0xB9, 0, 7 },
    { 0xBA, 0xBA, 0, 0 },
    { 0xBB, 0xBB, 0, 0xB },
    { 0xBC, 0xBC, 0, 0xF },
    { 0xBD, 0xBD, 0, 0xE },
    { 0xBE, 0xBE, 0, 0xC },
    { 0xBF, 0xBF, 0, 0x12 },
    { 0xC0, 0xC0, 0, 9 },
    { 0xC1, 0xC1, 0, 0xA },
    { 0xC2, 0xC2, 0, 5 },
    { 0xC3, 0xC3, 0, 0x16 },
    { 0xC4, 0xC4, 0, 0x15 },
    { 0xC5, 0xC5, 0, 0x14 },
    { 0xC6, 0xC6, 0, 0x18 },
    { 0xC7, 0xC7, 0, 0x17 },
    { 0xC9, 0xC9, 0, 0x19 },
    { 0xC8, 0xC8, 0, 3 },
    /* round data (AllstarRoundInfo[13]) encoded as raw bytes */
    { 0, 0, 0, 0 }, { 0, 0, 0, 1 },
    { 0, 0, 0, 1 }, { 0, 0, 0, 1 },
    { 0, 0, 0, 2 }, { 0, 0, 0, 1 },
    { 0, 0, 0, 3 }, { 0, 0, 0, 1 },
    { 0, 0, 0, 4 }, { 0, 0, 0, 2 },
    { 0, 0, 0, 6 }, { 0, 0, 0, 2 },
    { 0, 0, 0, 8 }, { 0, 0, 0, 2 },
    { 0, 0, 0, 10 }, { 0, 0, 0, 2 },
    { 0, 0, 0, 12 }, { 0, 0, 0, 3 },
    { 0, 0, 0, 15 }, { 0, 0, 0, 3 },
    { 0, 0, 0, 18 }, { 0, 0, 0, 3 },
    { 0, 0, 0, 21 }, { 0, 0, 0, 3 },
    { 0, 0, 0, 24 }, { 0, 0, 0, 1 },
    /* trailing pad */
    { 0, 0, 0, 0 },
};

gm_80490940_t gm_80490940[5];

/// #gm_801B5324

/// #gm_801B5624

void gm_801B59AC(MinorScene* arg0)
{
    u8* base = (u8*) gm_803DE930_MinorScenes;
    MatchExitInfo* exit = gm_801A4284(arg0);
    u8 idx = arg0->idx;
    s32 result = exit->x8;
    UnkAllstarData* data = &gm_80473A18;
    u16 round = gm_8017BE84(idx);
    u32 opp_start = ((AllstarRoundInfo*)(base + 0x31C))[round].start;
    u32 opp_idx = ((u32)((u8*)&((gm_803DEBE8_t*)base)[opp_start] + 0x2B8) - (u32)(base + 0x2B8)) / sizeof(gm_803DEBE8_t);

    if (result != 0) {
        ((u8*) gm_80490940)[opp_idx] = 2;
    } else {
        ((u8*) gm_80490940)[opp_idx] = 1;
    }
    data->x74 = exit->match_end.player_standings[0].percent;
    exit->match_end.frame_count;
    data->x9C += exit->match_end.frame_count;
    if (gm_8017D7AC(exit, &data->x0, 0x69) != 0 &&
        (u8) arg0->idx == 0x60)
    {
        gm_8017CBAC((UnkAdventureData*) data, gmMainLib_8015CDE0(), 0x17);
    }
}

void fn_801B5AA8(int arg0)
{
    lbBgFlash_8002063C(0x78);
}

/// #gm_801B5ACC

void gm_801B5E7C(MinorScene* arg0)
{
    MatchExitInfo* exit = gm_801A4284(arg0);
    gm_80473A18.x74 = exit->match_end.player_standings[0].percent;
    gm_8017D7AC(exit, &gm_80473A18.x0, 0x69);
}

void gm_801B5EB4(MinorScene* arg0)
{
    DebugGameOverData* data = gm_801A427C(arg0);
    gm_8017C9A8(data, &gm_80473A18.x0, 2);
}

void gm_801B5EE4(MinorScene* arg0)
{
    DebugGameOverData* data = gm_801A4284(arg0);
    UnkAllstarData* r30 = &gm_80473A18;
    gm_8017CA38(data, &r30->x0, gmMainLib_8015CDE0(), 2);
    if (data->xC != 0) {
        r30->x74 = 0;
    }
}

void gm_801B5F50(MinorScene* arg0)
{
    CSSData* temp_r31;
    struct gmm_x0_528_t* temp_r3;

    temp_r31 = gm_801A427C(arg0);
    temp_r3 = gmMainLib_8015CDE0();
    gm_801B06B0(temp_r31, 0xD, temp_r3->c_kind, temp_r3->stocks,
                temp_r3->color, temp_r3->x4, temp_r3->cpu_level,
                gm_80473A18.x0.slot);
    lbDvd_800174BC();
}

/// #gm_801B5F50

void gm_801B5FB4(MinorScene* arg0)
{
    CSSData* temp_r31 = gm_801A4284(arg0);
    struct gmm_x0_528_t* temp_r30 = gmMainLib_8015CDE0();
    UnkAllstarData* r29 = &gm_80473A18;

    if (temp_r31->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_801B0730(temp_r31, &temp_r30->c_kind, &temp_r30->stocks,
                &temp_r30->color, &temp_r30->x4, &temp_r30->cpu_level);
    r29->x0.ckind = temp_r30->c_kind;
    r29->x0.color = temp_r30->color;
    r29->x0.cpu_level = temp_r30->cpu_level;
    r29->x0.stocks = temp_r30->stocks;
    r29->x0.x4 = temp_r30->x4;
    gm_SetScenePendingMinor((temp_r30->x5 * 8) & 0xF8);
    gm_80168F88();
    gm_801B5324(r29, temp_r30->x5);
}

void gm_801B607C(MinorScene* unused)
{
    gm_801A42E8(MJ_MENU);
    gm_801A42D4();
}

void gm_801B60A4_OnLoad(void)
{
    UnkAllstarData* data;
    gm_803DEBE8_t* var_r29;
    gm_803DEBE8_t* var_r30;
    u32 var_r28;
    int temp;
    gm_803DEBE8_t tmp;

    data = &gm_80473A18;
    gmMainLib_8015CDE0();
    gm_8017C984(data);

    {
        gm_80490940_t* p = gm_80490940;
        char* pp = (char*) p;
        int i = 25;
        while (i--) {
            *(pp++) = 0;
        }
    }

    gm_8017DB58(data->x0.xC.x24);
    data->x0.slot = gm_801677F0();
    data->x48 = gm_8018A160;
    data->x4C = gm_8018A228;
    data->x50 = gm_8018A290;
    data->x54 = gm_8018A25C;
    data->x58 = 0;
    data->x64 = gm_8018A2C4;
    var_r29 = gm_803DEBE8;
    data->x68 = gm_8018A314;
    var_r30 = var_r29;
    for (var_r28 = 0; var_r28 < 25; var_r28++) {
        var_r30->x2 = *((&var_r30->x0) + HSD_Randi(2));
        var_r30++;
    }

    var_r30 = gm_803DEBE8;
    for (var_r28 = 0; var_r28 < 0x17; var_r28++) {
        gm_803DEBE8_t* swap = &var_r30[var_r28 + HSD_Randi(0x18 - var_r28)];
        tmp = *var_r29;
        *var_r29 = *swap;
        var_r29++;
        *swap = tmp;
    }

    data->x74 = 0;
    {
        UnkAllstarData* p = &gm_80473A18;
        int i = 0x18;
        p->x9C = 0;
        temp = 0x21;
        p->x76[0] = temp;
        p->x76[1] = temp;
        p->x76[2] = temp;
        p->x76[3] = temp;
        p->x76[4] = temp;
        p->x76[5] = temp;
        p->x76[6] = temp;
        p->x76[7] = temp;
        p->x76[8] = temp;
        p->x76[9] = temp;
        p->x76[0xA] = temp;
        p->x76[0xB] = temp;
        p->x76[0xC] = temp;
        p->x76[0xD] = temp;
        p->x76[0xE] = temp;
        p->x76[0xF] = temp;
        p->x76[0x10] = temp;
        p->x76[0x11] = temp;
        p->x76[0x12] = temp;
        p->x76[0x13] = temp;
        p->x76[0x14] = temp;
        p->x76[0x15] = temp;
        p->x76[0x16] = temp;
        p->x76[0x17] = temp;

        {
            u8* q = ((u8*) p) + i;
            int count = 0x1A - i;
            if (i < 0x1A) {
                do {
                    *(q++ + 0x76) = 0x21;
                } while (--count != 0);
            }
        }
    }

    {
        u8* p = gm_80473A18.x90;
        p[0] = 1;
        p[1] = 1;
        p[2] = 1;
        p[3] = 1;
    }

    gm_SetSceneMinor(0x70U);
    gm_80172174();
    Ground_801C5A28();
}

void gm_801B62D8_OnInit(void)
{
    struct gmm_x0_528_t* temp_r3 = gmMainLib_8015CDE0();
    temp_r3->c_kind = CHKIND_NONE;
    temp_r3->color = 0;
    temp_r3->stocks = 1;
    temp_r3->cpu_level = 0;
    temp_r3->x4 = 0x78;
    temp_r3->x5 = 0;
}
