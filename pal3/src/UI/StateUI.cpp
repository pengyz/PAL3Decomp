#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/StateUI.h"

// Forward declarations for unnamed functions
void * GetSaveDataManager(void); // from annotations
int sub_43FD90(float *_this, int a2); // from annotations
void sub_43FDB0(float *_this, int a2); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
int sub_484F10(int a2); // from annotations

// Unnamed globals (extern)
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern int dword_D8BBEC;
extern int dword_DC633C;
extern int dword_DC643C;
extern int dword_DD923C;
extern int dword_DD933C;
extern const char * off_56B97C;
extern const char * off_56B990;
extern const char * off_56BA08;
extern void * off_5C5EBC;
extern _SPropValue * off_5C5EC4;
extern void * off_5C5EC8;
extern RoleSystem stru_C059A0;

// 0x0047F390
int StateUI::LoadRoleList()
{
  int result; // eax
  int v3; // edi
  int BufferAt; // eax

  result = ((NPC *)&((RoleSystem *)&stru_C059A0)->m_fMoveTargetY)->GetBufferCount();
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
        BufferAt = ((NPC *)&((RoleSystem *)&stru_C059A0)->m_fMoveTargetY)->GetBufferAt(v3++);
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
  return ((MainEquipUI *)this)->ClearState();
}

// 0x0047F450
int StateUI::CategorizeRoles()
{
  int result; // eax
  int i; // edi
  int v4; // eax

  memset(&this->m_3DObj.m_bvisible, 0, 0x960u);
  result = this->m_3DObj.m_rect.bottom;
  for ( i = 0; i < result; ++i )
  {
    ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(_DWORD *)(this->m_3DObj.m_rect.right + 4 * i));
    switch ( *(_WORD *)(v4 + 4) )
    {
      case 1:
        *((_DWORD *)&this->m_DlgEx + this->m_3DObj.m_childs.m_needscriptdel++ + 337) = *(_DWORD *)v4;
        break;
      case 2:
        *((_DWORD *)&this->m_DlgEx.m_btRc + this->m_3DObj.m_childs.m_nSize++ + 79) = *(_DWORD *)v4;
        break;
      case 3:
        *((_DWORD *)&this->m_DlgEx.76 + (int)this->m_3DObj.m_childs.m_pData++ + 18) = *(_DWORD *)v4;
        break;
      case 4:
        *(&this->m_3DObj.m_bvisible + (int)this->m_3DObj.m_pfather++) = *(_DWORD *)v4;
        break;
      case 5:
        *(&this->m_DlgEx.m_text.m_textx + this->m_3DObj.m_childs.capacity++) = *(_DWORD *)v4;
        break;
      case 6:
        *((_DWORD *)this + this->m_3DObj.m_bcreateok++ + 40529) = *(_DWORD *)v4;
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
    ((void ( *)(gbTexture **, _DWORD))this->m_Head[0].*((_DWORD *)m_pbk2))(&this->m_Head[0].m_pbk2, pData);
    (*(void ( **)(float *, _DWORD))LODWORD(this->m_Head[2].m_ratioh))(&this->m_Head[2].m_ratioh, pData);
    (*(void ( **)(LONG *, _DWORD))this->m_Head[4].m_rect.right)(&this->m_Head[4].m_rect.right, pData);
    (*(void ( **)(int *, _DWORD))this->m_TopFrame.m_childs.capacity)(
      &this->m_TopFrame.m_childs.capacity,
      pData);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->m_LeaveHere.m_texarray.m_ptex[10]->0)(
      // [VTBL_DISPATCH]   &this->m_LeaveHere.m_texarray.m_ptex[10],
      // [VTBL_DISPATCH]   pData);
  }
  result = nVal;
  switch ( nVal )
  {
    case 0:
      result = *((_DWORD *)this + 40681);
      if ( (UIWnd *)result != bFlag )
        result = (*(int ( **)(int *, _DWORD))this->m_Alignment.m_bvisible)(
                   &this->m_Alignment.m_bvisible,
                   pData);
      if ( *((UIWnd **)this + 40682) != bFlag )
        result = ((int ( *)(gbTexture **, _DWORD))this->m_Head[0].*((_DWORD *)m_pbk2))(&this->m_Head[0].m_pbk2, pData);
      if ( *((UIWnd **)this + 40683) != bFlag )
        result = (*(int ( **)(float *, _DWORD))LODWORD(this->m_Head[2].m_ratioh))(
                   &this->m_Head[2].m_ratioh,
                   pData);
      if ( *((UIWnd **)this + 40684) != bFlag )
        result = (*(int ( **)(LONG *, _DWORD))this->m_Head[4].m_rect.right)(
                   &this->m_Head[4].m_rect.right,
                   pData);
      if ( *((UIWnd **)this + 40685) != bFlag )
        result = (*(int ( **)(int *, _DWORD))this->m_TopFrame.m_childs.capacity)(
                   &this->m_TopFrame.m_childs.capacity,
                   pData);
      if ( *((UIWnd **)this + 40686) != bFlag )
        // [VTBL_DISPATCH] result = ((int ( *)(gbTexture **, _DWORD))this->m_LeaveHere.m_texarray.m_ptex[10]->0)(
                   // [VTBL_DISPATCH]   &this->m_LeaveHere.m_texarray.m_ptex[10],
                   // [VTBL_DISPATCH]   pData);
      break;
    case 1:
      v6 = bFlag;
      if ( bFlag )
      {
        if ( *((UIWnd **)this + 40682) != bFlag )
          result = ((int ( *)(gbTexture **, _DWORD))this->m_Head[0].*((_DWORD *)m_pbk2))(&this->m_Head[0].m_pbk2, pData);
        if ( *((UIWnd **)this + 40683) != bFlag )
          result = (*(int ( **)(float *, _DWORD))LODWORD(this->m_Head[2].m_ratioh))(
                     &this->m_Head[2].m_ratioh,
                     pData);
        if ( *((UIWnd **)this + 40684) != bFlag )
          result = (*(int ( **)(LONG *, _DWORD))this->m_Head[4].m_rect.right)(
                     &this->m_Head[4].m_rect.right,
                     pData);
        if ( *((UIWnd **)this + 40685) == bFlag )
          goto LABEL_58;
        goto LABEL_57;
      }
      result = *((_DWORD *)this + 40681);
      if ( result )
        result = (*(int ( **)(int *, _DWORD))this->m_Alignment.m_bvisible)(
                   &this->m_Alignment.m_bvisible,
                   pData);
      break;
    case 2:
      v6 = bFlag;
      if ( bFlag )
      {
        if ( *((UIWnd **)this + 40683) != bFlag )
          result = this->DispatchCmd(2);
        if ( *((UIWnd **)this + 40684) == bFlag )
          goto LABEL_36;
        goto LABEL_35;
      }
      if ( *((_DWORD *)this + 40681) )
        this->DispatchCmd(0);
      result = *((_DWORD *)this + 40682);
      if ( result )
        result = this->DispatchCmd(1);
      break;
    case 3:
      v6 = bFlag;
      if ( bFlag )
      {
        if ( *((UIWnd **)this + 40684) != bFlag )
LABEL_35:
          result = this->DispatchCmd(3);
LABEL_36:
        if ( *((UIWnd **)this + 40685) == v6 )
          goto LABEL_58;
        goto LABEL_57;
      }
      if ( *((_DWORD *)this + 40681) )
        this->DispatchCmd(0);
      if ( *((_DWORD *)this + 40682) )
        this->DispatchCmd(1);
      result = *((_DWORD *)this + 40683);
      if ( result )
        result = this->DispatchCmd(2);
      break;
    case 4:
      v6 = bFlag;
      if ( bFlag )
      {
        if ( *((UIWnd **)this + 40685) != bFlag )
LABEL_57:
          result = this->DispatchCmd(4);
LABEL_58:
        if ( *((UIWnd **)this + 40686) != v6 )
          goto LABEL_72;
      }
      else
      {
        if ( *((_DWORD *)this + 40681) )
          this->DispatchCmd(0);
        if ( *((_DWORD *)this + 40682) )
          this->DispatchCmd(1);
        if ( *((_DWORD *)this + 40683) )
          this->DispatchCmd(2);
        result = *((_DWORD *)this + 40684);
        if ( result )
          result = this->DispatchCmd(3);
      }
      break;
    case 5:
      result = (int)bFlag;
      if ( bFlag )
      {
        if ( *((UIWnd **)this + 40686) != bFlag )
LABEL_72:
          result = this->DispatchCmd(5);
      }
      else
      {
        if ( *((_DWORD *)this + 40681) )
          this->DispatchCmd(0);
        if ( *((_DWORD *)this + 40682) )
          this->DispatchCmd(1);
        if ( *((_DWORD *)this + 40683) )
          this->DispatchCmd(2);
        if ( *((_DWORD *)this + 40684) )
          this->DispatchCmd(3);
        result = *((_DWORD *)this + 40685);
        if ( result )
          result = this->DispatchCmd(4);
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
      result = ((int ( *)(gbTexture **, _DWORD))this->m_Head[0].*((_DWORD *)m_pbk2))(&this->m_Head[0].m_pbk2, v3);
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
      // [VTBL_DISPATCH] result = ((int ( *)(gbTexture **, _DWORD))this->m_LeaveHere.m_texarray.m_ptex[10]->0)(
                 // [VTBL_DISPATCH]   &this->m_LeaveHere.m_texarray.m_ptex[10],
                 // [VTBL_DISPATCH]   v3);
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
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  char *v19; // [esp+0x18] [ebp-0xC]
  int v20; // [esp+0x1C] [ebp-0x8]
  int nVala; // [esp+0x28] [ebp+0x4]

  this->m_RoleState[4].m_JingVal.m_disablepicInfo = 0;
  this->m_RoleState[4].m_JingVal.m_pbk2 = 0;
  nVala = 16;
  *((_BYTE *)&this->m_RoleState[4].m_JingVal.m_disablepicInfo + nVal) = 1;
  v4 = (char *)this + 16 * nVal;
  v5 = (int *)(v4 + 154200);
  v6 = *((_DWORD *)&this->m_RoleState[4].m_JingVal.m_id + 4 * nVal) - *((_DWORD *)v4 + 38550);
  v19 = v4;
  v20 = v6;
  v7 = &this->m_GameMoney.m_rect.bottom + 2336 * nVal;
  while ( 1 )
  {
    ((RenderTarget *)v7)->LoadTexture(szFilename);
    ((RenderTarget *)v7)->SetSize(32);
    fY = rand() % 10 + 58;
    fX = rand() % 10 + 66;
    v8 = rand();
    ((RenderTarget *)v7)->SetColor(v8 % 10 - 6, fX, fY);
    v9 = rand();
    ((RenderTarget *)v7)->SetAlpha(v9 % 55 - 56);
    *((_BYTE *)v7 + 104) = 1;
    ((RenderTarget *)v7)->SetField084();
    ((RenderTarget *)v7)->SetState();
    fYa = (float)*((int *)v4 + 38551);
    fXa = (float)(*v5 + rand() % v6);
    ((RenderTarget *)v7)->UpdateTransform(fXa, fYa);
    ((RenderTarget *)v7)->Render(*v5, v5[1], v5[2]);
    rand();
    *(float *)&fXb = (float)(rand() % 2 + 1);
    ((RenderTarget *)v7)->SetOffset(fXb);
    ((RenderTarget *)v7)->SetScale(0);
    ((RenderTarget *)v7)->SetVisible(1);
    v10 = v7 + 18688;
    v11 = v7;
    v7 += 146;
    result = nVala - 1;
    v12 = nVala == 1;
    qmemcpy(v10, v11, 0x248u);
    --nVala;
    if ( v12 )
      break;
    v4 = v19;
    v6 = v20;
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
    ((ObjectCamera *)top)->Destroy();
    v3 = (void *)this->m_TopFrame.m_rect.top;
    if ( v3 )
    {
      ((ObjectCamera *)this->m_TopFrame.m_rect.top)->GetCameraDirect();
      operator delete(v3);
    }
    this->m_TopFrame.m_rect.top = 0;
  }
  ((UIRoleDialog *)&this->m_State[1].m_text[12])->_UIRoleDialog();
  ((UIFrameWnd *)&this->m_RoleState[4].m_ShenBar.m_color)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_par[0][0].par_radiusY)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_GameMoney.m_rect.bottom)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_GameTime.m_rect.bottom)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->stp_Effect.m_rect.bottom)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->stp_Exit.m_rect.bottom)->Destroy2();
  ((UICaption *)&this->stp_System.m_rect.bottom)->Destroy2();
  ((UICaption *)&this->stp_TaskBook.m_rect.bottom)->Destroy2();
  ((UICaption *)&this->stp_BattleArray.m_rect.bottom)->Destroy2();
  ((UICaption *)&this->stp_Prop.m_rect.bottom)->Destroy2();
  ((UICaption *)&this->stp_Equip.m_rect.bottom)->Destroy2();
  ((UICaption *)&this->stp_Magic.m_rect.bottom)->Destroy2();
  ((UICaption *)&this->stp_State.m_rect.bottom)->Destroy2();
  ((UICaption *)&this->stp_BarL.m_align)->Destroy2();
  ((UIFrameWnd *)&this->m_OutFrameB.m_align)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameL.m_align)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameR.m_align)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameT.m_align)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_TimeMoney.m_align)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Frame.m_align)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x004845F0
