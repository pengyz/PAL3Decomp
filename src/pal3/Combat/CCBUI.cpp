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

  LOBYTE(result) = this->UIFrameWnd[37];
  if ( !(_BYTE)result )
  {
    this->UIFrameWnd[37] = 1;
    return sub_4DC650(this, (int)sub_4DF2F0, 0, 0, 0, 0, 0, 0, -1, 0, 0);
  }
  return result;
}

// 0x004DC5C0
int CCBUI::SetParam(int a2, int a3)
{
  int result; // eax
  int v4; // [esp+10h] [ebp+Ch]

  result = a2;
  *(_DWORD *)&this->UIFrameWnd[44] = a3;
  this->UIFrameWnd[52] = 1;
  *(_DWORD *)&this->UIFrameWnd[40] = a2;
  *(_DWORD *)&this->UIFrameWnd[48] = v4;
  switch ( a2 )
  {
    case 259:
    case 260:
    case 261:
    case 262:
    case 265:
    case 267:
      *(_DWORD *)&this->UIFrameWnd[40] = a2;
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

  ((CCBSystem *)*(_DWORD *)this->UIFrameWnd)->ProcAI(flt_17A95F8);
  if ( *(_BYTE *)(*(_DWORD *)this->UIFrameWnd + 132) != byte_17A9924 )
    ((CCBSystem *)*(CCBSystem **)this->UIFrameWnd)->SetRenderFlag(byte_17A9924);
  *(_BYTE *)(*(_DWORD *)this->UIFrameWnd + 134) = byte_5D87F0;
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
    ((CCBStageScene *)*(_DWORD **)(*(_DWORD *)(*(_DWORD *)this->UIFrameWnd + 20) + 20))->Update();
    ((CCBStageScene *)*(float **)(*(_DWORD *)(*(_DWORD *)this->UIFrameWnd + 20) + 20))->ShowRoleIndex();
    result = byte_5D8864->CreateObj(0, 0x40u);
    byte_17A9930 = 0;
  }
  if ( byte_17A9932 )
    byte_17A9932 = 0;
  if ( byte_17A9931 )
    byte_17A9931 = 0;
  if ( byte_17A9933 )
  {
    v3 = sub_504240(*(_DWORD **)(*(_DWORD *)(*(_DWORD *)this->UIFrameWnd + 20) + 12));
    sprintf(Buffer, &byte_5D8848, v3);
    result = Buffer->CreateObj(0, 0x40u);
    byte_17A9933 = 0;
  }
  return result;
}

// 0x004E0740
char CCBUI::UpdateDisplay()
{
  int inited; // eax
  int v3; // edi
  int i; // esi
  void *v5; // ecx
  int v6; // edi
  int v7; // esi
  void *v8; // ecx
  HWND DlgItem; // eax

  LOBYTE(inited) = byte_17A9925;
  if ( byte_17A9925 )
  {
    v3 = 0;
    for ( i = 0; i < 4460; i += 892 )
    {
      inited = *(_DWORD *)this->UIFrameWnd;
      v5 = (void *)*(void **)(*(_DWORD *)this->UIFrameWnd + 16);
      if ( *((_BYTE *)v5 + i + 577) )
      {
        inited = v5->InitUI(v3);
        *(_BYTE *)(inited + 837) = 0;
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
      v8 = (void *)*(void **)(*(_DWORD *)this->UIFrameWnd + 16);
      if ( *((_BYTE *)v8 + v7 + 577) )
      {
        inited = v8->InitUI(v6);
        if ( !*(_BYTE *)(inited + 837) )
          break;
      }
      v7 += 892;
      ++v6;
      if ( v7 >= 4460 )
      {
        if ( !byte_17A9924 )
        {
          byte_17A9924 = 1;
          sprintf(byte_17A94E4, "%s", byte_5D8884);
          DlgItem = GetDlgItem(MEMORY[0xBFDA50], 1004);
          SendMessageA(DlgItem, 0xCu, 0, (LPARAM)byte_17A94E4);
          LOBYTE(inited) = ((CCBSystem *)*(_BYTE **)this->UIFrameWnd)->ProcFlee(byte_17A9924);
        }
        return inited;
      }
    }
  }
  return inited;
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
    result = sub_4E30E0(this);
  }
  if ( byte_17A9936 )
  {
    byte_17A9936 = 0;
    result = sub_4E3780(this);
  }
  if ( byte_17A9938 )
  {
    byte_17A9938 = 0;
    result = sub_4E3D90();
  }
  if ( byte_17A9937 )
  {
    byte_17A9937 = 0;
    result = sub_4E3A20();
  }
  if ( byte_17A9944 )
  {
    byte_17A9944 = 0;
    result = sub_4E40B0(this);
  }
  if ( byte_17A9945 )
  {
    byte_17A9945 = 0;
    result = sub_4E4570(this);
  }
  if ( byte_17A9946 )
  {
    byte_17A9946 = 0;
    result = sub_4E4A80();
  }
  if ( byte_17A9948 )
  {
    byte_17A9948 = 0;
    result = sub_4E4D70();
  }
  if ( byte_17A9947 )
  {
    byte_17A9947 = 0;
    result = sub_4E4D50(this);
  }
  if ( byte_17A994A )
  {
    byte_17A994A = 0;
    result = sub_4E50B0();
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
    result = sub_4E5B20((int *)this->UIFrameWnd);
  }
  if ( byte_17A994E )
  {
    byte_17A994E = 0;
    return sub_4E5E00((int *)this->UIFrameWnd);
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
  v2 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)this->UIFrameWnd + 20) + 16);
  if ( dword_17A990C == 4 )
  {
    DlgItem = GetDlgItem(MEMORY[0xBFDA54], 1201);
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

  v2 = (UIFrameWnd *)((operator *)0x98u)->new();
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
      v7 = (UIFrameWnd *)((operator *)0x98u)->new();
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
        return 1;
    }
  }
  return 0;
}

