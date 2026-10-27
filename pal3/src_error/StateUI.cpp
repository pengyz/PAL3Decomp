#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/StateUI.h"
#include "Role/Actor.h"
#include "Render/CScreenMode.h"
#include "Misc/ComposeUI.h"
#include "UI/EquipUI.h"
#include "GameBase/GRPinput.h"
#include "Misc/LineupComp.h"
#include "Misc/LineupUI.h"
#include "Misc/MainEquipUI.h"
#include "Role/NPC.h"
#include "Role/Object3D.h"
#include "Role/ObjectCamera.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/UIBigMap.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UITitle_XJTM.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/m_RoleState.h"
#include "Misc/s_SpecialPropItem.h"
#include "Misc/scAsmDecoder.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];

// 0x0047F390
int StateUI::LoadRoleList()
{
  int result; // eax
  int v3; // edi
  int BufferAt; // eax

  result = (((NPC *)(&g_RoleSlotBuf.dword_17AA450 + 134)))->NPC::GetBufferCount();
  v3 = 0;
  this->m_3DObj.m_rect.bottom = result;
  if ( result > 0 )
  {
    if ( this->m_3DObj.m_rect.right )
    {
      operator delete((void *)this->m_3DObj.m_rect.right);
      this->m_3DObj.m_rect.right = 0;
    }
    this->m_3DObj.m_rect.right = (LONG)operator new(4 * this->m_3DObj.m_rect.bottom);
    result = this->m_3DObj.m_rect.bottom;
    if ( result > 0 )
    {
      do
      {
        BufferAt = (((NPC *)(&g_RoleSlotBuf.dword_17AA450 + 134)))->NPC::GetBufferAt(v3++);
        *(_DWORD *)(this->m_3DObj.m_rect.right + 4 * v3 - 4) = BufferAt;
        result = this->m_3DObj.m_rect.bottom;
      }
      while ( v3 < result );
    }
  }
  return result;
}

// 0x0047F410
int StateUI::ReleaseResource()
{
  if ( this->m_3DObj.m_rect.bottom > 0 && this->m_3DObj.m_rect.right )
  {
    operator delete((void *)this->m_3DObj.m_rect.right);
    this->m_3DObj.m_rect.right = 0;
  }
  this->m_3DObj.m_rect.bottom = 0;
  return (((MainEquipUI *)this))->MainEquipUI::ClearState() /* [ROWTABLE] */;
}

// 0x0047F450
int StateUI::CategorizeRoles()
{
  int result; // eax
  int i; // edi
  int v4; // eax

  this->StateUI::LoadRoleList();
  memset(&this->m_3DObj.m_bvisible, 0, 0x960u);
  result = this->m_3DObj.m_rect.bottom;
  for ( i = 0; i < result; ++i )
  {
    (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(_DWORD *)(this->m_3DObj.m_rect.right + 4 * i));
    switch ( *(_WORD *)(v4 + 4) )
    {
      case 1:
        *((_DWORD *)&this->m_DlgEx + this->m_3DObj.m_childs.m_needscriptdel++ + 337) = *(_DWORD *)v4;
        break;
      case 2:
        *((_DWORD *)&this->m_DlgEx.m_btRc + this->m_3DObj.m_childs.m_nSize++ + 79) = *(_DWORD *)v4;
        break;
      case 3:
        *((_DWORD *)&this->m_DlgEx.m_bk.m_childs.m_pData + (int)this->m_3DObj.m_childs.m_pData++) = *(_DWORD *)v4;
        break;
      case 4:
        *(&this->m_3DObj.m_bvisible + (int)this->m_3DObj.m_pfather++) = *(_DWORD *)v4;
        break;
      case 5:
        *((_DWORD *)&this->m_DlgEx.m_text.m_textx + this->m_3DObj.m_childs.capacity++) = *(_DWORD *)v4;
        break;
      case 6:
        *((_DWORD *)&this[1].m_isJusticeBook + this->m_3DObj.m_bcreateok++ + 11) = *(_DWORD *)v4;
        break;
      default:
        break;
    }
    result = this->m_3DObj.m_rect.bottom;
  }
  return result;
}

// 0x00480070
int StateUI::ShowPanels(int nVal, unsigned __int8 pData, UIWnd *bFlag)
{
  int result; // eax
  UIWnd *v6; // edi

  if ( pData )
  {
    (*(void ( **)(int *, _DWORD))this->m_Alignment.m_bvisible)(
      &this->m_Alignment.m_bvisible,
      pData);
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_Head[0].m_pbk2))(&this->m_Head[0].m_pbk2, pData);
    (*(void ( **)(float *, _DWORD))LODWORD(this->m_Head[2].m_ratioh))(&this->m_Head[2].m_ratioh, pData);
    (*(void ( **)(LONG *, _DWORD))this->m_Head[4].m_rect.right)(&this->m_Head[4].m_rect.right, pData);
    (*(void ( **)(int *, _DWORD))this->m_TopFrame.m_childs.capacity)(
      &this->m_TopFrame.m_childs.capacity,
      pData);
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_LeaveHere.m_texarray.m_ptex[10]))(
      &this->m_LeaveHere.m_texarray.m_ptex[10],
      pData);
  }
  result = nVal;
  switch ( nVal )
  {
    case 0:
      result = (int)this[1].m_OutFrameT.m_ppicInfo;
      if ( (UIWnd *)result != bFlag )
        result = (*(int ( **)(int *, _DWORD))this->m_Alignment.m_bvisible)(
                   &this->m_Alignment.m_bvisible,
                   pData);
      if ( (UIWnd *)this[1].m_OutFrameT.m_disablepic != bFlag )
        result = ((int ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_Head[0].m_pbk2))(
                   &this->m_Head[0].m_pbk2,
                   pData);
      if ( (UIWnd *)this[1].m_OutFrameT.m_disablepicInfo != bFlag )
        result = (*(int ( **)(float *, _DWORD))LODWORD(this->m_Head[2].m_ratioh))(
                   &this->m_Head[2].m_ratioh,
                   pData);
      if ( (UIWnd *)this[1].m_OutFrameT.m_pbk2 != bFlag )
        result = (*(int ( **)(LONG *, _DWORD))this->m_Head[4].m_rect.right)(
                   &this->m_Head[4].m_rect.right,
                   pData);
      if ( *(UIWnd **)&this[1].m_OutFrameT.m_mouseoff != bFlag )
        result = (*(int ( **)(int *, _DWORD))this->m_TopFrame.m_childs.capacity)(
                   &this->m_TopFrame.m_childs.capacity,
                   pData);
      if ( (UIWnd *)this[1].m_OutFrameT.m_FVF != bFlag )
        result = ((int ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_LeaveHere.m_texarray.m_ptex[10]))(
                   &this->m_LeaveHere.m_texarray.m_ptex[10],
                   pData);
      break;
    case 1:
      v6 = (UIWnd *)bFlag;
      if ( bFlag )
      {
        if ( (UIWnd *)this[1].m_OutFrameT.m_disablepic != bFlag )
          result = ((int ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_Head[0].m_pbk2))(
                     &this->m_Head[0].m_pbk2,
                     pData);
        if ( (UIWnd *)this[1].m_OutFrameT.m_disablepicInfo != bFlag )
          result = (*(int ( **)(float *, _DWORD))LODWORD(this->m_Head[2].m_ratioh))(
                     &this->m_Head[2].m_ratioh,
                     pData);
        if ( (UIWnd *)this[1].m_OutFrameT.m_pbk2 != bFlag )
          result = (*(int ( **)(LONG *, _DWORD))this->m_Head[4].m_rect.right)(
                     &this->m_Head[4].m_rect.right,
                     pData);
        if ( *(UIWnd **)&this[1].m_OutFrameT.m_mouseoff == bFlag )
          goto LABEL_58;
        goto LABEL_57;
      }
      result = (int)this[1].m_OutFrameT.m_ppicInfo;
      if ( result )
        result = (*(int ( **)(int *, _DWORD))this->m_Alignment.m_bvisible)(
                   &this->m_Alignment.m_bvisible,
                   pData);
      break;
    case 2:
      v6 = (UIWnd *)bFlag;
      if ( bFlag )
      {
        if ( (UIWnd *)this[1].m_OutFrameT.m_disablepicInfo != bFlag )
          result = this->StateUI::DispatchCmd(2);
        if ( (UIWnd *)this[1].m_OutFrameT.m_pbk2 == bFlag )
          goto LABEL_36;
        goto LABEL_35;
      }
      if ( this[1].m_OutFrameT.m_ppicInfo )
        this->StateUI::DispatchCmd(0);
      result = (int)this[1].m_OutFrameT.m_disablepic;
      if ( result )
        result = this->StateUI::DispatchCmd(1);
      break;
    case 3:
      v6 = (UIWnd *)bFlag;
      if ( bFlag )
      {
        if ( (UIWnd *)this[1].m_OutFrameT.m_pbk2 != bFlag )
LABEL_35:
          result = this->StateUI::DispatchCmd(3);
LABEL_36:
        if ( *(UIWnd **)&this[1].m_OutFrameT.m_mouseoff == v6 )
          goto LABEL_58;
        goto LABEL_57;
      }
      if ( this[1].m_OutFrameT.m_ppicInfo )
        this->StateUI::DispatchCmd(0);
      if ( this[1].m_OutFrameT.m_disablepic )
        this->StateUI::DispatchCmd(1);
      result = (int)this[1].m_OutFrameT.m_disablepicInfo;
      if ( result )
        result = this->StateUI::DispatchCmd(2);
      break;
    case 4:
      v6 = (UIWnd *)bFlag;
      if ( bFlag )
      {
        if ( *(UIWnd **)&this[1].m_OutFrameT.m_mouseoff != bFlag )
LABEL_57:
          result = this->StateUI::DispatchCmd(4);
LABEL_58:
        if ( (UIWnd *)this[1].m_OutFrameT.m_FVF != v6 )
          goto LABEL_72;
      }
      else
      {
        if ( this[1].m_OutFrameT.m_ppicInfo )
          this->StateUI::DispatchCmd(0);
        if ( this[1].m_OutFrameT.m_disablepic )
          this->StateUI::DispatchCmd(1);
        if ( this[1].m_OutFrameT.m_disablepicInfo )
          this->StateUI::DispatchCmd(2);
        result = (int)this[1].m_OutFrameT.m_pbk2;
        if ( result )
          result = this->StateUI::DispatchCmd(3);
      }
      break;
    case 5:
      result = (int)bFlag;
      if ( bFlag )
      {
        if ( (UIWnd *)this[1].m_OutFrameT.m_FVF != bFlag )
LABEL_72:
          result = this->StateUI::DispatchCmd(5);
      }
      else
      {
        if ( this[1].m_OutFrameT.m_ppicInfo )
          this->StateUI::DispatchCmd(0);
        if ( this[1].m_OutFrameT.m_disablepic )
          this->StateUI::DispatchCmd(1);
        if ( this[1].m_OutFrameT.m_disablepicInfo )
          this->StateUI::DispatchCmd(2);
        if ( this[1].m_OutFrameT.m_pbk2 )
          this->StateUI::DispatchCmd(3);
        result = *(_DWORD *)&this[1].m_OutFrameT.m_mouseoff;
        if ( result )
          result = this->StateUI::DispatchCmd(4);
      }
      break;
    default:
      return result;
  }
  return result;
}

// 0x00480450
int StateUI::DispatchCmd(BOOL bFlag)
{
  int result; // eax
  unsigned __int8 v3; // [esp+0x8] [ebp+0x8]

  result = bFlag;
  switch ( bFlag )
  {
    case 0:
      result = (*(int ( **)(int *, _DWORD))this->m_Alignment.m_bvisible)(
                 &this->m_Alignment.m_bvisible,
                 v3);
      break;
    case 1:
      result = ((int ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_Head[0].m_pbk2))(
                 &this->m_Head[0].m_pbk2,
                 v3);
      break;
    case 2:
      result = (*(int ( **)(float *, _DWORD))LODWORD(this->m_Head[2].m_ratioh))(&this->m_Head[2].m_ratioh, v3);
      break;
    case 3:
      result = (*(int ( **)(LONG *, _DWORD))this->m_Head[4].m_rect.right)(&this->m_Head[4].m_rect.right, v3);
      break;
    case 4:
      result = (*(int ( **)(int *, _DWORD))this->m_TopFrame.m_childs.capacity)(
                 &this->m_TopFrame.m_childs.capacity,
                 v3);
      break;
    case 5:
      result = ((int ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_LeaveHere.m_texarray.m_ptex[10]))(
                 &this->m_LeaveHere.m_texarray.m_ptex[10],
                 v3);
      break;
    default:
      return result;
  }
  return result;
}

