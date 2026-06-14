#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIGameOver.h"

// Forward declarations for unnamed functions
int sub_445FA0(void *a2); // from annotations

// 0x0044D470
int UIGameOver::InitParticle(int nIndex)
{
  DWORD Time; // eax
  char *v4; // esi
  int nIndexa; // [esp+0xC] [ebp+0x4]

  Time = timeGetTime();
  CRT_set_new_handler(Time);
  v4 = (char *)this + 208 * nIndex;
  *((_DWORD *)v4 + 167) = rand() % 160 + 238;
  nIndexa = rand() % 120 + 698;
  *((_DWORD *)v4 + 166) = nIndexa;
  *((float *)v4 + 170) = (float)nIndexa;
  *((_DWORD *)v4 + 168) = *((_DWORD *)v4 + 166) + *((_DWORD *)v4 + 171);
  *((_DWORD *)v4 + 169) = *((_DWORD *)v4 + 167) + *((_DWORD *)v4 + 172);
  *((float *)v4 + 173) = (double)(rand() % 16) * 0.1 + 1.0;
  *((float *)v4 + 174) = (float)(rand() % 255);
  *((float *)v4 + 175) = (double)(rand() % 10 + 10) * 0.1;
  v4[704] = 1;
  return sub_445FA0(v4 + 512);
}

// 0x0044D580
int UIGameOver::RandomizeEffects(int nVal)
{
  char *v2; // esi
  int nVala; // [esp+0xC] [ebp+0x4]

  v2 = (char *)this + 208 * nVal;
  *((_DWORD *)v2 + 1311) = rand() % 50 + 111;
  nVala = rand() % 120 + 698;
  *((_DWORD *)v2 + 1310) = nVala;
  *((float *)v2 + 1314) = (float)nVala;
  *((_DWORD *)v2 + 1312) = *((_DWORD *)v2 + 1310) + *((_DWORD *)v2 + 1315);
  *((_DWORD *)v2 + 1313) = *((_DWORD *)v2 + 1311) + *((_DWORD *)v2 + 1316);
  *((float *)v2 + 1317) = (double)(rand() % 16) * 0.1 + 1.0;
  *((float *)v2 + 1318) = (float)(rand() % 255);
  *((float *)v2 + 1319) = (double)(rand() % 10 + 10) * 0.1;
  v2[5280] = 1;
  return sub_445FA0(v2 + 5088);
}

// 0x0044D680
int UIGameOver::InitParticle2(int nIndex)
{
  char *v2; // esi
  int nIndexa; // [esp+0xC] [ebp+0x4]

  v2 = (char *)this + 208 * nIndex;
  *((_DWORD *)v2 + 2143) = rand() % 40 + 70;
  nIndexa = rand() % 120 + 698;
  *((_DWORD *)v2 + 2142) = nIndexa;
  *((float *)v2 + 2146) = (float)nIndexa;
  *((_DWORD *)v2 + 2144) = *((_DWORD *)v2 + 2142) + *((_DWORD *)v2 + 2147);
  *((_DWORD *)v2 + 2145) = *((_DWORD *)v2 + 2143) + *((_DWORD *)v2 + 2148);
  *((float *)v2 + 2149) = (double)(rand() % 16) * 0.1 + 1.0;
  *((float *)v2 + 2150) = (float)(rand() % 255);
  *((float *)v2 + 2151) = (double)(rand() % 10 + 10) * 0.1;
  v2[8608] = 1;
  return sub_445FA0(v2 + 8416);
}

// 0x004500F0
void UIGameOver::Create()
{
  void *vftable; // edx
  int v3; // [esp+0xC] [ebp-0x10] BYREF
  int v4; // [esp+0x10] [ebp-0xC]
  int width; // [esp+0x14] [ebp-0x8]
  int height; // [esp+0x18] [ebp-0x4]

  v3 = 0;
  v4 = 0;
  width = g_DrvInfo.width;
  height = g_DrvInfo.height;
  ((UIListBox *)this)->SetSelTexture(0, 0, 0, g_DrvInfo.width, g_DrvInfo.height, 0);
// [VFTABLE] vftable = this->m_Blood.__vftable;
  v3 = (g_DrvInfo.width - 256) / 2;
  width = v3 + 256;
  height = g_DrvInfo.height;
  v4 = 0;
  ((void ( *)(UIStatic *, _DWORD, int *, UIGameOver *))vftable->Create)(
    &this->m_Blood,
    0,
    &v3,
    this);
  ((UIStatic *)&this->m_Blood)->CreateFromTemplate();
  this->m_fTime = 0.0;
}

