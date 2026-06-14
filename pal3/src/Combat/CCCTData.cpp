#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCCTData.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
int sub_506340(...);
int todo_408BD0(...);

LRESULT EditBox_SetFloat(HWND hWnd, float fValue); // from annotations
LRESULT EditBox_SetInt(HWND hWnd, int nValue); // from annotations
LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly); // from annotations

// Unnamed globals (extern)
extern char byte_17AAD89;
extern char byte_17AAEE0;
extern char byte_17AAF21;
extern char byte_A00527;
extern char byte_A00529;
extern char byte_A00530;
extern char byte_A00531;
extern char byte_A00532;
extern char byte_A00533;
extern char byte_A00534;
extern char byte_A00536;
extern char byte_A00537;
extern char byte_A00555;
extern char byte_A00556;
extern char byte_A00557;
extern char byte_A00558;
extern char byte_A00559;
extern char byte_A00560;
extern char byte_A00561;
extern char byte_A00562;
extern char byte_A00563;
extern int dword_17AAD4C;
extern int dword_17AAD50;
extern int dword_17AAD58;
extern int dword_17AAD5C;
extern int dword_17AAD64;
extern int dword_17AAD68;
extern int dword_17AAD70;
extern int dword_17AAD74;
extern int dword_17AAD90;
extern int dword_17AAD94;
extern int dword_17AAD9C;
extern int dword_17AADA0;
extern int dword_17AADA8;
extern int dword_17AADAC;
extern int dword_17AADB4;
extern int dword_17AADB8;
extern int dword_17AADD4;
extern int dword_17AADD8;
extern int dword_17AADE0;
extern int dword_17AADE4;
extern int dword_17AADEC;
extern int dword_17AADF0;
extern int dword_17AADF8;
extern int dword_17AADFC;
extern int dword_17AAE18;
extern int dword_17AAE1C;
extern int dword_17AAE24;
extern int dword_17AAE28;
extern int dword_17AAE30;
extern int dword_17AAE34;
extern int dword_17AAE3C;
extern int dword_17AAE40;
extern int dword_17AAE5C;
extern int dword_17AAE60;
extern int dword_17AAE68;
extern int dword_17AAE6C;
extern int dword_17AAE74;
extern int dword_17AAE78;
extern int dword_17AAE80;
extern int dword_17AAE84;
extern int dword_17AAEA0;
extern int dword_17AAEA4;
extern int dword_17AAEAC;
extern int dword_17AAEB0;
extern int dword_17AAEB8;
extern int dword_17AAEBC;
extern int dword_17AAEC4;
extern int dword_17AAEC8;
extern int dword_DC353C;
extern int dword_DC363C;
extern int dword_DC373C;
extern int dword_DCF73C;
extern float flt_17AAD60;
extern float flt_17AAD6C;
extern float flt_17AAD8C;
extern float flt_17AAD98;
extern float flt_17AADA4;
extern float flt_17AADB0;
extern float flt_17AADD0;
extern float flt_17AADDC;
extern float flt_17AADE8;
extern float flt_17AADF4;
extern float flt_17AAE14;
extern float flt_17AAE20;
extern float flt_17AAE2C;
extern float flt_17AAE38;
extern float flt_17AAE58;
extern float flt_17AAE64;
extern float flt_17AAE70;
extern float flt_17AAE7C;
extern float flt_17AAE9C;
extern float flt_17AAEA8;
extern float flt_17AAEB4;
extern float flt_17AAEC0;
void __cdecl nullsub_31(void);
extern int word_A00552;

// 0x0041C900
void CCCTData::CalcDist(float fVal, float fVal2)
{
  double v3; // st7
  float *v4; // ecx
  long double v5; // st6
  double v6; // st7
  float v7; // [esp+0x0] [ebp-0x10]
  float v8; // [esp+0x4] [ebp-0xC]
  float v9; // [esp+0x1C] [ebp+0xC]
  gbVec3D v10; // [esp+0x20] [ebp+0x10] BYREF
  int v11; // [esp+0x2C] [ebp+0x1C]
  int v12; // [esp+0x30] [ebp+0x20]

  v3 = v10.x - fVal;
  v4 = (float *)v11;
  v7 = v10.z - v9;
  v5 = atan2(-(v3 / v7), 1.0);
  *(float *)v11 = v5;
  if ( v10.z > (double)v9 )
    *v4 = v5 + 3.1415927;
  v8 = v3;
  v10.x = v8;
  v10.z = v7;
  *(float *)&v11 = v10.y - fVal2;
  LODWORD(v10.y) = v11;
  v6 = ((gbVec3D *)&v10)->Length();
  *(float *)v12 = asin(*(float *)&v11 / v6);
}

// 0x0044D780
int CCCTData::InitEntries(float fVal)
{
  unsigned int v2; // ebp
  unsigned int *p_dwID; // esi
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st7
  unsigned int v8; // ebp
  float *p_fCircleEndY; // esi
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  unsigned int v14; // ebp
  float *p_yaw; // esi
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  int result; // eax
  gbColorQuad v22; // [esp+0x34] [ebp-0x4] BYREF

  v2 = 0;
  p_dwID = &this->m_Pool[42].dwID;
  do
  {
    v4 = *(float *)p_dwID - g_fDefaultFOV * *((float *)p_dwID + 3) * fVal;
    *(float *)p_dwID = v4;
    *(p_dwID - 4) = (__int64)v4;
    *(p_dwID - 2) = (__int64)v4 + p_dwID[1];
    sub_445FA0(p_dwID - 42);
    v5 = fVal * 30.0 * *((float *)p_dwID + 5);
    if ( *((_BYTE *)p_dwID + 24) )
    {
      v6 = *((float *)p_dwID + 4) - v5;
      *((float *)p_dwID + 4) = v6;
      if ( v6 <= 0.0 )
      {
        p_dwID[4] = 0;
        *((_BYTE *)p_dwID + 24) = 0;
      }
    }
    else
    {
      v7 = v5 + *((float *)p_dwID + 4);
      *((float *)p_dwID + 4) = v7;
      if ( v7 >= 255.0 )
      {
        p_dwID[4] = 1132396544;
        *((_BYTE *)p_dwID + 24) = 1;
      }
    }
    ((NPC *)(p_dwID - 42))->NPC::UpdateAnim();
    if ( (int)*(p_dwID - 2) <= 150 )
      ((UIGameOver *)this)->InitParticle2(v2);
    ++v2;
    p_dwID += 52;
  }
  while ( v2 < 0xA );
  v8 = 0;
  p_fCircleEndY = &this->m_Pool[25].fCircleEndY;
  do
  {
    v10 = *p_fCircleEndY - g_fDefaultFOV * p_fCircleEndY[3] * fVal;
    *p_fCircleEndY = v10;
    *((_DWORD *)p_fCircleEndY - 4) = (__int64)v10;
    *((_DWORD *)p_fCircleEndY - 2) = (__int64)v10 + *((_DWORD *)p_fCircleEndY + 1);
    sub_445FA0(p_fCircleEndY - 42);
    v11 = fVal * 30.0 * p_fCircleEndY[5];
    if ( *((_BYTE *)p_fCircleEndY + 24) )
    {
      v12 = p_fCircleEndY[4] - v11;
      p_fCircleEndY[4] = v12;
      if ( v12 <= 0.0 )
      {
        p_fCircleEndY[4] = 0.0;
        *((_BYTE *)p_fCircleEndY + 24) = 0;
      }
    }
    else
    {
      v13 = v11 + p_fCircleEndY[4];
      p_fCircleEndY[4] = v13;
      if ( v13 >= 255.0 )
      {
        p_fCircleEndY[4] = 255.0;
        *((_BYTE *)p_fCircleEndY + 24) = 1;
      }
    }
    ((NPC *)(p_fCircleEndY - 42))->NPC::UpdateAnim();
    if ( *((int *)p_fCircleEndY - 2) <= 150 )
      ((UIGameOver *)this)->RandomizeEffects(v8);
    ++v8;
    p_fCircleEndY += 52;
  }
  while ( v8 < 0x10 );
  v14 = 0;
  p_yaw = &this->m_Pool[3].EndPos.yaw;
  do
  {
    v16 = *p_yaw - g_fDefaultFOV * p_yaw[3] * fVal;
    *p_yaw = v16;
    *((_DWORD *)p_yaw - 4) = (__int64)v16;
    *((_DWORD *)p_yaw - 2) = (__int64)v16 + *((_DWORD *)p_yaw + 1);
    sub_445FA0(p_yaw - 42);
    v17 = fVal * 30.0 * p_yaw[5];
    if ( *((_BYTE *)p_yaw + 24) )
    {
      v18 = p_yaw[4] - v17;
      p_yaw[4] = v18;
      if ( v18 <= 0.0 )
      {
        p_yaw[4] = 0.0;
        *((_BYTE *)p_yaw + 24) = 0;
      }
    }
    else
    {
      v19 = v17 + p_yaw[4];
      p_yaw[4] = v19;
      if ( v19 >= 255.0 )
      {
        p_yaw[4] = 255.0;
        *((_BYTE *)p_yaw + 24) = 1;
      }
    }
    ((NPC *)(p_yaw - 42))->NPC::UpdateAnim();
    if ( *((int *)p_yaw - 2) <= 150 )
      result = ((UIGameOver *)this)->InitParticle(v14);
    ++v14;
    p_yaw += 52;
  }
  while ( v14 < 0x16 );
  return result;
}

