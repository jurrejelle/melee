#include "gmclassic.h"

#include "gm_unsplit.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>
#include <sysdolphin/baselib/random.h>

extern UNK_T gmClassic_80470708[];
extern DebugGameOverData gmClassic_80470850;
extern UNK_T gmClassic_8047086C;
extern UNK_T gmClassic_80472AF8;
extern u8 gm_804908A0[];
extern UNK_T gmClassic_804D68D0;

typedef struct gmClassicMatchup {
    /* 0x00 */ u16 x00;
    /* 0x02 */ s8 x02[3];
    /* 0x05 */ u8 x05;
} gmClassicMatchup;
STATIC_ASSERT(sizeof(gmClassicMatchup) == 6);

typedef struct gmClassicMatchupData {
    /* 0x00 */ gmClassicMatchup x00;
    /* 0x06 */ u8 pad_06[2];
} gmClassicMatchupData;
STATIC_ASSERT(sizeof(gmClassicMatchupData) == 8);

typedef struct gmClassicIntroData {
    /* 0x00 */ s32 x00;
    /* 0x04 */ s32 x04;
    /* 0x08 */ u8 x08;
    /* 0x09 */ u8 x09;
    /* 0x0A */ u8 x0A;
    /* 0x0B */ u8 x0B;
    /* 0x0C */ u8 x0C;
    /* 0x0D */ u8 x0D[3];
    /* 0x10 */ u8 x10[3];
    /* 0x13 */ u8 x13[3];
    /* 0x16 */ u8 x16[3];
    /* 0x19 */ u8 x19[3];
    /* 0x1C */ u8 x1C[3];
    /* 0x1F */ u8 x1F;
} gmClassicIntroData;
STATIC_ASSERT(sizeof(gmClassicIntroData) == 0x20);

typedef struct gmClassic_80490880Data {
    /* 0x00 */ gmClassicIntroData x00;
    /* 0x20 */ u8 x20[0x0C];
    /* 0x2C */ u8 x2C[0x28];
    /* 0x54 */ u8 x54[0x20];
    /* 0x74 */ u8 x74[0x0C];
    /* 0x80 */ u8 x80[0x10];
} gmClassic_80490880Data;
STATIC_ASSERT(sizeof(gmClassic_80490880Data) == 0x90);

typedef struct gmClassic_803DDEC8Data {
    /* 0x000 */ gm_803DDEC8Struct x00[12];
    /* 0x0C0 */ gmClassicMatchup x0C0[2];
    /* 0x0CC */ gmClassicMatchup x0CC[39];
    /* 0x1B6 */ u8 pad_1B6[2];
    /* 0x1B8 */ gmClassicMatchup x1B8[30];
    /* 0x26C */ gmClassicMatchup x26C[11];
    /* 0x2AE */ u8 pad_2AE[2];
    /* 0x2B0 */ gmClassicMatchup x2B0[10];
    /* 0x2EC */ u8 pad_2EC[4];
} gmClassic_803DDEC8Data;
STATIC_ASSERT(sizeof(gmClassic_803DDEC8Data) == 0x2F0);

extern gmClassic_80490880Data gmClassic_80490880;
extern gmClassic_803DDEC8Data gmClassic_803DDEC8;

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

static void gmClassic_InitMatchupOrder(const gmClassicMatchup* matchups,
                                       u8* order)
{
    s32 count;
    s32 i;

    for (count = 0; matchups[count].x00 != 0x148; count++) {
    }

    for (i = 0; i < count; i++) {
        order[i] = i;
    }

    for (i = 0; i < count; i++) {
        s32 swap_idx = HSD_Randi(count);
        u8 tmp = order[i];
        order[i] = order[swap_idx];
        order[swap_idx] = tmp;
    }
}

