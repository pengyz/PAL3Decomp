#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/RoleShadow.h"

// Forward declarations for unnamed functions
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations

// Unnamed globals (extern)
extern int dword_56B220[];
extern char * off_5AC084;
extern void *off_5AC088;
extern void *off_5AC0A0;
extern void *off_5AC180;
extern RoleSystem stru_C059A0;

// 0x0044D290
int RoleShadow::InitParticles()
{
  DWORD Time; // eax
  float *p_y; // esi
  int v4; // ebp
  int result; // eax
  int v6; // [esp+0xC] [ebp-0x4]

  Time = timeGetTime();
  CRT_set_new_handler(Time);
  p_y = &this->m_CtrlRoleQuad.vec[0].y;
  v4 = 16;
  do
  {
    *((_DWORD *)p_y - 4) = rand() % 50 + 111;
    v6 = rand() % 500 + 150;
    *((_DWORD *)p_y - 5) = v6;
    *(p_y - 1) = (float)v6;
    *((_DWORD *)p_y - 3) = *(_DWORD *)p_y + *((_DWORD *)p_y - 5);
    *((_DWORD *)p_y - 2) = *((_DWORD *)p_y - 4) + *((_DWORD *)p_y + 1);
    p_y[2] = (double)(rand() % 16) * 0.1 + 1.0;
    p_y[3] = (float)(rand() % 255);
    p_y[4] = (double)(rand() % 10 + 10) * 0.1;
    *((_BYTE *)p_y + 20) = 1;
    result = sub_445FA0(p_y - 43);
    p_y += 52;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x00453FA0
int RoleShadow::InitFromTemplate(int nVal)
{
  float *p_sv; // ebx
  float x; // edx
  float y; // edx
  int v6; // eax
  float *p_z; // edi
  int v8; // ebx
  float v9; // edx
  float z; // edx
  float v11; // eax
  float v12; // edx
  float eu; // eax
  int v14; // eax
  float v15; // edx
  int v16; // ecx
  float v17; // edx
  int v18; // eax
  int v19; // ecx
  float v20; // edx
  unsigned __int8 v22; // [esp+0x94] [ebp-0x50]
  int v23; // [esp+A4h] [ebp-0x40] BYREF
  int v24; // [esp+A8h] [ebp-0x3C]
  int v25; // [esp+ACh] [ebp-0x38]
  int v26; // [esp+B0h] [ebp-0x34]
  int v27; // [esp+B4h] [ebp-0x30] BYREF
  int v28; // [esp+B8h] [ebp-0x2C]
  int v29; // [esp+BCh] [ebp-0x28]
  int v30; // [esp+C0h] [ebp-0x24]
  _DWORD v31[4]; // [esp+C4h] [ebp-0x20] BYREF
  int v32[4]; // [esp+D4h] [ebp-0x10] BYREF

  p_sv = &this->m_quad[0].sv;
  ((UIListBox *)this)->SetSelTexture(0, LODWORD(this->m_quad[0].sv), LODWORD(this->m_quad[0].eu), LODWORD(this->m_quad[0].ev), this->m_quad[0].color, 0);
  x = this->m_quad[5].vec[0].x;
  LODWORD(this->m_CtrlRoleQuad.eu) = nVal;
  (*(void ( **)(gbGeomQuad *, _DWORD, float *, RoleShadow *))(LODWORD(x) + 16))(
    &this->m_quad[5],
    0,
    p_sv,
    this);
  ((UIStatic *)&this->m_quad[5])->CreateFromTemplate();
  y = this->m_quad[7].vec[1].y;
  v31[1] = 66;
  v31[0] = 192;
  v31[2] = 620;
  v31[3] = 148;
  (*(void ( **)(float *, _DWORD, _DWORD *, RoleShadow *))(LODWORD(y) + 16))(
    &this->m_quad[7].vec[1].y,
    0,
    v31,
    this);
  ((UIScene *)&this->m_quad[7].vec[1].y)->SetShow(0);
  ((UICaption *)&this->m_quad[7].vec[1].y)->SetEnable((int)g_szSceneUIText, 0);
  v28 = 190;
  v27 = 18;
  v29 = 274;
  v30 = 534;
  p_z = &this->m_quad[9].vec[2].z;
  v8 = 0;
  do
  {
    LOBYTE(v6) = g_bAudioEnabled;
    (*(void ( **)(float *, int, int *, RoleShadow *, char *, int))(*(_DWORD *)p_z + 32))(
      p_z,
      dword_56B220[v8],
      &v27,
      this,
      off_5AC088[v8],
      v6);
    p_z[90] = 0.0;
    ((PalScript *)p_z)->OpenScript(off_5AC084, g_bAudioEnabled);
    ++v8;
    p_z += 94;
    v27 += 257;
    v6 = v27 + 256;
    v29 = v27 + 256;
  }
  while ( v8 < 3 );
  LOBYTE(v6) = g_bAudioEnabled;
  v9 = this->m_quad[26].vec[0].y;
  v28 = 537;
  v27 = 745;
  v29 = 801;
  v30 = 599;
  (*(void ( **)(float *, int, int *, RoleShadow *, char *, _DWORD, int))(LODWORD(v9) + 28))(
    &this->m_quad[26].vec[0].y,
    193,
    &v27,
    this,
    off_5AC180[0],
    0,
    v6);
  z = this->m_quad[31].vec[0].z;
  v24 = 58;
  v23 = 136;
  v25 = 648;
  v26 = 158;
  (*(void ( **)(float *, int, int *, RoleShadow *))(LODWORD(z) + 16))(
    &this->m_quad[31].vec[0].z,
    -1431699270,
    &v23,
    this);
  ((UIStatic *)&this->m_quad[31].vec[0].z)->CreateFromTemplate();
  v11 = this->m_quad[33].vec[2].x;
  v24 = 0;
  v23 = 0;
  v25 = 14;
  v26 = 600;
  (*(void ( **)(gbVec3D *, int, int *, RoleShadow *))(LODWORD(v11) + 16))(
    &this->m_quad[33].vec[2],
    -1431699269,
    &v23,
    this);
  ((UIStatic *)&this->m_quad[33].vec[2])->CreateFromTemplate();
  v12 = this->m_quad[35].vec[3].y;
  v23 = 786;
  v25 = 800;
  (*(void ( **)(float *, int, int *, RoleShadow *))(LODWORD(v12) + 16))(
    &this->m_quad[35].vec[3].y,
    -1431699268,
    &v23,
    this);
  ((UIStatic *)&this->m_quad[35].vec[3].y)->CreateFromTemplate();
  eu = this->m_quad[37].eu;
  v24 = 218;
  v23 = 365;
  v25 = 433;
  v26 = 250;
  (*(void ( **)(float *, int, int *, RoleShadow *))(LODWORD(eu) + 16))(
    &this->m_quad[37].eu,
    -1431699267,
    &v23,
    this);
  ((UIStatic *)&this->m_quad[37].eu)->CreateFromTemplate();
  v24 = v26;
  v23 -= 45;
  v15 = this->m_quad[42].vec[1].z;
  v26 += 38;
  v14 = v26;
  LOBYTE(v14) = g_bAudioEnabled;
  v25 = v23 + 162;
  (*(void ( **)(float *, int, int *, RoleShadow *, char *, _DWORD, int))(LODWORD(v15) + 28))(
    &this->m_quad[42].vec[1].z,
    -1431699013,
    &v23,
    this,
    off_5AC0A0[0],
    0,
    v14);
  ((CScreenMode *)&this->m_quad[42].vec[1].z)->SetTooltipText();
  v16 = v26;
  LOBYTE(this->m_quad[43].color) = 1;
  v17 = this->m_quad[52].vec[2].y;
  v24 = v16 + 1;
  v18 = v16 + 39;
  v26 = v16 + 39;
  LOBYTE(v18) = g_bAudioEnabled;
  (*(void ( **)(float *, int, int *, RoleShadow *, char *, _DWORD, int))(LODWORD(v17) + 28))(
    &this->m_quad[52].vec[2].y,
    -1431698501,
    &v23,
    this,
    off_5AC0A0[0],
    0,
    v18);
  ((CScreenMode *)&this->m_quad[52].vec[2].y)->SetTooltipText();
  v24 = v26;
  v23 += 45;
  v26 += 11;
  v19 = v23 + 68;
  LOBYTE(this->m_quad[54].vec[0].y) = 1;
  v20 = this->m_quad[40].vec[0].y;
  v25 = v19;
  (*(void ( **)(float *, int, int *, RoleShadow *))(LODWORD(v20) + 16))(
    &this->m_quad[40].vec[0].y,
    -1431699266,
    &v23,
    this);
  ((UIStatic *)&this->m_quad[40].vec[0].y)->CreateFromTemplate();
  v32[1] = 200;
  v32[0] = 336;
  v32[2] = 464;
  v32[3] = 400;
  ((ARC_PlayerAtt *)&this->m_quad[57].vec[2].z)->Create(-1431654210, (int)v32);
  LODWORD(this->m_CtrlRoleQuad.vec[3].z) = 5;
  LODWORD(this->m_CtrlRoleQuad.vec[3].y) = 30;
  ((LineupComp *)this)->SetVisible(1, v22);
  return this->CreateFromTemplate(0);
}

// 0x00454420
int RoleShadow::CreateFromTemplate(unsigned __int8 pData)
{
  float *p_z; // ebp

  p_z = &this->m_quad[31].vec[0].z;
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_quad[31].vec[0].z))(&this->m_quad[31].vec[0].z, pData);
  if ( pData && (LODWORD(this->m_CtrlRoleQuad.su) == 1 || (unsigned int)(LODWORD(this->m_CtrlRoleQuad.su) - 2) <= 1) )
    ((UIStatic *)p_z)->CreateFromTemplate();
  (*(void ( **)(gbVec3D *, _DWORD))LODWORD(this->m_quad[33].vec[2].x))(&this->m_quad[33].vec[2], pData);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_quad[35].vec[3].y))(&this->m_quad[35].vec[3].y, pData);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_quad[37].eu))(&this->m_quad[37].eu, pData);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_quad[42].vec[1].z))(&this->m_quad[42].vec[1].z, pData);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_quad[52].vec[2].y))(&this->m_quad[52].vec[2].y, pData);
  return (*(int ( **)(float *, _DWORD))LODWORD(this->m_quad[40].vec[0].y))(&this->m_quad[40].vec[0].y, pData);
}

