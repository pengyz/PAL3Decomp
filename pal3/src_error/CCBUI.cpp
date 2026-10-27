#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBUI.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Role/Actor.h"
#include "Misc/ArcLocaleRole.h"
#include "Combat/CCBAI.h"
#include "Combat/CCBAIWindow.h"
#include "Combat/CCBAttackSequen.h"
#include "Combat/CCBCamControl.h"
#include "Combat/CCBControl.h"
#include "Combat/CCBControlWindow.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBItemWindow.h"
#include "Combat/CCBLineupWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBParabolaWindow.h"
#include "Combat/CCBProtectWindow.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBSkillWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBStageEffect.h"
#include "Combat/CCBStageRole.h"
#include "Combat/CCBStageScene.h"
#include "Combat/CCBSystem.h"
#include "Misc/CCBUI_funcptr_t.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffSParticle.h"
#include "Effect/CEffect.h"
#include "Effect/CEffectSystem.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Scene/Camera.h"
#include "Combat/Combat.h"
#include "GameBase/GRPinput.h"
#include "GameBase/Logger.h"
#include "Misc/MUIDialog.h"
#include "Role/NPC.h"
#include "Misc/NameSys.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PlayerMgr.h"
#include "UI/PropUI.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Misc/SaleUI.h"
#include "Scene/SceneObj.h"
#include "Misc/UIButton.h"
#include "Misc/UICaption.h"
#include "Misc/UICoverFrm.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "UI/UINote.h"
#include "Misc/UIParticle.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UIStatic.h"
#include "Misc/UIStaticCB.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/tag17A7BData.h"
#include "Misc/tagEffMgrData.h"
#include "Misc/tagRoleState.h"
#include "Misc/tagUITask.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4CE030(...);
int sub_4CE5C0(...);
int sub_511630(...);
int sub_516170(...);
int sub_51A400(...);

// Unnamed globals (extern)
extern char aUiCombatContro_8[];
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DCF43C[256];

// 0x0043D7A0
int CCBUI::ForwardOnMessage(int nVal, int nMsg, int wParam)
{
  return this->UIWnd::OnMessage(nVal, nMsg, wParam);
}

// 0x00441040
void CCBUI::SetTooltip(const char *szText)
{
  if ( szText )
    strncpy((char *)&this->m_pAttackSequenFace[4], szText, 0x7Fu);
  else
    memset(&this->m_pAttackSequenFace[4], 0, 0x80u);
}

// 0x00441070
void CCBUI::SetRect(RECT *pRect)
{
  this->m_pAttackSequenBack = ((UIStatic *)((UIStatic *)pRect->left));
}

// 0x00441380
int CCBUI::ShowEffect(int nY, int nWidth, int nHeight)
{
  _DWORD a2[4]; // [esp+0x0] [ebp-0x10] BYREF
  int v6; // [esp+0x20] [ebp+0x10]

  a2[1] = nY;
  a2[2] = nHeight;
  a2[0] = nWidth;
  a2[3] = v6;
  return (((UIWnd *)&this->m_pAttackSequenBack))->UIWnd::sub_445FA0(a2);
}

// 0x004420B0
int CCBUI::VirtualCall(int nVal1)
{
  return ((int ( *)(UIStatic **, int))((UIWnd *)this->m_pAttackSequenBack))(&this->m_pAttackSequenBack, nVal1);
}

// 0x00442170
void CCBUI::SetTargetPos(gbVec3D *pPos, gbVec3D *pDir)
{
  float y; // ebx
  UIStatic *v4; // eax
  LONG left; // edx

  *(gbVec3D *)&this->m_pRoleStateDefenceInc[3] = *pPos;
  this->m_pRoleStateDefenceInc[6] = (UIStatic *)LODWORD(pPos[1].x);
  *(gbVec3D *)&this->m_pRoleStateDefenceInc[7] = *pDir;
  this->m_pRoleStateDefenceInc[10] = (UIStatic *)LODWORD(pDir[1].x);
  y = pDir->y;
  v4 = (UIStatic *)(LODWORD(pPos[1].x) - LODWORD(pPos->y));
  if ( (int)v4 <= LODWORD(pDir[1].x) - LODWORD(y) )
    v4 = (UIStatic *)(LODWORD(pDir[1].x) - LODWORD(y));
  left = this->m_rect.left;
  this->m_pRoleStatePanel[2] = v4;
  this->m_pRoleStateDefenceDec[0] = (UIStatic *)(LODWORD(pPos->x) - left);
}

// 0x004421F0
void CCBUI::SetCurPlayer(int nPlayer)
{
  this->m_pRoleStateDefenceDec[0] = (UIStatic *)nPlayer;
}

// 0x00442200
int CCBUI::SetRoleStatePointers(int nVal)
{
  int v2; // edx
  int result; // eax

  v2 = this->m_rect.top - (int)this->m_pRoleStateDefenceDec[3] / 2;
  this->m_pRoleStateDefenceDec[1] = (UIStatic *)nVal;
  result = v2 + nVal;
  this->m_pRoleStateFace[4] = (UIStatic *)(v2 + nVal);
  this->m_pRoleStateFace[3] = (UIStatic *)(v2 + nVal);
  return result;
}

// 0x00442230
int CCBUI::SetSelection(int nItemIndex)
{
  UIStatic *v2; // edx
  UIStatic *v3; // esi
  int result; // eax
  UIStatic *v5; // [esp+0xC] [ebp+0x8]

  v2 = (UIStatic *)this->m_pRoleStateDefenceInc[6];
  v3 = (UIStatic *)this->m_pRoleStateDefenceDec[1];
  this->m_pRoleStateDefenceDec[2] = (UIStatic *)nItemIndex;
  this->m_pRoleStateDefenceDec[3] = v5;
  result = (int)v3 + (_DWORD)v2 + (int)v5 / 2;
  this->m_pRoleStateFace[4] = (UIStatic *)result;
  this->m_pRoleStateFace[3] = (UIStatic *)result;
  return result;
}

// 0x00459F30
__int16 CCBUI::ForwardToPlayerMgr(_WORD *p_WORD)
{
  __int16 result; // ax

  (((SaleUI *)this[1].m_pRoleStateBlank[3]))->SaleUI::LoadState(p_WORD);
  (((PropUI *)this[1].m_pRoleStateBlank[4]))->PropUI::UpdateItemList(p_WORD);
  qmemcpy(&this[1].m_pRoleStateBlank[5][3].m_mouseoff, p_WORD, 0x4460u);
  result = p_WORD[1];
  LOWORD(this->m_pRoleStatePanel[3]) = result;
  return result;
}

// 0x00460A00
bool CCBUI::RollProbability(float fProb)
{
  int fProba; // [esp+0xC] [ebp+0x8]
  float fProbb; // [esp+0xC] [ebp+0x8]

  fProba = (__int64)(fProb * 100.0);
  if ( fProba <= 0 )
    return 0;
  fProbb = (float)fProba * 10.239999771118164f;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
  return (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)fProbb;
}

// 0x00469D00
int CCBUI::SetItemData(int nCol, int nRow, int nData, int nFlags)
{
  gbColorQuad *p_m_fontcolor; // eax
  LONG *p_top; // ecx
  unsigned int Color; // edx
  int result; // eax

  this->m_wndcolor.Color = nRow;
  p_m_fontcolor = (gbColorQuad *)&this->m_fontcolor;
  p_top = (LONG *)&this->m_rect.top;
  p_m_fontcolor->Color = nCol;
  *(p_top - 2) = nData;
  *(p_top - 1) = nFlags;
  *p_top = p_m_fontcolor->Color;
  p_top[1] = p_m_fontcolor[1].Color;
  Color = p_m_fontcolor[2].Color;
  result = p_m_fontcolor[3].Color;
  p_top[2] = Color;
  p_top[3] = result;
  return result;
}

// 0x00469D40
unsigned __int8 CCBUI::IsAddMode()
{
  return (unsigned __int8)this[1].m_pRoleStateBlank[9];
}

// 0x004AA9C0
void CCBUI::CreatePanelUI()
{
  int v2; // eax
  UIStatic *v3; // eax
  int v4; // esi
  UIStatic **v5; // edi
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // esi
  int v9; // edi
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // edx
  CScreenMode *Instance; // eax
  const void *v19; // [esp-0x10] [ebp-0x1E4]
  const CHAR *v20; // [esp-0x4] [ebp-0x1D8]
  CHAR v21[128]; // [esp+0x4] [ebp-0x1D0] BYREF
  char Buffer[253]; // [esp+0x84] [ebp-0x150] BYREF
  __int16 v23; // [esp+0x181] [ebp-0x53]
  char v24; // [esp+0x183] [ebp-0x51]
  CHAR String1[64]; // [esp+0x184] [ebp-0x50] BYREF
  float v26; // [esp+0x1C4] [ebp-0x10]
  unsigned int a2; // [esp+0x1C8] [ebp-0xC]
  int v28; // [esp+0x1CC] [ebp-0x8]
  float v29; // [esp+0x1D0] [ebp-0x4]

  if ( SLODWORD(this[8].m_Task[14].param.fEndX) > 0 )
  {
    switch ( g_nFiveNimbusCount )
    {
      case 0:
        lstrcpyA(String1, (LPCSTR)g_bSlotFlag);
        break;
      case 1:
        v20 = (const CHAR *)&g_bSlotFlag[256];
        goto LABEL_8;
      case 2:
        lstrcpyA(String1, byte_DC3F3C);
        break;
      case 3:
        lstrcpyA(String1, (LPCSTR)&g_bSlotFlag[512]);
        break;
      case 4:
        v20 = byte_DC403C;
LABEL_8:
        lstrcpyA(String1, v20);
        break;
      default:
        break;
    }
    v2 = dword_C10CC4;
    if ( dword_C10CC4 < 0 )
      v2 = 0;
    dword_C10CC4 = v2 + 1;
    if ( v2 + 1 >= 9 )
      dword_C10CC4 = 9;
    memset(this->m_pAttackSequenFace, 0, 0x100u);
    if ( *((_BYTE *)&g_nRoleParam + g_nFiveNimbusCount) || *((_BYTE *)&g_nRoleState + g_nFiveNimbusCount + 1) )
      *((_BYTE *)&g_nActorState + g_nFiveNimbusCount) = 1;
    lstrcpyA(v21, byte_DCF43C);
    v3 = (UIStatic *)this[8].m_pRoleStateForbid[0];
    v4 = 0;
    if ( (int)v3 > 0 )
    {
      v5 = (UIStatic **)&this->m_pRoleStateStable[1];
      v6 = (unsigned __int8)g_nActorState;
      a2 = (unsigned __int8)g_nActorState;
      while ( *(_QWORD *)(v5 - 1) != __PAIR64__(BYTE1(g_nActorState), v6)
           || *(_QWORD *)(v5 + 1) != __PAIR64__(BYTE2(g_nActorState), HIBYTE(g_nActorState))
           || v5[3] != (UIStatic *)(unsigned __int8)g_nActor_DE5F9C )
      {
        ++v4;
        v5 += 190;
        if ( v4 >= (int)v3 )
          goto LABEL_25;
        v6 = a2;
      }
      lstrcpyA(v21, (LPCSTR)&this->m_pRoleStateStable[190 * v4 + 5]);
    }
LABEL_25:
    v7 = (int)this->m_pRoleStateSpeedDec[3];
    v8 = 0;
    v9 = 0;
    a2 = 0;
    v26 = 0.0f;
    if ( v7 > 0 )
    {
      v10 = (int)this->m_pRoleStateSpeedDec[2];
      if ( v10 > 0 )
        a2 = v7 / v10;
    }
    v11 = (int)this->m_pRoleStateSpeedDec[4];
    if ( v11 > 0 )
    {
      v12 = (int)this->m_pRoleStateSpeedDec[7];
      if ( v12 > 0 )
        v9 = v11 / v12;
    }
    v13 = (int)this->m_pRoleStateSpeedDec[6];
    if ( v13 > 0 )
    {
      v28 = (int)this->m_pRoleStateSpeedDec[8];
      if ( v28 > 0 )
        v26 = ((float)v28 * 0.009999999776482582f + 0.8999999761581421f) * (float)(v13 / v28) * 0.20000000298023224f;
    }
    v14 = (int)this->m_pRoleStateSpeedDec[5];
    if ( v14 > 0 )
    {
      v15 = (int)this->m_pRoleStateSpeedDec[7];
      if ( v15 > 0 )
        v8 = v14 / v15;
    }
    v16 = (int)this->m_pRoleStateSpeedDec[1];
    v28 = (int)this->m_pRoleStateSpeedDec[2] / 2;
    v17 = *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[15] + v16 / 5 - v28;
    v28 = v17;
    if ( v17 > 0 )
    {
      if ( v17 > 20 )
        v28 = 20;
    }
    else
    {
      v28 = 1;
    }
    v29 = ((float)dword_C10CC4 * 0.019999999552965164f + 1.0f) * (float)(int)(a2 + v9 + v8 + (int)v26);
    a2 = (int)v29;
    v29 = _pal3_coerce_f32(ClampToRange(a2, dword_C10CC4));
    memset(Buffer, 0, sizeof(Buffer));
    v23 = 0;
    v24 = 0;
    LOBYTE(this->m_pAttackSequenFace[0]) = 0;
    sprintf(Buffer, "      %s   %s", (const char *)&dword_DC933C, String1);
    while ( lstrlenA((const char *)Buffer) < 22 )
      lstrcatA((char *)Buffer, " ");
    lstrcatA((LPSTR)this->m_pAttackSequenFace, Buffer);
    sprintf(Buffer, "%s %d", (const char *)&dword_DCE93C, v28);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, Buffer);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, aN);
    sprintf(Buffer, "      %s     %d", (const char *)&dword_DCFE3C, v29);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, Buffer);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, aN);
    sprintf(Buffer, "      %s %s", (const char *)&dword_DC923C, v21);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, Buffer);
    SetEnable((UICaption *)&this[151].m_Task[11].param.fSpeed);
    (((UIRoleSelect *)&this[151].m_Task[5].fExpectEndTime))->UIRoleSelect::SetByte(1);
    v19 = (const void *)off_5CF1F0;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v19, 1);
  }
}

// 0x004AB2B0
void CCBUI::DestroyDynamic(int nVal)
{
  UIListBox *p_fEndX; // ebx
  int v4; // ebp
  int *v5; // edi
  int v6; // eax
  int v7; // esi
  int *v8; // ebp
  int *v9; // edi
  int *v10; // esi
  int v11; // edx
  int v12; // eax
  int v13; // ebp
  int ListItems; // eax
  char *m_pAttackSequenFace; // esi
  int v16; // edi
  char *v17; // [esp+0x10] [ebp-0x44]
  int v18; // [esp+0x14] [ebp-0x40] BYREF
  int *v19; // [esp+0x18] [ebp-0x3C]
  CCBUI *v20; // [esp+0x1C] [ebp-0x38]
  int v21; // [esp+0x20] [ebp-0x34]
  int v22; // [esp+0x24] [ebp-0x30]
  int SkillNum; // [esp+0x28] [ebp-0x2C]
  int v24; // [esp+0x2C] [ebp-0x28] BYREF
  int v25; // [esp+0x30] [ebp-0x24]
  int i; // [esp+0x34] [ebp-0x20]
  char v27; // [esp+0x38] [ebp-0x1C]
  void *Block; // [esp+0x3C] [ebp-0x18]
  int *p_DWORD2; // [esp+0x40] [ebp-0x14]
  int v30; // [esp+0x44] [ebp-0x10]
  int v31; // [esp+0x50] [ebp-0x4]
  unsigned int nVala; // [esp+0x58] [ebp+0x4]
v27 = nVal;
  Block = 0;
  p_DWORD2 = 0;
  v30 = 0;
  p_fEndX = (UIListBox *)&this[149].m_Task[3].param.fEndX;
  v31 = 0;
  v21 = 0xFFFF;
  v22 = 0;
  SkillNum = 0;
  v4 = 0;
  if ( (((UIListBox *)&this[149].m_Task[3].param.fEndX))->UIListBox::GetItemData() > 0 )
  {
    v5 = (int *)&this[8].m_pRoleStateForbid[8];
    do
    {
      v6 = (unsigned long)*v5;
      v22 = (unsigned long)v5[1];
      v21 = v6;
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v6);
      RoleSystem::CheckVisible();
      ++v4;
      v5 += 4;
    }
    while ( v4 < (((UIListBox *)p_fEndX))->UIListBox::GetItemData() );
  }
  v19 = (int *)p_DWORD2;
  if ( ((char *)p_DWORD2 - (_BYTE *)Block) / 12 > 16 )
  {
    v7 = nVal;
    ArcLocaleRole::ParseLocaleData((char *)Block, (char *)p_DWORD2, nVal);
    v8 = (int *)((char *)Block + 192);
    SortTripletsByField((int *)Block, (int *)Block + 48, nVal);
    if ( (char *)Block + 192 != (char *)v19 )
    {
      v9 = (int *)((char *)Block + 180);
      v17 = (char *)Block + 180;
      while ( 1 )
      {
        v18 = v7;
        v10 = (int *)v8;
        v24 = (unsigned long)*v8;
        v25 = (unsigned long)v8[1];
        for ( i = v8[2]; sub_4AB560(&v18, (int)&v24, (int)v9); v9 -= 3 )
        {
          *v10 = *v9;
          v10[1] = (unsigned long)v9[1];
          v10[2] = (unsigned long)v9[2];
          v10 = (int *)v9;
        }
        v11 = v25;
        v12 = i;
        *v10 = v24;
        v10[1] = v11;
        v10[2] = v12;
        v8 += 3;
        v17 += 12;
        if ( v8 == v19 )
          break;
        v9 = (int *)v17;
        v7 = nVal;
      }
    }
  }
  else
  {
    SortTripletsByField((int *)Block, p_DWORD2, nVal);
  }
  (((UIListBox *)p_fEndX))->UIListBox::ClearAll();
  nVala = 0;
  v13 = 0;
  while ( Block && nVala < ((char *)p_DWORD2 - (_BYTE *)Block) / 12 )
  {
    v21 = *(_DWORD *)((char *)Block + v13);
    v22 = *(_DWORD *)((char *)Block + v13 + 4);
    SkillNum = *(_DWORD *)((char *)Block + v13 + 8);
    ListItems = (((UIListBox *)p_fEndX))->UIListBox::LoadListItems((char *)(SkillNum + 4), 0);
    m_pAttackSequenFace = (char *)this->m_pAttackSequenFace;
    v16 = ListItems;
    sprintf((char *const)this->m_pAttackSequenFace, (const char *)&dir[20], v22);
    (((UIListBox *)p_fEndX))->UIListBox::SetMouseMoveSel(1, v16, m_pAttackSequenFace, 0);
    sprintf(m_pAttackSequenFace, (const char *)&dir[20], *(_DWORD *)(SkillNum + 624));
    (((UIListBox *)p_fEndX))->UIListBox::SetMouseMoveSel(2, v16, m_pAttackSequenFace, 0);
    sprintf(m_pAttackSequenFace, (const char *)&dir[20], *(_DWORD *)(SkillNum + 608) / 2);
    (((UIListBox *)p_fEndX))->UIListBox::SetMouseMoveSel(3, v16, m_pAttackSequenFace, 0);
    v13 += 12;
    ++nVala;
  }
  operator delete(Block);
}

// 0x004DC220
char CCBUI::IsActive()
{
  (((CCBSystem *)this))->CCBSystem::ClearAllPointers();
  (((CCBRoleState *)this))->CCBRoleState::UpdatePanel(0);
  return 1;
}

// 0x004E04C0
int CCBUI::StepFrame()
{
  int result; // eax

  (((CCBSystem *)*(CCBSystem **)((UIWnd *)this)))->CCBSystem::ProcAI(formal);
  if ( *(_BYTE *)(*(_DWORD *)((UIWnd *)this) + 132) != (unsigned long)byte_17A9924 )
    (((CCBSystem *)*(CCBSystem **)((UIWnd *)this)))->CCBSystem::SetRenderFlag(byte_17A9924);
  *(_BYTE *)(*(_DWORD *)((UIWnd *)this) + 134) = (unsigned long)byte_5D87F0;
  if ( (_BYTE)g_bWPARAM_17A9926 )
  {
    (((CCBSystem *)*(CCBSystem **)((UIWnd *)this)))->CCBSystem::GetRenderFlag(1);
    LOBYTE(g_bWPARAM_17A9926) = 0;
  }
  this->CCBUI::ResetAllSlots();
  this->CCBUI::UpdateDisplay();
  this->CCBUI::UpdateAnimation();
  return this->CCBUI::UpdateState();
}

// 0x004E0690
char CCBUI::ResetAllSlots()
{
  char result; // al
  int FullConfig; // eax
  char Buffer[128]; // [esp+0x8] [ebp-0x80] BYREF

  result = byte_17A9930;
  if ( byte_17A9930 )
  {
    CCBStageScene_Update();
    (((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + 20)))->CCBStageScene::ShowRoleIndex();
    result = (((CCBSystem *)*(CCBSystem **)((UIWnd *)this)))->CCBSystem::CreateUIObj(&ppUI, 0, 0x40u);
    byte_17A9930 = 0;
  }
  if ( byte_17A9932 )
    byte_17A9932 = 0;
  if ( byte_17A9931 )
    byte_17A9931 = 0;
  if ( byte_17A9933 )
  {
    FullConfig = (((CCBStage *)*(CCBStage **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + 12)))->CCBStage::LoadFullConfig();
    sprintf(Buffer, (const char *)&unk_5D8848, FullConfig);
    result = (((CCBSystem *)*(CCBSystem **)((UIWnd *)this)))->CCBSystem::CreateUIObj((CCBUI **)Buffer, 0, 0x40u);
    byte_17A9933 = 0;
  }
  return result;
}

// 0x004E0740
char CCBUI::UpdateDisplay()
{
  _BYTE *inited; // eax
  int v3; // edi
  int i; // esi
  CCBRoleState *v5; // ecx
  int v6; // edi
  int v7; // esi
  CCBRoleState *v8; // ecx
  HWND DlgItem; // eax

  LOBYTE(inited) = (unsigned long)byte_17A9925;
  if ( byte_17A9925 )
  {
    v3 = 0;
    for ( i = 0; i < 4460; i += 892 )
    {
      inited = (_BYTE *)((UIWnd *)this);
      v5 = (CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)((UIWnd *)this) + 16);
      if ( v5->m_pObjMsgBuffer[i + 153] )
      {
        inited = (((CCBRoleState *)v5))->CCBRoleState::InitUI(v3);
        inited[837] = 0;
      }
      ++v3;
    }
    byte_17A9924 = 0;
    byte_17A9925 = 0;
  }
  else
  {
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      v8 = (CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)((UIWnd *)this) + 16);
      if ( v8->m_pObjMsgBuffer[v7 + 153] )
      {
        inited = (((CCBRoleState *)v8))->CCBRoleState::InitUI(v6);
        if ( !inited[837] )
          break;
      }
      v7 += 892;
      ++v6;
      if ( v7 >= 4460 )
      {
        if ( !byte_17A9924 )
        {
          byte_17A9924 = 1;
          sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D8884);
          DlgItem = GetDlgItem(g_todo_BFDA50, 1004);
          SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
          LOBYTE(inited) = (((CCBSystem *)*(CCBSystem **)((UIWnd *)this)))->CCBSystem::ProcFlee(byte_17A9924);
        }
        return (char)inited;
      }
    }
  }
  return (char)inited;
}

// 0x004E0820
char CCBUI::UpdateAnimation()
{
  char result; // al

  result = byte_17A9934;
  if ( byte_17A9934 )
  {
    byte_17A9934 = 0;
    (((CCBStage *)this))->CCBStage::InitUIByName() /* [ROWTABLE] */;
  }
  if ( byte_17A9935 )
  {
    byte_17A9935 = 0;
    result = (((CCBRoleState *)this))->CCBRoleState::SyncRoleUIData();
  }
  if ( byte_17A9936 )
  {
    byte_17A9936 = 0;
    result = this->CCBUI::UpdateDebugStatus();
  }
  if ( byte_17A9938 )
  {
    byte_17A9938 = 0;
    this->CCBUI::InitUI_4E3D90();
  }
  if ( byte_17A9937 )
  {
    byte_17A9937 = 0;
    result = this->CCBUI::InitUI();
  }
  if ( byte_17A9944 )
  {
    byte_17A9944 = 0;
    result = (((CCBRoleState *)this))->CCBRoleState::UpdateDebugDialog();
  }
  if ( byte_17A9945 )
  {
    byte_17A9945 = 0;
    result = (((CCBRoleState *)this))->CCBRoleState::ApplyDebugEdits();
  }
  if ( (_BYTE)g_bCommandEdited )
  {
    LOBYTE(g_bCommandEdited) = 0;
    result = this->CCBUI::PopulateCommandList();
  }
  if ( byte_17A9948 )
  {
    byte_17A9948 = 0;
    result = this->CCBUI::ShowCommandDetails();
  }
  if ( byte_17A9947 )
  {
    byte_17A9947 = 0;
    result = this->CCBUI::CloseCommandDialog();
  }
  if ( byte_17A994A )
  {
    byte_17A994A = 0;
    result = (unsigned __int8)(((PAL_GDB *)this))->PAL_GDB::SetupSkillConfig();
  }
  if ( byte_17A9949 )
  {
    byte_17A9949 = 0;
    result = this->CCBUI::ApplyCommandEdit();
  }
  if ( byte_17A994B )
  {
    byte_17A994B = 0;
    result = this->CCBUI::ShowSkillDetails();
  }
  if ( byte_17A994C )
  {
    byte_17A994C = 0;
    result = CCBRoleState::GetTargetCommand();
  }
  if ( byte_17A994D )
  {
    byte_17A994D = 0;
    result = (((PAL_GDB *)this))->PAL_GDB::RefreshPartyDialog();
  }
  if ( byte_17A994E )
  {
    byte_17A994E = 0;
    return (((PAL_GDB *)this))->PAL_GDB::PopulateAvailableRoles();
  }
  return result;
}

// 0x004E0980
char CCBUI::UpdateState()
{
  char result; // al
  int v2; // esi
  HWND DlgItem; // edi

  result = g_nCombatViewMode;
  v2 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + 16);
  if ( g_nCombatViewMode == 4 )
  {
    DlgItem = GetDlgItem(g_hMainWnd, 1201);
    result = *(_BYTE *)(v2 + 430012);
    if ( result )
    {
      byte_5D8808 = 1;
      sprintf((char *const)&g_CCBStageCamBuffer, "%03d-%03d", *(_DWORD *)(v2 + 430032), *(_DWORD *)(v2 + 430036));
      return SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    }
    else if ( byte_5D8808 == 1 )
    {
      byte_5D8808 = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, aStopped);
      return SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    }
  }
  return result;
}

