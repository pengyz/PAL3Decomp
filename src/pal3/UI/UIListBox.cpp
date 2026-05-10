#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/Parent_Data.h"
#include "pal3/gen/PtrArray.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_432680(...);
int sub_43DF70(...);
int sub_43F360(...);
int sub_43F520(...);
int sub_43F6D0(...);
int sub_4413C0(...);
int sub_442060(...);
int sub_5372D0(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Ui[];
extern char aUiCommonScroll[];
extern int dword_1894B78;
extern int dword_BFDA60;
extern void *off_56AD20;
extern void *off_56AD40;
extern int unk_D902F0;
extern int unk_D902F4;
extern int unk_D91780;

// 0x0043DCD0
UIListBox::UIListBox()
{
  ((UIWnd *)&this->_base)->UIWnd();
  *(_DWORD *)this->_base._pad_000 = &off_56AD20;
  *(_DWORD *)this->m_selcolor = 0;
  this->_base._pad_000;
}

// 0x0043DCF0
UIListBox::~UIListBox()
{
  ((UIWnd *)&Block->_base)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  (UIWnd *)Block;
}

// 0x0043DD60
int UIListBox::SetSelTexture(int id, int pRect, int a4, int a5, int a6, int a7)
{
  int v7; // edi
  gbTexture *v9; // eax

  v7 = a7;
  if ( a7 )
  {
    ((OpenBaseFile *)&a7)->OpenBaseFile();
    v9 = (gbTexture *)(*(int (**)(gbGfxManager *, int))(*(_DWORD *)dword_BFDA60->_pad_0000 + 8))(
                        dword_BFDA60,
                        v7);
    *(_DWORD *)this->m_selcolor = v9;
    if ( v9 )
      v9->LoadTexture(1);
    ((OpenNULLFile *)&a7)->OpenNULLFile();
  }
  return ((UIWnd *)&this->_base)->Create(id, &pRect, 0);
}

// 0x0043DDF0
int UIListBox::SetScroll()
{
  int result; // eax
  struct gbTextureArray v3; // [esp+4h] [ebp-44h] BYREF

  result = this->_base.m_bvisible;
  if ( result )
  {
    if ( *(_DWORD *)this->m_selcolor )
    {
      v3.pTexPt[0] = *(gbTexture **)this->m_selcolor;
      v3.nTex = 1;
      ((_TextureLib_Data *)this->_base.m_rect)->SetLibFolder((unsigned int *)this->_base.m_wndcolor, &v3, 0x114u, 0, COERCE_FLOAT(1));
    }
    return ((UIWnd *)&this->_base)->GetID();
  }
  return result;
}

// 0x0043DE40
int UIListBox::SetScrollPos()
{
  gbRefObject *v2; // ecx
  int result; // eax

  v2 = (gbRefObject *)*((_DWORD *)this + 17);
  if ( v2 )
  {
    v2->Release();
    *((_DWORD *)this + 17) = 0;
  }
  ((UIWnd *)this)->UpdateChildren();
  return result;
}

// 0x0043DE90
// attributes: thunk
int UIListBox::Destroy()
{
  return UIListBox::AddColumn();
}

// 0x0043DEA0
int UIListBox::AddColumn()
{
  unk_D902F4 = 1094713344;
  return 1094713344;
}

// 0x0043DEB0
// attributes: thunk
void UIListBox::AddRow()
{
  UIListBox::SetSubItem();
}

// 0x0043DEC0
void UIListBox::SetSubItem()
{
  unk_D902F0 = 12.0 + 12.0;
}

// 0x0043DED0
void * UIListBox::GetSubItemInfo()
{
  memset(this, 0, 0x48u);
  return this;
}

// 0x0043DEF0
int UIListBox::Render()
{
  UIListBox *v2; // ecx

  v2 = (UIListBox *)*this;
  if ( v2 )
    ((gbRefObject *)v2)->Release();
  memset(this, 0, 0x48u);
  return 0;
}

// 0x0043DF10
void UIListBox::CalHeightCount()
{
  ((PtrArray *)&this->_base.m_bfocus)->Clear();
}

// 0x0043DF20
void UIListBox::GetItemPos()
{
  sub_43DF70(this);
  sub_432680((void **)this + 16);
}

// 0x0043DFC0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char * UIListBox::UpdateKeyCtrl()
{
  char v3; // [esp+Bh] [ebp-11h]

  ((UIWnd *)&this->_base)->UIWnd();
  if ( gbColorQuad::ColorQuadFmt )
  {
    this->m_selcolor[2] = -6;
    this->m_selcolor[1] = 55;
    this->m_selcolor[0] = 55;
  }
  else
  {
    this->m_selcolor[0] = -6;
    this->m_selcolor[2] = 55;
    this->m_selcolor[1] = 55;
  }
  this->m_selcolor[3] = -56;
  ((UIWnd *)&this->m_scrollbar[3])->ctor_10F0();
  `eh vector constructor iterator'(
    &this->m_scrollbar[359],
    0x54u,
    8,
    (void (*)(void *))UIListBox::CalHeightCount,
    (void (*)(void *))UIListBox::GetItemPos);
  this->m_column[727] = -56;
  this->m_column[726] = -88;
  this->m_column[725] = -88;
  this->m_column[724] = -88;
  LOBYTE(this->m_fontsize) = v3;
  this->m_firstshow = 0;
  this->m_onsel = 0;
  this->m_locksel = 0;
  *(_DWORD *)&this->m_scrollbar[355] = 0;
  *(_DWORD *)&this->m_column[664] = 0;
  *(_DWORD *)&this->m_column[692] = 0;
  *(_DWORD *)&this->m_column[700] = 0;
  *(_DWORD *)&this->m_column[708] = 0;
  *(_DWORD *)&this->m_column[716] = 0;
  *(_DWORD *)&this->m_column[712] = 0;
  *(_DWORD *)&this->m_column[656] = 16;
  *(_DWORD *)&this->m_column[720] = 16;
  *(_DWORD *)&this->m_column[660] = 16;
  *(_DWORD *)&this->m_column[728] = 0;
  *(_DWORD *)&this->m_column[732] = 0;
  this->m_itemheight = 0;
  this->m_showGrayBk = 0;
  *(_DWORD *)&this->m_column[696] = 0;
  *(_DWORD *)&this->m_column[704] = 0;
  *(_DWORD *)this->_base._pad_000 = &off_56AD40;
  *(_DWORD *)&this->m_column[668] = -1;
  return this->_base._pad_000;
}

// 0x0043E100
UIWnd * UIListBox::DeleteAllItems(char a2)
{
  this->DeleteRow();
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return (UIWnd *)this;
}

// 0x0043E120
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIListBox::DeleteRow()
{
  *(_DWORD *)this->_base._pad_000 = &off_56AD40;
  ((UIListBox *)this)->GetItemCount();
  operator delete((void *)this->m_firstshow);
  this->m_firstshow = 0;
  this->m_onsel = 0;
  this->m_locksel = 0;
  `eh vector destructor iterator'(&this->m_scrollbar[359], 0x54u, 8, (void (*)(void *))UIListBox::GetItemPos);
  ((UIWnd *)&this->m_scrollbar[3])->ctor_11D0();
  ((UIWnd *)&this->_base)->_UIWnd();
}

// 0x0043E1C0
int UIListBox::CalScrollBarRange(
        UIListBox *this,
        int id,
        _DWORD *a3,
        int parent,
        LPCSTR lpString,
        int a6,
        char a7)
{
  const CHAR *v7; // edi
  int v9; // ebp
  Scene *v10; // eax
  gbTexture *v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  _DWORD *v15; // eax
  int (**v16)(char *, int); // edx
  _DWORD a2[4]; // [esp+20h] [ebp-1Ch] BYREF
  int v19; // [esp+38h] [ebp-4h]

  v7 = lpString;
  if ( lpString )
  {
    ((OpenBaseFile *)&lpString)->OpenBaseFile();
    v19 = 0;
    if ( a7 )
    {
      v9 = *(_DWORD *)dword_BFDA60->_pad_0000;
      v10 = ((_Texture_Info *)dword_1894B78)->_CalculateUV(v7);
      *(_DWORD *)&this->m_column[692] = (*(int (**)(gbGfxManager *, Scene *))(v9 + 8))(dword_BFDA60, v10);
      *(_DWORD *)&this->m_column[696] = ((Parent_Data *)dword_1894B78)->Parent_Data(v7);
    }
    else
    {
      *(_DWORD *)&this->m_column[692] = (*(int (**)(gbGfxManager *, const CHAR *))(*(_DWORD *)dword_BFDA60->_pad_0000
                                                                                            + 8))(
                                          dword_BFDA60,
                                          v7);
    }
    v11 = (gbTexture *)*(gbTexture **)&this->m_column[692];
    if ( v11 )
      v11->LoadTexture(1);
    v19 = -1;
    ((OpenNULLFile *)&lpString)->OpenNULLFile();
  }
  ((UIWnd *)&this->_base)->Create(id, a3, parent);
  v12 = *(_DWORD *)&this->m_column[720];
  this->m_hasKeyCtrl = 1;
  v13 = a3[2] - *a3;
  *(_DWORD *)&this->m_column[684] = v13;
  *(_DWORD *)&this->m_column[676] = v13 - v12;
  *(_DWORD *)&this->m_column[680] = 0;
  v14 = *(_DWORD *)&this->m_scrollbar[3];
  *(_DWORD *)&this->m_column[688] = a3[3] - a3[1];
  (*(void (**)(char *, int, char *, UIListBox *, char *, int, _DWORD))(v14 + 28))(
    &this->m_scrollbar[3],
    1,
    &this->m_column[676],
    this,
    aUiCommonScroll,
    1,
    0);
  sub_442060((int *)&this->m_scrollbar[3], 0);
  sub_43F520(this);
  v15 = ((UIWnd *)&this->m_scrollbar[3])->SetRect(a2);
  *(_DWORD *)&this->m_column[676] = *v15;
  *(_DWORD *)&this->m_column[680] = v15[1];
  *(_DWORD *)&this->m_column[684] = v15[2];
  v16 = *(int (***)(char *, int))&this->m_scrollbar[3];
  *(_DWORD *)&this->m_column[688] = v15[3];
  return (*v16)(&this->m_scrollbar[3], a6);
}

// 0x0043E330
void UIListBox::GetSel(int a2, int a3)
{
  int v3; // edi
  gbTexture *v5; // eax

  v3 = a2;
  if ( a2 )
  {
    ((OpenBaseFile *)&a2)->OpenBaseFile();
    v5 = (gbTexture *)(*(int (**)(gbGfxManager *, int))(*(_DWORD *)dword_BFDA60->_pad_0000 + 8))(
                        dword_BFDA60,
                        v3);
    *(_DWORD *)&this->m_column[700] = v5;
    if ( v5 )
      v5->LoadTexture(1);
    ((OpenNULLFile *)&a2)->OpenNULLFile();
  }
}

// 0x0043E3B0
int UIListBox::GetLockSel(int a2, _DWORD *a3, int a4, int a5, char a6)
{
  int v8; // ecx
  int v9; // edx

  if ( a2 )
    sub_4413C0((UIWnd **)&this->m_scrollbar[3], (struct gbVFileSystem *)a2, a6);
  *(_DWORD *)&this->m_column[676] = *a3;
  *(_DWORD *)&this->m_column[680] = a3[1];
  *(_DWORD *)&this->m_column[684] = a3[2];
  *(_DWORD *)&this->m_column[688] = a3[3];
  *(_DWORD *)&this->m_column[676] = *(_DWORD *)&this->m_column[684] - a4;
  ((UIWnd *)&this->m_scrollbar[3])->GetRect(&this->m_column[676]);
  v8 = *(_DWORD *)&this->m_scrollbar[327];
  v9 = a5 + *(_DWORD *)&this->m_scrollbar[311];
  *(_DWORD *)&this->m_scrollbar[159] = a5;
  *(_DWORD *)&this->m_scrollbar[319] = v9;
  *(_DWORD *)&this->m_scrollbar[335] = a5 + v8;
  *(_DWORD *)&this->m_column[720] = a4;
  return a5;
}

// 0x0043E440
int UIListBox::SetSel(int a2)
{
  int v3; // eax

  sub_43F520(this);
  v3 = a2;
  if ( a2 >= *(_DWORD *)&this->m_scrollbar[171] )
    v3 = *(_DWORD *)&this->m_scrollbar[171];
  if ( v3 <= *(_DWORD *)&this->m_scrollbar[167] )
    v3 = *(_DWORD *)&this->m_scrollbar[167];
  *(_DWORD *)&this->m_column[664] = v3;
  return sub_442060((int *)&this->m_scrollbar[3], v3);
}

// 0x0043E480
int UIListBox::SetItemHeight(int a2, int a3, int a4)
{
  int v6; // edi
  int Child; // eax
  UIWnd *m_pfather; // ecx
  UIWnd *v9; // ecx

  if ( a2 != 1005 )
    return a2->SendMessage(a3, a4);
  if ( this->m_itemheight )
  {
    v6 = *(_DWORD *)&this->m_column[664];
    *(_DWORD *)&this->m_column[664] = a4;
    Child = ((UIWnd *)&this->_base)->CreateChild();
    if ( Child == -1 )
    {
      *(_DWORD *)&this->m_column[664] = v6;
    }
    else if ( *(_DWORD *)(this->m_firstshow + 4 * Child) )
    {
      m_pfather = (UIWnd *)this->_base.m_pfather;
      if ( m_pfather )
        (*(void (**)(UIWnd *, int, unsigned int, int))(*(_DWORD *)m_pfather->_pad_000 + 24))(
          m_pfather,
          1006,
          this->_base.m_id,
          Child);
    }
  }
  else
  {
    *(_DWORD *)&this->m_column[664] = a4;
  }
  v9 = (UIWnd *)this->_base.m_pfather;
  if ( v9 )
    (*(void (**)(UIWnd *, int, _DWORD, _DWORD))(*(_DWORD *)v9->_pad_000 + 24))(v9, 1005, 0, 0);
  return 1;
}

// 0x0043E520
int UIListBox::GetItemCount()
{
  gbRefObject *v2; // ecx
  int result; // eax

  sub_43F360((int *)this);
  v2 = (gbRefObject *)*((_DWORD *)this + 286);
  *((_DWORD *)this + 108) = 0;
  if ( v2 )
  {
    v2->Release();
    *((_DWORD *)this + 286) = 0;
  }
  ((UIWnd *)this)->UpdateChildren();
  return result;
}

// 0x0043E560
int UIListBox::SetFirstShow(char *Source, int a3)
{
  int result; // eax

  strncpy(&this->m_scrollbar[84 * *(_DWORD *)&this->m_scrollbar[355] + 359], Source, 0x40u);
  *(_DWORD *)&this->m_column[84 * *(_DWORD *)&this->m_scrollbar[355] + 64] = a3;
  result = *(_DWORD *)&this->m_scrollbar[355] + 1;
  *(_DWORD *)&this->m_scrollbar[355] = result;
  return result;
}

// 0x0043E5C0
int UIListBox::SetItemOffset(char *Source, int a3)
{
  UIListBox *v4; // eax
  char *SubItemInfo; // edi
  gbTexture *v6; // eax
  int v7; // ebp
  int v8; // ebx
  PtrArray *v9; // edi
  UIListBox *v10; // eax
  void *v11; // eax
  _DWORD *m_onsel; // ecx
  int m_firstshow; // eax
  int Child; // eax
  UIWnd *m_pfather; // ecx
  int v17; // [esp+10h] [ebp-814h] BYREF
  OpenBaseFile v18; // [esp+14h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+18h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+418h] [ebp-40Ch] BYREF
  int v21; // [esp+820h] [ebp-4h]

  v4 = (UIListBox *)operator new(0x48u);
  if ( !v4 || (SubItemInfo = (char *)v4->GetSubItemInfo()) == 0 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Ui, 260),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( a3 )
  {
    ((OpenBaseFile *)&v18)->OpenBaseFile();
    v21 = 0;
    v6 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)dword_BFDA60->_pad_0000 + 8))(
                        dword_BFDA60,
                        Source);
    *(_DWORD *)SubItemInfo = v6;
    if ( v6 )
      v6->LoadTexture(1);
    v21 = -1;
    ((OpenNULLFile *)&v18)->OpenNULLFile();
  }
  else
  {
    strncpy(SubItemInfo + 4, Source, 0x40u);
    *((_DWORD *)SubItemInfo + 17) = *(_DWORD *)this->_base.m_fontcolor;
  }
  v7 = *(_DWORD *)&this->m_column[52];
  ((PtrArray *)&this->m_column[48])->SetAt(v7, (int)SubItemInfo);
  v8 = 1;
  if ( *(int *)&this->m_scrollbar[355] > 1 )
  {
    v9 = (PtrArray *)&this->m_column[132];
    do
    {
      v10 = (UIListBox *)operator new(0x48u);
      if ( !v10 || (v11 = v10->GetSubItemInfo()) == 0 )
      {
        qmemcpy(
          pExceptionObject,
          ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Ui, 282),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      v9->SetAt(v9->m_nSize, (int)v11);
      ++v8;
      v9 = (PtrArray *)((char *)v9 + 84);
    }
    while ( v8 < *(_DWORD *)&this->m_scrollbar[355] );
  }
  sub_43F520(this);
  m_onsel = (_DWORD *)this->m_onsel;
  v17 = 1;
  sub_5372D0((int)&this->m_fontsize, m_onsel, 1u, &v17);
  m_firstshow = this->m_firstshow;
  if ( m_firstshow )
  {
    if ( (this->m_onsel - m_firstshow) >> 2 )
    {
      if ( *(_DWORD *)&this->m_column[668] == -1 )
      {
        sub_43F6D0(this, 0);
        if ( *(_DWORD *)&this->m_column[668] != -1 )
        {
          Child = ((UIWnd *)&this->_base)->CreateChild();
          m_pfather = (UIWnd *)this->_base.m_pfather;
          if ( m_pfather )
            (*(void (**)(UIWnd *, int, unsigned int, int))(*(_DWORD *)m_pfather->_pad_000 + 24))(
              m_pfather,
              1006,
              this->_base.m_id,
              Child);
        }
      }
    }
  }
  return v7;
}

