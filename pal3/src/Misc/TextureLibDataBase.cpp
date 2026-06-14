#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/TextureLibDataBase.h"

// Unnamed globals (extern)
extern int unk_5D3C68;

// 0x00443A00
int TextureLibDataBase::CountEntries()
{
  int v2; // ebp
  int result; // eax
  int v4; // edi
  int v5; // eax
  char v6; // [esp+0x8] [ebp-0x48] BYREF
  __int16 v7; // [esp+0x9] [ebp-0x47]
  char v8; // [esp+0xB] [ebp-0x45]
  int v9; // [esp+0xC] [ebp-0x44]
  int v10; // [esp+0x4C] [ebp-0x4]

  v2 = 0;
  result = *(_DWORD *)&this->_libfolder[96];
  if ( result > 0 )
  {
    v4 = 0;
    do
    {
      v5 = *(_DWORD *)&this->_libfolder[100] + v4;
      if ( *(_DWORD *)(v5 + 44) )
      {
        if ( *(_BYTE *)v5 )
        {
          v9 = *(_DWORD *)(v5 + 44);
          v10 = 1;
          v7 = -1;
          v6 = -1;
          v8 = -1;
          ((TextureLibDataBase *)&v6)->SetLibFolder((char *)(v5 + 4));
        }
      }
      result = *(_DWORD *)&this->_libfolder[96];
      ++v2;
      v4 += 80;
    }
    while ( v2 < result );
  }
  return result;
}

// 0x00443A90
int TextureLibDataBase::SearchByIndex()
{
  int result; // eax
  int v2; // ebx
  int v3; // edi
  int v4; // edx
  int v5; // esi
  int v6; // esi

  result = 0;
  v2 = 0;
  if ( *(int *)&this->_libfolder[96] > 0 )
  {
    v3 = 0;
    do
    {
      v4 = v3 + *(_DWORD *)&this->_libfolder[100];
      v5 = *(_DWORD *)(v4 + 48);
      if ( v5 >= *(_DWORD *)&this->_libfolder[80]
        || v5 <= -256
        || (v6 = *(_DWORD *)(v4 + 56), v6 >= *(_DWORD *)&this->_libfolder[84])
        || v6 <= -256 )
      {
        *(_BYTE *)v4 = 0;
      }
      else
      {
        *(_BYTE *)v4 = 1;
        ++result;
      }
      ++v2;
      v3 += 80;
    }
    while ( v2 < *(_DWORD *)&this->_libfolder[96] );
  }
  return result;
}

// 0x004B4FE0
__int64 TextureLibDataBase::AutoScrollParticles(
        
        char *pszBuf,
        int nVal,
        TextureLibDataBase *pTextureLibDataBase,
        int nVal2)
{
  int v6; // edi
  char *tok; // edi
  Parent_Data v8; // edi
  double v9; // st7
  double v10; // st7
  double v11; // st7
  char *pszBufa; // [esp+0x54] [ebp+0x4]

  ((TextureLibDataBase *)pTextureLibDataBase)->GetLibInfo(pszBuf);
  if ( this->_libfolder[29] )
  {
    v6 = (__int64)*(float *)&this->_libfolder[132];
    *(float *)&this->_libfolder[124] = (double)(rand() % (2 * v6) - v6) + *(float *)&this->_libfolder[124];
    *(float *)&this->_libfolder[132] = *(float *)&this->_libfolder[140] + *(float *)&this->_libfolder[132];
  }
  if ( (double)(int)this->tok < *(float *)&this->_libfolder[124] )
  {
    tok = this->tok;
    *(float *)&this->_libfolder[124] = (float)(int)&tok[-(rand() % (int)&tok[-*(_DWORD *)this])];
  }
  if ( (double)(int)*((_DWORD *)this) > *(float *)&this->_libfolder[124] )
  {
    v8 = *((_DWORD *)this);
    *(float *)&this->_libfolder[124] = (float)(*(_DWORD *)&v8 + rand() % (int)&this->tok[-*(_DWORD *)&v8]);
  }
  if ( this->_libfolder[28] )
  {
    *(float *)&this->_libfolder[128] = *(float *)&this->_libfolder[128] - *(float *)&this->_libfolder[136] * 0.5;
    v10 = *(float *)&this->_libfolder[136] - *(float *)&this->_libfolder[144];
    *(float *)&this->_libfolder[136] = v10;
    if ( v10 <= 0.0 )
    {
      this->_libfolder[28] = 0;
      this->_libfolder[29] = 0;
    }
  }
  else
  {
    v9 = *(float *)&this->_libfolder[128] + *(float *)&this->_libfolder[136];
    pszBufa = (char *)(*(_DWORD *)this->_libfolder - *(_DWORD *)&this->_libfolder[16]);
    *(float *)&this->_libfolder[128] = v9;
    if ( v9 >= (double)(int)pszBufa )
      this->_libfolder[28] = 1;
    *(float *)&this->_libfolder[136] = *(float *)&this->_libfolder[144] + *(float *)&this->_libfolder[136];
  }
  v11 = (double)(unsigned __int8)this->_libfolder[115] - *(float *)&this->_libfolder[120];
  if ( v11 <= 0.0 )
  {
    v11 = 0.0;
    this->_libfolder[116] = 0;
    this->_libfolder[115] = 0;
    this->_libfolder[28] = 0;
    this->_libfolder[29] = 1;
  }
  this->_libfolder[115] = (__int64)v11;
  return (__int64)v11;
}