// 0x004E0A60
int CCBUI::DlgProcEditorMain(CCBUI *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam)
{
  HWND DlgItem; // ebx
  HWND v7; // ebp
  HWND v8; // edi
  int result; // eax
  void (__stdcall *v10)(HWND, UINT, WPARAM, LPARAM); // esi
  double v11; // st7
  bool v12; // zf
  LPARAM v13; // [esp+0x4] [ebp-0x18]
  HWND hWnd; // [esp+0x18] [ebp-0x4]
  HWND hDlga; // [esp+0x24] [ebp+0x8]

  DlgItem = GetDlgItem(hDlg, 1001);
  v7 = GetDlgItem(hDlg, 1003);
  hDlga = GetDlgItem(hDlg, 1004);
  hWnd = GetDlgItem(hDlg, 1005);
  v8 = GetDlgItem(hDlg, 1010);
  if ( uMsg > 0x110 )
  {
    if ( uMsg == 273 )
    {
      if ( wParam > 0x3F1u )
      {
        switch ( wParam )
        {
          case 0x3F3u:
            if ( !g_nCombatViewMode )
              return 0;
            (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)((UIWnd *)a1) + 12)))->CCBSystem::SetThreadFlag(1);
            if ( g_hMainWnd )
              DestroyWindow(g_hMainWnd);
            g_nCombatViewMode = 0;
            g_hMainWnd = CreateDialogParamA(
                           hInstance,
                           (LPCSTR)0x69,
                           (HWND)g_todo_BFDA4C,
                           (DLGPROC)CCBUI::CloseDialog,
                           0);
            ::ShowWindow(g_hMainWnd, 4);
            result = 0;
            break;
          case 0x3F4u:
            LOBYTE(g_bWPARAM_17A9926) = 1;
            result = 0;
            break;
          case 0x3F5u:
            byte_17A9927 = byte_17A9927 == 0;
            return 0;
          case 0x3F6u:
            if ( g_nCombatViewMode == 5 )
              return 0;
            (((CCBUI *)a1))->CCBUI::StartMagicThread();
            if ( g_hMainWnd )
              DestroyWindow(g_hMainWnd);
            g_nCombatViewMode = 5;
            g_hMainWnd = CreateDialogParamA(
                           hInstance,
                           (LPCSTR)0x71,
                           (HWND)g_todo_BFDA4C,
                           (DLGPROC)CCBStageCam::StoreCurrentView,
                           0);
            ::ShowWindow(g_hMainWnd, 4);
            (((CCBStageCam *)a1))->CCBStageCam::sub_4E95A0(g_hMainWnd);
            result = 0;
            break;
          case 0x3F7u:
            formal = 0.0;
            v13 = 0;
            goto LABEL_25;
          case 0x3F8u:
            if ( g_nCombatViewMode == 6 )
              return 0;
            (((CCBUI *)a1))->CCBUI::StartMagicThread();
            if ( g_hMainWnd )
              DestroyWindow(g_hMainWnd);
            g_nCombatViewMode = 6;
            g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x72, (HWND)g_todo_BFDA4C, CCBUI::_nearby_4eb230, 0);
            ::ShowWindow(g_hMainWnd, 4);
            (((CCBCamControl *)a1))->CCBCamControl::sub_4EB6F0(g_hMainWnd);
            result = 0;
            break;
          default:
            return 0;
        }
        return result;
      }
      if ( wParam == 1009 )
      {
        if ( g_nCombatViewMode != 1 )
        {
          (((CCBUI *)a1))->CCBUI::StartMagicThread();
          if ( g_hMainWnd )
            DestroyWindow(g_hMainWnd);
          g_nCombatViewMode = 1;
          g_hMainWnd = CreateDialogParamA(
                         hInstance,
                         (LPCSTR)0x68,
                         (HWND)g_todo_BFDA4C,
                         (DLGPROC)CCBUI::DlgProcEffect,
                         0);
          ::ShowWindow(g_hMainWnd, 4);
          return 0;
        }
      }
      else
      {
        if ( wParam <= 0x3ECu )
        {
          switch ( wParam )
          {
            case 0x3ECu:
              v12 = byte_17A9924 != 0;
              byte_17A9924 = byte_17A9924 == 0;
              if ( v12 )
              {
                byte_17A9925 = 1;
                sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D88E0);
              }
              else
              {
                sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D8884);
              }
              SendMessageA(hDlga, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
              return 0;
            case 1u:
              EndDialog(hDlg, 1);
              DestroyWindow((HWND)g_todo_BFDA4C);
              return 0;
            case 2u:
              return 1;
          }
          if ( wParam != 1003 )
            return 0;
          formal = 1.0;
          v13 = (__int64)(1.0 * 100.0);
LABEL_25:
          v10 = (void ( *)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
          SendMessageA(DlgItem, 0x405u, 1u, v13);
          v11 = formal;
LABEL_16:
          sprintf(unk_17A95E4, "Speed%1.2f", v11);
          v10(v7, 0xCu, 0, (LPARAM)unk_17A95E4);
          return 0;
        }
        if ( wParam == 1005 )
        {
          v12 = byte_5D87F0 != 0;
          byte_5D87F0 = byte_5D87F0 == 0;
          if ( v12 )
            sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D88C8);
          else
            sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D88D4);
          SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
          return 0;
        }
        if ( wParam == 1006 )
        {
          if ( g_nCombatViewMode != 2 )
          {
            (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)((UIWnd *)a1) + 12)))->CCBSystem::SetThreadFlag(1);
            (((CCBUI *)*(CCBUI **)(*(_DWORD *)((UIWnd *)a1) + 4)))->CCBUI::CreateResultWindow(1);
            if ( g_hMainWnd )
              DestroyWindow(g_hMainWnd);
            g_nCombatViewMode = 2;
            g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x6A, (HWND)g_todo_BFDA4C, CCBUI::CombatDlgProcThunk, 0);
            ::ShowWindow(g_hMainWnd, 4);
            (((CCBRoleState *)a1))->CCBRoleState::UpdateDebugTreeView();
            return 0;
          }
        }
        else if ( wParam == 1007 && g_nCombatViewMode != 4 )
        {
          (((CCBUI *)a1))->CCBUI::StartMagicThread();
          if ( g_hMainWnd )
            DestroyWindow(g_hMainWnd);
          g_nCombatViewMode = 4;
          g_hMainWnd = CreateDialogParamA(
                         hInstance,
                         (LPCSTR)0x6E,
                         (HWND)g_todo_BFDA4C,
                         (DLGPROC)PAL_GDB::DlgProcCamera,
                         0);
          ::ShowWindow(g_hMainWnd, 4);
          byte_17A994F = 1;
          return 0;
        }
      }
    }
    else if ( uMsg == 276 )
    {
      v10 = (void ( *)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
      v11 = (double)SendMessageA(DlgItem, 0x400u, 0, 0) / 100.0;
      formal = v11;
      goto LABEL_16;
    }
    return 0;
  }
  if ( uMsg != 272 )
  {
    if ( uMsg == 16 )
    {
      EndDialog(hDlg, wParam);
      DestroyWindow((HWND)g_todo_BFDA4C);
      return 1;
    }
    return 0;
  }
  SetWindowPos(hDlg, 0, 0, 600, 801, 130, 0x80u);
  SendMessageA(DlgItem, 0x407u, 0, 0);
  SendMessageA(DlgItem, 0x408u, 0, 2000);
  SendMessageA(DlgItem, 0x405u, 1u, (__int64)(formal * 100.0));
  sprintf(unk_17A95E4, "Speed%1.2f", formal);
  SendMessageA(v7, 0xCu, 0, (LPARAM)unk_17A95E4);
  if ( byte_17A9924 )
    sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D8884);
  else
    sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D88E0);
  SendMessageA(hDlga, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
  if ( byte_5D87F0 )
    sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D88D4);
  else
    sprintf((char *const)&g_CCBStageCamBuffer, "%s", &unk_5D88C8);
  SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
  sprintf((char *const)&g_CCBStageCamBuffer, "%s Build %s %s Release", "PAL3 COMBAT SYSTEM 1.03", "Jan  5 2004", a164229);
  SendMessageA(v8, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
  return 0;
}

// 0x004E10E0
int CCBUI::CloseDialog(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if ( uMsg == 16 )
  {
    EndDialog(hDlg, (unsigned __int16)wParam);
    return 1;
  }
  else
  {
    if ( uMsg == 272 )
    {
      SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
    }
    else if ( uMsg == 273 && (unsigned __int16)wParam == 1 )
    {
      EndDialog(hDlg, 1);
      return 0;
    }
    return 0;
  }
}

// 0x004E1160
int CCBUI::DlgProcEffect(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  return (((CEffectSystem *)pfVal))->CEffectSystem::CreateEffectChain((CCBUI *)pfVal, hDlg, msg, wParam, lParam);
}

// 0x004E16F0
unsigned __int8 * CCBUI::PopulateSceneList(HWND hDlg)
{
  LPARAM v2; // esi
  HWND DlgItem; // ebp
  unsigned __int8 *result; // eax
  HANDLE FirstFileA; // eax
  HANDLE hFindFile; // [esp+0x10] [ebp-0x270]
  LPARAM lParam[10]; // [esp+0x14] [ebp-0x26C] BYREF
  CHAR Filename[260]; // [esp+0x3C] [ebp-0x244] BYREF
  _WIN32_FIND_DATAA FindFileData; // [esp+0x140] [ebp-0x140] BYREF

  v2 = 0;
  DlgItem = GetDlgItem(hDlg, 1203);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  memset(Filename, 0, sizeof(Filename));
  GetModuleFileNameA(0, Filename, 0x104u);
  result = _mbsrchr((const unsigned char *)(const unsigned __int8 *)Filename, 0x5Cu);
  if ( result )
  {
    _mbsrchr((const unsigned char *)(const unsigned __int8 *)Filename, 0x5Cu)[1] = 0;
    lstrcatA(Filename, aBasedataCbscen);
    FirstFileA = FindFirstFileA(Filename, &FindFileData);
    hFindFile = FirstFileA;
    if ( FirstFileA == (HANDLE)-1 )
    {
      return (unsigned __int8 *)MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D88FC, 0, 0);
    }
    else
    {
      for ( result = (unsigned __int8 *)FindNextFileA(FirstFileA, &FindFileData);
            result;
            result = (unsigned __int8 *)FindNextFileA(hFindFile, &FindFileData) )
      {
        if ( !_mbsrchr((const unsigned char *)(const unsigned __int8 *)FindFileData.cFileName, 0x2Eu) )
        {
          lParam[0] = 1;
          lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
          lParam[1] = v2;
          lParam[2] = 0;
          sprintf((char *const)&g_CCBStageCamBuffer, "%03d", v2);
          SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
          lParam[5] = (LPARAM)FindFileData.cFileName;
          lParam[2] = 1;
          SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
          ++v2;
        }
      }
    }
  }
  return result;
}

// 0x004E1870
unsigned __int8 * CCBUI::LoadSceneByIndex(int nVal)
{
  unsigned __int8 *result; // eax
  HANDLE FirstFileA; // eax
  void *v5; // ebx
  int v6; // edi
  int v7; // [esp+0xC] [ebp-0x248]
  CHAR Filename[260]; // [esp+0x10] [ebp-0x244] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+0x114] [ebp-0x140] BYREF

  memset(Filename, 0, sizeof(Filename));
  v7 = 0;
  GetModuleFileNameA(0, Filename, 0x104u);
  result = _mbsrchr((const unsigned char *)(const unsigned __int8 *)Filename, 0x5Cu);
  if ( result )
  {
    _mbsrchr((const unsigned char *)(const unsigned __int8 *)Filename, 0x5Cu)[1] = 0;
    lstrcatA(Filename, aBasedataCbscen);
    FirstFileA = FindFirstFileA(Filename, &FindFileData);
    v5 = FirstFileA;
    if ( FirstFileA == (HANDLE)-1 )
    {
      return (unsigned __int8 *)MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D88FC, 0, 0);
    }
    else
    {
      for ( result = (unsigned __int8 *)FindNextFileA(FirstFileA, &FindFileData);
            result;
            result = (unsigned __int8 *)FindNextFileA(v5, &FindFileData) )
      {
        if ( !_mbsrchr((const unsigned char *)(const unsigned __int8 *)FindFileData.cFileName, 0x2Eu) )
        {
          if ( v7 == nVal )
          {
            v6 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + 20);
            if ( strcmp(FindFileData.cFileName, (const char *)(v6 + 345)) )
            {
              sub_511630(v6);
              (((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + 20)))->CCBStageScene::LoadModel(FindFileData.cFileName);
              strcpy((char *)&unk_C11720, FindFileData.cFileName);
            }
          }
          ++v7;
        }
      }
    }
  }
  return result;
}

// 0x004E1A10
int CCBUI::CombatDlgProcThunk(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return (((CCBRoleState *)pfVal))->CCBRoleState::CombatDialogProc(pfVal, hDlg, uMsg, wParam, lParam);
}

// 0x004E1F70
int CCBUI::SettingsDialogProc(HWND hDlg, unsigned int dwVal, WPARAM pData, LPARAM a5)
{
  HWND v5; // eax
  HWND DlgItem; // eax
  HWND v7; // ebx
  HWND v8; // eax
  HWND v9; // ebx
  HWND v10; // eax
  HWND v11; // ebx
  HWND v12; // eax
  HWND v13; // ebx
  HWND v14; // eax
  HWND v15; // ebx
  HWND v16; // eax
  HWND v17; // ebx
  HWND v18; // eax
  HWND v19; // ebx
  HWND v20; // eax
  HWND v21; // ebx
  HWND v22; // eax
  HWND v23; // edi
  unsigned int v25; // [esp+0x8] [ebp-0x28]
  LPARAM lParam[2]; // [esp+0xC] [ebp-0x24] BYREF
  LPARAM v27[3]; // [esp+0x14] [ebp-0x1C] BYREF
  void *v28; // [esp+0x20] [ebp-0x10]
  int v29; // [esp+0x28] [ebp-0x8]
  int v30; // [esp+0x2C] [ebp-0x4]

  v5 = 0;
  v25 = 0;
  lParam[1] = 1;
  lParam[0] = 1;
  if ( dwVal > 0x110 )
  {
    if ( dwVal == 273 )
    {
      if ( (unsigned __int16)pData > 0x428u )
      {
        if ( (unsigned __int16)pData == 1065 )
        {
          unk_5D87F8 = 3;
          goto LABEL_32;
        }
        if ( (unsigned __int16)pData == 1066 )
        {
          unk_5D87F8 = 4;
          goto LABEL_32;
        }
      }
      else
      {
        switch ( (unsigned __int16)pData )
        {
          case 0x428u:
            unk_5D87F8 = 2;
            goto LABEL_32;
          case 1u:
            byte_17A9938 = 1;
            EndDialog(hDlg, 1);
            return 1;
          case 0x426u:
            unk_5D87F8 = 0;
            goto LABEL_32;
          case 0x427u:
            unk_5D87F8 = 1;
LABEL_32:
            byte_17A9937 = 1;
            byte_17A9938 = 1;
            break;
        }
      }
    }
    return 0;
  }
  if ( dwVal != 272 )
  {
    if ( dwVal != 2 )
    {
      if ( dwVal != 78 || pData != 1114 || *(_DWORD *)(a5 + 8) != -551 )
        return 0;
      DlgItem = GetDlgItem(hDlg, 1114);
      g_nCCBUISelectedRole = SendMessageA(DlgItem, 0x130Bu, 0, 0);
      goto LABEL_32;
    }
    return 1;
  }
  if ( roleIdx <= 4 )
    v25 = roleIdx;
  switch ( roleIdx )
  {
    case 0u:
      v5 = GetDlgItem(hDlg, 1062);
      break;
    case 1u:
      v5 = GetDlgItem(hDlg, 1063);
      break;
    case 2u:
      v5 = GetDlgItem(hDlg, 1064);
      break;
    case 3u:
      v5 = GetDlgItem(hDlg, 1065);
      break;
    case 4u:
      v5 = GetDlgItem(hDlg, 1066);
      break;
    default:
      break;
  }
  SendMessageA(v5, 0xF1u, 1u, 0);
  v7 = GetDlgItem(hDlg, 1087);
  v8 = GetDlgItem(hDlg, 1102);
  SendMessageA(v7, 0x469u, (WPARAM)v8, 0);
  SendMessageA(v7, 0x465u, 0, 65540);
  SendMessageA(v7, 0x46Du, 0xAu, 0);
  SendMessageA(v7, 0x46Bu, 1u, (LPARAM)lParam);
  v9 = GetDlgItem(hDlg, 1088);
  v10 = GetDlgItem(hDlg, 1103);
  SendMessageA(v9, 0x469u, (WPARAM)v10, 0);
  SendMessageA(v9, 0x465u, 0, 65540);
  SendMessageA(v9, 0x46Du, 0xAu, 0);
  SendMessageA(v9, 0x46Bu, 1u, (LPARAM)lParam);
  v11 = GetDlgItem(hDlg, 1089);
  v12 = GetDlgItem(hDlg, 1105);
  SendMessageA(v11, 0x469u, (WPARAM)v12, 0);
  SendMessageA(v11, 0x465u, 0, 65540);
  SendMessageA(v11, 0x46Du, 0xAu, 0);
  SendMessageA(v11, 0x46Bu, 1u, (LPARAM)lParam);
  v13 = GetDlgItem(hDlg, 1090);
  v14 = GetDlgItem(hDlg, 1106);
  SendMessageA(v13, 0x469u, (WPARAM)v14, 0);
  SendMessageA(v13, 0x465u, 0, 65540);
  SendMessageA(v13, 0x46Du, 0xAu, 0);
  SendMessageA(v13, 0x46Bu, 1u, (LPARAM)lParam);
  v15 = GetDlgItem(hDlg, 1091);
  v16 = GetDlgItem(hDlg, 1107);
  SendMessageA(v15, 0x469u, (WPARAM)v16, 0);
  SendMessageA(v15, 0x465u, 0, 65540);
  SendMessageA(v15, 0x46Du, 0xAu, 0);
  SendMessageA(v15, 0x46Bu, 1u, (LPARAM)lParam);
  v17 = GetDlgItem(hDlg, 1092);
  v18 = GetDlgItem(hDlg, 1109);
  SendMessageA(v17, 0x469u, (WPARAM)v18, 0);
  SendMessageA(v17, 0x465u, 0, 65540);
  SendMessageA(v17, 0x46Du, 0xAu, 0);
  SendMessageA(v17, 0x46Bu, 1u, (LPARAM)lParam);
  v19 = GetDlgItem(hDlg, 1093);
  v20 = GetDlgItem(hDlg, 1110);
  SendMessageA(v19, 0x469u, (WPARAM)v20, 0);
  SendMessageA(v19, 0x465u, 0, 65540);
  SendMessageA(v19, 0x46Du, 0xAu, 0);
  SendMessageA(v19, 0x46Bu, 1u, (LPARAM)lParam);
  v21 = GetDlgItem(hDlg, 1094);
  v22 = GetDlgItem(hDlg, 1112);
  SendMessageA(v21, 0x469u, (WPARAM)v22, 0);
  SendMessageA(v21, 0x465u, 0, 65540);
  SendMessageA(v21, 0x46Du, 0xAu, 0);
  SendMessageA(v21, 0x46Bu, 1u, (LPARAM)lParam);
  v23 = GetDlgItem(hDlg, 1114);
  SendMessageA(v23, 0x1331u, 0, 10);
  SendMessageA(v23, 0x1329u, 0, 1310730);
  v27[0] = 1;
  v29 = 0;
  v30 = 0;
  v28 = (void *)&unk_5D8964;
  SendMessageA(v23, 0x1307u, 0, (LPARAM)v27);
  v28 = (void *)&unk_5D8960;
  SendMessageA(v23, 0x1307u, 1u, (LPARAM)v27);
  v28 = (void *)&unk_5D895C;
  SendMessageA(v23, 0x1307u, 2u, (LPARAM)v27);
  v28 = (void *)&unk_5D8958;
  SendMessageA(v23, 0x1307u, 3u, (LPARAM)v27);
  v28 = (void *)&unk_5D8954;
  SendMessageA(v23, 0x1307u, 4u, (LPARAM)v27);
  v28 = (void *)&unk_5D8950;
  SendMessageA(v23, 0x1307u, 5u, (LPARAM)v27);
  byte_17A9938 = 0;
  unk_5D87F8 = v25;
  byte_17A9937 = 1;
  return 1;
}

// 0x004E2430
int CCBUI::HandleWindowMessage(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if ( uMsg == 272 )
  {
    byte_17A9944 = 1;
  }
  else if ( uMsg == 273 )
  {
    if ( (unsigned __int16)wParam == 1 )
    {
      EndDialog((HWND)g_hCombatDlg1, 0);
      g_hCombatDlg1 = 0;
      return 0;
    }
    if ( (unsigned __int16)wParam == 2 )
    {
      byte_17A9945 = 1;
      return 0;
    }
  }
  return 0;
}

// 0x004E2490
int CCBUI::DlgProcMain(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  return (((CCBUI *)pfVal))->CCBUI::CommandEditDialogProc((int *)pfVal, hDlg, msg, wParam, lParam);
}

// 0x004E24C0
int CCBUI::CommandEditDialogProc(int *p_DWORD, HWND hDlg, int nVal, int nVal2, int nVal3)
{
  HWND DlgItem; // ebp
  HWND v7; // ebx
  HWND v8; // edi
  int v10; // edi
  int j; // esi
  int *v12; // eax
  int SlotCount; // edi
  int i; // esi
  int *TargetRole; // eax
  LRESULT v16; // eax
  LRESULT v17; // eax
  signed int SkillID; // ebp
  signed int v19; // edi
  int ItemID; // eax
  int SkillNum; // eax
  int v22; // [esp+0x10] [ebp-0x174] BYREF
  int v23; // [esp+0x14] [ebp-0x170]
  int v24; // [esp+0x18] [ebp-0x16C]
  LPARAM lParam[8]; // [esp+0x1C] [ebp-0x168] BYREF
  HWND v26; // [esp+0x3C] [ebp-0x148]
  HWND hWnd; // [esp+0x40] [ebp-0x144]
  LPARAM v28[10]; // [esp+0x44] [ebp-0x140] BYREF
  char pOut[12]; // [esp+0x6C] [ebp-0x118] BYREF
  char v30[12]; // [esp+0x78] [ebp-0x10C] BYREF
  char Buffer[256]; // [esp+0x84] [ebp-0x100] BYREF

  DlgItem = GetDlgItem(hDlg, 1142);
  v7 = GetDlgItem(hDlg, 1146);
  hWnd = GetDlgItem(hDlg, 1040);
  v26 = GetDlgItem(hDlg, 1149);
  v8 = GetDlgItem(hDlg, 1086);
  if ( nVal == 78 )
  {
    if ( nVal2 == 1142 )
    {
      if ( *(_DWORD *)(nVal3 + 8) == -2 && *(_DWORD *)(nVal3 + 12) != -1 )
      {
        dword_5D8800 = *(_DWORD *)(nVal3 + 12);
        byte_17A9948 = 1;
        EnableWindow(hWnd, 1);
        EnableWindow(v26, 1);
        EnableWindow(v8, 1);
      }
    }
    else if ( nVal2 == 1146 && *(_DWORD *)(nVal3 + 8) == -3 && *(_DWORD *)(nVal3 + 12) != -1 )
    {
      index = *(_DWORD *)(nVal3 + 12);
      byte_17A994A = 1;
      return 0;
    }
    return 0;
  }
  if ( nVal != 272 )
  {
    if ( nVal == 273 )
    {
      if ( (unsigned __int16)nVal2 > 0x412u )
      {
        switch ( (unsigned __int16)nVal2 )
        {
          case 0x413u:
            v22 = 0xFFFF;
            v23 = 0;
            v24 = 0;
LABEL_25:
            SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
            for ( i = 0; i < SlotCount; ++i )
            {
              TargetRole = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v30);
              v22 = (unsigned long)*TargetRole;
              v23 = (unsigned long)TargetRole[1];
              v24 = (unsigned long)TargetRole[2];
              if ( *(_BYTE *)(v24 + 612) == 1 )
              {
                (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v22);
                goto LABEL_25;
              }
            }
            goto LABEL_10;
          case 0x43Eu:
            byte_17A9949 = 1;
            return 0;
          case 0x47Du:
            byte_17A994B = 1;
            return 0;
        }
      }
      else
      {
        switch ( (unsigned __int16)nVal2 )
        {
          case 0x412u:
            v22 = 0xFFFF;
            v23 = 0;
            v24 = 0;
LABEL_14:
            v10 = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
            for ( j = 0; j < v10; ++j )
            {
              v12 = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
              v22 = (unsigned long)*v12;
              v23 = (unsigned long)v12[1];
              v24 = (unsigned long)v12[2];
              if ( *(_BYTE *)(v24 + 612) == 2 )
              {
                (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v22);
                goto LABEL_14;
              }
            }
            goto LABEL_10;
          case 1u:
            byte_17A9947 = 1;
            return 0;
          case 0x410u:
            byte_17A994C = 1;
            return 0;
          case 0x411u:
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::Reset();
LABEL_10:
            (((CCBUI *)p_DWORD))->CCBUI::PopulateCommandList();
            return 0;
        }
      }
    }
    return 0;
  }
  memset(lParam, 0, sizeof(lParam));
  LOBYTE(g_bCommandEdited) = 1;
  v16 = SendMessageA(DlgItem, 0x1037u, 0, 0);
  LOBYTE(v16) = v16 | 0x21;
  SendMessageA(DlgItem, 0x1036u, 0, v16);
  v17 = SendMessageA(v7, 0x1037u, 0, 0);
  LOBYTE(v17) = v17 | 0x21;
  SendMessageA(v7, 0x1036u, 0, v17);
  lParam[0] = 7;
  lParam[1] = 0;
  lParam[2] = 120;
  lParam[3] = (LPARAM)"Name";
  SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParam);
  lParam[1] = 1;
  lParam[2] = 50;
  lParam[3] = (LPARAM)&g_pCombatUIData;
  SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParam);
  lParam[2] = 50;
  lParam[3] = (LPARAM)"HP";
  SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)lParam);
  lParam[2] = 50;
  lParam[3] = (LPARAM)"GP";
  SendMessageA(DlgItem, 0x101Bu, 3u, (LPARAM)lParam);
  lParam[2] = 50;
  lParam[3] = (LPARAM)"MP";
  SendMessageA(DlgItem, 0x101Bu, 4u, (LPARAM)lParam);
  lParam[2] = 145;
  lParam[3] = (LPARAM)"Name";
  SendMessageA(v7, 0x101Bu, 0, (LPARAM)lParam);
  SkillID = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillID();
  memset(v28, 0, sizeof(v28));
  v19 = 0;
  v28[0] = 1;
  v28[2] = 0;
  v28[5] = (LPARAM)Buffer;
  if ( SkillID <= 0 )
    return 0;
  do
  {
    ItemID = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(v19);
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(ItemID);
    sprintf(Buffer, "%03d%s", v19, (const char *)(SkillNum + 4));
    v28[1] = v19;
    v28[2] = 0;
    SendMessageA(v7, 0x1007u, 0, (LPARAM)v28);
    ++v19;
  }
  while ( v19 < SkillID );
  return 0;
}

// 0x004E2AE0
LRESULT CCBUI::HandleRoleStateDialog(int nVal)
{
  LRESULT result; // eax
  HWND DlgItem; // ebx
  int v5; // edx
  tagRoleState *inited; // eax
  int v7; // eax
  tagRoleState *v8; // eax
  int v9; // ecx
  tagRoleState *v10; // eax
  LPARAM lParam[10]; // [esp+0xC] [ebp-A8h] BYREF
  char Buffer[128]; // [esp+0x34] [ebp-0x80] BYREF

  result = g_nCombatViewMode;
  if ( g_nCombatViewMode == 2 )
  {
    DlgItem = GetDlgItem(g_hMainWnd, 1000);
    result = g_nCombatViewMode;
    if ( g_nCombatViewMode == 2 )
    {
      v5 = (int)((UIWnd *)this);
      memset(lParam, 0, sizeof(lParam));
      lParam[0] = 1;
      lParam[1] = nVal;
      lParam[5] = (LPARAM)Buffer;
      lParam[2] = 2;
      inited = (((CCBRoleState *)*(CCBRoleState **)(v5 + 16)))->CCBRoleState::InitUI(nVal);
      sprintf(Buffer, (const char *)&dir[20], inited->nHP);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      v7 = (int)((UIWnd *)this);
      lParam[2] = 3;
      v8 = (((CCBRoleState *)*(CCBRoleState **)(v7 + 16)))->CCBRoleState::InitUI(nVal);
      sprintf(Buffer, (const char *)&dir[20], v8->nGP);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      v9 = (int)((UIWnd *)this);
      lParam[2] = 4;
      v10 = (((CCBRoleState *)*(CCBRoleState **)(v9 + 16)))->CCBRoleState::InitUI(nVal);
      sprintf(Buffer, (const char *)&dir[20], v10->nMP);
      return SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
  }
  return result;
}

// 0x004E3780
char CCBUI::UpdateDebugStatus()
{
  HWND DlgItem; // ebp
  HWND v3; // edi
  char result; // al
  int v5; // edi
  int SlotState; // eax
  int v7; // eax
  int ActionTypeBySlot; // eax
  int v9; // eax
  int v10; // eax
  int RoleCount; // eax
  HWND hWnd; // [esp+0x10] [ebp-0x20]
  HWND v13; // [esp+0x14] [ebp-0x1C]
  HWND v14; // [esp+0x18] [ebp-0x18]
  HWND v15; // [esp+0x1C] [ebp-0x14]
  HWND v16; // [esp+0x20] [ebp-0x10]
  HWND v17; // [esp+0x24] [ebp-0xC]
  HWND v18; // [esp+0x28] [ebp-0x8]
  HWND v19; // [esp+0x2C] [ebp-0x4]

  GetDlgItem(g_hMainWnd, 1024);
  DlgItem = GetDlgItem(g_hMainWnd, 1026);
  hWnd = GetDlgItem(g_hMainWnd, 1032);
  v13 = GetDlgItem(g_hMainWnd, 1025);
  v14 = GetDlgItem(g_hMainWnd, 1033);
  v15 = GetDlgItem(g_hMainWnd, 1027);
  v16 = GetDlgItem(g_hMainWnd, 1034);
  v3 = GetDlgItem(g_hMainWnd, 1028);
  GetDlgItem(g_hMainWnd, 1029);
  v17 = GetDlgItem(g_hMainWnd, 1030);
  v18 = GetDlgItem(g_hMainWnd, 1031);
  GetDlgItem(g_hMainWnd, 1035);
  v19 = GetDlgItem(g_hMainWnd, 1036);
  result = roleIdx;
  if ( roleIdx <= 0xA )
  {
    result = *(_BYTE *)(this->m_fontcolor.Color + 892 * roleIdx + 577);
    if ( result )
    {
      SendMessageA(v3, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
      v5 = atoi((const char *)&g_CCBStageCamBuffer);
      SlotState = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetSlotState(roleIdx, v5);
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], SlotState);
      SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
      SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
      v7 = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::CalcSpeedByLevel(roleIdx, v5);
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v7);
      SendMessageA(v13, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
      SendMessageA(v14, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
      ActionTypeBySlot = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetActionTypeBySlot(roleIdx, v5);
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], ActionTypeBySlot);
      SendMessageA(v15, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
      SendMessageA(v16, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
      v9 = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::CalcDefenseByLevel(roleIdx, v5);
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v9);
      SendMessageA(v17, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
      v10 = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::CalcDamage(roleIdx, v5);
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v10);
      SendMessageA(v18, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
      RoleCount = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::GetRoleCount(v5);
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], RoleCount);
      return SendMessageA(v19, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
    }
  }
  return result;
}

