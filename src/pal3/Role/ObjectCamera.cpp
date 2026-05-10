#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ObjectCamera.h"

// Unnamed globals (extern)
extern float flt_DE4A00;

// 0x0047C570
// attributes: thunk
void ObjectCamera::ObjectCamera()
{
  ObjectCamera::~ObjectCamera();
}

// 0x0047C580
ObjectCamera::~ObjectCamera()
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
  this->m_stepRot = 0.0;
  this->m_stepRotSpeed = 0.15000001;
  LOBYTE(this->m_bStepRot) = 0;
  return (float *)this;
}

// 0x0047C630
// attributes: thunk
void ObjectCamera::GetCameraDirect(ObjectCamera **this)
{
  this->Destroy();
}

// 0x0047C640
void ObjectCamera::SetCameraEyePosition(ObjectCamera **this, struct gbGfxManager *a2)
{
  gbCamera *v3; // eax
  ObjectCamera *v4; // eax
  ObjectCamera *v5; // eax

  v3 = (gbCamera *)operator new(0x178u);
  if ( v3 )
    v4 = (ObjectCamera *)v3->gbCamera(a2);
  else
    v4 = 0;
  *this = v4;
  (gbCamera *->SetDimention()v4, g_Input.KeyInfo[120].Data, g_Input.KeyInfo[120].HoldTime);
  v5 = (ObjectCamera *)*this;
  v5->m_camFrom.x = 0.0;
  v5->m_pCamera = (gbCamera *)1112014848;
  (gbCamera *->SetLookAt()*this,
    (struct gbVec3D *)(this + 1),
    (struct gbVec3D *)(this + 4),
    (struct gbVec3D *)(this + 7));
}

// 0x0047C6E0
int ObjectCamera::SetCameraAtPosition(int _this, int a2, int a3, int a4, char a5)
{
  int v6; // ecx
  double v7; // st7
  double v8; // st7
  gbVec3D v10; // [esp+4h] [ebp-Ch] BYREF
  float v11; // [esp+14h] [ebp+4h]
  float v12; // [esp+18h] [ebp+8h]
  float v13; // [esp+1Ch] [ebp+Ch]

  *(_DWORD *)(this + 4) = a2;
  *(_DWORD *)(this + 8) = a3;
  *(_DWORD *)(this + 12) = a4;
  if ( a5 )
  {
    v6 = *(_DWORD *)(this + 8);
    *(_DWORD *)(this + 16) = *(_DWORD *)(this + 4);
    *(_DWORD *)(this + 20) = v6;
    *(_DWORD *)(this + 24) = 0;
  }
  v11 = *(float *)(this + 16) - *(float *)(this + 4);
  v7 = *(float *)(this + 20) - *(float *)(this + 8);
  v10.x = v11;
  v12 = v7;
  v8 = *(float *)(this + 24) - *(float *)(this + 12);
  v10.y = v12;
  v13 = v8;
  v10.z = v13;
  *(float *)(this + 64) = gbVec3D::Length(&v10);
  return (ObjectCamera *->ComputeInfo()this, 1);
}

// 0x0047C770
int ObjectCamera::SetCameraRotate(int _this, int a2, int a3, int a4)
{
  double v5; // st7
  double v6; // st7
  gbVec3D v8; // [esp+4h] [ebp-Ch] BYREF
  float v9; // [esp+14h] [ebp+4h]
  float v10; // [esp+18h] [ebp+8h]
  float v11; // [esp+1Ch] [ebp+Ch]

  *(_DWORD *)(this + 16) = a2;
  *(_DWORD *)(this + 20) = a3;
  *(_DWORD *)(this + 24) = a4;
  v9 = *(float *)(this + 16) - *(float *)(this + 4);
  v5 = *(float *)(this + 20) - *(float *)(this + 8);
  v8.x = v9;
  v10 = v5;
  v6 = *(float *)(this + 24) - *(float *)(this + 12);
  v8.y = v10;
  v11 = v6;
  v8.z = v11;
  *(float *)(this + 64) = gbVec3D::Length(&v8);
  return (ObjectCamera *->ComputeInfo()this, 1);
}

// 0x0047C7E0
int ObjectCamera::SetCameraDist(int a2, int a3, int a4)
{
  LODWORD(this->m_yaw) = a2;
  LODWORD(this->m_nyaw) = a2;
  LODWORD(this->m_pitch) = a3;
  LODWORD(this->m_npitch) = a3;
  LODWORD(this->m_roll) = a4;
  LODWORD(this->m_nroll) = a4;
  return this->ComputeInfo(1);
}

// 0x0047C810
void ObjectCamera::Destroy(ObjectCamera **this)
{
  if ( *this )
  {
    operator delete(*this);
    *this = 0;
  }
}

