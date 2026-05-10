#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBSystem.h"
#include "pal3/gen/C2DSpark.h"
#include "pal3/gen/C3DSpark.h"
#include "pal3/gen/CCBAI.h"
#include "pal3/gen/CCBAttackSequen.h"
#include "pal3/gen/CCBControl.h"
#include "pal3/gen/CCBLineupWindow.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/CCBStage.h"
#include "pal3/gen/CCBStageCam.h"
#include "pal3/gen/CCBStageRole.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int SceneMgrUpdate(...);
int sub_4C6170(...);
int sub_4CDB60(...);
int sub_4CEA80(...);
int sub_4DB730(...);
int sub_4DB9F0(...);
int sub_4DBB80(...);
int sub_4DC220(...);
int sub_4DC3F0(...);
int sub_4DC510(...);
int sub_4E02F0(...);
int sub_4E0380(...);
int sub_4E0430(...);
int sub_4EC830(...);
int sub_4ECB20(...);
int sub_4F7FC0(...);
int sub_5158F0(...);
int sub_53E970(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Co_4[];
extern int dword_17A990C;
extern int dword_5DC3DC;

// 0x004DB3A0
// attributes: thunk
int CCBSystem::InitCmdTable1_thunk()
{
  return CCBSystem::InitCmdTable1();
}

// 0x004DB3B0
int CCBSystem::InitCmdTable1()
{
  *(_DWORD *)&Buffer[956] = 545;
  *(_DWORD *)&Buffer[960] = 545;
  *(_DWORD *)&Buffer[964] = 545;
  *(_DWORD *)&Buffer[968] = 545;
  return 545;
}

// 0x004DB3F0
// attributes: thunk
int CCBSystem::InitCmdTable2_thunk()
{
  return CCBSystem::InitCmdTable2();
}

// 0x004DB400
int CCBSystem::InitCmdTable2()
{
  *(_DWORD *)&Buffer[972] = 121;
  *(_DWORD *)&Buffer[976] = 316;
  *(_DWORD *)&Buffer[980] = 512;
  *(_DWORD *)&Buffer[984] = 709;
  return 709;
}

// 0x004DB440
// attributes: thunk
int CCBSystem::InitCmdTable3_thunk()
{
  return CCBSystem::InitCmdTable3();
}

// 0x004DB450
int CCBSystem::InitCmdTable3()
{
  *(_DWORD *)&Buffer[988] = 573;
  *(_DWORD *)&Buffer[992] = 573;
  *(_DWORD *)&Buffer[996] = 573;
  *(_DWORD *)&Buffer[1000] = 573;
  return 573;
}

// 0x004DB490
void * CCBSystem::InitCmd(int a2)
{
  memset(this, 0, 0x1C8u);
  this->m_pUtil = (CCBSystem *)a2;
  this->m_pUI = *(CCBUI **)(a2 + 4);
  this->m_pControl = *(CCBControl **)(a2 + 16);
  return this;
}

// 0x004DB4C0
int CCBSystem::ResetFlags()
{
  LOBYTE(this->m_Thread[1].cmd.bDestRole[6]) = 1;
  BYTE1(this->m_Thread[1].cmd.bDestRole[6]) = 1;
  BYTE2(this->m_Thread[1].cmd.bDestRole[6]) = 1;
  memset(&this->m_pAttackSequen, 0, 0x1B8u);
  return 0;
}

// 0x004DB4F0
char CCBSystem::DestroySubsystems()
{
  void (***m_pData)(void *, _DWORD); // ecx
  int i; // esi
  void (***v5)(_DWORD, _DWORD); // ecx
  void (***v6)(void *, int); // ecx
  int v7; // ebx
  int j; // esi
  CCBSystem *m_pUtil; // eax

  this->ResetFlags();
  if ( !this->m_pUtil )
    return 0;
  if ( !this->m_pUI )
    return 0;
  if ( !this->m_pControl )
    return 0;
  sub_4DBB80(this);
  sub_4DB9F0(this);
  if ( dword_17A990C == 1 )
  {
    m_pData = (void (***)(void *, _DWORD))this->m_pUtil->m_pUI->m_childs.m_pData;
    (**m_pData)(m_pData, 0);
    for ( i = 76; i < 120; i += 4 )
    {
      v5 = *(void (****)(_DWORD, _DWORD))((char *)&this->m_pUtil->m_pUI->m_fontcolor.ColorQuadFmt + i);
      (**v5)(v5, 0);
    }
    return 1;
  }
  else
  {
    v6 = (void (***)(void *, int))this->m_pUtil->m_pUI->m_childs.m_pData;
    (**v6)(v6, 1);
    v7 = 0;
    for ( j = 76; j < 120; j += 4 )
    {
      m_pUtil = (CCBSystem *)this->m_pUtil;
      if ( this->m_pUtil->m_pRoleState->m_Role[v7].bValid )
        (***(void (****)(_DWORD, int))((char *)&m_pUtil->m_pUI->m_fontcolor.ColorQuadFmt + j))(
          *(int *)((char *)&m_pUtil->m_pUI->m_fontcolor.ColorQuadFmt + j),
          1);
      else
        (***(void (****)(_DWORD, _DWORD))((char *)&m_pUtil->m_pUI->m_fontcolor.ColorQuadFmt + j))(
          *(int *)((char *)&m_pUtil->m_pUI->m_fontcolor.ColorQuadFmt + j),
          0);
      ++v7;
    }
    return 1;
  }
}

// 0x004DB640
int CCBSystem::CalcSpeed(int roleIdx, int a2)
{
  int v2; // ecx

  return 5 * (((CCBRoleState *)*(CCBRoleState **)(v2 + 8))->GetSpeedBonus(roleIdx) + 4);
}

// 0x004DB660
int CCBSystem::GetCmdSlot(int idx)
{
  char *v2; // ebx
  int result; // eax

  v2 = (char *)this + 40 * idx;
  v2[44] = idx->CalcSpeed(0);
  result = idx->CalcSpeed(1);
  v2[45] = result;
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
  int v2; // [esp+4h] [ebp+4h]

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
char * CCBSystem::CCBSystem::sub_4DB730(int a2)
{
  char *result; // eax

  result = (char *)this + 40 * a2;
  *((_DWORD *)result + 8) = 0;
  result[46] = 1;
  return result;
}

// 0x004DB750
char * CCBSystem::GetCmdData(int idx)
{
  char *result; // eax
  int v3; // [esp+8h] [ebp+8h]
  int v4; // [esp+Ch] [ebp+Ch]
  char v5; // [esp+10h] [ebp+10h]

  result = (char *)this + 40 * idx;
  *((_DWORD *)result + 8) = v3;
  *((_DWORD *)result + 9) = v4;
  result[46] = v5;
  return result;
}

// 0x004DB780
int CCBSystem::GetCmdCount(int idx)
{
  char v3; // [esp+8h] [ebp+8h]

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
  CCBRoleState *v6; // ecx
  double v7; // st7
  float v9; // [esp+10h] [ebp-Ch]
  int v10; // [esp+14h] [ebp-8h]

  v2 = 0;
  v9 = 100000000.0;
  v10 = -1;
  v3 = 0;
  p_m_pEffectSimple = &this->m_pEffectSimple;
  do
  {
    m_pControl = (CCBControl *)this->m_pControl;
    if ( *((_BYTE *)&m_pControl->m_Thread[8].dwTaskID + v3 * 892 + 1) )
    {
      if ( !((CCBStageRole *)m_pControl)->IsActive(v2) )
      {
        v6 = (CCBRoleState *)this->m_pControl;
        if ( !v6->m_Role[v3].nSpecStateRound[40]
          && !*(_BYTE *)(v6->InitUI(v2) + 879)
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
    ++v3;
    ++v2;
    p_m_pEffectSimple += 10;
  }
  while ( v3 < 11 );
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

// 0x004DB910
double CCBSystem::GetDeltaTime()
{
  double result; // st7
  char v2; // [esp+4h] [ebp+4h]

  BYTE1(this->m_Thread[1].cmd.bDestRole[6]) = v2;
  return result;
}

// 0x004DB920
int CCBSystem::SetCmdParam(int idx, int value)
{
  *((_BYTE *)&this->m_pEffMgr + 40 * idx + 3) = value;
  return 5 * idx;
}

// 0x004DC5B0
int CCBSystem::GetControl()
{
  return (int)this->m_pES;
}

// 0x004FC8F0
char CCBSystem::GetStageRole(int idx)
{
  char *v2; // esi

  v2 = (char *)this + 2632 * idx;
  v2[2796] = 0;
  memset(v2 + 184, 0, 0xA00u);
  *((_DWORD *)v2 + 44) = 0;
  --this->m_bFirstRender;
  return 1;
}

// 0x004FC940
char CCBSystem::GetStageRoleByIdx(int idx)
{
  char *v2; // eax

  v2 = (char *)this + 2632 * idx;
  *((_DWORD *)v2 + 43) = 3;
  *((_DWORD *)v2 + 50) = 3;
  *((float *)v2 + 52) = this->m_pUtil->m_fTimeFund;
  return 1;
}

// 0x00500170
int CCBSystem::EndBattle()
{
  unsigned __int32 v2; // eax
  _DWORD *v3; // edi
  char *v4; // ebp
  int v5; // eax

  v2 = 2632 * this->m_dwIDHolder;
  v3 = (__int32 *)((char *)&this->m_Thread[17].dwID + v2);
  v4 = (char *)&this->m_Thread[0].dwTaskID + 80 * this->m_nThread + v2;
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *v3))->IsReady(this->m_Thread[16].cmd.bDestRole[v2 / 4 + 9]) )
    goto LABEL_7;
  if ( !v4[41] && ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *v3))->ForceDelTaskByPFN() )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *v3))->GetState();
    v5 = *((_DWORD *)&this->m_pAI + *v3);
    *(_DWORD *)(v5 + 6632) = *(_DWORD *)(v5 + 6636);
    v4[41] = 1;
  }
  if ( v4[43] == 1 || ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *v3))->ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v4 + 4) = 4;
  return 0;
}

