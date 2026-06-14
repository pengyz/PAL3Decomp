#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffgbParticle.h"

// Forward declarations for unnamed functions
int sub_4C8E80(...);
int sub_4C90C0(...);
int sub_4C9260(...);
int sub_4C9320(...);
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
extern int dword_5D5038;
extern int dword_5D5040;
extern int dword_5D5048;
extern int dword_5D5050;
extern int dword_5D51A4;
extern int dword_5D51B0;
extern int dword_5D51BC;
extern int dword_5D51C8;
extern int dword_5D51D0;
extern int dword_5D51D8;
extern int dword_5D51E0;
extern int dword_5D51EC;
extern int dword_5D51F8;
extern int dword_5D5204;
extern int dword_5D5210;
extern int dword_5D521C;
extern int dword_5D522C;
void __cdecl nullsub_80(void);
void __cdecl nullsub_81(void);
void __cdecl nullsub_82(void);

// 0x004C6980
void CEffgbParticle::ReleaseEffect()
{
  CEffObj *v2; // edi
  ParticleEffect *m_pEffect; // eax
  int v4; // ebp
  float m_fX; // ecx
  CEffObj *v6; // esi
  CEffMgr *m_pEM; // eax
  bool v8; // cc
  int v9; // edi

  v2 = this + 1;
  m_pEffect = this->m_pEffect;
  v4 = 0;
  if ( m_pEffect )
    operator delete(m_pEffect);
  if ( LODWORD(this->m_fSize) )
    operator delete((void *)LODWORD(this->m_fSize));
  m_fX = this->m_fX;
  if ( m_fX != 0.0 )
    ((gbRefObject *)LODWORD(m_fX))->Release();
  if ( LODWORD(this->m_fY) )
    operator delete((void *)LODWORD(this->m_fY));
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

// 0x004C6C10
char CEffgbParticle::Create(tagEffObjType *pType)
{
  void *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // ebx
  ParticleEffect *v12; // eax
  int v13; // ebx
  int v14; // ebp
  int v15; // ebx
  int v16; // edi
  int v17; // ebx
  char *v18; // eax
  _DWORD *v19; // ecx
  int v20; // edx
  ParticleEffect *m_pEffect; // ecx
  ParticleEffect *v23; // [esp+0x10] [ebp-0x810]
  char pExceptionObject[1024]; // [esp+0x14] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x414] [ebp-0x40C] BYREF
  int v26; // [esp+0x81C] [ebp-0x4]

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
      v16 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v16 + *((_DWORD *)this + 6)));
        v16 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*((void **)this + 6));
  }
