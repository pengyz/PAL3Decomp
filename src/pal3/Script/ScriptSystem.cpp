#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ScriptSystem.h"

// Forward declarations for unnamed functions
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
int sub_41EFA0(...);
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
  int v1; // edx
  int v2; // ebx
  char *v3; // edi
  _DWORD *Instance; // eax
  int v5; // edi
  gbRenderEffect *v6; // ecx
  char *v7; // ecx
  int v8; // [esp+Ch] [ebp-10h] BYREF
  float v9; // [esp+10h] [ebp-Ch]
  int v10; // [esp+14h] [ebp-8h]
  int v11; // [esp+18h] [ebp-4h]

  v1 = *(_DWORD *)&g_SceneMgr.m_info[51512];
  v2 = 0;
  v3 = &g_SceneMgr.m_info[7120];
  do
  {
    if ( v2 != v1 )
    {
      RoleSystem::RenderRole((int)v3, (gbMatrixStack *)a1, 0);
      v1 = *(_DWORD *)&g_SceneMgr.m_info[51512];
    }
    v3 += 8704;
    ++v2;
  }
  while ( (int)v3 < (int)&g_SceneMgr.m_info[50640] );
  if ( flt_58DE64 >= 1.2 )
  {
    RoleSystem::RenderRole((int)&g_SceneMgr.m_info[8704 * v1 + 7120], (gbMatrixStack *)a1, 0);
  }
  else if ( rand() % 3 )
  {
    RoleSystem::RenderRole(
      (int)&g_SceneMgr.m_info[8704 * *(_DWORD *)&g_SceneMgr.m_info[51512] + 7120],
      (gbMatrixStack *)a1,
      0);
  }
  else
  {
    Instance = RenderTarget3::GetInstance();
    v5 = Instance[1];
    if ( v5 )
    {
      v6 = (gbRenderEffect *)Instance[1];
      v8 = 1060320051;
      v9 = 0.1;
      v10 = 1036831949;
      v11 = 1056964608;
      v6->SetVariant(PARAM_HANDLE_SPECULAR, &v8);
      RoleSystem::RenderRole(
        (int)&g_SceneMgr.m_info[8704 * *(_DWORD *)&g_SceneMgr.m_info[51512] + 7120],
        (gbMatrixStack *)a1,
        v5);
    }
  }
  RoleSystem::RenderRole((int)dword_BFFDB0, (gbMatrixStack *)a1, 0);
  RoleSystem::RenderRole((int)MEMORY[0xBFDBB0], (gbMatrixStack *)a1, 0);
  if ( *(_DWORD *)&g_SceneMgr.m_info[51500] )
  {
    v7 = &g_SceneMgr.m_info[8704 * *(_DWORD *)&g_SceneMgr.m_info[51512] + 7280];
    v8 = *(_DWORD *)v7;
    v9 = *((float *)v7 + 1);
    v10 = *((_DWORD *)v7 + 2);
    (gbMatrixStack *->Push()a1);
    v9 = v9 + 40.0;
    (gbMatrixStack *->Translate()a1, (struct gbVec3D *)&v8);
    (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)&g_SceneMgr.m_info[51500] + 16))(
      *(_DWORD *)&g_SceneMgr.m_info[51500],
      0);
    (gbMatrixStack *->Pop()a1);
  }
}

