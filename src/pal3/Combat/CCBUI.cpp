#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBUI.h"

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

  CCBSystem::ProcAI(*(_DWORD *)this->UIFrameWnd, flt_17A95F8);
  if ( *(_BYTE *)(*(_DWORD *)this->UIFrameWnd + 132) != byte_17A9924 )
    CCBSystem::SetRenderFlag(*(CCBSystem **)this->UIFrameWnd, byte_17A9924);
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
    CCBStageScene::Update(*(_DWORD **)(*(_DWORD *)(*(_DWORD *)this->UIFrameWnd + 20) + 20));
    CCBStageScene::ShowRoleIndex(*(float **)(*(_DWORD *)(*(_DWORD *)this->UIFrameWnd + 20) + 20));
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
      v5 = *(void **)(*(_DWORD *)this->UIFrameWnd + 16);
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
      v8 = *(void **)(*(_DWORD *)this->UIFrameWnd + 16);
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
          LOBYTE(inited) = CCBSystem::ProcFlee(*(_BYTE **)this->UIFrameWnd, byte_17A9924);
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
char sub_517650(gbRefObject ***this)
{
  _BYTE *v2; // eax
  gbRefObject **v3; // eax
  _DWORD *v5; // esi
  gbRefObject ***i; // edi
  _BYTE *v7; // eax
  gbRefObject **v8; // eax
  int v9; // [esp+10h] [ebp-1Ch] BYREF
  int v10; // [esp+14h] [ebp-18h]
  int v11; // [esp+18h] [ebp-14h]
  int v12; // [esp+1Ch] [ebp-10h]
  int v13; // [esp+28h] [ebp-4h]

  v2 = operator new(0x98u);
  v13 = 0;
  if ( v2 )
    v2->UIFrameWnd();
  else
    v3 = 0;
  v13 = -1;
  *(this + 18) = v3;
  if ( v3 )
  {
    v9 = 483;
    v10 = 10;
    v11 = 803;
    v12 = 42;
    ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v3)[4].RefCount)(v3, 1, &v9, this);
    UIWnd::CreateFromTemplate(*(this + 18), aUiCombatAttack_0, 0);
    v9 = 480;
    v11 = 544;
    v10 = 8;
    v12 = 72;
    v5 = &unk_5700E8;
    for ( i = this + 19; ; ++i )
    {
      v7 = operator new(0x98u);
      v13 = 1;
      if ( v7 )
        v7->UIFrameWnd();
      else
        v8 = 0;
      v13 = -1;
      *i = v8;
      if ( !v8 )
        break;
      ((void (__thiscall *)(gbRefObject **, _DWORD, int *, gbRefObject ***))(*v8)[4].RefCount)(v8, *v5, &v9, this);
      UIWnd::CreateFromTemplate(*i, aUiCombatAttack_1, 0);
      if ( (int)++v5 >= (int)dword_570114 )
        return 1;
    }
  }
  return 0;
}

// 0x005177B0
char sub_5177B0(gbRefObject ***this)
{
  _BYTE *v2; // eax
  int v3; // eax
  _BYTE *v4; // eax
  int v5; // eax
  _BYTE *v6; // eax
  gbRefObject **v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v11; // [esp+2Ch] [ebp-824h] BYREF
  int v12; // [esp+30h] [ebp-820h] BYREF
  int v13; // [esp+34h] [ebp-81Ch]
  int v14; // [esp+38h] [ebp-818h]
  int v15; // [esp+3Ch] [ebp-814h]
  _BYTE *v16; // [esp+40h] [ebp-810h]
  char pExceptionObject[1024]; // [esp+44h] [ebp-80Ch] BYREF
  char ArgList; // [esp+444h] [ebp-40Ch] BYREF
  int v19; // [esp+84Ch] [ebp-4h]

  v11 = -1;
  v2 = operator new(0x9Cu);
  v16 = v2;
  v19 = 0;
  if ( v2 )
    v3 = sub_442D00((int)v2);
  else
    v3 = 0;
  *(this + 268) = (gbRefObject **)v3;
  v4 = operator new(0x9Cu);
  v16 = v4;
  v19 = 1;
  if ( v4 )
    v5 = sub_442D00((int)v4);
  else
    v5 = 0;
  *(this + 269) = (gbRefObject **)v5;
  v6 = operator new(0x98u);
  v16 = v6;
  v19 = 2;
  if ( v6 )
    v6->UIFrameWnd();
  else
    v7 = 0;
  v8 = (int)*(this + 268);
  v19 = -1;
  *(this + 270) = v7;
  if ( !v8 || !*(this + 269) || !v7 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_12, 719),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v12 = 300;
  v13 = 30;
  v14 = 461;
  v15 = 87;
  (*(void (__thiscall **)(int, int, int *, gbRefObject ***))(*(_DWORD *)v8 + 16))(v8, 784, &v12, this);
  UIWnd::CreateFromTemplate(*(this + 268), aUiCombatTrickn, 0);
  UIWnd::SetShow(*(this + 268), 1);
  UIWnd::GetChild(*(this + 268), &v11);
  ((void (__thiscall *)(_DWORD, _DWORD))(**(this + 268))->RefCount)(*(this + 268), 0);
  ((void (__thiscall *)(_DWORD, int, int *, gbRefObject ***))(**(this + 269))[4].RefCount)(
    *(this + 269),
    784,
    &v12,
    this);
  UIWnd::CreateFromTemplate(*(this + 269), aUiCombatTrickn_0, 0);
  UIWnd::SetShow(*(this + 269), 1);
  UIWnd::GetChild(*(this + 269), &v11);
  ((void (__thiscall *)(_DWORD, _DWORD))(**(this + 269))->RefCount)(*(this + 269), 0);
  v9 = (int)*(this + 270);
  v12 = 100;
  v13 = 100;
  v14 = 356;
  v15 = 228;
  (*(void (__thiscall **)(int, int, int *, gbRefObject ***))(*(_DWORD *)v9 + 16))(v9, 1024, &v12, this);
  UIWnd::CreateFromTemplate(*(this + 270), aUiCombatDialog, 0);
  UIWnd::SetShow(*(this + 270), 1);
  UIWnd::GetChild(*(this + 270), &v11);
  ((void (__thiscall *)(_DWORD, _DWORD))(**(this + 270))->RefCount)(*(this + 270), 0);
  UIFrameWnd::SetPosition(*(this + 270), 5, 63);
  sub_442C80(*(this + 270), 190);
  return 1;
}

