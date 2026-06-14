#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/ScreenEffectMgr.h"

// Forward declarations for unnamed functions
int sub_4BDF30(...);
int sub_5420D8(...);
int sub_5420DE(...);
int sub_54210E(...);

int crt_sub_00540070(void); // from annotations

// Unnamed globals (extern)
void __cdecl unknown_libname_430(void);

// 0x004BDF60
int ScreenEffectMgr::IsScriptDelNeeded()
{
  return (int)this->m_fadeIn.m_needscriptdel;
}

// 0x004BDF70
void ScreenEffectMgr::StartFade()
{
  this->m_fadeIn.m_needscriptdel = (gbImage2D *)1;
  this->m_fadeIn.m_life = 0;
}

// 0x004BE080
void ScreenEffectMgr::ClearAllEffects()
{
  int i; // eax
  int v3; // edi
  int v4; // eax
  void **m_pAllocSlot; // eax
  int *v6; // eax
  int v7; // ecx
  char *m_pEffect; // [esp-0xC] [ebp-0x20]

  for ( i = this->m_nEffectCount; i; i = this->m_nEffectCount )
  {
    v3 = this->m_pAllocPos + 4;
    v4 = i - 1;
    this->m_pAllocPos = v3;
    this->m_nEffectCount = v4;
    if ( !v4 || v3 == this->m_pAllocBlockEnd )
    {
      m_pAllocSlot = (void **)this->m_pAllocSlot;
      this->m_pAllocSlot = (int)(m_pAllocSlot + 1);
      operator delete(*m_pAllocSlot);
      if ( this->m_nEffectCount )
      {
        v6 = (int *)this->m_pAllocSlot;
        v7 = *v6;
        this->m_pAllocBlock = *v6;
        this->m_pAllocBlockEnd = v7 + 4096;
        this->m_pAllocPos = v7;
        this->m_pAllocSlot = (int)v6;
      }
      else
      {
        this->m_pAllocBlock = 0;
        this->m_pAllocBlockEnd = 0;
        this->m_pAllocPos = 0;
        this->m_pAllocSlot = 0;
        this->m_pAllocRest = 0;
        m_pEffect = this->m_pEffect;
        this->m_nAllocFlag1 = 0;
        this->m_nAllocFlag2 = 0;
        this->m_fAllocFactor = 0;
        operator delete(m_pEffect);
      }
    }
  }
  ((CameraCtrl *)&this->m_fadeWhite2)->RenderFadeEffectB();
  ((CameraCtrl *)&this->m_fadeWhite)->RenderFadeEffect();
  ((CameraCtrl *)&this->m_fadeOut)->OnIdleB();
  ((CameraCtrl *)&this->m_fadeIn)->OnIdle();
}

