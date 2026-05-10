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
extern int dword_BFDA60;
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

  this->m_Pool[1707].StartPos.fPitch = *(float *)a2;
  this->m_Pool[1707].StartPos.pit = (float)a2[1];
  this->m_Pool[1707].StartPos.fRoll = (float)a2[2];
  this->m_Pool[1707].StartPos.rol = *(float *)a3;
  this->m_Pool[1707].EndPos.fFromX = (float)a3[1];
  result = a3[2];
  LODWORD(this->m_Pool[1707].EndPos.x) = result;
  result;
}

// 0x00505930
CCCTData::~CCCTData()
{
  float *p_fPitch; // ebp
  struct gbRenderEffect *v3; // ebx
  float *v4; // esi
  _BYTE *v5; // esi
  unsigned int *p_Color; // esi
  double v7; // st7
  float v8; // edx
  float pit; // eax
  int fRoll_low; // ecx
  double rol; // st7
  float v12; // edx
  float fFromX; // eax
  int x_low; // ecx
  float v15; // edx
  float v16; // eax
  float v17; // ecx
  float v18; // edx
  float y; // edi
  double v20; // st7
  double v21; // st6
  unsigned int v22; // edx
  double v23; // st6
  gbColorQuad v24; // [esp+40h] [ebp-A8h] BYREF
  int v25; // [esp+4Ch] [ebp-9Ch]
  int v26; // [esp+64h] [ebp-84h]
  float fRoll; // [esp+68h] [ebp-80h]
  int v28; // [esp+6Ch] [ebp-7Ch]
  int v29; // [esp+70h] [ebp-78h]
  int v30; // [esp+74h] [ebp-74h]
  int v31; // [esp+78h] [ebp-70h]
  struct gbColorQuad v32; // [esp+7Ch] [ebp-6Ch] BYREF
  float v33; // [esp+88h] [ebp-60h]
  float v34; // [esp+8Ch] [ebp-5Ch]
  float v35; // [esp+90h] [ebp-58h]
  float v36; // [esp+94h] [ebp-54h]
  float x; // [esp+98h] [ebp-50h]
  _BYTE v38[64]; // [esp+9Ch] [ebp-4Ch] BYREF
  float v39; // [esp+DCh] [ebp-Ch]
  float v40; // [esp+E0h] [ebp-8h]
  float v41; // [esp+E4h] [ebp-4h]

  if ( LOBYTE(this->m_Pool[1707].EndPos.fFromY) )
  {
    ((gbMatrix4 *)v38)->gbMatrix4();
    ((gbGeomNode *)LODWORD(this->m_Pool[1707].StartPos.yaw))->GetTotalOBBox((struct gbOBBox *)v38);
    p_fPitch = (float *)&this->m_Pool[1707].StartPos.fPitch;
    ((gbMatrix4 *)v38)->RightTranslate((struct gbVec3D *)&this->m_Pool[1707].StartPos.fPitch);
    v3 = ((gbEffectMgr *)dword_BFDA60->pEffectMgr)->NewTrivalEffect(3);
    *(_DWORD *)&v32.Blue = ((gbVertPoolMgr *)dword_BFDA60->pVertPoolMgr)->GetDynVertBuf(0x15u);
    if ( (byte_17AAEE0 & 1) == 0 )
    {
      v4 = (float *)&flt_17AAD48;
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
    flt_17AAD48 = v39 * -0.5;
    dword_17AAD50 = v28;
    dword_17AAD58 = v31;
    flt_17AAD54 = v39 * 0.5;
    dword_17AAD5C = v28;
    dword_17AAD68 = v28;
    *(float *)&v29 = v40 * -0.5;
    flt_17AAD60 = flt_17AAD54;
    dword_17AAD64 = v29;
    flt_17AAD6C = flt_17AAD48;
    dword_17AAD70 = v29;
    *(float *)&v30 = v41 * -0.5;
    dword_17AAD74 = v28;
    flt_17AAD8C = flt_17AAD48;
    dword_17AAD90 = v31;
    dword_17AAD94 = v30;
    flt_17AAD98 = flt_17AAD54;
    dword_17AAD9C = v31;
    dword_17AADA0 = v30;
    flt_17AADA4 = flt_17AAD54;
    flt_17AADB0 = flt_17AAD48;
    flt_17AADD0 = flt_17AAD48;
    dword_17AADA8 = v29;
    dword_17AADAC = v30;
    dword_17AADB4 = v29;
    dword_17AADB8 = v30;
    flt_17AADDC = flt_17AAD48;
    dword_17AADD4 = v31;
    dword_17AADD8 = v28;
    flt_17AADE8 = flt_17AAD48;
    dword_17AADE0 = v31;
    dword_17AADE4 = v30;
    flt_17AADF4 = flt_17AAD48;
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
    flt_17AAE58 = flt_17AAD48;
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
    flt_17AAE7C = flt_17AAD48;
    dword_17AAE78 = v28;
    dword_17AAE80 = v31;
    flt_17AAE9C = flt_17AAD48;
    dword_17AAE84 = v28;
    dword_17AAEA0 = v29;
    dword_17AAEA4 = v30;
    flt_17AAEA8 = flt_17AAD54;
    flt_17AAEB4 = flt_17AAD54;
    dword_17AAEAC = v29;
    dword_17AAEB0 = v30;
    flt_17AAEC0 = flt_17AAD48;
    dword_17AAEB8 = v29;
    dword_17AAEBC = v28;
    v26 = v29;
    fRoll = *(float *)&v28;
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
    ((gbDynVertBuf *)&flt_17AAD48)->RenderGeomQuad(6, v3, 0);
    p_Color = (unsigned int *)&v32.Color;
    v28 = 2;
    do
    {
      ((void (*)(unsigned int *))gbVec3D::`default constructor closure')(p_Color);
      p_Color += 3;
      --v28;
    }
    while ( *(float *)&v28 != 0.0 );
    v7 = *p_fPitch;
    v8 = *p_fPitch;
    pit = this->m_Pool[1707].StartPos.pit;
    fRoll = this->m_Pool[1707].StartPos.fRoll;
    v35 = v8;
    *(float *)&v32.Color = v7;
    v34 = fRoll;
    fRoll_low = SLODWORD(this->m_Pool[1707].StartPos.fRoll);
    v25 = (int)v3;
    v24.Color = 2;
    *(_DWORD *)&v24.Blue = &v32.Color;
    v36 = pit;
    v24.ColorQuadFmt = fRoll_low;
    x = *(float *)&fRoll_low;
    v32.ColorQuadFmt = 1358954495;
    v33 = 0.0;
    ((gbColorQuad *)&v24)->gbColorQuad(&v32);
    ((gbDynVertBuf *)LODWORD(v35))->RenderLineStrip();
    rol = this->m_Pool[1707].StartPos.rol;
    v12 = this->m_Pool[1707].StartPos.rol;
    fFromX = this->m_Pool[1707].EndPos.fFromX;
    fRoll = this->m_Pool[1707].EndPos.x;
    v35 = v12;
    *(float *)&v32.Color = rol;
    v34 = fRoll;
    x_low = SLODWORD(this->m_Pool[1707].EndPos.x);
    v25 = (int)v3;
    v24.Color = 2;
    *(_DWORD *)&v24.Blue = &v32.Color;
    v36 = fFromX;
    v24.ColorQuadFmt = x_low;
    x = *(float *)&x_low;
    v33 = 0.0;
    ((gbColorQuad *)&v24)->gbColorQuad(&v32);
    ((gbDynVertBuf *)LODWORD(v35))->RenderLineStrip();
    v15 = this->m_Pool[1707].StartPos.pit;
    v16 = this->m_Pool[1707].StartPos.fRoll;
    v32.Color = *(unsigned int *)p_fPitch;
    v17 = this->m_Pool[1707].StartPos.rol;
    v33 = v15;
    v18 = this->m_Pool[1707].EndPos.fFromX;
    v35 = v17;
    v25 = (int)v3;
    v24.Color = 2;
    *(_DWORD *)&v24.Blue = &v32.Color;
    v36 = v18;
    v24.ColorQuadFmt = (int)&v32.Color;
    v34 = v16;
    x = this->m_Pool[1707].EndPos.x;
    ((gbColorQuad *)&v24)->gbColorQuad(&v32);
    ((gbDynVertBuf *)LODWORD(v35))->RenderLineStrip();
    y = this->m_Pool[1706].EndPos.y;
    v20 = *(float *)(LODWORD(y) + 492) + 1.0;
    v21 = *(float *)(LODWORD(y) + 496) + 1.0;
    v22 = *(_DWORD *)p_fPitch;
    v25 = (int)v3;
    v24.Color = 2;
    *(float *)&v26 = v21;
    v23 = *(float *)(LODWORD(y) + 500);
    v35 = *(float *)&v22;
    v33 = *(float *)&v26;
    v36 = p_fPitch[1];
    fRoll = v23 + 1.0;
    *(_DWORD *)&v24.Blue = &v32.Color;
    *(float *)&v32.Color = v20;
    v34 = fRoll;
    v24.ColorQuadFmt = (int)p_fPitch[2];
    x = *(float *)&v24.ColorQuadFmt;
    ((gbColorQuad *)&v24)->gbColorQuad(&v32);
    ((gbDynVertBuf *)LODWORD(v35))->RenderLineStrip();
    ((gbRefObject *)v3)->Release();
  }
}

// 0x00506020
bool CCCTData::Create(float *a2)
{
  float fFromY; // eax
  float y; // ecx
  float pPos[2]; // [esp+8h] [ebp-90h] BYREF
  struct gbVec3D v7; // [esp+10h] [ebp-88h] BYREF
  gbRay v8; // [esp+1Ch] [ebp-7Ch] BYREF
  _BYTE v9[76]; // [esp+34h] [ebp-64h] BYREF
  _BYTE pTarget[24]; // [esp+80h] [ebp-18h] BYREF

  ((gbMatrix4 *)v9)->gbMatrix4();
  ((gbGeomNode *)LODWORD(this->m_Pool[1707].StartPos.yaw))->GetTotalOBBox((struct gbOBBox *)v9);
  v7.x = *a2;
  v7.y = a2[1];
  v7.z = a2[2];
  ((gbMatrix4 *)v9)->RightTranslate(&v7);
  fFromY = this->m_Pool[1706].EndPos.fFromY;
  pPos[0] = *(float *)(LODWORD(fFromY) + 80);
  y = this->m_Pool[1706].EndPos.y;
  pPos[1] = *(float *)(LODWORD(fFromY) + 84);
  qmemcpy(&v8, ((CameraCtrl *)LODWORD(y))->GetViewTarget(pTarget, pPos), sizeof(v8));
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
    *(_DWORD *)v3->_pad_0000 = &off_56A66C;
    v4 = v3;
  }
  else
  {
    v4 = 0;
  }
  v8 = -1;
  LODWORD(this->m_Pool[1707].StartPos.yaw) = v4;
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
  int fRoll_low; // edx
  float rol; // ebp
  unsigned int v4; // ecx
  char *v5; // edi

  fRoll_low = LODWORD(this->m_Pool[1706].EndPos.fRoll);
  rol = this->m_Pool[1706].EndPos.rol;
  v4 = this->m_Pool[1626].dwReserved[50 * fRoll_low + 1 + LODWORD(rol)];
  if ( v4 == -1 )
    v5 = 0;
  else
    v5 = (char *)this + 204 * v4;
  if ( v5[22] )
  {
    LODWORD(this->m_Pool[1706].EndPos.rol) = LODWORD(rol) + 1;
    if ( SLODWORD(this->m_Pool[1706].EndPos.rol) >= ((CCBStageCam *)this)->IsEditorCamValid(fRoll_low) )
    {
      LOBYTE(this->m_Pool[1706].EndPos.z) = 0;
      this->m_Pool[1706].EndPos.rol = NAN;
      this->m_Pool[1706].EndPos.fRoll = NAN;
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
  unsigned int *v5; // edx
  char *v6; // eax

  result = ((CCBStageCam *)this)->IsEditorCamValid(a2);
  if ( result > 0 )
  {
    v4 = result;
    v5 = (unsigned int *)&this->m_Pool[1626].dwReserved[50 * a2 + 1];
    do
    {
      if ( *v5 == -1 )
        v6 = 0;
      else
        v6 = (char *)this + 204 * *v5;
      v6[21] = 0;
      if ( *v5 == -1 )
        result = 0;
      else
        result = (int)this + 204 * *v5;
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
  float y; // eax
  double v3; // st7
  double v4; // st6
  int v5; // ecx
  int v6; // edx
  int v8; // [esp+0h] [ebp-10h]
  int v9; // [esp+4h] [ebp-Ch]

  y = this->m_Pool[1706].EndPos.y;
  v3 = *(float *)(LODWORD(y) + 496);
  v4 = *(float *)(LODWORD(y) + 492);
  v8 = *(_DWORD *)(LODWORD(y) + 500);
  v5 = *(_DWORD *)(LODWORD(y) + 452);
  v9 = *(_DWORD *)(LODWORD(y) + 456);
  v6 = *(_DWORD *)(LODWORD(y) + 464);
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
  unsigned int v1; // edx
  char *v2; // eax
  unsigned int v4; // ecx
  char *v5; // ebx
  double v6; // st7
  double fCircleCentreX; // st7
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
  double fStartFOV; // st7
  char v25; // cl
  unsigned int v26; // eax
  float *v27; // eax
  float v28; // edx
  float *v29; // eax
  float v30; // edx
  float *p_fCircleEndX; // esi
  unsigned __int8 v33; // c0
  unsigned __int8 v34; // c3
  float fInertia; // [esp+1Ch] [ebp-80h]
  float v36; // [esp+20h] [ebp-7Ch]
  float v37; // [esp+24h] [ebp-78h]
  float v38; // [esp+28h] [ebp-74h]
  float fEndFOV; // [esp+2Ch] [ebp-70h]
  float v40; // [esp+2Ch] [ebp-70h]
  float fStartTracePosX; // [esp+30h] [ebp-6Ch]
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

  v1 = this->m_Pool[1626].dwReserved[50 * LODWORD(this->m_Pool[1706].EndPos.fRoll)
                                   + 1
                                   + LODWORD(this->m_Pool[1706].EndPos.rol)];
  if ( v1 == -1 )
    v2 = 0;
  else
    v2 = (char *)this + 204 * v1;
  if ( v2[89] && v2[91] )
  {
    if ( !v2[90] )
    {
      v4 = this->m_Pool[1626].dwReserved[50 * LODWORD(this->m_Pool[1706].EndPos.fRoll)
                                       + 1
                                       + LODWORD(this->m_Pool[1706].EndPos.rol)];
      if ( v4 == -1 )
        v5 = 0;
      else
        v5 = (char *)this + 204 * v4;
      if ( !v5[21] )
      {
        if ( !v5[88] )
          this->Load((int)(v5 + 32));
        if ( v5[96] )
          v6 = *(float *)(*(_DWORD *)LODWORD(this->m_Pool[1706].EndPos.fFromY) + 104);
        else
          v6 = *(float *)(*(_DWORD *)LODWORD(this->m_Pool[1706].EndPos.fFromY) + 80);
        *((float *)v5 + 6) = v6;
        qmemcpy(&this->m_Pool[1706].fAcceleration2, v5 + 32, 0x18u);
        if ( v5[97] )
        {
          if ( *((float *)v5 + 17) - this->m_Pool[1706].fCircleCentreX <= 0.0 )
          {
            fCircleCentreX = this->m_Pool[1706].fCircleCentreX;
            if ( v9 )
              fCircleCentreX = fCircleCentreX - 6.2831855;
          }
          else
          {
            fCircleCentreX = this->m_Pool[1706].fCircleCentreX + 6.2831855;
          }
          this->m_Pool[1706].fCircleCentreX = fCircleCentreX;
        }
        this->m_Pool[1706].fInertia = *((float *)v5 + 33);
        this->m_Pool[1706].nStartCam = *((_DWORD *)v5 + 34);
        v5[21] = 1;
      }
      if ( v5[96] )
        v10 = *(float *)(*(_DWORD *)LODWORD(this->m_Pool[1706].EndPos.fFromY) + 104);
      else
        v10 = *(float *)(*(_DWORD *)LODWORD(this->m_Pool[1706].EndPos.fFromY) + 80);
      v11 = v10 - *((float *)v5 + 6);
      v36 = v11;
      fInertia = v11 * *(float *)&this->m_Pool[1706].nStartCam;
      if ( v36 >= (double)*((float *)v5 + 29) )
      {
        v12 = v36 - *((float *)v5 + 29);
        fInertia = v12 * *((float *)v5 + 31) * v12 * 0.5 + fInertia;
      }
      if ( v36 >= (double)*((float *)v5 + 30) )
      {
        v13 = v36 - *((float *)v5 + 30);
        fInertia = (*((float *)v5 + 32) + *((float *)v5 + 31)) * v13 * v13 * 0.5 + fInertia;
      }
      if ( v15 | v16 )
      {
        if ( fInertia < (double)this->m_Pool[1706].fInertia )
          fInertia = this->m_Pool[1706].fInertia;
      }
      else if ( fInertia > (double)this->m_Pool[1706].fInertia )
      {
        fInertia = this->m_Pool[1706].fInertia;
      }
      v17 = *((float *)v5 + 39) - *((float *)v5 + 36);
      v18 = fInertia / this->m_Pool[1706].fInertia;
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
      this->m_Pool[1706].fEndFOV = v49;
      v50 = v20;
      this->m_Pool[1706].fStartFOV = v19;
      this->m_Pool[1706].fStartTracePosX = v50;
      ((gbQuaternion *)&v51)->SetYawPitchRoll(fInertia, 0.0, 0.0);
      ((gbQuaternion *)&v51)->GetMatrix((struct gbMatrix4 *)v52);
      ((gbMatrix4 *)v52)->RotateIn((struct gbVec3D *)&this->m_Pool[1706].fStartFOV);
      v21 = v43 + this->m_Pool[1706].fStartFOV;
      v44 = 0.0;
      this->m_Pool[1706].fStartFOV = v21;
      v22 = v45 + this->m_Pool[1706].fEndFOV;
      v46 = 0.0;
      this->m_Pool[1706].fEndFOV = v22;
      v23 = v47 + this->m_Pool[1706].fStartTracePosX;
      v48 = 0.0;
      this->m_Pool[1706].fStartTracePosX = v23;
      this->m_Pool[1706].fEndFOV = v37 + this->m_Pool[1706].fEndFOV;
      fStartFOV = this->m_Pool[1706].fStartFOV;
      v38 = this->m_Pool[1706].fStartFOV;
      fEndFOV = this->m_Pool[1706].fEndFOV;
      v25 = v5[102];
      fStartTracePosX = this->m_Pool[1706].fStartTracePosX;
      if ( v25 || v5[101] )
      {
        v26 = *((_DWORD *)v5 + 26);
        if ( v26 > 0xA )
        {
          if ( v26 == -1 )
          {
            v29 = (float *)*(float **)(LODWORD(this->m_Pool[1706].EndPos.fFromY) + 20);
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
          v27 = (float *)*(float **)(LODWORD(this->m_Pool[1706].EndPos.fFromY) + 4 * v26 + 24);
          v28 = v27[1646];
          v27 += 1646;
          v44 = v28;
          v46 = v27[1];
          v48 = v27[2];
        }
      }
      if ( v25 )
      {
        v40 = fEndFOV + v46;
        v42 = fStartTracePosX + v48;
        fStartFOV = fStartFOV + v44 - *((float *)v5 + 46);
        v38 = fStartFOV;
        fEndFOV = v40 - *((float *)v5 + 47);
        fStartTracePosX = v42 - *((float *)v5 + 48);
      }
      p_fCircleEndX = (float *)&this->m_Pool[1706].fCircleEndX;
      if ( v5[101] )
      {
        this->m_Pool[1706].fCircleEndY = fEndFOV;
        this->m_Pool[1706].fCircleEndZ = fStartTracePosX;
        *p_fCircleEndX = fStartFOV;
        v38->CalcDist(fEndFOV);
      }
      else
      {
        * p_fCircleEndX = (*)this->m_Pool[1706].fAcceleration2;
        this->m_Pool[1706].fCircleEndY = this->m_Pool[1706].fCircleAngle;
        this->m_Pool[1706].fCircleEndZ = this->m_Pool[1706].fAngleSpeed;
        this->m_Pool[1706].fSwingFre = this->m_Pool[1706].fCircleCentreX;
        this->m_Pool[1706].fSwing = this->m_Pool[1706].fCircleCentreY;
        this->m_Pool[1706].fTimeExpiate = this->m_Pool[1706].fCircleCentreZ;
        this->m_Pool[1706].fCircleEndY = fEndFOV;
        *p_fCircleEndX = fStartFOV;
        this->m_Pool[1706].fCircleEndZ = fStartTracePosX;
      }
      ((CCCTData *)LODWORD(this->m_Pool[1706].EndPos.y))->UpdateCamera((int)&this->m_Pool[1706].fCircleEndX);
      ((CameraCtrl *)LODWORD(this->m_Pool[1706].EndPos.y))->SetAsCurrent(3);
      if ( v33 | v34 )
      {
        if ( fInertia <= (double)this->m_Pool[1706].fInertia )
        {
          *((float *)v5 + 7) = v36;
          v5[22] = 1;
        }
      }
      else if ( fInertia >= (double)this->m_Pool[1706].fInertia )
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
  unsigned int v2; // ecx
  char *v3; // ebx
  float *v4; // edx
  float rol; // eax
  unsigned int v6; // ecx
  char *v7; // eax
  double v8; // st7
  float v9; // ecx
  double v10; // st7
  float v11; // ecx
  int v12; // ecx
  double v13; // st7
  double fCircleCentreX; // st7
  char v16; // c0
  float fFromY; // edx
  double v18; // st7
  int v19; // eax
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st6
  double v24; // st6
  double fStartFOV; // st7
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
  int v41; // [esp+20h] [ebp-38h]
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
  int v52; // [esp+2Ch] [ebp-2Ch]
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

  v2 = this->m_Pool[1626].dwReserved[50 * LODWORD(this->m_Pool[1706].EndPos.fRoll)
                                   + 1
                                   + LODWORD(this->m_Pool[1706].EndPos.rol)];
  if ( v2 == -1 )
    v3 = 0;
  else
    v3 = (char *)this + 204 * v2;
  if ( !v3[21] )
  {
    if ( !v3[88] )
      this->Load((int)(v3 + 32));
    v4 = (float *)(v3 + 32);
    qmemcpy(&this->m_Pool[1706].fAcceleration2, v3 + 32, 0x18u);
    this->m_Pool[1706].fStartFOV = *((float *)v3 + 8);
    this->m_Pool[1706].fEndFOV = *((float *)v3 + 9);
    rol = this->m_Pool[1706].EndPos.rol;
    this->m_Pool[1706].fStartTracePosX = *((float *)v3 + 10);
    if ( rol == 0.0
      || SLODWORD(rol) > 0
      && ((v6 = this->m_Pool[1626].dwReserved[50 * LODWORD(this->m_Pool[1706].EndPos.fRoll) + LODWORD(rol)], v6 == -1)
        ? (v7 = 0)
        : (v7 = (char *)this + 204 * v6),
          !v7[94]) )
    {
      v8 = *((float *)v3 + 14) - *v4;
      v51 = *((float *)v3 + 15) - *((float *)v3 + 9);
      v58 = *((float *)v3 + 16) - *((float *)v3 + 10);
      if ( *((float *)v3 + 7) <= 0.0 )
      {
        v9 = *((float *)v3 + 16) - *((float *)v3 + 10);
        *(float *)&this->m_Pool[1706].bStartCamValid = v8;
        *(float *)&this->m_Pool[1706].bLineMove = v51;
      }
      else
      {
        v35 = 1.0 / *((float *)v3 + 7);
        v40 = v51 * v35;
        *(float *)&this->m_Pool[1706].bLineMove = v40;
        v45 = v58 * v35;
        v9 = v45;
        *(float *)&this->m_Pool[1706].bStartCamValid = v8 * v35;
      }
      *(float *)&this->m_Pool[1706].bAbsoluteTime = v9;
    }
    v10 = *((float *)v3 + 14) - *v4;
    *(float *)&v52 = *((float *)v3 + 15) - *((float *)v3 + 9);
    v59 = *((float *)v3 + 16) - *((float *)v3 + 10);
    if ( *((float *)v3 + 7) <= 0.0 )
    {
      v11 = *((float *)v3 + 16) - *((float *)v3 + 10);
      *(float *)&this->m_Pool[1706].bRandSwing = v10;
      this->m_Pool[1706].nTraceRole = v52;
    }
    else
    {
      v36 = 1.0 / *((float *)v3 + 7);
      *(float *)&v41 = *(float *)&v52 * v36;
      this->m_Pool[1706].nTraceRole = v41;
      v46 = v59 * v36;
      v11 = v46;
      *(float *)&this->m_Pool[1706].bRandSwing = v10 * v36;
    }
    this->m_Pool[1706].fStartSpeed = v11;
    v12 = *(_DWORD *)LODWORD(this->m_Pool[1706].EndPos.fFromY);
    if ( v3[96] )
      v13 = *(float *)(v12 + 104);
    else
      v13 = *(float *)(v12 + 80);
    *((float *)v3 + 6) = v13;
    qmemcpy(&this->m_Pool[1706].fCircleEndX, v4, 0x18u);
    if ( v3[97] )
    {
      if ( *((float *)v3 + 17) - this->m_Pool[1706].fCircleCentreX <= 0.0 )
      {
        fCircleCentreX = this->m_Pool[1706].fCircleCentreX;
        if ( v16 )
          fCircleCentreX = fCircleCentreX - 6.2831855;
      }
      else
      {
        fCircleCentreX = this->m_Pool[1706].fCircleCentreX + 6.2831855;
      }
      this->m_Pool[1706].fCircleCentreX = fCircleCentreX;
    }
    v3[21] = 1;
  }
  if ( v3[96] )
  {
    fFromY = this->m_Pool[1706].EndPos.fFromY;
    v37 = *(double *)(*(_DWORD *)LODWORD(fFromY) + 88);
    v18 = *(float *)(*(_DWORD *)LODWORD(fFromY) + 104);
  }
  else
  {
    v19 = *(_DWORD *)LODWORD(this->m_Pool[1706].EndPos.fFromY);
    v37 = *(double *)(v19 + 64);
    v18 = *(float *)(v19 + 80);
  }
  if ( *((float *)v3 + 7) > 0.0 )
    v34 = (v18 - *((float *)v3 + 6)) / (*((float *)v3 + 43) + *((float *)v3 + 7));
  else
    v34 = 1.0;
  v38 = ((gbVec3D *)&this->m_Pool[1706].bStartCamValid)->Length();
  v53 = v37 * *(float *)&this->m_Pool[1706].nTraceRole;
  v60 = v37 * this->m_Pool[1706].fStartSpeed;
  v20 = v37 * *(float *)&this->m_Pool[1706].bRandSwing + *(float *)&this->m_Pool[1706].bStartCamValid;
  v42 = v53 + *(float *)&this->m_Pool[1706].bLineMove;
  v21 = v60 + *(float *)&this->m_Pool[1706].bAbsoluteTime;
  *(float *)&this->m_Pool[1706].bLineMove = v42;
  v47 = v21;
  *(float *)&this->m_Pool[1706].bStartCamValid = v20;
  *(float *)&this->m_Pool[1706].bAbsoluteTime = v47;
  ((gbVec3D *)&this->m_Pool[1706].bStartCamValid)->Normalize();
  v50 = 0.0;
  *(float *)&this->m_Pool[1706].bStartCamValid = v38 * *(float *)&this->m_Pool[1706].bStartCamValid;
  *(float *)&this->m_Pool[1706].bLineMove = v38 * *(float *)&this->m_Pool[1706].bLineMove;
  *(float *)&this->m_Pool[1706].bAbsoluteTime = v38 * *(float *)&this->m_Pool[1706].bAbsoluteTime;
  v54 = v37 * *(float *)&this->m_Pool[1706].bLineMove;
  v61 = v37 * *(float *)&this->m_Pool[1706].bAbsoluteTime;
  v22 = v37 * *(float *)&this->m_Pool[1706].bStartCamValid + this->m_Pool[1706].fStartFOV;
  v23 = v54 + this->m_Pool[1706].fEndFOV;
  v55 = 0.0;
  v43 = v23;
  v24 = v61 + this->m_Pool[1706].fStartTracePosX;
  v62 = 0.0;
  this->m_Pool[1706].fEndFOV = v43;
  v48 = v24;
  this->m_Pool[1706].fStartFOV = v22;
  this->m_Pool[1706].fStartTracePosX = v48;
  fStartFOV = this->m_Pool[1706].fStartFOV;
  v26 = v3[102];
  v39 = this->m_Pool[1706].fStartFOV;
  if ( v26 || v3[101] )
  {
    v27 = *((_DWORD *)v3 + 26);
    if ( v27 > 0xA )
    {
      if ( v27 == -1 )
      {
        v30 = (float *)*(float **)(LODWORD(this->m_Pool[1706].EndPos.fFromY) + 20);
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
      v28 = (float *)*(float **)(LODWORD(this->m_Pool[1706].EndPos.fFromY) + 4 * v27 + 24);
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
    fStartFOV = fStartFOV + v50 - *((float *)v3 + 46);
    v39 = fStartFOV;
    v43 = v44 - *((float *)v3 + 47);
    v48 = v49 - *((float *)v3 + 48);
  }
  if ( v3[101] )
  {
    this->m_Pool[1706].fCircleEndY = v43;
    this->m_Pool[1706].fCircleEndZ = v48;
    this->m_Pool[1706].fCircleEndX = fStartFOV;
    v39->CalcDist(v43);
  }
  else
  {
    v56 = *((float *)v3 + 15) - this->m_Pool[1706].fCircleAngle;
    v63 = *((float *)v3 + 16) - this->m_Pool[1706].fAngleSpeed;
    v65 = *((float *)v3 + 17) - this->m_Pool[1706].fCircleCentreX;
    v67 = *((float *)v3 + 18) - this->m_Pool[1706].fCircleCentreY;
    v69 = *((float *)v3 + 19) - this->m_Pool[1706].fCircleCentreZ;
    v71 = v56 * v34;
    v72 = v63 * v34;
    v73 = v65 * v34;
    v74 = v67 * v34;
    v75 = v69 * v34;
    v32 = (*((float *)v3 + 14) - this->m_Pool[1706].fAcceleration2) * v34 + this->m_Pool[1706].fAcceleration2;
    v57 = v71 + this->m_Pool[1706].fCircleAngle;
    v64 = v72 + this->m_Pool[1706].fAngleSpeed;
    v66 = v73 + this->m_Pool[1706].fCircleCentreX;
    v68 = v74 + this->m_Pool[1706].fCircleCentreY;
    v33 = v75 + this->m_Pool[1706].fCircleCentreZ;
    this->m_Pool[1706].fCircleEndY = v57;
    this->m_Pool[1706].fCircleEndZ = v64;
    this->m_Pool[1706].fSwingFre = v66;
    this->m_Pool[1706].fSwing = v68;
    v70 = v33;
    this->m_Pool[1706].fCircleEndX = v32;
    this->m_Pool[1706].fTimeExpiate = v70;
    this->m_Pool[1706].fCircleEndX = fStartFOV;
    this->m_Pool[1706].fCircleEndY = v43;
    this->m_Pool[1706].fCircleEndZ = v48;
  }
  ((CCCTData *)LODWORD(this->m_Pool[1706].EndPos.y))->UpdateCamera((int)&this->m_Pool[1706].fCircleEndX);
  ((CameraCtrl *)LODWORD(this->m_Pool[1706].EndPos.y))->SetAsCurrent(3);
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