// 0x00512500
CCBSystem::CCBSystem()
{
  int *p_nTemp; // esi
  int v2; // ebx
  int *v3; // edi
  __int32 *v4; // esi
  int v5; // ebx
  __int32 *v6; // edi

  p_nTemp = (int *)&this->m_Thread[0].nTemp;
  v2 = 1024;
  do
  {
    v3 = p_nTemp;
    p_nTemp += 22;
    --v2;
    memset(v3, 0, 0x2Cu);
  }
  while ( v2 );
  v4 = (__int32 *)&this->m_Thread[592].cmd.bDestRole[1];
  v5 = 11;
  do
  {
    v6 = v4;
    v4 += 13;
    --v5;
    memset(v6, 0, 0x2Cu);
  }
  while ( v5 );
  memset(this, 0, 0x162D8u);
  this->m_eState = 0;
  LOBYTE(this->m_bFiveNimbus) = 0;
  BYTE1(this->m_bFiveNimbus) = 0;
  this->m_eResult = 0;
  LOBYTE(this->m_bQuitFlag) = 1;
  this->m_bPause = 1;
  BYTE2(this->m_bFiveNimbus) = 1;
  (int)this;
}

// 0x00512D60
char CCBSystem::ProcWeaponSkill()
{
  CCBUI *m_pUI; // ecx
  int *m_pControl; // ecx
  CCBRoleState *m_pRoleState; // ecx
  CCBSystem *m_pAttackSequen; // ecx
  CCBStage *m_pStage; // ecx
  CCBAI *m_pAI; // ecx
  CCBEditor *m_pEditor; // ecx
  CEffMgr *m_pEffMgr; // ecx
  CEffMgr *m_pATSEffMgr; // ecx
  int v12; // edi
  int i; // ebp
  CCBRoleState *v14; // ecx

  if ( !this->m_pUtil || !CCBLineupWindow::IsFaceOnInitPos() )
    return 0;
  m_pUI = (CCBUI *)this->m_pUI;
  if ( !m_pUI || !((int)m_pUI)->CreateParaWindow() )
    return 0;
  m_pControl = (int *)this->m_pControl;
  if ( !m_pControl || !sub_4DC220(m_pControl) )
    return 0;
  m_pRoleState = (CCBRoleState *)this->m_pRoleState;
  if ( !m_pRoleState || !sub_4EC830((int)m_pRoleState) )
    return 0;
  m_pAttackSequen = (CCBSystem *)this->m_pAttackSequen;
  if ( !m_pAttackSequen || !m_pAttackSequen->DestroySubsystems() )
    return 0;
  m_pStage = (CCBStage *)this->m_pStage;
  if ( !m_pStage || !m_pStage->Destroy() )
    return 0;
  m_pAI = (CCBAI *)this->m_pAI;
  if ( !m_pAI || !m_pAI->Init() )
    return 0;
  if ( BYTE1(this->m_bFiveNimbus) )
  {
    m_pEditor = (CCBEditor *)this->m_pEditor;
    if ( !m_pEditor || !sub_4E0430(&m_pEditor->m_bAIHandRequre) )
      return 0;
  }
  m_pEffMgr = (CEffMgr *)this->m_pEffMgr;
  if ( !m_pEffMgr || !sub_4CDB60(m_pEffMgr) )
    return 0;
  m_pATSEffMgr = (CEffMgr *)this->m_pATSEffMgr;
  if ( !m_pATSEffMgr || !sub_4CDB60(m_pATSEffMgr) )
    return 0;
  ((int)this->m_p2DSpark->m_Spark)->CreateTrack(0);
  ((C2DSpark *)this->m_p2DSpark)->CreateStars();
  ((C3DSpark *)this->m_p3DSpark)->DestroyAll();
  v12 = 0;
  this->CreateObj((int (*)(int, int))CCBSystem::Message, 0, 0, 0, 0);
  ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
  for ( i = 0; i < 5; ++i )
  {
    v14 = (CCBRoleState *)this->m_pRoleState;
    if ( v14->m_Role[i].bValid )
    {
      *(_BYTE *)(v14->InitUI(v12) + 876) = 0;
      *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v12) + 877) = 0;
    }
    ++v12;
  }
  sub_4C6170(this->m_pEffectSimple);
  ((gbSceneGraph *)*(gbSceneGraph **)(g_Input.KeyInfo[177].Data + 448))->ResetBladeMgr();
  if ( this->m_pRoleState->m_bEnemySneakAttackUs && *((_BYTE *)CEffectSystem::DestroyAllEffect() + 4) )
  {
    ((int)this->m_pStage->m_pCamControl)->ClearFinishedTask(20);
    HIBYTE(this->m_bFiveNimbus) = 1;
    return 1;
  }
  else
  {
    ((int)this->m_pStage->m_pCamControl)->ClearFinishedTask(0);
    HIBYTE(this->m_bFiveNimbus) = 1;
    return 1;
  }
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
  float a2; // [esp+0h] [ebp-8h]
  float a2a; // [esp+0h] [ebp-8h]
  float dta; // [esp+Ch] [ebp+4h]

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
  ((int)this)->ProcMagic();
  this->IsFriendDoSkill();
  ((CCBAttackSequen *)this->m_pAttackSequen)->Update();
  ((CCBRoleState *)this->m_pRoleState)->Update();
  ((CCBAI *)this->m_pAI)->Update();
  ((CCBStage *)this->m_pStage)->Update();
  ((CCBControl *)this->m_pControl)->Update();
  if ( BYTE1(this->m_bFiveNimbus) )
  {
    m_pEditor = (CCBEditor *)this->m_pEditor;
    if ( m_pEditor )
      ((CCBUI *)m_pEditor)->Update();
  }
  a2 = this->m_DeltaTime;
  ((int)this->m_p2DSpark->m_Spark)->Render(a2);
  a2a = this->m_DeltaTime;
  ((C3DSpark *)this->m_p3DSpark)->Update(a2a);
  LOBYTE(result) = ((int)this)->ProcDefence();
  return result;
}

