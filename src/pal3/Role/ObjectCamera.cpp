#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ObjectCamera.h"

// Forward declarations for unnamed functions
int sub_47C580(...);
int sub_47C590(...);
int sub_47C640(...);
int sub_47C6E0(...);
int sub_47C770(...);
int sub_47C7E0(...);
int sub_47C810(...);
int sub_47C830(...);
int sub_47C9B0(...);
int sub_47CAD0(...);

// Unnamed globals (extern)
extern float flt_DE4A00;

// 0x0047C570
// attributes: thunk
void ObjectCamera::ObjectCamera()
{
  ObjectCamera::~ObjectCamera();
}

// 0x0047C580
void sub_47C580()
{
  flt_DE4A00 = 12.0 + 12.0;
}

// 0x0047C590
float * sub_47C590()
{
  double v2; // st7
  float v3; // edx
  int v4; // edx

  *this = 0.0;
  *((_DWORD *)this + 1) = 0.0;
  *((_DWORD *)this + 2) = 0.0;
  *((_DWORD *)this + 3) = 0.0;
  *((_DWORD *)this + 4) = 0.0;
  *((_DWORD *)this + 5) = 0.0;
  *((_DWORD *)this + 6) = 0.0;
  *((_DWORD *)this + 7) = 0.0;
  *((_DWORD *)this + 8) = 0.0;
  *((_DWORD *)this + 9) = 0.0;
  *((_DWORD *)this + 10) = 0.0;
  *((_DWORD *)this + 11) = 0.0;
  *((_DWORD *)this + 12) = 0.0;
  *((_DWORD *)this + 20) = 0.0;
  *((_DWORD *)this + 21) = 0.0;
  *((_DWORD *)this + 22) = 0.0;
  *((_DWORD *)this + 23) = 0.0;
  *((_DWORD *)this + 24) = 0.0;
  *((_DWORD *)this + 25) = 0.0;
  *((_DWORD *)this + 1) = 0.0;
  *((_DWORD *)this + 2) = 0.0;
  *((_DWORD *)this + 3) = 800.0;
  v2 = *((_DWORD *)this + 1);
  v3 = *((_DWORD *)this + 2);
  *((_DWORD *)this + 6) = 0.0;
  *((_DWORD *)this + 4) = v2;
  *((_DWORD *)this + 5) = v3;
  *((_DWORD *)this + 7) = 0.0;
  *((_DWORD *)this + 8) = 1.0;
  *((_DWORD *)this + 9) = 0.0;
  v4 = *((_DWORD *)this + 3);
  *((_DWORD *)this + 15) = 0.0;
  *((_DWORD *)this + 14) = 0.0;
  *((_DWORD *)this + 13) = 0.0;
  *((_DWORD *)this + 19) = 0.0;
  *((_DWORD *)this + 18) = 0.0;
  *((_DWORD *)this + 17) = 0.0;
  *((_DWORD *)this + 16) = v4;
  *((_DWORD *)this + 28) = 0.0;
  *((_DWORD *)this + 27) = 0.0;
  *((_DWORD *)this + 26) = 0.15000001;
  *((_BYTE *)this + 120) = 0;
  return this;
}

// 0x0047C630
// attributes: thunk
void __thiscall ObjectCamera::GetCameraDirect(void **this)
{
  this->Destroy();
}

// 0x0047C640
void sub_47C640(gbCamera **this, struct gbGfxManager *a2)
{
  gbCamera *v3; // eax
  gbCamera *v4; // eax
  gbCamera *v5; // eax

  v3 = (gbCamera *)operator new(0x178u);
  if ( v3 )
    v4 = v3->gbCamera(a2);
  else
    v4 = 0;
  *this = v4;
  v4->SetDimention(MEMORY[0xBFD6D0], MEMORY[0xBFD6D4]);
  v5 = *this;
  *(_DWORD *)&v5->fov[4] = 0;
  *(_DWORD *)v5->fov = 1112014848;
  gbCamera::SetLookAt(*this, (struct gbVec3D *)(this + 1), (struct gbVec3D *)(this + 4), (struct gbVec3D *)(this + 7));
}

// 0x0047C6E0
int sub_47C6E0(int this, int a2, int a3, int a4, char a5)
{
  int v6; // ecx
  double v7; // st7
  double v8; // st7
  _DWORD v10[3]; // [esp+4h] [ebp-Ch] BYREF
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
  *(float *)v10 = v11;
  v12 = v7;
  v8 = *(float *)(this + 24) - *(float *)(this + 12);
  *(float *)&v10[1] = v12;
  v13 = v8;
  *(float *)&v10[2] = v13;
  *(float *)(this + 64) = (gbVec3D *->Length()v10);
  return ObjectCamera::ComputeInfo(1);
}

// 0x0047C770
int sub_47C770(int this, int a2, int a3, int a4)
{
  double v5; // st7
  double v6; // st7
  _DWORD v8[3]; // [esp+4h] [ebp-Ch] BYREF
  float v9; // [esp+14h] [ebp+4h]
  float v10; // [esp+18h] [ebp+8h]
  float v11; // [esp+1Ch] [ebp+Ch]

  *(_DWORD *)(this + 16) = a2;
  *(_DWORD *)(this + 20) = a3;
  *(_DWORD *)(this + 24) = a4;
  v9 = *(float *)(this + 16) - *(float *)(this + 4);
  v5 = *(float *)(this + 20) - *(float *)(this + 8);
  *(float *)v8 = v9;
  v10 = v5;
  v6 = *(float *)(this + 24) - *(float *)(this + 12);
  *(float *)&v8[1] = v10;
  v11 = v6;
  *(float *)&v8[2] = v11;
  *(float *)(this + 64) = (gbVec3D *->Length()v8);
  return ObjectCamera::ComputeInfo(1);
}

