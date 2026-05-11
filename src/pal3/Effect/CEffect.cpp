#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffect.h"
#include "pal3/gen/CEffExplosive.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/CEffgbParticle.h"

// Forward declarations for unnamed functions
int sub_4CDCA0(...);
int sub_4D4D30(...);
int sub_4D4D70(...);

// Unnamed globals (extern)
extern int dword_1895980;
extern int dword_DE99B0;
extern int dword_EC9E70;
extern int dword_EC9E74;
extern int nullsub_1;
extern int unk_EC9EB4;

// 0x004C6940
CEffect::CEffect()
{
  CEffectSystem *v0; // eax

  v0 = (CEffectSystem *)operator new(0x10C0u);
  if ( v0 )
  v0->FillDefaultUVSet();
  else
  0;
}

// 0x004C6A70
int CEffect::Reset(int a2, float a3, float a4, float a5)
{
  int nQuadIndex_low; // ecx

  this->m_eKind[0] = 0;
  LOBYTE(this->m_Partical[0].fZ) = 0;
  this->m_Partical[2].fSize = a3 + *(float *)(a2 + 184);
  *(float *)&this->m_Partical[2].byAlpha = a4 + *(float *)(a2 + 188);
  *(float *)&this->m_Partical[3].pPic = a5 + *(float *)(a2 + 192);
  this->m_Partical[2].fX = *(float *)(a2 + 216);
  this->m_Partical[2].fY = *(float *)(a2 + 196);
  this->m_Partical[2].fZ = *(float *)(a2 + 220);
  *(_DWORD *)&this->m_Partical[3].byMaxFrame = 0;
  *(_DWORD *)&this->m_Partical[3].bValid = 0;
  this->m_Partical[3].nQuadIndex = 0;
  this->m_Partical[1].nQuadIndex = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(float *)&this->m_Partical[1].bValid = (float)HIBYTE(this->m_Partical[1].nQuadIndex);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(float *)&this->m_Partical[1].byMaxFrame = (float)(unsigned __int8)BYTE2(this->m_Partical[1].nQuadIndex);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_Partical[1].fFramePerSec = (float)(unsigned __int8)BYTE1(this->m_Partical[1].nQuadIndex);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  this->m_Partical[1].pPic = 0;
  nQuadIndex_low = LOBYTE(this->m_Partical[1].nQuadIndex);
  *(_DWORD *)&this->m_Partical[0].byAlpha = 0;
  this->m_Partical[1].fCurFrame = (float)nQuadIndex_low;
  this->m_Partical[1].dwColor = *(_DWORD *)(a2 + 200);
  this->m_Partical[1].fX = *(float *)(a2 + 200);
  return ((CEffExplosive *)this)->CreateGeom();
}