// 0x0043E7D0
struct gbVFileSystem * UIListBox::SetMouseMoveSel(int a2, int a3, char *Source, int a5)
{
  int v5; // esi
  gbTexture *v6; // eax

  if ( a3 < 0 || a3 >= *(_DWORD *)&this->m_column[84 * a2 + 52] )
    v5 = 0;
  else
    v5 = *(_DWORD *)(*(_DWORD *)&this->m_column[84 * a2 + 48] + 4 * a3);
  if ( !a5 )
    return (struct gbVFileSystem *)strncpy((char *)(v5 + 4), Source, 0x40u);
  ((OpenBaseFile *)&a2)->OpenBaseFile();
  v6 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)dword_BFDA60->_pad_0000 + 8))(
                      dword_BFDA60,
                      Source);
  *(_DWORD *)v5 = v6;
  if ( v6 )
    v6->LoadTexture(1);
  return ((OpenNULLFile *)&a2)->OpenNULLFile();
}

// 0x0043E8A0
int UIListBox::EnableRow()
{
  int result; // eax
  unsigned int *v3; // eax
  int v4; // ebp
  char *v5; // eax
  int v6; // ebx
  int v7; // edi
  gbTexture **v8; // ecx
  int v9; // eax
  bool v10; // cc
  int Child; // eax
  int m_itemheight; // edx
  bool v13; // cl
  int v14; // eax
  int v15; // ecx
  int v16; // ebp
  int v17; // ebx
  int v18; // ecx
  int v19; // eax
  int v20; // ebx
  int v21; // edi
  int v22; // edx
  int v23; // edx
  int v24; // ecx
  int v25; // edi
  int v26; // edi
  int v27; // [esp-24h] [ebp-88h]
  int v28; // [esp-1Ch] [ebp-80h]
  char *v29; // [esp+4h] [ebp-60h]
  int v30; // [esp+8h] [ebp-5Ch]
  int v31; // [esp+Ch] [ebp-58h]
  int v32[3]; // [esp+10h] [ebp-54h] BYREF
  int v33; // [esp+1Ch] [ebp-48h]
  struct gbTextureArray v34; // [esp+20h] [ebp-44h] BYREF

  result = this->_base.m_bvisible;
  if ( result )
  {
    if ( *(_DWORD *)&this->m_column[692] )
    {
      v34.pTexPt[0] = *(gbTexture **)&this->m_column[692];
      v3 = (unsigned int *)*(unsigned int **)&this->m_column[696];
      v34.nTex = 1;
      ((_TextureLib_Data *)this->_base.m_rect)->SetLibFolder((unsigned int *)this->_base.m_wndcolor, &v34, 0x114u, v3, COERCE_FLOAT(1));
    }
    else if ( this->m_showGrayBk )
    {
      ((_TextureLib_Data *)*(_DWORD *)this->_base.m_rect)->~_TextureLib_Data(*(_DWORD *)&this->_base.m_rect[4], *(_DWORD *)&this->_base.m_rect[8], *(_DWORD *)&this->_base.m_rect[12], (float *)&unk_D91780);
    }
    v4 = *(_DWORD *)&this->m_column[728] + *(_DWORD *)this->_base.m_rect + 8;
    v30 = this->SetDefaultSel();
    v31 = 0;
    if ( *(int *)&this->m_scrollbar[355] > 0 )
    {
      v5 = (char *)&this->m_column[52];
      v29 = (char *)&this->m_column[52];
      do
      {
        v6 = *(_DWORD *)&this->m_column[664];
        v7 = *(_DWORD *)&this->_base.m_rect[4] + *(_DWORD *)&this->m_column[732] + 8;
        if ( v6 < v6 + v30 )
        {
          do
          {
            if ( v6 >= *(_DWORD *)v5 )
              break;
            v8 = v6 < 0 ? 0 : *(gbTexture ***)(*((_DWORD *)v5 - 1) + 4 * v6);
            if ( *v8 )
            {
              v34.pTexPt[0] = *v8;
              v32[2] = v4 + 32;
              v33 = v7 + 32;
              v32[0] = v4;
              v32[1] = v7;
              v34.nTex = 1;
              v32->SetLibFolder((unsigned int *)this->_base.m_wndcolor, &v34, 0x114u, 0, COERCE_FLOAT(1));
            }
            else if ( *(_DWORD *)(this->m_firstshow + 4 * v6) )
            {
              v9 = v6 < 0 || v6 >= *(_DWORD *)&this->m_column[52]
                 ? 0
                 : *(_DWORD *)(*(_DWORD *)&this->m_column[48] + 4 * v6);
              UIRenderQuad(v4, v7, (int)(v8 + 1), (_BYTE *)(v9 + 68), *(_DWORD *)&this->m_column[660]);
            }
            else
            {
              UIRenderQuad(v4, v7, (int)(v8 + 1), &unk_D91780, *(_DWORD *)&this->m_column[660]);
            }
            v7 += *(_DWORD *)&this->m_column[656];
            ++v6;
            v5 = v29;
          }
          while ( v6 < v30 + *(_DWORD *)&this->m_column[664] );
        }
        v4 += *((_DWORD *)v5 + 3);
        v5 += 84;
        v10 = ++v31 < *(_DWORD *)&this->m_scrollbar[355];
        v29 = v5;
      }
      while ( v10 );
    }
    Child = ((UIWnd *)&this->_base)->CreateChild();
    m_itemheight = this->m_itemheight;
    if ( m_itemheight )
    {
      v13 = *(_DWORD *)&this->m_column[668] != -1;
      if ( *(_DWORD *)&this->m_column[668] == -1 || !*(_DWORD *)(this->m_firstshow + 4 * Child) )
        return ((UIWnd *)&this->_base)->GetID();
    }
    else
    {
      v13 = *(_DWORD *)&this->m_column[672] != -1;
    }
    if ( v13 )
    {
      v14 = *(_DWORD *)this->_base.m_rect;
      v15 = *(_DWORD *)&this->_base.m_rect[4];
      v16 = *(_DWORD *)&this->m_column[732];
      v17 = *(_DWORD *)&this->_base.m_rect[8];
      v33 = *(_DWORD *)&this->_base.m_rect[12];
      v18 = v16 + v15;
      v19 = *(_DWORD *)&this->m_column[728] + v14 + 4;
      v20 = -2 - *(_DWORD *)&this->m_column[720] + v17;
      v21 = *(_DWORD *)&this->m_column[656];
      v22 = m_itemheight
          ? *(_DWORD *)&this->m_column[668]
          : *(_DWORD *)&this->m_column[672] - *(_DWORD *)&this->m_column[664];
      v23 = v18 + v21 * v22 + 8;
      v24 = v21 + v23 - 2;
      v25 = *(_DWORD *)&this->_base.m_rect[12];
      if ( v24 > v25 )
        v24 = *(_DWORD *)&this->_base.m_rect[12];
      if ( v23 >= *(_DWORD *)&this->_base.m_rect[4] && v24 <= v25 )
      {
        if ( *(_DWORD *)&this->m_column[700] )
        {
          v34.pTexPt[0] = *(gbTexture **)&this->m_column[700];
          v26 = *(_DWORD *)&this->m_column[708];
          v28 = v20 + *(_DWORD *)&this->m_column[716];
          v27 = v19 + *(_DWORD *)&this->m_column[712];
          v34.nTex = 1;
          UIDestorySystem(v27, v23 + v26, v28, v26 + v24, (int *)&this->m_column[724], &v34);
          return ((UIWnd *)&this->_base)->GetID();
        }
        v19->~_TextureLib_Data(v23, v20, v24, (float *)this->m_selcolor);
      }
    }
    return ((UIWnd *)&this->_base)->GetID();
  }
  return result;
}

// 0x0043EBA0
int UIListBox::SetDefaultSel()
{
  return (*(_DWORD *)&this->_base.m_rect[12] - *(_DWORD *)&this->_base.m_rect[4]) / *(_DWORD *)&this->m_column[656];
}
