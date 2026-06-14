#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBSystem.h"

// Forward declarations for unnamed functions
char SceneMgrUpdate(float *_this, float fVal); // from annotations
int sub_4431B0(...);
void * sub_445FE0(void *a2); // from annotations
int sub_4C5980(...);
int sub_4DB940(_BYTE *_this, char a2); // from annotations
int sub_515C90(...);
int sub_5163D0(...);
int sub_51D5C0(...);
int todo_408BD0(...);

// Unnamed globals (extern)
extern char byte_17A89E8[256];
extern CHAR byte_17AC6DC[256];
extern int dword_C10CD4;
void __cdecl nullsub_68(void);
extern RoleSystem stru_C059A0;
extern CHAR unk_5DE9E4;
extern unsigned int unk_5DFDEC;

// 0x00462280
void CCBSystem::ProcessSlotResults(int nVal)
{
  int v2; // edi
  int v3; // esi
  char **v4; // ebx
  CCBResultWindow *v5; // ecx

  v2 = *(_DWORD *)&this->m_Thread[178].cmd.bSrcRole[4 * nVal + 6];
  v3 = 0;
  v4 = &this->m_Thread[953].fp[1];
  do
  {
    switch ( *(_BYTE *)(v2 + 612) )
    {
      case 7:
        if ( *(_BYTE *)(v3 + v2 + 614) )
        {
          v5 = (CCBResultWindow *)(v4 - 135);
          goto LABEL_13;
        }
        break;
      case 8:
        if ( *(_BYTE *)(v3 + v2 + 614) )
        {
          v5 = (CCBResultWindow *)v4;
          goto LABEL_13;
        }
        break;
      case 9:
        if ( *(_BYTE *)(v3 + v2 + 614) )
        {
          v5 = (CCBResultWindow *)(v4 + 45);
          goto LABEL_13;
        }
        break;
      case 0xA:
        if ( *(_BYTE *)(v3 + v2 + 614) )
        {
          ((CCBResultWindow *)(CCBResultWindow *)v4 - 1)->StartAnim();
          v5 = (CCBResultWindow *)(v4 + 90);
          goto LABEL_13;
        }
        break;
      case 0xB:
        if ( *(_BYTE *)(v3 + v2 + 614) )
        {
          v5 = (CCBResultWindow *)(v4 - 90);
LABEL_13:
          ((CCBResultWindow *)v5)->StartAnim();
        }
        break;
      default:
        break;
    }
    ++v3;
    v4 += 270;
  }
  while ( v3 < 5 );
}

// 0x00462340
void CCBSystem::InitResultWindow()
{
  CCBResultWindow *v1; // esi
  int v2; // edi

  v1 = (CCBResultWindow *)&this->m_Thread[953].fp[1];
  v2 = 5;
  do
  {
    ((CCBResultWindow *)v1 - 3)->SetDirty();
    ((CCBResultWindow *)v1)->SetDirty();
    ((CCBResultWindow *)v1 + 1)->SetDirty();
    ((CCBResultWindow *)v1 - 1)->SetDirty();
    ((CCBResultWindow *)v1 + 2)->SetDirty();
    ((CCBResultWindow *)v1 - 2)->SetDirty();
    v1 += 6;
    --v2;
  }
  while ( v2 );
}

// 0x004C6170
_BYTE * CCBSystem::GetThreadBase()
{
  _BYTE *result; // eax
  int v2; // edx

  result = &this->m_pEffectSimple;
  v2 = 2048;
  do
  {
    *result = 0;
    result += 48;
    --v2;
  }
  while ( v2 );
  this->m_pAI = 0;
  *((_DWORD *)this + 24583) = 0;
  return result;
}

// 0x004DB3A0
// attributes: thunk
int CCBSystem::InitCmdTable1_thunk()
{
  return this->InitCmdTable1();
}

// 0x004DB3B0
int CCBSystem::InitCmdTable1()
{
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[23] = 545;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[27] = 545;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[31] = 545;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[35] = 545;
  return 545;
}

// 0x004DB3F0
// attributes: thunk
int CCBSystem::InitCmdTable2_thunk()
{
  return this->InitCmdTable2();
}

// 0x004DB400
int CCBSystem::InitCmdTable2()
{
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[39] = 121;
  *(_DWORD *)&g_RoleSystemCombat.m_partyActor.m_curact[43] = 316;
  LODWORD(g_RoleSystemCombat.m_partyActor.m_fDirX) = 512;
  LODWORD(g_RoleSystemCombat.m_partyActor.m_fDirY) = 709;
  return 709;
}

// 0x004DB440
// attributes: thunk
int CCBSystem::InitCmdTable3_thunk()
{
  return this->InitCmdTable3();
}

// 0x004DB450
int CCBSystem::InitCmdTable3()
{
  LODWORD(g_RoleSystemCombat.m_partyActor.m_fDirZ) = 573;
  LODWORD(g_RoleSystemCombat.m_partyActor.m_fNormX) = 573;
  LODWORD(g_RoleSystemCombat.m_partyActor.m_fNormY) = 573;
  LODWORD(g_RoleSystemCombat.m_partyActor.m_fNormZ) = 573;
  return 573;
}

// 0x004DB490
CCBSystem * CCBSystem::InitCmd(int nVal)
{
  memset(this, 0, 0x1C8u);
  this->m_pUtil = (CCBSystem *)nVal;
  this->m_pUI = *(CCBUI **)(nVal + 4);
  this->m_pControl = *(CCBControl **)(nVal + 16);
  return this;
}

// 0x004DB4C0
int CCBSystem::ResetFlags()
{
  this->m_Thread[3].bValid = 1;
  this->m_Thread[3].bExecuted = 1;
  *(&this->m_Thread[3].bExecuted + 1) = 1;
  memset(&this->m_pAttackSequen, 0, 0x1B8u);
  return 0;
}

// 0x004DB4F0
char CCBSystem::DestroySubsystems()
{
  UIStatic *m_pAttackSequenBack; // ecx
  int i; // esi
  void (***v5)(_DWORD, _DWORD); // ecx
  UIStatic *v6; // ecx
  int v7; // ebx
  int j; // esi
  CCBSystem *m_pUtil; // eax

  if ( !this->m_pUtil )
    return 0;
  if ( !this->m_pUI )
    return 0;
  if ( !this->m_pControl )
    return 0;
  ((CCBAttackSequen *)this)->CalcTurnOrder();

  if ( g_RoleSystemCombat.dwInitParam == (HWND)1 )
  {
    m_pAttackSequenBack = this->m_pUtil->m_pUI->m_pAttackSequenBack;
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pAttackSequenBack->__vftable->ShowWindow)(m_pAttackSequenBack, 0);
    for ( i = 76; i < 120; i += 4 )
    {
// [VFTABLE] v5 = *(void ( ****)(_DWORD, _DWORD))((char *)&this->m_pUtil->m_pUI->__vftable + i);
      (**v5)(v5, 0);
    }
    return 1;
  }
  else
  {
    v6 = this->m_pUtil->m_pUI->m_pAttackSequenBack;
// [VFTABLE] ((void ( *)(UIStatic *, int))v6->__vftable->ShowWindow)(v6, 1);
    v7 = 0;
    for ( j = 76; j < 120; j += 4 )
    {
      m_pUtil = this->m_pUtil;
      if ( this->m_pUtil->m_pRoleState->m_Role[0].bMagicMastered[5][v7 + 4] )
// [VFTABLE] (***(void ( ****)(_DWORD, int))((char *)&m_pUtil->m_pUI->__vftable + j))(
// [VFTABLE]   *(vtbl_0056AE2C **)((char *)&m_pUtil->m_pUI->__vftable + j),
// [VFTABLE]   1);
      else
// [VFTABLE] (***(void ( ****)(_DWORD, _DWORD))((char *)&m_pUtil->m_pUI->__vftable + j))(
// [VFTABLE]   *(vtbl_0056AE2C **)((char *)&m_pUtil->m_pUI->__vftable + j),
// [VFTABLE]   0);
      v7 += 892;
    }
    return 1;
  }
}

// 0x004DB640
int CCBSystem::CalcSpeed(int roleIdx, int nVal)
{
  return 5 * (((CCBRoleState *)this->m_pControl)->GetSpeedBonus(roleIdx) + 4);
}

// 0x004DB660
int CCBSystem::GetCmdSlot(int idx)
{
  char *v3; // ebx
  int result; // eax

  v3 = (char *)this + 40 * idx;
  v3[44] = this->CalcSpeed(idx, 0);
  result = this->CalcSpeed(idx, 1);
  v3[45] = result;
  return result;
}

// 0x004DB690
char CCBSystem::GetCmdType(int idx)
{
  return *((_BYTE *)&this->m_pATSEffMgr + 40 * idx);
}

// 0x004DB6A0
bool CCBSystem::IsBusy()
{
  int v2; // [esp+0x4] [ebp+0x4]

  return *((_DWORD *)&this->m_pES + 10 * v2) >= 11500;
}

// 0x004DB6C0
bool CCBSystem::IsCmdReady(int idx)
{
  return (int)(&this->m_pEffectSimple)[10 * idx] >= 11500;
}

// 0x004DB6E0
bool CCBSystem::IsCmdEmpty(int idx)
{
  return *((_BYTE *)&this->m_pEffMgr + 40 * idx + 2) == 0;
}

// 0x004DB700
int CCBSystem::GetCmdValue(int idx)
{
  return *((_DWORD *)&this->m_pConfig + 10 * idx);
}

// 0x004DB710
char * CCBSystem::GetCmdPtr(int idx)
{
  char *result; // eax

  result = (char *)this + 40 * idx;
  *((_DWORD *)result + 8) = 0;
  *((_DWORD *)result + 9) = 0;
  result[46] = 0;
  return result;
}

// 0x004DB730
char * CCBSystem::ClearCmdSlot(int nVal)
{
  char *result; // eax

  result = (char *)this + 40 * nVal;
  *((_DWORD *)result + 8) = 0;
  result[46] = 1;
  return result;
}

// 0x004DB750
char * CCBSystem::GetCmdData(int idx)
{
  char *result; // eax
  int v3; // [esp+0x8] [ebp+0x8]
  int v4; // [esp+0xC] [ebp+0xC]
  char v5; // [esp+0x10] [ebp+0x10]

  result = (char *)this + 40 * idx;
  *((_DWORD *)result + 8) = v3;
  *((_DWORD *)result + 9) = v4;
  result[46] = v5;
  return result;
}

// 0x004DB780
int CCBSystem::GetCmdCount(int idx)
{
  char v3; // [esp+0x8] [ebp+0x8]

  *((_BYTE *)&this->m_pEffMgr + 40 * idx + 1) = v3;
  return 5 * idx;
}

// 0x004DB7A0
int CCBSystem::ProcessAllCmds()
{
  int v2; // edi
  int v3; // esi
  CEffectSimple **p_m_pEffectSimple; // ebx
  CCBControl *m_pControl; // ecx
  CCBControl *v6; // ecx
  double v7; // st7
  float v9; // [esp+0x10] [ebp-0xC]
  int v10; // [esp+0x14] [ebp-0x8]

  v2 = 0;
  v9 = 100000000.0;
  v10 = -1;
  v3 = 0;
  p_m_pEffectSimple = &this->m_pEffectSimple;
  do
  {
    m_pControl = this->m_pControl;
    if ( BYTE1(m_pControl[1].m_Thread[1].fpCaller[v3 + 4]) )
    {
      if ( !((CCBRoleState *)m_pControl)->IsActive(v2) )
      {
        v6 = this->m_pControl;
        if ( !LOBYTE(v6[3].m_Thread[3].fpCaller[v3 + 2])
          && !HIBYTE(((CCBRoleState *)v6)->InitUI(v2)[1].dwMagicID[2][4])
          && ((CCBRoleState *)this->m_pControl)->SetRoleField(v2, 0) > 0 )
        {
          if ( *((_BYTE *)p_m_pEffectSimple + 10) )
            v7 = (double)(11500 - (int)*p_m_pEffectSimple)
               / ((double)*((unsigned __int8 *)p_m_pEffectSimple + 9)
                * 50.0);
          else
            v7 = (double)(11500 - (int)*(p_m_pEffectSimple - 1))
               / ((double)*((unsigned __int8 *)p_m_pEffectSimple + 8)
                * 50.0)
               + 10000.0;
          if ( v7 < v9 )
          {
            v9 = v7;
            v10 = v2;
          }
        }
      }
    }
    v3 += 223;
    ++v2;
    p_m_pEffectSimple += 10;
  }
  while ( v3 < 2453 );
  return v10;
}

// 0x004DB8B0
char * CCBSystem::GetCmdString(int idx)
{
  char *result; // eax

  result = (char *)this + 40 * idx;
  if ( result[46] )
  {
    *((_DWORD *)result + 9) = 0;
    *((_DWORD *)result + 8) = 5750;
    result[46] = 0;
  }
  return result;
}

// 0x004DB8E0
int CCBSystem::SetThreadFlag(char pData)
{
  int result; // eax

  if ( pData != this->m_Thread[3].bValid )
  {
    this->m_Thread[3].bValid = pData;
    ((CCBAttackSequen *)this)->SetPause();
    return sub_4DB940(this, pData);
  }
  return result;
}

// 0x004DB920
int CCBSystem::SetCmdParam(int idx, int value)
{
  *((_BYTE *)&this->m_pEffMgr + 40 * idx + 3) = value;
  return 5 * idx;
}

// 0x004DB9C0
int CCBSystem::InvokeThreadMethod(int nVal, char pData)
{
  int ( **v3)(int); // edx

  v3 = (int ( **)(int))**((_DWORD **)&this->m_pUI->pPanel + nVal);
  if ( pData )
    return (*v3)(1);
  else
    return (*v3)(0);
}