// 0x004533F0
int CCCTData::ProcessTask(int nVal)
{
  int v2; // edi
  int v3; // ebx
  unsigned __int8 v6; // al
  gbPrintFontMgr *pFontMgr; // edx
  gbPrintFont *v8; // ebp
  unsigned int Color; // edx
  int v10; // edx
  double v11; // st7
  unsigned __int8 *v12; // ecx
  int v13; // eax
  unsigned __int8 *v14; // ecx
  int v15; // ecx
  int v16; // eax
  double v17; // st7
  int v18; // edi
  gbGfxManager *pGfxMgr; // edx
  double v20; // st7
  char v21; // al
  char v22; // al
  char v23; // cl
  char v24; // dl
  char v25; // bl
  unsigned __int8 *v26; // ecx
  unsigned __int8 *v27; // ecx
  unsigned __int8 *v28; // edi
  unsigned __int8 *v29; // eax
  unsigned int dwID; // eax
  float fExpectTime; // ecx
  float v32; // [esp+0x10] [ebp-0x4C]
  float v33; // [esp+0x14] [ebp-0x48]
  __int16 v34; // [esp+0x30] [ebp-0x2C] BYREF
  char v35; // [esp+0x32] [ebp-0x2A]
  int v36; // [esp+0x34] [ebp-0x28]
  int v37; // [esp+0x38] [ebp-0x24]
  unsigned int v38; // [esp+0x3C] [ebp-0x20]
  unsigned int v39; // [esp+0x40] [ebp-0x1C]
  int v40; // [esp+0x44] [ebp-0x18]
  int v41; // [esp+0x48] [ebp-0x14]
  int v42; // [esp+0x4C] [ebp-0x10]
  int v43; // [esp+0x50] [ebp-0xC]
  int v44; // [esp+0x54] [ebp-0x8]
  gbColorQuad v45; // [esp+0x58] [ebp-0x4] BYREF

  v3 = 0;
  v43 = *(_DWORD *)(nVal + 8);
  v2 = v43;
  if ( v43 <= 0 )
    return 0;
  LOBYTE(v44) = HIBYTE(this->m_Pool[0].fp[1]);
  v6 = BYTE2(this->m_Pool[0].fp[1]);
  pFontMgr = gfxMgr->pFontMgr;
  LOBYTE(v42) = this->m_Pool[0].fp[1];
  v8 = pFontMgr->pAllFont[2];
  LOBYTE(v41) = BYTE1(this->m_Pool[0].fp[1]);
  LOBYTE(v40) = v6;
  // [AUTO-COMMENTED] Color = ((gbColorQuad *)&v45)->gbColorQuad(v6, v41, v42, v44)->Color;
  v37 = 0;
  v8->curColor.Color = Color;
  v34 = 0;
  v35 = 0;
  v10 = 20;
  v36 = 0;
  v11 = 40.0 / (double)g_DrvInfo.height;
  v42 = 20;
  v40 = 0;
  v8->ScaleX = 40.0 / (double)g_DrvInfo.width;
  v8->ScaleY = v11;
  v41 = 1;
  while ( 1 )
  {
    v12 = &g_bActorFlag;
    v13 = *(_DWORD *)(nVal + 4);
    if ( v13 )
      v12 = (unsigned __int8 *)(v13 + v3);
    if ( *v12 == 92 )
      break;
LABEL_28:
    v26 = &g_bActorFlag;
    v34 = 0;
    v35 = 0;
    if ( v13 )
      v26 = (unsigned __int8 *)(v13 + v3);
    if ( (char)*v26 <= 0 )
      goto LABEL_37;
    v27 = &g_bActorFlag;
    if ( v13 )
      v27 = (unsigned __int8 *)(v13 + v3);
    if ( *v27 == 127 )
    {
LABEL_37:
      if ( v41 >= v2 )
        goto LABEL_54;
      v28 = &g_bActorFlag;
      if ( v13 )
        v28 = (unsigned __int8 *)(v13 + v3);
      LOBYTE(v34) = *v28;
      if ( v13 )
        v29 = (unsigned __int8 *)(v13 + v3 + 1);
      else
        v29 = &g_bActorFlag;
      HIBYTE(v34) = *v29;
      v40 = v3 + 1;
      ++v41;
    }
    else if ( v13 )
    {
      LOBYTE(v34) = *(_BYTE *)(v3 + v13);
    }
    else
    {
      LOBYTE(v34) = g_bActorFlag;
    }
    v44 = this->m_Pool[0].dwID + v37 * v42 / 2;
    if ( (int)(v44 + v42 / 2 * strlen((const char *)&v34)) > SLODWORD(this->m_Pool[0].fStartTime) )
    {
      v37 = 0;
      dwID = this->m_Pool[0].dwID;
      v36 += v42 + 2;
      v44 = dwID;
    }
    fExpectTime = this->m_Pool[0].fExpectTime;
    v45.Color = v36 + v42 + *(_DWORD *)&this->m_Pool[0].bValid;
    if ( (int)v45.Color > SLODWORD(fExpectTime) )
    {
      v40 += 1 - strlen((const char *)&v34);
      v3 = v40;
      goto LABEL_54;
    }
    v33 = 1.0 - ((double)(int)v45.Color + (double)(int)v45.Color) / (double)g_DrvInfo.height;
    v32 = ((double)v44 + (double)v44) / (double)g_DrvInfo.width - 1.0;
    ((void ( *)(gbPrintFont *, __int16 *, _DWORD, _DWORD, int, int))v8->pGfxMgr->DrvInfo.subtype)(
      v8,
      &v34,
      LODWORD(v32),
      LODWORD(v33),
      1176256512,
      1176256512);
    v37 += strlen((const char *)&v34);
LABEL_48:
    v3 = v40;
LABEL_49:
    v40 = ++v3;
    ++v41;
    if ( v3 >= v43 )
      goto LABEL_54;
    v2 = v43;
    v10 = v42;
  }
  v40 = ++v3;
  ++v41;
  if ( v3 >= v2 )
  {
LABEL_54:
    ((void ( *)(gbPrintFont *))v8->pGfxMgr->hGfxWnd)(v8);
    return v3;
  }
  v14 = &g_bActorFlag;
  if ( v13 )
    v14 = (unsigned __int8 *)(v13 + v3);
  switch ( *v14 )
  {
    case 'b':
      ((void ( *)(gbPrintFont *))v8->pGfxMgr->hGfxWnd)(v8);
      v42 = 24;
      v37 = 0;
      v17 = 48.0 / (double)g_DrvInfo.height;
      v36 += 26;
      v16 = v36;
      v8->ScaleX = 48.0 / (double)g_DrvInfo.width;
      v8->ScaleY = v17;
      if ( *(_DWORD *)&this->m_Pool[0].bValid + v16 + 24 <= SLODWORD(this->m_Pool[0].fExpectTime) )
        goto LABEL_49;
      break;
    case 'i':
      v21 = HIBYTE(this->m_Pool[0].fp[1]);
      if ( gbColorQuad::ColorQuadFmt )
      {
        *(_WORD *)((char *)&v38 + 1) = -1;
        LOBYTE(v38) = 5;
      }
      else
      {
        *(_WORD *)((char *)&v38 + 1) = 1535;
        LOBYTE(v38) = -1;
      }
      HIBYTE(v38) = v21;
      v8->curColor.Color = v38;
      goto LABEL_49;
    case 'n':
      v15 = v10 + *(_DWORD *)&this->m_Pool[0].bValid;
      v37 = 0;
      v36 += v10 + 2;
      if ( v36 + v15 <= SLODWORD(this->m_Pool[0].fExpectTime) )
        goto LABEL_49;
      break;
    case 'p':
      break;
    case 'r':
      v22 = HIBYTE(this->m_Pool[0].fp[1]);
      v23 = (char)this->m_Pool[0].fp[1];
      v24 = BYTE1(this->m_Pool[0].fp[1]);
      v25 = BYTE2(this->m_Pool[0].fp[1]);
      if ( gbColorQuad::ColorQuadFmt )
      {
        BYTE2(v39) = this->m_Pool[0].fp[1];
        BYTE1(v39) = v24;
        LOBYTE(v39) = v25;
      }
      else
      {
        BYTE2(v39) = BYTE2(this->m_Pool[0].fp[1]);
        BYTE1(v39) = v24;
        LOBYTE(v39) = v23;
      }
      HIBYTE(v39) = v22;
      v8->curColor.Color = v39;
      goto LABEL_48;
    case 's':
      v18 = v36 + v10 + 2;
      pGfxMgr = v8->pGfxMgr;
      v36 = v18;
      ((void ( *)(gbPrintFont *))pGfxMgr->hGfxWnd)(v8);
      v42 = 20;
      v37 = 0;
      v20 = 40.0 / (double)g_DrvInfo.height;
      v8->ScaleX = 40.0 / (double)g_DrvInfo.width;
      v8->ScaleY = v20;
      if ( *(_DWORD *)&this->m_Pool[0].bValid + v18 + 20 <= SLODWORD(this->m_Pool[0].fExpectTime) )
        goto LABEL_49;
      break;
    case 't':
      v37 = 8 * ((v37 + 8) / 8);
      goto LABEL_49;
    default:
      v2 = v43;
      goto LABEL_28;
  }
  ((void ( *)(gbPrintFont *))v8->pGfxMgr->hGfxWnd)(v8);
  return v3 + 1;
}

// 0x004A6730
CCCTData * CCCTData::InitImages()
{
  char v3; // [esp+0xF] [ebp-0x11]

  LOBYTE(this->m_Pool[2].fp[0]) = v3;
  this->m_Pool[2].fp[1] = 0;
  this->m_Pool[2].fp[2] = 0;
  this->m_Pool[2].fp[3] = 0;
  this->m_Pool[0].fp[0] = 0;
  this->m_Pool[1].dwReserved[1] = 0;
  LOBYTE(this->m_Pool[2].dwID) = 0;
  return this;
}

// 0x004A67B0
void CCCTData::DestroyImage()
{
  gbImage2D *v2; // esi
  gbImage2D *v3; // edi
  char *v4; // eax
  int *v5; // eax
  int v6; // ebx
  int v7; // edi
  int *j; // esi
  bool v9; // zf
  int *i; // [esp+0x10] [ebp-0x24]
  char *v11; // [esp+0x14] [ebp-0x20]
  char *v12; // [esp+0x18] [ebp-0x1C]
  char **v13; // [esp+0x20] [ebp-0x14]

  v2 = (gbImage2D *)&this->m_Pool[0].fp[1];
  v13 = &this->m_Pool[0].fp[1];
  ((gbImage2D *)&this->m_Pool[0].fp[1])->Release();
  v3 = (gbImage2D *)&this->m_Pool[1];
  ((gbImage2D *)&this->m_Pool[1])->Release();
  v4 = this->m_Pool[2].fp[1];
  v12 = this->m_Pool[2].fp[2];
  v11 = v4;
  if ( v4 != v12 )
  {
    v5 = (int *)(v4 + 12);
    for ( i = v5; ; v5 = i )
    {
      v6 = v5[1];
      v7 = *v5;
      for ( j = v5 - 1; v7 != v6; v7 += 16 )
        ((CEffect *)j)->Update(v7);
      operator delete((void *)j[1]);
      j[1] = 0;
      j[2] = 0;
      j[3] = 0;
      v9 = v11 + 24 == v12;
      v11 += 24;
      i += 6;
      if ( v9 )
        break;
    }
    v3 = (gbImage2D *)&this->m_Pool[1];
    v2 = (gbImage2D *)v13;
  }
  operator delete(this->m_Pool[2].fp[1]);
  this->m_Pool[2].fp[1] = 0;
  this->m_Pool[2].fp[2] = 0;
  this->m_Pool[2].fp[3] = 0;
}

// 0x004A6F10
CCCTData::CCCTData()
{
  float *p_fCircleCentreX; // eax
  CHAR *v3; // ebp
  bool v4; // zf
  float *v6; // [esp+0x10] [ebp-0x18]
  int v7; // [esp+0x14] [ebp-0x14]

  *(_DWORD *)&this->m_Pool[0].bStartCamValid = 800;
  *(_DWORD *)&this->m_Pool[0].bLineMove = 600;
  *(_DWORD *)&this->m_Pool[0].bAbsoluteTime = 0;
  *(_DWORD *)&this->m_Pool[0].bRandSwing = 0;
  sub_4422E0(&this->m_Pool[1].fCircleEndZ);
  p_fCircleCentreX = &this->m_Pool[2].fCircleCentreX;
  v6 = &this->m_Pool[2].fCircleCentreX;
  v7 = 28;
  v3 = (CHAR *)&this->m_Pool[2].dwReserved[1];
  while ( 1 )
  {
    *p_fCircleCentreX = 0.0;
    lstrcpyA(v3 - 32, g_szSceneUIText);
    lstrcpyA(v3, g_szSceneUIText);
    memset(v3 + 532, 0, 0x18u);
    v3 += 760;
    v4 = v7 == 1;
    v6 += 190;
    --v7;
    if ( v4 )
      break;
    p_fCircleCentreX = v6;
  }
  BYTE1(this->m_Pool[107].fp[3]) = 0;
  BYTE2(this->m_Pool[107].fp[3]) = 1;
  HIBYTE(this->m_Pool[107].fp[3]) = 1;
  this->m_Pool[107].dwID = 0;
  *(_DWORD *)&this->m_Pool[107].bValid = 0;
  this->m_Pool[107].fStartTime = 180.0;
  LODWORD(this->m_Pool[114].fStartTracePosY) = 300;
  this->m_Pool[114].fStartTracePosZ = 0.0;
  this->m_Pool[114].dwReserved[0] = 0;
  sub_4422E0(&this->m_Pool[114].dwReserved[1]);
  sub_4422E0(&this->m_Pool[115].fCircleCentreZ);
  sub_4422E0(&this->m_Pool[116].bAbsoluteTime);
  sub_4422E0(&this->m_Pool[117].StartPos.yaw);
  sub_4422E0(this->m_Pool[117].dwReserved);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0(&this->m_Pool[133].fEndFOV);
  sub_4422E0(&this->m_Pool[134].fCircleCentreY);
  sub_4422E0(&this->m_Pool[135].bLineMove);
  sub_4422E0(&this->m_Pool[869].fCircleEndX);
  sub_4422E0(&this->m_Pool[870].bRandSwing);
  sub_4422E0(&this->m_Pool[871].StartPos.pit);
  sub_4422E0(&this->m_Pool[871].dwReserved[1]);
  ((UIProgressBar *)&this->m_Pool[872].fCircleCentreZ)->ctor();
  ((UIProgressBar *)&this->m_Pool[874].StartPos.pit)->ctor();
  sub_4422E0(&this->m_Pool[875].fCircleEndX);
  sub_4422E0(&this->m_Pool[876].bRandSwing);
  sub_4422E0(&this->m_Pool[877].StartPos.pit);
  UIScene::GetSys();
  LOBYTE(this->m_Pool[907].dwReserved[1]) = 1;
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  ((CCCTData *)&this->m_Pool[1876].StartPos.z)->InitImages();
  LOBYTE(this->m_Pool[1878].EndPos.yaw) = 0;
  this->m_Pool[1878].EndPos.z = 0.0;
  this->m_Pool[1878].EndPos.y = 0.0;
  this->m_Pool[1878].bStartCamValid = 0;
  this->m_Pool[1878].nEndCam = 0;
  this->m_Pool[1878].nStartCam = 0;
  ((UI3DCtrl *)&this->m_Pool[1878].fStartTracePosY)->ctor_D830();
  ((UI3DCtrl *)&this->m_Pool[1879].EndPos.yaw)->ctor_D830();
  sub_4422E0(&this->m_Pool[1888].StartPos.y);
  sub_4422E0(&this->m_Pool[1888].fStartTracePosY);
  ((UI3DCtrl *)&this->m_Pool[1889].fAngleSpeed)->ctor_D830();
  sub_4422E0(&this->m_Pool[1890].dwID);
  sub_4422E0(&this->m_Pool[1890].fSwing);
  sub_4422E0(&this->m_Pool[1891].fAccelerationTime1);
  sub_4422E0(&this->m_Pool[1892].EndPos.z);
  sub_4422E0(&this->m_Pool[1893].fp[3]);
  ((UIListBox *)&this->m_Pool[1911].fCircleCentreX)->UpdateKeyCtrl();
  ((UIListBox *)&this->m_Pool[1917].fAcceleration1)->UpdateKeyCtrl();
  ((UIListBox *)&this->m_Pool[1923].fStartSpeed)->UpdateKeyCtrl();
  ((UIListBox *)&this->m_Pool[1929].bLineMove)->UpdateKeyCtrl();
  ((UIListBox *)&this->m_Pool[1935].EndPos.rol)->UpdateKeyCtrl();
  ((UIListBox *)&this->m_Pool[1941].EndPos.y)->UpdateKeyCtrl();
  sub_4422E0(&this->m_Pool[1947].EndPos.y);
  sub_4422E0(&this->m_Pool[1948].fp[2]);
  sub_4422E0(&this->m_Pool[1948].fCircleEndZ);
  sub_4422E0(&this->m_Pool[1949].fAcceleration1);
  ((UI3DCtrl *)&this->m_Pool[1950].EndPos.pit)->ctor_D830();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  this->m_Pool[1960].dwReserved[0] = 0;
  ((ScriptSystem *)&this->m_Pool[1960].dwReserved[1])->ClearTimerSlot();
  ((ARC_PlayerAtt *)&this->m_Pool[1961].StartPos.y)->Refresh();
  ((ARC_PlayerAtt *)&this->m_Pool[1967].fEndFOV)->Refresh();
  g_nRoleParam = 0;
  g_nRoleState = 0;
  g_nActorState = 0;
  LOWORD(g_nActor_DE5FA8) = 0;
  LOBYTE(g_nActor_DE5F9C) = 0;
  this->m_Pool[869].fCircleCentreX = 0.0;
  this->m_Pool[869].fCircleCentreY = 0.0;
  this->m_Pool[869].fCircleCentreZ = 0.0;
  LOBYTE(this->m_Pool[1878].EndPos.pit) = 1;
  BYTE1(this->m_Pool[1878].EndPos.pit) = 0;
  BYTE2(this->m_Pool[1878].EndPos.pit) = 1;
  HIBYTE(this->m_Pool[1878].EndPos.pit) = 1;
  this->m_Pool[1878].EndPos.rol = 0.0;
  *(_DWORD *)&this->m_Pool[1878].bAbsoluteTime = 100;
  *(_DWORD *)&this->m_Pool[1878].bLineMove = 1000;
  this->m_Pool[107].fp[0] = 0;
  this->m_Pool[2].fInertia = 0.0;
  this->m_Pool[2].fStartSpeed = 0.0;
  this->m_Pool[2].fAcceleration2 = 0.0;
  this->m_Pool[2].fAcceleration1 = 0.0;
  this->m_Pool[2].fAccelerationTime2 = 0.0;
  this->m_Pool[2].fAccelerationTime1 = 0.0;
  this->m_Pool[2].fAngleSpeed = 0.0;
  this->m_Pool[2].fCircleAngle = 0.0;
  (int)this;
}

