#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/PropUI.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
CHAR * sub_458F70(LPCSTR lpString, int a2, LPSTR lpString1); // from annotations
char sub_46F3D0(_BYTE *_this); // from annotations

void GetGridOffset(void *_this, int *pOut, int index); // from annotations

// Unnamed globals (extern)
extern char asc_5B74B8[];
extern char byte_5967B0[3];
extern int dword_56B608[];
extern int dword_DC353C;
extern int dword_DC363C;
extern int dword_DC373C;
extern int dword_DC383C;
extern int dword_DC3A3C;
extern int dword_DCCC3C;
extern void * off_5B7650;
extern _SPropValue * off_5B765C;
extern void * off_5B7660;
extern RoleSystem stru_C059A0;

// 0x00452580
int PropUI::GetFaceNum()
{
  UIListBox *v0; // ecx
  int v1; // esi

  v1 = (int)v0;
  ((UITitle_BBTY *)(v1 + 1084))->ctor_1CC0();
  return v1;
}

// 0x00452670
void PropUI::Init()
{
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, 800, 600, 0);
  ((UIBigMap *)&this->bkWndX)->InitUI(100, (int)this);
  ((UITitle_BBTY *)((char *)&this->m_PropData + 996))->CreateFromScript();
}

// 0x0045B200
int PropUI::ShowCategory0(unsigned __int8 pData)
{
  gbTexture *m_pbk; // edx
  int v4; // edi
  int result; // eax

  m_pbk = this->m_EquipFlag.m_pbk;
  this->ml_ListProp.m_column[2].head[28] = pData;
  ((void ( *)(gbTexture **, _DWORD))*((_DWORD *)m_pbk))(&this->m_EquipFlag.m_pbk, pData);
  *((_DWORD *)&this->m_PropData + 68) = 0;
  *((_DWORD *)&this->m_PropData + 67) = 0;
  do
  {
    v4 = *((_DWORD *)&this->m_PropData + 67);
    if ( this->ml_ListProp.m_column[2].head[v4 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * v4 + 20] = *((_DWORD *)&this->m_PropData + 68)
                                                                   * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                   + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                    - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                   / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24] + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 20];
      sub_445FA0(&this->m_EquipFlag.m_text[152 * *((_DWORD *)&this->m_PropData + 67) + 16]);
      ++*((_DWORD *)&this->m_PropData + 68);
    }
    result = *((_DWORD *)&this->m_PropData + 67) + 1;
    *((_DWORD *)&this->m_PropData + 67) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0045B320
int PropUI::ShowCategory1(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  int v4; // edi
  int result; // eax

  v3 = *(void ( ***)(char *, _DWORD))&this->m_ListPropTitle.m_text[8];
  this->ml_ListProp.m_column[2].head[29] = pData;
  (*v3)(&this->m_ListPropTitle.m_text[8], pData);
  *((_DWORD *)&this->m_PropData + 68) = 0;
  *((_DWORD *)&this->m_PropData + 67) = 0;
  do
  {
    v4 = *((_DWORD *)&this->m_PropData + 67);
    if ( this->ml_ListProp.m_column[2].head[v4 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * v4 + 20] = *((_DWORD *)&this->m_PropData + 68)
                                                                   * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                   + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                    - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                   / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24] + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 20];
      sub_445FA0(&this->m_EquipFlag.m_text[152 * *((_DWORD *)&this->m_PropData + 67) + 16]);
      ++*((_DWORD *)&this->m_PropData + 68);
    }
    result = *((_DWORD *)&this->m_PropData + 67) + 1;
    *((_DWORD *)&this->m_PropData + 67) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0045B440
int PropUI::ShowCategory2(unsigned __int8 pData)
{
  void *vftable; // edx
  int v4; // edi
  int result; // eax

// [VFTABLE] vftable = this->ml_ListProp.m_scrollbar.__vftable;
  this->ml_ListProp.m_column[2].head[30] = pData;
  ((void ( *)(UIScrollBar *, _DWORD))vftable->ShowWindow)(&this->ml_ListProp.m_scrollbar, pData);
  *((_DWORD *)&this->m_PropData + 68) = 0;
  *((_DWORD *)&this->m_PropData + 67) = 0;
  do
  {
    v4 = *((_DWORD *)&this->m_PropData + 67);
    if ( this->ml_ListProp.m_column[2].head[v4 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * v4 + 20] = *((_DWORD *)&this->m_PropData + 68)
                                                                   * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                   + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                    - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                   / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24] + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 20];
      sub_445FA0(&this->m_EquipFlag.m_text[152 * *((_DWORD *)&this->m_PropData + 67) + 16]);
      ++*((_DWORD *)&this->m_PropData + 68);
    }
    result = *((_DWORD *)&this->m_PropData + 67) + 1;
    *((_DWORD *)&this->m_PropData + 67) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0045B560
int PropUI::ShowCategory3(unsigned __int8 pData)
{
  void ( **m_style)(int *, _DWORD); // edx
  int v4; // edi
  int result; // eax

  m_style = (void ( **)(int *, _DWORD))this->ml_ListProp.m_scrollbar.m_bk.m_style;
  this->ml_ListProp.m_column[2].head[31] = pData;
  (*m_style)(&this->ml_ListProp.m_scrollbar.m_bk.m_style, pData);
  *((_DWORD *)&this->m_PropData + 68) = 0;
  *((_DWORD *)&this->m_PropData + 67) = 0;
  do
  {
    v4 = *((_DWORD *)&this->m_PropData + 67);
    if ( this->ml_ListProp.m_column[2].head[v4 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * v4 + 20] = *((_DWORD *)&this->m_PropData + 68)
                                                                   * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                   + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                    - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                   / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24] + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 20];
      sub_445FA0(&this->m_EquipFlag.m_text[152 * *((_DWORD *)&this->m_PropData + 67) + 16]);
      ++*((_DWORD *)&this->m_PropData + 68);
    }
    result = *((_DWORD *)&this->m_PropData + 67) + 1;
    *((_DWORD *)&this->m_PropData + 67) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0045B680
int PropUI::ShowCategory4(unsigned __int8 pData)
{
  void ( **left)(tagRECT *, _DWORD); // edx
  int v4; // edi
  int result; // eax

  left = (void ( **)(tagRECT *, _DWORD))this->ml_ListProp.m_scrollbar.m_btnrect[0].left;
  this->ml_ListProp.m_column[2].head[32] = pData;
  (*left)(this->ml_ListProp.m_scrollbar.m_btnrect, pData);
  *((_DWORD *)&this->m_PropData + 68) = 0;
  *((_DWORD *)&this->m_PropData + 67) = 0;
  do
  {
    v4 = *((_DWORD *)&this->m_PropData + 67);
    if ( this->ml_ListProp.m_column[2].head[v4 + 28] )
    {
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * v4 + 20] = *((_DWORD *)&this->m_PropData + 68)
                                                                   * *(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                   + (*(_DWORD *)&this->ml_ListProp.m_column[2].head[16]
                                                                    - *(_DWORD *)&this->ml_ListProp.m_column[2].head[24])
                                                                   / 2;
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[12];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 24] = *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 16] + *(_DWORD *)&this->ml_ListProp.m_column[2].head[20];
      *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 28] = *(_DWORD *)&this->ml_ListProp.m_column[2].head[24] + *(_DWORD *)&this->ml_ListProp.m_column[1].head[16 * *((_DWORD *)&this->m_PropData + 67) + 20];
      sub_445FA0(&this->m_EquipFlag.m_text[152 * *((_DWORD *)&this->m_PropData + 67) + 16]);
      ++*((_DWORD *)&this->m_PropData + 68);
    }
    result = *((_DWORD *)&this->m_PropData + 67) + 1;
    *((_DWORD *)&this->m_PropData + 67) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046D140