// 0x004DB9F0
void CCBSystem::InitRoleStateUI()
{
  int v1; // edi
  int v3; // ebp
  int i; // esi
  CCBRoleState *m_pRoleState; // ecx
  tagRoleState *inited; // eax

  v1 = 0;
  v3 = 0;
  for ( i = 76; i < 120; i += 4 )
  {
    m_pRoleState = this->m_pUtil->m_pRoleState;
    if ( m_pRoleState->m_Role[0].bMagicMastered[5][v3 + 4] )
    {
      inited = ((CCBRoleState *)m_pRoleState)->InitUI(v1);
      sprintf(
        (char *const)&g_RoleSystemCombat,
        (const char *const)&pTarget.m_nTargetType + 940,
        &pTarget.m_nTargetType + 134,
        inited->sModel);
// [VFTABLE] ((UIStatic *)*(UIStatic **)((char *)&this->m_pUI->__vftable + i))->CreateFromTemplate();
    }
    ++v1;
    v3 += 892;
  }
}

// 0x004DBE60
void CCBSystem::InitCombatSlot(int roleIdx)
{
  char *v3; // edi
  tagRoleState *inited; // eax

  if ( BYTE1(this->m_pControl[1].m_Thread[1].fpCaller[223 * roleIdx + 4]) )
  {
    v3 = (char *)this + 40 * roleIdx;
    v3[48] = 1;
    v3[46] = 0;
    v3[44] = this->CalcSpeed(roleIdx, 0);
    v3[45] = this->CalcSpeed(roleIdx, 1);
    *((_DWORD *)v3 + 8) = 0;
    *((_DWORD *)v3 + 9) = 0;
    *((_DWORD *)&this->m_pConfig + 10 * roleIdx) = 0;
    inited = ((CCBRoleState *)this->m_pControl)->InitUI(roleIdx);
    sprintf(byte_17A89E8, (const char *const)&pTarget.m_nTargetType + 940, &pTarget.m_nTargetType + 134, inited->sModel);
    ((UIStatic *)*(&this->m_pUI->pPanel + roleIdx))->CreateFromTemplate();
  }
}

// 0x004DC160
CCBSystem * CCBSystem::CopyCmdData(int *p_DWORD)
{
  memset(&this->m_p3DSpark, 0, 0x2Cu);
  memset(this, 0, 0x570u);

  this->m_pUtil = (CCBSystem *)p_DWORD;
  this->m_pUI = (CCBUI *)p_DWORD[3];
  this->m_pControl = (CCBControl *)p_DWORD[5];
  this->m_pAttackSequen = (CCBAttackSequen *)p_DWORD[4];
  this->m_pRoleState = (CCBRoleState *)p_DWORD[1];
  return this;
}

// 0x004DC1B0
// attributes: thunk
int CCBSystem::GetState()
{
  return this->ClearAllPointers();
}

// 0x004DC1C0
int CCBSystem::ClearAllPointers()
{
  BYTE4(this->m_dAbsTimeFund) = 0;
  this->m_pConfig = 0;
  this->m_pEffMgr = 0;
  this->m_pATSEffMgr = 0;
  this->m_p2DSpark = 0;
  LOBYTE(this->m_pEffectSimple) = 0;
  this->m_fAbsTimeFund = NAN;
  this->m_fTimeScale = 0.0;
  memset(&this->m_pFightInfo, 0, 0x500u);
  memset(&this->m_p3DSpark, 0, 0x2Cu);
  this->m_pES = (CEffectSystem *)-1;
  BYTE1(this->m_pEffectSimple) = 0;
  this->m_pConfig = 0;
  this->m_pEffMgr = 0;
  this->m_pATSEffMgr = 0;
  this->m_p2DSpark = 0;
  return 0;
}

// 0x004DC3F0
char CCBSystem::StartRoleThread(int arg0)
{
  _DWORD *v6; // eax
  _BYTE a2[16]; // [esp+0x10] [ebp-0x10] BYREF

  if ( LOBYTE(this->m_p2DSpark) == 1 )
    return 0;
  this->m_pConfig = 0;
  this->m_pEffMgr = 0;
  this->m_pATSEffMgr = 0;
  this->m_p2DSpark = 0;
  memset(&this->m_p3DSpark, 0, 0x2Cu);
  LOBYTE(this->m_pEffectSimple) = 1;
  this->m_pES = (CEffectSystem *)arg0;
  this->FindFreeThread(0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, 0, 0, 0, -1, 0);
  ((CCBAttackSequen *)this->m_pUI)->SetPause();
  ((CCBSystem *)this->m_pUI)->SetCmdParam((int)this->m_pES, 1);
  _EAX = *((_DWORD *)&this->m_pControl->m_DeltaTime + (int)this->m_pES);
  __asm
  {
    fld     dword ptr [eax+0x19EC]
    fstp    dword ptr [eax+0x19E8]
  }
  *(float *)(_EAX + 6632) = _ET1;
  *(_BYTE *)(*((_DWORD *)&this->m_pControl->m_DeltaTime + (int)this->m_pES) + 280) = 1;
  if ( BYTE2(this->m_pUtil->m_nTimesOfCombat) )
  {
    v6 = sub_445FE0(a2);
    ((GRPinput *)&g_Input)->SetCursorPos((v6[2] + *v6) / 2, (v6[3] + v6[1]) / 2);
  }
  ((C2DSpark *)this->m_pUtil->m_p2DSpark)->SetEnableMouseTrack(691, 36);
  return 1;
}

// 0x004DC510
double CCBSystem::ResetConfig(int nVal)
{
  TxtFile **p_m_pConfig; // ecx
  CCBAttackSequen *m_pUI; // ecx
  double result; // st7

  p_m_pConfig = &this->m_pConfig;
  *p_m_pConfig = 0;
  p_m_pConfig[1] = 0;
  p_m_pConfig[2] = 0;
  p_m_pConfig[3] = 0;
  memset(&this->m_p3DSpark, 0, 0x2Cu);
  m_pUI = (CCBAttackSequen *)this->m_pUI;
  LOBYTE(this->m_pEffectSimple) = 0;
  result = ((CCBAttackSequen *)m_pUI)->SetPause();
  *(_BYTE *)(*((_DWORD *)&this->m_pControl->m_DeltaTime + (int)this->m_pES) + 280) = 0;
  this->m_pES = (CEffectSystem *)-1;
  return result;
}

// 0x004DC650
int CCBSystem::FindFreeThread(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        int nVal6,
        int nVal7,
        int nVal8,
        int nVal9)
{
  int v11; // edi
  int *i; // eax
  char *v14; // esi
  CCBSystem **v15; // edx
  int v16; // [esp+0x30] [ebp+0x28]

  v11 = 0;
  for ( i = &this->m_Thread[0].nTaskIndex; *(_BYTE *)i; i += 16 )
  {
    if ( ++v11 >= 20 )
      return -1;
  }
  v14 = (char *)this + 64 * v11;
  *((_DWORD *)v14 + 28) = nVal;
  *((_DWORD *)v14 + 29) = nVal2;
  *((_DWORD *)v14 + 30) = nVal3;
  *((_DWORD *)v14 + 31) = nVal4;
  v15 = &this->m_pUtil + 16 * v11 + 32;
  *v15 = (CCBSystem *)nVal5;
  v15[1] = (CCBSystem *)nVal6;
  v15[2] = (CCBSystem *)nVal7;
  v15[3] = (CCBSystem *)nVal8;
  v14[172] = 1;
  v14[173] = 0;
  *((_DWORD *)v14 + 37) = 0;
  *((_DWORD *)v14 + 38) = nVal9;
  *((_DWORD *)v14 + 39) = v16;
  *((_DWORD *)v14 + 40) = 0;
  *((_DWORD *)v14 + 36) = ((CCBSystem *)this->m_pUtil)->ProcProtect();
  *((_DWORD *)v14 + 41) = -1;
  ++LODWORD(this->m_fTimeScale);
  return v11;
}

// 0x004F1C40
char CCBSystem::ValidateThreadAction(int nVal)
{
  int i; // esi

  for ( i = 0; i < 11; ++i )
  {
    if ( *(_BYTE *)(nVal + 17) )
    {
      if ( !*(_BYTE *)(i + nVal + 29) )
        continue;
    }
    else if ( *(_DWORD *)(nVal + 12) != i )
    {
      continue;
    }
    if ( ((CCBRoleState *)this)->CalcComboDirect((const void *)nVal, i) < 0
      && !((CCBSystem *)*(CCBSystem **)(this->m_Thread[4].dwID + 12))->IsCmdEmpty(i)
      && !((CCBSystem *)*(CCBSystem **)(this->m_Thread[4].dwID + 12))->IsCmdReady(i) )
    {
      ((CCBSystem *)*(CCBSystem **)(this->m_Thread[4].dwID + 12))->GetCmdData(i);
    }
  }
  return 1;
}

// 0x004F2C70
int CCBSystem::AddCommand(int nCmdType, BOOL bImmediate, int nParam)
{
  char *v6; // ebp
  int v8; // ebx
  int TotalRounds; // eax
  int v10; // ecx
  unsigned int dwID; // eax
  unsigned int v12; // esi
  int RoleIndex; // ebp
  int v14; // eax
  char v15; // [esp+0x13] [ebp-0x39]
  int p_DWORD[3]; // [esp+0x14] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x20] [ebp-0x2C] BYREF
  int nCmdTypea; // [esp+0x50] [ebp+0x4]
  int bImmediatea; // [esp+0x54] [ebp+0x8]
  int v20; // [esp+0x5C] [ebp+0x10]

  memset(pData, 0, sizeof(pData));
  v15 = 1;
  v6 = (char *)this + 892 * nCmdType;
  nCmdTypea = (int)v6;
  if ( !v6[578] )
  {
    *((_DWORD *)v6 + 147) = 0;
    return 0;
  }
  if ( v6[1432] )
    return 0;
  if ( ((CCBRoleState *)this)->GetRoleField(nCmdType, 23) )
    return 0;
  v8 = bImmediate;
  if ( bImmediate < 0 && v6[1140] && bImmediate < -1 )
    v8 = bImmediate / 2;
  if ( !*(_BYTE *)(*(_DWORD *)(this->m_Thread[4].nTaskIndex + 4 * nCmdType + 24) + 272) )
    v15 = 0;
  if ( v8 < 0 && v6[700] )
  {
    TotalRounds = ((CCBRoleState *)this)->GetTotalRounds();
    if ( TotalRounds >= -v8 )
    {
      ((CCBRoleState *)this)->CheckBuff(nCmdType);
      return 0;
    }
    v8 += TotalRounds;
    ((CCBRoleState *)this)->CheckBuff(nCmdType);
  }
  bImmediatea = *((_DWORD *)v6 + 147);
  *((_DWORD *)v6 + 147) = v8 + bImmediatea;
  v10 = *((_DWORD *)v6 + 148);
  if ( v8 + bImmediatea <= v10 )
    v10 = v8 + bImmediatea < 0 ? 0 : v8 + bImmediatea;
  *((_DWORD *)v6 + 147) = v10;
  if ( v8 < 0 && ((CCBSystem *)this->m_Thread[4].dwID)->CreateObj((CCBRoleState **)nCmdType) )
    ((CCBSystem *)*(CCBSystem **)(this->m_Thread[4].dwID + 12))->GetCmdData(nCmdType);
  dwID = this->m_Thread[4].dwID;
  if ( *(_BYTE *)(dwID + 133) )
    ((CCBUI *)*(CCBUI **)(dwID + 28))->HandleRoleStateDialog(nCmdType);
  if ( v8 < 0 && ((CCBRoleState *)this)->GetRoleField(nCmdType, 17) )
    ((CCBRoleState *)this)->ProcessRound(nCmdType);
  if ( LOBYTE(this->m_Thread[4].cmd.dwItemID) && nCmdType == 10 )
    this->m_Thread[106].dwReturn = this->m_Thread[106].nTemp;
  if ( *((int *)v6 + 147) <= 0 )
  {
    if ( *((_DWORD *)v6 + 138) == 738 )
    {
      ((CCBSystem *)this->m_Thread[4].dwID)->ProcMessage(nCmdType);
      ((CCBRoleState *)this)->LoadRoleModel(nCmdType);
      v12 = this->m_Thread[4].dwID;
      if ( *(_BYTE *)(v12 + 133) )
        ((CCBUI *)*(CCBUI **)(v12 + 28))->HandleRoleStateDialog(nCmdType);
      return -bImmediatea;
    }
    *((_DWORD *)v6 + 147) = 0;
    *((float *)v6 + 349) = *(float *)(this->m_Thread[4].dwID + 80);
    *((_DWORD *)v6 + 348) = v20;
    ((CCBSystem *)this->m_Thread[4].dwID)->ProcMessage(nCmdType);
  }
  if ( v15 )
  {
    LOBYTE(pData[10]) = 1;
    pData[2] = nCmdType;
    pData[0] = 259;
    pData[1] = 0;
    pData[3] = nCmdType;
    LOWORD(pData[4]) = 0;
    if ( v8 > 0 )
    {
      RoleIndex = ((CCBStage *)this->m_Thread[4].nTaskIndex)->GetRoleIndex(6, pData, 1);
      if ( RoleIndex != -1 )
      {
        if ( v8 > *(_DWORD *)(nCmdTypea + 592) - bImmediatea )
          v8 = *(_DWORD *)(nCmdTypea + 592) - bImmediatea;
        ((CCBRoleState *)this)->CheckRoleStatus((int)p_DWORD);
        ((CCBStage *)this->m_Thread[4].nTaskIndex)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::GetRoleTaskNum */, 0, 0, 0, p_DWORD, -1082130432, 1075838976);
        goto LABEL_48;
      }
    }
    else
    {
      RoleIndex = ((CCBStage *)this->m_Thread[4].nTaskIndex)->GetRoleIndex(6, pData, 1);
      if ( RoleIndex != -1 )
      {
        if ( (_BYTE)nParam && v8 < 0 )
          ((CCBStage *)this->m_Thread[4].nTaskIndex)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::HandleKeyFriend */, 0, 0, 0, p_DWORD, -1082130432, 0);
        ((CCBRoleState *)this)->CheckRoleStatus((int)p_DWORD);
        ((CCBStage *)this->m_Thread[4].nTaskIndex)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::GetRoleTaskNum */, 0, 0, 0, p_DWORD, -1082130432, 0x40000000);
LABEL_48:
        ((CCBStage *)this->m_Thread[4].nTaskIndex)->GetStageRoleByIdx(RoleIndex);
      }
    }
    v6 = (char *)nCmdTypea;
  }
  v14 = *((_DWORD *)v6 + 148);
  if ( *((_DWORD *)v6 + 147) > v14 )
    *((_DWORD *)v6 + 147) = v14;
  if ( v8 <= 0 )
    return -abs32(bImmediatea - *((_DWORD *)v6 + 147));
  else
    return v8;
}