// 0x004B51A0
__int64 TextureLibDataBase::AutoScrollParticlesEx(
        
        char *pszBuf,
        TextureLibDataBase *pTextureLibDataBase,
        int nVal,
        int nVal2)
{
  char *v6; // ebp
  int v7; // edi
  int v8; // eax
  char *tok; // edi
  Parent_Data v10; // edi
  int v11; // edi
  double v12; // st7
  int v13; // edi
  __int64 result; // rax
  char *pszBufa; // [esp+0x58] [ebp+0x4]

  v6 = &this->_libfolder[112];
  ((TextureLibDataBase *)pTextureLibDataBase)->GetLib(pszBuf);
  v7 = *(_DWORD *)&this->_libfolder[20];
  *(float *)&this->_libfolder[124] = (double)(rand() % v7)
                                   - (double)(v7 / 2) * this->m_fScrollSpeed
                                   + *(float *)&this->_libfolder[124];
  v8 = rand();
  pszBufa = &this->tok[-*(_DWORD *)&this->_libfolder[12]];
  *(float *)&this->_libfolder[128] = (double)(v8 % *(_DWORD *)&this->_libfolder[24]) * this->m_fScrollSpeed
                                   + *(float *)&this->_libfolder[128];
  if ( (double)(int)pszBufa < *(float *)&this->_libfolder[124] )
  {
    tok = this->tok;
    *(float *)&this->_libfolder[124] = (float)(int)&tok[-(rand() % (int)&tok[-*(_DWORD *)this])];
  }
  if ( (double)(*(_DWORD *)this + *(_DWORD *)&this->_libfolder[12]) > *(float *)&this->_libfolder[124] )
  {
    v10 = *((_DWORD *)this);
    *(float *)&this->_libfolder[124] = (float)(*(_DWORD *)&v10 + rand() % (int)&this->tok[-*(_DWORD *)&v10]);
  }
  if ( (double)(*(_DWORD *)this->_libfolder - *(_DWORD *)&this->_libfolder[16]) < *(float *)&this->_libfolder[128] )
  {
    v11 = *(_DWORD *)this->_libfolder;
    *(float *)&this->_libfolder[128] = (float)(v11 - rand() % (signed int)(v11 - (unsigned int)this->Seps));
  }
  v12 = (double)(unsigned __int8)this->_libfolder[75] - *(float *)&this->_libfolder[120];
  if ( v12 <= 0.0 )
  {
    v12 = 0.0;
    this->_libfolder[116] = 0;
    this->_libfolder[75] = 0;
    this->_libfolder[28] = 0;
    this->_libfolder[29] = 1;
  }
  this->_libfolder[75] = (__int64)v12;
  v13 = 16 * (rand() % 12);
  this->_libfolder[114] = (__int64)*(float *)((char *)&unk_5D3C68 + v13);
  this->_libfolder[113] = (__int64)*(float *)(v13 + 6110308);
  result = (__int64)*(float *)(v13 + 6110304);
  this->_libfolder[115] = (__int64)v12;
  *v6 = result;
  return result;
}

// 0x004B5380
__int64 TextureLibDataBase::UpdateCircularMotion(
        
        char *pszBuf,
        int nVal,
        TextureLibDataBase *p,
        int nVal2)
{
  int v6; // ecx
  double v7; // st7
  int pszBufa; // [esp+0x4C] [ebp+0x4]

  ((TextureLibDataBase *)p)->GetLib(pszBuf);
  v6 = (unsigned __int8)this->_libfolder[115];
  pszBufa = *(_DWORD *)&this->_libfolder[24] / 2;
  *(float *)&this->_libfolder[124] = cos(*(float *)&this->_libfolder[32])
                                   * (double)(*(_DWORD *)&this->_libfolder[20] / 2)
                                   + *(float *)&this->_libfolder[36];
  *(float *)&this->_libfolder[128] = sin(*(float *)&this->_libfolder[32]) * (double)pszBufa
                                   + *(float *)&this->_libfolder[40];
  *(float *)&this->_libfolder[32] = this->m_fScrollSpeed + *(float *)&this->_libfolder[32];
  v7 = (double)v6 - *(float *)&this->_libfolder[120];
  if ( v7 <= 0.0 )
  {
    v7 = 0.0;
    this->_libfolder[116] = 0;
    this->_libfolder[115] = 0;
  }
  this->_libfolder[115] = (__int64)v7;
  return (__int64)v7;
}

// 0x004B5450
__int64 TextureLibDataBase::UpdateOrbitalMotion(
        
        char *pszBuf,
        int nVal,
        TextureLibDataBase *p,
        int nVal2)
{
  double v6; // st7
  double v7; // st7
  double v8; // st7
  float v10; // [esp+0x8] [ebp-0x48]
  int pszBufb; // [esp+0x54] [ebp+0x4]
  float pszBufa; // [esp+0x54] [ebp+0x4]

  ((TextureLibDataBase *)p)->GetLib(pszBuf);
  pszBufb = *(_DWORD *)&this->_libfolder[20] / 2;
  *(float *)&this->_libfolder[124] = cos(*(float *)&this->_libfolder[32]) * *(float *)&this->_libfolder[44]
                                   + *(float *)&this->_libfolder[36];
  *(float *)&this->_libfolder[128] = sin(*(float *)&this->_libfolder[32]) * *(float *)&this->_libfolder[48]
                                   + *(float *)&this->_libfolder[40];
  *(float *)&this->_libfolder[32] = this->m_fScrollSpeed + *(float *)&this->_libfolder[32];
  v6 = *(float *)&this->_libfolder[44] + 1.0;
  *(float *)&this->_libfolder[44] = v6;
  v10 = *(float *)&this->_libfolder[48] + 1.0;
  *(float *)&this->_libfolder[48] = v10;
  pszBufa = (float)pszBufb;
  if ( v6 >= pszBufa )
    *(float *)&this->_libfolder[44] = pszBufa;
  v7 = (double)(*(_DWORD *)&this->_libfolder[24] / 2);
  if ( v10 >= v7 )
    *(float *)&this->_libfolder[48] = v7;
  v8 = (double)(unsigned __int8)this->_libfolder[115] - *(float *)&this->_libfolder[120];
  if ( v8 <= 0.0 )
  {
    v8 = 0.0;
    this->_libfolder[116] = 0;
    this->_libfolder[115] = 0;
    *(_DWORD *)&this->_libfolder[44] = 0;
    *(_DWORD *)&this->_libfolder[48] = 0;
  }
  this->_libfolder[115] = (__int64)v8;
  return (__int64)v8;
}

