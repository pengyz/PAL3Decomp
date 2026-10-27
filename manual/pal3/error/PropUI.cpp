#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/PropUI.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBUI.h"
#include "Render/CScreenMode.h"
#include "Scene/Camera.h"
#include "Misc/FightItem.h"
#include "GameBase/GRPinput.h"
#include "Misc/MUIDialog.h"
#include "Misc/NameSys.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PlayerItem.h"
#include "Misc/PtrArray.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/UI3DCtrl.h"
#include "Misc/UIBigMap.h"
#include "Misc/UIButtonEX.h"
#include "Misc/UIButton_UIBUTTON_STATE.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UISceneMap.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/st_Manager.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern char asc_5B74B8[];

// 0x00452670
void PropUI::Init()
{
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, 0, 0, 800, 600) /* [ROWTABLE] */;
  (((UIBigMap *)&this->bkWndX))->UIBigMap::InitUI(100, (int)this);
  UITitle_BBTY_CreateFromScript((int)this);
}

// 0x0045B200
int PropUI::ShowCategory0(unsigned __int8 pData)
{
  gbTexture *m_pbk; // edx
  int m_nTodo_164; // edi
  int result; // eax

  m_pbk = (gbTexture *)this->m_EquipFlag.m_pbk;
  this->ml_ListProp.m_column[2].head[28] = pData;
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)m_pbk))(&this->m_EquipFlag.m_pbk, pData);
  this->m_nTodo_168 = 0;
  this->m_nTodo_164 = 0;
  do
  {
    m_nTodo_164 = this->m_nTodo_164;
    if ( this->ml_ListProp.m_column[2].head[m_nTodo_164 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * m_nTodo_164 + 20] = this->m_nTodo_168
                                                                            * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                            + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                             - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                            / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 20];
      (((UIWnd *)&this->m_EquipFlag.m_text[152 * this->m_nTodo_164 + 16]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]);
      ++this->m_nTodo_168;
    }
    result = this->m_nTodo_164 + 1;
    this->m_nTodo_164 = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0045B320
int PropUI::ShowCategory1(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  int m_nTodo_164; // edi
  int result; // eax

  v3 = *(void ( ***)(char *, _DWORD))&this->m_ListPropTitle.m_text[8];
  this->ml_ListProp.m_column[2].head[29] = pData;
  (*v3)(&this->m_ListPropTitle.m_text[8], pData);
  this->m_nTodo_168 = 0;
  this->m_nTodo_164 = 0;
  do
  {
    m_nTodo_164 = this->m_nTodo_164;
    if ( this->ml_ListProp.m_column[2].head[m_nTodo_164 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * m_nTodo_164 + 20] = this->m_nTodo_168
                                                                            * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                            + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                             - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                            / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 20];
      (((UIWnd *)&this->m_EquipFlag.m_text[152 * this->m_nTodo_164 + 16]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]);
      ++this->m_nTodo_168;
    }
    result = this->m_nTodo_164 + 1;
    this->m_nTodo_164 = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0045B440
int PropUI::ShowCategory2(unsigned __int8 pData)
{
  void ( **v3)(UIScrollBar *, _DWORD); // edx
  int m_nTodo_164; // edi
  int result; // eax

  v3 = (void ( **)(UIScrollBar *, _DWORD))((UIWnd *)&this->ml_ListProp.m_scrollbar);
  this->ml_ListProp.m_column[2].head[30] = pData;
  (*v3)(&this->ml_ListProp.m_scrollbar, pData);
  this->m_nTodo_168 = 0;
  this->m_nTodo_164 = 0;
  do
  {
    m_nTodo_164 = this->m_nTodo_164;
    if ( this->ml_ListProp.m_column[2].head[m_nTodo_164 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * m_nTodo_164 + 20] = this->m_nTodo_168
                                                                            * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                            + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                             - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                            / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 20];
      (((UIWnd *)&this->m_EquipFlag.m_text[152 * this->m_nTodo_164 + 16]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]);
      ++this->m_nTodo_168;
    }
    result = this->m_nTodo_164 + 1;
    this->m_nTodo_164 = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0045B560
int PropUI::ShowCategory3(unsigned __int8 pData)
{
  void ( **m_style)(int *, _DWORD); // edx
  int m_nTodo_164; // edi
  int result; // eax

  m_style = (void ( **)(int *, _DWORD))this->ml_ListProp.m_scrollbar.m_bk.m_style;
  this->ml_ListProp.m_column[2].head[31] = pData;
  (*m_style)(&this->ml_ListProp.m_scrollbar.m_bk.m_style, pData);
  this->m_nTodo_168 = 0;
  this->m_nTodo_164 = 0;
  do
  {
    m_nTodo_164 = this->m_nTodo_164;
    if ( this->ml_ListProp.m_column[2].head[m_nTodo_164 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * m_nTodo_164 + 20] = this->m_nTodo_168
                                                                            * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                            + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                             - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                            / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 20];
      (((UIWnd *)&this->m_EquipFlag.m_text[152 * this->m_nTodo_164 + 16]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]);
      ++this->m_nTodo_168;
    }
    result = this->m_nTodo_164 + 1;
    this->m_nTodo_164 = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0045B680
int PropUI::ShowCategory4(unsigned __int8 pData)
{
  void ( **left)(tagRECT *, _DWORD); // edx
  int m_nTodo_164; // edi
  int result; // eax

  left = (void ( **)(tagRECT *, _DWORD))this->ml_ListProp.m_scrollbar.m_btnrect[0].left;
  this->ml_ListProp.m_column[2].head[32] = pData;
  (*left)(this->ml_ListProp.m_scrollbar.m_btnrect, pData);
  this->m_nTodo_168 = 0;
  this->m_nTodo_164 = 0;
  do
  {
    m_nTodo_164 = this->m_nTodo_164;
    if ( this->ml_ListProp.m_column[2].head[m_nTodo_164 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * m_nTodo_164 + 20] = this->m_nTodo_168
                                                                            * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                            + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                             - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                            / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24]
                                                                                  + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 20];
      (((UIWnd *)&this->m_EquipFlag.m_text[152 * this->m_nTodo_164 + 16]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_column[1].head[16 * this->m_nTodo_164 + 16]);
      ++this->m_nTodo_168;
    }
    result = this->m_nTodo_164 + 1;
    this->m_nTodo_164 = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046D140
int PropUI::InitUI()
{
  int bkWndY; // eax

  ((UIListBox *)this)->UIListBox::UIListBox();
  this->bkWndX = 800;
  this->bkWndY = 600;
  this->m_ListWidth = 300;
  this->m_ListHeight = 400;
  *(_WORD *)(&this->m_PropData.m_Dicker + 1) = 0;
  *(&this->m_nTodo_3650 + 20) = 0;
  this->m_nTodo_36A4 = 0;
  memset(&this->m_nTodo_36A4 + 1, 0, 0x640u);
  memset(&this->m_nTodo_42D0 + 22, 0, 0x190u);
  memset(&this->m_nTodo_3C90 + 22, 0, 0x640u);
  *(_DWORD *)&this->m_PropData.m_Type = 0;
  this->p_DealData = ((PlayerItem *)0);
  this->m_ListSelNum = ((int *)0);
  this->m_MaxNum = ((int *)0);
  this->m_Sum = 0;
  this->i = 0;
  this->j = 0;
  this->_isCreatable = 0;
  (((UIFrameContainer *)&this->m_Frame))->UIFrameContainer::ResetContainerState();
  ((UI3DCtrl *)&this->m_EmbedUI3DCtrl)->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)&this->m_FrameBar.m_tex))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  ((PalScript *)&this->m_OutFrameL.m_rect.right)->PalScript::PalScript();
  ((UIRoleDialog *)&this->m_Role[1].m_bvisible)->UIRoleDialog::UIRoleDialog();
  (((UIProgressBar *)((char *)&this->m_Msg.m_btRc + 40)))->UIProgressBar::ctor();
  (((UIFrameContainer *)(&this->m_Msg.pCallbackVtable2 + 1)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->m_Msg.pCallbackVtable2 + 43)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_EmbedSubPanel))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_3DObj.m_numobj))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_3DObj.m_obj[4].m_pos))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Dlg.m_ratioh))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_ListGrid[10].m_rect))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_ListGrid[11].m_rect))->UIFrameContainer::ResetContainerState();
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::UpdateKeyCtrl();
  NameSys::GetSys();
  NameSys::GetSys();
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[40] = 32;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[44] = 16;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[48] = 0;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[52] = 0;
  (((UIFrameContainer *)&this->ml_ListProp.m_column[7].items.capacity))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_nCaptionOverlay))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_btnGroup.m_btnUp.m_benable))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_btnGroup.m_btnUp.m_caption[20]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_btnGroup.m_btnDw.m_childs))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)&this->mb_OK.m_texarray.m_ptex[1]))->UIFrameContainer::ResetContainerState();
  *(_DWORD *)&this->mb_OK.m_caption[60] = 0;
  *(_DWORD *)&this->mb_OK.m_caption[64] = 0;
  *(_DWORD *)&this->mb_OK.m_caption[68] = 0;
  this->mb_OK.m_caption[72] = 0;
  this->mb_OK.m_caption[73] = 0;
  *(_DWORD *)&this->mb_OK.m_caption[76] = 0;
  *(_DWORD *)&this->mb_OK.m_caption[80] = 1065353216;
  *(_DWORD *)&this->mb_OK.m_caption[84] = 0;
  memset(&this->m_PropData, 0, 0x4460u);
  bkWndY = this->bkWndY;
  LOBYTE(this->m_Role[1].m_childs.m_needscriptdel) = 1;
  LOBYTE(this->m_Role[1].m_bcreateok) = 0;
  this->m_Role[1].m_childs.m_pData = (char *)(bkWndY / 4);
  HIBYTE(this->m_Role[1].m_childs.m_needscriptdel) = 0;
  BYTE2(this->m_Role[1].m_childs.m_needscriptdel) = 0;
  BYTE1(this->m_Role[1].m_childs.m_needscriptdel) = 0;
  this->m_Role[1].m_pfather = (UIWnd *)68;
  this->m_Role[1].m_childs.capacity = 65;
  this->m_Role[1].m_childs.m_nSize = 86;
  this->mb_OK.m_caption[96] = 1;
  return (int)this;
}