// 0x0047C830
int ObjectCamera::ComputeInfo(int a2)
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
  float v16; // [esp+0h] [ebp-20h]
  float v17; // [esp+4h] [ebp-1Ch]
  float v18; // [esp+8h] [ebp-18h]
  float v19; // [esp+Ch] [ebp-14h]
  float v20; // [esp+10h] [ebp-10h]
  float v21; // [esp+14h] [ebp-Ch]
  float v22; // [esp+18h] [ebp-8h]
  float v23; // [esp+18h] [ebp-8h]
  float v24; // [esp+18h] [ebp-8h]
  float v25; // [esp+18h] [ebp-8h]
  float v26; // [esp+1Ch] [ebp-4h]
  float v27; // [esp+1Ch] [ebp-4h]
  float v28; // [esp+1Ch] [ebp-4h]

  v2 = this->m_yaw * 0.017453292;
  v19 = this->m_pitch * 0.017453292;
  v20 = this->m_roll * 0.017453292;
  v18 = cos(v2);
  v16 = cos(v19);
  v17 = cos(v20);
  v3 = sin(v2);
  v4 = sin(v19);
  v5 = sin(v20);
  this->m_forward.x = v3 * v16;
  this->m_forward.y = v4;
  this->m_forward.z = -(v16 * v18);
  m_dist = this->m_dist;
  v21 = m_dist * this->m_forward.x;
  v22 = m_dist * this->m_forward.y;
  if ( a2 )
  {
    v7 = this->m_camTo.x - v21;
    v23 = this->m_camTo.y - v22;
    v8 = this->m_camTo.z - m_dist * this->m_forward.z;
    this->m_camFrom.y = v23;
    v26 = v8;
    this->m_camFrom.x = v7;
    this->m_camFrom.z = v26;
  }
  else
  {
    v24 = v22 + this->m_camFrom.y;
    v9 = m_dist * this->m_forward.z;
    v10 = v21 + this->m_camFrom.x;
    v11 = v9 + this->m_camFrom.z;
    this->m_camTo.y = v24;
    v27 = v11;
    this->m_camTo.x = v10;
    this->m_camTo.z = v27;
  }
  this->m_camUp.x = -(v5 * v18) - v4 * v3 * v17;
  this->m_camUp.y = v17 * v16;
  this->m_camUp.z = -(v5 * v3) - -(v4 * v17 * v18);
  v12 = this->m_camUp.z * this->m_forward.y - this->m_forward.z * this->m_camUp.y;
  v25 = this->m_forward.z * this->m_camUp.x - this->m_camUp.z * this->m_forward.x;
  v13 = this->m_camUp.y * this->m_forward.x;
  v14 = this->m_camUp.x * this->m_forward.y;
  this->m_side.y = v25;
  v28 = v13 - v14;
  this->m_side.x = v12;
  this->m_side.z = v28;
  return LODWORD(v25);
}

// 0x0047C9B0
void ObjectCamera::SetStepRotate(int _this)
{
  int v2; // eax
  int v3; // eax
  double v4; // st7
  double v5; // st7
  int v6; // eax
  double v7; // st7
  double v8; // st7
  float v9; // [esp+4h] [ebp-4h]
  float v10; // [esp+4h] [ebp-4h]
  float v11; // [esp+4h] [ebp-4h]
  float v12; // [esp+4h] [ebp-4h]

  if ( *(_BYTE *)(this + 120) )
  {
    v2 = *(_DWORD *)(this + 112);
    if ( v2 )
    {
      if ( v2 == 1 )
      {
        v3 = *(_DWORD *)(this + 116);
        if ( v3 )
        {
          if ( v3 == 1 )
          {
            v4 = *(float *)(this + 104) + *(float *)(this + 52);
            *(float *)(this + 52) = v4;
            v9 = *(float *)(this + 108) + *(float *)(this + 68);
            if ( v4 >= v9 )
            {
              *(_BYTE *)(this + 120) = 0;
              *(float *)(this + 52) = v9;
              *(float *)(this + 68) = v9;
            }
          }
        }
        else
        {
          v5 = *(float *)(this + 104) + *(float *)(this + 56);
          *(float *)(this + 56) = v5;
          v10 = *(float *)(this + 108) + *(float *)(this + 72);
          if ( v5 >= v10 )
          {
            *(_BYTE *)(this + 120) = 0;
            *(float *)(this + 56) = v10;
            *(float *)(this + 72) = v10;
          }
        }
      }
    }
    else
    {
      v6 = *(_DWORD *)(this + 116);
      if ( v6 )
      {
        if ( v6 == 1 )
        {
          v7 = *(float *)(this + 52) - *(float *)(this + 104);
          *(float *)(this + 52) = v7;
          v11 = *(float *)(this + 68) - *(float *)(this + 108);
          if ( v7 <= v11 )
          {
            *(_BYTE *)(this + 120) = 0;
            *(float *)(this + 52) = v11;
            *(float *)(this + 68) = v11;
          }
        }
      }
      else
      {
        v8 = *(float *)(this + 56) - *(float *)(this + 104);
        *(float *)(this + 56) = v8;
        v12 = *(float *)(this + 72) - *(float *)(this + 108);
        if ( v8 <= v12 )
        {
          *(_BYTE *)(this + 120) = 0;
          *(float *)(this + 56) = v12;
          *(float *)(this + 72) = v12;
        }
      }
    }
    (ObjectCamera *->ComputeInfo()this, 1);
  }
  gbCamera::SetLookAt(
    *(gbCamera **)this,
    (struct gbVec3D *)(this + 4),
    (struct gbVec3D *)(this + 16),
    (struct gbVec3D *)(this + 28));
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
  this->m_stepRot = 0.0;
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
  LOBYTE(this->m_bStepRot) = 0;
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 35) = 0;
  BYTE1(this->m_bStepRot) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 33) = 0;
  *((_DWORD *)this + 34) = 1045220557;
}