LABEL_10:
  *((_DWORD *)this + 27) = (__int64)pType->fSacleX;
  *((_DWORD *)this + 28) = (__int64)pType->fSacleZ;
  *((_DWORD *)this + 29) = LODWORD(pType->fSacleY);
  *((_DWORD *)this + 31) = LODWORD(pType->fTopRadius);
  *((_DWORD *)this + 32) = LODWORD(pType->fBottomRadius);
  *((_DWORD *)this + 33) = LODWORD(pType->fTopRadiusIncSpeed);
  *((_DWORD *)this + 34) = LODWORD(pType->fBottomRadiusIncSpeed);
  v10 = *((_DWORD *)this + 27) * *((_DWORD *)this + 28);
  *((_DWORD *)this + 35) = LODWORD(pType->fTextureRepeat);
  *((_DWORD *)this + 36) = LODWORD(pType->fTopRiseSpeed);
  *((_DWORD *)this + 30) = v10;
  *((_DWORD *)this + 37) = LODWORD(pType->fFramePerSec);
  *((_DWORD *)this + 41) = LODWORD(pType->fX);
  *((_DWORD *)this + 42) = LODWORD(pType->fY);
  *((_DWORD *)this + 43) = LODWORD(pType->fZ);
  *((_DWORD *)this + 38) = LODWORD(pType->fStartXRot);
  *((_DWORD *)this + 39) = LODWORD(pType->fStartYRot);
  *((_DWORD *)this + 40) = LODWORD(pType->fStartZRot);
  BYTE1(this->m_fZ) = pType->bAdditiveBlend;
  BYTE2(this->m_fZ) = pType->bNoZTest;
  HIBYTE(this->m_fZ) = pType->nFrame;
  LODWORD(this->m_fPX) = (unsigned long)&byte_FFFFFF;
  *((_DWORD *)this + 20) = pType->dwColor;
  ((CEffExplosive *)this)->InitDefaultUVSet(pType->nFramePerRow, pType->nFramePerCol);
  v11 = *((_DWORD *)this + 30);
  v12 = (ParticleEffect *)operator new(68 * v11);
  v23 = v12;
  v26 = 0;
  if ( v12 )
  {
    v13 = v11 - 1;
    v14 = (int)v12;
    if ( v13 >= 0 )
    {
      v15 = v13 + 1;
      do
      {
        v14 += 68;
        --v15;
      }
      while ( v15 );
      v12 = v23;
    }
  }
  else
  {
    v12 = 0;
  }
  v17 = *((_DWORD *)this + 30);
  this->m_pEffect = v12;
  v26 = -1;
  v18 = (char *)operator new(24 * v17);
  if ( v18 )
  {
    if ( v17 - 1 >= 0 )
    {
      v19 = v18 + 20;
      v20 = v17;
      do
      {
        *(v19 - 5) = 0;
        *(v19 - 4) = 0;
        *(v19 - 3) = 0;
        *(v19 - 2) = 0;
        *(v19 - 1) = 0;
        *v19 = 0;
        v19 += 6;
        --v20;
      }
      while ( v20 );
    }
  }
  else
  {
    v18 = 0;
  }
  m_pEffect = this->m_pEffect;
  LODWORD(this->m_fSize) = v18;
  if ( !m_pEffect || !v18 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("new fail in CEffExplosive::Create", "D:\\Project\\PAL3\\combat\\EffExplosive.cpp", 121),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((CEffExplosive *)this)->LoadTexture(pType->szTexture);
  return 1;
}

