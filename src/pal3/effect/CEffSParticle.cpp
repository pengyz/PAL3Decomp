#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffSParticle.h"

// Forward declarations for unnamed functions
int sub_4D4EA0(...);
int sub_4D4EE0(...);
int sub_4D4F20(...);
int sub_4D4FC0(...);
int sub_4D51B0(...);
int sub_4D53E0(...);
int sub_4D5620(...);
int sub_4D56B0(...);
int sub_4D5790(...);
int sub_4D5860(...);
int sub_4D58D0(...);

// Unnamed globals (extern)
extern unsigned char byte_1895561;
extern int dword_17A8118;
extern void *off_56F62C;
extern void *off_56FB28;
extern void *off_56FB34;
extern void *off_56FB70;
extern int unk_5D4D3C;
extern int unk_5D4D7C;
extern int unk_5D4DF4;
extern int unk_5D572C;
extern int unk_5D5744;
extern int unk_5D5758;
extern int unk_5D5760;
extern int unk_5D576C;

// 0x004D4EE0
_DWORD *sub_4D4EE0()
{
  _DWORD *v0; // eax

  v0 = operator new(0x30u);
  if ( v0 )
    return sub_4D4EA0(v0);
  else
    return 0;
}

// 0x004D4F20
int sub_4D4F20()
{
  int v2; // esi
  int v3; // eax
  int result; // eax
  int v5; // ebx
  int v6; // edi

  *this = &off_56FB34;
  v2 = this != 0 ? (unsigned int)(this + 3) : 0;
  *((_DWORD *)this + 3) = &off_56FB28;
  v3 = *(_DWORD *)(v2 + 0x1C);
  *(_DWORD *)v2 = &off_56FB70;
  if ( v3 || (result = *(this != 0 ? this + 11 : (_DWORD *)32)) != 0 )
  {
    v5 = 0;
    if ( *(this != 0 ? this + 10 : (int *)28) > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(v6 + *(_DWORD *)(v2 + 12)));
        ++v5;
        *(_DWORD *)(v6 + *(_DWORD *)(v2 + 12)) = 0;
        v6 += 152;
      }
      while ( v5 < *(_DWORD *)(v2 + 28) );
    }
    operator delete(*(void **)(v2 + 12));
    *(_DWORD *)(v2 + 12) = 0;
    *(_DWORD *)(v2 + 28) = 0;
    *(_DWORD *)(v2 + 32) = 0;
    *this = &off_56F62C;
    return 0;
  }
  else
  {
    *this = &off_56F62C;
  }
  return result;
}