static gmClassicMatchup* gmClassic_801B2BA4(gmClassicMatchup* arg0, u8* arg1,
                                            gm_803DDEC8Struct* arg2)
{
    gmClassicMatchup* result;
    gmClassicMatchup* entry;
    s32 outer;
    s8 target_char;
    int cur_char;
    s32 stage1;
    gm_803DDEC8Struct* temp;
    s32 j;
    s32 count;
    s32 cnt;
    bool skip_entry;

    result = NULL;
    target_char = (s8) gmMainLib_8015CDC8()->c_kind;
    outer = 0;

    while (true) {
        entry = &arg0[*arg1];
        skip_entry = false;
        for (j = 0; j < 3; j++) {
            cur_char = entry->x02[j];

            if (cur_char == 0x21) {
                continue;
            }

            if (gm_80164430(entry->x00) == 0) {
                skip_entry = true;
                break;
            }
            if (gm_80164840(cur_char) == 0) {
                skip_entry = true;
                break;
            }
            if (cur_char == target_char) {
                skip_entry = true;
                break;
            }

            for (temp = arg2; temp->x0 != 0xD; temp++) {
                if (temp->xC != NULL) {
                    if (cur_char == ((gmClassicMatchup*) temp->xC)->x02[0]) {
                        skip_entry = true;
                        break;
                    }
                }
                if (temp->xC != NULL) {
                    if (cur_char == ((gmClassicMatchup*) temp->xC)->x02[1]) {
                        skip_entry = true;
                        break;
                    }
                }
                if (temp->xC != NULL) {
                    if (cur_char == ((gmClassicMatchup*) temp->xC)->x02[2]) {
                        skip_entry = true;
                        break;
                    }
                }
            }

            if (skip_entry) {
                break;
            }

            for (temp = arg2; temp->x0 != 0xD; temp++) {
                if (temp->xC != NULL) {
                    stage1 = Stage_8022519C((InternalStageId) entry->x00);
                    if (stage1 ==
                        Stage_8022519C(
                            (InternalStageId) ((gmClassicMatchup*) temp->xC)
                                ->x00))
                    {
                        result = entry;
                        skip_entry = true;
                        break;
                    }
                }
            }

            if (skip_entry) {
                break;
            }
        }

        if (!skip_entry) {
            return entry;
        }

        outer++;
        arg1++;
        cnt = 0;
        for (count = 0; arg0[count].x00 != 0x148; count++) {
            cnt++;
        }
        if (outer >= cnt) {
            break;
        }
    }

    return result;
}

static gmClassicMatchupData gm_804D4318 = { { 0x148, { 0x21, 0x21, 0x21 }, 0 },
                                            { 0, 0 } };
static gmClassicMatchupData gm_804D4320 = { { 0x052, { 0x21, 0x21, 0x21 }, 0 },
                                            { 0, 0 } };
static gmClassicMatchupData gm_804D4328 = { { 0x053, { 0x21, 0x21, 0x21 }, 0 },
                                            { 0, 0 } };

