#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/CCBAIWindow.h"
#include "pal3/gen/CCBControlWindow.h"
#include "pal3/gen/CCBItemWindow.h"
#include "pal3/gen/CCBLineupWindow.h"
#include "pal3/gen/CCBParabolaWindow.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/CCBSkillWindow.h"
#include "pal3/gen/CCBStageScene.h"
#include "pal3/gen/CCBSystem.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/NPC.h"
#include "pal3/gen/PalScript.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UIStatic.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_43F640(...);
int sub_43F670(...);
int sub_43F690(...);
int sub_43FE90(...);
int sub_4421F0(...);
int sub_442200(...);
int sub_442230(...);
int sub_442C80(...);
int sub_442D00(...);
int sub_4DC650(...);
int sub_4DF2F0(...);
int sub_4E2C50(...);
int sub_4E30E0(...);
int sub_4E3780(...);
int sub_4E3A20(...);
int sub_4E3D90(...);
int sub_4E40B0(...);
int sub_4E4570(...);
int sub_4E4A80(...);
int sub_4E4D50(...);
int sub_4E4D70(...);
int sub_4E4F00(...);
int sub_4E50B0(...);
int sub_4E5110(...);
int sub_4E5170(...);
int sub_4E5B20(...);
int sub_4E5E00(...);
int sub_504240(...);
int sub_51A400(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aCNewFailed_0[];
extern char aCost[];
extern char aDProjectPal3Co_12[];
extern char aLevelcost[];
extern char aName[];
extern char aQuantity[];
extern char aStopped[];
extern char aUiCombatAttack_0[];
extern char aUiCombatAttack_1[];
extern char aUiCombatContro[];
extern char aUiCombatContro_0[];
extern char aUiCombatContro_1[];
extern char aUiCombatContro_2[];
extern char aUiCombatContro_3[];
extern char aUiCombatContro_33[];
extern char aUiCombatContro_34[];
extern char aUiCombatContro_35[];
extern char aUiCombatContro_36[];
extern char aUiCombatContro_37[];
extern char aUiCombatContro_38[];
extern char aUiCombatContro_39[];
extern char aUiCombatContro_40[];
extern char aUiCombatContro_41[];
extern char aUiCombatContro_42[];
extern char aUiCombatContro_43[];
extern char aUiCombatContro_44[];
extern char aUiCombatContro_45[];
extern char aUiCombatContro_46[];
extern char aUiCombatContro_47[];
extern char aUiCombatContro_48[];
extern char aUiCombatContro_49[];
extern char aUiCombatContro_50[];
extern char aUiCombatContro_51[];
extern char aUiCombatContro_52[];
extern char aUiCombatContro_53[];
extern char aUiCombatContro_54[];
extern char aUiCombatDialog[];
extern char aUiCombatResult_10[];
extern char aUiCombatResult_11[];
extern char aUiCombatResult_12[];
extern char aUiCombatResult_13[];
extern char aUiCombatResult_6[];
extern char aUiCombatResult_7[];
extern char aUiCombatResult_8[];
extern char aUiCombatResult_9[];
extern char aUiCombatTrickn[];
extern char aUiCombatTrickn_0[];
extern char aWa001[];
extern char aWa002[];
extern unsigned char byte_17A94E4;
extern unsigned char byte_17A9924;
extern unsigned char byte_17A9925;
extern unsigned char byte_17A9926;
extern unsigned char byte_17A9930;
extern unsigned char byte_17A9931;
extern unsigned char byte_17A9932;
extern unsigned char byte_17A9933;
extern unsigned char byte_17A9934;
extern unsigned char byte_17A9935;
extern unsigned char byte_17A9936;
extern unsigned char byte_17A9937;
extern unsigned char byte_17A9938;
extern unsigned char byte_17A9944;
extern unsigned char byte_17A9945;
extern unsigned char byte_17A9946;
extern unsigned char byte_17A9947;
extern unsigned char byte_17A9948;
extern unsigned char byte_17A9949;
extern unsigned char byte_17A994A;
extern unsigned char byte_17A994B;
extern unsigned char byte_17A994C;
extern unsigned char byte_17A994D;
extern unsigned char byte_17A994E;
extern unsigned char byte_17ACB08;
extern unsigned char byte_5D87F0;
extern unsigned char byte_5D8808;
extern unsigned char byte_5D8848;
extern unsigned char byte_5D8864;
extern unsigned char byte_5D8884;
extern int dword_17A990C;
extern int dword_570110;
extern int dword_570114;
extern int dword_57011C;
extern int dword_570134;
extern int dword_57024C;
extern int dword_570268;
extern float flt_17A95F8;
extern void *off_570500;
extern int unk_5700E8;

// 0x004DC560
int CCBUI::GetState()
{
  int result; // eax

  LOBYTE(result) = BYTE1(this->m_wndcolor.Red);
  if ( !(_BYTE)result )
  {
    BYTE1(this->m_wndcolor.Red) = 1;
    return sub_4DC650((CCBSystem **)this, (CCBSystem *)sub_4DF2F0, 0, 0, 0, 0, 0, 0, (CCBSystem *)0xFFFFFFFF, 0, 0);
  }
  return result;
}

// 0x004DC5C0
int CCBUI::SetParam(int a2, int a3)
{
  int result; // eax
  __int32 v4; // [esp+10h] [ebp+Ch]

  result = a2;
  this->m_wndcolor.Color = a3;
  LOBYTE(this->m_rect.left) = 1;
  this->m_wndcolor.Alpha = a2;
  this->m_id = v4;
  switch ( a2 )
  {
    case 259:
    case 260:
    case 261:
    case 262:
    case 265:
    case 267:
      this->m_wndcolor.Alpha = a2;
      break;
    default:
      return result;
  }
  return result;
}

// 0x004E04C0
int CCBUI::Update()
{
  int result; // eax

  ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->ProcAI(flt_17A95F8);
  if ( *(_BYTE *)(this->m_fontcolor.ColorQuadFmt + 132) != byte_17A9924 )
    ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->SetRenderFlag(byte_17A9924);
  *(_BYTE *)(this->m_fontcolor.ColorQuadFmt + 134) = byte_5D87F0;
  if ( byte_17A9926 )
  {
    CCBSystem::GetRenderFlag();
    byte_17A9926 = 0;
  }
  this->UpdateInput();
  this->UpdateDisplay();
  this->UpdateAnimation();
  LOBYTE(result) = this->UpdateState();
  return result;
}

// 0x004E0690
char CCBUI::UpdateInput()
{
  char result; // al
  int v3; // eax
  char Buffer[128]; // [esp+8h] [ebp-80h] BYREF

  result = byte_17A9930;
  if ( byte_17A9930 )
  {
    ((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(this->m_fontcolor.ColorQuadFmt + 20) + 20))->Update();
    ((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(this->m_fontcolor.ColorQuadFmt + 20) + 20))->ShowRoleIndex();
    result = ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->CreateObj(byte_5D8864, 0, 0x40u);
    byte_17A9930 = 0;
  }
  if ( byte_17A9932 )
    byte_17A9932 = 0;
  if ( byte_17A9931 )
    byte_17A9931 = 0;
  if ( byte_17A9933 )
  {
    v3 = sub_504240(*(float **)(*(_DWORD *)(this->m_fontcolor.ColorQuadFmt + 20) + 12));
    sprintf(Buffer, &byte_5D8848, v3);
    result = ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->CreateObj(Buffer, 0, 0x40u);
    byte_17A9933 = 0;
  }
  return result;
}

// 0x004E0740
char CCBUI::UpdateDisplay()
{
  int ColorQuadFmt; // eax
  int v3; // edi
  int i; // esi
  CCBRoleState *v5; // ecx
  int v6; // edi
  int v7; // esi
  CCBRoleState *v8; // ecx
  HWND DlgItem; // eax

  LOBYTE(ColorQuadFmt) = byte_17A9925;
  if ( byte_17A9925 )
  {
    v3 = 0;
    for ( i = 0; i < 5; ++i )
    {
      ColorQuadFmt = this->m_fontcolor.ColorQuadFmt;
      v5 = (CCBRoleState *)*(CCBRoleState **)(this->m_fontcolor.ColorQuadFmt + 16);
      if ( v5->m_Role[i].bValid )
      {
        ColorQuadFmt = v5->InitUI(v3);
        *(_BYTE *)(ColorQuadFmt + 837) = 0;
      }
      ++v3;
    }
    byte_17A9924 = 0;
    byte_17A9925 = 0;
  }
  else
  {
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      v8 = (CCBRoleState *)*(CCBRoleState **)(this->m_fontcolor.ColorQuadFmt + 16);
      if ( v8->m_Role[v7].bValid )
      {
        ColorQuadFmt = v8->InitUI(v6);
        if ( !*(_BYTE *)(ColorQuadFmt + 837) )
          break;
      }
      ++v7;
      ++v6;
      if ( v7 >= 5 )
      {
        if ( !byte_17A9924 )
        {
          byte_17A9924 = 1;
          sprintf(byte_17A94E4, "%s", byte_5D8884);
          DlgItem = GetDlgItem((HWND)g_Input.KeyInfo[176].Data, 1004);
          SendMessageA(DlgItem, 0xCu, 0, (LPARAM)byte_17A94E4);
          LOBYTE(ColorQuadFmt) = ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->ProcFlee(byte_17A9924);
        }
        return ColorQuadFmt;
      }
    }
  }
  return ColorQuadFmt;
}