// 0x004C6F20
void CEffgbParticle::Destroy()
{
  char v2; // al
  bool v3; // zf
  CEffMgr *m_pEM; // eax
  gbRenderEffect *m_pAlphaBlendNoZ; // ebp
  gbMatrixStack *v6; // edi
  float v7; // [esp+0x3C] [ebp-0xC]
  float retaddr; // [esp+0x48] [ebp+0x0] BYREF

  if ( (g_PAL3.m_bCEffExplosiveFlag_DE99AC & 1) == 0 )
  {
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 392) = 1065353216;
    g_PAL3.m_bCEffExplosiveFlag_DE99AC |= 1u;
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 393) = 0;
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 394) = 0;
    atexit(nullsub_82);
  }
  if ( (g_PAL3.m_bCEffExplosiveFlag_DE99AC & 2) == 0 )
  {
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 388) = 0;
    g_PAL3.m_bCEffExplosiveFlag_DE99AC |= 2u;
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 389) = 1065353216;
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 390) = 0;
    atexit(nullsub_81);
  }
  if ( (g_PAL3.m_bCEffExplosiveFlag_DE99AC & 4) == 0 )
  {
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 384) = 0;
    g_PAL3.m_bCEffExplosiveFlag_DE99AC |= 4u;
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 385) = 0;
    *(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 386) = 1065353216;
    atexit(nullsub_80);
  }
  if ( !this->m_bIdle && LOBYTE(this->m_fZ) )
  {
    ((gbVertPoolMgr *)this->m_pEM->m_pDisplay->pVertPoolMgr)->GetDynVertBuf(0x15u);
    v2 = BYTE1(this->m_fZ);
    if ( BYTE2(this->m_fZ) )
    {
      v3 = v2 == 0;
      m_pEM = this->m_pEM;
      if ( v3 )
        m_pAlphaBlendNoZ = m_pEM->m_pAlphaBlendNoZ;
      else
        m_pAlphaBlendNoZ = m_pEM->m_pAdditiveBlendNoZ;
    }
    else
    {
      v3 = v2 == 0;
      m_pEM = this->m_pEM;
      if ( v3 )
        m_pAlphaBlendNoZ = m_pEM->m_pAlphaBlend;
      else
        m_pAlphaBlendNoZ = m_pEM->m_pAdditiveBlend;
    }
    v6 = m_pEM->m_pDisplay->pMatrixStack[1];
    ((gbMatrixStack *)v6)->Push();
    v7 = *((float *)this + 44) + *((float *)this + 41);
    retaddr = v7;
    ((gbMatrixStack *)v6)->Translate((gbVec3D *)&retaddr);
    ((gbMatrixStack *)v6)->Scale(*((float *)this + 25),   1.0,   *((float *)this + 26));
    ((gbMatrixStack *)v6)->Rotate(*((float *)this + 38), (gbVec3D *)(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 392));
    ((gbMatrixStack *)v6)->Rotate(*((float *)this + 39), (gbVec3D *)(&g_PAL3.m_nsub_4C55F0Count_DE9380 + 388));
    ((gbMatrixStack *)v6)->Rotate(*((float *)this + 40), (gbVec3D *)&g_PAL3.m_nsub_4C55F0Count_DE9380 + 128);
    ((gbDynVertBuf *)this->m_pEffect)->RenderGeomQuad(*((_DWORD *)this + 30), m_pAlphaBlendNoZ, (gbTextureArray *)LODWORD(this->m_fY));
    ((gbMatrixStack *)v6)->Pop();
  }
}

// 0x004C7A70
const char * CEffgbParticle::GetEditorTaskDescription(int nIndex)
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
      result = (const char *)dword_5D51B0;
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
      result = (const char *)dword_5D51A4;
      break;
    case 20:
      result = (const char *)&g_pszEditorDesc;
      break;
    default:
      result = (const char *)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004C7B70
