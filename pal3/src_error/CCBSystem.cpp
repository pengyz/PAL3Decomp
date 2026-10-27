#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBSystem.h"
#include "Role/Actor.h"
#include "Effect/C2DSpark.h"
#include "Effect/C3DSpark.h"
#include "Combat/CCBAI.h"
#include "Combat/CCBAttackSequen.h"
#include "Combat/CCBCamControl.h"
#include "Combat/CCBControl.h"
#include "Misc/CCBEditor.h"
#include "Combat/CCBLineupWindow.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBStageEffect.h"
#include "Combat/CCBStageRole.h"
#include "Combat/CCBStageScene.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffect.h"
#include "Misc/CEffectSimple.h"
#include "Effect/CEffectSystem.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Combat/Combat.h"
#include "Misc/FightInfo.h"
#include "GameBase/GRPinput.h"
#include "GameBase/Logger.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Misc/PtrArray.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneMgr.h"
#include "Scene/SceneObj.h"
#include "UI/StateUI.h"
#include "Misc/TxtFile.h"
#include "UI/UICursor.h"
#include "Misc/UIObj.h"
#include "Misc/UIPushButton.h"
#include "UI/UIScene.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/_Texture_uv.h"
#include "Misc/tagCmdData.h"
#include "Misc/tagPlayerSet.h"
#include "Misc/tagRoleState.h"
#include "Misc/tagThread.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4C5980(...);
int sub_515C90(...);
int sub_5163D0(...);
int sub_51D5C0(...);

// Unnamed globals (extern)
extern char aEffectCombat10[];
extern CHAR byte_17AC6DC[256];
void __cdecl nullsub_68(void);

// 0x00462280
void CCBSystem::ProcessSlotResults(int nVal)
{
  int v2; // edi
  int v3; // esi
  char **v4; // ebx
  CCBResultWindow *v5; // ecx

  v2 = *(_DWORD *)&this->m_Thread[178].cmd.bSrcRole[4 * nVal + 6];
  v3 = 0;
  v4 = (char **)&this->m_Thread[953].fp[1];
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
          ((CCBResultWindow *)((CCBResultWindow *)v4 - 1))->CCBResultWindow::StartAnim();
          v5 = (CCBResultWindow *)(v4 + 90);
          goto LABEL_13;
        }
        break;
      case 0xB:
        if ( *(_BYTE *)(v3 + v2 + 614) )
        {
          v5 = (CCBResultWindow *)(v4 - 90);
LABEL_13:
          (((CCBResultWindow *)v5))->CCBResultWindow::StartAnim();
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
    ((CCBResultWindow *)(v1 - 3))->CCBResultWindow::SetDirty();
    (((CCBResultWindow *)v1))->CCBResultWindow::SetDirty();
    ((CCBResultWindow *)(v1 + 1))->CCBResultWindow::SetDirty();
    ((CCBResultWindow *)(v1 - 1))->CCBResultWindow::SetDirty();
    ((CCBResultWindow *)(v1 + 2))->CCBResultWindow::SetDirty();
    ((CCBResultWindow *)(v1 - 2))->CCBResultWindow::SetDirty();
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

  result = (_BYTE *)&this->m_pEffectSimple;
  v2 = 2048;
  do
  {
    *result = 0;
    result += 48;
    --v2;
  }
  while ( v2 );
  this->m_pAI = ((CCBAI *)0);
  *(_DWORD *)&this[1].m_Thread[83].bValid = 0;
  return result;
}

// 0x004DB3A0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
int CCBSystem::InitCmdTable1_thunk()
{
  return this->CCBSystem::InitCmdTable1();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004DB3B0
int CCBSystem::InitCmdTable1()
{
  int result; // eax

  dword_17A8EA4 = 545;
  result = 545;
  g_RoleSystemCombat.m_partyActor.m_fAnimDelta = 545;
  g_RoleSystemCombat.m_partyActor.m_dwMatMsg[0] = 545;
  dword_17A8EB0 = 545;
  return result;
}

// 0x004DB3F0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
int CCBSystem::InitCmdTable2_thunk()
{
  return this->CCBSystem::InitCmdTable2();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004DB400
int CCBSystem::InitCmdTable2()
{
  int result; // eax

  dword_17A8EB4 = 121;
  result = 709;
  dword_17A8EB8 = 316;
  dword_17A8EBC = 512;
  dword_17A8EC0 = 709;
  return result;
}

// 0x004DB440
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
int CCBSystem::InitCmdTable3_thunk()
{
  return this->CCBSystem::InitCmdTable3();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004DB450
int CCBSystem::InitCmdTable3()
{
  int result; // eax

  dword_17A8EC4 = 573;
  result = 573;
  dword_17A8EC8 = 573;
  dword_17A8ECC = 573;
  dword_17A8ED0 = 573;
  return result;
}

// 0x004DB490
CCBSystem * CCBSystem::InitCmd(int nVal)
{
  memset(this, 0, 0x1C8u);
  this->m_pUtil = ((CCBSystem *)((CCBSystem *)nVal));
  this->m_pUI = ((CCBUI *)(*(CCBUI **)(nVal + 4)));
  this->m_pControl = ((CCBControl *)(*(CCBControl **)(nVal + 16)));
  return this;
}

// 0x004DB4C0
int CCBSystem::ResetFlags()
{
  int result; // eax

  this->m_Thread[3].bValid = 1;
  this->m_Thread[3].bExecuted = 1;
  *(&this->m_Thread[3].bExecuted + 1) = 1;
  result = 0;
  memset(&this->m_pAttackSequen, 0, 0x1B8u);
  return result;
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

  this->CCBSystem::ResetFlags();
  if ( !this->m_pUtil )
    return 0;
  if ( !this->m_pUI )
    return 0;
  if ( !this->m_pControl )
    return 0;
  (((CCBAttackSequen *)this))->CCBAttackSequen::CalcTurnOrder();
  this->CCBSystem::InitRoleStateUI();
  if ( g_nCombatViewMode == 1 )
  {
    m_pAttackSequenBack = (UIStatic *)this->m_pUtil->m_pUI->m_pAttackSequenBack;
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pAttackSequenBack))((UIStatic *)(m_pAttackSequenBack), (_DWORD)(0));
    for ( i = 76; i < 120; i += 4 )
    {
      v5 = *(void ( ****)(_DWORD, _DWORD))((char *)((UIWnd *)this->m_pUtil->m_pUI) + i);
      (**v5)((_DWORD)(v5), (_DWORD)(0));
    }
    return 1;
  }
  else
  {
    v6 = (UIStatic *)this->m_pUtil->m_pUI->m_pAttackSequenBack;
    (**(void ( ***)(UIStatic *, int))((UIWnd *)v6))((UIStatic *)(v6), (int)(1));
    v7 = 0;
    for ( j = 76; j < 120; j += 4 )
    {
      m_pUtil = (CCBSystem *)this->m_pUtil;
      if ( this->m_pUtil->m_pRoleState->m_pObjMsgBuffer[v7 + 153] )
        (***(void ( ****)(_DWORD, int))((char *)((UIWnd *)m_pUtil->m_pUI) + j))((_DWORD)(*(_DWORD *)((char *)((UIWnd *)m_pUtil->m_pUI) + j)), (int)(1));
      else
        (***(void ( ****)(_DWORD, _DWORD))((char *)((UIWnd *)m_pUtil->m_pUI) + j))((_DWORD)(*(_DWORD *)((char *)((UIWnd *)m_pUtil->m_pUI) + j)), (_DWORD)(0));
      v7 += 892;
    }
    return 1;
  }
}

// 0x004DB690
char CCBSystem::GetCmdType(int idx)
{
  return *((_BYTE *)&this->m_pATSEffMgr + 40 * idx);
}

// 0x004DB6A0
bool CCBSystem::IsBusy(int a1)
{
  return *((_DWORD *)&this->m_pES + 10 * a1) >= 11500;
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
int CCBSystem::GetCmdCount(int idx, int a2)
{
  int result; // eax

  result = 5 * idx;
  *((_BYTE *)&this->m_pEffMgr + 40 * idx + 1) = a2;
  return result;
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
    (((CCBAttackSequen *)this))->CCBAttackSequen::SetPause(pData == 0);
    return this->CCBSystem::StoreThreadFlag(pData);
  }
  return result;
}

// 0x004DB920
int CCBSystem::SetCmdParam(int idx, int value)
{
  int result; // eax

  result = 5 * idx;
  *((_BYTE *)&this->m_pEffMgr + 40 * idx + 3) = value;
  return result;
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
    m_pRoleState = (CCBRoleState *)this->m_pUtil->m_pRoleState;
    if ( m_pRoleState->m_pObjMsgBuffer[v3 + 153] )
    {
      inited = (((CCBRoleState *)m_pRoleState))->CCBRoleState::InitUI(v1);
      sprintf((char *const)&g_RoleSystemCombat, "%s\\%s.tga", "ui\\combat\\attacksequen", inited->sModel);
      (((UIPushButton *)*(UIPushButton **)((char *)((UIWnd *)this->m_pUI) + i)))->UIPushButton::CreateFromTemplate(&g_RoleSystemCombat, 0);
    }
    ++v1;
    v3 += 892;
  }
}

// 0x004DC160
CCBSystem * CCBSystem::CopyCmdData(int *p_DWORD)
{
  memset(&this->m_p3DSpark, 0, 0x2Cu);
  memset(this, 0, 0x570u);
  this->CCBSystem::ClearAllPointers();
  this->m_pUtil = ((CCBSystem *)((CCBSystem *)p_DWORD));
  this->m_pUI = ((CCBUI *)((CCBUI *)p_DWORD[3]));
  this->m_pControl = ((CCBControl *)((CCBControl *)p_DWORD[5]));
  this->m_pAttackSequen = ((CCBAttackSequen *)((CCBAttackSequen *)p_DWORD[4]));
  this->m_pRoleState = ((CCBRoleState *)((CCBRoleState *)p_DWORD[1]));
  return this;
}