// 0x004B5750
__int64 TextureLibDataBase::UpdateLinearMotion(
        
        char *pszBuf,
        int nVal,
        TextureLibDataBase *p,
        int nVal2)
{
  int v6; // edx
  char *v7; // eax
  double v8; // st7
  double v9; // st7
  int v10; // eax
  char *pszBufa; // [esp+0x4C] [ebp+0x4]

  ((TextureLibDataBase *)p)->GetLib(pszBuf);
  v6 = *(_DWORD *)&this->_libfolder[60];
  v7 = (char *)(unsigned __int8)this->_libfolder[115];
  *(_DWORD *)&this->_libfolder[124] = *(_DWORD *)&this->_libfolder[56];
  pszBufa = v7;
  LOBYTE(v7) = this->_libfolder[68];
  v8 = (double)(int)pszBufa;
  *(_DWORD *)&this->_libfolder[128] = v6;
  if ( (_BYTE)v7 )
  {
    v9 = v8 - *(float *)&this->_libfolder[120];
    if ( v9 <= 0.0 )
    {
      v10 = *(_DWORD *)&this->_libfolder[64];
      this->_libfolder[68] = 0;
      v9 = 0.0;
      *(_DWORD *)&this->_libfolder[64] = v10 - 1;
    }
  }
  else
  {
    v9 = v8 + *(float *)&this->_libfolder[120];
    if ( v9 >= 255.0 )
    {
      v9 = 255.0;
      this->_libfolder[68] = 1;
    }
  }
  if ( *(int *)&this->_libfolder[64] <= 0 )
  {
    v9 = 0.0;
    this->_libfolder[116] = 0;
    this->_libfolder[115] = 0;
  }
  this->_libfolder[115] = (__int64)v9;
  return (__int64)v9;
}

// 0x004B5D20
void TextureLibDataBase::RenderFrame(int nVal, int nVal2, int nVal3, int nVal4)
{
  int v5; // eax
  int v6; // eax
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  int v12; // [esp+0x4] [ebp-0x4C]
  char *v13; // [esp+0x4] [ebp-0x4C]
  int v14; // [esp+0x4] [ebp-0x4C]

  v12 = (__int64)(*(float *)&this->_libfolder[132] * this->m_fScrollSpeed);
  v5 = *(_DWORD *)&this->_libfolder[84];
  if ( v5 )
  {
    v6 = v5 - 1;
    if ( v6 )
    {
      if ( v6 == 1 )
      {
        v7 = (double)v12 + *(float *)&this->_libfolder[124];
        *(float *)&this->_libfolder[124] = v7;
        if ( v7 >= (double)(int)this->tok )
          *(_DWORD *)&this->_libfolder[84] = 1;
      }
      goto LABEL_12;
    }
    v8 = *(float *)&this->_libfolder[124] - (double)v12;
    *(float *)&this->_libfolder[124] = v8;
    if ( v8 > (double)(int)*((_DWORD *)this) )
      goto LABEL_12;
LABEL_11:
    *(_DWORD *)&this->_libfolder[84] = 2;
    goto LABEL_12;
  }
  v9 = (double)v12 + *(float *)&this->_libfolder[124];
  *(float *)&this->_libfolder[124] = v9;
  if ( v9 > (double)(int)this->tok )
    *(_DWORD *)&this->_libfolder[84] = 1;
  if ( v9 < (double)(int)*((_DWORD *)this) )
    goto LABEL_11;
LABEL_12:
  v10 = *(float *)&this->_libfolder[80] - *(float *)&this->_libfolder[136];
  v13 = &this->Seps[*(_DWORD *)&this->_libfolder[16]];
  *(float *)&this->_libfolder[128] = v10;
  if ( v10 <= (double)(int)v13 )
  {
    this->_libfolder[76] = 1;
    this->_libfolder[116] = 0;
  }
  v14 = (unsigned __int8)this->_libfolder[115];
  *(float *)&this->_libfolder[136] = *(float *)&this->_libfolder[144] * this->m_fScrollSpeed
                                   + *(float *)&this->_libfolder[136];
  v11 = (double)v14 - *(float *)&this->_libfolder[120];
  if ( v11 <= 0.0 )
  {
    v11 = 0.0;
    this->_libfolder[116] = 0;
    this->_libfolder[115] = 0;
    this->_libfolder[76] = 0;
  }
  this->_libfolder[115] = (__int64)v11;
  if ( this->_libfolder[116] || !this->_libfolder[76] )
    ((TextureLibDataBase *)*(TextureLibDataBase **)&this->_libfolder[404])->GetLib((char *)(__int64)(*(float *)&this->_libfolder[124] - (double)*(int *)&this->_libfolder[12]));
}