// 0x004F7050
bool CCBSystem::IsMagicSlotMsg(int nVal)
{
  int v2; // eax

  v2 = *(_DWORD *)(nVal + 4);
  return v2 == 6119 || v2 == 6120 || v2 == 6121 || v2 == 6122 || v2 == 6123 || v2 == 6124 || v2 == 6125;
}

// 0x004F70A0
char CCBSystem::HandleMagicCommand(int nVal)
{
  char result; // al

  switch ( *(_DWORD *)(nVal + 4) )
  {
    case 0x17E7:
      if ( !HIBYTE(g_nMagicSlotCountA) )
        goto LABEL_16;
      result = 1;
      break;
    case 0x17E8:
      if ( !(_BYTE)g_nMagicSlotCountB )
        goto LABEL_16;
      result = 1;
      break;
    case 0x17E9:
      if ( !BYTE1(g_nMagicSlotCountA) )
        goto LABEL_16;
      result = 1;
      break;
    case 0x17EA:
      if ( !BYTE2(g_nMagicSlotCountA) )
        goto LABEL_16;
      result = 1;
      break;
    case 0x17EB:
      if ( !BYTE1(g_nMagicSlotCountB) )
        goto LABEL_16;
      result = 1;
      break;
    case 0x17EC:
      if ( !HIBYTE(g_nMagicSlotCountB) )
        goto LABEL_16;
      result = 1;
      break;
    case 0x17ED:
      if ( !BYTE2(g_nMagicSlotCountB) )
        goto LABEL_16;
      result = 1;
      break;
    default:
LABEL_16:
      result = 0;
      break;
  }
  return result;
}

// 0x004F7140
char CCBSystem::HandleMagicSlotInput(int nVal)
{
  int v2; // eax

  v2 = *(_DWORD *)(nVal + 4) - 6119;
  switch ( *(_DWORD *)(nVal + 4) )
  {
    case 0x17E7:
      LOBYTE(v2) = HIBYTE(g_nMagicSlotCountA);
      if ( HIBYTE(g_nMagicSlotCountA) )
        LOBYTE(v2) = --HIBYTE(g_nMagicSlotCountA);
      break;
    case 0x17E8:
      LOBYTE(v2) = g_nMagicSlotCountB;
      if ( (_BYTE)g_nMagicSlotCountB )
      {
        LOBYTE(v2) = g_nMagicSlotCountB - 1;
        LOBYTE(g_nMagicSlotCountB) = g_nMagicSlotCountB - 1;
      }
      break;
    case 0x17E9:
      LOBYTE(v2) = BYTE1(g_nMagicSlotCountA);
      if ( BYTE1(g_nMagicSlotCountA) )
        LOBYTE(v2) = --BYTE1(g_nMagicSlotCountA);
      break;
    case 0x17EA:
      LOBYTE(v2) = BYTE2(g_nMagicSlotCountA);
      if ( BYTE2(g_nMagicSlotCountA) )
        LOBYTE(v2) = --BYTE2(g_nMagicSlotCountA);
      break;
    case 0x17EB:
      LOBYTE(v2) = BYTE1(g_nMagicSlotCountB);
      if ( BYTE1(g_nMagicSlotCountB) )
        LOBYTE(v2) = --BYTE1(g_nMagicSlotCountB);
      break;
    case 0x17EC:
      LOBYTE(v2) = HIBYTE(g_nMagicSlotCountB);
      if ( HIBYTE(g_nMagicSlotCountB) )
        LOBYTE(v2) = --HIBYTE(g_nMagicSlotCountB);
      break;
    case 0x17ED:
      LOBYTE(v2) = BYTE2(g_nMagicSlotCountB);
      if ( BYTE2(g_nMagicSlotCountB) )
        LOBYTE(v2) = --BYTE2(g_nMagicSlotCountB);
      break;
    default:
      return v2;
  }
  return v2;
}

// 0x004FCA40
int CCBSystem::FindThreadByID(int nID)
{
  int result; // eax
  int v3; // edx

  result = (int)&this->m_Thread[29].cmd;
  v3 = 0;
  while ( !*(_BYTE *)(result + 52) || *(_DWORD *)result != nID )
  {
    ++v3;
    result += 2632;
    if ( v3 >= 256 )
    {
      LOBYTE(result) = 0;
      return result;
    }
  }
  LOBYTE(result) = 1;
  return result;
}

// 0x00500170
int CCBSystem::EndBattle()
{
  int v2; // eax
  _DWORD *v3; // edi
  char *v4; // ebp
  int v5; // eax

  v2 = 2632 * (int)this->m_Thread[0].fp[2];
  v3 = &this->m_Thread[29].cmd.bMultiSrcRole + v2;
  v4 = (char *)&this->m_Thread[0].nTemp + 80 * (int)this->m_Thread[0].fp[3] + v2;
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *v3))->IsReady(*(unsigned int *)((char *)&this->m_Thread[29].cmd.dwCmdKind + v2)) )
    goto LABEL_7;
  if ( !v4[41] && ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *v3))->ForceDelTaskByPFN() )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *v3))->GetCurrentState();
    v5 = *((_DWORD *)&this->m_pAI + *v3);
    *(_DWORD *)(v5 + 6632) = *(_DWORD *)(v5 + 6636);
    v4[41] = 1;
  }
  if ( v4[43] == 1 || ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *v3))->ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v4 + 4) = 4;
  return 0;
}

// 0x00504D60
char CCBSystem::CastProtect(int nCaster, int nTarget, float fVal)
{
  unsigned int v5; // eax
  int *v7; // [esp-0x8] [ebp-0x28]
  int *v8; // [esp-0x4] [ebp-0x24]

  v8 = &this->m_Thread[50].nTemp + 6 * nTarget;
  v7 = &this->m_Thread[50].nTemp + 6 * nCaster;
  v5 = ((CCBSystem *)*(CCBSystem **)this->m_Thread[4].cmd.dwCmdKind)->ProcProtect();
  ((CCBStage *)this)->EnqueueCommand(0 /* TODO: (int)CCBStage::ProcessQueuedCommand */, 0, 0, 0, v5, fVal, v7, v8);
  return 1;
}

// 0x00512310
void CCBSystem::HandleInput()
{
  g_fCBTimeScale = 12.0 + 12.0;
}

// 0x00512320
// attributes: thunk
void CCBSystem::SetQuitFlag()
{

}

// 0x00512330
bool CCBSystem::IsEditorWindow()
{
  g_nCBRolePos[0] = 119;
  g_nCBRolePos[1] = 314;
  g_nCBRolePos[2] = 510;
  g_nCBRolePos[3] = 707;
  return -61;
}

// 0x00512370
// attributes: thunk
void CCBSystem::SetAuto()
{

}

// 0x00512380
void CCBSystem::SetAutoOnly()
{
  g_nCBRolePos[4] = 519;
  g_nCBRolePos[5] = 519;
  g_nCBRolePos[6] = 519;
  g_nCBRolePos[7] = 519;
}

// 0x005123C0
// attributes: thunk
void CCBSystem::ShowInfo()
{

}

// 0x005123D0
void CCBSystem::SetTimeScale()
{
  g_nCBRolePos[8] = 128;
  g_nCBRolePos[9] = 323;
  g_nCBRolePos[10] = 519;
  g_nCBRolePos[11] = 716;
}

// 0x00512410
// attributes: thunk
unsigned int CCBSystem::GetFreeID()
{
  return compiler_init_00512420(this);
}

// 0x00512460
// attributes: thunk
void CCBSystem::DelAllTaskAndThread()
{

}

// 0x00512470
void CCBSystem::Proceed()
{
  g_nCBRolePos[16] = 121;
  g_nCBRolePos[17] = 316;
  g_nCBRolePos[18] = 512;
  g_nCBRolePos[19] = 709;
}

// 0x005124B0
// attributes: thunk
bool CCBSystem::CanBeHandleWPX_R()
{
  return this->CanBeHandleNGH_R();
}

// 0x005124C0
bool CCBSystem::CanBeHandleNGH_R()
{
  g_nCBRolePos[20] = 573;
  g_nCBRolePos[21] = 573;
  g_nCBRolePos[22] = 573;
  g_nCBRolePos[23] = 573;
  return 61;
}

// 0x00512500
CCBSystem::CCBSystem()
{
  tagCmdData *p_cmd; // esi
  int v2; // ebx
  tagCmdData *v3; // edi
  tagPlayerSet *m_Player; // esi
  int v5; // ebx
  tagPlayerSet *v6; // edi

  p_cmd = &this->m_Thread[0].cmd;
  v2 = 1024;
  do
  {
    v3 = p_cmd;
    p_cmd += 2;
    --v2;
    memset(v3, 0, sizeof(tagCmdData));
  }
  while ( v2 );
  m_Player = this->m_Player;
  v5 = 11;
  do
  {
    v6 = m_Player++;
    --v5;
    memset(v6, 0, 0x2Cu);
  }
  while ( v5 );
  memset(this, 0, sizeof(CCBSystem));
  *(_DWORD *)&this->m_eResult = 0;
  LOBYTE(this->m_nTimesOfCombat) = 0;
  BYTE1(this->m_nTimesOfCombat) = 0;
  *(_DWORD *)&this->m_bFiveNimbus = 0;
  this->m_bQuitFlag = 1;
  *(_DWORD *)&this->m_eState = 1;
  BYTE2(this->m_nTimesOfCombat) = 1;
}

// 0x00512580
unsigned int CCBSystem::ProcDialog()
{
  this->m_DeltaTime = 0.0;
  memset(this->m_Thread, 0, sizeof(this->m_Thread));
  LODWORD(this->m_dTimeFund) = 0;
  LODWORD(this->m_AbsDeltaTime) = 0;
  LODWORD(this->m_dAbsTimeFund) = 0;
  *(_DWORD *)&this->m_eState = 1;
  *(_DWORD *)&this->m_eResult = 1;
  this->m_dwIDHolder = 0;
  this->m_nThread = -1;
  this->m_bQuitFlag = 1;
  HIDWORD(this->m_dTimeFund) = 0;
  this->m_fTimeFund = 0.0;
  HIDWORD(this->m_AbsDeltaTime) = 0;
  HIDWORD(this->m_dAbsTimeFund) = 0;
  this->m_fAbsTimeFund = 0.0;
  HIBYTE(this->m_nTimesOfCombat) = 1;
  return 0;
}