// 0x0052E500
void UIGameOver::SetupDisplay(int nVal)
{
  double v3; // st7
  Parent_Data *v4; // eax
  double v5; // st7
  Parent_Data *m_fonttype; // ecx
  double v7; // st7
  gbTexture *v8; // edx
  double v9; // st7
  gbTexture *v10; // eax
  double v11; // st7
  _PlugInfo *v12; // ecx
  double v13; // st7
  _PlugInfo *v14; // edx
  double v15; // st7
  gbTexture *v16; // eax
  double v17; // st7
  gbTexture *v18; // ecx
  unsigned int m_FVF; // ebp
  float v20; // eax
  float v21; // eax
  unsigned int v22; // edx

  if ( !this->m_Blood.m_mouseoff )
    return;
  if ( *(float *)&this->m_Blood.m_text[12] >= (double)*(float *)&this->m_Blood.m_fonttype )
  {
    if ( *(float *)&this->m_Blood.m_text[12] <= (double)*(float *)&this->m_Blood.m_fonttype )
      goto LABEL_9;
    v5 = *(float *)&this->m_Blood.m_text[12] - *(float *)&this->m_Blood.m_ppicInfo;
    *(float *)&this->m_Blood.m_text[12] = v5;
    if ( v5 <= *(float *)&this->m_Blood.m_fonttype )
    {
      m_fonttype = this->m_Blood.m_fonttype;
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      *(_DWORD *)&this->m_Blood.m_text[12] = m_fonttype;
      goto LABEL_9;
    }
  }
  else
  {
    v3 = *(float *)&this->m_Blood.m_ppicInfo + *(float *)&this->m_Blood.m_text[12];
    *(float *)&this->m_Blood.m_text[12] = v3;
    if ( v3 >= *(float *)&this->m_Blood.m_fonttype )
    {
      v4 = this->m_Blood.m_fonttype;
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      *(_DWORD *)&this->m_Blood.m_text[12] = v4;
      goto LABEL_9;
    }
  }
  *(&this->m_Blood.m_mouseoff + 1) = 0;
LABEL_9:
  if ( *(float *)&this->m_Blood.m_pbk >= (double)*(float *)this->m_Blood.m_text )
  {
    if ( *(float *)&this->m_Blood.m_pbk <= (double)*(float *)this->m_Blood.m_text )
      goto LABEL_16;
    v9 = *(float *)&this->m_Blood.m_pbk - *(float *)&this->m_Blood.m_disablepic;
    *(float *)&this->m_Blood.m_pbk = v9;
    if ( v9 <= *(float *)this->m_Blood.m_text )
    {
      v10 = *(gbTexture **)this->m_Blood.m_text;
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_pbk = v10;
      goto LABEL_16;
    }
  }
  else
  {
    v7 = *(float *)&this->m_Blood.m_disablepic + *(float *)&this->m_Blood.m_pbk;
    *(float *)&this->m_Blood.m_pbk = v7;
    if ( v7 >= *(float *)this->m_Blood.m_text )
    {
      v8 = *(gbTexture **)this->m_Blood.m_text;
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_pbk = v8;
      goto LABEL_16;
    }
  }
  *(&this->m_Blood.m_mouseoff + 1) = 0;
LABEL_16:
  if ( *(float *)&this->m_Blood.m_pbkInfo >= (double)*(float *)&this->m_Blood.m_text[4] )
  {
    if ( *(float *)&this->m_Blood.m_pbkInfo <= (double)*(float *)&this->m_Blood.m_text[4] )
      goto LABEL_23;
    v13 = *(float *)&this->m_Blood.m_pbkInfo - *(float *)&this->m_Blood.m_disablepicInfo;
    *(float *)&this->m_Blood.m_pbkInfo = v13;
    if ( v13 <= *(float *)&this->m_Blood.m_text[4] )
    {
      v14 = *(_PlugInfo **)&this->m_Blood.m_text[4];
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_pbkInfo = v14;
      goto LABEL_23;
    }
  }
  else
  {
    v11 = *(float *)&this->m_Blood.m_disablepicInfo + *(float *)&this->m_Blood.m_pbkInfo;
    *(float *)&this->m_Blood.m_pbkInfo = v11;
    if ( v11 >= *(float *)&this->m_Blood.m_text[4] )
    {
      v12 = *(_PlugInfo **)&this->m_Blood.m_text[4];
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_pbkInfo = v12;
      goto LABEL_23;
    }
  }
  *(&this->m_Blood.m_mouseoff + 1) = 0;
LABEL_23:
  if ( *(float *)&this->m_Blood.m_ppic >= (double)*(float *)&this->m_Blood.m_text[8] )
  {
    if ( *(float *)&this->m_Blood.m_ppic <= (double)*(float *)&this->m_Blood.m_text[8] )
      goto LABEL_30;
    v17 = *(float *)&this->m_Blood.m_ppic - *(float *)&this->m_Blood.m_pbk2;
    *(float *)&this->m_Blood.m_ppic = v17;
    if ( v17 <= *(float *)&this->m_Blood.m_text[8] )
    {
      v18 = *(gbTexture **)&this->m_Blood.m_text[8];
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_ppic = v18;
      goto LABEL_30;
    }
LABEL_29:
    *(&this->m_Blood.m_mouseoff + 1) = 0;
    goto LABEL_30;
  }
  v15 = *(float *)&this->m_Blood.m_pbk2 + *(float *)&this->m_Blood.m_ppic;
  *(float *)&this->m_Blood.m_ppic = v15;
  if ( v15 < *(float *)&this->m_Blood.m_text[8] )
    goto LABEL_29;
  v16 = *(gbTexture **)&this->m_Blood.m_text[8];
  *(&this->m_Blood.m_mouseoff + 1) = 1;
  this->m_Blood.m_ppic = v16;
LABEL_30:
  if ( *(&this->m_Blood.m_mouseoff + 1) )
  {
    if ( LOBYTE(this->m_Blood.m_nTextW) )
    {
      this->m_Blood.m_mouseoff = 0;
      *(&this->m_Blood.m_mouseoff + 1) = 0;
      LOBYTE(this->m_Blood.m_nTextW) = 0;
    }
    if ( *(&this->m_Blood.m_mouseoff + 1) )
    {
      m_FVF = this->m_Blood.m_FVF;
      if ( !LOBYTE(this->m_Blood.m_texty) )
      {
        v20 = COERCE_FLOAT(GetTickCount());
        this->m_Blood.m_ratioh = v20;
        *(float *)&this->m_Blood.m_textx = v20;
        LOBYTE(this->m_Blood.m_texty) = 1;
      }
      v21 = COERCE_FLOAT(GetTickCount());
      v22 = LODWORD(v21) - this->m_Blood.m_textx;
      this->m_Blood.m_ratioh = v21;
      if ( v22 > m_FVF )
      {
        *(float *)&this->m_Blood.m_textx = v21;
        LOBYTE(this->m_Blood.m_texty) = 0;
        *(&this->m_Blood.m_mouseoff + 1) = 0;
        *(_DWORD *)&this->m_Blood.m_text[8] = 0;
        *(_DWORD *)&this->m_Blood.m_text[4] = 0;
        *(_DWORD *)this->m_Blood.m_text = 0;
        this->m_Blood.m_fonttype = 0;
        LOBYTE(this->m_Blood.m_nTextW) = 1;
      }
    }
  }
  ((UIScene *)this)->CalcViewTransform(1);
}