// 0x00517B30
char sub_517B30(_DWORD *this)
{
  _DWORD *v2; // esi
  char result; // al
  _DWORD v4[4]; // [esp+8h] [ebp-10h] BYREF

  v2 = this + 281;
  result = CCBAIWindow::Update(this + 281);
  if ( result )
  {
    v4[0] = 2;
    v4[2] = 251;
    v4[1] = 278;
    v4[3] = 484;
    v4->AddTask(this);
    (**(void (__thiscall ***)(_DWORD, _DWORD))*v2)(*v2, 0);
    return 1;
  }
  return result;
}

// 0x00517C10
char sub_517C10(_DWORD *this)
{
  _DWORD *v2; // esi
  char result; // al
  _DWORD v4[4]; // [esp+8h] [ebp-10h] BYREF

  v2 = this + 283;
  result = CCBLineupWindow::CCBLineupWindow(this + 283);
  if ( result )
  {
    v4[0] = 14;
    v4[2] = 172;
    v4[1] = 316;
    v4[3] = 474;
    v4->Create(this);
    (**(void (__thiscall ***)(_DWORD, _DWORD))*v2)(*v2, 0);
    return 1;
  }
  return result;
}

// 0x00517C80
char sub_517C80(_DWORD *this)
{
  _DWORD *v2; // esi
  char result; // al
  _DWORD v4[4]; // [esp+8h] [ebp-10h] BYREF

  v2 = this + 284;
  result = CCBLineupWindow::~CCBLineupWindow(this + 284);
  if ( result )
  {
    v4[0] = 9;
    v4[2] = 239;
    v4[1] = 232;
    v4[3] = 482;
    v4->CCBParabolaWindow(this);
    (**(void (__thiscall ***)(_DWORD, _DWORD))*v2)(*v2, 0);
    return 1;
  }
  return result;
}

// 0x00517D60
char sub_517D60(_DWORD *this)
{
  int v1; // esi
  _DWORD *i; // edi
  int v5; // [esp+Ch] [ebp-10h] BYREF
  int v6; // [esp+10h] [ebp-Ch]
  int v7; // [esp+14h] [ebp-8h]
  int v8; // [esp+18h] [ebp-4h]

  v1 = 0;
  v6 = 0;
  v7 = 0;
  v5 = 0;
  v8 = 0;
  for ( i = this + 286; (unsigned __int8)i->Create(); ++i )
  {
    v7 = v1 + 256;
    v5 = v1;
    v6 = 0;
    v8 = 256;
    CCBSkillWindow::Create(&v5, this);
    (**(void (__thiscall ***)(_DWORD, _DWORD))*i)(*i, 0);
    v1 += 200;
    if ( v1 >= 800 )
      return 1;
  }
  return 0;
}

