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
int sub_512BA0(...);
int sub_5158F0(...);
int sub_515C90(...);
int sub_5163D0(...);
int sub_51D5C0(...);
int sub_53E970(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Co_4[];
extern char aEffectCombat10[];
extern char aPal3CombatSyst[];
extern char aTooManyCharact[];
extern unsigned char byte_17AC5DC;
extern unsigned char byte_17AC6DC;
extern unsigned char byte_17AC7F0;
extern unsigned char byte_5DE9E4;
extern int dword_17A990C;
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
extern int dword_5DC3DC;
extern float flt_17AC7DC;
extern float flt_17AC7EC;
extern float flt_17ACA78;
extern float flt_17ACE10;
extern int nullsub_3;
extern int nullsub_68;

// 0x004DB3A0
// attributes: thunk
int __cdecl CCBSystem::InitCmdTable1_thunk()
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
int __cdecl CCBSystem::InitCmdTable2_thunk()
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
int __cdecl CCBSystem::InitCmdTable3_thunk()
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
  *(_DWORD *)this->m_pUtil = a2;
  *(_DWORD *)&this->m_pUtil[4] = *(_DWORD *)(a2 + 4);
  *(_DWORD *)&this->m_pUtil[8] = *(_DWORD *)(a2 + 16);
  return this;
}

// 0x004DB4C0
int CCBSystem::ResetFlags()
{
  this->m_pUtil[452] = 1;
  this->m_pUtil[453] = 1;
  this->m_pUtil[454] = 1;
  memset(&this->m_pUtil[12], 0, 0x1B8u);
  return 0;
}

// 0x004DB4F0
char CCBSystem::DestroySubsystems()
{
  void (***v3)(_DWORD, _DWORD); // ecx
  int i; // esi
  void (***v5)(_DWORD, _DWORD); // ecx
  void (***v6)(_DWORD, int); // ecx
  int v7; // ebx
  int j; // esi
  int v9; // eax

  this->ResetFlags();
  if ( !*(_DWORD *)this->m_pUtil )
    return 0;
  if ( !*(_DWORD *)&this->m_pUtil[4] )
    return 0;
  if ( !*(_DWORD *)&this->m_pUtil[8] )
    return 0;
  sub_4DBB80(this);
  sub_4DB9F0(this);
  if ( dword_17A990C == 1 )
  {
    v3 = *(void (****)(_DWORD, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_pUtil + 4) + 72);
    (**v3)(v3, 0);
    for ( i = 76; i < 120; i += 4 )
    {
      v5 = *(void (****)(_DWORD, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_pUtil + 4) + i);
      (**v5)(v5, 0);
    }
    return 1;
  }
  else
  {
    v6 = *(void (****)(_DWORD, int))(*(_DWORD *)(*(_DWORD *)this->m_pUtil + 4) + 72);
    (**v6)(v6, 1);
    v7 = 0;
    for ( j = 76; j < 120; j += 4 )
    {
      v9 = *(_DWORD *)this->m_pUtil;
      if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)this->m_pUtil + 16) + v7 + 577) )
        (***(void (****)(_DWORD, int))(*(_DWORD *)(v9 + 4) + j))(*(_DWORD *)(*(_DWORD *)(v9 + 4) + j), 1);
      else
        (***(void (****)(_DWORD, _DWORD))(*(_DWORD *)(v9 + 4) + j))(*(_DWORD *)(*(_DWORD *)(v9 + 4) + j), 0);
      v7 += 892;
    }
    return 1;
  }
}

// 0x004DB640
int CCBSystem::CalcSpeed(int roleIdx, int a2)
{
  int v2; // ecx

  return 5 * (CCBRoleState::GetSpeedBonus(*(CCBRoleState **)(v2 + 8), roleIdx) + 4);
}

// 0x004DB660
int CCBSystem::GetCmdSlot(int idx)
{
  char *v2; // ebx
  int result; // eax

  v2 = (char *)&this->m_pUtil[40 * idx];
  v2[44] = idx->CalcSpeed(0);
  result = idx->CalcSpeed(1);
  v2[45] = result;
  return result;
}

// 0x004DB690
char CCBSystem::GetCmdType(int idx)
{
  return this->m_pUtil[40 * idx + 48];
}

// 0x004DB6A0
bool CCBSystem::IsBusy()
{
  int v2; // [esp+4h] [ebp+4h]

  return *(_DWORD *)&this->m_pUtil[40 * v2 + 32] >= 11500;
}

// 0x004DB6C0
bool CCBSystem::IsCmdReady(int idx)
{
  return *(_DWORD *)&this->m_pUtil[40 * idx + 36] >= 11500;
}

// 0x004DB6E0
bool CCBSystem::IsCmdEmpty(int idx)
{
  return this->m_pUtil[40 * idx + 46] == 0;
}

// 0x004DB700
int CCBSystem::GetCmdValue(int idx)
{
  return *(_DWORD *)&this->m_pUtil[40 * idx + 40];
}

// 0x004DB710
char * CCBSystem::GetCmdPtr(int idx)
{
  char *result; // eax

  result = (char *)&this->m_pUtil[40 * idx];
  *((_DWORD *)result + 8) = 0;
  *((_DWORD *)result + 9) = 0;
  result[46] = 0;
  return result;
}

// 0x004DB730
char * CCBSystem::CCBSystem::sub_4DB730(int a2)
{
  char *result; // eax

  result = (char *)&this->m_pUtil[40 * a2];
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

  result = (char *)&this->m_pUtil[40 * idx];
  *((_DWORD *)result + 8) = v3;
  *((_DWORD *)result + 9) = v4;
  result[46] = v5;
  return result;
}

// 0x004DB780
int CCBSystem::GetCmdCount(int idx)
{
  char v3; // [esp+8h] [ebp+8h]

  this->m_pUtil[40 * idx + 45] = v3;
  return 5 * idx;
}

// 0x004DB7A0
int CCBSystem::ProcessAllCmds()
{
  int v2; // edi
  int v3; // esi
  char *v4; // ebx
  CCBStageRole *v5; // ecx
  _BYTE *v6; // ecx
  double v7; // st7
  float v9; // [esp+10h] [ebp-Ch]
  int v10; // [esp+14h] [ebp-8h]

  v2 = 0;
  v9 = 100000000.0;
  v10 = -1;
  v3 = 0;
  v4 = (char *)&this->m_pUtil[36];
  do
  {
    v5 = (CCBStageRole *)*(CCBStageRole **)&this->m_pUtil[8];
    if ( v5->m_pStage[v3 + 577] )
    {
      if ( !v5->IsActive(v2) )
      {
        v6 = (_BYTE *)*(_BYTE **)&this->m_pUtil[8];
        if ( !v6[v3 + 1432]
          && !*(_BYTE *)(v6->InitUI(v2) + 879)
          && CCBRoleState::SetRoleField(*(CCBRoleState **)&this->m_pUtil[8], v2, 0) > 0 )
        {
          if ( v4[10] )
            v7 = (double)(11500 - *(_DWORD *)v4) / ((double)(unsigned __int8)v4[9] * 50.0);
          else
            v7 = (double)(11500 - *((_DWORD *)v4 - 1)) / ((double)(unsigned __int8)v4[8] * 50.0) + 10000.0;
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
    v4 += 40;
  }
  while ( v3 < 9812 );
  return v10;
}

// 0x004DB8B0
char * CCBSystem::GetCmdString(int idx)
{
  char *result; // eax

  result = (char *)&this->m_pUtil[40 * idx];
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

  this->m_pUtil[453] = v2;
  return result;
}

// 0x004DB920
int CCBSystem::SetCmdParam(int idx, int value)
{
  this->m_pUtil[40 * idx + 47] = value;
  return 5 * idx;
}

// 0x004DC5B0
int CCBSystem::GetControl()
{
  return *(_DWORD *)&this->m_pUtil[32];
}

// 0x004FC8F0
char CCBSystem::GetStageRole(int idx)
{
  char *v2; // esi

  v2 = (char *)&this->m_pUtil[2632 * idx];
  v2[2796] = 0;
  memset(v2 + 184, 0, 0xA00u);
  *((_DWORD *)v2 + 44) = 0;
  --*(_DWORD *)&this->m_pUtil[156];
  return 1;
}

// 0x004FC940
char CCBSystem::GetStageRoleByIdx(int idx)
{
  char *v2; // eax

  v2 = (char *)&this->m_pUtil[2632 * idx];
  *((_DWORD *)v2 + 43) = 3;
  *((_DWORD *)v2 + 50) = 3;
  *((float *)v2 + 52) = *(float *)(*(_DWORD *)this->m_pUtil + 80);
  return 1;
}

// 0x00500170
int CCBSystem::EndBattle()
{
  int v2; // eax
  char *v3; // edi
  char *v4; // ebp
  int v5; // eax

  v2 = 2632 * *(_DWORD *)&this->m_pUtil[160];
  v3 = (char *)&this->m_pUtil[v2 + 2760];
  v4 = (char *)&this->m_pUtil[80 * *(_DWORD *)&this->m_pUtil[164] + 184 + v2];
  if ( !CCBStageRole::IsReady(*(_DWORD *)&this->m_pUtil[4 * *(_DWORD *)v3 + 24], *(_DWORD *)&this->m_pUtil[v2 + 2744]) )
    goto LABEL_7;
  if ( !v4[41] && CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)&this->m_pUtil[4 * *(_DWORD *)v3 + 24]) )
  {
    CCBStageRole::GetState(*(CCBStageRole **)&this->m_pUtil[4 * *(_DWORD *)v3 + 24]);
    v5 = *(_DWORD *)&this->m_pUtil[4 * *(_DWORD *)v3 + 24];
    *(_DWORD *)(v5 + 6632) = *(_DWORD *)(v5 + 6636);
    v4[41] = 1;
  }
  if ( v4[43] == 1 || CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)&this->m_pUtil[4 * *(_DWORD *)v3 + 24]) )
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
  char *v4; // esi
  int v5; // ebx
  char *v6; // edi

  v1 = (char *)&this->m_pUtil[192];
  v2 = 1024;
  do
  {
    v3 = v1;
    v1 += 88;
    --v2;
    memset(v3, 0, 0x2Cu);
  }
  while ( v2 );
  v4 = (char *)&this->m_pUtil[90264];
  v5 = 11;
  do
  {
    v6 = v4;
    v4 += 52;
    --v5;
    memset(v6, 0, 0x2Cu);
  }
  while ( v5 );
  memset(this, 0, sizeof(CCBSystem));
  *(_DWORD *)&this->m_pUtil[124] = 0;
  this->m_pUtil[132] = 0;
  this->m_pUtil[133] = 0;
  *(_DWORD *)&this->m_pUtil[128] = 0;
  this->m_pUtil[116] = 1;
  *(_DWORD *)&this->m_pUtil[120] = 1;
  this->m_pUtil[134] = 1;
  return (int)this->m_pUtil;
}

