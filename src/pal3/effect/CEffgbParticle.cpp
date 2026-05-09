#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffgbParticle.h"

// 0x004C8650
int sub_4C8650(int *this, int a2, int a3, int a4, _DWORD *a5, int a6, int a7)
{
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  _DWORD *v13; // edx
  unsigned int v14; // eax
  _DWORD *v15; // edx

  v8 = *(this + 8);
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*(this + 3) + 152 * a2);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= v8 )
      return -1;
  }
  v13 = (_DWORD *)(v10 + 72 * v9);
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
    v15 = v13 + 7;
    *v15 = *a5;
    v15[1] = a5[1];
    v15[2] = a5[2];
    v15[3] = a5[3];
  }
  ++*(_DWORD *)(*(this + 3) + 152 * a2 + 4);
  return v9;
}

// 0x004C87A0
void * sub_4C87A0(void *Block, char a2)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi

  v3 = *((_DWORD *)Block + 7);
  *(_DWORD *)Block = &off_56F8B4;
  if ( v3 || *((_DWORD *)Block + 8) )
  {
    v4 = 0;
    if ( v3 > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(*((_DWORD *)Block + 3) + v5));
        ++v4;
        *(_DWORD *)(*((_DWORD *)Block + 3) + v5) = 0;
        v5 += 152;
      }
      while ( v4 < *((_DWORD *)Block + 7) );
    }
    operator delete(*((void **)Block + 3));
    *((_DWORD *)Block + 3) = 0;
    *((_DWORD *)Block + 7) = 0;
    *((_DWORD *)Block + 8) = 0;
  }
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x004C8830
int sub_4C8830(_DWORD *this, int a2)
{
  int v2; // edx
  int v3; // esi
  int result; // eax

  *(_BYTE *)(*(this + 3) + 152 * a2 + 148) = 0;
  v2 = 0;
  if ( (int)*(this + 8) > 0 )
  {
    v3 = 0;
    do
    {
      ++v2;
      v3 += 72;
      *(_BYTE *)(*(_DWORD *)(*(this + 3) + 152 * a2) + v3 - 8) = 0;
    }
    while ( v2 < *(this + 8) );
  }
  *(_DWORD *)(*(this + 3) + 152 * a2 + 4) = 0;
  result = *(this + 6) - 1;
  *(this + 6) = result;
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
_DWORD * sub_4C88D0(_DWORD *this)
{
  *(this + 1) = 0;
  *((_BYTE *)this + 8) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = -1;
  *(this + 8) = -1;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 3) = &off_56F908;
  *this = &off_56F8CC;
  *(this + 3) = &off_56F8C0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 16) = 0;
  *(this + 15) = 0;
  *(this + 14) = 0;
  *(this + 19) = 0;
  *(this + 18) = 0;
  *(this + 17) = 0;
  return this;
}

// 0x004C8930
_DWORD *sub_4C8930()
{
  _DWORD *v0; // eax

  v0 = operator new(0x50u);
  if ( v0 )
    return v0->Render();
  else
    return 0;
}

// 0x004C8970
void __fastcall sub_4C8970(_DWORD *a1)
{
  _DWORD *v2; // edi
  void (__thiscall ***v3)(_DWORD, int); // ecx
  int v4; // ebx
  _DWORD *v5; // esi
  int v6; // eax
  bool v7; // cc
  int v8; // edi

  v2 = a1 + 3;
  *a1 = &off_56F8CC;
  a1[3] = &off_56F8C0;
  v3 = (void (__thiscall ***)(_DWORD, int))a1[12];
  v4 = 0;
  if ( v3 )
  {
    (**v3)(v3, 1);
    a1[12] = 0;
  }
  v5 = a1 != 0 ? v2 : 0;
  *v5 = &off_56F908;
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
  *a1 = &off_56F62C;
}