int StateUI::IteratePlayerAtts()
{
  int v1; // esi
  int result; // eax

  v1 = 0;
  result = (int)&Buffer.m_fMoveTargetX + 2;
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
  while ( result < (int)&((RoleSystem *)&stru_C059A0)->m_StaticSlotArray.m_bfocus + 2 );
  return result;
}

// 0x00484660
int StateUI::UpdateVisibility()
{
  int v2; // ebx
  float *p_m_ratioh; // edi
  char *v4; // ebp
  int v5; // ebp
  char *v6; // edi
  int *p_m_benable; // ebx
  int v8; // ebx
  int i; // edi
  int result; // eax
  unsigned int v11; // [esp+0x0] [ebp-0x18]
  int v12; // [esp+0x10] [ebp-0x8]
  int *p_capacity; // [esp+0x14] [ebp-0x4]

  v2 = 5;
  *(_DWORD *)&this->m_State[1].m_text[8] = g_nCurrentRoleSlot;
  p_m_ratioh = &this->m_RoleState[4].m_WuLing[2].m_ratioh;
  v4 = &this->m_RoleState[4].m_ShenVal.m_text[8];
  do
  {
    (**(void ( ***)(char *, _DWORD))v4)(v4, 0);
    (**(void ( ***)(float *, int))p_m_ratioh)(p_m_ratioh, 1);
    v4 += 344;
    p_m_ratioh += 38;
    --v2;
  }
  while ( v2 );
  sub_445FA0(&this->m_RoleState[4].m_ShenVal.m_text[344 * *(_DWORD *)&this->m_State[1].m_text[8] + 8]);
  (**(void ( ***)(char *, int))&this->m_RoleState[4].m_ShenVal.m_text[344
                                                                              * *(_DWORD *)&this->m_State[1].m_text[8]
                                                                              + 8])(
    &this->m_RoleState[4].m_ShenVal.m_text[344 * *(_DWORD *)&this->m_State[1].m_text[8] + 8],
    1);
  v5 = 0;
  v12 = 1;
  *(&this->m_RoleState[4].m_WuLing[2].m_benable + *(_DWORD *)&this->m_State[1].m_text[8]) = 0;
  v6 = &this->m_RoleState[4].m_ShenVal.m_text[8];
  p_capacity = &this->m_State[1].m_childs.capacity;
  p_m_benable = &this->m_RoleState[4].m_WuLing[2].m_benable;
  do
  {
    if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) && *(_DWORD *)&this->m_State[1].m_text[8] != v5 )
    {
      *p_m_benable = v12;
      sub_445FA0(v6);
      (**(void ( ***)(char *, int))v6)(v6, 1);
      ++v12;
      p_capacity += 4;
    }
    ++v5;
    ++p_m_benable;
    v6 += 344;
  }
  while ( v5 < 5 );
  v8 = 42;
  ((LineupComp *)this)->PositionAt(*(_DWORD *)&this->m_State[1].m_text[8], 638, 42);
  ((LineupComp *)this)->DispatchSlotMethod(*(_DWORD *)&this->m_State[1].m_text[8], 1u);
  for ( i = 0; i < 5; ++i )
  {
    if ( *((_BYTE *)&this->m_Frame.m_bfocus + i + 1) && *(_DWORD *)&this->m_State[1].m_text[8] != i )
    {
      v8 += 124;
      ((LineupComp *)this)->PositionAt(i, 638, v8);
      ((LineupComp *)this)->DispatchSlotMethod(i, 1u);
    }
  }

  this->m_LeaveHere.m_rect.top = 0;
  result = ((LineupUI *)this)->GetSlotRect(g_nCurrentRoleSlot, v11);
  LOBYTE(this->m_TopFrame.m_rect.bottom) = 0;
  LOBYTE(this->m_TopFrame.m_childs.capacity) = 0;
  return result;
}

// 0x00484E90
int StateUI::SelectTab1(unsigned __int8 nTab)
{
  BYTE2(this->m_Frame.m_bfocus) = nTab;
  return ((LineupComp *)this)->DispatchSlotMethod(1, nTab);
}

// 0x00484EB0
int StateUI::SelectTab2(unsigned __int8 nTab)
{
  HIBYTE(this->m_Frame.m_bfocus) = nTab;
  return ((LineupComp *)this)->DispatchSlotMethod(2, nTab);
}