// 0x004A8770
int CCCTData::CreateUI()
{
  float z; // eax
  float *p_z; // edi
  unsigned int dwID; // eax
  int v5; // ecx
  float fCircleCentreX; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // eax
  int v17; // ecx
  float *p_fSwingFre; // edi
  int v19; // ebp
  int v20; // eax
  float fCircleEndX; // edx
  int v22; // edx
  int v23; // eax
  float fStartTime; // edx
  int v25; // eax
  float fSwingFre; // edx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  float fSwing; // eax
  float fAccelerationTime1; // edx
  int v32; // ecx
  int v33; // eax
  int v34; // ecx
  int v35; // eax
  float *p_fCircleEndX; // edi
  int v37; // ebp
  int v38; // eax
  float yaw; // edx
  float fStartTracePosX; // edx
  int v41; // eax
  float fAccelerationTime2; // edx
  int v43; // eax
  float x; // edx
  int v45; // eax
  float fStartTracePosY; // eax
  float v47; // edx
  float y; // eax
  float v49; // edx
  int v50; // eax
  float fTimeExpiate; // edx
  float v52; // eax
  int v53; // ecx
  float fCircleEndZ; // edx
  int p_DWORD; // [esp+0x2BC] [ebp-D0h] BYREF
  int v57; // [esp+0x2C0] [ebp-CCh]
  int nHeight; // [esp+0x2C4] [ebp-C8h]
  int v59; // [esp+0x2C8] [ebp-C4h]
  _DWORD v60[2]; // [esp+0x2CC] [ebp-C0h] BYREF
  int v61; // [esp+0x2D4] [ebp-B8h]
  int v62; // [esp+0x2D8] [ebp-B4h]
  int v63; // [esp+0x2DC] [ebp-B0h] BYREF
  int v64; // [esp+0x2E0] [ebp-ACh]
  int v65; // [esp+0x2E4] [ebp-A8h]
  int v66; // [esp+0x2E8] [ebp-A4h]
  _DWORD v67[2]; // [esp+0x2EC] [ebp-A0h] BYREF
  int v68; // [esp+0x2F4] [ebp-0x98]
  int v69; // [esp+0x2F8] [ebp-0x94]
  int v70; // [esp+0x2FC] [ebp-0x90] BYREF
  int v71; // [esp+0x300] [ebp-0x8C]
  int v72; // [esp+0x304] [ebp-0x88]
  int v73; // [esp+0x308] [ebp-0x84]
  int v74; // [esp+0x30C] [ebp-0x80] BYREF
  int v75; // [esp+0x310] [ebp-0x7C]
  int v76; // [esp+0x314] [ebp-0x78]
  int v77; // [esp+0x318] [ebp-0x74]
  gbVec3D pDir; // [esp+0x31C] [ebp-0x70] BYREF
  int v79; // [esp+0x328] [ebp-0x64]
  int v80; // [esp+0x32C] [ebp-0x60] BYREF
  int v81; // [esp+0x330] [ebp-0x5C]
  int v82; // [esp+0x334] [ebp-0x58]
  int v83; // [esp+0x338] [ebp-0x54]
  gbVec3D pPos; // [esp+0x33C] [ebp-0x50] BYREF
  int v85; // [esp+0x348] [ebp-0x44]
  int v86; // [esp+0x34C] [ebp-0x40] BYREF
  int v87; // [esp+0x350] [ebp-0x3C]
  int v88; // [esp+0x354] [ebp-0x38]
  int v89; // [esp+0x358] [ebp-0x34]
  _DWORD v90[2]; // [esp+0x35C] [ebp-0x30] BYREF
  int v91; // [esp+0x364] [ebp-0x28]
  int v92; // [esp+0x368] [ebp-0x24]
  _DWORD v93[4]; // [esp+0x36C] [ebp-0x20] BYREF
  _DWORD v94[4]; // [esp+0x37C] [ebp-0x10] BYREF

  z = this->m_Pool[1892].EndPos.z;
  p_z = &this->m_Pool[1892].EndPos.z;
  v64 = 108;
  v63 = 52;
  v65 = 388;
  v66 = 501;
  (*(void ( **)(float *, __int16 *, int *, CCCTData *))(LODWORD(z) + 16))(
    &this->m_Pool[1892].EndPos.z,
    &word_A00552,
    &v63,
    this);
  ((UIStatic *)p_z)->CreateFromTemplate();
  (**(void ( ***)(float *, _DWORD))p_z)(p_z, 0);
  v75 = v64 + 52;
  v74 = v63 + 10;
  v77 = v64 + 84;
  dwID = this->m_Pool[1890].dwID;
  v76 = v65;
  (*(void ( **)(unsigned int *, __int16 *, int *, CCCTData *))(dwID + 16))(
    &this->m_Pool[1890].dwID,
    &word_A00552,
    &v74,
    this);
  ((UIScene *)&this->m_Pool[1890].dwID)->SetShow(0);
  sub_446010(&this->m_Pool[1890].dwID);
  sprintf(
    (char *const)&this->m_Pool[0].nTraceRole,
    " %s            %s %s  %s",
    (const char *)dword_DC353C,
    (const char *)dword_DC373C,
    (const char *)dword_DCF73C,
    (const char *)dword_DC363C);
  ((UICaption *)&this->m_Pool[1890].dwID)->SetEnable((int)&this->m_Pool[0].nTraceRole, 0);
  v93[0] = v63;
  v93[1] = v64 + 2;
  v93[3] = v64 + 34;
  v93[2] = v65;
  (*(void ( **)(float *, __int16 *, _DWORD *, char *, _DWORD, CCCTData *))(LODWORD(this->m_Pool[1889].fAngleSpeed)
                                                                                   + 28))(
    &this->m_Pool[1889].fAngleSpeed,
    &word_A00552,
    v93,
    "UI\\Flex\\Bar.tga",
    0,
    this);
  ((CScreenMode *)&this->m_Pool[1889].fAngleSpeed)->SetPosition(32,   32);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1889].fAngleSpeed))(&this->m_Pool[1889].fAngleSpeed, 0);
  p_DWORD = v63 + 18;
  v57 = v64 + 76;
  v59 = v64 + 364;
  LODWORD(pPos.y) = v64 + 91;
  nHeight = v63 + 316;
  v5 = v63 + 307;
  v85 = v64 + 117;
  LODWORD(pPos.z) = v63 + 307;
  LODWORD(pDir.z) = v63 + 307;
  LOBYTE(v5) = g_bDebugMode;
  LODWORD(pDir.y) = v64 + 323;
  LODWORD(pPos.x) = v63 + 285;
  LODWORD(pDir.x) = v63 + 285;
  fCircleCentreX = this->m_Pool[1911].fCircleCentreX;
  v79 = v64 + 349;
  v7 = (*(int ( **)(float *, char *, int *, CCCTData *, _DWORD, int, int))(LODWORD(fCircleCentreX) + 28))(
         &this->m_Pool[1911].fCircleCentreX,
         byte_A00529,
         &p_DWORD,
         this,
         0,
         1,
         v5);
  LOBYTE(v7) = g_bDebugMode;
  ((UIListBox *)&this->m_Pool[1911].fCircleCentreX)->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v7);
  this->m_Pool[1917].EndPos.rol = NAN;
  ((UIListBox *)&this->m_Pool[1911].fCircleCentreX)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_Pool[1912].dwID)->ShowEffect(v57 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_Pool[1912].dwID)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_Pool[1912].dwID)->SetSelection(27);
  ((CCBUI *)&this->m_Pool[1912].dwID)->SetCurPlayer(5);
  ((UIListBox *)&this->m_Pool[1911].fCircleCentreX)->SetLockSel();
  ((UIListBox *)&this->m_Pool[1911].fCircleCentreX)->SetFirstShow((int)"Name", 130);
  ((UIListBox *)&this->m_Pool[1911].fCircleCentreX)->SetFirstShow((int)&g_pCombatUIData, 38);
  ((UIListBox *)&this->m_Pool[1911].fCircleCentreX)->SetFirstShow((int)"Gu", 38);
  ((UIListBox *)&this->m_Pool[1911].fCircleCentreX)->SetFirstShow((int)"Price", 50);
  ((CCBUI *)&this->m_Pool[1912].dwID)->VirtualCall();
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1911].fCircleCentreX))(
    &this->m_Pool[1911].fCircleCentreX,
    0);
  LOBYTE(this->m_Pool[1912].fp[3]) = 0;
  LOBYTE(v8) = g_bDebugMode;
  v9 = (*(int ( **)(float *, char *, int *, CCCTData *, _DWORD, int, int))(LODWORD(this->m_Pool[1917].fAcceleration1)
                                                                                   + 28))(
         &this->m_Pool[1917].fAcceleration1,
         &byte_A00530,
         &p_DWORD,
         this,
         0,
         1,
         v8);
  LOBYTE(v9) = g_bDebugMode;
  ((UIListBox *)&this->m_Pool[1917].fAcceleration1)->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v9);
  this->m_Pool[1923].EndPos.y = NAN;
  ((UIListBox *)&this->m_Pool[1917].fAcceleration1)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_Pool[1918])->ShowEffect(v57 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_Pool[1918])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_Pool[1918])->SetSelection(27);
  ((CCBUI *)&this->m_Pool[1918])->SetCurPlayer(5);
  ((UIListBox *)&this->m_Pool[1917].fAcceleration1)->SetLockSel();
  ((UIListBox *)&this->m_Pool[1917].fAcceleration1)->SetFirstShow((int)"Name", 130);
  ((UIListBox *)&this->m_Pool[1917].fAcceleration1)->SetFirstShow((int)&g_pCombatUIData, 38);
  ((UIListBox *)&this->m_Pool[1917].fAcceleration1)->SetFirstShow((int)"Gu", 38);
  ((UIListBox *)&this->m_Pool[1917].fAcceleration1)->SetFirstShow((int)"Price", 50);
  ((CCBUI *)&this->m_Pool[1918])->VirtualCall();
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1917].fAcceleration1))(
    &this->m_Pool[1917].fAcceleration1,
    0);
  LOBYTE(this->m_Pool[1917].dwReserved[1]) = 0;
  LOBYTE(v10) = g_bDebugMode;
  v11 = (*(int ( **)(float *, char *, int *, CCCTData *, _DWORD, int, int))(LODWORD(this->m_Pool[1923].fStartSpeed)
                                                                                    + 28))(
          &this->m_Pool[1923].fStartSpeed,
          &byte_A00531,
          &p_DWORD,
          this,
          0,
          1,
          v10);
  LOBYTE(v11) = g_bDebugMode;
  ((UIListBox *)&this->m_Pool[1923].fStartSpeed)->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v11);
  this->m_Pool[1929].StartPos.yaw = NAN;
  ((UIListBox *)&this->m_Pool[1923].fStartSpeed)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_Pool[1923].fStartTracePosY)->ShowEffect(v57 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_Pool[1923].fStartTracePosY)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_Pool[1923].fStartTracePosY)->SetSelection(27);
  ((CCBUI *)&this->m_Pool[1923].fStartTracePosY)->SetCurPlayer(5);
  ((UIListBox *)&this->m_Pool[1923].fStartSpeed)->SetLockSel();
  ((UIListBox *)&this->m_Pool[1923].fStartSpeed)->SetFirstShow((int)"Name", 130);
  ((UIListBox *)&this->m_Pool[1923].fStartSpeed)->SetFirstShow((int)&g_pCombatUIData, 38);
  ((UIListBox *)&this->m_Pool[1923].fStartSpeed)->SetFirstShow((int)"Gu", 38);
  ((UIListBox *)&this->m_Pool[1923].fStartSpeed)->SetFirstShow((int)"Price", 50);
  ((CCBUI *)&this->m_Pool[1923].fStartTracePosY)->VirtualCall();
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1923].fStartSpeed))(&this->m_Pool[1923].fStartSpeed, 0);
  LOBYTE(this->m_Pool[1923].fStartTracePosX) = 0;
  LOBYTE(v12) = g_bDebugMode;
  v13 = (*(int ( **)(_BYTE *, char *, int *, CCCTData *, _DWORD, int, int))(*(_DWORD *)&this->m_Pool[1929].bLineMove
                                                                                    + 28))(
          &this->m_Pool[1929].bLineMove,
          &byte_A00532,
          &p_DWORD,
          this,
          0,
          1,
          v12);
  LOBYTE(v13) = g_bDebugMode;
  ((UIListBox *)&this->m_Pool[1929].bLineMove)->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v13);
  this->m_Pool[1935].fExpectTime = NAN;
  ((UIListBox *)&this->m_Pool[1929].bLineMove)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_Pool[1929].fTimeExpiate)->ShowEffect(v57 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_Pool[1929].fTimeExpiate)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_Pool[1929].fTimeExpiate)->SetSelection(27);
  ((CCBUI *)&this->m_Pool[1929].fTimeExpiate)->SetCurPlayer(5);
  ((UIListBox *)&this->m_Pool[1929].bLineMove)->SetLockSel();
  ((UIListBox *)&this->m_Pool[1929].bLineMove)->SetFirstShow((int)"Name", 130);
  ((UIListBox *)&this->m_Pool[1929].bLineMove)->SetFirstShow((int)&g_pCombatUIData, 38);
  ((UIListBox *)&this->m_Pool[1929].bLineMove)->SetFirstShow((int)"Gu", 38);
  ((UIListBox *)&this->m_Pool[1929].bLineMove)->SetFirstShow((int)"Price", 50);
  ((CCBUI *)&this->m_Pool[1929].fTimeExpiate)->VirtualCall();
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_Pool[1929].bLineMove)(&this->m_Pool[1929].bLineMove, 0);
  LOBYTE(this->m_Pool[1929].fSwing) = 0;
  LOBYTE(v14) = g_bDebugMode;
  v15 = (*(int ( **)(float *, char *, int *, CCCTData *, _DWORD, int, int))(LODWORD(this->m_Pool[1935].EndPos.rol)
                                                                                    + 28))(
          &this->m_Pool[1935].EndPos.rol,
          &byte_A00533,
          &p_DWORD,
          this,
          0,
          1,
          v14);
  LOBYTE(v15) = g_bDebugMode;
  ((UIListBox *)&this->m_Pool[1935].EndPos.rol)->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v15);
  this->m_Pool[1941].fp[3] = (char *)-4;
  ((UIListBox *)&this->m_Pool[1935].EndPos.rol)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_Pool[1935].fCircleEndY)->ShowEffect(v57 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_Pool[1935].fCircleEndY)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_Pool[1935].fCircleEndY)->SetSelection(27);
  ((CCBUI *)&this->m_Pool[1935].fCircleEndY)->SetCurPlayer(5);
  ((UIListBox *)&this->m_Pool[1935].EndPos.rol)->SetLockSel();
  ((UIListBox *)&this->m_Pool[1935].EndPos.rol)->SetFirstShow((int)"Name", 130);
  ((UIListBox *)&this->m_Pool[1935].EndPos.rol)->SetFirstShow((int)&g_pCombatUIData, 38);
  ((UIListBox *)&this->m_Pool[1935].EndPos.rol)->SetFirstShow((int)"Gu", 38);
  ((UIListBox *)&this->m_Pool[1935].EndPos.rol)->SetFirstShow((int)"Price", 50);
  ((CCBUI *)&this->m_Pool[1935].fCircleEndY)->VirtualCall();
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1935].EndPos.rol))(&this->m_Pool[1935].EndPos.rol, 0);
  v16 = v57 + 2;
  v70 = p_DWORD;
  v17 = p_DWORD + 256;
  v71 = v57 + 2;
  LOBYTE(this->m_Pool[1935].fCircleEndX) = 0;
  v72 = v17;
  v73 = v16 + 23;
  p_fSwingFre = &this->m_Pool[1893].fSwingFre;
  v19 = 12;
  do
  {
    (*(void ( **)(float *, __int16 *, int *, CCCTData *))(*(_DWORD *)p_fSwingFre + 16))(
      p_fSwingFre,
      &word_A00552,
      &v70,
      this);
    ((UIStatic *)p_fSwingFre)->CreateFromTemplate();
    (**(void ( ***)(float *, _DWORD))p_fSwingFre)(p_fSwingFre, 0);
    p_fSwingFre += 38;
    v71 = v73;
    --v19;
    v73 += 23;
  }
  while ( v19 );
  v60[1] = v64;
  v20 = v64 + 50;
  v60[0] = v63 + 16;
  v62 = v64 + 50;
  LOBYTE(v20) = g_bDebugMode;
  fCircleEndX = this->m_Pool[1879].fCircleEndX;
  v61 = v63 + 56;
  (*(void ( **)(float *, char *, _DWORD *, CCCTData *, char *, _DWORD, int))(LODWORD(fCircleEndX) + 28))(
    &this->m_Pool[1879].fCircleEndX,
    byte_A00559,
    v60,
    this,
    "UI\\GameMainUI\\Equip\\Weapon",
    0,
    v20);
  ((PalScript *)&this->m_Pool[1879].fCircleEndX)->OpenScript("UI\\GameMainUI\\Equip\\Weapon2.tga", g_bDebugMode);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1879].fCircleEndX))(&this->m_Pool[1879].fCircleEndX, 0);
  v22 = *(_DWORD *)&this->m_Pool[1881].bStartCamValid;
  v60[0] = v61 + 26;
  v61 += 66;
  v23 = v61;
  LOBYTE(v23) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, _DWORD *, CCCTData *, char *, _DWORD, int))(v22 + 28))(
    &this->m_Pool[1881].bStartCamValid,
    &byte_A00560,
    v60,
    this,
    "UI\\GameMainUI\\Equip\\Cloth",
    0,
    v23);
  ((PalScript *)&this->m_Pool[1881].bStartCamValid)->OpenScript("UI\\GameMainUI\\Equip\\Cloth2.tga", g_bDebugMode);
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_Pool[1881].bStartCamValid)(&this->m_Pool[1881].bStartCamValid, 0);
  fStartTime = this->m_Pool[1883].fStartTime;
  v60[0] = v61 + 26;
  v61 += 66;
  v25 = v61;
  LOBYTE(v25) = g_bDebugMode;
  (*(void ( **)(float *, char *, _DWORD *, CCCTData *, char *, _DWORD, int))(LODWORD(fStartTime) + 28))(
    &this->m_Pool[1883].fStartTime,
    &byte_A00561,
    v60,
    this,
    "UI\\GameMainUI\\Equip\\Hat",
    0,
    v25);
  ((PalScript *)&this->m_Pool[1883].fStartTime)->OpenScript("UI\\GameMainUI\\Equip\\Hat2.tga", g_bDebugMode);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1883].fStartTime))(&this->m_Pool[1883].fStartTime, 0);
  fSwingFre = this->m_Pool[1884].fSwingFre;
  v60[0] = v61 + 26;
  v61 += 66;
  v27 = v61;
  LOBYTE(v27) = g_bDebugMode;
  (*(void ( **)(float *, char *, _DWORD *, CCCTData *, char *, _DWORD, int))(LODWORD(fSwingFre) + 28))(
    &this->m_Pool[1884].fSwingFre,
    &byte_A00562,
    v60,
    this,
    "UI\\GameMainUI\\Equip\\Shoes",
    0,
    v27);
  ((PalScript *)&this->m_Pool[1884].fSwingFre)->OpenScript("UI\\GameMainUI\\Equip\\Shoes2.tga", g_bDebugMode);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1884].fSwingFre))(&this->m_Pool[1884].fSwingFre, 0);
  v28 = *(_DWORD *)&this->m_Pool[1886].bRandSwing;
  v60[0] = v61 + 26;
  v61 += 66;
  v29 = v61;
  LOBYTE(v29) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, _DWORD *, CCCTData *, char *, _DWORD, int))(v28 + 28))(
    &this->m_Pool[1886].bRandSwing,
    &byte_A00563,
    v60,
    this,
    "UI\\GameMainUI\\Equip\\Adorn",
    0,
    v29);
  ((PalScript *)&this->m_Pool[1886].bRandSwing)->OpenScript("UI\\GameMainUI\\Equip\\Adorn2.tga", g_bDebugMode);
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_Pool[1886].bRandSwing)(&this->m_Pool[1886].bRandSwing, 0);
  v81 = v64;
  v80 = v65 + 6;
  v83 = v66;
  v82 = v65 + 342;
  (*((void ( **)(char **, __int16 *, int *, CCCTData *))this->m_Pool[1893].fp[3] + 4))(
    &this->m_Pool[1893].fp[3],
    &word_A00552,
    &v80,
    this);
  ((UIStatic *)&this->m_Pool[1893].fp[3])->CreateFromTemplate();
  (*(void ( **)(char **, _DWORD))this->m_Pool[1893].fp[3])(&this->m_Pool[1893].fp[3], 0);
  v75 = v81 + 52;
  v74 = v80 + 10;
  v77 = v81 + 84;
  fSwing = this->m_Pool[1890].fSwing;
  v76 = v82;
  (*(void ( **)(float *, __int16 *, int *, CCCTData *))(LODWORD(fSwing) + 16))(
    &this->m_Pool[1890].fSwing,
    &word_A00552,
    &v74,
    this);
  ((UIScene *)&this->m_Pool[1890].fSwing)->SetShow(0);
  sub_446010(&this->m_Pool[1890].fSwing);
  sprintf(
    (char *const)&this->m_Pool[0].nTraceRole,
    " %s            %s %s  %s",
    (const char *)dword_DC353C,
    (const char *)dword_DC373C,
    (const char *)dword_DCF73C,
    (const char *)dword_DC363C);
  ((UICaption *)&this->m_Pool[1890].fSwing)->SetEnable((int)&this->m_Pool[0].nTraceRole, 0);
  fAccelerationTime1 = this->m_Pool[1891].fAccelerationTime1;
  v75 = v81;
  v74 = v80 + 7;
  v77 = v81 + 49;
  v76 = v80 + 327;
  (*(void ( **)(float *, __int16 *, int *, CCCTData *))(LODWORD(fAccelerationTime1) + 16))(
    &this->m_Pool[1891].fAccelerationTime1,
    &word_A00552,
    &v74,
    this);
  ((UIStatic *)&this->m_Pool[1891].fAccelerationTime1)->CreateFromTemplate();
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1891].fAccelerationTime1))(
    &this->m_Pool[1891].fAccelerationTime1,
    0);
  p_DWORD = v80 + 18;
  v57 = v81 + 76;
  v59 = v81 + 364;
  LODWORD(pPos.y) = v81 + 91;
  nHeight = v80 + 316;
  v32 = v80 + 307;
  v85 = v81 + 117;
  LODWORD(pPos.z) = v80 + 307;
  LODWORD(pDir.z) = v80 + 307;
  LOBYTE(v32) = g_bDebugMode;
  LODWORD(pDir.y) = v81 + 323;
  v79 = v81 + 349;
  LODWORD(pPos.x) = v80 + 285;
  LODWORD(pDir.x) = v80 + 285;
  v33 = (*(int ( **)(float *, char *, int *, CCCTData *, _DWORD, int, int))(LODWORD(this->m_Pool[1941].EndPos.y)
                                                                                    + 28))(
          &this->m_Pool[1941].EndPos.y,
          byte_A00534,
          &p_DWORD,
          this,
          0,
          1,
          v32);
  LOBYTE(v33) = g_bDebugMode;
  ((UIListBox *)&this->m_Pool[1941].EndPos.y)->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v33);
  this->m_Pool[1946].dwReserved[1] = -4;
  ((UIListBox *)&this->m_Pool[1941].EndPos.y)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_Pool[1941].fCircleCentreX)->ShowEffect(v57 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_Pool[1941].fCircleCentreX)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_Pool[1941].fCircleCentreX)->SetSelection(27);
  ((CCBUI *)&this->m_Pool[1941].fCircleCentreX)->SetCurPlayer(5);
  ((UIListBox *)&this->m_Pool[1941].EndPos.y)->SetLockSel();
  ((UIListBox *)&this->m_Pool[1941].EndPos.y)->SetFirstShow((int)"Name", 130);
  ((UIListBox *)&this->m_Pool[1941].EndPos.y)->SetFirstShow((int)&g_pCombatUIData, 38);
  ((UIListBox *)&this->m_Pool[1941].EndPos.y)->SetFirstShow((int)"Gu", 38);
  ((UIListBox *)&this->m_Pool[1941].EndPos.y)->SetFirstShow((int)"Price", 50);
  ((CCBUI *)&this->m_Pool[1941].fCircleCentreX)->VirtualCall();
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1941].EndPos.y))(&this->m_Pool[1941].EndPos.y, 0);
  v70 = p_DWORD;
  v71 = v57 + 2;
  v34 = p_DWORD + 256;
  v35 = v57 + 25;
  LOBYTE(this->m_Pool[1941].fAngleSpeed) = 0;
  v72 = v34;
  v73 = v35;
  p_fCircleEndX = &this->m_Pool[1902].fCircleEndX;
  v37 = 12;
  do
  {
    (*(void ( **)(float *, __int16 *, int *, CCCTData *))(*(_DWORD *)p_fCircleEndX + 16))(
      p_fCircleEndX,
      &word_A00552,
      &v70,
      this);
    ((UIStatic *)p_fCircleEndX)->CreateFromTemplate();
    (**(void ( ***)(float *, _DWORD))p_fCircleEndX)(p_fCircleEndX, 0);
    p_fCircleEndX += 38;
    v71 = v73;
    v38 = v73 + 23;
    --v37;
    v73 += 23;
  }
  while ( v37 );
  LOBYTE(v38) = g_bDebugMode;
  yaw = this->m_Pool[1954].StartPos.yaw;
  v67[1] = 474;
  v67[0] = 124;
  v68 = 220;
  v69 = 500;
  (*(void ( **)(float *, char *, _DWORD *, CCCTData *, char *, int, int))(LODWORD(yaw) + 28))(
    &this->m_Pool[1954].StartPos.yaw,
    &byte_A00555,
    v67,
    this,
    "UI\\GameMainUI\\Communal\\SortPrice",
    1,
    v38);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1954].StartPos.yaw))(
    &this->m_Pool[1954].StartPos.yaw,
    0);
  fStartTracePosX = this->m_Pool[1955].fStartTracePosX;
  v67[0] = v68 + 6;
  v68 += 102;
  v41 = v68;
  LOBYTE(v41) = g_bDebugMode;
  (*(void ( **)(float *, char *, _DWORD *, CCCTData *, char *, int, int))(LODWORD(fStartTracePosX) + 28))(
    &this->m_Pool[1955].fStartTracePosX,
    &byte_A00556,
    v67,
    this,
    "UI\\GameMainUI\\Sword\\SortGu",
    1,
    v41);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1955].fStartTracePosX))(
    &this->m_Pool[1955].fStartTracePosX,
    0);
  fAccelerationTime2 = this->m_Pool[1957].fAccelerationTime2;
  v67[0] = v68 + 145;
  v68 += 241;
  v43 = v68;
  LOBYTE(v43) = g_bDebugMode;
  (*(void ( **)(float *, char *, _DWORD *, CCCTData *, char *, int, int))(LODWORD(fAccelerationTime2) + 28))(
    &this->m_Pool[1957].fAccelerationTime2,
    &byte_A00557,
    v67,
    this,
    "UI\\GameMainUI\\Communal\\SortPrice",
    1,
    v43);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1957].fAccelerationTime2))(
    &this->m_Pool[1957].fAccelerationTime2,
    0);
  x = this->m_Pool[1959].EndPos.x;
  v67[0] = v68 + 6;
  v68 += 102;
  v45 = v68;
  LOBYTE(v45) = g_bDebugMode;
  (*(void ( **)(tagCam *, char *, _DWORD *, CCCTData *, char *, int, int))(LODWORD(x) + 28))(
    &this->m_Pool[1959].EndPos,
    &byte_A00558,
    v67,
    this,
    "UI\\GameMainUI\\Sword\\SortGu",
    1,
    v45);
  (*(void ( **)(tagCam *, _DWORD))LODWORD(this->m_Pool[1959].EndPos.x))(&this->m_Pool[1959].EndPos, 0);
  fStartTracePosY = this->m_Pool[1878].fStartTracePosY;
  v87 = 93;
  v86 = 43;
  v88 = 731;
  v89 = 111;
  (*(void ( **)(float *, __int16 *, int *, char *, _DWORD, CCCTData *))(LODWORD(fStartTracePosY) + 28))(
    &this->m_Pool[1878].fStartTracePosY,
    &word_A00552,
    &v86,
    "UI\\Flex\\SmallBar.tga",
    0,
    this);
  ((CScreenMode *)&this->m_Pool[1878].fStartTracePosY)->SetPosition(40,   18);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1878].fStartTracePosY))(
    &this->m_Pool[1878].fStartTracePosY,
    0);
  v47 = this->m_Pool[1879].EndPos.yaw;
  v87 = 496;
  v86 = 42;
  v88 = 742;
  v89 = 531;
  (*(void ( **)(float *, __int16 *, int *, char *, _DWORD, CCCTData *))(LODWORD(v47) + 28))(
    &this->m_Pool[1879].EndPos.yaw,
    &word_A00552,
    &v86,
    "UI\\Flex\\BigBar.tga",
    0,
    this);
  ((CScreenMode *)&this->m_Pool[1879].EndPos.yaw)->SetPosition(40,   35);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1879].EndPos.yaw))(&this->m_Pool[1879].EndPos.yaw, 0);
  y = this->m_Pool[1888].StartPos.y;
  v90[1] = 76;
  v90[0] = 162;
  v91 = 282;
  v92 = 107;
  (*(void ( **)(float *, __int16 *, _DWORD *, CCCTData *))(LODWORD(y) + 16))(
    &this->m_Pool[1888].StartPos.y,
    &word_A00552,
    v90,
    this);
  ((UIStatic *)&this->m_Pool[1888].StartPos.y)->CreateFromTemplate();
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1888].StartPos.y))(&this->m_Pool[1888].StartPos.y, 0);
  v49 = this->m_Pool[1888].fStartTracePosY;
  v90[0] = v91 + 220;
  v91 += 340;
  (*(void ( **)(float *, __int16 *, _DWORD *, CCCTData *))(LODWORD(v49) + 16))(
    &this->m_Pool[1888].fStartTracePosY,
    &word_A00552,
    v90,
    this);
  ((UIStatic *)&this->m_Pool[1888].fStartTracePosY)->CreateFromTemplate();
  v50 = (*(int ( **)(float *, _DWORD))LODWORD(this->m_Pool[1888].fStartTracePosY))(
          &this->m_Pool[1888].fStartTracePosY,
          0);
  fTimeExpiate = this->m_Pool[1950].fTimeExpiate;
  LODWORD(this->m_Pool[1950].fCircleEndZ) = 502;
  LODWORD(this->m_Pool[1950].fSwingFre) = 322;
  LODWORD(this->m_Pool[1950].fCircleEndY) = 226;
  LODWORD(this->m_Pool[1950].fSwing) = 528;
  LOBYTE(v50) = g_bDebugMode;
  (*(void ( **)(float *, char *, float *, CCCTData *, char *, int, int))(LODWORD(fTimeExpiate) + 28))(
    &this->m_Pool[1950].fTimeExpiate,
    &byte_A00536,
    &this->m_Pool[1950].fCircleEndY,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    1,
    v50);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1950].fTimeExpiate))(
    &this->m_Pool[1950].fTimeExpiate,
    0);
  LODWORD(v52) = LODWORD(this->m_Pool[1950].fSwingFre) + 150;
  this->m_Pool[1950].fCircleEndY = v52;
  LODWORD(this->m_Pool[1950].fSwingFre) = LODWORD(v52) + 96;
  LOBYTE(v53) = g_bDebugMode;
  (*(void ( **)(float *, char *, float *, CCCTData *, char *, int, int))(LODWORD(this->m_Pool[1952].fStartSpeed)
                                                                                 + 28))(
    &this->m_Pool[1952].fStartSpeed,
    &byte_A00537,
    &this->m_Pool[1950].fCircleEndY,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    1,
    v53);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Pool[1952].fStartSpeed))(&this->m_Pool[1952].fStartSpeed, 0);
  fCircleEndZ = this->m_Pool[1948].fCircleEndZ;
  v94[1] = 116;
  v94[0] = 552;
  v94[2] = 680;
  v94[3] = 148;
  (*(void ( **)(float *, char *, _DWORD *, CCCTData *))(LODWORD(fCircleEndZ) + 16))(
    &this->m_Pool[1948].fCircleEndZ,
    &byte_A00527,
    v94,
    this);
  ((UIScene *)&this->m_Pool[1948].fCircleEndZ)->SetShow(0);
  sub_446010(&this->m_Pool[1948].fCircleEndZ);
  sprintf(
    (char *const)&this->m_Pool[0].nTraceRole,
    "%d/%d",
    this->m_Pool[114].fStartTracePosZ,
    this->m_Pool[114].fStartTracePosY);
  ((UICaption *)&this->m_Pool[1948].fCircleEndZ)->SetEnable((int)&this->m_Pool[0].nTraceRole, 0);
  return (*(int ( **)(float *, _DWORD))LODWORD(this->m_Pool[1948].fCircleEndZ))(
           &this->m_Pool[1948].fCircleEndZ,
           0);
}

