#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ScriptSystem.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/CGameData.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/CameraSystem.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/PalScript.h"
#include "pal3/gen/PtrArray.h"
#include "pal3/gen/RenderTarget3.h"
#include "pal3/gen/RoleSystem.h"
#include "pal3/gen/ScriptObj.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int UISceneUpdate(...);
int sub_410360(...);
int sub_411E00(...);
int sub_412230(...);
int sub_4122C0(...);
int sub_413CD0(...);
int sub_4142E0(...);
int sub_4150C0(...);
int sub_416BC0(...);
int sub_417420(...);
int sub_417C50(...);
int sub_419090(...);
int sub_419200(...);
int sub_419B30(...);
int sub_41A450(...);
int sub_41B300(...);
int sub_41B6C0(...);
int sub_4318A0(...);
int sub_4326A0(...);
int sub_43A270(...);
int sub_445500(...);
int sub_4524B0(...);

// Unnamed globals (extern)
extern char aDatascriptScen_0[];
extern char aFreeranges[];
extern char aMons[];
extern char aRole[];
extern char aTalkrange[];
extern char aWe015[];
extern char aWe016[];
extern char aWe017[];
extern char aWe018[];
extern char aWe019[];
extern int dword_586194;
extern int dword_58B260;
extern int dword_BFD6D0;
extern int dword_BFD6D4;
extern int dword_BFDA60;
extern int dword_BFDA68;
extern int dword_BFDB80;
extern int dword_BFDB84;
extern int dword_BFDB90;
extern int dword_BFDB98;
extern int dword_BFDB9C;
extern int dword_BFDBA0;
extern int dword_BFDBA4;
extern int dword_BFDBB0;
extern int dword_BFFDB0;
extern int dword_C02198;
extern int dword_C025EC;
extern int dword_C042E8;
extern float flt_58B378;
extern float flt_58DE64;
extern void *off_5861F8;
extern void *off_58B444;
extern void *off_58B448;
extern int unk_8ACD30;
extern int unk_BFDAB0;

// 0x0040C630
void ScriptSystem::Render(void *a1)
{
  __int32 m_nCameraState; // edx
  int v2; // ebx
  RoleSystem *v3; // edi
  _DWORD *Instance; // eax
  int v5; // edi
  gbRenderEffect *v6; // ecx
  struct gbVec3D v7; // [esp+Ch] [ebp-10h] BYREF
  int v8; // [esp+18h] [ebp-4h]

  m_nCameraState = g_SceneMgr.m_nCameraState;
  v2 = 0;
  v3 = (RoleSystem *)&g_SceneMgr.m_slot4[840];
  do
  {
    if ( v2 != m_nCameraState )
    {
      v3->RenderRole(a1, 0);
      m_nCameraState = g_SceneMgr.m_nCameraState;
    }
    v3 = (RoleSystem *)((char *)v3 + 8704);
    ++v2;
  }
  while ( (int)v3 < (int)&g_SceneMgr.m_pGameData );
  if ( flt_58DE64 >= 1.2 )
  {
    ((RoleSystem *)&g_SceneMgr.m_slot4[8704 * m_nCameraState + 840])->RenderRole(a1, 0);
  }
  else if ( rand() % 3 )
  {
    ((RoleSystem *)&g_SceneMgr.m_slot4[8704 * g_SceneMgr.m_nCameraState + 840])->RenderRole(a1, 0);
  }
  else
  {
    Instance = (_DWORD *)RenderTarget3::GetInstance();
    v5 = Instance[1];
    if ( v5 )
    {
      v6 = (gbRenderEffect *)Instance[1];
      v7.x = 0.69999999;
      v7.y = 0.1;
      v7.z = 0.1;
      v8 = 1056964608;
      v6->SetVariant(PARAM_HANDLE_SPECULAR, &v7);
      ((RoleSystem *)&g_SceneMgr.m_slot4[8704 * g_SceneMgr.m_nCameraState + 840])->RenderRole(a1, v5);
    }
  }
  ((RoleSystem *)dword_BFFDB0)->RenderRole(a1, 0);
  ((RoleSystem *)dword_BFDBB0)->RenderRole(a1, 0);
  if ( *(_DWORD *)&g_SceneMgr._gap_c5e0[844] )
  {
    v7 = *(struct gbVec3D *)&g_SceneMgr.m_slot4[8704 * g_SceneMgr.m_nCameraState + 1000];
    ((gbMatrixStack *)a1)->Push();
    v7.y = v7.y + 40.0;
    ((gbMatrixStack *)a1)->Translate(&v7);
    (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)&g_SceneMgr._gap_c5e0[844] + 16))(
      *(_DWORD *)&g_SceneMgr._gap_c5e0[844],
      0);
    ((gbMatrixStack *)a1)->Pop();
  }
}