// 0x0047C7E0
int sub_47C7E0(int a2, int a3, int a4)
{
  *((_DWORD *)this + 13) = a2;
  *((_DWORD *)this + 17) = a2;
  *((_DWORD *)this + 14) = a3;
  *((_DWORD *)this + 18) = a3;
  *((_DWORD *)this + 15) = a4;
  *((_DWORD *)this + 19) = a4;
  return ObjectCamera::ComputeInfo(1);
}

// 0x0047C810
void sub_47C810(void **this)
{
  if ( *this )
  {
    operator delete(*this);
    *this = 0;
  }
}

// 0x0047C830
int sub_47C830(int a2)
{
  long double v2; // st7
  long double v3; // st7
  long double v4; // st6
  long double v5; // st5
  double v6; // st4
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

  v2 = *((_DWORD *)this + 13) * 0.017453292;
  v19 = *((_DWORD *)this + 14) * 0.017453292;
  v20 = *((_DWORD *)this + 15) * 0.017453292;
  v18 = cos(v2);
  v16 = cos(v19);
  v17 = cos(v20);
  v3 = sin(v2);
  v4 = sin(v19);
  v5 = sin(v20);
  *((_DWORD *)this + 20) = v3 * v16;
  *((_DWORD *)this + 21) = v4;
  *((_DWORD *)this + 22) = -(v16 * v18);
  v6 = *((_DWORD *)this + 16);
  v21 = v6 * *((_DWORD *)this + 20);
  v22 = v6 * *((_DWORD *)this + 21);
  if ( a2 )
  {
    v7 = *((_DWORD *)this + 4) - v21;
    v23 = *((_DWORD *)this + 5) - v22;
    v8 = *((_DWORD *)this + 6) - v6 * *((_DWORD *)this + 22);
    *((_DWORD *)this + 2) = v23;
    v26 = v8;
    *((_DWORD *)this + 1) = v7;
    *((_DWORD *)this + 3) = v26;
  }
  else
  {
    v24 = v22 + *((_DWORD *)this + 2);
    v9 = v6 * *((_DWORD *)this + 22);
    v10 = v21 + *((_DWORD *)this + 1);
    v11 = v9 + *((_DWORD *)this + 3);
    *((_DWORD *)this + 5) = v24;
    v27 = v11;
    *((_DWORD *)this + 4) = v10;
    *((_DWORD *)this + 6) = v27;
  }
  *((_DWORD *)this + 7) = -(v5 * v18) - v4 * v3 * v17;
  *((_DWORD *)this + 8) = v17 * v16;
  *((_DWORD *)this + 9) = -(v5 * v3) - -(v4 * v17 * v18);
  v12 = *((_DWORD *)this + 9) * *((_DWORD *)this + 21) - *((_DWORD *)this + 22) * *((_DWORD *)this + 8);
  v25 = *((_DWORD *)this + 22) * *((_DWORD *)this + 7) - *((_DWORD *)this + 9) * *((_DWORD *)this + 20);
  v13 = *((_DWORD *)this + 8) * *((_DWORD *)this + 20);
  v14 = *((_DWORD *)this + 7) * *((_DWORD *)this + 21);
  *((_DWORD *)this + 24) = v25;
  v28 = v13 - v14;
  *((_DWORD *)this + 23) = v12;
  *((_DWORD *)this + 25) = v28;
  return LODWORD(v25);
}

// 0x0047C9B0
void sub_47C9B0(int this)
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
    (float *->ComputeInfo()this, 1);
  }
  gbCamera::SetLookAt(
    *(gbCamera **)this,
    (struct gbVec3D *)(this + 4),
    (struct gbVec3D *)(this + 16),
    (struct gbVec3D *)(this + 28));
}

// 0x0047CAD0
void sub_47CAD0()
{
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 0;
  *((_DWORD *)this + 8) = 0;
  *((_DWORD *)this + 9) = 0;
  *((_DWORD *)this + 10) = 0;
  *((_DWORD *)this + 11) = 0;
  *((_DWORD *)this + 12) = 0;
  *((_DWORD *)this + 13) = 0;
  *((_DWORD *)this + 26) = 0;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 28) = 0;
  *(_BYTE *)this = 0;
  *((_BYTE *)this + 20) = 0;
  *((_DWORD *)this + 3) = 0;
  *((_DWORD *)this + 16) = 0;
  *((_DWORD *)this + 15) = 0;
  *((_DWORD *)this + 14) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 17) = 0;
  *((_BYTE *)this + 80) = 0;
  *((_DWORD *)this + 21) = 0;
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 23) = 0;
  *((_DWORD *)this + 22) = 0;
  *((_DWORD *)this + 25) = 0;
  *((_BYTE *)this + 120) = 0;
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 35) = 0;
  *((_BYTE *)this + 121) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 33) = 0;
  *((_DWORD *)this + 34) = 1045220557;
}