// 0x004C8A40
char sub_4C8A40(int this, int a2)
{
  void *v3; // eax
  int v4; // ebp
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  _DWORD *v10; // eax
  _DWORD *v11; // eax
  int v12; // edi

  v3 = operator new(0x4C0u);
  *(_DWORD *)(this + 24) = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(*(_DWORD *)(this + 24) + v5) = operator new(0x2D0u);
      if ( !*(_DWORD *)(*(_DWORD *)(this + 24) + v5) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *(_DWORD *)(this + 40) = 8;
        *(_DWORD *)(this + 44) = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(*(_DWORD *)(this + 24) + v7 + 148) = 0;
          v8 = 0;
          if ( *(int *)(this + 44) > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(v9 + *(_DWORD *)(v7 + *(_DWORD *)(this + 24)) - 8) = 0;
            }
            while ( v8 < *(_DWORD *)(this + 44) );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *(_DWORD *)(this + 40) );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v12 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(*(_DWORD *)(this + 24) + v12));
        v12 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*(void **)(this + 24));
  }
LABEL_10:
  v10 = operator new(0x5896Cu);
  if ( v10 )
    v11 = sub_4BC760(v10);
  else
    v11 = 0;
  *(_DWORD *)(this + 48) = v11;
  return sub_4BD6C0(v11, (const char *)(a2 + 40));
}

// 0x004C8BF0
void sub_4C8BF0(float *this, float a2)
{
  float *v2; // edi
  double v3; // st7
  float *v4; // esi
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
  int v16; // edx
  int v17; // eax
  int v18; // ecx
  int v19; // [esp+Ch] [ebp-8h]
  int v21; // [esp+18h] [ebp+4h]

  v2 = this;
  v3 = a2 - *(this + 4);
  v4 = this + 3;
  *(this + 4) = a2;
  *(this + 5) = v3;
  v5 = *((int *)this + 5);
  if ( *(float *)&v5 > 0.0 )
  {
    sub_4BC7E0(*((_DWORD **)v2 + 12), v5);
    v6 = 0;
    v21 = 0;
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
        if ( ++v21 >= *((_DWORD *)v4 + 7) )
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
                if ( v4[1] - *(float *)(v9 + v10 - 56) > *(float *)(v9 + v10 + 20) )
                {
LABEL_25:
                  *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v4 + 3) + v6) + v9 + 8) = 3;
                  *(float *)(*(_DWORD *)(*((_DWORD *)v4 + 3) + v6) + v9 + 16) = v4[1];
                  *((_DWORD *)v4 + 4) = v21;
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
            *((_DWORD *)v4 + 4) = v21;
LABEL_26:
            (*(void (__thiscall **)(float *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4 + 4))(
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
              v16 = *(_DWORD *)(*v7 + 72 * v15 - 12);
              LOBYTE(v15) = *((_BYTE *)v7 + 149);
              v7[5] = v16;
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
    if ( *((int *)v2 + 9) <= 0 )
      sub_4BD7A0(*((_DWORD **)v2 + 12), 0);
  }
}

// 0x004C8E10
void sub_4C8E10(int this)
{
  gbMatrixStack *v2; // edi
  int v3; // eax
  float v4; // [esp+0h] [ebp-14h]
  float v5; // [esp+4h] [ebp-10h]
  float v6; // [esp+8h] [ebp-Ch]

  if ( !*(_BYTE *)(this + 8) )
  {
    v2 = *(gbMatrixStack **)(**(_DWORD **)(this + 4) + 216);
    v2->Push();
    v6 = *(float *)(this + 76) + *(float *)(this + 64);
    v5 = *(float *)(this + 72) + *(float *)(this + 60);
    v4 = *(float *)(this + 68) + *(float *)(this + 56);
    v2->Translate(v4, v5, v6);
    v3 = sub_4BC8A0(*(void **)(this + 48));
    if ( *(int *)(this + 36) <= 0 && v3 <= 0 )
      *(_BYTE *)(this + 8) = 1;
    v2->Pop();
  }
}
