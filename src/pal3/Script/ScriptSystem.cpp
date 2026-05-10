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
int sub_431870(...);
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
extern int dword_BFFDB0;
extern int dword_C02198;
extern int dword_C025EC;
extern int dword_C042E8;
extern float flt_58B378;
extern float flt_58DE64;
extern void *off_5861F8;
extern void *off_58B444;
extern void *off_58B448;

// 0x0040C630
void ScriptSystem::Render(void *a1)
{
  float x; // edx
  int v2; // ebx
  float *p_y; // edi
  _DWORD *Instance; // eax
  int v5; // edi
  gbRenderEffect *v6; // ecx
  struct gbVec3D v7; // [esp+Ch] [ebp-10h] BYREF
  int v8; // [esp+18h] [ebp-4h]

  x = g_SceneMgr.m_npc[5].m_path.normal[131].x;
  v2 = 0;
  p_y = (float *)&g_SceneMgr.m_npc[0].m_path.normal[83].y;
  do
  {
    if ( v2 != LODWORD(x) )
    {
      ((RoleSystem *)p_y)->RenderRole(a1, 0);
      x = g_SceneMgr.m_npc[5].m_path.normal[131].x;
    }
    p_y += 2176;
    ++v2;
  }
  while ( (int)p_y < (int)&g_SceneMgr.m_npc[5].m_path.normal[58].y );
  if ( flt_58DE64 >= 1.2 )
  {
    ((RoleSystem *)(&g_SceneMgr.m_npc[0].m_path.normal[83].y + 2176 * LODWORD(x)))->RenderRole(a1, 0);
  }
  else if ( rand() % 3 )
  {
    ((RoleSystem *)(&g_SceneMgr.m_npc[0].m_path.normal[83].y + 2176 * LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x)))->RenderRole(a1, 0);
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
      ((RoleSystem *)(&g_SceneMgr.m_npc[0].m_path.normal[83].y
                     + 2176 * LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x)))->RenderRole(a1, v5);
    }
  }
  ((RoleSystem *)dword_BFFDB0)->RenderRole(a1, 0);
  ((RoleSystem *)&g_Input.KeyInfo[198])->RenderRole(a1, 0);
  if ( LODWORD(g_SceneMgr.m_npc[5].m_path.normal[130].x) )
  {
    v7 = *(struct gbVec3D *)(&g_SceneMgr.m_npc[0].m_path.normal[96].z
                           + 2176 * LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x));
    ((gbMatrixStack *)a1)->Push();
    v7.y = v7.y + 40.0;
    ((gbMatrixStack *)a1)->Translate(&v7);
    (*(void (**)(_DWORD, _DWORD))(*(_DWORD *)LODWORD(g_SceneMgr.m_npc[5].m_path.normal[130].x) + 16))(
      LODWORD(g_SceneMgr.m_npc[5].m_path.normal[130].x),
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

  for ( i = 0; i < g_Input.KeyInfo[195].HoldTime; ++i )
  {
    v1 = *(void (****)(_DWORD, int))(g_Input.KeyInfo[195].Data + 4 * i);
    if ( v1 )
      (**v1)(v1, 1);
  }
  sub_4326A0((int)&g_Input.KeyInfo[195], 0, -1);
  return result;
}

