#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBSystem.h"

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
int sub_512310(...);
int sub_512330(...);
int sub_512380(...);
int sub_5123D0(...);
int sub_512420(...);
int sub_512470(...);
int sub_5124C0(...);
int sub_512580(...);
int sub_5125E0(...);
int sub_512BA0(...);
int sub_512D40(...);
int sub_513150(...);
int sub_513380(...);
int sub_513420(...);
int sub_513430(...);
int sub_513600(...);
int sub_5136A0(...);
int sub_5136D0(...);
int sub_5137F0(...);
int sub_5158F0(...);
int sub_5159A0(...);
int sub_515B20(...);
int sub_515C90(...);
int sub_515DD0(...);
int sub_515DF0(...);
int sub_515E50(...);
int sub_515E70(...);
int sub_515E90(...);
int sub_515EE0(...);
int sub_515F30(...);
int sub_515F80(...);
int sub_515FD0(...);
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
  void (__thiscall ***v3)(_DWORD, _DWORD); // ecx
  int i; // esi
  void (__thiscall ***v5)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v6)(_DWORD, int); // ecx
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
    v3 = *(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_pUtil + 4) + 72);
    (**v3)(v3, 0);
    for ( i = 76; i < 120; i += 4 )
    {
      v5 = *(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_pUtil + 4) + i);
      (**v5)(v5, 0);
    }
    return 1;
  }
  else
  {
    v6 = *(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(*(_DWORD *)this->m_pUtil + 4) + 72);
    (**v6)(v6, 1);
    v7 = 0;
    for ( j = 76; j < 120; j += 4 )
    {
      v9 = *(_DWORD *)this->m_pUtil;
      if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)this->m_pUtil + 16) + v7 + 577) )
        (***(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(v9 + 4) + j))(*(_DWORD *)(*(_DWORD *)(v9 + 4) + j), 1);
      else
        (***(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)(v9 + 4) + j))(*(_DWORD *)(*(_DWORD *)(v9 + 4) + j), 0);
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

  v2 = &this->m_pUtil[40 * idx];
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

  result = &this->m_pUtil[40 * idx];
  *((_DWORD *)result + 8) = 0;
  *((_DWORD *)result + 9) = 0;
  result[46] = 0;
  return result;
}

