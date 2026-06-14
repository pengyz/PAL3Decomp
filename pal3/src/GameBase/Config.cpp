#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/Config.h"

// 0x0042FDA0
int Config::ReadINIInt(char *filename, char *key)
{
  memset(this, 0, 0x104u);
  return (int)this;
}

// 0x0042FDC0
char * Config::FormatSectionPath(char *filename, char *key)
{
  return (char *)sprintf((char *const)this, "%s\\%s", Filename, filename);
}

// 0x0042FDE0
bool Config::ReadSectionAsInt(char *filename, char *section)
{
  DWORD PrivateProfileStringA; // edi
  int *v5; // [esp+0x18] [ebp+0xC]
  int v6; // [esp+0x1C] [ebp+0x10]

  PrivateProfileStringA = GetPrivateProfileStringA(filename, section, lpDefault, g_ScriptSystemData.m_String, 0xFFu, (LPCSTR)this);
  if ( !strcmp(g_ScriptSystemData.m_String, lpDefault) )
    *v5 = v6;
  else
    *v5 = atoi(g_ScriptSystemData.m_String);
  return PrivateProfileStringA < 0xFF;
}

// 0x0042FEB0
int * Config::ResetField7()
{
  *((_DWORD *)&this->m_ptr_4 + 7) = 0;
  return (int *)this;
}

// 0x0042FEC0
int Config::InitDefaults(int *p_DWORD, int *p_DWORD2)
{
  int v4; // edx
  __int64 v5; // rax
  double v6; // st7

  *p_DWORD = 60000;
  v4 = 4;
  *p_DWORD2 = -60000;
  do
  {
    if ( *(_DWORD *)this > *p_DWORD2 )
      *p_DWORD2 = *(_DWORD *)this;
    if ( *(_DWORD *)this < *p_DWORD )
      *p_DWORD = *(_DWORD *)this;
    this = (Config *)((char *)this + 8);
    --v4;
  }
  while ( v4 );
  LODWORD(v5) = *p_DWORD2;
  if ( *p_DWORD2 - *p_DWORD < 4 )
  {
    v6 = (double)((int)v5 + *p_DWORD) * 0.5;
    *p_DWORD2 = (__int64)(v6 + 2.5);
    v5 = (__int64)(v6 - 2.5);
    *p_DWORD = v5;
  }
  return v5;
}

// 0x0042FF40
BOOL Config::ReadFloatArray(int nVal, int nVal2, int *pnVal, int *pnVal2)
{
  int v6; // ebp
  int v7; // ebx
  int *v8; // edi
  int *v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // ecx
  double v13; // st7
  int v14; // eax
  int v15; // eax
  int v17; // [esp+0x10] [ebp-0x58]
  int *p_DWORD; // [esp+0x14] [ebp-0x54]
  int v19; // [esp+0x18] [ebp-0x50] BYREF
  int v20; // [esp+0x1C] [ebp-0x4C]
  _BYTE v21[72]; // [esp+0x20] [ebp-0x48] BYREF

  v6 = 0;
  v19 = 0;
  v20 = 0;
  v17 = 0;
  memset(v21, 0, sizeof(v21));
  v7 = 1;
  v8 = (int *)this;
  p_DWORD = &v19;
  while ( 1 )
  {
    v9 = (int *)((char *)this + 8 * (v7 % 4));
    if ( *v8 != *v9 )
    {
      if ( this->GetNextEntry(nVal, v8, v9, p_DWORD) )
      {
        ++v17;
        ++p_DWORD;
      }
      goto LABEL_7;
    }
    if ( nVal == *v8 )
      break;
LABEL_7:
    ++v6;
    ++v7;
    v8 += 2;
    if ( v7 >= 5 )
    {
      v10 = v20;
      v11 = v19;
      goto LABEL_10;
    }
  }
  v11 = *((_DWORD *)&this->m_ptr_4 + 2 * v6);
  v10 = *((_DWORD *)&this->m_ptr_4 + 2 * ((v6 + 1) % 4));
  v17 = 2;
LABEL_10:
  v12 = v11;
  if ( v11 >= v10 )
    v12 = v10;
  *pnVal = v12;
  if ( v11 <= v10 )
    v11 = v10;
  *pnVal2 = v11;
  if ( v11 - *pnVal < 4 )
  {
    v13 = (double)(v11 + *pnVal) * 0.5;
    *pnVal2 = (__int64)(v13 + 2.5);
    *pnVal = (__int64)(v13 - 2.5);
  }
  v14 = *(_DWORD *)(nVal2 + 4);
  if ( *pnVal < v14 )
    *pnVal = v14;
  v15 = *(_DWORD *)(nVal2 + 12);
  if ( *pnVal2 > v15 )
    *pnVal2 = v15;
  return v17 == 2;
}