// 0x00482C90
int StateUI::AutoScrollParticles(int nVal)
{
  char *v4; // edi
  int *v5; // ebx
  int v6; // esi
  LONG *v7; // ebp
  int v8; // eax
  int v9; // eax
  LONG *v10; // edi
  LONG *v11; // esi
  bool v12; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  float fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  float fYb; // [esp+0x4] [ebp-0x20]
  char *v20; // [esp+0x18] [ebp-0xC]
  int v21; // [esp+0x1C] [ebp-0x8]
  int nVala; // [esp+0x28] [ebp+0x4]

  this->m_RoleState[4].m_JingVal.m_disablepicInfo = ((_PlugInfo *)0);
  this->m_RoleState[4].m_JingVal.m_pbk2 = ((gbTexture *)0);
  nVala = 16;
  *((_BYTE *)&this->m_RoleState[4].m_JingVal.m_disablepicInfo + nVal) = 1;
  v4 = (char *)this + 16 * nVal;
  v5 = (int *)(v4 + 154200);
  v6 = *(&this->m_RoleState[4].m_JingVal.m_id + 4 * nVal) - *((_DWORD *)v4 + 38550);
  v20 = (char *)v4;
  v21 = v6;
  v7 = (LONG *)(&this->m_GameMoney.m_rect.bottom + 2336 * nVal);
  while ( 1 )
  {
    (((RenderTarget *)v7))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v7))->RenderTarget::SetSize(32);
    fY = rand() % 10 + 58;
    fX = rand() % 10 + 66;
    v8 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetColor(v8 % 10 - 6, fX, fY);
    v9 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetAlpha(v9 % 55 - 56);
    *((_BYTE *)v7 + 104) = 1;
    (((RenderTarget *)v7))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v7))->RenderTarget::SetState(1067030938);
    fYa = (float)*((int *)v4 + 38551);
    fXa = (float)(*v5 + rand() % v6);
    (((RenderTarget *)v7))->RenderTarget::UpdateTransform(fXa, fYa);
    (((RenderTarget *)v7))->RenderTarget::Render(*v5, v5[1], v5[2]);
    fYb = (float)(rand() % 2 + 1);
    fXb = (float)(rand() % 2 + 1);
    (((RenderTarget *)v7))->RenderTarget::SetOffset(fXb, fYb);
    (((RenderTarget *)v7))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v7))->RenderTarget::SetVisible(1);
    v10 = (LONG *)(v7 + 18688);
    v11 = (LONG *)v7;
    v7 += 146;
    result = nVala - 1;
    v12 = nVala == 1;
    qmemcpy(v10, v11, 0x248u);
    --nVala;
    if ( v12 )
      break;
    v4 = (char *)v20;
    v6 = v21;
  }
  return result;
}

// 0x00483380
void StateUI::ctor()
{
  ObjectCamera *top; // ecx
  void *v3; // edi

  top = (ObjectCamera *)this->m_TopFrame.m_rect.top;
  if ( top )
  {
    (((ObjectCamera *)top))->ObjectCamera::Destroy();
    v3 = (void *)this->m_TopFrame.m_rect.top;
    if ( v3 )
    {
      (((ObjectCamera *)this->m_TopFrame.m_rect.top))->ObjectCamera::GetCameraDirect();
      operator delete(v3);
    }
    this->m_TopFrame.m_rect.top = 0;
  }
  ((Object3D *)&this->m_TopFrame.m_pbkInfo)->Object3D::Object3D();
  (((UIRoleDialog *)&this->m_State[1].m_text[12]))->UIRoleDialog::~UIRoleDialog();
  (((UIFrameContainer *)&this->m_RoleState[4].m_ShenBar.m_color))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_par[0][0].par_radiusY))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_GameMoney.m_rect.bottom))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_GameTime.m_rect.bottom))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->stp_Effect.m_rect.bottom))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)&this->stp_Exit.m_rect.bottom))->UICaption::Destroy2();
  (((UICaption *)&this->stp_System.m_rect.bottom))->UICaption::Destroy2();
  (((UICaption *)&this->stp_TaskBook.m_rect.bottom))->UICaption::Destroy2();
  (((UICaption *)&this->stp_BattleArray.m_rect.bottom))->UICaption::Destroy2();
  (((UICaption *)&this->stp_Prop.m_rect.bottom))->UICaption::Destroy2();
  (((UICaption *)&this->stp_Equip.m_rect.bottom))->UICaption::Destroy2();
  (((UICaption *)&this->stp_Magic.m_rect.bottom))->UICaption::Destroy2();
  (((UICaption *)&this->stp_State.m_rect.bottom))->UICaption::Destroy2();
  (((UICaption *)&this->stp_BarL.m_align))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_OutFrameB.m_align))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_OutFrameL.m_align))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_OutFrameR.m_align))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_OutFrameT.m_align))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_TimeMoney.m_align))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Frame.m_align))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x004845F0
int StateUI::IteratePlayerAtts()
{
  int v1; // esi
  int result; // eax

  v1 = 0;
  result = (int)&g_RoleSlotBuf.m_nAnimCopy2 + 2;
  do
  {
    if ( *((_BYTE *)&this->m_Frame.m_bfocus + v1 + 1) )
    {
      switch ( *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + v1 + 2) )
      {
        case 0:
          *(_BYTE *)result = 1;
          break;
        case 1:
          *(_BYTE *)result = 2;
          break;
        case 2:
          *(_BYTE *)result = 3;
          break;
        case 3:
          *(_BYTE *)result = 4;
          break;
        case 4:
          *(_BYTE *)result = 5;
          break;
        case 5:
          *(_BYTE *)result = 6;
          break;
        default:
          break;
      }
    }
    result += 1408;
    ++v1;
  }
  while ( result < (int)byte_C0649E );
  return result;
}

// 0x00484660
int StateUI::UpdateVisibility()
{
  int v2; // ebx
  float *p_m_ratioh; // edi
  char *v4; // ebp
  int v5; // ebp
  UIWnd *v6; // edi
  int *p_m_benable; // ebx
  int v8; // ebx
  int i; // edi
  int result; // eax
  unsigned int v11; // [esp+0x0] [ebp-0x18]
  int v12; // [esp+0x10] [ebp-0x8]
  int *a2; // [esp+0x14] [ebp-0x4]

  v2 = 5;
  *(_DWORD *)&this->m_State[1].m_text[8] = (_DWORD)dword_C10CC8;
  p_m_ratioh = (float *)&this->m_RoleState[4].m_WuLing[2].m_ratioh;
  v4 = (char *)&this->m_RoleState[4].m_ShenVal.m_text[8];
  do
  {
    (**(void ( ***)(char *, _DWORD))v4)((char *)(v4), (_DWORD)(0));
    (**(void ( ***)(float *, int))p_m_ratioh)((float *)(p_m_ratioh), (int)(1));
    v4 += 344;
    p_m_ratioh += 38;
    --v2;
  }
  while ( v2 );
  (((UIWnd *)&this->m_RoleState[4].m_ShenVal.m_text[344 * *(_DWORD *)&this->m_State[1].m_text[8] + 8]))->UIWnd::sub_445FA0(&this->m_State[1].m_rect.right);
  (**(void ( ***)(char *, int))&this->m_RoleState[4].m_ShenVal.m_text[344
                                                                              * *(_DWORD *)&this->m_State[1].m_text[8]
                                                                              + 8])((char *)(&this->m_RoleState[4].m_ShenVal.m_text[344 * *(_DWORD *)&this->m_State[1].m_text[8] + 8]), (int)(1));
  v5 = 0;
  v12 = 1;
  *(&this->m_RoleState[4].m_WuLing[2].m_benable + *(_DWORD *)&this->m_State[1].m_text[8]) = 0;
  v6 = (UIWnd *)&this->m_RoleState[4].m_ShenVal.m_text[8];
  a2 = (int *)&this->m_State[1].m_childs.capacity;
  p_m_benable = (int *)&this->m_RoleState[4].m_WuLing[2].m_benable;
  do
  {
    if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) && *(_DWORD *)&this->m_State[1].m_text[8] != v5 )
    {
      *p_m_benable = v12;
      (((UIWnd *)v6))->UIWnd::sub_445FA0(a2);
      (**(void ( ***)(UIWnd *, int))v6)((UIWnd *)(v6), (int)(1));
      ++v12;
      a2 += 4;
    }
    ++v5;
    ++p_m_benable;
    v6 = (UIWnd *)((char *)v6 + 344);
  }
  while ( v5 < 5 );
  v8 = 42;
  (((LineupComp *)this))->LineupComp::PositionAt(*(_DWORD *)&this->m_State[1].m_text[8], 638, 42);
  (((LineupComp *)this))->LineupComp::DispatchSlotMethod(*(_DWORD *)&this->m_State[1].m_text[8], 1u);
  for ( i = 0; i < 5; ++i )
  {
    if ( *((_BYTE *)&this->m_Frame.m_bfocus + i + 1) && *(_DWORD *)&this->m_State[1].m_text[8] != i )
    {
      v8 += 124;
      (((LineupComp *)this))->LineupComp::PositionAt(i, 638, v8);
      (((LineupComp *)this))->LineupComp::DispatchSlotMethod(i, 1u);
    }
  }
  this->StateUI::RefreshStatsDisplay();
  this->m_LeaveHere.m_rect.top = 0;
  result = (((LineupUI *)this))->LineupUI::GetSlotRect((int)dword_C10CC8, v11) /* [ROWTABLE] */;
  LOBYTE(this->m_TopFrame.m_rect.bottom) = 0;
  LOBYTE(this->m_TopFrame.m_childs.capacity) = 0;
  return result;
}

// 0x00484E90
int StateUI::SelectTab1(unsigned __int8 nTab)
{
  BYTE2(this->m_Frame.m_bfocus) = nTab;
  return (((LineupComp *)this))->LineupComp::DispatchSlotMethod(1, nTab);
}

// 0x00484EB0
int StateUI::SelectTab2(unsigned __int8 nTab)
{
  HIBYTE(this->m_Frame.m_bfocus) = nTab;
  return (((LineupComp *)this))->LineupComp::DispatchSlotMethod(2, nTab);
}