// 0x00512580
int CCBSystem::ProcDialog(int _this)
{
  _DWORD *v3; // ecx

  v3 = (_DWORD *)(this + 64);
  *v3 = 0;
  v3[1] = 0;
  memset((void *)(this + 152), 0, 0x16000u);
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 88) = 0;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)(this + 120) = 1;
  *(_DWORD *)(this + 124) = 1;
  *(_DWORD *)(this + 140) = 0;
  *(_DWORD *)(this + 144) = -1;
  *(_BYTE *)(this + 116) = 1;
  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 80) = 0;
  *(_DWORD *)(this + 92) = 0;
  *(_DWORD *)(this + 100) = 0;
  *(_DWORD *)(this + 104) = 0;
  *(_BYTE *)(this + 135) = 1;
  return 0;
}

// 0x005125E0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char CCBSystem::ProcNormalAttack(CCBSystem *this)
{
  void *v2; // eax
  std::codecvt_base *v3; // ecx
  CCBSystem *v4; // eax
  char result; // al
  UIWnd *v6; // eax
  CCBUI *v7; // eax
  _DWORD *v8; // eax
  CCBRoleState *v9; // eax
  CCBSystem *v10; // eax
  CCBAttackSequen *inited; // eax
  CCBStage *v12; // eax
  CCBStage *v13; // eax
  _DWORD *v14; // eax
  CCBControl *v15; // eax
  CCBAI *v16; // eax
  CCBAI *v17; // eax
  SceneMgr *v18; // eax
  CCBStageCam *m_pCam; // edx
  int p_OrthoSize; // edx
  CEffMgr *v21; // eax
  SceneMgr *v22; // eax
  CCBStageCam *v23; // ecx
  int v24; // ecx
  CEffMgr *v25; // eax
  int v26; // eax
  C2DSpark *v27; // eax
  C3DSpark *v28; // eax
  C3DSpark *v29; // eax
  int *m_pES; // ecx
  CEffectSimple *v31; // eax
  char pExceptionObject[1024]; // [esp+Ch] [ebp-100Ch] BYREF
  char ArgList[1024]; // [esp+40Ch] [ebp-C0Ch] BYREF
  char v34[1024]; // [esp+80Ch] [ebp-80Ch] BYREF
  char v35[1024]; // [esp+C0Ch] [ebp-40Ch] BYREF
  int v36; // [esp+1014h] [ebp-4h]

  CCBSystem::ProcDialog((int)this);
  v2 = (void *)operator new(1u);
  v36 = 0;
  if ( v2 )
    v4 = (CCBSystem *)sub_51D5C0(v2, (int)this);
  else
    v4 = 0;
  this->m_pUtil = v4;
  v36 = -1;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_4, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = v3->codecvt_base::do_always_noconv();
  if ( result )
  {
    v6 = (UIWnd *)operator new(0xA48u);
    v36 = 1;
    if ( v6 )
      v7 = (CCBUI *)v6->ctor_60A0((int)this);
    else
      v7 = 0;
    v36 = -1;
    this->m_pUI = v7;
    if ( !v7 )
    {
      qmemcpy(
        pExceptionObject,
        Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_4, 2504),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    result = sub_5163D0(v7);
    if ( result )
    {
      v8 = (_DWORD *)operator new(0x50A4u);
      v36 = 2;
      if ( v8 )
        v9 = (CCBRoleState *)sub_4EC680(v8, (int)this);
      else
        v9 = 0;
      v36 = -1;
      this->m_pRoleState = v9;
      if ( !v9 )
      {
        qmemcpy(
          pExceptionObject,
          Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_4, 2504),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      result = sub_4EC700((int)v9);
      if ( result )
      {
        v10 = (CCBSystem *)operator new(0x1C8u);
        v36 = 3;
        if ( v10 )
          inited = (CCBAttackSequen *)v10->InitCmd((int)this);
        else
          inited = 0;
        v36 = -1;
        this->m_pAttackSequen = inited;
        if ( !inited )
        {
          qmemcpy(
            pExceptionObject,
            Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_4, 2504),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        result = std::codecvt_base::do_always_noconv((std::codecvt_base *)inited);
        if ( result )
        {
          v12 = (CCBStage *)operator new(0xA48B0u);
          v36 = 4;
          if ( v12 )
            v13 = (CCBStage *)v12->CCBStage((int)this);
          else
            v13 = 0;
          v36 = -1;
          this->m_pStage = v13;
          if ( !v13 )
          {
            qmemcpy(
              pExceptionObject,
              Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_4, 2504),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          result = v13->Reset();
          if ( result )
          {
            v14 = (_DWORD *)operator new(0x570u);
            v36 = 5;
            if ( v14 )
              v15 = (CCBControl *)sub_4DC160(v14, this);
            else
              v15 = 0;
            v36 = -1;
            this->m_pControl = v15;
            if ( !v15 )
            {
              qmemcpy(
                pExceptionObject,
                Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_4, 2504),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            result = std::codecvt_base::do_always_noconv((std::codecvt_base *)v15);
            if ( result )
            {
              v16 = (CCBAI *)operator new(0xE50u);
              v36 = 6;
              if ( v16 )
                v17 = (CCBAI *)v16->Create(this);
              else
                v17 = 0;
              v36 = -1;
              this->m_pAI = v17;
              if ( !v17 )
              {
                qmemcpy(v34, Logger::FormatException((Logger *)v35, aCNewFailed, aDProjectPal3Co_4, 2504), sizeof(v34));
                _CxxThrowException(v34, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              result = std::codecvt_base::do_always_noconv((std::codecvt_base *)v17);
              if ( result )
              {
                this->m_pES = (CEffectSystem *)g_Input.KeyInfo[178].Data;
                CCBSystem::ProcAI((int)this, 1.0);
                result = this->CreateObj2(&this->m_pEditor);
                if ( result )
                {
                  v18 = (SceneMgr *)operator new(0xA930u);
                  v36 = 7;
                  if ( v18 )
                  {
                    m_pCam = (CCBStageCam *)this->m_pStage->m_pCam;
                    if ( m_pCam )
                      p_OrthoSize = (int)&m_pCam->OrthoSize;
                    else
                      p_OrthoSize = 0;
                    v21 = (CEffMgr *)v18->Create(g_Input.KeyInfo[177].Data, p_OrthoSize, (int)this);
                  }
                  else
                  {
                    v21 = 0;
                  }
                  this->m_pEffMgr = v21;
                  v22 = (SceneMgr *)operator new(0xA930u);
                  v36 = 8;
                  if ( v22 )
                  {
                    v23 = (CCBStageCam *)this->m_pStage->m_pCam;
                    if ( v23 )
                      v24 = (int)&v23->OrthoSize;
                    else
                      v24 = 0;
                    v25 = (CEffMgr *)v22->Create(g_Input.KeyInfo[177].Data, v24, (int)this);
                  }
                  else
                  {
                    v25 = 0;
                  }
                  this->m_pATSEffMgr = v25;
                  v26 = operator new(0x5870u);
                  v36 = 9;
                  if ( v26 )
                    v27 = (C2DSpark *)v26->C2DSpark(g_Input.KeyInfo[120].Data, g_Input.KeyInfo[120].HoldTime);
                  else
                    v27 = 0;
                  this->m_p2DSpark = v27;
                  v28 = (C3DSpark *)operator new(0x3E30u);
                  v36 = 10;
                  if ( v28 )
                    v29 = (C3DSpark *)v28->C3DSpark();
                  else
                    v29 = 0;
                  m_pES = (int *)this->m_pES;
                  this->m_p3DSpark = v29;
                  v31 = (CEffectSimple *)sub_4C5980(m_pES, 1);
                  this->m_pEffectSimple = v31;
                  CEffectSystem::CEffectSystem((CEffectSystem *)v31, (int)aEffectCombat10);
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
char sub_512BA0(int _this)
{
  int v2; // ecx
  void *v3; // edi
  std::codecvt_base *v4; // ecx
  void *v5; // edi
  char *v6; // ecx
  void *v7; // edi
  std::codecvt_base *v8; // ecx
  void *v9; // edi
  int v10; // ecx
  int v11; // ecx
  std::codecvt_base *v12; // ecx
  void *v13; // ecx
  std::codecvt_base *v14; // ecx
  gbRefObject **v15; // edi
  void *v16; // edi
  void *v17; // edi
  void *v18; // ecx

  v2 = *(_DWORD *)(this + 20);
  if ( !v2 )
    return 0;
  v2->Create();
  v3 = (void *)*(void **)(this + 20);
  if ( v3 )
  {
    nullsub_3(*(void **)(this + 20));
    operator delete(v3);
  }
  *(_DWORD *)(this + 20) = 0;
  v4 = *(std::codecvt_base **)(this + 12);
  if ( !v4 )
    return 0;
  v4->codecvt_base::do_always_noconv();
  v5 = (void *)*(void **)(this + 12);
  if ( v5 )
  {
    nullsub_3(*(void **)(this + 12));
    operator delete(v5);
  }
  *(_DWORD *)(this + 12) = 0;
  v6 = (char *)*(char **)(this + 16);
  if ( !v6 )
    return 0;
  sub_4EC7D0(v6);
  v7 = (void *)*(void **)(this + 16);
  if ( v7 )
  {
    nullsub_3(*(void **)(this + 16));
    operator delete(v7);
  }
  *(_DWORD *)(this + 16) = 0;
  v8 = *(std::codecvt_base **)(this + 8);
  if ( !v8 )
    return 0;
  v8->codecvt_base::do_always_noconv();
  v9 = (void *)*(void **)(this + 8);
  if ( v9 )
  {
    sub_4DC1B0(*(void **)(this + 8));
    operator delete(v9);
  }
  *(_DWORD *)(this + 8) = 0;
  v10 = *(_DWORD *)(this + 4);
  if ( !v10 )
    return 0;
  (*(void (**)(int))(*(_DWORD *)v10 + 12))(v10);
  v11 = *(_DWORD *)(this + 4);
  if ( v11 )
    (*(void (**)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
  *(_DWORD *)(this + 4) = 0;
  v12 = *(std::codecvt_base **)(this + 24);
  if ( !v12 )
    return 0;
  v12->codecvt_base::do_always_noconv();
  v13 = (void *)*(void **)(this + 24);
  if ( v13 )
    v13->DestroyObj(1);
  *(_DWORD *)(this + 24) = 0;
  if ( !*(_DWORD *)(this + 28) )
    return 0;
  sub_4E03F0();
  v14 = *(std::codecvt_base **)(this + 28);
  if ( v14 )
    v14->DestroyObj(1);
  *(_DWORD *)(this + 28) = 0;
  if ( !*(_DWORD *)this )
    return 0;
  v14->codecvt_base::do_always_noconv();
  if ( *(_DWORD *)this )
    CCBSystem::DestroyObj(*(void **)this, 1);
  v15 = *(gbRefObject ***)(this + 44);
  *(_DWORD *)this = 0;
  if ( v15 )
  {
    sub_4CDAE0(v15);
    operator delete(v15);
    *(_DWORD *)(this + 44) = 0;
  }
  v16 = (void *)*(void **)(this + 48);
  if ( v16 )
  {
    sub_4CDAE0(*(gbRefObject ***)(this + 48));
    operator delete(v16);
    *(_DWORD *)(this + 48) = 0;
  }
  v17 = (void *)*(void **)(this + 52);
  if ( v17 )
  {
    C2DSpark::~C2DSpark(*(_DWORD *)(this + 52));
    operator delete(v17);
    *(_DWORD *)(this + 52) = 0;
  }
  v18 = (void *)*(void **)(this + 56);
  if ( v18 )
  {
    v18->ProcCoAttack(1);
    *(_DWORD *)(this + 56) = 0;
  }
  return 1;
}

// 0x00512D40
void * CCBSystem::ProcCoAttack(CCBSystem *Block, char a2)
{
  C3DSpark::~C3DSpark((int)Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00512D60
char CCBSystem::ProcWeaponSkill()
{
  CCBUI *m_pUI; // ecx
  CCBControl *m_pControl; // ecx
  CCBRoleState *m_pRoleState; // ecx
  CCBSystem *m_pAttackSequen; // ecx
  CCBStage *m_pStage; // ecx
  CCBAI *m_pAI; // ecx
  CCBEditor *m_pEditor; // ecx
  int v10; // edi
  int i; // ebp
  CCBRoleState *v12; // ecx

  if ( !this->m_pUtil || !CCBLineupWindow::IsFaceOnInitPos() )
    return 0;
  m_pUI = (CCBUI *)this->m_pUI;
  if ( !m_pUI || !CCBUI::CreateParaWindow((int)m_pUI) )
    return 0;
  m_pControl = (CCBControl *)this->m_pControl;
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
    if ( !m_pEditor || !sub_4E0430(m_pEditor) )
      return 0;
  }
  if ( !this->m_pEffMgr || !sub_4CDB60() )
    return 0;
  if ( !this->m_pATSEffMgr || !sub_4CDB60() )
    return 0;
  C2DSpark::CreateTrack((int)this->m_p2DSpark->m_Spark, 0);
  C2DSpark::CreateStars(this->m_p2DSpark);
  C3DSpark::DestroyAll(this->m_p3DSpark);
  v10 = 0;
  this->CreateObj(CCBSystem::Message, 0, 0, 0, 0);
  CCBSystem::GetDeltaTime((CCBSystem *)this->m_pAttackSequen);
  for ( i = 0; i < 4460; i += 892 )
  {
    v12 = (CCBRoleState *)this->m_pRoleState;
    if ( v12->m_Role[0].sModel[i + 5] )
    {
      *(_BYTE *)(v12->InitUI(v10) + 876) = 0;
      *(_BYTE *)(CCBRoleState::InitUI(this->m_pRoleState, v10) + 877) = 0;
    }
    ++v10;
  }
  sub_4C6170(this->m_pEffectSimple);
  gbSceneGraph::ResetBladeMgr(*(gbSceneGraph **)(g_Input.KeyInfo[177].Data + 448));
  if ( BYTE1(this->m_pRoleState->m_bWeSneakAttackEnemy) && *((_BYTE *)CEffectSystem::DestroyAllEffect() + 4) )
  {
    CCBStageCam::ClearFinishedTask((int)this->m_pStage->m_pCamControl, 20);
    HIBYTE(this->m_bFiveNimbus) = 1;
    return 1;
  }
  else
  {
    CCBStageCam::ClearFinishedTask((int)this->m_pStage->m_pCamControl, 0);
    HIBYTE(this->m_bFiveNimbus) = 1;
    return 1;
  }
}

// 0x00512F40
char CCBSystem::ProcMagicWait(int _this, int a2, char a3)
{
  int v4; // ecx
  unsigned int v5; // ebx
  char *v6; // edi
  int v8; // [esp+1Ch] [ebp+8h]
  char v9; // [esp+23h] [ebp+Fh]

  this->ProcDialog();
  v4 = *(_DWORD *)(this + 128) + 1;
  *(_BYTE *)(this + 133) = a3;
  *(_BYTE *)(this + 116) = 0;
  *(_DWORD *)(this + 120) = 2;
  *(_DWORD *)(this + 124) = 1;
  *(_DWORD *)(this + 128) = v4;
  ++*(_DWORD *)&g_SceneMgr.m_info[51524];
  *(_DWORD *)(this + 112) = a2;
  v9 = CCBSystem::ProcWeaponSkill((CCBSystem *)this);
  UICursor::IRender();
  v5 = 0;
  v6 = (char *)&g_SceneMgr.m_info[916];
  v8 = 0;
  do
  {
    if ( *(_BYTE *)(v8 + *(_DWORD *)(this + 16) + 577) && (*((_DWORD *)v6 - 3) == 8114 || *(_DWORD *)v6 == 8114) )
    {
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FF) < (int)102.39999 )
        CCBRoleState::ProcessRound(*(CCBRoleState **)(this + 16), v5);
    }
    v6 += 1408;
    ++v5;
    v8 += 892;
  }
  while ( (int)v6 < (int)&g_SceneMgr.m_info[7956] );
  return v9;
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
  CCBSystem::ProcMagic((int)this);
  this->IsFriendDoSkill();
  CCBAttackSequen::Update(this->m_pAttackSequen);
  CCBRoleState::Update(this->m_pRoleState);
  CCBAI::Update(this->m_pAI);
  CCBStage::Update(this->m_pStage);
  CCBControl::Update(this->m_pControl);
  if ( BYTE1(this->m_bFiveNimbus) )
  {
    m_pEditor = (CCBEditor *)this->m_pEditor;
    if ( m_pEditor )
      CCBUI::Update((CCBUI *)m_pEditor);
  }
  a2 = this->m_DeltaTime;
  C2DSpark::Render((int)this->m_p2DSpark->m_Spark, a2);
  a2a = this->m_DeltaTime;
  C3DSpark::Update(this->m_p3DSpark, a2a);
  LOBYTE(result) = CCBSystem::ProcDefence((int)this);
  return result;
}

// 0x00513120
char CCBSystem::RenderCheck()
{
  char result; // al

  result = this->m_pUtil[135];
  if ( result )
  {
    this->m_pUtil[135] = 0;
  }
  else
  {
    CCBStage::EditorUpdate(*(char **)&this->m_pUtil[20]);
    return C2DSpark::DestroyAll(*(_DWORD *)&this->m_pUtil[52]);
  }
  return result;
}

// 0x00513150
char CCBSystem::ProcMagic(int _this)
{
  char v2; // bl
  int v3; // ebp
  int i; // edi
  int v5; // eax
  int v6; // edi
  int j; // ebp
  void *v8; // ecx
  int v9; // edi
  int k; // ebp
  void *v11; // ecx
  int v12; // edi
  int m; // ebp
  _BYTE *v14; // ecx

  v2 = 0;
  if ( dword_17A990C == 1 )
  {
    if ( MEMORY[0xBFC6E4] == 1 || MEMORY[0xBFC6F4] == 1 )
    {
      v3 = 0;
      for ( i = 24; i < 68; i += 4 )
      {
        if ( sub_50A4B0(*(int **)(i + *(_DWORD *)(this + 20))) )
        {
          CCBStage::DoTask(*(_DWORD **)(this + 20), v3);
          v2 = 1;
        }
        ++v3;
      }
      if ( !v2 )
      {
        CCBStage::DoTask(*(_DWORD **)(this + 20), -1);
        if ( CCBStageScene::LoadFlingNode(*(float **)(*(_DWORD *)(this + 20) + 20)) )
          *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 20) + 20) + 964) = 1;
      }
    }
    if ( (MEMORY[0xBFC6D8] & 0xF) != 1 && (MEMORY[0xBFC6E8] & 0xF) != 1 )
    {
      CCBStage::DoTask(*(_DWORD **)(this + 20), -1);
      *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 20) + 20) + 964) = 0;
    }
  }
  LOBYTE(v5) = 1;
  if ( dword_17B30E4 != 1 )
  {
    if ( MEMORY[0xBFC7D4] == 1 && *(_DWORD *)(this + 16) )
    {
      v6 = 0;
      for ( j = 0; j < 4460; j += 892 )
      {
        v8 = (void *)*(void **)(this + 16);
        if ( *((_BYTE *)v8 + j + 577) )
        {
          *(_BYTE *)(v8->InitUI(v6) + 837) = 0;
          *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 16), v6) + 832) = 0;
          *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 16), v6) + 833) = 0;
          *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 16), v6) + 834) = 0;
          *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 16), v6) + 835) = 0;
        }
        ++v6;
      }
      LOBYTE(v5) = 1;
    }
    if ( MEMORY[0xBFC814] == 1 )
    {
      v9 = 0;
      for ( k = 0; k < 4460; k += 892 )
      {
        v11 = (void *)*(void **)(this + 16);
        if ( *((_BYTE *)v11 + k + 577) )
        {
          *(_BYTE *)(v11->InitUI(v9) + 876) = 1;
          *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 16), v9) + 877) = 0;
        }
        ++v9;
      }
      LOBYTE(v5) = 1;
    }
    if ( MEMORY[0xBFC824] == 1 )
    {
      v12 = 0;
      for ( m = 0; m < 4460; m += 892 )
      {
        v14 = (_BYTE *)*(_BYTE **)(this + 16);
        LOBYTE(v5) = v14[m + 577];
        if ( (_BYTE)v5 )
        {
          *(_BYTE *)(v14->InitUI(v12) + 877) = 1;
          v5 = CCBRoleState::InitUI(*(void **)(this + 16), v12);
          *(_BYTE *)(v5 + 876) = 0;
        }
        ++v12;
      }
    }
  }
  return v5;
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
    gbSceneGraph::ResetBladeMgr(*(gbSceneGraph **)&g_pGfxManager[448]);
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
  this->m_pUtil[132] = flag;
  do
  {
    *(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v3) + 837) = this->m_pUtil[132];
    *(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v3) + 832) = this->m_pUtil[132];
    *(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v3) + 833) = this->m_pUtil[132];
    *(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v3) + 834) = this->m_pUtil[132];
    result = CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v3++);
    *(_BYTE *)(result + 835) = this->m_pUtil[132];
  }
  while ( v3 < 5 );
  return result;
}

