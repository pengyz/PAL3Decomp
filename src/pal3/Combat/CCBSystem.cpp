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
#include "pal3/gen/CCBStageScene.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/Combat.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/PAL_GDB.h"
#include "pal3/gen/SceneMgr.h"
#include "pal3/gen/UICursor.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int SceneMgrUpdate(...);
int sub_4C5980(...);
int sub_4C6170(...);
int sub_4CDAE0(...);
int sub_4CDB60(...);
int sub_4CDC50(...);
int sub_4CEA80(...);
int sub_4DB730(...);
int sub_4DB9C0(...);
int sub_4DB9F0(...);
int sub_4DBB80(...);
int sub_4DC160(...);
int sub_4DC1B0(...);
int sub_4DC220(...);
int sub_4DC3F0(...);
int sub_4DC510(...);
int sub_4E02F0(...);
int sub_4E0330(...);
int sub_4E0380(...);
int sub_4E03F0(...);
int sub_4E0430(...);
int sub_4E0530(...);
int sub_4E05B0(...);
int sub_4EC680(...);
int sub_4EC700(...);
int sub_4EC7D0(...);
int sub_4EC830(...);
int sub_4ECB20(...);
int sub_4F7050(...);
int sub_4F7140(...);
int sub_4F76C0(...);
int sub_4F7820(...);
int sub_4F7FC0(...);
int sub_4FF360(...);
int sub_4FF560(...);
int sub_4FFA90(...);
int sub_4FFCB0(...);
int sub_4FFED0(...);
int sub_4FFF60(...);
int sub_500220(...);
int sub_5004B0(...);
int sub_500550(...);
int sub_5007A0(...);
int sub_500C20(...);
int sub_500D50(...);
int sub_5014E0(...);
int sub_502000(...);
int sub_5020D0(...);
int sub_5024D0(...);
int sub_50A4B0(...);
int sub_512420(...);
int sub_5158F0(...);
int sub_515C90(...);
int sub_5163D0(...);
int sub_51D5C0(...);
int sub_53E970(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Co_4[];
extern char aDeltatimeF[];
extern char aEffectCombat10[];
extern char aEffectObjectsD[];
extern char aEffectTimerF[];
extern char aPal3CombatSyst[];
extern char aRoleDXFZFRotF[];
extern char aThreadDStageta[];
extern char aTimefundF[];
extern char aTimesOfCombatD[];
extern char aTooManyCharact[];
extern unsigned char byte_17AC5DC;
extern unsigned char byte_17AC6DC;
extern unsigned char byte_17AC7F0;
extern unsigned char byte_5DE9E4;
extern int dword_17AC7E0;
extern int dword_17AC7E4;
extern int dword_17AC7E8;
extern int dword_17ACA80;
extern int dword_17ACA84;
extern int dword_17ACA88;
extern int dword_17ACA8C;
extern int dword_17ACA90;
extern int dword_17ACA94;
extern int dword_17ACA98;
extern int dword_17ACA9C;
extern int dword_17ACAA0;
extern int dword_17ACAA4;
extern int dword_17ACAA8;
extern int dword_17ACAAC;
extern int dword_17ACAC0;
extern int dword_17ACAC4;
extern int dword_17ACAC8;
extern int dword_17ACACC;
extern int dword_17ACAD0;
extern int dword_17ACAD4;
extern int dword_17ACAD8;
extern int dword_17ACADC;
extern int dword_17ACE14;
extern int dword_17ACE1C;
extern int dword_17ACE20;
extern int dword_17ACE24;
extern int dword_17ACE28;
extern int dword_17ACE2C;
extern int dword_17ACE30;
extern int dword_17ACE34;
extern int dword_17ACE38;
extern int dword_17ACE3C;
extern int dword_17ACE40;
extern int dword_17ACE44;
extern int dword_17ACE48;
extern int dword_17ACE4C;
extern int dword_17ACE50;
extern int dword_17ACE54;
extern int dword_17ACE58;
extern int dword_17ACE5C;
extern int dword_17ACE60;
extern int dword_17ACE64;
extern int dword_17ACE68;
extern int dword_17B30E4;
extern float flt_17AC7DC;
extern float flt_17AC7EC;
extern float flt_17ACA78;
extern float flt_17ACE10;
extern int nullsub_3;
extern int nullsub_68;

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
  this->m_Thread[300] = 1;
  this->m_Thread[301] = 1;
  this->m_Thread[302] = 1;
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

  this->ResetFlags();
  if ( !this->m_pUtil )
    return 0;
  if ( !this->m_pUI )
    return 0;
  if ( !this->m_pControl )
    return 0;
  sub_4DBB80(this);
  sub_4DB9F0(this);
  if ( g_nCombatMode == 1 )
  {
    m_pAttackSequenBack = (UIStatic *)this->m_pUtil->m_pUI->m_pAttackSequenBack;
    ((void (*)(UIStatic *, _DWORD))*m_pAttackSequenBack->_base._vftable)(m_pAttackSequenBack, 0);
    for ( i = 76; i < 120; i += 4 )
    {
      v5 = *(void (****)(_DWORD, _DWORD))((char *)&this->m_pUtil->m_pUI->_base._base._vftable + i);
      (**v5)(v5, 0);
    }
    return 1;
  }
  else
  {
    v6 = (UIStatic *)this->m_pUtil->m_pUI->m_pAttackSequenBack;
    (*(void (**)(UIStatic *, int))v6->_base._vftable)(v6, 1);
    v7 = 0;
    for ( j = 76; j < 120; j += 4 )
    {
      m_pUtil = (CCBSystem *)this->m_pUtil;
      if ( *(&this->m_pUtil->m_pRoleState->m_Role[0].bValid + v7) )
        (***(void (****)(_DWORD, int))((char *)&m_pUtil->m_pUI->_base._base._vftable + j))(
          *(void ***)((char *)&m_pUtil->m_pUI->_base._base._vftable + j),
          1);
      else
        (***(void (****)(_DWORD, _DWORD))((char *)&m_pUtil->m_pUI->_base._base._vftable + j))(
          *(void ***)((char *)&m_pUtil->m_pUI->_base._base._vftable + j),
          0);
      v7 += 892;
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
    if ( m_pControl->m_Thread[7]._pad_0004[v3 + 9] )
    {
      if ( !((CCBStageRole *)m_pControl)->IsActive(v2) )
      {
        v6 = (CCBRoleState *)this->m_pControl;
        if ( !v6->m_Role[0]._rest[v3 + 804]
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
    v3 += 892;
    ++v2;
    p_m_pEffectSimple += 10;
  }
  while ( v3 < 9812 );
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

  this->m_Thread[301] = v2;
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
  --*(_DWORD *)&this->m_Thread[4];
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
  int v2; // eax
  char *v3; // edi
  char *v4; // ebp
  int v5; // eax

  v2 = 2632 * *(_DWORD *)&this->m_Thread[8];
  v3 = (char *)&this->m_Thread[v2 + 2608];
  v4 = (char *)&this->m_Thread[80 * *(_DWORD *)&this->m_Thread[12] + 32 + v2];
  if ( !((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *(_DWORD *)v3))->IsReady(*(_DWORD *)&this->m_Thread[v2 + 2592]) )
    goto LABEL_7;
  if ( !v4[41] && ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *(_DWORD *)v3))->ForceDelTaskByPFN() )
  {
    ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *(_DWORD *)v3))->GetState();
    v5 = *((_DWORD *)&this->m_pAI + *(_DWORD *)v3);
    *(_DWORD *)(v5 + 6632) = *(_DWORD *)(v5 + 6636);
    v4[41] = 1;
  }
  if ( v4[43] == 1 || ((CCBStageRole *)*((CCBStageRole **)&this->m_pAI + *(_DWORD *)v3))->ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v4 + 4) = 4;
  return 0;
}

// 0x00512310
void CCBSystem::HandleInput()
{
  flt_17ACA78 = 12.0 + 12.0;
}

// 0x00512320
// attributes: thunk
int CCBSystem::SetQuitFlag()
{
  return CCBSystem::IsEditorWindow();
}

// 0x00512330
int CCBSystem::IsEditorWindow()
{
  dword_17ACA80 = 119;
  dword_17ACA84 = 314;
  dword_17ACA88 = 510;
  dword_17ACA8C = 707;
  return 707;
}

// 0x00512370
// attributes: thunk
int CCBSystem::SetAuto()
{
  return CCBSystem::SetAutoOnly();
}

// 0x00512380
int CCBSystem::SetAutoOnly()
{
  dword_17ACA90 = 519;
  dword_17ACA94 = 519;
  dword_17ACA98 = 519;
  dword_17ACA9C = 519;
  return 519;
}

// 0x005123C0
// attributes: thunk
int CCBSystem::ShowInfo()
{
  return CCBSystem::SetTimeScale();
}

// 0x005123D0
int CCBSystem::SetTimeScale()
{
  dword_17ACAA0 = 128;
  dword_17ACAA4 = 323;
  dword_17ACAA8 = 519;
  dword_17ACAAC = 716;
  return 716;
}