int PropUI::InitUI()
{
  int bkWndY; // eax

  this->bkWndX = 800;
  this->bkWndY = 600;
  this->m_ListWidth = 300;
  this->m_ListHeight = 400;
  *(_WORD *)(&this->m_PropData.m_Dicker + 1) = 0;
  *((_DWORD *)&this->m_PropData + 3474) = 0;
  *((_DWORD *)&this->m_PropData + 3475) = 0;
  memset((char *)&this->m_PropData + 13904, 0, 0x640u);
  memset((char *)&this->m_PropData + 17104, 0, 0x190u);
  memset((char *)&this->m_PropData + 15504, 0, 0x640u);
  *(_DWORD *)&this->m_PropData.m_Type = 0;
  this->p_DealData = 0;
  this->m_ListSelNum = 0;
  this->m_MaxNum = 0;
  this->m_Sum = 0;
  this->i = 0;
  this->j = 0;
  this->_isCreatable = 0;
  sub_4422E0(&this->m_Frame);
  ((UI3DCtrl *)(&this->m_Frame + 1))->ctor_D830();
  sub_4422E0(&this->m_FrameBar.m_tex);
  UIScene::GetSys();
  ((ARC_PlayerAtt *)&this->m_Role[1].m_bvisible)->Refresh();
  ((UIProgressBar *)((char *)&this->m_Msg.m_btRc + 40))->ctor();
  sub_4422E0((char *)&this->m_Msg.m_btRc + 348);
  sub_4422E0((char *)&this->m_Msg.m_btRc + 516);
  sub_4422E0((char *)&this->m_Msg + 1300);
  sub_4422E0(&this->m_3DObj.m_numobj);
  sub_4422E0(&this->m_3DObj.m_obj[4].m_pos);
  sub_4422E0(&this->m_Dlg.m_ratioh);
  sub_4422E0(&this->m_ListGrid[10].m_rect);
  sub_4422E0(&this->m_ListGrid[11].m_rect);
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->UpdateKeyCtrl();
  UIScene::GetSys();
  UIScene::GetSys();
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[40] = 32;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[44] = 16;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[48] = 0;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[52] = 0;
  sub_4422E0(&this->ml_ListProp.m_column[7].items.capacity);
  sub_4422E0((char *)&this->ml_ListProp + 1244);
  sub_4422E0(&this->m_btnGroup.m_btnUp.m_benable);
  sub_4422E0(&this->m_btnGroup.m_btnUp.m_caption[20]);
  sub_4422E0(&this->m_btnGroup.m_btnDw.m_childs);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0(&this->mb_OK.m_texarray.m_ptex[1]);
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
void PropUI::ctor()
{
  int *m_ListSelNum; // eax
  UIListBox *v3; // [esp+0x0] [ebp-0x20]
  int v4; // [esp+0x4] [ebp-0x1C]

  m_ListSelNum = this->m_ListSelNum;
  if ( m_ListSelNum )
  {
    operator delete(m_ListSelNum);
    this->m_ListSelNum = 0;
  }
  if ( this->m_MaxNum )
  {
    operator delete(this->m_MaxNum);
    this->m_MaxNum = 0;
  }
  this->_isCreatable = 0;
  *(_DWORD *)&this->mb_OK.m_caption[84] = 0;
  ((CCBRoleState *)this)->Destroy(v3, v4);
  ((UIFrameWnd *)&this->mb_OK.m_texarray.m_ptex[1])->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_MoneyRemark.m_ratiow)->Destroy2();
  ((UICaption *)&this->m_PropRemark.m_childs)->Destroy2();
  ((UICaption *)&this->m_btnGroup.m_btnDw.m_caption[12])->Destroy2();
  ((UIFrameWnd *)&this->m_btnGroup.m_btnDw.m_childs)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnGroup.m_btnUp.m_caption[20])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnGroup.m_btnUp.m_benable)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->ml_ListProp + 1244))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->ml_ListProp.m_column[7].items.capacity)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->ml_ListProp.m_column[3].head[32])->Destroy2();
  ((UICaption *)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9])->Destroy2();
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->DeleteRow();
  ((UIFrameWnd *)&this->m_ListGrid[11].m_rect)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_ListGrid[10].m_rect)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Dlg.m_ratioh)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_3DObj.m_obj[4].m_pos)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_3DObj.m_numobj)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_Msg + 1300))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_Msg.m_btRc + 516))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_Msg.m_btRc + 348))->UIFrameWnd::_UIFrameWnd();
  ((PalScript *)((char *)&this->m_Msg.m_btRc + 40))->PalScript_Init();
  ((UIRoleDialog *)&this->m_Role[1].m_bvisible)->_UIRoleDialog();
  ((PalScript *)&this->m_OutFrameL.m_rect.right)->ctor();
  ((UICaption *)&this->m_OutFrameT)->Destroy2();
  ((UIFrameWnd *)&this->m_FrameBar.m_tex)->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)(&this->m_Frame + 1))->ctor();
  ((UIFrameWnd *)&this->m_Frame)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0046DD10
int PropUI::UpdateItemList(const void *arg0)
{
  st_Manager *p_m_PropData; // ebx
  int *v4; // edi
  unsigned int v5; // edx
  int v6; // eax
  int **v7; // edi
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

  p_m_PropData = &this->m_PropData;
  memset(&this->m_PropData, 0, 0x4460u);
  p_m_pfather = (UIListBox *)&this->m_ListGrid[12].m_pfather;
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->ClearAll();
  qmemcpy(p_m_PropData, arg0, 0x4460u);
  if ( this->m_MaxNum )
  {
    operator delete(this->m_MaxNum);
    this->m_MaxNum = 0;
  }
  v4 = (int *)operator new(4 * *((_DWORD *)&this->m_PropData + 3475));
  v5 = 4 * *((_DWORD *)&this->m_PropData + 3475);
  this->m_MaxNum = v4;
  memset(v4, 0, v5);
  v15 = 0;
  v6 = *((_DWORD *)&this->m_PropData + 3475);
  p_DWORD = 0xFFFF;
  v17 = 0;
  v18 = 0;
  if ( v6 > 0 )
  {
    v7 = (int **)((char *)&this->m_PropData + 16304);
    arg0a = (const void *)(-16392 - (_DWORD)this);
    do
    {
      v8 = *v7;
      v9 = **v7;
      v17 = 1;
      p_DWORD = v9;
      v18 = v8;
      v10 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD);
      sprintf(this->buf, byte_5967B0, *v7 + 1);
      nVal = ((UIListBox *)p_m_pfather)->SetItemOffset(this->buf, 0);
      sprintf(this->buf, &dir[20], 0);
      ((UIListBox *)p_m_pfather)->SetMouseMoveSel(2, nVal, this->buf, 0);
      if ( v10 )
        *(int *)((char *)this->m_MaxNum + (unsigned int)v7 + (_DWORD)arg0a) = 99 - v10[1];
      else
        *(int *)((char *)this->m_MaxNum + (unsigned int)arg0a + (_DWORD)v7) = 99;
      if ( this->mb_OK.m_caption[73] )
      {
        *(int *)((char *)this->m_MaxNum + (unsigned int)v7 + (_DWORD)arg0a) = *(_DWORD *)&this->mb_OK.m_caption[76];
        sprintf(this->buf, &dir[20], (unsigned int)(__int64)((double)(*v7)[152] * *(float *)&this->mb_OK.m_caption[80]));
      }
      else
      {
        sprintf(this->buf, &dir[20], (*v7)[152]);
      }
      ((UIListBox *)p_m_pfather)->SetMouseMoveSel(1, nVal, this->buf, 0);
      v11 = *((_DWORD *)&this->m_PropData + 3475);
      ++v7;
      ++v15;
    }
    while ( v15 < v11 );
  }
  return ((UIListBox *)p_m_pfather)->GetItem();
}

// 0x0046DF40
int PropUI::InitPlayerList(int nVal)
{
  int bkWndX; // ecx
  gbTexture *m_tex; // edx
  int v5; // eax
  void *vftable; // eax
  float m_ratioh; // edx
  LONG left; // eax
  int m_num; // eax
  int v10; // ecx
  float v11; // edx
  UIWnd *m_pfather; // eax
  char *v13; // eax
  int i; // ecx
  int v15; // ebp
  _PlugInfo *v16; // edx
  _PlugInfo *v17; // ecx
  _PlugInfo *v18; // eax
  char *v19; // ebp
  int capacity; // eax
  int v21; // edx
  int m_benable; // edx
  LONG v23; // edx
  int v24; // edx
  char *m_pData; // eax
  int v26; // eax
  int v27; // edx
  int m_numobj; // edx
  float x; // edx
  int v30; // eax
  LONG right; // edx
  int v32; // ecx
  int v33; // edx
  LONG top; // edx
  gbTexture *v35; // eax
  char *v36; // edx
  int m_align; // ecx
  char *v38; // eax
  int v39; // ecx
  int v40; // eax
  int result; // eax
  int v42; // [esp+FCh] [ebp-0x10C]
  int v43; // [esp+FCh] [ebp-0x10C]
  float v44; // [esp+0x100] [ebp-0x108]
  int v45; // [esp+0x110] [ebp-F8h] BYREF
  int v46; // [esp+0x114] [ebp-F4h]
  int v47; // [esp+0x118] [ebp-F0h]
  int v48; // [esp+0x11C] [ebp-ECh]
  _DWORD v49[2]; // [esp+0x120] [ebp-E8h] BYREF
  int v50; // [esp+0x128] [ebp-E0h]
  int v51; // [esp+0x12C] [ebp-DCh]
  int v52; // [esp+0x130] [ebp-D8h]
  char *v53; // [esp+0x134] [ebp-D4h]
  gbTexture *v54; // [esp+0x138] [ebp-D0h] BYREF
  char *v55; // [esp+0x13C] [ebp-CCh]
  char *v56; // [esp+0x140] [ebp-C8h]
  char *v57; // [esp+0x144] [ebp-C4h]
  _DWORD v58[4]; // [esp+0x148] [ebp-C0h] BYREF
  gbVec3D pPos; // [esp+0x158] [ebp-B0h] BYREF
  int v60; // [esp+0x164] [ebp-A4h]
  _DWORD v61[4]; // [esp+0x168] [ebp-A0h] BYREF
  _DWORD v62[4]; // [esp+0x178] [ebp-0x90] BYREF
  _DWORD v63[4]; // [esp+0x188] [ebp-0x80] BYREF
  _DWORD v64[4]; // [esp+0x198] [ebp-0x70] BYREF
  gbVec3D pDir; // [esp+0x1A8] [ebp-0x60] BYREF
  int v66; // [esp+0x1B4] [ebp-0x54]
  _DWORD v67[4]; // [esp+0x1B8] [ebp-0x50] BYREF
  _DWORD v68[4]; // [esp+0x1C8] [ebp-0x40] BYREF
  int v69[4]; // [esp+0x1D8] [ebp-0x30] BYREF
  _DWORD v70[6]; // [esp+0x1E8] [ebp-0x20] BYREF
  int v71; // [esp+0x200] [ebp-0x8]
  int bkWndY; // [esp+0x204] [ebp-0x4]

  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, 800, 600, 0);
  bkWndX = this->bkWndX;
  m_tex = this->m_FrameBar.m_tex;
  bkWndY = this->bkWndY;
  v71 = bkWndX;
  v63[1] = 22;
  v63[0] = 266;
  v63[2] = 482;
  v63[3] = 150;
  (*((void ( **)(gbTexture **, int, _DWORD *, PropUI *))m_tex + 4))(
    &this->m_FrameBar.m_tex,
    513,
    v63,
    this);
  ((UIStatic *)&this->m_FrameBar.m_tex)->CreateFromTemplate();
  v5 = *((_DWORD *)&this->m_Frame + 38);
  v61[1] = 564;
  v61[0] = 0;
  v61[2] = 800;
  v61[3] = 599;
  (*(void ( **)(UIStatic *, int, _DWORD *, char *, _DWORD, PropUI *))(v5 + 28))(
    &this->m_Frame + 1,
    513,
    v61,
    "UI\\Flex\\framebar.tga",
    0,
    this);
  ((CScreenMode *)(&this->m_Frame + 1))->SetPosition(30,   35);
