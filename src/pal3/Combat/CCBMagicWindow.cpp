#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBMagicWindow.h"

// Forward declarations for unnamed functions
int sub_43FBC0(...);
int sub_440CE0(...);
int sub_51B9F0(...);
int sub_51BAB0(...);
int sub_51BB00(...);
int sub_51BB40(...);
int sub_51BB50(...);
int sub_51BB90(...);
int sub_51BBE0(...);
int sub_51BC50(...);
int sub_51BC70(...);
int sub_51C110(...);
int sub_51C1B0(...);
int sub_51C210(...);

// Unnamed globals (extern)
extern char aUiCombatContro_22[];
extern char aUiCombatContro_23[];
extern char aUiCombatContro_24[];
extern char aUiCombatContro_25[];
extern char aUiCombatContro_26[];
extern char aUiCombatContro_27[];
extern char aUiCombatContro_28[];
extern char aUiCombatContro_29[];
extern char aUiCombatContro_30[];
extern char aUiCombatContro_31[];
extern char aUiCombatContro_32[];
extern int dword_57024C;
extern int dword_570268;
extern void *off_570570;
extern void *off_57058C;

// 0x0051B9F0
char sub_51B9F0(_DWORD **this, int a2, int a3, _DWORD *a4)
{
  int v4; // eax
  _DWORD *v5; // eax
  int v7; // [esp-14h] [ebp-40h]
  int v8; // [esp-10h] [ebp-3Ch]
  int v9; // [esp-Ch] [ebp-38h]
  int v10; // [esp-8h] [ebp-34h]
  _DWORD v11[4]; // [esp+Ch] [ebp-20h] BYREF
  _DWORD v12[4]; // [esp+1Ch] [ebp-10h] BYREF

  v4 = dword_57024C[a2];
  v7 = v4 + 9;
  v8 = dword_570268[a2] + 232;
  v9 = v4 + 49;
  v10 = dword_570268[a2] + 270;
  v5 = UIWnd::SetRect(*(this + a3 + 24), v12);
  if ( (unsigned __int8)CCBLineupWindow::SetFaceLineup(*v5, v5[1], v5[2], v5[3], v7, v8, v9, v10, v11) )
  {
    *a4 = (v11[3] - v11[1]) * (v11[2] - v11[0]);
    return 1;
  }
  else
  {
    *a4 = 0;
    return 0;
  }
}

// 0x0051BAB0
int sub_51BAB0(_DWORD **this, int a2)
{
  int v2; // edi
  int v4; // ebx
  int i; // esi
  int v7; // [esp+10h] [ebp-4h] BYREF

  v2 = 0;
  v7 = 0;
  v4 = -1;
  for ( i = 1; i < 7; ++i )
  {
    if ( this->CCBMagicWindow(i, a2, &v7) && v7 > v2 )
    {
      v4 = i;
      v2 = v7;
    }
  }
  return v4;
}

// 0x0051BB00
int sub_51BB00(int a2, int a3)
{
  _DWORD *v3; // eax
  int v4; // esi

  v3 = this + 18;
  v4 = 5;
  do
  {
    if ( *v3 == a3 )
      *v3 = *(this + a2 + 18);
    ++v3;
    --v4;
  }
  while ( v4 );
  *(this + a2 + 18) = a3;
  sub_51BB50(this);
  return -1;
}

// 0x0051BB40
int sub_51BB40(int a2)
{
  *((_DWORD *)this + 29) = a2;
  return a2;
}

// 0x0051BB90
_DWORD * sub_51BB90()
{
  this->UIListBox();
  *this = &off_570570;
  this->OnMessage();
  return this;
}

// 0x0051BBE0
UIWnd * sub_51BBE0(UIWnd *Block, char a2)
{
  UIWnd::~UIWnd(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0051BC50
int sub_51BC50()
{
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 20) = 0;
  *((_DWORD *)this + 21) = 0;
  *((_DWORD *)this + 22) = 0;
  *((_DWORD *)this + 23) = 0;
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 25) = 0;
  return 0;
}

