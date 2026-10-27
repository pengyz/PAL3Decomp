#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCBControl.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Combat/CCBUI.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "GameBase/GRPinput.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "UI/PropUI.h"
#include "Misc/PtrArray.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UIScenePanel.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern CHAR byte_DC6A3C[256];

// 0x0043BE30
CCBResultWindow::~CCBResultWindow()
{
  (((UIScene *)this))->UIScene::ReleaseTexture();
  this->UIWnd::~UIWnd();
}

// 0x00442E10
void CCBResultWindow::ctor()
{
  (((UIFrameContainer *)this))->UIFrameContainer::ResetContainerState();
  this->m_pMP = ((UIProgressBar *)((UIProgressBar *)1056964608));
  this->m_pHGM = ((UIStatic *)0);
  this->m_pHP = ((UIProgressBar *)0);
  this->m_pGP = ((UIProgressBar *)0);
  this->m_pUI = ((CCBUI *)0);
  LOBYTE(this->m_nIndex) = 0;
  *(_DWORD *)&this->m_bClosed = 0;
  this->m_pFace[9] = (UIStatic *)21;
}

// 0x00443190
void CCBResultWindow::Create()
{
  this->CCBResultWindow::ctor();
}

// 0x00444A20
CCBResultWindow::CCBResultWindow()
{
  UIProgressBar *m_pHGM_high; // eax

  (((UIFrameContainer *)this))->UIFrameContainer::ResetContainerState();
  this->m_pUI = ((CCBUI *)((CCBUI *)1065353216));
  LOBYTE(this->m_nIndex) = 0;
  BYTE1(this->m_nIndex) = 0;
  BYTE2(this->m_nIndex) = 0;
  *(_DWORD *)&this->m_bClosed = 0;
  this->m_pMP = ((UIProgressBar *)((UIProgressBar *)6));
  this->m_pHGM = ((UIStatic *)((UIStatic *)-1));
  m_pHGM_high = (UIProgressBar *)HIBYTE(this->m_pHGM);
  this->m_pGP = ((UIProgressBar *)(m_pHGM_high));
  this->m_pHP = ((UIProgressBar *)(m_pHGM_high));
}

// 0x00444D10
int CCBResultWindow::StartAnim()
{
  int result; // eax

  BYTE1(this->m_nIndex) = 1;
  BYTE2(this->m_nIndex) = 0;
  return result;
}

// 0x00444D20
void CCBResultWindow::SetDirty()
{
  BYTE2(this->m_nIndex) = 1;
}

// 0x00515CE0
int CCBResultWindow::FindChildByID(int nID)
{
  int result; // eax
  int v3; // edx

  result = (int)&this->m_pUI;
  v3 = 0;
  while ( !*(_BYTE *)(result + 20) || *(_DWORD *)result != nID )
  {
    ++v3;
    result += 88;
    if ( v3 >= 1024 )
    {
      return 0;
    }
  }
  return 1;
}

// 0x00519360
void CCBResultWindow::ShowLineupWindow(BOOL bShow)
{
  (((CCBUI *)this))->CCBUI::Release();
  if ( bShow )
    operator delete(this);
}

// 0x00519510
void CCBResultWindow::Destroy()
{
  UIStatic *m_pBack; // ecx
  UIStatic *m_pWind; // ecx
  UIStatic *m_pThunder; // ecx
  UIStatic *m_pWater; // ecx
  UIStatic *m_pFire; // ecx
  UIStatic *m_pEarth; // ecx
  UIStatic *m_pDouble; // ecx
  UIStatic *m_pEXP; // ecx
  UIStatic *m_pLevel; // ecx
  UIStatic *v11; // ecx
  UIStatic *v12; // ecx

  Destroy__ovl_03((int)this);
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pBack) + 20))(m_pBack, 1);
    this->m_pBack = ((UIStatic *)0);
  }
  m_pWind = (UIStatic *)this->m_pWind;
  if ( m_pWind )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pWind) + 20))(m_pWind, 1);
    this->m_pWind = ((UIStatic *)0);
  }
  m_pThunder = (UIStatic *)this->m_pThunder;
  if ( m_pThunder )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pThunder) + 20))(m_pThunder, 1);
    this->m_pThunder = ((UIStatic *)0);
  }
  m_pWater = (UIStatic *)this->m_pWater;
  if ( m_pWater )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pWater) + 20))(m_pWater, 1);
    this->m_pWater = ((UIStatic *)0);
  }
  m_pFire = (UIStatic *)this->m_pFire;
  if ( m_pFire )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pFire) + 20))(m_pFire, 1);
    this->m_pFire = ((UIStatic *)0);
  }
  m_pEarth = (UIStatic *)this->m_pEarth;
  if ( m_pEarth )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pEarth) + 20))(m_pEarth, 1);
    this->m_pEarth = ((UIStatic *)0);
  }
  m_pDouble = (UIStatic *)this->m_pDouble;
  if ( m_pDouble )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pDouble) + 20))(m_pDouble, 1);
    this->m_pDouble = ((UIStatic *)0);
  }
  m_pEXP = (UIStatic *)this->m_pEXP;
  if ( m_pEXP )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pEXP) + 20))(m_pEXP, 1);
    this->m_pEXP = ((UIStatic *)0);
  }
  m_pLevel = (UIStatic *)this->m_pLevel;
  if ( m_pLevel )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pLevel) + 20))(m_pLevel, 1);
    this->m_pLevel = ((UIStatic *)0);
  }
  v11 = (UIStatic *)this->m_pFace[0];
  if ( v11 )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)v11) + 20))(v11, 1);
    this->m_pFace[0] = 0;
  }
  v12 = (UIStatic *)this->m_pFace[1];
  if ( v12 )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)v12) + 20))(v12, 1);
    this->m_pFace[1] = 0;
  }
}

// 0x005195E0
int CCBResultWindow::OnMessage(int pt, unsigned int area, int nVal)
{
  CScreenMode *Instance; // eax

  if ( pt == 1001 )
  {
    if ( area >= 0x103 && area <= 0x10C )
    {
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa001", 1);
    }
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(area, nVal, 0);
  }
  else if ( pt == 1007 && nVal != -1 )
  {
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(area, nVal, 0);
  }
  return this->UIWnd::OnMessage(pt, area, nVal);
}