const char * CEffgbParticle::GetEditorObjDescription(int nIndex)
{
  const char *result; // eax

  switch ( nIndex )
  {
    case 0:
      result = (const char *)dword_5D521C;
      break;
    case 1:
      result = (const char *)dword_5D5210;
      break;
    case 2:
      result = (const char *)dword_5D5204;
      break;
    case 3:
      result = (const char *)dword_5D51F8;
      break;
    case 4:
      result = (const char *)dword_5D51EC;
      break;
    case 5:
      result = (const char *)dword_5D51E0;
      break;
    case 6:
      result = (const char *)dword_5D51D8;
      break;
    case 7:
      result = (const char *)dword_5D51D0;
      break;
    case 8:
      result = (const char *)dword_5D51C8;
      break;
    case 9:
      result = (const char *)dword_5D51BC;
      break;
    default:
      result = (const char *)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004C8650
void CEffgbParticle::_CEffgbParticle(
        
        int nVal,
        int nVal2,
        int nVal3,
        int *p_DWORD,
        int nVal4,
        int nVal5)
{
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v12; // edx
  unsigned int v13; // eax
  int *v14; // edx

  v8 = *((_DWORD *)this + 8);
  v9 = 0;
  if ( v8 > 0 )
  {
    v10 = *(_DWORD *)(*((_DWORD *)this + 3) + 152 * nVal);
    for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
    {
      if ( ++v9 >= v8 )
        return;
    }
    v12 = (int *)(v10 + 72 * v9);
    memset(v12, 0, 0x48u);
    *((_BYTE *)v12 + 65) = 0;
    *((_BYTE *)v12 + 64) = 1;
    *v12 = nVal2;
    v12[1] = nVal3;
    v12[2] = 2;
    v13 = ++g_PAL3.m_nCEffCylinderCount;
    if ( !g_PAL3.m_nCEffCylinderCount || v13 >= 0x7FFFFFFF )
    {
      v13 = 1;
      g_PAL3.m_nCEffCylinderCount = 1;
    }
    v12[3] = v13;
    v12[4] = 0;
    v12[5] = nVal4;
    v12[6] = nVal5;
    if ( p_DWORD )
    {
      v14 = v12 + 7;
      *v14 = *p_DWORD;
      v14[1] = p_DWORD[1];
      v14[2] = p_DWORD[2];
      v14[3] = p_DWORD[3];
    }
    ++*(_DWORD *)(*((_DWORD *)this + 3) + 152 * nVal + 4);
  }
}

// 0x004C87A0
void * CEffgbParticle::Create(CEffgbParticle *Block, char pType)
{
  int v4; // eax
  int v5; // ebx
  int v6; // edi

  v4 = *((_DWORD *)this + 7);
  if ( v4 || *((_DWORD *)this + 8) )
  {
    v5 = 0;
    if ( v4 > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(*((_DWORD *)this + 3) + v6));
        ++v5;
        *(_DWORD *)(*((_DWORD *)this + 3) + v6) = 0;
        v6 += 152;
      }
      while ( v5 < *((_DWORD *)this + 7) );
    }
    operator delete(*((void **)this + 3));
    *((_DWORD *)this + 3) = 0;
    *((_DWORD *)this + 7) = 0;
    *((_DWORD *)this + 8) = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004C8830
int CEffgbParticle::Init(int pType)
{
  int v2; // edx
  int v3; // esi
  int result; // eax

  *(_BYTE *)(*((_DWORD *)this + 3) + 152 * pType + 148) = 0;
  v2 = 0;
  if ( *((int *)this + 8) > 0 )
  {
    v3 = 0;
    do
    {
      ++v2;
      v3 += 72;
      *(_BYTE *)(*(_DWORD *)(*((_DWORD *)this + 3) + 152 * pType) + v3 - 8) = 0;
    }
    while ( v2 < *((_DWORD *)this + 8) );
  }
  *(_DWORD *)(*((_DWORD *)this + 3) + 152 * pType + 4) = 0;
  result = *((_DWORD *)this + 6) - 1;
  *((_DWORD *)this + 6) = result;
  return result;
}

// 0x004C88C0
char * CEffgbParticle::Attach(char pData)
{
  char *v2; // esi

  v2 = (char *)this - 12;
  ((CEffgbParticle *)((char *)this - 12))->ReleaseEffect();
  if ( (pData & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004C88D0
int * CEffgbParticle::Render()
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
  this->m_pEffect = 0;
  this->m_fSize = 0.0;
  this->m_fZ = 0.0;
  this->m_fY = 0.0;
  this->m_fX = 0.0;
  this->m_fPZ = 0.0;
  this->m_fPY = 0.0;
  this->m_fPX = 0.0;
  return (int *)this;
}

// 0x004C8930
CEffgbParticle * CEffgbParticle::SetTimeScale()
{
  CEffgbParticle *v1; // eax

  v1 = (CEffgbParticle *)operator new(0x50u);
  if ( v1 )
    return (CEffgbParticle *)((CEffgbParticle *)v1)->Render();
  else
    return 0;
}

// 0x004C8970
void CEffgbParticle::Destroy__fastcall()
{
  CEffObj *v2; // edi
  ParticleEffect *m_pEffect; // ecx
  int v4; // ebx
  CEffObj *v5; // esi
  CEffMgr *m_pEM; // eax
  bool v7; // cc
  int v8; // edi

  v2 = this + 1;
  m_pEffect = this->m_pEffect;
  v4 = 0;
  if ( m_pEffect )
  {
    (**(void ( ***)(ParticleEffect *, int))m_pEffect->name)(m_pEffect, 1);
    this->m_pEffect = 0;
  }
  v5 = this != 0 ? v2 : 0;
  m_pEM = v5[2].m_pEM;
  v7 = (int)m_pEM <= 0;
  if ( !m_pEM )
  {
    if ( !*(this != 0 ? (_DWORD *)&v2[2].m_bIdle : (_DWORD *)32) )
      return;
    v7 = 1;
  }
  if ( !v7 )
  {
    v8 = 0;
    do
    {
// [VFTABLE] operator delete(*(void **)((char *)v5[1].__vftable + v8));
      ++v4;
// [VFTABLE] *(_DWORD *)((char *)v5[1].__vftable + v8) = 0;
      v8 += 152;
    }
    while ( v4 < (int)v5[2].m_pEM );
  }
// [VFTABLE] operator delete(v5[1].__vftable);
// [VFTABLE] v5[1].__vftable = 0;
  v5[2].m_pEM = 0;
  *(_DWORD *)&v5[2].m_bIdle = 0;
}

// 0x004C8A40
char CEffgbParticle::CreateTask(tagEffTaskParam *p)
{
  void *v3; // eax
  int v4; // ebp
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  ParticleEffect *v10; // eax
  ParticleEffect *v11; // eax
  int v12; // edi

  v3 = operator new(0x4C0u);
  *((_DWORD *)this + 6) = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(*((_DWORD *)this + 6) + v5) = operator new(0x2D0u);
      if ( !*(_DWORD *)(*((_DWORD *)this + 6) + v5) )
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
          *(_BYTE *)(*((_DWORD *)this + 6) + v7 + 148) = 0;
          v8 = 0;
          if ( *((int *)this + 11) > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(v9 + *(_DWORD *)(v7 + *((_DWORD *)this + 6)) - 8) = 0;
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
      v12 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(*((_DWORD *)this + 6) + v12));
        v12 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*((void **)this + 6));
  }
LABEL_10:
  v10 = (ParticleEffect *)operator new(0x5896Cu);
  if ( v10 )
    v11 = ((ParticleEffect *)v10)->Reset();
  else
    v11 = 0;
  this->m_pEffect = v11;
  return ((RenderTarget *)v11)->LoadParticleTextures((const char *)&p->fSoundStartTime3);
}

// 0x004C8B80
int CEffgbParticle::slot_2(int nVal, float a3, float a4, float a5)
{
  ParticleEffect *m_pEffect; // ecx
  int result; // eax
  double v9; // st7
  int nVala; // [esp+0x10] [ebp+0x4]

  this->m_bIdle = 0;
  m_pEffect = this->m_pEffect;
  nVala = *(int *)(nVal + 200);
  this->m_fSize = *(float *)&nVala;
  ((ParticleEffect *)m_pEffect)->SetTimeParam(nVala);
  result = (int)((CEffect *)this->m_pEffect)->SetQuadParam(0);
  this->m_fX = a3 + *(float *)(nVal + 184);
  this->m_fY = a4 + *(float *)(nVal + 188);
  v9 = a5 + *(float *)(nVal + 192);
  this->m_fPX = 0.0;
  this->m_fPY = 0.0;
  this->m_fPZ = 0.0;
  this->m_fZ = v9;
  return result;
}

// 0x004C8BF0
void CEffgbParticle::ProcCommonTask(float dwParam)
{
  CEffgbParticle *v2; // edi
  double v3; // st7
  CEffObj *v4; // esi
  int v5; // ecx
  int v6; // ebx
  char *v7; // ebp
  int v8; // edx
  int v9; // edi
  int v10; // ecx
  int v11; // ecx
  _DWORD *v12; // eax
  int v13; // edx
  _DWORD *v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // [esp+0xC] [ebp-0x8]
  CEffMgr *dwParama; // [esp+0x18] [ebp+0x4]
v3 = dwParam - *((float *)this + 4);
  v4 = this + 1;
  *((float *)this + 4) = dwParam;
  *((float *)this + 5) = v3;
  v5 = *((int *)this + 5);
  if ( *(float *)&v5 > 0.0 )
  {
    ((ParticleEffect *)this->m_pEffect)->SetDeltaTime(v5);
    v6 = 0;
    dwParama = 0;
    if ( (int)v4[2].m_pEM > 0 )
    {
      while ( 1 )
      {
// [VFTABLE] v7 = (char *)v4[1].__vftable + v6;
        if ( v7[148] )
        {
          if ( *((_DWORD *)v7 + 3) == 3 )
          {
            v8 = 0;
            v19 = 0;
            if ( *(int *)&v4[2].m_bIdle > 0 )
              break;
          }
        }
LABEL_33:
        v6 += 152;
        dwParama = (CEffMgr *)((char *)dwParama + 1);
        if ( (int)dwParama >= (int)v4[2].m_pEM )
        {
goto LABEL_35;
        }
      }
      v9 = 0;
      while ( 1 )
      {
        v10 = *(_DWORD *)v7;
        if ( !*(_BYTE *)(v9 + *(_DWORD *)v7 + 64) || v9 > 0 && *(_DWORD *)(v9 + v10 - 64) == 2 )
          goto LABEL_33;
        switch ( *(_DWORD *)(v9 + v10 + 8) )
        {
          case 2:
            if ( v9 > 0 )
            {
              if ( *(float *)(v9 + v10 + 20) >= 0.0 )
              {
                if ( *(float *)&v4->m_pEM - *(float *)(v9 + v10 - 56) > *(float *)(v9 + v10 + 20) )
                {
LABEL_25:
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v4[1].__vftable + v6) + v9 + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v4[1].__vftable + v6) + v9 + 16) = v4->m_pEM;
                  v4[1].m_pEM = dwParama;
                  *(_DWORD *)&v4[1].m_bIdle = v19;
                  goto LABEL_26;
                }
              }
              else if ( *(_DWORD *)(v9 + v10 - 64) == 4 )
              {
                goto LABEL_25;
              }
            }
            break;
          case 3:
            *(_DWORD *)&v4[1].m_bIdle = v8;
            v4[1].m_pEM = dwParama;
LABEL_26:
// [VFTABLE] (*((void ( **)(CEffObj *, _DWORD, _DWORD, _DWORD))v4->__vftable + 1))(
// [VFTABLE]   v4,
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v7 + v9),
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v7 + v9 + 4),
// [VFTABLE]   0);
            break;
          case 4:
            v11 = 0;
// [VFTABLE] v12 = (char *)v4[1].__vftable + v6;
            v13 = v12[1];
            if ( v13 <= 0 )
            {
LABEL_17:
              v15 = *((_DWORD *)v7 + 1);
              *((_DWORD *)v7 + 3) = 4;
              v16 = 9 * v15;
              LOBYTE(v15) = v7[149];
              *((_DWORD *)v7 + 5) = *(_DWORD *)(*(_DWORD *)v7 + 8 * v16 - 12);
              if ( (_BYTE)v15 == 1 )
              {
                v17 = 0;
// [VFTABLE] *((_BYTE *)v4[1].__vftable + v6 + 148) = 0;
                if ( *(int *)&v4[2].m_bIdle > 0 )
                {
                  v18 = 0;
                  do
                  {
                    ++v17;
                    v18 += 72;
// [VFTABLE] *(_BYTE *)(*(_DWORD *)((char *)v4[1].__vftable + v6) + v18 - 8) = 0;
                  }
                  while ( v17 < *(_DWORD *)&v4[2].m_bIdle );
                }
// [VFTABLE] *(_DWORD *)((char *)v4[1].__vftable + v6 + 4) = 0;
// [VFTABLE] --v4[2].__vftable;
                goto LABEL_33;
              }
            }
            else
            {
              v14 = (_DWORD *)(*v12 + 8);
              while ( *v14 == 4 )
              {
                ++v11;
                v14 += 18;
                if ( v11 >= v13 )
                  goto LABEL_17;
              }
            }
            break;
        }
        v8 = v19 + 1;
        v9 += 72;
        if ( ++v19 >= *(_DWORD *)&v4[2].m_bIdle )
          goto LABEL_33;
      }
    }
