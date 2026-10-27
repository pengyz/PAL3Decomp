#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/RenderTarget.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Effect/CEffect.h"
#include "Render/CScreenMode.h"
#include "Scene/CameraCtrl.h"
#include "Misc/LineupUI.h"
#include "GameBase/Logger.h"
#include "Misc/MainEquipUI.h"
#include "Misc/MainPropUI.h"
#include "Misc/NameSys.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/UI3DCtrl.h"
#include "Misc/UIButton.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "Misc/UIParticle.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_5427A5(...);
int sub_543C42(...);

// Unnamed globals (extern)
extern char asc_5B74B8[];

// 0x004867F0
int RenderTarget::InitChildPanels()
{
  int *p_m_nScaleY; // edi
  int v3; // ebp

  ((UIListBox *)this)->UIListBox::UIListBox();
  this->m_szPath = 800;
  this->m_nDefaultH = 600;
  this[4].m_fRenderY = 0.0f;
  LOBYTE(this[4].m_fileData) = 0;
  BYTE1(this[4].m_szPath) = 0;
  this[4].m_nDefaultH = 0;
  *(&this[4].m_nDefaultH + 1) = 0;
  this[4].m_ScreenPlane = ((gbTexture_D3D *)0);
  *((_DWORD *)&this[4].m_ScreenPlane + 1) = -1;
  *((_BYTE *)&this[4].m_ScreenPlane + 8) = 0;
  *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
  *((_BYTE *)&this[4].m_ScreenPlane + 11) = 0;
  *((_BYTE *)&this[4].m_ScreenPlane + 12) = 0;
  *((_DWORD *)&this[4].m_ScreenPlane + 4) = 0;
  *((_DWORD *)&this[16].m_ScreenPlane + 5) = 0;
  LOBYTE(this[16].m_fOffsetParam) = 0;
  BYTE1(this[16].m_fOffsetParam) = 0;
  LOBYTE(this[16].m_fOffsetY) = 0;
  this[16].m_fOffsetX = 0.0f;
  this[16].m_fRender = 0.0f;
  p_m_nScaleY = (int *)&this[16].m_nScaleY;
  v3 = 40;
  do
  {
    ArraySort((int)p_m_nScaleY, 12, 99, 0 /* TODO: pmf_to_u32((int * (RenderTarget::*)())RenderTarget::Init) */);
    p_m_nScaleY += 298;
    --v3;
  }
  while ( v3 );
  this[255].m_nWidth = 0;
  (((UIFrameContainer *)&this[255].m_nHeight))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[255].m_nTodo_0BC))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[256].m_fRender))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[257].m_nDefaultH))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[258].m_nTodo_02C))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[258].m_nState))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)&this[275].m_nTodo_02C))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[279].m_nHeight))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[279].m_nTodo_0BC))->UIFrameContainer::ResetContainerState();
  this[1028].m_nDeviceLost = 0;
  ((UIRoleDialog *)&this[1028].m_nTodo_0BC)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this[1035].m_nScaleY)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this[1042].m_nAlpha)->UIRoleDialog::UIRoleDialog();
  ((UI3DCtrl *)&this[1051].m_nHeight)->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)(&this[1051].m_ScreenPlane + 5)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[1059].m_nTodo_028))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this[1059].m_nTodo_0BC + 1)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[1060].m_fOffsetX))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this[1061].m_nDefaultH + 1)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this[1062].m_fX))->UIFrameContainer::ResetContainerState();
  (((UIListBox *)&this[1199].m_nRenderY))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1205].m_nHalfH))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1211].m_nHalfHeight))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1217].m_nHeight))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1223].m_nTodo_02C))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1229].m_fY))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1235].m_nTodo_03C))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)&this[1241].m_fRenderX))->UIListBox::UpdateKeyCtrl();
  (((UIProgressBar *)&this[1247].m_fileData))->UIProgressBar::ctor();
  BYTE1(this[4].m_fFileParam) = 0;
  LOBYTE(this[4].m_fFileParam) = 0;
  BYTE2(this[4].m_fileData) = 0;
  BYTE1(this[4].m_fileData) = 0;
  HIBYTE(this[4].m_fileData) = 0;
  this[16].m_fRenderIntensity = 0.0f;
  this[16].m_bVisible = 0;
  this[16].m_nAlpha = 0;
  this[1535].m_nWidth = 0;
  this[1535].m_nHeight = 0;
  *(_DWORD *)&this[1028].m_szTexPath[12] = 0;
  this[1028].m_fInvScale = 0.0f;
  *((_DWORD *)&this[1028].m_fInvScale + 1) = 0;
  return (int)this;
}

// 0x00486CE0
int * RenderTarget::Init()
{
  int *result; // eax

  result = (int *)&this->m_iMode;
  this->m_iMode = 0;
  this->m_Texture = ((gbTexture_D3D *)0);
  this->m_nRenderX = 0;
  this->m_iMode = 0xFFFF;
  return result;
}

// 0x0048EB40
int RenderTarget::MainPropUI_RenderWithEffects(int nVal)
{
  CCBControlWindow *v1; // ecx
  CCBControlWindow *v2; // edi
  int v3; // eax
  UIParticle *p_m_pButtonFlee; // esi
  int v5; // ebp
  int result; // eax
  int i; // esi
  UIParticle *p_m_pButtonSkill; // esi
  UIButton *m_pButtonSkill; // ebp
  int v10; // ebx
  int v11; // eax
  int v12; // ebp
  int v13; // eax
  int v14; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  int fYb; // [esp+0x4] [ebp-0x20]
  CCBMagicWindow *v21; // [esp+0x8] [ebp-0x1C]
  int v22; // [esp+0x18] [ebp-0xC]
  int m_pButtonMagic; // [esp+0x18] [ebp-0xC]
  UIParticle *v24; // [esp+0x1C] [ebp-0x8]
  int v25; // [esp+0x1C] [ebp-0x8]
  int v26; // [esp+0x20] [ebp-0x4]

  v2 = (CCBControlWindow *)v1;
  (((CCBControlWindow *)v1))->CCBControlWindow::Render(v21);
  v3 = 0;
  p_m_pButtonFlee = (UIParticle *)&v2[1566].m_pButtonFlee;
  v22 = 0;
  v24 = (UIParticle *)&v2[1566].m_pButtonFlee;
  do
  {
    if ( *((_BYTE *)&v2[4].m_pButtonDefence + v3 + 1) )
    {
      v5 = 8;
      do
      {
        // [overlay-fix 2026-10-27] 垃圾形条件——待语义修复
        // if ( IsVisible((RenderTarget *)&p_m_pButtonFlee[40]) )
        if ( 0 )
          ((UIParticle *)(p_m_pButtonFlee + 40))->UIParticle::Apply(8);
        // [overlay-fix 2026-10-27] 垃圾形条件——待语义修复
        // if ( IsVisible((RenderTarget *)p_m_pButtonFlee) )
        if ( 0 )
          (((UIParticle *)p_m_pButtonFlee))->UIParticle::Apply(7);
        ++p_m_pButtonFlee;
        --v5;
      }
      while ( v5 );
      v3 = v22;
    }
    ++v3;
    p_m_pButtonFlee = (UIParticle *)(v24 + 8);
    v22 = v3;
    v24 += 8;
  }
  while ( v3 < 5 );
  result = *((_DWORD *)&v2[1049].m_CurCtrl_2 + 14);
  if ( *((_BYTE *)&v2[1049].m_CurCtrl_2 + result + 48) )
  {
    for ( i = 0; i < 16; ++i )
    {
      // [overlay-fix 2026-10-27] 跨行垃圾形条件（整段注释）——待语义修复
      // if ( IsVisible((RenderTarget *)(&v2[286].m_pButtonMagic + 2336 * *((_DWORD *)&v2[1049].m_CurCtrl_2 + 14) + 146 * i)) )
      // ((UIParticle *)((UIParticle *)&v2[286].m_pButtonMagic + 16 * *((_DWORD *)&v2[1049].m_CurCtrl_2 + 14) + i))->UIParticle::Apply(11);
      // if ( IsVisible((RenderTarget *)(&v2[667].m_CurCtrl_2
      // + 2336 * *((_DWORD *)&v2[1049].m_CurCtrl_2 + 14)
      // + 146 * i
      // + 10)) )
      // (((UIParticle *)(&v2[667].m_CurCtrl_2 + 2336 * *((_DWORD *)&v2[1049].m_CurCtrl_2 + 14) + 146 * i + 10)))->UIParticle::Apply(10);
      if ( 0 )
        ;   // 空语句体（整段注释后 if 失体，防 C2143）
    }
  }
  LOBYTE(result) = (unsigned long)v2[17].m_fontcolor.Color;
  if ( (_BYTE)result )
  {
    p_m_pButtonSkill = (UIParticle *)&v2[1274].m_pButtonSkill;
    v25 = 98;
    do
    {
      // [overlay-fix 2026-10-27] 垃圾形条件——待语义修复
      // if ( IsVisible((RenderTarget *)p_m_pButtonSkill) )
      if ( 0 )
      {
        (((UIParticle *)p_m_pButtonSkill))->UIParticle::Apply(12);
      }
      else
      {
        m_pButtonSkill = (UIButton *)v2[1566].m_pButtonSkill;
        v10 = (char *)v2[1566].m_pButtonItem - (char *)m_pButtonSkill;
        v11 = rand();
        m_pButtonMagic = (int)v2[1566].m_pButtonMagic;
        v26 = (int)m_pButtonSkill + v11 % (v10 / 2);
        v12 = (int)v2[1566].m_pButtonDefence - m_pButtonMagic;
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::LoadTexture(szFilename);
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::SetSize(32);
        fY = rand() % 10 + 252;
        fX = rand() % 10 + 36;
        v13 = rand();
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::SetColor(v13 % 10 - 37, fX, fY);
        v14 = rand();
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::SetAlpha(v14 % 135 + 120);
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::SetField084(1065353216);
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::SetState(1058642330);
        fYa = (float)m_pButtonMagic;
        fXa = (float)v26;
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::UpdateTransform(fXa, fYa);
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::CalcRenderDimensions(v10, v12);
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::SetOffset(10.0, 2.0);
        *(float *)&fYb = (float)(rand() % 8 + 2);
        *(float *)&fXb = (float)(rand() % 8 + 2);
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::SetScale(fXb, fYb);
        (((RenderTarget *)p_m_pButtonSkill))->RenderTarget::SetVisible(1);
      }
      ++p_m_pButtonSkill;
      result = --v25;
    }
    while ( v25 );
  }
  return result;
}

