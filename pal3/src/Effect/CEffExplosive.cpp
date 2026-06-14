#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffExplosive.h"

// 0x004C7C00
void CEffExplosive::InitDefaultUVSet(int nFramePerRow, int nFramePerCol)
{
  int v3; // ebx
  float *p_eu; // edi
  int v5; // ecx
  double v6; // st7
  float *v7; // eax
  double v8; // st5
  double v9; // st5
  double v10; // st3
  double v11; // st3
  int v12; // [esp+0x8] [ebp-0x8]
  float v13; // [esp+0x8] [ebp-0x8]
  int v14; // [esp+0xC] [ebp-0x4]

  v3 = 0;
  v12 = 0;
  if ( nFramePerCol > 0 )
  {
    p_eu = &this->m_DefaultUVSet[0].eu;
    do
    {
      v5 = 0;
      v14 = 0;
      if ( nFramePerRow > 0 )
      {
        v6 = (double)nFramePerRow;
        v7 = p_eu;
        p_eu += 4 * nFramePerRow;
        v8 = (double)nFramePerCol;
        v13 = (double)v12 / v8;
        v9 = 1.0 - (1.0 / v8 + v13);
        do
        {
          v10 = (double)v14;
          v7 += 4;
          v14 = ++v5;
          v11 = v10 / v6;
          *(v7 - 6) = v11;
          *(v7 - 4) = 1.0 / v6 + v11;
          *(v7 - 5) = v9;
          *(v7 - 3) = 1.0 - v13;
        }
        while ( v5 < nFramePerRow );
      }
      v12 = ++v3;
    }
    while ( v3 < nFramePerCol );
  }
}

// 0x004C7CB0
int * CEffExplosive::LoadTexture(char *pFileName)
{
  gbTexture *v3; // eax
  int *result; // eax
  gbTexture *m_pTexture; // ecx
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x800] BYREF
  char ArgList; // [esp+0x408] [ebp-0x400] BYREF

  v3 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)this->m_pEM->m_pDisplay + 8))(
                      this->m_pEM->m_pDisplay,
                      pFileName);
  this->m_pTexture = v3;
  ((gbTexture *)v3)->LoadTexture(1);
  result = (int *)operator new(0x44u);
  if ( result )
  {
    m_pTexture = this->m_pTexture;
    result[16] = 1;
    *result = (int)m_pTexture;
  }
  else
  {
    result = 0;
  }
  this->m_pTextureArray = (gbTextureArray *)result;
  if ( !result )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("C++ new failed!", "D:\\Project\\PAL3\\combat\\EffExplosive.cpp", 499),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004C7D40
void CEffExplosive::CreateGeom()
{
  int m_nXDivision; // edx
  unsigned int v2; // ebx
  int v3; // ebp
  double v4; // st7
  double v5; // st6
  int v6; // esi
  unsigned int v7; // eax
  gbGeomQuad *m_pGeomQuad; // edx
  gbGeomQuad *v9; // edx
  gbGeomQuad *v10; // edx
  gbGeomQuad *v11; // edx
  gbGeomQuad *v12; // edx
  double v13; // st5
  float *p_z; // edx
  int m_nZDivision; // [esp+0x4] [ebp-0x8]
  float v16; // [esp+0x8] [ebp-0x4]

  m_nXDivision = this->m_nXDivision;
  m_nZDivision = this->m_nZDivision;
  v2 = 0;
  v3 = 0;
  v16 = (double)m_nXDivision * this->m_fGridSize * -0.5;
  v4 = (double)m_nZDivision * this->m_fGridSize * 0.5;
  if ( m_nZDivision > 0 )
  {
    do
    {
      v5 = v16;
      v6 = 0;
      if ( m_nXDivision > 0 )
      {
        v7 = v2;
        do
        {
          m_pGeomQuad = this->m_pGeomQuad;
          m_pGeomQuad[v7].vec[0].y = 0.0;
          m_pGeomQuad[v7].vec[0].x = v5;
          ++v2;
          m_pGeomQuad[v7].vec[0].z = v4;
          v9 = this->m_pGeomQuad;
          v9[v7].vec[1].y = 0.0;
          v9[v7].vec[1].x = v5;
          v9[v7].vec[1].z = v4;
          this->m_pGeomQuad[v7].vec[1].x = this->m_pGeomQuad[v7].vec[1].x + this->m_fGridSize;
          v10 = this->m_pGeomQuad;
          v10[v7].vec[2].y = 0.0;
          v10[v7].vec[2].x = v5;
          v10[v7].vec[2].z = v4;
          this->m_pGeomQuad[v7].vec[2].x = this->m_pGeomQuad[v7].vec[2].x + this->m_fGridSize;
          this->m_pGeomQuad[v7].vec[2].z = this->m_pGeomQuad[v7].vec[2].z - this->m_fGridSize;
          v11 = this->m_pGeomQuad;
          v11[v7].vec[3].y = 0.0;
          v11[v7].vec[3].x = v5;
          v11[v7].vec[3].z = v4;
          v12 = this->m_pGeomQuad;
          v13 = v12[v7].vec[3].z - this->m_fGridSize;
          p_z = &v12[v7++].vec[3].z;
          ++v6;
          *p_z = v13;
          m_nXDivision = this->m_nXDivision;
          v5 = v5 + this->m_fGridSize;
        }
        while ( v6 < m_nXDivision );
      }
      ++v3;
      v4 = v4 - this->m_fGridSize;
    }
    while ( v3 < this->m_nZDivision );
  }
}

