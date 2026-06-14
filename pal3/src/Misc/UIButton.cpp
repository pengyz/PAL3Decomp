#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIButton.h"

// Forward declarations for unnamed functions
int sub_445AA0(void); // from annotations

int crt_sub_00540070(void); // from annotations
int crt_sub_00540DC0(void); // from annotations

// 0x0043F7F0
// write access to const memory has been detected, the output may be wrong!
int *UIButton::ctor_17()
{
  int v2; // ecx

  sub_445AA0();
  *(_DWORD *)&this->m_hasDBclk = 0;
  this->m_ratiow = 0.0;
  this->m_texarray.m_ptex[3] = 0;
  this->m_texarray.m_ptex[4] = (gbTexture *)1065353216;
  this->m_texarray.m_ptex[5] = 0;
  this->m_texarray.m_ptex[7] = 0;
  this->m_texarray.m_ptex[9] = (gbTexture *)0x40000000;
  this->m_texarray.m_ptex[10] = 0;
  this->m_texarray.m_ptex[11] = 0;
  this->m_texarray.m_ptex[12] = 0;
  this->m_texarray.m_ptex[13] = 0;
  this->m_texarray.m_ptex[14] = 0;
  this->m_texarray.m_ptex[15] = 0;
  LOBYTE(this->m_texarray.m_num) = 0;
  this->m_texarrayInfo[2] = 0;
  this->m_disablepicInfo = 0;
  this->m_alignmode = 0;
  *(_DWORD *)&this->m_caption[4] = 0;
  *(_DWORD *)&this->m_caption[8] = 0;
  *(_DWORD *)&this->m_caption[12] = 0;
  *(_DWORD *)&this->m_caption[16] = 0;
  BYTE2(this->m_texarrayInfo[0]) = -1;
  BYTE1(this->m_texarrayInfo[0]) = -1;
  LOBYTE(this->m_texarrayInfo[0]) = -1;
  HIBYTE(this->m_texarrayInfo[0]) = -1;
  gbColorQuad::ColorQuadFmt = 1;
  BYTE2(this->m_texarrayInfo[1]) = -1;
  BYTE1(this->m_texarrayInfo[1]) = 0;
  LOBYTE(this->m_texarrayInfo[1]) = 0;
  HIBYTE(this->m_texarrayInfo[1]) = -1;
  *(_DWORD *)&this->m_caption[20] = 0;
  *(_DWORD *)&this->m_caption[40] = 1065353216;
  this->m_caption[44] = 0;
  this->m_caption[45] = 0;
  this->m_caption[46] = 0;
  *(_DWORD *)&this->m_caption[36] = 6;
  *(_DWORD *)&this->m_caption[24] = -1;
  v2 = (unsigned __int8)this->m_caption[27];
  this->m_disablepic = 0;
  *(_DWORD *)&this->m_mouseoff = 0;
  *(_DWORD *)this->m_caption = 0;
  *(_DWORD *)&this->m_caption[32] = v2;
  *(_DWORD *)&this->m_caption[28] = v2;
  *(_DWORD *)&this->m_caption[48] = -1;
  return (int *)this;
}

