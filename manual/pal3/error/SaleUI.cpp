#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SaleUI.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Role/Actor.h"
#include "Misc/ArcSceneObject.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Misc/CCBUIPanel.h"
#include "Render/CScreenMode.h"
#include "Scene/Camera.h"
#include "Misc/FightItem.h"
#include "GameBase/GRPinput.h"
#include "Misc/MUIDialog.h"
#include "Misc/NameSys.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "Misc/PlayerMgr.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Misc/SaleUI_SortData.h"
#include "Scene/SceneObj.h"
#include "Misc/UI3DCtrl.h"
#include "Misc/UIButton.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIItem.h"
#include "UI/UILBColumn.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UIStatic.h"
#include "Misc/UITextArea.h"
#include "Misc/UITitle_JDHY.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern char asc_5B74B8[];
extern CHAR byte_DC343C[256];
extern CHAR byte_DCEB3C[256];

// 0x0045A7B0
SaleUI::SaleUI()
{
  int *v2; // eax
  SaleUI_SortData *v3; // ebp
  bool v4; // zf
  int bkHeight; // kr00_4
  int *v6; // [esp+0x10] [ebp-0x18]
  int v7; // [esp+0x14] [ebp-0x14]

  ((UIListBox *)this)->UIListBox::UIListBox();
  this->bkWidth = 800;
  this->bkHeight = 600;
  *(_DWORD *)this->remarkbuf = 0;
  *(_DWORD *)&this->remarkbuf[4] = 0;
  *(_DWORD *)&this->remarkbuf[16] = 0;
  *(_DWORD *)&this->remarkbuf[20] = 0;
  *(_DWORD *)&this->remarkbuf[24] = 0;
  *(_DWORD *)&this->remarkbuf[28] = 0;
  this->remarkbuf[32] = 0;
  *(_DWORD *)&this->remarkbuf[36] = 1090519040;
  *(_WORD *)&this->remarkbuf[42] = 0;
  *(&this->dwWeaponWU + 3264) = 0;
  v7 = 5;
  *(&this->dwWeaponWU + 3265) = 0;
  memset(&this->dwWeaponWU + 3266, 0, 0x640u);
  memset(&this->dwWeaponWU + 4066, 0, 0x190u);
  memset(&this->dwWeaponWU + 3666, 0, 0x640u);
  v2 = (int *)(&this->dwWeaponWU + 4167);
  *(_DWORD *)&this->remarkbuf[40] = 0;
  *(&this->dwWeaponWU + 4166) = 0;
  v6 = (int *)(&this->dwWeaponWU + 4167);
  v3 = (SaleUI_SortData *)&this->m_sort[32][1];
  while ( 1 )
  {
    *v2 = 0;
    *(_WORD *)v3[-214]._tail_000 = 0;
    lstrcpyA((LPSTR)&v3[-214] + 2, unk_C10D38);
    lstrcpyA((LPSTR)&v3[-86] + 2, unk_C10D38);
    lstrcpyA((LPSTR)&v3[-78], unk_C10D38);
    lstrcpyA((LPSTR)&v3[-65], unk_C10D38);
    memset(&v3[-56], 0, 0x30u);
    v3[-20] = 0;
    v3[-2] = (SaleUI_SortData)0xFFFF;
    v3[-1] = 0;
    *v3 = 0;
    v3[1] = (SaleUI_SortData)0xFFFF;
    v3[2] = 0;
    v3[3] = 0;
    v3[4] = (SaleUI_SortData)0xFFFF;
    v3[5] = 0;
    v3[6] = 0;
    ArraySort((int)&v3[7], 12, 2, 0 /* TODO: pmf_to_u32((void (exception::*)())exception::exception) */);
    v3[13] = (SaleUI_SortData)0xFFFF;
    v3[14] = 0;
    v3[15] = 0;
    memset(v6, 0, 0x580u);
    v3 += 352;
    v4 = v7 == 1;
    v6 += 352;
    --v7;
    if ( v4 )
      break;
    v2 = (int *)v6;
  }
  (((UIFrameContainer *)this->m_sort[342]))->UIFrameContainer::ResetContainerState();
  ((UI3DCtrl *)&this->m_sort[349][3])->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)&this->m_sort[353][4]))->UIFrameContainer::ResetContainerState();
  ((PalScript *)&this->m_sort[361][2])->PalScript::PalScript();
  *(&this->m_bWPXS + 1258) = 0;
  LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
  HIBYTE(this->m_ListSaleTitle.m_childs.m_nSize) = 0;
  this->m_ListSaleTitle.m_childs.m_needscriptdel = 0;
  this->m_ListEquipTitleRc.bottom = 0;
  *(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) = 0;
  (((UIProgressBar *)&this->m_Icon[0][0].m_rect))->UIProgressBar::ctor();
  ((UIRoleDialog *)&this->m_Icon[0][1].m_FVF)->UIRoleDialog::UIRoleDialog();
  (((UIFrameContainer *)&this->m_Icon[1][4].m_align))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Icon[2][0].m_childs.m_nSize))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Icon[2][1].m_rect))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Icon[2][1].m_fadespeed))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)&this->m_Icon[3][1].m_ppicInfo))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Icon[3][2].m_pbk))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_ListGrid[1].m_disablepic))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_ListGrid[2].m_disablepic))->UIFrameContainer::ResetContainerState();
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::UpdateKeyCtrl();
  NameSys::GetSys();
  NameSys::GetSys();
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[0] = (gbTexture *)32;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[1] = (gbTexture *)16;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[2] = 0;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[3] = 0;
  (((UIFrameContainer *)&this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[7]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->ml_ResumeList.m_column[0].head[16]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->ml_ResumeList.m_column[2].head[16]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->ml_ResumeList.m_column[4].head[16]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->ml_ResumeList.m_column[6].head[16]))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)(&this->AttackNum + 112)))->UIFrameContainer::ResetContainerState();
  *((_BYTE *)&this->AttackNum + 600) = 0;
  *((_BYTE *)&this->AttackNum + 601) = 0;
  *((_BYTE *)&this->AttackNum + 1114) = 0;
  *(&this->AttackNum + 279) = 0;
  *(&this->AttackNum + 280) = -1;
  *(&this->AttackNum + 281) = -1;
  *((_BYTE *)&this->AttackNum + 1128) = 0;
  *(&this->AttackNum + 283) = 0;
  *(&this->AttackNum + 284) = 0;
  *(&this->AttackNum + 286) = 0;
  *(&this->AttackNum + 287) = 0;
  *((_BYTE *)&this->AttackNum + 1152) = 0;
  *((_BYTE *)&this->AttackNum + 1160) = 0;
  lstrcpyA((LPSTR)&this->AttackNum + 602, Destination);
  lstrcpyA((LPSTR)&this->AttackNum + 858, byte_DC343C);
  memset(&this->remarkbuf[40], 0, 0x4460u);
  memset(&this->dwWeaponWU + 4167, 0, 0x580u);
  this->m_sort[412][2]._tail_000[0] = 1;
  this->m_sort[412][3]._tail_000[0] = 0;
  this->m_sort[412][2]._tail_000[3] = 0;
  this->m_sort[412][2]._tail_000[2] = 0;
  this->m_sort[412][2]._tail_000[1] = 0;
  memset((char *)&this->m_ListSaleTitle.m_rect.left + 1, 0, 0x1Cu);
  *(_WORD *)((char *)&this->m_ListSaleTitle.m_childs.m_nSize + 1) = 0;
  memset(&this->m_ListSaleTitle.m_bcreateok, 0xFFu, 0x78u);
  memset(&this->m_bWPXS + 1198, 0, 0xF0u);
  memset(&this->m_bWPXS + 1259, 0, 0xF0u);
  this->m_Icon[0][0].m_fontcolor.Color = 0;
  this->m_Icon[0][0].m_wndcolor.Color = 0;
  LOWORD(this->m_Icon[0][0].m_id) = 0;
  bkHeight = this->bkHeight;
  this->m_sort[411][3] = (SaleUI_SortData)68;
  this->m_sort[411][4] = (SaleUI_SortData)(bkHeight / 4);
  this->m_sort[412][0] = (SaleUI_SortData)65;
  this->m_sort[412][1] = (SaleUI_SortData)86;
  *(&this->AttackNum + 285) = 0;
}

// 0x0045AE60
SaleUI::~SaleUI()
{
  void *m_needscriptdel; // eax

  m_needscriptdel = (void *)this->m_ListSaleTitle.m_childs.m_needscriptdel;
  if ( m_needscriptdel )
  {
    operator delete(m_needscriptdel);
    this->m_ListSaleTitle.m_childs.m_needscriptdel = 0;
  }
  if ( this->m_ListEquipTitleRc.bottom )
  {
    operator delete((void *)this->m_ListEquipTitleRc.bottom);
    this->m_ListEquipTitleRc.bottom = 0;
  }
  if ( *(_DWORD *)&this->remarkbuf[4] )
  {
    operator delete(*(void **)&this->remarkbuf[4]);
    *(_DWORD *)&this->remarkbuf[4] = 0;
  }
  if ( *(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) )
  {
    operator delete(*(void **)((UIWnd *)&this->m_Icon[0][0]));
    *(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) = 0;
  }
  this->remarkbuf[32] = 0;
  *((_BYTE *)&this->AttackNum + 1160) = 0;
  Destroy__ovl_03((int)this);
  (((UIFrameContainer *)(&this->AttackNum + 112)))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)(&this->AttackNum + 18)))->UICaption::Destroy2();
  (((UICaption *)&this->ml_AttackList.m_column[6].items.m_needscriptdel))->UICaption::Destroy2();
  (((UICaption *)&this->ml_AttackList.m_column[2].items.capacity))->UICaption::Destroy2();
  (((UICaption *)&this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14]))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->ml_TreasureList + 1276)))->UICaption::Destroy2();
  (((UICaption *)&this->ml_TreasureList.m_column[5].head[60]))->UICaption::Destroy2();
  (((UICaption *)&this->ml_TreasureList.m_column[1].head[36]))->UICaption::Destroy2();
  (((UICaption *)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize))->UICaption::Destroy2();
  (((UICaption *)&this->ml_ResumeList.m_locksel))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->ml_ResumeList.m_column[6].head[16]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->ml_ResumeList.m_column[4].head[16]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->ml_ResumeList.m_column[2].head[16]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->ml_ResumeList.m_column[0].head[16]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[7]))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)&this->m_ListGrid[14].m_bvisible))->UICaption::Destroy2();
  (((UICaption *)&this->m_ListGrid[12].m_rect))->UICaption::Destroy2();
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::DeleteRow();
  (((UIFrameContainer *)&this->m_ListGrid[2].m_disablepic))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_ListGrid[1].m_disablepic))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Icon[3][2].m_pbk))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Icon[3][1].m_ppicInfo))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)&this->m_Icon[2][4].m_mouseoff))->UICaption::Destroy2();
  (((UICaption *)&this->m_Icon[2][2].m_dstAlpha))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_Icon[2][1].m_fadespeed))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Icon[2][1].m_rect))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Icon[2][0].m_childs.m_nSize))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Icon[1][4].m_align))->UIFrameContainer::~UIFrameContainer();
  (((UIRoleDialog *)&this->m_Icon[0][1].m_FVF))->UIRoleDialog::~UIRoleDialog();
  (((PalScript *)&this->m_Icon[0][0].m_rect))->PalScript::Reset();
  (((PalScript *)&this->m_sort[361][2]))->PalScript::ctor();
  (((UIFrameContainer *)&this->m_sort[353][4]))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((UIFrameWnd *)&this->m_sort[349][3]);
  (((UIFrameContainer *)this->m_sort[342]))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x0045B7A0
unsigned __int8 SaleUI::LoadState(const void *arg0)
{
  char *v3; // ebx
  void *v4; // edi
  unsigned int v5; // edx
  int v6; // eax
  int **v7; // edi
  int ListItems; // ebx
  int *v9; // eax
  int v10; // ecx
  int *v11; // eax
  unsigned __int8 result; // al
  int v13; // [esp+0x10] [ebp-0x10]
  int p_DWORD; // [esp+0x14] [ebp-0xC] BYREF
  int v15; // [esp+0x18] [ebp-0x8]
  int *v16; // [esp+0x1C] [ebp-0x4]
  const void *arg0a; // [esp+0x24] [ebp+0x4]

  v3 = (char *)&this->remarkbuf[40];
  memset(&this->remarkbuf[40], 0, 0x4460u);
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::ClearAll();
  qmemcpy(v3, arg0, 0x4460u);
  if ( *(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) )
  {
    operator delete(*(void **)((UIWnd *)&this->m_Icon[0][0]));
    *(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) = 0;
  }
  v4 = (void *)operator new(4 * *(&this->dwWeaponWU + 3264));
  v5 = 4 * *(&this->dwWeaponWU + 3264);
  *(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) = (_DWORD)v4;
  memset(v4, 0, v5);
  v13 = 0;
  v6 = *(&this->dwWeaponWU + 3264);
  p_DWORD = 0xFFFF;
  v15 = 0;
  v16 = 0;
  if ( v6 > 0 )
  {
    v7 = (int **)(&this->dwWeaponWU + 3666);
    arg0a = (const void *)(-15880 - (_DWORD)this);
    do
    {
      sprintf(this->buf, "%s", *v7 + 1);
      ListItems = (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::LoadListItems(this->buf, 0);
      sprintf(this->buf, (const char *)&dir[20], (*v7)[152]);
      (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetMouseMoveSel(1, ListItems, this->buf, 0);
      sprintf(this->buf, (const char *)&dir[20], 0);
      (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetMouseMoveSel(2, ListItems, this->buf, 0);
      v9 = (int *)*v7;
      v10 = **v7;
      v15 = 1;
      p_DWORD = v10;
      v16 = (int *)v9;
      v11 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD);
      if ( v11 )
        *(int **)((char *)v7 + (_DWORD)arg0a + *(_DWORD *)((UIWnd *)&this->m_Icon[0][0])) = (int)(int *)(99 - v11[1]);
      else
        *(int **)((char *)v7 + (_DWORD)arg0a + *(_DWORD *)((UIWnd *)&this->m_Icon[0][0])) = (int)(int *)99;
      ++v7;
      ++v13;
    }
    while ( v13 < *(&this->dwWeaponWU + 3264) );
  }
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItem();
  result = this->remarkbuf[41];
  if ( !result )
  {
    sub_445E50((int)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize);
    result = (unsigned __int8)(((PalScript *)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnDicker.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  }
  *((_BYTE *)&this->AttackNum + 1160) = 1;
  return result;
}

// 0x0045B990
int SaleUI::InitCombatUI(int nVal)
{
  SaleUI_SortData *v3; // edi
  int bkHeight; // edx
  SaleUI_SortData v5; // eax
  SaleUI_SortData v6; // edx
  int v7; // edx
  SaleUI_SortData v8; // edx
  int v9; // edx
  gbTexture *m_pbk; // edx
  int v11; // edx
  gbTexture *m_disablepic; // edx
  gbTexture *v13; // eax
  int v14; // eax
  int v15; // ecx
  gbTexture *v16; // edx
  char *v17; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // ecx
  LONG left; // edx
  CHAR *v22; // ebp
  gbTexture *m_pbk2; // ecx
  unsigned int m_nTextW; // eax
  char *v25; // ebp
  gbTexture *v26; // eax
  int v27; // eax
  int v28; // edx
  int v29; // edx
  gbTexture *v30; // edx
  int v31; // edx
  SaleUI_SortData v32; // edx
  SaleUI_SortData v33; // eax
  SaleUI_SortData v34; // ecx
  int v35; // ecx
  int v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // edx
  int v41; // edx
  int v42; // edx
  int v43; // edx
  int v44; // edx
  int v45; // edx
  int v46; // edx
  int v47; // edx
  int v48; // edx
  int v49; // edx
  int v50; // edx
  int v51; // ecx
  int v52; // ecx
  int v53; // ecx
  SaleUI_SortData *v54; // ecx
  int v55; // ecx
  int v56; // ecx
  int v57; // ecx
  int v58; // ecx
  int v59; // ecx
  int v60; // ecx
  int v61; // ecx
  int v62; // ecx
  int v63; // ecx
  int v64; // ecx
  int v65; // ecx
  int v66; // ecx
  int v67; // ecx
  int v68; // ecx
  int v69; // ecx
  int *v70; // ecx
  int v71; // ecx
  int v72; // ecx
  int v73; // ecx
  int v74; // ecx
  int v75; // ecx
  int v76; // ecx
  int v77; // ecx
  int v78; // ecx
  int v79; // ecx
  int v80; // ecx
  int v81; // ecx
  int v82; // ecx
  SaleUI_SortData *v83; // ecx
  int v84; // ecx
  int v85; // ecx
  int v86; // ecx
  int v87; // ecx
  int v88; // ecx
  int v89; // ecx
  int v90; // ecx
  int v91; // ecx
  int v92; // ecx
  int v93; // ecx
  int v94; // ecx
  int v95; // ecx
  int v96; // ecx
  int v97; // ecx
  int v98; // ecx
  int *v99; // ecx
  int v100; // ecx
  int v101; // ecx
  int v102; // ecx
  int v103; // eax
  int m_align; // edx
  int v105; // edx
  int m_nSize; // edx
  int v107; // edx
  LONG v108; // edx
  int v109; // edx
  char *m_text; // ebp
  unsigned int v111; // eax
  int m_locksel; // edx
  int v113; // ecx
  LONG bottom; // edx
  char *v115; // eax
  int v116; // eax
  int v117; // eax
  int v118; // edx
  int v119; // edx
  int v120; // ecx
  int v121; // eax
  int v122; // ecx
  char *v123; // eax
  unsigned __int8 v124; // dl
  bool v125; // cf
  int v126; // eax
  int v127; // eax
  int v128; // eax
  gbTexture *v129; // edx
  int v130; // eax
  int v131; // eax
  int capacity; // edx
  int v133; // eax
  int v134; // eax
  int v135; // eax
  int v136; // eax
  int v137; // edx
  int v138; // eax
  int m_dstAlpha; // edx
  int v140; // eax
  int v141; // eax
  int v142; // eax
  int result; // eax
  CHAR *v144; // [esp+0x552] [ebp-0x100]
  CHAR *v145; // [esp+0x552] [ebp-0x100]
  _DWORD v146[4]; // [esp+0x566] [ebp-ECh] BYREF
  unsigned __int8 v147; // [esp+0x579] [ebp-D9h]
  CHAR *v148; // [esp+0x57A] [ebp-D8h]
  int v149; // [esp+0x57E] [ebp-D4h] BYREF
  int v150; // [esp+0x582] [ebp-D0h]
  int v151; // [esp+0x586] [ebp-CCh]
  int v152; // [esp+0x58A] [ebp-C8h]
  _DWORD v153[2]; // [esp+0x58E] [ebp-C4h] BYREF
  int v154; // [esp+0x596] [ebp-BCh]
  int v155; // [esp+0x59A] [ebp-B8h]
  char *v156; // [esp+0x59E] [ebp-B4h]
  gbTexture *m_ppic; // [esp+0x5A2] [ebp-B0h] BYREF
  char *v158; // [esp+0x5A6] [ebp-ACh]
  int *p_RefCount; // [esp+0x5AA] [ebp-A8h]
  char *v160; // [esp+0x5AE] [ebp-A4h]
  _DWORD v161[4]; // [esp+0x5B2] [ebp-A0h] BYREF
  gbVec3D pDir; // [esp+0x5C2] [ebp-0x90] BYREF
  int v163; // [esp+0x5CE] [ebp-0x84]
  _DWORD v164[4]; // [esp+0x5D2] [ebp-0x80] BYREF
  gbVec3D pPos; // [esp+0x5E2] [ebp-0x70] BYREF
  int v166; // [esp+0x5EE] [ebp-0x64]
  _DWORD v167[4]; // [esp+0x5F2] [ebp-0x60] BYREF
  _DWORD v168[4]; // [esp+0x602] [ebp-0x50] BYREF
  _DWORD v169[4]; // [esp+0x612] [ebp-0x40] BYREF
  _DWORD v170[4]; // [esp+0x622] [ebp-0x30] BYREF
  _DWORD v171[8]; // [esp+0x632] [ebp-0x20] BYREF

  v3 = (SaleUI_SortData *)&this->m_sort[341][1];
  this->m_sort[341][2] = 0;
  this->m_sort[341][1] = 0;
  this->m_sort[341][3] = (SaleUI_SortData)800;
  this->m_sort[341][4] = (SaleUI_SortData)600;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, *(_DWORD *)&this->m_sort[341][1], *(_DWORD *)&this->m_sort[341][2], *(_DWORD *)&this->m_sort[341][3], *(_DWORD *)&this->m_sort[341][4]) /* [ROWTABLE] */;
  *(&this->AttackNum + 289) = nVal;
  this->m_sort[341][2] = 0;
  *v3 = 0;
  bkHeight = this->bkHeight;
  v5 = this->m_sort[341][2];
  v164[1] = 22;
  v164[0] = 266;
  this->m_sort[341][4] = (SaleUI_SortData)(*(_DWORD *)&v5 + bkHeight);
  this->m_sort[341][3] = (SaleUI_SortData)(*(_DWORD *)v3 + this->bkWidth);
  v6 = this->m_sort[353][4];
  v164[2] = 482;
  v164[3] = 150;
  (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&v6 + 16))(
    &this->m_sort[353][4],
    257,
    (_DWORD *)(v164),
    this);
  LOBYTE(v7) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
  (((UIPushButton *)&this->m_sort[353][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\BuyFlag.tga", v7);
  v8 = this->m_sort[349][3];
  v161[1] = 564;
  v161[0] = 0;
  v161[2] = 800;
  v161[3] = 599;
  (*(void ( **)(SaleUI_SortData *, int, _DWORD *, char *, _DWORD, SaleUI *))(*(_DWORD *)&v8 + 28))(
    &this->m_sort[349][3],
    257,
    (_DWORD *)(v161),
    "UI\\Flex\\framebar.tga",
    0,
    this);
  (((CScreenMode *)&this->m_sort[349][3]))->CScreenMode::SetPosition(30,   35);
  v169[1] = 0;
  v169[0] = 0;
  v169[2] = 206;
  v169[3] = 600;
  (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[342][0] + 16))(
    this->m_sort[342],
    257,
    (_DWORD *)(v169),
    this);
  LOBYTE(v9) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
  (((UIPushButton *)this->m_sort[342]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\Frame.tga", v9);
  m_pbk = this->m_Icon[3][2].m_pbk;
  v167[1] = 32;
  v167[0] = 454;
  v167[2] = 790;
  v167[3] = 425;
  ((void ( *)(gbTexture **, int, _DWORD *, SaleUI *))m_pbk->IsLoaded)(
    &this->m_Icon[3][2].m_pbk,
    257,
    v167,
    this);
  LOBYTE(v11) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
  (((UIPushButton *)&this->m_Icon[3][2].m_pbk))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ListFrame.tga", v11);
  m_disablepic = (gbTexture *)this->m_ListGrid[2].m_disablepic;
  v171[1] = 50;
  v171[0] = 476;
  v171[2] = 782;
  v171[3] = 82;
  ((void ( *)(gbTexture **, int, _DWORD *, SaleUI *))m_disablepic->IsLoaded)(
    &this->m_ListGrid[2].m_disablepic,
    294,
    v171,
    this);
  (((UIScene *)&this->m_ListGrid[2].m_disablepic))->UIScene::SetShow(0);
  sprintf(
    this->buf,
    "%s                %s   %s",
    (const char *)&dword_DC353C,
    (const char *)&dword_DC363C,
    (const char *)&dword_DC373C);
  SetEnable((UICaption *)&this->m_ListGrid[2].m_disablepic);
  this->m_ListGrid[11].m_ppicInfo = (_PlugInfo *)79;
  this->m_ListGrid[11].m_ppic = (gbTexture *)476;
  this->m_ListGrid[11].m_disablepic = (gbTexture *)769;
  this->m_ListGrid[11].m_disablepicInfo = (_PlugInfo *)&this->m_ListGrid[11].m_ppicInfo->libName[18];
  v13 = (gbTexture *)this->m_ListGrid[11].m_disablepic;
  LODWORD(pPos.y) = (unsigned long)&this->m_ListGrid[11].m_ppicInfo->name[11];
  LODWORD(pPos.x) = (unsigned long)((char *)&v13[-1].InFmt.g_mask + 1);
  v166 = LODWORD(pPos.y) + 26;
  LODWORD(pPos.z) = (unsigned long)((char *)&v13[-1].InFmt.b_shift + 3);
  LODWORD(pDir.y) = LODWORD(pPos.y) + 253;
  LODWORD(pDir.x) = (unsigned long)((char *)&v13[-1].InFmt.g_mask + 1);
  v14 = *(&this->AttackNum + 289);
  v15 = LODWORD(pPos.y) + 279;
  pDir.z = pPos.z;
  v16 = (gbTexture *)this->m_ListGrid[3].m_disablepic;
  v163 = LODWORD(pPos.y) + 279;
  LOBYTE(v15) = *(_BYTE *)(v14 + 3284);
  ((void ( *)(gbTexture **, int, gbTexture **, SaleUI *, _DWORD, int, int))v16->Height)(
    &this->m_ListGrid[3].m_disablepic,
    259,
    &this->m_ListGrid[11].m_ppic,
    this,
    0,
    1,
    v15);
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetLockSel(23);
  this->m_ListGrid[11].m_align = -4;
  this->m_ListGrid[11].m_ratiow = NAN;
  LODWORD(this->m_ListGrid[11].m_ratioh) = 10;
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->m_ListGrid[11].m_ppic, 38, 27, 0);
  (((CCBUI *)&this->m_ListGrid[4].m_bvisible))->CCBUI::ShowEffect((int)&this->m_ListGrid[11].m_ppicInfo->filepos + 1, (int)&this->m_ListGrid[11].m_disablepic[-1].InFmt.Pal + 2, (int)this->m_ListGrid[11].m_disablepic);
  (((CCBUI *)&this->m_ListGrid[4].m_bvisible))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&this->m_ListGrid[4].m_bvisible))->CCBUI::SetSelection(27);
  (((CCBUI *)&this->m_ListGrid[4].m_bvisible))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetColumnHead((int)"Name", 168);
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetColumnHead((int)"Price", 51);
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetColumnHead((int)"Num1", 38);
  (((CCBUI *)&this->m_ListGrid[4].m_bvisible))->CCBUI::VirtualCall(1);
  v17 = (char *)&this->m_ListGrid[11].m_ppicInfo->filepos + 2;
  m_ppic = (gbTexture *)this->m_ListGrid[11].m_ppic;
  v158 = (char *)v17;
  p_RefCount = (int *)&m_ppic[3].RefCount;
  v160 = (char *)(v17 + 23);
  *(_DWORD *)&this->remarkbuf[20] = 0;
  do
  {
    (*(void ( **)(void **, int, gbTexture **, SaleUI *))(*((_DWORD *)&this->m_Icon[3][3].m_textx
                                                                   + 38 * *(_DWORD *)&this->remarkbuf[20])
                                                                 + 16))(
      &this->m_Icon[3][3].m_textx + 38 * *(_DWORD *)&this->remarkbuf[20],
      257,
      &m_ppic,
      this);
    LOBYTE(v18) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)(&this->m_Icon[3][3].m_textx + 38 * *(_DWORD *)&this->remarkbuf[20])))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\Buy_Grid.tga", v18);
    v19 = *(_DWORD *)&this->remarkbuf[20];
    v158 = (char *)v160;
    v160 += 23;
    *(_DWORD *)&this->remarkbuf[20] = v19 + 1;
  }
  while ( v19 + 1 < 13 );
  *(&this->AttackNum + 109) = 0;
  *(&this->AttackNum + 108) = 0;
  *(&this->AttackNum + 110) = 90;
  *(&this->AttackNum + 111) = *(&this->AttackNum + 109) + 32;
  (*(void ( **)(int *, int, int *, SaleUI *))(*(&this->AttackNum + 112) + 16))(
    &this->AttackNum + 112,
    513,
    &this->AttackNum + 108,
    this);
  (((UIScene *)(&this->AttackNum + 112)))->UIScene::SetShow(0);
  (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
  v20 = *(&this->AttackNum + 289);
  v156 = (char *)"UI\\Assistant\\Communal\\Add";
  LOBYTE(v148) = *(_BYTE *)(v20 + 3284);
  left = this->m_ListGrid[12].m_rect.left;
  v22 = (CHAR *)v148;
  v144 = (CHAR *)v148;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[0] = (gbTexture *)24;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[1] = (gbTexture *)40;
  *(_DWORD *)&this->m_ListGrid[11].m_mouseoff = 158;
  this->m_ListGrid[11].m_pbk2 = (gbTexture *)476;
  this->m_ListGrid[11].m_FVF = 500;
  this->m_ListGrid[11].m_nTextW = 198;
  (*(void ( **)(tagRECT *, int, gbTexture **, SaleUI *, char *, _DWORD, CHAR *))(left + 28))(
    &this->m_ListGrid[12].m_rect,
    405,
    &this->m_ListGrid[11].m_pbk2,
    this,
    "UI\\Assistant\\Communal\\Sub",
    0,
    v144);
  m_pbk2 = (gbTexture *)this->m_ListGrid[11].m_pbk2;
  m_nTextW = this->m_ListGrid[11].m_nTextW;
  this->m_ListGrid[12].m_fontcolor.Color = m_nTextW;
  v145 = (CHAR *)v22;
  v25 = (char *)v156;
  *(_DWORD *)((UIWnd *)&this->m_ListGrid[12]) = (_DWORD)m_pbk2;
  this->m_ListGrid[12].m_wndcolor.Color = this->m_ListGrid[11].m_FVF;
  this->m_ListGrid[12].m_id = (unsigned int)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[1] + m_nTextW;
  (*(void ( **)(int, UIStatic *, SaleUI *, char *, _DWORD, CHAR *))(this->m_ListGrid[14].m_bvisible + 28))(
    406,
    &this->m_ListGrid[12],
    this,
    v25,
    0,
    v145);
  LOBYTE(this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[4]) = (_BYTE)v148;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[2] = (gbTexture *)1;
  (((PalScript *)&this->m_ListGrid[12].m_rect))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnSub.tga", (char)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[4]);
  (((PalScript *)&this->m_ListGrid[14].m_bvisible))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnAdd.tga", (char)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[4]);
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[3] = (gbTexture *)20;
  (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 0);
  (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
    &this->m_ListGrid[14].m_bvisible,
    0);
  v26 = (gbTexture *)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[7];
  v150 = 142;
  v149 = 218;
  v151 = 450;
  v152 = 556;
  v27 = ((int ( *)(gbTexture **, int, int *, SaleUI *))v26->IsLoaded)(
          &this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[7],
          161,
          &v149,
          this);
  LOBYTE(v27) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
  (((UIPushButton *)&this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[7]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Info.tga", v27);
  v28 = *(_DWORD *)&this->ml_ResumeList.m_column[0].head[16];
  v150 = 388;
  v149 = 232;
  v151 = 444;
  v152 = 556;
  (*(void ( **)(char *, int, int *, SaleUI *))(v28 + 16))(
    &this->ml_ResumeList.m_column[0].head[16],
    161,
    &v149,
    this);
  (((UIScene *)&this->ml_ResumeList.m_column[0].head[16]))->UIScene::SetShow(0);
  v29 = *(_DWORD *)&this->ml_ResumeList.m_column[2].head[16];
  v150 = 520;
  v149 = 232;
  v151 = 444;
  v152 = 552;
  (*(void ( **)(char *, int, int *, SaleUI *))(v29 + 16))(
    &this->ml_ResumeList.m_column[2].head[16],
    161,
    &v149,
    this);
  (((UIScene *)&this->ml_ResumeList.m_column[2].head[16]))->UIScene::SetShow(0);
  v30 = (gbTexture *)this->m_ListGrid[1].m_disablepic;
  v168[1] = 158;
  v168[0] = 404;
  v168[2] = 420;
  v168[3] = 190;
  ((void ( *)(gbTexture **, int, _DWORD *, SaleUI *))v30->IsLoaded)(
    &this->m_ListGrid[1].m_disablepic,
    257,
    v168,
    this);
  LOBYTE(v31) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
  (((UIPushButton *)&this->m_ListGrid[1].m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Equip_word.tga", v31);
  *(_DWORD *)&this->ml_ResumeList.m_column[6].head[4] = 392;
  *(_DWORD *)this->ml_ResumeList.m_column[6].head = 478;
  *(_DWORD *)&this->ml_ResumeList.m_column[6].head[8] = 624;
  *(_DWORD *)&this->ml_ResumeList.m_column[6].head[12] = *(_DWORD *)&this->ml_ResumeList.m_column[6].head[4] + 32;
  (*(void ( **)(char *, int, UILBColumn *, SaleUI *))(*(_DWORD *)&this->ml_ResumeList.m_column[4].head[16] + 16))(
    &this->ml_ResumeList.m_column[4].head[16],
    272,
    &this->ml_ResumeList.m_column[6],
    this);
  (((UIScene *)&this->ml_ResumeList.m_column[4].head[16]))->UIScene::SetShow(0);
  sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)&this->ml_ResumeList.m_column[4].head[16]);
  this->ml_ResumeList.m_fontsize = 392;
  this->ml_ResumeList.m_itemheight = 638;
  this->ml_ResumeList.m_firstshow = 764;
  this->ml_ResumeList.m_onsel = this->ml_ResumeList.m_fontsize + 32;
  (*(void ( **)(char *, int, int *, SaleUI *))(*(_DWORD *)&this->ml_ResumeList.m_column[6].head[16]
                                                                  + 16))(
    &this->ml_ResumeList.m_column[6].head[16],
    261,
    &this->ml_ResumeList.m_itemheight,
    this);
  (((UIScene *)&this->ml_ResumeList.m_column[6].head[16]))->UIScene::SetShow(0);
  sprintf(this->buf, "%s %d", g_szCombatFieldName, *(_DWORD *)&this->remarkbuf[16]);
  SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
  *(_DWORD *)&this->remarkbuf[20] = 0;
  do
  {
    v32 = this->m_sort[412][0];
    v33 = this->m_sort[411][4];
    v146[0] = this->m_sort[411][3];
    v34 = this->m_sort[412][1];
    v146[1] = v33;
    v35 = *(_DWORD *)&v33 + *(_DWORD *)&v34;
    v36 = *(_DWORD *)&this->remarkbuf[20];
    v146[2] = v146[0] + *(_DWORD *)&v32;
    v146[3] = v35;
    (*(void ( **)(SaleUI_SortData *, _DWORD, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[369][38 * v36 + 3]
                                                                          + 16))(
      &this->m_sort[369][38 * v36 + 3],
      *(&dword_56B3C8 + v36),
      (_DWORD *)(v146),
      this);
    LOBYTE(v37) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[369][38 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate((void *)(0x56B43C)[*(_DWORD *)&this->remarkbuf[20]], v37);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[369][38 * *(_DWORD *)&this->remarkbuf[20] + 3])((SaleUI_SortData *)(&this->m_sort[369][38 * *(_DWORD *)&this->remarkbuf[20] + 3]), (_DWORD)(0));
    v38 = *(_DWORD *)&this->remarkbuf[20] + 1;
    *(_DWORD *)&this->remarkbuf[20] = v38;
  }
  while ( v38 < 5 );
  *(_DWORD *)&this->remarkbuf[20] = 0;
  do
  {
    (*(void ( **)(int *, _DWORD, _DWORD *, SaleUI *))(this->m_NotesNull[54
                                                                                           * *(_DWORD *)&this->remarkbuf[20]
                                                                                           + 277][4]
                                                                         + 16))(
      &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][4],
      *(&dword_56B4DC + *(_DWORD *)&this->remarkbuf[20]),
      (_DWORD *)(v146),
      this);
    LOBYTE(v39) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Cloth.tga", v39);
    this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][1] = *(int *)&this->remarkbuf[36];
    this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][3] = 1;
    (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][4])(
      &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][4],
      0);
    ((void ( *)(Parent_Data **, _DWORD, _DWORD *, SaleUI *))this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20]
                                                                                 + 2].m_fonttype[4])(
      &this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 2].m_fonttype,
      *(&dword_56B554 + *(_DWORD *)&this->remarkbuf[20]),
      v146,
      this);
    LOBYTE(v40) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 2].m_fonttype))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Cloth_small.tga", v40);
    (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 2].m_fonttype)(
      &this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 2].m_fonttype,
      0);
    (*(void ( **)(int *, _DWORD, _DWORD *, SaleUI *))(this->m_NotesNull[54
                                                                                           * *(_DWORD *)&this->remarkbuf[20]
                                                                                           + 286][4]
                                                                         + 16))(
      &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][4],
      *(&dword_56B540 + *(_DWORD *)&this->remarkbuf[20]),
      (_DWORD *)(v146),
      this);
    LOBYTE(v41) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Weapon.tga", v41);
    this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 295][1] = *(int *)&this->remarkbuf[36];
    this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 295][3] = 1;
    (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][4])(
      &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][4],
      0);
    ((void ( *)(Parent_Data **, _DWORD, _DWORD *, SaleUI *))this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20]
                                                                                 + 3].m_fonttype[4])(
      &this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 3].m_fonttype,
      *(&dword_56B5B8 + *(_DWORD *)&this->remarkbuf[20]),
      v146,
      this);
    LOBYTE(v42) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 3].m_fonttype))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Weapon_small.tga", v42);
    (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 3].m_fonttype)(
      &this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 3].m_fonttype,
      0);
    (*(void ( **)(int *, const char *, _DWORD *, SaleUI *))(this->m_NotesNull[54
                                                                                                 * *(_DWORD *)&this->remarkbuf[20]
                                                                                                 + 295][4]
                                                                               + 16))(
      &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 295][4],
      (&off_56B518)[*(_DWORD *)&this->remarkbuf[20]],
      (_DWORD *)(v146),
      this);
    LOBYTE(v43) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 295][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn.tga", v43);
    *(float *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 20][4] = *(float *)&this->remarkbuf[36];
    *(_DWORD *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 22][2] = 1;
    (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 295][4])(
      &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 295][4],
      0);
    ((void ( *)(Parent_Data **, _DWORD, _DWORD *, SaleUI *))this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20]
                                                                                 + 4].m_fonttype[4])(
      &this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 4].m_fonttype,
      *(&dword_56B590 + *(_DWORD *)&this->remarkbuf[20]),
      v146,
      this);
    LOBYTE(v44) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 4].m_fonttype))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn_small.tga", v44);
    (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 4].m_fonttype)(
      &this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 4].m_fonttype,
      0);
    (*(void ( **)(_BYTE *, _DWORD, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_IsEquip[216
                                                                                            * *(_DWORD *)&this->remarkbuf[20]
                                                                                            + 23][1]
                                                                + 16))(
      &this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 23][1],
      *(&dword_56B4F0 + *(_DWORD *)&this->remarkbuf[20]),
      (_DWORD *)(v146),
      this);
    LOBYTE(v45) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 23][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Hat.tga", v45);
    *(float *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 56][4] = *(float *)&this->remarkbuf[36];
    *(_DWORD *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 58][2] = 1;
    (**(void ( ***)(_BYTE *, _DWORD))&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 23][1])((_BYTE *)(&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 23][1]), (_DWORD)(0));
    (*(void ( **)(LONG *, _DWORD, _DWORD *, SaleUI *))(this->m_RoleRc[57 * *(_DWORD *)&this->remarkbuf[20] + 3].top
                                                               + 16))(
      &this->m_RoleRc[57 * *(_DWORD *)&this->remarkbuf[20] + 3].top,
      *(&dword_56B568 + *(_DWORD *)&this->remarkbuf[20]),
      (_DWORD *)(v146),
      this);
    LOBYTE(v46) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_RoleRc[57 * *(_DWORD *)&this->remarkbuf[20] + 3].top))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Hat_small.tga", v46);
    (*(void ( **)(LONG *, _DWORD))this->m_RoleRc[57 * *(_DWORD *)&this->remarkbuf[20] + 3].top)(
      &this->m_RoleRc[57 * *(_DWORD *)&this->remarkbuf[20] + 3].top,
      0);
    (*(void ( **)(_BYTE *, const char *, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 59][1]
                                                                      + 16))(
      &this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 59][1],
      (&off_56B504)[*(_DWORD *)&this->remarkbuf[20]],
      (_DWORD *)(v146),
      this);
    LOBYTE(v47) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 59][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Shoes.tga", v47);
    *(float *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 92][4] = *(float *)&this->remarkbuf[36];
    *(_DWORD *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 94][2] = 1;
    (**(void ( ***)(_BYTE *, _DWORD))&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 59][1])((_BYTE *)(&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 59][1]), (_DWORD)(0));
    (*(void ( **)(LONG *, _DWORD, _DWORD *, SaleUI *))(*(&this->m_Msg.m_textRc.top
                                                                 + 228 * *(_DWORD *)&this->remarkbuf[20])
                                                               + 16))(
      &this->m_Msg.m_textRc.top + 228 * *(_DWORD *)&this->remarkbuf[20],
      *(&dword_56B57C + *(_DWORD *)&this->remarkbuf[20]),
      (_DWORD *)(v146),
      this);
    LOBYTE(v48) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)(&this->m_Msg.m_textRc.top + 228 * *(_DWORD *)&this->remarkbuf[20])))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Shoes_small.tga", v48);
    (**((void ( ***)(LONG *, _DWORD))&this->m_Msg.m_textRc.top + 228 * *(_DWORD *)&this->remarkbuf[20]))((LONG *)(&this->m_Msg.m_textRc.top + 228 * *(_DWORD *)&this->remarkbuf[20]), (_DWORD)(0));
    (*(void ( **)(_BYTE *, const char *, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 95][1]
                                                                      + 16))(
      &this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 95][1],
      (&off_56B52C)[*(_DWORD *)&this->remarkbuf[20]],
      (_DWORD *)(v146),
      this);
    LOBYTE(v49) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 95][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn.tga", v49);
    *(float *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 128][4] = *(float *)&this->remarkbuf[36];
    *(_DWORD *)&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 130][2] = 1;
    (**(void ( ***)(_BYTE *, _DWORD))&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 95][1])((_BYTE *)(&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 95][1]), (_DWORD)(0));
    ((void ( *)(gbTexture **, _DWORD, _DWORD *, SaleUI *))this->m_Msg.m_bk.m_texs.m_ptex[228
                                                                                                 * *(_DWORD *)&this->remarkbuf[20]
                                                                                                 + 14]->IsLoaded)(
      &this->m_Msg.m_bk.m_texs.m_ptex[228 * *(_DWORD *)&this->remarkbuf[20] + 14],
      *(&dword_56B5A4 + *(_DWORD *)&this->remarkbuf[20]),
      v146,
      this);
    LOBYTE(v50) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_Msg.m_bk.m_texs.m_ptex[228 * *(_DWORD *)&this->remarkbuf[20] + 14]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn_small.tga", v50);
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_Msg.m_bk.m_texs.m_ptex[228 * *(_DWORD *)&this->remarkbuf[20]
                                                                             + 14]))(
      &this->m_Msg.m_bk.m_texs.m_ptex[228 * *(_DWORD *)&this->remarkbuf[20] + 14],
      0);
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]
                                                                       + 16))(
      &this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v51) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_up.tga", v51);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])((SaleUI_SortData *)(&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[420][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]
                                                                       + 16))(
      &this->m_sort[420][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v52) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[420][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_up.tga", v52);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[420][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])((SaleUI_SortData *)(&this->m_sort[420][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[428][1824 * *(_DWORD *)&this->remarkbuf[20]]
                                                                       + 16))(
      &this->m_sort[428][1824 * *(_DWORD *)&this->remarkbuf[20]],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v53) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[428][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_up.tga", v53);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[428][1824 * *(_DWORD *)&this->remarkbuf[20]])((SaleUI_SortData *)(&this->m_sort[428][1824 * *(_DWORD *)&this->remarkbuf[20]]), (_DWORD)(0));
    v54 = (SaleUI_SortData *)&this->m_sort[435][1824 * *(_DWORD *)&this->remarkbuf[20] + 3];
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)v54 + 16))(v54, 295, (_DWORD *)(v146), this);
    LOBYTE(v55) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[435][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_up.tga", v55);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[435][1824 * *(_DWORD *)&this->remarkbuf[20] + 3])((SaleUI_SortData *)(&this->m_sort[435][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[473][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]
                                                                       + 16))(
      &this->m_sort[473][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v56) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[473][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_up.tga", v56);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[473][1824 * *(_DWORD *)&this->remarkbuf[20] + 3])((SaleUI_SortData *)(&this->m_sort[473][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]
                                                                       + 16))(
      &this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v57) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_up.tga", v57);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1])((SaleUI_SortData *)(&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[488][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]
                                                                       + 16))(
      &this->m_sort[488][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v58) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[488][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_up.tga", v58);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[488][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])((SaleUI_SortData *)(&this->m_sort[488][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]
                                                                       + 16))(
      &this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v59) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_up.tga", v59);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])((SaleUI_SortData *)(&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[534][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]
                                                                       + 16))(
      &this->m_sort[534][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v60) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[534][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_up.tga", v60);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[534][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])((SaleUI_SortData *)(&this->m_sort[534][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[542][1824 * *(_DWORD *)&this->remarkbuf[20]]
                                                                       + 16))(
      &this->m_sort[542][1824 * *(_DWORD *)&this->remarkbuf[20]],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v61) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[542][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_up.tga", v61);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[542][1824 * *(_DWORD *)&this->remarkbuf[20]])((SaleUI_SortData *)(&this->m_sort[542][1824 * *(_DWORD *)&this->remarkbuf[20]]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[549][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]
                                                                       + 16))(
      &this->m_sort[549][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v62) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[549][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_up.tga", v62);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[549][1824 * *(_DWORD *)&this->remarkbuf[20] + 3])((SaleUI_SortData *)(&this->m_sort[549][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[557][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]
                                                                       + 16))(
      &this->m_sort[557][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v63) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[557][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_up.tga", v63);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[557][1824 * *(_DWORD *)&this->remarkbuf[20] + 1])((SaleUI_SortData *)(&this->m_sort[557][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[595][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]
                                                                       + 16))(
      &this->m_sort[595][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v64) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[595][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_up.tga", v64);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[595][1824 * *(_DWORD *)&this->remarkbuf[20] + 1])((SaleUI_SortData *)(&this->m_sort[595][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]), (_DWORD)(0));
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[4][1824
                                                                                            * *(_DWORD *)&this->remarkbuf[20]
                                                                                            + 4]
                                                                      + 16))(
      &this->m_ListSelNum[4][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v65) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[4][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_up.tga", v65);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[4][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])(
      &this->m_ListSelNum[4][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[12][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 2]
                                                                      + 16))(
      &this->m_ListSelNum[12][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v66) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[12][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_up.tga", v66);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[12][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])(
      &this->m_ListSelNum[12][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[20][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]]
                                                                      + 16))(
      &this->m_ListSelNum[20][1824 * *(_DWORD *)&this->remarkbuf[20]],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v67) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[20][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_up.tga", v67);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[20][1824 * *(_DWORD *)&this->remarkbuf[20]])(
      &this->m_ListSelNum[20][1824 * *(_DWORD *)&this->remarkbuf[20]],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[58][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]]
                                                                      + 16))(
      &this->m_ListSelNum[58][1824 * *(_DWORD *)&this->remarkbuf[20]],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v68) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[58][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_up.tga", v68);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[58][1824 * *(_DWORD *)&this->remarkbuf[20]])(
      &this->m_ListSelNum[58][1824 * *(_DWORD *)&this->remarkbuf[20]],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[65][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 3]
                                                                      + 16))(
      &this->m_ListSelNum[65][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v69) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[65][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_up.tga", v69);
    v70 = (int *)&this->m_ListSelNum[65][1824 * *(_DWORD *)&this->remarkbuf[20] + 3];
    (*(void ( **)(int *, _DWORD))*v70)(v70, 0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[73][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 1]
                                                                      + 16))(
      &this->m_ListSelNum[73][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v71) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[73][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_up.tga", v71);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[73][1824 * *(_DWORD *)&this->remarkbuf[20] + 1])(
      &this->m_ListSelNum[73][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[80][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 4]
                                                                      + 16))(
      &this->m_ListSelNum[80][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v72) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[80][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_up.tga", v72);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[80][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])(
      &this->m_ListSelNum[80][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[118][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]
                                                                                              + 4]
                                                                      + 16))(
      &this->m_ListSelNum[118][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v73) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[118][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_up.tga", v73);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[118][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])(
      &this->m_ListSelNum[118][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[126][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]
                                                                                              + 2]
                                                                      + 16))(
      &this->m_ListSelNum[126][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v74) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[126][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_up.tga", v74);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[126][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])(
      &this->m_ListSelNum[126][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[134][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]]
                                                                      + 16))(
      &this->m_ListSelNum[134][1824 * *(_DWORD *)&this->remarkbuf[20]],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v75) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[134][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_up.tga", v75);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[134][1824 * *(_DWORD *)&this->remarkbuf[20]])(
      &this->m_ListSelNum[134][1824 * *(_DWORD *)&this->remarkbuf[20]],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[141][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]
                                                                                              + 3]
                                                                      + 16))(
      &this->m_ListSelNum[141][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      295,
      (_DWORD *)(v146),
      this);
    LOBYTE(v76) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[141][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_up.tga", v76);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[141][1824 * *(_DWORD *)&this->remarkbuf[20] + 3])(
      &this->m_ListSelNum[141][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      0);
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[443][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]
                                                                       + 16))(
      &this->m_sort[443][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v77) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[443][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_down.tga", v77);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[443][1824 * *(_DWORD *)&this->remarkbuf[20] + 1])((SaleUI_SortData *)(&this->m_sort[443][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[450][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]
                                                                       + 16))(
      &this->m_sort[450][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v78) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[450][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_down.tga", v78);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[450][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])((SaleUI_SortData *)(&this->m_sort[450][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[458][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]
                                                                       + 16))(
      &this->m_sort[458][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v79) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[458][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_down.tga", v79);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[458][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])((SaleUI_SortData *)(&this->m_sort[458][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[466][1824 * *(_DWORD *)&this->remarkbuf[20]]
                                                                       + 16))(
      &this->m_sort[466][1824 * *(_DWORD *)&this->remarkbuf[20]],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v80) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[466][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_down.tga", v80);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[466][1824 * *(_DWORD *)&this->remarkbuf[20]])((SaleUI_SortData *)(&this->m_sort[466][1824 * *(_DWORD *)&this->remarkbuf[20]]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[504][1824 * *(_DWORD *)&this->remarkbuf[20]]
                                                                       + 16))(
      &this->m_sort[504][1824 * *(_DWORD *)&this->remarkbuf[20]],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v81) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[504][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_down.tga", v81);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[504][1824 * *(_DWORD *)&this->remarkbuf[20]])((SaleUI_SortData *)(&this->m_sort[504][1824 * *(_DWORD *)&this->remarkbuf[20]]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[511][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]
                                                                       + 16))(
      &this->m_sort[511][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v82) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[511][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_down.tga", v82);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[511][1824 * *(_DWORD *)&this->remarkbuf[20] + 3])((SaleUI_SortData *)(&this->m_sort[511][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]), (_DWORD)(0));
    v83 = (SaleUI_SortData *)&this->m_sort[519][1824 * *(_DWORD *)&this->remarkbuf[20] + 1];
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)v83 + 16))(v83, 296, (_DWORD *)(v146), this);
    LOBYTE(v84) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[519][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_down.tga", v84);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[519][1824 * *(_DWORD *)&this->remarkbuf[20] + 1])((SaleUI_SortData *)(&this->m_sort[519][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]
                                                                       + 16))(
      &this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v85) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_down.tga", v85);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])((SaleUI_SortData *)(&this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[564][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]
                                                                       + 16))(
      &this->m_sort[564][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v86) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[564][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_down.tga", v86);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[564][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])((SaleUI_SortData *)(&this->m_sort[564][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[572][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]
                                                                       + 16))(
      &this->m_sort[572][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v87) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[572][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_down.tga", v87);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[572][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])((SaleUI_SortData *)(&this->m_sort[572][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[580][1824 * *(_DWORD *)&this->remarkbuf[20]]
                                                                       + 16))(
      &this->m_sort[580][1824 * *(_DWORD *)&this->remarkbuf[20]],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v88) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[580][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_down.tga", v88);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[580][1824 * *(_DWORD *)&this->remarkbuf[20]])((SaleUI_SortData *)(&this->m_sort[580][1824 * *(_DWORD *)&this->remarkbuf[20]]), (_DWORD)(0));
    (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[587][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]
                                                                       + 16))(
      &this->m_sort[587][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v89) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_sort[587][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_down.tga", v89);
    (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[587][1824 * *(_DWORD *)&this->remarkbuf[20] + 3])((SaleUI_SortData *)(&this->m_sort[587][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]), (_DWORD)(0));
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[27][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 3]
                                                                      + 16))(
      &this->m_ListSelNum[27][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v90) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[27][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_down.tga", v90);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[27][1824 * *(_DWORD *)&this->remarkbuf[20] + 3])(
      &this->m_ListSelNum[27][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[35][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 1]
                                                                      + 16))(
      &this->m_ListSelNum[35][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v91) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[35][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_down.tga", v91);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[35][1824 * *(_DWORD *)&this->remarkbuf[20] + 1])(
      &this->m_ListSelNum[35][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[42][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 4]
                                                                      + 16))(
      &this->m_ListSelNum[42][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v92) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[42][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_down.tga", v92);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[42][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])(
      &this->m_ListSelNum[42][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[50][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 2]
                                                                      + 16))(
      &this->m_ListSelNum[50][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v93) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[50][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_down.tga", v93);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[50][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])(
      &this->m_ListSelNum[50][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[88][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]
                                                                                             + 2]
                                                                      + 16))(
      &this->m_ListSelNum[88][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v94) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[88][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_down.tga", v94);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[88][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])(
      &this->m_ListSelNum[88][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[96][1824
                                                                                             * *(_DWORD *)&this->remarkbuf[20]]
                                                                      + 16))(
      &this->m_ListSelNum[96][1824 * *(_DWORD *)&this->remarkbuf[20]],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v95) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[96][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_down.tga", v95);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[96][1824 * *(_DWORD *)&this->remarkbuf[20]])(
      &this->m_ListSelNum[96][1824 * *(_DWORD *)&this->remarkbuf[20]],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[103][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]
                                                                                              + 3]
                                                                      + 16))(
      &this->m_ListSelNum[103][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v96) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[103][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_down.tga", v96);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[103][1824 * *(_DWORD *)&this->remarkbuf[20] + 3])(
      &this->m_ListSelNum[103][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[111][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]
                                                                                              + 1]
                                                                      + 16))(
      &this->m_ListSelNum[111][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v97) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[111][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_down.tga", v97);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[111][1824 * *(_DWORD *)&this->remarkbuf[20] + 1])(
      &this->m_ListSelNum[111][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[149][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]
                                                                                              + 1]
                                                                      + 16))(
      &this->m_ListSelNum[149][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v98) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[149][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\W_down.tga", v98);
    v99 = (int *)&this->m_ListSelNum[149][1824 * *(_DWORD *)&this->remarkbuf[20] + 1];
    (*(void ( **)(int *, _DWORD))*v99)(v99, 0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[156][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]
                                                                                              + 4]
                                                                      + 16))(
      &this->m_ListSelNum[156][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v100) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[156][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\S_down.tga", v100);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[156][1824 * *(_DWORD *)&this->remarkbuf[20] + 4])(
      &this->m_ListSelNum[156][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[164][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]
                                                                                              + 2]
                                                                      + 16))(
      &this->m_ListSelNum[164][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v101) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[164][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\F_down.tga", v101);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[164][1824 * *(_DWORD *)&this->remarkbuf[20] + 2])(
      &this->m_ListSelNum[164][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
      0);
    (*(void ( **)(int *, int, _DWORD *, SaleUI *))(this->m_ListSelNum[172][1824
                                                                                              * *(_DWORD *)&this->remarkbuf[20]]
                                                                      + 16))(
      &this->m_ListSelNum[172][1824 * *(_DWORD *)&this->remarkbuf[20]],
      296,
      (_DWORD *)(v146),
      this);
    LOBYTE(v102) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
    (((UIPushButton *)&this->m_ListSelNum[172][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Y_down.tga", v102);
    (*(void ( **)(int *, _DWORD))this->m_ListSelNum[172][1824 * *(_DWORD *)&this->remarkbuf[20]])(
      &this->m_ListSelNum[172][1824 * *(_DWORD *)&this->remarkbuf[20]],
      0);
    v103 = *(_DWORD *)&this->remarkbuf[20] + 1;
    *(_DWORD *)&this->remarkbuf[20] = v103;
  }
  while ( v103 < 5 );
  m_align = this->m_Icon[1][4].m_align;
  v153[1] = 436;
  v153[0] = 456;
  v154 = 486;
  v155 = 555;
  (*(void ( **)(int *, int, _DWORD *, SaleUI *))(m_align + 16))(
    &this->m_Icon[1][4].m_align,
    257,
    (_DWORD *)(v153),
    this);
  LOBYTE(v105) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
  (((UIPushButton *)&this->m_Icon[1][4].m_align))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\EquipTopFrame\\TopFrameLS.tga", v105);
  m_nSize = this->m_Icon[2][0].m_childs.m_nSize;
  v153[0] = v154;
  v154 += 256;
  (*(void ( **)(int *, int, _DWORD *, SaleUI *))(m_nSize + 16))(
    &this->m_Icon[2][0].m_childs.m_nSize,
    257,
    (_DWORD *)(v153),
    this);
  LOBYTE(v107) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
  (((UIPushButton *)&this->m_Icon[2][0].m_childs.m_nSize))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\PropTopFrame\\TopFrameRM.tga", v107);
  v108 = this->m_Icon[2][1].m_rect.left;
  v153[0] = v154;
  v154 += 32;
  (*(void ( **)(tagRECT *, int, _DWORD *, SaleUI *))(v108 + 16))(&this->m_Icon[2][1].m_rect, 257, (_DWORD *)(v153), this);
  LOBYTE(v109) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
  (((UIPushButton *)&this->m_Icon[2][1].m_rect))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\EquipTopFrame\\TopFrameR.tga", v109);
  this->m_Icon[2][2].m_FVF = 447;
  *(_DWORD *)&this->m_Icon[2][2].m_mouseoff = 489;
  this->m_Icon[2][2].m_nTextW = 745;
  this->m_Icon[2][2].m_color.Color = this->m_Icon[2][2].m_FVF + 100;
  (*(void ( **)(float *, int, _BYTE *, SaleUI *))(LODWORD(this->m_Icon[2][1].m_fadespeed) + 16))(
    &this->m_Icon[2][1].m_fadespeed,
    265,
    &this->m_Icon[2][2].m_mouseoff,
    this);
  (((UIScene *)&this->m_Icon[2][1].m_fadespeed))->UIScene::SetShow(0);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Icon[2][1].m_fadespeed))(&this->m_Icon[2][1].m_fadespeed, 0);
  m_text = this->m_Icon[3][2].m_text;
  *(_DWORD *)&this->m_Icon[3][2].m_text[4] = this->m_Icon[2][2].m_FVF;
  *(_DWORD *)this->m_Icon[3][2].m_text = *(_DWORD *)&this->m_Icon[2][2].m_mouseoff;
  *(_DWORD *)&this->m_Icon[3][2].m_text[8] = this->m_Icon[2][2].m_nTextW;
  *(_DWORD *)&this->m_Icon[3][2].m_text[12] = this->m_Icon[2][2].m_color.Color;
  (*(void ( **)(_PlugInfo **, int, char *, SaleUI *))&this->m_Icon[3][1].m_ppicInfo->name[12])(
    &this->m_Icon[3][1].m_ppicInfo,
    305,
    this->m_Icon[3][2].m_text,
    this);
  (((UIScene *)&this->m_Icon[3][1].m_ppicInfo))->UIScene::SetShow(0);
  v111 = this->m_Icon[2][2].m_color.Color - 36;
  v170[0] = this->m_Icon[2][2].m_nTextW - 36;
  v170[1] = v111;
  v170[2] = v170[0] + 24;
  v170[3] = v111 + 32;
  (*(void ( **)(SaleUI_SortData *, int, _DWORD *, SaleUI *))(*(_DWORD *)&this->m_sort[361][2] + 16))(
    &this->m_sort[361][2],
    2,
    (_DWORD *)(v170),
    this);
  (((UIScene *)&this->m_sort[361][2]))->UIScene::LoadResource("ui\\scene\\page");
  UIScene_SetController(0x40000000);
  (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
  this->ml_TreasureList.m_scrollbar.m_bk.m_rect.bottom = 569;
  m_locksel = this->ml_ResumeList.m_locksel;
  this->ml_TreasureList.m_scrollbar.m_bk.m_rect.right = 300;
  this->ml_TreasureList.m_scrollbar.m_bk.m_pfather = ((UIWnd *)((UIWnd *)390));
  this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_pData = ((char *)((char *)(this->ml_TreasureList.m_scrollbar.m_bk.m_rect.bottom
                                                                   + 25)));
  v113 = *(&this->AttackNum + 289);
  LOBYTE(v113) = *(_BYTE *)(v113 + 3284);
  (*(void ( **)(int *, int, LONG *, SaleUI *, char *, _DWORD, int))(m_locksel + 28))(
    &this->ml_ResumeList.m_locksel,
    262,
    &this->ml_TreasureList.m_scrollbar.m_bk.m_rect.right,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v113);
  (((PalScript *)&this->ml_ResumeList.m_locksel))->PalScript::OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnYes.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  bottom = this->ml_TreasureList.m_scrollbar.m_bk.m_rect.bottom;
  *(_DWORD *)&this->ml_TreasureList.m_column[1].head[32]  = (unsigned long)(this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_pData);
  v115 = (char *)&this->ml_TreasureList.m_scrollbar.m_bk.m_pfather->m_bfocus + 2;
  *(_DWORD *)&this->ml_TreasureList.m_column[1].head[24] = bottom;
  *(_DWORD *)&this->ml_TreasureList.m_column[1].head[20] = (_DWORD)v115;
  *(_DWORD *)&this->ml_TreasureList.m_column[1].head[28] = (_DWORD)v115 + 90;
  v116 = *(&this->AttackNum + 289);
  LOBYTE(v116) = *(_BYTE *)(v116 + 3284);
  (*(void ( **)(int *, int, char *, SaleUI *, char *, _DWORD, int))(this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize
                                                                                       + 28))(
    &this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize,
    263,
    &this->ml_TreasureList.m_column[1].head[20],
    this,
    "UI\\Assistant\\Communal\\bDicker",
    0,
    v116);
  sub_445E50((int)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize);
  (((PalScript *)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnDicker.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  v117 = *(_DWORD *)&this->ml_TreasureList.m_column[1].head[28];
  v118 = *(_DWORD *)&this->ml_TreasureList.m_column[1].head[32];
  *(_DWORD *)&this->ml_TreasureList.m_column[5].head[48] = *(_DWORD *)&this->ml_TreasureList.m_column[1].head[24];
  v117 += 66;
  *(_DWORD *)&this->ml_TreasureList.m_column[5].head[56] = v118;
  v119 = *(&this->AttackNum + 289);
  *(_DWORD *)&this->ml_TreasureList.m_column[5].head[44] = v117;
  *(_DWORD *)&this->ml_TreasureList.m_column[5].head[52] = v117 + 90;
  LOBYTE(v119) = *(_BYTE *)(v119 + 3284);
  (*(void ( **)(char *, int, char *, SaleUI *, char *, _DWORD, int))(*(_DWORD *)&this->ml_TreasureList.m_column[1].head[36]
                                                                             + 28))(
    &this->ml_TreasureList.m_column[1].head[36],
    264,
    &this->ml_TreasureList.m_column[5].head[44],
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    v119);
  (((PalScript *)&this->ml_TreasureList.m_column[1].head[36]))->PalScript::OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnNo.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  v120 = *(_DWORD *)&this->m_sort[341][3] - 38;
  v121 = *(_DWORD *)&this->m_sort[341][4] - 50;
  *((_DWORD *)&this->ml_TreasureList + 315) = v120;
  *((_DWORD *)&this->ml_TreasureList + 316) = v121;
  *((_DWORD *)&this->ml_TreasureList + 317) = v120 + 38;
  v122 = *(&this->AttackNum + 289);
  *((_DWORD *)&this->ml_TreasureList + 318) = v121 + 48;
  LOBYTE(v122) = *(_BYTE *)(v122 + 3284);
  (*(void ( **)(char *, int, char *, SaleUI *, char *, _DWORD, int))(*(_DWORD *)&this->ml_TreasureList.m_column[5].head[60]
                                                                             + 28))(
    &this->ml_TreasureList.m_column[5].head[60],
    258,
    (char *)&this->ml_TreasureList + 1260,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    0,
    v122);
  (((PalScript *)&this->ml_TreasureList.m_column[5].head[60]))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnExit.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  (((CCBFiveNimbusWindow *)&this->m_Icon[0][0].m_rect))->CCBFiveNimbusWindow::CreateScriptAndCamera(404, (int)this);
  v148 = unk_C10D38;
  v123 = (char *)"D16";
  while ( 1 )
  {
    v124 = *v123;
    v147 = v124;
    v125 = v124 < (unsigned __int8)*v148;
    if ( v124 != *v148 )
      break;
    if ( !v124 )
      goto LABEL_12;
    v147 = v123[1];
    v125 = v147 < (unsigned __int8)v148[1];
    if ( v147 != v148[1] )
      break;
    v123 += 2;
    v148 += 2;
    if ( !v147 )
    {
LABEL_12:
      v126 = 0;
      goto LABEL_14;
    }
  }
  v126 = -v125 - (v125 - 1);
LABEL_14:
  if ( v126 )
    sprintf(this->buf, "Item\\%s\\%s.pol", "D16", "D16");
  else
    sprintf(this->buf, "%s", "NONE");
  (((PalScript *)&this->m_Icon[0][0].m_texty))->PalScript::LoadModel(this->buf, 0);
  this->m_Icon[0][0].m_fonttype = ((Parent_Data *)0);
  this->m_Icon[0][0].m_textx = (void *)1;
  (((CCBFiveNimbusWindow *)&this->m_Icon[0][0].m_rect))->CCBFiveNimbusWindow::SetFloatParam(120.0);
  (((Camera *)&this->m_Icon[0][0].m_rect))->Camera::UpdateCameraLookAt(330, 258, 600);
  sub_43A090((int)&this->m_Icon[0][0].m_rect, 1, 0.0);
  v127 = *(&this->AttackNum + 289);
  *(&this->AttackNum + 105) = 439;
  *(&this->AttackNum + 106) = 576;
  *(&this->AttackNum + 104) = 492;
  *(&this->AttackNum + 107) = 489;
  LOBYTE(v127) = *(_BYTE *)(v127 + 3284);
  (*(void ( **)(char *, int, int *, SaleUI *, char *, _DWORD, int))(*((_DWORD *)&this->ml_TreasureList
                                                                                         + 319)
                                                                                       + 28))(
    (char *)&this->ml_TreasureList + 1276,
    273,
    &this->AttackNum + 104,
    this,
    "UI\\Assistant\\Equip\\bDK5",
    0,
    v127);
  (((PalScript *)((char *)&this->ml_TreasureList + 1276)))->PalScript::OpenScript("UI\\Assistant\\Equip\\UnDK5.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  v128 = *(&this->AttackNum + 106);
  v129 = (gbTexture *)this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14];
  *(&this->AttackNum + 104) = v128;
  *(&this->AttackNum + 106) = v128 + 84;
  v130 = *(&this->AttackNum + 289);
  LOBYTE(v130) = *(_BYTE *)(v130 + 3284);
  ((void ( *)(gbTexture **, int, int *, SaleUI *, char *, _DWORD, int))v129->Height)(
    &this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14],
    274,
    &this->AttackNum + 104,
    this,
    "UI\\Assistant\\Equip\\bDK6",
    0,
    v130);
  (((PalScript *)&this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14]))->PalScript::OpenScript("UI\\Assistant\\Equip\\UnDK6.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  v131 = *(&this->AttackNum + 106);
  capacity = this->ml_AttackList.m_column[2].items.capacity;
  *(&this->AttackNum + 104) = v131;
  *(&this->AttackNum + 106) = v131 + 84;
  v133 = *(&this->AttackNum + 289);
  LOBYTE(v133) = *(_BYTE *)(v133 + 3284);
  (*(void ( **)(int *, int, int *, SaleUI *, char *, _DWORD, int))(capacity + 28))(
    &this->ml_AttackList.m_column[2].items.capacity,
    275,
    &this->AttackNum + 104,
    this,
    "UI\\Assistant\\Equip\\bDK7",
    0,
    v133);
  (((PalScript *)&this->ml_AttackList.m_column[2].items.capacity))->PalScript::OpenScript("UI\\Assistant\\Equip\\UnDK7.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  v134 = *(&this->AttackNum + 107);
  *(&this->AttackNum + 104) = 492;
  v134 += 2;
  *(&this->AttackNum + 106) = 576;
  *(&this->AttackNum + 105) = v134;
  *(&this->AttackNum + 107) = v134 + 50;
  v135 = *(&this->AttackNum + 289);
  LOBYTE(v135) = *(_BYTE *)(v135 + 3284);
  (*(void ( **)(int *, int, int *, SaleUI *, char *, _DWORD, int))(this->ml_AttackList.m_column[6].items.m_needscriptdel
                                                                                                 + 28))(
    &this->ml_AttackList.m_column[6].items.m_needscriptdel,
    276,
    &this->AttackNum + 104,
    this,
    "UI\\Assistant\\Equip\\bDK8",
    0,
    v135);
  (((PalScript *)&this->ml_AttackList.m_column[6].items.m_needscriptdel))->PalScript::OpenScript("UI\\Assistant\\Equip\\UnDK8.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  v136 = *(&this->AttackNum + 106);
  v137 = *(&this->AttackNum + 18);
  *(&this->AttackNum + 104) = v136;
  *(&this->AttackNum + 106) = v136 + 84;
  v138 = *(&this->AttackNum + 289);
  LOBYTE(v138) = *(_BYTE *)(v138 + 3284);
  (*(void ( **)(int *, int, int *, SaleUI *, char *, _DWORD, int))(v137 + 28))(
    &this->AttackNum + 18,
    277,
    &this->AttackNum + 104,
    this,
    "UI\\Assistant\\Equip\\bDK9",
    0,
    v138);
  (((PalScript *)(&this->AttackNum + 18)))->PalScript::OpenScript("UI\\Assistant\\Equip\\UnDK9.tga", *(_BYTE *)(*(&this->AttackNum + 289) + 3284));
  *(_DWORD *)&this->m_Icon[3][2].m_text[4] = 492;
  *(_DWORD *)m_text = 511;
  *(_DWORD *)&this->m_Icon[3][2].m_text[8] = 595;
  m_dstAlpha = this->m_Icon[2][2].m_dstAlpha;
  *(_DWORD *)&this->m_Icon[3][2].m_text[12] = *(_DWORD *)&this->m_Icon[3][2].m_text[4] + 50;
  v140 = *(&this->AttackNum + 289);
  LOBYTE(v140) = *(_BYTE *)(v140 + 3284);
  (*(void ( **)(int *, int, char *, SaleUI *, char *, _DWORD, int))(m_dstAlpha + 28))(
    &this->m_Icon[2][2].m_dstAlpha,
    297,
    this->m_Icon[3][2].m_text,
    this,
    "UI\\Assistant\\Equip\\bEquipYes",
    0,
    v140);
  v141 = *(_DWORD *)&this->m_Icon[3][2].m_text[8] + 40;
  *(_DWORD *)m_text = v141;
  *(_DWORD *)&this->m_Icon[3][2].m_text[8] = v141 + 84;
  v142 = *(&this->AttackNum + 289);
  LOBYTE(v142) = *(_BYTE *)(v142 + 3284);
  (*(void ( **)(int, char *, SaleUI *, char *, _DWORD, int))(*(_DWORD *)&this->m_Icon[2][4].m_mouseoff + 28))(
    304,
    this->m_Icon[3][2].m_text,
    this,
    "UI\\Assistant\\Equip\\bEquipNo",
    0,
    v142);
  this->SaleUI::GetValue(0);
  v171[5] = 200;
  v171[4] = 300;
  v171[6] = 500;
  v171[7] = 300;
  Create__ovl_1((ARC_PlayerAtt *)&this->m_Icon[0][1].m_FVF);
  (((UIItem *)&this->m_Icon[0][1].m_FVF))->UIItem::SetData(31);
  result = this->SaleUI::SetValue(0);
  this->remarkbuf[32] = 1;
  return result;
}

// 0x00460A90
int SaleUI::UpdateSkillPanel()
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // ebp
  int v7; // ecx
  int v8; // eax
  int v9; // edi
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // edi
  char *v15; // eax
  _DWORD *v16; // ecx
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  int v20; // edx
  int v21; // eax
  int v22; // ecx
  int v23; // eax
  int v24; // edx
  RoleAtt *v25; // eax
  char *v26; // eax
  int *v27; // eax
  int v28; // eax
  int v29; // edx
  RoleAtt *v30; // eax
  char *v31; // eax
  int v32; // eax
  RoleAtt *v33; // edx
  RoleAtt *v34; // eax
  char *v35; // eax
  int v36; // eax
  RoleAtt *v37; // edx
  RoleAtt *v38; // eax
  char *v39; // eax
  int v40; // eax
  RoleAtt *v41; // edx
  RoleAtt *v42; // eax
  char *v43; // eax
  int v44; // eax
  int v45; // edx
  RoleAtt *v46; // eax
  char *v47; // eax
  int v48; // eax
  int v49; // ecx
  int v50; // eax
  int v51; // ecx
  int **v52; // eax
  int v53; // ecx
  int *v54; // eax
  int v55; // ecx
  int v56; // eax
  int v57; // eax
  int v58; // edi
  char *v59; // eax
  _DWORD *v60; // ecx
  int v61; // edx
  int v62; // eax
  int v63; // ecx
  int v64; // edx
  int v65; // eax
  int v66; // ecx
  int v67; // eax
  int result; // eax
  int p_DWORD; // [esp+0x10] [ebp-0x18] BYREF
  int v70; // [esp+0x14] [ebp-0x14]
  RoleAtt *v71; // [esp+0x18] [ebp-0x10]
  int v72; // [esp+0x1C] [ebp-0xC] BYREF
  int v73; // [esp+0x20] [ebp-0x8]
  int *v74; // [esp+0x24] [ebp-0x4]
  int v75; // [esp+0x2C] [ebp+0x4]
  char v76; // [esp+0x30] [ebp+0x8]

  if ( *(&this->AttackNum + 285) )
  {
    operator delete(*((void **)&this->AttackNum + 285));
    *(&this->AttackNum + 285) = 0;
  }
  *(&this->AttackNum + 285) = (int)operator new(4 * *(&this->AttackNum + 286));
  v2 = *(&this->dwWeaponWU + 3264);
  *(&this->AttackNum + 287) = 0;
  *(_DWORD *)&this->remarkbuf[20] = 0;
  if ( v2 > 0 )
  {
    do
    {
      v3 = *(_DWORD *)&this->remarkbuf[20];
      v4 = *(_DWORD *)&this->remarkbuf[4];
      *(_DWORD *)&this->remarkbuf[24] = 0;
      if ( *(int *)(v4 + 4 * v3) > 0 )
      {
        do
        {
          *(_DWORD *)(*(&this->AttackNum + 285) + 4 * *(&this->AttackNum + 287)) = **((_DWORD **)&this->dwWeaponWU
                                                                                    + v3
                                                                                    + 3666);
          v5 = *(_DWORD *)&this->remarkbuf[4];
          v6 = *(_DWORD *)&this->remarkbuf[24] + 1;
          ++*(&this->AttackNum + 287);
          v3 = *(_DWORD *)&this->remarkbuf[20];
          *(_DWORD *)&this->remarkbuf[24] = v6;
        }
        while ( v6 < *(_DWORD *)(v5 + 4 * v3) );
      }
      if ( *(&this->AttackNum + 287) >= *(&this->AttackNum + 286) )
        break;
      v7 = *(&this->dwWeaponWU + 3264);
      v8 = *(_DWORD *)&this->remarkbuf[20] + 1;
      *(_DWORD *)&this->remarkbuf[20] = v8;
    }
    while ( v8 < v7 );
  }
  v9 = *(_DWORD *)&this->remarkbuf[16];
  if ( v76 )
  {
    switch ( v75 )
    {
      case 0:
        v10 = 5 * v9;
        goto LABEL_16;
      case 1:
        v11 = 6 * v9;
        goto LABEL_14;
      case 2:
        v10 = 7 * v9;
        goto LABEL_16;
      case 3:
        v11 = 8 * v9;
LABEL_14:
        v12 = v11 / 10;
        goto LABEL_17;
      case 4:
        v10 = 9 * v9;
LABEL_16:
        v12 = v10 / 10;
LABEL_17:
        v9 = v12;
        break;
      default:
        break;
    }
  }
  (*(void ( **)(float *, int))LODWORD(this->m_Icon[2][1].m_fadespeed))(&this->m_Icon[2][1].m_fadespeed, 1);
  (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (int)(1));
  v13 = *(&this->AttackNum + 281);
  *(&this->AttackNum + 279) = 0;
  switch ( v13 )
  {
    case 0:
      rand();
      SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
      *((_BYTE *)&this->AttackNum + 601) = 0;
      this->SaleUI::SetValue(0);
      goto LABEL_88;
    case 1:
      if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) < v9 || v9 <= 0 )
      {
        if ( *(int *)&this->remarkbuf[16] <= 0 )
        {
          SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
          *((_BYTE *)&this->AttackNum + 601) = 0;
          goto LABEL_88;
        }
        if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) >= v9 )
        {
          if ( v76 )
          {
            this->SaleUI::SetValue(1u);
            this->SaleUI::SetRange(0);
            sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
            *(&this->AttackNum + 281) = 0;
            *((_BYTE *)&this->AttackNum + 601) = 0;
            goto LABEL_88;
          }
          this->SaleUI::SetValue(0);
          this->SaleUI::SetRange(1u);
        }
        else
        {
          SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
          this->SaleUI::SetValue(0);
          (((PAL3 *)this))->PAL3::SetPanelStates(1u);
          this->SaleUI::SetRange(0);
        }
        sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
        *((_BYTE *)&this->AttackNum + 601) = 0;
      }
      else
      {
        *(&g_RoleSlotBuf.dword_17AA450 + 147) -= v9;
        if ( v76 )
          rand();
        SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
        if ( *(&this->dwWeaponWU + 4166) )
        {
          operator delete(*((void **)&this->dwWeaponWU + 4166));
          *(&this->dwWeaponWU + 4166) = 0;
        }
        v14 = *(&this->AttackNum + 286);
        v15 = (char *)operator new(12 * v14);
        if ( v15 )
        {
          if ( v14 - 1 >= 0 )
          {
            v16 = (_DWORD *)v15 + 8;
            v17 = v14;
            do
            {
              *(v16 - 2) = 0xFFFF;
              *(v16 - 1) = 0;
              *v16 = 0;
              v16 += 3;
              --v17;
            }
            while ( v17 );
          }
        }
        else
        {
          v15 = 0;
        }
        *(&this->dwWeaponWU + 4166) = (int)v15;
        v18 = *(&this->AttackNum + 286);
        *(_DWORD *)&this->remarkbuf[20] = 0;
        if ( v18 > 0 )
        {
          do
          {
            *(_DWORD *)(*(&this->dwWeaponWU + 4166) + 12 * *(_DWORD *)&this->remarkbuf[20]) = *(_DWORD *)(*(&this->AttackNum + 285) + 4 * *(_DWORD *)&this->remarkbuf[20]);
            *(_DWORD *)(*(&this->dwWeaponWU + 4166) + 12 * *(_DWORD *)&this->remarkbuf[20] + 4) = 1;
            *(_DWORD *)(*(&this->dwWeaponWU + 4166) + 12 * *(_DWORD *)&this->remarkbuf[20] + 8) = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(_DWORD *)(*(&this->AttackNum + 285) + 4 * *(_DWORD *)&this->remarkbuf[20]));
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive((int *)(*(&this->dwWeaponWU + 4166) + 12 * *(_DWORD *)&this->remarkbuf[20]));
            v19 = *(&this->AttackNum + 286);
            v20 = *(_DWORD *)&this->remarkbuf[20] + 1;
            *(_DWORD *)&this->remarkbuf[20] = v20;
          }
          while ( v20 < v19 );
        }
        p_DWORD = 0xFFFF;
        v70 = 0;
        v71 = 0;
        *(_DWORD *)&this->remarkbuf[20] = 0;
        do
        {
          if ( this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
          {
            *(_DWORD *)&this->remarkbuf[24] = 0;
            do
            {
              v21 = *(_DWORD *)&this->remarkbuf[20];
              v22 = *(_DWORD *)&this->remarkbuf[24];
              if ( *((_BYTE *)&this->m_ListSaleTitle.m_rect.left + 6 * v21 + v22 + 1) )
              {
                switch ( v22 )
                {
                  case 0:
                    v70 = 1;
                    v23 = 352 * v21;
                    v24 = *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrames + v23 * 4);
                    v25 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[v23];
                    p_DWORD = v24;
                    v71 = (RoleAtt *)v25;
                    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
                    v26 = (char *)this + 1408 * *(_DWORD *)&this->remarkbuf[20];
                    if ( *((_DWORD *)v26 + 4689) )
                    {
                      v27 = (int *)(v26 + 18748);
                      goto LABEL_51;
                    }
                    break;
                  case 1:
                    v70 = 1;
                    v44 = 1408 * v21;
                    v45 = *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_obbox + v44);
                    v46 = (RoleAtt *)*(RoleAtt **)((char *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + v44);
                    p_DWORD = v45;
                    v71 = (RoleAtt *)v46;
                    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
                    v47 = (char *)this + 1408 * *(_DWORD *)&this->remarkbuf[20];
                    if ( *((_DWORD *)v47 + 4701) )
                    {
                      v27 = (int *)(v47 + 18796);
                      goto LABEL_51;
                    }
                    break;
                  case 2:
                    v70 = 1;
                    v36 = 352 * v21;
                    v37 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[v36 + 1];
                    v38 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[v36 + 3];
                    p_DWORD = (int)v37;
                    v71 = (RoleAtt *)v38;
                    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
                    v39 = (char *)this + 1408 * *(_DWORD *)&this->remarkbuf[20];
                    if ( *((_DWORD *)v39 + 4695) )
                    {
                      v27 = (int *)(v39 + 18772);
                      goto LABEL_51;
                    }
                    break;
                  case 3:
                    v70 = 1;
                    v28 = 1408 * v21;
                    v29 = *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_nModelParamB + v28);
                    v30 = (RoleAtt *)*(RoleAtt **)((char *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + v28);
                    p_DWORD = v29;
                    v71 = (RoleAtt *)v30;
                    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
                    v31 = (char *)this + 1408 * *(_DWORD *)&this->remarkbuf[20];
                    if ( *((_DWORD *)v31 + 4686) )
                    {
                      v27 = (int *)(v31 + 18736);
                      goto LABEL_51;
                    }
                    break;
                  case 4:
                    v70 = 1;
                    v32 = 352 * v21;
                    v33 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[v32 + 1];
                    v34 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[v32];
                    p_DWORD = (int)v33;
                    v71 = (RoleAtt *)v34;
                    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
                    v35 = (char *)this + 1408 * *(_DWORD *)&this->remarkbuf[20];
                    if ( *((_DWORD *)v35 + 4692) )
                    {
                      v27 = (int *)(v35 + 18760);
                      goto LABEL_51;
                    }
                    break;
                  case 5:
                    v70 = 1;
                    v40 = 352 * v21;
                    v41 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[v40 + 4];
                    v42 = (RoleAtt *)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[v40 + 6];
                    p_DWORD = (int)v41;
                    v71 = (RoleAtt *)v42;
                    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
                    v43 = (char *)this + 1408 * *(_DWORD *)&this->remarkbuf[20];
                    if ( *((_DWORD *)v43 + 4698) )
                    {
                      v27 = (int *)(v43 + 18784);
LABEL_51:
                      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(v27);
                    }
                    break;
                  default:
                    break;
                }
              }
              v48 = *(_DWORD *)&this->remarkbuf[24] + 1;
              *(_DWORD *)&this->remarkbuf[24] = v48;
            }
            while ( v48 < 6 );
          }
          v49 = *(_DWORD *)&this->remarkbuf[20] + 1;
          *(_DWORD *)&this->remarkbuf[20] = v49;
        }
        while ( v49 < 5 );
        if ( *(&this->dwWeaponWU + 4166) )
        {
          operator delete(*((void **)&this->dwWeaponWU + 4166));
          *(&this->dwWeaponWU + 4166) = 0;
        }
        *(&this->AttackNum + 283) = 0;
        *(&this->AttackNum + 286) = 0;
        *(_DWORD *)&this->remarkbuf[16] = 0;
        sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
        SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
        SetEnable((UICaption *)&this->ml_ResumeList.m_column[0].head[16]);
        v50 = *(&this->dwWeaponWU + 3264);
        this->m_Icon[0][0].m_fonttype = ((Parent_Data *)0);
        *(_DWORD *)&this->remarkbuf[20] = 0;
        if ( v50 > 0 )
        {
          do
          {
            *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)&this->remarkbuf[20]) = 0;
            sprintf(
              this->buf,
              (const char *)&dir[20],
              *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)&this->remarkbuf[20]));
            (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)&this->remarkbuf[20], this->buf, 0);
            v51 = *(_DWORD *)&this->remarkbuf[20];
            v73 = 0;
            v74 = 0;
            v52 = (int **)(&this->dwWeaponWU + v51 + 3666);
            v72 = 0xFFFF;
            v53 = **v52;
            v73 = 1;
            v72 = v53;
            v74 = (int *)*v52;
            v54 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&v72);
            if ( v54 )
              *(_DWORD *)(*(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) + 4 * *(_DWORD *)&this->remarkbuf[20]) = 99 - v54[1];
            else
              *(_DWORD *)(*(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) + 4 * *(_DWORD *)&this->remarkbuf[20]) = 99;
            v55 = *(&this->dwWeaponWU + 3264);
            v56 = *(_DWORD *)&this->remarkbuf[20] + 1;
            *(_DWORD *)&this->remarkbuf[20] = v56;
          }
          while ( v56 < v55 );
        }
        this->SaleUI::SetValue(0);
        sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
        this->SaleUI::SetRange(0);
        *((_BYTE *)&this->AttackNum + 601) = 1;
      }
      goto LABEL_88;
    case 2:
      v57 = *(_DWORD *)&this->remarkbuf[16];
      if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) < v57 )
      {
        SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
        *(&this->AttackNum + 281) = 0;
        *((_BYTE *)&this->AttackNum + 601) = 0;
      }
      else
      {
        *(&g_RoleSlotBuf.dword_17AA450 + 147) -= v57;
        *(&this->AttackNum + 279) = 0;
        rand();
        SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
        if ( *(&this->dwWeaponWU + 4166) )
        {
          operator delete(*((void **)&this->dwWeaponWU + 4166));
          *(&this->dwWeaponWU + 4166) = 0;
        }
        v58 = *(&this->AttackNum + 286);
        v59 = (char *)operator new(12 * v58);
        if ( v59 )
        {
          if ( v58 - 1 >= 0 )
          {
            v60 = (_DWORD *)v59 + 8;
            v61 = v58;
            do
            {
              *(v60 - 2) = 0xFFFF;
              *(v60 - 1) = 0;
              *v60 = 0;
              v60 += 3;
              --v61;
            }
            while ( v61 );
          }
        }
        else
        {
          v59 = 0;
        }
        *(&this->dwWeaponWU + 4166) = (int)v59;
        v62 = *(&this->AttackNum + 286);
        *(_DWORD *)&this->remarkbuf[20] = 0;
        if ( v62 > 0 )
        {
          do
          {
            *(_DWORD *)(*(&this->dwWeaponWU + 4166) + 12 * *(_DWORD *)&this->remarkbuf[20]) = *(_DWORD *)(*(&this->AttackNum + 285) + 4 * *(_DWORD *)&this->remarkbuf[20]);
            *(_DWORD *)(*(&this->dwWeaponWU + 4166) + 12 * *(_DWORD *)&this->remarkbuf[20] + 4) = 1;
            *(_DWORD *)(*(&this->dwWeaponWU + 4166) + 12 * *(_DWORD *)&this->remarkbuf[20] + 8) = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(_DWORD *)(*(&this->AttackNum + 285) + 4 * *(_DWORD *)&this->remarkbuf[20]));
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive((int *)(*(&this->dwWeaponWU + 4166) + 12 * *(_DWORD *)&this->remarkbuf[20]));
            v63 = *(&this->AttackNum + 286);
            v64 = *(_DWORD *)&this->remarkbuf[20] + 1;
            *(_DWORD *)&this->remarkbuf[20] = v64;
          }
          while ( v64 < v63 );
        }
        if ( *(&this->dwWeaponWU + 4166) )
        {
          operator delete(*((void **)&this->dwWeaponWU + 4166));
          *(&this->dwWeaponWU + 4166) = 0;
        }
        *(&this->AttackNum + 283) = 0;
        *(&this->AttackNum + 286) = 0;
        *(_DWORD *)&this->remarkbuf[16] = 0;
        sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
        SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
        SetEnable((UICaption *)&this->ml_ResumeList.m_column[0].head[16]);
        v65 = *(&this->dwWeaponWU + 3264);
        this->m_Icon[0][0].m_fonttype = ((Parent_Data *)0);
        *(_DWORD *)&this->remarkbuf[20] = 0;
        if ( v65 > 0 )
        {
          do
          {
            *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)&this->remarkbuf[20]) = 0;
            sprintf(
              this->buf,
              (const char *)&dir[20],
              *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)&this->remarkbuf[20]));
            (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)&this->remarkbuf[20], this->buf, 0);
            v66 = *(&this->dwWeaponWU + 3264);
            v67 = *(_DWORD *)&this->remarkbuf[20] + 1;
            *(_DWORD *)&this->remarkbuf[20] = v67;
          }
          while ( v67 < v66 );
        }
        *((_BYTE *)&this->AttackNum + 601) = 1;
        this->SaleUI::SetValue(0);
LABEL_88:
        if ( *(&this->AttackNum + 285) )
        {
          operator delete(*((void **)&this->AttackNum + 285));
          *(&this->AttackNum + 285) = 0;
        }
        sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
        SetEnable((UICaption *)&this->ml_ResumeList.m_column[4].head[16]);
        (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 0);
        (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
          &this->m_ListGrid[14].m_bvisible,
          0);
        return (**((int ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
      }
      return result;
    case 3:
      this->SaleUI::SetValue(0);
      rand();
      SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
      g_bListNeedsRefresh = 1;
      goto LABEL_88;
    default:
      goto LABEL_88;
  }
}

// 0x004615F0
int SaleUI::DestroySubFrames()
{
  int v2; // ecx
  SaleUI_SortData *v3; // eax
  SaleUI_SortData *v4; // edi
  int v5; // eax
  LONG v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  _DWORD a2[4]; // [esp+0x18] [ebp-0x10] BYREF

  if ( !*((_BYTE *)&this->AttackNum + 601) )
  {
    this->SaleUI::ConsumeItems();
    v2 = 0;
    v3 = (SaleUI_SortData *)&this->m_sort[32][2];
    do
    {
      if ( this->m_sort[412][2]._tail_000[v2] )
      {
        if ( v3[2] )
        {
          *v3 = 0;
          v3[1] = 0;
          v3[2] = 0;
        }
        if ( v3[-1] )
        {
          v4 = (SaleUI_SortData *)(v3 - 3);
          *v4 = 0;
          v4[1] = 0;
          v4[2] = 0;
        }
        if ( v3[5] )
        {
          v3[3] = 0;
          v3[4] = 0;
          v3[5] = 0;
        }
        if ( v3[8] )
        {
          v3[6] = 0;
          v3[7] = 0;
          v3[8] = 0;
        }
        if ( v3[11] )
        {
          v3[9] = 0;
          v3[10] = 0;
          v3[11] = 0;
        }
        if ( v3[14] )
        {
          v3[12] = 0;
          v3[13] = 0;
          v3[14] = 0;
        }
      }
      ++v2;
      v3 += 352;
    }
    while ( v2 < 5 );
    v5 = *(&this->dwWeaponWU + 3264);
    *(_DWORD *)&this->remarkbuf[20] = 0;
    if ( v5 > 0 )
    {
      do
      {
        *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)&this->remarkbuf[20]) = 0;
        sprintf(this->buf, (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)&this->remarkbuf[20]));
        (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)&this->remarkbuf[20], this->buf, 0);
        v6 = *(_DWORD *)&this->remarkbuf[20];
        if ( v6 < 0 || v6 >= this->m_ListGrid[7].m_rect.right )
          v7 = 0;
        else
          v7 = *(_DWORD *)(this->m_ListGrid[7].m_rect.top + 4 * v6);
        *(_DWORD *)(v7 + 68)  = (unsigned long)(this->m_ListGrid[3].m_disablepicInfo);
        v8 = *(&this->dwWeaponWU + 3264);
        v9 = *(_DWORD *)&this->remarkbuf[20] + 1;
        *(_DWORD *)&this->remarkbuf[20] = v9;
      }
      while ( v9 < v8 );
    }
    (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItem();
    *(&this->AttackNum + 286) = 0;
    *(_DWORD *)&this->remarkbuf[16] = 0;
    sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
    SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
    *(_DWORD *)&this->remarkbuf[20] = 0;
    do
    {
      if ( this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
      {
        *(_DWORD *)&this->remarkbuf[24] = 0;
        do
        {
          (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4])(
            &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4],
            0);
          *(_DWORD *)&this->remarkbuf[28] = 0;
          do
          {
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[412][1824
                                                                                  * *(_DWORD *)&this->remarkbuf[20]
                                                                                  + 4
                                                                                  + 304
                                                                                  * *(_DWORD *)&this->remarkbuf[24]
                                                                                  + 38 * *(_DWORD *)&this->remarkbuf[28]])((SaleUI_SortData *)(&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                               + 4
                               + 304 * *(_DWORD *)&this->remarkbuf[24]
                               + 38 * *(_DWORD *)&this->remarkbuf[28]]), (_DWORD)(0));
            v10 = *(_DWORD *)&this->remarkbuf[28] + 1;
            *(_DWORD *)&this->remarkbuf[28] = v10;
          }
          while ( v10 < 8 );
          v11 = *(_DWORD *)&this->remarkbuf[24] + 1;
          *(_DWORD *)&this->remarkbuf[24] = v11;
        }
        while ( v11 < 6 );
      }
      v12 = *(_DWORD *)&this->remarkbuf[20] + 1;
      *(_DWORD *)&this->remarkbuf[20] = v12;
    }
    while ( v12 < 5 );
    SetEnable((UICaption *)&this->ml_ResumeList.m_column[2].head[16]);
    SetEnable((UICaption *)&this->ml_ResumeList.m_column[0].head[16]);
    this->m_Icon[0][0].m_fonttype = ((Parent_Data *)0);
    this->SaleUI::GetValue(0);
    LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
  }
  memset((char *)&this->m_ListSaleTitle.m_rect.left + 1, 0, 0x1Cu);
  *(_WORD *)((char *)&this->m_ListSaleTitle.m_childs.m_nSize + 1) = 0;
  memset(&this->m_ListSaleTitle.m_bcreateok, 0xFFu, 0x78u);
  this->m_Icon[0][0].m_fontcolor.Color = 0;
  this->m_Icon[0][0].m_wndcolor.Color = 0;
  LOWORD(this->m_Icon[0][0].m_id) = 0;
  memset(*(void **)&this->remarkbuf[4], 0, 4 * *(&this->dwWeaponWU + 3264));
  memset((void *)this->m_ListSaleTitle.m_childs.m_needscriptdel, 0, 4 * *(&this->dwWeaponWU + 3264));
  memset((void *)this->m_ListEquipTitleRc.bottom, 0, 4 * *(&this->dwWeaponWU + 3264));
  *(_DWORD *)&this->remarkbuf[20] = 0;
  do
  {
    if ( this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
    {
      *(_DWORD *)&this->remarkbuf[24] = 0;
      do
      {
        (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4])(
          &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4],
          0);
        (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20]
                                                                   + 2
                                                                   + *(_DWORD *)&this->remarkbuf[24]].m_fonttype)(
          &this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 2 + *(_DWORD *)&this->remarkbuf[24]].m_fonttype,
          0);
        (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4])(
          &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4],
          0);
        *(_DWORD *)&this->remarkbuf[28] = 0;
        do
        {
          (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                                                                                + 4
                                                                                + 304 * *(_DWORD *)&this->remarkbuf[24]
                                                                                + 38 * *(_DWORD *)&this->remarkbuf[28]])((SaleUI_SortData *)(&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                             + 4
                             + 304 * *(_DWORD *)&this->remarkbuf[24]
                             + 38 * *(_DWORD *)&this->remarkbuf[28]]), (_DWORD)(0));
          v13 = *(_DWORD *)&this->remarkbuf[28]
              + 8 * (*(_DWORD *)&this->remarkbuf[24] + 6 * *(_DWORD *)&this->remarkbuf[20]);
          a2[0] = *(&this->m_bWPXS + 4 * v13 + 238);
          a2[1] = *(&this->m_bWPXS + 4 * v13 + 239);
          a2[2] = *(&this->m_bWPXS + 4 * v13 + 240);
          a2[3] = *(&this->m_bWPXS + 4 * v13 + 241);
          (((UIWnd *)&this->m_sort[412][38 * v13 + 4]))->UIWnd::sub_445FA0(a2);
          v14 = *(_DWORD *)&this->remarkbuf[28] + 1;
          *(_DWORD *)&this->remarkbuf[28] = v14;
        }
        while ( v14 < 8 );
        v15 = *(_DWORD *)&this->remarkbuf[24] + 1;
        *(_DWORD *)&this->remarkbuf[24] = v15;
      }
      while ( v15 < 6 );
    }
    v16 = *(_DWORD *)&this->remarkbuf[20] + 1;
    *(_DWORD *)&this->remarkbuf[20] = v16;
  }
  while ( v16 < 5 );
  SetEnable((UICaption *)&this->ml_ResumeList.m_column[0].head[16]);
  SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Icon[2][1].m_fadespeed))(&this->m_Icon[2][1].m_fadespeed, 0);
  (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
  this->m_Icon[0][0].m_fonttype = ((Parent_Data *)0);
  (((PAL3 *)this))->PAL3::SetPanelStates(1u);
  this->SaleUI::GetValue(0);
  sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
  this->SaleUI::SetRange(1u);
  this->SaleUI::SetValue(0);
  this->SaleUI::SendInputToRole(0);
  *(_DWORD *)this->remarkbuf = 0;
  *(&this->AttackNum + 283) = 0;
  *(_DWORD *)&this->remarkbuf[16] = 0;
  *(&this->AttackNum + 286) = 0;
  *(&this->AttackNum + 287) = 0;
  *(&this->AttackNum + 279) = 0;
  *(&this->AttackNum + 281) = -1;
  *((_BYTE *)&this->AttackNum + 1114) = 0;
  *((_BYTE *)&this->AttackNum + 601) = 0;
  LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
  sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
  SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
  v17 = *(&this->dwWeaponWU + 3264);
  *(_DWORD *)&this->remarkbuf[20] = 0;
  if ( v17 > 0 )
  {
    do
    {
      sprintf(this->buf, (const char *)&dir[20], 0);
      (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)&this->remarkbuf[20], this->buf, 0);
      v18 = *(&this->dwWeaponWU + 3264);
      v19 = *(_DWORD *)&this->remarkbuf[20] + 1;
      *(_DWORD *)&this->remarkbuf[20] = v19;
    }
    while ( v19 < v18 );
  }
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItem();
  (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItem();
  SetEnable((UICaption *)&this->ml_ResumeList.m_column[2].head[16]);
  (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 0);
  (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
    &this->m_ListGrid[14].m_bvisible,
    0);
  return (**((int ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
}

// 0x00461C50
void SaleUI::InitMode(int nVal)
{
  float *p_m_fadespeed; // edi
  int v5; // edx
  int v6; // ecx
  float v7; // st7
  float v8; // st7
  int v9; // ecx
  int v10; // edx
  float fProb; // [esp+0xC] [ebp-0x4]
  int nVala; // [esp+0x14] [ebp+0x4]

  p_m_fadespeed = (float *)&this->m_Icon[2][1].m_fadespeed;
  (*(void ( **)(float *, int))LODWORD(this->m_Icon[2][1].m_fadespeed))(&this->m_Icon[2][1].m_fadespeed, 1);
  switch ( nVal )
  {
    case 0:
      v5 = 5 * *(_DWORD *)&this->remarkbuf[16] / 10;
      goto LABEL_8;
    case 1:
      v6 = 6 * *(_DWORD *)&this->remarkbuf[16];
      goto LABEL_7;
    case 2:
      if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) < 7 * *(_DWORD *)&this->remarkbuf[16] / 10 )
        goto LABEL_11;
      goto LABEL_12;
    case 3:
      v6 = 8 * *(_DWORD *)&this->remarkbuf[16];
LABEL_7:
      v5 = v6 / 10;
LABEL_8:
      if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) < v5 )
        goto LABEL_11;
      goto LABEL_12;
    case 4:
      if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) >= 9 * *(_DWORD *)&this->remarkbuf[16] / 10 )
        goto LABEL_12;
LABEL_11:
      SetEnable((UICaption *)p_m_fadespeed);
      (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (int)(1));
      this->SaleUI::SetValue(0);
      (((PAL3 *)this))->PAL3::SetPanelStates(1u);
      this->SaleUI::SetRange(0);
      sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
      sprintf(this->buf, "%s %d", g_szCombatFieldName, *(_DWORD *)&this->remarkbuf[16]);
      SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
      *(&this->AttackNum + 281) = 1;
      *((_BYTE *)&this->AttackNum + 601) = 0;
      break;
    default:
LABEL_12:
      *(&this->AttackNum + 284) = nVal;
      if ( *((float *)&this->dwWeaponWU + nVal + 369) >= 0.0 )
        v7 = *((float *)&this->dwWeaponWU + nVal + 369);
      else
        v7 = (float)(rand() % 100) * 0.009999999776482582f;
      *(float *)&nVala = v7;
      if ( *((float *)&this->dwWeaponWU + nVal + 1014) >= 0.0 )
        v8 = *((float *)&this->dwWeaponWU + nVal + 1014);
      else
        v8 = (float)(rand() % 100) * 0.009999999776482582f;
      if ( (((CCBUI *)this))->CCBUI::RollProbability(*(float *)&nVala) )
      {
        *(&this->AttackNum + 281) = 1;
        this->SaleUI::UpdateSkillPanel();
      }
      else
      {
        fProb = v8;
        if ( (((CCBUI *)this))->CCBUI::RollProbability(fProb) )
        {
          v9 = *(_DWORD *)(&this->m_data.m_Dicker + 43);
          v10 = *(&this->AttackNum + 283) + 1;
          *(&this->AttackNum + 281) = 0;
          *(&this->AttackNum + 283) = v10;
          if ( v10 < v9 )
          {
            switch ( nVal )
            {
              case 1:
                sub_445E50((int)&this->ml_TreasureList + 1276);
                this->SaleUI::UpdateSkillPanel();
                break;
              case 2:
                sub_445E50((int)&this->ml_TreasureList + 1276);
                sub_445E50((int)&this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14]);
                this->SaleUI::UpdateSkillPanel();
                break;
              case 3:
                sub_445E50((int)&this->ml_TreasureList + 1276);
                sub_445E50((int)&this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14]);
                sub_445E50((int)&this->ml_AttackList.m_column[2].items.capacity);
                this->SaleUI::UpdateSkillPanel();
                break;
              case 4:
                sub_445E50((int)&this->ml_TreasureList + 1276);
                sub_445E50((int)&this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14]);
                sub_445E50((int)&this->ml_AttackList.m_column[2].items.capacity);
                sub_445E50((int)&this->ml_AttackList.m_column[6].items.m_needscriptdel);
                this->SaleUI::UpdateSkillPanel();
                break;
              default:
                goto LABEL_29;
            }
          }
          else
          {
            *(&this->AttackNum + 281) = 2;
            this->SaleUI::UpdateSkillPanel();
          }
        }
        else
        {
          *(&this->AttackNum + 281) = 3;
LABEL_29:
          this->SaleUI::UpdateSkillPanel();
        }
      }
      break;
  }
}

// 0x00461FD0
int SaleUI::SetValue(unsigned __int8 nValue)
{
  (**((void ( ***)(char *, _DWORD))&this->ml_TreasureList + 319))((char *)((char *)&this->ml_TreasureList + 1276), (_DWORD)(nValue));
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14]))(
    &this->ml_AttackList.m_scrollbar.m_texarray.m_ptex[14],
    nValue);
  (*(void ( **)(int *, _DWORD))this->ml_AttackList.m_column[2].items.capacity)(
    &this->ml_AttackList.m_column[2].items.capacity,
    nValue);
  (*(void ( **)(int *, _DWORD))this->ml_AttackList.m_column[6].items.m_needscriptdel)(
    &this->ml_AttackList.m_column[6].items.m_needscriptdel,
    nValue);
  return (**((int ( ***)(int *, _DWORD))&this->AttackNum + 18))((int *)(&this->AttackNum + 18), (_DWORD)(nValue));
}

// 0x00462080
int SaleUI::SetRange(unsigned __int8 nMax)
{
  sub_445E50((int)&this->ml_TreasureList.m_column[5].head[60]);
  sub_445E50((int)&this->ml_ResumeList.m_locksel);
  if ( this->remarkbuf[41] && *(&this->AttackNum + 286) > 0 )
    sub_445E50((int)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize);
  return sub_445E50((int)&this->ml_TreasureList.m_column[1].head[36]);
}

// 0x004620E0
int SaleUI::SendInputToRole(unsigned __int8 pData)
{
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Icon[2][1].m_fadespeed))(
    &this->m_Icon[2][1].m_fadespeed,
    pData);
  return (**(int ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(pData));
}

// 0x00462220
int SaleUI::GetValue(unsigned __int8 nIndex)
{
  _PlugInfo **p_m_ppicInfo; // edi

  p_m_ppicInfo = (_PlugInfo **)&this->m_Icon[3][1].m_ppicInfo;
  SetEnable((UICaption *)&this->m_Icon[3][1].m_ppicInfo);
  ((void ( *)(_PlugInfo **, _DWORD))(*p_m_ppicInfo)->filepos)(p_m_ppicInfo, nIndex);
  (*(void ( **)(int *, _DWORD))this->m_Icon[2][2].m_dstAlpha)(
    &this->m_Icon[2][2].m_dstAlpha,
    nIndex);
  return (**(int ( ***)(_BYTE *, _DWORD))&this->m_Icon[2][4].m_mouseoff)((_BYTE *)(&this->m_Icon[2][4].m_mouseoff), (_DWORD)(nIndex));
}

// 0x004623A0
int SaleUI::CreatePanelElements(CCBUIPanel *arg0)
{
  _WORD *v3; // ebp
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  int i; // edi
  __int16 v9; // ax
  bool v10; // sf
  bool v11; // cc
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // edi
  int *v17; // eax
  _DWORD *v18; // ecx
  int v19; // edx
  _DWORD *v20; // eax
  int v21; // edx
  int v22; // ecx
  int v23; // eax
  int v24; // edx
  int v25; // ecx
  int v26; // edi
  __int16 v27; // ax
  bool v28; // sf
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // ecx
  int v34; // edi
  int *v35; // eax
  _DWORD *v36; // ecx
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // ecx
  int v41; // edi
  _DWORD *v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // edx
  int v47; // ecx
  int v48; // edi
  int *v49; // eax
  _DWORD *v50; // ecx
  int v51; // edx
  int v52; // eax
  int v53; // edx
  int v54; // ecx
  int v55; // edi
  _DWORD *v56; // eax
  __int16 v57; // ax
  bool v58; // sf
  int v59; // eax
  int v60; // eax
  int v61; // edx
  int v62; // ecx
  int v63; // edi
  int *v64; // eax
  _DWORD *v65; // ecx
  int v66; // edx
  _DWORD *v67; // eax
  int v68; // edx
  int v69; // ecx
  int v70; // eax
  int v71; // edx
  int v72; // ecx
  int v73; // edi
  __int16 v74; // ax
  bool v75; // sf
  int v76; // eax
  int v77; // eax
  int v78; // eax
  int v79; // edx
  int v80; // ecx
  int v81; // edi
  int *v82; // eax
  _DWORD *v83; // ecx
  int v84; // edx
  int v85; // eax
  int v86; // edx
  int v87; // ecx
  int v88; // edi
  _DWORD *v89; // eax
  int v90; // eax
  int v91; // eax
  int v92; // eax
  int v93; // edx
  int v94; // ecx
  int v95; // edi
  int *v96; // eax
  _DWORD *v97; // ecx
  int v98; // edx
  int v99; // eax
  int v100; // edx
  int v101; // ecx
  int v102; // edi
  _DWORD *v103; // eax
  int v104; // eax
  __int16 v105; // cx
  __int16 v106; // dx
  int v107; // eax
  int v108; // edx
  int v109; // ecx
  int v110; // edi
  int *v111; // eax
  _DWORD *v112; // ecx
  int v113; // edx
  int v114; // eax
  int v115; // edx
  int v116; // ecx
  int v117; // edi
  _DWORD *v118; // eax
  int v119; // eax
  __int16 v120; // cx
  __int16 v121; // dx
  int v122; // eax
  int v123; // eax
  int v124; // edx
  int v125; // ecx
  int v126; // edi
  int *v127; // eax
  _DWORD *v128; // ecx
  int v129; // edx
  int v130; // eax
  int v131; // edx
  int v132; // ecx
  int v133; // edi
  _DWORD *v134; // eax
  SaleUI_SortData *v135; // ecx
  int v136; // eax
  int v137; // eax
  int v138; // edx
  int v139; // ecx
  int v140; // edi
  int *v141; // eax
  _DWORD *v142; // ecx
  int v143; // edx
  int v144; // eax
  int v145; // edx
  int v146; // ecx
  int v147; // edi
  _DWORD *v148; // eax
  int v149; // eax
  __int16 v150; // cx
  __int16 v151; // dx
  int v152; // eax
  int v153; // edx
  int v154; // ecx
  int v155; // edi
  int *v156; // eax
  _DWORD *v157; // ecx
  int v158; // edx
  int v159; // eax
  int v160; // edx
  int v161; // ecx
  int v162; // edi
  _DWORD *v163; // eax
  int v164; // eax
  __int16 v165; // cx
  __int16 v166; // dx
  int v167; // eax
  int v168; // eax
  int v169; // edx
  int v170; // ecx
  int v171; // edi
  int v172; // eax
  int v173; // edx
  int v174; // ecx
  int v175; // edi
  int v176; // eax
  int v177; // eax
  int v178; // edx
  int v179; // ecx
  int v180; // edi
  int *v181; // eax
  _DWORD *v182; // ecx
  int v183; // edx
  int v184; // eax
  int v185; // edx
  int v186; // ecx
  int v187; // edi
  _DWORD *v188; // eax
  int v189; // ecx
  int v190; // edx
  int j; // edi
  __int16 v192; // ax
  bool v193; // sf
  int v194; // eax
  int v195; // eax
  int v196; // edx
  int v197; // ecx
  int v198; // edi
  int *v199; // eax
  _DWORD *v200; // ecx
  int v201; // edx
  _DWORD *v202; // eax
  int v203; // edx
  int v204; // ecx
  int v205; // eax
  int v206; // edx
  int v207; // ecx
  int v208; // edi
  __int16 v209; // ax
  bool v210; // sf
  int v211; // eax
  int v212; // eax
  int v213; // eax
  int v214; // edx
  int v215; // ecx
  int v216; // edi
  int *v217; // eax
  _DWORD *v218; // ecx
  int v219; // edx
  int v220; // eax
  int v221; // edx
  int v222; // ecx
  int v223; // edi
  _DWORD *v224; // eax
  int v225; // eax
  int v226; // eax
  int v227; // eax
  int v228; // edx
  int v229; // ecx
  int v230; // edi
  int *v231; // eax
  _DWORD *v232; // ecx
  int v233; // edx
  int v234; // eax
  int v235; // edx
  int v236; // ecx
  int v237; // edi
  _DWORD *v238; // eax
  __int16 v239; // ax
  bool v240; // sf
  int v241; // eax
  int v242; // eax
  int v243; // edx
  int v244; // ecx
  int v245; // edi
  int *v246; // eax
  _DWORD *v247; // ecx
  int v248; // edx
  _DWORD *v249; // eax
  int v250; // edx
  int v251; // ecx
  int v252; // eax
  int v253; // edx
  int v254; // ecx
  int v255; // edi
  __int16 v256; // ax
  bool v257; // sf
  int v258; // eax
  int v259; // eax
  int v260; // eax
  int v261; // edx
  int v262; // ecx
  int v263; // edi
  int *v264; // eax
  _DWORD *v265; // ecx
  int v266; // edx
  int v267; // eax
  int v268; // edx
  int v269; // ecx
  int v270; // edi
  _DWORD *v271; // eax
  int v272; // eax
  int v273; // eax
  int v274; // eax
  int v275; // edx
  int v276; // ecx
  int v277; // edi
  int *v278; // eax
  _DWORD *v279; // ecx
  int v280; // edx
  int v281; // eax
  int v282; // edx
  int v283; // ecx
  int v284; // edi
  _DWORD *v285; // eax
  int v286; // eax
  __int16 v287; // cx
  __int16 v288; // dx
  int v289; // eax
  int v290; // edx
  int v291; // ecx
  int v292; // edi
  int *v293; // eax
  _DWORD *v294; // ecx
  int v295; // edx
  int v296; // eax
  int v297; // edx
  int v298; // ecx
  int v299; // edi
  _DWORD *v300; // eax
  int v301; // eax
  __int16 v302; // cx
  __int16 v303; // dx
  int v304; // eax
  int v305; // eax
  int v306; // edx
  int v307; // ecx
  int v308; // edi
  int *v309; // eax
  _DWORD *v310; // ecx
  int v311; // edx
  int v312; // eax
  int v313; // edx
  int v314; // ecx
  int v315; // edi
  _DWORD *v316; // eax
  int *v317; // ecx
  int v318; // eax
  int v319; // eax
  int v320; // edx
  int v321; // ecx
  int v322; // edi
  int *v323; // eax
  _DWORD *v324; // ecx
  int v325; // edx
  int v326; // eax
  int v327; // edx
  int v328; // ecx
  int v329; // edi
  _DWORD *v330; // eax
  int v331; // eax
  __int16 v332; // cx
  __int16 v333; // dx
  int v334; // eax
  int v335; // edx
  int v336; // ecx
  int v337; // edi
  int *v338; // eax
  _DWORD *v339; // ecx
  int v340; // edx
  int v341; // eax
  int v342; // edx
  int v343; // ecx
  int v344; // edi
  _DWORD *v345; // eax
  int v346; // eax
  __int16 v347; // cx
  __int16 v348; // dx
  int v349; // eax
  int v350; // eax
  int v351; // edx
  int v352; // ecx
  int v353; // edi
  int v354; // eax
  int v355; // edx
  int v356; // ecx
  int v357; // edi
  int v358; // eax
  int v359; // eax
  int v360; // edx
  int v361; // ecx
  int v362; // edi
  int *v363; // eax
  _DWORD *v364; // ecx
  int v365; // edx
  int v366; // eax
  int v367; // edx
  int v368; // ecx
  int v369; // edi
  _DWORD *v370; // eax
  int v371; // ecx
  int v372; // edx
  int k; // edi
  __int16 v374; // ax
  bool v375; // sf
  int v376; // eax
  int v377; // eax
  int v378; // edx
  int v379; // ecx
  int v380; // edi
  int *v381; // eax
  _DWORD *v382; // ecx
  int v383; // edx
  _DWORD *v384; // eax
  int v385; // edx
  int v386; // ecx
  int v387; // eax
  int v388; // edx
  int v389; // ecx
  int v390; // edi
  __int16 v391; // ax
  bool v392; // sf
  int v393; // eax
  int v394; // eax
  int v395; // eax
  int v396; // edx
  int v397; // ecx
  int v398; // edi
  int *v399; // eax
  _DWORD *v400; // ecx
  int v401; // edx
  int v402; // eax
  int v403; // edx
  int v404; // ecx
  int v405; // edi
  _DWORD *v406; // eax
  int v407; // eax
  int v408; // eax
  int v409; // eax
  int v410; // edx
  int v411; // ecx
  int v412; // edi
  int *v413; // eax
  _DWORD *v414; // ecx
  int v415; // edx
  int v416; // eax
  int v417; // edx
  int v418; // ecx
  int v419; // edi
  _DWORD *v420; // eax
  __int16 v421; // ax
  bool v422; // sf
  int v423; // eax
  int v424; // eax
  int v425; // edx
  int v426; // ecx
  int v427; // edi
  int *v428; // eax
  _DWORD *v429; // ecx
  int v430; // edx
  _DWORD *v431; // eax
  int v432; // edx
  int v433; // ecx
  int v434; // eax
  int v435; // edx
  int v436; // ecx
  int v437; // edi
  __int16 v438; // ax
  bool v439; // sf
  int v440; // eax
  int v441; // eax
  int v442; // eax
  int v443; // edx
  int v444; // ecx
  int v445; // edi
  int *v446; // eax
  _DWORD *v447; // ecx
  int v448; // edx
  int v449; // eax
  int v450; // edx
  int v451; // ecx
  int v452; // edi
  _DWORD *v453; // eax
  int v454; // eax
  int v455; // eax
  int v456; // eax
  int v457; // edx
  int v458; // ecx
  int v459; // edi
  int *v460; // eax
  _DWORD *v461; // ecx
  int v462; // edx
  int v463; // eax
  int v464; // edx
  int v465; // ecx
  int v466; // edi
  _DWORD *v467; // eax
  int v468; // eax
  __int16 v469; // cx
  __int16 v470; // dx
  int v471; // eax
  int v472; // edx
  int v473; // ecx
  int v474; // edi
  int *v475; // eax
  _DWORD *v476; // ecx
  int v477; // edx
  int v478; // eax
  int v479; // edx
  int v480; // ecx
  int v481; // edi
  _DWORD *v482; // eax
  int v483; // eax
  __int16 v484; // cx
  __int16 v485; // dx
  int v486; // eax
  int v487; // eax
  int v488; // edx
  int v489; // ecx
  int v490; // edi
  int *v491; // eax
  _DWORD *v492; // ecx
  int v493; // edx
  int v494; // eax
  int v495; // edx
  int v496; // ecx
  int v497; // edi
  _DWORD *v498; // eax
  int *v499; // ecx
  int v500; // eax
  int v501; // eax
  int v502; // edx
  int v503; // ecx
  int v504; // edi
  int *v505; // eax
  _DWORD *v506; // ecx
  int v507; // edx
  int v508; // eax
  int v509; // edx
  int v510; // ecx
  int v511; // edi
  _DWORD *v512; // eax
  int v513; // eax
  __int16 v514; // cx
  __int16 v515; // dx
  int v516; // eax
  int v517; // edx
  int v518; // ecx
  int v519; // edi
  int *v520; // eax
  _DWORD *v521; // ecx
  int v522; // edx
  int v523; // eax
  int v524; // edx
  int v525; // ecx
  int v526; // edi
  _DWORD *v527; // eax
  int v528; // eax
  __int16 v529; // cx
  __int16 v530; // dx
  int v531; // eax
  int v532; // eax
  int v533; // edx
  int v534; // ecx
  int v535; // edi
  int v536; // eax
  int v537; // edx
  int v538; // ecx
  int v539; // edi
  int v540; // eax
  int v541; // eax
  int v542; // edx
  int v543; // ecx
  int v544; // edi
  int *v545; // eax
  _DWORD *v546; // ecx
  int v547; // edx
  int v548; // eax
  int v549; // edx
  int v550; // ecx
  int v551; // edi
  _DWORD *v552; // eax
  int v553; // ecx
  int v554; // edx
  int m; // edi
  __int16 v556; // ax
  bool v557; // sf
  int v558; // eax
  int v559; // eax
  int v560; // edx
  int v561; // ecx
  int v562; // edi
  int *v563; // eax
  _DWORD *v564; // ecx
  int v565; // edx
  _DWORD *v566; // eax
  int v567; // eax
  int v568; // edx
  int v569; // ecx
  int v570; // edi
  __int16 v571; // ax
  bool v572; // sf
  int v573; // eax
  int v574; // eax
  int v575; // eax
  int v576; // edx
  int v577; // ecx
  int v578; // edi
  int *v579; // eax
  _DWORD *v580; // ecx
  int v581; // edx
  int v582; // eax
  int v583; // edx
  int v584; // ecx
  int v585; // edi
  _DWORD *v586; // eax
  int v587; // eax
  int v588; // eax
  int v589; // eax
  int v590; // edx
  int v591; // ecx
  int v592; // edi
  int *v593; // eax
  _DWORD *v594; // ecx
  int v595; // edx
  int v596; // eax
  int v597; // edx
  int v598; // ecx
  int v599; // edi
  _DWORD *v600; // eax
  __int16 v601; // ax
  bool v602; // sf
  int v603; // eax
  int v604; // eax
  int v605; // edx
  int v606; // ecx
  int v607; // edi
  int *v608; // eax
  _DWORD *v609; // ecx
  int v610; // edx
  _DWORD *v611; // eax
  int v612; // eax
  int v613; // edx
  int v614; // ecx
  int v615; // edi
  __int16 v616; // ax
  bool v617; // sf
  int v618; // eax
  int v619; // eax
  int v620; // eax
  int v621; // edx
  int v622; // ecx
  int v623; // edi
  int *v624; // eax
  _DWORD *v625; // ecx
  int v626; // edx
  int v627; // eax
  int v628; // edx
  int v629; // ecx
  int v630; // edi
  _DWORD *v631; // eax
  int v632; // eax
  int v633; // eax
  int v634; // eax
  int v635; // edx
  int v636; // ecx
  int v637; // edi
  int *v638; // eax
  _DWORD *v639; // ecx
  int v640; // edx
  int v641; // eax
  int v642; // edx
  int v643; // ecx
  int v644; // edi
  _DWORD *v645; // eax
  int v646; // eax
  __int16 v647; // cx
  __int16 v648; // dx
  int v649; // eax
  int v650; // edx
  int v651; // ecx
  int v652; // edi
  int *v653; // eax
  _DWORD *v654; // ecx
  int v655; // edx
  int v656; // eax
  int v657; // edx
  int v658; // ecx
  int v659; // edi
  _DWORD *v660; // eax
  int v661; // eax
  __int16 v662; // cx
  __int16 v663; // dx
  int v664; // eax
  int v665; // eax
  int v666; // edx
  int v667; // ecx
  int v668; // edi
  int *v669; // eax
  _DWORD *v670; // ecx
  int v671; // edx
  int v672; // eax
  int v673; // edx
  int v674; // ecx
  int v675; // edi
  _DWORD *v676; // eax
  SaleUI_SortData *v677; // ecx
  int v678; // eax
  int v679; // eax
  int v680; // edx
  int v681; // ecx
  int v682; // edi
  int *v683; // eax
  _DWORD *v684; // ecx
  int v685; // edx
  int v686; // eax
  int v687; // edx
  int v688; // ecx
  int v689; // edi
  _DWORD *v690; // eax
  int v691; // eax
  __int16 v692; // cx
  __int16 v693; // dx
  int v694; // eax
  int v695; // edx
  int v696; // ecx
  int v697; // edi
  int *v698; // eax
  _DWORD *v699; // ecx
  int v700; // edx
  int v701; // eax
  int v702; // edx
  int v703; // ecx
  int v704; // edi
  _DWORD *v705; // eax
  int v706; // eax
  __int16 v707; // cx
  __int16 v708; // dx
  int v709; // eax
  int v710; // eax
  int v711; // edx
  int v712; // ecx
  int v713; // edi
  int v714; // eax
  int v715; // edx
  int v716; // ecx
  int v717; // edi
  int v718; // eax
  int v719; // eax
  int v720; // edx
  int v721; // ecx
  int v722; // edi
  int *v723; // eax
  _DWORD *v724; // ecx
  int v725; // edx
  int v726; // eax
  int v727; // edx
  int v728; // ecx
  int v729; // edi
  _DWORD *v730; // eax
  int v731; // ecx
  int v732; // edx
  int n; // edi
  __int16 v734; // ax
  bool v735; // sf
  int v736; // eax
  int v737; // eax
  int v738; // edx
  int v739; // ecx
  int v740; // edi
  int *v741; // eax
  _DWORD *v742; // ecx
  int v743; // edx
  _DWORD *v744; // eax
  int v745; // eax
  int v746; // edx
  int v747; // ecx
  int v748; // edi
  __int16 v749; // ax
  bool v750; // sf
  int v751; // eax
  int v752; // eax
  int v753; // eax
  int v754; // edx
  int v755; // ecx
  int v756; // edi
  int *v757; // eax
  _DWORD *v758; // ecx
  int v759; // edx
  int v760; // eax
  int v761; // edx
  int v762; // ecx
  int v763; // edi
  _DWORD *v764; // eax
  int v765; // eax
  int v766; // eax
  int v767; // eax
  int v768; // edx
  int v769; // ecx
  int v770; // edi
  int *v771; // eax
  _DWORD *v772; // ecx
  int v773; // edx
  int v774; // eax
  int v775; // edx
  int v776; // ecx
  int v777; // edi
  _DWORD *v778; // eax
  __int16 v779; // ax
  bool v780; // sf
  int v781; // eax
  int v782; // eax
  int v783; // edx
  int v784; // ecx
  int v785; // edi
  int *v786; // eax
  _DWORD *v787; // ecx
  int v788; // edx
  _DWORD *v789; // eax
  int v790; // eax
  int v791; // edx
  int v792; // ecx
  int v793; // edi
  __int16 v794; // ax
  int v795; // eax
  int v796; // eax
  int v797; // edx
  int v798; // ecx
  int v799; // edi
  int *v800; // eax
  _DWORD *v801; // ecx
  int v802; // edx
  int v803; // eax
  int v804; // edx
  int v805; // ecx
  int v806; // edi
  _DWORD *v807; // eax
  int v808; // eax
  int v809; // eax
  int v810; // edx
  int v811; // ecx
  int v812; // edi
  int *v813; // eax
  _DWORD *v814; // ecx
  int v815; // edx
  int v816; // eax
  int v817; // edx
  int v818; // ecx
  int v819; // edi
  _DWORD *v820; // eax
  int v821; // eax
  __int16 v822; // cx
  __int16 v823; // dx
  int v824; // eax
  int v825; // edx
  int v826; // ecx
  int v827; // edi
  int *v828; // eax
  _DWORD *v829; // ecx
  int v830; // edx
  int v831; // eax
  int v832; // edx
  int v833; // ecx
  int v834; // edi
  _DWORD *v835; // eax
  int v836; // eax
  __int16 v837; // cx
  __int16 v838; // dx
  int v839; // eax
  int v840; // eax
  int v841; // edx
  int v842; // ecx
  int v843; // edi
  int *v844; // eax
  _DWORD *v845; // ecx
  int v846; // edx
  int v847; // eax
  int v848; // edx
  int v849; // ecx
  int v850; // edi
  _DWORD *v851; // eax
  int *v852; // ecx
  int v853; // eax
  int v854; // eax
  int v855; // edx
  int v856; // ecx
  int v857; // edi
  int *v858; // eax
  _DWORD *v859; // ecx
  int v860; // edx
  int v861; // eax
  int v862; // edx
  int v863; // ecx
  int v864; // edi
  _DWORD *v865; // eax
  int v866; // eax
  __int16 v867; // cx
  __int16 v868; // dx
  int v869; // eax
  int v870; // edx
  int v871; // ecx
  int v872; // edi
  int *v873; // eax
  _DWORD *v874; // ecx
  int v875; // edx
  int v876; // eax
  int v877; // edx
  int v878; // ecx
  int v879; // edi
  _DWORD *v880; // eax
  int v881; // eax
  __int16 v882; // cx
  __int16 v883; // dx
  int v884; // eax
  int v885; // eax
  int v886; // edx
  int v887; // ecx
  int v888; // edi
  void *v889; // eax
  int v890; // eax
  void *v891; // eax
  int v892; // eax
  int *v893; // edx
  void *v894; // eax
  int v895; // eax
  CCBUI *v896; // ecx
  int v897; // eax
  int ii; // edi
  int v899; // eax
  int v900; // eax
  void *v901; // eax
  int v902; // eax
  int *v903; // edx
  void *v904; // eax
  int v905; // eax
  int v906; // eax
  void *v907; // eax
  int v908; // eax
  int *v909; // edx
  void *v910; // eax
  int v911; // eax
  int v912; // eax
  __int16 v913; // cx
  __int16 v914; // dx
  int v915; // eax
  int v916; // eax
  int v917; // eax
  __int16 v918; // cx
  __int16 v919; // dx
  void *v920; // eax
  int v921; // eax
  int *v922; // edx
  void *v923; // eax
  SaleUI_SortData *v924; // ecx
  void *v925; // eax
  int v926; // eax
  int *v927; // edx
  void *v928; // eax
  int v929; // eax
  __int16 v930; // cx
  __int16 v931; // dx
  int v932; // eax
  int v933; // eax
  int v934; // eax
  __int16 v935; // cx
  __int16 v936; // dx
  void *v937; // eax
  int v938; // eax
  int *v939; // edx
  void *v940; // eax
  void *v941; // eax
  int v942; // eax
  int *v943; // edx
  void *v944; // eax
  int result; // eax
  _WORD *v946; // [esp+0x24] [ebp-D3Ch]
  int v947; // [esp+0x28] [ebp-D38h]
  int v948; // [esp+0x2C] [ebp-D34h]
  int v949; // [esp+0x30] [ebp-D30h]
  int v950; // [esp+0x34] [ebp-D2Ch]
  int v951; // [esp+0x38] [ebp-D28h]
  int v952; // [esp+0x3C] [ebp-D24h]
  int v953; // [esp+0x40] [ebp-D20h]
  int v954; // [esp+0x44] [ebp-D1Ch]
  int v955; // [esp+0x48] [ebp-D18h]
  int v956; // [esp+0x4C] [ebp-D14h]
  _DWORD v957[4]; // [esp+0x50] [ebp-D10h] BYREF
  _DWORD v958[4]; // [esp+0x60] [ebp-D00h] BYREF
  _DWORD v959[4]; // [esp+0x70] [ebp-CF0h] BYREF
  _DWORD v960[4]; // [esp+0x80] [ebp-CE0h] BYREF
  _DWORD v961[4]; // [esp+0x90] [ebp-CD0h] BYREF
  _DWORD v962[4]; // [esp+A0h] [ebp-CC0h] BYREF
  _DWORD v963[4]; // [esp+B0h] [ebp-CB0h] BYREF
  _DWORD v964[4]; // [esp+C0h] [ebp-CA0h] BYREF
  _DWORD v965[4]; // [esp+D0h] [ebp-C90h] BYREF
  _DWORD v966[4]; // [esp+E0h] [ebp-C80h] BYREF
  _DWORD v967[4]; // [esp+F0h] [ebp-C70h] BYREF
  _DWORD v968[4]; // [esp+0x100] [ebp-C60h] BYREF
  _DWORD v969[4]; // [esp+0x110] [ebp-C50h] BYREF
  _DWORD v970[4]; // [esp+0x120] [ebp-C40h] BYREF
  _DWORD v971[4]; // [esp+0x130] [ebp-C30h] BYREF
  _DWORD v972[4]; // [esp+0x140] [ebp-C20h] BYREF
  _DWORD v973[4]; // [esp+0x150] [ebp-C10h] BYREF
  _DWORD v974[4]; // [esp+0x160] [ebp-C00h] BYREF
  _DWORD v975[4]; // [esp+0x170] [ebp-BF0h] BYREF
  _DWORD v976[4]; // [esp+0x180] [ebp-BE0h] BYREF
  _DWORD v977[4]; // [esp+0x190] [ebp-BD0h] BYREF
  _DWORD v978[4]; // [esp+0x1A0] [ebp-BC0h] BYREF
  _DWORD v979[4]; // [esp+0x1B0] [ebp-BB0h] BYREF
  _DWORD v980[4]; // [esp+0x1C0] [ebp-BA0h] BYREF
  _DWORD v981[4]; // [esp+0x1D0] [ebp-B90h] BYREF
  _DWORD v982[4]; // [esp+0x1E0] [ebp-B80h] BYREF
  _DWORD v983[4]; // [esp+0x1F0] [ebp-B70h] BYREF
  _DWORD v984[4]; // [esp+0x200] [ebp-B60h] BYREF
  _DWORD v985[4]; // [esp+0x210] [ebp-B50h] BYREF
  _DWORD v986[4]; // [esp+0x220] [ebp-B40h] BYREF
  _DWORD v987[4]; // [esp+0x230] [ebp-B30h] BYREF
  _DWORD v988[4]; // [esp+0x240] [ebp-B20h] BYREF
  _DWORD v989[4]; // [esp+0x250] [ebp-B10h] BYREF
  _DWORD a2[4]; // [esp+0x260] [ebp-B00h] BYREF
  _DWORD v991[4]; // [esp+0x270] [ebp-AF0h] BYREF
  _DWORD v992[4]; // [esp+0x280] [ebp-AE0h] BYREF
  _DWORD v993[4]; // [esp+0x290] [ebp-AD0h] BYREF
  _DWORD v994[4]; // [esp+0x2A0] [ebp-AC0h] BYREF
  _DWORD v995[4]; // [esp+0x2B0] [ebp-AB0h] BYREF
  _DWORD v996[4]; // [esp+0x2C0] [ebp-AA0h] BYREF
  _DWORD v997[4]; // [esp+0x2D0] [ebp-A90h] BYREF
  _DWORD v998[4]; // [esp+0x2E0] [ebp-A80h] BYREF
  _DWORD v999[4]; // [esp+0x2F0] [ebp-A70h] BYREF
  _DWORD v1000[4]; // [esp+0x300] [ebp-A60h] BYREF
  _DWORD v1001[4]; // [esp+0x310] [ebp-A50h] BYREF
  _DWORD v1002[4]; // [esp+0x320] [ebp-A40h] BYREF
  _DWORD v1003[4]; // [esp+0x330] [ebp-A30h] BYREF
  _DWORD v1004[4]; // [esp+0x340] [ebp-A20h] BYREF
  _DWORD v1005[4]; // [esp+0x350] [ebp-A10h] BYREF
  _DWORD v1006[4]; // [esp+0x360] [ebp-A00h] BYREF
  _DWORD v1007[4]; // [esp+0x370] [ebp-0x9F0] BYREF
  _DWORD v1008[4]; // [esp+0x380] [ebp-0x9E0] BYREF
  _DWORD v1009[4]; // [esp+0x390] [ebp-0x9D0] BYREF
  _DWORD v1010[4]; // [esp+0x3A0] [ebp-0x9C0] BYREF
  _DWORD v1011[4]; // [esp+0x3B0] [ebp-0x9B0] BYREF
  _DWORD v1012[4]; // [esp+0x3C0] [ebp-0x9A0] BYREF
  _DWORD v1013[4]; // [esp+0x3D0] [ebp-0x990] BYREF
  _DWORD v1014[4]; // [esp+0x3E0] [ebp-0x980] BYREF
  _DWORD v1015[4]; // [esp+0x3F0] [ebp-0x970] BYREF
  _DWORD v1016[4]; // [esp+0x400] [ebp-0x960] BYREF
  _DWORD v1017[4]; // [esp+0x410] [ebp-0x950] BYREF
  _DWORD v1018[4]; // [esp+0x420] [ebp-0x940] BYREF
  _DWORD v1019[4]; // [esp+0x430] [ebp-0x930] BYREF
  _DWORD v1020[4]; // [esp+0x440] [ebp-0x920] BYREF
  _DWORD v1021[4]; // [esp+0x450] [ebp-0x910] BYREF
  _DWORD v1022[4]; // [esp+0x460] [ebp-0x900] BYREF
  _DWORD v1023[4]; // [esp+0x470] [ebp-0x8F0] BYREF
  _DWORD v1024[4]; // [esp+0x480] [ebp-0x8E0] BYREF
  _DWORD v1025[4]; // [esp+0x490] [ebp-0x8D0] BYREF
  _DWORD v1026[4]; // [esp+0x4A0] [ebp-0x8C0] BYREF
  _DWORD v1027[4]; // [esp+0x4B0] [ebp-0x8B0] BYREF
  _DWORD v1028[4]; // [esp+0x4C0] [ebp-0x8A0] BYREF
  _DWORD v1029[4]; // [esp+0x4D0] [ebp-0x890] BYREF
  _DWORD v1030[4]; // [esp+0x4E0] [ebp-0x880] BYREF
  _DWORD v1031[4]; // [esp+0x4F0] [ebp-0x870] BYREF
  _DWORD v1032[4]; // [esp+0x500] [ebp-0x860] BYREF
  _DWORD v1033[7]; // [esp+0x510] [ebp-0x850] BYREF
  int v1034; // [esp+0x52C] [ebp-0x834]
  int v1035; // [esp+0x53C] [ebp-0x824]
  int v1036; // [esp+0x54C] [ebp-0x814]
  int v1037; // [esp+0x55C] [ebp-0x804]
  int v1038; // [esp+0x56C] [ebp-0x7F4]
  int v1039; // [esp+0x57C] [ebp-0x7E4]
  int v1040; // [esp+0x58C] [ebp-0x7D4]
  int v1041; // [esp+0x59C] [ebp-0x7C4]
  int v1042; // [esp+0x5AC] [ebp-0x7B4]
  int v1043; // [esp+0x5BC] [ebp-0x7A4]
  int v1044; // [esp+0x5CC] [ebp-0x794]
  int v1045; // [esp+0x5DC] [ebp-0x784]
  int v1046; // [esp+0x5EC] [ebp-0x774]
  int v1047; // [esp+0x5FC] [ebp-0x764]
  int v1048; // [esp+0x60C] [ebp-0x754]
  int v1049; // [esp+0x61C] [ebp-0x744]
  int v1050; // [esp+0x62C] [ebp-0x734]
  int v1051; // [esp+0x63C] [ebp-0x724]
  int v1052; // [esp+0x64C] [ebp-0x714]
  int v1053; // [esp+0x65C] [ebp-0x704]
  int v1054; // [esp+0x66C] [ebp-0x6F4]
  int v1055; // [esp+0x67C] [ebp-0x6E4]
  int v1056; // [esp+0x68C] [ebp-0x6D4]
  int v1057; // [esp+0x69C] [ebp-0x6C4]
  int v1058; // [esp+0x6AC] [ebp-0x6B4]
  int v1059; // [esp+0x6BC] [ebp-0x6A4]
  int v1060; // [esp+0x6CC] [ebp-0x694]
  int v1061; // [esp+0x6DC] [ebp-0x684]
  int v1062; // [esp+0x6EC] [ebp-0x674]
  int v1063; // [esp+0x6FC] [ebp-0x664]
  int v1064; // [esp+0x70C] [ebp-0x654]
  int v1065; // [esp+0x71C] [ebp-0x644]
  int v1066; // [esp+0x72C] [ebp-0x634]
  int v1067; // [esp+0x73C] [ebp-0x624]
  int v1068; // [esp+0x74C] [ebp-0x614]
  int v1069; // [esp+0x75C] [ebp-0x604]
  int v1070; // [esp+0x76C] [ebp-0x5F4]
  int v1071; // [esp+0x77C] [ebp-0x5E4]
  int v1072; // [esp+0x78C] [ebp-0x5D4]
  int v1073; // [esp+0x79C] [ebp-0x5C4]
  int v1074; // [esp+0x7AC] [ebp-0x5B4]
  int v1075; // [esp+0x7BC] [ebp-0x5A4]
  int v1076; // [esp+0x7CC] [ebp-0x594]
  int v1077; // [esp+0x7DC] [ebp-0x584]
  int v1078; // [esp+0x7EC] [ebp-0x574]
  int v1079; // [esp+0x7FC] [ebp-0x564]
  int v1080; // [esp+0x80C] [ebp-0x554]
  int v1081; // [esp+0x81C] [ebp-0x544]
  int v1082; // [esp+0x82C] [ebp-0x534]
  int v1083; // [esp+0x83C] [ebp-0x524]
  int v1084; // [esp+0x84C] [ebp-0x514]
  int v1085; // [esp+0x85C] [ebp-0x504]
  int v1086; // [esp+0x86C] [ebp-0x4F4]
  int v1087; // [esp+0x87C] [ebp-0x4E4]
  int v1088; // [esp+0x88C] [ebp-0x4D4]
  int v1089; // [esp+0x89C] [ebp-0x4C4]
  int v1090; // [esp+0x8AC] [ebp-0x4B4]
  int v1091; // [esp+0x8BC] [ebp-0x4A4]
  int v1092; // [esp+0x8CC] [ebp-0x494]
  int v1093; // [esp+0x8DC] [ebp-0x484]
  int v1094; // [esp+0x8EC] [ebp-0x474]
  int v1095; // [esp+0x8FC] [ebp-0x464]
  int v1096; // [esp+0x90C] [ebp-0x454]
  int v1097; // [esp+0x91C] [ebp-0x444]
  int v1098; // [esp+0x92C] [ebp-0x434]
  int v1099; // [esp+0x93C] [ebp-0x424]
  int v1100; // [esp+0x94C] [ebp-0x414]
  int v1101; // [esp+0x95C] [ebp-0x404]
  int v1102; // [esp+0x96C] [ebp-0x3F4]
  int v1103; // [esp+0x97C] [ebp-0x3E4]
  int v1104; // [esp+0x98C] [ebp-0x3D4]
  int v1105; // [esp+0x99C] [ebp-0x3C4]
  int v1106; // [esp+0x9AC] [ebp-0x3B4]
  int v1107; // [esp+0x9BC] [ebp-0x3A4]
  int v1108; // [esp+0x9CC] [ebp-0x394]
  int v1109; // [esp+0x9DC] [ebp-0x384]
  int v1110; // [esp+0x9EC] [ebp-0x374]
  int v1111; // [esp+0x9FC] [ebp-0x364]
  int v1112; // [esp+A0Ch] [ebp-0x354]
  int v1113; // [esp+A1Ch] [ebp-0x344]
  int v1114; // [esp+A2Ch] [ebp-0x334]
  int v1115; // [esp+A3Ch] [ebp-0x324]
  int v1116; // [esp+A4Ch] [ebp-0x314]
  int v1117; // [esp+A5Ch] [ebp-0x304]
  int v1118; // [esp+A6Ch] [ebp-0x2F4]
  int v1119; // [esp+A7Ch] [ebp-0x2E4]
  int v1120; // [esp+A8Ch] [ebp-0x2D4]
  int v1121; // [esp+A9Ch] [ebp-0x2C4]
  int v1122; // [esp+AACh] [ebp-0x2B4]
  int v1123; // [esp+ABCh] [ebp-0x2A4]
  int v1124; // [esp+ACCh] [ebp-0x294]
  int v1125; // [esp+ADCh] [ebp-0x284]
  int v1126; // [esp+AECh] [ebp-0x274]
  int v1127; // [esp+AFCh] [ebp-0x264]
  int v1128; // [esp+B0Ch] [ebp-0x254]
  int v1129; // [esp+B1Ch] [ebp-0x244]
  int v1130; // [esp+B2Ch] [ebp-0x234]
  int v1131; // [esp+B3Ch] [ebp-0x224]
  int v1132; // [esp+B4Ch] [ebp-0x214]
  int v1133; // [esp+B5Ch] [ebp-0x204]
  int v1134; // [esp+B6Ch] [ebp-0x1F4]
  int v1135; // [esp+B7Ch] [ebp-0x1E4]
  int v1136; // [esp+B8Ch] [ebp-0x1D4]
  int v1137; // [esp+B9Ch] [ebp-0x1C4]
  int v1138; // [esp+BACh] [ebp-0x1B4]
  int v1139; // [esp+BBCh] [ebp-0x1A4]
  int v1140; // [esp+BCCh] [ebp-0x194]
  int v1141; // [esp+BDCh] [ebp-0x184]
  int v1142; // [esp+BECh] [ebp-0x174]
  int v1143; // [esp+BFCh] [ebp-0x164]
  int v1144; // [esp+C0Ch] [ebp-0x154]
  int v1145; // [esp+C1Ch] [ebp-0x144]
  int v1146; // [esp+C2Ch] [ebp-0x134]
  int v1147; // [esp+C3Ch] [ebp-0x124]
  int v1148; // [esp+C4Ch] [ebp-0x114]
  int v1149; // [esp+C5Ch] [ebp-0x104]
  int v1150; // [esp+C6Ch] [ebp-F4h]
  PlayerMgr v1151; // [esp+C70h] [ebp-F0h] BYREF
  PlayerMgr v1152; // [esp+C80h] [ebp-E0h] BYREF
  PlayerMgr v1153; // [esp+C90h] [ebp-D0h] BYREF
  PlayerMgr v1154; // [esp+CA0h] [ebp-C0h] BYREF
  PlayerMgr v1155; // [esp+CB0h] [ebp-B0h] BYREF
  PlayerMgr v1156; // [esp+CC0h] [ebp-A0h] BYREF
  PlayerMgr v1157; // [esp+CD0h] [ebp-0x90] BYREF
  PlayerMgr v1158; // [esp+CE0h] [ebp-0x80] BYREF
  PlayerMgr v1159; // [esp+CF0h] [ebp-0x70] BYREF
  PlayerMgr v1160; // [esp+D00h] [ebp-0x60] BYREF
  PlayerMgr v1161; // [esp+D10h] [ebp-0x50] BYREF
  PlayerMgr v1162; // [esp+D20h] [ebp-0x40] BYREF
  PlayerMgr v1163; // [esp+D30h] [ebp-0x30] BYREF
  PlayerMgr v1164; // [esp+D40h] [ebp-0x20] BYREF
  int nCol[4]; // [esp+D50h] [ebp-0x10] BYREF

  v3 = (_WORD *)*(&this->dwWeaponWU + (_DWORD)arg0 + 3666);
  v946 = (_WORD *)v3;
  if ( *((CCBUIPanel **)&this->m_bWPXS + 1258) != arg0 )
  {
    memset(&this->m_bWPXS + 1198, 0, 0xF0u);
    memset(&this->m_bWPXS + 1259, 0, 0xF0u);
    *(&this->m_bWPXS + 1258) = (int)arg0;
  }
  *(_DWORD *)&this->remarkbuf[20] = 0;
  while ( 2 )
  {
    if ( !this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
      goto LABEL_406;
    *(_DWORD *)&this->remarkbuf[24] = 0;
    do
    {
      (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4])(
        &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4],
        0);
      *(_DWORD *)&this->remarkbuf[28] = 0;
      do
      {
        (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                                                                              + 4
                                                                              + 304 * *(_DWORD *)&this->remarkbuf[24]
                                                                              + 38 * *(_DWORD *)&this->remarkbuf[28]])((SaleUI_SortData *)(&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                           + 4
                           + 304 * *(_DWORD *)&this->remarkbuf[24]
                           + 38 * *(_DWORD *)&this->remarkbuf[28]]), (_DWORD)(0));
        v4 = *(_DWORD *)&this->remarkbuf[28] + 1;
        *(_DWORD *)&this->remarkbuf[28] = v4;
      }
      while ( v4 < 8 );
      v5 = *(_DWORD *)&this->remarkbuf[24] + 1;
      *(_DWORD *)&this->remarkbuf[24] = v5;
    }
    while ( v5 < 6 );
    switch ( *((_BYTE *)v3 + 612) )
    {
      case 7:
        v6 = *(_DWORD *)&this->remarkbuf[20];
        if ( !*((_BYTE *)v3 + v6 + 614) )
          goto LABEL_406;
        v7 = *(&this->AttackNum + 289);
        if ( !g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * v6] )
        {
          LOBYTE(v955) = *(_BYTE *)(v7 + 3284);
          (((UIPushButton *)&this->m_NotesNull[54 * v6 + 277][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Cloth.tga", v955);
          for ( i = 0; i < 8; ++i )
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[412][1824
                                                                                  * *(_DWORD *)&this->remarkbuf[20]
                                                                                  + 4
                                                                                  + 38 * i])((SaleUI_SortData *)(&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20] + 4 + 38 * i]), (_DWORD)(0));
          v9 = v3[325];
          v10 = v9 < 0;
          v11 = v9 <= 0;
          v12 = *(_DWORD *)&this->remarkbuf[20];
          if ( v11 )
          {
            if ( !v10 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v12 + 5036) = 0;
LABEL_20:
              v27 = v946[327];
              v28 = v27 < 0;
              v11 = v27 <= 0;
              v29 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                v43 = 3 * v29;
                if ( v28 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v43 + 5041) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5037) = 0;
                  v44 = *(_DWORD *)&this->remarkbuf[20];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v44 + 4796) )
                  {
                    v960[0] = *(&this->m_bWPXS + 192 * v44 + 262);
                    v960[1] = *(&this->m_bWPXS + 192 * v44 + 263);
                    v960[2] = *(&this->m_bWPXS + 192 * v44 + 264);
                    v960[3] = *(&this->m_bWPXS + 192 * v44 + 265);
                    (((UIWnd *)&this->m_sort[450][1824 * v44 + 4]))->UIWnd::sub_445FA0(v960);
                    v45 = *(_DWORD *)&this->remarkbuf[20];
                    v46 = *(&this->m_bWPXS + 192 * v45 + 262);
                    v47 = *(&this->m_bWPXS + 192 * v45 + 263);
                    v48 = *(&this->m_bWPXS + 192 * v45 + 264);
                    v1102 = *(&this->m_bWPXS + 192 * v45 + 265);
                    v49 = (int *)(&this->m_bWPXS + 624 * v45 + 2344);
                    v49[2] = v47;
                    v50 = (_DWORD *)v49 + 1;
                    v49[3] = v48;
                    v49[1] = v46;
                    v51 = v1102;
                  }
                  else
                  {
                    v1024[0] = *(&this->m_bWPXS + 192 * v44 + 254);
                    v1024[1] = *(&this->m_bWPXS + 192 * v44 + 255);
                    v1024[2] = *(&this->m_bWPXS + 192 * v44 + 256);
                    v1024[3] = *(&this->m_bWPXS + 192 * v44 + 257);
                    (((UIWnd *)&this->m_sort[450][1824 * v44 + 4]))->UIWnd::sub_445FA0(v1024);
                    v52 = *(_DWORD *)&this->remarkbuf[20];
                    v53 = *(&this->m_bWPXS + 192 * v52 + 254);
                    v54 = *(&this->m_bWPXS + 192 * v52 + 255);
                    v55 = *(&this->m_bWPXS + 192 * v52 + 256);
                    v1040 = *(&this->m_bWPXS + 192 * v52 + 257);
                    v49 = (int *)(&this->m_bWPXS + 624 * v52 + 2344);
                    v49[2] = v54;
                    v50 = (_DWORD *)v49 + 1;
                    v49[3] = v55;
                    v49[1] = v53;
                    v51 = v1040;
                  }
                  v49[4] = v51;
                  v56 = (_DWORD *)v49 + 5;
                  *v56 = *v50;
                  v56[1] = (unsigned long)v50[1];
                  v56[2] = (unsigned long)v50[2];
                  v56[3] = (unsigned long)v50[3];
                  (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[450][1824
                                                                                     * *(_DWORD *)&this->remarkbuf[20]
                                                                                     + 4])((SaleUI_SortData *)(&this->m_sort[450][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]), (int)(1));
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v43 + 5037) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v29 + 5037) = 1;
                v30 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v30 + 4792) )
                {
                  a2[0] = *(&this->m_bWPXS + 192 * v30 + 246);
                  a2[1] = *(&this->m_bWPXS + 192 * v30 + 247);
                  a2[2] = *(&this->m_bWPXS + 192 * v30 + 248);
                  a2[3] = *(&this->m_bWPXS + 192 * v30 + 249);
                  (((UIWnd *)&this->m_sort[420][1824 * v30 + 2]))->UIWnd::sub_445FA0(a2);
                  v31 = *(_DWORD *)&this->remarkbuf[20];
                  v32 = *(&this->m_bWPXS + 192 * v31 + 246);
                  v33 = *(&this->m_bWPXS + 192 * v31 + 247);
                  v34 = *(&this->m_bWPXS + 192 * v31 + 248);
                  v1146 = *(&this->m_bWPXS + 192 * v31 + 249);
                  v35 = (int *)(&this->m_bWPXS + 624 * v31 + 2292);
                  v35[2] = v33;
                  v36 = (_DWORD *)v35 + 1;
                  v35[3] = v34;
                  v35[1] = v32;
                  v37 = v1146;
                }
                else
                {
                  v996[0] = *(&this->m_bWPXS + 192 * v30 + 238);
                  v996[1] = *(&this->m_bWPXS + 192 * v30 + 239);
                  v996[2] = *(&this->m_bWPXS + 192 * v30 + 240);
                  v996[3] = *(&this->m_bWPXS + 192 * v30 + 241);
                  (((UIWnd *)&this->m_sort[420][1824 * v30 + 2]))->UIWnd::sub_445FA0(v996);
                  v38 = *(_DWORD *)&this->remarkbuf[20];
                  v39 = *(&this->m_bWPXS + 192 * v38 + 238);
                  v40 = *(&this->m_bWPXS + 192 * v38 + 239);
                  v41 = *(&this->m_bWPXS + 192 * v38 + 240);
                  v1038 = *(&this->m_bWPXS + 192 * v38 + 241);
                  v35 = (int *)(&this->m_bWPXS + 624 * v38 + 2292);
                  v35[2] = v40;
                  v36 = (_DWORD *)v35 + 1;
                  v35[3] = v41;
                  v35[1] = v39;
                  v37 = v1038;
                }
                v35[4] = v37;
                v42 = (_DWORD *)v35 + 5;
                *v42 = *v36;
                v42[1] = (unsigned long)v36[1];
                v42[2] = (unsigned long)v36[2];
                v42[3] = (unsigned long)v36[3];
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[420][1824
                                                                                   * *(_DWORD *)&this->remarkbuf[20]
                                                                                   + 2])((SaleUI_SortData *)(&this->m_sort[420][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (int)(1));
              }
              v57 = v946[326];
              v58 = v57 < 0;
              v11 = v57 <= 0;
              v59 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                if ( !v58 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v59 + 5038) = 0;
                  goto LABEL_37;
                }
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[458][1824 * v59 + 2])((SaleUI_SortData *)(&this->m_sort[458][1824 * v59 + 2]), (int)(1));
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4798) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5042) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5038) = 0;
                v70 = *(_DWORD *)&this->remarkbuf[20];
                v71 = *(&this->m_bWPXS + 192 * v70 + 262);
                v72 = *(&this->m_bWPXS + 192 * v70 + 263);
                v73 = *(&this->m_bWPXS + 192 * v70 + 264);
                v1042 = *(&this->m_bWPXS + 192 * v70 + 265);
                v64 = (int *)(&this->m_bWPXS + 624 * v70 + 2357);
                v64[2] = v72;
                v65 = (_DWORD *)v64 + 1;
                v64[3] = v73;
                v64[1] = v71;
                v66 = v1042;
              }
              else
              {
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[428][1824 * v59])((SaleUI_SortData *)(&this->m_sort[428][1824 * v59]), (int)(1));
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4794) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5038) = 1;
                v60 = *(_DWORD *)&this->remarkbuf[20];
                v61 = *(&this->m_bWPXS + 192 * v60 + 246);
                v62 = *(&this->m_bWPXS + 192 * v60 + 247);
                v63 = *(&this->m_bWPXS + 192 * v60 + 248);
                v1134 = *(&this->m_bWPXS + 192 * v60 + 249);
                v64 = (int *)(&this->m_bWPXS + 624 * v60 + 2305);
                v64[2] = v62;
                v65 = (_DWORD *)v64 + 1;
                v64[3] = v63;
                v64[1] = v61;
                v66 = v1134;
              }
              v64[4] = v66;
              v67 = (_DWORD *)v64 + 5;
              *v67 = *v65;
              v67[1] = (unsigned long)v65[1];
              v68 = (unsigned long)v65[2];
              v69 = (unsigned long)v65[3];
              v67[2] = v68;
              v67[3] = v69;
LABEL_37:
              v74 = v946[328];
              v75 = v74 < 0;
              v11 = v74 <= 0;
              v76 = *(_DWORD *)&this->remarkbuf[20];
              if ( !v11 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v76 + 5039) = 1;
                v77 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v77 + 4794) )
                {
                  v962[0] = *(&this->m_bWPXS + 192 * v77 + 238);
                  v962[1] = *(&this->m_bWPXS + 192 * v77 + 239);
                  v962[2] = *(&this->m_bWPXS + 192 * v77 + 240);
                  v962[3] = *(&this->m_bWPXS + 192 * v77 + 241);
                  (((UIWnd *)&this->m_sort[435][1824 * v77 + 3]))->UIWnd::sub_445FA0(v962);
                  v78 = *(_DWORD *)&this->remarkbuf[20];
                  v79 = *(&this->m_bWPXS + 192 * v78 + 238);
                  v80 = *(&this->m_bWPXS + 192 * v78 + 239);
                  v81 = *(&this->m_bWPXS + 192 * v78 + 240);
                  v1104 = *(&this->m_bWPXS + 192 * v78 + 241);
                  v82 = (int *)(&this->m_bWPXS + 624 * v78 + 2318);
                  v82[2] = v80;
                  v83 = (_DWORD *)v82 + 1;
                  v82[3] = v81;
                  v82[1] = v79;
                  v84 = v1104;
                }
                else
                {
                  v998[0] = *(&this->m_bWPXS + 192 * v77 + 250);
                  v998[1] = *(&this->m_bWPXS + 192 * v77 + 251);
                  v998[2] = *(&this->m_bWPXS + 192 * v77 + 252);
                  v998[3] = *(&this->m_bWPXS + 192 * v77 + 253);
                  (((UIWnd *)&this->m_sort[435][1824 * v77 + 3]))->UIWnd::sub_445FA0(v998);
                  v85 = *(_DWORD *)&this->remarkbuf[20];
                  v86 = *(&this->m_bWPXS + 192 * v85 + 250);
                  v87 = *(&this->m_bWPXS + 192 * v85 + 251);
                  v88 = *(&this->m_bWPXS + 192 * v85 + 252);
                  v1044 = *(&this->m_bWPXS + 192 * v85 + 253);
                  v82 = (int *)(&this->m_bWPXS + 624 * v85 + 2318);
                  v82[2] = v87;
                  v83 = (_DWORD *)v82 + 1;
                  v82[3] = v88;
                  v82[1] = v86;
                  v84 = v1044;
                }
                v82[4] = v84;
                v89 = (_DWORD *)v82 + 5;
                *v89 = *v83;
                v89[1] = (unsigned long)v83[1];
                v89[2] = (unsigned long)v83[2];
                v89[3] = (unsigned long)v83[3];
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[435][1824
                                                                                   * *(_DWORD *)&this->remarkbuf[20]
                                                                                   + 3])((SaleUI_SortData *)(&this->m_sort[435][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]), (int)(1));
                goto LABEL_78;
              }
              v90 = 3 * v76;
              if ( !v75 )
              {
                *((_BYTE *)&this->m_bWPXS + 16 * v90 + 5039) = 0;
                goto LABEL_78;
              }
              *((_BYTE *)&this->m_bWPXS + 16 * v90 + 5043) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5039) = 0;
              v91 = *(_DWORD *)&this->remarkbuf[20];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v91 + 4798) )
              {
                v964[0] = *(&this->m_bWPXS + 192 * v91 + 254);
                v964[1] = *(&this->m_bWPXS + 192 * v91 + 255);
                v964[2] = *(&this->m_bWPXS + 192 * v91 + 256);
                v964[3] = *(&this->m_bWPXS + 192 * v91 + 257);
                (((UIWnd *)&this->m_sort[466][1824 * v91]))->UIWnd::sub_445FA0(v964);
                v92 = *(_DWORD *)&this->remarkbuf[20];
                v93 = *(&this->m_bWPXS + 192 * v92 + 254);
                v94 = *(&this->m_bWPXS + 192 * v92 + 255);
                v95 = *(&this->m_bWPXS + 192 * v92 + 256);
                v1148 = *(&this->m_bWPXS + 192 * v92 + 257);
                v96 = (int *)(&this->m_bWPXS + 624 * v92 + 2370);
                v96[2] = v94;
                v97 = (_DWORD *)v96 + 1;
                v96[3] = v95;
                v96[1] = v93;
                v98 = v1148;
              }
              else
              {
                v1016[0] = *(&this->m_bWPXS + 192 * v91 + 266);
                v1016[1] = *(&this->m_bWPXS + 192 * v91 + 267);
                v1016[2] = *(&this->m_bWPXS + 192 * v91 + 268);
                v1016[3] = *(&this->m_bWPXS + 192 * v91 + 269);
                (((UIWnd *)&this->m_sort[466][1824 * v91]))->UIWnd::sub_445FA0(v1016);
                v99 = *(_DWORD *)&this->remarkbuf[20];
                v100 = *(&this->m_bWPXS + 192 * v99 + 266);
                v101 = *(&this->m_bWPXS + 192 * v99 + 267);
                v102 = *(&this->m_bWPXS + 192 * v99 + 268);
                v1046 = *(&this->m_bWPXS + 192 * v99 + 269);
                v96 = (int *)(&this->m_bWPXS + 624 * v99 + 2370);
                v96[2] = v101;
                v97 = (_DWORD *)v96 + 1;
                v96[3] = v102;
                v96[1] = v100;
                v98 = v1046;
              }
LABEL_46:
              v96[4] = v98;
              v103 = (_DWORD *)v96 + 5;
              *v103 = *v97;
              v103[1] = (unsigned long)v97[1];
              v103[2] = (unsigned long)v97[2];
              v103[3] = (unsigned long)v97[3];
              (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[466][1824
                                                                                 * *(_DWORD *)&this->remarkbuf[20]])((SaleUI_SortData *)(&this->m_sort[466][1824 * *(_DWORD *)&this->remarkbuf[20]]), (int)(1));
LABEL_78:
              (*(void ( **)(int *, int))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20]
                                                                             + 277][4])(
                &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][4],
                1);
              v3 = (_WORD *)v946;
              goto LABEL_406;
            }
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[443][1824 * v12 + 1])((SaleUI_SortData *)(&this->m_sort[443][1824 * v12 + 1]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4796) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5040) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5036) = 0;
            v23 = *(_DWORD *)&this->remarkbuf[20];
            v24 = *(&this->m_bWPXS + 192 * v23 + 254);
            v25 = *(&this->m_bWPXS + 192 * v23 + 255);
            v26 = *(&this->m_bWPXS + 192 * v23 + 256);
            v1036 = *(&this->m_bWPXS + 192 * v23 + 257);
            v17 = (int *)(&this->m_bWPXS + 624 * v23 + 2331);
            v17[2] = v25;
            v18 = (_DWORD *)v17 + 1;
            v17[3] = v26;
            v17[1] = v24;
            v19 = v1036;
          }
          else
          {
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[412][1824 * v12 + 4])((SaleUI_SortData *)(&this->m_sort[412][1824 * v12 + 4]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4792) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5036) = 1;
            v13 = *(_DWORD *)&this->remarkbuf[20];
            v14 = *(&this->m_bWPXS + 192 * v13 + 238);
            v15 = *(&this->m_bWPXS + 192 * v13 + 239);
            v16 = *(&this->m_bWPXS + 192 * v13 + 240);
            v1056 = *(&this->m_bWPXS + 192 * v13 + 241);
            v17 = (int *)(&this->m_bWPXS + 624 * v13 + 2279);
            v17[2] = v15;
            v18 = (_DWORD *)v17 + 1;
            v17[3] = v16;
            v17[1] = v14;
            v19 = v1056;
          }
          v17[4] = v19;
          v20 = (_DWORD *)v17 + 5;
          *v20 = *v18;
          v20[1] = (unsigned long)v18[1];
          v21 = (unsigned long)v18[2];
          v22 = (unsigned long)v18[3];
          v20[2] = v21;
          v20[3] = v22;
          goto LABEL_20;
        }
        LOBYTE(v956) = *(_BYTE *)(v7 + 3284);
        (((UIPushButton *)&this->m_NotesNull[54 * v6 + 277][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Cloth.tga", v956);
        v104 = *(_DWORD *)&this->remarkbuf[20];
        v105 = v3[325];
        v106 = HIWORD(g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * v104]->rolevalue[3]);
        if ( v105 >= v106 )
        {
          if ( v105 <= v106 )
            goto LABEL_53;
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[412][1824 * v104 + 4])((SaleUI_SortData *)(&this->m_sort[412][1824 * v104 + 4]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4792) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5036) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5040) = 0;
          v114 = *(_DWORD *)&this->remarkbuf[20];
          v115 = *(&this->m_bWPXS + 192 * v114 + 238);
          v116 = *(&this->m_bWPXS + 192 * v114 + 239);
          v117 = *(&this->m_bWPXS + 192 * v114 + 240);
          v1048 = *(&this->m_bWPXS + 192 * v114 + 241);
          v111 = (int *)(&this->m_bWPXS + 624 * v114 + 2279);
          v111[2] = v116;
          v112 = (_DWORD *)v111 + 1;
          v111[3] = v117;
          v111[1] = v115;
          v113 = v1048;
        }
        else
        {
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[443][1824 * v104 + 1])((SaleUI_SortData *)(&this->m_sort[443][1824 * v104 + 1]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4796) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5040) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5036) = 0;
          v107 = *(_DWORD *)&this->remarkbuf[20];
          v108 = *(&this->m_bWPXS + 192 * v107 + 254);
          v109 = *(&this->m_bWPXS + 192 * v107 + 255);
          v110 = *(&this->m_bWPXS + 192 * v107 + 256);
          v1106 = *(&this->m_bWPXS + 192 * v107 + 257);
          v111 = (int *)(&this->m_bWPXS + 624 * v107 + 2331);
          v111[2] = v109;
          v112 = (_DWORD *)v111 + 1;
          v111[3] = v110;
          v111[1] = v108;
          v113 = v1106;
        }
        v111[4] = v113;
        v118 = (_DWORD *)v111 + 5;
        *v118 = *v112;
        v118[1] = (unsigned long)v112[1];
        v118[2] = (unsigned long)v112[2];
        v118[3] = (unsigned long)v112[3];
LABEL_53:
        v119 = *(_DWORD *)&this->remarkbuf[20];
        v120 = v946[327];
        v121 = HIWORD(g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * v119]->rolevalue[4]);
        if ( v120 >= v121 )
        {
          if ( v120 <= v121 )
            goto LABEL_64;
          *((_BYTE *)&this->m_bWPXS + 48 * v119 + 5037) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5041) = 0;
          v136 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v136 + 4792) )
          {
            v968[0] = *(&this->m_bWPXS + 192 * v136 + 246);
            v968[1] = *(&this->m_bWPXS + 192 * v136 + 247);
            v968[2] = *(&this->m_bWPXS + 192 * v136 + 248);
            v968[3] = *(&this->m_bWPXS + 192 * v136 + 249);
            (((UIWnd *)&this->m_sort[420][1824 * v136 + 2]))->UIWnd::sub_445FA0(v968);
            v137 = *(_DWORD *)&this->remarkbuf[20];
            v138 = *(&this->m_bWPXS + 192 * v137 + 246);
            v139 = *(&this->m_bWPXS + 192 * v137 + 247);
            v140 = *(&this->m_bWPXS + 192 * v137 + 248);
            v1108 = *(&this->m_bWPXS + 192 * v137 + 249);
            v141 = (int *)(&this->m_bWPXS + 624 * v137 + 2292);
            v141[2] = v139;
            v142 = (_DWORD *)v141 + 1;
            v141[3] = v140;
            v141[1] = v138;
            v143 = v1108;
          }
          else
          {
            v1032[0] = *(&this->m_bWPXS + 192 * v136 + 238);
            v1032[1] = *(&this->m_bWPXS + 192 * v136 + 239);
            v1032[2] = *(&this->m_bWPXS + 192 * v136 + 240);
            v1032[3] = *(&this->m_bWPXS + 192 * v136 + 241);
            (((UIWnd *)&this->m_sort[420][1824 * v136 + 2]))->UIWnd::sub_445FA0(v1032);
            v144 = *(_DWORD *)&this->remarkbuf[20];
            v145 = *(&this->m_bWPXS + 192 * v144 + 238);
            v146 = *(&this->m_bWPXS + 192 * v144 + 239);
            v147 = *(&this->m_bWPXS + 192 * v144 + 240);
            v1052 = *(&this->m_bWPXS + 192 * v144 + 241);
            v141 = (int *)(&this->m_bWPXS + 624 * v144 + 2292);
            v141[2] = v146;
            v142 = (_DWORD *)v141 + 1;
            v141[3] = v147;
            v141[1] = v145;
            v143 = v1052;
          }
          v141[4] = v143;
          v148 = (_DWORD *)v141 + 5;
          *v148 = *v142;
          v148[1] = (unsigned long)v142[1];
          v148[2] = (unsigned long)v142[2];
          v148[3] = (unsigned long)v142[3];
          v135 = (SaleUI_SortData *)&this->m_sort[420][1824 * *(_DWORD *)&this->remarkbuf[20] + 2];
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v119 + 5041) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5037) = 0;
          v122 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v122 + 4796) )
          {
            v966[0] = *(&this->m_bWPXS + 192 * v122 + 262);
            v966[1] = *(&this->m_bWPXS + 192 * v122 + 263);
            v966[2] = *(&this->m_bWPXS + 192 * v122 + 264);
            v966[3] = *(&this->m_bWPXS + 192 * v122 + 265);
            (((UIWnd *)&this->m_sort[450][1824 * v122 + 4]))->UIWnd::sub_445FA0(v966);
            v123 = *(_DWORD *)&this->remarkbuf[20];
            v124 = *(&this->m_bWPXS + 192 * v123 + 262);
            v125 = *(&this->m_bWPXS + 192 * v123 + 263);
            v126 = *(&this->m_bWPXS + 192 * v123 + 264);
            v1136 = *(&this->m_bWPXS + 192 * v123 + 265);
            v127 = (int *)(&this->m_bWPXS + 624 * v123 + 2344);
            v127[2] = v125;
            v128 = (_DWORD *)v127 + 1;
            v127[3] = v126;
            v127[1] = v124;
            v129 = v1136;
          }
          else
          {
            v1000[0] = *(&this->m_bWPXS + 192 * v122 + 254);
            v1000[1] = *(&this->m_bWPXS + 192 * v122 + 255);
            v1000[2] = *(&this->m_bWPXS + 192 * v122 + 256);
            v1000[3] = *(&this->m_bWPXS + 192 * v122 + 257);
            (((UIWnd *)&this->m_sort[450][1824 * v122 + 4]))->UIWnd::sub_445FA0(v1000);
            v130 = *(_DWORD *)&this->remarkbuf[20];
            v131 = *(&this->m_bWPXS + 192 * v130 + 254);
            v132 = *(&this->m_bWPXS + 192 * v130 + 255);
            v133 = *(&this->m_bWPXS + 192 * v130 + 256);
            v1050 = *(&this->m_bWPXS + 192 * v130 + 257);
            v127 = (int *)(&this->m_bWPXS + 624 * v130 + 2344);
            v127[2] = v132;
            v128 = (_DWORD *)v127 + 1;
            v127[3] = v133;
            v127[1] = v131;
            v129 = v1050;
          }
          v127[4] = v129;
          v134 = (_DWORD *)v127 + 5;
          *v134 = *v128;
          v134[1] = (unsigned long)v128[1];
          v134[2] = (unsigned long)v128[2];
          v134[3] = (unsigned long)v128[3];
          v135 = (SaleUI_SortData *)&this->m_sort[450][1824 * *(_DWORD *)&this->remarkbuf[20] + 4];
        }
        (**(void ( ***)(SaleUI_SortData *, int))v135)((SaleUI_SortData *)(v135), (int)(1));
LABEL_64:
        v149 = *(_DWORD *)&this->remarkbuf[20];
        v150 = v946[326];
        v151 = g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * v149]->rolevalue[4];
        if ( v150 >= v151 )
        {
          if ( v150 <= v151 )
          {
LABEL_69:
            v164 = *(_DWORD *)&this->remarkbuf[20];
            v165 = v946[328];
            v166 = g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * v164]->rolevalue[5];
            if ( v165 >= v166 )
            {
              if ( v165 > v166 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v164 + 5039) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5043) = 0;
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[435][1824
                                                                                   * *(_DWORD *)&this->remarkbuf[20]
                                                                                   + 3])((SaleUI_SortData *)(&this->m_sort[435][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]), (int)(1));
                v176 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v176 + 4794) )
                {
                  v972[0] = *(&this->m_bWPXS + 192 * v176 + 238);
                  v972[1] = *(&this->m_bWPXS + 192 * v176 + 239);
                  v972[2] = *(&this->m_bWPXS + 192 * v176 + 240);
                  v972[3] = *(&this->m_bWPXS + 192 * v176 + 241);
                  (((UIWnd *)&this->m_sort[435][1824 * v176 + 3]))->UIWnd::sub_445FA0(v972);
                  v177 = *(_DWORD *)&this->remarkbuf[20];
                  v178 = *(&this->m_bWPXS + 192 * v177 + 238);
                  v179 = *(&this->m_bWPXS + 192 * v177 + 239);
                  v180 = *(&this->m_bWPXS + 192 * v177 + 240);
                  v1147 = *(&this->m_bWPXS + 192 * v177 + 241);
                  v181 = (int *)(&this->m_bWPXS + 624 * v177 + 2318);
                  v181[2] = v179;
                  v182 = (_DWORD *)v181 + 1;
                  v181[3] = v180;
                  v181[1] = v178;
                  v183 = v1147;
                }
                else
                {
                  v1018[0] = *(&this->m_bWPXS + 192 * v176 + 250);
                  v1018[1] = *(&this->m_bWPXS + 192 * v176 + 251);
                  v1018[2] = *(&this->m_bWPXS + 192 * v176 + 252);
                  v1018[3] = *(&this->m_bWPXS + 192 * v176 + 253);
                  (((UIWnd *)&this->m_sort[435][1824 * v176 + 3]))->UIWnd::sub_445FA0(v1018);
                  v184 = *(_DWORD *)&this->remarkbuf[20];
                  v185 = *(&this->m_bWPXS + 192 * v184 + 250);
                  v186 = *(&this->m_bWPXS + 192 * v184 + 251);
                  v187 = *(&this->m_bWPXS + 192 * v184 + 252);
                  v1058 = *(&this->m_bWPXS + 192 * v184 + 253);
                  v181 = (int *)(&this->m_bWPXS + 624 * v184 + 2318);
                  v181[2] = v186;
                  v182 = (_DWORD *)v181 + 1;
                  v181[3] = v187;
                  v181[1] = v185;
                  v183 = v1058;
                }
                v181[4] = v183;
                v188 = (_DWORD *)v181 + 5;
                *v188 = *v182;
                v188[1] = (unsigned long)v182[1];
                v188[2] = (unsigned long)v182[2];
                v188[3] = (unsigned long)v182[3];
              }
              goto LABEL_78;
            }
            *((_BYTE *)&this->m_bWPXS + 48 * v164 + 5043) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5039) = 0;
            v167 = *(_DWORD *)&this->remarkbuf[20];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v167 + 4798) )
            {
              v970[0] = *(&this->m_bWPXS + 192 * v167 + 254);
              v970[1] = *(&this->m_bWPXS + 192 * v167 + 255);
              v970[2] = *(&this->m_bWPXS + 192 * v167 + 256);
              v970[3] = *(&this->m_bWPXS + 192 * v167 + 257);
              (((UIWnd *)&this->m_sort[466][1824 * v167]))->UIWnd::sub_445FA0(v970);
              v168 = *(_DWORD *)&this->remarkbuf[20];
              v169 = *(&this->m_bWPXS + 192 * v168 + 254);
              v170 = *(&this->m_bWPXS + 192 * v168 + 255);
              v171 = *(&this->m_bWPXS + 192 * v168 + 256);
              v1110 = *(&this->m_bWPXS + 192 * v168 + 257);
              v96 = (int *)(&this->m_bWPXS + 624 * v168 + 2370);
              v96[2] = v170;
              v97 = (_DWORD *)v96 + 1;
              v96[3] = v171;
              v96[1] = v169;
              v98 = v1110;
            }
            else
            {
              v1002[0] = *(&this->m_bWPXS + 192 * v167 + 266);
              v1002[1] = *(&this->m_bWPXS + 192 * v167 + 267);
              v1002[2] = *(&this->m_bWPXS + 192 * v167 + 268);
              v1002[3] = *(&this->m_bWPXS + 192 * v167 + 269);
              (((UIWnd *)&this->m_sort[466][1824 * v167]))->UIWnd::sub_445FA0(v1002);
              v172 = *(_DWORD *)&this->remarkbuf[20];
              v173 = *(&this->m_bWPXS + 192 * v172 + 266);
              v174 = *(&this->m_bWPXS + 192 * v172 + 267);
              v175 = *(&this->m_bWPXS + 192 * v172 + 268);
              v1034 = *(&this->m_bWPXS + 192 * v172 + 269);
              v96 = (int *)(&this->m_bWPXS + 624 * v172 + 2370);
              v96[2] = v174;
              v97 = (_DWORD *)v96 + 1;
              v96[3] = v175;
              v96[1] = v173;
              v98 = v1034;
            }
            goto LABEL_46;
          }
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[428][1824 * v149])((SaleUI_SortData *)(&this->m_sort[428][1824 * v149]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4794) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5038) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5042) = 0;
          v159 = *(_DWORD *)&this->remarkbuf[20];
          v160 = *(&this->m_bWPXS + 192 * v159 + 246);
          v161 = *(&this->m_bWPXS + 192 * v159 + 247);
          v162 = *(&this->m_bWPXS + 192 * v159 + 248);
          v1054 = *(&this->m_bWPXS + 192 * v159 + 249);
          v156 = (int *)(&this->m_bWPXS + 624 * v159 + 2305);
          v156[2] = v161;
          v157 = (_DWORD *)v156 + 1;
          v156[3] = v162;
          v156[1] = v160;
          v158 = v1054;
        }
        else
        {
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[458][1824 * v149 + 2])((SaleUI_SortData *)(&this->m_sort[458][1824 * v149 + 2]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4798) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5042) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5038) = 0;
          v152 = *(_DWORD *)&this->remarkbuf[20];
          v153 = *(&this->m_bWPXS + 192 * v152 + 262);
          v154 = *(&this->m_bWPXS + 192 * v152 + 263);
          v155 = *(&this->m_bWPXS + 192 * v152 + 264);
          v1150 = *(&this->m_bWPXS + 192 * v152 + 265);
          v156 = (int *)(&this->m_bWPXS + 624 * v152 + 2357);
          v156[2] = v154;
          v157 = (_DWORD *)v156 + 1;
          v156[3] = v155;
          v156[1] = v153;
          v158 = v1150;
        }
        v156[4] = v158;
        v163 = (_DWORD *)v156 + 5;
        *v163 = *v157;
        v163[1] = (unsigned long)v157[1];
        v163[2] = (unsigned long)v157[2];
        v163[3] = (unsigned long)v157[3];
        goto LABEL_69;
      case 8:
        v189 = *(_DWORD *)&this->remarkbuf[20];
        if ( !*((_BYTE *)v3 + v189 + 614) )
          goto LABEL_406;
        v190 = *(&this->AttackNum + 289);
        if ( !*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * v189) )
        {
          LOBYTE(v949) = *(_BYTE *)(v190 + 3284);
          (((UIPushButton *)&this->m_IsEquip[216 * v189 + 23][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Hat.tga", v949);
          for ( j = 0; j < 8; ++j )
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[595][1824
                                                                                  * *(_DWORD *)&this->remarkbuf[20]
                                                                                  + 1
                                                                                  + 38 * j])((SaleUI_SortData *)(&this->m_sort[595][1824 * *(_DWORD *)&this->remarkbuf[20] + 1 + 38 * j]), (_DWORD)(0));
          v192 = v3[325];
          v193 = v192 < 0;
          v11 = v192 <= 0;
          v194 = *(_DWORD *)&this->remarkbuf[20];
          if ( v11 )
          {
            if ( !v193 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v194 + 5060) = 0;
LABEL_89:
              v209 = v946[327];
              v210 = v209 < 0;
              v11 = v209 <= 0;
              v211 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                v225 = 3 * v211;
                if ( v210 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v225 + 5065) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5061) = 0;
                  v226 = *(_DWORD *)&this->remarkbuf[20];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v226 + 4820) )
                  {
                    v976[0] = *(&this->m_bWPXS + 192 * v226 + 358);
                    v976[1] = *(&this->m_bWPXS + 192 * v226 + 359);
                    v976[2] = *(&this->m_bWPXS + 192 * v226 + 360);
                    v976[3] = *(&this->m_bWPXS + 192 * v226 + 361);
                    (((UIWnd *)&this->m_ListSelNum[35][1824 * v226 + 1]))->UIWnd::sub_445FA0(v976);
                    v227 = *(_DWORD *)&this->remarkbuf[20];
                    v228 = *(&this->m_bWPXS + 192 * v227 + 358);
                    v229 = *(&this->m_bWPXS + 192 * v227 + 359);
                    v230 = *(&this->m_bWPXS + 192 * v227 + 360);
                    v1114 = *(&this->m_bWPXS + 192 * v227 + 361);
                    v231 = (int *)(&this->m_bWPXS + 624 * v227 + 2656);
                    v231[2] = v229;
                    v232 = (_DWORD *)v231 + 1;
                    v231[3] = v230;
                    v231[1] = v228;
                    v233 = v1114;
                  }
                  else
                  {
                    v1026[0] = *(&this->m_bWPXS + 192 * v226 + 350);
                    v1026[1] = *(&this->m_bWPXS + 192 * v226 + 351);
                    v1026[2] = *(&this->m_bWPXS + 192 * v226 + 352);
                    v1026[3] = *(&this->m_bWPXS + 192 * v226 + 353);
                    (((UIWnd *)&this->m_ListSelNum[35][1824 * v226 + 1]))->UIWnd::sub_445FA0(v1026);
                    v234 = *(_DWORD *)&this->remarkbuf[20];
                    v235 = *(&this->m_bWPXS + 192 * v234 + 350);
                    v236 = *(&this->m_bWPXS + 192 * v234 + 351);
                    v237 = *(&this->m_bWPXS + 192 * v234 + 352);
                    v1064 = *(&this->m_bWPXS + 192 * v234 + 353);
                    v231 = (int *)(&this->m_bWPXS + 624 * v234 + 2656);
                    v231[2] = v236;
                    v232 = (_DWORD *)v231 + 1;
                    v231[3] = v237;
                    v231[1] = v235;
                    v233 = v1064;
                  }
                  v231[4] = v233;
                  v238 = (_DWORD *)v231 + 5;
                  *v238 = *v232;
                  v238[1] = (unsigned long)v232[1];
                  v238[2] = (unsigned long)v232[2];
                  v238[3] = (unsigned long)v232[3];
                  (*(void ( **)(int *, int))this->m_ListSelNum[35][1824
                                                                                      * *(_DWORD *)&this->remarkbuf[20]
                                                                                      + 1])(
                    &this->m_ListSelNum[35][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
                    1);
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v225 + 5061) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v211 + 5061) = 1;
                v212 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v212 + 4816) )
                {
                  v974[0] = *(&this->m_bWPXS + 192 * v212 + 342);
                  v974[1] = *(&this->m_bWPXS + 192 * v212 + 343);
                  v974[2] = *(&this->m_bWPXS + 192 * v212 + 344);
                  v974[3] = *(&this->m_bWPXS + 192 * v212 + 345);
                  (((UIWnd *)&this->m_ListSelNum[4][1824 * v212 + 4]))->UIWnd::sub_445FA0(v974);
                  v213 = *(_DWORD *)&this->remarkbuf[20];
                  v214 = *(&this->m_bWPXS + 192 * v213 + 342);
                  v215 = *(&this->m_bWPXS + 192 * v213 + 343);
                  v216 = *(&this->m_bWPXS + 192 * v213 + 344);
                  v1139 = *(&this->m_bWPXS + 192 * v213 + 345);
                  v217 = (int *)(&this->m_bWPXS + 624 * v213 + 2604);
                  v217[2] = v215;
                  v218 = (_DWORD *)v217 + 1;
                  v217[3] = v216;
                  v217[1] = v214;
                  v219 = v1139;
                }
                else
                {
                  v1004[0] = *(&this->m_bWPXS + 192 * v212 + 334);
                  v1004[1] = *(&this->m_bWPXS + 192 * v212 + 335);
                  v1004[2] = *(&this->m_bWPXS + 192 * v212 + 336);
                  v1004[3] = *(&this->m_bWPXS + 192 * v212 + 337);
                  (((UIWnd *)&this->m_ListSelNum[4][1824 * v212 + 4]))->UIWnd::sub_445FA0(v1004);
                  v220 = *(_DWORD *)&this->remarkbuf[20];
                  v221 = *(&this->m_bWPXS + 192 * v220 + 334);
                  v222 = *(&this->m_bWPXS + 192 * v220 + 335);
                  v223 = *(&this->m_bWPXS + 192 * v220 + 336);
                  v1062 = *(&this->m_bWPXS + 192 * v220 + 337);
                  v217 = (int *)(&this->m_bWPXS + 624 * v220 + 2604);
                  v217[2] = v222;
                  v218 = (_DWORD *)v217 + 1;
                  v217[3] = v223;
                  v217[1] = v221;
                  v219 = v1062;
                }
                v217[4] = v219;
                v224 = (_DWORD *)v217 + 5;
                *v224 = *v218;
                v224[1] = (unsigned long)v218[1];
                v224[2] = (unsigned long)v218[2];
                v224[3] = (unsigned long)v218[3];
                (*(void ( **)(int *, int))this->m_ListSelNum[4][1824
                                                                                   * *(_DWORD *)&this->remarkbuf[20]
                                                                                   + 4])(
                  &this->m_ListSelNum[4][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
                  1);
              }
              v239 = v946[326];
              v240 = v239 < 0;
              v11 = v239 <= 0;
              v241 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                if ( !v240 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v241 + 5062) = 0;
                  goto LABEL_106;
                }
                (*(void ( **)(int *, int))this->m_ListSelNum[42][1824 * v241 + 4])(
                  &this->m_ListSelNum[42][1824 * v241 + 4],
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4822) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5066) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5062) = 0;
                v252 = *(_DWORD *)&this->remarkbuf[20];
                v253 = *(&this->m_bWPXS + 192 * v252 + 358);
                v254 = *(&this->m_bWPXS + 192 * v252 + 359);
                v255 = *(&this->m_bWPXS + 192 * v252 + 360);
                v1066 = *(&this->m_bWPXS + 192 * v252 + 361);
                v246 = (int *)(&this->m_bWPXS + 624 * v252 + 2669);
                v246[2] = v254;
                v247 = (_DWORD *)v246 + 1;
                v246[3] = v255;
                v246[1] = v253;
                v248 = v1066;
              }
              else
              {
                (*(void ( **)(int *, int))this->m_ListSelNum[12][1824 * v241 + 2])(
                  &this->m_ListSelNum[12][1824 * v241 + 2],
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4818) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5062) = 1;
                v242 = *(_DWORD *)&this->remarkbuf[20];
                v243 = *(&this->m_bWPXS + 192 * v242 + 342);
                v244 = *(&this->m_bWPXS + 192 * v242 + 343);
                v245 = *(&this->m_bWPXS + 192 * v242 + 344);
                v1145 = *(&this->m_bWPXS + 192 * v242 + 345);
                v246 = (int *)(&this->m_bWPXS + 624 * v242 + 2617);
                v246[2] = v244;
                v247 = (_DWORD *)v246 + 1;
                v246[3] = v245;
                v246[1] = v243;
                v248 = v1145;
              }
              v246[4] = v248;
              v249 = (_DWORD *)v246 + 5;
              *v249 = *v247;
              v249[1] = (unsigned long)v247[1];
              v250 = (unsigned long)v247[2];
              v251 = (unsigned long)v247[3];
              v249[2] = v250;
              v249[3] = v251;
LABEL_106:
              v256 = v946[328];
              v257 = v256 < 0;
              v11 = v256 <= 0;
              v258 = *(_DWORD *)&this->remarkbuf[20];
              if ( !v11 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v258 + 5063) = 1;
                v259 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v259 + 4818) )
                {
                  v978[0] = *(&this->m_bWPXS + 192 * v259 + 334);
                  v978[1] = *(&this->m_bWPXS + 192 * v259 + 335);
                  v978[2] = *(&this->m_bWPXS + 192 * v259 + 336);
                  v978[3] = *(&this->m_bWPXS + 192 * v259 + 337);
                  (((UIWnd *)&this->m_ListSelNum[20][1824 * v259]))->UIWnd::sub_445FA0(v978);
                  v260 = *(_DWORD *)&this->remarkbuf[20];
                  v261 = *(&this->m_bWPXS + 192 * v260 + 334);
                  v262 = *(&this->m_bWPXS + 192 * v260 + 335);
                  v263 = *(&this->m_bWPXS + 192 * v260 + 336);
                  v1116 = *(&this->m_bWPXS + 192 * v260 + 337);
                  v264 = (int *)(&this->m_bWPXS + 624 * v260 + 2630);
                  v264[2] = v262;
                  v265 = (_DWORD *)v264 + 1;
                  v264[3] = v263;
                  v264[1] = v261;
                  v266 = v1116;
                }
                else
                {
                  v1006[0] = *(&this->m_bWPXS + 192 * v259 + 346);
                  v1006[1] = *(&this->m_bWPXS + 192 * v259 + 347);
                  v1006[2] = *(&this->m_bWPXS + 192 * v259 + 348);
                  v1006[3] = *(&this->m_bWPXS + 192 * v259 + 349);
                  (((UIWnd *)&this->m_ListSelNum[20][1824 * v259]))->UIWnd::sub_445FA0(v1006);
                  v267 = *(_DWORD *)&this->remarkbuf[20];
                  v268 = *(&this->m_bWPXS + 192 * v267 + 346);
                  v269 = *(&this->m_bWPXS + 192 * v267 + 347);
                  v270 = *(&this->m_bWPXS + 192 * v267 + 348);
                  v1068 = *(&this->m_bWPXS + 192 * v267 + 349);
                  v264 = (int *)(&this->m_bWPXS + 624 * v267 + 2630);
                  v264[2] = v269;
                  v265 = (_DWORD *)v264 + 1;
                  v264[3] = v270;
                  v264[1] = v268;
                  v266 = v1068;
                }
                v264[4] = v266;
                v271 = (_DWORD *)v264 + 5;
                *v271 = *v265;
                v271[1] = (unsigned long)v265[1];
                v271[2] = (unsigned long)v265[2];
                v271[3] = (unsigned long)v265[3];
                (*(void ( **)(int *, int))this->m_ListSelNum[20][1824
                                                                                    * *(_DWORD *)&this->remarkbuf[20]])(
                  &this->m_ListSelNum[20][1824 * *(_DWORD *)&this->remarkbuf[20]],
                  1);
                goto LABEL_147;
              }
              v272 = 3 * v258;
              if ( !v257 )
              {
                *((_BYTE *)&this->m_bWPXS + 16 * v272 + 5063) = 0;
LABEL_147:
                (**(void ( ***)(_BYTE *, int))&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 23][1])((_BYTE *)(&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 23][1]), (int)(1));
                v3 = (_WORD *)v946;
                goto LABEL_406;
              }
              *((_BYTE *)&this->m_bWPXS + 16 * v272 + 5067) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5063) = 0;
              v273 = *(_DWORD *)&this->remarkbuf[20];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v273 + 4822) )
              {
                v980[0] = *(&this->m_bWPXS + 192 * v273 + 350);
                v980[1] = *(&this->m_bWPXS + 192 * v273 + 351);
                v980[2] = *(&this->m_bWPXS + 192 * v273 + 352);
                v980[3] = *(&this->m_bWPXS + 192 * v273 + 353);
                (((UIWnd *)&this->m_ListSelNum[50][1824 * v273 + 2]))->UIWnd::sub_445FA0(v980);
                v274 = *(_DWORD *)&this->remarkbuf[20];
                v275 = *(&this->m_bWPXS + 192 * v274 + 350);
                v276 = *(&this->m_bWPXS + 192 * v274 + 351);
                v277 = *(&this->m_bWPXS + 192 * v274 + 352);
                v1141 = *(&this->m_bWPXS + 192 * v274 + 353);
                v278 = (int *)(&this->m_bWPXS + 624 * v274 + 2682);
                v278[2] = v276;
                v279 = (_DWORD *)v278 + 1;
                v278[3] = v277;
                v278[1] = v275;
                v280 = v1141;
              }
              else
              {
                v1020[0] = *(&this->m_bWPXS + 192 * v273 + 362);
                v1020[1] = *(&this->m_bWPXS + 192 * v273 + 363);
                v1020[2] = *(&this->m_bWPXS + 192 * v273 + 364);
                v1020[3] = *(&this->m_bWPXS + 192 * v273 + 365);
                (((UIWnd *)&this->m_ListSelNum[50][1824 * v273 + 2]))->UIWnd::sub_445FA0(v1020);
                v281 = *(_DWORD *)&this->remarkbuf[20];
                v282 = *(&this->m_bWPXS + 192 * v281 + 362);
                v283 = *(&this->m_bWPXS + 192 * v281 + 363);
                v284 = *(&this->m_bWPXS + 192 * v281 + 364);
                v1070 = *(&this->m_bWPXS + 192 * v281 + 365);
                v278 = (int *)(&this->m_bWPXS + 624 * v281 + 2682);
                v278[2] = v283;
                v279 = (_DWORD *)v278 + 1;
                v278[3] = v284;
                v278[1] = v282;
                v280 = v1070;
              }
LABEL_115:
              v278[4] = v280;
              v285 = (_DWORD *)v278 + 5;
              *v285 = *v279;
              v285[1] = (unsigned long)v279[1];
              v285[2] = (unsigned long)v279[2];
              v285[3] = (unsigned long)v279[3];
              (*(void ( **)(int *, int))this->m_ListSelNum[50][1824
                                                                                  * *(_DWORD *)&this->remarkbuf[20]
                                                                                  + 2])(
                &this->m_ListSelNum[50][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
                1);
              goto LABEL_147;
            }
            (*(void ( **)(int *, int))this->m_ListSelNum[27][1824 * v194 + 3])(
              &this->m_ListSelNum[27][1824 * v194 + 3],
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4820) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5064) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5060) = 0;
            v205 = *(_DWORD *)&this->remarkbuf[20];
            v206 = *(&this->m_bWPXS + 192 * v205 + 350);
            v207 = *(&this->m_bWPXS + 192 * v205 + 351);
            v208 = *(&this->m_bWPXS + 192 * v205 + 352);
            v1060 = *(&this->m_bWPXS + 192 * v205 + 353);
            v199 = (int *)(&this->m_bWPXS + 624 * v205 + 2643);
            v199[2] = v207;
            v200 = (_DWORD *)v199 + 1;
            v199[3] = v208;
            v199[1] = v206;
            v201 = v1060;
          }
          else
          {
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[595][1824 * v194 + 1])((SaleUI_SortData *)(&this->m_sort[595][1824 * v194 + 1]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4816) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5060) = 1;
            v195 = *(_DWORD *)&this->remarkbuf[20];
            v196 = *(&this->m_bWPXS + 192 * v195 + 334);
            v197 = *(&this->m_bWPXS + 192 * v195 + 335);
            v198 = *(&this->m_bWPXS + 192 * v195 + 336);
            v1112 = *(&this->m_bWPXS + 192 * v195 + 337);
            v199 = (int *)(&this->m_bWPXS + 624 * v195 + 2591);
            v199[2] = v197;
            v200 = (_DWORD *)v199 + 1;
            v199[3] = v198;
            v199[1] = v196;
            v201 = v1112;
          }
          v199[4] = v201;
          v202 = (_DWORD *)v199 + 5;
          *v202 = *v200;
          v202[1] = (unsigned long)v200[1];
          v203 = (unsigned long)v200[2];
          v204 = (unsigned long)v200[3];
          v202[2] = v203;
          v202[3] = v204;
          goto LABEL_89;
        }
        LOBYTE(v953) = *(_BYTE *)(v190 + 3284);
        (((UIPushButton *)&this->m_IsEquip[216 * v189 + 23][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Hat.tga", v953);
        v286 = *(_DWORD *)&this->remarkbuf[20];
        v287 = v3[325];
        v288 = *(_WORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * v286) + 650);
        if ( v287 >= v288 )
        {
          if ( v287 <= v288 )
            goto LABEL_122;
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[595][1824 * v286 + 1])((SaleUI_SortData *)(&this->m_sort[595][1824 * v286 + 1]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4816) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5060) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5064) = 0;
          v296 = *(_DWORD *)&this->remarkbuf[20];
          v297 = *(&this->m_bWPXS + 192 * v296 + 334);
          v298 = *(&this->m_bWPXS + 192 * v296 + 335);
          v299 = *(&this->m_bWPXS + 192 * v296 + 336);
          v1072 = *(&this->m_bWPXS + 192 * v296 + 337);
          v293 = (int *)(&this->m_bWPXS + 624 * v296 + 2591);
          v293[2] = v298;
          v294 = (_DWORD *)v293 + 1;
          v293[3] = v299;
          v293[1] = v297;
          v295 = v1072;
        }
        else
        {
          (*(void ( **)(int *, int))this->m_ListSelNum[27][1824 * v286 + 3])(
            &this->m_ListSelNum[27][1824 * v286 + 3],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4820) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5064) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5060) = 0;
          v289 = *(_DWORD *)&this->remarkbuf[20];
          v290 = *(&this->m_bWPXS + 192 * v289 + 350);
          v291 = *(&this->m_bWPXS + 192 * v289 + 351);
          v292 = *(&this->m_bWPXS + 192 * v289 + 352);
          v1118 = *(&this->m_bWPXS + 192 * v289 + 353);
          v293 = (int *)(&this->m_bWPXS + 624 * v289 + 2643);
          v293[2] = v291;
          v294 = (_DWORD *)v293 + 1;
          v293[3] = v292;
          v293[1] = v290;
          v295 = v1118;
        }
        v293[4] = v295;
        v300 = (_DWORD *)v293 + 5;
        *v300 = *v294;
        v300[1] = (unsigned long)v294[1];
        v300[2] = (unsigned long)v294[2];
        v300[3] = (unsigned long)v294[3];
LABEL_122:
        v301 = *(_DWORD *)&this->remarkbuf[20];
        v302 = v946[327];
        v303 = *(_WORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * v301) + 654);
        if ( v302 >= v303 )
        {
          if ( v302 <= v303 )
            goto LABEL_133;
          *((_BYTE *)&this->m_bWPXS + 48 * v301 + 5061) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5065) = 0;
          v318 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v318 + 4816) )
          {
            v984[0] = *(&this->m_bWPXS + 192 * v318 + 342);
            v984[1] = *(&this->m_bWPXS + 192 * v318 + 343);
            v984[2] = *(&this->m_bWPXS + 192 * v318 + 344);
            v984[3] = *(&this->m_bWPXS + 192 * v318 + 345);
            (((UIWnd *)&this->m_ListSelNum[4][1824 * v318 + 4]))->UIWnd::sub_445FA0(v984);
            v319 = *(_DWORD *)&this->remarkbuf[20];
            v320 = *(&this->m_bWPXS + 192 * v319 + 342);
            v321 = *(&this->m_bWPXS + 192 * v319 + 343);
            v322 = *(&this->m_bWPXS + 192 * v319 + 344);
            v1120 = *(&this->m_bWPXS + 192 * v319 + 345);
            v323 = (int *)(&this->m_bWPXS + 624 * v319 + 2604);
            v323[2] = v321;
            v324 = (_DWORD *)v323 + 1;
            v323[3] = v322;
            v323[1] = v320;
            v325 = v1120;
          }
          else
          {
            v1030[0] = *(&this->m_bWPXS + 192 * v318 + 334);
            v1030[1] = *(&this->m_bWPXS + 192 * v318 + 335);
            v1030[2] = *(&this->m_bWPXS + 192 * v318 + 336);
            v1030[3] = *(&this->m_bWPXS + 192 * v318 + 337);
            (((UIWnd *)&this->m_ListSelNum[4][1824 * v318 + 4]))->UIWnd::sub_445FA0(v1030);
            v326 = *(_DWORD *)&this->remarkbuf[20];
            v327 = *(&this->m_bWPXS + 192 * v326 + 334);
            v328 = *(&this->m_bWPXS + 192 * v326 + 335);
            v329 = *(&this->m_bWPXS + 192 * v326 + 336);
            v1076 = *(&this->m_bWPXS + 192 * v326 + 337);
            v323 = (int *)(&this->m_bWPXS + 624 * v326 + 2604);
            v323[2] = v328;
            v324 = (_DWORD *)v323 + 1;
            v323[3] = v329;
            v323[1] = v327;
            v325 = v1076;
          }
          v323[4] = v325;
          v330 = (_DWORD *)v323 + 5;
          *v330 = *v324;
          v330[1] = (unsigned long)v324[1];
          v330[2] = (unsigned long)v324[2];
          v330[3] = (unsigned long)v324[3];
          v317 = (int *)&this->m_ListSelNum[4][1824 * *(_DWORD *)&this->remarkbuf[20] + 4];
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v301 + 5065) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5061) = 0;
          v304 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v304 + 4820) )
          {
            v982[0] = *(&this->m_bWPXS + 192 * v304 + 358);
            v982[1] = *(&this->m_bWPXS + 192 * v304 + 359);
            v982[2] = *(&this->m_bWPXS + 192 * v304 + 360);
            v982[3] = *(&this->m_bWPXS + 192 * v304 + 361);
            (((UIWnd *)&this->m_ListSelNum[35][1824 * v304 + 1]))->UIWnd::sub_445FA0(v982);
            v305 = *(_DWORD *)&this->remarkbuf[20];
            v306 = *(&this->m_bWPXS + 192 * v305 + 358);
            v307 = *(&this->m_bWPXS + 192 * v305 + 359);
            v308 = *(&this->m_bWPXS + 192 * v305 + 360);
            v1149 = *(&this->m_bWPXS + 192 * v305 + 361);
            v309 = (int *)(&this->m_bWPXS + 624 * v305 + 2656);
            v309[2] = v307;
            v310 = (_DWORD *)v309 + 1;
            v309[3] = v308;
            v309[1] = v306;
            v311 = v1149;
          }
          else
          {
            v1008[0] = *(&this->m_bWPXS + 192 * v304 + 350);
            v1008[1] = *(&this->m_bWPXS + 192 * v304 + 351);
            v1008[2] = *(&this->m_bWPXS + 192 * v304 + 352);
            v1008[3] = *(&this->m_bWPXS + 192 * v304 + 353);
            (((UIWnd *)&this->m_ListSelNum[35][1824 * v304 + 1]))->UIWnd::sub_445FA0(v1008);
            v312 = *(_DWORD *)&this->remarkbuf[20];
            v313 = *(&this->m_bWPXS + 192 * v312 + 350);
            v314 = *(&this->m_bWPXS + 192 * v312 + 351);
            v315 = *(&this->m_bWPXS + 192 * v312 + 352);
            v1074 = *(&this->m_bWPXS + 192 * v312 + 353);
            v309 = (int *)(&this->m_bWPXS + 624 * v312 + 2656);
            v309[2] = v314;
            v310 = (_DWORD *)v309 + 1;
            v309[3] = v315;
            v309[1] = v313;
            v311 = v1074;
          }
          v309[4] = v311;
          v316 = (_DWORD *)v309 + 5;
          *v316 = *v310;
          v316[1] = (unsigned long)v310[1];
          v316[2] = (unsigned long)v310[2];
          v316[3] = (unsigned long)v310[3];
          v317 = (int *)&this->m_ListSelNum[35][1824 * *(_DWORD *)&this->remarkbuf[20] + 1];
        }
        (*(void ( **)(int *, int))*v317)(v317, 1);
LABEL_133:
        v331 = *(_DWORD *)&this->remarkbuf[20];
        v332 = v946[326];
        v333 = *(_WORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * v331) + 652);
        if ( v332 >= v333 )
        {
          if ( v332 <= v333 )
          {
LABEL_138:
            v346 = *(_DWORD *)&this->remarkbuf[20];
            v347 = v946[328];
            v348 = *(_WORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * v346) + 656);
            if ( v347 >= v348 )
            {
              if ( v347 > v348 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v346 + 5063) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5067) = 0;
                (*(void ( **)(int *, int))this->m_ListSelNum[20][1824
                                                                                    * *(_DWORD *)&this->remarkbuf[20]])(
                  &this->m_ListSelNum[20][1824 * *(_DWORD *)&this->remarkbuf[20]],
                  1);
                v358 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v358 + 4818) )
                {
                  v988[0] = *(&this->m_bWPXS + 192 * v358 + 334);
                  v988[1] = *(&this->m_bWPXS + 192 * v358 + 335);
                  v988[2] = *(&this->m_bWPXS + 192 * v358 + 336);
                  v988[3] = *(&this->m_bWPXS + 192 * v358 + 337);
                  (((UIWnd *)&this->m_ListSelNum[20][1824 * v358]))->UIWnd::sub_445FA0(v988);
                  v359 = *(_DWORD *)&this->remarkbuf[20];
                  v360 = *(&this->m_bWPXS + 192 * v359 + 334);
                  v361 = *(&this->m_bWPXS + 192 * v359 + 335);
                  v362 = *(&this->m_bWPXS + 192 * v359 + 336);
                  v1137 = *(&this->m_bWPXS + 192 * v359 + 337);
                  v363 = (int *)(&this->m_bWPXS + 624 * v359 + 2630);
                  v363[2] = v361;
                  v364 = (_DWORD *)v363 + 1;
                  v363[3] = v362;
                  v363[1] = v360;
                  v365 = v1137;
                }
                else
                {
                  v1022[0] = *(&this->m_bWPXS + 192 * v358 + 346);
                  v1022[1] = *(&this->m_bWPXS + 192 * v358 + 347);
                  v1022[2] = *(&this->m_bWPXS + 192 * v358 + 348);
                  v1022[3] = *(&this->m_bWPXS + 192 * v358 + 349);
                  (((UIWnd *)&this->m_ListSelNum[20][1824 * v358]))->UIWnd::sub_445FA0(v1022);
                  v366 = *(_DWORD *)&this->remarkbuf[20];
                  v367 = *(&this->m_bWPXS + 192 * v366 + 346);
                  v368 = *(&this->m_bWPXS + 192 * v366 + 347);
                  v369 = *(&this->m_bWPXS + 192 * v366 + 348);
                  v1082 = *(&this->m_bWPXS + 192 * v366 + 349);
                  v363 = (int *)(&this->m_bWPXS + 624 * v366 + 2630);
                  v363[2] = v368;
                  v364 = (_DWORD *)v363 + 1;
                  v363[3] = v369;
                  v363[1] = v367;
                  v365 = v1082;
                }
                v363[4] = v365;
                v370 = (_DWORD *)v363 + 5;
                *v370 = *v364;
                v370[1] = (unsigned long)v364[1];
                v370[2] = (unsigned long)v364[2];
                v370[3] = (unsigned long)v364[3];
              }
              goto LABEL_147;
            }
            *((_BYTE *)&this->m_bWPXS + 48 * v346 + 5067) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5063) = 0;
            v349 = *(_DWORD *)&this->remarkbuf[20];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v349 + 4822) )
            {
              v986[0] = *(&this->m_bWPXS + 192 * v349 + 350);
              v986[1] = *(&this->m_bWPXS + 192 * v349 + 351);
              v986[2] = *(&this->m_bWPXS + 192 * v349 + 352);
              v986[3] = *(&this->m_bWPXS + 192 * v349 + 353);
              (((UIWnd *)&this->m_ListSelNum[50][1824 * v349 + 2]))->UIWnd::sub_445FA0(v986);
              v350 = *(_DWORD *)&this->remarkbuf[20];
              v351 = *(&this->m_bWPXS + 192 * v350 + 350);
              v352 = *(&this->m_bWPXS + 192 * v350 + 351);
              v353 = *(&this->m_bWPXS + 192 * v350 + 352);
              v1122 = *(&this->m_bWPXS + 192 * v350 + 353);
              v278 = (int *)(&this->m_bWPXS + 624 * v350 + 2682);
              v278[2] = v352;
              v279 = (_DWORD *)v278 + 1;
              v278[3] = v353;
              v278[1] = v351;
              v280 = v1122;
            }
            else
            {
              v1010[0] = *(&this->m_bWPXS + 192 * v349 + 362);
              v1010[1] = *(&this->m_bWPXS + 192 * v349 + 363);
              v1010[2] = *(&this->m_bWPXS + 192 * v349 + 364);
              v1010[3] = *(&this->m_bWPXS + 192 * v349 + 365);
              (((UIWnd *)&this->m_ListSelNum[50][1824 * v349 + 2]))->UIWnd::sub_445FA0(v1010);
              v354 = *(_DWORD *)&this->remarkbuf[20];
              v355 = *(&this->m_bWPXS + 192 * v354 + 362);
              v356 = *(&this->m_bWPXS + 192 * v354 + 363);
              v357 = *(&this->m_bWPXS + 192 * v354 + 364);
              v1080 = *(&this->m_bWPXS + 192 * v354 + 365);
              v278 = (int *)(&this->m_bWPXS + 624 * v354 + 2682);
              v278[2] = v356;
              v279 = (_DWORD *)v278 + 1;
              v278[3] = v357;
              v278[1] = v355;
              v280 = v1080;
            }
            goto LABEL_115;
          }
          (*(void ( **)(int *, int))this->m_ListSelNum[12][1824 * v331 + 2])(
            &this->m_ListSelNum[12][1824 * v331 + 2],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4818) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5062) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5066) = 0;
          v341 = *(_DWORD *)&this->remarkbuf[20];
          v342 = *(&this->m_bWPXS + 192 * v341 + 342);
          v343 = *(&this->m_bWPXS + 192 * v341 + 343);
          v344 = *(&this->m_bWPXS + 192 * v341 + 344);
          v1078 = *(&this->m_bWPXS + 192 * v341 + 345);
          v338 = (int *)(&this->m_bWPXS + 624 * v341 + 2617);
          v338[2] = v343;
          v339 = (_DWORD *)v338 + 1;
          v338[3] = v344;
          v338[1] = v342;
          v340 = v1078;
        }
        else
        {
          (*(void ( **)(int *, int))this->m_ListSelNum[42][1824 * v331 + 4])(
            &this->m_ListSelNum[42][1824 * v331 + 4],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4822) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5066) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5062) = 0;
          v334 = *(_DWORD *)&this->remarkbuf[20];
          v335 = *(&this->m_bWPXS + 192 * v334 + 358);
          v336 = *(&this->m_bWPXS + 192 * v334 + 359);
          v337 = *(&this->m_bWPXS + 192 * v334 + 360);
          v1143 = *(&this->m_bWPXS + 192 * v334 + 361);
          v338 = (int *)(&this->m_bWPXS + 624 * v334 + 2669);
          v338[2] = v336;
          v339 = (_DWORD *)v338 + 1;
          v338[3] = v337;
          v338[1] = v335;
          v340 = v1143;
        }
        v338[4] = v340;
        v345 = (_DWORD *)v338 + 5;
        *v345 = *v339;
        v345[1] = (unsigned long)v339[1];
        v345[2] = (unsigned long)v339[2];
        v345[3] = (unsigned long)v339[3];
        goto LABEL_138;
      case 9:
        v371 = *(_DWORD *)&this->remarkbuf[20];
        if ( !*((_BYTE *)v3 + v371 + 614) )
          goto LABEL_406;
        v372 = *(&this->AttackNum + 289);
        if ( !g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v371] )
        {
          LOBYTE(v951) = *(_BYTE *)(v372 + 3284);
          (((UIPushButton *)&this->m_IsEquip[216 * v371 + 59][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Shoes.tga", v951);
          for ( k = 0; k < 8; ++k )
            (*(void ( **)(int *, _DWORD))this->m_ListSelNum[58][1824
                                                                                   * *(_DWORD *)&this->remarkbuf[20]
                                                                                   + 38 * k])(
              &this->m_ListSelNum[58][1824 * *(_DWORD *)&this->remarkbuf[20] + 38 * k],
              0);
          v374 = v3[325];
          v375 = v374 < 0;
          v11 = v374 <= 0;
          v376 = *(_DWORD *)&this->remarkbuf[20];
          if ( v11 )
          {
            if ( !v375 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v376 + 5068) = 0;
LABEL_158:
              v391 = v946[327];
              v392 = v391 < 0;
              v11 = v391 <= 0;
              v393 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                v407 = 3 * v393;
                if ( v392 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v407 + 5073) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5069) = 0;
                  v408 = *(_DWORD *)&this->remarkbuf[20];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v408 + 4828) )
                  {
                    v992[0] = *(&this->m_bWPXS + 192 * v408 + 390);
                    v992[1] = *(&this->m_bWPXS + 192 * v408 + 391);
                    v992[2] = *(&this->m_bWPXS + 192 * v408 + 392);
                    v992[3] = *(&this->m_bWPXS + 192 * v408 + 393);
                    (((UIWnd *)&this->m_ListSelNum[96][1824 * v408]))->UIWnd::sub_445FA0(v992);
                    v409 = *(_DWORD *)&this->remarkbuf[20];
                    v410 = *(&this->m_bWPXS + 192 * v409 + 390);
                    v411 = *(&this->m_bWPXS + 192 * v409 + 391);
                    v412 = *(&this->m_bWPXS + 192 * v409 + 392);
                    v1126 = *(&this->m_bWPXS + 192 * v409 + 393);
                    v413 = (int *)(&this->m_bWPXS + 624 * v409 + 2760);
                    v413[2] = v411;
                    v414 = (_DWORD *)v413 + 1;
                    v413[3] = v412;
                    v413[1] = v410;
                    v415 = v1126;
                  }
                  else
                  {
                    v1028[0] = *(&this->m_bWPXS + 192 * v408 + 382);
                    v1028[1] = *(&this->m_bWPXS + 192 * v408 + 383);
                    v1028[2] = *(&this->m_bWPXS + 192 * v408 + 384);
                    v1028[3] = *(&this->m_bWPXS + 192 * v408 + 385);
                    (((UIWnd *)&this->m_ListSelNum[96][1824 * v408]))->UIWnd::sub_445FA0(v1028);
                    v416 = *(_DWORD *)&this->remarkbuf[20];
                    v417 = *(&this->m_bWPXS + 192 * v416 + 382);
                    v418 = *(&this->m_bWPXS + 192 * v416 + 383);
                    v419 = *(&this->m_bWPXS + 192 * v416 + 384);
                    v1088 = *(&this->m_bWPXS + 192 * v416 + 385);
                    v413 = (int *)(&this->m_bWPXS + 624 * v416 + 2760);
                    v413[2] = v418;
                    v414 = (_DWORD *)v413 + 1;
                    v413[3] = v419;
                    v413[1] = v417;
                    v415 = v1088;
                  }
                  v413[4] = v415;
                  v420 = (_DWORD *)v413 + 5;
                  *v420 = *v414;
                  v420[1] = (unsigned long)v414[1];
                  v420[2] = (unsigned long)v414[2];
                  v420[3] = (unsigned long)v414[3];
                  (*(void ( **)(int *, int))this->m_ListSelNum[96][1824
                                                                                      * *(_DWORD *)&this->remarkbuf[20]])(
                    &this->m_ListSelNum[96][1824 * *(_DWORD *)&this->remarkbuf[20]],
                    1);
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v407 + 5069) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v393 + 5069) = 1;
                v394 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v394 + 4824) )
                {
                  v957[0] = *(&this->m_bWPXS + 192 * v394 + 374);
                  v957[1] = *(&this->m_bWPXS + 192 * v394 + 375);
                  v957[2] = *(&this->m_bWPXS + 192 * v394 + 376);
                  v957[3] = *(&this->m_bWPXS + 192 * v394 + 377);
                  (((UIWnd *)&this->m_ListSelNum[65][1824 * v394 + 3]))->UIWnd::sub_445FA0(v957);
                  v395 = *(_DWORD *)&this->remarkbuf[20];
                  v396 = *(&this->m_bWPXS + 192 * v395 + 374);
                  v397 = *(&this->m_bWPXS + 192 * v395 + 375);
                  v398 = *(&this->m_bWPXS + 192 * v395 + 376);
                  v1138 = *(&this->m_bWPXS + 192 * v395 + 377);
                  v399 = (int *)(&this->m_bWPXS + 624 * v395 + 2708);
                  v399[2] = v397;
                  v400 = (_DWORD *)v399 + 1;
                  v399[3] = v398;
                  v399[1] = v396;
                  v401 = v1138;
                }
                else
                {
                  v1012[0] = *(&this->m_bWPXS + 192 * v394 + 366);
                  v1012[1] = *(&this->m_bWPXS + 192 * v394 + 367);
                  v1012[2] = *(&this->m_bWPXS + 192 * v394 + 368);
                  v1012[3] = *(&this->m_bWPXS + 192 * v394 + 369);
                  (((UIWnd *)&this->m_ListSelNum[65][1824 * v394 + 3]))->UIWnd::sub_445FA0(v1012);
                  v402 = *(_DWORD *)&this->remarkbuf[20];
                  v403 = *(&this->m_bWPXS + 192 * v402 + 366);
                  v404 = *(&this->m_bWPXS + 192 * v402 + 367);
                  v405 = *(&this->m_bWPXS + 192 * v402 + 368);
                  v1086 = *(&this->m_bWPXS + 192 * v402 + 369);
                  v399 = (int *)(&this->m_bWPXS + 624 * v402 + 2708);
                  v399[2] = v404;
                  v400 = (_DWORD *)v399 + 1;
                  v399[3] = v405;
                  v399[1] = v403;
                  v401 = v1086;
                }
                v399[4] = v401;
                v406 = (_DWORD *)v399 + 5;
                *v406 = *v400;
                v406[1] = (unsigned long)v400[1];
                v406[2] = (unsigned long)v400[2];
                v406[3] = (unsigned long)v400[3];
                (*(void ( **)(int *, int))this->m_ListSelNum[65][1824
                                                                                    * *(_DWORD *)&this->remarkbuf[20]
                                                                                    + 3])(
                  &this->m_ListSelNum[65][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
                  1);
              }
              v421 = v946[326];
              v422 = v421 < 0;
              v11 = v421 <= 0;
              v423 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                if ( !v422 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v423 + 5070) = 0;
                  goto LABEL_175;
                }
                (*(void ( **)(int *, int))this->m_ListSelNum[103][1824 * v423 + 3])(
                  &this->m_ListSelNum[103][1824 * v423 + 3],
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4830) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5074) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5070) = 0;
                v434 = *(_DWORD *)&this->remarkbuf[20];
                v435 = *(&this->m_bWPXS + 192 * v434 + 390);
                v436 = *(&this->m_bWPXS + 192 * v434 + 391);
                v437 = *(&this->m_bWPXS + 192 * v434 + 392);
                v1090 = *(&this->m_bWPXS + 192 * v434 + 393);
                v428 = (int *)(&this->m_bWPXS + 624 * v434 + 2773);
                v428[2] = v436;
                v429 = (_DWORD *)v428 + 1;
                v428[3] = v437;
                v428[1] = v435;
                v430 = v1090;
              }
              else
              {
                (*(void ( **)(int *, int))this->m_ListSelNum[73][1824 * v423 + 1])(
                  &this->m_ListSelNum[73][1824 * v423 + 1],
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4826) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5070) = 1;
                v424 = *(_DWORD *)&this->remarkbuf[20];
                v425 = *(&this->m_bWPXS + 192 * v424 + 374);
                v426 = *(&this->m_bWPXS + 192 * v424 + 375);
                v427 = *(&this->m_bWPXS + 192 * v424 + 376);
                v1140 = *(&this->m_bWPXS + 192 * v424 + 377);
                v428 = (int *)(&this->m_bWPXS + 624 * v424 + 2721);
                v428[2] = v426;
                v429 = (_DWORD *)v428 + 1;
                v428[3] = v427;
                v428[1] = v425;
                v430 = v1140;
              }
              v428[4] = v430;
              v431 = (_DWORD *)v428 + 5;
              *v431 = *v429;
              v431[1] = (unsigned long)v429[1];
              v432 = (unsigned long)v429[2];
              v433 = (unsigned long)v429[3];
              v431[2] = v432;
              v431[3] = v433;
LABEL_175:
              v438 = v946[328];
              v439 = v438 < 0;
              v11 = v438 <= 0;
              v440 = *(_DWORD *)&this->remarkbuf[20];
              if ( !v11 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v440 + 5071) = 1;
                v441 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v441 + 4826) )
                {
                  v994[0] = *(&this->m_bWPXS + 192 * v441 + 366);
                  v994[1] = *(&this->m_bWPXS + 192 * v441 + 367);
                  v994[2] = *(&this->m_bWPXS + 192 * v441 + 368);
                  v994[3] = *(&this->m_bWPXS + 192 * v441 + 369);
                  (((UIWnd *)&this->m_ListSelNum[80][1824 * v441 + 4]))->UIWnd::sub_445FA0(v994);
                  v442 = *(_DWORD *)&this->remarkbuf[20];
                  v443 = *(&this->m_bWPXS + 192 * v442 + 366);
                  v444 = *(&this->m_bWPXS + 192 * v442 + 367);
                  v445 = *(&this->m_bWPXS + 192 * v442 + 368);
                  v1128 = *(&this->m_bWPXS + 192 * v442 + 369);
                  v446 = (int *)(&this->m_bWPXS + 624 * v442 + 2734);
                  v446[2] = v444;
                  v447 = (_DWORD *)v446 + 1;
                  v446[3] = v445;
                  v446[1] = v443;
                  v448 = v1128;
                }
                else
                {
                  v1014[0] = *(&this->m_bWPXS + 192 * v441 + 378);
                  v1014[1] = *(&this->m_bWPXS + 192 * v441 + 379);
                  v1014[2] = *(&this->m_bWPXS + 192 * v441 + 380);
                  v1014[3] = *(&this->m_bWPXS + 192 * v441 + 381);
                  (((UIWnd *)&this->m_ListSelNum[80][1824 * v441 + 4]))->UIWnd::sub_445FA0(v1014);
                  v449 = *(_DWORD *)&this->remarkbuf[20];
                  v450 = *(&this->m_bWPXS + 192 * v449 + 378);
                  v451 = *(&this->m_bWPXS + 192 * v449 + 379);
                  v452 = *(&this->m_bWPXS + 192 * v449 + 380);
                  v1092 = *(&this->m_bWPXS + 192 * v449 + 381);
                  v446 = (int *)(&this->m_bWPXS + 624 * v449 + 2734);
                  v446[2] = v451;
                  v447 = (_DWORD *)v446 + 1;
                  v446[3] = v452;
                  v446[1] = v450;
                  v448 = v1092;
                }
                v446[4] = v448;
                v453 = (_DWORD *)v446 + 5;
                *v453 = *v447;
                v453[1] = (unsigned long)v447[1];
                v453[2] = (unsigned long)v447[2];
                v453[3] = (unsigned long)v447[3];
                (*(void ( **)(int *, int))this->m_ListSelNum[80][1824
                                                                                    * *(_DWORD *)&this->remarkbuf[20]
                                                                                    + 4])(
                  &this->m_ListSelNum[80][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
                  1);
                goto LABEL_216;
              }
              v454 = 3 * v440;
              if ( !v439 )
              {
                *((_BYTE *)&this->m_bWPXS + 16 * v454 + 5071) = 0;
LABEL_216:
                (**(void ( ***)(_BYTE *, int))&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 59][1])((_BYTE *)(&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 59][1]), (int)(1));
                v3 = (_WORD *)v946;
                goto LABEL_406;
              }
              *((_BYTE *)&this->m_bWPXS + 16 * v454 + 5075) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5071) = 0;
              v455 = *(_DWORD *)&this->remarkbuf[20];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v455 + 4830) )
              {
                v958[0] = *(&this->m_bWPXS + 192 * v455 + 382);
                v958[1] = *(&this->m_bWPXS + 192 * v455 + 383);
                v958[2] = *(&this->m_bWPXS + 192 * v455 + 384);
                v958[3] = *(&this->m_bWPXS + 192 * v455 + 385);
                (((UIWnd *)&this->m_ListSelNum[111][1824 * v455 + 1]))->UIWnd::sub_445FA0(v958);
                v456 = *(_DWORD *)&this->remarkbuf[20];
                v457 = *(&this->m_bWPXS + 192 * v456 + 382);
                v458 = *(&this->m_bWPXS + 192 * v456 + 383);
                v459 = *(&this->m_bWPXS + 192 * v456 + 384);
                v1142 = *(&this->m_bWPXS + 192 * v456 + 385);
                v460 = (int *)(&this->m_bWPXS + 624 * v456 + 2786);
                v460[2] = v458;
                v461 = (_DWORD *)v460 + 1;
                v460[3] = v459;
                v460[1] = v457;
                v462 = v1142;
              }
              else
              {
                v959[0] = *(&this->m_bWPXS + 192 * v455 + 394);
                v959[1] = *(&this->m_bWPXS + 192 * v455 + 395);
                v959[2] = *(&this->m_bWPXS + 192 * v455 + 396);
                v959[3] = *(&this->m_bWPXS + 192 * v455 + 397);
                (((UIWnd *)&this->m_ListSelNum[111][1824 * v455 + 1]))->UIWnd::sub_445FA0(v959);
                v463 = *(_DWORD *)&this->remarkbuf[20];
                v464 = *(&this->m_bWPXS + 192 * v463 + 394);
                v465 = *(&this->m_bWPXS + 192 * v463 + 395);
                v466 = *(&this->m_bWPXS + 192 * v463 + 396);
                v1094 = *(&this->m_bWPXS + 192 * v463 + 397);
                v460 = (int *)(&this->m_bWPXS + 624 * v463 + 2786);
                v460[2] = v465;
                v461 = (_DWORD *)v460 + 1;
                v460[3] = v466;
                v460[1] = v464;
                v462 = v1094;
              }
LABEL_184:
              v460[4] = v462;
              v467 = (_DWORD *)v460 + 5;
              *v467 = *v461;
              v467[1] = (unsigned long)v461[1];
              v467[2] = (unsigned long)v461[2];
              v467[3] = (unsigned long)v461[3];
              (*(void ( **)(int *, int))this->m_ListSelNum[111][1824
                                                                                   * *(_DWORD *)&this->remarkbuf[20]
                                                                                   + 1])(
                &this->m_ListSelNum[111][1824 * *(_DWORD *)&this->remarkbuf[20] + 1],
                1);
              goto LABEL_216;
            }
            (*(void ( **)(int *, int))this->m_ListSelNum[88][1824 * v376 + 2])(
              &this->m_ListSelNum[88][1824 * v376 + 2],
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4828) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5072) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5068) = 0;
            v387 = *(_DWORD *)&this->remarkbuf[20];
            v388 = *(&this->m_bWPXS + 192 * v387 + 382);
            v389 = *(&this->m_bWPXS + 192 * v387 + 383);
            v390 = *(&this->m_bWPXS + 192 * v387 + 384);
            v1084 = *(&this->m_bWPXS + 192 * v387 + 385);
            v381 = (int *)(&this->m_bWPXS + 624 * v387 + 2747);
            v381[2] = v389;
            v382 = (_DWORD *)v381 + 1;
            v381[3] = v390;
            v381[1] = v388;
            v383 = v1084;
          }
          else
          {
            (*(void ( **)(int *, int))this->m_ListSelNum[58][1824 * v376])(
              &this->m_ListSelNum[58][1824 * v376],
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4824) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5068) = 1;
            v377 = *(_DWORD *)&this->remarkbuf[20];
            v378 = *(&this->m_bWPXS + 192 * v377 + 366);
            v379 = *(&this->m_bWPXS + 192 * v377 + 367);
            v380 = *(&this->m_bWPXS + 192 * v377 + 368);
            v1124 = *(&this->m_bWPXS + 192 * v377 + 369);
            v381 = (int *)(&this->m_bWPXS + 624 * v377 + 2695);
            v381[2] = v379;
            v382 = (_DWORD *)v381 + 1;
            v381[3] = v380;
            v381[1] = v378;
            v383 = v1124;
          }
          v381[4] = v383;
          v384 = (_DWORD *)v381 + 5;
          *v384 = *v382;
          v384[1] = (unsigned long)v382[1];
          v385 = (unsigned long)v382[2];
          v386 = (unsigned long)v382[3];
          v384[2] = v385;
          v384[3] = v386;
          goto LABEL_158;
        }
        LOBYTE(v947) = *(_BYTE *)(v372 + 3284);
        (((UIPushButton *)&this->m_IsEquip[216 * v371 + 59][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Shoes.tga", v947);
        v468 = *(_DWORD *)&this->remarkbuf[20];
        v469 = v3[325];
        v470 = HIWORD(g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v468]->rolevalue[3]);
        if ( v469 >= v470 )
        {
          if ( v469 <= v470 )
            goto LABEL_191;
          (*(void ( **)(int *, int))this->m_ListSelNum[58][1824 * v468])(
            &this->m_ListSelNum[58][1824 * v468],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4824) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5068) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5072) = 0;
          v478 = *(_DWORD *)&this->remarkbuf[20];
          v479 = *(&this->m_bWPXS + 192 * v478 + 366);
          v480 = *(&this->m_bWPXS + 192 * v478 + 367);
          v481 = *(&this->m_bWPXS + 192 * v478 + 368);
          v1096 = *(&this->m_bWPXS + 192 * v478 + 369);
          v475 = (int *)(&this->m_bWPXS + 624 * v478 + 2695);
          v475[2] = v480;
          v476 = (_DWORD *)v475 + 1;
          v475[3] = v481;
          v475[1] = v479;
          v477 = v1096;
        }
        else
        {
          (*(void ( **)(int *, int))this->m_ListSelNum[88][1824 * v468 + 2])(
            &this->m_ListSelNum[88][1824 * v468 + 2],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4828) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5072) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5068) = 0;
          v471 = *(_DWORD *)&this->remarkbuf[20];
          v472 = *(&this->m_bWPXS + 192 * v471 + 382);
          v473 = *(&this->m_bWPXS + 192 * v471 + 383);
          v474 = *(&this->m_bWPXS + 192 * v471 + 384);
          v1130 = *(&this->m_bWPXS + 192 * v471 + 385);
          v475 = (int *)(&this->m_bWPXS + 624 * v471 + 2747);
          v475[2] = v473;
          v476 = (_DWORD *)v475 + 1;
          v475[3] = v474;
          v475[1] = v472;
          v477 = v1130;
        }
        v475[4] = v477;
        v482 = (_DWORD *)v475 + 5;
        *v482 = *v476;
        v482[1] = (unsigned long)v476[1];
        v482[2] = (unsigned long)v476[2];
        v482[3] = (unsigned long)v476[3];
LABEL_191:
        v483 = *(_DWORD *)&this->remarkbuf[20];
        v484 = v946[327];
        v485 = HIWORD(g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v483]->rolevalue[4]);
        if ( v484 >= v485 )
        {
          if ( v484 <= v485 )
            goto LABEL_202;
          *((_BYTE *)&this->m_bWPXS + 48 * v483 + 5069) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5073) = 0;
          v500 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v500 + 4824) )
          {
            v965[0] = *(&this->m_bWPXS + 192 * v500 + 374);
            v965[1] = *(&this->m_bWPXS + 192 * v500 + 375);
            v965[2] = *(&this->m_bWPXS + 192 * v500 + 376);
            v965[3] = *(&this->m_bWPXS + 192 * v500 + 377);
            (((UIWnd *)&this->m_ListSelNum[65][1824 * v500 + 3]))->UIWnd::sub_445FA0(v965);
            v501 = *(_DWORD *)&this->remarkbuf[20];
            v502 = *(&this->m_bWPXS + 192 * v501 + 374);
            v503 = *(&this->m_bWPXS + 192 * v501 + 375);
            v504 = *(&this->m_bWPXS + 192 * v501 + 376);
            v1132 = *(&this->m_bWPXS + 192 * v501 + 377);
            v505 = (int *)(&this->m_bWPXS + 624 * v501 + 2708);
            v505[2] = v503;
            v506 = (_DWORD *)v505 + 1;
            v505[3] = v504;
            v505[1] = v502;
            v507 = v1132;
          }
          else
          {
            v967[0] = *(&this->m_bWPXS + 192 * v500 + 366);
            v967[1] = *(&this->m_bWPXS + 192 * v500 + 367);
            v967[2] = *(&this->m_bWPXS + 192 * v500 + 368);
            v967[3] = *(&this->m_bWPXS + 192 * v500 + 369);
            (((UIWnd *)&this->m_ListSelNum[65][1824 * v500 + 3]))->UIWnd::sub_445FA0(v967);
            v508 = *(_DWORD *)&this->remarkbuf[20];
            v509 = *(&this->m_bWPXS + 192 * v508 + 366);
            v510 = *(&this->m_bWPXS + 192 * v508 + 367);
            v511 = *(&this->m_bWPXS + 192 * v508 + 368);
            v1100 = *(&this->m_bWPXS + 192 * v508 + 369);
            v505 = (int *)(&this->m_bWPXS + 624 * v508 + 2708);
            v505[2] = v510;
            v506 = (_DWORD *)v505 + 1;
            v505[3] = v511;
            v505[1] = v509;
            v507 = v1100;
          }
          v505[4] = v507;
          v512 = (_DWORD *)v505 + 5;
          *v512 = *v506;
          v512[1] = (unsigned long)v506[1];
          v512[2] = (unsigned long)v506[2];
          v512[3] = (unsigned long)v506[3];
          v499 = (int *)&this->m_ListSelNum[65][1824 * *(_DWORD *)&this->remarkbuf[20] + 3];
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v483 + 5073) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5069) = 0;
          v486 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v486 + 4828) )
          {
            v961[0] = *(&this->m_bWPXS + 192 * v486 + 390);
            v961[1] = *(&this->m_bWPXS + 192 * v486 + 391);
            v961[2] = *(&this->m_bWPXS + 192 * v486 + 392);
            v961[3] = *(&this->m_bWPXS + 192 * v486 + 393);
            (((UIWnd *)&this->m_ListSelNum[96][1824 * v486]))->UIWnd::sub_445FA0(v961);
            v487 = *(_DWORD *)&this->remarkbuf[20];
            v488 = *(&this->m_bWPXS + 192 * v487 + 390);
            v489 = *(&this->m_bWPXS + 192 * v487 + 391);
            v490 = *(&this->m_bWPXS + 192 * v487 + 392);
            v1144 = *(&this->m_bWPXS + 192 * v487 + 393);
            v491 = (int *)(&this->m_bWPXS + 624 * v487 + 2760);
            v491[2] = v489;
            v492 = (_DWORD *)v491 + 1;
            v491[3] = v490;
            v491[1] = v488;
            v493 = v1144;
          }
          else
          {
            v963[0] = *(&this->m_bWPXS + 192 * v486 + 382);
            v963[1] = *(&this->m_bWPXS + 192 * v486 + 383);
            v963[2] = *(&this->m_bWPXS + 192 * v486 + 384);
            v963[3] = *(&this->m_bWPXS + 192 * v486 + 385);
            (((UIWnd *)&this->m_ListSelNum[96][1824 * v486]))->UIWnd::sub_445FA0(v963);
            v494 = *(_DWORD *)&this->remarkbuf[20];
            v495 = *(&this->m_bWPXS + 192 * v494 + 382);
            v496 = *(&this->m_bWPXS + 192 * v494 + 383);
            v497 = *(&this->m_bWPXS + 192 * v494 + 384);
            v1098 = *(&this->m_bWPXS + 192 * v494 + 385);
            v491 = (int *)(&this->m_bWPXS + 624 * v494 + 2760);
            v491[2] = v496;
            v492 = (_DWORD *)v491 + 1;
            v491[3] = v497;
            v491[1] = v495;
            v493 = v1098;
          }
          v491[4] = v493;
          v498 = (_DWORD *)v491 + 5;
          *v498 = *v492;
          v498[1] = (unsigned long)v492[1];
          v498[2] = (unsigned long)v492[2];
          v498[3] = (unsigned long)v492[3];
          v499 = (int *)&this->m_ListSelNum[96][1824 * *(_DWORD *)&this->remarkbuf[20]];
        }
        (*(void ( **)(int *, int))*v499)(v499, 1);
LABEL_202:
        v513 = *(_DWORD *)&this->remarkbuf[20];
        v514 = v946[326];
        v515 = g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v513]->rolevalue[4];
        if ( v514 >= v515 )
        {
          if ( v514 <= v515 )
          {
LABEL_207:
            v528 = *(_DWORD *)&this->remarkbuf[20];
            v529 = v946[328];
            v530 = g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v528]->rolevalue[5];
            if ( v529 >= v530 )
            {
              if ( v529 > v530 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v528 + 5071) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5075) = 0;
                (*(void ( **)(int *, int))this->m_ListSelNum[80][1824
                                                                                    * *(_DWORD *)&this->remarkbuf[20]
                                                                                    + 4])(
                  &this->m_ListSelNum[80][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
                  1);
                v540 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v540 + 4826) )
                {
                  v973[0] = *(&this->m_bWPXS + 192 * v540 + 366);
                  v973[1] = *(&this->m_bWPXS + 192 * v540 + 367);
                  v973[2] = *(&this->m_bWPXS + 192 * v540 + 368);
                  v973[3] = *(&this->m_bWPXS + 192 * v540 + 369);
                  (((UIWnd *)&this->m_ListSelNum[80][1824 * v540 + 4]))->UIWnd::sub_445FA0(v973);
                  v541 = *(_DWORD *)&this->remarkbuf[20];
                  v542 = *(&this->m_bWPXS + 192 * v541 + 366);
                  v543 = *(&this->m_bWPXS + 192 * v541 + 367);
                  v544 = *(&this->m_bWPXS + 192 * v541 + 368);
                  v1043 = *(&this->m_bWPXS + 192 * v541 + 369);
                  v545 = (int *)(&this->m_bWPXS + 624 * v541 + 2734);
                  v545[2] = v543;
                  v546 = (_DWORD *)v545 + 1;
                  v545[1] = v542;
                  v545[3] = v544;
                  v547 = v1043;
                }
                else
                {
                  v975[0] = *(&this->m_bWPXS + 192 * v540 + 378);
                  v975[1] = *(&this->m_bWPXS + 192 * v540 + 379);
                  v975[2] = *(&this->m_bWPXS + 192 * v540 + 380);
                  v975[3] = *(&this->m_bWPXS + 192 * v540 + 381);
                  (((UIWnd *)&this->m_ListSelNum[80][1824 * v540 + 4]))->UIWnd::sub_445FA0(v975);
                  v548 = *(_DWORD *)&this->remarkbuf[20];
                  v549 = *(&this->m_bWPXS + 192 * v548 + 378);
                  v550 = *(&this->m_bWPXS + 192 * v548 + 379);
                  v551 = *(&this->m_bWPXS + 192 * v548 + 380);
                  v1045 = *(&this->m_bWPXS + 192 * v548 + 381);
                  v545 = (int *)(&this->m_bWPXS + 624 * v548 + 2734);
                  v545[2] = v550;
                  v546 = (_DWORD *)v545 + 1;
                  v545[1] = v549;
                  v545[3] = v551;
                  v547 = v1045;
                }
                v545[4] = v547;
                v552 = (_DWORD *)v545 + 5;
                *v552 = *v546;
                v552[1] = (unsigned long)v546[1];
                v552[2] = (unsigned long)v546[2];
                v552[3] = (unsigned long)v546[3];
              }
              goto LABEL_216;
            }
            *((_BYTE *)&this->m_bWPXS + 48 * v528 + 5075) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5071) = 0;
            v531 = *(_DWORD *)&this->remarkbuf[20];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v531 + 4830) )
            {
              v969[0] = *(&this->m_bWPXS + 192 * v531 + 382);
              v969[1] = *(&this->m_bWPXS + 192 * v531 + 383);
              v969[2] = *(&this->m_bWPXS + 192 * v531 + 384);
              v969[3] = *(&this->m_bWPXS + 192 * v531 + 385);
              (((UIWnd *)&this->m_ListSelNum[111][1824 * v531 + 1]))->UIWnd::sub_445FA0(v969);
              v532 = *(_DWORD *)&this->remarkbuf[20];
              v533 = *(&this->m_bWPXS + 192 * v532 + 382);
              v534 = *(&this->m_bWPXS + 192 * v532 + 383);
              v535 = *(&this->m_bWPXS + 192 * v532 + 384);
              v1039 = *(&this->m_bWPXS + 192 * v532 + 385);
              v460 = (int *)(&this->m_bWPXS + 624 * v532 + 2786);
              v460[2] = v534;
              v461 = (_DWORD *)v460 + 1;
              v460[3] = v535;
              v460[1] = v533;
              v462 = v1039;
            }
            else
            {
              v971[0] = *(&this->m_bWPXS + 192 * v531 + 394);
              v971[1] = *(&this->m_bWPXS + 192 * v531 + 395);
              v971[2] = *(&this->m_bWPXS + 192 * v531 + 396);
              v971[3] = *(&this->m_bWPXS + 192 * v531 + 397);
              (((UIWnd *)&this->m_ListSelNum[111][1824 * v531 + 1]))->UIWnd::sub_445FA0(v971);
              v536 = *(_DWORD *)&this->remarkbuf[20];
              v537 = *(&this->m_bWPXS + 192 * v536 + 394);
              v538 = *(&this->m_bWPXS + 192 * v536 + 395);
              v539 = *(&this->m_bWPXS + 192 * v536 + 396);
              v1041 = *(&this->m_bWPXS + 192 * v536 + 397);
              v460 = (int *)(&this->m_bWPXS + 624 * v536 + 2786);
              v460[2] = v538;
              v461 = (_DWORD *)v460 + 1;
              v460[3] = v539;
              v460[1] = v537;
              v462 = v1041;
            }
            goto LABEL_184;
          }
          (*(void ( **)(int *, int))this->m_ListSelNum[73][1824 * v513 + 1])(
            &this->m_ListSelNum[73][1824 * v513 + 1],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4826) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5070) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5074) = 0;
          v523 = *(_DWORD *)&this->remarkbuf[20];
          v524 = *(&this->m_bWPXS + 192 * v523 + 374);
          v525 = *(&this->m_bWPXS + 192 * v523 + 375);
          v526 = *(&this->m_bWPXS + 192 * v523 + 376);
          v1037 = *(&this->m_bWPXS + 192 * v523 + 377);
          v520 = (int *)(&this->m_bWPXS + 624 * v523 + 2721);
          v520[2] = v525;
          v521 = (_DWORD *)v520 + 1;
          v520[3] = v526;
          v520[1] = v524;
          v522 = v1037;
        }
        else
        {
          (*(void ( **)(int *, int))this->m_ListSelNum[103][1824 * v513 + 3])(
            &this->m_ListSelNum[103][1824 * v513 + 3],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4830) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5074) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5070) = 0;
          v516 = *(_DWORD *)&this->remarkbuf[20];
          v517 = *(&this->m_bWPXS + 192 * v516 + 390);
          v518 = *(&this->m_bWPXS + 192 * v516 + 391);
          v519 = *(&this->m_bWPXS + 192 * v516 + 392);
          v1035 = *(&this->m_bWPXS + 192 * v516 + 393);
          v520 = (int *)(&this->m_bWPXS + 624 * v516 + 2773);
          v520[2] = v518;
          v521 = (_DWORD *)v520 + 1;
          v520[3] = v519;
          v520[1] = v517;
          v522 = v1035;
        }
        v520[4] = v522;
        v527 = (_DWORD *)v520 + 5;
        *v527 = *v521;
        v527[1] = (unsigned long)v521[1];
        v527[2] = (unsigned long)v521[2];
        v527[3] = (unsigned long)v521[3];
        goto LABEL_207;
      case 0xA:
        v553 = *(_DWORD *)&this->remarkbuf[20];
        if ( !*((_BYTE *)v3 + v553 + 614) )
          goto LABEL_406;
        v554 = *(&this->AttackNum + 289);
        if ( !g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v553 + 3] )
        {
          LOBYTE(v948) = *(_BYTE *)(v554 + 3284);
          (((UIPushButton *)&this->m_NotesNull[54 * v553 + 295][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn.tga", v948);
          for ( m = 0; m < 8; ++m )
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[534][1824
                                                                                  * *(_DWORD *)&this->remarkbuf[20]
                                                                                  + 2
                                                                                  + 38 * m])((SaleUI_SortData *)(&this->m_sort[534][1824 * *(_DWORD *)&this->remarkbuf[20] + 2 + 38 * m]), (_DWORD)(0));
          v556 = v3[325];
          v557 = v556 < 0;
          v11 = v556 <= 0;
          v558 = *(_DWORD *)&this->remarkbuf[20];
          if ( v11 )
          {
            if ( !v557 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v558 + 5052) = 0;
LABEL_227:
              v571 = v946[327];
              v572 = v571 < 0;
              v11 = v571 <= 0;
              v573 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                v587 = 3 * v573;
                if ( v572 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v587 + 5057) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5053) = 0;
                  v588 = *(_DWORD *)&this->remarkbuf[20];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v588 + 4812) )
                  {
                    v981[0] = *(&this->m_bWPXS + 192 * v588 + 326);
                    v981[1] = *(&this->m_bWPXS + 192 * v588 + 327);
                    v981[2] = *(&this->m_bWPXS + 192 * v588 + 328);
                    v981[3] = *(&this->m_bWPXS + 192 * v588 + 329);
                    (((UIWnd *)&this->m_sort[572][1824 * v588 + 2]))->UIWnd::sub_445FA0(v981);
                    v589 = *(_DWORD *)&this->remarkbuf[20];
                    v590 = *(&this->m_bWPXS + 192 * v589 + 326);
                    v591 = *(&this->m_bWPXS + 192 * v589 + 327);
                    v592 = *(&this->m_bWPXS + 192 * v589 + 328);
                    v1055 = *(&this->m_bWPXS + 192 * v589 + 329);
                    v593 = (int *)(&this->m_bWPXS + 624 * v589 + 2552);
                    v593[2] = v591;
                    v594 = (_DWORD *)v593 + 1;
                    v593[1] = v590;
                    v593[3] = v592;
                    v595 = v1055;
                  }
                  else
                  {
                    v983[0] = *(&this->m_bWPXS + 192 * v588 + 318);
                    v983[1] = *(&this->m_bWPXS + 192 * v588 + 319);
                    v983[2] = *(&this->m_bWPXS + 192 * v588 + 320);
                    v983[3] = *(&this->m_bWPXS + 192 * v588 + 321);
                    (((UIWnd *)&this->m_sort[572][1824 * v588 + 2]))->UIWnd::sub_445FA0(v983);
                    v596 = *(_DWORD *)&this->remarkbuf[20];
                    v597 = *(&this->m_bWPXS + 192 * v596 + 318);
                    v598 = *(&this->m_bWPXS + 192 * v596 + 319);
                    v599 = *(&this->m_bWPXS + 192 * v596 + 320);
                    v1057 = *(&this->m_bWPXS + 192 * v596 + 321);
                    v593 = (int *)(&this->m_bWPXS + 624 * v596 + 2552);
                    v593[2] = v598;
                    v594 = (_DWORD *)v593 + 1;
                    v593[1] = v597;
                    v593[3] = v599;
                    v595 = v1057;
                  }
                  v593[4] = v595;
                  v600 = (_DWORD *)v593 + 5;
                  *v600 = *v594;
                  v600[1] = (unsigned long)v594[1];
                  v600[2] = (unsigned long)v594[2];
                  v600[3] = (unsigned long)v594[3];
                  (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[572][1824
                                                                                     * *(_DWORD *)&this->remarkbuf[20]
                                                                                     + 2])((SaleUI_SortData *)(&this->m_sort[572][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (int)(1));
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v587 + 5053) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v573 + 5053) = 1;
                v574 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v574 + 4808) )
                {
                  v977[0] = *(&this->m_bWPXS + 192 * v574 + 310);
                  v977[1] = *(&this->m_bWPXS + 192 * v574 + 311);
                  v977[2] = *(&this->m_bWPXS + 192 * v574 + 312);
                  v977[3] = *(&this->m_bWPXS + 192 * v574 + 313);
                  (((UIWnd *)&this->m_sort[542][1824 * v574]))->UIWnd::sub_445FA0(v977);
                  v575 = *(_DWORD *)&this->remarkbuf[20];
                  v576 = *(&this->m_bWPXS + 192 * v575 + 310);
                  v577 = *(&this->m_bWPXS + 192 * v575 + 311);
                  v578 = *(&this->m_bWPXS + 192 * v575 + 312);
                  v1051 = *(&this->m_bWPXS + 192 * v575 + 313);
                  v579 = (int *)(&this->m_bWPXS + 624 * v575 + 2500);
                  v579[2] = v577;
                  v580 = (_DWORD *)v579 + 1;
                  v579[1] = v576;
                  v579[3] = v578;
                  v581 = v1051;
                }
                else
                {
                  v979[0] = *(&this->m_bWPXS + 192 * v574 + 302);
                  v979[1] = *(&this->m_bWPXS + 192 * v574 + 303);
                  v979[2] = *(&this->m_bWPXS + 192 * v574 + 304);
                  v979[3] = *(&this->m_bWPXS + 192 * v574 + 305);
                  (((UIWnd *)&this->m_sort[542][1824 * v574]))->UIWnd::sub_445FA0(v979);
                  v582 = *(_DWORD *)&this->remarkbuf[20];
                  v583 = *(&this->m_bWPXS + 192 * v582 + 302);
                  v584 = *(&this->m_bWPXS + 192 * v582 + 303);
                  v585 = *(&this->m_bWPXS + 192 * v582 + 304);
                  v1053 = *(&this->m_bWPXS + 192 * v582 + 305);
                  v579 = (int *)(&this->m_bWPXS + 624 * v582 + 2500);
                  v579[2] = v584;
                  v580 = (_DWORD *)v579 + 1;
                  v579[1] = v583;
                  v579[3] = v585;
                  v581 = v1053;
                }
                v579[4] = v581;
                v586 = (_DWORD *)v579 + 5;
                *v586 = *v580;
                v586[1] = (unsigned long)v580[1];
                v586[2] = (unsigned long)v580[2];
                v586[3] = (unsigned long)v580[3];
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[542][1824
                                                                                   * *(_DWORD *)&this->remarkbuf[20]])((SaleUI_SortData *)(&this->m_sort[542][1824 * *(_DWORD *)&this->remarkbuf[20]]), (int)(1));
              }
              v601 = v946[326];
              v602 = v601 < 0;
              v11 = v601 <= 0;
              v603 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                if ( !v602 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v603 + 5054) = 0;
                  goto LABEL_244;
                }
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[580][1824 * v603])((SaleUI_SortData *)(&this->m_sort[580][1824 * v603]), (int)(1));
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4814) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5058) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5054) = 0;
                v612 = *(_DWORD *)&this->remarkbuf[20];
                v613 = *(&this->m_bWPXS + 192 * v612 + 326);
                v614 = *(&this->m_bWPXS + 192 * v612 + 327);
                v615 = *(&this->m_bWPXS + 192 * v612 + 328);
                v1061 = *(&this->m_bWPXS + 192 * v612 + 329);
                v608 = (int *)(&this->m_bWPXS + 624 * v612 + 2565);
                v608[2] = v614;
                v609 = (_DWORD *)v608 + 1;
                v608[1] = v613;
                v608[3] = v615;
                v610 = v1061;
              }
              else
              {
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[549][1824 * v603 + 3])((SaleUI_SortData *)(&this->m_sort[549][1824 * v603 + 3]), (int)(1));
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4810) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5054) = 1;
                v604 = *(_DWORD *)&this->remarkbuf[20];
                v605 = *(&this->m_bWPXS + 192 * v604 + 310);
                v606 = *(&this->m_bWPXS + 192 * v604 + 311);
                v607 = *(&this->m_bWPXS + 192 * v604 + 312);
                v1059 = *(&this->m_bWPXS + 192 * v604 + 313);
                v608 = (int *)(&this->m_bWPXS + 624 * v604 + 2513);
                v608[2] = v606;
                v609 = (_DWORD *)v608 + 1;
                v608[1] = v605;
                v608[3] = v607;
                v610 = v1059;
              }
              v608[4] = v610;
              v611 = (_DWORD *)v608 + 5;
              *v611 = *v609;
              v611[1] = (unsigned long)v609[1];
              v611[2] = (unsigned long)v609[2];
              v611[3] = (unsigned long)v609[3];
LABEL_244:
              v616 = v946[328];
              v617 = v616 < 0;
              v11 = v616 <= 0;
              v618 = *(_DWORD *)&this->remarkbuf[20];
              if ( !v11 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v618 + 5055) = 1;
                v619 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v619 + 4810) )
                {
                  v985[0] = *(&this->m_bWPXS + 192 * v619 + 302);
                  v985[1] = *(&this->m_bWPXS + 192 * v619 + 303);
                  v985[2] = *(&this->m_bWPXS + 192 * v619 + 304);
                  v985[3] = *(&this->m_bWPXS + 192 * v619 + 305);
                  (((UIWnd *)&this->m_sort[557][1824 * v619 + 1]))->UIWnd::sub_445FA0(v985);
                  v620 = *(_DWORD *)&this->remarkbuf[20];
                  v621 = *(&this->m_bWPXS + 192 * v620 + 302);
                  v622 = *(&this->m_bWPXS + 192 * v620 + 303);
                  v623 = *(&this->m_bWPXS + 192 * v620 + 304);
                  v1063 = *(&this->m_bWPXS + 192 * v620 + 305);
                  v624 = (int *)(&this->m_bWPXS + 624 * v620 + 2526);
                  v624[2] = v622;
                  v625 = (_DWORD *)v624 + 1;
                  v624[1] = v621;
                  v624[3] = v623;
                  v626 = v1063;
                }
                else
                {
                  v987[0] = *(&this->m_bWPXS + 192 * v619 + 314);
                  v987[1] = *(&this->m_bWPXS + 192 * v619 + 315);
                  v987[2] = *(&this->m_bWPXS + 192 * v619 + 316);
                  v987[3] = *(&this->m_bWPXS + 192 * v619 + 317);
                  (((UIWnd *)&this->m_sort[557][1824 * v619 + 1]))->UIWnd::sub_445FA0(v987);
                  v627 = *(_DWORD *)&this->remarkbuf[20];
                  v628 = *(&this->m_bWPXS + 192 * v627 + 314);
                  v629 = *(&this->m_bWPXS + 192 * v627 + 315);
                  v630 = *(&this->m_bWPXS + 192 * v627 + 316);
                  v1065 = *(&this->m_bWPXS + 192 * v627 + 317);
                  v624 = (int *)(&this->m_bWPXS + 624 * v627 + 2526);
                  v624[2] = v629;
                  v625 = (_DWORD *)v624 + 1;
                  v624[1] = v628;
                  v624[3] = v630;
                  v626 = v1065;
                }
                v624[4] = v626;
                v631 = (_DWORD *)v624 + 5;
                *v631 = *v625;
                v631[1] = (unsigned long)v625[1];
                v631[2] = (unsigned long)v625[2];
                v631[3] = (unsigned long)v625[3];
                (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[557][1824
                                                                                   * *(_DWORD *)&this->remarkbuf[20]
                                                                                   + 1])((SaleUI_SortData *)(&this->m_sort[557][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]), (int)(1));
                goto LABEL_285;
              }
              v632 = 3 * v618;
              if ( !v617 )
              {
                *((_BYTE *)&this->m_bWPXS + 16 * v632 + 5055) = 0;
                goto LABEL_285;
              }
              *((_BYTE *)&this->m_bWPXS + 16 * v632 + 5059) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5055) = 0;
              v633 = *(_DWORD *)&this->remarkbuf[20];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v633 + 4814) )
              {
                v989[0] = *(&this->m_bWPXS + 192 * v633 + 318);
                v989[1] = *(&this->m_bWPXS + 192 * v633 + 319);
                v989[2] = *(&this->m_bWPXS + 192 * v633 + 320);
                v989[3] = *(&this->m_bWPXS + 192 * v633 + 321);
                (((UIWnd *)&this->m_sort[587][1824 * v633 + 3]))->UIWnd::sub_445FA0(v989);
                v634 = *(_DWORD *)&this->remarkbuf[20];
                v635 = *(&this->m_bWPXS + 192 * v634 + 318);
                v636 = *(&this->m_bWPXS + 192 * v634 + 319);
                v637 = *(&this->m_bWPXS + 192 * v634 + 320);
                v1067 = *(&this->m_bWPXS + 192 * v634 + 321);
                v638 = (int *)(&this->m_bWPXS + 624 * v634 + 2578);
                v638[2] = v636;
                v639 = (_DWORD *)v638 + 1;
                v638[1] = v635;
                v638[3] = v637;
                v640 = v1067;
              }
              else
              {
                v991[0] = *(&this->m_bWPXS + 192 * v633 + 330);
                v991[1] = *(&this->m_bWPXS + 192 * v633 + 331);
                v991[2] = *(&this->m_bWPXS + 192 * v633 + 332);
                v991[3] = *(&this->m_bWPXS + 192 * v633 + 333);
                (((UIWnd *)&this->m_sort[587][1824 * v633 + 3]))->UIWnd::sub_445FA0(v991);
                v641 = *(_DWORD *)&this->remarkbuf[20];
                v642 = *(&this->m_bWPXS + 192 * v641 + 330);
                v643 = *(&this->m_bWPXS + 192 * v641 + 331);
                v644 = *(&this->m_bWPXS + 192 * v641 + 332);
                v1069 = *(&this->m_bWPXS + 192 * v641 + 333);
                v638 = (int *)(&this->m_bWPXS + 624 * v641 + 2578);
                v638[2] = v643;
                v639 = (_DWORD *)v638 + 1;
                v638[1] = v642;
                v638[3] = v644;
                v640 = v1069;
              }
LABEL_253:
              v638[4] = v640;
              v645 = (_DWORD *)v638 + 5;
              *v645 = *v639;
              v645[1] = (unsigned long)v639[1];
              v645[2] = (unsigned long)v639[2];
              v645[3] = (unsigned long)v639[3];
              (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[587][1824
                                                                                 * *(_DWORD *)&this->remarkbuf[20]
                                                                                 + 3])((SaleUI_SortData *)(&this->m_sort[587][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]), (int)(1));
              goto LABEL_285;
            }
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[564][1824 * v558 + 4])((SaleUI_SortData *)(&this->m_sort[564][1824 * v558 + 4]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4812) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5056) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5052) = 0;
            v567 = *(_DWORD *)&this->remarkbuf[20];
            v568 = *(&this->m_bWPXS + 192 * v567 + 318);
            v569 = *(&this->m_bWPXS + 192 * v567 + 319);
            v570 = *(&this->m_bWPXS + 192 * v567 + 320);
            v1049 = *(&this->m_bWPXS + 192 * v567 + 321);
            v563 = (int *)(&this->m_bWPXS + 624 * v567 + 2539);
            v563[2] = v569;
            v564 = (_DWORD *)v563 + 1;
            v563[1] = v568;
            v563[3] = v570;
            v565 = v1049;
          }
          else
          {
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[534][1824 * v558 + 2])((SaleUI_SortData *)(&this->m_sort[534][1824 * v558 + 2]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4808) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5052) = 1;
            v559 = *(_DWORD *)&this->remarkbuf[20];
            v560 = *(&this->m_bWPXS + 192 * v559 + 302);
            v561 = *(&this->m_bWPXS + 192 * v559 + 303);
            v562 = *(&this->m_bWPXS + 192 * v559 + 304);
            v1047 = *(&this->m_bWPXS + 192 * v559 + 305);
            v563 = (int *)(&this->m_bWPXS + 624 * v559 + 2487);
            v563[2] = v561;
            v564 = (_DWORD *)v563 + 1;
            v563[1] = v560;
            v563[3] = v562;
            v565 = v1047;
          }
          v563[4] = v565;
          v566 = (_DWORD *)v563 + 5;
          *v566 = *v564;
          v566[1] = (unsigned long)v564[1];
          v566[2] = (unsigned long)v564[2];
          v566[3] = (unsigned long)v564[3];
          goto LABEL_227;
        }
        LOBYTE(v950) = *(_BYTE *)(v554 + 3284);
        (((UIPushButton *)&this->m_NotesNull[54 * v553 + 295][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn.tga", v950);
        v646 = *(_DWORD *)&this->remarkbuf[20];
        v647 = v3[325];
        v648 = HIWORD(g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v646 + 3]->rolevalue[3]);
        if ( v647 >= v648 )
        {
          if ( v647 <= v648 )
            goto LABEL_260;
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[534][1824 * v646 + 2])((SaleUI_SortData *)(&this->m_sort[534][1824 * v646 + 2]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4808) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5052) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5056) = 0;
          v656 = *(_DWORD *)&this->remarkbuf[20];
          v657 = *(&this->m_bWPXS + 192 * v656 + 302);
          v658 = *(&this->m_bWPXS + 192 * v656 + 303);
          v659 = *(&this->m_bWPXS + 192 * v656 + 304);
          v1073 = *(&this->m_bWPXS + 192 * v656 + 305);
          v653 = (int *)(&this->m_bWPXS + 624 * v656 + 2487);
          v653[2] = v658;
          v654 = (_DWORD *)v653 + 1;
          v653[1] = v657;
          v653[3] = v659;
          v655 = v1073;
        }
        else
        {
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[564][1824 * v646 + 4])((SaleUI_SortData *)(&this->m_sort[564][1824 * v646 + 4]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4812) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5056) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5052) = 0;
          v649 = *(_DWORD *)&this->remarkbuf[20];
          v650 = *(&this->m_bWPXS + 192 * v649 + 318);
          v651 = *(&this->m_bWPXS + 192 * v649 + 319);
          v652 = *(&this->m_bWPXS + 192 * v649 + 320);
          v1071 = *(&this->m_bWPXS + 192 * v649 + 321);
          v653 = (int *)(&this->m_bWPXS + 624 * v649 + 2539);
          v653[2] = v651;
          v654 = (_DWORD *)v653 + 1;
          v653[1] = v650;
          v653[3] = v652;
          v655 = v1071;
        }
        v653[4] = v655;
        v660 = (_DWORD *)v653 + 5;
        *v660 = *v654;
        v660[1] = (unsigned long)v654[1];
        v660[2] = (unsigned long)v654[2];
        v660[3] = (unsigned long)v654[3];
LABEL_260:
        v661 = *(_DWORD *)&this->remarkbuf[20];
        v662 = v946[327];
        v663 = HIWORD(g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v661 + 3]->rolevalue[4]);
        if ( v662 >= v663 )
        {
          if ( v662 <= v663 )
            goto LABEL_271;
          *((_BYTE *)&this->m_bWPXS + 48 * v661 + 5053) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5057) = 0;
          v678 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v678 + 4808) )
          {
            v997[0] = *(&this->m_bWPXS + 192 * v678 + 310);
            v997[1] = *(&this->m_bWPXS + 192 * v678 + 311);
            v997[2] = *(&this->m_bWPXS + 192 * v678 + 312);
            v997[3] = *(&this->m_bWPXS + 192 * v678 + 313);
            (((UIWnd *)&this->m_sort[542][1824 * v678]))->UIWnd::sub_445FA0(v997);
            v679 = *(_DWORD *)&this->remarkbuf[20];
            v680 = *(&this->m_bWPXS + 192 * v679 + 310);
            v681 = *(&this->m_bWPXS + 192 * v679 + 311);
            v682 = *(&this->m_bWPXS + 192 * v679 + 312);
            v1079 = *(&this->m_bWPXS + 192 * v679 + 313);
            v683 = (int *)(&this->m_bWPXS + 624 * v679 + 2500);
            v683[2] = v681;
            v684 = (_DWORD *)v683 + 1;
            v683[1] = v680;
            v683[3] = v682;
            v685 = v1079;
          }
          else
          {
            v999[0] = *(&this->m_bWPXS + 192 * v678 + 302);
            v999[1] = *(&this->m_bWPXS + 192 * v678 + 303);
            v999[2] = *(&this->m_bWPXS + 192 * v678 + 304);
            v999[3] = *(&this->m_bWPXS + 192 * v678 + 305);
            (((UIWnd *)&this->m_sort[542][1824 * v678]))->UIWnd::sub_445FA0(v999);
            v686 = *(_DWORD *)&this->remarkbuf[20];
            v687 = *(&this->m_bWPXS + 192 * v686 + 302);
            v688 = *(&this->m_bWPXS + 192 * v686 + 303);
            v689 = *(&this->m_bWPXS + 192 * v686 + 304);
            v1081 = *(&this->m_bWPXS + 192 * v686 + 305);
            v683 = (int *)(&this->m_bWPXS + 624 * v686 + 2500);
            v683[2] = v688;
            v684 = (_DWORD *)v683 + 1;
            v683[1] = v687;
            v683[3] = v689;
            v685 = v1081;
          }
          v683[4] = v685;
          v690 = (_DWORD *)v683 + 5;
          *v690 = *v684;
          v690[1] = (unsigned long)v684[1];
          v690[2] = (unsigned long)v684[2];
          v690[3] = (unsigned long)v684[3];
          v677 = (SaleUI_SortData *)&this->m_sort[542][1824 * *(_DWORD *)&this->remarkbuf[20]];
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v661 + 5057) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5053) = 0;
          v664 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v664 + 4812) )
          {
            v993[0] = *(&this->m_bWPXS + 192 * v664 + 326);
            v993[1] = *(&this->m_bWPXS + 192 * v664 + 327);
            v993[2] = *(&this->m_bWPXS + 192 * v664 + 328);
            v993[3] = *(&this->m_bWPXS + 192 * v664 + 329);
            (((UIWnd *)&this->m_sort[572][1824 * v664 + 2]))->UIWnd::sub_445FA0(v993);
            v665 = *(_DWORD *)&this->remarkbuf[20];
            v666 = *(&this->m_bWPXS + 192 * v665 + 326);
            v667 = *(&this->m_bWPXS + 192 * v665 + 327);
            v668 = *(&this->m_bWPXS + 192 * v665 + 328);
            v1075 = *(&this->m_bWPXS + 192 * v665 + 329);
            v669 = (int *)(&this->m_bWPXS + 624 * v665 + 2552);
            v669[2] = v667;
            v670 = (_DWORD *)v669 + 1;
            v669[1] = v666;
            v669[3] = v668;
            v671 = v1075;
          }
          else
          {
            v995[0] = *(&this->m_bWPXS + 192 * v664 + 318);
            v995[1] = *(&this->m_bWPXS + 192 * v664 + 319);
            v995[2] = *(&this->m_bWPXS + 192 * v664 + 320);
            v995[3] = *(&this->m_bWPXS + 192 * v664 + 321);
            (((UIWnd *)&this->m_sort[572][1824 * v664 + 2]))->UIWnd::sub_445FA0(v995);
            v672 = *(_DWORD *)&this->remarkbuf[20];
            v673 = *(&this->m_bWPXS + 192 * v672 + 318);
            v674 = *(&this->m_bWPXS + 192 * v672 + 319);
            v675 = *(&this->m_bWPXS + 192 * v672 + 320);
            v1077 = *(&this->m_bWPXS + 192 * v672 + 321);
            v669 = (int *)(&this->m_bWPXS + 624 * v672 + 2552);
            v669[2] = v674;
            v670 = (_DWORD *)v669 + 1;
            v669[1] = v673;
            v669[3] = v675;
            v671 = v1077;
          }
          v669[4] = v671;
          v676 = (_DWORD *)v669 + 5;
          *v676 = *v670;
          v676[1] = (unsigned long)v670[1];
          v676[2] = (unsigned long)v670[2];
          v676[3] = (unsigned long)v670[3];
          v677 = (SaleUI_SortData *)&this->m_sort[572][1824 * *(_DWORD *)&this->remarkbuf[20] + 2];
        }
        (**(void ( ***)(SaleUI_SortData *, int))v677)((SaleUI_SortData *)(v677), (int)(1));
LABEL_271:
        v691 = *(_DWORD *)&this->remarkbuf[20];
        v692 = v946[326];
        v693 = g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v691 + 3]->rolevalue[4];
        if ( v692 >= v693 )
        {
          if ( v692 <= v693 )
            goto LABEL_276;
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[549][1824 * v691 + 3])((SaleUI_SortData *)(&this->m_sort[549][1824 * v691 + 3]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4810) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5054) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5058) = 0;
          v701 = *(_DWORD *)&this->remarkbuf[20];
          v702 = *(&this->m_bWPXS + 192 * v701 + 310);
          v703 = *(&this->m_bWPXS + 192 * v701 + 311);
          v704 = *(&this->m_bWPXS + 192 * v701 + 312);
          v1085 = *(&this->m_bWPXS + 192 * v701 + 313);
          v698 = (int *)(&this->m_bWPXS + 624 * v701 + 2513);
          v698[2] = v703;
          v699 = (_DWORD *)v698 + 1;
          v698[1] = v702;
          v698[3] = v704;
          v700 = v1085;
        }
        else
        {
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[580][1824 * v691])((SaleUI_SortData *)(&this->m_sort[580][1824 * v691]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4814) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5058) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5054) = 0;
          v694 = *(_DWORD *)&this->remarkbuf[20];
          v695 = *(&this->m_bWPXS + 192 * v694 + 326);
          v696 = *(&this->m_bWPXS + 192 * v694 + 327);
          v697 = *(&this->m_bWPXS + 192 * v694 + 328);
          v1083 = *(&this->m_bWPXS + 192 * v694 + 329);
          v698 = (int *)(&this->m_bWPXS + 624 * v694 + 2565);
          v698[2] = v696;
          v699 = (_DWORD *)v698 + 1;
          v698[1] = v695;
          v698[3] = v697;
          v700 = v1083;
        }
        v698[4] = v700;
        v705 = (_DWORD *)v698 + 5;
        *v705 = *v699;
        v705[1] = (unsigned long)v699[1];
        v705[2] = (unsigned long)v699[2];
        v705[3] = (unsigned long)v699[3];
LABEL_276:
        v706 = *(_DWORD *)&this->remarkbuf[20];
        v707 = v946[328];
        v708 = g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v706 + 3]->rolevalue[5];
        if ( v707 < v708 )
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v706 + 5059) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5055) = 0;
          v709 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v709 + 4814) )
          {
            v1001[0] = *(&this->m_bWPXS + 192 * v709 + 318);
            v1001[1] = *(&this->m_bWPXS + 192 * v709 + 319);
            v1001[2] = *(&this->m_bWPXS + 192 * v709 + 320);
            v1001[3] = *(&this->m_bWPXS + 192 * v709 + 321);
            (((UIWnd *)&this->m_sort[587][1824 * v709 + 3]))->UIWnd::sub_445FA0(v1001);
            v710 = *(_DWORD *)&this->remarkbuf[20];
            v711 = *(&this->m_bWPXS + 192 * v710 + 318);
            v712 = *(&this->m_bWPXS + 192 * v710 + 319);
            v713 = *(&this->m_bWPXS + 192 * v710 + 320);
            v1087 = *(&this->m_bWPXS + 192 * v710 + 321);
            v638 = (int *)(&this->m_bWPXS + 624 * v710 + 2578);
            v638[2] = v712;
            v639 = (_DWORD *)v638 + 1;
            v638[1] = v711;
            v638[3] = v713;
            v640 = v1087;
          }
          else
          {
            v1003[0] = *(&this->m_bWPXS + 192 * v709 + 330);
            v1003[1] = *(&this->m_bWPXS + 192 * v709 + 331);
            v1003[2] = *(&this->m_bWPXS + 192 * v709 + 332);
            v1003[3] = *(&this->m_bWPXS + 192 * v709 + 333);
            (((UIWnd *)&this->m_sort[587][1824 * v709 + 3]))->UIWnd::sub_445FA0(v1003);
            v714 = *(_DWORD *)&this->remarkbuf[20];
            v715 = *(&this->m_bWPXS + 192 * v714 + 330);
            v716 = *(&this->m_bWPXS + 192 * v714 + 331);
            v717 = *(&this->m_bWPXS + 192 * v714 + 332);
            v1089 = *(&this->m_bWPXS + 192 * v714 + 333);
            v638 = (int *)(&this->m_bWPXS + 624 * v714 + 2578);
            v638[2] = v716;
            v639 = (_DWORD *)v638 + 1;
            v638[1] = v715;
            v638[3] = v717;
            v640 = v1089;
          }
          goto LABEL_253;
        }
        if ( v707 > v708 )
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v706 + 5055) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5059) = 0;
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[557][1824 * *(_DWORD *)&this->remarkbuf[20]
                                                                             + 1])((SaleUI_SortData *)(&this->m_sort[557][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]), (int)(1));
          v718 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v718 + 4810) )
          {
            v1005[0] = *(&this->m_bWPXS + 192 * v718 + 302);
            v1005[1] = *(&this->m_bWPXS + 192 * v718 + 303);
            v1005[2] = *(&this->m_bWPXS + 192 * v718 + 304);
            v1005[3] = *(&this->m_bWPXS + 192 * v718 + 305);
            (((UIWnd *)&this->m_sort[557][1824 * v718 + 1]))->UIWnd::sub_445FA0(v1005);
            v719 = *(_DWORD *)&this->remarkbuf[20];
            v720 = *(&this->m_bWPXS + 192 * v719 + 302);
            v721 = *(&this->m_bWPXS + 192 * v719 + 303);
            v722 = *(&this->m_bWPXS + 192 * v719 + 304);
            v1091 = *(&this->m_bWPXS + 192 * v719 + 305);
            v723 = (int *)(&this->m_bWPXS + 624 * v719 + 2526);
            v723[2] = v721;
            v724 = (_DWORD *)v723 + 1;
            v723[1] = v720;
            v723[3] = v722;
            v725 = v1091;
          }
          else
          {
            v1007[0] = *(&this->m_bWPXS + 192 * v718 + 314);
            v1007[1] = *(&this->m_bWPXS + 192 * v718 + 315);
            v1007[2] = *(&this->m_bWPXS + 192 * v718 + 316);
            v1007[3] = *(&this->m_bWPXS + 192 * v718 + 317);
            (((UIWnd *)&this->m_sort[557][1824 * v718 + 1]))->UIWnd::sub_445FA0(v1007);
            v726 = *(_DWORD *)&this->remarkbuf[20];
            v727 = *(&this->m_bWPXS + 192 * v726 + 314);
            v728 = *(&this->m_bWPXS + 192 * v726 + 315);
            v729 = *(&this->m_bWPXS + 192 * v726 + 316);
            v1093 = *(&this->m_bWPXS + 192 * v726 + 317);
            v723 = (int *)(&this->m_bWPXS + 624 * v726 + 2526);
            v723[2] = v728;
            v724 = (_DWORD *)v723 + 1;
            v723[1] = v727;
            v723[3] = v729;
            v725 = v1093;
          }
          v723[4] = v725;
          v730 = (_DWORD *)v723 + 5;
          *v730 = *v724;
          v730[1] = (unsigned long)v724[1];
          v730[2] = (unsigned long)v724[2];
          v730[3] = (unsigned long)v724[3];
        }
LABEL_285:
        v731 = *(_DWORD *)&this->remarkbuf[20];
        v732 = *(&this->AttackNum + 289);
        if ( !g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v731 + 6] )
        {
          LOBYTE(v952) = *(_BYTE *)(v732 + 3284);
          (((UIPushButton *)&this->m_IsEquip[216 * v731 + 95][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn.tga", v952);
          for ( n = 0; n < 8; ++n )
            (*(void ( **)(int *, _DWORD))this->m_ListSelNum[118][1824
                                                                                    * *(_DWORD *)&this->remarkbuf[20]
                                                                                    + 4
                                                                                    + 38 * n])(
              &this->m_ListSelNum[118][1824 * *(_DWORD *)&this->remarkbuf[20] + 4 + 38 * n],
              0);
          v734 = v946[325];
          v735 = v734 < 0;
          v11 = v734 <= 0;
          v736 = *(_DWORD *)&this->remarkbuf[20];
          if ( v11 )
          {
            if ( !v735 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v736 + 5076) = 0;
LABEL_294:
              v749 = v946[327];
              v750 = v749 < 0;
              v11 = v749 <= 0;
              v751 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                v765 = 3 * v751;
                if ( v750 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v765 + 5081) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5077) = 0;
                  v766 = *(_DWORD *)&this->remarkbuf[20];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v766 + 4836) )
                  {
                    v1013[0] = *(&this->m_bWPXS + 192 * v766 + 422);
                    v1013[1] = *(&this->m_bWPXS + 192 * v766 + 423);
                    v1013[2] = *(&this->m_bWPXS + 192 * v766 + 424);
                    v1013[3] = *(&this->m_bWPXS + 192 * v766 + 425);
                    (((UIWnd *)&this->m_ListSelNum[156][1824 * v766 + 4]))->UIWnd::sub_445FA0(v1013);
                    v767 = *(_DWORD *)&this->remarkbuf[20];
                    v768 = *(&this->m_bWPXS + 192 * v767 + 422);
                    v769 = *(&this->m_bWPXS + 192 * v767 + 423);
                    v770 = *(&this->m_bWPXS + 192 * v767 + 424);
                    v1103 = *(&this->m_bWPXS + 192 * v767 + 425);
                    v771 = (int *)(&this->m_bWPXS + 624 * v767 + 2864);
                    v771[2] = v769;
                    v772 = (_DWORD *)v771 + 1;
                    v771[1] = v768;
                    v771[3] = v770;
                    v773 = v1103;
                  }
                  else
                  {
                    v1015[0] = *(&this->m_bWPXS + 192 * v766 + 414);
                    v1015[1] = *(&this->m_bWPXS + 192 * v766 + 415);
                    v1015[2] = *(&this->m_bWPXS + 192 * v766 + 416);
                    v1015[3] = *(&this->m_bWPXS + 192 * v766 + 417);
                    (((UIWnd *)&this->m_ListSelNum[156][1824 * v766 + 4]))->UIWnd::sub_445FA0(v1015);
                    v774 = *(_DWORD *)&this->remarkbuf[20];
                    v775 = *(&this->m_bWPXS + 192 * v774 + 414);
                    v776 = *(&this->m_bWPXS + 192 * v774 + 415);
                    v777 = *(&this->m_bWPXS + 192 * v774 + 416);
                    v1105 = *(&this->m_bWPXS + 192 * v774 + 417);
                    v771 = (int *)(&this->m_bWPXS + 624 * v774 + 2864);
                    v771[2] = v776;
                    v772 = (_DWORD *)v771 + 1;
                    v771[1] = v775;
                    v771[3] = v777;
                    v773 = v1105;
                  }
                  v771[4] = v773;
                  v778 = (_DWORD *)v771 + 5;
                  *v778 = *v772;
                  v778[1] = (unsigned long)v772[1];
                  v778[2] = (unsigned long)v772[2];
                  v778[3] = (unsigned long)v772[3];
                  (*(void ( **)(int *, int))this->m_ListSelNum[156][1824
                                                                                       * *(_DWORD *)&this->remarkbuf[20]
                                                                                       + 4])(
                    &this->m_ListSelNum[156][1824 * *(_DWORD *)&this->remarkbuf[20] + 4],
                    1);
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v765 + 5077) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v751 + 5077) = 1;
                v752 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v752 + 4832) )
                {
                  v1009[0] = *(&this->m_bWPXS + 192 * v752 + 406);
                  v1009[1] = *(&this->m_bWPXS + 192 * v752 + 407);
                  v1009[2] = *(&this->m_bWPXS + 192 * v752 + 408);
                  v1009[3] = *(&this->m_bWPXS + 192 * v752 + 409);
                  (((UIWnd *)&this->m_ListSelNum[126][1824 * v752 + 2]))->UIWnd::sub_445FA0(v1009);
                  v753 = *(_DWORD *)&this->remarkbuf[20];
                  v754 = *(&this->m_bWPXS + 192 * v753 + 406);
                  v755 = *(&this->m_bWPXS + 192 * v753 + 407);
                  v756 = *(&this->m_bWPXS + 192 * v753 + 408);
                  v1099 = *(&this->m_bWPXS + 192 * v753 + 409);
                  v757 = (int *)(&this->m_bWPXS + 624 * v753 + 2812);
                  v757[2] = v755;
                  v758 = (_DWORD *)v757 + 1;
                  v757[1] = v754;
                  v757[3] = v756;
                  v759 = v1099;
                }
                else
                {
                  v1011[0] = *(&this->m_bWPXS + 192 * v752 + 398);
                  v1011[1] = *(&this->m_bWPXS + 192 * v752 + 399);
                  v1011[2] = *(&this->m_bWPXS + 192 * v752 + 400);
                  v1011[3] = *(&this->m_bWPXS + 192 * v752 + 401);
                  (((UIWnd *)&this->m_ListSelNum[126][1824 * v752 + 2]))->UIWnd::sub_445FA0(v1011);
                  v760 = *(_DWORD *)&this->remarkbuf[20];
                  v761 = *(&this->m_bWPXS + 192 * v760 + 398);
                  v762 = *(&this->m_bWPXS + 192 * v760 + 399);
                  v763 = *(&this->m_bWPXS + 192 * v760 + 400);
                  v1101 = *(&this->m_bWPXS + 192 * v760 + 401);
                  v757 = (int *)(&this->m_bWPXS + 624 * v760 + 2812);
                  v757[2] = v762;
                  v758 = (_DWORD *)v757 + 1;
                  v757[1] = v761;
                  v757[3] = v763;
                  v759 = v1101;
                }
                v757[4] = v759;
                v764 = (_DWORD *)v757 + 5;
                *v764 = *v758;
                v764[1] = (unsigned long)v758[1];
                v764[2] = (unsigned long)v758[2];
                v764[3] = (unsigned long)v758[3];
                (*(void ( **)(int *, int))this->m_ListSelNum[126][1824
                                                                                     * *(_DWORD *)&this->remarkbuf[20]
                                                                                     + 2])(
                  &this->m_ListSelNum[126][1824 * *(_DWORD *)&this->remarkbuf[20] + 2],
                  1);
              }
              v779 = v946[326];
              v780 = v779 < 0;
              v11 = v779 <= 0;
              v781 = *(_DWORD *)&this->remarkbuf[20];
              if ( v11 )
              {
                if ( !v780 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v781 + 5078) = 0;
                  goto LABEL_311;
                }
                (*(void ( **)(int *, int))this->m_ListSelNum[164][1824 * v781 + 2])(
                  &this->m_ListSelNum[164][1824 * v781 + 2],
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4838) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5082) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5078) = 0;
                v790 = *(_DWORD *)&this->remarkbuf[20];
                v791 = *(&this->m_bWPXS + 192 * v790 + 422);
                v792 = *(&this->m_bWPXS + 192 * v790 + 423);
                v793 = *(&this->m_bWPXS + 192 * v790 + 424);
                v1109 = *(&this->m_bWPXS + 192 * v790 + 425);
                v786 = (int *)(&this->m_bWPXS + 624 * v790 + 2877);
                v786[2] = v792;
                v787 = (_DWORD *)v786 + 1;
                v786[1] = v791;
                v786[3] = v793;
                v788 = v1109;
              }
              else
              {
                (*(void ( **)(int *, int))this->m_ListSelNum[134][1824 * v781])(
                  &this->m_ListSelNum[134][1824 * v781],
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4834) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5078) = 1;
                v782 = *(_DWORD *)&this->remarkbuf[20];
                v783 = *(&this->m_bWPXS + 192 * v782 + 406);
                v784 = *(&this->m_bWPXS + 192 * v782 + 407);
                v785 = *(&this->m_bWPXS + 192 * v782 + 408);
                v1107 = *(&this->m_bWPXS + 192 * v782 + 409);
                v786 = (int *)(&this->m_bWPXS + 624 * v782 + 2825);
                v786[2] = v784;
                v787 = (_DWORD *)v786 + 1;
                v786[1] = v783;
                v786[3] = v785;
                v788 = v1107;
              }
              v786[4] = v788;
              v789 = (_DWORD *)v786 + 5;
              *v789 = *v787;
              v789[1] = (unsigned long)v787[1];
              v789[2] = (unsigned long)v787[2];
              v789[3] = (unsigned long)v787[3];
LABEL_311:
              v3 = (_WORD *)v946;
              v794 = v946[328];
              if ( v794 > 0 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5079) = 1;
                v795 = *(_DWORD *)&this->remarkbuf[20];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v795 + 4834) )
                {
                  v1017[0] = *(&this->m_bWPXS + 192 * v795 + 398);
                  v1017[1] = *(&this->m_bWPXS + 192 * v795 + 399);
                  v1017[2] = *(&this->m_bWPXS + 192 * v795 + 400);
                  v1017[3] = *(&this->m_bWPXS + 192 * v795 + 401);
                  (((UIWnd *)&this->m_ListSelNum[141][1824 * v795 + 3]))->UIWnd::sub_445FA0(v1017);
                  v796 = *(_DWORD *)&this->remarkbuf[20];
                  v797 = *(&this->m_bWPXS + 192 * v796 + 398);
                  v798 = *(&this->m_bWPXS + 192 * v796 + 399);
                  v799 = *(&this->m_bWPXS + 192 * v796 + 400);
                  v1111 = *(&this->m_bWPXS + 192 * v796 + 401);
                  v800 = (int *)(&this->m_bWPXS + 624 * v796 + 2838);
                  v800[2] = v798;
                  v801 = (_DWORD *)v800 + 1;
                  v800[1] = v797;
                  v800[3] = v799;
                  v802 = v1111;
                }
                else
                {
                  v1019[0] = *(&this->m_bWPXS + 192 * v795 + 410);
                  v1019[1] = *(&this->m_bWPXS + 192 * v795 + 411);
                  v1019[2] = *(&this->m_bWPXS + 192 * v795 + 412);
                  v1019[3] = *(&this->m_bWPXS + 192 * v795 + 413);
                  (((UIWnd *)&this->m_ListSelNum[141][1824 * v795 + 3]))->UIWnd::sub_445FA0(v1019);
                  v803 = *(_DWORD *)&this->remarkbuf[20];
                  v804 = *(&this->m_bWPXS + 192 * v803 + 410);
                  v805 = *(&this->m_bWPXS + 192 * v803 + 411);
                  v806 = *(&this->m_bWPXS + 192 * v803 + 412);
                  v1113 = *(&this->m_bWPXS + 192 * v803 + 413);
                  v800 = (int *)(&this->m_bWPXS + 624 * v803 + 2838);
                  v800[2] = v805;
                  v801 = (_DWORD *)v800 + 1;
                  v800[1] = v804;
                  v800[3] = v806;
                  v802 = v1113;
                }
                v800[4] = v802;
                v807 = (_DWORD *)v800 + 5;
                *v807 = *v801;
                v807[1] = (unsigned long)v801[1];
                v807[2] = (unsigned long)v801[2];
                v807[3] = (unsigned long)v801[3];
                (*(void ( **)(int *, int))this->m_ListSelNum[141][1824
                                                                                     * *(_DWORD *)&this->remarkbuf[20]
                                                                                     + 3])(
                  &this->m_ListSelNum[141][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
                  1);
                v3 = (_WORD *)v946;
                goto LABEL_353;
              }
              if ( v794 >= 0 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5079) = 0;
                goto LABEL_353;
              }
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5083) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5079) = 0;
              v808 = *(_DWORD *)&this->remarkbuf[20];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v808 + 4838) )
              {
                v1021[0] = *(&this->m_bWPXS + 192 * v808 + 414);
                v1021[1] = *(&this->m_bWPXS + 192 * v808 + 415);
                v1021[2] = *(&this->m_bWPXS + 192 * v808 + 416);
                v1021[3] = *(&this->m_bWPXS + 192 * v808 + 417);
                (((UIWnd *)&this->m_ListSelNum[172][1824 * v808]))->UIWnd::sub_445FA0(v1021);
                v809 = *(_DWORD *)&this->remarkbuf[20];
                v810 = *(&this->m_bWPXS + 192 * v809 + 414);
                v811 = *(&this->m_bWPXS + 192 * v809 + 415);
                v812 = *(&this->m_bWPXS + 192 * v809 + 416);
                v1115 = *(&this->m_bWPXS + 192 * v809 + 417);
                v813 = (int *)(&this->m_bWPXS + 624 * v809 + 2890);
                v813[2] = v811;
                v814 = (_DWORD *)v813 + 1;
                v813[1] = v810;
                v813[3] = v812;
                v815 = v1115;
              }
              else
              {
                v1023[0] = *(&this->m_bWPXS + 192 * v808 + 426);
                v1023[1] = *(&this->m_bWPXS + 192 * v808 + 427);
                v1023[2] = *(&this->m_bWPXS + 192 * v808 + 428);
                v1023[3] = *(&this->m_bWPXS + 192 * v808 + 429);
                (((UIWnd *)&this->m_ListSelNum[172][1824 * v808]))->UIWnd::sub_445FA0(v1023);
                v816 = *(_DWORD *)&this->remarkbuf[20];
                v817 = *(&this->m_bWPXS + 192 * v816 + 426);
                v818 = *(&this->m_bWPXS + 192 * v816 + 427);
                v819 = *(&this->m_bWPXS + 192 * v816 + 428);
                v1117 = *(&this->m_bWPXS + 192 * v816 + 429);
                v813 = (int *)(&this->m_bWPXS + 624 * v816 + 2890);
                v813[2] = v818;
                v814 = (_DWORD *)v813 + 1;
                v813[1] = v817;
                v813[3] = v819;
                v815 = v1117;
              }
              goto LABEL_320;
            }
            (*(void ( **)(int *, int))this->m_ListSelNum[149][1824 * v736 + 1])(
              &this->m_ListSelNum[149][1824 * v736 + 1],
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4836) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5080) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5076) = 0;
            v745 = *(_DWORD *)&this->remarkbuf[20];
            v746 = *(&this->m_bWPXS + 192 * v745 + 414);
            v747 = *(&this->m_bWPXS + 192 * v745 + 415);
            v748 = *(&this->m_bWPXS + 192 * v745 + 416);
            v1097 = *(&this->m_bWPXS + 192 * v745 + 417);
            v741 = (int *)(&this->m_bWPXS + 624 * v745 + 2851);
            v741[2] = v747;
            v742 = (_DWORD *)v741 + 1;
            v741[1] = v746;
            v741[3] = v748;
            v743 = v1097;
          }
          else
          {
            (*(void ( **)(int *, int))this->m_ListSelNum[118][1824 * v736 + 4])(
              &this->m_ListSelNum[118][1824 * v736 + 4],
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4832) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5076) = 1;
            v737 = *(_DWORD *)&this->remarkbuf[20];
            v738 = *(&this->m_bWPXS + 192 * v737 + 398);
            v739 = *(&this->m_bWPXS + 192 * v737 + 399);
            v740 = *(&this->m_bWPXS + 192 * v737 + 400);
            v1095 = *(&this->m_bWPXS + 192 * v737 + 401);
            v741 = (int *)(&this->m_bWPXS + 624 * v737 + 2799);
            v741[2] = v739;
            v742 = (_DWORD *)v741 + 1;
            v741[1] = v738;
            v741[3] = v740;
            v743 = v1095;
          }
          v741[4] = v743;
          v744 = (_DWORD *)v741 + 5;
          *v744 = *v742;
          v744[1] = (unsigned long)v742[1];
          v744[2] = (unsigned long)v742[2];
          v744[3] = (unsigned long)v742[3];
          goto LABEL_294;
        }
        LOBYTE(v954) = *(_BYTE *)(v732 + 3284);
        (((UIPushButton *)&this->m_IsEquip[216 * v731 + 95][1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn.tga", v954);
        v821 = *(_DWORD *)&this->remarkbuf[20];
        v822 = v946[325];
        v823 = HIWORD(g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v821 + 6]->rolevalue[3]);
        if ( v822 >= v823 )
        {
          if ( v822 <= v823 )
            goto LABEL_328;
          (*(void ( **)(int *, int))this->m_ListSelNum[118][1824 * v821 + 4])(
            &this->m_ListSelNum[118][1824 * v821 + 4],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4832) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5076) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5080) = 0;
          v831 = *(_DWORD *)&this->remarkbuf[20];
          v832 = *(&this->m_bWPXS + 192 * v831 + 398);
          v833 = *(&this->m_bWPXS + 192 * v831 + 399);
          v834 = *(&this->m_bWPXS + 192 * v831 + 400);
          v1121 = *(&this->m_bWPXS + 192 * v831 + 401);
          v828 = (int *)(&this->m_bWPXS + 624 * v831 + 2799);
          v828[2] = v833;
          v829 = (_DWORD *)v828 + 1;
          v828[1] = v832;
          v828[3] = v834;
          v830 = v1121;
        }
        else
        {
          (*(void ( **)(int *, int))this->m_ListSelNum[149][1824 * v821 + 1])(
            &this->m_ListSelNum[149][1824 * v821 + 1],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4836) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5080) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5076) = 0;
          v824 = *(_DWORD *)&this->remarkbuf[20];
          v825 = *(&this->m_bWPXS + 192 * v824 + 414);
          v826 = *(&this->m_bWPXS + 192 * v824 + 415);
          v827 = *(&this->m_bWPXS + 192 * v824 + 416);
          v1119 = *(&this->m_bWPXS + 192 * v824 + 417);
          v828 = (int *)(&this->m_bWPXS + 624 * v824 + 2851);
          v828[2] = v826;
          v829 = (_DWORD *)v828 + 1;
          v828[1] = v825;
          v828[3] = v827;
          v830 = v1119;
        }
        v828[4] = v830;
        v835 = (_DWORD *)v828 + 5;
        *v835 = *v829;
        v835[1] = (unsigned long)v829[1];
        v835[2] = (unsigned long)v829[2];
        v835[3] = (unsigned long)v829[3];
LABEL_328:
        v836 = *(_DWORD *)&this->remarkbuf[20];
        v837 = v946[327];
        v838 = HIWORD(g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v836 + 6]->rolevalue[4]);
        if ( v837 >= v838 )
        {
          if ( v837 <= v838 )
            goto LABEL_339;
          *((_BYTE *)&this->m_bWPXS + 48 * v836 + 5077) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5081) = 0;
          v853 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v853 + 4832) )
          {
            v1029[0] = *(&this->m_bWPXS + 192 * v853 + 406);
            v1029[1] = *(&this->m_bWPXS + 192 * v853 + 407);
            v1029[2] = *(&this->m_bWPXS + 192 * v853 + 408);
            v1029[3] = *(&this->m_bWPXS + 192 * v853 + 409);
            (((UIWnd *)&this->m_ListSelNum[126][1824 * v853 + 2]))->UIWnd::sub_445FA0(v1029);
            v854 = *(_DWORD *)&this->remarkbuf[20];
            v855 = *(&this->m_bWPXS + 192 * v854 + 406);
            v856 = *(&this->m_bWPXS + 192 * v854 + 407);
            v857 = *(&this->m_bWPXS + 192 * v854 + 408);
            v1127 = *(&this->m_bWPXS + 192 * v854 + 409);
            v858 = (int *)(&this->m_bWPXS + 624 * v854 + 2812);
            v858[2] = v856;
            v859 = (_DWORD *)v858 + 1;
            v858[1] = v855;
            v858[3] = v857;
            v860 = v1127;
          }
          else
          {
            v1031[0] = *(&this->m_bWPXS + 192 * v853 + 398);
            v1031[1] = *(&this->m_bWPXS + 192 * v853 + 399);
            v1031[2] = *(&this->m_bWPXS + 192 * v853 + 400);
            v1031[3] = *(&this->m_bWPXS + 192 * v853 + 401);
            (((UIWnd *)&this->m_ListSelNum[126][1824 * v853 + 2]))->UIWnd::sub_445FA0(v1031);
            v861 = *(_DWORD *)&this->remarkbuf[20];
            v862 = *(&this->m_bWPXS + 192 * v861 + 398);
            v863 = *(&this->m_bWPXS + 192 * v861 + 399);
            v864 = *(&this->m_bWPXS + 192 * v861 + 400);
            v1129 = *(&this->m_bWPXS + 192 * v861 + 401);
            v858 = (int *)(&this->m_bWPXS + 624 * v861 + 2812);
            v858[2] = v863;
            v859 = (_DWORD *)v858 + 1;
            v858[1] = v862;
            v858[3] = v864;
            v860 = v1129;
          }
          v858[4] = v860;
          v865 = (_DWORD *)v858 + 5;
          *v865 = *v859;
          v865[1] = (unsigned long)v859[1];
          v865[2] = (unsigned long)v859[2];
          v865[3] = (unsigned long)v859[3];
          v852 = (int *)&this->m_ListSelNum[126][1824 * *(_DWORD *)&this->remarkbuf[20] + 2];
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v836 + 5081) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5077) = 0;
          v839 = *(_DWORD *)&this->remarkbuf[20];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v839 + 4836) )
          {
            v1025[0] = *(&this->m_bWPXS + 192 * v839 + 422);
            v1025[1] = *(&this->m_bWPXS + 192 * v839 + 423);
            v1025[2] = *(&this->m_bWPXS + 192 * v839 + 424);
            v1025[3] = *(&this->m_bWPXS + 192 * v839 + 425);
            (((UIWnd *)&this->m_ListSelNum[156][1824 * v839 + 4]))->UIWnd::sub_445FA0(v1025);
            v840 = *(_DWORD *)&this->remarkbuf[20];
            v841 = *(&this->m_bWPXS + 192 * v840 + 422);
            v842 = *(&this->m_bWPXS + 192 * v840 + 423);
            v843 = *(&this->m_bWPXS + 192 * v840 + 424);
            v1123 = *(&this->m_bWPXS + 192 * v840 + 425);
            v844 = (int *)(&this->m_bWPXS + 624 * v840 + 2864);
            v844[2] = v842;
            v845 = (_DWORD *)v844 + 1;
            v844[1] = v841;
            v844[3] = v843;
            v846 = v1123;
          }
          else
          {
            v1027[0] = *(&this->m_bWPXS + 192 * v839 + 414);
            v1027[1] = *(&this->m_bWPXS + 192 * v839 + 415);
            v1027[2] = *(&this->m_bWPXS + 192 * v839 + 416);
            v1027[3] = *(&this->m_bWPXS + 192 * v839 + 417);
            (((UIWnd *)&this->m_ListSelNum[156][1824 * v839 + 4]))->UIWnd::sub_445FA0(v1027);
            v847 = *(_DWORD *)&this->remarkbuf[20];
            v848 = *(&this->m_bWPXS + 192 * v847 + 414);
            v849 = *(&this->m_bWPXS + 192 * v847 + 415);
            v850 = *(&this->m_bWPXS + 192 * v847 + 416);
            v1125 = *(&this->m_bWPXS + 192 * v847 + 417);
            v844 = (int *)(&this->m_bWPXS + 624 * v847 + 2864);
            v844[2] = v849;
            v845 = (_DWORD *)v844 + 1;
            v844[1] = v848;
            v844[3] = v850;
            v846 = v1125;
          }
          v844[4] = v846;
          v851 = (_DWORD *)v844 + 5;
          *v851 = *v845;
          v851[1] = (unsigned long)v845[1];
          v851[2] = (unsigned long)v845[2];
          v851[3] = (unsigned long)v845[3];
          v852 = (int *)&this->m_ListSelNum[156][1824 * *(_DWORD *)&this->remarkbuf[20] + 4];
        }
        (*(void ( **)(int *, int))*v852)(v852, 1);
LABEL_339:
        v866 = *(_DWORD *)&this->remarkbuf[20];
        v867 = v946[326];
        v868 = g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v866 + 6]->rolevalue[4];
        if ( v867 < v868 )
        {
          (*(void ( **)(int *, int))this->m_ListSelNum[164][1824 * v866 + 2])(
            &this->m_ListSelNum[164][1824 * v866 + 2],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4838) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5082) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5078) = 0;
          v869 = *(_DWORD *)&this->remarkbuf[20];
          v870 = *(&this->m_bWPXS + 192 * v869 + 422);
          v871 = *(&this->m_bWPXS + 192 * v869 + 423);
          v872 = *(&this->m_bWPXS + 192 * v869 + 424);
          v1131 = *(&this->m_bWPXS + 192 * v869 + 425);
          v873 = (int *)(&this->m_bWPXS + 624 * v869 + 2877);
          v873[2] = v871;
          v874 = (_DWORD *)v873 + 1;
          v873[1] = v870;
          v873[3] = v872;
          v875 = v1131;
LABEL_343:
          v873[4] = v875;
          v880 = (_DWORD *)v873 + 5;
          *v880 = *v874;
          v880[1] = (unsigned long)v874[1];
          v880[2] = (unsigned long)v874[2];
          v880[3] = (unsigned long)v874[3];
          goto LABEL_344;
        }
        if ( v867 > v868 )
        {
          (*(void ( **)(int *, int))this->m_ListSelNum[134][1824 * v866])(
            &this->m_ListSelNum[134][1824 * v866],
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4834) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5078) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5082) = 0;
          v876 = *(_DWORD *)&this->remarkbuf[20];
          v877 = *(&this->m_bWPXS + 192 * v876 + 406);
          v878 = *(&this->m_bWPXS + 192 * v876 + 407);
          v879 = *(&this->m_bWPXS + 192 * v876 + 408);
          v1133 = *(&this->m_bWPXS + 192 * v876 + 409);
          v873 = (int *)(&this->m_bWPXS + 624 * v876 + 2825);
          v873[2] = v878;
          v874 = (_DWORD *)v873 + 1;
          v873[1] = v877;
          v873[3] = v879;
          v875 = v1133;
          goto LABEL_343;
        }
LABEL_344:
        v881 = *(_DWORD *)&this->remarkbuf[20];
        v3 = (_WORD *)v946;
        v882 = v946[328];
        v883 = g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v881 + 6]->rolevalue[5];
        if ( v882 >= v883 )
        {
          if ( v882 > v883 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * v881 + 5079) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5083) = 0;
            (*(void ( **)(int *, int))this->m_ListSelNum[141][1824
                                                                                 * *(_DWORD *)&this->remarkbuf[20]
                                                                                 + 3])(
              &this->m_ListSelNum[141][1824 * *(_DWORD *)&this->remarkbuf[20] + 3],
              1);
            if ( *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4834) )
            {
              v891 = (void *)this->SaleUI::AddItem(&v1162);
              (((UIWnd *)&this->m_ListSelNum[141][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIWnd::sub_445FA0(v891);
              v892 = *(_DWORD *)&this->remarkbuf[20];
              v893 = (int *)(&this->m_bWPXS + 192 * v892 + 398);
            }
            else
            {
              v894 = (void *)this->SaleUI::AddItem(&v1154);
              (((UIWnd *)&this->m_ListSelNum[141][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIWnd::sub_445FA0(v894);
              v892 = *(_DWORD *)&this->remarkbuf[20];
              v893 = (int *)(&this->m_bWPXS + 192 * v892 + 410);
            }
            (((CCBUI *)(&this->m_bWPXS + 624 * v892 + 2838)))->CCBUI::SetItemData(*v893, v893[1], v893[2], v893[3]);
          }
          goto LABEL_353;
        }
        *((_BYTE *)&this->m_bWPXS + 48 * v881 + 5083) = 1;
        *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5079) = 0;
        v884 = *(_DWORD *)&this->remarkbuf[20];
        if ( !*((_BYTE *)&this->m_bWPXS + 48 * v884 + 4838) )
        {
          v889 = (void *)this->SaleUI::AddItem(&v1151);
          (((UIWnd *)&this->m_ListSelNum[172][1824 * *(_DWORD *)&this->remarkbuf[20]]))->UIWnd::sub_445FA0(v889);
          v890 = *(_DWORD *)&this->remarkbuf[20];
          (((CCBUI *)(&this->m_bWPXS + 624 * v890 + 2890)))->CCBUI::SetItemData(*(&this->m_bWPXS + 192 * v890 + 426), *(&this->m_bWPXS + 192 * v890 + 427), *(&this->m_bWPXS + 192 * v890 + 428), *(&this->m_bWPXS + 192 * v890 + 429));
          goto LABEL_321;
        }
        v1033[0] = *(&this->m_bWPXS + 192 * v884 + 414);
        v1033[1] = *(&this->m_bWPXS + 192 * v884 + 415);
        v1033[2] = *(&this->m_bWPXS + 192 * v884 + 416);
        v1033[3] = *(&this->m_bWPXS + 192 * v884 + 417);
        (((UIWnd *)&this->m_ListSelNum[172][1824 * v884]))->UIWnd::sub_445FA0(v1033);
        v885 = *(_DWORD *)&this->remarkbuf[20];
        v886 = *(&this->m_bWPXS + 192 * v885 + 414);
        v887 = *(&this->m_bWPXS + 192 * v885 + 415);
        v888 = *(&this->m_bWPXS + 192 * v885 + 416);
        v1135 = *(&this->m_bWPXS + 192 * v885 + 417);
        v813 = (int *)(&this->m_bWPXS + 624 * v885 + 2890);
        v813[2] = v887;
        v814 = (_DWORD *)v813 + 1;
        v813[1] = v886;
        v813[3] = v888;
        v815 = v1135;
LABEL_320:
        v813[4] = v815;
        v820 = (_DWORD *)v813 + 5;
        *v820 = *v814;
        v820[1] = (unsigned long)v814[1];
        v820[2] = (unsigned long)v814[2];
        v820[3] = (unsigned long)v814[3];
LABEL_321:
        (*(void ( **)(int *, int))this->m_ListSelNum[172][1824 * *(_DWORD *)&this->remarkbuf[20]])(
          &this->m_ListSelNum[172][1824 * *(_DWORD *)&this->remarkbuf[20]],
          1);
        v3 = (_WORD *)v946;
LABEL_353:
        (*(void ( **)(int *, int))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 295][4])(
          &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 295][4],
          1);
        (**(void ( ***)(_BYTE *, int))&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 95][1])((_BYTE *)(&this->m_IsEquip[216 * *(_DWORD *)&this->remarkbuf[20] + 95][1]), (int)(1));
LABEL_406:
        result = *(_DWORD *)&this->remarkbuf[20] + 1;
        *(_DWORD *)&this->remarkbuf[20] = result;
        if ( result < 5 )
          continue;
        return result;
      case 0xB:
        v895 = *(_DWORD *)&this->remarkbuf[20];
        if ( !*((_BYTE *)v3 + v895 + 614) )
          goto LABEL_406;
        v896 = (CCBUI *)*(&this->AttackNum + 289);
        if ( !*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * v895) )
        {
          LOBYTE(v897) = (((CCBUI *)v896))->CCBUI::IsAddMode();
          (((UIPushButton *)&this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Weapon.tga", v897);
          for ( ii = 0; ii < 8; ++ii )
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[473][1824
                                                                                  * *(_DWORD *)&this->remarkbuf[20]
                                                                                  + 3
                                                                                  + 38 * ii])((SaleUI_SortData *)(&this->m_sort[473][1824 * *(_DWORD *)&this->remarkbuf[20] + 3 + 38 * ii]), (_DWORD)(0));
          v899 = *(_DWORD *)&this->remarkbuf[20];
          if ( (__int16)v3[325] <= 0 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * v899 + 5044) = 0;
          }
          else
          {
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[473][1824 * v899 + 3])((SaleUI_SortData *)(&this->m_sort[473][1824 * v899 + 3]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4800) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5044) = 1;
            v900 = *(_DWORD *)&this->remarkbuf[20];
            (((CCBUI *)(&this->m_bWPXS + 624 * v900 + 2383)))->CCBUI::SetItemData(*(&this->m_bWPXS + 192 * v900 + 270), *(&this->m_bWPXS + 192 * v900 + 271), *(&this->m_bWPXS + 192 * v900 + 272), *(&this->m_bWPXS + 192 * v900 + 273));
          }
          if ( (__int16)v3[327] <= 0 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5045) = 0;
          }
          else
          {
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5045) = 1;
            if ( *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4800) )
            {
              v901 = (void *)this->SaleUI::AddItem(&v1160);
              (((UIWnd *)&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIWnd::sub_445FA0(v901);
              v902 = *(_DWORD *)&this->remarkbuf[20];
              v903 = (int *)(&this->m_bWPXS + 192 * v902 + 278);
            }
            else
            {
              v904 = (void *)this->SaleUI::AddItem(&v1156);
              (((UIWnd *)&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIWnd::sub_445FA0(v904);
              v902 = *(_DWORD *)&this->remarkbuf[20];
              v903 = (int *)(&this->m_bWPXS + 192 * v902 + 270);
            }
            (((CCBUI *)(&this->m_bWPXS + 624 * v902 + 2396)))->CCBUI::SetItemData(*v903, v903[1], v903[2], v903[3]);
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20]
                                                                               + 1])((SaleUI_SortData *)(&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]), (int)(1));
          }
          v905 = *(_DWORD *)&this->remarkbuf[20];
          if ( (__int16)v3[326] <= 0 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * v905 + 5046) = 0;
          }
          else
          {
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[488][1824 * v905 + 4])((SaleUI_SortData *)(&this->m_sort[488][1824 * v905 + 4]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4802) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5046) = 1;
            v906 = *(_DWORD *)&this->remarkbuf[20];
            (((CCBUI *)(&this->m_bWPXS + 624 * v906 + 2409)))->CCBUI::SetItemData(*(&this->m_bWPXS + 192 * v906 + 278), *(&this->m_bWPXS + 192 * v906 + 279), *(&this->m_bWPXS + 192 * v906 + 280), *(&this->m_bWPXS + 192 * v906 + 281));
          }
          if ( (__int16)v3[328] <= 0 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5047) = 0;
          }
          else
          {
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5047) = 1;
            if ( *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4802) )
            {
              v907 = (void *)this->SaleUI::AddItem(&v1164);
              (((UIWnd *)&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIWnd::sub_445FA0(v907);
              v908 = *(_DWORD *)&this->remarkbuf[20];
              v909 = (int *)(&this->m_bWPXS + 192 * v908 + 270);
            }
            else
            {
              v910 = (void *)this->SaleUI::AddItem(&v1158);
              (((UIWnd *)&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIWnd::sub_445FA0(v910);
              v908 = *(_DWORD *)&this->remarkbuf[20];
              v909 = (int *)(&this->m_bWPXS + 192 * v908 + 282);
            }
            (((CCBUI *)(&this->m_bWPXS + 624 * v908 + 2422)))->CCBUI::SetItemData(*v909, v909[1], v909[2], v909[3]);
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20]
                                                                               + 2])((SaleUI_SortData *)(&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (int)(1));
          }
          goto LABEL_405;
        }
        LOBYTE(v911) = (((CCBUI *)v896))->CCBUI::IsAddMode();
        (((UIPushButton *)&this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][4]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Weapon.tga", v911);
        v912 = *(_DWORD *)&this->remarkbuf[20];
        v913 = v3[325];
        v914 = *(_WORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * v912) + 650);
        if ( v913 >= v914 )
        {
          if ( v913 > v914 )
          {
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[473][1824 * v912 + 3])((SaleUI_SortData *)(&this->m_sort[473][1824 * v912 + 3]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4800) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5044) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5048) = 0;
            v916 = *(_DWORD *)&this->remarkbuf[20];
            (((CCBUI *)(&this->m_bWPXS + 624 * v916 + 2383)))->CCBUI::SetItemData(*(&this->m_bWPXS + 192 * v916 + 270), *(&this->m_bWPXS + 192 * v916 + 271), *(&this->m_bWPXS + 192 * v916 + 272), *(&this->m_bWPXS + 192 * v916 + 273));
          }
        }
        else
        {
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[504][1824 * v912])((SaleUI_SortData *)(&this->m_sort[504][1824 * v912]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4804) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5048) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5044) = 0;
          v915 = *(_DWORD *)&this->remarkbuf[20];
          (((CCBUI *)(&this->m_bWPXS + 624 * v915 + 2435)))->CCBUI::SetItemData(*(&this->m_bWPXS + 192 * v915 + 286), *(&this->m_bWPXS + 192 * v915 + 287), *(&this->m_bWPXS + 192 * v915 + 288), *(&this->m_bWPXS + 192 * v915 + 289));
        }
        v917 = *(_DWORD *)&this->remarkbuf[20];
        v918 = v3[327];
        v919 = *(_WORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * v917) + 654);
        if ( v918 >= v919 )
        {
          if ( v918 <= v919 )
            goto LABEL_391;
          *((_BYTE *)&this->m_bWPXS + 48 * v917 + 5045) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5049) = 0;
          if ( *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4800) )
          {
            v925 = (void *)this->SaleUI::AddItem(&v1155);
            (((UIWnd *)&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIWnd::sub_445FA0(v925);
            v926 = *(_DWORD *)&this->remarkbuf[20];
            v927 = (int *)(&this->m_bWPXS + 192 * v926 + 278);
          }
          else
          {
            v928 = (void *)this->SaleUI::AddItem(&v1157);
            (((UIWnd *)&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1]))->UIWnd::sub_445FA0(v928);
            v926 = *(_DWORD *)&this->remarkbuf[20];
            v927 = (int *)(&this->m_bWPXS + 192 * v926 + 270);
          }
          (((CCBUI *)(&this->m_bWPXS + 624 * v926 + 2396)))->CCBUI::SetItemData(*v927, v927[1], v927[2], v927[3]);
          v924 = (SaleUI_SortData *)&this->m_sort[481][1824 * *(_DWORD *)&this->remarkbuf[20] + 1];
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v917 + 5049) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5045) = 0;
          if ( *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4804) )
          {
            v920 = (void *)this->SaleUI::AddItem(&v1152);
            (((UIWnd *)&this->m_sort[511][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIWnd::sub_445FA0(v920);
            v921 = *(_DWORD *)&this->remarkbuf[20];
            v922 = (int *)(&this->m_bWPXS + 192 * v921 + 294);
          }
          else
          {
            v923 = (void *)this->SaleUI::AddItem(&v1153);
            (((UIWnd *)&this->m_sort[511][1824 * *(_DWORD *)&this->remarkbuf[20] + 3]))->UIWnd::sub_445FA0(v923);
            v921 = *(_DWORD *)&this->remarkbuf[20];
            v922 = (int *)(&this->m_bWPXS + 192 * v921 + 286);
          }
          (((CCBUI *)(&this->m_bWPXS + 624 * v921 + 2448)))->CCBUI::SetItemData(*v922, v922[1], v922[2], v922[3]);
          v924 = (SaleUI_SortData *)&this->m_sort[511][1824 * *(_DWORD *)&this->remarkbuf[20] + 3];
        }
        (**(void ( ***)(SaleUI_SortData *, int))v924)((SaleUI_SortData *)(v924), (int)(1));
LABEL_391:
        v929 = *(_DWORD *)&this->remarkbuf[20];
        v930 = v3[326];
        v931 = *(_WORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * v929) + 652);
        if ( v930 >= v931 )
        {
          if ( v930 > v931 )
          {
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[488][1824 * v929 + 4])((SaleUI_SortData *)(&this->m_sort[488][1824 * v929 + 4]), (int)(1));
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4802) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5046) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5050) = 0;
            v933 = *(_DWORD *)&this->remarkbuf[20];
            (((CCBUI *)(&this->m_bWPXS + 624 * v933 + 2409)))->CCBUI::SetItemData(*(&this->m_bWPXS + 192 * v933 + 278), *(&this->m_bWPXS + 192 * v933 + 279), *(&this->m_bWPXS + 192 * v933 + 280), *(&this->m_bWPXS + 192 * v933 + 281));
          }
        }
        else
        {
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[519][1824 * v929 + 1])((SaleUI_SortData *)(&this->m_sort[519][1824 * v929 + 1]), (int)(1));
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4806) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5050) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5046) = 0;
          v932 = *(_DWORD *)&this->remarkbuf[20];
          (((CCBUI *)(&this->m_bWPXS + 624 * v932 + 2461)))->CCBUI::SetItemData(*(&this->m_bWPXS + 192 * v932 + 294), *(&this->m_bWPXS + 192 * v932 + 295), *(&this->m_bWPXS + 192 * v932 + 296), *(&this->m_bWPXS + 192 * v932 + 297));
        }
        v934 = *(_DWORD *)&this->remarkbuf[20];
        v935 = v3[328];
        v936 = *(_WORD *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * v934) + 656);
        if ( v935 >= v936 )
        {
          if ( v935 > v936 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * v934 + 5047) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5051) = 0;
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20]
                                                                               + 2])((SaleUI_SortData *)(&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]), (int)(1));
            if ( *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4802) )
            {
              v941 = (void *)this->SaleUI::AddItem(&v1163);
              (((UIWnd *)&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIWnd::sub_445FA0(v941);
              v942 = *(_DWORD *)&this->remarkbuf[20];
              v943 = (int *)(&this->m_bWPXS + 192 * v942 + 270);
            }
            else
            {
              v944 = (void *)this->SaleUI::AddItem((PlayerMgr *)nCol);
              (((UIWnd *)&this->m_sort[496][1824 * *(_DWORD *)&this->remarkbuf[20] + 2]))->UIWnd::sub_445FA0(v944);
              v942 = *(_DWORD *)&this->remarkbuf[20];
              v943 = (int *)(&this->m_bWPXS + 192 * v942 + 282);
            }
            (((CCBUI *)(&this->m_bWPXS + 624 * v942 + 2422)))->CCBUI::SetItemData(*v943, v943[1], v943[2], v943[3]);
          }
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v934 + 5051) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 5047) = 0;
          if ( *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->remarkbuf[20] + 4806) )
          {
            v937 = (void *)this->SaleUI::AddItem(&v1159);
            (((UIWnd *)&this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIWnd::sub_445FA0(v937);
            v938 = *(_DWORD *)&this->remarkbuf[20];
            v939 = (int *)(&this->m_bWPXS + 192 * v938 + 286);
          }
          else
          {
            v940 = (void *)this->SaleUI::AddItem(&v1161);
            (((UIWnd *)&this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]))->UIWnd::sub_445FA0(v940);
            v938 = *(_DWORD *)&this->remarkbuf[20];
            v939 = (int *)(&this->m_bWPXS + 192 * v938 + 298);
          }
          (((CCBUI *)(&this->m_bWPXS + 624 * v938 + 2474)))->CCBUI::SetItemData(*v939, v939[1], v939[2], v939[3]);
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20]
                                                                             + 4])((SaleUI_SortData *)(&this->m_sort[526][1824 * *(_DWORD *)&this->remarkbuf[20] + 4]), (int)(1));
        }
LABEL_405:
        (*(void ( **)(int *, int))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][4])(
          &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 286][4],
          1);
        goto LABEL_406;
      default:
        goto LABEL_406;
    }
  }
}

// 0x00469D50
int SaleUI::AddItem(PlayerMgr *thisa)
{
  int *v2; // ecx
  int result; // eax
  int v4; // [esp+0xC] [ebp+0x8]
  int v5; // [esp+0x10] [ebp+0xC]
  int v6; // [esp+0x14] [ebp+0x10]

  v2 = (int *)(&this->m_bWPXS + 192 * v4 + 32 * v5 + 4 * v6 + 238);
  result = (int)thisa;
  *(_DWORD *)thisa = (unsigned long)*v2;
  *(_DWORD *)&thisa[4] = (unsigned long)v2[1];
  *(_DWORD *)&thisa[8] = (unsigned long)v2[2];
  *(_DWORD *)&thisa[12] = (unsigned long)v2[3];
  return result;
}

// 0x00469D90
void SaleUI::SetupPlayerDisplay(int nVal)
{
  char *buf; // ebx
  CHAR *v4; // ebp
  RoleAtt *v5; // ecx
  void (__stdcall *v6)(LPSTR, LPCSTR); // ebp
  LPCSTR v7; // eax
  CHAR String1[253]; // [esp+0x10] [ebp-0x100] BYREF
  __int16 v9; // [esp+0x10D] [ebp-0x3]
  char v10; // [esp+0x10F] [ebp-0x1]

  buf = this->buf;
  sprintf(this->buf, unk_C10D38);
  memset(String1, 0, sizeof(String1));
  v9 = 0;
  v10 = 0;
  v4 = (CHAR *)sub_458F70((LPCSTR)(*(&this->dwWeaponWU + nVal + 3666) + 96), (int)asc_5B74B8, String1);
  if ( lstrlenA((const char *)v4) <= 0 )
  {
    (((RoleAtt *)v5))->RoleAtt::FormatAttributeText();
    v6 = (void (__stdcall *)(LPSTR, LPCSTR))lstrcatA;
    lstrcatA(buf, v7);
  }
  else
  {
    lstrcpyA(buf, v4);
    v6 = (void (__stdcall *)(LPSTR, LPCSTR))lstrcatA;
  }
  SetEnable((UICaption *)&this->ml_ResumeList.m_column[0].head[16]);
  switch ( *(_BYTE *)(*(&this->dwWeaponWU + nVal + 3666) + 613) )
  {
    case 1:
    case 3:
      v6(buf, " ");
      v6(buf, (LPCSTR)&dword_DDAA3C);
      break;
    case 2:
    case 5:
    case 6:
      v6(buf, " ");
      v6(buf, byte_DCEB3C);
      break;
    case 4:
    case 7:
      v6(buf, " ");
      v6(buf, (LPCSTR)&dword_DDA93C);
      break;
    default:
      break;
  }
  SetEnable((UICaption *)&this->ml_ResumeList.m_column[2].head[16]);
}

// 0x00469EB0
BOOL SaleUI::HandleInput(int nInputID, int nParam, int nFlags)
{
  BOOL result; // eax
  int m_needscriptdel; // eax
  int v8; // ecx
  int v10; // edx
  int v11; // ebx
  SaleUI_SortData *v12; // ecx
  SaleUI_SortData *v13; // edx
  _DWORD *v14; // eax
  _DWORD *v15; // eax
  SaleUI_SortData *v16; // edx
  int *v17; // ecx
  int v18; // edx
  int v19; // edx
  char v20; // bl
  _BYTE *v21; // edx
  SaleUI_SortData *v22; // ecx
  SaleUI_SortData *v23; // eax
  _DWORD *v24; // eax
  _DWORD *v25; // eax
  SaleUI_SortData *v26; // edx
  int v27; // ebx
  SaleUI_SortData *v28; // ecx
  SaleUI_SortData *v29; // eax
  _DWORD *v30; // eax
  _DWORD *v31; // eax
  SaleUI_SortData *v32; // edx
  int v33; // ebx
  SaleUI_SortData *v34; // ecx
  SaleUI_SortData *v35; // eax
  _DWORD *v36; // eax
  _DWORD *v37; // eax
  SaleUI_SortData *v38; // edx
  int v39; // ebx
  SaleUI_SortData *v40; // ecx
  SaleUI_SortData *v41; // eax
  _DWORD *v42; // eax
  _DWORD *v43; // eax
  SaleUI_SortData *v44; // edx
  int v45; // ebx
  SaleUI_SortData *v46; // ecx
  SaleUI_SortData *v47; // eax
  _DWORD *v48; // eax
  _DWORD *v49; // eax
  SaleUI_SortData *v50; // edx
  RoleSystem *v51; // esi
  int *v52; // eax
  int v53; // esi
  int v54; // edx
  int nVal; // [esp+0x14] [ebp+0x4]
  int *nParama; // [esp+0x18] [ebp+0x8]
  int *nParamb; // [esp+0x18] [ebp+0x8]
  gbTexture **nParamc; // [esp+0x18] [ebp+0x8]
  int *nParamd; // [esp+0x18] [ebp+0x8]
  int *nParame; // [esp+0x18] [ebp+0x8]
  int *nParamf; // [esp+0x18] [ebp+0x8]
  int nFlagsa; // [esp+0x1C] [ebp+0xC]

  if ( *((_BYTE *)&this->AttackNum + 1152) )
  {
    LOBYTE(result) = 0;
  }
  else if ( nFlags >= 0 )
  {
    m_needscriptdel = this->m_ListSaleTitle.m_childs.m_needscriptdel;
    v8 = *(_DWORD *)(m_needscriptdel + 4 * nFlags);
    result = m_needscriptdel + 4 * nFlags;
    if ( v8 > 0 )
    {
      if ( LOBYTE(this->m_ListSaleTitle.m_rect.left) )
      {
        v10 = 6 * nInputID;
        nFlagsa = 6 * nInputID;
        nVal = 6 * nInputID + nParam;
        if ( *(&this->m_ListSaleTitle.m_bcreateok + nVal) == nFlags )
        {
          LOBYTE(result) = 0;
        }
        else
        {
          switch ( nParam )
          {
            case 0:
              v11 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v11 + 612) == 7 && *(_BYTE *)(v11 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->m_ListSaleTitle.m_rect.left + v10 + 1) )
                {
                  nParama = (int *)(&this->m_ListSaleTitle.m_bcreateok + 6 * nInputID);
                  if ( *nParama != nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                    v12 = (SaleUI_SortData *)&this->m_sort[32][352 * nInputID + 2];
                    v13 = (SaleUI_SortData *)(&g_RoleSlotBuf.m_partyActor.m_nAnimFrames + 352 * nInputID);
                    *v13 = *v12;
                    v13[1] = this->m_sort[32][352 * nInputID + 3];
                    v13[2] = this->m_sort[32][352 * nInputID + 4];
                    *v12 = 0;
                    v12[1] = 0;
                    v12[2] = 0;
                    v14 = (_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *nParama);
                    ++*v14;
                    v10 = nFlagsa;
                    v15 = (_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * *nParama);
                    --*v15;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                }
                *((_BYTE *)&this->m_ListSaleTitle.m_rect.left + v10 + 1) = 1;
                (*(void ( **)(Parent_Data **, int))this->m_Role[6 * nInputID + 2].m_fonttype)(
                  &this->m_Role[6 * nInputID + 2].m_fonttype,
                  1);
                *(&this->m_ListSaleTitle.m_bcreateok + 6 * nInputID) = nFlags;
                if ( g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID] )
                {
                  this->m_sort[32][352 * nInputID + 2] = (SaleUI_SortData)*(&g_RoleSlotBuf.m_partyActor.m_nAnimFrames
                                                                          + 352 * nInputID);
                  this->m_sort[32][352 * nInputID + 3] = (SaleUI_SortData)*(&g_RoleSlotBuf.m_partyActor.m_nTransitionParam
                                                                          + 352 * nInputID);
                  this->m_sort[32][352 * nInputID + 4] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID];
                }
                else
                {
                  v16 = (SaleUI_SortData *)&this->m_sort[32][352 * nInputID + 2];
                  *v16 = 0;
                  v16[1] = 0;
                  v16[2] = 0;
                }
                *(&g_RoleSlotBuf.m_partyActor.m_nAnimFrames + 352 * nInputID) = **((_DWORD **)&this->dwWeaponWU
                                                                                 + nFlags
                                                                                 + 3666);
                *(&g_RoleSlotBuf.m_partyActor.m_nTransitionParam + 352 * nInputID) = 1;
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID] = (RoleAtt *)*(&this->dwWeaponWU + nFlags + 3666);
                v17 = (int *)&this->m_NotesNull[54 * nInputID + 277][4];
                goto LABEL_72;
              }
              break;
            case 1:
              v45 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v45 + 612) == 11 && *(_BYTE *)(v45 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->m_ListSaleTitle.m_rect.left + v10 + 2) )
                {
                  nParamf = (int *)(&this->m_ListSaleTitle.m_bvisible + 6 * nInputID);
                  if ( *nParamf != nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                    v46 = (SaleUI_SortData *)&this->m_sort[34][352 * nInputID + 4];
                    v47 = (SaleUI_SortData *)(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * nInputID);
                    *v47 = *v46;
                    v47[1] = this->m_sort[35][352 * nInputID];
                    v47[2] = this->m_sort[35][352 * nInputID + 1];
                    *v46 = 0;
                    v46[1] = 0;
                    v46[2] = 0;
                    v48 = (_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *nParamf);
                    ++*v48;
                    v49 = (_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * *nParamf);
                    v10 = nFlagsa;
                    --*v49;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                }
                *((_BYTE *)&this->m_ListSaleTitle.m_rect.left + v10 + 2) = 1;
                (*(void ( **)(Parent_Data **, int))this->m_Role[6 * nInputID + 3].m_fonttype)(
                  &this->m_Role[6 * nInputID + 3].m_fonttype,
                  1);
                *(&this->m_ListSaleTitle.m_bvisible + 6 * nInputID) = nFlags;
                if ( *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nInputID) )
                {
                  this->m_sort[34][352 * nInputID + 4] = (SaleUI_SortData)*(&g_RoleSlotBuf.m_partyActor.m_obbox
                                                                          + 352 * nInputID);
                  this->m_sort[35][352 * nInputID] = (SaleUI_SortData)*(&g_RoleSlotBuf.m_partyActor.m_obbox
                                                                      + 352 * nInputID
                                                                      + 1);
                  this->m_sort[35][352 * nInputID + 1] = (SaleUI_SortData)*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt
                                                                          + 352 * nInputID);
                }
                else
                {
                  v50 = (SaleUI_SortData *)&this->m_sort[34][352 * nInputID + 4];
                  *v50 = 0;
                  v50[1] = 0;
                  v50[2] = 0;
                }
                *(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * nInputID) = **((_DWORD **)&this->dwWeaponWU + nFlags + 3666);
                *(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * nInputID + 1) = 1;
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * nInputID) = *(&this->dwWeaponWU
                                                                                       + nFlags
                                                                                       + 3666);
                v17 = (int *)&this->m_NotesNull[54 * nInputID + 286][4];
                goto LABEL_72;
              }
              break;
            case 2:
              v33 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v33 + 612) == 10 && *(_BYTE *)(v33 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->m_ListSaleTitle.m_rect.left + v10 + 3) )
                {
                  nParamd = (int *)(&this->m_ListSaleTitle.m_benable + 6 * nInputID);
                  if ( *nParamd != nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                    v34 = (SaleUI_SortData *)&this->m_sort[33][352 * nInputID + 3];
                    v35 = (SaleUI_SortData *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 1];
                    *v35 = *v34;
                    v35[1] = this->m_sort[33][352 * nInputID + 4];
                    v35[2] = this->m_sort[34][352 * nInputID];
                    *v34 = 0;
                    v34[1] = 0;
                    v34[2] = 0;
                    v36 = (_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *nParamd);
                    ++*v36;
                    v37 = (_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * *nParamd);
                    v10 = nFlagsa;
                    --*v37;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                }
                *((_BYTE *)&this->m_ListSaleTitle.m_rect.left + v10 + 3) = 1;
                (*(void ( **)(Parent_Data **, int))this->m_Role[6 * nInputID + 4].m_fonttype)(
                  &this->m_Role[6 * nInputID + 4].m_fonttype,
                  1);
                *(&this->m_ListSaleTitle.m_benable + 6 * nInputID) = nFlags;
                *((_BYTE *)&this->m_Icon[0][0].m_fontcolor.Color + 2 * nInputID) = 1;
                if ( g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3] )
                {
                  this->m_sort[33][352 * nInputID + 3] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 1];
                  this->m_sort[33][352 * nInputID + 4] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 2];
                  this->m_sort[34][352 * nInputID] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3];
                }
                else
                {
                  v38 = (SaleUI_SortData *)&this->m_sort[33][352 * nInputID + 3];
                  *v38 = 0;
                  v38[1] = 0;
                  v38[2] = 0;
                }
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 1] = (RoleAtt *)**((_DWORD **)&this->dwWeaponWU
                                                                                          + nFlags
                                                                                          + 3666);
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 2] = (RoleAtt *)1;
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 3] = (RoleAtt *)*(&this->dwWeaponWU
                                                                                         + nFlags
                                                                                         + 3666);
                v17 = (int *)&this->m_NotesNull[54 * nInputID + 295][4];
                goto LABEL_72;
              }
              break;
            case 3:
              v18 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v18 + 612) == 8 && *(_BYTE *)(v18 + nInputID + 614) )
              {
                v19 = 3 * nInputID + 46722;
                v20 = *((_BYTE *)((UIWnd *)this) + 2 * v19);
                v21 = (char *)this + 2 * v19;
                if ( v20 )
                {
                  nParamb = (int *)(&this->m_ListSaleTitle.m_bfocus + 6 * nInputID);
                  if ( *nParamb != nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                    v22 = (SaleUI_SortData *)&this->m_sort[31][352 * nInputID + 4];
                    v23 = (SaleUI_SortData *)(&g_RoleSlotBuf.m_partyActor.m_nModelParamB + 352 * nInputID);
                    *v23 = *v22;
                    v23[1] = this->m_sort[32][352 * nInputID];
                    v23[2] = this->m_sort[32][352 * nInputID + 1];
                    *v22 = 0;
                    v22[1] = 0;
                    v22[2] = 0;
                    v24 = (_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *nParamb);
                    ++*v24;
                    v25 = (_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * *nParamb);
                    --*v25;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                }
                *v21 = 1;
                (*(void ( **)(LONG *, int))this->m_RoleRc[57 * nInputID + 3].top)(
                  &this->m_RoleRc[57 * nInputID + 3].top,
                  1);
                *(&this->m_ListSaleTitle.m_bfocus + 6 * nInputID) = nFlags;
                if ( *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nInputID) )
                {
                  this->m_sort[31][352 * nInputID + 4] = (SaleUI_SortData)*(&g_RoleSlotBuf.m_partyActor.m_nModelParamB
                                                                          + 352 * nInputID);
                  this->m_sort[32][352 * nInputID] = (SaleUI_SortData)*(&g_RoleSlotBuf.m_partyActor.m_nRoleState1
                                                                      + 352 * nInputID);
                  this->m_sort[32][352 * nInputID + 1] = (SaleUI_SortData)*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0
                                                                          + 352 * nInputID);
                }
                else
                {
                  v26 = (SaleUI_SortData *)&this->m_sort[31][352 * nInputID + 4];
                  *v26 = 0;
                  v26[1] = 0;
                  v26[2] = 0;
                }
                *(&g_RoleSlotBuf.m_partyActor.m_nModelParamB + 352 * nInputID) = **((_DWORD **)&this->dwWeaponWU
                                                                                  + nFlags
                                                                                  + 3666);
                *(&g_RoleSlotBuf.m_partyActor.m_nRoleState1 + 352 * nInputID) = 1;
                *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt0 + 352 * nInputID) = *(&this->dwWeaponWU
                                                                                         + nFlags
                                                                                         + 3666);
                v17 = (int *)&this->m_IsEquip[216 * nInputID + 23][1];
                goto LABEL_72;
              }
              break;
            case 4:
              v27 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v27 + 612) == 9 && *(_BYTE *)(v27 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->m_ListSaleTitle.m_rect.top + v10 + 1) )
                {
                  nParamc = (gbTexture **)(&this->m_ListSaleTitle.pDebugTex + 6 * nInputID);
                  if ( *nParamc != (gbTexture *)nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                    v28 = (SaleUI_SortData *)&this->m_sort[33][352 * nInputID];
                    v29 = (SaleUI_SortData *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID + 1];
                    *v29 = *v28;
                    v29[1] = this->m_sort[33][352 * nInputID + 1];
                    v29[2] = this->m_sort[33][352 * nInputID + 2];
                    *v28 = 0;
                    v28[1] = 0;
                    v28[2] = 0;
                    v30 = (_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * (_DWORD)*nParamc);
                    ++*v30;
                    v31 = (_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * (_DWORD)*nParamc);
                    v10 = nFlagsa;
                    --*v31;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                }
                *((_BYTE *)&this->m_ListSaleTitle.m_rect.top + v10 + 1) = 1;
                (**((void ( ***)(LONG *, int))&this->m_Msg.m_textRc.top + 228 * nInputID))((LONG *)(&this->m_Msg.m_textRc.top + 228 * nInputID), (int)(1));
                *((_DWORD *)&this->m_ListSaleTitle.pDebugTex + 6 * nInputID) = nFlags;
                if ( g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID] )
                {
                  this->m_sort[33][352 * nInputID] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID + 1];
                  this->m_sort[33][352 * nInputID + 1] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID + 2];
                  this->m_sort[33][352 * nInputID + 2] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID];
                }
                else
                {
                  v32 = (SaleUI_SortData *)&this->m_sort[33][352 * nInputID];
                  *v32 = 0;
                  v32[1] = 0;
                  v32[2] = 0;
                }
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID + 1] = (RoleAtt *)**((_DWORD **)&this->dwWeaponWU
                                                                                          + nFlags
                                                                                          + 3666);
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nInputID + 2] = (RoleAtt *)1;
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID] = (RoleAtt *)*(&this->dwWeaponWU + nFlags + 3666);
                v17 = (int *)&this->m_IsEquip[216 * nInputID + 59][1];
                goto LABEL_72;
              }
              break;
            case 5:
              v39 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v39 + 612) == 10 && *(_BYTE *)(v39 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->m_ListSaleTitle.m_rect.top + v10 + 2) )
                {
                  nParame = (int *)(&this->m_ListSaleTitle.m_align + 6 * nInputID);
                  if ( *nParame != nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                    v40 = (SaleUI_SortData *)&this->m_sort[34][352 * nInputID + 1];
                    v41 = (SaleUI_SortData *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 4];
                    *v41 = *v40;
                    v41[1] = this->m_sort[34][352 * nInputID + 2];
                    v41[2] = this->m_sort[34][352 * nInputID + 3];
                    *v40 = 0;
                    v40[1] = 0;
                    v40[2] = 0;
                    v42 = (_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *nParame);
                    ++*v42;
                    v43 = (_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * *nParame);
                    v10 = nFlagsa;
                    --*v43;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * nFlags);
                }
                *((_BYTE *)&this->m_ListSaleTitle.m_rect.top + v10 + 2) = 1;
                ((void ( *)(gbTexture **, int))((gbRefObject *)this->m_Msg.m_bk.m_texs.m_ptex[228 * nInputID + 14]))(
                  &this->m_Msg.m_bk.m_texs.m_ptex[228 * nInputID + 14],
                  1);
                *(&this->m_ListSaleTitle.m_align + 6 * nInputID) = nFlags;
                *((_BYTE *)&this->m_Icon[0][0].m_fontcolor.Color + 2 * nInputID + 1) = 1;
                if ( g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6] )
                {
                  this->m_sort[34][352 * nInputID + 1] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 4];
                  this->m_sort[34][352 * nInputID + 2] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 5];
                  this->m_sort[34][352 * nInputID + 3] = (SaleUI_SortData)g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6];
                }
                else
                {
                  v44 = (SaleUI_SortData *)&this->m_sort[34][352 * nInputID + 1];
                  *v44 = 0;
                  v44[1] = 0;
                  v44[2] = 0;
                }
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 4] = (RoleAtt *)**((_DWORD **)&this->dwWeaponWU
                                                                                          + nFlags
                                                                                          + 3666);
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 5] = (RoleAtt *)1;
                g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nInputID + 6] = (RoleAtt *)*(&this->dwWeaponWU
                                                                                         + nFlags
                                                                                         + 3666);
                v17 = (int *)&this->m_IsEquip[216 * nInputID + 95][1];
LABEL_72:
                (((CCBResultWindow *)v17))->CCBResultWindow::SetDirty();
              }
              break;
            default:
              break;
          }
          v51 = (RoleSystem *)((char *)&g_RoleSlotBuf + 1408 * nInputID);
          (((RoleSystem *)v51))->RoleSystem::RecalcAggregatedStats(0);
          v52 = (int *)&v51->m_partyActor.m_dwMatMsg[2];
          v53 = 12;
          do
          {
            v54 = *(v52 - 12);
            if ( *v52 < v54 )
            {
              if ( *v52 <= 0 )
                *v52 = 0;
            }
            else
            {
              *v52 = v54;
            }
            ++v52;
            --v53;
          }
          while ( v53 );
          result = this->SaleUI::CreatePanelElements((CCBUIPanel *)nFlags);
          LOBYTE(result) = *((_BYTE *)&this->m_ListSaleTitle.m_rect.left + nVal + 1);
        }
      }
      else
      {
        LOBYTE(result) = 0;
      }
    }
    else
    {
      LOBYTE(result) = 0;
    }
  }
  else
  {
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x0046A8B0
int SaleUI::Update(int deltatime, int haveinput)
{
  int result; // eax
  _BYTE *v5; // edx
  SaleUI_SortData *v6; // ecx
  SaleUI_SortData *v7; // eax
  int *v8; // eax
  _BYTE *v9; // edx
  SaleUI_SortData *v10; // ecx
  SaleUI_SortData *v11; // eax
  _BYTE *v12; // edx
  SaleUI_SortData *v13; // ecx
  SaleUI_SortData *v14; // eax
  _BYTE *v15; // edx
  SaleUI_SortData *v16; // ecx
  SaleUI_SortData *v17; // eax
  _BYTE *v18; // edx
  SaleUI_SortData *v19; // ecx
  SaleUI_SortData *v20; // eax
  _BYTE *v21; // edx
  SaleUI_SortData *v22; // ecx
  SaleUI_SortData *v23; // eax
  _DWORD *v24; // ecx
  unsigned int *v25; // eax
  int v26; // ebx
  int v27; // edx
  int v28; // esi

  result = haveinput;
  if ( haveinput < 6 )
  {
    switch ( haveinput )
    {
      case 0:
        v5 = (char *)&this->m_ListSaleTitle.m_rect.left + 6 * deltatime + 1;
        if ( *v5 )
        {
          v6 = (SaleUI_SortData *)&this->m_sort[32][352 * deltatime + 2];
          v7 = (SaleUI_SortData *)(&g_RoleSlotBuf.m_partyActor.m_nAnimFrames + 352 * deltatime);
          *v7 = this->m_sort[32][352 * deltatime + 2];
          v7[1] = this->m_sort[32][352 * deltatime + 3];
          v7[2] = this->m_sort[32][352 * deltatime + 4];
          *v6 = 0;
          v6[1] = 0;
          v6[2] = 0;
          *v5 = 0;
          (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * deltatime + 2].m_fonttype)(
            &this->m_Role[6 * deltatime + 2].m_fonttype,
            0);
          v8 = (int *)(&this->m_ListSaleTitle.m_bcreateok + 6 * deltatime);
          goto LABEL_15;
        }
        break;
      case 1:
        v21 = (char *)&this->m_ListSaleTitle.m_rect.left + 6 * deltatime + 2;
        if ( *v21 )
        {
          v22 = (SaleUI_SortData *)&this->m_sort[34][352 * deltatime + 4];
          v23 = (SaleUI_SortData *)(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * deltatime);
          *v23 = this->m_sort[34][352 * deltatime + 4];
          v23[1] = this->m_sort[35][352 * deltatime];
          v23[2] = this->m_sort[35][352 * deltatime + 1];
          *v22 = 0;
          v22[1] = 0;
          v22[2] = 0;
          *v21 = 0;
          (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * deltatime + 3].m_fonttype)(
            &this->m_Role[6 * deltatime + 3].m_fonttype,
            0);
          v8 = (int *)(&this->m_ListSaleTitle.m_bvisible + 6 * deltatime);
          goto LABEL_15;
        }
        break;
      case 2:
        v15 = (char *)&this->m_ListSaleTitle.m_rect.left + 6 * deltatime + 3;
        if ( *v15 )
        {
          v16 = (SaleUI_SortData *)&this->m_sort[33][352 * deltatime + 3];
          v17 = (SaleUI_SortData *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * deltatime + 1];
          *v17 = this->m_sort[33][352 * deltatime + 3];
          v17[1] = this->m_sort[33][352 * deltatime + 4];
          v17[2] = this->m_sort[34][352 * deltatime];
          *v16 = 0;
          v16[1] = 0;
          v16[2] = 0;
          *v15 = 0;
          (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * deltatime + 4].m_fonttype)(
            &this->m_Role[6 * deltatime + 4].m_fonttype,
            0);
          *((_BYTE *)&this->m_Icon[0][0].m_fontcolor.Color + 2 * deltatime) = 0;
          v8 = (int *)(&this->m_ListSaleTitle.m_benable + 6 * deltatime);
          goto LABEL_15;
        }
        break;
      case 3:
        v9 = (char *)&this->m_ListSaleTitle.m_rect.top + 6 * deltatime;
        if ( *v9 )
        {
          v10 = (SaleUI_SortData *)&this->m_sort[31][352 * deltatime + 4];
          v11 = (SaleUI_SortData *)(&g_RoleSlotBuf.m_partyActor.m_nModelParamB + 352 * deltatime);
          *v11 = this->m_sort[31][352 * deltatime + 4];
          v11[1] = this->m_sort[32][352 * deltatime];
          v11[2] = this->m_sort[32][352 * deltatime + 1];
          *v10 = 0;
          v10[1] = 0;
          v10[2] = 0;
          *v9 = 0;
          (*(void ( **)(LONG *, _DWORD))this->m_RoleRc[57 * deltatime + 3].top)(
            &this->m_RoleRc[57 * deltatime + 3].top,
            0);
          v8 = (int *)(&this->m_ListSaleTitle.m_bfocus + 6 * deltatime);
          goto LABEL_15;
        }
        break;
      case 4:
        v12 = (char *)&this->m_ListSaleTitle.m_rect.top + 6 * deltatime + 1;
        if ( *v12 )
        {
          v13 = (SaleUI_SortData *)&this->m_sort[33][352 * deltatime];
          v14 = (SaleUI_SortData *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * deltatime + 1];
          *v14 = this->m_sort[33][352 * deltatime];
          v14[1] = this->m_sort[33][352 * deltatime + 1];
          v14[2] = this->m_sort[33][352 * deltatime + 2];
          *v13 = 0;
          v13[1] = 0;
          v13[2] = 0;
          *v12 = 0;
          (**((void ( ***)(LONG *, _DWORD))&this->m_Msg.m_textRc.top + 228 * deltatime))((LONG *)(&this->m_Msg.m_textRc.top + 228 * deltatime), (_DWORD)(0));
          v8 = (int *)(&this->m_ListSaleTitle.pDebugTex + 6 * deltatime);
          goto LABEL_15;
        }
        break;
      case 5:
        v18 = (char *)&this->m_ListSaleTitle.m_rect.top + 6 * deltatime + 2;
        if ( *v18 )
        {
          v19 = (SaleUI_SortData *)&this->m_sort[34][352 * deltatime + 1];
          v20 = (SaleUI_SortData *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * deltatime + 4];
          *v20 = this->m_sort[34][352 * deltatime + 1];
          v20[1] = this->m_sort[34][352 * deltatime + 2];
          v20[2] = this->m_sort[34][352 * deltatime + 3];
          *v19 = 0;
          v19[1] = 0;
          v19[2] = 0;
          *v18 = 0;
          ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_Msg.m_bk.m_texs.m_ptex[228 * deltatime + 14]))(
            &this->m_Msg.m_bk.m_texs.m_ptex[228 * deltatime + 14],
            0);
          *((_BYTE *)&this->m_Icon[0][0].m_fontcolor.Color + 2 * deltatime + 1) = 0;
          v8 = (int *)(&this->m_ListSaleTitle.m_align + 6 * deltatime);
LABEL_15:
          ++*(_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *v8);
          v24 = (_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * *v8);
          --*v24;
          *(_DWORD *)this->remarkbuf = (unsigned long)*v8;
        }
        break;
      default:
        break;
    }
    (((RoleSystem *)((char *)&g_RoleSlotBuf + 1408 * deltatime)))->RoleSystem::RecalcAggregatedStats(0);
    v25 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * deltatime + 2];
    v26 = 12;
    do
    {
      v27 = *(v25 - 12);
      if ( (int)*v25 < v27 )
      {
        if ( (int)*v25 <= 0 )
          *v25 = 0;
      }
      else
      {
        *v25 = v27;
      }
      ++v25;
      --v26;
    }
    while ( v26 );
    v28 = haveinput + 6 * deltatime;
    if ( *(int *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *(&this->m_ListSaleTitle.m_bcreateok + v28)) <= 0 )
      (((CCBResultWindow *)&this->m_NotesNull[9 * v28 + 277][4]))->CCBResultWindow::SetDirty();
    else
      (((CCBResultWindow *)&this->m_NotesNull[9 * v28 + 277][4]))->CCBResultWindow::StartAnim();
    *(&this->m_ListSaleTitle.m_bcreateok + v28) = -1;
    (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItem();
    this->SaleUI::CreatePanelElements(*(CCBUIPanel **)this->remarkbuf);
    this->SaleUI::SetupPlayerDisplay(*(_DWORD *)this->remarkbuf);
    LOBYTE(this->m_ListSaleTitle.m_rect.left) = 1;
    return this->SaleUI::GetValue(0);
  }
  return result;
}

// 0x0046ACD0
int SaleUI::ConsumeItems()
{
  int i; // edi
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int result; // eax

  for ( i = 0; i < *(&this->dwWeaponWU + 3264); ++i )
  {
    while ( *(int *)(this->m_ListEquipTitleRc.bottom + 4 * i) > 0 )
    {
      *(_DWORD *)&this->remarkbuf[24] = 0;
      while ( 1 )
      {
        v3 = *(_DWORD *)&this->remarkbuf[24];
        if ( this->m_sort[412][2]._tail_000[v3] )
        {
          *(_DWORD *)&this->remarkbuf[28] = 0;
          while ( 1 )
          {
            v4 = *(_DWORD *)&this->remarkbuf[28];
            if ( *(&this->m_ListSaleTitle.m_bcreateok + 6 * v3 + v4) == i )
              break;
            v5 = v4 + 1;
            *(_DWORD *)&this->remarkbuf[28] = v5;
            if ( v5 >= 6 )
              goto LABEL_10;
          }
          this->SaleUI::Update(v3, *(_DWORD *)&this->remarkbuf[28]);
          this->SaleUI::GetValue(0);
          LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
          *(_DWORD *)&this->remarkbuf[28] = 1;
LABEL_10:
          if ( *(_DWORD *)&this->remarkbuf[28] == 1 )
            break;
        }
        v6 = *(_DWORD *)&this->remarkbuf[24] + 1;
        *(_DWORD *)&this->remarkbuf[24] = v6;
        if ( v6 >= 5 )
          goto LABEL_14;
      }
      *(_DWORD *)&this->remarkbuf[28] = 0;
LABEL_14:
      ;
    }
  }
  memset((void *)this->m_ListEquipTitleRc.bottom, 0, 4 * *(&this->dwWeaponWU + 3264));
  result = 0;
  memset((void *)this->m_ListSaleTitle.m_childs.m_needscriptdel, 0, 4 * *(&this->dwWeaponWU + 3264));
  return result;
}

// 0x0046B040
int SaleUI::ProcessCellAnimations(int deltatime, int haveinput)
{
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int *v7; // edx
  int v8; // eax
  int v9; // ecx
  int *v10; // edx
  int v11; // ebp
  int v12; // edx
  int *v13; // ecx
  int *v14; // edx
  int v15; // edi
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int *v19; // edx
  int v20; // eax
  int v21; // ecx
  int *v22; // edx
  int v23; // ebp
  int v24; // edx
  int *v25; // ecx
  int *v26; // edx
  int v27; // edi
  int v28; // ecx
  int v29; // eax
  int v30; // eax
  int v32; // [esp-0x14] [ebp-0x24] BYREF
  int v33; // [esp-0x10] [ebp-0x20]
  int v34; // [esp-0xC] [ebp-0x1C]
  int v35; // [esp-0x8] [ebp-0x18]
  SaleUI_SortData *v36; // [esp-0x4] [ebp-0x14]

  GetCellStateByte(this);
  (((GRPinput *)this))->GRPinput::ProcessButtonHold(*(float *)&deltatime);
  *(_DWORD *)&this->remarkbuf[20] = 0;
  do
  {
    if ( this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
    {
      *(_DWORD *)&this->remarkbuf[24] = 0;
      do
      {
        *(_DWORD *)&this->remarkbuf[28] = 0;
        do
        {
          *(&this->m_bWPXS
          + 624 * *(_DWORD *)&this->remarkbuf[20]
          + 104 * *(_DWORD *)&this->remarkbuf[24]
          + 13 * *(_DWORD *)&this->remarkbuf[28]
          + 2279) = 36;
          v4 = *(_DWORD *)&this->remarkbuf[28] + 1;
          *(_DWORD *)&this->remarkbuf[28] = v4;
        }
        while ( v4 < 8 );
        v6 = *(_DWORD *)&this->remarkbuf[24];
        v5 = v6 + 6 * *(_DWORD *)&this->remarkbuf[20];
        LOBYTE(v6) = *((_BYTE *)&this->m_bWPXS + 8 * v5 + 5036);
        if ( (_BYTE)v6 )
        {
          v36 = (SaleUI_SortData *)&this->m_sort[412][304 * v5 + 4];
          v32 = *(&this->m_bWPXS + 32 * v5 + 1319);
          v33 = *(&this->m_bWPXS + 32 * v5 + 1320);
          v34 = *(&this->m_bWPXS + 32 * v5 + 1321);
          v35 = *(&this->m_bWPXS + 32 * v5 + 1322);
          (((UIFrameWnd *)(&this->m_bWPXS + 104 * v5 + 2279)))->UIFrameWnd::ProcessTimer(v6, 1, 1, v32);
        }
        else
        {
          v36 = (SaleUI_SortData *)&this->m_sort[443][304 * v5 + 1];
          v7 = (int *)&v32;
          v32 = *(&this->m_bWPXS + 32 * v5 + 1335);
          v33 = *(&this->m_bWPXS + 32 * v5 + 1336);
          v34 = *(&this->m_bWPXS + 32 * v5 + 1337);
          v35 = *(&this->m_bWPXS + 32 * v5 + 1338);
          LOBYTE(v7) = *((_BYTE *)&this->m_bWPXS + 8 * v5 + 5040);
          (((UIFrameWnd *)(&this->m_bWPXS + 104 * v5 + 2331)))->UIFrameWnd::ProcessTimer((BOOL)v7, 1, 1, v32);
        }
        v9 = *(_DWORD *)&this->remarkbuf[24];
        v8 = v9 + 6 * *(_DWORD *)&this->remarkbuf[20];
        LOBYTE(v9) = *((_BYTE *)&this->m_bWPXS + 8 * v8 + 5037);
        if ( (_BYTE)v9 )
        {
          if ( *((_BYTE *)&this->m_bWPXS + 8 * v8 + 5036) )
          {
            v36 = (SaleUI_SortData *)&this->m_sort[420][304 * v8 + 2];
            v10 = (int *)(&this->m_bWPXS + 32 * v8 + 1327);
          }
          else
          {
            v36 = (SaleUI_SortData *)&this->m_sort[420][304 * v8 + 2];
            v10 = (int *)(&this->m_bWPXS + 32 * v8 + 1319);
          }
          v32 = (unsigned long)*v10;
          v33 = (unsigned long)v10[1];
          v11 = (unsigned long)v10[2];
          v12 = (unsigned long)v10[3];
          v34 = v11;
          v35 = v12;
          (((UIFrameWnd *)(&this->m_bWPXS + 104 * v8 + 2292)))->UIFrameWnd::ProcessTimer(v9, 1, 1, v32);
        }
        else
        {
          if ( *((_BYTE *)&this->m_bWPXS + 8 * v8 + 5040) )
          {
            v36 = (SaleUI_SortData *)&this->m_sort[450][304 * v8 + 4];
            v13 = (int *)(&this->m_bWPXS + 32 * v8 + 1343);
          }
          else
          {
            v36 = (SaleUI_SortData *)&this->m_sort[450][304 * v8 + 4];
            v13 = (int *)(&this->m_bWPXS + 32 * v8 + 1335);
          }
          v14 = (int *)&v32;
          v32 = (unsigned long)*v13;
          v33 = (unsigned long)v13[1];
          v15 = (unsigned long)v13[2];
          v16 = (unsigned long)v13[3];
          v34 = v15;
          v35 = v16;
          LOBYTE(v14) = *((_BYTE *)&this->m_bWPXS + 8 * v8 + 5041);
          (((UIFrameWnd *)(&this->m_bWPXS + 104 * v8 + 2344)))->UIFrameWnd::ProcessTimer((BOOL)v14, 1, 1, v32);
        }
        v18 = *(_DWORD *)&this->remarkbuf[24];
        v17 = v18 + 6 * *(_DWORD *)&this->remarkbuf[20];
        LOBYTE(v18) = *((_BYTE *)&this->m_bWPXS + 8 * v17 + 5038);
        if ( (_BYTE)v18 )
        {
          v36 = (SaleUI_SortData *)&this->m_sort[428][304 * v17];
          v32 = *(&this->m_bWPXS + 32 * v17 + 1327);
          v33 = *(&this->m_bWPXS + 32 * v17 + 1328);
          v34 = *(&this->m_bWPXS + 32 * v17 + 1329);
          v35 = *(&this->m_bWPXS + 32 * v17 + 1330);
          (((UIFrameWnd *)(&this->m_bWPXS + 104 * v17 + 2305)))->UIFrameWnd::ProcessTimer(v18, 1, 1, v32);
        }
        else
        {
          v36 = (SaleUI_SortData *)&this->m_sort[458][304 * v17 + 2];
          v19 = (int *)&v32;
          v32 = *(&this->m_bWPXS + 32 * v17 + 1343);
          v33 = *(&this->m_bWPXS + 32 * v17 + 1344);
          v34 = *(&this->m_bWPXS + 32 * v17 + 1345);
          v35 = *(&this->m_bWPXS + 32 * v17 + 1346);
          LOBYTE(v19) = *((_BYTE *)&this->m_bWPXS + 8 * v17 + 5042);
          (((UIFrameWnd *)(&this->m_bWPXS + 104 * v17 + 2357)))->UIFrameWnd::ProcessTimer((BOOL)v19, 1, 1, v32);
        }
        v21 = *(_DWORD *)&this->remarkbuf[24];
        v20 = v21 + 6 * *(_DWORD *)&this->remarkbuf[20];
        LOBYTE(v21) = *((_BYTE *)&this->m_bWPXS + 8 * v20 + 5039);
        if ( (_BYTE)v21 )
        {
          if ( *((_BYTE *)&this->m_bWPXS + 8 * v20 + 5038) )
          {
            v36 = (SaleUI_SortData *)&this->m_sort[435][304 * v20 + 3];
            v22 = (int *)(&this->m_bWPXS + 32 * v20 + 1319);
          }
          else
          {
            v36 = (SaleUI_SortData *)&this->m_sort[435][304 * v20 + 3];
            v22 = (int *)(&this->m_bWPXS + 32 * v20 + 1327);
          }
          v32 = (unsigned long)*v22;
          v33 = (unsigned long)v22[1];
          v23 = (unsigned long)v22[2];
          v24 = (unsigned long)v22[3];
          v34 = v23;
          v35 = v24;
          (((UIFrameWnd *)(&this->m_bWPXS + 104 * v20 + 2318)))->UIFrameWnd::ProcessTimer(v21, 1, 1, v32);
        }
        else
        {
          if ( *((_BYTE *)&this->m_bWPXS + 8 * v20 + 5042) )
          {
            v36 = (SaleUI_SortData *)&this->m_sort[466][304 * v20];
            v25 = (int *)(&this->m_bWPXS + 32 * v20 + 1335);
          }
          else
          {
            v36 = (SaleUI_SortData *)&this->m_sort[466][304 * v20];
            v25 = (int *)(&this->m_bWPXS + 32 * v20 + 1343);
          }
          v26 = (int *)&v32;
          v32 = (unsigned long)*v25;
          v33 = (unsigned long)v25[1];
          v27 = (unsigned long)v25[2];
          v28 = (unsigned long)v25[3];
          v34 = v27;
          v35 = v28;
          LOBYTE(v26) = *((_BYTE *)&this->m_bWPXS + 8 * v20 + 5043);
          (((UIFrameWnd *)(&this->m_bWPXS + 104 * v20 + 2370)))->UIFrameWnd::ProcessTimer((BOOL)v26, 1, 1, v32);
        }
        v29 = *(_DWORD *)&this->remarkbuf[24] + 1;
        *(_DWORD *)&this->remarkbuf[24] = v29;
      }
      while ( v29 < 6 );
    }
    v30 = *(_DWORD *)&this->remarkbuf[20] + 1;
    *(_DWORD *)&this->remarkbuf[20] = v30;
  }
  while ( v30 < 5 );
  (((SceneObj *)this))->SceneObj::Update(deltatime, haveinput) /* [ROWTABLE] */;
  return 1;
}

// 0x0046B4B0
int SaleUI::OnMessage(int nVal, char *pszBuf, int nVal2)
{
  SaleUI_SortData *v5; // edi
  int v6; // eax
  float m_fadespeed; // edx
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
  _DWORD *v19; // eax
  int v20; // eax
  _DWORD *v21; // ecx
  int v22; // eax
  CScreenMode *v23; // eax
  LONG v24; // eax
  int v25; // eax
  int *v26; // ecx
  int v27; // edx
  int v28; // eax
  CScreenMode *v29; // eax
  LONG v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // edi
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int *v37; // ecx
  int v38; // edx
  int v39; // eax
  int v40; // eax
  int *v41; // eax
  int v42; // eax
  const char *v43; // ebp
  int v44; // eax
  const char *v45; // ebp
  const char *v46; // edx
  int *v47; // eax
  int v48; // ebx
  int v49; // ebp
  gbTexture *v50; // eax
  gbTexture **p_m_pbk2; // edi
  unsigned int v52; // ebp
  gbTexture *v53; // ebx
  gbTexture *v54; // edx
  gbTexture *v55; // ecx
  unsigned int Color; // edx
  gbTexture *v57; // eax
  gbTexture *v58; // ecx
  char *v59; // edx
  gbTexture *v60; // edx
  char *v61; // eax
  int v62; // eax
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // eax
  int v67; // edx
  signed int v68; // ecx
  int v69; // eax
  int v70; // eax
  int v71; // eax
  const char *v72; // [esp-0x8] [ebp-0x128]
  const char *v73; // [esp-0x8] [ebp-0x128]
  const char *v74; // [esp-0x8] [ebp-0x128]
  const char *v75; // [esp-0x8] [ebp-0x128]
  const char *v76; // [esp-0x8] [ebp-0x128]
  const char *v77; // [esp-0x8] [ebp-0x128]
  const char *v78; // [esp-0x8] [ebp-0x128]
  const char *v79; // [esp-0x8] [ebp-0x128]
  const char *v80; // [esp-0x8] [ebp-0x128]
  char *v81; // [esp-0x8] [ebp-0x128]
  char *v82; // [esp-0x8] [ebp-0x128]
  int v83; // [esp-0x4] [ebp-0x124]
  int v84; // [esp+0x0] [ebp-0x120]
  gbColorQuad v85; // [esp+0x10] [ebp-0x110] BYREF
  gbColorQuad v86; // [esp+0x14] [ebp-0x10C] BYREF
  int pOut; // [esp+0x18] [ebp-0x108] BYREF
  char Buffer[253]; // [esp+0x20] [ebp-0x100] BYREF
  __int16 v89; // [esp+0x11D] [ebp-0x3]
  char v90; // [esp+0x11F] [ebp-0x1]

  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        if ( *(_DWORD *)&this->remarkbuf[4] )
        {
          operator delete(*(void **)&this->remarkbuf[4]);
          *(_DWORD *)&this->remarkbuf[4] = 0;
        }
        *(_DWORD *)&this->remarkbuf[4] = (unsigned long)operator new(4 * *(&this->dwWeaponWU + 3264));
        if ( this->m_ListSaleTitle.m_childs.m_needscriptdel )
        {
          operator delete((void *)this->m_ListSaleTitle.m_childs.m_needscriptdel);
          this->m_ListSaleTitle.m_childs.m_needscriptdel = 0;
        }
        this->m_ListSaleTitle.m_childs.m_needscriptdel = (int)operator new(4 * *(&this->dwWeaponWU + 3264));
        if ( this->m_ListEquipTitleRc.bottom )
        {
          operator delete((void *)this->m_ListEquipTitleRc.bottom);
          this->m_ListEquipTitleRc.bottom = 0;
        }
        this->m_ListEquipTitleRc.bottom = (LONG)operator new(4 * *(&this->dwWeaponWU + 3264));
        memset(*(void **)&this->remarkbuf[4], 0, 4 * *(&this->dwWeaponWU + 3264));
        memset((void *)this->m_ListSaleTitle.m_childs.m_needscriptdel, 0, 4 * *(&this->dwWeaponWU + 3264));
        memset((void *)this->m_ListEquipTitleRc.bottom, 0, 4 * *(&this->dwWeaponWU + 3264));
        (((UIPushButton *)&this->m_ListGrid[1].m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Equip_word.tga", *(unsigned __int8 *)(*(&this->AttackNum + 289) + 3284));
        (*(void ( **)(float *, int))LODWORD(this->m_Icon[2][1].m_fadespeed))(
          &this->m_Icon[2][1].m_fadespeed,
          1);
        if ( g_bListNeedsRefresh )
        {
          SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (int)(1));
          *((_BYTE *)&this->AttackNum + 601) = 1;
          *(&this->AttackNum + 281) = 2;
          *(&this->AttackNum + 279) = 1;
          sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
          (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItem();
          this->SaleUI::SetRange(0);
          this->SaleUI::GetValue(0);
          (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 0);
          (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
            &this->m_ListGrid[14].m_bvisible,
            0);
          sub_445E50((int)&this->ml_TreasureList.m_column[5].head[60]);
          (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
        }
        else
        {
          if ( (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItemData() <= 0 )
          {
            (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(
              &this->m_ListGrid[12].m_rect,
              0);
            (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
              &this->m_ListGrid[14].m_bvisible,
              0);
            v5 = (SaleUI_SortData *)&this->m_sort[361][2];
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
            (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
          }
          else
          {
            (*(void ( **)(SaleUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(this, 1007, 0, 0);
            v5 = (SaleUI_SortData *)&this->m_sort[361][2];
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (int)(1));
          }
          (((UITitle_JDHY *)this))->UITitle_JDHY::LayoutCalcRects() /* [ROWTABLE] */;
          this->SaleUI::SetRange(1u);
          sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
          (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItem();
          *(_DWORD *)this->remarkbuf = 0;
          if ( (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItemData() > 0 )
            (*(void ( **)(SaleUI *, int, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)this) + 24))(
              this,
              1007,
              0,
              *(_DWORD *)this->remarkbuf);
          else
            *(_DWORD *)this->remarkbuf = -1;
          if ( this->remarkbuf[41] )
            sub_445E50((int)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize);
          SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
          v6 = lstrlenA((LPCSTR)&this->m_data + 304);
          m_fadespeed = this->m_Icon[2][1].m_fadespeed;
          if ( v6 > 0 )
          {
            (*(void ( **)(float *, int, int))LODWORD(m_fadespeed))(&this->m_Icon[2][1].m_fadespeed, 1, v84);
            (**(void ( ***)(SaleUI_SortData *, int))v5)((SaleUI_SortData *)(v5), (int)(1));
          }
          else
          {
            (*(void ( **)(float *, _DWORD, int))LODWORD(m_fadespeed))(&this->m_Icon[2][1].m_fadespeed, 0, v84);
            (**(void ( ***)(SaleUI_SortData *, _DWORD))v5)((SaleUI_SortData *)(v5), (_DWORD)(0));
          }
          *((_BYTE *)&this->AttackNum + 600) = 1;
          sub_445E50((int)&this->ml_TreasureList.m_column[5].head[60]);
        }
        BYTE1(this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[6]) = 1;
        LOBYTE(this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[6]) = 1;
        sprintf(this->buf, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
        SetEnable((UICaption *)&this->ml_ResumeList.m_column[4].head[16]);
        (((UICursor *)v8))->UICursor::_todo_541CC0();
        return 1;
      }
      else
      {
        if ( this->m_ListSaleTitle.m_childs.m_needscriptdel )
        {
          operator delete((void *)this->m_ListSaleTitle.m_childs.m_needscriptdel);
          this->m_ListSaleTitle.m_childs.m_needscriptdel = 0;
        }
        if ( this->m_ListEquipTitleRc.bottom )
        {
          operator delete((void *)this->m_ListEquipTitleRc.bottom);
          this->m_ListEquipTitleRc.bottom = 0;
        }
        if ( !*(_DWORD *)&this->remarkbuf[4] )
          return 1;
        operator delete(*(void **)&this->remarkbuf[4]);
        *(_DWORD *)&this->remarkbuf[4] = 0;
        return 1;
      }
    case 1001:
      switch ( (unsigned int)pszBuf )
      {
        case 0x102u:
          this->SaleUI::DestroySubFrames();
          UIFrameWnd_OnPaintUpdate(0);
          v72 = g_pCScreenMode_5B46B4;
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v72, 1);
          return 1;
        case 0x106u:
          if ( (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItemData() > 0 )
          {
            *(&this->AttackNum + 281) = 1;
            *((_BYTE *)&this->AttackNum + 1128) = 0;
            this->SaleUI::UpdateSkillPanel();
            *((_BYTE *)&this->AttackNum + 1114) = 1;
            this->SaleUI::GetValue(0);
            v73 = g_pCScreenMode_5B46B4;
            v11 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v11))->CScreenMode::AudioSetPosition(v73, 1);
          }
          else
          {
            (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(
              &this->m_ListGrid[12].m_rect,
              0);
            (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
              &this->m_ListGrid[14].m_bvisible,
              0);
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
            (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
          }
          return 1;
        case 0x107u:
          if ( *(&this->AttackNum + 286) <= 0 )
            return 1;
          if ( (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItemData() > 0 )
          {
            *(&this->AttackNum + 281) = -1;
            *(&this->AttackNum + 279) = 0;
            (*(void ( **)(float *, int))LODWORD(this->m_Icon[2][1].m_fadespeed))(
              &this->m_Icon[2][1].m_fadespeed,
              1);
            SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (int)(1));
            *((_BYTE *)&this->AttackNum + 1128) = 1;
            *((_BYTE *)&this->AttackNum + 1114) = 1;
            sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
            this->SaleUI::SetRange(0);
            this->SaleUI::GetValue(0);
            (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(
              &this->m_ListGrid[12].m_rect,
              0);
            (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
              &this->m_ListGrid[14].m_bvisible,
              0);
            (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
            v74 = g_pCScreenMode_5B46B4;
            v12 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v12))->CScreenMode::AudioSetPosition(v74, 1);
          }
          else
          {
            (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(
              &this->m_ListGrid[12].m_rect,
              0);
            (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
              &this->m_ListGrid[14].m_bvisible,
              0);
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
            (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
          }
          return 1;
        case 0x108u:
          if ( (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetItemData() > 0 )
          {
            this->SaleUI::DestroySubFrames();
            (((CCBSystem *)this))->CCBSystem::InitResultWindow();
            if ( this->remarkbuf[41] )
              sub_445E50((int)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize);
            (*(void ( **)(float *, int))LODWORD(this->m_Icon[2][1].m_fadespeed))(
              &this->m_Icon[2][1].m_fadespeed,
              1);
            SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
            sub_445E50((int)&this->m_Icon[2][1].m_fadespeed);
            (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (int)(1));
            *((_BYTE *)&this->AttackNum + 600) = 1;
            goto LABEL_53;
          }
          (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 0);
          (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
            &this->m_ListGrid[14].m_bvisible,
            0);
          (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
          (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
          return 1;
        case 0x111u:
          this->SaleUI::InitMode(0);
          v75 = g_pCScreenMode_5B46B4;
          v13 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v13))->CScreenMode::AudioSetPosition(v75, 1);
          return 1;
        case 0x112u:
          this->SaleUI::InitMode(1);
          v76 = g_pCScreenMode_5B46B4;
          v14 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v14))->CScreenMode::AudioSetPosition(v76, 1);
          return 1;
        case 0x113u:
          this->SaleUI::InitMode(2);
          goto LABEL_53;
        case 0x114u:
          this->SaleUI::InitMode(3);
          v77 = g_pCScreenMode_5B46B4;
          v15 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v15))->CScreenMode::AudioSetPosition(v77, 1);
          return 1;
        case 0x115u:
          this->SaleUI::InitMode(4);
          v78 = g_pCScreenMode_5B46B4;
          v16 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v16))->CScreenMode::AudioSetPosition(v78, 1);
          return 1;
        case 0x129u:
          LOBYTE(this->m_ListSaleTitle.m_rect.left) = 1;
          *((_BYTE *)&this->AttackNum + 1114) = 0;
          this->SaleUI::GetValue(0);
          (((CCBSystem *)this))->CCBSystem::ProcessSlotResults(*(_DWORD *)this->remarkbuf);
          SaleUI_SetSelectionFlags(*(_DWORD *)this->remarkbuf);
          v79 = g_pCScreenMode_5B46B4;
          v17 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v17))->CScreenMode::AudioSetPosition(v79, 1);
          return 1;
        case 0x130u:
          this->SaleUI::GetValue(0);
          LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
LABEL_53:
          v80 = g_pCScreenMode_5B46B4;
          v18 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v18))->CScreenMode::AudioSetPosition(v80, 1);
          return 1;
        case 0x195u:
          this->SaleUI::SendInputToRole(0);
          v19 = (_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)this->remarkbuf);
          ++*v19;
          ++*(_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *(_DWORD *)this->remarkbuf);
          v20 = 4 * *(_DWORD *)this->remarkbuf;
          v21 = (_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + v20);
          v22 = *(_DWORD *)(v20 + *(_DWORD *)((UIWnd *)&this->m_Icon[0][0]));
          if ( *v21 < v22 )
          {
            sub_445E50((int)&this->m_ListGrid[12].m_rect);
            sub_445E50((int)&this->m_ListGrid[14].m_bvisible);
            v81 = (char *)off_5B46C4;
          }
          else
          {
            *v21 = v22;
            *(_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *(_DWORD *)this->remarkbuf) = *(_DWORD *)(4 * *(_DWORD *)this->remarkbuf + *(_DWORD *)((UIWnd *)&this->m_Icon[0][0]));
            sub_445E50((int)&this->m_ListGrid[12].m_rect);
            sub_445E50((int)&this->m_ListGrid[14].m_bvisible);
            sprintf(this->buf, "\\n      %s", (const char *)&dword_DCCC3C);
            SetEnable((UICaption *)&this->m_Icon[0][4].m_benable);
            (((UIRoleSelect *)&this->m_Icon[0][1].m_FVF))->UIRoleSelect::SetByte(1);
            v81 = off_5B46C0[0];
          }
          v23 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v23))->CScreenMode::AudioSetPosition(v81, 1);
          sprintf(this->buf, (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)this->remarkbuf));
          (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)this->remarkbuf, this->buf, 0);
          v24 = *(_DWORD *)this->remarkbuf;
          if ( *(int *)(*(_DWORD *)&this->remarkbuf[4] + 4 * v24) <= 0 )
          {
            if ( v24 < 0 || v24 >= this->m_ListGrid[7].m_rect.right )
              v25 = 0;
            else
              v25 = *(_DWORD *)(this->m_ListGrid[7].m_rect.top + 4 * v24);
            *(_DWORD *)(v25 + 68)  = (unsigned long)(this->m_ListGrid[3].m_disablepicInfo);
          }
          else
          {
            UITabCtrl_SetItemParam(*(_DWORD *)this->remarkbuf);
          }
          v26 = (int *)(*(int **)&this->remarkbuf[4]);
          *(_DWORD *)&this->remarkbuf[16] = (unsigned long)(*v26 * *(_DWORD *)(*(&this->dwWeaponWU + 3666) + 608));
          *(&this->AttackNum + 286) = *v26;
          v27 = *(&this->dwWeaponWU + 3264);
          *(_DWORD *)&this->remarkbuf[20] = 1;
          if ( v27 > 1 )
          {
            do
            {
              v28 = *(_DWORD *)&this->remarkbuf[20];
              *(_DWORD *)&this->remarkbuf[16] += (unsigned long)(v26[v28] * *(_DWORD *)(*(&this->dwWeaponWU + v28 + 3666) + 608));
              *(&this->AttackNum + 286) += v26[v28++];
              *(_DWORD *)&this->remarkbuf[20] = v28;
            }
            while ( v28 < v27 );
          }
          sprintf(this->buf, "%s %d", g_szCombatFieldName, *(_DWORD *)&this->remarkbuf[16]);
          SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
          if ( *(int *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)this->remarkbuf) > 0 )
          {
            LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
            SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
            this->SaleUI::GetValue(1u);
          }
          if ( *(int *)&this->remarkbuf[16] > 0 && !this->remarkbuf[41] )
            return 1;
          sub_445E50((int)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize);
          return 1;
        case 0x196u:
          this->SaleUI::SendInputToRole(0);
          --*(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)this->remarkbuf);
          --*(_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *(_DWORD *)this->remarkbuf);
          if ( *(int *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)this->remarkbuf) > 0 )
          {
            sub_445E50((int)&this->m_ListGrid[12].m_rect);
            sub_445E50((int)&this->m_ListGrid[14].m_bvisible);
            v82 = (char *)off_5B46C4;
          }
          else
          {
            (((CCBSystem *)this))->CCBSystem::InitResultWindow();
            *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)this->remarkbuf) = 0;
            *(_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *(_DWORD *)this->remarkbuf) = 0;
            sub_445E50((int)&this->m_ListGrid[12].m_rect);
            sub_445E50((int)&this->m_ListGrid[14].m_bvisible);
            this->SaleUI::GetValue(0);
            v82 = off_5B46C0[0];
          }
          v29 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v29))->CScreenMode::AudioSetPosition(v82, 1);
          sprintf(this->buf, (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)this->remarkbuf));
          (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)this->remarkbuf, this->buf, 0);
          v30 = *(_DWORD *)this->remarkbuf;
          if ( *(int *)(*(_DWORD *)&this->remarkbuf[4] + 4 * v30) <= 0 )
          {
            if ( v30 < 0 || v30 >= this->m_ListGrid[7].m_rect.right )
              v31 = 0;
            else
              v31 = *(_DWORD *)(this->m_ListGrid[7].m_rect.top + 4 * v30);
            *(_DWORD *)(v31 + 68)  = (unsigned long)(this->m_ListGrid[3].m_disablepicInfo);
          }
          else
          {
            UITabCtrl_SetItemParam(*(_DWORD *)this->remarkbuf);
          }
          if ( *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)this->remarkbuf) >= *(_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * *(_DWORD *)this->remarkbuf) )
            goto LABEL_94;
          *(_DWORD *)&this->remarkbuf[20] = 0;
          break;
        default:
          return 1;
      }
      while ( 1 )
      {
        v32 = *(_DWORD *)&this->remarkbuf[20];
        if ( this->m_sort[412][2]._tail_000[v32] )
        {
          v33 = *(_DWORD *)this->remarkbuf;
          *(_DWORD *)&this->remarkbuf[24] = 0;
          while ( 1 )
          {
            v34 = *(_DWORD *)&this->remarkbuf[24];
            if ( *(&this->m_ListSaleTitle.m_bcreateok + 6 * v32 + v34) == v33 )
              break;
            v35 = v34 + 1;
            *(_DWORD *)&this->remarkbuf[24] = v35;
            if ( v35 >= 6 )
              goto LABEL_90;
          }
          this->SaleUI::Update(v32, *(_DWORD *)&this->remarkbuf[24]);
          this->SaleUI::GetValue(0);
          LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
          *(_DWORD *)&this->remarkbuf[28] = 1;
LABEL_90:
          if ( *(_DWORD *)&this->remarkbuf[28] == 1 )
            break;
        }
        v36 = *(_DWORD *)&this->remarkbuf[20] + 1;
        *(_DWORD *)&this->remarkbuf[20] = v36;
        if ( v36 >= 5 )
          goto LABEL_94;
      }
      *(_DWORD *)&this->remarkbuf[28] = 0;
LABEL_94:
      v37 = (int *)(*(int **)&this->remarkbuf[4]);
      *(_DWORD *)&this->remarkbuf[16] = (unsigned long)(*v37 * *(_DWORD *)(*(&this->dwWeaponWU + 3666) + 608));
      *(&this->AttackNum + 286) = *v37;
      v38 = *(&this->dwWeaponWU + 3264);
      *(_DWORD *)&this->remarkbuf[20] = 1;
      if ( v38 > 1 )
      {
        do
        {
          v39 = *(_DWORD *)&this->remarkbuf[20];
          *(_DWORD *)&this->remarkbuf[16] += (unsigned long)(v37[v39] * *(_DWORD *)(*(&this->dwWeaponWU + v39 + 3666) + 608));
          *(&this->AttackNum + 286) += v37[v39++];
          *(_DWORD *)&this->remarkbuf[20] = v39;
        }
        while ( v39 < v38 );
      }
      sprintf(this->buf, "%s %d", g_szCombatFieldName, *(_DWORD *)&this->remarkbuf[16]);
      SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
      if ( *(int *)&this->remarkbuf[16] > 0 )
      {
        if ( this->remarkbuf[41] )
          sub_445E50((int)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize);
        return 1;
      }
      else
      {
        sub_445E50((int)&this->ml_TreasureList.m_scrollbar.m_bk.m_childs.m_nSize);
        return 1;
      }
    case 1002:
      switch ( (unsigned int)pszBuf )
      {
        case 0x111u:
          sprintf(
            this->buf,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)*(int *)&this->remarkbuf[16] * 0.5));
          goto LABEL_216;
        case 0x112u:
          sprintf(
            this->buf,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)*(int *)&this->remarkbuf[16] * 0.60000002));
          goto LABEL_216;
        case 0x113u:
          sprintf(
            this->buf,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)*(int *)&this->remarkbuf[16] * 0.69999999));
          goto LABEL_216;
        case 0x114u:
          sprintf(
            this->buf,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)*(int *)&this->remarkbuf[16] * 0.80000001));
          goto LABEL_216;
        case 0x115u:
          sprintf(
            this->buf,
            "%s %d",
            g_szCombatFieldName,
            (unsigned int)(__int64)((double)*(int *)&this->remarkbuf[16] * 0.89999998));
          goto LABEL_216;
        default:
          return 1;
      }
      return 1;
    case 1003:
      if ( (unsigned int)pszBuf >= 0x111 && (unsigned int)pszBuf <= 0x115 )
      {
        sprintf(this->buf, "%s %d", g_szCombatFieldName, *(_DWORD *)&this->remarkbuf[16]);
LABEL_216:
        SetEnable((UICaption *)&this->ml_ResumeList.m_column[6].head[16]);
      }
      return 1;
    case 1005:
      (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 0);
      (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
        &this->m_ListGrid[14].m_bvisible,
        0);
      (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
      return 1;
    case 1007:
      *(_DWORD *)this->remarkbuf = nVal2;
      if ( nVal2 > -1 )
      {
        if ( *(int *)(*(_DWORD *)&this->remarkbuf[4] + 4 * nVal2) <= 0
          || *(int *)(this->m_ListEquipTitleRc.bottom + 4 * nVal2) > 0 )
        {
          this->SaleUI::GetValue(0);
        }
        else
        {
          LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
          SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
          (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
          this->SaleUI::GetValue(1u);
        }
        SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
        (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
        this->SaleUI::CreatePanelElements(*(CCBUIPanel **)this->remarkbuf);
        this->SaleUI::SetupPlayerDisplay(*(_DWORD *)this->remarkbuf);
        (((CCBSystem *)this))->CCBSystem::InitResultWindow();
        v40 = *(unsigned __int8 *)(*(&this->dwWeaponWU + *(_DWORD *)this->remarkbuf + 3666) + 612) - 7;
        switch ( *(_BYTE *)(*(&this->dwWeaponWU + *(_DWORD *)this->remarkbuf + 3666) + 612) )
        {
          case 7:
            LOBYTE(v40) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
            (((UIPushButton *)&this->m_ListGrid[1].m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\fj_word.tga", v40);
            break;
          case 8:
            LOBYTE(v40) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
            (((UIPushButton *)&this->m_ListGrid[1].m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\tb_word.tga", v40);
            break;
          case 9:
            LOBYTE(v40) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
            (((UIPushButton *)&this->m_ListGrid[1].m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\jb_word.tga", v40);
            break;
          case 0xA:
            LOBYTE(v40) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
            (((UIPushButton *)&this->m_ListGrid[1].m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Adorn_word.tga", v40);
            break;
          case 0xB:
            LOBYTE(v40) = *(_BYTE *)(*(&this->AttackNum + 289) + 3284);
            (((UIPushButton *)&this->m_ListGrid[1].m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\wq_word.tga", v40);
            break;
          default:
            break;
        }
        v41 = (int *)*(&this->dwWeaponWU + *(_DWORD *)this->remarkbuf + 3666);
        if ( *((_BYTE *)v41 + 613) == 5 )
        {
          (((CCBFiveNimbusWindow *)&this->m_Icon[0][0].m_rect))->CCBFiveNimbusWindow::SetFloatParam(228.0);
          (((Camera *)&this->m_Icon[0][0].m_rect))->Camera::UpdateCameraLookAt(330, 280, 600);
        }
        else if ( *((_BYTE *)v41 + 612) == 11 )
        {
          (((CCBFiveNimbusWindow *)&this->m_Icon[0][0].m_rect))->CCBFiveNimbusWindow::SetFloatParam(228.0);
          (((Camera *)&this->m_Icon[0][0].m_rect))->Camera::UpdateCameraLookAt(330, 272, 600);
        }
        else
        {
          v42 = (unsigned long)*v41;
          if ( v42 == 8114 || v42 == 8132 )
          {
            (((CCBFiveNimbusWindow *)&this->m_Icon[0][0].m_rect))->CCBFiveNimbusWindow::SetFloatParam(180.0);
            (((Camera *)&this->m_Icon[0][0].m_rect))->Camera::UpdateCameraLookAt(330, 252, 600);
          }
          else
          {
            (((CCBFiveNimbusWindow *)&this->m_Icon[0][0].m_rect))->CCBFiveNimbusWindow::SetFloatParam(180.0);
            (((Camera *)&this->m_Icon[0][0].m_rect))->Camera::UpdateCameraLookAt(330, 268, 600);
          }
        }
        if ( !strcmp((const char *)(*(&this->dwWeaponWU + *(_DWORD *)this->remarkbuf + 3666) + 36), unk_C10D38) )
        {
          sprintf(this->buf, "%s", "NONE");
        }
        else
        {
          v43 = (const char *)(*(&this->dwWeaponWU + *(_DWORD *)this->remarkbuf + 3666) + 36);
          sprintf(this->buf, "Item\\%s\\%s.pol", v43, v43);
        }
        (((PalScript *)&this->m_Icon[0][0].m_texty))->PalScript::LoadModel(this->buf, 0);
        v44 = *(&this->dwWeaponWU + *(_DWORD *)this->remarkbuf + 3666);
        v45 = (const char *)(v44 + 36);
        v46 = (const char *)(v44 + 66);
        if ( !strcmp((const char *)(v44 + 36), unk_C10D38) )
        {
          sprintf(this->buf, "%s", "NONE");
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v89 = 0;
          v90 = 0;
          sprintf(Buffer, "%s%s", v45, v46);
          sprintf(this->buf, "Item\\%s\\%s.tga", v45, Buffer);
        }
        (((gbGeomNode *)*(gbGeomNode **)&this->m_Icon[0][0].m_text[8]))->gbGeomNode::ReplaceTexture(this->buf);
        v83 = *(_DWORD *)this->remarkbuf;
        this->m_Icon[0][0].m_fonttype = (Parent_Data *)1;
        (((UIListBox *)&this->m_ListGrid[3].m_disablepic))->UIListBox::GetGridOffset(&pOut, v83);
        v48 = (unsigned long)*v47;
        v49 = (unsigned long)v47[1];
        *(&this->AttackNum + 108) = *v47 + 90;
        *(&this->AttackNum + 109) = v49;
        *(&this->AttackNum + 110) = v48 + 180;
        *(&this->AttackNum + 111) = v49 + 32;
        (((UIWnd *)(&this->AttackNum + 112)))->UIWnd::sub_445FA0(&this->AttackNum + 108);
        sprintf(
          this->buf,
          "%s:%d",
          (const char *)&g_bSaveFlag,
          99 - *(_DWORD *)(*(_DWORD *)((UIWnd *)&this->m_Icon[0][0]) + 4 * *(_DWORD *)this->remarkbuf));
        SetEnable((UICaption *)(&this->AttackNum + 112));
        (**((void ( ***)(int *, int))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (int)(1));
        v50 = (gbTexture *)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[2];
        p_m_pbk2 = (gbTexture **)&this->m_ListGrid[11].m_pbk2;
        v52 = v49 - 4;
        v53 = (gbTexture *)(v48 + 200);
        if ( v50 )
        {
          if ( v50 == (gbTexture *)1 )
          {
            v54 = (gbTexture *)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[1];
            this->m_ListGrid[12].m_wndcolor.Color = (unsigned int)v53
                                                  + (unsigned int)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[0];
            this->m_ListGrid[12].m_fontcolor.Color = v52;
            *(_DWORD *)((UIWnd *)&this->m_ListGrid[12]) = (_DWORD)v53;
            this->m_ListGrid[12].m_id = (unsigned int)v54 + v52;
            (((UIWnd *)&this->m_ListGrid[14].m_bvisible))->UIWnd::sub_445FA0(&this->m_ListGrid[12]);
            v55 = (gbTexture *)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[3];
            Color = this->m_ListGrid[12].m_wndcolor.Color;
            *(_DWORD *)&this->m_ListGrid[11].m_mouseoff = this->m_ListGrid[12].m_fontcolor.Color;
            v57 = (gbTexture *)((char *)v55 + Color);
            v58 = (gbTexture *)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[0];
            *p_m_pbk2 = v57;
            this->m_ListGrid[11].m_FVF = (int)v57 + (_DWORD)v58;
            this->m_ListGrid[11].m_nTextW = this->m_ListGrid[12].m_id;
            (((UIWnd *)&this->m_ListGrid[12].m_rect))->UIWnd::sub_445FA0(&this->m_ListGrid[11].m_pbk2);
          }
        }
        else
        {
          v59 = (char *)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[1] + v52;
          this->m_ListGrid[11].m_FVF = (int)v53
                                     + (unsigned int)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[0];
          *(_DWORD *)&this->m_ListGrid[11].m_mouseoff = v52;
          *p_m_pbk2 = v53;
          this->m_ListGrid[11].m_nTextW = (int)v59;
          (((UIWnd *)&this->m_ListGrid[12].m_rect))->UIWnd::sub_445FA0(&this->m_ListGrid[11].m_pbk2);
          v60 = (gbTexture *)*p_m_pbk2;
          v61 = (char *)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[3] + this->m_ListGrid[11].m_nTextW;
          this->m_ListGrid[12].m_fontcolor.Color = (unsigned int)v61;
          *(_DWORD *)((UIWnd *)&this->m_ListGrid[12]) = (_DWORD)v60;
          this->m_ListGrid[12].m_wndcolor.Color = this->m_ListGrid[11].m_FVF;
          this->m_ListGrid[12].m_id = (unsigned int)this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[1]
                                    + (unsigned int)v61;
          (((UIWnd *)&this->m_ListGrid[14].m_bvisible))->UIWnd::sub_445FA0(&this->m_ListGrid[12]);
        }
        (*(void ( **)(tagRECT *, int))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 1);
        (*(void ( **)(int *, int))this->m_ListGrid[14].m_bvisible)(
          &this->m_ListGrid[14].m_bvisible,
          1);
        sub_445E50((int)&this->m_ListGrid[12].m_rect);
        sub_445E50((int)&this->m_ListGrid[14].m_bvisible);
        return 1;
      }
      *(_DWORD *)&this->remarkbuf[20] = 0;
      do
      {
        if ( this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
        {
          *(_DWORD *)&this->remarkbuf[24] = 0;
          do
          {
            (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20]
                                                                              + 277][45
                                                                                   * *(_DWORD *)&this->remarkbuf[24]
                                                                                   + 4])(
              &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4],
              0);
            *(_DWORD *)&this->remarkbuf[28] = 0;
            do
            {
              (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[412][1824
                                                                                    * *(_DWORD *)&this->remarkbuf[20]
                                                                                    + 4
                                                                                    + 304
                                                                                    * *(_DWORD *)&this->remarkbuf[24]
                                                                                    + 38
                                                                                    * *(_DWORD *)&this->remarkbuf[28]])((SaleUI_SortData *)(&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                                 + 4
                                 + 304 * *(_DWORD *)&this->remarkbuf[24]
                                 + 38 * *(_DWORD *)&this->remarkbuf[28]]), (_DWORD)(0));
              v62 = *(_DWORD *)&this->remarkbuf[28] + 1;
              *(_DWORD *)&this->remarkbuf[28] = v62;
            }
            while ( v62 < 8 );
            v63 = *(_DWORD *)&this->remarkbuf[24] + 1;
            *(_DWORD *)&this->remarkbuf[24] = v63;
          }
          while ( v63 < 6 );
        }
        v64 = *(_DWORD *)&this->remarkbuf[20] + 1;
        *(_DWORD *)&this->remarkbuf[20] = v64;
      }
      while ( v64 < 5 );
      SetEnable((UICaption *)&this->ml_ResumeList.m_column[0].head[16]);
      this->m_Icon[0][0].m_fonttype = ((Parent_Data *)0);
      (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 0);
      (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
        &this->m_ListGrid[14].m_bvisible,
        0);
      (**((void ( ***)(int *, _DWORD))&this->AttackNum + 112))((int *)(&this->AttackNum + 112), (_DWORD)(0));
      return this->UIWnd::OnMessage(nVal, (int)pszBuf, nVal2);
    case 1009:
      if ( *((_BYTE *)&this->AttackNum + 1114) )
        goto LABEL_159;
      *(_DWORD *)&this->remarkbuf[20] = 0;
      while ( 2 )
      {
        v65 = *(_DWORD *)&this->remarkbuf[20];
        if ( !this->m_sort[412][2]._tail_000[v65] )
          goto LABEL_150;
        if ( pszBuf == (char *)*(&dword_56B4DC + v65) )
        {
          this->SaleUI::HandleInput(*(_DWORD *)&this->remarkbuf[20], 0, *(_DWORD *)this->remarkbuf);
        }
        else if ( pszBuf == (char *)*(&dword_56B4F0 + v65) )
        {
          this->SaleUI::HandleInput(*(_DWORD *)&this->remarkbuf[20], 3, *(_DWORD *)this->remarkbuf);
        }
        else if ( pszBuf == (&off_56B504)[v65] )
        {
          this->SaleUI::HandleInput(*(_DWORD *)&this->remarkbuf[20], 4, *(_DWORD *)this->remarkbuf);
        }
        else if ( pszBuf == (&off_56B518)[v65] )
        {
          this->SaleUI::HandleInput(*(_DWORD *)&this->remarkbuf[20], 2, *(_DWORD *)this->remarkbuf);
        }
        else if ( pszBuf == (&off_56B52C)[v65] )
        {
          this->SaleUI::HandleInput(*(_DWORD *)&this->remarkbuf[20], 5, *(_DWORD *)this->remarkbuf);
        }
        else
        {
          if ( pszBuf != (char *)*(&dword_56B540 + v65) )
          {
LABEL_150:
            v66 = v65 + 1;
            *(_DWORD *)&this->remarkbuf[20] = v66;
            if ( v66 >= 5 )
              goto LABEL_159;
            continue;
          }
          this->SaleUI::HandleInput(*(_DWORD *)&this->remarkbuf[20], 1, *(_DWORD *)this->remarkbuf);
        }
        break;
      }
      HIBYTE(this->m_ListSaleTitle.m_childs.m_nSize) = 1;
LABEL_159:
      if ( HIBYTE(this->m_ListSaleTitle.m_childs.m_nSize) )
      {
        HIBYTE(this->m_ListSaleTitle.m_childs.m_nSize) = 0;
        return 1;
      }
      if ( pszBuf != (char *)265 )
        return 1;
      v67 = *(_DWORD *)&this->m_Icon[2][2].m_mouseoff;
      v68 = HIWORD(nVal2);
      *(_DWORD *)&this->remarkbuf[8] = (unsigned __int16)nVal2;
      *(_DWORD *)&this->remarkbuf[12] = HIWORD(nVal2);
      if ( (unsigned __int16)nVal2 <= v67
        || (unsigned __int16)nVal2 >= this->m_Icon[2][2].m_nTextW
        || v68 <= this->m_Icon[2][2].m_FVF
        || v68 >= (int)this->m_Icon[2][2].m_color.Color )
      {
        return 1;
      }
      if ( *((_BYTE *)&this->AttackNum + 1128) )
      {
        if ( *(&this->AttackNum + 279) < 1 )
        {
          (*(void ( **)(float *, int))LODWORD(this->m_Icon[2][1].m_fadespeed))(
            &this->m_Icon[2][1].m_fadespeed,
            1);
          ++*(&this->AttackNum + 279);
          SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
          (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (int)(1));
        }
        else
        {
          this->SaleUI::SetValue(1u);
          *((_BYTE *)&this->AttackNum + 1128) = 0;
          *(&this->AttackNum + 279) = 0;
          SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
          (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
        }
        return 1;
      }
      break;
    case 1010:
      if ( *((_BYTE *)&this->AttackNum + 1114) )
        goto LABEL_205;
      *(_DWORD *)&this->remarkbuf[20] = 0;
      while ( 2 )
      {
        v70 = *(_DWORD *)&this->remarkbuf[20];
        if ( !this->m_sort[412][2]._tail_000[v70] )
          goto LABEL_196;
        if ( pszBuf == (char *)*(&dword_56B554 + v70) )
        {
          this->SaleUI::Update(*(_DWORD *)&this->remarkbuf[20], 0);
        }
        else if ( pszBuf == (char *)*(&dword_56B568 + v70) )
        {
          this->SaleUI::Update(*(_DWORD *)&this->remarkbuf[20], 3);
        }
        else if ( pszBuf == (char *)*(&dword_56B57C + v70) )
        {
          this->SaleUI::Update(*(_DWORD *)&this->remarkbuf[20], 4);
        }
        else if ( pszBuf == (char *)*(&dword_56B590 + v70) )
        {
          this->SaleUI::Update(*(_DWORD *)&this->remarkbuf[20], 2);
        }
        else if ( pszBuf == (char *)*(&dword_56B5A4 + v70) )
        {
          this->SaleUI::Update(*(_DWORD *)&this->remarkbuf[20], 5);
        }
        else
        {
          if ( pszBuf != (char *)*(&dword_56B5B8 + v70) )
          {
LABEL_196:
            v71 = v70 + 1;
            *(_DWORD *)&this->remarkbuf[20] = v71;
            if ( v71 >= 5 )
              goto LABEL_205;
            continue;
          }
          this->SaleUI::Update(*(_DWORD *)&this->remarkbuf[20], 1);
        }
        break;
      }
      HIBYTE(this->m_ListSaleTitle.m_childs.m_nSize) = 1;
LABEL_205:
      if ( !HIBYTE(this->m_ListSaleTitle.m_childs.m_nSize) )
        return 1;
      HIBYTE(this->m_ListSaleTitle.m_childs.m_nSize) = 0;
      return this->UIWnd::OnMessage(nVal, (int)pszBuf, nVal2);
    default:
      return this->UIWnd::OnMessage(nVal, (int)pszBuf, nVal2);
  }
  switch ( *(&this->AttackNum + 281) )
  {
    case 0:
      this->SaleUI::SetValue(1u);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_Icon[2][1].m_fadespeed))(
        &this->m_Icon[2][1].m_fadespeed,
        0);
      SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
      (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
      *(&this->AttackNum + 279) = 0;
      goto LABEL_184;
    case 1:
      if ( *((_BYTE *)&this->AttackNum + 601) )
      {
        (*(void ( **)(float *, int))LODWORD(this->m_Icon[2][1].m_fadespeed))(
          &this->m_Icon[2][1].m_fadespeed,
          1);
        SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
        (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
        *(&this->AttackNum + 279) = 0;
        this->SaleUI::SetValue(0);
        this->SaleUI::SetRange(1u);
        sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
        this->SaleUI::DestroySubFrames();
        UIFrameWnd_OnPaintUpdate(4);
      }
      else
      {
        this->SaleUI::SetValue(0);
        this->SaleUI::SetRange(1u);
        sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
        SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
        (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
      }
      goto LABEL_184;
    case 2:
      v69 = *(&this->AttackNum + 279);
      if ( *((_BYTE *)&this->AttackNum + 601) )
      {
        if ( v69 >= 1 )
        {
          *(&this->AttackNum + 279) = 0;
          this->SaleUI::UpdateSkillPanel();
          this->SaleUI::DestroySubFrames();
          UIFrameWnd_OnPaintUpdate(4);
          goto LABEL_184;
        }
        goto LABEL_179;
      }
      if ( v69 < 1 )
      {
LABEL_179:
        *(&this->AttackNum + 279) = v69 + 1;
        SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
        (**(void ( ***)(SaleUI_SortData *, int))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (int)(1));
        goto LABEL_184;
      }
      *(&this->AttackNum + 279) = 0;
      this->SaleUI::SetValue(0);
      this->SaleUI::SetRange(1u);
      sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
LABEL_184:
      if ( *(&this->AttackNum + 281) < 0 && *((_BYTE *)&this->AttackNum + 600) )
      {
        SetEnable((UICaption *)&this->m_Icon[2][1].m_fadespeed);
        (*(void ( **)(float *, _DWORD))LODWORD(this->m_Icon[2][1].m_fadespeed))(
          &this->m_Icon[2][1].m_fadespeed,
          0);
        (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])((SaleUI_SortData *)(&this->m_sort[361][2]), (_DWORD)(0));
        *((_BYTE *)&this->AttackNum + 600) = 0;
        return 1;
      }
      return 1;
    case 3:
      (((PAL3 *)this))->PAL3::EnterGameMode(4);
      goto LABEL_184;
    default:
      goto LABEL_184;
  }
}

// 0x00471220
char SaleUI::ToggleSlot0(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  char *v4; // edi
  int v5; // ebx
  UIWnd *v6; // ebp
  LONG *p_bottom; // edi
  char result; // al
  float m_lastpos; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  v3 = *(void ( ***)(char *, _DWORD))&this->ml_ResumeList.m_column[3].head[20];
  v4 = (char *)&this->ml_ResumeList.m_column[3].head[20];
  LOBYTE(this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex[0]) = pData;
  (*v3)(&this->ml_ResumeList.m_column[3].head[20], pData);
  v5 = 0;
  v6 = (UIWnd *)v4;
  pDataa = 0;
  p_bottom = (LONG *)&this->ml_TreasureList.m_scrollbar.m_bk.m_rect.bottom;
  do
  {
    result = *((_BYTE *)this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex + v5);
    if ( result )
    {
      *p_bottom = pDataa * LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos)
                + (LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos) - this->ml_TreasureList.m_scrollbar.m_pagesize)
                / 2;
      m_lastpos = this->ml_TreasureList.m_scrollbar.m_lastpos;
      *((float *)p_bottom - 1) = m_lastpos;
      p_bottom[1] = LODWORD(m_lastpos) + LODWORD(this->ml_TreasureList.m_scrollbar.m_step);
      p_bottom[2] = this->ml_TreasureList.m_scrollbar.m_pagesize + *p_bottom;
      result = (((UIWnd *)v6))->UIWnd::sub_445FA0(p_bottom - 1);
      ++pDataa;
    }
    ++v5;
    p_bottom += 4;
    v6 = (UIWnd *)((char *)v6 + 152);
  }
  while ( v5 < 5 );
  return result;
}

// 0x004712D0
char SaleUI::ToggleSlot1(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  int v4; // ebx
  UIWnd *v5; // ebp
  LONG *p_bottom; // edi
  char result; // al
  float m_lastpos; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  v3 = *(void ( ***)(char *, _DWORD))&this->ml_ResumeList.m_column[5].head[4];
  BYTE1(this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex[0]) = pData;
  (*v3)(&this->ml_ResumeList.m_column[5].head[4], pData);
  v4 = 0;
  v5 = (UIWnd *)&this->ml_ResumeList.m_column[3].head[20];
  pDataa = 0;
  p_bottom = (LONG *)&this->ml_TreasureList.m_scrollbar.m_bk.m_rect.bottom;
  do
  {
    result = *((_BYTE *)this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex + v4);
    if ( result )
    {
      *p_bottom = pDataa * LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos)
                + (LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos) - this->ml_TreasureList.m_scrollbar.m_pagesize)
                / 2;
      m_lastpos = this->ml_TreasureList.m_scrollbar.m_lastpos;
      *((float *)p_bottom - 1) = m_lastpos;
      p_bottom[1] = LODWORD(m_lastpos) + LODWORD(this->ml_TreasureList.m_scrollbar.m_step);
      p_bottom[2] = this->ml_TreasureList.m_scrollbar.m_pagesize + *p_bottom;
      result = (((UIWnd *)v5))->UIWnd::sub_445FA0(p_bottom - 1);
      ++pDataa;
    }
    ++v4;
    p_bottom += 4;
    v5 = (UIWnd *)((char *)v5 + 152);
  }
  while ( v4 < 5 );
  return result;
}

// 0x00471380
char SaleUI::ToggleSlot2(unsigned __int8 pData)
{
  void ( **m_nSize)(int *, _DWORD); // edx
  int v4; // ebx
  UIWnd *v5; // ebp
  LONG *p_bottom; // edi
  char result; // al
  float m_lastpos; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  m_nSize = (void ( **)(int *, _DWORD))this->ml_ResumeList.m_column[6].items.m_nSize;
  BYTE2(this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex[0]) = pData;
  (*m_nSize)(&this->ml_ResumeList.m_column[6].items.m_nSize, pData);
  v4 = 0;
  v5 = (UIWnd *)&this->ml_ResumeList.m_column[3].head[20];
  pDataa = 0;
  p_bottom = (LONG *)&this->ml_TreasureList.m_scrollbar.m_bk.m_rect.bottom;
  do
  {
    result = *((_BYTE *)this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex + v4);
    if ( result )
    {
      *p_bottom = pDataa * LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos)
                + (LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos) - this->ml_TreasureList.m_scrollbar.m_pagesize)
                / 2;
      m_lastpos = this->ml_TreasureList.m_scrollbar.m_lastpos;
      *((float *)p_bottom - 1) = m_lastpos;
      p_bottom[1] = LODWORD(m_lastpos) + LODWORD(this->ml_TreasureList.m_scrollbar.m_step);
      p_bottom[2] = this->ml_TreasureList.m_scrollbar.m_pagesize + *p_bottom;
      result = (((UIWnd *)v5))->UIWnd::sub_445FA0(p_bottom - 1);
      ++pDataa;
    }
    ++v4;
    p_bottom += 4;
    v5 = (UIWnd *)((char *)v5 + 152);
  }
  while ( v4 < 5 );
  return result;
}

// 0x00471430
char SaleUI::ToggleSlot3(unsigned __int8 pData)
{
  void ( **m_seloffsetL)(int *, _DWORD); // edx
  int v4; // ebx
  UIWnd *v5; // ebp
  LONG *p_bottom; // edi
  char result; // al
  float m_lastpos; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  m_seloffsetL = (void ( **)(int *, _DWORD))this->ml_ResumeList.m_seloffsetL;
  HIBYTE(this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex[0]) = pData;
  (*m_seloffsetL)(&this->ml_ResumeList.m_seloffsetL, pData);
  v4 = 0;
  v5 = (UIWnd *)&this->ml_ResumeList.m_column[3].head[20];
  pDataa = 0;
  p_bottom = (LONG *)&this->ml_TreasureList.m_scrollbar.m_bk.m_rect.bottom;
  do
  {
    result = *((_BYTE *)this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex + v4);
    if ( result )
    {
      *p_bottom = pDataa * LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos)
                + (LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos) - this->ml_TreasureList.m_scrollbar.m_pagesize)
                / 2;
      m_lastpos = this->ml_TreasureList.m_scrollbar.m_lastpos;
      *((float *)p_bottom - 1) = m_lastpos;
      p_bottom[1] = LODWORD(m_lastpos) + LODWORD(this->ml_TreasureList.m_scrollbar.m_step);
      p_bottom[2] = this->ml_TreasureList.m_scrollbar.m_pagesize + *p_bottom;
      result = (((UIWnd *)v5))->UIWnd::sub_445FA0(p_bottom - 1);
      ++pDataa;
    }
    ++v4;
    p_bottom += 4;
    v5 = (UIWnd *)((char *)v5 + 152);
  }
  while ( v4 < 5 );
  return result;
}

// 0x004714E0
char SaleUI::ToggleSlot4(unsigned __int8 pData)
{
  void ( **right)(LONG *, _DWORD); // edx
  int v4; // ebx
  UIWnd *v5; // ebp
  LONG *p_bottom; // edi
  char result; // al
  float m_lastpos; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  right = (void ( **)(LONG *, _DWORD))this->ml_TreasureList.m_rect.right;
  LOBYTE(this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex[1]) = pData;
  (*right)(&this->ml_TreasureList.m_rect.right, pData);
  v4 = 0;
  v5 = (UIWnd *)&this->ml_ResumeList.m_column[3].head[20];
  pDataa = 0;
  p_bottom = (LONG *)&this->ml_TreasureList.m_scrollbar.m_bk.m_rect.bottom;
  do
  {
    result = *((_BYTE *)this->ml_TreasureList.m_scrollbar.m_texarray.m_ptex + v4);
    if ( result )
    {
      *p_bottom = pDataa * LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos)
                + (LODWORD(this->ml_TreasureList.m_scrollbar.m_drawpos) - this->ml_TreasureList.m_scrollbar.m_pagesize)
                / 2;
      m_lastpos = this->ml_TreasureList.m_scrollbar.m_lastpos;
      *((float *)p_bottom - 1) = m_lastpos;
      p_bottom[1] = LODWORD(m_lastpos) + LODWORD(this->ml_TreasureList.m_scrollbar.m_step);
      p_bottom[2] = this->ml_TreasureList.m_scrollbar.m_pagesize + *p_bottom;
      result = (((UIWnd *)v5))->UIWnd::sub_445FA0(p_bottom - 1);
      ++pDataa;
    }
    ++v4;
    p_bottom += 4;
    v5 = (UIWnd *)((char *)v5 + 152);
  }
  while ( v4 < 5 );
  return result;
}

// 0x00525120
int SaleUI::InitUI()
{
  int *v2; // edi
  int v3; // ebp
  int *v4; // edi
  int v5; // ebp
  int result; // eax

  ((UIListBox *)this)->UIListBox::UIListBox();
  *(_DWORD *)&this->buf[8] = 800;
  *(_DWORD *)&this->buf[12] = 600;
  ((UIFrameContainer *)((UIFrameContainer *)&this->dwWeaponWU + 3))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 140)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 178)))->UIFrameContainer::ResetContainerState();
  ((UIPushButton *)(&this->dwWeaponWU + 487))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->dwWeaponWU + 549))->UIPushButton::UIPushButton();
  NameSys::GetSys();
  (((UIProgressBar *)(&this->dwWeaponWU + 697)))->UIProgressBar::ctor();
  (((UIProgressBar *)(&this->dwWeaponWU + 774)))->UIProgressBar::ctor();
  (((UIProgressBar *)(&this->dwWeaponWU + 851)))->UIProgressBar::ctor();
  v2 = (int *)(&this->dwWeaponWU + 928);
  v3 = 2;
  do
  {
    v2 += 3;
    --v3;
  }
  while ( v3 );
  (((UIFrameContainer *)(&this->dwWeaponWU + 934)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 972)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 1010)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 1048)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 1086)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 1124)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 1162)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 1200)))->UIFrameContainer::ResetContainerState();
  *((_BYTE *)&this->dwWeaponWU + 4976) = 0;
  *(&this->dwWeaponWU + 1243) = 0;
  *(&this->dwWeaponWU + 1242) = 0;
  *((_BYTE *)&this->dwWeaponWU + 4988) = 0;
  ctor_17((UIButton *)(&this->dwWeaponWU + 1248));
  (((UITextArea *)(&this->dwWeaponWU + 1313)))->UITextArea::InitAfterClear();
  (((UIFrameContainer *)(&this->dwWeaponWU + 1361)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dwWeaponWU + 1399)))->UIFrameContainer::ResetContainerState();
  v4 = (int *)(&this->dwWeaponWU + 1439);
  v5 = 5;
  do
  {
    ArraySort((int)v4, 800, 2, 0 /* TODO: pmf_to_u32((ArcSceneObject * (ArcSceneObject::*)())ArcSceneObject::InitFromConfig) */);
    v4 += 402;
    --v5;
  }
  while ( v5 );
  *((_BYTE *)&this->dwWeaponWU + 13788) = 0;
  *(&this->dwWeaponWU + 3448) = 0;
  *((_BYTE *)&this->dwWeaponWU + 13796) = 0;
  *((_BYTE *)&this->dwWeaponWU + 13802) = 0;
  *(&this->dwWeaponWU + 3451) = 3;
  *(&this->dwWeaponWU + 3454) = 0;
  *((_BYTE *)&this->dwWeaponWU + 13820) = 0;
  *((_BYTE *)&this->dwWeaponWU + 13821) = 0;
  *((_BYTE *)&this->dwWeaponWU + 13822) = 0;
  LOBYTE(this->m_ListGrid[3].m_ppic) = 0;
  BYTE1(this->m_ListGrid[3].m_ppic) = 0;
  this->m_ListGrid[3].m_ppicInfo = ((_PlugInfo *)0);
  ((UIRoleDialog *)&this->m_ListGrid[3].m_disablepic)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this->m_ListGrid[12].m_disablepic)->UIRoleDialog::UIRoleDialog();
  *(int *)((char *)&this->dwWeaponWU + 13797) = 0;
  *((_BYTE *)&this->dwWeaponWU + 13801) = 0;
  *(&this->dwWeaponWU + 3452) = 0;
  *((_BYTE *)&this->dwWeaponWU + 13812) = 0;
  *(&this->dwWeaponWU + 3458) = 0;
  *(&this->dwWeaponWU + 3457) = 0;
  *(&this->dwWeaponWU + 3456) = 0;
  *(&this->dwWeaponWU + 3462) = 0;
  *(&this->dwWeaponWU + 3461) = 0;
  *(&this->dwWeaponWU + 3460) = 0;
  *(&this->dwWeaponWU + 3459) = 0;
  *(&this->dwWeaponWU + 1246) = 0;
  *(&this->dwWeaponWU + 1245) = 1;
  *((_BYTE *)&this->dwWeaponWU + 4960) = 0;
  *(&this->dwWeaponWU + 1241) = 0;
  *((_WORD *)&this->dwWeaponWU + 972) = (unsigned __int16)&byte_1010101;
  result = (int)this;
  *((_BYTE *)&this->dwWeaponWU + 1946) = (unsigned __int8)&byte_1010101;
  return result;
}

// 0x005263C0
int SaleUI::ResetGridState()
{
  signed int v2; // esi
  int *v3; // ebx
  int v4; // eax
  const void *v5; // esi
  int v6; // eax
  void *v7; // edi
  bool v8; // zf
  int result; // eax
  float fX; // [esp+0x0] [ebp-0x28]
  float fXa; // [esp+0x0] [ebp-0x28]
  float fXb; // [esp+0x0] [ebp-0x28]
  float fXc; // [esp+0x0] [ebp-0x28]
  float fY; // [esp+0x4] [ebp-0x24]
  float fYa; // [esp+0x4] [ebp-0x24]
  float fYb; // [esp+0x4] [ebp-0x24]
  float fYc; // [esp+0x4] [ebp-0x24]
  int v18; // [esp+0x18] [ebp-0x10]
  signed int v19; // [esp+0x1C] [ebp-0xC]
  int v20; // [esp+0x24] [ebp-0x4]

  v18 = 36;
  v2 = *(_DWORD *)this->m_ListGrid[3].m_text - (unsigned int)this->m_ListGrid[3].m_texty;
  v19 = v2;
  v20 = (int)this->m_ListGrid[3].m_pbk - *(_DWORD *)&this->m_ListGrid[3].m_text[8];
  v3 = (int *)(&this->dwWeaponWU + 3463);
  while ( 1 )
  {
    (((RenderTarget *)v3))->RenderTarget::LoadTexture("UI\\GameMainUI\\Par_Effect\\spark_16.tga");
    (((RenderTarget *)v3))->RenderTarget::SetSize(16);
    (((RenderTarget *)v3))->RenderTarget::SetColor(0x64u, 0x64u, 0xD2u);
    v4 = rand();
    (((RenderTarget *)v3))->RenderTarget::SetAlpha(v4 % 100 - 101);
    (((RenderTarget *)v3))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v3))->RenderTarget::SetState(1061997773);
    fY = (float)(int)this->m_ListGrid[3].m_fonttype;
    fX = (float)((unsigned int)this->m_ListGrid[3].m_texty + rand() % v2);
    (((RenderTarget *)v3))->RenderTarget::UpdateTransform(fX, fY);
    (((RenderTarget *)v3))->RenderTarget::Render((int)this->m_ListGrid[3].m_texty, (int)this->m_ListGrid[3].m_fonttype, *(_DWORD *)this->m_ListGrid[3].m_text);
    fYa = (float)(rand() % 2 + 1);
    fXa = (float)(rand() % 2 + 1);
    (((RenderTarget *)v3))->RenderTarget::SetOffset(fXa, fYa);
    (((RenderTarget *)v3))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v3))->RenderTarget::SetVisible(1);
    qmemcpy(v3 + 5256, v3, 0x248u);
    v5 = (char *)v3 + 10512;
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::LoadTexture("UI\\GameMainUI\\Par_Effect\\spark_16.tga");
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::SetSize(16);
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::SetColor(0x64u, 0x64u, 0xD2u);
    v6 = rand();
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::SetAlpha(v6 % 100 - 101);
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::SetState(1061997773);
    fYb = (float)*(int *)&this->m_ListGrid[3].m_text[12];
    fXb = (float)(*(_DWORD *)&this->m_ListGrid[3].m_text[8] + rand() % v20);
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::UpdateTransform(fXb, fYb);
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::Render(*(_DWORD *)&this->m_ListGrid[3].m_text[8], *(_DWORD *)&this->m_ListGrid[3].m_text[12], (int)this->m_ListGrid[3].m_pbk);
    fYc = (float)(rand() % 2 + 1);
    fXc = (float)(rand() % 2 + 1);
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::SetOffset(fXc, fYc);
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)(v3 + 10512)))->RenderTarget::SetVisible(1);
    v7 = (char *)v3 + 15768;
    v3 += 146;
    result = v18 - 1;
    v8 = v18 == 1;
    qmemcpy(v7, v5, 0x248u);
    --v18;
    if ( v8 )
      break;
    v2 = v19;
  }
  BYTE2(this->m_ListGrid[3].m_ppic) = 0;
  return result;
}
