#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/MiniGame2Scene.h"

// Unnamed globals (extern)
extern int dword_17AF5A8;
extern int dword_17AF5AC;
extern int dword_17AF5B0;
extern int dword_17AF5B8;
extern int dword_17AF5BC;
extern int dword_17AF5C0;
void __cdecl nullsub_69(void);
void __cdecl nullsub_70(void);

// 0x0052FBD0
gbOBBox * MiniGame2Scene::GetOBBox()
{
  gbOBBox *v2; // edi

  v2 = (gbOBBox *)(this + 913);
  ((gbGeomNode *)(this + 834))->GetOBBox((gbOBBox *)(this + 913));
  *((float *)this + 925) = *((float *)this + 907) + *((float *)this + 925);
  *((float *)this + 926) = *((float *)this + 908) + *((float *)this + 926);
  *((float *)this + 927) = *((float *)this + 909) + *((float *)this + 927);
  return v2;
}

// 0x0052FE30
void MiniGame2Scene::UpdateMiniGame2(float fDeltaTime)
{
  MiniGame2Scene *v3; // edi
  int v4; // ebx
  int v5; // edi
  MiniGame2Scene *v6; // ebp
  double v7; // st7
  float *v8; // eax
  double v9; // st7
  double v10; // st6
  float v11; // edx
  double v12; // st7
  int v13; // ecx
  double v14; // st7
  float v15; // ecx
  double v16; // st7
  float v17; // edx
  double v18; // st7
  double v19; // st7
  long double v20; // st7
  double v21; // st7
  char v23; // c0
  gbVec3D v24; // [esp+0x10] [ebp-0x30] BYREF
  gbVec3D v25; // [esp+0x1C] [ebp-0x24] BYREF
  float v26; // [esp+0x28] [ebp-0x18]
  float v27; // [esp+0x2C] [ebp-0x14]
  float v28; // [esp+0x30] [ebp-0x10]
  float v29; // [esp+0x34] [ebp-0xC]
  float v30; // [esp+0x38] [ebp-0x8]
  float v31; // [esp+0x3C] [ebp-0x4]
v4 = 6;
  do
  {
    (*(void ( **)(MiniGame2Scene *))(*(_DWORD *)v3 + 20))(v3);
    v3 += 70;
    --v4;
  }
  while ( v4 );
  v5 = 0;
  v6 = this + 556;
  do
  {
    if ( *((_BYTE *)this + v5 + 3328) )
      (*(void ( **)(MiniGame2Scene *))(*(_DWORD *)v6 + 20))(v6);
    ++v5;
    v6 += 70;
  }
  while ( v5 < 3 );
  v7 = fDeltaTime * 6.0 + *((float *)this + 833);
  *((float *)this + 833) = v7;
  if ( v7 >= 360.0 )
    *((_DWORD *)this + 833) = 0;
  if ( *((_BYTE *)this + 3744) )
  {
    v8 = (float *)((ArcSceneMonster *)(this + 937))->CheckDistance(*((float *)this + 932));
    if ( v8 )
    {
      v9 = *v8 - *((float *)this + 907);
      v30 = v8[1] - *((float *)this + 908);
      v10 = v8[2] - *((float *)this + 909);
      *((float *)this + 911) = v30;
      v31 = v10;
      v11 = v31;
      *((float *)this + 910) = v9;
      *((float *)this + 912) = v11;
      ((gbVec3D *)(this + 910))->Normalize();
      v12 = *((float *)this + 933) * *((float *)this + 910);
      v13 = *((_DWORD *)this + 907);
      *(this + 905) = *(this + 908);
      *((_DWORD *)this + 904) = v13;
      *(this + 906) = *(this + 909);
      v14 = v12 * fDeltaTime + *((float *)this + 907);
      v26 = *((float *)this + 904);
      v15 = *((float *)this + 905);
      *((float *)this + 907) = v14;
      v16 = *((float *)this + 911) * *((float *)this + 933);
      v17 = *((float *)this + 906);
      v27 = v15;
      v28 = v17;
      *((float *)this + 908) = v16 * fDeltaTime + *((float *)this + 908);
      *((float *)this + 909) = *((float *)this + 912) * *((float *)this + 933) * fDeltaTime + *((float *)this + 909);
      v29 = *((float *)this + 907);
      v30 = *((float *)this + 908);
      v31 = *((float *)this + 909);
      *((float *)this + 932) = sqrt((v26 - v29) * (v26 - v29) + (v27 - v30) * (v27 - v30) + (v28 - v31) * (v28 - v31))
                             + *((float *)this + 932);
      v29 = *((float *)this + 907) - *((float *)this + 904);
      v18 = *((float *)this + 908) - *((float *)this + 905);
      v25.x = v29;
      v30 = v18;
      v19 = *((float *)this + 909) - *((float *)this + 906);
      v25.y = v30;
      v31 = v19;
      v25.z = v31;
      ((gbVec3D *)&v25)->Normalize();
      v24 = v25;
      ((gbVec3D *)&v24)->Normalize();
      if ( (g_bgbGeomNodeFlag_17AF5C4 & 1) == 0 )
      {
        dword_17AF5B8 = 0;
        g_bgbGeomNodeFlag_17AF5C4 |= 1u;
        dword_17AF5BC = 0;
        dword_17AF5C0 = 1065353216;
        atexit(nullsub_70);
      }
      v20 = acos(v24.z * *(float *)&dword_17AF5C0 + v24.y * *(float *)&dword_17AF5BC + *(float *)&dword_17AF5B8 * v24.x);
      *((float *)this + 934) = v20;
      if ( v24.x < 0.0 )
        *((float *)this + 934) = 6.2831855 - v20;
      *((float *)this + 934) = *((float *)this + 934) * 57.29578;
      if ( (g_bgbGeomNodeFlag_17AF5C4 & 2) == 0 )
      {
        dword_17AF5A8 = 0;
        g_bgbGeomNodeFlag_17AF5C4 |= 2u;
        dword_17AF5AC = 1065353216;
        dword_17AF5B0 = 0;
        atexit(nullsub_69);
      }
      *((float *)this + 935) = acos(
                                 v24.z * *(float *)&dword_17AF5B0
                               + v24.y * *(float *)&dword_17AF5AC
                               + *(float *)&dword_17AF5A8 * v24.x)
                             * 57.29578;
      ((gbGeomNode *)(this + 834))->GetTotalOBBox((gbOBBox *)(this + 913));
      *((float *)this + 925) = *((float *)this + 925) + *((float *)this + 907);
      *((float *)this + 926) = *((float *)this + 926) + *((float *)this + 908);
      *((float *)this + 927) = *((float *)this + 927) + *((float *)this + 909);
      v21 = *((float *)this + 940) + 16.0;
      *((float *)this + 940) = v21;
      if ( !v23 )
        *((float *)this + 940) = 360.0 - v21;
      (*(void ( **)(MiniGame2Scene *))(*((_DWORD *)this + 834) + 20))(this + 834);
    }
    else
    {
      *((_BYTE *)this + 3744) = 0;
    }
  }
}
