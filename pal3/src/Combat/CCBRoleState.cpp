#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBRoleState.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445D20(_DWORD *_this, int a2, int a3); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_445FE0(void *a2); // from annotations
char sub_4499A0(void *_this, unsigned int a2, int a3); // from annotations
int sub_4DB940(_BYTE *_this, char a2); // from annotations
int sub_4FEEF0(...);

double EditBox_GetFloat(HWND hWnd); // from annotations
BOOL EditBox_IsModified(HWND hWnd); // from annotations
LRESULT EditBox_SetInt(HWND hWnd, int nValue); // from annotations
LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];
extern char byte_5B1A26;
extern char byte_5D897C[8];
extern char byte_5D8984[8];
extern char byte_5D898C[8];
extern char byte_5D8994[8];
extern char byte_5D899C[8];
extern char byte_FFFFFF;
extern int dword_17A9C50[];
extern int dword_17A9D50[];
extern int dword_17A9E50[];
extern int dword_17A9F50[];
extern int dword_17AA050[];
extern int dword_17AA150[];
extern int dword_17AA250[];
extern int dword_17AA350[];
extern int dword_17AA450[];
extern int dword_17AA808[];
extern int dword_17AA818[];
extern int dword_17AA828[];
extern int dword_17AA838[];
extern int dword_17AA848[];
extern int dword_17AA858[];
extern int dword_56B294[];
extern _DWORD dword_5D8DB8[1];
extern _DWORD dword_5D8DBC[1];
extern _DWORD dword_5D8DC4[15];
extern CCBUI * dword_5D8E98;
extern CCBUI * dword_5D8EC8;
extern CCBUI * dword_5D8EE0;
extern CCBUI * dword_5D8EF8;
extern CCBUI * dword_5D8F0C;
extern int dword_C10CC4;
extern int dword_DD553C[];
extern float flt_17AA550[];
extern void * off_5B0DA4;
extern const char * off_5B0E2C;
extern void *off_5B1604;
extern vtbl_0056B364 stru_56B364;
extern RoleSystem stru_C059A0;
extern RoleSystem stru_C08160;
extern char unk_5D8974;
extern unsigned __int8 unk_5DFDEB;
extern unsigned int unk_5DFDEC;

// 0x0043DE40
void CCBRoleState::Destroy(UIListBox *thisa, int a2)
{
  gbRefObject *m_bfocus; // ecx

  m_bfocus = (gbRefObject *)this->_embed_UIFrameWnd_168.m_bfocus;
  if ( m_bfocus )
  {
    ((gbRefObject *)m_bfocus)->Release();
    this->_embed_UIFrameWnd_168.m_bfocus = 0;
  }
  ((UIWnd *)this)->HideAll();
}

// 0x00449F00
__int64 CCBRoleState::CalcSpringForce(int nVal, int nVal2)
{
  double v4; // st7
  __int64 result; // rax
  float nVala; // [esp+0x10] [ebp+0x4]

  ((CCBUIPanel *)this)->EnsureSize(nVal, nVal2);
  *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[6][3] = nVal;
  *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[7][1] = nVal2;
  v4 = (double)*(int *)&this->m_RoleXor[3].bMagicMastered[6][3];
  *(float *)&this->m_RoleXor[3].bMagicMastered[7][5] = v4;
  nVala = (float)*(int *)&this->m_RoleXor[3].bMagicMastered[7][1];
  *(float *)&this->m_RoleXor[3].bMagicMastered[8][3] = nVala;
  *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[6][3] = (__int64)v4;
  result = (__int64)nVala;
  *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[7][1] = result;
  HIBYTE(this->m_RoleXor[3].byMagicUseTime[1][0]) = 1;
  return result;
}

// 0x00449FE0
int CCBRoleState::UpdateSpringAnim(float fDelta)
{
  int v3; // eax
  int v4; // ecx
  double v5; // st7
  double v6; // st7
  int v7; // eax
  int v8; // ecx
  double v9; // st7
  double v10; // st7
  double v11; // st7
  unsigned int v12; // edi
  int result; // eax
  float v14; // [esp+0x4] [ebp-0x4]
  float v15; // [esp+0x4] [ebp-0x4]
  float fDeltaa; // [esp+0xC] [ebp+0x4]
  float fDeltab; // [esp+0xC] [ebp+0x4]

  v3 = *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[5][1];
  v4 = *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[6][3];
  LOBYTE(this->m_RoleXor[3].byMagicUseTime[1][1]) = 0;
  if ( v3 >= v4 )
  {
    if ( v3 > v4 )
    {
      v6 = *(float *)&this->m_RoleXor[3].bMagicMastered[3][5]
         - fDelta
         * *(float *)((char *)&this->m_RoleXor[3].byMagicUseTime[1][2] + 1)
         * (double)*(int *)((char *)&this->m_RoleXor[3].byMagicUseTime[0][0] + 1);
      *(float *)&this->m_RoleXor[3].bMagicMastered[3][5] = v6;
      v15 = (float)v4;
      if ( v6 <= v15 )
        *(float *)&this->m_RoleXor[3].bMagicMastered[3][5] = v15;
    }
  }
  else
  {
    v5 = fDelta
       * *(float *)((char *)&this->m_RoleXor[3].byMagicUseTime[1][2] + 1)
       * (double)*(int *)((char *)&this->m_RoleXor[3].byMagicUseTime[0][0] + 1)
       + *(float *)&this->m_RoleXor[3].bMagicMastered[3][5];
    *(float *)&this->m_RoleXor[3].bMagicMastered[3][5] = v5;
    v14 = (float)v4;
    if ( v5 >= v14 )
      *(float *)&this->m_RoleXor[3].bMagicMastered[3][5] = v14;
  }
  v7 = *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[5][5];
  v8 = *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[7][1];
  if ( v7 >= v8 )
  {
    if ( v7 > v8 )
    {
      v10 = *(float *)&this->m_RoleXor[3].bMagicMastered[4][3]
          - fDelta
          * *(float *)((char *)&this->m_RoleXor[3].byMagicUseTime[1][2] + 1)
          * (double)*(int *)((char *)&this->m_RoleXor[3].byMagicUseTime[0][0] + 1);
      *(float *)&this->m_RoleXor[3].bMagicMastered[4][3] = v10;
      fDeltab = (float)v8;
      if ( v10 <= fDeltab )
        *(float *)&this->m_RoleXor[3].bMagicMastered[4][3] = fDeltab;
    }
  }
  else
  {
    v9 = fDelta
       * *(float *)((char *)&this->m_RoleXor[3].byMagicUseTime[1][2] + 1)
       * (double)*(int *)((char *)&this->m_RoleXor[3].byMagicUseTime[0][0] + 1)
       + *(float *)&this->m_RoleXor[3].bMagicMastered[4][3];
    *(float *)&this->m_RoleXor[3].bMagicMastered[4][3] = v9;
    fDeltaa = (float)v8;
    if ( v9 >= fDeltaa )
      *(float *)&this->m_RoleXor[3].bMagicMastered[4][3] = fDeltaa;
  }
  v11 = *(float *)&this->m_RoleXor[3].bMagicMastered[4][3];
  v12 = (__int64)*(float *)&this->m_RoleXor[3].bMagicMastered[3][5];
  *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[5][1] = v12;
  *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[5][5] = (__int64)v11;
  *(unsigned int *)((char *)&this->m_RoleXor[3].dwMagicID[2][3] + 3) = (__int64)v11;
  *(unsigned int *)((char *)&this->m_RoleXor[3].dwMagicID[2][2] + 3) = v12;
  *(unsigned int *)((char *)&this->m_RoleXor[3].dwMagicID[2][4] + 3) = v12 + 64;
  *(unsigned int *)((char *)&this->m_RoleXor[3].dwMagicID[2][5] + 3) = (__int64)v11 + 64;
  sub_445FA0((char *)&this->m_RoleXor[3].dwMagicID[3][0] + 3);
  result = *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[6][3];
  if ( *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[5][1] == result )
  {
    result = *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[7][1];
    if ( *(_DWORD *)&this->m_RoleXor[3].bMagicMastered[5][5] == result )
      LOBYTE(this->m_RoleXor[3].byMagicUseTime[1][1]) = 1;
  }
  return result;
}

// 0x0044A2E0
void CCBRoleState::UpdateFadeAlpha()
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // edi
  NPC *v7; // ebp
  gbColorQuad v8; // [esp+0x10] [ebp-0x4] BYREF

  if ( HIBYTE(this->m_RoleXor[9].dwSkillID[1]) )
  {
    v2 = *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[3] + 3);
    if ( v2 > 0 )
    {
      if ( LOBYTE(this->m_RoleXor[9].dwSkillID[2]) )
      {
        v3 = *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) + 10;
        *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) = v3;
        if ( v3 >= 255 )
        {
          v4 = v2 - 1;
          LOBYTE(this->m_RoleXor[9].dwSkillID[2]) = 0;
          *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) = 255;
          *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[3] + 3) = v4;
          if ( v4 <= 0 )
            *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) = 255;
        }
      }
      else
      {
        v5 = *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) - 10;
        *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) = v5;
        if ( v5 <= 0 )
        {
          LOBYTE(this->m_RoleXor[9].dwSkillID[2]) = 1;
          *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) = 0;
        }
      }
      v6 = 0;
      v7 = (NPC *)((char *)&this->m_Role[0].byMagicUseTime[0][5] + 1);
      do
      {
        if ( *((_BYTE *)&g_pSceneTransitionEnd + v6) )
        {
          if ( *(int *)((char *)&this->m_RoleXor[9].dwSkillID[3] + 3) <= 0 )
            *((_BYTE *)&g_pSceneTransitionEnd + v6) = 0;
          ((NPC *)v7)->NPC::UpdateAnim();
        }
        ++v6;
        v7 = (NPC *)((char *)v7 + 476);
      }
      while ( v6 < 38 );
    }
  }
}

// 0x0044A3D0
int CCBRoleState::InitFadeAndSpring()
{
  unsigned int v2; // ebp
  char *v3; // esi
  int i; // ebx
  int v5; // ecx
  double v6; // st7
  int v7; // ecx
  int v8; // edx
  double v9; // st7

  *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[6][1] + 1) = 1077936128;
  ((CCBFiveNimbusWindow *)((char *)&this->m_Role[0].dwMagicID[1][2] + 1))->UpdateDisplay();
  HIBYTE(this->m_RoleXor[9].dwSkillID[1]) = 0;
  *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) = 255;
  LOBYTE(this->m_RoleXor[9].dwSkillID[2]) = 1;
  *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[3] + 3) = 2;
  v2 = 0;
  v3 = (char *)&this->m_Role[0].dwMagicID[8][0] + 1;
  for ( i = 68; i < 220; i += 4 )
  {
    *((_DWORD *)v3 - 1) = *((_DWORD *)v3 + 3);
    *(_DWORD *)v3 = *((_DWORD *)v3 + 4);
    *((_DWORD *)v3 + 1) = *((_DWORD *)v3 + 5);
    v5 = *((_DWORD *)v3 + 6);
    *((_DWORD *)v3 + 9) = *((_DWORD *)v3 + 13);
    *((_DWORD *)v3 + 2) = v5;
    v6 = (double)*(int *)v3;
    v7 = *((_DWORD *)v3 + 15);
    v8 = *((_DWORD *)v3 + 16);
    *((_DWORD *)v3 + 10) = *((_DWORD *)v3 + 14);
    *((_DWORD *)v3 + 11) = v7;
    *((float *)v3 + 8) = v6;
    v9 = (double)*((int *)v3 - 1);
    *((_DWORD *)v3 + 12) = v8;
    *((float *)v3 + 7) = v9;
    sub_4499A0(this, v2, *(int *)((char *)&g_gamefrm + i));
    if ( *((_BYTE *)&g_pSceneTransitionEnd + v2) )
      HIBYTE(this->m_RoleXor[9].dwSkillID[1]) = 1;
    ++v2;
    v3 += 476;
  }
  if ( HIBYTE(this->m_RoleXor[9].dwSkillID[1]) )
    *(unsigned int *)((char *)&this->m_RoleXor[9].dwSkillID[2] + 3) = 0;
  *(_DWORD *)((char *)&this->m_RoleXor[3].byMagicUseTime[0][0] + 1) = 1;
  *(_DWORD *)((char *)&this->m_RoleXor[3].byMagicUseTime[0][4] + 1) = 1077936128;
  *(_DWORD *)((char *)&this->m_RoleXor[3].byMagicUseTime[0][2] + 1) = 1077936128;
  HIBYTE(this->m_RoleXor[3].byMagicUseTime[1][0]) = 0;
  LOBYTE(this->m_RoleXor[3].byMagicUseTime[1][1]) = 1;
  ((CCBUIPanel *)this)->FocusCurrentRole();
  ((CCBUIPanel *)this)->UpdateSlotPositions(0);
  BYTE1(this->m_Role[0].dwMagicID[7][3]) = 0;
  return ((CCBUIPanel *)this)->SetAllSlotsVisible(1u);
}

// 0x00456AB0
int CCBRoleState::ctor()
{
  sub_4422E0((char *)&this->m_Role[0].dwMagicID[1][2] + 1);
  UIScene::GetSys();
  sub_4422E0((char *)&this->m_RoleXor[6].dwMagicID[2][4] + 3);
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[1][1] = 0;
  this->m_fLastDialogTime = 0.0;
  this->_embed_UIFrameWnd_168.m_pbktex = 0;
  *(_DWORD *)&this->m_bCombatDialog = 800;
  this->m_pCBSystem = (CCBSystem *)600;
  return (int)this->m_sCombatDialog;
}

// 0x00456B80
void CCBRoleState::ctor_6B80()
{
  ((UIFrameWnd *)((char *)&this->m_RoleXor[6].dwMagicID[2][4] + 3))->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)((char *)&this->m_RoleXor[5].byMagicUseTime[4][2] + 1))->Destroy2();
  ((UIFrameWnd *)((char *)&this->m_Role[0].dwMagicID[1][2] + 1))->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00456C20
void CCBRoleState::_CCBRoleState()
{
  gbTexture **p_m_pbktex; // ebx
  int v3; // edx
  int v4; // ebp
  CCBUIPanel *v5; // edi
  int i; // ebx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  gbColorQuad v11; // [esp+0x38] [ebp-0x24] BYREF
  int v12; // [esp+0x3C] [ebp-0x20] BYREF
  int v13; // [esp+0x40] [ebp-0x1C]
  int v14; // [esp+0x44] [ebp-0x18]
  int v15; // [esp+0x48] [ebp-0x14]
  _DWORD v16[4]; // [esp+0x4C] [ebp-0x10] BYREF
  int v17; // [esp+0x60] [ebp+0x4]
  int v18; // [esp+0x60] [ebp+0x4]

  p_m_pbktex = &this->_embed_UIFrameWnd_168.m_pbktex;
  ((UIListBox *)this)->SetSelTexture(0, (int)this->_embed_UIFrameWnd_168.m_pbktex, LODWORD(this->m_fLastDialogTime), *(_DWORD *)&this->m_bCombatDialog, (int)this->m_pCBSystem, 0);
  v3 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[1][2] + 1);
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[1][1] = v17;
  (*(void ( **)(char *, _DWORD, gbTexture **, CCBRoleState *))(v3 + 16))(
    (char *)&this->m_Role[0].dwMagicID[1][2] + 1,
    0,
    p_m_pbktex,
    this);
  ((UIStatic *)((char *)&this->m_Role[0].dwMagicID[1][2] + 1))->CreateFromTemplate();
  v4 = 0;
  v13 = 60;
  v12 = 44;
  v14 = 130;
  v15 = 123;
  v18 = 1;
  v5 = (CCBUIPanel *)((char *)&this->m_Role[0].dwMagicID[7][4] + 1);
  for ( i = 0; i < 52; ++i )
  {
    v7 = sprintf((char *const)&this->m_nMaxRound, byte_5967B0, (&off_5B0E2C)[i]);
    LOBYTE(v7) = byte_5B1A26;
// [VFTABLE] ((void ( *)(CCBUIPanel *, int, int *, CCBRoleState *, int *, int))v5->__vftable[1].Render)(
// [VFTABLE]   v5,
// [VFTABLE]   dword_56B294[i],
// [VFTABLE]   &v12,
// [VFTABLE]   this,
// [VFTABLE]   &this->m_nMaxRound,
// [VFTABLE]   v7);
    ((CCBUIPanel *)v5)->SetUserData();
    if ( ++v4 / 8 < v18 )
    {
      v12 = v14 + 3;
      v14 += 89;
    }
    else
    {
      v12 = 44;
      v14 = 130;
      v13 += 68;
      v15 = v13 + 63;
      ++v18;
    }
    v5 = (CCBUIPanel *)((char *)v5 + 376);
  }
  v8 = *(unsigned int *)((char *)&this->m_RoleXor[6].dwMagicID[2][4] + 3);
  v16[1] = 476;
  v16[0] = 408;
  v16[2] = 744;
  v16[3] = 526;
  (*(void ( **)(char *, _DWORD, _DWORD *, CCBRoleState *))(v8 + 16))(
    (char *)&this->m_RoleXor[6].dwMagicID[2][4] + 3,
    0,
    v16,
    this);
  ((UIScene *)((char *)&this->m_RoleXor[6].dwMagicID[2][4] + 3))->SetShow(0);
  ((UICaption *)((char *)&this->m_RoleXor[6].dwMagicID[2][4] + 3))->SetEnable((int)g_szSceneUIText, 0);
  LOBYTE(v9) = byte_5B1A26;
  v10 = *(_DWORD *)((char *)&this->m_RoleXor[5].byMagicUseTime[4][2] + 1);
  v13 = 537;
  v12 = 745;
  v14 = 801;
  v15 = 599;
  (*(void ( **)(char *, int, int *, CCBRoleState *, char *, _DWORD, int))(v10 + 28))(
    (char *)&this->m_RoleXor[5].byMagicUseTime[4][2] + 1,
    177,
    &v12,
    this,
    off_5B1604[0],
    0,
    v9);
}

// 0x00457020
BOOL CCBRoleState::PlayVideoIfReady(int nVal, int nVal2)
{
  unsigned __int8 v5; // [esp+0x0] [ebp-0x4]

  if ( this->m_RoleXor[6].bMagicMastered[0][3] && ((CScreenMode *)&g_ScreenMode)->PlayVideo(1) )
  {
    ((CScreenMode *)this)->PauseAllStreams((void ( ***)(_DWORD, _DWORD))1, v5);
    this->m_RoleXor[6].bMagicMastered[0][3] = 0;
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x00457070
int CCBRoleState::ctor(int nVal, int nVal2, int nVal3)
{
  int result; // eax
  int v6; // eax
  int *v7; // ecx
  CScreenMode *Instance; // eax
  int Width; // eax
  int v10; // ecx
  int *v11; // eax
  int *v12; // eax
  const void *v13; // [esp-0x8] [ebp-0x10]
  int v14; // [esp-0x4] [ebp-0xC]
  unsigned __int8 v15; // [esp+0x0] [ebp-0x8]

  switch ( nVal )
  {
    case 1000:
      if ( !nVal2 )
        goto LABEL_20;
      ((Actor *)this)->ApplyStateArray();
      this->m_RoleXor[6].bMagicMastered[0][3] = 0;
      result = 1;
      break;
    case 1001:
      v6 = 0;
      v7 = dword_56B294;
      do
      {
        if ( nVal2 == *v7 )
        {
          sprintf((char *const)&this->m_nMaxRound, "Movie\\%s.bik", (const char *)(30 * v6 + 5967612));
          ((CScreenMode *)&g_ScreenMode)->CreateDevice((int)&this->m_nMaxRound, (int)hWnd, 0, 0);
          v14 = (600 - ((CScreenMode *)&g_ScreenMode)->GetHeight()) / 2;
          Width = ((CScreenMode *)&g_ScreenMode)->GetWidth();
          ((CScreenMode *)&g_ScreenMode)->SetViewport((800 - Width) / 2, v14);
          ((CScreenMode *)this)->PauseAllStreams(0, v15);
          this->m_RoleXor[6].bMagicMastered[0][3] = 1;
          return 1;
        }
        ++v7;
        ++v6;
      }
      while ( (int)v7 < (int)&stru_56B364 );
      if ( nVal2 != 177 )
        goto LABEL_20;
      v13 = off_5B0DA4;
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v13, 1);
      ((ChoseCompose *)*(ChoseCompose **)&this->m_RoleXor[6].bMagicMastered[1][1])->Init(0);
      result = 1;
      break;
    case 1002:
      v10 = 0;
      v11 = dword_56B294;
      do
      {
        if ( nVal2 == *v11 )
        {
          ((UICaption *)((char *)&this->m_RoleXor[6].dwMagicID[2][4] + 3))->SetEnable((int)&dword_DD553C[64 * v10], 0);
          goto LABEL_20;
        }
        ++v11;
        ++v10;
      }
      while ( (int)v11 < (int)&stru_56B364 );
      result = 1;
      break;
    case 1003:
      v12 = dword_56B294;
      while ( nVal2 != *v12 )
      {
        if ( (int)++v12 >= (int)&stru_56B364 )
          return 1;
      }
      ((UICaption *)((char *)&this->m_RoleXor[6].dwMagicID[2][4] + 3))->SetEnable((int)g_szSceneUIText, 0);
LABEL_20:
      result = 1;
      break;
    default:
      result = ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
      break;
  }
  return result;
}

// 0x0046D770
int CCBRoleState::LayoutSlotPanelA(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  int v4; // edi
  int result; // eax

  v3 = *(void ( ***)(char *, _DWORD))((char *)&this->m_RoleXor[4].fGPIncPerRound + 3);
  HIBYTE(this->m_RoleXor[5].dwMagicID[7][0]) = pData;
  (*v3)((char *)&this->m_RoleXor[4].fGPIncPerRound + 3, pData);
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3) = 0;
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = 0;
  do
  {
    v4 = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3);
    if ( *((_BYTE *)&this->m_RoleXor[5].dwMagicID[7][0] + v4 + 3) )
    {
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4 * v4 + 1] + 3) = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3)
                                                                                      * *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3)
                                                                                      + (int)(*(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3) - *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3))
                                                                                      / 2;
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][2] + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 2]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][4] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)]
                                                     + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 3]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
                                                                                              + 1]
                                                     + 3);
      sub_445FA0(
        (char *)&this->m_RoleXor[4].fGPIncPerRound
      + 152 * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
      + 3);
      ++*(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3);
    }
    result = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) + 1;
    *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046D890
int CCBRoleState::LayoutSlotPanelB(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  int v4; // edi
  int result; // eax

  v3 = *(void ( ***)(char *, _DWORD))((char *)&this->m_RoleXor[4].dwMagicID[2][4] + 3);
  LOBYTE(this->m_RoleXor[5].dwMagicID[7][1]) = pData;
  (*v3)((char *)&this->m_RoleXor[4].dwMagicID[2][4] + 3, pData);
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3) = 0;
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = 0;
  do
  {
    v4 = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3);
    if ( *((_BYTE *)&this->m_RoleXor[5].dwMagicID[7][0] + v4 + 3) )
    {
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4 * v4 + 1] + 3) = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3)
                                                                                      * *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3)
                                                                                      + (int)(*(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3) - *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3))
                                                                                      / 2;
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][2] + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 2]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][4] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)]
                                                     + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 3]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
                                                                                              + 1]
                                                     + 3);
      sub_445FA0(
        (char *)&this->m_RoleXor[4].fGPIncPerRound
      + 152 * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
      + 3);
      ++*(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3);
    }
    result = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) + 1;
    *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046D9B0
int CCBRoleState::LayoutSlotPanelC(unsigned __int8 pData)
{
  void ( **v3)(_BYTE *, _DWORD); // edx
  int v4; // edi
  int result; // eax

  v3 = *(void ( ***)(_BYTE *, _DWORD))&this->m_RoleXor[4].bMagicMastered[0][3];
  BYTE1(this->m_RoleXor[5].dwMagicID[7][1]) = pData;
  (*v3)(&this->m_RoleXor[4].bMagicMastered[0][3], pData);
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3) = 0;
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = 0;
  do
  {
    v4 = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3);
    if ( *((_BYTE *)&this->m_RoleXor[5].dwMagicID[7][0] + v4 + 3) )
    {
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4 * v4 + 1] + 3) = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3)
                                                                                      * *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3)
                                                                                      + (int)(*(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3) - *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3))
                                                                                      / 2;
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][2] + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 2]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][4] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)]
                                                     + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 3]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
                                                                                              + 1]
                                                     + 3);
      sub_445FA0(
        (char *)&this->m_RoleXor[4].fGPIncPerRound
      + 152 * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
      + 3);
      ++*(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3);
    }
    result = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) + 1;
    *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046DAD0
int CCBRoleState::LayoutSlotPanelD(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  int v4; // edi
  int result; // eax

  v3 = *(void ( ***)(char *, _DWORD))((char *)&this->m_RoleXor[4].byMagicUseTime[8][2] + 1);
  BYTE2(this->m_RoleXor[5].dwMagicID[7][1]) = pData;
  (*v3)((char *)&this->m_RoleXor[4].byMagicUseTime[8][2] + 1, pData);
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3) = 0;
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = 0;
  do
  {
    v4 = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3);
    if ( *((_BYTE *)&this->m_RoleXor[5].dwMagicID[7][0] + v4 + 3) )
    {
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4 * v4 + 1] + 3) = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3)
                                                                                      * *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3)
                                                                                      + (int)(*(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3) - *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3))
                                                                                      / 2;
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][2] + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 2]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][4] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)]
                                                     + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 3]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
                                                                                              + 1]
                                                     + 3);
      sub_445FA0(
        (char *)&this->m_RoleXor[4].fGPIncPerRound
      + 152 * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
      + 3);
      ++*(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3);
    }
    result = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) + 1;
    *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046DBF0
int CCBRoleState::LayoutSlotPanelE(unsigned __int8 pData)
{
  void ( **v3)(char *, _DWORD); // edx
  int v4; // edi
  int result; // eax

  v3 = *(void ( ***)(char *, _DWORD))((char *)&this->m_RoleXor[5].fMPIncPerRound + 3);
  HIBYTE(this->m_RoleXor[5].dwMagicID[7][1]) = pData;
  (*v3)((char *)&this->m_RoleXor[5].fMPIncPerRound + 3, pData);
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3) = 0;
  *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = 0;
  do
  {
    v4 = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3);
    if ( *((_BYTE *)&this->m_RoleXor[5].dwMagicID[7][0] + v4 + 3) )
    {
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4 * v4 + 1] + 3) = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3)
                                                                                      * *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3)
                                                                                      + (int)(*(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][3] + 3) - *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3))
                                                                                      / 2;
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][2] + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 2]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][4] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)]
                                                     + 3);
      *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                   * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5]
                                                                                         + 3)
                                                                   + 3]
                          + 3) = *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[6][5] + 3)
                               + *(unsigned int *)((char *)&this->m_RoleXor[5].dwMagicID[3][4
                                                                                              * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
                                                                                              + 1]
                                                     + 3);
      sub_445FA0(
        (char *)&this->m_RoleXor[4].fGPIncPerRound
      + 152 * *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3)
      + 3);
      ++*(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[8][0] + 3);
    }
    result = *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) + 1;
    *(unsigned int *)((char *)&this->m_RoleXor[2].dwMagicID[7][5] + 3) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0046F390
int CCBRoleState::NotifyStateChange(unsigned __int8 nState)
{
  (**(void ( ***)(char *, _DWORD))((char *)&this->m_RoleXor[9].dwMagicID[3][1] + 3))(
    (char *)&this->m_RoleXor[9].dwMagicID[3][1] + 3,
    nState);
  return (**(int ( ***)(char *, _DWORD))((char *)&this->m_RoleXor[3].byMagicUseTime[6][4] + 1))(
           (char *)&this->m_RoleXor[3].byMagicUseTime[6][4] + 1,
           nState);
}

// 0x004DC720
BOOL CCBRoleState::IsAlive()
{
  BOOL result; // eax
  int v2; // [esp+0x8] [ebp+0x4]

  result = v2 << 6;
  if ( *((_BYTE *)&this->m_Role[0].nFullMP + 64 * v2 + 1) )
  {
    memset(&this->m_bMustFail + 64 * v2, 0, 0x40u);
    result = this->m_nBossRound - 1;
    this->m_nBossRound = result;
    LOBYTE(result) = 1;
  }
  else
  {
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004DC760
char CCBRoleState::GetCombatDialogPos(int *p_DWORD, int *p_DWORD2, int *p_DWORD3)
{
  if ( !LOBYTE(this->_embed_UIFrameWnd_168.m_childs.m_needscriptdel) )
    return 0;
  *p_DWORD = (int)this->_embed_UIFrameWnd_168.m_childs.m_pData;
  *p_DWORD2 = this->_embed_UIFrameWnd_168.m_childs.capacity;
  *p_DWORD3 = this->_embed_UIFrameWnd_168.m_childs.m_nSize;
  LOBYTE(this->_embed_UIFrameWnd_168.m_childs.m_needscriptdel) = 0;
  this->_embed_UIFrameWnd_168.m_childs.m_pData = 0;
  this->_embed_UIFrameWnd_168.m_childs.capacity = 0;
  this->_embed_UIFrameWnd_168.m_childs.m_nSize = 0;
  return 1;
}

// 0x004DC7A0
void CCBRoleState::InitCombatDialog()
{
  int m_nMaxRound; // eax
  CScreenMode *Instance; // eax
  int v4; // ecx
  LONG bottom; // eax
  int p_DWORD; // [esp+0x10] [ebp-0xC] BYREF
  int p_DWORD3; // [esp+0x14] [ebp-0x8] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x4] BYREF

  m_nMaxRound = this->m_nMaxRound;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( !*((_BYTE *)&this->m_Role[0].nFullMP + 64 * m_nMaxRound + 2) )
  {
    ((CCBUI *)this)->UpdatePanel(1);
    *(_BYTE *)(*(_DWORD *)(this->_embed_UIFrameWnd_168.m_fontcolor.Color
                         + 4 * this->_embed_UIFrameWnd_168.m_rect.bottom
                         + 24)
             + 280) = 1;
    *((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) = 1;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa003", 1);
  }
  ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetRoleField(this->_embed_UIFrameWnd_168.m_rect.bottom, 15);
  sub_445E50(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 279) + 84));
  ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetRoleField(this->_embed_UIFrameWnd_168.m_rect.bottom, 16);
  sub_445E50(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 279) + 88));
  sub_445E50(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 279) + 104));

  sub_445E50(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 279) + 96));
  if ( !this->_embed_UIFrameWnd_168.m_rect.bottom
    && *(_DWORD *)&((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->byMagicUseTime[8][3] == 6
    && (((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(1)->bValid
     || ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(2)->bValid
     || ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(3)->bValid) )
  {
    v4 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 279) + 108);
  }
  else
  {
    v4 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 279) + 108);
  }
  sub_445E50(v4);
  if ( this->GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3) )
  {
    switch ( p_DWORD )
    {
      case 259:
        ((CCBUI *)this)->UpdatePanel(0);
        ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::DispatchCombatAction */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, 259);
        goto LABEL_36;
      case 260:
        ((CCBUI *)this)->UpdatePanel(0);
        ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::HandleItemMenu */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, 260);
        goto LABEL_36;
      case 261:
        if ( ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetRoleField(this->_embed_UIFrameWnd_168.m_rect.bottom, 15) )
        {
          goto LABEL_34;
        }
        ((CCBUI *)this)->UpdatePanel(0);
        ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::HandleMagicMenu */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, 261);
        goto LABEL_36;
      case 262:
        if ( ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetRoleField(this->_embed_UIFrameWnd_168.m_rect.bottom, 16) )
        {
          goto LABEL_34;
        }
        ((CCBUI *)this)->UpdatePanel(0);
        ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::HandleTargetMenu */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, 262);
        goto LABEL_36;
      case 264:
        if ( !this->CheckMP() )
          goto LABEL_34;
        ((CCBUI *)this)->UpdatePanel(0);
        this->_embed_UIFrameWnd_168.m_bcreateok = 264;
        this->_embed_UIFrameWnd_168.m_bvisible = 0;
        ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::EndRoundTasks */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, 264);
        goto LABEL_36;
      case 265:
        ((CCBUI *)this)->UpdatePanel(0);
        LOBYTE(this->m_pUtil) = 1;
        this->_embed_UIFrameWnd_168.m_bcreateok = 265;
        goto LABEL_21;
      case 266:
        ((CCBUI *)this)->UpdatePanel(0);
        this->_embed_UIFrameWnd_168.m_bcreateok = 266;
        this->_embed_UIFrameWnd_168.m_bvisible = 0;
        ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::StartLineupPhase */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, 266);
        goto LABEL_36;
      case 267:
        if ( ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetRoleField(this->_embed_UIFrameWnd_168.m_rect.bottom, 16) )
        {
          goto LABEL_34;
        }
        ((CCBUI *)this)->UpdatePanel(0);
        LOBYTE(this->m_pUtil) = 1;
        this->_embed_UIFrameWnd_168.m_bcreateok = 267;
LABEL_21:
        this->_embed_UIFrameWnd_168.m_benable = this->_embed_UIFrameWnd_168.m_rect.bottom;
        this->_embed_UIFrameWnd_168.m_bvisible = 0;
        this->_embed_UIFrameWnd_168.m_bfocus = -1;
        BYTE1(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
        LOBYTE(this->_embed_UIFrameWnd_168.m_pbktex) = 0;

        break;
      case 268:
        if ( this->_embed_UIFrameWnd_168.m_rect.bottom
          || *(_DWORD *)&((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->byMagicUseTime[8][3] != 6
          || !((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(1)->bValid
          && !((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(2)->bValid
          && !((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(3)->bValid )
        {
          goto LABEL_34;
        }
        ((CCBUI *)this)->UpdatePanel(0);
        this->_embed_UIFrameWnd_168.m_bvisible = 0;
        this->_embed_UIFrameWnd_168.m_bcreateok = 268;
        ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::InitSelectionUI */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, 268);

        break;
      case 269:
        ((CCBUI *)this)->UpdatePanel(0);
        bottom = this->_embed_UIFrameWnd_168.m_rect.bottom;
        LOBYTE(this->m_pUtil) = 1;
        this->_embed_UIFrameWnd_168.m_bcreateok = 269;
        this->_embed_UIFrameWnd_168.m_bvisible = 0;
        this->_embed_UIFrameWnd_168.m_benable = bottom;
        this->_embed_UIFrameWnd_168.m_bfocus = -1;
        BYTE1(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
        LOBYTE(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
        goto LABEL_36;
      default:
        goto LABEL_34;
    }
  }
  else
  {
LABEL_34:
    if ( BYTE1(this->_embed_UIFrameWnd_168.m_pfather) )
    {
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
      ((CCBUI *)this)->UpdatePanel(0);
LABEL_36:

    }
  }
}

// 0x004DCD00
int CCBRoleState::HandleItemMenu(int nState)
{
  int v3; // eax
  CScreenMode *Instance; // eax
  int *v5; // ecx
  int DialogSlot; // esi
  CCBRoleState *Color; // ecx
  const char *v8; // esi
  int p_DWORD3; // [esp+0x10] [ebp-0x138] BYREF
  int p_DWORD; // [esp+0x14] [ebp-0x134] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x130] BYREF
  _DWORD pOut[11]; // [esp+0x1C] [ebp-0x12C] BYREF
  char szName[256]; // [esp+0x48] [ebp-0x100] BYREF

  memset(pOut, 0, sizeof(pOut));
  v3 = this->m_nMaxRound << 6;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( !*((_BYTE *)&this->m_Role[0].nFullMP + v3 + 2) )
  {
    ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->PopulateItemList(this->_embed_UIFrameWnd_168.m_rect.bottom);
    ((UICaption *)*(UICaption **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 282) + 72))->SetEnable((int)g_szSceneUIText, 0);
    (***((void ( ****)(_DWORD, int))this->_embed_UIFrameWnd_168.m_id + 282))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 282),
      1);
    *((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) = 1;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa003", 1);
  }
  if ( this->GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3) && p_DWORD == 160 )
  {
    (***((void ( ****)(_DWORD, _DWORD))this->_embed_UIFrameWnd_168.m_id + 282))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 282),
      0);
    if ( p_DWORD2 == -1 )
    {
      v5 = (int *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5];
      ((CCBSystem *)this)->FindFreeThread(*v5, v5[1], v5[2], v5[3], 0 /* TODO: (int)CCBRoleState::HandleItemMenu */, 0, 0, 0, 0);
LABEL_15:

      return 0;
    }
    DialogSlot = ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetDialogSlot(this->_embed_UIFrameWnd_168.m_rect.bottom, p_DWORD2);
    if ( p_DWORD3 != 1 )
    {
      ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::DispatchCombatAction */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::HandleItemMenu */, 0, 0, 0, *(int *)((char *)&this->m_Role[0].nHP + 64 * this->m_nMaxRound + 1));
      goto LABEL_15;
    }
    memset(pOut, 0, sizeof(pOut));
    pOut[2] = this->_embed_UIFrameWnd_168.m_rect.bottom;
    Color = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
    LOBYTE(pOut[10]) = 1;
    pOut[0] = 260;
    pOut[1] = DialogSlot;
    pOut[3] = -1;
    if ( ((CCBRoleState *)Color)->GetRoleAI(pOut) )
    {
      v8 = (const char *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(DialogSlot) + 60);
      if ( strrchr(v8, 36) )
        strcpy(szName, strrchr(v8, 36) + 1);
      ((UICaption *)*(UICaption **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 282) + 72))->SetEnable((int)szName, 0);
    }
    (***((void ( ****)(_DWORD, int))this->_embed_UIFrameWnd_168.m_id + 282))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 282),
      1);
  }
  if ( BYTE1(this->_embed_UIFrameWnd_168.m_pfather) )
  {
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
    (***((void ( ****)(_DWORD, _DWORD))this->_embed_UIFrameWnd_168.m_id + 282))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 282),
      0);
    goto LABEL_15;
  }
  return 0;
}

// 0x004DCF80
int CCBRoleState::HandleMagicMenu(int nState)
{
  int v3; // eax
  CScreenMode *Instance; // eax
  int v5; // esi
  int v6; // eax
  int *v7; // ecx
  int v8; // edi
  int MagicSlotData; // esi
  int v10; // eax
  LONG bottom; // edx
  CCBRoleState *Color; // ecx
  const char *v13; // esi
  int p_DWORD; // [esp+0x10] [ebp-0x138] BYREF
  int p_DWORD3; // [esp+0x14] [ebp-0x134] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x130] BYREF
  _DWORD pOut[11]; // [esp+0x1C] [ebp-0x12C] BYREF
  char szName[256]; // [esp+0x48] [ebp-0x100] BYREF

  memset(pOut, 0, sizeof(pOut));
  v3 = this->m_nMaxRound << 6;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( !*((_BYTE *)&this->m_Role[0].nFullMP + v3 + 2) )
  {
    ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->PopulateMagicList(this->_embed_UIFrameWnd_168.m_rect.bottom);
    ((CCBControlWindow *)*((CCBControlWindow **)this->_embed_UIFrameWnd_168.m_id + 281))->HandleInput(*(UIButton **)(*(_DWORD *)this->m_sCombatDialog + 52 * this->_embed_UIFrameWnd_168.m_rect.bottom + 90308));
    ((UICaption *)*(UICaption **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 281) + 72))->SetEnable((int)g_szSceneUIText, 0);
    (***((void ( ****)(_DWORD, int))this->_embed_UIFrameWnd_168.m_id + 281))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 281),
      1);
    *((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) = 1;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa003", 1);
  }
  v5 = *(_DWORD *)this->m_sCombatDialog + 52 * this->_embed_UIFrameWnd_168.m_rect.bottom + 90264;
  ((CCBControlWindow *)*((CCBControlWindow **)this->_embed_UIFrameWnd_168.m_id + 281))->KeyPressed();
  *(_DWORD *)(v5 + 44) = v6;
  if ( this->GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3)
    && (unsigned int)p_DWORD >= 0x90
    && (unsigned int)p_DWORD <= 0x95 )
  {
    (***((void ( ****)(_DWORD, _DWORD))this->_embed_UIFrameWnd_168.m_id + 281))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 281),
      0);
    if ( p_DWORD2 == -1 )
    {
      v7 = (int *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5];
      ((CCBSystem *)this)->FindFreeThread(*v7, v7[1], v7[2], v7[3], 0 /* TODO: (int)CCBRoleState::HandleMagicMenu */, 0, 0, 0, 0);
LABEL_20:

      return 0;
    }
    v8 = p_DWORD - 144;
    MagicSlotData = ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetMagicSlotData(this->_embed_UIFrameWnd_168.m_rect.bottom, p_DWORD - 144, p_DWORD2);
    if ( p_DWORD3 != 1 )
    {
      ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::DispatchCombatAction */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::HandleMagicMenu */, 0, 0, 0, *(int *)((char *)&this->m_Role[0].nHP + 64 * this->m_nMaxRound + 1));
      goto LABEL_20;
    }
    ((CCBControlWindow *)*((CCBControlWindow **)this->_embed_UIFrameWnd_168.m_id + 281))->KeyPressed();
    if ( v10 == v8 )
    {
      bottom = this->_embed_UIFrameWnd_168.m_rect.bottom;
      memset(pOut, 0, sizeof(pOut));
      Color = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
      LOBYTE(pOut[10]) = 1;
      pOut[0] = 261;
      pOut[1] = MagicSlotData;
      pOut[3] = -1;
      pOut[2] = bottom;
      if ( ((CCBRoleState *)Color)->GetRoleAI(pOut) )
      {
        v13 = (const char *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(MagicSlotData) + 60);
        memset(szName, 0, sizeof(szName));
        if ( strrchr(v13, 36) )
          strcpy(szName, strrchr(v13, 36) + 1);
        ((UICaption *)*(UICaption **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 281) + 72))->SetEnable((int)szName, 0);
      }
    }
    (***((void ( ****)(_DWORD, int))this->_embed_UIFrameWnd_168.m_id + 281))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 281),
      1);
  }
  if ( ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetRoleField(this->_embed_UIFrameWnd_168.m_rect.bottom, 15) )
  {
    (***((void ( ****)(_DWORD, _DWORD))this->_embed_UIFrameWnd_168.m_id + 281))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 281),
      0);
    ((CCBSystem *)this)->FindFreeThread(*(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5], *(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 9], *(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 13], *((_DWORD *)&this->m_Role[0].bValid + 16 * this->m_nMaxRound), 0 /* TODO: (int)CCBRoleState::HandleMagicMenu */, 0, 0, 0, 0);
    goto LABEL_20;
  }
  if ( BYTE1(this->_embed_UIFrameWnd_168.m_pfather) )
  {
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
    (***((void ( ****)(_DWORD, _DWORD))this->_embed_UIFrameWnd_168.m_id + 281))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 281),
      0);
    goto LABEL_20;
  }
  return 0;
}

// 0x004DD300
int CCBRoleState::HandleTargetMenu(int nState)
{
  int v3; // eax
  CScreenMode *Instance; // eax
  unsigned int v5; // eax
  int *v6; // ecx
  int v7; // esi
  CCBRoleState *Color; // ecx
  const char *v9; // esi
  int *v10; // ecx
  int p_DWORD; // [esp+0x10] [ebp-0x144] BYREF
  int p_DWORD3; // [esp+0x14] [ebp-0x140] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x13C] BYREF
  _DWORD v15[11]; // [esp+0x1C] [ebp-0x138] BYREF
  _BYTE pOut[12]; // [esp+0x48] [ebp-0x10C] BYREF
  char szName[256]; // [esp+0x54] [ebp-0x100] BYREF

  memset(v15, 0, sizeof(v15));
  v3 = this->m_nMaxRound << 6;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( !*((_BYTE *)&this->m_Role[0].nFullMP + v3 + 2) )
  {
    ((UICaption *)*(UICaption **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280) + 76))->SetEnable((int)g_szSceneUIText, 0);
    (***((void ( ****)(_DWORD, int))this->_embed_UIFrameWnd_168.m_id + 280))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280),
      1);
    ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->PopulateTargetList(this->_embed_UIFrameWnd_168.m_rect.bottom, *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280) + 104));
    *((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) = 1;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa003", 1);
  }
  if ( this->GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3) )
  {
    v5 = p_DWORD;
    if ( (unsigned int)p_DWORD >= 0x80 && (unsigned int)p_DWORD <= 0x90 )
    {
      (***((void ( ****)(_DWORD, _DWORD))this->_embed_UIFrameWnd_168.m_id + 280))(
        *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280),
        0);
      if ( p_DWORD2 == -1 )
      {
        v6 = (int *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5];
        ((CCBSystem *)this)->FindFreeThread(*v6, v6[1], v6[2], v6[3], 0 /* TODO: (int)CCBRoleState::HandleTargetMenu */, 0, 0, 0, 0);
LABEL_22:

        return 0;
      }
      if ( p_DWORD3 != 1 )
      {
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, p_DWORD2);
        ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::DispatchCombatAction */, 0, 0, 0, 0 /* TODO: (int)CCBRoleState::HandleTargetMenu */, 0, 0, 0, *(int *)((char *)&this->m_Role[0].nHP + 64 * this->m_nMaxRound + 1));
        goto LABEL_22;
      }
      v7 = *(_DWORD *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, p_DWORD2);
      memset(v15, 0, sizeof(v15));
      v15[2] = this->_embed_UIFrameWnd_168.m_rect.bottom;
      Color = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
      LOBYTE(v15[10]) = 1;
      v15[0] = 262;
      v15[1] = v7;
      v15[3] = -1;
      if ( ((CCBRoleState *)Color)->GetRoleAI(v15) )
      {
        v9 = (const char *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v7) + 96);
        if ( strrchr(v9, 36) )
          strcpy(szName, strrchr(v9, 36) + 1);
        ((UICaption *)*(UICaption **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280) + 76))->SetEnable((int)szName, 0);
      }
      (***((void ( ****)(_DWORD, int))this->_embed_UIFrameWnd_168.m_id + 280))(
        *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280),
        1);
      v5 = p_DWORD;
    }
    if ( v5 >= 0xB5 && v5 <= 0xB7 )
      ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->PopulateTargetList(this->_embed_UIFrameWnd_168.m_rect.bottom, *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280) + 104));
  }
  if ( ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetRoleField(this->_embed_UIFrameWnd_168.m_rect.bottom, 16) )
  {
    (***((void ( ****)(_DWORD, _DWORD))this->_embed_UIFrameWnd_168.m_id + 280))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280),
      0);
    v10 = (int *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5];
    ((CCBSystem *)this)->FindFreeThread(*v10, v10[1], v10[2], v10[3], 0 /* TODO: (int)CCBRoleState::HandleTargetMenu */, 0, 0, 0, 0);
    goto LABEL_22;
  }
  if ( BYTE1(this->_embed_UIFrameWnd_168.m_pfather) )
  {
    (***((void ( ****)(_DWORD, _DWORD))this->_embed_UIFrameWnd_168.m_id + 280))(
      *((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 280),
      0);
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
    goto LABEL_22;
  }
  return 0;
}

// 0x004DD650
int CCBRoleState::StartLineupPhase(int nVal)
{
  int m_nMaxRound; // eax
  CScreenMode *Instance; // eax
  int *v5; // ecx
  CScreenMode *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  CScreenMode *v13; // eax
  int v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  CScreenMode *v21; // eax
  int v22; // eax
  CScreenMode *v23; // eax
  int v24; // eax
  CScreenMode *v25; // eax
  int v26; // eax
  CScreenMode *v27; // eax
  int v28; // eax
  CScreenMode *v29; // eax
  CScreenMode *v30; // eax
  bool v31; // bl
  char v32; // bl
  _DWORD *v33; // eax
  char v34; // cl
  int *v35; // edx
  int v36; // ecx
  int v37; // eax
  LONG bottom; // eax
  char v39; // [esp+0xF] [ebp-0xD]
  char v40; // [esp+0xF] [ebp-0xD]
  char v41; // [esp+0xF] [ebp-0xD]
  char v42; // [esp+0xF] [ebp-0xD]
  int p_DWORD2; // [esp+0x10] [ebp-0xC] BYREF
  int p_DWORD; // [esp+0x14] [ebp-0x8] BYREF
  int p_DWORD3; // [esp+0x18] [ebp-0x4] BYREF

  p_DWORD = 0;
  p_DWORD2 = 0;
  m_nMaxRound = this->m_nMaxRound;
  p_DWORD3 = 0;
  if ( !*((_BYTE *)&this->m_Role[0].nFullMP + 64 * m_nMaxRound + 2) )
  {
    ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->UpdateCommandButtons(this->_embed_UIFrameWnd_168.m_rect.bottom);
    ((CCBUI *)this->_embed_UIFrameWnd_168.m_id)->CreateLineupWindow(this->_embed_UIFrameWnd_168.m_rect.bottom, 1);
    *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 8) = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id
                                                                                + 283)
                                                                              + 116)
                                                                  + 68);
    *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 7) = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id
                                                                                + 283)
                                                                              + 112)
                                                                  + 68);
    *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 6) = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id
                                                                                + 283)
                                                                              + 108)
                                                                  + 68);
    *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 5) = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id
                                                                                + 283)
                                                                              + 104)
                                                                  + 68);
    *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 4) = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id
                                                                                + 283)
                                                                              + 100)
                                                                  + 68);
    *((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) = 1;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa003", 1);
  }
  if ( this->GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3)
    && (unsigned int)p_DWORD >= 0xD6
    && (unsigned int)p_DWORD <= 0xDC )
  {
    if ( p_DWORD2 == -1 )
    {
      ((CCBUI *)this->_embed_UIFrameWnd_168.m_id)->CreateLineupWindow(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
      v5 = (int *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5];
      ((CCBSystem *)this)->FindFreeThread(*v5, v5[1], v5[2], v5[3], 0 /* TODO: (int)CCBRoleState::StartLineupPhase */, 0, 0, 0, 0);

      return 0;
    }
    switch ( p_DWORD )
    {
      case 214:
        if ( p_DWORD2 == 1 )
        {
          if ( *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 116) + 68) )
          {
            v15 = CScreenMode::GetInstance();
            ((CScreenMode *)v15)->AudioSetPosition("wa001", 1);
          }
          else
          {
            v13 = CScreenMode::GetInstance();
            ((CScreenMode *)v13)->AudioSetPosition("wa004", 1);
            v14 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 96);
            *(_DWORD *)(v14 + 80) = 0;
            *(_BYTE *)(v14 + 68) = 0;
          }
        }
        if ( !p_DWORD2 )
        {
          v16 = CScreenMode::GetInstance();
          ((CScreenMode *)v16)->AudioSetPosition("wa001", 1);
          v17 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 108);
          *(_DWORD *)(v17 + 80) = 0;
          *(_BYTE *)(v17 + 68) = 0;
          v18 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 100);
          *(_DWORD *)(v18 + 80) = 0;
          *(_BYTE *)(v18 + 68) = 0;
          v19 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 104);
          *(_DWORD *)(v19 + 80) = 0;
          *(_BYTE *)(v19 + 68) = 0;
          v20 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 116);
          *(_DWORD *)(v20 + 80) = 0;
          *(_BYTE *)(v20 + 68) = 0;
        }
        break;
      case 215:
        if ( *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 116) + 68) )
          goto LABEL_29;
        v21 = CScreenMode::GetInstance();
        ((CScreenMode *)v21)->AudioSetPosition("wa004", 1);
        v22 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 100);
        *(_DWORD *)(v22 + 80) = 0;
        *(_BYTE *)(v22 + 68) = 0;
        break;
      case 216:
        if ( *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 116) + 68) )
          goto LABEL_29;
        v23 = CScreenMode::GetInstance();
        ((CScreenMode *)v23)->AudioSetPosition("wa004", 1);
        v24 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 104);
        *(_DWORD *)(v24 + 80) = 0;
        *(_BYTE *)(v24 + 68) = 0;
        break;
      case 217:
        if ( *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 116) + 68) )
          goto LABEL_29;
        v25 = CScreenMode::GetInstance();
        ((CScreenMode *)v25)->AudioSetPosition("wa004", 1);
        v26 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 108);
        *(_DWORD *)(v26 + 80) = 0;
        *(_BYTE *)(v26 + 68) = 0;
        break;
      case 218:
        if ( *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 116) + 68) )
        {
LABEL_29:
          v29 = CScreenMode::GetInstance();
          ((CScreenMode *)v29)->AudioSetPosition("wa001", 1);
        }
        else
        {
          v27 = CScreenMode::GetInstance();
          ((CScreenMode *)v27)->AudioSetPosition("wa004", 1);
          v28 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 112);
          if ( *(_BYTE *)(v28 + 68) )
          {
            *(_DWORD *)(v28 + 80) = 0;
            *(_BYTE *)(v28 + 68) = 0;
          }
          else
          {
            *(_DWORD *)(v28 + 80) = 1;
            *(_BYTE *)(v28 + 68) = 1;
          }
        }
        break;
      case 219:
        v7 = CScreenMode::GetInstance();
        ((CScreenMode *)v7)->AudioSetPosition("wa001", 1);
        if ( p_DWORD2 == 1 )
        {
          v8 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 96);
          *(_DWORD *)(v8 + 80) = 1;
          *(_BYTE *)(v8 + 68) = 1;
        }
        if ( !p_DWORD2 )
        {
          v9 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 108);
          *(_DWORD *)(v9 + 80) = 0;
          *(_BYTE *)(v9 + 68) = 0;
          v10 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 100);
          *(_DWORD *)(v10 + 80) = 0;
          *(_BYTE *)(v10 + 68) = 0;
          v11 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 104);
          *(_DWORD *)(v11 + 80) = 0;
          *(_BYTE *)(v11 + 68) = 0;
          v12 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 96);
          *(_DWORD *)(v12 + 80) = 0;
          *(_BYTE *)(v12 + 68) = 0;
        }
        break;
      default:
        break;
    }
    if ( p_DWORD == 220 )
    {
      v30 = CScreenMode::GetInstance();
      ((CScreenMode *)v30)->AudioSetPosition("wa001", 1);
      v39 = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 96) + 68);
      LOBYTE(((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(this->_embed_UIFrameWnd_168.m_rect.bottom)[1].dwMagicID[0][5]) = v39;
      v40 = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 104) + 68);
      BYTE2(((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(this->_embed_UIFrameWnd_168.m_rect.bottom)[1].dwMagicID[0][5]) = v40;
      v41 = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 108) + 68);
      BYTE1(((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(this->_embed_UIFrameWnd_168.m_rect.bottom)[1].dwMagicID[0][5]) = v41;
      v42 = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 100) + 68);
      HIBYTE(((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(this->_embed_UIFrameWnd_168.m_rect.bottom)[1].dwMagicID[0][5]) = v42;
      v31 = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 112) + 68) == 0;
      LOBYTE(((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(this->_embed_UIFrameWnd_168.m_rect.bottom)[1].dwMagicID[1][0]) = v31;
      v32 = *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283) + 116) + 68);
      BYTE1(((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(this->_embed_UIFrameWnd_168.m_rect.bottom)[1].dwMagicID[1][0]) = v32;
      ((CCBUI *)this->_embed_UIFrameWnd_168.m_id)->CreateLineupWindow(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
      v33 = (_DWORD *)*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 283);
      v34 = *(_BYTE *)(v33[29] + 68);
      if ( (!v34
         || *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 7) == *(_BYTE *)(v33[28] + 68)
         && *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 6) == *(_BYTE *)(v33[27] + 68)
         && *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 5) == *(_BYTE *)(v33[26] + 68)
         && *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 4) == *(_BYTE *)(v33[25] + 68))
        && *(&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 8) == v34 )
      {
        v35 = (int *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5];
        ((CCBSystem *)this)->FindFreeThread(*v35, v35[1], v35[2], v35[3], 0 /* TODO: (int)CCBRoleState::StartLineupPhase */, 0, 0, 0, 0);

        return 0;
      }
      v36 = this->m_nMaxRound;
      LOBYTE(this->m_pUtil) = 1;
      v36 <<= 6;
      this->_embed_UIFrameWnd_168.m_bcreateok = *(int *)((char *)&this->m_Role[0].nHP + v36 + 1);
      v37 = *(int *)((char *)&this->m_Role[0].nFullHP + v36 + 1);
      this->_embed_UIFrameWnd_168.m_bfocus = -1;
      this->_embed_UIFrameWnd_168.m_bvisible = v37;
      bottom = this->_embed_UIFrameWnd_168.m_rect.bottom;
      this->_embed_UIFrameWnd_168.m_benable = bottom;
      LOBYTE(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
      BYTE1(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(bottom, 0);
      goto LABEL_41;
    }
  }
  if ( BYTE1(this->_embed_UIFrameWnd_168.m_pfather) )
  {
    ((CCBUI *)this->_embed_UIFrameWnd_168.m_id)->CreateLineupWindow(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
LABEL_41:

  }
  return 0;
}

// 0x004DDC90
int CCBRoleState::EndRoundTasks(int B4)
{
  int v3; // edi
  int v4; // ebp
  int v5; // ebx
  CCBRoleState *Color; // ecx
  CCBStageRole *v7; // ecx
  int RoleIndex; // eax
  int v9; // edi
  int v10; // eax
  CScreenMode *Instance; // eax
  int v12; // ebp
  int v13; // ebx
  int i; // edi
  CCBRoleState *v15; // ecx
  int v16; // ecx
  int v17; // edi
  int v18; // ebx
  int v19; // ebp
  float *v20; // edi
  CCBRoleState *v21; // ecx
  int v22; // ebp
  CCBStage *v23; // ecx
  int v24; // edi
  int *v25; // ecx
  char *v26; // eax
  int v27; // edx
  LONG bottom; // eax
  CCBSystem *vftable; // ecx
  int v30; // ebp
  CCBStage *v31; // ecx
  int v32; // edi
  int *v33; // eax
  int v34; // edx
  int v35; // ebx
  unsigned int v36; // eax
  int *v37; // eax
  int v38; // edx
  int v39; // ebp
  _DWORD *m_id; // ecx
  int v41; // eax
  LONG x; // edi
  float m_fSpeed; // ecx
  LONG y; // edx
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  char v49; // al
  int v50; // eax
  CCBMagicWindow **v51; // ecx
  int v52; // ebp
  int v53; // eax
  int j; // edi
  CCBRoleState *v55; // ecx
  tagRoleState *inited; // eax
  CCBRoleState *v57; // ecx
  tagRoleState *v58; // ebx
  tagRoleState *v59; // eax
  int v60; // edi
  int v61; // ebp
  CCBStage *v62; // ecx
  int v63; // edi
  CCBStage *v64; // ecx
  int v65; // edi
  Combat *v67; // [esp-0x10] [ebp-C0h]
  int v68; // [esp+0x0] [ebp-B0h]
  int v69; // [esp+0x4] [ebp-ACh]
  int v70; // [esp+0x8] [ebp-A8h]
  int v71; // [esp+0x18] [ebp-0x98]
  int v72; // [esp+0x18] [ebp-0x98]
  int v73; // [esp+0x18] [ebp-0x98]
  int v74; // [esp+0x1C] [ebp-0x94]
  int v75; // [esp+0x1C] [ebp-0x94]
  int v76; // [esp+0x1C] [ebp-0x94]
  int v77; // [esp+0x20] [ebp-0x90]
  int v78; // [esp+0x20] [ebp-0x90]
  int v79; // [esp+0x20] [ebp-0x90]
  int nVal8; // [esp+0x24] [ebp-0x8C] BYREF
  int v81; // [esp+0x28] [ebp-0x88]
  int v82; // [esp+0x2C] [ebp-0x84]
  int v83; // [esp+0x30] [ebp-0x80]
  struct tagPOINT Point; // [esp+0x34] [ebp-0x7C]
  int p_DWORD2; // [esp+0x3C] [ebp-0x74] BYREF
  int p_DWORD; // [esp+0x40] [ebp-0x70] BYREF
  _DWORD pData[11]; // [esp+0x44] [ebp-0x6C] BYREF
  int p_DWORD3; // [esp+0x70] [ebp-0x40] BYREF
  _DWORD v89[11]; // [esp+0x74] [ebp-0x3C] BYREF
  _BYTE a2[16]; // [esp+A0h] [ebp-0x10] BYREF

  memset(v89, 0, sizeof(v89));
  if ( !*((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) )
  {
    v3 = 24;
    v4 = 0;
    v5 = 0;
    *(_BYTE *)(*(_DWORD *)(this->_embed_UIFrameWnd_168.m_fontcolor.Color
                         + 4 * this->_embed_UIFrameWnd_168.m_rect.bottom
                         + 24)
             + 280) = 0;
    do
    {
      Color = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
      if ( Color->m_Role[0].bMagicMastered[5][v5 + 4] )
      {
        *(float *)((char *)&g_RoleSystemCombat.m_partyActor.m_fNormX + v3) = *(float *)&((CCBRoleState *)Color)->InitUI(v4)->byMagicUseTime[8][3];
        v7 = *(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v3);
        if ( v7->m_bCatching && v7->m_bDelAllTask )
          return 0;
        if ( v7->m_bCatching == 1 )
          ((CCBStageRole *)v7)->GetCurrentTaskIndex();
        ((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v3))->DelAllTask(0x7FFFFFFF, 1);
      }
      v3 += 4;
      ++v4;
      v5 += 892;
    }
    while ( v3 < 44 );
    g_RoleSystemCombat.m_teamSlots[74] = 0;
    ((CCBUI *)this->_embed_UIFrameWnd_168.m_id)->CreateFiveNimbus(1);
    ((CCBCamControl *)*(CCBCamControl **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + 16))->ClearFinishedTask(6);
    RoleIndex = ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleIndex(3, 0, 1);
    v9 = RoleIndex;
    if ( RoleIndex != -1 )
    {
      LOBYTE(v10) = ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->EndTask(RoleIndex);
      g_RoleSystemCombat.m_teamSlots[74] = v10;
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v9, 0 /* TODO: (int)CCBStage::IsTaskValid */, 0, 0, 0, 0, -1082130432, 1056964608);
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRoleByIdx(v9);
    }
    *((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) = 1;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa003", 1);
  }
  if ( !(unsigned __int8)((CCBSystem *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->FindThreadByID(g_RoleSystemCombat.m_teamSlots[74]) )
    ((CCBStage *)*(CCBStage **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + 68))->EndTurnAndAdvance();
  v12 = 0;
  v13 = 0;
  for ( i = 96; i < 116; i += 4 )
  {
    v15 = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
    if ( v15->m_Role[0].bMagicMastered[5][v13 + 4] && ((CCBRoleState *)v15)->SetVisible(v12, v70) )
      v16 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 284) + i);
    else
      v16 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 284) + i);
    sub_445E50(v16);
    ++v12;
    v13 += 892;
  }
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( this->GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3)
    && (unsigned int)p_DWORD >= 0xF1
    && (unsigned int)p_DWORD <= 0xF5
    && p_DWORD2 == -1 )
  {
    *(&pTarget.m_vTargetPos + 140) = -1;
    ((CCBUI *)this->_embed_UIFrameWnd_168.m_id)->CreateFiveNimbus(0);
    ((CCBCamControl *)*(CCBCamControl **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + 16))->ClearFinishedTask(7);
    v17 = ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleIndex(3, 0, 1);
    if ( v17 != -1 )
    {
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v17, 0 /* TODO: (int)CCBStage::IsSubTaskValid */, 0, 0, 0, 0, -1082130432, 1056964608);
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRoleByIdx(v17);
    }
    v18 = 0;
    v19 = 0;
    v20 = &g_RoleSystemCombat.m_partyActor.m_fSpeed + 2;
    while ( 1 )
    {
      v21 = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
      if ( v21->m_Role[0].bMagicMastered[5][v19 + 4] )
      {
        if ( *(_DWORD *)v20 != *(_DWORD *)&((CCBRoleState *)v21)->InitUI(v18)->byMagicUseTime[8][3] )
          break;
      }
      ++v20;
      ++v18;
      v19 += 892;
      if ( (int)v20 >= (int)((float *)&g_RoleSystemCombat.m_partyActor.m_bDirFlag + 1) )
      {
        v22 = 24;
        v71 = 0;
        v74 = 0;
        v77 = 24;
        do
        {
          if ( *(_BYTE *)(this->_embed_UIFrameWnd_168.m_wndcolor.Color + v74 + 577) )
          {
            ((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v22))->GetCurrentTask(0x7FFFFFFF);
            ((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v22))->TryRelease();
            if ( !((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v22))->ForceEndTaskByPFN() )
            {
              memset(pData, 0, sizeof(pData));
              v23 = (CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color;
              LOBYTE(pData[10]) = 1;
              pData[2] = v71;
              pData[1] = 264;
              v24 = ((CCBStage *)v23)->GetRoleIndex(9, pData, 1);
              if ( v24 != -1 )
              {
                v82 = pData[3];
                v81 = pData[2];
                nVal8 = 0;
                ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v24, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, &nVal8, -1082130432, 0);
                ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v24, 0 /* TODO: (int)CCBStage::ProcShowItemName */, 0, 0, 0, &nVal8, -1082130432, 0);
                ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v24, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, &nVal8, -1082130432, 0);
                ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRoleByIdx(v24);
                v22 = v77;
              }
            }
          }
          v22 += 4;
          ++v71;
          v77 = v22;
          v74 += 892;
        }
        while ( v22 < 44 );
        v25 = (int *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5];
        ((CCBSystem *)this)->FindFreeThread(*v25, v25[1], v25[2], v25[3], 0 /* TODO: (int)CCBRoleState::EndRoundTasks */, 0, 0, 0, 0);
        goto LABEL_79;
      }
    }
    v26 = &this->m_sCombatDialog[64 * this->m_nMaxRound];
    this->_embed_UIFrameWnd_168.m_bfocus = 0;
    LOBYTE(this->m_pUtil) = 1;
    this->_embed_UIFrameWnd_168.m_bcreateok = *((_DWORD *)v26 + 38);
    v27 = *((_DWORD *)v26 + 39);
// [VFTABLE] vftable = (CCBSystem *)this->_embed_UIFrameWnd_168.__vftable;
    bottom = this->_embed_UIFrameWnd_168.m_rect.bottom;
    this->_embed_UIFrameWnd_168.m_bvisible = v27;
    this->_embed_UIFrameWnd_168.m_benable = bottom;
    this->_embed_UIFrameWnd_168.m_bfocus = -1;
    LOBYTE(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
    BYTE1(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
    ((CCBSystem *)vftable)->SetCmdParam(bottom, 0);
    v30 = 24;
    v72 = 0;
    v75 = 0;
    v78 = 24;
    do
    {
      if ( *(_BYTE *)(this->_embed_UIFrameWnd_168.m_wndcolor.Color + v75 + 577) )
      {
        ((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v30))->GetCurrentTask(0x7FFFFFFF);
        ((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v30))->TryRelease();
        if ( !((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v30))->ForceEndTaskByPFN() )
        {
          memset(pData, 0, sizeof(pData));
          v31 = (CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color;
          LOBYTE(pData[10]) = 1;
          pData[2] = v72;
          pData[1] = 264;
          v32 = ((CCBStage *)v31)->GetRoleIndex(9, pData, 1);
          if ( v32 != -1 )
          {
            nVal8 = 0;
            v82 = pData[3];
            v81 = pData[2];
            ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v32, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, &nVal8, -1082130432, 0);
            ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v32, 0 /* TODO: (int)CCBStage::ProcShowItemName */, 0, 0, 0, &nVal8, -1082130432, 0);
            ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v32, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, &nVal8, -1082130432, 0);
            ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRoleByIdx(v32);
            v30 = v78;
          }
        }
      }
      v30 += 4;
      ++v72;
      v78 = v30;
      v75 += 892;
    }
    while ( v30 < 44 );
    goto LABEL_79;
  }
  v33 = (int *)sub_445FE0(a2);
  v69 = v33[1];
  v68 = *v33;
  v34 = v33[3];
  v67 = *(Combat **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + 68);
  v82 = v33[2];
  v83 = v34;
  ((Combat *)v67)->LogMessage((char *)0x12C, 200, (char *)&pTarget.m_vTargetPos + 568, v68, v69);
  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( ((GRPinput *)&g_Input)->GetKeyState(0x100u) )
  {
    v35 = *(&pTarget.m_vTargetPos + 140);
    if ( *(&pTarget.m_vTargetPos + 140) != -1 )
    {
      v45 = *((_DWORD *)&g_RoleSystemCombat.m_partyActor.m_fSpeed + 1);
      m_fSpeed = g_RoleSystemCombat.m_partyActor.m_fSpeed;
      y = Point.y;
      x = Point.x;
LABEL_69:
      sub_445D20(
        *(_DWORD **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 284) + 4 * v35 + 96),
        x - LODWORD(m_fSpeed),
        y - v45);
      goto LABEL_70;
    }
    v36 = ((CCBParabolaWindow *)*((CCBParabolaWindow **)this->_embed_UIFrameWnd_168.m_id + 284))->Update(Point.x, Point.y);
    *(&pTarget.m_vTargetPos + 140) = v36;
    if ( v36 <= 0xA )
    {
      if ( !*(_BYTE *)(this->_embed_UIFrameWnd_168.m_wndcolor.Color + 892 * v36 + 577) )
      {
        *(&pTarget.m_vTargetPos + 140) = -1;
        goto LABEL_70;
      }
      if ( !((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->SetVisible(v36, v70) )
      {
        *(&pTarget.m_vTargetPos + 140) = -1;
        goto LABEL_70;
      }
      v36 = *(&pTarget.m_vTargetPos + 140);
    }
    if ( v36 != -1 )
    {
      ((CCBMagicWindow *)*((CCBMagicWindow **)this->_embed_UIFrameWnd_168.m_id + 284))->Create(v36);
      v37 = (int *)sub_445FE0(a2);
      v38 = *v37;
      v39 = v37[1];
      v82 = v37[2];
      m_id = this->_embed_UIFrameWnd_168.m_id;
      v83 = v37[3];
      v41 = *(_DWORD *)(m_id[284] + 4 * *(&pTarget.m_vTargetPos + 140) + 96);
      *(_DWORD *)(v41 + 76) = 1068708659;
      *(_DWORD *)(v41 + 80) = 1068708659;
      x = Point.x;
      v35 = *(&pTarget.m_vTargetPos + 140);
      LODWORD(m_fSpeed) = Point.x - v38;
      y = Point.y;
      g_RoleSystemCombat.m_partyActor.m_fSpeed = m_fSpeed;
      v45 = Point.y - v39;
      *((_DWORD *)&g_RoleSystemCombat.m_partyActor.m_fSpeed + 1) = Point.y - v39;
      if ( *(&pTarget.m_vTargetPos + 140) != -1 )
        goto LABEL_69;
    }
  }
  else if ( *(&pTarget.m_vTargetPos + 140) != -1 )
  {
    v46 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 284) + 4 * *(&pTarget.m_vTargetPos + 140) + 96);
    *(_DWORD *)(v46 + 76) = 1065353216;
    *(_DWORD *)(v46 + 80) = 1065353216;
    ((CCBMagicWindow *)*((CCBMagicWindow **)this->_embed_UIFrameWnd_168.m_id + 284))->_CCBMagicWindow(*(&pTarget.m_vTargetPos + 140));
    if ( v47 == -1
      || (((CCBMagicWindow *)*((CCBMagicWindow **)this->_embed_UIFrameWnd_168.m_id + 284))->_CCBMagicWindow(*(&pTarget.m_vTargetPos + 140)),
          ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->UnloadWeaponModel(v48),
          v49) )
    {
      ((RoleCameraCtrl *)*((RoleCameraCtrl **)this->_embed_UIFrameWnd_168.m_id + 284))->InitViewSlots();
      *(&pTarget.m_vTargetPos + 140) = -1;
    }
    else
    {
      ((CCBMagicWindow *)*((CCBMagicWindow **)this->_embed_UIFrameWnd_168.m_id + 284))->_CCBMagicWindow(*(&pTarget.m_vTargetPos + 140));
      ((CCBMagicWindow *)*((CCBMagicWindow **)this->_embed_UIFrameWnd_168.m_id + 284))->Reset(*(&pTarget.m_vTargetPos + 140), v50);
      v51 = (CCBMagicWindow **)this->_embed_UIFrameWnd_168.m_id;
      LOBYTE(v89[10]) = 1;
      v89[2] = *(&pTarget.m_vTargetPos + 140);
      ((CCBMagicWindow *)v51[284])->_CCBMagicWindow(*(&pTarget.m_vTargetPos + 140));
      v89[3] = -1;
      v52 = 0;
      v89[1] = v53;
      for ( j = 0; j < 4460; j += 892 )
      {
        v55 = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
        if ( v55->m_Role[0].bMagicMastered[5][j + 4] )
        {
          inited = ((CCBRoleState *)v55)->InitUI(v52);
          if ( *(_DWORD *)&inited->byMagicUseTime[8][3] == v89[1] )
          {
            v57 = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
            v89[3] = v52;
            v58 = ((CCBRoleState *)v57)->InitUI(*(&pTarget.m_vTargetPos + 140));
            *(_DWORD *)&((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(v52)->byMagicUseTime[8][3] = *(_DWORD *)&v58->byMagicUseTime[8][3];
          }
        }
        ++v52;
      }
      v59 = ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(*(&pTarget.m_vTargetPos + 140));
      *(_DWORD *)&v59->byMagicUseTime[8][3] = v89[1];
      v60 = ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleIndex(27, v89, 1);
      if ( v60 != -1 )
      {
        ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v60, 0 /* TODO: (int)CCBStageRole::SetupCombatAction */, 0, 0, 0, 0, -1082130432, 0);
        ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRoleByIdx(v60);
      }
      *(&pTarget.m_vTargetPos + 140) = -1;
    }
  }
LABEL_70:
  if ( BYTE1(this->_embed_UIFrameWnd_168.m_pfather) )
  {
    *(&pTarget.m_vTargetPos + 140) = -1;
    ((CCBUI *)this->_embed_UIFrameWnd_168.m_id)->CreateFiveNimbus(0);
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
    v61 = 24;
    v73 = 0;
    v76 = 0;
    v79 = 24;
    do
    {
      if ( *(_BYTE *)(this->_embed_UIFrameWnd_168.m_wndcolor.Color + v76 + 577) )
      {
        ((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v61))->GetCurrentTask(0x7FFFFFFF);
        ((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v61))->TryRelease();
        if ( !((CCBStageRole *)*(CCBStageRole **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + v61))->ForceEndTaskByPFN() )
        {
          memset(pData, 0, sizeof(pData));
          v62 = (CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color;
          LOBYTE(pData[10]) = 1;
          pData[2] = v73;
          pData[1] = 264;
          v63 = ((CCBStage *)v62)->GetRoleIndex(9, pData, 1);
          if ( v63 != -1 )
          {
            nVal8 = 0;
            v81 = pData[2];
            v82 = pData[3];
            v64 = (CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color;
            nVal8 = 0;
            ((CCBStage *)v64)->GetRoleName(v63, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, &nVal8, -1082130432, 0);
            ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v63, 0 /* TODO: (int)CCBStage::ProcShowItemName */, 0, 0, 0, &nVal8, -1082130432, 0);
            ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v63, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, &nVal8, -1082130432, 0);
            ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRoleByIdx(v63);
            v61 = v79;
          }
        }
      }
      v61 += 4;
      ++v73;
      v79 = v61;
      v76 += 892;
    }
    while ( v61 < 44 );
    ((CCBCamControl *)*(CCBCamControl **)(this->_embed_UIFrameWnd_168.m_fontcolor.Color + 16))->ClearFinishedTask(7);
    v65 = ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleIndex(3, 0, 1);
    if ( v65 != -1 )
    {
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName(v65, 0 /* TODO: (int)CCBStage::IsSubTaskValid */, 0, 0, 0, 0, -1082130432, 1056964608);
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRoleByIdx(v65);
    }
LABEL_79:

  }
  return 0;
}

// 0x004DE8C0
int CCBRoleState::InitSelectionUI(int nVal)
{
  int m_nMaxRound; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  CScreenMode *Instance; // eax
  unsigned int Color; // ecx
  int v12; // ecx
  CCBRoleState *v13; // ecx
  int v14; // ecx
  unsigned int v15; // ecx
  int v16; // ecx
  int v18; // edx
  CCBSystem *vftable; // ecx
  LONG bottom; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  float fValue; // [esp+0x0] [ebp-0x20]
  float fValuea; // [esp+0x0] [ebp-0x20]
  float fValueb; // [esp+0x0] [ebp-0x20]
  int p_DWORD; // [esp+0x14] [ebp-0xC] BYREF
  int p_DWORD2; // [esp+0x18] [ebp-0x8] BYREF
  int p_DWORD3; // [esp+0x1C] [ebp-0x4] BYREF

  m_nMaxRound = this->m_nMaxRound;
  p_DWORD = 0;
  p_DWORD2 = 0;
  p_DWORD3 = 0;
  if ( *((_BYTE *)&this->m_Role[0].nFullMP + 64 * m_nMaxRound + 2) )
    goto LABEL_17;
  ((UIListBox *)*(UIListBox **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 88))->GetCurSel();
  ((UIListBox *)*(UIListBox **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 92))->GetCurSel();
  ((UIListBox *)*(UIListBox **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 96))->GetCurSel();
  ((UIScrollBar *)*(UIScrollBar **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 88))->SetRange(100.0);
  ((UIScrollBar *)*(UIScrollBar **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 92))->SetRange(100.0);
  ((UIScrollBar *)*(UIScrollBar **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 96))->SetRange(100.0);
  fValue = (float)((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(1)->nLove;
  ((UIProgressBar *)*(UIProgressBar **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 88))->FindChildByName(fValue);
  fValuea = (float)((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(2)->nLove;
  ((UIProgressBar *)*(UIProgressBar **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 92))->FindChildByName(fValuea);
  fValueb = (float)((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(3)->nLove;
  ((UIProgressBar *)*(UIProgressBar **)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 96))->FindChildByName(fValueb);
  v4 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 76);
  *(_DWORD *)(v4 + 80) = 0;
  *(_BYTE *)(v4 + 68) = 0;
  v5 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 80);
  *(_DWORD *)(v5 + 80) = 0;
  *(_BYTE *)(v5 + 68) = 0;
  v6 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 84);
  *(_DWORD *)(v6 + 80) = 0;
  *(_BYTE *)(v6 + 68) = 0;
  if ( !((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(1)->bValid )
    sub_445E50(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 76));
  if ( !((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(2)->bValid )
    sub_445E50(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 80));
  if ( !((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(3)->bValid )
    sub_445E50(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 84));
  *(&pTarget.m_vTargetPos + 141) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->nProtectRole;
  v7 = ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->nProtectRole - 1;
  if ( !v7 )
  {
    v9 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 76);
    goto LABEL_15;
  }
  v8 = v7 - 1;
  if ( !v8 )
  {
    v9 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 80);
    goto LABEL_15;
  }
  if ( v8 == 1 )
  {
    v9 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 84);
LABEL_15:
    *(_DWORD *)(v9 + 80) = 1;
    *(_BYTE *)(v9 + 68) = 1;
    goto LABEL_16;
  }
  ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->nProtectRole = -1;
  *(&pTarget.m_vTargetPos + 141) = -1;
LABEL_16:
  ((CCBStageRole *)this->_embed_UIFrameWnd_168.m_id)->SetActionVisible(1);
  *((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) = 1;
  Instance = CScreenMode::GetInstance();
  ((CScreenMode *)Instance)->AudioSetPosition("wa003", 1);
LABEL_17:
  Color = this->_embed_UIFrameWnd_168.m_wndcolor.Color;
  if ( *(_BYTE *)(Color + 1469) && ((CCBRoleState *)Color)->IsRoleAlive(1) )
    v12 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 76);
  else
    v12 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 76);
  sub_445E50(v12);
  v13 = (CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color;
  if ( v13->m_Role[3].bMagicMastered[3][0] && ((CCBRoleState *)v13)->IsRoleAlive(2) )
    v14 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 80);
  else
    v14 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 80);
  sub_445E50(v14);
  v15 = this->_embed_UIFrameWnd_168.m_wndcolor.Color;
  if ( *(_BYTE *)(v15 + 3253) && ((CCBRoleState *)v15)->IsRoleAlive(3) )
    v16 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 84);
  else
    v16 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 84);
  sub_445E50(v16);
  if ( this->GetCombatDialogPos(&p_DWORD, &p_DWORD2, &p_DWORD3)
    && (p_DWORD == 272 || p_DWORD == 282 || (unsigned int)p_DWORD >= 0x111 && (unsigned int)p_DWORD <= 0x113) )
  {
    if ( p_DWORD2 == -1 )
    {
      ((CCBStageRole *)this->_embed_UIFrameWnd_168.m_id)->SetActionVisible(0);
      ((CCBSystem *)this)->FindFreeThread(*(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5], *(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 9], *(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 13], *((_DWORD *)&this->m_Role[0].bValid + 16 * this->m_nMaxRound), 0 /* TODO: (int)CCBRoleState::InitSelectionUI */, 0, 0, 0, 0);

      return 0;
    }
    if ( p_DWORD == 282 )
    {
      ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->nProtectRole = -1;
      if ( *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 76) + 68) )
        ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->nProtectRole = 1;
      if ( *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 80) + 68) )
        ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->nProtectRole = 2;
      if ( *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 84) + 68) )
        ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->nProtectRole = 3;
      ((CCBStageRole *)this->_embed_UIFrameWnd_168.m_id)->SetActionVisible(0);
      if ( *(&pTarget.m_vTargetPos + 141) == ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->InitUI(0)->nProtectRole )
      {
        ((CCBSystem *)this)->FindFreeThread(*(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 5], *(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 9], *(_DWORD *)&this->m_Role[0].sModel[64 * this->m_nMaxRound + 13], *((_DWORD *)&this->m_Role[0].bValid + 16 * this->m_nMaxRound), 0 /* TODO: (int)CCBRoleState::InitSelectionUI */, 0, 0, 0, 0);
      }
      else
      {
        v18 = this->m_nMaxRound;
        LOBYTE(this->m_pUtil) = 1;
        v18 <<= 6;
        this->_embed_UIFrameWnd_168.m_bcreateok = *(int *)((char *)&this->m_Role[0].nHP + v18 + 1);
// [VFTABLE] vftable = (CCBSystem *)this->_embed_UIFrameWnd_168.__vftable;
        bottom = this->_embed_UIFrameWnd_168.m_rect.bottom;
        this->_embed_UIFrameWnd_168.m_bvisible = *(int *)((char *)&this->m_Role[0].nFullHP + v18 + 1);
        this->_embed_UIFrameWnd_168.m_benable = bottom;
        LOBYTE(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
        BYTE1(this->_embed_UIFrameWnd_168.m_pbktex) = 0;
        ((CCBSystem *)vftable)->SetCmdParam(bottom, 0);
      }

      return 0;
    }
    if ( (unsigned int)p_DWORD >= 0x111 && p_DWORD2 == 1 )
    {
      v21 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 76);
      *(_DWORD *)(v21 + 80) = 0;
      *(_BYTE *)(v21 + 68) = 0;
      v22 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 80);
      *(_DWORD *)(v22 + 80) = 0;
      *(_BYTE *)(v22 + 68) = 0;
      v23 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 84);
      *(_DWORD *)(v23 + 80) = 0;
      *(_BYTE *)(v23 + 68) = 0;
      switch ( p_DWORD )
      {
        case 273:
          v24 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 76);
LABEL_55:
          *(_DWORD *)(v24 + 80) = 1;
          *(_BYTE *)(v24 + 68) = 1;
          break;
        case 274:
          v24 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 80);
          goto LABEL_55;
        case 275:
          v24 = *(_DWORD *)(*((_DWORD *)this->_embed_UIFrameWnd_168.m_id + 285) + 84);
          goto LABEL_55;
      }
    }
  }
  if ( BYTE1(this->_embed_UIFrameWnd_168.m_pfather) )
  {
    ((CCBStageRole *)this->_embed_UIFrameWnd_168.m_id)->SetActionVisible(0);
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);

  }
  return 0;
}

// 0x004DEE80
int CCBRoleState::DispatchCombatAction(int nVal)
{
  CCBSystem *RoleIndex; // esi
  char *v4; // eax
  LONG bottom; // ecx
  int RoleNum; // edi
  int ActionPriority; // eax
  int SkillNum; // edi
  LONG v9; // eax
  unsigned int Color; // edx
  unsigned int v11; // eax
  int v12; // eax
  CCBStage *v13; // eax
  int m_nMaxRound; // ecx
  char *v15; // eax
  int v17; // esi
  CCBStage *v18; // ecx
  int v19; // eax
  int *p_m_bcreateok; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  char *v25; // ecx
  char p_BYTE; // [esp+0x13] [ebp-0x41] BYREF
  int v27; // [esp+0x14] [ebp-0x40] BYREF
  int idx; // [esp+0x18] [ebp-0x3C]
  int p_DWORD[3]; // [esp+0x1C] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x28] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  LOBYTE(pData[10]) = 0;
  LOBYTE(pData[4]) = 0;
  RoleIndex = 0;
  v4 = &this->m_sCombatDialog[64 * this->m_nMaxRound];
  v27 = 0;
  p_BYTE = 0;
  pData[0] = *((_DWORD *)v4 + 38);
  bottom = this->_embed_UIFrameWnd_168.m_rect.bottom;
  pData[1] = *((_DWORD *)v4 + 39);
  pData[2] = bottom;
  pData[3] = -1;
  if ( !v4[173] )
  {
    switch ( *((_DWORD *)v4 + 38) )
    {
      case 0x103:
        RoleIndex = (CCBSystem *)((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleIndex(2, pData, 0);
        if ( RoleIndex != (CCBSystem *)-1 )
        {
          v9 = this->_embed_UIFrameWnd_168.m_rect.bottom;
          Color = this->_embed_UIFrameWnd_168.m_wndcolor.Color;
          p_DWORD[0] = 1;
          v11 = Color + 892 * v9;
          if ( *(_BYTE *)(v11 + 649) )
          {
            p_DWORD[0] = 5;
            goto LABEL_12;
          }
          v12 = -(*(_BYTE *)(v11 + 650) != 0);
          LOBYTE(v12) = v12 & 0xF8;
          ActionPriority = v12 + 17;
          goto LABEL_11;
        }
        break;
      case 0x104:
      case 0x105:
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*((_DWORD *)v4 + 39));
        RoleIndex = (CCBSystem *)((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleIndex(2, pData, 0);
        if ( RoleIndex != (CCBSystem *)-1 )
        {
          ActionPriority = this->GetActionPriority(*(unsigned __int8 *)(RoleNum + 577));
          goto LABEL_11;
        }
        break;
      case 0x106:
        SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*((_DWORD *)v4 + 39));
        RoleIndex = (CCBSystem *)((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleIndex(2, pData, 0);
        if ( RoleIndex != (CCBSystem *)-1 )
        {
          ActionPriority = this->GetActionPriority(*(unsigned __int8 *)(SkillNum + 629));
LABEL_11:
          p_DWORD[0] = ActionPriority;
LABEL_12:
          ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetRoleName((int)RoleIndex, 0 /* TODO: (int)CCBStage::HasNormalAttackRole */, 0, 0, 0, p_DWORD, -1082130432, 0);
          ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRoleByIdx((int)RoleIndex);
        }
        break;
      default:
        break;
    }
    *(CCBSystem **)((char *)&this->m_Role[0].pCCBSystem + 64 * this->m_nMaxRound + 1) = RoleIndex;
    LOBYTE(v13) = ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->EndTask((int)RoleIndex);
    *(CCBStage **)((char *)&this->m_Role[0].nMP + 64 * this->m_nMaxRound + 1) = v13;
    *((_BYTE *)&this->m_Role[0].nFullMP + 64 * this->m_nMaxRound + 2) = 1;
  }
  m_nMaxRound = this->m_nMaxRound;
  if ( BYTE1(this->_embed_UIFrameWnd_168.m_pfather) != 1 )
  {
    v17 = *(int *)((char *)&this->m_Role[0].pCCBSystem + 64 * m_nMaxRound + 1);
    v18 = (CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color;
    idx = v17;
    ((CCBStage *)v18)->DelTask(v17, &p_BYTE, &v27);
    if ( p_BYTE == 1 )
    {
      LOBYTE(v19) = ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->IsDoTask(v17);
      p_m_bcreateok = &this->_embed_UIFrameWnd_168.m_bcreateok;
      qmemcpy(&this->_embed_UIFrameWnd_168.m_bcreateok, (const void *)(v19 + 2584), 0x2Cu);
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->GetStageRole(idx);
      *(CCBSystem **)((char *)&this->m_Role[0].pCCBSystem + 64 * this->m_nMaxRound + 1) = (CCBSystem *)-1;
      if ( v27 == -1 )
      {
        v21 = this->m_nMaxRound;
        if ( *(_DWORD *)&this->m_Role[0].sModel[64 * v21 + 5] )
        {
LABEL_22:
          *(_BYTE *)(*(_DWORD *)(this->_embed_UIFrameWnd_168.m_fontcolor.Color
                               + 4 * this->_embed_UIFrameWnd_168.m_rect.bottom
                               + 24)
                   + 280) = 1;
          v22 = this->m_nMaxRound + 2;
// [VFTABLE] ((CCBSystem *)this)->FindFreeThread(*(_DWORD *)&this->m_sCombatDialog[64 * v22], *((_DWORD *)&this->_embed_UIFrameWnd_168.__vftable + 16 * v22), *(&this->_embed_UIFrameWnd_168.m_fontcolor.Color + 16 * v22), *(&this->_embed_UIFrameWnd_168.m_wndcolor.Color + 16 * v22), 0 /* TODO: (int)CCBRoleState::InitCombatDialog */, 0, 0, 0, *(int *)((char *)&this->m_Role[0].nHP + 64 * this->m_nMaxRound + 1));

          return 0;
        }
LABEL_29:
        *((_BYTE *)&this->m_Role[0].nFullMP + 64 * v21 + 2) = 0;
        LOBYTE(this->m_pUtil) = 0;
        return 0;
      }
      v23 = *p_m_bcreateok;
      if ( (*p_m_bcreateok == 259 || v23 == 261 || v23 == 260 || v23 == 262)
        && !((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->SumGPCost((int)&this->_embed_UIFrameWnd_168.m_bcreateok) )
      {
        v21 = this->m_nMaxRound;
        if ( *(_DWORD *)&this->m_Role[0].sModel[64 * v21 + 5] )
          goto LABEL_22;
        goto LABEL_29;
      }
      v24 = this->m_nMaxRound;
      LOBYTE(this->m_pUtil) = 1;
      v25 = &this->m_sCombatDialog[64 * v24];
      *p_m_bcreateok = *((_DWORD *)v25 + 38);
      this->_embed_UIFrameWnd_168.m_bvisible = *((_DWORD *)v25 + 39);

    }
    return 0;
  }
  v15 = &this->m_sCombatDialog[64 * m_nMaxRound];
  if ( *((_DWORD *)v15 + 41) != -1 )
  {
    if ( (unsigned __int8)((CCBSystem *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->FindThreadByID(*((_DWORD *)v15 + 42)) )
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_fontcolor.Color)->Procced(*(int *)((char *)&this->m_Role[0].pCCBSystem + 64 * this->m_nMaxRound + 1));
  }
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
  memset(&this->_embed_UIFrameWnd_168.m_bcreateok, 0, 0x2Cu);

  return 0;
}

// 0x004DF2F0
int CCBRoleState::ExecuteCombatCommand(int nVal)
{
  int v3; // eax
  char v4; // cl
  _BYTE *v5; // eax

  v3 = this->m_nMaxRound << 6;
  v4 = *((_BYTE *)&this->m_Role[0].nFullMP + v3 + 2);
  v5 = (char *)&this->m_Role[0].nFullMP + v3 + 2;
  if ( !v4 )
    *v5 = 1;
  if ( this->m_nBossRound == 1 )
  {
    this->_embed_UIFrameWnd_168.m_childs.m_pData = 0;
    this->_embed_UIFrameWnd_168.m_childs.capacity = 0;
    this->_embed_UIFrameWnd_168.m_childs.m_nSize = 0;
    this->_embed_UIFrameWnd_168.m_childs.m_needscriptdel = 0;
    LOBYTE(this->_embed_UIFrameWnd_168.m_pfather) = 0;
// [VFTABLE] ((CCBAttackSequen *)this->_embed_UIFrameWnd_168.__vftable)->SetPause();
// [VFTABLE] ((CCBSystem *)this->_embed_UIFrameWnd_168.__vftable)->SetCmdParam(this->_embed_UIFrameWnd_168.m_rect.bottom, 0);
    *(_BYTE *)(*(_DWORD *)(this->_embed_UIFrameWnd_168.m_fontcolor.Color
                         + 4 * this->_embed_UIFrameWnd_168.m_rect.bottom
                         + 24)
             + 280) = 0;
    this->_embed_UIFrameWnd_168.m_rect.bottom = -1;
    BYTE1(this->_embed_UIFrameWnd_168.m_pfather) = 0;

  }
  return 0;
}

// 0x004DF370
int CCBRoleState::GetActionPriority(int nVal)
{
  int result; // eax

  switch ( nVal )
  {
    case 1:
      result = 16;
      break;
    case 2:
      result = 2;
      break;
    case 4:
      result = 3;
      break;
    case 5:
      result = 5;
      break;
    case 6:
      result = 9;
      break;
    default:
      result = 17;
      break;
  }
  return result;
}

// 0x004DF3D0
char CCBRoleState::CheckMP()
{
  ((CCBRoleState *)this->_embed_UIFrameWnd_168.m_wndcolor.Color)->GetRoleMP(1);
  return 1;
}

// 0x004DF6D0
int CCBRoleState::ResetDialogSlots()
{
  memset(&this->_embed_UIFrameWnd_168.m_rect, 0, 0x4600u);
  this->_embed_UIFrameWnd_168.m_fontcolor.Color = -1;
  this->m_RoleXor[2].bSkillMastered[11] = 0;
  this->_embed_UIFrameWnd_168.m_id = 0;
  return 0;
}

// 0x004E1A40
int CCBRoleState::CombatDialogProc(
        
        int nVal,
        HWND hDlg,
        unsigned int uMsg,
        int wParam,
        int lParam)
{
  HWND DlgItem; // ebx
  HWND v8; // ebp
  HWND v9; // eax
  unsigned int v10; // eax
  int result; // eax
  LRESULT v12; // eax
  BOOL v13; // edx
  int v14; // ecx
  CCBRoleState *v15; // esi
  int Float; // edi
  HWND m_nActorRenderCount; // eax
  int v18; // esi
  _DWORD *v19; // eax
  HWND v20; // [esp+0x10] [ebp-0x28]
  HWND hWnd; // [esp+0x14] [ebp-0x24]
  LPARAM lParama[8]; // [esp+0x18] [ebp-0x20] BYREF
  HWND hDlga; // [esp+0x40] [ebp+0x8]

  DlgItem = GetDlgItem(hDlg, 1000);
  hDlga = GetDlgItem(hDlg, 1086);
  GetDlgItem(hDlg, 1042);
  v20 = GetDlgItem(hDlg, 1205);
  hWnd = GetDlgItem(hDlg, 1041);
  v8 = GetDlgItem(hDlg, 1209);
  v9 = GetDlgItem(hDlg, 1206);
  if ( uMsg <= 0x110 )
  {
    if ( uMsg == 272 )
    {
      memset(lParama, 0, sizeof(lParama));
      v12 = SendMessageA(DlgItem, 0x1037u, 0, 0);
      LOBYTE(v12) = v12 | 0x21;
      SendMessageA(DlgItem, 0x1036u, 0, v12);
      lParama[0] = 7;
      lParama[1] = 0;
      lParama[2] = 50;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 22;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParama);
      lParama[2] = 49;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)lParama);
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 3u, (LPARAM)lParama);
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 4u, (LPARAM)lParama);
      SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
      LOBYTE(v13) = unk_5DFDEB == 0;
      EditBox_SetReadOnly(v20, v13);
      v14 = nVal;
      LOBYTE(v14) = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)nVal + 16) + 516);
      EditBox_SetReadOnly(v8, v14);
      EnableWindow(hWnd, g_bFullScreen);
      return 0;
    }
    if ( uMsg == 16 )
    {
      EndDialog(hDlg, (unsigned __int16)wParam);
      return 1;
    }
    if ( uMsg == 78 && wParam == 1000 && *(_DWORD *)(lParam + 8) == -2 )
    {
      v10 = *(_DWORD *)(lParam + 12);
      if ( v10 != -1 )
      {
        dwVal = *(_DWORD *)(lParam + 12);
        LOBYTE(g_RoleSystemCombat._field_FE4) = 1;
        if ( v10 > 4 )
          EnableWindow(hDlga, 0);
        else
          EnableWindow(hDlga, 1);
        return 0;
      }
    }
    return 0;
  }
  if ( uMsg != 273 )
    return 0;
  switch ( (__int16)wParam )
  {
    case 1038:
      BYTE1(g_RoleSystemCombat._field_FE4) = 1;
      return 0;
    case 1040:
      m_nActorRenderCount = (HWND)g_RoleSystemCombat.m_nActorRenderCount;
      if ( !g_RoleSystemCombat.m_nActorRenderCount )
      {
        m_nActorRenderCount = CreateDialogParamA(hInstance, (LPCSTR)0x6D, ::hWnd, (DLGPROC)CCBUI::DlgProcMain, 0);
        g_RoleSystemCombat.m_nActorRenderCount = (int)m_nActorRenderCount;
      }
      goto LABEL_25;
    case 1041:
      ((CGameData *)&g_gamefrm)->Load((CUtil *)5);
      return 0;
    case 1042:
      m_nActorRenderCount = g_RoleSystemCombat.g_hCombatDlg2;
      if ( !g_RoleSystemCombat.g_hCombatDlg2 )
      {
        m_nActorRenderCount = CreateDialogParamA(
                                hInstance,
                                (LPCSTR)0x6C,
                                ::hWnd,
                                (DLGPROC)CCBUI::HandleWindowMessage,
                                0);
        g_RoleSystemCombat.g_hCombatDlg2 = m_nActorRenderCount;
      }
      goto LABEL_25;
    case 1043:
      m_nActorRenderCount = g_RoleSystemCombat.g_hCombatDlg1;
      if ( !g_RoleSystemCombat.g_hCombatDlg1 )
      {
        m_nActorRenderCount = CreateDialogParamA(hInstance, (LPCSTR)0x6B, ::hWnd, (DLGPROC)CCBUI::SettingsDialogProc, 0);
        g_RoleSystemCombat.g_hCombatDlg1 = m_nActorRenderCount;
      }
LABEL_25:
      ShowWindow(m_nActorRenderCount, 5);
      result = 0;
      break;
    case 1044:
      v19 = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)nVal + 20) + 16);
      v19[107519] = 1092616192;
      v19[107521] = 1119092736;
      v19[107520] = 1092616192;
      return 0;
    case 1045:
      ((CCBStage *)((unsigned __int16)wParam - 1038))->DestroyPreviewWindow();
      result = 0;
      break;
    case 1086:
      BYTE2(g_RoleSystemCombat._field_FE4) = 1;
      result = 0;
      break;
    case 1159:
      ((CGameData *)&g_gamefrm)->Load((CUtil *)6);
      result = 0;
      break;
    case 1205:
      unk_5DFDEB = !EditBox_IsModified(v20);
      result = 0;
      break;
    case 1207:
      v15 = *(CCBRoleState **)(*(_DWORD *)nVal + 16);
      Float = (__int64)EditBox_GetFloat(v9);
      ((CCBRoleState *)v15)->InitUI(0)->nMoney = Float;
      result = 0;
      break;
    case 1209:
      v18 = *(_DWORD *)(*(_DWORD *)nVal + 16);
      *(_BYTE *)(v18 + 516) = EditBox_IsModified(v8);
      result = 0;
      break;
    default:
      return 0;
  }
  return result;
}

// 0x004E28F0
LRESULT CCBRoleState::UpdateDebugTreeView()
{
  LRESULT result; // eax
  HWND DlgItem; // ebp
  int i; // esi
  int v5; // eax
  int v6; // edx
  tagRoleState *inited; // eax
  int v8; // eax
  tagRoleState *v9; // eax
  int v10; // ecx
  tagRoleState *v11; // eax
  LPARAM lParam[10]; // [esp+0x4] [ebp-0x128] BYREF
  char Buffer[256]; // [esp+0x2C] [ebp-0x100] BYREF

  result = (LRESULT)g_RoleSystemCombat.dwInitParam;
  if ( g_RoleSystemCombat.dwInitParam == (HWND)2 )
  {
    DlgItem = GetDlgItem(g_hMainWnd, 1000);
    memset(lParam, 0, sizeof(lParam));
    SendMessageA(DlgItem, 0x1009u, 0, 0);
    for ( i = 0; i < 11; ++i )
    {
      lParam[0] = 1;
      lParam[1] = i;
      lParam[2] = 0;
      lParam[5] = (LPARAM)Buffer;
      switch ( i )
      {
        case 0:
          sprintf(Buffer, byte_5D899C, 0);
          break;
        case 1:
          sprintf(Buffer, byte_5D8994, 1);
          break;
        case 2:
          sprintf(Buffer, byte_5D898C, 2);
          break;
        case 3:
          sprintf(Buffer, byte_5D8984, 3);
          break;
        case 4:
          sprintf(Buffer, byte_5D897C, 4);
          break;
        default:
          sprintf(Buffer, &unk_5D8974, i);
          break;
      }
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      v5 = *(_DWORD *)this->m_sCombatDialog;
      lParam[2] = 1;
      if ( *(_BYTE *)(*(_DWORD *)(v5 + 16) + 892 * i + 577) )
      {
        sprintf(Buffer, "Y");
        SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      }
      v6 = *(_DWORD *)this->m_sCombatDialog;
      lParam[2] = 2;
      inited = ((CCBRoleState *)*(CCBRoleState **)(v6 + 16))->InitUI(i);
      sprintf(Buffer, &dir[20], inited->nHP);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      v8 = *(_DWORD *)this->m_sCombatDialog;
      lParam[2] = 3;
      v9 = ((CCBRoleState *)*(CCBRoleState **)(v8 + 16))->InitUI(i);
      sprintf(Buffer, &dir[20], v9->nGP);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      v10 = *(_DWORD *)this->m_sCombatDialog;
      lParam[2] = 4;
      v11 = ((CCBRoleState *)*(CCBRoleState **)(v10 + 16))->InitUI(i);
      sprintf(Buffer, &dir[20], v11->nMP);
      result = SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
  }
  return result;
}

// 0x004E2C10
LRESULT CCBRoleState::HandleDlgMessage()
{
  LRESULT result; // eax
  HWND DlgItem; // esi
  tagRoleState *inited; // eax

  result = (LRESULT)g_RoleSystemCombat.dwInitParam;
  if ( g_RoleSystemCombat.dwInitParam == (HWND)2 )
  {
    DlgItem = GetDlgItem(g_hMainWnd, 1206);
    inited = ((CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)this->m_sCombatDialog + 16))->InitUI(0);
    return EditBox_SetInt(DlgItem, inited->nMoney);
  }
  return result;
}

// 0x004E30E0
unsigned __int8 CCBRoleState::SyncRoleUIData()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  unsigned __int8 result; // al
  int v5; // ebx
  int v6; // ebx
  int v7; // ebx
  unsigned int v8; // ebx
  int v9; // ebx
  tagRoleState *inited; // eax
  int v11; // ebx
  CCBSystem *v12; // ebx
  unsigned int v13; // ebx
  int v14; // ebx
  tagRoleState *v15; // eax
  CCBStage *v16; // ebx
  int v17; // ebx
  unsigned int v18; // ebx
  int v19; // ebx
  tagRoleState *v20; // eax
  int v21; // ebx
  unsigned int v22; // ebx
  int v23; // ebx
  unsigned int v24; // ebx
  int v25; // ebx
  unsigned int v26; // ebx
  int v27; // ebx
  unsigned int v28; // ebx
  int v29; // edi
  float fValue; // [esp+0x0] [ebp-0x40]
  float fValuea; // [esp+0x0] [ebp-0x40]
  float fValueb; // [esp+0x0] [ebp-0x40]
  HWND hWnd; // [esp+0x18] [ebp-0x28]
  HWND v34; // [esp+0x1C] [ebp-0x24]
  HWND v35; // [esp+0x20] [ebp-0x20]
  HWND v36; // [esp+0x24] [ebp-0x1C]
  HWND v37; // [esp+0x28] [ebp-0x18]
  HWND v38; // [esp+0x2C] [ebp-0x14]
  HWND v39; // [esp+0x30] [ebp-0x10]
  HWND v40; // [esp+0x34] [ebp-0xC]
  HWND v41; // [esp+0x38] [ebp-0x8]
  HWND v42; // [esp+0x3C] [ebp-0x4]

  GetDlgItem(g_hMainWnd, 1024);
  DlgItem = GetDlgItem(g_hMainWnd, 1026);
  v3 = GetDlgItem(g_hMainWnd, 1032);
  hWnd = GetDlgItem(g_hMainWnd, 1025);
  v34 = GetDlgItem(g_hMainWnd, 1033);
  v35 = GetDlgItem(g_hMainWnd, 1027);
  v36 = GetDlgItem(g_hMainWnd, 1034);
  v37 = GetDlgItem(g_hMainWnd, 1028);
  v38 = GetDlgItem(g_hMainWnd, 1029);
  v39 = GetDlgItem(g_hMainWnd, 1030);
  v40 = GetDlgItem(g_hMainWnd, 1031);
  v41 = GetDlgItem(g_hMainWnd, 1035);
  v42 = GetDlgItem(g_hMainWnd, 1036);
  result = dwVal;
  if ( dwVal <= 0xA )
  {
// [VFTABLE] result = *((_BYTE *)&this->_embed_UIFrameWnd_168.__vftable[20].Create + 892 * dwVal + 1);
    if ( result )
    {
      SendMessageA(DlgItem, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v5 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nHP = v5;
// [VFTABLE] if ( !((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->bAlive
// [VFTABLE]   && ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nHP > 0 )
      {
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
        ((CCBStageRole *)*(CCBStageRole **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 20) + 4 * dwVal + 24))->Release(1);
        v6 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nHP = v6;
      }
// [VFTABLE] if ( ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->bAlive == 1
// [VFTABLE]   && !((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nHP )
      {
        ((CCBSystem *)*(CCBSystem **)this->m_sCombatDialog)->ProcMessage(dwVal);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
        ((CCBStageRole *)*(CCBStageRole **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 20) + 4 * dwVal + 24))->Release(0);
      }
      SendMessageA(v3, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v7 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nFullHP = v7;
      if ( dwVal <= 4 )
      {
        v8 = 352 * dwVal;
// [VFTABLE] *(_DWORD *)&Buffer.m_partyActor.m_szTexture[v8 * 4 + 8] += ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nFullHP
                                                                 - Buffer.m_partyActor.m_dwMatMsg[v8 + 9];
        v9 = *(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4);
        fValue = (float)atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] inited = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal);
        ((UIScrollBar *)*(UIScrollBar **)(v9 + 4 * (unsigned __int8)inited->byUIIndex + 1020))->SetRange(fValue);
      }
      SendMessageA(hWnd, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v11 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nGP = v11;
      SendMessageA(v34, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v12 = (CCBSystem *)atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->pCCBSystem = v12;
      if ( dwVal <= 4 )
      {
        v13 = 352 * dwVal;
// [VFTABLE] *(_DWORD *)&Buffer.m_partyActor.m_szTexture[v13 * 4 + 12] += (char *)((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->pCCBSystem
                                                                   - Buffer.m_partyActor.m_dwMatMsg[v13 + 10];
        v14 = *(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4);
        fValuea = (float)atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] v15 = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal);
        ((UIScrollBar *)*(UIScrollBar **)(v14 + 4 * (unsigned __int8)v15->byUIIndex + 1036))->SetRange(fValuea);
      }
      SendMessageA(v35, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v16 = (CCBStage *)atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nMP = v16;
      SendMessageA(v36, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v17 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nFullMP = v17;
      if ( dwVal <= 4 )
      {
        v18 = 352 * dwVal;
// [VFTABLE] *(_DWORD *)&Buffer.m_partyActor.m_szTexture[v18 * 4 + 16] += ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nFullMP
                                                                   - Buffer.m_partyActor.m_dwMatMsg[v18 + 11];
        v19 = *(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4);
        fValueb = (float)atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] v20 = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal);
        ((UIScrollBar *)*(UIScrollBar **)(v19 + 4 * (unsigned __int8)v20->byUIIndex + 1052))->SetRange(fValueb);
      }
      SendMessageA(v37, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v21 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nLevel = v21;
      SendMessageA(v38, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal);
      atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleLevel(dwVal);
      v22 = 1408 * dwVal;
// [VFTABLE] *(_DWORD *)((char *)&Buffer.m_partyActor.m_vecLocalPos.x + v22) += ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nSpeed
                                                                       - *(_DWORD *)&Buffer.m_partyActor.m_curact[v22 + 11];
      SendMessageA(v39, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v23 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nAttack = v23;
      v24 = 1408 * dwVal;
// [VFTABLE] *(_DWORD *)&Buffer.m_partyActor.m_szTexture[v24 + 20] += ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nAttack
                                                             - *(_DWORD *)&Buffer.m_partyActor.m_curact[v24 + 3];
      SendMessageA(v40, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v25 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nDefence = v25;
      v26 = 1408 * dwVal;
// [VFTABLE] *(_DWORD *)&Buffer.m_partyActor.m_szTexture[v26 + 24] += ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nDefence
                                                             - *(_DWORD *)&Buffer.m_partyActor.m_curact[v26 + 7];
      SendMessageA(v41, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v27 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nLuck = v27;
      v28 = 1408 * dwVal;
// [VFTABLE] *(_DWORD *)((char *)&Buffer.m_partyActor.m_vecLocalPos.y + v28) += ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->nLuck
                                                                       - *(_DWORD *)&Buffer.m_partyActor.m_curact[v28 + 15];
      SendMessageA(v42, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v29 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] *(_DWORD *)&((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->InitUI(dwVal)->bLostMoneyGetLife = v29;
      ((CCBUI *)this)->HandleRoleStateDialog(dwVal);
      return ((RoleSystem *)((char *)&Buffer + 1408 * dwVal))->RecalcAggregatedStats(0);
    }
  }
  return result;
}

// 0x004E40B0
LRESULT CCBRoleState::UpdateDebugDialog()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  HWND v4; // edi
  LRESULT result; // eax
  CCBRoleState *vftable; // ecx
  BOOL v7; // eax
  BOOL v8; // eax
  BOOL v9; // eax
  BOOL v10; // eax
  BOOL v11; // eax
  BOOL v12; // eax
  BOOL v13; // eax
  BOOL v14; // eax
  BOOL v15; // eax
  BOOL v16; // eax
  BOOL v17; // eax
  BOOL v18; // eax
  BOOL v19; // eax
  BOOL v20; // eax
  BOOL v21; // eax
  BOOL v22; // eax
  BOOL v23; // eax
  BOOL v24; // eax
  BOOL v25; // eax
  BOOL v26; // eax
  BOOL v27; // eax
  BOOL v28; // eax
  BOOL v29; // eax
  BOOL v30; // eax
  HWND hWnd; // [esp+0x10] [ebp-0x54]
  HWND v32; // [esp+0x14] [ebp-0x50]
  HWND v33; // [esp+0x18] [ebp-0x4C]
  HWND v34; // [esp+0x1C] [ebp-0x48]
  HWND v35; // [esp+0x20] [ebp-0x44]
  HWND v36; // [esp+0x24] [ebp-0x40]
  HWND v37; // [esp+0x28] [ebp-0x3C]
  HWND v38; // [esp+0x2C] [ebp-0x38]
  HWND v39; // [esp+0x30] [ebp-0x34]
  HWND v40; // [esp+0x34] [ebp-0x30]
  HWND v41; // [esp+0x38] [ebp-0x2C]
  HWND v42; // [esp+0x3C] [ebp-0x28]
  HWND v43; // [esp+0x40] [ebp-0x24]
  HWND v44; // [esp+0x44] [ebp-0x20]
  HWND v45; // [esp+0x48] [ebp-0x1C]
  HWND v46; // [esp+0x4C] [ebp-0x18]
  HWND v47; // [esp+0x50] [ebp-0x14]
  HWND v48; // [esp+0x54] [ebp-0x10]
  HWND v49; // [esp+0x58] [ebp-0xC]
  HWND v50; // [esp+0x5C] [ebp-0x8]
  HWND v51; // [esp+0x60] [ebp-0x4]

  DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1116);
  v3 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1117);
  hWnd = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1119);
  v32 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1118);
  v33 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1120);
  v34 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1121);
  v35 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1122);
  v36 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1123);
  v37 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1124);
  v38 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1125);
  v39 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1126);
  v40 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1127);
  v41 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1128);
  v42 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1129);
  v43 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1130);
  v44 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1131);
  v45 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1132);
  v46 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1133);
  v47 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1134);
  v48 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1135);
  v49 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1136);
  v50 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1137);
  v51 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1138);
  v4 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1140);
  result = dwVal;
  if ( dwVal <= 0xA )
  {
// [VFTABLE] vftable = (CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable;
    if ( vftable->m_Role[0].bMagicMastered[5][892 * dwVal + 4] )
    {
      LOBYTE(v7) = ((CCBRoleState *)vftable)->GetRoleField(dwVal, 3);
      EditBox_SetReadOnly(DlgItem, v7);
// [VFTABLE] LOBYTE(v8) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 4);
      EditBox_SetReadOnly(v3, v8);
// [VFTABLE] LOBYTE(v9) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 1);
      EditBox_SetReadOnly(hWnd, v9);
// [VFTABLE] LOBYTE(v10) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 2);
      EditBox_SetReadOnly(v32, v10);
// [VFTABLE] LOBYTE(v11) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 5);
      EditBox_SetReadOnly(v33, v11);
// [VFTABLE] LOBYTE(v12) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 6);
      EditBox_SetReadOnly(v34, v12);
// [VFTABLE] LOBYTE(v13) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 7);
      EditBox_SetReadOnly(v35, v13);
// [VFTABLE] LOBYTE(v14) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 8);
      EditBox_SetReadOnly(v36, v14);
// [VFTABLE] LOBYTE(v15) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 9);
      EditBox_SetReadOnly(v37, v15);
// [VFTABLE] LOBYTE(v16) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 10);
      EditBox_SetReadOnly(v38, v16);
// [VFTABLE] LOBYTE(v17) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 11);
      EditBox_SetReadOnly(v39, v17);
// [VFTABLE] LOBYTE(v18) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 12);
      EditBox_SetReadOnly(v40, v18);
// [VFTABLE] LOBYTE(v19) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 13);
      EditBox_SetReadOnly(v41, v19);
// [VFTABLE] LOBYTE(v20) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 14);
      EditBox_SetReadOnly(v42, v20);
// [VFTABLE] LOBYTE(v21) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 15);
      EditBox_SetReadOnly(v43, v21);
// [VFTABLE] LOBYTE(v22) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 16);
      EditBox_SetReadOnly(v44, v22);
// [VFTABLE] LOBYTE(v23) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 17);
      EditBox_SetReadOnly(v45, v23);
// [VFTABLE] LOBYTE(v24) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 18);
      EditBox_SetReadOnly(v46, v24);
// [VFTABLE] LOBYTE(v25) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 19);
      EditBox_SetReadOnly(v47, v25);
// [VFTABLE] LOBYTE(v26) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 20);
      EditBox_SetReadOnly(v48, v26);
// [VFTABLE] LOBYTE(v27) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 21);
      EditBox_SetReadOnly(v49, v27);
// [VFTABLE] LOBYTE(v28) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 22);
      EditBox_SetReadOnly(v50, v28);
// [VFTABLE] LOBYTE(v29) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 23);
      EditBox_SetReadOnly(v51, v29);
// [VFTABLE] LOBYTE(v30) = ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleField(dwVal, 26);
      return EditBox_SetReadOnly(v4, v30);
    }
  }
  return result;
}

// 0x004E4570
char CCBRoleState::ApplyDebugEdits()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  HWND v4; // edi
  char result; // al
  HWND hWnd; // [esp+0x10] [ebp-0x54]
  HWND v7; // [esp+0x14] [ebp-0x50]
  HWND v8; // [esp+0x18] [ebp-0x4C]
  HWND v9; // [esp+0x1C] [ebp-0x48]
  HWND v10; // [esp+0x20] [ebp-0x44]
  HWND v11; // [esp+0x24] [ebp-0x40]
  HWND v12; // [esp+0x28] [ebp-0x3C]
  HWND v13; // [esp+0x2C] [ebp-0x38]
  HWND v14; // [esp+0x30] [ebp-0x34]
  HWND v15; // [esp+0x34] [ebp-0x30]
  HWND v16; // [esp+0x38] [ebp-0x2C]
  HWND v17; // [esp+0x3C] [ebp-0x28]
  HWND v18; // [esp+0x40] [ebp-0x24]
  HWND v19; // [esp+0x44] [ebp-0x20]
  HWND v20; // [esp+0x48] [ebp-0x1C]
  HWND v21; // [esp+0x4C] [ebp-0x18]
  HWND v22; // [esp+0x50] [ebp-0x14]
  HWND v23; // [esp+0x54] [ebp-0x10]
  HWND v24; // [esp+0x58] [ebp-0xC]
  HWND v25; // [esp+0x5C] [ebp-0x8]
  HWND v26; // [esp+0x60] [ebp-0x4]

  DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1116);
  v3 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1117);
  hWnd = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1119);
  v7 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1118);
  v8 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1120);
  v9 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1121);
  v10 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1122);
  v11 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1123);
  v12 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1124);
  v13 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1125);
  v14 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1126);
  v15 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1127);
  v16 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1128);
  v17 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1129);
  v18 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1130);
  v19 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1131);
  v20 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1132);
  v21 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1133);
  v22 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1134);
  v23 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1135);
  v24 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1136);
  v25 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1137);
  v26 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1138);
  v4 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg2, 1140);
  result = dwVal;
  if ( dwVal <= 0xA )
  {
// [VFTABLE] result = *((_BYTE *)&this->_embed_UIFrameWnd_168.__vftable[20].Create + 892 * dwVal + 1);
    if ( result )
    {
      EditBox_IsModified(DlgItem);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v3);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(hWnd);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v7);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v8);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v9);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v10);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v11);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v12);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v13);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v14);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v15);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v16);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v17);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v18);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v19);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v20);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v21);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v22);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v23);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v24);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v25);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v26);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      EditBox_IsModified(v4);
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->ProcessRound(dwVal);
      result = EndDialog(g_RoleSystemCombat.g_hCombatDlg2, 0);
      g_RoleSystemCombat.g_hCombatDlg2 = 0;
    }
  }
  return result;
}

// 0x004E5110
int CCBRoleState::GetTargetCommand()
{
  int *TargetRole; // eax
  int result; // eax
  int p_DWORD; // [esp+0x0] [ebp-0x18] BYREF
  int v3; // [esp+0x4] [ebp-0x14]
  int v4; // [esp+0x8] [ebp-0x10]
  char pOut[12]; // [esp+0xC] [ebp-0xC] BYREF

  v3 = 0;
  v4 = 0;
  p_DWORD = 0xFFFF;
  TargetRole = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
  p_DWORD = *TargetRole;
  v3 = TargetRole[1];
  v4 = TargetRole[2];
  result = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
  BYTE2(g_RoleSystemCombat.m_configData[2]) = 1;
  return result;
}

// 0x004EC680
CCBRoleState * CCBRoleState::ClearAndSetGP(int nVal)
{
  memset(this, 0, 0x50A4u);
  *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) = nVal;
  *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) = *(_DWORD *)(nVal + 4);
  return this;
}

// 0x004EC6B0
int CCBRoleState::ClearRoleMemory()
{
  *(_WORD *)((char *)&this->m_Role[0].dwMagicID[8][4] + 1) = 0;
  memset(&this->m_Role[0].bMagicMastered[1][3], 0, 0x2654u);
  memset(&this->m_BufferData[3647], 0, 0x2654u);
  memset(&this->m_RoleXor[6].bMagicMastered[3][5], 0, 0x24u);
  memset((char *)&this->m_RoleXor[6].byMagicUseTime[0][2] + 1, 0, 0x18u);
  return 0;
}

// 0x004EC7D0
char CCBRoleState::IterateMagicSlots()
{
  _BYTE *p_bAttackRow; // ebp
  _DWORD *v2; // esi
  int v3; // edi
  void ( ***v4)(_DWORD, int); // ecx
  int v6; // [esp+0x10] [ebp-0x4]

  p_bAttackRow = &this->m_Role[2].bAttackRow;
  v6 = 5;
  do
  {
    v2 = p_bAttackRow;
    v3 = 3;
    do
    {
      v4 = (void ( ***)(_DWORD, int))*(v2 - 3);
      if ( v4 )
      {
        (**v4)(v4, 1);
        *(v2 - 3) = 0;
      }
      if ( *v2 )
      {
        (**(void ( ***)(_DWORD, int))*v2)(*v2, 1);
        *v2 = 0;
      }
      ++v2;
      --v3;
    }
    while ( v3 );
    p_bAttackRow += 892;
    --v6;
  }
  while ( v6 );
  return 1;
}

// 0x004EC830
char CCBRoleState::DestroyAndReinit()
{
  unsigned int *v2; // eax
  int v3; // eax
  char v4; // cl
  int v5; // eax
  int v6; // ecx

  v2 = *(unsigned int **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
  *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) = v2[5];
  *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][3] + 1) = *v2;


  v3 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
  *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[7][4] + 1) = *(unsigned int *)(v3 + 80);
  *(_DWORD *)&this->m_Role[0].bMagicMastered[0][1] = 0;
  *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][5] + 1) = *(_DWORD *)(*(_DWORD *)(v3 + 112) + 28);
  v4 = *(_BYTE *)(*(_DWORD *)(v3 + 112) + 72);
  this->m_Role[0].bMagicMastered[1][0] = 0;
  this->m_Role[0].bMagicMastered[0][5] = v4;


  ((PAL_GDB *)this)->LoadSkillData();




  v5 = this->CheckDeath(*(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 112) + 64));
  this->SwapEffectParams(v5);

  v6 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[3][1] = 0;
  *(float *)((char *)&this->m_RoleXor[6].byMagicUseTime[2][2] + 1) = *(float *)(v6 + 80);
  return 1;
}

// 0x004EC910
int CCBRoleState::SetupCombatLayout()
{
  int v2; // eax
  int v3; // ebp
  int *i; // ebx
  void (***v5)(_DWORD, _DWORD); // ecx
  int result; // eax
  int v7; // edi
  void ( ***v8)(_DWORD, int); // ecx
  int v9; // ecx
  float fValue; // [esp+0x0] [ebp-0x20]
  float fValuea; // [esp+0x0] [ebp-0x20]
  float fValueb; // [esp+0x0] [ebp-0x20]
  int v13; // [esp+0x14] [ebp-0xC]
  int v14; // [esp+0x18] [ebp-0x8]
  int v15; // [esp+0x1C] [ebp-0x4]

  v2 = 0;
  v15 = 0;
  v3 = 156;
  for ( i = (int *)&this->m_Role[0].bMagicMastered[8][1]; ; i += 223 )
  {
    if ( *((_BYTE *)i - 15) )
    {
      *((_BYTE *)i - 16) = v2;
      v7 = v2;
      v15 = v2 + 1;
      fValue = (float)*i;
      ((UIScrollBar *)*(UIScrollBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v2 + 1020))->SetRange(fValue);
      fValuea = (float)i[2];
      ((UIScrollBar *)*(UIScrollBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v7 + 1036))->SetRange(fValuea);
      fValueb = (float)i[4];
      ((UIScrollBar *)*(UIScrollBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v7 + 1052))->SetRange(fValueb);
      this->Init(*((unsigned __int8 *)i - 16), 1);
      v8 = *(void ( ****)(_DWORD, int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                                + v3
                                                - 20);
      (**v8)(v8, 1);
      (***(void ( ****)(_DWORD, int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3))(
        *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3),
        1);
      result = g_nStatePanelL[v7];
      v9 = g_nStatePanelT[v7];
      v14 = result;
      v13 = v9;
      switch ( v7 )
      {
        case 0:
          sub_445D20(
            *(_DWORD **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3 - 20),
            result + 43,
            v9 + 14);
          result = sub_445D20(
                     *(_DWORD **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3),
                     v14 + 38,
                     v13 + 39);
          break;
        case 1:
        case 2:
          sub_445D20(
            *(_DWORD **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3 - 20),
            result + 33,
            v9 + 15);
          result = sub_445D20(
                     *(_DWORD **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3),
                     v14 + 24,
                     v13 + 41);
          break;
        case 3:
          sub_445D20(
            *(_DWORD **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3 - 20),
            result + 33,
            v9 + 15);
          result = sub_445D20(
                     *(_DWORD **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3),
                     v14 + 23,
                     v13 + 41);
          break;
        default:
          break;
      }
    }
    else
    {
      *((_BYTE *)i - 16) = -1;
      v5 = *(void ( ****)(_DWORD, _DWORD))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                                   + v3
                                                   - 20);
      (**v5)(v5, 0);
      result = (***(int ( ****)(_DWORD, _DWORD))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2]
                                                                               + 1)
                                                         + v3))(
                 *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + v3),
                 0);
    }
    v3 += 4;
    if ( v3 >= 176 )
      return result;
    v2 = v15;
  }
}

// 0x004ECB00
int CCBRoleState::Update()
{


  return this->UpdateEffects();
}

// 0x004ECB20
char CCBRoleState::ProcessCombatAction(int roleIdx)
{
  CCBSystem *v5; // ecx
  int v6; // eax
  char *v7; // edi
  char v8; // al
  int v9; // eax
  double v10; // st7
  CCBStage *v11; // ecx
  int RoleIndex; // edi
  CCBStage *v13; // ecx
  int v14; // eax
  _BYTE *v15; // ecx
  int v16; // eax
  _BYTE *i; // ecx
  _DWORD pData[11]; // [esp+0xC] [ebp-0x40] BYREF
  int p_DWORD[2]; // [esp+0x38] [ebp-0x14] BYREF
  int v21; // [esp+0x40] [ebp-0xC]
  int v22; // [esp+0x44] [ebp-0x8]
  char *v23; // [esp+0x48] [ebp-0x4]
  int roleIdxa; // [esp+0x54] [ebp+0x8]
  int roleIdxb; // [esp+0x54] [ebp+0x8]
  float roleIdxc; // [esp+0x54] [ebp+0x8]

  if ( *(_DWORD *)&this->m_Role[0].bMagicMastered[0][1] >= *(int *)((char *)&this->m_Role[0].dwMagicID[8][5]
                                                                             + 1) )
    return 1;
  v5 = *(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12);
  v6 = *(_DWORD *)((char *)&this->m_Role[2].fMPCostDec + 892 * roleIdx + 1);
  v7 = &this->m_sCombatDialog[892 * roleIdx];
  v23 = v7;
  roleIdxa = v6;
  if ( v6 < ((CCBSystem *)v5)->GetCmdValue(roleIdx) )
  {
    *((_DWORD *)v7 + 356) = roleIdxa + 1;
    if ( roleIdx == 10 )
      ++*(_DWORD *)&this->m_Role[0].bMagicMastered[0][1];
    this->TickDebuffs(roleIdx);
    if ( !v7[1390] )
      goto LABEL_17;
    v8 = v7[1391] + 1;
    v7[1391] = v8;
    if ( (unsigned __int8)v8 >= 4u )
      v7[1390] = 0;
    v9 = this->SetRoleField(roleIdx, 1);
    roleIdxb = 0;
    switch ( v7[1391] )
    {
      case 1:
        v10 = (double)-v9 * 0.050000001;
        break;
      case 2:
        v10 = (double)-v9 * 0.1;
        break;
      case 3:
        v10 = (double)-v9 * 0.15000001;
        break;
      default:
LABEL_16:
        ((CCBSystem *)this)->AddCommand(roleIdx, roleIdxb, 1);
        ((CCBSystem *)this)->AddCommand(3, -roleIdxb, 1);
LABEL_17:
        if ( *((float *)v7 + 168) > 0.0 && *((_DWORD *)v7 + 147) < *((_DWORD *)v7 + 148) )
          ((CCBSystem *)this)->AddCommand(roleIdx, (__int64)((double)*((int *)v7 + 148) * *((float *)v7 + 168) * 0.0099999998), 1);
        if ( *((float *)v7 + 169) > 0.0 && *((_DWORD *)v7 + 149) < *((_DWORD *)v7 + 150) )
          this->CalcAttackPower(roleIdx);
        if ( *((float *)v7 + 170) > 0.0 && *((_DWORD *)v7 + 151) < *((_DWORD *)v7 + 152) )
          this->CalcDefensePower(roleIdx);
        if ( roleIdx >= 5 && roleIdx < 11 && *((int *)v7 + 359) > 0 )
        {
          roleIdxc = (double)*((int *)v7 + 359) * 10.24;
          v22 = (int)roleIdxc;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
          if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < v22 )
          {
            v7[1431] = 1;
            memset(pData, 0, sizeof(pData));
            v11 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
            pData[2] = roleIdx;
            RoleIndex = ((CCBStage *)v11)->GetRoleIndex(21, pData, 1);
            if ( RoleIndex != -1 )
            {
              v21 = 0;
              p_DWORD[0] = 0;
              p_DWORD[1] = roleIdx;
              v13 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
              v21 = -1;
              ((CCBStage *)v13)->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, p_DWORD, -1082130432, 0);
              ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStageRole::TaskMoveToStart */, 0, 0, 0, p_DWORD, -1082130432, 0);
              ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, p_DWORD, -1082130432, 0);
              ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
            }
            v7 = v23;
          }
        }
        if ( *((_DWORD *)v7 + 138) == 7372 && *((_DWORD *)v7 + 356) == 3 )
          this->ProcessRound(roleIdx);
        if ( *((_DWORD *)v7 + 138) == 7378 && *((int *)v7 + 356) >= 3 )
        {
          v22 = (int)51.199997;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
          if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)51.199997 )
          {
            v14 = 0;
            v15 = &this->m_Role[0].bMagicMastered[5][5];
            while ( v14 < 5 || *(v15 - 1) && *v15 )
            {
              ++v14;
              v15 += 892;
              if ( v14 >= 11 )
                goto LABEL_46;
            }
            this->InitSlot(v14, 7378);
          }
        }
LABEL_46:
        if ( *((_DWORD *)v7 + 138) == 7395 && *((_DWORD *)v7 + 356) == 2 )
        {
          v22 = (int)204.79999;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
          if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)204.79999 )
          {
            v16 = 0;
            for ( i = &this->m_Role[0].bMagicMastered[5][4]; v16 < 5 || *i; i += 892 )
            {
              if ( ++v16 >= 11 )
                return 0;
            }
            this->InitSlot(v16, 7395);
          }
        }
        return 0;
    }
    roleIdxb = (__int64)v10;
    goto LABEL_16;
  }
  return 0;
}

// 0x004ED010
char CCBRoleState::IsRoleAlive(int roleIdx)
{
  if ( this->m_Role[0].bMagicMastered[5][892 * roleIdx + 4] )
    return this->m_Role[0].bMagicMastered[5][892 * roleIdx + 5];
  else
    return 0;
}

// 0x004ED040
char CCBRoleState::IsActive(int index)
{
  return this->m_Role[0].bMagicMastered[6][892 * index];
}

// 0x004ED060
char CCBRoleState::GetRoleType(int roleIdx)
{
  char *v2; // eax

  v2 = &this->m_sCombatDialog[892 * roleIdx];
  if ( !v2[577] )
    return 0;
  if ( v2[579] == 1 )
    return 0;
  return v2[580];
}

// 0x004ED0A0
char CCBRoleState::ApplyHitEffect(char pData)
{
  int v2; // edx
  int *i; // eax
  int v5; // edx
  _BYTE *j; // eax

  if ( pData )
  {
    v2 = 0;
    for ( i = (int *)&this->m_Role[0].bMagicMastered[7][3]; !*((_BYTE *)i - 11) || *i <= 0; i += 223 )
    {
      if ( ++v2 >= 5 )
        return 1;
    }
  }
  else
  {
    v5 = 0;
    for ( j = &this->m_Role[0].bMagicMastered[5][5]; !*(j - 1) || *j != 1; j += 892 )
    {
      if ( ++v5 >= 5 )
        return 1;
    }
  }
  return 0;
}

// 0x004ED100
int CCBRoleState::GetForce(int roleIdx)
{
  int v2; // edx
  int result; // eax

  v2 = 5;
  if ( (_BYTE)roleIdx )
  {
    result = (int)&this->m_Role[8].fMPIncPerRound + 1;
    while ( !*(_BYTE *)(result - 11) || *(int *)result <= 0 || *(_BYTE *)(result + 844) )
    {
      ++v2;
      result += 892;
      if ( v2 >= 11 )
      {
        LOBYTE(result) = 1;
        return result;
      }
    }
  }
  else
  {
    result = (int)&this->m_Role[8].fHPIncPerRound + 3;
    while ( !*(_BYTE *)(result - 1) || *(_BYTE *)result != 1 || *(_BYTE *)(result + 854) )
    {
      ++v2;
      result += 892;
      if ( v2 >= 11 )
      {
        LOBYTE(result) = 1;
        return result;
      }
    }
  }
  LOBYTE(result) = 0;
  return result;
}

// 0x004ED170
char CCBRoleState::ShuffleSlots()
{
  _BYTE *v1; // ebx
  int v2; // eax
  int v3; // ecx
  int v4; // edi
  int v5; // ecx
  int v6; // esi
  int v7; // edx
  int v8; // edx
  _DWORD v10[6]; // [esp+0x4] [ebp-0x18] BYREF

  v1 = *(_BYTE **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 112);
  LOBYTE(v2) = v1[80];
  if ( !(_BYTE)v2 )
  {
    LOBYTE(v2) = v1[72];
    if ( !(_BYTE)v2 )
    {
      qmemcpy(v10, v1, sizeof(v10));
      v3 = unk_5DFDEC;
      v4 = 100;
      do
      {
        v5 = 214013 * v3 + 2531011;
        *(_DWORD *)&g_TempBuffer1024[912] += 2;
        v6 = ((v5 >> 16) & 0x7FFF) % 6;
        v3 = 214013 * v5 + 2531011;
        unk_5DFDEC = v3;
        v2 = ((v3 >> 16) & 0x7FFF) / 6;
        v7 = ((v3 >> 16) & 0x7FFF) % 6;
        if ( v6 != v7 )
        {
          v2 = (int)&v10[v7];
          v8 = v10[v6];
          v10[v6] = *(_DWORD *)v2;
          *(_DWORD *)v2 = v8;
          v3 = unk_5DFDEC;
        }
        --v4;
      }
      while ( v4 );
      qmemcpy(v1, v10, 0x18u);
    }
  }
  return v2;
}

// 0x004ED250
int CCBRoleState::LoadPartyData()
{
  int v1; // edx
  int v2; // eax
  float *p_m_fActionAssignParam; // ebx
  char *v4; // ebp
  int v5; // eax
  int v6; // esi
  char v7; // al
  int v8; // edi
  int v9; // eax
  int result; // eax
  CCBRoleState *v11; // [esp+0x10] [ebp-0xC]
  unsigned int dwVal; // [esp+0x14] [ebp-0x8]
  int v13; // [esp+0x18] [ebp-0x4]

  v1 = 0;
  v2 = -20;
dwVal = 0;
  p_m_fActionAssignParam = &Buffer.m_partyActor.m_fActionAssignParam;
  v4 = (char *)&this->m_Role[0].byMagicUseTime[7][1] + 1;
  v13 = -20;
  do
  {
    if ( v2 < 0 )
    {
      *(v4 - 105) = 1;
      *(v4 - 104) = 0;
      *(v4 - 101) = 0;
      *((_DWORD *)v4 + 113) = *((unsigned __int8 *)p_m_fActionAssignParam + 666);
      if ( BYTE2(Buffer.m_partyActor.m_vecPos.x) )
        *(float *)v4 = *(float *)v4 + 20.0;
      if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v1) )
      {
        *(v4 - 107) = 1;
        *(v4 - 106) = 1;
        *((float *)v4 - 33) = *(p_m_fActionAssignParam - 185);
        *((_DWORD *)v4 - 32) = v1;
        *((float *)v4 + 5) = *p_m_fActionAssignParam;
        *((float *)v4 - 25) = *(p_m_fActionAssignParam - 27);
        *((float *)v4 - 23) = p_m_fActionAssignParam[46];
        *((float *)v4 - 21) = p_m_fActionAssignParam[47];
        *((float *)v4 - 19) = p_m_fActionAssignParam[48];
        *((float *)v4 - 24) = p_m_fActionAssignParam[58];
        *((float *)v4 - 22) = p_m_fActionAssignParam[59];
        *((float *)v4 - 20) = p_m_fActionAssignParam[60];
        *((_DWORD *)v4 + 113) = *((unsigned __int8 *)p_m_fActionAssignParam + 666);
        *((float *)v4 - 18) = p_m_fActionAssignParam[49];
        *((float *)v4 - 17) = p_m_fActionAssignParam[50];
        *((float *)v4 - 16) = p_m_fActionAssignParam[51];
        *((float *)v4 - 15) = p_m_fActionAssignParam[52];
        *((_DWORD *)v4 - 13) = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom;
        *((_DWORD *)v4 - 12) = 0;
        *((_DWORD *)v4 - 14) = *(int *)((char *)&g_nRoleInitLevel[5] + v2);
        qmemcpy(v4 + 28, p_m_fActionAssignParam + 73, 0x1Eu);
        qmemcpy(v4 + 60, p_m_fActionAssignParam + 81, 0xC0u);
        qmemcpy(v4 + 252, p_m_fActionAssignParam + 129, 0x30u);
        qmemcpy(v4 + 300, p_m_fActionAssignParam + 141, 0x30u);
        qmemcpy(v4 + 348, p_m_fActionAssignParam + 153, 0x30u);
        v4[705] = *((_BYTE *)p_m_fActionAssignParam + 660);
        v4[700] = *((_BYTE *)p_m_fActionAssignParam + 661);
        v4[701] = *((_BYTE *)p_m_fActionAssignParam + 662);
        v4[704] = *((_BYTE *)p_m_fActionAssignParam + 665);
        v4[702] = *((_BYTE *)p_m_fActionAssignParam + 663);
        v4[703] = *((_BYTE *)p_m_fActionAssignParam + 664);
      }
LABEL_29:
      this = v11;
      goto LABEL_30;
    }
    *(v4 - 105) = 0;
    if ( v1 > 4 && v1 < 11 )
      *((_DWORD *)v4 + 113) = v1 - 4;
    if ( *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 112) + v2) )
    {
      *(v4 - 107) = 1;
      *(v4 - 106) = 1;
      *((_DWORD *)v4 - 32) = v1;
      *((_DWORD *)v4 - 33) = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1)
                                                   + 112)
                                       + v2);
      *((_DWORD *)v4 + 177) = -1;
      if ( *((_DWORD *)v4 - 33) == 708 )
        LOBYTE(this->m_Role[5].fRecoverItemPowerInc) = 1;
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)v4 - 33));
      v6 = v5;
      *(v4 - 104) = 0;
      v7 = *(_BYTE *)(v5 + 518);
      if ( v7 == 98 || v7 == 66 )
      {
        *(v4 - 104) = 1;
        v4[483] = 1;
        *((_WORD *)v4 + 295) = 0x7FFF;
      }
      if ( *(_BYTE *)(v6 + 709) )
      {
        v4[483] = 1;
        *((_WORD *)v4 + 295) = 0x7FFF;
      }
      v8 = 0;
      *((_DWORD *)v4 - 23) = *(_DWORD *)(v6 + 636);
      *((_DWORD *)v4 - 21) = *(_DWORD *)(v6 + 640);
      *((_DWORD *)v4 - 19) = *(_DWORD *)(v6 + 644);
      *((_DWORD *)v4 - 24) = *((_DWORD *)v4 - 23);
      *((_DWORD *)v4 - 22) = *((_DWORD *)v4 - 21);
      *((_DWORD *)v4 - 20) = *((_DWORD *)v4 - 19);
      *((_DWORD *)v4 - 25) = *(_DWORD *)(v6 + 632);
      *((_DWORD *)v4 - 18) = *(_DWORD *)(v6 + 648);
      *((_DWORD *)v4 - 17) = *(_DWORD *)(v6 + 652);
      *((_DWORD *)v4 - 16) = *(_DWORD *)(v6 + 656);
      *((_DWORD *)v4 - 15) = *(_DWORD *)(v6 + 660);
      *((_DWORD *)v4 + 5) = *(_DWORD *)(v6 + 740);
      *((_DWORD *)v4 - 11) = *(_DWORD *)(v6 + 748);
      *((_DWORD *)v4 - 10) = *(_DWORD *)(v6 + 780);
      *((_DWORD *)v4 + 103) = *(__int16 *)(v6 + 842);
      *((_DWORD *)v4 + 104) = *(_DWORD *)(v6 + 844);
      *((_DWORD *)v4 + 105) = *(__int16 *)(v6 + 848);
      *((_DWORD *)v4 + 102) = 0;
      v4[746] = *(float *)(v6 + 796) <= 0.0;
      *((_DWORD *)v4 + 188) = (__int64)*(float *)(v6 + 724);
      v4[748] = 0;
      v4[747] = 0;
      v9 = *((_DWORD *)v4 - 24);
      if ( v9 >= 1000 )
      {
        if ( v9 >= 10000 )
        {
          if ( v9 >= 100000 )
            *((_DWORD *)v4 + 189) = &g_EffMgr;
          else
            *((_DWORD *)v4 + 189) = &g_EffMgr;
        }
        else
        {
          *((_DWORD *)v4 + 189) = &g_EffMgr;
        }
      }
      else
      {
        *((_DWORD *)v4 + 189) = &g_EffMgr;
      }
      do
      {
        if ( *(_BYTE *)(v6 + v8 + 684) )
          ((CCBRoleState *)v11)->ProcessRound(dwVal);
        ++v8;
      }
      while ( v8 < 23 );
      v2 = v13;
      v1 = dwVal;
      goto LABEL_29;
    }
LABEL_30:
    v2 += 4;
    ++v1;
    p_m_fActionAssignParam += 352;
    v4 += 892;
    dwVal = v1;
    v13 = v2;
  }
  while ( v2 < 24 );
  result = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 112) + 76);
  if ( result != -1 )
    this->m_Role[0].bMagicMastered[6][892 * result + 4] = 1;
  return result;
}

// 0x004ED680
char CCBRoleState::SavePartyData()
{
  CCBRoleState *v1; // edi
  int *v2; // esi
  char *v3; // ebp
  _DWORD *v4; // ebx
  int v5; // esi
  int *v6; // edi
  char result; // al
  int *v8; // [esp+0x10] [ebp-0x8]
v2 = g_nRoleInitLevel;
  v8 = g_nRoleInitLevel;
  v3 = &Buffer.m_partyActor.m_szTexture[4];
  v4 = (_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[8][5] + 1);
  do
  {
    if ( *((_BYTE *)v4 - 127) )
    {
      *((_DWORD *)v3 + 27) = *v4;
      *(_DWORD *)v3 = *(v4 - 30);
      *((_DWORD *)v3 + 85) = *(v4 - 29);
      *((_DWORD *)v3 + 86) = *(v4 - 27);
      *((_DWORD *)v3 + 87) = *(v4 - 25);
      *((_DWORD *)v3 + 88) = *(v4 - 23);
      *((_DWORD *)v3 + 89) = *(v4 - 22);
      *((_DWORD *)v3 + 90) = *(v4 - 21);
      *((_DWORD *)v3 + 91) = *(v4 - 20);
      ((RoleSystem *)(v3 - 632))->RecalcAggregatedStats(0);
      *v2 = *(v4 - 19);
      qmemcpy(v3 + 400, v4 + 2, 0x1Eu);
      qmemcpy(v3 + 432, v4 + 10, 0xC0u);
      qmemcpy(v3 + 624, v4 + 58, 0x30u);
      qmemcpy(v3 + 672, v4 + 70, 0x30u);
      qmemcpy(v3 + 720, v4 + 82, 0x30u);
v2 = v8;
      *((_DWORD *)v3 + 99) = v4[96];
    }
    ++v2;
    v4 += 223;
    v3 += 1408;
    v8 = v2;
  }
  while ( (int)v2 < (int)&g_nRoleInitLevel[5] );
  ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom = ((CCBRoleState *)v1)->GetTotalRounds();
  ((CCBRoleState *)v1)->UpdateDefenceStats();
  v5 = 0;
  v6 = (int *)&this->m_Role[0].bMagicMastered[7][3];
  do
  {
    result = *((_BYTE *)v6 - 11);
    if ( result && v5 >= 5 && *v6 <= 0 )
      result = ((NPC *)&((RoleSystem *)&stru_C059A0)->m_fMoveTargetY)->ShiftBufferData(*(v6 - 9));
    ++v5;
    v6 += 223;
  }
  while ( v5 < 11 );
  return result;
}

// 0x004ED800
char * CCBRoleState::UpdateDefenceStats()
{
  char *result; // eax
  char *v2; // ecx

  result = (char *)&Buffer.m_fCachePosZ;
  v2 = (char *)&this->m_Role[1].dwMagicID[8][4] + 1;
  do
  {
    if ( *(v2 - 559) )
    {
      result[6] = *v2;
      *result = v2[253];
      result[1] = v2[248];
      result[2] = v2[249];
      result[5] = v2[252];
      result[3] = v2[250];
      result[4] = v2[251];
    }
    result += 1408;
    v2 += 892;
  }
  while ( (int)result < (int)&((RoleSystem *)&stru_C059A0)->m_StaticSlotArray.m_benable );
  return result;
}

// 0x004ED870
char CCBRoleState::SyncSkillCent()
{
  int v2; // ebx
  char *v3; // edi
  _DWORD *v4; // esi
  int v5; // eax

  v2 = 0;
  v3 = &Buffer.m_partyActor.m_curact[39];
  v4 = &this->m_Role[0].bMagicMastered[7][3];
  do
  {
    LOBYTE(v5) = *((_BYTE *)v4 - 11);
    if ( (_BYTE)v5 )
    {
      if ( (int)*v4 <= 0 )
      {
        *v4 = 1;
        this->CanUseSkill(v2);
      }
      v5 = *v4;
      *(_DWORD *)v3 = *v4;
    }
    v3 += 1408;
    ++v2;
    v4 += 223;
  }
  while ( (int)v3 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[220] );
  return v5;
}

// 0x004EDC60
int CCBRoleState::RollInitiative()
{
  int v1; // eax
  int result; // eax

  v1 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
  *(_WORD *)((char *)&this->m_Role[0].dwMagicID[8][4] + 1) = 0;
  result = *(_DWORD *)(v1 + 112);
  if ( !*(_BYTE *)(result + 80) )
  {
    result = *(_DWORD *)(result + 68);
    if ( result == 1 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      result = ((int)unk_5DFDEC >> 16) & 0x3FF;
      if ( result < (int)512.0 )
        BYTE2(this->m_Role[0].dwMagicID[8][4]) = 1;
    }
    else if ( result == 2 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      result = ((int)unk_5DFDEC >> 16) & 0x3FF;
      if ( result < (int)512.0 )
        BYTE1(this->m_Role[0].dwMagicID[8][4]) = 1;
    }
  }
  return result;
}

// 0x004EDD60
CCBRoleState::CCBRoleState()
{
  int *v1; // ebp
  unsigned int *v2; // esi
  char *v3; // ebx
  int v4; // eax
  char *v5; // ecx
  int v6; // eax
  char *v7; // ecx
  int v8; // edx
  int v9; // eax
  char *v10; // ecx
  int v11; // edx
  int v12; // eax
  char *v13; // ecx
  int v14; // edx
  int v15; // eax
  char *v16; // ecx
  int v17; // edx
  int v18; // eax
  char *v19; // ecx
  int v20; // edx
  int v21; // edi
  int v22; // eax
  int v23; // ebp
  int v24; // eax
  int v25; // ecx
  int *v26; // [esp+0x10] [ebp-0x8]
  char *v27; // [esp+0x14] [ebp-0x4]

  v1 = (int *)((char *)&this->m_Role[1].dwMagicID[7][4] + 1);
  v2 = &Buffer.m_partyActor.m_dwMatMsg[8];
  v27 = (char *)&this->m_Role[1].dwMagicID[7][4] + 1;
  do
  {
    v3 = (char *)(v1 - 1);
    if ( *((_BYTE *)v1 - 535) )
    {
      memset(v3, 0, 0x1Cu);
      if ( (int)v2 < (int)&Buffer.m_partyActor.m_dwMatMsg[8] || (int)v2 >= (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[207] )
      {
        v21 = 580;
        v26 = v1;
        do
        {
          ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)v3 - 139));
          v23 = *(_DWORD *)(v22 + v21) << 16;
          ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)v3 - 139));
          v25 = *(_DWORD *)(v24 + v21);
          v21 += 4;
          *v26++ = v25 | v23;
        }
        while ( v21 < 600 );
        v1 = (int *)v27;
      }
      else
      {
        if ( *(v2 - 2) )
        {
          v4 = 0;
          v5 = (char *)v1;
          do
          {
            v5 += 4;
            *((_DWORD *)v5 - 1) = *(unsigned __int8 *)(*v2 + v4++ + 619) << 16;
          }
          while ( v4 < 5 );
        }
        if ( *(v2 - 17) )
        {
          v6 = 0;
          v7 = (char *)v1;
          do
          {
            v7 += 4;
            v8 = *(unsigned __int8 *)(*(v2 - 15) + v6++ + 619) + *((_DWORD *)v7 - 1);
            *((_DWORD *)v7 - 1) = v8;
          }
          while ( v6 < 5 );
        }
        if ( *(v2 - 14) )
        {
          v9 = 0;
          v10 = (char *)v1;
          do
          {
            v10 += 4;
            v11 = *(unsigned __int8 *)(*(v2 - 12) + v9++ + 619) + *((_DWORD *)v10 - 1);
            *((_DWORD *)v10 - 1) = v11;
          }
          while ( v9 < 5 );
        }
        if ( *(v2 - 11) )
        {
          v12 = 0;
          v13 = (char *)v1;
          do
          {
            v13 += 4;
            v14 = *(unsigned __int8 *)(v12 + *(v2 - 9) + 619) + *((_DWORD *)v13 - 1);
            ++v12;
            *((_DWORD *)v13 - 1) = v14;
          }
          while ( v12 < 5 );
        }
        if ( *(v2 - 8) )
        {
          v15 = 0;
          v16 = (char *)v1;
          do
          {
            v16 += 4;
            v17 = *(unsigned __int8 *)(*(v2 - 6) + v15++ + 619) + *((_DWORD *)v16 - 1);
            *((_DWORD *)v16 - 1) = v17;
          }
          while ( v15 < 5 );
        }
        if ( *(v2 - 5) )
        {
          v18 = 0;
          v19 = (char *)v1;
          do
          {
            v19 += 4;
            v20 = *(unsigned __int8 *)(*(v2 - 3) + v18++ + 619) + *((_DWORD *)v19 - 1);
            *((_DWORD *)v19 - 1) = v20;
          }
          while ( v18 < 5 );
        }
      }
    }
    v2 += 352;
    v1 += 223;
    v27 = (char *)v1;
  }
  while ( (int)v2 < (int)&((RoleSystem *)&stru_C08160)->m_partyActor.m_fMatrixParamC );
}

// 0x004EDF10
char CCBRoleState::UpdateRolePositions()
{
  int v2; // ebp
  void **v3; // edi
  float *v4; // esi
  char result; // al

  v2 = 0;
  v3 = &Buffer.m_partyActor.m_pParticleData + 3;
  v4 = (float *)((char *)&this->m_Role[0].byMagicUseTime[4][5] + 1);
  do
  {
    result = *((_BYTE *)v4 - 79);
    if ( result )
    {
      if ( *(v3 - 5) )
      {
        *v4 = (double)*((__int16 *)*(v3 - 3) + 384) + *v4;
        v4[1] = (double)*((__int16 *)*(v3 - 3) + 385) + v4[1];
        v4[3] = (double)*((__int16 *)*(v3 - 3) + 387) + v4[3];
        v4[2] = (double)*((__int16 *)*(v3 - 3) + 386) + v4[2];
        v4[4] = (double)*((__int16 *)*(v3 - 3) + 322) + v4[4];
        v4[5] = (double)*((__int16 *)*(v3 - 3) + 323) + v4[5];
        v4[6] = (double)*((__int16 *)*(v3 - 3) + 324) + v4[6];
        if ( *((_WORD *)*(v3 - 3) + 375) )
        {
          *((_BYTE *)v4 + 511) = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (char *)*((unsigned __int8 *)*(v3 - 3) + 628));
      }
      if ( *(v3 - 2) )
      {
        *v4 = (double)*((__int16 *)*v3 + 384) + *v4;
        v4[1] = (double)*((__int16 *)*v3 + 385) + v4[1];
        v4[3] = (double)*((__int16 *)*v3 + 387) + v4[3];
        v4[2] = (double)*((__int16 *)*v3 + 386) + v4[2];
        v4[4] = (double)*((__int16 *)*v3 + 322) + v4[4];
        v4[5] = (double)*((__int16 *)*v3 + 323) + v4[5];
        v4[6] = (double)*((__int16 *)*v3 + 324) + v4[6];
        if ( *((_WORD *)*v3 + 375) )
        {
          *((_BYTE *)v4 + 511) = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (char *)*((unsigned __int8 *)*v3 + 628));
      }
      if ( v3[1] )
      {
        *v4 = (double)*((__int16 *)v3[3] + 384) + *v4;
        v4[1] = (double)*((__int16 *)v3[3] + 385) + v4[1];
        v4[3] = (double)*((__int16 *)v3[3] + 387) + v4[3];
        v4[2] = (double)*((__int16 *)v3[3] + 386) + v4[2];
        v4[4] = (double)*((__int16 *)v3[3] + 322) + v4[4];
        v4[5] = (double)*((__int16 *)v3[3] + 323) + v4[5];
        v4[6] = (double)*((__int16 *)v3[3] + 324) + v4[6];
        if ( *((_WORD *)v3[3] + 375) )
        {
          *((_BYTE *)v4 + 511) = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (char *)*((unsigned __int8 *)v3[3] + 628));
      }
      if ( v3[4] )
      {
        *v4 = (double)*((__int16 *)v3[6] + 384) + *v4;
        v4[1] = (double)*((__int16 *)v3[6] + 385) + v4[1];
        v4[3] = (double)*((__int16 *)v3[6] + 387) + v4[3];
        v4[2] = (double)*((__int16 *)v3[6] + 386) + v4[2];
        v4[4] = (double)*((__int16 *)v3[6] + 322) + v4[4];
        v4[5] = (double)*((__int16 *)v3[6] + 323) + v4[5];
        v4[6] = (double)*((__int16 *)v3[6] + 324) + v4[6];
        if ( *((_WORD *)v3[6] + 375) )
        {
          *((_BYTE *)v4 + 511) = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (char *)*((unsigned __int8 *)v3[6] + 628));
      }
      if ( v3[7] )
      {
        *v4 = (double)*((__int16 *)v3[9] + 384) + *v4;
        v4[1] = (double)*((__int16 *)v3[9] + 385) + v4[1];
        v4[3] = (double)*((__int16 *)v3[9] + 387) + v4[3];
        v4[2] = (double)*((__int16 *)v3[9] + 386) + v4[2];
        v4[4] = (double)*((__int16 *)v3[9] + 322) + v4[4];
        v4[5] = (double)*((__int16 *)v3[9] + 323) + v4[5];
        v4[6] = (double)*((__int16 *)v3[9] + 324) + v4[6];
        if ( *((_WORD *)v3[9] + 375) )
        {
          *((_BYTE *)v4 + 511) = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (char *)*((unsigned __int8 *)v3[9] + 628));
      }
      if ( *(v3 - 5) == (void *)80015 )
      {
        if ( *(v3 - 2) == (void *)84018 && v3[1] == (void *)83012 && v3[4] == (void *)8153 && v3[7] == (void *)8154 )
          *((_BYTE *)v4 + 44) = 1;
        if ( *(v3 - 5) == (void *)80015
          && *(v3 - 2) == (void *)84018
          && v3[1] == (void *)83012
          && v3[4] == (void *)8154
          && v3[7] == (void *)8153 )
        {
          *((_BYTE *)v4 + 44) = 1;
        }
      }
      result = -82;
      if ( v3[4] == (void *)8110 || v3[7] == (void *)8110 )
        *((_BYTE *)v4 + 45) = 1;
    }
    v3 += 352;
    ++v2;
    v4 += 223;
  }
  while ( (int)v3 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[195] );
  return result;
}

// 0x004EE430
char * CCBRoleState::Reset(int nVal, char *pszBuf)
{
  char *result; // eax
  float *v4; // edx

  switch ( (unsigned int)pszBuf )
  {
    case 0x14u:
      result = (char *)&this->m_Role[0].byMagicUseTime[7][446 * nVal + 1] + 1;
      *(float *)result = *(float *)result + 5.0;
      break;
    case 0x15u:
      v4 = (float *)&this->m_sCombatDialog[892 * nVal];
      v4[171] = v4[171] + 15.0;
      v4[172] = v4[172] + 5.0;
      goto LABEL_4;
    case 0x16u:
LABEL_4:
      result = (char *)&this->m_Role[0].byMagicUseTime[7][446 * nVal + 5] + 1;
      *(float *)result = *(float *)result + 10.0;
      break;
    case 0x17u:
      result = (char *)&this->m_Role[0].byMagicUseTime[8][446 * nVal + 1] + 1;
      *(_DWORD *)result += 5;
      break;
    case 0x18u:
      result = (char *)&this->m_Role[0].byMagicUseTime[7][446 * nVal + 1] + 1;
      *(float *)result = *(float *)result + 20.0;
      break;
    default:
      result = pszBuf;
      break;
  }
  return result;
}

// 0x004EE540
bool CCBRoleState::Create()
{
  unsigned int *v1; // ebp
  gbGeomNode **v2; // edi
  int v3; // eax
  gbGeomNode *v4; // eax
  gbGeomNode *v5; // esi
  gbGeomNode *v6; // ecx
  gbGeomNode *v7; // eax
  gbGeomNode *v8; // esi
  gbGeomNode *v9; // ecx
  char Buffer[256]; // [esp+0x14] [ebp-0x120C] BYREF
  char v12[256]; // [esp+0x114] [ebp-0x110C] BYREF
  _BYTE pExceptionObject[1024]; // [esp+0x214] [ebp-0x100C] BYREF
  char v14[1024]; // [esp+0x614] [ebp-C0Ch] BYREF
  char ArgList; // [esp+A14h] [ebp-0x80C] BYREF
  char v16; // [esp+E14h] [ebp-0x40C] BYREF
  int v17; // [esp+0x121C] [ebp-0x4]

  v1 = &::Buffer.m_partyActor.m_dwMatMsg[8];
  v2 = (gbGeomNode **)((char *)&this->m_Role[2].nProtectRole + 1);
  do
  {
    LOBYTE(v3) = *((_BYTE *)v2 - 823);
    if ( (_BYTE)v3 )
    {
      v3 = *(v1 - 2);
      if ( v3 )
      {
        sprintf(Buffer, "weapon\\%s\\%s.pol", (const char *)(*v1 + 36), (const char *)(*v1 + 36));
        sprintf(
          v12,
          "weapon\\%s\\%s%s.tga",
          (const char *)(*v1 + 36),
          (const char *)(*v1 + 36),
          (const char *)(*v1 + 66));
        v4 = (gbGeomNode *)operator new(0x118u);
        v5 = v4;
        v17 = 0;
        if ( v4 )
        {
          v6 = v5;
        }
        else
        {
          v6 = 0;
        }
        v17 = -1;
        *v2 = v6;
        if ( !v6 )
        {
          qmemcpy(
            pExceptionObject,
            ((Logger *)&ArgList)->FormatException(aFailToCreateWe, aDProjectPal3Co_1, 1484),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        ((gbGeomNode *)v6)->LoadFromFile(Buffer, 0, 0);
        ((gbGeomNode *)*v2)->ReplaceTexture(v12);
        v7 = (gbGeomNode *)operator new(0x118u);
        v8 = v7;
        v17 = 1;
        if ( v7 )
        {
          v9 = v8;
        }
        else
        {
          v9 = 0;
        }
        v17 = -1;
        v2[3] = v9;
        if ( !v9 )
        {
          qmemcpy(v14, ((Logger *)&v16)->FormatException(aFailToCreateWe, aDProjectPal3Co_1, 1494), sizeof(v14));
          _CxxThrowException(v14, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        ((gbGeomNode *)v9)->LoadFromFile(Buffer, 0, 0);
        ((gbGeomNode *)v2[3])->ReplaceTexture(v12);
        LOBYTE(v3) = 1;
        (*v2)->bBlade = 1;
        v2[3]->bBlade = 1;
      }
    }
    v1 += 352;
    v2 += 223;
  }
  while ( (int)v1 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[207] );
  return v3;
}

// 0x004EE760
bool CCBRoleState::Destroy()
{
  _BYTE *p_bAttackRow; // ebp
  _DWORD *v2; // esi
  int v3; // edi
  void ( ***v4)(_DWORD, int); // ecx
  bool result; // al
  int v6; // [esp+0x10] [ebp-0x4]

  p_bAttackRow = &this->m_Role[2].bAttackRow;
  v6 = 5;
  do
  {
    v2 = p_bAttackRow;
    v3 = 3;
    do
    {
      v4 = (void ( ***)(_DWORD, int))*(v2 - 3);
      if ( v4 )
      {
        (**v4)(v4, 1);
        *(v2 - 3) = 0;
      }
      if ( *v2 )
      {
        (**(void ( ***)(_DWORD, int))*v2)(*v2, 1);
        *v2 = 0;
      }
      ++v2;
      --v3;
    }
    while ( v3 );
    p_bAttackRow += 892;
    result = --v6;
  }
  while ( v6 );
  return result;
}

// 0x004EE7C0
bool CCBRoleState::Init(int nVal, char pData)
{
  int v3; // esi

  v3 = *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 4);
  if ( pData == 1 )
  {
    if ( !nVal )
      (***(void ( ****)(_DWORD, int))(v3 + 1068))(*(_DWORD *)(v3 + 1068), 1);
    (***(void ( ****)(_DWORD, int))(v3 + 4 * nVal + 120))(*(_DWORD *)(v3 + 4 * nVal + 120), 1);
    (***(void ( ****)(_DWORD, int))(v3 + 4 * nVal + 1020))(*(_DWORD *)(v3 + 4 * nVal + 1020), 1);
    (***(void ( ****)(_DWORD, int))(v3 + 4 * nVal + 1052))(*(_DWORD *)(v3 + 4 * nVal + 1052), 1);
    return (***(bool ( ****)(_DWORD, int))(v3 + 4 * nVal + 1036))(*(_DWORD *)(v3 + 4 * nVal + 1036), 1);
  }
  else
  {
    if ( !nVal )
      (***(void ( ****)(_DWORD, _DWORD))(v3 + 1068))(*(_DWORD *)(v3 + 1068), 0);
    (***(void ( ****)(_DWORD, _DWORD))(v3 + 4 * nVal + 120))(*(_DWORD *)(v3 + 4 * nVal + 120), 0);
    (***(void ( ****)(_DWORD, _DWORD))(v3 + 4 * nVal + 1020))(*(_DWORD *)(v3 + 4 * nVal + 1020), 0);
    (***(void ( ****)(_DWORD, _DWORD))(v3 + 4 * nVal + 1052))(*(_DWORD *)(v3 + 4 * nVal + 1052), 0);
    return (***(bool ( ****)(_DWORD, _DWORD))(v3 + 4 * nVal + 1036))(*(_DWORD *)(v3 + 4 * nVal + 1036), 0);
  }
}

// 0x004EE870
tagRoleState * CCBRoleState::InitUI(int nVal)
{
  return (tagRoleState *)&this->m_Role[0].bMagicMastered[1][892 * nVal + 3];
}

// 0x004EE890
int CCBRoleState::Update(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return 0;
}

// 0x004EE910
int CCBRoleState::CheckMP(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return -1;
}

// 0x004EE990
bool CCBRoleState::VarianceRoundCounter(int *nRoleIndex)
{
  int RoleNum; // eax
  unsigned __int8 v5; // al
  int *nRoleIndexa; // [esp+0x14] [ebp+0x8]
  float nRoleIndexb; // [esp+0x14] [ebp+0x8]

  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nRoleIndex[1]);
  if ( *nRoleIndex == 261 )
    return 1;
  v5 = *(_BYTE *)(RoleNum + 616);
  if ( v5 <= 1u )
  {
    nRoleIndexa = (int *)this->ApplyDamage(1, nRoleIndex[2]);
    if ( (int)nRoleIndexa > 0 )
    {
      nRoleIndexb = (double)(int)nRoleIndexa * 10.24;
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      return (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)nRoleIndexb;
    }
  }
  else if ( v5 == 100 )
  {
    return 1;
  }
  return 0;
}

// 0x004EEA70
void CCBRoleState::CheckVarianceRound(int nRoleIndex, int nVal, int *pnVal)
{
  int v4; // edi
  signed int v5; // esi
  char v6; // bl
  int RoleBySlot; // eax
  int ItemNum; // eax
  int v9; // edi
  _DWORD *v10; // ebp
  int v11; // ecx
  char *v12; // esi
  unsigned __int8 v13; // cl
  bool v14; // zf
  int v15; // edx
  int v16; // ecx
  int *v17; // edi
  int v18; // ebp
  int v19; // esi
  int v20; // eax
  signed int v22; // [esp+0x14] [ebp-0x8]
// [IDA_MISID]   Concurrency::IThreadProxy *Proxy; // [esp+0x18] [ebp-0x4]

  v4 = nRoleIndex;
  if ( nRoleIndex >= 5 && nRoleIndex < 11 )
    return;
  v5 = 0;
// [IDA_MISID]   Proxy = ((Concurrency *)&g_pGDB)->details::InternalContextBase::GetProxy();
  v22 = 0;
  if ( (int)Proxy <= 0 )
    return;
  do
  {
    v6 = 1;
    RoleBySlot = ((UIAnimateCtrl *)&g_pGDB)->GetRoleBySlot(v5);
    *pnVal = RoleBySlot;
    ItemNum = ((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(RoleBySlot);
    if ( *(_DWORD *)(ItemNum + 56) != nVal )
      goto LABEL_53;
    if ( *(_DWORD *)(ItemNum + 36) != *(_DWORD *)&this->m_Role[0].bMagicMastered[1][892 * v4 + 3] )
      goto LABEL_52;
    v9 = 0;
    v10 = (_DWORD *)(ItemNum + 36);
    do
    {
      if ( !*v10 )
        goto LABEL_33;
      v11 = -1;
      switch ( *v10 )
      {
        case 'e':
          v11 = 0;
          break;
        case 'f':
          v11 = 4;
          break;
        case 'h':
          v11 = 1;
          break;
        case 'i':
        case 'j':
          v11 = 2;
          break;
        case 'k':
          v11 = 3;
          break;
        default:
          break;
      }
      v12 = &this->m_sCombatDialog[892 * v11];
      if ( !v12[577] )
        v6 = 0;
      v13 = *(_BYTE *)(ItemNum + v9 + 52);
      if ( v13 )
      {
        v14 = v13 == 7;
        if ( v13 >= 7u )
          goto LABEL_21;
        if ( v13 != v12[1136] )
          v6 = 0;
      }
      v14 = v13 == 7;
LABEL_21:
      if ( v14 )
      {
        v15 = *((_DWORD *)v12 + 284);
        if ( v15 != 3 && v15 != 2 && v15 != 4 )
          v6 = 0;
      }
      if ( v13 == 8 )
      {
        v16 = *((_DWORD *)v12 + 284);
        if ( v16 != 1 && v16 != 2 && v16 != 5 )
          v6 = 0;
      }
      if ( *(_BYTE *)(ItemNum + v9 + 60) != v12[648] )
        v6 = 0;
LABEL_33:
      ++v9;
      ++v10;
    }
    while ( v9 < 4 );
    if ( v6 )
    {
      v17 = (int *)(ItemNum + 68);
      v18 = 3;
      do
      {
        switch ( *(v17 - 7) )
        {
          case 'e':
            v19 = 0;
            goto LABEL_42;
          case 'f':
            v19 = 4;
            goto LABEL_42;
          case 'h':
            v19 = 1;
            goto LABEL_42;
          case 'i':
          case 'j':
            v19 = 2;
            goto LABEL_42;
          case 'k':
            v19 = 3;
LABEL_42:
            v20 = *v17;
            if ( *v17 >= 0 && v20 < 26 && !this->GetRoleField(v19, v20 + 1) )
              v6 = 0;
            if ( *v17 == 26 && !this->IsRoleInForce(v19) )
              v6 = 0;
            break;
          default:
            break;
        }
        ++v17;
        --v18;
      }
      while ( v18 );
      if ( v6 )
        break;
    }
    v5 = v22;
LABEL_52:
    v4 = nRoleIndex;
LABEL_53:
    v22 = ++v5;
  }
  while ( v5 < (int)Proxy );
}

// 0x004EECB0
void CCBRoleState::CancelVariance(int *nRoleIndex, unsigned int dwVal)
{
  char *v3; // eax

  if ( dwVal <= 0xA )
  {
    v3 = &this->m_sCombatDialog[892 * dwVal];
    if ( v3[577] )
    {
      if ( v3[578] && !v3[1432] && !v3[1431] && (v3[1164] != 1 || nRoleIndex[1] == 4401) && *nRoleIndex == 259 )
        this->CalSneakAttack(nRoleIndex[2], dwVal);
    }
  }
}

// 0x004EED60
char CCBRoleState::ForceRoleTaskByCond(int roleIdx)
{
  int v3; // eax
  char result; // al
  int v5; // esi
  int v6; // esi

  v3 = *(_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[3][1] + 1);
  if ( !v3 )
    return 0;
  if ( v3 != roleIdx )
    return 0;
  result = this->IsRoleAlive(0);
  if ( result )
  {
    v5 = this->SetRoleField(0, 1) / 2;
    if ( this->SetRoleField(0, 0) >= v5 )
    {
      v6 = this->SetRoleField(roleIdx, 1) / 10;
      if ( this->SetRoleField(roleIdx, 0) <= v6 )
      {
        if ( *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][4] + 1) == 6 )
        {
          result = ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                          + 1)
                                                                    + 24))->ForceDelTaskByPFN();
          if ( result )
          {
            result = ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                            + 1)
                                                                      + 24))->ForceEndTaskByPFN();
            if ( result )
              return ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                            + 1)
                                                                      + 4 * roleIdx
                                                                      + 24))->ForceEndTaskByPFN();
          }
        }
        else
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004EEE60
char CCBRoleState::IsAlive(int nIndex, int nVal)
{
  char result; // al
  int v5; // eax

  if ( !this->m_Role[0].bMagicMastered[5][4] )
    return 0;
  v5 = *(_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[3][1] + 1);
  if ( !v5 )
    return 0;
  if ( v5 != nIndex )
    return 0;
  result = this->IsRoleAlive(0);
  if ( result )
  {
    if ( *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][4] + 1) == 6 )
    {
      if ( this->GetRoleField(0, 14) )
      {
        return 0;
      }
      else
      {
        result = ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 24))->EndTask(nIndex, nVal);
        if ( result )
        {
          result = ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                          + 1)
                                                                    + 4 * nIndex
                                                                    + 24))->ForceEndTaskByPFN();
          if ( result )
            return ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->ForceDelTask(18);
        }
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004EEF20
int CCBRoleState::CalcCombatDamage(const void *pData, unsigned int roleIdx)
{
  int v3; // ebx
  CCBRoleState *v4; // ecx
  int v6; // edi
  CCBRoleState *v7; // kr10_4
  int v8; // eax
  __int16 v9; // ax
  int v10; // edx
  __int16 v11; // ax
  int v12; // eax
  __int16 v13; // ax
  CCBRoleState **v14; // eax
  int v15; // ebx
  CScreenMode *Instance; // eax
  char *v18; // [esp+0x4] [ebp-0x58]
  int nCmdData[11]; // [esp+0xC] [ebp-0x50] BYREF
  int v20; // [esp+0x38] [ebp-0x24]
  int v21; // [esp+0x3C] [ebp-0x20]
  int SkillNum; // [esp+0x40] [ebp-0x1C]
  int ItemNum; // [esp+0x44] [ebp-0x18]
  int RoleNum; // [esp+0x48] [ebp-0x14]
  char v25[4]; // [esp+0x4C] [ebp-0x10]
  int v26; // [esp+0x50] [ebp-0xC]
  CCBRoleState *v27; // [esp+0x54] [ebp-0x8]
  char v28; // [esp+0x5B] [ebp-0x1]
  char pData_3; // [esp+0x67] [ebp+0xB]
  float roleIdxb; // [esp+0x68] [ebp+0xC]
  signed int roleIdxa; // [esp+0x68] [ebp+0xC]
  float roleIdxc; // [esp+0x68] [ebp+0xC]
v3 = 0;
  qmemcpy(nCmdData, pData, sizeof(nCmdData));
  v26 = 0;
  *(_DWORD *)v25 = 0;
  RoleNum = 0;
  SkillNum = 0;
  ItemNum = 0;
  switch ( nCmdData[0] )
  {
    case 0x104:
    case 0x105:
    case 0x10D:
      RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nCmdData[1]);
      break;
    case 0x106:
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nCmdData[1]);
      break;
    case 0x10E:
      ItemNum = ((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(nCmdData[1]);
      break;
    default:
      v4 = 0;
      break;
  }
  v28 = 0;
  pData_3 = 0;
  v6 = 0;
  while ( 2 )
  {
    v7 = v4;
    v4 = 0;
    switch ( nCmdData[0] )
    {
      case 0x104:
        v9 = *(_WORD *)(RoleNum + 2 * v6 + 592);
        if ( v9 )
        {
          v3 = v9;
          if ( (int)roleIdx >= 5 && (int)roleIdx < 11 )
          {
            if ( unk_5DFDEB )
            {
              roleIdxb = (double)v9 * 0.1;
              v21 = (int)roleIdxb;
              roleIdxa = abs32(v21);
              if ( roleIdxa )
              {
                v10 = (((int)(214013 * unk_5DFDEC + 2531011) >> 16) & 0x7FFF) % roleIdxa;
                *(_DWORD *)&g_TempBuffer1024[912] += 2;
                unk_5DFDEC = 214013 * (214013 * unk_5DFDEC + 2531011) + 2531011;
                v4 = (CCBRoleState *)(((int)unk_5DFDEC >> 16) & 0x3FF);
                if ( (unsigned int)v4 < 0x200 )
                  v3 = v9 - v10;
                else
                  v3 = v10 + v9;
              }
            }
          }
          if ( !BYTE1(nCmdData[4]) && roleIdx <= 4 )
            *(_DWORD *)v25 = 1;
          if ( nCmdData[1] == 4102 )
          {
            v4 = v27;
            v3 = 2 * *(_DWORD *)&this->m_Role[0].bMagicMastered[6][5] + 40;
          }
          goto LABEL_36;
        }
        goto LABEL_67;
      case 0x105:
        if ( *(_WORD *)(RoleNum + 2 * v6 + 592) )
        {
          v8 = ((CCBRoleState *)v27)->ApplyDamage(2, nCmdData[2]);
          v4 = (CCBRoleState *)RoleNum;
          v3 = v8;
          *(_DWORD *)v25 = *(unsigned __int8 *)(RoleNum + v6 + 579);
          goto LABEL_36;
        }
        goto LABEL_67;
      case 0x106:
        v4 = (CCBRoleState *)SkillNum;
        v13 = *(_WORD *)(SkillNum + 2 * v6 + 644);
        if ( v13 )
        {
          v3 = v13;
          if ( v13 > 0 && nCmdData[2] <= 4u )
          {
            roleIdxc = (double)v13
                     * *(float *)((char *)&this->m_Role[0].byMagicUseTime[7][446 * nCmdData[2] + 5] + 1)
                     * 0.0099999998;
            v20 = (int)roleIdxc;
            v3 = v20 + v13;
          }
          *(_DWORD *)v25 = *(unsigned __int8 *)(SkillNum + v6 + 631);
          goto LABEL_36;
        }
        goto LABEL_67;
      case 0x10D:
        v11 = *(_WORD *)(RoleNum + 2 * v6 + 592);
        if ( v11 )
        {
          if ( roleIdx <= 4 )
            *(_DWORD *)v25 = 1;
          v3 = v11;
          if ( nCmdData[1] == 2224 )
            v3 = (__int64)(((double)dword_C10CC4 * 0.5 + 1.0) * (double)v11);
          goto LABEL_36;
        }
        goto LABEL_67;
      case 0x10E:
        v4 = (CCBRoleState *)ItemNum;
        if ( *(_WORD *)(ItemNum + 2 * v6 + 606) )
        {
          v12 = ((CCBRoleState *)v27)->ApplyItemEffect((int)nCmdData, roleIdx);
          v4 = (CCBRoleState *)ItemNum;
          if ( *(__int16 *)(ItemNum + 2 * v6 + 606) <= 0 )
            v3 = (v12 >> 31) - ((v12 >> 31) ^ v12);
          else
            v3 = abs32(v12);
          goto LABEL_36;
        }
        goto LABEL_67;
      default:
        v4 = v7;
LABEL_36:
        if ( v6 )
        {
          if ( v6 == 1 )
          {
            if ( *(_DWORD *)v25 > 2u )
              goto LABEL_67;
            if ( *(_DWORD *)v25 == 1 )
            {
              ((CCBRoleState *)v27)->GetRoleGPBak(roleIdx, 1);
              v3 = ((CCBRoleState *)v27)->CalcAttackPower(roleIdx);
            }
            else
            {
              if ( *(_DWORD *)v25 == 2 )
              {
                ((CCBRoleState *)v27)->GetRoleGPBak(roleIdx, 1);
                ((CCBRoleState *)v27)->GetRoleGPBak(roleIdx, 0);
              }
              v3 = ((CCBRoleState *)v27)->CalcAttackPower(roleIdx);
            }
            goto LABEL_66;
          }
          if ( v6 != 2 )
          {
            ((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1))->CreateObj(&dword_5D8E98, 0, 0x40u);
            goto LABEL_67;
          }
          if ( *(int *)v25 >= 0 )
          {
            if ( *(int *)v25 <= 2 )
            {
              if ( *(_DWORD *)v25 == 1 )
              {
                ((CCBRoleState *)v27)->GetRole(roleIdx);
              }
              else if ( *(_DWORD *)v25 == 2 )
              {
                ((CCBRoleState *)v27)->GetRole(roleIdx);
                ((CCBRoleState *)v27)->GetRole(roleIdx);
              }
              v3 = ((CCBRoleState *)v27)->CalcDefensePower(roleIdx);
              if ( v3 > 0 )
                pData_3 = 1;
LABEL_66:
              v26 = v3;
              goto LABEL_67;
            }
            if ( *(_DWORD *)v25 == 3 )
            {
              v14 = (CCBRoleState **)((char *)&this->m_Role[0].byMagicUseTime[0][446 * roleIdx + 5] + 1);
              v4 = (CCBRoleState *)((char *)*v14 + v3);
              *v14 = v4;
            }
          }
        }
        else
        {
          if ( *(int *)v25 < 0 )
            goto LABEL_67;
          if ( *(int *)v25 <= 2 )
          {
            if ( *(_DWORD *)v25 == 1 )
            {
              v3 = v3 * ((CCBRoleState *)v27)->SetRoleField(roleIdx, 1) / 100;
            }
            else if ( *(_DWORD *)v25 == 2 )
            {
              v15 = ((CCBRoleState *)v27)->SetRoleField(roleIdx, 1);
              v3 = v15 - ((CCBRoleState *)v27)->SetRoleField(roleIdx, 0);
            }
            v3 = ((CCBSystem *)v27)->AddCommand(roleIdx, v3, 1);
            if ( v3 > 0 )
              v28 = 1;
            goto LABEL_66;
          }
          if ( *(_DWORD *)v25 == 3 )
          {
            v26 = 0;
            v4 = (CCBRoleState *)(v3 + *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * roleIdx + 1]);
            *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * roleIdx + 1] = v4;
          }
        }
LABEL_67:
        if ( ++v6 < 12 )
          continue;
        if ( v28 )
        {
          if ( pData_3 )
            v18 = "wd003";
          else
            v18 = "wd001";
LABEL_74:
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v18, 1);
        }
        else if ( pData_3 )
        {
          v18 = "wd002";
          goto LABEL_74;
        }
        return v26;
    }
  }
}

// 0x004EF4A0
void CCBRoleState::IsBoss(int *arg0, unsigned int nRoleIndex)
{
  int RoleNum; // edi
  int SkillNum; // ebp
  int v5; // esi
  __int16 *v6; // ebx
  __int16 *v7; // ebp
  int v8; // eax
  int v9; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v11; // eax
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  char v17; // [esp+0x12] [ebp-0xA]
  char v18; // [esp+0x13] [ebp-0x9]
  char v19; // [esp+0x14] [ebp-0x8]
  char v20; // [esp+0x15] [ebp-0x7]
  char v21; // [esp+0x16] [ebp-0x6]
  char v22; // [esp+0x17] [ebp-0x5]

  RoleNum = 0;
  SkillNum = 0;
  if ( *arg0 == 262 )
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(arg0[1]);
  else
    RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(arg0[1]);
  v5 = 0;
  v6 = (__int16 *)(RoleNum + 618);
  v22 = 0;
  v17 = 0;
  v18 = 0;
  v19 = 0;
  v20 = 0;
  v21 = 0;
  v7 = (__int16 *)(SkillNum + 700);
  do
  {
    if ( *arg0 == 262 )
      v8 = *v7;
    else
      v8 = *v6;
    v9 = v8 - 1;
    if ( v9 )
    {
      if ( v9 == 1 )
      {
        this->ProcessRound(nRoleIndex);
        switch ( v5 )
        {
          case 13:
            v22 = 1;
            break;
          case 14:
            v17 = 1;
            break;
          case 15:
            v18 = 1;
            break;
          case 16:
            v19 = 1;
            break;
          case 17:
            v21 = 1;
            break;
          case 18:
            v20 = 1;
            break;
          default:
            break;
        }
      }
    }
    else
    {
      this->ProcessRound(nRoleIndex);
    }
    ++v5;
    ++v7;
    ++v6;
  }
  while ( v5 < 25 );
  if ( v22 )
  {
    if ( v17 && v18 && v19 && v20 && v21 )
    {
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(&g_EffMgr, 1);
      return;
    }
    v11 = CScreenMode::GetInstance();
    ((CScreenMode *)v11)->AudioSetPosition(&g_EffMgr, 1);
  }
  if ( v17 )
  {
    v12 = CScreenMode::GetInstance();
    ((CScreenMode *)v12)->AudioSetPosition(&g_EffMgr, 1);
  }
  if ( v18 )
  {
    v13 = CScreenMode::GetInstance();
    ((CScreenMode *)v13)->AudioSetPosition(&g_EffMgr, 1);
  }
  if ( v19 )
  {
    v14 = CScreenMode::GetInstance();
    ((CScreenMode *)v14)->AudioSetPosition(&g_EffMgr, 1);
  }
  if ( v20 )
  {
    v15 = CScreenMode::GetInstance();
    ((CScreenMode *)v15)->AudioSetPosition(&g_EffMgr, 1);
  }
  if ( v21 )
  {
    v16 = CScreenMode::GetInstance();
    ((CScreenMode *)v16)->AudioSetPosition(&g_EffMgr, 1);
  }
}

// 0x004EF6A0
bool CCBRoleState::IsAllWeDead(int bCheckHP)
{
  return *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][223 * bCheckHP + 4] + 1);
}

// 0x004EF6C0
int * CCBRoleState::IsAllEnemyDead(int bCheckHP, int *pnVal, int *pnVal2)
{
  int RoleNum; // eax
  int v5; // ecx
  int *result; // eax

  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(bCheckHP);
  v5 = 1;
  result = (int *)(RoleNum + 8);
  *pnVal2 = 0;
  *pnVal = 0;
  do
  {
    if ( *result == 1 )
    {
      if ( *pnVal )
        *pnVal2 = v5;
      else
        *pnVal = v5;
    }
    ++result;
    ++v5;
  }
  while ( v5 - 1 <= 4 );
  return result;
}

// 0x004EF710
bool CCBRoleState::CanAction(int nIndex, int nVal, int nVal2)
{
  int v5; // eax
  _DWORD *i; // ecx
  int v7; // edi
  _DWORD *j; // eax
  int v9; // ebp

  v5 = 1;
  for ( i = (unsigned int *)((char *)&this->m_Role[1].dwMagicID[7][223 * nVal + 4] + 1); !*i; ++i )
  {
    if ( ++v5 >= 6 )
      return 0;
  }
  v7 = 1;
  for ( j = (unsigned int *)((char *)&this->m_Role[1].dwMagicID[7][223 * nIndex + 4] + 1); (*j & 0xFFFF0000) == 0; ++j )
  {
    if ( ++v7 >= 6 )
      return 0;
  }
  v9 = this->CheckDeath(v7);
  return (*(unsigned int *)((char *)&this->m_Role[1].dwMagicID[7][223 * nVal + 3 + v9] + 1) != 0)
       - (*(unsigned int *)((char *)&this->m_Role[1].dwMagicID[7][223 * nVal
                                                                    + 3
                                                                    + this->GetSlotType(v7)]
                              + 1) != 0);
}

// 0x004EF7E0
void CCBRoleState::SetCanAction(unsigned int dmg, int roleIdx, int nVal)
{
  int v5; // eax
  int v6; // ecx

  if ( this->GetRoleField(roleIdx, 21) != 1 && this->GetRoleField(roleIdx, 23) != 1 )
  {
    v5 = this->ApplyDamage(7, dmg);
    if ( dmg <= 4 )
    {
      v6 = *(_DWORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * dmg + 8] + 764);
      if ( v6 > 1 )
        v5 /= v6;
    }
    if ( this->m_Role[1].bMagicMastered[2][892 * dmg + 5] )
      v5 *= 2;
    if ( v5 >= 0 )
    {
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    }
  }
}

// 0x004EF8B0
void CCBRoleState::RandSetEnemyPos(const void *arg0)
{
  struct tagCmdData nVal; // [esp+0x8] [ebp-0x2C] BYREF

  qmemcpy(&nVal, arg0, sizeof(nVal));
  switch ( nVal.dwCmdKind )
  {
    case 0x103u:
      this->CalcCombatDamage((int)&nVal);
      break;
    case 0x104u:
      this->GetDeadRoleNumInForce((int *)&nVal);
      break;
    case 0x105u:
      this->GetAliveRoleNumInForce(&nVal);
      break;
    case 0x106u:
      this->GetCastFightSkillSuccess((int)&nVal);
      break;
    case 0x10Du:
      this->SetCoAttack((unsigned int)&nVal);
      break;
    case 0x10Eu:
      ((CCBSystem *)this)->ValidateThreadAction((int)&nVal);
      break;
    default:
      return;
  }
}

// 0x004EF980
int CCBRoleState::CalcHealAmount(int roleIdx)
{
  int RoleHP; // eax
  char *v4; // eax
  int result; // eax
  int v6; // [esp+0xC] [ebp-0xC]

  *(_DWORD *)(roleIdx + 29) = 0;
  *(_DWORD *)(roleIdx + 33) = 0;
  *(_WORD *)(roleIdx + 37) = 0;
  *(_BYTE *)(roleIdx + 39) = 0;
  RoleHP = this->GetRoleHP(*(_DWORD *)(roleIdx + 12));
  this->GetRoleMP(RoleHP);
  v4 = &this->m_sCombatDialog[892 * *(_DWORD *)(roleIdx + 8)];
  if ( v4[651] )
  {
    v6 = 1;
  }
  else if ( v4[649] )
  {
    v6 = 2;
  }
  else
  {
    v6 = v4[650] != 0 ? 3 : 0;
  }
  result = v6;
  if ( v6 )
  {
    *(_BYTE *)(roleIdx + 17) = 1;
    *(_DWORD *)(roleIdx + 12) = -1;
  }
  else
  {
    *(_BYTE *)(roleIdx + 17) = 0;
  }
  return result;
}

// 0x004EFAF0
void CCBRoleState::WriteBackRoleData(int nVal, int *p_DWORD, int *pnVal)
{
  int *v4; // edi
  int v5; // ebx
  char v6; // dl
  int v7; // eax
  int *p_roleIdx; // esi
  char v9; // al
  int v10; // edi
  int v11; // esi
  int roleIdx; // [esp+0x10] [ebp-0x2C] BYREF
  int v13; // [esp+0x14] [ebp-0x28]

  v4 = pnVal;
  *pnVal = -1;
  *p_DWORD = -1;
  if ( *(_BYTE *)(nVal + 17) )
  {
    v5 = 0;
    v6 = 0;
    v7 = 0;
    p_roleIdx = &roleIdx;
    do
    {
      if ( *(_BYTE *)(nVal + v7 + 29) )
      {
        *p_roleIdx = v7;
        ++v5;
        ++p_roleIdx;
        if ( (unsigned int)v7 <= 4 )
        {
          v4 = pnVal;
          v6 = 1;
        }
      }
      ++v7;
    }
    while ( v7 < 11 );
    if ( v5 != 1 )
    {
      if ( v6 )
      {
        v10 = v13;
        v11 = roleIdx;
        if ( this->WriteBackConfig(roleIdx, v13) && v5 == 2 )
        {
          *p_DWORD = v11;
          *pnVal = v10;
        }
      }
      else if ( *(_BYTE *)(nVal + 37) && *(_BYTE *)(nVal + 38) )
      {
        *p_DWORD = 8;
        *v4 = 9;
      }
      else
      {
        v9 = *(_BYTE *)(nVal + 34);
        if ( (!v9
           || (!*(_BYTE *)(nVal + 39) || !*(_BYTE *)(nVal + 36)) && (*(_BYTE *)(nVal + 39) || !*(_BYTE *)(nVal + 36)))
          && (!*(_BYTE *)(nVal + 35) || *(_BYTE *)(nVal + 39)) )
        {
          if ( v9 )
          {
            if ( *(_BYTE *)(nVal + 39) )
            {
              if ( !*(_BYTE *)(nVal + 36) )
              {
                *p_DWORD = 5;
                *v4 = 10;
              }
            }
          }
          else if ( *(_BYTE *)(nVal + 39) && *(_BYTE *)(nVal + 36) )
          {
            *p_DWORD = 10;
            *v4 = 7;
          }
        }
      }
    }
  }
}

// 0x004EFD70
bool CCBRoleState::WriteBackConfig(int roleIdx, int nVal)
{
  int RoleHP; // ebp
  int v7; // eax
  bool result; // al
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // edx
  int v12; // eax
  _DWORD *i; // ecx
  int v14; // [esp+0x10] [ebp-0x4]
  int roleIdxa; // [esp+0x18] [ebp+0x4]
  int nVala; // [esp+0x1C] [ebp+0x8]

  v14 = -1;
  RoleHP = this->GetRoleHP(roleIdx);
  v7 = this->GetRoleHP(nVal);
  roleIdxa = *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][223 * roleIdx + 4] + 1);
  nVala = *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][223 * nVal + 4] + 1);
  if ( roleIdx == nVal )
    return 1;
  if ( RoleHP != v7 )
    return 0;
  if ( RoleHP == 2 )
  {
    switch ( roleIdx )
    {
      case 5:
      case 7:
      case 10:
        return nVal == 5 || nVal == 10 || nVal == 7;
      case 8:
      case 9:
        if ( nVal != 9 && nVal != 8 )
          return 0;
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    v9 = 0;
    v10 = &this->m_RoleXor[6].bMagicMastered[3][5];
    do
    {
      v11 = 3;
      do
      {
        if ( *v10 == roleIdxa )
          v14 = v9;
        ++v10;
        --v11;
      }
      while ( v11 );
      ++v9;
    }
    while ( v9 < 3 );
    v12 = 0;
    for ( i = &this->m_RoleXor[6].bMagicMastered[2 * v14 + 3][5]; *i != nVala; ++i )
    {
      if ( ++v12 >= 3 )
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004EFE90
bool CCBRoleState::ReviveAllFriendAtEnd(int roleIdx, int nVal)
{
  int RoleHP; // ebp
  int v7; // eax
  bool result; // al
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // edx
  int v12; // eax
  _DWORD *i; // ecx
  int v14; // [esp+0x10] [ebp-0x4]
  int roleIdxa; // [esp+0x18] [ebp+0x4]
  int nVala; // [esp+0x1C] [ebp+0x8]

  v14 = -1;
  RoleHP = this->GetRoleHP(roleIdx);
  v7 = this->GetRoleHP(nVal);
  roleIdxa = *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][223 * roleIdx + 4] + 1);
  nVala = *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][223 * nVal + 4] + 1);
  if ( roleIdx == nVal )
    return 1;
  if ( RoleHP != v7 )
    return 0;
  if ( RoleHP == 2 )
  {
    switch ( roleIdx )
    {
      case 5:
      case 8:
        if ( nVal != 8 && nVal != 5 )
          return 0;
        result = 1;
        break;
      case 6:
      case 10:
        if ( nVal != 10 && nVal != 6 )
          return 0;
        result = 1;
        break;
      case 7:
      case 9:
        return nVal == 9 || nVal == 7;
      default:
        return 0;
    }
  }
  else
  {
    v9 = 0;
    v10 = (_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[0][2] + 1);
    do
    {
      v11 = 2;
      do
      {
        if ( *v10 == roleIdxa )
          v14 = v9;
        ++v10;
        --v11;
      }
      while ( v11 );
      ++v9;
    }
    while ( v9 < 3 );
    v12 = 0;
    for ( i = (_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[0][4 * v14 + 2] + 1); *i != nVala; ++i )
    {
      if ( ++v12 >= 2 )
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004EFFC0
bool CCBRoleState::IsRoleReady(int roleIdx)
{
  int *v2; // eax

  v2 = (int *)&this->m_sCombatDialog[892 * roleIdx];
  return *((_BYTE *)v2 + 577)
      && !*((_BYTE *)v2 + 1432)
      && !*((_BYTE *)v2 + 1431)
      && v2[147] > 0
      && this->GetRoleField(roleIdx, 23) == 0;
}

// 0x004F0020
void CCBRoleState::SetEnemyBeImbibeNimbus(char pData, char pData2)
{
  int v4; // ebp
  int v5; // esi
  int v6; // ebp
  int v7; // edi
  int v8; // esi
  _DWORD v9[9]; // [esp+0x14] [ebp-0x24] BYREF

  memset(v9, 0xFFu, sizeof(v9));
  if ( pData2 )
  {
    if ( pData )
    {
      v4 = 0;
      if ( this->IsRoleReady(8) )
      {
        v9[0] = 8;
        v4 = 1;
      }
      if ( this->IsRoleReady(9) )
        v9[v4] = 9;
      v5 = 0;
      if ( this->IsRoleReady(5) )
      {
        v9[3] = 5;
        v5 = 1;
      }
      if ( this->IsRoleReady(10) )
        v9[v5++ + 3] = 10;
      if ( this->IsRoleReady(7) )
        v9[v5 + 3] = 7;
      this->IsRoleReady(6);
    }
    else
    {
      v6 = 0;
      if ( this->IsRoleReady(5) )
      {
        v9[0] = 5;
        v6 = 1;
      }
      if ( this->IsRoleReady(8) )
        v9[v6] = 8;
      v7 = 0;
      if ( this->IsRoleReady(6) )
      {
        v9[3] = 6;
        v7 = 1;
      }
      if ( this->IsRoleReady(10) )
        v9[v7 + 3] = 10;
      v8 = 0;
      if ( this->IsRoleReady(7) )
      {
        v9[6] = 7;
        v8 = 1;
      }
      if ( this->IsRoleReady(9) )
        v9[v8 + 6] = 9;
    }
  }
}

// 0x004F0210
bool CCBRoleState::CalSneakAttack(int nVal, unsigned int dwVal)
{
  signed int v4; // esi
  int v5; // ebx
  _BYTE *v6; // esi

  if ( nVal < 5 || nVal >= 11 )
  {
LABEL_14:
    v4 = dwVal;
  }
  else
  {
    v4 = dwVal;
    if ( dwVal <= 4 )
    {
      if ( HIBYTE(this->m_Role[0].byMagicUseTime[4][446 * nVal + 2])
        || LOBYTE(this->m_Role[0].byMagicUseTime[4][446 * nVal + 3]) )
      {
        return 1;
      }
      if ( *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][223 * dwVal + 4] + 1) == this->CheckDeath(*(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 112) + 64)) )
      {
        v5 = 0;
        v6 = (char *)&this->m_Role[2].fSkillCentInc + 1;
        while ( !*(v6 - 855)
             || *v6
             || *(v6 - 1)
             || *((_DWORD *)v6 - 74) != 6
             || this->SetRoleField(v5, 0) <= 0 )
        {
          ++v5;
          v6 += 892;
          if ( v5 >= 5 )
            goto LABEL_14;
        }
        return 0;
      }
    }
  }
  return (unsigned int)nVal > 4
      || v4 < 5
      || v4 >= 11
      || HIBYTE(this->m_Role[0].byMagicUseTime[4][446 * nVal + 2])
      || LOBYTE(this->m_Role[0].byMagicUseTime[4][446 * nVal + 3])
      || v4 != 6
      || !this->m_BufferData[2780]
      || this->m_BufferData[3635]
      || this->m_BufferData[3634]
      || this->SetRoleField(10, 0) <= 0;
}

// 0x004F0360
unsigned int CCBRoleState::InitRoleFiveMagic(int nVal)
{
  unsigned int result; // eax

  result = *(unsigned __int8 *)(((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(*(_DWORD *)(nVal + 4)) + 592);
  switch ( result )
  {
    case 0u:
      goto LABEL_12;
    case 1u:
      this->GetRoleMP(1);
      *(_BYTE *)(nVal + 17) = 1;
      *(_DWORD *)(nVal + 29) = 0;
      *(_DWORD *)(nVal + 33) = 0;
      *(_WORD *)(nVal + 37) = 0;
      *(_BYTE *)(nVal + 39) = 0;
      result = 0;
      goto LABEL_14;
    case 2u:
      result = *(_DWORD *)(nVal + 12);
      if ( result <= 4 )
      {
        this->GetRoleMP(2);
        result = *(_DWORD *)(nVal + 12);
        if ( result <= 4 )
        {
          result = 0;
          *(_DWORD *)(nVal + 12) = 0;
        }
      }
      if ( *(_DWORD *)(nVal + 12) != -1 )
        goto LABEL_12;
      result = 0;
      break;
    case 3u:
      this->GetRoleMP(2);
      *(_BYTE *)(nVal + 17) = 1;
      *(_DWORD *)(nVal + 29) = 0;
      *(_DWORD *)(nVal + 33) = 0;
      *(_WORD *)(nVal + 37) = 0;
      *(_BYTE *)(nVal + 39) = 0;
      result = 0;
LABEL_14:
      *(_DWORD *)(nVal + 12) = -1;
      return result;
    default:
      return result;
  }
  while ( !*(_BYTE *)(result + nVal + 29) )
  {
    if ( (int)++result >= 11 )
    {
      *(_BYTE *)(nVal + 17) = 0;
      return result;
    }
  }
  *(_DWORD *)(nVal + 12) = result;
LABEL_12:
  *(_BYTE *)(nVal + 17) = 0;
  return result;
}

// 0x004F05A0
char CCBRoleState::IsAllyTargetCmd(int *p_DWORD)
{
  char v2; // al
  char result; // al
  char v4; // al

  switch ( *p_DWORD )
  {
    case 260:
    case 261:
    case 269:
      v2 = *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(p_DWORD[1]) + 577);
      goto LABEL_4;
    case 262:
      v2 = *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(p_DWORD[1]) + 629);
LABEL_4:
      if ( v2 != 2 && v2 != 4 )
        goto LABEL_10;
      result = 1;
      break;
    case 270:
      v4 = *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(p_DWORD[1]) + 592);
      if ( v4 != 1 && v4 != 3 )
        goto LABEL_10;
      result = 1;
      break;
    default:
LABEL_10:
      result = 0;
      break;
  }
  return result;
}

// 0x004F0640
void CCBRoleState::InitRoleSpecEquipAttrib(int nRoleIndex)
{
  int v2; // edx
  int *v3; // eax

  if ( *(_DWORD *)(nRoleIndex + 12) > 0xAu )
  {
    v2 = 0;
    v3 = (int *)&this->m_Role[0].bMagicMastered[7][3];
    do
    {
      if ( *(_BYTE *)(nRoleIndex + v2 + 29) && *((_BYTE *)v3 - 11) && *v3 > 0 && !*((_BYTE *)v3 + 844) )
        break;
      ++v2;
      v3 += 223;
    }
    while ( v2 < 11 );
  }
}

// 0x004F0700
void CCBRoleState::UnloadWeaponModel(int nVal)
{
  int v3; // esi
  _DWORD *v4; // edi
  int v5; // [esp+0x0] [ebp-0x10]

  v3 = 0;
  v4 = (unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][4] + 1);
  do
  {
    if ( *((_BYTE *)v4 - 559) && *v4 == nVal && !this->SetVisible(v3, v5) )
      break;
    ++v3;
    v4 += 223;
  }
  while ( v3 < 5 );
}

// 0x004F0750
bool CCBRoleState::SetVisible(int roleIdx, int a3)
{
  if ( !this->m_Role[0].bMagicMastered[5][892 * roleIdx + 5] )
    return 0;
  if ( this->GetRoleField(roleIdx, 14) )
    return 0;
  if ( this->GetRoleField(roleIdx, 18) )
    return 0;
  if ( this->GetRoleField(roleIdx, 19) )
    return 0;
  return this->GetRoleField(roleIdx, 17) == 0;
}

// 0x004F07D0
char CCBRoleState::GetRole(int nIndex, int nVal)
{
  switch ( nIndex )
  {
    case 1:
      if ( nVal == 1 )
        return 1;
      break;
    case 2:
      if ( nVal == 2 )
        return 1;
      break;
    case 4:
      if ( nVal == 4 )
        return 1;
      break;
    case 3:
      if ( nVal == 3 )
        return 1;
      break;
    default:
      if ( nIndex == 5 && nVal == 5 )
        return 1;
      break;
  }
  return 0;
}

// 0x004F0830
unsigned __int8 CCBRoleState::GetRoleNum(int *pnVal)
{
  int v2; // eax
  int SkillNum; // ebp
  unsigned __int8 result; // al
  int RoleHP; // eax
  int RoleNum; // ebp

  v2 = *pnVal;
  if ( *pnVal == 261 || v2 == 260 || v2 == 269 )
  {
    RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pnVal[1]);
    result = *(_BYTE *)(RoleNum + 577);
    if ( result && result <= 4u )
    {
      if ( result != 1 && result != 3 )
      {
        RoleHP = this->GetRoleHP(pnVal[2]);
        if ( *(_BYTE *)(RoleNum + 577) > 2u )
          RoleHP = this->IsForce1(RoleHP);
        goto LABEL_10;
      }
      goto LABEL_18;
    }
  }
  else
  {
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(pnVal[1]);
    result = *(_BYTE *)(SkillNum + 629);
    if ( result && result <= 4u )
    {
      if ( result != 1 && result != 3 )
      {
        RoleHP = this->GetRoleHP(pnVal[2]);
        if ( *(_BYTE *)(SkillNum + 629) > 2u )
          RoleHP = this->IsForce1(RoleHP);
LABEL_10:
        this->GetRoleMP(RoleHP);
        *((_BYTE *)pnVal + 17) = 1;
        return 0;
      }
LABEL_18:
      *((_BYTE *)pnVal + 17) = 0;
      return result;
    }
  }
  return ((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1))->CreateObj(&dword_5D8EC8, 0, 0x40u);
}

// 0x004F0A10
char CCBRoleState::CalcCombatDamage(int nVal)
{
  unsigned int v3; // ebx
  int v4; // edx
  unsigned int v5; // edi
  bool v6; // al
  BOOL v7; // eax
  int v8; // eax
  int *v9; // edx
  int v10; // eax
  int *v11; // edx
  CCBStage *v12; // ecx
  int RoleIndex; // eax
  int v14; // ebx
  bool v15; // cc
  CCBStage *v17; // ecx
  bool v18; // zf
  void *v19; // eax
  _DWORD pData[11]; // [esp+0xC] [ebp-0x80] BYREF
  int v21; // [esp+0x38] [ebp-0x54]
  int nVal2; // [esp+0x44] [ebp-0x48]
  int p_DWORD[3]; // [esp+0x50] [ebp-0x3C] BYREF
  int v24; // [esp+0x5C] [ebp-0x30]
  int v25; // [esp+0x60] [ebp-0x2C]
  int v26; // [esp+0x64] [ebp-0x28]
  int v27; // [esp+0x68] [ebp-0x24]
  int v28; // [esp+0x6C] [ebp-0x20]
  unsigned int v29; // [esp+0x70] [ebp-0x1C]
  float v30; // [esp+0x74] [ebp-0x18]
  unsigned __int16 *v31; // [esp+0x78] [ebp-0x14]
  unsigned int nRoleIndex; // [esp+0x7C] [ebp-0x10]
  BOOL bImmediate; // [esp+0x80] [ebp-0xC]
  int v34; // [esp+0x84] [ebp-0x8]
  bool v35; // [esp+0x8A] [ebp-0x2]
  bool v36; // [esp+0x8B] [ebp-0x1]

  memset(pData, 0, sizeof(pData));
  memset(p_DWORD, 0, sizeof(p_DWORD));
  LOBYTE(pData[10]) = 1;
  v3 = *(_DWORD *)(nVal + 8);
  pData[3] = -1;
  pData[0] = 259;
  v29 = v3;
  v30 = COERCE_FLOAT(this->ApplyDamage(6, v3));
  if ( SLODWORD(v30) > 0 )
  {
    v30 = (double)SLODWORD(v30) * 10.24;
    v31 = (unsigned __int16 *)(int)v30;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    v36 = (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)v31;
  }
  else
  {
    v36 = 0;
  }
  v4 = 24;
  v5 = 0;
  v34 = 24;
  v31 = &this->m_Role[0].byMagicUseTime[8][4];
  do
  {
    if ( *(_BYTE *)(nVal + 17) )
    {
      if ( !*(_BYTE *)(v5 + nVal + 29) )
        goto LABEL_53;
    }
    else if ( *(_DWORD *)(nVal + 12) != v5 )
    {
      goto LABEL_53;
    }
    if ( ((CCBStageRole *)*(CCBStageRole **)(v4
                                                          + *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                + 1)))->ForceEndTaskByPFN()
      && this->IsRoleAlive(v5) == 1
      && !this->GetRoleField(v5, 21) )
    {
      if ( v34 < 44 || v34 >= 68 )
      {
        *(float *)&nRoleIndex = COERCE_FLOAT(this->ApplyDamage(5, v3));
        if ( (int)nRoleIndex > 0 )
        {
          *(float *)&nRoleIndex = (double)(int)nRoleIndex * 10.24;
          v28 = (int)*(float *)&nRoleIndex;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
          v6 = (((int)unk_5DFDEC >> 16) & 0x3FF) < v28;
        }
        else
        {
          v6 = 0;
        }
      }
      else
      {
        v6 = 0;
      }
      v35 = v6;
      if ( this->GetRoleField(v5, 20)
        || this->GetRoleField(v5, 14)
        || this->GetRoleField(v5, 17) )
      {
        v35 = 0;
      }
      this->SetCanAction(v3, v5, 0);
      bImmediate = v7;
      if ( !v35 && v7 < 0 )
      {
        if ( v36 )
        {
          *(float *)&nRoleIndex = (double)bImmediate * 1.3;
          LODWORD(v30) = (int)*(float *)&nRoleIndex;
          *(float *)&nRoleIndex = (double)SLODWORD(v30)
                                * *(float *)((char *)&this->m_Role[0].byMagicUseTime[5][446 * v3 + 3] + 1)
                                * 0.0099999998;
          v27 = (int)*(float *)&nRoleIndex;
          bImmediate = LODWORD(v30) + v27;
        }
        if ( this->GetRoleField(v5, 20)
          || (v26 = 1109645066,
              v25 = (int)40.959999,
              ++*(_DWORD *)&g_TempBuffer1024[912],
              unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
              (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)40.959999)
          && *(_BYTE *)v31 )
        {
          ((CCBSystem *)this)->AddCommand(v3, bImmediate, 0);
          goto LABEL_53;
        }
        nRoleIndex = v5;
        if ( v34 >= 24 && v34 < 44 && this->IsAlive(v5, v3) )
        {
          ((CCBSystem *)this)->AddCommand(0, bImmediate, 1);
          *(float *)&nRoleIndex = 0.0;
          this->CanUseSkill(v5);
          if ( v36 )
          {
            v8 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
            v9 = (int *)(*(_DWORD *)(*(_DWORD *)(v8 + 20) + 24) + 6584);
            nVal2 = *v9;
            ((CEffMgr *)*(CEffMgr **)(v8 + 44))->Init(470, nVal2, v9[1], v9[2], 0);
          }
          if ( v34 >= 24 && v34 < 44 )
            goto LABEL_45;
        }
        else
        {
          if ( bImmediate < 0
            && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdEmpty(v5)
            && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdReady(v5) )
          {
            ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdString(v5);
          }
          if ( v36 )
          {
            v10 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
            v11 = (int *)(*(_DWORD *)(*(_DWORD *)(v10 + 20) + v34) + 6584);
            v21 = *v11;
            ((CEffMgr *)*(CEffMgr **)(v10 + 44))->Init(470, v21, v11[1], v11[2], 0);
          }
          ((CCBSystem *)this)->AddCommand(v5, bImmediate, 1);
          if ( v34 >= 24 && v34 < 44 )
LABEL_45:
            this->CalcAttackPower(v5);
        }
        this->CanBeImbibeNimbus(v3, nRoleIndex);
        this->ValidateSlotIndex(v3, nRoleIndex);
        bImmediate = *(BOOL *)((char *)&this->m_Role[0].byMagicUseTime[8][446 * v3 + 1] + 1);
        if ( bImmediate > 0 )
        {
          *(float *)&bImmediate = (double)bImmediate * 10.24;
          v24 = (int)*(float *)&bImmediate;
          ++*(_DWORD *)&g_TempBuffer1024[912];
          unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
          if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < v24 )
            this->GetFirstAliveRoleInForce(v3, nRoleIndex);
        }
        goto LABEL_53;
      }
      v12 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
      pData[2] = v5;
      RoleIndex = ((CCBStage *)v12)->GetRoleIndex(5, pData, 1);
      v14 = RoleIndex;
      if ( RoleIndex != -1 )
      {
        ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, (int)sub_4FEEF0, 0, 0, 0, p_DWORD, -1082130432, 0);
        this->CheckRoleStatus((int)p_DWORD);
        ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v14, 0 /* TODO: (int)CCBStage::SelectRole */, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
        ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v14);
      }
      v3 = v29;
    }
    else if ( this->IsRoleAlive(v5) || this->GetRoleField(v5, 21) )
    {
      v17 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
      pData[2] = v5;
      *(float *)&nRoleIndex = COERCE_FLOAT(((CCBStage *)v17)->GetRoleIndex(7, pData, 1));
      if ( *(float *)&nRoleIndex != NAN )
      {
        this->CheckRoleStatus((int)p_DWORD);
        v18 = this->GetRoleField(v5, 21) == 0;
        v19 = CCBStage::GetRoleTaskNum;
        if ( v18 )
          v19 = CCBStage::SelectRole;
        ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(nRoleIndex, (int)v19, 0, 0, 0, p_DWORD, -1082130432, 1065353216);
        ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(nRoleIndex);
      }
    }
LABEL_53:
    v4 = v34 + 4;
    ++v5;
    v15 = v34 + 4 < 68;
    v34 += 4;
    v31 += 446;
  }
  while ( v15 );
  return 1;
}

// 0x004F1070
char CCBRoleState::GetAliveRoleNumInForce(tagCmdData *force)
{
  int v3; // edi
  int v4; // ecx
  tagCmdData *v5; // esi
  CCBStage *v6; // ecx
  int RoleIndex; // edi
  unsigned int v8; // esi
  int v9; // eax
  int v10; // ecx
  bool v11; // cc
  unsigned int nSrcRole; // eax
  int v13; // edx
  char v14; // al
  int v16; // [esp+0x0] [ebp-0x90]
  int nRoleIndex[11]; // [esp+0xC] [ebp-0x84] BYREF
  _DWORD pData[11]; // [esp+0x38] [ebp-0x58] BYREF
  int roleIdx[3]; // [esp+0x64] [ebp-0x2C] BYREF
  int v20; // [esp+0x70] [ebp-0x20]
  int v21; // [esp+0x74] [ebp-0x1C]
  float v22; // [esp+0x78] [ebp-0x18]
  int v23; // [esp+0x7C] [ebp-0x14]
  int p_DWORD; // [esp+0x80] [ebp-0x10] BYREF
  int pnVal; // [esp+0x84] [ebp-0xC] BYREF
  _DWORD *v26; // [esp+0x88] [ebp-0x8]
  unsigned int v27; // [esp+0x8C] [ebp-0x4]

  memset(nRoleIndex, 0, sizeof(nRoleIndex));
  v3 = 0;
  v4 = 24;
  v21 = 0;
  pnVal = 0;
  p_DWORD = 6;
  v27 = 0;
  v23 = 24;
  v26 = (unsigned int *)((char *)&this->m_Role[1].dwMagicID[6][5] + 1);
  do
  {
    v5 = force;
    if ( force->bMultiDestRole )
    {
      if ( !force->bDestRole[v3] )
        goto LABEL_27;
    }
    else if ( force->nDestRole != v3 )
    {
      goto LABEL_27;
    }
    if ( ((CCBStageRole *)*(CCBStageRole **)(v4
                                                          + *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                + 1)))->ForceEndTaskByPFN()
      || *(_WORD *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(force->dwItemID) + 666) == 2 )
    {
      if ( this->GetRoleField(v3, 22) )
        goto LABEL_27;
      qmemcpy(nRoleIndex, force, sizeof(nRoleIndex));
      nRoleIndex[3] = v27;
      if ( this->VarianceRoundCounter(nRoleIndex) )
      {
        v8 = v27;
        v21 = this->CheckTargetCombo(force, v27);
        if ( v21 < 0
          && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdEmpty(v8)
          && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdReady(v8) )
        {
          ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(force->dwItemID);
          ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdData(v8);
        }
        if ( v23 >= 44 && v23 < 68 && this->SetRoleField(v27, 0) <= 0 )
        {
          if ( (unsigned __int8)this->Revive(v16) )
          {
            ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(v26 - 135));
            if ( v9 )
            {
              if ( *(_DWORD *)(v9 + 832) )
              {
                if ( *(_DWORD *)(v9 + 836) == force->dwItemID )
                {
                  v10 = *(__int16 *)(v9 + 840);
                  v22 = *(float *)&v10;
                  if ( v10 > 0 )
                  {
                    v22 = (double)SLODWORD(v22) * 10.24;
                    v20 = (int)v22;
                    ++*(_DWORD *)&g_TempBuffer1024[912];
                    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
                    if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < v20 )
                      *v26 = *(_DWORD *)(v9 + 832);
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      memset(pData, 0, sizeof(pData));
      pData[2] = v27;
      v6 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
      LOBYTE(pData[10]) = 1;
      pData[1] = 0;
      RoleIndex = ((CCBStage *)v6)->GetRoleIndex(7, pData, 1);
      if ( RoleIndex == -1 )
        goto LABEL_27;
      this->CheckRoleStatus((int)roleIdx);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::SelectRole */, 0, 0, 0, roleIdx, 0, 1065353216);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
    }
    v5 = force;
LABEL_27:
    v4 = v23 + 4;
    v3 = v27 + 1;
    v11 = v23 + 4 < 68;
    ++v27;
    v23 += 4;
    v26 += 223;
  }
  while ( v11 );
  this->SetRoleHP(v5->nSrcRole, v5->dwItemID);
  nSrcRole = v5->nSrcRole;
  if ( nSrcRole <= 4 )
  {
    ((PAL_GDB *)this)->SearchItemLoop(nSrcRole, v5->dwItemID, &p_DWORD, &pnVal);
    v13 = pnVal + 892 * v5->nSrcRole + 8 * p_DWORD + 984;
    v14 = this->m_sCombatDialog[v13];
    if ( v14 != -1 )
      this->m_sCombatDialog[v13] = v14 + 1;
  }
  if ( *(_DWORD *)&this->m_Role[0].bMagicMastered[1][892 * v5->nSrcRole + 3] == 7312
    && v5->dwCmdKind == 261
    && v5->dwItemID == 210 )
  {
    this->CheckRoleCanAct(v5->nSrcRole);
  }
  return 1;
}

// 0x004F1420
char CCBRoleState::GetDeadRoleNumInForce(int *force)
{
  int v3; // edx
  CCBStage *v4; // ecx
  int v5; // esi
  CCBStage *v6; // ecx
  int RoleIndex; // esi
  int v8; // esi
  int v9; // eax
  int v10; // ecx
  bool v11; // cc
  int v13; // [esp+0x0] [ebp-C0h]
  int nRoleIndex[11]; // [esp+0xC] [ebp-B4h] BYREF
  _DWORD v15[11]; // [esp+0x38] [ebp-0x88] BYREF
  _DWORD pData[11]; // [esp+0x64] [ebp-0x5C] BYREF
  int p_DWORD[3]; // [esp+0x90] [ebp-0x30] BYREF
  int roleIdx[3]; // [esp+0x9C] [ebp-0x24] BYREF
  int v19; // [esp+A8h] [ebp-0x18]
  int v20; // [esp+ACh] [ebp-0x14]
  float v21; // [esp+B0h] [ebp-0x10]
  _DWORD *v22; // [esp+B4h] [ebp-0xC]
  int v23; // [esp+B8h] [ebp-0x8]
  int idx; // [esp+BCh] [ebp-0x4]

  v3 = 0;
  memset(nRoleIndex, 0, sizeof(nRoleIndex));
  v20 = 0;
  idx = 0;
  v23 = 24;
  v22 = (unsigned int *)((char *)&this->m_Role[1].dwMagicID[6][5] + 1);
  do
  {
    if ( *((_BYTE *)force + 17) )
    {
      if ( !*((_BYTE *)force + v3 + 29) )
        goto LABEL_30;
    }
    else if ( force[3] != v3 )
    {
      goto LABEL_30;
    }
    qmemcpy(nRoleIndex, force, sizeof(nRoleIndex));
    nRoleIndex[3] = v3;
    if ( this->VarianceRoundCounter(nRoleIndex) )
    {
      if ( this->IsAllyTargetCmd(force)
        || ((CCBStageRole *)*(CCBStageRole **)(v23
                                                            + *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                  + 1)))->ForceEndTaskByPFN()
        || *(_WORD *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(force[1]) + 666) == 2 )
      {
        v8 = idx;
        v20 = this->CheckBoss(force, idx);
        if ( v20 < 0
          && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdEmpty(v8)
          && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdReady(v8) )
        {
          ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdData(v8);
        }
        if ( force[1] == 4101 )
          this->GetFirstAliveRoleInForce(0, force[3]);
        if ( v23 >= 44 && v23 < 68 && this->SetRoleField(idx, 0) <= 0 )
        {
          if ( (unsigned __int8)this->Revive(v13) )
          {
            ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(v22 - 135));
            if ( v9 )
            {
              if ( *(_DWORD *)(v9 + 832) )
              {
                if ( *(_DWORD *)(v9 + 836) == force[1] )
                {
                  v10 = *(__int16 *)(v9 + 840);
                  v21 = *(float *)&v10;
                  if ( v10 > 0 )
                  {
                    v21 = (double)SLODWORD(v21) * 10.24;
                    v19 = (int)v21;
                    ++*(_DWORD *)&g_TempBuffer1024[912];
                    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
                    if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < v19 )
                      *v22 = *(_DWORD *)(v9 + 832);
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        memset(v15, 0, sizeof(v15));
        v6 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
        LOBYTE(v15[10]) = 1;
        v15[2] = idx;
        v15[1] = 0;
        RoleIndex = ((CCBStage *)v6)->GetRoleIndex(7, v15, 1);
        if ( RoleIndex != -1 )
        {
          this->CheckRoleStatus((int)p_DWORD);
          ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::SelectRole */, 0, 0, 0, p_DWORD, 0, 1065353216);
          ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
        }
      }
    }
    else
    {
      memset(pData, 0, sizeof(pData));
      v4 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
      pData[1] = 0;
      LOBYTE(pData[10]) = 1;
      pData[2] = idx;
      v5 = ((CCBStage *)v4)->GetRoleIndex(7, pData, 1);
      if ( v5 != -1 )
      {
        this->CheckRoleStatus((int)roleIdx);
        ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v5, 0 /* TODO: (int)CCBStage::SelectRole */, 0, 0, 0, roleIdx, 0, 1065353216);
        ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v5);
      }
    }
LABEL_30:
    v3 = idx + 1;
    v11 = v23 + 4 < 68;
    ++idx;
    v23 += 4;
    v22 += 223;
  }
  while ( v11 );
  this->SetRoleHP(force[2], force[1]);
  return 1;
}

// 0x004F17C0
char CCBRoleState::GetFirstAliveRoleInForce(int roleIdx, int arg4)
{
  int v4; // ebp
  int v5; // eax
  char *v6; // esi
  int v7; // ecx
  int v8; // edi
  int RoleIndex; // eax
  int v10; // ecx
  int v11; // edi
  CScreenMode *Instance; // eax
  int SkillNum; // eax
  int *v15; // [esp+0x0] [ebp-0x54]
  int p_DWORD; // [esp+0x10] [ebp-0x44] BYREF
  int v17; // [esp+0x14] [ebp-0x40]
  int v18; // [esp+0x18] [ebp-0x3C]
  int v19; // [esp+0x1C] [ebp-0x38] BYREF
  int v20; // [esp+0x20] [ebp-0x34]
  int v21; // [esp+0x24] [ebp-0x30]
  _DWORD pData[11]; // [esp+0x28] [ebp-0x2C] BYREF

  p_DWORD = 0;
  v17 = 0;
  v18 = 0;
  memset(pData, 0, sizeof(pData));
  v4 = -1;
  pData[3] = arg4;
  v19 = 0xFFFF;
  v20 = 0;
  v21 = 0;
  v5 = *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[7][223 * arg4] + 1);
  LOBYTE(pData[10]) = 1;
  v6 = &this->m_sCombatDialog[892 * arg4];
  pData[0] = 260;
  pData[1] = 0;
  if ( v5 > 0 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    v7 = *((_DWORD *)v6 + 274);
    v8 = (((int)unk_5DFDEC >> 16) & 0x7FFF) % v7 + 1;
    *((_DWORD *)v6 + 274) = v7 - v8;
    RoleIndex = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(28, pData, 1);
    v4 = RoleIndex;
    if ( RoleIndex != -1 )
    {
      p_DWORD = 1;
      v18 = v8;
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBRoleState::FormatAttackResultText */, 0, 0, 0, &p_DWORD, -1082130432, 0x40000000);
      this->CheckBuff(roleIdx);
    }
  }
  if ( *((_DWORD *)v6 + 275) && *((int *)v6 + 276) > 0 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    v10 = *((_DWORD *)v6 + 276);
    v11 = (((int)unk_5DFDEC >> 16) & 0x7FFF) % v10 + 1;
    *((_DWORD *)v6 + 276) = v10 - v11;
    if ( v4 == -1 )
    {
      v4 = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(28, pData, 1);
      if ( v4 == -1 )
        return 0;
    }
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa006", 1);
    v17 = *((_DWORD *)v6 + 275);
    p_DWORD = 0;
    v18 = v11;
    ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v4, 0 /* TODO: (int)CCBRoleState::FormatAttackResultText */, 0, 0, 0, &p_DWORD, -1082130432, 0x40000000);
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*((_DWORD *)v6 + 275));
    v19 = *((_DWORD *)v6 + 275);
    v21 = SkillNum;
    v20 = v11;
    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&v19, v15);
  }
  if ( v4 != -1 )
  {
    ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v4);
    return 1;
  }
  return 0;
}

// 0x004F1A30
bool CCBRoleState::GetCastFightSkillSuccess(int pCmd)
{
  int v4; // esi
  int i; // ebp
  int v6; // eax
  int pCmda; // [esp+0x14] [ebp+0x4]

  pCmda = *(_DWORD *)(pCmd + 8);
  v4 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( *(_BYTE *)(pCmd + 17) )
    {
      if ( !*(_BYTE *)(v4 + pCmd + 29) )
        goto LABEL_13;
    }
    else if ( *(_DWORD *)(pCmd + 12) != v4 )
    {
      goto LABEL_13;
    }
    if ( (this->IsAllyTargetCmd((int *)pCmd)
       || ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                 + 1)
                                                           + i))->ForceEndTaskByPFN()
       || *(_WORD *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(_DWORD *)(pCmd + 4)) + 748) == 2)
      && this->CheckBoss((int *)pCmd, v4) < 0
      && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdEmpty(v4)
      && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdReady(v4) )
    {
      ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdData(v4);
    }
LABEL_13:
    ++v4;
  }
  v6 = *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1120);
  if ( *(_DWORD *)(v6 + 56) == 1 )
    this->PopulateTargetList(pCmda, *(_DWORD *)(v6 + 104));
  return 1;
}

// 0x004F1B20
void CCBRoleState::SetCoAttack(unsigned int dwCoAttackID)
{
  unsigned int v4; // edi
  signed int dwCoAttackIDa; // [esp+0x14] [ebp+0x4]

  v4 = 0;
  for ( dwCoAttackIDa = 24; dwCoAttackIDa < 68; dwCoAttackIDa += 4 )
  {
    if ( *(_BYTE *)(dwCoAttackID + 17) )
    {
      if ( !*(_BYTE *)(v4 + dwCoAttackID + 29) )
        goto LABEL_12;
    }
    else if ( *(_DWORD *)(dwCoAttackID + 12) != v4 )
    {
      goto LABEL_12;
    }
    if ( (this->IsAllyTargetCmd((int *)dwCoAttackID)
       || ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                 + 1)
                                                           + dwCoAttackIDa))->ForceEndTaskByPFN())
      && this->GetV4((int *)dwCoAttackID, v4) < 0
      && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdEmpty(v4)
      && !((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->IsCmdReady(v4) )
    {
      ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdData(v4);
    }
LABEL_12:
    ++v4;
  }
  this->SetRoleHP(*(_DWORD *)(dwCoAttackID + 8), *(_DWORD *)(dwCoAttackID + 4));
  ((UIListBox *)*(UIListBox **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1068))->GetCurSel();
  ((UIScrollBar *)*(UIScrollBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1068))->SetRange(50.0);
  ((UIProgressBar *)*(UIProgressBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1068))->FindChildByName(0.0);
  *(unsigned int *)((char *)&this->m_Role[1].dwMagicID[6][223 * *(_DWORD *)(dwCoAttackID + 8) + 4] + 1) = 0;
}

// 0x004F1CC0
bool CCBRoleState::CanBeImbibeNimbus(int dmg, unsigned int nRoleIndex)
{
  bool result; // al
  char *v6; // [esp+0xC] [ebp-0x4]
  int dmga; // [esp+0x18] [ebp+0x8]
  float dmgb; // [esp+0x18] [ebp+0x8]

  if ( dmg < 5 )
    return 0;
  if ( dmg >= 11 )
    return 0;
  v6 = &this->m_sCombatDialog[892 * dmg];
  if ( !v6[577] )
    return 0;
  dmga = this->ApplyDamage(4, dmg);
  if ( dmga <= 0 )
    return 0;
  dmgb = (double)dmga * 10.24;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
  if ( (((int)unk_5DFDEC >> 16) & 0x3FF) >= (int)dmgb )
    return 0;
  switch ( *((_DWORD *)v6 + 160) )
  {
    case 0x385:
      this->ProcessRound(nRoleIndex);
      goto LABEL_8;
    case 0x386:
    case 0x387:
    case 0x388:
    case 0x389:
    case 0x38A:
    case 0x38B:
    case 0x38C:
    case 0x38D:
    case 0x38E:
    case 0x38F:
    case 0x394:
    case 0x395:
    case 0x396:
    case 0x397:
    case 0x398:
    case 0x399:
    case 0x39E:
    case 0x39F:
    case 0x3A0:
      this->ProcessRound(nRoleIndex);
      result = 1;
      break;
    case 0x390:
      this->GetMaxHP(nRoleIndex);
      this->GetMaxMP(nRoleIndex);
      result = 1;
      break;
    case 0x391:
      result = this->CheckRoleValid(dmg, nRoleIndex, 27);
      break;
    case 0x392:
      result = this->CheckRoleValid(dmg, nRoleIndex, 28);
      break;
    case 0x393:
      result = this->CheckRoleValid(dmg, nRoleIndex, 1);
      break;
    case 0x3A1:
      result = this->CheckRoleValid(dmg, nRoleIndex, 30);
      break;
    default:
LABEL_8:
      result = 1;
      break;
  }
  return result;
}

// 0x004F1FA0
bool CCBRoleState::CheckRoleValid(int nRoleIndex, unsigned int roleIdx, int nVal)
{
  bool result; // al
  CCBSystem *v6; // edx
  CCBStage *v7; // ecx
  int RoleIndex; // edi
  CCBSystem *v9; // ecx
  int v10; // edi
  int v11; // edi
  void *TargetRole; // eax
  int p_DWORD[3]; // [esp+0x10] [ebp-0x70] BYREF
  _BYTE pOut[12]; // [esp+0x1C] [ebp-0x64] BYREF
  _DWORD v15[11]; // [esp+0x28] [ebp-0x58] BYREF
  _DWORD pData[11]; // [esp+0x54] [ebp-0x2C] BYREF

  switch ( nVal )
  {
    case 1:
      return this->CanRoleAct(roleIdx);
    case 2:
      v6 = *(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
      if ( LOBYTE(v6->m_pFightInfo->nRoleWillNotBeAttack) )
      {
        memset(pData, 0, sizeof(pData));
        pData[2] = nRoleIndex;
        v7 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
        LOBYTE(pData[10]) = 1;
        pData[0] = 267;
        pData[1] = 0;
        pData[3] = -1;
        RoleIndex = ((CCBStage *)v7)->GetRoleIndex(26, pData, 1);
        if ( RoleIndex != -1 )
        {
          memset(p_DWORD, 0, sizeof(p_DWORD));
          ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcessRoleEffect */, 0, 0, 0, p_DWORD, 0, 1077936128);
          ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
        }
        goto LABEL_6;
      }
      this->m_Role[0].bMagicMastered[1][0] = 1;
      memset(v15, 0, sizeof(v15));
      LOBYTE(v15[10]) = 1;
      LOWORD(v15[4]) = 0;
      v15[1] = ((CCBSystem *)v6)->ProcProtect();
      v15[3] = roleIdx;
      v15[2] = nRoleIndex;
      v9 = *(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
      v15[0] = 267;
      ((CCBSystem *)v9)->CreateObj((int ( *)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, v15);
      return 1;
    case 24:
    case 30:
      return 1;
    case 25:

      return 1;
    case 27:
      if ( roleIdx > 4 )
        return 1;
      v10 = this->GetTotalRounds() / 200;
      v11 = v10 - this->GetTotalRounds() / 100;
      if ( v11 > 0 )
      {
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        v11 = (((int)unk_5DFDEC >> 16) & 0x7FFF) % v11;
      }
      if ( v11 + this->GetTotalRounds() / 200 <= 0 )
        return 1;
      this->CheckBuff(roleIdx);
      return 1;
    case 28:
      if ( roleIdx > 4 )
        return 1;
      if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(14) <= 0 )
        goto LABEL_6;
      ++*(_DWORD *)&g_TempBuffer1024[912];
      unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
      TargetRole = ((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(TargetRole);
      result = 1;
      break;
    case 29:
      if ( this->Update(2) == 1 )
        this->SpawnRandomEnemies(nRoleIndex, roleIdx);
      return 1;
    default:
LABEL_6:
      result = 0;
      break;
  }
  return result;
}

// 0x004F2310
char CCBRoleState::CheckRoleNimbus(int nRoleIndex, unsigned int dwVal)
{
  int SkillNum; // eax

  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(_DWORD *)(nRoleIndex + 4));
  return this->CheckRoleValid(*(_DWORD *)(nRoleIndex + 8), dwVal, *(unsigned __int8 *)(SkillNum + 628));
}

// 0x004F2350
bool CCBRoleState::CanBeSelect(tagCmdData *pCmd, unsigned int nDestRole)
{
  int RoleNum; // eax

  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pCmd->dwItemID);
  return this->CheckRoleValid(pCmd->nSrcRole, nDestRole, *(unsigned __int8 *)(RoleNum + 578));
}

// 0x004F2390
char CCBRoleState::CheckRoundComplete()
{
  unsigned int v2; // ebx
  int v3; // esi
  _BYTE *v4; // ebp
  int v5; // eax
  CCBControl *v6; // ecx
  int v7; // ecx
  int v8; // ebx
  int v9; // ecx
  int v10; // esi
  int v11; // edx
  _DWORD *v12; // eax
  int v13; // edx
  int v14; // ecx
  _DWORD *v15; // esi
  int v16; // eax
  int v17; // edx
  int v18; // ebp
  double v19; // st7
  double v20; // st6
  int v21; // eax
  float v22; // edx
  int v23; // eax
  int v24; // edx
  int v26; // [esp+0x0] [ebp-0x34] BYREF
  float v27; // [esp+0x14] [ebp-0x20]
  int v28; // [esp+0x18] [ebp-0x1C]
  _DWORD v29[6]; // [esp+0x1C] [ebp-0x18] BYREF

  v2 = 0;
  v3 = 24;
  v4 = &this->m_Role[0].bMagicMastered[5][4];
  do
  {
    if ( *v4 )
    {
      if ( !((CCBStageRole *)*(CCBStageRole **)(v3
                                                             + *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                   + 1)))->ForceEndTaskByPFN() )
        return 0;
      LOBYTE(v5) = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->IsTaskExist(v2);
      if ( v5 > 0 )
        return 0;
    }
    v3 += 4;
    ++v2;
    v4 += 892;
  }
  while ( v3 < 44 );
  v6 = *(CCBControl **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 8);
  if ( v6->m_bActive )
    ((CCBControl *)v6)->GetState();
  v7 = unk_5DFDEC;
  v29[0] = 1;
  v29[1] = 2;
  v29[2] = 3;
  v29[3] = 4;
  v29[4] = 5;
  v29[5] = 6;
  v8 = 32;
  do
  {
    v9 = 214013 * v7 + 2531011;
    *(_DWORD *)&g_TempBuffer1024[912] += 2;
    v10 = ((v9 >> 16) & 0x7FFF) % 6;
    v7 = 214013 * v9 + 2531011;
    unk_5DFDEC = v7;
    v11 = ((v7 >> 16) & 0x7FFF) % 6;
    if ( v10 != v11 )
    {
      v12 = &v29[v11];
      v13 = v29[v10];
      v29[v10] = *v12;
      *v12 = v13;
      v7 = unk_5DFDEC;
    }
    --v8;
  }
  while ( v8 );
  v14 = 24;
  v15 = (unsigned int *)((char *)&this->m_Role[1].dwMagicID[8][4] + 1);
  do
  {
    if ( *((_BYTE *)v15 - 559) )
    {
      v16 = *(int *)((char *)&v26 + v14 + 4);
      *v15 = v16;
      v17 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
      v16 *= 3;
      v18 = *(_DWORD *)(v17 + 20);
      v19 = *(float *)(v18 + 4 * v16 + 8);
      v20 = *(float *)(v18 + 4 * v16 + 12);
      v27 = *(float *)(v18 + 4 * v16 + 12);
      v28 = *(_DWORD *)(v18 + 4 * v16 + 16);
      v21 = *(_DWORD *)(v14 + v17) + 6584;
      *(_DWORD *)(v21 + 8) = v28;
      v22 = v27;
      *(float *)v21 = v19;
      *(float *)(v21 + 4) = v20;
      v23 = *(_DWORD *)(v14 + *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1));
      *(float *)(v23 + 6600) = v22;
      v24 = v28;
      v23 += 6596;
      *(float *)v23 = v19;
      *(_DWORD *)(v23 + 8) = v24;
    }
    v14 += 4;
    v15 += 223;
  }
  while ( v14 < 44 );
  return 1;
}

// 0x004F2560
char CCBRoleState::ValidateSlotIndex(unsigned int arg0, unsigned int dwVal)
{
  unsigned int *v3; // edi
  int v4; // esi
  int v5; // edx
  float arg0a; // [esp+0x18] [ebp+0x8]

  if ( arg0 > 4 )
    return 0;
  if ( !this->m_Role[0].bMagicMastered[5][892 * arg0 + 4] )
    return 0;
  v3 = &Buffer.m_partyActor.m_dwMatMsg[352 * arg0 + 8];
  if ( !*v3 )
    return 0;
  v4 = 0;
  v5 = 700;
  while ( 1 )
  {
    if ( *(_BYTE *)(*v3 + v4 + 668) )
    {
      if ( *(__int16 *)(v5 + *v3) > 0 )
      {
        arg0a = (double)*(__int16 *)(v5 + *v3) * 10.24;
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)arg0a )
          break;
      }
    }
    v5 += 2;
    ++v4;
    if ( v5 >= 746 )
      return 0;
  }
  this->ProcessRound(dwVal);
  return 1;
}

// 0x004F2660
int CCBRoleState::CheckTargetCombo(tagCmdData *p, unsigned int roleIdx)
{
  this->CanBeSelect(p, roleIdx);
  this->IsBoss((int *)p, roleIdx);
  return this->CalcCombatDamage(p, roleIdx);
}

// 0x004F2690
int CCBRoleState::CheckBoss(int *arg0, int roleIdx)
{
  int v5; // ebp
  int result; // eax
  char *v7; // esi
  int v8; // eax
  int roleIdxa; // [esp+0x18] [ebp+0x8]

  this->IsBoss(arg0, roleIdx);
  v5 = this->SetRoleField(roleIdx, 0);
  result = this->CalcCombatDamage(arg0, roleIdx);
  roleIdxa = result;
  switch ( arg0[1] )
  {
    case 4201:
      v8 = this->SetRoleField(roleIdx, 0);
      ((CCBSystem *)this)->AddCommand(arg0[2], abs32((v5 - v8) / 2), 1);
      return roleIdxa;
    case 4304:
      this->CalcDefensePower(arg0[2]);
      return roleIdxa;
    case 4402:
      v7 = &this->m_sCombatDialog[892 * roleIdx];
      v7[1390] = 1;
      v7[1391] = 0;
      break;
  }
  return result;
}

// 0x004F2750
int CCBRoleState::CheckBoss(int *arg0, int roleIdx)
{
  if ( arg0[1] != 6230 || this->IsRoleInForce(roleIdx) )
  {
    this->CheckRoleNimbus((int)arg0, roleIdx);
    this->IsBoss(arg0, roleIdx);
    return this->CalcCombatDamage(arg0, roleIdx);
  }
  else
  {
    ((CCBSystem *)this)->AddCommand(roleIdx, -99999999, 1);
    return 0;
  }
}

// 0x004F27B0
int CCBRoleState::GetV4(int *arg0, unsigned int roleIdx)
{
  int v4; // ebp

  v4 = this->CalcCombatDamage(arg0, roleIdx);
  this->IsBoss(arg0, roleIdx);
  return v4;
}

// 0x004F27E0
int CCBRoleState::CalcComboDirect(const void *pData, unsigned int roleIdx)
{
  return this->CalcCombatDamage(pData, roleIdx);
}

// 0x004F2800
int CCBRoleState::ApplyItemEffect(int nCmdData, int nParam)
{
  int v4; // edi
  int *v5; // ebx
  unsigned int RoleByID; // eax
  int v7; // eax
  int v8; // edi
  signed int v9; // esi
  int v10; // edx
  int nCmdDataa; // [esp+0x14] [ebp+0x8]
  float nCmdDatab; // [esp+0x14] [ebp+0x8]

  v4 = 0;
  v5 = (int *)(((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(*(_DWORD *)(nCmdData + 4)) + 36);
  nCmdDataa = 4;
  do
  {
    if ( *v5 )
    {
      RoleByID = this->FindRoleByID(*v5);
      this->SetCanAction(RoleByID, nParam, 0);
      v4 += v7;
    }
    ++v5;
    --nCmdDataa;
  }
  while ( nCmdDataa );
  v8 = 2 * v4;
  if ( unk_5DFDEB )
  {
    nCmdDatab = (double)v8 * 0.1;
    v9 = abs32((int)nCmdDatab);
    if ( v9 )
    {
      v10 = (((int)(214013 * unk_5DFDEC + 2531011) >> 16) & 0x7FFF) % v9;
      *(_DWORD *)&g_TempBuffer1024[912] += 2;
      unk_5DFDEC = 214013 * (214013 * unk_5DFDEC + 2531011) + 2531011;
      if ( (((int)unk_5DFDEC >> 16) & 0x3FFu) >= 0x200 )
        return v10 + v8;
      v8 -= v10;
    }
  }
  return v8;
}

// 0x004F2910
int CCBRoleState::SetRoleHP(int roleIdx, int value)
{
  int RoleNum; // ebx
  int result; // eax
  int v6; // ebx
  int p_DWORD; // [esp+0x10] [ebp-0x18] BYREF
  int v8; // [esp+0x14] [ebp-0x14]
  int v9; // [esp+0x18] [ebp-0x10]
  int nVal4[3]; // [esp+0x1C] [ebp-0xC] BYREF

  p_DWORD = 0xFFFF;
  v8 = 0;
  v9 = 0;
  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(value);
  this->CalcAttackPower(roleIdx);
  this->CalcDefensePower(roleIdx);
  result = *(_DWORD *)(RoleNum + 696);
  if ( result != -1 )
  {
    switch ( result )
    {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
        result = ((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1))->CreateObj(&dword_5D8F0C, 0, 0x40u);
        break;
      case 5:
        LOBYTE(result) = this->CanUseSkill(roleIdx);
        break;
      case 6:
        result = (int)&this->m_Role[0].byMagicUseTime[9][446 * roleIdx + 1] + 1;
        *(_DWORD *)result -= *(_DWORD *)(RoleNum + 704);
        break;
      case 7:
        result = this->GetRoleLevel(roleIdx);
        break;
      case 8:
        result = (int)&this->m_Role[0].byMagicUseTime[2][446 * roleIdx + 1] + 1;
        *(_DWORD *)result -= *(_DWORD *)(RoleNum + 704);
        break;
      case 9:
        result = ((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1))->CreateObj(&dword_5D8EF8, 0, 0x40u);
        break;
      case 10:
        LOBYTE(result) = this->CheckBuff(roleIdx);
        break;
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
        result = ((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1))->CreateObj(&dword_5D8EE0, 0, 0x40u);
        break;
      case 16:
        p_DWORD = 6113;
        result = (int)((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD);
        if ( result )
        {
          v9 = *(_DWORD *)(result + 8);
          v8 = 1;
          p_DWORD = 6113;
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          result = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(8, 0, 1);
          v6 = result;
          if ( result != -1 )
          {
            this->CheckRoleStatus((int)nVal4);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v6, 0 /* TODO: (int)CCBStage::ProcWait */, 0, 0, 0, nVal4, 0, 1080033280);
            LOBYTE(result) = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v6);
          }
        }
        break;
      default:
        return result;
    }
  }
  return result;
}

// 0x004F2BB0
int CCBRoleState::SetRoleField(int roleIdx, int value)
{
  if ( (_BYTE)value == 1 )
    return *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * roleIdx + 1];
  else
    return *(_DWORD *)&this->m_Role[0].bMagicMastered[7][892 * roleIdx + 3];
}

// 0x004F2BF0
int CCBRoleState::GetRoleGPBak(int nVal, char pData)
{
  if ( pData == 1 )
    return *(_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[0][446 * nVal + 1] + 1);
  else
    return *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * nVal + 5];
}

// 0x004F2C30
void * CCBRoleState::GetRole(int index)
{
  char v3; // [esp+0x8] [ebp+0x8]

  if ( v3 == 1 )
    return *(void **)((char *)&this->m_Role[0].byMagicUseTime[0][446 * index + 5] + 1);
  else
    return *(void **)((char *)&this->m_Role[0].byMagicUseTime[0][446 * index + 3] + 1);
}

// 0x004F3020
int CCBRoleState::CalcAttackPower(int roleIdx)
{
  int v2; // edi
  int v4; // edx
  char *v5; // esi
  int v6; // eax
  int v7; // ecx
  CCBStage *v8; // ecx
  int RoleIndex; // edi
  int v10; // esi
  int v11; // ebx
  _DWORD pData[11]; // [esp+0xC] [ebp-0x40] BYREF
  int p_DWORD[3]; // [esp+0x38] [ebp-0x14] BYREF
  int v15; // [esp+0x44] [ebp-0x8]
  int v16; // [esp+0x48] [ebp-0x4]
  int v17; // [esp+0x58] [ebp+0xC]
  float v18; // [esp+0x58] [ebp+0xC]
  char v19; // [esp+0x5C] [ebp+0x10]

  v2 = v17;
  if ( !v17 )
    return 0;
  v4 = roleIdx;
  v5 = &this->m_sCombatDialog[892 * roleIdx];
  if ( !v5[578] )
    return 0;
  v16 = *((_DWORD *)v5 + 149);
  if ( v17 < 0 )
  {
    v18 = (double)v17 * *((float *)v5 + 164) * 0.0099999998;
    v15 = (int)v18;
    v2 -= v15;
    v17 = v2;
  }
  v6 = v2 + *((_DWORD *)v5 + 149);
  *((_DWORD *)v5 + 149) = v6;
  v7 = *((_DWORD *)v5 + 150);
  if ( v6 <= v7 )
    v7 = v6 < 0 ? 0 : v6;
  *((_DWORD *)v5 + 149) = v7;
  if ( v19 )
  {
    memset(pData, 0, sizeof(pData));
    v8 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
    pData[2] = roleIdx;
    pData[3] = roleIdx;
    LOBYTE(pData[10]) = 1;
    pData[0] = 259;
    pData[1] = 0;
    LOWORD(pData[4]) = 0;
    RoleIndex = ((CCBStage *)v8)->GetRoleIndex(6, pData, 1);
    if ( RoleIndex != -1 )
    {
      if ( v17 <= 0 )
      {
        if ( v16 + v17 < 0 )
          v17 = -v16;
      }
      else
      {
        v10 = *((_DWORD *)v5 + 150) - v16;
        if ( v17 > v10 )
          v17 = v10;
      }
      this->CheckRoleStatus((int)p_DWORD);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::GetRoleTaskNum */, 0, 0, 0, p_DWORD, -1082130432, 1075838976);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
    }
    v4 = roleIdx;
    v2 = v17;
  }
  v11 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
  if ( *(_BYTE *)(v11 + 133) )
    ((CCBUI *)*(CCBUI **)(v11 + 28))->HandleRoleStateDialog(v4);
  return v2;
}

// 0x004F31C0
int CCBRoleState::CalcDefensePower(int roleIdx)
{
  int v2; // edi
  char *v4; // esi
  int v5; // eax
  int v6; // ecx
  CCBStage *v7; // ecx
  int RoleIndex; // edi
  int v9; // esi
  int v10; // ebx
  _DWORD pData[11]; // [esp+0xC] [ebp-0x40] BYREF
  int p_DWORD[3]; // [esp+0x38] [ebp-0x14] BYREF
  int v14; // [esp+0x44] [ebp-0x8]
  int v15; // [esp+0x48] [ebp-0x4]
  int v16; // [esp+0x58] [ebp+0xC]
  float v17; // [esp+0x58] [ebp+0xC]
  char v18; // [esp+0x5C] [ebp+0x10]

  v2 = v16;
  if ( !v16 )
    return 0;
  v4 = &this->m_sCombatDialog[892 * roleIdx];
  if ( !v4[578] || this->GetRoleField(roleIdx, 23) && v16 > 0 )
    return 0;
  v15 = *((_DWORD *)v4 + 151);
  if ( v16 < 0 )
  {
    v17 = (double)v16 * *((float *)v4 + 165) * 0.0099999998;
    v14 = (int)v17;
    v2 -= v14;
    v16 = v2;
  }
  v5 = v2 + *((_DWORD *)v4 + 151);
  *((_DWORD *)v4 + 151) = v5;
  v6 = *((_DWORD *)v4 + 152);
  if ( v5 <= v6 )
    v6 = v5 < 0 ? 0 : v5;
  *((_DWORD *)v4 + 151) = v6;
  if ( v18 )
  {
    memset(pData, 0, sizeof(pData));
    v7 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
    pData[2] = roleIdx;
    pData[3] = roleIdx;
    LOBYTE(pData[10]) = 1;
    pData[0] = 259;
    pData[1] = 0;
    LOWORD(pData[4]) = 0;
    RoleIndex = ((CCBStage *)v7)->GetRoleIndex(6, pData, 1);
    if ( RoleIndex != -1 )
    {
      if ( v16 <= 0 )
      {
        if ( v15 + v16 < 0 )
          v16 = -v15;
      }
      else
      {
        v9 = *((_DWORD *)v4 + 152) - v15;
        if ( v16 > v9 )
          v16 = v9;
      }
      this->CheckRoleStatus((int)p_DWORD);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::GetRoleTaskNum */, 0, 0, 0, p_DWORD, -1082130432, 1075838976);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
    }
    v2 = v16;
  }
  v10 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
  if ( *(_BYTE *)(v10 + 133) )
    ((CCBUI *)*(CCBUI **)(v10 + 28))->HandleRoleStateDialog(roleIdx);
  return v2;
}

// 0x004F3380
int CCBRoleState::GetMaxHP(int roleIdx)
{
  int v4; // [esp+0x14] [ebp+0x8]
  int v5; // [esp+0x18] [ebp+0xC]

  if ( (int)this->GetRole(roleIdx) < (int)abs32(v5) )
    this->GetRole(roleIdx);
  this->CalcDefensePower(roleIdx);
  return this->CalcDefensePower(v4);
}

// 0x004F33D0
int CCBRoleState::GetMaxMP(int roleIdx)
{
  int v4; // [esp+0x14] [ebp+0x8]
  int v5; // [esp+0x18] [ebp+0xC]

  if ( this->GetRoleGPBak(roleIdx, 0) < (int)abs32(v5) )
    this->GetRoleGPBak(roleIdx, 0);
  this->CalcAttackPower(roleIdx);
  return this->CalcAttackPower(v4);
}

// 0x004F3420
int CCBRoleState::GetTotalRounds()
{
  return *(_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[2][5] + 1);
}

// 0x004F3430
char CCBRoleState::CheckBuff(int roleIdx)
{
  int RoleIndex; // edi
  int v4; // esi
  char result; // al
  int p_DWORD[3]; // [esp+0x10] [ebp-0xC] BYREF
  int v7; // [esp+0x24] [ebp+0x8]

  *(_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[2][5] + 1) += v7;
  if ( v7 < 0 )
  {
    RoleIndex = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(8, 0, 1);
    if ( RoleIndex != -1 )
    {
      this->CheckRoleStatus((int)p_DWORD);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcWait */, 0, 0, 0, p_DWORD, 0, 1077936128);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
    }
  }
  v4 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
  result = *(_BYTE *)(v4 + 133);
  if ( result )
    return ((CCBRoleState *)*(CCBRoleState **)(v4 + 28))->HandleDlgMessage();
  return result;
}

// 0x004F34E0
char CCBRoleState::CanUseSkill(int roleIdx)
{
  char result; // al
  int *v3; // esi
  bool v4; // sf
  CScreenMode *Instance; // eax
  CScreenMode *v6; // eax
  int v7; // [esp+0xC] [ebp+0x8]

  result = this->m_Role[0].bMagicMastered[5][4];
  if ( result )
  {
    result = roleIdx;
    if ( roleIdx != 4 )
    {
      v3 = (int *)((char *)&this->m_Role[0].byMagicUseTime[2][446 * roleIdx + 3] + 1);
      v4 = v7 < 0;
      *v3 += v7;
      if ( v7 > 0 )
      {
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition("wa010", 1);
        v4 = v7 < 0;
      }
      if ( v4 )
      {
        v6 = CScreenMode::GetInstance();
        ((CScreenMode *)v6)->AudioSetPosition("wa048", 1);
      }
      if ( *v3 < 0 )
        *v3 = 0;
      if ( *v3 > 999 )
        *v3 = 999;
    }
  }
  return result;
}

// 0x004F3570
int CCBRoleState::CalcMagicAttack(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return 0;
}

// 0x004F3620
int CCBRoleState::CalcMPRegen(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return 0;
}

// 0x004F36D0
int CCBRoleState::CalcMagicDefense(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return 99999;
}

// 0x004F37A0
int CCBRoleState::GetAttackBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+0xC] [ebp+0x8]
  float roleIdxb; // [esp+0xC] [ebp+0x8]

  v2 = &this->m_sCombatDialog[892 * roleIdx];
  if ( v2[1147] )
  {
    v3 = *((_DWORD *)v2 + 153);
    roleIdxa = (double)v3 * 0.25;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1148];
    result = *((_DWORD *)v2 + 153);
    if ( v5 )
    {
      roleIdxb = (double)result * -0.25;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F3820
int CCBRoleState::GetDefenseBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+0xC] [ebp+0x8]
  float roleIdxb; // [esp+0xC] [ebp+0x8]

  v2 = &this->m_sCombatDialog[892 * roleIdx];
  if ( v2[1149] )
  {
    v3 = *((_DWORD *)v2 + 154);
    roleIdxa = (double)v3 * 0.25;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1150];
    result = *((_DWORD *)v2 + 154);
    if ( v5 )
    {
      roleIdxb = (double)result * -0.25;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F38A0
int CCBRoleState::GetRoleState(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+0xC] [ebp+0x8]
  float roleIdxb; // [esp+0xC] [ebp+0x8]

  v2 = &this->m_sCombatDialog[892 * roleIdx];
  if ( v2[1151] )
  {
    v3 = *((_DWORD *)v2 + 156);
    roleIdxa = (double)v3 * 0.25;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1152];
    result = *((_DWORD *)v2 + 156);
    if ( v5 )
    {
      roleIdxb = (double)result * -0.25;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F3920
int CCBRoleState::GetSpeedBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+0xC] [ebp+0x8]
  float roleIdxb; // [esp+0xC] [ebp+0x8]

  v2 = &this->m_sCombatDialog[892 * roleIdx];
  if ( v2[1153] )
  {
    v3 = *((_DWORD *)v2 + 155);
    roleIdxa = (double)v3 * 0.25;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1154];
    result = *((_DWORD *)v2 + 155);
    if ( v5 )
    {
      roleIdxb = (double)result * -0.25;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F39A0
int CCBRoleState::GetRoleLevel(int roleIdx)
{
  int v2; // edi
  _DWORD *v3; // edx
  int v5; // [esp+0x10] [ebp+0x8]

  v2 = *(_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[1][446 * roleIdx + 5] + 1);
  v3 = (_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[1][446 * roleIdx + 5] + 1);
  *v3 = v2 + v5;
  if ( v2 + v5 < 0 )
    *v3 = 0;
  ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdSlot(roleIdx);
  return v2;
}

// 0x004F39F0
int CCBRoleState::GetRoleExp(int roleIdx)
{
  int result; // eax
  int i; // edx
  int v4; // [esp+0x10] [ebp+0x8]

  result = 0;
  for ( i = 0; i < 8; ++i )
    result += *((unsigned __int8 *)&this->m_Role[1].dwMagicID[2][223 * roleIdx + 2 + 2 * v4] + i + 1);
  return result;
}

// 0x004F3A30
char CCBRoleState::SetRoleFlag(int roleIdx, char flag)
{
  BYTE1(this->m_Role[1].dwMagicID[8][223 * roleIdx + 5]) = flag;
  return flag;
}

// 0x004F3A50
int CCBRoleState::GetRoleAttr(int roleIdx)
{
  int v3; // ecx
  int v4; // esi

  v3 = this->SetRoleField(roleIdx, 0);
  v4 = *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * roleIdx + 1];
  if ( v3 == v4 )
    return 1;
  if ( v3 >= v4 / 2 && v3 < v4 )
    return 2;
  if ( v3 < v4 / 4 )
    return (v3 <= 0) + 4;
  return 3;
}

// 0x004F3AD0
int CCBRoleState::CalcMPCost(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return -1;
}

// 0x004F3B90
int CCBRoleState::GetRoleMP(int roleIdx)
{
  int result; // eax
  _DWORD *v3; // [esp+0x8] [ebp+0x8]
  _DWORD *v4; // [esp+0xC] [ebp+0xC]

  *v3 = 0;
  result = roleIdx - 1;
  *v4 = 11;
  if ( roleIdx == 1 )
  {
    *v4 = 5;
  }
  else
  {
    result = roleIdx - 2;
    if ( roleIdx == 2 )
      *v3 = 5;
  }
  return result;
}

// 0x004F3BC0
int CCBRoleState::GetRoleHP(int roleIdx)
{
  if ( this->m_Role[0].bMagicMastered[5][892 * roleIdx + 4] )
    return (roleIdx >= 5) + 1;
  else
    return 0;
}

// 0x004F3C00
int CCBRoleState::IsForce1(int force)
{
  if ( force == 1 )
    return 2;
  else
    return force == 2;
}

// 0x004F3C20
char CCBRoleState::IsPlayerTeam(int force)
{
  char result; // al

  switch ( force )
  {
    case 0:
    case 6:
    case 8:
    case 10:
    case 12:
    case 20:
    case 21:
    case 22:
    case 23:
    case 26:
    case 27:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x004F3C70
char CCBRoleState::GetRoleForce(int roleIdx)
{
  int v3; // esi
  char *v4; // ebx

  v3 = 1;
  v4 = (char *)&this->m_Role[1].dwMagicID[8][223 * roleIdx + 5] + 2;
  while ( v4[v3] != 1 || this->IsPlayerTeam(v3) )
  {
    if ( ++v3 >= 27 )
      return 0;
  }
  return 1;
}

// 0x004F3CC0
bool CCBRoleState::IsRoleInForce(int roleIdx)
{
  bool result; // al
  char *v3; // ecx

  result = 1;
  v3 = &this->m_sCombatDialog[892 * roleIdx];
  if ( v3[1142] != 1 && v3[1143] != 1 && v3[1144] != 1 && v3[1145] != 1 )
    return v3[1146] == 1;
  return result;
}

// 0x004F3D10
char CCBRoleState::CanRoleAct(int roleIdx)
{
  if ( this->GetRoleField(roleIdx, 26) )
    return 0;
  if ( !this->IsRoleInForce(roleIdx) )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    this->ProcessRound(roleIdx);
  }
  return 1;
}

// 0x004F3D90
char CCBRoleState::GetRoleField(int roleIdx, int fieldOff)
{
  return *((_BYTE *)&this->m_Role[1].dwMagicID[8][223 * roleIdx + 5] + fieldOff + 2);
}

// 0x004F3DC0
int CCBRoleState::FindFirstEnemySlot(int roleIdx)
{
  int v3; // esi

  if ( !this->m_Role[0].bMagicMastered[5][5] )
    return 0;
  v3 = 1;
  while ( !*((_BYTE *)&this->m_Role[1].dwMagicID[8][223 * roleIdx + 5] + v3 + 2) || this->IsPlayerTeam(v3) )
  {
    if ( ++v3 >= 27 )
      return 0;
  }
  return v3;
}

// 0x004F3E20
char CCBRoleState::ProcessRound(unsigned int dwVal)
{
  char *v3; // eax
  int i; // edi
  CCBStage *v5; // ecx
  int RoleIndex; // eax
  int v7; // edi
  int v8; // ecx
  unsigned int v9; // ebp
  int v10; // edi
  CScreenMode *Instance; // eax
  int v12; // edi
  int v13; // edx
  _BYTE *v14; // edi
  void ( ***v15)(_DWORD, int); // ecx
  CCBStage *v16; // ecx
  int v17; // edi
  int v18; // edi
  CScreenMode *v19; // eax
  const void *v21; // [esp-0x8] [ebp-0x50]
  char *v22; // [esp-0x8] [ebp-0x50]
  int p_DWORD[3]; // [esp+0x10] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x1C] [ebp-0x2C] BYREF
  int force; // [esp+0x50] [ebp+0x8]
  int forcea; // [esp+0x50] [ebp+0x8]
  char v27; // [esp+0x54] [ebp+0xC]
  char v28; // [esp+0x58] [ebp+0x10]

  LOBYTE(v3) = this->GetRoleField(dwVal, 23);
  if ( (_BYTE)v3 && force != 23 )
    return (char)v3;
  if ( force < 1 || force > 5 )
    goto LABEL_7;
  if ( v27 )
  {
    LOBYTE(v3) = this->IsRoleInForce(dwVal);
    if ( (_BYTE)v3 )
      return (char)v3;
LABEL_7:
    if ( v27 )
    {
      if ( force >= 1 && force <= 5 )
      {
        v3 = &this->m_sCombatDialog[892 * dwVal];
        *(_DWORD *)(v3 + 1142) = 0;
        v3[1146] = 0;
        if ( v3[1167] )
          return (char)v3;
      }
      if ( force >= 14 && force <= 23 )
      {
        for ( i = 14; i <= 23; ++i )
          this->ProcessRound(dwVal);
      }
      if ( !this->IsPlayerTeam(force)
        && force != 24
        && force != 25
        && *(int *)&this->m_Role[0].bMagicMastered[7][892 * dwVal + 3] > 0 )
      {
        memset(pData, 0, sizeof(pData));
        v5 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
        LOBYTE(pData[10]) = 1;
        pData[2] = dwVal;
        pData[0] = 0;
        pData[1] = 0;
        pData[3] = dwVal;
        LOWORD(pData[4]) = 0;
        RoleIndex = ((CCBStage *)v5)->GetRoleIndex(10, pData, 1);
        v7 = RoleIndex;
        if ( RoleIndex != -1 )
        {
          ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::HandleKeyFriend */, 0, 0, 0, p_DWORD, -1082130432, 0);
          ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v7);
        }
      }
    }
  }
  v8 = force;
  v9 = 892 * dwVal;
  v3 = (char *)&this->m_Role[1].dwMagicID[8][223 * dwVal + 5] + force + 2;
  *v3 = v27;
  v10 = force + 446 * dwVal;
  forcea = v10;
  *(_WORD *)&this->m_Role[1].bMagicMastered[4][2 * v10 + 1] = 0;
  *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 0;
  if ( v27 )
  {
    switch ( v8 )
    {
      case 1:
        *(_WORD *)&this->m_Role[1].bMagicMastered[4][2 * v10 + 1] = 3;
        goto LABEL_24;
      case 2:
        *(_WORD *)&this->m_Role[1].bMagicMastered[4][2 * v10 + 1] = 3;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 2;
        goto LABEL_25;
      case 3:
        *(_WORD *)&this->m_Role[1].bMagicMastered[4][2 * v10 + 1] = 0;
LABEL_24:
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        goto LABEL_25;
      case 4:
      case 5:
        *(_WORD *)&this->m_Role[1].bMagicMastered[4][2 * v10 + 1] = 0;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 0x7FFF;
LABEL_25:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 6:
        this->m_Role[1].bMagicMastered[0][v9 + 4] = 0;
        this->m_Role[1].bMagicMastered[0][v9 + 5] = 0;
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        goto LABEL_38;
      case 7:
        this->m_Role[1].bMagicMastered[0][v9 + 4] = 0;
        this->m_Role[1].bMagicMastered[0][v9 + 5] = 0;
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        goto LABEL_41;
      case 8:
        this->m_Role[1].bMagicMastered[1][v9] = 0;
        this->m_Role[1].bMagicMastered[1][v9 + 1] = 0;
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        goto LABEL_38;
      case 9:
        this->m_Role[1].bMagicMastered[1][v9] = 0;
        this->m_Role[1].bMagicMastered[1][v9 + 1] = 0;
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        goto LABEL_41;
      case 10:
        this->m_Role[1].bMagicMastered[1][v9 + 2] = 0;
        this->m_Role[1].bMagicMastered[1][v9 + 3] = 0;
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        goto LABEL_38;
      case 11:
        this->m_Role[1].bMagicMastered[1][v9 + 2] = 0;
        this->m_Role[1].bMagicMastered[1][v9 + 3] = 0;
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        goto LABEL_41;
      case 12:
        this->m_Role[1].bMagicMastered[1][v9 + 4] = 0;
        this->m_Role[1].bMagicMastered[1][v9 + 5] = 0;
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdSlot(dwVal);
LABEL_38:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 13:
        this->m_Role[1].bMagicMastered[1][v9 + 4] = 0;
        this->m_Role[1].bMagicMastered[1][v9 + 5] = 0;
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdSlot(dwVal);
LABEL_41:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 14:
        ((Combat *)this)->HandleControlCmd(dwVal);
        LOBYTE(v3) = v28;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 4;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 15:
        LOBYTE(v3) = v28;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 16:
        LOBYTE(v3) = v28;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 17:
        ((Combat *)this)->HandleControlCmd(dwVal);
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        LOBYTE(v3) = v28;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = (((int)unk_5DFDEC >> 16) & 0x7FFF)
                                                                                   % 7
                                                                                   + 2;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 18:
        ((Combat *)this)->HandleControlCmd(dwVal);
        ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * dwVal + 24))->DangerForceRelease(0);
        LOBYTE(v3) = v28;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 19:
        ((Combat *)this)->HandleControlCmd(dwVal);
        LOBYTE(v3) = v28;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 20:
        if ( dwVal > 4 )
          *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        else
          *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 3;
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 21:
        LOBYTE(v3) = v28;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 4;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 22:
        LOBYTE(v3) = v28;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 4;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 23:
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 5;
        if ( this->IsRoleAlive(dwVal) )
        {
          v12 = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(22, 0, 1);
          if ( v12 != -1 )
          {
            this->CheckRoleStatus((int)p_DWORD);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v12, 0 /* TODO: (int)CCBStageRole::TaskBlendToReady */, 0, 0, 0, p_DWORD, 0, 1065353216);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v12);
          }
        }
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = &g_EffMgr;
        break;
      case 24:
        v3 = &this->m_Role[0].bMagicMastered[7][v9 + 3];
        v13 = *(_DWORD *)&this->m_Role[0].bMagicMastered[8][v9 + 1] / 10;
        if ( *(_DWORD *)v3 > v13 )
          *(_DWORD *)v3 = v13;
        return (char)v3;
      case 25:
        v3 = *(char **)&this->m_Role[0].bMagicMastered[7][v9 + 3];
        if ( (int)v3 > 0 )
          *(_DWORD *)&this->m_Role[0].bMagicMastered[7][v9 + 3] = 0;
        return (char)v3;
      case 26:
        *v3 = 1;
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][v10] + 1) = 0x7FFF;
        return (char)v3;
      default:
        return (char)v3;
    }
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v21, 1);
  }
  else
  {
    switch ( v8 )
    {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        if ( v28 )
        {
          v22 = "wd006";
          break;
        }
        goto LABEL_91;
      case 12:
      case 13:
        ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdSlot(dwVal);
        goto LABEL_91;
      case 14:
        ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * dwVal + 24))->DangerForceRelease(0);
        goto LABEL_91;
      case 20:
      case 21:
      case 22:
        goto LABEL_86;
      case 23:
        if ( this->IsRoleAlive(dwVal) )
        {
          v18 = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(22, 0, 1);
          if ( v18 != -1 )
          {
            this->CheckRoleStatus((int)p_DWORD);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v18, 0 /* TODO: (int)CCBStageRole::TaskBlendToEnd */, 0, 0, 0, p_DWORD, 0, 1065353216);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v18);
          }
        }
LABEL_86:
        if ( !v28 )
          goto LABEL_91;
        v22 = (char *)&g_EffMgr;
        break;
      case 25:
        if ( this->m_Role[0].bMagicMastered[5][v9 + 5] )
          goto LABEL_91;
        this->m_Role[0].bMagicMastered[5][v9 + 5] = 1;
        *(_DWORD *)&this->m_Role[0].bMagicMastered[7][v9 + 3] = 0;
        memset((char *)&this->m_Role[1].dwMagicID[8][v9 / 4 + 5] + 2, 0, 0x18u);
        v14 = &this->m_Role[1].bMagicMastered[3][v9 + 4];
        *(_WORD *)v14 = 0;
        v14[2] = 0;
        memset(&this->m_Role[1].bMagicMastered[4][v9 + 1], 0, 0x34u);
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[1][v9 / 2 + 5] + 1) = 0;
        memset((char *)&this->m_Role[1].byMagicUseTime[2][v9 / 2] + 1, 0, 0x34u);
        *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[6][v9 / 2 + 2] + 1) = 0;
        BYTE1(this->m_Role[1].dwMagicID[8][v9 / 4 + 5]) = 0;
        ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * dwVal + 24))->DangerForceRelease(0);
        ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * dwVal + 24))->Release(1);
        v15 = *(void ( ****)(_DWORD, int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                                   + 4 * dwVal
                                                   + 76);
        (**v15)(v15, 1);
        ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->SetCmdParam(dwVal, 0);
        ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdData(dwVal);
        if ( !((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1]
                                                                                     + 1)
                                                               + 4 * dwVal
                                                               + 24))->ForceEndTaskByPFN() )
        {
          memset(pData, 0, sizeof(pData));
          v16 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
          LOBYTE(pData[10]) = 1;
          pData[2] = dwVal;
          pData[1] = 259;
          v17 = ((CCBStage *)v16)->GetRoleIndex(9, pData, 1);
          if ( v17 != -1 )
          {
            p_DWORD[2] = pData[3];
            p_DWORD[1] = pData[2];
            p_DWORD[0] = 0;
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v17, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, p_DWORD, -1082130432, 0);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v17, 0 /* TODO: (int)CCBStage::ProcShowItemName */, 0, 0, 0, p_DWORD, -1082130432, 0);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v17, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, p_DWORD, -1082130432, 0);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v17);
          }
        }
        if ( !v28 )
          goto LABEL_91;
        v22 = (char *)&g_EffMgr;
        break;
      default:
        goto LABEL_91;
    }
    v19 = CScreenMode::GetInstance();
    ((CScreenMode *)v19)->AudioSetPosition(v22, 1);
LABEL_91:
    *(_WORD *)&this->m_Role[1].bMagicMastered[4][2 * forcea + 1] = 0;
    *(unsigned __int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][forcea] + 1) = 0;
    LOBYTE(v3) = forcea;
  }
  return (char)v3;
}

// 0x004F48C0
void CCBRoleState::TickDebuffs(int roleIdx)
{
  int v4; // ebx
  int v5; // ecx
  __int16 v6; // dx
  _WORD *v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  char *v11; // [esp+0x14] [ebp-0x4]
  __int16 *roleIdxa; // [esp+0x20] [ebp+0x8]

  v4 = 1;
  v11 = (char *)&this->m_Role[1].dwMagicID[8][223 * roleIdx + 5] + 2;
  do
  {
    if ( v11[v4] )
    {
      v5 = 446 * roleIdx + v4;
      v6 = *(_WORD *)&this->m_Role[1].bMagicMastered[4][2 * v5 + 1];
      v7 = &this->m_Role[1].bMagicMastered[4][2 * v5 + 1];
      if ( v6 <= 0 )
      {
        roleIdxa = (__int16 *)((char *)&this->m_Role[1].byMagicUseTime[2][446 * roleIdx + v4] + 1);
        if ( *roleIdxa > 0 )
        {
          switch ( v4 )
          {
            case 1:
              v8 = this->SetRoleField(roleIdx, 1);
              ((CCBSystem *)this)->AddCommand(roleIdx, 3 * v8 / -4, 1);
              break;
            case 2:
              v9 = this->SetRoleField(roleIdx, 1);
              goto LABEL_10;
            case 3:
              v9 = this->SetRoleField(roleIdx, 0);
LABEL_10:
              ((CCBSystem *)this)->AddCommand(roleIdx, v9 / -2, 1);
              break;
            case 4:
              v10 = this->SetRoleField(roleIdx, 1);
              ((CCBSystem *)this)->AddCommand(roleIdx, 5 * v10 / -100, 1);
              break;
            case 5:
              if ( *roleIdxa == 0x7FFF )
                flt_17AA550[roleIdx] = (double)this->SetRoleField(roleIdx, 1) * -0.02;
              ((CCBSystem *)this)->AddCommand(roleIdx, (int)flt_17AA550[roleIdx], 1);
              flt_17AA550[roleIdx] = flt_17AA550[roleIdx] * 1.5;
              break;
            default:
              break;
          }
        }
        if ( --*roleIdxa <= 0 )
        {
          this->ProcessRound(roleIdx);
          *roleIdxa = 0;
          if ( v4 == 23 )
          {
            if ( this->IsRoleAlive(roleIdx) )
              ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * roleIdx + 24))->ForceRelease(1);
          }
        }
      }
      else
      {
        *v7 = v6 - 1;
      }
    }
    ++v4;
  }
  while ( v4 <= 23 );
}

// 0x004F4B90
unsigned int CCBRoleState::CalcMagicDamage(int roleIdx, int nMagicID)
{
  int SlotCount; // ebx
  int v5; // esi
  int v7; // eax
  unsigned int v8; // eax
  _BYTE pOut[12]; // [esp+0x10] [ebp-0x18] BYREF
  _BYTE v10[12]; // [esp+0x1C] [ebp-0xC] BYREF

  this->GetRoleHP(roleIdx);
  SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
  v5 = 0;
  if ( SlotCount <= 0 )
    return -1;
  while ( *((int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut) + 1) <= 0
       || *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v10) != nMagicID )
  {
    if ( ++v5 >= SlotCount )
      return -1;
  }
  v7 = *((_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v10) + 2);
  if ( !*(_BYTE *)(v7 + 631) )
    return *(__int16 *)(v7 + 644);
  if ( *(_BYTE *)(v7 + 631) != 1 )
    return 0;
  v8 = (int)((unsigned __int64)(1374389535LL
                              * *(__int16 *)(v7 + 644)
                              * *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * roleIdx + 1]) >> 32) >> 5;
  return (v8 >> 31) + v8;
}

// 0x004F4C80
unsigned int CCBRoleState::CalcSkillDamage(int roleIdx, int nSkillID)
{
  int SlotCount; // ebx
  int v5; // esi
  int v7; // eax
  unsigned int v8; // eax
  _BYTE pOut[12]; // [esp+0x10] [ebp-0x18] BYREF
  _BYTE v10[12]; // [esp+0x1C] [ebp-0xC] BYREF

  this->GetRoleHP(roleIdx);
  SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
  v5 = 0;
  if ( SlotCount <= 0 )
    return -1;
  while ( *((int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut) + 1) <= 0
       || *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v10) != nSkillID )
  {
    if ( ++v5 >= SlotCount )
      return -1;
  }
  v7 = *((_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v10) + 2);
  switch ( *(_BYTE *)(v7 + 631) )
  {
    case 0:
      return *(__int16 *)(v7 + 644);
    case 1:
      v8 = (int)((unsigned __int64)(1374389535LL
                                  * *(__int16 *)(v7 + 644)
                                  * *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * roleIdx + 1]) >> 32) >> 5;
      return (v8 >> 31) + v8;
    case 2:
      return *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * roleIdx + 1]
           - *(_DWORD *)&this->m_Role[0].bMagicMastered[7][892 * roleIdx + 3];
    default:
      return 0;
  }
}

// 0x004F4DA0
int CCBRoleState::ProcessAttackResult(int roleIdx)
{
  int v2; // ebx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int RoleNum; // eax
  int v10; // ebp
  int v11; // esi
  int *v12; // ebx
  int v13; // edi
  int v14; // eax
  bool v15; // cc
  int v16; // esi
  int *v17; // ebp
  CCBStageRole *Role; // ecx
  int v19; // [esp+0x10] [ebp-0x48]
  int v21; // [esp+0x18] [ebp-0x40]
  int v22; // [esp+0x1C] [ebp-0x3C]
  int *v23; // [esp+0x20] [ebp-0x38]
  signed int v24; // [esp+0x24] [ebp-0x34]
  int v25; // [esp+0x28] [ebp-0x30]
  _DWORD pOut[11]; // [esp+0x2C] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x5C] [ebp+0x4]
  char v28; // [esp+0x60] [ebp+0x8]
  int v29; // [esp+0x64] [ebp+0xC]

  v2 = roleIdx;
  memset(pOut, 0, sizeof(pOut));
  v19 = 0;
  v25 = -1;
  v24 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 261;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v5 = this->GetRoleHP(roleIdx) - 1;
  if ( v5 )
  {
    if ( v5 != 1 )
      return 0;
    roleIdxa = dword_17AA450;
    v6 = 760;
    while ( 1 )
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(_DWORD *)&this->m_Role[0].bMagicMastered[1][892 * v2 + 3]);
      v8 = *(_DWORD *)(v6 + v7);
      if ( v8 )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*(_DWORD *)(v6 + v7));
        if ( *(_BYTE *)(RoleNum + 4) == 3 )
        {
          if ( v28 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) == 2 )
              goto LABEL_14;
          }
          else if ( !v28 && *(_BYTE *)(RoleNum + 577) == 1 )
          {
LABEL_14:
            pOut[1] = v8;
            if ( this->GetRoleAI(pOut) )
            {
              *roleIdxa = v8;
              ++v19;
              ++roleIdxa;
            }
          }
        }
      }
      v6 += 4;
      if ( v6 >= 776 )
      {
        if ( !v19 )
          return 0;
LABEL_37:
        v16 = 0;
        if ( v19 <= 0 )
          return 0;
        v17 = dword_17AA450;
        do
        {
          Role = ((CCBStage *)this)->GetRole(v2);
          if ( (int)abs32((int)Role - v29) < v24 )
          {
            v25 = v16;
            v24 = abs32(abs32((int)Role) - abs32(v29));
          }
          ++v16;
          ++v17;
        }
        while ( v16 < v19 );
        if ( v25 == -1 )
          return 0;
        else
          return dword_17AA450[v25];
      }
    }
  }
  v21 = 0;
  v22 = 936;
  while ( 2 )
  {
    v10 = 0;
    v11 = 892 * v2;
    v23 = (int *)(4 * v19 + 24814672);
    v12 = (int *)(&this->m_Role[1].bCanAction + 892 * v2 + v21);
    do
    {
      v13 = *v12;
      if ( *v12 )
      {
        if ( this->m_sCombatDialog[v10 + v11 + v22] )
        {
          v14 = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v12);
          if ( *(_BYTE *)(v14 + 4) == 3 )
          {
            if ( v28 == 1 )
            {
              if ( *(_BYTE *)(v14 + 577) != 2 )
                goto LABEL_32;
            }
            else if ( v28 || *(_BYTE *)(v14 + 577) != 1 )
            {
              goto LABEL_32;
            }
            pOut[1] = v13;
            if ( this->GetRoleAI(pOut) )
            {
              *v23 = v13;
              ++v19;
              ++v23;
            }
          }
        }
      }
LABEL_32:
      ++v10;
      ++v12;
    }
    while ( v10 < 8 );
    v15 = v22 + 8 < 984;
    v21 += 32;
    v22 += 8;
    if ( v15 )
    {
      v2 = roleIdx;
      continue;
    }
    break;
  }
  if ( v19 )
  {
    v2 = roleIdx;
    goto LABEL_37;
  }
  return 0;
}

// 0x004F5070
int CCBRoleState::ProcessMagicResult(int roleIdx)
{
  int v2; // ebx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int RoleNum; // eax
  int v10; // ebp
  int v11; // esi
  int *v12; // ebx
  int v13; // edi
  int v14; // eax
  bool v15; // cc
  int v16; // edi
  int *v17; // esi
  unsigned int v18; // ebp
  __int64 v19; // rax
  int v20; // eax
  int v21; // [esp+0x10] [ebp-0x48]
  int v23; // [esp+0x18] [ebp-0x40]
  int v24; // [esp+0x1C] [ebp-0x3C]
  int *v25; // [esp+0x20] [ebp-0x38]
  int v26; // [esp+0x24] [ebp-0x34]
  int v27; // [esp+0x28] [ebp-0x30]
  _DWORD pOut[11]; // [esp+0x2C] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x5C] [ebp+0x4]
  char v30; // [esp+0x60] [ebp+0x8]
  int v31; // [esp+0x64] [ebp+0xC]

  v2 = roleIdx;
  memset(pOut, 0, sizeof(pOut));
  v21 = 0;
  v27 = -1;
  v26 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 261;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v5 = this->GetRoleHP(roleIdx) - 1;
  if ( v5 )
  {
    if ( v5 != 1 )
      return 0;
    roleIdxa = dword_17AA350;
    v6 = 760;
    while ( 1 )
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(_DWORD *)&this->m_Role[0].bMagicMastered[1][892 * v2 + 3]);
      v8 = *(_DWORD *)(v6 + v7);
      if ( v8 )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*(_DWORD *)(v6 + v7));
        if ( *(_BYTE *)(RoleNum + 4) == 2 )
        {
          if ( v30 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) == 4 )
              goto LABEL_14;
          }
          else if ( !v30 && *(_BYTE *)(RoleNum + 577) == 3 )
          {
LABEL_14:
            pOut[1] = v8;
            if ( this->GetRoleAI(pOut) )
            {
              *roleIdxa = v8;
              ++v21;
              ++roleIdxa;
            }
          }
        }
      }
      v6 += 4;
      if ( v6 >= 776 )
      {
        if ( !v21 )
          return 0;
LABEL_37:
        v16 = 0;
        if ( v21 <= 0 )
          return 0;
        v17 = dword_17AA350;
        v18 = abs32(v31);
        do
        {
          v19 = (int)(abs32((int)((CCBStage *)this)->GetRole(v2)) - v18);
          v20 = (HIDWORD(v19) ^ v19) - HIDWORD(v19);
          if ( v20 < v26 )
          {
            v26 = v20;
            v27 = v16;
          }
          ++v16;
          ++v17;
        }
        while ( v16 < v21 );
        if ( v27 == -1 )
          return 0;
        else
          return dword_17AA350[v27];
      }
    }
  }
  v23 = 0;
  v24 = 936;
  while ( 2 )
  {
    v10 = 0;
    v11 = 892 * v2;
    v25 = (int *)(4 * v21 + 24814416);
    v12 = (int *)(&this->m_Role[1].bCanAction + 892 * v2 + v23);
    do
    {
      v13 = *v12;
      if ( *v12 )
      {
        if ( this->m_sCombatDialog[v10 + v11 + v24] )
        {
          v14 = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v12);
          if ( *(_BYTE *)(v14 + 4) == 2 )
          {
            if ( v30 == 1 )
            {
              if ( *(_BYTE *)(v14 + 577) != 4 )
                goto LABEL_32;
            }
            else if ( v30 || *(_BYTE *)(v14 + 577) != 3 )
            {
              goto LABEL_32;
            }
            pOut[1] = v13;
            if ( this->GetRoleAI(pOut) )
            {
              *v25 = v13;
              ++v21;
              ++v25;
            }
          }
        }
      }
LABEL_32:
      ++v10;
      ++v12;
    }
    while ( v10 < 8 );
    v15 = v24 + 8 < 984;
    v23 += 32;
    v24 += 8;
    if ( v15 )
    {
      v2 = roleIdx;
      continue;
    }
    break;
  }
  if ( v21 )
  {
    v2 = roleIdx;
    goto LABEL_37;
  }
  return 0;
}

// 0x004F5330
int CCBRoleState::AISelectItem(int roleIdx, char pData)
{
  int v6; // eax
  int v7; // edi
  int *v8; // ebx
  int v9; // eax
  int v10; // esi
  int RoleNum; // eax
  int v12; // ecx
  bool v13; // cc
  int v14; // ebp
  int v15; // edi
  int v16; // eax
  int v17; // [esp+0x10] [ebp-0x40]
  int v19; // [esp+0x18] [ebp-0x38]
  int v20; // [esp+0x1C] [ebp-0x34]
  int *v21; // [esp+0x20] [ebp-0x30]
  _DWORD pOut[11]; // [esp+0x24] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x54] [ebp+0x4]
  int *roleIdxb; // [esp+0x54] [ebp+0x4]

  memset(pOut, 0, sizeof(pOut));
  v17 = 0;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 261;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v6 = this->GetRoleHP(roleIdx) - 1;
  if ( v6 )
  {
    if ( v6 != 1 )
      return 0;
    v7 = 760;
    v8 = dword_17AA250;
    roleIdxa = (int *)&this->m_Role[0].bMagicMastered[1][892 * roleIdx + 3];
    while ( 1 )
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*roleIdxa);
      v10 = *(_DWORD *)(v7 + v9);
      if ( v10 )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*(_DWORD *)(v7 + v9));
        if ( *(_BYTE *)(RoleNum + 4) == 1 )
        {
          if ( pData == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) == 2 )
              goto LABEL_14;
          }
          else if ( !pData && *(_BYTE *)(RoleNum + 577) == 1 )
          {
LABEL_14:
            pOut[1] = v10;
            if ( this->GetRoleAI(pOut) )
            {
              *v8++ = v10;
              ++v17;
            }
          }
        }
      }
      v7 += 4;
      if ( v7 >= 776 )
      {
        v12 = v17;
        v13 = v17 <= 0;
        if ( !v17 )
          return 0;
LABEL_36:
        if ( v13 )
          return -1;
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        return dword_17AA250[(((int)unk_5DFDEC >> 16) & 0x7FFF) % v12];
      }
    }
  }
  v19 = 0;
  v20 = 936;
  do
  {
    v14 = 0;
    v21 = (int *)(4 * v17 + 24814160);
    roleIdxb = (int *)(&this->m_Role[1].bCanAction + 892 * roleIdx + v19);
    do
    {
      v15 = *roleIdxb;
      if ( *roleIdxb )
      {
        if ( this->m_sCombatDialog[892 * roleIdx + v14 + v20] )
        {
          v16 = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*roleIdxb);
          if ( *(_BYTE *)(v16 + 4) == 1 )
          {
            if ( pData == 1 )
            {
              if ( *(_BYTE *)(v16 + 577) != 2 )
                goto LABEL_31;
            }
            else if ( pData || *(_BYTE *)(v16 + 577) != 1 )
            {
              goto LABEL_31;
            }
            pOut[1] = v15;
            if ( this->GetRoleAI(pOut) )
            {
              *v21 = v15;
              ++v17;
              ++v21;
            }
          }
        }
      }
LABEL_31:
      ++v14;
      ++roleIdxb;
    }
    while ( v14 < 8 );
    v13 = v20 + 8 < 984;
    v19 += 32;
    v20 += 8;
  }
  while ( v13 );
  if ( v17 )
  {
    v12 = v17;
    v13 = v17 <= 0;
    goto LABEL_36;
  }
  return 0;
}

// 0x004F55D0
int CCBRoleState::CalcPhysicalDamage(int roleIdx)
{
  signed int v2; // ebp
  int result; // eax
  int v4; // ebx
  char *v5; // eax
  int v6; // esi
  int RoleNum; // edi
  int v8; // esi
  int *v9; // ebx
  CCBStageRole *Role; // ecx
  int v12; // [esp+0x14] [ebp-0x40]
  int *v13; // [esp+0x18] [ebp-0x3C]
  int *v14; // [esp+0x1C] [ebp-0x38]
  int v15; // [esp+0x20] [ebp-0x34]
  _DWORD pOut[11]; // [esp+0x28] [ebp-0x2C] BYREF
  char v17; // [esp+0x5C] [ebp+0x8]
  int v18; // [esp+0x60] [ebp+0xC]

  memset(pOut, 0, sizeof(pOut));
  v12 = 0;
  v15 = -1;
  v2 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  pOut[3] = -1;
  v4 = 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 260;
  v5 = &this->m_sCombatDialog[892 * roleIdx];
  pOut[1] = 0;
  pOut[2] = roleIdx;
  LOWORD(pOut[4]) = 0;
  v14 = dword_17AA150;
  v13 = (int *)(v5 + 712);
  while ( 1 )
  {
    v6 = *v13;
    if ( *v13 )
    {
      if ( v5[v4 + 736] )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v13);
        if ( !*(_BYTE *)(RoleNum + 4) && ((PAL_GDB *)this)->IsRoleAlive(v6) )
        {
          if ( v17 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) != 2 )
              goto LABEL_16;
          }
          else if ( v17 || *(_BYTE *)(RoleNum + 577) != 1 )
          {
            goto LABEL_16;
          }
          pOut[1] = v6;
          if ( this->GetRoleAI(pOut) )
          {
            *v14 = v6;
            ++v12;
            ++v14;
          }
        }
      }
    }
LABEL_16:
    ++v4;
    ++v13;
    if ( v4 >= 6 )
      break;
    v5 = &this->m_sCombatDialog[892 * roleIdx];
  }
  result = v12;
  if ( v12 )
  {
    v8 = 0;
    if ( v12 <= 0 )
      return 0;
    v9 = dword_17AA150;
    do
    {
      Role = ((CCBStage *)this)->GetRole(roleIdx);
      if ( (int)abs32((int)Role - v18) < v2 )
      {
        v15 = v8;
        v2 = abs32(abs32((int)Role) - abs32(v18));
      }
      ++v8;
      ++v9;
    }
    while ( v8 < v12 );
    if ( v15 == -1 )
      return 0;
    else
      return dword_17AA150[v15];
  }
  return result;
}

// 0x004F57A0
int CCBRoleState::CalcMagicDamage(int roleIdx)
{
  signed int v3; // ebx
  int result; // eax
  int v5; // eax
  char *v6; // ecx
  int v7; // esi
  int RoleNum; // edi
  char v9; // al
  bool v10; // cc
  int v11; // esi
  int *v12; // ebp
  CCBStageRole *Role; // ecx
  int v14; // [esp+0x10] [ebp-0x48]
  int *v15; // [esp+0x14] [ebp-0x44]
  int *v16; // [esp+0x18] [ebp-0x40]
  int v17; // [esp+0x1C] [ebp-0x3C]
  int v18; // [esp+0x20] [ebp-0x38]
  _DWORD pOut[11]; // [esp+0x2C] [ebp-0x2C] BYREF
  char v21; // [esp+0x60] [ebp+0x8]
  int v22; // [esp+0x64] [ebp+0xC]

  memset(pOut, 0, sizeof(pOut));
  v14 = 0;
  v18 = -1;
  v3 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  v5 = 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 260;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  v6 = &this->m_sCombatDialog[892 * roleIdx];
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v17 = 0;
  v16 = dword_17AA050;
  v15 = (int *)(v6 + 712);
  while ( 1 )
  {
    v7 = *v15;
    if ( *v15 )
    {
      if ( v6[v5 + 736] )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v15);
        if ( !*(_BYTE *)(RoleNum + 4) && ((PAL_GDB *)this)->IsRoleDead(v7) )
        {
          v9 = *(_BYTE *)(RoleNum + 577);
          if ( v21 == 1 )
          {
            if ( v9 != 4 )
              goto LABEL_15;
          }
          else if ( v9 != 3 )
          {
            goto LABEL_15;
          }
          pOut[1] = v7;
          if ( this->GetRoleAI(pOut) )
          {
            *v16 = v7;
            ++v14;
            ++v16;
          }
        }
      }
    }
LABEL_15:
    v5 = v17 + 1;
    v10 = ++v17 < 6;
    ++v15;
    if ( !v10 )
      break;
    v6 = &this->m_sCombatDialog[892 * roleIdx];
  }
  result = v14;
  if ( v14 )
  {
    v11 = 0;
    if ( v14 <= 0 )
      return 0;
    v12 = dword_17AA050;
    do
    {
      Role = ((CCBStage *)this)->GetRole(roleIdx);
      if ( (int)abs32((int)Role - v22) < v3 )
      {
        v18 = v11;
        v3 = abs32(abs32((int)Role) - abs32(v22));
      }
      ++v11;
      ++v12;
    }
    while ( v11 < v14 );
    if ( v18 == -1 )
      return 0;
    else
      return dword_17AA050[v18];
  }
  return result;
}

// 0x004F5970
int CCBRoleState::ProcessSkillEffect(int roleIdx)
{
  CCBRoleState *v2; // ebp
  int v3; // edi
  int v5; // ebx
  int v6; // esi
  char v7; // al
  unsigned int v8; // ebp
  unsigned int v9; // ecx
  __int64 v10; // rax
  signed int v12; // [esp+0x14] [ebp-0x88]
  int v13; // [esp+0x18] [ebp-0x84]
  int SlotCount; // [esp+0x1C] [ebp-0x80]
  _DWORD v15[11]; // [esp+0x20] [ebp-0x7C] BYREF
  _BYTE v16[12]; // [esp+0x4C] [ebp-0x50] BYREF
  unsigned int pdwVal[11]; // [esp+0x58] [ebp-0x44] BYREF
  _BYTE pOut[12]; // [esp+0x84] [ebp-0x18] BYREF
  _BYTE v19[12]; // [esp+0x90] [ebp-0xC] BYREF
  char v20; // [esp+A4h] [ebp+0x8]
  int v21; // [esp+A8h] [ebp+0xC]
memset(v15, 0, sizeof(v15));
  v3 = roleIdx;
  v13 = -1;
  v12 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  v5 = 0;
  LOBYTE(v15[10]) = 1;
  v15[0] = 262;
  v15[1] = 0;
  v15[2] = roleIdx;
  v15[3] = -1;
  LOWORD(v15[4]) = 0;
  SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
  if ( SlotCount <= 0 )
    return 0;
  while ( 1 )
  {
    if ( *((int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut) + 1) > 0 )
    {
      v6 = *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v19);
      v15[1] = v6;
      if ( ((CCBRoleState *)v2)->GetRoleAI(v15) )
      {
        v7 = *(_BYTE *)(*((_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v16) + 2) + 629);
        if ( v20 )
        {
          if ( v7 == 1 || v7 == 3 )
            goto LABEL_21;
        }
        else if ( v7 == 2 || v7 == 4 )
        {
          goto LABEL_21;
        }
        if ( ((PAL_GDB *)v2)->GetSkillLevel(v6) )
        {
          v8 = ((CCBRoleState *)v2)->CalcSkillDamage(v3, v6);
          memset(pdwVal, 0, sizeof(pdwVal));
          pdwVal[0] = 262;
          pdwVal[1] = v6;
          if ( ((CCBStage *)this)->CheckGDBTypeCompat(pdwVal) )
            v8 += 100000;
          v9 = abs32(v8);
          if ( (int)abs32(v9 - v21) < v12 )
          {
            v13 = v5;
            v10 = (int)(v9 - abs32(v21));
            v12 = (HIDWORD(v10) ^ v10) - HIDWORD(v10);
          }
}
      }
    }
LABEL_21:
    if ( ++v5 >= SlotCount )
      break;
    v3 = roleIdx;
  }
  if ( v13 == -1 )
    return 0;
  else
    return *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v16);
}

// 0x004F5B70
int CCBRoleState::ProcessItemEffect(int roleIdx)
{
  signed int v3; // esi
  int i; // edi
  int v6; // ebp
  char v7; // al
  unsigned int v8; // ecx
  int v9; // [esp+0x10] [ebp-0x58]
  int SlotCount; // [esp+0x14] [ebp-0x54]
  _BYTE pOut[12]; // [esp+0x18] [ebp-0x50] BYREF
  _BYTE v12[12]; // [esp+0x24] [ebp-0x44] BYREF
  _BYTE v13[12]; // [esp+0x30] [ebp-0x38] BYREF
  _DWORD v14[11]; // [esp+0x3C] [ebp-0x2C] BYREF
  char v15; // [esp+0x70] [ebp+0x8]
  int v16; // [esp+0x74] [ebp+0xC]

  memset(v14, 0, sizeof(v14));
  v9 = -1;
  v3 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(v14[10]) = 1;
  v14[0] = 262;
  v14[1] = 0;
  v14[2] = roleIdx;
  v14[3] = -1;
  LOWORD(v14[4]) = 0;
  SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
  if ( SlotCount <= 0 )
    return 0;
  for ( i = 0; i < SlotCount; ++i )
  {
    if ( *((int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut) + 1) > 0 )
    {
      v6 = *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v12);
      v14[1] = v6;
      if ( this->GetRoleAI(v14) )
      {
        v7 = *(_BYTE *)(*((_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v13) + 2) + 629);
        if ( v15 )
        {
          if ( v7 == 1 || v7 == 3 )
            continue;
        }
        else if ( v7 == 2 || v7 == 4 )
        {
          continue;
        }
        if ( ((PAL_GDB *)this)->IsSkillUsable(v6) )
        {
          v8 = abs32(this->CalcMagicDamage(roleIdx, v6));
          if ( (int)abs32(v8 - v16) < v3 )
          {
            v9 = i;
            v3 = abs32(v8 - abs32(v16));
          }
        }
      }
    }
  }
  if ( v9 == -1 )
    return 0;
  else
    return *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v13);
}

// 0x004F5D00
int CCBRoleState::AISelectMagic(unsigned int roleIdx, char pData, int nVal)
{
  unsigned int v4; // ebx
  int v7; // eax
  int v8; // ebp
  int v9; // eax
  unsigned int v10; // esi
  int RoleNum; // edi
  int v12; // ebp
  int v13; // esi
  unsigned int v14; // edi
  int v15; // ebx
  bool v16; // cc
  int v17; // edi
  int *v18; // esi
  unsigned int v19; // ebp
  __int64 v20; // rax
  int v21; // eax
  int v22; // [esp+0x10] [ebp-0x4C]
  int *v24; // [esp+0x18] [ebp-0x44]
  int v25; // [esp+0x1C] [ebp-0x40]
  int v26; // [esp+0x20] [ebp-0x3C]
  int *v27; // [esp+0x24] [ebp-0x38]
  unsigned int *v28; // [esp+0x24] [ebp-0x38]
  int v29; // [esp+0x28] [ebp-0x34]
  int v30; // [esp+0x2C] [ebp-0x30]
  unsigned int pdwVal[11]; // [esp+0x30] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x60] [ebp+0x4]

  v4 = roleIdx;
  memset(pdwVal, 0, sizeof(pdwVal));
  v22 = 0;
  v30 = -1;
  v29 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 261;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  pdwVal[3] = -1;
  LOWORD(pdwVal[4]) = 0;
  v7 = this->GetRoleHP(roleIdx) - 1;
  if ( v7 )
  {
    if ( v7 != 1 )
      return 0;
    roleIdxa = dword_17A9F50;
    v8 = 760;
    v27 = (int *)&this->m_Role[0].bMagicMastered[1][892 * v4 + 3];
    while ( 1 )
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*v27);
      v10 = *(_DWORD *)(v9 + v8);
      if ( v10 )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*(_DWORD *)(v9 + v8));
        if ( *(_BYTE *)(RoleNum + 4) )
        {
          pdwVal[1] = v10;
          if ( ((CCBStage *)this)->CheckGDBTypeCompat(pdwVal) )
          {
            if ( pData == 1 )
            {
              if ( *(_BYTE *)(RoleNum + 577) == 2 )
                goto LABEL_15;
            }
            else if ( !pData && *(_BYTE *)(RoleNum + 577) == 1 )
            {
LABEL_15:
              if ( this->GetRoleAI(pdwVal) )
              {
                *roleIdxa = v10;
                ++v22;
                ++roleIdxa;
              }
            }
          }
        }
      }
      v8 += 4;
      if ( v8 >= 776 )
      {
        if ( !v22 )
          return 0;
LABEL_37:
        v17 = 0;
        if ( v22 <= 0 )
          return 0;
        v18 = dword_17A9F50;
        v19 = abs32(nVal);
        do
        {
          v20 = (int)(abs32((int)((CCBStage *)this)->GetRole(v4)) - v19);
          v21 = (HIDWORD(v20) ^ v20) - HIDWORD(v20);
          if ( v21 < v29 )
          {
            v29 = v21;
            v30 = v17;
          }
          ++v17;
          ++v18;
        }
        while ( v17 < v22 );
        if ( v30 == -1 )
          return 0;
        else
          return dword_17A9F50[v30];
      }
    }
  }
  v25 = 0;
  v26 = 936;
  do
  {
    v12 = 0;
    v13 = 892 * v4;
    v28 = (unsigned int *)(4 * v22 + 24813392);
    v24 = (int *)(&this->m_Role[1].bCanAction + 892 * v4 + v25);
    do
    {
      v14 = *v24;
      if ( *v24 && this->m_sCombatDialog[v12 + v13 + v26] )
      {
        v15 = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v24);
        pdwVal[1] = v14;
        if ( ((CCBStage *)this)->CheckGDBTypeCompat(pdwVal) )
        {
          if ( pData == 1 )
          {
            if ( *(_BYTE *)(v15 + 577) != 2 )
              goto LABEL_32;
          }
          else if ( pData || *(_BYTE *)(v15 + 577) != 1 )
          {
            goto LABEL_32;
          }
          if ( this->GetRoleAI(pdwVal) )
          {
            *v28 = v14;
            ++v22;
            ++v28;
          }
        }
LABEL_32:
        v4 = roleIdx;
      }
      ++v12;
      ++v24;
    }
    while ( v12 < 8 );
    v16 = v26 + 8 < 984;
    v25 += 32;
    v26 += 8;
  }
  while ( v16 );
  if ( v22 )
    goto LABEL_37;
  return 0;
}

// 0x004F6000
int CCBRoleState::AISelectHealItem(unsigned int roleIdx, char pData, int nVal)
{
  signed int v4; // ebp
  int result; // eax
  int v6; // ebx
  char *v7; // eax
  unsigned int v8; // esi
  int RoleNum; // edi
  char v10; // al
  int v11; // esi
  int *v12; // ebx
  CCBStageRole *Role; // ecx
  int v15; // [esp+0x14] [ebp-0x40]
  int *v16; // [esp+0x18] [ebp-0x3C]
  int *v17; // [esp+0x1C] [ebp-0x38]
  int v18; // [esp+0x20] [ebp-0x34]
  unsigned int pdwVal[11]; // [esp+0x28] [ebp-0x2C] BYREF

  memset(pdwVal, 0, sizeof(pdwVal));
  v15 = 0;
  v18 = -1;
  v4 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  pdwVal[3] = -1;
  v6 = 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 260;
  v7 = &this->m_sCombatDialog[892 * roleIdx];
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  LOWORD(pdwVal[4]) = 0;
  v17 = dword_17A9E50;
  v16 = (int *)(v7 + 712);
  while ( 1 )
  {
    v8 = *v16;
    if ( *v16 )
    {
      if ( v7[v6 + 736] )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v16);
        if ( !*(_BYTE *)(RoleNum + 4) )
        {
          pdwVal[1] = v8;
          if ( ((CCBStage *)this)->CheckGDBTypeCompat(pdwVal) )
          {
            v10 = *(_BYTE *)(RoleNum + 577);
            if ( pData == 1 )
            {
              if ( v10 != 2 )
                goto LABEL_15;
            }
            else if ( v10 != 1 )
            {
              goto LABEL_15;
            }
            if ( this->GetRoleAI(pdwVal) )
            {
              *v17 = v8;
              ++v15;
              ++v17;
            }
          }
        }
      }
    }
LABEL_15:
    ++v6;
    ++v16;
    if ( v6 >= 6 )
      break;
    v7 = &this->m_sCombatDialog[892 * roleIdx];
  }
  result = v15;
  if ( v15 )
  {
    v11 = 0;
    if ( v15 <= 0 )
      return 0;
    v12 = dword_17A9E50;
    do
    {
      Role = ((CCBStage *)this)->GetRole(roleIdx);
      if ( (int)abs32((int)Role - nVal) < v4 )
      {
        v18 = v11;
        v4 = abs32(abs32((int)Role) - abs32(nVal));
      }
      ++v11;
      ++v12;
    }
    while ( v11 < v15 );
    if ( v18 == -1 )
      return 0;
    else
      return dword_17A9E50[v18];
  }
  return result;
}

// 0x004F61D0
int CCBRoleState::AISelectTarget(unsigned int roleIdx, char pData, int nVal)
{
  signed int v4; // edi
  int i; // esi
  int v7; // ebp
  char v8; // al
  unsigned int v9; // ecx
  int v11; // [esp+0x10] [ebp-0x58]
  int SlotCount; // [esp+0x14] [ebp-0x54]
  _BYTE pOut[12]; // [esp+0x18] [ebp-0x50] BYREF
  _BYTE v14[12]; // [esp+0x24] [ebp-0x44] BYREF
  _BYTE v15[12]; // [esp+0x30] [ebp-0x38] BYREF
  unsigned int pdwVal[11]; // [esp+0x3C] [ebp-0x2C] BYREF

  memset(pdwVal, 0, sizeof(pdwVal));
  v11 = -1;
  v4 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 262;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  pdwVal[3] = -1;
  LOWORD(pdwVal[4]) = 0;
  SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
  if ( SlotCount <= 0 )
    return 0;
  for ( i = 0; i < SlotCount; ++i )
  {
    if ( *((int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut) + 1) <= 0 )
      continue;
    v7 = *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v14);
    v8 = *(_BYTE *)(*((_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v15) + 2) + 629);
    if ( pData )
    {
      if ( v8 == 1 || v8 == 3 )
        continue;
    }
    else if ( v8 == 2 || v8 == 4 )
    {
      continue;
    }
    pdwVal[1] = v7;
    if ( ((CCBStage *)this)->CheckGDBTypeCompat(pdwVal) )
    {
      if ( this->GetRoleAI(pdwVal) )
      {
        v9 = abs32(this->CalcMagicDamage(roleIdx, v7));
        if ( (int)abs32(v9 - nVal) < v4 )
        {
          v11 = i;
          v4 = abs32(v9 - abs32(nVal));
        }
      }
    }
  }
  if ( v11 == -1 )
    return 0;
  else
    return *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v15);
}

// 0x004F6370
int CCBRoleState::AISelectSkill(unsigned int roleIdx, int nVal, char pData)
{
  unsigned int v4; // ebx
  CCBRoleState *v5; // ebp
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // esi
  int RoleNum; // edi
  int v12; // ebp
  int v13; // esi
  unsigned int v14; // edi
  int v15; // ebx
  bool v16; // cc
  int v17; // esi
  int *v18; // edi
  CCBStageRole *Role; // ecx
  int v20; // [esp+0x10] [ebp-0x4C]
  int *v22; // [esp+0x18] [ebp-0x44]
  int v23; // [esp+0x1C] [ebp-0x40]
  int v24; // [esp+0x20] [ebp-0x3C]
  int v25; // [esp+0x20] [ebp-0x3C]
  unsigned int *v26; // [esp+0x24] [ebp-0x38]
  signed int v27; // [esp+0x28] [ebp-0x34]
  int v28; // [esp+0x2C] [ebp-0x30]
  unsigned int pdwVal[11]; // [esp+0x30] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x60] [ebp+0x4]

  v4 = roleIdx;
memset(pdwVal, 0, sizeof(pdwVal));
  v20 = 0;
  v28 = -1;
  v27 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 261;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  pdwVal[3] = -1;
  LOWORD(pdwVal[4]) = 0;
  v7 = ((CCBRoleState *)v5)->GetRoleHP(roleIdx) - 1;
  if ( v7 )
  {
    if ( v7 != 1 )
      return 0;
    v8 = 760;
    roleIdxa = dword_17A9D50;
    v24 = 760;
    while ( 1 )
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(_DWORD *)&this->m_Role[0].bMagicMastered[1][892 * v4 + 3]);
      v10 = *(_DWORD *)(v8 + v9);
      if ( v10 )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v10);
        if ( *(_BYTE *)(RoleNum + 4) )
        {
          pdwVal[1] = v10;
          if ( ((PAL_GDB *)v5)->IsRoleSkillValid(pdwVal, nVal) )
          {
            if ( pData == 1 )
            {
              if ( *(_BYTE *)(RoleNum + 577) == 2 )
                goto LABEL_15;
            }
            else if ( !pData && *(_BYTE *)(RoleNum + 577) == 1 )
            {
LABEL_15:
              if ( ((CCBRoleState *)v5)->GetRoleAI(pdwVal) )
              {
                *roleIdxa = v10;
                ++v20;
                ++roleIdxa;
              }
            }
          }
        }
      }
      v8 = v24 + 4;
      v24 += 4;
      if ( v24 >= 776 )
      {
        if ( !v20 )
          return 0;
LABEL_38:
        v17 = 0;
        if ( v20 <= 0 )
          return 0;
        v18 = dword_17A9D50;
        do
        {
          Role = ((CCBStage *)v5)->GetRole(v4);
          if ( (int)abs32((int)Role) < v27 )
          {
            v28 = v17;
            v27 = abs32(abs32((int)Role));
          }
          ++v17;
          ++v18;
        }
        while ( v17 < v20 );
        if ( v28 == -1 )
          return 0;
        else
          return dword_17A9D50[v28];
      }
    }
  }
  v23 = 0;
  v25 = 936;
  do
  {
    v12 = 0;
    v13 = 892 * v4;
    v26 = (unsigned int *)(4 * v20 + 24812880);
    v22 = (int *)(&this->m_Role[1].bCanAction + 892 * v4 + v23);
    do
    {
      v14 = *v22;
      if ( *v22 && this->m_sCombatDialog[v12 + v13 + v25] )
      {
        v15 = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v22);
        pdwVal[1] = v14;
        if ( ((PAL_GDB *)this)->IsRoleSkillValid(pdwVal, nVal) )
        {
          if ( pData == 1 )
          {
            if ( *(_BYTE *)(v15 + 577) != 2 )
              goto LABEL_32;
          }
          else if ( pData || *(_BYTE *)(v15 + 577) != 1 )
          {
            goto LABEL_32;
          }
          if ( this->GetRoleAI(pdwVal) )
          {
            *v26 = v14;
            ++v20;
            ++v26;
          }
        }
LABEL_32:
        v4 = roleIdx;
      }
      ++v12;
      ++v22;
    }
    while ( v12 < 8 );
    v16 = v25 + 8 < 984;
    v23 += 32;
    v25 += 8;
  }
  while ( v16 );
  if ( v20 )
  {
goto LABEL_38;
  }
  return 0;
}

// 0x004F6690
int CCBRoleState::AISelectItemForSkill(unsigned int roleIdx, int nSkillID, char pData)
{
  int v7; // ebx
  char *v8; // eax
  unsigned int v9; // esi
  int RoleNum; // edi
  char v11; // al
  int v12; // esi
  int *v13; // edi
  CCBStageRole *Role; // ecx
  int v15; // [esp+0x10] [ebp-0x44]
  int *v17; // [esp+0x18] [ebp-0x3C]
  signed int v18; // [esp+0x1C] [ebp-0x38]
  int v19; // [esp+0x20] [ebp-0x34]
  char *v20; // [esp+0x24] [ebp-0x30]
  unsigned int pdwVal[11]; // [esp+0x28] [ebp-0x2C] BYREF
  int *roleIdxa; // [esp+0x58] [ebp+0x4]

  memset(pdwVal, 0, sizeof(pdwVal));
  v15 = 0;
  v19 = -1;
  v18 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  pdwVal[3] = -1;
  v7 = 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 260;
  pdwVal[1] = 0;
  v8 = &this->m_sCombatDialog[892 * roleIdx];
  pdwVal[2] = roleIdx;
  LOWORD(pdwVal[4]) = 0;
  v17 = dword_17A9C50;
  v20 = v8;
  roleIdxa = (int *)(v8 + 712);
  while ( 1 )
  {
    v9 = *roleIdxa;
    if ( *roleIdxa )
    {
      if ( v8[v7 + 736] )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*roleIdxa);
        if ( !*(_BYTE *)(RoleNum + 4) )
        {
          pdwVal[1] = v9;
          if ( ((PAL_GDB *)this)->IsRoleSkillValid(pdwVal, nSkillID) )
          {
            v11 = *(_BYTE *)(RoleNum + 577);
            if ( pData == 1 )
            {
              if ( v11 != 2 )
                goto LABEL_15;
            }
            else if ( v11 != 1 )
            {
              goto LABEL_15;
            }
            if ( this->GetRoleAI(pdwVal) )
            {
              *v17 = v9;
              ++v15;
              ++v17;
            }
          }
        }
      }
    }
LABEL_15:
    ++v7;
    ++roleIdxa;
    if ( v7 >= 6 )
      break;
    v8 = v20;
  }
  if ( !v15 )
    return 0;
  v12 = 0;
  if ( v15 <= 0 )
    return 0;
  v13 = dword_17A9C50;
  do
  {
    Role = ((CCBStage *)this)->GetRole(roleIdx);
    if ( (int)abs32((int)Role) < v18 )
    {
      v19 = v12;
      v18 = abs32(abs32((int)Role));
    }
    ++v12;
    ++v13;
  }
  while ( v12 < v15 );
  if ( v19 == -1 )
    return 0;
  else
    return dword_17A9C50[v19];
}

// 0x004F6860
int CCBRoleState::AISelectSkillTarget(unsigned int roleIdx, int nSkillID, char pData)
{
  signed int v5; // ebp
  int i; // esi
  int v8; // edi
  char v9; // al
  int v10; // ecx
  int v11; // [esp+0x10] [ebp-0x58]
  int SlotCount; // [esp+0x14] [ebp-0x54]
  _BYTE pOut[12]; // [esp+0x18] [ebp-0x50] BYREF
  _BYTE v14[12]; // [esp+0x24] [ebp-0x44] BYREF
  _BYTE v15[12]; // [esp+0x30] [ebp-0x38] BYREF
  unsigned int pdwVal[11]; // [esp+0x3C] [ebp-0x2C] BYREF

  v5 = 0x7FFFFFFF;
  memset(pdwVal, 0, sizeof(pdwVal));
  v11 = -1;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pdwVal[10]) = 1;
  pdwVal[0] = 262;
  pdwVal[1] = 0;
  pdwVal[2] = roleIdx;
  pdwVal[3] = -1;
  LOWORD(pdwVal[4]) = 0;
  SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
  if ( SlotCount <= 0 )
    return 0;
  for ( i = 0; i < SlotCount; ++i )
  {
    if ( *((int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut) + 1) <= 0 )
      continue;
    v8 = *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v14);
    v9 = *(_BYTE *)(*((_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v15) + 2) + 629);
    if ( pData )
    {
      if ( v9 == 1 || v9 == 3 )
        continue;
    }
    else if ( v9 == 2 || v9 == 4 )
    {
      continue;
    }
    pdwVal[1] = v8;
    if ( ((PAL_GDB *)this)->IsRoleSkillValid(pdwVal, nSkillID) )
    {
      if ( this->GetRoleAI(pdwVal) )
      {
        v10 = abs32(this->CalcMagicDamage(roleIdx, v8));
        if ( (int)abs32(v10) < v5 )
        {
          v11 = i;
          v5 = abs32(v10);
        }
      }
    }
  }
  if ( v11 == -1 )
    return 0;
  else
    return *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v15);
}

// 0x004F6DA0
char CCBRoleState::ValidateCommandTarget(int *pCmd)
{
  unsigned int v2; // eax
  int v3; // edx
  _DWORD *j; // eax
  int v6; // edi
  int v7; // edx
  _DWORD *v8; // esi
  int v9; // ecx
  int v10; // eax
  _DWORD *i; // eax

  v2 = pCmd[2];
  if ( v2 > 4 )
  {
    ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(_DWORD *)&this->m_Role[0].bMagicMastered[1][892 * v2 + 3]);
    v9 = 0;
    for ( i = (_DWORD *)(v10 + 760); *i != pCmd[1]; ++i )
    {
      if ( ++v9 >= 4 )
        return 0;
    }
  }
  else if ( *pCmd == 260 )
  {
    v3 = 0;
    for ( j = (_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[9][446 * v2 + 3] + 1); *j != pCmd[1]; ++j )
    {
      if ( ++v3 >= 6 )
        return 0;
    }
  }
  else
  {
    v6 = 0;
LABEL_8:
    v7 = 0;
    v8 = &this->m_Role[1].bCanAction + 892 * v2 + v6;
    while ( *v8 != pCmd[1] )
    {
      ++v7;
      ++v8;
      if ( v7 >= 8 )
      {
        v6 += 32;
        if ( v6 < 192 )
          goto LABEL_8;
        return 0;
      }
    }
  }
  return 1;
}

// 0x004F7200
char CCBRoleState::CheckEventCondition(int pEvent)
{
  int RoleNum; // esi
  char *v4; // ecx
  char result; // al
  int v6; // ebp
  bool v7; // cc
  int v8; // esi
  int v9; // [esp-0x4] [ebp-0x1C]
  int p_DWORD[3]; // [esp+0xC] [ebp-0xC] BYREF

  v9 = *(_DWORD *)(pEvent + 4);
  p_DWORD[0] = 0xFFFF;
  p_DWORD[1] = 0;
  p_DWORD[2] = 0;
  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v9);
  v4 = &this->m_sCombatDialog[892 * *(_DWORD *)(pEvent + 8)];
  if ( !v4[578] )
    return 0;
  switch ( *(_DWORD *)(RoleNum + 696) )
  {
    case 0xFFFFFFFF:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
      goto LABEL_31;
    case 0:
      if ( *((_DWORD *)v4 + 147) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 1:
      if ( *((_DWORD *)v4 + 149) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 2:
      if ( *((_DWORD *)v4 + 151) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 3:
      if ( this->GetAttackBonus(*(_DWORD *)(pEvent + 8)) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 4:
      if ( this->GetDefenseBonus(*(_DWORD *)(pEvent + 8)) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 5:
      if ( *((_DWORD *)v4 + 157) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 6:
      if ( *((_DWORD *)v4 + 176) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 7:
      if ( this->GetSpeedBonus(*(_DWORD *)(pEvent + 8)) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 8:
      if ( this->GetRoleState(*(_DWORD *)(pEvent + 8)) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 9:
      if ( *((_DWORD *)v4 + 146) >= *(_DWORD *)(RoleNum + 704) )
        goto LABEL_31;
      return 0;
    case 0xA:
      if ( this->GetTotalRounds() < *(_DWORD *)(RoleNum + 704) )
        return 0;
      v6 = *(_DWORD *)(pEvent + 4);
      if ( v6 == 4102 )
      {
        v8 = this->Update(1);
        v7 = this->GetTotalRounds() < 2 * v8 * (*(_DWORD *)&this->m_Role[0].bMagicMastered[6][5] + 20);
      }
      else
      {
        if ( v6 != 4305 )
          goto LABEL_31;
        v7 = this->GetTotalRounds() < 1000;
      }
      if ( v7 )
        return 0;
LABEL_31:
      result = 1;
      break;
    case 0x10:
      p_DWORD[0] = 6113;
      if ( !((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(p_DWORD) )
        return 0;
      goto LABEL_31;
    default:
      return 0;
  }
  return result;
}

// 0x004F7480
char CCBRoleState::CheckMagicCost(int *p_DWORD)
{
  int RoleNum; // eax

  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(p_DWORD[1]);
  if ( *p_DWORD == 260 )
  {
    if ( *(_DWORD *)(RoleNum + 688) > *(_DWORD *)&this->m_Role[0].bMagicMastered[8][892 * p_DWORD[2] + 5] )
      return 0;
  }
  else if ( *p_DWORD == 261
         && *(_DWORD *)(RoleNum + 692) > *(_DWORD *)((char *)&this->m_Role[0].byMagicUseTime[0][446 * p_DWORD[2] + 3] + 1) )
  {
    return 0;
  }
  return 1;
}

// 0x004F7500
char CCBRoleState::GetRoleAI(void *pOut)
{
  int v3; // eax
  char v4; // dl
  char *v5; // ecx
  char result; // al

  v3 = *((_DWORD *)pOut + 2);
  v4 = this->m_Role[0].bMagicMastered[5][892 * v3 + 5];
  v5 = &this->m_sCombatDialog[892 * v3];
  if ( !v4 )
    return 0;
  if ( v5[1432] )
    return 0;
  this->GetRoleHP(*((_DWORD *)pOut + 2));
  result = ((PAL_GDB *)this)->IterateInventory((int *)pOut);
  if ( result )
  {
    switch ( *(_DWORD *)pOut )
    {
      case 0x104:
        result = this->ValidateCommandTarget((int *)pOut);
        if ( !result )
          return result;
        result = this->CheckMagicCost((int *)pOut);
        if ( !result )
          return result;
        result = this->CheckEventCondition((int)pOut);
        if ( !result )
          return result;
        ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*((_DWORD *)pOut + 1));
        break;
      case 0x105:
        result = this->ValidateCommandTarget((int *)pOut);
        if ( !result )
          return result;
        result = this->CheckMagicCost((int *)pOut);
        if ( !result )
          return result;
        result = this->CheckEventCondition((int)pOut);
        if ( !result )
          return result;
        if ( this->GetRoleField(*((_DWORD *)pOut + 2), 15) )
          return 0;
        if ( *((_DWORD *)pOut + 1) == 7710 )
        {
          if ( this->Update(2) != 1 )
            return 0;
          if ( HIBYTE(this->m_Role[8].fHPIncPerRound) && !BYTE1(this->m_Role[9].dwMagicID[6][5]) )
            return 0;
          if ( this->m_BufferData[105] && !this->m_BufferData[959] )
            return 0;
        }
        break;
      case 0x106:
        result = ((PAL_GDB *)this)->BuildItemArray((int)pOut);
        if ( result )
        {
          if ( this->GetRoleField(*((_DWORD *)pOut + 2), 16) )
          {
            return 0;
          }
          else if ( !((CCBSystem *)this)->IsMagicSlotMsg((int)pOut)
                 || (result = ((CCBSystem *)this)->HandleMagicCommand((int)pOut)) != 0 )
          {
            ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*((_DWORD *)pOut + 1));
            return 1;
          }
        }
        return result;
      default:
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004F76C0
int CCBRoleState::GetSkillCostLevel(unsigned int dwSlot, int nSkillID)
{
  int v4; // ebx
  int v5; // edx
  _DWORD *v6; // edi
  int v8; // eax
  int v9; // ecx
  _DWORD *v10; // edx
  int v11; // [esp+0x10] [ebp-0x4]
  unsigned int dwSlota; // [esp+0x18] [ebp+0x4]

  if ( dwSlot > 4 )
  {
    ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(_DWORD *)&this->m_Role[0].bMagicMastered[1][892 * dwSlot + 3]);
    v9 = 0;
    v10 = (_DWORD *)(v8 + 760);
    do
    {
      if ( *v10 == nSkillID )
        return *(unsigned __int8 *)(v8 + v9 + 776);
      ++v9;
      ++v10;
    }
    while ( v9 < 3 );
    if ( *(_DWORD *)(v8 + 772) == nSkillID )
      return 4;
    else
      return nSkillID == 207 || nSkillID == 215 || nSkillID == 232 || nSkillID == 224 || nSkillID == 240;
  }
  else
  {
    v11 = 0;
    dwSlota = 0;
    v4 = 936;
    while ( 2 )
    {
      v5 = 0;
      v6 = &this->m_Role[1].bCanAction + 892 * dwSlot + dwSlota;
      do
      {
        if ( *v6 == nSkillID && this->m_sCombatDialog[892 * dwSlot + v5 + v4] )
          return *((unsigned __int8 *)&this->m_Role[1].dwMagicID[4][223 * dwSlot + 2 + 2 * v11] + v5 + 1) + 1;
        ++v5;
        ++v6;
      }
      while ( v5 < 8 );
      v4 += 8;
      ++v11;
      dwSlota += 32;
      if ( v4 < 984 )
        continue;
      break;
    }
    return 0;
  }
}

// 0x004F7820
char CCBRoleState::SumGPCost(int nVal)
{
  int v3; // edx
  _BYTE *i; // eax

  if ( *(_DWORD *)(nVal + 12) > 0xAu )
  {
    v3 = 0;
    for ( i = &this->m_Role[0].bMagicMastered[5][5];
          !*(i - 1) || !*i || i[854] || i[853] || !*(_BYTE *)(v3 + nVal + 29);
          i += 892 )
    {
      if ( ++v3 >= 11 )
        return 0;
    }
  }
  return 1;
}

// 0x004F7880
unsigned int CCBRoleState::CheckStatus()
{
  char *v1; // ecx
  int v2; // edi
  int v3; // esi
  unsigned int result; // eax

  v1 = (char *)&this->m_Role[0].byMagicUseTime[0][3] + 1;
  v2 = 11;
  do
  {
    *((_DWORD *)v1 - 4) &= (*((int *)v1 - 4) < 0) - 1;
    *((_DWORD *)v1 - 2) &= (*((int *)v1 - 2) < 0) - 1;
    *(_DWORD *)v1 &= (*(int *)v1 < 0) - 1;
    if ( *((int *)v1 - 4) <= 0 )
    {
      *(v1 - 26) = 0;
      v1[562] = 1;
      v1[561] = 0;
    }
    v3 = *((_DWORD *)v1 - 4);
    result = (unsigned int)((unsigned __int64)(1717986919LL * *((int *)v1 - 3)) >> 32) >> 31;
    if ( v3 < *((_DWORD *)v1 - 3) / 10 && v3 > 0 )
      v1[561] = 1;
    v1 += 892;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x004F7910
void * CCBRoleState::ProcessActions()
{
  int RoleIndex; // edi
  int v3; // edi
  _BYTE *v4; // ebx
  int v5; // ebx
  _BYTE *v6; // ebp
  CCBStage *v7; // ecx
  int v8; // edi
  int v9; // edi
  int v10; // eax
  int v11; // edi
  void *result; // eax
  int v13; // ecx
  int v14; // [esp+0x0] [ebp-0x44]
  int v15; // [esp+0x4] [ebp-0x40]
  int v16; // [esp+0x10] [ebp-0x34]
  _BYTE *v17; // [esp+0x14] [ebp-0x30]
  _DWORD pData[11]; // [esp+0x18] [ebp-0x2C] BYREF

  memset(pData, 0, sizeof(pData));
  if ( this->ApplyHitEffect(0) == 1
    && *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 120) == 2
    && !((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->ForceDelTask(12) )
  {

    RoleIndex = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(25, pData, 1);
    if ( RoleIndex != -1 )
    {
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBRoleState::FadeMusicOut */, 0, 0, 0, 0, -1082130432, 1056964608);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStageRole::TaskShowSkillLearned */, 0, 0, 0, 0, -1082130432, 1084227584);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBRoleState::Func */, 0, 0, 0, 0, -1082130432, 1065353216);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBRoleState::FadeMusicIn */, 0, 0, 0, 0, -1082130432, 1045220557);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
    }
    ((CCBCamControl *)*(CCBCamControl **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 16))->ClearFinishedTask(10);
    v3 = 24;
    v4 = &this->m_Role[0].bMagicMastered[5][4];
    *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 120) = 7;
    do
    {
      if ( *v4 )
      {
        *(_BYTE *)(*(_DWORD *)(v3 + *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1)) + 280) = 0;
        *(_BYTE *)(*(_DWORD *)(v3 + *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1)) + 274) = 0;
        ((CCBStageRole *)*(CCBStageRole **)(v3
                                                  + *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1)))->TryRelease();
      }
      v3 += 4;
      v4 += 892;
    }
    while ( v3 < 68 );
  }
  if ( ((unsigned __int8)this->GetForce(0) == 1
     || *(_DWORD *)&this->m_Role[0].bMagicMastered[0][1] >= *(int *)((char *)&this->m_Role[0].dwMagicID[8][5]
                                                                              + 1)
     && !this->m_Role[0].bMagicMastered[0][5])
    && *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 120) == 2
    && !((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->ForceDelTask(12) )
  {

    this->UpdateRoleMP(1, -1);
    ((CCBCamControl *)*(CCBCamControl **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 16))->ClearFinishedTask(3);
    v5 = 0;
    v6 = &this->m_Role[0].bMagicMastered[5][5];
    v16 = 0;
    v17 = &this->m_Role[0].bMagicMastered[5][5];
    do
    {
      if ( *(v6 - 1) )
      {
        if ( *v6 )
        {
          v7 = *(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1);
          pData[2] = v5;
          v8 = ((CCBStage *)v7)->GetRoleIndex(24, pData, 1);
          if ( v8 != -1 )
          {
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v8, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, 0, -1082130432, 0);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v8, 0 /* TODO: (int)CCBStageRole::TaskReturnToIdle */, 0, 0, 0, 0, -1082130432, 0);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v8, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, 0, -1082130432, 0);
            ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v8);
            v6 = v17;
            v5 = v16;
          }
        }
      }
      ++v5;
      v6 += 892;
      v16 = v5;
      v17 = v6;
    }
    while ( v5 < 5 );
    v9 = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(23, pData, 1);
    if ( v9 != -1 )
    {
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v9, 0 /* TODO: (int)CCBRoleState::FadeMusicOut */, 0, 0, 0, 0, -1082130432, 1056964608);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v9, 0 /* TODO: (int)CCBStageRole::TaskShowLevelUp */, 0, 0, 0, 0, -1082130432, 1077936128);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v9, 0 /* TODO: (int)CCBRoleState::GetCombatDialogEntry */, 0, 0, 0, 0, -1082130432, 0x40000000);
      this->UpdateRoleMP(0, v9);
      this->CheckMPRequirement(v9);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v9, 0 /* TODO: (int)CCBStage::StartSubTask */, 0, 0, 0, 0, -1082130432, 1084227584);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v9, 0 /* TODO: (int)CCBRoleState::FadeMusicIn */, 0, 0, 0, 0, -1082130432, 1045220557);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v9, 0 /* TODO: (int)CCBRoleState::Func */, 0, 0, 0, 0, -1082130432, 1065353216);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v9);
      LOBYTE(v10) = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->EndTask(v9);
      *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[3][1] = v10;
    }


    ((C2DSpark *)*(C2DSpark **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 52))->CreateStars();
    ((C2DSpark *)*(C2DSpark **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 52))->CreateTrack(1, v14, v15);
    *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 120) = 5;
    ((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0]
                                                                               + 1)
                                                         + 20)
                                             + 20))->Destroy();
  }
  if ( *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 120) == 4 )
  {
    this->UpdateRoleMP(1, -1);
    ((CCBCamControl *)*(CCBCamControl **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 20) + 16))->ClearFinishedTask(8);
    ((CCBAttackSequen *)*(CCBAttackSequen **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1)
                                                  + 12))->SetPause();
    sub_4DB940(*(_BYTE **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12), 0);
    ((CCBUI *)*(CCBUI **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 4))->CreateMagicWindow();
    v11 = ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleIndex(23, pData, 1);
    if ( v11 != -1 )
    {
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v11, 0 /* TODO: (int)CCBRoleState::GetCombatDialogEntry */, 0, 0, 0, 0, -1082130432, 0x40000000);
      this->UpdateRoleMP(0, v11);
      this->CheckMPRequirement(v11);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(v11, 0 /* TODO: (int)CCBStage::StartSubTask */, 0, 0, 0, 0, -1082130432, 1097859072);
      ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(v11);
    }

    *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 120) = 5;
    ((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0]
                                                                               + 1)
                                                         + 20)
                                             + 20))->Destroy();
  }
  result = *(void **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
  v13 = *((_DWORD *)result + 30);
  if ( v13 == 5 )
  {
    result = (void *)((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->FindThreadByID(*(_DWORD *)&this->m_RoleXor[6].bMagicMastered[3][1]);
    if ( (_BYTE)result )
      return result;
    *(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 124) = 2;
    return (void *)((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1))->GetRenderFlag();
  }
  if ( v13 == 7 )
  {
    if ( *(int *)(*((_DWORD *)result + 5) + 156) > 0 )
      return result;
    *((_DWORD *)result + 31) = 3;
    return (void *)((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1))->GetRenderFlag();
  }
  if ( v13 == 6 && *(int *)(*((_DWORD *)result + 5) + 156) <= 0 )
  {
    *((_DWORD *)result + 31) = 4;

    return (void *)((CCBSystem *)*(CCBSystem **)((char *)&this->m_Role[0].dwMagicID[8][0] + 1))->GetRenderFlag();
  }
  return result;
}

// 0x004F7FC0
void CCBRoleState::ProcessCombatDialog(unsigned int dwVal)
{
  int v3; // esi
  _BYTE *v4; // ebp
  int v5; // ecx
  int v6; // edi
  CCBRoleState *v7; // ebx
  CCBStage *v8; // ecx
  int RoleIndex; // esi
  int nVal; // [esp+0x38] [ebp-0x39C]
  CIniFile v11; // [esp+0x3C] [ebp-0x398] BYREF
  CCBRoleState *v12; // [esp+0x44] [ebp-0x390]
  int v13; // [esp+0x48] [ebp-0x38C]
  int v14; // [esp+0x4C] [ebp-0x388]
  _DWORD pData[11]; // [esp+0x50] [ebp-0x384] BYREF
  int roleIdx[3]; // [esp+0x7C] [ebp-0x358] BYREF
  char v17[32]; // [esp+0x88] [ebp-0x34C] BYREF
  char v18[32]; // [esp+A8h] [ebp-0x32C] BYREF
  char v19[256]; // [esp+C8h] [ebp-0x30C] BYREF
  char v20[256]; // [esp+0x1C8] [ebp-0x20C] BYREF
  char Buffer[256]; // [esp+0x2C8] [ebp-0x10C] BYREF
  int v22; // [esp+0x3D0] [ebp-0x4]

  v3 = 0;
  ++*(_DWORD *)&g_TempBuffer1024[912];
v14 = 0;
  v13 = 0;
  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
  memset(pData, 0, sizeof(pData));
  if ( !BYTE1(this->m_Role[0].dwMagicID[7][5])
    || dwVal > 4
    || *(int *)&this->m_Role[0].bMagicMastered[7][892 * dwVal + 3] <= 0
    || *(float *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 80)
     - *(float *)((char *)&this->m_Role[0].dwMagicID[7][4] + 1) < 10.0 )
  {
    return;
  }
  v22 = 0;
  ((CIniFile *)&v11)->OpenFileRead("datascript\\combat.ini");
  this->GetSlotActionType(dwVal, v18);
  sprintf(Buffer, "%s-CombatDialog", v18);
  ((CIniFile *)&v11)->ReadSection(Buffer);
  this->GetRoleMP(1);
  nVal = v14;
  if ( v14 >= v13 )
    goto LABEL_29;
  v4 = &this->m_Role[0].bMagicMastered[8][892 * v14 + 1];
  v5 = unk_5DFDEC;
  while ( 1 )
  {
    ++*(_DWORD *)&g_TempBuffer1024[912];
    v5 = 214013 * v5 + 2531011;
    unk_5DFDEC = v5;
    v6 = ((v5 >> 16) & 0x7FFF) % 10;
    if ( *(v4 - 15) )
    {
      if ( *(v4 - 14) )
        break;
    }
LABEL_24:
    v4 += 892;
    if ( ++nVal >= v13 )
      goto LABEL_25;
  }
  ((CCBRoleState *)v12)->GetSlotActionType(nVal, v17);
  if ( nVal != dwVal )
  {
    if ( *((_DWORD *)v4 - 1) < 3 * *(_DWORD *)v4 / 10 )
    {
      sprintf(v19, "%sHPLow%d", v17, v6);
      v3 = ((CIniFile *)&v11)->ReadLine(v19, v20, 255);
      if ( v3 )
        goto LABEL_26;
    }
    goto LABEL_15;
  }
  if ( *((_DWORD *)v4 - 1) >= *(_DWORD *)v4 / 10
    || (sprintf(v19, "Dying%d", v6), v3 = ((CIniFile *)&v11)->ReadLine(v19, v20, 255), v3 != 1) )
  {
LABEL_15:
    if ( ((CCBRoleState *)v12)->IsRoleInForce(nVal) )
    {
      sprintf(v19, "Poison%d", v6);
      v3 = ((CIniFile *)&v11)->ReadLine(v19, v20, 255);
      if ( v3 )
        goto LABEL_26;
    }
    if ( v4[566] || v4[567] || v4[568] )
    {
      sprintf(v19, "%sSleep%d", v17, v6);
      v3 = ((CIniFile *)&v11)->ReadLine(v19, v20, 255);
      if ( v3 )
        goto LABEL_26;
    }
    if ( *((_DWORD *)v4 + 1) == *((_DWORD *)v4 + 2) )
    {
      sprintf(v19, "GPFull%d", v6);
      v3 = ((CIniFile *)&v11)->ReadLine(v19, v20, 255);
      if ( v3 )
        goto LABEL_26;
    }
    v5 = unk_5DFDEC;
    goto LABEL_24;
  }
LABEL_25:
  if ( !v3 )
    goto LABEL_29;
LABEL_26:
  v7 = v12;
  pData[2] = dwVal;
  strcpy(this->m_sCombatDialog, v20);
  pData[3] = dwVal;
  v8 = *(CCBStage **)((char *)&v7->m_Role[0].dwMagicID[8][1] + 1);
  LOBYTE(pData[10]) = 1;
  pData[0] = 259;
  pData[1] = 0;
  LOWORD(pData[4]) = 0;
  RoleIndex = ((CCBStage *)v8)->GetRoleIndex(29, pData, 1);
  if ( RoleIndex != -1 )
  {
    ((CCBRoleState *)v7)->CheckRoleStatus((int)roleIdx);
    ((CCBStage *)*(CCBStage **)((char *)&v7->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcShowFiveLineup */, 0, 0, 0, roleIdx, -1082130432, 0x40000000);
    ((CCBStage *)*(CCBStage **)((char *)&v7->m_Role[0].dwMagicID[8][1] + 1))->GetStageRoleByIdx(RoleIndex);
  }
  *(unsigned int *)((char *)&v7->m_Role[0].dwMagicID[7][4] + 1) = *(_DWORD *)(*(unsigned int *)((char *)&v7->m_Role[0].dwMagicID[8][0] + 1)
                                                                                + 80);
LABEL_29:
  v22 = -1;
}

// 0x004F8480
int CCBRoleState::UpdateEffects()
{
  int v2; // ebx
  int result; // eax
  int v4; // edi
  int v5; // eax
  int v6; // ecx
  char RoleField; // al
  void ( **v8)(int); // edx
  char v9; // al
  void ( **v10)(int); // edx
  char v11; // al
  void ( **v12)(int); // edx
  char v13; // al
  void ( **v14)(int); // edx
  char v15; // al
  void ( **v16)(int); // edx
  char v17; // al
  void ( **v18)(int); // edx
  char v19; // al
  void ( **v20)(int); // edx
  char v21; // al
  void ( **v22)(int); // edx
  char v23; // al
  void ( **v24)(int); // edx
  char v25; // al
  void ( **v26)(int); // edx
  char v27; // al
  void ( **v28)(int); // edx
  char v29; // al
  void ( **v30)(int); // edx
  char v31; // al
  void ( **v32)(int); // edx
  char v33; // al
  void ( **v34)(int); // edx
  char v35; // al
  void ( **v36)(int); // edx
  char v37; // al
  void ( **v38)(int); // edx
  char v39; // al
  void ( **v40)(int); // edx
  char v41; // al
  void ( **v42)(int); // edx
  char v43; // al
  int ( **v44)(int); // edx
  float fValue; // [esp+0x0] [ebp-0x30]
  float fValuea; // [esp+0x0] [ebp-0x30]
  float fValueb; // [esp+0x0] [ebp-0x30]
  float fValuec; // [esp+0x0] [ebp-0x30]
  float fValued; // [esp+0x0] [ebp-0x30]
  float fValuee; // [esp+0x0] [ebp-0x30]
  float fValuef; // [esp+0x0] [ebp-0x30]
  int fValueg; // [esp+0x0] [ebp-0x30]
  int fValueh; // [esp+0x0] [ebp-0x30]
  CCBStage *v54; // [esp+0x28] [ebp-0x8]
  int *v55; // [esp+0x2C] [ebp-0x4]

  v2 = 0;
  v54 = *(CCBStage **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 20) + 68);
  do
  {
    result = (int)&this->m_sCombatDialog[892 * v2];
    v55 = (int *)result;
    if ( *(_BYTE *)(result + 577) )
    {
      v4 = *(unsigned __int8 *)(result + 576);
      fValue = (float)*(int *)(result + 592);
      ((UIScrollBar *)*(UIScrollBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v4 + 1020))->SetRange(fValue);
      fValuea = (float)v55[150];
      ((UIScrollBar *)*(UIScrollBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v4 + 1036))->SetRange(fValuea);
      fValueb = (float)v55[152];
      ((UIScrollBar *)*(UIScrollBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v4 + 1052))->SetRange(fValueb);
      fValuec = (float)v55[147];
      ((UIProgressBar *)*(UIProgressBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v4 + 1020))->FindChildByName(fValuec);
      fValued = (float)v55[149];
      ((UIProgressBar *)*(UIProgressBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v4 + 1036))->FindChildByName(fValued);
      fValuee = (float)v55[151];
      ((UIProgressBar *)*(UIProgressBar **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v4 + 1052))->FindChildByName(fValuee);
      if ( !v2 )
      {
        v5 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1);
        if ( *(_DWORD *)(*(_DWORD *)(v5 + 120) + 56) == 1 )
        {
          fValuef = *(float *)((char *)&this->m_Role[1].dwMagicID[6][4] + 1) * 0.25;
          ((UIProgressBar *)*(UIProgressBar **)(v5 + 1068))->FindChildByName(fValuef);
          if ( *(int *)&this->m_Role[0].bMagicMastered[7][3] > 0 )
          {
            v6 = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1);
            if ( *(float *)(v6 + 80) - *(float *)((char *)&this->m_RoleXor[6].byMagicUseTime[2][2] + 1) > 0.1 )
            {
              *(float *)&fValueg = *(float *)((char *)&this->m_Role[1].dwMagicID[6][4] + 1) * 0.1;
              ((C2DSpark *)*(C2DSpark **)(v6 + 52))->CreateMore(25, 570, 20, fValueg);
              if ( *(float *)((char *)&this->m_Role[1].dwMagicID[6][4] + 1) > 199.89999 )
              {
                *(float *)&fValueh = *(float *)((char *)&this->m_Role[1].dwMagicID[6][4] + 1) * 0.1;
                ((C2DSpark *)*(C2DSpark **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 52))->CreateMore(25, 570, 20, fValueh);
              }
              *(float *)((char *)&this->m_RoleXor[6].byMagicUseTime[2][2] + 1) = *(float *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1)
                                                                                          + 80);
            }
          }
        }
      }
      result = *(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1);
      if ( *(_DWORD *)(*(_DWORD *)(result + 4 * v4 + 120) + 56) == 1 )
      {
        ((CCBStage *)v54)->AddTextLabel(dword_17AA808[v4] + 22, dword_17AA818[v4] + 5);
        ((CCBStage *)v54)->AddTextLabel(dword_17AA828[v4] + 31, dword_17AA838[v4] + 5);
        ((CCBStage *)v54)->AddTextLabel(dword_17AA848[v4] + 23, dword_17AA858[v4] + 5);
        if ( !this->GetRoleField(v2, 3)
          && !this->GetRoleField(v2, 4)
          && !this->GetRoleField(v2, 2)
          && !this->GetRoleField(v2, 1) )
        {
          this->GetRoleField(v2, 5);
        }
        ((NPC *)*(NPC **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v2 + 136))->NPC::UpdateAnim();
        if ( v55[147] <= 0 )
          ((NPC *)*(NPC **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 4 * v2 + 136))->NPC::UpdateAnim();
        RoleField = this->GetRoleField(v2, 6);
        v8 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                          + 4 * v4
                                          + 176);
        if ( RoleField )
          (*v8)(1);
        else
          (*v8)(0);
        v9 = this->GetRoleField(v2, 7);
        v10 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 220);
        if ( v9 )
          (*v10)(1);
        else
          (*v10)(0);
        v11 = this->GetRoleField(v2, 8);
        v12 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 264);
        if ( v11 )
          (*v12)(1);
        else
          (*v12)(0);
        v13 = this->GetRoleField(v2, 9);
        v14 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 308);
        if ( v13 )
          (*v14)(1);
        else
          (*v14)(0);
        v15 = this->GetRoleField(v2, 12);
        v16 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 440);
        if ( v15 )
          (*v16)(1);
        else
          (*v16)(0);
        v17 = this->GetRoleField(v2, 13);
        v18 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 484);
        if ( v17 )
          (*v18)(1);
        else
          (*v18)(0);
        v19 = this->GetRoleField(v2, 10);
        v20 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 352);
        if ( v19 )
          (*v20)(1);
        else
          (*v20)(0);
        v21 = this->GetRoleField(v2, 11);
        v22 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 396);
        if ( v21 )
          (*v22)(1);
        else
          (*v22)(0);
        v23 = this->GetRoleField(v2, 14);
        v24 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 528);
        if ( v23 )
          (*v24)(1);
        else
          (*v24)(0);
        v25 = this->GetRoleField(v2, 15);
        v26 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 572);
        if ( v25 )
          (*v26)(1);
        else
          (*v26)(0);
        v27 = this->GetRoleField(v2, 16);
        v28 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 616);
        if ( v27 )
          (*v28)(1);
        else
          (*v28)(0);
        v29 = this->GetRoleField(v2, 17);
        v30 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 660);
        if ( v29 )
          (*v30)(1);
        else
          (*v30)(0);
        v31 = this->GetRoleField(v2, 18);
        v32 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 704);
        if ( v31 )
          (*v32)(1);
        else
          (*v32)(0);
        v33 = this->GetRoleField(v2, 19);
        v34 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 748);
        if ( v33 )
          (*v34)(1);
        else
          (*v34)(0);
        v35 = this->GetRoleField(v2, 20);
        v36 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 792);
        if ( v35 )
          (*v36)(1);
        else
          (*v36)(0);
        v37 = this->GetRoleField(v2, 21);
        v38 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 836);
        if ( v37 )
          (*v38)(1);
        else
          (*v38)(0);
        v39 = this->GetRoleField(v2, 22);
        v40 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 880);
        if ( v39 )
          (*v40)(1);
        else
          (*v40)(0);
        v41 = this->GetRoleField(v2, 23);
        v42 = **(void ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                           + 4 * v4
                                           + 924);
        if ( v41 )
          (*v42)(1);
        else
          (*v42)(0);
        v43 = this->GetRoleField(v2, 26);
        v44 = **(int ( ****)(int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                          + 4 * v4
                                          + 968);
        if ( v43 )
          result = (*v44)(1);
        else
          result = (*v44)(0);
      }
    }
    ++v2;
  }
  while ( v2 < 5 );
  return result;
}

// 0x004F8AF0
void CCBRoleState::ProcessControlInput()
{
  unsigned __int8 *v2; // edi
  int v3; // ebp
  _BYTE *v4; // ebx
  CCBControl *v5; // ecx
  int v6; // [esp+0x0] [ebp-0x10]
  int v7; // [esp+0x4] [ebp-0xC]

  v2 = 0;
  v3 = 24;
  v4 = &this->m_Role[0].bMagicMastered[5][4];
  do
  {
    if ( *v4 )
    {
      *(float *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + v3) + 6632) = *(float *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + v3) + 6636);
      *(_BYTE *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + v3) + 280) = 0;
      this->ProcessRound((unsigned int)v2);
      this->ProcessRound((unsigned int)v2);
      this->ProcessRound((unsigned int)v2);
      v5 = *(CCBControl **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 8);
      if ( v5->m_bActive )
      {
        if ( (unsigned __int8 *)((CCBControl *)v5)->GetControl() == v2 )
          ((CCBControl *)*(CCBControl **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 8))->GetState();
      }
      ((CCBStage *)v2)->IsTaskValidButNotFinish(v6, v7);
    }
    v3 += 4;
    ++v2;
    v4 += 892;
  }
  while ( v3 < 44 );
}

// 0x004F8BB0
int CCBRoleState::InitSlot(int idx, int nRoleID)
{
  char *v4; // ebp
  int v5; // eax
  int v6; // ecx
  char v7; // al
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edi
  void ( ***v16)(_DWORD, int); // ecx
  int *v17; // eax
  int result; // eax
  int *idxa; // [esp+0x18] [ebp+0x4]

  v4 = &this->m_sCombatDialog[892 * idx];
  memset(v4 + 552, 0, 0x37Cu);
  v4[577] = 1;
  v4[578] = 1;
  v4[579] = 0;
  *((_DWORD *)v4 + 138) = nRoleID;
  *((_DWORD *)v4 + 348) = -1;
  *((_DWORD *)v4 + 284) = idx - 4;
  v4[1389] = 1;
  v4[1384] = 1;
  v4[1385] = 1;
  v4[1386] = 1;
  v4[1387] = 1;
  v4[1388] = 1;
  ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)v4 + 138));
  v6 = v5;
  v4[580] = 0;
  v7 = *(_BYTE *)(v5 + 518);
  if ( v7 == 98 || v7 == 66 )
  {
    v4[580] = 1;
    v4[1167] = 1;
    *((_WORD *)v4 + 637) = 0x7FFF;
  }
  if ( *(_BYTE *)(v6 + 709) )
  {
    v4[1167] = 1;
    *((_WORD *)v4 + 637) = 0x7FFF;
  }
  *((_DWORD *)v4 + 148) = *(_DWORD *)(v6 + 636);
  *((_DWORD *)v4 + 150) = *(_DWORD *)(v6 + 640);
  *((_DWORD *)v4 + 152) = *(_DWORD *)(v6 + 644);
  *((_DWORD *)v4 + 147) = *((_DWORD *)v4 + 148);
  *((_DWORD *)v4 + 149) = *((_DWORD *)v4 + 150);
  *((_DWORD *)v4 + 151) = *((_DWORD *)v4 + 152);
  *((_DWORD *)v4 + 146) = *(_DWORD *)(v6 + 632);
  *((_DWORD *)v4 + 153) = *(_DWORD *)(v6 + 648);
  *((_DWORD *)v4 + 154) = *(_DWORD *)(v6 + 652);
  *((_DWORD *)v4 + 155) = *(_DWORD *)(v6 + 656);
  *((_DWORD *)v4 + 156) = *(_DWORD *)(v6 + 660);
  *((_DWORD *)v4 + 176) = *(_DWORD *)(v6 + 740);
  *((_DWORD *)v4 + 160) = *(_DWORD *)(v6 + 748);
  *((_DWORD *)v4 + 274) = *(__int16 *)(v6 + 842);
  *((_DWORD *)v4 + 275) = *(_DWORD *)(v6 + 844);
  *((_DWORD *)v4 + 276) = *(__int16 *)(v6 + 848);
  v4[1430] = *(float *)(v6 + 796) <= 0.0;
  *((_DWORD *)v4 + 359) = (__int64)*(float *)(v6 + 724);
  v4[1432] = 0;
  v4[1431] = 0;
  v8 = *((_DWORD *)v4 + 147);
  if ( v8 >= 1000 )
  {
    if ( v8 >= 10000 )
    {
      if ( v8 >= 100000 )
        *((_DWORD *)v4 + 360) = &g_EffMgr;
      else
        *((_DWORD *)v4 + 360) = &g_EffMgr;
    }
    else
    {
      *((_DWORD *)v4 + 360) = &g_EffMgr;
    }
  }
  else
  {
    *((_DWORD *)v4 + 360) = &g_EffMgr;
  }
  v9 = *((_DWORD *)v4 + 160);
  if ( v9 == 916 || v9 == 917 || v9 == 921 || v9 == 922 || v9 == 926 || v9 == 927 )
    v4[649] = 1;
  v10 = *((_DWORD *)v4 + 160);
  if ( v10 == 918 || v10 == 919 || v10 == 920 || v10 == 923 || v10 == 928 )
    v4[650] = 1;
  strcpy(v4 + 560, (const char *)(v6 + 518));
  v11 = 580;
  idxa = (int *)(v4 + 1112);
  do
  {
    ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)v4 + 138));
    v13 = *(_DWORD *)(v12 + v11) << 16;
    ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)v4 + 138));
    v15 = *(_DWORD *)(v14 + v11) | v13;
    v11 += 4;
    *idxa++ = v15;
  }
  while ( v11 < 600 );
  v16 = *(void ( ****)(_DWORD, int))(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                             + 4 * idx
                                             + 76);
  (**v16)(v16, 1);
  ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->InitCombatSlot(idx);
  ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdData(idx);
  ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->GetCmdSlot(idx);
  ((CCBSystem *)*(CCBSystem **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 12))->SetCmdParam(idx, 0);
  ((CCBStageRole *)*(CCBStageRole **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * idx + 24))->IsAtProtectPos(idx, nRoleID, 0);
  ((CCBStageShadow *)*(CCBStageShadow **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 72))->Reset();
  ((CCBAI *)*(CCBAI **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 24))->RepeatPlayerLastOperation();
  v17 = *(int **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * idx + 24);
  LOBYTE(result) = ((CEffMgr *)*(CEffMgr **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 44))->Init(321, v17[1649], v17[1650], v17[1651], 0);
  return result;
}

// 0x004F8FA0
char CCBRoleState::LoadRoleModel(int nVal)
{
  this->InitSlot(nVal, 739);
  return ((CCBStageScene *)*(CCBStageScene **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 20))->LoadModel(aZ39);
}

// 0x004F8FD0
char CCBRoleState::SpawnRandomEnemies(int nVal, int nVal2)
{
  int v4; // eax
  int v5; // ecx
  int v6; // ebx
  int v7; // ecx
  int v8; // esi
  int v9; // edx
  int *v10; // eax
  int v11; // edx
  int nRoleID; // [esp+0x4] [ebp-0xC] BYREF
  int v14; // [esp+0x8] [ebp-0x8]
  int v15; // [esp+0xC] [ebp-0x4]

  nRoleID = 7369;
  v14 = 7368;
  v15 = 7370;
  v4 = this->Update(2);
  if ( v4 == 1 )
  {
    if ( !HIBYTE(this->m_Role[8].fHPIncPerRound) || (LOBYTE(v4) = BYTE1(this->m_Role[9].dwMagicID[6][5]), (_BYTE)v4) )
    {
      if ( !this->m_BufferData[105] || (LOBYTE(v4) = this->m_BufferData[959], (_BYTE)v4) )
      {
        v5 = unk_5DFDEC;
        v6 = 16;
        do
        {
          v7 = 214013 * v5 + 2531011;
          *(_DWORD *)&g_TempBuffer1024[912] += 2;
          v8 = ((v7 >> 16) & 0x7FFF) % 3;
          v5 = 214013 * v7 + 2531011;
          unk_5DFDEC = v5;
          v9 = ((v5 >> 16) & 0x7FFF) % 3;
          if ( v8 != v9 )
          {
            v10 = &nRoleID + v9;
            v11 = *(&nRoleID + v8);
            *(&nRoleID + v8) = *v10;
            *v10 = v11;
            v5 = unk_5DFDEC;
          }
          --v6;
        }
        while ( v6 );
        this->InitSlot(5, nRoleID);
        LOBYTE(v4) = this->InitSlot(7, v14);
      }
    }
  }
  return v4;
}

// 0x004F90F0
char * CCBRoleState::CheckRoleCanAct(int roleIdx)
{
  char *result; // eax
  int *v4; // edx
  int v5; // ebx
  int v6; // ebp
  int v7; // eax
  int nVal4; // [esp+0x10] [ebp-0x4]

  result = &this->m_sCombatDialog[892 * roleIdx];
  if ( result[577] && !result[1432] && !result[1431] )
  {
    v4 = (int *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * roleIdx + 24)
               + 6584);
    v5 = *v4;
    v6 = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1) + 4 * roleIdx + 24)
                   + 6588);
    nVal4 = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][1] + 1)
                                  + 4 * roleIdx
                                  + 24)
                      + 6592);
    ((CEffMgr *)*(CEffMgr **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 44))->Init(324, *v4, v6, nVal4, 0);
    ((CEffMgr *)*(CEffMgr **)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][0] + 1) + 44))->Init(325, v5, v6, nVal4, 0);
    v7 = this->SetRoleField(roleIdx, 0);
    return (char *)((CCBSystem *)this)->AddCommand(roleIdx, -v7, 0);
  }
  return result;
}

// 0x004F91B0
char * CCBRoleState::PopulateItemList(int nSlot)
{
  int v3; // ecx
  char *result; // eax
  int v5; // ebx
  int RoleNum; // ebp
  int v7; // edi
  bool v8; // cc
  int v9; // [esp+0x10] [ebp-0x34]
  char *v10; // [esp+0x14] [ebp-0x30]
  int p_DWORD[11]; // [esp+0x18] [ebp-0x2C] BYREF
  int *nSlota; // [esp+0x48] [ebp+0x4]

  memset(p_DWORD, 0, sizeof(p_DWORD));
  ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                                + 1128)
                                    + 80))->ClearAll();
  v3 = 0;
  p_DWORD[2] = nSlot;
  p_DWORD[3] = -1;
  LOWORD(p_DWORD[4]) = 0;
  LOBYTE(p_DWORD[10]) = 1;
  p_DWORD[0] = 260;
  v9 = 0;
  result = &this->m_sCombatDialog[892 * nSlot];
  v10 = result;
  nSlota = (int *)(result + 712);
  while ( 1 )
  {
    v5 = *nSlota;
    if ( result[v3 + 736] && v5 )
    {
      RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*nSlota);
      v7 = ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1128) + 80))->SetItemOffset((char *)&pTarget.m_nTargetType + 224, 0);
      ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1128) + 80))->SetMouseMoveSel(0, v7, (char *)(RoleNum + 28), 0);
      sprintf((char *const)&g_RoleSystemCombat.m_partyUI3._todo_05C + 23, "%2d", *(_DWORD *)(RoleNum + 688));
      ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1128) + 80))->SetMouseMoveSel(1, v7, (char *)&g_RoleSystemCombat.m_partyUI3._todo_05C + 23, 0);
      p_DWORD[1] = v5;
      if ( this->CheckMagicCost(p_DWORD) && this->CheckEventCondition((int)p_DWORD) )
        result = (char *)((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                                     + 1128)
                                         + 80))->SetChildParam(v7, 1);
      else
        result = (char *)((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                                     + 1128)
                                         + 80))->SetChildParam(v7, 0);
    }
    v3 = v9 + 1;
    v8 = ++v9 < 6;
    ++nSlota;
    if ( !v8 )
      break;
    result = v10;
  }
  return result;
}

// 0x004F9340
int CCBRoleState::GetDialogSlot(int nVal, int nVal2)
{
  int v3; // edi
  int v4; // edx
  char *v5; // esi
  int *i; // ecx
  int result; // eax

  v3 = 0;
  v4 = 0;
  v5 = &this->m_sCombatDialog[892 * nVal];
  for ( i = (int *)(v5 + 712); ; ++i )
  {
    result = *i;
    if ( v5[v4 + 736] )
      ++v3;
    if ( v3 == nVal2 + 1 )
      break;
    if ( ++v4 >= 6 )
      return 0;
  }
  return result;
}

// 0x004F9390
unsigned int CCBRoleState::PopulateMagicList(int nSlot)
{
  int v3; // edi
  char *v4; // eax
  unsigned int *v5; // ebx
  int v6; // ecx
  unsigned int result; // eax
  int RoleNum; // ebx
  int v9; // ebp
  bool v10; // cc
  int v11; // [esp+0x10] [ebp-0x38]
  unsigned int *v12; // [esp+0x14] [ebp-0x34]
  int v13; // [esp+0x18] [ebp-0x30]
  int p_DWORD[11]; // [esp+0x1C] [ebp-0x2C] BYREF
  int nSlota; // [esp+0x4C] [ebp+0x4]

  memset(p_DWORD, 0, sizeof(p_DWORD));
  p_DWORD[3] = -1;
  p_DWORD[2] = nSlot;
  LOWORD(p_DWORD[4]) = 0;
  LOBYTE(p_DWORD[10]) = 1;
  p_DWORD[0] = 261;
  v3 = 76;
  v4 = &this->m_sCombatDialog[892 * nSlot];
  v5 = (unsigned int *)(v4 + 744);
  nSlota = (int)(v4 + 984);
  do
  {
    ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                                  + 1124)
                                      + v3))->ClearAll();
    v6 = 0;
    v12 = v5;
    v11 = 0;
    do
    {
      result = *v5;
      v13 = *v5;
      if ( *(_BYTE *)(nSlota + v6 - 48) && result )
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(result);
        v9 = ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1124)
                             + v3))->SetItemOffset((char *)&pTarget.m_nTargetType + 224, 0);
        ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1124) + v3))->SetMouseMoveSel(0, v9, (char *)(RoleNum + 28), 0);
        sprintf((char *const)&g_RoleSystemCombat.m_configData[69], "%2d", *(_DWORD *)(RoleNum + 692));
        ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1124) + v3))->SetMouseMoveSel(1, v9, (char *)&g_RoleSystemCombat.m_configData[69], 0);
        sprintf(
          (char *const)&g_RoleSystemCombat.m_configData[69],
          "%d/%02d",
          *(unsigned __int8 *)(nSlota + v11 + 48) + 1,
          *(unsigned __int8 *)(nSlota + v11));
        ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1124) + v3))->SetMouseMoveSel(2, v9, (char *)&g_RoleSystemCombat.m_configData[69], 0);
        p_DWORD[1] = v13;
        if ( this->CheckMagicCost(p_DWORD) && this->CheckEventCondition((int)p_DWORD) )
          result = ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                               + 1124)
                                   + v3))->SetChildParam(v9, 1);
        else
          result = ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1)
                                               + 1124)
                                   + v3))->SetChildParam(v9, 0);
      }
      v6 = v11 + 1;
      v5 = v12 + 1;
      v10 = ++v11 < 8;
      ++v12;
    }
    while ( v10 );
    v3 += 4;
    nSlota += 8;
  }
  while ( v3 < 100 );
  return result;
}

// 0x004F9590
int CCBRoleState::GetMagicSlotData(int nVal, int nVal2, int nVal3)
{
  int v4; // ebx
  int v5; // esi
  int *v6; // edx
  char *v7; // ecx
  int result; // eax

  v4 = 0;
  v5 = 0;
  v6 = (int *)(&this->m_Role[1].bCanAction + 892 * nVal + 32 * nVal2);
  v7 = (char *)&this->m_Role[1].dwMagicID[0][223 * nVal + 2 + 2 * nVal2] + 1;
  while ( 1 )
  {
    result = *v6;
    if ( v7[v5] )
      ++v4;
    if ( nVal3 + 1 == v4 )
      break;
    ++v5;
    ++v6;
    if ( v5 >= 8 )
      return 0;
  }
  return result;
}

// 0x004F95F0
int CCBRoleState::PopulateTargetList(int nSlot, int nType)
{
  signed int v4; // ebp
  int v5; // eax
  int result; // eax
  int v7; // ebx
  _DWORD *v8; // eax
  _DWORD *v9; // eax
  int v10; // [esp+0xC] [ebp-0x54]
  _BYTE pOut[12]; // [esp+0x10] [ebp-0x50] BYREF
  _BYTE v12[12]; // [esp+0x1C] [ebp-0x44] BYREF
  _BYTE v13[12]; // [esp+0x28] [ebp-0x38] BYREF
  int nVal[11]; // [esp+0x34] [ebp-0x2C] BYREF

  v4 = 0;
  memset(nVal, 0, sizeof(nVal));
  v10 = 0;
  if ( nType )
  {
    if ( nType == 1 )
    {
      v5 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(2);
    }
    else
    {
      if ( nType != 2 )
        goto LABEL_8;
      v5 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(15);
    }
  }
  else
  {
    v5 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(14);
  }
  v10 = v5;
LABEL_8:
  ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert((void *)3);
  result = ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2]
                                                                               + 1)
                                                         + 1120)
                                             + 4 * nType
                                             + 80))->ClearAll();
  if ( v10 > 0 )
  {
    do
    {
      v7 = ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1120)
                           + 4 * nType
                           + 80))->SetItemOffset((char *)&pTarget.m_nTargetType + 224, 0);
      v8 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, v4);
      ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1120)
                      + 4 * nType
                      + 80))->SetMouseMoveSel(0, v7, (char *)(v8[2] + 4), 0);
      v9 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v12, v4);
      sprintf((char *const)&g_RoleSystemCombat.m_configData[5], "%2d", v9[1]);
      ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1120)
                      + 4 * nType
                      + 80))->SetMouseMoveSel(1, v7, (char *)&g_RoleSystemCombat.m_configData[5], 0);
      nVal[1] = **((_DWORD **)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v13, v4) + 2);
      if ( !((CCBSystem *)this)->IsMagicSlotMsg((int)nVal)
        || ((CCBSystem *)this)->HandleMagicCommand((int)nVal) )
      {
        ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1120)
                        + 4 * nType
                        + 80))->SetChildParam(v7, 1);
      }
      else
      {
        ((UIListBox *)*(UIListBox **)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1120)
                        + 4 * nType
                        + 80))->SetChildParam(v7, 0);
      }
      result = v10;
      ++v4;
    }
    while ( v4 < v10 );
  }
  return result;
}

// 0x004F9790
int CCBRoleState::UpdateCommandButtons(int nSlot)
{
  int result; // eax
  char *v3; // esi
  int v4; // edx
  int v5; // edx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // ecx

  result = 0;
  v3 = &this->m_sCombatDialog[892 * nSlot];
  v4 = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1132) + 96);
  if ( v3[1384] )
  {
    *(_DWORD *)(v4 + 80) = 1;
    *(_BYTE *)(v4 + 68) = 1;
  }
  else
  {
    *(_DWORD *)(v4 + 80) = 0;
    *(_BYTE *)(v4 + 68) = 0;
  }
  v5 = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1132) + 104);
  if ( v3[1386] )
  {
    *(_DWORD *)(v5 + 80) = 1;
    *(_BYTE *)(v5 + 68) = 1;
  }
  else
  {
    *(_DWORD *)(v5 + 80) = 0;
    *(_BYTE *)(v5 + 68) = 0;
  }
  v6 = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1132) + 108);
  if ( v3[1385] )
  {
    *(_DWORD *)(v6 + 80) = 1;
    *(_BYTE *)(v6 + 68) = 1;
  }
  else
  {
    *(_DWORD *)(v6 + 80) = 0;
    *(_BYTE *)(v6 + 68) = 0;
  }
  v7 = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1132) + 100);
  if ( v3[1387] )
  {
    *(_DWORD *)(v7 + 80) = 1;
    *(_BYTE *)(v7 + 68) = 1;
  }
  else
  {
    *(_DWORD *)(v7 + 80) = 0;
    *(_BYTE *)(v7 + 68) = 0;
  }
  v8 = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1132) + 112);
  if ( v3[1388] )
  {
    *(_DWORD *)(v8 + 80) = 0;
    *(_BYTE *)(v8 + 68) = 0;
  }
  else
  {
    *(_DWORD *)(v8 + 80) = 1;
    *(_BYTE *)(v8 + 68) = 1;
  }
  if ( v3[1389] )
  {
    result = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1132) + 116);
    *(_DWORD *)(result + 80) = 1;
    *(_BYTE *)(result + 68) = 1;
  }
  else
  {
    v9 = *(_DWORD *)(*(_DWORD *)(*(unsigned int *)((char *)&this->m_Role[0].dwMagicID[8][2] + 1) + 1132) + 116);
    *(_DWORD *)(v9 + 80) = 0;
    *(_BYTE *)(v9 + 68) = 0;
  }
  return result;
}

// 0x004F98B0
int CCBRoleState::ApplyDamage(int roleIdx, int dmg)
{
  int v3; // ebx
  int v4; // edi
  int RoleState; // eax
  int v7; // ebx
  signed int v8; // esi
  int v9; // edx
  int v10; // edi
  __int64 v11; // rax
  unsigned int v12; // ebx
  int v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int RoleHP; // eax
  int v19; // ecx
  _DWORD *v20; // edx
  int v21; // eax
  int v22; // edi
  int v23; // ebx
  int v24; // eax
  int v25; // edi
  int SpeedBonus; // edi
  int v27; // edi
  int v28; // ebx
  int AttackBonus; // edi
  int v30; // edi
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int v34; // eax
  int v36; // [esp-0x4] [ebp-0x1C]
  int v37; // [esp-0x4] [ebp-0x1C]
  int v38; // [esp+0xC] [ebp-0xC]
  int nIndex; // [esp+0x10] [ebp-0x8] BYREF
  int pnVal2; // [esp+0x14] [ebp-0x4] BYREF
  int *roleIdxa; // [esp+0x20] [ebp+0x8]
  int roleIdxb; // [esp+0x20] [ebp+0x8]
  int *roleIdxc; // [esp+0x20] [ebp+0x8]
  int pnVal; // [esp+0x28] [ebp+0x10] BYREF
  int v45; // [esp+0x2C] [ebp+0x14]
  int nVal; // [esp+0x30] [ebp+0x18]

  v3 = 0;
  v4 = 0;
  nIndex = 0;
  pnVal2 = 0;
  switch ( roleIdx )
  {
    case 1:
      RoleState = this->GetRoleState(pnVal);
      v7 = dmg;
      v45 = 10 * (this->GetRoleState(dmg) + 8 - RoleState);
      *(float *)&dmg = (double)v45
                     * *(float *)((char *)&this->m_Role[0].byMagicUseTime[5][446 * v7 + 5] + 1)
                     * 0.0099999998;
      pnVal = (int)*(float *)&dmg;
      v4 = pnVal + v45;
      dmg = pnVal + v45;
      if ( !unk_5DFDEB )
        goto LABEL_76;
      *(float *)&dmg = (double)dmg * 0.2;
      pnVal = (int)*(float *)&dmg;
      v8 = abs32(pnVal);
      if ( !v8 )
        goto LABEL_76;
      v9 = (((int)(214013 * unk_5DFDEC + 2531011) >> 16) & 0x7FFF) % v8;
      *(_DWORD *)&g_TempBuffer1024[912] += 2;
      unk_5DFDEC = 214013 * (214013 * unk_5DFDEC + 2531011) + 2531011;
      if ( (((int)unk_5DFDEC >> 16) & 0x3FFu) < 0x200 )
        v10 = v4 - v9;
      else
        v10 = v9 + v4;
      LODWORD(v11) = v10;
      return v11;
    case 2:
      if ( *(float *)&v45 == 0.0 )
        goto LABEL_54;
      ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nVal);
      v12 = dmg;
      if ( (unsigned int)dmg > 4 )
      {
        roleIdxa = (int *)&this->m_sCombatDialog[892 * dmg];
        v4 = abs32((__int64)(((double)roleIdxa[146] * 0.050000001 + 0.1) * (double)v45));
        dmg = v4;
        if ( unk_5DFDEB )
        {
          *(float *)&dmg = (double)dmg * 0.1;
          *(float *)&dmg = COERCE_FLOAT(abs32((int)*(float *)&dmg));
          if ( *(float *)&dmg != 0.0 )
          {
            v14 = (((int)(214013 * unk_5DFDEC + 2531011) >> 16) & 0x7FFF) % dmg;
            *(_DWORD *)&g_TempBuffer1024[912] += 2;
            unk_5DFDEC = 214013 * (214013 * unk_5DFDEC + 2531011) + 2531011;
            if ( (((int)unk_5DFDEC >> 16) & 0x3FFu) < 0x200 )
              v4 -= v14;
            else
              v4 += v14;
          }
        }
        if ( v45 <= 0 )
          goto LABEL_23;
      }
      else
      {
        roleIdxa = (int *)&this->m_sCombatDialog[892 * dmg];
        v4 = abs32((__int64)(((double)roleIdxa[146] * 0.050000001 + 1.0) * (double)v45));
        dmg = v4;
        if ( unk_5DFDEB )
        {
          *(float *)&dmg = (double)dmg * 0.1;
          *(float *)&dmg = COERCE_FLOAT(abs32((int)*(float *)&dmg));
          if ( *(float *)&dmg != 0.0 )
          {
            v13 = (((int)(214013 * unk_5DFDEC + 2531011) >> 16) & 0x7FFF) % dmg;
            *(_DWORD *)&g_TempBuffer1024[912] += 2;
            unk_5DFDEC = 214013 * (214013 * unk_5DFDEC + 2531011) + 2531011;
            if ( (((int)unk_5DFDEC >> 16) & 0x3FFu) < 0x200 )
              v4 -= v13;
            else
              v4 += v13;
          }
        }
        if ( v45 <= 0 )
LABEL_23:
          v4 = -v4;
      }
      if ( v12 > 4 )
        goto LABEL_76;
      *(float *)&dmg = 0.0;
      pnVal = 0;
      this->CountValidSlots(v12, nVal, &dmg, &pnVal);
      this->IsAllEnemyDead(nVal, &nIndex, &pnVal2);
      if ( this->GetRole(nIndex, roleIdxa[284]) || this->GetRole(pnVal2, roleIdxa[284]) )
        v4 += v4 / 2;
      if ( nIndex > 0 && nIndex < 6 )
      {
        v36 = roleIdxa[284];
        v15 = this->CheckDeath(nIndex);
        if ( this->GetRole(v15, v36) )
          v4 += v4 / -2;
      }
      if ( pnVal2 <= 0 )
        goto LABEL_76;
      if ( pnVal2 >= 6 )
        goto LABEL_76;
      v37 = roleIdxa[284];
      v16 = this->CheckDeath(pnVal2);
      if ( !this->GetRole(v16, v37) )
        goto LABEL_76;
      LODWORD(v11) = v4 / -2 + v4;
      return v11;
    case 3:
      v17 = dmg;
      this->GetRoleHP(dmg);
      RoleHP = this->GetRoleHP(pnVal);
      *(float *)&v45 = 0.0;
      *(float *)&dmg = 0.0;
      pnVal = 0;
      roleIdxb = *(_DWORD *)&this->m_Role[0].bMagicMastered[6][892 * v17 + 5];
      this->GetRoleMP(RoleHP);
      if ( v45 < dmg )
      {
        v19 = dmg - v45;
        v20 = &this->m_Role[0].bMagicMastered[6][892 * v45 + 5];
        do
        {
          if ( *((_BYTE *)v20 - 7) )
          {
            ++pnVal;
            v3 += *v20;
          }
          v20 += 223;
          --v19;
        }
        while ( v19 );
      }
      v38 = v3 / pnVal;
      v21 = this->GetRoleState(v17);
      v22 = v45;
      v23 = v21;
      nVal = (int)&byte_FFFFFF;
      if ( v45 < dmg )
      {
        pnVal = (int)&this->m_Role[0].bMagicMastered[5][892 * v45 + 4];
        do
        {
          if ( *(_BYTE *)pnVal )
          {
            v24 = this->GetRoleState(v22);
            if ( v24 < nVal )
              nVal = this->GetRoleState(v22);
          }
          ++v22;
          pnVal += 892;
        }
        while ( v22 < dmg );
      }
      LODWORD(v11) = 10 * ((roleIdxb - v38) * (v23 - nVal) + 3);
      return v11;
    case 4:
      v25 = 5 - this->GetRoleState(pnVal);
      LODWORD(v11) = this->GetRoleState(dmg) + v25;
      return v11;
    case 5:
      SpeedBonus = this->GetSpeedBonus(dmg);
      v4 = 5 * (this->GetSpeedBonus(pnVal) - SpeedBonus);
      if ( v4 >= 0 )
        goto LABEL_76;
      LODWORD(v11) = 0;
      return v11;
    case 6:
      v27 = dmg;
      if ( this->GetRoleState(dmg) > 0 )
        return (__int64)(sqrt((double)(this->GetRoleState(v27) / 2)) * 10.0);
      else
LABEL_54:
        LODWORD(v11) = 0;
      return v11;
    case 7:
      v28 = dmg;
      roleIdxc = (int *)&this->m_sCombatDialog[892 * dmg];
      AttackBonus = this->GetAttackBonus(dmg);
      *(float *)&v45 = (double)(AttackBonus - this->GetDefenseBonus(pnVal))
                     * ((double)roleIdxc[146] * 0.0049999999 + 1.0);
      nVal = (int)*(float *)&v45;
      v30 = -nVal;
      v45 = -nVal;
      if ( unk_5DFDEB )
      {
        *(float *)&v45 = (double)v45 * 0.1;
        nVal = (int)*(float *)&v45;
        *(float *)&v45 = COERCE_FLOAT(abs32(nVal));
        if ( *(float *)&v45 == 0.0 )
        {
          v45 = v30;
        }
        else
        {
          v31 = (((int)(214013 * unk_5DFDEC + 2531011) >> 16) & 0x7FFF) % v45;
          *(_DWORD *)&g_TempBuffer1024[912] += 2;
          unk_5DFDEC = 214013 * (214013 * unk_5DFDEC + 2531011) + 2531011;
          if ( (((int)unk_5DFDEC >> 16) & 0x3FFu) < 0x200 )
            v30 -= v31;
          else
            v30 += v31;
          v28 = dmg;
          v45 = v30;
        }
      }
      else
      {
        v45 = -nVal;
      }
      if ( *((_BYTE *)roleIdxc + 650) || *((_BYTE *)roleIdxc + 649) )
      {
        if ( unk_5DFDEB )
        {
          nVal = (int)5.0;
          *(float *)&v45 = COERCE_FLOAT(abs32((int)5.0));
          if ( *(float *)&v45 == 0.0 )
          {
            v32 = 100;
          }
          else
          {
            v33 = (((int)(214013 * unk_5DFDEC + 2531011) >> 16) & 0x7FFF) % v45;
            *(_DWORD *)&g_TempBuffer1024[912] += 2;
            unk_5DFDEC = 214013 * (214013 * unk_5DFDEC + 2531011) + 2531011;
            if ( (((int)unk_5DFDEC >> 16) & 0x3FFu) < 0x200 )
              v32 = 100 - v33;
            else
              v32 = v33 + 100;
            v28 = dmg;
          }
        }
        else
        {
          v32 = 100;
        }
        v45 = v30 * (v32 - 45) / 100;
      }
      LOBYTE(v34) = this->CanAction(v28, pnVal, 0);
      *(float *)&dmg = (1.0 - (double)v34 * 0.050000001) * (double)v45;
      pnVal = (int)*(float *)&dmg;
      v4 = pnVal;
      goto LABEL_76;
    default:
LABEL_76:
      LODWORD(v11) = v4;
      return v11;
  }
}

// 0x004FA210
int CCBRoleState::GetSlotState(int nVal, int nVal2)
{
  int result; // eax

  result = 0;
  switch ( nVal )
  {
    case 0:
      result = 8 * nVal2 + 80;
      break;
    case 1:
      result = 7 * nVal2 + 75;
      break;
    case 2:
      result = 9 * nVal2 + 80;
      break;
    case 3:
      result = 7 * nVal2 + 60;
      break;
    case 4:
      result = 9 * nVal2 + 100;
      break;
    default:
      return result;
  }
  return result;
}

// 0x004FA280
int CCBRoleState::CalcSpeedByLevel(int nRole, int nLevel)
{
  double v3; // st7
  long double v4; // st7
  float v6; // [esp+0x0] [ebp-0x4]
  float nLevela; // [esp+0x10] [ebp+0xC]

  v3 = (double)nLevel;
  nLevela = 0.0;
  v6 = v3;
  switch ( nRole )
  {
    case 0:
      v4 = sqrt(v6) * 9.0 + 8.0;
      goto LABEL_7;
    case 1:
      v4 = sqrt(v6) * 9.0 + 6.0;
      goto LABEL_7;
    case 2:
      v4 = sqrt(v6) * 9.0 + 7.0;
      goto LABEL_7;
    case 3:
      v4 = sqrt(v6) * 9.0 + 5.0;
      goto LABEL_7;
    case 4:
      v4 = (sqrt(v6) + 1.0) * 9.0;
LABEL_7:
      nLevela = v4;
      break;
    default:
      return (int)nLevela;
  }
  return (int)nLevela;
}

// 0x004FA330
int CCBRoleState::GetActionTypeBySlot(int nVal, int nVal2)
{
  int result; // eax

  result = 0;
  switch ( nVal )
  {
    case 0:
      result = 4 * nVal2 + 25;
      break;
    case 1:
      result = 5 * nVal2 + 25;
      break;
    case 2:
      result = 4 * nVal2 + 22;
      break;
    case 3:
      result = 2 * (3 * nVal2 + 15);
      break;
    case 4:
      result = 4 * nVal2 + 20;
      break;
    default:
      return result;
  }
  return result;
}

// 0x004FA3A0
int CCBRoleState::CalcDefenseByLevel(int nRole, int nLevel)
{
  double v3; // st7
  float v5; // [esp+0x0] [ebp-0x4]
  float nLevela; // [esp+0x10] [ebp+0xC]

  v5 = 0.0;
  nLevela = (float)nLevel;
  switch ( nRole )
  {
    case 0:
      v3 = nLevela * 4.5 + 26.0;
      goto LABEL_7;
    case 1:
      v3 = nLevela * 4.0 + 24.0;
      goto LABEL_7;
    case 2:
      v3 = nLevela * 4.5 + 20.0;
      goto LABEL_7;
    case 3:
      v3 = nLevela * 4.0 + 22.0;
      goto LABEL_7;
    case 4:
      v3 = nLevela * 5.0 + 35.0;
LABEL_7:
      v5 = v3;
      break;
    default:
      return (int)v5;
  }
  return (int)v5;
}

// 0x004FA440
int CCBRoleState::CalcDamage(int nVal, int nVal2)
{
  double v3; // st7
  float v5; // [esp+0x0] [ebp-0x4]
  float nVal2a; // [esp+0x10] [ebp+0xC]

  v5 = 0.0;
  nVal2a = (float)nVal2;
  switch ( nVal )
  {
    case 0:
      v3 = nVal2a * 3.3 + 17.0;
      goto LABEL_7;
    case 1:
      v3 = nVal2a * 3.0 + 13.0;
      goto LABEL_7;
    case 2:
      v3 = nVal2a * 3.5 + 16.0;
      goto LABEL_7;
    case 3:
      v3 = nVal2a * 3.0 + 16.0;
      goto LABEL_7;
    case 4:
      v3 = nVal2a * 3.0 + 18.0;
LABEL_7:
      v5 = v3;
      break;
    default:
      return (int)v5;
  }
  return (int)v5;
}

// 0x004FA4E0
int CCBRoleState::FindSlotByHP@<eax>(CCBRoleState *this@<ecx>, unsigned int a2, unsigned int a3)
{
  int result; // eax
  unsigned int *i; // ecx

  result = 0;
  for ( i = (unsigned int *)((char *)&this->m_RoleXor[6].nGP + 3); *i <= a2; ++i )
  {
    if ( ++result >= 100 )
      return 100;
  }
  return result;
}

// 0x004FA510
int CCBRoleState::GetRoleCount(int nVal)
{
  int v2; // eax

  v2 = nVal;
  if ( nVal < 1 )
    return *(int *)((char *)&this->m_RoleXor[6].nGP + 3);
  if ( nVal > 100 )
    v2 = 100;
  return *(int *)((char *)&this->m_RoleXor[6].nFullHP + 4 * v2 + 3);
}

// 0x004FA540
int CCBRoleState::CheckRoleStatus(int roleIdx)
{
  int v3; // [esp+0x8] [ebp+0x8]
  int v4; // [esp+0xC] [ebp+0xC]
  int v5; // [esp+0x10] [ebp+0x10]

  *(_DWORD *)roleIdx = v3;
  *(_DWORD *)(roleIdx + 4) = v4;
  *(_DWORD *)(roleIdx + 8) = v5;
  return roleIdx;
}

// 0x004FA560
int CCBRoleState::GetSlotActionType(int nVal, char *Buffer)
{
  int result; // eax

  result = nVal;
  switch ( nVal )
  {
    case 0:
      result = sprintf(Buffer, "Jingtian");
      break;
    case 1:
      result = sprintf(Buffer, "Xuejian");
      break;
    case 2:
      result = sprintf(Buffer, "Longkui");
      break;
    case 3:
      result = sprintf(Buffer, "Zixuan");
      break;
    case 4:
      result = sprintf(Buffer, "Changqing");
      break;
    default:
      return result;
  }
  return result;
}

// 0x004FA5F0
int CCBRoleState::FindRoleByID(int nVal)
{
  int result; // eax
  _BYTE *i; // ecx

  result = 0;
  for ( i = &this->m_Role[0].bMagicMastered[1][3]; !i[25] || nVal != *(_DWORD *)i; i += 892 )
  {
    if ( ++result >= 11 )
      return -1;
  }
  return result;
}

// 0x004FA620
int CCBRoleState::CountValidSlots(int nVal, int nVal2, int *p_DWORD, int *pnVal)
{
  int v5; // ebx
  int v6; // edi
  int result; // eax
  _DWORD *v8; // edx

  v5 = 0;
  v6 = 0;
  while ( 2 )
  {
    result = 0;
    v8 = &this->m_Role[1].bCanAction + 892 * nVal + v6;
    do
    {
      if ( *v8 == nVal2 )
      {
        *p_DWORD = v5;
        *pnVal = result;
        return result;
      }
      ++result;
      ++v8;
    }
    while ( result < 8 );
    v6 += 32;
    ++v5;
    if ( v6 < 192 )
      continue;
    break;
  }
  *pnVal = -1;
  *p_DWORD = -1;
  return (int)pnVal;
}

// 0x004FA6A0
int CCBRoleState::CheckDeath(int roleIdx)
{
  int result; // eax

  switch ( roleIdx )
  {
    case 1:
      result = 5;
      break;
    case 2:
      result = 1;
      break;
    case 3:
      result = 4;
      break;
    case 4:
      result = 2;
      break;
    case 5:
      result = 3;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x004FA700
int CCBRoleState::GetSlotType(int nVal)
{
  int result; // eax

  switch ( nVal )
  {
    case 1:
      result = 2;
      break;
    case 2:
      result = 4;
      break;
    case 3:
      result = 5;
      break;
    case 4:
      result = 3;
      break;
    case 5:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x004FA760
int CCBRoleState::SwapEffectParams(int nVal)
{
  int v2; // eax
  int v3; // edx
  int v4; // edi
  _DWORD *v5; // esi
  int v6; // eax
  int v7; // esi
  int v8; // edx
  int v9; // esi
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int result; // eax

  v2 = g_EffMgr;
  v3 = 0;
  v4 = 0;
  if ( nVal == g_EffMgr )
  {
LABEL_5:
    v3 = v4;
  }
  else
  {
    v5 = &g_EffMgr;
    while ( v2 != 6 )
    {
      v2 = v5[1];
      ++v5;
      ++v4;
      if ( nVal == v2 )
        goto LABEL_5;
    }
  }
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[3][5] = *((_DWORD *)&g_EffMgr + v3);
  v6 = v3 + 1;
  v7 = *((_DWORD *)&g_EffMgr + v3 + 1);
  v8 = v3 + 2;
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[5][5] = v7;
  v9 = *((_DWORD *)&g_EffMgr + v8++);
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[7][5] = v9;
  v6 += 2;
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[8][3] = *((_DWORD *)&g_EffMgr + v8);
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[6][3] = dword_5D8DC4[v8];
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[7][1] = 6;
  v10 = dword_5D8DB8[v6++];
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[0][2] + 1) = v10;
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[0][4] + 1) = dword_5D8DB8[v6];
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[2][0] + 1) = dword_5D8DBC[v6];
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][4] + 1) = *((_DWORD *)&g_EffMgr + v6);
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][0] + 1) = dword_5D8DC4[v6];
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][2] + 1) = 6;
  v11 = *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[3][5];
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[3][5] = *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[7][5];
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[7][5] = v11;
  v12 = *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[4][3];
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[4][3] = *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[8][3];
  *(_DWORD *)&this->m_RoleXor[6].bMagicMastered[8][3] = v12;
  v13 = *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[0][2] + 1);
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[0][2] + 1) = *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[0][4]
                                                                                + 1);
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[0][4] + 1) = v13;
  v14 = *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][0] + 1);
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][0] + 1) = *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][2]
                                                                                + 1);
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][2] + 1) = v14;
  result = *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][4] + 1);
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[1][4] + 1) = *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[2][0]
                                                                                + 1);
  *(_DWORD *)((char *)&this->m_RoleXor[6].byMagicUseTime[2][0] + 1) = result;
  return result;
}

// 0x004FA8B0
int CCBRoleState::Revive(int roleIdx)
{
  this->GetRoleMP(1);
  return 1;
}

// 0x004FA930
char CCBRoleState::UpdateRoleMP(char arg0, int nVal)
{
  int v3; // ebx
  char result; // al
  _BYTE *v6; // ecx
  _BYTE *v7; // eax
  unsigned int v8; // edi
  int SlotByHP; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int ActionTypeBySlot; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // edi
  int v26; // eax
  int v27; // edi
  int v28; // eax
  _BYTE *v29; // edi
  unsigned __int8 v30; // al
  int *v31; // eax
  bool v32; // cc
  _BYTE *v33; // edi
  int *v34; // eax
  int v35; // ecx
  int v36; // eax
  int v37; // eax
  _BYTE *v38; // ecx
  unsigned __int8 v39; // al
  int v40; // ecx
  bool v41; // zf
  int *v42; // eax
  int v43; // ecx
  int v44; // eax
  int v45; // eax
  int v46; // eax
  _BYTE *v47; // eax
  int v48; // eax
  int v49; // ecx
  int *v50; // eax
  int v51; // ecx
  int v52; // eax
  int v53; // eax
  int v54; // edx
  int v55; // edx
  unsigned int v56; // [esp+0x0] [ebp-0x5C]
  int p_DWORD; // [esp+0xC] [ebp-0x50] BYREF
  int v58; // [esp+0x10] [ebp-0x4C]
  int v59; // [esp+0x14] [ebp-0x48]
  int nVal2; // [esp+0x18] [ebp-0x44]
  int v61; // [esp+0x1C] [ebp-0x40]
  int v62; // [esp+0x20] [ebp-0x3C]
  int SlotState; // [esp+0x24] [ebp-0x38]
  int v64; // [esp+0x28] [ebp-0x34]
  int v65; // [esp+0x2C] [ebp-0x30]
  int v66; // [esp+0x30] [ebp-0x2C]
  int v67; // [esp+0x34] [ebp-0x28]
  int *RoleNum; // [esp+0x38] [ebp-0x24]
  int v69; // [esp+0x3C] [ebp-0x20]
  char *v70; // [esp+0x40] [ebp-0x1C]
  int v71; // [esp+0x44] [ebp-0x18]
  int v72; // [esp+0x48] [ebp-0x14]
  int v73; // [esp+0x4C] [ebp-0x10] BYREF
  _BYTE *v74; // [esp+0x50] [ebp-0xC]
  int nLevel; // [esp+0x54] [ebp-0x8]
  int pnVal; // [esp+0x58] [ebp-0x4] BYREF
  int arg0a; // [esp+0x64] [ebp+0x8]
  int arg0b; // [esp+0x64] [ebp+0x8]
  int arg0c; // [esp+0x64] [ebp+0x8]
  int *arg0d; // [esp+0x64] [ebp+0x8]
  char v81; // [esp+0x67] [ebp+0xB]

  v3 = 0;
  v71 = 0;
  v72 = 0;
  v70 = 0;
  pnVal = -1;
  if ( arg0 )
  {
    this->GetRoleMP(2);
    v69 = v71;
    this->Update(1);
    return this->GetRoleMP(1);
  }
  else
  {
    v69 = 0;
    v74 = &this->m_Role[0].bMagicMastered[5][5];
    v6 = &this->m_Role[0].bMagicMastered[5][5];
    v66 = 0;
    v70 = &Buffer.m_partyActor.m_szTexture[12];
    v62 = -578 - (_DWORD)this;
    do
    {
      if ( *(v6 - 1) && *v6 )
      {
        v7 = v74;
        v8 = *(_DWORD *)(v74 + 130) + *(_DWORD *)(v74 + 126);
        *(_DWORD *)(v74 + 126) = v8;
        arg0a = *(_DWORD *)(v7 + 6);
        SlotByHP = this->FindSlotByHP(v8, v56);
        nLevel = SlotByHP;
        if ( SlotByHP > arg0a )
        {
          p_DWORD = v3;
          v58 = SlotByHP;
          ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(nVal, 0 /* TODO: (int)CCBRoleState::FormatSkillResultText */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
          *(_DWORD *)(v74 + 6) = SlotByHP;
          SlotState = this->GetSlotState(v3, arg0a);
          v10 = this->GetSlotState(v3, SlotByHP);
          *((_DWORD *)v70 - 1) += v10 - SlotState;
          v11 = this->CalcSpeedByLevel(v3, arg0a);
          v12 = this->CalcSpeedByLevel(v3, nLevel);
          *(_DWORD *)v70 += v12 - v11;
          ActionTypeBySlot = this->GetActionTypeBySlot(v3, arg0a);
          v14 = this->GetActionTypeBySlot(v3, nLevel);
          *((_DWORD *)v70 + 1) += v14 - ActionTypeBySlot;
          v15 = this->CalcDefenseByLevel(v3, arg0a);
          v16 = this->CalcDefenseByLevel(v3, nLevel);
          *((_DWORD *)v70 + 2) += v16 - v15;
          v17 = this->CalcDamage(v3, arg0a);
          v18 = this->CalcDamage(v3, nLevel);
          *((_DWORD *)v70 + 3) += v18 - v17;
          v19 = this->GetSlotState(v3, arg0a);
          v20 = this->GetSlotState(v3, nLevel);
          *(_DWORD *)(v74 + 14) += v20 - v19;
          v21 = this->CalcSpeedByLevel(v3, arg0a);
          v22 = this->CalcSpeedByLevel(v3, nLevel);
          *(_DWORD *)(v74 + 22) += v22 - v21;
          v23 = this->GetActionTypeBySlot(v3, arg0a);
          v24 = this->GetActionTypeBySlot(v3, nLevel);
          *(_DWORD *)(v74 + 30) += v24 - v23;
          v25 = this->CalcDefenseByLevel(v3, arg0a);
          v26 = this->CalcDefenseByLevel(v3, nLevel);
          *(_DWORD *)(v74 + 34) += v26 - v25;
          v27 = this->CalcDamage(v3, arg0a);
          v28 = this->CalcDamage(v3, nLevel) - v27;
          v29 = v74;
          arg0b = 0;
          *(_DWORD *)(v74 + 38) += v28;
          *(_DWORD *)(v29 + 10) = *(_DWORD *)(v29 + 14);
          *(_DWORD *)(v29 + 18) = *(_DWORD *)(v29 + 22);
          *(_DWORD *)(v29 + 26) = *(_DWORD *)(v29 + 30);
          RoleNum = (int *)(v29 + 134);
          do
          {
            if ( *RoleNum )
            {
              if ( !v29[arg0b + 158] )
              {
                v30 = *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*RoleNum) + 713);
                if ( v30 )
                {
                  if ( nLevel >= v30 )
                  {
                    v31 = RoleNum;
                    p_DWORD = v3;
                    v29[arg0b + 158] = 1;
                    v58 = *v31;
                    ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(nVal, 0 /* TODO: (int)CCBRoleState::FormatItemResultText */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
                  }
                }
              }
            }
            v32 = ++arg0b < 6;
            ++RoleNum;
          }
          while ( v32 );
        }
        v33 = &v74[v62];
        do
        {
          v65 = 6;
          v34 = (int *)(v74 + 166);
          arg0c = (int)(v74 + 454);
          SlotState = (int)v34;
          v64 = -48 - (_DWORD)this;
          do
          {
            v35 = 0;
            v67 = (int)v34;
            nLevel = 0;
            do
            {
              v36 = *v34;
              if ( v36 )
              {
                if ( *(_BYTE *)(arg0c + v35 - 96) )
                {
                  RoleNum = (int *)((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v36);
                  if ( *(unsigned __int8 *)(arg0c + nLevel) < 3u
                    && *((_BYTE *)RoleNum + *(unsigned __int8 *)(arg0c + nLevel) + 710) <= *(_BYTE *)(arg0c + nLevel - 48) )
                  {
                    v37 = 2;
                    v38 = RoleNum + 178;
                    while ( this->m_sCombatDialog[nLevel + arg0c + v64] < *v38 )
                    {
                      --v37;
                      --v38;
                      if ( v37 < 0 )
                        goto LABEL_26;
                    }
                    v39 = v37 + 1;
                    *(_BYTE *)(arg0c + nLevel) = v39;
                    p_DWORD = v3;
                    v40 = *(_DWORD *)v67;
                    v59 = v39 + 1;
                    v58 = v40;
                    ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(nVal, 0 /* TODO: (int)CCBRoleState::FormatMagicResultText */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
                  }
                }
              }
LABEL_26:
              v35 = nLevel + 1;
              v34 = (int *)(v67 + 4);
              v32 = ++nLevel < 8;
              v67 += 4;
            }
            while ( v32 );
            v41 = v65 == 1;
            arg0c += 8;
            --v65;
          }
          while ( !v41 );
          v64 = 6;
          nVal2 = (int)(v33 + 1032);
          v67 = (int)(v33 + 1032);
          v42 = (int *)SlotState;
          do
          {
            v43 = 0;
            v65 = (int)v42;
            nLevel = 0;
            do
            {
              v44 = *v42;
              if ( v44 && this->m_sCombatDialog[v43 - 96 + v67] )
              {
                v45 = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v44);
                RoleNum = (int *)(v45 + 754);
                arg0d = (int *)(v45 + 724);
                v61 = -754 - v45;
                do
                {
                  if ( *arg0d )
                  {
                    if ( *((unsigned __int8 *)RoleNum - 3) <= (unsigned __int8)this->m_sCombatDialog[nLevel + v67] + 1
                      && *(unsigned __int8 *)RoleNum <= *(int *)(v74 + 6) )
                    {
                      v46 = arg0d[3];
                      if ( v46 )
                      {
                        if ( ((PAL_GDB *)this)->SearchItemLoop(v3, v46, &v73, &pnVal) )
                        {
                          if ( v33[8 * v73 + 936 + pnVal + (_DWORD)this] )
                          {
                            if ( *((unsigned __int8 *)RoleNum - 6) <= (unsigned __int8)v33[8 * v73
                                                                                         + 1032
                                                                                         + pnVal
                                                                                         + (_DWORD)this]
                                                                    + 1 )
                            {
                              if ( ((PAL_GDB *)this)->SearchItemLoop(v3, *arg0d, &v73, &pnVal) )
                              {
                                v47 = &v33[8 * v73 + 936 + pnVal + (_DWORD)this];
                                if ( !*v47 )
                                {
                                  *v47 = 1;
                                  v33[8 * v73 + 1032 + pnVal + (_DWORD)this] = 0;
                                  v48 = v66;
                                  v33[8 * v73 + 984 + pnVal + (_DWORD)this] = 0;
                                  p_DWORD = v3;
                                  v58 = *((_DWORD *)&this->m_Role[1].bCanAction + 8 * v73 + pnVal + v48);
                                  ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(nVal, 0 /* TODO: (int)CCBRoleState::FormatItemResultText */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
                                  v3 = v69;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                  ++arg0d;
                  v49 = (int)RoleNum + v61 + 1;
                  RoleNum = (int *)((char *)RoleNum + 1);
                }
                while ( v49 < 3 );
              }
              v43 = nLevel + 1;
              v42 = (int *)(v65 + 4);
              v32 = ++nLevel < 8;
              v65 += 4;
            }
            while ( v32 );
            v41 = v64 == 1;
            v67 += 8;
            --v64;
          }
          while ( !v41 );
          v50 = (int *)SlotState;
          v81 = 0;
          v67 = nVal2;
          v64 = 6;
          do
          {
            v51 = 0;
            SlotState = (int)v50;
            nLevel = 0;
            do
            {
              v52 = *v50;
              if ( v52 )
              {
                if ( this->m_sCombatDialog[v51 - 96 + v67] )
                {
                  v53 = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v52);
                  nVal2 = *(_DWORD *)(v53 + 716);
                  if ( nVal2 )
                  {
                    if ( *(unsigned __int8 *)(v53 + 714) <= (unsigned __int8)this->m_sCombatDialog[nLevel + v67] + 1
                      && *(unsigned __int8 *)(v53 + 713) <= *(int *)(v74 + 6) )
                    {
                      ((PAL_GDB *)this)->SearchItemLoop(v3, nVal2, &v73, &pnVal);
                      v54 = (int)&v33[8 * v73 + 936 + pnVal];
                      if ( !this->m_sCombatDialog[v54] )
                      {
                        this->m_sCombatDialog[v54] = 1;
                        v81 = 1;
                        v33[8 * v73 + 1032 + pnVal + (_DWORD)this] = 0;
                        v55 = v66;
                        v33[8 * v73 + 984 + pnVal + (_DWORD)this] = 0;
                        p_DWORD = v3;
                        v58 = *((_DWORD *)&this->m_Role[1].bCanAction + 8 * v73 + pnVal + v55);
                        ((CCBStage *)*(CCBStage **)((char *)&this->m_Role[0].dwMagicID[8][1] + 1))->GetRoleName(nVal, 0 /* TODO: (int)CCBRoleState::FormatItemResultText */, 0, 0, 0, &p_DWORD, -1082130432, 1084227584);
                      }
                    }
                  }
                }
              }
              v51 = nLevel + 1;
              v50 = (int *)(SlotState + 4);
              v32 = ++nLevel < 8;
              SlotState += 4;
            }
            while ( v32 );
            v41 = v64 == 1;
            v67 += 8;
            --v64;
          }
          while ( !v41 );
        }
        while ( v81 );
      }
      result = (_BYTE)v70 + 0x80;
      ++v3;
      v6 = v74 + 892;
      v32 = (int)(v70 + 1408) < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[137];
      v69 = v3;
      v70 += 1408;
      v74 += 892;
      v66 += 223;
    }
    while ( v32 );
  }
  return result;
}

// 0x004FB370
int CCBRoleState::CheckMPRequirement(int nVal)
{
  this->GetRoleMP(2);
  return 0;
}

// 0x004FB6B0
int CCBRoleState::RandomizeSpecialSkill(int nSkillId)
{
  int result; // eax

  if ( nSkillId != 7711 )
    return nSkillId;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
  switch ( (((int)unk_5DFDEC >> 16) & 0x7FFF) % 5 )
  {
    case 0:
      result = 207;
      break;
    case 1:
      result = 215;
      break;
    case 2:
      result = 232;
      break;
    case 3:
      result = 224;
      break;
    case 4:
      result = 240;
      break;
    default:
      return nSkillId;
  }
  return result;
}

// 0x00502000
int CCBRoleState::Func(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  double v7; // st7
  char v8; // al
  float fVal; // [esp+0x8] [ebp-0x4]

  v3 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v4 = 80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1);
  v5 = (char *)&this->m_Role[0].nSpeed + 8 * v3 + v4 + 1;
  if ( *((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) )
  {
    v7 = (*(float *)(*(_DWORD *)this->m_sCombatDialog + 80)
        - *(float *)((char *)&this->m_Role[0].nGPInc + 8 * v3 + v4 + 1))
       / *(float *)(&this->m_Role[0].bMagicSword + 8 * v3 + v4 + 1)
       * 255.0;
    fVal = v7;
    if ( v7 > 255.0 )
      fVal = 255.0;
    ((CCBStage *)this->_embed_UIFrameWnd_168.m_bfocus)->CalculateTurnOrder(fVal, *(_DWORD *)((char *)&this->m_Role[0].fPunchPowerInc + 8 * v3 + v4 + 1));
    if ( v5[43] == 1
      || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - *((float *)v5 + 6) > *((float *)v5 + 8)
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v8) )
    {
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_bfocus)->CalculateTurnOrder(255.0, *((_DWORD *)v5 + 11));
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    *((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) = 1;
    return 0;
  }
}

// 0x005020D0
int CCBRoleState::CalcTurnDelay(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // edi
  double v7; // st7
  char v8; // al
  float fVal; // [esp+0x8] [ebp-0x4]

  v3 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v4 = 80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1);
  v5 = (char *)&this->m_Role[0].nSpeed + 8 * v3 + v4 + 1;
  if ( *((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) )
  {
    v7 = (1.0
        - (*(float *)(*(_DWORD *)this->m_sCombatDialog + 80)
         - *(float *)((char *)&this->m_Role[0].nGPInc + 8 * v3 + v4 + 1))
        / *(float *)(&this->m_Role[0].bMagicSword + 8 * v3 + v4 + 1))
       * 255.0;
    fVal = v7;
    if ( v7 <= 255.0 )
    {
      if ( fVal < 0.0 )
        fVal = 0.0;
    }
    else
    {
      fVal = 255.0;
    }
    ((CCBStage *)this->_embed_UIFrameWnd_168.m_bfocus)->CalculateTurnOrder(fVal, *(_DWORD *)((char *)&this->m_Role[0].fPunchPowerInc + 8 * v3 + v4 + 1));
    if ( v5[43] == 1
      || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - *((float *)v5 + 6) > *((float *)v5 + 8)
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v8) )
    {
      ((CCBStage *)this->_embed_UIFrameWnd_168.m_bfocus)->CalculateTurnOrder(0.0, *((_DWORD *)v5 + 11));
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    *((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) = 1;
    return 0;
  }
}

// 0x005021C0
int CCBRoleState::FadeMusicIn(int nVal)
{
  int v3; // ecx
  int v4; // edx
  float *v5; // esi
  CScreenMode *Instance; // eax
  int AudioManager; // eax
  double v9; // st7
  CScreenMode *v10; // eax
  gbAudioManager *v11; // eax
  CScreenMode *v12; // eax
  gbAudioManager *v13; // eax
  float v14; // [esp-0x8] [ebp-0x14]
  float v15; // [esp+0x8] [ebp-0x4]

  v3 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v4 = 80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1);
  v5 = (float *)((char *)&this->m_Role[0].nSpeed + 8 * v3 + v4 + 1);
  if ( !*((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) )
  {
    *((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) = 1;
    if ( (g_dwGameFlags & 4) == 0 )
    {
      *(int *)((char *)&this->m_Role[0].nProtectRole + 8 * v3 + v4 + 1) = 4;
      return 0;
    }
    Instance = CScreenMode::GetInstance();
    AudioManager = ((CScreenMode *)Instance)->GetAudioManager();
    if ( AudioManager )
      v5[16] = *(float *)(AudioManager + 212);
    if ( v5[16] >= (double)*(float *)((char *)&this->m_Role[0].nLevel + 1) )
    {
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
    *((_BYTE *)v5 + 41) = 1;
  }
  v9 = (1.0 - (*(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - v5[6]) / v5[8])
     * (*(float *)((char *)&this->m_Role[0].nLevel + 1) - v5[16])
     + v5[16];
  v15 = v9;
  if ( v9 > *(float *)((char *)&this->m_Role[0].nLevel + 1) )
    v15 = *(float *)((char *)&this->m_Role[0].nLevel + 1);
  if ( v15 < 0.0 )
    v15 = 0.0;
  v10 = CScreenMode::GetInstance();
  v11 = (gbAudioManager *)((CScreenMode *)v10)->GetAudioManager();
  ((gbAudioManager *)v11)->SetMusicMasterVolume(v15);
  if ( *((_BYTE *)v5 + 43) == 1 || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - v5[6] > v5[8] )
  {
    v14 = *(float *)((char *)&this->m_Role[0].nLevel + 1);
    v12 = CScreenMode::GetInstance();
    v13 = (gbAudioManager *)((CScreenMode *)v12)->GetAudioManager();
    ((gbAudioManager *)v13)->SetMusicMasterVolume(v14);
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00502300
int CCBRoleState::FadeMusicOut(int nVal)
{
  int v3; // ecx
  int v4; // edx
  float *v5; // edi
  CScreenMode *Instance; // eax
  int AudioManager; // eax
  double v9; // st7
  CScreenMode *v10; // eax
  gbAudioManager *v11; // eax
  CScreenMode *v12; // eax
  gbAudioManager *v13; // esi
  float v14; // [esp+0x8] [ebp-0x4]

  v3 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v4 = 80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1);
  v5 = (float *)((char *)&this->m_Role[0].nSpeed + 8 * v3 + v4 + 1);
  if ( !*((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) )
  {
    if ( (g_dwGameFlags & 4) == 0 )
    {
      *((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) = 1;
      *(int *)((char *)&this->m_Role[0].nProtectRole + 8 * v3 + v4 + 1) = 4;
      return 0;
    }
    Instance = CScreenMode::GetInstance();
    AudioManager = ((CScreenMode *)Instance)->GetAudioManager();
    if ( AudioManager )
      *(int *)((char *)&this->m_Role[0].nLevel + 1) = *(int *)(AudioManager + 212);
    *((_BYTE *)v5 + 41) = 1;
  }
  v9 = (1.0 - (*(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - v5[6]) / v5[8])
     * *(float *)((char *)&this->m_Role[0].nLevel + 1);
  v14 = v9;
  if ( v9 > *(float *)((char *)&this->m_Role[0].nLevel + 1) )
    v14 = *(float *)((char *)&this->m_Role[0].nLevel + 1);
  if ( v14 < 0.0 )
    v14 = 0.0;
  v10 = CScreenMode::GetInstance();
  v11 = (gbAudioManager *)((CScreenMode *)v10)->GetAudioManager();
  ((gbAudioManager *)v11)->SetMusicMasterVolume(v14);
  if ( *((_BYTE *)v5 + 43) == 1 || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - v5[6] > v5[8] )
  {
    v12 = CScreenMode::GetInstance();
    v13 = (gbAudioManager *)((CScreenMode *)v12)->GetAudioManager();
    ((gbAudioManager *)v13)->StopSoundStream(1);
    ((gbAudioManager *)v13)->StopSoundStream(0);
    ((gbAudioManager *)v13)->StopSoundStream(2);
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00502430
int CCBRoleState::GetCombatDialogEntry(int nVal)
{
  int v3; // ecx
  char *v4; // eax
  int v5; // edi
  char v7; // al

  v3 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v4 = &this->m_sCombatDialog[80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1)];
  v5 = (int)&v4[8 * v3 + 184];
  if ( v4[8 * v3 + 225] )
  {
    if ( ((CCBUI *)*(CCBUI **)(*(_DWORD *)this->m_sCombatDialog + 4))->CreateProtectWindow() )
      *(_DWORD *)(v5 + 16) = 4;
    if ( *(_BYTE *)(v5 + 43) == 1
      || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - *(float *)(v5 + 24) > *(float *)(v5 + 32)
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v7) )
    {
      *(_DWORD *)(v5 + 16) = 4;
    }
    return 0;
  }
  else
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)this->m_sCombatDialog + 4))->InitRoleDisplay(1);
    *(_BYTE *)(v5 + 41) = 1;
    return 0;
  }
}

// 0x005025C0
int CCBRoleState::FormatSkillResultText(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  char *v6; // eax
  void ( ***v7)(_DWORD, int); // ecx
  CScreenMode *Instance; // eax
  char v10; // al
  void (***v11)(_DWORD, _DWORD); // ecx
  char *v12; // [esp-0x10] [ebp-0x98]
  char *v13; // [esp-0xC] [ebp-0x94]
  char *v14; // [esp-0xC] [ebp-0x94]
  int v15; // [esp-0x8] [ebp-0x90]
  int v16; // [esp-0x8] [ebp-0x90]
  char *v17; // [esp-0x4] [ebp-0x8C]
  char *v18; // [esp-0x4] [ebp-0x8C]
  char Buffer[128]; // [esp+0x8] [ebp-0x80] BYREF

  v3 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v4 = 80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1);
  v5 = (char *)&this->m_Role[0].nSpeed + 8 * v3 + v4 + 1;
  if ( *((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) )
  {
    if ( *((_BYTE *)&this->m_Role[0].fPunchPowerInc + 8 * v3 + v4) == 1
      || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80)
       - *(float *)((char *)&this->m_Role[0].nGPInc + 8 * v3 + v4 + 1) > *(float *)(&this->m_Role[0].bMagicSword
                                                                                  + 8 * v3
                                                                                  + v4
                                                                                  + 1)
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v10) )
    {
      v11 = *(void ( ****)(_DWORD, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1084);
      (**v11)(v11, 0);
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    switch ( *(_DWORD *)((char *)&this->m_Role[0].fPunchPowerInc + 8 * v3 + v4 + 1) )
    {
      case 0:
        v17 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v15 = *((_DWORD *)v5 + 12);
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v6 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Jingtian");
        goto LABEL_9;
      case 1:
        v17 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v15 = *((_DWORD *)v5 + 12);
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v6 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Xuejian");
        goto LABEL_9;
      case 2:
        v18 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v16 = *((_DWORD *)v5 + 12);
        v14 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v12 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Longkui");
        sprintf(Buffer, "%s%s %d %s", v12, v14, v16, v18);
        break;
      case 3:
        v17 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v15 = *((_DWORD *)v5 + 12);
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v6 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Zixuan");
        goto LABEL_9;
      case 4:
        v17 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v15 = *((_DWORD *)v5 + 12);
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v6 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Changqing");
LABEL_9:
        sprintf(Buffer, "%s%s %d %s", v6, v13, v15, v17);
        break;
      default:
        break;
    }
    ((UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1084))->SetEnable((int)Buffer, 1);
    v7 = *(void ( ****)(_DWORD, int))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1084);
    (**v7)(v7, 1);
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(&g_EffMgr, 1);
    v5[41] = 1;
    return 0;
  }
}

// 0x005027E0
int CCBRoleState::FormatAttackResultText(int nVal)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  int v6; // eax
  int SkillNum; // eax
  char *v8; // eax
  void ( ***v9)(_DWORD, int); // ecx
  char v11; // al
  void (***v12)(_DWORD, _DWORD); // ecx
  char *v13; // [esp-0xC] [ebp-0x114]
  char *v14; // [esp-0xC] [ebp-0x114]
  int v15; // [esp-0x8] [ebp-0x110]
  int v16; // [esp-0x8] [ebp-0x110]
  char *v17; // [esp-0x4] [ebp-0x10C]
  const char *v18; // [esp-0x4] [ebp-0x10C]
  int v19; // [esp-0x4] [ebp-0x10C]
  char Buffer[256]; // [esp+0x8] [ebp-0x100] BYREF

  v3 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v4 = 80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1);
  v5 = (char *)&this->m_Role[0].nSpeed + 8 * v3 + v4 + 1;
  if ( *((_BYTE *)&this->m_Role[0].fMPCostDec + 8 * v3 + v4 + 2) )
  {
    if ( *((_BYTE *)&this->m_Role[0].fPunchPowerInc + 8 * v3 + v4) == 1
      || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80)
       - *(float *)((char *)&this->m_Role[0].nGPInc + 8 * v3 + v4 + 1) > *(float *)(&this->m_Role[0].bMagicSword
                                                                                  + 8 * v3
                                                                                  + v4
                                                                                  + 1)
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v11) )
    {
      v12 = *(void ( ****)(_DWORD, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1112);
      (**v12)(v12, 0);
      *((_DWORD *)v5 + 4) = 4;
    }
    return 0;
  }
  else
  {
    v6 = *(_DWORD *)((char *)&this->m_Role[0].fPunchPowerInc + 8 * v3 + v4 + 1);
    if ( v6 )
    {
      if ( v6 == 1 )
      {
        v17 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aMoney);
        v15 = *((_DWORD *)v5 + 13);
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aGetitem_0);
        sprintf(Buffer, "%s %d %s", v13, v15, v17);
      }
    }
    else
    {
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(_DWORD *)((char *)&this->m_Role[0].fSkillCentInc + 8 * v3 + v4 + 1));
      if ( *((_DWORD *)v5 + 13) == 1 )
      {
        v18 = (const char *)(SkillNum + 4);
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aGetitem_0);
        sprintf(Buffer, "%s %s", v8, v18);
      }
      else
      {
        v19 = *((_DWORD *)v5 + 13);
        v16 = SkillNum + 4;
        v14 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aGetitem_0);
        sprintf(Buffer, "%s %s %d", v14, v16, v19);
      }
    }
    ((UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1112))->SetEnable((int)Buffer, 1);
    v9 = *(void ( ****)(_DWORD, int))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1112);
    (**v9)(v9, 1);
    v5[41] = 1;
    return 0;
  }
}

// 0x00502950
int CCBRoleState::FormatItemResultText(int nVal)
{
  UICaption *v3; // edi
  int v4; // ecx
  int v5; // edx
  char *v6; // ebx
  int RoleNum; // eax
  char *v8; // eax
  CScreenMode *Instance; // eax
  char v11; // al
  char *v12; // [esp-0xC] [ebp-A4h]
  char *v13; // [esp-0x8] [ebp-A0h]
  char *v14; // [esp-0x8] [ebp-A0h]
  int v15; // [esp-0x4] [ebp-0x9C]
  int v16; // [esp-0x4] [ebp-0x9C]
  int p_DWORD; // [esp+0xC] [ebp-0x8C] BYREF
  int p_DWORD2; // [esp+0x10] [ebp-0x88] BYREF
  int pnVal; // [esp+0x14] [ebp-0x84] BYREF
  char Buffer[128]; // [esp+0x18] [ebp-0x80] BYREF

  p_DWORD2 = -1;
  pnVal = -1;
  v3 = 0;
  v4 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v5 = 80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1);
  v6 = (char *)&this->m_Role[0].nSpeed + 8 * v4 + v5 + 1;
  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*(_DWORD *)((char *)&this->m_Role[0].fSkillCentInc + 8 * v4 + v5 + 1));
  if ( v6[41] )
  {
    if ( v6[43] == 1
      || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - *((float *)v6 + 6) > *((float *)v6 + 8)
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v11) )
    {
// [VFTABLE] if ( ((PAL_GDB *)this->_embed_UIFrameWnd_168.__vftable)->IsItemConsumable(*((_DWORD *)v6 + 12)) )
      {
// [VFTABLE] ((PAL_GDB *)this->_embed_UIFrameWnd_168.__vftable)->SearchAllItems(*((_DWORD *)v6 + 12), &p_DWORD, &pnVal, &p_DWORD2);
        switch ( p_DWORD )
        {
          case 0:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1096))(0);
            break;
          case 1:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1100))(0);
            break;
          case 2:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1092))(0);
            break;
          case 3:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1088))(0);
            break;
          case 4:
            (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1104))(0);
            break;
          case 5:
            v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1108);
            goto LABEL_32;
          default:
LABEL_32:
// [VFTABLE] v3->__vftable->ShowWindow(0);
            break;
        }
      }
      else
      {
        (***(void ( ****)(_DWORD))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1084))(0);
      }
      *((_DWORD *)v6 + 4) = 4;
    }
    return 0;
  }
  else
  {
    switch ( *((_DWORD *)v6 + 11) )
    {
      case 0:
        v15 = RoleNum + 28;
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aMastered);
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Jingtian");
        goto LABEL_9;
      case 1:
        v15 = RoleNum + 28;
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aMastered);
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Xuejian");
        goto LABEL_9;
      case 2:
        v16 = RoleNum + 28;
        v14 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aMastered);
        v12 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Longkui");
        sprintf(Buffer, "%s%s %s", v12, v14, v16);
        break;
      case 3:
        v15 = RoleNum + 28;
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aMastered);
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Zixuan");
        goto LABEL_9;
      case 4:
        v15 = RoleNum + 28;
        v13 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aMastered);
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Changqing");
LABEL_9:
        sprintf(Buffer, "%s%s %s", v8, v13, v15);
        break;
      default:
        break;
    }
// [VFTABLE] if ( ((PAL_GDB *)this->_embed_UIFrameWnd_168.__vftable)->IsItemConsumable(*((_DWORD *)v6 + 12)) )
    {
// [VFTABLE] ((PAL_GDB *)this->_embed_UIFrameWnd_168.__vftable)->SearchAllItems(*((_DWORD *)v6 + 12), &p_DWORD, &pnVal, &p_DWORD2);
      switch ( p_DWORD )
      {
        case 0:
          v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1096);
          break;
        case 1:
          v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1100);
          break;
        case 2:
          v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1092);
          break;
        case 3:
          v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1088);
          break;
        case 4:
          v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1104);
          break;
        case 5:
          v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1108);
          break;
        default:
          break;
      }
      ((UICaption *)v3)->SetEnable((int)Buffer, 1);
// [VFTABLE] v3->__vftable->ShowWindow(1);
    }
    else
    {
      ((UICaption *)*(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1084))->SetEnable((int)Buffer, 1);
      (***(void ( ****)(int))(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1084))(1);
    }
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(&g_EffMgr, 1);
    v6[41] = 1;
    return 0;
  }
}

// 0x00502CC0
int CCBRoleState::FormatMagicResultText(int nVal)
{
  UICaption *v3; // ebp
  int v4; // ecx
  int v5; // edx
  char *v6; // edi
  int RoleNum; // ebx
  char *v8; // eax
  CScreenMode *Instance; // eax
  char v10; // al
  char *v12; // [esp-0x14] [ebp-B0h]
  int v13; // [esp-0x10] [ebp-ACh]
  char *v14; // [esp-0xC] [ebp-A8h]
  char *v15; // [esp-0xC] [ebp-A8h]
  int v16; // [esp-0x8] [ebp-A4h]
  int v17; // [esp-0x8] [ebp-A4h]
  char *v18; // [esp-0x4] [ebp-A0h]
  char *v19; // [esp-0x4] [ebp-A0h]
  int p_DWORD; // [esp+0x10] [ebp-0x8C] BYREF
  int p_DWORD2; // [esp+0x14] [ebp-0x88] BYREF
  int pnVal; // [esp+0x18] [ebp-0x84] BYREF
  char Buffer[128]; // [esp+0x1C] [ebp-0x80] BYREF

  p_DWORD2 = -1;
  pnVal = -1;
  v3 = 0;
  v4 = 329 * *(int *)((char *)&this->m_Role[0].nGP + 1);
  v5 = 80 * *(int *)((char *)&this->m_Role[0].pCCBSystem + 1);
  v6 = (char *)&this->m_Role[0].nSpeed + 8 * v4 + v5 + 1;
  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*(_DWORD *)((char *)&this->m_Role[0].fSkillCentInc + 8 * v4 + v5 + 1));
  if ( !v6[41] )
  {
    switch ( *((_DWORD *)v6 + 11) )
    {
      case 0:
        v18 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v16 = *((_DWORD *)v6 + 13);
        v14 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v13 = RoleNum + 28;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Jingtian");
        goto LABEL_9;
      case 1:
        v18 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v16 = *((_DWORD *)v6 + 13);
        v14 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v13 = RoleNum + 28;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Xuejian");
        goto LABEL_9;
      case 2:
        v19 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v17 = *((_DWORD *)v6 + 13);
        v15 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v12 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Longkui");
        sprintf(Buffer, "%s %s %s %d %s", v12, RoleNum + 28, v15, v17, v19);
        break;
      case 3:
        v18 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v16 = *((_DWORD *)v6 + 13);
        v14 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v13 = RoleNum + 28;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Zixuan");
        goto LABEL_9;
      case 4:
        v18 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        v16 = *((_DWORD *)v6 + 13);
        v14 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevelup);
        v13 = RoleNum + 28;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Changqing");
LABEL_9:
        sprintf(Buffer, "%s %s %s %d %s", v8, v13, v14, v16, v18);
        break;
      default:
        break;
    }
// [VFTABLE] ((PAL_GDB *)this->_embed_UIFrameWnd_168.__vftable)->SearchAllItems(*((_DWORD *)v6 + 12), &p_DWORD, &pnVal, &p_DWORD2);
    switch ( p_DWORD )
    {
      case 0:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1096);
        break;
      case 1:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1100);
        break;
      case 2:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1092);
        break;
      case 3:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1088);
        break;
      case 4:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1104);
        break;
      case 5:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1108);
        break;
      default:
        break;
    }
    ((UICaption *)v3)->SetEnable((int)Buffer, 1);
// [VFTABLE] ((void ( *)(UICaption *, int))v3->__vftable->ShowWindow)(v3, 1);
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(&g_EffMgr, 1);
    v6[41] = 1;
  }
  if ( v6[43] == 1
    || *(float *)(*(_DWORD *)this->m_sCombatDialog + 80) - *((float *)v6 + 6) > *((float *)v6 + 8)
    || (((GRPinput *)&g_Input)->SetJoystickAbs(), v10) )
  {
// [VFTABLE] ((PAL_GDB *)this->_embed_UIFrameWnd_168.__vftable)->SearchAllItems(*((_DWORD *)v6 + 12), &p_DWORD, &pnVal, &p_DWORD2);
    switch ( p_DWORD )
    {
      case 0:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1096);
        break;
      case 1:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1100);
        break;
      case 2:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1092);
        break;
      case 3:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1088);
        break;
      case 4:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1104);
        break;
      case 5:
        v3 = *(UICaption **)(*(_DWORD *)(*(_DWORD *)this->m_sCombatDialog + 4) + 1108);
        break;
      default:
        break;
    }
// [VFTABLE] ((void ( *)(UICaption *, _DWORD))v3->__vftable->ShowWindow)(v3, 0);
    *((_DWORD *)v6 + 4) = 4;
  }
  return 0;
}

// 0x00503AE0
int CCBRoleState::GetRoleMPValue(int nVal, int nVal2, int nVal3)
{
  int v5; // edi
  CCBUI **p_m_pUI; // ecx
  int v7; // esi

  v5 = 0;
  p_m_pUI = &this->m_pUI;
  v7 = 2;
  *p_m_pUI = 0;
  p_m_pUI[1] = 0;
  *((_WORD *)p_m_pUI + 4) = 0;
  *((_BYTE *)p_m_pUI + 10) = 0;
  do
  {
    if ( ((unsigned int)(__int64)pow(2.0, (double)(v7 - 1)) & nVal2) != 0 )
      ++v5;
    ++v7;
  }
  while ( v7 < 5 );
  if ( v5 <= 1 )
  {
    if ( (nVal2 & 1) != 0 )
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleMP(2);
    else
// [VFTABLE] ((CCBRoleState *)this->_embed_UIFrameWnd_168.__vftable)->GetRoleMP(1);
    return 0;
  }
  else
  {
    *((_BYTE *)&this->m_pUI + nVal) = 1;
    return nVal;
  }
}

// 0x00524970
// attributes: thunk
void CCBRoleState::Render(
        
        UIListBox *thisa,
        const char *a3,
        tagRECT *a4,
        int a5,
        int a6,
        bool a7)
{
  ((CCBControlWindow *)this)->Render((CCBMagicWindow *)thisa);
}