// 0x00513120
char CCBSystem::RenderCheck()
{
  char result; // al

  result = HIBYTE(this->m_bFiveNimbus);
  if ( result )
  {
    HIBYTE(this->m_bFiveNimbus) = 0;
  }
  else
  {
    ((CCBStage *)this->m_pStage)->EditorUpdate();
    return ((int)this->m_p2DSpark->m_Spark)->DestroyAll();
  }
  return result;
}

// 0x00513330
int CCBSystem::GetRenderFlag()
{
  int v0; // ecx
  int result; // eax
  int v2; // esi
  unsigned int *Instance; // eax
  char v4; // [esp+8h] [ebp+4h]

  LOBYTE(result) = v4;
  v2 = v0;
  *(_BYTE *)(v0 + 116) = v4;
  if ( v4 == 1 )
  {
    ((gbSceneGraph *)*(gbSceneGraph **)(g_Input.KeyInfo[177].Data + 448))->ResetBladeMgr();
    sub_4CEA80(*(_DWORD **)(v2 + 44));
    LOBYTE(result) = sub_4CEA80(*(_DWORD **)(v2 + 48));
    if ( *(_DWORD *)(v2 + 124) == 3 )
    {
      LOBYTE(result) = *(_BYTE *)(*(_DWORD *)(v2 + 112) + 72);
      if ( (_BYTE)result )
      {
        Instance = (unsigned int *)CScreenMode::GetInstance();
        return sub_53E970(Instance);
      }
    }
  }
  return result;
}