LABEL_35:
    if ( *((int *)v2 + 9) <= 0 )
      ((CEffect *)this->m_pEffect)->SetQuadParam(0);
  }
}

// 0x004C8E10
void CEffgbParticle::GetEditorTaskDescription()
{
  gbMatrixStack *v2; // edi
  int v3; // eax
  float v4; // [esp+0x0] [ebp-0x14]
  float v5; // [esp+0x4] [ebp-0x10]
  float v6; // [esp+0x8] [ebp-0xC]

  if ( !this->m_bIdle )
  {
    v2 = this->m_pEM->m_pDisplay->pMatrixStack[1];
    ((gbMatrixStack *)v2)->Push();
    v6 = this->m_fPZ + this->m_fZ;
    v5 = this->m_fPY + this->m_fY;
    v4 = this->m_fPX + this->m_fX;
    ((gbMatrixStack *)v2)->Translate(v4,   v5,   v6);
    v3 = ((RenderTarget *)this->m_pEffect)->RenderToTexture();
    if ( *((int *)this + 9) <= 0 && v3 <= 0 )
      this->m_bIdle = 1;
    ((gbMatrixStack *)v2)->Pop();
  }
}

// 0x004C8E80
int CEffgbParticle::sub_4C8E80(int a2)
{
  int result; // eax

  result = (int)this->m_pEffect;
  *(_DWORD *)(result + 362768) = a2;
  return result;
}

