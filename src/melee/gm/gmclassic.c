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
extern u8 gmClassic_80490880[];
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

s32 gmClassic_801B2BA4(s8* arg0, u8* arg1, gm_803DDEC8Struct* arg2)
{
    s8* result;
    u8* idx_ptr;
    s32 outer;
    s8 target_char;
    s8* entry;
    s32 j;
    int cur_char;
    s32 stage1;
    gm_803DDEC8Struct* temp;
    void* xC;
    s8* count_ptr;
    s32 cnt;

    result = NULL;
    target_char = (s8) gmMainLib_8015CDC8()->c_kind;
    idx_ptr = arg1;
    outer = 0;

    goto loop_check;

loop_body:
    entry = arg0 + *idx_ptr * 6;

    for (j = 0; j < 3; j++) {
        cur_char = entry[j + 2];

        if (cur_char == 0x21) {
            continue;
        }

        if (gm_80164430(*(u16*) entry) == 0) {
            goto loop_incr;
        }
        if (gm_80164840(cur_char) == 0) {
            goto loop_incr;
        }
        if (cur_char == target_char) {
            goto loop_incr;
        }

        temp = arg2;
        while (temp->x0 != 0xD) {
            if (temp->xC != NULL) {
                if (cur_char == ((s8*) temp->xC)[2]) {
                    goto loop_incr;
                }
            }
            if (temp->xC != NULL) {
                if (cur_char == ((s8*) temp->xC)[3]) {
                    goto loop_incr;
                }
            }
            if (temp->xC != NULL) {
                if (cur_char == ((s8*) temp->xC)[4]) {
                    goto loop_incr;
                }
            }
            temp++;
        }

        temp = arg2;
        while (temp->x0 != 0xD) {
            if (temp->xC != NULL) {
                stage1 = Stage_8022519C(
                    (InternalStageId) *(u16*) entry);
                xC = temp->xC;
                if (stage1 == Stage_8022519C(
                        (InternalStageId) *(u16*) xC))
                {
                    result = entry;
                    goto loop_incr;
                }
            }
            temp++;
        }
    }

    if (entry != NULL) {
        return (s32) entry;
    }

loop_incr:
    outer++;
    idx_ptr++;

loop_check:
    count_ptr = arg0;
    cnt = 0;
    while (*(u16*) count_ptr != 0x148) {
        count_ptr += 6;
        cnt++;
    }
    if (outer < cnt) {
        goto loop_body;
    }

    if (result != NULL) {
        return (s32) result;
    }
    return 0;
}

/// #gmClassic_801B2D54

static u8 gm_804D4318[8] = { 0x01, 0x48, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00 };
static u8 gm_804D4320[8] = { 0x00, 0x52, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00 };
static u8 gm_804D4328[8] = { 0x00, 0x53, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00 };

