#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffCylinder.h"

// Forward declarations for unnamed functions
int sub_4C4B00(int _this, int a2); // from annotations
int sub_4C55F0(...);
int sub_4CAD10(...);
int sub_4CB000(...);
int sub_4CB0C0(...);
int sub_4CCDA0(...);
int sub_4CD3A0(...);
void __cdecl todo_401800(void);

// Unnamed globals (extern)
extern char byte_FFFFFF;
extern int dword_5D4DAC;
extern int dword_5D4DB8;
extern int dword_5D4DC4;
extern int dword_5D4DCC;
extern int dword_5D4DD4;
extern int dword_5D4E00;
extern int dword_5D4E24;
extern int dword_5D4E30;
extern int dword_5D4E38;
extern int dword_5D4E40;
extern int dword_5D4FD0;
extern int dword_5D4FE0;
extern int dword_5D4FF0;
extern int dword_5D4FFC;
extern int dword_5D5008;
extern int dword_5D5014;
extern int dword_5D5020;
extern int dword_5D502C;
extern int dword_5D5038;
extern int dword_5D5040;
extern int dword_5D5048;
extern int dword_5D5050;
extern int dword_5D505C;
extern int dword_5D5068;
extern int dword_5D5074;
extern int dword_5D5080;
extern int dword_5D508C;
extern int dword_5D5098;
extern int dword_5D50A4;
extern int dword_5D50B0;
extern int dword_5D50B8;
extern int dword_5D50C0;
extern int dword_5D50CC;
extern int dword_5D50D8;
extern int dword_5D50E4;
void __cdecl nullsub_76(void);
void __cdecl nullsub_77(void);
void __cdecl nullsub_78(void);

// 0x004C3C90
CEffCylinder ** CEffCylinder::Init()
{
  this->m_pEM = 0;
  this->m_bIdle = 0;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) = 0;
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 7) = -1;
  *((_DWORD *)this + 8) = -1;
  *((_DWORD *)this + 9) = 0;
  *((_DWORD *)this + 10) = 0;
  *((_DWORD *)this + 11) = 0;
  this->m_vecRot.x = 0.0;
  this->m_vecRot.y = 0.0;
  this->m_vecRot.z = 0.0;
  this->m_vecPos.x = 0.0;
  this->m_vecPos.y = 0.0;
  this->m_vecPos.z = 0.0;
  this->m_vecOffsetPos.x = 0.0;
  this->m_vecOffsetPos.y = 0.0;
  this->m_vecOffsetPos.z = 0.0;
  this->m_fRotAngle = 360.0;
  this->m_fWide = 10.0;
  this->m_nDivision = 10;
  this->m_fTopShrink = 0.0;
  this->m_fBottomShrink = 0.0;
  this->m_fTopRadius = 50.0;
  this->m_fBottomRadius = 50.0;
  this->m_fTopRadiusIncSpeed = 0.0;
  this->m_fBottomRadiusIncSpeed = 0.0;
  this->m_fTopRiseSpeed = 0.0;
  this->m_fBottomRiseSpeed = 0.0;
  this->m_vecPos.z = 0.0;
  this->m_vecPos.y = 0.0;
  this->m_vecPos.x = 0.0;
  this->m_vecOffsetPos.z = 0.0;
  this->m_vecOffsetPos.y = 0.0;
  this->m_vecOffsetPos.x = 0.0;
  this->m_vecRot.z = 0.0;
  this->m_vecRot.y = 0.0;
  this->m_vecRot.x = 0.0;
  this->m_pGeomQuad = 0;
  this->m_bAdditiveBlend = 0;
  this->m_bNoZTest = 0;
  this->m_pTexture = 0;
  this->m_pTextureArray = 0;
  return (CEffCylinder **)this;
}

// 0x004C3D90
void CEffCylinder::AllocEffect()
{
  CEffCylinder *v1; // eax

  v1 = (CEffCylinder *)operator new(0x10C4u);
  if ( v1 )
    ((CEffCylinder *)v1)->Init();
}

// 0x004C3DD0
void CEffCylinder::CEffCylinder()
{
  CEffObj *v2; // edi
  gbGeomQuad *m_pGeomQuad; // eax
  int v4; // ebx
  gbRefObject *m_pTexture; // ecx
  CEffObj *v6; // esi
  CEffMgr *m_pEM; // eax
  bool v8; // cc
  int v9; // edi

  v2 = this + 1;
  m_pGeomQuad = this->m_pGeomQuad;
  v4 = 0;
  if ( m_pGeomQuad )
    operator delete(m_pGeomQuad);
  m_pTexture = (gbRefObject *)this->m_pTexture;
  if ( m_pTexture )
    ((gbRefObject *)m_pTexture)->Release();
  if ( this->m_pTextureArray )
    operator delete(this->m_pTextureArray);
  v6 = this != 0 ? v2 : 0;
  m_pEM = v6[2].m_pEM;
  v8 = (int)m_pEM <= 0;
  if ( !m_pEM )
  {
    if ( !*(this != 0 ? (_DWORD *)&v2[2].m_bIdle : (_DWORD *)32) )
      return;
    v8 = 1;
  }
  if ( !v8 )
  {
    v9 = 0;
    do
    {
// [VFTABLE] operator delete(*(void **)((char *)v6[1].__vftable + v9));
      ++v4;
// [VFTABLE] *(_DWORD *)((char *)v6[1].__vftable + v9) = 0;
      v9 += 152;
    }
    while ( v4 < (int)v6[2].m_pEM );
  }
// [VFTABLE] operator delete(v6[1].__vftable);
// [VFTABLE] v6[1].__vftable = 0;
  v6[2].m_pEM = 0;
  *(_DWORD *)&v6[2].m_bIdle = 0;
}

