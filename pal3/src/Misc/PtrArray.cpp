#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PtrArray.h"

// Forward declarations for unnamed functions
int sub_434760(...);

// Unnamed globals (extern)
extern int dword_592E5C;
extern GRPinput stru_D8C2B8;

// 0x004019B0
void * PtrArray::ReleasePtrArray()
{
  int v2; // edi
  gbRefObject **v3; // ebx
  void *result; // eax

  v2 = 0;
  if ( *((int *)this + 16) <= 0 )
  {
    *((_DWORD *)this + 16) = 0;
  }
  else
  {
    v3 = (gbRefObject **)this;
    do
    {
      ((gbRefObject *)*v3)->Release();
      result = (void *)*((_DWORD *)this + 16);
      ++v2;
      ++v3;
    }
    while ( v2 < (int)result );
    *((_DWORD *)this + 16) = 0;
  }
  return result;
}

// 0x0040D620
int PtrArray::GetSize()
{
  int result; // eax

  result = *((_DWORD *)this + 6);
  if ( result )
    return (*((_DWORD *)this + 7) - result) / 12;
  return result;
}

// 0x0040D640
void * PtrArray::GetAt(void *pOut, unsigned int nIndex)
{
  int v3; // eax
  _DWORD *v4; // ecx

  if ( (nIndex & 0x80000000) == 0 && (v3 = *((_DWORD *)this + 6)) != 0 && nIndex < (*((_DWORD *)this + 7) - v3) / 12 )
  {
    v4 = (_DWORD *)(*((_DWORD *)this + 6) + 12 * nIndex);
    *(_DWORD *)pOut = *v4;
    *((_DWORD *)pOut + 1) = v4[1];
    *((_DWORD *)pOut + 2) = v4[2];
    return pOut;
  }
  else
  {
    *(_DWORD *)pOut = 0xFFFF;
    *((_DWORD *)pOut + 1) = 0;
    *((_DWORD *)pOut + 2) = 0;
    return pOut;
  }
}