// 0x0040C790
int ScriptSystem::Cleanup()
{
  int i; // esi
  void (***v1)(_DWORD, int); // ecx
  int result; // eax

  for ( i = 0; i < dword_BFDB84; ++i )
  {
    v1 = *(void (****)(_DWORD, int))(dword_BFDB80 + 4 * i);
    if ( v1 )
      (**v1)(v1, 1);
  }
  sub_4326A0((int)&dword_BFDB80, 0, -1);
  return result;
}

// 0x0040C7D0
char ScriptSystem::Render2()
{
  int i; // esi
  char result; // al
  double v2; // st7
  gbPrintFont *v3; // edi
  int v4; // ebx
  int v5; // ebp
  _DWORD *v6; // esi
  float v7; // [esp+Ch] [ebp-B8h]
  float v8; // [esp+30h] [ebp-94h] BYREF
  int v9; // [esp+34h] [ebp-90h] BYREF
  struct gbVec3D pOut; // [esp+38h] [ebp-8Ch] BYREF
  char Buffer[128]; // [esp+44h] [ebp-80h] BYREF

  sub_445500((int *)unk_BFDAB0._data);
  for ( i = 0; i < dword_BFDB84; ++i )
    ((GRPinput *)*(GRPinput **)(dword_BFDB80 + 4 * i))->SetMouseSensitivity();
  sub_43A270((UIWnd *)&g_SceneMgr.m_pCameraCtrl);
  result = g_SceneMgr.m_slot0[81];
  if ( g_SceneMgr.m_slot0[81] )
  {
    v2 = 32.0 / (double)dword_BFD6D4;
    v3 = (gbPrintFont *)dword_BFDA60->pFontMgr->pAllFont[3];
    *(float *)&v3->curColor.Blue = 32.0 / (double)dword_BFD6D0;
    *(float *)&v3->curColor.Color = v2;
    v3->curColor.ColorQuadFmt = -2134325048;
    v4 = UISceneUpdate();
    v5 = 0;
    if ( *(int *)(v4 + 57568) > 0 )
    {
      v6 = (_DWORD *)(v4 + 58204);
      do
      {
        if ( *(v6 - 122) && *v6 && *((_BYTE *)v6 - 459) == 2 )
        {
          memset(&pOut, 0, sizeof(pOut));
          ((RoleSystem *)(v6 - 158))->GetDirection(&pOut.x);
          ((gbCamera *)&dword_BFDA68->OrthoSize)->PointWorldToScr(&pOut, &v8, (float *)&v9);
          sprintf(Buffer, "%d", *((unsigned __int8 *)v6 - 332));
          v7 = v8 - 0.050000001;
          (*(void (**)(gbPrintFont *, char *, _DWORD, int, int, int))(*(_DWORD *)v3->_pad_0000 + 16))(
            v3,
            Buffer,
            LODWORD(v7),
            v9,
            1176256512,
            1176256512);
        }
        ++v5;
        v6 += 2176;
      }
      while ( v5 < *(_DWORD *)(v4 + 57568) );
    }
    return (*(int (**)(gbPrintFont *))(*(_DWORD *)v3->_pad_0000 + 8))(v3);
  }
  return result;
}

// 0x0040C960
int ScriptSystem::Destroy()
{
  ScriptObj *v0; // esi
  int result; // eax

  ((UIWnd *)&unk_BFDAB0)->Reset();
  ((PalScript *)&g_SceneMgr.m_pCameraCtrl)->Reset();
  ScriptSystem::Cleanup();
  v0 = (ScriptObj *)&g_SceneMgr.m_slot4[840];
  do
  {
    result = v0->Destroy();
    v0 += 8704;
  }
  while ( (int)v0 < (int)&g_SceneMgr.m_pGameData );
  return result;
}

