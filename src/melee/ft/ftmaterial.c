#include "ftmaterial.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0C31.h"
#include "ft/ft_0D31.h"
#include "ft/ftdevice.h"
#include "ft/types.h"
#include "ftCommon/ftCo_09F4.h"
#include "gm/gm_unsplit.h"
#include "lb/lb_00B0.h"
#include "lb/lbrefract.h"
#include "pl/player.h"

#include <baselib/class.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/mobj.h>
#include <baselib/state.h>
#include <baselib/tev.h>
#include <baselib/tobj.h>

/* literal */ extern char* ftCo_804D3C00;
/* literal */ extern char* ftCo_804D3C08;
/* literal */ float const ftCo_804D8C20 = 0;
/* literal */ float const ftCo_804D8C24 = 1;

#pragma force_active on

void ftMaterial_800BF260(void)
{
    hsdInitClassInfo(&ftMObj.parent, &hsdMObj.parent, (char*) &ftMObj + 0xDC,
                     (char*) &ftCo_804D3C00, 0x50, 0x20);
    ftMObj.setup = ftMaterial_800BF2B8;
}

void ftMaterial_800BF2B8(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TExp texp;
    HSD_PEDesc pe;
    Fighter* fp = GET_FIGHTER(HSD_GObj_804D7814);

    if (fp->x2226_b5) {
        lbRefract_80022998(mobj, rendermode,
                           fp->smash_attrs.x2134_vibrateFrame);
        return;
    }

    if (!fp->x2223_b2 && (!fp->x2228_b0 || !fp->x2224_b0)) {
        if (fp->is_metal) {
            mobj = ft_804D6580;
        } else if (fp->x2227_b3) {
            mobj = ft_804D6588;
        }
    }

    HSD_StateInitTev();

    {
        u32 mobj_rendermode = mobj->rendermode;
        HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                             mobj->mat->specular, mobj->mat->alpha);
        if (mobj_rendermode & RENDER_SPECULAR) {
            HSD_SetMaterialShininess(mobj->mat->shininess);
        }
        {
            HSD_TObj** cur_tobj = NULL;
            {
                HSD_TObj* tobj = mobj->tobj;
                if (mobj_rendermode & RENDER_SHADOW && tobj_shadows != NULL) {
                    cur_tobj = &tobj;
                    while (*cur_tobj != NULL) {
                        cur_tobj = &(*cur_tobj)->next;
                    }
                    *cur_tobj = tobj_shadows;
                }
                if ((mobj_rendermode & RENDER_TOON) && tobj_toon != NULL &&
                    tobj_toon->imagedesc != NULL)
                {
                    tobj_toon->next = tobj;
                    tobj = tobj_toon;
                }
                HSD_TObjSetup(tobj);
                HSD_TObjSetupTextureCoordGen(tobj);
                HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj, mobj_rendermode);
            }
            if (fp->x61D != 0xFF) {
                mobj_rendermode |= RENDER_NO_ZUPDATE | RENDER_XLU;
            }
            {
                HSD_TExp* texp1 =
                    ftMaterial_800BF534(fp, mobj, &texp, rendermode);
                ftMaterial_800BF6BC(fp, mobj, texp1);
                if (fp->x2223_b2 && !fp->x2223_b3) {
                    mobj_rendermode |= RENDER_NO_ZUPDATE;
                }
                {
                    HSD_PEDesc* pe_p;
                    if (fp->x2223_b4 && fp->x61D == 0xFF) {
                        pe.flags = (1 << 3) | (1 << 4) | (1 << 5);
                        pe.dst_alpha = 0;
                        pe.type = 0;
                        pe.src_factor = 4;
                        pe_p = &pe;
                        pe.dst_factor = 5;
                        pe.logic_op = 15;
                        pe.z_comp = 3;
                        pe.alpha_comp0 = 7;
                        pe.ref0 = 0;
                        pe.alpha_op = 0;
                        pe.alpha_comp1 = 7;
                        pe.ref1 = 0;
                    } else {
                        pe_p = mobj->pe;
                    }
                    HSD_SetupRenderModeWithCustomPE(mobj_rendermode, pe_p);
                }
                if (texp1 == NULL) {
                    ftCo_8009F75C(fp, true);
                }
            }
            if (cur_tobj != NULL) {
                *cur_tobj = NULL;
            }
        }
    }
}