// 0x004BE1A0
int ScreenEffectMgr::ProcessEffect()
{
  void *p_m_fadeOut; // ebp
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  void **v6; // eax
  int *v7; // eax
  int v8; // ecx
  int m_nEffectCount; // eax
  char *m_activeQueue; // esi
  _DWORD *v11; // eax
  _DWORD *v12; // edx
  int *v14; // edi
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // edi
  unsigned int v19; // eax
  int **v20; // eax
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // ebx
  int v25; // edx
  int v26; // ecx
  int v27; // edx
  int v28; // edx
  int v29; // ecx
  int v30; // edx
  char *m_pEffect; // [esp-0xC] [ebp-0x24]
  int m_pAllocBlock; // [esp+0x8] [ebp-0x10] BYREF
  int m_pAllocBlockEnd; // [esp+0xC] [ebp-0xC]
  int v34; // [esp+0x10] [ebp-0x8]
  int m_pAllocSlot; // [esp+0x14] [ebp-0x4]
  int v36; // [esp+0x1C] [ebp+0x4]

  p_m_fadeOut = 0;
  switch ( v36 )
  {
    case 1:
      p_m_fadeOut = &this->m_fadeOut;
      goto LABEL_6;
    case 2:
      p_m_fadeOut = &this->m_fadeIn;
      goto LABEL_6;
    case 3:
      p_m_fadeOut = &this->m_fadeWhite;
      goto LABEL_6;
    case 4:
      p_m_fadeOut = &this->m_fadeWhite2;
LABEL_6:
      if ( !p_m_fadeOut )
        return (int)p_m_fadeOut;
      (*(void ( **)(void *))(*(_DWORD *)p_m_fadeOut + 12))(p_m_fadeOut);
      if ( this->m_nEffectCount )
      {
        m_pAllocBlock = this->m_pAllocBlock;
        m_pAllocBlockEnd = this->m_pAllocBlockEnd;
        v3 = *(_DWORD *)this->m_pAllocPos;
        m_pAllocSlot = this->m_pAllocSlot;
        if ( *(_BYTE *)(v3 + 20) )
        {
          if ( !*(_DWORD *)(v3 + 8) )
          {
            v4 = this->m_pAllocPos + 4;
            v5 = this->m_nEffectCount - 1;
            this->m_pAllocPos = v4;
            this->m_nEffectCount = v5;
            if ( !v5 || v4 == this->m_pAllocBlockEnd )
            {
              v6 = (void **)this->m_pAllocSlot;
              this->m_pAllocSlot = (int)(v6 + 1);
              operator delete(*v6);
              if ( this->m_nEffectCount )
              {
                v7 = (int *)this->m_pAllocSlot;
                v8 = *v7;
                this->m_pAllocBlock = *v7;
                this->m_pAllocBlockEnd = v8 + 4096;
                this->m_pAllocPos = v8;
                this->m_pAllocSlot = (int)v7;
              }
              else
              {
                this->m_pAllocBlock = 0;
                this->m_pAllocBlockEnd = 0;
                this->m_pAllocPos = 0;
                this->m_pAllocSlot = 0;
                this->m_pAllocRest = 0;
                this->m_nAllocFlag1 = 0;
                m_pEffect = this->m_pEffect;
                this->m_nAllocFlag2 = 0;
                this->m_fAllocFactor = 0;
                operator delete(m_pEffect);
              }
            }
          }
        }
      }
      m_nEffectCount = this->m_nEffectCount;
      m_activeQueue = this->m_activeQueue;
      if ( !m_nEffectCount
        || (v11 = (_DWORD *)*((_DWORD *)m_activeQueue + 7), v12 = (_DWORD *)*((_DWORD *)m_activeQueue + 6), v11 == v12) )
      {
        v14 = (int *)operator new(0x1000u);
        if ( *((_DWORD *)m_activeQueue + 11) )
        {
          v19 = *((_DWORD *)m_activeQueue + 8);
          if ( v19 >= *((_DWORD *)m_activeQueue + 9) + 4 * *((_DWORD *)m_activeQueue + 10) - 4 )
          {
            v24 = ((int)(v19 - *((_DWORD *)m_activeQueue + 4)) >> 2) + 1;
            *(_DWORD *)&((RoleSystem *)m_activeQueue)->GetRoleName(2 * v24)[4 * v24] = v14;
            ((ScreenEffect *)&m_pAllocBlock)->CopyParams(*((int **)m_activeQueue + 3));
            v25 = m_pAllocBlockEnd;
            *((_DWORD *)m_activeQueue + 1) = m_pAllocBlock;
            v26 = v34;
            *((_DWORD *)m_activeQueue + 2) = v25;
            v27 = m_pAllocSlot;
            *((_DWORD *)m_activeQueue + 3) = v26;
            *((_DWORD *)m_activeQueue + 4) = v27;
            ((ScreenEffect *)&m_pAllocBlock)->CopyParams(v14);
            v28 = m_pAllocBlockEnd;
            *((_DWORD *)m_activeQueue + 5) = m_pAllocBlock;
            v29 = v34;
            *((_DWORD *)m_activeQueue + 6) = v28;
            v30 = m_pAllocSlot;
            *((_DWORD *)m_activeQueue + 7) = v29;
            *((_DWORD *)m_activeQueue + 8) = v30;
          }
          else
          {
            v20 = (int **)(v19 + 4);
            *((_DWORD *)m_activeQueue + 8) = v20;
            *v20 = v14;
            ((ScreenEffect *)&m_pAllocBlock)->CopyParams(v14);
            v21 = m_pAllocBlockEnd;
            *((_DWORD *)m_activeQueue + 5) = m_pAllocBlock;
            v22 = v34;
            *((_DWORD *)m_activeQueue + 6) = v21;
            v23 = m_pAllocSlot;
            *((_DWORD *)m_activeQueue + 7) = v22;
            *((_DWORD *)m_activeQueue + 8) = v23;
          }
        }
        else
        {
          *((_DWORD *)m_activeQueue + 10) = 2;
          ((ScreenEffectMgr *)m_activeQueue)->GetFadeFlags();
          *(_DWORD *)(*((_DWORD *)m_activeQueue + 9) + 4) = v14;
          ((ScreenEffect *)&m_pAllocBlock)->CopyParams(v14 + 512);
          v15 = m_pAllocBlock;
          v16 = v34;
          v17 = m_pAllocBlockEnd;
          v18 = m_pAllocSlot;
          *((_DWORD *)m_activeQueue + 1) = m_pAllocBlock;
          *((_DWORD *)m_activeQueue + 2) = v17;
          *((_DWORD *)m_activeQueue + 3) = v16;
          *((_DWORD *)m_activeQueue + 4) = v18;
          *((_DWORD *)m_activeQueue + 5) = v15;
          *((_DWORD *)m_activeQueue + 6) = v17;
          *((_DWORD *)m_activeQueue + 7) = v16;
          *((_DWORD *)m_activeQueue + 8) = v18;
        }
        v11 = (_DWORD *)*((_DWORD *)m_activeQueue + 7);
        *((_DWORD *)m_activeQueue + 7) = v11 + 1;
        if ( v11 )
LABEL_29:
          *v11 = p_m_fadeOut;
      }
      else
      {
        *((_DWORD *)m_activeQueue + 7) = v11 + 1;
        if ( v11 + 1 == v12 )
        {
          if ( v11 )
            *v11 = p_m_fadeOut;
          ((ScreenEffectMgr *)m_activeQueue)->AllocEffectBlock();
          ++*((_DWORD *)m_activeQueue + 11);
          return (int)p_m_fadeOut;
        }
        if ( v11 )
          goto LABEL_29;
      }
      ++*((_DWORD *)m_activeQueue + 11);
      return (int)p_m_fadeOut;
    default:
      return (int)p_m_fadeOut;
  }
}