// 0x004B5EE0
char TextureLibDataBase::LoadLibrary(
        
        char *pszBuf,
        int nVal,
        TextureLibDataBase *pTextureLibDataBase,
        int nVal2)
{
  __int64 v6; // rax
  double v7; // st7

  ((TextureLibDataBase *)pTextureLibDataBase)->GetLib(pszBuf);
  switch ( *(_DWORD *)&this->_libfolder[88] )
  {
    case 0:
      if ( (double)(int)*((_DWORD *)this) >= *(float *)&this->_libfolder[124] )
      {
        *(_DWORD *)&this->_libfolder[88] = 1;
      }
      else
      {
        *(float *)&this->_libfolder[124] = *(float *)&this->_libfolder[124]
                                         - this->m_fScrollSpeed * *(float *)&this->_libfolder[132];
        *(float *)&this->_libfolder[132] = *(float *)&this->_libfolder[140] + *(float *)&this->_libfolder[132];
        *(float *)&this->_libfolder[128] = (double)(int)this->Seps + *(float *)&this->_libfolder[144];
      }
      break;
    case 1:
      if ( (double)*(int *)this->_libfolder <= *(float *)&this->_libfolder[128] )
      {
        *(_DWORD *)&this->_libfolder[88] = 2;
      }
      else
      {
        *(float *)&this->_libfolder[128] = this->m_fScrollSpeed * *(float *)&this->_libfolder[136]
                                         + *(float *)&this->_libfolder[128];
        *(float *)&this->_libfolder[136] = *(float *)&this->_libfolder[144] + *(float *)&this->_libfolder[136];
        *(float *)&this->_libfolder[124] = (double)(int)*((_DWORD *)this) + *(float *)&this->_libfolder[140];
      }
      break;
    case 2:
      if ( (double)(int)this->tok <= *(float *)&this->_libfolder[124] )
      {
        *(_DWORD *)&this->_libfolder[88] = 3;
      }
      else
      {
        *(float *)&this->_libfolder[124] = this->m_fScrollSpeed * *(float *)&this->_libfolder[132]
                                         + *(float *)&this->_libfolder[124];
        *(float *)&this->_libfolder[132] = *(float *)&this->_libfolder[140] + *(float *)&this->_libfolder[132];
        *(float *)&this->_libfolder[128] = (double)*(int *)this->_libfolder + *(float *)&this->_libfolder[144];
      }
      break;
    case 3:
      if ( (double)(int)this->Seps >= *(float *)&this->_libfolder[128] )
      {
        *(_DWORD *)&this->_libfolder[88] = 0;
      }
      else
      {
        *(float *)&this->_libfolder[128] = *(float *)&this->_libfolder[128]
                                         - this->m_fScrollSpeed * *(float *)&this->_libfolder[136];
        *(float *)&this->_libfolder[136] = *(float *)&this->_libfolder[144] + *(float *)&this->_libfolder[136];
        *(float *)&this->_libfolder[124] = (double)(int)this->tok + *(float *)&this->_libfolder[140];
      }
      break;
    default:
      break;
  }
  LOBYTE(v6) = this->_libfolder[92];
  if ( (_BYTE)v6 )
  {
    v7 = (double)(unsigned __int8)this->_libfolder[115] - this->m_fScrollSpeed * *(float *)&this->_libfolder[120];
    if ( v7 <= 0.0 )
    {
      v7 = 0.0;
      this->_libfolder[116] = 0;
      this->_libfolder[115] = 0;
    }
    v6 = (__int64)v7;
    this->_libfolder[115] = (__int64)v7;
  }
  return v6;
}

// 0x004B60F0
char TextureLibDataBase::UpdateByMode(
        
        char *pszBuf,
        int nVal,
        TextureLibDataBase *p,
        int nVal2)
{
  __int64 v6; // rax
  double v7; // st7

  ((TextureLibDataBase *)p)->GetLib(pszBuf);
  switch ( *(_DWORD *)&this->_libfolder[88] )
  {
    case 0:
      if ( (double)(int)this->tok <= *(float *)&this->_libfolder[124] )
      {
        *(_DWORD *)&this->_libfolder[88] = 1;
      }
      else
      {
        *(float *)&this->_libfolder[124] = this->m_fScrollSpeed * *(float *)&this->_libfolder[132]
                                         + *(float *)&this->_libfolder[124];
        *(float *)&this->_libfolder[132] = *(float *)&this->_libfolder[140] + *(float *)&this->_libfolder[132];
        *(float *)&this->_libfolder[128] = (double)(int)this->Seps + *(float *)&this->_libfolder[144];
      }
      break;
    case 1:
      if ( (double)*(int *)this->_libfolder <= *(float *)&this->_libfolder[128] )
      {
        *(_DWORD *)&this->_libfolder[88] = 2;
      }
      else
      {
        *(float *)&this->_libfolder[128] = this->m_fScrollSpeed * *(float *)&this->_libfolder[136]
                                         + *(float *)&this->_libfolder[128];
        *(float *)&this->_libfolder[136] = *(float *)&this->_libfolder[144] + *(float *)&this->_libfolder[136];
        *(float *)&this->_libfolder[124] = (double)(int)this->tok + *(float *)&this->_libfolder[140];
      }
      break;
    case 2:
      if ( (double)(int)*((_DWORD *)this) >= *(float *)&this->_libfolder[124] )
      {
        *(_DWORD *)&this->_libfolder[88] = 3;
      }
      else
      {
        *(float *)&this->_libfolder[124] = *(float *)&this->_libfolder[124]
                                         - this->m_fScrollSpeed * *(float *)&this->_libfolder[132];
        *(float *)&this->_libfolder[132] = *(float *)&this->_libfolder[140] + *(float *)&this->_libfolder[132];
        *(float *)&this->_libfolder[128] = (double)*(int *)this->_libfolder + *(float *)&this->_libfolder[144];
      }
      break;
    case 3:
      if ( (double)(int)this->Seps >= *(float *)&this->_libfolder[128] )
      {
        *(_DWORD *)&this->_libfolder[88] = 0;
      }
      else
      {
        *(float *)&this->_libfolder[128] = *(float *)&this->_libfolder[128]
                                         - this->m_fScrollSpeed * *(float *)&this->_libfolder[136];
        *(float *)&this->_libfolder[136] = *(float *)&this->_libfolder[144] + *(float *)&this->_libfolder[136];
        *(float *)&this->_libfolder[124] = (double)(int)*((_DWORD *)this) + *(float *)&this->_libfolder[140];
      }
      break;
    default:
      break;
  }
  LOBYTE(v6) = this->_libfolder[92];
  if ( (_BYTE)v6 )
  {
    v7 = (double)(unsigned __int8)this->_libfolder[115] - this->m_fScrollSpeed * *(float *)&this->_libfolder[120];
    if ( v7 <= 0.0 )
    {
      v7 = 0.0;
      this->_libfolder[116] = 0;
      this->_libfolder[115] = 0;
    }
    v6 = (__int64)v7;
    this->_libfolder[115] = (__int64)v7;
  }
  return v6;
}

