#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ParabolaCalculator.h"

// 0x00523600
int sub_523600(_DWORD *this)
{
  int result; // eax
  int v2; // [esp-20h] [ebp-68h]
  int v3; // [esp-1Ch] [ebp-64h]
  int v4; // [esp-18h] [ebp-60h]
  int v5; // [esp-14h] [ebp-5Ch]
  int v6; // [esp-10h] [ebp-58h]
  int v7; // [esp-Ch] [ebp-54h]
  _BYTE v8[4]; // [esp+0h] [ebp-48h] BYREF
  _DWORD v9[17]; // [esp+4h] [ebp-44h] BYREF

  result = *(this + 439);
  if ( result )
  {
    v9[0] = *(this + 439);
    v9[16] = 1;
    v8[2] = -1;
    v8[1] = -1;
    v8[0] = -1;
    v7 = *(this + 441);
    v6 = *(this + 440);
    v5 = *(this + 21);
    v4 = *(this + 20);
    v3 = *(this + 19);
    v2 = *(this + 18);
    v8[3] = 62;
    return UIRenderQuad(v2, v3, v4, v5, v6, v7, v8, v9);
  }
  return result;
}

// 0x00523670
int sub_523670(int this)
{
  int result; // eax

  (_DWORD *->CalulateParabola()this);
  result = *(_DWORD *)(this + 1752);
  switch ( result )
  {
    case 0:
      result = (int *->SetScroll()this);
      break;
    case 1:
      result = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)(this + 1736) + 4))(*(_DWORD *)(this + 1736));
      break;
    case 2:
      result = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)(this + 1740) + 4))(*(_DWORD *)(this + 1740));
      break;
    case 3:
      result = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)(this + 1744) + 4))(*(_DWORD *)(this + 1744));
      break;
    case 4:
      result = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)(this + 1748) + 4))(*(_DWORD *)(this + 1748));
      break;
    default:
      return result;
  }
  return result;
}

// 0x005236E0
int sub_5236E0(int this, int a2, int a3)
{
  int v4; // eax
  gbAudioManager *v5; // eax
  int result; // eax

  if ( g_nGameState != 2 && (g_nGameFlags & 1) != 0 )
  {
    v4 = this->GetInstance();
    v5 = (gbAudioManager *)v4->GetAudioManager();
    v5->DetachAll3D();
  }
  if ( !sub_4A1CF0((_DWORD *)(this + 368)) )
    sub_523820(2);
  switch ( *(_DWORD *)(this + 1752) )
  {
    case 0:
      (_DWORD *->HitTest()this, a2, a3);
      result = 1;
      break;
    case 1:
      (*(void (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 1736) + 8))(*(_DWORD *)(this + 1736), a2, a3);
      result = 1;
      break;
    case 2:
      a2->RunSceneScript();
      (*(void (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 1740) + 8))(*(_DWORD *)(this + 1740), a2, a3);
      result = 1;
      break;
    case 3:
      (*(void (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 1744) + 8))(*(_DWORD *)(this + 1744), a2, a3);
      result = 1;
      break;
    case 4:
      (*(void (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 1748) + 8))(*(_DWORD *)(this + 1748), a2, a3);
      result = 1;
      break;
    case 5:
      CGameData_Load((int)&g_GameData, 0);
      result = 1;
      break;
    case 6:
      CGameData_Load((int)&g_GameData, 4);
      goto LABEL_14;
    default:
LABEL_14:
      result = 1;
      break;
  }
  return result;
}
