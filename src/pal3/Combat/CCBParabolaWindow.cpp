#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBParabolaWindow.h"

// 0x0051B710
char sub_51B710(gbRefObject ***this, int *a2, int a3)
{
  gbRefObject ***v4; // edi
  gbRefObject ***v5; // ebx
  int i; // edi
  int v7; // eax
  int v8; // ecx

  this->Create(1879048197, a2, a3);
  *(this + 30) = (gbRefObject **)a3;
  v4 = this + 23;
  if ( (unsigned __int8)CCBLineupWindow::Destroy(this + 23) == 1 )
  {
    *a2 = 0;
    a2[2] = 230;
    a2[1] = 0;
    a2[3] = 250;
    ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(**v4)[4].RefCount)(*v4, 240, a2, this);
    UIWnd::CreateFromTemplate(*v4, aUiCombatContro_21, 0);
    ((void (__thiscall *)(gbRefObject **, int))(**v4)->RefCount)(*v4, 1);
  }
  v5 = this + 24;
  for ( i = 0; i < 5; ++i )
  {
    if ( (unsigned __int8)v5->Destroy() )
    {
      v7 = dword_57026C[i];
      v8 = dword_570250[i];
      *a2 = v8;
      a2[1] = v7;
      a2[2] = v8 + 40;
      a2[3] = v7 + 38;
      ((void (__thiscall *)(gbRefObject **, int, int *, gbRefObject ***))(**v5)[4].RefCount)(
        *v5,
        dword_57014C[i],
        a2,
        this);
      UIWnd::CreateFromTemplate(*v5, off_570284[i], 0);
      sub_4425D0(*v5, off_570298[i], 0);
      ((void (__thiscall *)(gbRefObject **, int))(**v5)->RefCount)(*v5, 1);
    }
    ++v5;
  }
  return 1;
}

// 0x0051B810
int sub_51B810(int this)
{
  int result; // eax
  int v3; // ecx
  _DWORD *v4; // esi
  int v5; // edi

  result = (gbRefObject **->SetScrollPos()this);
  v3 = *(_DWORD *)(this + 92);
  if ( v3 )
  {
    result = (*(int (__thiscall **)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *(_DWORD *)(this + 92) = 0;
  }
  v4 = (_DWORD *)(this + 96);
  v5 = 5;
  do
  {
    if ( *v4 )
    {
      result = (*(int (__thiscall **)(_DWORD, int))(*(_DWORD *)*v4 + 20))(*v4, 1);
      *v4 = 0;
    }
    ++v4;
    --v5;
  }
  while ( v5 );
  return result;
}

// 0x0051B860
int sub_51B860(_DWORD *this, int a2, int a3, int a4)
{
  if ( a2 == 1001 )
  {
    this->GetInstance();
    aWa001->AudioSetPosition(1);
    CCBUI::SetParam(*(_DWORD *)(*(_DWORD *)(*(this + 8) + 1160) + 8), a3, a4, 0);
  }
  return a2->SendMessage(a3, a4);
}

// 0x0051B920
int sub_51B920(int *this)
{
  int v2; // ecx

  this->SetScroll();
  v2 = *(this + *(this + 29) + 24);
  return (*(int (__thiscall **)(int))(*(_DWORD *)v2 + 4))(v2);
}

// 0x0051B950
bool sub_51B950(_DWORD **this, int a2, int a3, int a4)
{
  _DWORD *v4; // eax
  _DWORD v6[4]; // [esp+8h] [ebp-10h] BYREF

  v4 = UIWnd::SetRect(*(this + a2 + 24), v6);
  return a3 >= *v4 && a3 < v4[2] && a4 >= v4[1] && a4 < v4[3];
}

// 0x0051B9A0
int sub_51B9A0(_DWORD **this, int a2, int a3)
{
  int v4; // esi
  _DWORD **i; // edi

  v4 = 0;
  for ( i = this + 24; (*i)[14] != 1 || !this->OnMessage(v4, a2, a3); ++i )
  {
    if ( ++v4 >= 5 )
      return -1;
  }
  return v4;
}