// 0x00517DF0
char sub_517DF0(gbRefObject ***this)
{
  gbRefObject ***v2; // edi
  char result; // al
  gbRefObject **v4; // ecx
  gbRefObject ***v5; // edi
  gbRefObject **v6; // ecx
  gbRefObject ***v7; // edi
  gbRefObject **v8; // ecx
  gbRefObject ***v9; // edi
  gbRefObject **v10; // ecx
  gbRefObject ***v11; // edi
  gbRefObject **v12; // ecx
  gbRefObject ***v13; // edi
  gbRefObject **v14; // ecx
  gbRefObject ***v15; // edi
  gbRefObject **v16; // ecx
  gbRefObject ***v17; // edi
  gbRefObject **v18; // ecx
  int v19; // [esp+7Ch] [ebp-14h] BYREF
  int v20; // [esp+80h] [ebp-10h] BYREF
  int v21; // [esp+84h] [ebp-Ch]
  int v22; // [esp+88h] [ebp-8h]
  int v23; // [esp+8Ch] [ebp-4h]

  v21 = 0;
  v2 = this + 271;
  v22 = 0;
  v20 = 0;
  v23 = 0;
  v19 = -1;
  result = CCBAIWindow::Reset(this + 271);
  if ( result )
  {
    v4 = *v2;
    v20 = 284;
    v22 = 516;
    v21 = 268;
    v23 = 332;
    ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v4)[4].RefCount)(v4, 531, &v20, this);
    UIWnd::CreateFromTemplate(*v2, aUiCombatResult_6, 0);
    UIWnd::SetShow(*v2, 1);
    UIWnd::GetChild(*v2, &v19);
    ((void (__thiscall *)(gbRefObject **, _DWORD))(**v2)->RefCount)(*v2, 0);
    v5 = this + 272;
    result = CCBAIWindow::Reset(this + 272);
    if ( result )
    {
      v6 = *v5;
      v20 = 249;
      v22 = 551;
      v21 = 263;
      v23 = 337;
      ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v6)[4].RefCount)(v6, 533, &v20, this);
      UIWnd::CreateFromTemplate(*v5, aUiCombatResult_8, 0);
      UIWnd::SetShow(*v5, 1);
      UIWnd::GetChild(*v5, &v19);
      ((void (__thiscall *)(gbRefObject **, _DWORD))(**v5)->RefCount)(*v5, 0);
      v7 = this + 273;
      result = CCBAIWindow::Reset(this + 273);
      if ( result )
      {
        v8 = *v7;
        v20 = 249;
        v22 = 551;
        v21 = 263;
        v23 = 337;
        ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v8)[4].RefCount)(v8, 534, &v20, this);
        UIWnd::CreateFromTemplate(*v7, aUiCombatResult_9, 0);
        UIWnd::SetShow(*v7, 1);
        UIWnd::GetChild(*v7, &v19);
        ((void (__thiscall *)(gbRefObject **, _DWORD))(**v7)->RefCount)(*v7, 0);
        v9 = this + 274;
        result = CCBAIWindow::Reset(this + 274);
        if ( result )
        {
          v10 = *v9;
          v20 = 249;
          v22 = 551;
          v21 = 263;
          v23 = 337;
          ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v10)[4].RefCount)(v10, 535, &v20, this);
          UIWnd::CreateFromTemplate(*v9, aUiCombatResult_10, 0);
          UIWnd::SetShow(*v9, 1);
          UIWnd::GetChild(*v9, &v19);
          ((void (__thiscall *)(gbRefObject **, _DWORD))(**v9)->RefCount)(*v9, 0);
          v11 = this + 275;
          result = CCBAIWindow::Reset(this + 275);
          if ( result )
          {
            v12 = *v11;
            v20 = 249;
            v22 = 551;
            v21 = 263;
            v23 = 337;
            ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v12)[4].RefCount)(v12, 536, &v20, this);
            UIWnd::CreateFromTemplate(*v11, aUiCombatResult_11, 0);
            UIWnd::SetShow(*v11, 1);
            UIWnd::GetChild(*v11, &v19);
            ((void (__thiscall *)(gbRefObject **, _DWORD))(**v11)->RefCount)(*v11, 0);
            v13 = this + 276;
            result = CCBAIWindow::Reset(this + 276);
            if ( result )
            {
              v14 = *v13;
              v20 = 249;
              v22 = 551;
              v21 = 263;
              v23 = 337;
              ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v14)[4].RefCount)(
                v14,
                538,
                &v20,
                this);
              UIWnd::CreateFromTemplate(*v13, aUiCombatResult_12, 0);
              UIWnd::SetShow(*v13, 1);
              UIWnd::GetChild(*v13, &v19);
              ((void (__thiscall *)(gbRefObject **, _DWORD))(**v13)->RefCount)(*v13, 0);
              v15 = this + 277;
              result = CCBAIWindow::Reset(this + 277);
              if ( result )
              {
                v16 = *v15;
                v20 = 249;
                v22 = 551;
                v21 = 263;
                v23 = 337;
                ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v16)[4].RefCount)(
                  v16,
                  539,
                  &v20,
                  this);
                UIWnd::CreateFromTemplate(*v15, aUiCombatResult_13, 0);
                UIWnd::SetShow(*v15, 1);
                UIWnd::GetChild(*v15, &v19);
                ((void (__thiscall *)(gbRefObject **, _DWORD))(**v15)->RefCount)(*v15, 0);
                v17 = this + 278;
                result = CCBAIWindow::Reset(this + 278);
                if ( result )
                {
                  v18 = *v17;
                  v20 = 221;
                  v22 = 579;
                  v21 = 255;
                  v23 = 345;
                  ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(*v18)[4].RefCount)(
                    v18,
                    532,
                    &v20,
                    this);
                  UIWnd::CreateFromTemplate(*v17, aUiCombatResult_7, 0);
                  UIWnd::SetShow(*v17, 1);
                  UIWnd::GetChild(*v17, &v19);
                  ((void (__thiscall *)(gbRefObject **, _DWORD))(**v17)->RefCount)(*v17, 0);
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
char sub_5181E0(int this)
{
  void (__thiscall ***v2)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v3)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v4)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v5)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v6)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v7)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v8)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v9)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v10)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v11)(_DWORD, _DWORD); // ecx
  int v12; // ecx
  int v13; // edi
  _DWORD *v14; // ebx

  *(_DWORD *)(this + 1164) = **(_DWORD **)(this + 1160);
  v2 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1012);
  if ( v2 )
    (**v2)(v2, 0);
  v3 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1016);
  if ( v3 )
    (**v3)(v3, 0);
  v4 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1084);
  if ( v4 )
    (**v4)(v4, 0);
  v5 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1088);
  if ( v5 )
    (**v5)(v5, 0);
  v6 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1092);
  if ( v6 )
    (**v6)(v6, 0);
  v7 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1096);
  if ( v7 )
    (**v7)(v7, 0);
  v8 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1100);
  if ( v8 )
    (**v8)(v8, 0);
  v9 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1104);
  if ( v9 )
    (**v9)(v9, 0);
  v10 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1108);
  if ( v10 )
    (**v10)(v10, 0);
  v11 = *(void (__thiscall ****)(_DWORD, _DWORD))(this + 1112);
  if ( v11 )
    (**v11)(v11, 0);
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1120))(*(_DWORD *)(this + 1120), 0);
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1124))(*(_DWORD *)(this + 1124), 0);
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1128))(*(_DWORD *)(this + 1128), 0);
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1132))(*(_DWORD *)(this + 1132), 0);
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1136))(*(_DWORD *)(this + 1136), 0);
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1140))(*(_DWORD *)(this + 1140), 0);
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1080))(*(_DWORD *)(this + 1080), 0);
  *(_DWORD *)(*(_DWORD *)(this + 1072) + 152) = 0;
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1072))(*(_DWORD *)(this + 1072), 0);
  *(_DWORD *)(*(_DWORD *)(this + 1076) + 152) = 0;
  (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1076))(*(_DWORD *)(this + 1076), 0);
  CCBUI::CreateResultWindow(0);
  v12 = *(_DWORD *)(this + 1068);
  if ( v12 )
  {
    sub_43FE90(v12);
    UIWnd::FindChild(*(_DWORD *)(this + 1068), 50.0);
    UIWnd::FindChildByName(*(_DWORD *)(this + 1068), 0.0);
  }
  v13 = 0;
  v14 = (_DWORD *)(this + 1144);
  do
  {
    *(_DWORD *)(*v14 + 172) = v13;
    (**(void (__thiscall ***)(_DWORD, _DWORD))*v14)(*v14, 0);
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
int ( *** sub_5183C0(_DWORD *this))(_DWORD, _DWORD)
{
  void (__thiscall ***v2)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v3)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v4)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v5)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v6)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v7)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v8)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v9)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v10)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v11)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v12)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v13)(_DWORD, _DWORD); // ecx
  int v14; // edi
  _DWORD *v15; // esi
  int (__thiscall ***result)(_DWORD, _DWORD); // eax

  v2 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 253);
  if ( v2 )
    (**v2)(v2, 0);
  v3 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 254);
  if ( v3 )
    (**v3)(v3, 0);
  v4 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 270);
  if ( v4 )
    (**v4)(v4, 0);
  v5 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 279);
  if ( v5 )
    (**v5)(v5, 0);
  v6 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 280);
  if ( v6 )
    (**v6)(v6, 0);
  v7 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 281);
  if ( v7 )
    (**v7)(v7, 0);
  v8 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 282);
  if ( v8 )
    (**v8)(v8, 0);
  v9 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 283);
  if ( v9 )
    (**v9)(v9, 0);
  v10 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 284);
  if ( v10 )
    (**v10)(v10, 0);
  v11 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 285);
  if ( v11 )
    (**v11)(v11, 0);
  v12 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 268);
  if ( v12 )
    (**v12)(v12, 0);
  v13 = (void (__thiscall ***)(_DWORD, _DWORD))*(this + 269);
  if ( v13 )
    (**v13)(v13, 0);
  CCBUI::CreateResultWindow(0);
  v14 = 0;
  v15 = this + 286;
  do
  {
    result = (int (__thiscall ***)(_DWORD, _DWORD))*v15;
    if ( *v15 )
    {
      result[43] = (int (__thiscall **)(_DWORD, _DWORD))v14;
      result = (int (__thiscall ***)(_DWORD, _DWORD))(**(int (__thiscall ***)(_DWORD, _DWORD))*v15)(*v15, 0);
    }
    ++v14;
    ++v15;
  }
  while ( v14 < 4 );
  return result;
}

