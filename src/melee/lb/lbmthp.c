#include "lbmthp.static.h"

#include "baselib/memory.h"
#include "baselib/video.h"
#include "lb/lbfile.h"

#include <Runtime/runtime.h>
#include <dolphin/dvd.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/os/OSCache.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <melee/lb/lbanim.h>
#include <melee/lb/types.h>

/// #fn_8001E910

s32 fn_8001EB14(THPDecComp* data, const char* path)
{
    THPInit();
    data->unk_128 = DVDConvertPathToEntrynum(path);
    lbFile_800161C4(data->unk_128, 0, (u32) data, 0x40, 0x21, 1);

    data->unk_40 = data->unk_1C;
    data->width = data->unk_10;
    data->height = data->unk_14;
    data->unk_100 = data->unk_0C;

    if (data->unk_24 != 0) {
        OSReport("Warning : frame offsets not supported\n");
    }

    if (data->unk_08 > 2) {
        OSReport("Warning : file format is newer than player\n");
    }

    data->unk_11C = 1;
    data->unk_6C = 1;
    data->unk_110 = 0;
    data->unk_70 = 1;
    data->unk_134 = 0;
    data->unk_130 = 0;

    return 1;
}

#define ALIGN_32(x) (((x) + 0x1F) & ~0x1F)

s32 fn_8001EBF0(THPDecComp* data)
{
    s32 size = 0;
    u32 width;
    u32 aligned_100;
    u32 height;
    u32 unk_104_val;
    u32 wh;
    u32 wh_div4;
    PAD_STACK(16);

    data->unk_104 = 0x20;

    /* Load width first */
    width = data->width;
    /* Load unk_100 */
    aligned_100 = data->unk_100;
    /* Load height */
    height = data->height;
    /* Load unk_104 */
    unk_104_val = data->unk_104;

    /* Align unk_100 */
    aligned_100 = ALIGN_32(aligned_100);

    /* Store width */
    data->unk_A0 = (u16) width;

    /* Multiply width * height */
    wh = width * height;

    /* Reload and store height */
    height = data->height;
    data->unk_A2 = (u16) height;

    /* size = aligned * unk_104 */
    size = aligned_100 * unk_104_val;

    /* Store 4 to unk_A4 */
    data->unk_A4 = 4;

    /* Zero unk_9C */
    data->unk_9C = 0;

    /* size += wh */
    size += wh;

    /* size += wh/4 twice */
    wh_div4 = wh >> 2;
    size += wh_div4;
    size += wh_div4;

    /* Call THPDec_8032FD40 with &unk_9C and height as u16 */
    size += THPDec_8032FD40(&data->unk_9C, (u16) data->height);

    /* Zero various fields */
    data->unk_7C = 0;
    data->unk_78 = 0;
    data->unk_84 = 0;
    data->unk_80 = 0;
    data->unk_90 = 0;
    data->unk_88 = 0;
    data->unk_94 = -1;
    data->unk_68 = 0;

    /* Copy width/height again */
    data->unk_A8 = (u16) data->width;
    data->unk_AA = (u16) data->height;
    data->unk_AC = 0;

    /* Add aligned sizes */
    size += ALIGN_32(data->unk_104 * 4);
    size += ALIGN_32(data->unk_40 * 4);

    return size;
}

/// #fn_8001ECF4

s32 fn_8001EF5C(THPDecComp* data)
{
    s32 spC;
    BOOL intr;

    if ((u32) data->unk_94 != data->unk_90) {
        intr = OSDisableInterrupts();
        data->unk_98 = THPVideoDecode(
            &data->unk_A8, &spC, data->unk_98,
            data->unk_4C[data->unk_90] + 4,
            &data->unk_9C);
        OSRestoreInterrupts(intr);

        if (data->width == 0x280) {
            THPDec_80331340(data->unk_98, data->unk_50,
                            data->unk_54, data->unk_58);
            DCStoreRange(data->unk_50,
                         data->width * data->height);
            DCStoreRange(data->unk_54,
                         (data->width * data->height) >> 2);
            DCStoreRange(data->unk_58,
                         (data->width * data->height) >> 2);
        } else {
            THPDec_803313D0(data->unk_98, data->unk_50,
                            data->unk_54, data->unk_58);
        }

        intr = OSDisableInterrupts();
        data->unk_94 = data->unk_90;
        OSRestoreInterrupts(intr);
        return fn_8001F13C(data);
    }

    return data->unk_94;
}