static gm_803DDEC8Struct* gmClassic_801B2D54(gm_803DDEC8Struct* arg0)
{
    gm_803DDEC8Struct* ptr;

    for (ptr = arg0; (u8) ptr->x0 != 0xD; ptr++) {
        if (ptr->x1 & 8) {
            gmClassicMatchup* result =
                gmClassic_801B2BA4(gmClassic_803DDEC8.x2B0,
                                   gmClassic_80490880.x80, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
    }

    for (ptr = arg0; (u8) ptr->x0 != 0xD; ptr++) {
        u8 flags = ptr->x1;
        if ((flags & 2) && !(flags & 0x20)) {
            gmClassicMatchup* result =
                gmClassic_801B2BA4(gmClassic_803DDEC8.x26C,
                                   gmClassic_80490880.x74, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
    }

    for (ptr = arg0; (u8) ptr->x0 != 0xD; ptr++) {
        u8 flags = ptr->x1;
        if ((flags & 0x10) && !(flags & 0x20)) {
            gmClassicMatchup* result =
                gmClassic_801B2BA4(gmClassic_803DDEC8.x1B8,
                                   gmClassic_80490880.x54, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
    }

    for (ptr = arg0; (u8) ptr->x0 != 0xD; ptr++) {
        u8 flags = ptr->x1;
        if (flags == 0 || flags == 4) {
            gmClassicMatchup* result =
                gmClassic_801B2BA4(gmClassic_803DDEC8.x0CC,
                                   gmClassic_80490880.x2C, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
    }

    for (ptr = arg0; (u8) ptr->x0 != 0xD; ptr++) {
        if ((u8) ptr->x1 == 0x80) {
            u8 x2val = ptr->x2;
            switch ((s32) x2val) {
            case 1:
                ptr->xC = &gm_804D4318.x00;
                break;
            case 2:
                ptr->xC = &gm_804D4320.x00;
                break;
            case 3:
                ptr->xC = &gm_804D4328.x00;
                break;
            }
        }
    }

    for (ptr = arg0; (u8) ptr->x0 != 0xD; ptr++) {
        if (ptr->x1 & 0x20) {
            ptr->xC = gmClassic_803DDEC8.x0C0;
            return ptr;
        }
    }
    return ptr;
}

void gmClassic_OnLoad(void)
{
    UnkAllstarData* data;
    gm_803DDEC8Struct* entry;
    s32 i;

    for (entry = gmClassic_803DDEC8.x00; entry->x0 != 0x0D; entry++) {
        entry->xC = NULL;
    }

    gmClassic_InitMatchupOrder(gmClassic_803DDEC8.x2B0, gmClassic_80490880.x80);
    gmClassic_InitMatchupOrder(gmClassic_803DDEC8.x26C, gmClassic_80490880.x74);
    gmClassic_InitMatchupOrder(gmClassic_803DDEC8.x1B8, gmClassic_80490880.x54);
    gmClassic_InitMatchupOrder(gmClassic_803DDEC8.x0CC, gmClassic_80490880.x2C);

    data = gm_8017EB30();
    gmMainLib_8015CDC8();
    gm_8017C984(data);

    for (i = 0; i < 0xC; i++) {
        gm_804908A0[i] = 0;
    }

    gm_8017DB58(data->x0.xC.x24);
    data->x0.slot = gm_801677F0();
    data->x48 = gm_8017EB3C;
    data->x4C = gm_8017EB64;
    data->x50 = gm_8017EBCC;
    data->x54 = gm_8017EB98;
    data->x64 = gm_8017ED3C;
    data->x68 = gm_8017ED8C;
    data->x58 = (u32) gm_8017ECA0;
    data->_5C = (u32) gm_8017ED08;
    data->_60 = (u32) gm_8017ECD4;
    data->_6C = (u32) gm_8017EC00;
    data->_70 = (u32) gm_8017EC50;

    gm_SetSceneMinor(0x70U);
    gm_80172174();
    Ground_801C5A28();
}

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

void gmClassic_801B3500(MinorScene* arg0)
{
    gmClassicIntroData* sd;
    gm_803DDEC8Struct* entry;
    UnkAllstarData* ad;
    int enemy_count;
    int ally_count;
    int i;
    struct GameCache* gc;
    int count;
    u64 audio;
    s8 ckind;
    PreloadCacheSceneEntry* ep;

    sd = gm_801A427C(arg0);
    entry = &gmClassic_803DDEC8.x00[(u8) gm_8017BE84(arg0->idx)];
    ad = gm_8017EB30();
    enemy_count = 0;
    ad->x0.x7 = arg0->idx;
    sd->x0A = entry->x0 + 1;
    sd->x08 = ad->x0.slot;

    if (entry->x1 & 0x80) {
        sd->x00 = 3;
    } else if (entry->x1 & 8) {
        sd->x00 = 4;
    } else if (entry->x1 & 0x10) {
        sd->x00 = 1;
    } else if (entry->x1 & 2) {
        sd->x00 = 2;
    } else {
        sd->x00 = 0;
    }

    if (sd->x00 == 3) {
        switch (entry->x2) {
        case 1:
            sd->x04 = 1;
            break;
        case 2:
            sd->x04 = 2;
            break;
        case 3:
            sd->x04 = 3;
            break;
        default:
            sd->x04 = 0;
            break;
        }
    } else {
        sd->x04 = 0;
    }

    for (i = 0; i < 3; i++) {
        sd->x10[i] = ((gmClassicMatchup*) entry->xC)->x02[i];
        sd->x16[i] = gm_8017CD94((UnkAdventureData*) ad,
                                 ((gmClassicMatchup*) entry->xC)->x02[i],
                                 entry->x0, i);
        gmRegSetupEnemyColorTable(ad->x0.ckind, ad->x0.color,
                                  ((gmClassicMatchup*) entry->xC)->x02,
                                  sd->x16);
        if (entry->x1 & 4) {
            sd->x1C[i] = 1;
        } else {
            sd->x1C[i] = 0;
        }
        if (sd->x10[i] != 0x21) {
            enemy_count++;
        }
    }
    sd->x0C = enemy_count;

    ally_count = 1;
    ckind = ad->x0.ckind;
    if (ckind == 0x12 && ad->x0.xC.x12 != 0) {
        sd->x0D[0] = 0x13;
    } else {
        sd->x0D[0] = ckind;
    }
    sd->x13[0] = ad->x0.color;

    gm_8017DB88(ad->x0.xC.x24, entry->x1, ad->x0.cpu_level,
                (u8) gm_8017BE84(arg0->idx), sd->x10, sd->x0D[0],
                (u8 (*)(s32, s32, u8)) ad->x58,
                (u8 (*)(s32, s32, u8)) ad->_5C,
                (u8 (*)(s32, s32, u8)) ad->_60,
                (f32 (*)(s32, s32)) ad->_6C,
                (f32 (*)(s32, s32)) ad->_70);

    for (i = 1; i < 3; i++) {
        sd->x0D[i] =
            gm_8017DB6C((gm_8017DB6C_arg0_t*) ad->x0.xC.x24, i - 1);
        sd->x13[i] =
            gm_8017DB78((gm_8017DB6C_arg0_t*) ad->x0.xC.x24, i - 1);
        if (sd->x0D[i] != 0x21) {
            ally_count++;
        }
    }
    sd->x0B = ally_count;
    sd->x09 = ad->x0.x4;

    gc = &lbDvd_8001822C()->game_cache;
    lbDvd_80018C6C();
    gc->entries[0].char_id = sd->x0D[0];
    gc->entries[0].color = ad->x0.color;
    count = 1;
    lbDvd_80018254();
    lbDvd_80018C2C(0xC7);
    lbDvd_80017700(4);

    {
        s8 echar;

        ep = &gc->entries[count];

        echar = ((gmClassicMatchup*) entry->xC)->x02[0];
        if (echar != 0x21) {
            ep->char_id = echar;
            if (entry->x1 & 8) {
                ep->color = 0xFF;
            } else {
                ep->color = sd->x16[0];
            }
            count++;
            ep++;
        }

        echar = ((gmClassicMatchup*) entry->xC)->x02[1];
        if (echar != 0x21) {
            ep->char_id = echar;
            if (entry->x1 & 8) {
                ep->color = 0xFF;
            } else {
                ep->color = sd->x16[1];
            }
            count++;
            ep++;
        }

        echar = ((gmClassicMatchup*) entry->xC)->x02[2];
        if (echar != 0x21) {
            ep->char_id = echar;
            if (entry->x1 & 8) {
                ep->color = 0xFF;
            } else {
                ep->color = sd->x16[2];
            }
            count++;
        }
    }

    {
        s8 achar;
        Unk1PData_x24* ap;

        ep = &gc->entries[count];
        ap = ad->x0.xC.x24;

        achar = ap->ckind;
        if (achar != 0x21) {
            ep->char_id = achar;
            ep->color = ap->x1;
            ep++;
        }
        ap++;

        achar = ap->ckind;
        if (achar != 0x21) {
            ep->char_id = achar;
            ep->color = ap->x1;
            ep++;
        }
        ap++;

        achar = ap->ckind;
        if (achar != 0x21) {
            ep->char_id = achar;
            ep->color = ap->x1;
        }
    }

    lbDvd_80018254();

    if (entry->x1 == 0x80 && entry->x2 == 1) {
        gc->stage_id = (u16) gm_801647F8(ad->x0.ckind);
    } else if (entry->x1 == 4) {
        gc->stage_id = 0xAF;
    } else {
        gc->stage_id = ((gmClassicMatchup*) entry->xC)->x00;
    }

    lbDvd_80018254();

    audio = lbAudioAx_80026E84(ad->x0.ckind);

    for (i = 0; i < 3; i++) {
        s8 achar = ad->x0.xC.x24[i].ckind;
        if (achar != 0x21) {
            audio |= lbAudioAx_80026E84(achar);
        }
    }

    for (i = 0; i < 3; i++) {
        s8 echar = ((gmClassicMatchup*) entry->xC)->x02[i];
        if (echar != 0x21) {
            audio |= lbAudioAx_80026E84(echar);
            if (((gmClassicMatchup*) entry->xC)->x02[i] == 4) {
                audio |= ((u64) 2 << 32) | 0x4000;
            }
        }
    }

    {
        InternalStageId stage_id;
        if (entry->x1 == 0x80 && entry->x2 == 1) {
            stage_id = (u16) gm_801647F8(ad->x0.ckind);
        } else {
            stage_id = ((gmClassicMatchup*) entry->xC)->x00;
        }
        audio |= lbAudioAx_80026EBC(stage_id);
    }

    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC, audio);
    lbAudioAx_80027168();
}

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
    temp_r31 = &gmClassic_803DDEC8.x00[(u8) gm_8017BE84(arg0->idx)];
    temp_r29 = gm_8017EB30();
    var_r27 = ((gmClassicMatchup*) temp_r31->xC)->x00;
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
                ((gmClassicMatchup*) temp_r31->xC)->x02, temp_r31->x6, 1, 0,
                temp_r31->x4, (int) var_r27, sp8, spC);
    gm_8016F088(temp_r30);
}

void gmClassic_801B3B40(MinorScene* arg0)
{
    MatchExitInfo* mei;
    UnkAllstarData* asd;
    s32 exit_result;
    gm_803DDEC8Struct* entry;
    u8 unused[16];
    s32 sp18;
    s32 sp14;
    s32 idx;
    u8 char_id;
    u32* time_ptr;
    s32* best_ptr;
    s32 mask;
    PAD_STACK(8);

    mei = (MatchExitInfo*) gm_801A4284(arg0);
    asd = gm_8017EB30();
    entry = &gmClassic_803DDEC8.x00[(u8) gm_8017BE84(arg0->idx)];
    exit_result = mei->x8;
    idx = (u16) gm_8017BE84(arg0->idx) - 1;

    if (exit_result != 0) {
        gm_804908A0[idx] = 2;
    } else {
        gm_804908A0[idx] = 1;
    }

    if (gm_8017D7AC(mei, &asd->x0, 0x69) != 0 && entry[1].x0 == 0xD) {
        gm_8017CBAC((UnkAdventureData*) asd, gmMainLib_8015CDC8(), 0x15);
    }

    if (entry->x1 == 0x80 && entry->x2 == 1) {
        char_id = gm_80164024((u8) asd->x0.ckind);
        time_ptr = gmMainLib_8015D438(char_id);
        best_ptr = gmMainLib_8015D450(char_id);
        Ground_801C1DE4(&sp18, &sp14);

        if (sp18 == 0) {
            mask = 1 << char_id;
            if (!(mask & gmMainLib_8015EDBC()->x8)) {
                *best_ptr = (s32) mei->match_end.frame_count;
                gmMainLib_8015EDBC()->x8 |= mask;
            } else {
                if ((u32) *best_ptr > mei->match_end.frame_count) {
                    *best_ptr = (s32) mei->match_end.frame_count;
                }
            }
            gmMainLib_8015ED98()->x1C |= mask;
            gmMainLib_8015EDB0()->x4 |= mask;
        }

        if (gmMainLib_8015D48C(char_id) == 0) {
            if (sp18 == 0) {
                gmMainLib_8015D4E8(char_id, 1);
                *time_ptr = mei->match_end.frame_count;
                return;
            }
            {
                u32 diff = sp14 - sp18;
                if ((u32) *time_ptr < diff) {
                    *time_ptr = diff;
                }
            }
        } else if (sp18 == 0) {
            if ((u32) *time_ptr > mei->match_end.frame_count) {
                *time_ptr = mei->match_end.frame_count;
            }
        }
    }
}

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
    gm_803DDEC8Struct* r4 = gmClassic_803DDEC8.x00;
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
