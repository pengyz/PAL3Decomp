#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIListBox.h"

// Forward declarations for unnamed functions
int _todo_4A9870(...);
void sub_4422E0(void *_this); // from annotations
int sub_445AA0(void); // from annotations
int sub_445DB0(void *a2); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_445FE0(void *a2); // from annotations
int sub_4A13E0(...);

int crt_sub_00540070(void); // from annotations
int crt_sub_00540FD0(void); // from annotations
void GetGridOffset(void *_this, int *pOut, int index); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];
extern char byte_D92785;
extern int dword_56B4DC[];
extern int dword_56B4F0[];
extern int dword_56B540[];
extern int dword_56B554[];
extern int dword_56B568[];
extern int dword_56B57C[];
extern int dword_56B590[];
extern int dword_56B5A4[];
extern int dword_56B5B8[];
extern int dword_DC843C;
extern int dword_DC913C;
extern int dword_DCCC3C;
extern int dword_DCEA3C;
extern int dword_DD423C;
extern const char * off_56B504;
extern const char * off_56B518;
extern const char * off_56B52C;
extern _SPropValue * off_5B46C0;
extern void * off_5B46C4;
extern void * off_5CF1F0;
extern void * off_5E92A0;
extern TextureLibDataBase stru_1894B78;
extern RoleSystem stru_C059A0;
extern int unk_D902F0;
extern int unk_D902F4;

// 0x00431CD0
void UIListBox::RefreshSelection()
{
  ((PalScript *)this)->CleanupInstances();
  ((UIListBox *)&this->m_wndcolor)->ReleaseVtable();
}

// 0x00432680
int UIListBox::ReleaseVtable()
{
  int result; // eax

// [VFTABLE] result = (int)this->__vftable;
// [VFTABLE] if ( this->__vftable )
  {
// [VFTABLE] free(this->__vftable);
// [VFTABLE] this->__vftable = 0;
  }
  return result;
}

// 0x0043DCD0
UIListBox::UIListBox()
{
  sub_445AA0();
  this->m_selcolor.Color = 0;
  (int *)this;
}

// 0x0043DD10
void UIListBox::_UIListBox()
{
  UIListBox *v2; // [esp+0x0] [ebp-0x14]

  ((CCBRoleState *)this)->Destroy(v2, (int)this);
// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x0043DD60
void UIListBox::SetSelTexture(int id, int pRect, int nVal, int nVal2, int nVal3, int nVal4)
{
  int v7; // edi
  gbTexture *v9; // eax

  v7 = nVal4;
  if ( nVal4 )
  {
    v9 = (gbTexture *)(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr + 8))(gfxMgr, v7);
    this->m_selcolor.Color = (unsigned int)v9;
    if ( v9 )
      ((gbTexture *)v9)->LoadTexture(1);
  }
  ((PalScript *)this)->Create(id, (tagRECT *)&pRect, 0);
}

// 0x0043DE90
// attributes: thunk
void UIListBox::Destroy()
{

}

// 0x0043DEA0
void UIListBox::AddColumn()
{
  unk_D902F4 = 1094713344;
}

// 0x0043DEB0
// attributes: thunk
void UIListBox::AddRow()
{

}

// 0x0043DEC0
void UIListBox::SetSubItem()
{
  unk_D902F0 = 12.0 + 12.0;
}

// 0x0043DED0
UIListBox * UIListBox::GetSubItemInfo()
{
  memset(this, 0, 0x48u);
  return this;
}

// 0x0043DEF0
void UIListBox::Render()
{
  gbRefObject *vftable; // ecx

// [VFTABLE] vftable = (gbRefObject *)this->__vftable;
  if ( vftable )
    ((gbRefObject *)vftable)->Release();
  memset(this, 0, 0x48u);
}

// 0x0043DF10
void UIListBox::CalHeightCount()
{
  ((PtrArray *)&this->m_bfocus)->Clear();
}

// 0x0043DF20
void UIListBox::GetItemPos()
{

  ((UIListBox *)&this->m_bfocus)->ReleaseVtable();
}

// 0x0043DF70
void UIListBox::GetItemAt()
{
  int i; // esi
  int m_bfocus; // eax
  void *v4; // ebx

  for ( i = 0; i < (int)this->m_selcolor.Color; ++i )
  {
    if ( i >= 0 && i < (int)this->m_selcolor.Color )
    {
      m_bfocus = this->m_bfocus;
      v4 = *(void **)(m_bfocus + 4 * i);
      if ( v4 )
      {
        ((UIListBox *)*(UIListBox **)(m_bfocus + 4 * i))->Render();
        operator delete(v4);
      }
    }
  }
  ((String *)&this->m_bfocus)->Assign(0, -1);
}

// 0x0043DFC0
UIListBox * UIListBox::UpdateKeyCtrl()
{
  char v3; // [esp+0xB] [ebp-0x11]

  sub_445AA0();
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(this->m_selcolor.Color) = -6;
    BYTE1(this->m_selcolor.Color) = 55;
    LOBYTE(this->m_selcolor.Color) = 55;
  }
  else
  {
    LOBYTE(this->m_selcolor.Color) = -6;
    BYTE2(this->m_selcolor.Color) = 55;
    BYTE1(this->m_selcolor.Color) = 55;
  }
  HIBYTE(this->m_selcolor.Color) = -56;
  ((UIMap *)&this->m_scrollbar)->ctor();
  HIBYTE(this->m_seltexcolor.Color) = -56;
  BYTE2(this->m_seltexcolor.Color) = -88;
  BYTE1(this->m_seltexcolor.Color) = -88;
  LOBYTE(this->m_seltexcolor.Color) = -88;
  this->m_rowenable[0] = v3;
  *(_DWORD *)&this->m_rowenable[4] = 0;
  *(_DWORD *)&this->m_rowenable[8] = 0;
  *(_DWORD *)&this->m_rowenable[12] = 0;
  this->m_numcol = 0;
  this->m_firstshow = 0;
  this->m_pbkpic = 0;
  this->m_selpic = 0;
  this->m_seloffset = 0;
  this->m_seloffsetR = 0;
  this->m_seloffsetL = 0;
  this->m_itemheight = 16;
  this->m_scrollW = 16;
  this->m_fontsize = 16;
  this->m_itemoffset.x = 0;
  this->m_itemoffset.y = 0;
  this->m_movesel = 0;
  this->m_showGrayBk = 0;
  this->m_pbkpicInfo = 0;
  this->m_selpicInfo = 0;
  this->m_onsel = -1;
  return this;
}

// 0x0043E120
void UIListBox::DeleteRow()
{

  operator delete(*(void **)&this->m_rowenable[4]);
  *(_DWORD *)&this->m_rowenable[4] = 0;
  *(_DWORD *)&this->m_rowenable[8] = 0;
  *(_DWORD *)&this->m_rowenable[12] = 0;
  ((UIMap *)&this->m_scrollbar)->ctor_11D0();
// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x0043E1C0
void UIListBox::CalScrollBarRange(
        
        int id,
        int *p_DWORD,
        int parent,
        LPCSTR lpString,
        int nVal,
        char pData)
{
  const CHAR *v7; // edi
  int v9; // ebp
  CHAR *v10; // eax
  gbTexture *m_pbkpic; // ecx
  int m_scrollW; // ecx
  LONG v13; // eax
  void *vftable; // eax
  LONG *v15; // eax
  void *v16; // edx
  _BYTE a2[16]; // [esp+0x20] [ebp-0x1C] BYREF
  int v18; // [esp+0x38] [ebp-0x4]

  v7 = lpString;
  if ( lpString )
  {
    v18 = 0;
    if ( pData )
    {
      v9 = *(_DWORD *)gfxMgr;
      v10 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v7);
      this->m_pbkpic = (gbTexture *)(*(int ( **)(gbGfxManager *, CHAR *))(v9 + 8))(gfxMgr, v10);
      this->m_pbkpicInfo = (_PlugInfo *)((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v7);
    }
    else
    {
      this->m_pbkpic = (gbTexture *)(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(
                                      gfxMgr,
                                      v7);
    }
    m_pbkpic = this->m_pbkpic;
    if ( m_pbkpic )
      ((gbTexture *)m_pbkpic)->LoadTexture(1);
    v18 = -1;
  }
  ((PalScript *)this)->Create(id, (tagRECT *)p_DWORD, parent);
  m_scrollW = this->m_scrollW;
  this->m_hasKeyCtrl = 1;
  v13 = p_DWORD[2] - *p_DWORD;
  this->m_scrollRc.right = v13;
  this->m_scrollRc.left = v13 - m_scrollW;
  this->m_scrollRc.top = 0;
// [VFTABLE] vftable = this->m_scrollbar.__vftable;
  this->m_scrollRc.bottom = p_DWORD[3] - p_DWORD[1];
  ((void ( *)(UIScrollBar *, int, tagRECT *, UIListBox *, char *, int, _DWORD))vftable[1].ShowWindow)(
    &this->m_scrollbar,
    1,
    &this->m_scrollRc,
    this,
    "UI\\common\\scrollbar",
    1,
    0);
  ((UIScene *)&this->m_scrollbar)->SetFirstShow();

  v15 = (LONG *)sub_445FE0(a2);
  this->m_scrollRc.left = *v15;
  this->m_scrollRc.top = v15[1];
  this->m_scrollRc.right = v15[2];
// [VFTABLE] v16 = this->m_scrollbar.__vftable;
  this->m_scrollRc.bottom = v15[3];
  ((void ( *)(UIScrollBar *, int))v16->ShowWindow)(&this->m_scrollbar, nVal);
}

// 0x0043E330
void UIListBox::GetSel(int nVal, int nVal2)
{
  int v3; // edi
  gbTexture *v5; // eax

  v3 = nVal;
  if ( nVal )
  {
    v5 = (gbTexture *)(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr + 8))(gfxMgr, v3);
    this->m_selpic = v5;
    if ( v5 )
      ((gbTexture *)v5)->LoadTexture(1);
  }
}

// 0x0043E3B0
int UIListBox::GetLockSel(int nVal, int *p_DWORD, int nVal2, int nVal3, char pData)
{
  LONG top; // ecx
  LONG v9; // edx

  if ( nVal )
    ((CCBUI *)&this->m_scrollbar)->LoadTextureSequence((gbVFileSystem *)nVal, pData);
  this->m_scrollRc.left = *p_DWORD;
  this->m_scrollRc.top = p_DWORD[1];
  this->m_scrollRc.right = p_DWORD[2];
  this->m_scrollRc.bottom = p_DWORD[3];
  this->m_scrollRc.left = this->m_scrollRc.right - nVal2;
  sub_445FA0(&this->m_scrollbar);
  top = this->m_scrollbar.m_btnrect[1].top;
  v9 = nVal3 + this->m_scrollbar.m_btnrect[0].top;
  this->m_scrollbar.m_btnH = nVal3;
  this->m_scrollbar.m_btnrect[0].bottom = v9;
  this->m_scrollbar.m_btnrect[1].bottom = nVal3 + top;
  this->m_scrollW = nVal2;
  return nVal3;
}

// 0x0043E440
void UIListBox::SetSel(int sel)
{
  int m_max; // eax

  m_max = sel;
  if ( sel >= this->m_scrollbar.m_max )
    m_max = this->m_scrollbar.m_max;
  if ( m_max <= this->m_scrollbar.m_min )
    m_max = this->m_scrollbar.m_min;
  this->m_firstshow = m_max;
  ((UIScene *)&this->m_scrollbar)->SetFirstShow();
}

// 0x0043E480
int UIListBox::OnMessage(int height, int nVal, int nVal2)
{
  int m_firstshow; // edi
  int Child; // eax
  UIWnd *m_pfather; // ecx
  UIWnd *v9; // ecx

  if ( height != 1005 )
    return ((PalScript *)this)->OnMessage(height, nVal, nVal2);
  if ( this->m_movesel )
  {
    m_firstshow = this->m_firstshow;
    this->m_firstshow = nVal2;
    Child = ((NPC *)this)->CreateChild();
    if ( Child == -1 )
    {
      this->m_firstshow = m_firstshow;
    }
    else if ( *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * Child) )
    {
      m_pfather = this->m_pfather;
      if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1006,
// [VFTABLE]   this->m_id,
// [VFTABLE]   Child);
    }
  }
  else
  {
    this->m_firstshow = nVal2;
  }
  v9 = this->m_pfather;
  if ( v9 )
// [VFTABLE] ((void ( *)(UIWnd *, int, _DWORD, _DWORD))v9->__vftable->OnMessage)(v9, 1005, 0, 0);
  return 1;
}

// 0x0043E520
void UIListBox::Destroy_e520()
{
  gbRefObject *m_pbkpic; // ecx

  m_pbkpic = (gbRefObject *)this->m_pbkpic;
  this->m_numcol = 0;
  if ( m_pbkpic )
  {
    ((gbRefObject *)m_pbkpic)->Release();
    this->m_pbkpic = 0;
  }
// [VFTABLE] ((UIWnd *)&this->__vftable)->HideAll();
}

// 0x0043E560
int UIListBox::SetFirstShow(int nVal, int nOffset)
{
  int result; // eax

  strncpy(this->m_column[this->m_numcol].head, (const char *)nVal, 0x40u);
  this->m_column[this->m_numcol].width = nOffset;
  result = this->m_numcol + 1;
  this->m_numcol = result;
  return result;
}

