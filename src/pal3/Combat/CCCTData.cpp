#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCCTData.h"
#include "pal3/gen/CCBStageCam.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int sub_41CA30(...);
int sub_506340(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Co_6[];
extern char aUiCombatPointe[];
extern unsigned char byte_17AAEE0;
extern unsigned char byte_17AAF21;
extern unsigned char byte_17AAF64;
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
extern float flt_17AAD48;
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

  this->m_Pool[1453].bEndCamValid = *a2;
  this->m_Pool[1453].bTimeValid = a2[1];
  this->m_Pool[1453].bSpeedValid = a2[2];
  this->m_Pool[1453].bLineMove = *a3;
  this->m_Pool[1453].bCircleMove = a3[1];
  result = a3[2];
  this->m_Pool[1453].bMechanicsMove = result;
  return result;
}

// 0x00505930
CCCTData::~CCCTData(int _this)
{
  __int32 *v2; // ebp
  struct gbRenderEffect *v3; // ebx
  float *v4; // esi
  _BYTE *v5; // esi
  __int32 *p_Green; // esi
  double v7; // st7
  float v8; // edx
  __int32 v9; // eax
  int v10; // ecx
  double v11; // st7
  __int32 v12; // edx
  __int32 v13; // eax
  int v14; // ecx
  __int32 v15; // edx
  __int32 v16; // eax
  __int32 v17; // ecx
  __int32 v18; // edx
  float *v19; // edi
  double v20; // st7
  double v21; // st6
  __int32 v22; // edx
  double v23; // st6
  gbColorQuad v24; // [esp+40h] [ebp-A8h] BYREF
  __int32 v25; // [esp+64h] [ebp-84h]
  __int32 v26; // [esp+68h] [ebp-80h]
  int v27; // [esp+6Ch] [ebp-7Ch]
  int v28; // [esp+70h] [ebp-78h]
  int v29; // [esp+74h] [ebp-74h]
  int v30; // [esp+78h] [ebp-70h]
  struct gbColorQuad v31; // [esp+7Ch] [ebp-6Ch] BYREF
  __int32 v32; // [esp+94h] [ebp-54h]
  int ColorQuadFmt; // [esp+98h] [ebp-50h]
  _BYTE v34[64]; // [esp+9Ch] [ebp-4Ch] BYREF
  float v35; // [esp+DCh] [ebp-Ch]
  float v36; // [esp+E0h] [ebp-8h]
  float v37; // [esp+E4h] [ebp-4h]

  if ( *(_BYTE *)(this + 430252) )
  {
    ((gbMatrix4 *)v34)->gbMatrix4();
    ((gbGeomNode *)*(gbGeomNode **)(this + 430224))->GetTotalOBBox((struct gbOBBox *)v34);
    v2 = (__int32 *)(this + 430228);
    ((gbMatrix4 *)v34)->RightTranslate((struct gbVec3D *)(this + 430228));
    v3 = ((gbEffectMgr *)*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200))->NewTrivalEffect(3);
    v31.Blue = (__int32)((gbVertPoolMgr *)*(gbVertPoolMgr **)(g_Input.KeyInfo[177].Data + 196))->GetDynVertBuf(0x15u);
    if ( (byte_17AAEE0 & 1) == 0 )
    {
      v4 = (float *)&flt_17AAD48;
      byte_17AAEE0 |= 1u;
      v27 = 6;
      do
      {
        ArraySort((int)v4, 12, 4, gbVec3D::`default constructor closure');
        v4 += 17;
        --v27;
      }
      while ( *(float *)&v27 != 0.0 );
      atexit(nullsub_31);
    }
    v35 = v35 + 2.0;
    v36 = v36 + 2.0;
    v37 = v37 + 2.0;
    *(float *)&v30 = v36 * 0.5;
    dword_17AAD4C = v30;
    *(float *)&v27 = v37 * 0.5;
    flt_17AAD48 = v35 * -0.5;
    dword_17AAD50 = v27;
    dword_17AAD58 = v30;
    flt_17AAD54 = v35 * 0.5;
    dword_17AAD5C = v27;
    dword_17AAD68 = v27;
    *(float *)&v28 = v36 * -0.5;
    flt_17AAD60 = flt_17AAD54;
    dword_17AAD64 = v28;
    flt_17AAD6C = flt_17AAD48;
    dword_17AAD70 = v28;
    *(float *)&v29 = v37 * -0.5;
    dword_17AAD74 = v27;
    flt_17AAD8C = flt_17AAD48;
    dword_17AAD90 = v30;
    dword_17AAD94 = v29;
    flt_17AAD98 = flt_17AAD54;
    dword_17AAD9C = v30;
    dword_17AADA0 = v29;
    flt_17AADA4 = flt_17AAD54;
    flt_17AADB0 = flt_17AAD48;
    flt_17AADD0 = flt_17AAD48;
    dword_17AADA8 = v28;
    dword_17AADAC = v29;
    dword_17AADB4 = v28;
    dword_17AADB8 = v29;
    flt_17AADDC = flt_17AAD48;
    dword_17AADD4 = v30;
    dword_17AADD8 = v27;
    flt_17AADE8 = flt_17AAD48;
    dword_17AADE0 = v30;
    dword_17AADE4 = v29;
    flt_17AADF4 = flt_17AAD48;
    dword_17AADEC = v28;
    dword_17AADF0 = v29;
    dword_17AADF8 = v28;
    flt_17AAE14 = flt_17AAD54;
    dword_17AADFC = v27;
    dword_17AAE18 = v30;
    dword_17AAE1C = v27;
    flt_17AAE20 = flt_17AAD54;
    dword_17AAE24 = v30;
    dword_17AAE28 = v29;
    flt_17AAE2C = flt_17AAD54;
    dword_17AAE30 = v28;
    flt_17AAE38 = flt_17AAD54;
    flt_17AAE58 = flt_17AAD48;
    dword_17AAE34 = v29;
    dword_17AAE3C = v28;
    flt_17AAE64 = flt_17AAD54;
    dword_17AAE40 = v27;
    dword_17AAE5C = v30;
    dword_17AAE60 = v29;
    flt_17AAE70 = flt_17AAD54;
    dword_17AAE68 = v30;
    dword_17AAE6C = v29;
    dword_17AAE74 = v30;
    flt_17AAE7C = flt_17AAD48;
    dword_17AAE78 = v27;
    dword_17AAE80 = v30;
    flt_17AAE9C = flt_17AAD48;
    dword_17AAE84 = v27;
    dword_17AAEA0 = v28;
    dword_17AAEA4 = v29;
    flt_17AAEA8 = flt_17AAD54;
    flt_17AAEB4 = flt_17AAD54;
    dword_17AAEAC = v28;
    dword_17AAEB0 = v29;
    flt_17AAEC0 = flt_17AAD48;
    dword_17AAEB8 = v28;
    dword_17AAEBC = v27;
    v25 = v28;
    v26 = v27;
    dword_17AAEC4 = v28;
    dword_17AAEC8 = v27;
    v5 = (_BYTE *)&unk_17AAD89;
    do
    {
      v5[1] = -1;
      *v5 = -1;
      v24.Red = 4;
      *(v5 - 1) = 10;
      v24.Green = (__int32)(v5 - 65);
      v5[2] = -101;
      ((gbMatrix4 *)v34)->Transform((struct gbVec3D *)v24.Green, v24.Red);
      v5 += 68;
    }
    while ( (int)v5 < (int)byte_17AAF21 );
    ((struct gbGeomQuad *)&flt_17AAD48)->RenderGeomQuad(6, v3, 0);
    p_Green = (__int32 *)&v31.Green;
    v27 = 2;
    do
    {
      ((void (*)(__int32 *))gbVec3D::`default constructor closure')(p_Green);
      p_Green += 3;
      --v27;
    }
    while ( *(float *)&v27 != 0.0 );
    v7 = *(float *)v2;
    v8 = *(float *)v2;
    v9 = *(_DWORD *)(this + 430232);
    v26 = *(__int32 *)(this + 430236);
    *(float *)&v31.Color = v8;
    *(float *)&v31.Green = v7;
    v31.Alpha = v26;
    v10 = *(_DWORD *)(this + 430236);
    v24.Red = (__int32)v3;
    v24.Green = 2;
    v24.Blue = (__int32)&v31.Green;
    v32 = v9;
    v24.ColorQuadFmt = v10;
    ColorQuadFmt = v10;
    v31.ColorQuadFmt = 1358954495;
    v31.Red = 0;
    ((gbColorQuad *)&v24)->gbColorQuad(&v31);
    ((gbDynVertBuf *)v31.Color)->RenderLineStrip();
    v11 = *(float *)(this + 430240);
    v12 = *(_DWORD *)(this + 430240);
    v13 = *(_DWORD *)(this + 430244);
    v26 = *(__int32 *)(this + 430248);
    v31.Color = v12;
    *(float *)&v31.Green = v11;
    v31.Alpha = v26;
    v14 = *(_DWORD *)(this + 430248);
    v24.Red = (__int32)v3;
    v24.Green = 2;
    v24.Blue = (__int32)&v31.Green;
    v32 = v13;
    v24.ColorQuadFmt = v14;
    ColorQuadFmt = v14;
    v31.Red = 0;
    ((gbColorQuad *)&v24)->gbColorQuad(&v31);
    ((gbDynVertBuf *)v31.Color)->RenderLineStrip();
    v15 = *(_DWORD *)(this + 430232);
    v16 = *(_DWORD *)(this + 430236);
    v31.Green = *v2;
    v17 = *(_DWORD *)(this + 430240);
    v31.Red = v15;
    v18 = *(_DWORD *)(this + 430244);
    v31.Color = v17;
    v24.Red = (__int32)v3;
    v24.Green = 2;
    v24.Blue = (__int32)&v31.Green;
    v32 = v18;
    v24.ColorQuadFmt = (int)&v31.Green;
    v31.Alpha = v16;
    ColorQuadFmt = *(_DWORD *)(this + 430248);
    ((gbColorQuad *)&v24)->gbColorQuad(&v31);
    ((gbDynVertBuf *)v31.Color)->RenderLineStrip();
    v19 = (float *)*(float **)(this + 430004);
    v20 = v19[123] + 1.0;
    v21 = v19[124] + 1.0;
    v22 = *v2;
    v24.Red = (__int32)v3;
    v24.Green = 2;
    *(float *)&v25 = v21;
    v23 = v19[125];
    v31.Color = v22;
    v31.Red = v25;
    v32 = v2[1];
    *(float *)&v26 = v23 + 1.0;
    v24.Blue = (__int32)&v31.Green;
    *(float *)&v31.Green = v20;
    v31.Alpha = v26;
    v24.ColorQuadFmt = v2[2];
    ColorQuadFmt = v24.ColorQuadFmt;
    ((gbColorQuad *)&v24)->gbColorQuad(&v31);
    ((gbDynVertBuf *)v31.Color)->RenderLineStrip();
    v3->Release();
  }
}

// 0x00506020
bool CCCTData::Create(int _this, float *a2)
{
  int v3; // eax
  CameraCtrl *v4; // ecx
  float pPos[2]; // [esp+8h] [ebp-90h] BYREF
  struct gbVec3D v7; // [esp+10h] [ebp-88h] BYREF
  gbRay v8; // [esp+1Ch] [ebp-7Ch] BYREF
  _BYTE v9[76]; // [esp+34h] [ebp-64h] BYREF
  _BYTE pTarget[24]; // [esp+80h] [ebp-18h] BYREF

  ((gbMatrix4 *)v9)->gbMatrix4();
  ((gbGeomNode *)*(gbGeomNode **)(this + 430224))->GetTotalOBBox((struct gbOBBox *)v9);
  v7.x = *a2;
  v7.y = a2[1];
  v7.z = a2[2];
  ((gbMatrix4 *)v9)->RightTranslate(&v7);
  v3 = *(_DWORD *)(this + 430000);
  pPos[0] = *(float *)(v3 + 80);
  v4 = (CameraCtrl *)*(CameraCtrl **)(this + 430004);
  pPos[1] = *(float *)(v3 + 84);
  qmemcpy(&v8, v4->GetViewTarget(pTarget, pPos), sizeof(v8));
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

  v2 = (gbGeomNode *)((operator *)0x118u)->new();
  v3 = v2;
  v8 = 0;
  if ( v2 )
  {
    v2->gbGeomNode();
    v3->next = (gbChain1DNode *)&off_56A66C;
    v4 = v3;
  }
  else
  {
    v4 = 0;
  }
  v8 = -1;
  this->m_Pool[1453].bStartCamValid = (__int32)v4;
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
void CCCTData::Init(int _this)
{
  int v2; // edx
  int v3; // ebp
  int v4; // ecx
  _BYTE *v5; // edi

  v2 = *(_DWORD *)(this + 430032);
  v3 = *(_DWORD *)(this + 430036);
  v4 = *(_DWORD *)(this + 4 * (v3 + 10 * (5 * v2 + 10250)));
  if ( v4 == -1 )
    v5 = 0;
  else
    v5 = (_BYTE *)(this + 204 * v4);
  if ( v5[22] )
  {
    *(_DWORD *)(this + 430036) = v3 + 1;
    if ( *(_DWORD *)(this + 430036) >= ((CCBStageCam *)this)->IsEditorCamValid(v2) )
    {
      *(_BYTE *)(this + 430012) = 0;
      *(_DWORD *)(this + 430036) = -1;
      *(_DWORD *)(this + 430032) = -1;
    }
  }
  else
  {
    if ( v5[100] )
      *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) = 1;
    else
      *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) = 0;
    if ( v5[92] )
      sub_506340(this);
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
  float *v5; // edx
  char *v6; // eax

  result = ((CCBStageCam *)this)->IsEditorCamValid(a2);
  if ( result > 0 )
  {
    v4 = result;
    v5 = (float *)&this->m_Pool[1385].StartPos.fFromY + 50 * a2;
    do
    {
      if ( *(_DWORD *)v5 == -1 )
        v6 = 0;
      else
        v6 = (char *)this + 204 * *(_DWORD *)v5;
      v6[21] = 0;
      if ( *(_DWORD *)v5 == -1 )
        result = 0;
      else
        result = (int)this + 204 * *(_DWORD *)v5;
      ++v5;
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
  float fAccelerationTime2; // eax
  double v3; // st7
  double v4; // st6
  int v5; // ecx
  int v6; // edx
  int v8; // [esp+0h] [ebp-10h]
  int v9; // [esp+4h] [ebp-Ch]

  fAccelerationTime2 = this->m_Pool[1452].fAccelerationTime2;
  v3 = *(float *)(LODWORD(fAccelerationTime2) + 496);
  v4 = *(float *)(LODWORD(fAccelerationTime2) + 492);
  v8 = *(_DWORD *)(LODWORD(fAccelerationTime2) + 500);
  v5 = *(_DWORD *)(LODWORD(fAccelerationTime2) + 452);
  v9 = *(_DWORD *)(LODWORD(fAccelerationTime2) + 456);
  v6 = *(_DWORD *)(LODWORD(fAccelerationTime2) + 464);
  *(_DWORD *)(a2 + 8) = v8;
  *(_DWORD *)(a2 + 12) = v9;
  *(_DWORD *)(a2 + 16) = v5;
  *(float *)a2 = v4;
  *(_DWORD *)(a2 + 20) = v6;
  *(float *)(a2 + 4) = v3;
  return a2;
}

// 0x005075E0
void CCCTData::InsertTaskToList(int _this)
{
  int v1; // edx
  _BYTE *v2; // eax
  int v4; // ecx
  int v5; // ebx
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
  char v25; // cl
  unsigned int v26; // eax
  float *v27; // eax
  float v28; // edx
  float *v29; // eax
  float v30; // edx
  float *v31; // esi
  unsigned __int8 v33; // c0
  unsigned __int8 v34; // c3
  float v35; // [esp+1Ch] [ebp-80h]
  float v36; // [esp+20h] [ebp-7Ch]
  float v37; // [esp+24h] [ebp-78h]
  float v38; // [esp+28h] [ebp-74h]
  float v39; // [esp+2Ch] [ebp-70h]
  float v40; // [esp+2Ch] [ebp-70h]
  float v41; // [esp+30h] [ebp-6Ch]
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

  v1 = *(_DWORD *)(this + 4 * (*(_DWORD *)(this + 430036) + 10 * (5 * *(_DWORD *)(this + 430032) + 10250)));
  if ( v1 == -1 )
    v2 = 0;
  else
    v2 = (_BYTE *)(this + 204 * v1);
  if ( v2[89] && v2[91] )
  {
    if ( !v2[90] )
    {
      v4 = *(_DWORD *)(this + 4 * (*(_DWORD *)(this + 430036) + 10 * (5 * *(_DWORD *)(this + 430032) + 10250)));
      if ( v4 == -1 )
        v5 = 0;
      else
        v5 = this + 204 * v4;
      if ( !*(_BYTE *)(v5 + 21) )
      {
        if ( !*(_BYTE *)(v5 + 88) )
          ((CCCTData *)this)->Load(v5 + 32);
        if ( *(_BYTE *)(v5 + 96) )
          v6 = *(float *)(**(_DWORD **)(this + 430000) + 104);
        else
          v6 = *(float *)(**(_DWORD **)(this + 430000) + 80);
        *(float *)(v5 + 24) = v6;
        qmemcpy((void *)(this + 430088), (const void *)(v5 + 32), 0x18u);
        if ( *(_BYTE *)(v5 + 97) )
        {
          if ( *(float *)(v5 + 68) - *(float *)(this + 430100) <= 0.0 )
          {
            v7 = *(float *)(this + 430100);
            if ( v9 )
              v7 = v7 - 6.2831855;
          }
          else
          {
            v7 = *(float *)(this + 430100) + 6.2831855;
          }
          *(float *)(this + 430100) = v7;
        }
        *(_DWORD *)(this + 430072) = *(_DWORD *)(v5 + 132);
        *(_DWORD *)(this + 430040) = *(_DWORD *)(v5 + 136);
        *(_BYTE *)(v5 + 21) = 1;
      }
      if ( *(_BYTE *)(v5 + 96) )
        v10 = *(float *)(**(_DWORD **)(this + 430000) + 104);
      else
        v10 = *(float *)(**(_DWORD **)(this + 430000) + 80);
      v11 = v10 - *(float *)(v5 + 24);
      v36 = v11;
      v35 = v11 * *(float *)(this + 430040);
      if ( v36 >= (double)*(float *)(v5 + 116) )
      {
        v12 = v36 - *(float *)(v5 + 116);
        v35 = v12 * *(float *)(v5 + 124) * v12 * 0.5 + v35;
      }
      if ( v36 >= (double)*(float *)(v5 + 120) )
      {
        v13 = v36 - *(float *)(v5 + 120);
        v35 = (*(float *)(v5 + 128) + *(float *)(v5 + 124)) * v13 * v13 * 0.5 + v35;
      }
      if ( v15 | v16 )
      {
        if ( v35 < (double)*(float *)(this + 430072) )
          v35 = *(float *)(this + 430072);
      }
      else if ( v35 > (double)*(float *)(this + 430072) )
      {
        v35 = *(float *)(this + 430072);
      }
      v17 = *(float *)(v5 + 156) - *(float *)(v5 + 144);
      v18 = v35 / *(float *)(this + 430072);
      memset(&v51, 0, 12);
      v51.w = 1.0;
      v37 = v17 * v18;
      ((gbMatrix4 *)v52)->gbMatrix4();
      v43 = *(float *)(v5 + 140);
      v45 = *(float *)(v5 + 144);
      v47 = *(float *)(v5 + 148);
      v19 = *(float *)(v5 + 32) - v43;
      v49 = *(float *)(v5 + 36) - v45;
      v20 = *(float *)(v5 + 40) - v47;
      *(float *)(this + 430140) = v49;
      v50 = v20;
      *(float *)(this + 430136) = v19;
      *(float *)(this + 430144) = v50;
      ((gbQuaternion *)&v51)->SetYawPitchRoll(v35, 0.0, 0.0);
      ((gbQuaternion *)&v51)->GetMatrix((struct gbMatrix4 *)v52);
      ((gbMatrix4 *)v52)->RotateIn((struct gbVec3D *)(this + 430136));
      v21 = v43 + *(float *)(this + 430136);
      v44 = 0.0;
      *(float *)(this + 430136) = v21;
      v22 = v45 + *(float *)(this + 430140);
      v46 = 0.0;
      *(float *)(this + 430140) = v22;
      v23 = v47 + *(float *)(this + 430144);
      v48 = 0.0;
      *(float *)(this + 430144) = v23;
      *(float *)(this + 430140) = v37 + *(float *)(this + 430140);
      v24 = *(float *)(this + 430136);
      v38 = *(float *)(this + 430136);
      v39 = *(float *)(this + 430140);
      v25 = *(_BYTE *)(v5 + 102);
      v41 = *(float *)(this + 430144);
      if ( v25 || *(_BYTE *)(v5 + 101) )
      {
        v26 = *(_DWORD *)(v5 + 104);
        if ( v26 > 0xA )
        {
          if ( v26 == -1 )
          {
            v29 = (float *)*(float **)(*(_DWORD *)(this + 430000) + 20);
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
          v27 = (float *)*(float **)(*(_DWORD *)(this + 430000) + 4 * v26 + 24);
          v28 = v27[1646];
          v27 += 1646;
          v44 = v28;
          v46 = v27[1];
          v48 = v27[2];
        }
      }
      if ( v25 )
      {
        v40 = v39 + v46;
        v42 = v41 + v48;
        v24 = v24 + v44 - *(float *)(v5 + 184);
        v38 = v24;
        v39 = v40 - *(float *)(v5 + 188);
        v41 = v42 - *(float *)(v5 + 192);
      }
      v31 = (float *)(this + 430112);
      if ( *(_BYTE *)(v5 + 101) )
      {
        *(float *)(this + 430116) = v39;
        *(float *)(this + 430120) = v41;
        *v31 = v24;
        v38->CalcDist(v39);
      }
      else
      {
        * v31 = (*)*(float *)(this + 430088);
        *(_DWORD *)(this + 430116) = *(_DWORD *)(this + 430092);
        *(_DWORD *)(this + 430120) = *(_DWORD *)(this + 430096);
        *(_DWORD *)(this + 430124) = *(_DWORD *)(this + 430100);
        *(_DWORD *)(this + 430128) = *(_DWORD *)(this + 430104);
        *(_DWORD *)(this + 430132) = *(_DWORD *)(this + 430108);
        *(float *)(this + 430116) = v39;
        *v31 = v24;
        *(float *)(this + 430120) = v41;
      }
      ((CCCTData *)*(CCCTData **)(this + 430004))->UpdateCamera(this + 430112);
      ((CameraCtrl *)*(CameraCtrl **)(this + 430004))->SetAsCurrent(3);
      if ( v33 | v34 )
      {
        if ( v35 <= (double)*(float *)(this + 430072) )
        {
          *(float *)(v5 + 28) = v36;
          *(_BYTE *)(v5 + 22) = 1;
        }
      }
      else if ( v35 >= (double)*(float *)(this + 430072) )
      {
        *(float *)(v5 + 28) = v36;
        *(_BYTE *)(v5 + 22) = 1;
      }
    }
  }
  else
  {
    nullsub_3((void *)this);
  }
}

// 0x00507B20
void CCCTData::SwapTask(int _this)
{
  int v2; // ecx
  int v3; // ebx
  float *v4; // edx
  int v5; // eax
  int v6; // ecx
  int v7; // eax
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

  v2 = *(_DWORD *)(this + 4 * (*(_DWORD *)(this + 430036) + 10 * (5 * *(_DWORD *)(this + 430032) + 10250)));
  if ( v2 == -1 )
    v3 = 0;
  else
    v3 = this + 204 * v2;
  if ( !*(_BYTE *)(v3 + 21) )
  {
    if ( !*(_BYTE *)(v3 + 88) )
      ((CCCTData *)this)->Load(v3 + 32);
    v4 = (float *)(v3 + 32);
    qmemcpy((void *)(this + 430088), (const void *)(v3 + 32), 0x18u);
    *(_DWORD *)(this + 430136) = *(_DWORD *)(v3 + 32);
    *(_DWORD *)(this + 430140) = *(_DWORD *)(v3 + 36);
    v5 = *(_DWORD *)(this + 430036);
    *(_DWORD *)(this + 430144) = *(_DWORD *)(v3 + 40);
    if ( !v5
      || v5 > 0
      && ((v6 = *(_DWORD *)(this + 4 * (v5 + 10 * (5 * *(_DWORD *)(this + 430032) + 10250) - 1)), v6 == -1)
        ? (v7 = 0)
        : (v7 = this + 204 * v6),
          !*(_BYTE *)(v7 + 94)) )
    {
      v8 = *(float *)(v3 + 56) - *v4;
      v51 = *(float *)(v3 + 60) - *(float *)(v3 + 36);
      v58 = *(float *)(v3 + 64) - *(float *)(v3 + 40);
      if ( *(float *)(v3 + 28) <= 0.0 )
      {
        v9 = *(float *)(v3 + 64) - *(float *)(v3 + 40);
        *(float *)(this + 430048) = v8;
        *(float *)(this + 430052) = v51;
      }
      else
      {
        v35 = 1.0 / *(float *)(v3 + 28);
        v40 = v51 * v35;
        *(float *)(this + 430052) = v40;
        v45 = v58 * v35;
        v9 = v45;
        *(float *)(this + 430048) = v8 * v35;
      }
      *(float *)(this + 430056) = v9;
    }
    v10 = *(float *)(v3 + 56) - *v4;
    v52 = *(float *)(v3 + 60) - *(float *)(v3 + 36);
    v59 = *(float *)(v3 + 64) - *(float *)(v3 + 40);
    if ( *(float *)(v3 + 28) <= 0.0 )
    {
      v11 = *(float *)(v3 + 64) - *(float *)(v3 + 40);
      *(float *)(this + 430060) = v10;
      *(float *)(this + 430064) = v52;
    }
    else
    {
      v36 = 1.0 / *(float *)(v3 + 28);
      v41 = v52 * v36;
      *(float *)(this + 430064) = v41;
      v46 = v59 * v36;
      v11 = v46;
      *(float *)(this + 430060) = v10 * v36;
    }
    *(float *)(this + 430068) = v11;
    v12 = **(_DWORD **)(this + 430000);
    if ( *(_BYTE *)(v3 + 96) )
      v13 = *(float *)(v12 + 104);
    else
      v13 = *(float *)(v12 + 80);
    *(float *)(v3 + 24) = v13;
    qmemcpy((void *)(this + 430112), v4, 0x18u);
    if ( *(_BYTE *)(v3 + 97) )
    {
      if ( *(float *)(v3 + 68) - *(float *)(this + 430100) <= 0.0 )
      {
        v14 = *(float *)(this + 430100);
        if ( v16 )
          v14 = v14 - 6.2831855;
      }
      else
      {
        v14 = *(float *)(this + 430100) + 6.2831855;
      }
      *(float *)(this + 430100) = v14;
    }
    *(_BYTE *)(v3 + 21) = 1;
  }
  if ( *(_BYTE *)(v3 + 96) )
  {
    v17 = *(_DWORD *)(this + 430000);
    v37 = *(double *)(*(_DWORD *)v17 + 88);
    v18 = *(float *)(*(_DWORD *)v17 + 104);
  }
  else
  {
    v19 = **(_DWORD **)(this + 430000);
    v37 = *(double *)(v19 + 64);
    v18 = *(float *)(v19 + 80);
  }
  if ( *(float *)(v3 + 28) > 0.0 )
    v34 = (v18 - *(float *)(v3 + 24)) / (*(float *)(v3 + 172) + *(float *)(v3 + 28));
  else
    v34 = 1.0;
  v38 = ((gbVec3D *)(this + 430048))->Length();
  v53 = v37 * *(float *)(this + 430064);
  v60 = v37 * *(float *)(this + 430068);
  v20 = v37 * *(float *)(this + 430060) + *(float *)(this + 430048);
  v42 = v53 + *(float *)(this + 430052);
  v21 = v60 + *(float *)(this + 430056);
  *(float *)(this + 430052) = v42;
  v47 = v21;
  *(float *)(this + 430048) = v20;
  *(float *)(this + 430056) = v47;
  ((gbVec3D *)(this + 430048))->Normalize();
  v50 = 0.0;
  *(float *)(this + 430048) = v38 * *(float *)(this + 430048);
  *(float *)(this + 430052) = v38 * *(float *)(this + 430052);
  *(float *)(this + 430056) = v38 * *(float *)(this + 430056);
  v54 = v37 * *(float *)(this + 430052);
  v61 = v37 * *(float *)(this + 430056);
  v22 = v37 * *(float *)(this + 430048) + *(float *)(this + 430136);
  v23 = v54 + *(float *)(this + 430140);
  v55 = 0.0;
  v43 = v23;
  v24 = v61 + *(float *)(this + 430144);
  v62 = 0.0;
  *(float *)(this + 430140) = v43;
  v48 = v24;
  *(float *)(this + 430136) = v22;
  *(float *)(this + 430144) = v48;
  v25 = *(float *)(this + 430136);
  v26 = *(_BYTE *)(v3 + 102);
  v39 = *(float *)(this + 430136);
  if ( v26 || *(_BYTE *)(v3 + 101) )
  {
    v27 = *(_DWORD *)(v3 + 104);
    if ( v27 > 0xA )
    {
      if ( v27 == -1 )
      {
        v30 = (float *)*(float **)(*(_DWORD *)(this + 430000) + 20);
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
      v28 = (float *)*(float **)(*(_DWORD *)(this + 430000) + 4 * v27 + 24);
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
    v25 = v25 + v50 - *(float *)(v3 + 184);
    v39 = v25;
    v43 = v44 - *(float *)(v3 + 188);
    v48 = v49 - *(float *)(v3 + 192);
  }
  if ( *(_BYTE *)(v3 + 101) )
  {
    *(float *)(this + 430116) = v43;
    *(float *)(this + 430120) = v48;
    *(float *)(this + 430112) = v25;
    v39->CalcDist(v43);
  }
  else
  {
    v56 = *(float *)(v3 + 60) - *(float *)(this + 430092);
    v63 = *(float *)(v3 + 64) - *(float *)(this + 430096);
    v65 = *(float *)(v3 + 68) - *(float *)(this + 430100);
    v67 = *(float *)(v3 + 72) - *(float *)(this + 430104);
    v69 = *(float *)(v3 + 76) - *(float *)(this + 430108);
    v71 = v56 * v34;
    v72 = v63 * v34;
    v73 = v65 * v34;
    v74 = v67 * v34;
    v75 = v69 * v34;
    v32 = (*(float *)(v3 + 56) - *(float *)(this + 430088)) * v34 + *(float *)(this + 430088);
    v57 = v71 + *(float *)(this + 430092);
    v64 = v72 + *(float *)(this + 430096);
    v66 = v73 + *(float *)(this + 430100);
    v68 = v74 + *(float *)(this + 430104);
    v33 = v75 + *(float *)(this + 430108);
    *(float *)(this + 430116) = v57;
    *(float *)(this + 430120) = v64;
    *(float *)(this + 430124) = v66;
    *(float *)(this + 430128) = v68;
    v70 = v33;
    *(float *)(this + 430112) = v32;
    *(float *)(this + 430132) = v70;
    *(float *)(this + 430112) = v25;
    *(float *)(this + 430116) = v43;
    *(float *)(this + 430120) = v48;
  }
  ((CCCTData *)*(CCCTData **)(this + 430004))->UpdateCamera(this + 430112);
  ((CameraCtrl *)*(CameraCtrl **)(this + 430004))->SetAsCurrent(3);
  if ( v34 >= 1.0 )
    *(_BYTE *)(v3 + 22) = 1;
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
  *(_DWORD *)&byte_17AAF64[1464] = 1094713344;
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
  *(float *)&byte_17AAF64[1460] = 12.0 + 12.0;
}