// 0x005177B0
char CCBUI::Reset()
{
  int v2; // eax
  CCBUI **v3; // eax
  int v4; // eax
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
  v2 = ((operator *)0x9Cu)->new();
  v16 = (UIFrameWnd *)v2;
  v19 = 0;
  if ( v2 )
    v3 = (CCBUI **)sub_442D00(v2);
  else
    v3 = 0;
  *((_DWORD *)this + 268) = v3;
  v4 = ((operator *)0x9Cu)->new();
  v16 = (UIFrameWnd *)v4;
  v19 = 1;
  if ( v4 )
    v5 = (CCBUI **)sub_442D00(v4);
  else
    v5 = 0;
  *((_DWORD *)this + 269) = v5;
  v6 = (UIFrameWnd *)((operator *)0x98u)->new();
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
  UIProgressBar *v4; // ecx
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
    v4 = (UIProgressBar *)*v2;
    v5 = 2;
    v7 = 251;
    v6 = 278;
    v8 = 484;
    ((int)v4)->AddTask(&v5, (int)this);
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
  UIProgressBar *v4; // ecx
  int v5; // [esp+8h] [ebp-10h] BYREF
  int v6; // [esp+Ch] [ebp-Ch]
  int v7; // [esp+10h] [ebp-8h]
  int v8; // [esp+14h] [ebp-4h]

  p_m_pRoleStateSword = &this->m_pRoleStateSword;
  result = ((CCBLineupWindow *)&this->m_pRoleStateSword)->CCBLineupWindow();
  if ( result )
  {
    v6 = 0;
    v7 = 0;
    v4 = (UIProgressBar *)*p_m_pRoleStateSword;
    v5 = 14;
    v7 = 172;
    v6 = 316;
    v8 = 474;
    ((int)v4)->Create(&v5, (int)this);
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
  UIStatic *v4; // ecx
  int v6; // [esp+Ch] [ebp-10h] BYREF
  int v7; // [esp+10h] [ebp-Ch]
  int v8; // [esp+14h] [ebp-8h]
  int v9; // [esp+18h] [ebp-4h]

  v1 = 0;
  v7 = 0;
  v8 = 0;
  v6 = 0;
  v9 = 0;
  for ( i = &this->m_pDialogBack; i->Create(); ++i )
  {
    v8 = v1 + 256;
    v4 = (UIStatic *)*i;
    v6 = v1;
    v7 = 0;
    v9 = 256;
    ((int)v4)->Create(&v6, (int)this);
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
char CCBUI::CreateParaWindow(int _this)
{
  void (***v2)(_DWORD, _DWORD); // ecx
  void (***v3)(_DWORD, _DWORD); // ecx
  void (***v4)(_DWORD, _DWORD); // ecx
  void (***v5)(_DWORD, _DWORD); // ecx
  void (***v6)(_DWORD, _DWORD); // ecx
  void (***v7)(_DWORD, _DWORD); // ecx
  void (***v8)(_DWORD, _DWORD); // ecx
  void (***v9)(_DWORD, _DWORD); // ecx
  void (***v10)(_DWORD, _DWORD); // ecx
  void (***v11)(_DWORD, _DWORD); // ecx
  int v12; // ecx
  int v13; // edi
  _DWORD *v14; // ebx

  *(_DWORD *)(this + 1164) = **(_DWORD **)(this + 1160);
  v2 = *(void (****)(_DWORD, _DWORD))(this + 1012);
  if ( v2 )
    (**v2)(v2, 0);
  v3 = *(void (****)(_DWORD, _DWORD))(this + 1016);
  if ( v3 )
    (**v3)(v3, 0);
  v4 = *(void (****)(_DWORD, _DWORD))(this + 1084);
  if ( v4 )
    (**v4)(v4, 0);
  v5 = *(void (****)(_DWORD, _DWORD))(this + 1088);
  if ( v5 )
    (**v5)(v5, 0);
  v6 = *(void (****)(_DWORD, _DWORD))(this + 1092);
  if ( v6 )
    (**v6)(v6, 0);
  v7 = *(void (****)(_DWORD, _DWORD))(this + 1096);
  if ( v7 )
    (**v7)(v7, 0);
  v8 = *(void (****)(_DWORD, _DWORD))(this + 1100);
  if ( v8 )
    (**v8)(v8, 0);
  v9 = *(void (****)(_DWORD, _DWORD))(this + 1104);
  if ( v9 )
    (**v9)(v9, 0);
  v10 = *(void (****)(_DWORD, _DWORD))(this + 1108);
  if ( v10 )
    (**v10)(v10, 0);
  v11 = *(void (****)(_DWORD, _DWORD))(this + 1112);
  if ( v11 )
    (**v11)(v11, 0);
  (***(void (****)(_DWORD, _DWORD))(this + 1120))(*(_DWORD *)(this + 1120), 0);
  (***(void (****)(_DWORD, _DWORD))(this + 1124))(*(_DWORD *)(this + 1124), 0);
  (***(void (****)(_DWORD, _DWORD))(this + 1128))(*(_DWORD *)(this + 1128), 0);
  (***(void (****)(_DWORD, _DWORD))(this + 1132))(*(_DWORD *)(this + 1132), 0);
  (***(void (****)(_DWORD, _DWORD))(this + 1136))(*(_DWORD *)(this + 1136), 0);
  (***(void (****)(_DWORD, _DWORD))(this + 1140))(*(_DWORD *)(this + 1140), 0);
  (***(void (****)(_DWORD, _DWORD))(this + 1080))(*(_DWORD *)(this + 1080), 0);
  *(_DWORD *)(*(_DWORD *)(this + 1072) + 152) = 0;
  (***(void (****)(_DWORD, _DWORD))(this + 1072))(*(_DWORD *)(this + 1072), 0);
  *(_DWORD *)(*(_DWORD *)(this + 1076) + 152) = 0;
  (***(void (****)(_DWORD, _DWORD))(this + 1076))(*(_DWORD *)(this + 1076), 0);
  ((CCBUI *)0)->CreateResultWindow();
  v12 = *(_DWORD *)(this + 1068);
  if ( v12 )
  {
    sub_43FE90(v12);
    ((UIWnd *)*(_DWORD *)(this + 1068))->FindChild(50.0);
    ((UIWnd *)*(_DWORD *)(this + 1068))->FindChildByName(0.0);
  }
  v13 = 0;
  v14 = (_DWORD *)(this + 1144);
  do
  {
    *(_DWORD *)(*v14 + 172) = v13;
    (**(void (***)(_DWORD, _DWORD))*v14)(*v14, 0);
    ++v13;
    ++v14;
  }
  while ( v13 < 4 );
  memset((void *)(this + 1168), 0, 0x5A0u);
  *(_DWORD *)(this + 2608) = 0;
  *(_DWORD *)(this + 2612) = 0;
  *(_DWORD *)(this + 2624) = 0;
  *(_DWORD *)(this + 2628) = -1;
  *(_DWORD *)(this + 2616) = 0;
  *(_DWORD *)(this + 2620) = -1;
  return 1;
}

// 0x005183C0
int ( *** CCBUI::CreateMagicWindow())(_DWORD, _DWORD)
{
  void (***v2)(_DWORD, _DWORD); // ecx
  void (***v3)(_DWORD, _DWORD); // ecx
  void (***v4)(_DWORD, _DWORD); // ecx
  void (***v5)(_DWORD, _DWORD); // ecx
  void (***v6)(_DWORD, _DWORD); // ecx
  void (***v7)(_DWORD, _DWORD); // ecx
  void (***v8)(_DWORD, _DWORD); // ecx
  void (***v9)(_DWORD, _DWORD); // ecx
  void (***v10)(_DWORD, _DWORD); // ecx
  void (***v11)(_DWORD, _DWORD); // ecx
  void (***v12)(_DWORD, _DWORD); // ecx
  void (***v13)(_DWORD, _DWORD); // ecx
  int v14; // edi
  _DWORD *v15; // esi
  int (***result)(_DWORD, _DWORD); // eax

  v2 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 253);
  if ( v2 )
    (**v2)(v2, 0);
  v3 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 254);
  if ( v3 )
    (**v3)(v3, 0);
  v4 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 270);
  if ( v4 )
    (**v4)(v4, 0);
  v5 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 279);
  if ( v5 )
    (**v5)(v5, 0);
  v6 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 280);
  if ( v6 )
    (**v6)(v6, 0);
  v7 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 281);
  if ( v7 )
    (**v7)(v7, 0);
  v8 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 282);
  if ( v8 )
    (**v8)(v8, 0);
  v9 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 283);
  if ( v9 )
    (**v9)(v9, 0);
  v10 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 284);
  if ( v10 )
    (**v10)(v10, 0);
  v11 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 285);
  if ( v11 )
    (**v11)(v11, 0);
  v12 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 268);
  if ( v12 )
    (**v12)(v12, 0);
  v13 = (void (***)(_DWORD, _DWORD))*((_DWORD *)this + 269);
  if ( v13 )
    (**v13)(v13, 0);
  ((CCBUI *)0)->CreateResultWindow();
  v14 = 0;
  v15 = (_DWORD *)this + 286;
  do
  {
    result = (int (***)(_DWORD, _DWORD))*v15;
    if ( *v15 )
    {
      result[43] = (int (**)(_DWORD, _DWORD))v14;
      result = (int (***)(_DWORD, _DWORD))(**(int (***)(_DWORD, _DWORD))*v15)(*v15, 0);
    }
    ++v14;
    ++v15;
  }
  while ( v14 < 4 );
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
char CCBUI::CreateResultWindow(int _this, char a2)
{
  int i; // edi
  char result; // al
  int v5; // ebx
  int v6; // edi
  int v7; // ebx
  _DWORD *v8; // edi
  int v9; // ebx
  int v10; // esi
  int v11; // edi

  if ( a2 )
  {
    for ( i = 0; i < 5; ++i )
    {
      result = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 1160) + 16) + 892 * i + 577);
      if ( result )
      {
        (***(void (****)(_DWORD, int))(this + 4 * i + 136))(*(_DWORD *)(this + 4 * i + 136), 1);
        (***(void (****)(_DWORD, int))(this + 4 * i + 156))(*(_DWORD *)(this + 4 * i + 156), 1);
        v5 = *(unsigned __int8 *)(((CCBRoleState *)*(void **)(*(_DWORD *)(this + 1160) + 16))->InitUI(i) + 24);
        (***(void (****)(_DWORD, int))(this + 4 * v5 + 1020))(*(_DWORD *)(this + 4 * v5 + 1020), 1);
        (***(void (****)(_DWORD, int))(this + 4 * v5 + 1036))(*(_DWORD *)(this + 4 * v5 + 1036), 1);
        (***(void (****)(_DWORD, int))(this + 4 * v5 + 1052))(*(_DWORD *)(this + 4 * v5 + 1052), 1);
        result = (***(int (****)(_DWORD, int))(this + 4 * v5 + 120))(*(_DWORD *)(this + 4 * v5 + 120), 1);
        if ( !i )
          result = (***(int (****)(_DWORD, int))(this + 1068))(*(_DWORD *)(this + 1068), 1);
      }
    }
  }
  else
  {
    (***(void (****)(_DWORD, _DWORD))(this + 1068))(*(_DWORD *)(this + 1068), 0);
    v6 = this + 1036;
    v7 = 4;
    do
    {
      (***(void (****)(_DWORD, _DWORD))(v6 - 16))(*(_DWORD *)(v6 - 16), 0);
      (***(void (****)(_DWORD, _DWORD))v6)(*(_DWORD *)v6, 0);
      (***(void (****)(_DWORD, _DWORD))(v6 + 16))(*(_DWORD *)(v6 + 16), 0);
      (***(void (****)(_DWORD, _DWORD))(v6 - 916))(*(_DWORD *)(v6 - 916), 0);
      v6 += 4;
      --v7;
    }
    while ( v7 );
    v8 = (_DWORD *)(this + 156);
    v9 = 5;
    do
    {
      (**(void (***)(_DWORD, _DWORD))*(v8 - 5))(*(v8 - 5), 0);
      (**(void (***)(_DWORD, _DWORD))*v8)(*v8, 0);
      ++v8;
      --v9;
    }
    while ( v9 );
    v10 = this + 220;
    v11 = 11;
    do
    {
      (***(void (****)(_DWORD, _DWORD))(v10 - 44))(*(_DWORD *)(v10 - 44), 0);
      (***(void (****)(_DWORD, _DWORD))v10)(*(_DWORD *)v10, 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 44))(*(_DWORD *)(v10 + 44), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 88))(*(_DWORD *)(v10 + 88), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 220))(*(_DWORD *)(v10 + 220), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 264))(*(_DWORD *)(v10 + 264), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 132))(*(_DWORD *)(v10 + 132), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 176))(*(_DWORD *)(v10 + 176), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 308))(*(_DWORD *)(v10 + 308), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 352))(*(_DWORD *)(v10 + 352), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 396))(*(_DWORD *)(v10 + 396), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 440))(*(_DWORD *)(v10 + 440), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 484))(*(_DWORD *)(v10 + 484), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 528))(*(_DWORD *)(v10 + 528), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 572))(*(_DWORD *)(v10 + 572), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 616))(*(_DWORD *)(v10 + 616), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 660))(*(_DWORD *)(v10 + 660), 0);
      (***(void (****)(_DWORD, _DWORD))(v10 + 704))(*(_DWORD *)(v10 + 704), 0);
      result = (***(int (****)(_DWORD, _DWORD))(v10 + 748))(*(_DWORD *)(v10 + 748), 0);
      v10 += 4;
      --v11;
    }
    while ( v11 );
  }
  return result;
}

