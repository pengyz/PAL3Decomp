#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/C2DSpark.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/Logger.h"

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
C2DSpark::C2DSpark(int a2, int a3)
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
  char ArgList[992]; // [esp+450h] [ebp-3E0h] BYREF

  *(_DWORD *)&this->_data[22636] = -1;
  *(_DWORD *)&this->_data[22632] = 0;
  memset(this, 0, sizeof(C2DSpark));
  *(float *)&this->_data[22528] = (float)a2;
  *(float *)&this->_data[22532] = (float)a3;
  this->_data[22552] = 0;
  *(_DWORD *)&this->_data[22556] = ((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptTlAdd, 0);
  v4 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                      g_pGfxMgr,
                      aEffectFlare3Bm);
  *(_DWORD *)&v20[12] = 1;
  *(_DWORD *)&this->_data[22560] = v4;
  v4->LoadTexture(*(_DWORD *)&v20[12]);
  v5 = (_DWORD *)operator new(0x44u);
  if ( v5 )
  {
    v6 = *(_DWORD *)&this->_data[22560];
    v5[16] = 1;
    *v5 = v6;
  }
  else
  {
    v5 = 0;
  }
  *(_DWORD *)&this->_data[22564] = v5;
  if ( !v5 )
  {
    qmemcpy(&v20[32], ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 41), 0x400u);
    _CxxThrowException(&v20[32], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                      g_pGfxMgr,
                      aEffectFlare2Bm);
  *(_DWORD *)&v20[8] = 1;
  *(_DWORD *)&this->_data[22584] = v7;
  v7->LoadTexture(*(_DWORD *)&v20[8]);
  v8 = (_DWORD *)operator new(0x44u);
  if ( v8 )
  {
    v9 = *(_DWORD *)&this->_data[22584];
    v8[16] = 1;
    *v8 = v9;
  }
  else
  {
    v8 = 0;
  }
  *(_DWORD *)&this->_data[22588] = v8;
  if ( !v8 )
  {
    qmemcpy(&v20[24], ((Logger *)&v20[1048])->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 46), 0x400u);
    _CxxThrowException(&v20[24], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                       g_pGfxMgr,
                       aEffectFlaregre);
  *(_DWORD *)v20 = 1;
  *(_DWORD *)&this->_data[22576] = v10;
  v10->LoadTexture(*(_DWORD *)v20);
  v11 = (_DWORD *)operator new(0x44u);
  if ( v11 )
  {
    v12 = *(_DWORD *)&this->_data[22576];
    v11[16] = 1;
    *v11 = v12;
  }
  else
  {
    v11 = 0;
  }
  *(_DWORD *)&this->_data[22580] = v11;
  if ( !*(_DWORD *)&this->_data[22588] )
  {
    qmemcpy(&v20[16], ((Logger *)&v20[1040])->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 51), 0x400u);
    _CxxThrowException(&v20[16], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v13 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                       g_pGfxMgr,
                       aEffectFlareblu);
  *(_DWORD *)&this->_data[22568] = v13;
  v13->LoadTexture(1);
  v14 = (_DWORD *)operator new(0x44u);
  if ( v14 )
  {
    v15 = *(_DWORD *)&this->_data[22568];
    v14[16] = 1;
    *v14 = v15;
  }
  else
  {
    v14 = 0;
  }
  *(_DWORD *)&this->_data[22572] = v14;
  if ( !v14 )
  {
    qmemcpy(&v20[8], ((Logger *)&v20[1032])->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 56), 0x400u);
    _CxxThrowException(&v20[8], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v16 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                       g_pGfxMgr,
                       aEffectFlarebri);
  *(_DWORD *)&this->_data[22592] = v16;
  v16->LoadTexture(1);
  v17 = (_DWORD *)operator new(0x44u);
  if ( v17 )
  {
    v18 = *(_DWORD *)&this->_data[22592];
    v17[16] = 1;
    *v17 = v18;
  }
  else
  {
    v17 = 0;
  }
  *(_DWORD *)&this->_data[22596] = v17;
  if ( !v17 )
  {
    qmemcpy(v20, ((Logger *)&v20[1024])->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 61), 0x400u);
    _CxxThrowException(v20, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *(_DWORD *)&this->_data[22636] = -1;
  *(_DWORD *)&this->_data[22628] = 1065353216;
  *(_DWORD *)&this->_data[22624] = 1065353216;
  *(_DWORD *)&this->_data[22620] = 0;
  *(_DWORD *)&this->_data[22616] = 0;
  *(_DWORD *)&this->_data[22632] = 1056964608;
  this;
}