// 0x0040E5F0
int ScriptSystem::Execute(int a1, char a2)
{
  _DWORD *m_pCollisionNode; // ecx
  int v3; // eax
  int v4; // eax
  __int32 m_nCameraState; // ecx
  int v6; // eax
  __int8 *v7; // ecx

  m_pCollisionNode = (_DWORD *)g_SceneMgr.m_pCollisionNode;
  flt_58DE64 = 10.0;
  if ( a2 )
  {
    v3 = 8704 * a1;
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 860] = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 20);
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 864] = m_pCollisionNode[6];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 868] = m_pCollisionNode[7];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 872] = m_pCollisionNode[8];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 876] = m_pCollisionNode[9];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 880] = m_pCollisionNode[10];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 844] = m_pCollisionNode[1];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 848] = m_pCollisionNode[2];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 852] = m_pCollisionNode[3];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 1000] = m_pCollisionNode[40];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 1004] = m_pCollisionNode[41];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 1008] = m_pCollisionNode[42];
    *(__int32 *)((char *)&g_SceneMgr.m_scriptState1 + v3) = m_pCollisionNode[2173];
    *(__int32 *)((char *)&g_SceneMgr.m_scriptState2 + v3) = m_pCollisionNode[2174];
    *(__int32 *)((char *)&g_SceneMgr.m_scriptState3 + v3) = m_pCollisionNode[2175];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 988] = m_pCollisionNode[37];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 992] = m_pCollisionNode[38];
    *(_DWORD *)&g_SceneMgr.m_slot4[v3 + 996] = m_pCollisionNode[39];
    *(_DWORD *)&g_SceneMgr._postSlots[v3 + 8120] = m_pCollisionNode[2172];
    *(_DWORD *)&g_SceneMgr._postSlots[v3 + 60] = m_pCollisionNode[157];
  }
  *(_DWORD *)&g_SceneMgr._postSlots[8704 * g_SceneMgr.m_nCameraState + 64] = 0;
  *(_DWORD *)&g_SceneMgr._postSlots[8704 * a1 + 64] = 1;
  RoleSystemNotify((int)&g_SceneMgr.m_slot4[8704 * a1 + 840]);
  ((CameraSystem *)&g_SceneMgr.m_slot4[8704 * a1 + 840])->Init();
  g_SceneMgr.m_nCameraState = a1;
  if ( dword_BFDA68->pControl[11] )
    ((RoleSystem *)dword_BFDA68)->SetActive((int)&g_SceneMgr.m_slot4[8704 * a1 + 840]);
  if ( a1 == 1 && dword_C025EC == 10 )
  {
    sub_419090((float *)&dword_C02198);
    dword_C042E8 = *(_DWORD *)&g_SceneMgr._midRegion[8688];
  }
  v4 = ((CGameData *)&g_GameData)->SetMode(0);
  if ( v4 )
    sub_4524B0((gbRefObject **)(v4 + 1084), g_SceneMgr.m_nCameraState);
  m_nCameraState = g_SceneMgr.m_nCameraState;
  if ( g_SceneMgr.m_nCameraState == 2 )
  {
    if ( _strcmpi(&g_SceneMgr._midRegion[8878], dword_586194) )
    {
      ((Actor *)&g_SceneMgr._midRegion[9384])->LoadModel();
      strcpy(&g_SceneMgr._midRegion[8878], dword_586194);
      ((RoleSystem *)&g_SceneMgr._midRegion[8704])->UpdateTransform();
    }
    m_nCameraState = g_SceneMgr.m_nCameraState;
  }
  v6 = 0;
  v7 = (__int8 *)&g_SceneMgr.m_slot0[1408 * m_nCameraState + 52];
  while ( !v7[v6] )
  {
    if ( ++v6 > 4 )
      return ((ScriptSystem *)31)->RunEvent(0, 0);
  }
  return v6->RunEvent(1, 1);
}

