#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBParabolaWindow.h"
#include "Combat/CCBAIWindow.h"
#include "Combat/CCBControl.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBLineupWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Misc/CCBPanelSlot.h"
#include "Combat/CCBSkillWindow.h"
#include "Combat/CCBStage.h"
#include "GameBase/GRPinput.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Scene/SceneObj.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/_Texture_Info.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

class TextureLibDataBase;

// Unnamed globals (extern)
extern TextureLibDataBase stru_1894B78;

// 0x00440BE0
gbVFileSystem * CCBParabolaWindow::LoadResourceEx(const char *pszName, char pData)
{
  int v4; // edi
  CCBParabolaWindow *v5; // esi
  int v6; // ebp
  CHAR *v7; // eax
  gbVFileSystem *result; // eax
  OpenBaseFile v9; // [esp+0x10] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x14] [ebp-0x110] BYREF
  int v11; // [esp+0x120] [ebp-0x4]

  v4 = 0;
  v11 = 0;
  v5 = this + 1;
  do
  {
    if ( *(_DWORD *)((UIWnd *)v5) )
      (((gbRefObject *)*(gbRefObject **)((UIWnd *)v5)))->gbRefObject::Release();
    sprintf(Buffer, "%s%d.tga", pszName, v4);
    if ( pData )
    {
      v6 = *(_DWORD *)*(void**)(gfxMgr);
      v7 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(Buffer);
      *(_DWORD *)((UIWnd *)v5)  = (unsigned long)(gfxMgr->NewTexture((const char *)v7));
      v5->m_wndcolor.Color = (unsigned int)(((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(Buffer);
    }
    else
    {
      *(_DWORD *)((UIWnd *)v5)  = (unsigned long)(gfxMgr->NewTexture((const char *)Buffer));
    }
    if ( *(_DWORD *)((UIWnd *)v5) )
      (((gbTexture *)*(gbTexture **)((UIWnd *)v5)))->gbTexture::LoadTexture(1);
    ++v4;
    v5 = (CCBParabolaWindow *)((char *)v5 + 4);
  }
  while ( v4 < 2 );
  v11 = -1;
  ((OpenNULLFile *)&v9)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x0051B710
CCBParabolaWindow::CCBParabolaWindow(
        
        CCBParabolaWindow **thisa,
        int *pnVal,
        int nVal)
{
  UIPushButton **p_m_wndcolor; // edi
  CCBLineupWindow *v6; // ecx
  CCBLineupWindow *v7; // ecx
  char v8; // al
  UIPushButton **p_m_id; // ebx
  int i; // edi
  char v11; // al
  int v12; // eax
  int v13; // ecx

  this->UIWnd::Create(1879048197, (tagRECT *)thisa, (int)pnVal);
  this[1].m_childs.m_pData = (char *)pnVal;
  p_m_wndcolor = (UIPushButton **)&this[1].m_wndcolor;
  (((CCBLineupWindow *)v6))->CCBLineupWindow::Destroy();
  if ( v8 == 1 )
  {
    *thisa = 0;
    thisa[2] = (CCBParabolaWindow *)230;
    thisa[1] = 0;
    thisa[3] = (CCBParabolaWindow *)250;
    (*(void (**)(UIPushButton *, int, CCBParabolaWindow **, CCBParabolaWindow *))(*(_DWORD *)((UIWnd *)(*p_m_wndcolor))
                                                                                           + 16))(
      *p_m_wndcolor,
      240,
      thisa,
      this);
    (((UIPushButton *)*p_m_wndcolor))->UIPushButton::CreateFromTemplate(&unk_5DF73C, 0);
    (**(void (***)(UIPushButton *, int))((UIWnd *)(*p_m_wndcolor)))((UIPushButton *)(*p_m_wndcolor), (int)(1));
  }
  p_m_id = (UIPushButton **)&this[1].m_id;
  for ( i = 0; i < 5; ++i )
  {
    (((CCBLineupWindow *)v7))->CCBLineupWindow::Destroy();
    if ( v11 )
    {
      v12 = g_nUnkTable_268[i + 1];
      v13 = g_nUnkTable_24C[i + 1];
      *thisa = (CCBParabolaWindow *)v13;
      thisa[1] = (CCBParabolaWindow *)v12;
      thisa[2] = (CCBParabolaWindow *)(v13 + 40);
      thisa[3] = (CCBParabolaWindow *)(v12 + 38);
      (*(void (**)(UIPushButton *, int, CCBParabolaWindow **, CCBParabolaWindow *))(*(_DWORD *)((UIWnd *)(*p_m_id))
                                                                                             + 16))(
        *p_m_id,
        g_nPropIDs_241[i],
        thisa,
        this);
      (((UIPushButton *)*p_m_id))->UIPushButton::CreateFromTemplate(*(_UNKNOWN **)((char *)&off_570284 + i * 4), 0);
      (((UIFrameWnd *)*p_m_id))->UIFrameWnd::SetTextureByName((&off_570298)[i], 0);
      (**(void (***)(UIPushButton *, int))((UIWnd *)(*p_m_id)))((UIPushButton *)(*p_m_id), (int)(1));
    }
    ++p_m_id;
  }
}

// 0x0051B810
CCBParabolaWindow::~CCBParabolaWindow()
{
  unsigned int Color; // ecx
  unsigned int *p_m_id; // esi
  int v4; // edi

  Destroy__ovl_03((int)this);
  Color = this[1].m_wndcolor.Color;
  if ( Color )
  {
    (*(void (**)(unsigned int, int))(*(_DWORD *)Color + 20))(Color, 1);
    this[1].m_wndcolor.Color = 0;
  }
  p_m_id = (unsigned int *)&this[1].m_id;
  v4 = 5;
  do
  {
    if ( *p_m_id )
    {
      (*(void (**)(unsigned int, int))(*(_DWORD *)*p_m_id + 20))(*p_m_id, 1);
      *p_m_id = 0;
    }
    ++p_m_id;
    --v4;
  }
  while ( v4 );
}

// 0x0051B920
void CCBParabolaWindow::Destroy()
{
  int v2; // ecx
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  (((CCBControlWindow *)this))->CCBControlWindow::Render(v3) /* [ROWTABLE] */;
  v2 = *(&this[1].m_id + (int)this[1].m_pfather);
  (*(void ( **)(int))(*(_DWORD *)v2 + 4))(v2);
}

// 0x0051B950
bool CCBParabolaWindow::OnMessage(
        
        int msg,
        unsigned int wparam,
        unsigned int lparam)
{
  _DWORD *v4; // eax
  _BYTE a2[16]; // [esp+0x8] [ebp-0x10] BYREF

  v4 = (_DWORD *)sub_445FE0(a2);
  return (signed int)wparam >= *v4
      && (signed int)wparam < v4[2]
      && (signed int)lparam >= v4[1]
      && (signed int)lparam < v4[3];
}

// 0x0051C260
UIWnd * CCBParabolaWindow::_scalar_deleting_destructor_(
        
        CCBSkillWindow *Block,
        char pData)
{
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x0051C880
int CCBParabolaWindow::Destroy_c880()
{
  int result; // eax
  LONG *p_right; // edi
  int v4; // ebx
  UIStatic *m_pBack; // ecx
  UIStatic *m_pDescription; // ecx
  UIListBox *m_pItemList; // ecx
  int v8; // ecx
  unsigned int Color; // ecx
  unsigned int v10; // ecx
  unsigned int m_id; // ecx
  LONG left; // ecx
  LONG top; // ecx
  gbTexture *m_pbktex; // ecx
  UIStatic *v15; // ecx
  UIStatic *v16; // ecx
  UIListBox *v17; // ecx

  result = Destroy__ovl_03((int)this);
  p_right = (LONG *)&this[1].m_rect.right;
  v4 = 11;
  do
  {
    if ( *p_right )
    {
      result = (*(int ( **)(LONG, int))(*(_DWORD *)*p_right + 20))(*p_right, 1);
      *p_right = 0;
    }
    ++p_right;
    --v4;
  }
  while ( v4 );
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    result = (*(int ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pBack) + 20))(m_pBack, 1);
    this->m_pBack = ((UIStatic *)0);
  }
  m_pDescription = (UIStatic *)this->m_pDescription;
  if ( m_pDescription )
  {
    result = (*(int ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pDescription) + 20))(m_pDescription, 1);
    this->m_pDescription = ((UIStatic *)0);
  }
  m_pItemList = (UIListBox *)this->m_pItemList;
  if ( m_pItemList )
  {
    result = (*(int ( **)(UIListBox *, int))(*(_DWORD *)((UIWnd *)m_pItemList) + 20))(m_pItemList, 1);
    this->m_pItemList = ((UIListBox *)0);
  }
  v8 = (int)((UIWnd *)&this[1]);
  if ( v8 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)((UIWnd *)&this[1]) = 0;
  }
  Color = this[1].m_fontcolor.Color;
  if ( Color )
  {
    result = (*(int ( **)(unsigned int, int))(*(_DWORD *)Color + 20))(Color, 1);
    this[1].m_fontcolor.Color = 0;
  }
  v10 = this[1].m_wndcolor.Color;
  if ( v10 )
  {
    result = (*(int ( **)(unsigned int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    this[1].m_wndcolor.Color = 0;
  }
  m_id = this[1].m_id;
  if ( m_id )
  {
    result = (*(int ( **)(unsigned int, int))(*(_DWORD *)m_id + 20))(m_id, 1);
    this[1].m_id = 0;
  }
  left = this[1].m_rect.left;
  if ( left )
  {
    result = (*(int ( **)(LONG, int))(*(_DWORD *)left + 20))(left, 1);
    this[1].m_rect.left = 0;
  }
  top = this[1].m_rect.top;
  if ( top )
  {
    result = (*(int ( **)(LONG, int))(*(_DWORD *)top + 20))(top, 1);
    this[1].m_rect.top = 0;
  }
  m_pbktex = this[1].m_pbktex;
  if ( m_pbktex )
  {
    result = (*(int ( **)(gbTexture *, int))(*(_DWORD *)((gbRefObject *)m_pbktex) + 20))(m_pbktex, 1);
    this[1].m_pbktex = ((gbTexture *)0);
  }
  v15 = (UIStatic *)this[1].m_pBack;
  if ( v15 )
  {
    result = (*(int ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)v15) + 20))(v15, 1);
    this[1].m_pBack = ((UIStatic *)0);
  }
  v16 = (UIStatic *)this[1].m_pDescription;
  if ( v16 )
  {
    result = (*(int ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)v16) + 20))(v16, 1);
    this[1].m_pDescription = ((UIStatic *)0);
  }
  v17 = (UIListBox *)this[1].m_pItemList;
  if ( v17 )
  {
    result = (*(int ( **)(UIListBox *, int))(*(_DWORD *)((UIWnd *)v17) + 20))(v17, 1);
    this[1].m_pItemList = ((UIListBox *)0);
  }
  return result;
}

