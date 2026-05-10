#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/RoleSystem.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_4019F0(...);
int sub_419C20(...);
int sub_424570(...);
int sub_43A660(...);
int sub_43A810(...);
int sub_445ED0(...);
int sub_445F60(...);

// Unnamed globals (extern)
extern void *off_56AC70;

// 0x004200A0
int UIScene::Render(int a2)
{
  int result; // eax
  gbVisNode *v4; // ecx
  int v5; // ebx
  char *v6; // esi

  result = *((_DWORD *)this + 123285);
  if ( result )
  {
    v4 = (gbVisNode *)*((_DWORD *)this + 123284);
    if ( v4 )
    {
      v4->SetTimeScale(0.2);
      (*(void (**)(_DWORD, _DWORD))(**((_DWORD **)this + 123284) + 16))(*((_DWORD *)this + 123284), 0);
    }
    result = *((_DWORD *)this + 55);
    v5 = 0;
    if ( result > 0 )
    {
      v6 = (char *)this + 224;
      do
      {
        if ( *((_DWORD *)v6 + 22) != 4 )
          sub_424570((int)v6, (gbMatrixStack *)a2, 0);
        result = *((_DWORD *)this + 55);
        ++v5;
        v6 += 896;
      }
      while ( v5 < result );
    }
  }
  return result;
}

// 0x00420110
int UIScene::RenderWithStack(void *pStack)
{
  int v3; // esi
  int result; // eax
  RoleSystem *v5; // edi

  v3 = 0;
  result = *((_DWORD *)this + 14392);
  if ( result > 0 )
  {
    v5 = (UIScene *)((char *)this + 57572);
    do
    {
      v5->RenderRole(pStack, 0);
      result = *((_DWORD *)this + 14392);
      ++v3;
      v5 = (RoleSystem *)((char *)v5 + 8704);
    }
    while ( v3 < result );
  }
  return result;
}

// 0x00421A10
int UIScene::NotifyRender()
{
  int v2; // esi
  int result; // eax

  v2 = 0;
  result = *((_DWORD *)this + 42);
  if ( result > 0 )
  {
    do
    {
      sub_4019F0(*(_DWORD *)(*((_DWORD *)this + 41) + 4 * v2));
      result = *((_DWORD *)this + 42);
      ++v2;
    }
    while ( v2 < result );
  }
  return result;
}

// 0x00421C00
int UIScene::EffectRender()
{
  int v2; // edi
  int result; // eax
  char *v4; // esi

  v2 = 0;
  result = *((_DWORD *)this + 14392);
  if ( result > 0 )
  {
    v4 = (char *)this + 57572;
    do
    {
      if ( v4[173] == 4 )
        sub_419C20((int)v4);
      result = *((_DWORD *)this + 14392);
      ++v2;
      v4 += 8704;
    }
    while ( v2 < result );
  }
  return result;
}

// 0x004220A0
int UIScene::OverlayRender(int a2)
{
  int v3; // edi
  int result; // eax
  char *v5; // esi

  v3 = 0;
  result = *((_DWORD *)this + 55);
  if ( result > 0 )
  {
    v5 = (char *)this + 224;
    do
    {
      if ( *((_DWORD *)v5 + 22) == 4 )
        sub_424570((int)v5, (gbMatrixStack *)a2, 0);
      result = *((_DWORD *)this + 55);
      ++v3;
      v5 += 896;
    }
    while ( v3 < result );
  }
  return result;
}

// 0x004234D0
int UIScene::CombatCheck()
{
  int v1; // eax

  if ( !*(_DWORD *)(UISceneUpdate() + 136) )
    return 0;
  v1 = UISceneUpdate();
  (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)(v1 + 136) + 16))(*(_DWORD *)(v1 + 136), 0);
  return 1;
}