// 0x004E0820
char CCBUI::UpdateAnimation()
{
  char result; // al

  result = byte_17A9934;
  if ( byte_17A9934 )
  {
    byte_17A9934 = 0;
    result = sub_4E2C50(this);
  }
  if ( byte_17A9935 )
  {
    byte_17A9935 = 0;
    result = sub_4E30E0(&this->m_fontcolor.ColorQuadFmt);
  }
  if ( byte_17A9936 )
  {
    byte_17A9936 = 0;
    result = sub_4E3780(this);
  }
  if ( byte_17A9938 )
  {
    byte_17A9938 = 0;
    result = sub_4E3D90((CCBRoleState **)this);
  }
  if ( byte_17A9937 )
  {
    byte_17A9937 = 0;
    result = sub_4E3A20((CCBRoleState **)this);
  }
  if ( byte_17A9944 )
  {
    byte_17A9944 = 0;
    result = sub_4E40B0((CCBRoleState **)this);
  }
  if ( byte_17A9945 )
  {
    byte_17A9945 = 0;
    result = sub_4E4570(this);
  }
  if ( byte_17A9946 )
  {
    byte_17A9946 = 0;
    result = sub_4E4A80(this);
  }
  if ( byte_17A9948 )
  {
    byte_17A9948 = 0;
    result = sub_4E4D70(this);
  }
  if ( byte_17A9947 )
  {
    byte_17A9947 = 0;
    result = sub_4E4D50(this);
  }
  if ( byte_17A994A )
  {
    byte_17A994A = 0;
    result = (unsigned __int8)sub_4E50B0();
  }
  if ( byte_17A9949 )
  {
    byte_17A9949 = 0;
    result = sub_4E4F00(this);
  }
  if ( byte_17A994B )
  {
    byte_17A994B = 0;
    result = sub_4E5170();
  }
  if ( byte_17A994C )
  {
    byte_17A994C = 0;
    result = sub_4E5110();
  }
  if ( byte_17A994D )
  {
    byte_17A994D = 0;
    result = sub_4E5B20(&this->m_fontcolor.ColorQuadFmt);
  }
  if ( byte_17A994E )
  {
    byte_17A994E = 0;
    return sub_4E5E00(&this->m_fontcolor.ColorQuadFmt);
  }
  return result;
}

// 0x004E0980
char CCBUI::UpdateState()
{
  char result; // al
  int v2; // esi
  HWND DlgItem; // edi

  result = dword_17A990C;
  v2 = *(_DWORD *)(*(_DWORD *)(this->m_fontcolor.ColorQuadFmt + 20) + 16);
  if ( dword_17A990C == 4 )
  {
    DlgItem = GetDlgItem((HWND)g_Input.KeyInfo[176].HoldTime, 1201);
    result = *(_BYTE *)(v2 + 430012);
    if ( result )
    {
      byte_5D8808 = 1;
      sprintf(byte_17A94E4, "%03d-%03d", *(_DWORD *)(v2 + 430032), *(_DWORD *)(v2 + 430036));
      return SendMessageA(DlgItem, 0xCu, 0, (LPARAM)byte_17A94E4);
    }
    else if ( byte_5D8808 == 1 )
    {
      byte_5D8808 = 0;
      sprintf(byte_17A94E4, aStopped);
      return SendMessageA(DlgItem, 0xCu, 0, (LPARAM)byte_17A94E4);
    }
  }
  return result;
}

// 0x00517650
CCBUI::~CCBUI()
{
  UIFrameWnd *v2; // eax
  CCBUI **v3; // eax
  _DWORD *v5; // esi
  CCBUI ***i; // edi
  UIFrameWnd *v7; // eax
  CCBUI **v8; // eax
  int v9; // [esp+10h] [ebp-1Ch] BYREF
  int v10; // [esp+14h] [ebp-18h]
  int v11; // [esp+18h] [ebp-14h]
  int v12; // [esp+1Ch] [ebp-10h]
  int v13; // [esp+28h] [ebp-4h]

  v2 = (UIFrameWnd *)operator new(0x98u);
  v13 = 0;
  if ( v2 )
    v2->UIFrameWnd();
  else
    v3 = 0;
  v13 = -1;
  *((_DWORD *)this + 18) = v3;
  if ( v3 )
  {
    v9 = 483;
    v10 = 10;
    v11 = 803;
    v12 = 42;
    ((void (*)(CCBUI **, int, int *, CCBUI ***))(*v3)->m_fontcolor.Alpha)(v3, 1, &v9, this);
    ((UIWnd *)*((_DWORD *)this + 18))->CreateFromTemplate(aUiCombatAttack_0, 0);
    v9 = 480;
    v11 = 544;
    v10 = 8;
    v12 = 72;
    v5 = (_DWORD *)&unk_5700E8;
    for ( i = this + 19; ; ++i )
    {
      v7 = (UIFrameWnd *)operator new(0x98u);
      v13 = 1;
      if ( v7 )
        v7->UIFrameWnd();
      else
        v8 = 0;
      v13 = -1;
      *i = v8;
      if ( !v8 )
        break;
      ((void (*)(CCBUI **, _DWORD, int *, CCBUI ***))(*v8)->m_fontcolor.Alpha)(v8, *v5, &v9, this);
      ((UIWnd *)*i)->CreateFromTemplate(aUiCombatAttack_1, 0);
      if ( (int)++v5 >= (int)dword_570114 )
  1;
    }
  }
  0;
}

// 0x005177B0
char CCBUI::Reset()
{
  UIFrameWnd *v2; // eax
  CCBUI **v3; // eax
  UIFrameWnd *v4; // eax
  CCBUI **v5; // eax
  UIFrameWnd *v6; // eax
  CCBUI **v7; // eax
  int v8; // ecx
  int v9; // ecx
  int id; // [esp+2Ch] [ebp-824h] BYREF
  int v12; // [esp+30h] [ebp-820h] BYREF
  int v13; // [esp+34h] [ebp-81Ch]
  int v14; // [esp+38h] [ebp-818h]
  int v15; // [esp+3Ch] [ebp-814h]
  UIFrameWnd *v16; // [esp+40h] [ebp-810h]
  char pExceptionObject[1024]; // [esp+44h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+444h] [ebp-40Ch] BYREF
  int v19; // [esp+84Ch] [ebp-4h]

  id = -1;
  v2 = (UIFrameWnd *)operator new(0x9Cu);
  v16 = v2;
  v19 = 0;
  if ( v2 )
    v3 = (CCBUI **)sub_442D00(v2);
  else
    v3 = 0;
  *((_DWORD *)this + 268) = v3;
  v4 = (UIFrameWnd *)operator new(0x9Cu);
  v16 = v4;
  v19 = 1;
  if ( v4 )
    v5 = (CCBUI **)sub_442D00(v4);
  else
    v5 = 0;
  *((_DWORD *)this + 269) = v5;
  v6 = (UIFrameWnd *)operator new(0x98u);
  v16 = v6;
  v19 = 2;
  if ( v6 )
    v6->UIFrameWnd();
  else
    v7 = 0;
  v8 = (int)*((_DWORD *)this + 268);
  v19 = -1;
  *((_DWORD *)this + 270) = v7;
  if ( !v8 || !*((_DWORD *)this + 269) || !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 719),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v12 = 300;
  v13 = 30;
  v14 = 461;
  v15 = 87;
  (*(void (**)(int, int, int *, CCBUI ***))(*(_DWORD *)v8 + 16))(v8, 784, &v12, this);
  ((UIWnd *)*((_DWORD *)this + 268))->CreateFromTemplate(aUiCombatTrickn, 0);
  ((UIWnd *)*((_DWORD *)this + 268))->SetShow(1);
  ((UIWnd *)*((_DWORD *)this + 268))->GetChild((int)&id);
  ((void (*)(_DWORD, _DWORD))(**((_DWORD *)this + 268))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 268), 0);
  ((void (*)(_DWORD, int, int *, CCBUI ***))(**((_DWORD *)this + 269))->m_fontcolor.Alpha)(
    *((_DWORD *)this + 269),
    784,
    &v12,
    this);
  ((UIWnd *)*((_DWORD *)this + 269))->CreateFromTemplate(aUiCombatTrickn_0, 0);
  ((UIWnd *)*((_DWORD *)this + 269))->SetShow(1);
  ((UIWnd *)*((_DWORD *)this + 269))->GetChild((int)&id);
  ((void (*)(_DWORD, _DWORD))(**((_DWORD *)this + 269))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 269), 0);
  v9 = (int)*((_DWORD *)this + 270);
  v12 = 100;
  v13 = 100;
  v14 = 356;
  v15 = 228;
  (*(void (**)(int, int, int *, CCBUI ***))(*(_DWORD *)v9 + 16))(v9, 1024, &v12, this);
  ((UIWnd *)*((_DWORD *)this + 270))->CreateFromTemplate(aUiCombatDialog, 0);
  ((UIWnd *)*((_DWORD *)this + 270))->SetShow(1);
  ((UIWnd *)*((_DWORD *)this + 270))->GetChild((int)&id);
  ((void (*)(_DWORD, _DWORD))(**((_DWORD *)this + 270))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 270), 0);
  ((UIFrameWnd *)*((_DWORD *)this + 270))->SetPosition(5, 63);
  sub_442C80(*((_DWORD *)this + 270), 190);
  return 1;
}

// 0x00517B30
char CCBUI::CreateCombatPanel()
{
  UIProgressBar **v2; // esi
  char result; // al
  CCBUI *v4; // ecx
  int v5; // [esp+8h] [ebp-10h] BYREF
  int v6; // [esp+Ch] [ebp-Ch]
  int v7; // [esp+10h] [ebp-8h]
  int v8; // [esp+14h] [ebp-4h]

  v2 = &this->m_pRoleStateMP[2];
  result = ((CCBAIWindow *)&this->m_pRoleStateMP[2])->Update();
  if ( result )
  {
    v6 = 0;
    v7 = 0;
    v4 = (CCBUI *)*v2;
    v5 = 2;
    v7 = 251;
    v6 = 278;
    v8 = 484;
    v4->AddTask(&v5, (int)this);
    (*(void (**)(UIProgressBar *, _DWORD))(*v2)->m_fontcolor.ColorQuadFmt)(*v2, 0);
    return 1;
  }
  return result;
}

// 0x00517C10
char CCBUI::CreateAttackSequen()
{
  UIProgressBar **p_m_pRoleStateSword; // esi
  char result; // al
  CCBItemWindow *v4; // ecx
  int pRect; // [esp+8h] [ebp-10h] BYREF
  int v6; // [esp+Ch] [ebp-Ch]
  int v7; // [esp+10h] [ebp-8h]
  int v8; // [esp+14h] [ebp-4h]

  p_m_pRoleStateSword = &this->m_pRoleStateSword;
  result = ((CCBLineupWindow *)&this->m_pRoleStateSword)->CCBLineupWindow();
  if ( result )
  {
    v6 = 0;
    v7 = 0;
    v4 = (CCBItemWindow *)*p_m_pRoleStateSword;
    pRect = 14;
    v7 = 172;
    v6 = 316;
    v8 = 474;
    v4->Create(&pRect, (int)this);
    (*(void (**)(UIProgressBar *, _DWORD))(*p_m_pRoleStateSword)->m_fontcolor.ColorQuadFmt)(
      *p_m_pRoleStateSword,
      0);
    return 1;
  }
  return result;
}