// 0x00524E00
int RoleShadow::LoadQuadData(int *p_DWORD)
{
  float v2; // eax
  int result; // eax
  double v4; // st7
  double v5; // st7
  unsigned __int8 v7; // c0
  unsigned __int8 v8; // c3
  float p_DWORDa; // [esp+0xC] [ebp+0x4]

  LODWORD(this->m_CtrlRoleQuad.vec[0].x) = *p_DWORD;
  qmemcpy(&this->m_CtrlRoleQuad.vec[1].y, p_DWORD + 3, 0xDCu);
  v2 = *((float *)p_DWORD + 2);
  this->m_CtrlRoleQuad.vec[0].z = v2;
  this->m_CtrlRoleQuad.vec[1].x = v2;
  result = LODWORD(this->m_CtrlRoleQuad.vec[0].x);
  if ( result <= 0 )
    return result;
  v4 = (double)result;
  p_DWORDa = v4;
  if ( v4 > 500000.0 )
  {
    LODWORD(this->m_CtrlRoleQuad.vec[0].z) = 4;
    LODWORD(this->m_CtrlRoleQuad.vec[1].x) = 4;
    return 4;
  }
  if ( p_DWORDa <= 0.0 )
  {
    LODWORD(this->m_CtrlRoleQuad.vec[0].z) = 6;
    LODWORD(this->m_CtrlRoleQuad.vec[1].x) = 6;
    return 6;
  }
  v5 = 100.0 / (500000.0 / p_DWORDa) * 0.01;
  this->m_quad[32].vec[3].x = v5;
  if ( !(v7 | v8) )
  {
    if ( v5 < 0.25 )
    {
LABEL_7:
      this->m_CtrlRoleQuad.vec[0].z = 0.0;
      this->m_CtrlRoleQuad.vec[1].x = 0.0;
      return 0;
    }
LABEL_9:
    if ( v5 < 0.5 )
    {
      LODWORD(this->m_CtrlRoleQuad.vec[0].z) = 1;
      LODWORD(this->m_CtrlRoleQuad.vec[1].x) = 1;
      return 1;
    }
LABEL_12:
    if ( v5 < 0.75 )
    {
      LODWORD(this->m_CtrlRoleQuad.vec[0].z) = 2;
      LODWORD(this->m_CtrlRoleQuad.vec[1].x) = 2;
      return 2;
    }
    goto LABEL_14;
  }
  if ( v5 >= 0.25 )
    goto LABEL_9;
  if ( v5 >= 0.5 )
    goto LABEL_12;
LABEL_14:
  if ( v5 < 0.75 )
  {
    if ( v5 < 1.0 )
      goto LABEL_7;
  }
  else if ( v5 < 1.0 )
  {
    LODWORD(this->m_CtrlRoleQuad.vec[0].z) = 3;
    LODWORD(this->m_CtrlRoleQuad.vec[1].x) = 3;
    return 3;
  }
  LODWORD(this->m_CtrlRoleQuad.vec[0].z) = 4;
  LODWORD(this->m_CtrlRoleQuad.vec[1].x) = 4;
  return 4;
}