// 0x0040C7D0
char ScriptSystem::Render2()
{
  int i; // esi
  char result; // al
  double v2; // st7
  int v3; // edi
  int v4; // ebx
  int v5; // ebp
  _DWORD *v6; // esi
  float v7; // [esp+Ch] [ebp-B8h]
  float v8; // [esp+30h] [ebp-94h] BYREF
  int v9; // [esp+34h] [ebp-90h] BYREF
  struct gbVec3D pOut; // [esp+38h] [ebp-8Ch] BYREF
  char Buffer[128]; // [esp+44h] [ebp-80h] BYREF

  sub_445500(&g_Input.KeyInfo[182].Data);
  for ( i = 0; i < g_Input.KeyInfo[195].HoldTime; ++i )
    ((GRPinput *)*(_DWORD *)(g_Input.KeyInfo[195].Data + 4 * i))->SetMouseSensitivity();
  sub_43A270((UIWnd *)&g_SceneMgr.m_npc[5].m_path.normal[59]);
  result = BYTE1(g_SceneMgr.m_npc[0].m_npcinfo.mrepeat);
  if ( BYTE1(g_SceneMgr.m_npc[0].m_npcinfo.mrepeat) )
  {
    v2 = 32.0 / (double)g_Input.KeyInfo[120].HoldTime;
    v3 = *(_DWORD *)(*(_DWORD *)(g_Input.KeyInfo[177].Data + 208) + 12);
    *(float *)(v3 + 48) = 32.0 / (double)g_Input.KeyInfo[120].Data;
    *(float *)(v3 + 52) = v2;
    *(_DWORD *)(v3 + 44) = -2134325048;
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
          ((gbCamera *)(g_Input.KeyInfo[177].CountMode + 4))->PointWorldToScr(&pOut, &v8, (float *)&v9);
          sprintf(Buffer, "%d", *((unsigned __int8 *)v6 - 332));
          v7 = v8 - 0.050000001;
          (*(void (**)(int, char *, _DWORD, int, int, int))(*(_DWORD *)v3 + 16))(
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
    return (*(int (**)(int))(*(_DWORD *)v3 + 8))(v3);
  }
  return result;
}

// 0x0040C960
int ScriptSystem::Destroy()
{
  float *p_y; // esi
  int result; // eax

  ((UIWnd *)&g_Input.KeyInfo[182])->Reset();
  ((PalScript *)&g_SceneMgr.m_npc[5].m_path.normal[59])->Reset();
  ScriptSystem::Cleanup();
  p_y = (float *)&g_SceneMgr.m_npc[0].m_path.normal[83].y;
  do
  {
    result = ((ScriptObj *)p_y)->Destroy();
    p_y += 2176;
  }
  while ( (int)p_y < (int)&g_SceneMgr.m_npc[5].m_path.normal[58].y );
  return result;
}

// 0x0040E5F0
int ScriptSystem::Execute(int a1, char a2)
{
  float *v2; // ecx
  int v3; // eax
  int v4; // eax
  float x; // ecx
  int v6; // eax
  char *v7; // ecx

  v2 = (float *)*(float **)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132];
  flt_58DE64 = 10.0;
  if ( a2 )
  {
    v3 = 8704 * a1;
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[85].x + v3) = *(float *)(*(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[132]
                                                                                 + 20);
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[85].y + v3) = v2[6];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[85].z + v3) = v2[7];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[86].x + v3) = v2[8];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[86].y + v3) = v2[9];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[86].z + v3) = v2[10];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[83].z + v3) = v2[1];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[84].x + v3) = v2[2];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[84].y + v3) = v2[3];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[96].z + v3) = v2[40];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[97].x + v3) = v2[41];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[97].y + v3) = v2[42];
    *(float *)((char *)&g_SceneMgr.m_npc[1].m_path.normal[77].y + v3) = v2[2173];
    *(float *)((char *)&g_SceneMgr.m_npc[1].m_path.normal[77].z + v3) = v2[2174];
    *(float *)((char *)&g_SceneMgr.m_npc[1].m_path.normal[78].x + v3) = v2[2175];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[95].z + v3) = v2[37];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[96].x + v3) = v2[38];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[96].y + v3) = v2[39];
    *(float *)((char *)&g_SceneMgr.m_npc[1].m_path.normal[77].x + v3) = v2[2172];
    *(float *)((char *)&g_SceneMgr.m_npc[0].m_path.normal[135].z + v3) = v2[157];
  }
  *((_DWORD *)&g_SceneMgr.m_npc[0].m_path.normal[136].x + 2176 * LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x)) = 0;
  *((_DWORD *)&g_SceneMgr.m_npc[0].m_path.normal[136].x + 2176 * a1) = 1;
  RoleSystemNotify((int)(&g_SceneMgr.m_npc[0].m_path.normal[83].y + 2176 * a1));
  ((int)(&g_SceneMgr.m_npc[0].m_path.normal[83].y + 2176 * a1))->Init();
  LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x) = a1;
  if ( *(_DWORD *)(g_Input.KeyInfo[177].CountMode + 448) )
    ((RoleSystem *)g_Input.KeyInfo[177].CountMode)->SetActive((int)(&g_SceneMgr.m_npc[0].m_path.normal[83].y + 2176 * a1));
  if ( a1 == 1 && dword_C025EC == 10 )
  {
    sub_419090((float *)&dword_C02198);
    dword_C042E8 = LODWORD(g_SceneMgr.m_npc[2].m_path.normal[72].x);
  }
  v4 = ((CGameData *)&g_GameData)->SetMode(0);
  if ( v4 )
    sub_4524B0((gbRefObject **)(v4 + 1084), SLODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x));
  x = g_SceneMgr.m_npc[5].m_path.normal[131].x;
  if ( LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x) == 2 )
  {
    if ( _strcmpi((const char *)&g_SceneMgr.m_npc[2].m_path.normal[87].z + 2, dword_586194) )
    {
      ((Actor *)&g_SceneMgr.m_npc[2].m_path.normal[130])->LoadModel();
      strcpy((char *)&g_SceneMgr.m_npc[2].m_path.normal[87].z + 2, dword_586194);
      ((RoleSystem *)&g_SceneMgr.m_npc[2].m_path.normal[73].y)->UpdateTransform();
    }
    x = g_SceneMgr.m_npc[5].m_path.normal[131].x;
  }
  v6 = 0;
  v7 = (char *)&g_SceneMgr.m_npc[0].m_npcinfo.initact[1408 * LODWORD(x) + 4];
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
  __int32 *v4; // edx
  float x; // edi
  int v6; // ebx
  int v7; // esi
  __int32 v8; // ecx
  int v9; // eax
  void *v10; // eax
  GRPinput *v11; // esi
  char *Instance; // eax
  void *v13; // [esp-8h] [ebp-13Ch]
  void *pPos[6]; // [esp+10h] [ebp-124h]
  char Buffer[256]; // [esp+28h] [ebp-10Ch] BYREF
  int v16; // [esp+130h] [ebp-4h]

  v4 = (__int32 *)&g_SceneMgr.m_npc[0].m_npcinfo.reserve[12];
  x = g_SceneMgr.m_npc[5].m_path.normal[131].x;
  v6 = 0;
  v7 = 0;
  do
  {
    LOBYTE(result) = *((_BYTE *)&g_SceneMgr.m_npc[0].m_path.normal[82].z + v7);
    if ( (_BYTE)result )
    {
      LOBYTE(result) = a3;
      if ( !(_BYTE)a3 || v7 == LODWORD(x) )
      {
        v8 = *v4;
        v9 = *v4 - a1;
        if ( v9 < 1 )
          v9 = 1;
        *v4 = v9;
        result = v9 - v8;
        if ( v7 == LODWORD(x) )
          v6 = result;
      }
    }
    v4 += 352;
    ++v7;
  }
  while ( (int)v4 < (int)&g_SceneMgr.m_npc[0].m_path.normal[159] );
  if ( v6 < 0 )
  {
    sprintf(Buffer, "%d", v6);
    v10 = (void *)((operator *)0x24u)->new();
    pPos[5] = v10;
    v16 = 0;
    if ( v10 )
      v11 = (GRPinput *)((int)v10)->SetMousePos();
    else
      v11 = 0;
    v16 = -1;
    v11->SetJoystickPos(Buffer, 0);
    ((PtrArray *)&g_Input.KeyInfo[195])->SetAt(g_Input.KeyInfo[195].HoldTime, (int)v11);
    LOBYTE(result) = a2;
    if ( (_BYTE)a2 )
    {
      pPos[0] = aWe015;
      pPos[1] = aWe016;
      pPos[2] = aWe017;
      pPos[3] = aWe018;
      pPos[4] = aWe019;
      v13 = (void *)pPos[LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x)];
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v13, 1);
    }
  }
  return result;
}

