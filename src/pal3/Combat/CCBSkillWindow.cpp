#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBSkillWindow.h"

// 0x0051C260
stdiobuf * sub_51C260(stdiobuf *Block, char a2)
{
  stdiobuf::~stdiobuf(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0051C2D0
int sub_51C2D0(_DWORD *this)
{
  *(this + 42) = 0;
  *(this + 43) = -1;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  memset(this + 27, 0, 0x2Cu);
  *(this + 38) = 0;
  *(this + 39) = 0;
  *(this + 40) = 0;
  *(this + 41) = 0;
  return 0;
}

// 0x0051C330
char sub_51C330(int this, _DWORD *a2, int a3)
{
  int v3; // ebx
  _DWORD *v5; // ebx
  LPCSTR *v6; // ebp
  gbRefObject ***v7; // ebx
  _DWORD *v8; // ebx
  _DWORD *v9; // eax
  _DWORD *v10; // ebx
  _DWORD *v11; // eax
  _DWORD *v12; // ebx
  _DWORD *v13; // eax
  _DWORD *v14; // ebx
  _DWORD *v15; // ebx
  _DWORD *v16; // ebx
  _DWORD *v17; // ebx
  _DWORD *v18; // ebx
  _DWORD *v19; // ebx
  _DWORD *v20; // ebx
  _DWORD *v21; // ebx
  _DWORD *v22; // ebx
  _DWORD v24[4]; // [esp+C8h] [ebp-10h] BYREF

  v3 = a3;
  (_DWORD *->Create()this, 512, a2, a3);
  *(_DWORD *)(this + 168) = v3;
  v5 = (_DWORD *)(this + 72);
  CCBLineupWindow::Destroy(this + 72);
  *a2 = 0;
  a2[2] = 256;
  a2[1] = 0;
  a2[3] = 256;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v5 + 16))(*v5, 513, a2, this);
  UIWnd::CreateFromTemplate(*(gbRefObject ***)(this + 72), aUiCombatResult, 0);
  (**(void (__thiscall ***)(_DWORD, int))*v5)(*v5, 1);
  v6 = (LPCSTR *)off_570310;
  v7 = (gbRefObject ***)(this + 108);
  do
  {
    v7->Destroy();
    *a2 = 15;
    a2[2] = 79;
    a2[1] = -15;
    a2[3] = 113;
    ((void (__thiscall *)(gbRefObject **, int, _DWORD *, int))(**v7)[4].RefCount)(*v7, 528, a2, this);
    UIWnd::CreateFromTemplate(*v7++, *v6++, 0);
  }
  while ( (int)v6 < (int)dword_570324 );
  (***(void (__thiscall ****)(_DWORD, int))(this + 108))(*(_DWORD *)(this + 108), 1);
  v8 = (_DWORD *)(this + 156);
  CCBLineupWindow::Render(this + 156);
  *a2 = 83;
  a2[2] = 168;
  a2[1] = 46;
  a2[3] = 58;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v8 + 16))(*v8, 545, a2, this);
  v9 = UIWnd::SetRect(*(_DWORD **)(this + 156), v24);
  UIWnd::AddChild(*(_DWORD **)(this + 156), v9);
  UIWnd::GetChildCount(*(gbRefObject ***)(this + 156), aUiCombatResult_4, 0);
  UIWnd::GetChildAt(*(gbRefObject ***)(this + 156), aUiCombatResult_1, 0);
  sub_43FD90(*(float **)(this + 156), 3);
  UIWnd::SetFrameRate(*(float **)(this + 156), -2);
  (**(void (__thiscall ***)(_DWORD, int))*v8)(*v8, 1);
  v10 = (_DWORD *)(this + 160);
  CCBLineupWindow::Render(this + 160);
  *a2 = 86;
  a2[2] = 171;
  a2[1] = 71;
  a2[3] = 83;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v10 + 16))(*v10, 546, a2, this);
  v11 = UIWnd::SetRect(*(_DWORD **)(this + 160), v24);
  UIWnd::AddChild(*(_DWORD **)(this + 160), v11);
  UIWnd::GetChildCount(*(gbRefObject ***)(this + 160), aUiCombatResult_4, 0);
  UIWnd::GetChildAt(*(gbRefObject ***)(this + 160), aUiCombatResult_2, 0);
  sub_43FD90(*(float **)(this + 160), 3);
  UIWnd::SetFrameRate(*(float **)(this + 160), -2);
  (**(void (__thiscall ***)(_DWORD, int))*v10)(*v10, 1);
  v12 = (_DWORD *)(this + 164);
  CCBLineupWindow::Render(this + 164);
  *a2 = 84;
  a2[2] = 169;
  a2[1] = 97;
  a2[3] = 109;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v12 + 16))(*v12, 547, a2, this);
  v13 = UIWnd::SetRect(*(_DWORD **)(this + 164), v24);
  UIWnd::AddChild(*(_DWORD **)(this + 164), v13);
  UIWnd::GetChildCount(*(gbRefObject ***)(this + 164), aUiCombatResult_4, 0);
  UIWnd::GetChildAt(*(gbRefObject ***)(this + 164), aUiCombatResult_3, 0);
  sub_43FD90(*(float **)(this + 164), 3);
  UIWnd::SetFrameRate(*(float **)(this + 164), -2);
  (**(void (__thiscall ***)(_DWORD, int))*v12)(*v12, 1);
  v14 = (_DWORD *)(this + 152);
  CCBLineupWindow::Destroy(this + 152);
  *a2 = 66;
  a2[2] = 130;
  a2[1] = 42;
  a2[3] = 109;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v14 + 16))(*v14, 544, a2, this);
  UIWnd::CreateFromTemplate(*(gbRefObject ***)(this + 152), aUiCombatResult_5, 0);
  (**(void (__thiscall ***)(_DWORD, int))*v14)(*v14, 1);
  v15 = (_DWORD *)(this + 76);
  a3 = -1;
  CCBLineupWindow::Destroy(this + 76);
  *a2 = 136;
  a2[2] = 200;
  a2[1] = 134;
  a2[3] = 166;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v15 + 16))(*v15, 514, a2, this);
  (**(void (__thiscall ***)(_DWORD, int))*v15)(*v15, 1);
  UIWnd::SetShow(*(_DWORD **)(this + 76), 0);
  UIWnd::GetChild(*(_DWORD **)(this + 76), &a3);
  v16 = (_DWORD *)(this + 80);
  CCBLineupWindow::Destroy(this + 80);
  *a2 = 51;
  a2[2] = 115;
  a2[1] = 134;
  a2[3] = 166;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v16 + 16))(*v16, 515, a2, this);
  (**(void (__thiscall ***)(_DWORD, int))*v16)(*v16, 1);
  UIWnd::SetShow(*(_DWORD **)(this + 80), 0);
  UIWnd::GetChild(*(_DWORD **)(this + 80), &a3);
  v17 = (_DWORD *)(this + 84);
  CCBLineupWindow::Destroy(this + 84);
  *a2 = 51;
  a2[2] = 115;
  a2[1] = 108;
  a2[3] = 140;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v17 + 16))(*v17, 516, a2, this);
  (**(void (__thiscall ***)(_DWORD, int))*v17)(*v17, 1);
  UIWnd::SetShow(*(_DWORD **)(this + 84), 0);
  UIWnd::GetChild(*(_DWORD **)(this + 84), &a3);
  v18 = (_DWORD *)(this + 88);
  CCBLineupWindow::Destroy(this + 88);
  *a2 = 136;
  a2[2] = 200;
  a2[1] = 108;
  a2[3] = 140;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v18 + 16))(*v18, 517, a2, this);
  (**(void (__thiscall ***)(_DWORD, int))*v18)(*v18, 1);
  UIWnd::SetShow(*(_DWORD **)(this + 88), 0);
  UIWnd::GetChild(*(_DWORD **)(this + 88), &a3);
  v19 = (_DWORD *)(this + 92);
  CCBLineupWindow::Destroy(this + 92);
  a2[2] = 115;
  *a2 = 51;
  a2[1] = 160;
  a2[3] = 192;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v19 + 16))(*v19, 518, a2, this);
  (**(void (__thiscall ***)(_DWORD, int))*v19)(*v19, 1);
  UIWnd::SetShow(*(_DWORD **)(this + 92), 0);
  UIWnd::GetChild(*(_DWORD **)(this + 92), &a3);
  v20 = (_DWORD *)(this + 96);
  CCBLineupWindow::Destroy(this + 96);
  *a2 = 136;
  a2[2] = 200;
  a2[1] = 160;
  a2[3] = 192;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v20 + 16))(*v20, 519, a2, this);
  (**(void (__thiscall ***)(_DWORD, int))*v20)(*v20, 1);
  UIWnd::SetShow(*(_DWORD **)(this + 96), 0);
  UIWnd::GetChild(*(_DWORD **)(this + 96), &a3);
  v21 = (_DWORD *)(this + 100);
  CCBLineupWindow::Destroy(this + 100);
  *a2 = 0;
  a2[2] = 187;
  a2[1] = 211;
  a2[3] = 243;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v21 + 16))(*v21, 529, a2, this);
  (**(void (__thiscall ***)(_DWORD, int))*v21)(*v21, 1);
  UIWnd::SetShow(*(_DWORD **)(this + 100), 0);
  UIWnd::GetChild(*(_DWORD **)(this + 100), &a3);
  v22 = (_DWORD *)(this + 104);
  CCBLineupWindow::Destroy(this + 104);
  *a2 = 0;
  a2[2] = 187;
  a2[1] = 0;
  a2[3] = 32;
  (*(void (__thiscall **)(_DWORD, int, _DWORD *, int))(*(_DWORD *)*v22 + 16))(*v22, 530, a2, this);
  (**(void (__thiscall ***)(_DWORD, int))*v22)(*v22, 1);
  UIWnd::SetShow(*(_DWORD **)(this + 104), 0);
  UIWnd::GetChild(*(_DWORD **)(this + 104), &a3);
  return 1;
}

