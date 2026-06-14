#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffMeteor.h"

// Forward declarations for unnamed functions
int sub_4CB3A0(...);
int sub_4CCA90(...);
int sub_4CCC60(...);
int sub_4CCD10(...);
void sub_4CD0D0(int pEM, int nMaxTrail, int bNoHead, int pTextureArray); // from annotations
int sub_4CD3D0(...);
int sub_4CD500(...);
void __cdecl todo_401800(void);
int todo_408BD0(...);

// Unnamed globals (extern)
extern char byte_FFFFFF;
extern int dword_5D4DAC;
extern int dword_5D4DB8;
extern int dword_5D4DC4;
extern int dword_5D4DCC;
extern int dword_5D4DD4;
extern int dword_5D4E00;
extern int dword_5D4E0C;
extern int dword_5D4E14;
extern int dword_5D4E1C;
extern int dword_5D4E24;
extern int dword_5D4E30;
extern int dword_5D4E38;
extern int dword_5D4E40;
extern int dword_5D4FFC;
extern int dword_5D5008;
extern int dword_5D5014;
extern int dword_5D5038;
extern int dword_5D5040;
extern int dword_5D5048;
extern int dword_5D5050;
extern int dword_5D51B0;
extern int dword_5D5318;
extern int dword_5D5324;
extern int dword_5D5330;
extern int dword_5D533C;
extern int dword_5D5348;
extern int dword_5D5354;
extern int dword_5D5360;
extern int dword_5D536C;
extern int dword_5D5378;
extern int dword_5D5384;
void __cdecl nullsub_17(void);
void __cdecl nullsub_18(void);
void __cdecl nullsub_19(void);

// 0x004CB480
CEffMeteor::CEffMeteor()
{
  void *v1; // eax

  v1 = operator new(0x10D0u);
  if ( v1 )
    sub_4CB3A0(v1);
}

// 0x004CB4C0
void CEffMeteor::_CEffMeteor()
{
  CEffObj *v2; // edi
  gbGeomQuad *m_pGeomQuad; // eax
  int v4; // ebp
  CMeteorChain *m_pChain; // eax
  gbRefObject *m_pTexture; // ecx
  CEffObj *v7; // esi
  CEffMgr *m_pEM; // eax
  bool v9; // cc
  int v10; // edi

  v2 = this + 1;
  m_pGeomQuad = this->m_pGeomQuad;
  v4 = 0;
  if ( m_pGeomQuad )
    operator delete(m_pGeomQuad);
  if ( this->m_pMeteor )
    operator delete(this->m_pMeteor);
  m_pChain = this->m_pChain;
  if ( m_pChain )
    operator delete(&m_pChain[-1].m_fWidthDecSpeed);
  m_pTexture = (gbRefObject *)this->m_pTexture;
  if ( m_pTexture )
    ((gbRefObject *)m_pTexture)->Release();
  if ( this->m_pTextureArray )
    operator delete(this->m_pTextureArray);
  v7 = this != 0 ? v2 : 0;
  m_pEM = v7[2].m_pEM;
  v9 = (int)m_pEM <= 0;
  if ( !m_pEM )
  {
    if ( !*(this != 0 ? (_DWORD *)&v2[2].m_bIdle : (_DWORD *)32) )
      return;
    v9 = 1;
  }
  if ( !v9 )
  {
    v10 = 0;
    do
    {
// [VFTABLE] operator delete(*(void **)((char *)v7[1].__vftable + v10));
      ++v4;
// [VFTABLE] *(_DWORD *)((char *)v7[1].__vftable + v10) = 0;
      v10 += 152;
    }
    while ( v4 < (int)v7[2].m_pEM );
  }
// [VFTABLE] operator delete(v7[1].__vftable);
// [VFTABLE] v7[1].__vftable = 0;
  v7[2].m_pEM = 0;
  *(_DWORD *)&v7[2].m_bIdle = 0;
}