// 0x00485230
int StateUI::sub_485230()
{
  __int64 v2; // rax
  int v3; // ebx
  int v4; // ebp
  double v5; // st7
  unsigned __int8 v7; // c0
  unsigned __int8 v8; // c3
  char *v9; // edi
  Object3D *v10; // ebp
  char *v11; // ebp
  Object3D *v12; // ebp
  long double v13; // st7
  double v14; // st7
  gbTexture *v15; // eax
  double v16; // st6
  char *v17; // ecx
  int v18; // edx
  int v19; // eax
  double v20; // st6
  char *v21; // ecx
  int v22; // edx
  int v23; // eax
  double v24; // st6
  UIWnd *m_pfather; // eax
  char v26; // cl
  char *v27; // eax
  float v28; // ebx
  UIWnd *v29; // eax
  CScreenMode *Instance; // eax
  int v31; // ebx
  gbTexture **v32; // ebp
  gbFontType *p_m_fonttype; // edi
  UIWnd *v34; // ecx
  float v35; // eax
  float v36; // eax
  int v37; // ecx
  double v38; // st7
  int v39; // edx
  int v40; // eax
  int v41; // ecx
  UIWnd *v42; // eax
  CScreenMode *v43; // eax
  int v44; // ebp
  Object3D *v45; // edi
  int v46; // ebx
  gbVisNode **v47; // edi
  char v48; // al
  const void *v50; // [esp-0x8] [ebp-0x58]
  const void *v51; // [esp-0x8] [ebp-0x58]
  int v52; // [esp-0x4] [ebp-0x54]
  tagPOINT *v53; // [esp+0x0] [ebp-0x50]
  bool v54; // [esp+0x13] [ebp-0x3D]
  float pOut; // [esp+0x14] [ebp-0x3C] BYREF
  float pOut2; // [esp+0x18] [ebp-0x38] BYREF
  float v57; // [esp+0x1C] [ebp-0x34]
  float v58; // [esp+0x20] [ebp-0x30]
  float v59; // [esp+0x24] [ebp-0x2C]
  float v60; // [esp+0x28] [ebp-0x28]
  float v61; // [esp+0x2C] [ebp-0x24]
  int v62; // [esp+0x30] [ebp-0x20]
  int v63; // [esp+0x34] [ebp-0x1C]
  gbFontType v64; // [esp+0x38] [ebp-0x18]
  float v65; // [esp+0x3C] [ebp-0x14]
  int v66; // [esp+0x40] [ebp-0x10]
  float v67; // [esp+0x44] [ebp-0xC]
  int v68; // [esp+0x48] [ebp-0x8]
  float v69; // [esp+0x4C] [ebp-0x4]
  float fVal; // [esp+0x54] [ebp+0x4]
  int fVala; // [esp+0x54] [ebp+0x4]
  int a3; // [esp+0x58] [ebp+0x8]

  v2 = (__int64)g_fGameTimer;
  v3 = (int)v2 / 3600;
  v4 = (int)v2 / 60 % 60;
  v52 = (int)v2 % 60;
  if ( (int)v2 / 3600 < 100 )
    sprintf((char *const)&this->m_isJusticeBook + 32, "%02d:%02d:%02d", v3, v4, v52);
  else
    sprintf((char *const)&this->m_isJusticeBook + 32, "%03d:%02d:%02d", v3, v4, v52);
  SetEnable((UICaption *)&this->m_GameTime.m_rect.bottom);
  sprintf((char *const)&this->m_isJusticeBook + 32, (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)&this->m_GameMoney.m_rect.bottom);
  if ( (((Object3D *)1))->Object3D::GetMouseRay(v53) )
  {
    (((GRPinput *)&g_Input))->GRPinput::GetMousePos(&pOut, &pOut2);
    v5 = (double)SLODWORD(pOut2) + *(float *)&this->m_TopFrame.m_id;
    *(float *)&this->m_TopFrame.m_id = v5;
    if ( v7 | v8 )
    {
      if ( v5 < -86.0 )
        this->m_TopFrame.m_id = -1028915200;
    }
    else
    {
      this->m_TopFrame.m_id = -1049624576;
    }
    (((ObjectCamera *)this->m_TopFrame.m_rect.top))->ObjectCamera::SetCameraDist(0, this->m_TopFrame.m_id, 1078774989);
  }
  LOBYTE(this->m_TopFrame.m_childs.capacity) = this->m_LeaveHere.m_caption[45];
  v9 = 0;
  v10 = (Object3D *)&this->m_LeaveHere.m_texarray.m_ptex[5];
  while ( !(((Object3D *)v10))->Object3D::Update() )
  {
    ++v9;
    ++v10;
    if ( (int)v9 >= 5 )
      goto LABEL_73;
  }
  v11 = (char *)this + 152 * (_DWORD)v9;
  if ( !v11[159937] )
  {
    if ( LOBYTE(this->m_TopFrame.m_rect.bottom) )
    {
      m_pfather = this->m_TopFrame.m_pfather;
      this->m_TopFrame.m_childs.m_pData = ((char *)(v9));
      if ( m_pfather != (UIWnd *)v9 )
      {
        v26 = *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)m_pfather + 2);
        *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)m_pfather + 2) = *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo
                                                                                              + (_DWORD)v9
                                                                                              + 2);
        *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v9 + 2) = v26;
        v27 = (char *)this + 152 * (int)this->m_TopFrame.m_pfather;
        pOut = *((float *)v27 + 39962);
        pOut2 = *((float *)v27 + 39963);
        v28 = *((float *)v11 + 39962);
        v57 = *((float *)v27 + 39964);
        (((Object3D *)(v27 + 159816)))->Object3D::VecAngle(v28, *((float *)v11 + 39963), *((float *)v11 + 39964));
        (((Object3D *)(v11 + 159816)))->Object3D::VecAngle(pOut, pOut2, v57);
        BYTE1(this->m_LeaveHere.m_texarray.m_ptex[38 * (int)this->m_TopFrame.m_pfather + 10]) = 0;
        v29 = this->m_TopFrame.m_pfather;
        if ( *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v29 + 2) == 5 )
        {
          this->m_LeaveHere.m_texarrayInfo[38 * (_DWORD)v29 + 2] = (_PlugInfo *)1119092736;
          *((_DWORD *)v11 + 39968) = 0;
        }
        if ( *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v9 + 2) == 5 )
        {
          this->m_LeaveHere.m_texarrayInfo[38 * (int)this->m_TopFrame.m_pfather + 2] = *((_PlugInfo **)v11 + 39968);
          *((_DWORD *)v11 + 39968) = 1119092736;
        }
        v50 = fVal2;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v50, 1);
      }
      LOBYTE(this->m_TopFrame.m_rect.bottom) = 0;
      v11[159837] = 0;
    }
    else
    {
      LOBYTE(this->m_TopFrame.m_rect.bottom) = 1;
      this->m_TopFrame.m_pfather = ((UIWnd *)((UIWnd *)v9));
      v11[159837] = 1;
      if ( *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v9 + 2) != 5 )
      {
        (((Actor *)this->m_LeaveHere.m_texarray.m_ptex[38 * (int)this->m_TopFrame.m_pfather + 7]))->Actor::CompareActionName(*(_DWORD *)&this->m_LeaveHere.m_caption[152 * (int)this->m_TopFrame.m_pfather + 72], 0);
        v12 = (Object3D *)(v11 + 159816);
        v13 = (((Object3D *)v12))->Object3D::SetCentrePos();
        pOut = v13;
        if ( v13 >= 1.5 && pOut <= 358.5f )
        {
          v54 = v12->m_position.x > (double)v12->RelativePos.x;
          v14 = 360.0 - pOut;
          *(float *)this->m_LeaveHere.m_texarray.m_ptex = v14;
          this->m_LeaveHere.m_texarray.m_ptex[2] = (gbTexture *)!v54;
          v15 = (gbTexture *)this->m_LeaveHere.m_texarray.m_ptex[3];
          *(_DWORD *)&this->m_LeaveHere.m_bBigFont = 0;
          BYTE1(this->m_LeaveHere.m_offsetx) = 1;
          if ( v15 )
          {
            if ( v15 != (gbTexture *)1 || this->m_LeaveHere.m_texarray.m_ptex[2] )
              goto LABEL_33;
            v16 = -(360.0 - *(float *)this->m_LeaveHere.m_texarray.m_ptex);
          }
          else
          {
            if ( *(float *)&this->m_TopFrame.m_nTextW <= (double)*(float *)&this->m_LeaveHere.m_wndcolor.Color )
              this->m_LeaveHere.m_offsety = *(float *)&this->m_LeaveHere.m_canctrl;
            else
              this->m_LeaveHere.m_offsety = 360.0f - *(float *)&this->m_LeaveHere.m_canctrl;
            if ( this->m_LeaveHere.m_texarray.m_ptex[2] == (gbTexture *)1 )
              v16 = -*(float *)this->m_LeaveHere.m_texarray.m_ptex;
            else
              v16 = 360.0 - *(float *)this->m_LeaveHere.m_texarray.m_ptex;
          }
          *(float *)this->m_LeaveHere.m_texarray.m_ptex = v16;
LABEL_33:
          v17 = (char *)&this->m_LeaveHere.m_caption[45];
          v18 = 5;
          while ( 1 )
          {
            *(float *)(v17 + 11) = v14;
            *(_DWORD *)(v17 + 19) = !v54;
            v19 = *(_DWORD *)(v17 + 23);
            *(_DWORD *)(v17 + 7) = 0;
            *v17 = 1;
            if ( v19 )
            {
              if ( v19 != 1 || *(_DWORD *)(v17 + 19) )
                goto LABEL_48;
              v20 = -(360.0 - *(float *)(v17 + 11));
            }
            else
            {
              if ( *(float *)(v17 - 89) <= (double)*(float *)(v17 - 77) )
                *(_DWORD *)(v17 + 3) = *(_DWORD *)(v17 - 5);
              else
                *(float *)(v17 + 3) = 360.0 - *(float *)(v17 - 5);
              if ( *(_DWORD *)(v17 + 19) == 1 )
                v20 = -*(float *)(v17 + 11);
              else
                v20 = 360.0 - *(float *)(v17 + 11);
            }
            *(float *)(v17 + 11) = v20;
LABEL_48:
            v17 += 152;
            if ( !--v18 )
            {
              v21 = (char *)&this->m_DlgEx.m_static.m_bvisible + 1;
              v22 = 6;
              while ( 1 )
              {
                *(float *)(v21 + 11) = v14;
                *(_DWORD *)(v21 + 19) = !v54;
                v23 = *(_DWORD *)(v21 + 23);
                *(_DWORD *)(v21 + 7) = 0;
                *v21 = 1;
                if ( v23 )
                {
                  if ( v23 != 1 || *(_DWORD *)(v21 + 19) )
                    goto LABEL_64;
                  v24 = -(360.0 - *(float *)(v21 + 11));
                }
                else
                {
                  if ( *(float *)(v21 - 89) <= (double)*(float *)(v21 - 77) )
                    *(_DWORD *)(v21 + 3) = *(_DWORD *)(v21 - 5);
                  else
                    *(float *)(v21 + 3) = 360.0 - *(float *)(v21 - 5);
                  if ( *(_DWORD *)(v21 + 19) == 1 )
                    v24 = -*(float *)(v21 + 11);
                  else
                    v24 = 360.0 - *(float *)(v21 + 11);
                }
                *(float *)(v21 + 11) = v24;
LABEL_64:
                v21 += 152;
                if ( !--v22 )
                  goto LABEL_73;
              }
            }
          }
        }
      }
    }
  }
LABEL_73:
  v31 = 0;
  v32 = (gbTexture **)&this->m_DlgEx.m_bk.m_texs.m_ptex[5];
  p_m_fonttype = (gbFontType *)&this->m_DlgEx.m_bk.m_fonttype;
  do
  {
    if ( (((Object3D *)(p_m_fonttype - 8)))->Object3D::Update() )
    {
      if ( *((_BYTE *)p_m_fonttype + 89) )
        break;
      if ( LOBYTE(this->m_TopFrame.m_rect.bottom) )
      {
        v34 = this->m_TopFrame.m_pfather;
        this->m_TopFrame.m_childs.m_pData = ((char *)((char *)-1));
        LOBYTE(pOut) = *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v34 + 2);
        *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v34 + 2) = v31;
        v67 = *(float *)p_m_fonttype;
        v68 = *((_DWORD *)p_m_fonttype + 1);
        v35 = *((float *)p_m_fonttype + 2);
        v64 = *p_m_fonttype;
        v69 = v35;
        v65 = *((float *)p_m_fonttype + 1);
        v36 = *(float *)p_m_fonttype;
        v66 = *((_DWORD *)p_m_fonttype + 2);
        v61 = v36;
        v37 = *((_DWORD *)p_m_fonttype + 1);
        v58 = v36;
        v38 = v65 - *(float *)&this->m_TopFrame.m_rect.right;
        v39 = *((_DWORD *)p_m_fonttype + 2);
        v62 = v37;
        v63 = v39;
        v59 = v38;
        v60 = v69;
        (((Object3D *)&this->m_LeaveHere.m_texarray.m_ptex[38 * (int)this->m_TopFrame.m_pfather + 5]))->Object3D::VecAngle(v36, v59, v69);
        BYTE1(this->m_LeaveHere.m_texarray.m_ptex[38 * (int)this->m_TopFrame.m_pfather + 10]) = 0;
        *v32 = (gbTexture *)this->m_TopFrame.m_pfather;
        v40 = LOBYTE(pOut);
        v41 = 9 * LOBYTE(pOut);
        this->m_DlgEx.m_bk.m_texs.m_ptex[LOBYTE(pOut) + 5] = (gbTexture *)-1;
        *((_BYTE *)p_m_fonttype + 48) = 0;
        *((_BYTE *)p_m_fonttype - 11) = 0;
        *((_BYTE *)&this->m_DlgEx.m_static.m_rect.left + 16 * v41 + 8 * v40) = 1;
        this->m_LeaveHere.m_texarrayInfo[38 * (int)this->m_TopFrame.m_pfather + 2] = 0;
        v42 = this->m_TopFrame.m_pfather;
        if ( *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v42 + 2) == 5 )
          this->m_LeaveHere.m_texarrayInfo[38 * (_DWORD)v42 + 2] = (_PlugInfo *)1119092736;
        v51 = fVal2;
        v43 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v43))->CScreenMode::AudioSetPosition(v51, 1);
        LOBYTE(this->m_TopFrame.m_rect.bottom) = 0;
      }
    }
    ++v31;
    ++v32;
    p_m_fonttype += 38;
  }
  while ( v31 < 6 );
  (((ObjectCamera *)this->m_TopFrame.m_rect.top))->ObjectCamera::SetStepRotate();
  v44 = LODWORD(fVal);
  (((Object3D *)&this->m_TopFrame.m_pbkInfo))->Object3D::CaculateRelative(fVal);
  v45 = (Object3D *)&this->m_LeaveHere.m_texarray.m_ptex[5];
  v46 = 5;
  do
  {
    (((Object3D *)v45++))->Object3D::CaculateRelative(fVal);
    --v46;
  }
  while ( v46 );
  v47 = (gbVisNode **)&this->m_DlgEx.m_bk.m_texs.m_ptex[13];
  fVala = 6;
  do
  {
    (((Object3D *)(v47 - 2)))->Object3D::CaculateRelative(*(float *)&v44);
    (((Object3D *)(v47 - 2)))->Object3D::Destroy();
    if ( v48 )
    {
      (*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)((gbChain1DNode *)(*v47)) + 24))(*v47, 0);
      (((gbVisNode *)*v47))->gbVisNode::SetTimeScale(1.0);
    }
    v47 += 38;
    --fVala;
  }
  while ( fVala );
  return (((SceneObj *)this))->SceneObj::Update(v44, a3) /* [ROWTABLE] */;
}