// 0x0051C880
int sub_51C880(int this)
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
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx

  result = (gbRefObject **->SetScrollPos()this);
  v3 = (_DWORD *)(this + 108);
  v4 = 11;
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
  v7 = *(_DWORD *)(this + 80);
  if ( v7 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
    *(_DWORD *)(this + 80) = 0;
  }
  v8 = *(_DWORD *)(this + 84);
  if ( v8 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *(_DWORD *)(this + 84) = 0;
  }
  v9 = *(_DWORD *)(this + 88);
  if ( v9 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *(_DWORD *)(this + 88) = 0;
  }
  v10 = *(_DWORD *)(this + 92);
  if ( v10 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *(_DWORD *)(this + 92) = 0;
  }
  v11 = *(_DWORD *)(this + 96);
  if ( v11 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
    *(_DWORD *)(this + 96) = 0;
  }
  v12 = *(_DWORD *)(this + 100);
  if ( v12 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
    *(_DWORD *)(this + 100) = 0;
  }
  v13 = *(_DWORD *)(this + 104);
  if ( v13 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
    *(_DWORD *)(this + 104) = 0;
  }
  v14 = *(_DWORD *)(this + 152);
  if ( v14 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v14 + 20))(v14, 1);
    *(_DWORD *)(this + 152) = 0;
  }
  v15 = *(_DWORD *)(this + 156);
  if ( v15 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v15 + 20))(v15, 1);
    *(_DWORD *)(this + 156) = 0;
  }
  v16 = *(_DWORD *)(this + 160);
  if ( v16 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v16 + 20))(v16, 1);
    *(_DWORD *)(this + 160) = 0;
  }
  v17 = *(_DWORD *)(this + 164);
  if ( v17 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v17 + 20))(v17, 1);
    *(_DWORD *)(this + 164) = 0;
  }
  return result;
}

// 0x0051C9B0
int sub_51C9B0(_DWORD *this, int a2, int a3, int a4)
{
  if ( a2 == 1001 )
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3, a4, 0);
  return a2->SendMessage(a3, a4);
}

// 0x0051C9F0
BOOL sub_51C9F0(_DWORD *this, int a2, int a3)
{
  if ( *(this + 14) == 1 && MEMORY[0xBFC6F4] == 1 && (MEMORY[0xBFC6E8] & 0xF) == 1 )
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), 513, -1, 0);
  return this->HitTest(a2, a3);
}