// 0x0048EF80
int RenderTarget::CameraCtrl_ValidateDevice(int nVal)
{
  int v1; // ecx
  int v2; // esi
  __int64 v3; // rax
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  char v7; // cl
  int v8; // eax
  int v9; // eax
  char v10; // cl
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int State; // eax
  DWORD TickCount; // eax
  DWORD v16; // eax
  unsigned int v17; // edx
  char v18; // al
  CScreenMode *Instance; // eax
  const void *v21; // [esp-0x8] [ebp-0x2C]
  int v22; // [esp-0x4] [ebp-0x28]
  const char *v23; // [esp-0x4] [ebp-0x28]
  int v24; // [esp+0x0] [ebp-0x24]
  int v25; // [esp+0x20] [ebp-0x4]
  int a3; // [esp+0x30] [ebp+0xC]

  v2 = v1;
  v3 = (__int64)g_fGameTimer;
  v4 = (int)v3 / 3600;
  v25 = (int)v3 / 60 % 60;
  v22 = (int)v3 % 60;
  if ( (int)v3 / 3600 < 100 )
    sprintf((char *const)(v1 + 104), "%02d:%02d:%02d", v4, v25, v22);
  else
    sprintf((char *const)(v1 + 104), "%03d:%02d:%02d", v4, v25, v22);
  (((UICaption *)(v2 + 55836)))->UICaption::SetEnable();
  sprintf((char *const)(v2 + 104), (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
  (((UICaption *)(v2 + 55988)))->UICaption::SetEnable();
  if ( *(_BYTE *)(v2 + 888) )
  {
    CameraCtrl_ProcessSaveSlotNav(v24);
    *(_DWORD *)(v2 + 96) = 0;
    do
    {
      v5 = *(_DWORD *)(v2 + 96);
      if ( *(_BYTE *)(v5 + v2 + 877) )
      {
        v6 = 4892 * v5;
        v7 = *(_BYTE *)(v6 + v2 + 213560);
        v8 = v2 + v6;
        if ( !v7 )
        {
          sprintf(
            (char *const)(v2 + 104),
            "%d/%d",
            (int)*(float *)(v8 + 213556),
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)(v2 + 96)));
          (((UICaption *)(4892 * *(_DWORD *)(v2 + 96) + v2 + 213644)))->UICaption::SetEnable();
        }
        v9 = 4892 * *(_DWORD *)(v2 + 96);
        v10 = *(_BYTE *)(v9 + v2 + 214656);
        v11 = v2 + v9;
        if ( !v10 )
        {
          sprintf(
            (char *const)(v2 + 104),
            "%d/%d",
            (int)*(float *)(v11 + 214652),
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)(v2 + 96) + 1));
          (((UICaption *)(4892 * *(_DWORD *)(v2 + 96) + v2 + 214740)))->UICaption::SetEnable();
        }
        v12 = 4892 * *(_DWORD *)(v2 + 96) + v2;
        if ( !*(_BYTE *)(v12 + 214108) )
        {
          sprintf(
            (char *const)(v2 + 104),
            "%d/%d",
            (int)*(float *)(v12 + 214104),
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)(v2 + 96) + 2));
          (((UICaption *)(4892 * *(_DWORD *)(v2 + 96) + v2 + 214192)))->UICaption::SetEnable();
        }
        (((UIFrameWnd *)(v2 + 52 * *(_DWORD *)(v2 + 96) + 209896)))->UIFrameWnd::ProcessTimer(1, 1, 2, *(_DWORD *)(16 * *(_DWORD *)(v2 + 96) + v2 + 210156));
      }
      v13 = *(_DWORD *)(v2 + 96) + 1;
      *(_DWORD *)(v2 + 96) = v13;
    }
    while ( v13 < 5 );
  }
  State = UIParabolaCtrl_GetState(v24);
  *(_DWORD *)(v2 + 209892) = State;
  if ( State )
  {
    if ( State != 1 )
      goto LABEL_20;
    (((MainPropUI *)v2))->MainPropUI::SetPage(1u);
  }
  else
  {
    (((CameraCtrl *)v2))->CameraCtrl::UpdateBlendWeight(*(_DWORD *)(v2 + 205784), *(_DWORD *)(v2 + 896));
  }
  *(_DWORD *)(v2 + 209892) = -1;
LABEL_20:
  if ( *(_BYTE *)(v2 + 3336) )
  {
    if ( !*(_BYTE *)(v2 + 3348) )
    {
      TickCount = GetTickCount();
      *(_DWORD *)(v2 + 3340) = TickCount;
      *(_DWORD *)(v2 + 3344) = TickCount;
      *(_BYTE *)(v2 + 3348) = 1;
    }
    v16 = GetTickCount();
    v17 = v16 - *(_DWORD *)(v2 + 3344);
    *(_DWORD *)(v2 + 3340) = v16;
    if ( v17 > 0x1388 )
    {
      *(_DWORD *)(v2 + 3344) = v16;
      *(_BYTE *)(v2 + 3348) = 0;
      v18 = *(_BYTE *)(v2 + 3337);
      *(_BYTE *)(v2 + 3336) = 0;
      v23 = (const char *)(v2 + 616);
      if ( v18 )
      {
        sprintf((char *const)(v2 + 104), "\\n    %s\\n%s", (const char *)&dword_DC8B3C, v23);
        (((UICaption *)(v2 + 206244)))->UICaption::SetEnable();
        lstrcpyA((LPSTR)(v2 + 616), unk_C10D38);
        v21 = (const void *)off_5C7770;
      }
      else
      {
        sprintf((char *const)(v2 + 104), "\\n    %s\\n%s", (const char *)&dword_DC8C3C, v23);
        (((UICaption *)(v2 + 206244)))->UICaption::SetEnable();
        lstrcpyA((LPSTR)(v2 + 616), unk_C10D38);
        v21 = (const void *)off_5C7774;
      }
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v21, 1);
      (((UIRoleSelect *)(v2 + 205788)))->UIRoleSelect::SetByte(1);
      (((MainPropUI *)v2))->MainPropUI::SetPage(1u);
      MagicUI_UpdateViewListItems(*(_DWORD *)(v2 + 205784));
      MagicUI_InitUILayout(7);
    }
  }
  return (((SceneObj *)v2))->SceneObj::Update(nVal, a3);
}

