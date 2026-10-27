#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/ScreenEffectMgr.h"
#include "Scene/CameraCtrl.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "GameBase/PAL3.h"
#include "Render/RenderTarget3.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Effect/ScreenEffect.h"
#include "Misc/ScreenFadeIn.h"
#include "Misc/ScreenFadeOut.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x004BDF60
int ScreenEffectMgr::IsScriptDelNeeded()
{
  return (int)this->m_fadeIn.m_needscriptdel;
}

// 0x004BDF70
void ScreenEffectMgr::StartFade()
{
  this->m_fadeIn.m_needscriptdel = ((gbImage2D *)((gbImage2D *)1));
  this->m_fadeIn.m_life = 0;
}

// 0x004BE080
void ScreenEffectMgr::ClearAllEffects()
{
  int i; // eax
  char *v3; // edi
  int v4; // eax
  void **m_pAllocSlot; // eax
  void **v6; // eax
  char *v7; // ecx
  char *m_pEffect; // [esp-0xC] [ebp-0x20]

  for ( i = this->m_nEffectCount; i; i = this->m_nEffectCount )
  {
    v3 = (char *)this->m_pAllocPos + 4;
    v4 = i - 1;
    this->m_pAllocPos = ((void *)((void *)v3));
    this->m_nEffectCount = v4;
    if ( !v4 || v3 == this->m_pAllocBlockEnd )
    {
      m_pAllocSlot = (void **)this->m_pAllocSlot;
      this->m_pAllocSlot = ((void *)(m_pAllocSlot + 1));
      operator delete(*m_pAllocSlot);
      if ( this->m_nEffectCount )
      {
        v6 = (void **)this->m_pAllocSlot;
        v7 = (char *)*v6;
        this->m_pAllocBlock = ((void *)(*v6));
        this->m_pAllocBlockEnd = ((void *)((char *)v7 + 4096));
        this->m_pAllocPos = ((void *)((void *)v7));
        this->m_pAllocSlot = ((void *)(v6));
      }
      else
      {
        this->m_pAllocBlock = ((void *)0);
        this->m_pAllocBlockEnd = ((void *)0);
        this->m_pAllocPos = ((void *)0);
        this->m_pAllocSlot = ((void *)0);
        this->m_pAllocRest = ((void *)0);
        m_pEffect = (char *)this->m_pEffect;
        this->m_nAllocFlag1 = 0;
        this->m_nAllocFlag2 = 0;
        this->m_fAllocFactor = 0;
        operator delete(m_pEffect);
      }
    }
  }
  (((CameraCtrl *)&this->m_fadeWhite2))->CameraCtrl::RenderFadeEffectB();
  (((CameraCtrl *)&this->m_fadeWhite))->CameraCtrl::RenderFadeEffect();
  (((CameraCtrl *)&this->m_fadeOut))->CameraCtrl::OnIdleB();
  (((CameraCtrl *)&this->m_fadeIn))->CameraCtrl::OnIdle();
}

