#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ComposeUI.h"

// Forward declarations for unnamed functions
int sub_43FEC0(void *a2); // from annotations
int sub_445FA0(void *a2); // from annotations

// Unnamed globals (extern)
extern int dword_DCFF3C;
extern int dword_DD203C;
extern RoleSystem stru_C059A0;

// 0x0047E030
int ComposeUI::RefreshRecipeList(int arg0)
{
  void ( **v3)(UIStatic *, int); // edx
  UIStatic *v4; // edi
  int i; // eax
  int SkillNum; // eax
  int *v7; // ebx
  int v8; // edi
  UIWnd **p_m_pfather; // ebp
  int result; // eax
  char *v11; // [esp+0x1C] [ebp-0x4]

  g_nSceneState = 2;
  v3 = (void ( **)(UIStatic *, int))*((_DWORD *)&this->m_BottomFrame + 38);
  v4 = &this->m_BottomFrame + 1;
  this->m_BottomFrame.m_FVF = arg0;
  (*v3)(&this->m_BottomFrame + 1, 1);
  this->m_BottomFrame.m_disablepicInfo = (_PlugInfo *)170;
  this->m_BottomFrame.m_pbk2 = (gbTexture *)468;
  *(_DWORD *)&this->m_BottomFrame.m_mouseoff = 330;
  this->m_BottomFrame.m_disablepic = (gbTexture *)310;
  for ( i = 0; i < 5; ++i )
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + i) )
      *(_DWORD *)&this->m_BottomFrame.m_mouseoff += 20;
  }
  sub_445FA0(v4);
  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(this->m_BottomFrame.m_FVF);
  sprintf(
    (char *const)&this->m_TopFrame.m_pfather,
    "%s%s%s",
    (const char *)dword_DCFF3C,
    (const char *)(SkillNum + 4),
    (const char *)g_ComposeRecipeTable);
  ((UICaption *)&this->m_MiddleFrame[1].m_pfather)->SetEnable((int)&this->m_TopFrame.m_pfather, 0);
  v7 = &this->m_SelBtn + 478;
  *(&this->m_SelBtn + 478) = 0;
  *((_BYTE *)&this->m_SelBtn + 1916) = 0;
  v11 = &this->m_BottomFrame.m_disablepicInfo->name[120];
  v8 = 0;
  p_m_pfather = &this->m_MiddleFrame[2].m_pfather;
  do
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v8) )
    {
      *((_BYTE *)v7 + v8) = 1;
      sub_445FA0(p_m_pfather);
      result = (int)(v11 + 26);
      v11 += 26;
    }
    else
    {
      *((_BYTE *)v7 + v8) = 0;(*p_m_pfather)->ShowWindow(0);
}
    ++v8;
    p_m_pfather += 86;
  }
  while ( v8 < 5 );
  LOBYTE(this->m_BottomFrame.m_nTextW) = 0;
  *((_BYTE *)&this->m_SelBtn + 1917) = 1;
  *((_BYTE *)&this->m_SelBtn + 1918) = 0;
  return result;
}