// 0x004E7D70
LRESULT CCCTData::UpdateDebugDialog()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  HWND v4; // esi
  int v5; // eax
  int v6; // ecx
  LRESULT result; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // esi
  BOOL v11; // edx
  LRESULT Only; // eax
  BOOL v13; // edx
  BOOL v14; // ecx
  BOOL v15; // ecx
  LRESULT v16; // eax
  BOOL v17; // ecx
  LRESULT v18; // eax
  BOOL v19; // edx
  LRESULT v20; // eax
  BOOL v21; // edx
  BOOL v22; // ecx
  BOOL v23; // edx
  BOOL v24; // ecx
  LRESULT v25; // eax
  HWND v26; // [esp+0x10] [ebp-0x8C]
  HWND hWnd; // [esp+0x14] [ebp-0x88]
  HWND v28; // [esp+0x18] [ebp-0x84]
  HWND v29; // [esp+0x1C] [ebp-0x80]
  HWND v30; // [esp+0x20] [ebp-0x7C]
  HWND v31; // [esp+0x24] [ebp-0x78]
  HWND v32; // [esp+0x28] [ebp-0x74]
  HWND v33; // [esp+0x2C] [ebp-0x70]
  HWND v34; // [esp+0x30] [ebp-0x6C]
  HWND v35; // [esp+0x34] [ebp-0x68]
  HWND v36; // [esp+0x38] [ebp-0x64]
  HWND v37; // [esp+0x3C] [ebp-0x60]
  HWND v38; // [esp+0x40] [ebp-0x5C]
  HWND v39; // [esp+0x44] [ebp-0x58]
  HWND v40; // [esp+0x48] [ebp-0x54]
  HWND v41; // [esp+0x4C] [ebp-0x50]
  HWND v42; // [esp+0x50] [ebp-0x4C]
  HWND v43; // [esp+0x54] [ebp-0x48]
  HWND v44; // [esp+0x58] [ebp-0x44]
  HWND v45; // [esp+0x5C] [ebp-0x40]
  HWND v46; // [esp+0x60] [ebp-0x3C]
  HWND v47; // [esp+0x64] [ebp-0x38]
  HWND v48; // [esp+0x68] [ebp-0x34]
  HWND v49; // [esp+0x6C] [ebp-0x30]
  HWND v50; // [esp+0x70] [ebp-0x2C]
  HWND v51; // [esp+0x74] [ebp-0x28]
  HWND v52; // [esp+0x78] [ebp-0x24]
  HWND v53; // [esp+0x7C] [ebp-0x20]
  int p_DWORD; // [esp+0x80] [ebp-0x1C] BYREF
  int v55; // [esp+0x84] [ebp-0x18]
  int v56; // [esp+0x88] [ebp-0x14]
  int p_DWORD2; // [esp+0x8C] [ebp-0x10] BYREF
  int v58; // [esp+0x90] [ebp-0xC]
  int v59; // [esp+0x94] [ebp-0x8]
  HWND v60; // [esp+0x98] [ebp-0x4]

  DlgItem = GetDlgItem(g_hMainWnd, 1185);
  v3 = GetDlgItem(g_hMainWnd, 1187);
  hWnd = GetDlgItem(g_hMainWnd, 1186);
  v49 = GetDlgItem(g_hMainWnd, 1174);
  v29 = GetDlgItem(g_hMainWnd, 1175);
  v43 = GetDlgItem(g_hMainWnd, 1164);
  v31 = GetDlgItem(g_hMainWnd, 1165);
  v53 = GetDlgItem(g_hMainWnd, 1199);
  v33 = GetDlgItem(g_hMainWnd, 1200);
  v45 = GetDlgItem(g_hMainWnd, 1178);
  v35 = GetDlgItem(g_hMainWnd, 1181);
  v51 = GetDlgItem(g_hMainWnd, 1166);
  v37 = GetDlgItem(g_hMainWnd, 1162);
  v47 = GetDlgItem(g_hMainWnd, 1177);
  v39 = GetDlgItem(g_hMainWnd, 1183);
  v52 = GetDlgItem(g_hMainWnd, 1182);
  v41 = GetDlgItem(g_hMainWnd, 1167);
  v26 = GetDlgItem(g_hMainWnd, 1184);
  v28 = GetDlgItem(g_hMainWnd, 1192);
  v30 = GetDlgItem(g_hMainWnd, 1193);
  v32 = GetDlgItem(g_hMainWnd, 1196);
  v34 = GetDlgItem(g_hMainWnd, 1171);
  v36 = GetDlgItem(g_hMainWnd, 1172);
  v38 = GetDlgItem(g_hMainWnd, 1173);
  v40 = GetDlgItem(g_hMainWnd, 1176);
  v42 = GetDlgItem(g_hMainWnd, 1179);
  v44 = GetDlgItem(g_hMainWnd, 1180);
  v46 = GetDlgItem(g_hMainWnd, 1191);
  v48 = GetDlgItem(g_hMainWnd, 1190);
  v50 = GetDlgItem(g_hMainWnd, 1202);
  v4 = GetDlgItem(g_hMainWnd, 1168);
  v60 = v4;
  v5 = *(_DWORD *)&this->m_Pool[39].bAbsoluteTime;
  if ( v5 == -1 || (v6 = *(_DWORD *)&this->m_Pool[39].bRandSwing, v6 == -1) )
  {
    EditBox_SetReadOnly(v3, 0);
    EditBox_SetReadOnly(DlgItem, 0);
    EditBox_SetReadOnly(hWnd, 0);
    EditBox_SetReadOnly(v49, 0);
    EditBox_SetReadOnly(v29, 0);
    EditBox_SetInt(v43, 0);
    EditBox_SetInt(v31, 0);
    EditBox_SetReadOnly(v53, 0);
    EditBox_SetReadOnly(v33, 0);
    EditBox_SetInt(v45, 0);
    EditBox_SetInt(v35, 0);
    EditBox_SetInt(v51, 0);
    EditBox_SetInt(v37, 0);
    EditBox_SetReadOnly(v47, 0);
    EditBox_SetReadOnly(v39, 0);
    EditBox_SetReadOnly(v52, 0);
    EditBox_SetInt(v41, 0);
    EditBox_SetReadOnly(v26, 0);
    EditBox_SetReadOnly(v28, 0);
    EditBox_SetReadOnly(v30, 0);
    EditBox_SetInt(v32, 0);
    EditBox_SetInt(v34, 0);
    EditBox_SetInt(v36, 0);
    EditBox_SetInt(v38, 0);
    EditBox_SetInt(v40, 0);
    EditBox_SetInt(v42, 0);
    EditBox_SetInt(v44, 0);
    EditBox_SetReadOnly(v46, 0);
    EditBox_SetReadOnly(v48, 0);
    EditBox_SetReadOnly(v50, 0);
    return EditBox_SetInt(v4, 0);
  }
  else
  {
    result = 5 * (5 * v5 + 10250);
    v8 = *(_DWORD *)(*((_DWORD *)this->m_Pool[0].fp[0] + 5) + 16);
    v9 = *(_DWORD *)(v8 + 4 * (v6 + 2 * result));
    if ( v9 != -1 )
    {
      result = 51 * v9;
      v10 = v8 + 204 * v9;
      if ( v10 )
      {
        LOBYTE(v9) = *(_BYTE *)(v10 + 93);
        EditBox_SetReadOnly(v3, v9);
        LOBYTE(v11) = *(_BYTE *)(v10 + 92);
        Only = EditBox_SetReadOnly(DlgItem, v11);
        LOBYTE(Only) = *(_BYTE *)(v10 + 94);
        EditBox_SetReadOnly(hWnd, Only);
        LOBYTE(v13) = *(_BYTE *)(v10 + 88) == 0;
        EditBox_SetReadOnly(v49, v13);
        LOBYTE(v14) = *(_BYTE *)(v10 + 89) == 0;
        EditBox_SetReadOnly(v29, v14);
        EditBox_SetInt(v43, *(_DWORD *)(v10 + 80));
        EditBox_SetInt(v31, *(_DWORD *)(v10 + 84));
        LOBYTE(v15) = *(_BYTE *)(v10 + 91);
        v16 = EditBox_SetReadOnly(v53, v15);
        LOBYTE(v16) = *(_BYTE *)(v10 + 90);
        EditBox_SetReadOnly(v33, v16);
        EditBox_SetFloat(v45, *(float *)(v10 + 132));
        EditBox_SetFloat(v35, *(float *)(v10 + 136));
        EditBox_SetFloat(v51, *(float *)(v10 + 108));
        EditBox_SetFloat(v37, *(float *)(v10 + 28));
        LOBYTE(v17) = *(_BYTE *)(v10 + 97);
        v18 = EditBox_SetReadOnly(v47, v17);
        LOBYTE(v18) = *(_BYTE *)(v10 + 98);
        EditBox_SetReadOnly(v39, v18);
        LOBYTE(v19) = *(_BYTE *)(v10 + 99);
        EditBox_SetReadOnly(v52, v19);
        v20 = EditBox_SetFloat(v41, *(float *)(v10 + 112));
        LOBYTE(v20) = *(_BYTE *)(v10 + 23);
        EditBox_SetReadOnly(v26, v20);
        LOBYTE(v21) = *(_BYTE *)(v10 + 101);
        EditBox_SetReadOnly(v28, v21);
        LOBYTE(v22) = *(_BYTE *)(v10 + 102);
        EditBox_SetReadOnly(v30, v22);
        EditBox_SetInt(v32, *(_DWORD *)(v10 + 104));
        EditBox_SetFloat(v34, *(float *)(v10 + 116));
        EditBox_SetFloat(v36, *(float *)(v10 + 120));
        EditBox_SetFloat(v38, *(float *)(v10 + 124));
        EditBox_SetFloat(v40, *(float *)(v10 + 128));
        EditBox_SetFloat(v42, *(float *)(v10 + 164));
        EditBox_SetFloat(v44, *(float *)(v10 + 168));
        LOBYTE(v23) = *(_BYTE *)(v10 + 100);
        EditBox_SetReadOnly(v46, v23);
        LOBYTE(v24) = *(_BYTE *)(v10 + 96);
        v25 = EditBox_SetReadOnly(v48, v24);
        LOBYTE(v25) = *(_BYTE *)(v10 + 95);
        EditBox_SetReadOnly(v50, v25);
        EditBox_SetFloat(v60, *(float *)(v10 + 172));
        p_DWORD = 0;
        v55 = 0;
        v56 = 0;
        p_DWORD2 = 0;
        v58 = 0;
        v59 = 0;
        p_DWORD = *(_DWORD *)(v10 + 140);
        v55 = *(_DWORD *)(v10 + 144);
        v56 = *(_DWORD *)(v10 + 148);
        p_DWORD2 = *(_DWORD *)(v10 + 152);
        v58 = *(_DWORD *)(v10 + 156);
        v59 = *(_DWORD *)(v10 + 160);
      }
    }
  }
  return result;
}

