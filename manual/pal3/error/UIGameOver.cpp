#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIGameOver.h"
#include "Misc/Parent_Data.h"
#include "UI/UIListBox.h"
#include "Misc/UIPushButton.h"
#include "UI/UIScene.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"

// Forward declarations for unnamed functions

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
  return (((UIWnd *)(v4 + 512)))->UIWnd::sub_445FA0(v4 + 664);
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
  return (((UIWnd *)(v2 + 5088)))->UIWnd::sub_445FA0(v2 + 5240);
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
  return (((UIWnd *)(v2 + 8416)))->UIWnd::sub_445FA0(v2 + 8568);
}

// 0x004500F0
void UIGameOver::Create()
{
  int v2; // edx
  int v3; // [esp+0xC] [ebp-0x10] BYREF
  int v4; // [esp+0x10] [ebp-0xC]
  int width; // [esp+0x14] [ebp-0x8]
  int height; // [esp+0x18] [ebp-0x4]

  v3 = 0;
  v4 = 0;
  width = g_DrvInfo.width;
  height = g_DrvInfo.height;
  (((UIListBox *)this))->UIListBox::SetSelTexture(0, 0, 0, g_DrvInfo.width, g_DrvInfo.height) /* [ROWTABLE] */;
  v2 = (int)((UIWnd *)&this->m_Blood);
  v3 = (g_DrvInfo.width - 256) / 2;
  width = v3 + 256;
  height = g_DrvInfo.height;
  v4 = 0;
  (*(void ( **)(UIStatic *, _DWORD, int *, UIGameOver *))(v2 + 16))(&this->m_Blood, 0, &v3, this);
  (((UIPushButton *)&this->m_Blood))->UIPushButton::CreateFromTemplate("ui\\GameOver\\di.tga", 0);
  this->m_fTime = 0.0f;
}

// 0x0052E500
void UIGameOver::SetupDisplay(int nVal)
{
  float v3; // st7
  Parent_Data *v4; // eax
  float v5; // st7
  Parent_Data *m_fonttype; // ecx
  float v7; // st7
  gbTexture *v8; // edx
  float v9; // st7
  gbTexture *v10; // eax
  float v11; // st7
  _PlugInfo *v12; // ecx
  float v13; // st7
  _PlugInfo *v14; // edx
  float v15; // st7
  gbTexture *v16; // eax
  float v17; // st7
  gbTexture *v18; // ecx
  unsigned int m_FVF; // ebp
  void *TickCount; // eax
  _BYTE *v21; // eax
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
      m_fonttype = (Parent_Data *)this->m_Blood.m_fonttype;
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      *(_DWORD *)&this->m_Blood.m_text[12] = (_DWORD)m_fonttype;
      goto LABEL_9;
    }
  }
  else
  {
    v3 = *(float *)&this->m_Blood.m_ppicInfo + *(float *)&this->m_Blood.m_text[12];
    *(float *)&this->m_Blood.m_text[12] = v3;
    if ( v3 >= *(float *)&this->m_Blood.m_fonttype )
    {
      v4 = (Parent_Data *)this->m_Blood.m_fonttype;
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      *(_DWORD *)&this->m_Blood.m_text[12] = (_DWORD)v4;
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
      v10 = (gbTexture *)*(gbTexture **)this->m_Blood.m_text;
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_pbk = ((gbTexture *)(v10));
      goto LABEL_16;
    }
  }
  else
  {
    v7 = *(float *)&this->m_Blood.m_disablepic + *(float *)&this->m_Blood.m_pbk;
    *(float *)&this->m_Blood.m_pbk = v7;
    if ( v7 >= *(float *)this->m_Blood.m_text )
    {
      v8 = (gbTexture *)*(gbTexture **)this->m_Blood.m_text;
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_pbk = ((gbTexture *)(v8));
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
      v14 = (_PlugInfo *)(*(_PlugInfo **)&this->m_Blood.m_text[4]);
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_pbkInfo = ((_PlugInfo *)(v14));
      goto LABEL_23;
    }
  }
  else
  {
    v11 = *(float *)&this->m_Blood.m_disablepicInfo + *(float *)&this->m_Blood.m_pbkInfo;
    *(float *)&this->m_Blood.m_pbkInfo = v11;
    if ( v11 >= *(float *)&this->m_Blood.m_text[4] )
    {
      v12 = (_PlugInfo *)(*(_PlugInfo **)&this->m_Blood.m_text[4]);
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_pbkInfo = ((_PlugInfo *)(v12));
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
      v18 = (gbTexture *)(*(gbTexture **)&this->m_Blood.m_text[8]);
      *(&this->m_Blood.m_mouseoff + 1) = 1;
      this->m_Blood.m_ppic = ((gbTexture *)(v18));
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
  v16 = (gbTexture *)(*(gbTexture **)&this->m_Blood.m_text[8]);
  *(&this->m_Blood.m_mouseoff + 1) = 1;
  this->m_Blood.m_ppic = ((gbTexture *)(v16));
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
        TickCount = (void *)GetTickCount();
        LODWORD(this->m_Blood.m_ratioh) = (unsigned long)TickCount;
        this->m_Blood.m_textx = ((void *)(TickCount));
        LOBYTE(this->m_Blood.m_texty) = 1;
      }
      v21 = (_BYTE *)GetTickCount();
      v22 = (unsigned int)v21 - (char *)this->m_Blood.m_textx;
      LODWORD(this->m_Blood.m_ratioh) = (unsigned long)v21;
      if ( v22 > m_FVF )
      {
        this->m_Blood.m_textx = ((void *)((void *)v21));
        LOBYTE(this->m_Blood.m_texty) = 0;
        *(&this->m_Blood.m_mouseoff + 1) = 0;
        *(_DWORD *)&this->m_Blood.m_text[8] = 0;
        *(_DWORD *)&this->m_Blood.m_text[4] = 0;
        *(_DWORD *)this->m_Blood.m_text = 0;
        this->m_Blood.m_fonttype = ((Parent_Data *)0);
        LOBYTE(this->m_Blood.m_nTextW) = 1;
      }
    }
  }
  (((UIScene *)this))->UIScene::CalcViewTransform(1) /* [ROWTABLE] */;
}