// 0x004D4FC0
int sub_4D4FC0(int this, float a2)
{
  float *v2; // esi
  int v3; // ebx
  int *v4; // ebp
  int v5; // edx
  int v6; // edi
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // edx
  _DWORD *v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // ecx
  int result; // eax
  int v17; // [esp+Ch] [ebp-8h]
  int v18; // [esp+10h] [ebp-4h]
  int v19; // [esp+18h] [ebp+4h]

  v2 = (float *)(this + 12);
  v3 = 0;
  v18 = this;
  *(float *)(this + 20) = a2 - *(float *)(this + 16);
  *(float *)(this + 16) = a2;
  v19 = 0;
  if ( *(int *)(this + 40) <= 0 )
    goto LABEL_34;
  do
  {
    v4 = (int *)(v3 + *((_DWORD *)v2 + 3));
    if ( *((_BYTE *)v4 + 148) )
    {
      if ( v4[3] == 3 )
      {
        v5 = 0;
        v17 = 0;
        if ( *((int *)v2 + 8) > 0 )
        {
          v6 = 0;
          do
          {
            v7 = *v4;
            if ( !*(_BYTE *)(v6 + *v4 + 64) || v6 > 0 && *(_DWORD *)(v6 + v7 - 64) == 2 )
              break;
            switch ( *(_DWORD *)(v6 + v7 + 8) )
            {
              case 2:
                if ( v6 > 0 )
                {
                  if ( *(float *)(v6 + v7 + 20) >= 0.0 )
                  {
                    if ( v2[1] - *(float *)(v6 + v7 - 56) > *(float *)(v6 + v7 + 20) )
                    {
LABEL_24:
                      *(_DWORD *)(*(_DWORD *)(v3 + *((_DWORD *)v2 + 3)) + v6 + 8) = 3;
                      *(float *)(*(_DWORD *)(v3 + *((_DWORD *)v2 + 3)) + v6 + 16) = v2[1];
                      *((_DWORD *)v2 + 4) = v19;
                      *((_DWORD *)v2 + 5) = v17;
                      goto LABEL_25;
                    }
                  }
                  else if ( *(_DWORD *)(v6 + v7 - 64) == 4 )
                  {
                    goto LABEL_24;
                  }
                }
                break;
              case 3:
                *((_DWORD *)v2 + 5) = v5;
                *((_DWORD *)v2 + 4) = v19;
LABEL_25:
                (*(void (__thiscall **)(float *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2 + 4))(
                  v2,
                  *(_DWORD *)(*v4 + v6),
                  *(_DWORD *)(*v4 + v6 + 4),
                  0);
                break;
              case 4:
                v8 = 0;
                v9 = (_DWORD *)(v3 + *((_DWORD *)v2 + 3));
                v10 = v9[1];
                if ( v10 <= 0 )
                {
LABEL_16:
                  v12 = v4[1];
                  v4[3] = 4;
                  v13 = *(_DWORD *)(*v4 + 72 * v12 - 12);
                  LOBYTE(v12) = *((_BYTE *)v4 + 149);
                  v4[5] = v13;
                  if ( (_BYTE)v12 == 1 )
                  {
                    v14 = 0;
                    *(_BYTE *)(v3 + *((_DWORD *)v2 + 3) + 148) = 0;
                    if ( *((int *)v2 + 8) > 0 )
                    {
                      v15 = 0;
                      do
                      {
                        ++v14;
                        v15 += 72;
                        *(_BYTE *)(*(_DWORD *)(v3 + *((_DWORD *)v2 + 3)) + v15 - 8) = 0;
                      }
                      while ( v14 < *((_DWORD *)v2 + 8) );
                    }
                    *(_DWORD *)(v3 + *((_DWORD *)v2 + 3) + 4) = 0;
                    --*((_DWORD *)v2 + 6);
                    goto LABEL_32;
                  }
                }
                else
                {
                  v11 = (_DWORD *)(*v9 + 8);
                  while ( *v11 == 4 )
                  {
                    ++v8;
                    v11 += 18;
                    if ( v8 >= v10 )
                      goto LABEL_16;
                  }
                }
                break;
            }
            v5 = v17 + 1;
            v6 += 72;
            ++v17;
          }
          while ( v17 < *((_DWORD *)v2 + 8) );
        }
      }
    }
LABEL_32:
    v3 += 152;
    ++v19;
  }
  while ( v19 < *((_DWORD *)v2 + 7) );
  this = v18;
LABEL_34:
  result = *(_DWORD *)(this + 36);
  if ( result <= 0 )
    *(_BYTE *)(this + 8) = 1;
  return result;
}

// 0x004D51B0
void sub_4D51B0(_DWORD *a2)
{
  _DWORD *v2; // ebx
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
  int (__thiscall **v13)(int, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int (__thiscall **v19)(int, int); // esi
  unsigned int v20; // eax

  v2 = this + 3;
  v3 = *((_DWORD *)this + 10);
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = v2[3];
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(v2[3] + v7 + 148) = 1;
    *(_BYTE *)(v2[3] + v7 + 149) = 1;
    v8 = ++dword_17A8118;
    if ( !dword_17A8118 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      dword_17A8118 = 1;
    }
    *(_DWORD *)(v2[3] + v7 + 16) = v8;
    *(_DWORD *)(v2[3] + v7 + 4) = 0;
    *(_DWORD *)(v2[3] + v7 + 8) = 0;
    *(_DWORD *)(v2[3] + v7 + 20) = 0;
    if ( a2 )
      qmemcpy((void *)(v2[3] + v7 + 24), a2, 0x7Cu);
    else
      memset((void *)(v2[3] + v7 + 24), 0, 0x7Cu);
    ++v2[6];
    if ( v4 != -1 )
    {
      v9 = v2[8];
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(v2[3] + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int (__thiscall **)(int, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int (__thiscall *)(int, int))2;
        v14 = ++dword_17A8118;
        if ( !dword_17A8118 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          dword_17A8118 = 1;
        }
        v13[3] = (int (__thiscall *)(int, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(v2[3] + v7 + 4);
      }
LABEL_22:
      v15 = v2[8];
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(v2[3] + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int (__thiscall **)(int, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int (__thiscall *)(int, int))2;
        v20 = ++dword_17A8118;
        if ( !dword_17A8118 || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          dword_17A8118 = 1;
        }
        v19[3] = (int (__thiscall *)(int, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(v2[3] + v7 + 4);
      }
LABEL_31:
      v4->Render(CEffSParticle::Attach, 0, 0, a2[18], a2[19]);
      *(_DWORD *)(v2[3] + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(v2[3] + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(v2[3] + v7) + 16) = v2[1];
    }
  }
}

// 0x004D53E0
int sub_4D53E0(int a2)
{
  int v3; // edi
  int v4; // ebx
  int v5; // ecx
  float v7; // [esp+Ch] [ebp-Ch]
  float v8; // [esp+10h] [ebp-8h]
  float v9; // [esp+14h] [ebp-4h]
  float v10; // [esp+14h] [ebp-4h]

  v3 = *((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7);
  v4 = *(_DWORD *)v3 + 72 * *((_DWORD *)this + 8);
  if ( (byte_1895561 & 1) == 0 )
  {
    byte_1895561 |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  if ( (byte_1895561 & 1) == 0 )
  {
    byte_1895561 |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  if ( !*(_BYTE *)(v4 + 65) )
  {
    *(float *)(v4 + 56) = *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 4) + 104);
    if ( *(_BYTE *)(v3 + 113) )
      *(float *)(v4 + 44) = *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 4) + 108);
    if ( *(_BYTE *)(v3 + 114) )
      CCBSystem::ProcAI(*(float *)(v3 + 24));
    *(_BYTE *)(v4 + 65) = 1;
  }
  v5 = *(_DWORD *)(*((_DWORD *)this + 1) + 4);
  v7 = *(double *)(v5 + 88);
  v8 = *(float *)(v5 + 104);
  if ( v8 - *(float *)(v4 + 56) > *(float *)(v3 + 28) )
  {
    v9 = *(float *)(v5 + 108) + v7 * *(float *)(v3 + 32);
    if ( (byte_1895561 & 1) == 0 )
    {
      byte_1895561 |= 1u;
      CEffMgr::Reset(&g_nCursorState);
      atexit(nullsub_1);
    }
    if ( v9 <= 20.0 )
    {
      if ( v9 < 0.0 )
        v9 = 0.0;
      v9->ProcAI();
    }
    else
    {
      CCBSystem::ProcAI(20.0);
    }
  }
  if ( v8 - *(float *)(v4 + 56) > *(float *)(v3 + 36) )
  {
    v10 = *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 4) + 108) + v7 * *(float *)(v3 + 56);
    if ( (byte_1895561 & 1) == 0 )
    {
      byte_1895561 |= 1u;
      CEffMgr::Reset(&g_nCursorState);
      atexit(nullsub_1);
    }
    if ( v10 <= 20.0 )
    {
      if ( v10 < 0.0 )
        v10 = 0.0;
      v10->ProcAI();
    }
    else
    {
      CCBSystem::ProcAI(20.0);
    }
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || v8 - *(float *)(v4 + 56) >= *(float *)(v4 + 24) )
  {
    if ( *(_BYTE *)(v3 + 113) )
      CCBSystem::ProcAI(1.0);
    *(_DWORD *)(v4 + 8) = 4;
  }
  return 0;
}

// 0x004D5620
void * sub_4D5620(int a1)
{
  void *result; // eax

  switch ( a1 )
  {
    case 0:
      result = &unk_5D576C;
      break;
    case 1:
    case 3:
      result = &unk_5D5760;
      break;
    case 2:
    case 4:
      result = &unk_5D5758;
      break;
    case 9:
      result = &unk_5D4DF4;
      break;
    case 20:
      result = &unk_5D4D7C;
      break;
    case 22:
      result = &unk_5D5744;
      break;
    case 23:
      result = &unk_5D572C;
      break;
    default:
      result = &unk_5D4D3C;
      break;
  }
  return result;
}

// 0x004D56B0
int sub_4D56B0(int a2, int a3, int a4, _DWORD *a5, int a6, int a7)
{
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  _DWORD *v13; // edx
  unsigned int v14; // eax
  _DWORD *v15; // edx

  v8 = *((_DWORD *)this + 8);
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*((_DWORD *)this + 3) + 152 * a2);
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
  v14 = ++dword_17A8118;
  if ( !dword_17A8118 || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    dword_17A8118 = 1;
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
  ++*(_DWORD *)(*((_DWORD *)this + 3) + 152 * a2 + 4);
  return v9;
}

// 0x004D5790
void * sub_4D5790(void *Block, char a2)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi

  v3 = *((_DWORD *)Block + 7);
  *(_DWORD *)Block = &off_56FB70;
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

// 0x004D5860
char * sub_4D5860(char a2)
{
  char *v2; // esi

  v2 = (char *)(this - 3);
  CEffSParticle::~CEffSParticle(this - 3);
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004D58D0
int sub_4D58D0(unsigned __int8 *a2)
{
  unsigned __int8 *v4; // edx
  int v5; // esi
  unsigned __int16 v6; // cx
  unsigned __int8 v7; // bl
  unsigned int i; // eax
  int v9; // ecx
  int v10; // eax

  if ( !*a2 )
    return 0;
  v4 = a2 + 1;
  v5 = *a2 << 24;
  if ( a2[1] )
  {
    v5 |= a2[1] << 16;
    v4 = a2 + 2;
    if ( a2[2] )
    {
      LOBYTE(v6) = 0;
      HIBYTE(v6) = a2[2];
      v5 |= v6;
      v4 = a2 + 3;
      if ( a2[3] )
      {
        v5 |= a2[3];
        v4 = a2 + 4;
      }
    }
  }
  v7 = *v4;
  for ( i = ~v5; v7; ++v4 )
  {
    v9 = *(this + HIBYTE(i));
    v10 = v7 | (i << 8);
    v7 = v4[1];
    i = v9 ^ v10;
  }
  return ~i;
}