// 0x004101F0
int ScriptSystem::RunWithDelay(float delay, int a2, int a3)
{
  float x; // ebx
  int v4; // edi
  __int32 *v5; // esi
  int v6; // ebp
  __int64 v7; // rax
  int result; // eax
  int v9; // eax
  GRPinput *v10; // esi
  char *Instance; // eax
  void *v12; // [esp-8h] [ebp-144h]
  int v13; // [esp+14h] [ebp-128h]
  void *pPos[5]; // [esp+1Ch] [ebp-120h]
  char Buffer[256]; // [esp+30h] [ebp-10Ch] BYREF
  int v16; // [esp+138h] [ebp-4h]

  x = g_SceneMgr.m_npc[5].m_path.normal[131].x;
  v4 = 0;
  v13 = 0;
  v5 = (__int32 *)&g_SceneMgr.m_npc[0].m_npcinfo.reserve[12];
  do
  {
    if ( *((_BYTE *)&g_SceneMgr.m_npc[0].m_path.normal[82].z + v4) && (!(_BYTE)a3 || v4 == LODWORD(x)) )
    {
      v6 = *v5;
      v7 = (__int64)((double)*v5 - (double)*(v5 - 12) * delay);
      *v5 = v7;
      if ( (int)v7 <= 0 )
        *v5 = 1;
      if ( v4 == LODWORD(x) )
        v13 = *v5 - v6;
    }
    v5 += 352;
    ++v4;
  }
  while ( (int)v5 < (int)&g_SceneMgr.m_npc[0].m_path.normal[159] );
  result = v13;
  if ( v13 < 0 )
  {
    sprintf(Buffer, "%d", v13);
    v9 = ((operator *)0x24u)->new();
    v16 = 0;
    if ( v9 )
      v10 = (GRPinput *)v9->SetMousePos();
    else
      v10 = 0;
    v16 = -1;
    v10->SetJoystickPos(Buffer, 0);
    ((PtrArray *)&g_Input.KeyInfo[195])->SetAt(g_Input.KeyInfo[195].HoldTime, (int)v10);
    LOBYTE(result) = a2;
    if ( (_BYTE)a2 )
    {
      pPos[0] = aWe015;
      pPos[1] = aWe016;
      pPos[2] = aWe017;
      pPos[3] = aWe018;
      pPos[4] = aWe019;
      v12 = (void *)pPos[LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x)];
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
  float x; // ecx
  int *v5; // eax
  int v6; // eax
  char *v7; // eax
  char Buffer[32]; // [esp+8h] [ebp-20h] BYREF

  LOBYTE(result) = a2;
  if ( !(_BYTE)a2 || (unsigned int)eventId > 4 || g_Input.KeyInfo[197].HoldTime != eventId )
  {
    memset(&g_Input.KeyInfo[196], 0, 0x20u);
    x = g_SceneMgr.m_npc[5].m_path.normal[131].x;
    g_Input.KeyInfo[196].Data = a3;
    g_Input.KeyInfo[197].HoldTime = eventId;
    v5 = (int *)(&g_SceneMgr.m_npc[0].m_path.normal[83].z + 2176 * LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x));
    g_Input.KeyInfo[196].CountMode = *v5;
    g_Input.KeyInfo[196].PressTime = v5[1];
    g_Input.KeyInfo[197].Data = v5[2];
    if ( !a3 )
    {
      v6 = 1408 * LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x);
      g_SceneMgr.m_npc[0].m_npcinfo.initact[v6 + 4] = 0;
      g_SceneMgr.m_npc[0].m_npcinfo.initact[v6 + 5] = 0;
      g_SceneMgr.m_npc[0].m_npcinfo.initact[v6 + 6] = 0;
      g_SceneMgr.m_npc[0].m_npcinfo.initact[v6 + 7] = 0;
      g_SceneMgr.m_npc[0].m_npcinfo.initact[v6 + 8] = 0;
    }
    result = 5 * LODWORD(x);
    if ( !BYTE1(g_SceneMgr.m_npc[0].m_npcinfo.mid[352 * LODWORD(x) + 3]) && (unsigned int)eventId <= 4 && !a3 )
    {
      sprintf(Buffer, off_5861F8, eventId);
      v7 = ((PalScript *)(&g_PAL3Data + 312))->SetAppName(Buffer);
      sub_410360(v7);
      result = LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x);
      g_SceneMgr.m_npc[0].m_npcinfo.initact[1408 * LODWORD(g_SceneMgr.m_npc[5].m_path.normal[131].x) + 4 + eventId] = 1;
    }
  }
  return result;
}