// 0x00513420
char CCBSystem::ProcFlee(char a2)
{
  LOBYTE(this->m_bFiveNimbus) = a2;
  return a2;
}

// 0x00513430
char CCBSystem::ProcDefence(int _this)
{
  int v2; // ebx
  int v3; // ebp
  int i; // edi
  int *v5; // eax
  int v6; // edx
  double v7; // st7
  char result; // al

  if ( (byte_17AC7F0 & 1) == 0 )
  {
    byte_17AC7F0 |= 1u;
    flt_17AC7EC = *(float *)(this + 80);
  }
  Combat::LogMessage(
    *(_DWORD *)(*(_DWORD *)(this + 20) + 68),
    5,
    75,
    "Thread=%d, StageTask=%d",
    *(_DWORD *)(this + 140),
    *(_DWORD *)(*(_DWORD *)(this + 20) + 156));
  Combat::LogMessage(*(_DWORD *)(*(_DWORD *)(this + 20) + 68), 5, 90, "Times of Combat=%d", *(_DWORD *)(this + 128));
  Combat::LogMessage(*(_DWORD *)(*(_DWORD *)(this + 20) + 68), 5, 105, "TimeFund=%f", *(float *)(this + 80));
  Combat::LogMessage(*(_DWORD *)(*(_DWORD *)(this + 20) + 68), 5, 120, "DeltaTime=%f", *(double *)(this + 64));
  Combat::LogMessage(
    *(_DWORD *)(*(_DWORD *)(this + 20) + 68),
    5,
    195,
    "Effect objects %d",
    *(_DWORD *)(*(_DWORD *)(this + 44) + 43292));
  Combat::LogMessage(
    *(_DWORD *)(*(_DWORD *)(this + 20) + 68),
    5,
    210,
    "Effect Timer %f",
    *(float *)(*(_DWORD *)(this + 44) + 43304));
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
    v5 = (int *)(*(_DWORD *)(*(_DWORD *)(this + 20) + i) + 6584);
    dword_17AC7E0 = *v5;
    dword_17AC7E4 = v5[1];
    dword_17AC7E8 = v5[2];
    v6 = *(_DWORD *)(*(_DWORD *)(this + 20) + i);
    v7 = *(float *)(v6 + 6632);
    flt_17AC7DC = *(float *)(v6 + 6632);
    result = Combat::LogMessage(
               *(_DWORD *)(*(_DWORD *)(this + 20) + 68),
               380,
               v3,
               "Role%d x=%f, z=%f, rot=%f",
               v2++,
               *(float *)&dword_17AC7E0,
               *(float *)&dword_17AC7E8,
               v7);
    v3 += 15;
  }
  return result;
}