// 0x0043E5C0
int UIListBox::SetItemOffset(char *Source, int y)
{
  UIListBox *v4; // eax
  UIListBox *SubItemInfo; // edi
  gbTexture *v6; // eax
  int capacity; // ebp
  int v8; // ebx
  PtrArray *p_items; // edi
  UIListBox *v10; // eax
  UIListBox *v11; // eax
  int *v12; // ecx
  int v13; // eax
  int Child; // eax
  UIWnd *m_pfather; // ecx
  int p_DWORD2; // [esp+0x10] [ebp-0x814] BYREF
  OpenBaseFile v18; // [esp+0x14] [ebp-0x810] BYREF
  char pExceptionObject[1024]; // [esp+0x18] [ebp-0x80C] BYREF
  char ArgList[1024]; // [esp+0x418] [ebp-0x40C] BYREF
  int v21; // [esp+0x820] [ebp-0x4]

  v4 = (UIListBox *)operator new(0x48u);
  if ( !v4 || (SubItemInfo = ((UIListBox *)v4)->GetSubItemInfo()) == 0 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(&path[164], "D:\\Project\\PAL3\\UI\\UIListBox.cpp", 260),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( y )
  {
    v21 = 0;
    v6 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, Source);
// [VFTABLE] SubItemInfo->__vftable = (vtbl_0056AE2C *)v6;
    if ( v6 )
      ((gbTexture *)v6)->LoadTexture(1);
    v21 = -1;
  }
  else
  {
    strncpy((char *)&SubItemInfo->m_fontcolor, Source, 0x40u);
    SubItemInfo->m_selcolor.Color = this->m_fontcolor.Color;
  }
  capacity = this->m_column[0].items.capacity;
  ((PtrArray *)&this->m_column[0].items)->SetAt(capacity, (int)SubItemInfo);
  v8 = 1;
  if ( this->m_numcol > 1 )
  {
    p_items = &this->m_column[1].items;
    do
    {
      v10 = (UIListBox *)operator new(0x48u);
      if ( !v10 || (v11 = ((UIListBox *)v10)->GetSubItemInfo()) == 0 )
      {
        qmemcpy(
          pExceptionObject,
          ((Logger *)ArgList)->FormatException(&path[164], "D:\\Project\\PAL3\\UI\\UIListBox.cpp", 282),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      ((PtrArray *)p_items)->SetAt(p_items->capacity, (int)v11);
      ++v8;
      p_items = (PtrArray *)((char *)p_items + 84);
    }
    while ( v8 < this->m_numcol );
  }

  v12 = *(int **)&this->m_rowenable[8];
  p_DWORD2 = 1;
  ((Actor *)this->m_rowenable)->LoadActionSequence(v12, 1u, &p_DWORD2);
  v13 = *(_DWORD *)&this->m_rowenable[4];
  if ( v13 )
  {
    if ( (*(_DWORD *)&this->m_rowenable[8] - v13) >> 2 )
    {
      if ( this->m_onsel == -1 )
      {
        this->SetFirstShow(0);
        if ( this->m_onsel != -1 )
        {
          Child = ((NPC *)this)->CreateChild();
          m_pfather = this->m_pfather;
          if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1006,
// [VFTABLE]   this->m_id,
// [VFTABLE]   Child);
        }
      }
    }
  }
  return capacity;
}

// 0x0043E7D0
gbVFileSystem * UIListBox::SetMouseMoveSel(int movesel, int nVal, char *Source, int nVal2)
{
  int v5; // esi
  gbTexture *v6; // eax
  gbVFileSystem *result; // eax

  if ( nVal < 0 || nVal >= this->m_column[movesel].items.capacity )
    v5 = 0;
  else
    v5 = *(_DWORD *)&this->m_column[movesel].items.m_pData[4 * nVal];
  if ( !nVal2 )
    return (gbVFileSystem *)strncpy((char *)(v5 + 4), Source, 0x40u);
  v6 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, Source);
  *(_DWORD *)v5 = v6;
  if ( v6 )
    ((gbTexture *)v6)->LoadTexture(1);
  return result;
}

// 0x0043E8A0
int UIListBox::Render_e8a0()
{
  int result; // eax
  int v3; // ebp
  int v4; // eax
  int *p_capacity; // eax
  int m_firstshow; // ebx
  int v7; // edi
  int *v8; // ecx
  bool v9; // cc
  int Child; // eax
  int m_movesel; // edx
  bool v12; // cl
  LONG top; // ecx
  LONG y; // ebp
  int v15; // ecx
  int m_itemheight; // edi
  int v17; // edx
  LONG v18; // edx
  LONG v19; // ecx
  LONG v20; // edi
  int *v21; // [esp+0x4] [ebp-0x60]
  int v22; // [esp+0x8] [ebp-0x5C]
  int v23; // [esp+0xC] [ebp-0x58]
  char pszFolder[4]; // [esp+0x10] [ebp-0x54] BYREF
  int v25; // [esp+0x14] [ebp-0x50]
  int v26; // [esp+0x18] [ebp-0x4C]
  LONG bottom; // [esp+0x1C] [ebp-0x48]
  int m_pbkpic; // [esp+0x20] [ebp-0x44] BYREF
  int v29; // [esp+0x60] [ebp-0x4]

  result = this->m_bvisible;
  if ( result )
  {
    if ( this->m_pbkpic )
    {
      m_pbkpic = (int)this->m_pbkpic;
      v29 = 1;
      ((TextureLibDataBase *)&m_pbkpic)->SetLibFolder((char *)&this->m_rect);
    }
    else if ( this->m_showGrayBk )
    {
      crt_sub_00540070();
    }
    v3 = this->m_itemoffset.x + this->m_rect.left + 8;

    v22 = v4;
    v23 = 0;
    if ( this->m_numcol > 0 )
    {
      p_capacity = &this->m_column[0].items.capacity;
      v21 = &this->m_column[0].items.capacity;
      do
      {
        m_firstshow = this->m_firstshow;
        v7 = this->m_rect.top + this->m_itemoffset.y + 8;
        if ( m_firstshow < m_firstshow + v22 )
        {
          do
          {
            if ( m_firstshow >= *p_capacity )
              break;
            v8 = m_firstshow < 0 ? 0 : *(int **)(*(p_capacity - 1) + 4 * m_firstshow);
            if ( *v8 )
            {
              m_pbkpic = *v8;
              v26 = v3 + 32;
              bottom = v7 + 32;
              *(_DWORD *)pszFolder = v3;
              v25 = v7;
              v29 = 1;
              ((TextureLibDataBase *)&this->m_wndcolor)->SetLibFolder(pszFolder);
            }
            else
            {
              crt_sub_00540FD0();
            }
            v7 += this->m_itemheight;
            ++m_firstshow;
            p_capacity = v21;
          }
          while ( m_firstshow < v22 + this->m_firstshow );
        }
        v3 += p_capacity[3];
        p_capacity += 21;
        v9 = ++v23 < this->m_numcol;
        v21 = p_capacity;
      }
      while ( v9 );
    }
    Child = ((NPC *)this)->CreateChild();
    m_movesel = this->m_movesel;
    if ( m_movesel )
    {
      v12 = this->m_onsel != -1;
      if ( this->m_onsel == -1 || !*(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * Child) )
      {
LABEL_34:
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
        return result;
      }
    }
    else
    {
      v12 = this->m_locksel != -1;
    }
    if ( v12 )
    {
      top = this->m_rect.top;
      y = this->m_itemoffset.y;
      bottom = this->m_rect.bottom;
      v15 = y + top;
      m_itemheight = this->m_itemheight;
      v17 = m_movesel ? this->m_onsel : this->m_locksel - this->m_firstshow;
      v18 = v15 + m_itemheight * v17 + 8;
      v19 = m_itemheight + v18 - 2;
      v20 = this->m_rect.bottom;
      if ( v19 > v20 )
        v19 = this->m_rect.bottom;
      if ( v18 >= this->m_rect.top && v19 <= v20 )
      {
        if ( this->m_selpic )
        {
          m_pbkpic = (int)this->m_selpic;
          v29 = 1;
          UIDestorySystem();
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
          return result;
        }
        crt_sub_00540070();
      }
    }
    goto LABEL_34;
  }
  return result;
}

// 0x0043EBA0
void UIListBox::SetDefaultSel()
{
  ;
}

// 0x0043EBE0
BOOL UIListBox::Update(int nVal, int nVal2)
{
  BOOL result; // eax
  LONG right; // ecx
  int m_scrollW; // ebx
  LONG left; // eax
  LONG bottom; // edx
  BOOL v9; // ebp
  int capacity; // ecx
  int m_onsel; // edi
  int v12; // ebx
  int v13; // eax
  int m_firstshow; // ecx
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int Child; // eax
  UIWnd *m_pfather; // ecx
  int m_locksel; // eax
  UIWnd *v21; // ecx
  void *vftable; // edx
  int v23; // edi
  int v24; // eax
  int v25; // ecx
  int v26; // eax
  int v27; // edx
  int v28; // ecx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  UIWnd *v32; // ecx
  int v33; // edi
  int v34; // eax
  int v35; // ecx
  int v36; // eax
  int v37; // edx
  int v38; // ecx
  int v39; // eax
  int v40; // eax
  int v41; // eax
  UIWnd *v42; // ecx
  UIWnd *v43; // ecx
  UIWnd *v44; // ecx
  POINT pt; // [esp+0x18] [ebp-0x18]
  RECT rc; // [esp+0x20] [ebp-0x10] BYREF

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( !nVal2 || this->m_numcol <= 0 )
    return nVal2 == 0;
  result = this->Update(nVal, nVal2);
  if ( result )
    return result;
  ((GRPinput *)&g_Input)->GetCursorPos();
  right = this->m_rect.right;
  m_scrollW = this->m_scrollW;
  left = this->m_rect.left;
  rc.top = this->m_rect.top;
  bottom = this->m_rect.bottom;
  rc.left = left;
  rc.right = right - m_scrollW;
  rc.bottom = bottom;
  v9 = PtInRect(&rc, pt);
  if ( this->m_movesel )
  {
    capacity = this->m_column[0].items.capacity;
    if ( capacity <= 0 )
      return 1;
    m_onsel = this->m_onsel;
    v12 = (pt.y - this->m_itemoffset.y - this->m_rect.top - 8) / this->m_itemheight;
    if ( v12 < 0 || v12 >= capacity )
    {
      this->m_onsel = -1;
    }
    else if ( *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * (v12 + this->m_firstshow)) )
    {
      this->m_onsel = v12;
    }
    v13 = this->m_onsel;
    if ( m_onsel != v13 )
    {
      if ( v13 != -1 )
      {
        m_firstshow = this->m_firstshow;
        v15 = m_firstshow + v13;
        if ( v15 < 0 )
          v15 = 0;
        if ( v15 > this->m_column[0].items.capacity )
          v15 = this->m_column[0].items.capacity;
        this->m_onsel = v15 - m_firstshow;

        if ( this->m_onsel >= v16 )
        {

          this->m_onsel = v17 - 1;
        }
      }
      Child = ((NPC *)this)->CreateChild();
      m_pfather = this->m_pfather;
      if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1006,
// [VFTABLE]   this->m_id,
// [VFTABLE]   Child);
    }
    if ( g_Input.KeyInfo[0].PressTime != 1 )
      goto LABEL_69;
    if ( (g_Input.KeyInfo[0].Data & 0xF) != 1 )
      goto LABEL_69;
    if ( !*(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * (v12 + this->m_firstshow)) )
      goto LABEL_69;
    m_locksel = ((NPC *)this)->CreateChild();
    v21 = this->m_pfather;
    if ( !v21 )
      goto LABEL_69;
// [VFTABLE] vftable = v21->__vftable;
    goto LABEL_68;
  }
  if ( v9 )
  {
    if ( g_Input.KeyInfo[0].PressTime != 1 )
      goto LABEL_69;
    if ( (g_Input.KeyInfo[0].Data & 0xF) == 2 )
    {
      v23 = this->m_onsel;
      v24 = (pt.y - this->m_itemoffset.y - this->m_rect.top - 8) / this->m_itemheight;
      if ( v24 < 0 || v24 >= this->m_column[0].items.capacity )
      {
        this->m_onsel = -1;
      }
      else
      {
        v25 = this->m_firstshow + v24;
        if ( *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * v25) )
        {
          this->m_onsel = v24;
          this->m_locksel = v25;
        }
      }
      v26 = this->m_onsel;
      if ( v23 != v26 )
      {
        v27 = this->m_column[0].items.capacity;
        if ( v26 != -1 )
        {
          v28 = this->m_firstshow;
          v29 = v28 + v26;
          if ( v29 < 0 )
            v29 = 0;
          if ( v29 >= v27 )
            v29 = v27 - 1;
          this->m_onsel = v29 - v28;

          if ( this->m_onsel >= v30 )
          {

            this->m_onsel = v31 - 1;
          }
        }
        this->m_locksel = this->m_onsel + this->m_firstshow;
      }
      v32 = this->m_pfather;
      if ( v32 )
// [VFTABLE] v32->__vftable->OnMessage(1008, (int)this->m_id, this->m_locksel);
      goto LABEL_69;
    }
    if ( g_Input.KeyInfo[0].PressTime != 1 || (g_Input.KeyInfo[0].Data & 0xF) != 1 )
      goto LABEL_69;
    v33 = this->m_onsel;
    v34 = (pt.y - this->m_itemoffset.y - this->m_rect.top - 8) / this->m_itemheight;
    if ( v34 < 0 || v34 >= this->m_column[0].items.capacity )
    {
      this->m_onsel = -1;
    }
    else
    {
      v35 = this->m_firstshow + v34;
      if ( *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * v35) )
      {
        this->m_onsel = v34;
        this->m_locksel = v35;
      }
    }
    v36 = this->m_onsel;
    if ( v33 != v36 )
    {
      v37 = this->m_column[0].items.capacity;
      if ( v36 != -1 )
      {
        v38 = this->m_firstshow;
        v39 = v38 + v36;
        if ( v39 < 0 )
          v39 = 0;
        if ( v39 >= v37 )
          v39 = v37 - 1;
        this->m_onsel = v39 - v38;

        if ( this->m_onsel >= v40 )
        {

          this->m_onsel = v41 - 1;
        }
      }
      this->m_locksel = this->m_onsel + this->m_firstshow;
    }
    v42 = this->m_pfather;
    if ( !v42 )
      goto LABEL_69;
// [VFTABLE] vftable = v42->__vftable;
    m_locksel = this->m_locksel;
LABEL_68:
    vftable->OnMessage(1007, (int)this->m_id, m_locksel);
LABEL_69:
    if ( v9 )
    {
      if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
      {
        v43 = this->m_pfather;
        if ( v43 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))v43->__vftable->OnMessage)(
// [VFTABLE]   v43,
// [VFTABLE]   1009,
// [VFTABLE]   this->m_id,
// [VFTABLE]   LOWORD(pt.x) | (LOWORD(pt.y) << 16));
      }
      if ( g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
      {
        v44 = this->m_pfather;
        if ( v44 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))v44->__vftable->OnMessage)(
// [VFTABLE]   v44,
// [VFTABLE]   1010,
// [VFTABLE]   this->m_id,
// [VFTABLE]   LOWORD(pt.x) | (LOWORD(pt.y) << 16));
      }
    }
  }
  if ( this->m_hasKeyCtrl )

  return v9;
}

// 0x0043F080
int UIListBox::ProcessSelection()
{
  int result; // eax
  int v3; // eax
  int capacity; // edi
  int m_firstshow; // ecx
  int v6; // eax
  int v7; // eax
  UIWnd *m_pfather; // ecx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  UIWnd *v15; // ecx
  int v16; // eax
  int v17; // edi
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  UIWnd *v21; // ecx
  void *vftable; // edx
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // ecx
  int v27; // eax
  int v28; // eax
  UIWnd *v29; // ecx
  UIWnd *v30; // ecx

  if ( (g_bSceneChangeFlags & 1) == 0 )
  {
    g_bSceneChangeFlags |= 1u;
    atexit((void ( *)())sub_4A13E0);
  }
  result = g_nUILayoutFlags;
  if ( g_nUILayoutFlags <= 0 )
  {
    result = this->m_movesel;
    if ( result )
    {
      result = this->m_onsel;
      if ( result < 0 )
        return result;
      if ( g_Input.KeyInfo[4].PressTime == 1 )
      {
        v3 = result - 1;
        this->m_onsel = v3;
        capacity = this->m_column[0].items.capacity;
        if ( v3 <= 0 )
        {
          this->m_onsel = 0;
          ((UIAnimateCtrlEX *)&this->m_scrollbar)->StepAnimation();
        }
        m_firstshow = this->m_firstshow;
        v6 = this->m_onsel + m_firstshow;
        if ( v6 < 0 )
          v6 = 0;
        if ( v6 >= capacity )
          v6 = capacity - 1;
        v7 = v6 - m_firstshow;
        this->m_onsel = v7;
        result = m_firstshow + v7;
        if ( !*(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * result) )
          goto LABEL_26;
        result = ((NPC *)this)->CreateChild();
        m_pfather = this->m_pfather;
        if ( !m_pfather )
          goto LABEL_26;
      }
      else
      {
        if ( g_Input.KeyInfo[5].PressTime != 1 )
          goto LABEL_26;
        this->m_onsel = result + 1;
        v9 = this->m_column[0].items.capacity;

        if ( this->m_onsel >= v10 - 1 )
        {

          this->m_onsel = v11 - 1;
          ((UIAnimateCtrlEX *)&this->m_scrollbar)->NextFrame();
        }
        v12 = this->m_firstshow;
        v13 = this->m_onsel + v12;
        if ( v13 < 0 )
          v13 = 0;
        if ( v13 >= v9 )
          v13 = v9 - 1;
        v14 = v13 - v12;
        this->m_onsel = v14;
        result = v12 + v14;
        if ( !*(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * result) )
          goto LABEL_26;
        result = ((NPC *)this)->CreateChild();
        m_pfather = this->m_pfather;
        if ( !m_pfather )
          goto LABEL_26;
      }
// [VFTABLE] result = ((int ( *)(UIWnd *, int, void *, int))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1006,
// [VFTABLE]   this->m_id,
// [VFTABLE]   result);
LABEL_26:
      if ( g_Input.KeyInfo[7].PressTime == 1
        && *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * (this->m_onsel + this->m_firstshow)) )
      {
        result = ((NPC *)this)->CreateChild();
        v15 = this->m_pfather;
        if ( v15 )
// [VFTABLE] return ((int ( *)(UIWnd *, int, void *, int))v15->__vftable->OnMessage)(
// [VFTABLE]   v15,
// [VFTABLE]   1007,
// [VFTABLE]   this->m_id,
// [VFTABLE]   result);
      }
      return result;
    }
    if ( g_Input.KeyInfo[4].PressTime == 1 )
    {
      v16 = this->m_onsel - 1;
      this->m_onsel = v16;
      v17 = this->m_column[0].items.capacity;
      if ( v16 <= 0 )
      {
        this->m_onsel = 0;
        ((UIAnimateCtrlEX *)&this->m_scrollbar)->StepAnimation();
      }
      v18 = this->m_firstshow;
      v19 = this->m_onsel + v18;
      if ( v19 < 0 )
        v19 = 0;
      if ( v19 >= v17 )
        v19 = v17 - 1;
      v20 = v19 - v18;
      this->m_onsel = v20;
      result = v18 + v20;
      v21 = this->m_pfather;
      this->m_locksel = result;
      if ( !v21 )
        goto LABEL_51;
// [VFTABLE] vftable = v21->__vftable;
    }
    else
    {
      if ( g_Input.KeyInfo[5].PressTime != 1 )
        goto LABEL_51;
      ++this->m_onsel;
      v23 = this->m_column[0].items.capacity;

      if ( this->m_onsel >= v24 - 1 )
      {

        this->m_onsel = v25 - 1;
        ((UIAnimateCtrlEX *)&this->m_scrollbar)->NextFrame();
      }
      v26 = this->m_firstshow;
      v27 = this->m_onsel + v26;
      if ( v27 < 0 )
        v27 = 0;
      if ( v27 >= v23 )
        v27 = v23 - 1;
      v28 = v27 - v26;
      this->m_onsel = v28;
      result = v26 + v28;
      this->m_locksel = result;
      if ( result >= v23 )
        this->m_locksel = v23 - 1;
      v29 = this->m_pfather;
      if ( !v29 )
        goto LABEL_51;
// [VFTABLE] vftable = v29->__vftable;
      result = this->m_locksel;
    }
    result = vftable->OnMessage(1007, (int)this->m_id, result);
LABEL_51:
    if ( g_Input.KeyInfo[7].PressTime == 1 )
    {
      v30 = this->m_pfather;
      if ( v30 )
// [VFTABLE] return ((int ( *)(UIWnd *, int, void *, int))v30->__vftable->OnMessage)(
// [VFTABLE]   v30,
// [VFTABLE]   1008,
// [VFTABLE]   this->m_id,
// [VFTABLE]   this->m_locksel);
    }
  }
  return result;
}