// 0x004C7150
void CEffect::CreateOnePartical(float a2)
{
  CEffect *v2; // edi
  double v3; // st7
  unsigned __int8 *p_m_bActive; // esi
  int v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // esi
  int v13; // edx
  int fY_low; // ecx
  float *v15; // eax
  float *v16; // ebx
  double v17; // st7
  int v18; // edx
  int v19; // eax
  float *v20; // [esp+0h] [ebp-18h]
  float *v21; // [esp+4h] [ebp-14h]
  float v22; // [esp+8h] [ebp-10h]
  int fZ_low; // [esp+Ch] [ebp-Ch]
  float v25; // [esp+Ch] [ebp-Ch]
  int v26; // [esp+10h] [ebp-8h]
  float v27; // [esp+10h] [ebp-8h]
  int v28; // [esp+14h] [ebp-4h]
  float v29; // [esp+14h] [ebp-4h]
  int a2a; // [esp+20h] [ebp+8h]
  int a2b; // [esp+20h] [ebp+8h]

  v2 = this;
  v3 = a2 - *(float *)&this->m_DeltaTime;
  p_m_bActive = (unsigned __int8 *)&this->m_bActive;
  *(float *)&this->m_DeltaTime = a2;
  *((float *)&this->m_DeltaTime + 1) = v3;
  if ( *((float *)&this->m_DeltaTime + 1) > 0.0 )
  {
    a2a = 0;
    if ( *(int *)&this->m_Partical[0].byMaxFrame > 0 )
    {
      v28 = 0;
      while ( 1 )
      {
        v5 = v28 + *((_DWORD *)p_m_bActive + 3);
        if ( *(_BYTE *)(v5 + 148) )
        {
          if ( *(_DWORD *)(v5 + 12) == 3 )
          {
            v6 = 0;
            v26 = 0;
            if ( *((int *)p_m_bActive + 8) > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++a2a < *((_DWORD *)p_m_bActive + 7);
        v28 += 152;
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
          v2 = this;
          goto LABEL_29;
        }
        switch ( *(_DWORD *)(v8 + 8) )
        {
          case 2:
            if ( v7 > 0 )
            {
              if ( *(float *)(v8 + 20) >= 0.0 )
              {
                if ( *((float *)p_m_bActive + 1) - *(float *)(v8 - 56) > *(float *)(v8 + 20) )
                {
                  sub_4D4D30(p_m_bActive, a2a, v6);
                  *((_DWORD *)p_m_bActive + 4) = a2a;
                  *((_DWORD *)p_m_bActive + 5) = v26;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
                *(_DWORD *)(*(_DWORD *)(v28 + *((_DWORD *)p_m_bActive + 3)) + v7 + 8) = 3;
                *(_DWORD *)(*(_DWORD *)(v28 + *((_DWORD *)p_m_bActive + 3)) + v7 + 16) = *((_DWORD *)p_m_bActive + 1);
LABEL_21:
                *((_DWORD *)p_m_bActive + 5) = v6;
                *((_DWORD *)p_m_bActive + 4) = a2a;
LABEL_24:
                (*(void (**)(unsigned __int8 *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)p_m_bActive + 4))(
                  p_m_bActive,
                  *(_DWORD *)(*(_DWORD *)v5 + v7),
                  *(_DWORD *)(*(_DWORD *)v5 + v7 + 4),
                  0);
              }
            }
            break;
          case 3:
            goto LABEL_21;
          case 4:
            if ( sub_4D4D70(p_m_bActive, a2a) )
            {
              v9 = *(_DWORD *)(v5 + 4);
              *(_DWORD *)(v5 + 12) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = *(_BYTE *)(v5 + 149);
              *(_DWORD *)(v5 + 20) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                ((CEffgbParticle *)p_m_bActive)->Init(a2a);
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = v26 + 1;
        v7 += 72;
        if ( ++v26 >= *((_DWORD *)p_m_bActive + 8) )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *(int *)&v2->m_Partical[0].bValid <= 0 )
      v2->m_eKind[0] = 1;
    if ( !v2->m_eKind[0] )
    {
      *(float *)&v2->m_Partical[1].pPic = *(float *)&v2->m_Partical[2].dwColor * *((float *)&v2->m_DeltaTime + 1)
                                        + *(float *)&v2->m_Partical[1].pPic;
      if ( (g_bCursorVisible & 1) == 0 )
      {
        g_bCursorVisible |= 1u;
        ((CEffMgr *)&g_nCursorState)->Reset();
        atexit(nullsub_1);
      }
      v12 = 0;
      v13 = (int)abs32((int)*(float *)&v2->m_Partical[1].pPic) % HIBYTE(v2->m_Partical[0].fZ);
      fY_low = LODWORD(v2->m_Partical[1].fY);
      v15 = (float *)((char *)v2 + 16 * v13);
      v16 = (float *)&v2->m_Partical[3].fCurFrame + 4 * v13;
      fZ_low = LODWORD(v2->m_Partical[1].fZ);
      v20 = v15;
      v21 = v16;
      a2b = 0;
      v29 = (v15[50] - *v16) * (1.0 / (double)fY_low);
      v27 = (v15[51] - v15[49]) * (1.0 / (double)fZ_low);
      if ( fZ_low > 0 )
      {
        do
        {
          v17 = *v16;
          v18 = 0;
          v25 = (double)a2b * v27 + v15[49];
          if ( fY_low > 0 )
          {
            v19 = 68 * v12;
            do
            {
              ++v12;
              *(float *)(v19 + LODWORD(v2->m_Partical[0].fCurFrame) + 48) = v17;
              v17 = v17 + v29;
              v19 += 68;
              ++v18;
              *(float *)(v19 + LODWORD(v2->m_Partical[0].fCurFrame) - 12) = v17;
              *(float *)(v19 + LODWORD(v2->m_Partical[0].fCurFrame) - 16) = v25;
              v22 = v27 + v25;
              *(float *)(v19 + LODWORD(v2->m_Partical[0].fCurFrame) - 8) = v22;
              *(_DWORD *)(v19 + LODWORD(v2->m_Partical[0].fCurFrame) - 4) = v2->m_Partical[1].nQuadIndex;
              fY_low = LODWORD(v2->m_Partical[1].fY);
            }
            while ( v18 < fY_low );
            v16 = v21;
            v15 = v20;
          }
          ++a2b;
        }
        while ( a2b < SLODWORD(v2->m_Partical[1].fZ) );
      }
    }
  }
}

// 0x004C7450
void CEffect::FillQuadByPartical(_DWORD *a2)
{
  unsigned __int8 *p_m_bActive; // ebx
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
  int (**v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int (**v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  p_m_bActive = (unsigned __int8 *)&this->m_bActive;
  v3 = *(_DWORD *)&this->m_Partical[0].byMaxFrame;
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *((_DWORD *)p_m_bActive + 3);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*((_DWORD *)p_m_bActive + 3) + v7 + 148) = 1;
    *(_BYTE *)(*((_DWORD *)p_m_bActive + 3) + v7 + 149) = 1;
    v8 = ++dword_DE99B0;
    if ( !dword_DE99B0 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      dword_DE99B0 = 1;
    }
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 16) = v8;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4) = 0;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 8) = 0;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 20) = 0;
    if ( a2 )
      qmemcpy((void *)(*((_DWORD *)p_m_bActive + 3) + v7 + 24), a2, 0x7Cu);
    else
      memset((void *)(*((_DWORD *)p_m_bActive + 3) + v7 + 24), 0, 0x7Cu);
    ++*((_DWORD *)p_m_bActive + 6);
    if ( v4 != -1 )
    {
      v9 = *((_DWORD *)p_m_bActive + 8);
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int (**)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        * v13 = (*)CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int (*)(CEffect *, int))2;
        v14 = ++dword_DE99B0;
        if ( !dword_DE99B0 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          dword_DE99B0 = 1;
        }
        v13[3] = (int (*)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4);
      }
LABEL_22:
      v15 = *((_DWORD *)p_m_bActive + 8);
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int (**)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        * v19 = (*)CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int (*)(CEffect *, int))2;
        v20 = ++dword_DE99B0;
        if ( !dword_DE99B0 || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          dword_DE99B0 = 1;
        }
        v19[3] = (int (*)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4);
      }
LABEL_31:
      ((CEffgbParticle *)p_m_bActive)->~CEffgbParticle(v4, (int)CEffExplosive::ProcCommonTask, 0, 0, a2[18], a2[19]);
      *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7) + 16) = *((_DWORD *)p_m_bActive + 1);
    }
  }
}