// 0x00518D40
int CCBUI::CreateFiveNimbus(int _this, char a2)
{
  int v3; // ebx
  int v4; // ebp
  int i; // esi

  if ( !a2 )
    return (***(int (****)(_DWORD, _DWORD))(this + 1136))(*(_DWORD *)(this + 1136), 0);
  v3 = 0;
  v4 = 0;
  for ( i = 96; i < 116; i += 4 )
  {
    if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 1160) + 16) + v4 + 577) )
    {
      (***(void (****)(_DWORD, int))(i + *(_DWORD *)(this + 1136)))(
        *(_DWORD *)(i + *(_DWORD *)(this + 1136)),
        1);
      *(_DWORD *)(i + *(_DWORD *)(this + 1136) - 24) = *(_DWORD *)(((CCBRoleState *)*(void **)(*(_DWORD *)(this + 1160) + 16))->InitUI(v3)
                                                                 + 584);
      ((UIWnd *)*(_DWORD **)(i + *(_DWORD *)(this + 1136)))->ScreenToClient(dword_57024C[*(_DWORD *)(i + *(_DWORD *)(this + 1136) - 24)] + 9, dword_570268[*(_DWORD *)(i + *(_DWORD *)(this + 1136) - 24)] + 232);
    }
    else
    {
      (***(void (****)(_DWORD, _DWORD))(*(_DWORD *)(this + 1136) + i))(
        *(_DWORD *)(*(_DWORD *)(this + 1136) + i),
        0);
    }
    ++v3;
    v4 += 892;
  }
  return (***(int (****)(_DWORD, int))(this + 1136))(*(_DWORD *)(this + 1136), 1);
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
  ((UIWnd *)Block)->~UIWnd();
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
char CCBUI::CreateImbibeNimbus(int _this, _DWORD *pRect, int parent)
{
  UIFrameWnd *v4; // eax
  int v5; // eax
  char pExceptionObject[1024]; // [esp+Ch] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+40Ch] [ebp-40Ch] BYREF
  int v9; // [esp+814h] [ebp-4h]

  ((UIWnd *)this)->Create(1879048193, pRect, parent);
  v4 = (UIFrameWnd *)((operator *)0x98u)->new();
  v9 = 0;
  if ( v4 )
    v4->UIFrameWnd();
  else
    v5 = 0;
  v9 = -1;
  *(_DWORD *)(this + 72) = v5;
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
  (*(void (**)(_DWORD, int, _DWORD *, int))(**(_DWORD **)(this + 72) + 16))(
    *(_DWORD *)(this + 72),
    256,
    pRect,
    this);
  ((UIWnd *)*(UIWnd ***)(this + 72))->CreateFromTemplate(aUiCombatContro_33, 0);
  (***(void (****)(_DWORD, int))(this + 72))(*(_DWORD *)(this + 72), 1);
  ((CCBUI ***)this)->SetNimbusToNimbusControl();
  return 1;
}