// 0x004C3EB0
void CEffCylinder::_CEffCylinder()
{
  ;
}

// 0x004C3EC0
int CEffCylinder::Init(float *pType, float fx, float fy, float fz)
{
  int result; // eax
  int m_dwStartColor_low; // ecx
  float v8; // edx

  this->m_bIdle = 0;
  this->m_bVisible = 0;
  this->m_vecPos.x = fx + pType[46];
  this->m_vecPos.y = fy + pType[47];
  this->m_vecPos.z = fz + pType[48];
  this->m_vecRot.x = pType[54];
  this->m_vecRot.y = pType[49];
  this->m_vecRot.z = pType[55];
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
  result = (unsigned __int8)BYTE1(this->m_dwStartColor);
  this->m_fGreen = (float)result;
  LOBYTE(result) = g_bEffSystemFlags;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    result = atexit(todo_401800);
  }
  this->m_fCurTextureV = 0.0;
  m_dwStartColor_low = LOBYTE(this->m_dwStartColor);
  this->m_fCurFrame = 0.0;
  this->m_nLoops = 0;
  this->m_fBlue = (float)m_dwStartColor_low;
  v8 = pType[50];
  this->m_fHeight = 1.0;
  this->m_fSize = v8;
  return result;
}

// 0x004C4060
char CEffCylinder::Create(tagEffObjType *pType)
{
  void *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  gbGeomQuad *v11; // eax
  int v12; // ebx
  int v13; // edi
  char ArgList; // [esp+0xC] [ebp-0x810] BYREF
  _BYTE pExceptionObject[1024]; // [esp+0x40C] [ebp-0x410] BYREF
  void *Block; // [esp+0x80C] [ebp-0x10]
  int v18; // [esp+0x818] [ebp-0x4]
  int pTypea; // [esp+0x824] [ebp+0x8]

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
      v13 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v13 + *((_DWORD *)this + 6)));
        v13 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*((void **)this + 6));
  }
LABEL_10:
  this->m_fRotAngle = pType->fSacleX;
  this->m_fWide = pType->fSacleY;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_nDivision = (int)pType->fSacleZ;
  this->m_fTopShrink = pType->fTopShrink;
  this->m_fBottomShrink = pType->fBottomShrink;
  this->m_fTopRadius = pType->fTopRadius;
  this->m_fBottomRadius = pType->fBottomRadius;
  this->m_fTopRadiusIncSpeed = pType->fTopRadiusIncSpeed;
  this->m_fBottomRadiusIncSpeed = pType->fBottomRadiusIncSpeed;
  this->m_fTopRiseSpeed = pType->fTopRiseSpeed;
  this->m_fBottomRiseSpeed = pType->fBottomRiseSpeed;
  this->m_fTextureRepeat = pType->fTextureRepeat;
  this->m_fFramePerSec = pType->fFramePerSec;
  this->m_vecPos.x = pType->fX;
  this->m_vecPos.y = pType->fY;
  this->m_vecPos.z = pType->fZ;
  this->m_vecRot.x = pType->fStartXRot;
  this->m_vecRot.y = pType->fStartYRot;
  this->m_vecRot.z = pType->fStartZRot;
  this->m_bAdditiveBlend = pType->bAdditiveBlend;
  this->m_bNoZTest = pType->bNoZTest;
  this->m_byMaxFrame = pType->nFrame;
  this->m_nRequireLoops = (int)&byte_FFFFFF;
  this->m_dwStartColor = pType->dwColor;
  this->InitDefaultUVSet(pType->nFramePerRow, pType->nFramePerCol);
  pTypea = this->m_nDivision;
  v11 = (gbGeomQuad *)operator new(68 * pTypea);
  Block = v11;
  v18 = 0;
  if ( v11 )
  {
    v12 = (int)v11;
    if ( pTypea - 1 >= 0 )
    {
      do
      {
        v12 += 68;
        --pTypea;
      }
      while ( pTypea );
      v11 = (gbGeomQuad *)Block;
    }
  }
  else
  {
    v11 = 0;
  }
  v18 = -1;
  this->m_pGeomQuad = v11;
  if ( !v11 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("new fail in CEffCylinder::Create", "D:\\Project\\PAL3\\combat\\EffCylinder.cpp", 127),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->LoadTexture(pType->szTexture);
  ((CEffMgr *)this)->UpdateParticlePositions();
  return 1;
}