// 0x0040C790
int ScriptSystem::Cleanup()
{
  int i; // esi
  void (__thiscall ***v1)(_DWORD, int); // ecx
  int result; // eax

  for ( i = 0; i < MEMORY[0xBFDB84]; ++i )
  {
    v1 = *(void (__thiscall ****)(_DWORD, int))(MEMORY[0xBFDB80] + 4 * i);
    if ( v1 )
      (**v1)(v1, 1);
  }
  sub_4326A0((int)&MEMORY[0xBFDB80], 0, -1);
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
  float pOut[3]; // [esp+38h] [ebp-8Ch] BYREF
  char Buffer[128]; // [esp+44h] [ebp-80h] BYREF

  sub_445500((int *)MEMORY[0xBFDAB0]._data);
  for ( i = 0; i < MEMORY[0xBFDB84]; ++i )
    GRPinput::SetMouseSensitivity(*(_DWORD *)(MEMORY[0xBFDB80] + 4 * i));
  sub_43A270(&g_SceneMgr.?[5].?.length[25]);
  result = (char)g_SceneMgr.?[225];
  if ( g_SceneMgr.?[225] )
  {
    v2 = 32.0 / (double)MEMORY[0xBFD6D4];
    v3 = *(_DWORD *)(*(_DWORD *)&g_pGfxManager[208] + 12);
    *(float *)(v3 + 48) = 32.0 / (double)MEMORY[0xBFD6D0];
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
          memset(pOut, 0, sizeof(pOut));
          (RoleSystem *->GetDirection()(v6 - 158), pOut);
          (gbCamera *->PointWorldToScr()&g_pCamera->OrthoSize, (struct gbVec3D *)pOut, &v8, (float *)&v9);
          sprintf(Buffer, "%d", *((unsigned __int8 *)v6 - 332));
          v7 = v8 - 0.050000001;
          (*(void (__thiscall **)(int, char *, _DWORD, int, int, int))(*(_DWORD *)v3 + 16))(
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
    return (*(int (__thiscall **)(int))(*(_DWORD *)v3 + 8))(v3);
  }
  return result;
}

// 0x0040C960
int ScriptSystem::Destroy()
{
  char *v0; // esi
  int result; // eax

  (UIWnd *->Reset()&MEMORY[0xBFDAB0]);
  (PalScript *->Reset()&g_SceneMgr.m_info[50648]);
  ScriptSystem::Cleanup();
  v0 = &g_SceneMgr.m_info[7120];
  do
  {
    result = v0->Destroy();
    v0 += 8704;
  }
  while ( (int)v0 < (int)&g_SceneMgr.m_info[50640] );
  return result;
}

// 0x0040E5F0
int ScriptSystem::Execute(int a1, char a2)
{
  _DWORD *v2; // ecx
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  char *v7; // ecx

  v2 = *(_DWORD **)&g_SceneMgr.m_info[54108];
  flt_58DE64 = 10.0;
  if ( a2 )
  {
    v3 = 8704 * a1;
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7140] = *(_DWORD *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 20);
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7144] = v2[6];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7148] = v2[7];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7152] = v2[8];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7156] = v2[9];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7160] = v2[10];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7124] = v2[1];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7128] = v2[2];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7132] = v2[3];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7280] = v2[40];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7284] = v2[41];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7288] = v2[42];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 15812] = v2[2173];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 15816] = v2[2174];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 15820] = v2[2175];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7268] = v2[37];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7272] = v2[38];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7276] = v2[39];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 15808] = v2[2172];
    *(_DWORD *)&g_SceneMgr.m_info[v3 + 7748] = v2[157];
  }
  *(_DWORD *)&g_SceneMgr.m_info[8704 * *(_DWORD *)&g_SceneMgr.m_info[51512] + 7752] = 0;
  *(_DWORD *)&g_SceneMgr.m_info[8704 * a1 + 7752] = 1;
  RoleSystemNotify((int)&g_SceneMgr.m_info[8704 * a1 + 7120]);
  CameraSystem::Init((int)&g_SceneMgr.m_info[8704 * a1 + 7120]);
  *(_DWORD *)&g_SceneMgr.m_info[51512] = a1;
  if ( *((_DWORD *)g_pCamera + 112) )
    (RoleSystem *->SetActive()g_pCamera, (int)&g_SceneMgr.m_info[8704 * a1 + 7120]);
  if ( a1 == 1 && dword_C025EC == 10 )
  {
    sub_419090((float *)&dword_C02198);
    dword_C042E8 = *(_DWORD *)&g_SceneMgr.m_info[24512];
  }
  v4 = CGameData::SetMode(&g_GameData, 0);
  if ( v4 )
    sub_4524B0((gbRefObject **)(v4 + 1084), *(int *)&g_SceneMgr.m_info[51512]);
  v5 = *(_DWORD *)&g_SceneMgr.m_info[51512];
  if ( *(_DWORD *)&g_SceneMgr.m_info[51512] == 2 )
  {
    if ( _strcmpi(&g_SceneMgr.m_info[24702], dword_586194) )
    {
      Actor::LoadModel((int)&g_SceneMgr.m_info[25208], dword_586194, 0);
      strcpy(&g_SceneMgr.m_info[24702], dword_586194);
      RoleSystem::UpdateTransform((int)&g_SceneMgr.m_info[24528]);
    }
    v5 = *(_DWORD *)&g_SceneMgr.m_info[51512];
  }
  v6 = 0;
  v7 = &g_SceneMgr.m_info[1408 * v5 + 700];
  while ( !v7[v6] )
  {
    if ( ++v6 > 4 )
      return ScriptSystem::RunEvent(31, 0, 0);
  }
  return v6->RunEvent(1, 1);
}