// 0x00485980
int StateUI::RefreshStatsDisplay()
{
  gbTexture **v2; // ebp
  gbColorQuad *p_m_bkColor; // ebx
  char *v4; // ecx
  gbTexture *v5; // edi
  char v6; // al
  int v7; // ebx
  float *p_m_needscriptdel; // edi
  tagRECT *p_m_rect; // ebp
  char *v11; // [esp+0x10] [ebp-0x10]
  float v12; // [esp+0x18] [ebp-0x8]

  v2 = (gbTexture **)&this->m_LeaveHere.m_texarray.m_ptex[5];
  p_m_bkColor = (gbColorQuad *)&this->m_RoleState[4].m_ShenBar.m_bkColor;
  this->m_DlgEx.m_bk.m_texs.m_ptex[3] = 0;
  LOWORD(this->m_DlgEx.m_bk.m_texs.m_ptex[4]) = 0;
  memset(&this->m_DlgEx.m_bk.m_texs.m_ptex[5], 0xFFu, 0x18u);
  v4 = (char *)&g_RoleSlotBuf.m_nAnimCopy1 + 1;
  v5 = 0;
  v11 = (char *)&g_RoleSlotBuf.m_nAnimCopy1 + 1;
  do
  {
    if ( *((_BYTE *)&v5[4].Width + (_DWORD)this + 1) )
    {
      if ( *(v4 - 1) )
        BYTE1(p_m_bkColor[1].Color) = 2;
      else
        BYTE1(p_m_bkColor[1].Color) = 0;
      LOBYTE(p_m_bkColor->Color) = (unsigned long)*v4 != 0 ? 2 : 0;
      if ( v4[2] )
        BYTE1(p_m_bkColor->Color) = 2;
      else
        BYTE1(p_m_bkColor->Color) = 0;
      if ( v4[1] )
        BYTE2(p_m_bkColor->Color) = 2;
      else
        BYTE2(p_m_bkColor->Color) = 0;
      if ( v4[3] )
        HIBYTE(p_m_bkColor->Color) = 2;
      else
        HIBYTE(p_m_bkColor->Color) = 0;
      if ( v4[4] )
        LOBYTE(p_m_bkColor[1].Color) = 2;
      else
        LOBYTE(p_m_bkColor[1].Color) = 0;
      switch ( v4[5] )
      {
        case 1:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v5 + 2) = 0;
          (((Object3D *)v2))->Object3D::VecAngle(*(float *)&this->m_TopFrame.m_childs.m_nSize, *(float *)&this->m_TopFrame.m_childs.m_needscriptdel, *(float *)&this->m_TopFrame.m_bcreateok);
          if ( *((_BYTE *)&v5[4].Width + (_DWORD)this + 1) )
          {
            LOBYTE(this->m_DlgEx.m_bk.m_texs.m_ptex[3]) = 1;
            this->m_DlgEx.m_bk.m_texs.m_ptex[5] = v5;
          }
          goto LABEL_31;
        case 2:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v5 + 2) = 1;
          (((Object3D *)v2))->Object3D::VecAngle(*(float *)&this->m_TopFrame.m_bvisible, *(float *)&this->m_TopFrame.m_benable, *(float *)&this->m_TopFrame.m_bfocus);
          if ( *((_BYTE *)&v5[4].Width + (_DWORD)this + 1) )
          {
            BYTE1(this->m_DlgEx.m_bk.m_texs.m_ptex[3]) = 1;
            this->m_DlgEx.m_bk.m_texs.m_ptex[6] = v5;
          }
          goto LABEL_31;
        case 3:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v5 + 2) = 3;
          (((Object3D *)v2))->Object3D::VecAngle(this->m_TopFrame.m_ratioh, *(float *)&this->m_TopFrame.m_textx, *(float *)&this->m_TopFrame.m_texty);
          if ( *((_BYTE *)&v5[4].Width + (_DWORD)this + 1) )
          {
            HIBYTE(this->m_DlgEx.m_bk.m_texs.m_ptex[3]) = 1;
            this->m_DlgEx.m_bk.m_texs.m_ptex[8] = v5;
          }
          goto LABEL_31;
        case 4:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v5 + 2) = 2;
          (((Object3D *)v2))->Object3D::VecAngle(*(float *)&this->m_TopFrame.pDebugTex, *(float *)&this->m_TopFrame.m_align, this->m_TopFrame.m_ratiow);
          if ( *((_BYTE *)&v5[4].Width + (_DWORD)this + 1) )
          {
            BYTE2(this->m_DlgEx.m_bk.m_texs.m_ptex[3]) = 1;
            this->m_DlgEx.m_bk.m_texs.m_ptex[7] = v5;
          }
          goto LABEL_31;
        case 5:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v5 + 2) = 4;
          (((Object3D *)v2))->Object3D::VecAngle(*(float *)&this->m_TopFrame.m_fonttype, *(float *)this->m_TopFrame.m_text, *(float *)&this->m_TopFrame.m_text[4]);
          if ( *((_BYTE *)&v5[4].Width + (_DWORD)this + 1) )
          {
            LOBYTE(this->m_DlgEx.m_bk.m_texs.m_ptex[4]) = 1;
            this->m_DlgEx.m_bk.m_texs.m_ptex[9] = v5;
          }
          goto LABEL_31;
        case 6:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + (_DWORD)v5 + 2) = 5;
          (((Object3D *)v2))->Object3D::VecAngle(*(float *)&this->m_TopFrame.m_text[8], *(float *)&this->m_TopFrame.m_text[12], *(float *)&this->m_TopFrame.m_pbk);
          v2[14] = (gbTexture *)1119092736;
          if ( *((_BYTE *)&v5[4].Width + (_DWORD)this + 1) )
          {
            BYTE1(this->m_DlgEx.m_bk.m_texs.m_ptex[4]) = 1;
            this->m_DlgEx.m_bk.m_texs.m_ptex[10] = v5;
          }
LABEL_31:
          v4 = (char *)v11;
          break;
        default:
          break;
      }
      v6 = *((_BYTE *)&v5[4].Width + (_DWORD)this + 1);
      *((_BYTE *)v2 + 80) = v6;
      if ( !v6 )
        *((_BYTE *)v2 + 21) = 0;
      *((_BYTE *)v2 + 21) = 0;
    }
    v4 += 1408;
    v5 = (gbTexture *)((char *)v5 + 1);
    p_m_bkColor = (gbColorQuad *)((char *)p_m_bkColor + 6);
    v2 += 38;
    v11 = (char *)v4;
  }
  while ( (int)v4 < (int)byte_C06499 );
  v7 = 0;
  p_m_needscriptdel = (float *)&this->m_TopFrame.m_childs.m_needscriptdel;
  p_m_rect = (tagRECT *)&this->m_DlgEx.m_static.m_rect;
  do
  {
    v12 = *(float *)&this->m_TopFrame.m_rect.right + *p_m_needscriptdel;
    (((Object3D *)&p_m_rect[-5]))->Object3D::VecAngle(*(p_m_needscriptdel - 1), v12, p_m_needscriptdel[1]);
    if ( *((_BYTE *)&this->m_DlgEx.m_bk.m_texs.m_ptex[3] + v7) )
    {
      LOBYTE(p_m_rect->left) = 0;
      BYTE1(p_m_rect[-4].top) = 0;
    }
    else
    {
      LOBYTE(p_m_rect->left) = 1;
    }
    ++v7;
    p_m_needscriptdel += 3;
    p_m_rect = (tagRECT *)((char *)p_m_rect + 152);
  }
  while ( v7 < 6 );
  return (((MainEquipUI *)this))->MainEquipUI::CountVisibleStats() /* [ROWTABLE] */;
}

// 0x00485CD0
char * StateUI::RefreshFromAtts()
{
  int v2; // esi
  char *result; // eax
  gbColorQuad *p_m_bkColor; // edx

  this->StateUI::IteratePlayerAtts();
  v2 = 0;
  result = (char *)&g_RoleSlotBuf.m_nAnimCopy1 + 1;
  p_m_bkColor = (gbColorQuad *)&this->m_RoleState[4].m_ShenBar.m_bkColor;
  do
  {
    if ( *((_BYTE *)&this->m_Frame.m_bfocus + v2 + 1) )
    {
      *(result - 1) = BYTE1(p_m_bkColor[1].Color) == 2;
      *result = LOBYTE(p_m_bkColor->Color) == 2;
      result[2] = BYTE1(p_m_bkColor->Color) == 2;
      result[1] = BYTE2(p_m_bkColor->Color) == 2;
      result[3] = HIBYTE(p_m_bkColor->Color) == 2;
      result[4] = LOBYTE(p_m_bkColor[1].Color) == 2;
      switch ( *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + v2 + 2) )
      {
        case 0:
          result[5] = 1;
          break;
        case 1:
          result[5] = 2;
          break;
        case 2:
          result[5] = 4;
          break;
        case 3:
          result[5] = 3;
          break;
        case 4:
          result[5] = 5;
          break;
        case 5:
          result[5] = 6;
          break;
        default:
          break;
      }
    }
    result += 1408;
    ++v2;
    p_m_bkColor = (gbColorQuad *)((char *)p_m_bkColor + 6);
  }
  while ( (int)result < (int)byte_C06499 );
  dword_C10CC8 = *(scAsmDecoder **)&this->m_State[1].m_text[8];
  return result;
}

// 0x00485DF0
int StateUI::OnRender(int nVal1)
{
  int v3; // ebx
  UICursor *v4; // ecx
  int *p_m_step; // esi
  int result; // eax
  int v7; // eax
  int v8; // ecx
  char *v9; // edx
  int v10; // ecx
  CScreenMode *Instance; // eax
  int v12; // eax
  int v13; // edx
  char *v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // eax
  gbColorQuad *v18; // eax
  s_SpecialPropItem *v19; // eax
  char *v20; // eax
  int v21; // eax
  int v22; // edx
  char *v23; // ecx
  CScreenMode *v24; // eax
  int v25; // eax
  int v26; // ecx
  const char **v27; // eax
  CScreenMode *v28; // eax
  CScreenMode *v29; // eax
  CScreenMode *v30; // eax
  CScreenMode *v31; // eax
  CScreenMode *v32; // eax
  CScreenMode *v33; // eax
  CScreenMode *v34; // eax
  CScreenMode *v35; // eax
  CScreenMode *v36; // eax
  CScreenMode *v37; // eax
  int v38; // eax
  int v39; // eax
  const void *v40; // [esp-0x8] [ebp-0x18]
  const void *v41; // [esp-0x8] [ebp-0x18]
  char *v42; // [esp-0x8] [ebp-0x18]
  const void *v43; // [esp-0x8] [ebp-0x18]
  const void *v44; // [esp-0x8] [ebp-0x18]
  const void *v45; // [esp-0x8] [ebp-0x18]
  const void *v46; // [esp-0x8] [ebp-0x18]
  const void *v47; // [esp-0x8] [ebp-0x18]
  const void *v48; // [esp-0x8] [ebp-0x18]
  const void *v49; // [esp-0x8] [ebp-0x18]
  const void *v50; // [esp-0x8] [ebp-0x18]
  const void *v51; // [esp-0x8] [ebp-0x18]
  unsigned int v52; // [esp+0x0] [ebp-0x10]
  const char *nMsg; // [esp+0x18] [ebp+0x8]
  int wParam; // [esp+0x1C] [ebp+0xC]

  switch ( nVal1 )
  {
    case 1000:
      v3 = 0;
      if ( nMsg )
      {
        this->StateUI::UpdateVisibility();
        (((EquipUI *)this))->EquipUI::ShowPage() /* [ROWTABLE] */;
        do
          LoadStateUIRenderTarget(v3++);
        while ( v3 < 8 );
        p_m_step = (int *)&this->m_RoleState[4].m_ShenBar.m_step;
        g_nSceneState = 1;
        *p_m_step = 0;
        p_m_step[1] = 0;
        (((UICursor *)v4))->UICursor::_todo_541CC0();
        result = 1;
      }
      else
      {
        memset(&this->m_RoleState[4].m_ShenBar.m_bkColor, 0, 0x1Cu);
        LOWORD(this->m_RoleState[4].m_ShenBar.m_pdecorateInfo) = 0;
        *(_PlugInfo **)((char *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + 2) = 0;
        result = 1;
        BYTE2(this->m_RoleState[4].m_ShenBar.m_decorateW) = 0;
        *(_DWORD *)&this->m_State[1].m_text[8] = 0;
      }
      break;
    case 1001:
      *((_DWORD *)&this->m_isJusticeBook + 6) = 0;
      do
      {
        v7 = *((_DWORD *)&this->m_isJusticeBook + 6);
        if ( *((_BYTE *)&this->m_Frame.m_bfocus + v7 + 1) )
        {
          *((_DWORD *)&this->m_isJusticeBook + 7) = 0;
          while ( 1 )
          {
            v8 = *((_DWORD *)&this->m_isJusticeBook + 7);
            if ( nMsg == (&(&off_56B990)[6 * v7])[v8] )
            {
              v9 = (char *)this + 1944 * v7 + 248 * v8;
              if ( !*((_DWORD *)v9 + 40509) )
              {
                v40 = (const void *)off_5C5EC8;
                Instance = (CScreenMode *)CScreenMode::GetInstance();
                (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v40, 1);
                v12 = 0;
                do
                {
                  v13 = v12 + 1944 * *((_DWORD *)&this->m_isJusticeBook + 6);
                  v12 += 248;
                  v14 = (char *)&this->m_SpecialPropItem[2] + v13;
                  *((_DWORD *)v14 + 20) = 0;
                  v14[68] = 0;
                }
                while ( v12 < 1488 );
                goto LABEL_28;
              }
              if ( v9[162045] )
                break;
            }
            v10 = v8 + 1;
            *((_DWORD *)&this->m_isJusticeBook + 7) = v10;
            if ( v10 >= 6 )
              goto LABEL_28;
          }
          v15 = *((_DWORD *)&this->m_isJusticeBook + 7);
          if ( *((_BYTE *)&this[1].m_childs.m_nSize + 1944 * v7 + 248 * v15) )
            *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_bkColor.Color + 6 * v7 + v15) = 2;
          else
            *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_bkColor.Color + 6 * v7 + v15) = 1;
          v16 = *((_DWORD *)&this->m_isJusticeBook + 7);
          if ( v16 == 5 || !v16 )
          {
            v17 = *((_DWORD *)&this->m_isJusticeBook + 6);
            if ( *((_BYTE *)&this[1].m_childs.m_nSize + 1944 * v17 + 248 * v16) )
            {
              (((LineupComp *)this))->LineupComp::GetSlotWidget(v17, 1u);
              v18 = (gbColorQuad *)(&this[1].stp_BarL.m_wndcolor + 486 * *((_DWORD *)&this->m_isJusticeBook + 6));
              v18[20].Color = 1;
              LOBYTE(v18[17].Color) = 1;
              *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_foColor.Color
              + 6 * *((_DWORD *)&this->m_isJusticeBook + 6)
              + 1) = 2;
              v19 = (s_SpecialPropItem *)&this->m_SpecialPropItem[243 * *((_DWORD *)&this->m_isJusticeBook + 6) + 2];
              v19[10].m_ItemId = 1;
              v19[8].m_CanUse = 1;
              *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_bkColor.Color + 6 * *((_DWORD *)&this->m_isJusticeBook + 6)) = 2;
            }
            else
            {
              v20 = (char *)&this->m_RoleState[4].m_ShenBar.m_bkColor + 6 * v17;
              *(_DWORD *)v20 = 0;
              *((_WORD *)v20 + 2) = 0;
              *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_foColor.Color
              + 6 * *((_DWORD *)&this->m_isJusticeBook + 6)
              + 1) = 1;
              (((LineupComp *)this))->LineupComp::GetSlotWidget(*((_DWORD *)&this->m_isJusticeBook + 6), 0);
              sub_445E50((int)(&this[1].stp_BarL.m_wndcolor + 486 * *((_DWORD *)&this->m_isJusticeBook + 6)));
              v21 = 0;
              do
              {
                v22 = v21 + 1944 * *((_DWORD *)&this->m_isJusticeBook + 6);
                v21 += 248;
                v23 = (char *)&this->m_SpecialPropItem[2] + v22;
                *((_DWORD *)v23 + 20) = 0;
                v23[68] = 0;
              }
              while ( v21 < 1488 );
            }
          }
          v41 = (const void *)off_5C5EBC;
          v24 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v24))->CScreenMode::AudioSetPosition(v41, 1);
          LOBYTE(this->m_Frame.m_bfocus) = 1;
        }
