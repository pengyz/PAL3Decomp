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
  int d5820; // ecx
  gbTexture *v7; // eax
  _DWORD *v8; // eax
  int d5838; // ecx
  gbTexture *v10; // eax
  _DWORD *v11; // eax
  int d5830; // ecx
  gbTexture *v13; // eax
  _DWORD *v14; // eax
  int d5828; // ecx
  gbTexture *v16; // eax
  _DWORD *v17; // eax
  int d5840; // ecx
  _BYTE v20[1056]; // [esp+30h] [ebp-800h] BYREF
  char ArgList[992]; // [esp+450h] [ebp-3E0h] BYREF

  this->_d586C = -1;
  this->_d5868 = 0;
  memset(this, 0, sizeof(C2DSpark));
  this->_f5800 = (float)a2;
  this->_f5804 = (float)a3;
  this->_pad_5818[0] = 0;
  this->_d581C = (int)((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptTlAdd, 0);
  v4 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                      g_pGfxMgr,
                      aEffectFlare3Bm);
  *(_DWORD *)&v20[12] = 1;
  this->_d5820 = (int)v4;
  v4->LoadTexture(*(_DWORD *)&v20[12]);
  v5 = (_DWORD *)operator new(0x44u);
  if ( v5 )
  {
    d5820 = this->_d5820;
    v5[16] = 1;
    *v5 = d5820;
  }
  else
  {
    v5 = 0;
  }
  this->_d5824 = (int)v5;
  if ( !v5 )
  {
    qmemcpy(&v20[32], ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 41), 0x400u);
    _CxxThrowException(&v20[32], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                      g_pGfxMgr,
                      aEffectFlare2Bm);
  *(_DWORD *)&v20[8] = 1;
  this->_d5838 = (int)v7;
  v7->LoadTexture(*(_DWORD *)&v20[8]);
  v8 = (_DWORD *)operator new(0x44u);
  if ( v8 )
  {
    d5838 = this->_d5838;
    v8[16] = 1;
    *v8 = d5838;
  }
  else
  {
    v8 = 0;
  }
  this->_d583C = (int)v8;
  if ( !v8 )
  {
    qmemcpy(&v20[24], ((Logger *)&v20[1048])->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 46), 0x400u);
    _CxxThrowException(&v20[24], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                       g_pGfxMgr,
                       aEffectFlaregre);
  *(_DWORD *)v20 = 1;
  this->_d5830 = (int)v10;
  v10->LoadTexture(*(_DWORD *)v20);
  v11 = (_DWORD *)operator new(0x44u);
  if ( v11 )
  {
    d5830 = this->_d5830;
    v11[16] = 1;
    *v11 = d5830;
  }
  else
  {
    v11 = 0;
  }
  this->_d5834 = (int)v11;
  if ( !this->_d583C )
  {
    qmemcpy(&v20[16], ((Logger *)&v20[1040])->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 51), 0x400u);
    _CxxThrowException(&v20[16], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v13 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                       g_pGfxMgr,
                       aEffectFlareblu);
  this->_d5828 = (int)v13;
  v13->LoadTexture(1);
  v14 = (_DWORD *)operator new(0x44u);
  if ( v14 )
  {
    d5828 = this->_d5828;
    v14[16] = 1;
    *v14 = d5828;
  }
  else
  {
    v14 = 0;
  }
  this->_d582C = (int)v14;
  if ( !v14 )
  {
    qmemcpy(&v20[8], ((Logger *)&v20[1032])->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 56), 0x400u);
    _CxxThrowException(&v20[8], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v16 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                       g_pGfxMgr,
                       aEffectFlarebri);
  this->_d5840 = (int)v16;
  v16->LoadTexture(1);
  v17 = (_DWORD *)operator new(0x44u);
  if ( v17 )
  {
    d5840 = this->_d5840;
    v17[16] = 1;
    *v17 = d5840;
  }
  else
  {
    v17 = 0;
  }
  this->_d5844 = (int)v17;
  if ( !v17 )
  {
    qmemcpy(v20, ((Logger *)&v20[1024])->FormatException(aCNewFailed_0, aDProjectPal3Co_10, 61), 0x400u);
    _CxxThrowException(v20, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->_d586C = -1;
  this->_d5864 = 1065353216;
  this->_d5860 = 1065353216;
  this->_d585C = 0;
  this->_d5858 = 0;
  this->_d5868 = 1056964608;
  this;
}

// 0x004D5DC0
C2DSpark::~C2DSpark()
{
  gbRefObject *d581C; // ecx
  gbRefObject *d5820; // ecx
  gbRefObject *d5830; // ecx
  gbRefObject *d5828; // ecx
  gbRefObject *d5838; // ecx
  gbRefObject *d5840; // ecx

  d581C = (gbRefObject *)this->_d581C;
  if ( d581C )
  {
    d581C->Release();
    this->_d581C = 0;
  }
  d5820 = (gbRefObject *)this->_d5820;
  if ( d5820 )
  {
    d5820->Release();
    this->_d5820 = 0;
  }
  d5830 = (gbRefObject *)this->_d5830;
  if ( d5830 )
  {
    d5830->Release();
    this->_d5830 = 0;
  }
  d5828 = (gbRefObject *)this->_d5828;
  if ( d5828 )
  {
    d5828->Release();
    this->_d5828 = 0;
  }
  d5838 = (gbRefObject *)this->_d5838;
  if ( d5838 )
  {
    d5838->Release();
    this->_d5838 = 0;
  }
  d5840 = (gbRefObject *)this->_d5840;
  if ( d5840 )
  {
    d5840->Release();
    this->_d5840 = 0;
  }
  if ( this->_d5824 )
  {
    operator delete((void *)this->_d5824);
    this->_d5824 = 0;
  }
  if ( this->_d5834 )
  {
    operator delete((void *)this->_d5834);
    this->_d5834 = 0;
  }
  if ( this->_d582C )
  {
    operator delete((void *)this->_d582C);
    this->_d582C = 0;
  }
  if ( this->_d583C )
  {
    operator delete((void *)this->_d583C);
    this->_d583C = 0;
  }
  if ( this->_d5844 )
  {
    operator delete((void *)this->_d5844);
    this->_d5844 = 0;
  }
}

// 0x004D5EC0
char C2DSpark::CreateSingle(const void *a2)
{
  int v3; // eax
  char *i; // ecx

  v3 = 0;
  for ( i = &this->_pad_000[41]; *i; i += 44 )
  {
    if ( ++v3 >= 512 )
      return 0;
  }
  qmemcpy((char *)this + 44 * v3, a2, 0x2Cu);
  this->_pad_000[44 * v3 + 41] = 1;
  if ( v3 >= this->_d5808 )
    this->_d5808 = v3 + 1;
  return 1;
}

// 0x004D5F20
char C2DSpark::CreateTrack(char a2)
{
  this->_f580C = 0.0;
  this->_pad_5818[0] = a2;
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
  this->_f580C = 250.0;
  this->_d5810 = a2;
  this->_d5814 = a3;
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

  result = (_BYTE *)&this->_pad_000[41];
  v2 = 512;
  do
  {
    *result = 0;
    result += 44;
    --v2;
  }
  while ( v2 );
  this->_d5808 = 0;
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
  struct gbRenderEffect *d581C; // ecx
  int result; // eax
  char *v9; // edi
  int d583C; // ecx
  struct gbRenderEffect *v11; // ecx
  int d5808; // ecx
  struct gbTextureArray *v13; // [esp-4h] [ebp-20h]
  struct tagPOINT Point; // [esp+Ch] [ebp-10h] BYREF
  float v15; // [esp+14h] [ebp-8h]
  int v16; // [esp+18h] [ebp-4h]

  DynVertBuf = ((gbVertPoolMgr *)g_pGfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  if ( this->_f580C > 2.0 )
  {
    ((GRPinput *)&Point)->GetCursorPos();
    if ( this->_pad_5818[0] )
    {
      GetCursorPos(&Point);
      y = Point.y;
      x = Point.x;
    }
    else
    {
      x = this->_d5810;
      y = this->_d5814;
      Point.x = x;
      Point.y = y;
    }
    v16 = y - 64;
    this->_f5848 = (float)(x - 64);
    v5 = (double)v16;
    v16 = x + 64;
    this->_f584C = v5;
    v6 = (double)v16;
    v16 = y + 64;
    this->_f5850 = v6;
    this->_f5854 = (float)v16;
    d581C = (struct gbRenderEffect *)this->_d581C;
    HIBYTE(this->_d586C) = (__int64)this->_f580C;
    DynVertBuf->RenderUIQuad((struct gbUIQuad *)&this->_f5848, 1, d581C, (struct gbTextureArray *)this->_d5824);
  }
  result = this->_d5808;
  v16 = 0;
  if ( result > 0 )
  {
    v9 = (char *)&this->_pad_000[32];
    do
    {
      if ( v9[9] )
      {
        result = (unsigned __int8)v9[8];
        switch ( v9[8] )
        {
          case 0:
            d583C = this->_d583C;
            goto LABEL_14;
          case 1:
            d583C = this->_d5834;
            goto LABEL_14;
          case 2:
            d583C = this->_d582C;
            goto LABEL_14;
          case 3:
            d583C = this->_d5844;
LABEL_14:
            this->_f5848 = *((float *)v9 - 8);
            this->_f584C = *((float *)v9 - 7);
            this->_f5850 = *(float *)v9 + *((float *)v9 - 8);
            this->_f5854 = *(float *)v9 + *((float *)v9 - 7);
            v15 = *((float *)v9 - 2);
            Point.y = (int)v15;
            v13 = (struct gbTextureArray *)d583C;
            v11 = (struct gbRenderEffect *)this->_d581C;
            HIBYTE(this->_d586C) = Point.y;
            DynVertBuf->RenderUIQuad((struct gbUIQuad *)&this->_f5848, 1, v11, v13);
            break;
          default:
            return result;
        }
      }
      d5808 = this->_d5808;
      result = v16 + 1;
      v9 += 44;
      ++v16;
    }
    while ( v16 < d5808 );
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

  if ( this->_pad_5818[0] )
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
      this->_f580C = (float)v10;
    }
  }
  if ( this->_f580C > 2.0 )
    this->_f580C = this->_f580C - a2 * 200.0;
  result = this->_d5808;
  v6 = 0;
  if ( result > 0 )
  {
    v7 = (char *)&this->_pad_000[8];
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
        if ( *((float *)v7 - 2) >= (double)this->_f5800
          || (*(float *)&Point.x = -*(float *)&v10, *((float *)v7 - 2) <= (double)*(float *)&Point.x)
          || *((float *)v7 - 1) >= (double)this->_f5804
          || *((float *)v7 - 1) <= (double)*(float *)&Point.x
          || *((float *)v7 + 4) <= 1.0
          || *((float *)v7 + 4) > 255.0
          || *(float *)&v10 < 0.0099999998 )
        {
          v7[33] = 0;
          v8 = this->_d5808 - 1;
          if ( v6 == v8 )
            this->_d5808 = v8;
        }
      }
      result = this->_d5808;
      ++v6;
      v7 += 44;
    }
    while ( v6 < result );
  }
  return result;
}