// 0x0048F3A0
int RenderTarget::OnRender(int nVal1)
{
  int i; // edi
  int result; // eax
  const char *v5; // ebp
  int v6; // ecx
  int *v7; // eax
  const char **v8; // eax
  int v9; // ebx
  CScreenMode *v10; // eax
  char *v11; // edi
  int v12; // ebp
  int v13; // ebp
  char *v14; // edi
  char v15; // al
  char v16; // al
  int v17; // edi
  char *v18; // ebp
  char v19; // al
  int *p_m_nTodo_03C; // edi
  int v21; // ebx
  CScreenMode *v22; // eax
  CScreenMode *v23; // eax
  CScreenMode *v24; // eax
  CScreenMode *v25; // eax
  CScreenMode *v26; // eax
  CScreenMode *v27; // eax
  CScreenMode *v28; // eax
  CScreenMode *v29; // eax
  int v30; // ecx
  int *v31; // eax
  char v32; // al
  char *v33; // esi
  int v34; // edi
  int v35; // ebx
  int v36; // eax
  int v37; // eax
  int v38; // ecx
  char *v39; // edx
  int v40; // ebp
  char *p_m_nAlpha; // edi
  char v42; // al
  char *v43; // esi
  int v44; // edi
  int v45; // edi
  int *v46; // edx
  int v47; // edi
  int *v48; // eax
  int v49; // edi
  int v50; // edi
  int v51; // edi
  int v52; // edi
  int v53; // edi
  CHAR *v54; // ebx
  LPCSTR v55; // eax
  const char *v56; // ebx
  int Child; // eax
  int m_nDeviceLost; // eax
  int v59; // eax
  int v60; // ecx
  int v61; // eax
  const char *v62; // eax
  int v63; // edx
  int v64; // eax
  int v65; // eax
  int v66; // eax
  int v67; // ecx
  int v68; // eax
  int v69; // edx
  int v70; // eax
  int v71; // eax
  int v72; // eax
  CHAR *v73; // ebx
  RoleAtt *v74; // ecx
  LPCSTR v75; // eax
  const char *v76; // ebx
  CScreenMode *Instance; // eax
  const void *v78; // [esp-0x8] [ebp-0x120]
  const char *v79; // [esp-0x8] [ebp-0x120]
  const void *v80; // [esp-0x8] [ebp-0x120]
  const void *v81; // [esp-0x8] [ebp-0x120]
  const void *v82; // [esp-0x8] [ebp-0x120]
  const void *v83; // [esp-0x8] [ebp-0x120]
  const void *v84; // [esp-0x8] [ebp-0x120]
  const void *v85; // [esp-0x8] [ebp-0x120]
  const void *v86; // [esp-0x8] [ebp-0x120]
  const void *v87; // [esp-0x8] [ebp-0x120]
  int v88; // [esp+0x0] [ebp-0x118]
  int v89; // [esp+0x0] [ebp-0x118]
  int v90; // [esp+0x10] [ebp-0x108]
  RoleAtt *SkillNum; // [esp+0x10] [ebp-0x108]
  const char *v92; // [esp+0x10] [ebp-0x108]
  const char **nVal; // [esp+0x14] [ebp-0x104]
  int *nVala; // [esp+0x14] [ebp-0x104]
  char Buffer; // [esp+0x18] [ebp-0x100] BYREF
  _BYTE v96[252]; // [esp+0x19] [ebp-FFh] BYREF
  __int16 v97; // [esp+0x115] [ebp-0x3]
  char v98; // [esp+0x117] [ebp-0x1]
  int nMsg; // [esp+0x120] [ebp+0x8]
  int wParam; // [esp+0x124] [ebp+0xC]

  switch ( nVal1 )
  {
    case 1000:
      if ( nMsg )
      {
        for ( i = 0; i < 8; ++i )
          (((CEffect *)this))->CEffect::CreateFromTemplate(i) /* [ROWTABLE] */;
        MagicUI_RefreshAndLayout(v88);
        PalScript_InitMainUIScripts(v89);
        g_nSceneState = 1;
        LOBYTE(this[4].m_szPath) = 1;
        *(_DWORD *)&this[1028].m_szTexPath[12] = 0;
        this[1028].m_fInvScale = 0.0f;
        *((_BYTE *)&this[4].m_ScreenPlane + 9) = 0;
        (((UICursor *)&this[1028].m_szTexPath[12]))->UICursor::_todo_541CC0();
        return 1;
      }
      else
      {
        LOBYTE(this[4].m_szPath) = 0;
        return 1;
      }
    case 1001:
      if ( LOBYTE(this[16].m_fOffsetParam) )
        return 1;
      v5 = (const char *)nMsg;
      v6 = 0;
      v7 = g_MonsterEntryTable;
      break;
    case 1002:
      if ( LOBYTE(this[16].m_fOffsetParam) )
        return 1;
      *(&this->m_nDefaultH + 1) = 0;
      v35 = 5;
      while ( 1 )
      {
        v36 = *(&this->m_nDefaultH + 1);
        if ( *((_BYTE *)&this[4].m_fileData + v36 + 1) )
        {
          if ( nMsg == g_MonsterEntryTable[v36] )
            break;
        }
        v37 = v36 + 1;
        *(&this->m_nDefaultH + 1) = v37;
        if ( v37 >= 5 )
        {
          switch ( nMsg )
          {
            case 10486018:
              *((_DWORD *)&this[1028].m_fInvScale + 1) = 0;
              if ( this[1028].m_szTexPath[12] )
                goto LABEL_100;
              (((CEffect *)this))->CEffect::CreateFromTemplate(0) /* [ROWTABLE] */;
              result = 1;
              break;
            case 10486019:
              *((_DWORD *)&this[1028].m_fInvScale + 1) = 1;
              if ( this[1028].m_szTexPath[13] )
                goto LABEL_100;
              (((CEffect *)this))->CEffect::CreateFromTemplate(1) /* [ROWTABLE] */;
              result = 1;
              break;
            case 10486020:
              *((_DWORD *)&this[1028].m_fInvScale + 1) = 2;
              if ( this[1028].m_szTexPath[14] )
                goto LABEL_100;
              (((CEffect *)this))->CEffect::CreateFromTemplate(2) /* [ROWTABLE] */;
              result = 1;
              break;
            case 10486021:
              *((_DWORD *)&this[1028].m_fInvScale + 1) = 3;
              if ( this[1028].m_szTexPath[15] )
                goto LABEL_100;
              (((CEffect *)this))->CEffect::CreateFromTemplate(3) /* [ROWTABLE] */;
              result = 1;
              break;
            case 10486022:
              *((_DWORD *)&this[1028].m_fInvScale + 1) = 5;
              if ( BYTE1(this[1028].m_fInvScale) )
                goto LABEL_100;
              (((CEffect *)this))->CEffect::CreateFromTemplate(5) /* [ROWTABLE] */;
              result = 1;
              break;
            case 10486023:
              *((_DWORD *)&this[1028].m_fInvScale + 1) = 6;
              if ( BYTE2(this[1028].m_fInvScale) )
                goto LABEL_100;
              (((CEffect *)this))->CEffect::CreateFromTemplate(6) /* [ROWTABLE] */;
              result = 1;
              break;
            case 10486024:
              *((_DWORD *)&this[1028].m_fInvScale + 1) = 4;
              if ( LOBYTE(this[1028].m_fInvScale) )
                goto LABEL_100;
              (((CEffect *)this))->CEffect::CreateFromTemplate(4) /* [ROWTABLE] */;
              result = 1;
              break;
            case 10486025:
              *((_DWORD *)&this[1028].m_fInvScale + 1) = 7;
              if ( !HIBYTE(this[1028].m_fInvScale) )
                (((CEffect *)this))->CEffect::CreateFromTemplate(7) /* [ROWTABLE] */;
              goto LABEL_100;
            default:
LABEL_100:
              result = 1;
              break;
          }
          return result;
        }
      }
      if ( *((_BYTE *)&this[4].m_ScreenPlane + 10) && *((_BYTE *)&this[4].m_ScreenPlane + 9) )
      {
        v38 = *(&this[4].m_nDefaultH + 1);
        if ( v38 < 0 )
          return 1;
        v39 = (char *)this + 12 * v38;
        v40 = (int)&v39[1192 * ((int)this[4].m_ScreenPlane + 8 * *((_DWORD *)&this[4].m_ScreenPlane + 1)) + 3356];
        if ( *(_BYTE *)(*(_DWORD *)&v39[1192
                                      * ((int)this[4].m_ScreenPlane + 8 * *((_DWORD *)&this[4].m_ScreenPlane + 1))
                                      + 3364]
                      + 577) == 1 )
        {
          p_m_nAlpha = (char *)&this[1086].m_nAlpha;
          do
          {
            (**(void ( ***)(char *, _DWORD))p_m_nAlpha)((char *)(p_m_nAlpha), (_DWORD)(0));
            p_m_nAlpha += 4892;
            --v35;
          }
          while ( v35 );
          (((CameraCtrl *)this))->CameraCtrl::CalcStatPower(v40);
          if ( v42 )
          {
            (**((void ( ***)(int *, int))&this[1086].m_nAlpha + 1223 * *(&this->m_nDefaultH + 1)))((int *)(&this[1086].m_nAlpha + 1223 * *(&this->m_nDefaultH + 1)), (int)(1));
            return 1;
          }
          CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
        }
      }
      return 1;
    case 1003:
      switch ( nMsg )
      {
        case 10486018:
          *((_DWORD *)&this[1028].m_fInvScale + 1) = 0;
          this[1028].m_szTexPath[12] = 0;
          result = 1;
          break;
        case 10486019:
          *((_DWORD *)&this[1028].m_fInvScale + 1) = 1;
          this[1028].m_szTexPath[13] = 0;
          result = 1;
          break;
        case 10486020:
          *((_DWORD *)&this[1028].m_fInvScale + 1) = 2;
          this[1028].m_szTexPath[14] = 0;
          result = 1;
          break;
        case 10486021:
          *((_DWORD *)&this[1028].m_fInvScale + 1) = 3;
          this[1028].m_szTexPath[15] = 0;
          result = 1;
          break;
        case 10486022:
          *((_DWORD *)&this[1028].m_fInvScale + 1) = 5;
          BYTE1(this[1028].m_fInvScale) = 0;
          result = 1;
          break;
        case 10486023:
          *((_DWORD *)&this[1028].m_fInvScale + 1) = 6;
          BYTE2(this[1028].m_fInvScale) = 0;
          result = 1;
          break;
        case 10486024:
          *((_DWORD *)&this[1028].m_fInvScale + 1) = 4;
          LOBYTE(this[1028].m_fInvScale) = 0;
          result = 1;
          break;
        case 10486025:
          *((_DWORD *)&this[1028].m_fInvScale + 1) = 7;
          HIBYTE(this[1028].m_fInvScale) = 0;
          goto LABEL_110;
        default:
LABEL_110:
          result = 1;
          break;
      }
      return result;
    case 1007:
      if ( LOBYTE(this[16].m_fOffsetParam) )
        return 1;
      *(&this[4].m_nDefaultH + 1) = wParam;
      if ( wParam >= 0 )
      {
        switch ( nMsg )
        {
          case 10486295:
            v45 = *(&this[4].m_nDefaultH + 1);
            if ( v45 >= (((UIListBox *)&this[1199].m_nRenderY))->UIListBox::GetItemData() )
              goto LABEL_148;
            v46 = (int *)(&this[16].m_nScaleY + 2384 * this[1028].m_nDeviceLost + 3 * v45);
            (((MainPropUI *)this))->MainPropUI::SetCaption(*v46, v46[1], v46[2]) /* [ROWTABLE] */;
            return 1;
          case 10486296:
            v47 = *(&this[4].m_nDefaultH + 1);
            if ( v47 >= (((UIListBox *)&this[1205].m_nHalfH))->UIListBox::GetItemData() )
              goto LABEL_148;
            v48 = (int *)(&this[40].m_nAlpha + 2384 * this[1028].m_nDeviceLost + 3 * v47);
            goto LABEL_136;
          case 10486297:
            v49 = *(&this[4].m_nDefaultH + 1);
            if ( v49 >= (((UIListBox *)&this[1211].m_nHalfHeight))->UIListBox::GetItemData() )
              goto LABEL_148;
            v48 = (int *)(&this[34].m_fRenderIntensity + 2384 * this[1028].m_nDeviceLost + 3 * v49);
            goto LABEL_136;
          case 10486304:
            v50 = *(&this[4].m_nDefaultH + 1);
            if ( v50 >= (((UIListBox *)&this[1217].m_nHeight))->UIListBox::GetItemData() )
              goto LABEL_148;
            v48 = (int *)(&this[22].m_fOffsetY + 2384 * this[1028].m_nDeviceLost + 3 * v50);
            goto LABEL_136;
          case 10486305:
            v51 = *(&this[4].m_nDefaultH + 1);
            if ( v51 >= (((UIListBox *)&this[1223].m_nTodo_02C))->UIListBox::GetItemData() )
              goto LABEL_148;
            v48 = (int *)(&this[28].m_fRender + 2384 * this[1028].m_nDeviceLost + 3 * v51);
            goto LABEL_136;
          case 10486306:
            v52 = *(&this[4].m_nDefaultH + 1);
            if ( v52 >= (((UIListBox *)&this[1229].m_fY))->UIListBox::GetItemData() )
              goto LABEL_148;
            v48 = (int *)(&this[46].m_ScreenPlane + 2384 * this[1028].m_nDeviceLost + 3 * v52 + 4);
            goto LABEL_136;
          case 10486307:
            v53 = *(&this[4].m_nDefaultH + 1);
            if ( v53 >= (((UIListBox *)&this[1235].m_nTodo_03C))->UIListBox::GetItemData() )
              goto LABEL_148;
            v48 = (int *)(&this[52].m_ScreenPlane + 2384 * this[1028].m_nDeviceLost + 3 * v53 + 2);
LABEL_136:
            (((MainPropUI *)this))->MainPropUI::SetCaption(*v48, v48[1], v48[2]) /* [ROWTABLE] */;
            result = 1;
            break;
          case 10486308:
            *(&this[4].m_nDefaultH + 1) = (((UIListBox *)&this[1241].m_fRenderX))->UIListBox::GetLockedSel();
            if ( *(&this[4].m_nDefaultH + 1) < (((UIListBox *)&this[1241].m_fRenderX))->UIListBox::GetItemData() )
            {
              (((MainPropUI *)this))->MainPropUI::FindValidSaveSlot() /* [ROWTABLE] */;
              SkillNum = (RoleAtt *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(&this[4].m_bVisible
                                      + 75 * *((unsigned __int8 *)&this[1535].m_nWidth + *(&this[4].m_nDefaultH + 1))));
              sprintf((char *const)&this->m_ScreenPlane + 4, unk_C10D38);
              v54 = (CHAR *)sub_458F70((LPCSTR)&SkillNum->Remark.skillCount + 90, (int)asc_5B74B8, this[1].m_szTexPath);
              if ( lstrlenA((const char *)v54) <= 0 )
              {
                (((RoleAtt *)SkillNum))->RoleAtt::FormatAttributeText();
                lstrcpyA((LPSTR)&this->m_ScreenPlane + 4, v55);
              }
              else
              {
                lstrcpyA((LPSTR)&this->m_ScreenPlane + 4, v54);
              }
              (((UICaption *)&this[1060].m_fOffsetX))->UICaption::SetEnable();
              (((UICaption *)(&this[1059].m_nTodo_0BC + 1)))->UICaption::SetEnable();
              (((UICaption *)&this[1062].m_fX))->UICaption::SetEnable();
              v56 = (char *)&SkillNum->Remark.skillCount + 30;
              if ( !strcmp((const char *)&SkillNum->Remark.skillCount + 30, unk_C10D38) )
                sprintf((char *const)&this->m_ScreenPlane + 4, "%s", "NONE");
              else
                sprintf(
                  (char *const)&this->m_ScreenPlane + 4,
                  "Item\\%s\\%s.pol",
                  (const char *)&SkillNum->Remark.skillCount + 30,
                  (const char *)&SkillNum->Remark.skillCount + 30);
              (((PalScript *)&this[1247].m_fOffsetY))->PalScript::LoadModel((const char *)&this->m_ScreenPlane + 4, 0);
              if ( !strcmp((const char *)&SkillNum->Remark.skillCount + 30, unk_C10D38) )
              {
                sprintf((char *const)&this->m_ScreenPlane + 4, "%s", "NONE");
              }
              else
              {
                Buffer = 0;
                memset(v96, 0, sizeof(v96));
                v97 = 0;
                v98 = 0;
                sprintf(&Buffer, "%s%s", v56, (const char *)&SkillNum->Remark.skillCount + 60);
                sprintf((char *const)&this->m_ScreenPlane + 4, "Item\\%s\\%s.tga", v56, &Buffer);
              }
              (((gbGeomNode *)*(gbGeomNode **)&this[1247].m_szTexPath[4]))->gbGeomNode::ReplaceTexture((const char *)&this->m_ScreenPlane + 4);
              this[1247].m_nScaleX = 1;
            }
            goto LABEL_148;
          default:
LABEL_148:
            result = 1;
            break;
        }
      }
      else
      {
        (((UICaption *)(&this[1059].m_nTodo_0BC + 1)))->UICaption::SetEnable();
        (((UICaption *)&this[1060].m_fOffsetX))->UICaption::SetEnable();
        return 1;
      }
      return result;
    case 1008:
      if ( LOBYTE(this[16].m_fOffsetParam) )
        return 1;
      switch ( nMsg )
      {
        case 10486295:
          Child = (((UIListBox *)&this[1199].m_nRenderY))->UIListBox::CreateChild();
          *(&this[4].m_nDefaultH + 1) = Child;
          if ( Child >= 0 )
          {
            if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(Child) )
            {
              CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
              (((MainPropUI *)this))->MainPropUI::SetPage(0) /* [ROWTABLE] */;
              m_nDeviceLost = this[1028].m_nDeviceLost;
              *((_BYTE *)&this[4].m_ScreenPlane + 8) = 1;
              *((_DWORD *)&this[4].m_ScreenPlane + 1) = m_nDeviceLost;
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 1;
              *((_BYTE *)&this[4].m_ScreenPlane + 9) = 1;
            }
            else
            {
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
            }
            this[4].m_ScreenPlane = ((gbTexture_D3D *)0);
            v79 = (const char *)off_5C7760;
          }
          else
          {
            v79 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486296:
          v59 = (((UIListBox *)&this[1205].m_nHalfH))->UIListBox::CreateChild();
          *(&this[4].m_nDefaultH + 1) = v59;
          if ( v59 >= 0 )
          {
            if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(v59) )
            {
              CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
              (((MainPropUI *)this))->MainPropUI::SetPage(0) /* [ROWTABLE] */;
              v60 = this[1028].m_nDeviceLost;
              *((_BYTE *)&this[4].m_ScreenPlane + 8) = 1;
              *((_DWORD *)&this[4].m_ScreenPlane + 1) = v60;
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 1;
              *((_BYTE *)&this[4].m_ScreenPlane + 9) = 1;
            }
            else
            {
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
            }
            this[4].m_ScreenPlane = (gbTexture_D3D *)4;
            v79 = (const char *)off_5C7760;
          }
          else
          {
            v79 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486297:
          v61 = (((UIListBox *)&this[1211].m_nHalfHeight))->UIListBox::CreateChild();
          *(&this[4].m_nDefaultH + 1) = v61;
          if ( v61 < 0 )
          {
            v62 = g_pCScreenMode_5C7768;
            goto LABEL_208;
          }
          if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(v61) )
          {
            CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
            (((MainPropUI *)this))->MainPropUI::SetPage(0) /* [ROWTABLE] */;
            v63 = this[1028].m_nDeviceLost;
            *((_BYTE *)&this[4].m_ScreenPlane + 8) = 1;
            *((_DWORD *)&this[4].m_ScreenPlane + 1) = v63;
            *((_BYTE *)&this[4].m_ScreenPlane + 10) = 1;
            *((_BYTE *)&this[4].m_ScreenPlane + 9) = 1;
          }
          else
          {
            *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
          }
          this[4].m_ScreenPlane = (gbTexture_D3D *)3;
          goto LABEL_207;
        case 10486304:
          v64 = (((UIListBox *)&this[1217].m_nHeight))->UIListBox::CreateChild();
          *(&this[4].m_nDefaultH + 1) = v64;
          if ( v64 >= 0 )
          {
            if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(v64) )
            {
              CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
              (((MainPropUI *)this))->MainPropUI::SetPage(0) /* [ROWTABLE] */;
              v65 = this[1028].m_nDeviceLost;
              *((_BYTE *)&this[4].m_ScreenPlane + 8) = 1;
              *((_DWORD *)&this[4].m_ScreenPlane + 1) = v65;
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 1;
              *((_BYTE *)&this[4].m_ScreenPlane + 9) = 1;
            }
            else
            {
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
            }
            this[4].m_ScreenPlane = (gbTexture_D3D *)1;
            v79 = (const char *)off_5C7760;
          }
          else
          {
            v79 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486305:
          v66 = (((UIListBox *)&this[1223].m_nTodo_02C))->UIListBox::CreateChild();
          *(&this[4].m_nDefaultH + 1) = v66;
          if ( v66 >= 0 )
          {
            if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(v66) )
            {
              CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
              (((MainPropUI *)this))->MainPropUI::SetPage(0) /* [ROWTABLE] */;
              v67 = this[1028].m_nDeviceLost;
              *((_BYTE *)&this[4].m_ScreenPlane + 8) = 1;
              *((_DWORD *)&this[4].m_ScreenPlane + 1) = v67;
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 1;
              *((_BYTE *)&this[4].m_ScreenPlane + 9) = 1;
            }
            else
            {
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
            }
            this[4].m_ScreenPlane = (gbTexture_D3D *)2;
            v79 = (const char *)off_5C7760;
          }
          else
          {
            v79 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486306:
          v68 = (((UIListBox *)&this[1229].m_fY))->UIListBox::CreateChild();
          *(&this[4].m_nDefaultH + 1) = v68;
          if ( v68 < 0 )
          {
            v62 = g_pCScreenMode_5C7768;
            goto LABEL_208;
          }
          if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(v68) )
          {
            CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
            (((MainPropUI *)this))->MainPropUI::SetPage(0) /* [ROWTABLE] */;
            v69 = this[1028].m_nDeviceLost;
            *((_BYTE *)&this[4].m_ScreenPlane + 8) = 1;
            *((_DWORD *)&this[4].m_ScreenPlane + 1) = v69;
            *((_BYTE *)&this[4].m_ScreenPlane + 10) = 1;
            *((_BYTE *)&this[4].m_ScreenPlane + 9) = 1;
          }
          else
          {
            *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
          }
          this[4].m_ScreenPlane = (gbTexture_D3D *)5;
          goto LABEL_207;
        case 10486307:
          v70 = (((UIListBox *)&this[1235].m_nTodo_03C))->UIListBox::CreateChild();
          *(&this[4].m_nDefaultH + 1) = v70;
          if ( v70 >= 0 )
          {
            if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(v70) )
            {
              CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
              (((MainPropUI *)this))->MainPropUI::SetPage(0) /* [ROWTABLE] */;
              v71 = this[1028].m_nDeviceLost;
              *((_BYTE *)&this[4].m_ScreenPlane + 8) = 1;
              *((_DWORD *)&this[4].m_ScreenPlane + 1) = v71;
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 1;
              *((_BYTE *)&this[4].m_ScreenPlane + 9) = 1;
            }
            else
            {
              *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
            }
            this[4].m_ScreenPlane = (gbTexture_D3D *)6;
            v79 = (const char *)off_5C7760;
          }
          else
          {
            v79 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486308:
          v72 = (((UIListBox *)&this[1241].m_fRenderX))->UIListBox::CreateChild();
          *(&this[4].m_nDefaultH + 1) = v72;
          if ( v72 < 0 )
          {
            v79 = g_pCScreenMode_5C7768;
            break;
          }
          if ( !(unsigned __int8)CameraCtrl_InitBlendState(v72) )
            return 1;
          (((MainPropUI *)this))->MainPropUI::FindValidSaveSlot() /* [ROWTABLE] */;
          v92 = (const char *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(&this[4].m_bVisible
                                + 75 * *((unsigned __int8 *)&this[1535].m_nWidth + *(&this[4].m_nDefaultH + 1))));
          sprintf((char *const)&this->m_ScreenPlane + 4, unk_C10D38);
          v73 = (CHAR *)sub_458F70(v92 + 96, (int)asc_5B74B8, this[1].m_szTexPath);
          if ( lstrlenA((const char *)v73) <= 0 )
          {
            (((RoleAtt *)v74))->RoleAtt::FormatAttributeText();
            lstrcpyA((LPSTR)&this->m_ScreenPlane + 4, v75);
          }
          else
          {
            lstrcpyA((LPSTR)&this->m_ScreenPlane + 4, v73);
          }
          (((UICaption *)&this[1060].m_fOffsetX))->UICaption::SetEnable();
          (((UICaption *)(&this[1059].m_nTodo_0BC + 1)))->UICaption::SetEnable();
          (((UICaption *)&this[1062].m_fX))->UICaption::SetEnable();
          v76 = (const char *)(v92 + 36);
          if ( !strcmp(v92 + 36, unk_C10D38) )
            sprintf((char *const)&this->m_ScreenPlane + 4, "%s", "NONE");
          else
            sprintf((char *const)&this->m_ScreenPlane + 4, "Item\\%s\\%s.pol", v92 + 36, v92 + 36);
          (((PalScript *)&this[1247].m_fOffsetY))->PalScript::LoadModel((const char *)&this->m_ScreenPlane + 4, 0);
          if ( !strcmp(v92 + 36, unk_C10D38) )
          {
            sprintf((char *const)&this->m_ScreenPlane + 4, "%s", "NONE");
          }
          else
          {
            Buffer = 0;
            memset(v96, 0, sizeof(v96));
            v97 = 0;
            v98 = 0;
            sprintf(&Buffer, "%s%s", v76, v92 + 66);
            sprintf((char *const)&this->m_ScreenPlane + 4, "Item\\%s\\%s.tga", v76, &Buffer);
          }
          (((gbGeomNode *)*(gbGeomNode **)&this[1247].m_szTexPath[4]))->gbGeomNode::ReplaceTexture((const char *)&this->m_ScreenPlane + 4);
          this[1247].m_nScaleX = 1;
          this[4].m_ScreenPlane = (gbTexture_D3D *)7;
          sprintf((char *const)&this->m_ScreenPlane + 4, "\\n            %s", (const char *)&dword_DC8D3C);
          (((UICaption *)(&this[1044].m_fInvScale + 1)))->UICaption::SetEnable();
          (((UIRoleSelect *)&this[1042].m_nAlpha))->UIRoleSelect::SetByte(1);
          (((MainPropUI *)this))->MainPropUI::SetPage(0) /* [ROWTABLE] */;
LABEL_207:
          v62 = (const char *)off_5C7760;
LABEL_208:
          v79 = (const char *)v62;
          break;
        default:
          return 1;
      }