// 0x00485980
int StateUI::RefreshStatsDisplay()
{
  gbTexture **v2; // ebp
  gbColorQuad *p_m_bkColor; // ebx
  char *v4; // ecx
  int v5; // edi
  char v6; // al
  int v7; // ebx
  float *p_m_needscriptdel; // edi
  tagRECT *p_m_rect; // ebp
  char *v11; // [esp+0x10] [ebp-0x10]
  float v12; // [esp+0x18] [ebp-0x8]

  v2 = &this->m_LeaveHere.m_texarray.m_ptex[5];
  p_m_bkColor = &this->m_RoleState[4].m_ShenBar.m_bkColor;
  *((_DWORD *)&this->m_DlgEx.76 + 33) = 0;
  *((_WORD *)&this->m_DlgEx.76 + 68) = 0;
  memset((char *)&this->m_DlgEx.76 + 140, 0xFFu, 0x18u);
  v4 = (char *)&Buffer.m_fCachePosZ + 1;
  v5 = 0;
  v11 = (char *)&Buffer.m_fCachePosZ + 1;
  do
  {
    if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) )
    {
      if ( *(v4 - 1) )
        BYTE1(p_m_bkColor[1].Color) = 2;
      else
        BYTE1(p_m_bkColor[1].Color) = 0;
      LOBYTE(p_m_bkColor->Color) = *v4 != 0 ? 2 : 0;
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
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + v5 + 2) = 0;
          ((Object3D *)v2)->VecAngle(*(float *)&this->m_TopFrame.m_childs.m_nSize, *(float *)&this->m_TopFrame.m_childs.m_needscriptdel, *(float *)&this->m_TopFrame.m_bcreateok);
          if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) )
          {
            *((_BYTE *)&this->m_DlgEx.76 + 132) = 1;
            *((_DWORD *)&this->m_DlgEx.76 + 35) = v5;
          }
          goto LABEL_31;
        case 2:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + v5 + 2) = 1;
          ((Object3D *)v2)->VecAngle(*(float *)&this->m_TopFrame.m_bvisible, *(float *)&this->m_TopFrame.m_benable, *(float *)&this->m_TopFrame.m_bfocus);
          if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) )
          {
            *((_BYTE *)&this->m_DlgEx.76 + 133) = 1;
            *((_DWORD *)&this->m_DlgEx.76 + 36) = v5;
          }
          goto LABEL_31;
        case 3:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + v5 + 2) = 3;
          ((Object3D *)v2)->VecAngle(this->m_TopFrame.m_ratioh, *(float *)&this->m_TopFrame.m_textx, *(float *)&this->m_TopFrame.m_texty);
          if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) )
          {
            *((_BYTE *)&this->m_DlgEx.76 + 135) = 1;
            *((_DWORD *)&this->m_DlgEx.76 + 38) = v5;
          }
          goto LABEL_31;
        case 4:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + v5 + 2) = 2;
          ((Object3D *)v2)->VecAngle(*(float *)&this->m_TopFrame.pDebugTex, *(float *)&this->m_TopFrame.m_align, this->m_TopFrame.m_ratiow);
          if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) )
          {
            *((_BYTE *)&this->m_DlgEx.76 + 134) = 1;
            *((_DWORD *)&this->m_DlgEx.76 + 37) = v5;
          }
          goto LABEL_31;
        case 5:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + v5 + 2) = 4;
          ((Object3D *)v2)->VecAngle(*(float *)&this->m_TopFrame.m_fonttype, *(float *)this->m_TopFrame.m_text, *(float *)&this->m_TopFrame.m_text[4]);
          if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) )
          {
            *((_BYTE *)&this->m_DlgEx.76 + 136) = 1;
            *((_DWORD *)&this->m_DlgEx.76 + 39) = v5;
          }
          goto LABEL_31;
        case 6:
          *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + v5 + 2) = 5;
          ((Object3D *)v2)->VecAngle(*(float *)&this->m_TopFrame.m_text[8], *(float *)&this->m_TopFrame.m_text[12], *(float *)&this->m_TopFrame.m_pbk);
          v2[14] = (gbTexture *)1119092736;
          if ( *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1) )
          {
            *((_BYTE *)&this->m_DlgEx.76 + 137) = 1;
            *((_DWORD *)&this->m_DlgEx.76 + 40) = v5;
          }
LABEL_31:
          v4 = v11;
          break;
        default:
          break;
      }
      v6 = *((_BYTE *)&this->m_Frame.m_bfocus + v5 + 1);
      *((_BYTE *)v2 + 80) = v6;
      if ( !v6 )
        *((_BYTE *)v2 + 21) = 0;
      *((_BYTE *)v2 + 21) = 0;
    }
    v4 += 1408;
    ++v5;
    p_m_bkColor = (gbColorQuad *)((char *)p_m_bkColor + 6);
    v2 += 38;
    v11 = v4;
  }
  while ( (int)v4 < (int)((char *)&((RoleSystem *)&stru_C059A0)->m_StaticSlotArray.m_benable + 1) );
  v7 = 0;
  p_m_needscriptdel = (float *)&this->m_TopFrame.m_childs.m_needscriptdel;
  p_m_rect = &this->m_DlgEx.m_static.m_rect;
  do
  {
    v12 = *(float *)&this->m_TopFrame.m_rect.right + *p_m_needscriptdel;
    ((Object3D *)&p_m_rect[-5])->VecAngle(*(p_m_needscriptdel - 1), v12, p_m_needscriptdel[1]);
    if ( *((_BYTE *)&this->m_DlgEx.76 + v7 + 132) )
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
  return ((MainEquipUI *)this)->CountVisibleStats();
}

// 0x00485CD0
char * StateUI::RefreshFromAtts()
{
  int v2; // esi
  char *result; // eax
  gbColorQuad *p_m_bkColor; // edx

  v2 = 0;
  result = (char *)&Buffer.m_fCachePosZ + 1;
  p_m_bkColor = &this->m_RoleState[4].m_ShenBar.m_bkColor;
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
  while ( (int)result < (int)((char *)&((RoleSystem *)&stru_C059A0)->m_StaticSlotArray.m_benable + 1) );
  g_nCurrentRoleSlot = *(_DWORD *)&this->m_State[1].m_text[8];
  return result;
}