// 0x004BE4A0
void ScreenEffectMgr::UpdateFrontEffect()
{
  int v2; // edi
  int v3; // edx
  int v4; // ecx
  void **m_pAllocSlot; // eax
  int *v6; // eax
  int *p_m_pAllocBlock; // esi
  int v8; // ecx
  char *m_pEffect; // [esp-0x8] [ebp-0x20]

  if ( this->m_nEffectCount )
  {
    v2 = *(_DWORD *)this->m_pAllocPos;
    (*(void ( **)(int))(*(_DWORD *)v2 + 16))(v2);
    if ( !*(_DWORD *)(v2 + 8) && !*(_BYTE *)(v2 + 20) )
    {
      v3 = this->m_pAllocPos + 4;
      v4 = this->m_nEffectCount - 1;
      this->m_pAllocPos = v3;
      this->m_nEffectCount = v4;
      if ( !v4 || v3 == this->m_pAllocBlockEnd )
      {
        m_pAllocSlot = (void **)this->m_pAllocSlot;
        this->m_pAllocSlot = (int)(m_pAllocSlot + 1);
        operator delete(*m_pAllocSlot);
        if ( this->m_nEffectCount )
        {
          v6 = (int *)this->m_pAllocSlot;
          p_m_pAllocBlock = &this->m_pAllocBlock;
          v8 = *v6;
          *p_m_pAllocBlock = *v6;
          p_m_pAllocBlock[1] = v8 + 4096;
          p_m_pAllocBlock[2] = v8;
          p_m_pAllocBlock[3] = (int)v6;
        }
        else
        {
          this->m_pAllocBlock = 0;
          this->m_pAllocBlockEnd = 0;
          this->m_pAllocPos = 0;
          this->m_pAllocSlot = 0;
          this->m_pAllocRest = 0;
          m_pEffect = this->m_pEffect;
          this->m_nAllocFlag1 = 0;
          this->m_nAllocFlag2 = 0;
          this->m_fAllocFactor = 0;
          operator delete(m_pEffect);
        }
      }
    }
  }
}