// 0x00512410
// attributes: thunk
int CCBSystem::GetFreeID()
{
  return sub_512420();
}

// 0x00512460
// attributes: thunk
int CCBSystem::DelAllTaskAndThread()
{
  return CCBSystem::Proceed();
}

// 0x00512470
int CCBSystem::Proceed()
{
  dword_17ACAC0 = 121;
  dword_17ACAC4 = 316;
  dword_17ACAC8 = 512;
  dword_17ACACC = 709;
  return 709;
}

// 0x005124B0
// attributes: thunk
int CCBSystem::CanBeHandleWPX_R()
{
  return CCBSystem::CanBeHandleNGH_R();
}

// 0x005124C0
int CCBSystem::CanBeHandleNGH_R()
{
  dword_17ACAD0 = 573;
  dword_17ACAD4 = 573;
  dword_17ACAD8 = 573;
  dword_17ACADC = 573;
  return 573;
}

// 0x00512500
CCBSystem::CCBSystem()
{
  char *v1; // esi
  int v2; // ebx
  char *v3; // edi
  char *m_Player; // esi
  int v5; // ebx
  char *v6; // edi

  v1 = (char *)&this->m_Thread[40];
  v2 = 1024;
  do
  {
    v3 = v1;
    v1 += 88;
    --v2;
    memset(v3, 0, 0x2Cu);
  }
  while ( v2 );
  m_Player = (char *)this->m_Player;
  v5 = 11;
  do
  {
    v6 = m_Player;
    m_Player += 52;
    --v5;
    memset(v6, 0, 0x2Cu);
  }
  while ( v5 );
  memset(this, 0, sizeof(CCBSystem));
  this->m_eResult = CBR_NONE;
  LOBYTE(this->m_nTimesOfCombat) = 0;
  BYTE1(this->m_nTimesOfCombat) = 0;
  *(_DWORD *)&this->m_bFiveNimbus = 0;
  this->m_bQuitFlag = 1;
  this->m_eState = CBS_RUNNING;
  BYTE2(this->m_nTimesOfCombat) = 1;
  (int)this;
}

