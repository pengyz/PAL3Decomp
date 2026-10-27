#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIListBox.h"
#include "Role/Actor.h"
#include "Combat/CCBControlWindow.h"
#include "Misc/CCBEditor.h"
#include "Combat/CCBMagicWindow.h"
#include "Misc/CCBPanelSlot.h"
#include "Combat/CCBUI.h"
#include "GameBase/GRPinput.h"
#include "GameBase/Logger.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "GameBase/PAL3.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/String.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UIAnimateCtrlEX.h"
#include "Misc/UIBigMap.h"
#include "Misc/UIButton.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UILBColumn.h"
#include "Misc/UIMap.h"
#include "Misc/UIRoleDialog.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UIStatic.h"
#include "Misc/UITabCtrl.h"
#include "Misc/UITextArea.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/_Texture_Info.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

class TextureLibDataBase;

// Unnamed globals (extern)
extern TextureLibDataBase stru_1894B78;

// 0x00431CD0
void UIListBox::RefreshSelection()
{
  (((PalScript *)this))->PalScript::CleanupInstances();
  (((UIListBox *)&this->m_wndcolor))->UIListBox::ReleaseVtable();
}

// 0x00432680
int UIListBox::ReleaseVtable()
{
  int result; // eax

  result = (int)((UIWnd *)this);
  if ( *(_DWORD *)((UIWnd *)this) )
  {
    free(*(void **)((UIWnd *)this));
    *(_DWORD *)((UIWnd *)this) = 0;
  }
  return result;
}

// 0x0043DCD0
UIListBox::UIListBox()
{
  ClearSubArraySlot();
  this->m_selcolor.Color = 0;
  (int *)this;
}

// 0x0043DD10
UIListBox::~UIListBox()
{
  // [overlay-fix 2026-10-27] C2065: Destroy__ovl_03 无定义/声明（IDA overlay 合成名）——待归属定谳
  // Destroy__ovl_03((int)this);
  this->UIWnd::~UIWnd();
}

// 0x0043DD60
void UIListBox::SetSelTexture(int id, int pRect, int nVal, int nVal2, int nVal3)
{
  gbVFileSystem *m_plastsys; // edi
  gbTexture *v8; // eax
  OpenBaseFile v9; // [esp+0x2C] [ebp+0x18] BYREF

  m_plastsys = (gbVFileSystem *)v9.m_plastsys;
  if ( v9.m_plastsys )
  {
    v8 = (gbTexture *)gfxMgr->NewTexture((const char *)m_plastsys);
    this->m_selcolor.Color = (unsigned int)v8;
    if ( v8 )
      (((gbTexture *)v8))->gbTexture::LoadTexture(1);
    ((OpenNULLFile *)&v9)->OpenNULLFile::OpenNULLFile();
  }
  this->UIWnd::Create(id, (tagRECT *)&pRect, 0);
}

// 0x0043DE90
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void UIListBox::Destroy()
{
  this->UIListBox::AddColumn();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x0043DEA0
void UIListBox::AddColumn()
{
  g_fDefaultColumnWidth = 12.0;
}

// 0x0043DEB0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void UIListBox::AddRow()
{
  this->UIListBox::SetSubItem();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x0043DEC0
void UIListBox::SetSubItem()
{
  g_fSubItemOffset = 12.0 + 12.0;
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
  gbRefObject *v2; // ecx

  v2 = (gbRefObject *)((UIWnd *)this);
  if ( v2 )
    (((gbRefObject *)v2))->gbRefObject::Release();
  memset(this, 0, 0x48u);
}

// 0x0043DF10
void UIListBox::CalHeightCount()
{
  (((PtrArray *)&this->m_bfocus))->PtrArray::Clear();
}

// 0x0043DF20
void UIListBox::GetItemPos()
{
  this->UIListBox::GetItemAt();
  (((UIListBox *)&this->m_bfocus))->UIListBox::ReleaseVtable();
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
      v4 = (void *)*(void **)(m_bfocus + 4 * i);
      if ( v4 )
      {
        (((UIListBox *)*(UIListBox **)(m_bfocus + 4 * i)))->UIListBox::Render();
        operator delete(v4);
      }
    }
  }
  (((String *)&this->m_bfocus))->String::Assign(0, -1);
}

// 0x0043DFC0
UIListBox * UIListBox::UpdateKeyCtrl()
{
  char v3; // [esp+0xB] [ebp-0x11]

  ClearSubArraySlot();
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
  (((UIMap *)&this->m_scrollbar))->UIMap::_todo_4410F0();
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
  this->m_pbkpic = ((gbTexture *)0);
  this->m_selpic = ((gbTexture *)0);
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
  this->m_pbkpicInfo = ((_PlugInfo *)0);
  this->m_selpicInfo = ((_PlugInfo *)0);
  this->m_onsel = -1;
  return this;
}

