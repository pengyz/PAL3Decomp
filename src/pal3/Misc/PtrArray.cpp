#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PtrArray.h"

// Forward declarations for unnamed functions
int sub_4326A0(...);
int sub_433F90(...);
int sub_434670(...);
int sub_4348E0(...);
int sub_5372D0(...);

// Unnamed globals (extern)
extern int stru_D8C2B8;

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

// 0x00434130
PtrArray::PtrArray(int a1, int a2, char a3)
{
  int result; // eax
  int v4; // edx

  result = a1;
  *(_BYTE *)a1 = a3;
  switch ( a3 )
  {
    case 1:
    case 2:
    case 4:
      *(_WORD *)(a1 + 2) = 4;
      *(_DWORD *)(a1 + 4) = **(_DWORD **)(a2 + 8);
      result = *(_DWORD *)(a2 + 8) + 4;
      *(_DWORD *)(a2 + 8) = result;
      break;
    case 3:
      *(_WORD *)(a1 + 2) = **(_WORD **)(a2 + 8);
      v4 = *(_DWORD *)(a2 + 8) + 2;
      *(_DWORD *)(a2 + 8) = v4;
      *(_DWORD *)(a1 + 4) = v4;
      result = *(unsigned __int16 *)(a1 + 2) + *(_DWORD *)(a2 + 8);
      *(_DWORD *)(a2 + 8) = result;
      break;
    case 5:
      *(_WORD *)(a1 + 2) = 2;
      *(_DWORD *)(a1 + 4) = **(unsigned __int16 **)(a2 + 8);
      result = *(_DWORD *)(a2 + 8) + 2;
      *(_DWORD *)(a2 + 8) = result;
      break;
    default:
      *(_BYTE *)a1 = -1;
      *(_WORD *)(a1 + 2) = 0;
      *(_DWORD *)(a1 + 4) = 0;
      break;
  }
  result;
}

// 0x004341E0
PtrArray::~PtrArray()
{
  unsigned int v2; // edi

  if ( !a1 )
  0;
  v2 = *(_DWORD *)(*(_DWORD *)a1 + 68) + *(_DWORD *)(*(_DWORD *)a1 + 72);
  if ( *(_DWORD *)(a1 + 8) >= v2 )
  2;
  stru_D8C2B8.KeyTransformation[1] = a1;
  if ( *(_DWORD *)(a1 + 8) < v2 )
  {
    do
      sub_433F90();
    while ( *(_BYTE *)(a1 + 4) != 1 && *(_DWORD *)(a1 + 8) < v2 );
  }
  stru_D8C2B8.KeyTransformation[1] = 0;
  1;
}

// 0x00434240
void PtrArray::SetSize()
{
  __int32 v0; // esi
  int v1; // edi
  void **v2; // ebx
  int v3; // esi
  int v4; // eax
  unsigned __int16 *v5; // esi
  int v6; // edi
  int v7; // eax
  int i; // [esp+Ch] [ebp-8h]
  __int32 v9; // [esp+10h] [ebp-4h]

  v0 = stru_D8C2B8.m_keyStates[11];
  v1 = 0;
  v9 = stru_D8C2B8.m_keyStates[11];
  for ( i = 0; v1 < v0; i = v1 )
  {
    if ( v1 < 0 || v1 >= stru_D8C2B8.m_keyStates[11] )
      v2 = 0;
    else
      v2 = *(void ***)(stru_D8C2B8.m_keyStates[10] + 4 * v1);
    if ( *v2 )
    {
      if ( *((_WORD *)*v2 + 38) )
      {
        v3 = 0;
        do
        {
          v4 = (int)v2[19] + 8 * v3;
          if ( *(_BYTE *)v4 == 3 )
          {
            free(*(void **)(v4 + 4));
            *((_DWORD *)v2[19] + 2 * v3 + 1) = 0;
          }
          ++v3;
        }
        while ( v3 < *((unsigned __int16 *)*v2 + 38) );
        free(v2[19]);
        v2[19] = 0;
      }
      v5 = (unsigned __int16 *)*v2;
      if ( *((_DWORD *)*v2 + 18) )
      {
        free(*((void **)*v2 + 18));
        *((_DWORD *)v5 + 18) = 0;
      }
      if ( v5[38] )
      {
        v6 = 0;
        do
        {
          v7 = *((_DWORD *)v5 + 20) + 8 * v6;
          if ( *(_WORD *)(v7 + 2) )
          {
            free(*(void **)(v7 + 4));
            *(_DWORD *)(*((_DWORD *)v5 + 20) + 8 * v6 + 4) = 0;
          }
          ++v6;
        }
        while ( v6 < v5[38] );
        free(*((void **)v5 + 20));
        v1 = i;
        *((_DWORD *)v5 + 20) = 0;
      }
      operator delete(*v2);
      v0 = v9;
      *v2 = 0;
    }
    free(v2);
    ++v1;
  }
  sub_4326A0((int)&stru_D8C2B8.m_keyStates[10], 0, -1);
  stru_D8C2B8.m_keyStates[16] = -1;
  memset(&stru_D8C2B8.m_keyStates[17], 0, 0x100u);
  stru_D8C2B8.KeyTransformation[1] = 0;
  if ( stru_D8C2B8.KeyTransformation[3] )
  {
    free((void *)stru_D8C2B8.KeyTransformation[3]);
    stru_D8C2B8.KeyTransformation[3] = 0;
  }
  stru_D8C2B8.KeyTransformation[2] = 0;
}

