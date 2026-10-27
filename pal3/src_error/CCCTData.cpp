#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCCTData.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBUI.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffect.h"
#include "Effect/CEffectSystem.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/InputSystem.h"
#include "GameBase/Logger.h"
#include "Role/NPC.h"
#include "Misc/NameSys.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget2.h"
#include "Script/ScriptSystem.h"
#include "Misc/UI3DCtrl.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIGameOver.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIRoleDialog.h"
#include "UI/UIWnd.h"
#include "Misc/tagCCT.h"
#include "Misc/tagCombatTaskData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_506340(...);

// Unnamed globals (extern)
void __cdecl nullsub_31(void);

// 0x0041C900
void CCCTData::CalcDist(float fVal, float fVal2)
{
  float v3; // st7
  float *v4; // ecx
  long double v5; // st6
  float v6; // st7
  float v7; // [esp+0x0] [ebp-0x10]
  float v8; // [esp+0x4] [ebp-0xC]
  float v9; // [esp+0x1C] [ebp+0xC]
  gbVec3D v10; // [esp+0x20] [ebp+0x10] BYREF
  int v11; // [esp+0x2C] [ebp+0x1C]
  int v12; // [esp+0x30] [ebp+0x20]

  v3 = v10.x - fVal;
  v4 = (float *)v11;
  v7 = v10.z - v9;
  v5 = atan2(-(v3 / v7), 1.0);
  *(float *)v11 = v5;
  if ( v10.z > (double)v9 )
    *v4 = v5 + 3.1415927;
  v8 = v3;
  v10.x = v8;
  v10.z = v7;
  *(float *)&v11 = v10.y - fVal2;
  LODWORD(v10.y) = v11;
  v6 = (((gbVec3D *)&v10))->gbVec3D::Length();
  *(float *)v12 = asin(*(float *)&v11 / v6);
}

// 0x0044D780
int CCCTData::InitEntries(float fVal)
{
  unsigned int v2; // ebp
  unsigned int *p_dwID; // esi
  float v4; // st7
  float v5; // st7
  float v6; // st7
  float v7; // st7
  int *v8; // eax
  unsigned int v9; // ebp
  float *p_fCircleEndY; // esi
  float v11; // st7
  float v12; // st7
  float v13; // st7
  float v14; // st7
  int *v15; // eax
  unsigned int v16; // ebp
  _inline_tagCam_yaw *p_yaw; // esi
  float v18; // st7
  float v19; // st7
  float v20; // st7
  float v21; // st7
  int *v22; // eax
  int result; // eax
  gbColorQuad v25; // [esp+0x34] [ebp-0x4] BYREF

  v2 = 0;
  p_dwID = (unsigned int *)&this->m_Pool[42].dwID;
  do
  {
    v4 = *(float *)p_dwID - g_fDefaultFOV * *((float *)p_dwID + 3) * fVal;
    *(float *)p_dwID = v4;
    *(p_dwID - 4) = (__int64)v4;
    *(p_dwID - 2) = (__int64)v4 + p_dwID[1];
    (((UIWnd *)(p_dwID - 42)))->UIWnd::sub_445FA0(p_dwID - 4);
    v5 = fVal * 30.0f * *((float *)p_dwID + 5);
    if ( *((_BYTE *)p_dwID + 24) )
    {
      v6 = *((float *)p_dwID + 4) - v5;
      *((float *)p_dwID + 4) = v6;
      if ( v6 <= 0.0f )
      {
        p_dwID[4] = 0;
        *((_BYTE *)p_dwID + 24) = 0;
      }
    }
    else
    {
      v7 = v5 + *((float *)p_dwID + 4);
      *((float *)p_dwID + 4) = v7;
      if ( v7 >= 255.0f )
      {
        p_dwID[4] = 1132396544;
        *((_BYTE *)p_dwID + 24) = 1;
      }
    }
    (((NPC *)(p_dwID - 42)))->NPC::UpdateAnim(*v8);
    if ( (int)*(p_dwID - 2) <= 150 )
      (((UIGameOver *)this))->UIGameOver::InitParticle2(v2);
    ++v2;
    p_dwID += 52;
  }
  while ( v2 < 0xA );
  v9 = 0;
  p_fCircleEndY = (float *)&this->m_Pool[25].fCircleEndY;
  do
  {
    v11 = *p_fCircleEndY - g_fDefaultFOV * p_fCircleEndY[3] * fVal;
    *p_fCircleEndY = v11;
    *((_DWORD *)p_fCircleEndY - 4) = (__int64)v11;
    *((_DWORD *)p_fCircleEndY - 2) = (__int64)v11 + *((_DWORD *)p_fCircleEndY + 1);
    (((UIWnd *)(p_fCircleEndY - 42)))->UIWnd::sub_445FA0(p_fCircleEndY - 4);
    v12 = fVal * 30.0f * p_fCircleEndY[5];
    if ( *((_BYTE *)p_fCircleEndY + 24) )
    {
      v13 = p_fCircleEndY[4] - v12;
      p_fCircleEndY[4] = v13;
      if ( v13 <= 0.0f )
      {
        p_fCircleEndY[4] = 0.0;
        *((_BYTE *)p_fCircleEndY + 24) = 0;
      }
    }
    else
    {
      v14 = v12 + p_fCircleEndY[4];
      p_fCircleEndY[4] = v14;
      if ( v14 >= 255.0f )
      {
        p_fCircleEndY[4] = 255.0;
        *((_BYTE *)p_fCircleEndY + 24) = 1;
      }
    }
    (((NPC *)(p_fCircleEndY - 42)))->NPC::UpdateAnim(*v15);
    if ( *((int *)p_fCircleEndY - 2) <= 150 )
      (((UIGameOver *)this))->UIGameOver::RandomizeEffects(v9);
    ++v9;
    p_fCircleEndY += 52;
  }
  while ( v9 < 0x10 );
  v16 = 0;
  p_yaw = (_inline_tagCam_yaw *)&this->m_Pool[3].EndPos.yaw;
  do
  {
    v18 = p_yaw->f - g_fDefaultFOV * p_yaw[3].f * fVal;
    p_yaw->f = v18;
    p_yaw[-4].p = (CEffMgr *)(__int64)v18;
    p_yaw[-2].p = (CEffMgr *)((char *)p_yaw[1].p + (__int64)v18);
    (((UIWnd *)&p_yaw[-42]))->UIWnd::sub_445FA0(&p_yaw[-4]);
    v19 = fVal * 30.0f * p_yaw[5].f;
    if ( LOBYTE(p_yaw[6].f) )
    {
      v20 = p_yaw[4].f - v19;
      p_yaw[4].f = v20;
      if ( v20 <= 0.0f )
      {
        p_yaw[4].p = 0;
        LOBYTE(p_yaw[6].f) = 0;
      }
    }
    else
    {
      v21 = v19 + p_yaw[4].f;
      p_yaw[4].f = v21;
      if ( v21 >= 255.0f )
      {
        p_yaw[4].p = (CEffMgr *)1132396544;
        LOBYTE(p_yaw[6].f) = 1;
      }
    }
    (((NPC *)&p_yaw[-42]))->NPC::UpdateAnim(*v22);
    if ( (int)p_yaw[-2].p <= 150 )
      result = (((UIGameOver *)this))->UIGameOver::InitParticle(v16);
    ++v16;
    p_yaw += 52;
  }
  while ( v16 < 0x16 );
  return result;
}