// 0x004E3A20
LRESULT CCBUI::InitUI()
{
  void *v1; // ebp
  HWND DlgItem; // edi
  int v3; // ebx
  char v4; // bl
  int RoleNum; // eax
  HWND v6; // eax
  void (__stdcall *v7)(HWND, UINT, WPARAM, LPARAM); // ebx
  int j; // ebp
  int v9; // edi
  char v10; // bl
  char *v11; // edi
  HWND v12; // eax
  LRESULT result; // eax
  int v14; // [esp-0x4] [ebp-0x2C]
  int v15; // [esp-0x4] [ebp-0x2C]
  char v16; // [esp+0x13] [ebp-0x15]
  HWND hWnd; // [esp+0x14] [ebp-0x14]
  int i; // [esp+0x18] [ebp-0x10]
  char *lParam; // [esp+0x20] [ebp-0x8]
  int v21; // [esp+0x24] [ebp-0x4]

  v1 = 0;
  DlgItem = 0;
  hWnd = 0;
  unk_5D87FC = unk_5D87F8;
  g_nCCBUI_17A9940 = g_nCCBUISelectedRole;
  for ( i = 0; i < 8; ++i )
  {
    v3 = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87F8)->dwSkillID[8 * g_nCCBUISelectedRole
                                                                                              + 7
                                                                                              + i];
    v16 = *((_BYTE *)&(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87F8)->dwMagicID[7][2 * g_nCCBUISelectedRole + 1]
          + i);
    v21 = (unsigned __int8)(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87F8)->bMagicMastered[8][8 * g_nCCBUISelectedRole + 4 + i]
        + 1;
    if ( v3 )
    {
      RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v3);
      v4 = v16;
      lParam = (char *)(RoleNum + 28);
    }
    else
    {
      lParam = (char *)&unk_5D89B0;
      v4 = 0;
      v21 = 0;
    }
    switch ( i )
    {
      case 0:
        DlgItem = GetDlgItem((HWND)dwInitParam, 1052);
        v6 = GetDlgItem((HWND)dwInitParam, 1102);
        goto LABEL_15;
      case 1:
        DlgItem = GetDlgItem((HWND)dwInitParam, 1054);
        v14 = 1103;
        goto LABEL_14;
      case 2:
        DlgItem = GetDlgItem((HWND)dwInitParam, 1055);
        v6 = GetDlgItem((HWND)dwInitParam, 1105);
        goto LABEL_15;
      case 3:
        DlgItem = GetDlgItem((HWND)dwInitParam, 1056);
        v6 = GetDlgItem((HWND)dwInitParam, 1106);
        goto LABEL_15;
      case 4:
        DlgItem = GetDlgItem((HWND)dwInitParam, 1057);
        v14 = 1107;
        goto LABEL_14;
      case 5:
        DlgItem = GetDlgItem((HWND)dwInitParam, 1058);
        v6 = GetDlgItem((HWND)dwInitParam, 1109);
        goto LABEL_15;
      case 6:
        DlgItem = GetDlgItem((HWND)dwInitParam, 1060);
        v6 = GetDlgItem((HWND)dwInitParam, 1110);
        goto LABEL_15;
      case 7:
        DlgItem = GetDlgItem((HWND)dwInitParam, 1061);
        v14 = 1112;
LABEL_14:
        v6 = GetDlgItem((HWND)dwInitParam, v14);
LABEL_15:
        v1 = v6;
        break;
      default:
        break;
    }
    if ( v4 )
    {
      v7 = (void ( *)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
      SendMessageA(DlgItem, 0xF1u, 1u, 0);
    }
    else
    {
      SendMessageA(DlgItem, 0xF1u, 0, 0);
      v7 = (void ( *)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
    }
    v7(DlgItem, 0xCu, 0, (LPARAM)lParam);
    sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], v21);
    v7(v1, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
  }
  for ( j = 0; j < 6; ++j )
  {
    v9 = *(&(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87F8)->nCombatEXP + j);
    v10 = *((_BYTE *)&(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87F8)->dwSkillID[5] + j);
    if ( v9 )
    {
      v11 = (char *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v9) + 28);
    }
    else
    {
      v11 = (char *)&unk_5D89B0;
      v10 = 0;
    }
    switch ( j )
    {
      case 0:
        v12 = GetDlgItem((HWND)dwInitParam, 1075);
        goto LABEL_32;
      case 1:
        v12 = GetDlgItem((HWND)dwInitParam, 1047);
        goto LABEL_32;
      case 2:
        v15 = 1048;
        goto LABEL_31;
      case 3:
        v12 = GetDlgItem((HWND)dwInitParam, 1049);
        goto LABEL_32;
      case 4:
        v12 = GetDlgItem((HWND)dwInitParam, 1050);
        goto LABEL_32;
      case 5:
        v15 = 1051;
LABEL_31:
        v12 = GetDlgItem((HWND)dwInitParam, v15);
LABEL_32:
        hWnd = v12;
        break;
      default:
        break;
    }
    SendMessageA(hWnd, 0xCu, 0, (LPARAM)v11);
    if ( v10 )
      result = SendMessageA(hWnd, 0xF1u, 1u, 0);
    else
      result = SendMessageA(hWnd, 0xF1u, 0, 0);
  }
  return result;
}

// 0x004E3D90
void CCBUI::InitUI_4E3D90()
{
  CCBUI *v1; // ebx
  HWND DlgItem; // edi
  void *v3; // ebp
  HWND v4; // eax
  bool v5; // bl
  char v6; // bl
  int j; // edi
  int v8; // ebp
  HWND v9; // eax
  int v10; // [esp-0x4] [ebp-0x28]
  int v11; // [esp-0x4] [ebp-0x28]
  bool v12; // [esp+0x13] [ebp-0x11]
  HWND hWnd; // [esp+0x14] [ebp-0x10]
  int i; // [esp+0x18] [ebp-0xC]
  unsigned int nVal; // [esp+0x20] [ebp-0x4]
DlgItem = 0;
  v3 = 0;
  hWnd = 0;
  for ( i = 0; i < 8; ++i )
  {
    nVal = (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87FC)->dwSkillID[8 * g_nCCBUI_17A9940
                                                                                              + 7
                                                                                              + i];
    (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87FC);
    (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87FC);
    if ( nVal )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nVal);
      switch ( i )
      {
        case 0:
          DlgItem = GetDlgItem((HWND)dwInitParam, 1052);
          v4 = GetDlgItem((HWND)dwInitParam, 1102);
          goto LABEL_13;
        case 1:
          DlgItem = GetDlgItem((HWND)dwInitParam, 1054);
          v10 = 1103;
          goto LABEL_12;
        case 2:
          DlgItem = GetDlgItem((HWND)dwInitParam, 1055);
          v4 = GetDlgItem((HWND)dwInitParam, 1105);
          goto LABEL_13;
        case 3:
          DlgItem = GetDlgItem((HWND)dwInitParam, 1056);
          v4 = GetDlgItem((HWND)dwInitParam, 1106);
          goto LABEL_13;
        case 4:
          DlgItem = GetDlgItem((HWND)dwInitParam, 1057);
          v10 = 1107;
          goto LABEL_12;
        case 5:
          DlgItem = GetDlgItem((HWND)dwInitParam, 1058);
          v4 = GetDlgItem((HWND)dwInitParam, 1109);
          goto LABEL_13;
        case 6:
          DlgItem = GetDlgItem((HWND)dwInitParam, 1060);
          v4 = GetDlgItem((HWND)dwInitParam, 1110);
          goto LABEL_13;
        case 7:
          DlgItem = GetDlgItem((HWND)dwInitParam, 1061);
          v10 = 1112;
LABEL_12:
          v4 = GetDlgItem((HWND)dwInitParam, v10);
LABEL_13:
          v3 = v4;
          break;
        default:
          break;
      }
      v5 = SendMessageA(DlgItem, 0xF0u, 0, 0) == 1;
      *((_BYTE *)&(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87FC)->dwMagicID[7][2 * g_nCCBUI_17A9940 + 1]
      + i) = v5;
      SendMessageA(v3, 0xDu, 2u, (LPARAM)&g_CCBStageCamBuffer);
      v6 = atoi((const char *)&g_CCBStageCamBuffer) - 1;
      (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87FC)->bMagicMastered[8][8 * g_nCCBUI_17A9940 + 4 + i] = v6;
}
  }
  for ( j = 0; j < 6; ++j )
  {
    v8 = *(&(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87FC)->nCombatEXP + j);
    (((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87FC);
    if ( v8 )
    {
      switch ( j )
      {
        case 0:
          v9 = GetDlgItem((HWND)dwInitParam, 1075);
          goto LABEL_26;
        case 1:
          v9 = GetDlgItem((HWND)dwInitParam, 1047);
          goto LABEL_26;
        case 2:
          v11 = 1048;
          goto LABEL_25;
        case 3:
          v9 = GetDlgItem((HWND)dwInitParam, 1049);
          goto LABEL_26;
        case 4:
          v9 = GetDlgItem((HWND)dwInitParam, 1050);
          goto LABEL_26;
        case 5:
          v11 = 1051;
LABEL_25:
          v9 = GetDlgItem((HWND)dwInitParam, v11);
LABEL_26:
          hWnd = v9;
          break;
        default:
          break;
      }
      v12 = SendMessageA(hWnd, 0xF0u, 0, 0) == 1;
      *((_BYTE *)&(((CCBRoleState *)this->m_fontcolor.Color))->CCBRoleState::InitUI(unk_5D87FC)->dwSkillID[5] + j) = v12;
    }
  }
}

// 0x004E4A80
LRESULT CCBUI::PopulateCommandList()
{
  HWND DlgItem; // ebx
  LPARAM v2; // ebp
  int *TargetRole; // eax
  int v4; // edi
  int SkillNum; // eax
  int ItemPrice; // eax
  int ItemWeight; // eax
  int ItemData; // eax
  int v10; // [esp-0x4] [ebp-0x17C]
  int SlotCount; // [esp+0x14] [ebp-0x164]
  HWND v13; // [esp+0x18] [ebp-0x160]
  HWND v14; // [esp+0x1C] [ebp-0x15C]
  HWND v15; // [esp+0x20] [ebp-0x158]
  HWND v16; // [esp+0x24] [ebp-0x154]
  HWND v17; // [esp+0x28] [ebp-0x150]
  HWND v18; // [esp+0x2C] [ebp-0x14C]
  HWND hWnd; // [esp+0x30] [ebp-0x148]
  HWND v20; // [esp+0x34] [ebp-0x144]
  LPARAM lParam[11]; // [esp+0x38] [ebp-0x140] BYREF
  int v22; // [esp+0x64] [ebp-0x114]
  int v23; // [esp+0x68] [ebp-0x110]
  char pOut[12]; // [esp+0x6C] [ebp-0x10C] BYREF
  char Buffer[256]; // [esp+0x78] [ebp-0x100] BYREF

  DlgItem = GetDlgItem((HWND)g_hCombatDlg2, 1142);
  GetDlgItem((HWND)g_hCombatDlg2, 1146);
  hWnd = GetDlgItem((HWND)g_hCombatDlg2, 1040);
  v15 = GetDlgItem((HWND)g_hCombatDlg2, 1149);
  v18 = GetDlgItem((HWND)g_hCombatDlg2, 1086);
  v17 = GetDlgItem((HWND)g_hCombatDlg2, 1145);
  v13 = GetDlgItem((HWND)g_hCombatDlg2, 1143);
  v20 = GetDlgItem((HWND)g_hCombatDlg2, 1144);
  v14 = GetDlgItem((HWND)g_hCombatDlg2, 1147);
  v16 = GetDlgItem((HWND)g_hCombatDlg2, 1148);
  SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
  (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillID();
  v2 = 0;
  memset(lParam, 0, 0x28u);
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  lParam[0] = 1;
  lParam[2] = 0;
  lParam[5] = (LPARAM)Buffer;
  if ( SlotCount > 0 )
  {
    do
    {
      TargetRole = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
      v4 = (unsigned long)*TargetRole;
      v10 = (unsigned long)*TargetRole;
      v22 = (unsigned long)TargetRole[1];
      v23 = (unsigned long)TargetRole[2];
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v10);
      sprintf(Buffer, "%s", SkillNum + 4);
      lParam[1] = v2;
      lParam[2] = 0;
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf(Buffer, (const char *)&dir[20], v22);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 2;
      ItemPrice = (((PAL_GDB *)this))->PAL_GDB::GetItemPrice(v4);
      sprintf(Buffer, (const char *)&dir[20], ItemPrice);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 3;
      ItemWeight = (((PAL_GDB *)this))->PAL_GDB::GetItemWeight(v4);
      sprintf(Buffer, (const char *)&dir[20], ItemWeight);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 4;
      ItemData = (((PAL_GDB *)this))->PAL_GDB::GetItemData(v4);
      sprintf(Buffer, (const char *)&dir[20], ItemData);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v2;
    }
    while ( v2 < SlotCount );
  }
  EnableWindow(hWnd, 0);
  EnableWindow(v15, 0);
  EnableWindow(v18, 0);
  SendMessageA(v17, 0xCu, 0, (LPARAM)unk_C10D38);
  SendMessageA(v13, 0xCu, 0, (LPARAM)unk_C10D38);
  SendMessageA(v20, 0xCu, 0, (LPARAM)unk_C10D38);
  SendMessageA(v14, 0xCu, 0, (LPARAM)unk_C10D38);
  return SendMessageA(v16, 0xCu, 0, (LPARAM)unk_C10D38);
}

// 0x004E4D70
LRESULT CCBUI::ShowCommandDetails()
{
  HWND DlgItem; // edi
  HWND v3; // ebp
  int *TargetRole; // eax
  int v5; // esi
  int SkillNum; // eax
  int ItemPrice; // eax
  int ItemWeight; // eax
  int ItemData; // eax
  HWND v11; // [esp+0x10] [ebp-0x124]
  HWND v12; // [esp+0x14] [ebp-0x120]
  HWND hWnd; // [esp+0x18] [ebp-0x11C]
  int v14; // [esp+0x20] [ebp-0x114]
  char pOut[12]; // [esp+0x28] [ebp-0x10C] BYREF
  char lParam[256]; // [esp+0x34] [ebp-0x100] BYREF

  GetDlgItem((HWND)g_hCombatDlg2, 1142);
  GetDlgItem((HWND)g_hCombatDlg2, 1146);
  DlgItem = GetDlgItem((HWND)g_hCombatDlg2, 1145);
  v3 = GetDlgItem((HWND)g_hCombatDlg2, 1143);
  hWnd = GetDlgItem((HWND)g_hCombatDlg2, 1144);
  v12 = GetDlgItem((HWND)g_hCombatDlg2, 1147);
  v11 = GetDlgItem((HWND)g_hCombatDlg2, 1148);
  TargetRole = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
  v5 = (unsigned long)*TargetRole;
  v14 = (unsigned long)TargetRole[1];
  SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*TargetRole);
  sprintf(lParam, "%s", SkillNum + 4);
  SendMessageA(DlgItem, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, (const char *)&dir[20], v14);
  SendMessageA(v3, 0xCu, 0, (LPARAM)lParam);
  ItemPrice = (((PAL_GDB *)this))->PAL_GDB::GetItemPrice(v5);
  sprintf(lParam, (const char *)&dir[20], ItemPrice);
  SendMessageA(hWnd, 0xCu, 0, (LPARAM)lParam);
  ItemWeight = (((PAL_GDB *)this))->PAL_GDB::GetItemWeight(v5);
  sprintf(lParam, (const char *)&dir[20], ItemWeight);
  SendMessageA(v12, 0xCu, 0, (LPARAM)lParam);
  ItemData = (((PAL_GDB *)this))->PAL_GDB::GetItemData(v5);
  sprintf(lParam, (const char *)&dir[20], ItemData);
  return SendMessageA(v11, 0xCu, 0, (LPARAM)lParam);
}

// 0x004E4F00
int CCBUI::ApplyCommandEdit()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  int *TargetRole; // eax
  int v5; // ebx
  int v6; // ebp
  int v7; // esi
  int result; // eax
  gbColorQuad *i; // edx
  _DWORD *v10; // ecx
  HWND hWnda; // [esp+0x10] [ebp-0x120]
  HWND hWnd; // [esp+0x10] [ebp-0x120]
  int p_DWORD; // [esp+0x14] [ebp-0x11C] BYREF
  int v14; // [esp+0x18] [ebp-0x118]
  int v15; // [esp+0x1C] [ebp-0x114]
  HWND v16; // [esp+0x20] [ebp-0x110]
  char pOut[12]; // [esp+0x24] [ebp-0x10C] BYREF
  char lParam[256]; // [esp+0x30] [ebp-0x100] BYREF

  v14 = 0;
  v15 = 0;
  p_DWORD = 0xFFFF;
  DlgItem = GetDlgItem((HWND)g_hCombatDlg2, 1143);
  v3 = GetDlgItem((HWND)g_hCombatDlg2, 1144);
  hWnda = GetDlgItem((HWND)g_hCombatDlg2, 1147);
  v16 = GetDlgItem((HWND)g_hCombatDlg2, 1148);
  TargetRole = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
  p_DWORD = (unsigned long)*TargetRole;
  v14 = (unsigned long)TargetRole[1];
  v15 = (unsigned long)TargetRole[2];
  (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_DWORD);
  SendMessageA(DlgItem, 0xDu, 0x14u, (LPARAM)lParam);
  v5 = atoi((const char *)lParam);
  SendMessageA(v3, 0xDu, 0x14u, (LPARAM)lParam);
  v6 = atoi((const char *)lParam);
  SendMessageA(hWnda, 0xDu, 0x14u, (LPARAM)lParam);
  hWnd = (HWND)atoi((const char *)lParam);
  SendMessageA(v16, 0xDu, 0x14u, (LPARAM)lParam);
  v7 = atoi((const char *)lParam);
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
  if ( v5 > 0 )
  {
    v14 = v5;
    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&p_DWORD);
  }
  result = 0;
  for ( i = &this->m_wndcolor; ; i += 4 )
  {
    if ( i->Color == p_DWORD )
    {
      v10 = (_DWORD *)((char *)this + 16 * result);
      goto LABEL_10;
    }
    if ( !i->Color )
      break;
    if ( ++result >= 500 )
    {
      LOBYTE(g_bCommandEdited) = 1;
      return result;
    }
  }
  v10 = (_DWORD *)((char *)this + 16 * result);
  v10[2] = p_DWORD;
LABEL_10:
  result = 16 * (result + 1);
  v10[3] = v6;
  *(_DWORD *)((char *)((UIWnd *)this) + result) = hWnd;
  v10[5] = v7;
  LOBYTE(g_bCommandEdited) = 1;
  return result;
}

// 0x004E5170
int CCBUI::ShowSkillDetails()
{
  HWND DlgItem; // edi
  HWND v2; // ebx
  HWND v3; // ebp
  int *TargetRole; // eax
  __int16 *SkillNum; // esi
  HWND hWnd; // [esp+0x10] [ebp-0x120]
  HWND v8; // [esp+0x14] [ebp-0x11C]
  int v9; // [esp+0x1C] [ebp-0x114]
  char pOut[12]; // [esp+0x24] [ebp-0x10C] BYREF
  char lParam[256]; // [esp+0x30] [ebp-0x100] BYREF

  GetDlgItem((HWND)g_hCombatDlg2, 1142);
  GetDlgItem((HWND)g_hCombatDlg2, 1146);
  DlgItem = GetDlgItem((HWND)g_hCombatDlg2, 1145);
  v2 = GetDlgItem((HWND)g_hCombatDlg2, 1143);
  v3 = GetDlgItem((HWND)g_hCombatDlg2, 1144);
  hWnd = GetDlgItem((HWND)g_hCombatDlg2, 1147);
  v8 = GetDlgItem((HWND)g_hCombatDlg2, 1148);
  TargetRole = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
  v9 = (unsigned long)TargetRole[1];
  SkillNum = (__int16 *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*TargetRole);
  sprintf(lParam, "%s", SkillNum + 2);
  SendMessageA(DlgItem, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, (const char *)&dir[20], v9);
  SendMessageA(v2, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, (const char *)&dir[20], SkillNum[322]);
  SendMessageA(v3, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, (const char *)&dir[20], SkillNum[323]);
  SendMessageA(hWnd, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, (const char *)&dir[20], SkillNum[324]);
  return SendMessageA(v8, 0xCu, 0, (LPARAM)lParam);
}

// 0x004E53C0
LRESULT CCBUI::SendWindowMessage(HWND hWnd, LPARAM lParam)
{
  return SendMessageA(hWnd, 0xCu, 0, lParam);
}

// 0x004E53E0
LRESULT CCBUI::FormatCombatBuffer(HWND hWnd, int nVal)
{
  sprintf((char *const)&g_CCBStageCamBuffer, off_5D89BC, nVal);
  return SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
}

// 0x004E5490
int CCBUI::StartMagicThread()
{
  CCBControl *v2; // ecx
  int v3; // edx
  int result; // eax

  (((CCBSystem *)*(CCBSystem **)(*(_DWORD *)((UIWnd *)this) + 12)))->CCBSystem::SetThreadFlag(0);
  (((CCBUI *)*(CCBUI **)(*(_DWORD *)((UIWnd *)this) + 4)))->CCBUI::CreateMagicWindow();
  v2 = (CCBControl *)*(CCBControl **)(*(_DWORD *)((UIWnd *)this) + 8);
  if ( v2->m_bActive )
    (((CCBControl *)v2))->CCBControl::GetState();
  v3 = 0;
  for ( result = 24; result < 68; result += 4 )
  {
    if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 16) + v3 + 577) )
    {
      *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + result) + 280) = 0;
      *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 20) + result) + 274) = 0;
    }
    v3 += 892;
  }
  return result;
}

// 0x004EA4A0
LRESULT CCBUI::_nearby_4ea4a0(HWND hDlg, int a3)
{
  int v4; // esi
  HWND *v5; // edi
  int v6; // ecx
  LPARAM v7; // eax
  LRESULT result; // eax
  _DWORD v9[13]; // [esp+0x10] [ebp-0x34] BYREF

  v9[0] = (unsigned long)GetDlgItem(hDlg, 1264);
  v9[1] = (unsigned long)GetDlgItem(hDlg, 1263);
  v9[2] = (unsigned long)GetDlgItem(hDlg, 1265);
  v9[3] = (unsigned long)GetDlgItem(hDlg, 1266);
  v9[4] = (unsigned long)GetDlgItem(hDlg, 1267);
  v9[5] = (unsigned long)GetDlgItem(hDlg, 1268);
  v9[6] = (unsigned long)GetDlgItem(hDlg, 1269);
  v9[7] = (unsigned long)GetDlgItem(hDlg, 1270);
  v9[8] = (unsigned long)GetDlgItem(hDlg, 1271);
  v9[9] = (unsigned long)GetDlgItem(hDlg, 1272);
  v9[10] = (unsigned long)GetDlgItem(hDlg, 1273);
  v9[11] = (unsigned long)GetDlgItem(hDlg, 1274);
  v9[12] = (unsigned long)GetDlgItem(hDlg, 1275);
  v4 = 0;
  v5 = (HWND *)v9;
  do
  {
    v6 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 44) + 72 * a3 + 96);
    v7 = (*(int ( **)(int, int))(*(_DWORD *)v6 + 40))(v6, v4);
    result = CCBUI::SendWindowMessage(*v5, v7);
    ++v4;
    ++v5;
  }
  while ( v4 < 13 );
  return result;
}

// 0x004EA5C0
int CCBUI::DlgProcCameraEdit(CCBCamControl *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam)
{
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  _BYTE *v10; // edi
  bool v11; // zf
  HWND hWnd; // [esp+0x8] [ebp-0x4]
  HWND hDlga; // [esp+0x14] [ebp+0x8]

  hDlga = GetDlgItem(hDlg, 1225);
  hWnd = GetDlgItem(hDlg, 1226);
  if ( uMsg == 272 )
  {
    v7 = -1;
    if ( a1->m_CamEntries[1405] == -1 )
    {
      v8 = (unsigned long)a1->m_CamEntries[1404];
      if ( v8 != -1 )
      {
        v9 = *(_DWORD *)(*(_DWORD *)a1 + 44) + 72 * v8;
        v10 = (_BYTE *)(v9 + 58);
        do
        {
          if ( !v7 )
            break;
          v11 = *v10++ == 0;
          --v7;
        }
        while ( !v11 );
        if ( -v7 == 2 )
          CCBUI::SendWindowMessage(hDlga, v9 + 28);
        else
          CCBUI::SendWindowMessage(hDlga, v9 + 58);
        EditBoxSetInt(hWnd, a1->m_CamEntries[1404]);
      }
    }
    (((CCBUI *)a1))->CCBUI::_nearby_4ea6d0(hDlg, a1->m_CamEntries[1405]);
  }
  else if ( uMsg == 273 )
  {
    if ( wParam == 1 )
    {
      if ( (((CCBUI *)a1))->CCBUI::_nearby_4eac10(hDlg, a1->m_CamEntries[1405]) )
      {
        (((CCBStageCam *)a1))->CCBStageCam::sub_4E95A0(g_hMainWnd);
        EndDialog(hDlg, 1);
        goto LABEL_8;
      }
    }
    else if ( wParam == 2 )
    {
      EndDialog(hDlg, 2);
LABEL_8:
      g_hCBStageCamDlg = 0;
      return 0;
    }
  }
  return 0;
}