// 0x004B6300
__int64 TextureLibDataBase::GetTextureByName(
        
        char *pszBuf,
        int nVal,
        TextureLibDataBase *pTextureLibDataBase,
        int nVal2)
{
  double v6; // st7

  ((TextureLibDataBase *)pTextureLibDataBase)->GetLib(pszBuf);
  v6 = (double)(unsigned __int8)this->_libfolder[115] - this->m_fScrollSpeed * *(float *)&this->_libfolder[120];
  if ( v6 <= 0.0 )
  {
    v6 = 0.0;
    this->_libfolder[116] = 0;
    this->_libfolder[115] = 0;
  }
  this->_libfolder[115] = (__int64)v6;
  return (__int64)v6;
}

// 0x0053FDD0
Parent_Data * TextureLibDataBase::CreateParentData(LPCSTR lpString)
{
  int v3; // edi
  int i; // ebx

  if ( !this->_isLoadTLI )
    return 0;
  if ( lstrlenA(lpString) <= 0 )
    return 0;
  v3 = 0;
  if ( this->_realNum <= 0 )
    return 0;
  for ( i = 0; _strcmpi(lpString, this->m_pData[i]._tex_name); ++i )
  {
    if ( ++v3 >= this->_realNum )
      return 0;
  }
  return (Parent_Data *)&this->m_pData[v3];
}

// 0x0053FFA0
void TextureLibDataBase::_TextureLib_Data()
{
  if ( g_pRenderEffect_1895048 )
  {
// [VFTABLE] ((gbRefObject *)&g_pRenderEffect_1895048->__vftable)->Release();
    g_pRenderEffect_1895048 = 0;
  }
  if ( g_pRenderEffect_189504C )
  {
// [VFTABLE] ((gbRefObject *)&g_pRenderEffect_189504C->__vftable)->Release();
    g_pRenderEffect_189504C = 0;
  }
  if ( g_pRenderEffect_1895054 )
  {
// [VFTABLE] ((gbRefObject *)&g_pRenderEffect_1895054->__vftable)->Release();
    g_pRenderEffect_1895054 = 0;
  }
  if ( g_pRenderEffect_189505C )
  {
// [VFTABLE] ((gbRefObject *)&g_pRenderEffect_189505C->__vftable)->Release();
    g_pRenderEffect_189505C = 0;
  }
  if ( g_pRenderEffect_1895068 )
  {
// [VFTABLE] ((gbRefObject *)&g_pRenderEffect_1895068->__vftable)->Release();
    g_pRenderEffect_1895068 = 0;
  }
  if ( g_pRenderEffect_1895050 )
  {
// [VFTABLE] ((gbRefObject *)&g_pRenderEffect_1895050->__vftable)->Release();
    g_pRenderEffect_1895050 = 0;
  }
  if ( g_pTexColorEffect )
  {
    ((gbRefObject *)g_pTexColorEffect)->Release();
    g_pTexColorEffect = 0;
  }
  if ( g_pRenderEffect_1895060 )
  {
// [VFTABLE] ((gbRefObject *)&g_pRenderEffect_1895060->__vftable)->Release();
    g_pRenderEffect_1895060 = 0;
  }
  if ( g_pRenderEffect_1895064 )
  {
// [VFTABLE] ((gbRefObject *)&g_pRenderEffect_1895064->__vftable)->Release();
    g_pRenderEffect_1895064 = 0;
  }
  if ( g_nParent_Data_189506C )
  {
    ((gbRefObject *)g_nParent_Data_189506C)->Release();
    g_nParent_Data_189506C = 0;
  }
}

// 0x005400E0
unsigned int TextureLibDataBase::_GetItemNum(void *pData)
{
  float v2; // ecx
  gbTexture *v3; // ecx
  long double v4; // st7
  double width; // st7
  gbRenderEffect *v6; // esi
  gbDynVertBuf *DynVertBuf; // eax
  unsigned int result; // eax
  struct gbUIQuad v9; // [esp+0x8] [ebp-0x28] BYREF
  gbTextureArray *v10; // [esp+0x38] [ebp+0x8]
  unsigned int v11; // [esp+0x3C] [ebp+0xC]
  int v12; // [esp+0x3C] [ebp+0xC]
  int v13; // [esp+0x3C] [ebp+0xC]
  float height; // [esp+0x3C] [ebp+0xC]
  float *v15; // [esp+0x40] [ebp+0x10]

  v9.color = v11;
  v9.z = 0.0;
  if ( v15 )
  {
    v9.su = v15[262];
    v9.sv = v15[263];
    v2 = v15[267];
    v9.eu = v15[266];
    v9.ev = v2;
  }
  else
  {
    v3 = v10->pTexPt[0];
    v12 = *((_DWORD *)pData + 2) - *(_DWORD *)pData;
    v9.sv = 0.0;
    v9.su = 0.0;
    v4 = (fabs((double)v12) + -0.5) / (double)v3->Width;
    v13 = *((_DWORD *)pData + 3) - *((_DWORD *)pData + 1);
    v9.eu = v4;
    v9.ev = (fabs((double)v13) + -0.5) / (double)v3->Height;
  }
  width = (double)g_DrvInfo.width;
  v6 = g_pRenderEffect_1895048;
  v9.sx = ((double)*(int *)pData + (double)*(int *)pData) / width - 1.0;
  height = (float)g_DrvInfo.height;
  v9.ey = 1.0 - ((double)*((int *)pData + 1) + (double)*((int *)pData + 1)) / height;
  v9.ex = ((double)*((int *)pData + 2) + (double)*((int *)pData + 2)) / width - 1.0;
  v9.sy = 1.0 - ((double)*((int *)pData + 3) + (double)*((int *)pData + 3)) / height;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v9, 1, v6, v10);
  return result;
}