// 0x004C8E90
int CEffgbParticle::RenderEffectPass(int a2)
{
  int result; // eax
  CEffObj *v3; // ebx
  int v4; // ecx
  int v5; // edx
  char *vftable; // esi
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

  v3 = this + 1;
  v4 = *((_DWORD *)this + 10);
  v5 = 0;
  if ( v4 > 0 )
  {
// [VFTABLE] vftable = (char *)v3[1].__vftable;
    result = (int)(vftable + 148);
    while ( *(_BYTE *)result )
    {
      ++v5;
      result += 152;
      if ( v5 >= v4 )
        return result;
    }
    v7 = 152 * v5;
    *(_DWORD *)&vftable[v7 + 12] = 2;
// [VFTABLE] *((_BYTE *)v3[1].__vftable + v7 + 148) = 1;
// [VFTABLE] *((_BYTE *)v3[1].__vftable + v7 + 149) = 1;
    v8 = ++*(&g_PAL3.m_nCEffCylinderCount + 1);
    if ( !*(&g_PAL3.m_nCEffCylinderCount + 1) || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      *(&g_PAL3.m_nCEffCylinderCount + 1) = 1;
    }
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 16) = v8;
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 4) = 0;
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 8) = 0;
// [VFTABLE] result = (int)v3[1].__vftable;
    *(_DWORD *)(result + v7 + 20) = 0;
    if ( a2 )
    {
// [VFTABLE] qmemcpy((char *)v3[1].__vftable + v7 + 24, (const void *)a2, 0x7Cu);
    }
    else
    {
      result = 0;
// [VFTABLE] memset((char *)v3[1].__vftable + v7 + 24, 0, 0x7Cu);
    }
