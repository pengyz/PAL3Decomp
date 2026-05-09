#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBControlWindow.h"

// 0x0051A700
CCBControlWindow * CCBControlWindow::CCBControlWindow()
{
  CCBControlWindow *v2; // edi
  int a4; // [esp+14h] [ebp-10h] BYREF
  int v5; // [esp+18h] [ebp-Ch]
  int v6; // [esp+1Ch] [ebp-8h]
  int v7; // [esp+20h] [ebp-4h]

  v2 = (CCBControlWindow *)((char *)this + 100);
  a4 = 40;
  v6 = 72;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 25, 192, (int)&a4, (int)aUiCombatContro_4);
  (**(void (__thiscall ***)(UIStatic *, int))v2->UIFrameWnd)(v2->UIFrameWnd, 1);
  a4 = 72;
  v6 = 104;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 26, 193, (int)&a4, (int)aUiCombatContro_5);
  (***((void (__thiscall ****)(_DWORD, int))this + 26))(*((_DWORD *)this + 26), 1);
  a4 = 104;
  v6 = 136;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 27, 194, (int)&a4, (int)aUiCombatContro_6);
  (***((void (__thiscall ****)(_DWORD, int))this + 27))(*((_DWORD *)this + 27), 1);
  a4 = 136;
  v6 = 168;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 28, 195, (int)&a4, (int)aUiCombatContro_7);
  (***((void (__thiscall ****)(_DWORD, int))this + 28))(*((_DWORD *)this + 28), 1);
  a4 = 168;
  v6 = 200;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 29, 196, (int)&a4, (int)aUiCombatContro_8);
  (***((void (__thiscall ****)(_DWORD, int))this + 29))(*((_DWORD *)this + 29), 1);
  a4 = 200;
  v6 = 232;
  v5 = 27;
  v7 = 59;
  this->Create((_DWORD *)this + 30, 197, (int)&a4, (int)aUiCombatContro_9);
  return (CCBControlWindow *)(***((int (__thiscall ****)(_DWORD, int))this + 30))(*((_DWORD *)this + 30), 1);
}

// 0x0051A880
int sub_51A880(int this)
{
  int result; // eax
  _DWORD *v3; // edi
  int v4; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  result = (gbRefObject **->SetScrollPos()this);
  v3 = (_DWORD *)(this + 76);
  v4 = 6;
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
  v5 = *(_DWORD *)(this + 100);
  if ( v5 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 100) = 0;
  }
  v6 = *(_DWORD *)(this + 104);
  if ( v6 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
    *(_DWORD *)(this + 104) = 0;
  }
  v7 = *(_DWORD *)(this + 108);
  if ( v7 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 108) = 0;
  }
  v8 = *(_DWORD *)(this + 112);
  if ( v8 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 112) = 0;
  }
  v9 = *(_DWORD *)(this + 116);
  if ( v9 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 116) = 0;
  }
  v10 = *(_DWORD *)(this + 120);
  if ( v10 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)(this + 120) = 0;
  }
  v11 = *(_DWORD *)(this + 72);
  if ( v11 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  return result;
}

// 0x0051A930
int sub_51A930(_DWORD *this, int a2, unsigned int a3, int a4)
{
  int v5; // eax

  if ( a2 == 1001 )
  {
    if ( a3 >= 0xC0 && a3 <= 0xC5 )
    {
      this->GetInstance();
      aWa001->AudioSetPosition(1);
      CCBControlWindow::HandleInput(a3 - 192);
      v5 = (int *->CreateChild()*(this + a3 - 173));
      if ( v5 != -1 )
        CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3 - 48, v5, 1);
    }
  }
  else if ( a2 == 1006 )
  {
    if ( a4 != -1 )
      CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3, a4, 1);
  }
  else if ( a2 == 1007 && a4 != -1 )
  {
    this->GetInstance();
    aWa002->AudioSetPosition(1);
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3, a4, 0);
  }
  return a2->SendMessage(a3, a4);
}