// 0x004343B0
char * PtrArray::SetAtGrow(signed __int16 a1, int a2)
{
  int v2; // ecx

  v2 = a2;
  if ( !a2 )
    v2 = stru_D8C2B8.KeyTransformation[1];
  if ( a1 >= 0 )
    return (char *)(*(_DWORD *)(v2 + 76) + 8 * (unsigned __int16)a1);
  else
    return (char *)(stru_D8C2B8.KeyTransformation[3] + 24 * (a1 & 0x7FFF));
}

// 0x004343F0
char * PtrArray::RemoveAt(const char *a1)
{
  int v1; // edi
  const char *i; // ebp

  v1 = 0;
  if ( stru_D8C2B8.KeyTransformation[2] <= 0 )
    return 0;
  for ( i = (const char *)(stru_D8C2B8.KeyTransformation[3] + 8); strcmp(a1, i); i += 24 )
  {
    if ( ++v1 >= stru_D8C2B8.KeyTransformation[2] )
      return 0;
  }
  return (char *)(stru_D8C2B8.KeyTransformation[3] + 24 * v1);
}

// 0x00434490
void PtrArray::Remove()
{
  sub_434670((int)this);
  operator delete((void *)this->m_nMaxSize);
  this->m_nMaxSize = 0;
  this->m_nGrowBy = 0;
  *((_DWORD *)this + 4) = 0;
}

// 0x004344F0
struct gbVFile * PtrArray::InsertAt(const char *a2)
{
  struct gbVFile *result; // eax
  int v4; // edi
  bool v5; // zf
  int v6; // ebx
  struct gbVFile *v7; // [esp+20h] [ebp-10h] BYREF
  char v8[5]; // [esp+24h] [ebp-Ch] BYREF
  int v9; // [esp+29h] [ebp-7h]

  sub_434670((int)this);
  result = (struct gbVFile *)g_pVFileSys->OpenFile(a2, 0x201u);
  this->m_pData = result;
  if ( result )
  {
    g_pVFileSys->Read(v8, 7u, result);
    if ( !strcmp(v8, "SCE") )
    {
      if ( v8[4] == 1 )
      {
        result = (struct gbVFile *)malloc(72 * (unsigned __int16)v9);
        *((_DWORD *)this + 6) = result;
        if ( result )
        {
          memset(result, 0, 72 * (unsigned __int16)v9);
          g_pVFileSys->Read(*((void **)this + 6), 72 * (unsigned __int16)v9, (struct gbVFile *)this->m_pData);
          v4 = 0;
          v5 = (_WORD)v9 == 0;
          *((_WORD *)this + 10) = v9;
          if ( !v5 )
          {
            v6 = 0;
            do
            {
              v7 = (struct gbVFile *)sub_4348E0((struct gbVFile **)this, v6 + *((_DWORD *)this + 6));
              sub_5372D0((int)&this->m_nSize, (_DWORD *)this->m_nGrowBy, 1u, &v7);
              ++v4;
              v6 += 72;
            }
            while ( v4 < (unsigned __int16)v9 );
          }
          g_pVFileSys->CloseFile((struct gbVFile *)this->m_pData);
          this->m_pData = 0;
          return (struct gbVFile *)1;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}