// 0x004EA6D0
char CCBUI::_nearby_4ea6d0(HWND hDlg, int a3)
{
  _DWORD *v4; // ebx
  int EffSlot; // eax
  int v6; // edx
  int v7; // edi
  LRESULT v8; // eax
  BOOL v9; // edx
  BOOL v10; // ecx
  HWND v12; // [esp+0x10] [ebp-0x1A4]
  HWND v13; // [esp+0x14] [ebp-0x1A0]
  HWND v14; // [esp+0x18] [ebp-0x19C]
  HWND v15; // [esp+0x1C] [ebp-0x198]
  HWND v16; // [esp+0x20] [ebp-0x194]
  HWND v17; // [esp+0x24] [ebp-0x190]
  HWND v18; // [esp+0x28] [ebp-0x18C]
  HWND v19; // [esp+0x2C] [ebp-0x188]
  HWND v20; // [esp+0x30] [ebp-0x184]
  HWND v21; // [esp+0x34] [ebp-0x180]
  HWND v22; // [esp+0x38] [ebp-0x17C]
  HWND v23; // [esp+0x3C] [ebp-0x178]
  HWND v24; // [esp+0x40] [ebp-0x174]
  HWND v25; // [esp+0x44] [ebp-0x170]
  HWND v26; // [esp+0x48] [ebp-0x16C]
  HWND v27; // [esp+0x4C] [ebp-0x168]
  HWND v28; // [esp+0x50] [ebp-0x164]
  HWND v29; // [esp+0x54] [ebp-0x160]
  HWND DlgItem; // [esp+0x58] [ebp-0x15C]
  HWND v31; // [esp+0x5C] [ebp-0x158]
  HWND hWnd; // [esp+0x60] [ebp-0x154]
  HWND v33; // [esp+0x64] [ebp-0x150]
  HWND v34; // [esp+0x68] [ebp-0x14C]
  HWND v35; // [esp+0x6C] [ebp-0x148]
  HWND v36; // [esp+0x70] [ebp-0x144]
  HWND v37; // [esp+0x74] [ebp-0x140]
  HWND v38; // [esp+0x78] [ebp-0x13C]
  HWND v39; // [esp+0x7C] [ebp-0x138]
  HWND v40; // [esp+0x80] [ebp-0x134]
  HWND v41; // [esp+0x84] [ebp-0x130]
  HWND v42; // [esp+0x88] [ebp-0x12C]
  HWND v43; // [esp+0x8C] [ebp-0x128]
  HWND v44; // [esp+0x90] [ebp-0x124]
  HWND v45; // [esp+0x94] [ebp-0x120]
  HWND v46; // [esp+0x98] [ebp-0x11C]
  _DWORD v47[70]; // [esp+0x9C] [ebp-0x118] BYREF

  DlgItem = GetDlgItem(hDlg, 1225);
  v14 = GetDlgItem(hDlg, 1226);
  v16 = GetDlgItem(hDlg, 1207);
  v46 = GetDlgItem(hDlg, 1206);
  v18 = GetDlgItem(hDlg, 1227);
  hWnd = GetDlgItem(hDlg, 1228);
  v40 = GetDlgItem(hDlg, 1248);
  v20 = GetDlgItem(hDlg, 1229);
  v21 = GetDlgItem(hDlg, 1216);
  v19 = GetDlgItem(hDlg, 1217);
  v17 = GetDlgItem(hDlg, 1221);
  v42 = GetDlgItem(hDlg, 1218);
  v28 = GetDlgItem(hDlg, 1219);
  v38 = GetDlgItem(hDlg, 1220);
  v12 = GetDlgItem(hDlg, 1244);
  v13 = GetDlgItem(hDlg, 1245);
  v15 = GetDlgItem(hDlg, 1230);
  v26 = GetDlgItem(hDlg, 1222);
  v34 = GetDlgItem(hDlg, 1232);
  v22 = GetDlgItem(hDlg, 1231);
  v44 = GetDlgItem(hDlg, 1233);
  v24 = GetDlgItem(hDlg, 1234);
  v36 = GetDlgItem(hDlg, 1224);
  v23 = GetDlgItem(hDlg, 1223);
  v25 = GetDlgItem(hDlg, 1235);
  v27 = GetDlgItem(hDlg, 1236);
  v29 = GetDlgItem(hDlg, 1237);
  v31 = GetDlgItem(hDlg, 1247);
  v33 = GetDlgItem(hDlg, 1238);
  v35 = GetDlgItem(hDlg, 1239);
  v37 = GetDlgItem(hDlg, 1240);
  v39 = GetDlgItem(hDlg, 1241);
  v41 = GetDlgItem(hDlg, 1242);
  v43 = GetDlgItem(hDlg, 1243);
  v45 = GetDlgItem(hDlg, 1246);
  v4 = v47;
  if ( a3 == -1 )
  {
    EffSlot = (int)this[3].m_pAttackSequenFace[3];
    if ( EffSlot == -1 )
      return EffSlot;
    v6 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 44) + 72 * EffSlot + 92);
    memset(v47, 0, sizeof(v47));
    v47[51] = -1;
    v47[42] = 1;
    v47[43] = 1;
    v47[44] = 1;
    v47[50] = 1065353216;
  }
  else
  {
    v4 = (_DWORD *)(280 * a3 + 24433456);
    LOBYTE(EffSlot) = g_EffTable[280 * a3 + 212];
    if ( !(_BYTE)EffSlot )
      return EffSlot;
    v6 = *(_DWORD *)&g_EffTable[280 * a3];
  }
  EffSlot = (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)((UIWnd *)this) + 44)))->CEffMgr::FindEffSlot(v6);
  v7 = EffSlot;
  if ( EffSlot != -1 )
  {
    this->CCBUI::_nearby_4ea4a0(hDlg, EffSlot);
    CCBUI::SendWindowMessage(DlgItem, *(_DWORD *)(*(_DWORD *)((UIWnd *)this) + 44) + 72 * v7 + 28);
    EditBoxSetInt(v14, v7);
    CCBUI::SendWindowMessage(v46, (LPARAM)(v4 + 10));
    v8 = CCBUI::SendWindowMessage(v16, (LPARAM)(v4 + 1));
    LOBYTE(v8) = *((_BYTE *)v4 + 213);
    EditBoxSetReadOnly(hWnd, v8);
    LOBYTE(v9) = *((_BYTE *)v4 + 214);
    EditBoxSetReadOnly(v18, v9);
    LOBYTE(v10) = *((_BYTE *)v4 + 215);
    EditBoxSetReadOnly(v40, v10);
    EditBoxSetInt(v20, v4[52]);
    CCBUI::FormatCombatBuffer(v34, HIBYTE(v4[51]));
    CCBUI::FormatCombatBuffer(v22, *((unsigned __int8 *)v4 + 206));
    CCBUI::FormatCombatBuffer(v44, *((unsigned __int8 *)v4 + 205));
    CCBUI::FormatCombatBuffer(v24, (unsigned __int8)v4[51]);
    EditBoxSetFloat(v36, *((float *)v4 + 45));
    EditBoxSetFloat(v26, *((float *)v4 + 50));
    EditBoxSetFloat(v42, *((float *)v4 + 46));
    EditBoxSetFloat(v28, *((float *)v4 + 47));
    EditBoxSetFloat(v38, *((float *)v4 + 48));
    EditBoxSetFloat(v12, *((float *)v4 + 54));
    EditBoxSetFloat(v13, *((float *)v4 + 49));
    EditBoxSetFloat(v15, *((float *)v4 + 55));
    EditBoxSetInt(v17, v4[44]);
    EditBoxSetInt(v19, v4[43]);
    EditBoxSetInt(v21, v4[42]);
    EditBoxSetFloat(v23, *((float *)v4 + 56));
    EditBoxSetFloat(v25, *((float *)v4 + 57));
    EditBoxSetFloat(v27, *((float *)v4 + 58));
    EditBoxSetFloat(v29, *((float *)v4 + 59));
    EditBoxSetFloat(v31, *((float *)v4 + 60));
    EditBoxSetFloat(v33, *((float *)v4 + 61));
    EditBoxSetFloat(v35, *((float *)v4 + 62));
    EditBoxSetFloat(v37, *((float *)v4 + 63));
    EditBoxSetFloat(v39, *((float *)v4 + 64));
    EditBoxSetFloat(v41, *((float *)v4 + 65));
    EditBoxSetFloat(v43, *((float *)v4 + 66));
    LOBYTE(EffSlot) = EditBoxSetFloat(v45, *((float *)v4 + 67));
  }
  return EffSlot;
}

// 0x004EAC10
char CCBUI::_nearby_4eac10(HWND hDlg, int a3)
{
  HWND v3; // ebx
  HWND v4; // ebp
  char *EditBoxText; // eax
  int v6; // esi
  int v7; // edi
  int v8; // ebx
  const char *v9; // eax
  int v10; // edi
  char *v11; // ecx
  UIStatic *v12; // ecx
  char *v13; // eax
  const char *v15; // ebx
  const char *v16; // eax
  int *v17; // esi
  int v18; // edx
  const char **v19; // ecx
  HWND v21; // [esp+0x14] [ebp-0x198]
  HWND v22; // [esp+0x18] [ebp-0x194]
  HWND v23; // [esp+0x1C] [ebp-0x190]
  HWND DlgItem; // [esp+0x20] [ebp-0x18C]
  HWND v25; // [esp+0x24] [ebp-0x188]
  HWND v26; // [esp+0x28] [ebp-0x184]
  HWND v27; // [esp+0x2C] [ebp-0x180]
  HWND v28; // [esp+0x30] [ebp-0x17C]
  HWND v29; // [esp+0x34] [ebp-0x178]
  HWND v30; // [esp+0x38] [ebp-0x174]
  HWND v31; // [esp+0x3C] [ebp-0x170]
  HWND v32; // [esp+0x40] [ebp-0x16C]
  HWND v33; // [esp+0x44] [ebp-0x168]
  HWND v34; // [esp+0x48] [ebp-0x164]
  HWND v35; // [esp+0x4C] [ebp-0x160]
  HWND v36; // [esp+0x50] [ebp-0x15C]
  HWND v37; // [esp+0x54] [ebp-0x158]
  HWND v38; // [esp+0x58] [ebp-0x154]
  HWND v39; // [esp+0x5C] [ebp-0x150]
  HWND v40; // [esp+0x60] [ebp-0x14C]
  HWND v41; // [esp+0x64] [ebp-0x148]
  HWND v42; // [esp+0x68] [ebp-0x144]
  HWND v43; // [esp+0x6C] [ebp-0x140]
  HWND v44; // [esp+0x70] [ebp-0x13C]
  HWND v45; // [esp+0x74] [ebp-0x138]
  HWND v46; // [esp+0x78] [ebp-0x134]
  HWND v47; // [esp+0x7C] [ebp-0x130]
  HWND v48; // [esp+0x80] [ebp-0x12C]
  HWND v49; // [esp+0x84] [ebp-0x128]
  HWND v50; // [esp+0x88] [ebp-0x124]
  HWND v51; // [esp+0x8C] [ebp-0x120]
  HWND hWnd; // [esp+0x90] [ebp-0x11C]
  const char *EditorTaskDescription; // [esp+0x94] [ebp-0x118] BYREF
  char nIndex[36]; // [esp+0x98] [ebp-0x114] BYREF
  char v55[128]; // [esp+BCh] [ebp-F0h] BYREF
  int v56; // [esp+0x13C] [ebp-0x70]
  int v57; // [esp+0x140] [ebp-0x6C]
  int v58; // [esp+0x144] [ebp-0x68]
  float Float; // [esp+0x148] [ebp-0x64]
  float v60; // [esp+0x14C] [ebp-0x60]
  float v61; // [esp+0x150] [ebp-0x5C]
  float v62; // [esp+0x154] [ebp-0x58]
  float v63; // [esp+0x158] [ebp-0x54]
  float v64; // [esp+0x15C] [ebp-0x50]
  int v65; // [esp+0x160] [ebp-0x4C]
  int Int; // [esp+0x164] [ebp-0x48]
  char v67; // [esp+0x168] [ebp-0x44]
  bool IsModified; // [esp+0x169] [ebp-0x43]
  bool v69; // [esp+0x16A] [ebp-0x42]
  bool v70; // [esp+0x16B] [ebp-0x41]
  float v71; // [esp+0x16C] [ebp-0x40]
  float v72; // [esp+0x170] [ebp-0x3C]
  float v73; // [esp+0x174] [ebp-0x38]
  float v74; // [esp+0x178] [ebp-0x34]
  float v75; // [esp+0x17C] [ebp-0x30]
  float v76; // [esp+0x180] [ebp-0x2C]
  float v77; // [esp+0x184] [ebp-0x28]
  float v78; // [esp+0x188] [ebp-0x24]
  float v79; // [esp+0x18C] [ebp-0x20]
  float v80; // [esp+0x190] [ebp-0x1C]
  float v81; // [esp+0x194] [ebp-0x18]
  float v82; // [esp+0x198] [ebp-0x14]
  float v83; // [esp+0x19C] [ebp-0x10]
  float v84; // [esp+0x1A0] [ebp-0xC]

  DlgItem = GetDlgItem(hDlg, 1225);
  v51 = GetDlgItem(hDlg, 1207);
  v49 = GetDlgItem(hDlg, 1206);
  v3 = GetDlgItem(hDlg, 1227);
  v4 = GetDlgItem(hDlg, 1228);
  hWnd = GetDlgItem(hDlg, 1248);
  v38 = GetDlgItem(hDlg, 1229);
  v23 = GetDlgItem(hDlg, 1216);
  v22 = GetDlgItem(hDlg, 1217);
  v21 = GetDlgItem(hDlg, 1221);
  v42 = GetDlgItem(hDlg, 1218);
  v32 = GetDlgItem(hDlg, 1219);
  v48 = GetDlgItem(hDlg, 1220);
  v34 = GetDlgItem(hDlg, 1244);
  v44 = GetDlgItem(hDlg, 1245);
  v36 = GetDlgItem(hDlg, 1230);
  v30 = GetDlgItem(hDlg, 1222);
  v46 = GetDlgItem(hDlg, 1232);
  v26 = GetDlgItem(hDlg, 1231);
  v40 = GetDlgItem(hDlg, 1233);
  v28 = GetDlgItem(hDlg, 1234);
  v50 = GetDlgItem(hDlg, 1224);
  v25 = GetDlgItem(hDlg, 1223);
  v27 = GetDlgItem(hDlg, 1235);
  v29 = GetDlgItem(hDlg, 1236);
  v31 = GetDlgItem(hDlg, 1237);
  v33 = GetDlgItem(hDlg, 1247);
  v35 = GetDlgItem(hDlg, 1238);
  v37 = GetDlgItem(hDlg, 1239);
  v39 = GetDlgItem(hDlg, 1240);
  v41 = GetDlgItem(hDlg, 1241);
  v43 = GetDlgItem(hDlg, 1242);
  v45 = GetDlgItem(hDlg, 1243);
  v47 = GetDlgItem(hDlg, 1246);
  IsModified = EditBoxIsModified(v4);
  v69 = EditBoxIsModified(v3);
  v70 = EditBoxIsModified(hWnd);
  Int = EditBoxGetInt(v38);
  v67 = 1;
  if ( (byte_1895559 & 1) == 0 )
  {
    LOBYTE(byte_1895559) = byte_1895559 | 1;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  EditBoxText = GetEditBoxText(DlgItem);
  EditorTaskDescription = (((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)EditBoxText);
  v6 = EditBoxGetInt(v46) << 24;
  v7 = EditBoxGetInt(v26) << 16;
  v8 = EditBoxGetInt(v40) << 8;
  v65 = v6 | v7 | v8 | EditBoxGetInt(v28);
  Float = EditBoxGetFloat(v50);
  v64 = EditBoxGetFloat(v30);
  v60 = EditBoxGetFloat(v42);
  v61 = EditBoxGetFloat(v32);
  v62 = EditBoxGetFloat(v48);
  v71 = EditBoxGetFloat(v34);
  v63 = EditBoxGetFloat(v44);
  v72 = EditBoxGetFloat(v36);
  v58 = EditBoxGetInt(v21);
  v57 = EditBoxGetInt(v22);
  v56 = EditBoxGetInt(v23);
  v73 = EditBoxGetFloat(v25);
  v74 = EditBoxGetFloat(v27);
  v75 = EditBoxGetFloat(v29);
  v76 = EditBoxGetFloat(v31);
  v77 = EditBoxGetFloat(v33);
  v78 = EditBoxGetFloat(v35);
  v79 = EditBoxGetFloat(v37);
  v80 = EditBoxGetFloat(v39);
  v81 = EditBoxGetFloat(v41);
  v82 = EditBoxGetFloat(v43);
  v83 = EditBoxGetFloat(v45);
  v84 = EditBoxGetFloat(v47);
  strcpy((char *)v55, GetEditBoxText(v49));
  strcpy((char *)nIndex, GetEditBoxText(v51));
  if ( (byte_1895559 & 1) == 0 )
  {
    LOBYTE(byte_1895559) = byte_1895559 | 1;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  v9 = (((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)nIndex);
  v10 = a3;
  if ( a3 == -1 )
  {
    v11 = (char *)&g_EffTable[36];
    do
    {
      if ( v11[176] && *(const char **)v11 == v9 )
      {
        MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8BE4, Caption, 0);
        return 0;
      }
      v11 += 280;
    }
    while ( (int)v11 < (int)((char *)&g_17A7BData.m_nEffParam1C + 4) );
    v12 = 0;
    v13 = (char *)&g_EffTable[212];
    while ( *v13 )
    {
      v13 += 280;
      v12 = (UIStatic *)((char *)v12 + 1);
      if ( (int)v13 >= (int)&g_EffTaskEnd )
        return 0;
    }
    v10 = (int)v12;
    this[3].m_pAttackSequenFace[4] = v12;
  }
  else
  {
    v15 = (const char *)(*(const char **)&g_EffTable[280 * a3 + 36]);
    if ( (byte_1895559 & 1) == 0 )
    {
      LOBYTE(byte_1895559) = byte_1895559 | 1;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v16 = (((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)nIndex);
    if ( v16 != v15 )
    {
      v17 = (int *)&g_nSaveSlot1;
      do
      {
        v18 = *(v17 - 1);
        if ( v18 > 0 )
        {
          v19 = (const char **)v17;
          do
          {
            if ( *v19 == v15 )
              *v19 = v16;
            ++v19;
            --v18;
          }
          while ( v18 );
        }
        v17 += 3985;
      }
      while ( (int)v17 < (int)&g_EffTable[4] );
    }
  }
  if ( v10 == -1 )
    return 0;
  sub_4CE030(&EditorTaskDescription, v10);
  return 1;
}

// 0x004EB230
INT_PTR CCBUI::_nearby_4eb230(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  return (((CCBUI *)pfVal))->CCBUI::DlgProcCameraConfig(hDlg, a2, a3, a4);
}

// 0x004EB260
int CCBUI::DlgProcCameraConfig(CCBCamControl *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam)
{
  HWND v5; // edi
  HWND DlgItem; // ebp
  HWND v7; // ebx
  int v8; // eax
  int v9; // eax
  LRESULT v11; // eax
  LRESULT v12; // eax
  int v13; // eax
  int v14; // eax
  LPARAM lParama[8]; // [esp+0x10] [ebp-0x20] BYREF

  v5 = hDlg;
  DlgItem = GetDlgItem(hDlg, 1276);
  v7 = GetDlgItem(hDlg, 1278);
  if ( uMsg != 78 )
  {
    if ( uMsg == 272 )
    {
      SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
      v11 = SendMessageA(DlgItem, 0x1037u, 0, 0);
      LOBYTE(v11) = v11 | 0x21;
      SendMessageA(DlgItem, 0x1036u, 0, v11);
      memset(lParama, 0, sizeof(lParama));
      lParama[0] = 7;
      lParama[1] = 0;
      lParama[2] = 30;
      lParama[3] = (LPARAM)&unk_5D8A58;
      SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 42;
      lParama[3] = (LPARAM)&unk_5D8B04;
      SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 86;
      lParama[3] = (LPARAM)&unk_5D8C14;
      SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)lParama);
      v12 = SendMessageA(v7, 0x1037u, 0, 0);
      LOBYTE(v12) = v12 | 0x21;
      SendMessageA(v7, 0x1036u, 0, v12);
      lParama[0] = 7;
      lParama[1] = 0;
      lParama[2] = 30;
      lParama[3] = (LPARAM)&unk_5D8A58;
      SendMessageA(v7, 0x101Bu, 0, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 108;
      lParama[3] = (LPARAM)&unk_5D8C0C;
      SendMessageA(v7, 0x101Bu, 1u, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 30;
      lParama[3] = (LPARAM)&unk_5D8C08;
      SendMessageA(v7, 0x101Bu, 2u, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 30;
      lParama[3] = (LPARAM)&unk_5D8C04;
      SendMessageA(v7, 0x101Bu, 3u, (LPARAM)lParama);
      return 0;
    }
    if ( uMsg != 273 )
      return 0;
    switch ( wParam )
    {
      case 0x41Fu:
        sub_4CE5C0(*(_DWORD *)(*(_DWORD *)a1 + 44));
        break;
      case 0x421u:
        if ( a1->m_CamEntries[1793] != -1 )
        {
          (((CEffect *)*(CEffect **)(*(_DWORD *)a1 + 44)))->CEffect::Render(a1->m_CamEntries[1793]);
          (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)a1 + 44)))->CEffMgr::Init(a1->m_CamEntries[1793], 0, 0, 0, 0);
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 44) + 43304) = 0;
        }
        break;
      case 0x4BAu:
        (((CCBStageEffect *)*(CCBStageEffect **)(*(_DWORD *)(*(_DWORD *)a1 + 20) + 76)))->CCBStageEffect::~CCBStageEffect();
        break;
      case 0x4BBu:
        if ( MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8B14, &unk_5D8B3C, 1u) == 1 )
        {
          *(CCBStageEffect **)(*(_DWORD *)(*(_DWORD *)a1 + 20) + 76)->CCBStageEffect::CCBStageEffect();
          (((CCBCamControl *)a1))->CCBCamControl::sub_4EB6F0(hDlg);
        }
        v5 = hDlg;
        break;
      case 0x4D0u:
        if ( a1->m_nCurCamIdx == -1 )
        {
          MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8C20, aWarning, 0);
        }
        else
        {
          (((CCBCamControl *)a1))->CCBCamControl::ReadCameraDialog(hDlg);
          (((CCBCamControl *)a1))->CCBCamControl::sub_4EB8D0(hDlg);
        }
        break;
      case 0x4D5u:
        (((CEffMgr *)*(CEffMgr **)(*(_DWORD *)a1 + 44)))->CEffMgr::ReleaseCompletedEffects();
        break;
      case 0x508u:
        (((PAL_GDB *)a1))->PAL_GDB::ShowDetailPanel(hDlg);
        break;
      default:
        break;
    }
  }
  if ( wParam == 1276 )
  {
    v13 = *(_DWORD *)(lParam + 8);
    if ( v13 == -3 || v13 == -2 )
    {
      v14 = *(_DWORD *)(lParam + 12);
      if ( v14 != -1 )
      {
        a1->m_CamEntries[1793] = v14;
        return 0;
      }
      a1->m_CamEntries[1793] = -1;
    }
    return 0;
  }
  if ( wParam != 1278 )
    return 0;
  v8 = *(_DWORD *)(lParam + 8);
  if ( v8 != -3 && v8 != -2 )
    return 0;
  v9 = *(_DWORD *)(lParam + 12);
  if ( v9 == -1 )
  {
    a1->m_nCurCamIdx = -1;
  }
  else
  {
    a1->m_nCurCamIdx = v9;
    (((CCBCamControl *)a1))->CCBCamControl::ShowCameraDialog(v5);
  }
  return 0;
}

// 0x005160A0
void CCBUI::_todo_5160A0(int nVal)
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  sub_516170(this);
  this->m_pSkillWindow = ((CCBSkillWindow *)((CCBSkillWindow *)nVal));
}

// 0x00517650
CCBUI::~CCBUI()
{
  UIFrameContainer *v2; // eax
  UIStatic *v3; // eax
  int *v4; // esi
  UIPushButton **p_pPanel; // edi
  UIFrameContainer *v6; // eax
  UIPushButton *v7; // eax
  int v8; // [esp+0x10] [ebp-0x1C] BYREF
  int v9; // [esp+0x14] [ebp-0x18]
  int v10; // [esp+0x18] [ebp-0x14]
  int v11; // [esp+0x1C] [ebp-0x10]
  int v12; // [esp+0x28] [ebp-0x4]

  v2 = (UIFrameContainer *)operator new(0x98u);
  v12 = 0;
  if ( v2 )
    (((UIFrameContainer *)v2))->UIFrameContainer::ResetContainerState();
  else
    v3 = 0;
  v12 = -1;
  this->m_pAttackSequenBack = ((UIStatic *)(v3));
  if ( v3 )
  {
    v8 = 483;
    v9 = 10;
    v10 = 803;
    v11 = 42;
    (*(void (**)(UIStatic *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v3) + 16))(v3, 1, &v8, this);
    (((UIPushButton *)this->m_pAttackSequenBack))->UIPushButton::CreateFromTemplate(&unk_5DF2C0, 0);
    v8 = 480;
    v10 = 544;
    v9 = 8;
    v11 = 72;
    v4 = (int *)&g_nSkillItemIDTable[5];
    p_pPanel = (UIPushButton **)&this->pPanel;
    do
    {
      v6 = (UIFrameContainer *)operator new(0x98u);
      v12 = 1;
      if ( v6 )
        (((UIFrameContainer *)v6))->UIFrameContainer::ResetContainerState();
      else
        v7 = 0;
      v12 = -1;
      *p_pPanel = v7;
      if ( !v7 )
        break;
      (*(void (**)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v7) + 16))(v7, *v4, &v8, this);
      (((UIPushButton *)*p_pPanel))->UIPushButton::CreateFromTemplate(&unk_5DF2A0, 0);
      ++v4;
      ++p_pPanel;
    }
    while ( (int)v4 < (int)&g_nSkillItemIDTable[16] );
  }
}

// 0x005177B0
void CCBUI::Reset()
{
  UIPushButton *v2; // eax
  UIProgressBar *v3; // eax
  UIPushButton *v4; // eax
  UIProgressBar *v5; // eax
  UIFrameContainer *v6; // eax
  UIProgressBar *v7; // eax
  UIProgressBar *v8; // ecx
  UIProgressBar *v9; // ecx
  int v10; // [esp+0x30] [ebp-0x820] BYREF
  int v11; // [esp+0x34] [ebp-0x81C]
  int v12; // [esp+0x38] [ebp-0x818]
  int v13; // [esp+0x3C] [ebp-0x814]
  void *v14; // [esp+0x40] [ebp-0x810]
  char pExceptionObject[1024]; // [esp+0x44] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x444] [ebp-0x40C] BYREF
  int v17; // [esp+0x84C] [ebp-0x4]

  v2 = (UIPushButton *)operator new(0x9Cu);
  v14 = (void *)v2;
  v17 = 0;
  if ( v2 )
    v3 = (UIProgressBar *)(((UIPushButton *)v2))->UIPushButton::CtorWithFlag();
  else
    v3 = 0;
  this->m_pRoleStateGP[2] = v3;
  v4 = (UIPushButton *)operator new(0x9Cu);
  v14 = (void *)v4;
  v17 = 1;
  if ( v4 )
    v5 = (UIProgressBar *)(((UIPushButton *)v4))->UIPushButton::CtorWithFlag();
  else
    v5 = 0;
  this->m_pRoleStateGP[3] = v5;
  v6 = (UIFrameContainer *)operator new(0x98u);
  v14 = (void *)v6;
  v17 = 2;
  if ( v6 )
    (((UIFrameContainer *)v6))->UIFrameContainer::ResetContainerState();
  else
    v7 = 0;
  v8 = (UIProgressBar *)this->m_pRoleStateGP[2];
  v17 = -1;
  this->m_pRoleStateMP[0] = v7;
  if ( !v8 || !this->m_pRoleStateGP[3] || !v7 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 719),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = 300;
  v11 = 30;
  v12 = 461;
  v13 = 87;
  (*(void ( **)(UIProgressBar *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v8) + 16))(v8, 784, &v10, this);
  (((UIPushButton *)this->m_pRoleStateGP[2]))->UIPushButton::CreateFromTemplate(&unk_5DEFD4, 0);
  (((UIScene *)this->m_pRoleStateGP[2]))->UIScene::SetShow(1);
  AllocObject(this->m_pRoleStateGP[2]);
  (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)this->m_pRoleStateGP[2]))((UIProgressBar *)(this->m_pRoleStateGP[2]), (_DWORD)(0));
  (*(void ( **)(UIProgressBar *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)this->m_pRoleStateGP[3]) + 16))(
    this->m_pRoleStateGP[3],
    784,
    &v10,
    this);
  (((UIPushButton *)this->m_pRoleStateGP[3]))->UIPushButton::CreateFromTemplate(&unk_5DEFB4, 0);
  (((UIScene *)this->m_pRoleStateGP[3]))->UIScene::SetShow(1);
  AllocObject(this->m_pRoleStateGP[3]);
  (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)this->m_pRoleStateGP[3]))((UIProgressBar *)(this->m_pRoleStateGP[3]), (_DWORD)(0));
  v9 = (UIProgressBar *)this->m_pRoleStateMP[0];
  v10 = 100;
  v11 = 100;
  v12 = 356;
  v13 = 228;
  (*(void ( **)(UIProgressBar *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v9) + 16))(v9, 1024, &v10, this);
  (((UIPushButton *)this->m_pRoleStateMP[0]))->UIPushButton::CreateFromTemplate(&unk_5DEF9C, 0);
  (((UIScene *)this->m_pRoleStateMP[0]))->UIScene::SetShow(1);
  AllocObject(this->m_pRoleStateMP[0]);
  (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)this->m_pRoleStateMP[0]))((UIProgressBar *)(this->m_pRoleStateMP[0]), (_DWORD)(0));
  (((UIFrameWnd *)this->m_pRoleStateMP[0]))->UIFrameWnd::SetPosition(5,   63);
  (((UIFrameWnd *)this->m_pRoleStateMP[0]))->UIFrameWnd::SetFrameParam(190);
}

