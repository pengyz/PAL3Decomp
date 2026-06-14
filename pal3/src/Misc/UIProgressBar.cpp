#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIProgressBar.h"

// Forward declarations for unnamed functions
int sub_445AA0(void); // from annotations

// Unnamed globals (extern)
extern int dword_A3A750;

// 0x00439030
int * UIProgressBar::ctor()
{
  sub_445AA0();
  *((_DWORD *)this + 74) = 0;
  *((_DWORD *)this + 75) = 0;
  *((_DWORD *)this + 76) = 0;
  *((_DWORD *)this + 71) = 1065353216;
  *((_DWORD *)this + 70) = 1065353216;
  *((_DWORD *)this + 69) = 1065353216;
  *((_DWORD *)this + 73) = 0;
  this->m_mode = 0;
  *(&this->m_warningval + 4) = 0;
  *((_DWORD *)this + 63) = 0;
  *((_DWORD *)this + 62) = 0;
  *((_DWORD *)this + 65) = 0;
  *((_DWORD *)this + 64) = 0;
  *((_DWORD *)this + 68) = 0;
  *((_DWORD *)this + 67) = 0;
  *((_DWORD *)this + 66) = 0;
  *((_BYTE *)&this->m_warningval + 20) = 0;
  *((_DWORD *)this + 61) = 98;
  *((_DWORD *)this + 72) = 0;
  return (int *)this;
}