// 0x0051AA20
char CCBControlWindow::Create(_DWORD *a2, int a3, int a4, int a5)
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
      (Logger *->FormatException()ArgList, aCNewFailed, aDProjectPal3Co_12, 2875),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void (__thiscall **)(int, int, int, CCBControlWindow *, int, _DWORD))(*(_DWORD *)v7 + 28))(v7, a3, a4, this, a5, 0);
  return 1;
}

// 0x0051AB60
int sub_51AB60(int this, int a2)
{
  int v3; // ebp
  _DWORD *v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int result; // eax
  int v11; // eax

  v3 = 6;
  v4 = (_DWORD *)(this + 76);
  do
  {
    (**(void (__thiscall ***)(_DWORD, _DWORD))*v4)(*v4, 0);
    ++v4;
    --v3;
  }
  while ( v3 );
  v5 = *(_DWORD *)(this + 100);
  *(_DWORD *)(v5 + 80) = 0;
  *(_BYTE *)(v5 + 68) = 0;
  v6 = *(_DWORD *)(this + 104);
  *(_DWORD *)(v6 + 80) = 0;
  *(_BYTE *)(v6 + 68) = 0;
  v7 = *(_DWORD *)(this + 108);
  *(_DWORD *)(v7 + 80) = 0;
  *(_BYTE *)(v7 + 68) = 0;
  v8 = *(_DWORD *)(this + 112);
  *(_DWORD *)(v8 + 80) = 0;
  *(_BYTE *)(v8 + 68) = 0;
  v9 = *(_DWORD *)(this + 116);
  *(_DWORD *)(v9 + 80) = 0;
  *(_BYTE *)(v9 + 68) = 0;
  result = *(_DWORD *)(this + 120);
  *(_DWORD *)(result + 80) = 0;
  *(_BYTE *)(result + 68) = 0;
  switch ( a2 )
  {
    case 0:
      v11 = *(_DWORD *)(this + 100);
      goto LABEL_10;
    case 1:
      v11 = *(_DWORD *)(this + 104);
      goto LABEL_10;
    case 2:
      v11 = *(_DWORD *)(this + 108);
      goto LABEL_10;
    case 3:
      v11 = *(_DWORD *)(this + 112);
      goto LABEL_10;
    case 4:
      v11 = *(_DWORD *)(this + 116);
      goto LABEL_10;
    case 5:
      v11 = *(_DWORD *)(this + 120);
LABEL_10:
      *(_DWORD *)(v11 + 80) = 1;
      *(_BYTE *)(v11 + 68) = 1;
      UIWnd::SetEnable(*(_DWORD **)(this + 72), MEMORY[0xC10D38], 0);
      result = (***(int (__thiscall ****)(_DWORD, int))(this + 4 * a2 + 76))(*(_DWORD *)(this + 4 * a2 + 76), 1);
      *(_DWORD *)(this + 124) = a2;
      break;
    default:
      return result;
  }
  return result;
}

// 0x0051AC30
int sub_51AC30(_DWORD *this)
{
  return *(this + 31);
}

// 0x0051AC40
_DWORD * sub_51AC40(_DWORD *this)
{
  this->UIListBox();
  *this = &off_57051C;
  this->CheckKeyInput();
  return this;
}