// 0x00513600
void CCBSystem::ProcAI(int _this, float a2)
{
  int v3; // ecx
  _DWORD *v4; // ecx
  _DWORD *v5; // ecx
  int v6; // ecx
  int i; // eax
  gbVisNode *v8; // ecx

  v3 = *(_DWORD *)(this + 32);
  *(float *)(this + 108) = a2;
  *(float *)(v3 + 332) = a2;
  v4 = (_DWORD *)*(_DWORD **)(this + 44);
  if ( v4 )
    sub_4CDC50(v4, SLODWORD(a2));
  v5 = (_DWORD *)*(_DWORD **)(this + 48);
  if ( v5 )
    sub_4CDC50(v5, 1065353216);
  v6 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( *(_BYTE *)(v6 + *(_DWORD *)(this + 16) + 577) )
      *(float *)(*(_DWORD *)(*(_DWORD *)(this + 20) + i) + 268) = a2;
    v6 += 892;
  }
  v8 = (gbVisNode *)*(gbVisNode **)(*(_DWORD *)(*(_DWORD *)(this + 20) + 20) + 616);
  if ( v8 )
    v8->SetTimeScale(a2);
  if ( *(_BYTE *)(this + 133) )
    sub_4E05B0(a2);
}

// 0x005136A0
int CCBSystem::ProcProtect()
{
  unsigned __int32 v1; // eax

  v1 = this->m_bPXVariance + 1;
  this->m_bPXVariance = v1;
  if ( v1 >= 0x7FFFFFFF )
    this->m_bPXVariance = 1;
  return this->m_bPXVariance;
}

// 0x005136D0
char CCBSystem::ProcMessage(int _this, int a2)
{
  int i; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // edx

  i = CCBRoleState::InitUI(*(void **)(this + 16), 0);
  if ( *(_DWORD *)(i + 84) == a2 )
  {
    i = CCBRoleState::InitUI(*(void **)(this + 16), 0);
    *(_DWORD *)(i + 84) = -1;
  }
  v4 = *(_DWORD *)(this + 8);
  if ( *(_BYTE *)(v4 + 36) )
  {
    i = CCBSystem::GetControl((_DWORD *)v4);
    if ( i == a2 )
    {
      CCBUI::GetState(*(_BYTE **)(this + 8));
      v5 = 0;
      for ( i = 24; i < 68; i += 4 )
      {
        if ( *(_BYTE *)(v5 + *(_DWORD *)(this + 16) + 577) )
        {
          *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 20) + i) + 280) = 0;
          *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 20) + i) + 274) = 0;
        }
        v5 += 892;
      }
    }
  }
  CCBStage::IsTaskValidButNotFinish((_BYTE *)i, *(_DWORD *)(this + 20), a2);
  CCBSystem::GetCmdPtr(*(char **)(this + 12), a2);
  sub_4DB9C0(*(_DWORD **)(this + 12), a2, 0);
  *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 20) + 4 * a2 + 24) + 280) = 0;
  *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 20) + 4 * a2 + 24) + 274) = 0;
  CCBStageRole::ClearAniMsg(*(_DWORD *)(*(_DWORD *)(this + 20) + 4 * a2 + 24), 0, 1.0);
  v6 = CCBRoleState::InitUI(*(void **)(this + 16), a2);
  memset((void *)(v6 + 589), 0, 0x18u);
  *(_WORD *)(v6 + 613) = 0;
  *(_BYTE *)(v6 + 615) = 0;
  memset((void *)(v6 + 616), 0, 0x34u);
  *(_WORD *)(v6 + 668) = 0;
  memset((void *)(v6 + 670), 0, 0x34u);
  *(_WORD *)(v6 + 722) = 0;
  *(_BYTE *)(v6 + 588) = 0;
  return CCBStageRole::DangerForceRelease(*(_BYTE **)(*(_DWORD *)(this + 20) + 4 * a2 + 24), 0);
}

