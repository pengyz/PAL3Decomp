#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIAnimateCtrlEX.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445AA0(void); // from annotations
void * sub_445EA0(void); // from annotations
int sub_445F60(unsigned int a2); // from annotations
void __stdcall sub_452DF0(int *a1, int nRoleIndex); // from annotations

int GetRoleDataOffset(int nRoleIndex); // from annotations

// Unnamed globals (extern)
extern char byte_DC25F4;
extern int dword_DC25E8;
extern int dword_DC25EC;
extern int dword_DC25F0;
void __cdecl nullsub_74(void);

// 0x00441D50
int UIAnimateCtrlEX::StepAnimation()
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  __int64 v6; // rax
  UIWnd *m_pfather; // ecx

  v2 = *((_DWORD *)this + 43) - 1;
  *((_DWORD *)this + 43) = v2;
  v3 = v2;
  v4 = *((_DWORD *)this + 41);
  if ( v3 <= v4 )
    *((_DWORD *)this + 43) = v4;
  v5 = *((_DWORD *)this + 42);
  if ( *((_DWORD *)this + 43) >= v5 )
    *((_DWORD *)this + 43) = v5;
  v6 = (__int64)((double)*((int *)this + 45) - *((float *)this + 46));
  m_pfather = this->m_pfather;
  *((_DWORD *)this + 45) = v6;
  if ( m_pfather )
// [VFTABLE] LODWORD(v6) = ((int ( *)(UIWnd *, int, void *, _DWORD))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1005,
// [VFTABLE]   this->m_id,
// [VFTABLE]   *((_DWORD *)this + 43));
  return v6;
}

// 0x00441DC0
int UIAnimateCtrlEX::NextFrame()
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  __int64 v6; // rax
  UIWnd *m_pfather; // ecx

  v2 = *((_DWORD *)this + 43) + 1;
  *((_DWORD *)this + 43) = v2;
  v3 = v2;
  v4 = *((_DWORD *)this + 41);
  if ( v3 <= v4 )
    *((_DWORD *)this + 43) = v4;
  v5 = *((_DWORD *)this + 42);
  if ( *((_DWORD *)this + 43) >= v5 )
    *((_DWORD *)this + 43) = v5;
  v6 = (__int64)((double)*((int *)this + 45) + *((float *)this + 46));
  m_pfather = this->m_pfather;
  *((_DWORD *)this + 45) = v6;
  if ( m_pfather )
// [VFTABLE] LODWORD(v6) = ((int ( *)(UIWnd *, int, void *, _DWORD))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1005,
// [VFTABLE]   this->m_id,
// [VFTABLE]   *((_DWORD *)this + 43));
  return v6;
}

// 0x00452790
UIAnimateCtrlEX::UIAnimateCtrlEX()
{
  sub_445AA0();
  UIScene::GetSys();
  sub_4422E0(&this->m_Frame);
  ((CCBResultWindow *)&this->m_ResultWnd)->ctor();
  ((UITextArea *)&this->m_TextArea)->InitAfterClear();
  sub_445EA0();
  *(_DWORD *)&this->m_bAnimFlag = 0;
}

// 0x00452AA0
void UIAnimateCtrlEX::Render()
{
  int v2; // ecx
  int v3; // edx
  int v4; // esi
  _DWORD *v5; // esi
  int i; // ebx
  double width; // st7
  RoleSystem *v8; // ebx
  gbVertPoolMgr *pVertPoolMgr; // ecx
  gbDynVertBuf *DynVertBuf; // ebp
  gbMatrixStack *v11; // esi
  float height; // [esp+0x4] [ebp-0x94]
  int v13; // [esp+0x8] [ebp-0x90] BYREF
  int v14; // [esp+0xC] [ebp-0x8C]
  float v15; // [esp+0x10] [ebp-0x88]
  int v16; // [esp+0x14] [ebp-0x84]
  float v17; // [esp+0x18] [ebp-0x80]
  struct gbUIQuad v18; // [esp+0x1C] [ebp-0x7C] BYREF
  int v19; // [esp+0x44] [ebp-0x54]
  int v20; // [esp+0x48] [ebp-0x50]
  struct gbTextureArray v21; // [esp+0x54] [ebp-0x44] BYREF

  if ( !this->m_bvisible )
    return;
// [VFTABLE] ((void ( *)(UITextArea *))this->m_TextArea.__vftable->Render)(&this->m_TextArea);
  if ( !this->m_TextArea.m_bvisible )
  {
    *(_DWORD *)&this->m_bAnimFlag = 0;
LABEL_10:
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
    return;
  }
  v2 = *((_DWORD *)&this->m_TextArea.m_bInvalidate + 3);
  v13 = *((_DWORD *)&this->m_TextArea.m_bInvalidate + 2) + 5;
  v3 = *((_DWORD *)&this->m_TextArea.m_bInvalidate + 4);
  v14 = v2 + 10;
  v4 = *((_DWORD *)&this->m_TextArea.m_bInvalidate + 5);
  LODWORD(v15) = v3 - 5;
  v16 = v4 - 5;
  v5 = (_DWORD *)(UISceneUpdate() + 492772);
  for ( i = 0; i < *v5; ++i )
    sub_452DF0(&v13, i);
  if ( *((_DWORD *)&this->m_TextArea + 43) != 2 )
    goto LABEL_10;
  GetRoleDataOffset(0);
  GetRoleDataOffset(1);
  width = (double)g_DrvInfo.width;
  v8 = g_pRoleSystem;
  v19 = v13 + (LODWORD(v15) - v13) / 2;
  v18.z = 0.0;
  v18.color = -1;
  v18.sv = 0.0;
  v20 = v14 + (v16 - v14) / 2;
  v18.su = 0.0;
  v18.eu = 1.0;
  v18.ev = 1.0;
  v18.sx = -14.0 / width;
  height = (float)g_DrvInfo.height;
  v18.ey = 14.0 / height;
  v18.ex = 14.0 / width;
  v18.sy = -14.0 / height;
  pVertPoolMgr = gfxMgr->pVertPoolMgr;
  v17 = ((double)v19 + (double)v19) / width - 1.0;
  DynVertBuf = ((gbVertPoolMgr *)pVertPoolMgr)->GetDynVertBuf(0x15u);
  v11 = gfxMgr->pMatrixStack[1];
  if ( (byte_DC25F4 & 1) == 0 )
  {
    dword_DC25E8 = 0;
    byte_DC25F4 |= 1u;
    dword_DC25EC = 0;
    dword_DC25F0 = 1065353216;
    atexit(nullsub_74);
  }
  ((gbMatrixStack *)v11)->Push();
  ((gbMatrixStack *)v11)->Translate(v18.ex,   v15,   0.0);
  ((gbMatrixStack *)v11)->Rotate(*(float *)((char *)&v8[1].m_partyUI3._todo_05C + 75), (gbVec3D *)&dword_DC25E8);
  v21.pTexPt[0] = (gbTexture *)sub_445F60(0);
  v21.nTex = 1;
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v18, 1, g_pRenderEffect_1895048, &v21);
  ((gbMatrixStack *)v11)->Pop();
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
}