// 0x004100A0
int ScriptSystem::RunScript(int a1, int a2, int a3)
{
  int result; // eax
  __int8 *v4; // edx
  __int32 m_nCameraState; // edi
  int v6; // ebx
  int v7; // esi
  int v8; // ecx
  int v9; // eax
  _DWORD *v10; // eax
  GRPinput *v11; // esi
  char *Instance; // eax
  void *v13; // [esp-8h] [ebp-13Ch]
  void *pPos[6]; // [esp+10h] [ebp-124h]
  char Buffer[256]; // [esp+28h] [ebp-10Ch] BYREF
  int v16; // [esp+130h] [ebp-4h]

  v4 = (__int8 *)&g_SceneMgr.m_slot0[340];
  m_nCameraState = g_SceneMgr.m_nCameraState;
  v6 = 0;
  v7 = 0;
  do
  {
    LOBYTE(result) = g_SceneMgr.m_slot4[v7 + 832];
    if ( (_BYTE)result )
    {
      LOBYTE(result) = a3;
      if ( !(_BYTE)a3 || v7 == m_nCameraState )
      {
        v8 = *(_DWORD *)v4;
        v9 = *(_DWORD *)v4 - a1;
        if ( v9 < 1 )
          v9 = 1;
        *(_DWORD *)v4 = v9;
        result = v9 - v8;
        if ( v7 == m_nCameraState )
          v6 = result;
      }
    }
    v4 += 1408;
    ++v7;
  }
  while ( (int)v4 < (int)&g_SceneMgr._postSlots[340] );
  if ( v6 < 0 )
  {
    sprintf(Buffer, "%d", v6);
    v10 = (_DWORD *)operator new(0x24u);
    pPos[5] = v10;
    v16 = 0;
    if ( v10 )
      v11 = (GRPinput *)((GRPinput *)v10)->SetMousePos();
    else
      v11 = 0;
    v16 = -1;
    v11->SetJoystickPos(Buffer, 0);
    ((PtrArray *)&dword_BFDB80)->SetAt(dword_BFDB84, (int)v11);
    LOBYTE(result) = a2;
    if ( (_BYTE)a2 )
    {
      pPos[0] = aWe015;
      pPos[1] = aWe016;
      pPos[2] = aWe017;
      pPos[3] = aWe018;
      pPos[4] = aWe019;
      v13 = (void *)pPos[g_SceneMgr.m_nCameraState];
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v13, 1);
    }
  }
  return result;
}

// 0x004101F0
int ScriptSystem::RunWithDelay(float delay, int a2, int a3)
{
  __int32 m_nCameraState; // ebx
  int v4; // edi
  __int8 *v5; // esi
  int v6; // ebp
  __int64 v7; // rax
  int result; // eax
  _DWORD *v9; // eax
  GRPinput *v10; // esi
  char *Instance; // eax
  void *v12; // [esp-8h] [ebp-144h]
  int v13; // [esp+14h] [ebp-128h]
  void *pPos[5]; // [esp+1Ch] [ebp-120h]
  char Buffer[256]; // [esp+30h] [ebp-10Ch] BYREF
  int v16; // [esp+138h] [ebp-4h]

  m_nCameraState = g_SceneMgr.m_nCameraState;
  v4 = 0;
  v13 = 0;
  v5 = (__int8 *)&g_SceneMgr.m_slot0[340];
  do
  {
    if ( g_SceneMgr.m_slot4[v4 + 832] && (!(_BYTE)a3 || v4 == m_nCameraState) )
    {
      v6 = *(_DWORD *)v5;
      v7 = (__int64)((double)*(int *)v5 - (double)*((int *)v5 - 12) * delay);
      *(_DWORD *)v5 = v7;
      if ( (int)v7 <= 0 )
        *(_DWORD *)v5 = 1;
      if ( v4 == m_nCameraState )
        v13 = *(_DWORD *)v5 - v6;
    }
    v5 += 1408;
    ++v4;
  }
  while ( (int)v5 < (int)&g_SceneMgr._postSlots[340] );
  result = v13;
  if ( v13 < 0 )
  {
    sprintf(Buffer, "%d", v13);
    v9 = (_DWORD *)operator new(0x24u);
    v16 = 0;
    if ( v9 )
      v10 = (GRPinput *)((GRPinput *)v9)->SetMousePos();
    else
      v10 = 0;
    v16 = -1;
    v10->SetJoystickPos(Buffer, 0);
    ((PtrArray *)&dword_BFDB80)->SetAt(dword_BFDB84, (int)v10);
    LOBYTE(result) = a2;
    if ( (_BYTE)a2 )
    {
      pPos[0] = aWe015;
      pPos[1] = aWe016;
      pPos[2] = aWe017;
      pPos[3] = aWe018;
      pPos[4] = aWe019;
      v12 = (void *)pPos[g_SceneMgr.m_nCameraState];
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v12, 1);
    }
  }
  return result;
}