// 0x00512580
int CCBSystem::ProcDialog()
{
  this->m_DeltaTime = 0.0;
  memset(this->m_Thread, 0, sizeof(this->m_Thread));
  LODWORD(this->m_dTimeFund) = 0;
  LODWORD(this->m_AbsDeltaTime) = 0;
  LODWORD(this->m_dAbsTimeFund) = 0;
  this->m_eState = CBS_RUNNING;
  this->m_eResult = CBR_WIN;
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
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char CCBSystem::ProcNormalAttack()
{
  int v1; // ebp
  _DWORD *v3; // eax
  std::codecvt_base *v4; // ecx
  CCBSystem *v5; // eax
  char result; // al
  UIWnd *v7; // eax
  CCBUI *v8; // eax
  _DWORD *v9; // eax
  CCBRoleState *v10; // eax
  CCBSystem *v11; // eax
  CCBAttackSequen *inited; // eax
  CCBStage *v13; // eax
  CCBStage *v14; // eax
  _DWORD *v15; // eax
  CCBControl *v16; // eax
  CCBAI *v17; // eax
  CCBAI *v18; // eax
  SceneMgr *v19; // eax
  CCBStageCam *m_pCam; // edx
  gbCamera *v21; // edx
  CEffMgr *v22; // eax
  SceneMgr *v23; // eax
  CCBStageCam *v24; // ecx
  gbCamera *v25; // ecx
  CEffMgr *v26; // eax
  C2DSpark *v27; // eax
  C2DSpark *v28; // eax
  C3DSpark *v29; // eax
  C3DSpark *v30; // eax
  int *m_pES; // ecx
  CEffectSimple *v32; // eax
  char pExceptionObject[1024]; // [esp+Ch] [ebp-100Ch] BYREF
  char ArgList[1024]; // [esp+40Ch] [ebp-C0Ch] BYREF
  char v35[1024]; // [esp+80Ch] [ebp-80Ch] BYREF
  char v36[1024]; // [esp+C0Ch] [ebp-40Ch] BYREF
  int v37; // [esp+1014h] [ebp-4h]

  this->ProcDialog();
  v3 = (_DWORD *)operator new(1u);
  v37 = 0;
  if ( v3 )
    v5 = (CCBSystem *)sub_51D5C0(v3, (int)this);
  else
    v5 = 0;
  this->m_pUtil = v5;
  v37 = -1;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_4, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = v4->codecvt_base::do_always_noconv();
  if ( result )
  {
    v7 = (UIWnd *)operator new(0xA48u);
    v37 = 1;
    if ( v7 )
      v8 = (CCBUI *)v7->ctor_60A0((int)this);
    else
      v8 = 0;
    v37 = -1;
    this->m_pUI = v8;
    if ( !v8 )
    {
      qmemcpy(
        pExceptionObject,
        ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_4, 2504),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    result = sub_5163D0((UIListBox *)v8, v1);
    if ( result )
    {
      v9 = (_DWORD *)operator new(0x50A4u);
      v37 = 2;
      if ( v9 )
        v10 = (CCBRoleState *)sub_4EC680(v9, (int)this);
      else
        v10 = 0;
      v37 = -1;
      this->m_pRoleState = v10;
      if ( !v10 )
      {
        qmemcpy(
          pExceptionObject,
          ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_4, 2504),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      result = sub_4EC700((int)v10);
      if ( result )
      {
        v11 = (CCBSystem *)operator new(0x1C8u);
        v37 = 3;
        if ( v11 )
          inited = (CCBAttackSequen *)v11->InitCmd((int)this);
        else
          inited = 0;
        v37 = -1;
        this->m_pAttackSequen = inited;
        if ( !inited )
        {
          qmemcpy(
            pExceptionObject,
            ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_4, 2504),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        result = ((std *)inited)->codecvt_base::do_always_noconv();
        if ( result )
        {
          v13 = (CCBStage *)operator new(0xA48B0u);
          v37 = 4;
          if ( v13 )
            v14 = (CCBStage *)v13->CCBStage((int)this);
          else
            v14 = 0;
          v37 = -1;
          this->m_pStage = v14;
          if ( !v14 )
          {
            qmemcpy(
              pExceptionObject,
              ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_4, 2504),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          result = v14->Reset();
          if ( result )
          {
            v15 = (_DWORD *)operator new(0x570u);
            v37 = 5;
            if ( v15 )
              v16 = (CCBControl *)sub_4DC160(v15, this);
            else
              v16 = 0;
            v37 = -1;
            this->m_pControl = v16;
            if ( !v16 )
            {
              qmemcpy(
                pExceptionObject,
                ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_4, 2504),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            result = ((std *)v16)->codecvt_base::do_always_noconv();
            if ( result )
            {
              v17 = (CCBAI *)operator new(0xE50u);
              v37 = 6;
              if ( v17 )
                v18 = (CCBAI *)v17->Create(this);
              else
                v18 = 0;
              v37 = -1;
              this->m_pAI = v18;
              if ( !v18 )
              {
                qmemcpy(v35, ((Logger *)v36)->FormatException(aCNewFailed, aDProjectPal3Co_4, 2504), sizeof(v35));
                _CxxThrowException(v35, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              result = ((std *)v18)->codecvt_base::do_always_noconv();
              if ( result )
              {
                this->m_pES = (CEffectSystem *)g_pEffectSystem;
                this->ProcAI(1.0);
                result = this->CreateObj2(&this->m_pEditor);
                if ( result )
                {
                  v19 = (SceneMgr *)operator new(0xA930u);
                  v37 = 7;
                  if ( v19 )
                  {
                    m_pCam = (CCBStageCam *)this->m_pStage->m_pCam;
                    if ( m_pCam )
                      v21 = (gbCamera *)&m_pCam->_base[4];
                    else
                      v21 = 0;
                    v22 = (CEffMgr *)v19->Create(g_pGfxMgr, v21, (gbSceneGraph *)this);
                  }
                  else
                  {
                    v22 = 0;
                  }
                  this->m_pEffMgr = v22;
                  v23 = (SceneMgr *)operator new(0xA930u);
                  v37 = 8;
                  if ( v23 )
                  {
                    v24 = (CCBStageCam *)this->m_pStage->m_pCam;
                    if ( v24 )
                      v25 = (gbCamera *)&v24->_base[4];
                    else
                      v25 = 0;
                    v26 = (CEffMgr *)v23->Create(g_pGfxMgr, v25, (gbSceneGraph *)this);
                  }
                  else
                  {
                    v26 = 0;
                  }
                  this->m_pATSEffMgr = v26;
                  v27 = (C2DSpark *)operator new(0x5870u);
                  v37 = 9;
                  if ( v27 )
                    v28 = (C2DSpark *)v27->C2DSpark((int)g_pGameTime, (int)g_pAbsTime);
                  else
                    v28 = 0;
                  this->m_p2DSpark = v28;
                  v29 = (C3DSpark *)operator new(0x3E30u);
                  v37 = 10;
                  if ( v29 )
                    v30 = (C3DSpark *)v29->C3DSpark();
                  else
                    v30 = 0;
                  m_pES = (int *)this->m_pES;
                  this->m_p3DSpark = v30;
                  v32 = (CEffectSimple *)sub_4C5980(m_pES, 1);
                  this->m_pEffectSimple = v32;
                  ((CEffectSystem *)v32)->CEffectSystem((int)aEffectCombat10);
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
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
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
  CCBSystem *v13; // ecx
  CCBSystem *m_pEditor; // ecx
  gbRefObject **m_pEffMgr; // edi
  CEffMgr *m_pATSEffMgr; // edi
  C2DSpark *m_p2DSpark; // edi
  CCBSystem *m_p3DSpark; // ecx

  m_pStage = (CCBStage *)this->m_pStage;
  if ( !m_pStage )
    return 0;
  m_pStage->Create();
  v3 = (CCBStage *)this->m_pStage;
  if ( v3 )
  {
    nullsub_3(this->m_pStage);
    operator delete(v3);
  }
  this->m_pStage = 0;
  m_pAttackSequen = (std::codecvt_base *)this->m_pAttackSequen;
  if ( !m_pAttackSequen )
    return 0;
  m_pAttackSequen->codecvt_base::do_always_noconv();
  v5 = (CCBAttackSequen *)this->m_pAttackSequen;
  if ( v5 )
  {
    nullsub_3(this->m_pAttackSequen);
    operator delete(v5);
  }
  this->m_pAttackSequen = 0;
  m_pRoleState = (CCBRoleState *)this->m_pRoleState;
  if ( !m_pRoleState )
    return 0;
  sub_4EC7D0(m_pRoleState->m_sCombatDialog);
  v7 = (CCBRoleState *)this->m_pRoleState;
  if ( v7 )
  {
    nullsub_3(this->m_pRoleState);
    operator delete(v7);
  }
  this->m_pRoleState = 0;
  m_pControl = (std::codecvt_base *)this->m_pControl;
  if ( !m_pControl )
    return 0;
  m_pControl->codecvt_base::do_always_noconv();
  v9 = (CCBControl *)this->m_pControl;
  if ( v9 )
  {
    sub_4DC1B0((int)this->m_pControl);
    operator delete(v9);
  }
  this->m_pControl = 0;
  m_pUI = (CCBUI *)this->m_pUI;
  if ( !m_pUI )
    return 0;
  (*((void (**)(CCBUI *))m_pUI->_base._base._vftable + 3))(m_pUI);
  v11 = (CCBUI *)this->m_pUI;
  if ( v11 )
    (*((void (**)(CCBUI *, int))v11->_base._base._vftable + 5))(v11, 1);
  this->m_pUI = 0;
  m_pAI = (std::codecvt_base *)this->m_pAI;
  if ( !m_pAI )
    return 0;
  m_pAI->codecvt_base::do_always_noconv();
  v13 = (CCBSystem *)this->m_pAI;
  if ( v13 )
    v13->DestroyObj(1);
  this->m_pAI = 0;
  if ( !this->m_pEditor )
    return 0;
  sub_4E03F0();
  m_pEditor = (CCBSystem *)this->m_pEditor;
  if ( m_pEditor )
    m_pEditor->DestroyObj(1);
  this->m_pEditor = 0;
  if ( !this->m_pUtil )
    return 0;
  ((std *)m_pEditor)->codecvt_base::do_always_noconv();
  if ( this->m_pUtil )
    ((CCBSystem *)this->m_pUtil)->DestroyObj(1);
  m_pEffMgr = (gbRefObject **)this->m_pEffMgr;
  this->m_pUtil = 0;
  if ( m_pEffMgr )
  {
    sub_4CDAE0(m_pEffMgr);
    operator delete(m_pEffMgr);
    this->m_pEffMgr = 0;
  }
  m_pATSEffMgr = (CEffMgr *)this->m_pATSEffMgr;
  if ( m_pATSEffMgr )
  {
    sub_4CDAE0((gbRefObject **)this->m_pATSEffMgr);
    operator delete(m_pATSEffMgr);
    this->m_pATSEffMgr = 0;
  }
  m_p2DSpark = (C2DSpark *)this->m_p2DSpark;
  if ( m_p2DSpark )
  {
    ((C2DSpark *)this->m_p2DSpark)->~C2DSpark();
    operator delete(m_p2DSpark);
    this->m_p2DSpark = 0;
  }
  m_p3DSpark = (CCBSystem *)this->m_p3DSpark;
  if ( m_p3DSpark )
  {
    m_p3DSpark->ProcCoAttack(1);
    this->m_p3DSpark = 0;
  }
  return 1;
}

// 0x00512D40
void * CCBSystem::ProcCoAttack(CCBSystem *Block, char a2)
{
  ((C3DSpark *)Block)->~C3DSpark();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
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
  int *m_pEditor; // ecx
  CEffMgr *m_pEffMgr; // ecx
  CEffMgr *m_pATSEffMgr; // ecx
  int v12; // edi
  int i; // ebp
  CCBRoleState *v14; // ecx

  if ( !this->m_pUtil || !CCBLineupWindow::IsFaceOnInitPos() )
    return 0;
  m_pUI = (CCBUI *)this->m_pUI;
  if ( !m_pUI || !m_pUI->CreateParaWindow() )
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
  if ( BYTE1(this->m_nTimesOfCombat) )
  {
    m_pEditor = (int *)this->m_pEditor;
    if ( !m_pEditor || !sub_4E0430(m_pEditor) )
      return 0;
  }
  m_pEffMgr = (CEffMgr *)this->m_pEffMgr;
  if ( !m_pEffMgr || !sub_4CDB60(m_pEffMgr) )
    return 0;
  m_pATSEffMgr = (CEffMgr *)this->m_pATSEffMgr;
  if ( !m_pATSEffMgr || !sub_4CDB60(m_pATSEffMgr) )
    return 0;
  ((C2DSpark *)this->m_p2DSpark)->CreateTrack(0);
  ((C2DSpark *)this->m_p2DSpark)->CreateStars();
  ((C3DSpark *)this->m_p3DSpark)->DestroyAll();
  v12 = 0;
  this->CreateObj((int (*)(int, int))CCBSystem::Message, 0, 0, 0, 0);
  ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
  for ( i = 0; i < 4460; i += 892 )
  {
    v14 = (CCBRoleState *)this->m_pRoleState;
    if ( *(&v14->m_Role[0].bValid + i) )
    {
      *(_BYTE *)(v14->InitUI(v12) + 876) = 0;
      *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v12) + 877) = 0;
    }
    ++v12;
  }
  sub_4C6170(this->m_pEffectSimple);
  ((gbSceneGraph *)g_pGfxMgr->pSceneGraph)->ResetBladeMgr();
  if ( this->m_pRoleState->m_bEnemySneakAttackUs && LOBYTE(CEffectSystem::DestroyAllEffect()->m_pVertexBuffer) )
  {
    ((CCBStageCam *)this->m_pStage->m_pCamControl)->ClearFinishedTask(20);
    HIBYTE(this->m_nTimesOfCombat) = 1;
    return 1;
  }
  else
  {
    ((CCBStageCam *)this->m_pStage->m_pCamControl)->ClearFinishedTask(0);
    HIBYTE(this->m_nTimesOfCombat) = 1;
    return 1;
  }
}

// 0x00512F40
char CCBSystem::ProcMagicWait(int a2, char a3)
{
  int v4; // ecx
  unsigned int v5; // ebx
  char *v6; // edi
  int v8; // [esp+1Ch] [ebp+8h]
  char v9; // [esp+23h] [ebp+Fh]

  this->ProcDialog();
  v4 = *(_DWORD *)&this->m_bFiveNimbus + 1;
  BYTE1(this->m_nTimesOfCombat) = a3;
  this->m_bQuitFlag = 0;
  this->m_eState = CBS_END;
  this->m_eResult = CBR_WIN;
  *(_DWORD *)&this->m_bFiveNimbus = v4;
  ++*(_DWORD *)&g_SceneMgr._gap_c93c[8];
  this->m_pFightInfo = (FightInfo *)a2;
  v9 = this->ProcWeaponSkill();
  UICursor::IRender();
  v5 = 0;
  v6 = (char *)&g_SceneMgr.m_slot0[268];
  v8 = 0;
  do
  {
    if ( *(&this->m_pRoleState->m_Role[0].bValid + v8) && (*((_DWORD *)v6 - 3) == 8114 || *(_DWORD *)v6 == 8114) )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)102.39999 )
        ((CCBRoleState *)this->m_pRoleState)->ProcessRound(v5);
    }
    v6 += 1408;
    ++v5;
    v8 += 892;
  }
  while ( (int)v6 < (int)&g_SceneMgr.m_RoleSystem[0]._pad_284[192] );
  return v9;
}

// 0x00513060
int CCBSystem::CombatUpdate(double dt)
{
  double v3; // st6
  float *pad_000; // ecx
  double v5; // st7
  double v6; // st7
  CCBEditor *m_pEditor; // ecx
  int result; // eax
  float a2; // [esp+0h] [ebp-8h]
  float a2a; // [esp+0h] [ebp-8h]
  float dta; // [esp+Ch] [ebp+4h]

  this->m_AbsDeltaTime = dt;
  v3 = dt + this->m_dAbsTimeFund;
  pad_000 = (float *)this->m_pEffMgr->_pad_000;
  this->m_dAbsTimeFund = v3;
  this->m_fAbsTimeFund = v3;
  v5 = dt * this->m_fTimeScale;
  this->m_DeltaTime = v5;
  v6 = v5 + this->m_dTimeFund;
  dta = v6;
  this->m_dTimeFund = v6;
  this->m_fTimeFund = v6;
  SceneMgrUpdate(pad_000, dta);
  SceneMgrUpdate((float *)this->m_pATSEffMgr->_pad_000, this->m_fAbsTimeFund);
  this->ProcMagic();
  this->IsFriendDoSkill();
  ((CCBAttackSequen *)this->m_pAttackSequen)->Update();
  ((CCBRoleState *)this->m_pRoleState)->Update();
  ((CCBAI *)this->m_pAI)->Update();
  ((CCBStage *)this->m_pStage)->Update();
  ((CCBControl *)this->m_pControl)->Update();
  if ( BYTE1(this->m_nTimesOfCombat) )
  {
    m_pEditor = (CCBEditor *)this->m_pEditor;
    if ( m_pEditor )
      ((CCBUI *)m_pEditor)->Update();
  }
  a2 = this->m_DeltaTime;
  ((C2DSpark *)this->m_p2DSpark)->Render(a2);
  a2a = this->m_DeltaTime;
  ((C3DSpark *)this->m_p3DSpark)->Update(a2a);
  LOBYTE(result) = this->ProcDefence();
  return result;
}

// 0x00513120
char CCBSystem::RenderCheck()
{
  char result; // al

  result = HIBYTE(this->m_nTimesOfCombat);
  if ( result )
  {
    HIBYTE(this->m_nTimesOfCombat) = 0;
  }
  else
  {
    ((CCBStage *)this->m_pStage)->EditorUpdate();
    return ((C2DSpark *)this->m_p2DSpark)->DestroyAll();
  }
  return result;
}

// 0x00513150
char CCBSystem::ProcMagic()
{
  char v2; // bl
  int v3; // ebp
  int i; // edi
  int inited; // eax
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
  if ( g_nCombatMode == 1 )
  {
    if ( g_Input.KeyInfo[15].PressTime == 1 || g_Input.KeyInfo[16].PressTime == 1 )
    {
      v3 = 0;
      for ( i = 24; i < 68; i += 4 )
      {
        if ( sub_50A4B0(*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + i)) )
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
          this->m_pStage->m_pScene->_pad_3C0[4] = 1;
      }
    }
    if ( (g_Input.KeyInfo[15].Data & 0xF) != 1 && (g_Input.KeyInfo[16].Data & 0xF) != 1 )
    {
      ((CCBStage *)this->m_pStage)->DoTask(-1);
      this->m_pStage->m_pScene->_pad_3C0[4] = 0;
    }
  }
  LOBYTE(inited) = 1;
  if ( dword_17B30E4 != 1 )
  {
    if ( g_Input.KeyInfo[30].PressTime == 1 && this->m_pRoleState )
    {
      v6 = 0;
      for ( j = 0; j < 4460; j += 892 )
      {
        m_pRoleState = (CCBRoleState *)this->m_pRoleState;
        if ( *(&m_pRoleState->m_Role[0].bValid + j) )
        {
          *(_BYTE *)(m_pRoleState->InitUI(v6) + 837) = 0;
          *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v6) + 832) = 0;
          *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v6) + 833) = 0;
          *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v6) + 834) = 0;
          *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v6) + 835) = 0;
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
        v11 = (CCBRoleState *)this->m_pRoleState;
        if ( *(&v11->m_Role[0].bValid + k) )
        {
          *(_BYTE *)(v11->InitUI(v9) + 876) = 1;
          *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v9) + 877) = 0;
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
        v14 = (CCBRoleState *)this->m_pRoleState;
        LOBYTE(inited) = *(&v14->m_Role[0].bValid + m);
        if ( (_BYTE)inited )
        {
          *(_BYTE *)(v14->InitUI(v12) + 877) = 1;
          inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(v12);
          *(_BYTE *)(inited + 876) = 0;
        }
        ++v12;
      }
    }
  }
  return inited;
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
    ((gbSceneGraph *)g_pGfxMgr->pSceneGraph)->ResetBladeMgr();
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

// 0x00513380
bool CCBSystem::ProcUseItem(HWND a1)
{
  return sub_4E0530(a1);
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
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v3) + 837) = this->m_nTimesOfCombat;
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v3) + 832) = this->m_nTimesOfCombat;
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v3) + 833) = this->m_nTimesOfCombat;
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v3) + 834) = this->m_nTimesOfCombat;
    result = ((CCBRoleState *)this->m_pRoleState)->InitUI(v3++);
    *(_BYTE *)(result + 835) = this->m_nTimesOfCombat;
  }
  while ( v3 < 5 );
  return result;
}