LABEL_209:
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v79, 1);
      return 1;
    case 1009:
      return 1;
    case 1010:
      if ( LOBYTE(this[16].m_fOffsetParam) )
        return 1;
      if ( *((int *)&this[4].m_ScreenPlane + 1) >= 0 )
      {
        *((_BYTE *)&this[4].m_ScreenPlane + 9) = 0;
        *((_BYTE *)&this[4].m_ScreenPlane + 11) = 0;
        *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
        *((_BYTE *)&this[4].m_ScreenPlane + 8) = 0;
        this[4].m_ScreenPlane = (gbTexture_D3D *)-1;
        *((_DWORD *)&this[4].m_ScreenPlane + 1) = -1;
        (((MainPropUI *)this))->MainPropUI::SetPage(1u) /* [ROWTABLE] */;
        v43 = (char *)&this[1086].m_nAlpha;
        v44 = 5;
        do
        {
          (**(void ( ***)(char *, _DWORD))v43)((char *)(v43), (_DWORD)(0));
          v43 += 4892;
          --v44;
        }
        while ( v44 );
      }
      return 1;
    case 1020:
      if ( LOBYTE(this[16].m_fOffsetParam) )
        return 1;
      v30 = 0;
      v31 = g_MonsterEntryTable;
      while ( nMsg != *v31 )
      {
        ++v31;
        ++v30;
        if ( (int)v31 >= (int)&g_ArcSceneMonsterTable )
          return 1;
      }
      if ( *(&this[4].m_nDefaultH + 1) >= 0 && *((_BYTE *)&this[4].m_ScreenPlane + 8) )
      {
        if ( (unsigned __int8)ScriptSystem_ProcessScriptEvent(*((_DWORD *)&this[4].m_ScreenPlane + 1)) )
        {
          LineupUI::LoadRoleData();
          (((MainPropUI *)this))->MainPropUI::SetPage(1u) /* [ROWTABLE] */;
        }
        if ( !*((_BYTE *)&this[4].m_ScreenPlane + 9) )
        {
          *((_BYTE *)&this[4].m_ScreenPlane + 8) = 0;
          *((_DWORD *)&this[4].m_ScreenPlane + 1) = -1;
          *((_BYTE *)&this[4].m_ScreenPlane + 11) = 0;
          *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
        }
        return 1;
      }
      else
      {
        v32 = *((_BYTE *)&this[4].m_ScreenPlane + 9);
        this[1028].m_nDeviceLost = v30;
        if ( !v32 )
        {
          MagicUI_UpdateViewListItems(v30);
          (((MainPropUI *)this))->MainPropUI::DisplayCaption(this[1028].m_nDeviceLost) /* [ROWTABLE] */;
          v33 = (char *)&this[1086].m_nAlpha;
          v34 = 5;
          do
          {
            (**(void ( ***)(char *, _DWORD))v33)((char *)(v33), (_DWORD)(0));
            v33 += 4892;
            --v34;
          }
          while ( v34 );
        }
        return 1;
      }
    default:
      return (((UIWnd *)this))->UIWnd::OnMessage(nVal1, nMsg, wParam) /* [ROWTABLE] */;
  }
  do
  {
    if ( nMsg == *v7 )
    {
      v90 = v6;
      if ( *((_BYTE *)&this[4].m_ScreenPlane + 10) )
      {
        if ( !*((_BYTE *)&this[4].m_ScreenPlane + 9) )
          goto LABEL_35;
        v13 = 5;
        v14 = (char *)&this[1086].m_nAlpha;
        nVala = (int *)&this[16].m_nScaleY
              + 298 * ((int)this[4].m_ScreenPlane + 8 * *((_DWORD *)&this[4].m_ScreenPlane + 1))
              + 3 * *(&this[4].m_nDefaultH + 1);
        do
        {
          (**(void ( ***)(char *, _DWORD))v14)((char *)(v14), (_DWORD)(0));
          v14 += 4892;
          --v13;
        }
        while ( v13 );
        v15 = *(_BYTE *)(nVala[2] + 577);
        if ( v15 == 1 )
        {
          (((CameraCtrl *)this))->CameraCtrl::CalcStatPower((int)nVala);
          if ( v16 )
            (**((void ( ***)(int *, int))&this[1086].m_nAlpha + 1223 * v90))((int *)(&this[1086].m_nAlpha + 1223 * v90), (int)(1));
          else
            CameraCtrl_ProcessCameraTask(*(&this[4].m_nDefaultH + 1));
        }
        else if ( v15 == 2 )
        {
          v17 = 0;
          v18 = (char *)&this[1086].m_nAlpha;
          do
          {
            if ( *((_BYTE *)&this[4].m_fileData + v17 + 1) )
            {
              (((CameraCtrl *)this))->CameraCtrl::CalcStatPower((int)nVala);
              if ( v19 )
                (**(void ( ***)(char *, int))v18)((char *)(v18), (int)(1));
              else
                (**(void ( ***)(char *, _DWORD))v18)((char *)(v18), (_DWORD)(0));
            }
            ++v17;
            v18 += 4892;
          }
          while ( v17 < 5 );
        }
      }
      if ( *((_BYTE *)&this[4].m_ScreenPlane + 9) )
      {
LABEL_36:
        v79 = (const char *)off_5C775C;
        goto LABEL_209;
      }
LABEL_35:
      this[1028].m_nDeviceLost = v90;
      MagicUI_UpdateViewListItems(v90);
      (((MainPropUI *)this))->MainPropUI::DisplayCaption(v90) /* [ROWTABLE] */;
      goto LABEL_36;
    }
    ++v7;
    ++v6;
  }
  while ( (int)v7 < (int)&g_ArcSceneMonsterTable );
  v8 = (const char **)&off_56C548;
  v9 = 0;
  // [overlay-fix 2026-10-27] 垃圾形赋值——待语义修复
  // nVal = (int)&off_56C548;
  nVal = 0;
  while ( v5 != *v8 )
  {
LABEL_17:
    ++v8;
    ++v9;
    nVal = (const char **)v8;
    if ( (int)v8 >= (int)g_MonsterEntryTable )
      goto LABEL_39;
  }
  if ( !LOBYTE(this[16].m_fOffsetParam) )
  {
    MagicUI_InitUILayout(v9);
    v78 = (const void *)off_5C775C;
    v10 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v10))->CScreenMode::AudioSetPosition(v78, 1);
    *(&this[4].m_nDefaultH + 1) = -1;
    *((_BYTE *)&this[4].m_ScreenPlane + 9) = 0;
    *((_BYTE *)&this[4].m_ScreenPlane + 11) = 0;
    *((_BYTE *)&this[4].m_ScreenPlane + 10) = 0;
    (((MainPropUI *)this))->MainPropUI::SetPage(1u) /* [ROWTABLE] */;
    v11 = (char *)&this[1086].m_nAlpha;
    v12 = 5;
    do
    {
      (**(void ( ***)(char *, _DWORD))v11)((char *)(v11), (_DWORD)(0));
      v11 += 4892;
      --v12;
    }
    while ( v12 );
    v8 = (const char **)nVal;
    v5 = (const char *)nMsg;
    goto LABEL_17;
  }
  p_m_nTodo_03C = (int *)&this[1185].m_nTodo_03C;
  v21 = 8;
  do
  {
    sub_445E50((int)p_m_nTodo_03C);
    p_m_nTodo_03C += 86;
    --v21;
  }
  while ( v21 );