// 0x0040D6B0
void * PtrArray::Insert(void *pItem)
{
  unsigned int *v2; // esi
  unsigned int *v3; // edi
  void *result; // eax
  unsigned int *v5; // ebp
  unsigned int *v6; // ebx
  unsigned int *v7; // edi
  unsigned int v8; // ecx
  unsigned int v9; // edx
  unsigned int *i; // eax
  unsigned int v11; // edx
  unsigned int v12; // ecx
  unsigned int v13; // ebx
  unsigned int v14; // ebp
  unsigned int *v15; // ecx
  unsigned int v16; // eax
  unsigned int v17; // edx
  bool v18; // al
  unsigned int *p_pKey; // edx
  bool v20; // al
  unsigned int *v21; // ebx
  unsigned int *m_needscriptdel; // esi
  int v23; // eax
  unsigned int *v24; // ebp
  char *v25; // ebx
  char *v26; // edi
  int v27; // ecx
  unsigned int v28; // edx
  unsigned int *j; // eax
  unsigned int v30; // edx
  unsigned int v31; // ecx
  void *v32; // ebp
  unsigned int *v33; // edi
  unsigned int *v34; // esi
  _DWORD *v35; // eax
  unsigned int v36; // edx
  bool v37; // cl
  bool v38; // cf
  unsigned int v39; // ecx
  PtrArray v40; // [esp+0x10] [ebp-0x58] BYREF
  unsigned int pKey; // [esp+0x20] [ebp-0x48] BYREF
  unsigned int v42; // [esp+0x24] [ebp-0x44]
  unsigned int v43; // [esp+0x28] [ebp-0x40]
  unsigned int v44; // [esp+0x2C] [ebp-0x3C] BYREF
  unsigned int v45; // [esp+0x30] [ebp-0x38]
  unsigned int v46; // [esp+0x34] [ebp-0x34]
  unsigned int pResult; // [esp+0x38] [ebp-0x30] BYREF
  int v48; // [esp+0x3C] [ebp-0x2C]
  unsigned int v49; // [esp+0x40] [ebp-0x28]
  unsigned int v50; // [esp+0x44] [ebp-0x24]
  unsigned int v51; // [esp+0x4C] [ebp-0x1C]
  unsigned int v52; // [esp+0x54] [ebp-0x14]
  unsigned int v53; // [esp+0x58] [ebp-0x10]
  unsigned int v54; // [esp+0x64] [ebp-0x4]
  unsigned int *pItema; // [esp+0x6C] [ebp+0x4]

  v2 = (unsigned int *)*((_DWORD *)this + 6);
  v3 = (unsigned int *)*((_DWORD *)this + 7);
  v40.capacity = (int)v3;
  v40.m_needscriptdel = (int)v2;
  result = (void *)((unsigned int)((unsigned __int64)(715827883LL * ((char *)v3 - (char *)v2)) >> 32) >> 31);
  if ( ((char *)v3 - (char *)v2) / 12 <= 16 )
  {
    v40.m_pData = (char *)pItem;
    if ( v2 != v3 )
    {
      v5 = v2 + 3;
      if ( v2 + 3 != v3 )
      {
        v6 = v2;
        pItema = v2;
        do
        {
          pKey = *v5;
          v42 = v5[1];
          v43 = v5[2];
          if ( ((PtrArray *)&v40)->Find(&pKey, v2) )
          {
            for ( i = v5; i != v2; i[5] = i[2] )
            {
              i -= 3;
              i[3] = *i;
              i[4] = i[1];
            }
            v11 = v42;
            *v2 = pKey;
            v12 = v43;
            v2[1] = v11;
            v2[2] = v12;
          }
          else
          {
            v40.m_nSize = (int)v40.m_pData;
            v44 = pKey;
            v45 = v42;
            v46 = v43;
            v7 = v5;
            if ( ((PtrArray *)&v40.m_nSize)->Find(&v44, pItema) )
            {
              do
              {
                *v7 = *v6;
                v7[1] = v6[1];
                v7[2] = v6[2];
                v7 = v6;
                v6 -= 3;
              }
              while ( ((PtrArray *)&v40.m_nSize)->Find(&v44, v6) );
            }
            v8 = v45;
            v9 = v46;
            *v7 = v44;
            v7[1] = v8;
            v7[2] = v9;
          }
          result = (void *)v40.capacity;
          v5 += 3;
          v6 = pItema + 3;
          pItema += 3;
        }
        while ( v5 != (unsigned int *)v40.capacity );
      }
    }
    return result;
  }
  do
  {
    v13 = *(v3 - 3);
    v14 = *(v3 - 2);
    v54 = *(v3 - 1);
    v15 = &v2[3 * (((char *)v3 - (char *)v2) / 12 / 2)];
    v16 = *v15;
    v52 = v15[1];
    v53 = v15[2];
    v50 = *v2;
    v17 = v2[2];
    v45 = v2[1];
    v51 = v17;
    v44 = v50;
    pResult = v16;
    v46 = v17;
    v48 = v52;
    v49 = v53;
    v42 = v14;
    v43 = v54;
    pKey = v13;
    v40.m_pData = (char *)pItem;
    if ( ((PtrArray *)&v40)->Find(&v44, &pResult) )
    {
      if ( ((PtrArray *)&v40)->Find(&pResult, &pKey) )
        goto LABEL_21;
      v18 = ((PtrArray *)&v40)->Find(&v44, &pKey);
      p_pKey = &pKey;
      if ( !v18 )
        p_pKey = &v44;
    }
    else
    {
      if ( ((PtrArray *)&v40)->Find(&v44, &pKey) )
      {
        p_pKey = &v44;
        goto LABEL_22;
      }
      v20 = ((PtrArray *)&v40)->Find(&pResult, &pKey);
      p_pKey = &pKey;
      if ( !v20 )
LABEL_21:
        p_pKey = &pResult;
    }
LABEL_22:
    v21 = ((Array *)v2)->PartialSort(v3, *p_pKey, p_pKey[1], p_pKey[2], (int)pItem);
    if ( ((char *)v3 - (char *)v21) / 12 > ((char *)v21 - (char *)v2) / 12 )
    {
      ((PtrArray *)v2)->ParseStringPair((char *)v21, (void **)pItem);
      v2 = v21;
    }
    else
    {
      ((PtrArray *)v21)->ParseStringPair((char *)v3, (void **)pItem);
      v3 = v21;
    }
  }
  while ( ((char *)v3 - (char *)v2) / 12 > 16 );
  m_needscriptdel = (unsigned int *)v40.m_needscriptdel;
  v40.m_nSize = (int)pItem;
  v23 = v40.m_needscriptdel + 192;
  v24 = (unsigned int *)(v40.m_needscriptdel + 12);
  if ( v40.m_needscriptdel + 12 != v40.m_needscriptdel + 192 )
  {
    v25 = (char *)v40.m_needscriptdel;
    v40.m_pData = (char *)v40.m_needscriptdel;
    do
    {
      pKey = *v24;
      v42 = v24[1];
      v43 = v24[2];
      if ( ((PtrArray *)&v40.m_nSize)->Find(&pKey, m_needscriptdel) )
      {
        for ( j = v24; j != m_needscriptdel; j[5] = j[2] )
        {
          j -= 3;
          j[3] = *j;
          j[4] = j[1];
        }
        v30 = v42;
        *m_needscriptdel = pKey;
        v31 = v43;
        m_needscriptdel[1] = v30;
        m_needscriptdel[2] = v31;
      }
      else
      {
        v40.m_needscriptdel = v40.m_nSize;
        pResult = pKey;
        v48 = v42;
        v49 = v43;
        v26 = (char *)v24;
        if ( ((PtrArray *)&v40.m_needscriptdel)->Find(&pResult, v40.m_pData) )
        {
          do
          {
            *(_DWORD *)v26 = *(_DWORD *)v25;
            *((_DWORD *)v26 + 1) = *((_DWORD *)v25 + 1);
            *((_DWORD *)v26 + 2) = *((_DWORD *)v25 + 2);
            v26 = v25;
            v25 -= 12;
          }
          while ( ((PtrArray *)&v40.m_needscriptdel)->Find(&pResult, v25) );
        }
        v27 = v48;
        v28 = v49;
        *(_DWORD *)v26 = pResult;
        *((_DWORD *)v26 + 1) = v27;
        *((_DWORD *)v26 + 2) = v28;
      }
      v24 += 3;
      v23 = (int)(m_needscriptdel + 48);
      v25 = v40.m_pData + 12;
      v40.m_pData += 12;
    }
    while ( v24 != m_needscriptdel + 48 );
  }
  v32 = pItem;
  v33 = (unsigned int *)v23;
  result = (void *)v40.capacity;
  if ( v33 != (unsigned int *)v40.capacity )
  {
LABEL_37:
    v34 = v33;
    pResult = *v33;
    v35 = v33 + 2;
    v48 = v33[1];
    v36 = v33[2];
    while ( 2 )
    {
      v35 -= 3;
      switch ( (unsigned int)v32 )
      {
        case 0u:
          v37 = *(_DWORD *)(v36 + 608) < *(_DWORD *)(*v35 + 608);
          goto LABEL_46;
        case 1u:
          v37 = *(_DWORD *)(v36 + 624) < *(_DWORD *)(*v35 + 624);
          goto LABEL_46;
        case 2u:
          v37 = v48 < *(v35 - 1);
          goto LABEL_46;
        case 3u:
          v38 = pResult < *(v35 - 2);
          goto LABEL_45;
        case 4u:
          v38 = *(_BYTE *)(v36 + 612) < *(_BYTE *)(*v35 + 612);
          goto LABEL_45;
        case 5u:
          v38 = *(_BYTE *)(v36 + 613) < *(_BYTE *)(*v35 + 613);
LABEL_45:
          v37 = v38;
LABEL_46:
          if ( !v37 )
            goto LABEL_48;
          *v34 = *(v35 - 2);
          v34[1] = *(v35 - 1);
          v32 = pItem;
          v34[2] = *v35;
          v34 = v35 - 2;
          continue;
        default:
LABEL_48:
          v39 = v48;
          *v34 = pResult;
          result = (void *)v40.capacity;
          v33 += 3;
          v34[1] = v39;
          v34[2] = v36;
          if ( v33 == result )
            return result;
          goto LABEL_37;
      }
    }
  }
  return result;
}