// 0x005184C0
int sub_5184C0(_DWORD *this, char a2)
{
  int (__thiscall ***v2)(_DWORD, int); // ecx

  v2 = (int (__thiscall ***)(_DWORD, int))*(this + 279);
  if ( a2 )
    return (**v2)(v2, 1);
  else
    return (**v2)(v2, 0);
}

// 0x00518AF0
int sub_518AF0(_DWORD *this, int a2, char a3)
{
  int (__thiscall ***v3)(_DWORD, int); // ecx

  *(_DWORD *)(*(this + 283) + 124) = a2;
  v3 = (int (__thiscall ***)(_DWORD, int))*(this + 283);
  if ( a3 )
    return (**v3)(v3, 1);
  else
    return (**v3)(v3, 0);
}

// 0x00518B20
char sub_518B20(_DWORD *this)
{
  return *(_BYTE *)(*(this + 286) + 176);
}

// 0x00518B30
char sub_518B30(int this, char a2)
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
        (***(void (__thiscall ****)(_DWORD, int))(this + 4 * i + 136))(*(_DWORD *)(this + 4 * i + 136), 1);
        (***(void (__thiscall ****)(_DWORD, int))(this + 4 * i + 156))(*(_DWORD *)(this + 4 * i + 156), 1);
        v5 = *(unsigned __int8 *)(CCBRoleState::InitUI(*(void **)(*(_DWORD *)(this + 1160) + 16), i) + 24);
        (***(void (__thiscall ****)(_DWORD, int))(this + 4 * v5 + 1020))(*(_DWORD *)(this + 4 * v5 + 1020), 1);
        (***(void (__thiscall ****)(_DWORD, int))(this + 4 * v5 + 1036))(*(_DWORD *)(this + 4 * v5 + 1036), 1);
        (***(void (__thiscall ****)(_DWORD, int))(this + 4 * v5 + 1052))(*(_DWORD *)(this + 4 * v5 + 1052), 1);
        result = (***(int (__thiscall ****)(_DWORD, int))(this + 4 * v5 + 120))(*(_DWORD *)(this + 4 * v5 + 120), 1);
        if ( !i )
          result = (***(int (__thiscall ****)(_DWORD, int))(this + 1068))(*(_DWORD *)(this + 1068), 1);
      }
    }
  }
  else
  {
    (***(void (__thiscall ****)(_DWORD, _DWORD))(this + 1068))(*(_DWORD *)(this + 1068), 0);
    v6 = this + 1036;
    v7 = 4;
    do
    {
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v6 - 16))(*(_DWORD *)(v6 - 16), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))v6)(*(_DWORD *)v6, 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v6 + 16))(*(_DWORD *)(v6 + 16), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v6 - 916))(*(_DWORD *)(v6 - 916), 0);
      v6 += 4;
      --v7;
    }
    while ( v7 );
    v8 = (_DWORD *)(this + 156);
    v9 = 5;
    do
    {
      (**(void (__thiscall ***)(_DWORD, _DWORD))*(v8 - 5))(*(v8 - 5), 0);
      (**(void (__thiscall ***)(_DWORD, _DWORD))*v8)(*v8, 0);
      ++v8;
      --v9;
    }
    while ( v9 );
    v10 = this + 220;
    v11 = 11;
    do
    {
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 - 44))(*(_DWORD *)(v10 - 44), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))v10)(*(_DWORD *)v10, 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 44))(*(_DWORD *)(v10 + 44), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 88))(*(_DWORD *)(v10 + 88), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 220))(*(_DWORD *)(v10 + 220), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 264))(*(_DWORD *)(v10 + 264), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 132))(*(_DWORD *)(v10 + 132), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 176))(*(_DWORD *)(v10 + 176), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 308))(*(_DWORD *)(v10 + 308), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 352))(*(_DWORD *)(v10 + 352), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 396))(*(_DWORD *)(v10 + 396), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 440))(*(_DWORD *)(v10 + 440), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 484))(*(_DWORD *)(v10 + 484), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 528))(*(_DWORD *)(v10 + 528), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 572))(*(_DWORD *)(v10 + 572), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 616))(*(_DWORD *)(v10 + 616), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 660))(*(_DWORD *)(v10 + 660), 0);
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v10 + 704))(*(_DWORD *)(v10 + 704), 0);
      result = (***(int (__thiscall ****)(_DWORD, _DWORD))(v10 + 748))(*(_DWORD *)(v10 + 748), 0);
      v10 += 4;
      --v11;
    }
    while ( v11 );
  }
  return result;
}

// 0x00518D40
int sub_518D40(int this, char a2)
{
  int v3; // ebx
  int v4; // ebp
  int i; // esi

  if ( !a2 )
    return (***(int (__thiscall ****)(_DWORD, _DWORD))(this + 1136))(*(_DWORD *)(this + 1136), 0);
  v3 = 0;
  v4 = 0;
  for ( i = 96; i < 116; i += 4 )
  {
    if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 1160) + 16) + v4 + 577) )
    {
      (***(void (__thiscall ****)(_DWORD, int))(i + *(_DWORD *)(this + 1136)))(
        *(_DWORD *)(i + *(_DWORD *)(this + 1136)),
        1);
      *(_DWORD *)(i + *(_DWORD *)(this + 1136) - 24) = *(_DWORD *)(CCBRoleState::InitUI(
                                                                     *(void **)(*(_DWORD *)(this + 1160) + 16),
                                                                     v3)
                                                                 + 584);
      UIWnd::ScreenToClient(
        *(_DWORD **)(i + *(_DWORD *)(this + 1136)),
        dword_57024C[*(_DWORD *)(i + *(_DWORD *)(this + 1136) - 24)] + 9,
        dword_570268[*(_DWORD *)(i + *(_DWORD *)(this + 1136) - 24)] + 232);
    }
    else
    {
      (***(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)(this + 1136) + i))(
        *(_DWORD *)(*(_DWORD *)(this + 1136) + i),
        0);
    }
    ++v3;
    v4 += 892;
  }
  return (***(int (__thiscall ****)(_DWORD, int))(this + 1136))(*(_DWORD *)(this + 1136), 1);
}