// 0x00517B30
bool CCBUI::CreateCombatPanel()
{
  UIStatic **p_m_pResultWaterLvup; // esi
  bool result; // al
  CCBUI *v4; // ecx
  int v5; // [esp+0x8] [ebp-0x10] BYREF
  int v6; // [esp+0xC] [ebp-0xC]
  int v7; // [esp+0x10] [ebp-0x8]
  int v8; // [esp+0x14] [ebp-0x4]

  p_m_pResultWaterLvup = (UIStatic **)&this->m_pResultWaterLvup;
  result = (((CCBAIWindow *)this))->CCBAIWindow::Update((CCBUI **)&this->m_pResultWaterLvup);
  if ( result )
  {
    v6 = 0;
    v7 = 0;
    v4 = (CCBUI *)*p_m_pResultWaterLvup;
    v5 = 2;
    v7 = 251;
    v6 = 278;
    v8 = 484;
    (((CCBUI *)v4))->CCBUI::AddTask((tagUITask *)&v5, (int)this);
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)(*p_m_pResultWaterLvup)))((UIStatic *)(*p_m_pResultWaterLvup), (_DWORD)(0));
    return 1;
  }
  return result;
}

// 0x00517C10
bool CCBUI::CreateAttackSequen()
{
  UIStatic **p_m_pResultEarthLvup; // esi
  bool result; // al
  CCBItemWindow *v4; // ecx
  int pRect; // [esp+0x8] [ebp-0x10] BYREF
  int v6; // [esp+0xC] [ebp-0xC]
  int v7; // [esp+0x10] [ebp-0x8]
  int v8; // [esp+0x14] [ebp-0x4]

  p_m_pResultEarthLvup = (UIStatic **)&this->m_pResultEarthLvup;
  ((CCBLineupWindow *)this)->CCBLineupWindow::CCBLineupWindow((CCBControlWindow **)&this->m_pResultEarthLvup);
  if ( result )
  {
    v6 = 0;
    v7 = 0;
    v4 = (CCBItemWindow *)*p_m_pResultEarthLvup;
    pRect = 14;
    v7 = 172;
    v6 = 316;
    v8 = 474;
    (((CCBItemWindow *)v4))->CCBItemWindow::Create(&pRect, (int)this);
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)(*p_m_pResultEarthLvup)))((UIStatic *)(*p_m_pResultEarthLvup), (_DWORD)(0));
    return 1;
  }
  return result;
}

// 0x00517C80
bool CCBUI::CreateBattleFieldAttr()
{
  UIStatic **p_m_pResultDoubleLvup; // esi
  bool result; // al
  CCBParabolaWindow *v4; // ecx
  int v5; // [esp+0x0] [ebp-0x18]
  CCBParabolaWindow *v6; // [esp+0x8] [ebp-0x10] BYREF
  int v7; // [esp+0xC] [ebp-0xC]
  int v8; // [esp+0x10] [ebp-0x8]
  int v9; // [esp+0x14] [ebp-0x4]

  p_m_pResultDoubleLvup = (UIStatic **)&this->m_pResultDoubleLvup;
  (((CCBLineupWindow *)this))->CCBLineupWindow::_todo_0051D070((CCBItemWindow **)&this->m_pResultDoubleLvup) /* [ROWTABLE] */;
  if ( result )
  {
    v7 = 0;
    v8 = 0;
    v4 = (CCBParabolaWindow *)*p_m_pResultDoubleLvup;
    v6 = (CCBParabolaWindow *)9;
    v8 = 239;
    v7 = 232;
    v9 = 482;
    v4->CCBParabolaWindow::CCBParabolaWindow(&v6, (int *)this, v5);
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)(*p_m_pResultDoubleLvup)))((UIStatic *)(*p_m_pResultDoubleLvup), (_DWORD)(0));
    return 1;
  }
  return result;
}

// 0x00517D60
bool CCBUI::CreateControlWindow()
{
  int v1; // esi
  CCBControlWindow **i; // edi
  CCBSkillWindow *v4; // ecx
  UIWnd *v6; // [esp+0x0] [ebp-0x1C]
  int pRect; // [esp+0xC] [ebp-0x10] BYREF
  int v8; // [esp+0x10] [ebp-0xC]
  int v9; // [esp+0x14] [ebp-0x8]
  int v10; // [esp+0x18] [ebp-0x4]

  v1 = 0;
  v8 = 0;
  v9 = 0;
  pRect = 0;
  v10 = 0;
  for ( i = &this->m_pMain; (((CCBLineupWindow *)i))->CCBLineupWindow::Create(v6); ++i )
  {
    v9 = v1 + 256;
    v4 = (CCBSkillWindow *)*i;
    pRect = v1;
    v8 = 0;
    v10 = 256;
    (((CCBSkillWindow *)v4))->CCBSkillWindow::Create(&pRect, (int)this);
    (**(void ( ***)(CCBControlWindow *, _DWORD))((UIWnd *)(*i)))((CCBControlWindow *)(*i), (_DWORD)(0));
    v1 += 200;
    if ( v1 >= 800 )
      return 1;
  }
  return 0;
}

// 0x00517DF0
BOOL CCBUI::CreateItemWindow()
{
  UIPushButton **v2; // edi
  BOOL result; // eax
  UIPushButton *v4; // ecx
  UIPushButton **v5; // edi
  UIPushButton *v6; // ecx
  UIPushButton **v7; // edi
  UIPushButton *v8; // ecx
  UIPushButton **p_m_pRoleStateSword; // edi
  UIPushButton *v10; // ecx
  UIPushButton **p_m_pTrickName; // edi
  UIPushButton *v12; // ecx
  UIPushButton **p_m_pTrickName2; // edi
  UIPushButton *v14; // ecx
  UIPushButton **p_m_pDialogBack; // edi
  UIPushButton *v16; // ecx
  UIPushButton **p_m_pResultLevelup; // edi
  UIPushButton *v18; // ecx
  int v19; // [esp+0x80] [ebp-0x10] BYREF
  int v20; // [esp+0x84] [ebp-0xC]
  int v21; // [esp+0x88] [ebp-0x8]
  int v22; // [esp+0x8C] [ebp-0x4]

  v20 = 0;
  v2 = (UIPushButton **)&this->m_pRoleStateMP[1];
  v21 = 0;
  v19 = 0;
  v22 = 0;
  (((CCBAIWindow *)this))->CCBAIWindow::Reset((int *)&this->m_pRoleStateMP[1]);
  if ( result )
  {
    v4 = (UIPushButton *)*v2;
    v19 = 284;
    v21 = 516;
    v20 = 268;
    v22 = 332;
    (*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v4) + 16))(v4, 531, &v19, this);
    (((UIPushButton *)*v2))->UIPushButton::CreateFromTemplate(&unk_5DF42C, 0);
    (((UIScene *)*v2))->UIScene::SetShow(1);
    AllocObject(*v2);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*v2)))((UIPushButton *)(*v2), (_DWORD)(0));
    v5 = (UIPushButton **)&this->m_pRoleStateMP[2];
    (((CCBAIWindow *)this))->CCBAIWindow::Reset((int *)&this->m_pRoleStateMP[2]);
    if ( result )
    {
      v6 = (UIPushButton *)*v5;
      v19 = 249;
      v21 = 551;
      v20 = 263;
      v22 = 337;
      (*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v6) + 16))(v6, 533, &v19, this);
      (((UIPushButton *)*v5))->UIPushButton::CreateFromTemplate(&unk_5DF3E4, 0);
      (((UIScene *)*v5))->UIScene::SetShow(1);
      AllocObject(*v5);
      (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*v5)))((UIPushButton *)(*v5), (_DWORD)(0));
      v7 = (UIPushButton **)&this->m_pRoleStateMP[3];
      (((CCBAIWindow *)this))->CCBAIWindow::Reset((int *)&this->m_pRoleStateMP[3]);
      if ( result )
      {
        v8 = (UIPushButton *)*v7;
        v19 = 249;
        v21 = 551;
        v20 = 263;
        v22 = 337;
        (*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v8) + 16))(v8, 534, &v19, this);
        (((UIPushButton *)*v7))->UIPushButton::CreateFromTemplate(&unk_5DF3BC, 0);
        (((UIScene *)*v7))->UIScene::SetShow(1);
        AllocObject(*v7);
        (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*v7)))((UIPushButton *)(*v7), (_DWORD)(0));
        p_m_pRoleStateSword = (UIPushButton **)&this->m_pRoleStateSword;
        (((CCBAIWindow *)this))->CCBAIWindow::Reset((int *)&this->m_pRoleStateSword);
        if ( result )
        {
          v10 = (UIPushButton *)*p_m_pRoleStateSword;
          v19 = 249;
          v21 = 551;
          v20 = 263;
          v22 = 337;
          (*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v10) + 16))(
            v10,
            535,
            &v19,
            this);
          (((UIPushButton *)*p_m_pRoleStateSword))->UIPushButton::CreateFromTemplate(&unk_5DF394, 0);
          (((UIScene *)*p_m_pRoleStateSword))->UIScene::SetShow(1);
          AllocObject(*p_m_pRoleStateSword);
          (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*p_m_pRoleStateSword)))((UIPushButton *)(*p_m_pRoleStateSword), (_DWORD)(0));
          p_m_pTrickName = (UIPushButton **)&this->m_pTrickName;
          (((CCBAIWindow *)this))->CCBAIWindow::Reset((int *)&this->m_pTrickName);
          if ( result )
          {
            v12 = (UIPushButton *)*p_m_pTrickName;
            v19 = 249;
            v21 = 551;
            v20 = 263;
            v22 = 337;
            (*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v12) + 16))(
              v12,
              536,
              &v19,
              this);
            (((UIPushButton *)*p_m_pTrickName))->UIPushButton::CreateFromTemplate(&unk_5DF370, 0);
            (((UIScene *)*p_m_pTrickName))->UIScene::SetShow(1);
            AllocObject(*p_m_pTrickName);
            (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*p_m_pTrickName)))((UIPushButton *)(*p_m_pTrickName), (_DWORD)(0));
            p_m_pTrickName2 = (UIPushButton **)&this->m_pTrickName2;
            (((CCBAIWindow *)this))->CCBAIWindow::Reset((int *)&this->m_pTrickName2);
            if ( result )
            {
              v14 = (UIPushButton *)*p_m_pTrickName2;
              v19 = 249;
              v21 = 551;
              v20 = 263;
              v22 = 337;
              (*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v14) + 16))(
                v14,
                538,
                &v19,
                this);
              (((UIPushButton *)*p_m_pTrickName2))->UIPushButton::CreateFromTemplate(&unk_5DF348, 0);
              (((UIScene *)*p_m_pTrickName2))->UIScene::SetShow(1);
              AllocObject(*p_m_pTrickName2);
              (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*p_m_pTrickName2)))((UIPushButton *)(*p_m_pTrickName2), (_DWORD)(0));
              p_m_pDialogBack = (UIPushButton **)&this->m_pDialogBack;
              (((CCBAIWindow *)this))->CCBAIWindow::Reset((int *)&this->m_pDialogBack);
              if ( result )
              {
                v16 = (UIPushButton *)*p_m_pDialogBack;
                v19 = 249;
                v21 = 551;
                v20 = 263;
                v22 = 337;
                (*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v16) + 16))(
                  v16,
                  539,
                  &v19,
                  this);
                (((UIPushButton *)*p_m_pDialogBack))->UIPushButton::CreateFromTemplate(&unk_5DF320, 0);
                (((UIScene *)*p_m_pDialogBack))->UIScene::SetShow(1);
                AllocObject(*p_m_pDialogBack);
                (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*p_m_pDialogBack)))((UIPushButton *)(*p_m_pDialogBack), (_DWORD)(0));
                p_m_pResultLevelup = (UIPushButton **)&this->m_pResultLevelup;
                (((CCBAIWindow *)this))->CCBAIWindow::Reset((int *)&this->m_pResultLevelup);
                if ( result )
                {
                  v18 = (UIPushButton *)*p_m_pResultLevelup;
                  v19 = 221;
                  v21 = 579;
                  v20 = 255;
                  v22 = 345;
                  (*(void ( **)(UIPushButton *, int, int *, CCBUI *))(*(_DWORD *)((UIWnd *)v18) + 16))(
                    v18,
                    532,
                    &v19,
                    this);
                  (((UIPushButton *)*p_m_pResultLevelup))->UIPushButton::CreateFromTemplate(&unk_5DF408, 0);
                  (((UIScene *)*p_m_pResultLevelup))->UIScene::SetShow(1);
                  AllocObject(*p_m_pResultLevelup);
                  result = (**(int ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*p_m_pResultLevelup)))((UIPushButton *)(*p_m_pResultLevelup), (_DWORD)(0));
                  LOBYTE(result) = 1;
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

// 0x005181E0
bool CCBUI::CreateParaWindow()
{
  UIStatic *v2; // ecx
  UIStatic *v3; // ecx
  UIProgressBar *v4; // ecx
  UIProgressBar *v5; // ecx
  UIProgressBar *v6; // ecx
  UIProgressBar *m_pRoleStateSword; // ecx
  UIStaticCB *m_pTrickName; // ecx
  UIStaticCB *m_pTrickName2; // ecx
  UIStatic *m_pDialogBack; // ecx
  UIStatic *m_pResultLevelup; // ecx
  UIListBox *v12; // ecx
  int v13; // edi
  CCBControlWindow **p_m_pMain; // ebx
  bool result; // al

  this->m_pAIWindow = ((CCBAIWindow *)((CCBAIWindow *)((UIWnd *)this->m_pSkillWindow)));
  v2 = (UIStatic *)this->m_pRoleStateImmunity[4];
  if ( v2 )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v2))((UIStatic *)(v2), (_DWORD)(0));
  v3 = (UIStatic *)this->m_pRoleStateImmunity[5];
  if ( v3 )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v3))((UIStatic *)(v3), (_DWORD)(0));
  v4 = (UIProgressBar *)this->m_pRoleStateMP[1];
  if ( v4 )
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v4))((UIProgressBar *)(v4), (_DWORD)(0));
  v5 = (UIProgressBar *)this->m_pRoleStateMP[2];
  if ( v5 )
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v5))((UIProgressBar *)(v5), (_DWORD)(0));
  v6 = (UIProgressBar *)this->m_pRoleStateMP[3];
  if ( v6 )
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v6))((UIProgressBar *)(v6), (_DWORD)(0));
  m_pRoleStateSword = (UIProgressBar *)this->m_pRoleStateSword;
  if ( m_pRoleStateSword )
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)m_pRoleStateSword))((UIProgressBar *)(m_pRoleStateSword), (_DWORD)(0));
  m_pTrickName = (UIStaticCB *)this->m_pTrickName;
  if ( m_pTrickName )
    (**(void ( ***)(UIStaticCB *, _DWORD))((UIWnd *)m_pTrickName))((UIStaticCB *)(m_pTrickName), (_DWORD)(0));
  m_pTrickName2 = (UIStaticCB *)this->m_pTrickName2;
  if ( m_pTrickName2 )
    (**(void ( ***)(UIStaticCB *, _DWORD))((UIWnd *)m_pTrickName2))((UIStaticCB *)(m_pTrickName2), (_DWORD)(0));
  m_pDialogBack = (UIStatic *)this->m_pDialogBack;
  if ( m_pDialogBack )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pDialogBack))((UIStatic *)(m_pDialogBack), (_DWORD)(0));
  m_pResultLevelup = (UIStatic *)this->m_pResultLevelup;
  if ( m_pResultLevelup )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultLevelup))((UIStatic *)(m_pResultLevelup), (_DWORD)(0));
  (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)this->m_pResultThunderLvup))((UIStatic *)(this->m_pResultThunderLvup), (_DWORD)(0));
  (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)this->m_pResultWaterLvup))((UIStatic *)(this->m_pResultWaterLvup), (_DWORD)(0));
  (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)this->m_pResultFireLvup))((UIStatic *)(this->m_pResultFireLvup), (_DWORD)(0));
  (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)this->m_pResultEarthLvup))((UIStatic *)(this->m_pResultEarthLvup), (_DWORD)(0));
  (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)this->m_pResultDoubleLvup))((UIStatic *)(this->m_pResultDoubleLvup), (_DWORD)(0));
  (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)this->m_pResultGetItem))((UIStatic *)(this->m_pResultGetItem), (_DWORD)(0));
  (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)this->m_pRoleStateMP[0]))((UIProgressBar *)(this->m_pRoleStateMP[0]), (_DWORD)(0));
  this->m_pRoleStateGP[2]->m_pbk = ((gbTexture *)0);
  (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)this->m_pRoleStateGP[2]))((UIProgressBar *)(this->m_pRoleStateGP[2]), (_DWORD)(0));
  this->m_pRoleStateGP[3]->m_pbk = ((gbTexture *)0);
  (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)this->m_pRoleStateGP[3]))((UIProgressBar *)(this->m_pRoleStateGP[3]), (_DWORD)(0));
  this->CCBUI::CreateResultWindow(0);
  v12 = (UIListBox *)this->m_pRoleStateGP[1];
  if ( v12 )
  {
    (((UIListBox *)v12))->UIListBox::GetCurSel();
    (((UIScrollBar *)this->m_pRoleStateGP[1]))->UIScrollBar::SetRange(50.0);
    (((UIProgressBar *)this->m_pRoleStateGP[1]))->UIProgressBar::FindChildByName(0.0);
  }
  v13 = 0;
  p_m_pMain = (CCBControlWindow **)&this->m_pMain;
  do
  {
    *((_DWORD *)&(*p_m_pMain)->m_CurCtrl_2 + 13) = v13;
    (**(void ( ***)(CCBControlWindow *, _DWORD))((UIWnd *)(*p_m_pMain)))((CCBControlWindow *)(*p_m_pMain), (_DWORD)(0));
    ++v13;
    ++p_m_pMain;
  }
  while ( v13 < 4 );
  memset(&this->m_pLineupWindow, 0, 0x5A0u);
  this->fp.fp = ((char *)0);
  this->fp.fp_data[0] = 0;
  *((_DWORD *)&this->fp + 4) = 0;
  *((_DWORD *)&this->fp + 5) = -1;
  result = 1;
  this->fp.fp_data[1] = 0;
  this->fp.fp_data[2] = -1;
  return result;
}

// 0x005183C0
BOOL CCBUI::CreateMagicWindow()
{
  UIStatic *v2; // ecx
  UIStatic *v3; // ecx
  UIProgressBar *v4; // ecx
  UIStatic *m_pResultWindLvup; // ecx
  UIStatic *m_pResultThunderLvup; // ecx
  UIStatic *m_pResultWaterLvup; // ecx
  UIStatic *m_pResultFireLvup; // ecx
  UIStatic *m_pResultEarthLvup; // ecx
  UIStatic *m_pResultDoubleLvup; // ecx
  UIStatic *m_pResultGetItem; // ecx
  UIProgressBar *v12; // ecx
  UIProgressBar *v13; // ecx
  int v14; // edi
  CCBControlWindow **p_m_pMain; // esi
  BOOL result; // eax

  v2 = (UIStatic *)this->m_pRoleStateImmunity[4];
  if ( v2 )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v2))((UIStatic *)(v2), (_DWORD)(0));
  v3 = (UIStatic *)this->m_pRoleStateImmunity[5];
  if ( v3 )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v3))((UIStatic *)(v3), (_DWORD)(0));
  v4 = (UIProgressBar *)this->m_pRoleStateMP[0];
  if ( v4 )
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v4))((UIProgressBar *)(v4), (_DWORD)(0));
  m_pResultWindLvup = (UIStatic *)this->m_pResultWindLvup;
  if ( m_pResultWindLvup )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultWindLvup))((UIStatic *)(m_pResultWindLvup), (_DWORD)(0));
  m_pResultThunderLvup = (UIStatic *)this->m_pResultThunderLvup;
  if ( m_pResultThunderLvup )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultThunderLvup))((UIStatic *)(m_pResultThunderLvup), (_DWORD)(0));
  m_pResultWaterLvup = (UIStatic *)this->m_pResultWaterLvup;
  if ( m_pResultWaterLvup )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultWaterLvup))((UIStatic *)(m_pResultWaterLvup), (_DWORD)(0));
  m_pResultFireLvup = (UIStatic *)this->m_pResultFireLvup;
  if ( m_pResultFireLvup )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultFireLvup))((UIStatic *)(m_pResultFireLvup), (_DWORD)(0));
  m_pResultEarthLvup = (UIStatic *)this->m_pResultEarthLvup;
  if ( m_pResultEarthLvup )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultEarthLvup))((UIStatic *)(m_pResultEarthLvup), (_DWORD)(0));
  m_pResultDoubleLvup = (UIStatic *)this->m_pResultDoubleLvup;
  if ( m_pResultDoubleLvup )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultDoubleLvup))((UIStatic *)(m_pResultDoubleLvup), (_DWORD)(0));
  m_pResultGetItem = (UIStatic *)this->m_pResultGetItem;
  if ( m_pResultGetItem )
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultGetItem))((UIStatic *)(m_pResultGetItem), (_DWORD)(0));
  v12 = (UIProgressBar *)this->m_pRoleStateGP[2];
  if ( v12 )
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v12))((UIProgressBar *)(v12), (_DWORD)(0));
  v13 = (UIProgressBar *)this->m_pRoleStateGP[3];
  if ( v13 )
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)v13))((UIProgressBar *)(v13), (_DWORD)(0));
  this->CCBUI::CreateResultWindow(0);
  v14 = 0;
  p_m_pMain = (CCBControlWindow **)&this->m_pMain;
  do
  {
    result = (BOOL)*p_m_pMain;
    if ( *p_m_pMain )
    {
      *(_DWORD *)(result + 172) = v14;
      result = (**(int ( ***)(CCBControlWindow *, _DWORD))((UIWnd *)(*p_m_pMain)))((CCBControlWindow *)(*p_m_pMain), (_DWORD)(0));
    }
    ++v14;
    ++p_m_pMain;
  }
  while ( v14 < 4 );
  return result;
}

// 0x005184C0
bool CCBUI::CreateSkillWindow(char pData)
{
  UIStatic *m_pResultWindLvup; // ecx

  m_pResultWindLvup = (UIStatic *)this->m_pResultWindLvup;
  if ( pData )
    return (**(int ( ***)(UIStatic *, int))((UIWnd *)m_pResultWindLvup))((UIStatic *)(m_pResultWindLvup), (int)(1));
  else
    return (**(int ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultWindLvup))((UIStatic *)(m_pResultWindLvup), (_DWORD)(0));
}