// 0x00513420
char CCBSystem::ProcFlee(char a2)
{
  LOBYTE(this->m_nTimesOfCombat) = a2;
  return a2;
}

// 0x00513430
char CCBSystem::ProcDefence()
{
  int v2; // ebx
  int v3; // ebp
  int i; // edi
  int *v5; // eax
  char result; // al

  if ( (byte_17AC7F0 & 1) == 0 )
  {
    byte_17AC7F0 |= 1u;
    flt_17AC7EC = this->m_fTimeFund;
  }
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage(5, 75, aThreadDStageta);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage(5, 90, aTimesOfCombatD);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage(5, 105, aTimefundF);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage(5, 120, aDeltatimeF);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage(5, 195, aEffectObjectsD);
  ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage(5, 210, aEffectTimerF);
  if ( (byte_17AC7F0 & 2) == 0 )
  {
    dword_17AC7E0 = 0;
    byte_17AC7F0 |= 2u;
    dword_17AC7E4 = 0;
    dword_17AC7E8 = 0;
    atexit(nullsub_68);
  }
  v2 = 0;
  v3 = 20;
  for ( i = 24; i < 44; i += 4 )
  {
    v5 = (int *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[6432];
    dword_17AC7E0 = *v5;
    dword_17AC7E4 = v5[1];
    dword_17AC7E8 = v5[2];
    flt_17AC7DC = *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[6480];
    result = ((Combat *)this->m_pStage->m_TempStorageNGH)->LogMessage(380, v3, aRoleDXFZFRotF);
    ++v2;
    v3 += 15;
  }
  return result;
}

// 0x00513600
void CCBSystem::ProcAI(float a2)
{
  CEffectSystem *m_pES; // ecx
  CEffMgr *m_pEffMgr; // ecx
  CEffMgr *m_pATSEffMgr; // ecx
  int v6; // ecx
  int i; // eax
  gbVisNode *d268; // ecx

  m_pES = (CEffectSystem *)this->m_pES;
  this->m_fTimeScale = a2;
  m_pES->m_fTimeScale = a2;
  m_pEffMgr = (CEffMgr *)this->m_pEffMgr;
  if ( m_pEffMgr )
    sub_4CDC50(m_pEffMgr, SLODWORD(a2));
  m_pATSEffMgr = (CEffMgr *)this->m_pATSEffMgr;
  if ( m_pATSEffMgr )
    sub_4CDC50(m_pATSEffMgr, 1065353216);
  v6 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( *(&this->m_pRoleState->m_Role[0].bValid + v6) )
      *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[116] = a2;
    v6 += 892;
  }
  d268 = (gbVisNode *)this->m_pStage->m_pScene->_d268;
  if ( d268 )
    d268->SetTimeScale(a2);
  if ( BYTE1(this->m_nTimesOfCombat) )
    sub_4E05B0(a2);
}

// 0x005136A0
int CCBSystem::ProcProtect()
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
  int inited; // eax
  CCBControl *m_pControl; // ecx
  int v5; // ecx
  int v6; // edx

  inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(0);
  if ( *(_DWORD *)(inited + 84) == idx )
  {
    inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(0);
    *(_DWORD *)(inited + 84) = -1;
  }
  m_pControl = (CCBControl *)this->m_pControl;
  if ( m_pControl->m_bActive )
  {
    inited = ((CCBSystem *)m_pControl)->GetControl();
    if ( inited == idx )
    {
      ((CCBUI *)this->m_pControl)->GetState();
      v5 = 0;
      for ( inited = 24; inited < 68; inited += 4 )
      {
        if ( *(&this->m_pRoleState->m_Role[0].bValid + v5) )
        {
          (*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + inited))->m_Thread[128] = 0;
          (*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + inited))->m_Thread[122] = 0;
        }
        v5 += 892;
      }
    }
  }
  ((CCBStage *)inited)->IsTaskValidButNotFinish((int)this->m_pStage, idx);
  ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(idx);
  sub_4DB9C0(&this->m_pAttackSequen->m_pCBSystem, idx, 0);
  this->m_pStage->m_pRole[idx]->m_bShowWeapon = 0;
  this->m_pStage->m_pRole[idx]->m_bFlash = 0;
  ((CCBStageRole *)this->m_pStage->m_pRole[idx])->ClearAniMsg(0, 1.0);
  v6 = ((CCBRoleState *)this->m_pRoleState)->InitUI(idx);
  memset((void *)(v6 + 589), 0, 0x18u);
  *(_WORD *)(v6 + 613) = 0;
  *(_BYTE *)(v6 + 615) = 0;
  memset((void *)(v6 + 616), 0, 0x34u);
  *(_WORD *)(v6 + 668) = 0;
  memset((void *)(v6 + 670), 0, 0x34u);
  *(_WORD *)(v6 + 722) = 0;
  *(_BYTE *)(v6 + 588) = 0;
  return ((CCBStageRole *)this->m_pStage->m_pRole[idx])->DangerForceRelease(0);
}