// 0x004BE1A0
int ScreenEffectMgr::ProcessEffect(int nVal1)
{
  void *p_m_fadeOut; // ebp
  int v4; // eax
  char *v5; // edx
  int v6; // ecx
  void **v7; // eax
  void **v8; // eax
  char *v9; // ecx
  int m_nEffectCount; // eax
  char *m_activeQueue; // esi
  _DWORD *v12; // eax
  _DWORD *v13; // edx
  int *v15; // edi
  void *v16; // eax
  int v17; // edx
  void *v18; // ecx
  void *v19; // edi
  unsigned int v20; // eax
  int **v21; // eax
  void *v22; // eax
  int v23; // edx
  void *v24; // eax
  int v25; // ebx
  void *v26; // edx
  int v27; // ecx
  void *v28; // edx
  void *v29; // edx
  int v30; // ecx
  void *v31; // edx
  char *m_pEffect; // [esp-0xC] [ebp-0x24]
  void *m_pAllocBlock; // [esp+0x8] [ebp-0x10] BYREF
  void *m_pAllocBlockEnd; // [esp+0xC] [ebp-0xC]
  int v35; // [esp+0x10] [ebp-0x8]
  void *m_pAllocSlot; // [esp+0x14] [ebp-0x4]

  p_m_fadeOut = 0;
  switch ( nVal1 )
  {
    case 1:
      p_m_fadeOut = (void *)&this->m_fadeOut;
      goto LABEL_6;
    case 2:
      p_m_fadeOut = (void *)&this->m_fadeIn;
      goto LABEL_6;
    case 3:
      p_m_fadeOut = (void *)&this->m_fadeWhite;
      goto LABEL_6;
    case 4:
      p_m_fadeOut = (void *)&this->m_fadeWhite2;
LABEL_6:
      if ( !p_m_fadeOut )
        return (int)p_m_fadeOut;
      (*(void ( **)(void *))(*(_DWORD *)p_m_fadeOut + 12))(p_m_fadeOut);
      if ( this->m_nEffectCount )
      {
        m_pAllocBlock = (void *)this->m_pAllocBlock;
        m_pAllocBlockEnd = (void *)this->m_pAllocBlockEnd;
        v4 = *(_DWORD *)this->m_pAllocPos;
        m_pAllocSlot = (void *)this->m_pAllocSlot;
        if ( *(_BYTE *)(v4 + 20) )
        {
          if ( !*(_DWORD *)(v4 + 8) )
          {
            v5 = (char *)this->m_pAllocPos + 4;
            v6 = this->m_nEffectCount - 1;
            this->m_pAllocPos = ((void *)((void *)v5));
            this->m_nEffectCount = v6;
            if ( !v6 || v5 == this->m_pAllocBlockEnd )
            {
              v7 = (void **)this->m_pAllocSlot;
              this->m_pAllocSlot = ((void *)(v7 + 1));
              operator delete(*v7);
              if ( this->m_nEffectCount )
              {
                v8 = (void **)this->m_pAllocSlot;
                v9 = (char *)*v8;
                this->m_pAllocBlock = ((void *)(*v8));
                this->m_pAllocBlockEnd = ((void *)((char *)v9 + 4096));
                this->m_pAllocPos = ((void *)((void *)v9));
                this->m_pAllocSlot = ((void *)(v8));
              }
              else
              {
                this->m_pAllocBlock = ((void *)0);
                this->m_pAllocBlockEnd = ((void *)0);
                this->m_pAllocPos = ((void *)0);
                this->m_pAllocSlot = ((void *)0);
                this->m_pAllocRest = ((void *)0);
                this->m_nAllocFlag1 = 0;
                m_pEffect = (char *)this->m_pEffect;
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
        || (v12 = (_DWORD *)*((_DWORD *)m_activeQueue + 7), v13 = (_DWORD *)*((_DWORD *)m_activeQueue + 6), v12 == v13) )
      {
        v15 = (int *)operator new(0x1000u);
        if ( *((_DWORD *)m_activeQueue + 11) )
        {
          v20 = *((_DWORD *)m_activeQueue + 8);
          if ( v20 >= *((_DWORD *)m_activeQueue + 9) + 4 * *((_DWORD *)m_activeQueue + 10) - 4 )
          {
            v25 = ((int)(v20 - *((_DWORD *)m_activeQueue + 4)) >> 2) + 1;
            *(_DWORD *)&(((RoleSystem *)m_activeQueue))->RoleSystem::GetRoleName(2 * v25)[4 * v25] = (_DWORD)v15;
            (((ScreenEffect *)&m_pAllocBlock))->ScreenEffect::CopyParams(*((int **)m_activeQueue + 3));
            v26 = (void *)m_pAllocBlockEnd;
            *((_DWORD *)m_activeQueue + 1) = (unsigned long)m_pAllocBlock;
            v27 = v35;
            *((_DWORD *)m_activeQueue + 2) = (unsigned long)v26;
            v28 = (void *)m_pAllocSlot;
            *((_DWORD *)m_activeQueue + 3) = v27;
            *((_DWORD *)m_activeQueue + 4) = (unsigned long)v28;
            (((ScreenEffect *)&m_pAllocBlock))->ScreenEffect::CopyParams(v15);
            v29 = (void *)m_pAllocBlockEnd;
            *((_DWORD *)m_activeQueue + 5) = (unsigned long)m_pAllocBlock;
            v30 = v35;
            *((_DWORD *)m_activeQueue + 6) = (unsigned long)v29;
            v31 = (void *)m_pAllocSlot;
            *((_DWORD *)m_activeQueue + 7) = v30;
            *((_DWORD *)m_activeQueue + 8) = (unsigned long)v31;
          }
          else
          {
            v21 = (int **)(v20 + 4);
            *((_DWORD *)m_activeQueue + 8) = (unsigned long)v21;
            *v21 = v15;
            (((ScreenEffect *)&m_pAllocBlock))->ScreenEffect::CopyParams(v15);
            v22 = (void *)m_pAllocBlockEnd;
            *((_DWORD *)m_activeQueue + 5) = (unsigned long)m_pAllocBlock;
            v23 = v35;
            *((_DWORD *)m_activeQueue + 6) = (unsigned long)v22;
            v24 = (void *)m_pAllocSlot;
            *((_DWORD *)m_activeQueue + 7) = v23;
            *((_DWORD *)m_activeQueue + 8) = (unsigned long)v24;
          }
        }
        else
        {
          *((_DWORD *)m_activeQueue + 10) = 2;
          (((ScreenEffectMgr *)m_activeQueue))->ScreenEffectMgr::GetFadeFlags();
          *(_DWORD *)(*((_DWORD *)m_activeQueue + 9) + 4) = (_DWORD)v15;
          (((ScreenEffect *)&m_pAllocBlock))->ScreenEffect::CopyParams(v15 + 512);
          v16 = (void *)m_pAllocBlock;
          v17 = v35;
          v18 = (void *)m_pAllocBlockEnd;
          v19 = (void *)m_pAllocSlot;
          *((_DWORD *)m_activeQueue + 1) = (unsigned long)m_pAllocBlock;
          *((_DWORD *)m_activeQueue + 2) = (unsigned long)v18;
          *((_DWORD *)m_activeQueue + 3) = v17;
          *((_DWORD *)m_activeQueue + 4) = (unsigned long)v19;
          *((_DWORD *)m_activeQueue + 5) = (unsigned long)v16;
          *((_DWORD *)m_activeQueue + 6) = (unsigned long)v18;
          *((_DWORD *)m_activeQueue + 7) = v17;
          *((_DWORD *)m_activeQueue + 8) = (unsigned long)v19;
        }
        v12 = (_DWORD *)*((_DWORD *)m_activeQueue + 7);
        *((_DWORD *)m_activeQueue + 7) = (unsigned long)(v12 + 1);
        if ( v12 )
LABEL_29:
          *v12 = (_DWORD)p_m_fadeOut;
      }
      else
      {
        *((_DWORD *)m_activeQueue + 7) = (unsigned long)(v12 + 1);
        if ( v12 + 1 == v13 )
        {
          if ( v12 )
            *v12 = (_DWORD)p_m_fadeOut;
          (((ScreenEffectMgr *)m_activeQueue))->ScreenEffectMgr::AllocEffectBlock();
          ++*((_DWORD *)m_activeQueue + 11);
          return (int)p_m_fadeOut;
        }
        if ( v12 )
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
  char *v3; // edx
  int v4; // ecx
  void **m_pAllocSlot; // eax
  void **v6; // eax
  void **p_m_pAllocBlock; // esi
  char *v8; // ecx
  char *m_pEffect; // [esp-0x8] [ebp-0x20]

  if ( this->m_nEffectCount )
  {
    v2 = *(_DWORD *)this->m_pAllocPos;
    (*(void ( **)(int))(*(_DWORD *)v2 + 16))(v2);
    if ( !*(_DWORD *)(v2 + 8) && !*(_BYTE *)(v2 + 20) )
    {
      v3 = (char *)this->m_pAllocPos + 4;
      v4 = this->m_nEffectCount - 1;
      this->m_pAllocPos = ((void *)((void *)v3));
      this->m_nEffectCount = v4;
      if ( !v4 || v3 == this->m_pAllocBlockEnd )
      {
        m_pAllocSlot = (void **)this->m_pAllocSlot;
        this->m_pAllocSlot = ((void *)(m_pAllocSlot + 1));
        operator delete(*m_pAllocSlot);
        if ( this->m_nEffectCount )
        {
          v6 = (void **)this->m_pAllocSlot;
          p_m_pAllocBlock = (void **)&this->m_pAllocBlock;
          v8 = (char *)*v6;
          *p_m_pAllocBlock = *v6;
          p_m_pAllocBlock[1] = v8 + 4096;
          p_m_pAllocBlock[2] = v8;
          p_m_pAllocBlock[3] = v6;
        }
        else
        {
          this->m_pAllocBlock = ((void *)0);
          this->m_pAllocBlockEnd = ((void *)0);
          this->m_pAllocPos = ((void *)0);
          this->m_pAllocSlot = ((void *)0);
          this->m_pAllocRest = ((void *)0);
          m_pEffect = (char *)this->m_pEffect;
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
  if ( (*(_BYTE *)(&g_PAL3.m_gametime + 70) & 1) == 0 )
  {
    *((_BYTE *)&g_PAL3.m_gametime + 560) |= 1u;
    ((ScreenEffect *)&g_PAL3.m_gametime + 17)->ScreenEffect::ScreenEffect();
    atexit(InitScreenEffectSingleton);
  }
  return (ScreenEffect *)(&g_PAL3.m_gametime + 51);
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
  char *v3; // edx
  int v4; // ecx
  void **m_pAllocSlot; // eax
  void **v6; // eax
  char *v7; // ecx
  char *m_pEffect; // [esp-0xC] [ebp-0x10]

  for ( result = this->m_nEffectCount; result; result = this->m_nEffectCount )
  {
    v3 = (char *)this->m_pAllocPos + 4;
    v4 = this->m_nEffectCount - 1;
    this->m_pAllocPos = ((void *)((void *)v3));
    this->m_nEffectCount = v4;
    if ( !v4 || v3 == this->m_pAllocBlockEnd )
    {
      m_pAllocSlot = (void **)this->m_pAllocSlot;
      this->m_pAllocSlot = ((void *)(m_pAllocSlot + 1));
      operator delete(*m_pAllocSlot);
      if ( this->m_nEffectCount )
      {
        v6 = (void **)this->m_pAllocSlot;
        v7 = (char *)*v6;
        this->m_pAllocBlock = ((void *)(*v6));
        this->m_pAllocBlockEnd = ((void *)((char *)v7 + 4096));
        this->m_pAllocPos = ((void *)((void *)v7));
        this->m_pAllocSlot = ((void *)(v6));
      }
      else
      {
        this->m_pAllocBlock = ((void *)0);
        this->m_pAllocBlockEnd = ((void *)0);
        this->m_pAllocPos = ((void *)0);
        this->m_pAllocSlot = ((void *)0);
        this->m_pAllocRest = ((void *)0);
        m_pEffect = (char *)this->m_pEffect;
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
  float v8; // ecx
  char *m_nTodo_000; // eax
  _DWORD *v10; // eax
  float *v11; // esi
  float v12; // ecx
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
  float v24; // ecx
  int v25; // [esp+0xC] [ebp-0x18]
  gbImage2D *v26; // [esp+0x10] [ebp-0x14]
  int m_nType; // [esp+0x1C] [ebp-0x8]

  v2 = (char *)operator new(0x1000u);
  if ( this->m_fadeOut.m_life )
  {
    m_nTodo_000 = (char *)this->m_fadeOut.m_nTodo_000;
    if ( m_nTodo_000 >= (char *)this->m_fadeOut.m_needscriptdel + 4 * this->m_fadeOut.m_nType - 4 )
    {
      v13 = ((int)&m_nTodo_000[-this->m_fadeIn.m_life] >> 2) + 1;
      v25 = v13;
      v14 = 8 * v13;
      if ( (v13 & 0x10000000) != 0 )
        v14 = 0;
      v15 = (gbImage2D *)operator new(v14);
      m_life = (char *)this->m_fadeIn.m_life;
      v26 = (gbImage2D *)v15;
      v17 = (int *)(&v15->ImgInfo.isdiskinfo + ((unsigned int)(2 * v13) >> 2));
      v18 = (char *)this->m_fadeOut.m_nTodo_000 + 4;
      v19 = (int *)v17;
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
      this->m_fadeOut.m_needscriptdel = ((gbImage2D *)(v26));
      this->m_fadeOut.m_nType = 2 * v13;
      result = (char *)&v17[v13];
      *(_DWORD *)result = (_DWORD)v2;
      m_nType = this->m_fadeIn.m_nType;
      p_m_fadeIn = (ScreenFadeIn *)&this->m_fadeIn;
      p_m_age = (float *)&this->m_fadeIn.m_age;
      v23 = (unsigned long)(*v17 + 4096);
      p_m_fadeIn->m_nTodo_000 = (void *)*v17;
      p_m_fadeIn->m_needscriptdel = (gbImage2D *)v23;
      p_m_fadeIn->m_nType = m_nType;
      p_m_fadeIn->m_life = (int)v17;
      v24 = *(float *)result;
      *p_m_age = *(float *)result;
      *((_DWORD *)p_m_age + 1) = LODWORD(v24) + 4096;
      *((_DWORD *)p_m_age + 2) = (unsigned long)v2;
      *((_DWORD *)p_m_age + 3) = (unsigned long)result;
    }
    else
    {
      v10 = (_DWORD *)m_nTodo_000 + 4;
      this->m_fadeOut.m_nTodo_000 = ((void *)(v10));
      v11 = (float *)&this->m_fadeIn.m_age;
      *v10 = (_DWORD)v2;
      result = (char *)*((_DWORD *)v11 + 3);
      v12 = *(float *)result;
      *v11 = *(float *)result;
      *((_DWORD *)v11 + 1) = LODWORD(v12) + 4096;
      *((_DWORD *)v11 + 2) = (unsigned long)v2;
      *((_DWORD *)v11 + 3) = (unsigned long)result;
    }
  }
  else
  {
    this->m_fadeOut.m_nType = 2;
    v3 = (gbImage2D *)operator new(8u);
    this->m_fadeOut.m_needscriptdel = ((gbImage2D *)(v3));
    v3->ImgInfo.goal = (int)v2;
    v4 = (char *)(v2 + 2048);
    result = (char *)&this->m_fadeOut.m_needscriptdel->ImgInfo.goal;
    v6 = (ScreenFadeIn *)&this->m_fadeIn;
    v7 = (float *)&this->m_fadeIn.m_age;
    v8 = *(float *)result;
    *v7 = *(float *)result;
    *(float *)&v6->m_nTodo_000 = v8;
    *((_DWORD *)v7 + 1) = LODWORD(v8) + 4096;
    v6->m_needscriptdel = (gbImage2D *)(LODWORD(v8) + 4096);
    *((_DWORD *)v7 + 2) = (unsigned long)v4;
    v6->m_nType = (int)v4;
    *((_DWORD *)v7 + 3) = (unsigned long)result;
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
  this->m_fadeOut.m_needscriptdel = ((gbImage2D *)((gbImage2D *)result));
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
    (((ScreenEffectMgr *)fVal))->ScreenEffectMgr::_todo_4BDF30();
}

// 0x004BE9E0
void ScreenEffectMgr::StartFadeIn()
{
  *(_DWORD *)&this->m_fadeIn.m_hold = 1;
  this->ScreenEffectMgr::StartFade();
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
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x114u);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad(&v3, 1, g_pRenderEffect_1895064, 0);
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
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x114u);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad(&v3, 1, g_pRenderEffect_1895064, 0);
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

  RenderTarget3::GenerateRingMesh(41.0, 28.0, 1112014848, 6, (int)&this[1].m_fadeIn.m_hold, 6, 3.0);
  RenderTarget3::GenerateRingMesh(34.0, 18.0, 1116209152, 6, (int)&this[3].m_nAllocFlag1, 6, 3.0);
  v3 = (char *)&this[1].m_fadeWhite2.m_nType + 1;
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
  this[6].m_fadeWhite2.m_nTodo_000 = (void *)-1039138816;
  this[6].m_fadeWhite2.m_needscriptdel = ((gbImage2D *)0);
  this[6].m_fadeWhite2.m_nType = -1039138816;
  this[6].m_fadeWhite2.m_life = -1039138816;
  this[6].m_fadeWhite2.m_age = 0.0;
  *(_DWORD *)&this[6].m_fadeWhite2.m_hold = 1108344832;
  *(_DWORD *)this[6].m_activeQueue = 1108344832;
  this[6].m_pAllocBlock = ((void *)0);
  this[6].m_pAllocBlockEnd = (void *)1108344832;
  this[6].m_pAllocPos = (void *)1108344832;
  this[6].m_pAllocSlot = ((void *)0);
  this[6].m_pAllocRest = (void *)-1039138816;
  this[6].m_nAllocFlag2 = 0;
  this[6].m_nAllocFlag1 = 0;
  this[6].m_pEffect = (char *)1065353216;
  this[6].m_fAllocFactor = 1065353216;
  *((_DWORD *)&this[6].m_pEffect + 1) = -1;
  this[1].m_fadeIn.m_life = (int)(((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewRenderEffect("gfxscript\\Geom_Fx.gbf", 0);
  v9 = 0;
  v5 = (gbTexture *)gfxMgr->NewTexture("Effect\\ray.tga");
  *(_DWORD *)&this->m_fadeWhite2.m_hold = (_DWORD)v5;
  (((gbTexture *)v5))->gbTexture::LoadTexture(1);
  this[1].m_fadeIn.m_nType = 1;
  v6 = (gbTexture *)gfxMgr->NewTexture("Effect\\trans.tga");
  LODWORD(this->m_fadeWhite2.m_age) = (unsigned long)v6;
  (((gbTexture *)v6))->gbTexture::LoadTexture(1);
  this->m_fadeWhite2.m_life = 0;
  v9 = -1;
  ((OpenNULLFile *)&v8)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x004BF170
void ScreenEffectMgr::CleanupTextures()
{
  gbRefObject *m_life; // ecx
  gbRefObject *v3; // ecx
  float m_age; // ecx

  m_life = (gbRefObject *)this[1].m_fadeIn.m_life;
  if ( m_life )
  {
    (((gbRefObject *)m_life))->gbRefObject::Release();
    this[1].m_fadeIn.m_life = 0;
  }
  v3 = (gbRefObject *)(*(gbRefObject **)&this->m_fadeWhite2.m_hold);
  if ( v3 )
  {
    (((gbRefObject *)v3))->gbRefObject::Release();
    *(_DWORD *)&this->m_fadeWhite2.m_hold = 0;
  }
  m_age = this->m_fadeWhite2.m_age;
  this[1].m_fadeIn.m_nType = 0;
  if ( m_age != 0.0f )
  {
    (((gbRefObject *)LODWORD(m_age)))->gbRefObject::Release();
    this->m_fadeWhite2.m_age = 0.0;
  }
}

// 0x004BF4F0
void ScreenEffectMgr::UpdateAnimation(float fVal)
{
  int v3; // ebx
  bool v4; // zf
  double v5; // st7
  ScreenFadeOut *p_m_fadeOut; // ebp
  float *p_m_fadeIn; // esi
  double v8; // st7
  float fAlpha; // [esp+0x0] [ebp-0x14]
  bool v10; // [esp+0xF] [ebp-0x5]
  int v11; // [esp+0x10] [ebp-0x4]

  v3 = 1;
  v4 = this->m_fadeWhite2.m_nType == 1;
  *(float *)&this->m_fadeWhite2.m_life = fVal * 32.0 + *(float *)&this->m_fadeWhite2.m_life;
  if ( v4 )
  {
    v5 = fVal + *(float *)&this[6].m_nEffectCount;
    *(float *)&this[6].m_nEffectCount = v5;
    if ( v5 >= 4.0 )
    {
      this[6].m_nEffectCount = 1082130432;
      this[7].m_fadeIn.m_first = 1;
    }
    v11 = 1;
    v10 = this[7].m_fadeIn.m_first == 1;
    *(float *)&this[7].m_pVtable = (float)(int)(__int64)((1.0 - cos(*(float *)&this[6].m_nEffectCount * 0.25 * 3.1415927))
                                                       * 0.5
                                                       * 60.0);
    p_m_fadeOut = (ScreenFadeOut *)&this[7].m_fadeOut;
    p_m_fadeIn = (float *)&this[7].m_fadeIn;
    do
    {
      if ( (double)v11 * 0.5 + 0.2 < *(p_m_fadeIn - 2) )
      {
        v8 = fVal + *p_m_fadeIn;
        *p_m_fadeIn = v8;
        if ( v8 >= 4.0 )
        {
          *p_m_fadeIn = 4.0;
          p_m_fadeOut->m_nTodo_000 = (void *)1;
        }
        p_m_fadeIn[1] = (float)(int)(__int64)(*p_m_fadeIn * 0.25 * 60.0);
        if ( !v10 || (v10 = 1, !p_m_fadeOut->m_nTodo_000) )
          v10 = 0;
      }
      ++v3;
      p_m_fadeOut = (ScreenFadeOut *)((char *)p_m_fadeOut + 4);
      p_m_fadeIn += 2;
      v11 = v3;
    }
    while ( v3 < 4 );
    if ( *(float *)&this[6].m_nEffectCount < 4.0f )
    {
      fAlpha = 1.0f - *(float *)&this[6].m_nEffectCount * 0.25f;
      (((RoleSystem *)&g_pRoleSystem))->RoleSystem::SetBlendMode(fAlpha);
    }
    else
    {
      (((RoleSystem *)&g_pRoleSystem))->RoleSystem::SetBlendMode(1.0);
      this->m_fadeWhite2.m_nType = 0;
    }
  }
}

// 0x004BF680
int ScreenEffectMgr::GetPageIndex(int nType)
{
  int result; // eax

  this->m_fadeWhite2.m_nType = nType;
  result = nType - 1;
  if ( nType == 1 )
  {
    result = 0;
    memset(&this[6].m_nEffectCount, 0, 0x20u);
    this[7].m_fadeIn.m_first = 0;
    this[7].m_fadeOut.m_nTodo_000 = ((void *)0);
    this[7].m_fadeOut.m_needscriptdel = ((gbImage2D *)0);
    this[7].m_fadeOut.m_nType = 0;
  }
  return result;
}

// 0x004BF6C0
int ScreenEffectMgr::SetFadeParams(gbMatrix4 *pMat)
{
  int result; // eax

  (((gbMatrix4 *)pMat))->gbMatrix4::LoadIdentity();
  result = 1109393408;
  pMat[1].xy = 60.0;
  pMat[1].xz = 40.0;
  *(_DWORD *)&pMat[1] = 1109393408;
  return result;
}

// 0x004BF760
int * ScreenEffectMgr::ResetFadeState()
{
  int *result; // eax

  result = (int *)this;
  this->m_fadeIn.m_life = -1;
  LOBYTE(this->m_pVtable) = 0;
  this->m_fadeIn.m_nType = 0;
  this->m_fadeIn.m_needscriptdel = ((gbImage2D *)0);
  this->m_fadeIn.m_age = 0.0;
  this->m_fadeIn.m_nTodo_000 = ((void *)0);
  return result;
}

// 0x0052F310
int ScreenEffectMgr::ProcessInstance()
{
  ScreenEffect *Instance; // eax
  int result; // eax

  Instance = (ScreenEffect *)this->ScreenEffectMgr::GetInstance();
  result = (((ScreenEffectMgr *)Instance))->ScreenEffectMgr::ProcessEffect(1);
  LODWORD(this->m_fadeIn.m_age) = result;
  return result;
}

// 0x0052F330
BOOL ScreenEffectMgr::IsFadeActive()
{
  float m_age; // ecx

  m_age = this->m_fadeIn.m_age;
  return m_age != 0.0f && !(*(int ( **)(float))(*(_DWORD *)LODWORD(m_age) + 4))(_pal3_coerce_f32(LODWORD(m_age)));
}

// 0x005420D8
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void ScreenEffectMgr::EnableShadow(int nEnable)
{
  (((gbVisNode *)this))->gbVisNode::EnableShadow(nEnable);
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x005420DE
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void ScreenEffectMgr::GetAABBox(gbAABBox *pBox)
{
  (((gbVisNode *)this))->gbVisNode::GetAABBox(*pBox);
}
#pragma auto_inline(on)
#pragma inline_depth()
