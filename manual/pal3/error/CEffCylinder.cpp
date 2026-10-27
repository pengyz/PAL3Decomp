#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffCylinder.h"
#include "Combat/CCBStage.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffect.h"
#include "Effect/CEffgbParticle.h"
#include "Misc/CTaskTpl_tagEffTaskParam_CEffCylinder.h"
#include "GameBase/Logger.h"
#include "Misc/tagEffMgrData.h"
#include "Misc/tagEffObjType.h"
#include "Misc/tagEffTaskParam.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4C55F0(...);
int sub_4CAD10(...);
int sub_4CB000(...);
int sub_4CB0C0(...);

// Unnamed globals (extern)
void __cdecl nullsub_76(void);
void __cdecl nullsub_77(void);
void __cdecl nullsub_78(void);
extern struct gbVec3D stru_DE9350;
extern struct gbVec3D stru_DE9360;
extern struct gbVec3D stru_DE9370;

// 0x004C2600
void CEffCylinder::_todo_4C2600()
{
  double v1; // st7
  float v2; // [esp+0x4] [ebp+0x4]

  v1 = *(float *)&v2 - *(float *)&this->m_pEM;
  this->m_pEM = ((CEffMgr *)(v2));
  *(float *)&this->m_bIdle = v1;
}

// 0x004C2620
void CEffCylinder::_todo_4C2620()
{
  int v2; // ecx
  int v3; // esi
  int v4; // edx
  _BYTE *i; // eax
  _DWORD *v6; // edx
  unsigned int v7; // eax
  _DWORD *v8; // edx
  int v9; // [esp+0x10] [ebp+0x4]
  int v10; // [esp+0x14] [ebp+0x8]
  int v11; // [esp+0x18] [ebp+0xC]
  _DWORD *v12; // [esp+0x1C] [ebp+0x10]
  int v13; // [esp+0x20] [ebp+0x14]
  int v14; // [esp+0x24] [ebp+0x18]

  v2 = *(_DWORD *)&this->_tail_000[20];
  v3 = 0;
  if ( v2 > 0 )
  {
    v4 = *(_DWORD *)(*(_DWORD *)*(void**)(this) + 152 * v9);
    for ( i = (_BYTE *)(v4 + 64); *i; i += 72 )
    {
      if ( ++v3 >= v2 )
        return;
    }
    v6 = (_DWORD *)(v4 + 72 * v3);
    memset(v6, 0, 0x48u);
    *((_BYTE *)v6 + 65) = 0;
    *((_BYTE *)v6 + 64) = 1;
    *v6 = v10;
    v6[1] = v11;
    v6[2] = 2;
    v7 = ++g_nVideoTargetSeq;
    if ( !g_nVideoTargetSeq || v7 >= 0x7FFFFFFF )
    {
      v7 = 1;
      g_nVideoTargetSeq = 1;
    }
    v6[3] = v7;
    v6[4] = 0;
    v6[5] = v13;
    v6[6] = v14;
    if ( v12 )
    {
      v8 = (_DWORD *)(v6 + 7);
      *v8 = *v12;
      v8[1] = (unsigned long)v12[1];
      v8[2] = (unsigned long)v12[2];
      v8[3] = (unsigned long)v12[3];
    }
    ++*(_DWORD *)(*(_DWORD *)*(void**)(this) + 152 * v9 + 4);
  }
}

// 0x004C2850
void CEffCylinder::_todo_4C2850()
{
  void ( *v1)(char *, int); // [esp+0x4] [ebp+0x4]
  int v2; // [esp+0x8] [ebp+0x8]
  int v3; // [esp+0xC] [ebp+0xC]

  v1((char *)this + v2 - 12, v3);
}

// 0x004C3BB0
void CEffCylinder::_todo_4C3BB0()
{
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  char v5; // [esp+0x8] [ebp+0x4]

  v2 = *(_DWORD *)&this->_tail_000[16];
  if ( v2 || *(_DWORD *)&this->_tail_000[20] )
  {
    v3 = 0;
    if ( v2 > 0 )
    {
      v4 = 0;
      do
      {
        operator delete(*(void **)(*(_DWORD *)*(void**)(this) + v4));
        ++v3;
        *(_DWORD *)(*(_DWORD *)*(void**)(this) + v4) = 0;
        v4 += 152;
      }
      while ( v3 < *(_DWORD *)&this->_tail_000[16] );
    }
    operator delete(*(void **)*(void**)(this));
    *(_DWORD *)*(void**)(this) = 0;
    *(_DWORD *)&this->_tail_000[16] = 0;
    *(_DWORD *)&this->_tail_000[20] = 0;
  }
  if ( (v5 & 1) != 0 )
    operator delete(this);
}

