#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffQuad.h"

// 0x004D1BE0
void CEffQuad::DestroyOneQuad(const void *n)
{
  int m_nMaxQuad; // ecx
  int v4; // ebp
  tagQuad *m_pQuad; // esi
  _BYTE *i; // eax
  int v7; // eax
  int m_nQuadNum; // ecx

  m_nMaxQuad = this->m_nMaxQuad;
  if ( this->m_nGeomQuadNum <= m_nMaxQuad )
  {
    v4 = 0;
    if ( m_nMaxQuad > 0 )
    {
      m_pQuad = this->m_pQuad;
      for ( i = &m_pQuad->bValid; *i; i += 80 )
      {
        if ( ++v4 >= m_nMaxQuad )
          return;
      }
      v7 = v4;
      qmemcpy(&m_pQuad[v4], n, sizeof(tagQuad));
      this->m_pQuad[v7].bValid = 1;
      this->m_pQuad[v7].fCurFrame = 0.0;
      this->m_pQuad[v7].byFrame = 0;
      this->m_pQuad[v7].byLoops = 0;
      m_nQuadNum = this->m_nQuadNum;
      if ( v4 > m_nQuadNum - 1 )
        this->m_nQuadNum = m_nQuadNum + 1;
      this->m_pQuad[v7].nGeomQuad = this->m_nGeomQuadNum;
      this->m_pnG2Q[this->m_nGeomQuadNum++] = v4;
      this->SetQuad(v4);
      this->m_nLastCreatedQuad = v4;
    }
  }
}

// 0x004D1CA0
bool CEffQuad::SetQuad(int n)
{
  tagQuad *v2; // edx
  int nGeomQuad; // eax
  double v4; // st7

  v2 = &this->m_pQuad[n];
  nGeomQuad = v2->nGeomQuad;
  this->m_pGeomQuad[nGeomQuad].color = v2->dwColor;
  if ( this->m_bBillBoard )
  {
    this->m_pGeomQuad[nGeomQuad].vec[0].x = v2->fX - v2->fXSize;
    this->m_pGeomQuad[nGeomQuad].vec[1].x = v2->fXSize + v2->fX;
    this->m_pGeomQuad[nGeomQuad].vec[2].x = v2->fXSize + v2->fX;
    this->m_pGeomQuad[nGeomQuad].vec[3].x = v2->fX - v2->fXSize;
    this->m_pGeomQuad[nGeomQuad].vec[0].y = v2->fY;
    this->m_pGeomQuad[nGeomQuad].vec[1].y = v2->fY;
    this->m_pGeomQuad[nGeomQuad].vec[2].y = v2->fY;
    this->m_pGeomQuad[nGeomQuad].vec[3].y = v2->fY;
    this->m_pGeomQuad[nGeomQuad].vec[0].z = v2->fYSize + v2->fZ;
    this->m_pGeomQuad[nGeomQuad].vec[1].z = v2->fYSize + v2->fZ;
    this->m_pGeomQuad[nGeomQuad].vec[2].z = v2->fZ - v2->fYSize;
    v4 = v2->fZ - v2->fYSize;
  }
  else
  {
    this->m_pGeomQuad[nGeomQuad].vec[0].x = -v2->fXSize;
    this->m_pGeomQuad[nGeomQuad].vec[1].x = v2->fXSize;
    this->m_pGeomQuad[nGeomQuad].vec[2].x = v2->fXSize;
    this->m_pGeomQuad[nGeomQuad].vec[3].x = -v2->fXSize;
    this->m_pGeomQuad[nGeomQuad].vec[0].y = 0.0;
    this->m_pGeomQuad[nGeomQuad].vec[1].y = 0.0;
    this->m_pGeomQuad[nGeomQuad].vec[2].y = 0.0;
    this->m_pGeomQuad[nGeomQuad].vec[3].y = 0.0;
    this->m_pGeomQuad[nGeomQuad].vec[0].z = v2->fYSize;
    this->m_pGeomQuad[nGeomQuad].vec[1].z = v2->fYSize;
    this->m_pGeomQuad[nGeomQuad].vec[2].z = -v2->fYSize;
    v4 = -v2->fYSize;
  }
  this->m_pGeomQuad[nGeomQuad].vec[3].z = v4;
  this->m_pGeomQuad[nGeomQuad].su = 0.0;
  this->m_pGeomQuad[nGeomQuad].eu = 0.0;
  this->m_pGeomQuad[nGeomQuad].sv = 0.0;
  this->m_pGeomQuad[nGeomQuad].ev = 0.0;
  return nGeomQuad * 68;
}

// 0x004D1E50
int * CEffQuad::DestroyAllQuad(int nVal)
{
  int *result; // eax
  tagQuad *v3; // ecx
  int v4; // edx
  int nGeomQuad; // ebx
  int v6; // ecx

  result = (int *)this;
  v3 = &this->m_pQuad[nVal];
  v4 = result[16] - 1;
  nGeomQuad = v3->nGeomQuad;
  v3->bValid = 0;
  if ( v4 != nGeomQuad )
  {
    qmemcpy((void *)(result[40] + 68 * nGeomQuad), (const void *)(result[40] + 68 * v4), 0x44u);
    *(_DWORD *)(80 * *(_DWORD *)(result[41] + 4 * v4) + result[39]) = nGeomQuad;
    *(_DWORD *)(result[41] + 4 * nGeomQuad) = *(_DWORD *)(result[41] + 4 * v4);
  }
  v6 = result[15] - 1;
  --result[16];
  if ( nVal == v6 )
    result[15] = v6;
  if ( nVal == result[18] )
    result[18] = -1;
  return result;
}

// 0x004D1F30
int * CEffQuad::ToNextFrame(int nQuad)
{
  gbTexture *v3; // eax
  int *result; // eax
  gbTexture *m_pTexture; // ecx
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x800] BYREF
  char ArgList; // [esp+0x408] [ebp-0x400] BYREF

  v3 = (gbTexture *)(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)this->m_pEM->m_pDisplay + 8))(
                      this->m_pEM->m_pDisplay,
                      nQuad);
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
      ((Logger *)&ArgList)->FormatException("C++ new failed!", (char *)&pTarget._todo_184 + 8, 540),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004D2E10
int CEffQuad::ProcessDestroyPass(int nVal)
{
  int v3; // ebp
  int v4; // edi
  int m_nLastCreatedQuad; // eax
  int v6; // edx
  int v7; // eax

  v3 = *((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7);
  v4 = *(_DWORD *)v3 + 72 * *((_DWORD *)this + 8);
  if ( !*(_BYTE *)(v4 + 65) )
  {
    m_nLastCreatedQuad = this->m_nLastCreatedQuad;
    if ( m_nLastCreatedQuad == -1 )
      this->DestroyOneQuad(&this->m_StartQuad);
    else
      this->DestroyOneQuad(&this->m_pQuad[m_nLastCreatedQuad]);
    v6 = *((_DWORD *)this + 4);
    *(_BYTE *)(v4 + 65) = 1;
    *(_DWORD *)(v4 + 44) = v6;
  }
  if ( !*(_BYTE *)(v3 + 113) )
    goto LABEL_14;
  if ( *((float *)this + 4) - *(float *)(v4 + 44) >= *(float *)(v3 + 108) )
  {
    v7 = this->m_nLastCreatedQuad;
    if ( v7 == -1 )
      this->DestroyOneQuad(&this->m_StartQuad);
    else
      this->DestroyOneQuad(&this->m_pQuad[v7]);
    *(_DWORD *)(v4 + 44) = *((_DWORD *)this + 4);
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || *((float *)this + 4) - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
LABEL_14:
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}