// 0x00439410
void UIProgressBar::Render()
{
  gbMatrixStack *v1; // ebp
  gbMatrixStack *v2; // edi
  gbSceneGraph *v4; // ebx
  int m_mode; // eax
  int *p_m_progress; // ebp
  int v7; // eax
  gbVec3D *v8; // ebp
  int v9; // ebp
  int v10; // ebp
  bool v11; // cc
  float v12; // [esp+0x54] [ebp-A0h]
  float v13; // [esp+0x54] [ebp-A0h]
  float v14; // [esp+0x54] [ebp-A0h]
  float v15; // [esp+0x54] [ebp-A0h]
  float v16; // [esp+0x54] [ebp-A0h]
  float v17; // [esp+0x54] [ebp-A0h]
  gbCamera *v18; // [esp+0x58] [ebp-0x9C]
  int *v19; // [esp+0x6C] [ebp-0x88]
  struct gbVec3D v20; // [esp+0x70] [ebp-0x84] BYREF
  int v21; // [esp+0x7C] [ebp-0x78]
  gbMatrixStack *v22; // [esp+0x80] [ebp-0x74]
  gbSceneGraph *pSceneGraph; // [esp+0x84] [ebp-0x70]
  struct gbQuaternion v24; // [esp+0x88] [ebp-0x6C] BYREF
  gbQuaternion v25; // [esp+0x98] [ebp-0x5C] BYREF
  gbQuaternion v26; // [esp+A8h] [ebp-0x4C] BYREF
  struct gbVec3D v27; // [esp+B8h] [ebp-0x3C] BYREF
  struct gbVec3D v28; // [esp+C4h] [ebp-0x30] BYREF
  struct gbVec3D v29; // [esp+D0h] [ebp-0x24] BYREF
  struct gbVec3D v30; // [esp+DCh] [ebp-0x18] BYREF
  struct gbVec3D v31; // [esp+E8h] [ebp-0xC] BYREF

  v2 = gfxMgr->pMatrixStack[1];
  v22 = gfxMgr->pMatrixStack[0];
  v1 = v22;
  ((gbMatrixStack *)v2)->Push();
  ((gbMatrixStack *)v22)->Push();
  v18 = (gbCamera *)*((_DWORD *)this + 73);
  pSceneGraph = gfxMgr->pSceneGraph;
  v4 = pSceneGraph;
  ((gbSceneGraph *)pSceneGraph)->Begin(v18);
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  memset(&v25, 0, 12);
  v25.w = 1.0;
  memset(&v26, 0, 12);
  v26.w = 1.0;
  memset(&v24, 0, 12);
  v24.w = 1.0;
  v20.x = 1.0;
  v20.y = 0.0;
  v20.z = 0.0;
  ((gbQuaternion *)&v25)->SetAxisAngle(&v20, 45.0);
  v20.x = 0.0;
  v20.y = 1.0;
  v20.z = 0.0;
  ((gbQuaternion *)&v26)->SetAxisAngle(&v20, 90.0);
  ((gbQuaternion *)&v26)->MultiplyBy(&v25, &v24);
  ((gbQuaternion *)&v24)->GetMatrix((gbMatrix4 *)dword_A3A750);
  ((gbVolModNode *)&g_pVolModNode)->Attach(0);
  ((gbCamera *)*((gbCamera **)this + 73))->SetAsCurrent(3);
  m_mode = this->m_mode;
  v21 = 0;
  if ( m_mode > 0 )
  {
    p_m_progress = &this->m_progress;
    v19 = &this->m_progress;
    while ( 1 )
    {
      v7 = *(p_m_progress - 3);
      v8 = (gbVec3D *)(p_m_progress + 1);
      if ( v7 )
        break;
LABEL_11:
      p_m_progress = v19 + 8;
      v11 = ++v21 < this->m_mode;
      v19 += 8;
      if ( !v11 )
      {
        v4 = pSceneGraph;
        v1 = v22;
        goto LABEL_13;
      }
    }
    ((gbMatrixStack *)v2)->Push();
    ((gbMatrixStack *)v2)->Translate(v8);
    v12 = *((float *)this + 62);
    v20.x = 0.0;
    v20.y = 1.0;
    v20.z = 0.0;
    ((gbMatrixStack *)v2)->Rotate(v12, v20);
    v13 = *((float *)this + 64);
    v28.x = 1.0;
    v28.y = 0.0;
    v28.z = 0.0;
    ((gbMatrixStack *)v2)->Rotate(v13, v28);
    v14 = *((float *)this + 65);
    v27.x = 0.0;
    v27.y = 0.0;
    v27.z = 1.0;
    ((gbMatrixStack *)v2)->Rotate(v14, v27);
    v15 = *((float *)this + 66);
    v29.x = 1.0;
    v29.y = 0.0;
    v29.z = 0.0;
    ((gbMatrixStack *)v2)->Rotate(v15, v29);
    v16 = *((float *)this + 67);
    v31.x = 0.0;
    v31.y = 1.0;
    v31.z = 0.0;
    ((gbMatrixStack *)v2)->Rotate(v16, v31);
    v17 = *((float *)this + 68);
    v30.x = 0.0;
    v30.y = 0.0;
    v30.z = 1.0;
    ((gbMatrixStack *)v2)->Rotate(v17, v30);
    v9 = LODWORD(v8[-1].y) - 1;
    if ( v9 )
    {
      v10 = v9 - 1;
      if ( !v10 )
      {
        ((Actor *)*v19)->DispatchAction(0);
LABEL_10:
        ((gbMatrixStack *)v2)->Pop();
        goto LABEL_11;
      }
      if ( v10 != 1 )
        goto LABEL_10;
    }
    ((gbMatrixStack *)v2)->Scale(*((float *)this + 69),   *((float *)this + 70),   *((float *)this + 71));
    (*(void ( **)(int, _DWORD))(*(_DWORD *)*v19 + 16))(*v19, 0);
    goto LABEL_10;
  }
LABEL_13:
  ((gbSceneGraph *)v4)->End();
  ((gbMatrixStack *)v1)->Pop();
  ((gbMatrixStack *)v2)->Pop();
}

// 0x00439810
void UIProgressBar::Destroy()
{
  int v2; // edi
  tagRECT *p_m_decorateRc; // ebx

  v2 = 0;
  if ( *((_DWORD *)this + 73) )
  {
    operator delete(*((void **)this + 73));
    *((_DWORD *)this + 73) = 0;
  }
  if ( this->m_mode > 0 )
  {
    p_m_decorateRc = &this->m_decorateRc;
    do
    {
      ((PalScript *)p_m_decorateRc)->ReleaseStateResource();
      ++v2;
      p_m_decorateRc += 2;
    }
    while ( v2 < this->m_mode );
  }
}