LABEL_39:
  switch ( (unsigned int)v5 )
  {
    case 0xA00102u:
      v80 = (const void *)off_5C775C;
      v22 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v22))->CScreenMode::AudioSetPosition(v80, 1);
      (((MainEquipUI *)this[255].m_nWidth))->MainEquipUI::HandleMessage(0);
      break;
    case 0xA00104u:
      v81 = (const void *)off_5C775C;
      v23 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v23))->CScreenMode::AudioSetPosition(v81, 1);
      (((MainEquipUI *)this[255].m_nWidth))->MainEquipUI::HandleMessage(2);
      break;
    case 0xA00105u:
      v82 = (const void *)off_5C775C;
      v24 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v24))->CScreenMode::AudioSetPosition(v82, 1);
      (((MainEquipUI *)this[255].m_nWidth))->MainEquipUI::HandleMessage(1);
      break;
    case 0xA00106u:
      v83 = (const void *)off_5C775C;
      v25 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v25))->CScreenMode::AudioSetPosition(v83, 1);
      (((MainEquipUI *)this[255].m_nWidth))->MainEquipUI::HandleMessage(5);
      break;
    case 0xA00107u:
      v84 = (const void *)off_5C775C;
      v26 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v26))->CScreenMode::AudioSetPosition(v84, 1);
      (((MainEquipUI *)this[255].m_nWidth))->MainEquipUI::HandleMessage(6);
      break;
    case 0xA00108u:
      v85 = (const void *)off_5C775C;
      v27 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v27))->CScreenMode::AudioSetPosition(v85, 1);
      (((MainEquipUI *)this[255].m_nWidth))->MainEquipUI::HandleMessage(4);
      break;
    case 0xA00109u:
      v86 = (const void *)off_5C775C;
      v28 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v28))->CScreenMode::AudioSetPosition(v86, 1);
      (((MainEquipUI *)this[255].m_nWidth))->MainEquipUI::HandleMessage(7);
      break;
    case 0xA00110u:
      v87 = (const void *)off_5C775C;
      v29 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v29))->CScreenMode::AudioSetPosition(v87, 1);
      (((MainEquipUI *)this[255].m_nWidth))->MainEquipUI::HandleMessage(9);
      break;
    default:
      return 1;
  }
  return 1;
}

// 0x004B4820
void RenderTarget::SetVisible(BOOL bVisible)
{
  LOBYTE(this->m_bVisible) = bVisible;
}

// 0x004B4840
void RenderTarget::SetField084(int nVal1)
{
  LODWORD(this->m_fRenderIntensity) = nVal1;
}

// 0x004B4850
void RenderTarget::SetColor(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b)
{
  int v5; // edi

  BYTE2(this->m_nAlpha) = r;
  BYTE1(this->m_nAlpha) = g;
  LOBYTE(this->m_nAlpha) = b;
  v5 = 16 * (rand() % 12);
  BYTE2(this->m_nColor) = (__int64)*(float *)((char *)&unk_5D3C68 + v5);
  BYTE1(this->m_nColor) = (__int64)*(float *)(v5 + 6110308);
  LOBYTE(this->m_nColor) = (__int64)*(float *)(v5 + 6110304);
}

// 0x004B48B0
void RenderTarget::SetAlpha(unsigned __int8 nAlpha)
{
  HIBYTE(this->m_nAlpha) = nAlpha;
  HIBYTE(this->m_nColor) = (__int64)*(&unk_5D3C6C + 4 * (rand() % 12));
}

// 0x004B48E0
void RenderTarget::SetSize(int nHeight)
{
  float v2; // [esp+0xC] [ebp+0x8]

  *(_DWORD *)&this[2].m_szTexPath[12] = nHeight;
  this[2].m_fInvScale = v2;
  this->m_nHalfWidth = nHeight / 2;
  this->m_nHalfHeight = SLODWORD(v2) / 2;
}

// 0x004B4910
void RenderTarget::SetState(int nVal1)
{
  *((_DWORD *)&this[2].m_fInvScale + 1) = nVal1;
}

// 0x004B4920
gbVFileSystem * RenderTarget::LoadTexture(const char *szFilename)
{
  char *m_szTexPath; // edi
  gbVFileSystem *result; // eax
  gbRefObject *m_nHalfW; // ecx
  gbTexture *v6; // eax

  m_szTexPath = this->m_szTexPath;
  result = (gbVFileSystem *)lstrcpyA(this->m_szTexPath, szFilename);
  if ( m_szTexPath )
  {
    m_nHalfW = (gbRefObject *)this[2].m_nHalfW;
    if ( m_nHalfW )
    {
      (((gbRefObject *)m_nHalfW))->gbRefObject::Release();
      this[2].m_nHalfW = 0;
    }
    ((OpenBaseFile *)&szFilename)->OpenBaseFile::OpenBaseFile();
    v6 = (gbTexture *)gfxMgr->NewTexture((const char *)m_szTexPath);
    this[2].m_nHalfW = (int)v6;
    if ( v6 )
      (((gbTexture *)v6))->gbTexture::LoadTexture(1);
    ((OpenNULLFile *)&szFilename)->OpenNULLFile::OpenNULLFile();
  }
  return result;
}

// 0x004B49C0
void RenderTarget::UpdateTransform(float fX, float fY)
{
  float v4; // st7
  __int64 v5; // rax
  float m_nHeight; // st7
  int v7; // eax
  gbTexture_D3D *m_Texture; // ebx
  int v9; // edi
  int v10; // eax
  int m_nHalfWidth; // ecx
  float v12; // st7
  float v13; // st6
  float v14; // st6
  int m_nHalfHeight; // ecx
  float v16; // st7
  int fXb; // [esp+0xC] [ebp+0x4]
  float fXa; // [esp+0xC] [ebp+0x4]

  this->m_fOffsetParam = fX;
  this->m_fRender = fY;
  this->m_fX = fX;
  this->m_fY = fY;
  this->m_Texture = ((gbTexture_D3D *)((gbTexture_D3D *)(__int64)fY));
  v4 = (float)(this->m_nWidth / 2);
  this->m_iMode = (__int64)(fX - v4);
  v5 = (__int64)(v4 + fX);
  m_nHeight = (float)this->m_nHeight;
  this->m_nRenderX = v5;
  this->m_nRenderY = (__int64)(m_nHeight + fY);
  v7 = rand();
  m_Texture = (gbTexture_D3D *)this->m_Texture;
  v9 = this->m_nHeight;
  this->m_fRenderX = (float)(this->m_iMode + v7 % this->m_nWidth);
  v10 = rand();
  m_nHalfWidth = this->m_nHalfWidth;
  v12 = (float)((int)m_Texture + v10 % v9);
  fXb = this->m_nRenderX - m_nHalfWidth;
  this->m_fRenderY = v12;
  v13 = (float)fXb;
  if ( v13 < this->m_fRenderX )
    this->m_fRenderX = v13;
  v14 = (float)(this->m_iMode + m_nHalfWidth);
  if ( v14 > this->m_fRenderX )
    this->m_fRenderX = v14;
  m_nHalfHeight = this->m_nHalfHeight;
  fXa = (float)(this->m_nRenderY - m_nHalfHeight);
  if ( v12 > fXa )
    this->m_fRenderY = fXa;
  v16 = (float)((int)m_Texture + m_nHalfHeight);
  if ( v16 > this->m_fRenderY )
    this->m_fRenderY = v16;
  *(float *)&this->m_nDefaultH = (double)v9 + this->m_fRender;
}