// [VFTABLE] vftable = this->m_Frame.__vftable;
  v70[1] = 0;
  v70[0] = 0;
  v70[2] = 206;
  v70[3] = 600;
  ((void ( *)(UIStatic *, int, _DWORD *, PropUI *))vftable->Create)(&this->m_Frame, 513, v70, this);
  ((UIStatic *)&this->m_Frame)->CreateFromTemplate();
  v58[1] = 32;
  v58[0] = 454;
  m_ratioh = this->m_Dlg.m_ratioh;
  v58[2] = 790;
  v58[3] = 425;
  (*(void ( **)(float *, int, _DWORD *, PropUI *))(LODWORD(m_ratioh) + 16))(
    &this->m_Dlg.m_ratioh,
    513,
    v58,
    this);
  ((UIStatic *)&this->m_Dlg.m_ratioh)->CreateFromTemplate();
  left = this->m_ListGrid[11].m_rect.left;
  v68[1] = 50;
  v68[0] = 476;
  v68[2] = 782;
  v68[3] = 82;
  (*(void ( **)(tagRECT *, int, _DWORD *, PropUI *))(left + 16))(&this->m_ListGrid[11].m_rect, 513, v68, this);
  ((UIScene *)&this->m_ListGrid[11].m_rect)->SetShow(0);
  sprintf(
    this->buf,
    "%s                %s   %s",
    (const char *)dword_DC353C,
    (const char *)dword_DC363C,
    (const char *)dword_DC373C);
  ((UICaption *)&this->m_ListGrid[11].m_rect)->SetEnable((int)this->buf, 0);
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15] = (gbTexture *)79;
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[14] = (gbTexture *)476;
  this->ml_ListProp.m_scrollbar.m_texarray.m_num = 769;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[0] = (_PlugInfo *)((char *)&this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15][3].InFmt.g_mask
                                                                + 2);
  m_num = this->ml_ListProp.m_scrollbar.m_texarray.m_num;
  // [VTBL_DISPATCH] LODWORD(pPos.y) = (char *)&this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15]->0 + 15;
  v60 = LODWORD(pPos.y) + 26;
  LODWORD(pDir.y) = LODWORD(pPos.y) + 253;
  v10 = LODWORD(pPos.y) + 279;
  v66 = LODWORD(pPos.y) + 279;
  LOBYTE(v10) = this->mb_OK.m_caption[96];
  LODWORD(pPos.x) = m_num - 31;
  LODWORD(v11) = m_num - 31 + 22;
  LODWORD(pDir.x) = m_num - 31;
  m_pfather = this->m_ListGrid[12].m_pfather;
  pPos.z = v11;
  pDir.z = v11;
  ((void ( *)(UIWnd **, int, gbTexture **, PropUI *, _DWORD, int, int))m_pfather->m_rect.bottom)(
    &this->m_ListGrid[12].m_pfather,
    259,
    &this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[14],
    this,
    0,
    1,
    v10);
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetLockSel();
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[2] = (gbTexture *)-4;
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[3] = (gbTexture *)-6;
  this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[4] = (gbTexture *)10;
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[14], 38, 27, 0);
  // [VTBL_DISPATCH] ((CCBUI *)&this->m_ListGrid[12].m_pbk)->ShowEffect((int)&this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15]->0 + 1, this->ml_ListProp.m_scrollbar.m_texarray.m_num - 38, this->ml_ListProp.m_scrollbar.m_texarray.m_num);
  ((CCBUI *)&this->m_ListGrid[12].m_pbk)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_ListGrid[12].m_pbk)->SetSelection(27);
  ((CCBUI *)&this->m_ListGrid[12].m_pbk)->SetCurPlayer(5);
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetFirstShow((int)"Name", 168);
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetFirstShow((int)"Price", 51);
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetFirstShow((int)"Num1", 38);
  ((CCBUI *)&this->m_ListGrid[12].m_pbk)->VirtualCall();
  // [VTBL_DISPATCH] v13 = (char *)&this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[15]->0 + 2;
  v54 = this->ml_ListProp.m_scrollbar.m_texarray.m_ptex[14];
  v55 = v13;
  v56 = (char *)(&v54[3] + 1);
  v57 = v13 + 23;
  this->i = 0;
  do
  {
    (*(void ( **)(int *, int, gbTexture **, PropUI *))(*(&this->m_TalkFrame.m_bvisible
                                                                            + 38 * this->i)
                                                                          + 16))(
      &this->m_TalkFrame.m_bvisible + 38 * this->i,
      513,
      &v54,
      this);
    ((UIStatic *)(UIStatic *)&this->m_TalkFrame.m_bvisible + this->i)->CreateFromTemplate();
    i = this->i;
    v55 = v57;
    v57 += 23;
    this->i = i + 1;
  }
  while ( i + 1 < 13 );
  this->mb_OK.m_offsety = 0.0;
  this->mb_OK.m_offsetx = 0;
  *(_DWORD *)&this->mb_OK.m_bBigFont = 90;
  this->mb_OK.m_texarray.m_ptex[0] = (gbTexture *)(LODWORD(this->mb_OK.m_offsety) + 32);
  // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, int, int *, PropUI *))&this->mb_OK.m_texarray.m_ptex[1]->0 + 4))(
    // [VTBL_DISPATCH]   &this->mb_OK.m_texarray.m_ptex[1],
    // [VTBL_DISPATCH]   513,
    // [VTBL_DISPATCH]   &this->mb_OK.m_offsetx,
    // [VTBL_DISPATCH]   this);
  ((UIScene *)&this->mb_OK.m_texarray.m_ptex[1])->SetShow(0);
  // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->mb_OK.m_texarray.m_ptex[1]->0)(&this->mb_OK.m_texarray.m_ptex[1], 0);
  LOBYTE(v52) = this->mb_OK.m_caption[96];
  v15 = v52;
  v42 = v52;
  v53 = "UI\\Assistant\\Communal\\Add";
  v16 = this->ml_ListProp.m_scrollbar.m_texarrayInfo[9];
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[40] = 24;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[44] = 40;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[2] = (_PlugInfo *)158;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[1] = (_PlugInfo *)476;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[3] = (_PlugInfo *)500;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[4] = (_PlugInfo *)198;
  (*(void ( **)(int, _PlugInfo **, PropUI *, char *, _DWORD, int))&v16->name[24])(
    546,
    &this->ml_ListProp.m_scrollbar.m_texarrayInfo[1],
    this,
    "UI\\Assistant\\Communal\\Sub",
    0,
    v42);
  v17 = this->ml_ListProp.m_scrollbar.m_texarrayInfo[1];
  v18 = this->ml_ListProp.m_scrollbar.m_texarrayInfo[4];
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[6] = v18;
  v43 = v15;
  v19 = v53;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[5] = v17;
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[7] = this->ml_ListProp.m_scrollbar.m_texarrayInfo[3];
  this->ml_ListProp.m_scrollbar.m_texarrayInfo[8] = (_PlugInfo *)((char *)v18
                                                                + *(_DWORD *)&this->ml_ListProp.m_column[7].head[44]);
  (*(void ( **)(int, _PlugInfo **, PropUI *, char *, _DWORD, int))(*(_DWORD *)&this->ml_ListProp.m_column[3].head[32]
                                                                          + 28))(
    547,
    &this->ml_ListProp.m_scrollbar.m_texarrayInfo[5],
    this,
    v19,
    0,
    v43);
  this->ml_ListProp.m_column[7].head[56] = v52;
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[48] = 1;
  ((PalScript *)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9])->OpenScript("UI\\Assistant\\Communal\\UnSub.tga", this->ml_ListProp.m_column[7].head[56]);
  ((PalScript *)&this->ml_ListProp.m_column[3].head[32])->OpenScript("UI\\Assistant\\Communal\\UnAdd.tga", this->ml_ListProp.m_column[7].head[56]);
  *(_DWORD *)&this->ml_ListProp.m_column[7].head[52] = 20;
  ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
    &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
    0);
  (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
    &this->ml_ListProp.m_column[3].head[32],
    0);
  capacity = this->ml_ListProp.m_column[7].items.capacity;
  v46 = 142;
  v45 = 218;
  v47 = 450;
  v48 = 556;
  (*(void ( **)(int *, int, int *, PropUI *))(capacity + 16))(
    &this->ml_ListProp.m_column[7].items.capacity,
    161,
    &v45,
    this);
  ((UIStatic *)&this->ml_ListProp.m_column[7].items.capacity)->CreateFromTemplate();
  v21 = *((_DWORD *)&this->ml_ListProp + 311);
  v46 = 388;
  v45 = 232;
  v47 = 444;
  v48 = 556;
  (*(void ( **)(char *, int, int *, PropUI *))(v21 + 16))((char *)&this->ml_ListProp + 1244, 161, &v45, this);
  ((UIScene *)((char *)&this->ml_ListProp + 1244))->SetShow(0);
  m_benable = this->m_btnGroup.m_btnUp.m_benable;
  v46 = 520;
  v45 = 232;
  v47 = 444;
  v48 = 552;
  (*(void ( **)(int *, int, int *, PropUI *))(m_benable + 16))(
    &this->m_btnGroup.m_btnUp.m_benable,
    161,
    &v45,
    this);
  ((UIScene *)&this->m_btnGroup.m_btnUp.m_benable)->SetShow(0);
  v23 = this->m_ListGrid[10].m_rect.left;
  v62[1] = 158;
  v62[0] = 404;
  v62[2] = 420;
  v62[3] = 190;
  (*(void ( **)(tagRECT *, int, _DWORD *, PropUI *))(v23 + 16))(&this->m_ListGrid[10].m_rect, 513, v62, this);
  ((UIStatic *)&this->m_ListGrid[10].m_rect)->CreateFromTemplate();
  this->m_btnGroup.m_btnDw.m_rect.right = 392;
  this->m_btnGroup.m_btnDw.m_rect.top = 478;
  this->m_btnGroup.m_btnDw.m_rect.bottom = 624;
  this->m_btnGroup.m_btnDw.m_pfather = (UIWnd *)(this->m_btnGroup.m_btnDw.m_rect.right + 32);
  (*(void ( **)(char *, int, LONG *, PropUI *))(*(_DWORD *)&this->m_btnGroup.m_btnUp.m_caption[20] + 16))(
    &this->m_btnGroup.m_btnUp.m_caption[20],
    272,
    &this->m_btnGroup.m_btnDw.m_rect.top,
    this);
  ((UIScene *)&this->m_btnGroup.m_btnUp.m_caption[20])->SetShow(0);
  sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)&this->m_btnGroup.m_btnUp.m_caption[20])->SetEnable((int)this->buf, 0);
  *(_DWORD *)this->m_btnGroup.m_btnDw.m_caption = 392;
  this->m_btnGroup.m_btnDw.m_alignmode = 638;
  *(_DWORD *)&this->m_btnGroup.m_btnDw.m_caption[4] = 764;
  *(_DWORD *)&this->m_btnGroup.m_btnDw.m_caption[8] = *(_DWORD *)this->m_btnGroup.m_btnDw.m_caption + 32;
  (*((void ( **)(PtrArray *, int, int *, PropUI *))this->m_btnGroup.m_btnDw.m_childs.m_pData + 4))(
    &this->m_btnGroup.m_btnDw.m_childs,
    261,
    &this->m_btnGroup.m_btnDw.m_alignmode,
    this);
  ((UIScene *)&this->m_btnGroup.m_btnDw.m_childs)->SetShow(0);
  sprintf(this->buf, "%s %d", g_szCombatFieldName, this->m_Sum);
  ((UICaption *)&this->m_btnGroup.m_btnDw.m_childs)->SetEnable((int)this->buf, 0);
  this->i = 0;
  do
  {
    v24 = this->m_Role[1].m_childs.capacity;
    m_pData = this->m_Role[1].m_childs.m_pData;
    v64[0] = this->m_Role[1].m_pfather;
    v64[1] = m_pData;
    v64[2] = v24 + v64[0];
    v64[3] = &m_pData[this->m_Role[1].m_childs.m_nSize];
    (*(void ( **)(LONG *, int, _DWORD *, PropUI *))(*(&this->m_OutFrameB.m_rect.bottom + 38 * this->i) + 16))(
      &this->m_OutFrameB.m_rect.bottom + 38 * this->i,
      dword_56B608[this->i],
      v64,
      this);
    ((UIStatic *)(UIStatic *)&this->m_OutFrameB.m_rect.bottom + this->i)->CreateFromTemplate();
    (**((void ( ***)(LONG *, _DWORD))&this->m_OutFrameB.m_rect.bottom + 38 * this->i))(
      &this->m_OutFrameB.m_rect.bottom + 38 * this->i,
      0);
    v26 = this->i + 1;
    this->i = v26;
  }
  while ( v26 < 5 );
  v27 = *((_DWORD *)&this->m_Msg.m_btRc + 129);
  v49[1] = 437;
  v49[0] = 456;
  v50 = 486;
  v51 = 556;
  (*(void ( **)(char *, int, _DWORD *, PropUI *))(v27 + 16))(
    (char *)&this->m_Msg.m_btRc + 516,
    513,
    v49,
    this);
  ((UIStatic *)((char *)&this->m_Msg.m_btRc + 516))->CreateFromTemplate();
  v49[0] = v50;
  v50 += 256;
  (*(void ( **)(char *, int, _DWORD *, PropUI *))(*((_DWORD *)&this->m_Msg + 325) + 16))(
    (char *)&this->m_Msg + 1300,
    513,
    v49,
    this);
  ((UIStatic *)((char *)&this->m_Msg + 1300))->CreateFromTemplate();
  m_numobj = this->m_3DObj.m_numobj;
  v49[0] = v50;
  v50 += 32;
  (*(void ( **)(int *, int, _DWORD *, PropUI *))(m_numobj + 16))(
    &this->m_3DObj.m_numobj,
    513,
    v49,
    this);
  ((UIStatic *)&this->m_3DObj.m_numobj)->CreateFromTemplate();
  x = this->m_3DObj.m_obj[4].m_pos.x;
  this->m_Dlg.pDebugTex = (gbTexture *)446;
  this->m_Dlg.m_bfocus = 489;
  this->m_Dlg.m_align = 745;
  LODWORD(this->m_Dlg.m_ratiow) = 546;
  (*(void ( **)(gbVec3D *, int, int *, PropUI *))(LODWORD(x) + 16))(
    &this->m_3DObj.m_obj[4].m_pos,
    521,
    &this->m_Dlg.m_bfocus,
    this);
  ((UIScene *)&this->m_3DObj.m_obj[4].m_pos)->SetShow(0);
  (*(void ( **)(gbVec3D *, _DWORD))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(&this->m_3DObj.m_obj[4].m_pos, 0);
  v30 = LODWORD(this->m_Dlg.m_ratiow) - 36;
  v67[0] = this->m_Dlg.m_align - 36;
  v67[1] = v30;
  v67[2] = v67[0] + 24;
  right = this->m_OutFrameL.m_rect.right;
  v67[3] = v30 + 32;
  (*(void ( **)(LONG *, int, _DWORD *, PropUI *))(right + 16))(&this->m_OutFrameL.m_rect.right, 2, v67, this);
  ((UIScene *)&this->m_OutFrameL.m_rect.right)->LoadResource("ui\\scene\\page");
  ((UIScene *)&this->m_OutFrameL.m_rect.right)->SetController(0x40000000);
  (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
  LOBYTE(v32) = this->mb_OK.m_caption[96];
  v33 = *(_DWORD *)&this->m_btnGroup.m_btnDw.m_caption[12];
  this->m_PropRemark.m_rect.top = 569;
  this->m_PropRemark.m_rect.left = 300;
  this->m_PropRemark.m_rect.right = 390;
  this->m_PropRemark.m_rect.bottom = 594;
  (*(void ( **)(char *, int, tagRECT *, PropUI *, char *, _DWORD, int))(v33 + 28))(
    &this->m_btnGroup.m_btnDw.m_caption[12],
    518,
    &this->m_PropRemark.m_rect,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v32);
  top = this->m_PropRemark.m_rect.top;
  this->m_MoneyRemark.m_align = this->m_PropRemark.m_rect.bottom;
  v35 = (gbTexture *)(this->m_PropRemark.m_rect.right + 66);
  this->m_MoneyRemark.m_bfocus = top;
  v36 = this->m_PropRemark.m_childs.m_pData;
  this->m_MoneyRemark.m_benable = (int)v35;
  v35 = (gbTexture *)((char *)v35 + 90);
  this->m_MoneyRemark.pDebugTex = v35;
  LOBYTE(v35) = this->mb_OK.m_caption[96];
  (*((void ( **)(PtrArray *, int, int *, PropUI *, char *, _DWORD, gbTexture *))v36 + 7))(
    &this->m_PropRemark.m_childs,
    520,
    &this->m_MoneyRemark.m_benable,
    this,
    "UI\\Assistant\\Communal\\bDicker",
    0,
    v35);
  sub_445E50((int)&this->m_PropRemark.m_childs);
  ((PalScript *)&this->m_PropRemark.m_childs)->OpenScript("UI\\Assistant\\Communal\\UnDicker.tga", this->mb_OK.m_caption[96]);
  m_align = this->m_MoneyRemark.m_align;
  LODWORD(this->mb_OK.m_ratiow) = this->m_MoneyRemark.m_bfocus;
  v38 = (char *)&this->m_MoneyRemark.pDebugTex->InFmt.r_shift + 2;
  *(_DWORD *)&this->mb_OK.m_canctrl = m_align;
  LOBYTE(m_align) = this->mb_OK.m_caption[96];
  *(_DWORD *)&this->mb_OK.m_hasDBclk = v38;
  this->mb_OK.m_state = (UIButton_UIBUTTON_STATE)(v38 + 90);
  (*(void ( **)(float *, int, _BYTE *, PropUI *, char *, _DWORD, int))(LODWORD(this->m_MoneyRemark.m_ratiow)
                                                                                          + 28))(
    &this->m_MoneyRemark.m_ratiow,
    519,
    &this->mb_OK.m_hasDBclk,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    m_align);
  v39 = v71 - 38;
  v40 = bkWndY - 50;
  this->m_Flag.m_nTextW = bkWndY - 50;
  this->m_Flag.m_FVF = v39;
  v39 += 38;
  *((_DWORD *)&this->m_Flag + 38) = v39;
  LOBYTE(v39) = this->mb_OK.m_caption[96];
  *((_DWORD *)&this->m_Flag + 39) = v40 + 48;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, PropUI *, char *, _DWORD, int))this->m_OutFrameT.__vftable[1].ShowWindow)(
// [VFTABLE]   &this->m_OutFrameT,
// [VFTABLE]   514,
// [VFTABLE]   &this->m_Flag.m_FVF,
// [VFTABLE]   this,
// [VFTABLE]   aUiGamemainuiCo_13,
// [VFTABLE]   0,
// [VFTABLE]   v39);
  ((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40))->CreateScriptAndCamera(545, (int)this);
  if ( !strcmp("D16", g_szSceneUIText) )
    sprintf(this->buf, byte_5967B0, "NONE");
  else
    sprintf(this->buf, "Item\\%s\\%s.pol", "D16", "D16");
  ((PalScript *)(&this->m_Msg.m_btRc + 7))->LoadModel(this->buf, 0);
  *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
  *((_DWORD *)&this->m_Msg.m_btRc + 27) = 1;
  ((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40))->SetFloatParam(100.0);
  ((Camera *)((char *)&this->m_Msg.m_btRc + 40))->UpdateCameraLookAt(330, 258, 600);
  ((UIPushButton *)((char *)&this->m_Msg.m_btRc + 40))->SetAnimOffset(1, 0, v44);
  v69[0] = 300;
  v69[3] = 300;
  v69[1] = 200;
  v69[2] = 500;
  ((ARC_PlayerAtt *)&this->m_Role[1].m_bvisible)->Create((int)&g_PlayerAttBuffer2.skill[2] + 1, (int)v69);
  ((UIItem *)&this->m_Role[1].m_bvisible)->SetData(18);
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
  int v2; // eax
  int i; // eax
  int v4; // eax
  int *m_ListSelNum; // edx
  int *v6; // edx
  int v7; // ebp
  int v8; // ecx
  int v9; // eax
  LONG m_Sum; // eax
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
  int *v24; // [esp+0x0] [ebp-0x1C]
  int p_DWORD; // [esp+0x10] [ebp-0xC] BYREF
  int v26; // [esp+0x14] [ebp-0x8]
  int v27; // [esp+0x18] [ebp-0x4]

  if ( *(_DWORD *)&this->mb_OK.m_caption[60] )
  {
    operator delete(*(void **)&this->mb_OK.m_caption[60]);
    *(_DWORD *)&this->mb_OK.m_caption[60] = 0;
  }
  *(_DWORD *)&this->mb_OK.m_caption[60] = operator new(4 * *(_DWORD *)&this->mb_OK.m_caption[64]);
  v2 = *((_DWORD *)&this->m_PropData + 3475);
  *(_DWORD *)&this->mb_OK.m_caption[68] = 0;
  this->i = 0;
  if ( v2 > 0 )
  {
    do
    {
      i = this->i;
      *((_BYTE *)&this->m_PropData + i + 17304) = this->m_ListSelNum[i] > 0;
      v4 = this->i;
      m_ListSelNum = this->m_ListSelNum;
      this->j = 0;
      if ( m_ListSelNum[v4] > 0 )
      {
        do
        {
          *(_DWORD *)(*(_DWORD *)&this->mb_OK.m_caption[60] + 4 * *(_DWORD *)&this->mb_OK.m_caption[68]) = **((_DWORD **)&this->m_PropData + v4 + 4076);
          v6 = this->m_ListSelNum;
          v7 = this->j + 1;
          ++*(_DWORD *)&this->mb_OK.m_caption[68];
          v4 = this->i;
          this->j = v7;
        }
        while ( v7 < v6[v4] );
      }
      v8 = *((_DWORD *)&this->m_PropData + 3475);
      v9 = this->i + 1;
      this->i = v9;
    }
    while ( v9 < v8 );
  }
  m_Sum = this->m_Sum;
  if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom < m_Sum )
  {
    ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)dword_DC3A3C, 0);
    (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(&this->m_3DObj.m_obj[4].m_pos, 1);
    (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
    LOBYTE(this->m_PropRemark.m_pfather) = 0;
    this->SetSceneStates(1u);
    return sub_445E50((int)&this->m_ListGrid[12].m_pfather);
  }
  else
  {
    ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom -= m_Sum;
    ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)dword_DC383C, 0);
    (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(&this->m_3DObj.m_obj[4].m_pos, 1);
    (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
    LOBYTE(this->m_PropRemark.m_pfather) = 1;
    this->SetSceneStates(0);
    sub_445E50((int)&this->m_ListGrid[12].m_pfather);
    sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
    ((UICaption *)&this->m_btnGroup.m_btnUp.m_caption[20])->SetEnable((int)this->buf, 0);
    if ( this->p_DealData )
    {
      operator delete(this->p_DealData);
      this->p_DealData = 0;
    }
    v11 = *(_DWORD *)&this->mb_OK.m_caption[64];
    v12 = (PlayerItem *)operator new(12 * v11);
    if ( v12 )
    {
      if ( v11 - 1 >= 0 )
      {
        p_item = &v12->item;
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
    this->p_DealData = v12;
    v15 = *(_DWORD *)&this->mb_OK.m_caption[64];
    this->i = 0;
    if ( v15 > 0 )
    {
      do
      {
        this->p_DealData[this->i].id = *(_DWORD *)(*(_DWORD *)&this->mb_OK.m_caption[60] + 4 * this->i);
        this->p_DealData[this->i].num = 1;
        this->p_DealData[this->i].item = (FightItem *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(_DWORD *)(*(_DWORD *)&this->mb_OK.m_caption[60] + 4 * this->i));
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&this->p_DealData[this->i], v24);
        v16 = *(_DWORD *)&this->mb_OK.m_caption[64];
        v17 = this->i + 1;
        this->i = v17;
      }
      while ( v17 < v16 );
    }
    if ( this->p_DealData )
    {
      operator delete(this->p_DealData);
      this->p_DealData = 0;
    }
    if ( *(_DWORD *)&this->mb_OK.m_caption[60] )
    {
      operator delete(*(void **)&this->mb_OK.m_caption[60]);
      *(_DWORD *)&this->mb_OK.m_caption[60] = 0;
    }
    *(_DWORD *)&this->mb_OK.m_caption[64] = 0;
    this->m_Sum = 0;
    sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
    ((UICaption *)&this->m_btnGroup.m_btnDw.m_childs)->SetEnable((int)this->buf, 0);
    ((UICaption *)((char *)&this->ml_ListProp + 1244))->SetEnable((int)g_szSceneUIText, 0);
    v18 = *((_DWORD *)&this->m_PropData + 3475);
    *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
    this->i = 0;
    if ( v18 > 0 )
    {
      do
      {
        this->m_ListSelNum[this->i] = 0;
        sprintf(this->buf, &dir[20], this->m_ListSelNum[this->i]);
        ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetMouseMoveSel(2, this->i, this->buf, 0);
        v19 = this->i;
        p_DWORD = 0xFFFF;
        v26 = 0;
        v27 = 0;
        p_DWORD = **((_DWORD **)&this->m_PropData + v19 + 4076);
        v26 = 1;
        v27 = *((_DWORD *)&this->m_PropData + v19 + 4076);
        v20 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD);
        if ( v20 )
          this->m_MaxNum[this->i] = 99 - v20[1];
        else
          this->m_MaxNum[this->i] = 99;
        if ( this->mb_OK.m_caption[73] )
          this->m_MaxNum[this->i] = *(_DWORD *)&this->mb_OK.m_caption[76];
        v21 = *((_DWORD *)&this->m_PropData + 3475);
        v22 = this->i + 1;
        this->i = v22;
      }
      while ( v22 < v21 );
    }
    ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
      &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
      0);
    (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
      &this->ml_ListProp.m_column[3].head[32],
      0);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->mb_OK.m_texarray.m_ptex[1]->0)(
      // [VTBL_DISPATCH]   &this->mb_OK.m_texarray.m_ptex[1],
      // [VTBL_DISPATCH]   0);
    return ((UISceneMap *)this)->RenderWithUpdate();
  }
}