// 0x004C4370
void CEffCylinder::Destroy()
{
  char m_bAdditiveBlend; // al
  bool v3; // zf
  CEffMgr *m_pEM; // eax
  gbRenderEffect *m_pAlphaBlendNoZ; // ebp
  gbMatrixStack *v6; // edi
  float v7; // [esp+0x3C] [ebp-0xC]
  float retaddr; // [esp+0x48] [ebp+0x0] BYREF

  if ( (g_PAL3.m_bCEffCylinderFlag_DE937C & 1) == 0 )
  {
    *(&g_PAL3.m_nCEffExplosiveCount + 10) = 1065353216;
    g_PAL3.m_bCEffCylinderFlag_DE937C |= 1u;
    *(&g_PAL3.m_nCEffExplosiveCount + 11) = 0;
    *(&g_PAL3.m_nCEffExplosiveCount + 12) = 0;
    atexit(nullsub_78);
  }
  if ( (g_PAL3.m_bCEffCylinderFlag_DE937C & 2) == 0 )
  {
    *(&g_PAL3.m_nCEffExplosiveCount + 6) = 0;
    g_PAL3.m_bCEffCylinderFlag_DE937C |= 2u;
    *(&g_PAL3.m_nCEffExplosiveCount + 7) = 1065353216;
    *(&g_PAL3.m_nCEffExplosiveCount + 8) = 0;
    atexit(nullsub_77);
  }
  if ( (g_PAL3.m_bCEffCylinderFlag_DE937C & 4) == 0 )
  {
    *(&g_PAL3.m_nCEffExplosiveCount + 2) = 0;
    g_PAL3.m_bCEffCylinderFlag_DE937C |= 4u;
    *(&g_PAL3.m_nCEffExplosiveCount + 3) = 0;
    *(&g_PAL3.m_nCEffExplosiveCount + 4) = 1065353216;
    atexit(nullsub_76);
  }
  if ( !this->m_bIdle && this->m_bVisible )
  {
    ((gbVertPoolMgr *)this->m_pEM->m_pDisplay->pVertPoolMgr)->GetDynVertBuf(0x15u);
    m_bAdditiveBlend = this->m_bAdditiveBlend;
    if ( this->m_bNoZTest )
    {
      v3 = m_bAdditiveBlend == 0;
      m_pEM = this->m_pEM;
      if ( v3 )
        m_pAlphaBlendNoZ = m_pEM->m_pAlphaBlendNoZ;
      else
        m_pAlphaBlendNoZ = m_pEM->m_pAdditiveBlendNoZ;
    }
    else
    {
      v3 = m_bAdditiveBlend == 0;
      m_pEM = this->m_pEM;
      if ( v3 )
        m_pAlphaBlendNoZ = m_pEM->m_pAlphaBlend;
      else
        m_pAlphaBlendNoZ = m_pEM->m_pAdditiveBlend;
    }
    v6 = m_pEM->m_pDisplay->pMatrixStack[1];
    ((gbMatrixStack *)v6)->Push();
    v7 = this->m_vecOffsetPos.x + this->m_vecPos.x;
    retaddr = v7;
    ((gbMatrixStack *)v6)->Translate((gbVec3D *)&retaddr);
    ((gbMatrixStack *)v6)->Rotate(this->m_vecRot.x, (gbVec3D *)(&g_PAL3.m_nCEffExplosiveCount + 10));
    ((gbMatrixStack *)v6)->Rotate(this->m_vecRot.y, (gbVec3D *)&g_PAL3.m_nCEffExplosiveCount + 2);
    ((gbMatrixStack *)v6)->Rotate(this->m_vecRot.z, (gbVec3D *)(&g_PAL3.m_nCEffExplosiveCount + 2));
    ((gbMatrixStack *)v6)->Scale(this->m_fSize,   this->m_fHeight,   this->m_fSize);
    ((gbDynVertBuf *)this->m_pGeomQuad)->RenderGeomQuadViaStrip(this->m_nDivision, m_pAlphaBlendNoZ, this->m_pTextureArray, this->m_dwStartColor);
    ((gbMatrixStack *)v6)->Pop();
  }
}