// 0x004CB5E0
int CEffMeteor::Init(float *pType, float fx, float fy, float fz)
{
  void *v5; // edi
  int m_dwStartColor_low; // ecx
  int result; // eax
  int v9; // ecx

  this->m_bIdle = 0;
  this->m_bVisible = 0;
  this->m_vecPos.x = fx + pType[46];
  this->m_vecPos.y = fy + pType[47];
  this->m_vecPos.z = fz + pType[48];
  this->m_vecRot.x = pType[54];
  this->m_vecRot.y = pType[49];
  this->m_vecRot.z = pType[55];
  this->m_vecTarget.x = fx + pType[63];
  this->m_vecTarget.y = fy + pType[64];
  this->m_vecTarget.z = fz + pType[65];
  this->m_vecOffsetPos.z = 0.0;
  this->m_vecOffsetPos.y = 0.0;
  this->m_vecOffsetPos.x = 0.0;
  this->m_dwStartColor = (unsigned int)pType[51];
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_fAlpha = (float)HIBYTE(this->m_dwStartColor);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_fRed = (float)(unsigned __int8)BYTE2(this->m_dwStartColor);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_fGreen = (float)(unsigned __int8)BYTE1(this->m_dwStartColor);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_fCurFrame = 0.0;
  m_dwStartColor_low = LOBYTE(this->m_dwStartColor);
  this->m_nLoops = 0;
  this->m_fBlue = (float)m_dwStartColor_low;
  this->m_fXSize = pType[50];
  this->m_fZSize = pType[50];
  todo_408BD0(v5);
  result = this->m_nMaxChain;
  v9 = 0;
  if ( result > 0 )
  {
    result = 0;
    do
    {
      ++v9;
      *(unsigned int *)((char *)&this->m_pChain->m_dwColor + result) = this->m_dwStartColor;
      *(float *)((char *)&this->m_pChain->m_fMaxWidth + result) = this->m_fMeteorWidth;
      *(float *)((char *)&this->m_pChain->m_fLumDecSpeed + result) = this->m_fLumDecSpeed;
      *(float *)((char *)&this->m_pChain->m_fWidthDecSpeed + result) = this->m_fWidthDecSpeed;
      *(float *)((char *)&this->m_pChain->m_fMaxLum + result) = this->m_fMaxLum;
      result += 56;
    }
    while ( v9 < this->m_nMaxChain );
  }
  return result;
}

// 0x004CB800
char CEffMeteor::Create(tagEffObjType *base)
{
  void *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v11; // edi
  int m_nMaxChain; // ebx
  gbGeomQuad *v13; // eax
  int v14; // ebx
  int v15; // ebx
  int v16; // ebx
  tagMeteor *v17; // eax
  int v18; // ebx
  _DWORD *p_z; // ecx
  int v20; // ebx
  int v21; // ebx
  int *v22; // eax
  CMeteorChain *v23; // eax
  gbGeomQuad *m_pGeomQuad; // ecx
  int v25; // ecx
  int v26; // edi
  int v27; // ebx
  char ArgList; // [esp+0xC] [ebp-0x810] BYREF
  _BYTE pExceptionObject[1024]; // [esp+0x40C] [ebp-0x410] BYREF
  void *Block; // [esp+0x80C] [ebp-0x10]
  int v32; // [esp+0x818] [ebp-0x4]
  tagEffObjType *basea; // [esp+0x824] [ebp+0x8]

  v3 = operator new(0x4C0u);
  *((_DWORD *)this + 6) = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v5 + *((_DWORD *)this + 6)) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v5 + *((_DWORD *)this + 6)) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *((_DWORD *)this + 10) = 8;
        *((_DWORD *)this + 11) = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(v7 + *((_DWORD *)this + 6) + 148) = 0;
          v8 = 0;
          if ( *((int *)this + 11) > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(*(_DWORD *)(v7 + *((_DWORD *)this + 6)) + v9 - 8) = 0;
            }
            while ( v8 < *((_DWORD *)this + 11) );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *((_DWORD *)this + 10) );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v11 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v11 + *((_DWORD *)this + 6)));
        v11 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*((void **)this + 6));
  }