// 0x005137F0
int CCBSystem::IsFriendDoSkill()
{
  __int32 v2; // ebp
  __int32 *p_m_bLockCam; // esi
  int result; // eax

  v2 = 0;
  p_m_bLockCam = (__int32 *)&this->m_bLockCam;
  do
  {
    if ( *((_BYTE *)p_m_bLockCam + 36) == 1 )
    {
      this->m_bAuto = v2;
      result = ((int (*)(char *, _DWORD))*p_m_bLockCam)((char *)this + p_m_bLockCam[1], 0);
      this->m_bAuto = -1;
    }
    ++v2;
    p_m_bLockCam += 22;
  }
  while ( v2 < 1024 );
  this->m_bAuto = -1;
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
  if ( (unsigned __int8)CCBRoleState::GetForce(this->m_pRoleState, 0) || this->m_bPause != 2 )
  {
    m_pControl = (CCBControl *)this->m_pControl;
    if ( LOBYTE(m_pControl->m_bActive) )
      CCBUI::GetState((CCBUI *)m_pControl);
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
      if ( !this->m_pRoleState->m_Role[0].sModel[v17 + 5]
        || !CCBStageRole::ForceDelTaskByPFN(*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + v3)) )
      {
        goto LABEL_39;
      }
      if ( sub_4ECB20(this->m_pRoleState, v5) )
      {
        CCBSystem::GetDeltaTime((CCBSystem *)this->m_pAttackSequen);
        return 0;
      }
      if ( CCBSystem::GetCmdType((CCBSystem *)this->m_pAttackSequen, v5) == 1
        && CCBRoleState::IsRoleAlive(this->m_pRoleState, v5) == 1
        && CCBStageRole::IsActive((CCBStageRole *)this->m_pRoleState, v5) == 1
        && CCBSystem::IsBusy((CCBSystem *)this->m_pAttackSequen) )
      {
        if ( CCBRoleState::GetRoleField(this->m_pRoleState, v5, 17)
          || CCBRoleState::GetRoleField(this->m_pRoleState, v5, 14) )
        {
          goto LABEL_38;
        }
        if ( !*(_BYTE *)(CCBRoleState::InitUI(this->m_pRoleState, v5) + 837)
          && !CCBRoleState::GetRoleField(this->m_pRoleState, v5, 18)
          && !CCBRoleState::GetRoleField(this->m_pRoleState, v5, 19) )
        {
          sub_4F7FC0((int)this->m_pRoleState->m_sCombatDialog, v5);
          if ( !*(_BYTE *)(CCBRoleState::InitUI(this->m_pRoleState, v5) + 877)
            || (v6 = CCBAI::HandleFriendAffirmative(this->m_pAI, v5, 1),
                *(_BYTE *)(CCBRoleState::InitUI(this->m_pRoleState, v5) + 877) = 0,
                !v6) )
          {
            if ( !*(_BYTE *)(CCBRoleState::InitUI(this->m_pRoleState, v5) + 876) )
            {
              dword_5DC3DC = v5;
              sub_4DC3F0((char *)this->m_pControl, v5);
              return 0;
            }
            if ( *((_BYTE *)v4 + 40) )
            {
              CCBAI::HandlePlayerNormalAttack(this->m_pAI, v5, (int)v4);
              for ( j = 0; j < 5; ++j )
              {
                inited = CCBRoleState::InitUI(this->m_pRoleState, j);
                *(_BYTE *)(inited + 876) = 0;
              }
            }
            else
            {
              CCBAI::HandleFriendAffirmative(this->m_pAI, v5, 0);
              for ( k = 0; k < 5; ++k )
              {
                v10 = CCBRoleState::InitUI(this->m_pRoleState, k);
                *(_BYTE *)(v10 + 876) = 0;
              }
            }
          }
          goto LABEL_39;
        }
        sub_4F7FC0((int)this->m_pRoleState->m_sCombatDialog, v5);
        CCBAI::HandleEnemyChaos(this->m_pAI, v5);
      }
      if ( CCBSystem::GetCmdType((CCBSystem *)this->m_pAttackSequen, v5) != 1
        || CCBRoleState::IsRoleAlive(this->m_pRoleState, v5) != 1
        || CCBStageRole::IsActive((CCBStageRole *)this->m_pRoleState, v5)
        || !CCBSystem::IsBusy((CCBSystem *)this->m_pAttackSequen) )
      {
        goto LABEL_39;
      }
      if ( CCBRoleState::GetRoleField(this->m_pRoleState, v5, 17)
        || CCBRoleState::GetRoleField(this->m_pRoleState, v5, 14)
        || *(_BYTE *)(CCBRoleState::InitUI(this->m_pRoleState, v5) + 879) )
      {
LABEL_38:
        CCBSystem::GetCmdData((CCBSystem *)this->m_pAttackSequen, v5);
        goto LABEL_39;
      }
      CCBAI::Render(this->m_pAI, v5);
LABEL_39:
      v3 = v18 + 4;
      v17 += 892;
      ++v5;
      v4 = (__int32 *)i + 13;
      v11 = v18 + 4 < 68;
      v18 += 4;
      if ( !v11 )
        return 0;
    }
  }
  CCBSystem::GetDeltaTime((CCBSystem *)this->m_pAttackSequen);
  v13 = (CCBControl *)this->m_pControl;
  if ( LOBYTE(v13->m_CmdData.bSrcRole[2]) )
    p_bValid = (int *)&v13->m_InputData.bValid;
  Control = CCBSystem::GetControl((CCBSystem *)v13);
  if ( *(_BYTE *)(CCBRoleState::InitUI(this->m_pRoleState, Control) + 877)
    || (v15 = CCBSystem::GetControl((CCBSystem *)this->m_pControl),
        *(_BYTE *)(CCBRoleState::InitUI(this->m_pRoleState, v15) + 876)) )
  {
    dword_5DC3DC = -1;
    CCBSystem::GetDeltaTime((CCBSystem *)this->m_pAttackSequen);
    CCBUI::GetState((CCBUI *)this->m_pControl);
    return 0;
  }
  if ( CCBSystem::GetControl((CCBSystem *)this->m_pControl) != dword_5DC3DC || !p_bValid )
    return 0;
  if ( CCBRoleState::GetRoleField(this->m_pRoleState, dword_5DC3DC, 14) )
  {
    CCBUI::GetState((CCBUI *)this->m_pControl);
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

// 0x00513EB0
int CCBSystem::Message(int a2)
{
  int RoleIndex; // edi

  BYTE2(this->m_pFightInfo->nRoleWillNotBeAttack) = 0;
  RoleIndex = CCBStage::GetRoleIndex(this->m_pStage, 3, 0, 1);
  if ( RoleIndex != -1 )
  {
    if ( BYTE1(this->m_pRoleState->m_bWeSneakAttackEnemy)
      || (CCBStage::GetRoleName(
            this->m_pStage,
            RoleIndex,
            (int)CCBStage::IsSubTaskFinished,
            0,
            0,
            0,
            0,
            -1082130432,
            1082130432),
          CCBStage::GetRoleName(
            this->m_pStage,
            RoleIndex,
            (int)CCBStage::IsAllSubTaskFinished,
            0,
            0,
            0,
            0,
            0,
            1082130432),
          LOBYTE(this->m_pRoleState->m_bWeSneakAttackEnemy)) )
    {
      CCBStage::GetRoleName(this->m_pStage, RoleIndex, (int)CCBStage::IsIdle, 0, 0, 0, 0, 0, 1077936128);
    }
    CCBSystem::GetStageRoleByIdx((CCBSystem *)this->m_pStage, RoleIndex);
  }
  this->CreateObj((int (*)(int, int))CCBSystem::CheckBattleEnd, 0, 0, 0, 0);
  this->ClearEffect(this->m_bAuto);
  return 0;
}

// 0x00513FD0
int CCBSystem::IsRoleWaitForFlee(int _this, int a2)
{
  int v3; // eax
  int v4; // ebp
  _DWORD *v5; // edi
  int v6; // eax
  int RoleIndex; // eax
  int v8; // edi
  char a3; // [esp+13h] [ebp-15h] BYREF
  int v11; // [esp+14h] [ebp-14h] BYREF
  int a4; // [esp+18h] [ebp-10h] BYREF
  int a7; // [esp+1Ch] [ebp-Ch] BYREF
  int v14; // [esp+20h] [ebp-8h]
  int v15; // [esp+24h] [ebp-4h]

  v3 = *(_DWORD *)(this + 144);
  a3 = 0;
  a4 = 0;
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    v5 = (_DWORD *)(this + 88 * v3 + 192);
    if ( !sub_4F7820(*(char **)(this + 16), (int)v5) )
    {
LABEL_11:
      CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
      goto LABEL_12;
    }
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 1);
    if ( CCBRoleState::CheckVarianceRound(*(CCBRoleState **)(this + 16), *(_DWORD *)(v4 + 48), 0, &v11) == 1 )
    {
      v6 = *(_DWORD *)(v4 + 48);
      *v5 = 270;
      *(_DWORD *)(v4 + 44) = v11;
      CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), v6);
      CCBSystem::CreateObj((CCBSystem *)this, CCBSystem::AddThread, 0, 0, 0, (const void *)(v4 + 40));