// 0x00518E60
int CCBUI::HideAll(_DWORD *this)
{
  _DWORD *v1; // esi
  int v2; // ebx
  int result; // eax
  float v4; // [esp+10h] [ebp-8h]
  int v5; // [esp+14h] [ebp-4h]

  HIBYTE(v5) = -1;
  v4 = sin(*(float *)(*(this + 290) + 80) * 12.0) * 50.0;
  v1 = this + 55;
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
    ++v1;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x00518FE0
int sub_518FE0(float *this, int a2)
{
  int v2; // esi
  double v3; // st7
  double v4; // st6
  double v5; // st7

  v2 = (int)(this + 18 * *((_DWORD *)this + 657) + 292);
  if ( !*((_BYTE *)this + 72 * *((_DWORD *)this + 657) + 1185) )
  {
    *(this + 18 * *((_DWORD *)this + 657) + 298) = *(float *)(*((_DWORD *)this + 290) + 80);
    *(_BYTE *)(v2 + 17) = 1;
  }
  v4 = *(float *)(v2 + 28) + *(float *)(v2 + 24);
  if ( *(float *)(*((_DWORD *)this + 290) + 80) <= v4 )
    return 0;
  v3 = *(float *)(*((_DWORD *)this + 290) + 80);
  v5 = (v3 - v4) * ((v3 - v4) * *(float *)(v2 + 32)) * 0.5 + *(float *)(v2 + 44);
  if ( v5 > *(float *)(v2 + 52) )
  {
    v5 = *(float *)(v2 + 52);
    *(_BYTE *)(v2 + 18) = 1;
  }
  UIWnd::ScreenToClient(*(_DWORD **)(v2 + 36), (__int64)*(float *)(v2 + 40), (__int64)v5);
  return 0;
}

// 0x00519080
int sub_519080(float *this, int a2)
{
  int v2; // esi
  double v3; // st6
  float v5; // [esp+8h] [ebp-8h]
  float v6; // [esp+Ch] [ebp-4h]

  v2 = (int)(this + 18 * *((_DWORD *)this + 657) + 292);
  if ( !*((_BYTE *)this + 72 * *((_DWORD *)this + 657) + 1185) )
  {
    *(this + 18 * *((_DWORD *)this + 657) + 298) = *(float *)(*((_DWORD *)this + 290) + 80);
    *(_BYTE *)(v2 + 17) = 1;
  }
  v3 = *(float *)(v2 + 28) + *(float *)(v2 + 24);
  if ( *(float *)(*((_DWORD *)this + 290) + 80) <= v3 )
    return 0;
  v6 = (*(float *)(*((_DWORD *)this + 290) + 80) - v3) / *(float *)(v2 + 32);
  v5 = (*(float *)(v2 + 48) - *(float *)(v2 + 40)) * v6 + *(float *)(v2 + 40);
  sprintf(byte_17ACB08, "%d", (int)v5);
  UIWnd::SetEnable(*(_DWORD **)(v2 + 36), byte_17ACB08, 1);
  if ( v6 < 1.0 )
    return 0;
  sprintf(byte_17ACB08, "%d", (int)*(float *)(v2 + 48));
  UIWnd::SetEnable(*(_DWORD **)(v2 + 36), byte_17ACB08, 1);
  *(_BYTE *)(v2 + 18) = 1;
  return 0;
}

// 0x00519200
int CCBUI::ShowDialogWindow()
{
  int v2; // esi
  char *v3; // edi
  int result; // eax

  v2 = 0;
  v3 = &this->UIFrameWnd[1186];
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
char sub_519230(_DWORD *this, int a2)
{
  *((_BYTE *)this + 72 * a2 + 1184) = 0;
  --*(this + 656);
  return 1;
}

// 0x00519260
char sub_519260(int *this, int a2, int a3, int a4, int a5, int a6, int a7, int a8, const void *a9)
{
  int v10; // eax
  _BYTE *i; // ecx
  int *v13; // eax

  if ( *(this + 656) >= 19 )
    return 0;
  v10 = 0;
  for ( i = this + 296; *i; i += 72 )
  {
    if ( ++v10 >= 20 )
      return 0;
  }
  v13 = this + 18 * v10;
  *((_BYTE *)v13 + 1184) = 1;
  *((_BYTE *)v13 + 1185) = 0;
  *((_BYTE *)v13 + 1186) = 0;
  v13[299] = a7;
  v13[300] = a8;
  v13[297] = a6;
  qmemcpy(v13 + 301, a9, 0x20u);
  v13 += 292;
  *v13 = a2;
  v13[1] = a3;
  v13[2] = a4;
  v13[3] = a5;
  ++*(this + 656);
  return 1;
}

// 0x00519360
stdiobuf * sub_519360(stdiobuf *Block, char a2)
{
  stdiobuf::~stdiobuf(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x005193D0
int sub_5193D0(_DWORD *this)
{
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  return 0;
}

// 0x00519400
char sub_519400(int this, _DWORD *a2, int a3)
{
  _BYTE *v4; // eax
  int v5; // eax
  char pExceptionObject[1024]; // [esp+Ch] [ebp-80Ch] BYREF
  char ArgList; // [esp+40Ch] [ebp-40Ch] BYREF
  int v9; // [esp+814h] [ebp-4h]

  (_DWORD *->Create()this, 1879048193, a2, a3);
  v4 = operator new(0x98u);
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
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_12, 2090),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *a2 = 0;
  a2[2] = 256;
  a2[1] = 0;
  a2[3] = 256;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(**(_DWORD **)(this + 72) + 16))(
    *(_DWORD *)(this + 72),
    256,
    a2,
    this);
  UIWnd::CreateFromTemplate(*(gbRefObject ***)(this + 72), aUiCombatContro_33, 0);
  (***(void (__thiscall ****)(_DWORD, int))(this + 72))(*(_DWORD *)(this + 72), 1);
  this->SetNimbusToNimbusControl();
  return 1;
}

// 0x00519510
int sub_519510(int this)
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

  result = (gbRefObject **->SetScrollPos()this);
  v3 = *(_DWORD *)(this + 72);
  if ( v3 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  v4 = *(_DWORD *)(this + 76);
  if ( v4 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *(_DWORD *)(this + 76) = 0;
  }
  v5 = *(_DWORD *)(this + 80);
  if ( v5 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 80) = 0;
  }
  v6 = *(_DWORD *)(this + 84);
  if ( v6 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)(this + 84) = 0;
  }
  v7 = *(_DWORD *)(this + 88);
  if ( v7 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 88) = 0;
  }
  v8 = *(_DWORD *)(this + 92);
  if ( v8 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 92) = 0;
  }
  v9 = *(_DWORD *)(this + 96);
  if ( v9 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 96) = 0;
  }
  v10 = *(_DWORD *)(this + 100);
  if ( v10 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)(this + 100) = 0;
  }
  v11 = *(_DWORD *)(this + 104);
  if ( v11 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
    *(_DWORD *)(this + 104) = 0;
  }
  v12 = *(_DWORD *)(this + 108);
  if ( v12 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
    *(_DWORD *)(this + 108) = 0;
  }
  v13 = *(_DWORD *)(this + 112);
  if ( v13 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
    *(_DWORD *)(this + 112) = 0;
  }
  return result;
}

