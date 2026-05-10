#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIRenderObj.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/UIQuadManager.h"

// 0x00541640
UIRenderObj::UIRenderObj()
{
  int v2; // ecx
  gbTexture *v3; // esi
  int v4; // [esp+4h] [ebp-70h] BYREF
  struct tagPOINT Point; // [esp+Ch] [ebp-68h] BYREF
  struct tagPOINT v6; // [esp+14h] [ebp-60h] BYREF
  int v7; // [esp+1Ch] [ebp-58h]
  int v8; // [esp+20h] [ebp-54h]
  struct gbTextureArray v9; // [esp+24h] [ebp-50h] BYREF
  int v10; // [esp+70h] [ebp-4h]

  if ( *((_BYTE *)this + 29) )
  {
    if ( *((_BYTE *)this + 28) )
    {
      PushMatrixStacks();
      v10 = 0;
      ((GRPinput *)&Point)->GetCursorPos();
      v6 = Point;
      v8 = Point.y + 32;
      v2 = *((_DWORD *)this + 3);
      v7 = Point.x + 32;
      v4 = -1;
      v3 = (gbTexture *)*((_DWORD *)this + v2 + 4);
      v9.nTex = 1;
      v9.pTexPt[0] = v3;
      ((_TextureLib_Data *)&v6.x)->SetLibFolder((unsigned int *)&v4, &v9, 0x114u, 0, COERCE_FLOAT(1));
      v10 = -1;
      PopMatrixStacks();
    }
  }
}

// 0x00541710
UIRenderObj::~UIRenderObj()
{
  if ( !*((_BYTE *)UIQuadManager::GetInstance() + 29) )
    return (*(unsigned __int8 (**)(gbGfxManager *, _DWORD))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 104))(
             g_pGfxMgr,
             a2);
  *((_BYTE *)this + 28) = a2;
  a2;
}
