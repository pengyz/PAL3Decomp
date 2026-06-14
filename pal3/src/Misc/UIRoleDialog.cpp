#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIRoleDialog.h"

// Unnamed globals (extern)
extern void * off_5CC578;

// 0x004A1410
void UIRoleDialog::_UIRoleDialog()
{

  ((UICaption *)((char *)this + 976))->Destroy2();
  ((UICaption *)&this->m_static.m_childs.capacity)->Destroy2();
  ((UIFrameWnd *)&this->m_face.m_rect.top)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_ani.m_pfather)->UIFrameWnd::_UIFrameWnd();
  ((UITextArea *)&this->m_bk.m_pfather)->Destroy();
  g_nUILayoutFlags = 0;
// [VFTABLE] ((UIWnd *)&this->__vftable)->Destroy();
}

// 0x004A14C0
// attributes: thunk
void UIRoleDialog::HideAll()
{
// [VFTABLE] ((UIWnd *)&this->__vftable)->HideAll();
}

// 0x004A1A80
void * UIRoleDialog::RemoveChild(void *pChild, char bDelete)
{
  void *result; // eax

  ((void ( *)(UIWnd **))this->m_bk.m_pfather->m_fontcolor.Color)(&this->m_bk.m_pfather);
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  return result;
}

// 0x004A1AA0
BOOL UIRoleDialog::ProcessFrame(int nVal, int nVal2)
{
  DWORD TickCount; // eax
  DWORD v6; // eax
  unsigned int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax

  if ( !*((_BYTE *)this + 1340) )
    return 0;
  if ( !nVal2 )
    return ((UIFrameWnd *)this)->Update_bbc0(nVal, 0);
  if ( !*((_BYTE *)this + 1364) && this->m_bmodal )
  {
    if ( !*((_BYTE *)this + 1360) )
    {
      TickCount = GetTickCount();
      *((_DWORD *)this + 338) = TickCount;
      *((_DWORD *)this + 339) = TickCount;
      *((_BYTE *)this + 1360) = 1;
    }
    v6 = GetTickCount();
    v7 = v6 - *((_DWORD *)this + 339);
    *((_DWORD *)this + 338) = v6;
    if ( v7 > 0x258 )
    {
      *((_DWORD *)this + 339) = v6;
      *((_BYTE *)this + 1360) = 0;
      *((_BYTE *)this + 1364) = 1;
    }
    return ((UIFrameWnd *)this)->Update_bbc0(nVal, nVal2);
  }
  v8 = *((_DWORD *)this + 331);
  if ( !v8 )
  {
// [VFTABLE] ((void ( *)(UIWnd **, int))this->m_ani.m_pfather->__vftable)(&this->m_ani.m_pfather, 1);
    (*(void ( **)(int *, int))this->m_static.m_childs.capacity)(
      &this->m_static.m_childs.capacity,
      1);
    *((_BYTE *)this + 732) = 1;
    if ( g_Input.KeyInfo[7].PressTime != 1 )
      goto LABEL_22;
    goto LABEL_21;
  }
  v9 = v8 - 2;
  if ( v9 )
  {
    if ( v9 == 1 && this->m_ani.m_id == (void *)2 )
      (*(void ( **)(LONG *, int))this->m_face.m_rect.top)(&this->m_face.m_rect.top, 1);
    goto LABEL_22;
  }
// [VFTABLE] ((void ( *)(UIWnd **, int))this->m_ani.m_pfather->__vftable)(&this->m_ani.m_pfather, 1);
  (*(void ( **)(int *, int))this->m_static.m_childs.capacity)(&this->m_static.m_childs.capacity, 1);
  (**((void ( ***)(char *, int))this + 244))((char *)this + 976, 1);
  *((_BYTE *)this + 732) = 1;
  *((_BYTE *)this + 1076) = 1;
  if ( g_Input.KeyInfo[7].PressTime == 1 )
  {
LABEL_21:
    this->OnMessage(1001, 655362, 0);
    goto LABEL_22;
  }
  if ( g_Input.KeyInfo[8].PressTime == 1 )
    this->OnMessage(1001, 655363, 0);
LABEL_22:
  v10 = *((_DWORD *)this + 331);
  if ( v10 < 0 )
    return ((UIFrameWnd *)this)->Update_bbc0(nVal, nVal2);
  if ( v10 <= 2 )
  {
    if ( !this->m_bmodal )
      return ((UIFrameWnd *)this)->Update_bbc0(nVal, nVal2);
  }
  else
  {
    if ( v10 != 3 || !this->m_bmodal )
      return ((UIFrameWnd *)this)->Update_bbc0(nVal, nVal2);
    if ( g_Input.KeyInfo[0].PressTime == 1
      || g_Input.KeyInfo[7].PressTime == 1
      || g_Input.KeyInfo[8].PressTime == 1
      || g_Input.KeyInfo[6].PressTime == 1
      || g_Input.KeyInfo[2].PressTime == 1
      || g_Input.KeyInfo[3].PressTime == 1
      || g_Input.KeyInfo[4].PressTime == 1
      || g_Input.KeyInfo[5].PressTime == 1
      || g_Input.KeyInfo[11].PressTime == 1 )
    {
      *((_DWORD *)this + 332) = 2;
      ((MUIDialog *)this)->InvokeCallback();
      return ((UIFrameWnd *)this)->Update_bbc0(nVal, nVal2);
    }
  }
  ((UIListBox *)this)->Update(nVal, 1);
  return 1;
}