// 0x00513390
int CCBSystem::SetRenderFlag(char flag)
{
  int v3; // edi
  int result; // eax

  v3 = 0;
  LOBYTE(this->m_bFiveNimbus) = flag;
  do
  {
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v3) + 837) = this->m_bFiveNimbus;
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v3) + 832) = this->m_bFiveNimbus;
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v3) + 833) = this->m_bFiveNimbus;
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v3) + 834) = this->m_bFiveNimbus;
    result = ((CCBRoleState *)this->m_pRoleState)->InitUI(v3++);
    *(_BYTE *)(result + 835) = this->m_bFiveNimbus;
  }
  while ( v3 < 5 );
  return result;
}

// 0x00513840
int CCBSystem::CheckBattleEnd()
{
  int *p_bValid; // ebx
  int v3; // eax
  __int32 *v4; // edi
  int v5; // esi
  char v6; // bl
  int j; // edi
  int inited; // eax
  int k; // edi
  int v10; // eax
  bool v11; // cc
  CCBControl *v13; // ecx
  int Control; // eax
  int v15; // eax
  CCBControl *m_pControl; // ecx
  int v17; // [esp+10h] [ebp-Ch]
  int v18; // [esp+14h] [ebp-8h]
  __int32 *i; // [esp+18h] [ebp-4h]

  if ( BYTE1(this->m_bFiveNimbus) && dword_17A990C != 2 )
    return 0;
  p_bValid = 0;
  if ( (unsigned __int8)((CCBRoleState *)this->m_pRoleState)->GetForce(0) || this->m_bPause != 2 )
  {
    m_pControl = (CCBControl *)this->m_pControl;
    if ( LOBYTE(m_pControl->m_bActive) )
      ((CCBUI *)m_pControl)->GetState();
    return 0;
  }
  if ( !LOBYTE(this->m_pControl->m_bActive) )
  {
    v3 = 24;
    v4 = (__int32 *)&this->m_Thread[592].cmd.bDestRole[1];
    v5 = 0;
    v17 = 0;
    v18 = 24;
    for ( i = &this->m_Thread[592].cmd.bDestRole[1]; ; i += 13 )
    {
      if ( !this->m_pRoleState->m_Role[v17].bValid
        || !((CCBStageRole *)*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + v3))->ForceDelTaskByPFN() )
      {
        goto LABEL_39;
      }
      if ( sub_4ECB20(this->m_pRoleState, v5) )
      {
        ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
        return 0;
      }
      if ( ((CCBSystem *)this->m_pAttackSequen)->GetCmdType(v5) == 1
        && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v5) == 1
        && ((CCBStageRole *)this->m_pRoleState)->IsActive(v5) == 1
        && ((CCBSystem *)this->m_pAttackSequen)->IsBusy() )
      {
        if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 17)
          || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 14) )
        {
          goto LABEL_38;
        }
        if ( !*(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v5) + 837)
          && !((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 18)
          && !((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 19) )
        {
          sub_4F7FC0((int)this->m_pRoleState->m_sCombatDialog, v5);
          if ( !*(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v5) + 877)
            || (v6 = ((CCBAI *)this->m_pAI)->HandleFriendAffirmative(v5, 1),
                *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v5) + 877) = 0,
                !v6) )
          {
            if ( !*(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v5) + 876) )
            {
              dword_5DC3DC = v5;
              sub_4DC3F0((char *)this->m_pControl, v5);
              return 0;
            }
            if ( *((_BYTE *)v4 + 40) )
            {
              ((CCBAI *)this->m_pAI)->HandlePlayerNormalAttack(v5, (int)v4);
              for ( j = 0; j < 5; ++j )
              {
                inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(j);
                *(_BYTE *)(inited + 876) = 0;
              }
            }
            else
            {
              ((CCBAI *)this->m_pAI)->HandleFriendAffirmative(v5, 0);
              for ( k = 0; k < 5; ++k )
              {
                v10 = ((CCBRoleState *)this->m_pRoleState)->InitUI(k);
                *(_BYTE *)(v10 + 876) = 0;
              }
            }
          }
          goto LABEL_39;
        }
        sub_4F7FC0((int)this->m_pRoleState->m_sCombatDialog, v5);
        ((CCBAI *)this->m_pAI)->HandleEnemyChaos(v5);
      }
      if ( ((CCBSystem *)this->m_pAttackSequen)->GetCmdType(v5) != 1
        || ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v5) != 1
        || ((CCBStageRole *)this->m_pRoleState)->IsActive(v5)
        || !((CCBSystem *)this->m_pAttackSequen)->IsBusy() )
      {
        goto LABEL_39;
      }
      if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 17)
        || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v5, 14)
        || *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v5) + 879) )
      {
LABEL_38:
        ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(v5);
        goto LABEL_39;
      }
      ((CCBAI *)this->m_pAI)->Render(v5);