// 0x00540210
int TextureLibDataBase::_CheckItem(char *pszName, char *pszBuf)
{
  float v3; // edx
  float v4; // eax
  float v5; // ecx
  gbTexture *v6; // ecx
  unsigned int v7; // eax
  gbRenderEffect *v8; // esi
  double v9; // st7
  double width; // st7
  __int64 v12; // rax
  double v13; // st7
  gbDynVertBuf *DynVertBuf; // eax
  int result; // eax
  __int64 v16; // [esp+0x10] [ebp-0x30]
  __int64 v17; // [esp+0x10] [ebp-0x30]
  struct gbUIQuad v18; // [esp+0x18] [ebp-0x28] BYREF
  float pszBufa; // [esp+0x48] [ebp+0x8]
  gbTextureArray *v20; // [esp+0x4C] [ebp+0xC]
  unsigned int v21; // [esp+0x50] [ebp+0x10]
  int v22; // [esp+0x50] [ebp+0x10]
  unsigned int v23; // [esp+0x54] [ebp+0x14]
  int v24; // [esp+0x58] [ebp+0x18]

  v18.z = 0.0;
  v18.color = v21;
  if ( v24 )
  {
    v3 = *(float *)(v24 + 1052);
    v4 = *(float *)(v24 + 1064);
    v18.su = *(float *)(v24 + 1048);
    v5 = *(float *)(v24 + 1068);
    v18.sv = v3;
    v18.eu = v4;
    v18.ev = v5;
  }
  else
  {
    v6 = v20->pTexPt[0];
    v18.sv = 0.0;
    v18.su = 0.0;
    v22 = *((_DWORD *)pszName + 3) - *((_DWORD *)pszName + 1);
    v18.eu = (fabs((double)(*((_DWORD *)pszName + 2) - *(_DWORD *)pszName)) + -0.5) / (double)v6->Width;
    v18.ev = (fabs((double)v22) + -0.5) / (double)v6->Height;
  }
  if ( (v23 & 0x100) != 0 )
  {
    v18.sx = (float)*(int *)pszBuf;
    v18.ey = (double)*((int *)pszBuf + 1) - 0.5;
    if ( v24 )
    {
      v7 = *(_DWORD *)(v24 + 1040);
      v16 = v7;
      LODWORD(v16) = *(_DWORD *)(v24 + 1044);
      v8 = g_pRenderEffect_189504C;
      v18.ex = (double)v7 + v18.sx + 0.5;
      v9 = (double)v16 + v18.ey + 0.5;
    }
    else
    {
      v8 = g_pRenderEffect_189504C;
      v18.ex = (float)*((int *)pszBuf + 2);
      v9 = (double)*((int *)pszBuf + 3);
    }
    v18.sy = v9;
  }
  else
  {
    width = (double)g_DrvInfo.width;
    v18.sx = ((double)*(int *)pszBuf + (double)*(int *)pszBuf) / width - 1.0;
    pszBufa = (float)g_DrvInfo.height;
    v18.ey = 1.0 - ((double)*((int *)pszBuf + 1) + (double)*((int *)pszBuf + 1)) / pszBufa;
    if ( v24 )
    {
      v12 = (__int64)((double)*(unsigned int *)(v24 + 1040) + v18.sx + 0.5);
      v17 = *(unsigned int *)(v24 + 1044);
      v18.ex = ((double)(int)v12 + (double)(int)v12) / width - 1.0;
      v13 = (double)(int)(__int64)((double)v17 + v18.ey + 0.5);
    }
    else
    {
      v18.ex = ((double)*((int *)pszBuf + 2) + (double)*((int *)pszBuf + 2)) / width - 1.0;
      v13 = (double)*((int *)pszBuf + 3);
    }
    v8 = g_pRenderEffect_1895048;
    v18.sy = 1.0 - (v13 + v13) / pszBufa;
  }
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(v23);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v18, 1, v8, v20);
  return result;
}