// 0x00411F60
int ScriptSystem::UpdateTimers(float dt)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  int v4; // eax
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  int v8; // [esp+8h] [ebp-24h]
  float v9; // [esp+Ch] [ebp-20h]
  int v10; // [esp+10h] [ebp-1Ch]
  int v11; // [esp+14h] [ebp-18h]
  int v12; // [esp+18h] [ebp-14h]
  int v13; // [esp+1Ch] [ebp-10h]
  int v14; // [esp+20h] [ebp-Ch]
  int v15; // [esp+24h] [ebp-8h]
  int v16; // [esp+28h] [ebp-4h]

  v2 = v1;
  result = *(_DWORD *)(v1 + 632);
  if ( result )
  {
    if ( *(_DWORD *)(v1 + 144) || *(_DWORD *)(v1 + 1264) == 4 )
      ((Actor *)(v1 + 680))->QueryState();
    switch ( *(_DWORD *)(v2 + 1264) )
    {
      case 0:
        return sub_412230((float *)v2, 0, 0);
      case 1:
        result = sub_417C50(v2, SLODWORD(dt));
        if ( result )
          goto LABEL_23;
        return result;
      case 2:
        sub_413CD0(v2, SLODWORD(dt));
        if ( !*(_DWORD *)(v2 + 1268) )
          goto LABEL_16;
        goto LABEL_13;
      case 3:
        if ( *(_DWORD *)(v2 + 1268) == 12 )
        {
LABEL_13:
          *(_DWORD *)(v2 + 1296) = *(_DWORD *)(v2 + 1308);
          *(_DWORD *)(v2 + 1300) = *(_DWORD *)(v2 + 1312);
          *(_DWORD *)(v2 + 1304) = *(_DWORD *)(v2 + 1316);
        }
        else
        {
          sub_413CD0(v2, SLODWORD(dt));
          if ( *(_DWORD *)(v2 + 1268) )
          {
            *(_DWORD *)(v2 + 1296) = *(_DWORD *)(v2 + 1308);
            *(_DWORD *)(v2 + 1300) = *(_DWORD *)(v2 + 1312);
            *(_DWORD *)(v2 + 1304) = *(_DWORD *)(v2 + 1316);
          }
        }
LABEL_16:
        v4 = *(_DWORD *)(v2 + 1388);
        if ( v4 && v4 != 4 )
          sub_416BC0(v2);
        goto LABEL_23;
      case 4:
        result = sub_4150C0(v2, SLODWORD(dt));
        if ( result )
          goto LABEL_23;
        return result;
      case 5:
        sub_417420(v2, SLODWORD(dt));
        goto LABEL_23;
      case 6:
        sub_419B30(v2, dt);
        goto LABEL_23;
      case 7:
        sub_41A450(v2, SLODWORD(dt));
        goto LABEL_23;
      default:
LABEL_23:
        *(_DWORD *)(v2 + 1300) = 0;
        if ( !(v6 | v7) )
        {
          if ( *(_DWORD *)(v2 + 636) || *(_DWORD *)(v2 + 1264) == 4 )
          {
            sub_411E00(v2, dt, 1);
          }
          else
          {
            v11 = *(_DWORD *)(v2 + 4);
            v12 = *(_DWORD *)(v2 + 8);
            v14 = *(_DWORD *)(v2 + 148);
            v13 = *(_DWORD *)(v2 + 12);
            v15 = *(_DWORD *)(v2 + 152);
            v16 = *(_DWORD *)(v2 + 156);
            v8 = *(_DWORD *)(v2 + 160);
            v9 = *(float *)(v2 + 164);
            v10 = *(_DWORD *)(v2 + 168);
            sub_411E00(v2, dt, 1);
            if ( fabs(*(float *)(v2 + 164) - v9) > 45.0 )
            {
              *(_DWORD *)(v2 + 12) = v13;
              *(_DWORD *)(v2 + 4) = v11;
              *(_DWORD *)(v2 + 8) = v12;
              *(_DWORD *)(v2 + 156) = v16;
              *(_DWORD *)(v2 + 148) = v14;
              *(_DWORD *)(v2 + 152) = v15;
              *(_DWORD *)(v2 + 168) = v10;
              *(_DWORD *)(v2 + 160) = v8;
              *(float *)(v2 + 164) = v9;
              sub_4142E0((_DWORD *)v2);
            }
          }
        }
        result = (*(int (**)(int))(*(_DWORD *)(v2 + 56) + 4))(v2 + 56);
        if ( !result )
          result = sub_41B300((void ***)v2);
        if ( *(_DWORD *)(v2 + 1264) == 3 )
          LOBYTE(result) = sub_41B6C0(v2, -1);
        break;
    }
  }
  return result;
}