// 0x004DB730
char * CCBSystem::sub_4DB730(int a2)
{
  char *result; // eax

  result = &this->m_pUtil[40 * a2];
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

  result = &this->m_pUtil[40 * idx];
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
  v4 = &this->m_pUtil[36];
  do
  {
    v5 = *(CCBStageRole **)&this->m_pUtil[8];
    if ( v5->m_pStage[v3 + 577] )
    {
      if ( !v5->IsActive(v2) )
      {
        v6 = *(_BYTE **)&this->m_pUtil[8];
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

  result = &this->m_pUtil[40 * idx];
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

  v2 = &this->m_pUtil[2632 * idx];
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

  v2 = &this->m_pUtil[2632 * idx];
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
  v3 = &this->m_pUtil[v2 + 2760];
  v4 = &this->m_pUtil[80 * *(_DWORD *)&this->m_pUtil[164] + 184 + v2];
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
void sub_512310()
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
int sub_512330()
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
int sub_512380()
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
int sub_5123D0()
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
int sub_512470()
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
int sub_5124C0()
{
  dword_17ACAD0 = 573;
  dword_17ACAD4 = 573;
  dword_17ACAD8 = 573;
  dword_17ACADC = 573;
  return 573;
}

// 0x00512500
int CCBSystem::CCBSystem()
{
  char *v1; // esi
  int v2; // ebx
  char *v3; // edi
  char *v4; // esi
  int v5; // ebx
  char *v6; // edi

  v1 = &this->m_pUtil[192];
  v2 = 1024;
  do
  {
    v3 = v1;
    v1 += 88;
    --v2;
    memset(v3, 0, 0x2Cu);
  }
  while ( v2 );
  v4 = &this->m_pUtil[90264];
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
int sub_512580(int this)
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
char __thiscall sub_5125E0(_DWORD *this)
{
  std::codecvt_base *v2; // ecx
  int v3; // eax
  char result; // al
  int v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // eax
  std::codecvt_base *v9; // eax
  _DWORD *v10; // eax
  _DWORD *v11; // eax
  _DWORD *v12; // eax
  std::codecvt_base *v13; // eax
  _DWORD *v14; // eax
  std::codecvt_base *v15; // eax
  _DWORD *v16; // eax
  int v17; // edx
  int v18; // edx
  _DWORD *v19; // eax
  _DWORD *v20; // eax
  int v21; // ecx
  int v22; // ecx
  _DWORD *v23; // eax
  void *v24; // eax
  int v25; // eax
  _DWORD *v26; // eax
  _DWORD *v27; // eax
  _DWORD *v28; // ecx
  _DWORD *v29; // eax
  char pExceptionObject[1024]; // [esp+Ch] [ebp-100Ch] BYREF
  char ArgList[1024]; // [esp+40Ch] [ebp-C0Ch] BYREF
  char v32[1024]; // [esp+80Ch] [ebp-80Ch] BYREF
  char v33; // [esp+C0Ch] [ebp-40Ch] BYREF
  int v34; // [esp+1014h] [ebp-4h]

  CCBSystem::ProcDialog((int)this);
  v34 = 0;
  if ( operator new(1u) )
    v3 = sub_51D5C0(this);
  else
    v3 = 0;
  *this = v3;
  v34 = -1;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_4, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = std::v2->do_always_noconv();
  if ( result )
  {
    v34 = 1;
    if ( operator new(0xA48u) )
      v5 = this->ctor_60A0();
    else
      v5 = 0;
    v34 = -1;
    *((_DWORD *)this + 1) = v5;
    if ( !v5 )
    {
      qmemcpy(
        pExceptionObject,
        (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_4, 2504),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    result = sub_5163D0(v5);
    if ( result )
    {
      v6 = operator new(0x50A4u);
      v34 = 2;
      if ( v6 )
        v7 = sub_4EC680(v6, (int)this);
      else
        v7 = 0;
      v34 = -1;
      *((_DWORD *)this + 4) = v7;
      if ( !v7 )
      {
        qmemcpy(
          pExceptionObject,
          (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_4, 2504),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      result = sub_4EC700((int)v7);
      if ( result )
      {
        v8 = operator new(0x1C8u);
        v34 = 3;
        if ( v8 )
          v9 = (std::codecvt_base *)v8->InitCmd((int)this);
        else
          v9 = 0;
        v34 = -1;
        *((_DWORD *)this + 3) = v9;
        if ( !v9 )
        {
          qmemcpy(
            pExceptionObject,
            (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_4, 2504),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        result = std::v9->do_always_noconv();
        if ( result )
        {
          v10 = operator new(0xA48B0u);
          v34 = 4;
          if ( v10 )
            v11 = v10->CCBStage((int)this);
          else
            v11 = 0;
          v34 = -1;
          *((_DWORD *)this + 5) = v11;
          if ( !v11 )
          {
            qmemcpy(
              pExceptionObject,
              (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_4, 2504),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          result = v11->Reset();
          if ( result )
          {
            v12 = operator new(0x570u);
            v34 = 5;
            if ( v12 )
              v13 = (std::codecvt_base *)sub_4DC160(v12, this);
            else
              v13 = 0;
            v34 = -1;
            *((_DWORD *)this + 2) = v13;
            if ( !v13 )
            {
              qmemcpy(
                pExceptionObject,
                (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_4, 2504),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            result = std::v13->do_always_noconv();
            if ( result )
            {
              v14 = operator new(0xE50u);
              v34 = 6;
              if ( v14 )
                v15 = (std::codecvt_base *)v14->Create(this);
              else
                v15 = 0;
              v34 = -1;
              *((_DWORD *)this + 6) = v15;
              if ( !v15 )
              {
                qmemcpy(
                  v32,
                  (const void *)Logger::FormatException((char)&v33, (int)aCNewFailed, (int)aDProjectPal3Co_4, 2504),
                  sizeof(v32));
                _CxxThrowException(v32, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              result = std::v15->do_always_noconv();
              if ( result )
              {
                *((_DWORD *)this + 8) = g_pSceneMgr;
                CCBSystem::ProcAI(1.0);
                result = CCBSystem::CreateObj2(this + 7);
                if ( result )
                {
                  v16 = operator new(0xA930u);
                  v34 = 7;
                  if ( v16 )
                  {
                    v17 = *(_DWORD *)(*((_DWORD *)this + 5) + 12);
                    if ( v17 )
                      v18 = v17 + 4;
                    else
                      v18 = 0;
                    v19 = v16->Create(g_pGfxManager, v18, (int)this);
                  }
                  else
                  {
                    v19 = 0;
                  }
                  *((_DWORD *)this + 11) = v19;
                  v20 = operator new(0xA930u);
                  v34 = 8;
                  if ( v20 )
                  {
                    v21 = *(_DWORD *)(*((_DWORD *)this + 5) + 12);
                    if ( v21 )
                      v22 = v21 + 4;
                    else
                      v22 = 0;
                    v23 = v20->Create(g_pGfxManager, v22, (int)this);
                  }
                  else
                  {
                    v23 = 0;
                  }
                  *((_DWORD *)this + 12) = v23;
                  v24 = operator new(0x5870u);
                  v34 = 9;
                  if ( v24 )
                    v25 = C2DSpark::C2DSpark((int)v24, MEMORY[0xBFD6D0], MEMORY[0xBFD6D4]);
                  else
                    v25 = 0;
                  *((_DWORD *)this + 13) = v25;
                  v26 = operator new(0x3E30u);
                  v34 = 10;
                  if ( v26 )
                    v27 = v26->C3DSpark();
                  else
                    v27 = 0;
                  v28 = (_DWORD *)*((_DWORD *)this + 8);
                  *((_DWORD *)this + 14) = v27;
                  v29 = (_DWORD *)sub_4C5980(v28, 1);
                  *((_DWORD *)this + 9) = v29;
                  v29->CEffectSystem((int)aEffectCombat10);
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
char __thiscall sub_512BA0(int this)
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
  v3 = *(void **)(this + 20);
  if ( v3 )
  {
    nullsub_3(*(void **)(this + 20));
    operator delete(v3);
  }
  *(_DWORD *)(this + 20) = 0;
  v4 = *(std::codecvt_base **)(this + 12);
  if ( !v4 )
    return 0;
  std::v4->do_always_noconv();
  v5 = *(void **)(this + 12);
  if ( v5 )
  {
    nullsub_3(*(void **)(this + 12));
    operator delete(v5);
  }
  *(_DWORD *)(this + 12) = 0;
  v6 = *(char **)(this + 16);
  if ( !v6 )
    return 0;
  sub_4EC7D0(v6);
  v7 = *(void **)(this + 16);
  if ( v7 )
  {
    nullsub_3(*(void **)(this + 16));
    operator delete(v7);
  }
  *(_DWORD *)(this + 16) = 0;
  v8 = *(std::codecvt_base **)(this + 8);
  if ( !v8 )
    return 0;
  std::v8->do_always_noconv();
  v9 = *(void **)(this + 8);
  if ( v9 )
  {
    sub_4DC1B0(*(void **)(this + 8));
    operator delete(v9);
  }
  *(_DWORD *)(this + 8) = 0;
  v10 = *(_DWORD *)(this + 4);
  if ( !v10 )
    return 0;
  (*(void (__thiscall **)(int))(*(_DWORD *)v10 + 12))(v10);
  v11 = *(_DWORD *)(this + 4);
  if ( v11 )
    (*(void (__thiscall **)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
  *(_DWORD *)(this + 4) = 0;
  v12 = *(std::codecvt_base **)(this + 24);
  if ( !v12 )
    return 0;
  std::v12->do_always_noconv();
  v13 = *(void **)(this + 24);
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
  std::v14->do_always_noconv();
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
  v16 = *(void **)(this + 48);
  if ( v16 )
  {
    sub_4CDAE0(*(gbRefObject ***)(this + 48));
    operator delete(v16);
    *(_DWORD *)(this + 48) = 0;
  }
  v17 = *(void **)(this + 52);
  if ( v17 )
  {
    C2DSpark::~C2DSpark(*(_DWORD *)(this + 52));
    operator delete(v17);
    *(_DWORD *)(this + 52) = 0;
  }
  v18 = *(void **)(this + 56);
  if ( v18 )
  {
    v18->ProcCoAttack(1);
    *(_DWORD *)(this + 56) = 0;
  }
  return 1;
}

// 0x00512D40
void * sub_512D40(void *Block, char a2)
{
  C3DSpark::~C3DSpark((int)Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00512D60
char CCBSystem::ProcWeaponSkill()
{
  int v3; // ecx
  CCBControl *v4; // ecx
  int v5; // ecx
  CCBSystem *v6; // ecx
  CCBStage *v7; // ecx
  int v8; // ecx
  CCBEditor *v9; // ecx
  int v10; // edi
  int i; // ebp
  CCBRoleState *v12; // ecx

  if ( !this->m_pUtil || !CCBLineupWindow::IsFaceOnInitPos() )
    return 0;
  v3 = (int)this->m_pUI;
  if ( !v3 || !v3->CreateParaWindow() )
    return 0;
  v4 = this->m_pControl;
  if ( !v4 || !sub_4DC220(v4) )
    return 0;
  v5 = (int)this->m_pRoleState->m_sCombatDialog;
  if ( !v5 || !sub_4EC830(v5) )
    return 0;
  v6 = (CCBSystem *)this->m_pAttackSequen;
  if ( !v6 || !v6->DestroySubsystems() )
    return 0;
  v7 = this->m_pStage;
  if ( !v7 || !v7->Destroy() )
    return 0;
  v8 = (int)this->m_pAI;
  if ( !v8 || !v8->Init() )
    return 0;
  if ( BYTE1(this->m_bFiveNimbus) )
  {
    v9 = this->m_pEditor;
    if ( !v9 || !sub_4E0430(v9) )
      return 0;
  }
  if ( !this->m_pEffMgr || !sub_4CDB60() )
    return 0;
  if ( !this->m_pATSEffMgr || !sub_4CDB60() )
    return 0;
  C2DSpark::CreateTrack((int)this->m_p2DSpark->m_Spark, 0);
  this->m_p2DSpark->m_Spark->CreateStars();
  this->m_p3DSpark->m_Spark->DestroyAll();
  v10 = 0;
  this->CreateObj(CCBSystem::Message, 0, 0, 0, 0);
  (CCBSystem *->GetDeltaTime()this->m_pAttackSequen);
  for ( i = 0; i < 1115; i += 223 )
  {
    v12 = this->m_pRoleState;
    if ( BYTE1(v12->m_bMustFail[0].sModel[i + 4]) )
    {
      *(_BYTE *)(v12->InitUI(v10) + 876) = 0;
      *(_BYTE *)(this->m_pRoleState->InitUI(v10) + 877) = 0;
    }
    ++v10;
  }
  sub_4C6170(this->m_pEffectSimple);
  gbSceneGraph::ResetBladeMgr(*(gbSceneGraph **)&g_pGfxManager[448]);
  if ( this->m_pRoleState->? && *((_BYTE *)CEffectSystem::DestroyAllEffect() + 4) )
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
char CCBSystem::ProcMagicWait(int this, int a2, char a3)
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
  v9 = (CCBSystem *->ProcWeaponSkill()this);
  UICursor::IRender();
  v5 = 0;
  v6 = &g_SceneMgr.m_info[916];
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
  float *v4; // ecx
  double v5; // st7
  double v6; // st7
  CCBUI *v7; // ecx
  int result; // eax
  float v9; // [esp+0h] [ebp-8h]
  float v10; // [esp+0h] [ebp-8h]
  float dta; // [esp+Ch] [ebp+4h]

  *(double *)&this->m_pUtil[88] = dt;
  v3 = dt + *(double *)&this->m_pUtil[96];
  v4 = *(float **)&this->m_pUtil[44];
  *(double *)&this->m_pUtil[96] = v3;
  *(float *)&this->m_pUtil[104] = v3;
  v5 = dt * *(float *)&this->m_pUtil[108];
  *(double *)&this->m_pUtil[64] = v5;
  v6 = v5 + *(double *)&this->m_pUtil[72];
  dta = v6;
  *(double *)&this->m_pUtil[72] = v6;
  *(float *)&this->m_pUtil[80] = v6;
  SceneMgrUpdate(v4, dta);
  SceneMgrUpdate(*(float **)&this->m_pUtil[48], *(float *)&this->m_pUtil[104]);
  CCBSystem::ProcMagic((int)this);
  this->IsFriendDoSkill();
  CCBAttackSequen::Update(*(CCBAttackSequen **)&this->m_pUtil[12]);
  CCBRoleState::Update(*(CCBRoleState **)&this->m_pUtil[16]);
  CCBAI::Update(*(void **)&this->m_pUtil[24]);
  CCBStage::Update(*(CCBStage **)&this->m_pUtil[20]);
  CCBControl::Update(*(CCBControl **)&this->m_pUtil[8]);
  if ( this->m_pUtil[133] )
  {
    v7 = *(CCBUI **)&this->m_pUtil[28];
    if ( v7 )
      v7->Update();
  }
  v9 = *(double *)&this->m_pUtil[64];
  C2DSpark::Render(*(_DWORD *)&this->m_pUtil[52], v9);
  v10 = *(double *)&this->m_pUtil[64];
  C3DSpark::Update(*(float **)&this->m_pUtil[56], v10);
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
char sub_513150(int this)
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
        v8 = *(void **)(this + 16);
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
        v11 = *(void **)(this + 16);
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
        v14 = *(_BYTE **)(this + 16);
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
bool sub_513380(HWND a1)
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
char sub_513420(char a2)
{
  *((_DWORD *)this + 132) = a2;
  return a2;
}

// 0x00513430
char sub_513430(int this)
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
void sub_513600(int this, float a2)
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
  v4 = *(_DWORD **)(this + 44);
  if ( v4 )
    sub_4CDC50(v4, SLODWORD(a2));
  v5 = *(_DWORD **)(this + 48);
  if ( v5 )
    sub_4CDC50(v5, 1065353216);
  v6 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( *(_BYTE *)(v6 + *(_DWORD *)(this + 16) + 577) )
      *(float *)(*(_DWORD *)(*(_DWORD *)(this + 20) + i) + 268) = a2;
    v6 += 892;
  }
  v8 = *(gbVisNode **)(*(_DWORD *)(*(_DWORD *)(this + 20) + 20) + 616);
  if ( v8 )
    v8->SetTimeScale(a2);
  if ( *(_BYTE *)(this + 133) )
    sub_4E05B0(a2);
}

// 0x005136A0
int sub_5136A0()
{
  unsigned int v1; // eax

  v1 = *((_DWORD *)this + 34) + 1;
  *((_DWORD *)this + 34) = v1;
  if ( v1 >= 0x7FFFFFFF )
    *((_DWORD *)this + 34) = 1;
  return *((_DWORD *)this + 34);
}

// 0x005136D0
char sub_5136D0(int this, int a2)
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
    i = (_DWORD *->GetControl()v4);
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
  (_BYTE *->IsTaskValidButNotFinish()i, *(_DWORD *)(this + 20), a2);
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
int sub_5137F0()
{
  int v2; // ebp
  _DWORD *v3; // esi
  int result; // eax

  v2 = 0;
  v3 = this + 38;
  do
  {
    if ( *((_BYTE *)v3 + 36) == 1 )
    {
      *((_DWORD *)this + 36) = v2;
      result = ((int (__thiscall *)(int, _DWORD))*v3)((int)this + v3[1], 0);
      *((_DWORD *)this + 36) = -1;
    }
    ++v2;
    v3 += 22;
  }
  while ( v2 < 1024 );
  *((_DWORD *)this + 36) = -1;
  return result;
}

// 0x00513840
int CCBSystem::CheckBattleEnd()
{
  int *v2; // ebx
  int v3; // eax
  char *v4; // edi
  int v5; // esi
  char v6; // bl
  int j; // edi
  int inited; // eax
  int k; // edi
  int v10; // eax
  bool v11; // cc
  CCBSystem *v13; // ecx
  int Control; // eax
  int v15; // eax
  CCBUI *v16; // ecx
  int v17; // [esp+10h] [ebp-Ch]
  int v18; // [esp+14h] [ebp-8h]
  char *i; // [esp+18h] [ebp-4h]

  if ( this->m_pUtil[133] && dword_17A990C != 2 )
    return 0;
  v2 = 0;
  if ( (unsigned __int8)CCBRoleState::GetForce(*(CCBRoleState **)&this->m_pUtil[16], 0)
    || *(_DWORD *)&this->m_pUtil[120] != 2 )
  {
    v16 = *(CCBUI **)&this->m_pUtil[8];
    if ( v16->UIFrameWnd[36] )
      v16->GetState();
    return 0;
  }
  if ( !*(_BYTE *)(*(_DWORD *)&this->m_pUtil[8] + 36) )
  {
    v3 = 24;
    v4 = &this->m_pUtil[90264];
    v5 = 0;
    v17 = 0;
    v18 = 24;
    for ( i = &this->m_pUtil[90264]; ; i += 52 )
    {
      if ( !*(_BYTE *)(v17 + *(_DWORD *)&this->m_pUtil[16] + 577)
        || !CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)(*(_DWORD *)&this->m_pUtil[20] + v3)) )
      {
        goto LABEL_39;
      }
      if ( sub_4ECB20(*(CCBRoleState **)&this->m_pUtil[16], v5) )
      {
        CCBSystem::GetDeltaTime(*(CCBSystem **)&this->m_pUtil[12]);
        return 0;
      }
      if ( CCBSystem::GetCmdType(*(CCBSystem **)&this->m_pUtil[12], v5) == 1
        && CCBRoleState::IsRoleAlive(*(CCBRoleState **)&this->m_pUtil[16], v5) == 1
        && CCBStageRole::IsActive(*(CCBStageRole **)&this->m_pUtil[16], v5) == 1
        && CCBSystem::IsBusy(*(CCBSystem **)&this->m_pUtil[12]) )
      {
        if ( CCBRoleState::GetRoleField(*(CCBRoleState **)&this->m_pUtil[16], v5, 17)
          || CCBRoleState::GetRoleField(*(CCBRoleState **)&this->m_pUtil[16], v5, 14) )
        {
          goto LABEL_38;
        }
        if ( !*(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v5) + 837)
          && !CCBRoleState::GetRoleField(*(CCBRoleState **)&this->m_pUtil[16], v5, 18)
          && !CCBRoleState::GetRoleField(*(CCBRoleState **)&this->m_pUtil[16], v5, 19) )
        {
          sub_4F7FC0(*(_DWORD *)&this->m_pUtil[16], v5);
          if ( !*(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v5) + 877)
            || (v6 = CCBAI::HandleFriendAffirmative(*(_DWORD **)&this->m_pUtil[24], v5, 1),
                *(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v5) + 877) = 0,
                !v6) )
          {
            if ( !*(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v5) + 876) )
            {
              dword_5DC3DC = v5;
              sub_4DC3F0(*(char **)&this->m_pUtil[8], v5);
              return 0;
            }
            if ( v4[40] )
            {
              CCBAI::HandlePlayerNormalAttack(*(_DWORD **)&this->m_pUtil[24], v5, (int)v4);
              for ( j = 0; j < 5; ++j )
              {
                inited = CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], j);
                *(_BYTE *)(inited + 876) = 0;
              }
            }
            else
            {
              CCBAI::HandleFriendAffirmative(*(_DWORD **)&this->m_pUtil[24], v5, 0);
              for ( k = 0; k < 5; ++k )
              {
                v10 = CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], k);
                *(_BYTE *)(v10 + 876) = 0;
              }
            }
          }
          goto LABEL_39;
        }
        sub_4F7FC0(*(_DWORD *)&this->m_pUtil[16], v5);
        CCBAI::HandleEnemyChaos(*(_DWORD **)&this->m_pUtil[24], v5);
      }
      if ( CCBSystem::GetCmdType(*(CCBSystem **)&this->m_pUtil[12], v5) != 1
        || CCBRoleState::IsRoleAlive(*(CCBRoleState **)&this->m_pUtil[16], v5) != 1
        || CCBStageRole::IsActive(*(CCBStageRole **)&this->m_pUtil[16], v5)
        || !CCBSystem::IsBusy(*(CCBSystem **)&this->m_pUtil[12]) )
      {
        goto LABEL_39;
      }
      if ( CCBRoleState::GetRoleField(*(CCBRoleState **)&this->m_pUtil[16], v5, 17)
        || CCBRoleState::GetRoleField(*(CCBRoleState **)&this->m_pUtil[16], v5, 14)
        || *(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v5) + 879) )
      {
LABEL_38:
        CCBSystem::GetCmdData(*(CCBSystem **)&this->m_pUtil[12], v5);
        goto LABEL_39;
      }
      CCBAI::Render(*(_DWORD **)&this->m_pUtil[24], v5);
LABEL_39:
      v3 = v18 + 4;
      v17 += 892;
      ++v5;
      v4 = i + 52;
      v11 = v18 + 4 < 68;
      v18 += 4;
      if ( !v11 )
        return 0;
    }
  }
  CCBSystem::GetDeltaTime(*(CCBSystem **)&this->m_pUtil[12]);
  v13 = *(CCBSystem **)&this->m_pUtil[8];
  if ( v13->m_pUtil[96] )
    v2 = (int *)&v13->m_pUtil[56];
  Control = v13->GetControl();
  if ( *(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], Control) + 877)
    || (v15 = CCBSystem::GetControl(*(CCBSystem **)&this->m_pUtil[8]),
        *(_BYTE *)(CCBRoleState::InitUI(*(void **)&this->m_pUtil[16], v15) + 876)) )
  {
    dword_5DC3DC = -1;
    CCBSystem::GetDeltaTime(*(CCBSystem **)&this->m_pUtil[12]);
    CCBUI::GetState(*(CCBUI **)&this->m_pUtil[8]);
    return 0;
  }
  if ( CCBSystem::GetControl(*(CCBSystem **)&this->m_pUtil[8]) != dword_5DC3DC || !v2 )
    return 0;
  if ( CCBRoleState::GetRoleField(*(CCBRoleState **)&this->m_pUtil[16], dword_5DC3DC, 14) )
  {
    CCBUI::GetState(*(CCBUI **)&this->m_pUtil[8]);
    return 0;
  }
  else
  {
    switch ( *v2 )
    {
      case 259:
        this->CreateObj(CCBSystem::IsRoleWaitForFlee, 0, 0, 0, v2);
        qmemcpy(&this->m_pUtil[52 * dword_5DC3DC + 90264], v2, 0x2Cu);
        *(_BYTE *)(*(_DWORD *)&this->m_pUtil[24] + dword_5DC3DC) = 0;
        break;
      case 260:
        this->CreateObj(CCBSystem::GetThreadIndex, 0, 0, 0, v2);
        qmemcpy(&this->m_pUtil[52 * dword_5DC3DC + 90264], v2, 0x2Cu);
        *(_BYTE *)(*(_DWORD *)&this->m_pUtil[24] + dword_5DC3DC) = 0;
        break;
      case 261:
        this->CreateObj(CCBSystem::GetSameThreadNum, 0, 0, 0, v2);
        qmemcpy(&this->m_pUtil[52 * dword_5DC3DC + 90264], v2, 0x2Cu);
        *(_BYTE *)(*(_DWORD *)&this->m_pUtil[24] + dword_5DC3DC) = 0;
        break;
      case 262:
        this->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v2);
        qmemcpy(&this->m_pUtil[52 * dword_5DC3DC + 90264], v2, 0x2Cu);
        *(_BYTE *)(*(_DWORD *)&this->m_pUtil[24] + dword_5DC3DC) = 0;
        break;
      case 264:
      case 266:
      case 268:
        this->CreateObj(sub_5158F0, 0, 0, 0, v2);
        break;
      case 265:
        this->CreateObj(CCBSystem::PassCmdViaThread, 0, 0, 0, v2);
        qmemcpy(&this->m_pUtil[52 * dword_5DC3DC + 90264], v2, 0x2Cu);
        *(_BYTE *)(*(_DWORD *)&this->m_pUtil[24] + dword_5DC3DC) = 0;
        break;
      case 267:
        this->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v2);
        qmemcpy(&this->m_pUtil[52 * dword_5DC3DC + 90264], v2, 0x2Cu);
        *(_BYTE *)(*(_DWORD *)&this->m_pUtil[24] + dword_5DC3DC) = 0;
        break;
      case 269:
        this->CreateObj(CCBSystem::DelThread, 0, 0, 0, v2);
        *(_BYTE *)(*(_DWORD *)&this->m_pUtil[24] + dword_5DC3DC) = 0;
        break;
      default:
        break;
    }
    sub_4DC510(*(_DWORD *)&this->m_pUtil[8], v2[2]);
    dword_5DC3DC = -1;
    return 0;
  }
}

// 0x00513EB0
int CCBSystem::Message(int this, int a2)
{
  int RoleIndex; // edi

  *(_BYTE *)(*(_DWORD *)(this + 112) + 82) = 0;
  RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 3, 0, 1);
  if ( RoleIndex != -1 )
  {
    if ( *(_BYTE *)(*(_DWORD *)(this + 16) + 537)
      || (CCBStage::GetRoleName(
            *(_DWORD **)(this + 20),
            RoleIndex,
            (int)CCBStage::IsSubTaskFinished,
            0,
            0,
            0,
            0,
            -1082130432,
            1082130432),
          CCBStage::GetRoleName(
            *(_DWORD **)(this + 20),
            RoleIndex,
            (int)CCBStage::IsAllSubTaskFinished,
            0,
            0,
            0,
            0,
            0,
            1082130432),
          *(_BYTE *)(*(_DWORD *)(this + 16) + 536)) )
    {
      CCBStage::GetRoleName(*(_DWORD **)(this + 20), RoleIndex, (int)CCBStage::IsIdle, 0, 0, 0, 0, 0, 1077936128);
    }
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), RoleIndex);
  }
  (_DWORD *->CreateObj()this, CCBSystem::CheckBattleEnd, 0, 0, 0, 0);
  (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
  return 0;
}

// 0x00513FD0
int CCBSystem::IsRoleWaitForFlee(int this, int a2)
{
  int v3; // eax
  int v4; // ebp
  _DWORD *v5; // edi
  int v6; // eax
  int RoleIndex; // eax
  int v8; // edi
  char v10; // [esp+13h] [ebp-15h] BYREF
  int v11; // [esp+14h] [ebp-14h] BYREF
  int v12; // [esp+18h] [ebp-10h] BYREF
  int v13; // [esp+1Ch] [ebp-Ch] BYREF
  int v14; // [esp+20h] [ebp-8h]
  int v15; // [esp+24h] [ebp-4h]

  v3 = *(_DWORD *)(this + 144);
  v10 = 0;
  v12 = 0;
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
    if ( CCBRoleState::CheckVarianceRound(*(_DWORD **)(this + 16), *(_DWORD *)(v4 + 48), 0, &v11) == 1 )
    {
      v6 = *(_DWORD *)(v4 + 48);
      *v5 = 270;
      *(_DWORD *)(v4 + 44) = v11;
      CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), v6);
      (_DWORD *->CreateObj()this, CCBSystem::AddThread, 0, 0, 0, (const void *)(v4 + 40));
LABEL_12:
      (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
      return 0;
    }
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 11, (const void *)(v4 + 40), 0);
    v8 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    if ( RoleIndex != -1 )
    {
      v13 = 0;
      v14 = 0;
      v15 = 0;
      v14 = *(_DWORD *)(v4 + 48);
      v15 = *(_DWORD *)(v4 + 52);
      CCBStage::GetRoleName(
        *(_DWORD **)(this + 20),
        RoleIndex,
        (int)CCBStage::ProcFiveLienupFadeIn,
        0,
        0,
        0,
        &v13,
        -1082130432,
        0);
      CCBStage::GetRoleName(
        *(_DWORD **)(this + 20),
        v8,
        (int)CCBStage::ProcShowSneakAttackState,
        0,
        0,
        0,
        &v13,
        -1082130432,
        0);
      CCBStage::GetRoleName(*(_DWORD **)(this + 20), v8, (int)CCBStage::HandleKeyCtrl, 0, 0, 0, &v13, -1082130432, 0);
      CCBStage::GetRoleName(*(_DWORD **)(this + 20), v8, (int)CCBStage::ProcShowName, 0, 0, 0, &v13, -1082130432, 0);
      CCBStage::GetRoleName(
        *(_DWORD **)(this + 20),
        v8,
        (int)CCBStage::ProcFiveLienupFadeOut,
        0,
        0,
        0,
        &v13,
        -1082130432,
        0);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v8);
    }
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    *(_BYTE *)(v4 + 37) = 1;
  }
  CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v10, &v12);
  if ( v10 == 1 )
  {
    if ( *(_DWORD *)(v4 + 20) != -1 )
      CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    goto LABEL_11;
  }
  return 0;
}

// 0x00514220
int CCBSystem::AddThread(int this, int a2)
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
      (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
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
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00514610
int CCBSystem::DelThread(int this, int a2)
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
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00514870
int CCBSystem::GetSameThreadNum(int this, int a2)
{
  int v3; // eax
  _DWORD *v4; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // ecx
  int v10; // [esp-4h] [ebp-14h]
  int v11; // [esp+Ch] [ebp-4h] BYREF

  v11 = 0;
  v3 = *(_DWORD *)(this + 144);
  v4 = (_DWORD *)(this + 88 * v3 + 152);
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    if ( CCBRoleState::CheckVarianceRound(
           *(_DWORD **)(this + 16),
           *(_DWORD *)(this + 88 * v3 + 200),
           *(_DWORD *)(this + 88 * v3 + 196),
           &v11) == 1 )
    {
      v10 = v4[12];
      v4[10] = 270;
      v4[11] = v11;
      CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), v10);
      (_DWORD *->CreateObj()this, CCBSystem::AddThread, 0, 0, 0, v4 + 10);
LABEL_20:
      (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
      return 0;
    }
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), v4[12], 0);
    if ( !CCBSystem::IsBusy(*(_DWORD **)(this + 12), v4[12]) )
    {
      (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
      return -1;
    }
    CCBSystem::sub_4DB730(*(char **)(this + 12), v4[12]);
    v6 = sub_4F76C0(*(_DWORD **)(this + 16), v4[12], v4[11]);
    v7 = v6;
    if ( v6 )
    {
      if ( v6 > 3 )
      {
        CCBSystem::GetCmdData(*(CCBSystem **)(this + 12), v4[12]);
LABEL_11:
        CCBStageRole::DelTask(*(_DWORD **)(*(_DWORD *)(this + 20) + 4 * v4[12] + 24), 4);
        *((_BYTE *)v4 + 37) = 1;
        goto LABEL_12;
      }
    }
    else
    {
      v7 = 1;
    }
    v8 = 2 * v7 * CCBSystem::CalcSpeed(v4[12], 1);
    if ( v8 > 255 )
      LOBYTE(v8) = -1;
    CCBSystem::GetCmdCount(*(_BYTE **)(this + 12), v4[12], v8);
    goto LABEL_11;
  }
LABEL_12:
  if ( CCBRoleState::GetForce(*(char **)(this + 16), 0) )
  {
LABEL_15:
    CCBStageRole::DelTask(*(_DWORD **)(*(_DWORD *)(this + 20) + 4 * v4[12] + 24), 2);
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
    return 0;
  }
  if ( CCBRoleState::GetRoleField(*(CCBRoleState **)(this + 16), v4[12], 15) )
  {
    CCBSystem::GetCmdData(*(CCBSystem **)(this + 12), v4[12]);
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), v4[12], 0);
    goto LABEL_15;
  }
  if ( CCBSystem::IsCmdReady(*(_DWORD **)(this + 12), v4[12]) )
  {
    CCBStageRole::DelTask(*(_DWORD **)(*(_DWORD *)(this + 20) + 4 * v4[12] + 24), 2);
    (_DWORD *->CreateObj()this, CCBSystem::IsThreadExist, 0, 0, 0, v4 + 10);
    goto LABEL_20;
  }
  if ( !CCBSystem::IsCmdEmpty(*(_BYTE **)(this + 12), v4[12]) )
    return 0;
  v9 = *(_DWORD *)(this + 8);
  if ( *(_BYTE *)(v9 + 36) )
  {
    if ( (_DWORD *->GetControl()v9) == v4[12] )
      CCBUI::GetState(*(_BYTE **)(this + 8));
  }
  CCBStageRole::DelTask(*(_DWORD **)(*(_DWORD *)(this + 20) + 4 * v4[12] + 24), 2);
  (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
  return -1;
}

// 0x00514AE0
int CCBSystem::IsThreadExist(int this, int a2)
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
      v8 = CCBStage::IsAllSubTaskFinished;
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
      v8 = CCBStage::IsSubTaskFinished;
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
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00514D60
int CCBSystem::GetThreadIndex(int this, int a2)
{
  int v3; // eax
  _DWORD *v4; // ebp
  int RoleIndex; // eax
  int v7; // edx
  int v8; // edi
  int v9; // [esp-4h] [ebp-2Ch]
  char v10; // [esp+13h] [ebp-15h] BYREF
  int v11; // [esp+14h] [ebp-14h] BYREF
  int v12; // [esp+18h] [ebp-10h] BYREF
  _DWORD v13[3]; // [esp+1Ch] [ebp-Ch] BYREF

  v3 = *(_DWORD *)(this + 144);
  v10 = 0;
  v12 = 0;
  v11 = 0;
  v4 = (_DWORD *)(this + 88 * v3 + 152);
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200), 1);
    if ( CCBRoleState::CheckVarianceRound(*(_DWORD **)(this + 16), v4[12], v4[11], &v11) == 1 )
    {
      v9 = v4[12];
      v4[10] = 270;
      v4[11] = v11;
      CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), v9);
      (_DWORD *->CreateObj()this, CCBSystem::AddThread, 0, 0, 0, v4 + 10);
      (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
      return 0;
    }
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 16, v4 + 10, 0);
    v7 = v4[11];
    v8 = RoleIndex;
    v4[5] = RoleIndex;
    v13[0] = v7;
    v13[1] = v4[12];
    v13[2] = v4[13];
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      v13,
      -1082130432,
      0);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v8,
      (int)CCBStage::ClearRoleAllTask,
      0,
      0,
      0,
      v13,
      -1082130432,
      1065353216);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v8, (int)CCBStage::ProcGrabStageRole, 0, 0, 0, v13, 1028443341, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v8, (int)sub_4FFA90, 0, 0, 0, v13, -1082130432, 0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v8, (int)sub_4FFCB0, 0, 0, 0, v13, -1082130432, 0);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v8,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      v13,
      -1082130432,
      0);
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v8);
    CCBSystem::GetCmdPtr(*(CCBSystem **)(this + 12), v4[12]);
    *((_BYTE *)v4 + 37) = 1;
  }
  CCBStage::DelTask(*(char **)(this + 20), v4[5], &v10, &v12);
  if ( v10 == 1 )
  {
    CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), v4[5]);
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), v4[12], 0);
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00514FE0
int CCBSystem::PassCmdToThread(int this, int a2)
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
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00515200
int CCBSystem::PassCmdToThread(int this, int a2)
{
  int v3; // eax
  int v4; // ebp
  char v6; // al
  int RoleIndex; // eax
  int v8; // edx
  int v9; // edi
  int v10; // eax
  int v11; // edx
  _DWORD *v12; // ecx
  int v13; // edi
  char v14; // [esp+13h] [ebp-49h] BYREF
  int v15; // [esp+14h] [ebp-48h] BYREF
  _DWORD v16[3]; // [esp+18h] [ebp-44h] BYREF
  _DWORD v17[3]; // [esp+24h] [ebp-38h] BYREF
  _DWORD v18[11]; // [esp+30h] [ebp-2Ch] BYREF

  v14 = 0;
  v3 = *(_DWORD *)(this + 144);
  v4 = this + 88 * v3 + 152;
  if ( !*(_BYTE *)(this + 88 * v3 + 189) )
  {
    if ( !CCBSystem::IsBusy(*(_DWORD **)(this + 12), *(_DWORD *)(this + 88 * v3 + 200))
      && !*(_BYTE *)(*(_DWORD *)(this + 16) + 549) )
    {
      CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
LABEL_5:
      (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
      return 0;
    }
    CCBSystem::sub_4DB730(*(char **)(this + 12), *(_DWORD *)(v4 + 48));
    v6 = CCBRoleState::GetSpeedBonus(*(char **)(this + 16), *(_DWORD *)(v4 + 48));
    CCBSystem::GetCmdCount(*(_BYTE **)(this + 12), *(_DWORD *)(v4 + 48), 8 * v6 + 20);
    if ( *(_BYTE *)(*(_DWORD *)(this + 16) + 549) )
      CCBSystem::GetCmdData(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
    CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    *(_BYTE *)(v4 + 37) = 1;
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)(this + 20), 20, (const void *)(v4 + 40), 0);
    v8 = *(_DWORD *)(v4 + 44);
    v9 = RoleIndex;
    *(_DWORD *)(v4 + 20) = RoleIndex;
    v16[0] = v8;
    v16[1] = *(_DWORD *)(v4 + 48);
    v16[2] = *(_DWORD *)(v4 + 52);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      RoleIndex,
      (int)CCBStage::ProcFiveLienupFadeIn,
      0,
      0,
      0,
      v16,
      -1082130432,
      0);
    CCBStage::GetRoleName(*(_DWORD **)(this + 20), v9, (int)sub_500C20, 0, 0, 0, v16, -1082130432, 0);
    CCBStage::GetRoleName(
      *(_DWORD **)(this + 20),
      v9,
      (int)CCBStage::ProcFiveLienupFadeOut,
      0,
      0,
      0,
      v16,
      -1082130432,
      0);
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v9);
    *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 16), *(_DWORD *)(v4 + 48)) + 30) = 1;
  }
  if ( CCBRoleState::GetForce(*(char **)(this + 16), 0)
    && (CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v14, &v15), v14) )
  {
    CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 16), *(_DWORD *)(v4 + 48)) + 30) = 0;
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
    return 0;
  }
  else
  {
    if ( CCBSystem::IsCmdReady(*(_DWORD **)(this + 12), *(_DWORD *)(v4 + 48))
      || *(_BYTE *)(*(_DWORD *)(this + 16) + 549) )
    {
      CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v14, &v15);
      if ( v14 )
      {
        CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
        (_DWORD *->CreateObj()this, CCBSystem::PassCmdToTask, 0, 0, 0, (const void *)(v4 + 40));
        goto LABEL_5;
      }
    }
    if ( CCBRoleState::GetRoleField(*(CCBRoleState **)(this + 16), *(_DWORD *)(v4 + 48), 16)
      && !*(_BYTE *)(*(_DWORD *)(this + 16) + 549) )
    {
      CCBSystem::GetCmdData(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48));
      CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    }
    if ( !CCBSystem::IsCmdEmpty(*(_BYTE **)(this + 12), *(_DWORD *)(v4 + 48)) )
      return 0;
    CCBStage::DelTask(*(char **)(this + 20), *(_DWORD *)(v4 + 20), &v14, &v15);
    if ( !v14 )
      return 0;
    CCBSystem::GetStageRole(*(CCBSystem **)(this + 20), *(_DWORD *)(v4 + 20));
    *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 16), *(_DWORD *)(v4 + 48)) + 30) = 0;
    memset(v18, 0, sizeof(v18));
    LOBYTE(v18[10]) = 1;
    v18[0] = 267;
    v10 = (_DWORD *->ProcProtect()this);
    v11 = *(_DWORD *)(v4 + 48);
    v12 = *(_DWORD **)(this + 20);
    v18[1] = v10;
    v18[2] = v11;
    v18[3] = -1;
    v13 = v12->GetRoleIndex(26, v18, 1);
    if ( v13 != -1 )
    {
      memset(v17, 0, sizeof(v17));
      CCBStage::GetRoleName(*(_DWORD **)(this + 20), v13, (int)sub_5024D0, 0, 0, 0, v17, 0, 1077936128);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 20), v13);
    }
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
    return -1;
  }
}