// 0x005137F0
int CCBSystem::IsFriendDoSkill()
{
  int v2; // ebp
  char *m_Thread; // esi
  int result; // eax

  v2 = 0;
  m_Thread = (char *)this->m_Thread;
  do
  {
    if ( m_Thread[36] == 1 )
    {
      this->m_nThread = v2;
      result = (*(int (**)(char *, _DWORD))m_Thread)((char *)this + *((_DWORD *)m_Thread + 1), 0);
      this->m_nThread = -1;
    }
    ++v2;
    m_Thread += 88;
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
  char *m_Player; // edi
  unsigned int v5; // esi
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
  char *i; // [esp+18h] [ebp-4h]

  if ( BYTE1(this->m_nTimesOfCombat) && g_nCombatMode != 2 )
    return 0;
  p_m_CmdData = 0;
  if ( (unsigned __int8)((CCBRoleState *)this->m_pRoleState)->GetForce(0) || this->m_eState != CBS_END )
  {
    m_pControl = (CCBControl *)this->m_pControl;
    if ( m_pControl->m_bActive )
      ((CCBUI *)m_pControl)->GetState();
    return 0;
  }
  if ( !this->m_pControl->m_bActive )
  {
    v3 = 24;
    m_Player = (char *)this->m_Player;
    v5 = 0;
    v17 = 0;
    v18 = 24;
    for ( i = this->m_Player; ; i += 52 )
    {
      if ( !*(&this->m_pRoleState->m_Role[0].bValid + v17)
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
              g_bDebugMode = v5;
              sub_4DC3F0((char *)this->m_pControl, v5);
              return 0;
            }
            if ( m_Player[40] )
            {
              ((CCBAI *)this->m_pAI)->HandlePlayerNormalAttack(v5, (int)m_Player);
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
      v17 += 892;
      ++v5;
      m_Player = (char *)i + 52;
      v11 = v18 + 4 < 68;
      v18 += 4;
      if ( !v11 )
        return 0;
    }
  }
  ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
  v13 = (CCBControl *)this->m_pControl;
  if ( v13->m_CmdData.bDestRole[7] )
    p_m_CmdData = (int *)&v13->m_CmdData;
  Control = ((CCBSystem *)v13)->GetControl();
  if ( *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(Control) + 877)
    || (v15 = ((CCBSystem *)this->m_pControl)->GetControl(),
        *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v15) + 876)) )
  {
    g_bDebugMode = -1;
    ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
    ((CCBUI *)this->m_pControl)->GetState();
    return 0;
  }
  if ( ((CCBSystem *)this->m_pControl)->GetControl() != g_bDebugMode || !p_m_CmdData )
    return 0;
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(g_bDebugMode, 14) )
  {
    ((CCBUI *)this->m_pControl)->GetState();
    return 0;
  }
  else
  {
    switch ( *p_m_CmdData )
    {
      case 259:
        this->CreateObj((int (*)(int, int))CCBSystem::IsRoleWaitForFlee, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[52 * g_bDebugMode], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[g_bDebugMode] = 0;
        break;
      case 260:
        this->CreateObj((int (*)(int, int))CCBSystem::GetThreadIndex, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[52 * g_bDebugMode], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[g_bDebugMode] = 0;
        break;
      case 261:
        this->CreateObj((int (*)(int, int))CCBSystem::GetSameThreadNum, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[52 * g_bDebugMode], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[g_bDebugMode] = 0;
        break;
      case 262:
        this->CreateObj((int (*)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[52 * g_bDebugMode], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[g_bDebugMode] = 0;
        break;
      case 264:
      case 266:
      case 268:
        this->CreateObj(sub_5158F0, 0, 0, 0, p_m_CmdData);
        break;
      case 265:
        this->CreateObj((int (*)(int, int))CCBSystem::PassCmdViaThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[52 * g_bDebugMode], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[g_bDebugMode] = 0;
        break;
      case 267:
        this->CreateObj((int (*)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[52 * g_bDebugMode], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[g_bDebugMode] = 0;
        break;
      case 269:
        this->CreateObj((int (*)(int, int))CCBSystem::DelThread, 0, 0, 0, p_m_CmdData);
        this->m_pAI->m_bNewRole[g_bDebugMode] = 0;
        break;
      default:
        break;
    }
    sub_4DC510((int)this->m_pControl, p_m_CmdData[2]);
    g_bDebugMode = -1;
    return 0;
  }
}

// 0x00513EB0
int CCBSystem::Message(int a2)
{
  int RoleIndex; // edi

  BYTE2(this->m_pFightInfo->nRoleWillNotBeAttack) = 0;
  RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(3, 0, 1);
  if ( RoleIndex != -1 )
  {
    if ( this->m_pRoleState->m_bEnemySneakAttackUs
      || (((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::IsSubTaskFinished, 0, 0, 0, 0, -1082130432, 1082130432),
          ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::IsAllSubTaskFinished, 0, 0, 0, 0, 0, 1082130432),
          this->m_pRoleState->m_bWeSneakAttackEnemy) )
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::IsIdle, 0, 0, 0, 0, 0, 1077936128);
    }
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
  }
  this->CreateObj((int (*)(int, int))CCBSystem::CheckBattleEnd, 0, 0, 0, 0);
  this->ClearEffect(this->m_nThread);
  return 0;
}

// 0x00513FD0
int CCBSystem::IsRoleWaitForFlee(int a2)
{
  int m_nThread; // eax
  char *v4; // ebp
  char *v5; // edi
  int v6; // eax
  int RoleIndex; // eax
  int v8; // edi
  char a3; // [esp+13h] [ebp-15h] BYREF
  int v11; // [esp+14h] [ebp-14h] BYREF
  int a4; // [esp+18h] [ebp-10h] BYREF
  int a7; // [esp+1Ch] [ebp-Ch] BYREF
  int v14; // [esp+20h] [ebp-8h]
  int v15; // [esp+24h] [ebp-4h]

  m_nThread = this->m_nThread;
  a3 = 0;
  a4 = 0;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    v5 = (char *)&this->m_Thread[88 * m_nThread + 40];
    if ( !sub_4F7820(this->m_pRoleState->m_sCombatDialog, (int)v5) )
    {
LABEL_11:
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
      goto LABEL_12;
    }
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 1);
    if ( ((CCBRoleState *)this->m_pRoleState)->CheckVarianceRound(*((_DWORD *)v4 + 12), 0, &v11) == 1 )
    {
      v6 = *((_DWORD *)v4 + 12);
      *(_DWORD *)v5 = 270;
      *((_DWORD *)v4 + 11) = v11;
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v6);
      this->CreateObj((int (*)(int, int))CCBSystem::AddThread, 0, 0, 0, v4 + 40);
LABEL_12:
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(11, v4 + 40, 0);
    v8 = RoleIndex;
    *((_DWORD *)v4 + 5) = RoleIndex;
    if ( RoleIndex != -1 )
    {
      a7 = 0;
      v14 = 0;
      v15 = 0;
      v14 = *((_DWORD *)v4 + 12);
      v15 = *((_DWORD *)v4 + 13);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ProcShowSneakAttackState, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::HandleKeyCtrl, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ProcShowName, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v8);
    }
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(*((_DWORD *)v4 + 12));
    v4[37] = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
  if ( a3 == 1 )
  {
    if ( *((_DWORD *)v4 + 5) != -1 )
      ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    goto LABEL_11;
  }
  return 0;
}

// 0x00514220
int CCBSystem::AddThread(int a2)
{
  int m_nThread; // eax
  char *v4; // ebp
  int RoleIndex; // eax
  int v6; // edi
  char a3; // [esp+13h] [ebp-11h] BYREF
  int a4; // [esp+14h] [ebp-10h] BYREF
  int a7; // [esp+18h] [ebp-Ch] BYREF
  int v11; // [esp+1Ch] [ebp-8h]
  int v12; // [esp+20h] [ebp-4h]

  m_nThread = this->m_nThread;
  a3 = 0;
  a4 = 0;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*(_DWORD *)&this->m_Thread[88 * m_nThread + 48], 1);
    ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
    ((CCBRoleState *)this->m_pRoleState)->InitRoleFiveMagic((int)(v4 + 40));
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(12, v4 + 40, 0);
    v6 = RoleIndex;
    *((_DWORD *)v4 + 5) = RoleIndex;
    if ( RoleIndex == -1 )
    {
      v4[37] = 1;
      ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    a7 = 0;
    v11 = 0;
    v12 = 0;
    v11 = *((_DWORD *)v4 + 12);
    v12 = *((_DWORD *)v4 + 13);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, &a7, -1082130432, 0);
    a7 = -1;
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)sub_502000, 0, 0, 0, &a7, -1082130432, 1065353216);
    a7 = 0;
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)sub_4FF360, 0, 0, 0, &a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)CCBStage::ProcShowDamage, 0, 0, 0, &a7, -1082130432, 0);
    a7 = -1;
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)sub_5020D0, 0, 0, 0, &a7, -1082130432, 1065353216);
    a7 = 0;
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)CCBStage::ClearRoleAllTask, 0, 0, 0, &a7, -1082130432, 1065353216);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)sub_4FF560, 0, 0, 0, &a7, 0, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)CCBStage::ProcShowCost, 0, 0, 0, &a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)sub_4FF560, 0, 0, 0, &a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)sub_502000, 0, 0, 0, &a7, -1082130432, 1065353216);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)CCBStage::ProcShowCombatDialog, 0, 0, 0, &a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)sub_5020D0, 0, 0, 0, &a7, -1082130432, 1065353216);
    ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, &a7, -1082130432, 0);
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v6);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(*((_DWORD *)v4 + 12));
    v4[37] = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
  if ( a3 == 1 )
  {
    if ( *((_DWORD *)v4 + 5) != -1 )
      ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    ((CCBSystem *)this->m_pAttackSequen)->GetDeltaTime();
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514610
int CCBSystem::DelThread(int a2)
{
  int m_nThread; // eax
  char *v4; // ebp
  int v5; // ecx
  int RoleIndex; // eax
  int v7; // edi
  char a3; // [esp+13h] [ebp-11h] BYREF
  int a4; // [esp+14h] [ebp-10h] BYREF
  int a7; // [esp+18h] [ebp-Ch] BYREF
  int v12; // [esp+1Ch] [ebp-8h]
  int v13; // [esp+20h] [ebp-4h]

  m_nThread = this->m_nThread;
  a3 = 0;
  a4 = 0;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*(_DWORD *)&this->m_Thread[88 * m_nThread + 48], 1);
    v4[80] = 1;
    *((_DWORD *)v4 + 12) = 0;
    *((_DWORD *)v4 + 10) = 269;
    v5 = *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(0) + 528);
    *((_DWORD *)v4 + 13) = -1;
    *((_DWORD *)v4 + 11) = v5;
    ((CCBRoleState *)this->m_pRoleState)->GetRoleNum((int *)v4 + 10);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(11, v4 + 40, 0);
    v7 = RoleIndex;
    *((_DWORD *)v4 + 5) = RoleIndex;
    if ( RoleIndex != -1 )
    {
      a7 = 0;
      v12 = 0;
      v13 = 0;
      v12 = *((_DWORD *)v4 + 12);
      v13 = *((_DWORD *)v4 + 13);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBStage::ClearRoleAllTask, 0, 0, 0, &a7, -1082130432, 1065353216);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)sub_4FFED0, 0, 0, 0, &a7, 0, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)sub_4FFF60, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBSystem::EndBattle, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, &a7, -1082130432, 0);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v7);
    }
    *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 12)) + 536) = 0;
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(*((_DWORD *)v4 + 12));
    v4[37] = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
  if ( a3 == 1 )
  {
    if ( *((_DWORD *)v4 + 5) != -1 )
      ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514870
int CCBSystem::GetSameThreadNum(int a2)
{
  int m_nThread; // eax
  char *v4; // edi
  CCBControl *m_pControl; // ecx
  int v7; // [esp-4h] [ebp-14h]
  int a4; // [esp+Ch] [ebp-4h] BYREF

  a4 = 0;
  m_nThread = this->m_nThread;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    if ( ((CCBRoleState *)this->m_pRoleState)->CheckVarianceRound(*(_DWORD *)&this->m_Thread[88 * m_nThread + 48], *(_DWORD *)&this->m_Thread[88 * m_nThread + 44], &a4) == 1 )
    {
      v7 = *((_DWORD *)v4 + 12);
      *((_DWORD *)v4 + 10) = 270;
      *((_DWORD *)v4 + 11) = a4;
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v7);
      this->CreateObj((int (*)(int, int))CCBSystem::AddThread, 0, 0, 0, v4 + 40);
LABEL_16:
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    if ( !((CCBSystem *)this->m_pAttackSequen)->IsBusy() )
    {
      this->ClearEffect(this->m_nThread);
      return -1;
    }
    ((CCBSystem *)this->m_pAttackSequen)->sub_4DB730(*((_DWORD *)v4 + 12));
    if ( sub_4F76C0(this->m_pRoleState->m_sCombatDialog, *((_DWORD *)v4 + 12), *((_DWORD *)v4 + 11)) >= 4 )
    {
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(*((_DWORD *)v4 + 12));
    }
    else
    {
      ((CCBSystem *)*((_DWORD *)v4 + 12))->CalcSpeed(1);
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdCount(*((_DWORD *)v4 + 12));
    }
    ((CCBStageRole *)this->m_pStage->m_pRole[*((_DWORD *)v4 + 12)])->DelTask(4);
    v4[37] = 1;
  }
  if ( (unsigned __int8)((CCBRoleState *)this->m_pRoleState)->GetForce(0) )
  {
LABEL_12:
    ((CCBStageRole *)this->m_pStage->m_pRole[*((_DWORD *)v4 + 12)])->DelTask(2);
    this->ClearEffect(this->m_nThread);
    return 0;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(*((_DWORD *)v4 + 12), 15) )
  {
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(*((_DWORD *)v4 + 12));
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    goto LABEL_12;
  }
  if ( ((CCBSystem *)this->m_pAttackSequen)->IsCmdReady(*((_DWORD *)v4 + 12)) )
  {
    ((CCBStageRole *)this->m_pStage->m_pRole[*((_DWORD *)v4 + 12)])->DelTask(2);
    this->CreateObj((int (*)(int, int))CCBSystem::IsThreadExist, 0, 0, 0, v4 + 40);
    goto LABEL_16;
  }
  if ( !((CCBSystem *)this->m_pAttackSequen)->IsCmdEmpty(*((_DWORD *)v4 + 12)) )
    return 0;
  m_pControl = (CCBControl *)this->m_pControl;
  if ( m_pControl->m_bActive )
  {
    if ( ((CCBSystem *)m_pControl)->GetControl() == *((_DWORD *)v4 + 12) )
      ((CCBUI *)this->m_pControl)->GetState();
  }
  ((CCBStageRole *)this->m_pStage->m_pRole[*((_DWORD *)v4 + 12)])->DelTask(2);
  this->ClearEffect(this->m_nThread);
  return -1;
}

