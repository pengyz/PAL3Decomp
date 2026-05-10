#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCCTData.h"
#include "pal3/gen/CCBStageCam.h"

// Forward declarations for unnamed functions
int sub_41CA30(...);

// 0x0041C900
void CCCTData::CalcDist(float a1, float a2)
{
  double v2; // st7
  float *v3; // ecx
  long double v4; // st6
  double v5; // st7
  float v6; // [esp+0h] [ebp-10h]
  float v7; // [esp+4h] [ebp-Ch]
  float v8; // [esp+1Ch] [ebp+Ch]
  gbVec3D v9; // [esp+20h] [ebp+10h] BYREF
  int v10; // [esp+2Ch] [ebp+1Ch]
  int v11; // [esp+30h] [ebp+20h]

  v2 = v9.x - a1;
  v3 = (float *)v10;
  v6 = v9.z - v8;
  v4 = atan2(-(v2 / v6), 1.0);
  *(float *)v10 = v4;
  if ( v9.z > (double)v8 )
    * v3 = (*)v4 + 3.1415927;
  v7 = v2;
  v9.x = v7;
  v9.z = v6;
  *(float *)&v10 = v9.y - a2;
  LODWORD(v9.y) = v10;
  v5 = ((gbVec3D *)&v9)->Length();
  *(float *)v11 = asin(*(float *)&v10 / v5);
}

// 0x005044C0
int CCCTData::UpdateCamera(int a2)
{
  return sub_41CA30(
           this,
           *(_DWORD *)(a2 + 12),
           *(_DWORD *)(a2 + 16),
           *(_DWORD *)(a2 + 20),
           *(_DWORD *)a2,
           *(_DWORD *)(a2 + 4),
           *(_DWORD *)(a2 + 8));
}

// 0x00506260
int CCCTData::Save(int a2)
{
  int result; // eax
  int v4; // esi
  float *v5; // edx
  char *v6; // eax

  result = ((CCBStageCam *)this)->IsEditorCamValid(a2);
  if ( result > 0 )
  {
    v4 = result;
    v5 = (float *)&this->m_Pool[1385].StartPos.fFromY + 50 * a2;
    do
    {
      if ( *(_DWORD *)v5 == -1 )
        v6 = 0;
      else
        v6 = (char *)this + 204 * *(_DWORD *)v5;
      v6[21] = 0;
      if ( *(_DWORD *)v5 == -1 )
        result = 0;
      else
        result = (int)this + 204 * *(_DWORD *)v5;
      ++v5;
      --v4;
      *(_BYTE *)(result + 22) = 0;
    }
    while ( v4 );
  }
  return result;
}
