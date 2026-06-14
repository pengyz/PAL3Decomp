#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIRenderObj.h"

// 0x00541640
UIRenderObj::UIRenderObj()
{
  int v2; // ecx
  int v3; // esi
  _BYTE v4[4]; // [esp+0x8] [ebp-0x6C] BYREF
  struct tagPOINT Point; // [esp+0xC] [ebp-0x68]
  struct tagPOINT pszFolder; // [esp+0x14] [ebp-0x60] BYREF
  int v7; // [esp+0x1C] [ebp-0x58]
  int v8; // [esp+0x20] [ebp-0x54]
  int v9; // [esp+0x24] [ebp-0x50]
  int v10; // [esp+0x64] [ebp-0x10]
  int v11; // [esp+0x70] [ebp-0x4]

  if ( *((_BYTE *)this + 29) )
  {
    if ( *((_BYTE *)this + 28) )
    {
      PushMatrixStacks(v4);
      v11 = 0;
      ((GRPinput *)&g_Input)->GetCursorPos();
      pszFolder = Point;
      v8 = Point.y + 32;
      v2 = *((_DWORD *)this + 3);
      v7 = Point.x + 32;
      v3 = *((_DWORD *)this + v2 + 4);
      v10 = 1;
      v9 = v3;
      ((TextureLibDataBase *)&pszFolder)->SetLibFolder((char *)&pszFolder);
      v11 = -1;
      PopMatrixStacks(v4);
    }
  }
}

// 0x00541710
void UIRenderObj::_UIRenderObj()
{
  unsigned __int8 v2; // [esp+0x8] [ebp+0x4]

  if ( UIQuadManager::GetInstance()[7]._tail_000[1] )
    *((_BYTE *)this + 28) = v2;
  else
    (*(void ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr + 104))(gfxMgr, v2);
}