// 0x0043F360
int UIListBox::ClearAll()
{
  int i; // edi
  int v3; // edi
  UILBColumn *m_column; // ebx
  int result; // eax

  for ( i = 0; i < this->m_column[0].items.capacity; ++i )
    this->AdjustScroll(i);
  v3 = 0;
  if ( this->m_numcol > 0 )
  {
    m_column = this->m_column;
    do
    {
      ((UIListBox *)m_column)->GetItemAt();
      ++v3;
      ++m_column;
    }
    while ( v3 < this->m_numcol );
  }
  this->m_firstshow = 0;
  ((UIBigMap *)&this->m_scrollbar)->SetScrollRange(0, 0);
  result = *(_DWORD *)&this->m_rowenable[8];
  *(_DWORD *)&this->m_rowenable[8] = *(_DWORD *)&this->m_rowenable[4];
  return result;
}

// 0x0043F410
int UIListBox::AdjustScroll(int nVal)
{
  int result; // eax
  PtrArray *p_items; // edi
  void *v6; // ebp
  _DWORD *v7; // ecx
  _DWORD *i; // eax
  int v9; // eax
  int nVala; // [esp+0xC] [ebp+0x4]

  result = this->m_numcol;
  if ( result > 0 && nVal >= 0 && nVal < this->m_column[0].items.capacity )
  {
    nVala = 0;
    p_items = &this->m_column[0].items;
    do
    {
      if ( nVal < p_items->capacity )
      {
        v6 = *(void **)&p_items->m_pData[4 * nVal];
        if ( v6 )
        {
          ((UIListBox *)*(UIListBox **)&p_items->m_pData[4 * nVal])->Render();
          operator delete(v6);
        }
      }
      ((PtrArray *)p_items)->RemoveAt(nVal, 1);
      p_items = (PtrArray *)((char *)p_items + 84);
      ++nVala;
    }
    while ( nVala < this->m_numcol );

    this->m_onsel = -1;
    v7 = *(_DWORD **)&this->m_rowenable[8];
    for ( i = (_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * nVal + 4); i != v7; ++i )
      *(i - 1) = *i;
    *(_DWORD *)&this->m_rowenable[8] -= 4;
    result = this->m_firstshow;
    if ( nVal <= result )
    {
      this->m_firstshow = result - 1;
      v9 = this->m_column[0].items.capacity - 1;
      if ( this->m_firstshow > v9 )
        this->m_firstshow = v9;
      result = this->m_firstshow;
      if ( result < 0 )
        this->m_firstshow = 0;
    }
  }
  return result;
}

// 0x0043F520
int UIListBox::InitScrollbar()
{
  int capacity; // esi
  int v3; // eax

  if ( this->m_numcol <= 0 )
    return ((UIBigMap *)&this->m_scrollbar)->SetScrollRange(0, 0);
  capacity = this->m_column[0].items.capacity;

  if ( capacity <= v3 )
    return ((UIBigMap *)&this->m_scrollbar)->SetScrollRange(0, 0);
  else
    return ((UIBigMap *)&this->m_scrollbar)->SetScrollRange(0, capacity - v3);
}

// 0x0043F590
int UIListBox::GetLockedSel()
{
  int result; // eax

  result = -1;
  if ( this->m_numcol > 0 && this->m_onsel != -1 )
    return this->m_locksel;
  return result;
}

// 0x0043F5B0
int UIListBox::GetItem()
{
  int m_firstshow; // ecx
  int v3; // eax
  int v4; // eax
  int result; // eax
  int v6; // [esp+0xC] [ebp+0x4]

  if ( v6 < 0 || v6 >= this->m_column[0].items.capacity )
  {
    this->m_onsel = -1;
  }
  else
  {
    m_firstshow = this->m_firstshow;
    this->m_onsel = v6 - m_firstshow;
    if ( v6 - m_firstshow < 0 )
      this->m_onsel = 0;

    if ( this->m_onsel >= v3 )
    {

      this->m_onsel = v4 - 1;
    }
    this->m_firstshow = v6 - this->m_onsel;
    ((UIScene *)&this->m_scrollbar)->SetFirstShow();
  }
  result = this->m_onsel + this->m_firstshow;
  this->m_locksel = result;
  return result;
}

// 0x0043F640
void UIListBox::SetLockSel()
{
  int v1; // [esp+0x4] [ebp+0x4]

  this->m_itemheight = v1;
}

// 0x0043F650
int UIListBox::GetItemData()
{
  if ( this->m_numcol > 0 )
    return this->m_column[0].items.capacity;
  else
    return 0;
}

// 0x0043F670
int UIListBox::SetItemOffset(int nVal, int nVal2)
{
  this->m_itemoffset.x = nVal;
  this->m_itemoffset.y = nVal2;
  return nVal;
}

// 0x0043F690
int UIListBox::SetItemData(int nData)
{
  this->m_movesel = nData;
  return nData;
}

// 0x0043F6A0
unsigned int UIListBox::SetChildParam(unsigned int dwVal, int nVal)
{
  unsigned int result; // eax

  *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * dwVal) = nVal;
  result = ((NPC *)this)->CreateChild();
  if ( dwVal == result )
    return this->SetFirstShow(dwVal);
  return result;
}

// 0x0043F6D0
int UIListBox::SetFirstShow(unsigned int dwVal)
{
  int v2; // edx
  int v3; // eax
  signed int v4; // esi
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int result; // eax
  _DWORD *v9; // edx

  v2 = *(_DWORD *)&this->m_rowenable[4];
  if ( v2 )
    v3 = (*(_DWORD *)&this->m_rowenable[8] - v2) >> 2;
  else
    v3 = 0;
  v4 = dwVal;
  if ( dwVal >= v3 - 1 )
  {
    v5 = *(_DWORD *)&this->m_rowenable[4];
    if ( v5 )
      v6 = (*(_DWORD *)&this->m_rowenable[8] - v5) >> 2;
    else
      v6 = 0;
    v4 = v6 - 1;
  }
  v7 = *(_DWORD *)&this->m_rowenable[4];
  for ( result = v4; v7 && result < (unsigned int)((*(_DWORD *)&this->m_rowenable[8] - v7) >> 2); ++result )
  {
    if ( *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * result) )
      goto LABEL_19;
  }
  result = 0;
  if ( v4 <= 0 )
  {
LABEL_18:
    this->m_onsel = -1;
    return result;
  }
  v9 = *(_DWORD **)&this->m_rowenable[4];
  while ( !*v9 )
  {
    ++result;
    ++v9;
    if ( result >= v4 )
      goto LABEL_18;
  }
LABEL_19:
  result -= this->m_firstshow;
  this->m_onsel = result;
  return result;
}

// 0x0043FE90
int UIListBox::GetCurSel()
{
  int m_tilewidth; // edx

  m_tilewidth = this->m_scrollbar.m_bk.m_tilewidth;
  this->m_scrollbar.m_childs.m_pData = 0;
  this->m_scrollbar.m_rect.bottom = 0;
  this->m_scrollbar.m_childs.m_nSize = 0;
  LOBYTE(this->m_scrollbar.m_bk.m_wndcolor.Color) = 0;
  BYTE1(this->m_scrollbar.m_btnH) = 0;
  this->m_scrollbar.m_bk.m_tileheight = m_tilewidth;
  LOBYTE(this->m_scrollbar.m_btnH) = 0;
  BYTE2(this->m_scrollbar.m_btnH) = 0;
  return 0;
}

// 0x00445C60
int UIListBox::Update(int a2, int a3)
{
  int v5; // edi
  int v6; // esi
  int v7; // ecx

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  v5 = this->m_childs.capacity - 1;
  if ( v5 < 0 )
    return a3 == 0;
  v6 = a3;
  do
  {
    v7 = *(_DWORD *)&this->m_childs.m_pData[4 * v5];
    if ( (*(int ( **)(int, int, int))(*(_DWORD *)v7 + 8))(v7, a2, v6) )
      v6 = 0;
    --v5;
  }
  while ( v5 >= 0 );
  return v6 == 0;
}

// 0x00451850
int UIListBox::UIListBox_Init()
{
  *(_DWORD *)&this->m_hasKeyCtrl = 0;
  ((UIListBox *)&this->m_scrollbar.m_wndcolor)->UpdateKeyCtrl();
  ((UITextArea *)((char *)this + 1296))->InitAfterClear();
// [VFTABLE] this->m_scrollbar.__vftable = 0;
  this->m_selcolor.Color = 1;
  this->m_scrollbar.m_fontcolor.Color = -1;
  return (int)this;
}

// 0x00451900
void UIListBox::DestroyContent()
{
  ((UITextArea *)&pWnd[19].m_fontcolor)->Destroy();
  ((UIListBox *)&pWnd[1].m_rect.top)->DeleteRow();
  ((UIWnd *)pWnd)->Destroy();
}

// 0x00451AD0
int UIListBox::ReinitScrollbar()
{
  int result; // eax

  result = ((UIListBox *)&this->m_scrollbar.m_wndcolor)->ClearAll();
  this->m_scrollbar.m_fontcolor.Color = -1;
  return result;
}

// 0x00451AF0
int UIListBox::CalcVisibleRange(char *Source, int nVal)
{
  gbColorQuad *p_m_wndcolor; // esi
  unsigned int v5; // eax
  unsigned int v6; // kr04_4
  int result; // eax

  p_m_wndcolor = &this->m_scrollbar.m_wndcolor;
  v5 = ((UIListBox *)&this->m_scrollbar.m_wndcolor)->SetItemOffset(Source, 0);
  ((UIListBox *)p_m_wndcolor)->SetChildParam(v5, nVal);
  ((UIListBox *)p_m_wndcolor)->GetItem();
  v6 = strlen(Source) + 1;
  result = this->m_scrollbar.m_fontcolor.Color;
  if ( (int)(v6 - 1) > result )
    this->m_scrollbar.m_fontcolor.Color = v6 - 1;
  return result;
}

// 0x00451B40
int UIListBox::ResizeToContent(int bResize)
{
  if ( bResize )
  {
    ((UIListBox *)&this->m_scrollbar.m_wndcolor)->GetItemData();
    sub_445FA0(this);
    sub_445FA0((char *)this + 1296);
    sub_445FA0(&this->m_scrollbar.m_wndcolor);
    sub_445DB0(this);
    sub_445DB0(0);
  }
  (**((void ( ***)(char *, int))this + 324))((char *)this + 1296, bResize);
  ((UIScene *)((char *)this + 1296))->SetState();
  return ((PalScript *)this)->ShowWindow(bResize);
}

// 0x00451C10
int UIListBox::IsVisible()
{
  int result; // eax

  result = this->m_bvisible;
  if ( result )
  {
    result = (*(int ( **)(char *))(*((_DWORD *)this + 324) + 4))((char *)this + 1296);
    if ( *((_DWORD *)this + 367) == 2 )
      return (*(int ( **)(gbColorQuad *))(this->m_scrollbar.m_wndcolor.Color + 4))(&this->m_scrollbar.m_wndcolor);
  }
  return result;
}

// 0x00452600
void UIListBox::ctor_2600()
{
  ((UITitle_BBTY *)&this->m_column[7].head[60])->ctor();
  ((UIAnimateCtrlEX *)&this->m_showGrayBk)->_UIAnimateCtrlEX();
}

// 0x004526C0
BOOL UIListBox::ShouldProcessInput(int nVal, int nVal2)
{
  if ( g_CCBEditorInst.m_dwTrickID[361] == 12 || g_nCameraUpdateCount > 0 )
    return this->Update(nVal, nVal2);
  else
    return 0;
}

// 0x004526F0
int UIListBox::RenderMagic()
{
  int result; // eax
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  if ( g_CCBEditorInst.m_dwTrickID[361] == 12 )
    ((CCBControlWindow *)this)->Render(v3);
  result = g_nCameraUpdateCount;
  if ( g_nCameraUpdateCount > 0 )
    ((CCBControlWindow *)this)->Render(v3);
  return result;
}

