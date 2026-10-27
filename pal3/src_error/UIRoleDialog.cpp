#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIRoleDialog.h"
#include "Render/CScreenMode.h"
#include "GameBase/GRPinput.h"
#include "Misc/MUIDialog.h"
#include "Misc/NameSys.h"
#include "Scene/SceneObj.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "Misc/UITextArea.h"
#include "Misc/UITitle.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x004A12F0
UIRoleDialog::UIRoleDialog()
{
  ((UIFrameWnd *)this)->UIFrameWnd::UIFrameWnd();
  (((UITextArea *)&this->m_static))->UITextArea::InitAfterClear();
  (((UIFrameContainer *)this->_todo_130))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)this->_todo_1c8))->UIFrameContainer::ResetContainerState();
  *(_DWORD *)&this->_todo_1c8[152] = 90;
  *(_DWORD *)&this->_todo_1c8[156] = 26;
  NameSys::GetSys();
  NameSys::GetSys();
  *(_DWORD *)&this->byMagicUseTime[2][4] = 0;
  *(_DWORD *)&this->byMagicUseTime[4][0] = -1;
  *(_DWORD *)&this->byMagicUseTime[4][4] = 208;
  *(_DWORD *)&this->byMagicUseTime[5][2] = 103;
  this->byMagicUseTime[6][0] = 0;
  this->byMagicUseTime[6][1] = 0;
  this->_todo_550 = 0;
  this->_todo_54c = 0;
  this->_todo_548 = 0;
  this->m_bmodal = 0;
}

// 0x004A1410
UIRoleDialog::~UIRoleDialog()
{
  (((UITitle *)this))->UITitle::HideAll() /* [ROWTABLE] */;
  (((UICaption *)this->_todo_3d0))->UICaption::Destroy2();
  (((UICaption *)this->_todo_278))->UICaption::Destroy2();
  (((UIFrameContainer *)this->_todo_1c8))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)this->_todo_130))->UIFrameContainer::~UIFrameContainer();
  UITextArea_Destroy();
  g_nUILayoutFlags = 0;
  (((UIFrameWnd *)this))->UIFrameWnd::UIFrameWnd();
}