// 0x005125E0
char CCBSystem::ProcNormalAttack()
{
  std::codecvt_base *v2; // ecx
  CCBSystem *v3; // eax
  char result; // al
  CCBUI *v5; // eax
  int *v6; // eax
  CCBRoleState *v7; // eax
  CCBRoleState *v8; // eax
  CCBSystem *v9; // eax
  CCBAttackSequen *inited; // eax
  CCBStage *v11; // eax
  int *v12; // eax
  CCBSystem *v13; // eax
  CCBControl *v14; // eax
  CCBAI *v15; // eax
  CCBAI *v16; // eax
  SceneMgr *v17; // eax
  CCBStageCam *m_pCam; // edx
  int p_OrthoSize; // edx
  CEffMgr *v20; // eax
  SceneMgr *v21; // eax
  CCBStageCam *v22; // ecx
  int v23; // ecx
  CEffMgr *v24; // eax
  C2DSpark *v25; // eax
  C2DSpark *v26; // eax
  C3DSpark *v27; // eax
  C3DSpark *v28; // eax
  CEffectSystem *m_pES; // ecx
  CEffectSimple *v30; // eax
  char pExceptionObject[1024]; // [esp+0xC] [ebp-0x100C] BYREF
  char ArgList[1024]; // [esp+0x40C] [ebp-C0Ch] BYREF
  char v33[1024]; // [esp+0x80C] [ebp-0x80C] BYREF
  char v34; // [esp+C0Ch] [ebp-0x40C] BYREF
  int v35; // [esp+0x1014] [ebp-0x4]

  v35 = 0;
  if ( operator new(1u) )
    v3 = (CCBSystem *)sub_51D5C0(this);
  else
    v3 = 0;
  this->m_pUtil = v3;
  v35 = -1;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_8, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = ((std *)v2)->codecvt_base::do_always_noconv();
  if ( result )
  {
    v5 = (CCBUI *)operator new(0xA48u);
    v35 = 1;
    if ( v5 )
      v6 = ((CCBUI *)v5)->ctor((int)this);
    else
      v6 = 0;
    v35 = -1;
    this->m_pUI = (CCBUI *)v6;
    if ( !v6 )
    {
      qmemcpy(
        pExceptionObject,
        ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_8, 2504),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    result = sub_5163D0((CCBUI *)v6);
    if ( result )
    {
      v7 = (CCBRoleState *)operator new(0x50A4u);
      v35 = 2;
      if ( v7 )
        v8 = ((CCBRoleState *)v7)->ClearAndSetGP((int)this);
      else
        v8 = 0;
      v35 = -1;
      this->m_pRoleState = v8;
      if ( !v8 )
      {
        qmemcpy(
          pExceptionObject,
          ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_8, 2504),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      result = ((CIniFile *)v8)->LoadData();
      if ( result )
      {
        v9 = (CCBSystem *)operator new(0x1C8u);
        v35 = 3;
        if ( v9 )
          inited = (CCBAttackSequen *)((CCBSystem *)v9)->InitCmd((int)this);
        else
          inited = 0;
        v35 = -1;
        this->m_pAttackSequen = inited;
        if ( !inited )
        {
          qmemcpy(
            pExceptionObject,
            ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_8, 2504),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        result = ((std *)inited)->codecvt_base::do_always_noconv();
        if ( result )
        {
          v11 = (CCBStage *)operator new(0xA48B0u);
          v35 = 4;
          if ( v11 )
            // [AUTO-COMMENTED] v12 = ((CCBStage *)v11)->CCBStage((int)this);
          else
            v12 = 0;
          v35 = -1;
          this->m_pStage = (CCBStage *)v12;
          if ( !v12 )
          {
            qmemcpy(
              pExceptionObject,
              ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_8, 2504),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          result = ((CCBStageScene *)v12)->ResetSceneState();
          if ( result )
          {
            v13 = (CCBSystem *)operator new(0x570u);
            v35 = 5;
            if ( v13 )
              v14 = (CCBControl *)((CCBSystem *)v13)->CopyCmdData((int *)this);
            else
              v14 = 0;
            v35 = -1;
            this->m_pControl = v14;
            if ( !v14 )
            {
              qmemcpy(
                pExceptionObject,
                ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_8, 2504),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            result = ((std *)v14)->codecvt_base::do_always_noconv();
            if ( result )
            {
              v15 = (CCBAI *)operator new(0xE50u);
              v35 = 6;
              if ( v15 )
                v16 = ((CCBAI *)v15)->Create((int *)this);
              else
                v16 = 0;
              v35 = -1;
              this->m_pAI = v16;
              if ( !v16 )
              {
                qmemcpy(v33, ((Logger *)&v34)->FormatException(&path[164], aDProjectPal3Co_8, 2504), sizeof(v33));
                _CxxThrowException(v33, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              result = ((std *)v16)->codecvt_base::do_always_noconv();
              if ( result )
              {
                this->m_pES = (CEffectSystem *)g_pEffectSystem;
                this->ProcAI(1.0);
                result = this->CreateObj(&this->m_pEditor);
                if ( result )
                {
                  v17 = (SceneMgr *)operator new(0xA930u);
                  v35 = 7;
                  if ( v17 )
                  {
                    m_pCam = this->m_pStage->m_pCam;
                    if ( m_pCam )
                      p_OrthoSize = (int)&m_pCam->OrthoSize;
                    else
                      p_OrthoSize = 0;
                    v20 = ((SceneMgr *)v17)->Create((int)gfxMgr, p_OrthoSize, (int)this);
                  }
                  else
                  {
                    v20 = 0;
                  }
                  this->m_pEffMgr = v20;
                  v21 = (SceneMgr *)operator new(0xA930u);
                  v35 = 8;
                  if ( v21 )
                  {
                    v22 = this->m_pStage->m_pCam;
                    if ( v22 )
                      v23 = (int)&v22->OrthoSize;
                    else
                      v23 = 0;
                    v24 = ((SceneMgr *)v21)->Create((int)gfxMgr, v23, (int)this);
                  }
                  else
                  {
                    v24 = 0;
                  }
                  this->m_pATSEffMgr = v24;
                  v25 = (C2DSpark *)operator new(0x5870u);
                  v35 = 9;
                  if ( v25 )
                  {
                  }
                  else
                    v26 = 0;
                  this->m_p2DSpark = v26;
                  v27 = (C3DSpark *)operator new(0x3E30u);
                  v35 = 10;
                  if ( v27 )
                    // [AUTO-COMMENTED] v28 = ((C3DSpark *)v27)->C3DSpark();
                  else
                    v28 = 0;
                  m_pES = this->m_pES;
                  this->m_p3DSpark = v28;
                  v30 = (CEffectSimple *)sub_4C5980(m_pES, 1);
                  this->m_pEffectSimple = v30;
                  return 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

// 0x00512BA0
char CCBSystem::ProcFling()
{
  CCBStage *m_pStage; // ecx
  CCBStage *v3; // edi
  std::codecvt_base *m_pAttackSequen; // ecx
  CCBAttackSequen *v5; // edi
  CCBRoleState *m_pRoleState; // ecx
  CCBRoleState *v7; // edi
  std::codecvt_base *m_pControl; // ecx
  CCBControl *v9; // edi
  CCBUI *m_pUI; // ecx
  CCBUI *v11; // ecx
  std::codecvt_base *m_pAI; // ecx
  CCBAI *v13; // ecx
  CCBEditor *m_pEditor; // ecx
  CCBEditor *v15; // ecx
  gbRefObject *m_pEffMgr; // edi
  CEffMgr *m_pATSEffMgr; // edi
  C2DSpark *m_p2DSpark; // edi
  C3DSpark *m_p3DSpark; // ecx
  void *v21; // [esp+0x0] [ebp-0xC]

  m_pStage = this->m_pStage;
  if ( !m_pStage )
    return 0;
  ((CCBStage *)m_pStage)->Create();
  v3 = this->m_pStage;
  if ( v3 )
  {
    todo_408BD0(v21);
    operator delete(v3);
  }
  this->m_pStage = 0;
  m_pAttackSequen = (std::codecvt_base *)this->m_pAttackSequen;
  if ( !m_pAttackSequen )
    return 0;
  ((std *)m_pAttackSequen)->codecvt_base::do_always_noconv();
  v5 = this->m_pAttackSequen;
  if ( v5 )
  {
    todo_408BD0(v21);
    operator delete(v5);
  }
  this->m_pAttackSequen = 0;
  m_pRoleState = this->m_pRoleState;
  if ( !m_pRoleState )
    return 0;
  ((CCBRoleState *)m_pRoleState)->IterateMagicSlots();
  v7 = this->m_pRoleState;
  if ( v7 )
  {
    todo_408BD0(v21);
    operator delete(v7);
  }
  this->m_pRoleState = 0;
  m_pControl = (std::codecvt_base *)this->m_pControl;
  if ( !m_pControl )
    return 0;
  ((std *)m_pControl)->codecvt_base::do_always_noconv();
  v9 = this->m_pControl;
  if ( v9 )
  {
    ((CCBSystem *)this->m_pControl)->GetState();
    operator delete(v9);
  }
  this->m_pControl = 0;
  m_pUI = this->m_pUI;
  if ( !m_pUI )
    return 0;
// [VFTABLE] ((void ( *)(CCBUI *))m_pUI->__vftable->Destroy)(m_pUI);
  v11 = this->m_pUI;
  if ( v11 )
// [VFTABLE] ((void ( *)(CCBUI *, int))v11->__vftable->sub_4431B0)(v11, 1);
  this->m_pUI = 0;
  m_pAI = (std::codecvt_base *)this->m_pAI;
  if ( !m_pAI )
    return 0;
  ((std *)m_pAI)->codecvt_base::do_always_noconv();
  v13 = this->m_pAI;
  if ( v13 )
    ((CCBSystem *)v13)->DestroyObj((CCBSystem *)1, (char)v21);
  this->m_pAI = 0;
  m_pEditor = this->m_pEditor;
  if ( !m_pEditor )
    return 0;
  ((CCBStage *)m_pEditor)->DestroyDialog();
  v15 = this->m_pEditor;
  if ( v15 )
    ((CCBSystem *)v15)->DestroyObj_5df0((CCBSystem *)1, (char)v21);
  this->m_pEditor = 0;
  if ( !this->m_pUtil )
    return 0;
  ((std *)v15)->codecvt_base::do_always_noconv();
  if ( this->m_pUtil )
    ((CCBSystem *)this->m_pUtil)->DestroyObj((CCBSystem *)1, (char)v21);
  m_pEffMgr = (gbRefObject *)this->m_pEffMgr;
  this->m_pUtil = 0;
  if ( m_pEffMgr )
  {
    ((gbRefObject *)m_pEffMgr)->ReleaseAllRefs((gbRefObject **)v21);
    operator delete(m_pEffMgr);
    this->m_pEffMgr = 0;
  }
  m_pATSEffMgr = this->m_pATSEffMgr;
  if ( m_pATSEffMgr )
  {
    ((gbRefObject *)this->m_pATSEffMgr)->ReleaseAllRefs((gbRefObject **)v21);
    operator delete(m_pATSEffMgr);
    this->m_pATSEffMgr = 0;
  }
  m_p2DSpark = this->m_p2DSpark;
  if ( m_p2DSpark )
  {
    ((C2DSpark *)this->m_p2DSpark)->_C2DSpark();
    operator delete(m_p2DSpark);
    this->m_p2DSpark = 0;
  }
  m_p3DSpark = this->m_p3DSpark;
  if ( m_p3DSpark )
  {
    ((CCBSystem *)m_p3DSpark)->ProcCoAttack((CCBSystem *)1, (char)v21);
    this->m_p3DSpark = 0;
  }
  return 1;
}

// 0x00512D40
void * CCBSystem::ProcCoAttack(CCBSystem *Block, char formal)
{
  ((C3DSpark *)this)->_C3DSpark();
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00512D60
char CCBSystem::ProcWeaponSkill()
{
  CCBUI *m_pUI; // ecx
  CCBControl *m_pControl; // ecx
  CCBRoleState *m_pRoleState; // ecx
  CCBAttackSequen *m_pAttackSequen; // ecx
  CCBStage *m_pStage; // ecx
  CCBAI *m_pAI; // ecx
  CCBEditor *m_pEditor; // ecx
  CEffMgr *m_pEffMgr; // ecx
  CEffMgr *m_pATSEffMgr; // ecx
  int v12; // edi
  int i; // ebp
  CCBRoleState *v14; // ecx
  CCBRoleState *v15; // ecx
  int v16; // [esp+0x0] [ebp-0x10]
  int v17; // [esp+0x4] [ebp-0xC]

  if ( !this->m_pUtil || !((CCBLineupWindow *)this)->IsFaceOnInitPos() )
    return 0;
  m_pUI = this->m_pUI;
  if ( !m_pUI || !((CCBUI *)m_pUI)->CreateParaWindow() )
    return 0;
  m_pControl = this->m_pControl;
  if ( !m_pControl || !((CCBUI *)m_pControl)->IsActive() )
    return 0;
  m_pRoleState = this->m_pRoleState;
  if ( !m_pRoleState || !((CCBRoleState *)m_pRoleState)->DestroyAndReinit() )
    return 0;
  m_pAttackSequen = this->m_pAttackSequen;
  if ( !m_pAttackSequen || !((CCBSystem *)m_pAttackSequen)->DestroySubsystems() )
    return 0;
  m_pStage = this->m_pStage;
  if ( !m_pStage || !((CCBStage *)m_pStage)->Destroy() )
    return 0;
  m_pAI = this->m_pAI;
  if ( !m_pAI || !((CCBAI *)m_pAI)->Init() )
    return 0;
  if ( BYTE1(this->m_nTimesOfCombat) )
  {
    m_pEditor = this->m_pEditor;
    if ( !m_pEditor || !((CCBStage *)m_pEditor)->CreatePreviewDialog() )
      return 0;
  }
  m_pEffMgr = this->m_pEffMgr;
  if ( !m_pEffMgr || !((Combat *)m_pEffMgr)->Func_4CDB60() )
    return 0;
  m_pATSEffMgr = this->m_pATSEffMgr;
  if ( !m_pATSEffMgr || !((Combat *)m_pATSEffMgr)->Func_4CDB60() )
    return 0;
  ((C2DSpark *)this->m_p2DSpark)->CreateTrack(0, v16, v17);
  ((C2DSpark *)this->m_p2DSpark)->CreateStars();
  ((C3DSpark *)this->m_p3DSpark)->DestroyAll();
  v12 = 0;
  this->CreateObj((int ( *)(int, int))CCBSystem::Message, 0, 0, 0, 0);
  ((CCBAttackSequen *)this->m_pAttackSequen)->SetPause();
  for ( i = 0; i < 4460; i += 892 )
  {
    v14 = this->m_pRoleState;
    if ( v14->m_Role[0].bMagicMastered[5][i + 4] )
    {
      LOBYTE(((CCBRoleState *)v14)->InitUI(v12)[1].dwMagicID[2][4]) = 0;
      BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(v12)[1].dwMagicID[2][4]) = 0;
    }
    ++v12;
  }
  ((CCBSystem *)this->m_pEffectSimple)->GetThreadBase();
  ((gbSceneGraph *)gfxMgr->pSceneGraph)->ResetBladeMgr();
  v15 = this->m_pRoleState;
  if ( BYTE2(v15->m_Role[0].dwMagicID[8][4]) && *((_BYTE *)((CEffectSystem *)v15)->DestroyAllEffect() + 4) )
  {
    ((CCBCamControl *)this->m_pStage->m_pCamControl)->ClearFinishedTask(20);
    HIBYTE(this->m_nTimesOfCombat) = 1;
    return 1;
  }
  else
  {
    ((CCBCamControl *)this->m_pStage->m_pCamControl)->ClearFinishedTask(0);
    HIBYTE(this->m_nTimesOfCombat) = 1;
    return 1;
  }
}

// 0x00512F40
char CCBSystem::ProcMagicWait(unsigned int formal, char pData)
{
  int v4; // ecx
  UICursor *v5; // ecx
  unsigned int v6; // ebx
  unsigned int *v7; // edi
  unsigned int formala; // [esp+0x1C] [ebp+0x8]
  char v10; // [esp+0x23] [ebp+0xF]

  v4 = *(_DWORD *)&this->m_bFiveNimbus + 1;
  BYTE1(this->m_nTimesOfCombat) = pData;
  this->m_bQuitFlag = 0;
  *(_DWORD *)&this->m_eState = 2;
  *(_DWORD *)&this->m_eResult = 1;
  *(_DWORD *)&this->m_bFiveNimbus = v4;
  ++dword_C10CD4;
  this->m_pFightInfo = (FightInfo *)formal;
  v10 = this->ProcWeaponSkill();
  ((UICursor *)v5)->IRender();
  v6 = 0;
  v7 = &Buffer.m_partyActor.m_dwMatMsg[3];
  formala = 0;
  do
  {
    if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][formala + 4] && (*(v7 - 3) == 8114 || *v7 == 8114) )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)102.39999 )
        ((CCBRoleState *)this->m_pRoleState)->ProcessRound(v6);
    }
    v7 += 352;
    ++v6;
    formala += 892;
  }
  while ( (int)v7 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[202] );
  return v10;
}

// 0x00513060
int CCBSystem::CombatUpdate(double dt)
{
  double v3; // st6
  float *m_pEffMgr; // ecx
  double v5; // st7
  double v6; // st7
  CCBEditor *m_pEditor; // ecx
  int result; // eax
  float fVal; // [esp+0x0] [ebp-0x8]
  float fVala; // [esp+0x0] [ebp-0x8]
  float dta; // [esp+0xC] [ebp+0x4]

  this->m_AbsDeltaTime = dt;
  v3 = dt + this->m_dAbsTimeFund;
  m_pEffMgr = (float *)this->m_pEffMgr;
  this->m_dAbsTimeFund = v3;
  this->m_fAbsTimeFund = v3;
  v5 = dt * this->m_fTimeScale;
  this->m_DeltaTime = v5;
  v6 = v5 + this->m_dTimeFund;
  dta = v6;
  this->m_dTimeFund = v6;
  this->m_fTimeFund = v6;
  SceneMgrUpdate(m_pEffMgr, dta);
  SceneMgrUpdate((float *)this->m_pATSEffMgr, this->m_fAbsTimeFund);


  ((CCBAttackSequen *)this->m_pAttackSequen)->ResetTimers();
  ((CCBRoleState *)this->m_pRoleState)->Update();
  ((CCBAI *)this->m_pAI)->Update();
  ((CCBStage *)this->m_pStage)->Update();
  ((CCBControl *)this->m_pControl)->GetActiveAttackCount();
  if ( BYTE1(this->m_nTimesOfCombat) )
  {
    m_pEditor = this->m_pEditor;
    if ( m_pEditor )
      ((CCBUI *)m_pEditor)->StepFrame();
  }
  fVal = this->m_DeltaTime;
  ((C2DSpark *)this->m_p2DSpark)->Render(fVal);
  fVala = this->m_DeltaTime;
  ((C3DSpark *)this->m_p3DSpark)->Update(fVala);
  LOBYTE(result) = this->ProcDefence();
  return result;
}

// 0x00513120
char CCBSystem::RenderCheck()
{
  int v1; // edi
  char result; // al

  result = HIBYTE(this->m_nTimesOfCombat);
  if ( result )
  {
    HIBYTE(this->m_nTimesOfCombat) = 0;
  }
  else
  {
    ((CCBStage *)this->m_pStage)->EditorUpdate(v1);
    ((C2DSpark *)this->m_p2DSpark)->DestroyAll();
  }
  return result;
}

// 0x00513150
char CCBSystem::ProcMagic()
{
  char v2; // bl
  int v3; // ebp
  int i; // edi
  tagRoleState *inited; // eax
  int v6; // edi
  int j; // ebp
  CCBRoleState *m_pRoleState; // ecx
  int v9; // edi
  int k; // ebp
  CCBRoleState *v11; // ecx
  int v12; // edi
  int m; // ebp
  CCBRoleState *v14; // ecx

  v2 = 0;
  if ( g_RoleSystemCombat.dwInitParam == (HWND)1 )
  {
    if ( g_Input.KeyInfo[15].PressTime == 1 || g_Input.KeyInfo[16].PressTime == 1 )
    {
      v3 = 0;
      for ( i = 24; i < 68; i += 4 )
      {
        if ( ((CCBStageRole *)*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + i))->CheckViewTarget() )
        {
          ((CCBStage *)this->m_pStage)->DoTask(v3);
          v2 = 1;
        }
        ++v3;
      }
      if ( !v2 )
      {
        ((CCBStage *)this->m_pStage)->DoTask(-1);
        if ( ((CCBStageScene *)this->m_pStage->m_pScene)->LoadFlingNode() )
          LOBYTE(this->m_pStage->m_pScene->m_vecEnemyFiveLineupPos.y) = 1;
      }
    }
    if ( (g_Input.KeyInfo[15].Data & 0xF) != 1 && (g_Input.KeyInfo[16].Data & 0xF) != 1 )
    {
      ((CCBStage *)this->m_pStage)->DoTask(-1);
      LOBYTE(this->m_pStage->m_pScene->m_vecEnemyFiveLineupPos.y) = 0;
    }
  }
  LOBYTE(inited) = 1;
  if ( g_nCBResultState != 1 )
  {
    if ( g_Input.KeyInfo[30].PressTime == 1 && this->m_pRoleState )
    {
      v6 = 0;
      for ( j = 0; j < 4460; j += 892 )
      {
        m_pRoleState = this->m_pRoleState;
        if ( m_pRoleState->m_Role[0].bMagicMastered[5][j + 4] )
        {
          BYTE1(((CCBRoleState *)m_pRoleState)->InitUI(v6)[1].dwMagicID[1][0]) = 0;
          LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(v6)[1].dwMagicID[0][5]) = 0;
          BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(v6)[1].dwMagicID[0][5]) = 0;
          BYTE2(((CCBRoleState *)this->m_pRoleState)->InitUI(v6)[1].dwMagicID[0][5]) = 0;
          HIBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(v6)[1].dwMagicID[0][5]) = 0;
        }
        ++v6;
      }
      LOBYTE(inited) = 1;
    }
    if ( g_Input.KeyInfo[34].PressTime == 1 )
    {
      v9 = 0;
      for ( k = 0; k < 4460; k += 892 )
      {
        v11 = this->m_pRoleState;
        if ( v11->m_Role[0].bMagicMastered[5][k + 4] )
        {
          LOBYTE(((CCBRoleState *)v11)->InitUI(v9)[1].dwMagicID[2][4]) = 1;
          BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(v9)[1].dwMagicID[2][4]) = 0;
        }
        ++v9;
      }
      LOBYTE(inited) = 1;
    }
    if ( g_Input.KeyInfo[35].PressTime == 1 )
    {
      v12 = 0;
      for ( m = 0; m < 4460; m += 892 )
      {
        v14 = this->m_pRoleState;
        LOBYTE(inited) = v14->m_Role[0].bMagicMastered[5][m + 4];
        if ( (_BYTE)inited )
        {
          BYTE1(((CCBRoleState *)v14)->InitUI(v12)[1].dwMagicID[2][4]) = 1;
          inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(v12);
          LOBYTE(inited[1].dwMagicID[2][4]) = 0;
        }
        ++v12;
      }
    }
  }
  return (char)inited;
}

// 0x00513330
int CCBSystem::GetRenderFlag()
{
  int result; // eax
  CScreenMode *Instance; // eax
  char v4; // [esp+0x8] [ebp+0x4]

  LOBYTE(result) = v4;
  this->m_bQuitFlag = v4;
  if ( v4 == 1 )
  {
    ((gbSceneGraph *)gfxMgr->pSceneGraph)->ResetBladeMgr();
    ((CEffMgr *)this->m_pEffMgr)->ReleaseCompletedEffects();
    LOBYTE(result) = ((CEffMgr *)this->m_pATSEffMgr)->ReleaseCompletedEffects();
    if ( *(_DWORD *)&this->m_eResult == 3 )
    {
      LOBYTE(result) = this->m_pFightInfo->eBattleFieldAttr;
      if ( (_BYTE)result )
      {
        Instance = CScreenMode::GetInstance();
        return ((CScreenMode *)Instance)->StopAll();
      }
    }
  }
  return result;
}

// 0x00513380
bool CCBSystem::ProcUseItem(HWND formal)
{
  return ((CCBStage *)this->m_pEditor)->ProcessAction(formal);
}

// 0x00513390
int CCBSystem::SetRenderFlag(char flag)
{
  int v3; // edi
  int result; // eax

  v3 = 0;
  LOBYTE(this->m_nTimesOfCombat) = flag;
  do
  {
    BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(v3)[1].dwMagicID[1][0]) = this->m_nTimesOfCombat;
    LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(v3)[1].dwMagicID[0][5]) = this->m_nTimesOfCombat;
    BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(v3)[1].dwMagicID[0][5]) = this->m_nTimesOfCombat;
    BYTE2(((CCBRoleState *)this->m_pRoleState)->InitUI(v3)[1].dwMagicID[0][5]) = this->m_nTimesOfCombat;
    result = (int)((CCBRoleState *)this->m_pRoleState)->InitUI(v3++);
    *(_BYTE *)(result + 835) = this->m_nTimesOfCombat;
  }
  while ( v3 < 5 );
  return result;
}

// 0x00513420
char CCBSystem::ProcFlee(char formal)
{
  LOBYTE(this->m_nTimesOfCombat) = formal;
  return formal;
}

// 0x00513430
char CCBSystem::ProcDefence()
{
  int v2; // ebx
  int v3; // ebp
  int i; // edi
  int *v5; // eax
  int v6; // edx
  double v7; // st7
  char result; // al

  if ( (g_bCBActive & 1) == 0 )
  {
    g_bCBActive |= 1u;
    g_fCBSpeed = this->m_fTimeFund;
  }
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage((char *)5, 75, aThreadDStageta, this->m_dwIDHolder, this->m_pStage->m_nTaskCount);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage((char *)5, 90, aTimesOfCombatD, *(_DWORD *)&this->m_bFiveNimbus);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage((char *)5, 105, aTimefundF, this->m_fTimeFund);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage((char *)5, 120, aDeltatimeF, this->m_DeltaTime);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage((char *)5, 195, aEffectObjectsD, *(_DWORD *)&this->m_pEffMgr->m_sz5D8C3C[1832]);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage((char *)5, 210, aEffectTimerF, *(float *)&this->m_pEffMgr->m_sz5D8C3C[1844]);
  if ( (g_bCBActive & 2) == 0 )
  {
    g_nCBRoundCount[0] = 0;
    g_bCBActive |= 2u;
    g_nCBRoundCount[1] = 0;
    g_nCBRoundCount[2] = 0;
    atexit(nullsub_68);
  }
  v2 = 0;
  v3 = 20;
  for ( i = 24; i < 44; i += 4 )
  {
    v5 = (int *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[73].fp[2];
    g_nCBRoundCount[0] = *v5;
    g_nCBRoundCount[1] = v5[1];
    g_nCBRoundCount[2] = v5[2];
    v6 = *(int *)((char *)&this->m_pStage->m_pCBSystem + i);
    v7 = *(float *)(v6 + 6632);
    g_fCBDeltaTime = *(float *)(v6 + 6632);
    result = ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage((char *)0x17C, v3, aRoleDXFZFRotF, v2++, *(float *)g_nCBRoundCount, *(float *)&g_nCBRoundCount[2], v7);
    v3 += 15;
  }
  return result;
}

// 0x00513600
void CCBSystem::ProcAI(float formal)
{
  CEffectSystem *m_pES; // ecx
  CEffMgr *m_pEffMgr; // ecx
  CEffMgr *m_pATSEffMgr; // ecx
  int v6; // ecx
  int i; // eax
  gbGeomNode *m_pPointer; // ecx

  m_pES = this->m_pES;
  this->m_fTimeScale = formal;
  *(float *)&m_pES->m_fTimeScale = formal;
  m_pEffMgr = this->m_pEffMgr;
  if ( m_pEffMgr )
    ((CEffMgr *)m_pEffMgr)->SetEffectsTimeScale(SLODWORD(formal));
  m_pATSEffMgr = this->m_pATSEffMgr;
  if ( m_pATSEffMgr )
    ((CEffMgr *)m_pATSEffMgr)->SetEffectsTimeScale(1065353216);
  v6 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v6 + 4] )
      *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[1].dwReturn = formal;
    v6 += 892;
  }
  m_pPointer = this->m_pStage->m_pScene->m_pPointer;
  if ( m_pPointer )
    ((gbVisNode *)m_pPointer)->SetTimeScale(formal);
  if ( BYTE1(this->m_nTimesOfCombat) )
    ((CCBStage *)formal)->CreatePreview();
}

// 0x005136A0
unsigned int CCBSystem::ProcProtect()
{
  unsigned int v1; // eax

  v1 = *(_DWORD *)&this->m_bAuto + 1;
  *(_DWORD *)&this->m_bAuto = v1;
  if ( v1 >= 0x7FFFFFFF )
    *(_DWORD *)&this->m_bAuto = 1;
  return *(_DWORD *)&this->m_bAuto;
}

// 0x005136D0
char CCBSystem::ProcMessage(int idx)
{
  CCBControl *m_pControl; // ecx
  int v4; // ecx
  int i; // eax
  tagRoleState *inited; // edx
  char result; // al
  int v8; // [esp+0x0] [ebp-0x10]
  int v9; // [esp+0x4] [ebp-0xC]

  if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(0)->nProtectRole == idx )
    ((CCBRoleState *)this->m_pRoleState)->InitUI(0)->nProtectRole = -1;
  m_pControl = this->m_pControl;
  if ( m_pControl->m_bActive && ((CCBControl *)m_pControl)->GetControl() == idx )
  {
    ((CCBControl *)this->m_pControl)->GetState();
    v4 = 0;
    for ( i = 24; i < 68; i += 4 )
    {
      if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v4 + 4] )
      {
        LOBYTE((*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[1].cmd.dwCmdKind) = 0;
        BYTE2((*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[1].nTemp) = 0;
      }
      v4 += 892;
    }
  }
  ((CCBStage *)idx)->IsTaskValidButNotFinish(v8, v9);
  ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(idx);
  ((CCBSystem *)this->m_pAttackSequen)->InvokeThreadMethod(idx, 0);
  this->m_pStage->m_pRole[idx]->m_bShowWeapon = 0;
  this->m_pStage->m_pRole[idx]->m_bFlash = 0;
  ((CCBStageRole *)this->m_pStage->m_pRole[idx])->ClearAniMsg(0, 1.0);
  inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(idx);
  memset((char *)&inited->byMagicUseTime[8][5] + 1, 0, 0x18u);
  *(_WORD *)&inited[1].sModel[5] = 0;
  inited[1].sModel[7] = 0;
  memset(&inited[1].sModel[8], 0, 0x34u);
  LOWORD(inited[1].nSpeed) = 0;
  memset((char *)&inited[1].nSpeed + 2, 0, 0x34u);
  HIWORD(inited[1].fHPIncPerRound) = 0;
  LOBYTE(inited->byMagicUseTime[8][5]) = 0;
  ((CCBStageRole *)this->m_pStage->m_pRole[idx])->DangerForceRelease(0);
  return result;
}