// 0x004C45A0
void CEffCylinder::CreateTask(float p)
{
  CEffCylinder *v2; // edi
  double v3; // st7
  CEffObj *v4; // esi
  char *v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // eax
  int v13; // edx
  float *v14; // eax
  double v15; // st7
  int v16; // ecx
  double v17; // st7
  int v18; // eax
  float v20; // [esp+0x4] [ebp-0xC]
  float v21; // [esp+0x4] [ebp-0xC]
  int v22; // [esp+0x8] [ebp-0x8]
  float v23; // [esp+0x8] [ebp-0x8]
  int v24; // [esp+0xC] [ebp-0x4]
  float v25; // [esp+0xC] [ebp-0x4]
  int pa; // [esp+0x18] [ebp+0x8]
  float pb; // [esp+0x18] [ebp+0x8]
v3 = p - *((float *)this + 4);
  v4 = this + 1;
  *((float *)this + 4) = p;
  *((float *)this + 5) = v3;
  if ( *((float *)this + 5) > 0.0 )
  {
    pa = 0;
    if ( *((int *)this + 10) > 0 )
    {
      v24 = 0;
      while ( 1 )
      {
// [VFTABLE] v5 = (char *)v4[1].__vftable + v24;
        if ( v5[148] )
        {
          if ( *((_DWORD *)v5 + 3) == 3 )
          {
            v6 = 0;
            v22 = 0;
            if ( *(int *)&v4[2].m_bIdle > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++pa < (int)v4[2].m_pEM;
        v24 += 152;
        if ( !v11 )
          goto LABEL_30;
      }
      v7 = 0;
      while ( 1 )
      {
        v8 = *(_DWORD *)v5 + v7;
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
                  ((CCBStage *)v4)->GetTaskParam(pa, v6);
                  v4[1].m_pEM = (CEffMgr *)pa;
                  *(_DWORD *)&v4[1].m_bIdle = v22;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v4[1].__vftable + v24) + v7 + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v4[1].__vftable + v24) + v7 + 16) = v4->m_pEM;
LABEL_21:
                *(_DWORD *)&v4[1].m_bIdle = v6;
                v4[1].m_pEM = (CEffMgr *)pa;
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
            if ( ((CCBStage *)v4)->SetTaskState(pa) )
            {
              v9 = *((_DWORD *)v5 + 1);
              *((_DWORD *)v5 + 3) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = v5[149];
              *((_DWORD *)v5 + 5) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                ((CEffgbParticle *)v4)->Init(pa);
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = v22 + 1;
        v7 += 72;
        if ( ++v22 >= *(_DWORD *)&v4[2].m_bIdle )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *((int *)v2 + 9) <= 0 )
      this->m_bIdle = 1;
    if ( !this->m_bIdle && (this->m_fFramePerSec != 0.0 && this->m_byMaxFrame != 1 || this->m_fCurTextureV != 0.0) )
    {
      v20 = this->m_fTextureRepeat / (double)this->m_nDivision;
      this->m_fCurFrame = this->m_fFramePerSec * *((float *)v2 + 5) + this->m_fCurFrame;
      if ( (g_bEffSystemFlags & 1) == 0 )
      {
        g_bEffSystemFlags |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      v12 = (int)abs32((int)this->m_fCurFrame) % (unsigned __int8)this->m_byMaxFrame;
      v13 = v12 + 13;
      v14 = (float *)((char *)v2 + 16 * v12);
      v25 = v14[49];
      v21 = (v14[51] - v25) * v20;
      pb = v14[50] + this->m_fCurTextureV;
// [VFTABLE] v23 = *((float *)&this->__vftable + 4 * v13) + this->m_fCurTextureV;
      if ( (g_bEffSystemFlags & 1) == 0 )
      {
        g_bEffSystemFlags |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      v15 = (double)(int)pb;
      if ( v15 > 1.0 )
      {
        pb = pb - v15;
        v23 = v23 - v15;
      }
      v16 = 0;
      if ( this->m_nDivision > 0 )
      {
        v17 = v25;
        v18 = 0;
        do
        {
          ++v16;
          this->m_pGeomQuad[v18].su = v17;
          v17 = v17 + v21;
          this->m_pGeomQuad[v18++].eu = v17;
          this->m_pGeomQuad[v18 - 1].sv = pb;
          this->m_pGeomQuad[v18 - 1].ev = v23;
        }
        while ( v16 < this->m_nDivision );
      }
    }
  }
}

// 0x004C48D0
void CEffCylinder::ProcInitTask(int *dwParam)
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
    v8 = ++g_PAL3.m_nsub_4C55F0Count_DE9380;
    if ( !g_PAL3.m_nsub_4C55F0Count_DE9380 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_PAL3.m_nsub_4C55F0Count_DE9380 = 1;
    }
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 16) = v8;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 4) = 0;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 8) = 0;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 20) = 0;
    if ( dwParam )
// [VFTABLE] qmemcpy((char *)v2[1].__vftable + v7 + 24, dwParam, 0x7Cu);
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
        v14 = ++g_PAL3.m_nsub_4C55F0Count_DE9380;
        if ( !g_PAL3.m_nsub_4C55F0Count_DE9380 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_PAL3.m_nsub_4C55F0Count_DE9380 = 1;
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
        v20 = ++g_PAL3.m_nsub_4C55F0Count_DE9380;
        if ( !g_PAL3.m_nsub_4C55F0Count_DE9380 || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_PAL3.m_nsub_4C55F0Count_DE9380 = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v2[1].__vftable + v7 + 4);
      }
LABEL_31:
      sub_4C55F0(v4, sub_4C4B00, 0, 0, dwParam[18], dwParam[19]);
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 12) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v2[1].__vftable + v7) + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v2[1].__vftable + v7) + 16) = v2->m_pEM;
    }
  }
}