// 0x004B4B10
void RenderTarget::CalcRenderDimensions(int nVal, int nVal2)
{
  float m_fRender; // st7
  __int64 v5; // rax
  float v6; // st7
  float m_fOffsetParam; // st6
  __int64 v8; // rax
  float v9; // st7
  int v10; // eax
  int m_nHeight; // edi
  gbTexture_D3D *m_Texture; // ebx
  int v13; // eax
  int m_nHalfWidth; // ecx
  float v15; // st7
  float v16; // st6
  float v17; // st6
  int m_nHalfHeight; // ecx
  float v19; // st7
  int nVala; // [esp+0x10] [ebp+0x4]
  int nVal2b; // [esp+0x14] [ebp+0x8]
  float nVal2a; // [esp+0x14] [ebp+0x8]

  this->m_nWidth = nVal;
  this->m_nHeight = nVal2;
  m_fRender = this->m_fRender;
  nVala = nVal / 2;
  this->m_nHalfW = nVala;
  *(_DWORD *)&this->m_nHalfH = nVal2 / 2;
  v5 = (__int64)m_fRender;
  v6 = (float)nVala;
  m_fOffsetParam = this->m_fOffsetParam;
  this->m_Texture = ((gbTexture_D3D *)((gbTexture_D3D *)v5));
  v8 = (__int64)(m_fOffsetParam - v6);
  v9 = v6 + this->m_fOffsetParam;
  this->m_iMode = v8;
  this->m_nRenderX = (__int64)v9;
  this->m_nRenderY = (__int64)((double)nVal2 + this->m_fRender);
  v10 = rand();
  m_nHeight = this->m_nHeight;
  m_Texture = (gbTexture_D3D *)this->m_Texture;
  this->m_fRenderX = (float)(this->m_iMode + v10 % this->m_nWidth);
  v13 = rand();
  m_nHalfWidth = this->m_nHalfWidth;
  v15 = (float)((int)m_Texture + v13 % m_nHeight);
  nVal2b = this->m_nRenderX - m_nHalfWidth;
  this->m_fRenderY = v15;
  v16 = (float)nVal2b;
  if ( v16 < this->m_fRenderX )
    this->m_fRenderX = v16;
  v17 = (float)(this->m_iMode + m_nHalfWidth);
  if ( v17 > this->m_fRenderX )
    this->m_fRenderX = v17;
  m_nHalfHeight = this->m_nHalfHeight;
  nVal2a = (float)(this->m_nRenderY - m_nHalfHeight);
  if ( v15 > nVal2a )
    this->m_fRenderY = nVal2a;
  v19 = (float)((int)m_Texture + m_nHalfHeight);
  if ( v19 > this->m_fRenderY )
    this->m_fRenderY = v19;
  *(float *)&this->m_nDefaultH = (double)m_nHeight + this->m_fRender;
}

// 0x004B4C60
void RenderTarget::Render(int nY, int nWidth, int nHeight)
{
  int v5; // eax
  gbTexture_D3D *m_Texture; // ebx
  int m_nHeight; // edi
  int v8; // eax
  int m_nHalfWidth; // ecx
  float v10; // st7
  float v11; // st6
  float v12; // st6
  int m_nHalfHeight; // ecx
  float v14; // st7
  int nYb; // [esp+0x18] [ebp+0x4]
  float nYa; // [esp+0x18] [ebp+0x4]
  int v17; // [esp+0x24] [ebp+0x10]

  this->m_nWidth = nHeight - nY;
  this->m_nHeight = v17 - nWidth;
  this->m_nHalfW = (nHeight - nY) / 2;
  *(_DWORD *)&this->m_nHalfH = (v17 - nWidth) / 2;
  this->m_iMode = nY;
  this->m_Texture = ((gbTexture_D3D *)((gbTexture_D3D *)nWidth));
  this->m_nRenderX = nHeight;
  this->m_nRenderY = v17;
  v5 = rand();
  m_Texture = (gbTexture_D3D *)this->m_Texture;
  m_nHeight = this->m_nHeight;
  this->m_fRenderX = (float)(this->m_iMode + v5 % this->m_nWidth);
  v8 = rand();
  m_nHalfWidth = this->m_nHalfWidth;
  v10 = (float)((int)m_Texture + v8 % m_nHeight);
  nYb = this->m_nRenderX - m_nHalfWidth;
  this->m_fRenderY = v10;
  v11 = (float)nYb;
  if ( v11 < this->m_fRenderX )
    this->m_fRenderX = v11;
  v12 = (float)(this->m_iMode + m_nHalfWidth);
  if ( v12 > this->m_fRenderX )
    this->m_fRenderX = v12;
  m_nHalfHeight = this->m_nHalfHeight;
  nYa = (float)(this->m_nRenderY - m_nHalfHeight);
  if ( v10 > nYa )
    this->m_fRenderY = nYa;
  v14 = (float)((int)m_Texture + m_nHalfHeight);
  if ( v14 > this->m_fRenderY )
    this->m_fRenderY = v14;
  *(float *)&this->m_nDefaultH = (double)m_nHeight + this->m_fRender;
}

// 0x004B4D80
void RenderTarget::SetOffset(float fVal1, float fVal2)
{
  this->m_fOffsetX = fVal1;
  this->m_fOffsetY = fVal2;
}

// 0x004B4DA0
void RenderTarget::SetScale(int nVal1, int nVal2)
{
  this->m_nScaleX = nVal1;
  this->m_nScaleY = nVal2;
}

// 0x004BB050
void RenderTarget::ReadVFile(gbVFile *pFile)
{
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(this, 0x40u, pFile);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&this->m_fileHeader, 4u, pFile);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&this->m_fRenderX, 4u, pFile);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&this->m_fFileParam, 4u, pFile);
}

// 0x004BB0B0
int RenderTarget::ClearTexture()
{
  int result; // eax

  this->m_iMode = 0;
  this->m_Texture = ((gbTexture_D3D *)0);
  this->m_nRenderX = 0;
  this->m_fRenderX = 0.0f;
  this->m_fileHeader = 0.0f;
  this->m_nTodo_03C = 0;
  this->m_nTodo_038 = 0;
  this->m_fX = 0.0f;
  this->m_nTodo_02C = 0.0f;
  *(_DWORD *)&this->m_nTodo_028 = 0;
  this->m_nHeight = 0;
  this->m_nHalfHeight = 0;
  this->m_nHalfWidth = 0;
  *(_DWORD *)&this->m_nHalfH = 0;
  this->m_nHalfW = 0;
  result = 1065353216;
  this->m_fRenderY = 1.0f;
  this->m_fY = 1.0f;
  this->m_nWidth = 1065353216;
  this->m_nRenderY = 1065353216;
  return result;
}

// 0x004BB0F0
int RenderTarget::ApplyScale(float fVal)
{
  float v2; // st7
  int result; // eax
  float v4; // st7

  v2 = 1.0f / this->m_fInvScale;
  result = LODWORD(fVal);
  this->m_fileData = v2 * this->m_fileData;
  this->m_fFileParam = v2 * this->m_fFileParam;
  *(float *)&this->m_nColor = v2 * *(float *)&this->m_nColor;
  v4 = 1.0f / this->m_fInvScale;
  this->m_fileHeader = v4 * this->m_fileHeader;
  this->m_fRenderX = v4 * this->m_fRenderX;
  this->m_fRenderY = v4 * this->m_fRenderY;
  this->m_fileData = fVal * this->m_fileData;
  this->m_fFileParam = fVal * this->m_fFileParam;
  *(float *)&this->m_nColor = fVal * *(float *)&this->m_nColor;
  this->m_fileHeader = fVal * this->m_fileHeader;
  this->m_fRenderX = fVal * this->m_fRenderX;
  this->m_fRenderY = fVal * this->m_fRenderY;
  this->m_fInvScale = fVal;
  return result;
}

// 0x004BB180
int RenderTarget::SetRenderState(int nVal)
{
  int result; // eax

  result = nVal;
  this[1].m_nScaleY = nVal;
  return result;
}

// 0x004BC7B0
void RenderTarget::UpdateTimeStep()
{
  ;
}