// 0x005044C0
int CCCTData::CCCTData::UpdateCamera(int nVal)
{
  return ((j_InputSystem *)*(_DWORD *)(nVal + 12))->InputSystem::ProcessKeyboard(*(_DWORD *)(nVal + 16), *(_DWORD *)(nVal + 20), *(_DWORD *)nVal, *(_DWORD *)(nVal + 4), *(_DWORD *)(nVal + 8));
}

// 0x005058F0
CCCTData::CCCTData(int *p_DWORD, int *p_DWORD2)
{
  *((_DWORD *)this + 107557) = *p_DWORD;
  *((_DWORD *)this + 107558) = p_DWORD[1];
  *((_DWORD *)this + 107559) = p_DWORD[2];
  *((_DWORD *)this + 107560) = *p_DWORD2;
  *((_DWORD *)this + 107561) = p_DWORD2[1];
  *((_DWORD *)this + 107562) = p_DWORD2[2];
}

// 0x00505930
void CCCTData::_CCCTData()
{
  char *v2; // ebp
  gbRenderEffect *v3; // ebx
  float *v4; // esi
  char *v5; // esi
  float *v6; // esi
  double v7; // st7
  gbDynVertBuf *v8; // edx
  int v9; // eax
  unsigned int v10; // ecx
  double v11; // st7
  gbDynVertBuf *v12; // edx
  int v13; // eax
  unsigned int v14; // ecx
  float v15; // edx
  float v16; // eax
  gbDynVertBuf *v17; // ecx
  int v18; // edx
  float *v19; // edi
  double v20; // st7
  double v21; // st6
  gbDynVertBuf *v22; // edx
  double v23; // st6
  gbColorQuad v24; // [esp+0x40] [ebp-A8h] BYREF
  float *v25; // [esp+0x44] [ebp-A4h]
  int v26; // [esp+0x48] [ebp-A0h]
  int v27; // [esp+0x4C] [ebp-0x9C]
  struct gbColorQuad v28; // [esp+0x50] [ebp-0x98]
  gbVec3D *v29; // [esp+0x54] [ebp-0x94]
  int v30; // [esp+0x58] [ebp-0x90]
  gbRenderEffect *v31; // [esp+0x5C] [ebp-0x8C]
  int v32; // [esp+0x64] [ebp-0x84]
  int v33; // [esp+0x68] [ebp-0x80]
  int v34; // [esp+0x6C] [ebp-0x7C]
  int v35; // [esp+0x70] [ebp-0x78]
  int v36; // [esp+0x74] [ebp-0x74]
  int v37; // [esp+0x78] [ebp-0x70]
  struct gbColorQuad v38[2]; // [esp+0x7C] [ebp-0x6C] BYREF
  float v39; // [esp+0x84] [ebp-0x64] BYREF
  float v40; // [esp+0x88] [ebp-0x60]
  float v41; // [esp+0x8C] [ebp-0x5C]
  gbDynVertBuf *v42; // [esp+0x90] [ebp-0x58]
  int v43; // [esp+0x94] [ebp-0x54]
  unsigned int Color; // [esp+0x98] [ebp-0x50]
  struct gbOBBox v45; // [esp+0x9C] [ebp-0x4C] BYREF

  if ( *((_BYTE *)this + 430252) )
  {
    ((gbGeomNode *)*((gbGeomNode **)this + 107556))->GetTotalOBBox(&v45);
    v2 = (char *)this + 430228;
    ((gbMatrix4 *)&v45)->RightTranslate((gbVec3D *)((char *)this + 430228));
    v3 = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewTrivalEffect(3);
    v38[1].Color = (unsigned int)((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
    if ( (byte_17AAEE0 & 1) == 0 )
    {
      v4 = &g_fCBAnimTime;
      byte_17AAEE0 |= 1u;
      v34 = 6;
      do
      {
        v4 += 17;
        --v34;
      }
      while ( *(float *)&v34 != 0.0 );
      atexit(nullsub_31);
    }
    v45.xlen = v45.xlen + 2.0;
    v45.ylen = v45.ylen + 2.0;
    v45.zlen = v45.zlen + 2.0;
    *(float *)&v37 = v45.ylen * 0.5;
    dword_17AAD4C = v37;
    *(float *)&v34 = v45.zlen * 0.5;
    g_fCBAnimTime = v45.xlen * -0.5;
    dword_17AAD50 = v34;
    dword_17AAD58 = v37;
    g_fCombatHalfParam = v45.xlen * 0.5;
    dword_17AAD5C = v34;
    dword_17AAD68 = v34;
    *(float *)&v35 = v45.ylen * -0.5;
    flt_17AAD60 = g_fCombatHalfParam;
    dword_17AAD64 = v35;
    flt_17AAD6C = g_fCBAnimTime;
    dword_17AAD70 = v35;
    *(float *)&v36 = v45.zlen * -0.5;
    dword_17AAD74 = v34;
    flt_17AAD8C = g_fCBAnimTime;
    dword_17AAD90 = v37;
    dword_17AAD94 = v36;
    flt_17AAD98 = g_fCombatHalfParam;
    dword_17AAD9C = v37;
    dword_17AADA0 = v36;
    flt_17AADA4 = g_fCombatHalfParam;
    flt_17AADB0 = g_fCBAnimTime;
    flt_17AADD0 = g_fCBAnimTime;
    dword_17AADA8 = v35;
    dword_17AADAC = v36;
    dword_17AADB4 = v35;
    dword_17AADB8 = v36;
    flt_17AADDC = g_fCBAnimTime;
    dword_17AADD4 = v37;
    dword_17AADD8 = v34;
    flt_17AADE8 = g_fCBAnimTime;
    dword_17AADE0 = v37;
    dword_17AADE4 = v36;
    flt_17AADF4 = g_fCBAnimTime;
    dword_17AADEC = v35;
    dword_17AADF0 = v36;
    dword_17AADF8 = v35;
    flt_17AAE14 = g_fCombatHalfParam;
    dword_17AADFC = v34;
    dword_17AAE18 = v37;
    dword_17AAE1C = v34;
    flt_17AAE20 = g_fCombatHalfParam;
    dword_17AAE24 = v37;
    dword_17AAE28 = v36;
    flt_17AAE2C = g_fCombatHalfParam;
    dword_17AAE30 = v35;
    flt_17AAE38 = g_fCombatHalfParam;
    flt_17AAE58 = g_fCBAnimTime;
    dword_17AAE34 = v36;
    dword_17AAE3C = v35;
    flt_17AAE64 = g_fCombatHalfParam;
    dword_17AAE40 = v34;
    dword_17AAE5C = v37;
    dword_17AAE60 = v36;
    flt_17AAE70 = g_fCombatHalfParam;
    dword_17AAE68 = v37;
    dword_17AAE6C = v36;
    dword_17AAE74 = v37;
    flt_17AAE7C = g_fCBAnimTime;
    dword_17AAE78 = v34;
    dword_17AAE80 = v37;
    flt_17AAE9C = g_fCBAnimTime;
    dword_17AAE84 = v34;
    dword_17AAEA0 = v35;
    dword_17AAEA4 = v36;
    flt_17AAEA8 = g_fCombatHalfParam;
    flt_17AAEB4 = g_fCombatHalfParam;
    dword_17AAEAC = v35;
    dword_17AAEB0 = v36;
    flt_17AAEC0 = g_fCBAnimTime;
    dword_17AAEB8 = v35;
    dword_17AAEBC = v34;
    v32 = v35;
    v33 = v34;
    dword_17AAEC4 = v35;
    dword_17AAEC8 = v34;
    v5 = byte_17AAD89;
    do
    {
      v5[1] = -1;
      *v5 = -1;
      v27 = 4;
      *(v5 - 1) = 10;
      v26 = (int)(v5 - 65);
      v5[2] = -101;
      ((gbMatrix4 *)&v45)->Transform((gbVec3D *)v26, v27);
      v5 += 68;
    }
    while ( (int)v5 < (int)byte_17AAF21 );
    ((gbDynVertBuf *)&g_fCBAnimTime)->RenderGeomQuad(6, v3, 0);
    v6 = &v39;
    v34 = 2;
    do
    {
      v6 += 3;
      --v34;
    }
    while ( *(float *)&v34 != 0.0 );
    v7 = *(float *)v2;
    v8 = *(gbDynVertBuf **)v2;
    v9 = *((_DWORD *)this + 107558);
    v33 = *((int *)this + 107559);
    v42 = v8;
    v39 = v7;
    v41 = *(float *)&v33;
    v10 = *((_DWORD *)this + 107559);
    v27 = (int)v3;
    v26 = 2;
    v25 = &v39;
    v43 = v9;
    v24.Color = v10;
    Color = v10;
    v38[0].Color = 1358954495;
    v40 = 0.0;
    ((gbDynVertBuf *)v42)->RenderLineStrip(v28, v29, v30, v31);
    v11 = *((float *)this + 107560);
    v12 = (gbDynVertBuf *)*((_DWORD *)this + 107560);
    v13 = *((_DWORD *)this + 107561);
    v33 = *((int *)this + 107562);
    v42 = v12;
    v39 = v11;
    v41 = *(float *)&v33;
    v14 = *((_DWORD *)this + 107562);
    v27 = (int)v3;
    v26 = 2;
    v25 = &v39;
    v43 = v13;
    v24.Color = v14;
    Color = v14;
    v40 = 0.0;
    ((gbDynVertBuf *)v42)->RenderLineStrip(v28, v29, v30, v31);
    v15 = *((float *)this + 107558);
    v16 = *((float *)this + 107559);
    v39 = *(float *)v2;
    v17 = (gbDynVertBuf *)*((_DWORD *)this + 107560);
    v40 = v15;
    v18 = *((_DWORD *)this + 107561);
    v42 = v17;
    v27 = (int)v3;
    v26 = 2;
    v25 = &v39;
    v43 = v18;
    v24.Color = (unsigned int)&v39;
    v41 = v16;
    Color = *((_DWORD *)this + 107562);
    ((gbDynVertBuf *)v42)->RenderLineStrip(v28, v29, v30, v31);
    v19 = (float *)*((_DWORD *)this + 107501);
    v20 = v19[123] + 1.0;
    v21 = v19[124] + 1.0;
    v22 = *(gbDynVertBuf **)v2;
    v27 = (int)v3;
    v26 = 2;
    *(float *)&v32 = v21;
    v23 = v19[125];
    v42 = v22;
    v40 = *(float *)&v32;
    v43 = *((_DWORD *)v2 + 1);
    *(float *)&v33 = v23 + 1.0;
    v25 = &v39;
    v39 = v20;
    v41 = *(float *)&v33;
    v24.Color = *((_DWORD *)v2 + 2);
    Color = v24.Color;
    ((gbDynVertBuf *)v42)->RenderLineStrip(v28, v29, v30, v31);
// [VFTABLE] ((gbRefObject *)&v3->__vftable)->Release();
  }
}

// 0x00506020
bool CCCTData::Create(float *pfVal)
{
  int v3; // eax
  CameraCtrl *v4; // ecx
  float pPos[2]; // [esp+0x8] [ebp-0x90] BYREF
  struct gbVec3D v7; // [esp+0x10] [ebp-0x88] BYREF
  gbRay v8; // [esp+0x1C] [ebp-0x7C] BYREF
  struct gbOBBox v9; // [esp+0x34] [ebp-0x64] BYREF
  _BYTE pTarget[24]; // [esp+0x80] [ebp-0x18] BYREF

  ((gbGeomNode *)*((gbGeomNode **)this + 107556))->GetTotalOBBox(&v9);
  v7.x = *pfVal;
  v7.y = pfVal[1];
  v7.z = pfVal[2];
  ((gbMatrix4 *)&v9)->RightTranslate(v7);
  v3 = *((_DWORD *)this + 107500);
  pPos[0] = *(float *)(v3 + 80);
  v4 = (CameraCtrl *)*((_DWORD *)this + 107501);
  pPos[1] = *(float *)(v3 + 84);
  qmemcpy(&v8, ((CameraCtrl *)v4)->GetViewTarget(pTarget, pPos), sizeof(v8));
  return ((gbRay *)&v8)->IsColOBB(v9) == 1;
}

// 0x005060D0
bool CCCTData::Destroy()
{
  gbGeomNode *v2; // eax
  gbGeomNode *v3; // esi
  gbGeomNode *v4; // ecx
  char pExceptionObject[1024]; // [esp+0xC] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x40C] [ebp-0x40C] BYREF
  int v8; // [esp+0x814] [ebp-0x4]

  v2 = (gbGeomNode *)operator new(0x118u);
  v3 = v2;
  v8 = 0;
  if ( v2 )
  {
    v4 = v3;
  }
  else
  {
    v4 = 0;
  }
  v8 = -1;
  *((_DWORD *)this + 107556) = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], aDProjectPal3Co_3, 1425),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((gbGeomNode *)v4)->LoadFromFile("ui\\combat\\pointer\\pointer.cvd", 0, 0);
  return 1;
}