// 0x004A1D10
int UIRoleDialog::OnCommand(int nVal, int nVal2, int nVal3)
{
  char v6; // cl
  CScreenMode *Instance; // eax
  char v8; // cl
  const void *v9; // [esp-0x8] [ebp-0xC]

  if ( nVal != 1001 )
    return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
  if ( nVal2 == 655362 )
  {
    if ( *((_BYTE *)this + 1364) )
    {
      v8 = *((_BYTE *)this + 1365);
      *((_DWORD *)this + 332) = 0;
      if ( !v8 )
        goto LABEL_9;
      v9 = off_5CC578;
      goto LABEL_8;
    }
    *((_BYTE *)this + 732) = 0;
    return 1;
  }
  if ( nVal2 != 655363 )
    return 1;
  if ( *((_BYTE *)this + 1364) )
  {
    v6 = *((_BYTE *)this + 1365);
    *((_DWORD *)this + 332) = 1;
    if ( !v6 )
    {
LABEL_9:
      ((MUIDialog *)this)->InvokeCallback();
      return 1;
    }
    v9 = off_5CC578;
LABEL_8:
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v9, 1);
    goto LABEL_9;
  }
  *((_BYTE *)this + 1076) = 0;
  return 1;
}

// 0x004BEF50
void UIRoleDialog::_UIWnd()
{
  ((ScreenEffectMgr *)this)->CleanupTextures();
  ((RenderTarget *)((char *)this + 1108))->UpdateTimeStep();
  ((gbChain1DNode *)this)->Process();
}

// 0x004BF1C0
void UIRoleDialog::Create(int nVal)
{
  this->Destroy(0);
}

// 0x004BF1D0
int UIRoleDialog::Destroy(int nVal)
{
  UIRoleDialog *v2; // edi
  gbRenderInfoObj *v3; // esi
  gbRenderEffect *m_bmodal; // ecx
  gbMatrix4 *Top; // eax
v3 = ((gbSceneGraph *)gfxMgr->pSceneGraph)->NewOneRenderObj((gbVisNode *)this);
  v2 = (UIRoleDialog *)((char *)v2 + 100);
  v3->Flags = 0;
  v3->Param = 0;
  m_bmodal = (gbRenderEffect *)this->m_bmodal;
  v3->pTexArray = (gbTextureArray *)v2;
  v3->pEffect = m_bmodal;
  Top = ((gbMatrixStack *)gfxMgr->pMatrixStack[1])->GetTop();
  ((gbMatrix4 *)Top)->Transform();
  v3->Priority = 1;
  v3->Z = 0.0;
  return 0;
}