// 0x004D5DC0
C2DSpark::~C2DSpark()
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  gbRefObject *v4; // ecx
  gbRefObject *v5; // ecx
  gbRefObject *v6; // ecx
  gbRefObject *v7; // ecx

  v2 = (gbRefObject *)*(gbRefObject **)&this->_data[22556];
  if ( v2 )
  {
    v2->Release();
    *(_DWORD *)&this->_data[22556] = 0;
  }
  v3 = (gbRefObject *)*(gbRefObject **)&this->_data[22560];
  if ( v3 )
  {
    v3->Release();
    *(_DWORD *)&this->_data[22560] = 0;
  }
  v4 = (gbRefObject *)*(gbRefObject **)&this->_data[22576];
  if ( v4 )
  {
    v4->Release();
    *(_DWORD *)&this->_data[22576] = 0;
  }
  v5 = (gbRefObject *)*(gbRefObject **)&this->_data[22568];
  if ( v5 )
  {
    v5->Release();
    *(_DWORD *)&this->_data[22568] = 0;
  }
  v6 = (gbRefObject *)*(gbRefObject **)&this->_data[22584];
  if ( v6 )
  {
    v6->Release();
    *(_DWORD *)&this->_data[22584] = 0;
  }
  v7 = (gbRefObject *)*(gbRefObject **)&this->_data[22592];
  if ( v7 )
  {
    v7->Release();
    *(_DWORD *)&this->_data[22592] = 0;
  }
  if ( *(_DWORD *)&this->_data[22564] )
  {
    operator delete(*(void **)&this->_data[22564]);
    *(_DWORD *)&this->_data[22564] = 0;
  }
  if ( *(_DWORD *)&this->_data[22580] )
  {
    operator delete(*(void **)&this->_data[22580]);
    *(_DWORD *)&this->_data[22580] = 0;
  }
  if ( *(_DWORD *)&this->_data[22572] )
  {
    operator delete(*(void **)&this->_data[22572]);
    *(_DWORD *)&this->_data[22572] = 0;
  }
  if ( *(_DWORD *)&this->_data[22588] )
  {
    operator delete(*(void **)&this->_data[22588]);
    *(_DWORD *)&this->_data[22588] = 0;
  }
  if ( *(_DWORD *)&this->_data[22596] )
  {
    operator delete(*(void **)&this->_data[22596]);
    *(_DWORD *)&this->_data[22596] = 0;
  }
}

// 0x004D5EC0
char C2DSpark::CreateSingle(const void *a2)
{
  int v3; // eax
  char *i; // ecx

  v3 = 0;
  for ( i = &this->_data[41]; *i; i += 44 )
  {
    if ( ++v3 >= 512 )
      return 0;
  }
  qmemcpy((char *)this + 44 * v3, a2, 0x2Cu);
  this->_data[44 * v3 + 41] = 1;
  if ( v3 >= *(_DWORD *)&this->_data[22536] )
    *(_DWORD *)&this->_data[22536] = v3 + 1;
  return 1;
}

// 0x004D5F20
char C2DSpark::CreateTrack(char a2)
{
  *(_DWORD *)&this->_data[22540] = 0;
  this->_data[22552] = a2;
  return a2;
}

// 0x004D5F40
int C2DSpark::SetEnableMouseTrack(int a2, int a3)
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
  *(_DWORD *)&this->_data[22540] = 1132068864;
  *(_DWORD *)&this->_data[22544] = a2;
  *(_DWORD *)&this->_data[22548] = a3;
  return a3;
}