// 0x0043E120
void UIListBox::DeleteRow()
{
  this->UIListBox::Destroy_e520();
  operator delete(*(void **)&this->m_rowenable[4]);
  *(_DWORD *)&this->m_rowenable[4] = 0;
  *(_DWORD *)&this->m_rowenable[8] = 0;
  *(_DWORD *)&this->m_rowenable[12] = 0;
  ((UIMap *)&this->m_scrollbar)->UIMap::UIMap();
  this->UIWnd::~UIWnd();
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
  int v14; // eax
  LONG *v15; // eax
  void ( **v16)(UIScrollBar *, int); // edx
  _BYTE a2[16]; // [esp+0x20] [ebp-0x1C] BYREF
  int v18; // [esp+0x38] [ebp-0x4]

  v7 = lpString;
  if ( lpString )
  {
    ((OpenBaseFile *)&lpString)->OpenBaseFile::OpenBaseFile();
    v18 = 0;
    if ( pData )
    {
      v9 = *(_DWORD *)*(void**)(gfxMgr);
      v10 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(v7);
      this->m_pbkpic = ((gbTexture *)((gbTexture *)gfxMgr->NewTexture((const char *)v10)));
      this->m_pbkpicInfo = ((_PlugInfo *)((_PlugInfo *)(((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(v7)));
    }
    else
    {
      this->m_pbkpic = ((gbTexture *)((gbTexture *)gfxMgr->NewTexture((const char *)v7)));
    }
    m_pbkpic = (gbTexture *)this->m_pbkpic;
    if ( m_pbkpic )
      (((gbTexture *)m_pbkpic))->gbTexture::LoadTexture(1);
    v18 = -1;
    ((OpenNULLFile *)&lpString)->OpenNULLFile::OpenNULLFile();
  }
  this->UIWnd::Create(id, (tagRECT *)p_DWORD, (UIWnd *)parent);
  m_scrollW = this->m_scrollW;
  this->m_hasKeyCtrl = 1;
  v13 = p_DWORD[2] - *p_DWORD;
  this->m_scrollRc.right = v13;
  this->m_scrollRc.left = v13 - m_scrollW;
  this->m_scrollRc.top = 0;
  v14 = (int)((UIWnd *)&this->m_scrollbar);
  this->m_scrollRc.bottom = p_DWORD[3] - p_DWORD[1];
  (*(void ( **)(UIScrollBar *, int, tagRECT *, UIListBox *, char *, int, _DWORD))(v14 + 28))(
    &this->m_scrollbar,
    1,
    &this->m_scrollRc,
    this,
    "UI\\common\\scrollbar",
    1,
    0);
  (((UIScene *)&this->m_scrollbar))->UIScene::SetFirstShow(0);
  this->UIListBox::InitScrollbar();
  v15 = (LONG *)sub_445FE0(a2);
  this->m_scrollRc.left = *v15;
  this->m_scrollRc.top = v15[1];
  this->m_scrollRc.right = v15[2];
  v16 = (void ( **)(UIScrollBar *, int))((UIWnd *)&this->m_scrollbar);
  this->m_scrollRc.bottom = v15[3];
  (*v16)(&this->m_scrollbar, nVal);
}

// 0x0043E330
void UIListBox::GetSel(int nVal, int nVal2)
{
  int v3; // edi
  gbTexture *v5; // eax

  v3 = nVal;
  if ( nVal )
  {
    ((OpenBaseFile *)&nVal)->OpenBaseFile::OpenBaseFile();
    v5 = (gbTexture *)gfxMgr->NewTexture((const char *)v3);
    this->m_selpic = ((gbTexture *)(v5));
    if ( v5 )
      (((gbTexture *)v5))->gbTexture::LoadTexture(1);
    ((OpenNULLFile *)&nVal)->OpenNULLFile::OpenNULLFile();
  }
}

// 0x0043E3B0
int UIListBox::GetLockSel(int nVal, int *p_DWORD, int nVal2, int nVal3, char pData)
{
  int result; // eax
  LONG top; // ecx
  LONG v9; // edx

  if ( nVal )
    CCBUI_LoadTextureSequence(nVal);
  this->m_scrollRc.left = *p_DWORD;
  this->m_scrollRc.top = p_DWORD[1];
  this->m_scrollRc.right = p_DWORD[2];
  this->m_scrollRc.bottom = p_DWORD[3];
  this->m_scrollRc.left = this->m_scrollRc.right - nVal2;
  (((UIWnd *)&this->m_scrollbar))->UIWnd::sub_445FA0(&this->m_scrollRc);
  result = nVal3;
  top = this->m_scrollbar.m_btnrect[1].top;
  v9 = nVal3 + this->m_scrollbar.m_btnrect[0].top;
  this->m_scrollbar.m_btnH = nVal3;
  this->m_scrollbar.m_btnrect[0].bottom = v9;
  this->m_scrollbar.m_btnrect[1].bottom = nVal3 + top;
  this->m_scrollW = nVal2;
  return result;
}

// 0x0043E440
void UIListBox::SetSel(int sel)
{
  int m_max; // eax

  this->UIListBox::InitScrollbar();
  m_max = sel;
  if ( sel >= this->m_scrollbar.m_max )
    m_max = this->m_scrollbar.m_max;
  if ( m_max <= this->m_scrollbar.m_min )
    m_max = this->m_scrollbar.m_min;
  this->m_firstshow = m_max;
  (((UIScene *)&this->m_scrollbar))->UIScene::SetFirstShow(m_max);
}

// 0x0043E480
int UIListBox::OnMessage(int height, int nVal, int nVal2)
{
  int m_firstshow; // edi
  int Child; // eax
  UIWnd *m_pfather; // ecx
  UIWnd *v9; // ecx

  if ( height != 1005 )
    return this->UIWnd::OnMessage(height, nVal, nVal2);
  if ( this->m_movesel )
  {
    m_firstshow = this->m_firstshow;
    this->m_firstshow = nVal2;
    Child = this->UIListBox::CreateChild();
    if ( Child == -1 )
    {
      this->m_firstshow = m_firstshow;
    }
    else if ( *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * Child) )
    {
      m_pfather = this->m_pfather;
      if ( m_pfather )
        m_pfather->OnMessage(1006, this->m_id, Child);
    }
  }
  else
  {
    this->m_firstshow = nVal2;
  }
  v9 = this->m_pfather;
  if ( v9 )
    v9->OnMessage(1005, 0, 0);
  return 1;
}

// 0x0043E520
void UIListBox::Destroy_e520()
{
  gbTexture *m_pbkpic; // ecx

  this->UIListBox::ClearAll();
  m_pbkpic = (gbTexture *)this->m_pbkpic;
  this->m_numcol = 0;
  if ( m_pbkpic )
  {
    (((gbRefObject *)m_pbkpic))->gbRefObject::Release();
    this->m_pbkpic = ((gbTexture *)0);
  }
  (((SceneObj *)this))->SceneObj::HideAll() /* [ROWTABLE] */;
}

// 0x0043E560
int UIListBox::SetColumnHead(int nVal, int nOffset)
{
  int result; // eax

  strncpy(this->m_column[this->m_numcol].head, (const char *)nVal, 0x40u);
  this->m_column[this->m_numcol].width = nOffset;
  result = this->m_numcol + 1;
  this->m_numcol = result;
  return result;
}

// 0x0043E5C0
int UIListBox::LoadListItems(char *Source, int y)
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
  int pVal; // [esp+0x10] [ebp-0x814] BYREF
  OpenBaseFile v18; // [esp+0x14] [ebp-0x810] BYREF
  char pExceptionObject[1024]; // [esp+0x18] [ebp-0x80C] BYREF
  char ArgList[1024]; // [esp+0x418] [ebp-0x40C] BYREF
  int v21; // [esp+0x820] [ebp-0x4]

  v4 = (UIListBox *)operator new(0x48u);
  if ( !v4 || (SubItemInfo = (((UIListBox *)v4))->UIListBox::GetSubItemInfo()) == 0 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException(&path[164], "D:\\Project\\PAL3\\UI\\UIListBox.cpp", 260),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( y )
  {
    v21 = 0;
    v6 = (gbTexture *)gfxMgr->NewTexture((const char *)Source);
    *(_DWORD *)((UIWnd *)SubItemInfo) = (_DWORD)v6;
    if ( v6 )
      (((gbTexture *)v6))->gbTexture::LoadTexture(1);
    v21 = -1;
    ((OpenNULLFile *)&v18)->OpenNULLFile::OpenNULLFile();
  }
  else
  {
    strncpy((char *)&SubItemInfo->m_fontcolor, Source, 0x40u);
    SubItemInfo->m_selcolor.Color = this->m_fontcolor.Color;
  }
  capacity = this->m_column[0].items.capacity;
  (((PtrArray *)&this->m_column[0].items))->PtrArray::SetAt(capacity, (int)SubItemInfo);
  v8 = 1;
  if ( this->m_numcol > 1 )
  {
    p_items = (PtrArray *)&this->m_column[1].items;
    do
    {
      v10 = (UIListBox *)operator new(0x48u);
      if ( !v10 || (v11 = (((UIListBox *)v10))->UIListBox::GetSubItemInfo()) == 0 )
      {
        qmemcpy(
          pExceptionObject,
          (((Logger *)ArgList))->Logger::FormatException(&path[164], "D:\\Project\\PAL3\\UI\\UIListBox.cpp", 282),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      (((PtrArray *)p_items))->PtrArray::SetAt(p_items->capacity, (int)v11);
      ++v8;
      p_items = (PtrArray *)((char *)p_items + 84);
    }
    while ( v8 < this->m_numcol );
  }
  this->UIListBox::InitScrollbar();
  v12 = (int *)(*(int **)&this->m_rowenable[8]);
  pVal = 1;
  PtrVec_Insert_dword((Actor *)this->m_rowenable, v12, 1u, &pVal);
  v13 = *(_DWORD *)&this->m_rowenable[4];
  if ( v13 )
  {
    if ( (*(_DWORD *)&this->m_rowenable[8] - v13) >> 2 )
    {
      if ( this->m_onsel == -1 )
      {
        UIListBox_SetFirstShow(0);
        if ( this->m_onsel != -1 )
        {
          Child = this->UIListBox::CreateChild();
          m_pfather = this->m_pfather;
          if ( m_pfather )
            m_pfather->OnMessage(1006, this->m_id, Child);
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
  ((OpenBaseFile *)&movesel)->OpenBaseFile::OpenBaseFile();
  v6 = (gbTexture *)gfxMgr->NewTexture((const char *)Source);
  *(_DWORD *)v5 = (_DWORD)v6;
  if ( v6 )
    (((gbTexture *)v6))->gbTexture::LoadTexture(1);
  ((OpenNULLFile *)&movesel)->OpenNULLFile::OpenNULLFile();
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
  gbTexture **v8; // ecx
  bool v9; // cc
  int Child; // eax
  int m_movesel; // edx
  bool v12; // cl
  LONG left; // eax
  LONG top; // ecx
  int y; // ebp
  LONG right; // ebx
  int v17; // ecx
  int v18; // eax
  int v19; // ebx
  int m_itemheight; // edi
  int v21; // edx
  LONG v22; // edx
  LONG v23; // ecx
  LONG v24; // edi
  int m_seloffset; // edi
  int v26; // [esp-0x24] [ebp-0x88]
  int v27; // [esp-0x1C] [ebp-0x80]
  int *v28; // [esp+0x4] [ebp-0x60]
  int v29; // [esp+0x8] [ebp-0x5C]
  int v30; // [esp+0xC] [ebp-0x58]
  char pszFolder[4]; // [esp+0x10] [ebp-0x54] BYREF
  int v32; // [esp+0x14] [ebp-0x50]
  int v33; // [esp+0x18] [ebp-0x4C]
  LONG bottom; // [esp+0x1C] [ebp-0x48]
  struct gbTextureArray v35; // [esp+0x20] [ebp-0x44] BYREF

  result = this->m_bvisible;
  if ( result )
  {
    if ( this->m_pbkpic )
    {
      v35.pTexPt[0] = this->m_pbkpic;
      v35.nTex = 1;
      (((TextureLibDataBase *)&v35))->TextureLibDataBase::SetLibFolder((const char *)&this->m_rect, (int)&this->m_wndcolor);
    }
    else if ( this->m_showGrayBk )
    {
      crt_sub_00540070();
    }
    v3 = this->m_itemoffset.x + this->m_rect.left + 8;
    this->UIListBox::SetDefaultSel();
    v29 = v4;
    v30 = 0;
    if ( this->m_numcol > 0 )
    {
      p_capacity = (int *)&this->m_column[0].items.capacity;
      v28 = (int *)&this->m_column[0].items.capacity;
      do
      {
        m_firstshow = this->m_firstshow;
        v7 = this->m_rect.top + this->m_itemoffset.y + 8;
        if ( m_firstshow < m_firstshow + v29 )
        {
          do
          {
            if ( m_firstshow >= *p_capacity )
              break;
            v8 = m_firstshow < 0 ? 0 : *(gbTexture ***)(*(p_capacity - 1) + 4 * m_firstshow);
            if ( *v8 )
            {
              v35.pTexPt[0] = *v8;
              v33 = v3 + 32;
              bottom = v7 + 32;
              *(_DWORD *)pszFolder = v3;
              v32 = v7;
              v35.nTex = 1;
              (((TextureLibDataBase *)&this->m_wndcolor))->TextureLibDataBase::SetLibFolder(pszFolder, (int)&this->m_wndcolor);
            }
            else
            {
              crt_sub_00540FD0();
            }
            v7 += this->m_itemheight;
            ++m_firstshow;
            p_capacity = (int *)v28;
          }
          while ( m_firstshow < v29 + this->m_firstshow );
        }
        v3 += p_capacity[3];
        p_capacity += 21;
        v9 = ++v30 < this->m_numcol;
        v28 = (int *)p_capacity;
      }
      while ( v9 );
    }
    Child = this->UIListBox::CreateChild();
    m_movesel = this->m_movesel;
    if ( m_movesel )
    {
      v12 = this->m_onsel != -1;
      if ( this->m_onsel == -1 || !*(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * Child) )
      {
LABEL_34:
        (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
        return result;
      }
    }
    else
    {
      v12 = this->m_locksel != -1;
    }
    if ( v12 )
    {
      left = this->m_rect.left;
      top = this->m_rect.top;
      y = this->m_itemoffset.y;
      right = this->m_rect.right;
      bottom = this->m_rect.bottom;
      v17 = y + top;
      v18 = this->m_itemoffset.x + left + 4;
      v19 = -2 - this->m_scrollW + right;
      m_itemheight = this->m_itemheight;
      v21 = m_movesel ? this->m_onsel : this->m_locksel - this->m_firstshow;
      v22 = v17 + m_itemheight * v21 + 8;
      v23 = m_itemheight + v22 - 2;
      v24 = this->m_rect.bottom;
      if ( v23 > v24 )
        v23 = this->m_rect.bottom;
      if ( v22 >= this->m_rect.top && v23 <= v24 )
      {
        if ( this->m_selpic )
        {
          v35.pTexPt[0] = this->m_selpic;
          m_seloffset = this->m_seloffset;
          v27 = v19 + this->m_seloffsetR;
          v26 = v18 + this->m_seloffsetL;
          v35.nTex = 1;
          UIDestorySystem(v26, v22 + m_seloffset, v27, m_seloffset + v23, &this->m_seltexcolor, &v35);
          (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
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

// 0x0043EBB0
void UIListBox::GetGridOffset(int *pOut, int index)
{
  LONG top; // eax
  int v4; // edx

  top = this->m_rect.top;
  v4 = this->m_itemheight * (index - this->m_firstshow);
  *pOut = this->m_rect.left;
  pOut[1] = top + v4;
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
  int v22; // edx
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
  POINT pt; // [esp+0x18] [ebp-0x18] BYREF
  RECT rc; // [esp+0x20] [ebp-0x10] BYREF

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( !nVal2 || this->m_numcol <= 0 )
    return nVal2 == 0;
  result = (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  if ( result )
    return result;
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
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
        this->UIListBox::SetDefaultSel();
        if ( this->m_onsel >= v16 )
        {
          this->UIListBox::SetDefaultSel();
          this->m_onsel = v17 - 1;
        }
      }
      Child = this->UIListBox::CreateChild();
      m_pfather = this->m_pfather;
      if ( m_pfather )
        m_pfather->OnMessage(1006, this->m_id, Child);
    }
    if ( g_Input.KeyInfo[0].PressTime != 1 )
      goto LABEL_69;
    if ( (g_Input.KeyInfo[0].Data & 0xF) != 1 )
      goto LABEL_69;
    if ( !*(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * (v12 + this->m_firstshow)) )
      goto LABEL_69;
    m_locksel = this->UIListBox::CreateChild();
    v21 = this->m_pfather;
    if ( !v21 )
      goto LABEL_69;
    v22 = *(_DWORD *)v21;
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
          this->UIListBox::SetDefaultSel();
          if ( this->m_onsel >= v30 )
          {
            this->UIListBox::SetDefaultSel();
            this->m_onsel = v31 - 1;
          }
        }
        this->m_locksel = this->m_onsel + this->m_firstshow;
      }
      v32 = this->m_pfather;
      if ( v32 )
        (*(void ( **)(int, unsigned int, int))(*(_DWORD *)v32 + 24))(
          1008,
          this->m_id,
          this->m_locksel);
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
        this->UIListBox::SetDefaultSel();
        if ( this->m_onsel >= v40 )
        {
          this->UIListBox::SetDefaultSel();
          this->m_onsel = v41 - 1;
        }
      }
      this->m_locksel = this->m_onsel + this->m_firstshow;
    }
    v42 = this->m_pfather;
    if ( !v42 )
      goto LABEL_69;
    v22 = *(_DWORD *)v42;
    m_locksel = this->m_locksel;
LABEL_68:
    (*(void ( **)(int, unsigned int, int))(v22 + 24))(1007, this->m_id, m_locksel);
LABEL_69:
    if ( v9 )
    {
      if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
      {
        v43 = this->m_pfather;
        if ( v43 )
          v43->OnMessage(1009, this->m_id, LOWORD(pt.x) | (LOWORD(pt.y) << 16));
      }
      if ( g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
      {
        v44 = this->m_pfather;
        if ( v44 )
          v44->OnMessage(1010, this->m_id, LOWORD(pt.x) | (LOWORD(pt.y) << 16));
      }
    }
  }
  if ( this->m_hasKeyCtrl )
    this->UIListBox::ProcessSelection();
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
  int v22; // edx
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
    atexit((void ( *)())SyncUIRoleDialogMembers);
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
          (((UIAnimateCtrlEX *)&this->m_scrollbar))->UIAnimateCtrlEX::StepAnimation();
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
        result = this->UIListBox::CreateChild();
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
        this->UIListBox::SetDefaultSel();
        if ( this->m_onsel >= v10 - 1 )
        {
          this->UIListBox::SetDefaultSel();
          this->m_onsel = v11 - 1;
          (((UIAnimateCtrlEX *)&this->m_scrollbar))->UIAnimateCtrlEX::NextFrame();
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
        result = this->UIListBox::CreateChild();
        m_pfather = this->m_pfather;
        if ( !m_pfather )
          goto LABEL_26;
      }
      result = (unsigned long)m_pfather->OnMessage(1006, this->m_id, result);
LABEL_26:
      if ( g_Input.KeyInfo[7].PressTime == 1
        && *(_DWORD *)(*(_DWORD *)&this->m_rowenable[4] + 4 * (this->m_onsel + this->m_firstshow)) )
      {
        result = this->UIListBox::CreateChild();
        v15 = this->m_pfather;
        if ( v15 )
          return v15->OnMessage(1007, this->m_id, result);
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
        (((UIAnimateCtrlEX *)&this->m_scrollbar))->UIAnimateCtrlEX::StepAnimation();
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
      v22 = *(_DWORD *)v21;
    }
    else
    {
      if ( g_Input.KeyInfo[5].PressTime != 1 )
        goto LABEL_51;
      ++this->m_onsel;
      v23 = this->m_column[0].items.capacity;
      this->UIListBox::SetDefaultSel();
      if ( this->m_onsel >= v24 - 1 )
      {
        this->UIListBox::SetDefaultSel();
        this->m_onsel = v25 - 1;
        (((UIAnimateCtrlEX *)&this->m_scrollbar))->UIAnimateCtrlEX::NextFrame();
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
      v22 = *(_DWORD *)v29;
      result = this->m_locksel;
    }
    result = (*(int ( **)(int, unsigned int, int))(v22 + 24))(1007, this->m_id, result);
LABEL_51:
    if ( g_Input.KeyInfo[7].PressTime == 1 )
    {
      v30 = this->m_pfather;
      if ( v30 )
        return v30->OnMessage(1008, this->m_id, this->m_locksel);
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
    this->UIListBox::AdjustScroll(i);
  v3 = 0;
  if ( this->m_numcol > 0 )
  {
    m_column = this->m_column;
    do
    {
      (((UIListBox *)m_column))->UIListBox::GetItemAt();
      ++v3;
      ++m_column;
    }
    while ( v3 < this->m_numcol );
  }
  this->m_firstshow = 0;
  (((UIBigMap *)&this->m_scrollbar))->UIBigMap::SetScrollRange(0, 0);
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
    p_items = (PtrArray *)&this->m_column[0].items;
    do
    {
      if ( nVal < p_items->capacity )
      {
        v6 = (void *)(*(void **)&p_items->m_pData[4 * nVal]);
        if ( v6 )
        {
          (((UIListBox *)*(UIListBox **)&p_items->m_pData[4 * nVal]))->UIListBox::Render();
          operator delete(v6);
        }
      }
      (((PtrArray *)p_items))->PtrArray::RemoveAt(nVal, 1);
      p_items = (PtrArray *)((char *)p_items + 84);
      ++nVala;
    }
    while ( nVala < this->m_numcol );
    this->UIListBox::InitScrollbar();
    this->m_onsel = -1;
    v7 = (_DWORD *)(*(_DWORD **)&this->m_rowenable[8]);
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
    return (((UIBigMap *)&this->m_scrollbar))->UIBigMap::SetScrollRange(0, 0);
  capacity = this->m_column[0].items.capacity;
  this->UIListBox::SetDefaultSel();
  if ( capacity <= v3 )
    return (((UIBigMap *)&this->m_scrollbar))->UIBigMap::SetScrollRange(0, 0);
  else
    return (((UIBigMap *)&this->m_scrollbar))->UIBigMap::SetScrollRange(0, capacity - v3);
}

// 0x0043F560
int UIListBox::CreateChild()
{
  int m_onsel; // edx

  if ( this->m_numcol <= 0 )
    return -1;
  m_onsel = this->m_onsel;
  if ( m_onsel == -1 )
    return -1;
  else
    return m_onsel + this->m_firstshow;
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
  int v6; // [esp-0x4] [ebp-0xC]
  int v7; // [esp+0xC] [ebp+0x4]

  if ( v7 < 0 || v7 >= this->m_column[0].items.capacity )
  {
    this->m_onsel = -1;
  }
  else
  {
    m_firstshow = this->m_firstshow;
    this->m_onsel = v7 - m_firstshow;
    if ( v7 - m_firstshow < 0 )
      this->m_onsel = 0;
    this->UIListBox::SetDefaultSel();
    if ( this->m_onsel >= v3 )
    {
      this->UIListBox::SetDefaultSel();
      this->m_onsel = v4 - 1;
    }
    v6 = v7 - this->m_onsel;
    this->m_firstshow = v6;
    (((UIScene *)&this->m_scrollbar))->UIScene::SetFirstShow(v6);
  }
  result = this->m_onsel + this->m_firstshow;
  this->m_locksel = result;
  return result;
}

// 0x0043F640
void UIListBox::SetLockSel(int nVal1)
{
  this->m_itemheight = nVal1;
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
  int result; // eax

  result = nVal;
  this->m_itemoffset.x = nVal;
  this->m_itemoffset.y = nVal2;
  return result;
}

// 0x0043FE90
int UIListBox::GetCurSel()
{
  int m_tilewidth; // edx
  int result; // eax

  m_tilewidth = this->m_scrollbar.m_bk.m_tilewidth;
  result = 0;
  this->m_scrollbar.m_childs.m_pData = ((char *)0);
  this->m_scrollbar.m_rect.bottom = 0;
  this->m_scrollbar.m_childs.m_nSize = 0;
  LOBYTE(this->m_scrollbar.m_bk.m_wndcolor.Color) = 0;
  BYTE1(this->m_scrollbar.m_btnH) = 0;
  this->m_scrollbar.m_bk.m_tileheight = m_tilewidth;
  LOBYTE(this->m_scrollbar.m_btnH) = 0;
  BYTE2(this->m_scrollbar.m_btnH) = 0;
  return result;
}

// 0x00451850
int UIListBox::UIListBox_Init()
{
  ((UIFrameWnd *)this)->UIFrameWnd::UIFrameWnd();
  *(_DWORD *)&this->m_hasKeyCtrl = 0;
  (((UIListBox *)&this->m_scrollbar.m_wndcolor))->UIListBox::UpdateKeyCtrl();
  (((UITextArea *)&this[1].m_scrollbar.m_wndcolor))->UITextArea::InitAfterClear();
  *(_DWORD *)((UIWnd *)&this->m_scrollbar) = 0;
  this->m_selcolor.Color = 1;
  this->m_scrollbar.m_fontcolor.Color = -1;
  return (int)this;
}

// 0x00451900
void UIListBox::DestroyContent()
{
  UITextArea_Destroy();
  (((UIListBox *)&this->m_scrollbar.m_wndcolor))->UIListBox::DeleteRow();
  (((UIFrameWnd *)this))->UIFrameWnd::UIFrameWnd();
}

// 0x00451AD0
int UIListBox::ReinitScrollbar()
{
  int result; // eax

  result = (((UIListBox *)&this->m_scrollbar.m_wndcolor))->UIListBox::ClearAll();
  this->m_scrollbar.m_fontcolor.Color = -1;
  return result;
}

// 0x00451AF0
int UIListBox::CalcVisibleRange(char *Source, int nVal)
{
  UIListBox *p_m_wndcolor; // esi
  int ListItems; // eax
  unsigned int v6; // kr04_4
  int result; // eax

  p_m_wndcolor = (UIListBox *)&this->m_scrollbar.m_wndcolor;
  ListItems = (((UIListBox *)&this->m_scrollbar.m_wndcolor))->UIListBox::LoadListItems(Source, 0);
  UIListBox_SetChildParam(ListItems);
  (((UIListBox *)p_m_wndcolor))->UIListBox::GetItem();
  v6 = strlen(Source) + 1;
  result = this->m_scrollbar.m_fontcolor.Color;
  if ( (int)(v6 - 1) > result )
    this->m_scrollbar.m_fontcolor.Color = v6 - 1;
  return result;
}

// 0x00451B40
int UIListBox::UIListBox_ResizeToContent(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ecx
  int v4; // eax
  _DWORD a2[2]; // [esp+0xC] [ebp-0x10] BYREF
  int v7; // [esp+0x14] [ebp-0x8]
  int v8; // [esp+0x18] [ebp-0x4]

  v2 = v1;
  if ( nVal )
  {
    a2[0] = 0;
    a2[1] = 0;
    v3 = 5 * ((((UIListBox *)(v1 + 88)))->UIListBox::GetItemData() + 2);
    v4 = *(_DWORD *)(v2 + 84) + 6;
    v8 = 4 * v3;
    v7 = 10 * v4;
    (((UIWnd *)v2))->UIWnd::sub_445FA0(a2);
    (((UIWnd *)(v2 + 1296)))->UIWnd::sub_445FA0(a2);
    v8 -= 20;
    v7 -= 20;
    (((UIWnd *)(v2 + 88)))->UIWnd::sub_445FA0(a2);
    sub_445DB0((void *)v2);
    sub_445DB0(0);
  }
  (**(void ( ***)(int, int))(v2 + 1296))((int)(v2 + 1296), (int)(nVal));
  (((UIScene *)(v2 + 1296)))->UIScene::SetState(1);
  return (((CCBPanelSlot *)v2))->CCBPanelSlot::ShowClipped(nVal);
}

// 0x00451C10
int UIListBox::UIListBox_IsVisible(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax

  v2 = v1;
  result = *(_DWORD *)(v1 + 56);
  if ( result )
  {
    result = (*(int ( **)(int))(*(_DWORD *)(v1 + 1296) + 4))(v1 + 1296);
    if ( *(_DWORD *)(v2 + 1468) == 2 )
      return (*(int ( **)(int))(*(_DWORD *)(v2 + 88) + 4))(v2 + 88);
  }
  return result;
}

// 0x004526C0
BOOL UIListBox::ShouldProcessInput(int nVal, int nVal2)
{
  if ( g_CCBEditorInst.m_dwTrickID[361] == 12 || g_nCameraUpdateCount > 0 )
    return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  else
    return 0;
}

// 0x004526F0
int UIListBox::RenderMagic()
{
  int result; // eax
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  if ( g_CCBEditorInst.m_dwTrickID[361] == 12 )
    (((CCBControlWindow *)this))->CCBControlWindow::Render(v3) /* [ROWTABLE] */;
  result = g_nCameraUpdateCount;
  if ( g_nCameraUpdateCount > 0 )
    (((CCBControlWindow *)this))->CCBControlWindow::Render(v3) /* [ROWTABLE] */;
  return result;
}

// 0x0049CF20
int UIListBox::GetSkillSlotLevel(int nVal, int nVal2)
{
  int v3; // esi
  float *v4; // edx
  int v5; // eax
  float *v6; // ecx

  v3 = 0;
  v4 = (float *)(&g_RoleSlotBuf.m_partyActor.m_fDirZ + 352 * nVal);
  while ( 2 )
  {
    v5 = 0;
    v6 = (float *)v4;
    do
    {
      if ( nVal2 == *(_DWORD *)v6 )
        return *((unsigned __int8 *)&g_RoleSlotBuf.m_fRotAxisZ + 1408 * nVal + 8 * v3 + v5);
      ++v5;
      ++v6;
    }
    while ( v5 < 8 );
    ++v3;
    v4 += 8;
    if ( v3 < 6 )
      continue;
    break;
  }
  return 0;
}

// 0x004B4690
// write access to const memory has been detected, the output may be wrong!
void UIListBox::Reset()
{
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
  this->m_pfather = ((UIWnd *)((UIWnd *)100));
  this->m_childs.m_pData = ((char *)((char *)200));
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
  *(_BYTE *)((UIWnd *)&this->m_scrollbar) = 1;
  LOBYTE(this->m_scrollbar.m_wndcolor.Color) = 0;
  this->m_scrollbar.m_id = 0;
  this->m_scrollbar.m_rect.left = 0;
  this->m_scrollbar.m_rect.top = 0;
  LOBYTE(this->m_scrollbar.m_rect.right) = 1;
  LOBYTE(this->m_scrollbar.m_childs.m_pData) = 0;
  this->m_scrollbar.m_pfather = ((UIWnd *)0);
  this->m_scrollbar.m_rect.bottom = 0;
  this->m_scrollbar.m_childs.capacity = 10;
  LOBYTE(this->m_scrollbar.m_childs.m_needscriptdel) = 0;
  this->m_scrollbar.m_bcreateok = 1065353216;
  this->m_scrollbar.m_bvisible = 0;
  this->m_scrollbar.m_benable = 0;
  this->m_scrollbar.m_bfocus = 0;
  *(_DWORD *)&this->m_scrollbar.m_bPress = 0;
  *(_DWORD *)((UIWnd *)&this->m_scrollbar.m_bk) = 0;
  this->m_scrollbar.m_bk.m_fontcolor.Color = 0;
  this->m_scrollbar.m_slideroffset = 0;
  (((UIFrameContainer *)&this->m_scrollbar.m_slidertboffset))->UIFrameContainer::ResetContainerState();
  *(_DWORD *)&this->m_column[1].head[52] = 0;
  *(_DWORD *)&this->m_column[1].head[56] = 0;
  *(_DWORD *)&this->m_column[1].head[60] = 1058642330;
  this->m_scrollbar.m_childs.m_nSize = -16777216;
  this->m_fontcolor.Color = 100;
  *(_DWORD *)((UIWnd *)this) = 100;
  this->m_wndcolor.Color = 200;
  this->m_id = 400;
  gbColorQuad::ColorQuadFmt = 1;
  this->m_scrollbar.m_fontcolor.Color = -16777216;
}

// 0x00519AF0
CCBUI * UIListBox::InitAndRender()
{
  this->UIListBox::UIListBox();
  (((CCBUI *)this))->CCBUI::Render();
  return (CCBUI *)this;
}

// 0x00527950
int UIListBox::ctor()
{
  this->UIListBox::UIListBox();
  this->m_scrollbar.m_wndcolor.Color = 800;
  this->m_scrollbar.m_id = 600;
  this->m_scrollbar.m_texarrayInfo[3] = 0;
  ((UIRoleDialog *)&this->m_scrollbar.m_texarrayInfo[4])->UIRoleDialog::UIRoleDialog();
  this[1].m_column[0].width = 0;
  *(_DWORD *)this[1].m_column[1].head = 0;
  *(_DWORD *)&this[1].m_column[1].head[16] = 0;
  this[1].m_column[1].head[28] = 1;
  return (int)this;
}

// 0x00532A40
int * UIListBox::ResetRect()
{
  this->m_id = 0;
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
  this->m_pfather = ((UIWnd *)0);
  this->m_childs.m_pData = ((char *)0);
  this->m_childs.capacity = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_needscriptdel = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  this->m_scrollbar.m_childs.m_pData = ((char *)0);
  this->m_scrollbar.m_childs.capacity = 0;
  this->m_scrollbar.m_childs.m_nSize = 0;
  (((UITabCtrl *)this))->UITabCtrl::InitAnimParams();
  return (int *)this;
}

// 0x0053D100
void UIListBox::RefreshList()
{
  (((UIListBox *)&this->m_rect))->UIListBox::ReleaseVtable();
  this->UIListBox::ReleaseVtable();
}