// 0x0051C9F0
BOOL CCBParabolaWindow::Update(int deltatime, int haveinput)
{
  if ( this->m_bvisible == 1 && g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 )
    (((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8)))->CCBControl::SetParam(513, -1, 0);
  return (((SceneObj *)this))->SceneObj::Update(deltatime, haveinput) /* [ROWTABLE] */;
}

// 0x0051CA50
CCBAIWindow * CCBParabolaWindow::ToggleSlots(int nVal)
{
  int v3; // edi
  LONG *p_right; // esi
  void ( ***v5)(_DWORD, int); // ecx

  if ( nVal == 1 )
  {
    LOBYTE(this[2].m_wndcolor.Color) = 0;
    v3 = 0;
    p_right = (LONG *)&this[1].m_rect.right;
    do
    {
      v5 = (void ( ***)(_DWORD, int))*p_right;
      if ( this[2].m_fontcolor.Color == v3 )
        (**v5)((_DWORD)((_DWORD)(v5)), (int)(1));
      else
        (**v5)((_DWORD)((_DWORD)(v5)), (int)(0));
      ++v3;
      ++p_right;
    }
    while ( v3 < 5 );
  }
  return (CCBAIWindow *)(((CCBPanelSlot *)this))->CCBPanelSlot::ShowClipped(nVal);
}

// 0x0051CAA0
void CCBParabolaWindow::Render()
{
  LONG left; // ebx
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x18]

  (((CCBControlWindow *)this))->CCBControlWindow::Render(v3) /* [ROWTABLE] */;
  left = this->m_rect.left;
  CCBStage_AddTextLabel(left + 105);
  CCBStage_AddTextLabel(left + 117);
  CCBStage_AddTextLabel(left + 107);
}