// 0x0046B4B0
int UIListBox::OnMessage(int nVal, char *pszBuf, int nVal2)
{
  char *v5; // edi
  int v6; // eax
  void ( **v7)(char *, int, int); // edx
  UICursor *v8; // ecx
  CScreenMode *Instance; // eax
  CScreenMode *v11; // eax
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  CScreenMode *v17; // eax
  CScreenMode *v18; // eax
  int *v19; // eax
  int v20; // eax
  _DWORD *v21; // ecx
  int v22; // eax
  CScreenMode *v23; // eax
  int m_num; // eax
  int v25; // eax
  _PlugInfo *v26; // ecx
  int v27; // edx
  _PlugInfo *v28; // eax
  CScreenMode *v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // edi
  _PlugInfo *v34; // eax
  _PlugInfo *v35; // eax
  _PlugInfo *v36; // eax
  _PlugInfo *v37; // ecx
  int v38; // edx
  _PlugInfo *v39; // eax
  int *v40; // eax
  int v41; // eax
  const char *v42; // ebp
  int v43; // eax
  const char *v44; // ebp
  const char *v45; // edx
  int *v46; // eax
  int v47; // ebx
  int v48; // ebp
  int v49; // eax
  UIListBox *v50; // edi
  int v51; // ebp
  void *v52; // ebx
  int v53; // edx
  int v54; // ecx
  int v55; // edx
  void *v56; // eax
  int v57; // ecx
  char *v58; // ecx
  int v59; // edx
  void *vftable; // edx
  int v61; // eax
  _PlugInfo *v62; // eax
  _PlugInfo *v63; // eax
  _PlugInfo *v64; // eax
  _PlugInfo *v65; // eax
  _PlugInfo *v66; // eax
  int v67; // edx
  signed int v68; // ecx
  int v69; // eax
  int v70; // eax
  int v71; // edx
  int v72; // eax
  _PlugInfo *v73; // eax
  _PlugInfo *v74; // eax
  UIScrollBar *p_m_scrollbar; // edi
  const char *v76; // [esp-0x8] [ebp-0x128]
  const char *v77; // [esp-0x8] [ebp-0x128]
  const char *v78; // [esp-0x8] [ebp-0x128]
  const char *v79; // [esp-0x8] [ebp-0x128]
  const char *v80; // [esp-0x8] [ebp-0x128]
  const char *v81; // [esp-0x8] [ebp-0x128]
  const char *v82; // [esp-0x8] [ebp-0x128]
  const char *v83; // [esp-0x8] [ebp-0x128]
  const char *v84; // [esp-0x8] [ebp-0x128]
  _SPropValue *v85; // [esp-0x8] [ebp-0x128]
  _SPropValue *v86; // [esp-0x8] [ebp-0x128]
  int v87; // [esp-0x4] [ebp-0x124]
  int v88; // [esp+0x0] [ebp-0x120]
  gbColorQuad v89; // [esp+0x10] [ebp-0x110] BYREF
  gbColorQuad v90; // [esp+0x14] [ebp-0x10C] BYREF
  int pOut; // [esp+0x18] [ebp-0x108] BYREF
  char Buffer[253]; // [esp+0x20] [ebp-0x100] BYREF
  __int16 v93; // [esp+0x11D] [ebp-0x3]
  char v94; // [esp+0x11F] [ebp-0x1]

  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        if ( this->m_scrollbar.m_texarrayInfo[0] )
        {
          operator delete(this->m_scrollbar.m_texarrayInfo[0]);
          this->m_scrollbar.m_texarrayInfo[0] = 0;
        }
        this->m_scrollbar.m_texarrayInfo[0] = (_PlugInfo *)operator new(4 * *((_DWORD *)this + 3568));
        if ( *((_DWORD *)this + 23368) )
        {
          operator delete(*((void **)this + 23368));
          *((_DWORD *)this + 23368) = 0;
        }
        *((_DWORD *)this + 23368) = operator new(4 * *((_DWORD *)this + 3568));
        if ( *((_DWORD *)this + 23399) )
        {
          operator delete(*((void **)this + 23399));
          *((_DWORD *)this + 23399) = 0;
        }
        *((_DWORD *)this + 23399) = operator new(4 * *((_DWORD *)this + 3568));
        memset(this->m_scrollbar.m_texarrayInfo[0], 0, 4 * *((_DWORD *)this + 3568));
        memset(*((void **)this + 23368), 0, 4 * *((_DWORD *)this + 3568));
        memset(*((void **)this + 23399), 0, 4 * *((_DWORD *)this + 3568));
        ((UIStatic *)((char *)this + 98900))->CreateFromTemplate();
        (**((void ( ***)(char *, int))this + 23937))((char *)this + 95748, 1);
        if ( g_bListNeedsRefresh )
        {
          ((UICaption *)((char *)this + 95748))->SetEnable((int)this + 2436, 0);
          (**((void ( ***)(char *, int))this + 6332))((char *)this + 25328, 1);
          *((_BYTE *)this + 105349) = 1;
          *((_DWORD *)this + 26468) = 2;
          *((_DWORD *)this + 26466) = 1;
          sub_445E50((int)this + 99204);
          ((UIListBox *)((char *)this + 99204))->GetItem();
          ((PAL3 *)this)->SetRange(0);
          ((PAL3 *)this)->GetValue(0);
          (**((void ( ***)(char *, _DWORD))this + 25115))((char *)this + 100460, 0);
          (**((void ( ***)(char *, _DWORD))this + 25201))((char *)this + 100804, 0);
          sub_445E50((int)this + 103084);
          (**((void ( ***)(char *, _DWORD))this + 26299))((char *)this + 105196, 0);
        }
        else
        {
          if ( ((UIListBox *)((char *)this + 99204))->GetItemData() <= 0 )
          {
            (**((void ( ***)(char *, _DWORD))this + 25115))((char *)this + 100460, 0);
            (**((void ( ***)(char *, _DWORD))this + 25201))((char *)this + 100804, 0);
            v5 = (char *)this + 25328;
            (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
            (**((void ( ***)(char *, _DWORD))this + 26299))((char *)this + 105196, 0);
          }
          else
          {
            this->OnMessage(1007, 0, 0);
            v5 = (char *)this + 25328;
            (**((void ( ***)(char *, int))this + 6332))((char *)this + 25328, 1);
          }
          ((UITitle_JDHY *)this)->LayoutCalcRects();
          ((PAL3 *)this)->SetRange(1u);
          sub_445E50((int)this + 99204);
          ((UIListBox *)((char *)this + 99204))->GetItem();
          this->m_scrollbar.m_texarray.m_num = 0;
          if ( ((UIListBox *)((char *)this + 99204))->GetItemData() > 0 )
            this->OnMessage(1007,
              0,
              this->m_scrollbar.m_texarray.m_num);
          else
            this->m_scrollbar.m_texarray.m_num = -1;
          if ( BYTE1(this->m_scrollbar.m_texarrayInfo[9]) )
            sub_445E50((int)this + 102364);
          ((UICaption *)((char *)this + 95748))->SetEnable((int)&this->m_column[5].head[44], 0);
          v6 = lstrlenA(&this->m_column[5].head[44]);
          v7 = (void ( **)(char *, int, int))*((_DWORD *)this + 23937);
          if ( v6 > 0 )
          {
            (*v7)((char *)this + 95748, 1, v88);
            (**(void ( ***)(char *, int))v5)(v5, 1);
          }
          else
          {
            (*v7)((char *)this + 95748, 0, v88);
            (**(void ( ***)(char *, _DWORD))v5)(v5, 0);
          }
          *((_BYTE *)this + 105348) = 1;
          sub_445E50((int)this + 103084);
        }
        *((_BYTE *)this + 101173) = 1;
        *((_BYTE *)this + 101172) = 1;
        sprintf(
          (char *const)&this->m_scrollbar,
          "%s %d",
          (const char *)&g_bSaveFlag,
          ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
        ((UICaption *)(UICaption *)this + 1059)->SetEnable((int)&this->m_scrollbar, 0);
        ((UICursor *)v8)->IRender();
        return 1;
      }
      else
      {
        if ( *((_DWORD *)this + 23368) )
        {
          operator delete(*((void **)this + 23368));
          *((_DWORD *)this + 23368) = 0;
        }
        if ( *((_DWORD *)this + 23399) )
        {
          operator delete(*((void **)this + 23399));
          *((_DWORD *)this + 23399) = 0;
        }
        if ( !this->m_scrollbar.m_texarrayInfo[0] )
          return 1;
        operator delete(this->m_scrollbar.m_texarrayInfo[0]);
        this->m_scrollbar.m_texarrayInfo[0] = 0;
        return 1;
      }
    case 1001:
      switch ( (unsigned int)pszBuf )
      {
        case 0x102u:
          ((SaleUI *)this)->DestroySubFrames();
          ((UIFrameWnd *)*((UIFrameWnd **)this + 26476))->OnPaintUpdate();
          v76 = g_pCScreenMode_5B46B4;
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v76, 1);
          return 1;
        case 0x106u:
          if ( ((UIListBox *)((char *)this + 99204))->GetItemData() > 0 )
          {
            *((_DWORD *)this + 26468) = 1;
            *((_BYTE *)this + 105876) = 0;
            ((PAL_GDB *)this)->UpdateSkillPanel();
            *((_BYTE *)this + 105862) = 1;
            ((PAL3 *)this)->GetValue(0);
            v77 = g_pCScreenMode_5B46B4;
            v11 = CScreenMode::GetInstance();
            ((CScreenMode *)v11)->AudioSetPosition(v77, 1);
          }
          else
          {
            (**((void ( ***)(char *, _DWORD))this + 25115))((char *)this + 100460, 0);
            (**((void ( ***)(char *, _DWORD))this + 25201))((char *)this + 100804, 0);
            (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
            (**((void ( ***)(char *, _DWORD))this + 26299))((char *)this + 105196, 0);
          }
          return 1;
        case 0x107u:
          if ( *((int *)this + 26473) <= 0 )
            return 1;
          if ( ((UIListBox *)((char *)this + 99204))->GetItemData() > 0 )
          {
            *((_DWORD *)this + 26468) = -1;
            *((_DWORD *)this + 26466) = 0;
            (**((void ( ***)(char *, int))this + 23937))((char *)this + 95748, 1);
            ((UICaption *)((char *)this + 95748))->SetEnable((int)this + 256 * *((_DWORD *)this + 26466) + 105350, 0);
            (**((void ( ***)(char *, int))this + 6332))((char *)this + 25328, 1);
            *((_BYTE *)this + 105876) = 1;
            *((_BYTE *)this + 105862) = 1;
            sub_445E50((int)this + 99204);
            ((PAL3 *)this)->SetRange(0);
            ((PAL3 *)this)->GetValue(0);
            (**((void ( ***)(char *, _DWORD))this + 25115))((char *)this + 100460, 0);
            (**((void ( ***)(char *, _DWORD))this + 25201))((char *)this + 100804, 0);
            (**((void ( ***)(char *, _DWORD))this + 26299))((char *)this + 105196, 0);
            v78 = g_pCScreenMode_5B46B4;
            v12 = CScreenMode::GetInstance();
            ((CScreenMode *)v12)->AudioSetPosition(v78, 1);
          }
          else
          {
            (**((void ( ***)(char *, _DWORD))this + 25115))((char *)this + 100460, 0);
            (**((void ( ***)(char *, _DWORD))this + 25201))((char *)this + 100804, 0);
            (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
            (**((void ( ***)(char *, _DWORD))this + 26299))((char *)this + 105196, 0);
          }
          return 1;
        case 0x108u:
          if ( ((UIListBox *)((char *)this + 99204))->GetItemData() > 0 )
          {
            ((SaleUI *)this)->DestroySubFrames();
            ((CCBSystem *)this)->InitResultWindow();
            if ( BYTE1(this->m_scrollbar.m_texarrayInfo[9]) )
              sub_445E50((int)this + 102364);
            (**((void ( ***)(char *, int))this + 23937))((char *)this + 95748, 1);
            ((UICaption *)((char *)this + 95748))->SetEnable((int)this + 1668, 0);
            sub_445E50((int)this + 95748);
            (**((void ( ***)(char *, int))this + 6332))((char *)this + 25328, 1);
            *((_BYTE *)this + 105348) = 1;
            goto LABEL_53;
          }
          (**((void ( ***)(char *, _DWORD))this + 25115))((char *)this + 100460, 0);
          (**((void ( ***)(char *, _DWORD))this + 25201))((char *)this + 100804, 0);
          (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
          (**((void ( ***)(char *, _DWORD))this + 26299))((char *)this + 105196, 0);
          return 1;
        case 0x111u:
          ((PlayerMgr *)this)->InitMode(0);
          v79 = g_pCScreenMode_5B46B4;
          v13 = CScreenMode::GetInstance();
          ((CScreenMode *)v13)->AudioSetPosition(v79, 1);
          return 1;
        case 0x112u:
          ((PlayerMgr *)this)->InitMode(1);
          v80 = g_pCScreenMode_5B46B4;
          v14 = CScreenMode::GetInstance();
          ((CScreenMode *)v14)->AudioSetPosition(v80, 1);
          return 1;
        case 0x113u:
          ((PlayerMgr *)this)->InitMode(2);
          goto LABEL_53;
        case 0x114u:
          ((PlayerMgr *)this)->InitMode(3);
          v81 = g_pCScreenMode_5B46B4;
          v15 = CScreenMode::GetInstance();
          ((CScreenMode *)v15)->AudioSetPosition(v81, 1);
          return 1;
        case 0x115u:
          ((PlayerMgr *)this)->InitMode(4);
          v82 = g_pCScreenMode_5B46B4;
          v16 = CScreenMode::GetInstance();
          ((CScreenMode *)v16)->AudioSetPosition(v82, 1);
          return 1;
        case 0x129u:
          *((_BYTE *)this + 93440) = 1;
          *((_BYTE *)this + 105862) = 0;
          ((PAL3 *)this)->GetValue(0);
          ((CCBSystem *)this)->ProcessSlotResults(this->m_scrollbar.m_texarray.m_num);
          ((PlayerMgr *)this)->SetSelectionFlags(this->m_scrollbar.m_texarray.m_num);
          v83 = g_pCScreenMode_5B46B4;
          v17 = CScreenMode::GetInstance();
          ((CScreenMode *)v17)->AudioSetPosition(v83, 1);
          return 1;
        case 0x130u:
          ((PAL3 *)this)->GetValue(0);
          *((_BYTE *)this + 93440) = 0;
LABEL_53:
          v84 = g_pCScreenMode_5B46B4;
          v18 = CScreenMode::GetInstance();
          ((CScreenMode *)v18)->AudioSetPosition(v84, 1);
          return 1;
        case 0x195u:
          ((PlayerMgr *)this)->SendInputToRole(0);
          v19 = &this->m_scrollbar.m_texarrayInfo[0]->filepos + this->m_scrollbar.m_texarray.m_num;
          ++*v19;
          ++*(_DWORD *)(*((_DWORD *)this + 23368) + 4 * this->m_scrollbar.m_texarray.m_num);
          v20 = 4 * this->m_scrollbar.m_texarray.m_num;
          v21 = (int *)((char *)&this->m_scrollbar.m_texarrayInfo[0]->filepos + v20);
          v22 = *(_DWORD *)(v20 + *((_DWORD *)this + 23400));
          if ( *v21 < v22 )
          {
            sub_445E50((int)this + 100460);
            sub_445E50((int)this + 100804);
            v85 = (_SPropValue *)off_5B46C4;
          }
          else
          {
            *v21 = v22;
            *(_DWORD *)(*((_DWORD *)this + 23368) + 4 * this->m_scrollbar.m_texarray.m_num) = *(_DWORD *)(4 * this->m_scrollbar.m_texarray.m_num + *((_DWORD *)this + 23400));
            sub_445E50((int)this + 100460);
            sub_445E50((int)this + 100804);
            sprintf((char *const)&this->m_scrollbar, "\\n      %s", (const char *)dword_DCCC3C);
            ((UICaption *)((char *)this + 94380))->SetEnable((int)&this->m_scrollbar, 0);
            ((UIRoleSelect *)((char *)this + 93924))->SetByte(1);
            v85 = off_5B46C0;
          }
          v23 = CScreenMode::GetInstance();
          ((CScreenMode *)v23)->AudioSetPosition(v85, 1);
          sprintf(
            (char *const)&this->m_scrollbar,
            &dir[20],
            *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + this->m_scrollbar.m_texarray.m_num));
          ((UIListBox *)((char *)this + 99204))->SetMouseMoveSel(2, this->m_scrollbar.m_texarray.m_num, (char *)&this->m_scrollbar, 0);
          m_num = this->m_scrollbar.m_texarray.m_num;
          if ( *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + m_num) <= 0 )
          {
            if ( m_num < 0 || m_num >= *((_DWORD *)this + 24927) )
              v25 = 0;
            else
              v25 = *(_DWORD *)(*((_DWORD *)this + 24926) + 4 * m_num);
            *(_DWORD *)(v25 + 68) = *((_DWORD *)this + 24802);
          }
          else
          {
            ((UITabCtrl *)((char *)this + 99204))->SetItemParam(this->m_scrollbar.m_texarray.m_num);
          }
          v26 = this->m_scrollbar.m_texarrayInfo[0];
          this->m_scrollbar.m_texarrayInfo[3] = (_PlugInfo *)(v26->filepos * *(_DWORD *)(*((_DWORD *)this + 3970) + 608));
          *((_DWORD *)this + 26473) = v26->filepos;
          v27 = *((_DWORD *)this + 3568);
          this->m_scrollbar.m_texarrayInfo[4] = (_PlugInfo *)1;
          if ( v27 > 1 )
          {
            do
            {
              v28 = this->m_scrollbar.m_texarrayInfo[4];
              this->m_scrollbar.m_texarrayInfo[3] = (_PlugInfo *)((char *)this->m_scrollbar.m_texarrayInfo[3]
                                                                + *(&v26->filepos + (_DWORD)v28)
                                                                * *(_DWORD *)(*((_DWORD *)this + (_DWORD)v28 + 3970)
                                                                            + 608));
              *((_DWORD *)this + 26473) += *(&v26->filepos + (_DWORD)v28);
              v28 = (_PlugInfo *)((char *)v28 + 1);
              this->m_scrollbar.m_texarrayInfo[4] = v28;
            }
            while ( (int)v28 < v27 );
          }
          sprintf((char *const)&this->m_scrollbar, "%s %d", g_szCombatFieldName, this->m_scrollbar.m_texarrayInfo[3]);
          ((UICaption *)((char *)this + 101832))->SetEnable((int)&this->m_scrollbar, 0);
          if ( *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + this->m_scrollbar.m_texarray.m_num) > 0 )
          {
            *((_BYTE *)this + 93440) = 0;
            ((UICaption *)((char *)this + 95748))->SetEnable((int)g_szSceneUIText, 0);
            (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
            ((PAL3 *)this)->GetValue(1u);
          }
          if ( (int)this->m_scrollbar.m_texarrayInfo[3] > 0 && !BYTE1(this->m_scrollbar.m_texarrayInfo[9]) )
            return 1;
          sub_445E50((int)this + 102364);
          return 1;
        case 0x196u:
          ((PlayerMgr *)this)->SendInputToRole(0);
          --*(&this->m_scrollbar.m_texarrayInfo[0]->filepos + this->m_scrollbar.m_texarray.m_num);
          --*(_DWORD *)(*((_DWORD *)this + 23368) + 4 * this->m_scrollbar.m_texarray.m_num);
          if ( *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + this->m_scrollbar.m_texarray.m_num) > 0 )
          {
            sub_445E50((int)this + 100460);
            sub_445E50((int)this + 100804);
            v86 = (_SPropValue *)off_5B46C4;
          }
          else
          {
            ((CCBSystem *)this)->InitResultWindow();
            *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + this->m_scrollbar.m_texarray.m_num) = 0;
            *(_DWORD *)(*((_DWORD *)this + 23368) + 4 * this->m_scrollbar.m_texarray.m_num) = 0;
            sub_445E50((int)this + 100460);
            sub_445E50((int)this + 100804);
            ((PAL3 *)this)->GetValue(0);
            v86 = off_5B46C0;
          }
          v29 = CScreenMode::GetInstance();
          ((CScreenMode *)v29)->AudioSetPosition(v86, 1);
          sprintf(
            (char *const)&this->m_scrollbar,
            &dir[20],
            *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + this->m_scrollbar.m_texarray.m_num));
          ((UIListBox *)((char *)this + 99204))->SetMouseMoveSel(2, this->m_scrollbar.m_texarray.m_num, (char *)&this->m_scrollbar, 0);
          v30 = this->m_scrollbar.m_texarray.m_num;
          if ( *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + v30) <= 0 )
          {
            if ( v30 < 0 || v30 >= *((_DWORD *)this + 24927) )
              v31 = 0;
            else
              v31 = *(_DWORD *)(*((_DWORD *)this + 24926) + 4 * v30);
            *(_DWORD *)(v31 + 68) = *((_DWORD *)this + 24802);
          }
          else
          {
            ((UITabCtrl *)((char *)this + 99204))->SetItemParam(this->m_scrollbar.m_texarray.m_num);
          }
          if ( *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + this->m_scrollbar.m_texarray.m_num) >= *(_DWORD *)(*((_DWORD *)this + 23399) + 4 * this->m_scrollbar.m_texarray.m_num) )
            goto LABEL_94;
          this->m_scrollbar.m_texarrayInfo[4] = 0;
          break;
        default:
          return 1;
      }
      while ( 1 )
      {
        v32 = (int)this->m_scrollbar.m_texarrayInfo[4];
        if ( *((_BYTE *)this + v32 + 26348) )
        {
          v33 = this->m_scrollbar.m_texarray.m_num;
          this->m_scrollbar.m_texarrayInfo[5] = 0;
          while ( 1 )
          {
            v34 = this->m_scrollbar.m_texarrayInfo[5];
            if ( *((_DWORD *)this + (_DWORD)v34 + 6 * v32 + 23369) == v33 )
              break;
            v35 = (_PlugInfo *)((char *)&v34->filepos + 1);
            this->m_scrollbar.m_texarrayInfo[5] = v35;
            if ( (int)v35 >= 6 )
              goto LABEL_90;
          }
          ((SaleUI *)this)->Update(v32, (int)this->m_scrollbar.m_texarrayInfo[5]);
          ((PAL3 *)this)->GetValue(0);
          *((_BYTE *)this + 93440) = 0;
          this->m_scrollbar.m_texarrayInfo[6] = (_PlugInfo *)1;
LABEL_90:
          if ( this->m_scrollbar.m_texarrayInfo[6] == (_PlugInfo *)1 )
            break;
        }
        v36 = (_PlugInfo *)((char *)&this->m_scrollbar.m_texarrayInfo[4]->filepos + 1);
        this->m_scrollbar.m_texarrayInfo[4] = v36;
        if ( (int)v36 >= 5 )
          goto LABEL_94;
      }
      this->m_scrollbar.m_texarrayInfo[6] = 0;
