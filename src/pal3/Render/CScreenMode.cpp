#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/CPK.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/PalScript.h"
#include "pal3/gen/PalScriptMgr.h"
#include "pal3/gen/PtrArray.h"
#include "pal3/gen/UICursor.h"
#include "pal3/gen/UIQuadManager.h"
#include "pal3/gen/UIRenderObj.h"

// Forward declarations for unnamed functions
int sub_42C1C0(...);
int sub_53C420(...);
int sub_53C460(...);
int sub_53C470(...);
int sub_53DFB0(...);
int sub_53E510(...);
int sub_53E740(...);
int sub_53E890(...);
int sub_5694F0(...);

// Unnamed globals (extern)
extern char aDatascriptMusi[];
extern char aMovieMovieCpk[];
extern char aMovieMovieEndC[];
extern char aMusicMusicCpk[];
extern unsigned char byte_17B41E8;
extern unsigned char byte_56A634;

// 0x0053C340
char CScreenMode::InitCPK(int a2, int a3)
{
  char result; // al
  CPK *v5; // esi
  CPK *v6; // edi
  char Buffer[320]; // [esp+14h] [ebp-140h] BYREF

  if ( a3 )
    result = BinkSetSoundSystem(BinkOpenDirectSound, a2);
  else
    result = BinkSetSoundSystem(BinkOpenMiles, a2);
  if ( (g_nGameFlags & 2) != 0 )
  {
    v5 = (CPK *)((char *)this + 16);
    ((CPK *)((char *)this + 16))->SetOpenMode(CPKM_Normal);
    v6 = (CPK *)((char *)this + 917964);
    v6->SetOpenMode(CPKM_Normal);
    if ( v5->IsValidCPK(aMovieMovieCpk) )
    {
      v5->Load(aMovieMovieCpk);
    }
    else
    {
      sprintf(Buffer, "%s%s", Data, aMovieMovieCpk);
      if ( v5->IsValidCPK(Buffer) )
        v5->Load(Buffer);
    }
    result = v6->IsValidCPK(aMovieMovieEndC);
    if ( result )
      return v6->Load(aMovieMovieEndC);
  }
  return result;
}

// 0x0053C440
int CScreenMode::CreateDevice(int a, int b, int c, int d)
{
  return sub_5694F0((int)this, (const char *)a, b, c, d);
}

// 0x0053C5A0
int CScreenMode::PlayVideo(int a2)
{
  int Data; // esi
  UIRenderObj *Instance; // eax
  UIRenderObj *v5; // eax
  UIRenderObj *v7; // eax
  struct tagMSG Msg; // [esp+4Ch] [ebp-1Ch] BYREF

  if ( *((_DWORD *)this + 3) )
  {
    Data = g_Input.KeyInfo[177].Data;
    (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)(g_Input.KeyInfo[177].Data + 1816)
                                                                         + 172))(
      *(_DWORD *)(g_Input.KeyInfo[177].Data + 1816),
      0,
      0,
      1,
      -16777216,
      1065353216,
      0);
    (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(**(_DWORD **)(Data + 1816) + 68))(
      *(_DWORD *)(Data + 1816),
      0,
      0,
      0,
      0);
    (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(**(_DWORD **)(Data + 1816) + 172))(
      *(_DWORD *)(Data + 1816),
      0,
      0,
      1,
      -16777216,
      1065353216,
      0);
    Instance = (UIRenderObj *)UIQuadManager::GetInstance();
    Instance->~UIRenderObj(0);
    do
    {
      while ( PeekMessageA(&Msg, 0, 0, 0, 1u) )
      {
        if ( Msg.message == 18 )
        {
          PostQuitMessage(Msg.wParam);
LABEL_13:
          sub_53C420((int *)this);
          UICursor::IRender();
          v5 = (UIRenderObj *)UIQuadManager::GetInstance();
          v5->~UIRenderObj(1u);
          return 0;
        }
        if ( a2 && Msg.message == 258 && Msg.wParam == 27 )
          goto LABEL_13;
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
      }
    }
    while ( sub_53C460((int *)this) || !sub_53C470((int *)this) );
    sub_53C420((int *)this);
    UICursor::IRender();
    v7 = (UIRenderObj *)UIQuadManager::GetInstance();
    v7->~UIRenderObj(1u);
  }
  return 1;
}

