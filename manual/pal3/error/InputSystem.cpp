#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/InputSystem.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Misc/PtrArray.h"
#include "Misc/RoleCameraCtrl.h"
#include "Scene/Scene.h"
#include "Effect/ScreenEffect.h"
#include "Effect/ScreenEffectMgr.h"
#include "Misc/SystemUI.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

class RoleCameraCtrl;

// Unnamed globals (extern)
extern RoleCameraCtrl stru_DBA134;

// 0x00410360
void InputSystem::ProcessFrame(char *pInputState)
{
  ScreenEffectMgr *v1; // ecx
  ScreenEffect *Instance; // eax
  GRPinput *v3; // eax
  GRPinput *v4; // esi
  int v5; // eax
  void **v6; // ecx

  Instance = (((ScreenEffectMgr *)v1))->ScreenEffectMgr::GetInstance();
  if ( !(((ScreenEffectMgr *)Instance))->ScreenEffectMgr::IsFadeWhiteHolding() )
  {
    v3 = (GRPinput *)operator new(0x24u);
    if ( v3 )
      v4 = (((GRPinput *)v3))->GRPinput::SetMousePos();
    else
      v4 = 0;
    (((GRPinput *)v4))->GRPinput::SetJoystickPos(pInputState, 1);
    v5 = nIndex - 1;
    if ( nIndex - 1 >= 0 )
    {
      v6 = (void **)&g_pScriptObjArray[v5];
      while ( *((_DWORD *)*v6 + 7) != 1 )
      {
        --v5;
        --v6;
        if ( v5 < 0 )
          goto LABEL_11;
      }
      (((GRPinput *)v4))->GRPinput::GetMouseSensitivity(*((_DWORD *)*v6 + 8) + 24);
    }
LABEL_11:
    (((RoleCameraCtrl *)&stru_DBA134))->RoleCameraCtrl::ShowWindow(0);
    (((PtrArray *)&g_pScriptObjArray))->PtrArray::SetAt(nIndex, (int)v4);
  }
}

// 0x0041C540
void InputSystem::ProcessMouse(int nVal)
{
  int v1; // ecx
  int v2; // esi
  Scene *v3; // eax
  float v4; // st7
  float v5; // st7
  float v6; // [esp+0x4] [ebp-0x1C]
  float v7; // [esp+0x4] [ebp-0x1C]
  int item[2]; // [esp+0x8] [ebp-0x18] BYREF
  float v9; // [esp+0x10] [ebp-0x10]
  float v10; // [esp+0x14] [ebp-0xC]
  int v11; // [esp+0x18] [ebp-0x8]
  float v12; // [esp+0x1C] [ebp-0x4]

  v2 = v1;
  item[0] = 0;
  item[1] = 0;
  v9 = 0.0f;
  v10 = 0.0f;
  v11 = 0;
  v12 = 0.0f;
  v3 = UISceneUpdate();
  if ( (((SystemUI *)v3))->SystemUI::GetNoteItemData(item) )
  {
    v4 = v10 - 120.0f;
    v6 = *(float *)item + 120.0f;
    if ( v4 < *(float *)(v2 + 480) )
      *(float *)(v2 + 480) = v4;
    if ( *(float *)(v2 + 480) < (double)v6 )
      *(float *)(v2 + 480) = v6;
    v5 = v12 - 120.0f;
    v7 = v9 + 120.0f;
    if ( v5 < *(float *)(v2 + 488) )
      *(float *)(v2 + 488) = v5;
    if ( *(float *)(v2 + 488) < (double)v7 )
      *(float *)(v2 + 488) = v7;
  }
}

// 0x0041C9A0
int InputSystem::SetCameraTransition(
        
        int nMode,
        int nStart,
        int nTarget,
        int nPosX,
        int nPosY,
        int nPosZ,
        int bTargetCoord)
{
  int result; // eax

  *(_DWORD *)&this[12]._tail_000[20] = nStart;
  *(_DWORD *)this[13]._tail_000 = nTarget;
  *(_DWORD *)&this[12]._tail_000[24] = nMode;
  *(_DWORD *)&this[12]._tail_000[28] = 0;
  if ( bTargetCoord )
  {
    *(_DWORD *)&this[13]._tail_000[24] = nPosX;
    *(_DWORD *)&this[13]._tail_000[28] = nPosY;
    *(_DWORD *)&this[13]._tail_000[32] = nPosZ;
    this->InputSystem::ProcessKeyboard(bTargetCoord == 0);
  }
  else
  {
    *(_DWORD *)&this[13]._tail_000[12] = nPosX;
    *(_DWORD *)&this[13]._tail_000[16] = nPosY;
    *(_DWORD *)&this[13]._tail_000[20] = nPosZ;
    this->InputSystem::ProcessKeyboard(1);
  }
  return result;
}
