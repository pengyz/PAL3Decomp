#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffExplosive.h"
#include "pal3/gen/CEffCallBack.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_4C7E60(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Co_13[];
extern char aNewFailInCeffe[];
extern unsigned char byte_DE99AC;
extern int dword_DE9980;
extern int dword_DE9984;
extern int dword_DE9988;
extern int dword_DE9990;
extern int dword_DE9994;
extern int dword_DE9998;
extern int dword_DE99A0;
extern int dword_DE99A4;
extern int dword_DE99A8;
extern int nullsub_1;
extern int nullsub_80;
extern int nullsub_81;
extern int nullsub_82;
extern int unk_5D4D3C;
extern int unk_5D4D7C;
extern int unk_5D4DAC;
extern int unk_5D4DB8;
extern int unk_5D4DC4;
extern int unk_5D4DCC;
extern int unk_5D4DD4;
extern int unk_5D4DF4;
extern int unk_5D4E00;
extern int unk_5D4E24;
extern int unk_5D4E30;
extern int unk_5D4E38;
extern int unk_5D4E40;
extern int unk_5D5038;
extern int unk_5D5040;
extern int unk_5D5048;
extern int unk_5D5050;
extern int unk_5D51A4;
extern int unk_5D51B0;
extern int unk_5D51BC;
extern int unk_5D51C8;
extern int unk_5D51D0;
extern int unk_5D51D8;
extern int unk_5D51EC;
extern int unk_5D51F8;
extern int unk_5D5204;
extern int unk_5D5210;
extern int unk_5D521C;
extern int unk_FFFFFF;

