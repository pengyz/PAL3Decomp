#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffect.h"

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
  _DWORD *v0; // eax

  v0 = (_DWORD *)operator new(0x10C0u);
  if ( v0 )
    return v0->FillDefaultUVSet();
  else
    return 0;
}

// 0x004C6A70
int CEffect::Reset(int _this, int a2, float a3, float a4, float a5)
{
  int v6; // ecx

  *(_BYTE *)(this + 8) = 0;
  *(_BYTE *)(this + 64) = 0;
  *(float *)(this + 164) = a3 + *(float *)(a2 + 184);
  *(float *)(this + 168) = a4 + *(float *)(a2 + 188);
  *(float *)(this + 172) = a5 + *(float *)(a2 + 192);
  *(_DWORD *)(this + 152) = *(_DWORD *)(a2 + 216);
  *(_DWORD *)(this + 156) = *(_DWORD *)(a2 + 196);
  *(_DWORD *)(this + 160) = *(_DWORD *)(a2 + 220);
  *(_DWORD *)(this + 184) = 0;
  *(_DWORD *)(this + 180) = 0;
  *(_DWORD *)(this + 176) = 0;
  *(_DWORD *)(this + 80) = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *(float *)(this + 84) = (float)HIBYTE(*(_DWORD *)(this + 80));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *(float *)(this + 88) = (float)(unsigned __int8)BYTE2(*(_DWORD *)(this + 80));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *(float *)(this + 92) = (float)(unsigned __int8)BYTE1(*(_DWORD *)(this + 80));
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *(_DWORD *)(this + 76) = 0;
  v6 = *(unsigned __int8 *)(this + 80);
  *(_DWORD *)(this + 72) = 0;
  *(float *)(this + 96) = (float)v6;
  *(_DWORD *)(this + 100) = *(_DWORD *)(a2 + 200);
  *(_DWORD *)(this + 104) = *(_DWORD *)(a2 + 200);
  return this->CreateGeom();
}