// 0x00485DF0
int StateUI::OnRender()
{
  int v2; // ebx
  UICursor *v3; // ecx
  int *p_m_step; // esi
  int result; // eax
  int v6; // eax
  int v7; // ecx
  char *v8; // edx
  int v9; // ecx
  CScreenMode *Instance; // eax
  int v11; // eax
  int v12; // edx
  char *v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // eax
  char *v17; // eax
  s_SpecialPropItem *v18; // eax
  char *v19; // eax
  int v20; // eax
  int v21; // edx
  char *v22; // ecx
  CScreenMode *v23; // eax
  int v24; // eax
  int v25; // ecx
  const char **v26; // eax
  CScreenMode *v27; // eax
  CScreenMode *v28; // eax
  CScreenMode *v29; // eax
  int v30; // eax
  int v31; // eax
  const void *v32; // [esp-0x8] [ebp-0x18]
  const void *v33; // [esp-0x8] [ebp-0x18]
  _SPropValue *v34; // [esp-0x8] [ebp-0x18]
  const void *v35; // [esp-0x8] [ebp-0x18]
  const void *v36; // [esp-0x8] [ebp-0x18]
  unsigned int v37; // [esp+0x0] [ebp-0x10]
  int nVal; // [esp+0x14] [ebp+0x4]
  const char *nMsg; // [esp+0x18] [ebp+0x8]
  int wParam; // [esp+0x1C] [ebp+0xC]

  switch ( nVal )
  {
    case 1000:
      v2 = 0;
      if ( nMsg )
      {

        ((EquipUI *)this)->ShowPage();
        do
          sub_484F10(v2++);
        while ( v2 < 8 );
        p_m_step = &this->m_RoleState[4].m_ShenBar.m_step;
        g_nSceneState = 1;
        *p_m_step = 0;
        p_m_step[1] = 0;
        ((UICursor *)v3)->IRender();
        result = 1;
      }
      else
      {
        memset(&this->m_RoleState[4].m_ShenBar.m_bkColor, 0, 0x1Cu);
        LOWORD(this->m_RoleState[4].m_ShenBar.m_pdecorateInfo) = 0;
        *(_PlugInfo **)((char *)&this->m_RoleState[4].m_ShenBar.m_pdecorateInfo + 2) = 0;
        BYTE2(this->m_RoleState[4].m_ShenBar.m_decorateW) = 0;
        *(_DWORD *)&this->m_State[1].m_text[8] = 0;
        result = 1;
      }
      break;
    case 1001:
      *((_DWORD *)&this->m_isJusticeBook + 6) = 0;
      do
      {
        v6 = *((_DWORD *)&this->m_isJusticeBook + 6);
        if ( *((_BYTE *)&this->m_Frame.m_bfocus + v6 + 1) )
        {
          *((_DWORD *)&this->m_isJusticeBook + 7) = 0;
          while ( 1 )
          {
            v7 = *((_DWORD *)&this->m_isJusticeBook + 7);
            if ( nMsg == (&(&off_56B990)[6 * v6])[v7] )
            {
              v8 = (char *)this + 1944 * v6 + 248 * v7;
              if ( !*((_DWORD *)v8 + 40509) )
              {
                v32 = off_5C5EC8;
                Instance = CScreenMode::GetInstance();
                ((CScreenMode *)Instance)->AudioSetPosition(v32, 1);
                v11 = 0;
                do
                {
                  v12 = v11 + 1944 * *((_DWORD *)&this->m_isJusticeBook + 6);
                  v11 += 248;
                  v13 = (char *)&this->m_SpecialPropItem[2] + v12;
                  *((_DWORD *)v13 + 20) = 0;
                  v13[68] = 0;
                }
                while ( v11 < 1488 );
                goto LABEL_28;
              }
              if ( v8[162045] )
                break;
            }
            v9 = v7 + 1;
            *((_DWORD *)&this->m_isJusticeBook + 7) = v9;
            if ( v9 >= 6 )
              goto LABEL_28;
          }
          v14 = *((_DWORD *)&this->m_isJusticeBook + 7);
          if ( *((_BYTE *)this + 1944 * v6 + 248 * v14 + 162044) )
            *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_bkColor.Color + 6 * v6 + v14) = 2;
          else
            *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_bkColor.Color + 6 * v6 + v14) = 1;
          v15 = *((_DWORD *)&this->m_isJusticeBook + 7);
          if ( v15 == 5 || !v15 )
          {
            v16 = *((_DWORD *)&this->m_isJusticeBook + 6);
            if ( *((_BYTE *)this + 1944 * v16 + 248 * v15 + 162044) )
            {
              ((LineupComp *)this)->GetSlotWidget(v16, 1u);
              v17 = (char *)this + 1944 * *((_DWORD *)&this->m_isJusticeBook + 6) + 163216;
              *((_DWORD *)v17 + 20) = 1;
              v17[68] = 1;
              *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_foColor.Color
              + 6 * *((_DWORD *)&this->m_isJusticeBook + 6)
              + 1) = 2;
              v18 = &this->m_SpecialPropItem[243 * *((_DWORD *)&this->m_isJusticeBook + 6) + 2];
              v18[10].m_ItemId = 1;
              v18[8].m_CanUse = 1;
              *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_bkColor.Color + 6 * *((_DWORD *)&this->m_isJusticeBook + 6)) = 2;
            }
            else
            {
              v19 = (char *)&this->m_RoleState[4].m_ShenBar.m_bkColor + 6 * v16;
              *(_DWORD *)v19 = 0;
              *((_WORD *)v19 + 2) = 0;
              *((_BYTE *)&this->m_RoleState[4].m_ShenBar.m_foColor.Color
              + 6 * *((_DWORD *)&this->m_isJusticeBook + 6)
              + 1) = 1;
              ((LineupComp *)this)->GetSlotWidget(*((_DWORD *)&this->m_isJusticeBook + 6), 0);
              sub_445E50((int)this + 1944 * *((_DWORD *)&this->m_isJusticeBook + 6) + 163216);
              v20 = 0;
              do
              {
                v21 = v20 + 1944 * *((_DWORD *)&this->m_isJusticeBook + 6);
                v20 += 248;
                v22 = (char *)&this->m_SpecialPropItem[2] + v21;
                *((_DWORD *)v22 + 20) = 0;
                v22[68] = 0;
              }
              while ( v20 < 1488 );
            }
          }
          v33 = off_5C5EBC;
          v23 = CScreenMode::GetInstance();
          ((CScreenMode *)v23)->AudioSetPosition(v33, 1);
          LOBYTE(this->m_Frame.m_bfocus) = 1;
        }