// [VFTABLE] ++v3[2].__vftable;
    if ( v5 != -1 )
    {
      v9 = *(_DWORD *)&v3[2].m_bIdle;
      v10 = 0;
      if ( v9 > 0 )
      {
// [VFTABLE] v11 = *((_DWORD *)v3[1].__vftable + 38 * v5);
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
        v14 = ++*(&g_PAL3.m_nCEffCylinderCount + 1);
        if ( !*(&g_PAL3.m_nCEffCylinderCount + 1) || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          *(&g_PAL3.m_nCEffCylinderCount + 1) = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v3[1].__vftable + v7 + 4);
      }
LABEL_22:
      v15 = *(_DWORD *)&v3[2].m_bIdle;
      v16 = 0;
      if ( v15 > 0 )
      {
// [VFTABLE] v17 = *((_DWORD *)v3[1].__vftable + 38 * v5);
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
        v20 = ++*(&g_PAL3.m_nCEffCylinderCount + 1);
        if ( !*(&g_PAL3.m_nCEffCylinderCount + 1) || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          *(&g_PAL3.m_nCEffCylinderCount + 1) = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v3[1].__vftable + v7 + 4);
      }
LABEL_31:
      sub_4C9320(v5, sub_4C90C0, 0, 0, *(_DWORD *)(a2 + 72), *(_DWORD *)(a2 + 76));
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 12) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v3[1].__vftable + v7) + 8) = 3;
// [VFTABLE] result = *(_DWORD *)((char *)v3[1].__vftable + v7);
      *(_DWORD *)(result + 16) = v3->m_pEM;
    }
  }
  return result;
}