// 0x005137F0
bool CCBSystem::IsFriendDoSkill()
{
  int v2; // ebp
  tagThread *m_Thread; // esi
  bool result; // al

  v2 = 0;
  m_Thread = this->m_Thread;
  do
  {
    if ( m_Thread->bValid == 1 )
    {
      this->m_nThread = v2;
      result = ((int ( *)(char *, _DWORD))m_Thread->fp[0])((char *)this + (unsigned int)m_Thread->fp[1], 0);
      this->m_nThread = -1;
    }
    ++v2;
    ++m_Thread;
  }
  while ( v2 < 1024 );
  this->m_nThread = -1;
  return result;
}

// 0x00513840
int CCBSystem::CheckBattleEnd()
{
  int *p_m_CmdData; // ebx
  int v3; // eax
  tagPlayerSet *m_Player; // edi
  int v5; // esi
  bool v6; // bl
  int j; // edi
  tagRoleState *inited; // eax
  int k; // edi
  tagRoleState *v10; // eax
  bool v11; // cc
  CCBControl *v13; // ecx
  int Control; // eax
  int v15; // eax
  CCBControl *m_pControl; // ecx
  int v17; // [esp+0x10] [ebp-0xC]
  int v18; // [esp+0x14] [ebp-0x8]
  tagPlayerSet *i; // [esp+0x18] [ebp-0x4]

  if ( BYTE1(this->m_nTimesOfCombat) && g_RoleSystemCombat.dwInitParam != (HWND)2 )
    return 0;
  p_m_CmdData = 0;
  if ( (unsigned __int8)((CCBRoleState *)this->m_pRoleState)->GetForce(0) || *(_DWORD *)&this->m_eState != 2 )
  {
    m_pControl = this->m_pControl;
    if ( m_pControl->m_bActive )
      ((CCBControl *)m_pControl)->GetState();
    return 0;
  }
  if ( !this->m_pControl->m_bActive )
  {
    v3 = 24;
    m_Player = this->m_Player;
    v5 = 0;
    v17 = 0;
    v18 = 24;
    for ( i = this->m_Player; ; ++i )
    {
      if ( !this->m_pRoleState->m_Role[0].bMagicMastered[5][v17 + 4]
        || !((CCBStageRole *)*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + v3))->ForceDelTaskByPFN() )
      {
        goto LABEL_39;
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->ProcessCombatAction(v5) )
      {
        ((CCBAttackSequen *)this->m_pAttackSequen)->SetPause();
        return 0;
      }
      if ( ((CCBSystem *)this->m_pAttackSequen)->GetCmdType(v5) == 1
        && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v5) == 1
        && ((CCBRoleState *)this->m_pRoleState)->IsActive(v5) == 1
        && ((CCBSystem *)this->m_pAttackSequen)->IsBusy() )
      {
        if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 17)
          || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 14) )
        {
          goto LABEL_38;
        }
        if ( !BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(v5)[1].dwMagicID[1][0])
          && !((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 18)
          && !((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 19) )
        {
          ((CCBRoleState *)this->m_pRoleState)->ProcessCombatDialog(v5);
          if ( !BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(v5)[1].dwMagicID[2][4])
            || (v6 = ((CCBAI *)this->m_pAI)->HandleFriendAffirmative(v5, 1),
                BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(v5)[1].dwMagicID[2][4]) = 0,
                !v6) )
          {
            if ( !LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(v5)[1].dwMagicID[2][4]) )
            {
              nVal3 = v5;
              ((CCBSystem *)this->m_pControl)->StartRoleThread(v5);
              return 0;
            }
            if ( m_Player->LastRoleCmd.bValid )
            {
              ((CCBAI *)this->m_pAI)->HandlePlayerNormalAttack(v5, (int)m_Player);
              for ( j = 0; j < 5; ++j )
              {
                inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(j);
                LOBYTE(inited[1].dwMagicID[2][4]) = 0;
              }
            }
            else
            {
              ((CCBAI *)this->m_pAI)->HandleFriendAffirmative(v5, 0);
              for ( k = 0; k < 5; ++k )
              {
                v10 = ((CCBRoleState *)this->m_pRoleState)->InitUI(k);
                LOBYTE(v10[1].dwMagicID[2][4]) = 0;
              }
            }
          }
          goto LABEL_39;
        }
        ((CCBRoleState *)this->m_pRoleState)->ProcessCombatDialog(v5);
        ((CCBAI *)this->m_pAI)->HandleEnemyChaos(v5);
      }
      if ( ((CCBSystem *)this->m_pAttackSequen)->GetCmdType(v5) != 1
        || ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v5) != 1
        || ((CCBRoleState *)this->m_pRoleState)->IsActive(v5)
        || !((CCBSystem *)this->m_pAttackSequen)->IsBusy() )
      {
        goto LABEL_39;
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 17)
        || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 14)
        || HIBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(v5)[1].dwMagicID[2][4]) )
      {
LABEL_38:
        ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(v5);
        goto LABEL_39;
      }
      ((CCBAI *)this->m_pAI)->Render(v5);