// 0x00517C80
char CCBUI::CreateBattleFieldAttr()
{
  UIStaticCB **p_m_pTrickName; // esi
  char result; // al
  CCBParabolaWindow ***v4; // ecx
  int a2; // [esp+8h] [ebp-10h] BYREF
  int v6; // [esp+Ch] [ebp-Ch]
  int v7; // [esp+10h] [ebp-8h]
  int v8; // [esp+14h] [ebp-4h]

  p_m_pTrickName = &this->m_pTrickName;
  result = ((CCBLineupWindow *)&this->m_pTrickName)->~CCBLineupWindow();
  if ( result )
  {
    v6 = 0;
    v7 = 0;
    v4 = (CCBParabolaWindow ***)*p_m_pTrickName;
    a2 = 9;
    v7 = 239;
    v6 = 232;
    v8 = 482;
    v4->CCBParabolaWindow(&a2, (int)this);
    (*(void (**)(UIStaticCB *, _DWORD))(*p_m_pTrickName)->m_fontcolor.ColorQuadFmt)(*p_m_pTrickName, 0);
    return 1;
  }
  return result;
}

// 0x00517D60
char CCBUI::CreateControlWindow()
{
  int v1; // esi
  UIStatic **i; // edi
  CCBSkillWindow *v4; // ecx
  int pRect; // [esp+Ch] [ebp-10h] BYREF
  int v7; // [esp+10h] [ebp-Ch]
  int v8; // [esp+14h] [ebp-8h]
  int v9; // [esp+18h] [ebp-4h]

  v1 = 0;
  v7 = 0;
  v8 = 0;
  pRect = 0;
  v9 = 0;
  for ( i = &this->m_pDialogBack; i->Create(); ++i )
  {
    v8 = v1 + 256;
    v4 = (CCBSkillWindow *)*i;
    pRect = v1;
    v7 = 0;
    v9 = 256;
    v4->Create(&pRect, (int)this);
    (*(void (**)(UIStatic *, _DWORD))(*i)->m_fontcolor.ColorQuadFmt)(*i, 0);
    v1 += 200;
    if ( v1 >= 800 )
      return 1;
  }
  return 0;
}

