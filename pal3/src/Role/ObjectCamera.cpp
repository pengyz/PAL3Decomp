#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/ObjectCamera.h"

// Unnamed globals (extern)
extern float flt_DE4A00;

// 0x0047C570
// attributes: thunk
ObjectCamera::ObjectCamera()
{
}

// 0x0047C580
void ObjectCamera::_ObjectCamera()
{
  flt_DE4A00 = 12.0 + 12.0;
}

// 0x0047C590
float * ObjectCamera::Create()
{
  double x; // st7
  float y; // edx
  float z; // edx

  this->m_pCamera = 0;
  this->m_camFrom.x = 0.0;
  this->m_camFrom.y = 0.0;
  this->m_camFrom.z = 0.0;
  this->m_camTo.x = 0.0;
  this->m_camTo.y = 0.0;
  this->m_camTo.z = 0.0;
  this->m_camUp.x = 0.0;
  this->m_camUp.y = 0.0;
  this->m_camUp.z = 0.0;
  this->m_camDirect.x = 0.0;
  this->m_camDirect.y = 0.0;
  this->m_camDirect.z = 0.0;
  this->m_forward.x = 0.0;
  this->m_forward.y = 0.0;
  this->m_forward.z = 0.0;
  this->m_side.x = 0.0;
  this->m_side.y = 0.0;
  this->m_side.z = 0.0;
  this->m_camFrom.x = 0.0;
  this->m_camFrom.y = 0.0;
  this->m_camFrom.z = 800.0;
  x = this->m_camFrom.x;
  y = this->m_camFrom.y;
  this->m_camTo.z = 0.0;
  this->m_camTo.x = x;
  this->m_camTo.y = y;
  this->m_camUp.x = 0.0;
  this->m_camUp.y = 1.0;
  this->m_camUp.z = 0.0;
  z = this->m_camFrom.z;
  this->m_roll = 0.0;
  this->m_pitch = 0.0;
  this->m_yaw = 0.0;
  this->m_nroll = 0.0;
  this->m_npitch = 0.0;
  this->m_nyaw = 0.0;
  this->m_dist = z;
  this->m_stepRotMode = 0;
  this->m_stepRot = 0;
  this->m_stepRotSpeed = 0.15000001;
  this->m_bStepRot = 0;
  return (float *)this;
}

// 0x0047C630
// attributes: thunk
void ObjectCamera::GetCameraDirect()
{

}

// 0x0047C640
void ObjectCamera::SetCameraEyePosition(gbGfxManager *position)
{
  gbCamera *v3; // eax
  gbCamera *v4; // eax
  gbCamera *m_pCamera; // eax

  v3 = (gbCamera *)operator new(0x178u);
  if ( v3 )
    // [AUTO-COMMENTED] v4 = ((gbCamera *)v3)->gbCamera(position);
  else
    v4 = 0;
  this->m_pCamera = v4;
  ((gbCamera *)v4)->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  m_pCamera = this->m_pCamera;
  m_pCamera->OrthoSize = 0.0;
  m_pCamera->fov = 50.0;
  ((gbCamera *)this->m_pCamera)->SetLookAt(&this->m_camFrom, &this->m_camTo, &this->m_camUp);
}

// 0x0047C6E0
void ObjectCamera::SetCameraAtPosition(gbVec3D position, char pData)
{
  float y; // ecx
  double v5; // st7
  double v6; // st7
  gbVec3D v7; // [esp+0x4] [ebp-0xC] BYREF
  float positiona; // [esp+0x14] [ebp+0x4]
  float position_4; // [esp+0x18] [ebp+0x8]
  float position_8; // [esp+0x1C] [ebp+0xC]

  this->m_camFrom = position;
  if ( pData )
  {
    y = this->m_camFrom.y;
    this->m_camTo.x = this->m_camFrom.x;
    this->m_camTo.y = y;
    this->m_camTo.z = 0.0;
  }
  positiona = this->m_camTo.x - this->m_camFrom.x;
  v5 = this->m_camTo.y - this->m_camFrom.y;
  v7.x = positiona;
  position_4 = v5;
  v6 = this->m_camTo.z - this->m_camFrom.z;
  v7.y = position_4;
  position_8 = v6;
  v7.z = position_8;
  this->m_dist = ((gbVec3D *)&v7)->Length();
  this->ComputeInfo(1);
}