LABEL_39:
      v3 = v18 + 4;
      v17 += 892;
      ++v5;
      m_Player = i + 1;
      v11 = v18 + 4 < 68;
      v18 += 4;
      if ( !v11 )
        return 0;
    }
  }
  ((CCBAttackSequen *)this->m_pAttackSequen)->SetPause();
  v13 = this->m_pControl;
  if ( v13->m_CmdData.bValid )
    p_m_CmdData = (int *)&v13->m_CmdData;
  Control = ((CCBControl *)v13)->GetControl();
  if ( BYTE1(((CCBRoleState *)this->m_pRoleState)->InitUI(Control)[1].dwMagicID[2][4])
    || (v15 = ((CCBControl *)this->m_pControl)->GetControl(),
        LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(v15)[1].dwMagicID[2][4])) )
  {
    nVal3 = -1;
    ((CCBAttackSequen *)this->m_pAttackSequen)->SetPause();
    ((CCBControl *)this->m_pControl)->GetState();
    return 0;
  }
  if ( ((CCBControl *)this->m_pControl)->GetControl() != nVal3 || !p_m_CmdData )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(nVal3, 14) )
  {
    ((CCBControl *)this->m_pControl)->GetState();
    return 0;
  }
  else
  {
    switch ( *p_m_CmdData )
    {
      case 259:
        this->CreateObj((int ( *)(int, int))CCBSystem::IsRoleWaitForFlee, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 260:
        this->CreateObj((int ( *)(int, int))CCBSystem::GetThreadIndex, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 261:
        this->CreateObj((int ( *)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 262:
        this->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 264:
      case 266:
      case 268:
        this->CreateObj((int ( *)(int, int))CCBSystem::AllocThread, 0, 0, 0, p_m_CmdData);
        break;
      case 265:
        this->CreateObj((int ( *)(int, int))CCBSystem::PassCmdViaThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 267:
        this->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 269:
        this->CreateObj((int ( *)(int, int))CCBSystem::DelThread, 0, 0, 0, p_m_CmdData);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      default:
        break;
    }
    ((CCBSystem *)this->m_pControl)->ResetConfig(p_m_CmdData[2]);
    nVal3 = -1;
    return 0;
  }
}

// 0x00513EB0
int CCBSystem::Message(char *a2, char *a3, int a4)
{
  int RoleIndex; // edi

  BYTE2(this->m_pFightInfo->nRoleWillNotBeAttack) = 0;
  RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(3, 0, 1);
  if ( RoleIndex != -1 )
  {
    if ( BYTE2(this->m_pRoleState->m_Role[0].dwMagicID[8][4])
      || (((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::IsSubTaskFinished */, 0, 0, 0, 0, -1082130432, 1082130432),
          ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::IsAllSubTaskFinished */, 0, 0, 0, 0, 0, 1082130432),
          BYTE1(this->m_pRoleState->m_Role[0].dwMagicID[8][4])) )
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::IsIdle */, 0, 0, 0, 0, 0, 1077936128);
    }
    ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
  }
  this->CreateObj((int (*)(int, int))CCBSystem::CheckBattleEnd, 0, 0, 0, 0);
  this->ClearEffect(this->m_nThread);
  return 0;
}

// 0x00513FD0
bool CCBSystem::IsRoleWaitForFlee(int nRoleIndex)
{
  int m_nThread; // eax
  tagThread *v4; // ebp
  tagCmdData *p_cmd; // edi
  char v6; // al
  int nSrcRole; // eax
  int RoleIndex; // eax
  int v9; // edi
  char p_BYTE; // [esp+0x13] [ebp-0x15] BYREF
  int pnVal; // [esp+0x14] [ebp-0x14] BYREF
  int v13; // [esp+0x18] [ebp-0x10] BYREF
  int p_DWORD; // [esp+0x1C] [ebp-0xC] BYREF
  int v15; // [esp+0x20] [ebp-0x8]
  int nDestRole; // [esp+0x24] [ebp-0x4]

  m_nThread = this->m_nThread;
  p_BYTE = 0;
  v13 = 0;
  v4 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    p_cmd = &this->m_Thread[m_nThread].cmd;
    if ( !((CCBRoleState *)this->m_pRoleState)->SumGPCost((int)p_cmd) )
    {
LABEL_11:
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
      goto LABEL_12;
    }
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 1);
    ((CCBRoleState *)this->m_pRoleState)->CheckVarianceRound(v4->cmd.nSrcRole, 0, &pnVal);
    if ( v6 == 1 )
    {
      nSrcRole = v4->cmd.nSrcRole;
      p_cmd->dwCmdKind = 270;
      v4->cmd.dwItemID = pnVal;
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(nSrcRole);
      this->CreateObj((int ( *)(int, int))CCBSystem::AddThread, 0, 0, 0, &v4->cmd);
LABEL_12:
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(11, &v4->cmd, 0);
    v9 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    if ( RoleIndex != -1 )
    {
      p_DWORD = 0;
      v15 = 0;
      nDestRole = 0;
      v15 = v4->cmd.nSrcRole;
      nDestRole = v4->cmd.nDestRole;
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::ProcShowSneakAttackState */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::HandleKeyCtrl */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::ProcShowName */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v9);
    }
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(v4->nTaskIndex, &p_BYTE, &v13);
  if ( p_BYTE == 1 )
  {
    if ( v4->nTaskIndex != -1 )
      ((CCBStage *)this->m_pStage)->GetStageRole(v4->nTaskIndex);
    goto LABEL_11;
  }
  return 0;
}

// 0x00514220
unsigned int CCBSystem::AddThread(int fp)
{
  int m_nThread; // eax
  tagThread *v4; // ebp
  int RoleIndex; // eax
  int v6; // edi
  char p_BYTE; // [esp+0x13] [ebp-0x11] BYREF
  int v9; // [esp+0x14] [ebp-0x10] BYREF
  int p_DWORD; // [esp+0x18] [ebp-0xC] BYREF
  int nSrcRole; // [esp+0x1C] [ebp-0x8]
  int nDestRole; // [esp+0x20] [ebp-0x4]

  m_nThread = this->m_nThread;
  p_BYTE = 0;
  v9 = 0;
  v4 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    ((CCBAttackSequen *)this->m_pAttackSequen)->SetPause();
    ((CCBRoleState *)this->m_pRoleState)->InitRoleFiveMagic((int)&v4->cmd);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(12, &v4->cmd, 0);
    v6 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    if ( RoleIndex == -1 )
    {
      v4->bExecuted = 1;
      ((CCBAttackSequen *)this->m_pAttackSequen)->SetPause();
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    p_DWORD = 0;
    nSrcRole = 0;
    nDestRole = 0;
    nSrcRole = v4->cmd.nSrcRole;
    nDestRole = v4->cmd.nDestRole;
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    p_DWORD = -1;
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBRoleState::Func */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    p_DWORD = 0;
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBCamControl::ProcessCamMove */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBStage::ProcShowDamage */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    p_DWORD = -1;
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBRoleState::CalcTurnDelay */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    p_DWORD = 0;
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBStage::ClearRoleAllTask */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBStage::ProcTaskSlot */, 0, 0, 0, &p_DWORD, 0, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBStage::ProcShowCost */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBStage::ProcTaskSlot */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBRoleState::Func */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBStage::ProcShowCombatDialog */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBRoleState::CalcTurnDelay */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v6);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(v4->nTaskIndex, &p_BYTE, &v9);
  if ( p_BYTE == 1 )
  {
    if ( v4->nTaskIndex != -1 )
      ((CCBStage *)this->m_pStage)->GetStageRole(v4->nTaskIndex);
    ((CCBAttackSequen *)this->m_pAttackSequen)->SetPause();
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514610
bool CCBSystem::DelThread(int nIndex)
{
  int m_nThread; // eax
  tagThread *v4; // ebp
  unsigned int v5; // ecx
  int RoleIndex; // eax
  int v7; // edi
  char p_BYTE; // [esp+0x13] [ebp-0x11] BYREF
  int v10; // [esp+0x14] [ebp-0x10] BYREF
  int p_DWORD; // [esp+0x18] [ebp-0xC] BYREF
  int nSrcRole; // [esp+0x1C] [ebp-0x8]
  int nDestRole; // [esp+0x20] [ebp-0x4]

  m_nThread = this->m_nThread;
  p_BYTE = 0;
  v10 = 0;
  v4 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    v4->cmd.bValid = 1;
    v4->cmd.nSrcRole = 0;
    v4->cmd.dwCmdKind = 269;
    v5 = *(_DWORD *)&((CCBRoleState *)this->m_pRoleState)->InitUI(0)->byMagicUseTime[3][5];
    v4->cmd.nDestRole = -1;
    v4->cmd.dwItemID = v5;
    ((CCBRoleState *)this->m_pRoleState)->GetRoleNum((int *)&v4->cmd);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(11, &v4->cmd, 0);
    v7 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    if ( RoleIndex != -1 )
    {
      p_DWORD = 0;
      nSrcRole = 0;
      nDestRole = 0;
      nSrcRole = v4->cmd.nSrcRole;
      nDestRole = v4->cmd.nDestRole;
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStage::ClearRoleAllTask */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStageRole::TaskResetToIdle */, 0, 0, 0, &p_DWORD, 0, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStageRole::TaskExecMagicEffect */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBSystem::EndBattle */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v7);
    }
    *(_DWORD *)&((CCBRoleState *)this->m_pRoleState)->InitUI(v4->cmd.nSrcRole)->byMagicUseTime[4][3] = 0;
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(v4->nTaskIndex, &p_BYTE, &v10);
  if ( p_BYTE == 1 )
  {
    if ( v4->nTaskIndex != -1 )
      ((CCBStage *)this->m_pStage)->GetStageRole(v4->nTaskIndex);
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514870
int CCBSystem::GetSameThreadNum(int fp)
{
  int m_nThread; // eax
  tagThread *v4; // edi
  char v5; // al
  CCBControl *m_pControl; // ecx
  int nSrcRole; // [esp-0x4] [ebp-0x14]
  int pnVal; // [esp+0xC] [ebp-0x4] BYREF

  pnVal = 0;
  m_nThread = this->m_nThread;
  v4 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBRoleState *)this->m_pRoleState)->CheckVarianceRound(this->m_Thread[m_nThread].cmd.nSrcRole, this->m_Thread[m_nThread].cmd.dwItemID, &pnVal);
    if ( v5 == 1 )
    {
      nSrcRole = v4->cmd.nSrcRole;
      v4->cmd.dwCmdKind = 270;
      v4->cmd.dwItemID = pnVal;
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(nSrcRole);
      this->CreateObj((int ( *)(int, int))CCBSystem::AddThread, 0, 0, 0, &v4->cmd);
LABEL_16:
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
    if ( !((CCBSystem *)this->m_pAttackSequen)->IsBusy() )
    {
      this->ClearEffect(this->m_nThread);
      return -1;
    }
    ((CCBSystem *)this->m_pAttackSequen)->ClearCmdSlot(v4->cmd.nSrcRole);
    if ( ((CCBRoleState *)this->m_pRoleState)->GetSkillCostLevel(v4->cmd.nSrcRole, v4->cmd.dwItemID) >= 4 )
    {
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(v4->cmd.nSrcRole);
    }
    else
    {
      ((CCBSystem *)this->m_pAttackSequen)->CalcSpeed(v4->cmd.nSrcRole, 1);
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdCount(v4->cmd.nSrcRole);
    }
    ((CCBStageRole *)this->m_pStage->m_pRole[v4->cmd.nSrcRole])->DelTask(4);
    v4->bExecuted = 1;
  }
  if ( (unsigned __int8)((CCBRoleState *)this->m_pRoleState)->GetForce(0) )
  {
LABEL_12:
    ((CCBStageRole *)this->m_pStage->m_pRole[v4->cmd.nSrcRole])->DelTask(2);
    this->ClearEffect(this->m_nThread);
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v4->cmd.nSrcRole, 15) )
  {
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(v4->cmd.nSrcRole);
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
    goto LABEL_12;
  }
  if ( ((CCBSystem *)this->m_pAttackSequen)->IsCmdReady(v4->cmd.nSrcRole) )
  {
    ((CCBStageRole *)this->m_pStage->m_pRole[v4->cmd.nSrcRole])->DelTask(2);
    this->CreateObj((int ( *)(int, int))CCBSystem::IsThreadExist, 0, 0, 0, &v4->cmd);
    goto LABEL_16;
  }
  if ( !((CCBSystem *)this->m_pAttackSequen)->IsCmdEmpty(v4->cmd.nSrcRole) )
    return 0;
  m_pControl = this->m_pControl;
  if ( m_pControl->m_bActive )
  {
    if ( ((CCBControl *)m_pControl)->GetControl() == v4->cmd.nSrcRole )
      ((CCBControl *)this->m_pControl)->GetState();
  }
  ((CCBStageRole *)this->m_pStage->m_pRole[v4->cmd.nSrcRole])->DelTask(2);
  this->ClearEffect(this->m_nThread);
  return -1;
}

// 0x00514AE0
bool CCBSystem::IsThreadExist(unsigned int dwThreadID)
{
  int m_nThread; // eax
  tagThread *v4; // ebp
  int RoleIndex; // eax
  int dwItemID; // edx
  int v7; // edi
  void *v8; // eax
  char p_BYTE; // [esp+0x13] [ebp-0x11] BYREF
  int v11; // [esp+0x14] [ebp-0x10] BYREF
  int p_DWORD[3]; // [esp+0x18] [ebp-0xC] BYREF

  m_nThread = this->m_nThread;
  p_BYTE = 0;
  v11 = 0;
  v4 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(14, &v4->cmd, 0);
    dwItemID = v4->cmd.dwItemID;
    v7 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    p_DWORD[0] = dwItemID;
    p_DWORD[1] = v4->cmd.nSrcRole;
    p_DWORD[2] = v4->cmd.nDestRole;
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, p_DWORD, -1082130432, 0);
    if ( v4->cmd.nSrcRole > 4u )
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStage::ClearRoleAllTask */, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
      v8 = CCBStage::IsAllSubTaskFinished;
    }
    else
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStage::ClearRoleAllTask */, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
      v8 = CCBStage::IsSubTaskFinished;
    }
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)v8, 0, 0, 0, p_DWORD, 0, 0x40000000);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBSystem::EndBattle */, 0, 0, 0, p_DWORD, 0, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStageRole::TaskExecSkill */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStageRole::TaskWaitIdle */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v7);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(v4->nTaskIndex, &p_BYTE, &v11);
  if ( p_BYTE == 1 )
  {
    if ( v4->nTaskIndex != -1 )
      ((CCBStage *)this->m_pStage)->GetStageRole(v4->nTaskIndex);
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514D60
int CCBSystem::GetThreadIndex(unsigned int dwThreadID)
{
  int m_nThread; // eax
  tagThread *v4; // ebp
  char v5; // al
  int RoleIndex; // eax
  int dwItemID; // edx
  int v9; // edi
  int nSrcRole; // [esp-0x4] [ebp-0x2C]
  char p_BYTE; // [esp+0x13] [ebp-0x15] BYREF
  int pnVal; // [esp+0x14] [ebp-0x14] BYREF
  int v13; // [esp+0x18] [ebp-0x10] BYREF
  int p_DWORD[3]; // [esp+0x1C] [ebp-0xC] BYREF

  m_nThread = this->m_nThread;
  p_BYTE = 0;
  v13 = 0;
  pnVal = 0;
  v4 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    ((CCBRoleState *)this->m_pRoleState)->CheckVarianceRound(v4->cmd.nSrcRole, v4->cmd.dwItemID, &pnVal);
    if ( v5 == 1 )
    {
      nSrcRole = v4->cmd.nSrcRole;
      v4->cmd.dwCmdKind = 270;
      v4->cmd.dwItemID = pnVal;
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(nSrcRole);
      this->CreateObj((int ( *)(int, int))CCBSystem::AddThread, 0, 0, 0, &v4->cmd);
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(16, &v4->cmd, 0);
    dwItemID = v4->cmd.dwItemID;
    v9 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    p_DWORD[0] = dwItemID;
    p_DWORD[1] = v4->cmd.nSrcRole;
    p_DWORD[2] = v4->cmd.nDestRole;
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::ClearRoleAllTask */, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
    ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::ProcGrabStageRole */, 0, 0, 0, p_DWORD, 1028443341, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStageRole::TaskExecAttack */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStageRole::TaskExecCommand */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v9);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(v4->nTaskIndex, &p_BYTE, &v13);
  if ( p_BYTE == 1 )
  {
    ((CCBStage *)this->m_pStage)->GetStageRole(v4->nTaskIndex);
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514FE0
int CCBSystem::PassCmdToThread(int a_34)
{
  int m_nThread; // eax
  tagThread *v4; // edi
  int RoleIndex; // eax
  int dwItemID; // ecx
  int v7; // ebp
  int SkillNum; // eax
  CCBRoleState *m_pRoleState; // ecx
  char p_BYTE; // [esp+0x13] [ebp-0x1D] BYREF
  int v12; // [esp+0x14] [ebp-0x1C] BYREF
  int p_DWORD[3]; // [esp+0x18] [ebp-0x18] BYREF
  unsigned int v14; // [esp+0x24] [ebp-0xC] BYREF
  int v15; // [esp+0x28] [ebp-0x8]
  int v16; // [esp+0x2C] [ebp-0x4]

  v12 = 0;
  m_nThread = this->m_nThread;
  p_BYTE = 0;
  v4 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(17, &v4->cmd, 0);
    dwItemID = v4->cmd.dwItemID;
    v7 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    p_DWORD[0] = dwItemID;
    p_DWORD[1] = v4->cmd.nSrcRole;
    p_DWORD[2] = v4->cmd.nDestRole;
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStage::EndRoleAllTask */, 0, 0, 0, p_DWORD, -1082130432, 1069547520);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStageRole::TaskExecItem */, 0, 0, 0, p_DWORD, 0, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStageRole::TaskForceEnd */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v7);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v4->cmd.nSrcRole);
    v15 = 0;
    v16 = 0;
    v14 = v4->cmd.dwItemID;
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v14);
    m_pRoleState = this->m_pRoleState;
    v16 = SkillNum;
    v15 = 1;
    if ( ((CCBSystem *)m_pRoleState)->IsMagicSlotMsg((int)&v4->cmd) )
      ((CCBSystem *)this->m_pRoleState)->HandleMagicSlotInput((int)&v4->cmd);
    else
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v14);
    v4->bExecuted = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(v4->nTaskIndex, &p_BYTE, &v12);
  if ( p_BYTE == 1 )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v4->cmd.nSrcRole, 0);
    ((CCBStage *)this->m_pStage)->GetStageRole(v4->nTaskIndex);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00515200