// 0x00439A20
BOOL UIProgressBar::CheckRayHitRole(int nVal, int nVal2)
{
  int v5; // edi
  int *p_m_progress; // esi
  double v8; // st7
  char v9; // c0
  bool v10; // zf
  bool v11; // c0
  bool v12; // c3
  int v13; // ecx
  double v14; // st7
  void *RayToScreen; // esi
  int m_mode; // eax
  int v17; // edi
  int *i; // esi
  UIWnd *m_pfather; // ecx
  void *v20; // esi
  int v21; // eax
  int v22; // edi
  int *j; // esi
  UIWnd *v24; // ecx
  void *v25; // esi
  int v26; // eax
  int v27; // edi
  int *k; // esi
  UIWnd *v29; // ecx
  void *v30; // esi
  int v31; // eax
  int v32; // edi
  int *m; // esi
  UIWnd *v34; // ecx
  void *v35; // eax
  int v36; // edx
  int v37; // edi
  LONG *n; // eax
  char *v39; // esi
  UIWnd *v40; // ecx
  UIWnd *v41; // ecx
  struct tagPOINT Point; // [esp+0x10] [ebp-0x84] BYREF
  gbRay v43; // [esp+0x18] [ebp-0x7C] BYREF
  struct gbOBBox actionId; // [esp+0x30] [ebp-0x64] BYREF
  _BYTE pRay[24]; // [esp+0x7C] [ebp-0x18] BYREF

  if ( !this->m_bvisible )
    return 0;
  v5 = 0;
  if ( this->m_mode > 0 )
  {
    p_m_progress = &this->m_progress;
    do
    {
      if ( *(p_m_progress - 3) )
      {
        if ( *(p_m_progress - 1) == 2 )
        {
          ((Actor *)*p_m_progress)->QueryState();
        }
        else if ( *(p_m_progress - 1) == 3 )
        {
          (*(void ( **)(int))(*(_DWORD *)*p_m_progress + 20))(*p_m_progress);
        }
      }
      ++v5;
      p_m_progress += 8;
    }
    while ( v5 < this->m_mode );
  }
  if ( *(&this->m_warningval + 4) == 1 )
  {
    v14 = (double)*((int *)this + 61) * *(float *)&nVal + *((float *)this + 62);
    *((float *)this + 62) = v14;
    if ( v14 >= 359.0 )
      *((_DWORD *)this + 62) = 0;
  }
  else
  {
    if ( *(&this->m_warningval + 4) != 2 )
      goto LABEL_21;
    v8 = (double)*((int *)this + 61) * *(float *)&nVal + *((float *)this + 62);
    v10 = v9 == 0;
    *((float *)this + 62) = v8;
    v11 = v8 < *((float *)this + 63);
    v12 = v8 == *((float *)this + 63);
    if ( !v10 )
    {
      if ( !v11 && !v12 )
      {
        *((_BYTE *)&this->m_warningval + 20) = 1;
        *(&this->m_warningval + 4) = 0;
        *((_DWORD *)this + 62) = 0;
        goto LABEL_21;
      }
      goto LABEL_16;
    }
    if ( v11 || v12 )
    {
LABEL_16:
      *((_BYTE *)&this->m_warningval + 20) = 0;
      goto LABEL_21;
    }
    v13 = *((_DWORD *)this + 63);
    *(&this->m_warningval + 4) = 0;
    *((_DWORD *)this + 62) = v13;
    *((_BYTE *)&this->m_warningval + 20) = 1;
  }
LABEL_21:
  if ( !this->m_benable )
    return 0;
  if ( !nVal2 )
    return ((UIListBox *)this)->Update(nVal, nVal2);
  if ( g_Input.KeyInfo[0].PressTime == 1 )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    RayToScreen = ((PalScript *)this)->GetRayToScreen(pRay, &Point.x);
    m_mode = this->m_mode;
    qmemcpy(&v43, RayToScreen, sizeof(v43));
    v17 = 0;
    if ( m_mode <= 0 )
      return ((UIListBox *)this)->Update(nVal, nVal2);
    for ( i = &this->m_progress; ; i += 8 )
    {
      if ( !*(i - 3) )
        goto LABEL_35;
      if ( *(i - 1) != 1 )
      {
        if ( *(i - 1) == 2 )
        {
          ((Actor *)*i)->PlayAction((int)&actionId);
          ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(i + 1));
          goto LABEL_34;
        }
        if ( *(i - 1) != 3 )
          goto LABEL_35;
      }
      ((gbGeomNode *)*i)->GetOBBox(&actionId);
      ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(i + 1));