// 0x00430080
int Config::SetSlotValue(int nVal, int nVal2)
{
  int result; // eax

  *((_DWORD *)this + 2 * *((_DWORD *)&this->m_ptr_4 + 7)) = nVal;
  *((_DWORD *)&this->m_ptr_4 + 2 * *((_DWORD *)&this->m_ptr_4 + 7)) = nVal2;
  result = *((_DWORD *)&this->m_ptr_4 + 7) + 1;
  *((_DWORD *)&this->m_ptr_4 + 7) = result;
  return result;
}

// 0x004300A0
bool Config::GetNextEntry(int nVal, int *pnVal, int *pnVal2, int *p_DWORD)
{
  int v5; // ecx
  int v6; // eax
  int v7; // ebp
  int v8; // edx
  int v9; // ecx
  __int64 v10; // rax
  int v11; // esi

  v5 = *pnVal;
  v6 = *pnVal2;
  v7 = *pnVal;
  if ( *pnVal <= *pnVal2 )
    v7 = *pnVal2;
  v8 = *pnVal;
  if ( v5 >= v6 )
    v8 = *pnVal2;
  if ( nVal > v7 || nVal <= v8 )
    return 0;
  v10 = (__int64)((double)pnVal[1]
                - (double)*pnVal * ((double)(pnVal2[1] - pnVal[1]) / (double)(v6 - v5))
                + (double)nVal * ((double)(pnVal2[1] - pnVal[1]) / (double)(v6 - v5))
                + 0.5);
  *p_DWORD = v10;
  v9 = pnVal[1];
  HIDWORD(v10) = pnVal2[1];
  v11 = v9;
  if ( v9 <= SHIDWORD(v10) )
    v11 = pnVal2[1];
  if ( v9 >= SHIDWORD(v10) )
    v9 = pnVal2[1];
  return (int)v10 >= v9 && (int)v10 <= v11;
}

// 0x00430670
int Config::ParseSection(int nVal)
{
  unsigned int v3; // ebp
  int v4; // esi
  int v5; // eax
  unsigned int v6; // ebp
  unsigned __int8 *v8; // eax
  unsigned __int8 *v9; // eax
  unsigned __int8 *v10; // esi

  *(_BYTE *)this = *(_BYTE *)nVal;
  this->m_ptr_4 = 0;
  *((_DWORD *)&this->m_ptr_4 + 1) = 0;
  *((_DWORD *)&this->m_ptr_4 + 2) = 0;
  v3 = *(_DWORD *)(nVal + 8);
  if ( this == (Config *)nVal )
  {
    v4 = -1;
    if ( v3 )
// [IDA_MISID]       std::_Xran();
    ((std *)this)->string::_Split();
    v5 = *((_DWORD *)&this->m_ptr_4 + 1);
    if ( v5 != -1 )
      v4 = *((_DWORD *)&this->m_ptr_4 + 1);
    if ( v4 )
    {
      memcpy(this->m_ptr_4, &this->m_ptr_4[v4], v5 - v4);
      v6 = *((_DWORD *)&this->m_ptr_4 + 1) - v4;
      if ( ((SceneObj *)this)->UpdateAutoDelete(v6) )
        ((std *)v6)->string::_Eos();
    }
    ((std *)this)->string::_Split();
    return (int)this;
  }
  else
  {
    if ( !v3 )
      goto LABEL_24;
    v8 = *(unsigned __int8 **)(nVal + 4);
    if ( !v8 )
      v8 = &g_bActorFlag;
    if ( *(v8 - 1) < 0xFEu )
    {
      this->m_ptr_4 = 0;
      *((_DWORD *)&this->m_ptr_4 + 1) = 0;
      *((_DWORD *)&this->m_ptr_4 + 2) = 0;
      v9 = *(unsigned __int8 **)(nVal + 4);
      if ( !v9 )
        v9 = &g_bActorFlag;
      this->m_ptr_4 = v9;
      *((_DWORD *)&this->m_ptr_4 + 1) = *(_DWORD *)(nVal + 8);
      *((_DWORD *)&this->m_ptr_4 + 2) = *(_DWORD *)(nVal + 12);
      ++*(v9 - 1);
      return (int)this;
    }
    else
    {
LABEL_24:
      if ( ((SceneObj *)this)->UpdateAutoDelete(v3) )
      {
        v10 = *(unsigned __int8 **)(nVal + 4);
        if ( !v10 )
          v10 = &g_bActorFlag;
        qmemcpy(this->m_ptr_4, v10, v3);
        ((std *)v3)->string::_Eos();
      }
      return (int)this;
    }
  }
}