LABEL_10:
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_nMaxChain = abs32((int)base->fSacleX);
  this->m_fMeteorWidth = base->fSacleY;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_nMaxTrail = (int)base->fSacleZ;
  this->m_fLumDecSpeed = base->fTopRadius;
  this->m_fWidthDecSpeed = base->fBottomRadius;
  this->m_fMaxLum = base->fTextureRepeat;
  this->m_bHaveHead = base->fSacleX > 0.0;
  this->m_fFramePerSec = base->fFramePerSec;
  this->m_vecPos.x = base->fX;
  this->m_vecPos.y = base->fY;
  this->m_vecPos.z = base->fZ;
  this->m_vecRot.x = base->fStartXRot;
  this->m_vecRot.y = base->fStartYRot;
  this->m_vecRot.z = base->fStartZRot;
  this->m_vecTarget.x = base->fTopRadiusIncSpeed;
  this->m_vecTarget.y = base->fBottomRadiusIncSpeed;
  this->m_vecTarget.z = base->fTopRiseSpeed;
  this->m_vecStartSpeed.x = base->fBottomRiseSpeed;
  this->m_vecStartSpeed.y = base->fTopShrink;
  this->m_vecStartSpeed.z = base->fBottomShrink;
  this->m_bAdditiveBlend = base->bAdditiveBlend;
  this->m_bNoZTest = base->bNoZTest;
  this->m_byMaxFrame = base->nFrame;
  this->m_nRequireLoops = (int)&byte_FFFFFF;
  this->m_dwStartColor = base->dwColor;
  sub_4CCC60(base->nFramePerRow, base->nFramePerCol);
  m_nMaxChain = this->m_nMaxChain;
  v13 = (gbGeomQuad *)operator new(68 * m_nMaxChain);
  Block = v13;
  v32 = 0;
  if ( v13 )
  {
    v14 = m_nMaxChain - 1;
    basea = (tagEffObjType *)v13;
    if ( v14 >= 0 )
    {
      v15 = v14 + 1;
      do
      {
        --v15;
        basea = (tagEffObjType *)((char *)basea + 68);
      }
      while ( v15 );
      v13 = (gbGeomQuad *)Block;
    }
  }
  else
  {
    v13 = 0;
  }
  v16 = this->m_nMaxChain;
  this->m_pGeomQuad = v13;
  v32 = -1;
  v17 = (tagMeteor *)operator new(48 * v16);
  if ( v17 )
  {
    v18 = v16 - 1;
    if ( v18 >= 0 )
    {
      p_z = (_DWORD *)&v17->vecSpeed.z;
      v20 = v18 + 1;
      do
      {
        *(p_z - 5) = 0;
        *(p_z - 4) = 0;
        *(p_z - 3) = 0;
        *(p_z - 2) = 0;
        *(p_z - 1) = 0;
        *p_z = 0;
        p_z[1] = 0;
        p_z[2] = 0;
        p_z[3] = 0;
        p_z[4] = 0;
        p_z[5] = 0;
        p_z[6] = 0;
        p_z += 12;
        --v20;
      }
      while ( v20 );
    }
  }
  else
  {
    v17 = 0;
  }
  v21 = this->m_nMaxChain;
  this->m_pMeteor = v17;
  v22 = (int *)operator new(56 * v21 + 4);
  Block = v22;
  v32 = 1;
  if ( v22 )
  {
    *v22 = v21;
    v23 = (CMeteorChain *)(v22 + 1);
  }
  else
  {
    v23 = 0;
  }
  m_pGeomQuad = this->m_pGeomQuad;
  v32 = -1;
  this->m_pChain = v23;
  if ( !m_pGeomQuad || !v23 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("new fail in CEffMeteor::Create", "D:\\Project\\PAL3\\combat\\EffMeteor.cpp", 144),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  sub_4CCD10(base->szTexture);
  v26 = 0;
  if ( this->m_nMaxChain > 0 )
  {
    v27 = 0;
    do
    {
      LOBYTE(v25) = this->m_bHaveHead == 0;
      sub_4CD0D0((int)this->m_pEM, this->m_nMaxTrail, v25, (int)this->m_pTextureArray);
      ++v26;
      v27 += 56;
    }
    while ( v26 < this->m_nMaxChain );
  }
  return 1;
}

