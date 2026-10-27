#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/RoleAtt.h"
#include "Role/Actor.h"
#include "Misc/ArcSceneMonster.h"
#include "Misc/CCBPanelSlot.h"
#include "GameBase/GRPinput.h"
#include "Script/PalScript.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Effect/ScreenEffect.h"
#include "Effect/ScreenEffectMgr.h"
#include "Misc/UIBigMap.h"
#include "Misc/UIButton.h"
#include "Misc/UICoverFrm.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "Misc/s_RoleState.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DC4C3C[256];
extern CHAR byte_DC4D3C[256];
extern CHAR byte_DC4E3C[256];
extern CHAR byte_DC4F3C[256];
extern CHAR byte_DC503C[256];
extern CHAR byte_DC513C[256];
extern CHAR byte_DC523C[256];
extern CHAR byte_DC533C[256];
extern CHAR byte_DC543C[256];
extern CHAR byte_DC553C[256];
extern CHAR byte_DC563C[256];
extern CHAR byte_DC583C[256];
extern CHAR byte_DC593C[256];
extern CHAR byte_DC5A3C[256];
extern CHAR byte_DC5B3C[256];
extern CHAR byte_DC5C3C[768];
extern CHAR byte_DCBC3C[256];
extern CHAR byte_DCC93C[256];

// 0x00450EB0
void RoleAtt::_sdtor_call_dtor(UIWnd *pWnd)
{
  (((RoleAtt *)pWnd))->RoleAtt::Destroy();
  (((UIButton *)&pWnd[12].m_pfather))->UIButton::~UIButton();
  (((UIFrameContainer *)&pWnd[10].m_rect))->UIFrameContainer::~UIFrameContainer();
  (((SceneObj *)&pWnd[8].m_childs.m_needscriptdel))->SceneObj::~SceneObj();
  (((UIFrameWnd *)&pWnd[6].m_rect.bottom))->UIFrameWnd::_dtor_thunk();
  (((PalScript *)&pWnd[4]))->PalScript::ctor();
  UITextArea_Destroy();
  UIFrameWnd((UIFrameWnd *)pWnd);
}

// 0x00450F80
BOOL RoleAtt::IsValid()
{
  return this[-1].shikuaiskill != 0;
}