// 0x005195E0
int sub_5195E0(_DWORD *this, int a2, unsigned int a3, int a4)
{
  if ( a2 == 1001 )
  {
    if ( a3 >= 0x103 && a3 <= 0x10C )
    {
      this->GetInstance();
      aWa001->AudioSetPosition(1);
    }
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3, a4, 0);
  }
  else if ( a2 == 1007 && a4 != -1 )
  {
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3, a4, 0);
  }
  return a2->SendMessage(a3, a4);
}

// 0x00519660
BOOL sub_519660(_DWORD *this, int a2, int a3)
{
  if ( *(this + 14) == 1 && (MEMORY[0xBFC6F4] == 1 && (MEMORY[0xBFC6E8] & 0xF) == 1 || MEMORY[0xBFC704] == 1) )
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), 128, -1, 0);
  return this->HitTest(a2, a3);
}

// 0x005196C0
struct gbVFileSystem * CCBUI::SetNimbusToNimbusControl(gbRefObject ***this)
{
  gbRefObject ***v2; // edi
  int a4; // [esp+24h] [ebp-10h] BYREF
  int v5; // [esp+28h] [ebp-Ch]
  int v6; // [esp+2Ch] [ebp-8h]
  int v7; // [esp+30h] [ebp-4h]

  v2 = this + 28;
  a4 = -13;
  v6 = 71;
  v5 = 185;
  v7 = 269;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 28, 269, (int)&a4, (int)aUiCombatContro_42);
  ((void (__thiscall *)(gbRefObject **, _DWORD))(**v2)->RefCount)(*v2, 0);
  a4 = 53;
  v6 = 99;
  v5 = 156;
  v7 = 202;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 19, 259, (int)&a4, (int)aUiCombatContro_34);
  ((void (__thiscall *)(_DWORD, int))(**(this + 19))->RefCount)(*(this + 19), 1);
  PalScript::OpenScript(*(this + 19), aUiCombatContro_35, 0);
  a4 = 57;
  v6 = 103;
  v5 = 97;
  v7 = 143;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 20, 260, (int)&a4, (int)aUiCombatContro_36);
  ((void (__thiscall *)(_DWORD, int))(**(this + 20))->RefCount)(*(this + 20), 1);
  PalScript::OpenScript(*(this + 20), aUiCombatContro_37, 0);
  a4 = 2;
  v6 = 48;
  v5 = 153;
  v7 = 199;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 21, 261, (int)&a4, (int)aUiCombatContro_38);
  ((void (__thiscall *)(_DWORD, int))(**(this + 21))->RefCount)(*(this + 21), 1);
  PalScript::OpenScript(*(this + 21), aUiCombatContro_39, 0);
  a4 = 56;
  v6 = 102;
  v5 = 208;
  v7 = 254;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 22, 262, (int)&a4, (int)aUiCombatContro_40);
  ((void (__thiscall *)(_DWORD, int))(**(this + 22))->RefCount)(*(this + 22), 1);
  PalScript::OpenScript(*(this + 22), aUiCombatContro_41, 0);
  a4 = 19;
  v6 = 65;
  v5 = 192;
  v7 = 238;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 24, 264, (int)&a4, (int)aUiCombatContro_43);
  ((void (__thiscall *)(_DWORD, int))(**(this + 24))->RefCount)(*(this + 24), 1);
  PalScript::OpenScript(*(this + 24), aUiCombatContro_44, 0);
  a4 = 19;
  v6 = 65;
  v5 = 121;
  v7 = 167;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 25, 266, (int)&a4, (int)aUiCombatContro_47);
  ((void (__thiscall *)(_DWORD, int))(**(this + 25))->RefCount)(*(this + 25), 1);
  PalScript::OpenScript(*(this + 25), aUiCombatContro_48, 0);
  a4 = 90;
  v6 = 136;
  v5 = 192;
  v7 = 238;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 26, 267, (int)&a4, (int)aUiCombatContro_49);
  ((void (__thiscall *)(_DWORD, int))(**(this + 26))->RefCount)(*(this + 26), 1);
  PalScript::OpenScript(*(this + 26), aUiCombatContro_50, 0);
  a4 = 90;
  v6 = 136;
  v5 = 121;
  v7 = 167;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 27, 268, (int)&a4, (int)aUiCombatContro_51);
  ((void (__thiscall *)(_DWORD, int))(**(this + 27))->RefCount)(*(this + 27), 1);
  PalScript::OpenScript(*(this + 27), aUiCombatContro_52, 0);
  a4 = 111;
  v6 = 157;
  v5 = 153;
  v7 = 199;
  (CCBUI *->WriteNimbusToPlayerMgr()this, this + 23, 265, (int)&a4, (int)aUiCombatContro_45);
  ((void (__thiscall *)(_DWORD, int))(**(this + 23))->RefCount)(*(this + 23), 1);
  return PalScript::OpenScript(*(this + 23), aUiCombatContro_46, 0);
}