// 0x0046D4E0
PropUI::~PropUI()
{
  int *m_ListSelNum; // eax

  m_ListSelNum = (int *)this->m_ListSelNum;
  if ( m_ListSelNum )
  {
    operator delete(m_ListSelNum);
    this->m_ListSelNum = ((int *)0);
  }
  if ( this->m_MaxNum )
  {
    operator delete(this->m_MaxNum);
    this->m_MaxNum = ((int *)0);
  }
  this->_isCreatable = 0;
  *(_DWORD *)&this->mb_OK.m_caption[84] = 0;
  Destroy__ovl_03((int)this);
  (((UIFrameContainer *)&this->mb_OK.m_texarray.m_ptex[1]))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)&this->m_MoneyRemark.m_ratiow))->UICaption::Destroy2();
  (((UICaption *)&this->m_PropRemark.m_childs))->UICaption::Destroy2();
  (((UICaption *)&this->m_btnGroup.m_btnDw.m_caption[12]))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_btnGroup.m_btnDw.m_childs))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_btnGroup.m_btnUp.m_caption[20]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_btnGroup.m_btnUp.m_benable))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_nCaptionOverlay))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->ml_ListProp.m_column[7].items.capacity))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)&this->ml_ListProp.m_column[3].head[32]))->UICaption::Destroy2();
  (((UICaption *)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]))->UICaption::Destroy2();
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::DeleteRow();
  (((UIFrameContainer *)&this->m_ListGrid[11].m_rect))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_ListGrid[10].m_rect))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Dlg.m_ratioh))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_3DObj.m_obj[4].m_pos))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_3DObj.m_numobj))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_EmbedSubPanel))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(&this->m_Msg.pCallbackVtable2 + 43)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(&this->m_Msg.pCallbackVtable2 + 1)))->UIFrameContainer::~UIFrameContainer();
  (((PalScript *)((char *)&this->m_Msg.m_btRc + 40)))->PalScript::Reset();
  (((UIRoleDialog *)&this->m_Role[1].m_bvisible))->UIRoleDialog::~UIRoleDialog();
  (((PalScript *)&this->m_OutFrameL.m_rect.right))->PalScript::ctor();
  (((UICaption *)&this->m_OutFrameT))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_FrameBar.m_tex))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((UIFrameWnd *)&this->m_EmbedUI3DCtrl);
  (((UIFrameContainer *)&this->m_Frame))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x0046DD10
int PropUI::UpdateItemList(const void *arg0)
{
  st_Manager *p_m_PropData; // ebx
  int *v4; // edi
  unsigned int v5; // edx
  int m_nTodo_36A4; // eax
  int **p_m_nTodo_4008; // edi
  int *v8; // eax
  int v9; // ecx
  int *v10; // ebx
  int v11; // ecx
  UIListBox *p_m_pfather; // [esp+0x10] [ebp-0x18]
  int nVal; // [esp+0x14] [ebp-0x14]
  int v15; // [esp+0x18] [ebp-0x10]
  int p_DWORD; // [esp+0x1C] [ebp-0xC] BYREF
  int v17; // [esp+0x20] [ebp-0x8]
  int *v18; // [esp+0x24] [ebp-0x4]
  const void *arg0a; // [esp+0x2C] [ebp+0x4]

  p_m_PropData = (st_Manager *)&this->m_PropData;
  memset(&this->m_PropData, 0, 0x4460u);
  p_m_pfather = (UIListBox *)&this->m_ListGrid[12].m_pfather;
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::ClearAll();
  qmemcpy(p_m_PropData, arg0, 0x4460u);
  if ( this->m_MaxNum )
  {
    operator delete(this->m_MaxNum);
    this->m_MaxNum = ((int *)0);
  }
  v4 = (int *)operator new(4 * this->m_nTodo_36A4);
  v5 = 4 * this->m_nTodo_36A4;
  this->m_MaxNum = ((int *)(v4));
  memset(v4, 0, v5);
  v15 = 0;
  m_nTodo_36A4 = this->m_nTodo_36A4;
  p_DWORD = 0xFFFF;
  v17 = 0;
  v18 = 0;
  if ( m_nTodo_36A4 > 0 )
  {
    p_m_nTodo_4008 = (int **)&this->m_nTodo_4008;
    arg0a = (const void *)(-16392 - (_DWORD)this);
    do
    {
      v8 = (int *)*p_m_nTodo_4008;
      v9 = **p_m_nTodo_4008;
      v17 = 1;
      p_DWORD = v9;
      v18 = (int *)v8;
      v10 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD);
      sprintf(this->buf, "%s", *p_m_nTodo_4008 + 1);
      nVal = (((UIListBox *)p_m_pfather))->UIListBox::LoadListItems(this->buf, 0);
      sprintf(this->buf, (const char *)&dir[20], 0);
      (((UIListBox *)p_m_pfather))->UIListBox::SetMouseMoveSel(2, nVal, this->buf, 0);
      if ( v10 )
        *(int *)((char *)this->m_MaxNum + (unsigned int)p_m_nTodo_4008 + (_DWORD)arg0a) = 99 - v10[1];
      else
        *(int *)((char *)this->m_MaxNum + (unsigned int)arg0a + (_DWORD)p_m_nTodo_4008) = 99;
      if ( this->mb_OK.m_caption[73] )
      {
        *(int *)((char *)this->m_MaxNum + (unsigned int)p_m_nTodo_4008 + (_DWORD)arg0a) = *(_DWORD *)&this->mb_OK.m_caption[76];
        sprintf(
          this->buf,
          (const char *)&dir[20],
          (unsigned int)(__int64)((double)(*p_m_nTodo_4008)[152] * *(float *)&this->mb_OK.m_caption[80]));
      }
      else
      {
        sprintf(this->buf, (const char *)&dir[20], (*p_m_nTodo_4008)[152]);
      }
      (((UIListBox *)p_m_pfather))->UIListBox::SetMouseMoveSel(1, nVal, this->buf, 0);
      v11 = this->m_nTodo_36A4;
      ++p_m_nTodo_4008;
      ++v15;
    }
    while ( v15 < v11 );
  }
  return (((UIListBox *)p_m_pfather))->UIListBox::GetItem();
}