// 0x00452D30
BOOL UIAnimateCtrlEX::ComputeStatBonus(int nVal, int nVal2)
{
  double v5; // st7
  int v6; // ebx

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  v5 = g_pCameraCtrl->m_fOrbitAngle * 57.29578;
  LOBYTE(this->m_ResultWnd.m_nIndex) = 0;
  *(float *)&this->m_ResultWnd.m_pGP = v5;
  v6 = ((UIListBox *)this)->Update(nVal, nVal2);
// [VFTABLE] ((void ( *)(UITextArea *, int, _DWORD))this->m_TextArea.__vftable->Update_2ff0)(&this->m_TextArea, nVal, 0);
  return v6;
}

// 0x00452DA0
int UIAnimateCtrlEX::OnNotify(int msg, int wparam, int lparam)
{
  void *vftable; // eax

  if ( msg == 1001 )
  {
    if ( !*(_DWORD *)&this->m_bAnimFlag )
    {
// [VFTABLE] vftable = this->m_TextArea.__vftable;
      *(_DWORD *)&this->m_bAnimFlag = 1;
      ((void ( *)(UITextArea *, int))vftable->ShowWindow)(&this->m_TextArea, 1);
      return 0;
    }
// [VFTABLE] ((void ( *)(UITextArea *, _DWORD))this->m_TextArea.__vftable->ShowWindow)(&this->m_TextArea, 0);
  }
  return 0;
}

// 0x00530990
int UIAnimateCtrlEX::SetTextBottom(int nVal)
{
  this->m_TextArea.m_rect.bottom = nVal;
  return nVal;
}

// 0x00530BE0
int UIAnimateCtrlEX::SwapBuffer(int nNewBuf)
{
  int result; // eax

  result = (int)this->m_TextArea.m_childs.m_pData;
  this->m_TextArea.m_childs.capacity = result;
  this->m_TextArea.m_childs.m_pData = (char *)nNewBuf;
  return result;
}

// 0x00535A70
int UIAnimateCtrlEX::InitMatrix()
{
  gbTexture **v2; // edi
  int v3; // ebx

  v2 = &this->m_texarray.m_ptex[3];
  v3 = 4;
  do
  {
    v2 += 3;
    --v3;
  }
  while ( v3 );
  this->m_nLoop = 0;
  this->m_mode = 0;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 42) = 0;
  *((_DWORD *)this + 43) = 0;
  *((_DWORD *)this + 44) = 0;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 46) = 0;
  *((_DWORD *)this + 47) = 0;
  ((UIScene *)this)->ClearColors();
  return (int)this;
}

// 0x00535E70
int UIAnimateCtrlEX::NormalizeVector(int nVal, int nVal2, int nVal3, int nVal4)
{
  double v6; // st7
  double v7; // st6
  int nVal2a; // [esp+0xC] [ebp+0x8]
  float nVal3a; // [esp+0x10] [ebp+0xC]

  *((_DWORD *)this + 45) = *((_DWORD *)this + 42);
  *((_DWORD *)this + 46) = *((_DWORD *)this + 43);
  *((_DWORD *)this + 47) = *((_DWORD *)this + 44);
  *((_DWORD *)this + 42) = nVal;
  *((_DWORD *)this + 43) = nVal2;
  *((_DWORD *)this + 44) = nVal3;
  v6 = *((float *)this + 42) - *((float *)this + 45);
  *(float *)&nVal2a = *((float *)this + 43) - *((float *)this + 46);
  v7 = *((float *)this + 44) - *((float *)this + 47);
  this->m_mode = nVal2a;
  nVal3a = v7;
  *(float *)&this->m_nLoop = v6;
  *((float *)this + 41) = nVal3a;
  ((gbVec3D *)&this->m_nLoop)->Normalize();
  *((_DWORD *)this + 48) = nVal4;
  return nVal4;
}
