#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ParabolaCalculator.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/PalScriptMgr.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_4A1CF0(...);
int sub_523820(...);

// 0x00523600
int ParabolaCalculator::CalulateParabola()
{
  int result; // eax
  gbVec3D v2; // [esp-20h] [ebp-68h]
  int v3; // [esp-14h] [ebp-5Ch]
  int v4; // [esp-10h] [ebp-58h]
  int v5; // [esp-Ch] [ebp-54h]
  int v6; // [esp+0h] [ebp-48h] BYREF
  struct gbTextureArray v7; // [esp+4h] [ebp-44h] BYREF

  result = *((_DWORD *)this + 439);
  if ( result )
  {
    v7.pTexPt[0] = (gbTexture *)*((_DWORD *)this + 439);
    v7.nTex = 1;
    *(_WORD *)((char *)&v6 + 1) = -1;
    LOBYTE(v6) = -1;
    v5 = *((_DWORD *)this + 441);
    v4 = *((_DWORD *)this + 440);
    v3 = *((_DWORD *)this + 21);
    v2 = *(gbVec3D *)((_BYTE *)this + 6);
    HIBYTE(v6) = 62;
    UIRenderQuad(SLODWORD(v2.x), SLODWORD(v2.y), SLODWORD(v2.z), v3, v4, v5, &v6, &v7);
  }
  return result;
}

// 0x00523670
int ParabolaCalculator::UpdateParabola(int _this)
{
  int result; // eax

  ParabolaCalculator::CalulateParabola((ParabolaCalculator *)this);
  result = *(_DWORD *)(this + 1752);
  switch ( result )
  {
    case 0:
      result = UIListBox::SetScroll((UIListBox *)this);
      break;
    case 1:
      result = (*(int (**)(_DWORD))(**(_DWORD **)(this + 1736) + 4))(*(_DWORD *)(this + 1736));
      break;
    case 2:
      result = (*(int (**)(_DWORD))(**(_DWORD **)(this + 1740) + 4))(*(_DWORD *)(this + 1740));
      break;
    case 3:
      result = (*(int (**)(_DWORD))(**(_DWORD **)(this + 1744) + 4))(*(_DWORD *)(this + 1744));
      break;
    case 4:
      result = (*(int (**)(_DWORD))(**(_DWORD **)(this + 1748) + 4))(*(_DWORD *)(this + 1748));
      break;
    default:
      return result;
  }
  return result;
}

// 0x005236E0
int ParabolaCalculator::UpdateParabolaY(int _this, int a2, int a3)
{
  char *Instance; // eax
  gbAudioManager *AudioManager; // eax
  int result; // eax

  if ( g_Input.KeyInfo[177].PressTime != 2 && (g_nGameFlags & 1) != 0 )
  {
    Instance = (char *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)CScreenMode::GetAudioManager((CScreenMode *)Instance);
    AudioManager->DetachAll3D();
  }
  if ( !sub_4A1CF0((_DWORD *)(this + 368)) )
    sub_523820((_DWORD *)this, 2);
  switch ( *(_DWORD *)(this + 1752) )
  {
    case 0:
      UIWnd::HitTest((UIWnd *)this, a2, a3);
      result = 1;
      break;
    case 1:
      (*(void (**)(_DWORD, int, int))(**(_DWORD **)(this + 1736) + 8))(*(_DWORD *)(this + 1736), a2, a3);
      result = 1;
      break;
    case 2:
      a2->RunSceneScript();
      (*(void (**)(_DWORD, int, int))(**(_DWORD **)(this + 1740) + 8))(*(_DWORD *)(this + 1740), a2, a3);
      result = 1;
      break;
    case 3:
      (*(void (**)(_DWORD, int, int))(**(_DWORD **)(this + 1744) + 8))(*(_DWORD *)(this + 1744), a2, a3);
      result = 1;
      break;
    case 4:
      (*(void (**)(_DWORD, int, int))(**(_DWORD **)(this + 1748) + 8))(*(_DWORD *)(this + 1748), a2, a3);
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