// 0x0051BC70
char sub_51BC70(_DWORD *a2, int a3)
{
  gbRefObject ***v4; // edi
  gbRefObject ***v5; // edi
  _DWORD *v6; // eax
  gbRefObject **v7; // eax
  gbRefObject ***v8; // edi
  _DWORD *v9; // eax
  gbRefObject **v10; // eax
  gbRefObject ***v11; // edi
  _DWORD *v12; // eax
  gbRefObject **v13; // eax
  gbRefObject ***v14; // edi
  gbRefObject ***v15; // edi
  gbRefObject ***v16; // edi
  _DWORD *v17; // edi
  _DWORD v19[4]; // [esp+3Ch] [ebp-10h] BYREF

  this->Create(1879048198, a2, a3);
  v4 = (gbRefObject ***)(this + 18);
  if ( (unsigned __int8)CCBLineupWindow::Destroy(this + 18) == 1 )
  {
    *a2 = 0;
    a2[2] = 230;
    a2[1] = 0;
    a2[3] = 200;
    ((void (__thiscall *)(gbRefObject **, int, _DWORD *, _DWORD *))(**v4)[4].RefCount)(*v4, 272, a2, this);
    UIWnd::CreateFromTemplate(*v4, aUiCombatContro_22, 0);
    ((void (__thiscall *)(gbRefObject **, int))(**v4)->RefCount)(*v4, 1);
  }
  v5 = (gbRefObject ***)(this + 22);
  if ( (unsigned __int8)CCBLineupWindow::Render(this + 22) == 1 )
  {
    *a2 = 27;
    a2[1] = 57;
    a2[2] = 211;
    a2[3] = 95;
    ((void (__thiscall *)(gbRefObject **, int, _DWORD *, _DWORD *))(**v5)[4].RefCount)(*v5, 276, a2, this);
    v6 = UIWnd::SetRect(*v5, v19);
    UIWnd::AddChild(*v5, v6);
    UIWnd::GetChildCount(*v5, aUiCombatContro_29, 0);
    UIWnd::GetChildAt(*v5, aUiCombatContro_30, 0);
    (float *->SetFrameRate()*v5, 48);
    (float *->GetHeight()*v5, 23);
    (float *->GetWidth()*v5, 11);
    (float *->GetPosition()*v5, 5);
    sub_43FBC0(*v5, aUiCombatContro_31, 0);
    v7 = *v5;
    v7[49] = (gbRefObject *)10;
    v7[50] = (gbRefObject *)9;
    UIWnd::FindChild((int)*v5, 100.0);
    UIWnd::FindChildByName((int)*v5, 100.0);
    (*v5)[28] = (gbRefObject *)1077936128;
    ((void (__thiscall *)(gbRefObject **, int))(**v5)->RefCount)(*v5, 1);
  }
  v8 = (gbRefObject ***)(this + 23);
  if ( (unsigned __int8)CCBLineupWindow::Render(this + 23) == 1 )
  {
    *a2 = 27;
    a2[1] = 94;
    a2[2] = 211;
    a2[3] = 132;
    ((void (__thiscall *)(gbRefObject **, int, _DWORD *, _DWORD *))(**v8)[4].RefCount)(*v8, 277, a2, this);
    v9 = UIWnd::SetRect(*v8, v19);
    UIWnd::AddChild(*v8, v9);
    UIWnd::GetChildCount(*v8, aUiCombatContro_29, 0);
    UIWnd::GetChildAt(*v8, aUiCombatContro_30, 0);
    (float *->SetFrameRate()*v8, 48);
    (float *->GetHeight()*v8, 23);
    (float *->GetWidth()*v8, 11);
    (float *->GetPosition()*v8, 5);
    sub_43FBC0(*v8, aUiCombatContro_31, 0);
    v10 = *v8;
    v10[49] = (gbRefObject *)10;
    v10[50] = (gbRefObject *)9;
    UIWnd::FindChild((int)*v8, 100.0);
    UIWnd::FindChildByName((int)*v8, 100.0);
    (*v8)[28] = (gbRefObject *)1077936128;
    ((void (__thiscall *)(gbRefObject **, int))(**v8)->RefCount)(*v8, 1);
  }
  v11 = (gbRefObject ***)(this + 24);
  if ( (unsigned __int8)CCBLineupWindow::Render(this + 24) == 1 )
  {
    *a2 = 27;
    a2[1] = 132;
    a2[2] = 211;
    a2[3] = 170;
    ((void (__thiscall *)(gbRefObject **, int, _DWORD *, _DWORD *))(**v11)[4].RefCount)(*v11, 278, a2, this);
    v12 = UIWnd::SetRect(*v11, v19);
    UIWnd::AddChild(*v11, v12);
    UIWnd::GetChildCount(*v11, aUiCombatContro_29, 0);
    UIWnd::GetChildAt(*v11, aUiCombatContro_30, 0);
    (float *->SetFrameRate()*v11, 48);
    (float *->GetHeight()*v11, 23);
    (float *->GetWidth()*v11, 11);
    (float *->GetPosition()*v11, 5);
    sub_43FBC0(*v11, aUiCombatContro_31, 0);
    v13 = *v11;
    v13[49] = (gbRefObject *)10;
    v13[50] = (gbRefObject *)9;
    UIWnd::FindChild((int)*v11, 100.0);
    UIWnd::FindChildByName((int)*v11, 100.0);
    (*v11)[28] = (gbRefObject *)1077936128;
    ((void (__thiscall *)(gbRefObject **, int))(**v11)->RefCount)(*v11, 1);
  }
  v14 = (gbRefObject ***)(this + 19);
  if ( (unsigned __int8)CCBLineupWindow::OnMessage(this + 19) == 1 )
  {
    *a2 = 37;
    a2[1] = 57;
    a2[2] = 69;
    a2[3] = 89;
    ((void (__thiscall *)(gbRefObject **, int, _DWORD *, _DWORD *, char *, _DWORD))(**v14)[7].RefCount)(
      *v14,
      273,
      a2,
      this,
      aUiCombatContro_23,
      0);
    sub_440CE0(*v14, aUiCombatContro_26, 0);
    ((void (__thiscall *)(gbRefObject **, int))(**v14)->RefCount)(*v14, 1);
  }
  v15 = (gbRefObject ***)(this + 20);
  if ( (unsigned __int8)CCBLineupWindow::OnMessage(this + 20) == 1 )
  {
    *a2 = 37;
    a2[1] = 94;
    a2[2] = 69;
    a2[3] = 126;
    ((void (__thiscall *)(gbRefObject **, int, _DWORD *, _DWORD *, char *, _DWORD))(**v15)[7].RefCount)(
      *v15,
      274,
      a2,
      this,
      aUiCombatContro_24,
      0);
    sub_440CE0(*v15, aUiCombatContro_27, 0);
    ((void (__thiscall *)(gbRefObject **, int))(**v15)->RefCount)(*v15, 1);
  }
  v16 = (gbRefObject ***)(this + 21);
  if ( (unsigned __int8)CCBLineupWindow::OnMessage(this + 21) == 1 )
  {
    *a2 = 37;
    a2[1] = 132;
    a2[2] = 69;
    a2[3] = 164;
    ((void (__thiscall *)(gbRefObject **, int, _DWORD *, _DWORD *, char *, _DWORD))(**v16)[7].RefCount)(
      *v16,
      275,
      a2,
      this,
      aUiCombatContro_25,
      0);
    sub_440CE0(*v16, aUiCombatContro_28, 0);
    ((void (__thiscall *)(gbRefObject **, int))(**v16)->RefCount)(*v16, 1);
  }
  v17 = this + 25;
  CCBLineupWindow::Update(this + 25);
  *a2 = 68;
  a2[2] = 160;
  a2[1] = 170;
  a2[3] = 196;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, _DWORD *, char *, int, _DWORD))(*(_DWORD *)*v17 + 28))(
    *v17,
    282,
    a2,
    this,
    aUiCombatContro_32,
    1,
    0);
  (**(void (__thiscall ***)(_DWORD, int))*v17)(*v17, 1);
  return 1;
}

// 0x0051C110
int sub_51C110(int this)
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
  return result;
}

// 0x0051C1B0
BOOL sub_51C1B0(int a2, int a3)
{
  if ( *((_DWORD *)this + 14) == 1 && (MEMORY[0xBFC6F4] == 1 && (MEMORY[0xBFC6E8] & 0xF) == 1 || MEMORY[0xBFC704] == 1) )
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 8) + 1160) + 8), 272, -1, 0);
  return this->HitTest(a2, a3);
}

// 0x0051C210
_DWORD * sub_51C210()
{
  this->UIListBox();
  *this = &off_57058C;
  this->Reset();
  return this;
}