// 0x004CBC50
int CEffMeteor::slot_6()
{
  int result; // eax
  int v1; // ecx
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  char v5; // al
  bool v6; // zf
  _DWORD *v7; // eax
  gbRenderEffect *v8; // ecx
  int v9; // ebx
  int v10; // edi
  int v11; // ebp
  gbMatrix4 *Top; // eax
  double v13; // st7
  long double v14; // st6
  double v15; // st5
  double v16; // st6
  double v17; // st6
  double v18; // st7
  double v19; // st6
  gbVec3D *v20; // [esp+0x0] [ebp-0x48]
  gbVec3D *v21; // [esp+0x4] [ebp-0x44]
  int v22; // [esp+0x8] [ebp-0x40]
  float v23; // [esp+0x10] [ebp-0x38]
  float v24; // [esp+0x14] [ebp-0x34]
  gbRenderEffect *v25; // [esp+0x18] [ebp-0x30]
  float v26; // [esp+0x1C] [ebp-0x2C]
  gbMatrixStack *v27; // [esp+0x20] [ebp-0x28]
  float v28; // [esp+0x24] [ebp-0x24]
  float v29; // [esp+0x24] [ebp-0x24]
  float v30; // [esp+0x28] [ebp-0x20]
  float v31; // [esp+0x28] [ebp-0x20]
  float v32; // [esp+0x2C] [ebp-0x1C]
  float v33; // [esp+0x2C] [ebp-0x1C]
  float v34; // [esp+0x30] [ebp-0x18]
  float v35; // [esp+0x34] [ebp-0x14]

  v2 = v1;
  if ( (*(_BYTE *)(&g_PAL3.m_nCEffCylinderCount + 27) & 1) == 0 )
  {
    *(&g_PAL3.m_nCEffCylinderCount + 24) = 1065353216;
    *((_BYTE *)&g_PAL3.m_nCEffCylinderCount + 108) |= 1u;
    *(&g_PAL3.m_nCEffCylinderCount + 25) = 0;
    *(&g_PAL3.m_nCEffCylinderCount + 26) = 0;
    result = atexit(nullsub_19);
  }
  if ( (*(_BYTE *)(&g_PAL3.m_nCEffCylinderCount + 27) & 2) == 0 )
  {
    *(&g_PAL3.m_nCEffCylinderCount + 20) = 0;
    *((_BYTE *)&g_PAL3.m_nCEffCylinderCount + 108) |= 2u;
    *(&g_PAL3.m_nCEffCylinderCount + 21) = 1065353216;
    *(&g_PAL3.m_nCEffCylinderCount + 22) = 0;
    result = atexit(nullsub_18);
  }
  if ( (*(_BYTE *)(&g_PAL3.m_nCEffCylinderCount + 27) & 4) == 0 )
  {
    *(&g_PAL3.m_nCEffCylinderCount + 16) = 0;
    *((_BYTE *)&g_PAL3.m_nCEffCylinderCount + 108) |= 4u;
    *(&g_PAL3.m_nCEffCylinderCount + 17) = 0;
    *(&g_PAL3.m_nCEffCylinderCount + 18) = 1065353216;
    result = atexit(nullsub_17);
  }
  LOBYTE(result) = *(_BYTE *)(v2 + 8);
  if ( !(_BYTE)result )
  {
    LOBYTE(result) = *(_BYTE *)(v2 + 68);
    if ( (_BYTE)result )
    {
      result = *(_DWORD *)(v2 + 116);
      v3 = 0;
      if ( result > 0 )
      {
        v4 = 0;
        do
        {
          sub_4CD500(*(_DWORD *)(v2 + 52) + v4);
          result = *(_DWORD *)(v2 + 116);
          ++v3;
          v4 += 56;
        }
        while ( v3 < result );
      }
      LOBYTE(result) = *(_BYTE *)(v2 + 71);
      if ( (_BYTE)result )
      {
        ((gbVertPoolMgr *)*(gbVertPoolMgr **)(**(_DWORD **)(v2 + 4) + 196))->GetDynVertBuf(0x15u);
        v5 = *(_BYTE *)(v2 + 69);
        if ( *(_BYTE *)(v2 + 70) )
        {
          v6 = v5 == 0;
          v7 = *(_DWORD **)(v2 + 4);
          if ( !v6 )
          {
            v25 = (gbRenderEffect *)v7[2];
LABEL_21:
            v9 = 0;
            v27 = *(gbMatrixStack **)(*v7 + 216);
            if ( *(int *)(v2 + 116) > 0 )
            {
              v10 = 0;
              v11 = 0;
              do
              {
                Top = ((gbMatrixStack *)v27)->GetTop();
                ((gbMatrix4 *)Top)->Transform(v20, v21, v22);
                v13 = *(float *)(v2 + 108);
                v14 = *(float *)(v2 + 156) * 0.017453292;
                v26 = *(float *)(v2 + 112);
                v24 = cos(v14);
                v23 = sin(v14);
                v34 = -v13 * v24;
                v15 = -v26;
                v28 = v15;
                v30 = v15 * v23;
                *(float *)(*(_DWORD *)(v2 + 48) + v10) = v34 - v30 + 0.0;
                v35 = -v13 * v23;
                v16 = v28 * v24;
                v29 = v16;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 + 4) = v16 + v35 + 0.0;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 + 8) = 0;
                v17 = v24 * v13;
                v32 = v17;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 + 12) = v17 - v30 + 0.0;
                v18 = v13 * v23;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 + 16) = v18 + v29 + 0.0;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 + 20) = 0;
                v31 = v23 * v26;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 + 24) = v32 - v31 + 0.0;
                v19 = v24 * v26;
                v33 = v19;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 + 28) = v19 + v18 + 0.0;
                ++v9;
                v11 += 48;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 + 32) = 0;
                v10 += 68;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 - 32) = v34 - v31 + 0.0;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 - 28) = v33 + v35 + 0.0;
                *(float *)(*(_DWORD *)(v2 + 48) + v10 - 24) = 0;
              }
              while ( v9 < *(_DWORD *)(v2 + 116) );
            }
            ((gbMatrixStack *)v27)->Push();
            ((gbMatrixStack *)v27)->LoadIdentity();
            ((gbDynVertBuf *)*(gbGeomQuad **)(v2 + 48))->RenderGeomQuad(*(_DWORD *)(v2 + 116), v25, *(gbTextureArray **)(v2 + 64));
            ((gbMatrixStack *)v27)->Pop();
            return result;
          }
          v8 = (gbRenderEffect *)v7[3];
        }
        else
        {
          v6 = v5 == 0;
          v7 = *(_DWORD **)(v2 + 4);
          if ( !v6 )
          {
            v25 = (gbRenderEffect *)v7[4];
            goto LABEL_21;
          }
          v8 = (gbRenderEffect *)v7[5];
        }
        v25 = v8;
        goto LABEL_21;
      }
    }
  }
  return result;
}