LABEL_34:
      if ( ((gbRay *)&v43)->IsColOBB_H(actionId) )
      {
        m_pfather = this->m_pfather;
        if ( m_pfather )
// [VFTABLE] m_pfather->__vftable->OnMessage(1013, (int)this->m_id, v17);
        return ((UIListBox *)this)->Update(nVal, nVal2);
      }
LABEL_35:
      if ( ++v17 >= this->m_mode )
        return ((UIListBox *)this)->Update(nVal, nVal2);
    }
  }
  if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    v20 = ((PalScript *)this)->GetRayToScreen(pRay, &Point.x);
    v21 = this->m_mode;
    qmemcpy(&v43, v20, sizeof(v43));
    v22 = 0;
    if ( v21 <= 0 )
      return ((UIListBox *)this)->Update(nVal, nVal2);
    for ( j = &this->m_progress; ; j += 8 )
    {
      if ( !*(j - 3) )
        goto LABEL_50;
      if ( *(j - 1) != 1 )
      {
        if ( *(j - 1) == 2 )
        {
          ((Actor *)*j)->PlayAction((int)&actionId);
          ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(j + 1));
          goto LABEL_49;
        }
        if ( *(j - 1) != 3 )
          goto LABEL_50;
      }
      ((gbGeomNode *)*j)->GetOBBox(&actionId);
      ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(j + 1));
LABEL_49:
      if ( ((gbRay *)&v43)->IsColOBB_H(actionId) )
      {
        v24 = this->m_pfather;
        if ( v24 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))v24->__vftable->OnMessage)(v24, 1016, this->m_id, v22);
        return ((UIListBox *)this)->Update(nVal, nVal2);
      }
LABEL_50:
      if ( ++v22 >= this->m_mode )
        return ((UIListBox *)this)->Update(nVal, nVal2);
    }
  }
  if ( (g_Input.KeyInfo[0].Data & 0xFu) > 1 )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    v25 = ((PalScript *)this)->GetRayToScreen(pRay, &Point.x);
    v26 = this->m_mode;
    qmemcpy(&v43, v25, sizeof(v43));
    v27 = 0;
    if ( v26 <= 0 )
      return ((UIListBox *)this)->Update(nVal, nVal2);
    for ( k = &this->m_progress; ; k += 8 )
    {
      if ( !*(k - 3) )
        goto LABEL_65;
      if ( *(k - 1) != 1 )
      {
        if ( *(k - 1) == 2 )
        {
          ((Actor *)*k)->PlayAction((int)&actionId);
          ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(k + 1));
          goto LABEL_64;
        }
        if ( *(k - 1) != 3 )
          goto LABEL_65;
      }
      ((gbGeomNode *)*k)->GetOBBox(&actionId);
      ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(k + 1));
LABEL_64:
      if ( ((gbRay *)&v43)->IsColOBB_H(actionId) )
      {
        v29 = this->m_pfather;
        if ( v29 )
// [VFTABLE] v29->__vftable->OnMessage(1017, (int)this->m_id, v27);
        return ((UIListBox *)this)->Update(nVal, nVal2);
      }