// 0x004BE590
ScreenEffect * ScreenEffectMgr::GetInstance()
{
  if ( (*(_BYTE *)(&g_PAL3.m_snaph_2 + 74) & 1) == 0 )
  {
    *((_BYTE *)&g_PAL3.m_snaph_2 + 296) |= 1u;
    atexit(unknown_libname_430);
  }
  return (ScreenEffect *)(&g_PAL3.m_snaph_2 + 36);
}

// 0x004BE5E0
bool ScreenEffectMgr::IsFadeWhiteHolding()
{
  return this->m_nEffectCount != 0;
}

// 0x004BE5F0
int ScreenEffectMgr::DrainQueue()
{
  int result; // eax
  int v3; // edx
  int v4; // ecx
  void **m_pAllocSlot; // eax
  int *v6; // eax
  int v7; // ecx
  char *m_pEffect; // [esp-0xC] [ebp-0x10]

  for ( result = this->m_nEffectCount; result; result = this->m_nEffectCount )
  {
    v3 = this->m_pAllocPos + 4;
    v4 = this->m_nEffectCount - 1;
    this->m_pAllocPos = v3;
    this->m_nEffectCount = v4;
    if ( !v4 || v3 == this->m_pAllocBlockEnd )
    {
      m_pAllocSlot = (void **)this->m_pAllocSlot;
      this->m_pAllocSlot = (int)(m_pAllocSlot + 1);
      operator delete(*m_pAllocSlot);
      if ( this->m_nEffectCount )
      {
        v6 = (int *)this->m_pAllocSlot;
        v7 = *v6;
        this->m_pAllocBlock = *v6;
        this->m_pAllocBlockEnd = v7 + 4096;
        this->m_pAllocPos = v7;
        this->m_pAllocSlot = (int)v6;
      }
      else
      {
        this->m_pAllocBlock = 0;
        this->m_pAllocBlockEnd = 0;
        this->m_pAllocPos = 0;
        this->m_pAllocSlot = 0;
        this->m_pAllocRest = 0;
        m_pEffect = this->m_pEffect;
        this->m_nAllocFlag1 = 0;
        this->m_nAllocFlag2 = 0;
        this->m_fAllocFactor = 0;
        operator delete(m_pEffect);
      }
    }
  }
  return result;
}