// 0x0043F970
void UIButton::_UIButton()
{

// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x0043F9C0
void UIButton::Destroy()
{
  gbRefObject *v2; // ecx
  gbRefObject *m_disablepicInfo; // ecx

  v2 = (gbRefObject *)this->m_texarrayInfo[2];
  if ( v2 )
  {
    ((gbRefObject *)v2)->Release();
    this->m_texarrayInfo[2] = 0;
  }
  m_disablepicInfo = (gbRefObject *)this->m_disablepicInfo;
  if ( m_disablepicInfo )
  {
    ((gbRefObject *)m_disablepicInfo)->Release();
    this->m_disablepicInfo = 0;
  }
}

// 0x0043FF00
int UIButton::Create(int id, int *pRect, int parent)
{
  LONG left; // ebx
  double v5; // st7

  this->m_rect = *(tagRECT *)pRect;
  this->m_state = (UIButton_UIBUTTON_STATE)*pRect;
  *(_DWORD *)&this->m_canctrl = pRect[1];
  this->m_offsetx = pRect[2];
  left = this->m_rect.left;
  LODWORD(this->m_offsety) = pRect[3];
  v5 = (double)(this->m_rect.right - left);
  *(float *)&this->m_texarray.m_ptex[6] = v5;
  *(float *)&this->m_texarray.m_ptex[7] = v5;
  return ((PalScript *)this)->Create(id, (tagRECT *)pRect, parent);
}

// 0x0043FF70
void UIButton::Render()
{
  int v2; // eax
  float m_ratiow; // eax
  double v4; // st7
  __int64 v5; // rax
  double v6; // st7
  double v7; // st6
  int v8; // edi
  int v9; // ebx
  int v10; // ebp
  float v11; // ecx
  gbTexture *v12; // ecx
  int v13; // edi
  __int64 v14; // rax
  double left; // st7
  int v16; // ebx
  __int64 v17; // rax
  double right; // st7
  double v19; // st6
  int v20; // edi
  __int64 v21; // rax
  gbTexture *v22; // ecx
  int v23; // ebx
  int v24; // edi
  float v25; // eax
  double v26; // st7
  double v27; // st6
  int v28; // edi
  __int64 v29; // rax
  double v30; // st7
  UIButton_UIBUTTON_STATE v31; // ebx
  __int64 v32; // rax
  int v33; // ecx
  gbTexture *v34; // edi
  int v35; // ebp
  int v36; // ebx
  double v37; // st7
  int v38; // edi
  __int64 v39; // rax
  double bottom; // st7
  double v41; // st6
  int v42; // ebx
  __int64 v43; // rax
  int v44; // ecx
  gbTexture *v45; // edi
  int v46; // ebp
  int v47; // ebx
  int v48; // eax
  int v49; // [esp+0x4] [ebp-0x224]
  int v50[34]; // [esp+0x4C] [ebp-0x1DC] BYREF
  int v51[85]; // [esp+D4h] [ebp-0x154] BYREF

  if ( this->m_bvisible )
  {
    v2 = *(_DWORD *)&this->m_hasDBclk;
    if ( v2 )
    {
      if ( v2 == 1 )
      {
        m_ratiow = this->m_ratiow;
        if ( m_ratiow == 0.0 )
        {
          v14 = (__int64)((double)this->m_rect.bottom
                        - (*(float *)&this->m_texarray.m_ptex[13]
                         + *(float *)&this->m_texarray.m_ptex[9])
                        - 1.0);
          LODWORD(this->m_offsety) = v14;
          left = (double)this->m_rect.left;
          v16 = (__int64)((double)(int)v14 - *(float *)&this->m_texarray.m_ptex[3]);
          *(_DWORD *)&this->m_canctrl = v16;
          v17 = (__int64)(left + *(float *)&this->m_texarray.m_ptex[10] + *(float *)&this->m_texarray.m_ptex[9]);
          right = (double)this->m_rect.right;
          v19 = *(float *)&this->m_texarray.m_ptex[11] + *(float *)&this->m_texarray.m_ptex[9];
          v20 = v17;
          this->m_state = (UIButton_UIBUTTON_STATE)v17;
          v21 = (__int64)(right - v19);
          v22 = (gbTexture *)(v16 - *(_DWORD *)&this->m_caption[8] / 2);
          v23 = *(_DWORD *)&this->m_caption[4];
          this->m_offsetx = v21;
          this->m_texarray.m_ptex[0] = v22;
          v24 = ((int)v21 - v20) / 2 - v23 / 2 + v20;
          HIDWORD(v21) = (char *)v22 + *(_DWORD *)&this->m_caption[16];
          LODWORD(v21) = v24 + *(_DWORD *)&this->m_caption[12];
          *(_DWORD *)&this->m_bBigFont = v24;
          this->m_texarray.m_ptex[1] = (gbTexture *)(v23 + v21);
          this->m_texarray.m_ptex[2] = (gbTexture *)(*(_DWORD *)&this->m_caption[8] + HIDWORD(v21));
        }
        else if ( LODWORD(m_ratiow) == 1 )
        {
          v4 = (double)this->m_rect.left;
          v49 = (__int64)(*(float *)&this->m_texarray.m_ptex[12]
                        + *(float *)&this->m_texarray.m_ptex[9]
                        + (double)this->m_rect.top
                        - 1.0);
          *(_DWORD *)&this->m_canctrl = v49;
          v5 = (__int64)(v4 + *(float *)&this->m_texarray.m_ptex[10] + *(float *)&this->m_texarray.m_ptex[9]);
          v6 = (double)this->m_rect.right;
          v7 = *(float *)&this->m_texarray.m_ptex[11] + *(float *)&this->m_texarray.m_ptex[9];
          v8 = v5;
          this->m_state = (UIButton_UIBUTTON_STATE)v5;
          v9 = (__int64)(v6 - v7);
          this->m_offsetx = v9;
          v10 = *(_DWORD *)&this->m_caption[8];
          LODWORD(v11) = (__int64)((double)v49 + *(float *)&this->m_texarray.m_ptex[3]);
          LODWORD(v5) = *(_DWORD *)&this->m_caption[8];
          this->m_offsety = v11;
          v12 = (gbTexture *)(LODWORD(v11) - (int)v5 / 2);
          this->m_texarray.m_ptex[0] = v12;
          v13 = (v9 - v8) / 2 - *(_DWORD *)&this->m_caption[4] / 2 + v8;
          HIDWORD(v5) = (char *)v12 + *(_DWORD *)&this->m_caption[16];
          LODWORD(v5) = *(_DWORD *)&this->m_caption[4] + v13 + *(_DWORD *)&this->m_caption[12];
          *(_DWORD *)&this->m_bBigFont = v13;
          this->m_texarray.m_ptex[1] = (gbTexture *)v5;
          this->m_texarray.m_ptex[2] = (gbTexture *)(v10 + HIDWORD(v5));
        }
      }
    }
    else
    {
      v25 = this->m_ratiow;
      if ( v25 == 0.0 )
      {
        v37 = *(float *)&this->m_texarray.m_ptex[10] + *(float *)&this->m_texarray.m_ptex[9] + (double)this->m_rect.left;
        v38 = (__int64)((double)this->m_rect.top
                      + *(float *)&this->m_texarray.m_ptex[12]
                      + *(float *)&this->m_texarray.m_ptex[9]
                      - 1.0);
        *(_DWORD *)&this->m_canctrl = v38;
        this->m_state = (UIButton_UIBUTTON_STATE)(__int64)v37;
        v39 = (__int64)((double)(int)(__int64)v37 + *(float *)&this->m_texarray.m_ptex[3]);
        bottom = (double)this->m_rect.bottom;
        v41 = *(float *)&this->m_texarray.m_ptex[13] + *(float *)&this->m_texarray.m_ptex[9];
        v42 = v39;
        this->m_offsetx = v39;
        v43 = (__int64)(bottom - v41);
        v44 = *(_DWORD *)&this->m_caption[8];
        LODWORD(this->m_offsety) = v43;
        v45 = (gbTexture *)(*(_DWORD *)&this->m_caption[16] + ((int)v43 - v38) / 2 - v44 / 2 + v38);
        v46 = *(_DWORD *)&this->m_caption[4];
        this->m_texarray.m_ptex[0] = v45;
        v47 = *(_DWORD *)&this->m_caption[12] - v46 / 2 + v42;
        *(_DWORD *)&this->m_bBigFont = v47;
        this->m_texarray.m_ptex[1] = (gbTexture *)(v47 + v46);
        this->m_texarray.m_ptex[2] = (gbTexture *)((char *)v45 + v44);
      }
      else if ( LODWORD(v25) == 1 )
      {
        v26 = (double)this->m_rect.right;
        v27 = *(float *)&this->m_texarray.m_ptex[11] + *(float *)&this->m_texarray.m_ptex[9];
        v28 = (__int64)((double)this->m_rect.top + *(float *)&this->m_texarray.m_ptex[9] - 1.0);
        *(_DWORD *)&this->m_canctrl = v28;
        v29 = (__int64)(v26 - v27);
        this->m_offsetx = v29;
        v30 = (double)this->m_rect.bottom;
        v31 = (UIButton_UIBUTTON_STATE)(__int64)((double)(int)v29 - *(float *)&this->m_texarray.m_ptex[3]);
        this->m_state = v31;
        v32 = (__int64)(v30 - *(float *)&this->m_texarray.m_ptex[9]);
        v33 = *(_DWORD *)&this->m_caption[8];
        LODWORD(this->m_offsety) = v32;
        v34 = (gbTexture *)(*(_DWORD *)&this->m_caption[16] + ((int)v32 - v28) / 2 - v33 / 2 + v28);
        v35 = *(_DWORD *)&this->m_caption[4];
        this->m_texarray.m_ptex[0] = v34;
        v36 = *(_DWORD *)&this->m_caption[12] - v35 / 2 + *(_DWORD *)&v31;
        *(_DWORD *)&this->m_bBigFont = v36;
        this->m_texarray.m_ptex[1] = (gbTexture *)(v35 + v36);
        this->m_texarray.m_ptex[2] = (gbTexture *)((char *)v34 + v33);
      }
    }
    v48 = *(_DWORD *)&this->m_caption[20];
    if ( v48 )
    {
      if ( v48 == 1 )
      {
        this->m_caption[27] = this->m_caption[32];
        if ( this->m_texarrayInfo[2] )
        {
          v51[17] = (int)this->m_texarrayInfo[2];
          v51[33] = 1;
          ((TextureLibDataBase *)&this->m_rect)->SetLibFolder((char *)&this->m_rect);
        }
        else
        {
          crt_sub_00540070();
        }
        if ( this->m_disablepicInfo )
        {
          if ( LODWORD(this->m_ratiow) || !*(_DWORD *)&this->m_mouseoff )
          {
            v51[51] = (int)this->m_disablepicInfo;
            v51[67] = 1;
            crt_sub_00540DC0();
          }
          else
          {
            v50[17] = (int)this->m_disablepicInfo;
            v50[33] = 1;
            crt_sub_00540DC0();
          }
        }
        else
        {
          HIBYTE(this->m_texarrayInfo[1]) = this->m_caption[27];
          crt_sub_00540070();
        }
        if ( this->m_alignmode )
        {
          crt_sub_00540DC0();
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
          return;
        }
      }
    }
    else
    {
      if ( this->m_texarrayInfo[2] )
      {
        v50[0] = (int)this->m_texarrayInfo[2];
        v50[16] = 1;
        ((TextureLibDataBase *)v50)->SetLibFolder((char *)&this->m_rect);
      }
      if ( this->m_disablepicInfo )
      {
        if ( LODWORD(this->m_ratiow) || !*(_DWORD *)&this->m_mouseoff )
        {
          v51[34] = (int)this->m_disablepicInfo;
          v51[50] = 1;
          ((TextureLibDataBase *)&this->m_state)->SetLibFolder((char *)&this->m_state);
        }
        else
        {
          v51[0] = (int)this->m_disablepicInfo;
          v51[16] = 1;
          ((TextureLibDataBase *)v51)->SetLibFolder((char *)&this->m_state);
        }
      }
      else
      {
        crt_sub_00540070();
      }
      if ( this->m_alignmode )
      {
        v51[68] = this->m_alignmode;
        v51[84] = 1;
        ((TextureLibDataBase *)&this->m_bBigFont)->SetLibFolder(&this->m_bBigFont);
      }
    }
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  }
}

// 0x00440560
BOOL UIButton::Update(int nDelta, int nVal2)
{
  double v5; // st7
  double v6; // st7
  double v7; // st7
  __int64 v8; // rax
  int v9; // ecx
  char v10; // al
  __int64 v11; // rax
  int v12; // ecx

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( *(float *)&this->m_texarray.m_ptex[3] < (double)*(float *)&this->m_texarray.m_ptex[5] )
  {
    v5 = *(float *)&nDelta * 36.0 * *(float *)&this->m_texarray.m_ptex[4] + *(float *)&this->m_texarray.m_ptex[3];
    *(float *)&this->m_texarray.m_ptex[3] = v5;
    if ( v5 >= *(float *)&this->m_texarray.m_ptex[5] )
      this->m_texarray.m_ptex[3] = this->m_texarray.m_ptex[5];
LABEL_8:
    v6 = *(float *)&this->m_texarray.m_ptex[14] * *(float *)&this->m_texarray.m_ptex[3];
    LOBYTE(this->m_texarray.m_num) = 0;
    *(float *)&this->m_texarray.m_ptex[15] = v6;
    goto LABEL_13;
  }
  if ( *(float *)&this->m_texarray.m_ptex[3] > (double)*(float *)&this->m_texarray.m_ptex[5] )
  {
    v7 = *(float *)&this->m_texarray.m_ptex[3] - *(float *)&nDelta * 36.0 * *(float *)&this->m_texarray.m_ptex[4];
    *(float *)&this->m_texarray.m_ptex[3] = v7;
    if ( v7 <= *(float *)&this->m_texarray.m_ptex[5] )
      this->m_texarray.m_ptex[3] = this->m_texarray.m_ptex[5];
    goto LABEL_8;
  }
  LOBYTE(this->m_texarray.m_num) = 1;
LABEL_13:
  if ( *(_DWORD *)&this->m_caption[20] == 1 && this->m_caption[45] )
  {
    if ( this->m_caption[44] )
    {
      v8 = (__int64)(*(float *)&nDelta * 36.0 * *(float *)&this->m_caption[40] + (double)*(int *)&this->m_caption[32]);
      v9 = *(_DWORD *)&this->m_caption[28];
      *(_DWORD *)&this->m_caption[32] = v8;
      if ( (int)v8 >= v9 )
      {
        v10 = this->m_caption[46];
        *(_DWORD *)&this->m_caption[32] = v9;
        this->m_caption[44] = 0;
        if ( v10 )
        {
          this->m_caption[45] = 0;
          *(_DWORD *)&this->m_caption[32] = v9;
          this->m_caption[44] = 0;
          this->m_caption[46] = 0;
        }
      }
    }
    else
    {
      v11 = (__int64)((double)*(int *)&this->m_caption[32] - *(float *)&nDelta * 36.0 * *(float *)&this->m_caption[40]);
      v12 = *(_DWORD *)&this->m_caption[36];
      *(_DWORD *)&this->m_caption[32] = v11;
      if ( (int)v11 <= v12 )
      {
        *(_DWORD *)&this->m_caption[32] = v12;
        this->m_caption[44] = 1;
      }
    }
  }
  return ((UIListBox *)this)->Update(nDelta, nVal2);
}