// 0x00519660
BOOL CCBResultWindow::IsImbibeNimbusNotFinish(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(g_nSkillItemIDTable[15], -1, 0);
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x0051F1B0
int CCBResultWindow::OnMessage(int nVal, int nVal2, int nVal3)
{
  CScreenMode *Instance; // eax
  int v7; // eax
  UIStatic *m_pWater; // esi
  UIWnd **v9; // ecx
  UIStatic *v10; // edi
  int v11; // edi
  char *v12; // ecx
  int v13; // edx
  int *v14; // ecx
  _BYTE *v15; // eax
  tagRECT *v16; // edi
  bool v17; // zf
  CScreenMode *v18; // eax
  void ( ***v19)(UIStatic **, int); // esi
  tagRECT *p_m_rect; // edi
  CScreenMode *v21; // eax
  CScreenMode *v22; // eax
  PalScriptMgr *v23; // ecx
  CScreenMode *v24; // eax
  LONG m_benable; // eax
  UIStatic *v26; // esi
  UIStatic *m_pWind; // eax
  UIStatic *m_pBack; // edx
  UIStatic *v29; // ecx
  LONG *p_bottom; // edx
  unsigned int v31; // eax
  char *v32; // edi
  char *v33; // esi
  char v34; // cl
  int v35; // eax
  LONG v36; // eax
  UIStatic *v37; // esi
  UIStatic *v38; // eax
  UIStatic *v39; // edx
  UIStatic *v40; // ecx
  LONG *v41; // edx
  unsigned int v42; // eax
  char *v43; // edi
  char *v44; // esi
  char v45; // cl
  int v46; // eax
  CScreenMode *v47; // eax
  char *p_m_bvisible; // ecx
  char *p_m_pDouble; // ecx
  CScreenMode *v50; // eax
  char *v51; // ecx
  void ( **v52)(int); // eax
  CScreenMode *v53; // eax
  UIStatic *m_nField_1490; // eax
  UIStatic *v55; // esi
  UIStatic *m_pEarth; // eax
  int pDebugTex_low; // ecx
  DWORD Time; // eax
  int v59; // esi
  UIStatic *v60; // eax
  signed int v61; // esi
  void *v62; // eax
  int ItemID; // eax
  int v64; // eax
  int v65; // eax
  int v66; // edx
  UIStatic **v67; // ecx
  int SkillNum; // esi
  int v69; // ecx
  int v70; // edx
  void *v71; // ecx
  signed int v72; // edi
  int v73; // eax
  int v74; // esi
  int v75; // esi
  signed int v76; // edi
  int v77; // eax
  int v78; // eax
  int v79; // edx
  UIStatic **v80; // ecx
  int v81; // eax
  int v82; // ecx
  char v83; // al
  int v84; // ecx
  int v85; // eax
  int v86; // edx
  int Size; // esi
  void *v88; // eax
  signed int v89; // edi
  int v90; // ecx
  _DWORD *v91; // eax
  int v92; // eax
  signed int v93; // esi
  int v94; // eax
  int v95; // eax
  int v96; // eax
  int v97; // ecx
  _DWORD *v98; // edx
  int v99; // esi
  UIStatic **v100; // ecx
  _BYTE *v101; // eax
  char v102; // cl
  int v103; // ecx
  int v104; // eax
  int v105; // edx
  int v106; // esi
  UIStatic *m_pFire; // esi
  UIStatic *v108; // esi
  const char *v109; // [esp-0x8] [ebp-0x38]
  const char *v110; // [esp-0x8] [ebp-0x38]
  const char *v111; // [esp-0x8] [ebp-0x38]
  const char *v112; // [esp-0x8] [ebp-0x38]
  const char *v113; // [esp-0x8] [ebp-0x38]
  const char *v114; // [esp-0x8] [ebp-0x38]
  const char *v115; // [esp-0x8] [ebp-0x38]
  const char *v116; // [esp-0x8] [ebp-0x38]
  int v117; // [esp-0x4] [ebp-0x34]
  void *v118; // [esp+0x0] [ebp-0x30]
  char pOut[12]; // [esp+0xC] [ebp-0x24] BYREF
  int v120; // [esp+0x18] [ebp-0x18]
  void *Block; // [esp+0x1C] [ebp-0x14]
  int v122; // [esp+0x20] [ebp-0x10]
  _DWORD *v123; // [esp+0x24] [ebp-0xC]
  const void *v124; // [esp+0x28] [ebp-0x8]
  signed int i; // [esp+0x2C] [ebp-0x4]
  int nVala; // [esp+0x38] [ebp+0x8]
  _DWORD *nValb; // [esp+0x38] [ebp+0x8]
  UIStatic **nValc; // [esp+0x38] [ebp+0x8]
  gbTexture **nVald; // [esp+0x38] [ebp+0x8]
  gbTexture **nVale; // [esp+0x38] [ebp+0x8]
  int nValf; // [esp+0x38] [ebp+0x8]
  int nValg; // [esp+0x38] [ebp+0x8]
  int nVal2a; // [esp+0x3C] [ebp+0xC]
  UIStatic **nVal2b; // [esp+0x3C] [ebp+0xC]
  UIStatic **nVal2c; // [esp+0x3C] [ebp+0xC]
  UIStatic **nVal2d; // [esp+0x3C] [ebp+0xC]
  void *nVal2f; // [esp+0x3C] [ebp+0xC]
  float nVal2g; // [esp+0x3C] [ebp+0xC]
  signed int nVal2e; // [esp+0x3C] [ebp+0xC]
  int nVal3a; // [esp+0x40] [ebp+0x10]
  int nVal3b; // [esp+0x40] [ebp+0x10]
  int nVal3c; // [esp+0x40] [ebp+0x10]
  int nVal3d; // [esp+0x40] [ebp+0x10]

  if ( nVal == 1000 )
  {
    if ( nVal2 )
    {
      m_nField_1490 = (UIStatic *)(((PalScriptMgr *)this[44].m_pEarth))->PalScriptMgr::Get_m_nField_1490();
      this[44].m_pFace[4] = m_nField_1490;
      this[1919].m_pGP = (UIProgressBar *)m_nField_1490;
      v55 = (UIStatic *)this[44].m_pFace[4];
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      switch ( (unsigned int)v55 )
      {
        case 0u:
        case 1u:
        case 2u:
        case 3u:
        case 4u:
          sub_445E50((int)&this[9].m_pFace[4]);
          sub_445E50((int)this[11].m_pFace);
          sub_445E50((int)&this[13].m_pEarth);
          sub_445E50((int)&this[14].m_pGP);
          break;
        default:
          break;
      }
      this[44].m_pFace[5] = (UIStatic *)(((CCBStage *)this[44].m_pEarth))->CCBStage::sub_525090(v118);
      nVal2f = (void *)this[44].m_pEarth[34].m_texty;
      this[1822].m_benable = (int)nVal2f;
      nVal2g = (float)(int)nVal2f * *(float *)&this[44].m_pFace[5][1].m_bfocus;
      this[1822].m_bfocus = (int)nVal2g;
      this[1919].m_pGP = (UIProgressBar *)this[44].m_pFace[4];
      this[1919].m_pHGM = (UIStatic *)this[1822].m_benable;
      qmemcpy(&this[1919].m_pMP, this[44].m_pFace[5], 0xDCu);
      m_pEarth = (UIStatic *)this[44].m_pEarth;
      pDebugTex_low = LOBYTE(m_pEarth[25].pDebugTex);
      LOBYTE(m_pEarth[25].pDebugTex) = 0;
      if ( (_BYTE)pDebugTex_low )
      {
        nVal3d = 0;
        while ( 1 )
        {
          Time = timeGetTime();
          CRT_set_new_handler(Time);
          memset(g_CCBProtectData, 0, 0x30u);
          v59 = 0;
          nVal2e = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillID();
          v60 = (UIStatic *)this[44].m_pFace[5];
          if ( (int)v60->m_id > 0 )
            break;
LABEL_123:
          v61 = 0;
          v62 = 0;
          nValg = 0;
          Block = 0;
          if ( nVal2e > 0 )
          {
            do
            {
              ItemID = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(v61);
              if ( *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(ItemID) + 612) == 1 )
                Block = (char *)Block + 1;
              ++v61;
            }
            while ( v61 < nVal2e );
            v62 = (void *)Block;
          }
          v122 = 12 * nVal3d;
          if ( (int)v62 < *(_DWORD *)&g_CCBProtectData[12 * nVal3d] )
            *(_DWORD *)&g_CCBProtectData[12 * nVal3d] = (_DWORD)v62;
          for ( i = 0; i < nVal2e; ++i )
          {
            v64 = rand();
            v65 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(v64 % nVal2e);
            v66 = 0;
            if ( nValg <= 0 )
            {
LABEL_135:
              SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v65);
              v124 = (const void *)SkillNum;
              if ( *(int *)(SkillNum + 608) > 0 && *(_BYTE *)(SkillNum + 612) == 1 )
              {
                qmemcpy(
                  &this[44].m_pFace[13332 * nVal3d + 6] + 6666 * nVal3d + 202 * nValg,
                  (const void *)SkillNum,
                  0x320u);
                v69 = nValg + 50 * nVal3d;
                ++nValg;
                v70 = v122;
                qmemcpy(&this[2820].m_pbktex + 202 * v69, v124, 0x320u);
                if ( nValg >= *(_DWORD *)&g_CCBProtectData[v70] )
                  break;
              }
            }
            else
            {
              v67 = (UIStatic **)&this[44].m_pFace[19998 * nVal3d + 6];
              while ( (UIStatic *)v65 != *v67 )
              {
                ++v66;
                v67 += 202;
                if ( v66 >= nValg )
                  goto LABEL_135;
              }
            }
          }
          v71 = 0;
          v72 = 0;
          Block = 0;
          if ( nVal2e > 0 )
          {
            do
            {
              v73 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(v72);
              v74 = v73;
              if ( v73 != 6119
                && v73 != 6120
                && v73 != 6121
                && v73 != 6122
                && v73 != 6123
                && v73 != 6124
                && v73 != 6125
                && v73 != 6427
                && v73 != 6408
                && v73 != 6409
                && v73 != 6410
                && v73 != 6411
                && v73 != 6412
                && v73 != 6413
                && (*(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v73) + 612) == 2
                 || *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v74) + 612) == 3) )
              {
                Block = (char *)Block + 1;
              }
              ++v72;
            }
            while ( v72 < nVal2e );
            v71 = (void *)Block;
          }
          if ( (int)v71 < *(int *)((char *)&dword_17AD5C8 + v122) )
            *(int *)((char *)&dword_17AD5C8 + v122) = (int)v71;
          v123 = 0;
          i = 0;
          if ( nVal2e > 0 )
          {
            v75 = nVal3d;
            v76 = nVal2e;
            do
            {
              v77 = rand();
              v78 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(v77 % v76);
              if ( v78 != 6119
                && v78 != 6120
                && v78 != 6121
                && v78 != 6122
                && v78 != 6123
                && v78 != 6124
                && v78 != 6125
                && v78 != 6427
                && v78 != 6408
                && v78 != 6409
                && v78 != 6410
                && v78 != 6411
                && v78 != 6412
                && v78 != 6413 )
              {
                v79 = 0;
                if ( nValg <= 0 )
                {
LABEL_181:
                  v81 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v78);
                  v82 = *(_DWORD *)(v81 + 608);
                  v124 = (const void *)v81;
                  if ( v82 > 0 )
                  {
                    v83 = *(_BYTE *)(v81 + 612);
                    if ( v83 == 2 || v83 == 3 )
                    {
                      qmemcpy(&this[44].m_pFace[13332 * nVal3d + 6] + 6666 * nVal3d + 202 * nValg, v124, 0x320u);
                      v84 = nValg + 50 * nVal3d;
                      ++nValg;
                      v123 = (_DWORD *)((char *)v123 + 1);
                      v85 = (int)v123;
                      v86 = v122;
                      qmemcpy(&this[2820].m_pbktex + 202 * v84, v124, 0x320u);
                      if ( v85 >= *(int *)((char *)&dword_17AD5C8 + v86) )
                        break;
                      v76 = nVal2e;
                      v75 = nVal3d;
                    }
                  }
                }
                else
                {
                  v80 = (UIStatic **)&this[44].m_pFace[19998 * v75 + 6];
                  while ( (UIStatic *)v78 != *v80 )
                  {
                    ++v79;
                    v80 += 202;
                    if ( v79 >= nValg )
                      goto LABEL_181;
                  }
                }
              }
              ++i;
            }
            while ( i < v76 );
          }
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(4);
          Size = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize();
          v120 = Size;
          v88 = (void *)operator new(4 * Size);
          v89 = 0;
          Block = (void *)v88;
          if ( Size > 0 )
          {
            v123 = (_DWORD *)v88;
            do
            {
              v90 = *(_DWORD *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v89);
              v91 = (_DWORD *)v123;
              ++v89;
              *v123 = v90;
              v123 = (_DWORD *)(v91 + 1);
            }
            while ( v89 < Size );
          }
          v92 = 0;
          v93 = 0;
          v123 = 0;
          if ( nVal2e > 0 )
          {
            do
            {
              v94 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(v93);
              if ( *((_DWORD *)Block + v89) != v94
                && v94 != 6001
                && v94 != 6023
                && v94 != 6021
                && v94 != 6025
                && v94 != 6026
                && v94 != 6010
                && *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v94) + 612) == 4 )
              {
                v123 = (_DWORD *)((char *)v123 + 1);
              }
              ++v93;
            }
            while ( v93 < nVal2e );
            v92 = (int)v123;
          }
          if ( v92 < *(int *)((char *)&dword_17AD5CC + v122) )
            *(int *)((char *)&dword_17AD5CC + v122) = v92;
          v123 = 0;
          for ( i = 0; i < nVal2e; ++i )
          {
            v95 = rand();
            v96 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(v95 % nVal2e);
            v97 = 0;
            if ( v120 <= 0 )
            {
LABEL_209:
              if ( v96 != 6001 && v96 != 6023 && v96 != 6021 && v96 != 6025 && v96 != 6026 && v96 != 6010 )
              {
                v99 = 0;
                if ( nValg <= 0 )
                {
LABEL_219:
                  v101 = (_BYTE *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v96);
                  v102 = v101[612];
                  v124 = (void *)v101;
                  if ( v102 == 4 )
                  {
                    qmemcpy(&this[44].m_pFace[13332 * nVal3d + 6] + 6666 * nVal3d + 202 * nValg, v124, 0x320u);
                    v103 = nValg + 50 * nVal3d;
                    ++nValg;
                    v123 = (_DWORD *)((char *)v123 + 1);
                    v104 = (int)v123;
                    v105 = v122;
                    qmemcpy(&this[2820].m_pbktex + 202 * v103, v124, 0x320u);
                    if ( v104 >= *(int *)((char *)&dword_17AD5CC + v105) )
                      break;
                  }
                }
                else
                {
                  v100 = (UIStatic **)&this[44].m_pFace[19998 * nVal3d + 6];
                  while ( (UIStatic *)v96 != *v100 )
                  {
                    ++v99;
                    v100 += 202;
                    if ( v99 >= nValg )
                      goto LABEL_219;
                  }
                }
              }
            }
            else
            {
              v98 = (_DWORD *)Block;
              while ( v96 != *v98 )
              {
                ++v97;
                ++v98;
                if ( v97 >= v120 )
                  goto LABEL_209;
              }
            }
          }
          if ( Block )
            operator delete(Block);
          this[44].m_pFace[nVal3d] = (UIStatic *)nValg;
          *(&this[3718].m_rect.bottom + nVal3d) = nValg;
          this[1919].m_pFace[7] = 0;
          ++nVal3d;
          this[1919].m_pFace[8] = 0;
          this[1919].m_pFace[9] = 0;
          this[1919].m_pFace[10] = 0;
          if ( nVal3d >= 4 )
          {
            BYTE1(this[44].m_pLevel) = 0;
            switch ( (unsigned int)this[44].m_pFace[4] )
            {
              case 0u:
                sprintf(
                  (char *const)&this->m_pLevel,
                  "\\n    %s%s%s",
                  (const char *)&dword_DCF53C,
                  (const char *)&dword_DDB63C,
                  byte_DC6A3C);
                goto LABEL_231;
              case 1u:
                sprintf(
                  (char *const)&this->m_pLevel,
                  "\\n    %s%s%s",
                  (const char *)&dword_DCF53C,
                  (const char *)&dword_DDB53C,
                  byte_DC6A3C);
                goto LABEL_231;
              case 2u:
                sprintf(
                  (char *const)&this->m_pLevel,
                  "\\n    %s%s%s",
                  (const char *)&dword_DCF53C,
                  (const char *)&dword_DDB43C,
                  byte_DC6A3C);
                goto LABEL_231;
              case 3u:
                sprintf(
                  (char *const)&this->m_pLevel,
                  "\\n    %s%s%s",
                  (const char *)&dword_DCF53C,
                  (const char *)&dword_DDB33C,
                  byte_DC6A3C);
                goto LABEL_231;
              case 4u:
                sprintf(
                  (char *const)&this->m_pLevel,
                  "\\n    %s%s%s",
                  (const char *)&dword_DCF53C,
                  (const char *)&dword_DDB23C,
                  byte_DC6A3C);
LABEL_231:
                SetEnable((UICaption *)&this[3720].m_pGP);
                (((UIRoleSelect *)&this[3718].m_bfocus))->UIRoleSelect::SetByte(1);
                break;
              default:
                goto LABEL_232;
            }
            goto LABEL_232;
          }
        }
        nValf = 48 * nVal3d;
        while ( !CCBStage::CheckActionValid((__int64)(*(float *)((char *)&v60->m_rect.right + nValf) * 100.0)) )
        {
          if ( CCBStage::CheckActionValid((__int64)(*(float *)((char *)&this[44].m_pFace[5]->m_rect.bottom + nValf)
                                                  * 100.0)) )
          {
            ++*(&dword_17AD5C8 + 3 * nVal3d);
            goto LABEL_121;
          }
          if ( CCBStage::CheckActionValid((__int64)(*(float *)((char *)&this[44].m_pFace[5]->m_pfather + nValf) * 100.0)) )
          {
            ++*(&dword_17AD5CC + 3 * nVal3d);
            goto LABEL_121;
          }
LABEL_122:
          v60 = (UIStatic *)this[44].m_pFace[5];
          if ( v59 >= (int)v60->m_id )
            goto LABEL_123;
        }
        ++*(_DWORD *)&g_CCBProtectData[12 * nVal3d];