// 0x004CBFC0
void CEffMeteor::CreateTask(int arg0)
{
  CEffMeteor *v2; // edi
  double v3; // st7
  CEffObj *v4; // esi
  char *v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // ebx
  int v13; // esi
  int v14; // esi
  int v15; // edx
  int v16; // eax
  void **v17; // ecx
  int v19; // [esp+0x4] [ebp-0xC]
  int v20; // [esp+0x8] [ebp-0x8]
  int nVal; // [esp+0xC] [ebp-0x4]
v3 = *(float *)&arg0 - *((float *)this + 4);
  v4 = this + 1;
  *((float *)this + 4) = *(float *)&arg0;
  *((float *)this + 5) = v3;
  if ( *((float *)this + 5) > 0.0 )
  {
    nVal = 0;
    if ( *((int *)this + 10) > 0 )
    {
      v20 = 0;
      while ( 1 )
      {
// [VFTABLE] v5 = (char *)v4[1].__vftable + v20;
        if ( v5[148] )
        {
          if ( *((_DWORD *)v5 + 3) == 3 )
          {
            v6 = 0;
            v19 = 0;
            if ( *(int *)&v4[2].m_bIdle > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++nVal < (int)v4[2].m_pEM;
        v20 += 152;
        if ( !v11 )
          goto LABEL_30;
      }
      v7 = 0;
      while ( 1 )
      {
        v8 = v7 + *(_DWORD *)v5;
        if ( !*(_BYTE *)(v8 + 64) || v7 > 0 && *(_DWORD *)(v8 - 64) == 2 )
        {
LABEL_28:
goto LABEL_29;
        }
        switch ( *(_DWORD *)(v8 + 8) )
        {
          case 2:
            if ( v7 > 0 )
            {
              if ( *(float *)(v8 + 20) >= 0.0 )
              {
                if ( *(float *)&v4->m_pEM - *(float *)(v8 - 56) > *(float *)(v8 + 20) )
                {
                  ((CCBStage *)v4)->GetTaskParam(nVal, v6);
                  v4[1].m_pEM = (CEffMgr *)nVal;
                  *(_DWORD *)&v4[1].m_bIdle = v19;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v4[1].__vftable + v20) + v7 + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v4[1].__vftable + v20) + v7 + 16) = v4->m_pEM;
LABEL_21:
                *(_DWORD *)&v4[1].m_bIdle = v6;
                v4[1].m_pEM = (CEffMgr *)nVal;
LABEL_24:
// [VFTABLE] (*((void ( **)(CEffObj *, _DWORD, _DWORD, _DWORD))v4->__vftable + 1))(
// [VFTABLE]   v4,
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v5 + v7),
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v5 + v7 + 4),
// [VFTABLE]   0);
              }
            }
            break;
          case 3:
            goto LABEL_21;
          case 4:
            if ( ((CCBStage *)v4)->SetTaskState(nVal) )
            {
              v9 = *((_DWORD *)v5 + 1);
              *((_DWORD *)v5 + 3) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = v5[149];
              *((_DWORD *)v5 + 5) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                ((CEffgbParticle *)v4)->Init(nVal);
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = v19 + 1;
        v7 += 72;
        if ( ++v19 >= *(_DWORD *)&v4[2].m_bIdle )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *((int *)v2 + 9) <= 0 )
      this->m_bIdle = 1;
    if ( !this->m_bIdle )
    {
      v12 = 0;
      if ( this->m_nMaxChain > 0 )
      {
        v13 = 0;
        do
        {
          this->m_pChain[v13].m_dwColor = this->m_dwStartColor;
          this->m_pChain[v13].m_fMaxLum = this->m_fMaxLum;
          sub_4CD3D0(arg0);
          ++v12;
          ++v13;
        }
        while ( v12 < this->m_nMaxChain );
      }
      if ( this->m_bHaveHead )
      {
        this->m_fCurFrame = this->m_fFramePerSec * *((float *)v2 + 5) + this->m_fCurFrame;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        v14 = 0;
        v15 = (int)abs32((int)this->m_fCurFrame) % (unsigned __int8)this->m_byMaxFrame;
        if ( this->m_nMaxChain > 0 )
        {
          v16 = 0;
// [VFTABLE] v17 = &this->__vftable + 4 * v15;
          do
          {
            ++v14;
            this->m_pGeomQuad[v16++].su = this->m_DefaultUVSet[v15].su;
            LODWORD(this->m_pGeomQuad[v16 - 1].eu) = v17[54];
            LODWORD(this->m_pGeomQuad[v16 - 1].sv) = v17[53];
            LODWORD(this->m_pGeomQuad[v16 - 1].ev) = v17[55];
            this->m_pGeomQuad[v16 - 1].color = this->m_dwStartColor;
          }
          while ( v14 < this->m_nMaxChain );
        }
      }
    }
  }
}

// 0x004CC290
void CEffMeteor::CreateTarget(int *pnVal)
{
  CEffObj *v2; // ebx
  int v3; // ecx
  int v4; // edx
  char *vftable; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v2 = this + 1;
  v3 = *((_DWORD *)this + 10);
  v4 = 0;
  if ( v3 > 0 )
  {
// [VFTABLE] vftable = (char *)v2[1].__vftable;
    for ( i = vftable + 148; *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)&vftable[v7 + 12] = 2;
// [VFTABLE] *((_BYTE *)v2[1].__vftable + v7 + 148) = 1;
// [VFTABLE] *((_BYTE *)v2[1].__vftable + v7 + 149) = 1;
    v8 = ++g_PAL3.m_nMeteorChainCount;
    if ( !g_PAL3.m_nMeteorChainCount || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_PAL3.m_nMeteorChainCount = 1;
    }
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 16) = v8;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 4) = 0;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 8) = 0;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 20) = 0;
    if ( pnVal )
