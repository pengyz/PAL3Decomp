#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Scene.h"
#include "pal3/gen/Array.h"

// Unnamed globals (extern)
extern int nullsub_2;

// 0x00410990
int Scene::LoadConfig(void *pConfig)
{
  char *v3; // ecx
  char *v4; // edi
  int v5; // ebx
  unsigned int v6; // ebp
  int v7; // edx
  unsigned int v8; // eax
  int v9; // eax
  char *v10; // ebp
  int i; // ebx
  int v12; // eax
  int result; // eax
  int v14; // ecx
  char *v15; // ecx
  char *v16; // eax
  char *v17; // edi
  unsigned int v18; // [esp+10h] [ebp-8h]
  int v19; // [esp+14h] [ebp-4h]

  v3 = (char *)*(char **)&this->m_info.cityname[8];
  v4 = v3;
  if ( (*(_DWORD *)&this->m_info.cityname[12] - (int)v3) / 12 )
  {
    v3->Insert(v3, v3 + 12);
    ((Array *)*(void **)&this->m_info.cityname[8])->Erase(1 - (*(_DWORD *)&this->m_info.cityname[8] - (int)v4) / 12, pConfig);
    v15 = (char *)*(char **)&this->m_info.cityname[8];
    v16 = v4;
    if ( v4 == v15 )
    {
      result = *(_DWORD *)&this->m_info.cityname[8] + 12;
      *(_DWORD *)&this->m_info.cityname[8] = result;
    }
    else
    {
      do
      {
        v17 = v16;
        v16 += 12;
        *(_DWORD *)v17 = *(_DWORD *)pConfig;
        *((_DWORD *)v17 + 1) = *((_DWORD *)pConfig + 1);
        *((_DWORD *)v17 + 2) = *((_DWORD *)pConfig + 2);
      }
      while ( v16 != v15 );
      result = *(_DWORD *)&this->m_info.cityname[8] + 12;
      *(_DWORD *)&this->m_info.cityname[8] = result;
    }
  }
  else
  {
    v5 = *(_DWORD *)&this->m_info.cityname[4];
    if ( !v5 || (v6 = (int)&v3[-v5] / 12, v6 <= 1) )
      v6 = 1;
    if ( v5 )
      v7 = (int)&v3[-v5] / 12;
    else
      v7 = 0;
    v8 = v7 + v6;
    v18 = v7 + v6;
    if ( (int)(v7 + v6) < 0 )
      v8 = 0;
    v9 = ((operator *)12 * v8)->new();
    v10 = (char *)*(char **)&this->m_info.cityname[4];
    v19 = v9;
    for ( i = v9; v10 != v4; i += 12 )
    {
      ((void *)i)->Copy(v10);
      v10 += 12;
    }
    ((void *)i)->Erase(1, pConfig);
    v4->Insert(*(void **)&this->m_info.cityname[8], (void *)(i + 12));
    nullsub_2(*(_DWORD *)&this->m_info.cityname[4], *(_DWORD *)&this->m_info.cityname[8]);
    operator delete(*(void **)&this->m_info.cityname[4]);
    *(_DWORD *)&this->m_info.cityname[12] = v19 + 12 * v18;
    v12 = *(_DWORD *)&this->m_info.cityname[4];
    if ( v12 )
    {
      v14 = *(_DWORD *)&this->m_info.cityname[8];
      *(_DWORD *)&this->m_info.cityname[4] = v19;
      result = v19 + 4 * (3 * ((v14 - v12) / 12) + 3);
      *(_DWORD *)&this->m_info.cityname[8] = result;
    }
    else
    {
      *(_DWORD *)&this->m_info.cityname[4] = v19;
      *(_DWORD *)&this->m_info.cityname[8] = v19 + 12;
      return v19 + 12;
    }
  }
  return result;
}