// 0x004BE6B0
char * ScreenEffectMgr::AllocEffectBlock()
{
  char *v2; // ebx
  gbImage2D *v3; // eax
  char *v4; // edi
  char *result; // eax
  ScreenFadeIn *v6; // ebx
  float *v7; // esi
  int v8; // ecx
  char *vftable; // eax
  _DWORD *v10; // eax
  float *v11; // esi
  int v12; // ecx
  int v13; // ebp
  size_t v14; // eax
  gbImage2D *v15; // eax
  char *m_life; // ecx
  int *v17; // edi
  char *v18; // eax
  int *v19; // edx
  int v20; // ebp
  ScreenFadeIn *p_m_fadeIn; // ebp
  float *p_m_age; // esi
  int v23; // edx
  int v24; // ecx
  int v25; // [esp+0xC] [ebp-0x18]
  gbImage2D *v26; // [esp+0x10] [ebp-0x14]
  int m_nType; // [esp+0x1C] [ebp-0x8]

  v2 = (char *)operator new(0x1000u);
  if ( this->m_fadeOut.m_life )
  {
// [VFTABLE] vftable = (char *)this->m_fadeOut.__vftable;
    if ( vftable >= (char *)this->m_fadeOut.m_needscriptdel + 4 * this->m_fadeOut.m_nType - 4 )
    {
      v13 = ((int)&vftable[-this->m_fadeIn.m_life] >> 2) + 1;
      v25 = v13;
      v14 = 8 * v13;
      if ( (v13 & 0x10000000) != 0 )
        v14 = 0;
      v15 = (gbImage2D *)operator new(v14);
      m_life = (char *)this->m_fadeIn.m_life;
      v26 = v15;
      v17 = &v15->ImgInfo.isdiskinfo + ((unsigned int)(2 * v13) >> 2);
// [VFTABLE] v18 = (char *)this->m_fadeOut.__vftable + 4;
      v19 = v17;
      if ( m_life != v18 )
      {
        do
        {
          v20 = *(_DWORD *)m_life;
          m_life += 4;
          *v19++ = v20;
        }
        while ( m_life != v18 );
        v13 = v25;
      }
      operator delete(this->m_fadeOut.m_needscriptdel);
      this->m_fadeOut.m_needscriptdel = v26;
      this->m_fadeOut.m_nType = 2 * v13;
      result = (char *)&v17[v13];
      *(_DWORD *)result = v2;
      m_nType = this->m_fadeIn.m_nType;
      p_m_fadeIn = &this->m_fadeIn;
      p_m_age = &this->m_fadeIn.m_age;
      v23 = *v17 + 4096;
// [VFTABLE] p_m_fadeIn->__vftable = (void *)*v17;
      p_m_fadeIn->m_needscriptdel = (gbImage2D *)v23;
      p_m_fadeIn->m_nType = m_nType;
      p_m_fadeIn->m_life = (int)v17;
      v24 = *(_DWORD *)result;
      *p_m_age = *(float *)result;
      *((_DWORD *)p_m_age + 1) = v24 + 4096;
      *((_DWORD *)p_m_age + 2) = v2;
      *((_DWORD *)p_m_age + 3) = result;
    }
    else
    {
      v10 = vftable + 4;
// [VFTABLE] this->m_fadeOut.__vftable = v10;
      v11 = &this->m_fadeIn.m_age;
      *v10 = v2;
      result = (char *)*((_DWORD *)v11 + 3);
      v12 = *(_DWORD *)result;
      *v11 = *(float *)result;
      *((_DWORD *)v11 + 1) = v12 + 4096;
      *((_DWORD *)v11 + 2) = v2;
      *((_DWORD *)v11 + 3) = result;
    }
  }
  else
  {
    this->m_fadeOut.m_nType = 2;
    v3 = (gbImage2D *)operator new(8u);
    this->m_fadeOut.m_needscriptdel = v3;
    v3->ImgInfo.goal = (int)v2;
    v4 = v2 + 2048;
    result = (char *)&this->m_fadeOut.m_needscriptdel->ImgInfo.goal;
    v6 = &this->m_fadeIn;
    v7 = &this->m_fadeIn.m_age;
    v8 = *(_DWORD *)result;
    *v7 = *(float *)result;
// [VFTABLE] v6->__vftable = (void *)v8;
    *((_DWORD *)v7 + 1) = v8 + 4096;
    v6->m_needscriptdel = (gbImage2D *)(v8 + 4096);
    *((_DWORD *)v7 + 2) = v4;
    v6->m_nType = (int)v4;
    *((_DWORD *)v7 + 3) = result;
    v6->m_life = (int)result;
  }
  return result;
}

// 0x004BE810
int * ScreenEffectMgr::GetFadeFlags()
{
  size_t v2; // eax
  int *result; // eax

  v2 = 4 * this->m_fadeOut.m_nType;
  if ( (this->m_fadeOut.m_nType & 0x20000000) != 0 )
    v2 = 0;
  result = (int *)operator new(v2);
  this->m_fadeOut.m_needscriptdel = (gbImage2D *)result;
  return result;
}

// 0x004BE920
void ScreenEffectMgr::RenderFadeOut()
{
  _BYTE v1[4]; // [esp+0xC] [ebp-0x10] BYREF
  int v2; // [esp+0x18] [ebp-0x4]

  PushMatrixStacks(v1);
  v2 = 0;
  crt_sub_00540070();
  v2 = -1;
  PopMatrixStacks(v1);
}