// [VFTABLE] qmemcpy((char *)v2[1].__vftable + v7 + 24, pnVal, 0x7Cu);
    else
// [VFTABLE] memset((char *)v2[1].__vftable + v7 + 24, 0, 0x7Cu);
// [VFTABLE] ++v2[2].__vftable;
    if ( v4 != -1 )
    {
      v9 = *(_DWORD *)&v2[2].m_bIdle;
      v10 = 0;
      if ( v9 > 0 )
      {
// [VFTABLE] v11 = *((_DWORD *)v2[1].__vftable + 38 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_PAL3.m_nMeteorChainCount;
        if ( !g_PAL3.m_nMeteorChainCount || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_PAL3.m_nMeteorChainCount = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v2[1].__vftable + v7 + 4);
      }
LABEL_22:
      v15 = *(_DWORD *)&v2[2].m_bIdle;
      v16 = 0;
      if ( v15 > 0 )
      {
// [VFTABLE] v17 = *((_DWORD *)v2[1].__vftable + 38 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_PAL3.m_nMeteorChainCount;
        if ( !g_PAL3.m_nMeteorChainCount || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_PAL3.m_nMeteorChainCount = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v2[1].__vftable + v7 + 4);
      }
LABEL_31:
      ((CMeteorChain *)v2)->Update(v4, 0 /* TODO: (int)CEffCylinder::Update */, 0, 0, pnVal[18], pnVal[19]);
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 12) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v2[1].__vftable + v7) + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v2[1].__vftable + v7) + 16) = v2->m_pEM;
    }
  }
}