// 0x004BF260
void UIRoleDialog::Render(int nVal)
{
  gbMatrixStack *v2; // edi
  gbDynVertBuf *DynVertBuf; // ebp
  double v5; // st7
  double v6; // st7
  float *v7; // ebx
  double v8; // st7
  double v9; // st7
  __int64 v10; // rax
  gbRenderEffect *v11; // ecx
  bool v12; // cc
  float v13; // [esp+0x64] [ebp-0x6C]
  gbRenderEffect *v14; // [esp+0x64] [ebp-0x6C]
  float v15; // [esp+0x64] [ebp-0x6C]
  float v16; // [esp+0x64] [ebp-0x6C]
  int v17; // [esp+0x7C] [ebp-0x54]
  struct gbVec3D v18; // [esp+0x80] [ebp-0x50] BYREF
  struct gbTextureArray v19; // [esp+0x8C] [ebp-0x44] BYREF
  UIRoleDialog *nVala; // [esp+D4h] [ebp+0x4]

  v2 = gfxMgr->pMatrixStack[1];
  ((gbMatrixStack *)v2)->Push();
  ((gbMatrixStack *)v2)->LoadMatrix((gbMatrix4 *)(nVal + 32));
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
  ((gbRenderEffect *)this->m_bk.m_texs.m_ptex[1])->Begin();
  ((gbRenderEffect *)this->m_bk.m_texs.m_ptex[1])->Pass(0);
  ((gbMatrixStack *)v2)->Push();
  v5 = *(float *)&this->m_bk.m_id * -0.2;
  v18.x = 0.0;
  v18.y = 1.0;
  v13 = v5;
  v18.z = 0.0;
  ((gbMatrixStack *)v2)->Rotate(v13, v18);
  v19.pTexPt[0] = (gbTexture *)this->m_bk.m_rect.left;
  v14 = (gbRenderEffect *)this->m_bk.m_texs.m_ptex[1];
  v19.nTex = 1;
  ((gbDynVertBuf *)DynVertBuf)->RenderGeomQuad((gbGeomQuad *)((char *)this + 992), 1, v14, &v19);
  ((gbDynVertBuf *)DynVertBuf)->RenderGeomQuad((gbGeomQuad *)&this->m_bk.m_texs.m_ptex[3], 6, (gbRenderEffect *)this->m_bk.m_texs.m_ptex[1], (gbTextureArray *)&this->m_bk.m_rect.top);
  ((gbMatrixStack *)v2)->Pop();
  ((gbMatrixStack *)v2)->Push();
  v6 = *(float *)&this->m_bk.m_id * -2.0;
  v18.x = 0.0;
  v18.y = 1.0;
  v15 = v6;
  v18.z = 0.0;
  ((gbMatrixStack *)v2)->Rotate(v15, v18);
  ((gbDynVertBuf *)DynVertBuf)->RenderGeomQuad((gbGeomQuad *)&this->m_face.m_nTextW, 6, (gbRenderEffect *)this->m_bk.m_texs.m_ptex[1], (gbTextureArray *)&this->m_bk.m_rect.top);
  ((gbMatrixStack *)v2)->Pop();
  if ( this->m_bk.m_wndcolor.Color == 1 )
  {
    ((gbMatrixStack *)v2)->Scale(0.60000002,   1.0,   0.60000002);
    v17 = 0;
    v7 = (float *)((char *)this + 1064);
    nVala = (UIRoleDialog *)((char *)this + 1092);
    do
    {
      if ( *(v7 - 1) <= 0.0 )
        break;
// [VFTABLE] if ( !nVala->__vftable )
      {
        ((gbMatrixStack *)v2)->Push();
        v8 = *(float *)&this->m_bk.m_id * -0.5;
        v18.x = 0.0;
        v9 = v8 - *(v7 - 1);
        v18.y = 1.0;
        v18.z = 0.0;
        v16 = v9;
        ((gbMatrixStack *)v2)->Rotate(v16, v18);
        ((gbMatrixStack *)v2)->Translate(0.0,   *v7,   0.0);
        v10 = (__int64)(255.0 - *v7 * 0.016666668 * 255.0);
        v11 = (gbRenderEffect *)this->m_bk.m_texs.m_ptex[1];
        HIDWORD(v10) = this->m_bk.m_rect.left;
        *((_BYTE *)this + 1056) = v10;
        *((_BYTE *)this + 1057) = v10;
        *((_BYTE *)this + 1058) = v10;
        v19.nTex = 1;
        v19.pTexPt[0] = (gbTexture *)HIDWORD(v10);
        ((gbDynVertBuf *)DynVertBuf)->RenderGeomQuad((gbGeomQuad *)((char *)this + 992), 1, v11, &v19);
        ((gbMatrixStack *)v2)->Pop();
      }
      v7 += 2;
      v12 = ++v17 < 4;
      nVala = (UIRoleDialog *)((char *)nVala + 4);
    }
    while ( v12 );
    *((_DWORD *)this + 264) = -1;
  }
  ((gbRenderEffect *)this->m_bk.m_texs.m_ptex[1])->End();
  ((gbMatrixStack *)v2)->Pop();
}
