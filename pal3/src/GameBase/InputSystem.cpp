#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/InputSystem.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations

// Unnamed globals (extern)
extern RoleCameraCtrl stru_DBA134;

// 0x00410360
void InputSystem::ProcessFrame()
{
  ScreenEffectMgr *v1; // ecx
  ScreenEffect *Instance; // eax
  GRPinput *v3; // eax
  GRPinput *v4; // esi
  int v5; // eax
  void **v6; // ecx

  Instance = ((ScreenEffectMgr *)v1)->GetInstance();
  if ( !((ScreenEffectMgr *)Instance)->IsFadeWhiteHolding() )
  {
    v3 = (GRPinput *)operator new(0x24u);
    if ( v3 )
      v4 = ((GRPinput *)v3)->SetMousePos();
    else
      v4 = 0;
    ((GRPinput *)v4)->SetJoystickPos(pInputState, 1);
    v5 = (int)g_pScriptEventObj - 1;
    if ( (int)g_pScriptEventObj - 1 >= 0 )
    {
      v6 = &g_pScriptObjArray[v5];
      while ( *((_DWORD *)*v6 + 7) != 1 )
      {
        --v5;
        --v6;
        if ( v5 < 0 )
          goto LABEL_11;
      }
      ((GRPinput *)v4)->GetMouseSensitivity(*((_DWORD *)*v6 + 8) + 24);
    }
LABEL_11:
    ((RoleCameraCtrl *)&stru_DBA134)->ShowWindow();
    ((PtrArray *)&g_pScriptObjArray)->SetAt((int)g_pScriptEventObj, (int)v4);
  }
}

// 0x0041C540
void InputSystem::ProcessMouse(int nVal)
{
  int v1; // ecx
  int v2; // esi
  SystemUI *v3; // eax
  double v4; // st7
  double v5; // st7
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
  v9 = 0.0;
  v10 = 0.0;
  v11 = 0;
  v12 = 0.0;
  v3 = (SystemUI *)UISceneUpdate();
  if ( ((SystemUI *)v3)->GetNoteItemData(item) )
  {
    v4 = v10 - 120.0;
    v6 = *(float *)item + 120.0;
    if ( v4 < *(float *)(v2 + 480) )
      *(float *)(v2 + 480) = v4;
    if ( *(float *)(v2 + 480) < (double)v6 )
      *(float *)(v2 + 480) = v6;
    v5 = v12 - 120.0;
    v7 = v9 + 120.0;
    if ( v5 < *(float *)(v2 + 488) )
      *(float *)(v2 + 488) = v5;
    if ( *(float *)(v2 + 488) < (double)v7 )
      *(float *)(v2 + 488) = v7;
  }
}

// 0x0041C710
void InputSystem::InputSystem::ProcessKeyboard()
{
  long double v1; // st7
  long double v2; // st6
  long double v3; // st5
  double v4; // st5
  double v5; // st4
  double v6; // st3
  double v7; // st4
  double v8; // st5
  double v9; // st4
  double v10; // st7
  double v11; // st6
  double v12; // st5
  float v13; // [esp+0x0] [ebp-0x1C]
  float v14; // [esp+0x4] [ebp-0x18]
  float v15; // [esp+0x8] [ebp-0x14]
  float v16; // [esp+0xC] [ebp-0x10]
  float v17; // [esp+0x10] [ebp-0xC]
  float v18; // [esp+0x14] [ebp-0x8]
  float v19; // [esp+0x14] [ebp-0x8]
  float v20; // [esp+0x14] [ebp-0x8]
  float v21; // [esp+0x14] [ebp-0x8]
  float v22; // [esp+0x18] [ebp-0x4]
  float v23; // [esp+0x18] [ebp-0x4]
  float v24; // [esp+0x18] [ebp-0x4]
  int v25; // [esp+0x20] [ebp+0x4]

  v1 = cos(*((float *)this + 114));
  v2 = cos(*((float *)this + 113));
  v15 = cos(*((float *)this + 116));
  v13 = sin(*((float *)this + 114));
  v14 = sin(*((float *)this + 113));
  v3 = sin(*((float *)this + 116));
  *((float *)this + 127) = v14;
  v16 = v3;
  *((float *)this + 126) = v13 * v2;
  *((float *)this + 128) = -(v2 * v1);
  v4 = *((float *)this + 117);
  v17 = v4 * *((float *)this + 126);
  v18 = v4 * *((float *)this + 127);
  if ( v25 )
  {
    v5 = *((float *)this + 120) - v17;
    v19 = *((float *)this + 121) - v18;
    v6 = *((float *)this + 122) - v4 * *((float *)this + 128);
    *((float *)this + 124) = v19;
    v22 = v6;
    *((float *)this + 123) = v5;
    *((float *)this + 125) = v22;
  }
  else
  {
    v20 = v18 + *((float *)this + 124);
    v7 = v4 * *((float *)this + 128);
    v8 = v17 + *((float *)this + 123);
    v9 = v7 + *((float *)this + 125);
    *((float *)this + 121) = v20;
    v23 = v9;
    *((float *)this + 120) = v8;
    *((float *)this + 122) = v23;
  }
  *((float *)this + 129) = -(v16 * v1) - v14 * v13 * v15;
  *((float *)this + 130) = v15 * v2;
  *((float *)this + 131) = -(v16 * v13) - -(v14 * v15 * v1);
  v10 = *((float *)this + 131) * *((float *)this + 127) - *((float *)this + 128) * *((float *)this + 130);
  v21 = *((float *)this + 128) * *((float *)this + 129) - *((float *)this + 131) * *((float *)this + 126);
  v11 = *((float *)this + 126) * *((float *)this + 130);
  v12 = *((float *)this + 129) * *((float *)this + 127);
  *((float *)this + 133) = v21;
  v24 = v11 - v12;
  *((float *)this + 132) = v10;
  *((float *)this + 134) = v24;
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

  *((_DWORD *)this + 113) = nStart;
  *((_DWORD *)this + 117) = nTarget;
  *((_DWORD *)this + 114) = nMode;
  *((_DWORD *)this + 115) = 0;
  if ( bTargetCoord )
  {
    *((_DWORD *)this + 123) = nPosX;
    *((_DWORD *)this + 124) = nPosY;
    *((_DWORD *)this + 125) = nPosZ;
  }
  else
  {
    *((_DWORD *)this + 120) = nPosX;
    *((_DWORD *)this + 121) = nPosY;
    *((_DWORD *)this + 122) = nPosZ;
  }

  return result;
}