// 0x004C9260
int CEffgbParticle::sub_4C9260(int a2)
{
  int result; // eax

  switch ( a2 )
  {
    case 0:
      result = (int)dword_5D522C;
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
    case 9:
      result = (int)&g_EffEditorState;
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
    case 20:
      result = (int)&g_pszEditorDesc;
      break;
    default:
      result = (int)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004C9540
char * CEffgbParticle::DestroyEffect(char pData)
{
  char *v2; // esi

  v2 = (char *)this - 12;
  ((CEffgbParticle *)((char *)this - 12))->Destroy__fastcall();
  if ( (pData & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004CEB60
int CEffgbParticle::CreateInstance(
        
        CEffgbParticle *pSrc,
        int nVal,
        CEffgbParticle *pParam)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  CEffgbParticle *v9; // eax
  int *v10; // eax

  v4 = 0;
  for ( i = (char *)this + 88; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pSrc);
  v8 = (const char *)pParam;
  if ( !pParam )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (CEffgbParticle *)operator new(0x50u);
  if ( v9 )
    v10 = ((CEffgbParticle *)v9)->Render();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pSrc);
  return v4;
}

// 0x004CFD40
int CEffgbParticle::_nearby_4cfd40()
{
  CEffObj *v2; // edi
  CEffObj *v3; // esi
  int result; // eax
  int v5; // ebx
  int v6; // edi

  v2 = a1 + 1;
  ((CEffgbParticle *)a1)->DestroyEffect();
  v3 = a1 != 0 ? v2 : 0;
  result = (int)v3[2].m_pEM;
  if ( result || *(a1 != 0 ? (_DWORD *)&v2[2].m_bIdle : (_DWORD *)32) )
  {
    v5 = 0;
    if ( result > 0 )
    {
      v6 = 0;
      do
      {
// [VFTABLE] operator delete(*(void **)((char *)v3[1].__vftable + v6));
        ++v5;
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v6) = 0;
        v6 += 152;
      }
      while ( v5 < (int)v3[2].m_pEM );
    }
// [VFTABLE] operator delete(v3[1].__vftable);
// [VFTABLE] v3[1].__vftable = 0;
    v3[2].m_pEM = 0;
    *(_DWORD *)&v3[2].m_bIdle = 0;
    return 0;
  }
  return result;
}

// 0x004D0A60
void CEffgbParticle::DestroyEffect()
{
  ParticleEffect *m_pEffect; // ecx

  m_pEffect = this->m_pEffect;
  if ( m_pEffect )
  {
    (**(void ( ***)(ParticleEffect *, int))m_pEffect->name)(m_pEffect, 1);
    this->m_pEffect = 0;
  }
}