// 0x0046DF40
int PropUI::InitPlayerList(int nVal)
{
  int bkWndX; // ecx
  gbTexture *m_tex; // edx
  int v5; // ecx
  int m_EmbedUI3DCtrl; // eax
  int v7; // eax
  int v8; // edx
  float m_ratioh; // edx
  int v10; // ecx
  LONG left; // eax
  int m_num; // eax
  int v13; // ecx
  float v14; // edx
  UIWnd *m_pfather; // eax
  char *v16; // eax
  int v17; // ecx
  int i; // ecx
  int v19; // ebp
  _PlugInfo *v20; // edx
  _PlugInfo *v21; // ecx
  _PlugInfo *v22; // eax
  char *v23; // ebp
  int capacity; // eax
  int v25; // edx
  int m_nCaptionOverlay; // edx
  int m_benable; // edx
  LONG v28; // edx
  int v29; // ecx
  int v30; // edx
  char *m_pData; // eax
  int v32; // ecx
  int v33; // eax
  int v34; // edx
  int v35; // ecx
  int v36; // edx
  int m_numobj; // edx
  int v38; // ecx
  float x; // edx
  int v40; // eax
  LONG right; // edx
  int v42; // ecx
  int v43; // edx
  LONG top; // edx
  gbTexture *v45; // eax
  char *v46; // edx
  int m_align; // ecx
  char *v48; // eax
  int v49; // ecx
  int v50; // eax
  int result; // eax
  int v52; // [esp+FCh] [ebp-0x10C]
  int v53; // [esp+FCh] [ebp-0x10C]
  int v54; // [esp+0x110] [ebp-F8h] BYREF
  int v55; // [esp+0x114] [ebp-F4h]
  int v56; // [esp+0x118] [ebp-F0h]
  int v57; // [esp+0x11C] [ebp-ECh]
  _DWORD v58[2]; // [esp+0x120] [ebp-E8h] BYREF
  int v59; // [esp+0x128] [ebp-E0h]
  int v60; // [esp+0x12C] [ebp-DCh]
  int v61; // [esp+0x130] [ebp-D8h]
  char *v62; // [esp+0x134] [ebp-D4h]
  gbTexture *v63; // [esp+0x138] [ebp-D0h] BYREF
  char *v64; // [esp+0x13C] [ebp-CCh]
  int *p_RefCount; // [esp+0x140] [ebp-C8h]
  char *v66; // [esp+0x144] [ebp-C4h]
  _DWORD v67[4]; // [esp+0x148] [ebp-C0h] BYREF
  gbVec3D pPos; // [esp+0x158] [ebp-B0h] BYREF
  int v69; // [esp+0x164] [ebp-A4h]
  _DWORD v70[4]; // [esp+0x168] [ebp-A0h] BYREF
  _DWORD v71[4]; // [esp+0x178] [ebp-0x90] BYREF
  _DWORD v72[4]; // [esp+0x188] [ebp-0x80] BYREF
  _DWORD v73[4]; // [esp+0x198] [ebp-0x70] BYREF
  gbVec3D pDir; // [esp+0x1A8] [ebp-0x60] BYREF
  int v75; // [esp+0x1B4] [ebp-0x54]
  _DWORD v76[4]; // [esp+0x1B8] [ebp-0x50] BYREF
  _DWORD v77[8]; // [esp+0x1C8] [ebp-0x40] BYREF
  _DWORD v78[6]; // [esp+0x1E8] [ebp-0x20] BYREF
  int v79; // [esp+0x200] [ebp-0x8]
  int bkWndY; // [esp+0x204] [ebp-0x4]

  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, 0, 0, 800, 600) /* [ROWTABLE] */;
  bkWndX = this->bkWndX;
  m_tex = (gbTexture *)this->m_FrameBar.m_tex;
  bkWndY = this->bkWndY;
  v79 = bkWndX;
  v72[1] = 22;
  v72[0] = 266;
  v72[2] = 482;
  v72[3] = 150;
  ((void ( *)(gbTexture **, int, _DWORD *, PropUI *))m_tex->IsLoaded)(&this->m_FrameBar.m_tex, 513, v72, this);
  LOBYTE(v5) = this->mb_OK.m_caption[96];
  (((UIPushButton *)&this->m_FrameBar.m_tex))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\BuyFlag.tga", v5);
  m_EmbedUI3DCtrl = this->m_EmbedUI3DCtrl;
  v70[1] = 564;
  v70[0] = 0;
  v70[2] = 800;
  v70[3] = 599;
  (*(void ( **)(int *, int, _DWORD *, char *, _DWORD, PropUI *))(m_EmbedUI3DCtrl + 28))(
    &this->m_EmbedUI3DCtrl,
    513,
    (_DWORD *)(v70),
    "UI\\Flex\\framebar.tga",
    0,
    this);
  (((CScreenMode *)&this->m_EmbedUI3DCtrl))->CScreenMode::SetPosition(30,   35);
  v7 = (int)((UIWnd *)&this->m_Frame);
  v78[1] = 0;
  v78[0] = 0;
  v78[2] = 206;
  v78[3] = 600;
  (*(void ( **)(UIStatic *, int, _DWORD *, PropUI *))(v7 + 16))(&this->m_Frame, 513, (_DWORD *)(v78), this);
  LOBYTE(v8) = this->mb_OK.m_caption[96];
  (((UIPushButton *)&this->m_Frame))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\Frame.tga", v8);
  v67[1] = 32;
  v67[0] = 454;
  m_ratioh = this->m_Dlg.m_ratioh;
  v67[2] = 790;
  v67[3] = 425;
  (*(void ( **)(float *, int, _DWORD *, PropUI *))(LODWORD(m_ratioh) + 16))(
    &this->m_Dlg.m_ratioh,
    513,
    (_DWORD *)(v67),
    this);
  LOBYTE(v10) = this->mb_OK.m_caption[96];
  (((UIPushButton *)&this->m_Dlg.m_ratioh))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ListFrame.tga", v10);
  left = this->m_ListGrid[11].m_rect.left;
  v77[1] = 50;
  v77[0] = 476;
  v77[2] = 782;
  v77[3] = 82;
  (*(void ( **)(tagRECT *, int, _DWORD *, PropUI *))(left + 16))(&this->m_ListGrid[11].m_rect, 513, (_DWORD *)(v77), this);
  (((UIScene *)&this->m_ListGrid[11].m_rect))->UIScene::SetShow(0);
  sprintf(
    this->buf,
    "%s                %s   %s",
    (const char *)&dword_DC353C,
    (const char *)&dword_DC363C,
    (const char *)&dword_DC373C);
  SetEnable((UICaption *)&this->m_ListGrid[11].m_rect);
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15] = (gbTexture *)79;
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[14] = (gbTexture *)476;
  this->ml_ListProp.m_scrollbar.m_texarray.m_num = 769;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[0] = (_PlugInfo *)((char *)&this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15][3].InFmt.g_mask
                                                                + 2);
  m_num = this->ml_ListProp.m_scrollbar.m_texarray.m_num;
  LODWORD(pPos.y) = (unsigned long)((char *)&this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15]->NameCrc32 + 3);
  v69 = LODWORD(pPos.y) + 26;
  LODWORD(pDir.y) = LODWORD(pPos.y) + 253;
  v13 = LODWORD(pPos.y) + 279;
  v75 = LODWORD(pPos.y) + 279;
  LOBYTE(v13) = this->mb_OK.m_caption[96];
  LODWORD(pPos.x) = m_num - 31;
  LODWORD(v14) = m_num - 31 + 22;
  LODWORD(pDir.x) = m_num - 31;
  m_pfather = this->m_ListGrid[12].m_pfather;
  pPos.z = v14;
  pDir.z = v14;
  ((void ( *)(UIWnd **, int, gbTexture **, PropUI *, _DWORD, int, int))m_pfather->m_rect.bottom)(
    &this->m_ListGrid[12].m_pfather,
    259,
    &this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[14],
    this,
    0,
    1,
    v13);
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetLockSel(23);
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[2] = (gbTexture *)-4;
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[3] = (gbTexture *)-6;
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[4] = (gbTexture *)10;
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[14], 38, 27, 0);
  (((CCBUI *)&this->m_ListGrid[12].m_pbk))->CCBUI::ShowEffect((int)((gbRefObject *)this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15]) + 1, this->ml_ListProp.m_scrollbar.m_texarray.m_num - 38, this->ml_ListProp.m_scrollbar.m_texarray.m_num);
  (((CCBUI *)&this->m_ListGrid[12].m_pbk))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&this->m_ListGrid[12].m_pbk))->CCBUI::SetSelection(27);
  (((CCBUI *)&this->m_ListGrid[12].m_pbk))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetColumnHead((int)"Name", 168);
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetColumnHead((int)"Price", 51);
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetColumnHead((int)"Num1", 38);
  (((CCBUI *)&this->m_ListGrid[12].m_pbk))->CCBUI::VirtualCall(1);
  v16 = (char *)((gbRefObject *)this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15]) + 2;
  v63 = (gbTexture *)this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[14];
  v64 = (char *)v16;
  p_RefCount = (int *)&v63[3].RefCount;
  v66 = (char *)(v16 + 23);
  this->i = 0;
  do
  {
    (*(void ( **)(int *, int, gbTexture **, PropUI *))(*(&this->m_TalkFrame.m_bvisible
                                                                            + 38 * this->i)
                                                                          + 16))(
      &this->m_TalkFrame.m_bvisible + 38 * this->i,
      513,
      &v63,
      this);
    LOBYTE(v17) = this->mb_OK.m_caption[96];
    (((UIPushButton *)(&this->m_TalkFrame.m_bvisible + 38 * this->i)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\Buy_Grid.tga", v17);
    i = this->i;
    v64 = (char *)v66;
    v66 += 23;
    this->i = i + 1;
  }
  while ( i + 1 < 13 );
  this->mb_OK.m_offsety = 0.0f;
  this->mb_OK.m_offsetx = 0;
  *(_DWORD *)&this->mb_OK.m_bBigFont = 90;
  this->mb_OK.m_texarray.m_ptex[0] = (gbTexture *)(LODWORD(this->mb_OK.m_offsety) + 32);
  ((void ( *)(gbTexture **, int, int *, PropUI *))this->mb_OK.m_texarray.m_ptex[1]->IsLoaded)(
    &this->mb_OK.m_texarray.m_ptex[1],
    513,
    &this->mb_OK.m_offsetx,
    this);
  (((UIScene *)&this->mb_OK.m_texarray.m_ptex[1]))->UIScene::SetShow(0);
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->mb_OK.m_texarray.m_ptex[1]))(
    &this->mb_OK.m_texarray.m_ptex[1],
    0);
  LOBYTE(v61) = this->mb_OK.m_caption[96];
  v19 = v61;
  v52 = v61;
  v62 = (char *)"UI\\Assistant\\Communal\\Add";
  v20 = (_PlugInfo *)this->ml_ListProp.m_scrollbar.m_texarrayInfo[9];
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[40] = 24;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[44] = 40;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[2] = (_PlugInfo *)158;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[1] = (_PlugInfo *)476;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[3] = (_PlugInfo *)500;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[4] = (_PlugInfo *)198;
  (*(void ( **)(int, _PlugInfo **, PropUI *, char *, _DWORD, int))&v20->name[24])(
    546,
    &this->ml_ListProp.m_scrollbar.m_texarrayInfo[1],
    this,
    "UI\\Assistant\\Communal\\Sub",
    0,
    v52);
  v21 = (_PlugInfo *)this->ml_ListProp.m_scrollbar.m_texarrayInfo[1];
  v22 = (_PlugInfo *)this->ml_ListProp.m_scrollbar.m_texarrayInfo[4];
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[6] = v22;
  v53 = v19;
  v23 = (char *)v62;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[5] = v21;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[7] = this->ml_ListProp.m_scrollbar.m_texarrayInfo[3];
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[8] = (_PlugInfo *)((char *)v22
                                                                + *(_DWORD *)&this->ml_ListProp.m_column[7].head[44]);
  (*(void ( **)(int, _PlugInfo **, PropUI *, char *, _DWORD, int))(*(_DWORD *)&this->ml_ListProp.m_column[3].head[32]
                                                                          + 28))(
    547,
    &this->ml_ListProp.m_scrollbar.m_texarrayInfo[5],
    this,
    v23,
    0,
    v53);
  this->ml_ListProp.m_column[7].head[56] = v61;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[48] = 1;
  (((PalScript *)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnSub.tga", this->ml_ListProp.m_column[7].head[56]);
  (((PalScript *)&this->ml_ListProp.m_column[3].head[32]))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnAdd.tga", this->ml_ListProp.m_column[7].head[56]);
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[52] = 20;
  ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
    &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
    0);
  (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
  capacity = this->ml_ListProp.m_column[7].items.capacity;
  v55 = 142;
  v54 = 218;
  v56 = 450;
  v57 = 556;
  (*(void ( **)(int *, int, int *, PropUI *))(capacity + 16))(
    &this->ml_ListProp.m_column[7].items.capacity,
    161,
    &v54,
    this);
  LOBYTE(v25) = this->mb_OK.m_caption[96];
  (((UIPushButton *)&this->ml_ListProp.m_column[7].items.capacity))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Info.tga", v25);
  m_nCaptionOverlay = this->m_nCaptionOverlay;
  v55 = 388;
  v54 = 232;
  v56 = 444;
  v57 = 556;
  (*(void ( **)(int *, int, int *, PropUI *))(m_nCaptionOverlay + 16))(
    &this->m_nCaptionOverlay,
    161,
    &v54,
    this);
  (((UIScene *)&this->m_nCaptionOverlay))->UIScene::SetShow(0);
  m_benable = this->m_btnGroup.m_btnUp.m_benable;
  v55 = 520;
  v54 = 232;
  v56 = 444;
  v57 = 552;
  (*(void ( **)(int *, int, int *, PropUI *))(m_benable + 16))(
    &this->m_btnGroup.m_btnUp.m_benable,
    161,
    &v54,
    this);
  (((UIScene *)&this->m_btnGroup.m_btnUp.m_benable))->UIScene::SetShow(0);
  v28 = this->m_ListGrid[10].m_rect.left;
  v71[1] = 158;
  v71[0] = 404;
  v71[2] = 420;
  v71[3] = 190;
  (*(void ( **)(tagRECT *, int, _DWORD *, PropUI *))(v28 + 16))(&this->m_ListGrid[10].m_rect, 513, (_DWORD *)(v71), this);
  LOBYTE(v29) = this->mb_OK.m_caption[96];
  (((UIPushButton *)&this->m_ListGrid[10].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Prop_word.tga", v29);
  this->m_btnGroup.m_btnDw.m_rect.right = 392;
  this->m_btnGroup.m_btnDw.m_rect.top = 478;
  this->m_btnGroup.m_btnDw.m_rect.bottom = 624;
  this->m_btnGroup.m_btnDw.m_pfather = ((UIWnd *)((UIWnd *)(this->m_btnGroup.m_btnDw.m_rect.right + 32)));
  (*(void ( **)(char *, int, LONG *, PropUI *))(*(_DWORD *)&this->m_btnGroup.m_btnUp.m_caption[20] + 16))(
    &this->m_btnGroup.m_btnUp.m_caption[20],
    272,
    &this->m_btnGroup.m_btnDw.m_rect.top,
    this);
  (((UIScene *)&this->m_btnGroup.m_btnUp.m_caption[20]))->UIScene::SetShow(0);
  sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)&this->m_btnGroup.m_btnUp.m_caption[20]);
  *(_DWORD *)this->m_btnGroup.m_btnDw.m_caption = 392;
  this->m_btnGroup.m_btnDw.m_alignmode = 638;
  *(_DWORD *)&this->m_btnGroup.m_btnDw.m_caption[4] = 764;
  *(_DWORD *)&this->m_btnGroup.m_btnDw.m_caption[8] = *(_DWORD *)this->m_btnGroup.m_btnDw.m_caption + 32;
  (*((void ( **)(PtrArray *, int, int *, PropUI *))this->m_btnGroup.m_btnDw.m_childs.m_pData + 4))(
    &this->m_btnGroup.m_btnDw.m_childs,
    261,
    &this->m_btnGroup.m_btnDw.m_alignmode,
    this);
  (((UIScene *)&this->m_btnGroup.m_btnDw.m_childs))->UIScene::SetShow(0);
  sprintf(this->buf, "%s %d", g_szCombatFieldName, this->m_Sum);
  SetEnable((UICaption *)&this->m_btnGroup.m_btnDw.m_childs);
  this->i = 0;
  do
  {
    v30 = this->m_Role[1].m_childs.capacity;
    m_pData = this->m_Role[1].m_childs.m_pData;
    v73[0] = (unsigned long)(this->m_Role[1].m_pfather);
    v73[1] = (unsigned long)m_pData;
    v73[2] = v30 + v73[0];
    v73[3] = (unsigned long)&m_pData[this->m_Role[1].m_childs.m_nSize];
    (*(void ( **)(LONG *, _DWORD, _DWORD *, PropUI *))(*(&this->m_OutFrameB.m_rect.bottom + 38 * this->i) + 16))(
      &this->m_OutFrameB.m_rect.bottom + 38 * this->i,
      *(&dword_56B608 + this->i),
      (_DWORD *)(v73),
      this);
    LOBYTE(v32) = this->mb_OK.m_caption[96];
    (((UIPushButton *)(&this->m_OutFrameB.m_rect.bottom + 38 * this->i)))->UIPushButton::CreateFromTemplate((void *)(0x56B674)[this->i], v32);
    (**((void ( ***)(LONG *, _DWORD))&this->m_OutFrameB.m_rect.bottom + 38 * this->i))((LONG *)(&this->m_OutFrameB.m_rect.bottom + 38 * this->i), (_DWORD)(0));
    v33 = this->i + 1;
    this->i = v33;
  }
  while ( v33 < 5 );
  v34 = *((_DWORD *)&this->m_Msg.pCallbackVtable2 + 43);
  v58[1] = 437;
  v58[0] = 456;
  v59 = 486;
  v60 = 556;
  (*(void ( **)(void **, int, _DWORD *, PropUI *))(v34 + 16))(
    &this->m_Msg.pCallbackVtable2 + 43,
    513,
    (_DWORD *)(v58),
    this);
  LOBYTE(v35) = this->mb_OK.m_caption[96];
  (((UIPushButton *)(&this->m_Msg.pCallbackVtable2 + 43)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\EquipTopFrame\\TopFrameLS.tga", v35);
  v58[0] = v59;
  v59 += 256;
  (*(void ( **)(int *, int, _DWORD *, PropUI *))(this->m_EmbedSubPanel + 16))(
    &this->m_EmbedSubPanel,
    513,
    (_DWORD *)(v58),
    this);
  LOBYTE(v36) = this->mb_OK.m_caption[96];
  (((UIPushButton *)&this->m_EmbedSubPanel))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\PropTopFrame\\TopFrameRM.tga", v36);
  m_numobj = this->m_3DObj.m_numobj;
  v58[0] = v59;
  v59 += 32;
  (*(void ( **)(int *, int, _DWORD *, PropUI *))(m_numobj + 16))(
    &this->m_3DObj.m_numobj,
    513,
    (_DWORD *)(v58),
    this);
  LOBYTE(v38) = this->mb_OK.m_caption[96];
  (((UIPushButton *)&this->m_3DObj.m_numobj))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\EquipTopFrame\\TopFrameR.tga", v38);
  x = this->m_3DObj.m_obj[4].m_pos.x;
  this->m_Dlg.pDebugTex = ((gbTexture *)((gbTexture *)446));
  this->m_Dlg.m_bfocus = 489;
  this->m_Dlg.m_align = 745;
  LODWORD(this->m_Dlg.m_ratiow) = 546;
  (*(void ( **)(gbVec3D *, int, int *, PropUI *))(LODWORD(x) + 16))(
    &this->m_3DObj.m_obj[4].m_pos,
    521,
    &this->m_Dlg.m_bfocus,
    this);
  (((UIScene *)&this->m_3DObj.m_obj[4].m_pos))->UIScene::SetShow(0);
  (*(void ( **)(gbVec3D *, _DWORD))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(&this->m_3DObj.m_obj[4].m_pos, 0);
  v40 = LODWORD(this->m_Dlg.m_ratiow) - 36;
  v76[0] = this->m_Dlg.m_align - 36;
  v76[1] = v40;
  v76[2] = v76[0] + 24;
  right = this->m_OutFrameL.m_rect.right;
  v76[3] = v40 + 32;
  (*(void ( **)(LONG *, int, _DWORD *, PropUI *))(right + 16))(&this->m_OutFrameL.m_rect.right, 2, (_DWORD *)(v76), this);
  (((UIScene *)&this->m_OutFrameL.m_rect.right))->UIScene::LoadResource("ui\\scene\\page");
  UIScene_SetController(0x40000000);
  (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
  LOBYTE(v42) = this->mb_OK.m_caption[96];
  v43 = *(_DWORD *)&this->m_btnGroup.m_btnDw.m_caption[12];
  this->m_PropRemark.m_rect.top = 569;
  this->m_PropRemark.m_rect.left = 300;
  this->m_PropRemark.m_rect.right = 390;
  this->m_PropRemark.m_rect.bottom = 594;
  (*(void ( **)(char *, int, tagRECT *, PropUI *, char *, _DWORD, int))(v43 + 28))(
    &this->m_btnGroup.m_btnDw.m_caption[12],
    518,
    &this->m_PropRemark.m_rect,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v42);
  top = this->m_PropRemark.m_rect.top;
  this->m_MoneyRemark.m_align = this->m_PropRemark.m_rect.bottom;
  v45 = (gbTexture *)(this->m_PropRemark.m_rect.right + 66);
  this->m_MoneyRemark.m_bfocus = top;
  v46 = this->m_PropRemark.m_childs.m_pData;
  this->m_MoneyRemark.m_benable = (int)v45;
  v45 = (gbTexture *)((char *)v45 + 90);
  this->m_MoneyRemark.pDebugTex = ((gbTexture *)(v45));
  LOBYTE(v45) = this->mb_OK.m_caption[96];
  (*((void ( **)(PtrArray *, int, int *, PropUI *, char *, _DWORD, gbTexture *))v46 + 7))(
    &this->m_PropRemark.m_childs,
    520,
    &this->m_MoneyRemark.m_benable,
    this,
    "UI\\Assistant\\Communal\\bDicker",
    0,
    v45);
  sub_445E50((int)&this->m_PropRemark.m_childs);
  (((PalScript *)&this->m_PropRemark.m_childs))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnDicker.tga", this->mb_OK.m_caption[96]);
  m_align = this->m_MoneyRemark.m_align;
  LODWORD(this->mb_OK.m_ratiow) = this->m_MoneyRemark.m_bfocus;
  v48 = (char *)&this->m_MoneyRemark.pDebugTex->InFmt.r_shift + 2;
  *(_DWORD *)&this->mb_OK.m_canctrl = m_align;
  LOBYTE(m_align) = this->mb_OK.m_caption[96];
  *(_DWORD *)&this->mb_OK.m_hasDBclk = (_DWORD)v48;
  this->mb_OK.m_state = (UIButton_UIBUTTON_STATE)(v48 + 90);
  (*(void ( **)(float *, int, _BYTE *, PropUI *, char *, _DWORD, int))(LODWORD(this->m_MoneyRemark.m_ratiow)
                                                                                          + 28))(
    &this->m_MoneyRemark.m_ratiow,
    519,
    &this->mb_OK.m_hasDBclk,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    m_align);
  v49 = v79 - 38;
  v50 = bkWndY - 50;
  this->m_Flag.m_nTextW = bkWndY - 50;
  this->m_Flag.m_FVF = v49;
  v49 += 38;
  this->m_nTodo_486C = v49;
  LOBYTE(v49) = this->mb_OK.m_caption[96];
  this->m_nTodo_4870 = v50 + 48;
  (*(void ( **)(UIStatic *, int, int *, PropUI *, char *, _DWORD, int))(*(_DWORD *)((UIWnd *)&this->m_OutFrameT) + 28))(
    &this->m_OutFrameT,
    514,
    &this->m_Flag.m_FVF,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    0,
    v49);
  (((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40)))->CCBFiveNimbusWindow::CreateScriptAndCamera(545, (int)this);
  if ( !strcmp("D16", unk_C10D38) )
    sprintf(this->buf, "%s", "NONE");
  else
    sprintf(this->buf, "Item\\%s\\%s.pol", "D16", "D16");
  (((PalScript *)(&this->m_Msg.m_btRc + 7)))->PalScript::LoadModel(this->buf, 0);
  *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
  *((_DWORD *)&this->m_Msg.m_btRc + 27) = 1;
  (((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40)))->CCBFiveNimbusWindow::SetFloatParam(100.0);
  (((Camera *)((char *)&this->m_Msg.m_btRc + 40)))->Camera::UpdateCameraLookAt(330, 258, 600);
  sub_43A090((int)&this->m_Msg.m_btRc + 40, 1, 0.0);
  v77[4] = 300;
  v77[7] = 300;
  v77[5] = 200;
  v77[6] = 500;
  Create__ovl_1((ARC_PlayerAtt *)&this->m_Role[1].m_bvisible);
  (((UIItem *)&this->m_Role[1].m_bvisible))->UIItem::SetData(18);
  result = *(_DWORD *)&this->mb_OK.m_caption[84];
  if ( result )
  {
    if ( !--result )
    {
      this->_isCreatable = 1;
      *(_DWORD *)&this->mb_OK.m_caption[92] = nVal;
      return result;
    }
  }
  else
  {
    *(_DWORD *)&this->mb_OK.m_caption[88] = nVal;
  }
  this->_isCreatable = 1;
  return result;
}

// 0x0046EC30
int PropUI::SetSlotLock(int nVal)
{
  int result; // eax

  result = nVal;
  if ( nVal < 2 )
    *(_DWORD *)&this->mb_OK.m_caption[84] = nVal;
  return result;
}

// 0x0046EC50
bool PropUI::CheckMode(unsigned int dwVal)
{
  return dwVal <= 1 && *(_DWORD *)&this->mb_OK.m_caption[84] == dwVal;
}

// 0x0046EC70
int PropUI::SetSceneStates(unsigned __int8 pData)
{
  sub_445E50((int)&this->m_OutFrameT);
  sub_445E50((int)&this->m_btnGroup.m_btnDw.m_caption[12]);
  sub_445E50((int)&this->m_PropRemark.m_childs);
  return sub_445E50((int)&this->m_MoneyRemark.m_ratiow);
}

// 0x0046ECC0
int PropUI::DisplayItemInfo()
{
  int m_nTodo_36A4; // eax
  int i; // eax
  int v4; // eax
  int *m_ListSelNum; // edx
  int *v6; // edx
  int v7; // ebp
  int v8; // ecx
  int v9; // eax
  int m_Sum; // eax
  int v11; // ebp
  PlayerItem *v12; // eax
  FightItem **p_item; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int *v20; // eax
  int v21; // ecx
  int v22; // eax
  int p_DWORD; // [esp+0x10] [ebp-0xC] BYREF
  int v25; // [esp+0x14] [ebp-0x8]
  int v26; // [esp+0x18] [ebp-0x4]

  if ( *(_DWORD *)&this->mb_OK.m_caption[60] )
  {
    operator delete(*(void **)&this->mb_OK.m_caption[60]);
    *(_DWORD *)&this->mb_OK.m_caption[60] = 0;
  }
  *(_DWORD *)&this->mb_OK.m_caption[60] = (unsigned long)operator new(4 * *(_DWORD *)&this->mb_OK.m_caption[64]);
  m_nTodo_36A4 = this->m_nTodo_36A4;
  *(_DWORD *)&this->mb_OK.m_caption[68] = 0;
  this->i = 0;
  if ( m_nTodo_36A4 > 0 )
  {
    do
    {
      i = this->i;
      *((_BYTE *)&this->m_nTodo_42D0 + i + 288) = this->m_ListSelNum[i] > 0;
      v4 = this->i;
      m_ListSelNum = (int *)this->m_ListSelNum;
      this->j = 0;
      if ( m_ListSelNum[v4] > 0 )
      {
        do
        {
          *(_DWORD *)(*(_DWORD *)&this->mb_OK.m_caption[60] + 4 * *(_DWORD *)&this->mb_OK.m_caption[68]) = **((_DWORD **)&this->m_nTodo_4008 + v4);
          v6 = (int *)this->m_ListSelNum;
          v7 = this->j + 1;
          ++*(_DWORD *)&this->mb_OK.m_caption[68];
          v4 = this->i;
          this->j = v7;
        }
        while ( v7 < v6[v4] );
      }
      v8 = this->m_nTodo_36A4;
      v9 = this->i + 1;
      this->i = v9;
    }
    while ( v9 < v8 );
  }
  m_Sum = this->m_Sum;
  if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) < m_Sum )
  {
    SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
    (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(&this->m_3DObj.m_obj[4].m_pos, 1);
    (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
    LOBYTE(this->m_PropRemark.m_pfather) = 0;
    this->PropUI::SetSceneStates(1u);
    return sub_445E50((int)&this->m_ListGrid[12].m_pfather);
  }
  else
  {
    *(&g_RoleSlotBuf.dword_17AA450 + 147) -= m_Sum;
    SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
    (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(&this->m_3DObj.m_obj[4].m_pos, 1);
    (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
    LOBYTE(this->m_PropRemark.m_pfather) = 1;
    this->PropUI::SetSceneStates(0);
    sub_445E50((int)&this->m_ListGrid[12].m_pfather);
    sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
    SetEnable((UICaption *)&this->m_btnGroup.m_btnUp.m_caption[20]);
    if ( this->p_DealData )
    {
      operator delete(this->p_DealData);
      this->p_DealData = ((PlayerItem *)0);
    }
    v11 = *(_DWORD *)&this->mb_OK.m_caption[64];
    v12 = (PlayerItem *)operator new(12 * v11);
    if ( v12 )
    {
      if ( v11 - 1 >= 0 )
      {
        p_item = (FightItem **)&v12->item;
        v14 = v11;
        do
        {
          *(p_item - 2) = (FightItem *)0xFFFF;
          *(p_item - 1) = 0;
          *p_item = 0;
          p_item += 3;
          --v14;
        }
        while ( v14 );
      }
    }
    else
    {
      v12 = 0;
    }
    this->p_DealData = ((PlayerItem *)(v12));
    v15 = *(_DWORD *)&this->mb_OK.m_caption[64];
    this->i = 0;
    if ( v15 > 0 )
    {
      do
      {
        this->p_DealData[this->i].id = *(_DWORD *)(*(_DWORD *)&this->mb_OK.m_caption[60] + 4 * this->i);
        this->p_DealData[this->i].num = 1;
        this->p_DealData[this->i].item = (FightItem *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(_DWORD *)(*(_DWORD *)&this->mb_OK.m_caption[60] + 4 * this->i));
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive((int *)&this->p_DealData[this->i]);
        v16 = *(_DWORD *)&this->mb_OK.m_caption[64];
        v17 = this->i + 1;
        this->i = v17;
      }
      while ( v17 < v16 );
    }
    if ( this->p_DealData )
    {
      operator delete(this->p_DealData);
      this->p_DealData = ((PlayerItem *)0);
    }
    if ( *(_DWORD *)&this->mb_OK.m_caption[60] )
    {
      operator delete(*(void **)&this->mb_OK.m_caption[60]);
      *(_DWORD *)&this->mb_OK.m_caption[60] = 0;
    }
    *(_DWORD *)&this->mb_OK.m_caption[64] = 0;
    this->m_Sum = 0;
    sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
    SetEnable((UICaption *)&this->m_btnGroup.m_btnDw.m_childs);
    SetEnable((UICaption *)&this->m_nCaptionOverlay);
    v18 = this->m_nTodo_36A4;
    *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
    this->i = 0;
    if ( v18 > 0 )
    {
      do
      {
        this->m_ListSelNum[this->i] = 0;
        sprintf(this->buf, (const char *)&dir[20], this->m_ListSelNum[this->i]);
        (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetMouseMoveSel(2, this->i, this->buf, 0);
        v19 = this->i;
        p_DWORD = 0xFFFF;
        v25 = 0;
        v26 = 0;
        p_DWORD = **((_DWORD **)&this->m_nTodo_4008 + v19);
        v25 = 1;
        v26 = *(&this->m_nTodo_4008 + v19);
        v20 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD);
        if ( v20 )
          this->m_MaxNum[this->i] = 99 - v20[1];
        else
          this->m_MaxNum[this->i] = 99;
        if ( this->mb_OK.m_caption[73] )
          this->m_MaxNum[this->i] = *(_DWORD *)&this->mb_OK.m_caption[76];
        v21 = this->m_nTodo_36A4;
        v22 = this->i + 1;
        this->i = v22;
      }
      while ( v22 < v21 );
    }
    ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
      &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
      0);
    (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->mb_OK.m_texarray.m_ptex[1]))(
      &this->mb_OK.m_texarray.m_ptex[1],
      0);
    return (((UISceneMap *)this))->UISceneMap::RenderWithUpdate() /* [ROWTABLE] */;
  }
}

// 0x0046F160
int PropUI::UpdateCaptions()
{
  int m_nTodo_36A4; // eax
  int i; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax

  SetEnable((UICaption *)&this->m_nCaptionOverlay);
  SetEnable((UICaption *)&this->m_btnGroup.m_btnUp.m_benable);
  *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
  *(_DWORD *)&this->mb_OK.m_caption[64] = 0;
  this->m_Sum = 0;
  sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
  SetEnable((UICaption *)&this->m_btnGroup.m_btnDw.m_childs);
  m_nTodo_36A4 = this->m_nTodo_36A4;
  this->i = 0;
  if ( m_nTodo_36A4 > 0 )
  {
    do
    {
      sprintf(this->buf, (const char *)&dir[20], 0);
      (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetMouseMoveSel(2, this->i, this->buf, 0);
      i = this->i;
      if ( i < 0 || i >= (int)this->m_ScrollHB.m_ppic )
        v4 = 0;
      else
        v4 = *(&this->m_ScrollHB.m_pbkInfo->filepos + i);
      *(_DWORD *)(v4 + 68)  = (unsigned long)(this->m_ListGrid[12].m_childs.m_pData);
      v5 = this->m_nTodo_36A4;
      v6 = this->i + 1;
      this->i = v6;
    }
    while ( v6 < v5 );
  }
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetItem();
  (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetItem();
  this->PropUI::SetSceneStates(1u);
  sub_445E50((int)&this->m_ListGrid[12].m_pfather);
  (((CCBRoleState *)this))->CCBRoleState::NotifyStateChange(0);
  (**(void ( ***)(UIStatic *, int))((UIWnd *)&this->m_OutFrameT))((UIStatic *)(&this->m_OutFrameT), (int)(1));
  ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
    &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
    0);
  (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
  result = ((int ( *)(gbTexture **, _DWORD))((gbRefObject *)this->mb_OK.m_texarray.m_ptex[1]))(
             &this->mb_OK.m_texarray.m_ptex[1],
             0);
  LOBYTE(this->m_PropRemark.m_pfather) = 0;
  return result;
}

// 0x0046F300
void PropUI::UpdateItemDetail(int nItemIdx)
{
  char *buf; // edi
  CHAR *v4; // ebx
  RoleAtt *v5; // ecx
  LPCSTR v6; // eax

  buf = this->buf;
  sprintf(this->buf, unk_C10D38);
  v4 = (CHAR *)sub_458F70((LPCSTR)(*(&this->m_nTodo_4008 + nItemIdx) + 96), (int)asc_5B74B8, this->remarkbuf);
  if ( lstrlenA((const char *)v4) <= 0 )
  {
    (((RoleAtt *)v5))->RoleAtt::FormatAttributeText();
    lstrcatA(buf, v6);
  }
  else
  {
    lstrcpyA(buf, v4);
  }
  SetEnable((UICaption *)&this->m_btnGroup.m_btnUp.m_benable);
  SetEnable((UICaption *)&this->m_nCaptionOverlay);
}

// 0x0046F620
int PropUI::HandleInput(int nVal, int nVal2)
{
  this->PropUI::GetInputFlag();
  (((GRPinput *)this))->GRPinput::ProcessMouseInput(*(float *)&nVal);
  (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return 1;
}

// 0x0046F650
int PropUI::InitListUI(int arg0, int nVal, unsigned int dwVal)
{
  int *m_ListSelNum; // eax
  int *v6; // edi
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  LONG *p_right; // ecx
  UICursor *m_MaxNum; // ecx
  int v12; // edi
  int *p_m_nTodo_4008; // ebx
  int *v14; // eax
  int *v15; // eax
  CScreenMode *Instance; // eax
  int m_nTodo_36A4; // ecx
  int *v19; // edx
  int i; // eax
  int v21; // eax
  CScreenMode *v22; // eax
  int j; // edi
  int v24; // eax
  int v25; // eax
  int m_SelNum; // eax
  int v27; // eax
  int *v28; // ecx
  int v29; // eax
  CScreenMode *v30; // eax
  int v31; // eax
  int v32; // eax
  int *v33; // ebp
  int v34; // ebx
  int v35; // edi
  __int64 v36; // rax
  int v37; // ecx
  int *v38; // ecx
  int v39; // edx
  int v40; // eax
  int v41; // ebx
  int v42; // ebx
  int *v43; // eax
  int *v44; // eax
  CScreenMode *v45; // eax
  int v46; // eax
  int v47; // eax
  int *v48; // ebp
  int v49; // ebx
  int v50; // edi
  int v51; // eax
  int *v52; // ecx
  int v53; // edx
  int v54; // eax
  int v55; // ebx
  int v56; // ebx
  int v57; // edx
  int v58; // ecx
  int v59; // eax
  int *v60; // eax
  int v61; // eax
  const char *v62; // ebp
  int v63; // eax
  const char *v64; // ebp
  const char *v65; // edx
  float *v66; // eax
  float v67; // ebx
  gbTexture **v68; // edi
  float v69; // ebp
  int v70; // edx
  _PlugInfo **v71; // edi
  _PlugInfo *v72; // ecx
  _PlugInfo *v73; // eax
  int v74; // ebx
  int v75; // edx
  _PlugInfo *v76; // eax
  int v77; // ecx
  _PlugInfo *v78; // eax
  _PlugInfo *v79; // eax
  _PlugInfo *v80; // ecx
  int v81; // edx
  _PlugInfo *v82; // edx
  int v83; // eax
  _PlugInfo *v84; // eax
  _PlugInfo *v85; // edx
  int m_bfocus; // edx
  signed int v87; // ecx
  int v88; // eax
  int v89; // edi
  const void *v90; // [esp+0x0] [ebp-0x134]
  const void *v91; // [esp+0x0] [ebp-0x134]
  char *v92; // [esp+0x0] [ebp-0x134]
  char *v93; // [esp+0x0] [ebp-0x134]
  int m_Sum; // [esp+0x4] [ebp-0x130]
  int v95; // [esp+0x4] [ebp-0x130]
  int p_DWORD; // [esp+0x18] [ebp-0x11C] BYREF
  int v97; // [esp+0x1C] [ebp-0x118]
  int *v98; // [esp+0x20] [ebp-0x114]
  gbColorQuad v99; // [esp+0x24] [ebp-0x110] BYREF
  gbColorQuad v100; // [esp+0x28] [ebp-0x10C] BYREF
  int pOut; // [esp+0x2C] [ebp-0x108] BYREF
  char Buffer[253]; // [esp+0x34] [ebp-0x100] BYREF
  __int16 v103; // [esp+0x131] [ebp-0x3]
  char v104; // [esp+0x133] [ebp-0x1]

  switch ( arg0 )
  {
    case 1000:
      m_ListSelNum = (int *)this->m_ListSelNum;
      if ( nVal )
      {
        if ( m_ListSelNum )
        {
          operator delete(this->m_ListSelNum);
          this->m_ListSelNum = ((int *)0);
        }
        v6 = (int *)operator new(4 * this->m_nTodo_36A4);
        this->m_ListSelNum = ((int *)(v6));
        memset(v6, 0, 4 * this->m_nTodo_36A4);
        if ( (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetItemData() <= 0 )
        {
          this->m_SelNum = -1;
          ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
            &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
            0);
          (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
          (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
          ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->mb_OK.m_texarray.m_ptex[1]))(
            &this->mb_OK.m_texarray.m_ptex[1],
            0);
        }
        else
        {
          this->m_SelNum = 0;
          (*(void ( **)(PropUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(this, 1007, 0, 0);
          if ( this->m_nTodo_36A4 >= 0 )
            (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetItem();
        }
        LOBYTE(v7) = this->mb_OK.m_caption[96];
        (((UIPushButton *)&this->m_ListGrid[10].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Prop_word.tga", v7);
        v8 = *(_DWORD *)&this->mb_OK.m_caption[84];
        if ( v8 )
        {
          if ( v8 == 1 )
          {
            sub_445E50((int)&this->m_ListGrid[12].m_pfather);
            sub_445E50((int)&this->m_btnGroup.m_btnDw.m_caption[12]);
            (*(void ( **)(PtrArray *, _DWORD))this->m_PropRemark.m_childs.m_pData)(
              &this->m_PropRemark.m_childs,
              0);
            sub_445E50((int)&this->m_MoneyRemark.m_ratiow);
            sub_445E50((int)&this->m_OutFrameT);
            SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
            (*(void ( **)(gbVec3D *, _DWORD))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(
              &this->m_3DObj.m_obj[4].m_pos,
              0);
            (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
          }
        }
        else if ( g_bListNeedsRefresh )
        {
          (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(
            &this->m_3DObj.m_obj[4].m_pos,
            1);
          SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
          (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
          sub_445E50((int)&this->m_ListGrid[12].m_pfather);
          sub_445E50((int)&this->m_btnGroup.m_btnDw.m_caption[12]);
          (*(void ( **)(PtrArray *, int))this->m_PropRemark.m_childs.m_pData)(&this->m_PropRemark.m_childs, 1);
          sub_445E50((int)&this->m_MoneyRemark.m_ratiow);
          ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
            &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
            0);
          (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
          sub_445E50((int)&this->m_OutFrameT);
        }
        else
        {
          sub_445E50((int)&this->m_ListGrid[12].m_pfather);
          sub_445E50((int)&this->m_btnGroup.m_btnDw.m_caption[12]);
          sub_445E50((int)&this->m_MoneyRemark.m_ratiow);
          sub_445E50((int)&this->m_OutFrameT);
          (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(
            &this->m_3DObj.m_obj[4].m_pos,
            1);
          SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
          v9 = lstrlenA((const char *)(LPCSTR)&this->m_nTodo_264);
          p_right = (LONG *)&this->m_OutFrameL.m_rect.right;
          if ( v9 > 0 )
            (*(void ( **)(LONG *, int))*p_right)(p_right, 1);
          else
            (*(void ( **)(LONG *, _DWORD))*p_right)(p_right, 0);
        }
        sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
        SetEnable((UICaption *)&this->m_btnGroup.m_btnUp.m_caption[20]);
        v12 = 0;
        if ( this->m_nTodo_36A4 > 0 )
        {
          p_m_nTodo_4008 = (int *)&this->m_nTodo_4008;
          do
          {
            v14 = (int *)*p_m_nTodo_4008;
            p_DWORD = 0xFFFF;
            v97 = 0;
            v98 = 0;
            p_DWORD = (unsigned long)*v14;
            v97 = 1;
            v98 = (int *)v14;
            v15 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD);
            if ( v15 )
            {
              m_MaxNum = (UICursor *)(99 - v15[1]);
              this->m_MaxNum[v12] = (int)m_MaxNum;
            }
            else
            {
              this->m_MaxNum[v12] = 99;
            }
            if ( this->mb_OK.m_caption[73] )
            {
              m_MaxNum = (UICursor *)this->m_MaxNum;
              m_MaxNum->m_dwID[v12] = *(_DWORD *)&this->mb_OK.m_caption[76];
            }
            ++v12;
            ++p_m_nTodo_4008;
          }
          while ( v12 < this->m_nTodo_36A4 );
        }
        BYTE1(this->ml_ListProp.m_column[7].items.m_pData) = 1;
        LOBYTE(this->ml_ListProp.m_column[7].items.m_pData) = 1;
        (((UICursor *)m_MaxNum))->UICursor::_todo_541CC0();
        return 1;
      }
      else
      {
        if ( m_ListSelNum )
        {
          operator delete(this->m_ListSelNum);
          this->m_ListSelNum = ((int *)0);
        }
        return 1;
      }
    case 1001:
      switch ( nVal )
      {
        case 514:
          (((UISceneMap *)this))->UISceneMap::RenderWithUpdate() /* [ROWTABLE] */;
          v90 = (const void *)off_5B7650;
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v90, 1);
          return 1;
        case 518:
          if ( (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetItemData() <= 0 )
            goto LABEL_32;
          m_nTodo_36A4 = this->m_nTodo_36A4;
          this->mb_OK.m_caption[72] = 0;
          this->i = 0;
          if ( m_nTodo_36A4 > 0 )
          {
            v19 = (int *)this->m_ListSelNum;
            do
            {
              i = this->i;
              if ( v19[i] > 0 )
                this->mb_OK.m_caption[72] = 1;
              v21 = i + 1;
              this->i = v21;
            }
            while ( v21 < m_nTodo_36A4 );
          }
          if ( this->mb_OK.m_caption[72] )
          {
            this->PropUI::DisplayItemInfo();
          }
          else if ( !*(_DWORD *)&this->mb_OK.m_caption[84] )
          {
            SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
            (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(
              &this->m_3DObj.m_obj[4].m_pos,
              1);
            (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
            LOBYTE(this->m_PropRemark.m_pfather) = 0;
            (((CCBRoleState *)this))->CCBRoleState::NotifyStateChange(1u);
          }
          goto LABEL_42;
        case 519:
          if ( (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetItemData() <= 0 )
          {
LABEL_32:
            this->m_SelNum = -1;
            ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
              &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
              0);
            (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
            (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
            ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->mb_OK.m_texarray.m_ptex[1]))(
              &this->mb_OK.m_texarray.m_ptex[1],
              0);
            return 1;
          }
          else
          {
            for ( j = 0; j < this->m_nTodo_36A4; *(_DWORD *)(v24 + 68) = this->m_ListGrid[12].m_childs.m_pData )
            {
              this->m_ListSelNum[j] = 0;
              sprintf(this->buf, (const char *)&dir[20], this->m_ListSelNum[j]);
              (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetMouseMoveSel(2, j, this->buf, 0);
              if ( j < 0 || j >= (int)this->m_ScrollHB.m_ppic )
                v24 = 0;
              else
                v24 = *(&this->m_ScrollHB.m_pbkInfo->filepos + j);
              ++j;
            }
            (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetItem();
            (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetItem();
            *(_DWORD *)&this->mb_OK.m_caption[64] = 0;
            this->m_Sum = 0;
            LOBYTE(this->m_PropRemark.m_pfather) = 0;
            sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
            SetEnable((UICaption *)&this->m_btnGroup.m_btnDw.m_childs);
            SetEnable((UICaption *)&this->m_nCaptionOverlay);
            *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
            SetEnable((UICaption *)&this->m_btnGroup.m_btnUp.m_benable);
            (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(
              &this->m_3DObj.m_obj[4].m_pos,
              1);
            ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
              &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
              0);
            (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
            ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->mb_OK.m_texarray.m_ptex[1]))(
              &this->mb_OK.m_texarray.m_ptex[1],
              0);
            v25 = *(_DWORD *)&this->mb_OK.m_caption[84];
            if ( v25 )
            {
              if ( v25 == 1 )
              {
                SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
                (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(
                  &this->m_OutFrameL.m_rect.right,
                  0);
              }
            }
            else
            {
              (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(
                &this->m_3DObj.m_obj[4].m_pos,
                1);
              SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
              (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
            }
LABEL_42:
            v91 = (const void *)off_5B7650;
            v22 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v22))->CScreenMode::AudioSetPosition(v91, 1);
            return 1;
          }
        case 546:
          (((CCBRoleState *)this))->CCBRoleState::NotifyStateChange(0);
          m_SelNum = this->m_SelNum;
          if ( m_SelNum < 0 )
            return 1;
          ++this->m_ListSelNum[m_SelNum];
          v27 = this->m_SelNum;
          v28 = (int *)&this->m_ListSelNum[v27];
          v29 = (unsigned long)this->m_MaxNum[v27];
          if ( *v28 < v29 )
          {
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            v92 = (char *)off_5B7660;
          }
          else
          {
            *v28 = v29;
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            if ( !*(_DWORD *)&this->mb_OK.m_caption[84] )
            {
              sprintf(this->buf, "\\n      %s", (const char *)&dword_DCCC3C);
              SetEnable((UICaption *)&this->m_Role[4].m_bvisible);
              (((UIRoleSelect *)&this->m_Role[1].m_bvisible))->UIRoleSelect::SetByte(1);
            }
            v92 = off_5B765C[0];
          }
          v30 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v30))->CScreenMode::AudioSetPosition(v92, 1);
          sprintf(this->buf, (const char *)&dir[20], this->m_ListSelNum[this->m_SelNum]);
          (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetMouseMoveSel(2, this->m_SelNum, this->buf, 0);
          v31 = this->m_SelNum;
          if ( this->m_ListSelNum[v31] <= 0 )
          {
            if ( v31 < 0 || v31 >= (int)this->m_ScrollHB.m_ppic )
              v32 = 0;
            else
              v32 = *(&this->m_ScrollHB.m_pbkInfo->filepos + v31);
            *(_DWORD *)(v32 + 68)  = (unsigned long)(this->m_ListGrid[12].m_childs.m_pData);
          }
          else
          {
            UITabCtrl_SetItemParam(this->m_SelNum);
          }
          if ( !this->mb_OK.m_caption[73] )
          {
            v38 = (int *)this->m_ListSelNum;
            this->m_Sum = *v38 * *(_DWORD *)(this->m_nTodo_4008 + 608);
            *(_DWORD *)&this->mb_OK.m_caption[64] = (unsigned long)*v38;
            v39 = this->m_nTodo_36A4;
            this->i = 1;
            if ( v39 > 1 )
            {
              do
              {
                v40 = this->i;
                v41 = *(_DWORD *)&this->mb_OK.m_caption[64];
                this->m_Sum += v38[v40] * *(_DWORD *)(*(&this->m_nTodo_4008 + v40) + 608);
                v42 = (unsigned long)(v38[v40++] + v41);
                *(_DWORD *)&this->mb_OK.m_caption[64] = v42;
                this->i = v40;
              }
              while ( v40 < v39 );
            }
            goto LABEL_74;
          }
          v33 = (int *)this->m_ListSelNum;
          v34 = this->m_nTodo_36A4;
          this->m_Sum = (__int64)((double)*(int *)(this->m_nTodo_4008 + 608)
                                * *(float *)&this->mb_OK.m_caption[80]
                                * (double)*v33);
          *(_DWORD *)&this->mb_OK.m_caption[64] = (unsigned long)*v33;
          this->i = 1;
          if ( v34 <= 1 )
          {
LABEL_74:
            m_Sum = this->m_Sum;
            goto LABEL_92;
          }
          do
          {
            v35 = this->i;
            v36 = (__int64)((double)*(int *)(*(&this->m_nTodo_4008 + v35) + 608)
                          * *(float *)&this->mb_OK.m_caption[80]
                          * (double)v33[v35]);
            HIDWORD(v36) = *(_DWORD *)&this->mb_OK.m_caption[64];
            v37 = v36 + this->m_Sum;
            this->m_Sum = v37;
            *(_DWORD *)&this->mb_OK.m_caption[64] = (unsigned long)(v33[v35] + HIDWORD(v36));
            this->i = v35 + 1;
          }
          while ( v35 + 1 < v34 );
          m_Sum = v37;
LABEL_92:
          sprintf(this->buf, "%s %d", g_szCombatFieldName, m_Sum);
          SetEnable((UICaption *)&this->m_btnGroup.m_btnDw.m_childs);
          return 1;
        case 547:
          (((CCBRoleState *)this))->CCBRoleState::NotifyStateChange(0);
          v43 = (int *)&this->m_ListSelNum[this->m_SelNum];
          --*v43;
          v44 = (int *)&this->m_ListSelNum[this->m_SelNum];
          if ( *v44 > 0 )
          {
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            v93 = (char *)off_5B7660;
          }
          else
          {
            *v44 = 0;
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            v93 = off_5B765C[0];
          }
          v45 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v45))->CScreenMode::AudioSetPosition(v93, 1);
          sprintf(this->buf, (const char *)&dir[20], this->m_ListSelNum[this->m_SelNum]);
          (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetMouseMoveSel(2, this->m_SelNum, this->buf, 0);
          v46 = this->m_SelNum;
          if ( this->m_ListSelNum[v46] <= 0 )
          {
            if ( v46 < 0 || v46 >= (int)this->m_ScrollHB.m_ppic )
              v47 = 0;
            else
              v47 = *(&this->m_ScrollHB.m_pbkInfo->filepos + v46);
            *(_DWORD *)(v47 + 68)  = (unsigned long)(this->m_ListGrid[12].m_childs.m_pData);
          }
          else
          {
            UITabCtrl_SetItemParam(this->m_SelNum);
          }
          if ( this->mb_OK.m_caption[73] )
          {
            v48 = (int *)this->m_ListSelNum;
            v49 = this->m_nTodo_36A4;
            this->m_Sum = (__int64)((double)*(int *)(this->m_nTodo_4008 + 608)
                                  * *(float *)&this->mb_OK.m_caption[80]
                                  * (double)*v48);
            *(_DWORD *)&this->mb_OK.m_caption[64] = (unsigned long)*v48;
            this->i = 1;
            if ( v49 > 1 )
            {
              do
              {
                v50 = this->i;
                v51 = *(_DWORD *)&this->mb_OK.m_caption[64];
                this->m_Sum += (__int64)((double)*(int *)(*(&this->m_nTodo_4008 + v50) + 608)
                                       * *(float *)&this->mb_OK.m_caption[80]
                                       * (double)v48[v50]);
                *(_DWORD *)&this->mb_OK.m_caption[64] = (unsigned long)(v48[v50] + v51);
                this->i = v50 + 1;
              }
              while ( v50 + 1 < v49 );
            }
          }
          else
          {
            v52 = (int *)this->m_ListSelNum;
            this->m_Sum = *v52 * *(_DWORD *)(this->m_nTodo_4008 + 608);
            v53 = this->m_nTodo_36A4;
            *(_DWORD *)&this->mb_OK.m_caption[64] = (unsigned long)*v52;
            this->i = 1;
            if ( v53 > 1 )
            {
              do
              {
                v54 = this->i;
                v55 = *(_DWORD *)&this->mb_OK.m_caption[64];
                this->m_Sum += v52[v54] * *(_DWORD *)(*(&this->m_nTodo_4008 + v54) + 608);
                v56 = (unsigned long)(v52[v54++] + v55);
                *(_DWORD *)&this->mb_OK.m_caption[64] = v56;
                this->i = v54;
              }
              while ( v54 < v53 );
            }
          }
          m_Sum = this->m_Sum;
          goto LABEL_92;
        default:
          return 1;
      }
    case 1005:
      ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
        &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
        0);
      (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
      ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->mb_OK.m_texarray.m_ptex[1]))(
        &this->mb_OK.m_texarray.m_ptex[1],
        0);
      return 1;
    case 1007:
      this->m_SelNum = dwVal;
      if ( (int)dwVal <= -1 )
      {
        SetEnable((UICaption *)&this->m_nCaptionOverlay);
        *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
        ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
          &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
          0);
        (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (_DWORD)(0));
        ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->mb_OK.m_texarray.m_ptex[1]))(
          &this->mb_OK.m_texarray.m_ptex[1],
          0);
        return this->UIWnd::OnMessage(arg0, nVal, dwVal);
      }
      else
      {
        SetEnable((UICaption *)&this->m_3DObj.m_obj[4].m_pos);
        (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
        this->PropUI::UpdateItemDetail(this->m_SelNum);
        v57 = this->m_SelNum;
        v58 = *(unsigned __int8 *)(*(&this->m_nTodo_4008 + v57) + 612);
        v59 = v58 - 1;
        switch ( *(_BYTE *)(*(&this->m_nTodo_4008 + v57) + 612) )
        {
          case 1:
            LOBYTE(v57) = this->mb_OK.m_caption[96];
            (((UIPushButton *)&this->m_ListGrid[10].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Resume_word.tga", v57);
            break;
          case 2:
            LOBYTE(v58) = this->mb_OK.m_caption[96];
            (((UIPushButton *)&this->m_ListGrid[10].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Attack_word.tga", v58);
            break;
          case 3:
            LOBYTE(v59) = this->mb_OK.m_caption[96];
            (((UIPushButton *)&this->m_ListGrid[10].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Treasure_word.tga", v59);
            break;
          case 4:
            LOBYTE(v57) = this->mb_OK.m_caption[96];
            (((UIPushButton *)&this->m_ListGrid[10].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Ancient_word.tga", v57);
            break;
          case 5:
            LOBYTE(v58) = this->mb_OK.m_caption[96];
            (((UIPushButton *)&this->m_ListGrid[10].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Smelt_word.tga", v58);
            break;
          case 6:
            LOBYTE(v59) = this->mb_OK.m_caption[96];
            (((UIPushButton *)&this->m_ListGrid[10].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Special_word.tga", v59);
            break;
          default:
            break;
        }
        v60 = (int *)*(&this->m_nTodo_4008 + this->m_SelNum);
        if ( *((_BYTE *)v60 + 613) == 5 )
        {
          (((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40)))->CCBFiveNimbusWindow::SetFloatParam(228.0);
          (((Camera *)((char *)&this->m_Msg.m_btRc + 40)))->Camera::UpdateCameraLookAt(330, 280, 600);
        }
        else if ( *((_BYTE *)v60 + 612) == 11 )
        {
          (((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40)))->CCBFiveNimbusWindow::SetFloatParam(228.0);
          (((Camera *)((char *)&this->m_Msg.m_btRc + 40)))->Camera::UpdateCameraLookAt(330, 272, 600);
        }
        else
        {
          v61 = (unsigned long)*v60;
          if ( v61 == 8114 || v61 == 8132 )
          {
            (((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40)))->CCBFiveNimbusWindow::SetFloatParam(180.0);
            (((Camera *)((char *)&this->m_Msg.m_btRc + 40)))->Camera::UpdateCameraLookAt(330, 252, 600);
          }
          else
          {
            (((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40)))->CCBFiveNimbusWindow::SetFloatParam(180.0);
            (((Camera *)((char *)&this->m_Msg.m_btRc + 40)))->Camera::UpdateCameraLookAt(330, 268, 600);
          }
        }
        if ( !strcmp((const char *)(*(&this->m_nTodo_4008 + this->m_SelNum) + 36), unk_C10D38) )
        {
          sprintf(this->buf, "%s", "NONE");
        }
        else
        {
          v62 = (const char *)(*(&this->m_nTodo_4008 + this->m_SelNum) + 36);
          sprintf(this->buf, "Item\\%s\\%s.pol", v62, v62);
        }
        (((PalScript *)(&this->m_Msg.m_btRc + 7)))->PalScript::LoadModel(this->buf, 0);
        v63 = *(&this->m_nTodo_4008 + this->m_SelNum);
        v64 = (const char *)(v63 + 36);
        v65 = (const char *)(v63 + 66);
        if ( !strcmp((const char *)(v63 + 36), unk_C10D38) )
        {
          sprintf(this->buf, "%s", "NONE");
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v103 = 0;
          v104 = 0;
          sprintf(Buffer, "%s%s", v64, v65);
          sprintf(this->buf, "Item\\%s\\%s.tga", v64, Buffer);
        }
        (((gbGeomNode *)*((gbGeomNode **)&this->m_Msg.m_btRc + 32)))->gbGeomNode::ReplaceTexture(this->buf);
        v95 = this->m_SelNum;
        *((_DWORD *)&this->m_Msg.m_btRc + 29) = 1;
        (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::GetGridOffset(&pOut, v95);
        v67 = *v66;
        v68 = (gbTexture **)&this->mb_OK.m_texarray.m_ptex[1];
        v69 = v66[1];
        this->mb_OK.m_offsetx = *(_DWORD *)v66 + 90;
        this->mb_OK.m_offsety = v69;
        *(_DWORD *)&this->mb_OK.m_bBigFont = LODWORD(v67) + 180;
        this->mb_OK.m_texarray.m_ptex[0] = (gbTexture *)(LODWORD(v69) + 32);
        (((UIWnd *)&this->mb_OK.m_texarray.m_ptex[1]))->UIWnd::sub_445FA0(&this->mb_OK.m_offsetx);
        sprintf(this->buf, "%s:%d", (const char *)&g_bSaveFlag, 99 - this->m_MaxNum[this->m_SelNum]);
        SetEnable((UICaption *)&this->mb_OK.m_texarray.m_ptex[1]);
        if ( *(_DWORD *)&this->mb_OK.m_caption[84] )
          ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)(*v68)))(&this->mb_OK.m_texarray.m_ptex[1], 0);
        else
          ((void ( *)(gbTexture **, int))((gbRefObject *)(*v68)))(&this->mb_OK.m_texarray.m_ptex[1], 1);
        v70 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[48];
        v71 = (_PlugInfo **)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[1];
        v72 = (_PlugInfo *)(LODWORD(v69) - 4);
        v73 = (_PlugInfo *)(LODWORD(v67) + 200);
        if ( v70 )
        {
          if ( v70 == 1 )
          {
            v74 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[40];
            this->ml_ListProp.m_scrollbar.m_texarrayInfo[6] = v72;
            this->ml_ListProp.m_scrollbar.m_texarrayInfo[5] = v73;
            this->ml_ListProp.m_scrollbar.m_texarrayInfo[7] = (_PlugInfo *)((char *)v73 + v74);
            this->ml_ListProp.m_scrollbar.m_texarrayInfo[8] = (_PlugInfo *)((char *)v72
                                                                          + *(_DWORD *)&this->ml_ListProp.m_column[7].head[44]);
            (((UIWnd *)&this->ml_ListProp.m_column[3].head[32]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_scrollbar.m_texarrayInfo[5]);
            v75 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[52];
            v76 = (_PlugInfo *)this->ml_ListProp.m_scrollbar.m_texarrayInfo[7];
            this->ml_ListProp.m_scrollbar.m_texarrayInfo[2] = this->ml_ListProp.m_scrollbar.m_texarrayInfo[6];
            v77 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[40];
            v78 = (_PlugInfo *)((char *)v76 + v75);
            *v71 = v78;
            v79 = (_PlugInfo *)((char *)v78 + v77);
            v80 = (_PlugInfo *)this->ml_ListProp.m_scrollbar.m_texarrayInfo[8];
            this->ml_ListProp.m_scrollbar.m_texarrayInfo[3] = v79;
            this->ml_ListProp.m_scrollbar.m_texarrayInfo[4] = v80;
            (((UIWnd *)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_scrollbar.m_texarrayInfo[1]);
          }
        }
        else
        {
          v81 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[40];
          *v71 = v73;
          v82 = (_PlugInfo *)((char *)v73 + v81);
          v83 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[44];
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[2] = v72;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[3] = v82;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[4] = (_PlugInfo *)((char *)v72 + v83);
          (((UIWnd *)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_scrollbar.m_texarrayInfo[1]);
          v84 = (_PlugInfo *)((char *)this->ml_ListProp.m_scrollbar.m_texarrayInfo[4]
                            + *(_DWORD *)&this->ml_ListProp.m_column[7].head[52]);
          v85 = (_PlugInfo *)*v71;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[6] = v84;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[5] = v85;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[7] = this->ml_ListProp.m_scrollbar.m_texarrayInfo[3];
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[8] = (_PlugInfo *)((char *)v84
                                                                        + *(_DWORD *)&this->ml_ListProp.m_column[7].head[44]);
          (((UIWnd *)&this->ml_ListProp.m_column[3].head[32]))->UIWnd::sub_445FA0(&this->ml_ListProp.m_scrollbar.m_texarrayInfo[5]);
        }
        ((void ( *)(_PlugInfo **, int))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
          &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
          1);
        (**(void ( ***)(char *, int))&this->ml_ListProp.m_column[3].head[32])((char *)(&this->ml_ListProp.m_column[3].head[32]), (int)(1));
        sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
        sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
        return 1;
      }
    case 1009:
      if ( nVal != 521 )
        return 1;
      m_bfocus = this->m_Dlg.m_bfocus;
      v87 = HIWORD(dwVal);
      this->m_x = (unsigned __int16)dwVal;
      this->m_y = HIWORD(dwVal);
      if ( (unsigned __int16)dwVal <= m_bfocus
        || (unsigned __int16)dwVal >= this->m_Dlg.m_align
        || v87 <= (int)this->m_Dlg.pDebugTex
        || v87 >= SLODWORD(this->m_Dlg.m_ratiow) )
      {
        return 1;
      }
      v88 = *(_DWORD *)&this->mb_OK.m_caption[84];
      if ( v88 )
      {
        if ( v88 == 1 )
        {
          this->PropUI::UpdateCaptions();
          v89 = 0;
          if ( this->m_nTodo_36A4 > 0 )
          {
            do
            {
              this->m_ListSelNum[v89] = 0;
              sprintf(this->buf, (const char *)&dir[20], this->m_ListSelNum[v89]);
              (((UIListBox *)&this->m_ListGrid[12].m_pfather))->UIListBox::SetMouseMoveSel(2, v89++, this->buf, 0);
            }
            while ( v89 < this->m_nTodo_36A4 );
            return 1;
          }
        }
      }
      else
      {
        if ( g_bListNeedsRefresh )
        {
          this->PropUI::UpdateCaptions();
          UIFrameWnd_OnPaintUpdate(4);
          return 1;
        }
        if ( LOBYTE(this->m_PropRemark.m_pfather) )
        {
          this->PropUI::UpdateCaptions();
          return 1;
        }
        (((CCBRoleState *)this))->CCBRoleState::NotifyStateChange(0);
      }
      return 1;
    case 1010:
      return 1;
    default:
      return this->UIWnd::OnMessage(arg0, nVal, dwVal);
  }
}

// 0x00521A50
int PropUI::SetPendingMessage(char msg, int wparam, int lparam)
{
  int result; // eax

  this->mb_OK.m_caption[73] = msg;
  result = lparam;
  *(_DWORD *)&this->mb_OK.m_caption[76] = wparam;
  *(_DWORD *)&this->mb_OK.m_caption[80] = lparam;
  return result;
}