// 0x004BC8A0
int RenderTarget::RenderToTexture()
{
  RenderTarget *v1; // ebp
  float xy; // ebx
  int v3; // edi
  int m_nTodo_03C; // eax
  int v5; // eax
  int v6; // edx
  double v7; // st7
  int v8; // eax
  int m_nScaleX; // eax
  float *v10; // esi
  double v11; // st7
  double v12; // st7
  int v13; // ebp
  int v14; // edi
  __int64 v15; // rax
  double v16; // st7
  int v17; // ebp
  int v18; // edi
  __int64 v19; // rax
  double v20; // st7
  double v21; // st6
  int v22; // ebp
  int v23; // edi
  __int64 v24; // rax
  double v25; // st7
  double v26; // st6
  int v27; // ebp
  int v28; // edi
  __int64 v29; // rax
  int v30; // ecx
  int v31; // eax
  int v33; // [esp+C8h] [ebp-0x224]
  float v34; // [esp+C8h] [ebp-0x224]
  float v35; // [esp+DCh] [ebp-0x210]
  float v36; // [esp+E0h] [ebp-0x20C]
  float v37; // [esp+E4h] [ebp-0x208]
  float v38; // [esp+E8h] [ebp-0x204]
  int v39; // [esp+ECh] [ebp-0x200]
  int v40; // [esp+ECh] [ebp-0x200]
  int v41; // [esp+ECh] [ebp-0x200]
  float v42; // [esp+F0h] [ebp-0x1FC]
  int v43; // [esp+F0h] [ebp-0x1FC]
  float v44; // [esp+F4h] [ebp-0x1F8]
  float v45; // [esp+F8h] [ebp-0x1F4] BYREF
  float v46; // [esp+FCh] [ebp-0x1F0]
  float v47[2]; // [esp+0x100] [ebp-0x1EC]
  float v48; // [esp+0x108] [ebp-0x1E4]
  int v49; // [esp+0x10C] [ebp-0x1E0]
  int v50; // [esp+0x110] [ebp-0x1DC]
  float v51; // [esp+0x114] [ebp-0x1D8]
  float v52; // [esp+0x118] [ebp-0x1D4] BYREF
  float v53; // [esp+0x11C] [ebp-0x1D0]
  float v54; // [esp+0x120] [ebp-0x1CC]
  char *v55; // [esp+0x128] [ebp-0x1C4]
  float v56; // [esp+0x12C] [ebp-0x1C0]
  RenderTarget *v57; // [esp+0x130] [ebp-0x1BC]
  int v58; // [esp+0x134] [ebp-0x1B8]
  gbMatrixStack *v59; // [esp+0x138] [ebp-0x1B4]
  float v60[5]; // [esp+0x13C] [ebp-0x1B0]
  float v61; // [esp+0x150] [ebp-0x19C]
  float v62; // [esp+0x154] [ebp-0x198]
  int v63[7]; // [esp+0x158] [ebp-0x194] BYREF
  float v64; // [esp+0x174] [ebp-0x178]
  float v65; // [esp+0x178] [ebp-0x174]
  float v66; // [esp+0x180] [ebp-0x16C]
  float v67; // [esp+0x184] [ebp-0x168]
  float v68; // [esp+0x18C] [ebp-0x160]
  float v69; // [esp+0x190] [ebp-0x15C]
  float v70; // [esp+0x198] [ebp-0x154]
  float v71; // [esp+0x19C] [ebp-0x150]
  float v72; // [esp+0x1A4] [ebp-0x148]
  float v73; // [esp+0x1A8] [ebp-0x144]
  float v74; // [esp+0x1B0] [ebp-0x13C]
  float v75; // [esp+0x1B4] [ebp-0x138]
  float v76; // [esp+0x1BC] [ebp-0x130]
  float v77; // [esp+0x1C0] [ebp-0x12C]
  _DWORD v78[4]; // [esp+0x1C4] [ebp-0x128] BYREF
  float v79; // [esp+0x1D4] [ebp-0x118]
  float v80; // [esp+0x1D8] [ebp-0x114]
  _DWORD v81[4]; // [esp+0x1DC] [ebp-0x110] BYREF
  float v82; // [esp+0x1EC] [ebp-0x100]
  float v83; // [esp+0x1F0] [ebp-FCh]
  float v84; // [esp+0x1F8] [ebp-F4h]
  float v85; // [esp+0x1FC] [ebp-F0h]
  float v86; // [esp+0x204] [ebp-E8h]
  float v87; // [esp+0x208] [ebp-E4h]
  int v88[16]; // [esp+0x20C] [ebp-E0h] BYREF
  float v89[16]; // [esp+0x24C] [ebp-A0h] BYREF
  float v90[24]; // [esp+0x28C] [ebp-0x60] BYREF

  v1 = this;
  v57 = this;
  qmemcpy(v89, (((gbGfxManager *)gfxMgr))->gbGfxManager::GetWorldMatrix(), sizeof(v89));
  ParticleEffect_UpdateParticles(v1[1814].m_nTodo_038);
  xy = gfxMgr[1].InvViewMatrix.xy;
  v59 = gfxMgr->pMatrixStack[1];
  (((gbMatrixStack *)v59))->gbMatrixStack::Push();
  if ( v1[1813].m_nScaleY != 1 )
    (((gbGfxManager *)gfxMgr))->gbGfxManager::IdentityWorldMatrix();
  (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 60))(gfxMgr);
  qmemcpy(v89, (((gbGfxManager *)gfxMgr))->gbGfxManager::GetViewMatrix(), sizeof(v89));
  *(float *)&v88[12] = v89[12];
  *(float *)&v88[13] = v89[13];
  *(float *)&v88[14] = v89[14];
  *(float *)v78 = v89[0];
  *(float *)&v78[1] = v89[4];
  *(float *)&v78[2] = v89[8];
  *(float *)v81 = v89[1];
  *(float *)&v81[1] = v89[5];
  *(float *)&v81[2] = v89[9];
  v3 = 0;
  v88[11] = 0;
  memset(&v88[6], 0, 16);
  memset(&v88[1], 0, 16);
  v88[15] = 1065353216;
  v88[10] = 1065353216;
  v88[5] = 1065353216;
  v88[0] = 1065353216;
  *(float *)v63 = v89[2];
  *(float *)&v63[1] = v89[6];
  *(float *)&v63[2] = v89[10];
  (*(void ( **)(float, _DWORD))(*(_DWORD *)LODWORD(xy) + 368))(_pal3_coerce_f32(LODWORD(xy)), 0);
  (*(void ( **)(float, int))(*(_DWORD *)LODWORD(xy) + 356))(_pal3_coerce_f32(LODWORD(xy)), 322);
  (*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(_pal3_coerce_f32(LODWORD(xy)), 7, 1);
  (*(void ( **)(float, int, _DWORD))(*(_DWORD *)LODWORD(xy) + 228))(_pal3_coerce_f32(LODWORD(xy)), 14, 0);
  (*(void ( **)(float, int, _DWORD))(*(_DWORD *)LODWORD(xy) + 228))(_pal3_coerce_f32(LODWORD(xy)), 137, 0);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 268))(_pal3_coerce_f32(LODWORD(xy)), 0, 1, 4);
  (*(void ( **)(float, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(xy) + 268))(_pal3_coerce_f32(LODWORD(xy)), 0, 2, 0);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 268))(_pal3_coerce_f32(LODWORD(xy)), 0, 3, 2);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 276))(_pal3_coerce_f32(LODWORD(xy)), 0, 6, 2);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 276))(_pal3_coerce_f32(LODWORD(xy)), 0, 5, 2);
  (*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(_pal3_coerce_f32(LODWORD(xy)), 27, 1);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 268))(_pal3_coerce_f32(LODWORD(xy)), 0, 4, 7);
  (*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(_pal3_coerce_f32(LODWORD(xy)), 19, 2);
  (*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(_pal3_coerce_f32(LODWORD(xy)), 20, 2);
  m_nTodo_03C = v1[1].m_nTodo_03C;
  v1[1814].m_nHeight = 0;
  v49 = 0;
  if ( m_nTodo_03C > 0 )
  {
    do
    {
      if ( *(&v1[740].m_nDefaultH + v3) )
      {
        v5 = *(&v1[186].m_nHalfWidth + 9238 * v3);
        v6 = *((_DWORD *)&v1[1814].m_nTodo_028 + *((_DWORD *)&v1[1].m_fOffsetY + 9238 * v3));
        v55 = (char *)this + 36952 * v3;
        v33 = *(_DWORD *)(v6 + 84);
        v51 = 1.0f / (float)*(int *)(v5 + 364);
        v7 = (double)*(int *)(v5 + 360);
        v8 = *(_DWORD *)LODWORD(xy);
        v48 = 1.0f / v7;
        (*(void ( **)(float, _DWORD, int))(v8 + 260))(_pal3_coerce_f32(LODWORD(xy)), 0, v33);
        m_nScaleX = v1[1813].m_nScaleX;
        v50 = 0;
        if ( m_nScaleX > 0 )
        {
          v10 = (float *)(&v1[2].m_nTodo_038 + 9238 * v3);
          do
          {
            if ( *((_DWORD *)v10 - 19) )
            {
              ++v1[1814].m_nHeight;
              v36 = *(v10 - 7);
              v37 = *(v10 - 6);
              v38 = *(v10 - 5);
              v44 = (float)*((int *)v10 - 15) * v51;
              v42 = (float)*((int *)v10 - 14) * v48;
              v34 = v10[2] * 0.01745329238474369f;
              sub_543C42((int)v88, (int)v63, v34);
              sub_5427A5(&v52, v78, v88);
              sub_5427A5(&v45, v81, v88);
              v35 = *(v10 - 4) * 0.5f * *(float *)(*((_DWORD *)v55 + 9306) + 356);
              v11 = -v52;
              v56 = v11;
              *(float *)&v58 = -v53;
              v60[2] = *(float *)&v58;
              v60[0] = -v54;
              v60[3] = v60[0];
              v86 = *(float *)&v58 - v46;
              v87 = v60[0] - v47[0];
              v64 = v86 * v35;
              v65 = v87 * v35;
              v79 = v64 + v37;
              v90[1] = v79;
              v80 = v65 + v38;
              v90[0] = (v11 - v45) * v35 + v36;
              v12 = *(v10 - 2);
              v90[2] = v80;
              if ( v12 < 1.0 )
              {
                if ( *(v10 - 2) > 0.0 )
                  v39 = (__int64)(*(v10 - 2) * 255.0 + 0.5);
                else
                  v39 = 0;
              }
              else
              {
                v39 = 255;
              }
              if ( *(v10 - 1) < 1.0 )
              {
                if ( *(v10 - 1) > 0.0 )
                  v13 = (__int64)(*(v10 - 1) * 255.0 + 0.5);
                else
                  v13 = 0;
              }
              else
              {
                v13 = 255;
              }
              if ( *v10 < 1.0f )
              {
                if ( *v10 > 0.0f )
                  v14 = (__int64)(*v10 * 255.0 + 0.5);
                else
                  v14 = 0;
              }
              else
              {
                v14 = 255;
              }
              if ( v10[1] < 1.0f )
              {
                if ( v10[1] > 0.0f )
                  v15 = (__int64)(v10[1] * 255.0 + 0.5);
                else
                  LODWORD(v15) = 0;
              }
              else
              {
                LODWORD(v15) = 255;
              }
              v68 = v53 - v46;
              v90[4] = v44;
              v69 = v54 - v47[0];
              v84 = v68 * v35;
              LODWORD(v90[3]) = v14 | ((v13 | ((v39 | ((_DWORD)v15 << 8)) << 8)) << 8);
              v90[5] = v42;
              v85 = v69 * v35;
              v72 = v84 + v37;
              v90[7] = v72;
              v73 = v85 + v38;
              v90[6] = (v52 - v45) * v35 + v36;
              v16 = *(v10 - 2);
              v90[8] = v73;
              if ( v16 < 1.0 )
              {
                if ( *(v10 - 2) > 0.0 )
                  v40 = (__int64)(*(v10 - 2) * 255.0 + 0.5);
                else
                  v40 = 0;
              }
              else
              {
                v40 = 255;
              }
              if ( *(v10 - 1) < 1.0 )
              {
                if ( *(v10 - 1) > 0.0 )
                  v17 = (__int64)(*(v10 - 1) * 255.0 + 0.5);
                else
                  v17 = 0;
              }
              else
              {
                v17 = 255;
              }
              if ( *v10 < 1.0f )
              {
                if ( *v10 > 0.0f )
                  v18 = (__int64)(*v10 * 255.0 + 0.5);
                else
                  v18 = 0;
              }
              else
              {
                v18 = 255;
              }
              if ( v10[1] < 1.0f )
              {
                if ( v10[1] > 0.0f )
                  v19 = (__int64)(v10[1] * 255.0 + 0.5);
                else
                  LODWORD(v19) = 0;
              }
              else
              {
                LODWORD(v19) = 255;
              }
              v20 = v44 + v51;
              v90[10] = v20;
              v82 = v46 + v53;
              v83 = v47[0] + v54;
              LODWORD(v90[9]) = v18 | ((v17 | ((v40 | ((_DWORD)v19 << 8)) << 8)) << 8);
              v90[11] = v42;
              v76 = v82 * v35;
              v77 = v83 * v35;
              v61 = v76 + v37;
              v90[13] = v61;
              v62 = v77 + v38;
              v90[12] = (v45 + v52) * v35 + v36;
              v21 = *(v10 - 2);
              v90[14] = v62;
              if ( v21 < 1.0 )
              {
                if ( *(v10 - 2) > 0.0 )
                  v41 = (__int64)(*(v10 - 2) * 255.0 + 0.5);
                else
                  v41 = 0;
              }
              else
              {
                v41 = 255;
              }
              if ( *(v10 - 1) < 1.0 )
              {
                if ( *(v10 - 1) > 0.0 )
                  v22 = (__int64)(*(v10 - 1) * 255.0 + 0.5);
                else
                  v22 = 0;
              }
              else
              {
                v22 = 255;
              }
              if ( *v10 < 1.0f )
              {
                if ( *v10 > 0.0f )
                  v23 = (__int64)(*v10 * 255.0 + 0.5);
                else
                  v23 = 0;
              }
              else
              {
                v23 = 255;
              }
              if ( v10[1] < 1.0f )
              {
                if ( v10[1] > 0.0f )
                  v24 = (__int64)(v10[1] * 255.0 + 0.5);
                else
                  LODWORD(v24) = 0;
              }
              else
              {
                LODWORD(v24) = 255;
              }
              v90[16] = v20;
              v25 = v42 + v48;
              v90[17] = v25;
              *(float *)&v63[5] = v60[0];
              LODWORD(v90[15]) = v23 | ((v22 | ((v41 | ((_DWORD)v24 << 8)) << 8)) << 8);
              v63[4] = v58;
              v66 = *(float *)&v58 + v46;
              v67 = v60[0] + v47[0];
              v70 = v66 * v35;
              v71 = v67 * v35;
              v74 = v70 + v37;
              v90[19] = v74;
              v75 = v71 + v38;
              v90[18] = (v56 + v45) * v35 + v36;
              v26 = *(v10 - 2);
              v90[20] = v75;
              if ( v26 < 1.0 )
              {
                if ( *(v10 - 2) > 0.0 )
                  v43 = (__int64)(*(v10 - 2) * 255.0 + 0.5);
                else
                  v43 = 0;
              }
              else
              {
                v43 = 255;
              }
              if ( *(v10 - 1) < 1.0 )
              {
                if ( *(v10 - 1) > 0.0 )
                  v27 = (__int64)(*(v10 - 1) * 255.0 + 0.5);
                else
                  v27 = 0;
              }
              else
              {
                v27 = 255;
              }
              if ( *v10 < 1.0f )
              {
                if ( *v10 > 0.0f )
                  v28 = (__int64)(*v10 * 255.0 + 0.5);
                else
                  v28 = 0;
              }
              else
              {
                v28 = 255;
              }
              if ( v10[1] < 1.0f )
              {
                if ( v10[1] > 0.0f )
                  v29 = (__int64)(v10[1] * 255.0 + 0.5);
                else
                  LODWORD(v29) = 0;
              }
              else
              {
                LODWORD(v29) = 255;
              }
              v90[22] = v44;
              v90[23] = v25;
              LODWORD(v90[21]) = v28 | ((v27 | ((v43 | ((_DWORD)v29 << 8)) << 8)) << 8);
              (*(void ( **)(float, int, int, float *, int))(*(_DWORD *)LODWORD(xy) + 332))(
                _pal3_coerce_f32(LODWORD(xy)),
                6,
                2,
                v90,
                24);
              v3 = v49;
              v1 = (RenderTarget *)v57;
            }
            v30 = v1[1813].m_nScaleX;
            v10 += 23;
            ++v50;
          }
          while ( v50 < v30 );
        }
      }
      v31 = v1[1].m_nTodo_03C;
      v49 = ++v3;
    }
    while ( v3 < v31 );
  }
  (((gbMatrixStack *)v59))->gbMatrixStack::Pop();
  gfxMgr[1].AllLight[1].attenuation1 = 0.0;
  (((gbGfxManager_D3D *)gfxMgr))->gbGfxManager_D3D::SetTexture(0);
  (((gbRenderEffect *)gfxMgr->pEffectMgr->m_pDefEffect))->gbRenderEffect::Apply();
  return v1[1814].m_nHeight;
}

// 0x004BD6C0
char RenderTarget::LoadParticleTextures(const char *pszName)
{
  char *v3; // eax
  char Str[260]; // [esp+0xC] [ebp-0x208] BYREF
  char v5[260]; // [esp+0x110] [ebp-0x104] BYREF

  if ( !pszName )
    return 0;
  strcpy((char *)Str, pszName);
  v3 = strrchr(Str, 92);
  if ( !v3 )
    return 0;
  strcpy((char *)v5, v3 + 1);
  strcpy(v3, unk_C10D38);
  return ParticleEffect_LoadTextures((int)Str);
}

// 0x004BD870
void RenderTarget::GetManagedTexture(int nVal1)
{
  (((gbChain1DNode *)this))->gbChain1DNode::Process();
}

// 0x004BD880
gbParticleEffect * RenderTarget::CreateParticleEffect(int nVal)
{
  gbParticleEffect *v3; // eax
  gbParticleEffect *v4; // esi
  gbParticleEffect *v5; // ecx
  gbParticleEffect *result; // eax

  v3 = (gbParticleEffect *)operator new(0x160u);
  v4 = (gbParticleEffect *)v3;
  v5 = 0;
  if ( v3 )
  {
    v3->gbParticleEffect::gbParticleEffect();
    v5 = (gbParticleEffect *)v4;
  }
  this->m_nDefaultH = (int)v5;
  (((gbParticleEffect *)v5))->gbParticleEffect::LoadFromFile("effect\\gbParticle\\poisonfog.par");
  result = (gbParticleEffect *)this->m_nDefaultH;
  result->SpaceScale = 32.0f;
  return result;
}

// 0x004BD900
gbParticleGroup * RenderTarget::UpdateParticleEffect(int nVal)
{
  int m_szPath; // eax
  gbParticleGroup *result; // eax

  m_szPath = this->m_szPath;
  if ( !m_szPath )
    return (gbParticleGroup *)(*(int ( **)(int))(*(_DWORD *)this->m_nDefaultH + 20))(this->m_nDefaultH);
  result = (gbParticleGroup *)(m_szPath - 1);
  if ( !result )
  {
    (*(void ( **)(int))(*(_DWORD *)this->m_nDefaultH + 20))(this->m_nDefaultH);
    result = (((gbParticleEffect *)this->m_nDefaultH))->gbParticleEffect::GetParticleGroup(0);
    if ( result->nAlivePart <= 0 )
      this->m_szPath = -1;
  }
  return result;
}

// 0x004BD950
int RenderTarget::Stop(int nVal)
{
  if ( this->m_szPath == -1 )
    return 0;
  (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_nDefaultH + 16))(this->m_nDefaultH, 0);
  return 1;
}