// 0x004C5010
const char * CEffCylinder::GetEditorTaskDescription(int nIndex)
{
  const char *result; // eax

  switch ( nIndex )
  {
    case 0:
      result = (const char *)dword_5D5050;
      break;
    case 1:
      result = (const char *)dword_5D4E40;
      break;
    case 2:
      result = (const char *)dword_5D4E38;
      break;
    case 3:
      result = (const char *)dword_5D4E30;
      break;
    case 4:
      result = (const char *)dword_5D4E24;
      break;
    case 5:
      result = (const char *)dword_5D5048;
      break;
    case 6:
      result = (const char *)dword_5D5040;
      break;
    case 7:
      result = (const char *)dword_5D5038;
      break;
    case 8:
      result = (const char *)dword_5D4E00;
      break;
    case 9:
      result = (const char *)&g_EffEditorState;
      break;
    case 10:
      result = (const char *)dword_5D502C;
      break;
    case 11:
      result = (const char *)dword_5D5020;
      break;
    case 12:
      result = (const char *)dword_5D4DD4;
      break;
    case 13:
      result = (const char *)dword_5D4DCC;
      break;
    case 14:
      result = (const char *)dword_5D4DC4;
      break;
    case 15:
      result = (const char *)dword_5D4DB8;
      break;
    case 16:
      result = (const char *)dword_5D4DAC;
      break;
    case 17:
      result = (const char *)dword_5D5014;
      break;
    case 18:
      result = (const char *)dword_5D5008;
      break;
    case 19:
      result = (const char *)dword_5D4FFC;
      break;
    case 20:
      result = (const char *)&g_pszEditorDesc;
      break;
    case 21:
      result = (const char *)dword_5D4FF0;
      break;
    case 22:
      result = (const char *)dword_5D4FE0;
      break;
    case 23:
      result = (const char *)dword_5D4FD0;
      break;
    default:
      result = (const char *)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004C5150
const char * CEffCylinder::GetEditorObjDescription(int nIndex)
{
  const char *result; // eax

  switch ( nIndex )
  {
    case 0:
      result = (const char *)dword_5D50E4;
      break;
    case 1:
      result = (const char *)dword_5D50D8;
      break;
    case 2:
      result = (const char *)dword_5D50CC;
      break;
    case 3:
      result = (const char *)dword_5D50C0;
      break;
    case 4:
      result = (const char *)dword_5D50B8;
      break;
    case 5:
      result = (const char *)dword_5D50B0;
      break;
    case 6:
      result = (const char *)dword_5D50A4;
      break;
    case 7:
      result = (const char *)dword_5D5098;
      break;
    case 8:
      result = (const char *)dword_5D508C;
      break;
    case 9:
      result = (const char *)dword_5D5080;
      break;
    case 10:
      result = (const char *)dword_5D5074;
      break;
    case 11:
      result = (const char *)dword_5D5068;
      break;
    case 12:
      result = (const char *)dword_5D505C;
      break;
    default:
      result = (const char *)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004C5210
void CEffCylinder::InitDefaultUVSet(int nFramePerRow, int nFramePerCol)
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

// 0x004C52C0
int * CEffCylinder::LoadTexture(char *pFileName)
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
      ((Logger *)&ArgList)->FormatException("C++ new failed!", "D:\\Project\\PAL3\\combat\\EffCylinder.cpp", 504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004C7680
int CEffCylinder::ProcCommonTask__ovl(int a2)
{
  double v3; // st7
  int v4; // edi
  int v5; // ecx
  double v6; // st7
  int v7; // ebp
  double m_fAlpha; // st7
  unsigned __int16 v9; // cx
  float fTime; // [esp+0x10] [ebp-0x80]
  int fTimea; // [esp+0x10] [ebp-0x80]
  float fDeltaTime; // [esp+0x24] [ebp-0x6C]
  float v14; // [esp+0x28] [ebp-0x68]
  float v15; // [esp+0x2C] [ebp-0x64]
  float v16; // [esp+0x30] [ebp-0x60]
  float v17; // [esp+0x34] [ebp-0x5C]
  gbVec3D v18; // [esp+0x38] [ebp-0x58] BYREF
  struct gbVec3D v19; // [esp+0x44] [ebp-0x4C] BYREF
  gbMatrix4 v20; // [esp+0x50] [ebp-0x40] BYREF

  v3 = *((float *)this + 4);
  v4 = *((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7);
  v5 = 9 * *((_DWORD *)this + 8);
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  fDeltaTime = *((float *)this + 5);
  if ( v6 > *(float *)(v7 + 24) )
    fDeltaTime = fDeltaTime - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    *(_DWORD *)(v7 + 44) = 0;
    this->m_bVisible = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  if ( *((float *)this + 4) - *(float *)(v7 + 16) > *(float *)(v4 + 84) && !*(_DWORD *)(v7 + 44) )
  {
    ((CEffMgr *)this)->EmitParticles();
    *(_DWORD *)(v7 + 44) = 1;
  }
  this->m_vecRot.x = fDeltaTime * *(float *)(v4 + 64) + this->m_vecRot.x;
  this->m_vecRot.y = fDeltaTime * *(float *)(v4 + 68) + this->m_vecRot.y;
  this->m_vecRot.z = fDeltaTime * *(float *)(v4 + 72) + this->m_vecRot.z;
  this->m_vecPos.x = fDeltaTime * *(float *)(v4 + 28) + this->m_vecPos.x;
  this->m_vecPos.y = fDeltaTime * *(float *)(v4 + 32) + this->m_vecPos.y;
  this->m_vecPos.z = fDeltaTime * *(float *)(v4 + 36) + this->m_vecPos.z;
  memset(&v18, 0, sizeof(v18));
  memset(&v19, 0, sizeof(v19));
  ((gbMatrix4 *)&v20)->LoadIdentity();
  v18 = *(gbVec3D *)(v4 + 44);
  ((gbVec3D *)&v18)->Normalize();
  fTime = (*((float *)this + 4) - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  ((gbMatrix4 *)&v20)->SetAxisAngle(&v18, fTime);
  v19.z = *(float *)(v4 + 56);
  v19.x = 0.0;
  v19.y = 0.0;
  ((gbMatrix4 *)&v20)->Rotate(&v19, this->m_vecOffsetPos);
  if ( *(float *)(v4 + 80) != 0.0
    || *(float *)(v4 + 84) != 0.0
    || *(float *)(v4 + 92) != 0.0
    || *(float *)(v4 + 88) != 0.0 )
  {
    this->m_fAlpha = fDeltaTime * *(float *)(v4 + 80) + this->m_fAlpha;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fAlpha <= 255.0 )
    {
      if ( this->m_fAlpha >= 0.0 )
        m_fAlpha = this->m_fAlpha;
      else
        m_fAlpha = 0.0;
    }
    else
    {
      m_fAlpha = 255.0;
    }
    this->m_fAlpha = m_fAlpha;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v14 = this->m_fAlpha + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v15 = this->m_fRed + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v16 = this->m_fGreen + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v17 = this->m_fBlue + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    HIBYTE(v9) = LOBYTE(v14);
    LOBYTE(v9) = LOBYTE(v15);
    this->m_dwStartColor = LOBYTE(v17) | ((LOBYTE(v16) | (v9 << 8)) << 8);
  }
  this->m_fXSize = fDeltaTime * *(float *)(v4 + 24) + this->m_fXSize;
  this->m_fZSize = fDeltaTime * *(float *)(v4 + 108) + this->m_fZSize;
  if ( *(_DWORD *)(v7 + 44) == 1 )
  {
    *(float *)&fTimea = *((float *)this + 4) - *(float *)(v7 + 16);
    ((CEffExplosive *)this)->UpdateExplosive(fDeltaTime, fTimea);
  }
  if ( *(_BYTE *)(v7 + 66) == 1 || *((float *)this + 4) - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
    *(_DWORD *)(v7 + 8) = 4;
  return 0;
}

// 0x004CA450
int CEffCylinder::UpdateGeometry(int nVal)
{
  double v3; // st7
  int v4; // esi
  int v5; // ecx
  double v6; // st7
  int v7; // edi
  double m_fGreen; // st7
  double m_fBlue; // st7
  double m_fSize; // st7
  double m_fHeight; // st7
  unsigned __int16 v12; // cx
  int v13; // eax
  double v14; // st7
  gbTexture *m_pTexture; // esi
  gbTextureArray *m_pTextureArray; // edi
  float v18; // [esp+0x0] [ebp-0x84]
  float v19; // [esp+0x14] [ebp-0x70]
  float v20; // [esp+0x18] [ebp-0x6C]
  float v21; // [esp+0x1C] [ebp-0x68]
  float v22; // [esp+0x20] [ebp-0x64]
  float v23; // [esp+0x24] [ebp-0x60]
  int v24; // [esp+0x28] [ebp-0x5C]
  gbVec3D v25; // [esp+0x2C] [ebp-0x58] BYREF
  struct gbVec3D v26; // [esp+0x38] [ebp-0x4C] BYREF
  gbMatrix4 v27; // [esp+0x44] [ebp-0x40] BYREF

  v3 = *((float *)this + 4);
  v4 = *((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7);
  v5 = 9 * *((_DWORD *)this + 8);
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  v19 = *((float *)this + 5);
  v24 = v7;
  if ( v6 > *(float *)(v7 + 24) )
    v19 = v19 - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    LOBYTE(this->m_nLoops) = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  this->m_fTextureRepeat = v19 * *(float *)(v4 + 64) + this->m_fTextureRepeat;
  this->m_fFramePerSec = v19 * *(float *)(v4 + 68) + this->m_fFramePerSec;
  this->m_fCurTextureV = v19 * *(float *)(v4 + 72) + this->m_fCurTextureV;
  this->m_vecRot.x = v19 * *(float *)(v4 + 28) + this->m_vecRot.x;
  this->m_vecRot.y = v19 * *(float *)(v4 + 32) + this->m_vecRot.y;
  this->m_vecRot.z = v19 * *(float *)(v4 + 36) + this->m_vecRot.z;
  memset(&v25, 0, sizeof(v25));
  memset(&v26, 0, sizeof(v26));
  ((gbMatrix4 *)&v27)->LoadIdentity();
  v25 = *(gbVec3D *)(v4 + 44);
  ((gbVec3D *)&v25)->Normalize();
  v18 = (*((float *)this + 4) - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  ((gbMatrix4 *)&v27)->SetAxisAngle(&v25, v18);
  v26.z = *(float *)(v4 + 56);
  v26.x = 0.0;
  v26.y = 0.0;
  ((gbMatrix4 *)&v27)->Rotate(&v26, this->m_vecPos);
  if ( *(float *)(v4 + 80) != 0.0
    || *(float *)(v4 + 84) != 0.0
    || *(float *)(v4 + 92) != 0.0
    || *(float *)(v4 + 88) != 0.0 )
  {
    this->m_fGreen = v19 * *(float *)(v4 + 80) + this->m_fGreen;
    this->m_fBlue = v19 * *(float *)(v4 + 84) + this->m_fBlue;
    this->m_fSize = v19 * *(float *)(v4 + 88) + this->m_fSize;
    this->m_fHeight = v19 * *(float *)(v4 + 92) + this->m_fHeight;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fGreen <= 255.0 )
    {
      if ( this->m_fGreen >= 0.0 )
        m_fGreen = this->m_fGreen;
      else
        m_fGreen = 0.0;
    }
    else
    {
      m_fGreen = 255.0;
    }
    this->m_fGreen = m_fGreen;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fBlue <= 255.0 )
    {
      if ( this->m_fBlue >= 0.0 )
        m_fBlue = this->m_fBlue;
      else
        m_fBlue = 0.0;
    }
    else
    {
      m_fBlue = 255.0;
    }
    this->m_fBlue = m_fBlue;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fSize <= 255.0 )
    {
      if ( this->m_fSize >= 0.0 )
        m_fSize = this->m_fSize;
      else
        m_fSize = 0.0;
    }
    else
    {
      m_fSize = 255.0;
    }
    this->m_fSize = m_fSize;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fHeight <= 255.0 )
    {
      if ( this->m_fHeight >= 0.0 )
        m_fHeight = this->m_fHeight;
      else
        m_fHeight = 0.0;
    }
    else
    {
      m_fHeight = 255.0;
    }
    this->m_fHeight = m_fHeight;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v20 = this->m_fGreen + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v21 = this->m_fBlue + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v22 = this->m_fSize + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v23 = this->m_fHeight + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    HIBYTE(v12) = LOBYTE(v20);
    LOBYTE(v12) = LOBYTE(v21);
    LODWORD(this->m_fRed) = LOBYTE(v23) | ((LOBYTE(v22) | (v12 << 8)) << 8);
  }
  v13 = (LODWORD(this->m_fTopShrink) + 1) * (this->m_nDivision + 1);
  this->m_fRotAngle = v19 * *(float *)(v4 + 24) + this->m_fRotAngle;
  v14 = v19 * *(float *)(v4 + 108) + this->m_fWide;
  m_pTexture = this->m_pTexture;
  m_pTextureArray = this->m_pTextureArray;
  this->m_fWide = v14;
  qmemcpy(m_pTextureArray, m_pTexture, 4 * ((unsigned int)(12 * v13) >> 2));
  sub_4CB000(this);
  sub_4CB0C0(this);
  sub_4CAD10(this);
  qmemcpy(this->m_pTexture, this->m_pTextureArray, 12 * (LODWORD(this->m_fTopShrink) + 1) * (this->m_nDivision + 1));
  if ( *(_BYTE *)(v24 + 66) == 1 || *((float *)this + 4) - *(float *)(v24 + 16) >= *(float *)(v24 + 24) )
    *(_DWORD *)(v24 + 8) = 4;
  return 0;
}

// 0x004CC4C0
int CEffCylinder::Update(int nVal)
{
  double v3; // st7
  int v4; // edi
  int v5; // ecx
  double v6; // st7
  int v7; // ebp
  double m_fBottomRadiusIncSpeed; // st7
  double m_fBlue; // st7
  double m_fSize; // st7
  double m_fHeight; // st7
  double m_fRotAngle; // st7
  unsigned __int16 v13; // cx
  int v14; // edi
  int v15; // ebx
  float v17; // [esp+0x10] [ebp-0x80]
  int v18; // [esp+0x10] [ebp-0x80]
  float fVal; // [esp+0x24] [ebp-0x6C]
  float v20; // [esp+0x28] [ebp-0x68]
  float v21; // [esp+0x2C] [ebp-0x64]
  float v22; // [esp+0x30] [ebp-0x60]
  float v23; // [esp+0x34] [ebp-0x5C]
  gbVec3D v24; // [esp+0x38] [ebp-0x58] BYREF
  struct gbVec3D v25; // [esp+0x44] [ebp-0x4C] BYREF
  gbMatrix4 v26; // [esp+0x50] [ebp-0x40] BYREF

  v3 = *((float *)this + 4);
  v4 = *((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7);
  v5 = 9 * *((_DWORD *)this + 8);
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  fVal = *((float *)this + 5);
  if ( v6 > *(float *)(v7 + 24) )
    fVal = fVal - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    *(_DWORD *)(v7 + 44) = 0;
    LOBYTE(this->m_nLoops) = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  if ( *((float *)this + 4) - *(float *)(v7 + 16) >= *(float *)(v4 + 84) && !*(_DWORD *)(v7 + 44) )
  {
    sub_4CCDA0(this);
    *(_DWORD *)(v7 + 44) = 1;
  }
  this->m_fTextureRepeat = fVal * *(float *)(v4 + 64) + this->m_fTextureRepeat;
  this->m_fFramePerSec = fVal * *(float *)(v4 + 68) + this->m_fFramePerSec;
  this->m_fCurTextureV = fVal * *(float *)(v4 + 72) + this->m_fCurTextureV;
  this->m_vecRot.x = fVal * *(float *)(v4 + 28) + this->m_vecRot.x;
  this->m_vecRot.y = fVal * *(float *)(v4 + 32) + this->m_vecRot.y;
  this->m_vecRot.z = fVal * *(float *)(v4 + 36) + this->m_vecRot.z;
  memset(&v24, 0, sizeof(v24));
  memset(&v25, 0, sizeof(v25));
  ((gbMatrix4 *)&v26)->LoadIdentity();
  v24 = *(gbVec3D *)(v4 + 44);
  ((gbVec3D *)&v24)->Normalize();
  v17 = (*((float *)this + 4) - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  ((gbMatrix4 *)&v26)->SetAxisAngle(&v24, v17);
  v25.z = *(float *)(v4 + 56);
  v25.x = 0.0;
  v25.y = 0.0;
  ((gbMatrix4 *)&v26)->Rotate(&v25, this->m_vecPos);
  if ( *(float *)(v4 + 80) != 0.0
    || *(float *)(v4 + 84) != 0.0
    || *(float *)(v4 + 92) != 0.0
    || *(float *)(v4 + 88) != 0.0 )
  {
    this->m_fBlue = fVal * *(float *)(v4 + 80) + this->m_fBlue;
    this->m_fBottomRadiusIncSpeed = fVal * *(float *)(v4 + 80) + this->m_fBottomRadiusIncSpeed;
    this->m_fSize = fVal * *(float *)(v4 + 84) + this->m_fSize;
    this->m_fHeight = fVal * *(float *)(v4 + 88) + this->m_fHeight;
    this->m_fRotAngle = fVal * *(float *)(v4 + 92) + this->m_fRotAngle;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fBottomRadiusIncSpeed <= 255.0 )
    {
      if ( this->m_fBottomRadiusIncSpeed >= 0.0 )
        m_fBottomRadiusIncSpeed = this->m_fBottomRadiusIncSpeed;
      else
        m_fBottomRadiusIncSpeed = 0.0;
    }
    else
    {
      m_fBottomRadiusIncSpeed = 255.0;
    }
    this->m_fBottomRadiusIncSpeed = m_fBottomRadiusIncSpeed;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fBlue <= 255.0 )
    {
      if ( this->m_fBlue >= 0.0 )
        m_fBlue = this->m_fBlue;
      else
        m_fBlue = 0.0;
    }
    else
    {
      m_fBlue = 255.0;
    }
    this->m_fBlue = m_fBlue;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fSize <= 255.0 )
    {
      if ( this->m_fSize >= 0.0 )
        m_fSize = this->m_fSize;
      else
        m_fSize = 0.0;
    }
    else
    {
      m_fSize = 255.0;
    }
    this->m_fSize = m_fSize;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fHeight <= 255.0 )
    {
      if ( this->m_fHeight >= 0.0 )
        m_fHeight = this->m_fHeight;
      else
        m_fHeight = 0.0;
    }
    else
    {
      m_fHeight = 255.0;
    }
    this->m_fHeight = m_fHeight;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( this->m_fRotAngle <= 255.0 )
    {
      if ( this->m_fRotAngle >= 0.0 )
        m_fRotAngle = this->m_fRotAngle;
      else
        m_fRotAngle = 0.0;
    }
    else
    {
      m_fRotAngle = 255.0;
    }
    this->m_fRotAngle = m_fRotAngle;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v20 = this->m_fBlue + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v21 = this->m_fSize + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v22 = this->m_fHeight + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v23 = this->m_fRotAngle + 12582912.0;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    HIBYTE(v13) = LOBYTE(v20);
    LOBYTE(v13) = LOBYTE(v21);
    LODWORD(this->m_fGreen) = LOBYTE(v23) | ((LOBYTE(v22) | (v13 << 8)) << 8);
  }
  this->m_fWide = fVal * *(float *)(v4 + 24) + this->m_fWide;
  *(float *)&this->m_nDivision = fVal * *(float *)(v4 + 108) + *(float *)&this->m_nDivision;
  if ( *(_DWORD *)(v7 + 44) == 1 )
  {
    *(float *)&v18 = *((float *)this + 4) - *(float *)(v7 + 16);
    ((CEffMgr *)this)->UpdateEffect(fVal, v18);
  }
  if ( *(_BYTE *)(v7 + 66) == 1 || *((float *)this + 4) - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
  {
    v14 = 0;
    if ( SLODWORD(this->m_fTopShrink) > 0 )
    {
      v15 = 0;
      do
      {
        sub_4CD3A0((char *)this->m_pTexture + v15);
        ++v14;
        v15 += 56;
      }
      while ( v14 < SLODWORD(this->m_fTopShrink) );
    }
    *(_DWORD *)(v7 + 8) = 4;
  }
  return 0;
}