// 0x004C7150
void CEffect::CreateOnePartical(int _this, float a2)
{
  int v2; // edi
  double v3; // st7
  int v4; // esi
  int v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // esi
  int v13; // edx
  int v14; // ecx
  float *v15; // eax
  float *v16; // ebx
  double v17; // st7
  int v18; // edx
  int v19; // eax
  float *v20; // [esp+0h] [ebp-18h]
  float *v21; // [esp+4h] [ebp-14h]
  float v22; // [esp+8h] [ebp-10h]
  int v24; // [esp+Ch] [ebp-Ch]
  float v25; // [esp+Ch] [ebp-Ch]
  int v26; // [esp+10h] [ebp-8h]
  float v27; // [esp+10h] [ebp-8h]
  int v28; // [esp+14h] [ebp-4h]
  float v29; // [esp+14h] [ebp-4h]
  int v30; // [esp+20h] [ebp+8h]
  int v31; // [esp+20h] [ebp+8h]

  v2 = this;
  v3 = a2 - *(float *)(this + 16);
  v4 = this + 12;
  *(float *)(this + 16) = a2;
  *(float *)(this + 20) = v3;
  if ( *(float *)(this + 20) > 0.0 )
  {
    v30 = 0;
    if ( *(int *)(this + 40) > 0 )
    {
      v28 = 0;
      while ( 1 )
      {
        v5 = v28 + *(_DWORD *)(v4 + 12);
        if ( *(_BYTE *)(v5 + 148) )
        {
          if ( *(_DWORD *)(v5 + 12) == 3 )
          {
            v6 = 0;
            v26 = 0;
            if ( *(int *)(v4 + 32) > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++v30 < *(_DWORD *)(v4 + 28);
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
                if ( *(float *)(v4 + 4) - *(float *)(v8 - 56) > *(float *)(v8 + 20) )
                {
                  sub_4D4D30(v30, v6);
                  *(_DWORD *)(v4 + 16) = v30;
                  *(_DWORD *)(v4 + 20) = v26;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
                *(_DWORD *)(*(_DWORD *)(v28 + *(_DWORD *)(v4 + 12)) + v7 + 8) = 3;
                *(_DWORD *)(*(_DWORD *)(v28 + *(_DWORD *)(v4 + 12)) + v7 + 16) = *(_DWORD *)(v4 + 4);
LABEL_21:
                *(_DWORD *)(v4 + 20) = v6;
                *(_DWORD *)(v4 + 16) = v30;
LABEL_24:
                (*(void (**)(int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4 + 4))(
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
            if ( (unsigned __int8)sub_4D4D70(v30) )
            {
              v9 = *(_DWORD *)(v5 + 4);
              *(_DWORD *)(v5 + 12) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = *(_BYTE *)(v5 + 149);
              *(_DWORD *)(v5 + 20) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                v30->Init();
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = v26 + 1;
        v7 += 72;
        if ( ++v26 >= *(_DWORD *)(v4 + 32) )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *(int *)(v2 + 36) <= 0 )
      *(_BYTE *)(v2 + 8) = 1;
    if ( !*(_BYTE *)(v2 + 8) )
    {
      *(float *)(v2 + 76) = *(float *)(v2 + 148) * *(float *)(v2 + 20) + *(float *)(v2 + 76);
      if ( (g_bCursorVisible & 1) == 0 )
      {
        g_bCursorVisible |= 1u;
        CEffMgr::Reset(&g_nCursorState);
        atexit(nullsub_1);
      }
      v12 = 0;
      v13 = (int)abs32((int)*(float *)(v2 + 76)) % *(unsigned __int8 *)(v2 + 67);
      v14 = *(_DWORD *)(v2 + 108);
      v15 = (float *)(v2 + 16 * v13);
      v16 = (float *)(16 * (v13 + 12) + v2);
      v24 = *(_DWORD *)(v2 + 112);
      v20 = v15;
      v21 = v16;
      v31 = 0;
      v29 = (v15[50] - *v16) * (1.0 / (double)v14);
      v27 = (v15[51] - v15[49]) * (1.0 / (double)v24);
      if ( v24 > 0 )
      {
        do
        {
          v17 = *v16;
          v18 = 0;
          v25 = (double)v31 * v27 + v15[49];
          if ( v14 > 0 )
          {
            v19 = 68 * v12;
            do
            {
              ++v12;
              *(float *)(v19 + *(_DWORD *)(v2 + 48) + 48) = v17;
              v17 = v17 + v29;
              v19 += 68;
              ++v18;
              *(float *)(v19 + *(_DWORD *)(v2 + 48) - 12) = v17;
              *(float *)(v19 + *(_DWORD *)(v2 + 48) - 16) = v25;
              v22 = v27 + v25;
              *(float *)(v19 + *(_DWORD *)(v2 + 48) - 8) = v22;
              *(_DWORD *)(v19 + *(_DWORD *)(v2 + 48) - 4) = *(_DWORD *)(v2 + 80);
              v14 = *(_DWORD *)(v2 + 108);
            }
            while ( v18 < v14 );
            v16 = v21;
            v15 = v20;
          }
          ++v31;
        }
        while ( v31 < *(_DWORD *)(v2 + 112) );
      }
    }
  }
}

// 0x004C7450
void CEffect::FillQuadByPartical(_DWORD *a2)
{
  __int32 *p_m_bVisible; // ebx
  __int32 bVisible; // ecx
  int v4; // edx
  __int32 v5; // esi
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

  p_m_bVisible = (__int32 *)&this->m_bVisible;
  bVisible = this->m_Partical[0].bVisible;
  v4 = 0;
  if ( bVisible > 0 )
  {
    v5 = p_m_bVisible[3];
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= bVisible )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(p_m_bVisible[3] + v7 + 148) = 1;
    *(_BYTE *)(p_m_bVisible[3] + v7 + 149) = 1;
    v8 = ++dword_DE99B0;
    if ( !dword_DE99B0 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      dword_DE99B0 = 1;
    }
    *(_DWORD *)(p_m_bVisible[3] + v7 + 16) = v8;
    *(_DWORD *)(p_m_bVisible[3] + v7 + 4) = 0;
    *(_DWORD *)(p_m_bVisible[3] + v7 + 8) = 0;
    *(_DWORD *)(p_m_bVisible[3] + v7 + 20) = 0;
    if ( a2 )
      qmemcpy((void *)(p_m_bVisible[3] + v7 + 24), a2, 0x7Cu);
    else
      memset((void *)(p_m_bVisible[3] + v7 + 24), 0, 0x7Cu);
    ++p_m_bVisible[6];
    if ( v4 != -1 )
    {
      v9 = p_m_bVisible[8];
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(p_m_bVisible[3] + 152 * v4);
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
        ++*(_DWORD *)(p_m_bVisible[3] + v7 + 4);
      }
LABEL_22:
      v15 = p_m_bVisible[8];
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(p_m_bVisible[3] + 152 * v4);
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
        ++*(_DWORD *)(p_m_bVisible[3] + v7 + 4);
      }
LABEL_31:
      CEffgbParticle::~CEffgbParticle(
        (CEffgbParticle *)p_m_bVisible,
        v4,
        (int)CEffExplosive::ProcCommonTask,
        0,
        0,
        a2[18],
        a2[19]);
      *(_DWORD *)(p_m_bVisible[3] + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_bVisible[3] + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_bVisible[3] + v7) + 16) = p_m_bVisible[1];
    }
  }
}

// 0x004CA400
int CEffect::SetParam(int a2)
{
  int v2; // edx
  char v3; // bl
  int v4; // edx

  v2 = *(_DWORD *)(*(_DWORD *)&this->m_pES[24] + 152 * *(_DWORD *)&this->m_pES[28]);
  v3 = *(_BYTE *)(v2 + 72 * *(_DWORD *)&this->m_pES[32] + 65);
  v4 = v2 + 72 * *(_DWORD *)&this->m_pES[32];
  if ( !v3 )
    *(_BYTE *)(v4 + 65) = 1;
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->m_pES[16] - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
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
    CEffMgr::Reset(&g_nCursorState);
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
      v5 = sub_4CDCA0((int *)this->m_pES, *a2a, v3, 0, 0, 0);
      if ( v5 != -1 )
      {
        v6 = v9;
        v7 = 8;
        do
        {
          if ( v6[88] )
            (*(void (**)(_DWORD, char *))(**(_DWORD **)&this->m_pES[20 * v5 + 2348] + 36))(
              *(_DWORD *)&this->m_pES[20 * v5 + 2348],
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