// 0x0046F160
int PropUI::UpdateCaptions()
{
  int v2; // eax
  int i; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax

  ((UICaption *)((char *)&this->ml_ListProp + 1244))->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->m_btnGroup.m_btnUp.m_benable)->SetEnable((int)g_szSceneUIText, 0);
  *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
  *(_DWORD *)&this->mb_OK.m_caption[64] = 0;
  this->m_Sum = 0;
  sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
  ((UICaption *)&this->m_btnGroup.m_btnDw.m_childs)->SetEnable((int)this->buf, 0);
  v2 = *((_DWORD *)&this->m_PropData + 3475);
  this->i = 0;
  if ( v2 > 0 )
  {
    do
    {
      sprintf(this->buf, &dir[20], 0);
      ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetMouseMoveSel(2, this->i, this->buf, 0);
      i = this->i;
      if ( i < 0 || i >= (int)this->m_ScrollHB.m_ppic )
        v4 = 0;
      else
        v4 = *(&this->m_ScrollHB.m_pbkInfo->filepos + i);
      *(_DWORD *)(v4 + 68) = this->m_ListGrid[12].m_childs.m_pData;
      v5 = *((_DWORD *)&this->m_PropData + 3475);
      v6 = this->i + 1;
      this->i = v6;
    }
    while ( v6 < v5 );
  }
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetItem();
  ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetItem();
  this->SetSceneStates(1u);
  sub_445E50((int)&this->m_ListGrid[12].m_pfather);
  ((CCBRoleState *)this)->NotifyStateChange(0);
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_OutFrameT.__vftable->ShowWindow)(&this->m_OutFrameT, 1);
  ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
    &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
    0);
  (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
    &this->ml_ListProp.m_column[3].head[32],
    0);
  // [VTBL_DISPATCH] result = ((int ( *)(gbTexture **, _DWORD))this->mb_OK.m_texarray.m_ptex[1]->0)(
             // [VTBL_DISPATCH]   &this->mb_OK.m_texarray.m_ptex[1],
             // [VTBL_DISPATCH]   0);
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
  sprintf(this->buf, g_szSceneUIText);
  v4 = sub_458F70((LPCSTR)(*((_DWORD *)&this->m_PropData + nItemIdx + 4076) + 96), (int)asc_5B74B8, this->remarkbuf);
  if ( lstrlenA(v4) <= 0 )
  {
    ((RoleAtt *)v5)->FormatAttributeText();
    lstrcatA(buf, v6);
  }
  else
  {
    lstrcpyA(buf, v4);
  }
  ((UICaption *)&this->m_btnGroup.m_btnUp.m_benable)->SetEnable((int)buf, 0);
  ((UICaption *)((char *)&this->ml_ListProp + 1244))->SetEnable((int)this->remarkbuf, 0);
}