// 0x004533F0
int CCCTData::ProcessTask(int nVal)
{
  int v2; // edi
  int v3; // ebx
  unsigned __int8 v6; // al
  gbPrintFontMgr *pFontMgr; // edx
  gbPrintFont *v8; // ebp
  unsigned int *v9; // eax
  unsigned int v10; // edx
  int v11; // edx
  float v12; // st7
  unsigned __int8 *v13; // ecx
  int v14; // eax
  unsigned __int8 *v15; // ecx
  int v16; // ecx
  int v17; // eax
  float v18; // st7
  int v19; // edi
  gbGfxManager *pGfxMgr; // edx
  float v21; // st7
  char v22; // al
  char v23; // al
  char v24; // cl
  char v25; // dl
  char v26; // bl
  unsigned __int8 *v27; // ecx
  unsigned __int8 *v28; // ecx
  unsigned __int8 *v29; // edi
  unsigned __int8 *v30; // eax
  unsigned int dwID; // eax
  float fExpectTime; // ecx
  float v33; // [esp+0x10] [ebp-0x4C]
  float v34; // [esp+0x14] [ebp-0x48]
  __int16 v35; // [esp+0x30] [ebp-0x2C] BYREF
  char v36; // [esp+0x32] [ebp-0x2A]
  int v37; // [esp+0x34] [ebp-0x28]
  int v38; // [esp+0x38] [ebp-0x24]
  unsigned int v39; // [esp+0x3C] [ebp-0x20]
  unsigned int v40; // [esp+0x40] [ebp-0x1C]
  unsigned __int8 v41[4]; // [esp+0x44] [ebp-0x18]
  unsigned __int8 v42[4]; // [esp+0x48] [ebp-0x14]
  unsigned __int8 v43[4]; // [esp+0x4C] [ebp-0x10]
  int v44; // [esp+0x50] [ebp-0xC]
  unsigned __int8 v45[4]; // [esp+0x54] [ebp-0x8]
  gbColorQuad v46; // [esp+0x58] [ebp-0x4] BYREF

  v3 = 0;
  v44 = *(_DWORD *)(nVal + 8);
  v2 = v44;
  if ( v44 <= 0 )
    return 0;
  v45[0] = HIBYTE(this->m_Pool[0].fp[1]);
  v6 = BYTE2(this->m_Pool[0].fp[1]);
  pFontMgr = gfxMgr->pFontMgr;
  v43[0] = (unsigned __int8)this->m_Pool[0].fp[1];
  v8 = (gbPrintFont *)pFontMgr->pAllFont[2];
  v42[0] = BYTE1(this->m_Pool[0].fp[1]);
  v41[0] = v6;
  v10 = (unsigned long)*v9;
  v38 = 0;
  v8->curColor.Color = v10;
  v35 = 0;
  v36 = 0;
  v11 = 20;
  v37 = 0;
  v12 = 40.0f / (float)g_DrvInfo.height;
  *(_DWORD *)v43 = 20;
  *(_DWORD *)v41 = 0;
  v8->ScaleX = 40.0f / (float)g_DrvInfo.width;
  v8->ScaleY = v12;
  *(_DWORD *)v42 = 1;
  while ( 1 )
  {
    v13 = (unsigned __int8 *)&g_bActorFlag;
    v14 = *(_DWORD *)(nVal + 4);
    if ( v14 )
      v13 = (unsigned __int8 *)(v14 + v3);
    if ( *v13 == 92 )
      break;
LABEL_28:
    v27 = (unsigned __int8 *)&g_bActorFlag;
    v35 = 0;
    v36 = 0;
    if ( v14 )
      v27 = (unsigned __int8 *)(v14 + v3);
    if ( (char)*v27 <= 0 )
      goto LABEL_37;
    v28 = (unsigned __int8 *)&g_bActorFlag;
    if ( v14 )
      v28 = (unsigned __int8 *)(v14 + v3);
    if ( *v28 == 127 )
    {
LABEL_37:
      if ( *(int *)v42 >= v2 )
        goto LABEL_54;
      v29 = (unsigned __int8 *)&g_bActorFlag;
      if ( v14 )
        v29 = (unsigned __int8 *)(v14 + v3);
      LOBYTE(v35) = (unsigned long)*v29;
      if ( v14 )
        v30 = (unsigned __int8 *)(v14 + v3 + 1);
      else
        v30 = (unsigned __int8 *)&g_bActorFlag;
      HIBYTE(v35) = (unsigned long)*v30;
      *(_DWORD *)v41 = v3 + 1;
      ++*(_DWORD *)v42;
    }
    else if ( v14 )
    {
      LOBYTE(v35) = *(_BYTE *)(v3 + v14);
    }
    else
    {
      LOBYTE(v35) = g_bActorFlag;
    }
    *(_DWORD *)v45 = this->m_Pool[0].dwID + v38 * *(_DWORD *)v43 / 2;
    if ( (signed int)(*(_DWORD *)v45 + *(_DWORD *)v43 / 2 * strlen((const char *)&v35)) > SLODWORD(this->m_Pool[0].fStartTime) )
    {
      v38 = 0;
      dwID = this->m_Pool[0].dwID;
      v37 += *(_DWORD *)v43 + 2;
      *(_DWORD *)v45 = dwID;
    }
    fExpectTime = this->m_Pool[0].fExpectTime;
    v46.Color = v37 + *(_DWORD *)v43 + *(_DWORD *)&this->m_Pool[0].bValid;
    if ( (int)v46.Color > SLODWORD(fExpectTime) )
    {
      *(_DWORD *)v41 += 1 - strlen((const char *)&v35);
      v3 = *(_DWORD *)v41;
      goto LABEL_54;
    }
    v34 = 1.0f - ((float)(int)v46.Color + (float)(int)v46.Color) / (float)g_DrvInfo.height;
    v33 = ((float)*(int *)v45 + (float)*(int *)v45) / (float)g_DrvInfo.width - 1.0f;
    ((void ( *)(gbPrintFont *, __int16 *, _DWORD, _DWORD, int, int))v8->pGfxMgr->DrvInfo.subtype)(
      v8,
      &v35,
      LODWORD(v33),
      LODWORD(v34),
      1176256512,
      1176256512);
    v38 += strlen((const char *)&v35);
LABEL_48:
    v3 = *(_DWORD *)v41;
LABEL_49:
    *(_DWORD *)v41 = ++v3;
    ++*(_DWORD *)v42;
    if ( v3 >= v44 )
      goto LABEL_54;
    v2 = v44;
    v11 = *(_DWORD *)v43;
  }
  *(_DWORD *)v41 = ++v3;
  ++*(_DWORD *)v42;
  if ( v3 >= v2 )
  {
LABEL_54:
    ((void ( *)(gbPrintFont *))v8->pGfxMgr->hGfxWnd)(v8);
    return v3;
  }
  v15 = (unsigned __int8 *)&g_bActorFlag;
  if ( v14 )
    v15 = (unsigned __int8 *)(v14 + v3);
  switch ( *v15 )
  {
    case 'b':
      ((void ( *)(gbPrintFont *))v8->pGfxMgr->hGfxWnd)(v8);
      *(_DWORD *)v43 = 24;
      v38 = 0;
      v18 = 48.0f / (float)g_DrvInfo.height;
      v37 += 26;
      v17 = v37;
      v8->ScaleX = 48.0f / (float)g_DrvInfo.width;
      v8->ScaleY = v18;
      if ( *(_DWORD *)&this->m_Pool[0].bValid + v17 + 24 <= SLODWORD(this->m_Pool[0].fExpectTime) )
        goto LABEL_49;
      break;
    case 'i':
      v22 = HIBYTE(this->m_Pool[0].fp[1]);
      if ( gbColorQuad::ColorQuadFmt )
      {
        *(_WORD *)((char *)&v39 + 1) = -1;
        LOBYTE(v39) = 5;
      }
      else
      {
        *(_WORD *)((char *)&v39 + 1) = 1535;
        LOBYTE(v39) = -1;
      }
      HIBYTE(v39) = v22;
      v8->curColor.Color = v39;
      goto LABEL_49;
    case 'n':
      v16 = v11 + *(_DWORD *)&this->m_Pool[0].bValid;
      v38 = 0;
      v37 += v11 + 2;
      if ( v37 + v16 <= SLODWORD(this->m_Pool[0].fExpectTime) )
        goto LABEL_49;
      break;
    case 'p':
      break;
    case 'r':
      v23 = HIBYTE(this->m_Pool[0].fp[1]);
      v24 = (char)this->m_Pool[0].fp[1];
      v25 = BYTE1(this->m_Pool[0].fp[1]);
      v26 = BYTE2(this->m_Pool[0].fp[1]);
      if ( gbColorQuad::ColorQuadFmt )
      {
        BYTE2(v40) = (unsigned long)this->m_Pool[0].fp[1];
        BYTE1(v40) = v25;
        LOBYTE(v40) = v26;
      }
      else
      {
        BYTE2(v40) = BYTE2(this->m_Pool[0].fp[1]);
        BYTE1(v40) = v25;
        LOBYTE(v40) = v24;
      }
      HIBYTE(v40) = v23;
      v8->curColor.Color = v40;
      goto LABEL_48;
    case 's':
      v19 = v37 + v11 + 2;
      pGfxMgr = (gbGfxManager *)v8->pGfxMgr;
      v37 = v19;
      ((void ( *)(gbPrintFont *))pGfxMgr->hGfxWnd)(v8);
      *(_DWORD *)v43 = 20;
      v38 = 0;
      v21 = 40.0f / (float)g_DrvInfo.height;
      v8->ScaleX = 40.0f / (float)g_DrvInfo.width;
      v8->ScaleY = v21;
      if ( *(_DWORD *)&this->m_Pool[0].bValid + v19 + 20 <= SLODWORD(this->m_Pool[0].fExpectTime) )
        goto LABEL_49;
      break;
    case 't':
      v38 = 8 * ((v38 + 8) / 8);
      goto LABEL_49;
    default:
      v2 = v44;
      goto LABEL_28;
  }
  ((void ( *)(gbPrintFont *))v8->pGfxMgr->hGfxWnd)(v8);
  return v3 + 1;
}

// 0x004A6730
CCCTData * CCCTData::InitImages()
{
  char v3; // [esp+0xF] [ebp-0x11]

  ((gbImage2D *)&this->m_Pool[0].fp[1])->gbImage2D::gbImage2D();
  ((gbImage2D *)&this->m_Pool[1])->gbImage2D::gbImage2D();
  LOBYTE(this->m_Pool[2].fp[0]) = v3;
  this->m_Pool[2].fp[1] = 0;
  this->m_Pool[2].fp[2] = 0;
  this->m_Pool[2].fp[3] = 0;
  this->m_Pool[0].fp[0] = 0;
  this->m_Pool[1].dwReserved[1] = 0;
  LOBYTE(this->m_Pool[2].dwID) = 0;
  return this;
}