// 0x00517DF0
char CCBUI::CreateItemWindow()
{
  CCBUI ***v2; // edi
  char result; // al
  UIWnd **v4; // ecx
  CCBUI ***v5; // edi
  UIWnd **v6; // ecx
  CCBUI ***v7; // edi
  UIWnd **v8; // ecx
  CCBUI ***v9; // edi
  UIWnd **v10; // ecx
  CCBUI ***v11; // edi
  UIWnd **v12; // ecx
  CCBUI ***v13; // edi
  UIWnd **v14; // ecx
  CCBUI ***v15; // edi
  UIWnd **v16; // ecx
  CCBUI ***v17; // edi
  UIWnd **v18; // ecx
  int id; // [esp+7Ch] [ebp-14h] BYREF
  int v20; // [esp+80h] [ebp-10h] BYREF
  int v21; // [esp+84h] [ebp-Ch]
  int v22; // [esp+88h] [ebp-8h]
  int v23; // [esp+8Ch] [ebp-4h]

  v21 = 0;
  v2 = this + 271;
  v22 = 0;
  v20 = 0;
  v23 = 0;
  id = -1;
  result = ((CCBAIWindow *)this + 271)->Reset();
  if ( result )
  {
    v4 = *v2;
    v20 = 284;
    v22 = 516;
    v21 = 268;
    v23 = 332;
    ((void (*)(UIWnd **, int, int *, CCBUI ***))(*v4)->m_fontcolor.Alpha)(v4, 531, &v20, this);
    ((UIWnd *)*v2)->CreateFromTemplate(aUiCombatResult_6, 0);
    ((UIWnd *)*v2)->SetShow(1);
    ((UIWnd *)*v2)->GetChild((int)&id);
    ((void (*)(CCBUI **, _DWORD))(**v2)->m_fontcolor.ColorQuadFmt)(*v2, 0);
    v5 = this + 272;
    result = ((CCBAIWindow *)this + 272)->Reset();
    if ( result )
    {
      v6 = *v5;
      v20 = 249;
      v22 = 551;
      v21 = 263;
      v23 = 337;
      ((void (*)(UIWnd **, int, int *, CCBUI ***))(*v6)->m_fontcolor.Alpha)(v6, 533, &v20, this);
      ((UIWnd *)*v5)->CreateFromTemplate(aUiCombatResult_8, 0);
      ((UIWnd *)*v5)->SetShow(1);
      ((UIWnd *)*v5)->GetChild((int)&id);
      ((void (*)(CCBUI **, _DWORD))(**v5)->m_fontcolor.ColorQuadFmt)(*v5, 0);
      v7 = this + 273;
      result = ((CCBAIWindow *)this + 273)->Reset();
      if ( result )
      {
        v8 = *v7;
        v20 = 249;
        v22 = 551;
        v21 = 263;
        v23 = 337;
        ((void (*)(UIWnd **, int, int *, CCBUI ***))(*v8)->m_fontcolor.Alpha)(v8, 534, &v20, this);
        ((UIWnd *)*v7)->CreateFromTemplate(aUiCombatResult_9, 0);
        ((UIWnd *)*v7)->SetShow(1);
        ((UIWnd *)*v7)->GetChild((int)&id);
        ((void (*)(CCBUI **, _DWORD))(**v7)->m_fontcolor.ColorQuadFmt)(*v7, 0);
        v9 = this + 274;
        result = ((CCBAIWindow *)this + 274)->Reset();
        if ( result )
        {
          v10 = *v9;
          v20 = 249;
          v22 = 551;
          v21 = 263;
          v23 = 337;
          ((void (*)(UIWnd **, int, int *, CCBUI ***))(*v10)->m_fontcolor.Alpha)(v10, 535, &v20, this);
          ((UIWnd *)*v9)->CreateFromTemplate(aUiCombatResult_10, 0);
          ((UIWnd *)*v9)->SetShow(1);
          ((UIWnd *)*v9)->GetChild((int)&id);
          ((void (*)(CCBUI **, _DWORD))(**v9)->m_fontcolor.ColorQuadFmt)(*v9, 0);
          v11 = this + 275;
          result = ((CCBAIWindow *)this + 275)->Reset();
          if ( result )
          {
            v12 = *v11;
            v20 = 249;
            v22 = 551;
            v21 = 263;
            v23 = 337;
            ((void (*)(UIWnd **, int, int *, CCBUI ***))(*v12)->m_fontcolor.Alpha)(v12, 536, &v20, this);
            ((UIWnd *)*v11)->CreateFromTemplate(aUiCombatResult_11, 0);
            ((UIWnd *)*v11)->SetShow(1);
            ((UIWnd *)*v11)->GetChild((int)&id);
            ((void (*)(CCBUI **, _DWORD))(**v11)->m_fontcolor.ColorQuadFmt)(*v11, 0);
            v13 = this + 276;
            result = ((CCBAIWindow *)this + 276)->Reset();
            if ( result )
            {
              v14 = *v13;
              v20 = 249;
              v22 = 551;
              v21 = 263;
              v23 = 337;
              ((void (*)(UIWnd **, int, int *, CCBUI ***))(*v14)->m_fontcolor.Alpha)(v14, 538, &v20, this);
              ((UIWnd *)*v13)->CreateFromTemplate(aUiCombatResult_12, 0);
              ((UIWnd *)*v13)->SetShow(1);
              ((UIWnd *)*v13)->GetChild((int)&id);
              ((void (*)(CCBUI **, _DWORD))(**v13)->m_fontcolor.ColorQuadFmt)(*v13, 0);
              v15 = this + 277;
              result = ((CCBAIWindow *)this + 277)->Reset();
              if ( result )
              {
                v16 = *v15;
                v20 = 249;
                v22 = 551;
                v21 = 263;
                v23 = 337;
                ((void (*)(UIWnd **, int, int *, CCBUI ***))(*v16)->m_fontcolor.Alpha)(v16, 539, &v20, this);
                ((UIWnd *)*v15)->CreateFromTemplate(aUiCombatResult_13, 0);
                ((UIWnd *)*v15)->SetShow(1);
                ((UIWnd *)*v15)->GetChild((int)&id);
                ((void (*)(CCBUI **, _DWORD))(**v15)->m_fontcolor.ColorQuadFmt)(*v15, 0);
                v17 = this + 278;
                result = ((CCBAIWindow *)this + 278)->Reset();
                if ( result )
                {
                  v18 = *v17;
                  v20 = 221;
                  v22 = 579;
                  v21 = 255;
                  v23 = 345;
                  ((void (*)(UIWnd **, int, int *, CCBUI ***))(*v18)->m_fontcolor.Alpha)(
                    v18,
                    532,
                    &v20,
                    this);
                  ((UIWnd *)*v17)->CreateFromTemplate(aUiCombatResult_7, 0);
                  ((UIWnd *)*v17)->SetShow(1);
                  ((UIWnd *)*v17)->GetChild((int)&id);
                  ((void (*)(CCBUI **, _DWORD))(**v17)->m_fontcolor.ColorQuadFmt)(*v17, 0);
                  return 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

// 0x005181E0
char CCBUI::CreateParaWindow()
{
  UIStatic *v2; // ecx
  UIStatic *v3; // ecx
  UIProgressBar *v4; // ecx
  UIProgressBar *v5; // ecx
  UIProgressBar *v6; // ecx
  UIProgressBar *v7; // ecx
  UIProgressBar *v8; // ecx
  UIProgressBar *v9; // ecx
  UIProgressBar *v10; // ecx
  UIProgressBar *v11; // ecx
  UIStatic *v12; // ecx
  int v13; // edi
  UIStatic **p_m_pDialogBack; // ebx

  this->m_pResultFireLvup = (UIStatic *)this->m_pResultWaterLvup->m_fontcolor.ColorQuadFmt;
  v2 = (UIStatic *)this->m_pRoleStateHermit[6];
  if ( v2 )
    (*(void (**)(UIStatic *, _DWORD))v2->m_fontcolor.ColorQuadFmt)(v2, 0);
  v3 = (UIStatic *)this->m_pRoleStateHermit[7];
  if ( v3 )
    (*(void (**)(UIStatic *, _DWORD))v3->m_fontcolor.ColorQuadFmt)(v3, 0);
  v4 = (UIProgressBar *)this->m_pRoleStateHP[0];
  if ( v4 )
    (*(void (**)(UIProgressBar *, _DWORD))v4->m_fontcolor.ColorQuadFmt)(v4, 0);
  v5 = (UIProgressBar *)this->m_pRoleStateHP[1];
  if ( v5 )
    (*(void (**)(UIProgressBar *, _DWORD))v5->m_fontcolor.ColorQuadFmt)(v5, 0);
  v6 = (UIProgressBar *)this->m_pRoleStateHP[2];
  if ( v6 )
    (*(void (**)(UIProgressBar *, _DWORD))v6->m_fontcolor.ColorQuadFmt)(v6, 0);
  v7 = (UIProgressBar *)this->m_pRoleStateHP[3];
  if ( v7 )
    (*(void (**)(UIProgressBar *, _DWORD))v7->m_fontcolor.ColorQuadFmt)(v7, 0);
  v8 = (UIProgressBar *)this->m_pRoleStateGP[0];
  if ( v8 )
    (*(void (**)(UIProgressBar *, _DWORD))v8->m_fontcolor.ColorQuadFmt)(v8, 0);
  v9 = (UIProgressBar *)this->m_pRoleStateGP[1];
  if ( v9 )
    (*(void (**)(UIProgressBar *, _DWORD))v9->m_fontcolor.ColorQuadFmt)(v9, 0);
  v10 = (UIProgressBar *)this->m_pRoleStateGP[2];
  if ( v10 )
    (*(void (**)(UIProgressBar *, _DWORD))v10->m_fontcolor.ColorQuadFmt)(v10, 0);
  v11 = (UIProgressBar *)this->m_pRoleStateGP[3];
  if ( v11 )
    (*(void (**)(UIProgressBar *, _DWORD))v11->m_fontcolor.ColorQuadFmt)(v11, 0);
  (*(void (**)(UIProgressBar *, _DWORD))this->m_pRoleStateMP[1]->m_fontcolor.ColorQuadFmt)(
    this->m_pRoleStateMP[1],
    0);
  (*(void (**)(UIProgressBar *, _DWORD))this->m_pRoleStateMP[2]->m_fontcolor.ColorQuadFmt)(
    this->m_pRoleStateMP[2],
    0);
  (*(void (**)(UIProgressBar *, _DWORD))this->m_pRoleStateMP[3]->m_fontcolor.ColorQuadFmt)(
    this->m_pRoleStateMP[3],
    0);
  (*(void (**)(UIProgressBar *, _DWORD))this->m_pRoleStateSword->m_fontcolor.ColorQuadFmt)(
    this->m_pRoleStateSword,
    0);
  (*(void (**)(UIStaticCB *, _DWORD))this->m_pTrickName->m_fontcolor.ColorQuadFmt)(this->m_pTrickName, 0);
  (*(void (**)(UIStaticCB *, _DWORD))this->m_pTrickName2->m_fontcolor.ColorQuadFmt)(this->m_pTrickName2, 0);
  (*(void (**)(UIStatic *, _DWORD))this->m_pLosePanel->m_fontcolor.ColorQuadFmt)(this->m_pLosePanel, 0);
  this->m_pRoleStateImmunity[10]->m_ppicInfo = 0;
  (*(void (**)(UIStatic *, _DWORD))this->m_pRoleStateImmunity[10]->m_fontcolor.ColorQuadFmt)(
    this->m_pRoleStateImmunity[10],
    0);
  this->m_pWinPanel->m_ppicInfo = 0;
  (*(void (**)(UIStatic *, _DWORD))this->m_pWinPanel->m_fontcolor.ColorQuadFmt)(this->m_pWinPanel, 0);
  this->CreateResultWindow(0);
  v12 = (UIStatic *)this->m_pRoleStateImmunity[9];
  if ( v12 )
  {
    sub_43FE90((int)v12);
    ((UIWnd *)this->m_pRoleStateImmunity[9])->FindChild(50.0);
    ((UIWnd *)this->m_pRoleStateImmunity[9])->FindChildByName(0.0);
  }
  v13 = 0;
  p_m_pDialogBack = &this->m_pDialogBack;
  do
  {
    (*p_m_pDialogBack)->m_FVF = v13;
    (*(void (**)(UIStatic *, _DWORD))(*p_m_pDialogBack)->m_fontcolor.ColorQuadFmt)(*p_m_pDialogBack, 0);
    ++v13;
    ++p_m_pDialogBack;
  }
  while ( v13 < 4 );
  memset(&this->m_pResultEarthLvup, 0, 0x5A0u);
  this->m_Task[21].fExpectStartTime = 0.0;
  this->m_Task[21].fExpectEndTime = 0.0;
  this->m_Task[21].param.fFromY = 0.0;
  this->m_Task[21].param.fEndX = NAN;
  this->m_Task[21].param.pUI = 0;
  this->m_Task[21].param.fFromX = NAN;
  return 1;
}

// 0x005183C0
int CCBUI::CreateMagicWindow(int a2)
{
  CCBUI *v2; // ecx
  CCBUI *v3; // esi
  UIStatic *v4; // ecx
  UIStatic *v5; // ecx
  UIStatic *m_pLosePanel; // ecx
  UIProgressBar *v7; // ecx
  UIProgressBar *v8; // ecx
  UIProgressBar *v9; // ecx
  UIProgressBar *v10; // ecx
  UIProgressBar *m_pRoleStateSword; // ecx
  UIStaticCB *m_pTrickName; // ecx
  UIStaticCB *m_pTrickName2; // ecx
  UIStatic *v14; // ecx
  UIStatic *m_pWinPanel; // ecx
  int v16; // edi
  UIStatic **p_m_pDialogBack; // esi
  int result; // eax

  v3 = v2;
  v4 = (UIStatic *)v2->m_pRoleStateHermit[6];
  if ( v4 )
    (*(void (**)(UIStatic *, _DWORD))v4->m_fontcolor.ColorQuadFmt)(v4, 0);
  v5 = (UIStatic *)v3->m_pRoleStateHermit[7];
  if ( v5 )
    (*(void (**)(UIStatic *, _DWORD))v5->m_fontcolor.ColorQuadFmt)(v5, 0);
  m_pLosePanel = (UIStatic *)v3->m_pLosePanel;
  if ( m_pLosePanel )
    (*(void (**)(UIStatic *, _DWORD))m_pLosePanel->m_fontcolor.ColorQuadFmt)(m_pLosePanel, 0);
  v7 = (UIProgressBar *)v3->m_pRoleStateMP[0];
  if ( v7 )
    (*(void (**)(UIProgressBar *, _DWORD))v7->m_fontcolor.ColorQuadFmt)(v7, 0);
  v8 = (UIProgressBar *)v3->m_pRoleStateMP[1];
  if ( v8 )
    (*(void (**)(UIProgressBar *, _DWORD))v8->m_fontcolor.ColorQuadFmt)(v8, 0);
  v9 = (UIProgressBar *)v3->m_pRoleStateMP[2];
  if ( v9 )
    (*(void (**)(UIProgressBar *, _DWORD))v9->m_fontcolor.ColorQuadFmt)(v9, 0);
  v10 = (UIProgressBar *)v3->m_pRoleStateMP[3];
  if ( v10 )
    (*(void (**)(UIProgressBar *, _DWORD))v10->m_fontcolor.ColorQuadFmt)(v10, 0);
  m_pRoleStateSword = (UIProgressBar *)v3->m_pRoleStateSword;
  if ( m_pRoleStateSword )
    (*(void (**)(UIProgressBar *, _DWORD))m_pRoleStateSword->m_fontcolor.ColorQuadFmt)(m_pRoleStateSword, 0);
  m_pTrickName = (UIStaticCB *)v3->m_pTrickName;
  if ( m_pTrickName )
    (*(void (**)(UIStaticCB *, _DWORD))m_pTrickName->m_fontcolor.ColorQuadFmt)(m_pTrickName, 0);
  m_pTrickName2 = (UIStaticCB *)v3->m_pTrickName2;
  if ( m_pTrickName2 )
    (*(void (**)(UIStaticCB *, _DWORD))m_pTrickName2->m_fontcolor.ColorQuadFmt)(m_pTrickName2, 0);
  v14 = (UIStatic *)v3->m_pRoleStateImmunity[10];
  if ( v14 )
    (*(void (**)(UIStatic *, _DWORD))v14->m_fontcolor.ColorQuadFmt)(v14, 0);
  m_pWinPanel = (UIStatic *)v3->m_pWinPanel;
  if ( m_pWinPanel )
    (*(void (**)(UIStatic *, _DWORD))m_pWinPanel->m_fontcolor.ColorQuadFmt)(m_pWinPanel, 0);
  v3->CreateResultWindow(0);
  v16 = 0;
  p_m_pDialogBack = &v3->m_pDialogBack;
  do
  {
    result = (int)*p_m_pDialogBack;
    if ( *p_m_pDialogBack )
    {
      *(_DWORD *)(result + 172) = v16;
      result = (*(int (**)(UIStatic *, _DWORD))(*p_m_pDialogBack)->m_fontcolor.ColorQuadFmt)(
                 *p_m_pDialogBack,
                 0);
    }
    ++v16;
    ++p_m_pDialogBack;
  }
  while ( v16 < 4 );
  return result;
}

// 0x005184C0
int CCBUI::CreateSkillWindow(char a2)
{
  UIProgressBar *v2; // ecx

  v2 = (UIProgressBar *)this->m_pRoleStateMP[0];
  if ( a2 )
    return (*(int (**)(UIProgressBar *, int))v2->m_fontcolor.ColorQuadFmt)(v2, 1);
  else
    return (*(int (**)(UIProgressBar *, _DWORD))v2->m_fontcolor.ColorQuadFmt)(v2, 0);
}

// 0x00518AF0
int CCBUI::CreateLineupWindow(int a2, char a3)
{
  UIProgressBar *m_pRoleStateSword; // ecx

  this->m_pRoleStateSword->m_ProgressRc.bottom = a2;
  m_pRoleStateSword = (UIProgressBar *)this->m_pRoleStateSword;
  if ( a3 )
    return (*(int (**)(UIProgressBar *, int))m_pRoleStateSword->m_fontcolor.ColorQuadFmt)(
             m_pRoleStateSword,
             1);
  else
    return (*(int (**)(UIProgressBar *, _DWORD))m_pRoleStateSword->m_fontcolor.ColorQuadFmt)(
             m_pRoleStateSword,
             0);
}

// 0x00518B20
char CCBUI::CreateProtectWindow()
{
  return this->m_pDialogBack->m_nTextW;
}

// 0x00518B30
char CCBUI::CreateResultWindow(char a2)
{
  int i; // edi
  char result; // al
  int v5; // ebx
  UIStatic **v6; // edi
  int v7; // ebx
  UIStatic **v8; // edi
  int v9; // ebx
  UIStatic **m_pRoleStateFaceName; // esi
  int v11; // edi

  if ( a2 )
  {
    for ( i = 0; i < 5; ++i )
    {
      result = *(_BYTE *)(this->m_pResultWaterLvup->m_fontcolor.Alpha + 892 * i + 577);
      if ( result )
      {
        (*(void (**)(UIStatic *, int))this->m_pBattleFieldAttr[i + 5]->m_fontcolor.ColorQuadFmt)(
          this->m_pBattleFieldAttr[i + 5],
          1);
        (*(void (**)(UIStatic *, int))this->m_pAttackSequenFace[i + 4]->m_fontcolor.ColorQuadFmt)(
          this->m_pAttackSequenFace[i + 4],
          1);
        v5 = *(unsigned __int8 *)(((CCBRoleState *)this->m_pResultWaterLvup->m_fontcolor.Alpha)->InitUI(i)
                                + 24);
        (*(void (**)(UIStatic *, int))this->m_pRoleStateHermit[v5 + 8]->m_fontcolor.ColorQuadFmt)(
          this->m_pRoleStateHermit[v5 + 8],
          1);
        (*(void (**)(UIStatic *, int))this->m_pRoleStateImmunity[v5 + 1]->m_fontcolor.ColorQuadFmt)(
          this->m_pRoleStateImmunity[v5 + 1],
          1);
        (*(void (**)(UIStatic *, int))this->m_pRoleStateImmunity[v5 + 5]->m_fontcolor.ColorQuadFmt)(
          this->m_pRoleStateImmunity[v5 + 5],
          1);
        result = (*(int (**)(UIStatic *, int))this->m_pBattleFieldAttr[v5 + 1]->m_fontcolor.ColorQuadFmt)(
                   this->m_pBattleFieldAttr[v5 + 1],
                   1);
        if ( !i )
          result = (*(int (**)(UIStatic *, int))this->m_pRoleStateImmunity[9]->m_fontcolor.ColorQuadFmt)(
                     this->m_pRoleStateImmunity[9],
                     1);
      }
    }
  }
  else
  {
    (*(void (**)(UIStatic *, _DWORD))this->m_pRoleStateImmunity[9]->m_fontcolor.ColorQuadFmt)(
      this->m_pRoleStateImmunity[9],
      0);
    v6 = &this->m_pRoleStateImmunity[1];
    v7 = 4;
    do
    {
      (*(void (**)(_DWORD, _DWORD))(*(v6 - 4))->m_fontcolor.ColorQuadFmt)(*(v6 - 4), 0);
      (*(void (**)(UIStatic *, _DWORD))(*v6)->m_fontcolor.ColorQuadFmt)(*v6, 0);
      (*(void (**)(UIStatic *, _DWORD))v6[4]->m_fontcolor.ColorQuadFmt)(v6[4], 0);
      (*(void (**)(_DWORD, _DWORD))(*(v6 - 229))->m_fontcolor.ColorQuadFmt)(*(v6 - 229), 0);
      ++v6;
      --v7;
    }
    while ( v7 );
    v8 = &this->m_pAttackSequenFace[4];
    v9 = 5;
    do
    {
      (*(void (**)(_DWORD, _DWORD))(*(v8 - 5))->m_fontcolor.ColorQuadFmt)(*(v8 - 5), 0);
      (*(void (**)(UIStatic *, _DWORD))(*v8)->m_fontcolor.ColorQuadFmt)(*v8, 0);
      ++v8;
      --v9;
    }
    while ( v9 );
    m_pRoleStateFaceName = this->m_pRoleStateFaceName;
    v11 = 11;
    do
    {
      (*(void (**)(_DWORD, _DWORD))(*(m_pRoleStateFaceName - 11))->m_fontcolor.ColorQuadFmt)(
        *(m_pRoleStateFaceName - 11),
        0);
      (*(void (**)(UIStatic *, _DWORD))(*m_pRoleStateFaceName)->m_fontcolor.ColorQuadFmt)(
        *m_pRoleStateFaceName,
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[11]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[11],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[22]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[22],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[55]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[55],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[66]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[66],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[33]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[33],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[44]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[44],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[77]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[77],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[88]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[88],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[99]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[99],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[110]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[110],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[121]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[121],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[132]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[132],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[143]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[143],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[154]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[154],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[165]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[165],
        0);
      (*(void (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[176]->m_fontcolor.ColorQuadFmt)(
        m_pRoleStateFaceName[176],
        0);
      result = (*(int (**)(UIStatic *, _DWORD))m_pRoleStateFaceName[187]->m_fontcolor.ColorQuadFmt)(
                 m_pRoleStateFaceName[187],
                 0);
      ++m_pRoleStateFaceName;
      --v11;
    }
    while ( v11 );
  }
  return result;
}

// 0x00518D40
int CCBUI::CreateFiveNimbus(char a2)
{
  int v3; // ebx
  int v4; // ebp
  int i; // esi

  if ( !a2 )
    return (*(int (**)(UIStaticCB *, _DWORD))this->m_pTrickName->m_fontcolor.ColorQuadFmt)(
             this->m_pTrickName,
             0);
  v3 = 0;
  v4 = 0;
  for ( i = 96; i < 116; i += 4 )
  {
    if ( *(_BYTE *)(this->m_pResultWaterLvup->m_fontcolor.Alpha + v4 + 577) )
    {
      (***(void (****)(_DWORD, int))((char *)&this->m_pTrickName->m_fontcolor.ColorQuadFmt + i))(
        *(int *)((char *)&this->m_pTrickName->m_fontcolor.ColorQuadFmt + i),
        1);
      *(_DWORD *)((char *)this->m_pTrickName + i - 24) = *(_DWORD *)(((CCBRoleState *)this->m_pResultWaterLvup->m_fontcolor.Alpha)->InitUI(v3)
                                                                   + 584);
      ((UIWnd *)*(UIWnd **)((char *)&this->m_pTrickName->m_fontcolor.ColorQuadFmt + i))->ScreenToClient(dword_57024C[*(_DWORD *)((char *)this->m_pTrickName + i - 24)] + 9, dword_570268[*(_DWORD *)((char *)this->m_pTrickName + i - 24)] + 232);
    }
    else
    {
      (***(void (****)(_DWORD, _DWORD))((char *)&this->m_pTrickName->m_fontcolor.ColorQuadFmt + i))(
        *(int *)((char *)&this->m_pTrickName->m_fontcolor.ColorQuadFmt + i),
        0);
    }
    ++v3;
    v4 += 892;
  }
  return (*(int (**)(UIStaticCB *, int))this->m_pTrickName->m_fontcolor.ColorQuadFmt)(this->m_pTrickName, 1);
}

// 0x00518E60
int CCBUI::HideAll()
{
  UIStatic **m_pRoleStateFaceName; // esi
  int v2; // ebx
  int result; // eax
  float v4; // [esp+10h] [ebp-8h]
  int v5; // [esp+14h] [ebp-4h]

  HIBYTE(v5) = -1;
  v4 = sin(*(float *)&this->m_pResultWaterLvup->m_childs.m_nMaxSize * 12.0) * 50.0;
  m_pRoleStateFaceName = this->m_pRoleStateFaceName;
  v2 = 4;
  BYTE2(v5) = (int)v4 - 56;
  BYTE1(v5) = BYTE2(v5);
  LOBYTE(v5) = BYTE2(v5);
  do
  {
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    v5->UpdateAnim();
    result = v5->UpdateAnim();
    ++m_pRoleStateFaceName;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x00518FE0
int CCBUI::ShowBattleFieldAttr(int a2)
{
  UIStatic **v2; // esi
  UIStatic *m_pResultWaterLvup; // ecx
  double v4; // st6
  double v5; // st7
  double v6; // st7

  v2 = &this->m_pResultEarthLvup + 18 * LODWORD(this->m_Task[21].param.fEndX);
  if ( !*((_BYTE *)&this->m_pItemWindow + 72 * LODWORD(this->m_Task[21].param.fEndX) + 1) )
  {
    *((float *)&this->m_pMagicWindow + 18 * LODWORD(this->m_Task[21].param.fEndX)) = *(float *)&this->m_pResultWaterLvup->m_childs.m_nMaxSize;
    *((_BYTE *)v2 + 17) = 1;
  }
  m_pResultWaterLvup = (UIStatic *)this->m_pResultWaterLvup;
  v4 = *((float *)v2 + 7) + *((float *)v2 + 6);
  if ( *(float *)&m_pResultWaterLvup->m_childs.m_nMaxSize <= v4 )
    return 0;
  v5 = *(float *)&m_pResultWaterLvup->m_childs.m_nMaxSize - v4;
  v6 = v5 * (v5 * *((float *)v2 + 8)) * 0.5 + *((float *)v2 + 11);
  if ( v6 > *((float *)v2 + 13) )
  {
    v6 = *((float *)v2 + 13);
    *((_BYTE *)v2 + 18) = 1;
  }
  ((UIWnd *)v2[9])->ScreenToClient((__int64)*((float *)v2 + 10), (__int64)v6);
  return 0;
}

// 0x00519080
int CCBUI::ShowControlWindow(int a2)
{
  UIStatic **v2; // esi
  double v3; // st6
  float v5; // [esp+8h] [ebp-8h]
  float v6; // [esp+Ch] [ebp-4h]

  v2 = &this->m_pResultEarthLvup + 18 * LODWORD(this->m_Task[21].param.fEndX);
  if ( !*((_BYTE *)&this->m_pItemWindow + 72 * LODWORD(this->m_Task[21].param.fEndX) + 1) )
  {
    *((float *)&this->m_pMagicWindow + 18 * LODWORD(this->m_Task[21].param.fEndX)) = *(float *)&this->m_pResultWaterLvup->m_childs.m_nMaxSize;
    *((_BYTE *)v2 + 17) = 1;
  }
  v3 = *((float *)v2 + 7) + *((float *)v2 + 6);
  if ( *(float *)&this->m_pResultWaterLvup->m_childs.m_nMaxSize <= v3 )
    return 0;
  v6 = (*(float *)&this->m_pResultWaterLvup->m_childs.m_nMaxSize - v3) / *((float *)v2 + 8);
  v5 = (*((float *)v2 + 12) - *((float *)v2 + 10)) * v6 + *((float *)v2 + 10);
  sprintf(byte_17ACB08, "%d", (int)v5);
  ((UIWnd *)v2[9])->SetEnable(byte_17ACB08, 1);
  if ( v6 < 1.0 )
    return 0;
  sprintf(byte_17ACB08, "%d", (int)*((float *)v2 + 12));
  ((UIWnd *)v2[9])->SetEnable(byte_17ACB08, 1);
  *((_BYTE *)v2 + 18) = 1;
  return 0;
}

// 0x00519200
int CCBUI::ShowDialogWindow()
{
  int v2; // esi
  _BYTE *v3; // edi
  int result; // eax

  v2 = 0;
  v3 = (char *)&this->m_pItemWindow + 2;
  do
  {
    if ( *(v3 - 2) == 1 && *v3 == 1 )
      LOBYTE(result) = this->ShowAIWindow(v2);
    ++v2;
    v3 += 72;
  }
  while ( v2 < 20 );
  return result;
}

// 0x00519230
char CCBUI::ShowAIWindow(int a2)
{
  *((_BYTE *)&this->m_pItemWindow + 72 * a2) = 0;
  --LODWORD(this->m_Task[21].param.fFromY);
  return 1;
}

// 0x00519260
char CCBUI::IsResultWindowClosed(
        CCBUI *this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        const void *a9)
{
  int v10; // eax
  CCBItemWindow **i; // ecx
  char *v13; // eax

  if ( SLODWORD(this->m_Task[21].param.fFromY) >= 19 )
    return 0;
  v10 = 0;
  for ( i = &this->m_pItemWindow; *(_BYTE *)i; i += 18 )
  {
    if ( ++v10 >= 20 )
      return 0;
  }
  v13 = (char *)this + 72 * v10;
  v13[1184] = 1;
  v13[1185] = 0;
  v13[1186] = 0;
  *((_DWORD *)v13 + 299) = a7;
  *((_DWORD *)v13 + 300) = a8;
  *((_DWORD *)v13 + 297) = a6;
  qmemcpy(v13 + 1204, a9, 0x20u);
  v13 += 1168;
  *(_DWORD *)v13 = a2;
  *((_DWORD *)v13 + 1) = a3;
  *((_DWORD *)v13 + 2) = a4;
  *((_DWORD *)v13 + 3) = a5;
  ++LODWORD(this->m_Task[21].param.fFromY);
  return 1;
}

// 0x00519360
UIWnd * CCBUI::ShowLineupWindow(CCBUI *Block, char a2)
{
  Block->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x005193D0
int CCBUI::OnMessage()
{
  this->m_childs.m_pData = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_nMaxSize = 0;
  this->m_childs.m_nGrowBy = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  this->m_benable = 0;
  this->m_bfocus = 0;
  this->m_pbktex = 0;
  this->m_pAttackSequenBack = 0;
  this->pPanel = 0;
  return 0;
}

// 0x00519400
char CCBUI::CreateImbibeNimbus(_DWORD *pRect, int parent)
{
  UIFrameWnd *v4; // eax
  void *v5; // eax
  char pExceptionObject[1024]; // [esp+Ch] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+40Ch] [ebp-40Ch] BYREF
  int v9; // [esp+814h] [ebp-4h]

  this->Create(1879048193, pRect, parent);
  v4 = (UIFrameWnd *)operator new(0x98u);
  v9 = 0;
  if ( v4 )
    v4->UIFrameWnd();
  else
    v5 = 0;
  v9 = -1;
  this->m_childs.m_pData = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 2090),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
  (*(void (**)(void *, int, _DWORD *, CCBUI *))(*(_DWORD *)this->m_childs.m_pData + 16))(
    this->m_childs.m_pData,
    256,
    pRect,
    this);
  ((UIWnd *)this->m_childs.m_pData)->CreateFromTemplate(aUiCombatContro_33, 0);
  (**(void (***)(void *, int))this->m_childs.m_pData)(this->m_childs.m_pData, 1);
  ((CCBUI *)this)->SetNimbusToNimbusControl();
  return 1;
}

// 0x00519510
int CCBUI::ConfigImbibeNimbus()
{
  int result; // eax
  void *m_pData; // ecx
  int m_nSize; // ecx
  int m_nMaxSize; // ecx
  int m_nGrowBy; // ecx
  int m_bcreateok; // ecx
  int m_bvisible; // ecx
  int m_benable; // ecx
  int m_bfocus; // ecx
  gbTexture *m_pbktex; // ecx
  UIStatic *m_pAttackSequenBack; // ecx
  UIStatic *pPanel; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  m_pData = (void *)this->m_childs.m_pData;
  if ( m_pData )
  {
    result = (*(int (**)(void *, int))(*(_DWORD *)m_pData + 20))(m_pData, 1);
    this->m_childs.m_pData = 0;
  }
  m_nSize = this->m_childs.m_nSize;
  if ( m_nSize )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nSize + 20))(m_nSize, 1);
    this->m_childs.m_nSize = 0;
  }
  m_nMaxSize = this->m_childs.m_nMaxSize;
  if ( m_nMaxSize )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nMaxSize + 20))(m_nMaxSize, 1);
    this->m_childs.m_nMaxSize = 0;
  }
  m_nGrowBy = this->m_childs.m_nGrowBy;
  if ( m_nGrowBy )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nGrowBy + 20))(m_nGrowBy, 1);
    this->m_childs.m_nGrowBy = 0;
  }
  m_bcreateok = this->m_bcreateok;
  if ( m_bcreateok )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bcreateok + 20))(m_bcreateok, 1);
    this->m_bcreateok = 0;
  }
  m_bvisible = this->m_bvisible;
  if ( m_bvisible )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bvisible + 20))(m_bvisible, 1);
    this->m_bvisible = 0;
  }
  m_benable = this->m_benable;
  if ( m_benable )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_benable + 20))(m_benable, 1);
    this->m_benable = 0;
  }
  m_bfocus = this->m_bfocus;
  if ( m_bfocus )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bfocus + 20))(m_bfocus, 1);
    this->m_bfocus = 0;
  }
  m_pbktex = (gbTexture *)this->m_pbktex;
  if ( m_pbktex )
  {
    result = (*(int (**)(gbTexture *, int))(*(_DWORD *)m_pbktex->_pad_0000 + 20))(m_pbktex, 1);
    this->m_pbktex = 0;
  }
  m_pAttackSequenBack = (UIStatic *)this->m_pAttackSequenBack;
  if ( m_pAttackSequenBack )
  {
    result = (*(int (**)(UIStatic *, int))(m_pAttackSequenBack->m_fontcolor.ColorQuadFmt + 20))(
               m_pAttackSequenBack,
               1);
    this->m_pAttackSequenBack = 0;
  }
  pPanel = (UIStatic *)this->pPanel;
  if ( pPanel )
  {
    result = (*(int (**)(UIStatic *, int))(pPanel->m_fontcolor.ColorQuadFmt + 20))(pPanel, 1);
    this->pPanel = 0;
  }
  return result;
}