// 0x0046F620
int PropUI::HandleInput(int nVal, int nVal2)
{
  sub_46F3D0(this);
  ((GRPinput *)this)->ProcessMouseInput(*(float *)&nVal);
  ((UIListBox *)this)->Update(nVal, nVal2);
  return 1;
}

// 0x0046F650
int PropUI::InitListUI(int arg0, int nVal, unsigned int dwVal)
{
  int *m_ListSelNum; // eax
  int *v6; // edi
  int v7; // eax
  int v8; // eax
  LONG *p_right; // ecx
  UICursor *m_MaxNum; // ecx
  int v11; // edi
  int **v12; // ebx
  int *v13; // eax
  int *v14; // eax
  CScreenMode *Instance; // eax
  int v17; // ecx
  int *v18; // edx
  int i; // eax
  int v20; // eax
  CScreenMode *v21; // eax
  int j; // edi
  int v23; // eax
  int v24; // eax
  int m_SelNum; // eax
  int v26; // eax
  int *v27; // ecx
  int v28; // eax
  CScreenMode *v29; // eax
  int v30; // eax
  int v31; // eax
  int *v32; // ebp
  int v33; // ebx
  int v34; // edi
  __int64 v35; // rax
  int v36; // ecx
  int *v37; // ecx
  int v38; // edx
  int v39; // eax
  int v40; // ebx
  int v41; // ebx
  int *v42; // eax
  int *v43; // eax
  CScreenMode *v44; // eax
  int v45; // eax
  int v46; // eax
  int *v47; // ebp
  int v48; // ebx
  int v49; // edi
  int v50; // eax
  int *v51; // ecx
  int v52; // edx
  int v53; // eax
  int v54; // ebx
  int v55; // ebx
  int *v56; // eax
  int v57; // eax
  const char *v58; // ebp
  int v59; // eax
  const char *v60; // ebp
  const char *v61; // edx
  float *v62; // eax
  float v63; // ebx
  gbTexture **v64; // edi
  float v65; // ebp
  int v66; // edx
  _PlugInfo **v67; // edi
  _PlugInfo *v68; // ecx
  _PlugInfo *v69; // eax
  int v70; // ebx
  int v71; // edx
  _PlugInfo *v72; // eax
  int v73; // ecx
  _PlugInfo *v74; // eax
  _PlugInfo *v75; // eax
  _PlugInfo *v76; // ecx
  char *v77; // ecx
  int v78; // edx
  _PlugInfo *v79; // edx
  int v80; // eax
  _PlugInfo *v81; // eax
  _PlugInfo *v82; // edx
  int m_bfocus; // edx
  signed int v84; // ecx
  int v85; // eax
  int v86; // edi
  const void *v87; // [esp+0x0] [ebp-0x134]
  const void *v88; // [esp+0x0] [ebp-0x134]
  _SPropValue *v89; // [esp+0x0] [ebp-0x134]
  _SPropValue *v90; // [esp+0x0] [ebp-0x134]
  int m_Sum; // [esp+0x4] [ebp-0x130]
  int v92; // [esp+0x4] [ebp-0x130]
  int p_DWORD; // [esp+0x18] [ebp-0x11C] BYREF
  int v94; // [esp+0x1C] [ebp-0x118]
  int *v95; // [esp+0x20] [ebp-0x114]
  gbColorQuad v96; // [esp+0x24] [ebp-0x110] BYREF
  gbColorQuad v97; // [esp+0x28] [ebp-0x10C] BYREF
  int pOut; // [esp+0x2C] [ebp-0x108] BYREF
  char Buffer[253]; // [esp+0x34] [ebp-0x100] BYREF
  __int16 v100; // [esp+0x131] [ebp-0x3]
  char v101; // [esp+0x133] [ebp-0x1]

  switch ( arg0 )
  {
    case 1000:
      m_ListSelNum = this->m_ListSelNum;
      if ( nVal )
      {
        if ( m_ListSelNum )
        {
          operator delete(this->m_ListSelNum);
          this->m_ListSelNum = 0;
        }
        v6 = (int *)operator new(4 * *((_DWORD *)&this->m_PropData + 3475));
        this->m_ListSelNum = v6;
        memset(v6, 0, 4 * *((_DWORD *)&this->m_PropData + 3475));
        if ( ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetItemData() <= 0 )
        {
          this->m_SelNum = -1;
          ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
            &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
            0);
          (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
            &this->ml_ListProp.m_column[3].head[32],
            0);
          (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
          // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->mb_OK.m_texarray.m_ptex[1]->0)(
            // [VTBL_DISPATCH]   &this->mb_OK.m_texarray.m_ptex[1],
            // [VTBL_DISPATCH]   0);
        }
        else
        {
          this->m_SelNum = 0;
          this->OnMessage(1007, 0, 0);
          if ( *((int *)&this->m_PropData + 3475) >= 0 )
            ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetItem();
        }
        ((UIStatic *)&this->m_ListGrid[10].m_rect)->CreateFromTemplate();
        v7 = *(_DWORD *)&this->mb_OK.m_caption[84];
        if ( v7 )
        {
          if ( v7 == 1 )
          {
            sub_445E50((int)&this->m_ListGrid[12].m_pfather);
            sub_445E50((int)&this->m_btnGroup.m_btnDw.m_caption[12]);
            (*(void ( **)(PtrArray *, _DWORD))this->m_PropRemark.m_childs.m_pData)(
              &this->m_PropRemark.m_childs,
              0);
            sub_445E50((int)&this->m_MoneyRemark.m_ratiow);
            sub_445E50((int)&this->m_OutFrameT);
            ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)g_szSceneUIText, 0);
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
          ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)&this->m_PropData + 2060, 0);
          (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
          sub_445E50((int)&this->m_ListGrid[12].m_pfather);
          sub_445E50((int)&this->m_btnGroup.m_btnDw.m_caption[12]);
          (*(void ( **)(PtrArray *, int))this->m_PropRemark.m_childs.m_pData)(&this->m_PropRemark.m_childs, 1);
          sub_445E50((int)&this->m_MoneyRemark.m_ratiow);
          ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
            &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
            0);
          (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
            &this->ml_ListProp.m_column[3].head[32],
            0);
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
          ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)&this->m_PropData + 524, 0);
          v8 = lstrlenA((LPCSTR)&this->m_PropData + 524);
          p_right = &this->m_OutFrameL.m_rect.right;
          if ( v8 > 0 )
            (*(void ( **)(LONG *, int))*p_right)(p_right, 1);
          else
            (*(void ( **)(LONG *, _DWORD))*p_right)(p_right, 0);
        }
        sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
        ((UICaption *)&this->m_btnGroup.m_btnUp.m_caption[20])->SetEnable((int)this->buf, 0);
        v11 = 0;
        if ( *((int *)&this->m_PropData + 3475) > 0 )
        {
          v12 = (int **)((char *)&this->m_PropData + 16304);
          do
          {
            v13 = *v12;
            p_DWORD = 0xFFFF;
            v94 = 0;
            v95 = 0;
            p_DWORD = *v13;
            v94 = 1;
            v95 = v13;
            v14 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD);
            if ( v14 )
            {
              m_MaxNum = (UICursor *)(99 - v14[1]);
              this->m_MaxNum[v11] = (int)m_MaxNum;
            }
            else
            {
              this->m_MaxNum[v11] = 99;
            }
            if ( this->mb_OK.m_caption[73] )
            {
              m_MaxNum = (UICursor *)this->m_MaxNum;
              m_MaxNum->m_dwID[v11] = *(_DWORD *)&this->mb_OK.m_caption[76];
            }
            ++v11;
            ++v12;
          }
          while ( v11 < *((_DWORD *)&this->m_PropData + 3475) );
        }
        BYTE1(this->ml_ListProp.m_column[7].items.m_pData) = 1;
        LOBYTE(this->ml_ListProp.m_column[7].items.m_pData) = 1;
        ((UICursor *)m_MaxNum)->IRender();
        return 1;
      }
      else
      {
        if ( m_ListSelNum )
        {
          operator delete(this->m_ListSelNum);
          this->m_ListSelNum = 0;
        }
        return 1;
      }
    case 1001:
      switch ( nVal )
      {
        case 514:
          ((UISceneMap *)this)->RenderWithUpdate();
          v87 = off_5B7650;
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v87, 1);
          return 1;
        case 518:
          if ( ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetItemData() <= 0 )
            goto LABEL_32;
          v17 = *((_DWORD *)&this->m_PropData + 3475);
          this->mb_OK.m_caption[72] = 0;
          this->i = 0;
          if ( v17 > 0 )
          {
            v18 = this->m_ListSelNum;
            do
            {
              i = this->i;
              if ( v18[i] > 0 )
                this->mb_OK.m_caption[72] = 1;
              v20 = i + 1;
              this->i = v20;
            }
            while ( v20 < v17 );
          }
          if ( this->mb_OK.m_caption[72] )
          {

          }
          else if ( !*(_DWORD *)&this->mb_OK.m_caption[84] )
          {
            ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)&this->m_PropData + 524, 0);
            (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(
              &this->m_3DObj.m_obj[4].m_pos,
              1);
            (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
            LOBYTE(this->m_PropRemark.m_pfather) = 0;
            ((CCBRoleState *)this)->NotifyStateChange(1u);
          }
          goto LABEL_42;
        case 519:
          if ( ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetItemData() <= 0 )
          {
LABEL_32:
            this->m_SelNum = -1;
            ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
              &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
              0);
            (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
              &this->ml_ListProp.m_column[3].head[32],
              0);
            (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
            // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->mb_OK.m_texarray.m_ptex[1]->0)(
              // [VTBL_DISPATCH]   &this->mb_OK.m_texarray.m_ptex[1],
              // [VTBL_DISPATCH]   0);
            return 1;
          }
          else
          {
            for ( j = 0;
                  j < *((_DWORD *)&this->m_PropData + 3475);
                  *(_DWORD *)(v23 + 68) = this->m_ListGrid[12].m_childs.m_pData )
            {
              this->m_ListSelNum[j] = 0;
              sprintf(this->buf, &dir[20], this->m_ListSelNum[j]);
              ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetMouseMoveSel(2, j, this->buf, 0);
              if ( j < 0 || j >= (int)this->m_ScrollHB.m_ppic )
                v23 = 0;
              else
                v23 = *(&this->m_ScrollHB.m_pbkInfo->filepos + j);
              ++j;
            }
            ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetItem();
            ((UIListBox *)&this->m_ListGrid[12].m_pfather)->GetItem();
            *(_DWORD *)&this->mb_OK.m_caption[64] = 0;
            this->m_Sum = 0;
            LOBYTE(this->m_PropRemark.m_pfather) = 0;
            sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
            ((UICaption *)&this->m_btnGroup.m_btnDw.m_childs)->SetEnable((int)this->buf, 0);
            ((UICaption *)((char *)&this->ml_ListProp + 1244))->SetEnable((int)g_szSceneUIText, 0);
            *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
            ((UICaption *)&this->m_btnGroup.m_btnUp.m_benable)->SetEnable((int)g_szSceneUIText, 0);
            (*(void ( **)(gbVec3D *, int))LODWORD(this->m_3DObj.m_obj[4].m_pos.x))(
              &this->m_3DObj.m_obj[4].m_pos,
              1);
            ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
              &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
              0);
            (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
              &this->ml_ListProp.m_column[3].head[32],
              0);
            // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->mb_OK.m_texarray.m_ptex[1]->0)(
              // [VTBL_DISPATCH]   &this->mb_OK.m_texarray.m_ptex[1],
              // [VTBL_DISPATCH]   0);
            v24 = *(_DWORD *)&this->mb_OK.m_caption[84];
            if ( v24 )
            {
              if ( v24 == 1 )
              {
                ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)g_szSceneUIText, 0);
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
              ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)&this->m_PropData + 1292, 0);
              (*(void ( **)(LONG *, int))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 1);
            }