// 0x005184E0
int CCBUI::InitRoleDisplay(int a_128)
{
  int v3; // ebx
  CCBControlWindow **p_m_pMain; // esi
  CCBRoleState *left; // ebp
  CCBRoleState *v6; // ebp
  char *v7; // eax
  CCBRoleState *v8; // ebp
  CCBRoleState *v9; // ebp
  CCBRoleState *v10; // ebp
  CCBRoleState *v11; // ebp
  CCBSkillWindow *m_pSkillWindow; // edx
  float nEXP; // st7
  CCBControlWindow *v14; // eax
  unsigned int v15; // eax
  int RoleExp; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int *v22; // eax
  CCBControlWindow *v23; // ebp
  int v24; // ecx
  int v25; // eax
  CCBSkillWindow *v26; // ecx
  unsigned int v27; // eax
  int result; // eax
  bool v29; // cc
  int nVal6; // [esp+0x4] [ebp-0x120]
  int nLevel; // [esp+0x8] [ebp-0x11C]
  int fValue; // [esp+0xC] [ebp-0x118]
  char *fValuea; // [esp+0xC] [ebp-0x118]
  float fValueb; // [esp+0xC] [ebp-0x118]
  float fValuec; // [esp+0xC] [ebp-0x118]
  float fValued; // [esp+0xC] [ebp-0x118]
  float fValuee; // [esp+0xC] [ebp-0x118]
  float fValuef; // [esp+0xC] [ebp-0x118]
  float fValueg; // [esp+0xC] [ebp-0x118]
  int v40; // [esp+0x20] [ebp-0x104]
  char *v41; // [esp+0x24] [ebp-0x100]
  unsigned int dwID; // [esp+0x28] [ebp-FCh]
  int v43; // [esp+0x2C] [ebp-F8h]
  CCBRoleState *v44; // [esp+0x30] [ebp-F4h]
  CCBControlWindow *v45; // [esp+0x34] [ebp-F0h] BYREF
  float v46; // [esp+0x38] [ebp-ECh]
  float v47; // [esp+0x3C] [ebp-E8h]
  float v48; // [esp+0x40] [ebp-E4h]
  int v49; // [esp+0x44] [ebp-E0h]
  int v50; // [esp+0x54] [ebp-D0h]
  int v51; // [esp+0x5C] [ebp-C8h]
  char Buffer[140]; // [esp+0x64] [ebp-C0h] BYREF
  int v53; // [esp+F0h] [ebp-0x34]
  UICaption *pData[8]; // [esp+F4h] [ebp-0x30] BYREF
  char a2[16]; // [esp+0x114] [ebp-0x10] BYREF

  v3 = 0;
  v43 = 0;
  v40 = 108;
  p_m_pMain = (CCBControlWindow **)&this->m_pMain;
  left = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
  v44 = (CCBRoleState *)left;
  v41 = (char *)&left->m_pObjMsgBuffer[153];
  do
  {
    if ( !*v41 )
      goto LABEL_23;
    dwID = (((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(v3)->dwID;
    *((_DWORD *)&(*p_m_pMain)->m_CurCtrl_2 + 13) = v3;
    if ( (((CCBRoleState *)left))->CCBRoleState::GetRoleField(v3, 3) )
    {
      (((NPC *)*(NPC **)((char *)((UIWnd *)(*p_m_pMain)) + v40)))->NPC::UpdateAnim(-13002067);
    }
    else
    {
      if ( !(((CCBRoleState *)left))->CCBRoleState::GetRoleField(v3, 4) )
      {
        if ( (((CCBRoleState *)left))->CCBRoleState::GetRoleField(v3, 2) )
        {
          fValue = -6002966;
        }
        else
        {
          if ( (((CCBRoleState *)left))->CCBRoleState::GetRoleField(v3, 1) )
          {
            (((NPC *)*(NPC **)((char *)((UIWnd *)(*p_m_pMain)) + v40)))->NPC::UpdateAnim(-11356565);
            goto LABEL_15;
          }
          if ( (((CCBRoleState *)left))->CCBRoleState::GetRoleField(v3, 5) )
          {
            (((NPC *)*(NPC **)((char *)((UIWnd *)(*p_m_pMain)) + v40)))->NPC::UpdateAnim(-2707878);
            goto LABEL_15;
          }
          fValue = -1;
        }
        (((NPC *)*(NPC **)((char *)((UIWnd *)(*p_m_pMain)) + v40)))->NPC::UpdateAnim(fValue);
        goto LABEL_15;
      }
      (((NPC *)*(NPC **)((char *)((UIWnd *)(*p_m_pMain)) + v40)))->NPC::UpdateAnim(-2198223);
    }
LABEL_15:
    switch ( dwID )
    {
      case 'e':
        v6 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValuea = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        nLevel = (((CCBRoleState *)v6))->CCBRoleState::InitUI(v3)->nLevel;
        v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Jingtian");
        goto LABEL_21;
      case 'f':
        v11 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValuea = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        nLevel = (((CCBRoleState *)v11))->CCBRoleState::InitUI(v3)->nLevel;
        v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Changqing");
        goto LABEL_21;
      case 'h':
        v8 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValuea = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        nLevel = (((CCBRoleState *)v8))->CCBRoleState::InitUI(v3)->nLevel;
        v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Xuejian");
        goto LABEL_21;
      case 'i':
      case 'j':
        v9 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValuea = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        nLevel = (((CCBRoleState *)v9))->CCBRoleState::InitUI(v3)->nLevel;
        v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Longkui");
        goto LABEL_21;
      case 'k':
        v10 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValuea = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(aLevel);
        nLevel = (((CCBRoleState *)v10))->CCBRoleState::InitUI(v3)->nLevel;
        v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("Zixuan");
LABEL_21:
        sprintf(Buffer, "%s %d %s", v7, nLevel, fValuea);
        break;
      default:
        break;
    }
    SetEnable((UICaption *)(*p_m_pMain)->m_pButtonFlee);
    SetEnable((UICaption *)(*p_m_pMain)->m_pButtonLineup);
    (((UIListBox *)*((UIListBox **)&(*p_m_pMain)->m_CurCtrl_2 + 9)))->UIListBox::GetCurSel();
    fValueb = (float)(((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(v3)->nFullHP;
    (((UIScrollBar *)*((UIScrollBar **)&(*p_m_pMain)->m_CurCtrl_2 + 9)))->UIScrollBar::SetRange(fValueb);
    fValuec = (float)(((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(v3)->nHP;
    (((UIProgressBar *)*((UIProgressBar **)&(*p_m_pMain)->m_CurCtrl_2 + 9)))->UIProgressBar::FindChildByName(fValuec);
    (((UIListBox *)*((UIListBox **)&(*p_m_pMain)->m_CurCtrl_2 + 10)))->UIListBox::GetCurSel();
    fValued = (float)(int)(((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(v3)->pCCBSystem;
    (((UIScrollBar *)*((UIScrollBar **)&(*p_m_pMain)->m_CurCtrl_2 + 10)))->UIScrollBar::SetRange(fValued);
    fValuee = (float)(((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(v3)->nGP;
    (((UIProgressBar *)*((UIProgressBar **)&(*p_m_pMain)->m_CurCtrl_2 + 10)))->UIProgressBar::FindChildByName(fValuee);
    (((UIListBox *)*((UIListBox **)&(*p_m_pMain)->m_CurCtrl_2 + 11)))->UIListBox::GetCurSel();
    fValuef = (float)(((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(v3)->nFullMP;
    (((UIScrollBar *)*((UIScrollBar **)&(*p_m_pMain)->m_CurCtrl_2 + 11)))->UIScrollBar::SetRange(fValuef);
    fValueg = (float)(int)(((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(v3)->nMP;
    (((UIProgressBar *)*((UIProgressBar **)&(*p_m_pMain)->m_CurCtrl_2 + 11)))->UIProgressBar::FindChildByName(fValueg);
    m_pSkillWindow = (CCBSkillWindow *)this->m_pSkillWindow;
    pData[1] = 0;
    nEXP = (float)((*((CCBRoleState **)m_pSkillWindow + 4)))->CCBRoleState::InitUI(v3)->nEXP;
    v14 = (CCBControlWindow *)*p_m_pMain;
    *(float *)&pData[3] = nEXP;
    pData[0] = (UICaption *)v14->m_pButtonAI;
    SetEnable(pData[0]);
    v15 = (((CCBSystem *)this->m_pSkillWindow))->CCBSystem::ProcProtect();
    this->CCBUI::IsResultWindowClosed(0 /* TODO: pmf_to_u32((void (CCBUI::*)(int))CCBUI::ShowControlWindow) */, 0, 0, 0, v15, 0, 0x40000000, pData);
    RoleExp = (((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::GetRoleExp(v3);
    sprintf(Buffer, (const char *)&dir[20], RoleExp);
    SetEnable((UICaption *)(*p_m_pMain)->m_pButtonAttack);
    v17 = (((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::GetRoleExp(v3);
    sprintf(Buffer, (const char *)&dir[20], v17);
    SetEnable((UICaption *)(*p_m_pMain)->m_pButtonSkill);
    v18 = (((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::GetRoleExp(v3);
    sprintf(Buffer, (const char *)&dir[20], v18);
    SetEnable((UICaption *)(*p_m_pMain)->m_pButtonMagic);
    v19 = (((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::GetRoleExp(v3);
    sprintf(Buffer, (const char *)&dir[20], v19);
    SetEnable((UICaption *)(*p_m_pMain)->m_pButtonItem);
    v20 = (((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::GetRoleExp(v3);
    sprintf(Buffer, (const char *)&dir[20], v20);
    SetEnable((UICaption *)(*p_m_pMain)->m_pButtonDefence);
    v21 = (((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::GetRoleExp(v3);
    sprintf(Buffer, (const char *)&dir[20], v21);
    SetEnable((UICaption *)(*p_m_pMain)->m_pButtonLineup);
    v22 = (int *)sub_445FE0(a2);
    v23 = (CCBControlWindow *)*p_m_pMain;
    v50 = (unsigned long)*v22;
    v24 = (unsigned long)v22[1];
    v51 = (unsigned long)v22[2];
    v25 = (unsigned long)v22[3];
    v49 = 0;
    v46 = (float)v50;
    v45 = (CCBControlWindow *)v23;
    v47 = -(float)(v25 - v24);
    v48 = v46;
    MoveToAbsolute(v23, (__int64)v46, (__int64)v47);
    (**(void ( ***)(CCBControlWindow *, int))((UIWnd *)v45))((CCBControlWindow *)(v45), (int)(1));
    v26 = (CCBSkillWindow *)this->m_pSkillWindow;
    v53 = 0;
    *(float *)&nVal6 = (double)v43 * 0.079999998;
    v27 = (((CCBSystem *)v26))->CCBSystem::ProcProtect();
    this->CCBUI::IsResultWindowClosed(0 /* TODO: pmf_to_u32((void (CCBUI::*)(int))CCBUI::ShowBattleFieldAttr) */, 0, 0, v53, v27, nVal6, 1161527296, &v45);
    left = (CCBRoleState *)v44;
    ++p_m_pMain;
    ++v43;
LABEL_23:
    result = v40 + 4;
    ++v3;
    v29 = v40 + 4 < 128;
    v40 += 4;
    v41 += 892;
  }
  while ( v29 );
  return result;
}

// 0x00518AF0
bool CCBUI::CreateLineupWindow(int nVal, char pData)
{
  UIStatic *m_pResultEarthLvup; // ecx

  this->m_pResultEarthLvup->m_ppicInfo = ((_PlugInfo *)((_PlugInfo *)nVal));
  m_pResultEarthLvup = (UIStatic *)this->m_pResultEarthLvup;
  if ( pData )
    return (**(int ( ***)(UIStatic *, int))((UIWnd *)m_pResultEarthLvup))((UIStatic *)(m_pResultEarthLvup), (int)(1));
  else
    return (**(int ( ***)(UIStatic *, _DWORD))((UIWnd *)m_pResultEarthLvup))((UIStatic *)(m_pResultEarthLvup), (_DWORD)(0));
}

// 0x00518B20
bool CCBUI::CreateProtectWindow()
{
  return *((_BYTE *)&this->m_pMain->m_CurCtrl_2 + 56);
}

// 0x00518B30
bool CCBUI::CreateResultWindow(char pData)
{
  int i; // edi
  bool result; // al
  int byUIIndex; // ebx
  UIStatic **v6; // edi
  int v7; // ebx
  UIStatic **v8; // edi
  int v9; // ebx
  UIStatic **v10; // esi
  int v11; // edi

  if ( pData )
  {
    for ( i = 0; i < 5; ++i )
    {
      result = *(_BYTE *)(this->m_pSkillWindow->m_rect.left + 892 * i + 577);
      if ( result )
      {
        (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pAttackSequenFace[i + 8]))((UIStatic *)(this->m_pAttackSequenFace[i + 8]), (int)(1));
        (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pRoleStatePanel[i + 2]))((UIStatic *)(this->m_pRoleStatePanel[i + 2]), (int)(1));
        byUIIndex = (unsigned __int8)(((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(i)->byUIIndex;
        (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pRoleStateImmunity[byUIIndex + 6]))((UIStatic *)(this->m_pRoleStateImmunity[byUIIndex + 6]), (int)(1));
        (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pRoleStateImmunity[byUIIndex + 10]))((UIStatic *)(this->m_pRoleStateImmunity[byUIIndex + 10]), (int)(1));
        (**(void ( ***)(UIProgressBar *, int))((UIWnd *)this->m_pRoleStateHP[byUIIndex + 1]))((UIProgressBar *)(this->m_pRoleStateHP[byUIIndex + 1]), (int)(1));
        result = (**(int ( ***)(UIStatic *, int))((UIWnd *)this->m_pAttackSequenFace[byUIIndex + 4]))((UIStatic *)(this->m_pAttackSequenFace[byUIIndex + 4]), (int)(1));
        if ( !i )
          result = (**(int ( ***)(UIProgressBar *, int))((UIWnd *)this->m_pRoleStateGP[1]))((UIProgressBar *)(this->m_pRoleStateGP[1]), (int)(1));
      }
    }
  }
  else
  {
    (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)this->m_pRoleStateGP[1]))((UIProgressBar *)(this->m_pRoleStateGP[1]), (_DWORD)(0));
    v6 = (UIStatic **)&this->m_pRoleStateImmunity[10];
    v7 = 4;
    do
    {
      (**(void ( ***)(_DWORD, _DWORD))((UIWnd *)(*(v6 - 4))))((_DWORD)(*(v6 - 4)), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)(*v6)))((UIStatic *)(*v6), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v6[4]))((UIStatic *)(v6[4]), (_DWORD)(0));
      (**(void ( ***)(_DWORD, _DWORD))((UIWnd *)(*(v6 - 229))))((_DWORD)(*(v6 - 229)), (_DWORD)(0));
      ++v6;
      --v7;
    }
    while ( v7 );
    v8 = (UIStatic **)&this->m_pRoleStatePanel[2];
    v9 = 5;
    do
    {
      (**(void ( ***)(_DWORD, _DWORD))((UIWnd *)(*(v8 - 5))))((_DWORD)(*(v8 - 5)), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)(*v8)))((UIStatic *)(*v8), (_DWORD)(0));
      ++v8;
      --v9;
    }
    while ( v9 );
    v10 = (UIStatic **)&this->m_pRoleStateAttackInc[4];
    v11 = 11;
    do
    {
      (**(void ( ***)(_DWORD, _DWORD))((UIWnd *)(*(v10 - 11))))((_DWORD)(*(v10 - 11)), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)(*v10)))((UIStatic *)(*v10), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[11]))((UIStatic *)(v10[11]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[22]))((UIStatic *)(v10[22]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[55]))((UIStatic *)(v10[55]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[66]))((UIStatic *)(v10[66]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[33]))((UIStatic *)(v10[33]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[44]))((UIStatic *)(v10[44]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[77]))((UIStatic *)(v10[77]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[88]))((UIStatic *)(v10[88]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[99]))((UIStatic *)(v10[99]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[110]))((UIStatic *)(v10[110]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[121]))((UIStatic *)(v10[121]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[132]))((UIStatic *)(v10[132]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[143]))((UIStatic *)(v10[143]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[154]))((UIStatic *)(v10[154]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[165]))((UIStatic *)(v10[165]), (_DWORD)(0));
      (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[176]))((UIStatic *)(v10[176]), (_DWORD)(0));
      result = (**(int ( ***)(UIStatic *, _DWORD))((UIWnd *)v10[187]))((UIStatic *)(v10[187]), (_DWORD)(0));
      ++v10;
      --v11;
    }
    while ( v11 );
  }
  return result;
}

// 0x00518D40
bool CCBUI::CreateFiveNimbus(char pData)
{
  int v3; // ebx
  int v4; // ebp
  int i; // esi

  if ( !pData )
    return (**(int ( ***)(UIStatic *, _DWORD))((UIWnd *)this->m_pResultDoubleLvup))((UIStatic *)(this->m_pResultDoubleLvup), (_DWORD)(0));
  v3 = 0;
  v4 = 0;
  for ( i = 96; i < 116; i += 4 )
  {
    if ( *(_BYTE *)(this->m_pSkillWindow->m_rect.left + v4 + 577) )
    {
      (***(void ( ****)(_DWORD, int))((char *)((UIWnd *)this->m_pResultDoubleLvup) + i))((_DWORD)(*(_DWORD *)((char *)((UIWnd *)this->m_pResultDoubleLvup) + i)), (int)(1));
      *(_DWORD *)((char *)this->m_pResultDoubleLvup + i - 24) = *(_DWORD *)&(((CCBRoleState *)this->m_pSkillWindow->m_rect.left))->CCBRoleState::InitUI(v3)->byMagicUseTime[8][3];
      MoveToAbsolute(
        *(_DWORD **)((char *)((UIWnd *)this->m_pResultDoubleLvup) + i),
        g_nUnkTable_24C[*(_DWORD *)((char *)this->m_pResultDoubleLvup + i - 24)] + 9,
        g_nUnkTable_268[*(_DWORD *)((char *)this->m_pResultDoubleLvup + i - 24)] + 232);
    }
    else
    {
      (***(void ( ****)(_DWORD, _DWORD))((char *)((UIWnd *)this->m_pResultDoubleLvup) + i))((_DWORD)(*(_DWORD *)((char *)((UIWnd *)this->m_pResultDoubleLvup) + i)), (_DWORD)(0));
    }
    ++v3;
    v4 += 892;
  }
  return (**(int ( ***)(UIStatic *, int))((UIWnd *)this->m_pResultDoubleLvup))((UIStatic *)(this->m_pResultDoubleLvup), (int)(1));
}

// 0x00518E60
void CCBUI::HideAll()
{
  NPC **v1; // esi
  int v2; // ebx
  float v3; // [esp+0x10] [ebp-0x8]
  int v4; // [esp+0x14] [ebp-0x4]

  HIBYTE(v4) = -1;
  v3 = sin(*(float *)this->m_pSkillWindow->m_pSkillList * 12.0f) * 50.0f;
  v1 = (NPC **)&this->m_pRoleStateAttackInc[4];
  v2 = 4;
  BYTE2(v4) = (int)v3 - 56;
  BYTE1(v4) = BYTE2(v4);
  LOBYTE(v4) = BYTE2(v4);
  do
  {
    (((NPC *)*(v1 - 11)))->NPC::UpdateAnim(v4);
    (((NPC *)*v1))->NPC::UpdateAnim(v4);
    (((NPC *)v1[11]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[22]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[33]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[44]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[55]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[66]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[77]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[88]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[99]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[110]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[121]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[132]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[143]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[154]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[165]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[176]))->NPC::UpdateAnim(v4);
    (((NPC *)v1[187]))->NPC::UpdateAnim(v4);
    ++v1;
    --v2;
  }
  while ( v2 );
}

// 0x00518FE0
void CCBUI::ShowBattleFieldAttr(int attr)
{
  CCBLineupWindow **v2; // esi
  CCBSkillWindow *m_pSkillWindow; // ecx
  float v4; // st6
  float v5; // st7
  float v6; // st7

  v2 = (CCBLineupWindow **)(&this->m_pLineupWindow + 18 * *((_DWORD *)&this->fp + 5));
  if ( !BYTE1(this->m_pResultWindow[18 * *((_DWORD *)&this->fp + 5) + 2]) )
  {
    this->m_pResultWindow[18 * *((_DWORD *)&this->fp + 5) + 4] = (CCBResultWindow *)this->m_pSkillWindow->m_pSkillList[0];
    *((_BYTE *)v2 + 17) = 1;
  }
  m_pSkillWindow = (CCBSkillWindow *)this->m_pSkillWindow;
  v4 = *((float *)v2 + 7) + *((float *)v2 + 6);
  if ( *(float *)m_pSkillWindow->m_pSkillList > v4 )
  {
    v5 = *(float *)m_pSkillWindow->m_pSkillList - v4;
    v6 = v5 * (v5 * *((float *)v2 + 8)) * 0.5f + *((float *)v2 + 11);
    if ( v6 > *((float *)v2 + 13) )
    {
      v6 = *((float *)v2 + 13);
      *((_BYTE *)v2 + 18) = 1;
    }
    MoveToAbsolute(v2[9], (__int64)*((float *)v2 + 10), (__int64)v6);
  }
}

// 0x00519080
void CCBUI::ShowControlWindow(int bShow)
{
  CCBLineupWindow **v2; // esi
  float v3; // st6
  float v4; // [esp+0x8] [ebp-0x8]
  float v5; // [esp+0xC] [ebp-0x4]

  v2 = (CCBLineupWindow **)(&this->m_pLineupWindow + 18 * *((_DWORD *)&this->fp + 5));
  if ( !BYTE1(this->m_pResultWindow[18 * *((_DWORD *)&this->fp + 5) + 2]) )
  {
    this->m_pResultWindow[18 * *((_DWORD *)&this->fp + 5) + 4] = (CCBResultWindow *)this->m_pSkillWindow->m_pSkillList[0];
    *((_BYTE *)v2 + 17) = 1;
  }
  v3 = *((float *)v2 + 7) + *((float *)v2 + 6);
  if ( *(float *)this->m_pSkillWindow->m_pSkillList > v3 )
  {
    v5 = (*(float *)this->m_pSkillWindow->m_pSkillList - v3) / *((float *)v2 + 8);
    v4 = (*((float *)v2 + 12) - *((float *)v2 + 10)) * v5 + *((float *)v2 + 10);
    sprintf(byte_17ACB08, (const char *)&dir[20], (int)v4);
    SetEnable((UICaption *)v2[9]);
    if ( v5 >= 1.0f )
    {
      sprintf(byte_17ACB08, (const char *)&dir[20], (int)*((float *)v2 + 12));
      SetEnable((UICaption *)v2[9]);
      *((_BYTE *)v2 + 18) = 1;
    }
  }
}

// 0x00519200
void CCBUI::ShowDialogWindow()
{
  int v2; // esi
  _BYTE *v3; // edi

  v2 = 0;
  v3 = (char *)&this->m_pResultWindow[2] + 2;
  do
  {
    if ( *(v3 - 2) == 1 && *v3 == 1 )
      this->CCBUI::ShowAIWindow(v2);
    ++v2;
    v3 += 72;
  }
  while ( v2 < 20 );
}

// 0x00519230
void CCBUI::ShowAIWindow(int nRoleIndex)
{
  LOBYTE(this->m_pResultWindow[18 * nRoleIndex + 2]) = 0;
  --*((_DWORD *)&this->fp + 4);
}

// 0x00519260
bool CCBUI::IsResultWindowClosed(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        int nVal6,
        int nVal7,
        const void *pData)
{
  int v10; // eax
  CCBResultWindow **i; // ecx
  UIFrameWnd *v13; // eax

  if ( *((int *)&this->fp + 4) >= 19 )
    return 0;
  v10 = 0;
  for ( i = &this->m_pResultWindow[2]; *(_BYTE *)i; i += 18 )
  {
    if ( ++v10 >= 20 )
      return 0;
  }
  v13 = (CCBUI *)((char *)this + 72 * v10);
  LOBYTE(v13[16].m_pfather) = 1;
  BYTE1(v13[16].m_pfather) = 0;
  BYTE2(v13[16].m_pfather) = 0;
  v13[16].m_childs.m_nSize = nVal6;
  v13[16].m_childs.m_needscriptdel = nVal7;
  v13[16].m_childs.m_pData = (char *)nVal5;
  qmemcpy(&v13[16].m_bcreateok, pData, 0x20u);
  v13 = (UIFrameWnd *)((char *)v13 + 1168);
  *(_DWORD *)((UIWnd *)v13) = nVal;
  v13->m_fontcolor.Color = nVal2;
  v13->m_wndcolor.Color = nVal3;
  v13->m_id = nVal4;
  ++*((_DWORD *)&this->fp + 4);
  return 1;
}

// 0x00519310
CCBUI::CCBUI()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  this->CCBUI::ClearAttackSequence();
}

// 0x00519380
void CCBUI::Release()
{
  this->CCBUI::ClearAttackSequence();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x005193D0
void CCBUI::ClearAttackSequence()
{
  this->m_pAttackSequenBack = ((UIStatic *)0);
  this->pPanel = ((UIStatic *)0);
  this->m_pBattleFieldAttr[0] = 0;
  this->m_pBattleFieldAttr[1] = 0;
  this->m_pBattleFieldAttr[2] = 0;
  this->m_pBattleFieldAttr[3] = 0;
  this->m_pBattleFieldAttr[4] = 0;
  this->m_pBattleFieldAttr[5] = 0;
  this->m_pAttackSequenFace[0] = 0;
  this->m_pAttackSequenFace[1] = 0;
  this->m_pAttackSequenFace[2] = 0;
}

// 0x00519400
void CCBUI::CreateImbibeNimbus(int nCount)
{
  UIFrameContainer *v3; // eax
  UIStatic *v4; // eax
  char pExceptionObject[1024]; // [esp+0xC] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x40C] [ebp-0x40C] BYREF
  int v7; // [esp+0x814] [ebp-0x4]
  int parent; // [esp+0x820] [ebp+0x8]

  this->UIWnd::Create(1879048193, (tagRECT *)nCount, parent);
  v3 = (UIFrameContainer *)operator new(0x98u);
  v7 = 0;
  if ( v3 )
    (((UIFrameContainer *)v3))->UIFrameContainer::ResetContainerState();
  else
    v4 = 0;
  v7 = -1;
  this->m_pAttackSequenBack = ((UIStatic *)(v4));
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 2090),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *(_DWORD *)nCount = 0;
  *(_DWORD *)(nCount + 8) = 256;
  *(_DWORD *)(nCount + 4) = 0;
  *(_DWORD *)(nCount + 12) = 256;
  (*(void ( **)(UIStatic *, int, int, CCBUI *))(*(_DWORD *)((UIWnd *)this->m_pAttackSequenBack) + 16))(
    this->m_pAttackSequenBack,
    256,
    nCount,
    this);
  (((UIPushButton *)this->m_pAttackSequenBack))->UIPushButton::CreateFromTemplate(&unk_5DF204, 0);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pAttackSequenBack))((UIStatic *)(this->m_pAttackSequenBack), (int)(1));
  this->CCBUI::SetNimbusToNimbusControl();
}

// 0x005196C0
void CCBUI::SetNimbusToNimbusControl()
{
  UIStatic **v2; // edi

  v2 = (UIStatic **)&this->m_pAttackSequenFace[2];
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)(*v2)))((UIStatic *)(*v2), (_DWORD)(0));
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->pPanel))((UIStatic *)(this->pPanel), (int)(1));
  (((PalScript *)this->pPanel))->PalScript::OpenScript("ui\\combat\\control\\attack3.tga", 0);
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[0]))((UIStatic *)(this->m_pBattleFieldAttr[0]), (int)(1));
  (((PalScript *)this->m_pBattleFieldAttr[0]))->PalScript::OpenScript("ui\\combat\\control\\skill3.tga", 0);
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[1]))((UIStatic *)(this->m_pBattleFieldAttr[1]), (int)(1));
  (((PalScript *)this->m_pBattleFieldAttr[1]))->PalScript::OpenScript("ui\\combat\\control\\magic3.tga", 0);
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[2]))((UIStatic *)(this->m_pBattleFieldAttr[2]), (int)(1));
  (((PalScript *)this->m_pBattleFieldAttr[2]))->PalScript::OpenScript("ui\\combat\\control\\item3.tga", 0);
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[4]))((UIStatic *)(this->m_pBattleFieldAttr[4]), (int)(1));
  (((PalScript *)this->m_pBattleFieldAttr[4]))->PalScript::OpenScript("ui\\combat\\control\\lineup3.tga", 0);
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[5]))((UIStatic *)(this->m_pBattleFieldAttr[5]), (int)(1));
  (((PalScript *)this->m_pBattleFieldAttr[5]))->PalScript::OpenScript("ui\\combat\\control\\ai3.tga", 0);
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pAttackSequenFace[0]))((UIStatic *)(this->m_pAttackSequenFace[0]), (int)(1));
  (((PalScript *)this->m_pAttackSequenFace[0]))->PalScript::OpenScript("ui\\combat\\control\\flee3.tga", 0);
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pAttackSequenFace[1]))((UIStatic *)(this->m_pAttackSequenFace[1]), (int)(1));
  (((PalScript *)this->m_pAttackSequenFace[1]))->PalScript::OpenScript("ui\\combat\\control\\protect3.tga", 0);
  this->CCBUI::WriteNimbusToPlayerMgr();
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[3]))((UIStatic *)(this->m_pBattleFieldAttr[3]), (int)(1));
  (((PalScript *)this->m_pBattleFieldAttr[3]))->PalScript::OpenScript("ui\\combat\\control\\defence3.tga", 0);
}

// 0x00519A10
void CCBUI::WriteNimbusToPlayerMgr()
{
  NameSys *Sys; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x408] [ebp-0x40C] BYREF
  int v5; // [esp+0x810] [ebp-0x4]
  NameSys **v6; // [esp+0x818] [ebp+0x4]
  int v7; // [esp+0x81C] [ebp+0x8]
  int v8; // [esp+0x820] [ebp+0xC]
  int v9; // [esp+0x824] [ebp+0x10]

  v5 = 0;
  if ( operator new(0x158u) )
    Sys = (NameSys *)NameSys::GetSys();
  else
    Sys = 0;
  v5 = -1;
  *v6 = Sys;
  if ( !Sys )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_7, 2306),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void ( **)(NameSys *, int, int, CCBUI *, int, int, _DWORD))(*(_DWORD *)Sys->m_Flag + 28))(
    Sys,
    v7,
    v8,
    this,
    v9,
    1,
    0);
}

// 0x00519BB0
void CCBUI::Render()
{
  this->m_pBattleFieldAttr[0] = 0;
  this->m_pBattleFieldAttr[1] = 0;
  this->m_pBattleFieldAttr[2] = 0;
  this->m_pAttackSequenBack = ((UIStatic *)0);
  this->pPanel = ((UIStatic *)0);
  this->m_pBattleFieldAttr[3] = 0;
  this->m_pBattleFieldAttr[4] = 0;
  this->m_pBattleFieldAttr[5] = 0;
}