// 0x0047E190
void ComposeUI::ProcessFrame(int nVal)
{
  int v2; // eax
  int v4; // edx
  int i; // ecx
  UIWnd **p_m_pfather; // edi
  int v7; // ebp
  int m_FVF; // ecx
  int SkillNum; // ebp
  char *v10; // esi
  char *v11; // eax
  char *v12; // [esp-0xC] [ebp-0x138]
  const CHAR *v13; // [esp-0x8] [ebp-0x134]
  CHAR String1[29]; // [esp+0xC] [ebp-0x120] BYREF
  __int16 v15; // [esp+0x29] [ebp-0x103]
  char v16; // [esp+0x2B] [ebp-0x101]
  char Buffer[253]; // [esp+0x2C] [ebp-0x100] BYREF
  __int16 v18; // [esp+0x129] [ebp-0x3]
  char v19; // [esp+0x12B] [ebp-0x1]

  v2 = -1;
  switch ( this->m_BottomFrame.m_FVF )
  {
    case 0x183A:
      v2 = 0;
      break;
    case 0x183C:
      v2 = 1;
      break;
    case 0x183E:
      v2 = 3;
      break;
    case 0x1840:
      v2 = 7;
      break;
    case 0x1842:
      v2 = 2;
      break;
    case 0x184F:
      v2 = 4;
      break;
    case 0x1850:
      v2 = 6;
      break;
    case 0x1856:
      v2 = 5;
      break;
    default:
      break;
  }
  v4 = 0;
  for ( i = 0; i < 8; ++i )
  {
    if ( g_SaveSlotFlags[8 * nVal + i] )
      ++v4;
  }
  if ( v4 >= 6 )
  {
    memset(Buffer, 0, sizeof(Buffer));
    v18 = 0;
    v19 = 0;
    sprintf(Buffer, "\\n  %s", (const char *)dword_DD203C);
    ((UICaption *)(&this->m_SelBtn + 250))->SetEnable((int)Buffer, 0);
    ((UIRoleSelect *)(&this->m_SelBtn + 136))->SetByte(1);
  }
  else
  {
    g_SaveSlotFlags[8 * nVal + v2] = 1;
    (**((void ( ***)(UIStatic *, _DWORD))&this->m_BottomFrame + 38))(&this->m_BottomFrame + 1, 0);
// [VFTABLE] ((void ( *)(UIWnd **, _DWORD))this->m_MiddleFrame[1].m_pfather->__vftable)(
// [VFTABLE]   &this->m_MiddleFrame[1].m_pfather,
// [VFTABLE]   0);
    p_m_pfather = &this->m_MiddleFrame[2].m_pfather;
    v7 = 5;
    do
    {(*p_m_pfather)->ShowWindow(0);
p_m_pfather += 86;
      --v7;
    }
    while ( v7 );
    m_FVF = this->m_BottomFrame.m_FVF;
    LOBYTE(this->m_BottomFrame.m_nTextW) = 1;
    *((_BYTE *)&this->m_SelBtn + 1917) = 0;
    *((_BYTE *)&this->m_SelBtn + 1918) = 0;
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(m_FVF);
    memset(String1, 0, sizeof(String1));
    v15 = 0;
    v16 = 0;
    switch ( nVal )
    {
      case 0:
        lstrcpyA(String1, "Jingtian");
        break;
      case 1:
        v13 = "Xuejian";
        goto LABEL_23;
      case 2:
        lstrcpyA(String1, "Longkui");
        break;
      case 3:
        lstrcpyA(String1, "Zixuan");
        break;
      case 4:
        v13 = "Changqing";
LABEL_23:
        lstrcpyA(String1, v13);
        break;
      default:
        break;
    }
    v10 = (char *)&this->m_TopFrame.m_pfather;
    v12 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(String1);
    v11 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("AddSkill");
    _snprintf(v10, 0xFFu, v11, v12, SkillNum + 4);
    ((InputSystem *)v10)->ProcessFrame();
  }
}

// 0x004A3730
int ComposeUI::ProcessChildItem(int arg0, int *p_DWORD)
{
  int result; // eax
  char *v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int a2; // [esp+0x0] [ebp-0x40] BYREF
  int v13; // [esp+0x4] [ebp-0x3C]
  int v14; // [esp+0x8] [ebp-0x38]
  int v15; // [esp+0xC] [ebp-0x34]
  int v16; // [esp+0x10] [ebp-0x30]
  int v17; // [esp+0x14] [ebp-0x2C]
  int v18; // [esp+0x18] [ebp-0x28]
  int v19; // [esp+0x1C] [ebp-0x24]
  int v20; // [esp+0x20] [ebp-0x20]
  int v21; // [esp+0x24] [ebp-0x1C]
  int v22; // [esp+0x28] [ebp-0x18]
  int v23; // [esp+0x2C] [ebp-0x14]
  int v24; // [esp+0x30] [ebp-0x10]
  int v25; // [esp+0x34] [ebp-0xC]
  int v26; // [esp+0x38] [ebp-0x8]
  int v27; // [esp+0x3C] [ebp-0x4]

  result = arg0;
  if ( arg0 <= 5 )
  {
    v4 = (char *)this + 3788 * arg0;
    sub_445FA0(v4 + 155140);
    v5 = p_DWORD[1] + 10;
    v20 = *p_DWORD + 25;
    v22 = v20 + 65;
    v21 = v5;
    v23 = v5 + 86;
    sub_445FA0(v4 + 155292);
    v6 = p_DWORD[1] + 36;
    v24 = p_DWORD[2] - 27;
    v25 = v6;
    v26 = v24 + 32;
    v27 = v6 + 128;
    sub_445FA0(v4 + 155444);
    v7 = *p_DWORD - 72;
    v13 = p_DWORD[1] + 21;
    a2 = v7;
    v15 = v13 + 12;
    v14 = v7 + 85;
    sub_43FEC0(&a2);
    v8 = *p_DWORD - 80;
    v13 = v15 + 16;
    a2 = v8;
    v15 += 28;
    v14 = v8 + 85;
    sub_43FEC0(&a2);
    v9 = *p_DWORD - 70;
    v13 = v15 + 16;
    a2 = v9;
    v14 = v9 + 85;
    v15 += 28;
    sub_43FEC0(&a2);
    v10 = p_DWORD[1];
    v16 = a2;
    v17 = v10;
    v18 = a2 + 100;
    v19 = v10 + 32;
    sub_445FA0(v4 + 155992);
    v11 = p_DWORD[1] + 28;
    v16 = a2;
    v17 = v11;
    v19 = v11 + 32;
    v18 = a2 + 100;
    sub_445FA0(v4 + 157088);
    v17 = p_DWORD[1] + 56;
    v16 = a2;
    v18 = a2 + 100;
    v19 = v17 + 32;
    return sub_445FA0(v4 + 156540);
  }
  return result;
}