// 0x0040DBD0
BOOL PtrArray::Find(void *pKey, void *pResult)
{
  BOOL result; // eax

  result = (BOOL)this->m_pData;
  switch ( (unsigned int)this->m_pData )
  {
    case 0u:
      result = *((_DWORD *)pResult + 2);
      LOBYTE(result) = *(_DWORD *)(*((_DWORD *)pKey + 2) + 608) < *(_DWORD *)(result + 608);
      break;
    case 1u:
      result = *((_DWORD *)pResult + 2);
      LOBYTE(result) = *(_DWORD *)(*((_DWORD *)pKey + 2) + 624) < *(_DWORD *)(result + 624);
      break;
    case 2u:
      result = *((_DWORD *)pKey + 1) < *((_DWORD *)pResult + 1);
      break;
    case 3u:
      result = *(_DWORD *)pKey < *(_DWORD *)pResult;
      break;
    case 4u:
      result = *(_BYTE *)(*((_DWORD *)pKey + 2) + 612) < *(_BYTE *)(*((_DWORD *)pResult + 2) + 612);
      break;
    case 5u:
      result = *(_BYTE *)(*((_DWORD *)pKey + 2) + 613) < *(_BYTE *)(*((_DWORD *)pResult + 2) + 613);
      break;
    default:
      LOBYTE(result) = 0;
      break;
  }
  return result;
}

// 0x0040DCD0
BOOL PtrArray::CompareValues(int *p_DWORD2)
{
  return *p_DWORD == *p_DWORD2;
}