// 0x0053C6F0
int CScreenMode::SetViewport(int x, int y)
{
  *((_DWORD *)this + 1) = x;
  *((_DWORD *)this + 2) = y;
  return x;
}

// 0x0053C710
int CScreenMode::GetWidth()
{
  int result; // eax

  result = *((_DWORD *)this + 3);
  if ( result )
    return *(_DWORD *)result;
  return result;
}

// 0x0053C720
int CScreenMode::GetHeight()
{
  int result; // eax

  result = *((_DWORD *)this + 3);
  if ( result )
    return *(_DWORD *)(result + 4);
  return result;
}

// 0x0053CDD0
int CScreenMode::SetState(int state)
{
  *((_DWORD *)this + 1161) = state;
  return state;
}

// 0x0053D1E0
void CScreenMode::SetAudioParam()
{
  int i; // edi
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int j; // edi
  int v7; // ecx
  int v8; // eax
  int k; // edi

  for ( i = 0; i < *((_DWORD *)this + 5); ++i )
  {
    if ( i < 0 || i >= *((_DWORD *)this + 5) )
      v3 = 0;
    else
      v3 = *(_DWORD *)(*((_DWORD *)this + 4) + 4 * i);
    if ( !v3->ClearAllScript() && i >= 0 && i < *((_DWORD *)this + 5) )
      *(_DWORD *)(*((_DWORD *)this + 4) + 4 * i) = 0;
  }
  v4 = 0;
  while ( v4 < *((_DWORD *)this + 5) )
  {
    if ( v4 >= 0 && v4 < *((_DWORD *)this + 5) && *(_DWORD *)(*((_DWORD *)this + 4) + 4 * v4) )
      ++v4;
    else
      ((PtrArray *)(PtrArray *)this + 1)->InsertAt(v4, 1);
  }
  v5 = *((_DWORD *)this + 1);
  for ( j = 0; j < v5; ++j )
  {
    if ( j < 0 || j >= v5 )
      v7 = 0;
    else
      v7 = *(_DWORD *)(*(_DWORD *)this + 4 * j);
    if ( sub_42C1C0(v7) && j >= 0 && j < *((_DWORD *)this + 1) )
      *(_DWORD *)(*(_DWORD *)this + 4 * j) = 0;
    v5 = *((_DWORD *)this + 1);
  }
  v8 = *((_DWORD *)this + 1);
  for ( k = 0; k < v8; v8 = *((_DWORD *)this + 1) )
  {
    if ( k >= 0 && k < v8 && *(_DWORD *)(*(_DWORD *)this + 4 * k) )
      ++k;
    else
      ((PtrArray *)this)->InsertAt(k, 1);
  }
}

// 0x0053D2D0
char CScreenMode::IsAudioReady()
{
  return *((int *)this + 1) <= 0 && *((int *)this + 5) <= 0;
}