int CCBSystem::PassCmdToThread(int a2, int a3)
{
  int m_nThread; // eax
  tagThread *v5; // ebp
  int RoleIndex; // eax
  int dwItemID; // edx
  int v9; // edi
  unsigned int v10; // eax
  int nSrcRole; // edx
  CCBStage *m_pStage; // ecx
  int v13; // edi
  char p_BYTE; // [esp+0x13] [ebp-0x49] BYREF
  int v15; // [esp+0x14] [ebp-0x48] BYREF
  int p_DWORD[3]; // [esp+0x18] [ebp-0x44] BYREF
  int v17[3]; // [esp+0x24] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x30] [ebp-0x2C] BYREF

  p_BYTE = 0;
  m_nThread = this->m_nThread;
  v5 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    if ( !((CCBSystem *)this->m_pAttackSequen)->IsBusy() && !this->m_pRoleState->m_Role[0].bMagicMastered[1][0] )
    {
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v5->cmd.nSrcRole, 0);
LABEL_5:
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    ((CCBSystem *)this->m_pAttackSequen)->ClearCmdSlot(v5->cmd.nSrcRole);
    ((CCBRoleState *)this->m_pRoleState)->GetSpeedBonus(v5->cmd.nSrcRole);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdCount(v5->cmd.nSrcRole);
    if ( this->m_pRoleState->m_Role[0].bMagicMastered[1][0] )
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(v5->cmd.nSrcRole);
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v5->cmd.nSrcRole, 0);
    v5->bExecuted = 1;
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(20, &v5->cmd, 0);
    dwItemID = v5->cmd.dwItemID;
    v9 = RoleIndex;
    v5->nTaskIndex = RoleIndex;
    p_DWORD[0] = dwItemID;
    p_DWORD[1] = v5->cmd.nSrcRole;
    p_DWORD[2] = v5->cmd.nDestRole;
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStageRole::TaskExecAction */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v9);
    ((CCBRoleState *)this->m_pRoleState)->InitUI(v5->cmd.nSrcRole)->bWaitForFlee = 1;
  }
  if ( (unsigned __int8)((CCBRoleState *)this->m_pRoleState)->GetForce(0)
    && (((CCBStage *)this->m_pStage)->DelTask(v5->nTaskIndex, &p_BYTE, &v15), p_BYTE) )
  {
    ((CCBStage *)this->m_pStage)->GetStageRole(v5->nTaskIndex);
    ((CCBRoleState *)this->m_pRoleState)->InitUI(v5->cmd.nSrcRole)->bWaitForFlee = 0;
    this->ClearEffect(this->m_nThread);
    return 0;
  }
  else
  {
    if ( ((CCBSystem *)this->m_pAttackSequen)->IsCmdReady(v5->cmd.nSrcRole)
      || this->m_pRoleState->m_Role[0].bMagicMastered[1][0] )
    {
      ((CCBStage *)this->m_pStage)->DelTask(v5->nTaskIndex, &p_BYTE, &v15);
      if ( p_BYTE )
      {
        ((CCBStage *)this->m_pStage)->GetStageRole(v5->nTaskIndex);
        this->CreateObj((int (*)(int, int))CCBSystem::PassCmdToTask, 0, 0, 0, &v5->cmd);
        goto LABEL_5;
      }
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5->cmd.nSrcRole, 16)
      && !this->m_pRoleState->m_Role[0].bMagicMastered[1][0] )
    {
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(v5->cmd.nSrcRole);
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v5->cmd.nSrcRole, 0);
    }
    if ( !((CCBSystem *)this->m_pAttackSequen)->IsCmdEmpty(v5->cmd.nSrcRole) )
      return 0;
    ((CCBStage *)this->m_pStage)->DelTask(v5->nTaskIndex, &p_BYTE, &v15);
    if ( !p_BYTE )
      return 0;
    ((CCBStage *)this->m_pStage)->GetStageRole(v5->nTaskIndex);
    ((CCBRoleState *)this->m_pRoleState)->InitUI(v5->cmd.nSrcRole)->bWaitForFlee = 0;
    memset(pData, 0, sizeof(pData));
    LOBYTE(pData[10]) = 1;
    pData[0] = 267;
    v10 = this->ProcProtect();
    nSrcRole = v5->cmd.nSrcRole;
    m_pStage = this->m_pStage;
    pData[1] = v10;
    pData[2] = nSrcRole;
    pData[3] = -1;
    v13 = ((CCBStage *)m_pStage)->GetRoleIndex(26, pData, 1);
    if ( v13 != -1 )
    {
      memset(v17, 0, sizeof(v17));
      ((CCBStage *)this->m_pStage)->GetRoleName(v13, 0 /* TODO: (int)CCBStage::ProcessRoleEffect */, 0, 0, 0, v17, 0, 1077936128);
      ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v13);
    }
    this->ClearEffect(this->m_nThread);
    return -1;
  }
}