LABEL_28:
        v24 = *((_DWORD *)&this->m_isJusticeBook + 6) + 1;
        *((_DWORD *)&this->m_isJusticeBook + 6) = v24;
      }
      while ( v24 < 5 );
      v25 = 0;
      v26 = &off_56B97C;
      while ( nMsg != *v26 )
      {
        ++v26;
        ++v25;
        if ( (int)v26 >= (int)&off_56B990 )
          goto LABEL_37;
      }
      if ( dword_D8BBEC == 2 )
      {
        ((LineupUI *)this)->GetSlotRect(v25, v37);
        v34 = (_SPropValue *)off_5C5EBC;
      }
      else
      {
        sprintf((char *const)&this->m_isJusticeBook + 32, "\\n%s", (const char *)dword_DD923C);
        ((UICaption *)&this->m_Alignment.m_text[12])->SetEnable((int)(&this->m_isJusticeBook + 32), 0);
        ((UIRoleSelect *)&this->m_State[1].m_text[12])->SetByte(1);
        v34 = off_5C5EC4;
      }
      v27 = CScreenMode::GetInstance();
      ((CScreenMode *)v27)->AudioSetPosition(v34, 1);
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
            if ( !LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_59;
            goto LABEL_55;
          case 0xA00103u:
            if ( !LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_59;
            goto LABEL_55;
          case 0xA00104u:
            if ( !LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_59;
            goto LABEL_55;
          case 0xA00105u:
            if ( !LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_59;
            goto LABEL_55;
          case 0xA00106u:
            if ( !LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_59;
            goto LABEL_55;
          case 0xA00107u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            goto LABEL_59;
          case 0xA00109u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
              goto LABEL_55;
            goto LABEL_59;
          case 0xA00110u:
            if ( LOBYTE(this->m_TopFrame.m_childs.capacity) )
            {
LABEL_55:
              v35 = off_5C5EC8;
              v28 = CScreenMode::GetInstance();
              ((CScreenMode *)v28)->AudioSetPosition(v35, 1);
              result = 1;
            }
            else
            {
LABEL_59:
              v36 = off_5C5EBC;
              v29 = CScreenMode::GetInstance();
              ((CScreenMode *)v29)->AudioSetPosition(v36, 1);

              ((MainEquipUI *)*((MainEquipUI **)this + 42810))->HandleMessage();
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
      v30 = *(_DWORD *)&this->m_State[1].m_text[8];
      if ( nMsg == (&off_56BA08)[v30] )
      {
        (**((void ( ***)(int *, _DWORD))&this->m_RoleState[5].m_Head.m_bfocus + 38 * v30))(
          &this->m_RoleState[5].m_Head.m_bfocus + 38 * v30,
          0);
        (**(void ( ***)(char *, int))&this->m_RoleState[4].m_ShenVal.m_text[344
                                                                                    * *(_DWORD *)&this->m_State[1].m_text[8]
                                                                                    + 8])(
          &this->m_RoleState[4].m_ShenVal.m_text[344 * *(_DWORD *)&this->m_State[1].m_text[8] + 8],
          1);
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
            sub_484F10(0);
            result = 1;
            break;
          case 0xA00103u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 1;
            if ( BYTE1(this->m_RoleState[4].m_ShenBar.m_step) )
              goto LABEL_80;
            sub_484F10(1);
            result = 1;
            break;
          case 0xA00104u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 2;
            if ( BYTE2(this->m_RoleState[4].m_ShenBar.m_step) )
              goto LABEL_80;
            sub_484F10(2);
            result = 1;
            break;
          case 0xA00105u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 3;
            if ( HIBYTE(this->m_RoleState[4].m_ShenBar.m_step) )
              goto LABEL_80;
            sub_484F10(3);
            result = 1;
            break;
          case 0xA00106u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 5;
            if ( BYTE1(this->m_RoleState[4].m_ShenBar.m_Val) )
              goto LABEL_80;
            sub_484F10(5);
            result = 1;
            break;
          case 0xA00107u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 6;
            if ( BYTE2(this->m_RoleState[4].m_ShenBar.m_Val) )
              goto LABEL_80;
            sub_484F10(6);
            result = 1;
            break;
          case 0xA00108u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 4;
            if ( LOBYTE(this->m_RoleState[4].m_ShenBar.m_Val) )
              goto LABEL_80;
            sub_484F10(4);
            result = 1;
            break;
          case 0xA00109u:
            *(_DWORD *)&this->m_RoleState[4].m_ShenBar.m_IsGetit = 7;
            if ( !HIBYTE(this->m_RoleState[4].m_ShenBar.m_Val) )
              sub_484F10(7);
            goto LABEL_80;
          default:
LABEL_80:
            result = 1;
            break;
        }
      }
      break;
    case 1003:
      v31 = *(_DWORD *)&this->m_State[1].m_text[8];
      if ( nMsg == (&off_56B97C)[v31] )
      {
        (**((void ( ***)(int *, int))&this->m_RoleState[5].m_Head.m_bfocus + 38 * v31))(
          &this->m_RoleState[5].m_Head.m_bfocus + 38 * v31,
          1);
        (**(void ( ***)(char *, _DWORD))&this->m_RoleState[4].m_ShenVal.m_text[344
                                                                                       * *(_DWORD *)&this->m_State[1].m_text[8]
                                                                                       + 8])(
          &this->m_RoleState[4].m_ShenVal.m_text[344 * *(_DWORD *)&this->m_State[1].m_text[8] + 8],
          0);
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
      result = ((PalScript *)this)->OnMessage(nVal, (int)nMsg, wParam);
      break;
  }
  return result;
}

// 0x0048A310
int StateUI::SelectSubTab1(unsigned __int8 nTab)
{
  BYTE2(this->m_OutFrameR.m_ppicInfo) = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState(1, nTab);
}

// 0x0048A330
int StateUI::SelectSubTab2(unsigned __int8 nTab)
{
  HIBYTE(this->m_OutFrameR.m_ppicInfo) = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState(2, nTab);
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
  p_m_mouseoff = &this->m_RoleState[4].m_WuLing[4].m_mouseoff;
  do
  {
    (**((void ( ***)(int, _DWORD))p_m_mouseoff - 38))((int)(p_m_mouseoff - 152), 0);
    (**(void ( ***)(_BYTE *, _DWORD))p_m_mouseoff)(p_m_mouseoff, 0);
    (**((void ( ***)(int, _DWORD))p_m_mouseoff + 38))((int)(p_m_mouseoff + 152), 0);
    (**((void ( ***)(int, _DWORD))p_m_mouseoff + 76))((int)(p_m_mouseoff + 304), 0);
    (**((void ( ***)(int, _DWORD))p_m_mouseoff + 114))((int)(p_m_mouseoff + 456), 0);
    (**((void ( ***)(int, _DWORD))p_m_mouseoff + 152))((int)(p_m_mouseoff + 608), 0);
    v4 = (void ( ***)(_DWORD, _DWORD))(p_m_mouseoff + 2280);
    v5 = 10;
    do
    {
      (**(v4 - 380))(v4 - 380, 0);
      (**v4)(v4, 0);
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
    (**v7)(v7, 1);
    (*v7[380])(v7 + 380, 1);
    v7 += 38;
    --v8;
  }
  while ( v8 );
  ((UIScene *)this)->LoadRoleSkillData(nVal);
  ((MainEquipUI *)this)->UpdateTooltip(nVal);
}

// 0x00493420
void StateUI::UpdateAttributeDisplay(int arg0, char *pszBuf, float id)
{
  char *v4; // esi
  int v5; // edi
  __int16 v6; // ax
  unsigned int v7; // esi
  int v8; // edx
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
memset(Buffer, 0, sizeof(Buffer));
  memset(v24, 0, sizeof(v24));
  memset(v23, 0, sizeof(v23));
  v4 = (char *)&this->m_DlgEx.m_btRc + 360;
  v5 = 5;
  do
  {
    (**(void ( ***)(char *, _DWORD))v4)(v4, 0);
    v4 += 9980;
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
      *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * arg0 + 24]);
    sprintf(v23, "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[1408 * arg0 + 7]);
    sprintf(
      &Buffer[30],
      "%s %d",
      (const char *)&g_szRoleName0,
      *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * arg0 + 20]);
    sprintf(&v23[30], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[1408 * arg0 + 3]);
    sprintf(
      &Buffer[60],
      "%s %d",
      (const char *)&g_szRoleName2,
      *((_DWORD *)&::Buffer.m_partyActor.m_vecLocalPos.x + 352 * arg0));
    sprintf(&v23[60], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[1408 * arg0 + 11]);
    sprintf(
      &Buffer[90],
      "%s %d",
      (const char *)&g_szRoleName3,
      *((_DWORD *)&::Buffer.m_partyActor.m_vecLocalPos.y + 352 * arg0));
    sprintf(&v23[90], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[1408 * arg0 + 15]);
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
        *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * arg0 + 24]);
      sprintf(v23, "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[1408 * arg0 + 7]);
    }
    else
    {
      sprintf(
        Buffer,
        "%s %d",
        (const char *)&g_szRoleName1,
        *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * arg0 + 24]);
      sprintf(v24, "      %d", *((__int16 *)pszBuf + 326));
      sprintf(v23, "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[1408 * arg0 + 7]);
    }
  }
  else
  {
    v7 = 1408 * arg0;
    sprintf(
      Buffer,
      "%s %d",
      (const char *)&g_szRoleName1,
      *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * arg0 + 24]);
    sprintf(v24, "      +%d", *((__int16 *)pszBuf + 326));
    sprintf(v23, "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[1408 * arg0 + 7]);
  }
  if ( id == 0.0 && *(_DWORD *)pszBuf == 6603 && !arg0 )
  {
    if ( g_nUpdateInterval < 35 )
      g_nUpdateInterval = 35;
    sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[20]);
    sprintf(&v24[30], "      +%d", g_nUpdateInterval);
    v8 = *(_DWORD *)&::Buffer.m_partyActor.m_curact[3];
    goto LABEL_19;
  }
  v9 = *((_WORD *)pszBuf + 325);
  v15 = *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[v7 + 20];
  if ( v9 > 0 )
  {
    sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, v15);
    sprintf(&v24[30], "      +%d", *((__int16 *)pszBuf + 325));
LABEL_18:
    v8 = *(_DWORD *)&::Buffer.m_partyActor.m_curact[v7 + 3];
LABEL_19:
    sprintf(&v23[30], "          (%d)", v8);
    goto LABEL_20;
  }
  if ( v9 < 0 )
  {
    sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, v15);
    sprintf(&v24[30], "      %d", *((__int16 *)pszBuf + 325));
    goto LABEL_18;
  }
  sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, v15);
  sprintf(&v23[30], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[v7 + 3]);
LABEL_20:
  v10 = *((_WORD *)pszBuf + 327);
  v16 = *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos.x + v7);
  if ( v10 > 0 )
  {
    sprintf(&Buffer[60], "%s %d", (const char *)&g_szRoleName2, v16);
    sprintf(&v24[60], "      +%d", *((__int16 *)pszBuf + 327));
LABEL_27:
    sprintf(&v23[60], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[v7 + 11]);
    goto LABEL_28;
  }
  if ( v10 < 0 )
  {
    sprintf(&Buffer[60], "%s %d", (const char *)&g_szRoleName2, v16);
    sprintf(&v24[60], "      %d", *((__int16 *)pszBuf + 327));
    goto LABEL_27;
  }
  sprintf(&Buffer[60], "%s %d", (const char *)&g_szRoleName2, v16);
  sprintf(&v23[60], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[v7 + 11]);
LABEL_28:
  v11 = *((_WORD *)pszBuf + 328);
  v17 = *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos.y + v7);
  if ( v11 <= 0 )
  {
    if ( v11 >= 0 )
    {
      sprintf(&Buffer[90], "%s %d", (const char *)&g_szRoleName3, v17);
      sprintf(&v23[90], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[v7 + 15]);
    }
    else
    {
      sprintf(&Buffer[90], "%s %d", (const char *)&g_szRoleName3, v17);
      sprintf(&v24[90], "      %d", *((__int16 *)pszBuf + 328));
      sprintf(&v23[90], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[v7 + 15]);
    }
  }
  else
  {
    sprintf(&Buffer[90], "%s %d", (const char *)&g_szRoleName3, v17);
    sprintf(&v24[90], "      +%d", *((__int16 *)pszBuf + 328));
    sprintf(&v23[90], "          (%d)", *(_DWORD *)&::Buffer.m_partyActor.m_curact[v7 + 15]);
  }
LABEL_31:
  sprintf(
    &Buffer[120],
    "%s %d",
    (const char *)&g_szSceneName,
    *(_DWORD *)((char *)&::Buffer.m_partyActor.m_fActionAssignParam + v7));
  lstrcpyA(&v24[120], g_szSceneUIText);
  lstrcpyA(&v23[120], g_szSceneUIText);
  if ( !pszBuf )
  {
    sprintf(
      &Buffer[150],
      "%s %d",
      (const char *)g_bSlotFlag,
      *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos.z + v7));
    sprintf(
      &Buffer[180],
      "%s %d",
      (const char *)&g_bSlotFlag[256],
      *(&v26[1].m_par[9][3]._element.m_textx + 213 * arg0));
    sprintf(&Buffer[210], "%s %d", byte_DC3F3C, *(_DWORD *)((char *)&::Buffer.m_partyActor.m_nAnimState + v7));
    sprintf(
      &Buffer[240],
      "%s %d",
      (const char *)&g_bSlotFlag[512],
      *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos + v7 + 16));
    sprintf(&Buffer[270], "%s %d", byte_DC403C, *(_DWORD *)(&::Buffer.m_partyActor.m_nActionType + v7));
    goto LABEL_68;
  }
  id_3 = *(_DWORD *)pszBuf == 6603;
  if ( *(_DWORD *)pszBuf == 6603 && !g_nFiveNimbusCount )
  {
    sprintf(&Buffer[150], "%s %d", g_bSlotFlag, *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos.z + v7));