// 0x004100A0
int ScriptSystem::RunScript(int a1, int a2, int a3)
{
  int result; // eax
  char *v4; // edx
  int v5; // edi
  int v6; // ebx
  int v7; // esi
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  _BYTE *v11; // esi
  int *Instance; // eax
  const void *v13; // [esp-8h] [ebp-13Ch]
  _DWORD v14[6]; // [esp+10h] [ebp-124h]
  char Buffer[256]; // [esp+28h] [ebp-10Ch] BYREF
  int v16; // [esp+130h] [ebp-4h]

  v4 = &g_SceneMgr.m_info[988];
  v5 = *(_DWORD *)&g_SceneMgr.m_info[51512];
  v6 = 0;
  v7 = 0;
  do
  {
    LOBYTE(result) = g_SceneMgr.m_info[v7 + 7112];
    if ( (_BYTE)result )
    {
      LOBYTE(result) = a3;
      if ( !(_BYTE)a3 || v7 == v5 )
      {
        v8 = *(_DWORD *)v4;
        v9 = *(_DWORD *)v4 - a1;
        if ( v9 < 1 )
          v9 = 1;
        *(_DWORD *)v4 = v9;
        result = v9 - v8;
        if ( v7 == v5 )
          v6 = result;
      }
    }
    v4 += 1408;
    ++v7;
  }
  while ( (int)v4 < (int)&g_SceneMgr.m_info[8028] );
  if ( v6 < 0 )
  {
    sprintf(Buffer, "%d", v6);
    v10 = operator new(0x24u);
    v14[5] = v10;
    v16 = 0;
    if ( v10 )
      v11 = (_BYTE *)v10->SetMousePos();
    else
      v11 = 0;
    v16 = -1;
    v11->SetJoystickPos(Buffer, 0);
    PtrArray::SetAt(&MEMORY[0xBFDB80], MEMORY[0xBFDB84], (int)v11);
    LOBYTE(result) = a2;
    if ( (_BYTE)a2 )
    {
      v14[0] = aWe015;
      v14[1] = aWe016;
      v14[2] = aWe017;
      v14[3] = aWe018;
      v14[4] = aWe019;
      v13 = (const void *)v14[*(_DWORD *)&g_SceneMgr.m_info[51512]];
      Instance = (int *)CScreenMode::GetInstance();
      Instance->AudioSetPosition(v13, 1);
    }
  }
  return result;
}

// 0x004101F0
int ScriptSystem::RunWithDelay(float delay, int a2, int a3)
{
  int v3; // ebx
  int v4; // edi
  char *v5; // esi
  int v6; // ebp
  __int64 v7; // rax
  int result; // eax
  int v9; // eax
  _BYTE *v10; // esi
  int *Instance; // eax
  const void *v12; // [esp-8h] [ebp-144h]
  int v13; // [esp+14h] [ebp-128h]
  _DWORD v14[5]; // [esp+1Ch] [ebp-120h]
  char Buffer[256]; // [esp+30h] [ebp-10Ch] BYREF
  int v16; // [esp+138h] [ebp-4h]

  v3 = *(_DWORD *)&g_SceneMgr.m_info[51512];
  v4 = 0;
  v13 = 0;
  v5 = &g_SceneMgr.m_info[988];
  do
  {
    if ( g_SceneMgr.m_info[v4 + 7112] && (!(_BYTE)a3 || v4 == v3) )
    {
      v6 = *(_DWORD *)v5;
      v7 = (__int64)((double)*(int *)v5 - (double)*((int *)v5 - 12) * delay);
      *(_DWORD *)v5 = v7;
      if ( (int)v7 <= 0 )
        *(_DWORD *)v5 = 1;
      if ( v4 == v3 )
        v13 = *(_DWORD *)v5 - v6;
    }
    v5 += 1408;
    ++v4;
  }
  while ( (int)v5 < (int)&g_SceneMgr.m_info[8028] );
  result = v13;
  if ( v13 < 0 )
  {
    sprintf(Buffer, "%d", v13);
    v9 = operator new(0x24u);
    v16 = 0;
    if ( v9 )
      v10 = (_BYTE *)v9->SetMousePos();
    else
      v10 = 0;
    v16 = -1;
    v10->SetJoystickPos(Buffer, 0);
    PtrArray::SetAt(&MEMORY[0xBFDB80], MEMORY[0xBFDB84], (int)v10);
    LOBYTE(result) = a2;
    if ( (_BYTE)a2 )
    {
      v14[0] = aWe015;
      v14[1] = aWe016;
      v14[2] = aWe017;
      v14[3] = aWe018;
      v14[4] = aWe019;
      v12 = (const void *)v14[*(_DWORD *)&g_SceneMgr.m_info[51512]];
      Instance = (int *)CScreenMode::GetInstance();
      Instance->AudioSetPosition(v12, 1);
    }
  }
  return result;
}

