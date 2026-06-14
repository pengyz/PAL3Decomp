#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/RoleCamera.h"

// Forward declarations for unnamed functions
int sub_445FA0(void *a2); // from annotations

// 0x0041D410
int RoleCamera::PushState()
{
  float v2; // eax
  void **v3; // eax
  float y; // eax
  float v5; // eax
  float v6; // edx
  float v7; // ecx
  float v8; // edi
  float v9; // edx
  float v10; // eax
  int v11; // ecx
  float m_nextYAW; // eax
  float v13; // eax
  double v14; // st7
  float v15; // ecx
  float v16; // edx
  float v17; // eax
  float v18; // ecx
  float v19; // edx
  float v20; // eax
  int result; // eax
  float m_pitch; // [esp-0x8] [ebp-0x40]
  float z; // [esp+0xC] [ebp-0x2C] BYREF
  float m_yaw; // [esp+0x10] [ebp-0x28]
  float m_fCtrlYaw; // [esp+0x14] [ebp-0x24]
  int m_dist; // [esp+0x18] [ebp-0x20]
  float v27[7]; // [esp+0x1C] [ebp-0x1C] BYREF

  z = this->m_fromVec.z;
  m_yaw = this->m_yaw;
  m_fCtrlYaw = this->m_fCtrlYaw;
  m_dist = this->m_dist;
  ((CameraCtrl *)&z)->SetupCameraArray(-1);
  v2 = this->m_fCtrlYaw;
  qmemcpy(v27, (const void *)LODWORD(m_fCtrlYaw), sizeof(v27));
  if ( LODWORD(v2) == LODWORD(this->m_fromVec.z) )
  {
    v3 = (void **)this->m_dist;
    this->m_dist = (int)(v3 - 1);
    operator delete(*v3);
    if ( LODWORD(this->m_nextYAW) )
    {
      ((CameraCtrl *)&z)->SetCameraSource(*(_DWORD *)this->m_dist + 4088, (int *)this->m_dist);
      v9 = m_yaw;
      v10 = m_fCtrlYaw;
      this->m_fromVec.z = z;
      v11 = m_dist;
      this->m_yaw = v9;
      this->m_fCtrlYaw = v10;
      this->m_dist = v11;
    }
    else
    {
      y = this->m_fromVec.y;
      if ( LODWORD(y) == this->m_dist )
        operator delete(*(void **)LODWORD(y));
      ((PalScriptMgr *)&z)->Get_result();
      v5 = z;
      v6 = m_fCtrlYaw;
      v7 = m_yaw;
      v8 = *(float *)&m_dist;
      this->m_lastFrom.y = z;
      this->m_fromVec.z = v5;
      this->m_yaw = v7;
      this->m_fCtrlYaw = v6;
      this->m_lastFrom.z = v7;
      *(float *)&this->m_dist = v8;
      this->m_fromVec.x = v6;
      m_pitch = this->m_pitch;
      this->m_fromVec.y = v8;
      operator delete((void *)LODWORD(m_pitch));
    }
  }
  m_nextYAW = this->m_nextYAW;
  if ( m_nextYAW != 0.0 )
    LODWORD(this->m_fCtrlYaw) -= 28;
  LODWORD(v13) = LODWORD(m_nextYAW) - 1;
  this->m_nextYAW = v13;
  if ( v13 == 0.0 )
    ((CameraCtrl *)&this->m_lastFrom)->PopState();
  v14 = v27[0];
  v15 = v27[3];
  v16 = v27[1];
  v17 = v27[2];
  this->Wscreen = 0.0;
  this->OrthoSize = v14;
  *(float *)&this->m_argstack[4] = v15;
  v18 = v27[6];
  this->m_camVelocity.y = v16;
  v19 = v27[4];
  this->m_camVelocity.x = v17;
  v20 = v27[5];
  *(float *)&this->m_argstack[24] = v18;
  *(float *)&this->m_argstack[16] = v19;
  *(float *)&this->m_argstack[20] = v20;
  ((InputSystem *)this)->InputSystem::ProcessKeyboard();
  return result;
}

// 0x0044D180
int RoleCamera::InitParticles()
{
  DWORD Time; // eax
  float *p_y; // esi
  int v4; // ebp
  int result; // eax
  int v6; // [esp+0xC] [ebp-0x4]

  Time = timeGetTime();
  CRT_set_new_handler(Time);
  p_y = &this->m_lastUP.y;
  v4 = 22;
  do
  {
    *((_DWORD *)p_y - 4) = rand() % 160 + 238;
    v6 = rand() % 500 + 150;
    *((_DWORD *)p_y - 5) = v6;
    *(p_y - 1) = (float)v6;
    *((_DWORD *)p_y - 3) = *(_DWORD *)p_y + *((_DWORD *)p_y - 5);
    *((_DWORD *)p_y - 2) = *((_DWORD *)p_y - 4) + *((_DWORD *)p_y + 1);
    p_y[2] = (double)(rand() % 16) * 0.1 + 1.0;
    p_y[3] = (float)(rand() % 255);
    p_y[4] = (double)(rand() % 10 + 10) * 0.1;
    *((_BYTE *)p_y + 20) = 1;
    *((_DWORD *)p_y + 6) = rand() % 3;
    *((_DWORD *)p_y + 8) = 30;
    p_y[7] = *(p_y - 4);
    result = sub_445FA0(p_y - 43);
    p_y += 52;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x00534CF0
void RoleCamera::UpdateAudioListener(int nVal, int nVal2)
{
  gbVec3D *p_z; // ebx
  const gbVec3D *p_y; // ebp
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v8; // edi

  p_z = (gbVec3D *)&this->m_lastUP.z;
  p_y = (const gbVec3D *)&this->m_LockCenter.y;
  ((gbCamera *)&this->OrthoSize)->SetLookAt((gbVec3D *)&this->m_LockCenter.y, (gbVec3D *)&this->m_roomHeight, (gbVec3D *)&this->m_lastUP.z);
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    v8 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->SetListenerPosition(p_y);
      ((gbAudioManager *)v8)->SetListenerOrientation((gbVec3D *)&this->m_side.y, p_z);
    }
  }
}
