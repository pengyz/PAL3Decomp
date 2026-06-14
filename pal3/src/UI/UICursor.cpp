#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UICursor.h"

int crt_sub_00541210(void); // from annotations

// 0x00535120
void UICursor::Update(double fDelta)
{
  UIAnimateCtrlEX *v3; // eax
  MiniGame3 *inited; // eax
  PalScriptIdleObj *v5; // eax
  UISceneFrm *v6; // eax
  UIListBox *v7; // eax
  int *v8; // eax
  int v9; // ecx
  Iostream_init *v10; // eax
  Iostream_init *v11; // eax
  SceneObjParam *v12; // eax
  CameraCtrl *updated; // eax
  SceneObj *v14; // eax
  gbTexture *UI; // eax
  void *v16; // eax
  void *v17; // edi
  unsigned int v18; // edx
  double v19; // [esp-0x4] [ebp-0x20]
  gbTexture *v20; // [esp-0x4] [ebp-0x20]
  int v21; // [esp+0x4] [ebp-0x18]

  v3 = (UIAnimateCtrlEX *)operator new(0xE4u);
  if ( v3 )
    inited = (MiniGame3 *)((UIAnimateCtrlEX *)v3)->InitMatrix();
  else
    inited = 0;
  this->m_dwID[0] = (unsigned int)inited;
  ((MiniGame3 *)inited)->LoadModels(pszModel1, 0, 0);
  v5 = (PalScriptIdleObj *)operator new(0xC94u);
  if ( v5 )
    v6 = ((PalScriptIdleObj *)v5)->ResetTimers();
  else
    v6 = 0;
  this->m_dwID[1] = (unsigned int)v6;
  LODWORD(v19) = g_nMiniGameParam;
  ((UISceneMap *)v6)->LoadOverlayTexture(v19, v21);
  ((UISceneMap *)this->m_dwID[1])->SetColorIfValid(this->m_dwID[0]);
  v7 = (UIListBox *)operator new(0x90u);
  if ( v7 )
    v8 = ((UIListBox *)v7)->ResetRect();
  else
    v8 = 0;
  v9 = this->m_dwID[1];
  this->m_tex[0] = (gbTexture *)v8;
  ((RoleSystem *)v8)->AdjustHeight(v9);
  v10 = (Iostream_init *)operator new(8u);
  if ( v10 )
    // [AUTO-COMMENTED] v11 = ((Iostream_init *)v10)->Iostream_init();
  else
    v11 = 0;
  v20 = this->m_tex[0];
  this->m_dwID[2] = (unsigned int)v11;
  ((CameraCtrl *)v11)->SetFOVIfValid((int)v20);
  v12 = (SceneObjParam *)operator new(0x2E8u);
  if ( v12 )
    updated = (CameraCtrl *)((SceneObjParam *)v12)->UpdateCameraAndRole(gfxMgr);
  else
    updated = 0;
  this->m_active = updated;
  ((CameraCtrl *)updated)->InitDefaultView();
  v14 = (SceneObj *)operator new(0xDA8u);
  if ( v14 )
    UI = (gbTexture *)((SceneObj *)v14)->CreateUI();
  else
    UI = 0;
  this->m_tex[1] = UI;
  ((Actor *)UI)->ProcessActorFrame();
  ((UISceneMap *)this->m_dwID[0])->SetFieldIfValid((int)this->m_tex[1]);
  v16 = (void *)*((_DWORD *)this + 11);
  *((_DWORD *)this + 10) = 36;
  if ( v16 )
  {
    operator delete(v16);
    *((_DWORD *)this + 11) = 0;
  }
  v17 = operator new(4 * *((_DWORD *)this + 10));
  v18 = 4 * *((_DWORD *)this + 10);
  *((_DWORD *)this + 11) = v17;
  memset(v17, 0, v18);
  *((_DWORD *)this + 13) = 0;
  *((_BYTE *)this + 60) = 1;
  *((_BYTE *)this + 61) = 0;
  *((_BYTE *)this + 62) = 0;
  UICursor::IRender();
  *((_BYTE *)this + 38) = 1;
}

// 0x00541160
int UICursor::UIRenderPar(int nX, int nY, int nW, int nH, gbColorQuad *pColor, gbTextureArray *pTex, _PlugInfo *pInfo)
{
  gbPrintFont *v7; // edi
  int nHa; // [esp+0x20] [ebp+0x10]

  v7 = gfxMgr->pFontMgr->pAllFont[nH];
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(nHa) = *(_BYTE *)nW;
    BYTE1(nHa) = *(_BYTE *)(nW + 1);
    LOBYTE(nHa) = *(_BYTE *)(nW + 2);
  }
  else
  {
    *(_WORD *)((char *)&nHa + 1) = *(_WORD *)(nW + 1);
    LOBYTE(nHa) = *(_BYTE *)nW;
  }
  HIBYTE(nHa) = *(_BYTE *)(nW + 3);
  v7->curColor.Color = nHa;
  return crt_sub_00541210();
}

// 0x00541CC0
void UICursor::IRender()
{
  gbUpdateCurTime();
  dbl_1895070 = g_CurrentTime;
}