// 0x005061A0
void CCCTData::Init()
{
  int v2; // edx
  int v3; // ebp
  CEffectSystem *v4; // ecx
  tagCCT *v5; // edi
  int v6; // eax

  v2 = *((_DWORD *)this + 107508);
  v3 = *((_DWORD *)this + 107509);
  v4 = (CEffectSystem *)this->m_nCCTIndex[0][50 * v2 + v3];
  if ( v4 == (CEffectSystem *)-1 )
    v5 = 0;
  else
    v5 = &this->m_Pool[(_DWORD)v4];
  if ( v5->bFinished )
  {
    *((_DWORD *)this + 107509) = v3 + 1;
    LOBYTE(v6) = ((CCBStageCam *)this)->IsEditorCamValid(v2);
    if ( *((_DWORD *)this + 107509) >= v6 )
    {
      *((_BYTE *)this + 430012) = 0;
      *((_DWORD *)this + 107509) = -1;
      *((_DWORD *)this + 107508) = -1;
    }
  }
  else
  {
    if ( v5->bRandSwing )
      *((_BYTE *)((CEffectSystem *)v4)->DestroyAllEffect() + 5) = 1;
    else
      *((_BYTE *)((CEffectSystem *)v4)->DestroyAllEffect() + 5) = 0;
    if ( v5->bLineMove )
      sub_506340(this);
    if ( v5->bCircleMove )

    if ( v5->bMechanicsMove )

  }
}