// 0x00410470
int ScriptSystem::RunEvent(int eventId, int a2, int a3)
{
  int result; // eax
  __int32 m_nCameraState; // ecx
  int *v5; // eax
  __int32 v6; // eax
  char *v7; // eax
  char Buffer[32]; // [esp+8h] [ebp-20h] BYREF

  LOBYTE(result) = a2;
  if ( !(_BYTE)a2 || (unsigned int)eventId > 4 || dword_BFDBA4 != eventId )
  {
    memset(&dword_BFDB90, 0, 0x20u);
    m_nCameraState = g_SceneMgr.m_nCameraState;
    dword_BFDB90 = a3;
    dword_BFDBA4 = eventId;
    v5 = (int *)&g_SceneMgr.m_slot4[8704 * g_SceneMgr.m_nCameraState + 844];
    dword_BFDB98 = *v5;
    dword_BFDB9C = v5[1];
    dword_BFDBA0 = v5[2];
    if ( !a3 )
    {
      v6 = 1408 * g_SceneMgr.m_nCameraState;
      g_SceneMgr.m_slot0[v6 + 52] = 0;
      g_SceneMgr.m_slot0[v6 + 53] = 0;
      g_SceneMgr.m_slot0[v6 + 54] = 0;
      g_SceneMgr.m_slot0[v6 + 55] = 0;
      g_SceneMgr.m_slot0[v6 + 56] = 0;
    }
    result = 5 * m_nCameraState;
    if ( !g_SceneMgr.m_slot0[1408 * m_nCameraState + 77] && (unsigned int)eventId <= 4 && !a3 )
    {
      sprintf(Buffer, off_5861F8, eventId);
      v7 = ((PalScript *)&unk_8ACD30)->SetAppName(Buffer);
      sub_410360(v7);
      result = g_SceneMgr.m_nCameraState;
      g_SceneMgr.m_slot0[1408 * g_SceneMgr.m_nCameraState + 52 + eventId] = 1;
    }
  }
  return result;
}

