#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PalScriptWaitObj.h"

// 0x004A68D0
char PalScriptWaitObj::ReleaseObject(char *pszBuf)
{
  gbRefObject *vftable; // ecx
  gbTexture *v4; // eax

// [VFTABLE] vftable = (gbRefObject *)this->__vftable;
  if ( vftable )
  {
    ((gbRefObject *)vftable)->Release();
// [VFTABLE] this->__vftable = 0;
  }
  ((gbImage2D *)&this->m_needscriptdel)->Release();
  ((gbImage2D *)&this->m_needscriptdel)->LoadImageFile(pszBuf, 0);
  v4 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, pszBuf);
// [VFTABLE] this->__vftable = v4;
  ((gbTexture *)v4)->LoadTexture(2);
  return 1;
}