// 0x00514AE0
int CCBSystem::IsThreadExist(int a2)
{
  int m_nThread; // eax
  char *v4; // ebp
  int RoleIndex; // eax
  int v6; // edx
  int v7; // edi
  int (*v8)(CCBStage *, int); // eax
  char a3; // [esp+13h] [ebp-11h] BYREF
  int a4; // [esp+14h] [ebp-10h] BYREF
  _DWORD a7[3]; // [esp+18h] [ebp-Ch] BYREF

  m_nThread = this->m_nThread;
  a3 = 0;
  a4 = 0;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*(_DWORD *)&this->m_Thread[88 * m_nThread + 48], 1);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(14, v4 + 40, 0);
    v6 = *((_DWORD *)v4 + 11);
    v7 = RoleIndex;
    *((_DWORD *)v4 + 5) = RoleIndex;
    a7[0] = v6;
    a7[1] = *((_DWORD *)v4 + 12);
    a7[2] = *((_DWORD *)v4 + 13);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, a7, -1082130432, 0);
    if ( *((_DWORD *)v4 + 12) > 4u )
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBStage::ClearRoleAllTask, 0, 0, 0, a7, -1082130432, 1065353216);
      v8 = CCBStage::IsAllSubTaskFinished;
    }
    else
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBStage::ClearRoleAllTask, 0, 0, 0, a7, -1082130432, 1065353216);
      v8 = CCBStage::IsSubTaskFinished;
    }
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)v8, 0, 0, 0, a7, 0, 0x40000000);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBSystem::EndBattle, 0, 0, 0, a7, 0, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)sub_500220, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)sub_5004B0, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, a7, -1082130432, 0);
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v7);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(*((_DWORD *)v4 + 12));
    v4[37] = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
  if ( a3 == 1 )
  {
    if ( *((_DWORD *)v4 + 5) != -1 )
      ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514D60
int CCBSystem::GetThreadIndex(int a2)
{
  int m_nThread; // eax
  char *v4; // ebp
  int RoleIndex; // eax
  int v7; // edx
  int v8; // edi
  int v9; // [esp-4h] [ebp-2Ch]
  char a3; // [esp+13h] [ebp-15h] BYREF
  int v11; // [esp+14h] [ebp-14h] BYREF
  int a4; // [esp+18h] [ebp-10h] BYREF
  _DWORD a7[3]; // [esp+1Ch] [ebp-Ch] BYREF

  m_nThread = this->m_nThread;
  a3 = 0;
  a4 = 0;
  v11 = 0;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*(_DWORD *)&this->m_Thread[88 * m_nThread + 48], 1);
    if ( ((CCBRoleState *)this->m_pRoleState)->CheckVarianceRound(*((_DWORD *)v4 + 12), *((_DWORD *)v4 + 11), &v11) == 1 )
    {
      v9 = *((_DWORD *)v4 + 12);
      *((_DWORD *)v4 + 10) = 270;
      *((_DWORD *)v4 + 11) = v11;
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(v9);
      this->CreateObj((int (*)(int, int))CCBSystem::AddThread, 0, 0, 0, v4 + 40);
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(16, v4 + 40, 0);
    v7 = *((_DWORD *)v4 + 11);
    v8 = RoleIndex;
    *((_DWORD *)v4 + 5) = RoleIndex;
    a7[0] = v7;
    a7[1] = *((_DWORD *)v4 + 12);
    a7[2] = *((_DWORD *)v4 + 13);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ClearRoleAllTask, 0, 0, 0, a7, -1082130432, 1065353216);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ProcGrabStageRole, 0, 0, 0, a7, 1028443341, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)sub_4FFA90, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)sub_4FFCB0, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, a7, -1082130432, 0);
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v8);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(*((_DWORD *)v4 + 12));
    v4[37] = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
  if ( a3 == 1 )
  {
    ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514FE0
int CCBSystem::PassCmdToThread(int a2)
{
  int m_nThread; // eax
  char *v4; // edi
  int RoleIndex; // eax
  int v6; // ecx
  int v7; // ebp
  char a3; // [esp+13h] [ebp-1Dh] BYREF
  int a4; // [esp+14h] [ebp-1Ch] BYREF
  _DWORD a7[3]; // [esp+18h] [ebp-18h] BYREF
  int v12; // [esp+24h] [ebp-Ch] BYREF
  int v13; // [esp+28h] [ebp-8h]
  int SkillNum; // [esp+2Ch] [ebp-4h]

  a4 = 0;
  m_nThread = this->m_nThread;
  a3 = 0;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*(_DWORD *)&this->m_Thread[88 * m_nThread + 48], 1);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(17, v4 + 40, 0);
    v6 = *((_DWORD *)v4 + 11);
    v7 = RoleIndex;
    *((_DWORD *)v4 + 5) = RoleIndex;
    a7[0] = v6;
    a7[1] = *((_DWORD *)v4 + 12);
    a7[2] = *((_DWORD *)v4 + 13);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBStage::EndRoleAllTask, 0, 0, 0, a7, -1082130432, 1069547520);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)sub_500550, 0, 0, 0, a7, 0, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)sub_5007A0, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, a7, -1082130432, 0);
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v7);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(*((_DWORD *)v4 + 12));
    v13 = 0;
    SkillNum = 0;
    v12 = *((_DWORD *)v4 + 11);
    SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(v12);
    v13 = 1;
    if ( sub_4F7050((int)(v4 + 40)) )
      sub_4F7140((int)(v4 + 40));
    else
      CCBStageRole_PassCmd(&g_SceneMgr._gap_1888[792], &v12);
    v4[37] = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
  if ( a3 == 1 )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00515200