LABEL_42:
    sprintf(&v24[150], "      +%d", 1);
    goto LABEL_43;
  }
  v18 = *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos.z + v7);
  if ( pszBuf[619] )
  {
    sprintf(&Buffer[150], "%s %d", g_bSlotFlag, v18);
    goto LABEL_42;
  }
  sprintf(&Buffer[150], "%s %d", (const char *)g_bSlotFlag, v18);
LABEL_43:
  if ( id_3 && g_nFiveNimbusCount == 1 )
  {
    v19 = *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos + v7 + 12);
  }
  else
  {
    v19 = *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos + v7 + 12);
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
    sprintf(&Buffer[210], "%s %d", byte_DC3F3C, *(_DWORD *)((char *)&::Buffer.m_partyActor.m_nAnimState + v7));
LABEL_55:
    sprintf(&v24[210], "      +%d", 1);
    goto LABEL_56;
  }
  v20 = *(_DWORD *)((char *)&::Buffer.m_partyActor.m_nAnimState + v7);
  if ( pszBuf[622] )
  {
    sprintf(&Buffer[210], "%s %d", byte_DC3F3C, v20);
    goto LABEL_55;
  }
  sprintf(&Buffer[210], "%s %d", byte_DC3F3C, v20);
LABEL_56:
  if ( id_3 && g_nFiveNimbusCount == 3 )
  {
    v21 = *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos + v7 + 16);
  }
  else
  {
    v21 = *(_DWORD *)((char *)&::Buffer.m_partyActor.m_vecLocalPos + v7 + 16);
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
    sprintf(&Buffer[270], "%s %d", byte_DC403C, *(_DWORD *)(&::Buffer.m_partyActor.m_nActionType + v7));
    sprintf(&v24[270], "      +%d", 1);
  }
  else
  {
    v22 = *(_DWORD *)(&::Buffer.m_partyActor.m_nActionType + v7);
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
  pszBufa = (char *)v26 + 9980 * arg0;
  v12 = pszBufa + 159232;
  for ( i = 0; i < 300; i += 30 )
  {
    sub_446010(v12);
    sub_446010(v12 + 1520);
    ((UICaption *)v12)->SetEnable((int)&v24[i], 0);
    ((UICaption *)(v12 - 1520))->SetEnable((int)&Buffer[i], 0);
    ((UICaption *)(v12 + 1520))->SetEnable((int)&v23[i], 0);
    v12 += 152;
  }
  v14 = &this->m_isJusticeBook + 32;
  sprintf(
    (char *const)&this->m_isJusticeBook + 32,
    "%d/%d",
    (int)*((float *)pszBufa + 38866),
    ::Buffer.m_partyActor.m_dwMatMsg[v7 / 4 + 9]);
  ((UICaption *)(pszBufa + 155552))->SetEnable((int)v14, 0);
  sprintf(v14, "%d/%d", (int)*((float *)pszBufa + 39140), ::Buffer.m_partyActor.m_dwMatMsg[v7 / 4 + 10]);
  ((UICaption *)(pszBufa + 156648))->SetEnable((int)v14, 0);
  sprintf(v14, "%d/%d", (int)*((float *)pszBufa + 39003), ::Buffer.m_partyActor.m_dwMatMsg[v7 / 4 + 11]);
  ((UICaption *)(pszBufa + 156100))->SetEnable((int)v14, 0);
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
  v1 = (int *)&Buffer.m_partyActor.m_curact[39];
  p_m_needscriptdel = &this->m_RoleState[4].m_WuLing[1].m_childs.m_needscriptdel;
  do
  {
    if ( *v10 )
    {
      ((RoleSystem *)(v1 - 243))->RecalcAggregatedStats(0);
      fValue = (float)*(v1 - 12);
      ((UIScrollBar *)(p_m_needscriptdel - 274))->SetRange(fValue);
      fValuea = (float)*(v1 - 11);
      ((UIScrollBar *)p_m_needscriptdel)->SetRange(fValuea);
      fValueb = (float)*(v1 - 10);
      ((UIScrollBar *)(p_m_needscriptdel - 137))->SetRange(fValueb);
      fValuec = (float)*v1;
      ((UIProgressBar *)(p_m_needscriptdel - 274))->FindChildByName(fValuec);
      fValued = (float)v1[1];
      ((UIProgressBar *)p_m_needscriptdel)->FindChildByName(fValued);
      fValuee = (float)v1[2];
      ((UIProgressBar *)(p_m_needscriptdel - 137))->FindChildByName(fValuee);
      sprintf((char *const)&this->m_isJusticeBook + 32, "%d/%d", (int)*((float *)p_m_needscriptdel - 235), *(v1 - 12));
      ((UICaption *)(p_m_needscriptdel - 213))->SetEnable((int)(&this->m_isJusticeBook + 32), 0);
      sprintf((char *const)&this->m_isJusticeBook + 32, "%d/%d", (int)*((float *)p_m_needscriptdel + 39), *(v1 - 11));
      ((UICaption *)(p_m_needscriptdel + 61))->SetEnable((int)(&this->m_isJusticeBook + 32), 0);
      sprintf((char *const)&this->m_isJusticeBook + 32, "%d/%d", (int)*((float *)p_m_needscriptdel - 98), *(v1 - 10));
      ((UICaption *)(p_m_needscriptdel - 76))->SetEnable((int)(&this->m_isJusticeBook + 32), 0);
    }
    v1 += 352;
    p_m_needscriptdel += 2495;
    ++v10;
  }
  while ( (int)v1 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[220] );
}

// 0x004945E0
int StateUI::ForwardToBigMap(char pData)
{
  BYTE2(this->m_Frame.m_bfocus) = pData;
  return ((UIBigMap *)this)->SetEntryVisible(1, pData);
}

// 0x00494600
int StateUI::SelectBigMapTab2(char nTab)
{
  HIBYTE(this->m_Frame.m_bfocus) = nTab;
  return ((UIBigMap *)this)->SetEntryVisible(2, nTab);
}