// 0x00411290
unsigned int PtrArray::ParseStringPair(char *pszBuf2, void **a3)
{
  char *v3; // ebx
  char *v4; // ebp
  unsigned int result; // eax
  int v6; // edx
  unsigned int v7; // esi
  int *v8; // ebp
  int v9; // edi
  int v10; // ecx
  char *v11; // eax
  unsigned int v12; // edx
  int v13; // eax
  int v14; // ebx
  bool v15; // al
  bool v16; // cf
  bool v17; // al
  int *p_m_nSize; // ecx
  bool v19; // al
  int v20; // eax
  int v21; // edx
  int v22; // ecx
  char *v23; // edi
  char *v24; // esi
  bool v25; // al
  bool v26; // cf
  unsigned __int8 v27; // al
  unsigned __int8 v28; // dl
  char *v29; // edx
  char *v30; // ebx
  int v31; // eax
  int v32; // ecx
  int v33; // eax
  PtrArray pResult; // [esp+0x8] [ebp-0x44] BYREF
  int v35; // [esp+0x18] [ebp-0x34]
  unsigned int pKey; // [esp+0x1C] [ebp-0x30] BYREF
  int v37; // [esp+0x20] [ebp-0x2C]
  int v38; // [esp+0x24] [ebp-0x28]
  unsigned int v39; // [esp+0x28] [ebp-0x24] BYREF
  int v40; // [esp+0x2C] [ebp-0x20]
  int v41; // [esp+0x30] [ebp-0x1C]
  _DWORD v42[5]; // [esp+0x34] [ebp-0x18] BYREF
  int v43; // [esp+0x48] [ebp-0x4]

  v3 = pszBuf;
  v4 = pszBuf2;
  result = (unsigned int)((unsigned __int64)(715827883LL * (pszBuf2 - pszBuf)) >> 32) >> 31;
  v6 = (pszBuf2 - pszBuf) / 12;
  if ( v6 <= 16 )
    return result;
LABEL_2:
  v7 = *(_DWORD *)v3;
  v8 = (int *)(v4 - 12);
  v9 = *((_DWORD *)v3 + 1);
  v42[0] = *(_DWORD *)v3;
  v10 = *((_DWORD *)v3 + 2);
  v42[1] = v9;
  v11 = &v3[12 * (v6 / 2)];
  v42[2] = v10;
  v12 = *(_DWORD *)v11;
  pKey = *(_DWORD *)v11;
  v37 = *((_DWORD *)v11 + 1);
  v13 = *((_DWORD *)v11 + 2);
  pResult.m_nSize = *v8;
  v14 = v8[1];
  v38 = v13;
  pResult.m_needscriptdel = v14;
  v35 = v8[2];
  pResult.m_pData = (char *)a3;
  switch ( (unsigned int)a3 )
  {
    case 0u:
      v15 = *(_DWORD *)(v10 + 608) < *(_DWORD *)(v13 + 608);
      goto LABEL_10;
    case 1u:
      v15 = *(_DWORD *)(v10 + 624) < *(_DWORD *)(v13 + 624);
      goto LABEL_10;
    case 2u:
      v15 = v9 < v37;
      goto LABEL_10;
    case 3u:
      v16 = v7 < v12;
      goto LABEL_9;
    case 4u:
      v16 = *(_BYTE *)(v10 + 612) < *(_BYTE *)(v13 + 612);
      goto LABEL_9;
    case 5u:
      v16 = *(_BYTE *)(v10 + 613) < *(_BYTE *)(v13 + 613);
LABEL_9:
      v15 = v16;
LABEL_10:
      if ( !v15 )
        goto LABEL_14;
      if ( ((PtrArray *)&pResult)->Find(&pKey, &pResult.m_nSize) )
        goto LABEL_17;
      v17 = ((PtrArray *)&pResult)->Find(v42, &pResult.m_nSize);
      p_m_nSize = &pResult.m_nSize;
      if ( !v17 )
        p_m_nSize = v42;
      break;
    default:
LABEL_14:
      if ( ((PtrArray *)&pResult)->Find(v42, &pResult.m_nSize) )
      {
        p_m_nSize = v42;
      }
      else
      {
        v19 = ((PtrArray *)&pResult)->Find(&pKey, &pResult.m_nSize);
        p_m_nSize = &pResult.m_nSize;
        if ( !v19 )
LABEL_17:
          p_m_nSize = (int *)&pKey;
      }
      break;
  }
  v20 = *p_m_nSize;
  v21 = p_m_nSize[1];
  v22 = p_m_nSize[2];
  v4 = pszBuf2;
  pResult.capacity = (int)a3;
  v3 = pszBuf;
  v39 = v20;
  v40 = v21;
  v41 = v22;
  v23 = pszBuf2;
  v24 = pszBuf;
  while ( 2 )
  {
    switch ( pResult.capacity )
    {
      case 0:
        v25 = *(_DWORD *)(*((_DWORD *)v24 + 2) + 608) < *(_DWORD *)(v22 + 608);
        goto LABEL_28;
      case 1:
        v25 = *(_DWORD *)(*((_DWORD *)v24 + 2) + 624) < *(_DWORD *)(v22 + 624);
        goto LABEL_28;
      case 2:
        v25 = *((_DWORD *)v24 + 1) < v40;
        goto LABEL_28;
      case 3:
        v26 = *(_DWORD *)v24 < v39;
        goto LABEL_27;
      case 4:
        v27 = *(_BYTE *)(*((_DWORD *)v24 + 2) + 612);
        v28 = *(_BYTE *)(v22 + 612);
        goto LABEL_26;
      case 5:
        v27 = *(_BYTE *)(*((_DWORD *)v24 + 2) + 613);
        v28 = *(_BYTE *)(v22 + 613);
LABEL_26:
        v26 = v27 < v28;
LABEL_27:
        v25 = v26;
LABEL_28:
        if ( !v25 )
          goto LABEL_30;
        v24 += 12;
        continue;
      default:
LABEL_30:
        for ( v23 -= 12; ((PtrArray *)&pResult.capacity)->Find(&v39, v23); v23 -= 12 )
          ;
        if ( v23 > v24 )
        {
          v29 = v24;
          v30 = v24;
          v24 += 12;
          v31 = *(_DWORD *)v29;
          v32 = *((_DWORD *)v29 + 1);
          v43 = *((_DWORD *)v29 + 2);
          *(_DWORD *)v30 = *(_DWORD *)v23;
          *((_DWORD *)v30 + 1) = *((_DWORD *)v23 + 1);
          v4 = pszBuf2;
          *((_DWORD *)v30 + 2) = *((_DWORD *)v23 + 2);
          v3 = pszBuf;
          *(_DWORD *)v23 = v31;
          v33 = v43;
          *((_DWORD *)v23 + 1) = v32;
          v22 = v41;
          *((_DWORD *)v23 + 2) = v33;
          continue;
        }
        if ( (v4 - v24) / 12 > (v24 - v3) / 12 )
        {
          ((PtrArray *)v3)->ParseStringPair(v24, a3);
          v3 = v24;
          pszBuf = v24;
        }
        else
        {
          ((PtrArray *)v24)->ParseStringPair(v4, a3);
          v4 = v24;
          pszBuf2 = v24;
        }
        result = (unsigned int)((unsigned __int64)(715827883LL * (v4 - v3)) >> 32) >> 31;
        v6 = (v4 - v3) / 12;
        if ( v6 > 16 )
          goto LABEL_2;
        return result;
    }
  }
}