// 0x00519A10
char CCBUI::WriteNimbusToPlayerMgr(_DWORD *a2, int a3, int a4, int a5)
{
  _DWORD *v6; // eax
  int v7; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-40Ch] BYREF
  int v11; // [esp+810h] [ebp-4h]

  v6 = (_DWORD *)operator new(0x158u);
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
      (Logger *->FormatException()ArgList, aCNewFailed, aDProjectPal3Co_12, 2306),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (__thiscall **)(int, int, int, CCBUI *, int, int, _DWORD))(*(_DWORD *)v7 + 28))(v7, a3, a4, this, a5, 1, 0);
  return 1;
}

// 0x00519B40
stdiobuf * sub_519B40(stdiobuf *Block, char a2)
{
  stdiobuf::~stdiobuf(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00519BB0
int sub_519BB0(_DWORD *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  return 0;
}

// 0x00519BD0
char __userpurge sub_519BD0@<al>(
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
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v29 = &loc_56720A;
  v28 = ExceptionList;
  v8 = alloca(4120);
  (_DWORD *->Create()a1, 1879048193, a6, a7);
  v10 = operator new(0x98u);
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
      (const void *)Logger::FormatException(
                      (char)&pExceptionObject[1024],
                      (int)aCNewFailed_0,
                      (int)aDProjectPal3Co_12,
                      2366),
      0x400u);
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *a6 = 0;
  a6[2] = 249;
  a6[1] = 0;
  a6[3] = 206;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int, int, int, int, int))(**(_DWORD **)(a1 + 72) + 16))(
    *(_DWORD *)(a1 + 72),
    131,
    a6,
    a1,
    a4,
    a5,
    a3,
    a2);
  UIWnd::CreateFromTemplate(*(gbRefObject ***)(a1 + 72), aUiCombatContro_53, 0);
  v12 = *(_DWORD **)(a1 + 72);
  v22 = -1862270977;
  v12->SetShow(0);
  UIWnd::GetChild(*(_DWORD **)(a1 + 72), &v22);
  UIFrameWnd::SetPosition(*(_DWORD **)(a1 + 72), 40, 150);
  UIFrameWnd::SetPosition(*(_DWORD **)(a1 + 72), 0, 0);
  (***(void (__thiscall ****)(_DWORD, int))(a1 + 72))(*(_DWORD *)(a1 + 72), 1);
  v13 = &dword_570110;
  v14 = (char **)(a1 + 80);
  do
  {
    v15 = (char *)operator new(0x4B8u);
    v23 = v15;
    if ( v15 )
      v16 = v15->UpdateKeyCtrl();
    else
      v16 = 0;
    *v14 = v16;
    if ( !v16 )
    {
      qmemcpy(
        &pExceptionObject[16],
        (const void *)Logger::FormatException((char)&v25, (int)aCNewFailed_0, (int)aDProjectPal3Co_12, 2390),
        0x400u);
      _CxxThrowException(&pExceptionObject[16], (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *a6 = 39;
    a6[2] = 241;
    a6[1] = 78;
    a6[3] = 175;
    (*(void (__thiscall **)(char *, int, _DWORD *, int, _DWORD, int, _DWORD))(*(_DWORD *)*v14 + 28))(
      *v14,
      *v13,
      a6,
      a1,
      0,
      1,
      0);
    (**(void (__thiscall ***)(char *, int))*v14)(*v14, 1);
    sub_43F670(*v14, 2, -4);
    UIListBox::SetFirstShow(*v14, aName, 150);
    UIListBox::SetFirstShow(*v14, aQuantity, 43);
    sub_43F640(*v14, 19);
    UIListBox::GetSel(*v14, (int)aUiCombatContro_0, 0);
    sub_43F690(*v14, 1);
    v17 = (_DWORD *->SetRect()*v14 + 20, pExceptionObject);
    *a6 = *v17;
    a6[1] = v17[1];
    a6[2] = v17[2];
    a6[3] = v17[3];
    UIListBox::GetLockSel(*v14, (int)aUiCombatContro, a6, 16, 16, 0);
    sub_442230((_DWORD *)*v14 + 20, 26, 28);
    sub_4421F0((_DWORD *)*v14 + 20, -5);
    sub_442200((_DWORD *)*v14 + 20, -2);
    ++v13;
    ++v14;
  }
  while ( (int)v13 < (int)&dword_57011C );
  a1->ChangeSpecStateLum();
  v18 = (char *)operator new(0x98u);
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
      (const void *)Logger::FormatException((char)&v27, (int)aCNewFailed, (int)aDProjectPal3Co_12, 4346),
      sizeof(v26));
    _CxxThrowException(v26, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *a6 = 37;
  a6[2] = 237;
  a6[1] = 170;
  a6[3] = 210;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(**(_DWORD **)(a1 + 76) + 16))(*(_DWORD *)(a1 + 76), 131, a6, a1);
  (***(void (__thiscall ****)(_DWORD, int))(a1 + 76))(*(_DWORD *)(a1 + 76), 1);
  CCBUI::GravityDown(0);
  return 1;
}

// 0x00519F50
int sub_519F50(int this)
{
  int result; // eax
  _DWORD *v3; // esi
  int v4; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx

  result = (gbRefObject **->SetScrollPos()this);
  v3 = (_DWORD *)(this + 80);
  v4 = 3;
  do
  {
    if ( *v3 )
    {
      result = (*(int (__thiscall **)(_DWORD, int))(*(_DWORD *)*v3 + 20))(*v3, 1);
      *v3 = 0;
    }
    ++v3;
    --v4;
  }
  while ( v4 );
  v5 = *(_DWORD *)(this + 72);
  if ( v5 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  v6 = *(_DWORD *)(this + 76);
  if ( v6 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)(this + 76) = 0;
  }
  v7 = *(_DWORD *)(this + 92);
  if ( v7 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 92) = 0;
  }
  v8 = *(_DWORD *)(this + 96);
  if ( v8 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 96) = 0;
  }
  v9 = *(_DWORD *)(this + 100);
  if ( v9 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 100) = 0;
  }
  return result;
}

// 0x00519FE0
int sub_519FE0(_DWORD *this, int a2, unsigned int a3, int a4)
{
  int v5; // ecx
  int v7; // [esp-4h] [ebp-14h]

  if ( a2 == 1001 )
  {
    if ( a3 < 0xB5 || a3 > 0xB7 )
      return a2->SendMessage(a3, a4);
    CCBUI::GravityDown(a3 - 181);
    v5->GetInstance();
    aWa001->AudioSetPosition(1);
    v7 = 0;
LABEL_11:
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3, a4, v7);
    return a2->SendMessage(a3, a4);
  }
  if ( a2 == 1006 )
  {
    if ( a4 == -1 )
      return a2->SendMessage(a3, a4);
    v7 = 1;
    goto LABEL_11;
  }
  if ( a2 == 1007 && a4 != -1 )
  {
    this->GetInstance();
    aWa002->AudioSetPosition(1);
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3, a4, 0);
  }
  return a2->SendMessage(a3, a4);
}