// 0x004998E0
int StateUI::ShowPage()
{
  _BYTE *p_m_benable_snd; // ecx

  if ( g_bRoleFlag1 )
  {
    p_m_benable_snd = &this->stp_Prop.m_benable_snd;
  }
  else
  {
    ((PalScript *)&this->stp_Prop.m_benable_snd)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    p_m_benable_snd = &this->stp_Prop.m_benable_snd;
  }
  sub_445E50((int)p_m_benable_snd);
  if ( !g_bRoleFlag2 )
    ((PalScript *)&this->stp_BattleArray.m_benable_snd)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_BattleArray.m_benable_snd);
  ((PalScript *)&this->stp_Equip.m_benable_snd)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnProp.tga", g_bDebugMode);
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

  p_m_bvisible = &this->m_Alignment.m_bvisible;
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
      (**v4)(v4, 0);
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
    (**v8)(v8, 1);
    v8 += 38;
    --v7;
  }
  while ( v7 );
  (**((void ( ***)(int, int))v6 + 39611))((int)(v6 + 158444), 1);
  (**((void ( ***)(int, int))v6 + 39649))((int)(v6 + 158596), 1);
  (**((void ( ***)(int, int))v6 + 39687))((int)(v6 + 158748), 1);
  (**((void ( ***)(int, int))v6 + 39725))((int)(v6 + 158900), 1);
  (**((void ( ***)(int, int))v6 + 39763))((int)(v6 + 159052), 1);
  (**((void ( ***)(int, int))v6 + 39801))((int)(v6 + 159204), 1);
  (**((void ( ***)(int, int))v6 + 39839))((int)(v6 + 159356), 1);
  (**((void ( ***)(int, int))v6 + 39877))((int)(v6 + 159508), 1);
  (**((void ( ***)(int, int))v6 + 39915))((int)(v6 + 159660), 1);
  (**((void ( ***)(int, int))v6 + 39953))((int)(v6 + 159812), 1);
  (**((void ( ***)(int, int))v6 + 39991))((int)(v6 + 159964), 1);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szRoleName1,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 7]);
  ((UICaption *)(v6 + 159356))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szRoleName0,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 3]);
  ((UICaption *)(v6 + 159508))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szRoleName2,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 11]);
  ((UICaption *)(v6 + 159660))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szRoleName3,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 15]);
  ((UICaption *)(v6 + 159812))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_szSceneName,
    *((_DWORD *)&Buffer.m_partyActor.m_fActionAssignParam + 352 * nVal));
  ((UICaption *)(v6 + 159964))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)g_bSlotFlag,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 19]);
  ((UICaption *)(v6 + 160116))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_bSlotFlag[256],
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 23]);
  ((UICaption *)(v6 + 160268))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    byte_DC3F3C,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 31]);
  ((UICaption *)(v6 + 160420))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    (const char *)&g_bSlotFlag[512],
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 27]);
  ((UICaption *)(v6 + 160572))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
  sprintf(
    (char *const)&this->m_isJusticeBook + 36,
    "%s %d",
    byte_DC403C,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 35]);
  ((UICaption *)(v6 + 160724))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
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
      fValue = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * v2 + 9];
      ((UIScrollBar *)(&this->m_RoleState[4].m_WuLing[4].m_mouseoff + 4892 * v2))->SetRange(fValue);
      v3 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValuea = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * v3 + 10];
      ((UIScrollBar *)(&this->m_State[0].m_pbkInfo + 1223 * v3))->SetRange(fValuea);
      v4 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValueb = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * v4 + 11];
      ((UIScrollBar *)(&this->m_RoleState[5].m_Name.m_bfocus + 1223 * v4))->SetRange(fValueb);
      v5 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValuec = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v5 + 39];
      ((UIProgressBar *)(&this->m_RoleState[4].m_WuLing[4].m_mouseoff + 4892 * v5))->FindChildByName(fValuec);
      v6 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValued = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v6 + 43];
      ((UIProgressBar *)(&this->m_State[0].m_pbkInfo + 1223 * v6))->FindChildByName(fValued);
      v7 = *((_DWORD *)&this->m_isJusticeBook + 6);
      fValuee = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v7 + 47];
      ((UIProgressBar *)(&this->m_RoleState[5].m_Name.m_bfocus + 1223 * v7))->FindChildByName(fValuee);
      sprintf(
        (char *const)&this->m_isJusticeBook + 36,
        "%d/%d",
        (int)*((float *)&this->m_RoleState[4].m_FWSY.m_FVF + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)),
        Buffer.m_partyActor.m_dwMatMsg[352 * *((_DWORD *)&this->m_isJusticeBook + 6) + 9]);
      ((UICaption *)(&this->m_RoleState[5].m_Headbk.m_bfocus + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
      sprintf(
        (char *const)&this->m_isJusticeBook + 36,
        "%d/%d",
        (int)*((float *)&this->m_State[1].m_ppic + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)),
        Buffer.m_partyActor.m_dwMatMsg[352 * *((_DWORD *)&this->m_isJusticeBook + 6) + 10]);
      ((UICaption *)(&this->m_State[2].m_bvisible + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
      sprintf(
        (char *const)&this->m_isJusticeBook + 36,
        "%d/%d",
        (int)*((float *)&this->m_RoleState[5].m_Jing.pDebugTex + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)),
        Buffer.m_partyActor.m_dwMatMsg[352 * *((_DWORD *)&this->m_isJusticeBook + 6) + 11]);
      ((UICaption *)(&this->m_RoleState[5].m_JingBar.m_fontcolor + 1223 * *((_DWORD *)&this->m_isJusticeBook + 6)))->SetEnable((int)(&this->m_isJusticeBook + 36), 0);
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
  return ((UITitle_XJTM *)this)->SetMonsterState2(1, nTab);
}

// 0x0049E880
int StateUI::SelectXJTMTab2(unsigned __int8 nTab)
{
  HIBYTE(this->m_OutFrameT.m_rect.top) = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState2(2, nTab);
}

// 0x004A2BD0
UIWnd * StateUI::GetChildPtr(int index)
{
  int v2; // edi
  int v4; // ecx
  char *v5; // edi
  int v6; // edx
  UIWnd *result; // eax
  int v9; // [esp+0x20] [ebp-0x20]
  int v10; // [esp+0x30] [ebp-0x10] BYREF
  int v11; // [esp+0x34] [ebp-0xC]
  _DWORD v12[2]; // [esp+0x38] [ebp-0x8] BYREF
  int *v13; // [esp+0x48] [ebp+0x8]
  int v14; // [esp+0x50] [ebp+0x10]

  if ( index <= 5 )
  {
    v9 = v2;
    v4 = *v13;
    v11 = v13[1];
    v12[1] = v11 + 12;
    v10 = v4;
    v12[0] = v4 + 85;
    v5 = (char *)this + 3788 * index;
    (*(void ( **)(char *, int, int *, StateUI *, int))(*((_DWORD *)v5 + 38937) + 16))(
      v5 + 155748,
      g_ComposeUIChildIDs[index],
      &v10,
      this,
      v9);
    ((UIScene *)(v5 + 155748))->GetChildCount();
    ((UIScene *)(v5 + 155748))->GetChildAt();
    *((_DWORD *)v5 + 38955) = 1;
    v5[155918] = -30;
    v5[155917] = -51;
    v5[155916] = 58;
    v5[155919] = -1;
    sub_43FD90((float *)v5 + 38937, 4);
    ((UIWnd *)(v5 + 155748))->GetWidth(-4);
    sub_43FDB0((float *)v5 + 38937, 1);
    ((UIWnd *)(v5 + 155748))->GetPosition(-3);
    (*(void ( **)(char *, int, _DWORD *, StateUI *))(*((_DWORD *)v5 + 39211) + 16))(
      v5 + 156844,
      g_ComposeUIChildIDs[index],
      v12,
      this);
    ((UIScene *)(v5 + 156844))->GetChildCount();
    ((UIScene *)(v5 + 156844))->GetChildAt();
    *((_DWORD *)v5 + 39229) = 1;
    v5[157014] = -30;
    v5[157013] = -51;
    v5[157012] = 58;
    v5[157015] = -1;
    sub_43FD90((float *)v5 + 39211, 4);
    ((UIWnd *)(v5 + 156844))->GetWidth(-4);
    sub_43FDB0((float *)v5 + 39211, 1);
    ((UIWnd *)(v5 + 156844))->GetPosition(-3);
    (*(void ( **)(char *, int, _DWORD *, StateUI *))(*((_DWORD *)v5 + 39074) + 16))(
      v5 + 156296,
      g_ComposeUIChildIDs[index],
      v12,
      this);
    ((UIScene *)(v5 + 156296))->GetChildCount();
    ((UIScene *)(v5 + 156296))->GetChildAt();
    *((_DWORD *)v5 + 39092) = 1;
    v5[156466] = -30;
    v5[156465] = -51;
    v5[156464] = 58;
    v5[156467] = -1;
    sub_43FD90((float *)v5 + 39074, 4);
    ((UIWnd *)(v5 + 156296))->GetWidth(-4);
    sub_43FDB0((float *)v5 + 39074, 1);
    ((UIWnd *)(v5 + 156296))->GetPosition(-3);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v5 + 38998) + 16))(
      v5 + 155992,
      g_ComposeUIChildIDs[index],
      v14,
      this);
    sub_446010(v5 + 155992);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v5 + 39272) + 16))(
      v5 + 157088,
      g_ComposeUIChildIDs[index],
      v14,
      this);
    sub_446010(v5 + 157088);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v5 + 39135) + 16))(
      v5 + 156540,
      g_ComposeUIChildIDs[index],
      v14,
      this);
    sub_446010(v5 + 156540);
    (*(void ( **)(char *, int))(*((_DWORD *)v5 + 38785) + 16))(v5 + 155140, g_ComposeUIChildIDs[index]);
    ((UIStatic *)(v5 + 155140))->CreateFromTemplate();
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v5 + 38823) + 16))(
      v5 + 155292,
      g_ComposeUIChildIDs[index],
      v14,
      this);
    ((UIStatic *)(v5 + 155292))->CreateFromTemplate();
    v6 = *((_DWORD *)v5 + 38861);
    v5 += 155444;
    (*(void ( **)(char *, int, int, StateUI *))(v6 + 16))(v5, g_ComposeUIChildIDs[index], v14, this);
    ((UIStatic *)v5)->CreateFromTemplate();
    return (UIWnd *)((UIScene *)v5)->SetShow(0);
  }
  return result;
}