LABEL_12:
      CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
      return 0;
    }
    RoleIndex = CCBStage::GetRoleIndex(*(CCBStage **)(this + 20), 11, (const void *)(v4 + 40), 0);
    v8 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    if ( RoleIndex != -1 )
    {
      a7 = 0;
      v14 = 0;
      v15 = 0;
      v14 = *(_DWORD *)(v4 + 48);
      v15 = *(_DWORD *)(v4 + 52);
      CCBStage::GetRoleName(
        *(CCBStage **)(this + 20),
        RoleIndex,
        (int)CCBStage::ProcFiveLienupFadeIn,
        0,
        0,
        0,
        &a7,
        -1082130432,
        0);
      CCBStage::GetRoleName(
        *(CCBStage **)(this + 20),
        v8,
        (int)CCBStage::ProcShowSneakAttackState,
        0,
        0,
        0,
        &a7,
        -1082130432,
        0);
      CCBStage::GetRoleName(*(CCBStage **)(this + 20), v8, (int)CCBStage::HandleKeyCtrl, 0, 0, 0, &a7, -1082130432, 0);
      CCBStage::GetRoleName(*(CCBStage **)(this + 20), v8, (int)CCBStage::ProcShowName, 0, 0, 0, &a7, -1082130432, 0);
      CCBStage::GetRoleName(
        *(CCBStage **)(this + 20),
        v8,
        (int)CCBStage::ProcFiveLienupFadeOut,
        0,
        0,
        0,
        &a7,
        -1082130432,
        0);
      CCBSystem::GetStageRoleByIdx(*(CCBSystem **)(this + 20), v8);
    }
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    *(_BYTE *)(v4 + 37) = 1;
  }
  CCBStage::DelTask(*(CCBStage **)(this + 20), *(_DWORD *)(v4 + 20), &a3, &a4);
  if ( a3 == 1 )
  {
    if ( *(_DWORD *)(v4 + 20) != -1 )
      CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    goto LABEL_11;
  }
  return 0;
}

// 0x00514220
int CCBSystem::AddThread(int _this, int a2)
{
  int v3; // eax
  int v4; // ebp
  int RoleIndex; // eax
  int v6; // edi
  char v8; // [esp+13h] [ebp-11h] BYREF
  int v9; // [esp+14h] [ebp-10h] BYREF
  int v10; // [esp+18h] [ebp-Ch] BYREF
  int v11; // [esp+1Ch] [ebp-8h]
  int v12; // [esp+20h] [ebp-4h]

  v3 = *(_DWORD *)(this + 144);
  v8 = 0;
  v9 = 0;
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200), 1);
    CCBSystem::GetDeltaTime(*(CCBSystem **)(this + 12));
    CCBRoleState::InitRoleFiveMagic(*(CCBRoleState **)(this + 16), v4 + 40);
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 12, (const void *)(v4 + 40), 0);
    v6 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    if ( RoleIndex == -1 )
    {
      *(_BYTE *)(v4 + 37) = 1;
      CCBSystem::GetDeltaTime(*(CCBSystem **)(this + 12));
      CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
      CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
      return 0;
    }
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v11 = *(_DWORD *)(v4 + 48);
    v12 = *(_DWORD *)(v4 + 52);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      &v10,
      -1082130432,
      0);
    v10 = -1;
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)sub_502000, 0, 0, 0, &v10, -1082130432, 1065353216);
    v10 = 0;
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)sub_4FF360, 0, 0, 0, &v10, -1082130432, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)CCBStage::ProcShowDamage, 0, 0, 0, &v10, -1082130432, 0);
    v10 = -1;
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)sub_5020D0, 0, 0, 0, &v10, -1082130432, 1065353216);
    v10 = 0;
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v6,
      (int)CCBStage::ClearRoleAllTask,
      0,
      0,
      0,
      &v10,
      -1082130432,
      1065353216);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)sub_4FF560, 0, 0, 0, &v10, 0, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)CCBStage::ProcShowCost, 0, 0, 0, &v10, -1082130432, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)sub_4FF560, 0, 0, 0, &v10, -1082130432, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)sub_502000, 0, 0, 0, &v10, -1082130432, 1065353216);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v6,
      (int)CCBStage::ProcShowCombatDialog,
      0,
      0,
      0,
      &v10,
      -1082130432,
      0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v6, (int)sub_5020D0, 0, 0, 0, &v10, -1082130432, 1065353216);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v6,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      &v10,
      -1082130432,
      0);
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v6);
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    *(_BYTE *)(v4 + 37) = 1;
  }
  CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v8, &v9);
  if ( v8 == 1 )
  {
    if ( *(_DWORD *)(v4 + 20) != -1 )
      CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    CCBSystem::GetDeltaTime(*(CCBSystem **)(this + 12));
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00514610
int CCBSystem::DelThread(int _this, int a2)
{
  int v3; // eax
  int v4; // ebp
  int v5; // ecx
  int RoleIndex; // eax
  int v7; // edi
  char v9; // [esp+13h] [ebp-11h] BYREF
  int v10; // [esp+14h] [ebp-10h] BYREF
  int v11; // [esp+18h] [ebp-Ch] BYREF
  int v12; // [esp+1Ch] [ebp-8h]
  int v13; // [esp+20h] [ebp-4h]

  v3 = *(_DWORD *)(this + 144);
  v9 = 0;
  v10 = 0;
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200), 1);
    *(_BYTE *)(v4 + 80) = 1;
    *(_DWORD *)(v4 + 48) = 0;
    *(_DWORD *)(v4 + 40) = 269;
    v5 = *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 16), 0) + 528);
    *(_DWORD *)(v4 + 52) = -1;
    *(_DWORD *)(v4 + 44) = v5;
    CCBRoleState::GetRoleNum(*(CCBRoleState **)(this + 16), (int *)(v4 + 40));
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 11, (const void *)(v4 + 40), 0);
    v7 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    if ( RoleIndex != -1 )
    {
      v11 = 0;
      v12 = 0;
      v13 = 0;
      v12 = *(_DWORD *)(v4 + 48);
      v13 = *(_DWORD *)(v4 + 52);
      CCBStage::GetRoleName(
        *(_DWORD **)(this + 20),
        RoleIndex,
        (int)CCBStage::ProcFiveLienupFadeIn,
        0,
        0,
        0,
        &v11,
        -1082130432,
        0);
      CCBStage::GetRoleName(
        *(_DWORD **)(this + 20),
        v7,
        (int)CCBStage::ClearRoleAllTask,
        0,
        0,
        0,
        &v11,
        -1082130432,
        1065353216);
      CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)sub_4FFED0, 0, 0, 0, &v11, 0, 0);
      CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)sub_4FFF60, 0, 0, 0, &v11, -1082130432, 0);
      CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)CCBSystem::EndBattle, 0, 0, 0, &v11, -1082130432, 0);
      CCBStage::GetRoleName(
        *(_DWORD **)(this + 20),
        v7,
        (int)CCBStage::ProcFiveLienupFadeOut,
        0,
        0,
        0,
        &v11,
        -1082130432,
        0);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v7);
    }
    *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 16), *(_DWORD *)(v4 + 48)) + 536) = 0;
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    *(_BYTE *)(v4 + 37) = 1;
  }
  CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v9, &v10);
  if ( v9 == 1 )
  {
    if ( *(_DWORD *)(v4 + 20) != -1 )
      CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00514870
int CCBSystem::GetSameThreadNum(int _this, int a2)
{
  int v3; // eax
  _DWORD *v4; // edi
  int v6; // ecx
  int v7; // [esp-4h] [ebp-14h]
  int a4; // [esp+Ch] [ebp-4h] BYREF

  a4 = 0;
  v3 = *(_DWORD *)(this + 144);
  v4 = (_DWORD *)(this + 88 * v3 + 152);
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    if ( CCBRoleState::CheckVarianceRound(
           *(CCBRoleState **)(this + 16),
           *(_DWORD *)(this + 88 * v3 + 200),
           *(_DWORD *)(this + 88 * v3 + 196),
           &a4) == 1 )
    {
      v7 = v4[12];
      v4[10] = 270;
      v4[11] = a4;
      CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), v7);
      CCBSystem::CreateObj((CCBSystem *)this, CCBSystem::AddThread, 0, 0, 0, v4 + 10);
LABEL_16:
      CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
      return 0;
    }
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), v4[12], 0);
    if ( !CCBSystem::IsBusy(*(CCBSystem **)(this + 12)) )
    {
      CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
      return -1;
    }
    CCBSystem::sub_4DB730(*(CCBSystem **)(this + 12), v4[12]);
    if ( sub_4F76C0(*(_DWORD **)(this + 16), v4[12], v4[11]) >= 4 )
    {
      CCBSystem::GetCmdData(*(CCBSystem **)(this + 12), v4[12]);
    }
    else
    {
      CCBSystem::CalcSpeed(v4[12], 1);
      CCBSystem::GetCmdCount(*(CCBSystem **)(this + 12), v4[12]);
    }
    CCBStageRole::DelTask(*(CCBStageRole **)(*(_DWORD *)(this + 20) + 4 * v4[12] + 24), 4);
    *((_BYTE *)v4 + 37) = 1;
  }
  if ( (unsigned __int8)CCBRoleState::GetForce(*(CCBRoleState **)(this + 16), 0) )
  {
LABEL_12:
    CCBStageRole::DelTask(*(CCBStageRole **)(*(_DWORD *)(this + 20) + 4 * v4[12] + 24), 2);
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
    return 0;
  }
  if ( CCBRoleState::GetRoleField(*(CCBRoleState **)(this + 16), v4[12], 15) )
  {
    CCBSystem::GetCmdData(*(CCBSystem **)(this + 12), v4[12]);
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), v4[12], 0);
    goto LABEL_12;
  }
  if ( CCBSystem::IsCmdReady(*(CCBSystem **)(this + 12), v4[12]) )
  {
    CCBStageRole::DelTask(*(CCBStageRole **)(*(_DWORD *)(this + 20) + 4 * v4[12] + 24), 2);
    CCBSystem::CreateObj((CCBSystem *)this, CCBSystem::IsThreadExist, 0, 0, 0, v4 + 10);
    goto LABEL_16;
  }
  if ( !CCBSystem::IsCmdEmpty(*(CCBSystem **)(this + 12), v4[12]) )
    return 0;
  v6 = *(_DWORD *)(this + 8);
  if ( *(_BYTE *)(v6 + 36) )
  {
    if ( CCBSystem::GetControl((CCBSystem *)v6) == v4[12] )
      CCBUI::GetState(*(CCBUI **)(this + 8));
  }
  CCBStageRole::DelTask(*(CCBStageRole **)(*(_DWORD *)(this + 20) + 4 * v4[12] + 24), 2);
  CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
  return -1;
}