// 0x00431CB0
int * PtrArray::Reset()
{
  ((PtrArray *)&this->m_nSize)->Clear();
  this->capacity = 0;
  LOBYTE(this->m_pData) = 0;
  return (int *)this;
}

// 0x00431E90
void PtrArray::ConditionalCleanup()
{
  if ( (((GRPinput *)&stru_D8C2B8)->m_keyStates[4] & 4) == 0 )
  {
    ((GRPinput *)&stru_D8C2B8)->m_keyStates[4] |= 4u;
    ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_mousept)->Remove();
  }
}

// 0x004325A0
int PtrArray::IsArrayReady()
{
  int v1; // esi
  int i; // edi

  v1 = 0;
  if ( !LOWORD(((GRPinput *)&stru_D8C2B8)->m_joystickDeltaY) )
    return 0;
  for ( i = 0; _strcmpi(String1, (const char *)(i + *(_DWORD *)((GRPinput *)&stru_D8C2B8)->m_keyStates + 8)); i += 72 )
  {
    if ( ++v1 >= LOWORD(((GRPinput *)&stru_D8C2B8)->m_joystickDeltaY) )
      return 0;
  }
  return *(_DWORD *)(*(_DWORD *)((GRPinput *)&stru_D8C2B8)->m_keyStates + 72 * v1);
}

// 0x00432660
int * PtrArray::Clear()
{
  this->m_pData = 0;
  this->m_nSize = 0;
  this->capacity = 0;
  this->m_needscriptdel = 32;
  return (int *)this;
}

// 0x00432770
void PtrArray::SetAt(int nIndex, int newElement)
{
  if ( nIndex >= this->capacity )
    ((String *)this)->Assign((char *)(nIndex + 1), -1);
  *(_DWORD *)&this->m_pData[4 * nIndex] = newElement;
}

// 0x004327B0
int PtrArray::RemoveAt(int nIndex, int nCount)
{
  int v4; // eax
  int result; // eax

  v4 = this->capacity - nIndex - nCount;
  if ( v4 )
    memcpy(&this->m_pData[4 * nIndex], &this->m_pData[4 * nIndex + 4 * nCount], 4 * v4);
  result = this->capacity - nCount;
  this->capacity = result;
  return result;
}

// 0x004327F0
int PtrArray::FindFirst(void *pData)
{
  int capacity; // esi
  int result; // eax
  void *v4; // edx

  capacity = this->capacity;
  result = 0;
  if ( capacity > 0 )
  {
    while ( 1 )
    {
      v4 = result < 0 || result >= capacity ? 0 : *(void **)&this->m_pData[4 * result];
      if ( pData == v4 )
        break;
      if ( ++result >= capacity )
        return result;
    }
    return this->RemoveAt(result, 1);
  }
  return result;
}

// 0x00433C50
void PtrArray::ReadFromVFile(gbVFile *pFile)
{
  unsigned __int16 *v2; // esi
  void *v3; // eax

  *(_DWORD *)pBuf = 0;
  *((_DWORD *)pBuf + 1) = 0;
  if ( pFile )
  {
    ((gbVFileSystem *)g_pVFileSys)->Read(pBuf, 1u, pFile);
    v2 = pBuf + 1;
    ((gbVFileSystem *)g_pVFileSys)->Read(pBuf + 1, 2u, pFile);
    if ( pBuf[1] )
    {
      v3 = malloc(*v2);
      *((_DWORD *)pBuf + 1) = v3;
      if ( v3 )
        ((gbVFileSystem *)g_pVFileSys)->Read(v3, *v2, pFile);
    }
  }
}

