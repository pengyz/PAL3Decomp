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

// Unnamed globals (extern)
extern int dword_BFDA6C;

// 0x00523600
int ParabolaCalculator::CalulateParabola()
{
  int result; // eax
  int d048; // [esp-20h] [ebp-68h]
  int d04C; // [esp-1Ch] [ebp-64h]
  int d050; // [esp-18h] [ebp-60h]
  int d054; // [esp-14h] [ebp-5Ch]
  int v6; // [esp-10h] [ebp-58h]
  int v7; // [esp-Ch] [ebp-54h]
  int v8; // [esp+0h] [ebp-48h] BYREF
  struct gbTextureArray v9; // [esp+4h] [ebp-44h] BYREF

  result = *((_DWORD *)this + 439);
  if ( result )
  {
    v9.pTexPt[0] = (gbTexture *)*((_DWORD *)this + 439);
    v9.nTex = 1;
    *(_WORD *)((char *)&v8 + 1) = -1;
    LOBYTE(v8) = -1;
    v7 = *((_DWORD *)this + 441);
    v6 = *((_DWORD *)this + 440);
    d054 = this->_d054;
    d050 = this->_d050;
    d04C = this->_d04C;
    d048 = this->_d048;
    HIBYTE(v8) = 62;
    UIRenderQuad(d048, d04C, d050, d054, v6, v7, &v8, &v9);
  }
  return result;
}

// 0x00523670
int ParabolaCalculator::UpdateParabola()
{
  int result; // eax

  this->CalulateParabola();
  result = *((_DWORD *)this + 438);
  switch ( result )
  {
    case 0:
      result = ((UIListBox *)this)->SetScroll();
      break;
    case 1:
      result = (*(int (**)(_DWORD))(**((_DWORD **)this + 434) + 4))(*((_DWORD *)this + 434));
      break;
    case 2:
      result = (*(int (**)(_DWORD))(**((_DWORD **)this + 435) + 4))(*((_DWORD *)this + 435));
      break;
    case 3:
      result = (*(int (**)(_DWORD))(**((_DWORD **)this + 436) + 4))(*((_DWORD *)this + 436));
      break;
    case 4:
      result = (*(int (**)(_DWORD))(**((_DWORD **)this + 437) + 4))(*((_DWORD *)this + 437));
      break;
    default:
      return result;
  }
  return result;
}

// 0x005236E0
int ParabolaCalculator::UpdateParabolaY(int a2, int a3)
{
  char *Instance; // eax
  gbAudioManager *AudioManager; // eax
  int result; // eax

  if ( dword_BFDA6C != 2 && (g_nGameFlags & 1) != 0 )
  {
    Instance = (char *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    AudioManager->DetachAll3D();
  }
  if ( !sub_4A1CF0(&this->_tail[280]) )
    sub_523820(this, 2);
  switch ( *((_DWORD *)this + 438) )
  {
    case 0:
      ((UIWnd *)this)->HitTest(a2, a3);
      result = 1;
      break;
    case 1:
      (*(void (**)(_DWORD, int, int))(**((_DWORD **)this + 434) + 8))(*((_DWORD *)this + 434), a2, a3);
      result = 1;
      break;
    case 2:
      a2->RunSceneScript();
      (*(void (**)(_DWORD, int, int))(**((_DWORD **)this + 435) + 8))(*((_DWORD *)this + 435), a2, a3);
      result = 1;
      break;
    case 3:
      (*(void (**)(_DWORD, int, int))(**((_DWORD **)this + 436) + 8))(*((_DWORD *)this + 436), a2, a3);
      result = 1;
      break;
    case 4:
      (*(void (**)(_DWORD, int, int))(**((_DWORD **)this + 437) + 8))(*((_DWORD *)this + 437), a2, a3);
      result = 1;
      break;
    case 5:
      CGameData_Load((int)&g_GameData, 0);
      result = 1;
      break;
    case 6:
      CGameData_Load((int)&g_GameData, (CUtil *)4);
      goto LABEL_14;
    default:
LABEL_14:
      result = 1;
      break;
  }
  return result;
}
