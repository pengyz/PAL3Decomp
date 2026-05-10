#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffMeteor.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/CEffgbParticle.h"
#include "pal3/gen/CMeteorChain.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_4CB3A0(...);
int sub_4CCC60(...);
int sub_4CCD10(...);
int sub_4CD070(...);
int sub_4CD0D0(...);
int sub_4CD3D0(...);
int sub_4D4D30(...);
int sub_4D4D70(...);

// Unnamed globals (extern)
extern char aDProjectPal3Co_0[];
extern char aNewFailInCeffm[];
extern int nullsub_1;
extern int nullsub_3;
extern void *off_56F62C;
extern void *off_56F96C;
extern void *off_56F978;
extern void *off_56F9B4;
extern int unk_FFFFFF;

// 0x004CB480
CEffMeteor::CEffMeteor()
{
  _DWORD *v0; // eax

  v0 = (_DWORD *)operator new(0x10D0u);
  if ( v0 )
  sub_4CB3A0(v0);
  else
  0;
}

// 0x004CB4C0
CEffMeteor::~CEffMeteor()
{
  int v2; // edi
  void *v3; // eax
  int v4; // ebp
  char *v5; // eax
  char *v6; // esi
  gbRefObject *v7; // ecx
  int v8; // esi
  int v9; // eax
  bool v10; // cc
  int v11; // edi

  v2 = a1 + 12;
  *(_DWORD *)a1 = &off_56F978;
  *(_DWORD *)(a1 + 12) = &off_56F96C;
  v3 = (void *)*(void **)(a1 + 48);
  v4 = 0;
  if ( v3 )
    operator delete(v3);
  if ( *(_DWORD *)(a1 + 56) )
    operator delete(*(void **)(a1 + 56));
  v5 = (char *)*(char **)(a1 + 52);
  if ( v5 )
  {
    v6 = (char *)v5 - 4;
    `eh vector destructor iterator'(
      v5,
      0x38u,
      *((_DWORD *)v5 - 1),
      (void (*)(void *))CMeteorChain::CMeteorChain);
    operator delete(v6);
  }
  v7 = (gbRefObject *)*(gbRefObject **)(a1 + 60);
  if ( v7 )
    v7->Release();
  if ( *(_DWORD *)(a1 + 64) )
    operator delete(*(void **)(a1 + 64));
  v8 = a1 != 0 ? v2 : 0;
  *(_DWORD *)v8 = &off_56F9B4;
  v9 = *(_DWORD *)(v8 + 0x1C);
  v10 = v9 <= 0;
  if ( !v9 )
  {
    if ( !*(_DWORD *)(a1 != 0 ? v2 + 0x20 : 32) )
      goto LABEL_18;
    v10 = 1;
  }
  if ( !v10 )
  {
    v11 = 0;
    do
    {
      operator delete(*(void **)(*(_DWORD *)(v8 + 12) + v11));
      ++v4;
      *(_DWORD *)(*(_DWORD *)(v8 + 12) + v11) = 0;
      v11 += 152;
    }
    while ( v4 < *(_DWORD *)(v8 + 28) );
  }
  operator delete(*(void **)(v8 + 12));
  *(_DWORD *)(v8 + 12) = 0;
  *(_DWORD *)(v8 + 28) = 0;
  *(_DWORD *)(v8 + 32) = 0;
LABEL_18:
  *(_DWORD *)a1 = &off_56F62C;
}

// 0x004CB5E0
int CEffMeteor::Init(int a2, float a3, float a4, float a5)
{
  int v6; // ecx
  int result; // eax
  int v8; // ecx

  this->_data[8] = 0;
  this->_data[68] = 0;
  *(float *)&this->_data[160] = a3 + *(float *)(a2 + 184);
  *(float *)&this->_data[164] = a4 + *(float *)(a2 + 188);
  *(float *)&this->_data[168] = a5 + *(float *)(a2 + 192);
  *(_DWORD *)&this->_data[148] = *(_DWORD *)(a2 + 216);
  *(_DWORD *)&this->_data[152] = *(_DWORD *)(a2 + 196);
  *(_DWORD *)&this->_data[156] = *(_DWORD *)(a2 + 220);
  *(float *)&this->_data[184] = a3 + *(float *)(a2 + 252);
  *(float *)&this->_data[188] = a4 + *(float *)(a2 + 256);
  *(float *)&this->_data[192] = a5 + *(float *)(a2 + 260);
  *(_DWORD *)&this->_data[180] = 0;
  *(_DWORD *)&this->_data[176] = 0;
  *(_DWORD *)&this->_data[172] = 0;
  *(_DWORD *)&this->_data[88] = *(_DWORD *)(a2 + 204);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(float *)&this->_data[92] = (float)HIBYTE(*(_DWORD *)&this->_data[88]);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(float *)&this->_data[96] = (float)(unsigned __int8)BYTE2(*(_DWORD *)&this->_data[88]);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(float *)&this->_data[100] = (float)(unsigned __int8)BYTE1(*(_DWORD *)&this->_data[88]);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(_DWORD *)&this->_data[84] = 0;
  v6 = (unsigned __int8)this->_data[88];
  *(_DWORD *)&this->_data[80] = 0;
  *(float *)&this->_data[104] = (float)v6;
  *(_DWORD *)&this->_data[108] = *(_DWORD *)(a2 + 200);
  *(_DWORD *)&this->_data[112] = *(_DWORD *)(a2 + 200);
  nullsub_3(this);
  result = *(_DWORD *)&this->_data[116];
  v8 = 0;
  if ( result > 0 )
  {
    result = 0;
    do
    {
      ++v8;
      *(_DWORD *)(*(_DWORD *)&this->_data[52] + result + 36) = *(_DWORD *)&this->_data[88];
      *(_DWORD *)(*(_DWORD *)&this->_data[52] + result + 48) = *(_DWORD *)&this->_data[120];
      *(_DWORD *)(*(_DWORD *)&this->_data[52] + result + 44) = *(_DWORD *)&this->_data[128];
      *(_DWORD *)(*(_DWORD *)&this->_data[52] + result + 52) = *(_DWORD *)&this->_data[132];
      *(_DWORD *)(*(_DWORD *)&this->_data[52] + result + 40) = *(_DWORD *)&this->_data[136];
      result += 56;
    }
    while ( v8 < *(_DWORD *)&this->_data[116] );
  }
  return result;
}

// 0x004CB800
char CEffMeteor::Create(int base)
{
  _DWORD *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v11; // edi
  int v12; // ebx
  void *v13; // eax
  int v14; // ebx
  int v15; // ebx
  int v16; // ebx
  _DWORD *v17; // eax
  int v18; // ebx
  _DWORD *v19; // ecx
  int v20; // ebx
  int v21; // ebx
  char *v22; // eax
  int v23; // eax
  int v24; // ecx
  int v25; // edi
  int v26; // ebx
  char ArgList[1024]; // [esp+Ch] [ebp-810h] BYREF
  _BYTE pExceptionObject[1024]; // [esp+40Ch] [ebp-410h] BYREF
  void *Block; // [esp+80Ch] [ebp-10h]
  int v31; // [esp+818h] [ebp-4h]
  int basea; // [esp+824h] [ebp+8h]
  int baseb; // [esp+824h] [ebp+8h]

  v3 = (_DWORD *)operator new(0x4C0u);
  *(_DWORD *)&this->_data[24] = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v5 + *(_DWORD *)&this->_data[24]) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v5 + *(_DWORD *)&this->_data[24]) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *(_DWORD *)&this->_data[40] = 8;
        *(_DWORD *)&this->_data[44] = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(v7 + *(_DWORD *)&this->_data[24] + 148) = 0;
          v8 = 0;
          if ( *(int *)&this->_data[44] > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(*(_DWORD *)(v7 + *(_DWORD *)&this->_data[24]) + v9 - 8) = 0;
            }
            while ( v8 < *(_DWORD *)&this->_data[44] );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *(_DWORD *)&this->_data[40] );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v11 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v11 + *(_DWORD *)&this->_data[24]));
        v11 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*(void **)&this->_data[24]);
  }
LABEL_10:
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(_DWORD *)&this->_data[116] = abs32((int)*(float *)(base + 224));
  *(_DWORD *)&this->_data[120] = *(_DWORD *)(base + 228);
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  *(_DWORD *)&this->_data[124] = (int)*(float *)(base + 232);
  *(_DWORD *)&this->_data[128] = *(_DWORD *)(base + 244);
  *(_DWORD *)&this->_data[132] = *(_DWORD *)(base + 248);
  *(_DWORD *)&this->_data[136] = *(_DWORD *)(base + 268);
  this->_data[71] = *(float *)(base + 224) > 0.0;
  *(_DWORD *)&this->_data[144] = *(_DWORD *)(base + 180);
  *(_DWORD *)&this->_data[160] = *(_DWORD *)(base + 184);
  *(_DWORD *)&this->_data[164] = *(_DWORD *)(base + 188);
  *(_DWORD *)&this->_data[168] = *(_DWORD *)(base + 192);
  *(_DWORD *)&this->_data[148] = *(_DWORD *)(base + 216);
  *(_DWORD *)&this->_data[152] = *(_DWORD *)(base + 196);
  *(_DWORD *)&this->_data[156] = *(_DWORD *)(base + 220);
  *(_DWORD *)&this->_data[184] = *(_DWORD *)(base + 252);
  *(_DWORD *)&this->_data[188] = *(_DWORD *)(base + 256);
  *(_DWORD *)&this->_data[192] = *(_DWORD *)(base + 260);
  *(_DWORD *)&this->_data[196] = *(_DWORD *)(base + 264);
  *(_DWORD *)&this->_data[200] = *(_DWORD *)(base + 236);
  *(_DWORD *)&this->_data[204] = *(_DWORD *)(base + 240);
  this->_data[69] = *(_BYTE *)(base + 213);
  this->_data[70] = *(_BYTE *)(base + 215);
  this->_data[72] = *(_BYTE *)(base + 176);
  *(_DWORD *)&this->_data[76] = &unk_FFFFFF;
  *(_DWORD *)&this->_data[88] = *(_DWORD *)(base + 204);
  sub_4CCC60(this->_data, *(_DWORD *)(base + 168), *(_DWORD *)(base + 172));
  v12 = *(_DWORD *)&this->_data[116];
  v13 = (void *)operator new(68 * v12);
  Block = v13;
  v31 = 0;
  if ( v13 )
  {
    v14 = v12 - 1;
    basea = (int)v13;
    if ( v14 >= 0 )
    {
      v15 = v14 + 1;
      do
      {
        ArraySort(basea, 12, 4, gbVec3D::`default constructor closure');
        --v15;
        basea += 68;
      }
      while ( v15 );
      v13 = Block;
    }
  }
  else
  {
    v13 = 0;
  }
  v16 = *(_DWORD *)&this->_data[116];
  *(_DWORD *)&this->_data[48] = v13;
  v31 = -1;
  v17 = (_DWORD *)operator new(48 * v16);
  if ( v17 )
  {
    v18 = v16 - 1;
    if ( v18 >= 0 )
    {
      v19 = (_DWORD *)v17 + 5;
      v20 = v18 + 1;
      do
      {
        *(v19 - 5) = 0;
        *(v19 - 4) = 0;
        *(v19 - 3) = 0;
        *(v19 - 2) = 0;
        *(v19 - 1) = 0;
        *v19 = 0;
        v19[1] = 0;
        v19[2] = 0;
        v19[3] = 0;
        v19[4] = 0;
        v19[5] = 0;
        v19[6] = 0;
        v19 += 12;
        --v20;
      }
      while ( v20 );
    }
  }
  else
  {
    v17 = 0;
  }
  v21 = *(_DWORD *)&this->_data[116];
  *(_DWORD *)&this->_data[56] = v17;
  v22 = (char *)operator new(56 * v21 + 4);
  Block = v22;
  v31 = 1;
  if ( v22 )
  {
    *(_DWORD *)v22 = v21;
    baseb = (int)(v22 + 4);
    `eh vector constructor iterator'(
      v22 + 4,
      0x38u,
      v21,
      (void (*)(void *))sub_4CD070,
      (void (*)(void *))CMeteorChain::CMeteorChain);
    v23 = baseb;
  }
  else
  {
    v23 = 0;
  }
  v24 = *(_DWORD *)&this->_data[48];
  v31 = -1;
  *(_DWORD *)&this->_data[52] = v23;
  if ( !v24 || !v23 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffm, aDProjectPal3Co_0, 144),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  sub_4CCD10((int)this, base + 40);
  v25 = 0;
  if ( *(int *)&this->_data[116] > 0 )
  {
    v26 = 0;
    do
    {
      sub_4CD0D0(
        (_BYTE *)(*(_DWORD *)&this->_data[52] + v26),
        *(_DWORD *)&this->_data[4],
        *(_DWORD *)&this->_data[124],
        this->_data[71] == 0,
        *(_DWORD *)&this->_data[64]);
      ++v25;
      v26 += 56;
    }
    while ( v25 < *(_DWORD *)&this->_data[116] );
  }
  return 1;
}

// 0x004CBFC0
void CEffMeteor::CreateTask(int arg0)
{
  CEffMeteor *v2; // edi
  double v3; // st7
  char *v4; // esi
  int v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // ebx
  int v13; // esi
  int v14; // esi
  int v15; // edx
  int v16; // eax
  char *v17; // ecx
  int v19; // [esp+4h] [ebp-Ch]
  int v20; // [esp+8h] [ebp-8h]
  int a2; // [esp+Ch] [ebp-4h]

  v2 = this;
  v3 = *(float *)&arg0 - *(float *)&this->_data[16];
  v4 = (char *)&this->_data[12];
  *(float *)&this->_data[16] = *(float *)&arg0;
  *(float *)&this->_data[20] = v3;
  if ( *(float *)&this->_data[20] > 0.0 )
  {
    a2 = 0;
    if ( *(int *)&this->_data[40] > 0 )
    {
      v20 = 0;
      while ( 1 )
      {
        v5 = v20 + *((_DWORD *)v4 + 3);
        if ( *(_BYTE *)(v5 + 148) )
        {
          if ( *(_DWORD *)(v5 + 12) == 3 )
          {
            v6 = 0;
            v19 = 0;
            if ( *((int *)v4 + 8) > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++a2 < *((_DWORD *)v4 + 7);
        v20 += 152;
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
                if ( *((float *)v4 + 1) - *(float *)(v8 - 56) > *(float *)(v8 + 20) )
                {
                  sub_4D4D30(v4, a2, v6);
                  *((_DWORD *)v4 + 4) = a2;
                  *((_DWORD *)v4 + 5) = v19;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
                *(_DWORD *)(*(_DWORD *)(v20 + *((_DWORD *)v4 + 3)) + v7 + 8) = 3;
                *(_DWORD *)(*(_DWORD *)(v20 + *((_DWORD *)v4 + 3)) + v7 + 16) = *((_DWORD *)v4 + 1);
LABEL_21:
                *((_DWORD *)v4 + 5) = v6;
                *((_DWORD *)v4 + 4) = a2;
LABEL_24:
                (*(void (**)(char *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v4 + 4))(
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
            if ( sub_4D4D70(v4, a2) )
            {
              v9 = *(_DWORD *)(v5 + 4);
              *(_DWORD *)(v5 + 12) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = *(_BYTE *)(v5 + 149);
              *(_DWORD *)(v5 + 20) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                ((CEffgbParticle *)v4)->Init(a2);
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = v19 + 1;
        v7 += 72;
        if ( ++v19 >= *((_DWORD *)v4 + 8) )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *(int *)&v2->_data[36] <= 0 )
      v2->_data[8] = 1;
    if ( !v2->_data[8] )
    {
      v12 = 0;
      if ( *(int *)&v2->_data[116] > 0 )
      {
        v13 = 0;
        do
        {
          *(_DWORD *)(v13 + *(_DWORD *)&v2->_data[52] + 36) = *(_DWORD *)&v2->_data[88];
          *(_DWORD *)(v13 + *(_DWORD *)&v2->_data[52] + 40) = *(_DWORD *)&v2->_data[136];
          sub_4CD3D0(*(_DWORD *)&v2->_data[52] + v13, arg0);
          ++v12;
          v13 += 56;
        }
        while ( v12 < *(_DWORD *)&v2->_data[116] );
      }
      if ( v2->_data[71] )
      {
        *(float *)&v2->_data[84] = *(float *)&v2->_data[144] * *(float *)&v2->_data[20] + *(float *)&v2->_data[84];
        if ( (g_bCursorVisible & 1) == 0 )
        {
          g_bCursorVisible |= 1u;
          ((CEffMgr *)&g_nCursorState)->Reset();
          atexit(nullsub_1);
        }
        v14 = 0;
        v15 = (int)abs32((int)*(float *)&v2->_data[84]) % (unsigned __int8)v2->_data[72];
        if ( *(int *)&v2->_data[116] > 0 )
        {
          v16 = 0;
          v17 = (char *)&v2->_data[16 * v15];
          do
          {
            ++v14;
            v16 += 68;
            *(_DWORD *)(v16 + *(_DWORD *)&v2->_data[48] - 20) = *(_DWORD *)&v2->_data[16 * v15 + 208];
            *(_DWORD *)(v16 + *(_DWORD *)&v2->_data[48] - 12) = *((_DWORD *)v17 + 54);
            *(_DWORD *)(v16 + *(_DWORD *)&v2->_data[48] - 16) = *((_DWORD *)v17 + 53);
            *(_DWORD *)(v16 + *(_DWORD *)&v2->_data[48] - 8) = *((_DWORD *)v17 + 55);
            *(_DWORD *)(v16 + *(_DWORD *)&v2->_data[48] - 4) = *(_DWORD *)&v2->_data[88];
          }
          while ( v14 < *(_DWORD *)&v2->_data[116] );
        }
      }
    }
  }
}