LABEL_94:
      v37 = this->m_scrollbar.m_texarrayInfo[0];
      this->m_scrollbar.m_texarrayInfo[3] = (_PlugInfo *)(v37->filepos * *(_DWORD *)(*((_DWORD *)this + 3970) + 608));
      *((_DWORD *)this + 26473) = v37->filepos;
      v38 = *((_DWORD *)this + 3568);
      this->m_scrollbar.m_texarrayInfo[4] = (_PlugInfo *)1;
      if ( v38 > 1 )
      {
        do
        {
          v39 = this->m_scrollbar.m_texarrayInfo[4];
          this->m_scrollbar.m_texarrayInfo[3] = (_PlugInfo *)((char *)this->m_scrollbar.m_texarrayInfo[3]
                                                            + *(&v37->filepos + (_DWORD)v39)
                                                            * *(_DWORD *)(*((_DWORD *)this + (_DWORD)v39 + 3970) + 608));
          *((_DWORD *)this + 26473) += *(&v37->filepos + (_DWORD)v39);
          v39 = (_PlugInfo *)((char *)v39 + 1);
          this->m_scrollbar.m_texarrayInfo[4] = v39;
        }
        while ( (int)v39 < v38 );
      }
      sprintf((char *const)&this->m_scrollbar, "%s %d", g_szCombatFieldName, this->m_scrollbar.m_texarrayInfo[3]);
      ((UICaption *)((char *)this + 101832))->SetEnable((int)&this->m_scrollbar, 0);
      if ( (int)this->m_scrollbar.m_texarrayInfo[3] > 0 )
      {
        if ( BYTE1(this->m_scrollbar.m_texarrayInfo[9]) )
          sub_445E50((int)this + 102364);
        return 1;
      }
      else
      {
        sub_445E50((int)this + 102364);
        return 1;
      }
    case 1002:
      switch ( (unsigned int)pszBuf )
      {
        case 0x111u:
          p_m_scrollbar = &this->m_scrollbar;
          sprintf(
            (char *const)&this->m_scrollbar,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)(int)this->m_scrollbar.m_texarrayInfo[3] * 0.5));
          goto LABEL_213;
        case 0x112u:
          p_m_scrollbar = &this->m_scrollbar;
          sprintf(
            (char *const)&this->m_scrollbar,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)(int)this->m_scrollbar.m_texarrayInfo[3] * 0.60000002));
          goto LABEL_213;
        case 0x113u:
          p_m_scrollbar = &this->m_scrollbar;
          sprintf(
            (char *const)&this->m_scrollbar,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)(int)this->m_scrollbar.m_texarrayInfo[3] * 0.69999999));
          goto LABEL_213;
        case 0x114u:
          p_m_scrollbar = &this->m_scrollbar;
          sprintf(
            (char *const)&this->m_scrollbar,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)(int)this->m_scrollbar.m_texarrayInfo[3] * 0.80000001));
          goto LABEL_213;
        case 0x115u:
          p_m_scrollbar = &this->m_scrollbar;
          sprintf(
            (char *const)&this->m_scrollbar,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)(int)this->m_scrollbar.m_texarrayInfo[3] * 0.89999998));
          goto LABEL_213;
        default:
          return 1;
      }
      return 1;
    case 1003:
      if ( (unsigned int)pszBuf >= 0x111 && (unsigned int)pszBuf <= 0x115 )
      {
        p_m_scrollbar = &this->m_scrollbar;
        sprintf((char *const)&this->m_scrollbar, "%s %d", g_szCombatFieldName, this->m_scrollbar.m_texarrayInfo[3]);
LABEL_213:
        ((UICaption *)((char *)this + 101832))->SetEnable((int)p_m_scrollbar, 0);
      }
      return 1;
    case 1005:
      (**((void ( ***)(char *, _DWORD))this + 25115))((char *)this + 100460, 0);
      (**((void ( ***)(char *, _DWORD))this + 25201))((char *)this + 100804, 0);
      (**((void ( ***)(char *, _DWORD))this + 26299))((char *)this + 105196, 0);
      return 1;
    case 1007:
      this->m_scrollbar.m_texarray.m_num = nVal2;
      if ( nVal2 > -1 )
      {
        if ( *(&this->m_scrollbar.m_texarrayInfo[0]->filepos + nVal2) <= 0
          || *(int *)(*((_DWORD *)this + 23399) + 4 * nVal2) > 0 )
        {
          ((PAL3 *)this)->GetValue(0);
        }
        else
        {
          *((_BYTE *)this + 93440) = 0;
          ((UICaption *)((char *)this + 95748))->SetEnable((int)g_szSceneUIText, 0);
          (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
          ((PAL3 *)this)->GetValue(1u);
        }
        ((UICaption *)((char *)this + 95748))->SetEnable((int)g_szSceneUIText, 0);
        (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
        ((PlayerMgr *)this)->CreatePanelElements((CCBUIPanel *)this->m_scrollbar.m_texarray.m_num);
        ((PlayerMgr *)this)->SetupPlayerDisplay(this->m_scrollbar.m_texarray.m_num);
        ((CCBSystem *)this)->InitResultWindow();
        switch ( *(_BYTE *)(*((_DWORD *)this + this->m_scrollbar.m_texarray.m_num + 3970) + 612) )
        {
          case 7:
          case 8:
          case 9:
          case 0xA:
          case 0xB:
            ((UIStatic *)((char *)this + 98900))->CreateFromTemplate();
            break;
          default:
            break;
        }
        v40 = (int *)*((_DWORD *)this + this->m_scrollbar.m_texarray.m_num + 3970);
        if ( *((_BYTE *)v40 + 613) == 5 )
        {
          ((CCBFiveNimbusWindow *)((char *)this + 93616))->SetFloatParam(228.0);
          ((Camera *)((char *)this + 93616))->UpdateCameraLookAt(330, 280, 600);
        }
        else if ( *((_BYTE *)v40 + 612) == 11 )
        {
          ((CCBFiveNimbusWindow *)((char *)this + 93616))->SetFloatParam(228.0);
          ((Camera *)((char *)this + 93616))->UpdateCameraLookAt(330, 272, 600);
        }
        else
        {
          v41 = *v40;
          if ( v41 == 8114 || v41 == 8132 )
          {
            ((CCBFiveNimbusWindow *)((char *)this + 93616))->SetFloatParam(180.0);
            ((Camera *)((char *)this + 93616))->UpdateCameraLookAt(330, 252, 600);
          }
          else
          {
            ((CCBFiveNimbusWindow *)((char *)this + 93616))->SetFloatParam(180.0);
            ((Camera *)((char *)this + 93616))->UpdateCameraLookAt(330, 268, 600);
          }
        }
        if ( !strcmp(
                (const char *)(*((_DWORD *)this + this->m_scrollbar.m_texarray.m_num + 3970) + 36),
                g_szSceneUIText) )
        {
          sprintf((char *const)&this->m_scrollbar, byte_5967B0, "NONE");
        }
        else
        {
          v42 = (const char *)(*((_DWORD *)this + this->m_scrollbar.m_texarray.m_num + 3970) + 36);
          sprintf((char *const)&this->m_scrollbar, "Item\\%s\\%s.pol", v42, v42);
        }
        ((PalScript *)((char *)this + 93688))->LoadModel((const char *)&this->m_scrollbar, 0);
        v43 = *((_DWORD *)this + this->m_scrollbar.m_texarray.m_num + 3970);
        v44 = (const char *)(v43 + 36);
        v45 = (const char *)(v43 + 66);
        if ( !strcmp((const char *)(v43 + 36), g_szSceneUIText) )
        {
          sprintf((char *const)&this->m_scrollbar, byte_5967B0, "NONE");
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v93 = 0;
          v94 = 0;
          sprintf(Buffer, "%s%s", v44, v45);
          sprintf((char *const)&this->m_scrollbar, "Item\\%s\\%s.tga", v44, Buffer);
        }
        ((gbGeomNode *)*((gbGeomNode **)this + 23426))->ReplaceTexture((const char *)&this->m_scrollbar);
        v87 = this->m_scrollbar.m_texarray.m_num;
        *((_DWORD *)this + 23423) = 1;
        GetGridOffset((char *)this + 99204, &pOut, v87);
        v47 = *v46;
        v48 = v46[1];
        *((_DWORD *)this + 26295) = *v46 + 90;
        *((_DWORD *)this + 26296) = v48;
        *((_DWORD *)this + 26297) = v47 + 180;
        *((_DWORD *)this + 26298) = v48 + 32;
        sub_445FA0((char *)this + 105196);
        sprintf(
          (char *const)&this->m_scrollbar,
          "%s:%d",
          (const char *)&g_bSaveFlag,
          99 - *(_DWORD *)(*((_DWORD *)this + 23400) + 4 * this->m_scrollbar.m_texarray.m_num));
        ((UICaption *)((char *)this + 105196))->SetEnable((int)&this->m_scrollbar, 0);
        (**((void ( ***)(char *, int))this + 26299))((char *)this + 105196, 1);
        v49 = *((_DWORD *)this + 25289);
        v50 = (UIListBox *)((char *)this + 100428);
        v51 = v48 - 4;
        v52 = (void *)(v47 + 200);
        if ( v49 )
        {
          if ( v49 != 1 )
          {
LABEL_128:
            (**((void ( ***)(char *, int))this + 25115))((char *)this + 100460, 1);
            (**((void ( ***)(char *, int))this + 25201))((char *)this + 100804, 1);
            sub_445E50((int)this + 100460);
            sub_445E50((int)this + 100804);
            return 1;
          }
          v53 = *((_DWORD *)this + 25288);
          *((_DWORD *)this + 25113) = (char *)v52 + *((_DWORD *)this + 25287);
          *((_DWORD *)this + 25112) = v51;
          *((_DWORD *)this + 25111) = v52;
          *((_DWORD *)this + 25114) = v51 + v53;
          sub_445FA0((char *)this + 100804);
          v54 = *((_DWORD *)this + 25290);
          v55 = *((_DWORD *)this + 25113);
          *((_DWORD *)this + 25108) = *((_DWORD *)this + 25112);
          v56 = (void *)(v54 + v55);
          v57 = *((_DWORD *)this + 25287);
// [VFTABLE] v50->__vftable = v56;
          *((_DWORD *)this + 25109) = (char *)v56 + v57;
          *((_DWORD *)this + 25110) = *((_DWORD *)this + 25114);
          v58 = (char *)this + 100460;
        }
        else
        {
          v59 = v51 + *((_DWORD *)this + 25288);
          *((_DWORD *)this + 25109) = (char *)v52 + *((_DWORD *)this + 25287);
          *((_DWORD *)this + 25108) = v51;
// [VFTABLE] v50->__vftable = v52;
          *((_DWORD *)this + 25110) = v59;
          sub_445FA0((char *)this + 100460);
// [VFTABLE] vftable = v50->__vftable;
          v61 = *((_DWORD *)this + 25110) + *((_DWORD *)this + 25290);
          *((_DWORD *)this + 25112) = v61;
          *((_DWORD *)this + 25111) = vftable;
          *((_DWORD *)this + 25113) = *((_DWORD *)this + 25109);
          v58 = (char *)this + 100804;
          *((_DWORD *)this + 25114) = *((_DWORD *)this + 25288) + v61;
        }
        sub_445FA0(v58);
        goto LABEL_128;
      }
      this->m_scrollbar.m_texarrayInfo[4] = 0;
      do
      {
        if ( this->m_scrollbar.m_texarrayInfo[4][45].name[(unsigned int)this + 64] )
        {
          this->m_scrollbar.m_texarrayInfo[5] = 0;
          do
          {
            (**((void ( ***)(char *, _DWORD))this
              + 45 * ((int)this->m_scrollbar.m_texarrayInfo[5] + 6 * (int)this->m_scrollbar.m_texarrayInfo[4])
              + 20870))(
              (char *)this
            + 180 * ((int)this->m_scrollbar.m_texarrayInfo[5] + 6 * (int)this->m_scrollbar.m_texarrayInfo[4])
            + 83480,
              0);
            this->m_scrollbar.m_texarrayInfo[6] = 0;
            do
            {
              (**((void ( ***)(char *, _DWORD))this
                + 38
                * ((int)this->m_scrollbar.m_texarrayInfo[6]
                 + 8 * ((int)this->m_scrollbar.m_texarrayInfo[5] + 6 * (int)this->m_scrollbar.m_texarrayInfo[4]))
                + 6589))(
                (char *)this
              + 152
              * ((int)this->m_scrollbar.m_texarrayInfo[6]
               + 8 * ((int)this->m_scrollbar.m_texarrayInfo[5] + 6 * (int)this->m_scrollbar.m_texarrayInfo[4]))
              + 26356,
                0);
              v62 = (_PlugInfo *)((char *)&this->m_scrollbar.m_texarrayInfo[6]->filepos + 1);
              this->m_scrollbar.m_texarrayInfo[6] = v62;
            }
            while ( (int)v62 < 8 );
            v63 = (_PlugInfo *)((char *)&this->m_scrollbar.m_texarrayInfo[5]->filepos + 1);
            this->m_scrollbar.m_texarrayInfo[5] = v63;
          }
          while ( (int)v63 < 6 );
        }
        v64 = (_PlugInfo *)((char *)&this->m_scrollbar.m_texarrayInfo[4]->filepos + 1);
        this->m_scrollbar.m_texarrayInfo[4] = v64;
      }
      while ( (int)v64 < 5 );
      ((UICaption *)((char *)this + 101328))->SetEnable((int)g_szSceneUIText, 0);
      *((_DWORD *)this + 23423) = 0;
      (**((void ( ***)(char *, _DWORD))this + 25115))((char *)this + 100460, 0);
      (**((void ( ***)(char *, _DWORD))this + 25201))((char *)this + 100804, 0);
      (**((void ( ***)(char *, _DWORD))this + 26299))((char *)this + 105196, 0);
      return ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nVal2);
    case 1009:
      if ( *((_BYTE *)this + 105862) )
        goto LABEL_156;
      this->m_scrollbar.m_texarrayInfo[4] = 0;
      while ( 2 )
      {
        v65 = this->m_scrollbar.m_texarrayInfo[4];
        if ( !*((_BYTE *)this + (_DWORD)v65 + 26348) )
          goto LABEL_147;
        if ( pszBuf == (char *)dword_56B4DC[(_DWORD)v65] )
        {
          ((PlayerMgr *)this)->HandleInput((int)this->m_scrollbar.m_texarrayInfo[4], 0, this->m_scrollbar.m_texarray.m_num);
        }
        else if ( pszBuf == (char *)dword_56B4F0[(_DWORD)v65] )
        {
          ((PlayerMgr *)this)->HandleInput((int)this->m_scrollbar.m_texarrayInfo[4], 3, this->m_scrollbar.m_texarray.m_num);
        }
        else if ( pszBuf == (&off_56B504)[(_DWORD)v65] )
        {
          ((PlayerMgr *)this)->HandleInput((int)this->m_scrollbar.m_texarrayInfo[4], 4, this->m_scrollbar.m_texarray.m_num);
        }
        else if ( pszBuf == (&off_56B518)[(_DWORD)v65] )
        {
          ((PlayerMgr *)this)->HandleInput((int)this->m_scrollbar.m_texarrayInfo[4], 2, this->m_scrollbar.m_texarray.m_num);
        }
        else if ( pszBuf == (&off_56B52C)[(_DWORD)v65] )
        {
          ((PlayerMgr *)this)->HandleInput((int)this->m_scrollbar.m_texarrayInfo[4], 5, this->m_scrollbar.m_texarray.m_num);
        }
        else
        {
          if ( pszBuf != (char *)dword_56B540[(_DWORD)v65] )
          {
LABEL_147:
            v66 = (_PlugInfo *)((char *)&v65->filepos + 1);
            this->m_scrollbar.m_texarrayInfo[4] = v66;
            if ( (int)v66 >= 5 )
              goto LABEL_156;
            continue;
          }
          ((PlayerMgr *)this)->HandleInput((int)this->m_scrollbar.m_texarrayInfo[4], 1, this->m_scrollbar.m_texarray.m_num);
        }
        break;
      }
      *((_BYTE *)this + 93471) = 1;
LABEL_156:
      if ( *((_BYTE *)this + 93471) )
      {
        *((_BYTE *)this + 93471) = 0;
        return 1;
      }
      if ( pszBuf != (char *)265 )
        return 1;
      v67 = *((_DWORD *)this + 23975);
      v68 = HIWORD(nVal2);
      this->m_scrollbar.m_texarrayInfo[1] = (_PlugInfo *)(unsigned __int16)nVal2;
      this->m_scrollbar.m_texarrayInfo[2] = (_PlugInfo *)HIWORD(nVal2);
      if ( (unsigned __int16)nVal2 <= v67
        || (unsigned __int16)nVal2 >= *((int *)this + 23977)
        || v68 <= *((_DWORD *)this + 23976)
        || v68 >= *((_DWORD *)this + 23978) )
      {
        return 1;
      }
      if ( *((_BYTE *)this + 105876) )
      {
        if ( *((int *)this + 26466) < 1 )
        {
          (**((void ( ***)(char *, int))this + 23937))((char *)this + 95748, 1);
          v69 = *((_DWORD *)this + 26466) + 1;
          *((_DWORD *)this + 26466) = v69;
          ((UICaption *)((char *)this + 95748))->SetEnable((int)this + 256 * v69 + 105350, 0);
          (**((void ( ***)(char *, int))this + 6332))((char *)this + 25328, 1);
        }
        else
        {
          ((PAL3 *)this)->SetValue(1u);
          *((_BYTE *)this + 105876) = 0;
          *((_DWORD *)this + 26466) = 0;
          ((UICaption *)((char *)this + 95748))->SetEnable((int)g_szSceneUIText, 0);
          (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
        }
        return 1;
      }
      switch ( *((_DWORD *)this + 26468) )
      {
        case 0:
          ((PAL3 *)this)->SetValue(1u);
          (**((void ( ***)(char *, _DWORD))this + 23937))((char *)this + 95748, 0);
          ((UICaption *)((char *)this + 95748))->SetEnable((int)g_szSceneUIText, 0);
          (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
          *((_DWORD *)this + 26466) = 0;
          break;
        case 1:
          if ( *((_BYTE *)this + 105349) )
          {
            (**((void ( ***)(char *, int))this + 23937))((char *)this + 95748, 1);
            ((UICaption *)((char *)this + 95748))->SetEnable((int)g_szSceneUIText, 0);
            (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
            *((_DWORD *)this + 26466) = 0;
            ((PAL3 *)this)->SetValue(0);
            ((PAL3 *)this)->SetRange(1u);
            sub_445E50((int)this + 99204);
            ((SaleUI *)this)->DestroySubFrames();
            ((UIFrameWnd *)*((UIFrameWnd **)this + 26476))->OnPaintUpdate();
          }
          else
          {
            ((PAL3 *)this)->SetValue(0);
            ((PAL3 *)this)->SetRange(1u);
            sub_445E50((int)this + 99204);
            ((UICaption *)((char *)this + 95748))->SetEnable((int)g_szSceneUIText, 0);
            (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
          }
          break;
        case 2:
          v70 = *((_DWORD *)this + 26466);
          if ( *((_BYTE *)this + 105349) )
          {
            if ( v70 < 1 )
            {
              v71 = *((_DWORD *)this + 26471) << 8;
              *((_DWORD *)this + 26466) = v70 + 1;
              ((UICaption *)((char *)this + 95748))->SetEnable((int)this + v71 + 12992, 0);
              (**((void ( ***)(char *, int))this + 6332))((char *)this + 25328, 1);
            }
            else
            {
              *((_DWORD *)this + 26466) = 0;
              ((PAL_GDB *)this)->UpdateSkillPanel();
              ((SaleUI *)this)->DestroySubFrames();
              ((UIFrameWnd *)*((UIFrameWnd **)this + 26476))->OnPaintUpdate();
            }
          }
          else if ( v70 < 1 )
          {
            v72 = v70 + 1;
            *((_DWORD *)this + 26466) = v72;
            ((UICaption *)((char *)this + 95748))->SetEnable((int)this + 256 * v72 + 10432, 0);
            (**((void ( ***)(char *, int))this + 6332))((char *)this + 25328, 1);
          }
          else
          {
            *((_DWORD *)this + 26466) = 0;
            ((PAL3 *)this)->SetValue(0);
            ((PAL3 *)this)->SetRange(1u);
            sub_445E50((int)this + 99204);
          }
          break;
        case 3:
          ((PAL3 *)this)->EnterGameMode(4);
          break;
        default:
          break;
      }
      if ( *((int *)this + 26468) < 0 && *((_BYTE *)this + 105348) )
      {
        ((UICaption *)((char *)this + 95748))->SetEnable((int)g_szSceneUIText, 0);
        (**((void ( ***)(char *, _DWORD))this + 23937))((char *)this + 95748, 0);
        (**((void ( ***)(char *, _DWORD))this + 6332))((char *)this + 25328, 0);
        *((_BYTE *)this + 105348) = 0;
        return 1;
      }
      return 1;
    case 1010:
      if ( *((_BYTE *)this + 105862) )
        goto LABEL_202;
      this->m_scrollbar.m_texarrayInfo[4] = 0;
      while ( 2 )
      {
        v73 = this->m_scrollbar.m_texarrayInfo[4];
        if ( !*((_BYTE *)this + (_DWORD)v73 + 26348) )
          goto LABEL_193;
        if ( pszBuf == (char *)dword_56B554[(_DWORD)v73] )
        {
          ((SaleUI *)this)->Update((int)this->m_scrollbar.m_texarrayInfo[4], 0);
        }
        else if ( pszBuf == (char *)dword_56B568[(_DWORD)v73] )
        {
          ((SaleUI *)this)->Update((int)this->m_scrollbar.m_texarrayInfo[4], 3);
        }
        else if ( pszBuf == (char *)dword_56B57C[(_DWORD)v73] )
        {
          ((SaleUI *)this)->Update((int)this->m_scrollbar.m_texarrayInfo[4], 4);
        }
        else if ( pszBuf == (char *)dword_56B590[(_DWORD)v73] )
        {
          ((SaleUI *)this)->Update((int)this->m_scrollbar.m_texarrayInfo[4], 2);
        }
        else if ( pszBuf == (char *)dword_56B5A4[(_DWORD)v73] )
        {
          ((SaleUI *)this)->Update((int)this->m_scrollbar.m_texarrayInfo[4], 5);
        }
        else
        {
          if ( pszBuf != (char *)dword_56B5B8[(_DWORD)v73] )
          {
LABEL_193:
            v74 = (_PlugInfo *)((char *)&v73->filepos + 1);
            this->m_scrollbar.m_texarrayInfo[4] = v74;
            if ( (int)v74 >= 5 )
              goto LABEL_202;
            continue;
          }
          ((SaleUI *)this)->Update((int)this->m_scrollbar.m_texarrayInfo[4], 1);
        }
        break;
      }
      *((_BYTE *)this + 93471) = 1;
LABEL_202:
      if ( *((_BYTE *)this + 93471) )
      {
        *((_BYTE *)this + 93471) = 0;
        return ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nVal2);
      }
      return 1;
    default:
      return ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nVal2);
  }
}

// 0x00470A60
int UIListBox::InitWithPalScript(int nVal, int nVal2)
{
  UIListBox *v4; // eax
  int v5; // ecx
  UIListBox *v6; // eax
  int v7; // ecx
  int v8; // eax

  this->m_showGrayBk = 800;
  *(_DWORD *)&this->m_hasKeyCtrl = 600;
  this->m_column[1].items.m_nSize = -1;
  HIWORD(this->m_column[1].items.m_needscriptdel) = 0;
  *((_DWORD *)this + 3623) = 0;
  *((_DWORD *)this + 3624) = 0;
  memset((char *)this + 14500, 0, 0x640u);
  memset((char *)this + 17700, 0, 0x190u);
  memset((char *)this + 16100, 0, 0x640u);
  this->m_column[1].items.m_needscriptdel = 0;
  v4 = (UIListBox *)((char *)this + 46832);
  v5 = 1794;
  do
  {
// [VFTABLE] v4->__vftable = (vtbl_0056AE2C *)0xFFFF;
    v4->m_fontcolor.Color = 0;
    v4->m_wndcolor.Color = 0;
    v4 = (UIListBox *)((char *)v4 + 12);
    --v5;
  }
  while ( v5 );
  v6 = (UIListBox *)((char *)this + 68360);
  v7 = 1794;
  do
  {
// [VFTABLE] v6->__vftable = (vtbl_0056AE2C *)0xFFFF;
    v6->m_fontcolor.Color = 0;
    v6->m_wndcolor.Color = 0;
    v6 = (UIListBox *)((char *)v6 + 12);
    --v7;
  }
  while ( v7 );
  *((_DWORD *)this + 25163) = 0;
  sub_4422E0((char *)this + 100672);
  ((UI3DCtrl *)((char *)this + 100824))->ctor_D830();
  sub_4422E0((char *)this + 100908);
  UIScene::GetSys();
  *((_DWORD *)this + 25606) = 250;
  *((_DWORD *)this + 25607) = 150;
  ((ARC_PlayerAtt *)((char *)this + 102448))->Refresh();
  ((UIProgressBar *)((char *)this + 103816))->ctor();
  sub_4422E0((char *)this + 104140);
  sub_4422E0((char *)this + 104292);
  sub_4422E0((char *)this + 104444);
  sub_4422E0((char *)this + 104596);
  sub_4422E0((char *)this + 107100);
  ((UI3DCtrl *)((char *)this + 111768))->ctor_D830();
  sub_4422E0((char *)this + 111852);
  ((UIListBox *)((char *)this + 113844))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 115056))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 116268))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 117480))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 118692))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 119904))->UpdateKeyCtrl();
  *((_DWORD *)this + 30279) = 0;
  *((_DWORD *)this + 30280) = 0;
  UIScene::GetSys();
  UIScene::GetSys();
  *((_DWORD *)this + 30461) = 32;
  *((_DWORD *)this + 30462) = 16;
  *((_DWORD *)this + 30463) = 0;
  *((_DWORD *)this + 30464) = 0;
  UIScene::GetSys();
  UIScene::GetSys();
  *((_DWORD *)this + 30640) = -1;
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0((char *)this + 123268);
  sub_4422E0((char *)this + 123420);
  sub_4422E0((char *)this + 123572);
  sub_4422E0((char *)this + 123740);
  sub_4422E0((char *)this + 123908);
  sub_4422E0((char *)this + 124076);
  *((_BYTE *)this + 124244) = 0;
  *((_BYTE *)this + 124245) = 0;
  *((_DWORD *)this + 31062) = 0;
  *((_DWORD *)this + 30278) = 0;
  *((_DWORD *)this + 29975) = 0;
  *((_DWORD *)this + 29672) = 0;
  *((_DWORD *)this + 29369) = 0;
  *((_DWORD *)this + 29066) = 0;
  *((_DWORD *)this + 28763) = 0;
  *((_BYTE *)this + 46828) = 0;
  *((_BYTE *)this + 102440) = 1;
  *((_BYTE *)this + 102444) = 0;
  *((_BYTE *)this + 102443) = 0;
  *((_BYTE *)this + 102442) = 0;
  *((_BYTE *)this + 102441) = 0;
  memset((char *)this + 46832, 0, 0x5418u);
  memset((char *)this + 68360, 0, 0x5418u);
  memset((char *)this + 18100, 0, 0x3810u);
  memset((char *)this + 32452, 0, 0x1C08u);
  memset((char *)this + 39628, 0, 0x1C08u);
  memset((char *)this + 89888, 0, 0x1C08u);
  memset((char *)this + 46804, 0, 0x18u);
  lstrcpyA((LPSTR)this + 104764, g_szSceneUIText);
  v8 = *(_DWORD *)&this->m_hasKeyCtrl;
  *((_DWORD *)this + 25606) = 68;
  *((_DWORD *)this + 25608) = 65;
  *((_DWORD *)this + 25607) = v8 / 4;
  *((_DWORD *)this + 25609) = 86;
  *((_BYTE *)this + 124264) = 1;
  return (int)this;
}