// 0x004DC1B0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
int CCBSystem::GetState()
{
  return this->CCBSystem::ClearAllPointers();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004DC1C0
int CCBSystem::ClearAllPointers()
{
  int result; // eax

  result = 0;
  BYTE4(this->m_dAbsTimeFund) = 0;
  this->m_pConfig = ((TxtFile *)0);
  this->m_pEffMgr = ((CEffMgr *)0);
  this->m_pATSEffMgr = ((CEffMgr *)0);
  this->m_p2DSpark = ((C2DSpark *)0);
  LOBYTE(this->m_pEffectSimple) = 0;
  this->m_fAbsTimeFund = NAN;
  this->m_fTimeScale = 0.0f;
  memset(&this->m_pFightInfo, 0, 0x500u);
  memset(&this->m_p3DSpark, 0, 0x2Cu);
  this->m_pES = ((CEffectSystem *)((CEffectSystem *)-1));
  BYTE1(this->m_pEffectSimple) = 0;
  this->m_pConfig = ((TxtFile *)0);
  this->m_pEffMgr = ((CEffMgr *)0);
  this->m_pATSEffMgr = ((CEffMgr *)0);
  this->m_p2DSpark = ((C2DSpark *)0);
  return result;
}

// 0x004DC3F0
char CCBSystem::StartRoleThread(int arg0)
{
    unsigned long reg_EAX = 0;

  _DWORD *v6; // eax
  _BYTE a2[16]; // [esp+0x10] [ebp-0x10] BYREF

  if ( LOBYTE(this->m_p2DSpark) == 1 )
    return 0;
  this->m_pConfig = ((TxtFile *)0);
  this->m_pEffMgr = ((CEffMgr *)0);
  this->m_pATSEffMgr = ((CEffMgr *)0);
  this->m_p2DSpark = ((C2DSpark *)0);
  memset(&this->m_p3DSpark, 0, 0x2Cu);
  LOBYTE(this->m_pEffectSimple) = 1;
  this->m_pES = ((CEffectSystem *)((CEffectSystem *)arg0));
  this->CCBSystem::FindFreeThread(0 /* TODO: pmf_to_u32((void (CCBRoleState::*)())CCBRoleState::InitCombatDialog) */, 0, 0, 0, 0, 0, 0, -1, 0);
  (((CCBAttackSequen *)this->m_pUI))->CCBAttackSequen::SetPause(1);
  (((CCBSystem *)this->m_pUI))->CCBSystem::SetCmdParam((int)this->m_pES, 1);
  reg_EAX = *((_DWORD *)&this->m_pControl->m_DeltaTime + (int)this->m_pES);
  __asm
  {
    fld     dword ptr [eax+0x19EC]
    fstp    dword ptr [eax+0x19E8]
  }
  *(float *)(reg_EAX + 6632) = _ET1;
  *(_BYTE *)(*((_DWORD *)&this->m_pControl->m_DeltaTime + (int)this->m_pES) + 280) = 1;
  if ( BYTE2(this->m_pUtil->m_nTimesOfCombat) )
  {
    v6 = (_DWORD *)sub_445FE0(a2);
    (((GRPinput *)&g_Input))->GRPinput::SetCursorPos((v6[2] + *v6) / 2, (v6[3] + v6[1]) / 2);
  }
  (((C2DSpark *)this->m_pUtil->m_p2DSpark))->C2DSpark::SetEnableMouseTrack(691, 36);
  return 1;
}

// 0x004DC510
double CCBSystem::ResetConfig(int nVal)
{
  TxtFile **p_m_pConfig; // ecx
  CCBAttackSequen *m_pUI; // ecx
  double result; // st7

  p_m_pConfig = (TxtFile **)&this->m_pConfig;
  *p_m_pConfig = 0;
  p_m_pConfig[1] = 0;
  p_m_pConfig[2] = 0;
  p_m_pConfig[3] = 0;
  memset(&this->m_p3DSpark, 0, 0x2Cu);
  m_pUI = (CCBAttackSequen *)this->m_pUI;
  LOBYTE(this->m_pEffectSimple) = 0;
  result = (((CCBAttackSequen *)m_pUI))->CCBAttackSequen::SetPause(0);
  *(_BYTE *)(*((_DWORD *)&this->m_pControl->m_DeltaTime + (int)this->m_pES) + 280) = 0;
  this->m_pES = ((CEffectSystem *)((CEffectSystem *)-1));
  return result;
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
    if ( (((CCBRoleState *)this))->CCBRoleState::CalcComboDirect((const void *)nVal, i) < 0
      && !(((CCBSystem *)*(CCBSystem **)(this->m_Thread[4].dwID + 12)))->CCBSystem::IsCmdEmpty(i)
      && !(((CCBSystem *)*(CCBSystem **)(this->m_Thread[4].dwID + 12)))->CCBSystem::IsCmdReady(i) )
    {
      (((CCBSystem *)*(CCBSystem **)(this->m_Thread[4].dwID + 12)))->CCBSystem::GetCmdData(i);
    }
  }
  return 1;
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
      return 0;
    }
  }
  return 1;
}