// 0x005195E0
int CCBUI::CheckNimbusMove(int a2, unsigned int a3, int a4)
{
  char *Instance; // eax

  if ( a2 == 1001 )
  {
    if ( a3 >= 0x103 && a3 <= 0x10C )
    {
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(aWa001, 1);
    }
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3, a4);
  }
  else if ( a2 == 1007 && a4 != -1 )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3, a4);
  }
  return a2->SendMessage(a3, a4);
}

// 0x00519660
BOOL CCBUI::IsImbibeNimbusNotFinish(int a2, int a3)
{
  if ( this->m_rect.top == 1
    && (g_Input.m_DIKToKEY[1] == 1 && (g_Input.m_shiftedKeyStates[268] & 0xF) == 1 || g_Input.m_DIKToKEY[5] == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(128, -1);
  }
  return this->HitTest(a2, a3);
}

// 0x005196C0
struct gbVFileSystem * CCBUI::SetNimbusToNimbusControl()
{
  CCBUI ***v2; // edi
  int a4; // [esp+24h] [ebp-10h] BYREF
  int v5; // [esp+28h] [ebp-Ch]
  int v6; // [esp+2Ch] [ebp-8h]
  int v7; // [esp+30h] [ebp-4h]

  v2 = this + 28;
  a4 = -13;
  v6 = 71;
  v5 = 185;
  v7 = 269;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 28, 269, (int)&a4, (int)aUiCombatContro_42);
  ((void (*)(CCBUI **, _DWORD))(**v2)->m_fontcolor.ColorQuadFmt)(*v2, 0);
  a4 = 53;
  v6 = 99;
  v5 = 156;
  v7 = 202;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 19, 259, (int)&a4, (int)aUiCombatContro_34);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 19))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 19), 1);
  ((PalScript *)*((_DWORD *)this + 19))->OpenScript(aUiCombatContro_35, 0);
  a4 = 57;
  v6 = 103;
  v5 = 97;
  v7 = 143;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 20, 260, (int)&a4, (int)aUiCombatContro_36);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 20))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 20), 1);
  ((PalScript *)*((_DWORD *)this + 20))->OpenScript(aUiCombatContro_37, 0);
  a4 = 2;
  v6 = 48;
  v5 = 153;
  v7 = 199;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 21, 261, (int)&a4, (int)aUiCombatContro_38);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 21))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 21), 1);
  ((PalScript *)*((_DWORD *)this + 21))->OpenScript(aUiCombatContro_39, 0);
  a4 = 56;
  v6 = 102;
  v5 = 208;
  v7 = 254;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 22, 262, (int)&a4, (int)aUiCombatContro_40);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 22))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 22), 1);
  ((PalScript *)*((_DWORD *)this + 22))->OpenScript(aUiCombatContro_41, 0);
  a4 = 19;
  v6 = 65;
  v5 = 192;
  v7 = 238;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 24, 264, (int)&a4, (int)aUiCombatContro_43);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 24))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 24), 1);
  ((PalScript *)*((_DWORD *)this + 24))->OpenScript(aUiCombatContro_44, 0);
  a4 = 19;
  v6 = 65;
  v5 = 121;
  v7 = 167;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 25, 266, (int)&a4, (int)aUiCombatContro_47);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 25))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 25), 1);
  ((PalScript *)*((_DWORD *)this + 25))->OpenScript(aUiCombatContro_48, 0);
  a4 = 90;
  v6 = 136;
  v5 = 192;
  v7 = 238;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 26, 267, (int)&a4, (int)aUiCombatContro_49);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 26))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 26), 1);
  ((PalScript *)*((_DWORD *)this + 26))->OpenScript(aUiCombatContro_50, 0);
  a4 = 90;
  v6 = 136;
  v5 = 121;
  v7 = 167;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 27, 268, (int)&a4, (int)aUiCombatContro_51);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 27))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 27), 1);
  ((PalScript *)*((_DWORD *)this + 27))->OpenScript(aUiCombatContro_52, 0);
  a4 = 111;
  v6 = 157;
  v5 = 153;
  v7 = 199;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 23, 265, (int)&a4, (int)aUiCombatContro_45);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 23))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 23), 1);
  return ((PalScript *)*((_DWORD *)this + 23))->OpenScript(aUiCombatContro_46, 0);
}