// 0x004A6F10
CCCTData::CCCTData()
{
  float *p_fCircleCentreX; // eax
  CHAR *v3; // ebp
  bool v4; // zf
  float *v5; // [esp+0x10] [ebp-0x18]
  int v6; // [esp+0x14] [ebp-0x14]

  ((UIListBox *)this)->UIListBox::UIListBox();
  *(_DWORD *)&this->m_Pool[0].bStartCamValid = 800;
  *(_DWORD *)&this->m_Pool[0].bLineMove = 600;
  *(_DWORD *)&this->m_Pool[0].bAbsoluteTime = 0;
  *(_DWORD *)&this->m_Pool[0].bRandSwing = 0;
  (((UIFrameContainer *)&this->m_Pool[1].fCircleEndZ))->UIFrameContainer::ResetContainerState();
  p_fCircleCentreX = (float *)&this->m_Pool[2].fCircleCentreX;
  v5 = (float *)&this->m_Pool[2].fCircleCentreX;
  v6 = 28;
  v3 = (CHAR *)&this->m_Pool[2].dwReserved[1];
  while ( 1 )
  {
    *p_fCircleCentreX = 0.0;
    lstrcpyA((char *)v3 - 32, unk_C10D38);
    lstrcpyA((char *)v3, unk_C10D38);
    memset(v3 + 532, 0, 0x18u);
    v3 += 760;
    v4 = v6 == 1;
    v5 += 190;
    --v6;
    if ( v4 )
      break;
    p_fCircleCentreX = (float *)v5;
  }
  BYTE1(this->m_Pool[107].fp[3]) = 0;
  BYTE2(this->m_Pool[107].fp[3]) = 1;
  HIBYTE(this->m_Pool[107].fp[3]) = 1;
  this->m_Pool[107].dwID = 0;
  *(_DWORD *)&this->m_Pool[107].bValid = 0;
  this->m_Pool[107].fStartTime = 180.0f;
  LODWORD(this->m_Pool[114].fStartTracePosY) = 300;
  this->m_Pool[114].fStartTracePosZ = 0.0f;
  this->m_Pool[114].dwReserved[0] = 0;
  (((UIFrameContainer *)&this->m_Pool[114].dwReserved[1]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[115].fCircleCentreZ))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[116].bAbsoluteTime))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[117].StartPos.yaw))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)this->m_Pool[117].dwReserved))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)&this->m_Pool[133].fEndFOV))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[134].fCircleCentreY))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[135].bLineMove))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[869].fCircleEndX))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[870].bRandSwing))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[871].StartPos.pit))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[871].dwReserved[1]))->UIFrameContainer::ResetContainerState();
  (((UIProgressBar *)&this->m_Pool[872].fCircleCentreZ))->UIProgressBar::ctor();
  (((UIProgressBar *)&this->m_Pool[874].StartPos.pit))->UIProgressBar::ctor();
  (((UIFrameContainer *)&this->m_Pool[875].fCircleEndX))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[876].bRandSwing))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[877].StartPos.pit))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  LOBYTE(this->m_Pool[907].dwReserved[1]) = 1;
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((CCCTData *)&this->m_Pool[1876].StartPos.z))->CCCTData::InitImages();
  LOBYTE(this->m_Pool[1878].EndPos.yaw.f) = 0;
  this->m_Pool[1878].EndPos.z = 0.0f;
  this->m_Pool[1878].EndPos.y = 0.0f;
  this->m_Pool[1878].bStartCamValid = 0;
  this->m_Pool[1878].nEndCam = 0;
  this->m_Pool[1878].nStartCam = 0;
  ((UI3DCtrl *)&this->m_Pool[1878].fStartTracePosY)->UI3DCtrl::UI3DCtrl();
  ((UI3DCtrl *)&this->m_Pool[1879].EndPos.yaw)->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)&this->m_Pool[1888].StartPos.y))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[1888].fStartTracePosY))->UIFrameContainer::ResetContainerState();
  ((UI3DCtrl *)&this->m_Pool[1889].fAngleSpeed)->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)&this->m_Pool[1890].dwID))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[1890].fSwing))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[1891].fAccelerationTime1))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[1892].EndPos.z))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[1893].fp[3]))->UIFrameContainer::ResetContainerState();
  (((UIListBox *)&this->m_Pool[1911].fCircleCentreX))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this->m_Pool[1917].fAcceleration1))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this->m_Pool[1923].fStartSpeed))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this->m_Pool[1929].bLineMove))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this->m_Pool[1935].EndPos.rol))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this->m_Pool[1941].EndPos.y))->UIListBox::UpdateKeyCtrl();
  (((UIFrameContainer *)&this->m_Pool[1947].EndPos.y))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[1948].fp[2]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[1948].fCircleEndZ))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Pool[1949].fAcceleration1))->UIFrameContainer::ResetContainerState();
  ((UI3DCtrl *)&this->m_Pool[1950].EndPos.pit)->UI3DCtrl::UI3DCtrl();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  this->m_Pool[1960].dwReserved[0] = 0;
  ScriptSystem::ClearTimerSlot();
  ((UIRoleDialog *)&this->m_Pool[1961].StartPos.y)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this->m_Pool[1967].fEndFOV)->UIRoleDialog::UIRoleDialog();
  g_nRoleParam = 0;
  g_nRoleState = 0;
  g_nActorState = 0;
  LOWORD(g_nActor_DE5FA8) = 0;
  LOBYTE(g_nActor_DE5F9C) = 0;
  this->m_Pool[869].fCircleCentreX = 0.0f;
  this->m_Pool[869].fCircleCentreY = 0.0f;
  this->m_Pool[869].fCircleCentreZ = 0.0f;
  LOBYTE(this->m_Pool[1878].EndPos.pit) = 1;
  BYTE1(this->m_Pool[1878].EndPos.pit) = 0;
  BYTE2(this->m_Pool[1878].EndPos.pit) = 1;
  HIBYTE(this->m_Pool[1878].EndPos.pit) = 1;
  this->m_Pool[1878].EndPos.rol = 0.0f;
  *(_DWORD *)&this->m_Pool[1878].bAbsoluteTime = 100;
  *(_DWORD *)&this->m_Pool[1878].bLineMove = 1000;
  this->m_Pool[107].fp[0] = 0;
  this->m_Pool[2].fInertia = 0.0f;
  this->m_Pool[2].fStartSpeed = 0.0f;
  this->m_Pool[2].fAcceleration2 = 0.0f;
  this->m_Pool[2].fAcceleration1 = 0.0f;
  this->m_Pool[2].fAccelerationTime2 = 0.0f;
  this->m_Pool[2].fAccelerationTime1 = 0.0f;
  this->m_Pool[2].fAngleSpeed = 0.0f;
  this->m_Pool[2].fCircleAngle = 0.0f;
}

