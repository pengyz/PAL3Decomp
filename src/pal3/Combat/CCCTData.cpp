#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCCTData.h"
#include "pal3/gen/CCBStageCam.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_41CA30(...);
int sub_506340(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Co_6[];
extern char aUiCombatPointe[];
extern unsigned char byte_17AAEE0;
extern unsigned char byte_17AAF21;
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
extern float flt_17AAD54;
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
extern int nullsub_3;
extern int nullsub_31;
extern void *off_56A66C;
extern int unk_17AAD89;

// 0x0041C900
void CCCTData::CalcDist(float a1, float a2)
{
  double v2; // st7
  float *v3; // ecx
  long double v4; // st6
  double v5; // st7
  float v6; // [esp+0h] [ebp-10h]
  float v7; // [esp+4h] [ebp-Ch]
  float v8; // [esp+1Ch] [ebp+Ch]
  gbVec3D v9; // [esp+20h] [ebp+10h] BYREF
  int v10; // [esp+2Ch] [ebp+1Ch]
  int v11; // [esp+30h] [ebp+20h]

  v2 = v9.x - a1;
  v3 = (float *)v10;
  v6 = v9.z - v8;
  v4 = atan2(-(v2 / v6), 1.0);
  *(float *)v10 = v4;
  if ( v9.z > (double)v8 )
    * v3 = (*)v4 + 3.1415927;
  v7 = v2;
  v9.x = v7;
  v9.z = v6;
  *(float *)&v10 = v9.y - a2;
  LODWORD(v9.y) = v10;
  v5 = ((gbVec3D *)&v9)->Length();
  *(float *)v11 = asin(*(float *)&v10 / v5);
}

// 0x005044C0
int CCCTData::UpdateCamera(int a2)
{
  return sub_41CA30(
           this,
           *(_DWORD *)(a2 + 12),
           *(_DWORD *)(a2 + 16),
           *(_DWORD *)(a2 + 20),
           *(_DWORD *)a2,
           *(_DWORD *)(a2 + 4),
           *(_DWORD *)(a2 + 8));
}

// 0x005058F0
CCCTData::CCCTData(_DWORD *a2, _DWORD *a3)
{
  int result; // eax

  this->_d69094 = *a2;
  this->_f69098 = (float)a2[1];
  this->_f6909C = (float)a2[2];
  this->_f690A0 = *(float *)a3;
  this->_d690A4 = a3[1];
  result = a3[2];
  this->_d690A8 = result;
  result;
}

// 0x00505930
CCCTData::~CCCTData()
{
  int *p_d69094; // ebp
  struct gbRenderEffect *v3; // ebx
  float *v4; // esi
  _BYTE *v5; // esi
  unsigned int *p_Color; // esi
  double v7; // st7
  float v8; // edx
  float f69098; // eax
  int f6909C_low; // ecx
  double f690A0; // st7
  float v12; // edx
  int d690A4; // eax
  int d690A8; // ecx
  float v15; // edx
  float v16; // eax
  float v17; // ecx
  int v18; // edx
  float *d68FB4; // edi
  double v20; // st7
  double v21; // st6
  unsigned int v22; // edx
  double v23; // st6
  gbColorQuad v24; // [esp+40h] [ebp-A8h] BYREF
  int v25; // [esp+4Ch] [ebp-9Ch]
  int v26; // [esp+64h] [ebp-84h]
  float f6909C; // [esp+68h] [ebp-80h]
  int v28; // [esp+6Ch] [ebp-7Ch]
  int v29; // [esp+70h] [ebp-78h]
  int v30; // [esp+74h] [ebp-74h]
  int v31; // [esp+78h] [ebp-70h]
  struct gbColorQuad v32; // [esp+7Ch] [ebp-6Ch] BYREF
  float v33; // [esp+88h] [ebp-60h]
  float v34; // [esp+8Ch] [ebp-5Ch]
  float v35; // [esp+90h] [ebp-58h]
  float v36; // [esp+94h] [ebp-54h]
  int ColorQuadFmt; // [esp+98h] [ebp-50h]
  _BYTE v38[64]; // [esp+9Ch] [ebp-4Ch] BYREF
  float v39; // [esp+DCh] [ebp-Ch]
  float v40; // [esp+E0h] [ebp-8h]
  float v41; // [esp+E4h] [ebp-4h]

  if ( this->_tail[0] )
  {
    ((gbMatrix4 *)v38)->gbMatrix4();
    ((gbGeomNode *)this->_d69090)->GetTotalOBBox((struct gbOBBox *)v38);
    p_d69094 = (int *)&this->_d69094;
    ((gbMatrix4 *)v38)->RightTranslate((struct gbVec3D *)&this->_d69094);
    v3 = ((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewTrivalEffect(3);
    *(_DWORD *)&v32.Blue = ((gbVertPoolMgr *)g_pGfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
    if ( (byte_17AAEE0 & 1) == 0 )
    {
      v4 = (float *)&g_fMoveSpeed;
      byte_17AAEE0 |= 1u;
      v28 = 6;
      do
      {
        ArraySort((int)v4, 12, 4, gbVec3D::`default constructor closure');
        v4 += 17;
        --v28;
      }
      while ( *(float *)&v28 != 0.0 );
      atexit(nullsub_31);
    }
    v39 = v39 + 2.0;
    v40 = v40 + 2.0;
    v41 = v41 + 2.0;
    *(float *)&v31 = v40 * 0.5;
    dword_17AAD4C = v31;
    *(float *)&v28 = v41 * 0.5;
    g_fMoveSpeed = v39 * -0.5;
    dword_17AAD50 = v28;
    dword_17AAD58 = v31;
    flt_17AAD54 = v39 * 0.5;
    dword_17AAD5C = v28;
    dword_17AAD68 = v28;
    *(float *)&v29 = v40 * -0.5;
    flt_17AAD60 = flt_17AAD54;
    dword_17AAD64 = v29;
    flt_17AAD6C = g_fMoveSpeed;
    dword_17AAD70 = v29;
    *(float *)&v30 = v41 * -0.5;
    dword_17AAD74 = v28;
    flt_17AAD8C = g_fMoveSpeed;
    dword_17AAD90 = v31;
    dword_17AAD94 = v30;
    flt_17AAD98 = flt_17AAD54;
    dword_17AAD9C = v31;
    dword_17AADA0 = v30;
    flt_17AADA4 = flt_17AAD54;
    flt_17AADB0 = g_fMoveSpeed;
    flt_17AADD0 = g_fMoveSpeed;
    dword_17AADA8 = v29;
    dword_17AADAC = v30;
    dword_17AADB4 = v29;
    dword_17AADB8 = v30;
    flt_17AADDC = g_fMoveSpeed;
    dword_17AADD4 = v31;
    dword_17AADD8 = v28;
    flt_17AADE8 = g_fMoveSpeed;
    dword_17AADE0 = v31;
    dword_17AADE4 = v30;
    flt_17AADF4 = g_fMoveSpeed;
    dword_17AADEC = v29;
    dword_17AADF0 = v30;
    dword_17AADF8 = v29;
    flt_17AAE14 = flt_17AAD54;
    dword_17AADFC = v28;
    dword_17AAE18 = v31;
    dword_17AAE1C = v28;
    flt_17AAE20 = flt_17AAD54;
    dword_17AAE24 = v31;
    dword_17AAE28 = v30;
    flt_17AAE2C = flt_17AAD54;
    dword_17AAE30 = v29;
    flt_17AAE38 = flt_17AAD54;
    flt_17AAE58 = g_fMoveSpeed;
    dword_17AAE34 = v30;
    dword_17AAE3C = v29;
    flt_17AAE64 = flt_17AAD54;
    dword_17AAE40 = v28;
    dword_17AAE5C = v31;
    dword_17AAE60 = v30;
    flt_17AAE70 = flt_17AAD54;
    dword_17AAE68 = v31;
    dword_17AAE6C = v30;
    dword_17AAE74 = v31;
    flt_17AAE7C = g_fMoveSpeed;
    dword_17AAE78 = v28;
    dword_17AAE80 = v31;
    flt_17AAE9C = g_fMoveSpeed;
    dword_17AAE84 = v28;
    dword_17AAEA0 = v29;
    dword_17AAEA4 = v30;
    flt_17AAEA8 = flt_17AAD54;
    flt_17AAEB4 = flt_17AAD54;
    dword_17AAEAC = v29;
    dword_17AAEB0 = v30;
    flt_17AAEC0 = g_fMoveSpeed;
    dword_17AAEB8 = v29;
    dword_17AAEBC = v28;
    v26 = v29;
    f6909C = *(float *)&v28;
    dword_17AAEC4 = v29;
    dword_17AAEC8 = v28;
    v5 = (_BYTE *)&unk_17AAD89;
    do
    {
      v5[1] = -1;
      *v5 = -1;
      v25 = 4;
      *(v5 - 1) = 10;
      v24.Color = (unsigned int)(v5 - 65);
      v5[2] = -101;
      ((gbMatrix4 *)v38)->Transform((struct gbVec3D *)v24.Color, v25);
      v5 += 68;
    }
    while ( (int)v5 < (int)byte_17AAF21 );
    ((gbDynVertBuf *)&g_fMoveSpeed)->RenderGeomQuad(6, v3, 0);
    p_Color = (unsigned int *)&v32.Color;
    v28 = 2;
    do
    {
      ((void (*)(unsigned int *))gbVec3D::`default constructor closure')(p_Color);
      p_Color += 3;
      --v28;
    }
    while ( *(float *)&v28 != 0.0 );
    v7 = *(float *)p_d69094;
    v8 = *(float *)p_d69094;
    f69098 = this->_f69098;
    f6909C = this->_f6909C;
    v35 = v8;
    *(float *)&v32.Color = v7;
    v34 = f6909C;
    f6909C_low = LODWORD(this->_f6909C);
    v25 = (int)v3;
    v24.Color = 2;
    *(_DWORD *)&v24.Blue = &v32.Color;
    v36 = f69098;
    v24.ColorQuadFmt = f6909C_low;
    ColorQuadFmt = f6909C_low;
    v32.ColorQuadFmt = 1358954495;
    v33 = 0.0;
    ((gbColorQuad *)&v24)->gbColorQuad(&v32);
    ((gbDynVertBuf *)LODWORD(v35))->RenderLineStrip();
    f690A0 = this->_f690A0;
    v12 = this->_f690A0;
    d690A4 = this->_d690A4;
    f6909C = *(float *)&this->_d690A8;
    v35 = v12;
    *(float *)&v32.Color = f690A0;
    v34 = f6909C;
    d690A8 = this->_d690A8;
    v25 = (int)v3;
    v24.Color = 2;
    *(_DWORD *)&v24.Blue = &v32.Color;
    v36 = *(float *)&d690A4;
    v24.ColorQuadFmt = d690A8;
    ColorQuadFmt = d690A8;
    v33 = 0.0;
    ((gbColorQuad *)&v24)->gbColorQuad(&v32);
    ((gbDynVertBuf *)LODWORD(v35))->RenderLineStrip();
    v15 = this->_f69098;
    v16 = this->_f6909C;
    v32.Color = *p_d69094;
    v17 = this->_f690A0;
    v33 = v15;
    v18 = this->_d690A4;
    v35 = v17;
    v25 = (int)v3;
    v24.Color = 2;
    *(_DWORD *)&v24.Blue = &v32.Color;
    v36 = *(float *)&v18;
    v24.ColorQuadFmt = (int)&v32.Color;
    v34 = v16;
    ColorQuadFmt = this->_d690A8;
    ((gbColorQuad *)&v24)->gbColorQuad(&v32);
    ((gbDynVertBuf *)LODWORD(v35))->RenderLineStrip();
    d68FB4 = (float *)this->_d68FB4;
    v20 = d68FB4[123] + 1.0;
    v21 = d68FB4[124] + 1.0;
    v22 = *p_d69094;
    v25 = (int)v3;
    v24.Color = 2;
    *(float *)&v26 = v21;
    v23 = d68FB4[125];
    v35 = *(float *)&v22;
    v33 = *(float *)&v26;
    v36 = *((float *)p_d69094 + 1);
    f6909C = v23 + 1.0;
    *(_DWORD *)&v24.Blue = &v32.Color;
    *(float *)&v32.Color = v20;
    v34 = f6909C;
    v24.ColorQuadFmt = p_d69094[2];
    ColorQuadFmt = v24.ColorQuadFmt;
    ((gbColorQuad *)&v24)->gbColorQuad(&v32);
    ((gbDynVertBuf *)LODWORD(v35))->RenderLineStrip();
    ((gbRefObject *)v3)->Release();
  }
}

// 0x00506020
bool CCCTData::Create(float *a2)
{
  int d68FB0; // eax
  CameraCtrl *d68FB4; // ecx
  float pPos[2]; // [esp+8h] [ebp-90h] BYREF
  struct gbVec3D v7; // [esp+10h] [ebp-88h] BYREF
  gbRay v8; // [esp+1Ch] [ebp-7Ch] BYREF
  _BYTE v9[76]; // [esp+34h] [ebp-64h] BYREF
  _BYTE pTarget[24]; // [esp+80h] [ebp-18h] BYREF

  ((gbMatrix4 *)v9)->gbMatrix4();
  ((gbGeomNode *)this->_d69090)->GetTotalOBBox((struct gbOBBox *)v9);
  v7.x = *a2;
  v7.y = a2[1];
  v7.z = a2[2];
  ((gbMatrix4 *)v9)->RightTranslate(&v7);
  d68FB0 = this->_d68FB0;
  pPos[0] = *(float *)(d68FB0 + 80);
  d68FB4 = (CameraCtrl *)this->_d68FB4;
  pPos[1] = *(float *)(d68FB0 + 84);
  qmemcpy(&v8, d68FB4->GetViewTarget(pTarget, pPos), sizeof(v8));
  return ((gbRay *)&v8)->IsColOBB((struct gbOBBox *)v9) == 1;
}

// 0x005060D0
char CCCTData::Destroy()
{
  gbGeomNode *v2; // eax
  gbGeomNode *v3; // esi
  gbGeomNode *v4; // ecx
  char pExceptionObject[1024]; // [esp+Ch] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+40Ch] [ebp-40Ch] BYREF
  int v8; // [esp+814h] [ebp-4h]

  v2 = (gbGeomNode *)operator new(0x118u);
  v3 = v2;
  v8 = 0;
  if ( v2 )
  {
    v2->gbGeomNode();
    *(_DWORD *)v3->_base = &off_56A66C;
    v4 = v3;
  }
  else
  {
    v4 = 0;
  }
  v8 = -1;
  this->_d69090 = (int)v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_6, 1425),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v4->LoadFromFile(aUiCombatPointe, 0, 0);
  return 1;
}

// 0x005061A0
void CCCTData::Init()
{
  int d68FD0; // edx
  int d68FD4; // ebp
  int v4; // ecx
  char *v5; // edi

  d68FD0 = this->_d68FD0;
  d68FD4 = this->_d68FD4;
  v4 = *(_DWORD *)&this->_p0000[200 * d68FD0 + 410000 + 4 * d68FD4];
  if ( v4 == -1 )
    v5 = 0;
  else
    v5 = (char *)&this->_p0000[204 * v4];
  if ( v5[22] )
  {
    this->_d68FD4 = d68FD4 + 1;
    if ( this->_d68FD4 >= ((CCBStageCam *)this)->IsEditorCamValid(d68FD0) )
    {
      this->_p68FB8[4] = 0;
      this->_d68FD4 = -1;
      this->_d68FD0 = -1;
    }
  }
  else
  {
    if ( v5[100] )
      BYTE1(CEffectSystem::DestroyAllEffect()->m_pVertexBuffer) = 1;
    else
      BYTE1(CEffectSystem::DestroyAllEffect()->m_pVertexBuffer) = 0;
    if ( v5[92] )
      sub_506340((int)this);
    if ( v5[93] )
      this->InsertTaskToList();
    if ( v5[94] )
      this->SwapTask();
  }
}

// 0x00506260
int CCCTData::Save(int a2)
{
  int result; // eax
  int v4; // esi
  char *v5; // edx
  char *v6; // eax

  result = ((CCBStageCam *)this)->IsEditorCamValid(a2);
  if ( result > 0 )
  {
    v4 = result;
    v5 = (char *)&this->_p0000[200 * a2 + 410000];
    do
    {
      if ( *(_DWORD *)v5 == -1 )
        v6 = 0;
      else
        v6 = (char *)&this->_p0000[204 * *(_DWORD *)v5];
      v6[21] = 0;
      if ( *(_DWORD *)v5 == -1 )
        result = 0;
      else
        result = (int)&this->_p0000[204 * *(_DWORD *)v5];
      v5 += 4;
      --v4;
      *(_BYTE *)(result + 22) = 0;
    }
    while ( v4 );
  }
  return result;
}

// 0x005062D0
int CCCTData::Load(int a2)
{
  int d68FB4; // eax
  double v3; // st7
  double v4; // st6
  int v5; // ecx
  int v6; // edx
  int v8; // [esp+0h] [ebp-10h]
  int v9; // [esp+4h] [ebp-Ch]

  d68FB4 = this->_d68FB4;
  v3 = *(float *)(d68FB4 + 496);
  v4 = *(float *)(d68FB4 + 492);
  v8 = *(_DWORD *)(d68FB4 + 500);
  v5 = *(_DWORD *)(d68FB4 + 452);
  v9 = *(_DWORD *)(d68FB4 + 456);
  v6 = *(_DWORD *)(d68FB4 + 464);
  *(_DWORD *)(a2 + 8) = v8;
  *(_DWORD *)(a2 + 12) = v9;
  *(_DWORD *)(a2 + 16) = v5;
  *(float *)a2 = v4;
  *(_DWORD *)(a2 + 20) = v6;
  *(float *)(a2 + 4) = v3;
  return a2;
}

// 0x005075E0
void CCCTData::InsertTaskToList()
{
  int v1; // edx
  char *v2; // eax
  int v4; // ecx
  char *v5; // ebx
  double v6; // st7
  double f69014; // st7
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
  double f69038; // st7
  char v25; // cl
  unsigned int v26; // eax
  float *v27; // eax
  float v28; // edx
  float *v29; // eax
  float v30; // edx
  float *p_f69020; // esi
  unsigned __int8 v33; // c0
  unsigned __int8 v34; // c3
  float f68FF8; // [esp+1Ch] [ebp-80h]
  float v36; // [esp+20h] [ebp-7Ch]
  float v37; // [esp+24h] [ebp-78h]
  float v38; // [esp+28h] [ebp-74h]
  float f6903C; // [esp+2Ch] [ebp-70h]
  float v40; // [esp+2Ch] [ebp-70h]
  float f69040; // [esp+30h] [ebp-6Ch]
  float v42; // [esp+30h] [ebp-6Ch]
  float v43; // [esp+34h] [ebp-68h]
  float v44; // [esp+34h] [ebp-68h]
  float v45; // [esp+38h] [ebp-64h]
  float v46; // [esp+38h] [ebp-64h]
  float v47; // [esp+3Ch] [ebp-60h]
  float v48; // [esp+3Ch] [ebp-60h]
  float v49; // [esp+44h] [ebp-58h]
  float v50; // [esp+48h] [ebp-54h]
  gbQuaternion v51; // [esp+4Ch] [ebp-50h] BYREF
  _BYTE v52[64]; // [esp+5Ch] [ebp-40h] BYREF

  v1 = *(_DWORD *)&this->_p0000[200 * this->_d68FD0 + 410000 + 4 * this->_d68FD4];
  if ( v1 == -1 )
    v2 = 0;
  else
    v2 = (char *)&this->_p0000[204 * v1];
  if ( v2[89] && v2[91] )
  {
    if ( !v2[90] )
    {
      v4 = *(_DWORD *)&this->_p0000[200 * this->_d68FD0 + 410000 + 4 * this->_d68FD4];
      if ( v4 == -1 )
        v5 = 0;
      else
        v5 = (char *)&this->_p0000[204 * v4];
      if ( !v5[21] )
      {
        if ( !v5[88] )
          this->Load((int)(v5 + 32));
        if ( v5[96] )
          v6 = *(float *)(*(_DWORD *)this->_d68FB0 + 104);
        else
          v6 = *(float *)(*(_DWORD *)this->_d68FB0 + 80);
        *((float *)v5 + 6) = v6;
        qmemcpy(&this->_f69008, v5 + 32, 0x18u);
        if ( v5[97] )
        {
          if ( *((float *)v5 + 17) - this->_f69014 <= 0.0 )
          {
            f69014 = this->_f69014;
            if ( v9 )
              f69014 = f69014 - 6.2831855;
          }
          else
          {
            f69014 = this->_f69014 + 6.2831855;
          }
          this->_f69014 = f69014;
        }
        this->_f68FF8 = *((float *)v5 + 33);
        this->_f68FD8 = *((float *)v5 + 34);
        v5[21] = 1;
      }
      if ( v5[96] )
        v10 = *(float *)(*(_DWORD *)this->_d68FB0 + 104);
      else
        v10 = *(float *)(*(_DWORD *)this->_d68FB0 + 80);
      v11 = v10 - *((float *)v5 + 6);
      v36 = v11;
      f68FF8 = v11 * this->_f68FD8;
      if ( v36 >= (double)*((float *)v5 + 29) )
      {
        v12 = v36 - *((float *)v5 + 29);
        f68FF8 = v12 * *((float *)v5 + 31) * v12 * 0.5 + f68FF8;
      }
      if ( v36 >= (double)*((float *)v5 + 30) )
      {
        v13 = v36 - *((float *)v5 + 30);
        f68FF8 = (*((float *)v5 + 32) + *((float *)v5 + 31)) * v13 * v13 * 0.5 + f68FF8;
      }
      if ( v15 | v16 )
      {
        if ( f68FF8 < (double)this->_f68FF8 )
          f68FF8 = this->_f68FF8;
      }
      else if ( f68FF8 > (double)this->_f68FF8 )
      {
        f68FF8 = this->_f68FF8;
      }
      v17 = *((float *)v5 + 39) - *((float *)v5 + 36);
      v18 = f68FF8 / this->_f68FF8;
      memset(&v51, 0, 12);
      v51.w = 1.0;
      v37 = v17 * v18;
      ((gbMatrix4 *)v52)->gbMatrix4();
      v43 = *((float *)v5 + 35);
      v45 = *((float *)v5 + 36);
      v47 = *((float *)v5 + 37);
      v19 = *((float *)v5 + 8) - v43;
      v49 = *((float *)v5 + 9) - v45;
      v20 = *((float *)v5 + 10) - v47;
      this->_f6903C = v49;
      v50 = v20;
      this->_f69038 = v19;
      this->_f69040 = v50;
      ((gbQuaternion *)&v51)->SetYawPitchRoll(f68FF8, 0.0, 0.0);
      ((gbQuaternion *)&v51)->GetMatrix((struct gbMatrix4 *)v52);
      ((gbMatrix4 *)v52)->RotateIn((struct gbVec3D *)&this->_f69038);
      v21 = v43 + this->_f69038;
      v44 = 0.0;
      this->_f69038 = v21;
      v22 = v45 + this->_f6903C;
      v46 = 0.0;
      this->_f6903C = v22;
      v23 = v47 + this->_f69040;
      v48 = 0.0;
      this->_f69040 = v23;
      this->_f6903C = v37 + this->_f6903C;
      f69038 = this->_f69038;
      v38 = this->_f69038;
      f6903C = this->_f6903C;
      v25 = v5[102];
      f69040 = this->_f69040;
      if ( v25 || v5[101] )
      {
        v26 = *((_DWORD *)v5 + 26);
        if ( v26 > 0xA )
        {
          if ( v26 == -1 )
          {
            v29 = (float *)*(float **)(this->_d68FB0 + 20);
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
          v27 = (float *)*(float **)(this->_d68FB0 + 4 * v26 + 24);
          v28 = v27[1646];
          v27 += 1646;
          v44 = v28;
          v46 = v27[1];
          v48 = v27[2];
        }
      }
      if ( v25 )
      {
        v40 = f6903C + v46;
        v42 = f69040 + v48;
        f69038 = f69038 + v44 - *((float *)v5 + 46);
        v38 = f69038;
        f6903C = v40 - *((float *)v5 + 47);
        f69040 = v42 - *((float *)v5 + 48);
      }
      p_f69020 = (float *)&this->_f69020;
      if ( v5[101] )
      {
        this->_f69024 = f6903C;
        this->_f69028 = f69040;
        *p_f69020 = f69038;
        v38->CalcDist(f6903C);
      }
      else
      {
        *p_f69020 = this->_f69008;
        this->_f69024 = this->_f6900C;
        this->_f69028 = this->_f69010;
        this->_f6902C = this->_f69014;
        this->_f69030 = this->_f69018;
        this->_f69034 = this->_f6901C;
        this->_f69024 = f6903C;
        *p_f69020 = f69038;
        this->_f69028 = f69040;
      }
      ((CCCTData *)this->_d68FB4)->UpdateCamera((int)&this->_f69020);
      ((CameraCtrl *)this->_d68FB4)->SetAsCurrent(3);
      if ( v33 | v34 )
      {
        if ( f68FF8 <= (double)this->_f68FF8 )
        {
          *((float *)v5 + 7) = v36;
          v5[22] = 1;
        }
      }
      else if ( f68FF8 >= (double)this->_f68FF8 )
      {
        *((float *)v5 + 7) = v36;
        v5[22] = 1;
      }
    }
  }
  else
  {
    nullsub_3(this);
  }
}

// 0x00507B20
void CCCTData::SwapTask()
{
  int v2; // ecx
  char *v3; // ebx
  float *v4; // edx
  int d68FD4; // eax
  int v6; // ecx
  char *v7; // eax
  double v8; // st7
  float v9; // ecx
  double v10; // st7
  float v11; // ecx
  int v12; // ecx
  double v13; // st7
  double f69014; // st7
  char v16; // c0
  int d68FB0; // edx
  double v18; // st7
  int v19; // eax
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st6
  double v24; // st6
  double f69038; // st7
  char v26; // cl
  unsigned int v27; // eax
  float *v28; // eax
  float v29; // edx
  float *v30; // eax
  float v31; // edx
  double v32; // st6
  double v33; // st5
  float v34; // [esp+10h] [ebp-48h]
  float v35; // [esp+14h] [ebp-44h]
  float v36; // [esp+14h] [ebp-44h]
  float v37; // [esp+14h] [ebp-44h]
  float v38; // [esp+18h] [ebp-40h]
  float v39; // [esp+1Ch] [ebp-3Ch]
  float v40; // [esp+20h] [ebp-38h]
  float v41; // [esp+20h] [ebp-38h]
  float v42; // [esp+20h] [ebp-38h]
  float v43; // [esp+20h] [ebp-38h]
  float v44; // [esp+20h] [ebp-38h]
  float v45; // [esp+24h] [ebp-34h]
  float v46; // [esp+24h] [ebp-34h]
  float v47; // [esp+24h] [ebp-34h]
  float v48; // [esp+24h] [ebp-34h]
  float v49; // [esp+24h] [ebp-34h]
  float v50; // [esp+28h] [ebp-30h]
  float v51; // [esp+2Ch] [ebp-2Ch]
  float v52; // [esp+2Ch] [ebp-2Ch]
  float v53; // [esp+2Ch] [ebp-2Ch]
  float v54; // [esp+2Ch] [ebp-2Ch]
  float v55; // [esp+2Ch] [ebp-2Ch]
  float v56; // [esp+2Ch] [ebp-2Ch]
  float v57; // [esp+2Ch] [ebp-2Ch]
  float v58; // [esp+30h] [ebp-28h]
  float v59; // [esp+30h] [ebp-28h]
  float v60; // [esp+30h] [ebp-28h]
  float v61; // [esp+30h] [ebp-28h]
  float v62; // [esp+30h] [ebp-28h]
  float v63; // [esp+30h] [ebp-28h]
  float v64; // [esp+30h] [ebp-28h]
  float v65; // [esp+34h] [ebp-24h]
  float v66; // [esp+34h] [ebp-24h]
  float v67; // [esp+38h] [ebp-20h]
  float v68; // [esp+38h] [ebp-20h]
  float v69; // [esp+3Ch] [ebp-1Ch]
  float v70; // [esp+3Ch] [ebp-1Ch]
  float v71; // [esp+44h] [ebp-14h]
  float v72; // [esp+48h] [ebp-10h]
  float v73; // [esp+4Ch] [ebp-Ch]
  float v74; // [esp+50h] [ebp-8h]
  float v75; // [esp+54h] [ebp-4h]

  v2 = *(_DWORD *)&this->_p0000[200 * this->_d68FD0 + 410000 + 4 * this->_d68FD4];
  if ( v2 == -1 )
    v3 = 0;
  else
    v3 = (char *)&this->_p0000[204 * v2];
  if ( !v3[21] )
  {
    if ( !v3[88] )
      this->Load((int)(v3 + 32));
    v4 = (float *)(v3 + 32);
    qmemcpy(&this->_f69008, v3 + 32, 0x18u);
    this->_f69038 = *((float *)v3 + 8);
    this->_f6903C = *((float *)v3 + 9);
    d68FD4 = this->_d68FD4;
    this->_f69040 = *((float *)v3 + 10);
    if ( !d68FD4
      || d68FD4 > 0
      && ((v6 = *(_DWORD *)&this->_p0000[200 * this->_d68FD0 + 409996 + 4 * d68FD4], v6 == -1)
        ? (v7 = 0)
        : (v7 = &this->_p0000[204 * v6]),
          !v7[94]) )
    {
      v8 = *((float *)v3 + 14) - *v4;
      v51 = *((float *)v3 + 15) - *((float *)v3 + 9);
      v58 = *((float *)v3 + 16) - *((float *)v3 + 10);
      if ( *((float *)v3 + 7) <= 0.0 )
      {
        v9 = *((float *)v3 + 16) - *((float *)v3 + 10);
        this->_f68FE0 = v8;
        this->_f68FE4 = v51;
      }
      else
      {
        v35 = 1.0 / *((float *)v3 + 7);
        v40 = v51 * v35;
        this->_f68FE4 = v40;
        v45 = v58 * v35;
        v9 = v45;
        this->_f68FE0 = v8 * v35;
      }
      this->_f68FE8 = v9;
    }
    v10 = *((float *)v3 + 14) - *v4;
    v52 = *((float *)v3 + 15) - *((float *)v3 + 9);
    v59 = *((float *)v3 + 16) - *((float *)v3 + 10);
    if ( *((float *)v3 + 7) <= 0.0 )
    {
      v11 = *((float *)v3 + 16) - *((float *)v3 + 10);
      this->_f68FEC = v10;
      this->_f68FF0 = v52;
    }
    else
    {
      v36 = 1.0 / *((float *)v3 + 7);
      v41 = v52 * v36;
      this->_f68FF0 = v41;
      v46 = v59 * v36;
      v11 = v46;
      this->_f68FEC = v10 * v36;
    }
    this->_f68FF4 = v11;
    v12 = *(_DWORD *)this->_d68FB0;
    if ( v3[96] )
      v13 = *(float *)(v12 + 104);
    else
      v13 = *(float *)(v12 + 80);
    *((float *)v3 + 6) = v13;
    qmemcpy(&this->_f69020, v4, 0x18u);
    if ( v3[97] )
    {
      if ( *((float *)v3 + 17) - this->_f69014 <= 0.0 )
      {
        f69014 = this->_f69014;
        if ( v16 )
          f69014 = f69014 - 6.2831855;
      }
      else
      {
        f69014 = this->_f69014 + 6.2831855;
      }
      this->_f69014 = f69014;
    }
    v3[21] = 1;
  }
  if ( v3[96] )
  {
    d68FB0 = this->_d68FB0;
    v37 = *(double *)(*(_DWORD *)d68FB0 + 88);
    v18 = *(float *)(*(_DWORD *)d68FB0 + 104);
  }
  else
  {
    v19 = *(_DWORD *)this->_d68FB0;
    v37 = *(double *)(v19 + 64);
    v18 = *(float *)(v19 + 80);
  }
  if ( *((float *)v3 + 7) > 0.0 )
    v34 = (v18 - *((float *)v3 + 6)) / (*((float *)v3 + 43) + *((float *)v3 + 7));
  else
    v34 = 1.0;
  v38 = ((gbVec3D *)&this->_f68FE0)->Length();
  v53 = v37 * this->_f68FF0;
  v60 = v37 * this->_f68FF4;
  v20 = v37 * this->_f68FEC + this->_f68FE0;
  v42 = v53 + this->_f68FE4;
  v21 = v60 + this->_f68FE8;
  this->_f68FE4 = v42;
  v47 = v21;
  this->_f68FE0 = v20;
  this->_f68FE8 = v47;
  ((gbVec3D *)&this->_f68FE0)->Normalize();
  v50 = 0.0;
  this->_f68FE0 = v38 * this->_f68FE0;
  this->_f68FE4 = v38 * this->_f68FE4;
  this->_f68FE8 = v38 * this->_f68FE8;
  v54 = v37 * this->_f68FE4;
  v61 = v37 * this->_f68FE8;
  v22 = v37 * this->_f68FE0 + this->_f69038;
  v23 = v54 + this->_f6903C;
  v55 = 0.0;
  v43 = v23;
  v24 = v61 + this->_f69040;
  v62 = 0.0;
  this->_f6903C = v43;
  v48 = v24;
  this->_f69038 = v22;
  this->_f69040 = v48;
  f69038 = this->_f69038;
  v26 = v3[102];
  v39 = this->_f69038;
  if ( v26 || v3[101] )
  {
    v27 = *((_DWORD *)v3 + 26);
    if ( v27 > 0xA )
    {
      if ( v27 == -1 )
      {
        v30 = (float *)*(float **)(this->_d68FB0 + 20);
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
      v28 = (float *)*(float **)(this->_d68FB0 + 4 * v27 + 24);
      v29 = v28[1646];
      v28 += 1646;
      v50 = v29;
      v55 = v28[1];
      v62 = v28[2];
    }
  }
  if ( v26 )
  {
    v44 = v55 + v43;
    v49 = v62 + v48;
    f69038 = f69038 + v50 - *((float *)v3 + 46);
    v39 = f69038;
    v43 = v44 - *((float *)v3 + 47);
    v48 = v49 - *((float *)v3 + 48);
  }
  if ( v3[101] )
  {
    this->_f69024 = v43;
    this->_f69028 = v48;
    this->_f69020 = f69038;
    v39->CalcDist(v43);
  }
  else
  {
    v56 = *((float *)v3 + 15) - this->_f6900C;
    v63 = *((float *)v3 + 16) - this->_f69010;
    v65 = *((float *)v3 + 17) - this->_f69014;
    v67 = *((float *)v3 + 18) - this->_f69018;
    v69 = *((float *)v3 + 19) - this->_f6901C;
    v71 = v56 * v34;
    v72 = v63 * v34;
    v73 = v65 * v34;
    v74 = v67 * v34;
    v75 = v69 * v34;
    v32 = (*((float *)v3 + 14) - this->_f69008) * v34 + this->_f69008;
    v57 = v71 + this->_f6900C;
    v64 = v72 + this->_f69010;
    v66 = v73 + this->_f69014;
    v68 = v74 + this->_f69018;
    v33 = v75 + this->_f6901C;
    this->_f69024 = v57;
    this->_f69028 = v64;
    this->_f6902C = v66;
    this->_f69030 = v68;
    v70 = v33;
    this->_f69020 = v32;
    this->_f69034 = v70;
    this->_f69020 = f69038;
    this->_f69024 = v43;
    this->_f69028 = v48;
  }
  ((CCCTData *)this->_d68FB4)->UpdateCamera((int)&this->_f69020);
  ((CameraCtrl *)this->_d68FB4)->SetAsCurrent(3);
  if ( v34 >= 1.0 )
    v3[22] = 1;
}

// 0x00508190
// attributes: thunk
int CCCTData::ClearList()
{
  return CCCTData::IsTaskValid();
}

// 0x005081A0
int CCCTData::IsTaskValid()
{
  *((_DWORD *)&g_bSceneLoaded + 366) = 1094713344;
  return 1094713344;
}

// 0x005081B0
// attributes: thunk
void CCCTData::GetTaskNumInList()
{
  CCCTData::GetFreeSpaceInPool();
}

// 0x005081C0
void CCCTData::GetFreeSpaceInPool()
{
  *((float *)&g_bSceneLoaded + 365) = 12.0 + 12.0;
}