// 0x0049CF20
int UIListBox::GetSkillSlotLevel(int nVal, int nVal2)
{
  int v3; // esi
  _BYTE *v4; // edx
  int v5; // eax
  _DWORD *v6; // ecx

  v3 = 0;
  v4 = &Buffer.m_partyActor.m_bDirFlag + 1408 * nVal + 32;
  while ( 2 )
  {
    v5 = 0;
    v6 = v4;
    do
    {
      if ( nVal2 == *v6 )
        return *((unsigned __int8 *)&Buffer.m_FrameA.m_bfocus + 1408 * nVal + 8 * v3 + v5);
      ++v5;
      ++v6;
    }
    while ( v5 < 8 );
    ++v3;
    v4 += 32;
    if ( v3 < 6 )
      continue;
    break;
  }
  return 0;
}

// 0x004A9870
int UIListBox::_todo_4A9870()
{
  int result; // eax
  signed int v2; // ebp
  UIListBox *v4; // edi
  char *p_right; // esi
  int *v6; // eax
  int v7; // ebx
  char *v8; // esi
  int *v9; // eax
  int v10; // ebx
  char *v11; // esi
  int *v12; // eax
  int v13; // ebx
  char *v14; // esi
  int *v15; // eax
  int v16; // ebx
  char *v17; // esi
  int *v18; // eax
  int v19; // ebx
  int *v20; // [esp+0x0] [ebp-0x5C]
  int sel; // [esp+0x10] [ebp-0x4C]
  int v22; // [esp+0x14] [ebp-0x48] BYREF
  int v23; // [esp+0x18] [ebp-0x44]
  int v24; // [esp+0x1C] [ebp-0x40]
  _BYTE pOut[12]; // [esp+0x20] [ebp-0x3C] BYREF
  _BYTE v26[12]; // [esp+0x2C] [ebp-0x30] BYREF
  _BYTE v27[12]; // [esp+0x38] [ebp-0x24] BYREF
  _BYTE v28[12]; // [esp+0x44] [ebp-0x18] BYREF
  _BYTE v29[12]; // [esp+0x50] [ebp-0xC] BYREF
  CCBStageRole *v30; // [esp+0x60] [ebp+0x4]
  CCBStageRole *v31; // [esp+0x60] [ebp+0x4]
  CCBStageRole *v32; // [esp+0x60] [ebp+0x4]
  CCBStageRole *v33; // [esp+0x60] [ebp+0x4]
  CCBStageRole *v34; // [esp+0x60] [ebp+0x4]
  CCBStageRole *v35; // [esp+0x60] [ebp+0x4]

  result = (int)v30;
  v2 = 0;
  v22 = 0xFFFF;
  v23 = 0;
  v24 = 0;
  switch ( (unsigned int)v30 )
  {
    case 0u:
      v4 = (UIListBox *)((char *)this + 389984);
      sel = *((_DWORD *)this + 97559);
      ((UIListBox *)((char *)this + 389984))->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(7);
      if ( *((int *)this + 100009) >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(*((void **)this + 100009));
      v31 = (CCBStageRole *)((char *)this + 400040);
      ((CCBStageRole *)((char *)this + 400040))->Reset();
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        p_right = (char *)&this->m_scrollbar.m_rect.right;
        do
        {
          v6 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, v2);
          v22 = *v6;
          v23 = v6[1];
          v24 = v6[2];
          v7 = ((UIListBox *)v4)->SetItemOffset((char *)(v24 + 4), 0);
          sprintf(p_right, &dir[20], v23);
          ((UIListBox *)v4)->SetMouseMoveSel(1, v7, p_right, 0);
          sprintf(p_right, &dir[20], *(_DWORD *)(v24 + 624));
          ((UIListBox *)v4)->SetMouseMoveSel(2, v7, p_right, 0);
          sprintf(p_right, &dir[20], *(_DWORD *)(v24 + 608) / 2);
          ((UIListBox *)v4)->SetMouseMoveSel(3, v7, p_right, 0);
          ((CCBStageRole *)v31)->GetAlive((int)&v22, v20);
          ++v2;
        }
        while ( v2 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
      goto LABEL_31;
    case 1u:
      v4 = (UIListBox *)((char *)this + 391192);
      sel = *((_DWORD *)this + 97861);
      ((UIListBox *)((char *)this + 391192))->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(11);
      if ( *((int *)this + 100009) >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(*((void **)this + 100009));
      v32 = (CCBStageRole *)((char *)this + 400040);
      ((CCBStageRole *)((char *)this + 400040))->Reset();
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        v8 = (char *)&this->m_scrollbar.m_rect.right;
        do
        {
          v9 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v26, v2);
          v22 = *v9;
          v23 = v9[1];
          v24 = v9[2];
          v10 = ((UIListBox *)v4)->SetItemOffset((char *)(v24 + 4), 0);
          sprintf(v8, &dir[20], v23);
          ((UIListBox *)v4)->SetMouseMoveSel(1, v10, v8, 0);
          sprintf(v8, &dir[20], *(_DWORD *)(v24 + 624));
          ((UIListBox *)v4)->SetMouseMoveSel(2, v10, v8, 0);
          sprintf(v8, &dir[20], *(_DWORD *)(v24 + 608) / 2);
          ((UIListBox *)v4)->SetMouseMoveSel(3, v10, v8, 0);
          ((CCBStageRole *)v32)->GetAlive((int)&v22, v20);
          ++v2;
        }
        while ( v2 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
      goto LABEL_31;
    case 2u:
      v4 = (UIListBox *)((char *)this + 392400);
      sel = *((_DWORD *)this + 98163);
      ((UIListBox *)((char *)this + 392400))->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(12);
      if ( *((int *)this + 100009) >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(*((void **)this + 100009));
      v33 = (CCBStageRole *)((char *)this + 400040);
      ((CCBStageRole *)((char *)this + 400040))->Reset();
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        v11 = (char *)&this->m_scrollbar.m_rect.right;
        do
        {
          v12 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v27, v2);
          v22 = *v12;
          v23 = v12[1];
          v24 = v12[2];
          v13 = ((UIListBox *)v4)->SetItemOffset((char *)(v24 + 4), 0);
          sprintf(v11, &dir[20], v23);
          ((UIListBox *)v4)->SetMouseMoveSel(1, v13, v11, 0);
          sprintf(v11, &dir[20], *(_DWORD *)(v24 + 624));
          ((UIListBox *)v4)->SetMouseMoveSel(2, v13, v11, 0);
          sprintf(v11, &dir[20], *(_DWORD *)(v24 + 608) / 2);
          ((UIListBox *)v4)->SetMouseMoveSel(3, v13, v11, 0);
          ((CCBStageRole *)v33)->GetAlive((int)&v22, v20);
          ++v2;
        }
        while ( v2 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
      goto LABEL_31;
    case 3u:
      v4 = (UIListBox *)((char *)this + 393608);
      sel = *((_DWORD *)this + 98465);
      ((UIListBox *)((char *)this + 393608))->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(13);
      if ( *((int *)this + 100009) >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(*((void **)this + 100009));
      v34 = (CCBStageRole *)((char *)this + 400040);
      ((CCBStageRole *)((char *)this + 400040))->Reset();
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        v14 = (char *)&this->m_scrollbar.m_rect.right;
        do
        {
          v15 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v28, v2);
          v22 = *v15;
          v23 = v15[1];
          v24 = v15[2];
          v16 = ((UIListBox *)v4)->SetItemOffset((char *)(v24 + 4), 0);
          sprintf(v14, &dir[20], v23);
          ((UIListBox *)v4)->SetMouseMoveSel(1, v16, v14, 0);
          sprintf(v14, &dir[20], *(_DWORD *)(v24 + 624));
          ((UIListBox *)v4)->SetMouseMoveSel(2, v16, v14, 0);
          sprintf(v14, &dir[20], *(_DWORD *)(v24 + 608) / 2);
          ((UIListBox *)v4)->SetMouseMoveSel(3, v16, v14, 0);
          ((CCBStageRole *)v34)->GetAlive((int)&v22, v20);
          ++v2;
        }
        while ( v2 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
      goto LABEL_31;
    case 4u:
      v4 = (UIListBox *)((char *)this + 394816);
      sel = *((_DWORD *)this + 98767);
      ((UIListBox *)((char *)this + 394816))->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(9);
      if ( *((int *)this + 100009) >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(*((void **)this + 100009));
      v35 = (CCBStageRole *)((char *)this + 400040);
      ((CCBStageRole *)((char *)this + 400040))->Reset();
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        v17 = (char *)&this->m_scrollbar.m_rect.right;
        do
        {
          v18 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v29, v2);
          v22 = *v18;
          v23 = v18[1];
          v24 = v18[2];
          v19 = ((UIListBox *)v4)->SetItemOffset((char *)(v24 + 4), 0);
          sprintf(v17, &dir[20], v23);
          ((UIListBox *)v4)->SetMouseMoveSel(1, v19, v17, 0);
          sprintf(v17, &dir[20], *(_DWORD *)(v24 + 624));
          ((UIListBox *)v4)->SetMouseMoveSel(2, v19, v17, 0);
          sprintf(v17, &dir[20], *(_DWORD *)(v24 + 608) / 2);
          ((UIListBox *)v4)->SetMouseMoveSel(3, v19, v17, 0);
          ((CCBStageRole *)v35)->GetAlive((int)&v22, v20);
          ++v2;
        }
        while ( v2 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
LABEL_31:
      ((UIListBox *)v4)->SetSel(sel);
      break;
    default:
      return result;
  }
  return result;
}

// 0x004AA1B0
int UIListBox::ResetAllListBoxes()
{

  *(_DWORD *)this->m_column[1].head = 0;
  this->m_column[0].width = 0;
  *(_DWORD *)&this->m_column[1].head[16] = 0;
  *(_DWORD *)&this->m_column[1].head[12] = 0;
  *(_DWORD *)&this->m_column[1].head[8] = 0;
  *(_DWORD *)&this->m_column[1].head[4] = 0;
  *(_DWORD *)&this->m_column[1].head[24] = 0;
  *(_DWORD *)&this->m_column[1].head[20] = 0;
  *((_DWORD *)this + 5862) = 0;
  ((UIListBox *)((char *)this + 389984))->ClearAll();
  ((UIListBox *)((char *)this + 391192))->ClearAll();
  ((UIListBox *)((char *)this + 392400))->ClearAll();
  ((UIListBox *)((char *)this + 393608))->ClearAll();
  return ((UIListBox *)((char *)this + 394816))->ClearAll();
}

// 0x004AA230
int UIListBox::ShowSlotUI()
{
  int v2; // ebx
  char *v3; // ebp
  char *v4; // esi
  int result; // eax
  UIListBox *v6; // esi
  int v7; // ebp
  int v8; // eax
  int v9; // ecx
  int *v10; // [esp+0x0] [ebp-0x1C]
  int v11; // [esp+0x10] [ebp-0xC] BYREF
  void *vftable; // [esp+0x14] [ebp-0x8]
  int SkillNum; // [esp+0x18] [ebp-0x4]

  v2 = 5;
  v3 = (char *)this + 383468;
  v4 = (char *)this + 383468;
  do
  {
    sub_445E50((int)v4);
    v4 += 344;
    --v2;
  }
  while ( v2 );
  sub_445E50((int)v3);
  result = ((UIListBox *)((char *)this + 396024))->GetItemData();
  if ( result > 0 )
  {
    vftable = 0;
    SkillNum = 0;
    v11 = 0xFFFF;
    v6 = (UIListBox *)((char *)this + 21864);
    v7 = result;
    do
    {
      v8 = *(_DWORD *)&v6[-1].m_rowenable[12];
// [VFTABLE] vftable = v6->__vftable;
      v11 = v8;
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v8);
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&v11, v10);

      v9 = *((_DWORD *)this + 5861);
      *((_DWORD *)this + 5862) = 0;
      sprintf((char *const)&this->m_scrollbar.m_rect.right, "%d/%d", 0, v9);
      ((UICaption *)((char *)this + 397552))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      v6 = (UIListBox *)((char *)v6 + 16);
      --v7;
    }
    while ( v7 );
    ((UIListBox *)((char *)this + 396024))->ClearAll();
    memset((char *)this + 21860, 0, 0x630u);
    return 0;
  }
  return result;
}

// 0x004AA320
void UIListBox::InsertUIListBox(void *a2)
{
  int v3; // ebp
  void *v4; // eax
  int *TargetRole; // eax
  int v6; // eax
  CScreenMode *v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  CScreenMode *Instance; // eax
  int v12; // eax
  int v13; // edx
  char v14; // cl
  int v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  tagRECT *i; // eax
  void **v21; // eax
  int v22; // eax
  int v23; // ecx
  const void *v24; // [esp-0x8] [ebp-0x30]
  const void *v25; // [esp-0x8] [ebp-0x30]
  tagRECT *v26; // [esp+0xC] [ebp-0x1C]
  int p_DWORD; // [esp+0x10] [ebp-0x18] BYREF
  int v28; // [esp+0x14] [ebp-0x14]
  int v29; // [esp+0x18] [ebp-0x10]
  char pOut[12]; // [esp+0x1C] [ebp-0xC] BYREF

  v3 = 0;
  if ( *((int *)this + 5461) >= 0 )
  {
    v4 = (void *)*((_DWORD *)this + 100009);
    p_DWORD = 0xFFFF;
    v28 = 0;
    v29 = 0;
    if ( (int)v4 >= 0 )
      ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(v4);
    TargetRole = (int *)((CCBAI *)((char *)this + 400040))->GetTargetRole(pOut);
    p_DWORD = *TargetRole;
    v28 = TargetRole[1];
    v29 = TargetRole[2];
    v6 = *(_DWORD *)(v29 + 624);
    if ( v6 > 0 )
    {
      v8 = *((_DWORD *)this + 5862);
      v9 = *((_DWORD *)this + 5861);
      v10 = v8 + v6;
      *((_DWORD *)this + 5862) = v10;
      if ( v10 <= v9 )
      {
        sprintf((char *const)&this->m_scrollbar.m_rect.right, "%d/%d", v10, v9);
        ((UICaption *)((char *)this + 397552))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
        v12 = v29;
        if ( *(_BYTE *)(v29 + 612) == 11 )
        {
          v13 = *(_DWORD *)&this->m_column[1].head[4];
          ++*(_DWORD *)this->m_column[1].head;
          *(_DWORD *)&this->m_column[1].head[4] = *(__int16 *)(v12 + 650) + v13;
        }
        v14 = *(_BYTE *)(v12 + 612);
        if ( v14 == 7 || v14 == 8 || v14 == 9 || v14 == 10 )
        {
          ++this->m_column[0].width;
          if ( *(_BYTE *)(v12 + 612) == 10 )
          {
            v15 = *(_DWORD *)&this->m_column[1].head[12];
            *(_DWORD *)&this->m_column[1].head[8] += *(__int16 *)(v12 + 650);
            v16 = *(__int16 *)(v12 + 652) + v15;
            v17 = *(_DWORD *)&this->m_column[1].head[20] + 1;
            *(_DWORD *)&this->m_column[1].head[12] = v16;
            *(_DWORD *)&this->m_column[1].head[20] = v17;
          }
          else
          {
            v18 = *(__int16 *)(v12 + 652);
            v19 = *(_DWORD *)&this->m_column[1].head[24] + 1;
            *(_DWORD *)&this->m_column[1].head[16] += v18;
            *(_DWORD *)&this->m_column[1].head[24] = v19;
          }
        }
        if ( ((UIListBox *)((char *)this + 396024))->GetItemData() <= 0 )
        {
LABEL_22:
          v3 = ((UIListBox *)((char *)this + 396024))->SetItemOffset((char *)(v29 + 4), 0);
// [VFTABLE] v21 = &this->__vftable + 4 * v3;
          v21[5465] = (void *)p_DWORD;
          v21[5466] = (void *)((char *)v21[5466] + 1);
          v21[5467] = a2;
          *((_DWORD *)this + 4 * v3 + 5468) = *((_DWORD *)this + 5461);
          v22 = (int)v21[5466];
        }
        else
        {
          for ( i = (tagRECT *)((char *)this + 21860); i->left != p_DWORD; i = v26 )
          {
            ++v3;
            v26 = i + 1;
            if ( v3 >= ((UIListBox *)((char *)this + 396024))->GetItemData() )
              goto LABEL_22;
          }
          v23 = *((_DWORD *)this + 4 * v3 + 5466) + 1;
          *((_DWORD *)this + 4 * v3 + 5466) = v23;
          v22 = v23;
        }
        sprintf((char *const)&this->m_scrollbar.m_rect.right, &dir[20], v22);
        ((UIListBox *)((char *)this + 396024))->SetMouseMoveSel(1, v3, (char *)&this->m_scrollbar.m_rect.right, 0);
        sprintf((char *const)&this->m_scrollbar.m_rect.right, &dir[20], *(_DWORD *)(v29 + 624));
        ((UIListBox *)((char *)this + 396024))->SetMouseMoveSel(2, v3, (char *)&this->m_scrollbar.m_rect.right, 0);
        sprintf((char *const)&this->m_scrollbar.m_rect.right, &dir[20], *(_DWORD *)(v29 + 608) / 2);
        ((UIListBox *)((char *)this + 396024))->SetMouseMoveSel(3, v3, (char *)&this->m_scrollbar.m_rect.right, 0);
        v28 = 1;
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);

      }
      else
      {
        *((_DWORD *)this + 5862) = v8;
        sprintf((char *const)&this->m_scrollbar.m_rect.right, "\\n\\n       %s", (const char *)dword_DC913C);
        ((UICaption *)((char *)this + 400536))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
        ((UIRoleSelect *)((char *)this + 400080))->SetByte(1);
        v25 = off_5CF1F0;
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v25, 1);
      }
    }
    else
    {
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "\\n   %s\\n   %s",
        (const char *)dword_DCEA3C,
        (const char *)dword_DD423C);
      ((UICaption *)((char *)this + 400536))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      ((UIRoleSelect *)((char *)this + 400080))->SetByte(1);
      v24 = off_5CF1F0;
      v7 = CScreenMode::GetInstance();
      ((CScreenMode *)v7)->AudioSetPosition(v24, 1);
    }
  }
}

