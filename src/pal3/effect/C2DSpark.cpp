#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/C2DSpark.h"

// Forward declarations for unnamed functions
int sub_4D5AB0(...);
int sub_4D5DC0(...);
int sub_4D5EC0(...);
int sub_4D5F20(...);
int sub_4D5F40(...);
int sub_4D6050(...);
int sub_4D61A0(...);
int sub_4D61C0(...);
int sub_4D6380(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Co_10[];
extern char aEffectFlare2Bm[];
extern char aEffectFlare3Bm[];
extern char aEffectFlareblu[];
extern char aEffectFlarebri[];
extern char aEffectFlaregre[];
extern char aGfxscriptTlAdd[];
extern unsigned char byte_17A8148;
extern unsigned char byte_17A8178;
extern unsigned char byte_17A81A8;
extern int dword_17A8130;
extern int dword_17A8134;
extern int dword_17A8138;
extern int dword_17A813C;
extern int dword_17A8140;
extern int dword_17A8144;
extern int dword_17A8158;
extern int dword_17A815C;
extern int dword_17A8160;
extern int dword_17A8164;
extern int dword_17A8168;
extern int dword_17A816C;
extern int dword_17A8170;
extern int dword_17A8174;
extern int dword_17A8190;
extern int dword_17A8194;
extern int dword_17A8198;
extern int dword_17A819C;
extern int dword_17A81A0;
extern int dword_17A81A4;
extern float flt_17A8120;
extern float flt_17A8124;
extern float flt_17A8128;
extern float flt_17A812C;
extern float flt_17A8150;
extern float flt_17A8154;
extern float flt_17A8180;
extern float flt_17A8184;
extern float flt_17A8188;
extern float flt_17A818C;

// 0x004D5AB0
int sub_4D5AB0(int _this, int a2, int a3)
{
  gbTexture *v4; // eax
  _DWORD *v5; // eax
  int v6; // ecx
  gbTexture *v7; // eax
  _DWORD *v8; // eax
  int v9; // ecx
  gbTexture *v10; // eax
  _DWORD *v11; // eax
  int v12; // ecx
  gbTexture *v13; // eax
  _DWORD *v14; // eax
  int v15; // ecx
  gbTexture *v16; // eax
  _DWORD *v17; // eax
  int v18; // ecx
  _BYTE v20[1056]; // [esp+30h] [ebp-800h] BYREF
  char ArgList; // [esp+450h] [ebp-3E0h] BYREF

  *(_DWORD *)(this + 22636) = -1;
  *(_DWORD *)(this + 22632) = 0;
  memset((void *)this, 0, 0x5870u);
  *(float *)(this + 22528) = (float)a2;
  *(float *)(this + 22532) = (float)a3;
  *(_BYTE *)(this + 22552) = 0;
  *(_DWORD *)(this + 22556) = gbEffectMgr::NewRenderEffect(
                                *(gbEffectMgr **)(g_pGfxManager + 200),
                                aGfxscriptTlAdd,
                                0);
  v4 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      aEffectFlare3Bm);
  *(_DWORD *)&v20[12] = 1;
  *(_DWORD *)(this + 22560) = v4;
  v4->LoadTexture(*(_DWORD *)&v20[12]);
  v5 = operator new(0x44u);
  if ( v5 )
  {
    v6 = *(_DWORD *)(this + 22560);
    v5[16] = 1;
    *v5 = v6;
  }
  else
  {
    v5 = 0;
  }
  *(_DWORD *)(this + 22564) = v5;
  if ( !v5 )
  {
    qmemcpy(
      &v20[32],
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_10, 41),
      0x400u);
    _CxxThrowException(&v20[32], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      aEffectFlare2Bm);
  *(_DWORD *)&v20[8] = 1;
  *(_DWORD *)(this + 22584) = v7;
  v7->LoadTexture(*(_DWORD *)&v20[8]);
  v8 = operator new(0x44u);
  if ( v8 )
  {
    v9 = *(_DWORD *)(this + 22584);
    v8[16] = 1;
    *v8 = v9;
  }
  else
  {
    v8 = 0;
  }
  *(_DWORD *)(this + 22588) = v8;
  if ( !v8 )
  {
    qmemcpy(
      &v20[24],
      (const void *)Logger::FormatException((char)&v20[1048], (int)aCNewFailed_0, (int)aDProjectPal3Co_10, 46),
      0x400u);
    _CxxThrowException(&v20[24], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                       g_pGfxManager,
                       aEffectFlaregre);
  *(_DWORD *)v20 = 1;
  *(_DWORD *)(this + 22576) = v10;
  v10->LoadTexture(*(_DWORD *)v20);
  v11 = operator new(0x44u);
  if ( v11 )
  {
    v12 = *(_DWORD *)(this + 22576);
    v11[16] = 1;
    *v11 = v12;
  }
  else
  {
    v11 = 0;
  }
  *(_DWORD *)(this + 22580) = v11;
  if ( !*(_DWORD *)(this + 22588) )
  {
    qmemcpy(
      &v20[16],
      (const void *)Logger::FormatException((char)&v20[1040], (int)aCNewFailed_0, (int)aDProjectPal3Co_10, 51),
      0x400u);
    _CxxThrowException(&v20[16], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v13 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                       g_pGfxManager,
                       aEffectFlareblu);
  *(_DWORD *)(this + 22568) = v13;
  v13->LoadTexture(1);
  v14 = operator new(0x44u);
  if ( v14 )
  {
    v15 = *(_DWORD *)(this + 22568);
    v14[16] = 1;
    *v14 = v15;
  }
  else
  {
    v14 = 0;
  }
  *(_DWORD *)(this + 22572) = v14;
  if ( !v14 )
  {
    qmemcpy(
      &v20[8],
      (const void *)Logger::FormatException((char)&v20[1032], (int)aCNewFailed_0, (int)aDProjectPal3Co_10, 56),
      0x400u);
    _CxxThrowException(&v20[8], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v16 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                       g_pGfxManager,
                       aEffectFlarebri);
  *(_DWORD *)(this + 22592) = v16;
  v16->LoadTexture(1);
  v17 = operator new(0x44u);
  if ( v17 )
  {
    v18 = *(_DWORD *)(this + 22592);
    v17[16] = 1;
    *v17 = v18;
  }
  else
  {
    v17 = 0;
  }
  *(_DWORD *)(this + 22596) = v17;
  if ( !v17 )
  {
    qmemcpy(
      v20,
      (const void *)Logger::FormatException((char)&v20[1024], (int)aCNewFailed_0, (int)aDProjectPal3Co_10, 61),
      0x400u);
    _CxxThrowException(v20, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *(_DWORD *)(this + 22636) = -1;
  *(_DWORD *)(this + 22628) = 1065353216;
  *(_DWORD *)(this + 22624) = 1065353216;
  *(_DWORD *)(this + 22620) = 0;
  *(_DWORD *)(this + 22616) = 0;
  *(_DWORD *)(this + 22632) = 1056964608;
  return this;
}

// 0x004D5DC0
void sub_4D5DC0(int _this)
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  gbRefObject *v4; // ecx
  gbRefObject *v5; // ecx
  gbRefObject *v6; // ecx
  gbRefObject *v7; // ecx

  v2 = *(gbRefObject **)(this + 22556);
  if ( v2 )
  {
    v2->Release();
    *(_DWORD *)(this + 22556) = 0;
  }
  v3 = *(gbRefObject **)(this + 22560);
  if ( v3 )
  {
    v3->Release();
    *(_DWORD *)(this + 22560) = 0;
  }
  v4 = *(gbRefObject **)(this + 22576);
  if ( v4 )
  {
    v4->Release();
    *(_DWORD *)(this + 22576) = 0;
  }
  v5 = *(gbRefObject **)(this + 22568);
  if ( v5 )
  {
    v5->Release();
    *(_DWORD *)(this + 22568) = 0;
  }
  v6 = *(gbRefObject **)(this + 22584);
  if ( v6 )
  {
    v6->Release();
    *(_DWORD *)(this + 22584) = 0;
  }
  v7 = *(gbRefObject **)(this + 22592);
  if ( v7 )
  {
    v7->Release();
    *(_DWORD *)(this + 22592) = 0;
  }
  if ( *(_DWORD *)(this + 22564) )
  {
    operator delete(*(void **)(this + 22564));
    *(_DWORD *)(this + 22564) = 0;
  }
  if ( *(_DWORD *)(this + 22580) )
  {
    operator delete(*(void **)(this + 22580));
    *(_DWORD *)(this + 22580) = 0;
  }
  if ( *(_DWORD *)(this + 22572) )
  {
    operator delete(*(void **)(this + 22572));
    *(_DWORD *)(this + 22572) = 0;
  }
  if ( *(_DWORD *)(this + 22588) )
  {
    operator delete(*(void **)(this + 22588));
    *(_DWORD *)(this + 22588) = 0;
  }
  if ( *(_DWORD *)(this + 22596) )
  {
    operator delete(*(void **)(this + 22596));
    *(_DWORD *)(this + 22596) = 0;
  }
}

// 0x004D5EC0
char sub_4D5EC0(const void *a2)
{
  int v3; // eax
  _BYTE *i; // ecx

  v3 = 0;
  for ( i = (char *)this + 41; *i; i += 44 )
  {
    if ( ++v3 >= 512 )
      return 0;
  }
  qmemcpy(this + 11 * v3, a2, 0x2Cu);
  *((_BYTE *)this + 44 * v3 + 41) = 1;
  if ( v3 >= *((_DWORD *)this + 5634) )
    *((_DWORD *)this + 5634) = v3 + 1;
  return 1;
}

// 0x004D5F20
char sub_4D5F20(int _this, char a2)
{
  *(_DWORD *)(this + 22540) = 0;
  *(_BYTE *)(this + 22552) = a2;
  return a2;
}

// 0x004D5F40
int sub_4D5F40(int a2, int a3)
{
  int v4; // edi
  long double v5; // st7
  float v7; // [esp+0h] [ebp-8h]

  dword_17A81A0 = 1098907648;
  dword_17A8198 = 1128792064;
  dword_17A8190 = 0;
  dword_17A8194 = 1145569280;
  dword_17A819C = -1011941376;
  dword_17A81A4 = 0;
  flt_17A8180 = (double)a2 - 8.0;
  v4 = 0;
  flt_17A8184 = (double)a3 - 8.0;
  do
  {
    byte_17A81A8 = rand() & 3;
    v7 = (float)(rand() % 300);
    v5 = (double)(rand() % 5760 / 16) * 0.017453292;
    flt_17A8188 = sin(v5) * v7;
    flt_17A818C = cos(v5) * v7;
    if ( !this->CreateSingle(&flt_17A8180) )
      break;
    ++v4;
  }
  while ( v4 < 60 );
  *((_DWORD *)this + 5635) = 1132068864;
  *((_DWORD *)this + 5636) = a2;
  *((_DWORD *)this + 5637) = a3;
  return a3;
}

// 0x004D6050
char sub_4D6050(int a2, int a3, int a4, int a5)
{
  double v5; // st7
  double v7; // st7
  float v9; // [esp+0h] [ebp-4h]
  float v10; // [esp+8h] [ebp+4h]
  float v11; // [esp+Ch] [ebp+8h]

  v5 = *(float *)&a5 * 0.5;
  dword_17A8170 = a5;
  dword_17A8168 = 1128792064;
  dword_17A8158 = 0;
  dword_17A815C = -1054867456;
  dword_17A8160 = 0;
  dword_17A8164 = -1035468800;
  v9 = (double)a2 - v5;
  dword_17A816C = -1027080192;
  dword_17A8174 = 0;
  byte_17A8178 = 2;
  v11 = (double)a3 - v5;
  *(float *)&dword_17A8168 = 250.0 - (double)(rand() % 50);
  v10 = (float)a4;
  flt_17A8150 = (double)(rand() % a4) + v9 - v10 * 0.5;
  flt_17A8154 = (double)(rand() % (2 * a4)) + v11 - v10;
  if ( *(float *)&a5 >= 19.0 )
    v7 = (double)-(rand() % 100);
  else
    v7 = (double)-(rand() % 50);
  *(float *)&dword_17A8164 = v7;
  return this->CreateSingle(&flt_17A8150);
}

// 0x004D61A0
_BYTE * sub_4D61A0()
{
  _BYTE *result; // eax
  int v2; // edx

  result = (char *)this + 41;
  v2 = 512;
  do
  {
    *result = 0;
    result += 44;
    --v2;
  }
  while ( v2 );
  *((_DWORD *)this + 5634) = 0;
  return result;
}

// 0x004D61C0
int sub_4D61C0(int _this)
{
  gbDynVertBuf *DynVertBuf; // ebx
  LONG y; // ecx
  LONG x; // eax
  double v5; // st7
  double v6; // st7
  struct gbRenderEffect *v7; // ecx
  int result; // eax
  int v9; // edi
  struct gbTextureArray *v10; // ecx
  struct gbRenderEffect *v11; // ecx
  int v12; // ecx
  struct gbTextureArray *v13; // [esp-4h] [ebp-20h]
  struct tagPOINT Point; // [esp+Ch] [ebp-10h] BYREF
  float v15; // [esp+14h] [ebp-8h]
  int v16; // [esp+18h] [ebp-4h]

  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x114u);
  if ( *(float *)(this + 22540) > 2.0 )
  {
    GRPinput::GetCursorPos(&Point);
    if ( *(_BYTE *)(this + 22552) )
    {
      GetCursorPos(&Point);
      y = Point.y;
      x = Point.x;
    }
    else
    {
      x = *(_DWORD *)(this + 22544);
      y = *(_DWORD *)(this + 22548);
      Point.x = x;
      Point.y = y;
    }
    v16 = y - 64;
    *(float *)(this + 22600) = (float)(x - 64);
    v5 = (double)v16;
    v16 = x + 64;
    *(float *)(this + 22604) = v5;
    v6 = (double)v16;
    v16 = y + 64;
    *(float *)(this + 22608) = v6;
    *(float *)(this + 22612) = (float)v16;
    v7 = *(struct gbRenderEffect **)(this + 22556);
    *(_BYTE *)(this + 22639) = (__int64)*(float *)(this + 22540);
    DynVertBuf->RenderUIQuad((struct gbUIQuad *)(this + 22600),
      1,
      v7,
      *(struct gbTextureArray **)(this + 22564));
  }
  result = *(_DWORD *)(this + 22536);
  v16 = 0;
  if ( result > 0 )
  {
    v9 = this + 32;
    do
    {
      if ( *(_BYTE *)(v9 + 9) )
      {
        result = *(unsigned __int8 *)(v9 + 8);
        switch ( *(_BYTE *)(v9 + 8) )
        {
          case 0:
            v10 = *(struct gbTextureArray **)(this + 22588);
            goto LABEL_14;
          case 1:
            v10 = *(struct gbTextureArray **)(this + 22580);
            goto LABEL_14;
          case 2:
            v10 = *(struct gbTextureArray **)(this + 22572);
            goto LABEL_14;
          case 3:
            v10 = *(struct gbTextureArray **)(this + 22596);
LABEL_14:
            *(_DWORD *)(this + 22600) = *(_DWORD *)(v9 - 32);
            *(_DWORD *)(this + 22604) = *(_DWORD *)(v9 - 28);
            *(float *)(this + 22608) = *(float *)v9 + *(float *)(v9 - 32);
            *(float *)(this + 22612) = *(float *)v9 + *(float *)(v9 - 28);
            v15 = *(float *)(v9 - 8);
            Point.y = (int)v15;
            v13 = v10;
            v11 = *(struct gbRenderEffect **)(this + 22556);
            *(_BYTE *)(this + 22639) = Point.y;
            DynVertBuf->RenderUIQuad((struct gbUIQuad *)(this + 22600), 1, v11, v13);
            break;
          default:
            return result;
        }
      }
      v12 = *(_DWORD *)(this + 22536);
      result = v16 + 1;
      v9 += 44;
      ++v16;
    }
    while ( v16 < v12 );
  }
  return result;
}

// 0x004D6380
int sub_4D6380(int _this, float a2)
{
  int v3; // edi
  int v4; // eax
  __int64 v5; // rax
  int v6; // ecx
  struct tagPOINT Point; // [esp+8h] [ebp-Ch] BYREF
  int v9; // [esp+10h] [ebp-4h]

  if ( *(_BYTE *)(this + 22552) )
  {
    GRPinput::GetCursorPos(&Point);
    if ( Point.x != (_DWORD)qword_17A8438 || Point.y != HIDWORD(qword_17A8438) )
    {
      dword_17A8140 = 1098907648;
      dword_17A8138 = 1125842944;
      v3 = 5;
      flt_17A8120 = (double)Point.x - 8.0;
      flt_17A8124 = (double)Point.y - 8.0;
      do
      {
        rand();
        byte_17A8148 = 0;
        v9 = rand() % 100;
        flt_17A8128 = ((double)v9 - 50.0) * 2.5;
        v4 = rand();
        dword_17A8130 = 0;
        dword_17A8134 = 1145569280;
        dword_17A813C = -1011941376;
        dword_17A8144 = 0;
        v9 = v4 % 100;
        flt_17A812C = ((double)(v4 % 100) - 50.0) * 2.5;
        (_DWORD *->CreateSingle()this, &flt_17A8120);
        --v3;
      }
      while ( v3 );
      qword_17A8438 = (__int64)Point;
      v9 = (unsigned __int8)rand();
      *(float *)(this + 22540) = (float)v9;
    }
  }
  if ( *(float *)(this + 22540) > 2.0 )
    *(float *)(this + 22540) = *(float *)(this + 22540) - a2 * 200.0;
  v5 = *(unsigned int *)(this + 22536);
  if ( (int)v5 > 0 )
  {
    v6 = this + 8;
    do
    {
      if ( *(_BYTE *)(v6 + 33) )
      {
        *(float *)v6 = a2 * *(float *)(v6 + 8) + *(float *)v6;
        *(float *)(v6 + 4) = a2 * *(float *)(v6 + 12) + *(float *)(v6 + 4);
        *(float *)(v6 - 8) = a2 * *(float *)v6 + *(float *)(v6 - 8);
        *(float *)(v6 - 4) = a2 * *(float *)(v6 + 4) + *(float *)(v6 - 4);
        *(float *)(v6 + 16) = a2 * *(float *)(v6 + 20) + *(float *)(v6 + 16);
        *(float *)&v9 = a2 * *(float *)(v6 + 28) + *(float *)(v6 + 24);
        *(float *)(v6 + 24) = *(float *)&v9;
        if ( *(float *)(v6 - 8) >= (double)*(float *)(this + 22528)
          || (*(float *)&Point.x = -*(float *)&v9, *(float *)(v6 - 8) <= (double)*(float *)&Point.x)
          || *(float *)(v6 - 4) >= (double)*(float *)(this + 22532)
          || *(float *)(v6 - 4) <= (double)*(float *)&Point.x
          || *(float *)(v6 + 16) <= 1.0
          || *(float *)(v6 + 16) > 255.0
          || *(float *)&v9 < 0.0099999998 )
        {
          *(_BYTE *)(v6 + 33) = 0;
          LODWORD(v5) = *(_DWORD *)(this + 22536) - 1;
          if ( HIDWORD(v5) == (_DWORD)v5 )
            *(_DWORD *)(this + 22536) = v5;
        }
      }
      LODWORD(v5) = *(_DWORD *)(this + 22536);
      ++HIDWORD(v5);
      v6 += 44;
    }
    while ( SHIDWORD(v5) < (int)v5 );
  }
  return v5;
}