// 0x004CCA90
int CEffMeteor::sub_4CCA90(int a2)
{
  int result; // eax

  switch ( a2 )
  {
    case 0:
      result = (int)dword_5D5050;
      break;
    case 1:
      result = (int)dword_5D4E40;
      break;
    case 2:
      result = (int)dword_5D4E38;
      break;
    case 3:
      result = (int)dword_5D4E30;
      break;
    case 4:
      result = (int)dword_5D4E24;
      break;
    case 5:
      result = (int)dword_5D5048;
      break;
    case 6:
      result = (int)dword_5D5040;
      break;
    case 7:
      result = (int)dword_5D5038;
      break;
    case 8:
      result = (int)dword_5D4E00;
      break;
    case 9:
      result = (int)&g_EffEditorState;
      break;
    case 10:
      result = (int)dword_5D51B0;
      break;
    case 12:
      result = (int)dword_5D4DD4;
      break;
    case 13:
      result = (int)dword_5D4DCC;
      break;
    case 14:
      result = (int)dword_5D4DC4;
      break;
    case 15:
      result = (int)dword_5D4DB8;
      break;
    case 16:
      result = (int)dword_5D4DAC;
      break;
    case 17:
      result = (int)dword_5D5014;
      break;
    case 18:
      result = (int)dword_5D5008;
      break;
    case 19:
      result = (int)dword_5D4FFC;
      break;
    case 20:
      result = (int)&g_pszEditorDesc;
      break;
    default:
      result = (int)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004CCBA0
int CEffMeteor::DispatchByType(int a2)
{
  int result; // eax

  switch ( a2 )
  {
    case 0:
      result = (int)dword_5D5384;
      break;
    case 1:
      result = (int)dword_5D5378;
      break;
    case 2:
      result = (int)dword_5D536C;
      break;
    case 3:
      result = (int)dword_5D5360;
      break;
    case 4:
      result = (int)dword_5D5354;
      break;
    case 5:
      result = (int)dword_5D5348;
      break;
    case 6:
      result = (int)dword_5D533C;
      break;
    case 7:
      result = (int)dword_5D4E1C;
      break;
    case 8:
      result = (int)dword_5D4E14;
      break;
    case 9:
      result = (int)dword_5D4E0C;
      break;
    case 10:
      result = (int)dword_5D5330;
      break;
    case 11:
      result = (int)dword_5D5324;
      break;
    case 12:
      result = (int)dword_5D5318;
      break;
    default:
      result = (int)&g_EffCylinderEditorData;
      break;
  }
  return result;
}