// 0x004BE9C0
void ScreenEffectMgr::ToggleFade(float fVal)
{
  if ( *(_DWORD *)&this->m_fadeIn.m_hold )
    *(_DWORD *)&this->m_fadeIn.m_hold = 0;
  else
    sub_4BDF30(fVal);
}

// 0x004BE9E0
void ScreenEffectMgr::StartFadeIn()
{
  *(_DWORD *)&this->m_fadeIn.m_hold = 1;

}

// 0x004BEAB0
void ScreenEffectMgr::RenderFadeIn()
{
  _BYTE v1[4]; // [esp+0xC] [ebp-0x10] BYREF
  int v2; // [esp+0x18] [ebp-0x4]

  PushMatrixStacks(v1);
  v2 = 0;
  crt_sub_00540070();
  v2 = -1;
  PopMatrixStacks(v1);
}

// 0x004BEC00
void ScreenEffectMgr::RenderFadeWhiteOut()
{
  gbDynVertBuf *DynVertBuf; // eax
  unsigned int v2; // [esp+0x0] [ebp-0x2C]
  struct gbUIQuad v3; // [esp+0x4] [ebp-0x28] BYREF

  LOBYTE(v2) = (__int64)(*(float *)&this->m_fadeIn.m_life / *(float *)&this->m_fadeIn.m_nType * 255.0);
  BYTE1(v2) = v2;
  BYTE2(v2) = v2;
  v3.ex = (float)g_DrvInfo.width;
  HIBYTE(v2) = -1;
  v3.z = 0.0;
  v3.color = v2;
  v3.sy = (float)g_DrvInfo.height;
  v3.sx = 0.0;
  v3.ey = 0.0;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v3, 1, g_pRenderEffect_1895064, 0);
}

// 0x004BED50
void ScreenEffectMgr::RenderFadeWhiteIn()
{
  gbDynVertBuf *DynVertBuf; // eax
  unsigned int v2; // [esp+0x0] [ebp-0x2C]
  struct gbUIQuad v3; // [esp+0x4] [ebp-0x28] BYREF

  LOBYTE(v2) = (__int64)((1.0 - *(float *)&this->m_fadeIn.m_life / *(float *)&this->m_fadeIn.m_nType) * 255.0);
  BYTE1(v2) = v2;
  BYTE2(v2) = v2;
  v3.ex = (float)g_DrvInfo.width;
  HIBYTE(v2) = -1;
  v3.z = 0.0;
  v3.color = v2;
  v3.sy = (float)g_DrvInfo.height;
  v3.sx = 0.0;
  v3.ey = 0.0;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v3, 1, g_pRenderEffect_1895064, 0);
}

// 0x004BEE60
ScreenEffectMgr::ScreenEffectMgr()
{
  char *v2; // esi
  int v3; // ebx
  char *v4; // esi
  int v5; // ebx
  char *v6; // esi
  int v7; // ebx

  *((_DWORD *)this + 41) = 0;
  v2 = (char *)this + 176;
  v3 = 6;
  do
  {
    v2 += 68;
    --v3;
  }
  while ( v3 );
  v4 = (char *)this + 584;
  v5 = 6;
  do
  {
    v4 += 68;
    --v5;
  }
  while ( v5 );
  v6 = (char *)this + 992;
  v7 = 4;
  do
  {
    v6 += 12;
    --v7;
  }
  while ( v7 );
  ((ParticleEffect *)((char *)this + 1108))->Reset();
  *((_DWORD *)this + 42) = 0;
  this;
}