// 0x00433DC0
int * PtrArray::CopyRange(int nVal, int nVal2)
{
  int *result; // eax
  int *v4; // ebp
  int *v5; // esi
  void *v6; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // esi
  int v11; // ebx
  _DWORD *v12; // esi
  unsigned __int16 *v13; // eax
  unsigned __int16 v14; // ax
  char *v15; // edx
  unsigned int v16; // ebp
  char *v17; // edi
  char v18; // cl
  int *v19; // [esp+0xC] [ebp-0x4]
  int *p_DWORDa; // [esp+0x14] [ebp+0x4]
  int nVala; // [esp+0x18] [ebp+0x8]

  result = (int *)sub_434760(nVal);
  v4 = result;
  v19 = result;
  if ( result )
  {
    if ( !result[17] )
      return 0;
    result = (int *)malloc(0x50u);
    v5 = result;
    p_DWORDa = result;
    if ( result )
    {
      memset(result, 0, 0x50u);
      *result = (int)v4;
      result[2] = nVal2 + v4[18];
      if ( *((_WORD *)v4 + 38) )
      {
        v6 = malloc(8 * *((unsigned __int16 *)v4 + 38));
        v5[19] = (int)v6;
        if ( !v6 )
        {
          free(v5);
          return 0;
        }
        memset(v6, 0, 8 * *((unsigned __int16 *)v4 + 38));
        v7 = 0;
        nVala = 0;
        if ( *((_WORD *)v4 + 38) )
        {
          do
          {
            v8 = v5[19];
            v9 = 8 * v7;
            v10 = v9 + v4[20];
            v11 = v9 + v8;
            *(_BYTE *)v11 = *(_BYTE *)v10;
            switch ( *(_BYTE *)v10 )
            {
              case 1:
              case 2:
              case 4:
                *(_WORD *)(v11 + 2) = 4;
                v12 = *(_DWORD **)(v10 + 4);
                if ( v12 )
                  *(_DWORD *)(v11 + 4) = *v12;
                else
                  *(_DWORD *)(v11 + 4) = 0;
                break;
              case 3:
                v13 = *(unsigned __int16 **)(v10 + 4);
                if ( v13 && (v14 = *v13, *(_WORD *)(v11 + 2) = v14, (v15 = (char *)malloc(v14)) != 0) )
                {
                  v16 = *(unsigned __int16 *)(v11 + 2);
                  memset(v15, 0, 4 * (v16 >> 2));
                  v17 = &v15[4 * (v16 >> 2)];
                  v18 = v16;
                  v4 = v19;
                  memset(v17, 0, v18 & 3);
                  qmemcpy(v15, (const void *)(*(_DWORD *)(v10 + 4) + 2), *(unsigned __int16 *)(v11 + 2));
                  *(_DWORD *)(v11 + 4) = v15;
                }
                else
                {
                  *(_WORD *)(v11 + 2) = 0;
                  *(_DWORD *)(v11 + 4) = 0;
                }
                break;
              default:
                *(_BYTE *)v11 = -1;
                *(_WORD *)(v11 + 2) = 0;
                *(_DWORD *)(v11 + 4) = 0;
                break;
            }
            v5 = p_DWORDa;
            v7 = nVala + 1;
            nVala = v7;
          }
          while ( v7 < *((unsigned __int16 *)v4 + 38) );
        }
      }
      ++v4[21];
      ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[40])->SetAt(*(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[44], (int)v5);
      *((_BYTE *)v5 + 4) = 1;
      return v5;
    }
  }
  return result;
}

// 0x00434130
PtrArray::PtrArray(int nInitSize, int nGrowBy, char bOwned)
{
  int v4; // edx

  *(_BYTE *)nInitSize = bOwned;
  switch ( bOwned )
  {
    case 1:
    case 2:
    case 4:
      *(_WORD *)(nInitSize + 2) = 4;
      *(_DWORD *)(nInitSize + 4) = **(_DWORD **)(nGrowBy + 8);
      *(_DWORD *)(nGrowBy + 8) += 4;
      break;
    case 3:
      *(_WORD *)(nInitSize + 2) = **(_WORD **)(nGrowBy + 8);
      v4 = *(_DWORD *)(nGrowBy + 8) + 2;
      *(_DWORD *)(nGrowBy + 8) = v4;
      *(_DWORD *)(nInitSize + 4) = v4;
      *(_DWORD *)(nGrowBy + 8) += *(unsigned __int16 *)(nInitSize + 2);
      break;
    case 5:
      *(_WORD *)(nInitSize + 2) = 2;
      *(_DWORD *)(nInitSize + 4) = **(unsigned __int16 **)(nGrowBy + 8);
      *(_DWORD *)(nGrowBy + 8) += 2;
      break;
    default:
      *(_BYTE *)nInitSize = -1;
      *(_WORD *)(nInitSize + 2) = 0;
      *(_DWORD *)(nInitSize + 4) = 0;
      break;
  }
}

// 0x004341E0
void PtrArray::_PtrArray()
{
  unsigned int v1; // edi
  int v2; // [esp+0xC] [ebp+0x4]

  if ( v2 )
  {
    v1 = *(_DWORD *)(*(_DWORD *)v2 + 68) + *(_DWORD *)(*(_DWORD *)v2 + 72);
    if ( *(_DWORD *)(v2 + 8) < v1 )
    {
      ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode = v2;
      if ( *(_DWORD *)(v2 + 8) < v1 )
      {
        do
          PalScript::ProcessGBKString();
        while ( *(_BYTE *)(v2 + 4) != 1 && *(_DWORD *)(v2 + 8) < v1 );
      }
      ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode = 0;
    }
  }
}

// 0x00434240
void PtrArray::SetSize()
{
  int v1; // esi
  int v2; // edi
  void **v3; // ebx
  int v4; // esi
  int v5; // eax
  unsigned __int16 *v6; // esi
  int v7; // edi
  int v8; // eax
  int i; // [esp+0xC] [ebp-0x8]
  int v10; // [esp+0x10] [ebp-0x4]

  v1 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[44];
  v2 = 0;
  v10 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[44];
  for ( i = 0; v2 < v1; i = v2 )
  {
    if ( v2 < 0 || v2 >= *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[44] )
      v3 = 0;
    else
      v3 = *(void ***)(*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[40] + 4 * v2);
    if ( *v3 )
    {
      if ( *((_WORD *)*v3 + 38) )
      {
        v4 = 0;
        do
        {
          v5 = (int)v3[19] + 8 * v4;
          if ( *(_BYTE *)v5 == 3 )
          {
            free(*(void **)(v5 + 4));
            *((_DWORD *)v3[19] + 2 * v4 + 1) = 0;
          }
          ++v4;
        }
        while ( v4 < *((unsigned __int16 *)*v3 + 38) );
        free(v3[19]);
        v3[19] = 0;
      }
      v6 = (unsigned __int16 *)*v3;
      if ( *((_DWORD *)*v3 + 18) )
      {
        free(*((void **)*v3 + 18));
        *((_DWORD *)v6 + 18) = 0;
      }
      if ( v6[38] )
      {
        v7 = 0;
        do
        {
          v8 = *((_DWORD *)v6 + 20) + 8 * v7;
          if ( *(_WORD *)(v8 + 2) )
          {
            free(*(void **)(v8 + 4));
            *(_DWORD *)(*((_DWORD *)v6 + 20) + 8 * v7 + 4) = 0;
          }
          ++v7;
        }
        while ( v7 < v6[38] );
        free(*((void **)v6 + 20));
        v2 = i;
        *((_DWORD *)v6 + 20) = 0;
      }
      operator delete(*v3);
      v1 = v10;
      *v3 = 0;
    }
    free(v3);
    ++v2;
  }
  ((String *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[40])->Assign(0, -1);
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] = -1;
  memset(&((GRPinput *)&stru_D8C2B8)->m_keyStates[68], 0, 0x100u);
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode = 0;
  if ( ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].Data )
  {
    free((void *)((GRPinput *)&stru_D8C2B8)->KeyInfo[148].Data);
    ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].Data = 0;
  }
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].PressTime = 0;
}