LABEL_28:
        v25 = *((_DWORD *)&this->m_isJusticeBook + 6) + 1;
        *((_DWORD *)&this->m_isJusticeBook + 6) = v25;
      }
      while ( v25 < 5 );
      v26 = 0;
      v27 = (const char **)&off_56B97C;
      while ( nMsg != *v27 )
      {
        ++v27;
        ++v26;
        if ( (int)v27 >= (int)&off_56B990 )
          goto LABEL_37;
      }
      if ( g_ScriptSystemData.m_nGameMode == 2 )
      {
        (((LineupUI *)this))->LineupUI::GetSlotRect(v26, v52) /* [ROWTABLE] */;
        v42 = (char *)off_5C5EBC;
      }
      else
      {
        sprintf((char *const)&this->m_isJusticeBook + 32, "\\n%s", (const char *)&dword_DD923C);
        SetEnable((UICaption *)&this->m_Alignment.m_text[12]);
        (((UIRoleSelect *)&this->m_State[1].m_text[12]))->UIRoleSelect::SetByte(1);
        v42 = off_5C5EC4[0];
      }
      v28 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v28))->CScreenMode::AudioSetPosition(v42, 1);
      LOBYTE(this->m_Frame.m_bfocus) = 1;
LABEL_37:
      if ( LOBYTE(this->m_Frame.m_bfocus) )
      {
        LOBYTE(this->m_Frame.m_bfocus) = 0;
        result = 1;
      }
      else
      {
        switch ( (unsigned int)nMsg )
        {
          case 0xA00102u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            v43 = (const void *)off_5C5EBC;
            v29 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v29))->CScreenMode::AudioSetPosition(v43, 1);
            this->StateUI::RefreshFromAtts();
            (((MainEquipUI *)*(MainEquipUI **)&this[1].m_par[1][0]._texName[172]))->MainEquipUI::HandleMessage(0);
            goto LABEL_60;
          case 0xA00103u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            v44 = (const void *)off_5C5EBC;
            v30 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v30))->CScreenMode::AudioSetPosition(v44, 1);
            this->StateUI::RefreshFromAtts();
            (((MainEquipUI *)*(MainEquipUI **)&this[1].m_par[1][0]._texName[172]))->MainEquipUI::HandleMessage(3);
            goto LABEL_60;
          case 0xA00104u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            v45 = (const void *)off_5C5EBC;
            v31 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v31))->CScreenMode::AudioSetPosition(v45, 1);
            this->StateUI::RefreshFromAtts();
            (((MainEquipUI *)*(MainEquipUI **)&this[1].m_par[1][0]._texName[172]))->MainEquipUI::HandleMessage(2);
            goto LABEL_60;
          case 0xA00105u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            v46 = (const void *)off_5C5EBC;
            v32 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v32))->CScreenMode::AudioSetPosition(v46, 1);
            this->StateUI::RefreshFromAtts();
            (((MainEquipUI *)*(MainEquipUI **)&this[1].m_par[1][0]._texName[172]))->MainEquipUI::HandleMessage(1);
            goto LABEL_60;
          case 0xA00106u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            v47 = (const void *)off_5C5EBC;
            v33 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v33))->CScreenMode::AudioSetPosition(v47, 1);
            this->StateUI::RefreshFromAtts();
            (((MainEquipUI *)*(MainEquipUI **)&this[1].m_par[1][0]._texName[172]))->MainEquipUI::HandleMessage(5);
            goto LABEL_60;
          case 0xA00107u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            v48 = (const void *)off_5C5EBC;
            v34 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v34))->CScreenMode::AudioSetPosition(v48, 1);
            this->StateUI::RefreshFromAtts();
            (((MainEquipUI *)*(MainEquipUI **)&this[1].m_par[1][0]._texName[172]))->MainEquipUI::HandleMessage(6);
            goto LABEL_60;
          case 0xA00109u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            v50 = (const void *)off_5C5EBC;
            v36 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v36))->CScreenMode::AudioSetPosition(v50, 1);
            this->StateUI::RefreshFromAtts();
            (((MainEquipUI *)*(MainEquipUI **)&this[1].m_par[1][0]._texName[172]))->MainEquipUI::HandleMessage(7);
            goto LABEL_60;
          case 0xA00110u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
            {
LABEL_55:
              v49 = (const void *)off_5C5EC8;
              v35 = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)v35))->CScreenMode::AudioSetPosition(v49, 1);
              result = 1;
            }
            else
            {
              v51 = (const void *)off_5C5EBC;
              v37 = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)v37))->CScreenMode::AudioSetPosition(v51, 1);
              this->StateUI::RefreshFromAtts();
              (((MainEquipUI *)*(MainEquipUI **)&this[1].m_par[1][0]._texName[172]))->MainEquipUI::HandleMessage(9);
LABEL_60:
              result = 1;
            }
            break;
          default:
            goto LABEL_60;
        }
      }
      break;
    case 1002:
      v38 = *(_DWORD *)&this->m_State[1].m_text[8];
      if ( nMsg == (&off_56BA08)[v38] )
      {
        (**((void ( ***)(int *, _DWORD))&this->m_RoleState[5].m_Head.m_bfocus + 38 * v38))((int *)(&this->m_RoleState[5].m_Head.m_bfocus + 38 * v38), (_DWORD)(0));
        (**(void ( ***)(char *, int))&this->m_RoleState[4].m_ShenVal.m_text[344
                                                                                    * *(_DWORD *)&this->m_State[1].m_text[8]
                                                                                    + 8])((char *)(&this->m_RoleState[4].m_ShenVal.m_text[344 * *(_DWORD *)&this->m_State[1].m_text[8] + 8]), (int)(1));
        LOBYTE(this->m_Frame.m_bfocus) = 1;
        result = 1;
      }
      else
      {
        switch ( (unsigned int)nMsg )
        {
          case 0xA00102u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 0;
            if ( LOBYTE(this->m_RoleState[4].m_ShenBar.m_step) )
              goto LABEL_80;
            LoadStateUIRenderTarget(0);
            result = 1;
            break;
          case 0xA00103u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 1;
            if ( BYTE1(this->m_RoleState[4].m_ShenBar.m_step) )
              goto LABEL_80;
            LoadStateUIRenderTarget(1);
            result = 1;
            break;
          case 0xA00104u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 2;
            if ( BYTE2(this->m_RoleState[4].m_ShenBar.m_step) )
              goto LABEL_80;
            LoadStateUIRenderTarget(2);
            result = 1;
            break;
          case 0xA00105u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 3;
            if ( HIBYTE(this->m_RoleState[4].m_ShenBar.m_step) )
              goto LABEL_80;
            LoadStateUIRenderTarget(3);
            result = 1;
            break;
          case 0xA00106u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 5;
            if ( BYTE1(this->m_RoleState[4].m_ShenBar.m_Val) )
              goto LABEL_80;
            LoadStateUIRenderTarget(5);
            result = 1;
            break;
          case 0xA00107u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 6;
            if ( BYTE2(this->m_RoleState[4].m_ShenBar.m_Val) )
              goto LABEL_80;
            LoadStateUIRenderTarget(6);
            result = 1;
            break;
          case 0xA00108u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 4;
            if ( LOBYTE(this->m_RoleState[4].m_ShenBar.m_Val) )
              goto LABEL_80;
            LoadStateUIRenderTarget(4);
            result = 1;
            break;
          case 0xA00109u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 7;
            if ( !HIBYTE(this->m_RoleState[4].m_ShenBar.m_Val) )
              LoadStateUIRenderTarget(7);
            goto LABEL_80;
          default:
LABEL_80:
            result = 1;
            break;
        }
      }
      break;
    case 1003:
      v39 = *(_DWORD *)&this->m_State[1].m_text[8];
      if ( nMsg == (&off_56B97C)[v39] )
      {
        (**((void ( ***)(int *, int))&this->m_RoleState[5].m_Head.m_bfocus + 38 * v39))((int *)(&this->m_RoleState[5].m_Head.m_bfocus + 38 * v39), (int)(1));
        (**(void ( ***)(char *, _DWORD))&this->m_RoleState[4].m_ShenVal.m_text[344
                                                                                       * *(_DWORD *)&this->m_State[1].m_text[8]
                                                                                       + 8])((char *)(&this->m_RoleState[4].m_ShenVal.m_text[344 * *(_DWORD *)&this->m_State[1].m_text[8] + 8]), (_DWORD)(0));
        LOBYTE(this->m_Frame.m_bfocus) = 1;
        result = 1;
      }
      else
      {
        switch ( (unsigned int)nMsg )
        {
          case 0xA00102u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 0;
            LOBYTE(this->m_RoleState[4].m_ShenBar.m_step) = 0;
            result = 1;
            break;
          case 0xA00103u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 1;
            BYTE1(this->m_RoleState[4].m_ShenBar.m_step) = 0;
            result = 1;
            break;
          case 0xA00104u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 2;
            BYTE2(this->m_RoleState[4].m_ShenBar.m_step) = 0;
            result = 1;
            break;
          case 0xA00105u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 3;
            HIBYTE(this->m_RoleState[4].m_ShenBar.m_step) = 0;
            result = 1;
            break;
          case 0xA00106u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 5;
            BYTE1(this->m_RoleState[4].m_ShenBar.m_Val) = 0;
            result = 1;
            break;
          case 0xA00107u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 6;
            BYTE2(this->m_RoleState[4].m_ShenBar.m_Val) = 0;
            result = 1;
            break;
          case 0xA00108u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 4;
            LOBYTE(this->m_RoleState[4].m_ShenBar.m_Val) = 0;
            result = 1;
            break;
          case 0xA00109u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 7;
            HIBYTE(this->m_RoleState[4].m_ShenBar.m_Val) = 0;
            goto LABEL_92;
          default:
            goto LABEL_92;
        }
      }
      break;
    case 1009:
    case 1010:
    case 1013:
LABEL_92:
      result = 1;
      break;
    default:
      result = this->UIWnd::OnMessage(nVal1, (int)nMsg, wParam);
      break;
  }
  return result;
}

// 0x0048A310
int StateUI::SelectSubTab1(unsigned __int8 nTab)
{
  BYTE2(this->m_OutFrameR.m_ppicInfo) = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState(1, nTab);
}

// 0x0048A330
int StateUI::SelectSubTab2(unsigned __int8 nTab)
{
  HIBYTE(this->m_OutFrameR.m_ppicInfo) = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState(2, nTab);
}