LABEL_121:
        ++v59;
        goto LABEL_122;
      }
LABEL_232:
      if ( (((PropUI *)this[44].m_pEXP))->PropUI::CheckMode(1u) )
      {
        this->m_pDouble = ((UIStatic *)0);
        if ( (int)this[1919].m_pFace[(int)this[1822].m_pFire + 7] > 0 )
        {
          do
          {
            v106 = 99 * (int)this[1822].m_pFire;
            *((_BYTE *)&this[49].m_pfather
            + 808 * v106
            + 808 * *((_DWORD *)&this[49].m_childs.m_pData + 202 * ((int)this->m_pDouble + v106))) = (((UIScenePanel *)this[44].m_pEXP))->UIScenePanel::ValidateIndex((int)this->m_pDouble);
            m_pFire = (UIStatic *)this[1822].m_pFire;
            *((_BYTE *)&this[2824].m_pFace[10100 * (_DWORD)m_pFire + 10]
            + 808 * *((_DWORD *)&this[49].m_childs.m_pData + 202 * ((int)this->m_pDouble + 99 * (_DWORD)m_pFire))) = (((UIScenePanel *)this[44].m_pEXP))->UIScenePanel::ValidateIndex((int)this->m_pDouble);
            *((_DWORD *)&this[49].m_childs.m_pData + 202 * ((int)this->m_pDouble + 99 * (int)this[1822].m_pFire)) = -1;
            v108 = (UIStatic *)((char *)((UIWnd *)this->m_pDouble) + 1);
            this->m_pDouble = ((UIStatic *)(v108));
          }
          while ( (int)v108 < (int)this[1919].m_pFace[(int)this[1822].m_pFire + 7] );
        }
      }
      BYTE2(this[44].m_pLevel) = 0;
    }
    return 1;
  }
  if ( nVal != 1001 )
    return this->UIWnd::OnMessage(nVal, nVal2, nVal3);
  switch ( nVal2 )
  {
    case 10492673:
      if ( LOBYTE(this[13].m_pGP) )
      {
        v109 = (const char *)off_5DFF94;
      }
      else
      {
        this[13].m_nIndex = 0;
        LOBYTE(this[13].m_pGP) = 0;
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[20].m_pFace[5]))(&this[20].m_pFace[5], 0);
        (*(void ( **)(tagRECT *, _DWORD))this[22].m_rect.left)(&this[22].m_rect, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[23].m_pWater))(&this[23].m_pWater, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[24].m_pHGM))(&this[24].m_pHGM, 0);
        (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
        (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[30].m_pDouble))(&this[30].m_pDouble, 0);
        ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
        (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[34].m_pFace[7]))(&this[34].m_pFace[7], 0);
        (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
        (**(void ( ***)(_BYTE *, _DWORD))&this[38].m_bClosed)((_BYTE *)(&this[38].m_bClosed), (_DWORD)(0));
        (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
        (*(void ( **)(LONG *, _DWORD))this[43].m_rect.top)(&this[43].m_rect.top, 0);
        this[21].m_rect.bottom = 0;
        LOBYTE(this[21].m_rect.left) = 0;
        this[22].m_pDouble = ((UIStatic *)0);
        LOBYTE(this[22].m_pWater) = 0;
        this[23].m_pMP = ((UIProgressBar *)0);
        LOBYTE(this[23].m_pHGM) = 0;
        this[25].m_bcreateok = 0;
        LOBYTE(this[25].m_childs.capacity) = 0;
        CUtil_Update(3);
        v109 = (const char *)off_5DFF88;
      }
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v109, 1);
      return 1;
    case 10492674:
      if ( LOBYTE(this[13].m_pGP) )
        goto LABEL_46;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[20].m_pFace[5]))(&this[20].m_pFace[5], 0);
      (*(void ( **)(tagRECT *, _DWORD))this[22].m_rect.left)(&this[22].m_rect, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[23].m_pWater))(&this[23].m_pWater, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[24].m_pHGM))(&this[24].m_pHGM, 0);
      (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
      (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[30].m_pDouble))(&this[30].m_pDouble, 0);
      ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
      (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[34].m_pFace[7]))(&this[34].m_pFace[7], 0);
      (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
      (**(void ( ***)(_BYTE *, _DWORD))&this[38].m_bClosed)((_BYTE *)(&this[38].m_bClosed), (_DWORD)(0));
      (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
      (*(void ( **)(LONG *, _DWORD))this[43].m_rect.top)(&this[43].m_rect.top, 0);
      v7 = 0;
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      m_pWater = (UIStatic *)this[1822].m_pWater;
      nVal2a = 0;
      nVala = 0;
      this[1919].m_pFace[(_DWORD)m_pWater + 7] = 0;
      if ( (int)this[44].m_pFace[(_DWORD)m_pWater] > 0 )
      {
        v9 = (UIWnd **)(&this[49].m_pfather + 19998 * (_DWORD)m_pWater);
        do
        {
          *((_BYTE *)v9 + 1) = 0;
          if ( !*(_BYTE *)v9 )
            ++nVala;
          ++v7;
          v9 += 202;
        }
        while ( v7 < (int)this[44].m_pFace[(_DWORD)m_pWater] );
      }
      v10 = (UIStatic *)this[44].m_pFace[5];
      nVal3a = 0;
      Block = *((void **)v10 + 4);
      Block = (char *)Block + rand() % (v10->m_rect.top - (int)Block);
      if ( (int)Block <= 0 )
        goto LABEL_32;
      break;
    case 10492675:
      v19 = (void ( ***)(UIStatic **, int))&this[20].m_pFace[5];
      if ( LOBYTE(this[13].m_pGP) )
      {
        (**v19)((UIStatic **)(&this[20].m_pFace[5]), (int)(1));
        p_m_rect = (tagRECT *)&this[22].m_rect;
        (*(void ( **)(tagRECT *, int))this[22].m_rect.left)(&this[22].m_rect, 1);
        nVal2b = (UIStatic **)&this[23].m_pWater;
        ((void ( *)(int))((UIWnd *)this[23].m_pWater))(1);
        nValc = (UIStatic **)&this[24].m_pHGM;
        ((void ( *)(int))((UIWnd *)this[24].m_pHGM))(1);
      }
      else
      {
        (**v19)((UIStatic **)(&this[20].m_pFace[5]), (int)(0));
        p_m_rect = (tagRECT *)&this[22].m_rect;
        (*(void ( **)(tagRECT *, _DWORD))this[22].m_rect.left)(&this[22].m_rect, 0);
        nVal2b = (UIStatic **)&this[23].m_pWater;
        ((void ( *)(_DWORD))((UIWnd *)this[23].m_pWater))(0);
        nValc = (UIStatic **)&this[24].m_pHGM;
        ((void ( *)(_DWORD))((UIWnd *)this[24].m_pHGM))(0);
        (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
        (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[30].m_pDouble))(&this[30].m_pDouble, 0);
        ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
        (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[34].m_pFace[7]))(&this[34].m_pFace[7], 0);
        (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
        (**(void ( ***)(_BYTE *, _DWORD))&this[38].m_bClosed)((_BYTE *)(&this[38].m_bClosed), (_DWORD)(0));
        (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
        (*(void ( **)(_DWORD))this[43].m_rect.top)(0);
      }
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      p_m_rect[5].left = 0;
      LOBYTE(p_m_rect[4].top) = 0;
      nVal2b[20] = 0;
      *((_BYTE *)nVal2b + 68) = 0;
      nValc[20] = 0;
      *((_BYTE *)nValc + 68) = 0;
      goto LABEL_59;
    case 10492676:
      if ( LOBYTE(this[13].m_pGP) )
        goto LABEL_46;
      if ( (int)this[44].m_pFace[4] >= 4 || *(&g_RoleSlotBuf.dword_17AA450 + 147) <= 0 )
      {
        sprintf(
          (char *const)&this->m_pLevel,
          "\\n        %s: %d, %s",
          (const char *)&dword_DC783C,
          *(&g_RoleSlotBuf.dword_17AA450 + 147),
          (const char *)&dword_DD373C);
        SetEnable((UICaption *)&this[3728].m_pFire);
        (((UIRoleSelect *)&this[3725].m_nIndex))->UIRoleSelect::SetByte(1);
        v111 = (const char *)off_5DFF90;
        v21 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v21))->CScreenMode::AudioSetPosition(v111, 1);
        return 1;
      }
      else
      {
        BYTE2(this[44].m_pLevel) = 1;
        this[13].m_nIndex = 0;
        LOBYTE(this[13].m_pGP) = 0;
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[20].m_pFace[5]))(&this[20].m_pFace[5], 0);
        (*(void ( **)(tagRECT *, _DWORD))this[22].m_rect.left)(&this[22].m_rect, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[23].m_pWater))(&this[23].m_pWater, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[24].m_pHGM))(&this[24].m_pHGM, 0);
        (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
        (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[30].m_pDouble))(&this[30].m_pDouble, 0);
        ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
        (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[34].m_pFace[7]))(&this[34].m_pFace[7], 0);
        (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
        (**(void ( ***)(_BYTE *, _DWORD))&this[38].m_bClosed)((_BYTE *)(&this[38].m_bClosed), (_DWORD)(0));
        (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
        (*(void ( **)(LONG *, _DWORD))this[43].m_rect.top)(&this[43].m_rect.top, 0);
        this[21].m_rect.bottom = 0;
        LOBYTE(this[21].m_rect.left) = 0;
        this[22].m_pDouble = ((UIStatic *)0);
        LOBYTE(this[22].m_pWater) = 0;
        this[23].m_pMP = ((UIProgressBar *)0);
        LOBYTE(this[23].m_pHGM) = 0;
        this[25].m_bcreateok = 0;
        LOBYTE(this[25].m_childs.capacity) = 0;
        CUtil_Update(1);
LABEL_59:
        v115 = (const char *)off_5DFF88;
        v50 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v50))->CScreenMode::AudioSetPosition(v115, 1);
        return 1;
      }
    case 10492677:
      if ( LOBYTE(this[13].m_pGP) )
      {
LABEL_46:
        v112 = (const char *)off_5DFF94;
        v22 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v22))->CScreenMode::AudioSetPosition(v112, 1);
        return 1;
      }
      else
      {
        CUtil_Update(5);
        (((PalScriptMgr *)v23))->PalScriptMgr::Destroy();
        v113 = (const char *)off_5DFF88;
        v24 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v24))->CScreenMode::AudioSetPosition(v113, 1);
        m_benable = this[1822].m_benable;
        v26 = (UIStatic *)this[44].m_pFace[5];
        this[2819].m_rect.right = (LONG)this[44].m_pFace[4];
        this[2819].m_rect.left = m_benable;
        m_pWind = (UIStatic *)this[1822].m_pWind;
        m_pBack = (UIStatic *)this[1822].m_pBack;
        nVal3b = 4;
        qmemcpy(&this[2819].m_rect.bottom, v26, 0xDCu);
        v29 = (UIStatic *)this[1822].m_pWater;
        this[3718].m_childs.m_needscriptdel = (int)m_pWind;
        this[3718].m_bvisible = (int)v29;
        this[3718].m_bcreateok = (int)this[1822].m_pThunder;
        this[3718].m_childs.m_nSize = (int)m_pBack;
        p_bottom = (LONG *)&this[3718].m_rect.bottom;
        nVald = (gbTexture **)&this[2820].m_pbktex;
        nVal2c = (UIStatic **)&this[44].m_pFace[6];
        do
        {
          ++p_bottom;
          v31 = 808 * this[44].m_pFace[5]->m_id;
          qmemcpy(nVald, nVal2c, 4 * (v31 >> 2));
          v33 = (char *)&nVal2c[v31 >> 2];
          v32 = (char *)&nVald[v31 >> 2];
          v34 = v31;
          v35 = nVal3b;
          qmemcpy(v32, v33, v34 & 3);
          *(p_bottom - 1) = *(p_bottom - 165311);
          nVal2c += 19998;
          nVald += 10100;
          --nVal3b;
        }
        while ( v35 != 1 );
        return 1;
      }
    case 10492680:
      if ( !this[44].m_pFace[5] )
        return 1;
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      v36 = this[1822].m_benable;
      v37 = (UIStatic *)this[44].m_pFace[5];
      this[2819].m_rect.right = (LONG)this[44].m_pFace[4];
      this[2819].m_rect.left = v36;
      v38 = (UIStatic *)this[1822].m_pWind;
      v39 = (UIStatic *)this[1822].m_pBack;
      qmemcpy(&this[2819].m_rect.bottom, v37, 0xDCu);
      v40 = (UIStatic *)this[1822].m_pWater;
      this[3718].m_childs.m_needscriptdel = (int)v38;
      this[3718].m_bvisible = (int)v40;
      this[3718].m_bcreateok = (int)this[1822].m_pThunder;
      this[3718].m_childs.m_nSize = (int)v39;
      v41 = (LONG *)&this[3718].m_rect.bottom;
      nVale = (gbTexture **)&this[2820].m_pbktex;
      nVal2d = (UIStatic **)&this[44].m_pFace[6];
      nVal3c = 4;
      do
      {
        ++v41;
        v42 = 808 * this[44].m_pFace[5]->m_id;
        qmemcpy(nVale, nVal2d, 4 * (v42 >> 2));
        v44 = (char *)&nVal2d[v42 >> 2];
        v43 = (char *)&nVale[v42 >> 2];
        v45 = v42;
        v46 = nVal3c;
        qmemcpy(v43, v44, v45 & 3);
        *(v41 - 1) = *(v41 - 165311);
        nVal2d += 19998;
        nVale += 10100;
        --nVal3c;
      }
      while ( v46 != 1 );
      CUtil_Update(5);
      v114 = (const char *)off_5DFF88;
      v47 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v47))->CScreenMode::AudioSetPosition(v114, 1);
      return 1;
    case 10492681:
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[30].m_pDouble))(&this[30].m_pDouble, 0);
      ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
      (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[34].m_pFace[7]))(&this[34].m_pFace[7], 0);
      (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
      (**(void ( ***)(_BYTE *, _DWORD))&this[38].m_bClosed)((_BYTE *)(&this[38].m_bClosed), (_DWORD)(0));
      (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
      (*(void ( **)(LONG *, _DWORD))this[43].m_rect.top)(&this[43].m_rect.top, 0);
      p_m_bvisible = (char *)&this[26].m_bvisible;
      if ( LOBYTE(this[21].m_rect.left) )
      {
        (**(void ( ***)(char *, int))p_m_bvisible)((char *)(p_m_bvisible), (int)(1));
        ((void ( *)(UIStatic **, int))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 1);
        (*(void ( **)(unsigned int *, int))this[29].m_id)(&this[29].m_id, 1);
        this[22].m_pDouble = ((UIStatic *)0);
        LOBYTE(this[22].m_pWater) = 0;
        this[23].m_pMP = ((UIProgressBar *)0);
        LOBYTE(this[23].m_pHGM) = 0;
        this[25].m_bcreateok = 0;
        LOBYTE(this[25].m_childs.capacity) = 0;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))p_m_bvisible)((char *)(p_m_bvisible), (_DWORD)(0));
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
        (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
      }
      goto LABEL_59;
    case 10492688:
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[34].m_pFace[7]))(&this[34].m_pFace[7], 0);
      (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
      (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
      (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
      (**(void ( ***)(_BYTE *, _DWORD))&this[38].m_bClosed)((_BYTE *)(&this[38].m_bClosed), (_DWORD)(0));
      (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
      (*(void ( **)(LONG *, _DWORD))this[43].m_rect.top)(&this[43].m_rect.top, 0);
      p_m_pDouble = (char *)&this[30].m_pDouble;
      if ( LOBYTE(this[22].m_pWater) )
      {
        (**(void ( ***)(char *, int))p_m_pDouble)((char *)(p_m_pDouble), (int)(1));
        ((void ( *)(UIProgressBar **, int))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 1);
        (*(void ( **)(int *, int))this[33].m_bcreateok)(&this[33].m_bcreateok, 1);
        this[21].m_rect.bottom = 0;
        LOBYTE(this[21].m_rect.left) = 0;
        this[23].m_pMP = ((UIProgressBar *)0);
        LOBYTE(this[23].m_pHGM) = 0;
        this[25].m_bcreateok = 0;
        LOBYTE(this[25].m_childs.capacity) = 0;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))p_m_pDouble)((char *)(p_m_pDouble), (_DWORD)(0));
        ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
        (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
      }
      goto LABEL_59;
    case 10492689:
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[30].m_pDouble))(&this[30].m_pDouble, 0);
      ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
      (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
      (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
      (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
      (**(void ( ***)(_BYTE *, _DWORD))&this[38].m_bClosed)((_BYTE *)(&this[38].m_bClosed), (_DWORD)(0));
      (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
      (*(void ( **)(LONG *, _DWORD))this[43].m_rect.top)(&this[43].m_rect.top, 0);
      v51 = (char *)&this[34].m_pFace[7];
      if ( LOBYTE(this[23].m_pHGM) )
      {
        (**(void ( ***)(char *, int))v51)((char *)(v51), (int)(1));
        (*(void ( **)(LONG *, int))this[36].m_rect.right)(&this[36].m_rect.right, 1);
        ((void ( *)(UIStatic **, int))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 1);
        this[21].m_rect.bottom = 0;
        LOBYTE(this[21].m_rect.left) = 0;
        this[22].m_pDouble = ((UIStatic *)0);
        LOBYTE(this[22].m_pWater) = 0;
        this[25].m_bcreateok = 0;
        LOBYTE(this[25].m_childs.capacity) = 0;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))v51)((char *)(v51), (_DWORD)(0));
        (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
      }
      goto LABEL_59;
    case 10492690:
      (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
      (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[30].m_pDouble))(&this[30].m_pDouble, 0);
      ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
      (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[34].m_pFace[7]))(&this[34].m_pFace[7], 0);
      (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
      v52 = *(void ( ***)(int))&this[38].m_bClosed;
      if ( LOBYTE(this[25].m_childs.capacity) )
      {
        (*v52)(1);
        (*(void ( **)(int *, int))this[40].m_bfocus)(&this[40].m_bfocus, 1);
        ((void ( *)(UIStatic **, int))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 1);
        (*(void ( **)(LONG *, int))this[43].m_rect.top)(&this[43].m_rect.top, 1);
        this[21].m_rect.bottom = 0;
        LOBYTE(this[21].m_rect.left) = 0;
        this[22].m_pDouble = ((UIStatic *)0);
        LOBYTE(this[22].m_pWater) = 0;
        this[23].m_pMP = ((UIProgressBar *)0);
        LOBYTE(this[23].m_pHGM) = 0;
      }
      else
      {
        (*v52)(0);
        (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
        ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
        (*(void ( **)(LONG *, _DWORD))this[43].m_rect.top)(&this[43].m_rect.top, 0);
      }
      goto LABEL_59;
    case 10492691:
      LOBYTE(this[28].m_id) = 0;
      this[28].m_rect.right = 0;
      this[29].m_pEarth = ((UIStatic *)0);
      LOBYTE(this[29].m_pThunder) = 0;
      this[1822].m_pBack = ((UIStatic *)0);
      if ( !LOBYTE(this[26].m_pFace[4]) )
      {
        this[1822].m_pBack = (UIStatic *)1;
        this[28].m_rect.right = 1;
        LOBYTE(this[28].m_id) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDA3C,
        (const char *)&dword_DCDE3C);
      goto LABEL_103;
    case 10492692:
      LOBYTE(this[26].m_pFace[4]) = 0;
      this[26].m_pFace[7] = 0;
      this[29].m_pEarth = ((UIStatic *)0);
      LOBYTE(this[29].m_pThunder) = 0;
      this[1822].m_pBack = (UIStatic *)1;
      if ( !LOBYTE(this[28].m_id) )
      {
        this[1822].m_pBack = (UIStatic *)1;
        this[28].m_rect.right = 1;
        LOBYTE(this[28].m_id) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDA3C,
        (const char *)&dword_DCDF3C);
      goto LABEL_103;
    case 10492693:
      LOBYTE(this[26].m_pFace[4]) = 0;
      this[26].m_pFace[7] = 0;
      this[28].m_rect.right = 0;
      LOBYTE(this[28].m_id) = 0;
      this[1822].m_pBack = (UIStatic *)2;
      if ( !LOBYTE(this[29].m_pThunder) )
      {
        this[1822].m_pBack = (UIStatic *)1;
        this[28].m_rect.right = 1;
        LOBYTE(this[28].m_id) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDA3C,
        (const char *)&dword_DCE03C);
      goto LABEL_107;
    case 10492694:
      LOBYTE(this[32].m_bcreateok) = 0;
      this[32].m_bfocus = 0;
      this[33].m_pFace[6] = 0;
      LOBYTE(this[33].m_pFace[3]) = 0;
      this[1822].m_pWind = ((UIStatic *)0);
      if ( !LOBYTE(this[30].m_pMP) )
      {
        this[1822].m_pWind = (UIStatic *)1;
        this[32].m_bfocus = 1;
        LOBYTE(this[32].m_bcreateok) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDB3C,
        (const char *)&dword_DCE13C);
      goto LABEL_103;
    case 10492695:
      LOBYTE(this[30].m_pMP) = 0;
      *(_DWORD *)&this[30].m_bClosed = 0;
      this[33].m_pFace[6] = 0;
      LOBYTE(this[33].m_pFace[3]) = 0;
      this[1822].m_pWind = (UIStatic *)1;
      if ( !LOBYTE(this[32].m_bcreateok) )
      {
        this[1822].m_pWind = (UIStatic *)1;
        this[32].m_bfocus = 1;
        LOBYTE(this[32].m_bcreateok) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDB3C,
        (const char *)&dword_DCE23C);
      goto LABEL_103;
    case 10492696:
      LOBYTE(this[30].m_pMP) = 0;
      *(_DWORD *)&this[30].m_bClosed = 0;
      this[32].m_bfocus = 0;
      LOBYTE(this[32].m_bcreateok) = 0;
      this[1822].m_pWind = (UIStatic *)2;
      if ( !LOBYTE(this[33].m_pFace[3]) )
      {
        this[1822].m_pWind = (UIStatic *)1;
        this[32].m_bfocus = 1;
        LOBYTE(this[32].m_bcreateok) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDB3C,
        (const char *)&dword_DCE33C);
      goto LABEL_107;
    case 10492697:
      LOBYTE(this[36].m_pEarth) = 0;
      this[36].m_pLevel = ((UIStatic *)0);
      this[37].m_nIndex = 0;
      LOBYTE(this[37].m_pGP) = 0;
      this[1822].m_pThunder = ((UIStatic *)0);
      if ( !LOBYTE(this[35].m_rect.right) )
      {
        this[1822].m_pThunder = (UIStatic *)1;
        this[36].m_pLevel = (UIStatic *)1;
        LOBYTE(this[36].m_pEarth) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDC3C,
        (const char *)&dword_DCE13C);
      goto LABEL_103;
    case 10492704:
      LOBYTE(this[35].m_rect.right) = 0;
      this[35].m_childs.m_pData = ((char *)0);
      this[37].m_nIndex = 0;
      LOBYTE(this[37].m_pGP) = 0;
      this[1822].m_pThunder = (UIStatic *)1;
      if ( !LOBYTE(this[36].m_pEarth) )
      {
        this[1822].m_pThunder = (UIStatic *)1;
        this[36].m_pLevel = (UIStatic *)1;
        LOBYTE(this[36].m_pEarth) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDC3C,
        (const char *)&dword_DCE23C);
      goto LABEL_103;
    case 10492705:
      LOBYTE(this[35].m_rect.right) = 0;
      this[35].m_childs.m_pData = ((char *)0);
      this[36].m_pLevel = ((UIStatic *)0);
      LOBYTE(this[36].m_pEarth) = 0;
      this[1822].m_pThunder = (UIStatic *)2;
      if ( !LOBYTE(this[37].m_pGP) )
      {
        this[1822].m_pThunder = (UIStatic *)1;
        this[36].m_pLevel = (UIStatic *)1;
        LOBYTE(this[36].m_pEarth) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n            %s: %s",
        (const char *)&dword_DCDC3C,
        (const char *)&dword_DCE33C);
      goto LABEL_107;
    case 10492706:
      LOBYTE(this[40].m_pFace[6]) = 0;
      this[40].m_pFace[9] = 0;
      this[42].m_pfather = ((UIWnd *)0);
      LOBYTE(this[42].m_rect.top) = 0;
      this[43].m_pEXP = ((UIStatic *)0);
      LOBYTE(this[43].m_pFire) = 0;
      this[1822].m_pWater = (UIStatic *)1;
      if ( !LOBYTE(this[39].m_bfocus) )
      {
        this[1822].m_pWater = ((UIStatic *)0);
        this[43].m_pEXP = (UIStatic *)1;
        LOBYTE(this[43].m_pFire) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n        %s: %s",
        (const char *)&dword_DCDD3C,
        (const char *)&dword_DCE43C);
      goto LABEL_103;
    case 10492707:
      LOBYTE(this[39].m_bfocus) = 0;
      this[39].m_pWind = ((UIStatic *)0);
      this[42].m_pfather = ((UIWnd *)0);
      LOBYTE(this[42].m_rect.top) = 0;
      this[43].m_pEXP = ((UIStatic *)0);
      LOBYTE(this[43].m_pFire) = 0;
      this[1822].m_pWater = (UIStatic *)2;
      if ( !LOBYTE(this[40].m_pFace[6]) )
      {
        this[1822].m_pWater = ((UIStatic *)0);
        this[43].m_pEXP = (UIStatic *)1;
        LOBYTE(this[43].m_pFire) = 1;
      }
      (((CCBStage *)this))->CCBStage::DispatchUpdate(0) /* [ROWTABLE] */;
      (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
      (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n        %s: %s",
        (const char *)&dword_DCDD3C,
        (const char *)&dword_DCE53C);
      goto LABEL_107;
    case 10492708:
      this[39].m_pWind = ((UIStatic *)0);
      LOBYTE(this[39].m_bfocus) = 0;
      this[40].m_pFace[9] = 0;
      LOBYTE(this[40].m_pFace[6]) = 0;
      this[43].m_pEXP = ((UIStatic *)0);
      LOBYTE(this[43].m_pFire) = 0;
      this[1822].m_pWater = (UIStatic *)3;
      if ( !LOBYTE(this[42].m_rect.top) )
      {
        this[1822].m_pWater = ((UIStatic *)0);
        this[43].m_pEXP = (UIStatic *)1;
        LOBYTE(this[43].m_pFire) = 1;
      }
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[20].m_pFace[5]))(&this[20].m_pFace[5], 0);
      (*(void ( **)(tagRECT *, _DWORD))this[22].m_rect.left)(&this[22].m_rect, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[23].m_pWater))(&this[23].m_pWater, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[24].m_pHGM))(&this[24].m_pHGM, 0);
      CCBStageRole_DispatchUpdate_1eb0(0);
      CCBStageRole_DispatchUpdate_1ef0(0);
      (((CCBStage *)this))->CCBStage::DispatchUpdateAll(0) /* [ROWTABLE] */;
      CCBStageRole_DispatchUpdate_1f70(0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n        %s: %s",
        (const char *)&dword_DCDD3C,
        (const char *)&dword_DCE63C);