// 0x004E7D70
LRESULT CCCTData::UpdateDebugDialog()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  HWND v4; // esi
  int v5; // eax
  int v6; // ecx
  LRESULT result; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // esi
  BOOL v11; // edx
  LRESULT Only; // eax
  BOOL v13; // edx
  BOOL v14; // ecx
  BOOL v15; // ecx
  LRESULT v16; // eax
  BOOL v17; // ecx
  LRESULT v18; // eax
  BOOL v19; // edx
  LRESULT v20; // eax
  BOOL v21; // edx
  BOOL v22; // ecx
  BOOL v23; // edx
  BOOL v24; // ecx
  LRESULT v25; // eax
  HWND v26; // [esp+0x10] [ebp-0x8C]
  HWND hWnd; // [esp+0x14] [ebp-0x88]
  HWND v28; // [esp+0x18] [ebp-0x84]
  HWND v29; // [esp+0x1C] [ebp-0x80]
  HWND v30; // [esp+0x20] [ebp-0x7C]
  HWND v31; // [esp+0x24] [ebp-0x78]
  HWND v32; // [esp+0x28] [ebp-0x74]
  HWND v33; // [esp+0x2C] [ebp-0x70]
  HWND v34; // [esp+0x30] [ebp-0x6C]
  HWND v35; // [esp+0x34] [ebp-0x68]
  HWND v36; // [esp+0x38] [ebp-0x64]
  HWND v37; // [esp+0x3C] [ebp-0x60]
  HWND v38; // [esp+0x40] [ebp-0x5C]
  HWND v39; // [esp+0x44] [ebp-0x58]
  HWND v40; // [esp+0x48] [ebp-0x54]
  HWND v41; // [esp+0x4C] [ebp-0x50]
  HWND v42; // [esp+0x50] [ebp-0x4C]
  HWND v43; // [esp+0x54] [ebp-0x48]
  HWND v44; // [esp+0x58] [ebp-0x44]
  HWND v45; // [esp+0x5C] [ebp-0x40]
  HWND v46; // [esp+0x60] [ebp-0x3C]
  HWND v47; // [esp+0x64] [ebp-0x38]
  HWND v48; // [esp+0x68] [ebp-0x34]
  HWND v49; // [esp+0x6C] [ebp-0x30]
  HWND v50; // [esp+0x70] [ebp-0x2C]
  HWND v51; // [esp+0x74] [ebp-0x28]
  HWND v52; // [esp+0x78] [ebp-0x24]
  HWND v53; // [esp+0x7C] [ebp-0x20]
  int p_DWORD; // [esp+0x80] [ebp-0x1C] BYREF
  int v55; // [esp+0x84] [ebp-0x18]
  int v56; // [esp+0x88] [ebp-0x14]
  int p_DWORD2; // [esp+0x8C] [ebp-0x10] BYREF
  int v58; // [esp+0x90] [ebp-0xC]
  int v59; // [esp+0x94] [ebp-0x8]
  HWND v60; // [esp+0x98] [ebp-0x4]

  DlgItem = GetDlgItem(g_hMainWnd, 1185);
  v3 = GetDlgItem(g_hMainWnd, 1187);
  hWnd = GetDlgItem(g_hMainWnd, 1186);
  v49 = GetDlgItem(g_hMainWnd, 1174);
  v29 = GetDlgItem(g_hMainWnd, 1175);
  v43 = GetDlgItem(g_hMainWnd, 1164);
  v31 = GetDlgItem(g_hMainWnd, 1165);
  v53 = GetDlgItem(g_hMainWnd, 1199);
  v33 = GetDlgItem(g_hMainWnd, 1200);
  v45 = GetDlgItem(g_hMainWnd, 1178);
  v35 = GetDlgItem(g_hMainWnd, 1181);
  v51 = GetDlgItem(g_hMainWnd, 1166);
  v37 = GetDlgItem(g_hMainWnd, 1162);
  v47 = GetDlgItem(g_hMainWnd, 1177);
  v39 = GetDlgItem(g_hMainWnd, 1183);
  v52 = GetDlgItem(g_hMainWnd, 1182);
  v41 = GetDlgItem(g_hMainWnd, 1167);
  v26 = GetDlgItem(g_hMainWnd, 1184);
  v28 = GetDlgItem(g_hMainWnd, 1192);
  v30 = GetDlgItem(g_hMainWnd, 1193);
  v32 = GetDlgItem(g_hMainWnd, 1196);
  v34 = GetDlgItem(g_hMainWnd, 1171);
  v36 = GetDlgItem(g_hMainWnd, 1172);
  v38 = GetDlgItem(g_hMainWnd, 1173);
  v40 = GetDlgItem(g_hMainWnd, 1176);
  v42 = GetDlgItem(g_hMainWnd, 1179);
  v44 = GetDlgItem(g_hMainWnd, 1180);
  v46 = GetDlgItem(g_hMainWnd, 1191);
  v48 = GetDlgItem(g_hMainWnd, 1190);
  v50 = GetDlgItem(g_hMainWnd, 1202);
  v4 = GetDlgItem(g_hMainWnd, 1168);
  v60 = v4;
  v5 = *(_DWORD *)&this->m_Pool[39].bAbsoluteTime;
  if ( v5 == -1 || (v6 = *(_DWORD *)&this->m_Pool[39].bRandSwing, v6 == -1) )
  {
    EditBoxSetReadOnly(v3, 0);
    EditBoxSetReadOnly(DlgItem, 0);
    EditBoxSetReadOnly(hWnd, 0);
    EditBoxSetReadOnly(v49, 0);
    EditBoxSetReadOnly(v29, 0);
    EditBoxSetInt(v43, 0);
    EditBoxSetInt(v31, 0);
    EditBoxSetReadOnly(v53, 0);
    EditBoxSetReadOnly(v33, 0);
    EditBoxSetInt(v45, 0);
    EditBoxSetInt(v35, 0);
    EditBoxSetInt(v51, 0);
    EditBoxSetInt(v37, 0);
    EditBoxSetReadOnly(v47, 0);
    EditBoxSetReadOnly(v39, 0);
    EditBoxSetReadOnly(v52, 0);
    EditBoxSetInt(v41, 0);
    EditBoxSetReadOnly(v26, 0);
    EditBoxSetReadOnly(v28, 0);
    EditBoxSetReadOnly(v30, 0);
    EditBoxSetInt(v32, 0);
    EditBoxSetInt(v34, 0);
    EditBoxSetInt(v36, 0);
    EditBoxSetInt(v38, 0);
    EditBoxSetInt(v40, 0);
    EditBoxSetInt(v42, 0);
    EditBoxSetInt(v44, 0);
    EditBoxSetReadOnly(v46, 0);
    EditBoxSetReadOnly(v48, 0);
    EditBoxSetReadOnly(v50, 0);
    return EditBoxSetInt(v4, 0);
  }
  else
  {
    result = 5 * (5 * v5 + 10250);
    v8 = *(_DWORD *)(*((_DWORD *)this->m_Pool[0].fp[0] + 5) + 16);
    v9 = *(_DWORD *)(v8 + 4 * (v6 + 2 * result));
    if ( v9 != -1 )
    {
      result = 51 * v9;
      v10 = v8 + 204 * v9;
      if ( v10 )
      {
        LOBYTE(v9) = *(_BYTE *)(v10 + 93);
        EditBoxSetReadOnly(v3, v9);
        LOBYTE(v11) = *(_BYTE *)(v10 + 92);
        Only = EditBoxSetReadOnly(DlgItem, v11);
        LOBYTE(Only) = *(_BYTE *)(v10 + 94);
        EditBoxSetReadOnly(hWnd, Only);
        LOBYTE(v13) = *(_BYTE *)(v10 + 88) == 0;
        EditBoxSetReadOnly(v49, v13);
        LOBYTE(v14) = *(_BYTE *)(v10 + 89) == 0;
        EditBoxSetReadOnly(v29, v14);
        EditBoxSetInt(v43, *(_DWORD *)(v10 + 80));
        EditBoxSetInt(v31, *(_DWORD *)(v10 + 84));
        LOBYTE(v15) = *(_BYTE *)(v10 + 91);
        v16 = EditBoxSetReadOnly(v53, v15);
        LOBYTE(v16) = *(_BYTE *)(v10 + 90);
        EditBoxSetReadOnly(v33, v16);
        EditBoxSetFloat(v45, *(float *)(v10 + 132));
        EditBoxSetFloat(v35, *(float *)(v10 + 136));
        EditBoxSetFloat(v51, *(float *)(v10 + 108));
        EditBoxSetFloat(v37, *(float *)(v10 + 28));
        LOBYTE(v17) = *(_BYTE *)(v10 + 97);
        v18 = EditBoxSetReadOnly(v47, v17);
        LOBYTE(v18) = *(_BYTE *)(v10 + 98);
        EditBoxSetReadOnly(v39, v18);
        LOBYTE(v19) = *(_BYTE *)(v10 + 99);
        EditBoxSetReadOnly(v52, v19);
        v20 = EditBoxSetFloat(v41, *(float *)(v10 + 112));
        LOBYTE(v20) = *(_BYTE *)(v10 + 23);
        EditBoxSetReadOnly(v26, v20);
        LOBYTE(v21) = *(_BYTE *)(v10 + 101);
        EditBoxSetReadOnly(v28, v21);
        LOBYTE(v22) = *(_BYTE *)(v10 + 102);
        EditBoxSetReadOnly(v30, v22);
        EditBoxSetInt(v32, *(_DWORD *)(v10 + 104));
        EditBoxSetFloat(v34, *(float *)(v10 + 116));
        EditBoxSetFloat(v36, *(float *)(v10 + 120));
        EditBoxSetFloat(v38, *(float *)(v10 + 124));
        EditBoxSetFloat(v40, *(float *)(v10 + 128));
        EditBoxSetFloat(v42, *(float *)(v10 + 164));
        EditBoxSetFloat(v44, *(float *)(v10 + 168));
        LOBYTE(v23) = *(_BYTE *)(v10 + 100);
        EditBoxSetReadOnly(v46, v23);
        LOBYTE(v24) = *(_BYTE *)(v10 + 96);
        v25 = EditBoxSetReadOnly(v48, v24);
        LOBYTE(v25) = *(_BYTE *)(v10 + 95);
        EditBoxSetReadOnly(v50, v25);
        EditBoxSetFloat(v60, *(float *)(v10 + 172));
        p_DWORD = 0;
        v55 = 0;
        v56 = 0;
        p_DWORD2 = 0;
        v58 = 0;
        v59 = 0;
        p_DWORD = *(_DWORD *)(v10 + 140);
        v55 = *(_DWORD *)(v10 + 144);
        v56 = *(_DWORD *)(v10 + 148);
        p_DWORD2 = *(_DWORD *)(v10 + 152);
        v58 = *(_DWORD *)(v10 + 156);
        v59 = *(_DWORD *)(v10 + 160);
        *(CCCTData **)(*((_DWORD *)this->m_Pool[0].fp[0] + 5) + 16)->CCCTData::CCCTData(&p_DWORD, &p_DWORD2);
      }
    }
  }
  return result;
}

// 0x005044C0
int CCCTData::UpdateCamera(int nVal)
{
  return (((InputSystem *)*(_DWORD *)(nVal + 12)))->ProcessKeyboard(*(_DWORD *)(nVal + 16), *(_DWORD *)(nVal + 20), *(_DWORD *)nVal, *(_DWORD *)(nVal + 4), *(_DWORD *)(nVal + 8));
}

// 0x005058F0
CCCTData::CCCTData(int *p_DWORD, int *p_DWORD2)
{
  LODWORD(this[1].m_Pool[1].fStartTime) = (unsigned long)*p_DWORD;
  LODWORD(this[1].m_Pool[1].fExpectTime) = (unsigned long)p_DWORD[1];
  LODWORD(this[1].m_Pool[1].StartPos.x) = (unsigned long)p_DWORD[2];
  LODWORD(this[1].m_Pool[1].StartPos.y) = (unsigned long)*p_DWORD2;
  LODWORD(this[1].m_Pool[1].StartPos.z) = (unsigned long)p_DWORD2[1];
  this[1].m_Pool[1].StartPos.yaw.p = (CEffMgr *)p_DWORD2[2];
}