// 0x00492850
void StateUI::UpdateRoleTooltip(int nVal)
{
  _BYTE *p_m_mouseoff; // esi
  void (***v4)(_DWORD, _DWORD); // edi
  int v5; // ebx
  void ( ***v6)(int, int); // esi
  void ( ***v7)(_DWORD, int); // esi
  int v8; // ebx
  int v9; // [esp+0x24] [ebp-0x4]

  v9 = 5;
  p_m_mouseoff = (_BYTE *)&this->m_RoleState[4].m_WuLing[4].m_mouseoff;
  do
  {
    (**((void ( ***)(int, _DWORD))p_m_mouseoff - 38))((int)((int)(p_m_mouseoff - 152)), (_DWORD)(0));
    (**(void ( ***)(_BYTE *, _DWORD))p_m_mouseoff)((_BYTE *)(p_m_mouseoff), (_DWORD)(0));
    (**((void ( ***)(int, _DWORD))p_m_mouseoff + 38))((int)((int)(p_m_mouseoff + 152)), (_DWORD)(0));
    (**((void ( ***)(int, _DWORD))p_m_mouseoff + 76))((int)((int)(p_m_mouseoff + 304)), (_DWORD)(0));
    (**((void ( ***)(int, _DWORD))p_m_mouseoff + 114))((int)((int)(p_m_mouseoff + 456)), (_DWORD)(0));
    (**((void ( ***)(int, _DWORD))p_m_mouseoff + 152))((int)((int)(p_m_mouseoff + 608)), (_DWORD)(0));
    v4 = (void ( ***)(_DWORD, _DWORD))(p_m_mouseoff + 2280);
    v5 = 10;
    do
    {
      (**(v4 - 380))(v4 - 380, 0);
      (**v4)((_DWORD)(v4), (_DWORD)(0));
      (*v4[380])(v4 + 380, 0);
      v4 += 38;
      --v5;
    }
    while ( v5 );
    p_m_mouseoff += 9980;
    --v9;
  }
  while ( v9 );
  v6 = (void ( ***)(int, int))((char *)this + 9980 * nVal);
  (*v6[39200])((int)(v6 + 39200), 1);
  (*v6[39238])((int)(v6 + 39238), 1);
  (*v6[39276])((int)(v6 + 39276), 1);
  (*v6[39314])((int)(v6 + 39314), 1);
  (*v6[39352])((int)(v6 + 39352), 1);
  (*v6[39390])((int)(v6 + 39390), 1);
  v7 = v6 + 39808;
  v8 = 10;
  do
  {
    (**(v7 - 380))(v7 - 380, 1);
    (**v7)((_DWORD)((_DWORD)(v7)), (int)(1));
    (*v7[380])(v7 + 380, 1);
    v7 += 38;
    --v8;
  }
  while ( v8 );
  UIScene_LoadRoleSkillData(nVal);
  (((MainEquipUI *)this))->MainEquipUI::UpdateTooltip(nVal) /* [ROWTABLE] */;
}

// 0x00493420
void StateUI::UpdateAttributeDisplay(int arg0, char *pszBuf, float id)
{
  void **v4; // esi
  int v5; // edi
  __int16 v6; // ax
  int v7; // esi
  void *m_pParticleData; // edx
  __int16 v9; // ax
  __int16 v10; // ax
  __int16 v11; // ax
  char *v12; // ebx
  int i; // edi
  char *v14; // edi
  int v15; // [esp-0x4] [ebp-0x398]
  int v16; // [esp-0x4] [ebp-0x398]
  int v17; // [esp-0x4] [ebp-0x398]
  int v18; // [esp-0x4] [ebp-0x398]
  int v19; // [esp-0x4] [ebp-0x398]
  int v20; // [esp-0x4] [ebp-0x398]
  int v21; // [esp-0x4] [ebp-0x398]
  int v22; // [esp-0x4] [ebp-0x398]
  char v23[300]; // [esp+0xC] [ebp-0x388] BYREF
  char v24[300]; // [esp+0x138] [ebp-0x25C] BYREF
  char Buffer[300]; // [esp+0x264] [ebp-0x130] BYREF
  StateUI *v26; // [esp+0x390] [ebp-0x4]
  char *pszBufa; // [esp+0x3A0] [ebp+0xC]
  bool id_3; // [esp+0x3A7] [ebp+0x13]

  v26 = this;
  memset(Buffer, 0, sizeof(Buffer));
  memset(v24, 0, sizeof(v24));
  memset(v23, 0, sizeof(v23));
  v4 = (void **)(&this->m_DlgEx.pCallbackVtable2 + 4);
  v5 = 5;
  do
  {
    (*(void ( **)(void **, _DWORD))*v4)(v4, 0);
    v4 += 2495;
    --v5;
  }
  while ( v5 );
  if ( !pszBuf )
  {
    v7 = 1408 * arg0;
    sprintf(
      Buffer,
      "%s %d",
      (const char *)&g_szRoleName1,
      *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + 352 * arg0));
    sprintf(v23, "          (%d)", *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * arg0 + 1));
    sprintf(
      &Buffer[30],
      "%s %d",
      (const char *)&g_szRoleName0,
      *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixB + 352 * arg0));
    sprintf(&v23[30], "          (%d)", *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * arg0));
    sprintf(
      &Buffer[60],
      "%s %d",
      (const char *)&g_szRoleName2,
      *(&g_RoleSlotBuf.m_partyActor.m_nMatrixParam + 352 * arg0));
    sprintf(&v23[60], "          (%d)", *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * arg0 + 2));
    sprintf(
      &Buffer[90],
      "%s %d",
      (const char *)&g_szRoleName3,
      *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamA + 352 * arg0));
    sprintf(&v23[90], "          (%d)", *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * arg0 + 3));
    goto LABEL_31;
  }
  v6 = *((_WORD *)pszBuf + 326);
  if ( v6 <= 0 )
  {
    v7 = 1408 * arg0;
    if ( v6 >= 0 )
    {
      sprintf(
        Buffer,
        "%s %d",
        (const char *)&g_szRoleName1,
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + 352 * arg0));
      sprintf(v23, "          (%d)", *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * arg0 + 1));
    }
    else
    {
      sprintf(
        Buffer,
        "%s %d",
        (const char *)&g_szRoleName1,
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + 352 * arg0));
      sprintf(v24, "      %d", *((__int16 *)pszBuf + 326));
      sprintf(v23, "          (%d)", *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * arg0 + 1));
    }
  }
  else
  {
    v7 = 1408 * arg0;
    sprintf(
      Buffer,
      "%s %d",
      (const char *)&g_szRoleName1,
      *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + 352 * arg0));
    sprintf(v24, "      +%d", *((__int16 *)pszBuf + 326));
    sprintf(v23, "          (%d)", *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * arg0 + 1));
  }
  if ( id == 0.0f && *(_DWORD *)pszBuf == 6603 && !arg0 )
  {
    if ( g_nUpdateInterval < 35 )
      g_nUpdateInterval = 35;
    sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixB);
    sprintf(&v24[30], "      +%d", g_nUpdateInterval);
    m_pParticleData = (void *)g_RoleSlotBuf.m_partyActor.m_pParticleData;
    goto LABEL_19;
  }
  v9 = *((_WORD *)pszBuf + 325);
  v15 = *(_DWORD *)(&g_RoleSlotBuf.m_partyActor.m_fMatrixB + v7);
  if ( v9 > 0 )
  {
    sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, v15);
    sprintf(&v24[30], "      +%d", *((__int16 *)pszBuf + 325));
LABEL_18:
    m_pParticleData = (void *)*(void **)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + v7);
LABEL_19:
    sprintf(&v23[30], "          (%d)", m_pParticleData);
    goto LABEL_20;
  }
  if ( v9 < 0 )
  {
    sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, v15);
    sprintf(&v24[30], "      %d", *((__int16 *)pszBuf + 325));
    goto LABEL_18;
  }
  sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, v15);
  sprintf(&v23[30], "          (%d)", *(void **)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + v7));
LABEL_20:
  v10 = *((_WORD *)pszBuf + 327);
  v16 = *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_nMatrixParam + v7);
  if ( v10 > 0 )
  {
    sprintf(&Buffer[60], "%s %d", (const char *)&g_szRoleName2, v16);
    sprintf(&v24[60], "      +%d", *((__int16 *)pszBuf + 327));
LABEL_27:
    sprintf(&v23[60], "          (%d)", *(void **)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + v7 + 8));
    goto LABEL_28;
  }
  if ( v10 < 0 )
  {
    sprintf(&Buffer[60], "%s %d", (const char *)&g_szRoleName2, v16);
    sprintf(&v24[60], "      %d", *((__int16 *)pszBuf + 327));
    goto LABEL_27;
  }
  sprintf(&Buffer[60], "%s %d", (const char *)&g_szRoleName2, v16);
  sprintf(&v23[60], "          (%d)", *(void **)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + v7 + 8));
LABEL_28:
  v11 = *((_WORD *)pszBuf + 328);
  v17 = *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamA + v7);
  if ( v11 <= 0 )
  {
    if ( v11 >= 0 )
    {
      sprintf(&Buffer[90], "%s %d", (const char *)&g_szRoleName3, v17);
      sprintf(&v23[90], "          (%d)", *(void **)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + v7 + 12));
    }
    else
    {
      sprintf(&Buffer[90], "%s %d", (const char *)&g_szRoleName3, v17);
      sprintf(&v24[90], "      %d", *((__int16 *)pszBuf + 328));
      sprintf(&v23[90], "          (%d)", *(void **)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + v7 + 12));
    }
  }
  else
  {
    sprintf(&Buffer[90], "%s %d", (const char *)&g_szRoleName3, v17);
    sprintf(&v24[90], "      +%d", *((__int16 *)pszBuf + 328));
    sprintf(&v23[90], "          (%d)", *(void **)((char *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + v7 + 12));
  }
LABEL_31:
  sprintf(
    &Buffer[120],
    "%s %d",
    (const char *)&g_szSceneName,
    *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z + v7));
  lstrcpyA((char *)&v24[120], unk_C10D38);
  lstrcpyA((char *)&v23[120], unk_C10D38);
  if ( !pszBuf )
  {
    sprintf(
      &Buffer[150],
      "%s %d",
      (const char *)g_bSlotFlag,
      *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamB + v7));
    sprintf(
      &Buffer[180],
      "%s %d",
      (const char *)&g_bSlotFlag[256],
      *((_DWORD *)&v26[1].m_par[9][3]._element.m_textx + 213 * arg0));
    sprintf(&Buffer[210], "%s %d", byte_DC3F3C, *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamC + v7));
    sprintf(
      &Buffer[240],
      "%s %d",
      (const char *)&g_bSlotFlag[512],
      *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixF + v7));
    sprintf(&Buffer[270], "%s %d", byte_DC403C, *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_Actor + v7));
    goto LABEL_68;
  }
  id_3 = *(_DWORD *)pszBuf == 6603;
  if ( *(_DWORD *)pszBuf == 6603 && !g_nFiveNimbusCount )
  {
    sprintf(&Buffer[150], "%s %d", g_bSlotFlag, *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamB + v7));
LABEL_42:
    sprintf(&v24[150], "      +%d", 1);
    goto LABEL_43;
  }
  v18 = *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamB + v7);
  if ( pszBuf[619] )
  {
    sprintf(&Buffer[150], "%s %d", g_bSlotFlag, v18);
    goto LABEL_42;
  }
  sprintf(&Buffer[150], "%s %d", (const char *)g_bSlotFlag, v18);
LABEL_43:
  if ( id_3 && g_nFiveNimbusCount == 1 )
  {
    v19 = *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixE + v7);
  }
  else
  {
    v19 = *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixE + v7);
    if ( !pszBuf[620] )
    {
      sprintf(&Buffer[180], "%s %d", (const char *)&g_bSlotFlag[256], v19);
      goto LABEL_47;
    }
  }
  sprintf(&Buffer[180], "%s %d", &g_bSlotFlag[256], v19);
  sprintf(&v24[180], "      +%d", 1);
LABEL_47:
  if ( id_3 && g_nFiveNimbusCount == 2 )
  {
    sprintf(&Buffer[210], "%s %d", byte_DC3F3C, *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamC + v7));
LABEL_55:
    sprintf(&v24[210], "      +%d", 1);
    goto LABEL_56;
  }
  v20 = *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixParamC + v7);
  if ( pszBuf[622] )
  {
    sprintf(&Buffer[210], "%s %d", byte_DC3F3C, v20);
    goto LABEL_55;
  }
  sprintf(&Buffer[210], "%s %d", byte_DC3F3C, v20);
LABEL_56:
  if ( id_3 && g_nFiveNimbusCount == 3 )
  {
    v21 = *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixF + v7);
  }
  else
  {
    v21 = *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_fMatrixF + v7);
    if ( !pszBuf[621] )
    {
      sprintf(&Buffer[240], "%s %d", (const char *)&g_bSlotFlag[512], v21);
      goto LABEL_60;
    }
  }
  sprintf(&Buffer[240], "%s %d", &g_bSlotFlag[512], v21);
  sprintf(&v24[240], "      +%d", 1);
LABEL_60:
  if ( id_3 && g_nFiveNimbusCount == 4 )
  {
    sprintf(&Buffer[270], "%s %d", byte_DC403C, *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_Actor + v7));
    sprintf(&v24[270], "      +%d", 1);
  }
  else
  {
    v22 = *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_Actor + v7);
    if ( pszBuf[623] )
    {
      sprintf(&Buffer[270], "%s %d", byte_DC403C, v22);
      sprintf(&v24[270], "      +%d", 1);
    }
    else
    {
      sprintf(&Buffer[270], "%s %d", byte_DC403C, v22);
    }
  }