// 0x004D6050
char C2DSpark::CreateMore(int a2, int a3, int a4, int a5)
{
  double v5; // st7
  double v7; // st7
  float v9; // [esp+0h] [ebp-4h]
  float a2a; // [esp+8h] [ebp+4h]
  float a3a; // [esp+Ch] [ebp+8h]

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
  a3a = (double)a3 - v5;
  *(float *)&dword_17A8168 = 250.0 - (double)(rand() % 50);
  a2a = (float)a4;
  flt_17A8150 = (double)(rand() % a4) + v9 - a2a * 0.5;
  flt_17A8154 = (double)(rand() % (2 * a4)) + a3a - a2a;
  if ( *(float *)&a5 >= 19.0 )
    v7 = (double)-(rand() % 100);
  else
    v7 = (double)-(rand() % 50);
  *(float *)&dword_17A8164 = v7;
  return this->CreateSingle(&flt_17A8150);
}

// 0x004D61A0
_BYTE * C2DSpark::CreateStars()
{
  _BYTE *result; // eax
  int v2; // edx

  result = (_BYTE *)&this->_data[41];
  v2 = 512;
  do
  {
    *result = 0;
    result += 44;
    --v2;
  }
  while ( v2 );
  *(_DWORD *)&this->_data[22536] = 0;
  return result;
}