// 0x00411F60
int ScriptSystem::UpdateTimers(float dt)
{
  int v1; // ecx
  double v2; // st6
  int v3; // esi
  int result; // eax
  int v5; // eax
  unsigned __int8 v7; // c0
  unsigned __int8 v8; // c3
  int v9; // [esp+8h] [ebp-24h]
  float v10; // [esp+Ch] [ebp-20h]
  int v11; // [esp+10h] [ebp-1Ch]
  int v12; // [esp+14h] [ebp-18h]
  int v13; // [esp+18h] [ebp-14h]
  int v14; // [esp+1Ch] [ebp-10h]
  int v15; // [esp+20h] [ebp-Ch]
  int v16; // [esp+24h] [ebp-8h]
  int v17; // [esp+28h] [ebp-4h]

  v3 = v1;
  result = *(_DWORD *)(v1 + 632);
  if ( result )
  {
    if ( *(_DWORD *)(v1 + 144) || *(_DWORD *)(v1 + 1264) == 4 )
      ((Actor *)(v1 + 680))->QueryState();
    switch ( *(_DWORD *)(v3 + 1264) )
    {
      case 0:
        sub_412230((float *)v3, v2, 0, 0);
        return result;
      case 1:
        result = sub_417C50(v3, v2, SLODWORD(dt));
        if ( result )
          goto LABEL_23;
        return result;
      case 2:
        sub_413CD0(v3, v2, SLODWORD(dt));
        if ( !*(_DWORD *)(v3 + 1268) )
          goto LABEL_16;
        goto LABEL_13;
      case 3:
        if ( *(_DWORD *)(v3 + 1268) == 12 )
        {
LABEL_13:
          *(_DWORD *)(v3 + 1296) = *(_DWORD *)(v3 + 1308);
          *(_DWORD *)(v3 + 1300) = *(_DWORD *)(v3 + 1312);
          *(_DWORD *)(v3 + 1304) = *(_DWORD *)(v3 + 1316);
        }
        else
        {
          sub_413CD0(v3, v2, SLODWORD(dt));
          if ( *(_DWORD *)(v3 + 1268) )
          {
            *(_DWORD *)(v3 + 1296) = *(_DWORD *)(v3 + 1308);
            *(_DWORD *)(v3 + 1300) = *(_DWORD *)(v3 + 1312);
            *(_DWORD *)(v3 + 1304) = *(_DWORD *)(v3 + 1316);
          }
        }
LABEL_16:
        v5 = *(_DWORD *)(v3 + 1388);
        if ( v5 && v5 != 4 )
          sub_416BC0(v3);
        goto LABEL_23;
      case 4:
        sub_4150C0(v3, v2, SLODWORD(dt));
        if ( result )
          goto LABEL_23;
        return result;
      case 5:
        sub_417420(v3, v2, SLODWORD(dt));
        goto LABEL_23;
      case 6:
        sub_419B30(v3, dt);
        goto LABEL_23;
      case 7:
        sub_41A450(v3, v2, SLODWORD(dt));
        goto LABEL_23;
      default:
LABEL_23:
        *(_DWORD *)(v3 + 1300) = 0;
        if ( !(v7 | v8) )
        {
          if ( *(_DWORD *)(v3 + 636) || *(_DWORD *)(v3 + 1264) == 4 )
          {
            sub_411E00(v3, dt, 1);
          }
          else
          {
            v12 = *(_DWORD *)(v3 + 4);
            v13 = *(_DWORD *)(v3 + 8);
            v15 = *(_DWORD *)(v3 + 148);
            v14 = *(_DWORD *)(v3 + 12);
            v16 = *(_DWORD *)(v3 + 152);
            v17 = *(_DWORD *)(v3 + 156);
            v9 = *(_DWORD *)(v3 + 160);
            v10 = *(float *)(v3 + 164);
            v11 = *(_DWORD *)(v3 + 168);
            sub_411E00(v3, dt, 1);
            if ( fabs(*(float *)(v3 + 164) - v10) > 45.0 )
            {
              *(_DWORD *)(v3 + 12) = v14;
              *(_DWORD *)(v3 + 4) = v12;
              *(_DWORD *)(v3 + 8) = v13;
              *(_DWORD *)(v3 + 156) = v17;
              *(_DWORD *)(v3 + 148) = v15;
              *(_DWORD *)(v3 + 152) = v16;
              *(_DWORD *)(v3 + 168) = v11;
              *(_DWORD *)(v3 + 160) = v9;
              *(float *)(v3 + 164) = v10;
              sub_4142E0((RoleSystem *)v3);
            }
          }
        }
        result = (*(int (**)(int))(*(_DWORD *)(v3 + 56) + 4))(v3 + 56);
        if ( !result )
          result = sub_41B300((void ***)v3);
        if ( *(_DWORD *)(v3 + 1264) == 3 )
          LOBYTE(result) = sub_41B6C0(v3, -1);
        break;
    }
  }
  return result;
}