// 0x00519510
int CCBUI::ConfigImbibeNimbus(int _this)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  result = ((gbRefObject **)this)->SetScrollPos();
  v3 = *(_DWORD *)(this + 72);
  if ( v3 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  v4 = *(_DWORD *)(this + 76);
  if ( v4 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *(_DWORD *)(this + 76) = 0;
  }
  v5 = *(_DWORD *)(this + 80);
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 80) = 0;
  }
  v6 = *(_DWORD *)(this + 84);
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)(this + 84) = 0;
  }
  v7 = *(_DWORD *)(this + 88);
  if ( v7 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 88) = 0;
  }
  v8 = *(_DWORD *)(this + 92);
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 92) = 0;
  }
  v9 = *(_DWORD *)(this + 96);
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 96) = 0;
  }
  v10 = *(_DWORD *)(this + 100);
  if ( v10 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)(this + 100) = 0;
  }
  v11 = *(_DWORD *)(this + 104);
  if ( v11 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
    *(_DWORD *)(this + 104) = 0;
  }
  v12 = *(_DWORD *)(this + 108);
  if ( v12 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
    *(_DWORD *)(this + 108) = 0;
  }
  v13 = *(_DWORD *)(this + 112);
  if ( v13 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
    *(_DWORD *)(this + 112) = 0;
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
  ((PalScript **)*((_DWORD *)this + 19))->OpenScript(aUiCombatContro_35, 0);
  a4 = 57;
  v6 = 103;
  v5 = 97;
  v7 = 143;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 20, 260, (int)&a4, (int)aUiCombatContro_36);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 20))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 20), 1);
  ((PalScript **)*((_DWORD *)this + 20))->OpenScript(aUiCombatContro_37, 0);
  a4 = 2;
  v6 = 48;
  v5 = 153;
  v7 = 199;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 21, 261, (int)&a4, (int)aUiCombatContro_38);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 21))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 21), 1);
  ((PalScript **)*((_DWORD *)this + 21))->OpenScript(aUiCombatContro_39, 0);
  a4 = 56;
  v6 = 102;
  v5 = 208;
  v7 = 254;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 22, 262, (int)&a4, (int)aUiCombatContro_40);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 22))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 22), 1);
  ((PalScript **)*((_DWORD *)this + 22))->OpenScript(aUiCombatContro_41, 0);
  a4 = 19;
  v6 = 65;
  v5 = 192;
  v7 = 238;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 24, 264, (int)&a4, (int)aUiCombatContro_43);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 24))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 24), 1);
  ((PalScript **)*((_DWORD *)this + 24))->OpenScript(aUiCombatContro_44, 0);
  a4 = 19;
  v6 = 65;
  v5 = 121;
  v7 = 167;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 25, 266, (int)&a4, (int)aUiCombatContro_47);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 25))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 25), 1);
  ((PalScript **)*((_DWORD *)this + 25))->OpenScript(aUiCombatContro_48, 0);
  a4 = 90;
  v6 = 136;
  v5 = 192;
  v7 = 238;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 26, 267, (int)&a4, (int)aUiCombatContro_49);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 26))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 26), 1);
  ((PalScript **)*((_DWORD *)this + 26))->OpenScript(aUiCombatContro_50, 0);
  a4 = 90;
  v6 = 136;
  v5 = 121;
  v7 = 167;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 27, 268, (int)&a4, (int)aUiCombatContro_51);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 27))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 27), 1);
  ((PalScript **)*((_DWORD *)this + 27))->OpenScript(aUiCombatContro_52, 0);
  a4 = 111;
  v6 = 157;
  v5 = 153;
  v7 = 199;
  ((CCBUI *)this)->WriteNimbusToPlayerMgr(this + 23, 265, (int)&a4, (int)aUiCombatContro_45);
  ((void (*)(_DWORD, int))(**((_DWORD *)this + 23))->m_fontcolor.ColorQuadFmt)(*((_DWORD *)this + 23), 1);
  return ((PalScript **)*((_DWORD *)this + 23))->OpenScript(aUiCombatContro_46, 0);
}