LABEL_39:
      v3 = v18 + 4;
      ++v17;
      ++v5;
      v4 = (__int32 *)i + 13;
      v11 = v18 + 4 < 68;
      v18 += 4;
      if ( !v11 )
        return 0;
    }
  }
  ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
  v13 = (CCBControl *)this->m_pControl;
  if ( LOBYTE(v13->m_CmdData.bSrcRole[2]) )
    p_bValid = (int *)&v13->m_InputData.bValid;
  Control = ((CCBSystem *)v13)->GetControl();
  if ( *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(Control) + 877)
    || (v15 = ((CCBSystem *)this->m_pControl)->GetControl(),
        *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v15) + 876)) )
  {
    dword_5DC3DC = -1;
    ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
    ((CCBUI *)this->m_pControl)->GetState();
    return 0;
  }
  if ( ((CCBSystem *)this->m_pControl)->GetControl() != dword_5DC3DC || !p_bValid )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(dword_5DC3DC, 14) )
  {
    ((CCBUI *)this->m_pControl)->GetState();
    return 0;
  }
  else
  {
    switch ( *p_bValid )
    {
      case 259:
        this->CreateObj(CCBSystem::IsRoleWaitForFlee, 0, 0, 0, p_bValid);
        qmemcpy(&this->m_Thread[592].cmd.bDestRole[13 * dword_5DC3DC + 1], p_bValid, 0x2Cu);
        *((_BYTE *)this->m_pAI->m_bNewRole + dword_5DC3DC) = 0;
        break;
      case 260:
        this->CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, p_bValid);
        qmemcpy(&this->m_Thread[592].cmd.bDestRole[13 * dword_5DC3DC + 1], p_bValid, 0x2Cu);
        *((_BYTE *)this->m_pAI->m_bNewRole + dword_5DC3DC) = 0;
        break;
      case 261:
        this->CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, p_bValid);
        qmemcpy(&this->m_Thread[592].cmd.bDestRole[13 * dword_5DC3DC + 1], p_bValid, 0x2Cu);
        *((_BYTE *)this->m_pAI->m_bNewRole + dword_5DC3DC) = 0;
        break;
      case 262:
        this->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, p_bValid);
        qmemcpy(&this->m_Thread[592].cmd.bDestRole[13 * dword_5DC3DC + 1], p_bValid, 0x2Cu);
        *((_BYTE *)this->m_pAI->m_bNewRole + dword_5DC3DC) = 0;
        break;
      case 264:
      case 266:
      case 268:
        this->CreateObj(sub_5158F0, 0, 0, 0, p_bValid);
        break;
      case 265:
        this->CreateObj(CCBSystem::PassCmdViaThread, 0, 0, 0, p_bValid);
        qmemcpy(&this->m_Thread[592].cmd.bDestRole[13 * dword_5DC3DC + 1], p_bValid, 0x2Cu);
        *((_BYTE *)this->m_pAI->m_bNewRole + dword_5DC3DC) = 0;
        break;
      case 267:
        this->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, p_bValid);
        qmemcpy(&this->m_Thread[592].cmd.bDestRole[13 * dword_5DC3DC + 1], p_bValid, 0x2Cu);
        *((_BYTE *)this->m_pAI->m_bNewRole + dword_5DC3DC) = 0;
        break;
      case 269:
        this->CreateObj(CCBSystem::DelThread, 0, 0, 0, p_bValid);
        *((_BYTE *)this->m_pAI->m_bNewRole + dword_5DC3DC) = 0;
        break;
      default:
        break;
    }
    sub_4DC510((int)this->m_pControl, p_bValid[2]);
    dword_5DC3DC = -1;
    return 0;
  }
}

// 0x00515AC0
char CCBSystem::CreateObj(int a2)
{
  int v2; // edx
  __int32 *i; // eax

  v2 = 0;
  for ( i = &this->m_bLockCam;
        !*((_BYTE *)i + 36)
     || (int (*)(int, int))*i != CCBSystem::PassCmdToThread
     || *i && (i[1] || i[2] || i[3])
     || i[12] != a2;
        i += 22 )
  {
    if ( ++v2 >= 1024 )
      return 0;
  }
  return 1;
}

// 0x00515C50
char CCBSystem::ClearEffect(int idx)
{
  memset(&this->m_bLockCam + 22 * idx, 0, 0x58u);
  --this->m_nTimesOfCombat;
  return 1;
}

// 0x00515D10
bool CCBSystem::CreateObj2(_DWORD *a2)
{
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-40Ch] BYREF
  int v8; // [esp+810h] [ebp-4h]

  v3 = (_DWORD *)((operator *)0x2598u)->new();
  v8 = 0;
  if ( v3 )
    v4 = (_DWORD *)sub_4E02F0(v3, (int)this);
  else
    v4 = 0;
  v8 = -1;
  *a2 = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_4, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return sub_4E0380(v4) != 0;
}