// 0x004AA680
void UIListBox::ProcessListInput(int a2)
{
  UIListBox *v3; // edi
  char *v4; // ebp
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  char *p_right; // esi
  int v10; // eax
  char v11; // cl
  int ItemData; // ebp
  char *v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // ebx
  int v17; // ebp
  bool v18; // zf
  int *v19; // [esp+0x0] [ebp-0x24]
  char *v20; // [esp+0x10] [ebp-0x14]
  int v21; // [esp+0x10] [ebp-0x14]
  char *v22; // [esp+0x14] [ebp-0x10]
  int v23; // [esp+0x18] [ebp-0xC] BYREF
  int v24; // [esp+0x1C] [ebp-0x8]
  int SkillNum; // [esp+0x20] [ebp-0x4]
  int v26; // [esp+0x28] [ebp+0x4]
  UIListBox *v27; // [esp+0x28] [ebp+0x4]

  if ( a2 >= 0 )
  {
    v3 = (UIListBox *)((char *)this + 396024);
    if ( a2 < ((UIListBox *)((char *)this + 396024))->GetItemData() )
    {
      v23 = 0xFFFF;
      v24 = 0;
      SkillNum = 0;
      if ( ((UIListBox *)((char *)this + 396024))->GetItemData() > 0 )
      {
        v4 = (char *)this + 16 * a2;
        v24 = 1;
        v23 = *((_DWORD *)v4 + 5465);
        SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v23);
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&v23, v19);

        ((CCBCamControl *)this)->ShowAllSlots(*((_DWORD *)this + 5462));
        v5 = SkillNum;
        switch ( *(_BYTE *)(SkillNum + 612) )
        {
          case 7:
          case 8:
          case 9:
            v6 = *(_DWORD *)&this->m_column[1].head[24] - 1;
            --this->m_column[0].width;
            *(_DWORD *)&this->m_column[1].head[24] = v6;
            break;
          case 0xA:
            v7 = *(_DWORD *)&this->m_column[1].head[20] - 1;
            --this->m_column[0].width;
            *(_DWORD *)&this->m_column[1].head[20] = v7;
            break;
          case 0xB:
            --*(_DWORD *)this->m_column[1].head;
            break;
          default:
            break;
        }
        v8 = *((_DWORD *)this + 5862) - *(_DWORD *)(v5 + 624);
        *((_DWORD *)this + 5862) = v8;
        if ( v8 <= 0 )
          *((_DWORD *)this + 5862) = 0;
        p_right = (char *)&this->m_scrollbar.m_rect.right;
        sprintf(
          (char *const)&this->m_scrollbar.m_rect.right,
          "%d/%d",
          *((_DWORD *)this + 5862),
          *((_DWORD *)this + 5861));
        ((UICaption *)((char *)this + 397552))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
        v10 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*((_DWORD *)v4 + 5465));
        if ( *(_BYTE *)(v10 + 612) == 11 )
          *(_DWORD *)&this->m_column[1].head[4] -= *(__int16 *)(v10 + 650);
        v11 = *(_BYTE *)(v10 + 612);
        if ( v11 == 7 || v11 == 8 || v11 == 9 || v11 == 10 )
        {
          if ( v11 == 10 )
          {
            *(_DWORD *)&this->m_column[1].head[8] -= *(__int16 *)(v10 + 650);
            *(_DWORD *)&this->m_column[1].head[12] -= *(__int16 *)(v10 + 652);
          }
          else
          {
            *(_DWORD *)&this->m_column[1].head[16] -= *(__int16 *)(v10 + 652);
          }
        }
        --*((_DWORD *)v4 + 5466);
        ItemData = ((UIListBox *)((char *)this + 396024))->GetItemData();
        v26 = ItemData;
        ((UIListBox *)((char *)this + 396024))->ClearAll();
        v13 = (char *)this + 21860;
        v14 = 0;
        v22 = (char *)this + 21860;
        v20 = (char *)this + 21860;
        do
        {
          if ( *((int *)v13 + 1) <= 0 && *(_DWORD *)v13 )
          {
            if ( v14 < ItemData )
            {
              v15 = ItemData - v14;
              do
              {
                *(_DWORD *)v13 = *((_DWORD *)v13 + 4);
                *((_DWORD *)v13 + 1) = *((_DWORD *)v13 + 5);
                *((_DWORD *)v13 + 2) = *((_DWORD *)v13 + 6);
                v13 += 16;
                --v15;
              }
              while ( v15 );
              ItemData = v26;
              v13 = v20;
            }
            v26 = --ItemData;
          }
          ++v14;
          v13 += 16;
          v20 = v13;
        }
        while ( v14 < 99 );
        if ( ItemData > 0 )
        {
          v21 = ItemData;
          v27 = (UIListBox *)((char *)this + 21864);
          do
          {
            v16 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(_DWORD *)&v27[-1].m_rowenable[12]);
            v17 = ((UIListBox *)v3)->SetItemOffset((char *)(v16 + 4), 0);
// [VFTABLE] sprintf(p_right, &dir[20], v27->__vftable);
            ((UIListBox *)v3)->SetMouseMoveSel(1, v17, p_right, 0);
            sprintf(p_right, &dir[20], *(_DWORD *)(v16 + 624));
            ((UIListBox *)v3)->SetMouseMoveSel(2, v17, p_right, 0);
            sprintf(p_right, &dir[20], *(_DWORD *)(v16 + 608) / 2);
            ((UIListBox *)v3)->SetMouseMoveSel(3, v17, p_right, 0);
            v18 = v21 == 1;
            v27 = (UIListBox *)((char *)v27 + 16);
            --v21;
          }
          while ( !v18 );
        }
        if ( ((UIListBox *)v3)->GetItemData() <= 0 )
        {
          ((UIListBox *)v3)->ClearAll();
          memset(v22, 0, 0x630u);
        }
      }
    }
  }
}