// 0x005155D0
int CCBSystem::PassCmdToTask(int a2, int a3)
{
  int m_nThread; // eax
  tagThread *v5; // esi
  int RoleIndex; // eax
  int dwItemID; // edx
  int v8; // ebp
  C2DSpark *m_p2DSpark; // ecx
  char p_BYTE; // [esp+0x13] [ebp-0x11] BYREF
  int v12; // [esp+0x14] [ebp-0x10] BYREF
  int p_DWORD[3]; // [esp+0x18] [ebp-0xC] BYREF

  p_BYTE = 0;
  v12 = 0;
  m_nThread = this->m_nThread;
  v5 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(20, &v5->cmd, 0);
    dwItemID = v5->cmd.dwItemID;
    v8 = RoleIndex;
    v5->nTaskIndex = RoleIndex;
    p_DWORD[0] = dwItemID;
    p_DWORD[1] = v5->cmd.nSrcRole;
    p_DWORD[2] = v5->cmd.nDestRole;
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, 0 /* TODO: (int)CCBStageRole::TaskResolveAction */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(v8);
    v5->bExecuted = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(v5->nTaskIndex, &p_BYTE, &v12);
  if ( p_BYTE == 1 )
  {
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v5->cmd.nSrcRole);
    ((CCBStage *)this->m_pStage)->GetStageRole(v5->nTaskIndex);
    if ( v12 )
    {
      m_p2DSpark = this->m_p2DSpark;
      *(_DWORD *)&this->m_eState = 4;
      ((C2DSpark *)m_p2DSpark)->CreateStars();
    }
    else
    {
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(v5->cmd.nSrcRole, 0);
    }
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00515760
int CCBSystem::PassCmdViaThread(int a2, int a3)
{
  int m_nThread; // eax
  tagThread *v5; // esi
  int RoleIndex; // ebx
  int nSrcRole; // ecx
  int p_DWORD[3]; // [esp+0x10] [ebp-0xC] BYREF

  m_nThread = this->m_nThread;
  v5 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 0);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v5->cmd.nSrcRole);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(19, &v5->cmd, 1);
    p_DWORD[2] = v5->cmd.nDestRole;
    v5->nTaskIndex = RoleIndex;
    nSrcRole = v5->cmd.nSrcRole;
    p_DWORD[0] = v5->cmd.dwItemID;
    p_DWORD[1] = nSrcRole;
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStageRole::TaskEnterGuard */, 0, 0, 0, p_DWORD, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, p_DWORD, -1082130432, 0);
    v5->nTemp = ((CCBRoleState *)this->m_pRoleState)->InitUI(v5->cmd.nSrcRole)[1].dwMagicID[2][3];
    ((CCBStage *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
    v5->bExecuted = 1;
  }
  if ( ((CCBSystem *)this->m_pAttackSequen)->IsBusy()
    || *(_DWORD *)&this->m_eState != 2
    || (int)((CCBRoleState *)this->m_pRoleState)->InitUI(v5->cmd.nSrcRole)[1].dwMagicID[2][3] > v5->nTemp )
  {
    ((CCBRoleState *)this->m_pRoleState)->SetRoleFlag(v5->cmd.nSrcRole, 0);
    this->ClearEffect(this->m_nThread);
    v5->nTemp = 0;
  }
  return 0;
}

// 0x005158F0
int CCBSystem::AllocThread(int nVal)
{
  int m_nThread; // eax
  tagThread *v4; // edi

  m_nThread = this->m_nThread;
  v4 = &this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(this->m_Thread[m_nThread].cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  this->ClearEffect(this->m_nThread);
  return 0;
}

// 0x00515940
int CCBSystem::CreateObj(int nVal)
{
  int m_nThread; // eax
  tagThread *v4; // edi
  BOOL Obj; // edi

  m_nThread = this->m_nThread;
  v4 = &this->m_Thread[m_nThread];
  if ( this->m_Thread[m_nThread].bExecuted )
  {
    Obj = this->CreateObj(0, 0, 0x40u);
    this->ClearEffect(this->m_nThread);
    return Obj;
  }
  else
  {
    this->ProcAI(0.0);
    v4->bExecuted = 1;
    return 0;
  }
}

// 0x005159A0
BOOL CCBSystem::CreateObj(CCBUI **ppUI, const char *szName, UINT nFlags)
{
  unsigned int v5; // eax
  CHAR *v6; // edi
  CCBUI **v7; // esi
  char v8; // cl
  unsigned int v9; // edx

  if ( !ppUI )
    return MessageBoxA(hWnd, byte_17AC6DC, (LPCSTR)&g_bCBFlag, uType);
  if ( strlen((const char *)ppUI) >= 0xFF )
  {
    v9 = strlen("Too many character in calling Message") + 1;
    qmemcpy(byte_17AC6DC, "Too many character in calling Message", 4 * (v9 >> 2));
    v7 = (CCBUI **)&aTooManyCharact[4 * (v9 >> 2)];
    v6 = &byte_17AC6DC[4 * (v9 >> 2)];
    v8 = v9;
  }
  else
  {
    v5 = strlen((const char *)ppUI) + 1;
    qmemcpy(byte_17AC6DC, ppUI, 4 * (v5 >> 2));
    v7 = &ppUI[v5 >> 2];
    v6 = &byte_17AC6DC[4 * (v5 >> 2)];
    v8 = v5;
  }
  qmemcpy(v6, v7, v8 & 3);
  if ( szName )
  {
    if ( strlen(szName) < 0xFF )
      strcpy((char *)&g_bCBFlag, szName);
  }
  else
  {
    sprintf((char *const)&g_bCBFlag, "%s", "PAL3 COMBAT SYSTEM 1.03");
  }
  uType = nFlags;
  this->CreateObj((int ( *)(int, int))CCBSystem::CreateObj, 0, 0, 0, 0);
  return 0;
}

// 0x00515AC0
char CCBSystem::CreateObj(CCBRoleState **a2)
{
  int v2; // edx
  tagThread *i; // eax

  v2 = 0;
  for ( i = this->m_Thread;
        !i->bValid
     || (int (*)@<eax>(CCBSystem *@<ecx>, int, int))i->fp[0] != CCBSystem::PassCmdToThread
     || i->fp[0] && (i->fp[1] || i->fp[2] || i->fp[3])
     || (CCBRoleState **)i->cmd.nSrcRole != a2;
        ++i )
  {
    if ( ++v2 >= 1024 )
      return 0;
  }
  return 1;
}

// 0x00515B20
int CCBSystem::CreateObj(
        
        int ( *a2)(int this, int a2),
        int nVal,
        int nVal2,
        int nVal3,
        const void *pData)
{
  int v8; // eax
  _BYTE *i; // ecx
  char *v10; // ebp

  if ( (int)this->m_dwIDHolder >= 1023 )
    MessageBoxA(0, &unk_5DE9E4, 0, 0x30u);
  if ( (char *)a2 == (char *)CCBSystem::CheckBattleEnd
    && (!CCBSystem::CheckBattleEnd || !nVal && !nVal2 && !nVal3)
    && (int)sub_515C90(CCBSystem::CheckBattleEnd, 0, 0, 0) > 0 )
  {
    return 0;
  }
  v8 = 0;
  for ( i = &this->m_Thread[0].bValid; *i; i += 88 )
  {
    if ( ++v8 >= 1024 )
      return -1;
  }
  v10 = (char *)this + 88 * v8;
  v10[188] = 1;
  v10[189] = 0;
  *((_DWORD *)v10 + 38) = a2;
  *((_DWORD *)v10 + 39) = nVal;
  *((_DWORD *)v10 + 40) = nVal2;
  *((_DWORD *)v10 + 41) = nVal3;
  *((_DWORD *)v10 + 42) = this->ProcProtect();
  *((_DWORD *)v10 + 45) = 0;
  *((_DWORD *)v10 + 43) = -1;
  if ( pData )
    qmemcpy(v10 + 192, pData, 0x2Cu);
  ++this->m_dwIDHolder;
  return *((_DWORD *)v10 + 42);
}

// 0x00515C50
char CCBSystem::ClearEffect(int idx)
{
  memset(&this->m_Thread[idx], 0, sizeof(this->m_Thread[idx]));
  --this->m_dwIDHolder;
  return 1;
}

// 0x00515D10
bool CCBSystem::CreateObj(CCBEditor **a2)
{
  CCBStage *v3; // eax
  int *v4; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x408] [ebp-0x40C] BYREF
  int v8; // [esp+0x810] [ebp-0x4]

  v3 = (CCBStage *)operator new(0x2598u);
  v8 = 0;
  if ( v3 )
    v4 = ((CCBStage *)v3)->ResetAndSetSystem((int)this);
  else
    v4 = 0;
  v8 = -1;
  *a2 = (CCBEditor *)v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], aDProjectPal3Co_8, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return ((CCBStage *)v4)->SyncTimeScale() != 0;
}

// 0x00515DD0
void * CCBSystem::DestroyObj(CCBSystem *Block, char pData)
{
  void *v5; // [esp+0x0] [ebp-0x4]

  todo_408BD0(v5);
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00515DF0
void * CCBSystem::DestroyObj_5df0(CCBSystem *Block, char pData)
{
  ((CCBStage *)this)->Reset();
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00515E50
BOOL CCBSystem::DestroyObj()
{
  g_nCBCamState[0] = 1094713344;
  return 1094713344;
}

// 0x00515E70
void CCBSystem::DestroyObj_5e70()
{
  g_fCBCamParam = 12.0 + 12.0;
}

// 0x00515E90
bool CCBSystem::InitObj()
{
  g_nCBCamState[2] = g_nStatePanelL_dup[0] + 119;
  g_nCBCamState[3] = g_nStatePanelL_dup[1] + 107;
  g_nCBCamState[4] = g_nStatePanelL_dup[2] + 107;
  g_nCBCamState[5] = g_nStatePanelL_dup[3] + 107;
  return LOBYTE(g_nStatePanelL_dup[3]) + 107;
}

// 0x00515EE0
int CCBSystem::InitObj_5ee0()
{
  g_nCBCamState[6] = g_nStatePanelT_dup[0] + 28;
  g_nCBCamState[7] = g_nStatePanelT_dup[1] + 28;
  g_nCBCamState[8] = g_nStatePanelT_dup[2] + 28;
  g_nCBCamState[9] = g_nStatePanelT_dup[3] + 28;
  return g_nStatePanelT_dup[3] + 28;
}

// 0x00515F30
int CCBSystem::InitObj_5f30()
{
  g_nCBCamState[10] = g_nStatePanelL_dup[0] + 128;
  g_nCBCamState[11] = g_nStatePanelL_dup[1] + 116;
  g_nCBCamState[12] = g_nStatePanelL_dup[2] + 116;
  g_nCBCamState[13] = g_nStatePanelL_dup[3] + 116;
  return g_nStatePanelL_dup[3] + 116;
}

// 0x00515F80
int CCBSystem::InitObj_5f80()
{
  g_nCBCamState[14] = g_nStatePanelT_dup[0] + 54;
  g_nCBCamState[15] = g_nStatePanelT_dup[1] + 54;
  g_nCBCamState[16] = g_nStatePanelT_dup[2] + 54;
  g_nCBCamState[17] = g_nStatePanelT_dup[3] + 54;
  return g_nStatePanelT_dup[3] + 54;
}

// 0x00515FD0
int CCBSystem::InitObj_5fd0()
{
  g_nCBCamState[18] = g_nStatePanelL_dup[0] + 121;
  g_nCBCamState[19] = g_nStatePanelL_dup[1] + 109;
  g_nCBCamState[20] = g_nStatePanelL_dup[2] + 109;
  g_nCBCamState[21] = g_nStatePanelL_dup[3] + 109;
  return g_nStatePanelL_dup[3] + 109;
}
