#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/Parent_Data.h"

// Unnamed globals (extern)
extern int dword_189503C;
extern int dword_1895040;
extern int dword_1895044;
extern float flt_1895038;

// 0x0053FE80
// attributes: thunk
int Parent_Data::_CheckKeyWord()
{
  return this->_CheckStr();
}

// 0x0053FE90
int Parent_Data::_CheckStr()
{
  dword_189503C = 1094713344;
  return 1094713344;
}

// 0x0053FEA0
// attributes: thunk
void Parent_Data::GetSize()
{

}

// 0x0053FEB0
void Parent_Data::spstr()
{
  flt_1895038 = 12.0 + 12.0;
}

// 0x0053FEC0
gbRenderEffect * Parent_Data::spstr_fec0()
{
  gbEffectMgr *pEffectMgr; // esi
  gbRenderEffect *result; // eax

  dword_1895040 = (g_DrvInfo.width - 800) / 2;
  dword_1895044 = (g_DrvInfo.height - 600) / 2;
  pEffectMgr = gfxMgr->pEffectMgr;
  g_pRenderEffect_1895048 = ((gbEffectMgr *)pEffectMgr)->NewTrivalEffect(0);
  g_pRenderEffect_189504C = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\ui_TL.gbf", 0);
  g_pRenderEffect_1895050 = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\ui_notex_TL.gbf", 0);
  g_pRenderEffect_1895068 = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\ui_notex.gbf", 0);
  g_pRenderEffect_1895054 = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\ui_tex_vcolor.gbf", 0);
  g_pTexColorEffect = (int)((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\ui_tex_color.gbf", 0);
  g_pRenderEffect_189505C = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\ui_par_tex_color.gbf", 0);
  g_pRenderEffect_1895060 = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\ui_alpha.gbf", 0);
  g_pRenderEffect_1895064 = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\ui_AddColor.gbf", 0);
  result = ((gbEffectMgr *)pEffectMgr)->NewRenderEffect("gfxscript\\geom_notex_line.gbf", 0);
  g_nParent_Data_189506C = (int)result;
  return result;
}