// 0x00519BD0
bool CCBUI::CreateButton(int parent, int id, int rc, int picname, UIButton **a5)
{
  _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v7; // esp
  UIFrameContainer *v9; // eax
  UIStatic *v10; // eax
  int *v11; // ebx
  UIListBox **m_pBattleFieldAttr; // esi
  UIListBox *v13; // eax
  UIListBox *updated; // eax
  _DWORD *v15; // eax
  UIFrameContainer *v16; // eax
  UIStatic *v17; // eax
  _BYTE pExceptionObject[1040]; // [esp+0x40] [ebp-0x100C] BYREF
  char v20; // [esp+0x450] [ebp-BFCh] BYREF
  char v21[1024]; // [esp+0x850] [ebp-0x7FC] BYREF
  char v22; // [esp+C50h] [ebp-0x3FC] BYREF
  _EXCEPTION_REGISTRATION_RECORD *v23; // [esp+0x1040] [ebp-0xC]
  void *v24; // [esp+0x1044] [ebp-0x8]
  int v25; // [esp+0x1048] [ebp-0x4]

  v25 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v24 = ((void*)0);
  v23 = (_EXCEPTION_REGISTRATION_RECORD *)ExceptionList;
  v7 = alloca(4120);
  this->UIWnd::Create(1879048193, (tagRECT *)parent, id);
  v9 = (UIFrameContainer *)operator new(0x98u);
  v25 = 0;
  if ( v9 )
    (((UIFrameContainer *)v9))->UIFrameContainer::ResetContainerState();
  else
    v10 = 0;
  v25 = -1;
  this->m_pAttackSequenBack = ((UIStatic *)(v10));
  if ( !v10 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&pExceptionObject[1024]))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 2366),
      0x400u);
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *(_DWORD *)parent = 0;
  *(_DWORD *)(parent + 8) = 249;
  *(_DWORD *)(parent + 4) = 0;
  *(_DWORD *)(parent + 12) = 206;
  (*(void ( **)(UIStatic *, int, int, CCBUI *))(*(_DWORD *)((UIWnd *)this->m_pAttackSequenBack) + 16))(
    this->m_pAttackSequenBack,
    131,
    parent,
    this);
  (((UIPushButton *)this->m_pAttackSequenBack))->UIPushButton::CreateFromTemplate(&unk_5DEF70, 0);
  (((UIScene *)this->m_pAttackSequenBack))->UIScene::SetShow(0);
  AllocObject(this->m_pAttackSequenBack);
  (((UIFrameWnd *)this->m_pAttackSequenBack))->UIFrameWnd::SetPosition(40,   150);
  (((UIFrameWnd *)this->m_pAttackSequenBack))->UIFrameWnd::SetPosition(0,   0);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pAttackSequenBack))((UIStatic *)(this->m_pAttackSequenBack), (int)(1));
  v11 = (int *)&g_nSkillItemIDTable[15];
  m_pBattleFieldAttr = (UIListBox **)this->m_pBattleFieldAttr;
  do
  {
    v13 = (UIListBox *)operator new(0x4B8u);
    if ( v13 )
      updated = (((UIListBox *)v13))->UIListBox::UpdateKeyCtrl();
    else
      updated = 0;
    *m_pBattleFieldAttr = updated;
    if ( !updated )
    {
      qmemcpy(
        &pExceptionObject[16],
        (((Logger *)&v20))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 2390),
        0x400u);
      _CxxThrowException(&pExceptionObject[16], (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *(_DWORD *)parent = 39;
    *(_DWORD *)(parent + 8) = 241;
    *(_DWORD *)(parent + 4) = 78;
    *(_DWORD *)(parent + 12) = 175;
    (*(void ( **)(UIListBox *, int, int, CCBUI *, _DWORD, int, _DWORD))(*(_DWORD *)((UIWnd *)(*m_pBattleFieldAttr))
                                                                                + 28))(
      *m_pBattleFieldAttr,
      *v11,
      parent,
      this,
      0,
      1,
      0);
    (**(void ( ***)(UIListBox *, int))((UIWnd *)(*m_pBattleFieldAttr)))((UIListBox *)(*m_pBattleFieldAttr), (int)(1));
    (((UIListBox *)*m_pBattleFieldAttr))->UIListBox::SetItemOffset(2, -4);
    (((UIListBox *)*m_pBattleFieldAttr))->UIListBox::SetColumnHead((int)"Name", 150);
    (((UIListBox *)*m_pBattleFieldAttr))->UIListBox::SetColumnHead((int)asc_5DFDB4, 43);
    (((UIListBox *)*m_pBattleFieldAttr))->UIListBox::SetLockSel(19);
    (((UIListBox *)*m_pBattleFieldAttr))->UIListBox::GetSel(g_nUnkDataTable[5], 0);
    UIListBox_SetItemData(1);
    v15 = (_DWORD *)sub_445FE0(pExceptionObject);
    *(_DWORD *)parent = (unsigned long)*v15;
    *(_DWORD *)(parent + 4) = (unsigned long)v15[1];
    *(_DWORD *)(parent + 8) = (unsigned long)v15[2];
    *(_DWORD *)(parent + 12) = (unsigned long)v15[3];
    (((UIListBox *)*m_pBattleFieldAttr))->UIListBox::GetLockSel((int)aUiCombatContro_8, (int *)parent, 16, 16, 0);
    (((CCBUI *)&(*m_pBattleFieldAttr)->m_scrollbar))->CCBUI::SetSelection(26);
    (((CCBUI *)&(*m_pBattleFieldAttr)->m_scrollbar))->CCBUI::SetCurPlayer(-5);
    (((CCBUI *)&(*m_pBattleFieldAttr)->m_scrollbar))->CCBUI::SetRoleStatePointers(-2);
    ++v11;
    ++m_pBattleFieldAttr;
  }
  while ( (int)v11 < (int)&g_nSkillItemIDTable[18] );
  this->CCBUI::ChangeSpecStateLum();
  v16 = (UIFrameContainer *)operator new(0x98u);
  if ( v16 )
    (((UIFrameContainer *)v16))->UIFrameContainer::ResetContainerState();
  else
    v17 = 0;
  this->pPanel = ((UIStatic *)(v17));
  if ( !v17 )
  {
    qmemcpy(v21, (((Logger *)&v22))->Logger::FormatException(&path[164], aDProjectPal3Co_7, 4346), sizeof(v21));
    _CxxThrowException(v21, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *(_DWORD *)parent = 37;
  *(_DWORD *)(parent + 8) = 237;
  *(_DWORD *)(parent + 4) = 170;
  *(_DWORD *)(parent + 12) = 210;
  (*(void ( **)(UIStatic *, int, int, CCBUI *))(*(_DWORD *)((UIWnd *)this->pPanel) + 16))(
    this->pPanel,
    131,
    parent,
    this);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->pPanel))((UIStatic *)(this->pPanel), (int)(1));
  this->CCBUI::GravityDown(0);
  return 1;
}

// 0x0051A0F0
void CCBUI::ChangeSpecStateLum()
{
  UIStatic **v2; // edi

  v2 = (UIStatic **)&this->m_pBattleFieldAttr[3];
  this->CCBUI::LineMove((POINT *)&this->m_pBattleFieldAttr[3], (POINT *)0xB5);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)(*v2)))((UIStatic *)(*v2), (int)(1));
  this->CCBUI::LineMove((POINT *)&this->m_pBattleFieldAttr[4], (POINT *)0xB6);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[4]))((UIStatic *)(this->m_pBattleFieldAttr[4]), (int)(1));
  this->CCBUI::LineMove((POINT *)&this->m_pBattleFieldAttr[5], (POINT *)0xB7);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[5]))((UIStatic *)(this->m_pBattleFieldAttr[5]), (int)(1));
}

// 0x0051A1D0
BOOL CCBUI::LineMove(POINT *pStart, POINT *pEnd)
{
  UIPushButton *v4; // eax
  int v5; // eax
  BOOL result; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x408] [ebp-0x40C] BYREF
  int v9; // [esp+0x810] [ebp-0x4]
  int v10; // [esp+0x820] [ebp+0xC]
  int v11; // [esp+0x824] [ebp+0x10]

  v4 = (UIPushButton *)operator new(0xF8u);
  v9 = 0;
  if ( v4 )
    v4->UIPushButton::UIPushButton();
  else
    v5 = 0;
  v9 = -1;
  pStart->x = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_7, 2575),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = (*(int ( **)(int, POINT *, int, CCBUI *, int, _DWORD))(*(_DWORD *)v5 + 28))(
             v5,
             pEnd,
             v10,
             this,
             v11,
             0);
  return 1;
}

// 0x0051A2B0
unsigned int CCBUI::GravityDown(unsigned int formal)
{
  int v3; // ebp
  UIStatic **m_pBattleFieldAttr; // edi
  UIStatic *v5; // eax
  UIStatic *v6; // eax
  UIStatic *v7; // eax
  UIStatic *v8; // eax
  unsigned int result; // eax

  v3 = 3;
  m_pBattleFieldAttr = (UIStatic **)this->m_pBattleFieldAttr;
  do
  {
    (**(void ( ***)(UIStatic *, _DWORD))((UIWnd *)(*m_pBattleFieldAttr)))((UIStatic *)(*m_pBattleFieldAttr), (_DWORD)(0));
    v5 = (UIStatic *)this->m_pBattleFieldAttr[3];
    ++m_pBattleFieldAttr;
    --v3;
    v5->m_ratioh = 0.0f;
    LOBYTE(v5->pDebugTex) = 0;
    v6 = (UIStatic *)this->m_pBattleFieldAttr[4];
    v6->m_ratioh = 0.0f;
    LOBYTE(v6->pDebugTex) = 0;
    v7 = (UIStatic *)this->m_pBattleFieldAttr[5];
    v7->m_ratioh = 0.0f;
    LOBYTE(v7->pDebugTex) = 0;
  }
  while ( v3 );
  switch ( formal )
  {
    case 0u:
      v8 = (UIStatic *)this->m_pBattleFieldAttr[3];
      goto LABEL_9;
    case 1u:
      v8 = (UIStatic *)this->m_pBattleFieldAttr[4];
      goto LABEL_9;
    case 2u:
      v8 = (UIStatic *)this->m_pBattleFieldAttr[5];
LABEL_9:
      LODWORD(v8->m_ratioh) = 1;
      LOBYTE(v8->pDebugTex) = 1;
      break;
  }
  SetEnable((UICaption *)this->m_pAttackSequenBack);
  SetEnable((UICaption *)this->pPanel);
  result = (**(int ( ***)(UIStatic *, int))((UIWnd *)this->m_pBattleFieldAttr[formal]))((UIStatic *)(this->m_pBattleFieldAttr[formal]), (int)(1));
  this->m_pAttackSequenFace[0] = (UIStatic *)formal;
  return result;
}

// 0x0051A340
unsigned int CCBUI::ChangeNumTxt()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  sub_51A400(this);
  return (unsigned int)this;
}

// 0x0051A430
BOOL CCBUI::AddTask(tagUITask *pTask, int nParam)
{
  UIFrameContainer *v4; // eax
  UIStatic *v5; // eax
  int *v6; // ebp
  UIListBox **p_pPanel; // esi
  UIListBox *v8; // eax
  UIListBox *updated; // eax
  char **v10; // eax
  BOOL result; // eax
  char a2[16]; // [esp+0x2C] [ebp-0x81C] BYREF
  char pExceptionObject[1024]; // [esp+0x3C] [ebp-0x80C] BYREF
  char ArgList[1024]; // [esp+0x43C] [ebp-0x40C] BYREF
  int v15; // [esp+0x844] [ebp-0x4]

  this->UIWnd::Create(1879048194, (tagRECT *)pTask, nParam);
  v4 = (UIFrameContainer *)operator new(0x98u);
  v15 = 0;
  if ( v4 )
    (((UIFrameContainer *)v4))->UIFrameContainer::ResetContainerState();
  else
    v5 = 0;
  v15 = -1;
  this->m_pAttackSequenBack = ((UIStatic *)(v5));
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 2678),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  pTask->fp[0] = 0;
  pTask->fp[2] = (char *)249;
  pTask->fp[1] = 0;
  pTask->fp[3] = (char *)206;
  (*(void ( **)(UIStatic *, int, tagUITask *, CCBUI *))(*(_DWORD *)((UIWnd *)this->m_pAttackSequenBack) + 16))(
    this->m_pAttackSequenBack,
    150,
    pTask,
    this);
  (((UIPushButton *)this->m_pAttackSequenBack))->UIPushButton::CreateFromTemplate(&unk_5DEF44, 0);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)this->m_pAttackSequenBack))((UIStatic *)(this->m_pAttackSequenBack), (int)(1));
  (((UIScene *)this->m_pAttackSequenBack))->UIScene::SetShow(0);
  AllocObject(this->m_pAttackSequenBack);
  (((UIFrameWnd *)this->m_pAttackSequenBack))->UIFrameWnd::SetPosition(40,   170);
  v6 = (int *)&g_nSkillItemIDTable[18];
  p_pPanel = (UIListBox **)&this->pPanel;
  do
  {
    v8 = (UIListBox *)operator new(0x4B8u);
    v15 = 1;
    if ( v8 )
      updated = (((UIListBox *)v8))->UIListBox::UpdateKeyCtrl();
    else
      updated = 0;
    v15 = -1;
    *p_pPanel = updated;
    if ( !updated )
    {
      qmemcpy(
        pExceptionObject,
        (((Logger *)ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], aDProjectPal3Co_7, 2700),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    pTask->fp[0] = (char *)39;
    pTask->fp[2] = (char *)241;
    pTask->fp[1] = (char *)78;
    pTask->fp[3] = (char *)175;
    (*(void ( **)(UIListBox *, int, tagUITask *, CCBUI *, _DWORD, int, _DWORD))(*(_DWORD *)((UIWnd *)(*p_pPanel))
                                                                                        + 28))(
      *p_pPanel,
      *v6,
      pTask,
      this,
      0,
      1,
      0);
    (**(void ( ***)(UIListBox *, _DWORD))((UIWnd *)(*p_pPanel)))((UIListBox *)(*p_pPanel), (_DWORD)(0));
    (((UIListBox *)*p_pPanel))->UIListBox::SetItemOffset(2, -4);
    (((UIListBox *)*p_pPanel))->UIListBox::SetColumnHead((int)"Name", 96);
    (((UIListBox *)*p_pPanel))->UIListBox::SetColumnHead((int)asc_5DFDCC, 37);
    (((UIListBox *)*p_pPanel))->UIListBox::SetColumnHead((int)asc_5DFDC0, 50);
    (((UIListBox *)*p_pPanel))->UIListBox::SetLockSel(19);
    (((UIListBox *)*p_pPanel))->UIListBox::GetSel(g_nUnkDataTable[9], 0);
    UIListBox_SetItemData(1);
    v10 = (char **)sub_445FE0(a2);
    pTask->fp[0] = *v10;
    pTask->fp[1] = v10[1];
    pTask->fp[2] = v10[2];
    pTask->fp[3] = v10[3];
    (((UIListBox *)*p_pPanel))->UIListBox::GetLockSel((int)aUiCombatContro_8, (int *)pTask, 16, 16, 0);
    (((CCBUI *)&(*p_pPanel)->m_scrollbar))->CCBUI::SetSelection(26);
    (((CCBUI *)&(*p_pPanel)->m_scrollbar))->CCBUI::SetCurPlayer(-5);
    (((CCBUI *)&(*p_pPanel)->m_scrollbar))->CCBUI::SetRoleStatePointers(-2);
    ++v6;
    ++p_pPanel;
  }
  while ( (int)v6 < (int)&g_nSkillItemIDTable[24] );
  ((CCBControlWindow *)this)->CCBControlWindow::CCBControlWindow();
  result = (BOOL)(((CCBControlWindow *)this))->CCBControlWindow::HandleInput(0) /* [ROWTABLE] */;
  return 1;
}

// 0x0051AB00
BOOL CCBUI::CheckMagicKeyPress(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(g_nSkillItemIDTable[18], -1, 0);
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x0051B8C0
void CCBUI::_todo_B8C0()
{
  int a2; // [esp+0x8] [ebp+0x4]
  int a3; // [esp+0xC] [ebp+0x8]

  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(g_nPropIDs_241[0], -1, 0);
  }
  (((SceneObj *)this))->SceneObj::Update(a2, a3) /* [ROWTABLE] */;
}

// 0x00525540
void CCBUI::InitShopUI()
{
  (((UIRoleDialog *)&this[37].m_Task[19].dwID))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)&this[37].m_Task[0].dwID))->UIRoleDialog::~UIRoleDialog();
  (((UIFrameContainer *)&this[2].m_Task[4].dwID))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[2].m_Task[2].fp[3]))->UIFrameContainer::~UIFrameContainer();
  UITextArea_Destroy();
  (((UIButton *)&this[2].m_pRoleStateBound[1]))->UIButton::~UIButton();
  (((UIFrameContainer *)&this[2].m_pRoleStateSleep[8]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[2].m_pRoleStateStable[3]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[2].m_pRoleStateLuckInc[9]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[2].m_pRoleStateAttackDec[4]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[2].m_pAttackSequenFace[2]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[1].fp))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[1].m_Task[17].fStartTime))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this[1].m_Task[15].bValid))->UIFrameContainer::~UIFrameContainer();
  (((PalScript *)&this[1].m_Task[10].param.fFromY))->PalScript::Reset();
  (((PalScript *)&this[1].m_Task[6].fStartTime))->PalScript::Reset();
  (((PalScript *)&this[1].m_Task[2].fp[1]))->PalScript::Reset();
  (((UICaption *)&this[1].m_pRoleStateImmunity[4]))->UICaption::Destroy2();
  (((UIPushButton *)&this[1].m_pRoleStateChaos[8]))->UIPushButton::~UIPushButton();
  (((UIPushButton *)&this[1].m_pRoleStateSpeedDec[1]))->UIPushButton::~UIPushButton();
  (((UIFrameContainer *)&this->m_Task[10]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Task[7].param.nTimes))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Task[5].param.fSpeed))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x005257B0
int * CCBUI::InitSkillUI(int nVal)
{
  int v3; // eax
  int v4; // eax
  float fStartTime; // edx
  UIStatic *v6; // eax
  int v7; // eax
  UIStatic *v8; // edx
  int v9; // edx
  UIStatic *v10; // edx
  UIStatic *v11; // edx
  UIStatic *v12; // edx
  float fSpeed; // edx
  int v14; // edx
  int v15; // ecx
  const char **v16; // ebp
  UIPushButton *v17; // edi
  char *fp; // edx
  int v19; // edx
  const char **v20; // ebp
  PalScript *v21; // edi
  int *v22; // ebx
  int v23; // ecx
  int v24; // eax
  int v25; // ecx
  int v26; // edx
  CCBFiveNimbusWindow *v27; // eax
  CUtil *v28; // edx
  int v29; // eax
  int v30; // edx
  char *v31; // edx
  char *v32; // ecx
  char *v33; // edx
  int v34; // ecx
  char **v35; // ebp
  int v36; // ebx
  int *p_fExpectStartTime; // ebp
  int v38; // ebx
  int nTimes; // edx
  int v40; // edx
  _DWORD *p_fEndX; // eax
  int v42; // ecx
  char *v43; // eax
  UIStatic *v44; // eax
  int v45; // eax
  int v47; // [esp+0x134] [ebp-D0h] BYREF
  int v48; // [esp+0x138] [ebp-CCh]
  int v49; // [esp+0x13C] [ebp-C8h]
  int v50; // [esp+0x140] [ebp-C4h]
  int v51; // [esp+0x144] [ebp-C0h] BYREF
  int v52; // [esp+0x148] [ebp-BCh]
  int v53; // [esp+0x14C] [ebp-B8h]
  int v54; // [esp+0x150] [ebp-B4h]
  int v55; // [esp+0x154] [ebp-B0h] BYREF
  int v56; // [esp+0x158] [ebp-ACh]
  int v57; // [esp+0x15C] [ebp-A8h]
  int v58; // [esp+0x160] [ebp-A4h]
  int v59; // [esp+0x164] [ebp-A0h] BYREF
  int v60; // [esp+0x168] [ebp-0x9C]
  int v61; // [esp+0x16C] [ebp-0x98]
  int v62; // [esp+0x170] [ebp-0x94]
  int v63; // [esp+0x174] [ebp-0x90] BYREF
  int v64; // [esp+0x178] [ebp-0x8C]
  int v65; // [esp+0x17C] [ebp-0x88]
  int v66; // [esp+0x180] [ebp-0x84]
  _DWORD v67[2]; // [esp+0x184] [ebp-0x80] BYREF
  int v68; // [esp+0x18C] [ebp-0x78]
  int v69; // [esp+0x190] [ebp-0x74]
  _DWORD v70[2]; // [esp+0x194] [ebp-0x70] BYREF
  int v71; // [esp+0x19C] [ebp-0x68]
  int v72; // [esp+0x1A0] [ebp-0x64]
  int v73; // [esp+0x1A4] [ebp-0x60]
  int v74; // [esp+0x1A8] [ebp-0x5C]
  int v75; // [esp+0x1AC] [ebp-0x58]
  int v76; // [esp+0x1B0] [ebp-0x54]
  _DWORD v77[4]; // [esp+0x1B4] [ebp-0x50] BYREF
  _DWORD v78[4]; // [esp+0x1C4] [ebp-0x40] BYREF
  _DWORD v79[4]; // [esp+0x1D4] [ebp-0x30] BYREF
  _DWORD v80[4]; // [esp+0x1E4] [ebp-0x20] BYREF
  _DWORD v81[4]; // [esp+0x1F4] [ebp-0x10] BYREF

  this->pPanel = ((UIStatic *)0);
  this->m_pAttackSequenBack = ((UIStatic *)0);
  this->m_pBattleFieldAttr[0] = this->m_pBattleFieldAttr[2];
  this->m_pBattleFieldAttr[1] = (UIStatic *)((char *)this->pPanel + (unsigned int)this->m_pBattleFieldAttr[3]);
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, (int)this->m_pAttackSequenBack, (int)this->pPanel, (int)this->m_pBattleFieldAttr[0], (int)this->m_pBattleFieldAttr[1]) /* [ROWTABLE] */;
  *(_DWORD *)&this[37].m_Task[0].bValid = nVal;
  v3 = *(_DWORD *)&this[1].m_Task[15].bValid;
  v52 = 32;
  v51 = 168;
  v53 = 636;
  v54 = 136;
  v4 = (*(int ( **)(_BYTE *, char *, int *, CCBUI *))(v3 + 16))(
         &this[1].m_Task[15].bValid,
         &g_PlayerAttBuffer._todo_074[140],
         &v51,
         this);
  LOBYTE(v4) = *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756);
  (((UIPushButton *)&this[1].m_Task[15].bValid))->UIPushButton::CreateFromTemplate("SubGame\\Appraise\\Exhibit\\ExhibitRemark.tga", v4);
  fStartTime = this[1].m_Task[17].fStartTime;
  v52 += 6;
  v51 += 24;
  v54 = v52 + 158;
  v53 = v51 + 428;
  (*(void ( **)(float *, char *, int *, CCBUI *))(LODWORD(fStartTime) + 16))(
    &this[1].m_Task[17].fStartTime,
    &g_PlayerAttBuffer._todo_074[140],
    &v51,
    this);
  (((UIScene *)&this[1].m_Task[17].fStartTime))->UIScene::SetShow(0);
  AllocObject(&this[1].m_Task[17].fStartTime);
  v6 = (UIStatic *)this[2].m_pRoleStateStable[3];
  v67[1] = 0;
  v67[0] = 0;
  v68 = 14;
  v69 = 600;
  v7 = ((int ( *)(UIStatic **, ARC_PlayerAtt *, _DWORD *, CCBUI *))v6->m_rect.left)(
         &this[2].m_pRoleStateStable[3],
         &g_PlayerAttBuffer,
         v67,
         this);
  LOBYTE(v7) = *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756);
  (((UIPushButton *)&this[2].m_pRoleStateStable[3]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\smt_Line.tga", v7);
  v8 = (UIStatic *)this[2].m_pRoleStateSleep[8];
  v67[0] = 786;
  v68 = 800;
  ((void ( *)(UIStatic **, ARC_PlayerAtt *, _DWORD *, CCBUI *))v8->m_rect.left)(
    &this[2].m_pRoleStateSleep[8],
    &g_PlayerAttBuffer,
    v67,
    this);
  LOBYTE(v9) = *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756);
  (((UIPushButton *)&this[2].m_pRoleStateSleep[8]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\smt_Line.tga", v9);
  v10 = (UIStatic *)this[2].m_pRoleStateBound[1];
  v80[1] = 0;
  v80[0] = 16;
  v80[2] = 788;
  v80[3] = 92;
  ((void ( *)(UIStatic **, char *, _DWORD *, CCBUI *))v10->m_rect.left)(
    &this[2].m_pRoleStateBound[1],
    &g_PlayerAttBuffer._todo_074[140],
    v80,
    this);
  (((UIScene *)&this[2].m_pRoleStateBound[1]))->UIScene::GetChildCount();
  (((UIScene *)&this[2].m_pRoleStateBound[1]))->UIScene::GetChildAt();
  sub_43FD90((float *)&this[2].m_pRoleStateBound[1], 0);
  (((UIScrollBar *)&this[2].m_pRoleStateBound[1]))->UIScrollBar::SetRange(620.0);
  this[2].m_pResultWaterLvup = (UIStatic *)1;
  this[2].m_pParabolaWindow = (CCBParabolaWindow *)300;
  this[2].m_pMain = (CCBControlWindow *)1092616192;
  this[2].m_pResultEarthLvup = (UIStatic *)255;
  (((UIProgressBar *)&this[2].m_pRoleStateBound[1]))->UIProgressBar::FindChildByName(620.0);
  this[2].m_pRoleStateImmunity[7] = (UIStatic *)1142620160;
  v11 = (UIStatic *)this[2].m_pAttackSequenFace[2];
  v64 = 18;
  v63 = 64;
  v65 = 96;
  v66 = 42;
  ((void ( *)(UIStatic **, char *, int *, CCBUI *))v11->m_rect.left)(
    &this[2].m_pAttackSequenFace[2],
    &g_PlayerAttBuffer._todo_074[140],
    &v63,
    this);
  v12 = (UIStatic *)this[2].m_pRoleStateAttackDec[4];
  v64 = v66;
  v66 += 24;
  ((void ( *)(UIStatic **, char *, int *, CCBUI *))v12->m_rect.left)(
    &this[2].m_pRoleStateAttackDec[4],
    &g_PlayerAttBuffer._todo_074[140],
    &v63,
    this);
  fSpeed = this->m_Task[5].param.fSpeed;
  v77[1] = 136;
  v77[0] = 90;
  v77[2] = 714;
  v77[3] = 598;
  (*(void ( **)(float *, char *, _DWORD *, CCBUI *))(LODWORD(fSpeed) + 16))(
    &this->m_Task[5].param.fSpeed,
    &g_PlayerAttBuffer._todo_074[140],
    (_DWORD *)(v77),
    this);
  LOBYTE(v14) = *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756);
  (((UIPushButton *)&this->m_Task[5].param.fSpeed))->UIPushButton::CreateFromTemplate("SubGame\\Appraise\\Do\\DoingBk.tga", v14);
  v70[1] = 162;
  v70[0] = 120;
  v71 = 160;
  v72 = 208;
  v16 = (const char **)&off_5706AC;
  v17 = (UIPushButton *)&this->m_pRoleStateDefenceDec[4];
  do
  {
    LOBYTE(v15) = *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756);
    (*(void ( **)(UIPushButton *, const char *, _DWORD *, CCBUI *, char *, int))(*(_DWORD *)((UIWnd *)v17) + 28))(
      v17,
      *v16,
      (_DWORD *)(v70),
      this,
      "SubGame\\Appraise\\Do\\queue",
      v15);
    (((UIPushButton *)v17))->UIPushButton::SetText();
    ++v16;
    v70[0] = v71;
    ++v17;
    v71 += 40;
  }
  while ( (int)v16 < (int)&off_5706C0 );
  fp = (char *)this[1].fp.fp;
  v78[1] = 170;
  v78[0] = 326;
  v78[2] = 482;
  v78[3] = 202;
  (*((void ( **)(CCBUI_funcptr_t *, char *, _DWORD *, CCBUI *))fp + 4))(
    &this[1].fp,
    &g_PlayerAttBuffer._todo_074[173],
    v78,
    this);
  (((UIScene *)&this[1].fp))->UIScene::SetShow(0);
  AllocObject(&this[1].fp);
  v56 = 146;
  v55 = 552;
  v57 = 597;
  v58 = 210;
  v20 = (const char **)&off_5706C0;
  v21 = (PalScript *)&this->m_Task[12].fp[2];
  v22 = (int *)&this[1].m_pRoleStateLuckDec[10];
  do
  {
    LOBYTE(v19) = *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756);
    v21->ShowWindow(*v20, &v55, this, "SubGame\\Appraise\\Do\\Magnifier", 0, v19);
    v23 = v56;
    *v22 = v55;
    v24 = v57;
    v22[1] = v23;
    v25 = v58;
    v22[2] = v24;
    v22[3] = v25;
    (((PalScript *)v21))->PalScript::OpenScript("SubGame\\Appraise\\Do\\unMagnifier.tga", *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756));
    v19 = v57;
    ++v20;
    v22 += 4;
    v21 = (PalScript *)((char *)v21 + 344);
    v55 = v57 + 2;
    v57 += 47;
  }
  while ( (int)v20 < (int)&off_5706CC );
  v26 = *(_DWORD *)&this[37].m_Task[0].bValid;
  v48 = 548;
  v47 = 213;
  v49 = 307;
  v50 = 568;
  LOBYTE(v26) = *(_BYTE *)(v26 + 1756);
  ((void ( *)(UIStatic **, char *, int *, CCBUI *, char *, int))this[1].m_pRoleStateSpeedDec[1]->m_rect.bottom)(
    &this[1].m_pRoleStateSpeedDec[1],
    &g_PlayerAttBuffer._todo_074[162],
    &v47,
    this,
    "SubGame\\Appraise\\Do\\Result",
    v26);
  v27 = (CCBFiveNimbusWindow *)v48;
  this[37].m_pResultWindow[3] = (CCBResultWindow *)v47;
  v28 = (CUtil *)v50;
  this[37].m_pFiveNimbusWindow = v27;
  v29 = v49;
  this[37].m_pCBSystem = (CCBSystem *)v49;
  v47 = v29 + 200;
  this[37].m_pUtil = v28;
  v30 = *(_DWORD *)&this[37].m_Task[0].bValid;
  v49 = v29 + 294;
  LOBYTE(v30) = *(_BYTE *)(v30 + 1756);
  ((void ( *)(UIStatic **, char *, int *, CCBUI *, char *, int))this[1].m_pRoleStateChaos[8]->m_rect.bottom)(
    &this[1].m_pRoleStateChaos[8],
    &g_PlayerAttBuffer._todo_074[163],
    &v47,
    this,
    "SubGame\\Appraise\\Do\\Result",
    v30);
  v31 = (char *)v48;
  v79[1] = 573;
  v79[0] = 358;
  v79[2] = 448;
  *((_DWORD *)&this[37].m_pUtil + 1) = v47;
  v32 = (char *)v49;
  v79[3] = 598;
  this[37].m_Task[0].fp[0] = v31;
  v33 = (char *)v50;
  this[37].m_Task[0].fp[1] = v32;
  v34 = *(_DWORD *)&this[37].m_Task[0].bValid;
  this[37].m_Task[0].fp[2] = v33;
  LOBYTE(v33) = *(_BYTE *)(v34 + 1756);
  ((void ( *)(UIStatic **, char *, _DWORD *, CCBUI *, char *, _DWORD, char *))this[1].m_pRoleStateImmunity[4]->m_rect.bottom)(
    &this[1].m_pRoleStateImmunity[4],
    &g_PlayerAttBuffer._todo_074[164],
    v79,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v33);
  ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[1].m_pRoleStateImmunity[4]))(
    &this[1].m_pRoleStateImmunity[4],
    0);
  (((CCBFiveNimbusWindow *)&this[1].m_Task[2].fp[1]))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&g_PlayerAttBuffer._todo_074[177], (int)this);
  (((CCBFiveNimbusWindow *)&this[1].m_Task[2].fp[1]))->CCBFiveNimbusWindow::SetFloatParam(600.0);
  (((Camera *)&this[1].m_Task[2].fp[1]))->Camera::UpdateCameraLookAt(400, 320);
  v35 = (char **)&this[1].m_Task[3].fp[2];
  v36 = 5;
  do
  {
    *v35 = 0;
    sub_43A090((int)&this[1].m_Task[2].fp[1], 1, 180.0);
    LODWORD(this[1].m_Task[5].fExpectEndTime) = 58;
    v35 += 8;
    --v36;
    ++this[1].m_Task[3].fp[0];
  }
  while ( v36 );
  (((CCBFiveNimbusWindow *)&this[1].m_Task[6].fStartTime))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&g_PlayerAttBuffer._todo_074[178], (int)this);
  (((CCBFiveNimbusWindow *)&this[1].m_Task[6].fStartTime))->CCBFiveNimbusWindow::SetFloatParam(600.0);
  (((Camera *)&this[1].m_Task[6].fStartTime))->Camera::UpdateCameraLookAt(400, 320);
  p_fExpectStartTime = (int *)&this[1].m_Task[7].fExpectStartTime;
  v38 = 5;
  do
  {
    *p_fExpectStartTime = 0;
    sub_43A090((int)&this[1].m_Task[6].fStartTime, 1, 180.0);
    LODWORD(this[1].m_Task[9].param.fEndY) = 58;
    p_fExpectStartTime += 8;
    --v38;
    ++this[1].m_Task[7].dwID;
  }
  while ( v38 );
  nTimes = this->m_Task[7].param.nTimes;
  *((_DWORD *)&this[1].m_Task[14].param + 8) = -1029701632;
  this[1].m_Task[15].fp[2] = (char *)-1029701632;
  this[1].m_Task[14].param.nTimes = -1017380864;
  this[1].m_Task[15].fp[0] = 0;
  this[1].m_Task[15].fp[1] = (char *)1130102784;
  this[1].m_Task[15].fp[3] = 0;
  v60 = 136;
  v59 = 90;
  v61 = 716;
  v62 = 603;
  (*(void ( **)(int *, char *, int *, CCBUI *))(nTimes + 16))(
    &this->m_Task[7].param.nTimes,
    &g_PlayerAttBuffer._todo_074[165],
    &v59,
    this);
  LOBYTE(v40) = *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756);
  (((UIPushButton *)&this->m_Task[7].param.nTimes))->UIPushButton::CreateFromTemplate("SubGame\\Appraise\\Do\\ExhibitZoom.tga", v40);
  (*(void ( **)(int *, _DWORD))this->m_Task[7].param.nTimes)(&this->m_Task[7].param.nTimes, 0);
  (((CCBFiveNimbusWindow *)&this[1].m_Task[10].param.fFromY))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&g_PlayerAttBuffer._todo_074[179], (int)this);
  (((CCBFiveNimbusWindow *)&this[1].m_Task[10].param.fFromY))->CCBFiveNimbusWindow::SetFloatParam(580.0);
  (((Camera *)&this[1].m_Task[10].param.fFromY))->Camera::UpdateCameraLookAt(400, 346);
  p_fEndX = (_DWORD *)&this[1].m_Task[11].param.fEndX;
  v42 = 5;
  do
  {
    *p_fEndX = 0;
    p_fEndX += 8;
    --v42;
    ++LODWORD(this[1].m_Task[11].param.fFromX);
  }
  while ( v42 );
  v43 = (char *)this->m_Task[10].fp[0];
  v60 = 164;
  v59 = 326;
  v61 = 482;
  v62 = 196;
  (*((void ( **)(tagUITask *, char *, int *, CCBUI *))v43 + 4))(
    &this->m_Task[10],
    &g_PlayerAttBuffer._todo_074[165],
    &v59,
    this);
  (((UIScene *)&this->m_Task[10]))->UIScene::SetShow(0);
  AllocObject(&this->m_Task[10]);
  (*(void ( **)(tagUITask *, _DWORD))this->m_Task[10].fp[0])(&this->m_Task[10], 0);
  v44 = (UIStatic *)this[2].m_pRoleStateLuckInc[9];
  v81[1] = 158;
  v81[0] = 536;
  v81[2] = 581;
  v81[3] = 208;
  v45 = ((int ( *)(UIStatic **, char *, _DWORD *, CCBUI *))v44->m_rect.left)(
          &this[2].m_pRoleStateLuckInc[9],
          &g_PlayerAttBuffer._todo_074[140],
          v81,
          this);
  LOBYTE(v45) = *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756);
  (((UIPushButton *)&this[2].m_pRoleStateLuckInc[9]))->UIPushButton::CreateFromTemplate("SubGame\\Appraise\\Do\\Magnifier0.tga", v45);
  ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[2].m_pRoleStateLuckInc[9]))(&this[2].m_pRoleStateLuckInc[9], 0);
  v73 = 300;
  v76 = 300;
  this[2].m_pRoleStateWall[2] = (UIStatic *)45;
  this[2].m_pRoleStateWall[3] = (UIStatic *)50;
  v74 = 200;
  v75 = 500;
  Create__ovl_1((ARC_PlayerAtt *)&this[37].m_Task[0].dwID);
  (((UIItem *)&this[37].m_Task[0].dwID))->UIItem::SetData(31);
  AllocObject(&this[37].m_Task[0].dwID);
  Create__ovl_1((ARC_PlayerAtt *)&this[37].m_Task[19].dwID);
  (((UIItem *)&this[37].m_Task[19].dwID))->UIItem::SetData(31);
  AllocObject(&this[37].m_Task[19].dwID);
  this[2].m_pSkillWindow = (CCBSkillWindow *)120;
  this[2].m_pAIWindow = (CCBAIWindow *)534;
  this[2].m_pLineupWindow = (CCBLineupWindow *)420;
  this[2].m_pMagicWindow = (CCBMagicWindow *)278;
  (((UINote *)&this[2].m_pProtectWindow))->UINote::Create((int)&g_PlayerAttBuffer._todo_074[174], (int)&this[2].m_pMagicWindow, (int)this, "UI\\Flex\\Note");
  ((void ( *)(CCBProtectWindow **, _DWORD))((UIWnd *)this[2].m_pProtectWindow))(&this[2].m_pProtectWindow, 0);
  (*((void ( **)(char **, char *, CCBMagicWindow **, CCBUI *))this[2].m_Task[2].fp[3] + 4))(
    &this[2].m_Task[2].fp[3],
    &g_PlayerAttBuffer._todo_074[174],
    &this[2].m_pMagicWindow,
    this);
  (((UIScene *)&this[2].m_Task[2].fp[3]))->UIScene::SetShow(0);
  AllocObject(&this[2].m_Task[2].fp[3]);
  (*(void ( **)(char **, _DWORD))this[2].m_Task[2].fp[3])(&this[2].m_Task[2].fp[3], 0);
  (*(void ( **)(unsigned int *, char *, CCBMagicWindow **, CCBUI *))(this[2].m_Task[4].dwID + 16))(
    &this[2].m_Task[4].dwID,
    &g_PlayerAttBuffer._todo_074[175],
    &this[2].m_pMagicWindow,
    this);
  (((UIScene *)&this[2].m_Task[4].dwID))->UIScene::SetShow(0);
  (*(void ( **)(unsigned int *, _DWORD))this[2].m_Task[4].dwID)(&this[2].m_Task[4].dwID, 0);
  return (int *)AllocObject(&this[2].m_Task[4].dwID);
}