// 0x00505930
CCCTData::~CCCTData()
{
  char *p_fStartTime; // ebp
  gbRenderEffect *v3; // ebx
  float *v4; // esi
  char *v5; // esi
  float *v6; // esi
  float v7; // st7
  gbDynVertBuf *v8; // edx
  float fExpectTime; // eax
  float v10; // ecx
  double y; // st7
  float v12; // edx
  float z; // eax
  unsigned int p; // ecx
  float v15; // edx
  float v16; // eax
  float v17; // ecx
  float v18; // edx
  float *v19; // edi
  float v20; // st7
  float v21; // st6
  gbDynVertBuf *v22; // edx
  float v23; // st6
  gbColorQuad v24; // [esp+0x40] [ebp-A8h] BYREF
  float *v25; // [esp+0x44] [ebp-A4h]
  int v26; // [esp+0x48] [ebp-A0h]
  int v27; // [esp+0x4C] [ebp-0x9C]
  struct gbColorQuad v28; // [esp+0x50] [ebp-0x98]
  gbVec3D *v29; // [esp+0x54] [ebp-0x94]
  int v30; // [esp+0x58] [ebp-0x90]
  gbRenderEffect *v31; // [esp+0x5C] [ebp-0x8C]
  float v32; // [esp+0x64] [ebp-0x84]
  float x; // [esp+0x68] [ebp-0x80]
  int v34; // [esp+0x6C] [ebp-0x7C]
  float v35; // [esp+0x70] [ebp-0x78]
  int v36; // [esp+0x74] [ebp-0x74]
  float v37; // [esp+0x78] [ebp-0x70]
  struct gbColorQuad v38; // [esp+0x7C] [ebp-0x6C] BYREF
  gbDynVertBuf *DynVertBuf; // [esp+0x80] [ebp-0x68]
  float v40; // [esp+0x84] [ebp-0x64] BYREF
  float v41; // [esp+0x88] [ebp-0x60]
  float v42; // [esp+0x8C] [ebp-0x5C]
  gbDynVertBuf *v43; // [esp+0x90] [ebp-0x58]
  float v44; // [esp+0x94] [ebp-0x54]
  unsigned int Color; // [esp+0x98] [ebp-0x50]
  struct gbOBBox v46; // [esp+0x9C] [ebp-0x4C] BYREF

  if ( LOBYTE(this[1].m_Pool[1].StartPos.pit) )
  {
    (((gbGeomNode *)*(gbGeomNode **)&this[1].m_Pool[1].bValid))->gbGeomNode::GetTotalOBBox(&v46);
    p_fStartTime = (char *)&this[1].m_Pool[1].fStartTime;
    (((gbMatrix4 *)&v46.trans))->gbMatrix4::RightTranslate(*(gbVec3D *)&this[1].m_Pool[1].fStartTime);
    v3 = (((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewTrivalEffect(3);
    DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x15u);
    if ( (byte_17AAEE0 & 1) == 0 )
    {
      v4 = (float *)&g_fCBAnimTime;
      LOBYTE(byte_17AAEE0) = byte_17AAEE0 | 1;
      v34 = 6;
      do
      {
        v4 += 17;
        --v34;
      }
      while ( *(float *)&v34 != 0.0f );
      atexit(nullsub_31);
    }
    v46.xlen = v46.xlen + 2.0;
    v46.ylen = v46.ylen + 2.0;
    v46.zlen = v46.zlen + 2.0;
    v37 = v46.ylen * 0.5f;
    *(float *)g_CombatTaskData.m_nEffParamBase = v37;
    *(float *)&v34 = v46.zlen * 0.5;
    g_fCBAnimTime = v46.xlen * -0.5;
    g_CombatTaskData.m_nEffParamBase[1] = v34;
    *(float *)&g_CombatTaskData.m_nEffParam0 = v37;
    *(float *)&g_CombatTaskData.m_nEffParamBase[2] = v46.xlen * 0.5;
    g_CombatTaskData.m_nEffParam10 = v34;
    g_CombatTaskData.m_nEffParam1C = v34;
    v35 = v46.ylen * -0.5f;
    g_CombatTaskData.m_nEffParam14 = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    *(float *)&g_CombatTaskData.m_nEffParam1 = v35;
    g_CombatTaskData.m_nEffTypeID = g_fCBAnimTime;
    *(float *)&g_CombatTaskData.m_nEffParam24 = v35;
    *(float *)&v36 = v46.zlen * -0.5;
    g_CombatTaskData.m_nEffTypeCode = v34;
    g_CombatTaskData.m_nEffParam40 = g_fCBAnimTime;
    *(float *)&g_CombatTaskData.m_nEffParam44 = v37;
    g_CombatTaskData.m_nEffParam48 = v36;
    g_CombatTaskData.m_nEffParam4C = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    *(float *)&g_CombatTaskData.m_nEffParam50 = v37;
    g_CombatTaskData.m_nEffParam2 = v36;
    g_CombatTaskData.m_nEffParam58 = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    g_CombatTaskData.m_fCombatTime = g_fCBAnimTime;
    g_CombatTaskData.m_nEffParam7 = g_fCBAnimTime;
    *(float *)&g_CombatTaskData.m_nEffParam5C = v35;
    g_CombatTaskData.m_nEffParam3 = v36;
    *(float *)&g_CombatTaskData.m_nEffParam4 = v35;
    g_CombatTaskData._todo_06C = v36;
    g_CombatTaskData._todo_090 = g_fCBAnimTime;
    g_CombatTaskData.m_fTargetParam = v37;
    g_CombatTaskData.m_nEffParam8 = v34;
    g_CombatTaskData.m_nEffParam9C = g_fCBAnimTime;
    *(float *)&g_CombatTaskData.m_nEffParam9 = v37;
    g_CombatTaskData.m_nEffParam98 = v36;
    g_CombatTaskData.m_nEffParamA8 = g_fCBAnimTime;
    *(float *)&g_CombatTaskData.m_nEffParamA0 = v35;
    g_CombatTaskData.m_nEffParamA4 = v36;
    *(float *)&g_CombatTaskData.m_nEffParamAC = v35;
    g_CombatTaskData.m_nEffParamC8 = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    g_CombatTaskData.m_nEffParamB0 = v34;
    *(float *)&g_CombatTaskData.m_nEffParamCC = v37;
    g_CombatTaskData.m_nEffParamD0 = v34;
    g_CombatTaskData.m_nEffParamD4 = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    *(float *)&g_CombatTaskData.m_nEffParamD8 = v37;
    g_CombatTaskData.m_nEffParamDC = v36;
    g_CombatTaskData.m_nEffParamE0 = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    *(float *)&g_CombatTaskData.m_nEffParamE4 = v35;
    g_CombatTaskData.m_nEffParamEC = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    g_CombatTaskData._todo_10C = g_fCBAnimTime;
    g_CombatTaskData.m_nEffParamE8 = v36;
    *(float *)&g_CombatTaskData.m_nEffParamF0 = v35;
    g_CombatTaskData._todo_118 = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    g_CombatTaskData._todo_0F4 = v34;
    *(float *)&g_CombatTaskData._todo_110 = v37;
    g_CombatTaskData._todo_114 = v36;
    g_CombatTaskData._todo_124 = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    *(float *)&g_CombatTaskData._todo_11C = v37;
    g_CombatTaskData._todo_120 = v36;
    *(float *)&g_CombatTaskData._todo_128 = v37;
    g_CombatTaskData._todo_130 = g_fCBAnimTime;
    g_CombatTaskData._todo_12C = v34;
    *(float *)&g_CombatTaskData._todo_134 = v37;
    g_CombatTaskData._todo_150 = g_fCBAnimTime;
    g_CombatTaskData._todo_138 = v34;
    *(float *)&g_CombatTaskData._todo_154 = v35;
    g_CombatTaskData._todo_158 = v36;
    g_CombatTaskData._todo_15C = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    g_CombatTaskData._todo_168 = *(float *)&g_CombatTaskData.m_nEffParamBase[2];
    g_CombatTaskData.m_fFloatParam = v35;
    g_CombatTaskData._todo_164 = v36;
    g_CombatTaskData._todo_174 = g_fCBAnimTime;
    *(float *)&g_CombatTaskData._todo_16C = v35;
    g_CombatTaskData._todo_170 = v34;
    v32 = v35;
    x = *(float *)&v34;
    *(float *)&g_CombatTaskData._todo_178 = v35;
    g_CombatTaskData._todo_17C = v34;
    v5 = (char *)&g_CombatTaskData.m_nEffTypeCode + 21;
    do
    {
      v5[1] = -1;
      *v5 = -1;
      v27 = 4;
      *(v5 - 1) = 10;
      v26 = (int)(v5 - 65);
      v5[2] = -101;
      (((gbMatrix4 *)&v46.trans))->gbMatrix4::Transform((gbVec3D *)v26, v27);
      v5 += 68;
    }
    while ( (int)v5 < (int)&byte_17AAF21 );
    (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&g_fCBAnimTime, 6, v3, 0);
    v6 = (float *)&v40;
    v34 = 2;
    do
    {
      v6 += 3;
      --v34;
    }
    while ( *(float *)&v34 != 0.0f );
    v7 = *(float *)p_fStartTime;
    v8 = (gbDynVertBuf *)*(gbDynVertBuf **)p_fStartTime;
    fExpectTime = this[1].m_Pool[1].fExpectTime;
    x = this[1].m_Pool[1].StartPos.x;
    v43 = (gbDynVertBuf *)v8;
    v40 = v7;
    v42 = x;
    v10 = this[1].m_Pool[1].StartPos.x;
    v27 = (int)v3;
    v26 = 2;
    v25 = (float *)&v40;
    v44 = fExpectTime;
    v24.Color = LODWORD(v10);
    Color = LODWORD(v10);
    v38.Color = 1358954495;
    v41 = 0.0f;
    (((gbDynVertBuf *)v43))->gbDynVertBuf::RenderLineStrip(v28, v29, v30, v31);
    y = this[1].m_Pool[1].StartPos.y;
    v12 = this[1].m_Pool[1].StartPos.y;
    z = this[1].m_Pool[1].StartPos.z;
    x = this[1].m_Pool[1].StartPos.yaw.f;
    v43 = (gbDynVertBuf *)LODWORD(v12);
    v40 = y;
    v42 = x;
    p = (unsigned int)this[1].m_Pool[1].StartPos.yaw.p;
    v27 = (int)v3;
    v26 = 2;
    v25 = (float *)&v40;
    v44 = z;
    v24.Color = p;
    Color = p;
    v41 = 0.0f;
    (((gbDynVertBuf *)v43))->gbDynVertBuf::RenderLineStrip(v28, v29, v30, v31);
    v15 = this[1].m_Pool[1].fExpectTime;
    v16 = this[1].m_Pool[1].StartPos.x;
    v40 = *(float *)p_fStartTime;
    v17 = this[1].m_Pool[1].StartPos.y;
    v41 = v15;
    v18 = this[1].m_Pool[1].StartPos.z;
    v43 = (gbDynVertBuf *)LODWORD(v17);
    v27 = (int)v3;
    v26 = 2;
    v25 = (float *)&v40;
    v44 = v18;
    v24.Color = (unsigned int)&v40;
    v42 = v16;
    Color = (unsigned int)this[1].m_Pool[1].StartPos.yaw.p;
    (((gbDynVertBuf *)v43))->gbDynVertBuf::RenderLineStrip(v28, v29, v30, v31);
    v19 = (float *)this[1].m_Pool[0].fp[1];
    v20 = v19[123] + 1.0f;
    v21 = v19[124] + 1.0f;
    v22 = (gbDynVertBuf *)*(gbDynVertBuf **)p_fStartTime;
    v27 = (int)v3;
    v26 = 2;
    v32 = v21;
    v23 = v19[125];
    v43 = (gbDynVertBuf *)v22;
    v41 = v32;
    v44 = *((float *)p_fStartTime + 1);
    x = v23 + 1.0f;
    v25 = (float *)&v40;
    v40 = v20;
    v42 = x;
    v24.Color = *((_DWORD *)p_fStartTime + 2);
    Color = v24.Color;
    (((gbDynVertBuf *)v43))->gbDynVertBuf::RenderLineStrip(v28, v29, v30, v31);
    (((gbRefObject *)v3))->gbRefObject::Release();
  }
}

// 0x00506020
bool CCCTData::Create(float *pfVal)
{
  char *v3; // eax
  CameraCtrl *v4; // ecx
  float pPos[2]; // [esp+0x8] [ebp-0x90] BYREF
  struct gbVec3D v7; // [esp+0x10] [ebp-0x88] BYREF
  gbRay v8; // [esp+0x1C] [ebp-0x7C] BYREF
  struct gbOBBox v9; // [esp+0x34] [ebp-0x64] BYREF
  _BYTE pTarget[24]; // [esp+0x80] [ebp-0x18] BYREF

  (((gbGeomNode *)*(gbGeomNode **)&this[1].m_Pool[1].bValid))->gbGeomNode::GetTotalOBBox(&v9);
  v7.x = *pfVal;
  v7.y = pfVal[1];
  v7.z = pfVal[2];
  (((gbMatrix4 *)&v9.trans))->gbMatrix4::RightTranslate(v7);
  v3 = (char *)this[1].m_Pool[0].fp[0];
  pPos[0] = *((float *)v3 + 20);
  v4 = (CameraCtrl *)this[1].m_Pool[0].fp[1];
  pPos[1] = *((float *)v3 + 21);
  qmemcpy(&v8, (((CameraCtrl *)v4))->CameraCtrl::GetViewTarget(pTarget, pPos), sizeof(v8));
  return (((gbRay *)&v8))->gbRay::IsColOBB(v9) == 1;
}

// 0x005060D0
bool CCCTData::Destroy()
{
  gbGeomNode *v2; // eax
  gbGeomNode *v3; // esi
  gbGeomNode *v4; // ecx
  char pExceptionObject[1024]; // [esp+0xC] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x40C] [ebp-0x40C] BYREF
  int v8; // [esp+0x814] [ebp-0x4]

  v2 = (gbGeomNode *)operator new(0x118u);
  v3 = (gbGeomNode *)v2;
  v8 = 0;
  if ( v2 )
  {
    v2->gbGeomNode::gbGeomNode();
    v4 = (gbGeomNode *)v3;
  }
  else
  {
    v4 = 0;
  }
  v8 = -1;
  *(_DWORD *)&this[1].m_Pool[1].bValid = (_DWORD)v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_9, 1425),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (((gbGeomNode *)v4))->gbGeomNode::LoadFromFile("ui\\combat\\pointer\\pointer.cvd", 0, 0);
  return 1;
}

// 0x005061A0
void CCCTData::Init()
{
  int x_low; // edx
  float y; // ebp
  CEffectSystem *v4; // ecx
  tagCCT *v5; // edi
  int v6; // eax

  x_low = LODWORD(this[1].m_Pool[0].StartPos.x);
  y = this[1].m_Pool[0].StartPos.y;
  v4 = (CEffectSystem *)this->m_nCCTIndex[0][50 * x_low + LODWORD(y)];
  if ( v4 == (CEffectSystem *)-1 )
    v5 = 0;
  else
    v5 = (tagCCT *)&this->m_Pool[(_DWORD)v4];
  if ( v5->bFinished )
  {
    LODWORD(this[1].m_Pool[0].StartPos.y) = LODWORD(y) + 1;
    LOBYTE(v6) = (((CCBStageCam *)this))->CCBStageCam::IsEditorCamValid(x_low);
    if ( SLODWORD(this[1].m_Pool[0].StartPos.y) >= v6 )
    {
      LOBYTE(this[1].m_Pool[0].fp[3]) = 0;
      this[1].m_Pool[0].StartPos.y = NAN;
      this[1].m_Pool[0].StartPos.x = NAN;
    }
  }
  else
  {
    if ( v5->bRandSwing )
      *((_BYTE *)(((CEffectSystem *)v4))->CEffectSystem::DestroyAllEffect() + 5) = 1;
    else
      *((_BYTE *)(((CEffectSystem *)v4))->CEffectSystem::DestroyAllEffect() + 5) = 0;
    if ( v5->bLineMove )
      sub_506340(this);
    if ( v5->bCircleMove )
      this->CCCTData::InsertTaskToList();
    if ( v5->bMechanicsMove )
      this->CCCTData::SwapTask();
  }
}

// 0x00506260
char * CCCTData::Save(int nVal)
{
  char *result; // eax
  char *v4; // esi
  int *v5; // edx
  tagCCT *v6; // eax

  LOBYTE(result) = (((CCBStageCam *)this))->CCBStageCam::IsEditorCamValid(nVal);
  if ( (int)result > 0 )
  {
    v4 = (char *)result;
    v5 = (int *)&this->m_nCCTIndex[0][50 * nVal];
    do
    {
      if ( *v5 == -1 )
        v6 = 0;
      else
        v6 = (tagCCT *)&this->m_Pool[*v5];
      v6->bExecuted = 0;
      if ( *v5 == -1 )
        result = 0;
      else
        result = (char *)&this->m_Pool[*v5];
      ++v5;
      --v4;
      result[22] = 0;
    }
    while ( v4 );
  }
  return result;
}

// 0x005062D0
bool CCCTData::Load(float *pfVal)
{
  char *v2; // eax
  float v3; // st7
  float v4; // st6
  int v5; // ecx
  int v6; // edx
  bool result; // al
  int v8; // [esp+0x0] [ebp-0x10]
  int v9; // [esp+0x4] [ebp-0xC]

  v2 = (char *)this[1].m_Pool[0].fp[1];
  v3 = *((float *)v2 + 124);
  v4 = *((float *)v2 + 123);
  v8 = *((_DWORD *)v2 + 125);
  v5 = *((_DWORD *)v2 + 113);
  v9 = *((_DWORD *)v2 + 114);
  v6 = *((_DWORD *)v2 + 116);
  result = (char)pfVal;
  *((_DWORD *)pfVal + 2) = v8;
  *((_DWORD *)pfVal + 3) = v9;
  *((_DWORD *)pfVal + 4) = v5;
  *pfVal = v4;
  *((_DWORD *)pfVal + 5) = v6;
  pfVal[1] = v3;
  return result;
}

// 0x005075E0
void CCCTData::InsertTaskToList()
{
  int v1; // edx
  tagCCT *v2; // eax
  int v4; // ecx
  tagCCT *v5; // ebx
  float v6; // st7
  float v7; // st7
  char v9; // c0
  float v10; // st7
  float v11; // st7
  float v12; // st7
  float v13; // st7
  unsigned __int8 v15; // c0
  unsigned __int8 v16; // c3
  float v17; // st7
  float v18; // st6
  float v19; // st7
  float v20; // st6
  float v21; // st7
  float v22; // st7
  float v23; // st7
  double fAngleSpeed; // st7
  char bPosTrace; // cl
  unsigned int nTraceRole; // eax
  float *v27; // eax
  float v28; // edx
  float *v29; // eax
  float v30; // edx
  float *p_fInertia; // esi
  unsigned __int8 v33; // c0
  unsigned __int8 v34; // c3
  float pit; // [esp+0x1C] [ebp-0x80]
  float v36; // [esp+0x20] [ebp-0x7C]
  float v37; // [esp+0x24] [ebp-0x78]
  float v38; // [esp+0x28] [ebp-0x74]
  float v39; // [esp+0x2C] [ebp-0x70]
  float v40; // [esp+0x2C] [ebp-0x70]
  float v41; // [esp+0x30] [ebp-0x6C]
  float v42; // [esp+0x30] [ebp-0x6C]
  float fCircleCentreX; // [esp+0x34] [ebp-0x68]
  float v44; // [esp+0x34] [ebp-0x68]
  float fCircleCentreY; // [esp+0x38] [ebp-0x64]
  float v46; // [esp+0x38] [ebp-0x64]
  float fCircleCentreZ; // [esp+0x3C] [ebp-0x60]
  float v48; // [esp+0x3C] [ebp-0x60]
  float v49; // [esp+0x44] [ebp-0x58]
  float v50; // [esp+0x48] [ebp-0x54]
  gbQuaternion v51; // [esp+0x4C] [ebp-0x50] BYREF
  gbMatrix4 v52; // [esp+0x5C] [ebp-0x40] BYREF
  void *v53; // [esp+A0h] [ebp+0x4]

  v1 = this->m_nCCTIndex[0][50 * LODWORD(this[1].m_Pool[0].StartPos.x) + LODWORD(this[1].m_Pool[0].StartPos.y)];
  if ( v1 == -1 )
    v2 = 0;
  else
    v2 = (tagCCT *)&this->m_Pool[v1];
  if ( v2->bEndCamValid && v2->bSpeedValid )
  {
    if ( !v2->bTimeValid )
    {
      v4 = this->m_nCCTIndex[0][50 * LODWORD(this[1].m_Pool[0].StartPos.x) + LODWORD(this[1].m_Pool[0].StartPos.y)];
      if ( v4 == -1 )
        v5 = 0;
      else
        v5 = (tagCCT *)&this->m_Pool[v4];
      if ( !v5->bExecuted )
      {
        if ( !v5->bStartCamValid )
          this->CCCTData::Load(&v5->StartPos.x);
        if ( v5->bAbsoluteTime )
          v6 = *(float *)(*(_DWORD *)this[1].m_Pool[0].fp[0] + 104);
        else
          v6 = *(float *)(*(_DWORD *)this[1].m_Pool[0].fp[0] + 80);
        v5->fStartTime = v6;
        qmemcpy(&this[1].m_Pool[0].bStartCamValid, &v5->StartPos, 0x18u);
        if ( v5->bCounterYaw )
        {
          if ( v5->EndPos.yaw.f - *(float *)&this[1].m_Pool[0].bRandSwing <= 0.0 )
          {
            v7 = *(float *)&this[1].m_Pool[0].bRandSwing;
            if ( v9 )
              v7 = v7 - 6.2831854820251465f;
          }
          else
          {
            v7 = *(float *)&this[1].m_Pool[0].bRandSwing + 6.2831854820251465f;
          }
          *(float *)&this[1].m_Pool[0].bRandSwing = v7;
        }
        this[1].m_Pool[0].EndPos.pit = v5->fCircleAngle;
        this[1].m_Pool[0].StartPos.z = v5->fAngleSpeed;
        v5->bExecuted = 1;
      }
      if ( v5->bAbsoluteTime )
        v10 = *(float *)(*(_DWORD *)this[1].m_Pool[0].fp[0] + 104);
      else
        v10 = *(float *)(*(_DWORD *)this[1].m_Pool[0].fp[0] + 80);
      v11 = v10 - v5->fStartTime;
      v36 = v11;
      pit = v11 * this[1].m_Pool[0].StartPos.z;
      if ( v36 >= (double)v5->fAccelerationTime1 )
      {
        v12 = v36 - v5->fAccelerationTime1;
        pit = v12 * v5->fAcceleration1 * v12 * 0.5f + pit;
      }
      if ( v36 >= (double)v5->fAccelerationTime2 )
      {
        v13 = v36 - v5->fAccelerationTime2;
        pit = (v5->fAcceleration2 + v5->fAcceleration1) * v13 * v13 * 0.5f + pit;
      }
      if ( v15 | v16 )
      {
        if ( pit < (double)this[1].m_Pool[0].EndPos.pit )
          pit = this[1].m_Pool[0].EndPos.pit;
      }
      else if ( pit > (double)this[1].m_Pool[0].EndPos.pit )
      {
        pit = this[1].m_Pool[0].EndPos.pit;
      }
      v17 = v5->fCircleEndY - v5->fCircleCentreY;
      v18 = pit / this[1].m_Pool[0].EndPos.pit;
      memset(&v51, 0, 12);
      v51.w = 1.0f;
      v37 = v17 * v18;
      fCircleCentreX = v5->fCircleCentreX;
      fCircleCentreY = v5->fCircleCentreY;
      fCircleCentreZ = v5->fCircleCentreZ;
      v19 = v5->StartPos.x - fCircleCentreX;
      v49 = v5->StartPos.y - fCircleCentreY;
      v20 = v5->StartPos.z - fCircleCentreZ;
      this[1].m_Pool[0].fCircleCentreX = v49;
      v50 = v20;
      this[1].m_Pool[0].fAngleSpeed = v19;
      this[1].m_Pool[0].fCircleCentreY = v50;
      (((gbQuaternion *)&v51))->gbQuaternion::SetYawPitchRoll(pit, 0.0, 0.0);
      (((gbQuaternion *)&v51))->gbQuaternion::GetMatrix(&v52);
      (((gbMatrix4 *)&v52))->gbMatrix4::RotateIn((gbVec3D *)&this[1].m_Pool[0].fAngleSpeed);
      v21 = fCircleCentreX + this[1].m_Pool[0].fAngleSpeed;
      v44 = 0.0f;
      this[1].m_Pool[0].fAngleSpeed = v21;
      v22 = fCircleCentreY + this[1].m_Pool[0].fCircleCentreX;
      v46 = 0.0f;
      this[1].m_Pool[0].fCircleCentreX = v22;
      v23 = fCircleCentreZ + this[1].m_Pool[0].fCircleCentreY;
      v48 = 0.0f;
      this[1].m_Pool[0].fCircleCentreY = v23;
      this[1].m_Pool[0].fCircleCentreX = v37 + this[1].m_Pool[0].fCircleCentreX;
      fAngleSpeed = this[1].m_Pool[0].fAngleSpeed;
      v38 = this[1].m_Pool[0].fAngleSpeed;
      v39 = this[1].m_Pool[0].fCircleCentreX;
      bPosTrace = v5->bPosTrace;
      v41 = this[1].m_Pool[0].fCircleCentreY;
      if ( bPosTrace || v5->bSightTrace )
      {
        nTraceRole = v5->nTraceRole;
        if ( nTraceRole > 0xA )
        {
          if ( nTraceRole == -1 )
          {
            v29 = (float *)*((_DWORD *)this[1].m_Pool[0].fp[0] + 5);
            v30 = v29[225];
            v29 += 225;
            v44 = v30;
            v46 = v29[1];
            v48 = v29[2];
          }
          else
          {
            v48 = 0.0f;
            v46 = 0.0f;
            v44 = 0.0f;
          }
        }
        else
        {
          v27 = (float *)(*(float **)&this[1].m_Pool[0].fp[0][4 * nTraceRole + 24]);
          v28 = v27[1646];
          v27 += 1646;
          v44 = v28;
          v46 = v27[1];
          v48 = v27[2];
        }
      }
      if ( bPosTrace )
      {
        v40 = v39 + v46;
        v42 = v41 + v48;
        fAngleSpeed = fAngleSpeed + v44 - v5->fStartTracePosX;
        v38 = fAngleSpeed;
        v39 = v40 - v5->fStartTracePosY;
        v41 = v42 - v5->fStartTracePosZ;
      }
      p_fInertia = (float *)&this[1].m_Pool[0].fInertia;
      if ( v5->bSightTrace )
      {
        this[1].m_Pool[0].fAccelerationTime1 = v39;
        this[1].m_Pool[0].fAccelerationTime2 = v41;
        *p_fInertia = fAngleSpeed;
        (((CCCTData *)this[1].m_Pool[0].fp[1]))->CCCTData::CalcDist(v38, v39);
      }
      else
      {
        *p_fInertia = *(float *)&this[1].m_Pool[0].bStartCamValid;
        this[1].m_Pool[0].fAccelerationTime1 = *(float *)&this[1].m_Pool[0].bLineMove;
        this[1].m_Pool[0].fAccelerationTime2 = *(float *)&this[1].m_Pool[0].bAbsoluteTime;
        this[1].m_Pool[0].fAcceleration1 = *(float *)&this[1].m_Pool[0].bRandSwing;
        LODWORD(this[1].m_Pool[0].fAcceleration2) = this[1].m_Pool[0].nTraceRole;
        this[1].m_Pool[0].fCircleAngle = this[1].m_Pool[0].fStartSpeed;
        this[1].m_Pool[0].fAccelerationTime1 = v39;
        *p_fInertia = fAngleSpeed;
        this[1].m_Pool[0].fAccelerationTime2 = v41;
      }
      (((CCCTData *)this[1].m_Pool[0].fp[1]))->CCCTData::UpdateCamera((int)&this[1].m_Pool[0].fInertia);
      (((CameraCtrl *)this[1].m_Pool[0].fp[1]))->CameraCtrl::SetAsCurrent(3);
      if ( v33 | v34 )
      {
        if ( pit <= (double)this[1].m_Pool[0].EndPos.pit )
        {
          v5->fExpectTime = v36;
          v5->bFinished = 1;
        }
      }
      else if ( pit >= (double)this[1].m_Pool[0].EndPos.pit )
      {
        v5->fExpectTime = v36;
        v5->bFinished = 1;
      }
    }
  }
  else
  {
    NullCallback(v53);
  }
}

// 0x00507B20
void CCCTData::SwapTask()
{
  int v2; // ecx
  tagCCT *v3; // ebx
  float *p_x; // edx
  float y; // eax
  int v6; // ecx
  tagCCT *v7; // eax
  double v8; // st7
  float v9; // ecx
  double v10; // st7
  float v11; // ecx
  int v12; // ecx
  double v13; // st7
  double v14; // st7
  char v16; // c0
  char *v17; // edx
  double v18; // st7
  int v19; // eax
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st6
  double v24; // st6
  double fAngleSpeed; // st7
  char bPosTrace; // cl
  unsigned int nTraceRole; // eax
  float *v28; // eax
  float v29; // edx
  float *v30; // eax
  float v31; // edx
  double v32; // st6
  double v33; // st5
  float v34; // [esp+0x10] [ebp-0x48]
  float v35; // [esp+0x14] [ebp-0x44]
  float v36; // [esp+0x14] [ebp-0x44]
  float v37; // [esp+0x14] [ebp-0x44]
  float v38; // [esp+0x18] [ebp-0x40]
  float v39; // [esp+0x1C] [ebp-0x3C]
  float v40; // [esp+0x20] [ebp-0x38]
  float v41; // [esp+0x20] [ebp-0x38]
  float v42; // [esp+0x20] [ebp-0x38]
  float v43; // [esp+0x20] [ebp-0x38]
  float v44; // [esp+0x20] [ebp-0x38]
  float v45; // [esp+0x24] [ebp-0x34]
  float v46; // [esp+0x24] [ebp-0x34]
  float v47; // [esp+0x24] [ebp-0x34]
  float v48; // [esp+0x24] [ebp-0x34]
  float v49; // [esp+0x24] [ebp-0x34]
  float v50; // [esp+0x28] [ebp-0x30]
  float v51; // [esp+0x2C] [ebp-0x2C]
  float v52; // [esp+0x2C] [ebp-0x2C]
  float v53; // [esp+0x2C] [ebp-0x2C]
  float v54; // [esp+0x2C] [ebp-0x2C]
  float v55; // [esp+0x2C] [ebp-0x2C]
  float v56; // [esp+0x2C] [ebp-0x2C]
  float v57; // [esp+0x2C] [ebp-0x2C]
  float v58; // [esp+0x30] [ebp-0x28]
  float v59; // [esp+0x30] [ebp-0x28]
  float v60; // [esp+0x30] [ebp-0x28]
  float v61; // [esp+0x30] [ebp-0x28]
  float v62; // [esp+0x30] [ebp-0x28]
  float v63; // [esp+0x30] [ebp-0x28]
  float v64; // [esp+0x30] [ebp-0x28]
  float v65; // [esp+0x34] [ebp-0x24]
  float v66; // [esp+0x34] [ebp-0x24]
  float v67; // [esp+0x38] [ebp-0x20]
  float v68; // [esp+0x38] [ebp-0x20]
  float v69; // [esp+0x3C] [ebp-0x1C]
  float v70; // [esp+0x3C] [ebp-0x1C]
  float v71; // [esp+0x44] [ebp-0x14]
  float v72; // [esp+0x48] [ebp-0x10]
  float v73; // [esp+0x4C] [ebp-0xC]
  float v74; // [esp+0x50] [ebp-0x8]
  float v75; // [esp+0x54] [ebp-0x4]

  v2 = this->m_nCCTIndex[0][50 * LODWORD(this[1].m_Pool[0].StartPos.x) + LODWORD(this[1].m_Pool[0].StartPos.y)];
  if ( v2 == -1 )
    v3 = 0;
  else
    v3 = (tagCCT *)&this->m_Pool[v2];
  if ( !v3->bExecuted )
  {
    if ( !v3->bStartCamValid )
      this->CCCTData::Load(&v3->StartPos.x);
    p_x = (float *)&v3->StartPos.x;
    qmemcpy(&this[1].m_Pool[0].bStartCamValid, &v3->StartPos, 0x18u);
    this[1].m_Pool[0].fAngleSpeed = v3->StartPos.x;
    this[1].m_Pool[0].fCircleCentreX = v3->StartPos.y;
    y = this[1].m_Pool[0].StartPos.y;
    this[1].m_Pool[0].fCircleCentreY = v3->StartPos.z;
    if ( y == 0.0f
      || SLODWORD(y) > 0
      && ((v6 = *(_DWORD *)&this->m_bPoolInUse[200 * LODWORD(this[1].m_Pool[0].StartPos.x) + 1996 + 4 * LODWORD(y)],
           v6 == -1)
        ? (v7 = 0)
        : (v7 = &this->m_Pool[v6]),
          !v7->bMechanicsMove) )
    {
      v8 = v3->EndPos.x - *p_x;
      v51 = v3->EndPos.y - v3->StartPos.y;
      v58 = v3->EndPos.z - v3->StartPos.z;
      if ( v3->fExpectTime <= 0.0f )
      {
        v9 = v3->EndPos.z - v3->StartPos.z;
        this[1].m_Pool[0].StartPos.pit = v8;
        this[1].m_Pool[0].StartPos.rol = v51;
      }
      else
      {
        v35 = 1.0f / v3->fExpectTime;
        v40 = v51 * v35;
        this[1].m_Pool[0].StartPos.rol = v40;
        v45 = v58 * v35;
        v9 = v45;
        this[1].m_Pool[0].StartPos.pit = v8 * v35;
      }
      this[1].m_Pool[0].EndPos.x = v9;
    }
    v10 = v3->EndPos.x - *p_x;
    v52 = v3->EndPos.y - v3->StartPos.y;
    v59 = v3->EndPos.z - v3->StartPos.z;
    if ( v3->fExpectTime <= 0.0f )
    {
      v11 = v3->EndPos.z - v3->StartPos.z;
      this[1].m_Pool[0].EndPos.y = v10;
      this[1].m_Pool[0].EndPos.z = v52;
    }
    else
    {
      v36 = 1.0f / v3->fExpectTime;
      v41 = v52 * v36;
      this[1].m_Pool[0].EndPos.z = v41;
      v46 = v59 * v36;
      v11 = v46;
      this[1].m_Pool[0].EndPos.y = v10 * v36;
    }
    this[1].m_Pool[0].EndPos.yaw.f = v11;
    v12 = *(_DWORD *)this[1].m_Pool[0].fp[0];
    if ( v3->bAbsoluteTime )
      v13 = *(float *)(v12 + 104);
    else
      v13 = *(float *)(v12 + 80);
    v3->fStartTime = v13;
    qmemcpy(&this[1].m_Pool[0].fInertia, p_x, 0x18u);
    if ( v3->bCounterYaw )
    {
      if ( v3->EndPos.yaw.f - *(float *)&this[1].m_Pool[0].bRandSwing <= 0.0 )
      {
        v14 = *(float *)&this[1].m_Pool[0].bRandSwing;
        if ( v16 )
          v14 = v14 - 6.2831855;
      }
      else
      {
        v14 = *(float *)&this[1].m_Pool[0].bRandSwing + 6.2831855;
      }
      *(float *)&this[1].m_Pool[0].bRandSwing = v14;
    }
    v3->bExecuted = 1;
  }
  if ( v3->bAbsoluteTime )
  {
    v17 = (char *)this[1].m_Pool[0].fp[0];
    v37 = *(double *)(*(_DWORD *)v17 + 88);
    v18 = *(float *)(*(_DWORD *)v17 + 104);
  }
  else
  {
    v19 = *(_DWORD *)this[1].m_Pool[0].fp[0];
    v37 = *(double *)(v19 + 64);
    v18 = *(float *)(v19 + 80);
  }
  if ( v3->fExpectTime > 0.0f )
    v34 = (v18 - v3->fStartTime) / (v3->fTimeExpiate + v3->fExpectTime);
  else
    v34 = 1.0f;
  v38 = (((gbVec3D *)&this[1].m_Pool[0].StartPos.pit))->gbVec3D::Length();
  v53 = v37 * this[1].m_Pool[0].EndPos.z;
  v60 = v37 * this[1].m_Pool[0].EndPos.yaw.f;
  v20 = v37 * this[1].m_Pool[0].EndPos.y + this[1].m_Pool[0].StartPos.pit;
  v42 = v53 + this[1].m_Pool[0].StartPos.rol;
  v21 = v60 + this[1].m_Pool[0].EndPos.x;
  this[1].m_Pool[0].StartPos.rol = v42;
  v47 = v21;
  this[1].m_Pool[0].StartPos.pit = v20;
  this[1].m_Pool[0].EndPos.x = v47;
  (((gbVec3D *)&this[1].m_Pool[0].StartPos.pit))->gbVec3D::Normalize();
  v50 = 0.0f;
  this[1].m_Pool[0].StartPos.pit = v38 * this[1].m_Pool[0].StartPos.pit;
  this[1].m_Pool[0].StartPos.rol = v38 * this[1].m_Pool[0].StartPos.rol;
  this[1].m_Pool[0].EndPos.x = v38 * this[1].m_Pool[0].EndPos.x;
  v54 = v37 * this[1].m_Pool[0].StartPos.rol;
  v61 = v37 * this[1].m_Pool[0].EndPos.x;
  v22 = v37 * this[1].m_Pool[0].StartPos.pit + this[1].m_Pool[0].fAngleSpeed;
  v23 = v54 + this[1].m_Pool[0].fCircleCentreX;
  v55 = 0.0f;
  v43 = v23;
  v24 = v61 + this[1].m_Pool[0].fCircleCentreY;
  v62 = 0.0f;
  this[1].m_Pool[0].fCircleCentreX = v43;
  v48 = v24;
  this[1].m_Pool[0].fAngleSpeed = v22;
  this[1].m_Pool[0].fCircleCentreY = v48;
  fAngleSpeed = this[1].m_Pool[0].fAngleSpeed;
  bPosTrace = v3->bPosTrace;
  v39 = this[1].m_Pool[0].fAngleSpeed;
  if ( bPosTrace || v3->bSightTrace )
  {
    nTraceRole = v3->nTraceRole;
    if ( nTraceRole > 0xA )
    {
      if ( nTraceRole == -1 )
      {
        v30 = (float *)*((_DWORD *)this[1].m_Pool[0].fp[0] + 5);
        v31 = v30[225];
        v30 += 225;
        v50 = v31;
        v55 = v30[1];
        v62 = v30[2];
      }
      else
      {
        v62 = 0.0f;
        v55 = 0.0f;
        v50 = 0.0f;
      }
    }
    else
    {
      v28 = (float *)(*(float **)&this[1].m_Pool[0].fp[0][4 * nTraceRole + 24]);
      v29 = v28[1646];
      v28 += 1646;
      v50 = v29;
      v55 = v28[1];
      v62 = v28[2];
    }
  }
  if ( bPosTrace )
  {
    v44 = v55 + v43;
    v49 = v62 + v48;
    fAngleSpeed = fAngleSpeed + v50 - v3->fStartTracePosX;
    v39 = fAngleSpeed;
    v43 = v44 - v3->fStartTracePosY;
    v48 = v49 - v3->fStartTracePosZ;
  }
  if ( v3->bSightTrace )
  {
    this[1].m_Pool[0].fAccelerationTime1 = v43;
    this[1].m_Pool[0].fAccelerationTime2 = v48;
    this[1].m_Pool[0].fInertia = fAngleSpeed;
    (((CCCTData *)this[1].m_Pool[0].fp[1]))->CCCTData::CalcDist(v39, v43);
  }
  else
  {
    v56 = v3->EndPos.y - *(float *)&this[1].m_Pool[0].bLineMove;
    v63 = v3->EndPos.z - *(float *)&this[1].m_Pool[0].bAbsoluteTime;
    v65 = v3->EndPos.yaw.f - *(float *)&this[1].m_Pool[0].bRandSwing;
    v67 = v3->EndPos.pit - *(float *)&this[1].m_Pool[0].nTraceRole;
    v69 = v3->EndPos.rol - this[1].m_Pool[0].fStartSpeed;
    v71 = v56 * v34;
    v72 = v63 * v34;
    v73 = v65 * v34;
    v74 = v67 * v34;
    v75 = v69 * v34;
    v32 = (v3->EndPos.x - *(float *)&this[1].m_Pool[0].bStartCamValid) * v34
        + *(float *)&this[1].m_Pool[0].bStartCamValid;
    v57 = v71 + *(float *)&this[1].m_Pool[0].bLineMove;
    v64 = v72 + *(float *)&this[1].m_Pool[0].bAbsoluteTime;
    v66 = v73 + *(float *)&this[1].m_Pool[0].bRandSwing;
    v68 = v74 + *(float *)&this[1].m_Pool[0].nTraceRole;
    v33 = v75 + this[1].m_Pool[0].fStartSpeed;
    this[1].m_Pool[0].fAccelerationTime1 = v57;
    this[1].m_Pool[0].fAccelerationTime2 = v64;
    this[1].m_Pool[0].fAcceleration1 = v66;
    this[1].m_Pool[0].fAcceleration2 = v68;
    v70 = v33;
    this[1].m_Pool[0].fInertia = v32;
    this[1].m_Pool[0].fCircleAngle = v70;
    this[1].m_Pool[0].fInertia = fAngleSpeed;
    this[1].m_Pool[0].fAccelerationTime1 = v43;
    this[1].m_Pool[0].fAccelerationTime2 = v48;
  }
  (((CCCTData *)this[1].m_Pool[0].fp[1]))->CCCTData::UpdateCamera((int)&this[1].m_Pool[0].fInertia);
  (((CameraCtrl *)this[1].m_Pool[0].fp[1]))->CameraCtrl::SetAsCurrent(3);
  if ( v34 >= 1.0f )
    v3->bFinished = 1;
}

// 0x00508190
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
bool CCCTData::ClearList()
{
  return this->CCCTData::IsTaskValid();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005081A0
bool CCCTData::IsTaskValid()
{
  bool result; // al

  result = 0;
  *((_DWORD *)&g_CCBCamControlData + 366) = 1094713344;
  return result;
}

// 0x005081B0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCCTData::GetTaskNumInList()
{
  this->CCCTData::GetFreeSpaceInPool();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005081C0
void CCCTData::GetFreeSpaceInPool()
{
  *((float *)&g_CCBCamControlData + 365) = 12.0 + 12.0;
}
