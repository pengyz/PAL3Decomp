#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PtrArray.h"

// Forward declarations for unnamed functions
int sub_4326A0(...);

// 0x00432660
_DWORD * PtrArray::Clear()
{
  this->m_pData = 0;
  this->m_nMaxSize = 0;
  this->m_nSize = 0;
  this->m_nGrowBy = 32;
  return &this->m_pData;
}

// 0x00432770
void PtrArray::SetAt(int a2, int a3)
{
  if ( a2 >= this->m_nSize )
    sub_4326A0((int)this, a2 + 1, -1);
  *((_DWORD *)this->m_pData + a2) = a3;
}

// 0x004327B0
int PtrArray::InsertAt(int a2, int a3)
{
  int v4; // eax
  int result; // eax

  v4 = this->m_nSize - a2 - a3;
  if ( v4 )
    memcpy((char *)this->m_pData + 4 * a2, (char *)this->m_pData + 4 * a2 + 4 * a3, 4 * v4);
  result = this->m_nSize - a3;
  this->m_nSize = result;
  return result;
}