// 0x004CA400
int CEffect::SetParam(int a2)
{
  int v2; // edx
  char v3; // bl
  int v4; // edx

  v2 = *(_DWORD *)(this->m_nPartical + 152 * (int)this->m_Partical[0].pPic);
  v3 = *(_BYTE *)(v2 + 72 * this->m_Partical[0].nQuadIndex + 65);
  v4 = v2 + 72 * this->m_Partical[0].nQuadIndex;
  if ( !v3 )
    *(_BYTE *)(v4 + 65) = 1;
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->m_DeltaTime - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004CE460
int CEffect::Render(int a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ebx
  int v5; // edi
  char *v6; // esi
  int v7; // ebp
  bool v8; // cc
  char *v9; // [esp+8h] [ebp-10h]
  int v11; // [esp+10h] [ebp-8h]
  int v12; // [esp+14h] [ebp-4h]
  int *a2a; // [esp+1Ch] [ebp+4h]

  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  result = dword_1895980;
  if ( dword_1895980 == -1 )
    result = 1;
  v3 = result;
  dword_1895980 = result + 1;
  v12 = result;
  v11 = 0;
  v4 = 3985 * a2;
  if ( dword_EC9E70[3985 * a2] > 0 )
  {
    v9 = (char *)&unk_EC9EB4 + v4 * 4;
    a2a = (int *)&dword_EC9E74[v4];
    do
    {
      v5 = sub_4CDCA0((int *)this, *a2a, v3, 0, 0, 0);
      if ( v5 != -1 )
      {
        v6 = v9;
        v7 = 8;
        do
        {
          if ( v6[88] )
            (*(void (**)(_DWORD, char *))(**((_DWORD **)&this->m_Partical[48].fFramePerSec + 5 * v5) + 36))(
              *((_DWORD *)&this->m_Partical[48].fFramePerSec + 5 * v5),
              v6);
          v6 += 124;
          --v7;
        }
        while ( v7 );
        v3 = v12;
      }
      v8 = ++v11 < dword_EC9E70[v4];
      ++a2a;
      v9 += 992;
    }
    while ( v8 );
    return v3;
  }
  return result;
}
