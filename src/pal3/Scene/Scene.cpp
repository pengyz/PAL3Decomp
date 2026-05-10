#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Scene.h"
#include "pal3/gen/Array.h"

// Unnamed globals (extern)
extern int nullsub_2;

// 0x00410990
int Scene::LoadConfig(void *pConfig)
{
  char *m_pDataEnd; // ecx
  char *v4; // edi
  _BYTE *m_pDataBegin; // ebx
  unsigned int v6; // ebp
  int v7; // edx
  unsigned int v8; // eax
  _DWORD *v9; // eax
  char *v10; // ebp
  _DWORD *i; // ebx
  _BYTE *v12; // eax
  int result; // eax
  _BYTE *v14; // ecx
  char *v15; // ecx
  char *v16; // eax
  char *v17; // edi
  unsigned int v18; // [esp+10h] [ebp-8h]
  _DWORD *v19; // [esp+14h] [ebp-4h]

  m_pDataEnd = (char *)this->m_pDataEnd;
  v4 = m_pDataEnd;
  if ( ((char *)this->m_pCapacity - (char *)m_pDataEnd) / 12 )
  {
    m_pDataEnd->Insert(m_pDataEnd, m_pDataEnd + 12);
    ((Array *)this->m_pDataEnd)->Erase(1 - ((char *)this->m_pDataEnd - (char *)v4) / 12, pConfig);
    v15 = (char *)this->m_pDataEnd;
    v16 = v4;
    if ( v4 == v15 )
    {
      result = (int)this->m_pDataEnd + 12;
      this->m_pDataEnd = (void *)result;
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
      result = (int)this->m_pDataEnd + 12;
      this->m_pDataEnd = (void *)result;
    }
  }
  else
  {
    m_pDataBegin = (_BYTE *)this->m_pDataBegin;
    if ( !m_pDataBegin || (v6 = (m_pDataEnd - m_pDataBegin) / 12, v6 <= 1) )
      v6 = 1;
    if ( m_pDataBegin )
      v7 = (m_pDataEnd - m_pDataBegin) / 12;
    else
      v7 = 0;
    v8 = v7 + v6;
    v18 = v7 + v6;
    if ( (int)(v7 + v6) < 0 )
      v8 = 0;
    v9 = (_DWORD *)operator new(12 * v8);
    v10 = (char *)this->m_pDataBegin;
    v19 = v9;
    for ( i = v9; v10 != v4; i += 3 )
    {
      i->Copy(v10);
      v10 += 12;
    }
    i->Erase(1, pConfig);
    v4->Insert(this->m_pDataEnd, i + 3);
    nullsub_2(this->m_pDataBegin, this->m_pDataEnd);
    operator delete(this->m_pDataBegin);
    this->m_pCapacity = &v19[3 * v18];
    v12 = (_BYTE *)this->m_pDataBegin;
    if ( v12 )
    {
      v14 = (_BYTE *)this->m_pDataEnd;
      this->m_pDataBegin = v19;
      result = (int)&v19[3 * ((v14 - v12) / 12) + 3];
      this->m_pDataEnd = (void *)result;
    }
    else
    {
      this->m_pDataBegin = v19;
      this->m_pDataEnd = v19 + 3;
      return (int)(v19 + 3);
    }
  }
  return result;
}