// 0x00410470
int ScriptSystem::RunEvent(int eventId, int a2, int a3)
{
  int result; // eax
  int v4; // ecx
  int *v5; // eax
  int v6; // eax
  char *v7; // eax
  char Buffer[32]; // [esp+8h] [ebp-20h] BYREF

  LOBYTE(result) = a2;
  if ( !(_BYTE)a2 || (unsigned int)eventId > 4 || MEMORY[0xBFDBA4] != eventId )
  {
    memset(&MEMORY[0xBFDB90], 0, 0x20u);
    v4 = *(_DWORD *)&g_SceneMgr.m_info[51512];
    MEMORY[0xBFDB90] = a3;
    MEMORY[0xBFDBA4] = eventId;
    v5 = (int *)&g_SceneMgr.m_info[8704 * *(_DWORD *)&g_SceneMgr.m_info[51512] + 7124];
    MEMORY[0xBFDB98] = *v5;
    MEMORY[0xBFDB9C] = v5[1];
    MEMORY[0xBFDBA0] = v5[2];
    if ( !a3 )
    {
      v6 = 1408 * *(_DWORD *)&g_SceneMgr.m_info[51512];
      g_SceneMgr.m_info[v6 + 700] = 0;
      g_SceneMgr.m_info[v6 + 701] = 0;
      g_SceneMgr.m_info[v6 + 702] = 0;
      g_SceneMgr.m_info[v6 + 703] = 0;
      g_SceneMgr.m_info[v6 + 704] = 0;
    }
    result = 5 * v4;
    if ( !g_SceneMgr.m_info[1408 * v4 + 725] && (unsigned int)eventId <= 4 && !a3 )
    {
      sprintf(Buffer, off_5861F8, eventId);
      v7 = PalScript::SetAppName(&MEMORY[0x8ACD30], Buffer);
      sub_410360(v7);
      result = *(_DWORD *)&g_SceneMgr.m_info[51512];
      g_SceneMgr.m_info[1408 * *(_DWORD *)&g_SceneMgr.m_info[51512] + 700 + eventId] = 1;
    }
  }
  return result;
}