// 0x004BD970
int RenderTarget::ReleaseDefault()
{
  int ( ***m_nDefaultH)(_DWORD, int); // ecx
  int result; // eax

  m_nDefaultH = (int ( ***)(_DWORD, int))this->m_nDefaultH;
  if ( m_nDefaultH )
  {
    result = (**m_nDefaultH)((_DWORD)((_DWORD)(m_nDefaultH)), (int)(1));
    this->m_nDefaultH = 0;
  }
  return result;
}

// 0x004BD990
void RenderTarget::SetPathMode(int nVal)
{
  gbPartEmitter *Emitter; // eax

  if ( nVal == 1 )
  {
    this->m_szPath = 1;
    Emitter = (((gbParticleEffect *)this->m_nDefaultH))->gbParticleEffect::GetEmitter(0);
    (((gbPartEmitter *)Emitter))->gbPartEmitter::SetLoopEmit(0);
  }
}

// 0x004BD9C0
int RenderTarget::SetDefaultParams(int nVal)
{
  int result; // eax

  (((gbMatrix4 *)nVal))->gbMatrix4::LoadIdentity();
  result = 1111490560;
  *(_DWORD *)(nVal + 52) = 1109393408;
  *(_DWORD *)(nVal + 72) = 1111490560;
  *(_DWORD *)(nVal + 68) = 1111490560;
  *(_DWORD *)(nVal + 64) = 1114636288;
  return result;
}

// 0x004BDAC0
RenderTarget::~RenderTarget()
{
  (((gbTexture_D3D *)&this->m_ScreenPlane))->gbTexture_D3D::~gbTexture_D3D();
  (((gbTexture_D3D *)&this->m_Texture))->gbTexture_D3D::~gbTexture_D3D();
}

// 0x004BDB60
void RenderTarget::Create()
{
  int v2; // [esp+0xC] [ebp-0x814] BYREF
  int v3; // [esp+0x14] [ebp-0x80C]
  char pExceptionObject[1024]; // [esp+0x20] [ebp-0x800] BYREF
  char ArgList; // [esp+0x420] [ebp-0x400] BYREF

  if ( !(*(int ( **)(gbGfxManager *, int *, int))(*(_DWORD *)*(void**)(gfxMgr) + 84))(gfxMgr, &v2, 1) )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException("Lock Back Buffer failed.", "D:\\Project\\PAL3\\effect\\RenderTarget.cpp", 39),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 88))(gfxMgr);
  ((void ( *)(gbTexture_D3D **, int, int, int))this->m_ScreenPlane->NameCrc32)(
    &this->m_ScreenPlane,
    g_DrvInfo.width,
    g_DrvInfo.height,
    v3);
  ((void ( *)(gbTexture_D3D **, int, int, int))this->m_Texture->NameCrc32)(&this->m_Texture, 512, 512, v3);
  this->m_iMode = 0;
  this->m_nState = 0;
}

// 0x004BDC10
void RenderTarget::OnDeviceLost(int nVal)
{
  int v2; // eax

  if ( this->m_nState != 1 )
  {
    v2 = nVal;
    if ( (nVal == 1 || nVal == 2) && !this->m_nDeviceLost )
      v2 = 0;
    this->m_iMode = v2;
  }
}

// 0x004BDC40
bool RenderTarget::OnResetDevice(int nVal)
{
  BOOL v3; // eax
  int m_iMode; // ecx
  int v5; // esi
  RenderTarget *v7; // [esp+0x28] [ebp-0x10] BYREF
  int v8; // [esp+0x34] [ebp-0x4]
if ( this->m_nState != 1 )
  {
    this->m_nState = 1;
    m_iMode = this->m_iMode;
    v5 = 0;
    if ( this->m_iMode )
    {
      if ( m_iMode <= 0 || m_iMode > 2 )
        return v5 != 0;
      v5 = (*(int ( **)(gbGfxManager *, gbTexture_D3D **))(*(_DWORD *)*(void**)(gfxMgr) + 92))(
             gfxMgr,
             &this->m_ScreenPlane);
    }
    else
    {
      v5 = (*(int ( **)(gbGfxManager *, gbTexture_D3D **))(*(_DWORD *)*(void**)(gfxMgr) + 92))(
             gfxMgr,
             &this->m_Texture);
      (((gbCamera *)&g_pCameraCtrl->m_fMinDist))->gbCamera::SetDimention(512, 384);
      (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetAsCurrent(3);
    }
    if ( v5 && (_BYTE)nVal )
    {
      (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                           + 172))(
        LODWORD(gfxMgr[1].InvViewMatrix.xy),
        0,
        0,
        3,
        -16777216,
        1065353216,
        0);
      (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 48))(gfxMgr);
      PushMatrixStacks(&v7);
      v8 = 0;
      crt_sub_00540070();
      (*(void ( **)(gbGfxManager *))(*(_DWORD *)*(void**)(gfxMgr) + 52))(gfxMgr);
      v8 = -1;
      PopMatrixStacks(&v7);
    }
    return v5 != 0;
  }
  return 0;
}

// 0x004BDD90
int RenderTarget::RenderToScreen()
{
  int result; // eax
  gbGfxManager *v3; // ebx
  int v4; // [esp+0x34] [ebp-0x48] BYREF
  int v5; // [esp+0x38] [ebp-0x44] BYREF
  _DWORD v6[4]; // [esp+0x3C] [ebp-0x40] BYREF
  _DWORD v7[4]; // [esp+0x4C] [ebp-0x30] BYREF
  _BYTE v8[24]; // [esp+0x5C] [ebp-0x20] BYREF
  int v9; // [esp+0x74] [ebp-0x8]
  int v10; // [esp+0x78] [ebp-0x4]

  (((gbCamera *)&g_pCameraCtrl->m_fMinDist))->gbCamera::SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetAsCurrent(3);
  (*(void ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)*(void**)(gfxMgr) + 92))(gfxMgr, 0);
  result = this->m_iMode - 2;
  if ( this->m_iMode == 2 )
  {
    result = this->m_nDeviceLost;
    v3 = gfxMgr;
    if ( result )
    {
      v5 = 0;
      result = (*(int ( **)(int, _DWORD, int *))(*(_DWORD *)result + 72))(result, 0, &v5);
      if ( v5 )
      {
        result = this->m_szPath;
        if ( result )
        {
          v4 = 0;
          result = (*(int ( **)(int, _DWORD, int *))(*(_DWORD *)result + 72))(result, 0, &v4);
          if ( v4 )
          {
            v6[1] = 0;
            v7[1] = 0;
            v6[0] = 0;
            v7[0] = 0;
            (*(void ( **)(int, _BYTE *))(*(_DWORD *)v5 + 48))(v5, (_BYTE *)(v8));
            v7[2] = v9;
            v7[3] = v10;
            (*(void ( **)(int, _BYTE *))(*(_DWORD *)v4 + 48))(v4, (_BYTE *)(v8));
            v6[2] = v9;
            v6[3] = v10;
            result = (*(int ( **)(_DWORD, int, _DWORD *, int, _DWORD *, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy)
                                                                                        + 136))(
                       LODWORD(v3[1].InvViewMatrix.xy),
                       v5,
                       (_DWORD *)(v7),
                       v4,
                       (_DWORD *)(v6),
                       0);
          }
        }
      }
    }
  }
  this->m_nState = 0;
  return result;
}

// 0x004BDEB0
gbTexture * RenderTarget::GetActiveTexture()
{
  if ( this->m_iMode )
  {
    if ( this->m_iMode == 1 )
      return (gbTexture *)&this->m_ScreenPlane;
    if ( this->m_iMode != 2 )
      return 0;
  }
  return (gbTexture *)&this->m_Texture;
}

// 0x004BDF10
int * RenderTarget::Destroy()
{
  int *result; // eax

  result = (int *)&this->m_iMode;
  this->m_Texture = ((gbTexture_D3D *)0);
  this->m_nRenderX = 1;
  this->m_nHalfW = 0;
  this->m_nRenderY = 0;
  this->m_nHalfH = 0;
  return result;
}

// 0x004BE8D0
int RenderTarget::ResetHorizontal()
{
  this->RenderTarget::Destroy();
  this->m_nRenderY = 1075838976;
  this->m_nHalfWidth = 1;
  return (int)this;
}

// 0x004BEA60
RenderTarget * RenderTarget::ResetVertical()
{
  this->RenderTarget::Destroy();
  this->m_nRenderY = 1075838976;
  this->m_nHalfH = 1;
  return this;
}

// 0x004BEBB0
RenderTarget * RenderTarget::ResetVertical2()
{
  this->RenderTarget::Destroy();
  this->m_nRenderY = 1075838976;
  this->m_nHalfH = 1;
  return this;
}

// 0x004BED00
RenderTarget * RenderTarget::ResetBase()
{
  this->RenderTarget::Destroy();
  this->m_nRenderY = 1075838976;
  return this;
}
