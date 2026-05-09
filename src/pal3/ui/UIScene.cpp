#include "pal3/gen/UIScene.h"

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
      (*(void (__thiscall **)(_DWORD, _DWORD))(**((_DWORD **)this + 123284) + 16))(*((_DWORD *)this + 123284), 0);
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
  (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(v1 + 136) + 16))(*(_DWORD *)(v1 + 136), 0);
  return 1;
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
    sub_445F20((gbRefObject **)this + 19);
    *((_DWORD *)this + 37) = 0;
    OpenBaseFile::OpenBaseFile(&v4);
    v6 = 0;
    sprintf(Buffer, "%s%d.tga", path, 0);
    while ( (int)g_pVFileSys->FileExistNum(Buffer) > 0 )
    {
      if ( !sub_445ED0() )
        sub_445F20((gbRefObject **)this + 19);
      ++v2;
      ++*((_DWORD *)this + 37);
      sprintf(Buffer, "%s%d.tga", path, v2);
    }
    *((_DWORD *)this + 40) = 0;
    sub_43A660(this);
    v6 = -1;
    OpenNULLFile::OpenNULLFile(&v4);
  }
}

// 0x0043A770
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __thiscall sub_43A770(_DWORD *this)
{
  UIWnd::UIWnd();
  UIWnd::DestroyChildren(this + 29);
  *(this + 24) = 0;
  *(this + 49) = 0;
  *this = &off_56AC70;
  *((_BYTE *)this + 204) = 1;
  memset(this + 53, 0, 0x80u);
  *(this + 19) = 1065353216;
  *(this + 18) = 1065353216;
  *(this + 52) = 1;
}

// 0x0043AB00
int sub_43AB00(char *this)
{
  sub_445F20(this + 116);
  return sub_445C10(this);
}

// 0x0043AB20
int sub_43AB20(int this, int a2, int a3)
{
  BOOL v4; // edi
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  char *v13; // [esp-8h] [ebp-20h]
  POINT pt; // [esp+10h] [ebp-8h] BYREF

  GRPinput::GetCursorPos(&pt);
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
    if ( v4 && MEMORY[0xBFC5F4] == 1 )
    {
      v6 = *(_DWORD *)(this + 32);
      if ( v6 )
        (*(void (__thiscall **)(int, int, _DWORD, int))(*(_DWORD *)v6 + 24))(v6, 1021, *(_DWORD *)(this + 12), 1);
      if ( *(_BYTE *)(this + 340) )
      {
        v13 = pPos[0];
        CScreenMode::GetInstance();
        v13->AudioSetPosition(1);
      }
    }
    *(_DWORD *)(this + 96) = 0;
    return 0;
  }
  if ( !a3 )
  {
    *(_DWORD *)(this + 96) = 0;
    return a2->HitTest(0);
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
      v8 = *(_DWORD *)(this + 32);
      *(_BYTE *)(this + 204) = 1;
      if ( v8 )
        (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1003, *(_DWORD *)(this + 12), 0);
    }
    goto LABEL_30;
  }
  if ( MEMORY[0xBFC5F4] == 1 && (MEMORY[0xBFC5E8] & 0xF) == 2 && *(_BYTE *)(this + 68) )
  {
    v7 = *(_DWORD *)(this + 32);
    *(_DWORD *)(this + 96) = 2;
    if ( v7 )
    {
      (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v7 + 24))(v7, 1020, *(_DWORD *)(this + 12), 0);
      *(_BYTE *)(this + 204) = 0;
      goto LABEL_30;
    }
  }
  else if ( MEMORY[0xBFC5F4] == 1 )
  {
    v10 = *(_DWORD *)(this + 32);
    *(_DWORD *)(this + 96) = 2;
    if ( v10 )
    {
      (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(v10, 1004, *(_DWORD *)(this + 12), 0);
      *(_BYTE *)(this + 204) = 0;
      goto LABEL_30;
    }
  }
  else
  {
    v11 = *(_DWORD *)(this + 32);
    if ( v11 )
      (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1002, *(_DWORD *)(this + 12), 0);
  }
  *(_BYTE *)(this + 204) = 0;
LABEL_30:
  if ( *(_DWORD *)(this + 96) == 2 && (MEMORY[0xBFC5E8] & 0xF) != 1 )
  {
    if ( v4 )
    {
      v9 = *(_DWORD *)(this + 32);
      *(_DWORD *)(this + 96) = 1;
      if ( v9 )
        (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1001, *(_DWORD *)(this + 12), 0);
    }
    else
    {
      *(_DWORD *)(this + 96) = 0;
    }
  }
  v12 = a2->HitTest(a3);
  return v4 || v12;
}