LABEL_42:
            v88 = off_5B7650;
            v21 = CScreenMode::GetInstance();
            ((CScreenMode *)v21)->AudioSetPosition(v88, 1);
            return 1;
          }
        case 546:
          ((CCBRoleState *)this)->NotifyStateChange(0);
          m_SelNum = this->m_SelNum;
          if ( m_SelNum < 0 )
            return 1;
          ++this->m_ListSelNum[m_SelNum];
          v26 = this->m_SelNum;
          v27 = &this->m_ListSelNum[v26];
          v28 = this->m_MaxNum[v26];
          if ( *v27 < v28 )
          {
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            v89 = (_SPropValue *)off_5B7660;
          }
          else
          {
            *v27 = v28;
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            if ( !*(_DWORD *)&this->mb_OK.m_caption[84] )
            {
              sprintf(this->buf, "\\n      %s", (const char *)dword_DCCC3C);
              ((UICaption *)&this->m_Role[4].m_bvisible)->SetEnable((int)this->buf, 0);
              ((UIRoleSelect *)&this->m_Role[1].m_bvisible)->SetByte(1);
            }
            v89 = off_5B765C;
          }
          v29 = CScreenMode::GetInstance();
          ((CScreenMode *)v29)->AudioSetPosition(v89, 1);
          sprintf(this->buf, &dir[20], this->m_ListSelNum[this->m_SelNum]);
          ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetMouseMoveSel(2, this->m_SelNum, this->buf, 0);
          v30 = this->m_SelNum;
          if ( this->m_ListSelNum[v30] <= 0 )
          {
            if ( v30 < 0 || v30 >= (int)this->m_ScrollHB.m_ppic )
              v31 = 0;
            else
              v31 = *(&this->m_ScrollHB.m_pbkInfo->filepos + v30);
            *(_DWORD *)(v31 + 68) = this->m_ListGrid[12].m_childs.m_pData;
          }
          else
          {
            ((UITabCtrl *)&this->m_ListGrid[12].m_pfather)->SetItemParam(this->m_SelNum);
          }
          if ( this->mb_OK.m_caption[73] )
          {
            v32 = this->m_ListSelNum;
            v33 = *((_DWORD *)&this->m_PropData + 3475);
            this->m_Sum = (__int64)((double)*(int *)(*((_DWORD *)&this->m_PropData + 4076) + 608)
                                  * *(float *)&this->mb_OK.m_caption[80]
                                  * (double)*v32);
            *(_DWORD *)&this->mb_OK.m_caption[64] = *v32;
            this->i = 1;
            if ( v33 > 1 )
            {
              do
              {
                v34 = this->i;
                v35 = (__int64)((double)*(int *)(*((_DWORD *)&this->m_PropData + v34 + 4076) + 608)
                              * *(float *)&this->mb_OK.m_caption[80]
                              * (double)v32[v34]);
                HIDWORD(v35) = *(_DWORD *)&this->mb_OK.m_caption[64];
                v36 = v35 + this->m_Sum;
                this->m_Sum = v36;
                *(_DWORD *)&this->mb_OK.m_caption[64] = v32[v34] + HIDWORD(v35);
                this->i = v34 + 1;
              }
              while ( v34 + 1 < v33 );
              m_Sum = v36;
LABEL_92:
              sprintf(this->buf, "%s %d", g_szCombatFieldName, m_Sum);
              ((UICaption *)&this->m_btnGroup.m_btnDw.m_childs)->SetEnable((int)this->buf, 0);
              return 1;
            }
          }
          else
          {
            v37 = this->m_ListSelNum;
            this->m_Sum = *v37 * *(_DWORD *)(*((_DWORD *)&this->m_PropData + 4076) + 608);
            *(_DWORD *)&this->mb_OK.m_caption[64] = *v37;
            v38 = *((_DWORD *)&this->m_PropData + 3475);
            this->i = 1;
            if ( v38 > 1 )
            {
              do
              {
                v39 = this->i;
                v40 = *(_DWORD *)&this->mb_OK.m_caption[64];
                this->m_Sum += v37[v39] * *(_DWORD *)(*((_DWORD *)&this->m_PropData + v39 + 4076) + 608);
                v41 = v37[v39++] + v40;
                *(_DWORD *)&this->mb_OK.m_caption[64] = v41;
                this->i = v39;
              }
              while ( v39 < v38 );
            }
          }
          m_Sum = this->m_Sum;
          goto LABEL_92;
        case 547:
          ((CCBRoleState *)this)->NotifyStateChange(0);
          v42 = &this->m_ListSelNum[this->m_SelNum];
          --*v42;
          v43 = &this->m_ListSelNum[this->m_SelNum];
          if ( *v43 > 0 )
          {
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            v90 = (_SPropValue *)off_5B7660;
          }
          else
          {
            *v43 = 0;
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            v90 = off_5B765C;
          }
          v44 = CScreenMode::GetInstance();
          ((CScreenMode *)v44)->AudioSetPosition(v90, 1);
          sprintf(this->buf, &dir[20], this->m_ListSelNum[this->m_SelNum]);
          ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetMouseMoveSel(2, this->m_SelNum, this->buf, 0);
          v45 = this->m_SelNum;
          if ( this->m_ListSelNum[v45] <= 0 )
          {
            if ( v45 < 0 || v45 >= (int)this->m_ScrollHB.m_ppic )
              v46 = 0;
            else
              v46 = *(&this->m_ScrollHB.m_pbkInfo->filepos + v45);
            *(_DWORD *)(v46 + 68) = this->m_ListGrid[12].m_childs.m_pData;
          }
          else
          {
            ((UITabCtrl *)&this->m_ListGrid[12].m_pfather)->SetItemParam(this->m_SelNum);
          }
          if ( this->mb_OK.m_caption[73] )
          {
            v47 = this->m_ListSelNum;
            v48 = *((_DWORD *)&this->m_PropData + 3475);
            this->m_Sum = (__int64)((double)*(int *)(*((_DWORD *)&this->m_PropData + 4076) + 608)
                                  * *(float *)&this->mb_OK.m_caption[80]
                                  * (double)*v47);
            *(_DWORD *)&this->mb_OK.m_caption[64] = *v47;
            this->i = 1;
            if ( v48 > 1 )
            {
              do
              {
                v49 = this->i;
                v50 = *(_DWORD *)&this->mb_OK.m_caption[64];
                this->m_Sum += (__int64)((double)*(int *)(*((_DWORD *)&this->m_PropData + v49 + 4076) + 608)
                                       * *(float *)&this->mb_OK.m_caption[80]
                                       * (double)v47[v49]);
                *(_DWORD *)&this->mb_OK.m_caption[64] = v47[v49] + v50;
                this->i = v49 + 1;
              }
              while ( v49 + 1 < v48 );
            }
          }
          else
          {
            v51 = this->m_ListSelNum;
            this->m_Sum = *v51 * *(_DWORD *)(*((_DWORD *)&this->m_PropData + 4076) + 608);
            v52 = *((_DWORD *)&this->m_PropData + 3475);
            *(_DWORD *)&this->mb_OK.m_caption[64] = *v51;
            this->i = 1;
            if ( v52 > 1 )
            {
              do
              {
                v53 = this->i;
                v54 = *(_DWORD *)&this->mb_OK.m_caption[64];
                this->m_Sum += v51[v53] * *(_DWORD *)(*((_DWORD *)&this->m_PropData + v53 + 4076) + 608);
                v55 = v51[v53++] + v54;
                *(_DWORD *)&this->mb_OK.m_caption[64] = v55;
                this->i = v53;
              }
              while ( v53 < v52 );
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
      (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
        &this->ml_ListProp.m_column[3].head[32],
        0);
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->mb_OK.m_texarray.m_ptex[1]->0)(
        // [VTBL_DISPATCH]   &this->mb_OK.m_texarray.m_ptex[1],
        // [VTBL_DISPATCH]   0);
      return 1;
    case 1007:
      this->m_SelNum = dwVal;
      if ( (int)dwVal > -1 )
      {
        ((UICaption *)&this->m_3DObj.m_obj[4].m_pos)->SetEnable((int)g_szSceneUIText, 0);
        (*(void ( **)(LONG *, _DWORD))this->m_OutFrameL.m_rect.right)(&this->m_OutFrameL.m_rect.right, 0);
        this->UpdateItemDetail(this->m_SelNum);
        switch ( *(_BYTE *)(*((_DWORD *)&this->m_PropData + this->m_SelNum + 4076) + 612) )
        {
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
            ((UIStatic *)&this->m_ListGrid[10].m_rect)->CreateFromTemplate();
            break;
          default:
            break;
        }
        v56 = (int *)*((_DWORD *)&this->m_PropData + this->m_SelNum + 4076);
        if ( *((_BYTE *)v56 + 613) == 5 )
        {
          ((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40))->SetFloatParam(228.0);
          ((Camera *)((char *)&this->m_Msg.m_btRc + 40))->UpdateCameraLookAt(330, 280, 600);
        }
        else if ( *((_BYTE *)v56 + 612) == 11 )
        {
          ((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40))->SetFloatParam(228.0);
          ((Camera *)((char *)&this->m_Msg.m_btRc + 40))->UpdateCameraLookAt(330, 272, 600);
        }
        else
        {
          v57 = *v56;
          if ( v57 == 8114 || v57 == 8132 )
          {
            ((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40))->SetFloatParam(180.0);
            ((Camera *)((char *)&this->m_Msg.m_btRc + 40))->UpdateCameraLookAt(330, 252, 600);
          }
          else
          {
            ((CCBFiveNimbusWindow *)((char *)&this->m_Msg.m_btRc + 40))->SetFloatParam(180.0);
            ((Camera *)((char *)&this->m_Msg.m_btRc + 40))->UpdateCameraLookAt(330, 268, 600);
          }
        }
        if ( !strcmp((const char *)(*((_DWORD *)&this->m_PropData + this->m_SelNum + 4076) + 36), g_szSceneUIText) )
        {
          sprintf(this->buf, byte_5967B0, "NONE");
        }
        else
        {
          v58 = (const char *)(*((_DWORD *)&this->m_PropData + this->m_SelNum + 4076) + 36);
          sprintf(this->buf, "Item\\%s\\%s.pol", v58, v58);
        }
        ((PalScript *)(&this->m_Msg.m_btRc + 7))->LoadModel(this->buf, 0);
        v59 = *((_DWORD *)&this->m_PropData + this->m_SelNum + 4076);
        v60 = (const char *)(v59 + 36);
        v61 = (const char *)(v59 + 66);
        if ( !strcmp((const char *)(v59 + 36), g_szSceneUIText) )
        {
          sprintf(this->buf, byte_5967B0, "NONE");
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v100 = 0;
          v101 = 0;
          sprintf(Buffer, "%s%s", v60, v61);
          sprintf(this->buf, "Item\\%s\\%s.tga", v60, Buffer);
        }
        ((gbGeomNode *)*((gbGeomNode **)&this->m_Msg.m_btRc + 32))->ReplaceTexture(this->buf);
        v92 = this->m_SelNum;
        *((_DWORD *)&this->m_Msg.m_btRc + 29) = 1;
        GetGridOffset(&this->m_ListGrid[12].m_pfather, &pOut, v92);
        v63 = *v62;
        v64 = &this->mb_OK.m_texarray.m_ptex[1];
        v65 = v62[1];
        this->mb_OK.m_offsetx = *(_DWORD *)v62 + 90;
        this->mb_OK.m_offsety = v65;
        *(_DWORD *)&this->mb_OK.m_bBigFont = LODWORD(v63) + 180;
        this->mb_OK.m_texarray.m_ptex[0] = (gbTexture *)(LODWORD(v65) + 32);
        sub_445FA0(&this->mb_OK.m_texarray.m_ptex[1]);
        sprintf(this->buf, "%s:%d", (const char *)&g_bSaveFlag, 99 - this->m_MaxNum[this->m_SelNum]);
        ((UICaption *)&this->mb_OK.m_texarray.m_ptex[1])->SetEnable((int)this->buf, 0);
        if ( *(_DWORD *)&this->mb_OK.m_caption[84] )
          // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*v64)->0)(&this->mb_OK.m_texarray.m_ptex[1], 0);
        else
          // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*v64)->0)(&this->mb_OK.m_texarray.m_ptex[1], 1);
        v66 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[48];
        v67 = &this->ml_ListProp.m_scrollbar.m_texarrayInfo[1];
        v68 = (_PlugInfo *)(LODWORD(v65) - 4);
        v69 = (_PlugInfo *)(LODWORD(v63) + 200);
        if ( v66 )
        {
          if ( v66 != 1 )
          {
LABEL_120:
            ((void ( *)(_PlugInfo **, int))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
              &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
              1);
            (**(void ( ***)(char *, int))&this->ml_ListProp.m_column[3].head[32])(
              &this->ml_ListProp.m_column[3].head[32],
              1);
            sub_445E50((int)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
            sub_445E50((int)&this->ml_ListProp.m_column[3].head[32]);
            return 1;
          }
          v70 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[40];
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[6] = v68;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[5] = v69;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[7] = (_PlugInfo *)((char *)v69 + v70);
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[8] = (_PlugInfo *)((char *)v68
                                                                        + *(_DWORD *)&this->ml_ListProp.m_column[7].head[44]);
          sub_445FA0(&this->ml_ListProp.m_column[3].head[32]);
          v71 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[52];
          v72 = this->ml_ListProp.m_scrollbar.m_texarrayInfo[7];
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[2] = this->ml_ListProp.m_scrollbar.m_texarrayInfo[6];
          v73 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[40];
          v74 = (_PlugInfo *)((char *)v72 + v71);
          *v67 = v74;
          v75 = (_PlugInfo *)((char *)v74 + v73);
          v76 = this->ml_ListProp.m_scrollbar.m_texarrayInfo[8];
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[3] = v75;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[4] = v76;
          v77 = (char *)&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9];
        }
        else
        {
          v78 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[40];
          *v67 = v69;
          v79 = (_PlugInfo *)((char *)v69 + v78);
          v80 = *(_DWORD *)&this->ml_ListProp.m_column[7].head[44];
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[2] = v68;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[3] = v79;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[4] = (_PlugInfo *)((char *)v68 + v80);
          sub_445FA0(&this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]);
          v81 = (_PlugInfo *)((char *)this->ml_ListProp.m_scrollbar.m_texarrayInfo[4]
                            + *(_DWORD *)&this->ml_ListProp.m_column[7].head[52]);
          v82 = *v67;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[6] = v81;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[5] = v82;
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[7] = this->ml_ListProp.m_scrollbar.m_texarrayInfo[3];
          v77 = &this->ml_ListProp.m_column[3].head[32];
          this->ml_ListProp.m_scrollbar.m_texarrayInfo[8] = (_PlugInfo *)((char *)v81
                                                                        + *(_DWORD *)&this->ml_ListProp.m_column[7].head[44]);
        }
        sub_445FA0(v77);
        goto LABEL_120;
      }
      ((UICaption *)((char *)&this->ml_ListProp + 1244))->SetEnable((int)g_szSceneUIText, 0);
      *((_DWORD *)&this->m_Msg.m_btRc + 29) = 0;
      ((void ( *)(_PlugInfo **, _DWORD))this->ml_ListProp.m_scrollbar.m_texarrayInfo[9]->filepos)(
        &this->ml_ListProp.m_scrollbar.m_texarrayInfo[9],
        0);
      (**(void ( ***)(char *, _DWORD))&this->ml_ListProp.m_column[3].head[32])(
        &this->ml_ListProp.m_column[3].head[32],
        0);
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->mb_OK.m_texarray.m_ptex[1]->0)(
        // [VTBL_DISPATCH]   &this->mb_OK.m_texarray.m_ptex[1],
        // [VTBL_DISPATCH]   0);
      return ((PalScript *)this)->OnMessage(arg0, nVal, dwVal);
    case 1009:
      if ( nVal != 521 )
        return 1;
      m_bfocus = this->m_Dlg.m_bfocus;
      v84 = HIWORD(dwVal);
      this->m_x = (unsigned __int16)dwVal;
      this->m_y = HIWORD(dwVal);
      if ( (unsigned __int16)dwVal <= m_bfocus
        || (unsigned __int16)dwVal >= this->m_Dlg.m_align
        || v84 <= (int)this->m_Dlg.pDebugTex
        || v84 >= SLODWORD(this->m_Dlg.m_ratiow) )
      {
        return 1;
      }
      v85 = *(_DWORD *)&this->mb_OK.m_caption[84];
      if ( v85 )
      {
        if ( v85 == 1 )
        {

          v86 = 0;
          if ( *((int *)&this->m_PropData + 3475) > 0 )
          {
            do
            {
              this->m_ListSelNum[v86] = 0;
              sprintf(this->buf, &dir[20], this->m_ListSelNum[v86]);
              ((UIListBox *)&this->m_ListGrid[12].m_pfather)->SetMouseMoveSel(2, v86++, this->buf, 0);
            }
            while ( v86 < *((_DWORD *)&this->m_PropData + 3475) );
            return 1;
          }
        }
      }
      else
      {
        if ( g_bListNeedsRefresh )
        {

          ((UIFrameWnd *)*(UIFrameWnd **)&this->mb_OK.m_caption[88])->OnPaintUpdate();
          return 1;
        }
        if ( LOBYTE(this->m_PropRemark.m_pfather) )
        {

          return 1;
        }
        ((CCBRoleState *)this)->NotifyStateChange(0);
      }
      return 1;
    case 1010:
      return 1;
    default:
      return ((PalScript *)this)->OnMessage(arg0, nVal, dwVal);
  }
}

// 0x00521A50
int PropUI::SetPendingMessage(char msg, int wparam, int lparam)
{
  this->mb_OK.m_caption[73] = msg;
  *(_DWORD *)&this->mb_OK.m_caption[76] = wparam;
  *(_DWORD *)&this->mb_OK.m_caption[80] = lparam;
  return lparam;
}
