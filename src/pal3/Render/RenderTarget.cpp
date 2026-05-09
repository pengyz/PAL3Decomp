#include "pal3/gen/RenderTarget.h"

// 0x004BDAC0
void sub_4BDAC0(int this)
{
  gbTexture_D3D::~gbTexture_D3D((void *)(this + 100));
  gbTexture_D3D::~gbTexture_D3D((void *)(this + 4));
}

// 0x004BDB60
int sub_4BDB60(_DWORD *this)
{
  int result; // eax
  int v3; // [esp+Ch] [ebp-814h] BYREF
  int v4; // [esp+14h] [ebp-80Ch]
  char pExceptionObject[1024]; // [esp+20h] [ebp-800h] BYREF
  char ArgList; // [esp+420h] [ebp-400h] BYREF

  if ( !(*(int (__thiscall **)(int, int *, int))(*(_DWORD *)MEMORY[0xBFDA60] + 84))(MEMORY[0xBFDA60], &v3, 1) )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aLockBackBuffer, (int)aDProjectPal3Ef, 39),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (__thiscall **)(int))(*(_DWORD *)MEMORY[0xBFDA60] + 88))(MEMORY[0xBFDA60]);
  (*(void (__thiscall **)(_DWORD *, int, int, int))(*(this + 25) + 12))(
    this + 25,
    MEMORY[0xBFD6D0],
    MEMORY[0xBFD6D4],
    v4);
  result = (*(int (__thiscall **)(_DWORD *, int, int, int))(*(this + 1) + 12))(this + 1, 512, 512, v4);
  *this = 0;
  *(this + 49) = 0;
  return result;
}

// 0x004BDC10
void sub_4BDC10(_DWORD *this, int a2)
{
  int v2; // eax

  if ( *(this + 49) != 1 )
  {
    v2 = a2;
    if ( (a2 == 1 || a2 == 2) && !*(this + 46) )
      v2 = 0;
    *this = v2;
  }
}

// 0x004BDC40
bool sub_4BDC40(int *this, int a2)
{
  int v4; // ecx
  int v5; // esi
  int *v6; // [esp+28h] [ebp-10h] BYREF
  int v7; // [esp+34h] [ebp-4h]

  v6 = this;
  if ( *(this + 49) == 1 )
    return 0;
  *(this + 49) = 1;
  v4 = *this;
  v5 = 0;
  if ( !*this )
  {
    v5 = (*(int (__thiscall **)(int, int *))(*(_DWORD *)MEMORY[0xBFDA60] + 92))(MEMORY[0xBFDA60], this + 1);
    (gbCamera *->SetDimention()(MEMORY[0xBFDA68] + 4), 512, 384);
    CameraCtrl::SetAsCurrent(MEMORY[0xBFDA68], 3);
LABEL_8:
    if ( v5 )
    {
      if ( (_BYTE)a2 )
      {
        (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)(MEMORY[0xBFDA60] + 1816)
                                                                             + 172))(
          *(_DWORD *)(MEMORY[0xBFDA60] + 1816),
          0,
          0,
          3,
          -16777216,
          1065353216,
          0);
        (*(void (__thiscall **)(int))(*(_DWORD *)MEMORY[0xBFDA60] + 48))(MEMORY[0xBFDA60]);
        PushMatrixStacks(&v6);
        v7 = 0;
        a2 = -16777216;
        _TextureLib_Data::~_TextureLib_Data(0, 0, 512, 512, &a2);
        (*(void (__thiscall **)(int))(*(_DWORD *)MEMORY[0xBFDA60] + 52))(MEMORY[0xBFDA60]);
        v7 = -1;
        PopMatrixStacks(&v6);
      }
    }
    return v5 != 0;
  }
  if ( v4 > 0 && v4 <= 2 )
  {
    v5 = (*(int (__thiscall **)(int, int *))(*(_DWORD *)MEMORY[0xBFDA60] + 92))(MEMORY[0xBFDA60], this + 25);
    goto LABEL_8;
  }
  return v5 != 0;
}

// 0x004BDF10
_DWORD * sub_4BDF10(_DWORD *this)
{
  *(this + 1) = 0;
  *this = &off_56F4F0;
  *(this + 2) = 1;
  *(this + 4) = 0;
  *(this + 3) = 0;
  *((_BYTE *)this + 20) = 0;
  return this;
}