LABEL_103:
      SetEnable((UICaption *)&this[3728].m_pFire);
      (((UIRoleSelect *)&this[3725].m_nIndex))->UIRoleSelect::SetByte(1);
      v116 = (const char *)off_5DFF88;
      v53 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v53))->CScreenMode::AudioSetPosition(v116, 1);
      return 1;
    case 10492709:
      this[39].m_pWind = ((UIStatic *)0);
      LOBYTE(this[39].m_bfocus) = 0;
      this[40].m_pFace[9] = 0;
      LOBYTE(this[40].m_pFace[6]) = 0;
      this[42].m_pfather = ((UIWnd *)0);
      LOBYTE(this[42].m_rect.top) = 0;
      this[1822].m_pWater = ((UIStatic *)0);
      if ( !LOBYTE(this[43].m_pFire) )
      {
        this[1822].m_pWater = ((UIStatic *)0);
        this[43].m_pEXP = (UIStatic *)1;
        LOBYTE(this[43].m_pFire) = 1;
      }
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[20].m_pFace[5]))(&this[20].m_pFace[5], 0);
      (*(void ( **)(tagRECT *, _DWORD))this[22].m_rect.left)(&this[22].m_rect, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[23].m_pWater))(&this[23].m_pWater, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[24].m_pHGM))(&this[24].m_pHGM, 0);
      (*(void ( **)(int *, _DWORD))this[26].m_bvisible)(&this[26].m_bvisible, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[27].m_pFace[4]))(&this[27].m_pFace[4], 0);
      (*(void ( **)(unsigned int *, _DWORD))this[29].m_id)(&this[29].m_id, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[30].m_pDouble))(&this[30].m_pDouble, 0);
      ((void ( *)(UIProgressBar **, _DWORD))((UIWnd *)this[31].m_pMP))(&this[31].m_pMP, 0);
      (*(void ( **)(int *, _DWORD))this[33].m_bcreateok)(&this[33].m_bcreateok, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[34].m_pFace[7]))(&this[34].m_pFace[7], 0);
      (*(void ( **)(LONG *, _DWORD))this[36].m_rect.right)(&this[36].m_rect.right, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[37].m_pEarth))(&this[37].m_pEarth, 0);
      (**(void ( ***)(_BYTE *, _DWORD))&this[38].m_bClosed)((_BYTE *)(&this[38].m_bClosed), (_DWORD)(0));
      (*(void ( **)(int *, _DWORD))this[40].m_bfocus)(&this[40].m_bfocus, 0);
      ((void ( *)(UIStatic **, _DWORD))((UIWnd *)this[41].m_pFace[6]))(&this[41].m_pFace[6], 0);
      (*(void ( **)(LONG *, _DWORD))this[43].m_rect.top)(&this[43].m_rect.top, 0);
      this[21].m_rect.bottom = 0;
      LOBYTE(this[21].m_rect.left) = 0;
      this[22].m_pDouble = ((UIStatic *)0);
      LOBYTE(this[22].m_pWater) = 0;
      this[23].m_pMP = ((UIProgressBar *)0);
      LOBYTE(this[23].m_pHGM) = 0;
      this[25].m_bcreateok = 0;
      LOBYTE(this[25].m_childs.capacity) = 0;
      this[13].m_nIndex = 0;
      LOBYTE(this[13].m_pGP) = 0;
      sprintf(
        (char *const)&this->m_pLevel,
        "\\n        %s: %s",
        (const char *)&dword_DCDD3C,
        (const char *)&dword_DCE73C);