// 0x004C3C90
CEffCylinder ** CEffCylinder::Init()
{
  CEffCylinder **result; // eax

  result = (CEffCylinder **)this;
  this->m_pEM = ((CEffMgr *)0);
  this->m_bIdle = 0;
  *(_DWORD *)&this->_tail_000[4] = 0;
  *(_DWORD *)&this->_tail_000[8] = 0;
  *(_DWORD *)&this->_tail_000[12] = 0;
  *(_DWORD *)&this->_tail_000[16] = -1;
  *(_DWORD *)&this->_tail_000[20] = -1;
  *(_DWORD *)&this->_tail_000[24] = 0;
  *(_DWORD *)&this->_tail_000[28] = 0;
  *(_DWORD *)&this->_tail_000[32] = 0;
  this->m_vecRot.x = 0.0f;
  this->m_vecRot.y = 0.0f;
  this->m_vecRot.z = 0.0f;
  this->m_vecPos.x = 0.0f;
  this->m_vecPos.y = 0.0f;
  this->m_vecPos.z = 0.0f;
  this->m_vecOffsetPos.x = 0.0f;
  this->m_vecOffsetPos.y = 0.0f;
  this->m_vecOffsetPos.z = 0.0f;
  this->m_fRotAngle = 360.0f;
  this->m_fWide = 10.0f;
  this->m_nDivision = 10;
  this->m_fTopShrink = 0.0f;
  this->m_fBottomShrink = 0.0f;
  this->m_fTopRadius = 50.0f;
  this->m_fBottomRadius = 50.0f;
  this->m_fTopRadiusIncSpeed = 0.0f;
  this->m_fBottomRadiusIncSpeed = 0.0f;
  this->m_fTopRiseSpeed = 0.0f;
  this->m_fBottomRiseSpeed = 0.0f;
  this->m_vecPos.z = 0.0f;
  this->m_vecPos.y = 0.0f;
  this->m_vecPos.x = 0.0f;
  this->m_vecOffsetPos.z = 0.0f;
  this->m_vecOffsetPos.y = 0.0f;
  this->m_vecOffsetPos.x = 0.0f;
  this->m_vecRot.z = 0.0f;
  this->m_vecRot.y = 0.0f;
  this->m_vecRot.x = 0.0f;
  this->m_pGeomQuad = ((gbGeomQuad *)0);
  this->m_bAdditiveBlend = 0;
  this->m_bNoZTest = 0;
  this->m_pTexture = ((gbTexture *)0);
  this->m_pTextureArray = ((gbTextureArray *)0);
  return result;
}

// 0x004C3D90
void CEffCylinder::AllocEffect()
{
  CEffCylinder *v1; // eax

  v1 = (CEffCylinder *)operator new(0x10C4u);
  if ( v1 )
    (((CEffCylinder *)v1))->CEffCylinder::Init();
}

// 0x004C3EB0
CEffCylinder::~CEffCylinder()
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
  this->m_vecOffsetPos.z = 0.0f;
  this->m_vecOffsetPos.y = 0.0f;
  this->m_vecOffsetPos.x = 0.0f;
  this->m_dwStartColor = (unsigned int)pType[51];
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  this->m_fAlpha = (float)HIBYTE(this->m_dwStartColor);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  this->m_fRed = (float)(unsigned __int8)BYTE2(this->m_dwStartColor);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  result = (unsigned __int8)BYTE1(this->m_dwStartColor);
  this->m_fGreen = (float)result;
  LOBYTE(result) = g_bEffSystemFlags;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    result = atexit(j_j_codecvt_base);
  }
  this->m_fCurTextureV = 0.0f;
  m_dwStartColor_low = LOBYTE(this->m_dwStartColor);
  this->m_fCurFrame = 0.0f;
  this->m_nLoops = 0;
  this->m_fBlue = (float)m_dwStartColor_low;
  v8 = pType[50];
  this->m_fHeight = 1.0f;
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

  v3 = (void *)operator new(0x4C0u);
  *(_DWORD *)&this->_tail_000[12] = (_DWORD)v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v5 + *(_DWORD *)&this->_tail_000[12]) = (unsigned long)operator new(0x2D0u);
      if ( !*(_DWORD *)(v5 + *(_DWORD *)&this->_tail_000[12]) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *(_DWORD *)&this->_tail_000[28] = 8;
        *(_DWORD *)&this->_tail_000[32] = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(v7 + *(_DWORD *)&this->_tail_000[12] + 148) = 0;
          v8 = 0;
          if ( *(int *)&this->_tail_000[32] > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(*(_DWORD *)(v7 + *(_DWORD *)&this->_tail_000[12]) + v9 - 8) = 0;
            }
            while ( v8 < *(_DWORD *)&this->_tail_000[32] );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *(_DWORD *)&this->_tail_000[28] );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v13 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v13 + *(_DWORD *)&this->_tail_000[12]));
        v13 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*(void **)&this->_tail_000[12]);
  }