// 0x004343B0
char * PtrArray::SetAtGrow(unsigned __int16 pData, int *nIndex)
{
  int CountMode; // ecx

  CountMode = (int)nIndex;
  if ( !nIndex )
    CountMode = ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode;
  if ( (pData & 0x8000u) == 0 )
    return (char *)(*(_DWORD *)(CountMode + 76) + 8 * pData);
  else
    return (char *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[148].Data + 24 * (pData & 0x7FFF));
}

// 0x004343F0
void PtrArray::RemoveAt(const char *nIndex)
{
  int v2; // edi
  const char *v3; // ebp

  v2 = 0;
  if ( ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].PressTime > 0 )
  {
    v3 = (const char *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[148].Data + 8);
    do
    {
      if ( !strcmp(nIndex, v3) )
        break;
      ++v2;
      v3 += 24;
    }
    while ( v2 < ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].PressTime );
  }
}

// 0x00434490
void PtrArray::Remove()
{

  operator delete((void *)this->m_nSize);
  this->m_nSize = 0;
  this->m_needscriptdel = 0;
  *((_DWORD *)this + 4) = 0;
}

// 0x004344F0
void PtrArray::InsertAt(const char *nIndex)
{
  char *v3; // eax
  void *v4; // edi
  int v5; // edi
  bool v6; // zf
  int v7; // ebx
  int p_DWORD2; // [esp+0x20] [ebp-0x10] BYREF
  char v9[5]; // [esp+0x24] [ebp-0xC] BYREF
  int v10; // [esp+0x29] [ebp-0x7]

  v3 = (char *)((gbVFileSystem *)g_pVFileSys)->OpenFile(nIndex, 0x201u);
  this->m_pData = v3;
  if ( v3 )
  {
    ((gbVFileSystem *)g_pVFileSys)->Read(v9, 7u, (gbVFile *)v3);
    if ( !strcmp(v9, (const char *)&dword_592E5C) && v9[4] == 1 )
    {
      v4 = malloc(72 * (unsigned __int16)v10);
      *((_DWORD *)this + 6) = v4;
      if ( v4 )
      {
        memset(v4, 0, 72 * (unsigned __int16)v10);
        ((gbVFileSystem *)g_pVFileSys)->Read(*((void **)this + 6), 72 * (unsigned __int16)v10, (gbVFile *)this->m_pData);
        v5 = 0;
        v6 = (_WORD)v10 == 0;
        *((_WORD *)this + 10) = v10;
        if ( !v6 )
        {
          v7 = 0;
          do
          {
            p_DWORD2 = (int)this->ReadFileSection(v7 + *((_DWORD *)this + 6));
            ((Actor *)&this->capacity)->LoadActionSequence((int *)this->m_needscriptdel, 1u, &p_DWORD2);
            ++v5;
            v7 += 72;
          }
          while ( v5 < (unsigned __int16)v10 );
        }
        ((gbVFileSystem *)g_pVFileSys)->CloseFile((gbVFile *)this->m_pData);
        this->m_pData = 0;
      }
    }
  }
}

// 0x00434670
int PtrArray::DestroyAll()
{
  unsigned int i; // edi
  int m_nSize; // eax
  int v4; // esi
  int v5; // edi
  int v6; // eax
  bool v7; // zf
  int v8; // eax
  int result; // eax
  unsigned int v10; // [esp+0xC] [ebp-0x4]

  if ( *((_DWORD *)this + 6) )
  {
    free(*((void **)this + 6));
    *((_DWORD *)this + 6) = 0;
  }
  for ( i = 0; ; ++i )
  {
    m_nSize = this->m_nSize;
    v10 = i;
    if ( !m_nSize || i >= (this->m_needscriptdel - m_nSize) >> 2 )
      break;
    v4 = *(_DWORD *)(m_nSize + 4 * i);
    if ( *(_DWORD *)(v4 + 72) )
    {
      free(*(void **)(v4 + 72));
      *(_DWORD *)(v4 + 72) = 0;
    }
    if ( *(_WORD *)(v4 + 76) )
    {
      v5 = 0;
      do
      {
        v6 = *(_DWORD *)(v4 + 80);
        v7 = *(_WORD *)(v6 + 8 * v5 + 2) == 0;
        v8 = v6 + 8 * v5;
        if ( !v7 )
        {
          free(*(void **)(v8 + 4));
          *(_DWORD *)(*(_DWORD *)(v4 + 80) + 8 * v5 + 4) = 0;
        }
        ++v5;
      }
      while ( v5 < *(unsigned __int16 *)(v4 + 76) );
      free(*(void **)(v4 + 80));
      i = v10;
      *(_DWORD *)(v4 + 80) = 0;
    }
    free(*(void **)(this->m_nSize + 4 * i));
  }
  result = this->m_needscriptdel;
  this->m_needscriptdel = this->m_nSize;
  *((_WORD *)this + 10) = 0;
  return result;
}