// 0x00506260
char * CCCTData::Save(int nVal)
{
  char *result; // eax
  char *v4; // esi
  int *v5; // edx
  tagCCT *v6; // eax

  LOBYTE(result) = ((CCBStageCam *)this)->IsEditorCamValid(nVal);
  if ( (int)result > 0 )
  {
    v4 = result;
    v5 = &this->m_nCCTIndex[0][50 * nVal];
    do
    {
      if ( *v5 == -1 )
        v6 = 0;
      else
        v6 = &this->m_Pool[*v5];
      v6->bExecuted = 0;
      if ( *v5 == -1 )
        result = 0;
      else
        result = (char *)&this->m_Pool[*v5];
      ++v5;
      --v4;
      result[22] = 0;
    }
    while ( v4 );
  }
  return result;
}

// 0x005062D0
bool CCCTData::Load(float *pfVal)
{
  int v2; // eax
  double v3; // st7
  double v4; // st6
  int v5; // ecx
  int v6; // edx
  int v8; // [esp+0x0] [ebp-0x10]
  int v9; // [esp+0x4] [ebp-0xC]

  v2 = *((_DWORD *)this + 107501);
  v3 = *(float *)(v2 + 496);
  v4 = *(float *)(v2 + 492);
  v8 = *(_DWORD *)(v2 + 500);
  v5 = *(_DWORD *)(v2 + 452);
  v9 = *(_DWORD *)(v2 + 456);
  v6 = *(_DWORD *)(v2 + 464);
  *((_DWORD *)pfVal + 2) = v8;
  *((_DWORD *)pfVal + 3) = v9;
  *((_DWORD *)pfVal + 4) = v5;
  *pfVal = v4;
  *((_DWORD *)pfVal + 5) = v6;
  pfVal[1] = v3;
  return (char)pfVal;
}

// 0x005075E0
void CCCTData::InsertTaskToList()
{
  int v1; // edx
  tagCCT *v2; // eax
  int v4; // ecx
  tagCCT *v5; // ebx
  double v6; // st7
  double v7; // st7
  char v9; // c0
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  unsigned __int8 v15; // c0
  unsigned __int8 v16; // c3
  double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st6
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  char bPosTrace; // cl
  unsigned int nTraceRole; // eax
  float *v27; // eax
  float v28; // edx
  float *v29; // eax
  float v30; // edx
  float *v31; // esi
  unsigned __int8 v33; // c0
  unsigned __int8 v34; // c3
  float v35; // [esp+0x1C] [ebp-0x80]
  float v36; // [esp+0x20] [ebp-0x7C]
  float v37; // [esp+0x24] [ebp-0x78]
  float v38; // [esp+0x28] [ebp-0x74]
  float v39; // [esp+0x2C] [ebp-0x70]
  float v40; // [esp+0x2C] [ebp-0x70]
  float v41; // [esp+0x30] [ebp-0x6C]
  float v42; // [esp+0x30] [ebp-0x6C]
  float fCircleCentreX; // [esp+0x34] [ebp-0x68]
  float v44; // [esp+0x34] [ebp-0x68]
  float fCircleCentreY; // [esp+0x38] [ebp-0x64]
  float v46; // [esp+0x38] [ebp-0x64]
  float fCircleCentreZ; // [esp+0x3C] [ebp-0x60]
  float v48; // [esp+0x3C] [ebp-0x60]
  float v49; // [esp+0x44] [ebp-0x58]
  float v50; // [esp+0x48] [ebp-0x54]
  gbQuaternion v51; // [esp+0x4C] [ebp-0x50] BYREF
  gbMatrix4 v52; // [esp+0x5C] [ebp-0x40] BYREF
  void *v53; // [esp+A0h] [ebp+0x4]

  v1 = this->m_nCCTIndex[0][50 * *((_DWORD *)this + 107508) + *((_DWORD *)this + 107509)];
  if ( v1 == -1 )
    v2 = 0;
  else
    v2 = &this->m_Pool[v1];
  if ( v2->bEndCamValid && v2->bSpeedValid )
  {
    if ( !v2->bTimeValid )
    {
      v4 = this->m_nCCTIndex[0][50 * *((_DWORD *)this + 107508) + *((_DWORD *)this + 107509)];
      if ( v4 == -1 )
        v5 = 0;
      else
        v5 = &this->m_Pool[v4];
      if ( !v5->bExecuted )
      {
        if ( !v5->bStartCamValid )
          this->Load(&v5->StartPos.x);
        if ( v5->bAbsoluteTime )
          v6 = *(float *)(**((_DWORD **)this + 107500) + 104);
        else
          v6 = *(float *)(**((_DWORD **)this + 107500) + 80);
        v5->fStartTime = v6;
        qmemcpy((char *)this + 430088, &v5->StartPos, 0x18u);
        if ( v5->bCounterYaw )
        {
          if ( v5->EndPos.yaw - *((float *)this + 107525) <= 0.0 )
          {
            v7 = *((float *)this + 107525);
            if ( v9 )
              v7 = v7 - 6.2831855;
          }
          else
          {
            v7 = *((float *)this + 107525) + 6.2831855;
          }
          *((float *)this + 107525) = v7;
        }
        *((_DWORD *)this + 107518) = LODWORD(v5->fCircleAngle);
        *((_DWORD *)this + 107510) = LODWORD(v5->fAngleSpeed);
        v5->bExecuted = 1;
      }
      if ( v5->bAbsoluteTime )
        v10 = *(float *)(**((_DWORD **)this + 107500) + 104);
      else
        v10 = *(float *)(**((_DWORD **)this + 107500) + 80);
      v11 = v10 - v5->fStartTime;
      v36 = v11;
      v35 = v11 * *((float *)this + 107510);
      if ( v36 >= (double)v5->fAccelerationTime1 )
      {
        v12 = v36 - v5->fAccelerationTime1;
        v35 = v12 * v5->fAcceleration1 * v12 * 0.5 + v35;
      }
      if ( v36 >= (double)v5->fAccelerationTime2 )
      {
        v13 = v36 - v5->fAccelerationTime2;
        v35 = (v5->fAcceleration2 + v5->fAcceleration1) * v13 * v13 * 0.5 + v35;
      }
      if ( v15 | v16 )
      {
        if ( v35 < (double)*((float *)this + 107518) )
          v35 = *((float *)this + 107518);
      }
      else if ( v35 > (double)*((float *)this + 107518) )
      {
        v35 = *((float *)this + 107518);
      }
      v17 = v5->fCircleEndY - v5->fCircleCentreY;
      v18 = v35 / *((float *)this + 107518);
      memset(&v51, 0, 12);
      v51.w = 1.0;
      v37 = v17 * v18;
      fCircleCentreX = v5->fCircleCentreX;
      fCircleCentreY = v5->fCircleCentreY;
      fCircleCentreZ = v5->fCircleCentreZ;
      v19 = v5->StartPos.x - fCircleCentreX;
      v49 = v5->StartPos.y - fCircleCentreY;
      v20 = v5->StartPos.z - fCircleCentreZ;
      *((float *)this + 107535) = v49;
      v50 = v20;
      *((float *)this + 107534) = v19;
      *((float *)this + 107536) = v50;
      ((gbQuaternion *)&v51)->SetYawPitchRoll(v35, 0.0, 0.0);
      ((gbQuaternion *)&v51)->GetMatrix(&v52);
      ((gbMatrix4 *)&v52)->RotateIn((gbVec3D *)((char *)this + 430136));
      v21 = fCircleCentreX + *((float *)this + 107534);
      v44 = 0.0;
      *((float *)this + 107534) = v21;
      v22 = fCircleCentreY + *((float *)this + 107535);
      v46 = 0.0;
      *((float *)this + 107535) = v22;
      v23 = fCircleCentreZ + *((float *)this + 107536);
      v48 = 0.0;
      *((float *)this + 107536) = v23;
      *((float *)this + 107535) = v37 + *((float *)this + 107535);
      v24 = *((float *)this + 107534);
      v38 = *((float *)this + 107534);
      v39 = *((float *)this + 107535);
      bPosTrace = v5->bPosTrace;
      v41 = *((float *)this + 107536);
      if ( bPosTrace || v5->bSightTrace )
      {
        nTraceRole = v5->nTraceRole;
        if ( nTraceRole > 0xA )
        {
          if ( nTraceRole == -1 )
          {
            v29 = *(float **)(*((_DWORD *)this + 107500) + 20);
            v30 = v29[225];
            v29 += 225;
            v44 = v30;
            v46 = v29[1];
            v48 = v29[2];
          }
          else
          {
            v48 = 0.0;
            v46 = 0.0;
            v44 = 0.0;
          }
        }
        else
        {
          v27 = *(float **)(*((_DWORD *)this + 107500) + 4 * nTraceRole + 24);
          v28 = v27[1646];
          v27 += 1646;
          v44 = v28;
          v46 = v27[1];
          v48 = v27[2];
        }
      }
      if ( bPosTrace )
      {
        v40 = v39 + v46;
        v42 = v41 + v48;
        v24 = v24 + v44 - v5->fStartTracePosX;
        v38 = v24;
        v39 = v40 - v5->fStartTracePosY;
        v41 = v42 - v5->fStartTracePosZ;
      }
      v31 = (float *)((char *)this + 430112);
      if ( v5->bSightTrace )
      {
        *((float *)this + 107529) = v39;
        *((float *)this + 107530) = v41;
        *v31 = v24;
        ((CCCTData *)*((CCCTData **)this + 107501))->CalcDist(v38, v39);
      }
      else
      {
        *v31 = *((float *)this + 107522);
        *((_DWORD *)this + 107529) = *((_DWORD *)this + 107523);
        *((_DWORD *)this + 107530) = *((_DWORD *)this + 107524);
        *((_DWORD *)this + 107531) = *((_DWORD *)this + 107525);
        *((_DWORD *)this + 107532) = *((_DWORD *)this + 107526);
        *((_DWORD *)this + 107533) = *((_DWORD *)this + 107527);
        *((float *)this + 107529) = v39;
        *v31 = v24;
        *((float *)this + 107530) = v41;
      }
      ((CCCTData *)*((CCCTData **)this + 107501))->CCCTData::UpdateCamera((int)this + 430112);
      ((CameraCtrl *)*((CameraCtrl **)this + 107501))->SetAsCurrent(3);
      if ( v33 | v34 )
      {
        if ( v35 <= (double)*((float *)this + 107518) )
        {
          v5->fExpectTime = v36;
          v5->bFinished = 1;
        }
      }
      else if ( v35 >= (double)*((float *)this + 107518) )
      {
        v5->fExpectTime = v36;
        v5->bFinished = 1;
      }
    }
  }
  else
  {
    todo_408BD0(v53);
  }
}