// 0x00526660
int CCBUI::CCBUI_Render(int nVal)
{
  CCBControlWindow *v1; // ecx
  CCBControlWindow *v2; // ebp
  int result; // eax
  RenderTarget *p_bottom; // esi
  int v5; // ebx
  RenderTarget *v6; // esi
  int v7; // ebx
  CCBMagicWindow *v8; // [esp+0x0] [ebp-0x10]

  v2 = (CCBControlWindow *)v1;
  (((CCBControlWindow *)v1))->CCBControlWindow::Render(v8);
  if ( LOBYTE(v2[506].m_rect.top) )
  {
    p_bottom = (RenderTarget *)&v2[184].m_rect.bottom;
    v5 = 36;
    do
    {
      if ( IsVisible((RenderTarget *)((char *)p_bottom - 21024)) )
        (((UIParticle *)&p_bottom[-106].m_fInvScale))->UIParticle::Apply(10);
      LOBYTE(result) = IsVisible(p_bottom);
      if ( (_BYTE)result )
        (((UIParticle *)p_bottom))->UIParticle::Apply(11);
      p_bottom = (RenderTarget *)((char *)p_bottom + 584);
      --v5;
    }
    while ( v5 );
    LOBYTE(v2[506].m_rect.top) = 0;
    BYTE2(v2[506].m_rect.top) = 1;
  }
  else if ( BYTE1(v2[506].m_rect.top) )
  {
    v6 = (RenderTarget *)(&v2[398].m_CurCtrl_2 + 3);
    v7 = 36;
    do
    {
      if ( IsVisible((RenderTarget *)((char *)v6 - 21024)) )
        (((UIParticle *)&v6[-106].m_fInvScale))->UIParticle::Apply(10);
      LOBYTE(result) = IsVisible(v6);
      if ( (_BYTE)result )
        (((UIParticle *)v6))->UIParticle::Apply(11);
      v6 = (RenderTarget *)((char *)v6 + 584);
      --v7;
    }
    while ( v7 );
    BYTE1(v2[506].m_rect.top) = 0;
    BYTE2(v2[506].m_rect.top) = 1;
  }
  else
  {
    LOBYTE(result) = BYTE2(v2[506].m_rect.top);
    if ( (_BYTE)result )
      return (((SaleUI *)v2))->SaleUI::ResetGridState();
  }
  return result;
}

// 0x00526740
int CCBUI::Update(int deltatime, int haveinput)
{
  UIStatic *TickCount; // eax
  UIStatic *v5; // eax
  unsigned int v6; // ecx
  UIStatic *v7; // eax
  UIStatic *v8; // eax
  int v9; // kr00_4
  int v10; // ecx
  UIStatic *v11; // edx
  float fValue; // [esp+0x4] [ebp-0x28]
  int v14; // [esp+0x8] [ebp-0x24]
  int v15; // [esp+0x8] [ebp-0x24]
  int v16; // [esp+0x8] [ebp-0x24]
  struct tagPOINT Point; // [esp+0x14] [ebp-0x18] BYREF
  _DWORD a2[4]; // [esp+0x1C] [ebp-0x10] BYREF

  if ( UIParabolaCtrl_GetState(v14) == 2 )
    CCBAttackSequen_AdvanceToNextSlot(v15);
  if ( UIParabolaCtrl_GetState(v15) == 2 )
  {
    if ( BYTE1(this[5].m_Task[8].fp[3]) )
      CCBUI_UpdateCaptions(v16);
    else
      LOBYTE(this[2].m_pRoleStateBound[0]) = 0;
  }
  if ( this[2].m_Task[1].param.nTimes == 2 )
    (*(void ( **)(char **, int))this[2].m_Task[2].fp[3])(&this[2].m_Task[2].fp[3], 1);
  if ( !LOBYTE(this[2].m_pRoleStateBound[0])
    && !BYTE2(this[5].m_Task[7].param.nTimes)
    && !BYTE1(this[5].m_Task[8].fp[3]) )
  {
    if ( !LOBYTE(this[2].m_pRoleStateWall[8]) )
    {
      TickCount = (UIStatic *)GetTickCount();
      this[2].m_pRoleStateWall[6] = TickCount;
      this[2].m_pRoleStateWall[7] = TickCount;
      LOBYTE(this[2].m_pRoleStateWall[8]) = 1;
    }
    v5 = (UIStatic *)GetTickCount();
    v6 = (char *)v5 - (char *)this[2].m_pRoleStateWall[7];
    this[2].m_pRoleStateWall[6] = v5;
    if ( v6 > 0x3E8 )
    {
      this[2].m_pRoleStateWall[7] = v5;
      LOBYTE(this[2].m_pRoleStateWall[8]) = 0;
      v7 = (UIStatic *)((char *)this[2].m_pRoleStateWall[10] - 1);
      this[2].m_pRoleStateWall[10] = v7;
      if ( (int)v7 < 0 )
      {
        v8 = (UIStatic *)this[2].m_pRoleStateWall[9];
        this[2].m_pRoleStateWall[10] = (UIStatic *)59;
        v8 = (UIStatic *)((char *)v8 - 1);
        this[2].m_pRoleStateWall[9] = v8;
        if ( (int)v8 < 0 )
        {
          this[2].m_pRoleStateWall[9] = 0;
          this[2].m_pRoleStateWall[10] = 0;
          LOBYTE(this[2].m_pRoleStateBound[0]) = 1;
          CCBUI_UpdateCaptions(v16);
        }
      }
      if ( LOBYTE(this[2].m_pRoleStateGP[2]) )
        this[2].m_pRoleStateImmunity[7] = (UIStatic *)1065353216;
      Point.x = 10 * ((int)((UIWnd *)this[2].m_pRoleStateWall[10]) + 2);
      fValue = (float)Point.x;
      (((UIProgressBar *)&this[2].m_pRoleStateBound[1]))->UIProgressBar::FindChildByName(fValue);
    }
  }
  CreateDigitPair(
    (int)this[2].m_pRoleStateWall[10],
    &this[2].m_pAttackSequenFace[2],
    &this[2].m_pRoleStateAttackDec[4],
    pszTexBase,
    *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1756));
  if ( LOBYTE(this[2].m_pRoleStateWall[4]) )
  {
    (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&Point);
    v9 = (int)this[2].m_pRoleStateWall[2];
    a2[2] = Point.x + v9 - v9 / 2;
    v10 = (int)this[2].m_pRoleStateWall[3];
    a2[0] = Point.x - v9 / 2;
    a2[1] = Point.y - v10 / 2;
    a2[3] = Point.y + v10 - v10 / 2;
    (((UIWnd *)((char *)this + 5712)))->UIWnd::sub_445FA0(a2);
    if ( (g_Input.KeyInfo[1].Data & 0xF) == 1 )
    {
      v11 = (UIStatic *)this[2].m_pRoleStateLuckInc[9];
      LOBYTE(this[2].m_pRoleStateWall[4]) = 0;
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)v11))(&this[2].m_pRoleStateLuckInc[9], 0);
      (((UIWnd *)((char *)this + 5712)))->UIWnd::sub_445FA0(&this[1].m_pRoleStateLuckDec[4 * (int)this[2].m_pRoleStateWall[5] + 10]);
      sub_445E50((int)&this->m_Task[12].fp[86 * (int)this[2].m_pRoleStateWall[5] + 2]);
    }
  }
  (((SceneObj *)this))->SceneObj::Update(deltatime, haveinput) /* [ROWTABLE] */;
  return 1;
}

// 0x00526A40
void CCBUI::_todo_526A40()
{
  ARC_PlayerAtt *v2; // edx
  float v3; // eax
  const char **v4; // ecx
  UIStatic *v5; // edi
  const char **v6; // ebp
  UIStatic *v7; // edx
  CScreenMode *v8; // eax
  CScreenMode *Instance; // eax
  char *v10; // eax
  UIStatic **v11; // ecx
  UIStatic **v12; // esi
  UIStatic *v13; // edx
  UIStatic *v14; // eax
  int v15; // ebp
  int *p_fExpectEndTime; // edi
  int v17; // edi
  char **v18; // ebp
  UIStatic *v19; // ecx
  char **v20; // esi
  int v21; // edi
  UIStatic *v22; // eax
  char **v23; // esi
  int v24; // edi
  const void *v25; // [esp-0x8] [ebp-0x24]
  char *v26; // [esp-0x8] [ebp-0x24]
  int v27; // [esp-0x4] [ebp-0x20]
  int v28; // [esp+0x0] [ebp-0x1C]
  int pConfig; // [esp+0x10] [ebp-0xC] BYREF
  int pOut2; // [esp+0x14] [ebp-0x8] BYREF
  int SkillNum; // [esp+0x18] [ebp-0x4]
  int a2; // [esp+0x20] [ebp+0x4]
  char **a2a; // [esp+0x20] [ebp+0x4]
  ARC_PlayerAtt *nMsg; // [esp+0x24] [ebp+0x8]
  int wParam; // [esp+0x28] [ebp+0xC]

  switch ( a2 )
  {
    case 1000:
      if ( nMsg )
      {
        (((PAL_GDB *)this))->PAL_GDB::RefreshPartyStats();
        MUIDialog_SetSlotCaption(LODWORD(this[5].m_Task[7].param.fSpeed));
        (((SaleUI *)this))->SaleUI::ResetGridState() /* [ROWTABLE] */;
      }
      return;
    case 1001:
      v2 = (ARC_PlayerAtt *)nMsg;
      v3 = 0.0f;
      v4 = (const char **)&off_5706AC;
      break;
    case 1002:
      if ( nMsg == (ARC_PlayerAtt *)&g_PlayerAttBuffer._todo_074[162] )
      {
        if ( !BYTE2(this[5].m_Task[7].param.nTimes) && !LOBYTE(this[2].m_pRoleStateWall[4]) )
          LOBYTE(this[37].m_Task[0].fp[3]) = 1;
      }
      else if ( (char *)nMsg - &g_PlayerAttBuffer._todo_074[162] == 1
             && !BYTE2(this[5].m_Task[7].param.nTimes)
             && !LOBYTE(this[2].m_pRoleStateWall[4]) )
      {
        BYTE1(this[37].m_Task[0].fp[3]) = 1;
      }
      return;
    case 1009:
      if ( nMsg == (ARC_PlayerAtt *)&g_PlayerAttBuffer._todo_074[174] )
      {
        if ( *(_BYTE *)(*(_DWORD *)&this[37].m_Task[0].bValid + 1740) )
        {
          v15 = 0;
          p_fExpectEndTime = (int *)&this[2].m_Task[6].fExpectEndTime;
          do
          {
            if ( *((_BYTE *)this[5].m_Task[8].fp + v15) )
            {
              v27 = (unsigned long)*p_fExpectEndTime;
              pOut2 = 0;
              SkillNum = 0;
              pConfig = v27;
              SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v27);
              pOut2 = 1;
              (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&pConfig);
            }
            ++v15;
            p_fExpectEndTime += 402;
          }
          while ( v15 < 5 );
        }
        (((CScreenMode *)*(CScreenMode **)&this[37].m_Task[0].bValid))->CScreenMode::InitSceneAudio(3);
      }
      return;
    case 1010:
      if ( BYTE2(this[5].m_Task[7].param.nTimes) )
      {
        (((UICoverFrm *)this))->UICoverFrm::ResetStarFrames(LODWORD(this[5].m_Task[7].param.fSpeed)) /* [ROWTABLE] */;
        this[1].m_Task[14].fExpectStartTime = 0;
        this[1].m_Task[14].fStartTime = 0.0f;
        this[1].m_Task[14].dwID = 0;
        v17 = 0;
        v18 = (char **)&this->m_Task[12].fp[2];
        do
        {
          if ( *((_BYTE *)this[1].m_pRoleStateSpeedDec + v17) )
            sub_445E50((int)v18);
          ++v17;
          v18 += 86;
        }
        while ( v17 < 3 );
      }
      return;
    case 1013:
      if ( nMsg == (ARC_PlayerAtt *)&g_PlayerAttBuffer._todo_074[177] )
      {
        if ( LOBYTE(this[2].m_pRoleStateWall[4]) )
        {
          (((UICoverFrm *)this))->UICoverFrm::UpdateClouds(0, LODWORD(this[5].m_Task[7].param.fSpeed)) /* [ROWTABLE] */;
          v22 = (UIStatic *)this[2].m_pRoleStateWall[5];
          v23 = (char **)&this->m_Task[12].fp[2];
          v24 = 3;
          *((_BYTE *)v23 + (_DWORD)v22 + 1080) = 0;
          do
          {
            sub_445E50((int)v23);
            v23 += 86;
            --v24;
          }
          while ( v24 );
        }
      }
      else if ( (char *)nMsg - &g_PlayerAttBuffer._todo_074[177] == 1 && LOBYTE(this[2].m_pRoleStateWall[4]) )
      {
        (((UICoverFrm *)this))->UICoverFrm::UpdateClouds(1, LODWORD(this[5].m_Task[7].param.fSpeed)) /* [ROWTABLE] */;
        v19 = (UIStatic *)this[2].m_pRoleStateWall[5];
        v20 = (char **)&this->m_Task[12].fp[2];
        v21 = 3;
        *((_BYTE *)v20 + (_DWORD)v19 + 1080) = 0;
        do
        {
          sub_445E50((int)v20);
          v20 += 86;
          --v21;
        }
        while ( v21 );
      }
      return;
    case 1016:
      if ( nMsg == (ARC_PlayerAtt *)&g_PlayerAttBuffer._todo_074[179] )
      {
        (((GRPinput *)&g_Input))->GRPinput::GetMousePos(&pConfig, &pOut2);
        *(float *)&this[1].m_Task[14].dwID = (double)pOut2 + *(float *)&this[1].m_Task[14].dwID;
        this[1].m_Task[14].fStartTime = (float)pConfig + this[1].m_Task[14].fStartTime;
      }
      return;
    default:
      this->UIWnd::OnMessage(a2, (int)nMsg, wParam);
      return;
  }
  do
  {
    if ( nMsg == (ARC_PlayerAtt *)*v4 )
    {
      if ( LOBYTE(this[2].m_pRoleStateWall[4]) )
      {
        v10 = (char *)this + 248 * LODWORD(v3);
        if ( v10[420] )
        {
          *((_DWORD *)v10 + 108) = 0;
          v10[420] = 0;
        }
        else
        {
          *((_DWORD *)v10 + 108) = 1;
          v10[420] = 1;
        }
        return;
      }
      if ( LOBYTE(this[5].m_Task[7].param.fEnergy) || BYTE2(this[5].m_Task[7].param.nTimes) )
      {
        if ( !*((_BYTE *)&this[5].m_Task[7].param.fEnergy + LODWORD(v3) + 1) )
        {
          v11 = (UIStatic **)&this->m_pRoleStateDefenceDec[62 * LODWORD(v3) + 4];
          v11[20] = 0;
          *((_BYTE *)v11 + 68) = 0;
        }
        if ( LODWORD(this[5].m_Task[7].param.fSpeed) == LODWORD(v3) )
        {
          v12 = (UIStatic **)&this->m_pRoleStateDefenceDec[62 * LODWORD(v3) + 4];
          v12[20] = (UIStatic *)1;
          *((_BYTE *)v12 + 68) = 1;
        }
        v26 = off_5E7ED8[0];
      }
      else if ( *((_BYTE *)&this[5].m_Task[7].param.fEnergy + LODWORD(v3) + 1) )
      {
        v26 = off_5E7ED8[0];
      }
      else
      {
        this[5].m_Task[7].param.fSpeed = v3;
        if ( (((CCBAttackSequen *)this))->CCBAttackSequen::FindSequenceSlot(SLODWORD(v3)) > 0 )
          MUIDialog_SetSlotCaption(LODWORD(this[5].m_Task[7].param.fSpeed));
LABEL_20:
        v26 = (char *)off_5E7ECC;
      }
LABEL_21:
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v26, 1);
      return;
    }
    ++v4;
    ++LODWORD(v3);
  }
  while ( (int)v4 < (int)&off_5706C0 );
  v5 = 0;
  v6 = (const char **)&off_5706C0;
  a2a = (char **)&this->m_Task[12].fp[2];
  do
  {
    if ( !LOBYTE(this[2].m_pRoleStateWall[4]) && v2 == (ARC_PlayerAtt *)*v6 )
    {
      if ( !BYTE2(this[5].m_Task[7].param.nTimes) )
      {
        v7 = (UIStatic *)this[2].m_pRoleStateLuckInc[9];
        LOBYTE(this[2].m_pRoleStateWall[4]) = 1;
        ((void ( *)(UIStatic **, int))((UIWnd *)v7))(&this[2].m_pRoleStateLuckInc[9], 1);
        this[2].m_pRoleStateWall[5] = v5;
        sub_445E50((int)a2a);
        this[1].m_Task[14].fExpectStartTime = 0;
        this[1].m_Task[14].fStartTime = 0.0f;
        this[1].m_Task[14].dwID = 0;
      }
      v25 = off_5E7ECC;
      v8 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v8))->CScreenMode::AudioSetPosition(v25, 1);
      v2 = (ARC_PlayerAtt *)nMsg;
    }
    ++v6;
    v5 = (UIStatic *)((char *)v5 + 1);
    a2a += 86;
  }
  while ( (int)v6 < (int)&off_5706CC );
  if ( v2 == (ARC_PlayerAtt *)&g_PlayerAttBuffer._todo_074[162] )
  {
    if ( BYTE2(this[5].m_Task[7].param.nTimes) )
      return;
    if ( LOBYTE(this[2].m_pRoleStateWall[4]) )
    {
      this[1].m_pRoleStateStable[10] = 0;
      LOBYTE(this[1].m_pRoleStateStable[7]) = 0;
    }
    LOBYTE(this[5].m_Task[7].param.fEnergy) = 1;
    this[1].m_pRoleStateMirror[6] = 0;
    LOBYTE(this[1].m_pRoleStateMirror[3]) = 0;
    ((void ( *)(UIStatic **, int))((UIWnd *)this[1].m_pRoleStateImmunity[4]))(&this[1].m_pRoleStateImmunity[4], 1);
    if ( this[5].m_Task[8].fp[2] )
      *((_BYTE *)this[5].m_Task[8].fp + LODWORD(this[5].m_Task[7].param.fSpeed)) = 0;
    else
      *((_BYTE *)this[5].m_Task[8].fp + LODWORD(this[5].m_Task[7].param.fSpeed)) = 1;
    if ( !LOBYTE(this[1].m_pRoleStateStable[7]) && !LOBYTE(this[1].m_pRoleStateMirror[3]) )
    {
      v14 = (UIStatic *)this[1].m_pRoleStateImmunity[4];
      LOBYTE(this[5].m_Task[7].param.fEnergy) = 0;
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)v14))(&this[1].m_pRoleStateImmunity[4], 0);
      *((_BYTE *)this[5].m_Task[8].fp + LODWORD(this[5].m_Task[7].param.fSpeed)) = 0;
    }
    goto LABEL_47;
  }
  if ( (char *)v2 - &g_PlayerAttBuffer._todo_074[162] == 1 )
  {
    if ( BYTE2(this[5].m_Task[7].param.nTimes) )
      return;
    if ( LOBYTE(this[2].m_pRoleStateWall[4]) )
    {
      this[1].m_pRoleStateMirror[6] = 0;
      LOBYTE(this[1].m_pRoleStateMirror[3]) = 0;
    }
    LOBYTE(this[5].m_Task[7].param.fEnergy) = 1;
    this[1].m_pRoleStateStable[10] = 0;
    LOBYTE(this[1].m_pRoleStateStable[7]) = 0;
    ((void ( *)(UIStatic **, int))((UIWnd *)this[1].m_pRoleStateImmunity[4]))(&this[1].m_pRoleStateImmunity[4], 1);
    if ( this[5].m_Task[8].fp[2] )
      *((_BYTE *)this[5].m_Task[8].fp + LODWORD(this[5].m_Task[7].param.fSpeed)) = 0;
    else
      *((_BYTE *)this[5].m_Task[8].fp + LODWORD(this[5].m_Task[7].param.fSpeed)) = 1;
    if ( !LOBYTE(this[1].m_pRoleStateStable[7]) && !LOBYTE(this[1].m_pRoleStateMirror[3]) )
    {
      v13 = (UIStatic *)this[1].m_pRoleStateImmunity[4];
      LOBYTE(this[5].m_Task[7].param.fEnergy) = 0;
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)v13))(&this[1].m_pRoleStateImmunity[4], 0);
      *((_BYTE *)this[5].m_Task[8].fp + LODWORD(this[5].m_Task[7].param.fSpeed)) = 0;
    }
LABEL_47:
    (((UICoverFrm *)this))->UICoverFrm::ResetStarFrames(LODWORD(this[5].m_Task[7].param.fSpeed)) /* [ROWTABLE] */;
    v26 = (char *)off_5E7ECC;
    goto LABEL_21;
  }
  if ( (char *)v2 - &g_PlayerAttBuffer._todo_074[162] == 2
    && !BYTE2(this[5].m_Task[7].param.nTimes)
    && !LOBYTE(this[2].m_pRoleStateWall[4]) )
  {
    CCBUI_PlayResultSound(v28);
    goto LABEL_20;
  }
}