// 0x004194C0
int ScriptSystem::UpdateObjects(float dt)
{
  int v1; // ecx
  gbVec3D *v2; // esi
  float *p_x; // edi
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

  v2 = (gbVec3D *)v1;
  ((Actor *)(v1 + 680))->QueryState();
  if ( LODWORD(g_SceneMgr.m_npc[1].m_path.normal[185].y) <= 2
    && LODWORD(v2[107].x) != LODWORD(g_SceneMgr.m_npc[1].m_path.normal[185].y) )
  {
    v2[107].x = g_SceneMgr.m_npc[1].m_path.normal[185].y;
    ((RoleSystem *)v2)->UpdatePath(SLODWORD(g_SceneMgr.m_npc[1].m_path.normal[185].y));
  }
  p_x = (float *)&v2[112].x;
  sub_419090(&v2[112].x);
  if ( !sub_419200((int)v2, dt, 300.0, v16, v17) )
    goto LABEL_9;
  v14 = v2[112].z - v2[14].x;
  v12 = v2[112].y - v2[13].z;
  v10 = *p_x - v2[13].y;
  v4 = ((gbVec3D *)&v20)->gbVec3D(v10, v12, v14);
  v5 = v2[725].x - v2[14].x;
  v18.x = v4->x;
  v18.y = v4->y;
  v15 = v5;
  v6 = v2[724].z - v2[13].z;
  v18.z = v4->z;
  v13 = v6;
  v11 = v2[724].y - v2[13].y;
  v19 = *((gbVec3D *)&v21)->gbVec3D(v11, v13, v15);
  v7 = ((gbVec3D *)&v18)->Length();
  dta = v7;
  if ( v7 < 0.000049999999 || (v8 = ((gbVec3D *)&v18)->DotProduct(&v19) / dta, v8 >= 0.0) && v8 - dta > -0.1 )
  {
    v2[13].y = *p_x;
    v2[13].z = v2[112].y;
    v2[14].x = v2[112].z;
LABEL_9:
    v2[108] = g_SceneMgr.m_npc[1].m_path.normal[80];
    sub_4122C0((int)v2);
    return result;
  }
  v2[13].y = v2[724].y;
  v2[13].z = v2[724].z;
  v2[14].x = v2[725].x;
  sub_4122C0((int)v2);
  return result;
}