// 0x004235B0
BOOL UIScene::ProcessInput(char *String1, char *a2)
{
  const char *v2; // esi
  bool v3; // bl
  bool v4; // al

  v2 = (const char *)UISceneUpdate();
  v3 = _strcmpi(String1, v2) == 0;
  v4 = 1;
  if ( a2 )
    v4 = _strcmpi(a2, v2 + 32) == 0;
  return v3 && v4;
}

// 0x0043A4C0
void UIScene::LoadResource(char *path)
{
  int v2; // edi
  struct gbVFileSystem *v4; // [esp+Ch] [ebp-114h] BYREF
  char Buffer[260]; // [esp+10h] [ebp-110h] BYREF
  int v6; // [esp+11Ch] [ebp-4h]

  v2 = 0;
  if ( path )
  {
    ((UIWnd *)(gbRefObject **)this + 19)->MoveWindow();
    *((_DWORD *)this + 37) = 0;
    ((OpenBaseFile *)&v4)->OpenBaseFile();
    v6 = 0;
    sprintf(Buffer, "%s%d.tga", path, 0);
    while ( (int)g_pVFileSys->FileExistNum(Buffer) > 0 )
    {
      if ( !sub_445ED0() )
        ((UIWnd *)(gbRefObject **)this + 19)->MoveWindow();
      ++v2;
      ++*((_DWORD *)this + 37);
      sprintf(Buffer, "%s%d.tga", path, v2);
    }
    *((_DWORD *)this + 40) = 0;
    sub_43A660(this);
    v6 = -1;
    ((OpenNULLFile *)&v4)->OpenNULLFile();
  }
}

// 0x0043A770
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIScene::_UIScene(UIScene *this)
{
  ((UIWnd *)this)->UIWnd();
  ((UIWnd *)((char *)this + 116))->DestroyChildren();
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 49) = 0;
  *(_DWORD *)this = &off_56AC70;
  *((_BYTE *)this + 204) = 1;
  memset((char *)this + 212, 0, 0x80u);
  *((_DWORD *)this + 19) = 1065353216;
  *((_DWORD *)this + 18) = 1065353216;
  *((_DWORD *)this + 52) = 1;
}

// 0x0043A810
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_43A810(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AC70;
  UIScene::OnMessage2();
  ((j_UIWnd *)(char *)this + 116)->MoveWindow();
  this->_UIWnd();
}

// 0x0043AB00
int UIScene::OnMessage2()
{
  int result; // eax

  ((UIWnd *)(UIWnd **)this + 29)->MoveWindow();
  ((UIWnd *)this)->UpdateChildren();
  return result;
}