LABEL_107:
      SetEnable((UICaption *)&this[3728].m_pFire);
      (((UIRoleSelect *)&this[3725].m_nIndex))->UIRoleSelect::SetByte(1);
      goto LABEL_59;
    default:
      return 1;
  }
  while ( nVala > 0 )
  {
    v11 = rand() % (int)this[44].m_pFace[(_DWORD)m_pWater];
    if ( nVala <= (int)Block )
    {
      v13 = 0;
      if ( (int)this[44].m_pFace[(_DWORD)m_pWater] > 0 )
      {
        v14 = (int *)&this[49].m_childs + 13332 * (_DWORD)m_pWater + 6666 * (_DWORD)m_pWater + 202 * nVal2a;
        v15 = (char *)&this[49].m_pfather + 79992 * (_DWORD)m_pWater + 1;
        do
        {
          if ( !*(v15 - 1) && !*v15 && *(_DWORD *)(v15 - 801) )
          {
            *v15 = 1;
            *v14 = v13;
            ++nVal2a;
            v14 += 202;
            ++this[1919].m_pFace[(_DWORD)m_pWater + 7];
          }
          ++v13;
          v15 += 808;
        }
        while ( v13 < (int)this[44].m_pFace[(_DWORD)m_pWater] );
      }
      break;
    }
    v12 = (char *)this + 79992 * (_DWORD)m_pWater + 808 * v11;
    if ( !v12[8852] && !v12[8853] && *((_DWORD *)v12 + 2013) )
    {
      v12[8853] = 1;
      *((_DWORD *)&this[49].m_childs.m_pData + 19998 * (_DWORD)m_pWater + 202 * nVal2a++) = v11;
      ++nVal3a;
      ++this[1919].m_pFace[(_DWORD)m_pWater + 7];
    }
    if ( nVal3a >= (int)Block )
      break;
  }
LABEL_32:
  this[1899].m_pFace[6] = (UIStatic *)nVal2a;
  if ( nVal2a > 0 )
  {
    v16 = (tagRECT *)&this[1913].m_rect;
    nValb = (_DWORD *)(&this[49].m_childs.m_pData + 19998 * (_DWORD)m_pWater);
    do
    {
      v117 = *((_DWORD *)&this[44].m_pFace[19998 * (_DWORD)m_pWater + 6] + 202 * *nValb);
      v16[-100].left = v117;
      v16->left = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v117);
      v16 = (tagRECT *)((char *)v16 + 4);
      v17 = nVal2a == 1;
      nValb += 202;
      --nVal2a;
    }
    while ( !v17 );
  }
  (((PropUI *)this[44].m_pEXP))->PropUI::SetPendingMessage(1, 1, this[44].m_pFace[5]->m_wndcolor.Color);
  (((PropUI *)this[44].m_pEXP))->PropUI::UpdateItemList(&this[1822].m_pEarth);
  this[1822].m_pFire = m_pWater;
  CUtil_Update(4);
  v110 = (const char *)off_5DFF88;
  v18 = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)v18))->CScreenMode::AudioSetPosition(v110, 1);
  return 1;
}