// 0x004BEFB0
gbVFileSystem * ScreenEffectMgr::LoadResources(int nVal)
{
  char *v3; // eax
  int v4; // ecx
  gbTexture *v5; // eax
  gbTexture *v6; // eax
  gbVFileSystem *result; // eax
  OpenBaseFile v8; // [esp+0x18] [ebp-0x10] BYREF
  int v9; // [esp+0x24] [ebp-0x4]

  ((RenderTarget3 *)41.0)->GenerateRingMesh(28.0, 1112014848, 6, (int)this + 176, 6, 3.0);
  ((RenderTarget3 *)34.0)->GenerateRingMesh(18.0, 1116209152, 6, (int)this + 584, 6, 3.0);
  v3 = (char *)this + 241;
  v4 = 6;
  do
  {
    v3[1] = -11;
    *v3 = -68;
    *(v3 - 1) = 28;
    *(_DWORD *)(v3 - 5) = 1064346583;
    v3[409] = 10;
    v3[408] = 67;
    v3[407] = -29;
    *(_DWORD *)(v3 + 403) = 1064346583;
    v3 += 68;
    --v4;
  }
  while ( v4 );
  *((_DWORD *)this + 248) = -1039138816;
  *((_DWORD *)this + 249) = 0;
  *((_DWORD *)this + 250) = -1039138816;
  *((_DWORD *)this + 251) = -1039138816;
  *((_DWORD *)this + 252) = 0;
  *((_DWORD *)this + 253) = 1108344832;
  *((_DWORD *)this + 254) = 1108344832;
  *((_DWORD *)this + 255) = 0;
  *((_DWORD *)this + 256) = 1108344832;
  *((_DWORD *)this + 257) = 1108344832;
  *((_DWORD *)this + 258) = 0;
  *((_DWORD *)this + 259) = -1039138816;
  *((_DWORD *)this + 261) = 0;
  *((_DWORD *)this + 260) = 0;
  *((_DWORD *)this + 263) = 1065353216;
  *((_DWORD *)this + 262) = 1065353216;
  *((_DWORD *)this + 264) = -1;
  *((_DWORD *)this + 42) = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\Geom_Fx.gbf", 0);
  v9 = 0;
  v5 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, "Effect\\ray.tga");
  *(_DWORD *)&this->m_fadeWhite2.m_hold = v5;
  ((gbTexture *)v5)->LoadTexture(1);
  *((_DWORD *)this + 41) = 1;
  v6 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, "Effect\\trans.tga");
  LODWORD(this->m_fadeWhite2.m_age) = v6;
  ((gbTexture *)v6)->LoadTexture(1);
  this->m_fadeWhite2.m_life = 0;
  v9 = -1;
  return result;
}

// 0x004BF170
void ScreenEffectMgr::CleanupTextures()
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  float m_age; // ecx

  v2 = (gbRefObject *)*((_DWORD *)this + 42);
  if ( v2 )
  {
    ((gbRefObject *)v2)->Release();
    *((_DWORD *)this + 42) = 0;
  }
  v3 = *(gbRefObject **)&this->m_fadeWhite2.m_hold;
  if ( v3 )
  {
    ((gbRefObject *)v3)->Release();
    *(_DWORD *)&this->m_fadeWhite2.m_hold = 0;
  }
  m_age = this->m_fadeWhite2.m_age;
  *((_DWORD *)this + 41) = 0;
  if ( m_age != 0.0 )
  {
    ((gbRefObject *)LODWORD(m_age))->Release();
    this->m_fadeWhite2.m_age = 0.0;
  }
}

