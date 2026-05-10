#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffgbParticle.h"

// Forward declarations for unnamed functions
int sub_4BC760(...);
int sub_4BC7E0(...);
int sub_4BC8A0(...);
int sub_4BD6C0(...);
int sub_4BD7A0(...);
int sub_4C6980(...);

// Unnamed globals (extern)
extern int dword_DE99B0;
extern void *off_56F62C;
extern void *off_56F8B4;
extern void *off_56F8C0;
extern void *off_56F8CC;
extern void *off_56F908;

// 0x004C8650
CEffgbParticle::~CEffgbParticle(
        CEffgbParticle *this,
        int a2,
        int a3,
        int a4,
        _DWORD *a5,
        int a6,
        int a7)
{
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  _DWORD *v15; // edx

  v8 = *(_DWORD *)&this->_pad_0000[32];
  v9 = 0;
  if ( v8 <= 0 )
  -1;
  v10 = *(_DWORD *)(*(_DWORD *)&this->_pad_0000[12] + 152 * a2);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= v8 )
  -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = a3;
  v13[1] = a4;
  v13[2] = 2;
  v14 = ++dword_DE99B0;
  if ( !dword_DE99B0 || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    dword_DE99B0 = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = a6;
  v13[6] = a7;
  if ( a5 )
  {
    v15 = (_DWORD *)v13 + 7;
    * v15 = (*)*a5;
    v15[1] = a5[1];
    v15[2] = a5[2];
    v15[3] = a5[3];
  }
  ++*(_DWORD *)(*(_DWORD *)&this->_pad_0000[12] + 152 * a2 + 4);
  v9;
}

// 0x004C87A0
void * CEffgbParticle::Create(CEffgbParticle *Block, char a2)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi

  v3 = *(_DWORD *)&Block->_pad_0000[28];
  *(_DWORD *)Block->_pad_0000 = &off_56F8B4;
  if ( v3 || *(_DWORD *)&Block->_pad_0000[32] )
  {
    v4 = 0;
    if ( v3 > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(*(_DWORD *)&Block->_pad_0000[12] + v5));
        ++v4;
        *(_DWORD *)(*(_DWORD *)&Block->_pad_0000[12] + v5) = 0;
        v5 += 152;
      }
      while ( v4 < *(_DWORD *)&Block->_pad_0000[28] );
    }
    operator delete(*(void **)&Block->_pad_0000[12]);
    *(_DWORD *)&Block->_pad_0000[12] = 0;
    *(_DWORD *)&Block->_pad_0000[28] = 0;
    *(_DWORD *)&Block->_pad_0000[32] = 0;
  }
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x004C8830
int CEffgbParticle::Init(int a2)
{
  int v2; // edx
  int v3; // esi
  int result; // eax

  *(_BYTE *)(*(_DWORD *)&this->_pad_0000[12] + 152 * a2 + 148) = 0;
  v2 = 0;
  if ( *(int *)&this->_pad_0000[32] > 0 )
  {
    v3 = 0;
    do
    {
      ++v2;
      v3 += 72;
      *(_BYTE *)(*(_DWORD *)(*(_DWORD *)&this->_pad_0000[12] + 152 * a2) + v3 - 8) = 0;
    }
    while ( v2 < *(_DWORD *)&this->_pad_0000[32] );
  }
  *(_DWORD *)(*(_DWORD *)&this->_pad_0000[12] + 152 * a2 + 4) = 0;
  result = *(_DWORD *)&this->_pad_0000[24] - 1;
  *(_DWORD *)&this->_pad_0000[24] = result;
  return result;
}