/// #fn_8001EF5C

s32 fn_8001F06C(THPDecComp* data)
{
    BOOL intr;

    intr = OSDisableInterrupts();

    if (data->unk_108 > 0 || data->unk_6C == 0) {
        data->unk_78++;

        if (data->unk_78 == data->unk_40) {
            if (data->unk_68 != 0) {
                data->unk_78 = 0;
            } else {
                data->unk_78--;
                goto end;
            }
        }

        data->unk_88++;
        data->unk_108--;

        if (data->unk_88 >= data->unk_104) {
            data->unk_88 = 0;
        }
    }

    if (data->unk_108 < data->unk_10C) {
        data->unk_10C = data->unk_108;
    }

end:
    OSRestoreInterrupts(intr);
    return 1;
}

/// #fn_8001F13C

s32 fn_8001F13C(THPDecComp* data)
{
    BOOL intr;
    u32 next;

    intr = OSDisableInterrupts();
    if ((data->unk_90 != data->unk_8C) && (data->unk_110 == 0) &&
        (data->unk_70 != 0))
    {
        data->unk_13C = OSGetTick();
        data->unk_138 = 0;
        if (data->unk_74 != data->unk_40) {
            if (data->unk_124 == 0) {
                OSReport("filnum = %d, ofs = %d, by sugano.\n",
                         data->unk_128, data->unk_120);
                __assert("lbmthp.c", 0x121,
                         "(u32)streamPlayer->currPackedSize != 0");
            }
            HSD_DevComRequest(data->unk_128, data->unk_120,
                              data->unk_4C[data->unk_8C],
                              ALIGN_32(data->unk_124), 0x21, 1,
                              fn_8001E910, NULL);
            data->unk_74++;
            if ((data->unk_74 == data->unk_40) && (data->unk_68 != 0)) {
                data->unk_74 = 0;
            }
            next = data->unk_8C + 1;
            if (next >= data->unk_104) {
                next = 0;
            }
            data->unk_8C = next;
            data->unk_110 = 1;
        }
    }
    return OSRestoreInterrupts(intr);
}

s32 fn_8001F294(void);

/// #fn_8001F2A4

/// #lbMthp_8001F410

void lbMthp_8001F410(const char* filename, void* rate_table, int buf_arg,
                     int bufsize, int loop)
{
    s32 size;
    void* buf = (void*) buf_arg;

    if (lbl_804333E0.unk_14C != 0) {
        __assert("lbmthp.c", 0x341, "lbl_804333E0.unk_14C == 0");
    }
    lbl_804333E0.unk_14C = 1;
    fn_8001EB14((THPDecComp*) &lbl_804333E0, filename);
    lbl_804333E0.unk_12C = (s32) rate_table;
    size = fn_8001EBF0((THPDecComp*) &lbl_804333E0);
    if (buf != NULL) {
        if ((u32) bufsize < (u32) size) {
            __assert("lbmthp.c", 0x350, "bufsize >= size");
        }
        lbl_804333E0.unk_140 = NULL;
    } else {
        buf = HSD_MemAlloc(size);
        lbl_804333E0.unk_140 = buf;
    }
    lbl_804333E0.unk_68 = loop;
    fn_8001ECF4((THPDecComp*) &lbl_804333E0, buf);
    lbl_804333E0.unk_144 = 0;
    lbl_804333E0.unk_148 = 1;
    OSCreateAlarm(&lbl_804333E0.unk_150);
    OSSetPeriodicAlarm(
        &lbl_804333E0.unk_150,
        __cvt_dbl_usll(
            (f64) (0.016666668f * (f32) (*(u32*) 0x800000F8 >> 2))),
        __cvt_dbl_usll(
            (f64) (0.016666668f * (f32) (*(u32*) 0x800000F8 >> 2))),
        (OSAlarmHandler) fn_8001F2A4);
}

void lbMthp_8001F578(void)
{
    BOOL intr;
    PAD_STACK(8);
    intr = OSDisableInterrupts();
    lbl_804333E0.unk_90 = lbl_804333E0.unk_88;
    lbl_804333E0.unk_7C = lbl_804333E0.unk_78;
    lbl_804333E0.unk_84 = lbl_804333E0.unk_80;
    OSRestoreInterrupts(intr);
}

s32 lbMthp_8001F5C4(void)
{
    return lbl_804333E0.unk_84;
}

s32 lbMthp_8001F5D4(void)
{
    return lbl_804333E0.unk_134;
}