// 0x004348E0
gbVFile * PtrArray::ReadFileSection(int nSection)
{
  gbVFile *result; // eax
  gbVFile *v4; // ebx
  void ( *v5)(gbVFileSystem *__hidden, void *, unsigned int, gbVFile *); // esi
  void *v6; // edi
  gbVFile *v7; // edi
  void *v8; // edx
  int v9; // edi
  char *m_pData; // ecx
  int v11; // eax
  int v12; // esi
  void *v13; // eax
  size_t *v14; // edi
  void *v15; // eax
  unsigned int v16; // edx
  int v17; // [esp+0x3C] [ebp-0xC]
  unsigned __int16 pBuf[2]; // [esp+0x40] [ebp-0x8] BYREF
  const void *v19; // [esp+0x44] [ebp-0x4]

  if ( !*((_WORD *)this + 10) )
    return 0;
  result = (gbVFile *)this->m_pData;
  if ( this->m_pData )
  {
    if ( !nSection )
      return 0;
    ((gbVFileSystem *)g_pVFileSys)->Seek(result, *(_DWORD *)(nSection + 4), 1);
    result = (gbVFile *)malloc(0x58u);
    v4 = result;
    if ( result )
    {
      v5 = gbVFileSystem::Read;
      memset(result, 0, 0x58u);
      ((gbVFileSystem *)g_pVFileSys)->Read(result, 4u, (gbVFile *)this->m_pData);
      ((gbVFileSystem *)g_pVFileSys)->Read(&nSection, 2u, (gbVFile *)this->m_pData);
      v6 = operator new((unsigned __int16)nSection);
      if ( v6 )
      {
        ((gbVFileSystem *)g_pVFileSys)->Read(v6, (unsigned __int16)nSection, (gbVFile *)this->m_pData);
        strncpy((char *)&v4[4], (const char *)v6, 0x40u);
        operator delete(v6);
      }
      v7 = v4 + 76;
      ((gbVFileSystem *)g_pVFileSys)->Read(&v4[76], 2u, (gbVFile *)this->m_pData);
      if ( *(_WORD *)&v4[76] )
      {
        v8 = malloc(8 * *(_WORD *)v7);
        *(_DWORD *)&v4[80] = v8;
        if ( !v8 )
        {
          free(v4);
          return 0;
        }
        memset(v8, 0, 4 * ((8 * (unsigned int)*(_WORD *)v7) >> 2));
        v9 = 0;
        v17 = 0;
        if ( *(_WORD *)&v4[76] )
        {
          do
          {
            m_pData = this->m_pData;
            *(_DWORD *)pBuf = 0;
            v19 = 0;
            ((PtrArray *)pBuf)->ReadFromVFile((gbVFile *)m_pData);
            v11 = *(_DWORD *)&v4[80];
            *(_BYTE *)(v11 + 8 * v9) = pBuf[0];
            v12 = v11 + 8 * v9;
            *(_WORD *)(v12 + 2) = pBuf[1];
            if ( pBuf[1] )
            {
              v13 = malloc(pBuf[1]);
              *(_DWORD *)(v12 + 4) = v13;
              qmemcpy(v13, v19, *(unsigned __int16 *)(v12 + 2));
              v9 = v17;
            }
            else
            {
              *(_DWORD *)(v12 + 4) = 0;
            }
            v17 = ++v9;
          }
          while ( v9 < *(unsigned __int16 *)&v4[76] );
          v5 = gbVFileSystem::Read;
        }
      }
      v14 = (size_t *)&v4[68];
      v5(g_pVFileSys, &v4[68], 4u, (gbVFile *)this->m_pData);
      if ( *(_DWORD *)&v4[68] )
      {
        v15 = malloc(*v14);
        v16 = *v14;
        *(_DWORD *)&v4[72] = v15;
        v5(g_pVFileSys, v15, v16, (gbVFile *)this->m_pData);
      }
      return v4;
    }
  }
  return result;
}

// 0x0044BD60
PtrArray::PtrArray()
{
  this->m_pData = 0;
  this->capacity = 0;
  this->m_nSize = 0;
  this->m_needscriptdel = 32;
}

// 0x0053D0B0
PtrArray * PtrArray::ClearBoth()
{

  ((PtrArray *)this + 1)->Clear();
  return this;
}

// 0x0053D1A0
void PtrArray::SetResolution(int nVal, int arg4)
{
  if ( nVal )
    this->SetAt(this->capacity, nVal);
  if ( arg4 )
    ((PtrArray *)this + 1)->SetAt(*((_DWORD *)this + 5), arg4);
}