// 0x00524F90
int RoleShadow::UpdateShadow()
{
  if ( SLODWORD(this->m_CtrlRoleQuad.vec[0].x) > 0 )
    return ((CUtil *)LODWORD(this->m_quad[76].ev))->Update(2.0f);
  this->m_CtrlRoleQuad.vec[0].y = 0.0;
  sub_445E50((int)&this->m_quad[22].vec[2].y);
  ((UIScene *)&this->m_quad[18].vec[2].y)->RefreshLayout();
  sprintf(
    (char *const)&this->m_quad[1].vec[1].y,
    &dir[20],
    ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom - LODWORD(this->m_CtrlRoleQuad.vec[0].y));
  ((UICaption *)&this->m_quad[7].vec[1].y)->SetEnable((int)&this->m_quad[1].vec[1].y, 0);
  sprintf((char *const)&this->m_quad[1].vec[1].y, &dir[20], this->m_CtrlRoleQuad.vec[0].y);
  ((UICaption *)&this->m_quad[9].vec[2].z)->SetEnable((int)&this->m_quad[1].vec[1].y, 0);
  sprintf((char *const)&this->m_quad[1].vec[1].y, &dir[20], 500000);
  ((UICaption *)&this->m_quad[11].su)->SetEnable((int)&this->m_quad[1].vec[1].y, 0);
  sprintf((char *const)&this->m_quad[1].vec[1].y, &dir[20], this->m_CtrlRoleQuad.vec[0].x);
  ((UICaption *)&this->m_quad[13].color)->SetEnable((int)&this->m_quad[1].vec[1].y, 0);
  return ((CUtil *)LODWORD(this->m_quad[76].ev))->Update(5.0f);
}
