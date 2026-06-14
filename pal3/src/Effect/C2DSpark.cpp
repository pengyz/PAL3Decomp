#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/C2DSpark.h"

// Unnamed globals (extern)
extern char byte_17A8148;
extern char byte_17A8178;
extern char byte_17A81A8;
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
extern int dword_17A8438;
extern int dword_17A843C;
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
C2DSpark::C2DSpark(int nClientWidth, int nClientHeight)
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
  _BYTE v19[1056]; // [esp+0x30] [ebp-0x800] BYREF
  char ArgList; // [esp+0x450] [ebp-0x3E0] BYREF

  *(_DWORD *)&this->m_Spark[471]._tail_000[28] = -1;
  *(_DWORD *)&this->m_Spark[471]._tail_000[24] = 0;
  memset(this, 0, 0x5870u);
  *(float *)&this->m_Spark[469]._tail_000[16] = (float)nClientWidth;
  *(float *)&this->m_Spark[469]._tail_000[20] = (float)nClientHeight;
  this->m_Spark[469]._tail_000[40] = 0;
  *(_DWORD *)&this->m_Spark[469]._tail_000[44] = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect((const char *)&pTarget.m_nTargetType + 412, 0);
  v4 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                      gfxMgr,
                      &pTarget.m_nTargetType + 98);
  *(_DWORD *)&v19[12] = 1;
  *(_DWORD *)this->m_Spark[470]._tail_000 = v4;
  ((gbTexture *)v4)->LoadTexture(*(_DWORD *)&v19[12]);
  v5 = operator new(0x44u);
  if ( v5 )
  {
    v6 = *(_DWORD *)this->m_Spark[470]._tail_000;
    v5[16] = 1;
    *v5 = v6;
  }
  else
  {
    v5 = 0;
  }
  *(_DWORD *)&this->m_Spark[470]._tail_000[4] = v5;
  if ( !v5 )
  {
    qmemcpy(
      &v19[32],
      ((Logger *)&ArgList)->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 352, 41),
      0x400u);
    _CxxThrowException(&v19[32], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v7 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                      gfxMgr,
                      &pTarget.m_nTargetType + 83);
  *(_DWORD *)&v19[8] = 1;
  *(_DWORD *)&this->m_Spark[470]._tail_000[24] = v7;
  ((gbTexture *)v7)->LoadTexture(*(_DWORD *)&v19[8]);
  v8 = operator new(0x44u);
  if ( v8 )
  {
    v9 = *(_DWORD *)&this->m_Spark[470]._tail_000[24];
    v8[16] = 1;
    *v8 = v9;
  }
  else
  {
    v8 = 0;
  }
  *(_DWORD *)&this->m_Spark[470]._tail_000[28] = v8;
  if ( !v8 )
  {
    qmemcpy(
      &v19[24],
      ((Logger *)&v19[1048])->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 352, 46),
      0x400u);
    _CxxThrowException(&v19[24], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                       gfxMgr,
                       &pTarget.m_nTargetType + 77);
  *(_DWORD *)v19 = 1;
  *(_DWORD *)&this->m_Spark[470]._tail_000[16] = v10;
  ((gbTexture *)v10)->LoadTexture(*(_DWORD *)v19);
  v11 = operator new(0x44u);
  if ( v11 )
  {
    v12 = *(_DWORD *)&this->m_Spark[470]._tail_000[16];
    v11[16] = 1;
    *v11 = v12;
  }
  else
  {
    v11 = 0;
  }
  *(_DWORD *)&this->m_Spark[470]._tail_000[20] = v11;
  if ( !*(_DWORD *)&this->m_Spark[470]._tail_000[28] )
  {
    qmemcpy(
      &v19[16],
      ((Logger *)&v19[1040])->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 352, 51),
      0x400u);
    _CxxThrowException(&v19[16], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v13 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                       gfxMgr,
                       &pTarget.m_nTargetType + 71);
  *(_DWORD *)&this->m_Spark[470]._tail_000[8] = v13;
  ((gbTexture *)v13)->LoadTexture(1);
  v14 = operator new(0x44u);
  if ( v14 )
  {
    v15 = *(_DWORD *)&this->m_Spark[470]._tail_000[8];
    v14[16] = 1;
    *v14 = v15;
  }
  else
  {
    v14 = 0;
  }
  *(_DWORD *)&this->m_Spark[470]._tail_000[12] = v14;
  if ( !v14 )
  {
    qmemcpy(
      &v19[8],
      ((Logger *)&v19[1032])->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 352, 56),
      0x400u);
    _CxxThrowException(&v19[8], (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v16 = (gbTexture *)(*(int (**)(gbGfxManager *, int *))(*(_DWORD *)gfxMgr + 8))(
                       gfxMgr,
                       &pTarget.m_nTargetType + 63);
  *(_DWORD *)&this->m_Spark[470]._tail_000[32] = v16;
  ((gbTexture *)v16)->LoadTexture(1);
  v17 = operator new(0x44u);
  if ( v17 )
  {
    v18 = *(_DWORD *)&this->m_Spark[470]._tail_000[32];
    v17[16] = 1;
    *v17 = v18;
  }
  else
  {
    v17 = 0;
  }
  *(_DWORD *)&this->m_Spark[470]._tail_000[36] = v17;
  if ( !v17 )
  {
    qmemcpy(
      v19,
      ((Logger *)&v19[1024])->FormatException("C++ new failed!", (char *)&pTarget.m_nTargetType + 352, 61),
      0x400u);
    _CxxThrowException(v19, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *(_DWORD *)&this->m_Spark[471]._tail_000[28] = -1;
  *(_DWORD *)&this->m_Spark[471]._tail_000[20] = 1065353216;
  *(_DWORD *)&this->m_Spark[471]._tail_000[16] = 1065353216;
  *(_DWORD *)&this->m_Spark[471]._tail_000[12] = 0;
  *(_DWORD *)&this->m_Spark[471]._tail_000[8] = 0;
  *(_DWORD *)&this->m_Spark[471]._tail_000[24] = 1056964608;
}

// 0x004D5DC0
void C2DSpark::_C2DSpark()
{
  gbRefObject *v2; // ecx
  gbRefObject *v3; // ecx
  gbRefObject *v4; // ecx
  gbRefObject *v5; // ecx
  gbRefObject *v6; // ecx
  gbRefObject *v7; // ecx

  v2 = *(gbRefObject **)&this->m_Spark[469]._tail_000[44];
  if ( v2 )
  {
    ((gbRefObject *)v2)->Release();
    *(_DWORD *)&this->m_Spark[469]._tail_000[44] = 0;
  }
  v3 = *(gbRefObject **)this->m_Spark[470]._tail_000;
  if ( v3 )
  {
    ((gbRefObject *)v3)->Release();
    *(_DWORD *)this->m_Spark[470]._tail_000 = 0;
  }
  v4 = *(gbRefObject **)&this->m_Spark[470]._tail_000[16];
  if ( v4 )
  {
    ((gbRefObject *)v4)->Release();
    *(_DWORD *)&this->m_Spark[470]._tail_000[16] = 0;
  }
  v5 = *(gbRefObject **)&this->m_Spark[470]._tail_000[8];
  if ( v5 )
  {
    ((gbRefObject *)v5)->Release();
    *(_DWORD *)&this->m_Spark[470]._tail_000[8] = 0;
  }
  v6 = *(gbRefObject **)&this->m_Spark[470]._tail_000[24];
  if ( v6 )
  {
    ((gbRefObject *)v6)->Release();
    *(_DWORD *)&this->m_Spark[470]._tail_000[24] = 0;
  }
  v7 = *(gbRefObject **)&this->m_Spark[470]._tail_000[32];
  if ( v7 )
  {
    ((gbRefObject *)v7)->Release();
    *(_DWORD *)&this->m_Spark[470]._tail_000[32] = 0;
  }
  if ( *(_DWORD *)&this->m_Spark[470]._tail_000[4] )
  {
    operator delete(*(void **)&this->m_Spark[470]._tail_000[4]);
    *(_DWORD *)&this->m_Spark[470]._tail_000[4] = 0;
  }
  if ( *(_DWORD *)&this->m_Spark[470]._tail_000[20] )
  {
    operator delete(*(void **)&this->m_Spark[470]._tail_000[20]);
    *(_DWORD *)&this->m_Spark[470]._tail_000[20] = 0;
  }
  if ( *(_DWORD *)&this->m_Spark[470]._tail_000[12] )
  {
    operator delete(*(void **)&this->m_Spark[470]._tail_000[12]);
    *(_DWORD *)&this->m_Spark[470]._tail_000[12] = 0;
  }
  if ( *(_DWORD *)&this->m_Spark[470]._tail_000[28] )
  {
    operator delete(*(void **)&this->m_Spark[470]._tail_000[28]);
    *(_DWORD *)&this->m_Spark[470]._tail_000[28] = 0;
  }
  if ( *(_DWORD *)&this->m_Spark[470]._tail_000[36] )
  {
    operator delete(*(void **)&this->m_Spark[470]._tail_000[36]);
    *(_DWORD *)&this->m_Spark[470]._tail_000[36] = 0;
  }
}

// 0x004D5EC0
bool C2DSpark::CreateSingle(const void *pSpark)
{
  int v3; // eax
  _BYTE *i; // ecx

  v3 = 0;
  for ( i = &this->m_Spark[0]._tail_000[41]; *i; i += 44 )
  {
    if ( ++v3 >= 512 )
      return 0;
  }
  qmemcpy((char *)this + 44 * v3, pSpark, 0x2Cu);
  this->m_Spark[0]._tail_000[44 * v3 + 41] = 1;
  if ( v3 >= *(_DWORD *)&this->m_Spark[469]._tail_000[24] )
    *(_DWORD *)&this->m_Spark[469]._tail_000[24] = v3 + 1;
  return 1;
}

// 0x004D5F20
char C2DSpark::CreateTrack(char a2, int a3, int a4)
{
  *(_DWORD *)&this->m_Spark[469]._tail_000[28] = 0;
  this->m_Spark[469]._tail_000[40] = a2;
  return a2;
}

// 0x004D5F40
void C2DSpark::SetEnableMouseTrack(int bEnable, int nVal)
{
  int v4; // edi
  long double v5; // st7
  float v6; // [esp+0x0] [ebp-0x8]

  dword_17A81A0 = 1098907648;
  dword_17A8198 = 1128792064;
  dword_17A8190 = 0;
  dword_17A8194 = 1145569280;
  dword_17A819C = -1011941376;
  dword_17A81A4 = 0;
  flt_17A8180 = (double)bEnable - 8.0;
  v4 = 0;
  flt_17A8184 = (double)nVal - 8.0;
  do
  {
    byte_17A81A8 = rand() & 3;
    v6 = (float)(rand() % 300);
    v5 = (double)(rand() % 5760 / 16) * 0.017453292;
    flt_17A8188 = sin(v5) * v6;
    flt_17A818C = cos(v5) * v6;
    if ( !this->CreateSingle(&flt_17A8180) )
      break;
    ++v4;
  }
  while ( v4 < 60 );
  *(_DWORD *)&this->m_Spark[469]._tail_000[28] = 1132068864;
  *(_DWORD *)&this->m_Spark[469]._tail_000[32] = bEnable;
  *(_DWORD *)&this->m_Spark[469]._tail_000[36] = nVal;
}

// 0x004D6050
void C2DSpark::CreateMore(int x, int y, int color, int nVal)
{
  double v5; // st7
  double v7; // st7
  float v8; // [esp+0x0] [ebp-0x4]
  float xa; // [esp+0x8] [ebp+0x4]
  float ya; // [esp+0xC] [ebp+0x8]

  v5 = *(float *)&nVal * 0.5;
  dword_17A8170 = nVal;
  dword_17A8168 = 1128792064;
  dword_17A8158 = 0;
  dword_17A815C = -1054867456;
  dword_17A8160 = 0;
  dword_17A8164 = -1035468800;
  v8 = (double)x - v5;
  dword_17A816C = -1027080192;
  dword_17A8174 = 0;
  byte_17A8178 = 2;
  ya = (double)y - v5;
  *(float *)&dword_17A8168 = 250.0 - (double)(rand() % 50);
  xa = (float)color;
  flt_17A8150 = (double)(rand() % color) + v8 - xa * 0.5;
  flt_17A8154 = (double)(rand() % (2 * color)) + ya - xa;
  if ( *(float *)&nVal >= 19.0 )
    v7 = (double)-(rand() % 100);
  else
    v7 = (double)-(rand() % 50);
  *(float *)&dword_17A8164 = v7;
  this->CreateSingle(&flt_17A8150);
}

// 0x004D61A0
_BYTE * C2DSpark::CreateStars()
{
  _BYTE *result; // eax
  int v2; // edx

  result = &this->m_Spark[0]._tail_000[41];
  v2 = 512;
  do
  {
    *result = 0;
    result += 44;
    --v2;
  }
  while ( v2 );
  *(_DWORD *)&this->m_Spark[469]._tail_000[24] = 0;
  return result;
}

// 0x004D61C0
void C2DSpark::DestroyAll()
{
  gbDynVertBuf *DynVertBuf; // ebx
  LONG y; // ecx
  LONG x; // eax
  double v5; // st7
  double v6; // st7
  gbRenderEffect *v7; // ecx
  int v8; // eax
  _BYTE *v9; // edi
  gbTextureArray *v10; // ecx
  gbRenderEffect *v11; // ecx
  int v12; // ecx
  gbTextureArray *v13; // [esp-0x4] [ebp-0x20]
  struct tagPOINT Point; // [esp+0xC] [ebp-0x10] BYREF
  float v15; // [esp+0x14] [ebp-0x8]
  int v16; // [esp+0x18] [ebp-0x4]

  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  if ( *(float *)&this->m_Spark[469]._tail_000[28] > 2.0 )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    if ( this->m_Spark[469]._tail_000[40] )
    {
      GetCursorPos(&Point);
      y = Point.y;
      x = Point.x;
    }
    else
    {
      x = *(_DWORD *)&this->m_Spark[469]._tail_000[32];
      y = *(_DWORD *)&this->m_Spark[469]._tail_000[36];
      Point.x = x;
      Point.y = y;
    }
    v16 = y - 64;
    *(float *)&this->m_Spark[470]._tail_000[40] = (float)(x - 64);
    v5 = (double)v16;
    v16 = x + 64;
    *(float *)&this->m_Spark[470]._tail_000[44] = v5;
    v6 = (double)v16;
    v16 = y + 64;
    *(float *)this->m_Spark[471]._tail_000 = v6;
    *(float *)&this->m_Spark[471]._tail_000[4] = (float)v16;
    v7 = *(gbRenderEffect **)&this->m_Spark[469]._tail_000[44];
    this->m_Spark[471]._tail_000[31] = (__int64)*(float *)&this->m_Spark[469]._tail_000[28];
    ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad((gbUIQuad *)&this->m_Spark[470]._tail_000[40], 1, v7, *(gbTextureArray **)&this->m_Spark[470]._tail_000[4]);
  }
  v8 = *(_DWORD *)&this->m_Spark[469]._tail_000[24];
  v16 = 0;
  if ( v8 > 0 )
  {
    v9 = &this->m_Spark[0]._tail_000[32];
    do
    {
      if ( v9[9] )
      {
        switch ( v9[8] )
        {
          case 0:
            v10 = *(gbTextureArray **)&this->m_Spark[470]._tail_000[28];
            goto LABEL_14;
          case 1:
            v10 = *(gbTextureArray **)&this->m_Spark[470]._tail_000[20];
            goto LABEL_14;
          case 2:
            v10 = *(gbTextureArray **)&this->m_Spark[470]._tail_000[12];
            goto LABEL_14;
          case 3:
            v10 = *(gbTextureArray **)&this->m_Spark[470]._tail_000[36];
LABEL_14:
            *(_DWORD *)&this->m_Spark[470]._tail_000[40] = *((_DWORD *)v9 - 8);
            *(_DWORD *)&this->m_Spark[470]._tail_000[44] = *((_DWORD *)v9 - 7);
            *(float *)this->m_Spark[471]._tail_000 = *(float *)v9 + *((float *)v9 - 8);
            *(float *)&this->m_Spark[471]._tail_000[4] = *(float *)v9 + *((float *)v9 - 7);
            v15 = *((float *)v9 - 2);
            Point.y = (int)v15;
            v13 = v10;
            v11 = *(gbRenderEffect **)&this->m_Spark[469]._tail_000[44];
            this->m_Spark[471]._tail_000[31] = Point.y;
            ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad((gbUIQuad *)&this->m_Spark[470]._tail_000[40], 1, v11, v13);
            break;
          default:
            return;
        }
      }
      v12 = *(_DWORD *)&this->m_Spark[469]._tail_000[24];
      v9 += 44;
      ++v16;
    }
    while ( v16 < v12 );
  }
}

// 0x004D6380
void C2DSpark::Render(float fVal)
{
  int v3; // edi
  int v4; // eax
  int v5; // edx
  float *v6; // ecx
  int v7; // eax
  int Point; // [esp+0x8] [ebp-0xC]
  float Pointa; // [esp+0x8] [ebp-0xC]
  int Point_4; // [esp+0xC] [ebp-0x8]
  float v11; // [esp+0x10] [ebp-0x4]

  if ( this->m_Spark[469]._tail_000[40] )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    if ( Point != dword_17A8438 || Point_4 != dword_17A843C )
    {
      dword_17A8140 = 1098907648;
      dword_17A8138 = 1125842944;
      v3 = 5;
      flt_17A8120 = (double)Point - 8.0;
      flt_17A8124 = (double)Point_4 - 8.0;
      do
      {
        rand();
        byte_17A8148 = 0;
        flt_17A8128 = ((double)(rand() % 100) - 50.0) * 2.5;
        v4 = rand();
        dword_17A8130 = 0;
        dword_17A8134 = 1145569280;
        dword_17A813C = -1011941376;
        dword_17A8144 = 0;
        flt_17A812C = ((double)(v4 % 100) - 50.0) * 2.5;
        this->CreateSingle(&flt_17A8120);
        --v3;
      }
      while ( v3 );
      dword_17A8438 = Point;
      dword_17A843C = Point_4;
      *(float *)&this->m_Spark[469]._tail_000[28] = (float)(unsigned __int8)rand();
    }
  }
  if ( *(float *)&this->m_Spark[469]._tail_000[28] > 2.0 )
    *(float *)&this->m_Spark[469]._tail_000[28] = *(float *)&this->m_Spark[469]._tail_000[28] - fVal * 200.0;
  v5 = 0;
  if ( *(int *)&this->m_Spark[469]._tail_000[24] > 0 )
  {
    v6 = (float *)&this->m_Spark[0]._tail_000[8];
    do
    {
      if ( *((_BYTE *)v6 + 33) )
      {
        *v6 = fVal * v6[2] + *v6;
        v6[1] = fVal * v6[3] + v6[1];
        *(v6 - 2) = fVal * *v6 + *(v6 - 2);
        *(v6 - 1) = fVal * v6[1] + *(v6 - 1);
        v6[4] = fVal * v6[5] + v6[4];
        v11 = fVal * v6[7] + v6[6];
        v6[6] = v11;
        if ( *(v6 - 2) >= (double)*(float *)&this->m_Spark[469]._tail_000[16]
          || (Pointa = -v11, *(v6 - 2) <= (double)Pointa)
          || *(v6 - 1) >= (double)*(float *)&this->m_Spark[469]._tail_000[20]
          || *(v6 - 1) <= (double)Pointa
          || v6[4] <= 1.0
          || v6[4] > 255.0
          || v11 < 0.0099999998 )
        {
          *((_BYTE *)v6 + 33) = 0;
          v7 = *(_DWORD *)&this->m_Spark[469]._tail_000[24] - 1;
          if ( v5 == v7 )
            *(_DWORD *)&this->m_Spark[469]._tail_000[24] = v7;
        }
      }
      ++v5;
      v6 += 11;
    }
    while ( v5 < *(_DWORD *)&this->m_Spark[469]._tail_000[24] );
  }
}