// 0x00540440
void TextureLibDataBase::SetLibFolder(char *pszFolder)
{
  __int64 v2; // rcx
  float v3; // ecx
  float v4; // edx
  float v5; // ecx
  gbTexture *v6; // ecx
  long double v7; // st7
  double v8; // st7
  gbRenderEffect *v9; // esi
  double v10; // st6
  __int64 v11; // rax
  double v12; // st5
  gbDynVertBuf *DynVertBuf; // eax
  __int64 v14; // [esp+0x10] [ebp-0x30]
  struct gbUIQuad v15; // [esp+0x18] [ebp-0x28] BYREF
  unsigned int *v16; // [esp+0x48] [ebp+0x8]
  int v17; // [esp+0x48] [ebp+0x8]
  int v18; // [esp+0x48] [ebp+0x8]
  float height; // [esp+0x48] [ebp+0x8]
  gbTextureArray *v20; // [esp+0x4C] [ebp+0xC]
  unsigned int v21; // [esp+0x50] [ebp+0x10]
  int v22; // [esp+0x54] [ebp+0x14]
  char v23; // [esp+0x58] [ebp+0x18]
  float width; // [esp+0x58] [ebp+0x18]

  v2 = *v16;
  v15.z = 0.0;
  v15.color = v2;
  if ( v22 )
  {
    v3 = *(float *)(v22 + 1052);
    v15.su = *(float *)(v22 + 1048);
    v4 = *(float *)(v22 + 1064);
    v15.sv = v3;
    v5 = *(float *)(v22 + 1068);
    v15.eu = v4;
    v15.ev = v5;
  }
  else
  {
    v6 = v20->pTexPt[0];
    v17 = *((_DWORD *)pszFolder + 2) - *(_DWORD *)pszFolder;
    v15.sv = 0.0;
    v15.su = 0.0;
    v7 = (fabs((double)v17) + -0.5) / (double)v6->Width;
    v18 = *((_DWORD *)pszFolder + 3) - *((_DWORD *)pszFolder + 1);
    v15.eu = v7;
    v15.ev = (fabs((double)v18) + -0.5) / (double)v6->Height;
  }
  if ( (v21 & 0x100) != 0 )
  {
    v8 = (double)*(int *)pszFolder;
    v15.ey = (float)*((int *)pszFolder + 1);
    if ( v22 == HIDWORD(v2) || v23 == BYTE4(v2) )
    {
      v10 = (double)*((int *)pszFolder + 2);
      v9 = g_pRenderEffect_189504C;
      v15.sy = (float)*((int *)pszFolder + 3);
    }
    else
    {
      LODWORD(v2) = *(_DWORD *)(v22 + 1044);
      v9 = g_pRenderEffect_189504C;
      v10 = (double)*(unsigned int *)(v22 + 1040) + v8;
      v15.sy = (double)v2 + v15.ey;
    }
  }
  else
  {
    width = (float)g_DrvInfo.width;
    v8 = ((double)*(int *)pszFolder + (double)*(int *)pszFolder) / width - 1.0;
    height = (float)g_DrvInfo.height;
    v15.ey = 1.0 - ((double)*((int *)pszFolder + 1) + (double)*((int *)pszFolder + 1)) / height;
    if ( v22 == HIDWORD(v2) )
    {
      v10 = ((double)*((int *)pszFolder + 2) + (double)*((int *)pszFolder + 2)) / width - 1.0;
      v12 = (double)*((int *)pszFolder + 3);
    }
    else
    {
      v11 = (__int64)((double)__PAIR64__(HIDWORD(v2), *(_DWORD *)(v22 + 1040)) + v8);
      LODWORD(v14) = *(_DWORD *)(v22 + 1044);
      HIDWORD(v14) = HIDWORD(v2);
      v10 = ((double)(int)v11 + (double)(int)v11) / width - 1.0;
      v12 = (double)(int)(__int64)((double)v14 + v15.ey);
    }
    v9 = g_pRenderEffect_1895048;
    v15.sy = 1.0 - (v12 + v12) / height;
  }
  v15.sx = v8 - -0.5;
  v15.ex = v10 - -0.5;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(v21);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v15, 1, v9, v20);
}

// 0x00540650
bool TextureLibDataBase::GetLibInfo(char *pszName)
{
  float v2; // ecx
  float v3; // edx
  float v4; // ecx
  gbTexture *v5; // ecx
  double v6; // st7
  double v7; // st6
  double v8; // st5
  gbDynVertBuf *DynVertBuf; // eax
  gbRenderEffect *v10; // edx
  bool result; // al
  gbTextureArray *v12; // [esp-0x4] [ebp-0x38]
  struct gbUIQuad v13; // [esp+0xC] [ebp-0x28] BYREF
  int v14; // [esp+0x3C] [ebp+0x8]
  int v15; // [esp+0x40] [ebp+0xC]
  int v16; // [esp+0x44] [ebp+0x10]
  unsigned int *v17; // [esp+0x48] [ebp+0x14]
  gbTextureArray *v18; // [esp+0x4C] [ebp+0x18]
  int v19; // [esp+0x50] [ebp+0x1C]
  int v20; // [esp+0x54] [ebp+0x20]

  v13.z = 0.0;
  v13.color = *v17;
  if ( v20 )
  {
    v2 = *(float *)(v20 + 1052);
    v13.su = *(float *)(v20 + 1048);
    v3 = *(float *)(v20 + 1064);
    v13.sv = v2;
    v4 = *(float *)(v20 + 1068);
    v13.eu = v3;
    v13.ev = v4;
  }
  else
  {
    v5 = v18->pTexPt[0];
    v13.sv = 0.0;
    v13.su = 0.0;
    v13.eu = (fabs((double)(v15 - (int)pszName)) + -0.5) / (double)v5->Width;
    v13.ev = (fabs((double)(v16 - v14)) + -0.5) / (double)v5->Height;
  }
  v6 = (double)(int)pszName;
  v13.ey = (float)v14;
  if ( v20 )
  {
    v7 = (double)*(unsigned int *)(v20 + 1040) + v6;
    v8 = (double)*(unsigned int *)(v20 + 1044) + v13.ey;
  }
  else
  {
    v7 = (double)v15;
    v8 = (double)v16;
  }
  v13.sy = v8;
  v13.sx = v6 - -0.5;
  v13.ex = v7 - -0.5;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  if ( !v19 )
  {
    v12 = v18;
    goto LABEL_11;
  }
  v12 = v18;
  if ( v19 != 1 )
  {
LABEL_11:
    v10 = (gbRenderEffect *)g_pTexColorEffect;
    goto LABEL_12;
  }
  v10 = g_pRenderEffect_1895054;
LABEL_12:
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v13, 1, v10, v12);
  return result;
}