// 0x0053DD70
void CScreenMode::SetMode(int mode)
{
  gbAudioManager *v3; // eax
  gbAudioManager *v4; // edi
  bool v5; // zf
  int v6; // eax
  CPK *v7; // esi
  int v8; // [esp+Ch] [ebp-268h] BYREF
  OpenBaseFile v9; // [esp+10h] [ebp-264h] BYREF
  gbAudioManager *v10; // [esp+14h] [ebp-260h]
  char Buffer[324]; // [esp+18h] [ebp-25Ch] BYREF
  gbAudioMgrDesc v12; // [esp+15Ch] [ebp-118h] BYREF
  int v13; // [esp+270h] [ebp-4h]

  if ( (g_nGameFlags & 5) != 0 )
  {
    ((gbAudioMgrDesc *)&v12)->gbAudioMgrDesc();
    v3 = (gbAudioManager *)((operator *)0xF4u)->new();
    v10 = v3;
    v13 = 0;
    if ( v3 )
      v4 = (gbAudioManager *)v3->gbAudioManager(&v8, &v12);
    else
      v4 = 0;
    v13 = -1;
    v5 = v8 == 0;
    *((_DWORD *)this + 202) = v4;
    if ( v5 )
    {
      if ( v4 )
      {
        v4->~gbAudioManager();
        operator delete(v4);
      }
      *((_DWORD *)this + 202) = 0;
      v6 = g_nGameFlags;
      LOBYTE(v6) = g_nGameFlags & 0xFA;
      g_nGameFlags = v6;
    }
    else
    {
      *((_DWORD *)this + 207) = 0;
      *((_DWORD *)this + 6) = 0;
      ((OpenBaseFile *)&v9)->OpenBaseFile();
      v13 = 1;
      ((PalScript *)((char *)this + 284))->LoadFromFile(aDatascriptMusi);
      if ( (g_nGameFlags & 2) != 0 )
      {
        v7 = (CPK *)((char *)this + 832);
        v7->SetOpenMode(CPKM_Normal);
        if ( v7->IsValidCPK(aMusicMusicCpk) )
        {
          v7->Load(aMusicMusicCpk);
        }
        else
        {
          sprintf(Buffer, "%s%s", Data, aMusicMusicCpk);
          if ( v7->IsValidCPK(Buffer) )
            v7->Load(Buffer);
        }
      }
      v13 = -1;
      ((OpenNULLFile **)&v9)->OpenNULLFile();
    }
  }
}

// 0x0053DEF0
void CScreenMode::Restore()
{
  void *v2; // esi

  sub_53E890(this);
  v2 = (void *)*((_DWORD *)this + 202);
  if ( v2 )
  {
    ((gbAudioManager *)*((gbAudioManager **)this + 202))->~gbAudioManager();
    operator delete(v2);
    *((_DWORD *)this + 202) = 0;
  }
}

// 0x0053DF70
char *CScreenMode::GetInstance()
{
  return byte_17B41E8;
}

// 0x0053E2E0
void CScreenMode::AudioSetPosition(void *pPos, int a3)
{
  int v3; // eax

  if ( (g_nGameFlags & 1) != 0 )
  {
    v3 = sub_53DFB0((int *)this, pPos);
    if ( v3 )
    {
      *(_DWORD *)(*(_DWORD *)(v3 + 16) + 8) = a3;
      ((gbSound2DNode *)*(gbSound2DNode **)(v3 + 16))->Play();
    }
  }
}

// 0x0053E490
void CScreenMode::AudioUpdate()
{
  if ( (g_nGameFlags & 1) != 0 )
  {
    if ( g_Input.KeyInfo[177].CountMode )
    {
      ((gbAudioManager *)*((gbAudioManager **)this + 202))->SetListenerPosition((const struct gbVec3D *)(g_Input.KeyInfo[177].CountMode + 492));
      ((gbAudioManager *)*((gbAudioManager **)this + 202))->SetListenerOrientation((struct gbVec3D *)(g_Input.KeyInfo[177].CountMode + 504), (struct gbVec3D *)(g_Input.KeyInfo[177].CountMode + 516));
    }
  }
}

// 0x0053E500
int CScreenMode::GetAudioManager()
{
  return *((_DWORD *)this + 202);
}

// 0x0053E950
void CScreenMode::AudioStopAll()
{
  char *v2; // eax
  const char *v3; // [esp-8h] [ebp-Ch]

  v3 = (const char *)(UISceneUpdate() + 32);
  v2 = (char *)UISceneUpdate();
  sub_53E510((int)this, v2, v3, 0);
}

// 0x0053EA60
void CScreenMode::AudioFadeOut()
{
  char *v1; // eax

  if ( *((_DWORD *)this + 4) )
  {
    v1 = (char *)*((_DWORD *)this + 3);
    if ( !v1 )
      v1 = byte_56A634;
    sub_53E740((gbAudioManager **)this, v1, *((gbAudioManager **)this + 6));
  }
}