s32 lbMthp_8001F5E4(void)
{
    return lbl_804333E0.unk_108;
}

s32 lbMthp_8001F5F4(void)
{
    return lbl_804333E0.unk_10C;
}

s32 lbMthp_8001F604(void)
{
    return lbl_804333E0.unk_144;
}

void lbMthp_8001F614(s32 arg0)
{
    lbl_804333E0.unk_148 = arg0;
}

HSD_SObj* lbMthp_8001F624(HSD_GObj* gobj, int width, int height)
{
    HSD_SObj* sobj;
    lbl_803BAFE8.x0 = 0;
    lbl_803BAFE8.x4 = (u16) width;
    lbl_803BAFE8.x6 = (u16) height;
    sobj = HSD_SObjLib_803A477C(gobj, (int) &lbl_804D3834, 0, 0, 0x80, 0);
    sobj->x40 |= 0x10;
    return sobj;
}

/// #lbMthp_8001F67C

void lbMthp_8001F800(void)
{
    struct lbl_804333E0_t* base;
    s32* p_14C;

    base = &lbl_804333E0;
    p_14C = &base->unk_14C;

    if (*p_14C != 0) {
        *(s32*) ((u8*) base + 0x70) = 0;

        while (fn_8001F294()) {
        }

        OSCancelAlarm((OSAlarm*) ((u8*) base + 0x150));
        HSD_VIWaitXFBFlush();

        if (*(void**) ((u8*) base + 0x140) != NULL) {
            HSD_Free(*(void**) ((u8*) base + 0x140));
        }

        *p_14C = 0;
    }
}

s32 fn_8001F294(void)
{
    return lbl_804333E0.unk_110;
}

void lbMthp_8001F87C(void)
{
    lbl_804333E0.unk_14C = 0;
}

void* lbMthp8001F890(HSD_GObj* gobj)
{
    lbl_804335B8.x70 = 0;
    lbl_804335B8.x74 = lbl_804335B8.x6C;
    lbl_804335B8.x76 = lbl_804335B8.x6E;
    lbl_804335B8.x78 = 6;
    lbl_804335B8.x7C = 0;
    lbl_804335B8.x84 = lbl_804D7CE0;
    lbl_804335B8.x80 = lbl_804D7CE0;
    lbl_804335B8.x88 = &lbl_804335B8.x70;
    lbl_804335B8.x8C = 0;
    lbl_804335B8.x90 = (struct HSD_SObj*) HSD_SObjLib_803A477C(
        gobj, (int) &lbl_804335B8.x88, 0, 0, 0x80, 0);
    lbl_804335B8.x90->x40 |= 0x10;
    return lbl_804335B8.x90;
}

void lbMthp8001F928(HSD_GObj* gobj, int arg1)
{
    u16* pWidth = &lbl_804335B8.x6C;
    u16* pHeight = &lbl_804335B8.x6E;

    /* First texture - full size */
    GXInitTexObj(&lbl_804335B8.tex0, lbl_804335B8.x20, lbl_804335B8.x6C,
                 lbl_804335B8.x6E, 1, 0, 0, 0);
    GXInitTexObjLOD(&lbl_804335B8.tex0, 0, 0, lbl_804D7CE0, lbl_804D7CE0,
                    lbl_804D7CE0, 0, 0, 0);
    GXLoadTexObj(&lbl_804335B8.tex0, 0);

    /* Second texture - half size */
    GXInitTexObj(&lbl_804335B8.tex1, lbl_804335B8.x44, (u16) (*pWidth >> 1),
                 (u16) (*pHeight >> 1), 1, 0, 0, 0);
    GXInitTexObjLOD(&lbl_804335B8.tex1, 0, 0, lbl_804D7CE0, lbl_804D7CE0,
                    lbl_804D7CE0, 0, 0, 0);
    GXLoadTexObj(&lbl_804335B8.tex1, 1);

    /* Third texture - half size */
    GXInitTexObj(&lbl_804335B8.tex2, lbl_804335B8.x68, (u16) (*pWidth >> 1),
                 (u16) (*pHeight >> 1), 1, 0, 0, 0);
    GXInitTexObjLOD(&lbl_804335B8.tex2, 0, 0, lbl_804D7CE0, lbl_804D7CE0,
                    lbl_804D7CE0, 0, 0, 0);
    GXLoadTexObj(&lbl_804335B8.tex2, 2);

    HSD_SObjLib_803A49E0(gobj, arg1);
}

/// #lbMthp8001FAA0