// 0x005407A0
char * TextureLibDataBase::GetLib(char *pszName)
{
  unsigned int v2; // ecx
  __int64 v3; // rax
  gbTexture *v4; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st5
  gbDynVertBuf *DynVertBuf; // eax
  char *result; // eax
  struct gbUIQuad v10; // [esp+0xC] [ebp-0x28] BYREF
  int v11; // [esp+0x3C] [ebp+0x8]
  int v12; // [esp+0x40] [ebp+0xC]
  int v13; // [esp+0x44] [ebp+0x10]
  unsigned int *v14; // [esp+0x48] [ebp+0x14]
  gbTextureArray *v15; // [esp+0x4C] [ebp+0x18]
  unsigned int v16; // [esp+0x50] [ebp+0x1C]

  v2 = *v14;
  v3 = v16;
  v10.z = 0.0;
  v10.color = v2;
  if ( v16 )
  {
    v10.su = *(float *)(v16 + 1048);
    v10.sv = *(float *)(v16 + 1052);
    v10.eu = *(float *)(v16 + 1064);
    v10.ev = *(float *)(v16 + 1068);
  }
  else
  {
    v4 = v15->pTexPt[0];
    v10.sv = 0.0;
    v10.su = 0.0;
    v10.eu = (fabs((double)(v12 - (int)pszName)) + -0.5) / (double)v4->Width;
    v10.ev = (fabs((double)(v13 - v11)) + -0.5) / (double)v4->Height;
  }
  v5 = (double)(int)pszName;
  v10.ey = (float)v11;
  if ( v16 )
  {
    LODWORD(v3) = *(_DWORD *)(v16 + 1044);
    v6 = (double)*(unsigned int *)(v16 + 1040) + v5;
    v7 = (double)v3 + v10.ey;
  }
  else
  {
    v6 = (double)v12;
    v7 = (double)v13;
  }
  v10.sy = v7;
  v10.sx = v5 - -0.5;
  v10.ex = v6 - -0.5;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v10, 1, g_pRenderEffect_189505C, v15);
  return result;
}

// 0x005408E0
_Texture_Info * TextureLibDataBase::GetTextureInfo(char *pszName)
{
  float v2; // ecx
  float v3; // edx
  float v4; // ecx
  gbTexture *v5; // edx
  int v6; // ebx
  double v7; // st7
  gbDynVertBuf *DynVertBuf; // eax
  _Texture_Info *result; // eax
  __int64 v10; // [esp+0x4] [ebp-0x30]
  struct gbUIQuad v11; // [esp+0xC] [ebp-0x28] BYREF
  int *v12; // [esp+0x3C] [ebp+0x8]
  unsigned int *v13; // [esp+0x40] [ebp+0xC]
  int v14; // [esp+0x40] [ebp+0xC]
  gbTextureArray *v15; // [esp+0x44] [ebp+0x10]
  int v16; // [esp+0x48] [ebp+0x14]

  v11.z = 0.0;
  v11.color = *v13;
  if ( v16 )
  {
    v2 = *(float *)(v16 + 1052);
    v11.su = *(float *)(v16 + 1048);
    v3 = *(float *)(v16 + 1064);
    v11.sv = v2;
    v4 = *(float *)(v16 + 1068);
    v11.eu = v3;
    v11.ev = v4;
  }
  else
  {
    v5 = v15->pTexPt[0];
    v6 = *((_DWORD *)pszName + 2) - *(_DWORD *)pszName;
    v11.sv = 0.0;
    v11.su = 0.0;
    v14 = *((_DWORD *)pszName + 3) - *((_DWORD *)pszName + 1);
    v11.eu = (fabs((double)v6) + -0.5) / (double)v5->Width;
    v11.ev = (fabs((double)v14) + -0.5) / (double)v5->Height;
  }
  v11.sx = (float)*v12;
  v11.ey = (float)v12[1];
  if ( v16 )
  {
    v10 = *(unsigned int *)(v16 + 1044);
    v11.ex = (double)*(unsigned int *)(v16 + 1040) + v11.sx;
    v7 = (double)v10 + v11.ey;
  }
  else
  {
    v11.ex = (float)v12[2];
    v7 = (double)v12[3];
  }
  v11.sy = v7;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v11, 1, g_pRenderEffect_1895054, v15);
  return result;
}

// 0x00540A20
_Texture_Info * TextureLibDataBase::GetTextureInfoByIndex(int nIndex)
{
  double v2; // st7
  double v3; // st6
  double v4; // st5
  gbDynVertBuf *DynVertBuf; // eax
  _Texture_Info *result; // eax
  struct gbUIQuad v7; // [esp+0x8] [ebp-0x28] BYREF
  int v8; // [esp+0x38] [ebp+0x8]
  int v9; // [esp+0x3C] [ebp+0xC]
  int v10; // [esp+0x40] [ebp+0x10]
  unsigned int *v11; // [esp+0x44] [ebp+0x14]
  gbTextureArray *v12; // [esp+0x48] [ebp+0x18]
  int v13; // [esp+0x4C] [ebp+0x1C]

  v7.z = 0.0;
  v7.color = *v11;
  if ( v13 )
  {
    v7.su = *(float *)(v13 + 1048);
    v7.sv = *(float *)(v13 + 1052);
    v7.eu = *(float *)(v13 + 1064);
    v7.ev = *(float *)(v13 + 1068);
  }
  else
  {
    v7.su = 0.0;
    v7.sv = 0.0;
    v7.eu = 1.0;
    v7.ev = 1.0;
  }
  v2 = (double)nIndex;
  v7.ey = (float)v8;
  if ( v13 )
  {
    v3 = (double)*(unsigned int *)(v13 + 1040) + v2;
    v4 = (double)*(unsigned int *)(v13 + 1044) + v7.ey;
  }
  else
  {
    v3 = (double)v9;
    v4 = (double)v10;
  }
  v7.sy = v4;
  v7.sx = v2 - -0.5;
  v7.ex = v3 - -0.5;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v7, 1, (gbRenderEffect *)g_pTexColorEffect, v12);
  return result;
}