// 0x004A1A80
void * UIRoleDialog::RemoveChild(void *pChild, char bDelete)
{
  void *result; // eax

  (*(void ( **)(UITextArea *))(*(_DWORD *)((UIWnd *)&this->m_static) + 4))(&this->m_static);
  (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
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

  if ( !this->byMagicUseTime[6][0] )
    return 0;
  if ( !nVal2 )
    return (((UIFrameWnd *)this))->UIFrameWnd::Update_bbc0(nVal, 0) /* [ROWTABLE] */;
  if ( !this->_gap_551[3] && this->m_bmodal )
  {
    if ( !this->_todo_550 )
    {
      TickCount = GetTickCount();
      this->_todo_548 = TickCount;
      this->_todo_54c = TickCount;
      this->_todo_550 = 1;
    }
    v6 = GetTickCount();
    v7 = v6 - this->_todo_54c;
    this->_todo_548 = v6;
    if ( v7 > 0x258 )
    {
      this->_todo_54c = v6;
      this->_todo_550 = 0;
      this->_gap_551[3] = 1;
    }
    return (((UIFrameWnd *)this))->UIFrameWnd::Update_bbc0(nVal, nVal2) /* [ROWTABLE] */;
  }
  v8 = *(_DWORD *)&this->byMagicUseTime[3][2];
  if ( !v8 )
  {
    (**(void ( ***)(char *, int))this->_todo_130)((char *)(this->_todo_130), (int)(1));
    (**(void ( ***)(char *, int))this->_todo_278)((char *)(this->_todo_278), (int)(1));
    this->_todo_278[100] = 1;
    if ( g_Input.KeyInfo[7].PressTime != 1 )
      goto LABEL_22;
    goto LABEL_21;
  }
  v9 = v8 - 2;
  if ( v9 )
  {
    if ( v9 == 1 && this->m_static.m_nTodo_AC == 2 )
      (**(void ( ***)(char *, int))this->_todo_1c8)((char *)(this->_todo_1c8), (int)(1));
    goto LABEL_22;
  }
  (**(void ( ***)(char *, int))this->_todo_130)((char *)(this->_todo_130), (int)(1));
  (**(void ( ***)(char *, int))this->_todo_278)((char *)(this->_todo_278), (int)(1));
  (**(void ( ***)(char *, int))this->_todo_3d0)((char *)(this->_todo_3d0), (int)(1));
  this->_todo_278[100] = 1;
  this->_todo_3d0[100] = 1;
  if ( g_Input.KeyInfo[7].PressTime == 1 )
  {
LABEL_21:
    (*(void ( **)(UIRoleDialog *, int, int, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(this, 1001, 655362, 0);
    goto LABEL_22;
  }
  if ( g_Input.KeyInfo[8].PressTime == 1 )
    (*(void ( **)(UIRoleDialog *, int, int, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(this, 1001, 655363, 0);
LABEL_22:
  v10 = *(_DWORD *)&this->byMagicUseTime[3][2];
  if ( v10 < 0 )
    return (((UIFrameWnd *)this))->UIFrameWnd::Update_bbc0(nVal, nVal2) /* [ROWTABLE] */;
  if ( v10 <= 2 )
  {
    if ( !this->m_bmodal )
      return (((UIFrameWnd *)this))->UIFrameWnd::Update_bbc0(nVal, nVal2) /* [ROWTABLE] */;
  }
  else
  {
    if ( v10 != 3 || !this->m_bmodal )
      return (((UIFrameWnd *)this))->UIFrameWnd::Update_bbc0(nVal, nVal2) /* [ROWTABLE] */;
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
      *(_DWORD *)&this->byMagicUseTime[4][0] = 2;
      (((MUIDialog *)this))->MUIDialog::InvokeCallback();
      return (((UIFrameWnd *)this))->UIFrameWnd::Update_bbc0(nVal, nVal2) /* [ROWTABLE] */;
    }
  }
  (((SceneObj *)this))->SceneObj::Update(nVal, 1) /* [ROWTABLE] */;
  return 1;
}

// 0x004A1D10
int UIRoleDialog::OnCommand(int nVal, int nVal2, int nVal3)
{
  char v6; // cl
  CScreenMode *Instance; // eax
  char todo_555; // cl
  const void *v9; // [esp-0x8] [ebp-0xC]

  if ( nVal != 1001 )
    return this->UIWnd::OnMessage(nVal, nVal2, nVal3);
  if ( nVal2 == 655362 )
  {
    if ( this->_gap_551[3] )
    {
      todo_555 = this->_todo_555;
      *(_DWORD *)&this->byMagicUseTime[4][0] = 0;
      if ( !todo_555 )
        goto LABEL_9;
      v9 = (const void *)off_5CC578;
      goto LABEL_8;
    }
    this->_todo_278[100] = 0;
    return 1;
  }
  if ( nVal2 != 655363 )
    return 1;
  if ( this->_gap_551[3] )
  {
    v6 = this->_todo_555;
    *(_DWORD *)&this->byMagicUseTime[4][0] = 1;
    if ( !v6 )
    {
LABEL_9:
      (((MUIDialog *)this))->MUIDialog::InvokeCallback();
      return 1;
    }
    v9 = (const void *)off_5CC578;
LABEL_8:
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v9, 1);
    goto LABEL_9;
  }
  this->_todo_3d0[100] = 0;
  return 1;
}

// 0x004BF1C0
void UIRoleDialog::Create(int nVal)
{
  (*(void ( **)(UIRoleDialog *, _DWORD))(*(_DWORD *)((UIWnd *)this) + 12))(this, 0);
}

// 0x004BF1D0
int UIRoleDialog::Destroy(int nVal)
{
  UIRoleDialog *v2; // edi
  gbRenderInfoObj *v3; // esi
  gbRenderEffect *m_bmodal; // ecx
  gbMatrix4 *Top; // eax
  int result; // eax
  const gbVec3D *v7; // [esp+0x0] [ebp-0x20]
  gbVec3D *v8; // [esp+0x4] [ebp-0x1C]
v3 = (((gbSceneGraph *)gfxMgr->pSceneGraph))->gbSceneGraph::NewOneRenderObj((gbVisNode *)this);
  v2 = (UIRoleDialog *)((char *)this + 100);
  v3->Flags = 0;
  v3->Param = 0;
  m_bmodal = (gbRenderEffect *)this->m_bmodal;
  v3->pTexArray = (gbTextureArray *)this;
  v3->pEffect = m_bmodal;
  Top = (((gbMatrixStack *)gfxMgr->pMatrixStack[1]))->gbMatrixStack::GetTop();
  (((gbMatrix4 *)Top))->gbMatrix4::Transform(v7, v8);
  result = 0;
  v3->Priority = 1;
  v3->Z = 0.0f;
  return result;
}

// 0x004BF260
void UIRoleDialog::Render(int nVal)
{
  gbMatrixStack *v2; // edi
  gbDynVertBuf *DynVertBuf; // ebp
  float v5; // st7
  float v6; // st7
  float *v7; // ebx
  float v8; // st7
  float v9; // st7
  __int64 v10; // rax
  gbRenderEffect *v11; // ecx
  bool v12; // cc
  float v13; // [esp+0x64] [ebp-0x6C]
  gbRenderEffect *m_bvisible; // [esp+0x64] [ebp-0x6C]
  float v15; // [esp+0x64] [ebp-0x6C]
  float v16; // [esp+0x64] [ebp-0x6C]
  int v17; // [esp+0x7C] [ebp-0x54]
  struct gbVec3D v18; // [esp+0x80] [ebp-0x50] BYREF
  struct gbTextureArray v19; // [esp+0x8C] [ebp-0x44] BYREF
  char *nVala; // [esp+D4h] [ebp+0x4]

  v2 = gfxMgr->pMatrixStack[1];
  (((gbMatrixStack *)v2))->gbMatrixStack::Push();
  (((gbMatrixStack *)v2))->gbMatrixStack::LoadMatrix((gbMatrix4 *)(nVal + 32));
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x15u);
  (((gbRenderEffect *)this->m_static.m_bvisible))->gbRenderEffect::Begin();
  (((gbRenderEffect *)this->m_static.m_bvisible))->gbRenderEffect::Pass(0);
  (((gbMatrixStack *)v2))->gbMatrixStack::Push();
  v5 = *(float *)&this->_todo_050[12] * -0.20000000298023224f;
  v18.x = 0.0;
  v18.y = 1.0;
  v13 = v5;
  v18.z = 0.0;
  (((gbMatrixStack *)v2))->gbMatrixStack::Rotate(v13,  v18);
  v19.pTexPt[0] = *(gbTexture **)&this->_todo_050[16];
  m_bvisible = (gbRenderEffect *)this->m_static.m_bvisible;
  v19.nTex = 1;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&this->_todo_3d0[16], 1, m_bvisible, &v19);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&this->m_static.m_bfocus, 6, (gbRenderEffect *)this->m_static.m_bvisible, (gbTextureArray *)&this->_todo_050[20]);
  (((gbMatrixStack *)v2))->gbMatrixStack::Pop();
  (((gbMatrixStack *)v2))->gbMatrixStack::Push();
  v6 = *(float *)&this->_todo_050[12] * -2.0f;
  v18.x = 0.0;
  v18.y = 1.0;
  v15 = v6;
  v18.z = 0.0;
  (((gbMatrixStack *)v2))->gbMatrixStack::Rotate(v15,  v18);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&this->_todo_1c8[128], 6, (gbRenderEffect *)this->m_static.m_bvisible, (gbTextureArray *)&this->_todo_050[20]);
  (((gbMatrixStack *)v2))->gbMatrixStack::Pop();
  if ( *(_DWORD *)&this->_todo_050[8] == 1 )
  {
    (((gbMatrixStack *)v2))->gbMatrixStack::Scale(0.60000002,   1.0,   0.60000002);
    v17 = 0;
    v7 = (float *)&this->_todo_3d0[88];
    nVala = (char *)&this->_todo_3d0[116];
    do
    {
      if ( *(v7 - 1) <= 0.0 )
        break;
      if ( !*(_DWORD *)nVala )
      {
        (((gbMatrixStack *)v2))->gbMatrixStack::Push();
        v8 = *(float *)&this->_todo_050[12] * -0.5f;
        v18.x = 0.0;
        v9 = v8 - *(v7 - 1);
        v18.y = 1.0;
        v18.z = 0.0;
        v16 = v9;
        (((gbMatrixStack *)v2))->gbMatrixStack::Rotate(v16,  v18);
        (((gbMatrixStack *)v2))->gbMatrixStack::Translate(0.0,   *v7,   0.0);
        v10 = (__int64)(255.0 - *v7 * 0.016666668 * 255.0);
        v11 = (gbRenderEffect *)this->m_static.m_bvisible;
        HIDWORD(v10) = *(_DWORD *)&this->_todo_050[16];
        this->_todo_3d0[80] = v10;
        this->_todo_3d0[81] = v10;
        this->_todo_3d0[82] = v10;
        v19.nTex = 1;
        v19.pTexPt[0] = (gbTexture *)HIDWORD(v10);
        (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&this->_todo_3d0[16], 1, v11, &v19);
        (((gbMatrixStack *)v2))->gbMatrixStack::Pop();
      }
      v7 += 2;
      v12 = ++v17 < 4;
      nVala += 4;
    }
    while ( v12 );
    *(_DWORD *)&this->_todo_3d0[80] = -1;
  }
  (((gbRenderEffect *)this->m_static.m_bvisible))->gbRenderEffect::End();
  (((gbMatrixStack *)v2))->gbMatrixStack::Pop();
}