int CCBSystem::PassCmdToThread(int a2)
{
  int m_nThread; // eax
  char *v4; // ebp
  int RoleIndex; // eax
  int v7; // edx
  int v8; // edi
  int v9; // eax
  int v10; // edx
  CCBStage *m_pStage; // ecx
  int v12; // edi
  char a3; // [esp+13h] [ebp-49h] BYREF
  int a4; // [esp+14h] [ebp-48h] BYREF
  _DWORD a7[3]; // [esp+18h] [ebp-44h] BYREF
  _DWORD v16[3]; // [esp+24h] [ebp-38h] BYREF
  _DWORD v17[11]; // [esp+30h] [ebp-2Ch] BYREF

  a3 = 0;
  m_nThread = this->m_nThread;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    if ( !((CCBSystem *)this->m_pAttackSequen)->IsBusy() && !this->m_pRoleState->m_bFleeAlwaysSuccess )
    {
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
LABEL_5:
      this->ClearEffect(this->m_nThread);
      return 0;
    }
    ((CCBSystem *)this->m_pAttackSequen)->sub_4DB730(*((_DWORD *)v4 + 12));
    ((CCBRoleState *)this->m_pRoleState)->GetSpeedBonus(*((_DWORD *)v4 + 12));
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdCount(*((_DWORD *)v4 + 12));
    if ( this->m_pRoleState->m_bFleeAlwaysSuccess )
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(*((_DWORD *)v4 + 12));
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    v4[37] = 1;
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(20, v4 + 40, 0);
    v7 = *((_DWORD *)v4 + 11);
    v8 = RoleIndex;
    *((_DWORD *)v4 + 5) = RoleIndex;
    a7[0] = v7;
    a7[1] = *((_DWORD *)v4 + 12);
    a7[2] = *((_DWORD *)v4 + 13);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)sub_500C20, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, a7, -1082130432, 0);
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v8);
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 12)) + 30) = 1;
  }
  if ( (unsigned __int8)((CCBRoleState *)this->m_pRoleState)->GetForce(0)
    && (((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4), a3) )
  {
    ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 12)) + 30) = 0;
    this->ClearEffect(this->m_nThread);
    return 0;
  }
  else
  {
    if ( ((CCBSystem *)this->m_pAttackSequen)->IsCmdReady(*((_DWORD *)v4 + 12))
      || this->m_pRoleState->m_bFleeAlwaysSuccess )
    {
      ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
      if ( a3 )
      {
        ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
        this->CreateObj((int (*)(int, int))CCBSystem::PassCmdToTask, 0, 0, 0, v4 + 40);
        goto LABEL_5;
      }
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(*((_DWORD *)v4 + 12), 16)
      && !this->m_pRoleState->m_bFleeAlwaysSuccess )
    {
      ((CCBSystem *)this->m_pAttackSequen)->GetCmdData(*((_DWORD *)v4 + 12));
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    }
    if ( !((CCBSystem *)this->m_pAttackSequen)->IsCmdEmpty(*((_DWORD *)v4 + 12)) )
      return 0;
    ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
    if ( !a3 )
      return 0;
    ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 12)) + 30) = 0;
    memset(v17, 0, sizeof(v17));
    LOBYTE(v17[10]) = 1;
    v17[0] = 267;
    v9 = this->ProcProtect();
    v10 = *((_DWORD *)v4 + 12);
    m_pStage = (CCBStage *)this->m_pStage;
    v17[1] = v9;
    v17[2] = v10;
    v17[3] = -1;
    v12 = m_pStage->GetRoleIndex(26, v17, 1);
    if ( v12 != -1 )
    {
      memset(v16, 0, sizeof(v16));
      ((CCBStage *)this->m_pStage)->GetRoleName(v12, (int)sub_5024D0, 0, 0, 0, v16, 0, 1077936128);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v12);
    }
    this->ClearEffect(this->m_nThread);
    return -1;
  }
}

// 0x005155D0
int CCBSystem::PassCmdToTask(int a2)
{
  int m_nThread; // eax
  char *v4; // esi
  int RoleIndex; // eax
  int v6; // edx
  int v7; // ebp
  C2DSpark *m_p2DSpark; // ecx
  char a3; // [esp+13h] [ebp-11h] BYREF
  int a4; // [esp+14h] [ebp-10h] BYREF
  _DWORD a7[3]; // [esp+18h] [ebp-Ch] BYREF

  a3 = 0;
  a4 = 0;
  m_nThread = this->m_nThread;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*(_DWORD *)&this->m_Thread[88 * m_nThread + 48], 1);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(20, v4 + 40, 0);
    v6 = *((_DWORD *)v4 + 11);
    v7 = RoleIndex;
    *((_DWORD *)v4 + 5) = RoleIndex;
    a7[0] = v6;
    a7[1] = *((_DWORD *)v4 + 12);
    a7[2] = *((_DWORD *)v4 + 13);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)sub_500D50, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(v7, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, a7, -1082130432, 0);
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v7);
    v4[37] = 1;
  }
  ((CCBStage *)this->m_pStage)->DelTask(*((_DWORD *)v4 + 5), &a3, &a4);
  if ( a3 == 1 )
  {
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(*((_DWORD *)v4 + 12));
    ((CCBSystem *)this->m_pStage)->GetStageRole(*((_DWORD *)v4 + 5));
    if ( a4 )
    {
      m_p2DSpark = (C2DSpark *)this->m_p2DSpark;
      this->m_eState = 4;
      m_p2DSpark->CreateStars();
    }
    else
    {
      ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*((_DWORD *)v4 + 12), 0);
    }
    this->ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00515760