// 0x00519A10
char CCBUI::WriteNimbusToPlayerMgr(_DWORD *a2, int a3, int a4, int a5)
{
  UIScene *v6; // eax
  int v7; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-40Ch] BYREF
  int v11; // [esp+810h] [ebp-4h]

  v6 = (UIScene *)operator new(0x158u);
  v11 = 0;
  if ( v6 )
    v6->_UIScene();
  else
    v7 = 0;
  v11 = -1;
  *a2 = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 2306),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (**)(int, int, int, CCBUI *, int, int, _DWORD))(*(_DWORD *)v7 + 28))(v7, a3, a4, this, a5, 1, 0);
  return 1;
}

// 0x00519B40
UIWnd * CCBUI::GetNimbusColor(CCBUI *Block, char a2)
{
  Block->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x00519BB0
int CCBUI::Render()
{
  this->m_childs.m_nMaxSize = 0;
  this->m_childs.m_nGrowBy = 0;
  this->m_bcreateok = 0;
  this->m_childs.m_pData = 0;
  this->m_childs.m_nSize = 0;
  this->m_bvisible = 0;
  this->m_benable = 0;
  this->m_bfocus = 0;
  return 0;
}

// 0x00519BD0
char CCBUI::CreateButton@<al>(
        int a1@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<edi>,
        int a5@<esi>,
        _DWORD *pRect,
        int parent)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v8; // esp
  UIFrameWnd *v10; // eax
  int v11; // eax
  UIWnd *v12; // ecx
  const int *v13; // ebx
  UIListBox **v14; // esi
  UIListBox *v15; // eax
  char *updated; // eax
  _DWORD *v17; // eax
  UIFrameWnd *v18; // eax
  int v19; // eax
  int id; // [esp+38h] [ebp-1014h] BYREF
  void *v23; // [esp+3Ch] [ebp-1010h]
  _BYTE pExceptionObject[1040]; // [esp+40h] [ebp-100Ch] BYREF
  char v25[1024]; // [esp+450h] [ebp-BFCh] BYREF
  char v26[1024]; // [esp+850h] [ebp-7FCh] BYREF
  char v27[1008]; // [esp+C50h] [ebp-3FCh] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v28; // [esp+1040h] [ebp-Ch]
  void *v29; // [esp+1044h] [ebp-8h]
  int v30; // [esp+1048h] [ebp-4h]

  v30 = -1;
  ExceptionList = (struct _EXCEPTION_REGISTRATION_RECORD *)NtCurrentTeb()->NtTib.ExceptionList;
  v29 = (void *)&loc_56720A;
  v28 = ExceptionList;
  v8 = (void *)alloca(4120);
  ((UIWnd *)a1)->Create(1879048193, pRect, parent);
  v10 = (UIFrameWnd *)operator new(0x98u);
  v30 = 0;
  if ( v10 )
    v10->UIFrameWnd();
  else
    v11 = 0;
  v30 = -1;
  *(_DWORD *)(a1 + 72) = v11;
  if ( !v11 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&pExceptionObject[1024])->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 2366),
      0x400u);
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *pRect = 0;
  pRect[2] = 249;
  pRect[1] = 0;
  pRect[3] = 206;
  (*(void (**)(_DWORD, int, _DWORD *, int, int, int, int, int))(**(_DWORD **)(a1 + 72) + 16))(
    *(_DWORD *)(a1 + 72),
    131,
    pRect,
    a1,
    a4,
    a5,
    a3,
    a2);
  ((UIWnd *)*(UIWnd ***)(a1 + 72))->CreateFromTemplate(aUiCombatContro_53, 0);
  v12 = (UIWnd *)*(UIWnd **)(a1 + 72);
  id = -1862270977;
  v12->SetShow(0);
  ((UIWnd *)*(UIWnd **)(a1 + 72))->GetChild((int)&id);
  ((UIFrameWnd *)*(UIFrameWnd **)(a1 + 72))->SetPosition(40, 150);
  ((UIFrameWnd *)*(UIFrameWnd **)(a1 + 72))->SetPosition(0, 0);
  (***(void (****)(_DWORD, int))(a1 + 72))(*(_DWORD *)(a1 + 72), 1);
  v13 = (const int *)&dword_570110;
  v14 = (UIListBox **)(a1 + 80);
  do
  {
    v15 = (UIListBox *)operator new(0x4B8u);
    v23 = v15;
    if ( v15 )
      updated = (char *)v15->UpdateKeyCtrl();
    else
      updated = 0;
    *v14 = (UIListBox *)updated;
    if ( !updated )
    {
      qmemcpy(
        &pExceptionObject[16],
        ((Logger *)v25)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 2390),
        0x400u);
      _CxxThrowException(&pExceptionObject[16], (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *pRect = 39;
    pRect[2] = 241;
    pRect[1] = 78;
    pRect[3] = 175;
    (*(void (**)(UIListBox *, const int, _DWORD *, int, _DWORD, int, _DWORD))((*v14)->m_fontcolor.ColorQuadFmt
                                                                                       + 28))(
      *v14,
      *v13,
      pRect,
      a1,
      0,
      1,
      0);
    (*(void (**)(UIListBox *, int))(*v14)->m_fontcolor.ColorQuadFmt)(*v14, 1);
    sub_43F670(*v14, 2, -4);
    ((UIListBox *)*v14)->SetFirstShow(aName, 150);
    ((UIListBox *)*v14)->SetFirstShow(aQuantity, 43);
    sub_43F640(*v14, 19);
    ((UIListBox *)*v14)->GetSel((int)aUiCombatContro_0, 0);
    sub_43F690(*v14, 1);
    v17 = ((UIWnd *)&(*v14)->m_childs.m_nMaxSize)->SetRect(pExceptionObject);
    * pRect = (*)*v17;
    pRect[1] = v17[1];
    pRect[2] = v17[2];
    pRect[3] = v17[3];
    ((UIListBox *)*v14)->GetLockSel((int)aUiCombatContro, pRect, 16, 16, 0);
    sub_442230(&(*v14)->m_childs.m_nMaxSize, 26, 28);
    sub_4421F0(&(*v14)->m_childs.m_nMaxSize, -5);
    sub_442200(&(*v14)->m_childs.m_nMaxSize, -2);
    ++v13;
    ++v14;
  }
  while ( (int)v13 < (int)&dword_57011C );
  ((CCBUI *)a1)->ChangeSpecStateLum();
  v18 = (UIFrameWnd *)operator new(0x98u);
  v23 = v18;
  if ( v18 )
    v18->UIFrameWnd();
  else
    v19 = 0;
  *(_DWORD *)(a1 + 76) = v19;
  if ( !v19 )
  {
    qmemcpy(v26, ((Logger *)v27)->FormatException(aCNewFailed, aDProjectPal3Co_12, 4346), sizeof(v26));
    _CxxThrowException(v26, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *pRect = 37;
  pRect[2] = 237;
  pRect[1] = 170;
  pRect[3] = 210;
  (*(void (**)(_DWORD, int, _DWORD *, int))(**(_DWORD **)(a1 + 76) + 16))(
    *(_DWORD *)(a1 + 76),
    131,
    pRect,
    a1);
  (***(void (****)(_DWORD, int))(a1 + 76))(*(_DWORD *)(a1 + 76), 1);
  ((CCBUI *)a1)->GravityDown(0);
  return 1;
}

// 0x00519F50
int CCBUI::DeleteUIObj()
{
  int result; // eax
  int *p_m_nMaxSize; // esi
  int v4; // ebx
  void *m_pData; // ecx
  int m_nSize; // ecx
  int m_bvisible; // ecx
  int m_benable; // ecx
  int m_bfocus; // ecx

  result = ((UIListBox *)this)->SetScrollPos();
  p_m_nMaxSize = (int *)&this->m_childs.m_nMaxSize;
  v4 = 3;
  do
  {
    if ( *p_m_nMaxSize )
    {
      result = (*(int (**)(int, int))(*(_DWORD *)*p_m_nMaxSize + 20))(*p_m_nMaxSize, 1);
      *p_m_nMaxSize = 0;
    }
    ++p_m_nMaxSize;
    --v4;
  }
  while ( v4 );
  m_pData = (void *)this->m_childs.m_pData;
  if ( m_pData )
  {
    result = (*(int (**)(void *, int))(*(_DWORD *)m_pData + 20))(m_pData, 1);
    this->m_childs.m_pData = 0;
  }
  m_nSize = this->m_childs.m_nSize;
  if ( m_nSize )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_nSize + 20))(m_nSize, 1);
    this->m_childs.m_nSize = 0;
  }
  m_bvisible = this->m_bvisible;
  if ( m_bvisible )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bvisible + 20))(m_bvisible, 1);
    this->m_bvisible = 0;
  }
  m_benable = this->m_benable;
  if ( m_benable )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_benable + 20))(m_benable, 1);
    this->m_benable = 0;
  }
  m_bfocus = this->m_bfocus;
  if ( m_bfocus )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)m_bfocus + 20))(m_bfocus, 1);
    this->m_bfocus = 0;
  }
  return result;
}