// 0x00514AE0
int CCBSystem::IsThreadExist(int _this, int a2)
{
  int v3; // eax
  int v4; // ebp
  int RoleIndex; // eax
  int v6; // edx
  int v7; // edi
  void *v8; // eax
  char v10; // [esp+13h] [ebp-11h] BYREF
  int v11; // [esp+14h] [ebp-10h] BYREF
  _DWORD v12[3]; // [esp+18h] [ebp-Ch] BYREF

  v3 = *(_DWORD *)(this + 144);
  v10 = 0;
  v11 = 0;
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200), 1);
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 14, (const void *)(v4 + 40), 0);
    v6 = *(_DWORD *)(v4 + 44);
    v7 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    v12[0] = v6;
    v12[1] = *(_DWORD *)(v4 + 48);
    v12[2] = *(_DWORD *)(v4 + 52);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      v12,
      -1082130432,
      0);
    if ( *(_DWORD *)(v4 + 48) > 4u )
    {
      CCBStage::GetRoleName(
        *(_DWORD **)(this + 20),
        v7,
        (int)CCBStage::ClearRoleAllTask,
        0,
        0,
        0,
        v12,
        -1082130432,
        1065353216);
      v8 = (void *)CCBStage::IsAllSubTaskFinished;
    }
    else
    {
      CCBStage::GetRoleName(
        *(_DWORD **)(this + 20),
        v7,
        (int)CCBStage::ClearRoleAllTask,
        0,
        0,
        0,
        v12,
        -1082130432,
        1065353216);
      v8 = (void *)CCBStage::IsSubTaskFinished;
    }
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)v8, 0, 0, 0, v12, 0, 0x40000000);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)CCBSystem::EndBattle, 0, 0, 0, v12, 0, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)sub_500220, 0, 0, 0, v12, -1082130432, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)sub_5004B0, 0, 0, 0, v12, -1082130432, 0);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v7,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      v12,
      -1082130432,
      0);
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v7);
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    *(_BYTE *)(v4 + 37) = 1;
  }
  CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v10, &v11);
  if ( v10 == 1 )
  {
    if ( *(_DWORD *)(v4 + 20) != -1 )
      CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00514D60
int CCBSystem::GetThreadIndex(int _this, int a2)
{
  int v3; // eax
  _DWORD *v4; // ebp
  int RoleIndex; // eax
  int v7; // edx
  int v8; // edi
  int v9; // [esp-4h] [ebp-2Ch]
  char a3; // [esp+13h] [ebp-15h] BYREF
  int v11; // [esp+14h] [ebp-14h] BYREF
  int a4; // [esp+18h] [ebp-10h] BYREF
  _DWORD a7[3]; // [esp+1Ch] [ebp-Ch] BYREF

  v3 = *(_DWORD *)(this + 144);
  a3 = 0;
  a4 = 0;
  v11 = 0;
  v4 = (_DWORD *)(this + 88 * v3 + 152);
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200), 1);
    if ( CCBRoleState::CheckVarianceRound(*(CCBRoleState **)(this + 16), v4[12], v4[11], &v11) == 1 )
    {
      v9 = v4[12];
      v4[10] = 270;
      v4[11] = v11;
      CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), v9);
      CCBSystem::CreateObj((CCBSystem *)this, CCBSystem::AddThread, 0, 0, 0, v4 + 10);
      CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
      return 0;
    }
    RoleIndex = CCBStage::GetRoleIndex(*(CCBStage **)(this + 20), 16, v4 + 10, 0);
    v7 = v4[11];
    v8 = RoleIndex;
    v4[5] = RoleIndex;
    a7[0] = v7;
    a7[1] = v4[12];
    a7[2] = v4[13];
    CCBStage::GetRoleName(
      *(CCBStage **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      a7,
      -1082130432,
      0);
    CCBStage::GetRoleName(
      *(CCBStage **)(this + 20),
      v8,
      (int)CCBStage::ClearRoleAllTask,
      0,
      0,
      0,
      a7,
      -1082130432,
      1065353216);
    CCBStage::GetRoleName(*(CCBStage **)(this + 20), v8, (int)CCBStage::ProcGrabStageRole, 0, 0, 0, a7, 1028443341, 0);
    CCBStage::GetRoleName(*(CCBStage **)(this + 20), v8, (int)sub_4FFA90, 0, 0, 0, a7, -1082130432, 0);
    CCBStage::GetRoleName(*(CCBStage **)(this + 20), v8, (int)sub_4FFCB0, 0, 0, 0, a7, -1082130432, 0);
    CCBStage::GetRoleName(
      *(CCBStage **)(this + 20),
      v8,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      a7,
      -1082130432,
      0);
    CCBSystem::GetStageRoleByIdx(*(CCBSystem **)(this + 20), v8);
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), v4[12]);
    *((_BYTE *)v4 + 37) = 1;
  }
  CCBStage::DelTask(*(CCBStage **)(this + 20), v4[5], &a3, &a4);
  if ( a3 == 1 )
  {
    CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), v4[5]);
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), v4[12], 0);
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00514FE0
int CCBSystem::PassCmdToThread(int _this, int a2)
{
  int v3; // eax
  int v4; // edi
  int RoleIndex; // eax
  int v6; // ecx
  int v7; // ebp
  char v9; // [esp+13h] [ebp-1Dh] BYREF
  int v10; // [esp+14h] [ebp-1Ch] BYREF
  _DWORD v11[3]; // [esp+18h] [ebp-18h] BYREF
  int v12; // [esp+24h] [ebp-Ch] BYREF
  int v13; // [esp+28h] [ebp-8h]
  int SkillNum; // [esp+2Ch] [ebp-4h]

  v10 = 0;
  v3 = *(_DWORD *)(this + 144);
  v9 = 0;
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200), 1);
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 17, (const void *)(v4 + 40), 0);
    v6 = *(_DWORD *)(v4 + 44);
    v7 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    v11[0] = v6;
    v11[1] = *(_DWORD *)(v4 + 48);
    v11[2] = *(_DWORD *)(v4 + 52);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      v11,
      -1082130432,
      0);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v7,
      (int)CCBStage::EndRoleAllTask,
      0,
      0,
      0,
      v11,
      -1082130432,
      1069547520);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)sub_500550, 0, 0, 0, v11, 0, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)sub_5007A0, 0, 0, 0, v11, -1082130432, 0);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v7,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      v11,
      -1082130432,
      0);
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v7);
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    v13 = 0;
    SkillNum = 0;
    v12 = *(_DWORD *)(v4 + 44);
    SkillNum = g_GDB->GDB_GetSkillNum(v12);
    v13 = 1;
    if ( sub_4F7050(v4 + 40) )
      sub_4F7140(v4 + 40);
    else
      CCBStageRole_PassCmd(&g_SceneMgr.m_info[7072], (int)&v12);
    *(_BYTE *)(v4 + 37) = 1;
  }
  CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v9, &v10);
  if ( v9 == 1 )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00515200