// 0x004C88C0
char * CEffgbParticle::Attach(char a2)
{
  char *v2; // esi

  v2 = (char *)this - 12;
  sub_4C6980((int)this - 12);
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004C88D0
_DWORD * CEffgbParticle::Render()
{
  *(_DWORD *)&this->_pad_0000[4] = 0;
  this->_pad_0000[8] = 0;
  *(_DWORD *)&this->_pad_0000[16] = 0;
  *(_DWORD *)&this->_pad_0000[20] = 0;
  *(_DWORD *)&this->_pad_0000[24] = 0;
  *(_DWORD *)&this->_pad_0000[28] = -1;
  *(_DWORD *)&this->_pad_0000[32] = -1;
  *(_DWORD *)&this->_pad_0000[36] = 0;
  *(_DWORD *)&this->_pad_0000[40] = 0;
  *(_DWORD *)&this->_pad_0000[44] = 0;
  *(_DWORD *)&this->_pad_0000[12] = &off_56F908;
  *(_DWORD *)this->_pad_0000 = &off_56F8CC;
  *(_DWORD *)&this->_pad_0000[12] = &off_56F8C0;
  this->m_pEffect = 0;
  this->m_fSize = 0.0;
  this->m_fZ = 0.0;
  this->m_fY = 0.0;
  this->m_fX = 0.0;
  this->m_fPZ = 0.0;
  this->m_fPY = 0.0;
  this->m_fPX = 0.0;
  return this->_pad_0000;
}

// 0x004C8930
_DWORD *CEffgbParticle::SetTimeScale()
{
  CEffgbParticle *v0; // eax

  v0 = (CEffgbParticle *)operator new(0x50u);
  if ( v0 )
    return v0->Render();
  else
    return 0;
}

// 0x004C8970
void CEffgbParticle::Destroy(_DWORD *a1)
{
  _DWORD *v2; // edi
  void (***v3)(_DWORD, int); // ecx
  int v4; // ebx
  _DWORD *v5; // esi
  int v6; // eax
  bool v7; // cc
  int v8; // edi

  v2 = (_DWORD *)a1 + 3;
  * a1 = (*)&off_56F8CC;
  a1[3] = &off_56F8C0;
  v3 = (void (***)(_DWORD, int))a1[12];
  v4 = 0;
  if ( v3 )
  {
    (**v3)(v3, 1);
    a1[12] = 0;
  }
  v5 = (_DWORD *)a1 != 0 ? v2 : 0;
  * v5 = (*)&off_56F908;
  v6 = v5[7];
  v7 = v6 <= 0;
  if ( !v6 )
  {
    if ( !*(a1 != 0 ? v2 + 8 : (_DWORD *)32) )
      goto LABEL_10;
    v7 = 1;
  }
  if ( !v7 )
  {
    v8 = 0;
    do
    {
      operator delete(*(void **)(v5[3] + v8));
      ++v4;
      *(_DWORD *)(v5[3] + v8) = 0;
      v8 += 152;
    }
    while ( v4 < v5[7] );
  }
  operator delete((void *)v5[3]);
  v5[3] = 0;
  v5[7] = 0;
  v5[8] = 0;
LABEL_10:
  * a1 = (*)&off_56F62C;
}

// 0x004C8A40
char CEffgbParticle::CreateTask(int a2)
{
  _DWORD *v3; // eax
  int v4; // ebp
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  char *v10; // eax
  ParticleEffect *v11; // eax
  int v12; // edi

  v3 = (_DWORD *)operator new(0x4C0u);
  *(_DWORD *)&this->_pad_0000[24] = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(*(_DWORD *)&this->_pad_0000[24] + v5) = operator new(0x2D0u);
      if ( !*(_DWORD *)(*(_DWORD *)&this->_pad_0000[24] + v5) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *(_DWORD *)&this->_pad_0000[40] = 8;
        *(_DWORD *)&this->_pad_0000[44] = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(*(_DWORD *)&this->_pad_0000[24] + v7 + 148) = 0;
          v8 = 0;
          if ( *(int *)&this->_pad_0000[44] > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(v9 + *(_DWORD *)(v7 + *(_DWORD *)&this->_pad_0000[24]) - 8) = 0;
            }
            while ( v8 < *(_DWORD *)&this->_pad_0000[44] );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *(_DWORD *)&this->_pad_0000[40] );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v12 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(*(_DWORD *)&this->_pad_0000[24] + v12));
        v12 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*(void **)&this->_pad_0000[24]);
  }
LABEL_10:
  v10 = (char *)operator new(0x5896Cu);
  if ( v10 )
    v11 = (ParticleEffect *)sub_4BC760(v10);
  else
    v11 = 0;
  this->m_pEffect = v11;
  return sub_4BD6C0(v11, (const char *)(a2 + 40));
}