// 0x0051A090
BOOL sub_51A090(_DWORD *this, int a2, int a3)
{
  if ( *(this + 14) == 1 && (MEMORY[0xBFC6F4] == 1 && (MEMORY[0xBFC6E8] & 0xF) == 1 || MEMORY[0xBFC704] == 1) )
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), 128, -1, 0);
  return this->HitTest(a2, a3);
}

// 0x0051A0F0
int CCBUI::ChangeSpecStateLum(int this)
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
  (CCBUI *->LineMove()this, (_DWORD *)(this + 92), 181, (int)&a4, (int)aUiCombatContro_1);
  (**(void (__thiscall ***)(_DWORD, int))*v2)(*v2, 1);
  a4 = 72;
  v6 = 104;
  v5 = 27;
  v7 = 59;
  (CCBUI *->LineMove()this, (_DWORD *)(this + 96), 182, (int)&a4, (int)aUiCombatContro_2);
  (***(void (__thiscall ****)(_DWORD, int))(this + 96))(*(_DWORD *)(this + 96), 1);
  a4 = 104;
  v6 = 136;
  v5 = 27;
  v7 = 59;
  (CCBUI *->LineMove()this, (_DWORD *)(this + 100), 183, (int)&a4, (int)aUiCombatContro_3);
  return (***(int (__thiscall ****)(_DWORD, int))(this + 100))(*(_DWORD *)(this + 100), 1);
}

// 0x0051A1D0
char CCBUI::LineMove(_DWORD *a2, int a3, int a4, int a5)
{
  char *v6; // eax
  int v7; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-40Ch] BYREF
  int v11; // [esp+810h] [ebp-4h]

  v6 = (char *)operator new(0xF8u);
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
      (Logger *->FormatException()ArgList, aCNewFailed, aDProjectPal3Co_12, 2575),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (__thiscall **)(int, int, int, CCBUI *, int, _DWORD))(*(_DWORD *)v7 + 28))(v7, a3, a4, this, a5, 0);
  return 1;
}

// 0x0051A2B0
int sub_51A2B0(int this, int a2)
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
    (**(void (__thiscall ***)(_DWORD, _DWORD))*v4)(*v4, 0);
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
  UIWnd::SetEnable(*(_DWORD **)(this + 72), MEMORY[0xC10D38], 0);
  UIWnd::SetEnable(*(_DWORD **)(this + 76), MEMORY[0xC10D38], 0);
  result = (***(int (__thiscall ****)(_DWORD, int))(this + 4 * a2 + 80))(*(_DWORD *)(this + 4 * a2 + 80), 1);
  *(_DWORD *)(this + 104) = a2;
  return result;
}

// 0x0051A340
_DWORD * sub_51A340(_DWORD *this)
{
  this->UIListBox();
  *this = &off_570500;
  sub_51A400(this);
  return this;
}

// 0x0051A390
stdiobuf * sub_51A390(stdiobuf *Block, char a2)
{
  stdiobuf::~stdiobuf(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0051A430
char sub_51A430(int this, _DWORD *a2, int a3)
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

  (_DWORD *->Create()this, 1879048194, a2, a3);
  v4 = (char *)operator new(0x98u);
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
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_12, 2678),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *a2 = 0;
  a2[2] = 249;
  a2[1] = 0;
  a2[3] = 206;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(**(_DWORD **)(this + 72) + 16))(
    *(_DWORD *)(this + 72),
    150,
    a2,
    this);
  UIWnd::CreateFromTemplate(*(gbRefObject ***)(this + 72), aUiCombatContro_54, 0);
  (***(void (__thiscall ****)(_DWORD, int))(this + 72))(*(_DWORD *)(this + 72), 1);
  v6 = *(_DWORD **)(this + 72);
  v13 = -1879048192;
  v6->SetShow(0);
  UIWnd::GetChild(*(_DWORD **)(this + 72), &v13);
  UIFrameWnd::SetPosition(*(_DWORD **)(this + 72), 40, 170);
  v7 = &dword_57011C;
  v8 = (char **)(this + 76);
  do
  {
    v9 = (char *)operator new(0x4B8u);
    v14 = v9;
    v18 = 1;
    if ( v9 )
      v10 = v9->UpdateKeyCtrl();
    else
      v10 = 0;
    v18 = -1;
    *v8 = v10;
    if ( !v10 )
    {
      qmemcpy(
        pExceptionObject,
        (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_12, 2700),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *a2 = 39;
    a2[2] = 241;
    a2[1] = 78;
    a2[3] = 175;
    (*(void (__thiscall **)(char *, int, _DWORD *, int, _DWORD, int, _DWORD))(*(_DWORD *)*v8 + 28))(
      *v8,
      *v7,
      a2,
      this,
      0,
      1,
      0);
    (**(void (__thiscall ***)(char *, _DWORD))*v8)(*v8, 0);
    sub_43F670(*v8, 2, -4);
    UIListBox::SetFirstShow(*v8, aName, 96);
    UIListBox::SetFirstShow(*v8, aCost, 37);
    UIListBox::SetFirstShow(*v8, aLevelcost, 50);
    sub_43F640(*v8, 19);
    UIListBox::GetSel(*v8, (int)aUiCombatContro_0, 0);
    sub_43F690(*v8, 1);
    v11 = (_DWORD *->SetRect()*v8 + 20, v15);
    *a2 = *v11;
    a2[1] = v11[1];
    a2[2] = v11[2];
    a2[3] = v11[3];
    UIListBox::GetLockSel(*v8, (int)aUiCombatContro, a2, 16, 16, 0);
    sub_442230((_DWORD *)*v8 + 20, 26, 30);
    sub_4421F0((_DWORD *)*v8 + 20, -5);
    sub_442200((_DWORD *)*v8 + 20, -2);
    ++v7;
    ++v8;
  }
  while ( (int)v7 < (int)&dword_570134 );
  this->CCBControlWindow();
  CCBControlWindow::HandleInput(0);
  return 1;
}