gm_803DDEC8Struct* gmClassic_801B2D54(gm_803DDEC8Struct* arg0)
{
    gm_803DDEC8Struct* ptr;
    u8* data_base = gmClassic_80490880;
    u8* ms_base = (u8*) gm_803DDC58_MinorScenes;

    /* Pass 1: entries with x1 & 8 */
    ptr = arg0;
    while ((u8) ptr->x0 != 0xD) {
        if (ptr->x1 & 8) {
            void* result = (void*) gmClassic_801B2BA4(
                (s8*) (ms_base + 0x520), data_base + 0x80, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
        ptr++;
    }

    /* Pass 2: entries with x1 & 2, not x1 & 0x20 */
    ptr = arg0;
    while ((u8) ptr->x0 != 0xD) {
        u8 flags = ptr->x1;
        if ((flags & 2) && !(flags & 0x20)) {
            void* result = (void*) gmClassic_801B2BA4(
                (s8*) (ms_base + 0x4DC), data_base + 0x74, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
        ptr++;
    }

    /* Pass 3: entries with x1 & 0x10, not x1 & 0x20 */
    ptr = arg0;
    while ((u8) ptr->x0 != 0xD) {
        u8 flags = ptr->x1;
        if ((flags & 0x10) && !(flags & 0x20)) {
            void* result = (void*) gmClassic_801B2BA4(
                (s8*) (ms_base + 0x428), data_base + 0x54, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
        ptr++;
    }

    /* Pass 4: entries with x1 == 0 or x1 == 4 */
    ptr = arg0;
    while ((u8) ptr->x0 != 0xD) {
        u8 flags = ptr->x1;
        if (flags == 0 || flags == 4) {
            void* result = (void*) gmClassic_801B2BA4(
                (s8*) (ms_base + 0x33C), data_base + 0x2C, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
        ptr++;
    }

    /* Pass 5: entries with x1 == 0x80, switch on x2 */
    ptr = arg0;
    while ((u8) ptr->x0 != 0xD) {
        if ((u8) ptr->x1 == 0x80) {
            u8 x2val = ptr->x2;
            switch ((s32) x2val) {
            case 1:
                ptr->xC = gm_804D4318;
                break;
            case 2:
                ptr->xC = gm_804D4320;
                break;
            case 3:
                ptr->xC = gm_804D4328;
                break;
            }
        }
        ptr++;
    }

    /* Pass 6: find entry with x1 & 0x20, set xC and return */
    ptr = arg0;
    while ((u8) ptr->x0 != 0xD) {
        if (ptr->x1 & 0x20) {
            ptr->xC = (void*) (ms_base + 0x330);
            return ptr;
        }
        ptr++;
    }
    return ptr;
}

void gmClassic_OnLoad(void)
{
    u8* buf = gmClassic_80490880;
    MinorScene* ms = gm_803DDC58_MinorScenes;
    UnkAllstarData* data;
    gm_803DDEC8Struct* entry;
    int count;
    int i;
    PAD_STACK(56);

    entry = (gm_803DDEC8Struct*) ((u8*) ms + 0x270);
    while (entry->x0 != 0x0D) {
        entry->xC = NULL;
        entry++;
    }

    /* Block 1: scan offset 0x520, fill offset 0x80 */
    {
        u16* scan = (u16*) ((u8*) ms + 0x520);
        count = 0;
        while (*scan != 0x148) {
            scan = (u16*) ((u8*) scan + 6);
            count++;
        }
        for (i = 0; i < count; i++) {
            buf[i + 0x80] = i;
        }
        {
            u8* sp = buf + 0x80;
            int j;
            for (j = 0; j < count; j++) {
                u8* swap = buf + HSD_Randi(count);
                u8 tmp = *sp;
                *sp = swap[0x80];
                swap[0x80] = tmp;
                sp++;
            }
        }
    }

    /* Block 2: scan offset 0x4DC, fill offset 0x74 */
    {
        u16* scan = (u16*) ((u8*) ms + 0x4DC);
        count = 0;
        while (*scan != 0x148) {
            scan = (u16*) ((u8*) scan + 6);
            count++;
        }
        for (i = 0; i < count; i++) {
            buf[i + 0x74] = i;
        }
        {
            u8* sp = buf + 0x74;
            int j;
            for (j = 0; j < count; j++) {
                u8* swap = buf + HSD_Randi(count);
                u8 tmp = *sp;
                *sp = swap[0x74];
                swap[0x74] = tmp;
                sp++;
            }
        }
    }

    /* Block 3: scan offset 0x428, fill offset 0x54 */
    {
        u16* scan = (u16*) ((u8*) ms + 0x428);
        count = 0;
        while (*scan != 0x148) {
            scan = (u16*) ((u8*) scan + 6);
            count++;
        }
        for (i = 0; i < count; i++) {
            buf[i + 0x54] = i;
        }
        {
            u8* sp = buf + 0x54;
            int j;
            for (j = 0; j < count; j++) {
                u8* swap = buf + HSD_Randi(count);
                u8 tmp = *sp;
                *sp = swap[0x54];
                swap[0x54] = tmp;
                sp++;
            }
        }
    }

    /* Block 4: scan offset 0x33C, fill offset 0x2C */
    {
        u16* scan = (u16*) ((u8*) ms + 0x33C);
        count = 0;
        while (*scan != 0x148) {
            scan = (u16*) ((u8*) scan + 6);
            count++;
        }
        for (i = 0; i < count; i++) {
            buf[i + 0x2C] = i;
        }
        {
            u8* sp = buf + 0x2C;
            int j;
            for (j = 0; j < count; j++) {
                u8* swap = buf + HSD_Randi(count);
                u8 tmp = *sp;
                *sp = swap[0x2C];
                swap[0x2C] = tmp;
                sp++;
            }
        }
    }

    data = gm_8017EB30();
    gmMainLib_8015CDC8();
    gm_8017C984(data);

    {
        int n = 2;
        u8* p = buf + 0x20;
        do {
            p[0] = 0;
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
            p[4] = 0;
            p[5] = 0;
            p += 6;
        } while (--n);
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
    u8* sd;
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
    entry = &gmClassic_803DDEC8[(u8) gm_8017BE84(arg0->idx)];
    ad = gm_8017EB30();
    enemy_count = 0;
    ad->x0.x7 = arg0->idx;
    sd[0x0A] = entry->x0 + 1;
    sd[0x08] = ad->x0.slot;

    /* mode determination — store directly in each branch */
    if (entry->x1 & 0x80) {
        *(s32*) sd = 3;
    } else if (entry->x1 & 8) {
        *(s32*) sd = 4;
    } else if (entry->x1 & 0x10) {
        *(s32*) sd = 1;
    } else if (entry->x1 & 2) {
        *(s32*) sd = 2;
    } else {
        *(s32*) sd = 0;
    }

    /* sub-mode */
    if (*(s32*) sd != 3)
        goto submode_default;
    switch (entry->x2) {
    case 1:
        *(s32*) (sd + 4) = 1;
        break;
    case 2:
        *(s32*) (sd + 4) = 2;
        break;
    case 3:
        *(s32*) (sd + 4) = 3;
        break;
    default:
    submode_default:
        *(s32*) (sd + 4) = 0;
        break;
    }

    /* enemy char loop */
    for (i = 0; i < 3; i++) {
        sd[i + 0x10] = ((u8*) entry->xC)[i + 2];
        sd[i + 0x16] = gm_8017CD94((UnkAdventureData*) ad,
                                    (s8) ((u8*) entry->xC)[i + 2],
                                    entry->x0, i);
        gmRegSetupEnemyColorTable(ad->x0.ckind, ad->x0.color,
                                  (s8*) entry->xC + 2, sd + 0x16);
        if (entry->x1 & 4) {
            sd[i + 0x1C] = 1;
        } else {
            sd[i + 0x1C] = 0;
        }
        if (sd[i + 0x10] != 0x21) {
            enemy_count++;
        }
    }
    sd[0x0C] = enemy_count;

    /* player ckind + Zelda check */
    ally_count = 1;
    ckind = ad->x0.ckind;
    if (ckind == 0x12 && ad->x0.xC.x12 != 0) {
        sd[0x0D] = 0x13;
    } else {
        sd[0x0D] = ckind;
    }
    sd[0x13] = ad->x0.color;

    /* gm_8017DB88 call (11 args) */
    gm_8017DB88(ad->x0.xC.x24, entry->x1, ad->x0.cpu_level,
                (u8) gm_8017BE84(arg0->idx), (u8*) entry->xC + 2,
                sd[0x0D], ad->x58, ad->_5C, ad->_60, ad->_6C, ad->_70);

    /* ally loop */
    for (i = 1; i < 3; i++) {
        sd[i + 0x0D] = gm_8017DB6C((gm_8017DB6C_arg0_t*) ad->x0.xC.x24,
                                    i - 1);
        sd[i + 0x13] = gm_8017DB78((gm_8017DB6C_arg0_t*) ad->x0.xC.x24,
                                    i - 1);
        if (sd[i + 0x0D] != 0x21) {
            ally_count++;
        }
    }
    sd[0x0B] = ally_count;
    sd[0x09] = ad->x0.x4;

    /* preload cache setup */
    gc = &lbDvd_8001822C()->game_cache;
    lbDvd_80018C6C();
    gc->entries[0].char_id = sd[0x0D];
    gc->entries[0].color = ad->x0.color;
    count = 1;
    lbDvd_80018254();
    lbDvd_80018C2C(0xC7);
    lbDvd_80017700(4);

    /* enemy preload entries (3 unrolled) — pointer stepping */
    {
        s8 echar;

        ep = &gc->entries[count];

        echar = ((s8*) entry->xC)[2];
        if (echar != 0x21) {
            ep->char_id = echar;
            if (entry->x1 & 8) {
                ep->color = 0xFF;
            } else {
                ep->color = sd[0x16];
            }
            count++;
            ep++;
        }

        echar = ((s8*) entry->xC)[3];
        if (echar != 0x21) {
            ep->char_id = echar;
            if (entry->x1 & 8) {
                ep->color = 0xFF;
            } else {
                ep->color = sd[0x17];
            }
            count++;
            ep++;
        }

        echar = ((s8*) entry->xC)[4];
        if (echar != 0x21) {
            ep->char_id = echar;
            if (entry->x1 & 8) {
                ep->color = 0xFF;
            } else {
                ep->color = sd[0x18];
            }
            count++;
        }
    }

    /* ally preload entries (3 unrolled) — pointer stepping */
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

    /* stage ID for preload */
    if (entry->x1 == 0x80 && entry->x2 == 1) {
        gc->stage_id = (u16) gm_801647F8(ad->x0.ckind);
    } else if (entry->x1 == 4) {
        gc->stage_id = 0xAF;
    } else {
        gc->stage_id = *(u16*) entry->xC;
    }

    lbDvd_80018254();

    /* audio preload - player */
    audio = lbAudioAx_80026E84(ad->x0.ckind);

    /* audio preload - allies */
    for (i = 0; i < 3; i++) {
        s8 achar = ad->x0.xC.x24[i].ckind;
        if (achar != 0x21) {
            audio |= lbAudioAx_80026E84(achar);
        }
    }

    /* audio preload - enemies */
    for (i = 0; i < 3; i++) {
        s8 echar = ((s8*) entry->xC)[i + 2];
        if (echar != 0x21) {
            audio |= lbAudioAx_80026E84(echar);
            if (((s8*) entry->xC)[i + 2] == 4) {
                audio |= ((u64) 2 << 32) | 0x4000;
            }
        }
    }

    /* stage audio — no 0xAF case */
    {
        InternalStageId stage_id;
        if (entry->x1 == 0x80 && entry->x2 == 1) {
            stage_id = (u16) gm_801647F8(ad->x0.ckind);
        } else {
            stage_id = *(u16*) entry->xC;
        }
        audio |= lbAudioAx_80026EBC(stage_id);
    }

    /* final audio calls */
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
    entry = &gmClassic_803DDEC8[(u8) gm_8017BE84(arg0->idx)];
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