// 0x00519A10
char CCBUI::WriteNimbusToPlayerMgr(_DWORD *a2, int a3, int a4, int a5)
{
  _DWORD *v6; // eax
  int v7; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-40Ch] BYREF
  int v11; // [esp+810h] [ebp-4h]

  v6 = (_DWORD *)((operator *)0x158u)->new();
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
  ((UIWnd *)Block)->~UIWnd();
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
        _DWORD *a6,
        int a7)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v8; // esp
  _BYTE *v10; // eax
  int v11; // eax
  _DWORD *v12; // ecx
  int *v13; // ebx
  char **v14; // esi
  char *v15; // eax
  char *v16; // eax
  _DWORD *v17; // eax
  char *v18; // eax
  int v19; // eax
  int v22; // [esp+38h] [ebp-1014h] BYREF
  char *v23; // [esp+3Ch] [ebp-1010h]
  _BYTE pExceptionObject[1040]; // [esp+40h] [ebp-100Ch] BYREF
  char v25; // [esp+450h] [ebp-BFCh] BYREF
  char v26[1024]; // [esp+850h] [ebp-7FCh] BYREF
  char v27; // [esp+C50h] [ebp-3FCh] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v28; // [esp+1040h] [ebp-Ch]
  void *v29; // [esp+1044h] [ebp-8h]
  int v30; // [esp+1048h] [ebp-4h]

  v30 = -1;
  ExceptionList = (struct _EXCEPTION_REGISTRATION_RECORD *)NtCurrentTeb()->NtTib.ExceptionList;
  v29 = (void *)&loc_56720A;
  v28 = ExceptionList;
  v8 = (void *)alloca(4120);
  ((_DWORD *)a1)->Create(1879048193, a6, a7);
  v10 = ((operator *)0x98u)->new();
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
      (const void *)((char)&pExceptionObject[1024])->FormatException((int)aCNewFailed_0, (int)aDProjectPal3Co_12, 2366),
      0x400u);
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *a6 = 0;
  a6[2] = 249;
  a6[1] = 0;
  a6[3] = 206;
  (*(void (**)(_DWORD, int, _DWORD *, int, int, int, int, int))(**(_DWORD **)(a1 + 72) + 16))(
    *(_DWORD *)(a1 + 72),
    131,
    a6,
    a1,
    a4,
    a5,
    a3,
    a2);
  ((UIWnd *)*(gbRefObject ***)(a1 + 72))->CreateFromTemplate(aUiCombatContro_53, 0);
  v12 = (_DWORD *)*(_DWORD **)(a1 + 72);
  v22 = -1862270977;
  v12->SetShow(0);
  ((UIWnd *)*(_DWORD **)(a1 + 72))->GetChild(&v22);
  ((UIFrameWnd *)*(_DWORD **)(a1 + 72))->SetPosition(40, 150);
  ((UIFrameWnd *)*(_DWORD **)(a1 + 72))->SetPosition(0, 0);
  (***(void (****)(_DWORD, int))(a1 + 72))(*(_DWORD *)(a1 + 72), 1);
  v13 = (int *)&dword_570110;
  v14 = (char **)(a1 + 80);
  do
  {
    v15 = (char *)((operator *)0x4B8u)->new();
    v23 = v15;
    if ( v15 )
      v16 = (char *)v15->UpdateKeyCtrl();
    else
      v16 = 0;
    *v14 = v16;
    if ( !v16 )
    {
      qmemcpy(
        &pExceptionObject[16],
        (const void *)((char)&v25)->FormatException((int)aCNewFailed_0, (int)aDProjectPal3Co_12, 2390),
        0x400u);
      _CxxThrowException(&pExceptionObject[16], (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *a6 = 39;
    a6[2] = 241;
    a6[1] = 78;
    a6[3] = 175;
    (*(void (**)(char *, int, _DWORD *, int, _DWORD, int, _DWORD))(*(_DWORD *)*v14 + 28))(
      *v14,
      *v13,
      a6,
      a1,
      0,
      1,
      0);
    (**(void (***)(char *, int))*v14)(*v14, 1);
    sub_43F670(*v14, 2, -4);
    ((UIListBox *)*v14)->SetFirstShow(aName, 150);
    ((UIListBox *)*v14)->SetFirstShow(aQuantity, 43);
    sub_43F640(*v14, 19);
    ((UIListBox *)*v14)->GetSel((int)aUiCombatContro_0, 0);
    sub_43F690(*v14, 1);
    v17 = ((UIWnd *)(_DWORD *)*v14 + 20)->SetRect(pExceptionObject);
    * a6 = (*)*v17;
    a6[1] = v17[1];
    a6[2] = v17[2];
    a6[3] = v17[3];
    ((UIListBox *)*v14)->GetLockSel((int)aUiCombatContro, a6, 16, 16, 0);
    sub_442230((_DWORD *)*v14 + 20, 26, 28);
    sub_4421F0((_DWORD *)*v14 + 20, -5);
    sub_442200((_DWORD *)*v14 + 20, -2);
    ++v13;
    ++v14;
  }
  while ( (int)v13 < (int)&dword_57011C );
  a1->ChangeSpecStateLum();
  v18 = (char *)((operator *)0x98u)->new();
  v23 = v18;
  if ( v18 )
    v18->UIFrameWnd();
  else
    v19 = 0;
  *(_DWORD *)(a1 + 76) = v19;
  if ( !v19 )
  {
    qmemcpy(
      v26,
      (const void *)((char)&v27)->FormatException((int)aCNewFailed, (int)aDProjectPal3Co_12, 4346),
      sizeof(v26));
    _CxxThrowException(v26, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *a6 = 37;
  a6[2] = 237;
  a6[1] = 170;
  a6[3] = 210;
  (*(void (**)(_DWORD, int, _DWORD *, int))(**(_DWORD **)(a1 + 76) + 16))(*(_DWORD *)(a1 + 76), 131, a6, a1);
  (***(void (****)(_DWORD, int))(a1 + 76))(*(_DWORD *)(a1 + 76), 1);
  ((CCBUI *)0)->GravityDown();
  return 1;
}

// 0x00519F50
int CCBUI::DeleteUIObj(int _this)
{
  int result; // eax
  _DWORD *v3; // esi
  int v4; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx

  result = ((gbRefObject **)this)->SetScrollPos();
  v3 = (_DWORD *)(this + 80);
  v4 = 3;
  do
  {
    if ( *v3 )
    {
      result = (*(int (**)(_DWORD, int))(*(_DWORD *)*v3 + 20))(*v3, 1);
      *v3 = 0;
    }
    ++v3;
    --v4;
  }
  while ( v4 );
  v5 = *(_DWORD *)(this + 72);
  if ( v5 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  v6 = *(_DWORD *)(this + 76);
  if ( v6 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)(this + 76) = 0;
  }
  v7 = *(_DWORD *)(this + 92);
  if ( v7 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 92) = 0;
  }
  v8 = *(_DWORD *)(this + 96);
  if ( v8 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 96) = 0;
  }
  v9 = *(_DWORD *)(this + 100);
  if ( v9 )
  {
    result = (*(int (**)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 100) = 0;
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
    ((int)this)->GravityDown(a3 - 181);
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
int CCBUI::ChangeSpecStateLum(int _this)
{
  _DWORD *v2; // edi
  int a4; // [esp+8h] [ebp-10h] BYREF
  int v5; // [esp+Ch] [ebp-Ch]
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v2 = (_DWORD *)(this + 92);
  a4 = 40;
  v6 = 72;
  v5 = 27;
  v7 = 59;
  ((CCBUI *)this)->LineMove((_DWORD *)(this + 92), 181, (int)&a4, (int)aUiCombatContro_1);
  (**(void (***)(_DWORD, int))*v2)(*v2, 1);
  a4 = 72;
  v6 = 104;
  v5 = 27;
  v7 = 59;
  ((CCBUI *)this)->LineMove((_DWORD *)(this + 96), 182, (int)&a4, (int)aUiCombatContro_2);
  (***(void (****)(_DWORD, int))(this + 96))(*(_DWORD *)(this + 96), 1);
  a4 = 104;
  v6 = 136;
  v5 = 27;
  v7 = 59;
  ((CCBUI *)this)->LineMove((_DWORD *)(this + 100), 183, (int)&a4, (int)aUiCombatContro_3);
  return (***(int (****)(_DWORD, int))(this + 100))(*(_DWORD *)(this + 100), 1);
}

// 0x0051A1D0
char CCBUI::LineMove(_DWORD *a2, int a3, int a4, int a5)
{
  char *v6; // eax
  int v7; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-40Ch] BYREF
  int v11; // [esp+810h] [ebp-4h]

  v6 = (char *)((operator *)0xF8u)->new();
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
int CCBUI::GravityDown(int _this, int a2)
{
  int v3; // ebp
  _DWORD *v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int result; // eax

  v3 = 3;
  v4 = (_DWORD *)(this + 80);
  do
  {
    (**(void (***)(_DWORD, _DWORD))*v4)(*v4, 0);
    v5 = *(_DWORD *)(this + 92);
    ++v4;
    --v3;
    *(_DWORD *)(v5 + 80) = 0;
    *(_BYTE *)(v5 + 68) = 0;
    v6 = *(_DWORD *)(this + 96);
    *(_DWORD *)(v6 + 80) = 0;
    *(_BYTE *)(v6 + 68) = 0;
    v7 = *(_DWORD *)(this + 100);
    *(_DWORD *)(v7 + 80) = 0;
    *(_BYTE *)(v7 + 68) = 0;
  }
  while ( v3 );
  switch ( a2 )
  {
    case 0:
      v8 = *(_DWORD *)(this + 92);
      goto LABEL_9;
    case 1:
      v8 = *(_DWORD *)(this + 96);
      goto LABEL_9;
    case 2:
      v8 = *(_DWORD *)(this + 100);
LABEL_9:
      *(_DWORD *)(v8 + 80) = 1;
      *(_BYTE *)(v8 + 68) = 1;
      break;
  }
  ((UIWnd *)*(_DWORD **)(this + 72))->SetEnable(MEMORY[0xC10D38], 0);
  ((UIWnd *)*(_DWORD **)(this + 76))->SetEnable(MEMORY[0xC10D38], 0);
  result = (***(int (****)(_DWORD, int))(this + 4 * a2 + 80))(*(_DWORD *)(this + 4 * a2 + 80), 1);
  *(_DWORD *)(this + 104) = a2;
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
  ((UIWnd *)Block)->~UIWnd();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0051A430
char CCBUI::AddTask(int _this, _DWORD *a2, int a3)
{
  char *v4; // eax
  int v5; // eax
  _DWORD *v6; // ecx
  int *v7; // ebp
  char **v8; // esi
  char *v9; // eax
  char *v10; // eax
  _DWORD *v11; // eax
  int v13; // [esp+24h] [ebp-824h] BYREF
  char *v14; // [esp+28h] [ebp-820h]
  int v15[4]; // [esp+2Ch] [ebp-81Ch] BYREF
  char pExceptionObject[1024]; // [esp+3Ch] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+43Ch] [ebp-40Ch] BYREF
  int v18; // [esp+844h] [ebp-4h]

  ((_DWORD *)this)->Create(1879048194, a2, a3);
  v4 = (char *)((operator *)0x98u)->new();
  v14 = v4;
  v18 = 0;
  if ( v4 )
    v4->UIFrameWnd();
  else
    v5 = 0;
  v18 = -1;
  *(_DWORD *)(this + 72) = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)((char)ArgList)->FormatException((int)aCNewFailed_0, (int)aDProjectPal3Co_12, 2678),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *a2 = 0;
  a2[2] = 249;
  a2[1] = 0;
  a2[3] = 206;
  (*(void (**)(_DWORD, int, _DWORD *, int))(**(_DWORD **)(this + 72) + 16))(
    *(_DWORD *)(this + 72),
    150,
    a2,
    this);
  ((UIWnd *)*(gbRefObject ***)(this + 72))->CreateFromTemplate(aUiCombatContro_54, 0);
  (***(void (****)(_DWORD, int))(this + 72))(*(_DWORD *)(this + 72), 1);
  v6 = (_DWORD *)*(_DWORD **)(this + 72);
  v13 = -1879048192;
  v6->SetShow(0);
  ((UIWnd *)*(_DWORD **)(this + 72))->GetChild(&v13);
  ((UIFrameWnd *)*(_DWORD **)(this + 72))->SetPosition(40, 170);
  v7 = (int *)&dword_57011C;
  v8 = (char **)(this + 76);
  do
  {
    v9 = (char *)((operator *)0x4B8u)->new();
    v14 = v9;
    v18 = 1;
    if ( v9 )
      v10 = (char *)v9->UpdateKeyCtrl();
    else
      v10 = 0;
    v18 = -1;
    *v8 = v10;
    if ( !v10 )
    {
      qmemcpy(
        pExceptionObject,
        (const void *)((char)ArgList)->FormatException((int)aCNewFailed_0, (int)aDProjectPal3Co_12, 2700),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *a2 = 39;
    a2[2] = 241;
    a2[1] = 78;
    a2[3] = 175;
    (*(void (**)(char *, int, _DWORD *, int, _DWORD, int, _DWORD))(*(_DWORD *)*v8 + 28))(
      *v8,
      *v7,
      a2,
      this,
      0,
      1,
      0);
    (**(void (***)(char *, _DWORD))*v8)(*v8, 0);
    sub_43F670(*v8, 2, -4);
    ((UIListBox *)*v8)->SetFirstShow(aName, 96);
    ((UIListBox *)*v8)->SetFirstShow(aCost, 37);
    ((UIListBox *)*v8)->SetFirstShow(aLevelcost, 50);
    sub_43F640(*v8, 19);
    ((UIListBox *)*v8)->GetSel((int)aUiCombatContro_0, 0);
    sub_43F690(*v8, 1);
    v11 = ((UIWnd *)(_DWORD *)*v8 + 20)->SetRect(v15);
    * a2 = (*)*v11;
    a2[1] = v11[1];
    a2[2] = v11[2];
    a2[3] = v11[3];
    ((UIListBox *)*v8)->GetLockSel((int)aUiCombatContro, a2, 16, 16, 0);
    sub_442230((_DWORD *)*v8 + 20, 26, 30);
    sub_4421F0((_DWORD *)*v8 + 20, -5);
    sub_442200((_DWORD *)*v8 + 20, -2);
    ++v7;
    ++v8;
  }
  while ( (int)v7 < (int)&dword_570134 );
  this->CCBControlWindow();
  ((CCBControlWindow *)0)->HandleInput();
  return 1;
}