// 0x00530570
int UIGameOver::ClearState()
{
// [VFTABLE] this->__vftable = 0;
  this->m_fontcolor.Color = 0;
  *((_DWORD *)this + 144) = 0;
  *((_DWORD *)this + 194) = 0;
  *((_DWORD *)this + 145) = 0;
  *((_DWORD *)this + 195) = 0;
  LOBYTE(this->m_fTime) = 0;
  *((_DWORD *)this + 121) = 0;
  return 0;
}

// 0x005305A0
int UIGameOver::ResetState()
{
  *((_DWORD *)this + 149) = 0;
  *((_DWORD *)this + 150) = 0;
  *((_DWORD *)this + 151) = 0;
  *((_DWORD *)this + 146) = 0;
  *((_DWORD *)this + 147) = *((_DWORD *)this + 150);
  *((_DWORD *)this + 148) = *((_DWORD *)this + 151);
  *((_DWORD *)this + 152) = 0;
  *((_DWORD *)this + 153) = 0;
  *((_DWORD *)this + 154) = 0;
  *((_DWORD *)this + 155) = 0;
  *((_DWORD *)this + 156) = *((_DWORD *)this + 153);
  *((_DWORD *)this + 157) = *((_DWORD *)this + 154);
  *((_DWORD *)this + 158) = 0;
  *((_DWORD *)this + 159) = 0;
  *((_DWORD *)this + 160) = 0;
  *((_DWORD *)this + 161) = 0;
  *((_DWORD *)this + 162) = 0;
  *((_DWORD *)this + 163) = -1165815185;
  *((_DWORD *)this + 164) = 0;
  *((_DWORD *)this + 165) = 1093517967;
  *((_DWORD *)this + 166) = 1093517967;
  *((_DWORD *)this + 169) = 0;
  *((_DWORD *)this + 181) = 0;
  return 0;
}