LABEL_68:
  pszBufa = (char *)this + 9980 * arg0;
  v12 = (char *)(pszBufa + 159232);
  for ( i = 0; i < 300; i += 30 )
  {
    AllocObject(v12);
    AllocObject(v12 + 1520);
    SetEnable((UICaption *)v12);
    SetEnable((UICaption *)(v12 - 1520));
    SetEnable((UICaption *)(v12 + 1520));
    v12 += 152;
  }
  v14 = (char *)(&this->m_isJusticeBook + 32);
  sprintf(
    (char *const)&this->m_isJusticeBook + 32,
    "%d/%d",
    (int)*((float *)pszBufa + 38866),
    *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v7));
  SetEnable((UICaption *)(pszBufa + 155552));
  sprintf(
    v14,
    "%d/%d",
    (int)*((float *)pszBufa + 39140),
    *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v7 + 4));
  SetEnable((UICaption *)(pszBufa + 156648));
  sprintf(
    v14,
    "%d/%d",
    (int)*((float *)pszBufa + 39003),
    *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v7 + 8));
  SetEnable((UICaption *)(pszBufa + 156100));
}

// 0x004940F0
void StateUI::UpdateScrollBars()
{
  int *v1; // esi
  int *p_m_needscriptdel; // edi
  float fValue; // [esp+0x0] [ebp-0x30]
  float fValuea; // [esp+0x0] [ebp-0x30]
  float fValueb; // [esp+0x0] [ebp-0x30]
  float fValuec; // [esp+0x0] [ebp-0x30]
  float fValued; // [esp+0x0] [ebp-0x30]
  float fValuee; // [esp+0x0] [ebp-0x30]
  _BYTE *v10; // [esp+0x2C] [ebp-0x4]

  v10 = (char *)&this->m_Frame.m_bfocus + 1;
  v1 = (int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2];
  p_m_needscriptdel = (int *)&this->m_RoleState[4].m_WuLing[1].m_childs.m_needscriptdel;
  do
  {
    if ( *v10 )
    {
      (((RoleSystem *)(v1 - 243)))->RoleSystem::RecalcAggregatedStats(0);
      fValue = (float)*(v1 - 12);
      (((UIScrollBar *)(p_m_needscriptdel - 274)))->UIScrollBar::SetRange(fValue);
      fValuea = (float)*(v1 - 11);
      (((UIScrollBar *)p_m_needscriptdel))->UIScrollBar::SetRange(fValuea);
      fValueb = (float)*(v1 - 10);
      (((UIScrollBar *)(p_m_needscriptdel - 137)))->UIScrollBar::SetRange(fValueb);
      fValuec = (float)*v1;
      (((UIProgressBar *)(p_m_needscriptdel - 274)))->UIProgressBar::FindChildByName(fValuec);
      fValued = (float)v1[1];
      (((UIProgressBar *)p_m_needscriptdel))->UIProgressBar::FindChildByName(fValued);
      fValuee = (float)v1[2];
      (((UIProgressBar *)(p_m_needscriptdel - 137)))->UIProgressBar::FindChildByName(fValuee);
      sprintf((char *const)&this->m_isJusticeBook + 32, "%d/%d", (int)*((float *)p_m_needscriptdel - 235), *(v1 - 12));
      SetEnable((UICaption *)(p_m_needscriptdel - 213));
      sprintf((char *const)&this->m_isJusticeBook + 32, "%d/%d", (int)*((float *)p_m_needscriptdel + 39), *(v1 - 11));
      SetEnable((UICaption *)(p_m_needscriptdel + 61));
      sprintf((char *const)&this->m_isJusticeBook + 32, "%d/%d", (int)*((float *)p_m_needscriptdel - 98), *(v1 - 10));
      SetEnable((UICaption *)(p_m_needscriptdel - 76));
    }
    v1 += 352;
    p_m_needscriptdel += 2495;
    ++v10;
  }
  while ( (int)v1 < (int)dword_C062EC );
}

// 0x004945E0
int StateUI::ForwardToBigMap(char pData)
{
  BYTE2(this->m_Frame.m_bfocus) = pData;
  return (((UIBigMap *)this))->UIBigMap::SetEntryVisible(1, pData);
}

// 0x00494600
int StateUI::SelectBigMapTab2(char nTab)
{
  HIBYTE(this->m_Frame.m_bfocus) = nTab;
  return (((UIBigMap *)this))->UIBigMap::SetEntryVisible(2, nTab);
}

// 0x004998E0
int StateUI::ShowPage()
{
  _BYTE *p_m_benable_snd; // ecx

  if ( g_bRoleFlag1 )
  {
    p_m_benable_snd = (_BYTE *)&this->stp_Prop.m_benable_snd;
  }
  else
  {
    (((PalScript *)&this->stp_Prop.m_benable_snd))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    p_m_benable_snd = (_BYTE *)&this->stp_Prop.m_benable_snd;
  }
  sub_445E50((int)p_m_benable_snd);
  if ( !g_bRoleFlag2 )
    (((PalScript *)&this->stp_BattleArray.m_benable_snd))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_BattleArray.m_benable_snd);
  (((PalScript *)&this->stp_Equip.m_benable_snd))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnProp.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_Equip.m_benable_snd);
  sub_445E50((int)&this->stp_BarR.m_disablepic);
  sub_445E50((int)&this->stp_State.m_benable_snd);
  sub_445E50((int)&this->stp_Magic.m_benable_snd);
  sub_445E50((int)&this->stp_TaskBook.m_benable_snd);
  sub_445E50((int)&this->stp_System.m_benable_snd);
  return sub_445E50((int)&this->stp_Exit.m_benable_snd);
}

// 0x0049A360
void StateUI::DisplayCaption(int nVal)
{
  int *p_m_bvisible; // esi
  void (***v4)(_DWORD, _DWORD); // edi
  int v5; // ebx
  char *v6; // edi
  int v7; // ebp
  void ( ***v8)(_DWORD, int); // esi
  int v9; // [esp+0x5C] [ebp-0x8]

  p_m_bvisible = (int *)&this->m_Alignment.m_bvisible;
  v9 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*(p_m_bvisible - 38))(p_m_bvisible - 38, 0);
    (*(void ( **)(int *, _DWORD))*p_m_bvisible)(p_m_bvisible, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[38])(p_m_bvisible + 38, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[76])(p_m_bvisible + 76, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[114])(p_m_bvisible + 114, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[152])(p_m_bvisible + 152, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[190])(p_m_bvisible + 190, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[228])(p_m_bvisible + 228, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[266])(p_m_bvisible + 266, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[304])(p_m_bvisible + 304, 0);
    (*(void ( **)(int *, _DWORD))p_m_bvisible[342])(p_m_bvisible + 342, 0);
    v4 = (void ( ***)(_DWORD, _DWORD))(p_m_bvisible + 380);
    v5 = 5;
    do
    {
      (**v4)((_DWORD)(v4), (_DWORD)(0));
      v4 += 38;
      --v5;
    }
    while ( v5 );
    p_m_bvisible += 1223;
    --v9;
  }
  while ( v9 );
  v6 = (char *)this + 4892 * nVal;
  v7 = 5;
  v8 = (void ( ***)(_DWORD, int))(v6 + 160116);
  do
  {
    (**v8)((_DWORD)((_DWORD)(v8)), (int)(1));
    v8 += 38;
    --v7;
  }
  while ( v7 );
  (**((void ( ***)(int, int))v6 + 39611))((int)((int)(v6 + 158444)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39649))((int)((int)(v6 + 158596)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39687))((int)((int)(v6 + 158748)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39725))((int)((int)(v6 + 158900)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39763))((int)((int)(v6 + 159052)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39801))((int)((int)(v6 + 159204)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39839))((int)((int)(v6 + 159356)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39877))((int)((int)(v6 + 159508)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39915))((int)((int)(v6 + 159660)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39953))((int)((int)(v6 + 159812)), (int)(1));
  (**((void ( ***)(int, int))v6 + 39991))((int)((int)(v6 + 159964)), (int)(1));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szRoleName1,
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * nVal + 1));
  SetEnable((UICaption *)(v6 + 159356));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szRoleName0,
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * nVal));
  SetEnable((UICaption *)(v6 + 159508));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szRoleName2,
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * nVal + 2));
  SetEnable((UICaption *)(v6 + 159660));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szRoleName3,
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * nVal + 3));
  SetEnable((UICaption *)(v6 + 159812));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szSceneName,
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z + 352 * nVal));
  SetEnable((UICaption *)(v6 + 159964));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)g_bSlotFlag,
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * nVal + 4));
  SetEnable((UICaption *)(v6 + 160116));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_bSlotFlag[256],
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pParticleData + 352 * nVal + 5));
  SetEnable((UICaption *)(v6 + 160268));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    byte_DC3F3C,
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * nVal]);
  SetEnable((UICaption *)(v6 + 160420));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_bSlotFlag[512],
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fAnimDelta + 352 * nVal));
  SetEnable((UICaption *)(v6 + 160572));
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    byte_DC403C,
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * nVal + 1]);
  SetEnable((UICaption *)(v6 + 160724));
}

// 0x0049AC70
int StateUI::UpdateScrollValues()
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int result; // eax
  float fValue; // [esp+0x0] [ebp-0x1C]
  float fValuea; // [esp+0x0] [ebp-0x1C]
  float fValueb; // [esp+0x0] [ebp-0x1C]
  float fValuec; // [esp+0x0] [ebp-0x1C]
  float fValued; // [esp+0x0] [ebp-0x1C]
  float fValuee; // [esp+0x0] [ebp-0x1C]

  *((_DWORD *)&this->m_isJusticeBook + 6) = 0;
  do
  {
    v2 = *((_DWORD *)&this->m_isJusticeBook + 6);
    if ( *((_BYTE *)&this->m_OutFrameT.m_rect.top + v2 + 1) )
    {
      fValue = (float)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * v2);
      (((UIScrollBar *)(&this->m_RoleState[4].m_WuLing[4].m_mouseoff + 4892 * v2)))->UIScrollBar::SetRange(fValue);
      v3 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValuea = (float)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * v3 + 1);
      (((UIScrollBar *)(&this->m_State[0].m_pbkInfo + 1223 * v3)))->UIScrollBar::SetRange(fValuea);
      v4 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValueb = (float)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * v4 + 2);
      (((UIScrollBar *)(&this->m_RoleState[5].m_Name.m_bfocus + 1223 * v4)))->UIScrollBar::SetRange(fValueb);
      v5 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValuec = (float)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * v5 + 2];
      (((UIProgressBar *)(&this->m_RoleState[4].m_WuLing[4].m_mouseoff + 4892 * v5)))->UIProgressBar::FindChildByName(fValuec);
      v6 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValued = (float)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * v6 + 3];
      (((UIProgressBar *)(&this->m_State[0].m_pbkInfo + 1223 * v6)))->UIProgressBar::FindChildByName(fValued);
      v7 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValuee = (float)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * v7 + 4];
      (((UIProgressBar *)(&this->m_RoleState[5].m_Name.m_bfocus + 1223 * v7)))->UIProgressBar::FindChildByName(fValuee);
      sprintf(
        (char *const)&this->m_isJusticeBook + 36,
        "%d/%d",
        (int)*((float *)&this->m_RoleState[4].m_FWSY.m_FVF + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)&this->m_isJusticeBook + 6)));
      SetEnable((UICaption *)(&this->m_RoleState[5].m_Headbk.m_bfocus + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)));
      sprintf(
        (char *const)&this->m_isJusticeBook + 36,
        "%d/%d",
        (int)*((float *)&this->m_State[1].m_ppic + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)&this->m_isJusticeBook + 6) + 1));
      SetEnable((UICaption *)(&this->m_State[2].m_bvisible + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)));
      sprintf(
        (char *const)&this->m_isJusticeBook + 36,
        "%d/%d",
        (int)*((float *)&this->m_RoleState[5].m_Jing.pDebugTex + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)&this->m_isJusticeBook + 6) + 2));
      SetEnable((UICaption *)(&this->m_RoleState[5].m_JingBar.m_fontcolor
                            + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)));
    }
    result = *((_DWORD *)&this->m_isJusticeBook + 6) + 1;
    *((_DWORD *)&this->m_isJusticeBook + 6) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0049E860
int StateUI::SelectXJTMTab1(unsigned __int8 nTab)
{
  BYTE2(this->m_OutFrameT.m_rect.top) = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState2(1, nTab);
}

// 0x0049E880
int StateUI::SelectXJTMTab2(unsigned __int8 nTab)
{
  HIBYTE(this->m_OutFrameT.m_rect.top) = nTab;
  return (((UITitle_XJTM *)this))->UITitle_XJTM::SetMonsterState2(2, nTab);
}