// 0x00519FE0
int CCBUI::AddRightControlButtonAni(int a2, unsigned int a3, int a4)
{
  char *v5; // eax
  char *Instance; // eax

  if ( a2 == 1001 )
  {
    if ( a3 < 0xB5 || a3 > 0xB7 )
      return a2->SendMessage(a3, a4);
    this->GravityDown(a3 - 181);
    Instance = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(aWa001, 1);
LABEL_11:
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3, a4);
    return a2->SendMessage(a3, a4);
  }
  if ( a2 == 1006 )
  {
    if ( a4 == -1 )
      return a2->SendMessage(a3, a4);
    goto LABEL_11;
  }
  if ( a2 == 1007 && a4 != -1 )
  {
    v5 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v5)->AudioSetPosition(aWa002, 1);
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(a3, a4);
  }
  return a2->SendMessage(a3, a4);
}

// 0x0051A090
BOOL CCBUI::AddResultWindowAni(int a2, int a3)
{
  if ( this->m_rect.top == 1
    && (g_Input.m_DIKToKEY[1] == 1 && (g_Input.m_shiftedKeyStates[268] & 0xF) == 1 || g_Input.m_DIKToKEY[5] == 1) )
  {
    ((CCBUI *)*(CCBUI **)(*(_DWORD *)(this->m_wndcolor.Green + 1160) + 8))->SetParam(128, -1);
  }
  return this->HitTest(a2, a3);
}