// 0x004C8370
void CEffExplosive::UpdateExplosive(float fDeltaTime, int fTime)
{
  unsigned int v4; // ebp
  unsigned int v5; // edi
  int v6; // ebp
  float *v7; // eax
  double v8; // st7
  gbGeomQuad *m_pGeomQuad; // ecx
  float *p_x; // eax
  gbGeomQuad *v11; // edx
  float *v12; // eax
  gbGeomQuad *v13; // eax
  double x; // st6
  float *v15; // eax
  tagExplosive *m_pExplosive; // ecx
  gbGeomQuad *v17; // eax
  double v18; // st7
  float *v19; // eax
  gbGeomQuad *v20; // ecx
  float *v21; // eax
  gbGeomQuad *v22; // edx
  float *v23; // eax
  gbGeomQuad *v24; // eax
  double v25; // st7
  float *v26; // eax
  unsigned int v27; // edx
  bool v28; // cc
  float v29; // [esp+0x4] [ebp-0x90]
  float v30; // [esp+0x8] [ebp-0x8C]
  float v31; // [esp+0xC] [ebp-0x88]
  int v32; // [esp+0x20] [ebp-0x74]
  int v33; // [esp+0x24] [ebp-0x70]
  int i; // [esp+0x28] [ebp-0x6C]
  float v35; // [esp+0x2C] [ebp-0x68]
  float v36; // [esp+0x30] [ebp-0x64]
  float v37; // [esp+0x30] [ebp-0x64]
  float v38; // [esp+0x34] [ebp-0x60]
  float v39; // [esp+0x34] [ebp-0x60]
  float v40; // [esp+0x3C] [ebp-0x58]
  float v41; // [esp+0x40] [ebp-0x54]
  gbQuaternion v42; // [esp+0x44] [ebp-0x50] BYREF
  gbMatrix4 v43; // [esp+0x54] [ebp-0x40] BYREF

  memset(&v42, 0, 12);
  v42.w = 1.0;
  v4 = 0;
  v32 = 0;
  for ( i = 0; i < this->m_nXDivision; ++i )
  {
    v33 = 0;
    if ( this->m_nZDivision > 0 )
    {
      v5 = v4;
      v6 = v4;
      do
      {
        v7 = (float *)&this->m_pGeomQuad[v5];
        v8 = (v7[9] + v7[6] + v7[3] + *v7) * 0.25;
        v36 = (v7[10] + v7[7] + v7[4] + v7[1]) * 0.25;
        v38 = (v7[11] + v7[8] + v7[5] + v7[2]) * 0.25;
        *v7 = *v7 - v8;
        v7[1] = v7[1] - v36;
        v7[2] = v7[2] - v38;
        m_pGeomQuad = this->m_pGeomQuad;
        p_x = &m_pGeomQuad[v5].vec[1].x;
        *p_x = *p_x - v8;
        p_x[1] = m_pGeomQuad[v5].vec[1].y - v36;
        p_x[2] = m_pGeomQuad[v5].vec[1].z - v38;
        v11 = this->m_pGeomQuad;
        v12 = &v11[v5].vec[2].x;
        *v12 = *v12 - v8;
        v12[1] = v11[v5].vec[2].y - v36;
        v12[2] = v11[v5].vec[2].z - v38;
        v13 = this->m_pGeomQuad;
        x = v13[v5].vec[3].x;
        v15 = &v13[v5].vec[3].x;
        *v15 = x - v8;
        v15[1] = v15[1] - v36;
        v15[2] = v15[2] - v38;
        m_pExplosive = this->m_pExplosive;
        v40 = fDeltaTime * m_pExplosive[v6].vecSpeed.y;
        v41 = fDeltaTime * m_pExplosive[v6].vecSpeed.z;
        v35 = fDeltaTime * m_pExplosive[v6].vecSpeed.x + v8;
        v37 = v40 + v36;
        v39 = v41 + v38;
        v31 = fDeltaTime * m_pExplosive[v6].vecRot.z;
        v30 = fDeltaTime * m_pExplosive[v6].vecRot.y;
        v29 = fDeltaTime * m_pExplosive[v6].vecRot.x;
        ((gbQuaternion *)&v42)->SetYawPitchRoll(v29, v30, v31);
        ((gbQuaternion *)&v42)->GetMatrix(&v43);
        ((gbMatrix4 *)&v43)->RotateIn(this->m_pGeomQuad[v5].vec);
        ((gbMatrix4 *)&v43)->RotateIn(&this->m_pGeomQuad[v5].vec[1]);
        ((gbMatrix4 *)&v43)->RotateIn(&this->m_pGeomQuad[v5].vec[2]);
        ((gbMatrix4 *)&v43)->RotateIn(&this->m_pGeomQuad[v5].vec[3]);
        v17 = this->m_pGeomQuad;
        v18 = v35 + v17[v5].vec[0].x;
        v19 = (float *)&v17[v5];
        *v19 = v18;
        v19[1] = v37 + v19[1];
        v19[2] = v39 + v19[2];
        v20 = this->m_pGeomQuad;
        v21 = &v20[v5].vec[1].x;
        *v21 = v35 + *v21;
        v21[1] = v37 + v20[v5].vec[1].y;
        v21[2] = v39 + v20[v5].vec[1].z;
        v22 = this->m_pGeomQuad;
        v23 = &v22[v5].vec[2].x;
        *v23 = v35 + *v23;
        v23[1] = v37 + v22[v5].vec[2].y;
        v23[2] = v39 + v22[v5].vec[2].z;
        v24 = this->m_pGeomQuad;
        v25 = v35 + v24[v5].vec[3].x;
        v26 = &v24[v5].vec[3].x;
        *v26 = v25;
        ++v6;
        ++v5;
        v26[1] = v37 + v26[1];
        v26[2] = v39 + v26[2];
        v27 = v32 + 1;
        v28 = ++v33 < this->m_nZDivision;
        ++v32;
      }
      while ( v28 );
      v4 = v27;
    }
  }
}