// 0x0051AC90
stdiobuf * sub_51AC90(stdiobuf *Block, char a2)
{
  stdiobuf::~stdiobuf(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0051AD00
int sub_51AD00(_DWORD *this)
{
  *(this + 20) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  return 0;
}

// 0x0051AD10
char sub_51AD10(int this, _DWORD *a2, int a3)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  char *v6; // eax
  int v7; // eax
  char *v8; // eax
  int v9; // eax
  _DWORD *v10; // ecx
  int *v11; // ebp
  char **v12; // esi
  char *v13; // eax
  char *v14; // eax
  int v16; // [esp+10h] [ebp-1014h] BYREF
  char *v17; // [esp+14h] [ebp-1010h]
  char pExceptionObject[1024]; // [esp+18h] [ebp-100Ch] BYREF
  char ArgList[1024]; // [esp+418h] [ebp-C0Ch] BYREF
  char v20[1024]; // [esp+818h] [ebp-80Ch] BYREF
  char v21; // [esp+C18h] [ebp-40Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v22; // [esp+1018h] [ebp-Ch]
  void *v23; // [esp+101Ch] [ebp-8h]
  int v24; // [esp+1020h] [ebp-4h]

  v24 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v23 = &loc_56733A;
  v22 = ExceptionList;
  v4 = alloca(4104);
  (_DWORD *->Create()this, 1879048195, a2, a3);
  v6 = (char *)operator new(0x98u);
  v17 = v6;
  v24 = 0;
  if ( v6 )
    v6->UIFrameWnd();
  else
    v7 = 0;
  v24 = -1;
  *(_DWORD *)(this + 72) = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_12, 3023),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *a2 = 0;
  a2[2] = 256;
  a2[1] = 0;
  a2[3] = 256;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(**(_DWORD **)(this + 72) + 16))(
    *(_DWORD *)(this + 72),
    161,
    a2,
    this);
  UIWnd::CreateFromTemplate(*(gbRefObject ***)(this + 72), aUiCombatContro_55, 0);
  (***(void (__thiscall ****)(_DWORD, int))(this + 72))(*(_DWORD *)(this + 72), 1);
  v8 = (char *)operator new(0x98u);
  v17 = v8;
  v24 = 1;
  if ( v8 )
    v8->UIFrameWnd();
  else
    v9 = 0;
  v24 = -1;
  *(_DWORD *)(this + 76) = v9;
  if ( !v9 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_12, 3037),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = *(_DWORD **)(this + 72);
  v16 = -1879048192;
  v10->SetShow(0);
  UIWnd::GetChild(*(_DWORD **)(this + 72), &v16);
  UIFrameWnd::SetPosition(*(_DWORD **)(this + 72), 39, 219);
  v11 = &dword_570134;
  v12 = (char **)(this + 80);
  do
  {
    v13 = (char *)operator new(0x4B8u);
    v17 = v13;
    v24 = 2;
    if ( v13 )
      v14 = v13->UpdateKeyCtrl();
    else
      v14 = 0;
    v24 = -1;
    *v12 = v14;
    if ( !v14 )
    {
      qmemcpy(
        v20,
        (const void *)Logger::FormatException((char)&v21, (int)aCNewFailed_0, (int)aDProjectPal3Co_12, 3067),
        sizeof(v20));
      _CxxThrowException(v20, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    *a2 = 39;
    a2[2] = 241;
    a2[1] = 110;
    a2[3] = 226;
    (*(void (__thiscall **)(char *, int, _DWORD *, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)*v12 + 28))(
      *v12,
      *v11,
      a2,
      this,
      0,
      0,
      0);
    (**(void (__thiscall ***)(char *, int))*v12)(*v12, 1);
    sub_43F670(*v12, 2, -4);
    UIListBox::SetFirstShow(*v12, aName, 150);
    UIListBox::SetFirstShow(*v12, aCost, 43);
    sub_43F640(*v12, 19);
    UIListBox::GetSel(*v12, (int)aUiCombatContro_0, 0);
    sub_43F690(*v12, 1);
    ++v11;
    ++v12;
  }
  while ( (int)v11 < (int)&dword_570138 );
  return 1;
}

// 0x0051AFE0
int sub_51AFE0(int this)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  result = (gbRefObject **->SetScrollPos()this);
  v3 = *(_DWORD *)(this + 80);
  if ( v3 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *(_DWORD *)(this + 80) = 0;
  }
  v4 = *(_DWORD *)(this + 72);
  if ( v4 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *(_DWORD *)(this + 72) = 0;
  }
  v5 = *(_DWORD *)(this + 76);
  if ( v5 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)(this + 76) = 0;
  }
  return result;
}

// 0x0051B0B0
BOOL sub_51B0B0(_DWORD *this, int a2, int a3)
{
  if ( *(this + 14) == 1 && (MEMORY[0xBFC6F4] == 1 && (MEMORY[0xBFC6E8] & 0xF) == 1 || MEMORY[0xBFC704] == 1) )
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), 160, -1, 0);
  return this->HitTest(a2, a3);
}

// 0x0051B110
_DWORD * sub_51B110(_DWORD *this)
{
  this->UIListBox();
  *this = &off_570538;
  this->Reset();
  return this;
}