// 0x0043AB20
BOOL UIScene::Update2(int _this, int a2, int a3)
{
  BOOL v4; // edi
  int v6; // ecx
  char *Instance; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  BOOL v13; // eax
  void *v14; // [esp-8h] [ebp-20h]
  POINT pt; // [esp+10h] [ebp-8h] BYREF

  ((GRPinput *)&pt)->GetCursorPos();
  v4 = PtInRect((const RECT *)(this + 16), pt);
  if ( !*(_DWORD *)(this + 56) )
    return 0;
  if ( !*(_BYTE *)(this + 100) )
  {
    if ( v4 )
      *(_DWORD *)(this + 96) = 1;
    return 0;
  }
  if ( !*(_DWORD *)(this + 60) )
  {
    if ( v4 && g_Input.m_shiftedKeyStates[207] == 1 )
    {
      v6 = *(_DWORD *)(this + 32);
      if ( v6 )
        (*(void (**)(int, int, _DWORD, int))(*(_DWORD *)v6 + 24))(v6, 1021, *(_DWORD *)(this + 12), 1);
      if ( *(_BYTE *)(this + 340) )
      {
        v14 = pPos;
        Instance = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v14, 1);
      }
    }
    *(_DWORD *)(this + 96) = 0;
    return 0;
  }
  if ( !a3 )
  {
    *(_DWORD *)(this + 96) = 0;
    return ((UIWnd *)this)->HitTest(a2, 0);
  }
  if ( *(_DWORD *)(this + 96) != 2 )
  {
    if ( !v4 )
    {
      *(_DWORD *)(this + 96) = 0;
      goto LABEL_27;
    }
    *(_DWORD *)(this + 96) = 1;
  }
  if ( !v4 )
  {
LABEL_27:
    if ( !*(_BYTE *)(this + 204) )
    {
      v9 = *(_DWORD *)(this + 32);
      *(_BYTE *)(this + 204) = 1;
      if ( v9 )
        (*(void (**)(int, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1003, *(_DWORD *)(this + 12), 0);
    }
    goto LABEL_30;
  }
  if ( g_Input.m_shiftedKeyStates[207] == 1 && (g_Input.m_shiftedKeyStates[204] & 0xF) == 2 && *(_BYTE *)(this + 68) )
  {
    v8 = *(_DWORD *)(this + 32);
    *(_DWORD *)(this + 96) = 2;
    if ( v8 )
    {
      (*(void (**)(int, int, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1020, *(_DWORD *)(this + 12), 0);
      *(_BYTE *)(this + 204) = 0;
      goto LABEL_30;
    }
  }
  else if ( g_Input.m_shiftedKeyStates[207] == 1 )
  {
    v11 = *(_DWORD *)(this + 32);
    *(_DWORD *)(this + 96) = 2;
    if ( v11 )
    {
      (*(void (**)(int, int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1004, *(_DWORD *)(this + 12), 0);
      *(_BYTE *)(this + 204) = 0;
      goto LABEL_30;
    }
  }
  else
  {
    v12 = *(_DWORD *)(this + 32);
    if ( v12 )
      (*(void (**)(int, int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1002, *(_DWORD *)(this + 12), 0);
  }
  *(_BYTE *)(this + 204) = 0;
LABEL_30:
  if ( *(_DWORD *)(this + 96) == 2 && (g_Input.m_shiftedKeyStates[204] & 0xF) != 1 )
  {
    if ( v4 )
    {
      v10 = *(_DWORD *)(this + 32);
      *(_DWORD *)(this + 96) = 1;
      if ( v10 )
        (*(void (**)(int, int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(v10, 1001, *(_DWORD *)(this + 12), 0);
    }
    else
    {
      *(_DWORD *)(this + 96) = 0;
    }
  }
  v13 = ((UIWnd *)this)->HitTest(a2, a3);
  return v4 || v13;
}

// 0x0043AD40
int UIScene::Create2(int _this)
{
  int result; // eax
  int v3; // ecx
  int *v4; // edi
  int v5; // eax
  double v6; // st7
  int v7; // ecx
  double v8; // st7
  double v9; // st6
  __int64 v10; // rax
  double v11; // st7
  struct gbTexture *v12; // ebx
  int v13; // ecx
  struct gbTextureArray *v14; // eax
  struct gbTextureArray *v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // edi
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  gbColorQuad v22; // [esp-Ch] [ebp-94h] BYREF
  int v23; // [esp+10h] [ebp-78h]
  int v24; // [esp+14h] [ebp-74h]
  int v25; // [esp+18h] [ebp-70h]
  int v26; // [esp+1Ch] [ebp-6Ch] BYREF
  int v27; // [esp+24h] [ebp-64h] BYREF
  int v28; // [esp+28h] [ebp-60h]
  int v29; // [esp+2Ch] [ebp-5Ch]
  int v30; // [esp+30h] [ebp-58h]
  int v31[5]; // [esp+34h] [ebp-54h] BYREF
  _BYTE v32[64]; // [esp+48h] [ebp-40h] BYREF

  result = *(_DWORD *)(this + 56);
  if ( !result )
    return result;
  v3 = *(_DWORD *)(this + 16);
  v4 = (int *)(this + 16);
  v24 = *(_DWORD *)(this + 24);
  v5 = v3 + v24;
  v23 = v3;
  v6 = 1.0 - *(float *)(this + 72);
  v7 = *(_DWORD *)(this + 20);
  v27 = v5 / 2;
  v8 = v6 * (double)(v5 / 2);
  v26 = *(_DWORD *)(this + 28);
  v25 = v7;
  v9 = (double)v23 * *(float *)(this + 72);
  v28 = (v7 + v26) / 2;
  v31[0] = (__int64)(v9 + v8);
  v10 = (__int64)((double)v24 * *(float *)(this + 72) + v8);
  v11 = (1.0 - *(float *)(this + 76)) * (double)v28;
  v31[2] = v10;
  v31[1] = (__int64)((double)v7 * *(float *)(this + 76) + v11);
  v31[3] = (__int64)((double)v26 * *(float *)(this + 76) + v11);
  v12 = (struct gbTexture *)sub_445F60((_DWORD *)(this + 116), *(_DWORD *)(this + 96));
  if ( !v12 )
    goto LABEL_6;
  v13 = *(_DWORD *)(this + 96);
  v22.Green = *(_DWORD *)(this + 4 * v13 + 184);
  v22.Blue = 276;
  v22.ColorQuadFmt = v13;
  ((gbColorQuad *)&v22)->gbColorQuad((struct gbColorQuad *)(this + 8));
  v14 = ((gbTextureArray *)v32)->gbTextureArray(v12);
  ((_DWORD *)(this + 16))->_CheckItem(v31, v14, v22.ColorQuadFmt, v22.Blue, (float *)v22.Green);
  if ( !*(_DWORD *)(this + 60) )
  {
    if ( *(_DWORD *)(this + 196) )
    {
      v22.Green = *(_DWORD *)(this + 200);
      v22.Blue = 276;
      v22.ColorQuadFmt = v22.Green;
      ((gbColorQuad *)&v22)->gbColorQuad((struct gbColorQuad *)(this + 8));
      v15 = ((gbTextureArray *)v32)->gbTextureArray(*(struct gbTexture **)(this + 196));
      ((_DWORD *)(this + 16))->_CheckItem((int *)(this + 16), v15, v22.ColorQuadFmt, v22.Blue, (float *)v22.Green);
      goto LABEL_7;
    }
LABEL_6:
    ((_TextureLib_Data *)*v4)->~_TextureLib_Data(*(_DWORD *)(this + 20), *(_DWORD *)(this + 24), *(_DWORD *)(this + 28), (float *)&g_GameData_0._data[12992]);
  }
LABEL_7:
  if ( *(_BYTE *)(this + 212) )
  {
    v16 = *v4;
    v26 = *(_DWORD *)(this + 4);
    v17 = *(_DWORD *)(this + 20);
    v29 = *(_DWORD *)(this + 24);
    v18 = *(_DWORD *)(this + 108);
    v30 = *(_DWORD *)(this + 28);
    v19 = v18 + v17;
    v27 = *(_DWORD *)(this + 104) + v16;
    v20 = *(_DWORD *)(this + 60);
    v28 = v19;
    if ( !v20 || *(_DWORD *)(this + 96) == 2 )
    {
      BYTE2(v26) = (BYTE2(v26) - 64) & ((BYTE2(v26) - 64 < 0) - 1);
      BYTE1(v26) = (BYTE1(v26) - 64) & ((BYTE1(v26) - 64 < 0) - 1);
      v21 = *(_DWORD *)(this + 96);
      LOBYTE(v26) = (v26 - 64) & (((unsigned __int8)v26 - 64 < 0) - 1);
      if ( v21 == 2 )
        v28 = v19 + 6;
    }
    if ( *(_BYTE *)(this + 112) )
    {
      v22.Green = 1;
      v22.Blue = 2;
    }
    else
    {
      v22.Green = *(_DWORD *)(this + 208);
      v22.Blue = 1;
    }
    UIRenderPar(this + 212, (int)&v27, &v26, v22.Blue, v22.Green);
  }
  return ((UIWnd *)this)->GetID();
}