// 0x004A2F90
UIWnd * StateUI::FindChild(int id)
{
  int v2; // ebp
  char *v4; // ebp
  int v5; // edx
  UIWnd *result; // eax
  int v7; // [esp+0x64] [ebp-0x10]
  int v8; // [esp+0x7C] [ebp+0x8]

  if ( id <= 5 )
  {
    v7 = v2;
    v4 = (char *)this + 3788 * id;
    (*(void ( **)(char *, int, int, StateUI *, int))(*((_DWORD *)v4 + 39310) + 16))(
      v4 + 157240,
      g_ComposeUIChildIDs[id],
      v8,
      this,
      v7);
    ((UIStatic *)(v4 + 157240))->CreateFromTemplate();
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39348) + 16))(
      v4 + 157392,
      g_ComposeUIChildIDs[id],
      v8,
      this);
    ((UIStatic *)(v4 + 157392))->CreateFromTemplate();
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39386) + 16))(
      v4 + 157544,
      g_ComposeUIChildIDs[id],
      v8,
      this);
    ((UIScene *)(v4 + 157544))->SetShow(0);
    sub_446010(v4 + 157544);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39424) + 16))(
      v4 + 157696,
      g_ComposeUIChildIDs[id],
      v8,
      this);
    ((UIScene *)(v4 + 157696))->SetShow(0);
    sub_446010(v4 + 157696);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39462) + 16))(
      v4 + 157848,
      g_ComposeUIChildIDs[id],
      v8,
      this);
    ((UIScene *)(v4 + 157848))->SetShow(0);
    sub_446010(v4 + 157848);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39500) + 16))(
      v4 + 158000,
      g_ComposeUIChildIDs[id],
      v8,
      this);
    ((UIScene *)(v4 + 158000))->SetShow(0);
    sub_446010(v4 + 158000);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39538) + 16))(
      v4 + 158152,
      g_ComposeUIChildIDs[id],
      v8,
      this);
    ((UIScene *)(v4 + 158152))->SetShow(0);
    sub_446010(v4 + 158152);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39614) + 16))(
      v4 + 158456,
      g_ComposeUIChildIDs[id],
      v8,
      this);
    ((UIScene *)(v4 + 158456))->SetShow(0);
    sub_446010(v4 + 158456);
    (*(void ( **)(char *, int, int, StateUI *))(*((_DWORD *)v4 + 39576) + 16))(
      v4 + 158304,
      g_ComposeUIChildIDs[id],
      v8,
      this);
    ((UIScene *)(v4 + 158304))->SetShow(0);
    sub_446010(v4 + 158304);
    v5 = *((_DWORD *)v4 + 39652);
    v4 += 158608;
    (*(void ( **)(char *, int))(v5 + 16))(v4, g_ComposeUIChildIDs[id]);
    ((UIScene *)v4)->SetShow(0);
    return (UIWnd *)sub_446010(v4);
  }
  return result;
}

// 0x004A4960
int StateUI::InitLayout()
{
  unsigned int data; // [esp+0x8] [ebp+0x4]

  if ( ((EquipUI *)this)->GetSelected() < 5 )
  {
    BYTE2(this->m_Frame.m_bfocus) = data;
    ((UIBase *)this)->SetItemData(1, data);
    ((StateUI *)*((StateUI **)this + 44015))->SelectSubTab1(data);
    ((StateUI *)*((StateUI **)this + 44016))->ForwardToBigMap(data);
    ((StateUI *)*((StateUI **)this + 44017))->SelectXJTMTab1(data);
    return ((StateUI *)*((StateUI **)this + 44014))->SelectTab1(data);
  }
  else
  {
    BYTE2(this->m_Frame.m_bfocus) = 0;
    ((UIBase *)this)->SetItemData(1, 0);
    ((StateUI *)*((StateUI **)this + 44015))->SelectSubTab1(0);
    ((StateUI *)*((StateUI **)this + 44016))->ForwardToBigMap(0);
    ((StateUI *)*((StateUI **)this + 44017))->SelectXJTMTab1(0);
    return ((StateUI *)*((StateUI **)this + 44014))->SelectTab1(0);
  }
}

// 0x004A4A10
void StateUI::CreateWidgets()
{
  unsigned int data; // [esp+0x8] [ebp+0x4]

  if ( ((EquipUI *)this)->GetSelected() < 5 )
  {
    HIBYTE(this->m_Frame.m_bfocus) = data;
    ((UIBase *)this)->SetItemData(2, data);
    ((StateUI *)*((StateUI **)this + 44015))->SelectSubTab2(data);
    ((StateUI *)*((StateUI **)this + 44016))->SelectBigMapTab2(data);
    ((StateUI *)*((StateUI **)this + 44017))->SelectXJTMTab2(data);
    ((StateUI *)*((StateUI **)this + 44014))->SelectTab2(data);
  }
  else
  {
    HIBYTE(this->m_Frame.m_bfocus) = 0;
    ((UIBase *)this)->SetItemData(2, 0);
    ((StateUI *)*((StateUI **)this + 44015))->SelectSubTab2(0);
    ((StateUI *)*((StateUI **)this + 44016))->SelectBigMapTab2(0);
    ((StateUI *)*((StateUI **)this + 44017))->SelectXJTMTab2(0);
    ((StateUI *)*((StateUI **)this + 44014))->SelectTab2(0);
  }
}

// 0x004B2470
int StateUI::SaveData()
{
  char *v1; // ebp
  void **p_m_id; // edi
  Actor *SaveDataManager; // eax
  void **v4; // esi
  int i; // ebp
  __int64 v6; // rax
  int v7; // esi
  int v8; // ebx
  int v9; // ebp
  void **v10; // esi
  int result; // eax
  int v12; // [esp-0x4] [ebp-0x170]
  int v13; // [esp+0x10] [ebp-0x15C]
  void **v14; // [esp+0x14] [ebp-0x158]
  float v15; // [esp+0x18] [ebp-0x154]
  _BYTE v16[5]; // [esp+0x1C] [ebp-0x150]
  char v17[67]; // [esp+0x21] [ebp-0x14B] BYREF
  int v18; // [esp+0x64] [ebp-0x108]
  char Buffer[257]; // [esp+0x68] [ebp-0x104] BYREF
  __int16 v20; // [esp+0x169] [ebp-0x3]
  char v21; // [esp+0x16B] [ebp-0x1]

  memset(Buffer, 0, sizeof(Buffer));
  v1 = 0;
  v20 = 0;
  v21 = 0;
  v13 = 0;
  p_m_id = &this->m_Alignment.m_id;
  while ( 1 )
  {
    SaveDataManager = (Actor *)GetSaveDataManager();
    if ( ((Actor *)SaveDataManager)->LoadSaveData(v1) )
    {
      v6 = (__int64)v15;
      v7 = (int)v6 / 3600;
      v8 = (int)v6 / 60 % 60;
      v12 = (int)v6 % 60;
      if ( (int)v6 / 3600 < 100 )
        sprintf(Buffer, "%s %02d:%02d:%02d", dword_DC643C, v7, v8, v12);
      else
        sprintf(Buffer, "%s %03d:%02d:%02d", dword_DC643C, v7, v8, v12);
      ((UICaption *)p_m_id)->SetEnable((int)Buffer, 0);
      sprintf(Buffer, "%s %d", (const char *)dword_DC633C, v18);
      ((UICaption *)(p_m_id + 38))->SetEnable((int)Buffer, 0);
      sprintf(Buffer, "%s %s", (const char *)dword_DD933C, v17);
      ((UICaption *)(p_m_id + 304))->SetEnable((int)Buffer, 0);
      sprintf(Buffer, "Save\\PAL3_%04d.JPG", v1);
      ((UIFrameWnd *)(p_m_id + 266))->SetTextureByID((int)Buffer);
      (*(void ( **)(void **, int))p_m_id[266])(p_m_id + 266, 1);
      v9 = 0;
      v10 = p_m_id - 192;
      do
      {
        if ( v16[v9] )
        {
          *((_BYTE *)p_m_id + v9 - 8) = 1;
          (*(void ( **)(void **, _DWORD))*v10)(v10, 0);
          ((UIStatic *)v10)->CreateFromTemplate();
          (*(void ( **)(void **, int))*(v10 - 190))(v10 - 190, 1);
          ((UIStatic *)(UIStatic *)v10 - 5)->CreateFromTemplate();
          ((UICaption *)(v10 + 268))->SetEnable((int)g_szSceneUIText, 1);
        }
        else
        {
          (*(void ( **)(void **, _DWORD))*v10)(v10, 0);
          (*(void ( **)(void **, _DWORD))*(v10 - 190))(v10 - 190, 0);
          *((_BYTE *)p_m_id + v9 - 8) = 0;
        }
        ++v9;
        v10 += 38;
      }
      while ( v9 < 5 );
    }
    else
    {
      ((UICaption *)p_m_id)->SetEnable((int)g_szSceneUIText, 0);
      ((UICaption *)(p_m_id + 38))->SetEnable((int)g_szSceneUIText, 0);
      ((UICaption *)(p_m_id + 304))->SetEnable((int)g_szSceneUIText, 0);
      (*(void ( **)(void **, _DWORD))p_m_id[266])(p_m_id + 266, 0);
      v4 = p_m_id - 382;
      v14 = p_m_id - 2;
      for ( i = 0; i < 20; i += 4 )
      {
        *(_BYTE *)v14 = 0;
        (*(void ( **)(void **, _DWORD))v4[190])(v4 + 190, 0);
        ((UIStatic *)(UIStatic *)v4 + 5)->CreateFromTemplate();
        (*(void ( **)(void **, _DWORD))*v4)(v4, 0);
        ((UIStatic *)v4)->CreateFromTemplate();
        ((UICaption *)(v4 + 458))->SetEnable((int)g_szSceneUIText, 1);
        v4 += 38;
        v14 = (void **)((char *)v14 + 1);
      }
    }
    p_m_id += 890;
    result = ++v13;
    if ( v13 >= 36 )
      break;
    v1 = (char *)v13;
  }
  return result;
}
