#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UICursor.h"
#include "Scene/CameraCtrl.h"
#include "Misc/Iostream_init.h"
#include "MiniGame/MiniGame3.h"
#include "Script/PalScript.h"
#include "Misc/PalScriptIdleObj.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/SceneObjParam.h"
#include "Misc/UIAnimateCtrlEX.h"
#include "UI/UIListBox.h"
#include "Misc/UISceneFrm.h"
#include "Misc/UISceneMap.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x00535120
void UICursor::Update(double fDelta)
{
  UIAnimateCtrlEX *v3; // eax
  MiniGame3 *inited; // eax
  PalScriptIdleObj *v5; // eax
  UISceneFrm *v6; // eax
  UIListBox *v7; // eax
  gbTexture *v8; // eax
  int v9; // ecx
  Iostream_init *v10; // eax
  Iostream_init *v11; // eax
  SceneObjParam *v12; // eax
  CameraCtrl *updated; // eax
  SceneObj *v14; // eax
  gbTexture *UI; // eax
  void *m_pData; // eax
  void *v17; // edi
  unsigned int v18; // edx
  gbTexture *v19; // [esp-0x4] [ebp-0x20]
  int v20; // [esp+0x0] [ebp-0x1C]

  v3 = (UIAnimateCtrlEX *)operator new(0xE4u);
  if ( v3 )
    inited = (MiniGame3 *)(((UIAnimateCtrlEX *)v3))->UIAnimateCtrlEX::InitMatrix();
  else
    inited = 0;
  this->m_dwID[0] = (unsigned int)inited;
  (((MiniGame3 *)inited))->MiniGame3::LoadModels(pszModel1, 0, 0);
  v5 = (PalScriptIdleObj *)operator new(0xC94u);
  if ( v5 )
    v6 = (((PalScriptIdleObj *)v5))->PalScriptIdleObj::ResetTimers();
  else
    v6 = 0;
  this->m_dwID[1] = (unsigned int)v6;
  LoadOverlayTexture(v6);
  (((UISceneMap *)this->m_dwID[1]))->UISceneMap::SetColorIfValid(this->m_dwID[0]);
  v7 = (UIListBox *)operator new(0x90u);
  if ( v7 )
    v8 = (gbTexture *)(((UIListBox *)v7))->UIListBox::ResetRect();
  else
    v8 = 0;
  v9 = this->m_dwID[1];
  this->m_tex[0] = v8;
  (((RoleSystem *)v8))->RoleSystem::AdjustHeight(v9);
  v10 = (Iostream_init *)operator new(8u);
  if ( v10 )
    v11 = (Iostream_init *)v10->Iostream_init::Iostream_init();
  else
    v11 = 0;
  v19 = (gbTexture *)this->m_tex[0];
  this->m_dwID[2] = (unsigned int)v11;
  (((CameraCtrl *)v11))->CameraCtrl::SetFOVIfValid((int)v19);
  v12 = (SceneObjParam *)operator new(0x2E8u);
  if ( v12 )
    updated = (CameraCtrl *)(((SceneObjParam *)v12))->SceneObjParam::UpdateCameraAndRole(gfxMgr);
  else
    updated = 0;
  this->m_active = ((CameraCtrl *)(updated));
  (((CameraCtrl *)updated))->CameraCtrl::InitDefaultView();
  v14 = (SceneObj *)operator new(0xDA8u);
  if ( v14 )
    UI = (gbTexture *)(((SceneObj *)v14))->SceneObj::CreateUI();
  else
    UI = 0;
  this->m_tex[1] = UI;
  Actor_ProcessActorFrame(v20);
  UISceneMap_SetFieldIfValid((int)this->m_tex[1]);
  m_pData = (void *)this->m_pData;
  *(_DWORD *)(&this->m_bSoftMode + 11) = 36;
  if ( m_pData )
  {
    operator delete(m_pData);
    this->m_pData = 0;
  }
  v17 = (void *)operator new(4 * *(_DWORD *)(&this->m_bSoftMode + 11));
  v18 = 4 * *(_DWORD *)(&this->m_bSoftMode + 11);
  this->m_pData = (unsigned int)v17;
  memset(v17, 0, v18);
  *(&this->m_pData + 2) = 0;
  *((_BYTE *)&this->m_pData + 16) = 1;
  *((_BYTE *)&this->m_pData + 17) = 0;
  *((_BYTE *)&this->m_pData + 18) = 0;
  (((UICursor *)0))->UICursor::_todo_541CC0();
  *(&this->m_bSoftMode + 9) = 1;
}

// 0x00541CC0
void UICursor::_todo_541CC0()
{
  gbUpdateCurTime();
  dbl_1895070 = g_CurrentTime;
}