int CCBSystem::PassCmdViaThread(int a2)
{
  int m_nThread; // eax
  char *v4; // esi
  int RoleIndex; // ebx
  int v6; // ecx
  _DWORD a7[3]; // [esp+10h] [ebp-Ch] BYREF

  m_nThread = this->m_nThread;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( !this->m_Thread[88 * m_nThread + 37] )
  {
    ((CCBSystem *)this->m_pAttackSequen)->SetCmdParam(*(_DWORD *)&this->m_Thread[88 * m_nThread + 48], 0);
    ((CCBSystem *)this->m_pAttackSequen)->GetCmdPtr(*((_DWORD *)v4 + 12));
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(19, v4 + 40, 1);
    a7[2] = *((_DWORD *)v4 + 13);
    *((_DWORD *)v4 + 5) = RoleIndex;
    v6 = *((_DWORD *)v4 + 12);
    a7[0] = *((_DWORD *)v4 + 11);
    a7[1] = v6;
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)sub_5014E0, 0, 0, 0, a7, -1082130432, 0);
    ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, a7, -1082130432, 0);
    *((_DWORD *)v4 + 8) = *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 12)) + 872);
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
    v4[37] = 1;
  }
  if ( ((CCBSystem *)this->m_pAttackSequen)->IsBusy()
    || this->m_eState != CBS_END
    || *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 12)) + 872) > *((_DWORD *)v4 + 8) )
  {
    ((CCBRoleState *)this->m_pRoleState)->SetRoleFlag(*((_DWORD *)v4 + 12), 0);
    this->ClearEffect(this->m_nThread);
    *((_DWORD *)v4 + 8) = 0;
  }
  return 0;
}

// 0x00515940
int CCBSystem::CreateObj(int a2)
{
  int m_nThread; // eax
  char *v4; // edi
  int Obj; // edi

  m_nThread = this->m_nThread;
  v4 = (char *)&this->m_Thread[88 * m_nThread];
  if ( this->m_Thread[88 * m_nThread + 37] )
  {
    Obj = this->CreateObj(0, 0, 0x40u);
    this->ClearEffect(this->m_nThread);
    return Obj;
  }
  else
  {
    this->ProcAI(0.0);
    v4[37] = 1;
    return 0;
  }
}

// 0x005159A0
int CCBSystem::CreateObj(const char *a2, const char *a3, UINT a4)
{
  unsigned int v5; // eax
  CHAR *v6; // edi
  char *v7; // esi
  char v8; // cl
  unsigned int v9; // edx

  if ( !a2 )
    return MessageBoxA((HWND)g_pRoleSystem2, byte_17AC6DC, byte_17AC5DC, uType);
  if ( strlen(a2) >= 0xFF )
  {
    v9 = strlen(aTooManyCharact) + 1;
    qmemcpy(byte_17AC6DC, aTooManyCharact, 4 * (v9 >> 2));
    v7 = (char *)&aTooManyCharact[4 * (v9 >> 2)];
    v6 = (CHAR *)&byte_17AC6DC[4 * (v9 >> 2)];
    v8 = v9;
  }
  else
  {
    v5 = strlen(a2) + 1;
    qmemcpy(byte_17AC6DC, a2, 4 * (v5 >> 2));
    v7 = (char *)&a2[4 * (v5 >> 2)];
    v6 = (CHAR *)&byte_17AC6DC[4 * (v5 >> 2)];
    v8 = v5;
  }
  qmemcpy(v6, v7, v8 & 3);
  if ( a3 )
  {
    if ( strlen(a3) < 0xFF )
      strcpy(byte_17AC5DC, a3);
  }
  else
  {
    sprintf(byte_17AC5DC, aS_3, aPal3CombatSyst);
  }
  uType = a4;
  this->CreateObj((int (*)(int, int))CCBSystem::CreateObj, 0, 0, 0, 0);
  return 0;
}

// 0x00515AC0
char CCBSystem::CreateObj(int a2)
{
  int v2; // edx
  char *i; // eax

  v2 = 0;
  for ( i = this->m_Thread;
        !i[36]
     || *(int (**)(CCBSystem *, int))i != CCBSystem::PassCmdToThread
     || *(_DWORD *)i && (*((_DWORD *)i + 1) || *((_DWORD *)i + 2) || *((_DWORD *)i + 3))
     || *((_DWORD *)i + 12) != a2;
        i += 88 )
  {
    if ( ++v2 >= 1024 )
      return 0;
  }
  return 1;
}

// 0x00515B20
int CCBSystem::CreateObj(
        CCBSystem *this,
        int (*a2)(int _this, int a2),
        int a3,
        int a4,
        int a5,
        const void *a6)
{
  int v8; // eax
  char *i; // ecx
  char *v10; // ebp

  if ( (int)this->m_dwIDHolder >= 1023 )
    MessageBoxA(0, &byte_5DE9E4, 0, 0x30u);
  if ( (char *)a2 == (char *)CCBSystem::CheckBattleEnd
    && (!CCBSystem::CheckBattleEnd || !a3 && !a4 && !a5)
    && sub_515C90((char *)this, (int)CCBSystem::CheckBattleEnd, 0, 0, 0) > 0 )
  {
    return 0;
  }
  v8 = 0;
  for ( i = &this->m_Thread[36]; *i; i += 88 )
  {
    if ( ++v8 >= 1024 )
      return -1;
  }
  v10 = (char *)this + 88 * v8;
  v10[188] = 1;
  v10[189] = 0;
  *((_DWORD *)v10 + 38) = a2;
  *((_DWORD *)v10 + 39) = a3;
  *((_DWORD *)v10 + 40) = a4;
  *((_DWORD *)v10 + 41) = a5;
  *((_DWORD *)v10 + 42) = this->ProcProtect();
  *((_DWORD *)v10 + 45) = 0;
  *((_DWORD *)v10 + 43) = -1;
  if ( a6 )
    qmemcpy(v10 + 192, a6, 0x2Cu);
  ++this->m_dwIDHolder;
  return *((_DWORD *)v10 + 42);
}

// 0x00515C50
char CCBSystem::ClearEffect(int idx)
{
  memset(&this->m_Thread[88 * idx], 0, 0x58u);
  --this->m_dwIDHolder;
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

  v3 = (_DWORD *)operator new(0x2598u);
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

// 0x00515DD0
void * CCBSystem::DestroyObj(CCBSystem *Block, char a2)
{
  nullsub_3(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00515DF0
void * CCBSystem::DestroyObj(CCBSystem *Block, char a2)
{
  sub_4E0330(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00515E40
// attributes: thunk
int CCBSystem::DestroyObj()
{
  return ?DestroyObj@CCBSystem@@AAE_NPAPAVCCBUI@@@Z();
}

// 0x00515E50
int CCBSystem::DestroyObj()
{
  dword_17ACE14 = 1094713344;
  return 1094713344;
}

// 0x00515E60
// attributes: thunk
void CCBSystem::DestroyObj()
{
  ?DestroyObj@CCBSystem@@AAE_NPAPAVCCBEditor@@@Z();
}

// 0x00515E70
void CCBSystem::DestroyObj()
{
  flt_17ACE10 = 12.0 + 12.0;
}

// 0x00515E80
// attributes: thunk
int CCBSystem::DestroyObj()
{
  return CCBSystem::InitObj();
}

// 0x00515E90
int CCBSystem::InitObj()
{
  dword_17ACE1C[0] = 119;
  dword_17ACE20 = 314;
  dword_17ACE24 = 510;
  dword_17ACE28 = 707;
  return 707;
}

// 0x00515ED0
// attributes: thunk
int CCBSystem::InitObj()
{
  return ?InitObj@CCBSystem@@AAE_NPAVCCBControl@@@Z();
}

// 0x00515EE0
int CCBSystem::InitObj()
{
  dword_17ACE2C[0] = 519;
  dword_17ACE30 = 519;
  dword_17ACE34 = 519;
  dword_17ACE38 = 519;
  return 519;
}

// 0x00515F20
// attributes: thunk
int CCBSystem::InitObj()
{
  return ?InitObj@CCBSystem@@AAE_NPAVCCBAttackSequen@@@Z();
}

// 0x00515F30
int CCBSystem::InitObj()
{
  dword_17ACE3C[0] = 128;
  dword_17ACE40 = 323;
  dword_17ACE44 = 519;
  dword_17ACE48 = 716;
  return 716;
}

// 0x00515F70
// attributes: thunk
int CCBSystem::InitObj()
{
  return ?InitObj@CCBSystem@@AAE_NPAVCCBAI@@@Z();
}

// 0x00515F80
int CCBSystem::InitObj()
{
  dword_17ACE4C[0] = 545;
  dword_17ACE50 = 545;
  dword_17ACE54 = 545;
  dword_17ACE58 = 545;
  return 545;
}

// 0x00515FC0
// attributes: thunk
int CCBSystem::InitObj()
{
  return ?InitObj@CCBSystem@@AAE_NPAVCEffMgr@@@Z();
}

// 0x00515FD0
int CCBSystem::InitObj()
{
  dword_17ACE5C[0] = 121;
  dword_17ACE60 = 316;
  dword_17ACE64 = 512;
  dword_17ACE68 = 709;
  return 709;
}