// 0x0051A0F0
int CCBUI::ChangeSpecStateLum()
{
  int *p_m_bvisible; // edi
  int a4; // [esp+8h] [ebp-10h] BYREF
  int v5; // [esp+Ch] [ebp-Ch]
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  p_m_bvisible = (int *)&this->m_bvisible;
  a4 = 40;
  v6 = 72;
  v5 = 27;
  v7 = 59;
  this->LineMove(&this->m_bvisible, 181, (int)&a4, (int)aUiCombatContro_1);
  (**(void (***)(int, int))*p_m_bvisible)(*p_m_bvisible, 1);
  a4 = 72;
  v6 = 104;
  v5 = 27;
  v7 = 59;
  this->LineMove(&this->m_benable, 182, (int)&a4, (int)aUiCombatContro_2);
  (**(void (***)(int, int))this->m_benable)(this->m_benable, 1);
  a4 = 104;
  v6 = 136;
  v5 = 27;
  v7 = 59;
  this->LineMove(&this->m_bfocus, 183, (int)&a4, (int)aUiCombatContro_3);
  return (**(int (***)(int, int))this->m_bfocus)(this->m_bfocus, 1);
}

// 0x0051A1D0
char CCBUI::LineMove(_DWORD *a2, int a3, int a4, int a5)
{
  UIStatic *v6; // eax
  int v7; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-40Ch] BYREF
  int v11; // [esp+810h] [ebp-4h]

  v6 = (UIStatic *)operator new(0xF8u);
  v11 = 0;
  if ( v6 )
    v6->UIStatic();
  else
    v7 = 0;
  v11 = -1;
  *a2 = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_12, 2575),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (**)(int, int, int, CCBUI *, int, _DWORD))(*(_DWORD *)v7 + 28))(v7, a3, a4, this, a5, 0);
  return 1;
}

// 0x0051A2B0
int CCBUI::GravityDown(int a2)
{
  int v3; // ebp
  int *p_m_nMaxSize; // edi
  int m_bvisible; // eax
  int m_benable; // eax
  int m_bfocus; // eax
  int v8; // eax
  int result; // eax

  v3 = 3;
  p_m_nMaxSize = (int *)&this->m_childs.m_nMaxSize;
  do
  {
    (**(void (***)(int, _DWORD))*p_m_nMaxSize)(*p_m_nMaxSize, 0);
    m_bvisible = this->m_bvisible;
    ++p_m_nMaxSize;
    --v3;
    *(_DWORD *)(m_bvisible + 80) = 0;
    *(_BYTE *)(m_bvisible + 68) = 0;
    m_benable = this->m_benable;
    *(_DWORD *)(m_benable + 80) = 0;
    *(_BYTE *)(m_benable + 68) = 0;
    m_bfocus = this->m_bfocus;
    *(_DWORD *)(m_bfocus + 80) = 0;
    *(_BYTE *)(m_bfocus + 68) = 0;
  }
  while ( v3 );
  switch ( a2 )
  {
    case 0:
      v8 = this->m_bvisible;
      goto LABEL_9;
    case 1:
      v8 = this->m_benable;
      goto LABEL_9;
    case 2:
      v8 = this->m_bfocus;
LABEL_9:
      *(_DWORD *)(v8 + 80) = 1;
      *(_BYTE *)(v8 + 68) = 1;
      break;
  }
  ((UIWnd *)this->m_childs.m_pData)->SetEnable(g_SceneMgr.m_szUIString, 0);
  ((UIWnd *)this->m_childs.m_nSize)->SetEnable(g_SceneMgr.m_szUIString, 0);
  result = (***((int (****)(_DWORD, int))&this->m_childs.m_nMaxSize + a2))(
             *(&this->m_childs.m_nMaxSize + a2),
             1);
  this->m_pbktex = (gbTexture *)a2;
  return result;
}

// 0x0051A340
_DWORD * CCBUI::ChangeNumTxt()
{
  ((UIListBox *)this)->UIListBox();
  this->m_fontcolor.ColorQuadFmt = (int)&off_570500;
  sub_51A400(this);
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0051A390
UIWnd * CCBUI::DoTask(CCBUI *Block, char a2)
{
  Block->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0051A430
char CCBUI::AddTask(_DWORD *pRect, int parent)
{
  UIFrameWnd *v4; // eax
  void *v5; // eax
  UIWnd *m_pData; // ecx
  const int *v7; // ebp
  int *p_m_nSize; // esi
  UIListBox *v9; // eax
  char *updated; // eax
  _DWORD *v11; // eax
  int id; // [esp+24h] [ebp-824h] BYREF
  void *v14; // [esp+28h] [ebp-820h]
  _DWORD a2[4]; // [esp+2Ch] [ebp-81Ch] BYREF
  char pExceptionObject[1024]; // [esp+3Ch] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+43Ch] [ebp-40Ch] BYREF
  int v18; // [esp+844h] [ebp-4h]

  this->Create(1879048194, pRect, parent);
  v4 = (UIFrameWnd *)operator new(0x98u);
  v14 = v4;
  v18 = 0;
  if ( v4 )
    v4->UIFrameWnd();
  else
    v5 = 0;
  v18 = -1;
  this->m_childs.m_pData = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 2678),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *pRect = 0;
  pRect[2] = 249;
  pRect[1] = 0;
  pRect[3] = 206;
  (*(void (**)(void *, int, _DWORD *, CCBUI *))(*(_DWORD *)this->m_childs.m_pData + 16))(
    this->m_childs.m_pData,
    150,
    pRect,
    this);
  ((UIWnd *)this->m_childs.m_pData)->CreateFromTemplate(aUiCombatContro_54, 0);
  (**(void (***)(void *, int))this->m_childs.m_pData)(this->m_childs.m_pData, 1);
  m_pData = (UIWnd *)this->m_childs.m_pData;
  id = -1879048192;
  m_pData->SetShow(0);
  ((UIWnd *)this->m_childs.m_pData)->GetChild((int)&id);
  ((UIFrameWnd *)this->m_childs.m_pData)->SetPosition(40, 170);
  v7 = (const int *)&dword_57011C;
  p_m_nSize = (int *)&this->m_childs.m_nSize;
  do
  {
    v9 = (UIListBox *)operator new(0x4B8u);
    v14 = v9;
    v18 = 1;
    if ( v9 )
      updated = (char *)v9->UpdateKeyCtrl();
    else
      updated = 0;
    v18 = -1;
    *p_m_nSize = (int)updated;
    if ( !updated )
    {
      qmemcpy(
        pExceptionObject,
        ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_12, 2700),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *pRect = 39;
    pRect[2] = 241;
    pRect[1] = 78;
    pRect[3] = 175;
    (*(void (**)(int, const int, _DWORD *, CCBUI *, _DWORD, int, _DWORD))(*(_DWORD *)*p_m_nSize + 28))(
      *p_m_nSize,
      *v7,
      pRect,
      this,
      0,
      1,
      0);
    (**(void (***)(int, _DWORD))*p_m_nSize)(*p_m_nSize, 0);
    sub_43F670((_DWORD *)*p_m_nSize, 2, -4);
    ((UIListBox *)*p_m_nSize)->SetFirstShow(aName, 96);
    ((UIListBox *)*p_m_nSize)->SetFirstShow(aCost, 37);
    ((UIListBox *)*p_m_nSize)->SetFirstShow(aLevelcost, 50);
    sub_43F640((_DWORD *)*p_m_nSize, 19);
    ((UIListBox *)*p_m_nSize)->GetSel((int)aUiCombatContro_0, 0);
    sub_43F690((_DWORD *)*p_m_nSize, 1);
    v11 = ((UIWnd *)(*p_m_nSize + 80))->SetRect(a2);
    * pRect = (*)*v11;
    pRect[1] = v11[1];
    pRect[2] = v11[2];
    pRect[3] = v11[3];
    ((UIListBox *)*p_m_nSize)->GetLockSel((int)aUiCombatContro, pRect, 16, 16, 0);
    sub_442230((_DWORD *)(*p_m_nSize + 80), 26, 30);
    sub_4421F0((_DWORD *)(*p_m_nSize + 80), -5);
    sub_442200((_DWORD *)(*p_m_nSize + 80), -2);
    ++v7;
    ++p_m_nSize;
  }
  while ( (int)v7 < (int)&dword_570134 );
  ((CCBControlWindow *)this)->CCBControlWindow();
  ((CCBControlWindow *)this)->HandleInput(0);
  return 1;
}