// 0x004194C0
int ScriptSystem::UpdateObjects(float dt)
{
  int v1; // ecx
  int v2; // esi
  float *v3; // edi
  gbVec3D *v4; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  int result; // eax
  float v10; // [esp+Ch] [ebp-44h]
  float v11; // [esp+Ch] [ebp-44h]
  float v12; // [esp+10h] [ebp-40h]
  float v13; // [esp+10h] [ebp-40h]
  float v14; // [esp+14h] [ebp-3Ch]
  float v15; // [esp+14h] [ebp-3Ch]
  float v16; // [esp+18h] [ebp-38h]
  float v17; // [esp+1Ch] [ebp-34h]
  gbVec3D v18; // [esp+20h] [ebp-30h] BYREF
  struct gbVec3D v19; // [esp+2Ch] [ebp-24h] BYREF
  gbVec3D v20; // [esp+38h] [ebp-18h] BYREF
  gbVec3D v21; // [esp+44h] [ebp-Ch] BYREF
  float dta; // [esp+54h] [ebp+4h]

  v2 = v1;
  ((Actor *)(v1 + 680))->QueryState();
  if ( *(_DWORD *)&g_SceneMgr._midRegion[1284] <= 2u
    && *(_DWORD *)(v2 + 1284) != *(_DWORD *)&g_SceneMgr._midRegion[1284] )
  {
    *(_DWORD *)(v2 + 1284) = *(_DWORD *)&g_SceneMgr._midRegion[1284];
    ((RoleSystem *)v2)->UpdatePath(*(int *)&g_SceneMgr._midRegion[1284]);
  }
  v3 = (float *)(v2 + 1344);
  sub_419090((float *)(v2 + 1344));
  if ( !sub_419200(v2, dt, 300.0, v16, v17) )
    goto LABEL_9;
  v14 = *(float *)(v2 + 1352) - *(float *)(v2 + 168);
  v12 = *(float *)(v2 + 1348) - *(float *)(v2 + 164);
  v10 = *v3 - *(float *)(v2 + 160);
  v4 = ((gbVec3D *)&v20)->gbVec3D(v10, v12, v14);
  v5 = *(float *)(v2 + 8700) - *(float *)(v2 + 168);
  v18.x = v4->x;
  v18.y = v4->y;
  v15 = v5;
  v6 = *(float *)(v2 + 8696) - *(float *)(v2 + 164);
  v18.z = v4->z;
  v13 = v6;
  v11 = *(float *)(v2 + 8692) - *(float *)(v2 + 160);
  v19 = *((gbVec3D *)&v21)->gbVec3D(v11, v13, v15);
  v7 = ((gbVec3D *)&v18)->Length();
  dta = v7;
  if ( v7 < 0.000049999999 || (v8 = ((gbVec3D *)&v18)->DotProduct(&v19) / dta, v8 >= 0.0) && v8 - dta > -0.1 )
  {
    *(float *)(v2 + 160) = *v3;
    *(_DWORD *)(v2 + 164) = *(_DWORD *)(v2 + 1348);
    *(_DWORD *)(v2 + 168) = *(_DWORD *)(v2 + 1352);
LABEL_9:
    *(_DWORD *)(v2 + 1296) = *(_DWORD *)&g_SceneMgr._midRegion[20];
    *(_DWORD *)(v2 + 1300) = *(_DWORD *)&g_SceneMgr._midRegion[24];
    *(_DWORD *)(v2 + 1304) = *(_DWORD *)&g_SceneMgr._midRegion[28];
    sub_4122C0(v2);
    return result;
  }
  *(_DWORD *)(v2 + 160) = *(_DWORD *)(v2 + 8692);
  *(_DWORD *)(v2 + 164) = *(_DWORD *)(v2 + 8696);
  *(_DWORD *)(v2 + 168) = *(_DWORD *)(v2 + 8700);
  sub_4122C0(v2);
  return result;
}

// 0x0041EFA0
void ScriptSystem::Init()
{
  int v0; // edi
  const char *v1; // esi
  int v2; // edi
  const char *v3; // esi
  PalScript String[8]; // [esp+8h] [ebp-218h] BYREF
  int v5; // [esp+21Ch] [ebp-4h]

  ctor_0x431870(String);
  v5 = 0;
  String->LoadFromFile(aDatascriptScen_0);
  String->SetDirectory(aRole);
  while ( String->HasNext() )
  {
    if ( !_strcmpi(String[0]._pad_000, off_58B448) )
      break;
    v0 = 0;
    v1 = aTalkrange;
    while ( _strcmpi(String[0]._pad_000, v1) )
    {
      v1 += 20;
      ++v0;
      if ( (int)v1 >= (int)&off_58B444 )
        goto LABEL_8;
    }
    String->LoadNext();
    flt_58B378[5 * v0] = atof(String[0]._pad_000);
LABEL_8:
    ;
  }
  String->SetDirectory(aMons);
  while ( String->HasNext() )
  {
    if ( !_strcmpi(String[0]._pad_000, off_58B448) )
      break;
    v2 = 0;
    v3 = aFreeranges;
    while ( _strcmpi(String[0]._pad_000, v3) )
    {
      v3 += 20;
      ++v2;
      if ( (int)v3 >= (int)aTalkrange )
        goto LABEL_16;
    }
    String->LoadNext();
    *(float *)&dword_58B260[5 * v2] = atof(String[0]._pad_000);
LABEL_16:
    ;
  }
  v5 = -1;
  sub_4318A0((int)String);
}