// 0x004C8BF0
void CEffgbParticle::ProcCommonTask(float a2)
{
  CEffgbParticle *v2; // edi
  double v3; // st7
  char *v4; // esi
  int v5; // ecx
  int v6; // ebx
  int *v7; // ebp
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
  int v19; // [esp+Ch] [ebp-8h]
  int a2a; // [esp+18h] [ebp+4h]

  v2 = this;
  v3 = a2 - *(float *)&this->_pad_0000[16];
  v4 = (char *)&this->_pad_0000[12];
  *(float *)&this->_pad_0000[16] = a2;
  *(float *)&this->_pad_0000[20] = v3;
  v5 = *(int *)&this->_pad_0000[20];
  if ( *(float *)&v5 > 0.0 )
  {
    sub_4BC7E0(v2->m_pEffect->name, v5);
    v6 = 0;
    a2a = 0;
    if ( *((int *)v4 + 7) > 0 )
    {
      while ( 1 )
      {
        v7 = (int *)(*((_DWORD *)v4 + 3) + v6);
        if ( *((_BYTE *)v7 + 148) )
        {
          if ( v7[3] == 3 )
          {
            v8 = 0;
            v19 = 0;
            if ( *((int *)v4 + 8) > 0 )
              break;
          }
        }
LABEL_33:
        v6 += 152;
        if ( ++a2a >= *((_DWORD *)v4 + 7) )
        {
          v2 = this;
          goto LABEL_35;
        }
      }
      v9 = 0;
      while ( 1 )
      {
        v10 = *v7;
        if ( !*(_BYTE *)(v9 + *v7 + 64) || v9 > 0 && *(_DWORD *)(v9 + v10 - 64) == 2 )
          goto LABEL_33;
        switch ( *(_DWORD *)(v9 + v10 + 8) )
        {
          case 2:
            if ( v9 > 0 )
            {
              if ( *(float *)(v9 + v10 + 20) >= 0.0 )
              {
                if ( *((float *)v4 + 1) - *(float *)(v9 + v10 - 56) > *(float *)(v9 + v10 + 20) )
                {
LABEL_25:
                  *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v4 + 3) + v6) + v9 + 8) = 3;
                  *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v4 + 3) + v6) + v9 + 16) = *((_DWORD *)v4 + 1);
                  *((_DWORD *)v4 + 4) = a2a;
                  *((_DWORD *)v4 + 5) = v19;
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
            *((_DWORD *)v4 + 5) = v8;
            *((_DWORD *)v4 + 4) = a2a;
LABEL_26:
            (*(void (**)(char *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4 + 4))(
              v4,
              *(_DWORD *)(*v7 + v9),
              *(_DWORD *)(*v7 + v9 + 4),
              0);
            break;
          case 4:
            v11 = 0;
            v12 = (_DWORD *)(*((_DWORD *)v4 + 3) + v6);
            v13 = v12[1];
            if ( v13 <= 0 )
            {
LABEL_17:
              v15 = v7[1];
              v7[3] = 4;
              v16 = 9 * v15;
              LOBYTE(v15) = *((_BYTE *)v7 + 149);
              v7[5] = *(_DWORD *)(*v7 + 8 * v16 - 12);
              if ( (_BYTE)v15 == 1 )
              {
                v17 = 0;
                *(_BYTE *)(*((_DWORD *)v4 + 3) + v6 + 148) = 0;
                if ( *((int *)v4 + 8) > 0 )
                {
                  v18 = 0;
                  do
                  {
                    ++v17;
                    v18 += 72;
                    *(_BYTE *)(*(_DWORD *)(*((_DWORD *)v4 + 3) + v6) + v18 - 8) = 0;
                  }
                  while ( v17 < *((_DWORD *)v4 + 8) );
                }
                *(_DWORD *)(*((_DWORD *)v4 + 3) + v6 + 4) = 0;
                --*((_DWORD *)v4 + 6);
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
        if ( ++v19 >= *((_DWORD *)v4 + 8) )
          goto LABEL_33;
      }
    }
LABEL_35:
    if ( *(int *)&v2->_pad_0000[36] <= 0 )
      sub_4BD7A0(v2->m_pEffect->name, 0);
  }
}

// 0x004C8E10
void CEffgbParticle::GetEditorTaskDescription()
{
  gbMatrixStack *v2; // edi
  int v3; // eax
  float v4; // [esp+0h] [ebp-14h]
  float v5; // [esp+4h] [ebp-10h]
  float v6; // [esp+8h] [ebp-Ch]

  if ( !this->_pad_0000[8] )
  {
    v2 = (gbMatrixStack *)*(gbMatrixStack **)(**(_DWORD **)&this->_pad_0000[4] + 216);
    v2->Push();
    v6 = this->m_fPZ + this->m_fZ;
    v5 = this->m_fPY + this->m_fY;
    v4 = this->m_fPX + this->m_fX;
    v2->Translate(v4, v5, v6);
    v3 = sub_4BC8A0(this->m_pEffect->name);
    if ( *(int *)&this->_pad_0000[36] <= 0 && v3 <= 0 )
      this->_pad_0000[8] = 1;
    v2->Pop();
  }
}