// 0x00500170
int CCBSystem::EndBattle(int nVal1)
{
  int v3; // eax
  _DWORD *v4; // edi
  char *v5; // ebp
  int v6; // eax

  v3 = 2632 * (int)this->m_Thread[0].fp[2];
  v4 = (_DWORD *)(&this->m_Thread[29].cmd.bMultiSrcRole + v3);
  v5 = (char *)&this->m_Thread[0].nTemp + 80 * (int)this->m_Thread[0].fp[3] + v3;
  if ( !(((CCBStage *)*((CCBStage **)&this->m_pAI + *v4)))->CCBStage::IsReady(*(unsigned int *)((char *)&this->m_Thread[29].cmd.dwCmdKind + v3)) )
    goto LABEL_7;
  if ( !v5[41] && (((CCBStage *)*((CCBStage **)&this->m_pAI + *v4)))->CCBStage::ForceDelTaskByPFN() )
  {
    (((CCBStage *)*((CCBStage **)&this->m_pAI + *v4)))->CCBStage::GetCurrentState();
    v6 = *((_DWORD *)&this->m_pAI + *v4);
    *(_DWORD *)(v6 + 6632) = *(_DWORD *)(v6 + 6636);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || (((CCBStage *)*((CCBStage **)&this->m_pAI + *v4)))->CCBStage::ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00504D60
char CCBSystem::CastProtect(int nCaster, int nTarget, float fVal)
{
  unsigned int v5; // eax
  int *v7; // [esp-0x8] [ebp-0x28]
  int *v8; // [esp-0x4] [ebp-0x24]

  v8 = (int *)(&this->m_Thread[50].nTemp + 6 * nTarget);
  v7 = (int *)(&this->m_Thread[50].nTemp + 6 * nCaster);
  v5 = (((CCBSystem *)*(CCBSystem **)this->m_Thread[4].cmd.dwCmdKind))->CCBSystem::ProcProtect();
  (((CCBStage *)this))->CCBStage::EnqueueCommand(0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessQueuedCommand) */, 0, 0, 0, v5, fVal, v7, v8) /* [ROWTABLE] */;
  return 1;
}

// 0x00512310
void CCBSystem::HandleInput()
{
  g_fCBTimeScale = 12.0 + 12.0;
}

// 0x00512320
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBSystem::SetQuitFlag()
{
  this->CCBSystem::IsEditorWindow();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00512330
bool CCBSystem::IsEditorWindow()
{
  bool result; // al

  g_nCBRolePos[0] = 119;
  result = -61;
  g_nCBRolePos[1] = 314;
  g_nCBRolePos[2] = 510;
  g_nCBRolePos[3] = 707;
  return result;
}

// 0x00512370
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBSystem::SetAuto()
{
  this->CCBSystem::SetAutoOnly();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00512380
void CCBSystem::SetAutoOnly()
{
  g_nCBRolePos[4] = 519;
  g_nCBRolePos[5] = 519;
  g_nCBRolePos[6] = 519;
  g_nCBRolePos[7] = 519;
}

// 0x005123C0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBSystem::ShowInfo()
{
  this->CCBSystem::SetTimeScale();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005123D0
void CCBSystem::SetTimeScale()
{
  g_nCBRolePos[8] = 128;
  g_nCBRolePos[9] = 323;
  g_nCBRolePos[10] = 519;
  g_nCBRolePos[11] = 716;
}

// 0x00512410
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
unsigned int CCBSystem::GetFreeID()
{
  return compiler_init_00512420();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00512460
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBSystem::DelAllTaskAndThread()
{
  this->CCBSystem::Proceed();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00512470
void CCBSystem::Proceed()
{
  g_nCBRolePos[16] = 121;
  g_nCBRolePos[17] = 316;
  g_nCBRolePos[18] = 512;
  g_nCBRolePos[19] = 709;
}

// 0x005124B0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
bool CCBSystem::CanBeHandleWPX_R()
{
  return this->CCBSystem::CanBeHandleNGH_R();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005124C0
bool CCBSystem::CanBeHandleNGH_R()
{
  bool result; // al

  g_nCBRolePos[20] = 573;
  result = 61;
  g_nCBRolePos[21] = 573;
  g_nCBRolePos[22] = 573;
  g_nCBRolePos[23] = 573;
  return result;
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

  p_cmd = (tagCmdData *)&this->m_Thread[0].cmd;
  v2 = 1024;
  do
  {
    v3 = (tagCmdData *)p_cmd;
    p_cmd += 2;
    --v2;
    memset(v3, 0, sizeof(tagCmdData));
  }
  while ( v2 );
  m_Player = this->m_Player;
  v5 = 11;
  do
  {
    v6 = (tagPlayerSet *)(m_Player++);
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
  unsigned int result; // eax

  result = 0;
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
  this->m_fTimeFund = 0.0f;
  HIDWORD(this->m_AbsDeltaTime) = 0;
  HIDWORD(this->m_dAbsTimeFund) = 0;
  this->m_fAbsTimeFund = 0.0f;
  HIBYTE(this->m_nTimesOfCombat) = 1;
  return result;
}

// 0x005125E0
char CCBSystem::ProcNormalAttack()
{
  std::codecvt_base *v2; // ecx
  CCBSystem *v3; // eax
  char result; // al
  CCBUI *v5; // eax
  CCBUI *v6; // eax
  CCBRoleState *v7; // eax
  CCBRoleState *v8; // eax
  CCBSystem *v9; // eax
  CCBAttackSequen *inited; // eax
  CCBStage *v11; // eax
  CCBStage *v12; // eax
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
  char pExceptionObject[1024]; // [esp+0xC] [ebp-0x100C] BYREF
  char ArgList[1024]; // [esp+0x40C] [ebp-C0Ch] BYREF
  char v32[1024]; // [esp+0x80C] [ebp-0x80C] BYREF
  char v33; // [esp+C0Ch] [ebp-0x40C] BYREF
  int v34; // [esp+0x1014] [ebp-0x4]

  this->CCBSystem::ProcDialog();
  v34 = 0;
  if ( operator new(1u) )
    v3 = (CCBSystem *)sub_51D5C0(this);
  else
    v3 = 0;
  this->m_pUtil = ((CCBSystem *)(v3));
  v34 = -1;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_6, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = (((std::codecvt_base *)v2))->do_always_noconv();
  if ( result )
  {
    v5 = (CCBUI *)operator new(0xA48u);
    v34 = 1;
    if ( v5 )
      (((CCBUI *)v5))->CCBUI::_todo_5160A0((int)this);
    else
      v6 = 0;
    v34 = -1;
    this->m_pUI = ((CCBUI *)(v6));
    if ( !v6 )
    {
      qmemcpy(
        pExceptionObject,
        (((Logger *)ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_6, 2504),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    result = sub_5163D0(v6);
    if ( result )
    {
      v7 = (CCBRoleState *)operator new(0x50A4u);
      v34 = 2;
      if ( v7 )
        v8 = (((CCBRoleState *)v7))->CCBRoleState::ClearAndSetGP((int)this);
      else
        v8 = 0;
      v34 = -1;
      this->m_pRoleState = ((CCBRoleState *)(v8));
      if ( !v8 )
      {
        qmemcpy(
          pExceptionObject,
          (((Logger *)ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_6, 2504),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      result = (((CIniFile *)v8))->CIniFile::LoadData();
      if ( result )
      {
        v9 = (CCBSystem *)operator new(0x1C8u);
        v34 = 3;
        if ( v9 )
          inited = (CCBAttackSequen *)(((CCBSystem *)v9))->CCBSystem::InitCmd((int)this);
        else
          inited = 0;
        v34 = -1;
        this->m_pAttackSequen = ((CCBAttackSequen *)(inited));
        if ( !inited )
        {
          qmemcpy(
            pExceptionObject,
            (((Logger *)ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_6, 2504),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        result = (((std::codecvt_base *)inited))->do_always_noconv();
        if ( result )
        {
          v11 = (CCBStage *)operator new(0xA48B0u);
          v34 = 4;
          if ( v11 )
            v12 = (CCBStage *)v11->CCBStage::CCBStage((int)this);
          else
            v12 = 0;
          v34 = -1;
          this->m_pStage = ((CCBStage *)(v12));
          if ( !v12 )
          {
            qmemcpy(
              pExceptionObject,
              (((Logger *)ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_6, 2504),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          result = (((CCBStageScene *)v12))->CCBStageScene::ResetSceneState();
          if ( result )
          {
            v13 = (CCBSystem *)operator new(0x570u);
            v34 = 5;
            if ( v13 )
              v14 = (CCBControl *)(((CCBSystem *)v13))->CCBSystem::CopyCmdData((int *)this);
            else
              v14 = 0;
            v34 = -1;
            this->m_pControl = ((CCBControl *)(v14));
            if ( !v14 )
            {
              qmemcpy(
                pExceptionObject,
                (((Logger *)ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_6, 2504),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            result = (((std::codecvt_base *)v14))->do_always_noconv();
            if ( result )
            {
              v15 = (CCBAI *)operator new(0xE50u);
              v34 = 6;
              if ( v15 )
                v16 = (((CCBAI *)v15))->CCBAI::Create((int *)this);
              else
                v16 = 0;
              v34 = -1;
              this->m_pAI = ((CCBAI *)(v16));
              if ( !v16 )
              {
                qmemcpy(v32, (((Logger *)&v33))->Logger::FormatException(&path[164], aDProjectPal3Co_6, 2504), sizeof(v32));
                _CxxThrowException(v32, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              result = (((std::codecvt_base *)v16))->do_always_noconv();
              if ( result )
              {
                this->m_pES = ((CEffectSystem *)((CEffectSystem *)g_pEffectSystem));
                this->CCBSystem::ProcAI(1.0);
                result = this->CCBSystem::CreateEditorObj(&this->m_pEditor);
                if ( result )
                {
                  v17 = (SceneMgr *)operator new(0xA930u);
                  v34 = 7;
                  if ( v17 )
                  {
                    m_pCam = (CCBStageCam *)this->m_pStage->m_pCam;
                    if ( m_pCam )
                      p_OrthoSize = (int)&m_pCam->OrthoSize;
                    else
                      p_OrthoSize = 0;
                    v20 = (((SceneMgr *)v17))->SceneMgr::Create((int)gfxMgr, p_OrthoSize, (int)this);
                  }
                  else
                  {
                    v20 = 0;
                  }
                  this->m_pEffMgr = ((CEffMgr *)(v20));
                  v21 = (SceneMgr *)operator new(0xA930u);
                  v34 = 8;
                  if ( v21 )
                  {
                    v22 = (CCBStageCam *)this->m_pStage->m_pCam;
                    if ( v22 )
                      v23 = (int)&v22->OrthoSize;
                    else
                      v23 = 0;
                    v24 = (((SceneMgr *)v21))->SceneMgr::Create((int)gfxMgr, v23, (int)this);
                  }
                  else
                  {
                    v24 = 0;
                  }
                  this->m_pATSEffMgr = ((CEffMgr *)(v24));
                  v25 = (C2DSpark *)operator new(0x5870u);
                  v34 = 9;
                  if ( v25 )
                    v25->C2DSpark::C2DSpark(g_DrvInfo.width, g_DrvInfo.height);
                  else
                    v26 = 0;
                  this->m_p2DSpark = ((C2DSpark *)(v26));
                  v27 = (C3DSpark *)operator new(0x3E30u);
                  v34 = 10;
                  if ( v27 )
                    v28 = (C3DSpark *)v27->C3DSpark::C3DSpark();
                  else
                    v28 = 0;
                  m_pES = (CEffectSystem *)this->m_pES;
                  this->m_p3DSpark = ((C3DSpark *)(v28));
                  this->m_pEffectSimple = ((CEffectSimple *)((CEffectSimple *)sub_4C5980((_Texture_uv *)m_pES, (_Texture_uv *)1)));
                  CEffectSystem_CEffectSystem((int)aEffectCombat10);
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
  CEffMgr *m_pEffMgr; // edi
  CEffMgr *m_pATSEffMgr; // edi
  C2DSpark *m_p2DSpark; // edi
  C3DSpark *m_p3DSpark; // ecx
  void *v21; // [esp+0x0] [ebp-0xC]

  m_pStage = (CCBStage *)this->m_pStage;
  if ( !m_pStage )
    return 0;
  (((CCBStage *)m_pStage))->CCBStage::Create();
  v3 = (CCBStage *)this->m_pStage;
  if ( v3 )
  {
    NullCallback(v21);
    operator delete(v3);
  }
  this->m_pStage = ((CCBStage *)0);
  m_pAttackSequen = (std::codecvt_base *)this->m_pAttackSequen;
  if ( !m_pAttackSequen )
    return 0;
  (((std::codecvt_base *)m_pAttackSequen))->do_always_noconv();
  v5 = (CCBAttackSequen *)this->m_pAttackSequen;
  if ( v5 )
  {
    NullCallback(v21);
    operator delete(v5);
  }
  this->m_pAttackSequen = ((CCBAttackSequen *)0);
  m_pRoleState = (CCBRoleState *)this->m_pRoleState;
  if ( !m_pRoleState )
    return 0;
  (((CCBRoleState *)m_pRoleState))->CCBRoleState::IterateMagicSlots();
  v7 = (CCBRoleState *)this->m_pRoleState;
  if ( v7 )
  {
    NullCallback(v21);
    operator delete(v7);
  }
  this->m_pRoleState = ((CCBRoleState *)0);
  m_pControl = (std::codecvt_base *)this->m_pControl;
  if ( !m_pControl )
    return 0;
  (((std::codecvt_base *)m_pControl))->do_always_noconv();
  v9 = (CCBControl *)this->m_pControl;
  if ( v9 )
  {
    (((CCBSystem *)this->m_pControl))->CCBSystem::GetState();
    operator delete(v9);
  }
  this->m_pControl = ((CCBControl *)0);
  m_pUI = (CCBUI *)this->m_pUI;
  if ( !m_pUI )
    return 0;
  (*(void ( **)(CCBUI *))(*(_DWORD *)((UIWnd *)m_pUI) + 12))(m_pUI);
  v11 = (CCBUI *)this->m_pUI;
  if ( v11 )
    (*(void ( **)(CCBUI *, int))(*(_DWORD *)((UIWnd *)v11) + 20))(v11, 1);
  this->m_pUI = ((CCBUI *)0);
  m_pAI = (std::codecvt_base *)this->m_pAI;
  if ( !m_pAI )
    return 0;
  (((std::codecvt_base *)m_pAI))->do_always_noconv();
  v13 = (CCBAI *)this->m_pAI;
  if ( v13 )
    (((CCBSystem *)v13))->CCBSystem::_scalar_deleting_destructor_((CCBSystem *)1, (char)v21);
  this->m_pAI = ((CCBAI *)0);
  m_pEditor = (CCBEditor *)this->m_pEditor;
  if ( !m_pEditor )
    return 0;
  (((CCBStage *)m_pEditor))->CCBStage::DestroyDialog();
  v15 = (CCBEditor *)this->m_pEditor;
  if ( v15 )
    (((CCBSystem *)v15))->CCBSystem::DestroyObj_5df0((CCBSystem *)1, (char)v21);
  this->m_pEditor = ((CCBEditor *)0);
  if ( !this->m_pUtil )
    return 0;
  (((std::codecvt_base *)v15))->do_always_noconv();
  if ( this->m_pUtil )
    (((CCBSystem *)this->m_pUtil))->CCBSystem::_scalar_deleting_destructor_((CCBSystem *)1, (char)v21);
  m_pEffMgr = (CEffMgr *)this->m_pEffMgr;
  this->m_pUtil = ((CCBSystem *)0);
  if ( m_pEffMgr )
  {
    (((CEffMgr *)m_pEffMgr))->CEffMgr::ReleaseAllRefs();
    operator delete(m_pEffMgr);
    this->m_pEffMgr = ((CEffMgr *)0);
  }
  m_pATSEffMgr = (CEffMgr *)this->m_pATSEffMgr;
  if ( m_pATSEffMgr )
  {
    (((CEffMgr *)this->m_pATSEffMgr))->CEffMgr::ReleaseAllRefs();
    operator delete(m_pATSEffMgr);
    this->m_pATSEffMgr = ((CEffMgr *)0);
  }
  m_p2DSpark = (C2DSpark *)this->m_p2DSpark;
  if ( m_p2DSpark )
  {
    (((C2DSpark *)this->m_p2DSpark))->C2DSpark::~C2DSpark();
    operator delete(m_p2DSpark);
    this->m_p2DSpark = ((C2DSpark *)0);
  }
  m_p3DSpark = (C3DSpark *)this->m_p3DSpark;
  if ( m_p3DSpark )
  {
    (((CCBSystem *)m_p3DSpark))->CCBSystem::ProcCoAttack((CCBSystem *)1, (char)v21);
    this->m_p3DSpark = ((C3DSpark *)0);
  }
  return 1;
}

// 0x00512D40
void * CCBSystem::ProcCoAttack(CCBSystem *Block, char formal)
{
  (((C3DSpark *)this))->C3DSpark::~C3DSpark();
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00512D60
char CCBSystem::ProcWeaponSkill()
{
  char result; // al
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
  gbColorQuad v17; // [esp+0x4] [ebp-0xC]

  if ( !this->m_pUtil || !(((CCBLineupWindow *)this))->CCBLineupWindow::IsFaceOnInitPos() /* [ROWTABLE] */ )
    return 0;
  m_pUI = (CCBUI *)this->m_pUI;
  if ( !m_pUI || !(((CCBUI *)m_pUI))->CCBUI::CreateParaWindow() )
    return 0;
  m_pControl = (CCBControl *)this->m_pControl;
  if ( !m_pControl || !(((CCBUI *)m_pControl))->CCBUI::IsActive() )
    return 0;
  m_pRoleState = (CCBRoleState *)this->m_pRoleState;
  if ( !m_pRoleState || !(((CCBRoleState *)m_pRoleState))->CCBRoleState::DestroyAndReinit() )
    return 0;
  m_pAttackSequen = (CCBAttackSequen *)this->m_pAttackSequen;
  if ( !m_pAttackSequen || !(((CCBSystem *)m_pAttackSequen))->CCBSystem::DestroySubsystems() )
    return 0;
  m_pStage = (CCBStage *)this->m_pStage;
  if ( !m_pStage || !(((CCBStage *)m_pStage))->CCBStage::Destroy() )
    return 0;
  m_pAI = (CCBAI *)this->m_pAI;
  if ( !m_pAI || !(((CCBAI *)m_pAI))->CCBAI::Init() )
    return 0;
  if ( BYTE1(this->m_nTimesOfCombat) )
  {
    m_pEditor = (CCBEditor *)this->m_pEditor;
    if ( !m_pEditor || !(((CCBStage *)m_pEditor))->CCBStage::CreatePreviewDialog() )
      return 0;
  }
  m_pEffMgr = (CEffMgr *)this->m_pEffMgr;
  if ( !m_pEffMgr || !(((Combat *)m_pEffMgr))->Combat::ReleaseCompletedEffects() )
    return 0;
  m_pATSEffMgr = (CEffMgr *)this->m_pATSEffMgr;
  if ( !m_pATSEffMgr || !(((Combat *)m_pATSEffMgr))->Combat::ReleaseCompletedEffects() )
    return 0;
  (((C2DSpark *)0))->C2DSpark::CreateTrack(v16, v17);
  (((C2DSpark *)this->m_p2DSpark))->C2DSpark::CreateStars();
  (((C3DSpark *)this->m_p3DSpark))->C3DSpark::DestroyAll();
  v12 = 0;
  this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::Message, 0, 0, 0, 0);
  (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::SetPause(0);
  for ( i = 0; i < 4460; i += 892 )
  {
    v14 = (CCBRoleState *)this->m_pRoleState;
    if ( v14->m_pObjMsgBuffer[i + 153] )
    {
      LOBYTE((((CCBRoleState *)v14))->CCBRoleState::InitUI(v12)[1].dwMagicID[2][4]) = 0;
      BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v12)[1].dwMagicID[2][4]) = 0;
    }
    ++v12;
  }
  (((CCBSystem *)this->m_pEffectSimple))->CCBSystem::GetThreadBase();
  (((gbSceneGraph *)gfxMgr->pSceneGraph))->gbSceneGraph::ResetBladeMgr();
  v15 = (CCBRoleState *)this->m_pRoleState;
  if ( v15->m_pObjMsgBuffer[113] && *((_BYTE *)(((CEffectSystem *)v15))->CEffectSystem::DestroyAllEffect() + 4) )
  {
    (((CCBCamControl *)this->m_pStage->m_pCamControl))->CCBCamControl::ClearFinishedTask(20);
    result = 1;
    HIBYTE(this->m_nTimesOfCombat) = 1;
  }
  else
  {
    (((CCBCamControl *)this->m_pStage->m_pCamControl))->CCBCamControl::ClearFinishedTask(0);
    result = 1;
    HIBYTE(this->m_nTimesOfCombat) = 1;
  }
  return result;
}

// 0x00512F40
char CCBSystem::ProcMagicWait(unsigned int formal, char pData)
{
  int v4; // ecx
  UICursor *v5; // ecx
  unsigned int v6; // ebx
  RoleAtt **v7; // edi
  unsigned int formala; // [esp+0x1C] [ebp+0x8]
  char v10; // [esp+0x23] [ebp+0xF]

  this->CCBSystem::ProcDialog();
  v4 = *(_DWORD *)&this->m_bFiveNimbus + 1;
  BYTE1(this->m_nTimesOfCombat) = pData;
  this->m_bQuitFlag = 0;
  *(_DWORD *)&this->m_eState = 2;
  *(_DWORD *)&this->m_eResult = 1;
  *(_DWORD *)&this->m_bFiveNimbus = v4;
  ++dword_C10CD4;
  this->m_pFightInfo = ((FightInfo *)((FightInfo *)formal));
  v10 = this->CCBSystem::ProcWeaponSkill();
  (((UICursor *)v5))->UICursor::_todo_541CC0();
  v6 = 0;
  v7 = (RoleAtt **)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[4];
  formala = 0;
  do
  {
    if ( this->m_pRoleState->m_pObjMsgBuffer[formala + 153] && (*(v7 - 3) == (RoleAtt *)8114 || *v7 == (RoleAtt *)8114) )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
      if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)102.39999 )
        (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::ProcessRound(v6, 23, 1, 1);
    }
    v7 += 352;
    ++v6;
    formala += 892;
  }
  while ( (int)v7 < (int)&unk_C062A4 );
  return v10;
}

// 0x00513060
int CCBSystem::CombatUpdate(double dt)
{
  double v3; // st6
  double v4; // st7
  double v5; // st7
  CCBEditor *m_pEditor; // ecx
  int result; // eax
  float fVal; // [esp+0x0] [ebp-0x8]
  float dta; // [esp+0xC] [ebp+0x4]

  this->m_AbsDeltaTime = dt;
  v3 = dt + this->m_dAbsTimeFund;
  this->m_dAbsTimeFund = v3;
  this->m_fAbsTimeFund = v3;
  v4 = dt * this->m_fTimeScale;
  this->m_DeltaTime = v4;
  v5 = v4 + this->m_dTimeFund;
  dta = v5;
  this->m_dTimeFund = v5;
  this->m_fTimeFund = v5;
  SceneMgrUpdate(dta);
  SceneMgrUpdate(this->m_fAbsTimeFund);
  this->CCBSystem::ProcMagic();
  this->CCBSystem::IsFriendDoSkill();
  (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::ResetTimers();
  (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::Update();
  (((CCBAI *)this->m_pAI))->CCBAI::Update();
  (((CCBStage *)this->m_pStage))->CCBStage::Update();
  (((CCBControl *)this->m_pControl))->CCBControl::GetActiveAttackCount();
  if ( BYTE1(this->m_nTimesOfCombat) )
  {
    m_pEditor = (CCBEditor *)this->m_pEditor;
    if ( m_pEditor )
      (((CCBUI *)m_pEditor))->CCBUI::StepFrame();
  }
  fVal = this->m_DeltaTime;
  (((C2DSpark *)this->m_p2DSpark))->C2DSpark::Render(fVal);
  Update(this->m_p3DSpark);
  return this->CCBSystem::ProcDefence();
}

// 0x00513120
char CCBSystem::RenderCheck()
{
  char result; // al
  float v3; // [esp+0x0] [ebp-0x4]

  result = HIBYTE(this->m_nTimesOfCombat);
  if ( result )
  {
    HIBYTE(this->m_nTimesOfCombat) = 0;
  }
  else
  {
    (((CCBStage *)v3))->CCBStage::EditorUpdate();
    (((C2DSpark *)this->m_p2DSpark))->C2DSpark::DestroyAll();
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
  if ( g_nCombatViewMode == 1 )
  {
    if ( g_Input.KeyInfo[15].PressTime == 1 || g_Input.KeyInfo[16].PressTime == 1 )
    {
      v3 = 0;
      for ( i = 24; i < 68; i += 4 )
      {
        if ( (((CCBStage *)*(CCBStage **)((char *)&this->m_pStage->m_pCBSystem + i)))->CCBStage::CheckViewTarget() )
        {
          (((CCBStage *)this->m_pStage))->CCBStage::DoTask(v3);
          v2 = 1;
        }
        ++v3;
      }
      if ( !v2 )
      {
        (((CCBStage *)this->m_pStage))->CCBStage::DoTask(-1);
        if ( (((CCBStageScene *)this->m_pStage->m_pScene))->CCBStageScene::LoadFlingNode() )
          LOBYTE(this->m_pStage->m_pScene->m_vecEnemyFiveLineupPos.y) = 1;
      }
    }
    if ( (g_Input.KeyInfo[15].Data & 0xF) != 1 && (g_Input.KeyInfo[16].Data & 0xF) != 1 )
    {
      (((CCBStage *)this->m_pStage))->CCBStage::DoTask(-1);
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
        m_pRoleState = (CCBRoleState *)this->m_pRoleState;
        if ( m_pRoleState->m_pObjMsgBuffer[j + 153] )
        {
          BYTE1((((CCBRoleState *)m_pRoleState))->CCBRoleState::InitUI(v6)[1].dwMagicID[1][0]) = 0;
          LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v6)[1].dwMagicID[0][5]) = 0;
          BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v6)[1].dwMagicID[0][5]) = 0;
          BYTE2((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v6)[1].dwMagicID[0][5]) = 0;
          HIBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v6)[1].dwMagicID[0][5]) = 0;
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
        if ( v11->m_pObjMsgBuffer[k + 153] )
        {
          LOBYTE((((CCBRoleState *)v11))->CCBRoleState::InitUI(v9)[1].dwMagicID[2][4]) = 1;
          BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v9)[1].dwMagicID[2][4]) = 0;
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
        LOBYTE(inited) = (unsigned long)v14->m_pObjMsgBuffer[m + 153];
        if ( (_BYTE)inited )
        {
          BYTE1((((CCBRoleState *)v14))->CCBRoleState::InitUI(v12)[1].dwMagicID[2][4]) = 1;
          inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v12);
          LOBYTE(inited[1].dwMagicID[2][4]) = 0;
        }
        ++v12;
      }
    }
  }
  return (char)inited;
}

// 0x00513330
int CCBSystem::GetRenderFlag(int a2)
{
  int result; // eax
  CScreenMode *Instance; // eax

  LOBYTE(result) = a2;
  this->m_bQuitFlag = a2;
  if ( (_BYTE)a2 == 1 )
  {
    (((gbSceneGraph *)gfxMgr->pSceneGraph))->gbSceneGraph::ResetBladeMgr();
    (((CEffMgr *)this->m_pEffMgr))->CEffMgr::ReleaseCompletedEffects();
    LOBYTE(result) = (((CEffMgr *)this->m_pATSEffMgr))->CEffMgr::ReleaseCompletedEffects();
    if ( *(_DWORD *)&this->m_eResult == 3 )
    {
      LOBYTE(result) = (unsigned long)this->m_pFightInfo->eBattleFieldAttr;
      if ( (_BYTE)result )
      {
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        return (((CScreenMode *)Instance))->CScreenMode::StopAll();
      }
    }
  }
  return result;
}

// 0x00513380
bool CCBSystem::ProcUseItem(HWND formal)
{
  return (((CCBStage *)this->m_pEditor))->CCBStage::ProcessAction(formal);
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
    BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v3)[1].dwMagicID[1][0]) = this->m_nTimesOfCombat;
    LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v3)[1].dwMagicID[0][5]) = this->m_nTimesOfCombat;
    BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v3)[1].dwMagicID[0][5]) = this->m_nTimesOfCombat;
    BYTE2((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v3)[1].dwMagicID[0][5]) = this->m_nTimesOfCombat;
    result = (int)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v3++);
    *(_BYTE *)(result + 835) = this->m_nTimesOfCombat;
  }
  while ( v3 < 5 );
  return result;
}

// 0x00513420
char CCBSystem::ProcFlee(char formal)
{
  char result; // al

  result = formal;
  LOBYTE(this->m_nTimesOfCombat) = formal;
  return result;
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
  (((Combat *)this->m_pStage->m_TempStorageNGH))->Combat::LogMessage((char *)5, 75, "Thread=%d, StageTask=%d", this->m_dwIDHolder, this->m_pStage->m_nTaskCount);
  (((Combat *)this->m_pStage->m_TempStorageNGH))->Combat::LogMessage((char *)5, 90, "Times of Combat=%d", *(_DWORD *)&this->m_bFiveNimbus);
  (((Combat *)this->m_pStage->m_TempStorageNGH))->Combat::LogMessage((char *)5, 105, "TimeFund=%f", this->m_fTimeFund);
  (((Combat *)this->m_pStage->m_TempStorageNGH))->Combat::LogMessage((char *)5, 120, "DeltaTime=%f", this->m_DeltaTime);
  (((Combat *)this->m_pStage->m_TempStorageNGH))->Combat::LogMessage((char *)5, 195, "Effect objects %d", *(_DWORD *)&this->m_pEffMgr->_tail_000[43292]);
  (((Combat *)this->m_pStage->m_TempStorageNGH))->Combat::LogMessage((char *)5, 210, "Effect Timer %f", *(float *)&this->m_pEffMgr->_tail_000[43304]);
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
    result = (((Combat *)this->m_pStage->m_TempStorageNGH))->Combat::LogMessage((char *)0x17C, v3, "Role%d x=%f, z=%f, rot=%f", v2++, *(float *)g_nCBRoundCount, *(float *)&g_nCBRoundCount[2], v7);
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

  m_pES = (CEffectSystem *)this->m_pES;
  this->m_fTimeScale = formal;
  m_pES->m_fTimeFund = formal;
  m_pEffMgr = (CEffMgr *)this->m_pEffMgr;
  if ( m_pEffMgr )
    (((CEffMgr *)m_pEffMgr))->CEffMgr::SetEffectsTimeScale(SLODWORD(formal));
  m_pATSEffMgr = (CEffMgr *)this->m_pATSEffMgr;
  if ( m_pATSEffMgr )
    (((CEffMgr *)m_pATSEffMgr))->CEffMgr::SetEffectsTimeScale(1065353216);
  v6 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( this->m_pRoleState->m_pObjMsgBuffer[v6 + 153] )
      *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[1].dwReturn = formal;
    v6 += 892;
  }
  m_pPointer = (gbGeomNode *)this->m_pStage->m_pScene->m_pPointer;
  if ( m_pPointer )
    (((gbVisNode *)m_pPointer))->gbVisNode::SetTimeScale(formal);
  if ( BYTE1(this->m_nTimesOfCombat) )
    CCBStage::CreatePreview(formal);
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

  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->nProtectRole == idx )
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->nProtectRole = -1;
  m_pControl = (CCBControl *)this->m_pControl;
  if ( m_pControl->m_bActive && (((CCBControl *)m_pControl))->CCBControl::GetControl() == idx )
  {
    (((CCBControl *)this->m_pControl))->CCBControl::GetState();
    v4 = 0;
    for ( i = 24; i < 68; i += 4 )
    {
      if ( this->m_pRoleState->m_pObjMsgBuffer[v4 + 153] )
      {
        LOBYTE((*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[1].cmd.dwCmdKind) = 0;
        BYTE2((*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[1].nTemp) = 0;
      }
      v4 += 892;
    }
  }
  (((CCBStage *)idx))->CCBStage::IsTaskValidButNotFinish(v8, v9);
  (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(idx);
  (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::InvokeThreadMethod(idx, 0);
  this->m_pStage->m_pRole[idx]->m_bShowWeapon = 0;
  this->m_pStage->m_pRole[idx]->m_bFlash = 0;
  (((CCBStage *)this->m_pStage->m_pRole[idx]))->CCBStage::ClearAniMsg(0, 1.0);
  inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(idx);
  memset((char *)&inited->byMagicUseTime[8][5] + 1, 0, 0x18u);
  *(_WORD *)&inited[1].sModel[5] = 0;
  inited[1].sModel[7] = 0;
  memset(&inited[1].sModel[8], 0, 0x34u);
  LOWORD(inited[1].nSpeed) = 0;
  memset((char *)&inited[1].nSpeed + 2, 0, 0x34u);
  HIWORD(inited[1].fHPIncPerRound) = 0;
  LOBYTE(inited->byMagicUseTime[8][5]) = 0;
  (((CCBStage *)this->m_pStage->m_pRole[idx]))->CCBStage::DangerForceRelease(0);
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

  if ( BYTE1(this->m_nTimesOfCombat) && g_nCombatViewMode != 2 )
    return 0;
  p_m_CmdData = 0;
  if ( (unsigned __int8)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetForce(0) || *(_DWORD *)&this->m_eState != 2 )
  {
    m_pControl = (CCBControl *)this->m_pControl;
    if ( m_pControl->m_bActive )
      (((CCBControl *)m_pControl))->CCBControl::GetState();
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
      if ( !this->m_pRoleState->m_pObjMsgBuffer[v17 + 153]
        || !(((CCBStage *)*(CCBStage **)((char *)&this->m_pStage->m_pCBSystem + v3)))->CCBStage::ForceDelTaskByPFN() )
      {
        goto LABEL_39;
      }
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::ProcessCombatAction(v5) )
      {
        (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::SetPause(1);
        return 0;
      }
      if ( (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdType(v5) == 1
        && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v5) == 1
        && (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(v5) == 1
        && (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::IsBusy(v5) )
      {
        if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v5, 17)
          || (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v5, 14) )
        {
          goto LABEL_38;
        }
        if ( !BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v5)[1].dwMagicID[1][0])
          && !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v5, 18)
          && !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v5, 19) )
        {
          (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::ProcessCombatDialog(v5);
          if ( !BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v5)[1].dwMagicID[2][4])
            || (v6 = (((CCBAI *)this->m_pAI))->CCBAI::HandleFriendAffirmative(v5, 1),
                BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v5)[1].dwMagicID[2][4]) = 0,
                !v6) )
          {
            if ( !LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v5)[1].dwMagicID[2][4]) )
            {
              nVal3 = v5;
              (((CCBSystem *)this->m_pControl))->CCBSystem::StartRoleThread(v5);
              return 0;
            }
            if ( m_Player->LastRoleCmd.bValid )
            {
              (((CCBAI *)this->m_pAI))->CCBAI::HandlePlayerNormalAttack(v5, (int)m_Player);
              for ( j = 0; j < 5; ++j )
              {
                inited = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(j);
                LOBYTE(inited[1].dwMagicID[2][4]) = 0;
              }
            }
            else
            {
              (((CCBAI *)this->m_pAI))->CCBAI::HandleFriendAffirmative(v5, 0);
              for ( k = 0; k < 5; ++k )
              {
                v10 = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(k);
                LOBYTE(v10[1].dwMagicID[2][4]) = 0;
              }
            }
          }
          goto LABEL_39;
        }
        (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::ProcessCombatDialog(v5);
        (((CCBAI *)this->m_pAI))->CCBAI::HandleEnemyChaos(v5);
      }
      if ( (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdType(v5) != 1
        || (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsRoleAlive(v5) != 1
        || (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::IsActive(v5)
        || !(((CCBSystem *)this->m_pAttackSequen))->CCBSystem::IsBusy(v5) )
      {
        goto LABEL_39;
      }
      if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v5, 17)
        || (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v5, 14)
        || HIBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v5)[1].dwMagicID[2][4]) )
      {
LABEL_38:
        (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdData(v5);
        goto LABEL_39;
      }
      (((CCBAI *)this->m_pAI))->CCBAI::Render(v5);
LABEL_39:
      v3 = v18 + 4;
      v17 += 892;
      ++v5;
      m_Player = (tagPlayerSet *)(i + 1);
      v11 = v18 + 4 < 68;
      v18 += 4;
      if ( !v11 )
        return 0;
    }
  }
  (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::SetPause(1);
  v13 = (CCBControl *)this->m_pControl;
  if ( v13->m_CmdData.bValid )
    p_m_CmdData = (int *)&v13->m_CmdData;
  Control = (((CCBControl *)v13))->CCBControl::GetControl();
  if ( BYTE1((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(Control)[1].dwMagicID[2][4])
    || (v15 = (((CCBControl *)this->m_pControl))->CCBControl::GetControl(),
        LOBYTE((((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v15)[1].dwMagicID[2][4])) )
  {
    nVal3 = -1;
    (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::SetPause(0);
    (((CCBControl *)this->m_pControl))->CCBControl::GetState();
    return 0;
  }
  if ( (((CCBControl *)this->m_pControl))->CCBControl::GetControl() != nVal3 || !p_m_CmdData )
    return 0;
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(nVal3, 14) )
  {
    (((CCBControl *)this->m_pControl))->CCBControl::GetState();
    return 0;
  }
  else
  {
    switch ( *p_m_CmdData )
    {
      case 259:
        this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::IsRoleWaitForFlee, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 260:
        this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::GetThreadIndex, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 261:
        this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::GetSameThreadNum, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 262:
        this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::PassCmdToThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 264:
      case 266:
      case 268:
        this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::AllocThread, 0, 0, 0, p_m_CmdData);
        break;
      case 265:
        this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::PassCmdViaThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 267:
        this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::PassCmdToThread, 0, 0, 0, p_m_CmdData);
        qmemcpy(&this->m_Player[nVal3], p_m_CmdData, 0x2Cu);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      case 269:
        this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::DelThread, 0, 0, 0, p_m_CmdData);
        this->m_pAI->m_bNewRole[nVal3] = 0;
        break;
      default:
        break;
    }
    (((CCBSystem *)this->m_pControl))->CCBSystem::ResetConfig(p_m_CmdData[2]);
    nVal3 = -1;
    return 0;
  }
}

// 0x00513EB0
int CCBSystem::Message(char *pMsg, char *pTitle, unsigned int uType)
{
  CCBSystem *v3; // ecx
  CCBSystem *v4; // esi
  int RoleIndex; // edi

  v4 = (CCBSystem *)v3;
  BYTE2(v3->m_pFightInfo->nRoleWillNotBeAttack) = 0;
  RoleIndex = (((CCBStage *)v3->m_pStage))->CCBStage::GetRoleIndex(3, 0, 1);
  if ( RoleIndex != -1 )
  {
    if ( v4->m_pRoleState->m_pObjMsgBuffer[113]
      || ((((CCBStage *)v4->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::IsSubTaskFinished */, 0, 0, 0, 0, -1082130432, 1082130432),
          (((CCBStage *)v4->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((bool (CCBStage::*)(int))CCBStage::IsAllSubTaskFinished) */, 0, 0, 0, 0, 0, 1082130432),
          v4->m_pRoleState->m_pObjMsgBuffer[112]) )
    {
      (((CCBStage *)v4->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((bool (CCBStage::*)(int))CCBStage::IsIdle) */, 0, 0, 0, 0, 0, 1077936128);
    }
    (((CCBStage *)v4->m_pStage))->CCBStage::GetStageRoleByIdx(RoleIndex);
  }
  (((CCBSystem *)v4))->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::CheckBattleEnd, 0, 0, 0, 0);
  (((CCBSystem *)v4))->CCBSystem::ClearEffect(v4->m_nThread);
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
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    p_cmd = (tagCmdData *)&this->m_Thread[m_nThread].cmd;
    if ( !(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SumGPCost((int)p_cmd) )
    {
LABEL_11:
      (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
      goto LABEL_12;
    }
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 1);
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CheckVarianceRound(v4->cmd.nSrcRole, 0, &pnVal);
    if ( v6 == 1 )
    {
      nSrcRole = v4->cmd.nSrcRole;
      p_cmd->dwCmdKind = 270;
      v4->cmd.dwItemID = pnVal;
      (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(nSrcRole);
      this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::AddThread, 0, 0, 0, &v4->cmd);
LABEL_12:
      this->CCBSystem::ClearEffect(this->m_nThread);
      return 0;
    }
    RoleIndex = (((CCBStage *)this->m_pStage))->CCBStage::GetRoleIndex(11, &v4->cmd, 0);
    v9 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    if ( RoleIndex != -1 )
    {
      p_DWORD = 0;
      v15 = 0;
      nDestRole = 0;
      v15 = v4->cmd.nSrcRole;
      nDestRole = v4->cmd.nDestRole;
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int 74))CCBStage::ProcShowSneakAttackState) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::HandleKeyCtrl) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcShowName) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetStageRoleByIdx(v9);
    }
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  (((CCBStage *)this->m_pStage))->CCBStage::DelTask(v4->nTaskIndex, &p_BYTE, &v13);
  if ( p_BYTE == 1 )
  {
    if ( v4->nTaskIndex != -1 )
      (((CCBStage *)this->m_pStage))->CCBStage::GetStageRole(v4->nTaskIndex);
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
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::SetPause(1);
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitRoleFiveMagic((int)&v4->cmd);
    RoleIndex = (((CCBStage *)this->m_pStage))->CCBStage::GetRoleIndex(12, &v4->cmd, 0);
    v6 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    if ( RoleIndex == -1 )
    {
      v4->bExecuted = 1;
      (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::SetPause(0);
      (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
      this->CCBSystem::ClearEffect(this->m_nThread);
      return 0;
    }
    p_DWORD = 0;
    nSrcRole = 0;
    nDestRole = 0;
    nSrcRole = v4->cmd.nSrcRole;
    nDestRole = v4->cmd.nDestRole;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    p_DWORD = -1;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::CCBRoleState_Func) */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    p_DWORD = 0;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((int (CCBCamControl::*)(int))CCBCamControl::ProcessCamMove) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcShowDamage) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    p_DWORD = -1;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, (int)CCBRoleState_CalcTurnDelay, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    p_DWORD = 0;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::ClearRoleAllTask) */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcTaskSlot) */, 0, 0, 0, &p_DWORD, 0, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcShowCost) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcTaskSlot) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((int (CCBRoleState::*)(int))CCBRoleState::CCBRoleState_Func) */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcShowCombatDialog) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, (int)CCBRoleState_CalcTurnDelay, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v6, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetStageRoleByIdx(v6);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  (((CCBStage *)this->m_pStage))->CCBStage::DelTask(v4->nTaskIndex, &p_BYTE, &v9);
  if ( p_BYTE == 1 )
  {
    if ( v4->nTaskIndex != -1 )
      (((CCBStage *)this->m_pStage))->CCBStage::GetStageRole(v4->nTaskIndex);
    (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::SetPause(0);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
    this->CCBSystem::ClearEffect(this->m_nThread);
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
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    v4->cmd.bValid = 1;
    v4->cmd.nSrcRole = 0;
    v4->cmd.dwCmdKind = 269;
    v5 = *(_DWORD *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(0)->byMagicUseTime[3][5];
    v4->cmd.nDestRole = -1;
    v4->cmd.dwItemID = v5;
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleNum((int *)&v4->cmd);
    RoleIndex = (((CCBStage *)this->m_pStage))->CCBStage::GetRoleIndex(11, &v4->cmd, 0);
    v7 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    if ( RoleIndex != -1 )
    {
      p_DWORD = 0;
      nSrcRole = 0;
      nDestRole = 0;
      nSrcRole = v4->cmd.nSrcRole;
      nDestRole = v4->cmd.nDestRole;
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::ClearRoleAllTask) */, 0, 0, 0, &p_DWORD, -1082130432, 1065353216);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskResetToIdle) */, 0, 0, 0, &p_DWORD, 0, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskExecMagicEffect) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((int (CCBSystem::*)(int))CCBSystem::EndBattle) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, &p_DWORD, -1082130432, 0);
      (((CCBStage *)this->m_pStage))->CCBStage::GetStageRoleByIdx(v7);
    }
    *(_DWORD *)&(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v4->cmd.nSrcRole)->byMagicUseTime[4][3] = 0;
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  (((CCBStage *)this->m_pStage))->CCBStage::DelTask(v4->nTaskIndex, &p_BYTE, &v10);
  if ( p_BYTE == 1 )
  {
    if ( v4->nTaskIndex != -1 )
      (((CCBStage *)this->m_pStage))->CCBStage::GetStageRole(v4->nTaskIndex);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
    this->CCBSystem::ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00514870
int CCBSystem::GetSameThreadNum(int fp)
{
  int m_nThread; // eax
  tagThread *v4; // edi
  char v5; // al
  int SkillCostLevel; // eax
  int v8; // ebx
  int v9; // eax
  CCBControl *m_pControl; // ecx
  int nSrcRole; // [esp-0x4] [ebp-0x14]
  int pnVal; // [esp+0xC] [ebp-0x4] BYREF

  pnVal = 0;
  m_nThread = this->m_nThread;
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CheckVarianceRound(this->m_Thread[m_nThread].cmd.nSrcRole, this->m_Thread[m_nThread].cmd.dwItemID, &pnVal);
    if ( v5 == 1 )
    {
      nSrcRole = v4->cmd.nSrcRole;
      v4->cmd.dwCmdKind = 270;
      v4->cmd.dwItemID = pnVal;
      (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(nSrcRole);
      this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::AddThread, 0, 0, 0, &v4->cmd);
LABEL_20:
      this->CCBSystem::ClearEffect(this->m_nThread);
      return 0;
    }
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
    if ( !(((CCBSystem *)this->m_pAttackSequen))->CCBSystem::IsBusy(v4->cmd.nSrcRole) )
    {
      this->CCBSystem::ClearEffect(this->m_nThread);
      return -1;
    }
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::ClearCmdSlot(v4->cmd.nSrcRole);
    SkillCostLevel = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetSkillCostLevel(v4->cmd.nSrcRole, v4->cmd.dwItemID);
    v8 = SkillCostLevel;
    if ( SkillCostLevel )
    {
      if ( SkillCostLevel > 3 )
      {
        (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdData(v4->cmd.nSrcRole);
LABEL_11:
        (((CCBStage *)this->m_pStage->m_pRole[v4->cmd.nSrcRole]))->CCBStage::DelTask(4);
        v4->bExecuted = 1;
        goto LABEL_12;
      }
    }
    else
    {
      v8 = 1;
    }
    v9 = 2 * v8 * (((CCBAttackSequen *)this->m_pAttackSequen))->CCBAttackSequen::CalcSpeed(v4->cmd.nSrcRole, 1);
    if ( v9 > 255 )
      v9 = 255;
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdCount(v4->cmd.nSrcRole, v9);
    goto LABEL_11;
  }
LABEL_12:
  if ( (unsigned __int8)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetForce(0) )
  {
LABEL_15:
    (((CCBStage *)this->m_pStage->m_pRole[v4->cmd.nSrcRole]))->CCBStage::DelTask(2);
    this->CCBSystem::ClearEffect(this->m_nThread);
    return 0;
  }
  if ( (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::GetRoleField(v4->cmd.nSrcRole, 15) )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdData(v4->cmd.nSrcRole);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
    goto LABEL_15;
  }
  if ( (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::IsCmdReady(v4->cmd.nSrcRole) )
  {
    (((CCBStage *)this->m_pStage->m_pRole[v4->cmd.nSrcRole]))->CCBStage::DelTask(2);
    this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::IsThreadExist, 0, 0, 0, &v4->cmd);
    goto LABEL_20;
  }
  if ( !(((CCBSystem *)this->m_pAttackSequen))->CCBSystem::IsCmdEmpty(v4->cmd.nSrcRole) )
    return 0;
  m_pControl = (CCBControl *)this->m_pControl;
  if ( m_pControl->m_bActive )
  {
    if ( (((CCBControl *)m_pControl))->CCBControl::GetControl() == v4->cmd.nSrcRole )
      (((CCBControl *)this->m_pControl))->CCBControl::GetState();
  }
  (((CCBStage *)this->m_pStage->m_pRole[v4->cmd.nSrcRole]))->CCBStage::DelTask(2);
  this->CCBSystem::ClearEffect(this->m_nThread);
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
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    RoleIndex = (((CCBStage *)this->m_pStage))->CCBStage::GetRoleIndex(14, &v4->cmd, 0);
    dwItemID = v4->cmd.dwItemID;
    v7 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    p_DWORD[0] = dwItemID;
    p_DWORD[1] = v4->cmd.nSrcRole;
    p_DWORD[2] = v4->cmd.nDestRole;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    if ( v4->cmd.nSrcRole > 4u )
    {
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::ClearRoleAllTask) */, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
      *(bool (CCBStage::**)(int))&(v8) = CCBStage::IsAllSubTaskFinished;
    }
    else
    {
      (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::ClearRoleAllTask) */, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
      v8 = CCBStage::IsSubTaskFinished;
    }
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, (int)v8, 0, 0, 0, p_DWORD, 0, 0x40000000);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((int (CCBSystem::*)(int))CCBSystem::EndBattle) */, 0, 0, 0, p_DWORD, 0, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskExecSkill) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskWaitIdle) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetStageRoleByIdx(v7);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  (((CCBStage *)this->m_pStage))->CCBStage::DelTask(v4->nTaskIndex, &p_BYTE, &v11);
  if ( p_BYTE == 1 )
  {
    if ( v4->nTaskIndex != -1 )
      (((CCBStage *)this->m_pStage))->CCBStage::GetStageRole(v4->nTaskIndex);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
    this->CCBSystem::ClearEffect(this->m_nThread);
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
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::CheckVarianceRound(v4->cmd.nSrcRole, v4->cmd.dwItemID, &pnVal);
    if ( v5 == 1 )
    {
      nSrcRole = v4->cmd.nSrcRole;
      v4->cmd.dwCmdKind = 270;
      v4->cmd.dwItemID = pnVal;
      (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(nSrcRole);
      this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::AddThread, 0, 0, 0, &v4->cmd);
      this->CCBSystem::ClearEffect(this->m_nThread);
      return 0;
    }
    RoleIndex = (((CCBStage *)this->m_pStage))->CCBStage::GetRoleIndex(16, &v4->cmd, 0);
    dwItemID = v4->cmd.dwItemID;
    v9 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    p_DWORD[0] = dwItemID;
    p_DWORD[1] = v4->cmd.nSrcRole;
    p_DWORD[2] = v4->cmd.nDestRole;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::ClearRoleAllTask) */, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(unsigned int))CCBStage::ProcGrabStageRole) */, 0, 0, 0, p_DWORD, 1028443341, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskExecAttack) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskExecCommand) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v9, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetStageRoleByIdx(v9);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(v4->cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  (((CCBStage *)this->m_pStage))->CCBStage::DelTask(v4->nTaskIndex, &p_BYTE, &v13);
  if ( p_BYTE == 1 )
  {
    (((CCBStage *)this->m_pStage))->CCBStage::GetStageRole(v4->nTaskIndex);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
    this->CCBSystem::ClearEffect(this->m_nThread);
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
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 1);
    RoleIndex = (((CCBStage *)this->m_pStage))->CCBStage::GetRoleIndex(17, &v4->cmd, 0);
    dwItemID = v4->cmd.dwItemID;
    v7 = RoleIndex;
    v4->nTaskIndex = RoleIndex;
    p_DWORD[0] = dwItemID;
    p_DWORD[1] = v4->cmd.nSrcRole;
    p_DWORD[2] = v4->cmd.nDestRole;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((void (CCBStage::*)(int))CCBStage::EndRoleAllTask) */, 0, 0, 0, p_DWORD, -1082130432, 1069547520);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskExecItem) */, 0, 0, 0, p_DWORD, 0, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskForceEnd) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(v7, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetStageRoleByIdx(v7);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(v4->cmd.nSrcRole);
    v15 = 0;
    v16 = 0;
    v14 = v4->cmd.dwItemID;
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v14);
    m_pRoleState = (CCBRoleState *)this->m_pRoleState;
    v16 = SkillNum;
    v15 = 1;
    if ( (((CCBSystem *)m_pRoleState))->CCBSystem::IsMagicSlotMsg((int)&v4->cmd) )
      (((CCBSystem *)this->m_pRoleState))->CCBSystem::HandleMagicSlotInput((int)&v4->cmd);
    else
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v14);
    v4->bExecuted = 1;
  }
  (((CCBStage *)this->m_pStage))->CCBStage::DelTask(v4->nTaskIndex, &p_BYTE, &v12);
  if ( p_BYTE == 1 )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(v4->cmd.nSrcRole, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetStageRole(v4->nTaskIndex);
    this->CCBSystem::ClearEffect(this->m_nThread);
  }
  return 0;
}

