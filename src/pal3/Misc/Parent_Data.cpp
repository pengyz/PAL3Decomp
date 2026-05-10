#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Parent_Data.h"

// Unnamed globals (extern)
extern char aGfxscriptGeomN[];
extern char aGfxscriptUiAdd[];
extern char aGfxscriptUiAlp[];
extern char aGfxscriptUiNot[];
extern char aGfxscriptUiNot_0[];
extern char aGfxscriptUiPar[];
extern char aGfxscriptUiTex[];
extern char aGfxscriptUiTex_0[];
extern char aGfxscriptUiTlG[];
extern int dword_189503C;
extern int dword_1895040;
extern int dword_1895044;
extern int dword_1895048;
extern int dword_189504C;
extern int dword_1895050;
extern int dword_1895054;
extern int dword_1895058;
extern int dword_189505C;
extern int dword_1895060;
extern int dword_1895064;
extern int dword_1895068;
extern int dword_189506C;
extern float flt_1895038;

// 0x0053FDD0
Parent_Data::Parent_Data(LPCSTR lpString)
{
  int v3; // edi
  int i; // ebx

  if ( !*((_BYTE *)this + 532) )
    return 0;
  if ( lstrlenA(lpString) <= 0 )
    return 0;
  v3 = 0;
  if ( *((int *)this + 131) <= 0 )
    return 0;
  for ( i = 0; _strcmpi(lpString, (const char *)(i + *((_DWORD *)this + 132))); i += 1088 )
  {
    if ( ++v3 >= *((_DWORD *)this + 131) )
      return 0;
  }
  return (Parent_Data *)(*((_DWORD *)this + 132) + 1088 * v3);
}

// 0x0053FE80
// attributes: thunk
int Parent_Data::_CheckKeyWord()
{
  return Parent_Data::_CheckStr();
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
  Parent_Data::spstr();
}

// 0x0053FEB0
void Parent_Data::spstr()
{
  flt_1895038 = 12.0 + 12.0;
}

// 0x0053FEC0
struct gbRenderEffect *Parent_Data::spstr()
{
  gbEffectMgr *v0; // esi
  struct gbRenderEffect *result; // eax

  dword_1895040 = (g_Input.KeyInfo[120].Data - 800) / 2;
  dword_1895044 = (g_Input.KeyInfo[120].HoldTime - 600) / 2;
  v0 = (gbEffectMgr *)*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200);
  dword_1895048 = (int)v0->NewTrivalEffect(0);
  dword_189504C = (int)v0->NewRenderEffect(aGfxscriptUiTlG, 0);
  dword_1895050 = (int)v0->NewRenderEffect(aGfxscriptUiNot, 0);
  dword_1895068 = (int)v0->NewRenderEffect(aGfxscriptUiNot_0, 0);
  dword_1895054 = (int)v0->NewRenderEffect(aGfxscriptUiTex, 0);
  dword_1895058 = (int)v0->NewRenderEffect(aGfxscriptUiTex_0, 0);
  dword_189505C = (int)v0->NewRenderEffect(aGfxscriptUiPar, 0);
  dword_1895060 = (int)v0->NewRenderEffect(aGfxscriptUiAlp, 0);
  dword_1895064 = (int)v0->NewRenderEffect(aGfxscriptUiAdd, 0);
  result = (struct gbRenderEffect *)v0->NewRenderEffect(aGfxscriptGeomN, 0);
  dword_189506C = (int)result;
  return result;
}