// 0x0047C770
void ObjectCamera::SetCameraRotate(float yaw, float pitch, float roll)
{
  double v5; // st7
  double v6; // st7
  gbVec3D v7; // [esp+0x4] [ebp-0xC] BYREF
  float yawa; // [esp+0x14] [ebp+0x4]
  float pitcha; // [esp+0x18] [ebp+0x8]
  float rolla; // [esp+0x1C] [ebp+0xC]

  this->m_camTo.x = yaw;
  this->m_camTo.y = pitch;
  this->m_camTo.z = roll;
  yawa = this->m_camTo.x - this->m_camFrom.x;
  v5 = this->m_camTo.y - this->m_camFrom.y;
  v7.x = yawa;
  pitcha = v5;
  v6 = this->m_camTo.z - this->m_camFrom.z;
  v7.y = pitcha;
  rolla = v6;
  v7.z = rolla;
  this->m_dist = ((gbVec3D *)&v7)->Length();
  this->ComputeInfo(1);
}

// 0x0047C7E0
void ObjectCamera::SetCameraDist(int dist, int nVal, int nVal2)
{
  LODWORD(this->m_yaw) = dist;
  LODWORD(this->m_nyaw) = dist;
  LODWORD(this->m_pitch) = nVal;
  LODWORD(this->m_npitch) = nVal;
  LODWORD(this->m_roll) = nVal2;
  LODWORD(this->m_nroll) = nVal2;
  this->ComputeInfo(1);
}

// 0x0047C810
void ObjectCamera::Destroy()
{
  if ( this->m_pCamera )
  {
    operator delete(this->m_pCamera);
    this->m_pCamera = 0;
  }
}

// 0x0047C830
void ObjectCamera::ComputeInfo(int from)
{
  long double v2; // st7
  long double v3; // st7
  long double v4; // st6
  long double v5; // st5
  double m_dist; // st4
  double v7; // st3
  double v8; // st2
  double v9; // st3
  double v10; // st4
  double v11; // st3
  double v12; // st7
  double v13; // st6
  double v14; // st5
  float v15; // [esp+0x0] [ebp-0x20]
  float v16; // [esp+0x4] [ebp-0x1C]
  float v17; // [esp+0x8] [ebp-0x18]
  float v18; // [esp+0xC] [ebp-0x14]
  float v19; // [esp+0x10] [ebp-0x10]
  float v20; // [esp+0x14] [ebp-0xC]
  float v21; // [esp+0x18] [ebp-0x8]
  float v22; // [esp+0x18] [ebp-0x8]
  float v23; // [esp+0x18] [ebp-0x8]
  float v24; // [esp+0x18] [ebp-0x8]
  float v25; // [esp+0x1C] [ebp-0x4]
  float v26; // [esp+0x1C] [ebp-0x4]
  float v27; // [esp+0x1C] [ebp-0x4]

  v2 = this->m_yaw * 0.017453292;
  v18 = this->m_pitch * 0.017453292;
  v19 = this->m_roll * 0.017453292;
  v17 = cos(v2);
  v15 = cos(v18);
  v16 = cos(v19);
  v3 = sin(v2);
  v4 = sin(v18);
  v5 = sin(v19);
  this->m_forward.x = v3 * v15;
  this->m_forward.y = v4;
  this->m_forward.z = -(v15 * v17);
  m_dist = this->m_dist;
  v20 = m_dist * this->m_forward.x;
  v21 = m_dist * this->m_forward.y;
  if ( from )
  {
    v7 = this->m_camTo.x - v20;
    v22 = this->m_camTo.y - v21;
    v8 = this->m_camTo.z - m_dist * this->m_forward.z;
    this->m_camFrom.y = v22;
    v25 = v8;
    this->m_camFrom.x = v7;
    this->m_camFrom.z = v25;
  }
  else
  {
    v23 = v21 + this->m_camFrom.y;
    v9 = m_dist * this->m_forward.z;
    v10 = v20 + this->m_camFrom.x;
    v11 = v9 + this->m_camFrom.z;
    this->m_camTo.y = v23;
    v26 = v11;
    this->m_camTo.x = v10;
    this->m_camTo.z = v26;
  }
  this->m_camUp.x = -(v5 * v17) - v4 * v3 * v16;
  this->m_camUp.y = v16 * v15;
  this->m_camUp.z = -(v5 * v3) - -(v4 * v16 * v17);
  v12 = this->m_camUp.z * this->m_forward.y - this->m_forward.z * this->m_camUp.y;
  v24 = this->m_forward.z * this->m_camUp.x - this->m_camUp.z * this->m_forward.x;
  v13 = this->m_camUp.y * this->m_forward.x;
  v14 = this->m_camUp.x * this->m_forward.y;
  this->m_side.y = v24;
  v27 = v13 - v14;
  this->m_side.x = v12;
  this->m_side.z = v27;
}