// 0x004512F0
void ** RoleAtt::Render()
{
  void **result; // eax

  result = (void **)*(void ***)((char *)&this->Remark.skillCount + 50);
  if ( result )
  {
    result = (void **)(*(int ( **)(char *))(*(_DWORD *)((char *)&this->Remark.skillCount + 74) + 4))((char *)&this->Remark.skillCount + 74);
    if ( *(_DWORD *)((char *)&this->Remark.skillCount + 246) == 2 )
      (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
  }
  return result;
}

// 0x00451320
void RoleAtt::Destroy()
{
  (*(void ( **)(char *))(*(_DWORD *)((char *)&this->Remark.skillCount + 74) + 12))((char *)&this->Remark.skillCount + 74);
  (*(void ( **)(char *))(*(_DWORD *)((char *)&this->Remark + 430) + 12))((char *)&this->Remark + 430);
  (*(void ( **)(int *))(this->att[3] + 12))(&this->att[3]);
  (((SceneObj *)this))->SceneObj::HideAll() /* [ROWTABLE] */;
}

// 0x004515A0
int RoleAtt::OnMessage(int nVal, LPCSTR lpString1, int nVal2)
{
  if ( nVal == 1000 && !lpString1 )
    (((UIBigMap *)this))->UIBigMap::LayoutBinkVideo(0, 0);
  return (((UIWnd *)this))->UIWnd::OnMessage(nVal, (int)lpString1, nVal2) /* [ROWTABLE] */;
}

// 0x004515E0
int RoleAtt::HandleInput(int nVal, int nVal2)
{
  BOOL v5; // ecx
  int v6; // eax
  void ( **id)(RoleAtt *, _DWORD); // eax
  double v8; // st7
  float v9; // edx

  if ( !*(_DWORD *)((char *)&this->Remark.skillCount + 50) )
    return 0;
  if ( !*(_DWORD *)((char *)&this->Remark.skillCount + 54) )
    return 0;
  (*(void ( **)(char *, int, int))(*(_DWORD *)((char *)&this->Remark.skillCount + 74) + 8))(
    (char *)&this->Remark.skillCount + 74,
    nVal,
    nVal2);
  v5 = g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1
    || g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2
    || g_Input.KeyInfo[6].PressTime == 1 && (g_Input.KeyInfo[6].Data & 0xF) == 1
    || g_Input.KeyInfo[6].PressTime == 1 && (g_Input.KeyInfo[6].Data & 0xF) == 2;
  v6 = *(_DWORD *)((char *)&this[1].Remark.skillCount + 238);
  if ( v6 )
  {
    if ( v6 == 1 )
    {
      if ( v5 )
      {
        id = (void ( **)(RoleAtt *, _DWORD))this->id;
        *(_DWORD *)((char *)&this[1].Remark.skillCount + 246) = 1;
        (*id)(this, 0);
      }
      v8 = *(float *)&nVal + *(float *)((char *)&this[1].Remark.skillCount + 242);
      *(float *)((char *)&this[1].Remark.skillCount + 242) = v8;
      if ( v8 > 4.0 )
      {
        v9 = (void ( **)(RoleAtt *, _DWORD))this->id;
        *(_DWORD *)((char *)&this[1].Remark.skillCount + 246) = 0;
        (*v9)(this, 0);
        *(_DWORD *)((char *)&this[1].Remark.skillCount + 242) = 1082130432;
      }
      (((UIScrollBar *)&this->stealnum))->UIScrollBar::SetRange(4.0);
      (((UIProgressBar *)&this->stealnum))->UIProgressBar::FindChildByName(*(float *)((char *)&this[1].Remark.skillCount + 242));
    }
  }
  else if ( v5 )
  {
    if ( (((UIPushButton *)&this->att[3]))->UIPushButton::IsHidden() )
      (*(void ( **)(RoleAtt *, _DWORD))this->id)(this, 0);
    else
      (((RoleAtt *)&this->att[3]))->RoleAtt::_sub_4531F0();
  }
  (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return 1;
}

// 0x00451740
void RoleAtt::ShowWindow(int lpString1)
{
  int v3; // ebx
  int v4; // ebp

  if ( lpString1 != *(_DWORD *)((char *)&this->Remark.skillCount + 50) )
  {
    (**(void ( ***)(char *, int))((char *)&this->Remark.skillCount + 74))((char *)((char *)&this->Remark.skillCount + 74), (int)(lpString1));
    v3 = *(_DWORD *)&this->height;
    v4 = *(_DWORD *)((char *)&this[1].Remark.skillCount + 46);
    (((CCBPanelSlot *)this))->CCBPanelSlot::ShowClipped(lpString1);
    (**(void ( ***)(_BYTE *, int))&this->fightstate[12])((_BYTE *)(&this->fightstate[12]), (int)(v3));
    (**(void ( ***)(signed __int16 *, int))&this->stealnum)((signed __int16 *)(&this->stealnum), (int)(v4));
  }
  if ( !lpString1 )
    (((UIBigMap *)this))->UIBigMap::LayoutBinkVideo(0, 1);
}

// 0x004531F0
void RoleAtt::_sub_4531F0()
{
  *((_BYTE *)&this->Remark.skillCount + 94) = 1;
}

// 0x00457F90
void RoleAtt::FormatAttributeText()
{
  __int16 v1; // ax
  __int16 v2; // ax
  __int16 v3; // ax
  __int16 v4; // ax
  __int16 v5; // ax
  __int16 v6; // ax
  __int16 v7; // ax
  __int16 v8; // ax
  __int16 v9; // ax
  __int16 v10; // ax
  __int16 v11; // ax
  __int16 v12; // ax
  __int16 v13; // ax
  __int16 v14; // ax
  __int16 v15; // ax
  __int16 v16; // ax
  __int16 v17; // ax
  __int16 v18; // ax
  __int16 v19; // ax
  __int16 v20; // ax
  __int16 v21; // ax
  __int16 v22; // ax
  __int16 v23; // ax
  __int16 v24; // ax
  __int16 v25; // ax
  __int16 v26; // ax
  __int16 v27; // ax
  __int16 v28; // si
  int v29; // esi
  CHAR *v30; // edi
  int v31; // esi
  CHAR *v32; // edi
  int v33; // esi
  CHAR *v34; // edi
  int v35; // esi
  CHAR *v36; // edi
  int *v37; // [esp+0x4] [ebp-0x448]
  unsigned __int8 v38; // [esp+0x8] [ebp-0x444]
  int *v39; // [esp+0xC] [ebp-0x440]
  int *v40; // [esp+0x10] [ebp-0x43C]
  int *v41; // [esp+0x14] [ebp-0x438]
  int *v42; // [esp+0x18] [ebp-0x434]
  _BYTE v43[28]; // [esp+0x1C] [ebp-0x430] BYREF
  __int16 v44; // [esp+0x38] [ebp-0x414]
  char v45; // [esp+0x3A] [ebp-0x412]
  CHAR v46[240]; // [esp+0x3C] [ebp-0x410] BYREF
  CHAR v47[80]; // [esp+0x12C] [ebp-0x320] BYREF
  CHAR v48[620]; // [esp+0x17C] [ebp-0x2D0] BYREF
  CHAR String2[100]; // [esp+0x3E8] [ebp-0x64] BYREF
  int v50; // [esp+0x450] [ebp+0x4]

  if ( v50 )
  {
    memset(v46, 0, sizeof(v46));
    memset(String2, 0, sizeof(String2));
    memset(v47, 0, sizeof(v47));
    memset(v48, 0, sizeof(v48));
    v40 = (int *)&byte_1010101;
    v41 = (int *)&byte_1010101;
    v42 = (int *)&byte_1010101;
    v37 = (int *)&byte_1010101;
    v39 = (int *)&byte_1010101;
    v38 = (unsigned __int8)&byte_1010101;
    memset(v43, 0, sizeof(v43));
    v44 = 0;
    v45 = 0;
    memset(&String1, 0, 0x100u);
    if ( *(_BYTE *)(v50 + 619) )
      sprintf(String2, "%s ", (const char *)g_bSlotFlag);
    else
      LOBYTE(v37) = 0;
    if ( *(_BYTE *)(v50 + 620) )
      sprintf(&String2[20], "%s ", (const char *)&g_bSlotFlag[256]);
    else
      BYTE1(v37) = 0;
    if ( *(_BYTE *)(v50 + 621) )
      sprintf(&String2[40], "%s ", (const char *)&g_bSlotFlag[512]);
    else
      BYTE2(v37) = 0;
    if ( *(_BYTE *)(v50 + 622) )
      sprintf(&String2[60], "%s ", byte_DC3F3C);
    else
      HIBYTE(v37) = 0;
    if ( *(_BYTE *)(v50 + 623) )
      sprintf(&String2[80], "%s ", byte_DC403C);
    else
      v38 = 0;
    v1 = *(_WORD *)(v50 + 644);
    if ( v1 <= 0 )
    {
      if ( v1 >= 0 )
      {
        LOBYTE(v40) = 0;
      }
      else if ( *(_BYTE *)(v50 + 631) == 1 )
      {
        sprintf(v46, "%s%d%% ", (const char *)&dword_DC413C, v1);
      }
      else
      {
        sprintf(v46, "%s%d ", &dword_DC413C, v1);
      }
    }
    else if ( *(_BYTE *)(v50 + 631) == 1 )
    {
      sprintf(v46, "%s+%d%% ", &dword_DC413C, v1);
    }
    else
    {
      sprintf(v46, "%s+%d ", (const char *)&dword_DC413C, v1);
    }
    v2 = *(_WORD *)(v50 + 646);
    if ( v2 <= 0 )
    {
      if ( v2 >= 0 )
      {
        BYTE1(v40) = 0;
      }
      else if ( *(_BYTE *)(v50 + 632) == 1 )
      {
        sprintf(&v46[20], "%s%d%% ", (const char *)&dword_DC423C, v2);
      }
      else
      {
        sprintf(&v46[20], "%s%d ", &dword_DC423C, v2);
      }
    }
    else if ( *(_BYTE *)(v50 + 632) == 1 )
    {
      sprintf(&v46[20], "%s+%d%% ", &dword_DC423C, v2);
    }
    else
    {
      sprintf(&v46[20], "%s+%d ", (const char *)&dword_DC423C, v2);
    }
    v3 = *(_WORD *)(v50 + 648);
    if ( v3 <= 0 )
    {
      if ( v3 >= 0 )
      {
        BYTE2(v40) = 0;
      }
      else if ( *(_BYTE *)(v50 + 633) == 1 )
      {
        sprintf(&v46[40], "%s%d%% ", (const char *)&dword_DC433C, v3);
      }
      else
      {
        sprintf(&v46[40], "%s%d ", &dword_DC433C, v3);
      }
    }
    else if ( *(_BYTE *)(v50 + 633) == 1 )
    {
      sprintf(&v46[40], "%s+%d%% ", &dword_DC433C, v3);
    }
    else
    {
      sprintf(&v46[40], "%s+%d ", (const char *)&dword_DC433C, v3);
    }
    v4 = *(_WORD *)(v50 + 650);
    if ( v4 <= 0 )
    {
      if ( v4 >= 0 )
        HIBYTE(v40) = 0;
      else
        sprintf(&v46[60], "%s%d ", (const char *)&g_szRoleName0, v4);
    }
    else
    {
      sprintf(&v46[60], "%s+%d ", (const char *)&g_szRoleName0, v4);
    }
    v5 = *(_WORD *)(v50 + 652);
    if ( v5 <= 0 )
    {
      if ( v5 >= 0 )
        LOBYTE(v41) = 0;
      else
        sprintf(&v46[80], "%s%d ", (const char *)&g_szRoleName1, v5);
    }
    else
    {
      sprintf(&v46[80], "%s+%d ", (const char *)&g_szRoleName1, v5);
    }
    v6 = *(_WORD *)(v50 + 654);
    if ( v6 <= 0 )
    {
      if ( v6 >= 0 )
        BYTE1(v41) = 0;
      else
        sprintf(&v46[100], "%s%d ", (const char *)&g_szRoleName2, v6);
    }
    else
    {
      sprintf(&v46[100], "%s+%d ", (const char *)&g_szRoleName2, v6);
    }
    v7 = *(_WORD *)(v50 + 656);
    if ( v7 <= 0 )
    {
      if ( v7 >= 0 )
        BYTE2(v41) = 0;
      else
        sprintf(&v46[120], "%s%d ", (const char *)&g_szRoleName3, v7);
    }
    else
    {
      sprintf(&v46[120], "%s+%d ", (const char *)&g_szRoleName3, v7);
    }
    v8 = *(_WORD *)(v50 + 768);
    if ( v8 <= 0 )
      LOBYTE(v39) = 0;
    else
      sprintf(v47, "%s-%d%% ", (const char *)&dword_DC483C, v8);
    v9 = *(_WORD *)(v50 + 770);
    if ( v9 <= 0 )
      BYTE1(v39) = 0;
    else
      sprintf(&v47[20], "%s-%d%% ", (const char *)&dword_DC493C, v9);
    v10 = *(_WORD *)(v50 + 772);
    if ( v10 <= 0 )
      BYTE2(v39) = 0;
    else
      sprintf(&v47[40], "%s+%d%% ", (const char *)&dword_DC4A3C, v10);
    v11 = *(_WORD *)(v50 + 774);
    if ( v11 <= 0 )
      HIBYTE(v39) = 0;
    else
      sprintf(&v47[60], "%s+%d%% ", (const char *)&dword_DC4B3C, v11);
    if ( *(_WORD *)(v50 + 710) == 1 )
    {
      sprintf(&v48[100], "%s 10%% ", (const char *)&dword_DCC13C);
      v43[5] = 1;
    }
    if ( *(_WORD *)(v50 + 712) == 1 )
    {
      sprintf(&v48[120], "%s 10%% ", (const char *)&dword_DCC23C);
      v43[6] = 1;
    }
    if ( *(_WORD *)(v50 + 714) == 1 )
    {
      sprintf(&v48[140], "%s 10%% ", (const char *)&dword_DCC33C);
      v43[7] = 1;
    }
    if ( *(_WORD *)(v50 + 716) == 1 )
    {
      sprintf(&v48[160], "%s 10%% ", (const char *)&dword_DCC43C);
      v43[8] = 1;
    }
    if ( *(_WORD *)(v50 + 718) == 1 )
    {
      sprintf(&v48[180], "%s 10%% ", (const char *)&dword_DCC53C);
      v43[9] = 1;
    }
    if ( *(_WORD *)(v50 + 720) == 1 )
    {
      sprintf(&v48[200], "%s 10%% ", (const char *)&dword_DCC63C);
      v43[10] = 1;
    }
    if ( *(_WORD *)(v50 + 722) == 1 )
    {
      sprintf(&v48[220], "%s 10%% ", (const char *)&dword_DCC73C);
      v43[11] = 1;
    }
    if ( *(_WORD *)(v50 + 724) == 1 )
    {
      sprintf(&v48[240], "%s 10%% ", (const char *)&dword_DCC83C);
      v43[12] = 1;
    }
    v12 = *(_WORD *)(v50 + 704);
    if ( v12 > 0 )
    {
      if ( v12 <= 1 )
        lstrcpyA((char *)&v48[40], byte_DC4C3C);
      else
        lstrcpyA((char *)&v48[40], (LPCSTR)&dword_DC7F3C);
      v43[2] = 1;
    }
    v13 = *(_WORD *)(v50 + 706);
    if ( v13 > 0 )
    {
      if ( v13 <= 1 )
        lstrcpyA((char *)&v48[60], byte_DC4D3C);
      else
        lstrcpyA((char *)&v48[60], (LPCSTR)&dword_DC803C);
      v43[3] = 1;
    }
    v14 = *(_WORD *)(v50 + 700);
    if ( v14 > 0 )
    {
      if ( v14 <= 1 )
        lstrcpyA(v48, byte_DC4E3C);
      else
        lstrcpyA(v48, (LPCSTR)&dword_DC813C);
      v43[0] = 1;
    }
    v15 = *(_WORD *)(v50 + 702);
    if ( v15 > 0 )
    {
      if ( v15 <= 1 )
        lstrcpyA((char *)&v48[20], byte_DC4F3C);
      else
        lstrcpyA((char *)&v48[20], (LPCSTR)&dword_DC823C);
      v43[1] = 1;
    }
    v16 = *(_WORD *)(v50 + 708);
    if ( v16 > 0 )
    {
      if ( v16 <= 1 )
        lstrcpyA((char *)&v48[80], byte_DC503C);
      else
        lstrcpyA((char *)&v48[80], (LPCSTR)&dword_DC833C);
      v43[4] = 1;
    }
    v17 = *(_WORD *)(v50 + 726);
    if ( v17 > 0 )
    {
      if ( v17 <= 1 )
        lstrcpyA((char *)&v48[260], byte_DC513C);
      else
        lstrcpyA((char *)&v48[260], (LPCSTR)&dword_DCB63C);
      v43[13] = 1;
    }
    v18 = *(_WORD *)(v50 + 728);
    if ( v18 > 0 )
    {
      if ( v18 <= 1 )
        lstrcpyA((char *)&v48[280], byte_DC523C);
      else
        lstrcpyA((char *)&v48[280], (LPCSTR)&dword_DCB73C);
      v43[14] = 1;
    }
    v19 = *(_WORD *)(v50 + 730);
    if ( v19 > 0 )
    {
      if ( v19 <= 1 )
        lstrcpyA((char *)&v48[300], byte_DC533C);
      else
        lstrcpyA((char *)&v48[300], (LPCSTR)&dword_DCB83C);
      v43[15] = 1;
    }
    v20 = *(_WORD *)(v50 + 732);
    if ( v20 > 0 )
    {
      if ( v20 <= 1 )
        lstrcpyA((char *)&v48[320], byte_DC543C);
      else
        lstrcpyA((char *)&v48[320], (LPCSTR)&dword_DCB93C);
      v43[16] = 1;
    }
    v21 = *(_WORD *)(v50 + 734);
    if ( v21 > 0 )
    {
      if ( v21 <= 1 )
        lstrcpyA((char *)&v48[340], byte_DC553C);
      else
        lstrcpyA((char *)&v48[340], (LPCSTR)&dword_DCBA3C);
      v43[17] = 1;
    }
    v22 = *(_WORD *)(v50 + 736);
    if ( v22 > 0 )
    {
      if ( v22 <= 1 )
        lstrcpyA((char *)&v48[360], byte_DC563C);
      else
        lstrcpyA((char *)&v48[360], (LPCSTR)&dword_DCBB3C);
      v43[18] = 1;
    }
    v23 = *(_WORD *)(v50 + 738);
    if ( v23 > 0 )
    {
      if ( v23 <= 1 )
        lstrcpyA((char *)&v48[380], byte_DCBC3C);
      else
        lstrcpyA((char *)&v48[380], (LPCSTR)&dword_DC573C);
      v43[19] = 1;
    }
    v24 = *(_WORD *)(v50 + 740);
    if ( v24 > 0 )
    {
      if ( v24 <= 1 )
        lstrcpyA((char *)&v48[400], byte_DC583C);
      else
        lstrcpyA((char *)&v48[400], (LPCSTR)&dword_DCBD3C);
      v43[20] = 1;
    }
    v25 = *(_WORD *)(v50 + 742);
    if ( v25 > 0 )
    {
      if ( v25 <= 1 )
        lstrcpyA((char *)&v48[420], byte_DC593C);
      else
        lstrcpyA((char *)&v48[420], (LPCSTR)&dword_DCBE3C);
      v43[21] = 1;
    }
    v26 = *(_WORD *)(v50 + 744);
    if ( v26 > 0 )
    {
      if ( v26 <= 1 )
        lstrcpyA((char *)&v48[440], byte_DC5A3C);
      else
        lstrcpyA((char *)&v48[440], (LPCSTR)&dword_DCBF3C);
      v43[22] = 1;
    }
    if ( *(__int16 *)(v50 + 750) > 0 )
    {
      lstrcpyA((char *)&v48[500], byte_DC5B3C);
      v43[25] = 1;
    }
    v27 = *(_WORD *)(v50 + 752);
    if ( v27 > 0 )
    {
      if ( v27 <= 1 )
        lstrcpyA((char *)&v48[520], byte_DC5C3C);
      else
        lstrcpyA((char *)&v48[520], (LPCSTR)&dword_DCC13C);
      v43[26] = 1;
    }
    v28 = *(_WORD *)(v50 + 748);
    if ( v28 > 0 )
    {
      if ( v28 <= 1 )
        lstrcpyA((char *)&v48[480], byte_DCC93C);
      else
        lstrcpyA((char *)&v48[480], (LPCSTR)&dword_DCCA3C);
      v43[24] = 1;
    }
    lstrcpyA((char *)&String1, unk_C10D38);
    v29 = 0;
    v30 = String2;
    do
    {
      if ( *((_BYTE *)&v37 + v29) )
        lstrcatA((char *)&String1, v30);
      ++v29;
      v30 += 20;
    }
    while ( v29 < 5 );
    v31 = 0;
    v32 = v46;
    do
    {
      if ( *((_BYTE *)&v40 + v31) )
        lstrcatA((char *)&String1, v32);
      ++v31;
      v32 += 20;
    }
    while ( v31 < 12 );
    v33 = 0;
    v34 = v47;
    do
    {
      if ( *((_BYTE *)&v39 + v33) )
        lstrcatA((char *)&String1, v34);
      ++v33;
      v34 += 20;
    }
    while ( v33 < 4 );
    v35 = 0;
    v36 = v48;
    do
    {
      if ( v43[v35] )
        lstrcatA((char *)&String1, v36);
      ++v35;
      v36 += 20;
    }
    while ( v35 < 31 );
  }
}

// 0x00530810
void RoleAtt::LoadModelAndInit()
{
  gbLightObj *v2; // eax
  gbLightObj *v3; // esi

  sub_5306A0((int)this, dword_58619C);
  (((UICoverFrm *)&this->ImageID[16]))->UICoverFrm::LoadFromFile(aBasedataSkeePa);
  this->fightstate[20] = 1;
  this->fightstate[21] = 0;
  (((Actor *)this))->Actor::ResetTransformState();
  v2 = (gbLightObj *)operator new(0xD8u);
  if ( v2 )
  {
    *((_DWORD *)((gbVolumeModifier *)v2) + 1) = 1;
    v2->m_BoundSphere.center.x = 0.0f;
    v2->m_BoundSphere.center.y = 0.0f;
    v2->m_BoundSphere.center.z = 0.0f;
    v2->m_SysLight.position.x = 0.0f;
    v2->m_SysLight.position.y = 0.0f;
    v2->m_SysLight.position.z = 0.0f;
    v2->m_SysLight.direction.x = 0.0f;
    v2->m_SysLight.direction.y = 0.0f;
    v2->m_SysLight.direction.z = 0.0f;
    v3 = (gbLightObj *)v2;
  }
  else
  {
    v3 = 0;
  }
  (((gbLightObj *)v3))->gbLightObj::Init(LIGHT_SPOT);
  v3->m_Ambient.Red = 1.0f;
  v3->m_Ambient.Green = 1.0f;
  v3->m_Ambient.Blue = 1.0f;
  v3->m_Ambient.Alpha = 1.0f;
  v3->m_UseSpecular = 1;
  v3->m_UseDiffuse = 1;
  v3->m_Color.Red = 0.5f;
  v3->m_Color.Green = 0.5f;
  v3->m_Color.Blue = 0.5f;
  v3->m_Color.Alpha = 1.0f;
  v3->m_FarEnd = 100.0f;
  v3->m_FarStart = 100.0f;
  (((gbVolModNode *)((char *)&this->Remark.skillCount + 2)))->gbVolModNode::SetVolModObj(v3);
  (((gbRefObject *)v3))->gbRefObject::Release();
  HIBYTE(this->skill[2]) = 1;
  LOBYTE(this->skill[3]) = 1;
}

// 0x00530960
int RoleAtt::SetSAIDAndImage(int *pnVal)
{
  float v2; // st7
  int v3; // eax
  int result; // eax

  v2 = *(float *)&this->SAID;
  *(_DWORD *)&this->ImageID[28] = (unsigned long)pnVal;
  v3 = (unsigned long)*pnVal;
  *(float *)v3 = v2;
  *(_DWORD *)(v3 + 4) = 0;
  (((UIScene *)*(UIScene **)&this->ImageID[28]))->UIScene::LoadMapData(*(_DWORD *)&this->fightstate[24]);
  return result;
}

// 0x00531010
void RoleAtt::ApplySpeedFactor(float fVal)
{
  float v2; // st7
  float v3; // st7
  float v4; // eax

  v2 = fVal * this->append[6];
  if ( BYTE2(this->append[3]) )
  {
    v3 = v2 + this->append[5];
    this->append[5] = v3;
    this->append[9] = v3 + *(float *)this->rolevalue;
    if ( v3 >= this->append[4] )
      BYTE2(this->append[3]) = 0;
  }
  else
  {
    this->append[9] = this->append[9] - v2;
    this->append[6] = this->append[8] + this->append[6];
    if ( this->append[9] <= (double)*(float *)this->rolevalue )
    {
      LODWORD(this->append[9]) = this->rolevalue[0];
      BYTE2(this->append[3]) = 1;
      HIBYTE(this->append[3]) = 1;
      v4 = this->append[7];
      this->append[5] = 0.0;
      this->append[6] = v4;
      UIAnimateCtrlEX_SwapBuffer(0);
    }
  }
}

// 0x005310C0
void RoleAtt::UpdateTimedBuff(float fDelta)
{
  float v3; // st7
  Actor *id; // ecx

  if ( *(float *)&this->rolevalue[6] > 0.0f )
  {
    v3 = *(float *)&this->rolevalue[6] - fDelta * 0.5f;
    *(float *)&this->rolevalue[6] = v3;
    if ( v3 < 0.0f )
    {
      id = (Actor *)this->id;
      this->rolevalue[6] = 0;
      (((Actor *)id))->Actor::CompareActionName(0, 0);
    }
  }
  if ( (((ScreenEffectMgr *)*(ScreenEffectMgr **)(this->att[0] + 1312)))->ScreenEffectMgr::IsFadeActive()
    && *(float *)&this->rolevalue[6] == 0.0f
    && !this->fightstate[22] )
  {
    (((RoleSystem *)this->att[0]))->RoleSystem::ShowHideUI(BYTE2(this->skill[2]));
    this->fightstate[22] = 1;
  }
}

// 0x00531160
char RoleAtt::InterpolateStats(int nVal)
{
  float *v3; // eax
  float *v4; // edi
  s_RoleState *v5; // ecx
  int v6; // eax
  float v7; // st7
  float v8; // st6
  int v9; // edx
  int v10; // eax
  float lv; // ecx
  int v12; // edx
  int v13; // eax
  int v15; // [esp+0xC] [ebp-0x8]
  int v16; // [esp+0x10] [ebp-0x4]

  v3 = (float *)(((ArcSceneMonster *)&this->ImageID[16]))->ArcSceneMonster::CheckDistance(*(float *)&this->rolevalue[5]);
  v4 = (float *)v3;
  if ( v3 )
  {
    v7 = *v3 - this->lv;
    *(float *)&v15 = v3[1] - *(float *)this->rolevalue;
    v8 = v3[2] - *(float *)&this->rolevalue[1];
    this->rolevalue[3] = v15;
    *(float *)&v16 = v8;
    *(float *)&this->rolevalue[2] = v7;
    this->rolevalue[4] = v16;
    (((gbVec3D *)&this->rolevalue[2]))->gbVec3D::Normalize();
    v9 = *(_DWORD *)this->name;
    v10 = *(_DWORD *)&this->name[4];
    this->att[1] = this->att[4];
    lv = this->lv;
    this->att[2] = v9;
    v12 = this->rolevalue[0];
    this->att[3] = v10;
    v13 = this->rolevalue[1];
    *(float *)&this->att[4] = lv;
    *(_DWORD *)this->name = v12;
    *(_DWORD *)&this->name[4] = v13;
    this->lv = *v4;
    this->rolevalue[0] = (int)v4[1];
    v6 = *((_DWORD *)v4 + 2);
    this->rolevalue[1] = v6;
  }
  else
  {
    v5 = (s_RoleState *)*(s_RoleState **)this->skill_lv;
    this->fightstate[0] = 0;
    (((s_RoleState *)v5))->s_RoleState::CopyRoleData(0, 0);
    BYTE1(this->skill[3]) = 1;
    LOBYTE(v6) = UpdateAnimState((Actor *)this, 0);
  }
  return v6;
}

// 0x005322F0
int RoleAtt::SwitchPage(int nPageIdx, int nParam)
{
  char *v4; // esi
  int v5; // edi

  v4 = (char *)&this[3].Remark + 426;
  v5 = 10;
  do
  {
    (**((void ( ***)(int, _DWORD))v4 - 380))((int)((int)(v4 - 1520)), (_DWORD)(0));
    (**(void ( ***)(char *, _DWORD))v4)((char *)(v4), (_DWORD)(0));
    v4 += 152;
    --v5;
  }
  while ( v5 );
  (**(void ( ***)(char *, int))&this[1].name[152 * nPageIdx + 16])((char *)(&this[1].name[152 * nPageIdx + 16]), (int)(1));
  return (**(int ( ***)(char *, int))((char *)&this[3].Remark + 152 * nParam + 426))((char *)((char *)&this[3].Remark + 152 * nParam + 426), (int)(1));
}

// 0x00533FE0
void RoleAtt::UpdatePosition(float fX, float fY, float fZ)
{
  char v4; // al
  float v5; // st7
  long double v6; // st7
  long double v7; // st7
  float v8; // st7
  long double v9; // st7
  long double v10; // st7
  long double v11; // st7
  long double v12; // st7

  *(float *)&this->rolevalue[10] = fX;
  *(float *)&this->rolevalue[11] = fY;
  *(float *)this->fightstate = fZ;
  *(float *)&this->ImageID[28] = fX;
  *(float *)this->att = fY;
  v4 = this->fightstate[17];
  *(float *)&this->att[1] = fZ;
  if ( v4 )
  {
    if ( *(float *)&this->fightstate[20] > 0.0f )
    {
      if ( this->SAID )
      {
        v6 = this->Escape + *(float *)this->haogan;
        *(float *)this->haogan = v6;
        if ( *(float *)&this->fightstate[20] <= fabs(v6) )
        {
          *(_DWORD *)this->haogan = 0;
          this->SAID = 0;
        }
      }
      else
      {
        v7 = *(float *)this->haogan - this->Escape;
        *(float *)this->haogan = v7;
        if ( *(float *)&this->fightstate[20] >= fabs(v7) )
        {
          *(_DWORD *)this->haogan = 0;
          this->SAID = 1;
        }
      }
      v5 = *(float *)this->haogan;
    }
    else
    {
      v5 = 0.0f;
    }
    *(float *)&this->rolevalue[10] = v5 + fX;
    if ( *(float *)&this->fightstate[24] > 0.0f )
    {
      if ( *(&this->SAID + 1) )
      {
        v9 = this->Escape + *(float *)&this->haogan[2];
        *(float *)&this->haogan[2] = v9;
        if ( *(float *)&this->fightstate[24] <= fabs(v9) )
        {
          *(_DWORD *)&this->haogan[2] = 0;
          this->SAID = 0;
        }
      }
      else
      {
        v10 = *(float *)&this->haogan[2] - this->Escape;
        *(float *)&this->haogan[2] = v10;
        if ( *(float *)&this->fightstate[24] >= fabs(v10) )
        {
          *(_DWORD *)&this->haogan[2] = 0;
          *(&this->SAID + 1) = 1;
        }
      }
      v8 = *(float *)&this->haogan[2];
    }
    else
    {
      v8 = 0.0f;
    }
    *(float *)&this->rolevalue[11] = v8 + fY;
    if ( *(float *)&this->fightstate[28] <= 0.0f )
    {
      *(float *)this->fightstate = fZ + 0.0;
      return;
    }
    if ( *(&this->SAID + 2) )
    {
      v11 = this->Escape + *(float *)&this->haogan[4];
      *(float *)&this->haogan[4] = v11;
      if ( *(float *)&this->fightstate[28] <= fabs(v11) )
      {
        *(_DWORD *)&this->haogan[4] = 0;
        *(&this->SAID + 2) = 0;
        *(float *)this->fightstate = *(float *)&this->haogan[4] + fZ;
        return;
      }
    }
    else
    {
      v12 = *(float *)&this->haogan[4] - this->Escape;
      *(float *)&this->haogan[4] = v12;
      if ( *(float *)&this->fightstate[28] >= fabs(v12) )
      {
        *(_DWORD *)&this->haogan[4] = 0;
        *(&this->SAID + 2) = 1;
      }
    }
    *(float *)this->fightstate = *(float *)&this->haogan[4] + fZ;
  }
}

// 0x00534210
void RoleAtt::SetPositionFromInts(int nX, int nY, int nZ)
{
  float v4; // st7
  char v5; // al
  float v6; // st6
  long double v7; // st6
  long double v8; // st6
  float v9; // st7
  long double v10; // st7
  long double v11; // st7
  long double v12; // st7
  long double v13; // st7
  float v14; // [esp+0x0] [ebp-0x4]
  int nXa; // [esp+0x8] [ebp+0x4]

  this->rolevalue[10] = nX;
  this->rolevalue[11] = nY;
  *(_DWORD *)this->fightstate = nZ;
  v4 = *(float *)&this->rolevalue[10];
  v5 = this->fightstate[17];
  *(float *)&this->ImageID[28] = *(float *)&this->rolevalue[10];
  nXa = this->rolevalue[11];
  this->att[0] = nXa;
  v14 = *(float *)this->fightstate;
  *(float *)&this->att[1] = v14;
  if ( v5 )
  {
    if ( *(float *)&this->fightstate[20] > 0.0f )
    {
      if ( this->SAID )
      {
        v7 = this->Escape + *(float *)this->haogan;
        *(float *)this->haogan = v7;
        if ( *(float *)&this->fightstate[20] <= fabs(v7) )
        {
          *(_DWORD *)this->haogan = 0;
          this->SAID = 0;
        }
      }
      else
      {
        v8 = *(float *)this->haogan - this->Escape;
        *(float *)this->haogan = v8;
        if ( *(float *)&this->fightstate[20] >= fabs(v8) )
        {
          *(_DWORD *)this->haogan = 0;
          this->SAID = 1;
        }
      }
      v6 = *(float *)this->haogan;
    }
    else
    {
      v6 = 0.0f;
    }
    *(float *)&this->rolevalue[10] = v4 + v6;
    if ( *(float *)&this->fightstate[24] > 0.0f )
    {
      if ( *(&this->SAID + 1) )
      {
        v10 = this->Escape + *(float *)&this->haogan[2];
        *(float *)&this->haogan[2] = v10;
        if ( *(float *)&this->fightstate[24] <= fabs(v10) )
        {
          *(_DWORD *)&this->haogan[2] = 0;
          this->SAID = 0;
        }
      }
      else
      {
        v11 = *(float *)&this->haogan[2] - this->Escape;
        *(float *)&this->haogan[2] = v11;
        if ( *(float *)&this->fightstate[24] >= fabs(v11) )
        {
          *(_DWORD *)&this->haogan[2] = 0;
          *(&this->SAID + 1) = 1;
        }
      }
      v9 = *(float *)&this->haogan[2];
    }
    else
    {
      v9 = 0.0f;
    }
    *(float *)&this->rolevalue[11] = *(float *)&nXa + v9;
    if ( *(float *)&this->fightstate[28] > 0.0f )
    {
      if ( *(&this->SAID + 2) )
      {
        v12 = this->Escape + *(float *)&this->haogan[4];
        *(float *)&this->haogan[4] = v12;
        if ( *(float *)&this->fightstate[28] <= fabs(v12) )
        {
          *(_DWORD *)&this->haogan[4] = 0;
          *(&this->SAID + 2) = 0;
        }
      }
      else
      {
        v13 = *(float *)&this->haogan[4] - this->Escape;
        *(float *)&this->haogan[4] = v13;
        if ( *(float *)&this->fightstate[28] >= fabs(v13) )
        {
          *(_DWORD *)&this->haogan[4] = 0;
          *(&this->SAID + 2) = 1;
        }
      }
      *(float *)this->fightstate = v14 + *(float *)&this->haogan[4];
    }
    else
    {
      *(float *)this->fightstate = v14 + 0.0;
    }
  }
}

// 0x00534450
void RoleAtt::InterpolateMotion(float f1, float f2, float f3, float f4, float f5)
{
  float v7; // st7
  float exp; // st7
  float v9; // st7
  float v10; // st7
  float v11; // st7
  float v12; // st7
  float v13; // st6
  float v14; // st6
  float v15; // st7
  float v16; // st7
  float v17; // st6
  int v18; // eax
  float v19; // st7
  float v20; // st6
  long double v21; // st6
  long double v22; // st6
  float v23; // st7
  long double v24; // st7
  long double v25; // st7
  gbVec3D v26; // [esp+0x0] [ebp-0x18] BYREF
  int v27; // [esp+0x10] [ebp-0x8]
  int v28; // [esp+0x14] [ebp-0x4]
  float f1a; // [esp+0x1C] [ebp+0x4]
  float f4a; // [esp+0x28] [ebp+0x10]

  v7 = f1 - *(float *)&this->rolevalue[10];
  *(float *)&this->rolevalue[8] = f2;
  *(float *)&this->rolevalue[7] = f1;
  *(float *)&this->rolevalue[9] = f3;
  v26.x = v7;
  v26.y = f2 - *(float *)&this->rolevalue[11];
  v26.z = f3 - *(float *)this->fightstate;
  (((gbVec3D *)&v26))->gbVec3D::Normalize();
  if ( this->fightstate[16] )
  {
    if ( this->RoundNum > 0.0f )
    {
      if ( *(&this->SAID + 3) )
      {
        v9 = this->Escape + this->exp;
        this->exp = v9;
        if ( this->RoundNum <= fabs(v9) )
        {
          this->exp = 0.0f;
          *(&this->SAID + 3) = 0;
        }
      }
      else
      {
        v10 = this->exp - this->Escape;
        this->exp = v10;
        if ( this->RoundNum >= fabs(v10) )
        {
          this->exp = 0.0f;
          *(&this->SAID + 3) = 1;
        }
      }
      exp = this->exp;
    }
    else
    {
      exp = 0.0f;
    }
    v11 = exp + f4;
    f1a = v11;
    v26.x = v11 * v26.x;
    v12 = f1a * v26.y;
    v26.z = f1a * v26.z;
    if ( this->RoundNum > 0.0f )
    {
      if ( *(&this->SAID + 3) )
      {
        v13 = this->Escape + this->exp;
        this->exp = v13;
        if ( this->RoundNum <= fabs(v13) )
        {
          this->exp = 0.0f;
          *(&this->SAID + 3) = 0;
        }
      }
      else
      {
        v14 = this->exp - this->Escape;
        this->exp = v14;
        if ( this->RoundNum >= fabs(v14) )
        {
          this->exp = 0.0f;
          *(&this->SAID + 3) = 1;
        }
      }
      *(float *)&this->ImageID[8] = this->exp + f4;
    }
    else
    {
      *(float *)&this->ImageID[8] = f4 + 0.0;
    }
  }
  else
  {
    v15 = v26.x * f4;
    *(float *)&this->ImageID[8] = f4;
    v26.x = v15;
    v12 = v26.y * f4;
    v26.z = v26.z * f4;
  }
  *(float *)&this->ImageID[12] = f5;
  v26.y = v12 + f5;
  v16 = v26.x + *(float *)&this->rolevalue[10];
  *(float *)&v27 = v26.y + *(float *)&this->rolevalue[11];
  v17 = v26.z + *(float *)this->fightstate;
  this->rolevalue[8] = v27;
  *(float *)&v28 = v17;
  v18 = v28;
  *(float *)&this->rolevalue[7] = v16;
  this->rolevalue[9] = v18;
  v19 = *(float *)&this->rolevalue[7];
  *(_DWORD *)&this->ImageID[24] = this->rolevalue[9];
  LOBYTE(v18) = this->fightstate[16];
  *(float *)&this->ImageID[16] = v19;
  f4a = *(float *)&this->rolevalue[8];
  *(float *)&this->ImageID[20] = f4a;
  if ( (_BYTE)v18 )
  {
    if ( *(float *)&this->fightstate[20] > 0.0f )
    {
      if ( this->SAID )
      {
        v21 = this->Escape + *(float *)this->haogan;
        *(float *)this->haogan = v21;
        if ( *(float *)&this->fightstate[20] <= fabs(v21) )
        {
          *(_DWORD *)this->haogan = 0;
          this->SAID = 0;
        }
      }
      else
      {
        v22 = *(float *)this->haogan - this->Escape;
        *(float *)this->haogan = v22;
        if ( *(float *)&this->fightstate[20] >= fabs(v22) )
        {
          *(_DWORD *)this->haogan = 0;
          this->SAID = 1;
        }
      }
      v20 = *(float *)this->haogan;
    }
    else
    {
      v20 = 0.0f;
    }
    *(float *)&this->rolevalue[7] = v19 + v20;
    if ( *(float *)&this->fightstate[24] > 0.0f )
    {
      if ( *(&this->SAID + 1) )
      {
        v24 = this->Escape + *(float *)&this->haogan[2];
        *(float *)&this->haogan[2] = v24;
        if ( *(float *)&this->fightstate[24] <= fabs(v24) )
        {
          *(_DWORD *)&this->haogan[2] = 0;
          this->SAID = 0;
        }
      }
      else
      {
        v25 = *(float *)&this->haogan[2] - this->Escape;
        *(float *)&this->haogan[2] = v25;
        if ( *(float *)&this->fightstate[24] >= fabs(v25) )
        {
          *(_DWORD *)&this->haogan[2] = 0;
          *(&this->SAID + 1) = 1;
        }
      }
      v23 = *(float *)&this->haogan[2];
    }
    else
    {
      v23 = 0.0f;
    }
    *(float *)&this->rolevalue[8] = f4a + v23;
    *(float *)&this->rolevalue[9] = this->RoleAtt::UpdateOscillation() + *(float *)&this->ImageID[24];
  }
}

// 0x00534810
void RoleAtt::UpdateDirectionalMotion(gbVec3D pData, float fVal, float fVal2)
{
  float y; // ecx
  float z; // edx
  float exp; // st7
  float v8; // st7
  float v9; // st7
  float v10; // st7
  float v11; // st7
  float v12; // st6
  float v13; // st6
  float v14; // st7
  float v15; // st7
  float v16; // st7
  float v17; // st6
  float v18; // st7
  char v19; // al
  float v20; // st6
  long double v21; // st6
  long double v22; // st6
  float v23; // st7
  long double v24; // st7
  long double v25; // st7
  float v26; // [esp+0x4] [ebp-0x10]
  int v27; // [esp+0xC] [ebp-0x8]
  int v28; // [esp+0x10] [ebp-0x4]

  (((gbVec3D *)&pData))->gbVec3D::Normalize();
  y = pData.y;
  z = pData.z;
  this->att[2] = LODWORD(pData.x);
  *(float *)&this->att[3] = y;
  *(float *)&this->att[4] = z;
  if ( this->fightstate[16] )
  {
    if ( this->RoundNum > 0.0f )
    {
      if ( *(&this->SAID + 3) )
      {
        v8 = this->Escape + this->exp;
        this->exp = v8;
        if ( this->RoundNum <= fabs(v8) )
        {
          this->exp = 0.0f;
          *(&this->SAID + 3) = 0;
        }
      }
      else
      {
        v9 = this->exp - this->Escape;
        this->exp = v9;
        if ( this->RoundNum >= fabs(v9) )
        {
          this->exp = 0.0f;
          *(&this->SAID + 3) = 1;
        }
      }
      exp = this->exp;
    }
    else
    {
      exp = 0.0f;
    }
    v10 = exp + fVal;
    v26 = v10;
    pData.x = v10 * pData.x;
    v11 = v26 * pData.y;
    pData.z = pData.z * v26;
    if ( this->RoundNum > 0.0f )
    {
      if ( *(&this->SAID + 3) )
      {
        v12 = this->Escape + this->exp;
        this->exp = v12;
        if ( this->RoundNum <= fabs(v12) )
        {
          this->exp = 0.0f;
          *(&this->SAID + 3) = 0;
        }
      }
      else
      {
        v13 = this->exp - this->Escape;
        this->exp = v13;
        if ( this->RoundNum >= fabs(v13) )
        {
          this->exp = 0.0f;
          *(&this->SAID + 3) = 1;
        }
      }
      *(float *)&this->ImageID[8] = this->exp + fVal;
    }
    else
    {
      *(float *)&this->ImageID[8] = fVal + 0.0;
    }
  }
  else
  {
    v14 = pData.x * fVal;
    *(float *)&this->ImageID[8] = fVal;
    pData.x = v14;
    v11 = pData.y * fVal;
    pData.z = pData.z * fVal;
  }
  v15 = v11 + fVal2;
  *(float *)&this->ImageID[12] = fVal2;
  pData.y = v15;
  v16 = pData.x + *(float *)&this->rolevalue[10];
  *(float *)&v27 = pData.y + *(float *)&this->rolevalue[11];
  v17 = pData.z + *(float *)this->fightstate;
  this->rolevalue[8] = v27;
  *(float *)&v28 = v17;
  *(float *)&this->rolevalue[7] = v16;
  this->rolevalue[9] = v28;
  v18 = *(float *)&this->rolevalue[7];
  *(_DWORD *)&this->ImageID[24] = this->rolevalue[9];
  v19 = this->fightstate[16];
  *(float *)&this->ImageID[16] = v18;
  fVal = *(float *)&this->rolevalue[8];
  *(float *)&this->ImageID[20] = fVal;
  if ( v19 )
  {
    if ( *(float *)&this->fightstate[20] > 0.0f )
    {
      if ( this->SAID )
      {
        v21 = this->Escape + *(float *)this->haogan;
        *(float *)this->haogan = v21;
        if ( *(float *)&this->fightstate[20] <= fabs(v21) )
        {
          *(_DWORD *)this->haogan = 0;
          this->SAID = 0;
        }
      }
      else
      {
        v22 = *(float *)this->haogan - this->Escape;
        *(float *)this->haogan = v22;
        if ( *(float *)&this->fightstate[20] >= fabs(v22) )
        {
          *(_DWORD *)this->haogan = 0;
          this->SAID = 1;
        }
      }
      v20 = *(float *)this->haogan;
    }
    else
    {
      v20 = 0.0f;
    }
    *(float *)&this->rolevalue[7] = v18 + v20;
    if ( *(float *)&this->fightstate[24] > 0.0f )
    {
      if ( *(&this->SAID + 1) )
      {
        v24 = this->Escape + *(float *)&this->haogan[2];
        *(float *)&this->haogan[2] = v24;
        if ( *(float *)&this->fightstate[24] <= fabs(v24) )
        {
          *(_DWORD *)&this->haogan[2] = 0;
          this->SAID = 0;
        }
      }
      else
      {
        v25 = *(float *)&this->haogan[2] - this->Escape;
        *(float *)&this->haogan[2] = v25;
        if ( *(float *)&this->fightstate[24] >= fabs(v25) )
        {
          *(_DWORD *)&this->haogan[2] = 0;
          *(&this->SAID + 1) = 1;
        }
      }
      v23 = *(float *)&this->haogan[2];
    }
    else
    {
      v23 = 0.0f;
    }
    *(float *)&this->rolevalue[8] = fVal + v23;
    *(float *)&this->rolevalue[9] = this->RoleAtt::UpdateOscillation() + *(float *)&this->ImageID[24];
  }
}

// 0x00534BA0
int RoleAtt::SetFightState(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        char pData,
        char pData2)
{
  int result; // eax

  this->fightstate[16] = pData;
  this->fightstate[17] = pData2;
  *(_DWORD *)&this->fightstate[20] = nVal;
  *(_DWORD *)&this->fightstate[24] = nVal2;
  *(_DWORD *)&this->fightstate[28] = nVal3;
  result = nVal5;
  LODWORD(this->RoundNum) = nVal4;
  LODWORD(this->Escape) = nVal5;
  return result;
}

// 0x00534BF0
int RoleAtt::ResetFightState()
{
  int result; // eax

  result = 0;
  this->Escape = 1.0f;
  this->fightstate[16] = 0;
  this->RoundNum = 0.0f;
  *(_DWORD *)&this->fightstate[28] = 0;
  *(_DWORD *)&this->fightstate[24] = 0;
  *(_DWORD *)&this->fightstate[20] = 0;
  *(&this->SAID + 3) = 0;
  *(&this->SAID + 2) = 0;
  *(&this->SAID + 1) = 0;
  this->SAID = 0;
  this->exp = 0.0f;
  *(_DWORD *)&this->haogan[4] = 0;
  *(_DWORD *)&this->haogan[2] = 0;
  *(_DWORD *)this->haogan = 0;
  return result;
}

// 0x00534C50
double RoleAtt::UpdateOscillation()
{
  long double v2; // st7
  long double v3; // st7

  if ( *(float *)&this->fightstate[28] <= 0.0f )
    return 0.0;
  if ( *(&this->SAID + 2) )
  {
    v2 = this->Escape + *(float *)&this->haogan[4];
    *(float *)&this->haogan[4] = v2;
    if ( *(float *)&this->fightstate[28] <= fabs(v2) )
    {
      *(_DWORD *)&this->haogan[4] = 0;
      *(&this->SAID + 2) = 0;
      return *(float *)&this->haogan[4];
    }
  }
  else
  {
    v3 = *(float *)&this->haogan[4] - this->Escape;
    *(float *)&this->haogan[4] = v3;
    if ( *(float *)&this->fightstate[28] >= fabs(v3) )
    {
      *(_DWORD *)&this->haogan[4] = 0;
      *(&this->SAID + 2) = 1;
    }
  }
  return *(float *)&this->haogan[4];
}