// 0x0043AD40
int sub_43AD40(int this)
{
  int result; // eax
  int v3; // ecx
  _DWORD *v4; // edi
  int v5; // eax
  double v6; // st7
  int v7; // ecx
  double v8; // st7
  double v9; // st6
  __int64 v10; // rax
  double v11; // st7
  struct gbTexture *v12; // ebx
  int v13; // ecx
  gbTextureArray *v14; // eax
  gbTextureArray *v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // edi
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // [esp-Ch] [ebp-94h] BYREF
  int v23; // [esp-8h] [ebp-90h]
  int v24; // [esp-4h] [ebp-8Ch]
  int v25; // [esp+10h] [ebp-78h]
  int v26; // [esp+14h] [ebp-74h]
  int v27; // [esp+18h] [ebp-70h]
  int v28; // [esp+1Ch] [ebp-6Ch] BYREF
  int v29; // [esp+24h] [ebp-64h] BYREF
  int v30; // [esp+28h] [ebp-60h]
  int v31; // [esp+2Ch] [ebp-5Ch]
  int v32; // [esp+30h] [ebp-58h]
  _DWORD v33[5]; // [esp+34h] [ebp-54h] BYREF
  _BYTE v34[64]; // [esp+48h] [ebp-40h] BYREF

  result = *(_DWORD *)(this + 56);
  if ( !result )
    return result;
  v3 = *(_DWORD *)(this + 16);
  v4 = (_DWORD *)(this + 16);
  v26 = *(_DWORD *)(this + 24);
  v5 = v3 + v26;
  v25 = v3;
  v6 = 1.0 - *(float *)(this + 72);
  v7 = *(_DWORD *)(this + 20);
  v29 = v5 / 2;
  v8 = v6 * (double)(v5 / 2);
  v28 = *(_DWORD *)(this + 28);
  v27 = v7;
  v9 = (double)v25 * *(float *)(this + 72);
  v30 = (v7 + v28) / 2;
  v33[0] = (__int64)(v9 + v8);
  v10 = (__int64)((double)v26 * *(float *)(this + 72) + v8);
  v11 = (1.0 - *(float *)(this + 76)) * (double)v30;
  v33[2] = v10;
  v33[1] = (__int64)((double)v7 * *(float *)(this + 76) + v11);
  v33[3] = (__int64)((double)v28 * *(float *)(this + 76) + v11);
  v12 = (struct gbTexture *)sub_445F60(*(_DWORD *)(this + 96));
  if ( !v12 )
    goto LABEL_6;
  v13 = *(_DWORD *)(this + 96);
  v24 = *(_DWORD *)(this + 4 * v13 + 184);
  v23 = 276;
  v22 = v13;
  (gbColorQuad *->gbColorQuad()&v22, (struct gbColorQuad *)(this + 8));
  v14 = (gbTextureArray *->gbTextureArray()v34, v12);
  _TextureLib_Data::_CheckItem(this + 16, v33, v14, v22, v23, v24);
  if ( !*(_DWORD *)(this + 60) )
  {
    if ( *(_DWORD *)(this + 196) )
    {
      v24 = *(_DWORD *)(this + 200);
      v23 = 276;
      v22 = v24;
      (gbColorQuad *->gbColorQuad()&v22, (struct gbColorQuad *)(this + 8));
      v15 = (gbTextureArray *->gbTextureArray()v34, *(struct gbTexture **)(this + 196));
      _TextureLib_Data::_CheckItem(this + 16, this + 16, v15, v22, v23, v24);
      goto LABEL_7;
    }
LABEL_6:
    _TextureLib_Data::~_TextureLib_Data(
      *v4,
      *(_DWORD *)(this + 20),
      *(_DWORD *)(this + 24),
      *(_DWORD *)(this + 28),
      &MEMORY[0xD91780]);
  }
LABEL_7:
  if ( *(_BYTE *)(this + 212) )
  {
    v16 = *v4;
    v28 = *(_DWORD *)(this + 4);
    v17 = *(_DWORD *)(this + 20);
    v31 = *(_DWORD *)(this + 24);
    v18 = *(_DWORD *)(this + 108);
    v32 = *(_DWORD *)(this + 28);
    v19 = v18 + v17;
    v29 = *(_DWORD *)(this + 104) + v16;
    v20 = *(_DWORD *)(this + 60);
    v30 = v19;
    if ( !v20 || *(_DWORD *)(this + 96) == 2 )
    {
      BYTE2(v28) = (BYTE2(v28) - 64) & ((BYTE2(v28) - 64 < 0) - 1);
      BYTE1(v28) = (BYTE1(v28) - 64) & ((BYTE1(v28) - 64 < 0) - 1);
      v21 = *(_DWORD *)(this + 96);
      LOBYTE(v28) = (v28 - 64) & (((unsigned __int8)v28 - 64 < 0) - 1);
      if ( v21 == 2 )
        v30 = v19 + 6;
    }
    if ( *(_BYTE *)(this + 112) )
    {
      v24 = 1;
      v23 = 2;
    }
    else
    {
      v24 = *(_DWORD *)(this + 208);
      v23 = 1;
    }
    UIRenderPar(this + 212, &v29, &v28, v23, v24);
  }
  return sub_445CD0(this);
}