// 0x0047C9B0
void ObjectCamera::SetStepRotate()
{
  int m_stepRotMode; // eax
  int v3; // eax
  double v4; // st7
  double v5; // st7
  int v6; // eax
  double v7; // st7
  double v8; // st7
  float v9; // [esp+0x4] [ebp-0x4]
  float v10; // [esp+0x4] [ebp-0x4]
  float v11; // [esp+0x4] [ebp-0x4]
  float v12; // [esp+0x4] [ebp-0x4]

  if ( this->m_bStepRot )
  {
    m_stepRotMode = this->m_stepRotMode;
    if ( m_stepRotMode )
    {
      if ( m_stepRotMode == 1 )
      {
        v3 = *(_DWORD *)&this->m_stepRotAxis;
        if ( v3 )
        {
          if ( v3 == 1 )
          {
            v4 = this->m_stepRotSpeed + this->m_yaw;
            this->m_yaw = v4;
            v9 = *(float *)&this->m_stepRot + this->m_nyaw;
            if ( v4 >= v9 )
            {
              this->m_bStepRot = 0;
              this->m_yaw = v9;
              this->m_nyaw = v9;
            }
          }
        }
        else
        {
          v5 = this->m_stepRotSpeed + this->m_pitch;
          this->m_pitch = v5;
          v10 = *(float *)&this->m_stepRot + this->m_npitch;
          if ( v5 >= v10 )
          {
            this->m_bStepRot = 0;
            this->m_pitch = v10;
            this->m_npitch = v10;
          }
        }
      }
    }
    else
    {
      v6 = *(_DWORD *)&this->m_stepRotAxis;
      if ( v6 )
      {
        if ( v6 == 1 )
        {
          v7 = this->m_yaw - this->m_stepRotSpeed;
          this->m_yaw = v7;
          v11 = this->m_nyaw - *(float *)&this->m_stepRot;
          if ( v7 <= v11 )
          {
            this->m_bStepRot = 0;
            this->m_yaw = v11;
            this->m_nyaw = v11;
          }
        }
      }
      else
      {
        v8 = this->m_pitch - this->m_stepRotSpeed;
        this->m_pitch = v8;
        v12 = this->m_npitch - *(float *)&this->m_stepRot;
        if ( v8 <= v12 )
        {
          this->m_bStepRot = 0;
          this->m_pitch = v12;
          this->m_npitch = v12;
        }
      }
    }
    this->ComputeInfo(1);
  }
  ((gbCamera *)this->m_pCamera)->SetLookAt(&this->m_camFrom, &this->m_camTo, &this->m_camUp);
}

// 0x0047CAD0
void ObjectCamera::Update()
{
  this->m_camFrom.x = 0.0;
  this->m_camFrom.y = 0.0;
  this->m_camUp.y = 0.0;
  this->m_camUp.z = 0.0;
  this->m_camDirect.x = 0.0;
  this->m_camDirect.y = 0.0;
  this->m_camDirect.z = 0.0;
  this->m_yaw = 0.0;
  this->m_stepRotSpeed = 0.0;
  this->m_stepRot = 0;
  this->m_stepRotMode = 0;
  LOBYTE(this->m_pCamera) = 0;
  LOBYTE(this->m_camTo.y) = 0;
  this->m_camFrom.z = 0.0;
  this->m_dist = 0.0;
  this->m_roll = 0.0;
  this->m_pitch = 0.0;
  this->m_nroll = 0.0;
  this->m_npitch = 0.0;
  this->m_nyaw = 0.0;
  LOBYTE(this->m_forward.x) = 0;
  this->m_forward.y = 0.0;
  this->m_side.y = 0.0;
  this->m_side.x = 0.0;
  this->m_forward.z = 0.0;
  this->m_side.z = 0.0;
  this->m_bStepRot = 0;
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 35) = 0;
  *(&this->m_bStepRot + 1) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 33) = 0;
  *((_DWORD *)this + 34) = 1045220557;
}