// 0x004C6C10
char CEffExplosive::Create(int a2)
{
  _DWORD *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // ebx
  _DWORD *v12; // eax
  int v13; // ebx
  int v14; // ebp
  int v15; // ebx
  int v16; // edi
  int v17; // ebx
  _DWORD *v18; // eax
  _DWORD *v19; // ecx
  int v20; // edx
  int v21; // ecx
  _DWORD *v23; // [esp+10h] [ebp-810h]
  char pExceptionObject[1024]; // [esp+14h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+414h] [ebp-40Ch] BYREF
  int v26; // [esp+81Ch] [ebp-4h]

  v3 = (_DWORD *)operator new(0x4C0u);
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
  *((_DWORD *)this + 27) = (__int64)*(float *)(a2 + 224);
  *((_DWORD *)this + 28) = (__int64)*(float *)(a2 + 232);
  *((_DWORD *)this + 29) = *(_DWORD *)(a2 + 228);
  *((_DWORD *)this + 31) = *(_DWORD *)(a2 + 244);
  *((_DWORD *)this + 32) = *(_DWORD *)(a2 + 248);
  *((_DWORD *)this + 33) = *(_DWORD *)(a2 + 252);
  *((_DWORD *)this + 34) = *(_DWORD *)(a2 + 256);
  v10 = *((_DWORD *)this + 27) * *((_DWORD *)this + 28);
  *((_DWORD *)this + 35) = *(_DWORD *)(a2 + 268);
  *((_DWORD *)this + 36) = *(_DWORD *)(a2 + 260);
  *((_DWORD *)this + 30) = v10;
  *((_DWORD *)this + 37) = *(_DWORD *)(a2 + 180);
  *((_DWORD *)this + 41) = *(_DWORD *)(a2 + 184);
  *((_DWORD *)this + 42) = *(_DWORD *)(a2 + 188);
  *((_DWORD *)this + 43) = *(_DWORD *)(a2 + 192);
  *((_DWORD *)this + 38) = *(_DWORD *)(a2 + 216);
  *((_DWORD *)this + 39) = *(_DWORD *)(a2 + 196);
  *((_DWORD *)this + 40) = *(_DWORD *)(a2 + 220);
  *((_DWORD *)this + 65) = *(CEffExplosive *)(a2 + 213);
  *((_DWORD *)this + 66) = *(CEffExplosive *)(a2 + 215);
  *((_DWORD *)this + 67) = *(CEffExplosive *)(a2 + 176);
  *((_DWORD *)this + 17) = &unk_FFFFFF;
  *((_DWORD *)this + 20) = *(_DWORD *)(a2 + 204);
  this->InitDefaultUVSet(*(_DWORD *)(a2 + 168), *(_DWORD *)(a2 + 172));
  v11 = *((_DWORD *)this + 30);
  v12 = (_DWORD *)operator new(68 * v11);
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
        ArraySort(v14, 12, 4, gbVec3D::`default constructor closure');
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
  *((_DWORD *)this + 12) = v12;
  v26 = -1;
  v18 = (_DWORD *)operator new(24 * v17);
  if ( v18 )
  {
    if ( v17 - 1 >= 0 )
    {
      v19 = (_DWORD *)v18 + 5;
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
  v21 = *((_DWORD *)this + 12);
  *((_DWORD *)this + 13) = v18;
  if ( !v21 || !v18 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffe, aDProjectPal3Co_13, 121),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->LoadTexture(a2 + 40);
  return 1;
}

// 0x004C6F20
void CEffExplosive::Destroy()
{
  char v2; // al
  bool v3; // zf
  _DWORD *v4; // eax
  struct gbRenderEffect *v5; // ebp
  gbMatrixStack *v6; // edi
  float v7; // [esp+3Ch] [ebp-Ch]
  float retaddr; // [esp+48h] [ebp+0h] BYREF

  if ( (byte_DE99AC & 1) == 0 )
  {
    dword_DE99A0 = 1065353216;
    byte_DE99AC |= 1u;
    dword_DE99A4 = 0;
    dword_DE99A8 = 0;
    atexit(nullsub_82);
  }
  if ( (byte_DE99AC & 2) == 0 )
  {
    dword_DE9990 = 0;
    byte_DE99AC |= 2u;
    dword_DE9994 = 1065353216;
    dword_DE9998 = 0;
    atexit(nullsub_81);
  }
  if ( (byte_DE99AC & 4) == 0 )
  {
    dword_DE9980 = 0;
    byte_DE99AC |= 4u;
    dword_DE9984 = 0;
    dword_DE9988 = 1065353216;
    atexit(nullsub_80);
  }
  if ( !*((_BYTE *)this + 8) && *((_BYTE *)this + 64) )
  {
    ((gbVertPoolMgr *)*(gbVertPoolMgr **)(**((_DWORD **)this + 1) + 196))->GetDynVertBuf(0x15u);
    v2 = *((_BYTE *)this + 65);
    if ( *((_BYTE *)this + 66) )
    {
      v3 = v2 == 0;
      v4 = (_DWORD *)*((_DWORD *)this + 1);
      if ( v3 )
        v5 = (struct gbRenderEffect *)v4[3];
      else
        v5 = (struct gbRenderEffect *)v4[2];
    }
    else
    {
      v3 = v2 == 0;
      v4 = (_DWORD *)*((_DWORD *)this + 1);
      if ( v3 )
        v5 = (struct gbRenderEffect *)v4[5];
      else
        v5 = (struct gbRenderEffect *)v4[4];
    }
    v6 = (gbMatrixStack *)*(gbMatrixStack **)(*v4 + 216);
    v6->Push();
    v7 = *((float *)this + 44) + *((float *)this + 41);
    retaddr = v7;
    v6->Translate((struct gbVec3D *)&retaddr);
    v6->Scale(*((float *)this + 25), 1.0, *((float *)this + 26));
    v6->Rotate(*((float *)this + 38), (struct gbVec3D *)&dword_DE99A0);
    v6->Rotate(*((float *)this + 39), (struct gbVec3D *)&dword_DE9990);
    v6->Rotate(*((float *)this + 40), (struct gbVec3D *)&dword_DE9980);
    ((gbDynVertBuf *)*((struct gbGeomQuad **)this + 12))->RenderGeomQuad(*((_DWORD *)this + 30), v5, *((struct gbTextureArray **)this + 15));
    v6->Pop();
  }
}

// 0x004C7680
int CEffExplosive::ProcCommonTask(int _94)
{
  double v3; // st7
  int v4; // edi
  int v5; // ecx
  double v6; // st7
  int v7; // ebp
  double v8; // st7
  unsigned __int16 v9; // cx
  float a3; // [esp+10h] [ebp-80h]
  int a3a; // [esp+10h] [ebp-80h]
  float a2; // [esp+24h] [ebp-6Ch]
  float v14; // [esp+28h] [ebp-68h]
  float v15; // [esp+2Ch] [ebp-64h]
  float v16; // [esp+30h] [ebp-60h]
  float v17; // [esp+34h] [ebp-5Ch]
  gbVec3D v18; // [esp+38h] [ebp-58h] BYREF
  struct gbVec3D v19; // [esp+44h] [ebp-4Ch] BYREF
  _BYTE v20[64]; // [esp+50h] [ebp-40h] BYREF

  v3 = *((float *)this + 4);
  v4 = *((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7);
  v5 = 9 * *((_DWORD *)this + 8);
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  a2 = *((float *)this + 5);
  if ( v6 > *(float *)(v7 + 24) )
    a2 = a2 - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    *(_DWORD *)(v7 + 44) = 0;
    *((_BYTE *)this + 64) = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  if ( *((float *)this + 4) - *(float *)(v7 + 16) > *(float *)(v4 + 84) && !*(_DWORD *)(v7 + 44) )
  {
    sub_4C7E60((int)this);
    *(_DWORD *)(v7 + 44) = 1;
  }
  *((float *)this + 38) = a2 * *(float *)(v4 + 64) + *((float *)this + 38);
  *((float *)this + 39) = a2 * *(float *)(v4 + 68) + *((float *)this + 39);
  *((float *)this + 40) = a2 * *(float *)(v4 + 72) + *((float *)this + 40);
  *((float *)this + 41) = a2 * *(float *)(v4 + 28) + *((float *)this + 41);
  *((float *)this + 42) = a2 * *(float *)(v4 + 32) + *((float *)this + 42);
  *((float *)this + 43) = a2 * *(float *)(v4 + 36) + *((float *)this + 43);
  ((gbMatrix4 *)v20)->gbMatrix4();
  memset(&v18, 0, sizeof(v18));
  memset(&v19, 0, sizeof(v19));
  ((gbMatrix4 *)v20)->LoadIdentity();
  v18 = *(gbVec3D *)(v4 + 44);
  ((gbVec3D *)&v18)->Normalize();
  a3 = (*((float *)this + 4) - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  ((gbMatrix4 *)v20)->SetAxisAngle(&v18, a3);
  v19.z = *(float *)(v4 + 56);
  v19.x = 0.0;
  v19.y = 0.0;
  ((gbMatrix4 *)v20)->Rotate(&v19, (struct gbVec3D *)(this + 176));
  if ( *(float *)(v4 + 80) != 0.0
    || *(float *)(v4 + 84) != 0.0
    || *(float *)(v4 + 92) != 0.0
    || *(float *)(v4 + 88) != 0.0 )
  {
    *((float *)this + 21) = a2 * *(float *)(v4 + 80) + *((float *)this + 21);
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( *((float *)this + 21) <= 255.0 )
    {
      if ( *((float *)this + 21) >= 0.0 )
        v8 = *((float *)this + 21);
      else
        v8 = 0.0;
    }
    else
    {
      v8 = 255.0;
    }
    *((float *)this + 21) = v8;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v14 = *((float *)this + 21) + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v15 = *((float *)this + 22) + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v16 = *((float *)this + 23) + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v17 = *((float *)this + 24) + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    HIBYTE(v9) = LOBYTE(v14);
    LOBYTE(v9) = LOBYTE(v15);
    *((_DWORD *)this + 20) = LOBYTE(v17) | ((LOBYTE(v16) | (v9 << 8)) << 8);
  }
  *((float *)this + 25) = a2 * *(float *)(v4 + 24) + *((float *)this + 25);
  *((float *)this + 26) = a2 * *(float *)(v4 + 108) + *((float *)this + 26);
  if ( *(_DWORD *)(v7 + 44) == 1 )
  {
    *(float *)&a3a = *((float *)this + 4) - *(float *)(v7 + 16);
    this->UpdateExplosive(a2, a3a);
  }
  if ( *(_BYTE *)(v7 + 66) == 1 || *((float *)this + 4) - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
    *(_DWORD *)(v7 + 8) = 4;
  return 0;
}

// 0x004C7A70
void * CEffExplosive::GetEditorTaskDescription(int a1)
{
  void *result; // eax

  switch ( a1 )
  {
    case 0:
      result = (void *)&unk_5D5050;
      break;
    case 1:
      result = (void *)&unk_5D4E40;
      break;
    case 2:
      result = (void *)&unk_5D4E38;
      break;
    case 3:
      result = (void *)&unk_5D4E30;
      break;
    case 4:
      result = (void *)&unk_5D4E24;
      break;
    case 5:
      result = (void *)&unk_5D5048;
      break;
    case 6:
      result = (void *)&unk_5D5040;
      break;
    case 7:
      result = (void *)&unk_5D5038;
      break;
    case 8:
      result = (void *)&unk_5D4E00;
      break;
    case 9:
      result = (void *)&unk_5D4DF4;
      break;
    case 10:
      result = (void *)&unk_5D51B0;
      break;
    case 12:
      result = (void *)&unk_5D4DD4;
      break;
    case 13:
      result = (void *)&unk_5D4DCC;
      break;
    case 14:
      result = (void *)&unk_5D4DC4;
      break;
    case 15:
      result = (void *)&unk_5D4DB8;
      break;
    case 16:
      result = (void *)&unk_5D4DAC;
      break;
    case 17:
      result = (void *)&unk_5D51A4;
      break;
    case 20:
      result = (void *)&unk_5D4D7C;
      break;
    default:
      result = (void *)&unk_5D4D3C;
      break;
  }
  return result;
}

// 0x004C7B70
void * CEffExplosive::GetEditorObjDescription(int a1)
{
  void *result; // eax

  switch ( a1 )
  {
    case 0:
      result = (void *)&unk_5D521C;
      break;
    case 1:
      result = (void *)&unk_5D5210;
      break;
    case 2:
      result = (void *)&unk_5D5204;
      break;
    case 3:
      result = (void *)&unk_5D51F8;
      break;
    case 4:
      result = (void *)&unk_5D51EC;
      break;
    case 5:
      result = (void *)&CTaskTpl<tagEffTaskParam,unsigned long (CEffCallBack::*)(unsigned long)>::DelTask;
      break;
    case 6:
      result = (void *)&unk_5D51D8;
      break;
    case 7:
      result = (void *)&unk_5D51D0;
      break;
    case 8:
      result = (void *)&unk_5D51C8;
      break;
    case 9:
      result = (void *)&unk_5D51BC;
      break;
    default:
      result = (void *)&unk_5D4D3C;
      break;
  }
  return result;
}

// 0x004C7C00
void CEffExplosive::InitDefaultUVSet(int a2, int a3)
{
  int v3; // ebx
  CEffExplosive *v4; // edi
  int v5; // ecx
  double v6; // st7
  CEffExplosive *v7; // eax
  double v8; // st5
  double v9; // st5
  double v10; // st3
  double v11; // st3
  int v12; // [esp+8h] [ebp-8h]
  float v13; // [esp+8h] [ebp-8h]
  int v14; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v12 = 0;
  if ( a3 > 0 )
  {
    v4 = (CEffExplosive *)this + 200;
    do
    {
      v5 = 0;
      v14 = 0;
      if ( a2 > 0 )
      {
        v6 = (double)a2;
        v7 = v4;
        v4 += 16 * a2;
        v8 = (double)a3;
        v13 = (double)v12 / v8;
        v9 = 1.0 - (1.0 / v8 + v13);
        do
        {
          v10 = (double)v14;
          v7 += 16;
          v14 = ++v5;
          v11 = v10 / v6;
          *(float *)&v7[-24] = v11;
          *(float *)&v7[-16] = 1.0 / v6 + v11;
          *(float *)&v7[-20] = v9;
          *(float *)&v7[-12] = 1.0 - v13;
        }
        while ( v5 < a2 );
      }
      v12 = ++v3;
    }
    while ( v3 < a3 );
  }
}

// 0x004C7CB0
_DWORD * CEffExplosive::LoadTexture(int a2)
{
  gbTexture *v3; // eax
  _DWORD *result; // eax
  int v5; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(***((_DWORD ***)this + 1) + 8))(**((_DWORD **)this + 1), a2);
  *((_DWORD *)this + 14) = v3;
  v3->LoadTexture(1);
  result = (_DWORD *)operator new(0x44u);
  if ( result )
  {
    v5 = *((_DWORD *)this + 14);
    result[16] = 1;
    *result = v5;
  }
  else
  {
    result = 0;
  }
  *((_DWORD *)this + 15) = result;
  if ( !result )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_13, 499),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004C7D40
int CEffExplosive::CreateGeom()
{
  int v1; // edx
  int result; // eax
  int v3; // ebx
  int v4; // ebp
  double i; // st7
  double v6; // st6
  int v7; // esi
  int v8; // eax
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  double v14; // st5
  float *v15; // edx
  float v16; // [esp+8h] [ebp-4h]

  v1 = *((_DWORD *)this + 27);
  result = *((_DWORD *)this + 28);
  v3 = 0;
  v4 = 0;
  v16 = (double)v1 * *((float *)this + 29) * -0.5;
  for ( i = (double)result * *((float *)this + 29) * 0.5; v4 < result; i = i - *((float *)this + 29) )
  {
    v6 = v16;
    v7 = 0;
    if ( v1 > 0 )
    {
      v8 = 68 * v3;
      do
      {
        v9 = *((_DWORD *)this + 12);
        *(_DWORD *)(v9 + v8 + 4) = 0;
        *(float *)(v9 + v8) = v6;
        ++v3;
        *(float *)(v8 + v9 + 8) = i;
        v10 = *((_DWORD *)this + 12);
        *(_DWORD *)(v10 + v8 + 16) = 0;
        *(float *)(v10 + v8 + 12) = v6;
        *(float *)(v10 + v8 + 20) = i;
        *(float *)(*((_DWORD *)this + 12) + v8 + 12) = *(float *)(*((_DWORD *)this + 12) + v8 + 12)
                                                     + *((float *)this + 29);
        v11 = *((_DWORD *)this + 12);
        *(_DWORD *)(v11 + v8 + 28) = 0;
        *(float *)(v11 + v8 + 24) = v6;
        *(float *)(v11 + v8 + 32) = i;
        *(float *)(*((_DWORD *)this + 12) + v8 + 24) = *(float *)(*((_DWORD *)this + 12) + v8 + 24)
                                                     + *((float *)this + 29);
        *(float *)(*((_DWORD *)this + 12) + v8 + 32) = *(float *)(*((_DWORD *)this + 12) + v8 + 32)
                                                     - *((float *)this + 29);
        v12 = *((_DWORD *)this + 12);
        *(_DWORD *)(v12 + v8 + 40) = 0;
        *(float *)(v12 + v8 + 36) = v6;
        *(float *)(v12 + v8 + 44) = i;
        v13 = *((_DWORD *)this + 12);
        v14 = *(float *)(v13 + v8 + 44) - *((float *)this + 29);
        v15 = (float *)(v13 + v8 + 44);
        v8 += 68;
        ++v7;
        *v15 = v14;
        v1 = *((_DWORD *)this + 27);
        v6 = v6 + *((float *)this + 29);
      }
      while ( v7 < v1 );
    }
    result = *((_DWORD *)this + 28);
    ++v4;
  }
  return result;
}

// 0x004C8370
int CEffExplosive::UpdateExplosive(float a2, int a3)
{
  int result; // eax
  int v5; // ebp
  int v6; // edi
  int v7; // ebp
  float *v8; // eax
  double v9; // st7
  int v10; // ecx
  float *v11; // eax
  int v12; // edx
  float *v13; // eax
  int v14; // eax
  double v15; // st6
  float *v16; // eax
  int v17; // ecx
  int v18; // eax
  double v19; // st7
  float *v20; // eax
  int v21; // ecx
  float *v22; // eax
  int v23; // edx
  float *v24; // eax
  int v25; // eax
  double v26; // st7
  float *v27; // eax
  int v28; // edx
  bool v29; // cc
  float v30; // [esp+4h] [ebp-90h]
  float v31; // [esp+8h] [ebp-8Ch]
  float v32; // [esp+Ch] [ebp-88h]
  int v33; // [esp+20h] [ebp-74h]
  int v34; // [esp+24h] [ebp-70h]
  int v35; // [esp+28h] [ebp-6Ch]
  float v36; // [esp+2Ch] [ebp-68h]
  float v37; // [esp+30h] [ebp-64h]
  float v38; // [esp+30h] [ebp-64h]
  float v39; // [esp+34h] [ebp-60h]
  float v40; // [esp+34h] [ebp-60h]
  float v41; // [esp+3Ch] [ebp-58h]
  float v42; // [esp+40h] [ebp-54h]
  gbQuaternion v43; // [esp+44h] [ebp-50h] BYREF
  _BYTE v44[64]; // [esp+54h] [ebp-40h] BYREF

  memset(&v43, 0, 12);
  v43.w = 1.0;
  ((gbMatrix4 *)v44)->gbMatrix4();
  result = *((_DWORD *)this + 27);
  v5 = 0;
  v33 = 0;
  v35 = 0;
  if ( result > 0 )
  {
    do
    {
      v34 = 0;
      if ( *((int *)this + 28) > 0 )
      {
        v6 = 68 * v5;
        v7 = 24 * v5;
        do
        {
          v8 = (float *)(v6 + *((_DWORD *)this + 12));
          v9 = (v8[9] + v8[6] + v8[3] + *v8) * 0.25;
          v37 = (v8[10] + v8[7] + v8[4] + v8[1]) * 0.25;
          v39 = (v8[11] + v8[8] + v8[5] + v8[2]) * 0.25;
          * v8 = (*)*v8 - v9;
          v8[1] = v8[1] - v37;
          v8[2] = v8[2] - v39;
          v10 = *((_DWORD *)this + 12);
          v11 = (float *)(v10 + v6 + 12);
          * v11 = (*)*v11 - v9;
          v11[1] = *(float *)(v10 + v6 + 16) - v37;
          v11[2] = *(float *)(v10 + v6 + 20) - v39;
          v12 = *((_DWORD *)this + 12);
          v13 = (float *)(v12 + v6 + 24);
          * v13 = (*)*v13 - v9;
          v13[1] = *(float *)(v12 + v6 + 28) - v37;
          v13[2] = *(float *)(v12 + v6 + 32) - v39;
          v14 = *((_DWORD *)this + 12);
          v15 = *(float *)(v14 + v6 + 36);
          v16 = (float *)(v14 + v6 + 36);
          * v16 = (*)v15 - v9;
          v16[1] = v16[1] - v37;
          v16[2] = v16[2] - v39;
          v17 = *((_DWORD *)this + 13);
          v41 = a2 * *(float *)(v17 + v7 + 4);
          v42 = a2 * *(float *)(v17 + v7 + 8);
          v36 = a2 * *(float *)(v17 + v7) + v9;
          v38 = v41 + v37;
          v40 = v42 + v39;
          v32 = a2 * *(float *)(v17 + v7 + 20);
          v31 = a2 * *(float *)(v17 + v7 + 16);
          v30 = a2 * *(float *)(v17 + v7 + 12);
          ((gbQuaternion *)&v43)->SetYawPitchRoll(v30, v31, v32);
          ((gbQuaternion *)&v43)->GetMatrix((struct gbMatrix4 *)v44);
          ((gbMatrix4 *)v44)->RotateIn((struct gbVec3D *)(v6 + *((_DWORD *)this + 12)));
          ((gbMatrix4 *)v44)->RotateIn((struct gbVec3D *)(*((_DWORD *)this + 12) + v6 + 12));
          ((gbMatrix4 *)v44)->RotateIn((struct gbVec3D *)(*((_DWORD *)this + 12) + v6 + 24));
          ((gbMatrix4 *)v44)->RotateIn((struct gbVec3D *)(*((_DWORD *)this + 12) + v6 + 36));
          v18 = *((_DWORD *)this + 12);
          v19 = v36 + *(float *)(v18 + v6);
          v20 = (float *)(v6 + v18);
          *v20 = v19;
          v20[1] = v38 + v20[1];
          v20[2] = v40 + v20[2];
          v21 = *((_DWORD *)this + 12);
          v22 = (float *)(v21 + v6 + 12);
          * v22 = (*)v36 + *v22;
          v22[1] = v38 + *(float *)(v21 + v6 + 16);
          v22[2] = v40 + *(float *)(v21 + v6 + 20);
          v23 = *((_DWORD *)this + 12);
          v24 = (float *)(v23 + v6 + 24);
          * v24 = (*)v36 + *v24;
          v24[1] = v38 + *(float *)(v23 + v6 + 28);
          v24[2] = v40 + *(float *)(v23 + v6 + 32);
          v25 = *((_DWORD *)this + 12);
          v26 = v36 + *(float *)(v25 + v6 + 36);
          v27 = (float *)(v25 + v6 + 36);
          *v27 = v26;
          v7 += 24;
          v6 += 68;
          v27[1] = v38 + v27[1];
          v27[2] = v40 + v27[2];
          v28 = v33 + 1;
          v29 = ++v34 < *((_DWORD *)this + 28);
          ++v33;
        }
        while ( v29 );
        v5 = v28;
      }
      result = ++v35;
    }
    while ( v35 < *((_DWORD *)this + 27) );
  }
  return result;
}