HSD_TExp* ftMaterial_800BF534(Fighter* fp, HSD_MObj* mobj, HSD_TExp* texp,
                              u32 rendermode)
{
    HSD_TevDesc sp_tevdesc;
    s32 reg;
    bool chk;
    char* base = (char*) &ftMObj;
    ColorOverlay* overlay = ftCo_800C0658(fp);

    if (overlay->x7C_flag2 && overlay->x7C_light_enable) {
        if (!(rendermode & RENDER_XLU) && !fp->x2223_b2) {
            texp->cnst = *(HSD_TECnst*) (base + 0xC4);
            reg = lbGetFreeColorRegister(0, mobj, NULL);
            if (reg == -1) {
                OSReport(base + 0xF4);
                __assert(base + 0x118, 240, (char*) &ftCo_804D3C08);
            }
            texp->cnst.reg = (u8) reg;
            texp->cnst.val = &overlay->x50_light_color;
            HSD_TExpSetReg(texp);

            sp_tevdesc = *(HSD_TevDesc*) (base + 0x50);
            sp_tevdesc.stage = HSD_StateAssignTev();
            sp_tevdesc.color = 2;
            sp_tevdesc.u.tevconf.clr_a = GX_CC_ZERO;
            sp_tevdesc.u.tevconf.clr_b = lb_8000CC8C(reg);
            sp_tevdesc.u.tevconf.clr_c = GX_CC_RASA;
            chk = false;
            sp_tevdesc.u.tevconf.clr_d = GX_CC_CPREV;
            if (reg < 4) {
                chk = true;
            }
            if (chk) {
                sp_tevdesc.u.tevconf.kcsel = lb_8000CCA4(reg);
            }
            HSD_SetupTevStage(&sp_tevdesc);
            return texp;
        }
        ftCo_8009F75C(fp, false);
    }
    return NULL;
}

void ftMaterial_800BF6BC(Fighter* fp, HSD_MObj* mobj, HSD_TExp* texp)
{
    NOT_IMPLEMENTED;
}

void ftMaterial_800BFB4C(Fighter_GObj* gobj, GXColor* diffuse)
{
    HSD_JObj* cur = GET_JOBJ(gobj);

    while (cur != NULL) {
        HSD_DObj* dobj = HSD_JObjGetDObj(cur);
        while (dobj != NULL) {
            HSD_MObj* mobj = dobj != NULL ? dobj->mobj : NULL;
            if (mobj != NULL) {
                if (mobj->mat != NULL) {
                    HSD_Material* mat = mobj->mat;
                    mat->diffuse = *diffuse;
                }
            }
            dobj = dobj != NULL ? dobj->next : NULL;
        }
        if (!(HSD_JObjGetFlags(cur) & JOBJ_INSTANCE)) {
            HSD_JObj* child;
            if (cur == NULL) {
                child = NULL;
            } else {
                child = cur->child;
            }
            if (child != NULL) {
                HSD_JObj* child;
                if (cur == NULL) {
                    child = NULL;
                } else {
                    child = cur->child;
                }
                cur = child;
                continue;
            }
        }
        {
            HSD_JObj* next;
            if (cur == NULL) {
                next = NULL;
            } else {
                next = cur->next;
            }
            if (next != NULL) {
                HSD_JObj* next;
                if (cur == NULL) {
                    next = NULL;
                } else {
                    next = cur->next;
                }
                cur = next;
            } else {
                while (true) {
                    HSD_JObj* parent;
                    if (cur == NULL) {
                        parent = NULL;
                    } else {
                        parent = cur->parent;
                    }
                    if (parent == NULL) {
                        cur = NULL;
                    } else {
                        HSD_JObj* parent;
                        if (cur == NULL) {
                            parent = NULL;
                        } else {
                            parent = cur->parent;
                        }
                        {
                            HSD_JObj* next;
                            if (parent == NULL) {
                                next = NULL;
                            } else {
                                next = parent->next;
                            }
                            if (next != NULL) {
                                HSD_JObj* parent;
                                if (cur == NULL) {
                                    parent = NULL;
                                } else {
                                    parent = cur->parent;
                                }
                                {
                                    HSD_JObj* next;
                                    if (parent == NULL) {
                                        next = NULL;
                                    } else {
                                        next = parent->next;
                                    }
                                    cur = next;
                                }
                            } else {
                                HSD_JObj* parent;
                                if (cur == NULL) {
                                    parent = NULL;
                                } else {
                                    parent = cur->parent;
                                }
                                cur = parent;
                                continue;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}

void ftMaterial_800BFD04(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Sleep, Ft_MF_None, 0, 1, 0, NULL);
    fp->invisible = true;
    fp->x221E_b1 = true;
    fp->x221E_b2 = true;
    fp->x2219_b1 = true;
    fp->x890_cameraBox->x8 = true;
    fp->x221F_b3 = true;
    fp->x221F_b1 = true;
}

void ftMaterial_800BFD9C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMaterial_800BFD04(gobj);
    if (fp->x2222_b5) {
        HSD_GObj* pl_gobj = Player_GetEntityAtIndex(fp->player_id, 1);
        if (pl_gobj != NULL) {
            ftCo_800D4F24(pl_gobj, 1);
        }
    }
    gm_80167320(fp->player_id, fp->x221F_b4);
}