int CCBSystem::PassCmdToThread(int _this, int a2)
{
  int v3; // eax
  int v4; // ebp
  int RoleIndex; // eax
  int v7; // edx
  int v8; // edi
  int v9; // eax
  int v10; // edx
  CCBStage *v11; // ecx
  int v12; // edi
  char a3; // [esp+13h] [ebp-49h] BYREF
  int a4; // [esp+14h] [ebp-48h] BYREF
  _DWORD a7[3]; // [esp+18h] [ebp-44h] BYREF
  _DWORD v16[3]; // [esp+24h] [ebp-38h] BYREF
  _DWORD v17[11]; // [esp+30h] [ebp-2Ch] BYREF

  a3 = 0;
  v3 = *(_DWORD *)(this + 144);
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    if ( !CCBSystem::IsBusy(*(CCBSystem **)(this + 12)) && !*(_BYTE *)(*(_DWORD *)(this + 16) + 549) )
    {
      CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
LABEL_5:
      CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
      return 0;
    }
    CCBSystem::sub_4DB730(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    CCBRoleState::GetSpeedBonus(*(CCBRoleState **)(this + 16), *(_DWORD *)(v4 + 48));
    CCBSystem::GetCmdCount(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    if ( *(_BYTE *)(*(_DWORD *)(this + 16) + 549) )
      CCBSystem::GetCmdData(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    *(_BYTE *)(v4 + 37) = 1;
    RoleIndex = CCBStage::GetRoleIndex(*(CCBStage **)(this + 20), 20, (const void *)(v4 + 40), 0);
    v7 = *(_DWORD *)(v4 + 44);
    v8 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    a7[0] = v7;
    a7[1] = *(_DWORD *)(v4 + 48);
    a7[2] = *(_DWORD *)(v4 + 52);
    CCBStage::GetRoleName(
      *(CCBStage **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      a7,
      -1082130432,
      0);
    CCBStage::GetRoleName(*(CCBStage **)(this + 20), v8, (int)sub_500C20, 0, 0, 0, a7, -1082130432, 0);
    CCBStage::GetRoleName(
      *(CCBStage **)(this + 20),
      v8,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      a7,
      -1082130432,
      0);
    CCBSystem::GetStageRoleByIdx(*(CCBSystem **)(this + 20), v8);
    *(_BYTE *)(CCBRoleState::InitUI(*(CCBRoleState **)(this + 16), *(_DWORD *)(v4 + 48)) + 30) = 1;
  }
  if ( (unsigned __int8)CCBRoleState::GetForce(*(CCBRoleState **)(this + 16), 0)
    && (CCBStage::DelTask(*(CCBStage **)(this + 20), *(_DWORD *)(v4 + 20), &a3, &a4), a3) )
  {
    CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    *(_BYTE *)(CCBRoleState::InitUI(*(CCBRoleState **)(this + 16), *(_DWORD *)(v4 + 48)) + 30) = 0;
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
    return 0;
  }
  else
  {
    if ( CCBSystem::IsCmdReady(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48))
      || *(_BYTE *)(*(_DWORD *)(this + 16) + 549) )
    {
      CCBStage::DelTask(*(CCBStage **)(this + 20), *(_DWORD *)(v4 + 20), &a3, &a4);
      if ( a3 )
      {
        CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
        CCBSystem::CreateObj((CCBSystem *)this, CCBSystem::PassCmdToTask, 0, 0, 0, (const void *)(v4 + 40));
        goto LABEL_5;
      }
    }
    if ( CCBRoleState::GetRoleField(*(CCBRoleState **)(this + 16), *(_DWORD *)(v4 + 48), 16)
      && !*(_BYTE *)(*(_DWORD *)(this + 16) + 549) )
    {
      CCBSystem::GetCmdData(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
      CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    }
    if ( !CCBSystem::IsCmdEmpty(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48)) )
      return 0;
    CCBStage::DelTask(*(CCBStage **)(this + 20), *(_DWORD *)(v4 + 20), &a3, &a4);
    if ( !a3 )
      return 0;
    CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    *(_BYTE *)(CCBRoleState::InitUI(*(CCBRoleState **)(this + 16), *(_DWORD *)(v4 + 48)) + 30) = 0;
    memset(v17, 0, sizeof(v17));
    LOBYTE(v17[10]) = 1;
    v17[0] = 267;
    v9 = CCBSystem::ProcProtect((CCBSystem *)this);
    v10 = *(_DWORD *)(v4 + 48);
    v11 = (CCBStage *)*(CCBStage **)(this + 20);
    v17[1] = v9;
    v17[2] = v10;
    v17[3] = -1;
    v12 = v11->GetRoleIndex(26, v17, 1);
    if ( v12 != -1 )
    {
      memset(v16, 0, sizeof(v16));
      CCBStage::GetRoleName(*(CCBStage **)(this + 20), v12, (int)sub_5024D0, 0, 0, 0, v16, 0, 1077936128);
      CCBSystem::GetStageRoleByIdx(*(CCBSystem **)(this + 20), v12);
    }
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
    return -1;
  }
}

// 0x005155D0
int CCBSystem::PassCmdToTask(int _this, int a2)
{
  int v3; // eax
  int v4; // esi
  int RoleIndex; // eax
  int v6; // edx
  int v7; // ebp
  _DWORD *v8; // ecx
  char v10; // [esp+13h] [ebp-11h] BYREF
  int v11; // [esp+14h] [ebp-10h] BYREF
  _DWORD v12[3]; // [esp+18h] [ebp-Ch] BYREF

  v10 = 0;
  v11 = 0;
  v3 = *(_DWORD *)(this + 144);
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200), 1);
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 20, (const void *)(v4 + 40), 0);
    v6 = *(_DWORD *)(v4 + 44);
    v7 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    v12[0] = v6;
    v12[1] = *(_DWORD *)(v4 + 48);
    v12[2] = *(_DWORD *)(v4 + 52);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      v12,
      -1082130432,
      0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v7, (int)sub_500D50, 0, 0, 0, v12, -1082130432, 0);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v7,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      v12,
      -1082130432,
      0);
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v7);
    *(_BYTE *)(v4 + 37) = 1;
  }
  CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v10, &v11);
  if ( v10 == 1 )
  {
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    if ( v11 )
    {
      v8 = (_DWORD *)*(_DWORD **)(this + 52);
      *(_DWORD *)(this + 120) = 4;
      v8->CreateStars();
    }
    else
    {
      CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    }
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00515760
int CCBSystem::PassCmdViaThread(int _this, int a2)
{
  int v3; // eax
  int v4; // esi
  int RoleIndex; // ebx
  int v6; // ecx
  _DWORD v8[3]; // [esp+10h] [ebp-Ch] BYREF

  v3 = *(_DWORD *)(this + 144);
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200), 0);
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 19, (const void *)(v4 + 40), 1);
    v8[2] = *(_DWORD *)(v4 + 52);
    *(_DWORD *)(v4 + 20) = RoleIndex;
    v6 = *(_DWORD *)(v4 + 48);
    v8[0] = *(_DWORD *)(v4 + 44);
    v8[1] = v6;
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      v8,
      -1082130432,
      0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), RoleIndex, (int)sub_5014E0, 0, 0, 0, v8, -1082130432, 0);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      v8,
      -1082130432,
      0);
    *(_DWORD *)(v4 + 32) = *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 16), *(_DWORD *)(v4 + 48)) + 872);
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), RoleIndex);
    *(_BYTE *)(v4 + 37) = 1;
  }
  if ( CCBSystem::IsBusy(*(_DWORD **)(this + 12), *(_DWORD *)(v4 + 48))
    || *(_DWORD *)(this + 120) != 2
    || *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 16), *(_DWORD *)(v4 + 48)) + 872) > *(_DWORD *)(v4 + 32) )
  {
    CCBRoleState::SetRoleFlag(*(_BYTE **)(this + 16), *(_DWORD *)(v4 + 48), 0);
    CCBSystem::ClearEffect((CCBSystem *)this, *(_DWORD *)(this + 144));
    *(_DWORD *)(v4 + 32) = 0;
  }
  return 0;
}

// 0x00515940
int CCBSystem::CreateObj(int a2)
{
  __int32 m_bAuto; // eax
  __int32 *v4; // edi
  int Obj; // edi

  m_bAuto = this->m_bAuto;
  v4 = (__int32 *)&this->m_bLockCam + 22 * m_bAuto;
  if ( *((_BYTE *)&this->m_Thread[0].dwReturn + 88 * m_bAuto + 1) )
  {
    Obj = CCBSystem::CreateObj(0, 0, 0x40u);
    this->ClearEffect(this->m_bAuto);
    return Obj;
  }
  else
  {
    CCBSystem::ProcAI((int)this, 0.0);
    *((_BYTE *)v4 + 37) = 1;
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
    return MessageBoxA((HWND)g_Input.KeyInfo[175].PressTime, byte_17AC6DC, byte_17AC5DC, uType);
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
  for ( i = &this->m_pUtil[152];
        !i[36]
     || *(int (**)(int, int))i != CCBSystem::PassCmdToThread
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
  __int32 *i; // ecx
  char *v10; // ebp

  if ( this->m_nTimesOfCombat >= 1023 )
    MessageBoxA(0, &byte_5DE9E4, 0, 0x30u);
  if ( (char *)a2 == (char *)CCBSystem::CheckBattleEnd
    && (!CCBSystem::CheckBattleEnd || !a3 && !a4 && !a5)
    && sub_515C90((char *)this, (int)CCBSystem::CheckBattleEnd, 0, 0, 0) > 0 )
  {
    return 0;
  }
  v8 = 0;
  for ( i = &this->m_Thread[0].dwReturn; *(_BYTE *)i; i += 22 )
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
  ++this->m_nTimesOfCombat;
  return *((_DWORD *)v10 + 42);
}

// 0x00515C50
char CCBSystem::ClearEffect(int idx)
{
  memset(&this->m_pUtil[88 * idx + 152], 0, 0x58u);
  --*(_DWORD *)&this->m_pUtil[140];
  return 1;
}

// 0x00515D10
bool CCBSystem::CreateObj(_DWORD *a2)
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
      Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_4, 2504),
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
  dword_17ACE1C = 119;
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
  dword_17ACE2C = 519;
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
  dword_17ACE3C = 128;
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
  dword_17ACE4C = 545;
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
  dword_17ACE5C = 121;
  dword_17ACE60 = 316;
  dword_17ACE64 = 512;
  dword_17ACE68 = 709;
  return 709;
}