// 0x004A2BD0
UIWnd * StateUI::GetChildPtr(int index)
{
  int v2; // edi
  int v4; // ecx
  char *v5; // edi
  int v6; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // ecx
  UIWnd *result; // eax
  int v12; // [esp+0x20] [ebp-0x20]
  int v13; // [esp+0x30] [ebp-0x10] BYREF
  int v14; // [esp+0x34] [ebp-0xC]
  _DWORD v15[2]; // [esp+0x38] [ebp-0x8] BYREF
  int *v16; // [esp+0x48] [ebp+0x8]
  int v17; // [esp+0x50] [ebp+0x10]

  if ( index <= 5 )
  {
    v12 = v2;
    v4 = (unsigned long)*v16;
    v14 = (unsigned long)v16[1];
    v15[1] = v14 + 12;
    v13 = v4;
    v15[0] = v4 + 85;
    v5 = (char *)this + 3788 * index;
    (*(void ( **)(char *, int, int *, StateUI *, int))(*((_DWORD *)v5 + 38937) + 16))(
      v5 + 155748,
      g_ComposeUIChildIDs[index],
      &v13,
      this,
      v12);
    (((UIScene *)(v5 + 155748)))->UIScene::GetChildCount();
    (((UIScene *)(v5 + 155748)))->UIScene::GetChildAt();
    *((_DWORD *)v5 + 38955) = 1;
    v5[155918] = -30;
    v5[155917] = -51;
    v5[155916] = 58;
    v5[155919] = -1;
    sub_43FD90((float *)v5 + 38937, 4);
    (((UIProgressBar *)(v5 + 155748)))->UIProgressBar::GetWidth(-4);
    sub_43FDB0((float *)v5 + 38937, 1);
    (((UIProgressBar *)(v5 + 155748)))->UIProgressBar::GetPosition(-3);
    (*(void ( **)(char *, int, _DWORD *, StateUI *))(*((_DWORD *)v5 + 39211) + 16))(
      v5 + 156844,
      g_ComposeUIChildIDs[index],
      (_DWORD *)(v15),
      this);
    (((UIScene *)(v5 + 156844)))->UIScene::GetChildCount();
    (((UIScene *)(v5 + 156844)))->UIScene::GetChildAt();
    *((_DWORD *)v5 + 39229) = 1;
    v5[157014] = -30;
    v5[157013] = -51;
    v5[157012] = 58;
    v5[157015] = -1;
    sub_43FD90((float *)v5 + 39211, 4);
    (((UIProgressBar *)(v5 + 156844)))->UIProgressBar::GetWidth(-4);
    sub_43FDB0((float *)v5 + 39211, 1);
    (((UIProgressBar *)(v5 + 156844)))->UIProgressBar::GetPosition(-3);
    (*(void ( **)(char *, int, _DWORD *, StateUI *))(*((_DWORD *)v5 + 39074) + 16))(
      v5 + 156296,
      g_ComposeUIChildIDs[index],
      (_DWORD *)(v15),
      this);
    (((UIScene *)(v5 + 156296)))->UIScene::GetChildCount();
    (((UIScene *)(v5 + 156296)))->UIScene::GetChildAt();
    *((_DWORD *)v5 + 39092) = 1;
    v5[156466] = -30;
    v5[156465] = -51;
    v5[156464] = 58;
    v5[156467] = -1;
    sub_43FD90((float *)v5 + 39074, 4);
    (((UIProgressBar *)(v5 + 156296)))->UIProgressBar::GetWidth(-4);
    sub_43FDB0((float *)v5 + 39074, 1);
    (((UIProgressBar *)(v5 + 156296)))->UIProgressBar::GetPosition(-3);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v5 + 38998) + 16))(
      v5 + 155992,
      g_ComposeUIChildIDs[index],
      v17,
      this);
    AllocObject(v5 + 155992);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v5 + 39272) + 16))(
      v5 + 157088,
      g_ComposeUIChildIDs[index],
      v17,
      this);
    AllocObject(v5 + 157088);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v5 + 39135) + 16))(
      v5 + 156540,
      g_ComposeUIChildIDs[index],
      v17,
      this);
    AllocObject(v5 + 156540);
    (*(void ( **)(char *, int))(*((_DWORD *)v5 + 38785) + 16))(v5 + 155140, g_ComposeUIChildIDs[index]);
    LOBYTE(v6) = g_bDebugMode;
    (((UIPushButton *)(v5 + 155140)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\HeadBk.tga", v6);
    v7 = (*(int ( **)(char *, int, int, StateUI *))(*((_DWORD *)v5 + 38823) + 16))(
           v5 + 155292,
           g_ComposeUIChildIDs[index],
           v17,
           this);
    LOBYTE(v7) = g_bDebugMode;
    (((UIPushButton *)(v5 + 155292)))->UIPushButton::CreateFromTemplate(&"UI\\GameMainUI\\Communal\\RoleHead00.tga"[256 * index], v7);
    v8 = *((_DWORD *)v5 + 38861);
    v5 += 155444;
    (*(void ( **)(char *, int, int, StateUI *))(v8 + 16))(v5, g_ComposeUIChildIDs[index], v17, this);
    LOBYTE(v9) = g_bDebugMode;
    (((UIPushButton *)v5))->UIPushButton::CreateFromTemplate((void *)(0x56F018)[index], v9);
    return (UIWnd *)(((UIScene *)v5))->UIScene::SetShow(0);
  }
  return result;
}

// 0x004A2F90
UIWnd * StateUI::FindChild(int id)
{
  int v2; // ebp
  char *v4; // ebp
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  UIWnd *result; // eax
  int v9; // [esp+0x64] [ebp-0x10]
  int v10; // [esp+0x7C] [ebp+0x8]

  if ( id <= 5 )
  {
    v9 = v2;
    v4 = (char *)this + 3788 * id;
    v5 = (*(int ( **)(char *, int, int, StateUI *, int))(*((_DWORD *)v4 + 39310) + 16))(
           v4 + 157240,
           g_ComposeUIChildIDs[id],
           v10,
           this,
           v9);
    LOBYTE(v5) = g_bDebugMode;
    (((UIPushButton *)(v4 + 157240)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\State\\Shade.tga", v5);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39348) + 16))(
      v4 + 157392,
      g_ComposeUIChildIDs[id],
      v10,
      this);
    LOBYTE(v6) = g_bDebugMode;
    (((UIPushButton *)(v4 + 157392)))->UIPushButton::CreateFromTemplate(&"UI\\GameMainUI\\State\\Portrait0.tga"[256 * id], v6);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39386) + 16))(
      v4 + 157544,
      g_ComposeUIChildIDs[id],
      v10,
      this);
    (((UIScene *)(v4 + 157544)))->UIScene::SetShow(0);
    AllocObject(v4 + 157544);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39424) + 16))(
      v4 + 157696,
      g_ComposeUIChildIDs[id],
      v10,
      this);
    (((UIScene *)(v4 + 157696)))->UIScene::SetShow(0);
    AllocObject(v4 + 157696);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39462) + 16))(
      v4 + 157848,
      g_ComposeUIChildIDs[id],
      v10,
      this);
    (((UIScene *)(v4 + 157848)))->UIScene::SetShow(0);
    AllocObject(v4 + 157848);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39500) + 16))(
      v4 + 158000,
      g_ComposeUIChildIDs[id],
      v10,
      this);
    (((UIScene *)(v4 + 158000)))->UIScene::SetShow(0);
    AllocObject(v4 + 158000);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39538) + 16))(
      v4 + 158152,
      g_ComposeUIChildIDs[id],
      v10,
      this);
    (((UIScene *)(v4 + 158152)))->UIScene::SetShow(0);
    AllocObject(v4 + 158152);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39614) + 16))(
      v4 + 158456,
      g_ComposeUIChildIDs[id],
      v10,
      this);
    (((UIScene *)(v4 + 158456)))->UIScene::SetShow(0);
    AllocObject(v4 + 158456);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39576) + 16))(
      v4 + 158304,
      g_ComposeUIChildIDs[id],
      v10,
      this);
    (((UIScene *)(v4 + 158304)))->UIScene::SetShow(0);
    AllocObject(v4 + 158304);
    v7 = *((_DWORD *)v4 + 39652);
    v4 += 158608;
    (*(void ( **)(char *, int))(v7 + 16))(v4, g_ComposeUIChildIDs[id]);
    (((UIScene *)v4))->UIScene::SetShow(0);
    return (UIWnd *)AllocObject(v4);
  }
  return result;
}

// 0x004B2470
int StateUI::SaveData()
{
  char *v1; // ebp
  unsigned int *p_m_id; // edi
  Actor *SaveDataManager; // eax
  unsigned int *v4; // esi
  int i; // ebp
  int v6; // eax
  int v7; // eax
  __int64 v8; // rax
  int v9; // esi
  int v10; // ebx
  int v11; // ebp
  unsigned int *v12; // esi
  int v13; // ecx
  int v14; // ecx
  int result; // eax
  int v16; // [esp-0x4] [ebp-0x170]
  int v17; // [esp+0x10] [ebp-0x15C]
  unsigned int *v18; // [esp+0x14] [ebp-0x158]
  float v19; // [esp+0x18] [ebp-0x154]
  char v20[5]; // [esp+0x1C] [ebp-0x150]
  char v21[67]; // [esp+0x21] [ebp-0x14B] BYREF
  int v22; // [esp+0x64] [ebp-0x108]
  char Buffer[257]; // [esp+0x68] [ebp-0x104] BYREF
  __int16 v24; // [esp+0x169] [ebp-0x3]
  char v25; // [esp+0x16B] [ebp-0x1]

  memset(Buffer, 0, sizeof(Buffer));
  v1 = 0;
  v24 = 0;
  v25 = 0;
  v17 = 0;
  p_m_id = (unsigned int *)&this->m_Alignment.m_id;
  while ( 1 )
  {
    SaveDataManager = (Actor *)GetSaveDataManager();
    if ( (((Actor *)SaveDataManager))->Actor::LoadSaveData(v1) )
    {
      v8 = (__int64)v19;
      v9 = (int)v8 / 3600;
      v10 = (int)v8 / 60 % 60;
      v16 = (int)v8 % 60;
      if ( (int)v8 / 3600 < 100 )
        sprintf(Buffer, "%s %02d:%02d:%02d", &dword_DC643C, v9, v10, v16);
      else
        sprintf(Buffer, "%s %03d:%02d:%02d", &dword_DC643C, v9, v10, v16);
      SetEnable((UICaption *)p_m_id);
      sprintf(Buffer, "%s %d", (const char *)&dword_DC633C, v22);
      SetEnable((UICaption *)(p_m_id + 38));
      sprintf(Buffer, "%s %s", (const char *)&dword_DD933C, v21);
      SetEnable((UICaption *)(p_m_id + 304));
      sprintf(Buffer, "Save\\PAL3_%04d.JPG", v1);
      (((UIFrameWnd *)(p_m_id + 266)))->UIFrameWnd::SetTextureByID((int)Buffer);
      (*(void ( **)(unsigned int *, int))p_m_id[266])(p_m_id + 266, 1);
      v11 = 0;
      v12 = (unsigned int *)(p_m_id - 192);
      do
      {
        if ( v20[v11] )
        {
          *((_BYTE *)p_m_id + v11 - 8) = 1;
          (*(void ( **)(unsigned int *, _DWORD))*v12)(v12, 0);
          LOBYTE(v13) = g_bDebugMode;
          (((UIPushButton *)v12))->UIPushButton::CreateFromTemplate((void *)off_56F314[v11], v13);
          (*(void ( **)(unsigned int *, int))*(v12 - 190))(v12 - 190, 1);
          LOBYTE(v14) = g_bDebugMode;
          (((UIPushButton *)(v12 - 190)))->UIPushButton::CreateFromTemplate((void *)off_56F328[v11], v14);
          SetEnable((UICaption *)(v12 + 268));
        }
        else
        {
          (*(void ( **)(unsigned int *, _DWORD))*v12)(v12, 0);
          (*(void ( **)(unsigned int *, _DWORD))*(v12 - 190))(v12 - 190, 0);
          *((_BYTE *)p_m_id + v11 - 8) = 0;
        }
        ++v11;
        v12 += 38;
      }
      while ( v11 < 5 );
    }
    else
    {
      SetEnable((UICaption *)p_m_id);
      SetEnable((UICaption *)(p_m_id + 38));
      SetEnable((UICaption *)(p_m_id + 304));
      (*(void ( **)(unsigned int *, _DWORD))p_m_id[266])(p_m_id + 266, 0);
      v4 = (unsigned int *)(p_m_id - 382);
      v18 = (unsigned int *)(p_m_id - 2);
      for ( i = 0; i < 5; ++i )
      {
        *(_BYTE *)v18 = 0;
        v6 = (*(int ( **)(unsigned int *, _DWORD))v4[190])(v4 + 190, 0);
        LOBYTE(v6) = g_bDebugMode;
        (((UIPushButton *)(v4 + 190)))->UIPushButton::CreateFromTemplate((void *)off_56F314[i], v6);
        v7 = (*(int ( **)(unsigned int *, _DWORD))*v4)(v4, 0);
        LOBYTE(v7) = g_bDebugMode;
        (((UIPushButton *)v4))->UIPushButton::CreateFromTemplate((void *)off_56F328[i], v7);
        SetEnable((UICaption *)(v4 + 458));
        v4 += 38;
        v18 = (unsigned int *)((char *)v18 + 1);
      }
    }
    p_m_id += 890;
    result = ++v17;
    if ( v17 >= 36 )
      break;
    v1 = (char *)v17;
  }
  return result;
}