// 0x004BF4F0
void ScreenEffectMgr::UpdateAnimation(float fVal)
{
  int v3; // ebx
  bool v4; // zf
  double v5; // st7
  ScreenEffectMgr *v6; // ebp
  float *v7; // esi
  double v8; // st7
  float fAlpha; // [esp+0x0] [ebp-0x14]
  bool v10; // [esp+0xF] [ebp-0x5]
  int v11; // [esp+0x10] [ebp-0x4]

  v3 = 1;
  v4 = this->m_fadeWhite2.m_nType == 1;
  *(float *)&this->m_fadeWhite2.m_life = fVal * 32.0 + *(float *)&this->m_fadeWhite2.m_life;
  if ( v4 )
  {
    v5 = fVal + *((float *)this + 265);
    *((float *)this + 265) = v5;
    if ( v5 >= 4.0 )
    {
      *((_DWORD *)this + 265) = 1082130432;
      *((_DWORD *)this + 273) = 1;
    }
    v11 = 1;
    v10 = *((_DWORD *)this + 273) == 1;
    *((float *)this + 266) = (float)(int)(__int64)((1.0 - cos(*((float *)this + 265) * 0.25 * 3.1415927)) * 0.5 * 60.0);
    v6 = (ScreenEffectMgr *)((char *)this + 1096);
    v7 = (float *)((char *)this + 1068);
    do
    {
      if ( (double)v11 * 0.5 + 0.2 < *(v7 - 2) )
      {
        v8 = fVal + *v7;
        *v7 = v8;
        if ( v8 >= 4.0 )
        {
          *v7 = 4.0;
          v6->m_pVtable = (void *)1;
        }
        v7[1] = (float)(int)(__int64)(*v7 * 0.25 * 60.0);
        if ( !v10 || (v10 = 1, !v6->m_pVtable) )
          v10 = 0;
      }
      ++v3;
      v6 = (ScreenEffectMgr *)((char *)v6 + 4);
      v7 += 2;
      v11 = v3;
    }
    while ( v3 < 4 );
    if ( *((float *)this + 265) < 4.0 )
    {
      fAlpha = 1.0 - *((float *)this + 265) * 0.25;
      ((RoleSystem *)&g_pRoleSystem)->SetBlendMode(fAlpha);
    }
    else
    {
      ((RoleSystem *)&g_pRoleSystem)->SetBlendMode(1.0);
      this->m_fadeWhite2.m_nType = 0;
    }
  }
}

// 0x004BF680
int ScreenEffectMgr::GetPageIndex(int nVal)
{
  int result; // eax

  this->m_fadeWhite2.m_nType = nVal;
  result = nVal - 1;
  if ( nVal == 1 )
  {
    memset((char *)this + 1060, 0, 0x20u);
    *((_DWORD *)this + 273) = 0;
    *((_DWORD *)this + 274) = 0;
    *((_DWORD *)this + 275) = 0;
    *((_DWORD *)this + 276) = 0;
    return 0;
  }
  return result;
}

// 0x004BF6C0
int ScreenEffectMgr::SetFadeParams(int nVal)
{
  ((gbMatrix4 *)nVal)->LoadIdentity();
  *(_DWORD *)(nVal + 68) = 1114636288;
  *(_DWORD *)(nVal + 72) = 1109393408;
  *(_DWORD *)(nVal + 64) = 1109393408;
  return 1109393408;
}

// 0x004BF760
int * ScreenEffectMgr::ResetFadeState()
{
  this->m_fadeIn.m_life = -1;
  LOBYTE(this->m_pVtable) = 0;
  this->m_fadeIn.m_nType = 0;
  this->m_fadeIn.m_needscriptdel = 0;
  this->m_fadeIn.m_age = 0.0;
// [VFTABLE] this->m_fadeIn.__vftable = 0;
  return (int *)this;
}

// 0x0052F310
int ScreenEffectMgr::ProcessInstance()
{
  ScreenEffect *Instance; // eax
  int result; // eax

  Instance = this->GetInstance();
  result = ((ScreenEffectMgr *)Instance)->ProcessEffect();
  LODWORD(this->m_fadeIn.m_age) = result;
  return result;
}

// 0x0052F330
BOOL ScreenEffectMgr::IsFadeActive()
{
  float m_age; // ecx

  m_age = this->m_fadeIn.m_age;
  return m_age != 0.0 && !(*(int ( **)(float))(*(_DWORD *)LODWORD(m_age) + 4))(COERCE_FLOAT(LODWORD(m_age)));
}

// 0x005420D8
// attributes: thunk
void ScreenEffectMgr::sub_5420D8(int a2)
{
  ((gbVisNode *)this)->EnableShadow(a2);
}

// 0x005420DE
// attributes: thunk
int ScreenEffectMgr::sub_5420DE(gbAABBox *a2)
{
  return ((gbVisNode *)this)->GetAABBox(a2);
}

// 0x0054210E
// attributes: thunk
void ScreenEffectMgr::sub_54210E(gbSphere *a2)
{
  ((gbVisNode *)this)->GetBoundSphere(a2);
}