// 0x00411F60
int ScriptSystem::UpdateTimers(float dt)
{
  _DWORD *v1; // ecx
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

  v2 = (int)v1;
  result = v1[158];
  if ( result )
  {
    if ( v1[36] || v1[316] == 4 )
      Actor::QueryState(v1 + 170);
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
        result = (*(int (__thiscall **)(int))(*(_DWORD *)(v2 + 56) + 4))(v2 + 56);
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
  int v2; // esi
  float *v3; // edi
  gbVec3D *v4; // eax
  double v5; // st7
  double v6; // st7
  gbVec3D *v7; // eax
  double v8; // st7
  double v9; // st7
  int result; // eax
  float v11; // [esp+Ch] [ebp-44h]
  float v12; // [esp+Ch] [ebp-44h]
  float v13; // [esp+10h] [ebp-40h]
  float v14; // [esp+10h] [ebp-40h]
  float v15; // [esp+14h] [ebp-3Ch]
  float v16; // [esp+14h] [ebp-3Ch]
  float v17; // [esp+18h] [ebp-38h]
  float v18; // [esp+1Ch] [ebp-34h]
  _DWORD v19[3]; // [esp+20h] [ebp-30h] BYREF
  _DWORD v20[3]; // [esp+2Ch] [ebp-24h] BYREF
  float v21[3]; // [esp+38h] [ebp-18h] BYREF
  _BYTE v22[12]; // [esp+44h] [ebp-Ch] BYREF
  float dta; // [esp+54h] [ebp+4h]

  v2 = v1;
  (void *->QueryState()(v1 + 680));
  if ( *(_DWORD *)&g_SceneMgr.m_info[17108] <= 2u && *(_DWORD *)(v2 + 1284) != *(_DWORD *)&g_SceneMgr.m_info[17108] )
  {
    *(_DWORD *)(v2 + 1284) = *(_DWORD *)&g_SceneMgr.m_info[17108];
    (RoleSystem *->UpdatePath()v2, *(int *)&g_SceneMgr.m_info[17108]);
  }
  v3 = (float *)(v2 + 1344);
  sub_419090((float *)(v2 + 1344));
  if ( !sub_419200(v2, dt, 300.0, v17, v18) )
    goto LABEL_9;
  v15 = *(float *)(v2 + 1352) - *(float *)(v2 + 168);
  v13 = *(float *)(v2 + 1348) - *(float *)(v2 + 164);
  v11 = *v3 - *(float *)(v2 + 160);
  v4 = (gbVec3D *->gbVec3D()v21, v11, v13, v15);
  v5 = *(float *)(v2 + 8700) - *(float *)(v2 + 168);
  v19[0] = *(_DWORD *)v4;
  v19[1] = *((_DWORD *)v4 + 1);
  v16 = v5;
  v6 = *(float *)(v2 + 8696) - *(float *)(v2 + 164);
  v19[2] = *((_DWORD *)v4 + 2);
  v14 = v6;
  v12 = *(float *)(v2 + 8692) - *(float *)(v2 + 160);
  v7 = (gbVec3D *->gbVec3D()v22, v12, v14, v16);
  v20[0] = *(_DWORD *)v7;
  v20[1] = *((_DWORD *)v7 + 1);
  v20[2] = *((_DWORD *)v7 + 2);
  v8 = (gbVec3D *->Length()v19);
  dta = v8;
  if ( v8 < 0.000049999999
    || (v9 = (gbVec3D *->DotProduct()v19, (const struct gbVec3D *)v20) / dta, v9 >= 0.0) && v9 - dta > -0.1 )
  {
    *(float *)(v2 + 160) = *v3;
    *(_DWORD *)(v2 + 164) = *(_DWORD *)(v2 + 1348);
    *(_DWORD *)(v2 + 168) = *(_DWORD *)(v2 + 1352);
LABEL_9:
    *(_DWORD *)(v2 + 1296) = *(_DWORD *)&g_SceneMgr.m_info[15844];
    *(_DWORD *)(v2 + 1300) = *(_DWORD *)&g_SceneMgr.m_info[15848];
    *(_DWORD *)(v2 + 1304) = *(_DWORD *)&g_SceneMgr.m_info[15852];
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
int sub_41EFA0()
{
  int v0; // edi
  const char *v1; // esi
  int v2; // edi
  const char *v3; // esi
  char String[524]; // [esp+8h] [ebp-218h] BYREF
  int v6; // [esp+21Ch] [ebp-4h]

  sub_431870(String);
  v6 = 0;
  aDatascriptScen_0->LoadFromFile();
  String->SetDirectory(aRole);
  while ( String->HasNext() )
  {
    if ( !_strcmpi(String, off_58B448) )
      break;
    v0 = 0;
    v1 = aTalkrange;
    while ( _strcmpi(String, v1) )
    {
      v1 += 20;
      ++v0;
      if ( (int)v1 >= (int)&off_58B444 )
        goto LABEL_8;
    }
    String->LoadNext();
    flt_58B378[5 * v0] = atof(String);
LABEL_8:
    ;
  }
  String->SetDirectory(aMons);
  while ( String->HasNext() )
  {
    if ( !_strcmpi(String, off_58B448) )
      break;
    v2 = 0;
    v3 = aFreeranges;
    while ( _strcmpi(String, v3) )
    {
      v3 += 20;
      ++v2;
      if ( (int)v3 >= (int)aTalkrange )
        goto LABEL_16;
    }
    String->LoadNext();
    *(float *)&dword_58B260[5 * v2] = atof(String);
LABEL_16:
    ;
  }
  v6 = -1;
  return sub_4318A0(String);
}