// 0x00507B20
void CCCTData::SwapTask()
{
  int v2; // ecx
  tagCCT *v3; // ebx
  float *p_x; // edx
  int v5; // eax
  int v6; // ecx
  tagCCT *v7; // eax
  double v8; // st7
  float v9; // ecx
  double v10; // st7
  float v11; // ecx
  int v12; // ecx
  double v13; // st7
  double v14; // st7
  char v16; // c0
  int v17; // edx
  double v18; // st7
  int v19; // eax
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st6
  double v24; // st6
  double v25; // st7
  char bPosTrace; // cl
  unsigned int nTraceRole; // eax
  float *v28; // eax
  float v29; // edx
  float *v30; // eax
  float v31; // edx
  double v32; // st6
  double v33; // st5
  float v34; // [esp+0x10] [ebp-0x48]
  float v35; // [esp+0x14] [ebp-0x44]
  float v36; // [esp+0x14] [ebp-0x44]
  float v37; // [esp+0x14] [ebp-0x44]
  float v38; // [esp+0x18] [ebp-0x40]
  float v39; // [esp+0x1C] [ebp-0x3C]
  float v40; // [esp+0x20] [ebp-0x38]
  float v41; // [esp+0x20] [ebp-0x38]
  float v42; // [esp+0x20] [ebp-0x38]
  float v43; // [esp+0x20] [ebp-0x38]
  float v44; // [esp+0x20] [ebp-0x38]
  float v45; // [esp+0x24] [ebp-0x34]
  float v46; // [esp+0x24] [ebp-0x34]
  float v47; // [esp+0x24] [ebp-0x34]
  float v48; // [esp+0x24] [ebp-0x34]
  float v49; // [esp+0x24] [ebp-0x34]
  float v50; // [esp+0x28] [ebp-0x30]
  float v51; // [esp+0x2C] [ebp-0x2C]
  float v52; // [esp+0x2C] [ebp-0x2C]
  float v53; // [esp+0x2C] [ebp-0x2C]
  float v54; // [esp+0x2C] [ebp-0x2C]
  float v55; // [esp+0x2C] [ebp-0x2C]
  float v56; // [esp+0x2C] [ebp-0x2C]
  float v57; // [esp+0x2C] [ebp-0x2C]
  float v58; // [esp+0x30] [ebp-0x28]
  float v59; // [esp+0x30] [ebp-0x28]
  float v60; // [esp+0x30] [ebp-0x28]
  float v61; // [esp+0x30] [ebp-0x28]
  float v62; // [esp+0x30] [ebp-0x28]
  float v63; // [esp+0x30] [ebp-0x28]
  float v64; // [esp+0x30] [ebp-0x28]
  float v65; // [esp+0x34] [ebp-0x24]
  float v66; // [esp+0x34] [ebp-0x24]
  float v67; // [esp+0x38] [ebp-0x20]
  float v68; // [esp+0x38] [ebp-0x20]
  float v69; // [esp+0x3C] [ebp-0x1C]
  float v70; // [esp+0x3C] [ebp-0x1C]
  float v71; // [esp+0x44] [ebp-0x14]
  float v72; // [esp+0x48] [ebp-0x10]
  float v73; // [esp+0x4C] [ebp-0xC]
  float v74; // [esp+0x50] [ebp-0x8]
  float v75; // [esp+0x54] [ebp-0x4]

  v2 = this->m_nCCTIndex[0][50 * *((_DWORD *)this + 107508) + *((_DWORD *)this + 107509)];
  if ( v2 == -1 )
    v3 = 0;
  else
    v3 = &this->m_Pool[v2];
  if ( !v3->bExecuted )
  {
    if ( !v3->bStartCamValid )
      this->Load(&v3->StartPos.x);
    p_x = &v3->StartPos.x;
    qmemcpy((char *)this + 430088, &v3->StartPos, 0x18u);
    *((_DWORD *)this + 107534) = LODWORD(v3->StartPos.x);
    *((_DWORD *)this + 107535) = LODWORD(v3->StartPos.y);
    v5 = *((_DWORD *)this + 107509);
    *((_DWORD *)this + 107536) = LODWORD(v3->StartPos.z);
    if ( !v5
      || v5 > 0
      && ((v6 = *(_DWORD *)&this->m_bPoolInUse[200 * *((_DWORD *)this + 107508) + 1996 + 4 * v5], v6 == -1)
        ? (v7 = 0)
        : (v7 = &this->m_Pool[v6]),
          !v7->bMechanicsMove) )
    {
      v8 = v3->EndPos.x - *p_x;
      v51 = v3->EndPos.y - v3->StartPos.y;
      v58 = v3->EndPos.z - v3->StartPos.z;
      if ( v3->fExpectTime <= 0.0 )
      {
        v9 = v3->EndPos.z - v3->StartPos.z;
        *((float *)this + 107512) = v8;
        *((float *)this + 107513) = v51;
      }
      else
      {
        v35 = 1.0 / v3->fExpectTime;
        v40 = v51 * v35;
        *((float *)this + 107513) = v40;
        v45 = v58 * v35;
        v9 = v45;
        *((float *)this + 107512) = v8 * v35;
      }
      *((float *)this + 107514) = v9;
    }
    v10 = v3->EndPos.x - *p_x;
    v52 = v3->EndPos.y - v3->StartPos.y;
    v59 = v3->EndPos.z - v3->StartPos.z;
    if ( v3->fExpectTime <= 0.0 )
    {
      v11 = v3->EndPos.z - v3->StartPos.z;
      *((float *)this + 107515) = v10;
      *((float *)this + 107516) = v52;
    }
    else
    {
      v36 = 1.0 / v3->fExpectTime;
      v41 = v52 * v36;
      *((float *)this + 107516) = v41;
      v46 = v59 * v36;
      v11 = v46;
      *((float *)this + 107515) = v10 * v36;
    }
    *((float *)this + 107517) = v11;
    v12 = **((_DWORD **)this + 107500);
    if ( v3->bAbsoluteTime )
      v13 = *(float *)(v12 + 104);
    else
      v13 = *(float *)(v12 + 80);
    v3->fStartTime = v13;
    qmemcpy((char *)this + 430112, p_x, 0x18u);
    if ( v3->bCounterYaw )
    {
      if ( v3->EndPos.yaw - *((float *)this + 107525) <= 0.0 )
      {
        v14 = *((float *)this + 107525);
        if ( v16 )
          v14 = v14 - 6.2831855;
      }
      else
      {
        v14 = *((float *)this + 107525) + 6.2831855;
      }
      *((float *)this + 107525) = v14;
    }
    v3->bExecuted = 1;
  }
  if ( v3->bAbsoluteTime )
  {
    v17 = *((_DWORD *)this + 107500);
    v37 = *(double *)(*(_DWORD *)v17 + 88);
    v18 = *(float *)(*(_DWORD *)v17 + 104);
  }
  else
  {
    v19 = **((_DWORD **)this + 107500);
    v37 = *(double *)(v19 + 64);
    v18 = *(float *)(v19 + 80);
  }
  if ( v3->fExpectTime > 0.0 )
    v34 = (v18 - v3->fStartTime) / (v3->fTimeExpiate + v3->fExpectTime);
  else
    v34 = 1.0;
  v38 = ((gbVec3D *)((char *)this + 430048))->Length();
  v53 = v37 * *((float *)this + 107516);
  v60 = v37 * *((float *)this + 107517);
  v20 = v37 * *((float *)this + 107515) + *((float *)this + 107512);
  v42 = v53 + *((float *)this + 107513);
  v21 = v60 + *((float *)this + 107514);
  *((float *)this + 107513) = v42;
  v47 = v21;
  *((float *)this + 107512) = v20;
  *((float *)this + 107514) = v47;
  ((gbVec3D *)((char *)this + 430048))->Normalize();
  v50 = 0.0;
  *((float *)this + 107512) = v38 * *((float *)this + 107512);
  *((float *)this + 107513) = v38 * *((float *)this + 107513);
  *((float *)this + 107514) = v38 * *((float *)this + 107514);
  v54 = v37 * *((float *)this + 107513);
  v61 = v37 * *((float *)this + 107514);
  v22 = v37 * *((float *)this + 107512) + *((float *)this + 107534);
  v23 = v54 + *((float *)this + 107535);
  v55 = 0.0;
  v43 = v23;
  v24 = v61 + *((float *)this + 107536);
  v62 = 0.0;
  *((float *)this + 107535) = v43;
  v48 = v24;
  *((float *)this + 107534) = v22;
  *((float *)this + 107536) = v48;
  v25 = *((float *)this + 107534);
  bPosTrace = v3->bPosTrace;
  v39 = *((float *)this + 107534);
  if ( bPosTrace || v3->bSightTrace )
  {
    nTraceRole = v3->nTraceRole;
    if ( nTraceRole > 0xA )
    {
      if ( nTraceRole == -1 )
      {
        v30 = *(float **)(*((_DWORD *)this + 107500) + 20);
        v31 = v30[225];
        v30 += 225;
        v50 = v31;
        v55 = v30[1];
        v62 = v30[2];
      }
      else
      {
        v62 = 0.0;
        v55 = 0.0;
        v50 = 0.0;
      }
    }
    else
    {
      v28 = *(float **)(*((_DWORD *)this + 107500) + 4 * nTraceRole + 24);
      v29 = v28[1646];
      v28 += 1646;
      v50 = v29;
      v55 = v28[1];
      v62 = v28[2];
    }
  }
  if ( bPosTrace )
  {
    v44 = v55 + v43;
    v49 = v62 + v48;
    v25 = v25 + v50 - v3->fStartTracePosX;
    v39 = v25;
    v43 = v44 - v3->fStartTracePosY;
    v48 = v49 - v3->fStartTracePosZ;
  }
  if ( v3->bSightTrace )
  {
    *((float *)this + 107529) = v43;
    *((float *)this + 107530) = v48;
    *((float *)this + 107528) = v25;
    ((CCCTData *)*((CCCTData **)this + 107501))->CalcDist(v39, v43);
  }
  else
  {
    v56 = v3->EndPos.y - *((float *)this + 107523);
    v63 = v3->EndPos.z - *((float *)this + 107524);
    v65 = v3->EndPos.yaw - *((float *)this + 107525);
    v67 = v3->EndPos.pit - *((float *)this + 107526);
    v69 = v3->EndPos.rol - *((float *)this + 107527);
    v71 = v56 * v34;
    v72 = v63 * v34;
    v73 = v65 * v34;
    v74 = v67 * v34;
    v75 = v69 * v34;
    v32 = (v3->EndPos.x - *((float *)this + 107522)) * v34 + *((float *)this + 107522);
    v57 = v71 + *((float *)this + 107523);
    v64 = v72 + *((float *)this + 107524);
    v66 = v73 + *((float *)this + 107525);
    v68 = v74 + *((float *)this + 107526);
    v33 = v75 + *((float *)this + 107527);
    *((float *)this + 107529) = v57;
    *((float *)this + 107530) = v64;
    *((float *)this + 107531) = v66;
    *((float *)this + 107532) = v68;
    v70 = v33;
    *((float *)this + 107528) = v32;
    *((float *)this + 107533) = v70;
    *((float *)this + 107528) = v25;
    *((float *)this + 107529) = v43;
    *((float *)this + 107530) = v48;
  }
  ((CCCTData *)*((CCCTData **)this + 107501))->CCCTData::UpdateCamera((int)this + 430112);
  ((CameraCtrl *)*((CameraCtrl **)this + 107501))->SetAsCurrent(3);
  if ( v34 >= 1.0 )
    v3->bFinished = 1;
}

// 0x00508190
// attributes: thunk
bool CCCTData::ClearList()
{
  return this->IsTaskValid();
}

// 0x005081A0
bool CCCTData::IsTaskValid()
{
  *((_DWORD *)&g_CCBCamControlData + 366) = 1094713344;
  return 0;
}

// 0x005081B0
// attributes: thunk
void CCCTData::GetTaskNumInList()
{

}

// 0x005081C0
void CCCTData::GetFreeSpaceInPool()
{
  *((float *)&g_CCBCamControlData + 365) = 12.0 + 12.0;
}
