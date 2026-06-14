#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ArcPastScene.h"

// 0x00533B50
bool ArcPastScene::LoadCityData()
{
  int v1; // esi
  int v2; // ebx
  __int64 v3; // rax

  v1 = *(_DWORD *)&this->cityname[8];
  v2 = (__int64)((*(float *)&this->name[4] - *(float *)(v1 + 128)) / g_fSceneScale);
  v3 = (__int64)((*(float *)&this->name[12] - *(float *)(v1 + 136)) / g_fSceneScale);
  return v2 >= 0
      && v2 < *(_DWORD *)(v1 + 152)
      && (int)v3 >= 0
      && (int)v3 < *(_DWORD *)(v1 + 156)
      && *(_BYTE *)(*(_DWORD *)(v1 + 160) + 8 * (v2 + v3 * *(_DWORD *)(v1 + 152)) + 5) == 3;
}

// 0x00534F50
int ArcPastScene::ResetCityName()
{
  this->name[0] = 0;
  *(_DWORD *)&this->cityname[28] = 0;
  *(_DWORD *)&this->cityname[24] = 0;
  *(_DWORD *)&this->name[8] = 0;
  *(_DWORD *)&this->name[12] = 0;
  *(_DWORD *)&this->name[20] = 0;
  this->name[28] = 1;
  this->name[29] = 1;
  this->name[30] = 0;
  ((PalScript *)this)->ResetAll();
  return (int)this->cityname;
}

// 0x00534FB0
void ArcPastScene::FreeChildList()
{
  ((ArcLocaleRole *)this)->Destroy();
  if ( *(_DWORD *)&this->name[12] )
  {
    operator delete(*(void **)&this->name[12]);
    *(_DWORD *)&this->name[12] = 0;
  }
}