// 0x004B4690
// write access to const memory has been detected, the output may be wrong!
void UIListBox::Reset()
{
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
  this->m_pfather = (UIWnd *)100;
  this->m_childs.m_pData = (char *)200;
  LOBYTE(this->m_childs.capacity) = 0;
  BYTE1(this->m_childs.capacity) = 1;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_needscriptdel = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  this->m_benable = 0;
  LOBYTE(this->m_bfocus) = 1;
  this->m_selcolor.Color = 0;
  this->m_showGrayBk = 0;
  *(_DWORD *)&this->m_hasKeyCtrl = 2;
// [VFTABLE] LOBYTE(this->m_scrollbar.__vftable) = 1;
  LOBYTE(this->m_scrollbar.m_wndcolor.Color) = 0;
  this->m_scrollbar.m_id = 0;
  this->m_scrollbar.m_rect.left = 0;
  this->m_scrollbar.m_rect.top = 0;
  LOBYTE(this->m_scrollbar.m_rect.right) = 1;
  LOBYTE(this->m_scrollbar.m_childs.m_pData) = 0;
  this->m_scrollbar.m_pfather = 0;
  this->m_scrollbar.m_rect.bottom = 0;
  this->m_scrollbar.m_childs.capacity = 10;
  LOBYTE(this->m_scrollbar.m_childs.m_needscriptdel) = 0;
  this->m_scrollbar.m_bcreateok = 1065353216;
  this->m_scrollbar.m_bvisible = 0;
  this->m_scrollbar.m_benable = 0;
  this->m_scrollbar.m_bfocus = 0;
  *(_DWORD *)&this->m_scrollbar.m_bPress = 0;
// [VFTABLE] this->m_scrollbar.m_bk.__vftable = 0;
  this->m_scrollbar.m_bk.m_fontcolor.Color = 0;
  this->m_scrollbar.m_slideroffset = 0;
  sub_4422E0(&this->m_scrollbar.m_slidertboffset);
  *(_DWORD *)&this->m_column[1].head[52] = 0;
  *(_DWORD *)&this->m_column[1].head[56] = 0;
  *(_DWORD *)&this->m_column[1].head[60] = 1058642330;
  this->m_scrollbar.m_childs.m_nSize = -16777216;
  this->m_fontcolor.Color = 100;
// [VFTABLE] this->__vftable = (vtbl_0056AE2C *)100;
  this->m_wndcolor.Color = 200;
  this->m_id = (void *)400;
  gbColorQuad::ColorQuadFmt = 1;
  this->m_scrollbar.m_fontcolor.Color = -16777216;
}

// 0x00519AF0
CCBUI * UIListBox::InitAndRender()
{

  ((CCBUI *)this)->Render();
  return (CCBUI *)this;
}

// 0x00527950
int UIListBox::ctor()
{

  this->m_scrollbar.m_wndcolor.Color = 800;
  this->m_scrollbar.m_id = (void *)600;
  this->m_scrollbar.m_texarrayInfo[3] = 0;
  ((ARC_PlayerAtt *)&this->m_scrollbar.m_texarrayInfo[4])->Refresh();
  *((_DWORD *)this + 431) = 0;
  *((_DWORD *)this + 432) = 0;
  *((_DWORD *)this + 436) = 0;
  *((_BYTE *)this + 1756) = 1;
  return (int)this;
}

// 0x005279F0
void UIListBox::ctor_79F0()
{
  int v2; // ecx
  int v3; // ecx

  v2 = *((_DWORD *)this + 431);
  if ( v2 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v2 + 20))(v2, 1);
    *((_DWORD *)this + 431) = 0;
  }
  v3 = *((_DWORD *)this + 432);
  if ( v3 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *((_DWORD *)this + 432) = 0;
  }
  ((UIRoleDialog *)&this->m_scrollbar.m_texarrayInfo[4])->_UIRoleDialog();
}

// 0x00527D80
int UIListBox::RenderWithSceneMap()
{
  _PlugInfo *v2; // eax
  char *v3; // eax
  int result; // eax
  CCBMagicWindow *v5; // [esp+0x0] [ebp-0x4]

  ((UISceneMap *)this)->Render_527cd0();
  v2 = this->m_scrollbar.m_texarrayInfo[3];
  if ( v2 )
  {
    v3 = (char *)&v2[-1]._tex_uvRT.v + 3;
    if ( v3 )
    {
      result = (int)(v3 - 1);
      if ( !result )
        return (*(int ( **)(_DWORD))(**((_DWORD **)this + 432) + 4))(*((_DWORD *)this + 432));
    }
    else
    {
      return (*(int ( **)(_DWORD))(**((_DWORD **)this + 431) + 4))(*((_DWORD *)this + 431));
    }
  }
  else
  {
    ((CCBControlWindow *)this)->Render(v5);
  }
  return result;
}

// 0x00527DC0
int UIListBox::ProcessInput(int nVal, int nVal2)
{
  int State; // eax
  int result; // eax

  State = ((UIParabolaCtrl *)&this->m_scrollbar.m_texarrayInfo[4])->GetState();
  if ( State )
  {
    if ( State == 1 )
    {
      byte_D92785 = 0;
      ((CScreenMode *)this)->InitSceneAudio(3);
    }
  }
  else
  {
    byte_D92785 = 1;
    ((CScreenMode *)this)->InitSceneAudio(1);
    BYTE1(g_dwUISettings) = 1;
  }
  switch ( (unsigned int)this->m_scrollbar.m_texarrayInfo[3] )
  {
    case 0u:
      this->Update(nVal, nVal2);
      result = 1;
      break;
    case 1u:
      (*(void ( **)(_DWORD, int, int))(**((_DWORD **)this + 431) + 8))(*((_DWORD *)this + 431), nVal, nVal2);
      result = 1;
      break;
    case 2u:
      (*(void ( **)(_DWORD, int, int))(**((_DWORD **)this + 432) + 8))(*((_DWORD *)this + 432), nVal, nVal2);
      result = 1;
      break;
    case 3u:
      ((CGameData *)&g_gamefrm)->Load(*((CUtil **)this + 434));
      goto LABEL_10;
    default:
LABEL_10:
      result = 1;
      break;
  }
  return result;
}

// 0x00527EA0
int UIListBox::OnMessageEx(int nVal, int nVal2, int nVal3)
{
  CScreenMode *Instance; // eax
  const void *v7; // [esp-0xC] [ebp-0x10]

  if ( nVal != 1000 )
    return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
  if ( nVal2 )
  {
    if ( *((_DWORD *)this + 434) )
    {
      byte_D92785 = 1;
      ((CScreenMode *)this)->InitSceneAudio(1);
      BYTE1(g_dwUISettings) = 1;
      return 1;
    }
    sprintf((char *const)&this->m_scrollbar.m_rect, "\\n         %s", (const char *)dword_DC843C);
    ((UICaption *)&this->m_column[4].head[40])->SetEnable((int)&this->m_scrollbar.m_rect, 0);
    ((UIRoleSelect *)&this->m_scrollbar.m_texarrayInfo[4])->SetByte(1);
    v7 = off_5E92A0;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v7, 1);
  }
  return 1;
}

// 0x00532A40
int * UIListBox::ResetRect()
{
  this->m_id = 0;
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
  this->m_pfather = 0;
  this->m_childs.m_pData = 0;
  this->m_childs.capacity = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_needscriptdel = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  this->m_scrollbar.m_childs.m_pData = 0;
  this->m_scrollbar.m_childs.capacity = 0;
  this->m_scrollbar.m_childs.m_nSize = 0;
  ((UITabCtrl *)this)->InitAnimParams();
  return (int *)this;
}

// 0x0053D100
void UIListBox::RefreshList()
{
  ((UIListBox *)&this->m_rect)->ReleaseVtable();

}
