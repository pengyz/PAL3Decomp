#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIRenderObj.h"

// Forward declarations for unnamed functions
int sub_541640(...);
int sub_541710(...);

// 0x00541640
void sub_541640(int _this)
{
  int v2; // ecx
  int v3; // esi
  int v4; // [esp+4h] [ebp-70h] BYREF
  _BYTE v5[4]; // [esp+8h] [ebp-6Ch] BYREF
  struct tagPOINT Point; // [esp+Ch] [ebp-68h] BYREF
  struct tagPOINT v7; // [esp+14h] [ebp-60h] BYREF
  int v8; // [esp+1Ch] [ebp-58h]
  int v9; // [esp+20h] [ebp-54h]
  int v10[17]; // [esp+24h] [ebp-50h] BYREF
  int v11; // [esp+70h] [ebp-4h]

  if ( *(_BYTE *)(this + 29) )
  {
    if ( *(_BYTE *)(this + 28) )
    {
      PushMatrixStacks(v5);
      v11 = 0;
      GRPinput::GetCursorPos(&Point);
      v7 = Point;
      v9 = Point.y + 32;
      v2 = *(_DWORD *)(this + 12);
      v8 = Point.x + 32;
      v4 = -1;
      v3 = *(_DWORD *)(this + 4 * v2 + 16);
      v10[16] = 1;
      v10[0] = v3;
      _TextureLib_Data::SetLibFolder(
        &v7.x,
        (unsigned int *)&v4,
        (struct gbTextureArray *)v10,
        0x114u,
        0,
        COERCE_FLOAT(1));
      v11 = -1;
      PopMatrixStacks();
    }
  }
}

// 0x00541710
unsigned __int8 sub_541710(unsigned __int8 a2)
{
  if ( !*((_BYTE *)UIQuadManager::GetInstance() + 29) )
    return (*(int (**)(int, _DWORD))(*(_DWORD *)g_pGfxManager + 104))(g_pGfxManager, a2);
  *((_DWORD *)this + 28) = a2;
  return a2;
}