// 0x0041EFA0
int ScriptSystem::Init()
{
  int v0; // edi
  const char *v1; // esi
  int v2; // edi
  const char *v3; // esi
  PalScript String[13]; // [esp+8h] [ebp-218h] BYREF
  int v6; // [esp+21Ch] [ebp-4h]

  sub_431870(String);
  v6 = 0;
  String->LoadFromFile(aDatascriptScen_0);
  String->SetDirectory(aRole);
  while ( String->HasNext() )
  {
    if ( !_strcmpi((const char *)String, off_58B448) )
      break;
    v0 = 0;
    v1 = aTalkrange;
    while ( _strcmpi((const char *)String, v1) )
    {
      v1 += 20;
      ++v0;
      if ( (int)v1 >= (int)&off_58B444 )
        goto LABEL_8;
    }
    String->LoadNext();
    flt_58B378[5 * v0] = atof((const char *)String);
LABEL_8:
    ;
  }
  String->SetDirectory(aMons);
  while ( String->HasNext() )
  {
    if ( !_strcmpi((const char *)String, off_58B448) )
      break;
    v2 = 0;
    v3 = aFreeranges;
    while ( _strcmpi((const char *)String, v3) )
    {
      v3 += 20;
      ++v2;
      if ( (int)v3 >= (int)aTalkrange )
        goto LABEL_16;
    }
    String->LoadNext();
    *(float *)&dword_58B260[5 * v2] = atof((const char *)String);
LABEL_16:
    ;
  }
  v6 = -1;
  return sub_4318A0(String);
}