// 0x005155D0
int CCBSystem::PassCmdToTask(int this, int a2)
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
      v8 = *(_DWORD **)(this + 52);
      *(_DWORD *)(this + 120) = 4;
      v8->CreateStars();
    }
    else
    {
      CCBSystem::SetCmdParam(*(CCBSystem **)(this + 12), *(_DWORD *)(v4 + 48), 0);
    }
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
  }
  return 0;
}

// 0x00515760
int CCBSystem::PassCmdViaThread(int this, int a2)
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
    (CCBSystem *->ClearEffect()this, *(_DWORD *)(this + 144));
    *(_DWORD *)(v4 + 32) = 0;
  }
  return 0;
}

// 0x00515940
int CCBSystem::CreateObj(int a2)
{
  int v3; // eax
  _DWORD *v4; // edi
  int Obj; // edi

  v3 = *((_DWORD *)this + 36);
  v4 = this + 22 * v3 + 38;
  if ( *((_BYTE *)this + 88 * v3 + 189) )
  {
    Obj = CCBSystem::CreateObj(0, 0, 0x40u);
    (CCBSystem *->ClearEffect()this, *((_DWORD *)this + 36));
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
int sub_5159A0(const char *a1, const char *a2, UINT a3)
{
  unsigned int v3; // eax
  CHAR *v4; // edi
  char *v5; // esi
  char v6; // cl
  unsigned int v7; // edx

  if ( !a1 )
    return MessageBoxA(MEMORY[0xBFDA4C], byte_17AC6DC, byte_17AC5DC, uType);
  if ( strlen(a1) >= 0xFF )
  {
    v7 = strlen(aTooManyCharact) + 1;
    qmemcpy(byte_17AC6DC, aTooManyCharact, 4 * (v7 >> 2));
    v5 = &aTooManyCharact[4 * (v7 >> 2)];
    v4 = &byte_17AC6DC[4 * (v7 >> 2)];
    v6 = v7;
  }
  else
  {
    v3 = strlen(a1) + 1;
    qmemcpy(byte_17AC6DC, a1, 4 * (v3 >> 2));
    v5 = (char *)&a1[4 * (v3 >> 2)];
    v4 = &byte_17AC6DC[4 * (v3 >> 2)];
    v6 = v3;
  }
  qmemcpy(v4, v5, v6 & 3);
  if ( a2 )
  {
    if ( strlen(a2) < 0xFF )
      strcpy(byte_17AC5DC, a2);
  }
  else
  {
    sprintf(byte_17AC5DC, aS_3, aPal3CombatSyst);
  }
  uType = a3;
  CCBSystem::CreateObj(CCBSystem::CreateObj, 0, 0, 0, 0);
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
     || *(int (__thiscall **)(int, int))i != CCBSystem::PassCmdToThread
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
int sub_515B20(int ( *a2)(int this, int a2), int a3, int a4, int a5, const void *a6)
{
  int v8; // eax
  _BYTE *i; // ecx
  _DWORD *v10; // ebp

  if ( (int)*((_DWORD *)this + 35) >= 1023 )
    MessageBoxA(0, &byte_5DE9E4, 0, 0x30u);
  if ( a2 == CCBSystem::CheckBattleEnd
    && (!CCBSystem::CheckBattleEnd || !a3 && !a4 && !a5)
    && (int)sub_515C90(CCBSystem::CheckBattleEnd, 0, 0, 0) > 0 )
  {
    return 0;
  }
  v8 = 0;
  for ( i = this + 47; *i; i += 88 )
  {
    if ( ++v8 >= 1024 )
      return -1;
  }
  v10 = this + 22 * v8;
  *((_BYTE *)v10 + 188) = 1;
  *((_BYTE *)v10 + 189) = 0;
  v10[38] = a2;
  v10[39] = a3;
  v10[40] = a4;
  v10[41] = a5;
  v10[42] = this->ProcProtect();
  v10[45] = 0;
  v10[43] = -1;
  if ( a6 )
    qmemcpy(v10 + 48, a6, 0x2Cu);
  ++*((_DWORD *)this + 35);
  return v10[42];
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
    v4 = sub_4E02F0(v3, (int)this);
  else
    v4 = 0;
  v8 = -1;
  *a2 = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      (Logger *->FormatException()ArgList, aCNewFailed, aDProjectPal3Co_4, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return sub_4E0380(v4) != 0;
}

// 0x00515DD0
void * sub_515DD0(void *Block, char a2)
{
  nullsub_3(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00515DF0
void * sub_515DF0(void *Block, char a2)
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
int sub_515E50()
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
void sub_515E70()
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
int sub_515E90()
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
int sub_515EE0()
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
int sub_515F30()
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
int sub_515F80()
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
int sub_515FD0()
{
  dword_17ACE5C = 121;
  dword_17ACE60 = 316;
  dword_17ACE64 = 512;
  dword_17ACE68 = 709;
  return 709;
}