LABEL_10:
  this->m_fRotAngle = pType->fSacleX;
  this->m_fWide = pType->fSacleY;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
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
  this->CEffCylinder::InitDefaultUVSet(pType->nFramePerRow, pType->nFramePerCol);
  pTypea = this->m_nDivision;
  v11 = (gbGeomQuad *)operator new(68 * pTypea);
  Block = (void *)v11;
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
  this->m_pGeomQuad = ((gbGeomQuad *)(v11));
  if ( !v11 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[472], &g_EffMgrData._tail_000[508], 127),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->CEffCylinder::LoadTexture(pType->szTexture);
  (((CEffMgr *)this))->CEffMgr::UpdateParticlePositions();
  return 1;
}

// 0x004C4370
void CEffCylinder::Destroy()
{
  char m_bAdditiveBlend; // al
  bool v3; // zf
  CEffMgr *m_pEM; // eax
  gbRenderEffect *v5; // ebp
  gbMatrixStack *v6; // edi
  gbDynVertBuf *v7; // [esp+0x2C] [ebp-0x1C]
  float v8; // [esp+0x3C] [ebp-0xC]
  float retaddr; // [esp+0x48] [ebp+0x0] BYREF

  if ( (g_bCEffCylinderFlag_DE937C & 1) == 0 )
  {
    stru_DE9370.x = 1.0;
    LOBYTE(g_bCEffCylinderFlag_DE937C) = g_bCEffCylinderFlag_DE937C | 1;
    stru_DE9370.y = 0.0;
    stru_DE9370.z = 0.0;
    atexit(nullsub_78);
  }
  if ( (g_bCEffCylinderFlag_DE937C & 2) == 0 )
  {
    stru_DE9360.x = 0.0;
    LOBYTE(g_bCEffCylinderFlag_DE937C) = g_bCEffCylinderFlag_DE937C | 2;
    stru_DE9360.y = 1.0;
    stru_DE9360.z = 0.0;
    atexit(nullsub_77);
  }
  if ( (g_bCEffCylinderFlag_DE937C & 4) == 0 )
  {
    stru_DE9350.x = 0.0;
    LOBYTE(g_bCEffCylinderFlag_DE937C) = g_bCEffCylinderFlag_DE937C | 4;
    stru_DE9350.y = 0.0;
    stru_DE9350.z = 1.0;
    atexit(nullsub_76);
  }
  if ( !this->m_bIdle && this->m_bVisible )
  {
    (((gbVertPoolMgr *)*(gbVertPoolMgr **)(*(_DWORD *)this->m_pEM + 196)))->gbVertPoolMgr::GetDynVertBuf(0x15u);
    m_bAdditiveBlend = this->m_bAdditiveBlend;
    if ( this->m_bNoZTest )
    {
      v3 = m_bAdditiveBlend == 0;
      m_pEM = this->m_pEM;
      if ( v3 )
        v5 = (gbRenderEffect *)(*(gbRenderEffect **)&m_pEM->_tail_000[12]);
      else
        v5 = (gbRenderEffect *)(*(gbRenderEffect **)&m_pEM->_tail_000[8]);
    }
    else
    {
      v3 = m_bAdditiveBlend == 0;
      m_pEM = this->m_pEM;
      if ( v3 )
        v5 = (gbRenderEffect *)(*(gbRenderEffect **)&m_pEM->_tail_000[20]);
      else
        v5 = (gbRenderEffect *)(*(gbRenderEffect **)&m_pEM->_tail_000[16]);
    }
    v6 = (gbMatrixStack *)*(gbMatrixStack **)(*(_DWORD *)*(void**)(m_pEM) + 216);
    (((gbMatrixStack *)v6))->gbMatrixStack::Push();
    v8 = this->m_vecOffsetPos.x + this->m_vecPos.x;
    retaddr = v8;
    (((gbMatrixStack *)v6))->gbMatrixStack::Translate(*(gbVec3D *)&retaddr);
    (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(this->m_vecRot.x,  stru_DE9370);
    (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(this->m_vecRot.y,  stru_DE9360);
    (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(this->m_vecRot.z,  stru_DE9350);
    (((gbMatrixStack *)v6))->gbMatrixStack::Scale(this->m_fSize,   this->m_fHeight,   this->m_fSize);
    (((gbDynVertBuf *)v7))->gbDynVertBuf::RenderGeomQuadViaStrip(this->m_pGeomQuad, this->m_nDivision, v5, this->m_pTextureArray, this->m_dwStartColor);
    (((gbMatrixStack *)v6))->gbMatrixStack::Pop();
  }
}

// 0x004C45A0
void CEffCylinder::CreateTask(float p)
{
  CEffCylinder *v2; // edi
  float v3; // st7
  CTaskTpl_tagEffTaskParam_CEffCylinder *v4; // esi
  int v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // eax
  int v13; // edx
  float *v14; // eax
  float v15; // st7
  int v16; // ecx
  float v17; // st7
  int v18; // eax
  float v20; // [esp+0x4] [ebp-0xC]
  float v21; // [esp+0x4] [ebp-0xC]
  int v22; // [esp+0x8] [ebp-0x8]
  float v23; // [esp+0x8] [ebp-0x8]
  int v24; // [esp+0xC] [ebp-0x4]
  float v25; // [esp+0xC] [ebp-0x4]
  int pa; // [esp+0x18] [ebp+0x8]
  float pb; // [esp+0x18] [ebp+0x8]
v3 = p - *(float *)&this->_tail_000[4];
  v4 = ((CTaskTpl_tagEffTaskParam_CEffCylinder *)((char *)this + 12));
  *(float *)&this->_tail_000[4] = p;
  *(float *)&this->_tail_000[8] = v3;
  if ( *(float *)&this->_tail_000[8] > 0.0f )
  {
    pa = 0;
    if ( *(int *)&this->_tail_000[28] > 0 )
    {
      v24 = 0;
      while ( 1 )
      {
        v5 = v24 + *(_DWORD *)&v4->_tail_000[12];
        if ( *(_BYTE *)(v5 + 148) )
        {
          if ( *(_DWORD *)(v5 + 12) == 3 )
          {
            v6 = 0;
            v22 = 0;
            if ( *(int *)&v4->_tail_000[32] > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++pa < *(_DWORD *)&v4->_tail_000[28];
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
              if ( *(float *)(v8 + 20) >= 0.0f )
              {
                if ( *(float *)&v4->_tail_000[4] - *(float *)(v8 - 56) > *(float *)(v8 + 20) )
                {
                  (((CCBStage *)v4))->CCBStage::GetTaskParam(pa, v6);
                  *(_DWORD *)&v4->_tail_000[16] = pa;
                  *(_DWORD *)&v4->_tail_000[20] = v22;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
                *(_DWORD *)(*(_DWORD *)(v24 + *(_DWORD *)&v4->_tail_000[12]) + v7 + 8) = 3;
                *(_DWORD *)(*(_DWORD *)(v24 + *(_DWORD *)&v4->_tail_000[12]) + v7 + 16) = *(_DWORD *)&v4->_tail_000[4];
LABEL_21:
                *(_DWORD *)&v4->_tail_000[20] = v6;
                *(_DWORD *)&v4->_tail_000[16] = pa;
LABEL_24:
                (*(void ( **)(CTaskTpl_tagEffTaskParam_CEffCylinder *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)*(void**)(v4) + 4))(
                  v4,
                  *(_DWORD *)(*(_DWORD *)v5 + v7),
                  *(_DWORD *)(*(_DWORD *)v5 + v7 + 4),
                  0);
              }
            }
            break;
          case 3:
            goto LABEL_21;
          case 4:
            if ( (((CCBStage *)v4))->CCBStage::SetTaskState(pa) )
            {
              v9 = *(_DWORD *)(v5 + 4);
              *(_DWORD *)(v5 + 12) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = *(_BYTE *)(v5 + 149);
              *(_DWORD *)(v5 + 20) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                (((CEffgbParticle *)v4))->CEffgbParticle::Init(pa);
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = v22 + 1;
        v7 += 72;
        if ( ++v22 >= *(_DWORD *)&v4->_tail_000[32] )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *(int *)&this->_tail_000[24] <= 0 )
      this->m_bIdle = 1;
    if ( !this->m_bIdle && (this->m_fFramePerSec != 0.0f && this->m_byMaxFrame != 1 || this->m_fCurTextureV != 0.0f) )
    {
      v20 = this->m_fTextureRepeat / (float)this->m_nDivision;
      this->m_fCurFrame = this->m_fFramePerSec * *(float *)&this->_tail_000[8] + this->m_fCurFrame;
      if ( (g_bEffSystemFlags & 1) == 0 )
      {
        g_bEffSystemFlags |= 1u;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      v12 = (int)abs32((int)this->m_fCurFrame) % (unsigned __int8)this->m_byMaxFrame;
      v13 = v12 + 13;
      v14 = (float *)((char *)this + 16 * v12);
      v25 = v14[49];
      v21 = (v14[51] - v25) * v20;
      pb = v14[50] + this->m_fCurTextureV;
      v23 = *((float *)&this->vfptr + 4 * v13) + this->m_fCurTextureV;
      if ( (g_bEffSystemFlags & 1) == 0 )
      {
        g_bEffSystemFlags |= 1u;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      v15 = (float)(int)pb;
      if ( v15 > 1.0f )
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
  CTaskTpl_tagEffTaskParam_CEffCylinder *v2; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // esi
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

  v2 = ((CTaskTpl_tagEffTaskParam_CEffCylinder *)((char *)this + 12));
  v3 = *(_DWORD *)&this->_tail_000[28];
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *(_DWORD *)&v2->_tail_000[12];
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 148) = 1;
    *(_BYTE *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 149) = 1;
    v8 = ++g_nCylinderInitSeq;
    if ( !g_nCylinderInitSeq || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nCylinderInitSeq = 1;
    }
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 16) = v8;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 4) = 0;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 8) = 0;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 20) = 0;
    if ( dwParam )
      qmemcpy((void *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 24), dwParam, 0x7Cu);
    else
      memset((void *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 24), 0, 0x7Cu);
    ++*(_DWORD *)&v2->_tail_000[24];
    if ( v4 != -1 )
    {
      v9 = *(_DWORD *)&v2->_tail_000[32];
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + 152 * v4);
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
        *(int (CEffect::**)(int))v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nCylinderInitSeq;
        if ( !g_nCylinderInitSeq || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nCylinderInitSeq = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 4);
      }
LABEL_22:
      v15 = *(_DWORD *)&v2->_tail_000[32];
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + 152 * v4);
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
        *(int (CEffect::**)(int))v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_nCylinderInitSeq;
        if ( !g_nCylinderInitSeq || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nCylinderInitSeq = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 4);
      }
LABEL_31:
      sub_4C55F0(v4, sub_4C4B00, 0, 0, dwParam[18], dwParam[19]);
      *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7) + 16) = *(_DWORD *)&v2->_tail_000[4];
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
      result = (const char *)&g_EffMgrData._tail_000[676];
      break;
    case 1:
      result = (const char *)&g_EffMgrData._tail_000[148];
      break;
    case 2:
      result = (const char *)&g_EffMgrData._tail_000[140];
      break;
    case 3:
      result = (const char *)&g_EffMgrData._tail_000[132];
      break;
    case 4:
      result = (const char *)&g_EffMgrData._tail_000[120];
      break;
    case 5:
      result = (const char *)&g_EffMgrData._tail_000[668];
      break;
    case 6:
      result = (const char *)&g_EffMgrData._tail_000[660];
      break;
    case 7:
      result = (const char *)&g_EffMgrData._tail_000[652];
      break;
    case 8:
      result = (const char *)&g_EffMgrData._tail_000[84];
      break;
    case 9:
      result = (const char *)&g_EffMgrData._tail_000[72];
      break;
    case 10:
      result = (const char *)&g_EffMgrData._tail_000[640];
      break;
    case 11:
      result = (const char *)&g_EffMgrData._tail_000[628];
      break;
    case 12:
      result = (const char *)&g_EffMgrData._tail_000[40];
      break;
    case 13:
      result = (const char *)&g_EffMgrData._tail_000[32];
      break;
    case 14:
      result = (const char *)&g_EffMgrData._tail_000[24];
      break;
    case 15:
      result = (const char *)&g_EffMgrData._tail_000[12];
      break;
    case 16:
      result = (const char *)&g_EffMgrData;
      break;
    case 17:
      result = (const char *)&g_EffMgrData._tail_000[616];
      break;
    case 18:
      result = (const char *)&g_EffMgrData._tail_000[604];
      break;
    case 19:
      result = (const char *)&g_EffMgrData._tail_000[592];
      break;
    case 20:
      result = (const char *)&g_pszEditorDesc;
      break;
    case 21:
      result = (const char *)&g_EffMgrData._tail_000[580];
      break;
    case 22:
      result = (const char *)&g_EffMgrData._tail_000[564];
      break;
    case 23:
      result = (const char *)&g_EffMgrData._tail_000[548];
      break;
    default:
      result = g_EffCylinderEditorData;
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
      result = (const char *)&g_EffMgrData._tail_000[824];
      break;
    case 1:
      result = (const char *)&g_EffMgrData._tail_000[812];
      break;
    case 2:
      result = (const char *)&g_EffMgrData._tail_000[800];
      break;
    case 3:
      result = (const char *)&g_EffMgrData._tail_000[788];
      break;
    case 4:
      result = (const char *)&g_EffMgrData._tail_000[780];
      break;
    case 5:
      result = (const char *)&g_EffMgrData._tail_000[772];
      break;
    case 6:
      result = (const char *)&g_EffMgrData._tail_000[760];
      break;
    case 7:
      result = (const char *)&g_EffMgrData._tail_000[748];
      break;
    case 8:
      result = (const char *)&g_EffMgrData._tail_000[736];
      break;
    case 9:
      result = (const char *)&g_EffMgrData._tail_000[724];
      break;
    case 10:
      result = (const char *)&g_EffMgrData._tail_000[712];
      break;
    case 11:
      result = (const char *)&g_EffMgrData._tail_000[700];
      break;
    case 12:
      result = (const char *)&g_EffMgrData._tail_000[688];
      break;
    default:
      result = g_EffCylinderEditorData;
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
  float v6; // st7
  float *v7; // eax
  float v8; // st5
  float v9; // st5
  float v10; // st3
  float v11; // st3
  int v12; // [esp+0x8] [ebp-0x8]
  float v13; // [esp+0x8] [ebp-0x8]
  int v14; // [esp+0xC] [ebp-0x4]

  v3 = 0;
  v12 = 0;
  if ( nFramePerCol > 0 )
  {
    p_eu = (float *)&this->m_DefaultUVSet[0].eu;
    do
    {
      v5 = 0;
      v14 = 0;
      if ( nFramePerRow > 0 )
      {
        v6 = (float)nFramePerRow;
        v7 = (float *)p_eu;
        p_eu += 4 * nFramePerRow;
        v8 = (float)nFramePerCol;
        v13 = (float)v12 / v8;
        v9 = 1.0f - (1.0f / v8 + v13);
        do
        {
          v10 = (float)v14;
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

  v3 = (gbTexture *)(*(int ( **)(_DWORD, char *))(**(_DWORD **)this->m_pEM + 8))(
                      *(_DWORD *)this->m_pEM,
                      pFileName);
  this->m_pTexture = ((gbTexture *)(v3));
  (((gbTexture *)v3))->gbTexture::LoadTexture(1);
  result = (int *)operator new(0x44u);
  if ( result )
  {
    m_pTexture = (gbTexture *)this->m_pTexture;
    result[16] = 1;
    *result = (int)m_pTexture;
  }
  else
  {
    result = 0;
  }
  this->m_pTextureArray = ((gbTextureArray *)((gbTextureArray *)result));
  if ( !result )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], &g_EffMgrData._tail_000[508], 504),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004C5800
void CEffCylinder::_todo_4C5800()
{
  float v1; // [esp+0x4] [ebp+0x4]

  (((CEffCylinder *)((char *)this - 12)))->CEffCylinder::CreateTask(v1);
}

// 0x004CA450
int CEffCylinder::UpdateGeometry(int nVal)
{
  float v3; // st7
  int v4; // esi
  int v5; // ecx
  float v6; // st7
  int v7; // edi
  float m_fGreen; // st7
  float m_fBlue; // st7
  float m_fSize; // st7
  float m_fHeight; // st7
  unsigned __int16 v12; // cx
  int v13; // eax
  float v14; // st7
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

  v3 = *(float *)&this->_tail_000[4];
  v4 = *(_DWORD *)&this->_tail_000[12] + 152 * *(_DWORD *)&this->_tail_000[16];
  v5 = 9 * *(_DWORD *)&this->_tail_000[20];
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  v19 = *(float *)&this->_tail_000[8];
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
  (((gbMatrix4 *)&v27))->gbMatrix4::LoadIdentity();
  v25 = *(gbVec3D *)(v4 + 44);
  (((gbVec3D *)&v25))->gbVec3D::Normalize();
  v18 = (*(float *)&this->_tail_000[4] - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  (((gbMatrix4 *)&v27))->gbMatrix4::SetAxisAngle(&v25, v18);
  v26.z = *(float *)(v4 + 56);
  v26.x = 0.0;
  v26.y = 0.0;
  (((gbMatrix4 *)&v27))->gbMatrix4::Rotate(&v26, &this->m_vecPos);
  if ( *(float *)(v4 + 80) != 0.0f
    || *(float *)(v4 + 84) != 0.0f
    || *(float *)(v4 + 92) != 0.0f
    || *(float *)(v4 + 88) != 0.0f )
  {
    this->m_fGreen = v19 * *(float *)(v4 + 80) + this->m_fGreen;
    this->m_fBlue = v19 * *(float *)(v4 + 84) + this->m_fBlue;
    this->m_fSize = v19 * *(float *)(v4 + 88) + this->m_fSize;
    this->m_fHeight = v19 * *(float *)(v4 + 92) + this->m_fHeight;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( this->m_fGreen <= 255.0f )
    {
      if ( this->m_fGreen >= 0.0f )
        m_fGreen = this->m_fGreen;
      else
        m_fGreen = 0.0f;
    }
    else
    {
      m_fGreen = 255.0f;
    }
    this->m_fGreen = m_fGreen;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( this->m_fBlue <= 255.0f )
    {
      if ( this->m_fBlue >= 0.0f )
        m_fBlue = this->m_fBlue;
      else
        m_fBlue = 0.0f;
    }
    else
    {
      m_fBlue = 255.0f;
    }
    this->m_fBlue = m_fBlue;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( this->m_fSize <= 255.0f )
    {
      if ( this->m_fSize >= 0.0f )
        m_fSize = this->m_fSize;
      else
        m_fSize = 0.0f;
    }
    else
    {
      m_fSize = 255.0f;
    }
    this->m_fSize = m_fSize;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( this->m_fHeight <= 255.0f )
    {
      if ( this->m_fHeight >= 0.0f )
        m_fHeight = this->m_fHeight;
      else
        m_fHeight = 0.0f;
    }
    else
    {
      m_fHeight = 255.0f;
    }
    this->m_fHeight = m_fHeight;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v20 = this->m_fGreen + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v21 = this->m_fBlue + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v22 = this->m_fSize + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v23 = this->m_fHeight + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    HIBYTE(v12) = LOBYTE(v20);
    LOBYTE(v12) = LOBYTE(v21);
    LODWORD(this->m_fRed) = LOBYTE(v23) | ((LOBYTE(v22) | (v12 << 8)) << 8);
  }
  v13 = (LODWORD(this->m_fTopShrink) + 1) * (this->m_nDivision + 1);
  this->m_fRotAngle = v19 * *(float *)(v4 + 24) + this->m_fRotAngle;
  v14 = v19 * *(float *)(v4 + 108) + this->m_fWide;
  m_pTexture = (gbTexture *)this->m_pTexture;
  m_pTextureArray = (gbTextureArray *)this->m_pTextureArray;
  this->m_fWide = v14;
  qmemcpy(m_pTextureArray, m_pTexture, 4 * ((unsigned int)(12 * v13) >> 2));
  sub_4CB000(this);
  sub_4CB0C0(this);
  sub_4CAD10(this);
  qmemcpy(this->m_pTexture, this->m_pTextureArray, 12 * (LODWORD(this->m_fTopShrink) + 1) * (this->m_nDivision + 1));
  if ( *(_BYTE *)(v24 + 66) == 1 || *(float *)&this->_tail_000[4] - *(float *)(v24 + 16) >= *(float *)(v24 + 24) )
    *(_DWORD *)(v24 + 8) = 4;
  return 0;
}