// 0x004D61C0
int C2DSpark::DestroyAll()
{
  gbDynVertBuf *DynVertBuf; // ebx
  int y; // ecx
  int x; // eax
  double v5; // st7
  double v6; // st7
  struct gbRenderEffect *v7; // ecx
  int result; // eax
  char *v9; // edi
  struct gbTextureArray *v10; // ecx
  struct gbRenderEffect *v11; // ecx
  int v12; // ecx
  struct gbTextureArray *v13; // [esp-4h] [ebp-20h]
  struct tagPOINT Point; // [esp+Ch] [ebp-10h] BYREF
  float v15; // [esp+14h] [ebp-8h]
  int v16; // [esp+18h] [ebp-4h]

  DynVertBuf = ((gbVertPoolMgr *)g_pGfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  if ( *(float *)&this->_data[22540] > 2.0 )
  {
    ((GRPinput *)&Point)->GetCursorPos();
    if ( this->_data[22552] )
    {
      GetCursorPos(&Point);
      y = Point.y;
      x = Point.x;
    }
    else
    {
      x = *(_DWORD *)&this->_data[22544];
      y = *(_DWORD *)&this->_data[22548];
      Point.x = x;
      Point.y = y;
    }
    v16 = y - 64;
    *(float *)&this->_data[22600] = (float)(x - 64);
    v5 = (double)v16;
    v16 = x + 64;
    *(float *)&this->_data[22604] = v5;
    v6 = (double)v16;
    v16 = y + 64;
    *(float *)&this->_data[22608] = v6;
    *(float *)&this->_data[22612] = (float)v16;
    v7 = (struct gbRenderEffect *)*(struct gbRenderEffect **)&this->_data[22556];
    this->_data[22639] = (__int64)*(float *)&this->_data[22540];
    DynVertBuf->RenderUIQuad((struct gbUIQuad *)&this->_data[22600], 1, v7, *(struct gbTextureArray **)&this->_data[22564]);
  }
  result = *(_DWORD *)&this->_data[22536];
  v16 = 0;
  if ( result > 0 )
  {
    v9 = (char *)&this->_data[32];
    do
    {
      if ( v9[9] )
      {
        result = (unsigned __int8)v9[8];
        switch ( v9[8] )
        {
          case 0:
            v10 = (struct gbTextureArray *)*(struct gbTextureArray **)&this->_data[22588];
            goto LABEL_14;
          case 1:
            v10 = (struct gbTextureArray *)*(struct gbTextureArray **)&this->_data[22580];
            goto LABEL_14;
          case 2:
            v10 = (struct gbTextureArray *)*(struct gbTextureArray **)&this->_data[22572];
            goto LABEL_14;
          case 3:
            v10 = (struct gbTextureArray *)*(struct gbTextureArray **)&this->_data[22596];
LABEL_14:
            *(_DWORD *)&this->_data[22600] = *((_DWORD *)v9 - 8);
            *(_DWORD *)&this->_data[22604] = *((_DWORD *)v9 - 7);
            *(float *)&this->_data[22608] = *(float *)v9 + *((float *)v9 - 8);
            *(float *)&this->_data[22612] = *(float *)v9 + *((float *)v9 - 7);
            v15 = *((float *)v9 - 2);
            Point.y = (int)v15;
            v13 = v10;
            v11 = (struct gbRenderEffect *)*(struct gbRenderEffect **)&this->_data[22556];
            this->_data[22639] = Point.y;
            DynVertBuf->RenderUIQuad((struct gbUIQuad *)&this->_data[22600], 1, v11, v13);
            break;
          default:
            return result;
        }
      }
      v12 = *(_DWORD *)&this->_data[22536];
      result = v16 + 1;
      v9 += 44;
      ++v16;
    }
    while ( v16 < v12 );
  }
  return result;
}

// 0x004D6380
int C2DSpark::Render(float a2)
{
  int v3; // edi
  int v4; // eax
  int result; // eax
  int v6; // edx
  char *v7; // ecx
  int v8; // eax
  struct tagPOINT Point; // [esp+8h] [ebp-Ch] BYREF
  int v10; // [esp+10h] [ebp-4h]

  if ( this->_data[22552] )
  {
    ((GRPinput *)&Point)->GetCursorPos();
    if ( Point != qword_17A8438 )
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
        v10 = rand() % 100;
        flt_17A8128 = ((double)v10 - 50.0) * 2.5;
        v4 = rand();
        dword_17A8130 = 0;
        dword_17A8134 = 1145569280;
        dword_17A813C = -1011941376;
        dword_17A8144 = 0;
        v10 = v4 % 100;
        flt_17A812C = ((double)(v4 % 100) - 50.0) * 2.5;
        this->CreateSingle(&flt_17A8120);
        --v3;
      }
      while ( v3 );
      qword_17A8438 = (__int64)Point;
      v10 = (unsigned __int8)rand();
      *(float *)&this->_data[22540] = (float)v10;
    }
  }
  if ( *(float *)&this->_data[22540] > 2.0 )
    *(float *)&this->_data[22540] = *(float *)&this->_data[22540] - a2 * 200.0;
  result = *(_DWORD *)&this->_data[22536];
  v6 = 0;
  if ( result > 0 )
  {
    v7 = (char *)&this->_data[8];
    do
    {
      if ( v7[33] )
      {
        *(float *)v7 = a2 * *((float *)v7 + 2) + *(float *)v7;
        *((float *)v7 + 1) = a2 * *((float *)v7 + 3) + *((float *)v7 + 1);
        *((float *)v7 - 2) = a2 * *(float *)v7 + *((float *)v7 - 2);
        *((float *)v7 - 1) = a2 * *((float *)v7 + 1) + *((float *)v7 - 1);
        *((float *)v7 + 4) = a2 * *((float *)v7 + 5) + *((float *)v7 + 4);
        *(float *)&v10 = a2 * *((float *)v7 + 7) + *((float *)v7 + 6);
        *((float *)v7 + 6) = *(float *)&v10;
        if ( *((float *)v7 - 2) >= (double)*(float *)&this->_data[22528]
          || (*(float *)&Point.x = -*(float *)&v10, *((float *)v7 - 2) <= (double)*(float *)&Point.x)
          || *((float *)v7 - 1) >= (double)*(float *)&this->_data[22532]
          || *((float *)v7 - 1) <= (double)*(float *)&Point.x
          || *((float *)v7 + 4) <= 1.0
          || *((float *)v7 + 4) > 255.0
          || *(float *)&v10 < 0.0099999998 )
        {
          v7[33] = 0;
          v8 = *(_DWORD *)&this->_data[22536] - 1;
          if ( v6 == v8 )
            *(_DWORD *)&this->_data[22536] = v8;
        }
      }
      result = *(_DWORD *)&this->_data[22536];
      ++v6;
      v7 += 44;
    }
    while ( v6 < result );
  }
  return result;
}