LABEL_65:
      if ( ++v27 >= this->m_mode )
        return ((UIListBox *)this)->Update(nVal, nVal2);
    }
  }
  if ( g_Input.KeyInfo[1].PressTime == 1 )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    v30 = ((PalScript *)this)->GetRayToScreen(pRay, &Point.x);
    v31 = this->m_mode;
    qmemcpy(&v43, v30, sizeof(v43));
    v32 = 0;
    if ( v31 <= 0 )
      return ((UIListBox *)this)->Update(nVal, nVal2);
    for ( m = &this->m_progress; ; m += 8 )
    {
      if ( !*(m - 3) )
        goto LABEL_80;
      if ( *(m - 1) != 1 )
      {
        if ( *(m - 1) == 2 )
        {
          ((Actor *)*m)->PlayAction((int)&actionId);
          ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(m + 1));
          goto LABEL_79;
        }
        if ( *(m - 1) != 3 )
          goto LABEL_80;
      }
      ((gbGeomNode *)*m)->GetOBBox(&actionId);
      ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(m + 1));
LABEL_79:
      if ( ((gbRay *)&v43)->IsColOBB_H(actionId) )
      {
        v34 = this->m_pfather;
        if ( v34 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))v34->__vftable->OnMessage)(v34, 1018, this->m_id, v32);
        return ((UIListBox *)this)->Update(nVal, nVal2);
      }
LABEL_80:
      if ( ++v32 >= this->m_mode )
        return ((UIListBox *)this)->Update(nVal, nVal2);
    }
  }
  ((GRPinput *)&g_Input)->GetCursorPos();
  v35 = ((PalScript *)this)->GetRayToScreen(pRay, &Point.x);
  v36 = this->m_mode;
  qmemcpy(&v43, v35, sizeof(v43));
  v37 = 0;
  if ( v36 <= 0 )
    return ((UIListBox *)this)->Update(nVal, nVal2);
  for ( n = &this->m_decorateRc.bottom; ; n += 8 )
  {
    if ( *(n - 2) )
    {
      if ( *n == 1 )
        break;
      if ( *n == 2 )
      {
        v39 = (char *)this + 32 * v37;
        ((Actor *)*((Actor **)v39 + 22))->PlayAction((int)&actionId);
        goto LABEL_94;
      }
      if ( *n == 3 )
        break;
    }
    if ( ++v37 >= v36 )
      return ((UIListBox *)this)->Update(nVal, nVal2);
  }
  v39 = (char *)this + 32 * v37;
  ((gbGeomNode *)*((gbGeomNode **)v39 + 22))->GetOBBox(&actionId);
LABEL_94:
  ((gbMatrix4 *)&actionId)->RightTranslate((gbVec3D *)(v39 + 92));
  if ( ((gbRay *)&v43)->IsColOBB_H(actionId) )
  {
    v39[72] = 0;
    v40 = this->m_pfather;
    if ( v40 )
// [VFTABLE] v40->__vftable->OnMessage(1014, (int)this->m_id, v37);
  }
  else if ( !v39[72] )
  {
    v39[72] = 1;
    v41 = this->m_pfather;
    if ( v41 )
// [VFTABLE] v41->__vftable->OnMessage(1015, (int)this->m_id, v37);
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x0043FDF0
void UIProgressBar::FindChildByName(float fValue)
{
  double m_tradius; // st7
  double v3; // st6

  if ( this->m_tradius > 0.0 )
  {
    m_tradius = fValue;
    if ( fValue < 0.0 )
      m_tradius = 0.0;
    if ( m_tradius > this->m_tradius )
      m_tradius = this->m_tradius;
    v3 = m_tradius * this->m_bradius;
    *(float *)&this->m_lradius = v3;
    if ( v3 >= *(float *)&this->m_rradius )
      this->m_lradius = this->m_rradius;
    *(float *)&this->m_pbkInfo = *(float *)&this->m_pbk * this->m_stepval;
    if ( m_tradius > (double)*(&this->m_warningval + 5) )
    {
      *((_BYTE *)&this->m_warningval + 18) = 1;
    }
    else
    {
      *((_BYTE *)&this->m_warningval + 17) = 1;
      *((_BYTE *)&this->m_warningval + 18) = 0;
    }
    LOBYTE(this->m_ppic) = 0;
  }
}