// 0x00515200
int CCBSystem::PassCmdToThread(int nThreadIndex, tagCmdData *a_68)
{
  int v2; // ecx
  int v3; // esi
  int v4; // eax
  int v5; // ebp
  int SpeedBonus; // eax
  int RoleIndex; // eax
  int v9; // edx
  int v10; // edi
  unsigned int v11; // eax
  int v12; // edx
  CCBStage *v13; // ecx
  int v14; // edi
  char p_BYTE; // [esp+0x13] [ebp-0x49] BYREF
  int v16; // [esp+0x14] [ebp-0x48] BYREF
  int p_DWORD[3]; // [esp+0x18] [ebp-0x44] BYREF
  int v18[3]; // [esp+0x24] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x30] [ebp-0x2C] BYREF

  v3 = v2;
  p_BYTE = 0;
  v4 = *(_DWORD *)(v2 + 144);
  v5 = v2 + 88 * v4 + 152;
  if ( !*(_BYTE *)(v2 + 88 * v4 + 189) )
  {
    if ( !(((CCBSystem *)*(CCBSystem **)(v2 + 12)))->CCBSystem::IsBusy(*(_DWORD *)(v2 + 88 * v4 + 200))
      && !*(_BYTE *)(*(_DWORD *)(v3 + 16) + 549) )
    {
      (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::SetCmdParam(*(_DWORD *)(v5 + 48), 0);
LABEL_5:
      (((CCBSystem *)v3))->CCBSystem::ClearEffect(*(_DWORD *)(v3 + 144));
      return 0;
    }
    (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::ClearCmdSlot(*(_DWORD *)(v5 + 48));
    SpeedBonus = (((CCBRoleState *)*(CCBRoleState **)(v3 + 16)))->CCBRoleState::GetSpeedBonus(*(_DWORD *)(v5 + 48));
    LOBYTE(SpeedBonus) = 8 * SpeedBonus + 20;
    (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::GetCmdCount(*(_DWORD *)(v5 + 48), SpeedBonus);
    if ( *(_BYTE *)(*(_DWORD *)(v3 + 16) + 549) )
      (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::GetCmdData(*(_DWORD *)(v5 + 48));
    (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::SetCmdParam(*(_DWORD *)(v5 + 48), 0);
    *(_BYTE *)(v5 + 37) = 1;
    RoleIndex = (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleIndex(20, (const void *)(v5 + 40), 0);
    v9 = *(_DWORD *)(v5 + 44);
    v10 = RoleIndex;
    *(_DWORD *)(v5 + 20) = RoleIndex;
    p_DWORD[0] = v9;
    p_DWORD[1] = *(_DWORD *)(v5 + 48);
    p_DWORD[2] = *(_DWORD *)(v5 + 52);
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleName(v10, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskExecAction) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleName(v10, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetStageRoleByIdx(v10);
    (((CCBRoleState *)*(CCBRoleState **)(v3 + 16)))->CCBRoleState::InitUI(*(_DWORD *)(v5 + 48))->bWaitForFlee = 1;
  }
  if ( (unsigned __int8)(((CCBRoleState *)*(CCBRoleState **)(v3 + 16)))->CCBRoleState::GetForce(0)
    && ((((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::DelTask(*(_DWORD *)(v5 + 20), &p_BYTE, &v16), p_BYTE) )
  {
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetStageRole(*(_DWORD *)(v5 + 20));
    (((CCBRoleState *)*(CCBRoleState **)(v3 + 16)))->CCBRoleState::InitUI(*(_DWORD *)(v5 + 48))->bWaitForFlee = 0;
    (((CCBSystem *)v3))->CCBSystem::ClearEffect(*(_DWORD *)(v3 + 144));
    return 0;
  }
  else
  {
    if ( (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::IsCmdReady(*(_DWORD *)(v5 + 48)) || *(_BYTE *)(*(_DWORD *)(v3 + 16) + 549) )
    {
      (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::DelTask(*(_DWORD *)(v5 + 20), &p_BYTE, &v16);
      if ( p_BYTE )
      {
        (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetStageRole(*(_DWORD *)(v5 + 20));
        (((CCBSystem *)v3))->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::PassCmdToTask, 0, 0, 0, (const void *)(v5 + 40));
        goto LABEL_5;
      }
    }
    if ( (((CCBRoleState *)*(CCBRoleState **)(v3 + 16)))->CCBRoleState::GetRoleField(*(_DWORD *)(v5 + 48), 16)
      && !*(_BYTE *)(*(_DWORD *)(v3 + 16) + 549) )
    {
      (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::GetCmdData(*(_DWORD *)(v5 + 48));
      (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::SetCmdParam(*(_DWORD *)(v5 + 48), 0);
    }
    if ( !(((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::IsCmdEmpty(*(_DWORD *)(v5 + 48)) )
      return 0;
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::DelTask(*(_DWORD *)(v5 + 20), &p_BYTE, &v16);
    if ( !p_BYTE )
      return 0;
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetStageRole(*(_DWORD *)(v5 + 20));
    (((CCBRoleState *)*(CCBRoleState **)(v3 + 16)))->CCBRoleState::InitUI(*(_DWORD *)(v5 + 48))->bWaitForFlee = 0;
    memset(pData, 0, sizeof(pData));
    LOBYTE(pData[10]) = 1;
    pData[0] = 267;
    v11 = (((CCBSystem *)v3))->CCBSystem::ProcProtect();
    v12 = *(_DWORD *)(v5 + 48);
    v13 = (CCBStage *)*(CCBStage **)(v3 + 20);
    pData[1] = v11;
    pData[2] = v12;
    pData[3] = -1;
    v14 = (((CCBStage *)v13))->CCBStage::GetRoleIndex(26, pData, 1);
    if ( v14 != -1 )
    {
      memset(v18, 0, sizeof(v18));
      (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleName(v14, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::ProcessRoleEffect) */, 0, 0, 0, v18, 0, 1077936128);
      (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetStageRoleByIdx(v14);
    }
    (((CCBSystem *)v3))->CCBSystem::ClearEffect(*(_DWORD *)(v3 + 144));
    return -1;
  }
}

// 0x005155D0
bool CCBSystem::PassCmdToTask(int nTaskIndex, int nThreadIndex)
{
  int v2; // ecx
  int v3; // edi
  int v4; // eax
  int v5; // esi
  int RoleIndex; // eax
  int v7; // edx
  int v8; // ebp
  C2DSpark *v9; // ecx
  char p_BYTE; // [esp+0x13] [ebp-0x11] BYREF
  int v12; // [esp+0x14] [ebp-0x10] BYREF
  int p_DWORD[3]; // [esp+0x18] [ebp-0xC] BYREF

  v3 = v2;
  p_BYTE = 0;
  v12 = 0;
  v4 = *(_DWORD *)(v2 + 144);
  v5 = v2 + 88 * v4 + 152;
  if ( !*(_BYTE *)(v2 + 88 * v4 + 189) )
  {
    (((CCBSystem *)*(CCBSystem **)(v2 + 12)))->CCBSystem::SetCmdParam(*(_DWORD *)(v2 + 88 * v4 + 200), 1);
    RoleIndex = (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleIndex(20, (const void *)(v5 + 40), 0);
    v7 = *(_DWORD *)(v5 + 44);
    v8 = RoleIndex;
    *(_DWORD *)(v5 + 20) = RoleIndex;
    p_DWORD[0] = v7;
    p_DWORD[1] = *(_DWORD *)(v5 + 48);
    p_DWORD[2] = *(_DWORD *)(v5 + 52);
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleName(v8, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskResolveAction) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetRoleName(v8, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetStageRoleByIdx(v8);
    *(_BYTE *)(v5 + 37) = 1;
  }
  (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::DelTask(*(_DWORD *)(v5 + 20), &p_BYTE, &v12);
  if ( p_BYTE == 1 )
  {
    (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::GetCmdPtr(*(_DWORD *)(v5 + 48));
    (((CCBStage *)*(CCBStage **)(v3 + 20)))->CCBStage::GetStageRole(*(_DWORD *)(v5 + 20));
    if ( v12 )
    {
      v9 = (C2DSpark *)*(C2DSpark **)(v3 + 52);
      *(_DWORD *)(v3 + 120) = 4;
      (((C2DSpark *)v9))->C2DSpark::CreateStars();
    }
    else
    {
      (((CCBSystem *)*(CCBSystem **)(v3 + 12)))->CCBSystem::SetCmdParam(*(_DWORD *)(v5 + 48), 0);
    }
    (((CCBSystem *)v3))->CCBSystem::ClearEffect(*(_DWORD *)(v3 + 144));
  }
  return 0;
}

// 0x00515760
bool CCBSystem::PassCmdViaThread(int nDestThread, int nSrcThread)
{
  int m_nThread; // eax
  tagThread *v5; // esi
  int RoleIndex; // ebx
  int nSrcRole; // ecx
  int p_DWORD[3]; // [esp+0x10] [ebp-0xC] BYREF

  m_nThread = this->m_nThread;
  v5 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::SetCmdParam(this->m_Thread[m_nThread].cmd.nSrcRole, 0);
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(v5->cmd.nSrcRole);
    RoleIndex = (((CCBStage *)this->m_pStage))->CCBStage::GetRoleIndex(19, &v5->cmd, 1);
    p_DWORD[2] = v5->cmd.nDestRole;
    v5->nTaskIndex = RoleIndex;
    nSrcRole = v5->cmd.nSrcRole;
    p_DWORD[0] = v5->cmd.dwItemID;
    p_DWORD[1] = nSrcRole;
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeIn) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((int (CCBStage::*)(int))CCBStage::TaskEnterGuard) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    (((CCBStage *)this->m_pStage))->CCBStage::GetRoleName(RoleIndex, 0 /* TODO: pmf_to_u32((unsigned int (CCBStage::*)(int))CCBStage::ProcFiveLienupFadeOut) */, 0, 0, 0, p_DWORD, -1082130432, 0);
    v5->nTemp = (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v5->cmd.nSrcRole)[1].dwMagicID[2][3];
    (((CCBStage *)this->m_pStage))->CCBStage::GetStageRoleByIdx(RoleIndex);
    v5->bExecuted = 1;
  }
  if ( (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::IsBusy(v5->cmd.nSrcRole)
    || *(_DWORD *)&this->m_eState != 2
    || (int)(((CCBRoleState *)this->m_pRoleState))->CCBRoleState::InitUI(v5->cmd.nSrcRole)[1].dwMagicID[2][3] > v5->nTemp )
  {
    (((CCBRoleState *)this->m_pRoleState))->CCBRoleState::SetRoleFlag(v5->cmd.nSrcRole, 0);
    this->CCBSystem::ClearEffect(this->m_nThread);
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
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( !this->m_Thread[m_nThread].bExecuted )
  {
    (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::GetCmdPtr(this->m_Thread[m_nThread].cmd.nSrcRole);
    v4->bExecuted = 1;
  }
  this->CCBSystem::ClearEffect(this->m_nThread);
  return 0;
}

// 0x00515940
int CCBSystem::CreateThreadObj(int nVal)
{
  int m_nThread; // eax
  tagThread *v4; // edi
  BOOL UIObj; // edi

  m_nThread = this->m_nThread;
  v4 = (tagThread *)&this->m_Thread[m_nThread];
  if ( this->m_Thread[m_nThread].bExecuted )
  {
    UIObj = this->CCBSystem::CreateUIObj(0, 0, 0x40u);
    this->CCBSystem::ClearEffect(this->m_nThread);
    return UIObj;
  }
  else
  {
    this->CCBSystem::ProcAI(0.0);
    v4->bExecuted = 1;
    return 0;
  }
}

// 0x005159A0
BOOL CCBSystem::CreateUIObj(CCBUI **ppUI, const char *szName, UINT nFlags)
{
  unsigned int v5; // eax
  CHAR *v6; // edi
  char *v7; // esi
  char v8; // cl
  unsigned int v9; // edx

  if ( !ppUI )
    return MessageBoxA((HWND)g_todo_BFDA4C, byte_17AC6DC, (LPCSTR)&g_bCBFlag, uType);
  if ( strlen((const char *)ppUI) >= 0xFF )
  {
    v9 = strlen(aTooManyCharact) + 1;
    qmemcpy(byte_17AC6DC, aTooManyCharact, 4 * (v9 >> 2));
    v7 = (char *)&aTooManyCharact[4 * (v9 >> 2)];
    v6 = (CHAR *)&byte_17AC6DC[4 * (v9 >> 2)];
    v8 = v9;
  }
  else
  {
    v5 = strlen((const char *)ppUI) + 1;
    qmemcpy(byte_17AC6DC, ppUI, 4 * (v5 >> 2));
    v7 = (char *)&ppUI[v5 >> 2];
    v6 = (CHAR *)&byte_17AC6DC[4 * (v5 >> 2)];
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
    sprintf((char *const)&g_bCBFlag, aS_2_0, "PAL3 COMBAT SYSTEM 1.03");
  }
  uType = nFlags;
  this->CCBSystem::CreateProtectedObj((int (CCBSystem::*)(int))&CCBSystem::CreateThreadObj, 0, 0, 0, 0);
  return 0;
}

// 0x00515AC0
char CCBSystem::CreateRoleStateObj(CCBRoleState **a2)
{
  int v2; // edx
  tagThread *i; // eax

  v2 = 0;
  for ( i = this->m_Thread;
        !i->bValid
     || (int (*)(int, tagCmdData *))i->fp[0] != CCBSystem::PassCmdToThread
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
int CCBSystem::CreateProtectedObj(
        
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
    MessageBoxA(0, (const char *)&unk_5DE9E4, 0, 0x30u);
  if ( a2 == &CCBSystem::CheckBattleEnd
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
  *((_DWORD *)v10 + 42) = this->CCBSystem::ProcProtect();
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
bool CCBSystem::CreateEditorObj(CCBEditor **a2)
{
  CCBStage *v3; // eax
  int *v4; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x408] [ebp-0x40C] BYREF
  int v8; // [esp+0x810] [ebp-0x4]

  v3 = (CCBStage *)operator new(0x2598u);
  v8 = 0;
  if ( v3 )
    v4 = (((CCBStage *)v3))->CCBStage::ResetAndSetSystem((int)this);
  else
    v4 = 0;
  v8 = -1;
  *a2 = (CCBEditor *)v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_6, 2504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return (((CCBStage *)v4))->CCBStage::SyncTimeScale() != 0;
}

// 0x00515DD0
void * CCBSystem::_scalar_deleting_destructor_(CCBSystem *Block, char pData)
{
  void *v5; // [esp+0x0] [ebp-0x4]

  NullCallback(v5);
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00515DF0
void * CCBSystem::DestroyObj_5df0(CCBSystem *Block, char pData)
{
  (((CCBStage *)this))->CCBStage::ClearAll() /* [ROWTABLE] */;
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00515E50
BOOL CCBSystem::DestroyObj()
{
  BOOL result; // eax

  result = 1094713344;
  g_nCBCamState[0] = 1094713344;
  return result;
}

// 0x00515E70
void CCBSystem::DestroyObj_5e70()
{
  g_fCBCamParam = 12.0 + 12.0;
}

// 0x00515E90
bool CCBSystem::InitObj()
{
  bool result; // al

  g_nCBCamState[2] = g_nStatePanelL_dup[0] + 119;
  result = LOBYTE(g_nStatePanelL_dup[3]) + 107;
  g_nCBCamState[3] = g_nStatePanelL_dup[1] + 107;
  g_nCBCamState[4] = g_nStatePanelL_dup[2] + 107;
  g_nCBCamState[5] = g_nStatePanelL_dup[3] + 107;
  return result;
}

// 0x00515EE0
int CCBSystem::InitObj_5ee0()
{
  int result; // eax

  g_nCBCamState[6] = g_nStatePanelT_dup[0] + 28;
  result = g_nStatePanelT_dup[3] + 28;
  g_nCBCamState[7] = g_nStatePanelT_dup[1] + 28;
  g_nCBCamState[8] = g_nStatePanelT_dup[2] + 28;
  g_nCBCamState[9] = g_nStatePanelT_dup[3] + 28;
  return result;
}

// 0x00515F30
int CCBSystem::InitObj_5f30()
{
  int result; // eax

  g_nCBCamState[10] = g_nStatePanelL_dup[0] + 128;
  result = g_nStatePanelL_dup[3] + 116;
  g_nCBCamState[11] = g_nStatePanelL_dup[1] + 116;
  g_nCBCamState[12] = g_nStatePanelL_dup[2] + 116;
  g_nCBCamState[13] = g_nStatePanelL_dup[3] + 116;
  return result;
}

// 0x00515F80
int CCBSystem::InitObj_5f80()
{
  int result; // eax

  g_nCBCamState[14] = g_nStatePanelT_dup[0] + 54;
  result = g_nStatePanelT_dup[3] + 54;
  g_nCBCamState[15] = g_nStatePanelT_dup[1] + 54;
  g_nCBCamState[16] = g_nStatePanelT_dup[2] + 54;
  g_nCBCamState[17] = g_nStatePanelT_dup[3] + 54;
  return result;
}

// 0x00515FD0
int CCBSystem::InitObj_5fd0()
{
  int result; // eax

  g_nCBCamState[18] = g_nStatePanelL_dup[0] + 121;
  result = g_nStatePanelL_dup[3] + 109;
  g_nCBCamState[19] = g_nStatePanelL_dup[1] + 109;
  g_nCBCamState[20] = g_nStatePanelL_dup[2] + 109;
  g_nCBCamState[21] = g_nStatePanelL_dup[3] + 109;
  return result;
}
