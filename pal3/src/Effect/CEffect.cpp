#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffect.h"

// Forward declarations for unnamed functions
int sub_4D1FD0(...);
int sub_4D2ED0(...);
int sub_4D3010(...);
int sub_4D48B0(...);
int sub_4D4AB0(...);
void __cdecl todo_401800(void);

// Unnamed globals (extern)
extern char byte_FFFFFF;
extern int dword_5D4DAC;
extern int dword_5D4DB8;
extern int dword_5D4DC4;
extern int dword_5D4DCC;
extern int dword_5D4DD4;
extern int dword_5D4E00;
extern int dword_5D4E24;
extern int dword_5D4E30;
extern int dword_5D4E38;
extern int dword_5D4E40;
extern int dword_5D4FD0;
extern int dword_5D4FE0;
extern int dword_5D4FF0;
extern int dword_5D4FFC;
extern int dword_5D5008;
extern int dword_5D5014;
extern int dword_5D5020;
extern int dword_5D5038;
extern int dword_5D5040;
extern int dword_5D5048;
extern int dword_5D5050;

// 0x0048E780
int CEffect::CreateFromTemplate(int f)
{
  char *v4; // edx
  int *v5; // ebx
  int v6; // esi
  RenderTarget *v7; // ebp
  int v8; // eax
  int v9; // eax
  int *p_m_nScaleX; // edi
  RenderTarget *v11; // esi
  bool v12; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  int v19; // [esp+0x18] [ebp-0xC]
  int *v20; // [esp+0x1C] [ebp-0x8]
  int fa; // [esp+0x28] [ebp+0x4]

  this->m_QuadBuffer[1579].color = 0;
  this->m_QuadBuffer[1580].vec[0].x = 0.0;
  fa = 16;
  v4 = (char *)this + 16 * f;
  *((_BYTE *)&this->m_QuadBuffer[1579].color + f) = 1;
  v5 = (int *)(v4 + 205644);
  v6 = *((_DWORD *)v4 + 51413) - *((_DWORD *)v4 + 51411);
  v20 = (int *)(&this->m_QuadBuffer[1578].vec[0].z + 4 * f);
  v19 = v6;
  v7 = (RenderTarget *)((char *)&this->m_Partical[1169] + 9344 * f);
  while ( 1 )
  {
    ((RenderTarget *)v7)->LoadTexture(szFilename);
    ((RenderTarget *)v7)->SetSize(32);
    fY = rand() % 10 + 66;
    fX = rand() % 10 + 188;
    v8 = rand();
    ((RenderTarget *)v7)->SetColor(v8 % 10 - 6, fX, fY);
    v9 = rand();
    ((RenderTarget *)v7)->SetAlpha(v9 % 55 - 56);
    *((_BYTE *)&v7->m_ScreenPlane + 4) = 1;
    ((RenderTarget *)v7)->SetField084();
    ((RenderTarget *)v7)->SetState();
    fYa = (float)*v20;
    fXa = (float)(*v5 + rand() % v6);
    ((RenderTarget *)v7)->UpdateTransform(fXa, fYa);
    ((RenderTarget *)v7)->Render(*v5, v5[1], v5[2]);
    rand();
    *(float *)&fXb = (float)(rand() % 2 + 1);
    ((RenderTarget *)v7)->SetOffset(fXb);
    ((RenderTarget *)v7)->SetScale(0);
    ((RenderTarget *)v7)->SetVisible(1);
    p_m_nScaleX = &v7[373].m_nScaleX;
    v11 = v7;
    v7 = (RenderTarget *)((char *)v7 + 584);
    result = fa - 1;
    v12 = fa == 1;
    qmemcpy(p_m_nScaleX, v11, 0x248u);
    --fa;
    if ( v12 )
      break;
    v6 = v19;
  }
  return result;
}

// 0x0048E950
char CEffect::UpdateState(int nVal)
{
  char result; // al
  CEffectSystem **v4; // edi
  int v5; // ebx
  int v6; // ebp
  int v7; // eax
  RenderTarget *v8; // ebx
  int v9; // esi
  int v10; // edi
  int v11; // eax
  char *p_field_028; // edi
  RenderTarget *v13; // esi
  bool v14; // zf
  int nOffY; // [esp+0x0] [ebp-0x28]
  int nOffYa; // [esp+0x0] [ebp-0x28]
  float fX; // [esp+0x18] [ebp-0x10]
  float fY; // [esp+0x1C] [ebp-0xC]
  int nVal2; // [esp+0x20] [ebp-0x8]
  int nVala; // [esp+0x2C] [ebp+0x4]

  result = *((_BYTE *)&this->m_Partical[17].fY + nVal + 1);
  if ( result )
  {
    v4 = &this->m_pES[4 * nVal];
    v5 = *((_DWORD *)this + 4 * nVal + 88440);
    v6 = (int)v4[88442] - v5;
    v7 = (int)v4[88441];
    nVal2 = (int)v4[88443] - v7;
    nVala = 8;
    fY = (float)v7;
    fX = (float)(v5 + v6 / 2);
    v8 = (RenderTarget *)((char *)this + 4672 * nVal + 330400);
    do
    {
      ((RenderTarget *)v8)->LoadTexture(szFilename);
      ((RenderTarget *)v8)->SetSize(32);
      v9 = rand() % 10 + 219;
      v10 = rand() % 10 + 36;
      v11 = rand();
      ((RenderTarget *)v8)->SetColor(v9, v10, v11 % 10 - 4);
      ((RenderTarget *)v8)->SetAlpha(0xFFu);
      ((RenderTarget *)v8)->SetField084();
      ((RenderTarget *)v8)->SetState();
      ((RenderTarget *)v8)->UpdateTransform(fX, fY);
      ((RenderTarget *)v8)->CalcRenderDimensions(v6, nVal2);
      rand();
      *(float *)&nOffY = (float)(rand() % 2 + 1);
      ((RenderTarget *)v8)->SetOffset(nOffY);
      rand();
      *(float *)&nOffYa = (float)(rand() % 2 + 2);
      ((RenderTarget *)v8)->SetScale(nOffYa);
      LODWORD(v8->m_fileData) = 3;
      ((RenderTarget *)v8)->SetVisible(1);
      p_field_028 = &v8[-117]._field_028;
      v13 = v8;
      v8 = (RenderTarget *)((char *)v8 + 584);
      result = nVala - 1;
      v14 = nVala == 1;
      qmemcpy(p_field_028, v13, 0x248u);
      --nVala;
    }
    while ( !v14 );
  }
  return result;
}

// 0x004AF760
int CEffect::Update(int a2)
{
  int result; // eax

  return result;
}

// 0x004BB190
int CEffect::SetRenderParam(int nVal)
{
  int v3; // edi
  float *p_ev; // ebx
  int result; // eax
  int v6; // edi
  RenderTarget *p_color; // ebx

  v3 = 0;
  if ( *(int *)&this->m_Partical[4].byAlpha > 0 )
  {
    p_ev = &this->m_QuadBuffer[2000].ev;
    do
    {
      ((RenderTarget *)p_ev)->ApplyScale(*(float *)&nVal);
      ++v3;
      p_ev += 8022;
    }
    while ( v3 < *(_DWORD *)&this->m_Partical[4].byAlpha );
  }
  result = LODWORD(this->m_Partical[4].fSize);
  v6 = 0;
  if ( result > 0 )
  {
    p_color = (RenderTarget *)&this->m_QuadBuffer[731].color;
    do
    {
      ((RenderTarget *)p_color)->fn_4BB180(nVal);
      result = LODWORD(this->m_Partical[4].fSize);
      ++v6;
      p_color = (RenderTarget *)((char *)p_color + 21572);
    }
    while ( v6 < result );
  }
  return result;
}

// 0x004BD7A0
int * CEffect::SetQuadParam(int nVal)
{
  int *result; // eax
  int v3; // ecx

  result = (int *)&this->m_QuadBuffer[2003].vec[2];
  v3 = 4;
  do
  {
    *result = nVal;
    result += 8022;
    --v3;
  }
  while ( v3 );
  return result;
}

// 0x004C6940
CEffect::CEffect()
{
  CEffectSystem *v1; // eax

  v1 = (CEffectSystem *)operator new(0x10C0u);
  if ( v1 )
    ((CEffectSystem *)v1)->FillDefaultUVSet();
}

// 0x004C6A70
void CEffect::Reset(float *pfVal, float fVal, float fVal2, float fVal3)
{
  int nQuadIndex_low; // ecx

  this->m_eKind = 0;
  LOBYTE(this->m_Partical[0].fZ) = 0;
  this->m_Partical[2].fSize = fVal + pfVal[46];
  *(float *)&this->m_Partical[2].byAlpha = fVal2 + pfVal[47];
  *(float *)&this->m_Partical[3].pPic = fVal3 + pfVal[48];
  this->m_Partical[2].fX = pfVal[54];
  this->m_Partical[2].fY = pfVal[49];
  this->m_Partical[2].fZ = pfVal[55];
  *(_DWORD *)&this->m_Partical[3].byMaxFrame = 0;
  *(_DWORD *)&this->m_Partical[3].bValid = 0;
  this->m_Partical[3].nQuadIndex = 0;
  this->m_Partical[1].nQuadIndex = (int)pfVal[51];
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *(float *)&this->m_Partical[1].bValid = (float)HIBYTE(this->m_Partical[1].nQuadIndex);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *(float *)&this->m_Partical[1].byMaxFrame = (float)(unsigned __int8)BYTE2(this->m_Partical[1].nQuadIndex);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_Partical[1].fFramePerSec = (float)(unsigned __int8)BYTE1(this->m_Partical[1].nQuadIndex);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_Partical[1].pPic = 0;
  nQuadIndex_low = LOBYTE(this->m_Partical[1].nQuadIndex);
  *(_DWORD *)&this->m_Partical[0].byAlpha = 0;
  this->m_Partical[1].fCurFrame = (float)nQuadIndex_low;
  this->m_Partical[1].dwColor = (unsigned int)pfVal[50];
  this->m_Partical[1].fX = pfVal[50];
  ((CEffExplosive *)this)->CreateGeom();
}

// 0x004C7150
void CEffect::CreateOnePartical(float pPartical)
{
  CEffect *v2; // edi
  double v3; // st7
  CCBStage *p_m_bActive; // esi
  char *v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  bool v11; // cc
  int v12; // esi
  int v13; // edx
  int fY_low; // ecx
  float *v15; // eax
  float *v16; // ebx
  double v17; // st7
  int v18; // edx
  int v19; // eax
  float *v20; // [esp+0x0] [ebp-0x18]
  float *v21; // [esp+0x4] [ebp-0x14]
  float v22; // [esp+0x8] [ebp-0x10]
  int fZ_low; // [esp+0xC] [ebp-0xC]
  float v25; // [esp+0xC] [ebp-0xC]
  CCBStageScene *v26; // [esp+0x10] [ebp-0x8]
  float v27; // [esp+0x10] [ebp-0x8]
  int v28; // [esp+0x14] [ebp-0x4]
  float v29; // [esp+0x14] [ebp-0x4]
  int pParticala; // [esp+0x20] [ebp+0x8]
  int pParticalb; // [esp+0x20] [ebp+0x8]
v3 = pPartical - *(float *)&this->m_DeltaTime;
  p_m_bActive = (CCBStage *)&this->m_bActive;
  *(float *)&this->m_DeltaTime = pPartical;
  *((float *)&this->m_DeltaTime + 1) = v3;
  if ( *((float *)&this->m_DeltaTime + 1) > 0.0 )
  {
    pParticala = 0;
    if ( *(int *)&this->m_Partical[0].byMaxFrame > 0 )
    {
      v28 = 0;
      while ( 1 )
      {
        v5 = (char *)p_m_bActive->m_pCam + v28;
        if ( v5[148] )
        {
          if ( *((_DWORD *)v5 + 3) == 3 )
          {
            v6 = 0;
            v26 = 0;
            if ( (int)p_m_bActive->m_pRole[2] > 0 )
              break;
          }
        }
LABEL_29:
        v11 = ++pParticala < (int)p_m_bActive->m_pRole[1];
        v28 += 152;
        if ( !v11 )
          goto LABEL_30;
      }
      v7 = 0;
      while ( 1 )
      {
        v8 = v7 + *(_DWORD *)v5;
        if ( !*(_BYTE *)(v8 + 64) || v7 > 0 && *(_DWORD *)(v8 - 64) == 2 )
        {
LABEL_28:
goto LABEL_29;
        }
        switch ( *(_DWORD *)(v8 + 8) )
        {
          case 2:
            if ( v7 > 0 )
            {
              if ( *(float *)(v8 + 20) >= 0.0 )
              {
                if ( *(float *)&p_m_bActive->m_pRoleState - *(float *)(v8 - 56) > *(float *)(v8 + 20) )
                {
                  ((CCBStage *)p_m_bActive)->GetTaskParam(pParticala, v6);
                  p_m_bActive->m_pCamControl = (CCBCamControl *)pParticala;
                  p_m_bActive->m_pScene = v26;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v8 - 64) == 4 )
              {
                *(_DWORD *)(*(_DWORD *)((char *)&p_m_bActive->m_pCam->fov + v28) + v7 + 8) = 3;
                *(_DWORD *)(*(_DWORD *)((char *)&p_m_bActive->m_pCam->fov + v28) + v7 + 16) = p_m_bActive->m_pRoleState;
LABEL_21:
                p_m_bActive->m_pScene = (CCBStageScene *)v6;
                p_m_bActive->m_pCamControl = (CCBCamControl *)pParticala;
LABEL_24:
                ((void ( *)(CCBStage *, _DWORD, _DWORD, _DWORD))p_m_bActive->m_pCBSystem->m_pUI)(
                  p_m_bActive,
                  *(_DWORD *)(*(_DWORD *)v5 + v7),
                  *(_DWORD *)(*(_DWORD *)v5 + v7 + 4),
                  0);
              }
            }
            break;
          case 3:
            goto LABEL_21;
          case 4:
            if ( ((CCBStage *)p_m_bActive)->SetTaskState(pParticala) )
            {
              v9 = *((_DWORD *)v5 + 1);
              *((_DWORD *)v5 + 3) = 4;
              v10 = 9 * v9;
              LOBYTE(v9) = v5[149];
              *((_DWORD *)v5 + 5) = *(_DWORD *)(*(_DWORD *)v5 + 8 * v10 - 12);
              if ( (_BYTE)v9 == 1 )
              {
                ((CEffgbParticle *)p_m_bActive)->Init(pParticala);
                goto LABEL_28;
              }
            }
            break;
        }
        v6 = (int)&v26->m_pStage + 1;
        v7 += 72;
        v26 = (CCBStageScene *)((char *)v26 + 1);
        if ( (int)v26 >= (int)p_m_bActive->m_pRole[2] )
          goto LABEL_28;
      }
    }
LABEL_30:
    if ( *(int *)&this->m_Partical[0].bValid <= 0 )
      this->m_eKind = (EEffect)1;
    if ( !*(_BYTE *)&this->m_eKind )
    {
      *(float *)&this->m_Partical[1].pPic = *(float *)&this->m_Partical[2].dwColor * *((float *)&this->m_DeltaTime + 1)
                                        + *(float *)&this->m_Partical[1].pPic;
      if ( (g_bEffSystemFlags & 1) == 0 )
      {
        g_bEffSystemFlags |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      v12 = 0;
      v13 = (int)abs32((int)*(float *)&this->m_Partical[1].pPic) % HIBYTE(this->m_Partical[0].fZ);
      fY_low = LODWORD(this->m_Partical[1].fY);
      v15 = (float *)((char *)v2 + 16 * v13);
      v16 = &this->m_Partical[3].fCurFrame + 4 * v13;
      fZ_low = LODWORD(this->m_Partical[1].fZ);
      v20 = v15;
      v21 = v16;
      pParticalb = 0;
      v29 = (v15[50] - *v16) * (1.0 / (double)fY_low);
      v27 = (v15[51] - v15[49]) * (1.0 / (double)fZ_low);
      if ( fZ_low > 0 )
      {
        do
        {
          v17 = *v16;
          v18 = 0;
          v25 = (double)pParticalb * v27 + v15[49];
          if ( fY_low > 0 )
          {
            v19 = 68 * v12;
            do
            {
              ++v12;
              *(float *)(v19 + LODWORD(this->m_Partical[0].fCurFrame) + 48) = v17;
              v17 = v17 + v29;
              v19 += 68;
              ++v18;
              *(float *)(v19 + LODWORD(this->m_Partical[0].fCurFrame) - 12) = v17;
              *(float *)(v19 + LODWORD(this->m_Partical[0].fCurFrame) - 16) = v25;
              v22 = v27 + v25;
              *(float *)(v19 + LODWORD(this->m_Partical[0].fCurFrame) - 8) = v22;
              *(_DWORD *)(v19 + LODWORD(this->m_Partical[0].fCurFrame) - 4) = this->m_Partical[1].nQuadIndex;
              fY_low = LODWORD(this->m_Partical[1].fY);
            }
            while ( v18 < fY_low );
            v16 = v21;
            v15 = v20;
          }
          ++pParticalb;
        }
        while ( pParticalb < SLODWORD(this->m_Partical[1].fZ) );
      }
    }
  }
}

// 0x004C7450
void CEffect::FillQuadByPartical(int *nParticalIndex)
{
  _BYTE *p_m_bActive; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  p_m_bActive = &this->m_bActive;
  v3 = *(_DWORD *)&this->m_Partical[0].byMaxFrame;
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *((_DWORD *)p_m_bActive + 3);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*((_DWORD *)p_m_bActive + 3) + v7 + 148) = 1;
    *(_BYTE *)(*((_DWORD *)p_m_bActive + 3) + v7 + 149) = 1;
    v8 = ++g_PAL3.m_nCEffCylinderCount;
    if ( !g_PAL3.m_nCEffCylinderCount || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_PAL3.m_nCEffCylinderCount = 1;
    }
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 16) = v8;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4) = 0;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 8) = 0;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 20) = 0;
    if ( nParticalIndex )
      qmemcpy((void *)(*((_DWORD *)p_m_bActive + 3) + v7 + 24), nParticalIndex, 0x7Cu);
    else
      memset((void *)(*((_DWORD *)p_m_bActive + 3) + v7 + 24), 0, 0x7Cu);
    ++*((_DWORD *)p_m_bActive + 6);
    if ( v4 != -1 )
    {
      v9 = *((_DWORD *)p_m_bActive + 8);
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_PAL3.m_nCEffCylinderCount;
        if ( !g_PAL3.m_nCEffCylinderCount || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_PAL3.m_nCEffCylinderCount = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4);
      }
LABEL_22:
      v15 = *((_DWORD *)p_m_bActive + 8);
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_PAL3.m_nCEffCylinderCount;
        if ( !g_PAL3.m_nCEffCylinderCount || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_PAL3.m_nCEffCylinderCount = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4);
      }
LABEL_31:
      ((CEffgbParticle *)p_m_bActive)->_CEffgbParticle(v4, (int)ProcCommonTask__ovl, 0, 0, nParticalIndex[18], nParticalIndex[19]);
      *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7) + 16) = *((_DWORD *)p_m_bActive + 1);
    }
  }
}

// 0x004CA400
int CEffect::SetParam(int nVal)
{
  int v2; // edx
  char v3; // bl
  int v4; // edx

  v2 = *(_DWORD *)(this->m_nPartical + 152 * (int)this->m_Partical[0].pPic);
  v3 = *(_BYTE *)(v2 + 72 * this->m_Partical[0].nQuadIndex + 65);
  v4 = v2 + 72 * this->m_Partical[0].nQuadIndex;
  if ( !v3 )
    *(_BYTE *)(v4 + 65) = 1;
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->m_DeltaTime - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004CE460
int CEffect::Render(int nVal)
{
  int result; // eax
  int v3; // esi
  unsigned int v4; // ebx
  int Effect; // edi
  int *v6; // esi
  int v7; // ebp
  bool v8; // cc
  int *v9; // [esp+0x8] [ebp-0x10]
  int v11; // [esp+0x10] [ebp-0x8]
  int v12; // [esp+0x14] [ebp-0x4]
  int *nVala; // [esp+0x1C] [ebp+0x4]

  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  result = g_nCEffect_1895980;
  if ( g_nCEffect_1895980 == -1 )
    result = 1;
  v3 = result;
  g_nCEffect_1895980 = result + 1;
  v12 = result;
  v11 = 0;
  v4 = 15940 * nVal;
  if ( *(&g_nSaveSlot0 + 3985 * nVal) > 0 )
  {
    v9 = &g_nSaveSlotBase[v4 / 4];
    nVala = (int *)((char *)&g_nSaveSlot1 + v4);
    do
    {
      Effect = ((CEffMgr *)this)->CreateEffect(*nVala, v3, 0, 0, 0);
      if ( Effect != -1 )
      {
        v6 = v9;
        v7 = 8;
        do
        {
          if ( *((_BYTE *)v6 + 88) )
            (*(void ( **)(_DWORD, int *))(**((_DWORD **)&this->m_Partical[48].fFramePerSec + 5 * Effect) + 36))(
              *((_DWORD *)&this->m_Partical[48].fFramePerSec + 5 * Effect),
              v6);
          v6 += 31;
          --v7;
        }
        while ( v7 );
        v3 = v12;
      }
      v8 = ++v11 < *(int *)((char *)&g_nSaveSlot0 + v4);
      ++nVala;
      v9 += 248;
    }
    while ( v8 );
    return v3;
  }
  return result;
}

// 0x004CFE20
int CEffect::_nearby_4cfe20(int thisa, int a2, float a3, float a4, float a5)
{
  int result; // eax
  float fCurFrame; // ecx

  this->m_eKind = 0;
  this->m_Partical[1].byMaxFrame = 0;
  *(float *)&this->m_Partical[0].dwColor = *(float *)&a2 + *(float *)(thisa + 184);
  this->m_Partical[0].fX = a3 + *(float *)(thisa + 188);
  this->m_Partical[0].fY = a4 + *(float *)(thisa + 192);
  *(_DWORD *)&this->m_Partical[0].byAlpha = 0;
  this->m_Partical[0].fSize = 0.0;
  this->m_Partical[0].fZ = 0.0;
  this->m_Partical[1].pPic = *(char **)(thisa + 216);
  this->m_Partical[1].nQuadIndex = *(_DWORD *)(thisa + 196);
  *(_DWORD *)&this->m_Partical[1].bValid = *(_DWORD *)(thisa + 220);
  this->m_Partical[1].fFramePerSec = *(float *)(thisa + 200);
  this->m_Partical[1].fCurFrame = *(float *)(thisa + 200);
  result = *(_DWORD *)(thisa + 200);
  this->m_Partical[1].dwColor = result;
  fCurFrame = this->m_Partical[0].fCurFrame;
  if ( fCurFrame != 0.0 )
    return (*(int ( **)(float, _DWORD))(*(_DWORD *)LODWORD(fCurFrame) + 24))(
             COERCE_FLOAT(LODWORD(fCurFrame)),
             0);
  return result;
}

// 0x004CFFB0
void CEffect::_nearby_4cffb0(int thisa, float a2)
{
  float *p_m_bActive; // esi
  int v4; // ebx
  int *v5; // ebp
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // edx
  _DWORD *v12; // eax
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  float fCurFrame; // ecx
  int v18; // [esp+0xC] [ebp-0x8]
  CEffect *v19; // [esp+0x10] [ebp-0x4]
  int thisb; // [esp+0x18] [ebp+0x4]

  p_m_bActive = (float *)&this->m_bActive;
*((float *)&this->m_DeltaTime + 1) = *(float *)&thisa - *(float *)&this->m_DeltaTime;
  *(float *)&this->m_DeltaTime = *(float *)&thisa;
  if ( *((float *)&this->m_DeltaTime + 1) <= 0.0 )
    return;
  v4 = 0;
  thisb = 0;
  if ( *(int *)&this->m_Partical[0].byMaxFrame <= 0 )
    goto LABEL_35;
  do
  {
    v5 = (int *)(v4 + *((_DWORD *)p_m_bActive + 3));
    if ( *((_BYTE *)v5 + 148) )
    {
      if ( v5[3] == 3 )
      {
        v6 = 0;
        v18 = 0;
        if ( *((int *)p_m_bActive + 8) > 0 )
        {
          v7 = 0;
          do
          {
            v8 = *v5;
            if ( !*(_BYTE *)(v7 + *v5 + 64) || v7 > 0 && *(_DWORD *)(v7 + v8 - 64) == 2 )
              break;
            switch ( *(_DWORD *)(v7 + v8 + 8) )
            {
              case 2:
                if ( v7 > 0 )
                {
                  if ( *(float *)(v7 + v8 + 20) >= 0.0 )
                  {
                    if ( p_m_bActive[1] - *(float *)(v7 + v8 - 56) > *(float *)(v7 + v8 + 20) )
                    {
LABEL_25:
                      *(_DWORD *)(*(_DWORD *)(v4 + *((_DWORD *)p_m_bActive + 3)) + v7 + 8) = 3;
                      *(float *)(*(_DWORD *)(v4 + *((_DWORD *)p_m_bActive + 3)) + v7 + 16) = p_m_bActive[1];
                      *((_DWORD *)p_m_bActive + 4) = thisb;
                      *((_DWORD *)p_m_bActive + 5) = v18;
                      goto LABEL_26;
                    }
                  }
                  else if ( *(_DWORD *)(v7 + v8 - 64) == 4 )
                  {
                    goto LABEL_25;
                  }
                }
                break;
              case 3:
                *((_DWORD *)p_m_bActive + 5) = v6;
                *((_DWORD *)p_m_bActive + 4) = thisb;
LABEL_26:
                (*(void ( **)(float *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)p_m_bActive + 4))(
                  p_m_bActive,
                  *(_DWORD *)(*v5 + v7),
                  *(_DWORD *)(*v5 + v7 + 4),
                  0);
                break;
              case 4:
                v9 = 0;
                v10 = (_DWORD *)(v4 + *((_DWORD *)p_m_bActive + 3));
                v11 = v10[1];
                if ( v11 <= 0 )
                {
LABEL_17:
                  v13 = v5[1];
                  v5[3] = 4;
                  v14 = 9 * v13;
                  LOBYTE(v13) = *((_BYTE *)v5 + 149);
                  v5[5] = *(_DWORD *)(*v5 + 8 * v14 - 12);
                  if ( (_BYTE)v13 == 1 )
                  {
                    v15 = 0;
                    *(_BYTE *)(v4 + *((_DWORD *)p_m_bActive + 3) + 148) = 0;
                    if ( *((int *)p_m_bActive + 8) > 0 )
                    {
                      v16 = 0;
                      do
                      {
                        ++v15;
                        v16 += 72;
                        *(_BYTE *)(*(_DWORD *)(v4 + *((_DWORD *)p_m_bActive + 3)) + v16 - 8) = 0;
                      }
                      while ( v15 < *((_DWORD *)p_m_bActive + 8) );
                    }
                    *(_DWORD *)(v4 + *((_DWORD *)p_m_bActive + 3) + 4) = 0;
                    --*((_DWORD *)p_m_bActive + 6);
                    goto LABEL_33;
                  }
                }
                else
                {
                  v12 = (_DWORD *)(*v10 + 8);
                  while ( *v12 == 4 )
                  {
                    ++v9;
                    v12 += 18;
                    if ( v9 >= v11 )
                      goto LABEL_17;
                  }
                }
                break;
            }
            v6 = v18 + 1;
            v7 += 72;
            ++v18;
          }
          while ( v18 < *((_DWORD *)p_m_bActive + 8) );
        }
      }
    }
LABEL_33:
    v4 += 152;
    ++thisb;
  }
  while ( thisb < *((_DWORD *)p_m_bActive + 7) );
  this = v19;
LABEL_35:
  if ( *(int *)&this->m_Partical[0].bValid <= 0 )
  {
    this->m_eKind = (EEffect)1;
    this->m_Partical[1].byMaxFrame = 0;
  }
  fCurFrame = this->m_Partical[0].fCurFrame;
  if ( fCurFrame != 0.0 )
    (*(void ( **)(float))(*(_DWORD *)LODWORD(fCurFrame) + 20))(COERCE_FLOAT(LODWORD(fCurFrame)));
}

// 0x004D0D70
CEffect * CEffect::SetTimeScale()
{
  CEffModel *v1; // eax

  v1 = (CEffModel *)operator new(0x10B0u);
  if ( v1 )
    return (CEffect *)((CEffModel *)v1)->Reset();
  else
    return 0;
}

// 0x004D0DB0
void CEffect::UpdateCallback()
{
  _BYTE *p_m_bActive; // edi
  float fY; // eax
  int v4; // ebp
  gbRefObject *v5; // ecx
  _BYTE *v6; // esi
  int v7; // eax
  bool v8; // cc
  int v9; // edi

  p_m_bActive = &this->m_bActive;
  fY = this->m_Partical[2].fY;
  v4 = 0;
  if ( fY != 0.0 )
    operator delete((void *)LODWORD(fY));
  if ( LODWORD(this->m_Partical[2].fZ) )
    operator delete((void *)LODWORD(this->m_Partical[2].fZ));
  if ( LODWORD(this->m_Partical[2].fSize) )
    operator delete((void *)LODWORD(this->m_Partical[2].fSize));
  v5 = *(gbRefObject **)&this->m_Partical[88].byMaxFrame;
  if ( v5 )
    ((gbRefObject *)v5)->Release();
  if ( LODWORD(this->m_Partical[88].fFramePerSec) )
    operator delete((void *)LODWORD(this->m_Partical[88].fFramePerSec));
  v6 = this != 0 ? p_m_bActive : 0;
  v7 = *((_DWORD *)v6 + 7);
  v8 = v7 <= 0;
  if ( !v7 )
  {
    if ( !*(this != 0 ? (_DWORD *)(p_m_bActive + 32) : (_DWORD *)32) )
      return;
    v8 = 1;
  }
  if ( !v8 )
  {
    v9 = 0;
    do
    {
      operator delete(*(void **)(*((_DWORD *)v6 + 3) + v9));
      ++v4;
      *(_DWORD *)(*((_DWORD *)v6 + 3) + v9) = 0;
      v9 += 152;
    }
    while ( v4 < *((_DWORD *)v6 + 7) );
  }
  operator delete(*((void **)v6 + 3));
  *((_DWORD *)v6 + 3) = 0;
  *((_DWORD *)v6 + 7) = 0;
  *((_DWORD *)v6 + 8) = 0;
}

// 0x004D0EC0
int CEffect::ProcInitTask(float *dwParam, float fVal, float fVal2, float fVal3)
{
  int v7; // edx
  double v8; // st7

  LOBYTE(this->m_Partical[0].fCurFrame) = 1;
  BYTE1(this->m_Partical[0].fCurFrame) = 1;
  this->m_eKind = 0;
  HIBYTE(this->m_Partical[0].fCurFrame) = *((_BYTE *)dwParam + 214);
  ((CCBStage *)this)->GetActiveTaskCount();
  this->m_Partical[1].nQuadIndex = 257;
  this->m_Partical[2].fX = dwParam[51];
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *(float *)&this->m_Partical[2].byMaxFrame = (float)HIBYTE(*((_DWORD *)dwParam + 51));
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_Partical[2].fFramePerSec = (float)(unsigned __int8)BYTE2(*((_DWORD *)dwParam + 51));
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_Partical[2].fCurFrame = (float)(unsigned __int8)BYTE1(*((_DWORD *)dwParam + 51));
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  v7 = *((unsigned __int8 *)dwParam + 204);
  *(_DWORD *)&this->m_Partical[1].byMaxFrame = 0;
  *(float *)&this->m_Partical[2].dwColor = (float)v7;
  *(float *)&this->m_Partical[1].bValid = dwParam[45];
  this->m_Partical[2].pPic = (char *)dwParam[49];
  this->m_Partical[2].nQuadIndex = (int)dwParam[54];
  *(float *)&this->m_Partical[2].bValid = dwParam[55];
  this->m_Partical[1].fX = dwParam[50];
  this->m_Partical[1].fY = dwParam[50];
  this->m_Partical[1].fFramePerSec = fVal + dwParam[46];
  this->m_Partical[1].fCurFrame = fVal2 + dwParam[47];
  v8 = fVal3 + dwParam[48];
  this->m_Partical[1].fZ = 0.0;
  this->m_Partical[1].fSize = 0.0;
  *(_DWORD *)&this->m_Partical[1].byAlpha = 0;
  this->m_Partical[1].pPic = 0;
  *(float *)&this->m_Partical[1].dwColor = v8;
  return 0;
}

// 0x004D1090
char CEffect::Create(tagEffObjType *pEffObjType)
{
  int nMaxQuad; // ebp
  void *v4; // eax
  int v5; // ebp
  int v6; // ebx
  int v7; // ebp
  void *v8; // eax
  float fY; // ecx
  int i; // eax
  void *v11; // eax
  int v12; // ebx
  int v13; // edi
  int v14; // edi
  int v15; // edx
  int v16; // eax
  int v17; // ecx
  int v19; // edi
  size_t v20; // [esp-0x4] [ebp-0x824]
  void *v21; // [esp+0x10] [ebp-0x810]
  char pExceptionObject[1024]; // [esp+0x14] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x414] [ebp-0x40C] BYREF
  int v24; // [esp+0x81C] [ebp-0x4]

  BYTE2(this->m_Partical[0].fCurFrame) = 1;
  BYTE1(this->m_Partical[0].dwColor) = pEffObjType->bNoZTest;
  LOBYTE(this->m_Partical[0].dwColor) = pEffObjType->bAdditiveBlend;
  BYTE2(this->m_Partical[0].dwColor) = pEffObjType->nFrame;
  LODWORD(this->m_Partical[0].fX) = (unsigned long)&byte_FFFFFF;
  sub_4D1FD0(pEffObjType->nFramePerRow, pEffObjType->nFramePerCol);
  LODWORD(this->m_Partical[2].fY) = operator new(80 * pEffObjType->nMaxQuad);
  nMaxQuad = pEffObjType->nMaxQuad;
  v4 = operator new(68 * nMaxQuad);
  v21 = v4;
  v24 = 0;
  if ( v4 )
  {
    v5 = nMaxQuad - 1;
    v6 = (int)v4;
    if ( v5 >= 0 )
    {
      v7 = v5 + 1;
      do
      {
        v6 += 68;
        --v7;
      }
      while ( v7 );
      v4 = v21;
    }
  }
  else
  {
    v4 = 0;
  }
  LODWORD(this->m_Partical[2].fZ) = v4;
  v20 = 4 * pEffObjType->nMaxQuad;
  v24 = -1;
  v8 = operator new(v20);
  fY = this->m_Partical[2].fY;
  LODWORD(this->m_Partical[2].fSize) = v8;
  if ( fY == 0.0 || !LODWORD(this->m_Partical[2].fZ) || !v8 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException((char *)&pTarget.m_pfnUpdatePost + 8, (char *)&pTarget._todo_184 + 8, 127),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  LODWORD(this->m_Partical[0].fSize) = pEffObjType->nMaxQuad;
  ((CCBStage *)this)->GetActiveTaskCount();
  for ( i = 0; i < SLODWORD(this->m_Partical[0].fSize); ++i )
    *(_DWORD *)(LODWORD(this->m_Partical[2].fSize) + 4 * i) = i;
  ((CEffQuad *)this)->ToNextFrame((int)pEffObjType->szTexture);
  v11 = operator new(0x4C0u);
  this->m_nPartical = (int)v11;
  if ( v11 )
  {
    v12 = 0;
    v13 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v13 + this->m_nPartical) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v13 + this->m_nPartical) )
        break;
      v13 += 152;
      ++v12;
      if ( v13 >= 1216 )
      {
        v14 = 0;
        *(_DWORD *)&this->m_Partical[0].byMaxFrame = 8;
        LODWORD(this->m_Partical[0].fFramePerSec) = 10;
        v15 = 0;
        do
        {
          *(_BYTE *)(v15 + this->m_nPartical + 148) = 0;
          v16 = 0;
          if ( SLODWORD(this->m_Partical[0].fFramePerSec) > 0 )
          {
            v17 = 0;
            do
            {
              ++v16;
              v17 += 72;
              *(_BYTE *)(*(_DWORD *)(v15 + this->m_nPartical) + v17 - 8) = 0;
            }
            while ( v16 < SLODWORD(this->m_Partical[0].fFramePerSec) );
          }
          ++v14;
          v15 += 152;
        }
        while ( v14 < *(_DWORD *)&this->m_Partical[0].byMaxFrame );
        return 1;
      }
    }
    if ( v12 > 0 && v12 - 1 >= 0 )
    {
      v19 = 152 * (v12 - 1);
      do
      {
        operator delete(*(void **)(v19 + this->m_nPartical));
        v19 -= 152;
        --v12;
      }
      while ( v12 );
    }
    operator delete((void *)this->m_nPartical);
  }
  return 1;
}

// 0x004D2080
int CEffect::CreateTask(int *p)
{
  _DWORD *p_m_bActive; // ebp
  int v3; // edx
  int result; // eax
  int m_nPartical; // esi
  _BYTE *i; // ecx
  int v7; // ebx
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // esi
  _BYTE *v12; // edi
  int ( **v13)(CEffect *, int); // edx
  unsigned int v14; // eax
  int v15; // edx
  int v16; // ecx
  _DWORD *v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // esi
  _BYTE *v21; // edi
  int ( **v22)(CEffect *, int); // edx
  unsigned int v23; // eax
  int v24; // edx
  int v25; // ecx
  _DWORD *v26; // eax
  int v27; // [esp+0x10] [ebp-0xC]

  p_m_bActive = &this->m_bActive;
  v3 = 0;
  LODWORD(this->m_Partical[0].fX) = p[20];
  result = *(_DWORD *)&this->m_Partical[0].byMaxFrame;
  if ( result > 0 )
  {
    m_nPartical = this->m_nPartical;
    for ( i = (_BYTE *)(m_nPartical + 148); *i; i += 152 )
    {
      if ( ++v3 >= result )
        return result;
    }
    v27 = v3;
    v7 = 152 * v3;
    *(_DWORD *)(m_nPartical + v7 + 12) = 2;
    *(_BYTE *)(p_m_bActive[3] + v7 + 148) = 1;
    *(_BYTE *)(p_m_bActive[3] + v7 + 149) = 1;
    v8 = ++g_nSceneObjCount;
    if ( !g_nSceneObjCount || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nSceneObjCount = 1;
    }
    *(_DWORD *)(p_m_bActive[3] + v7 + 16) = v8;
    *(_DWORD *)(p_m_bActive[3] + v7 + 4) = 0;
    *(_DWORD *)(p_m_bActive[3] + v7 + 8) = 0;
    *(_DWORD *)(p_m_bActive[3] + v7 + 20) = 0;
    if ( p )
    {
      result = p_m_bActive[3];
      qmemcpy((void *)(result + v7 + 24), p, 0x7Cu);
    }
    else
    {
      result = 0;
      memset((void *)(p_m_bActive[3] + v7 + 24), 0, 0x7Cu);
    }
    ++p_m_bActive[6];
    if ( v3 != -1 )
    {
      v9 = p_m_bActive[8];
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(v7 + p_m_bActive[3]);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *((_BYTE *)v13 + 65) = 0;
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nSceneObjCount;
        if ( !g_nSceneObjCount || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nSceneObjCount = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        v15 = p_m_bActive[3];
        v16 = *(_DWORD *)(v7 + v15 + 4);
        v17 = (_DWORD *)(v7 + v15 + 4);
        v3 = v27;
        *v17 = v16 + 1;
      }
LABEL_22:
      v18 = p_m_bActive[8];
      v19 = 0;
      if ( v18 > 0 )
      {
        v20 = *(_DWORD *)(p_m_bActive[3] + v7);
        v21 = (_BYTE *)(v20 + 64);
        while ( *v21 )
        {
          ++v19;
          v21 += 72;
          if ( v19 >= v18 )
            goto LABEL_31;
        }
        v22 = (int ( **)(CEffect *, int))(v20 + 72 * v19);
        memset(v22, 0, 0x48u);
        *((_BYTE *)v22 + 64) = 1;
        *v22 = CEffect::SetParam;
        *((_BYTE *)v22 + 65) = 0;
        v22[1] = 0;
        v22[2] = (int ( *)(CEffect *, int))2;
        v23 = ++g_nSceneObjCount;
        if ( !g_nSceneObjCount || v23 >= 0x7FFFFFFF )
        {
          v23 = 1;
          g_nSceneObjCount = 1;
        }
        v22[3] = (int ( *)(CEffect *, int))v23;
        v22[5] = 0;
        v22[4] = 0;
        v22[6] = 0;
        v24 = p_m_bActive[3];
        v25 = *(_DWORD *)(v24 + v7 + 4);
        v26 = (_DWORD *)(v24 + v7 + 4);
        v3 = v27;
        *v26 = v25 + 1;
      }
LABEL_31:
      sub_4D3010(v3, CEffMgr::UpdateKeyframe, 0, 0, p[18], p[19]);
      sub_4D3010(v27, CEffQuad::ProcessDestroyPass, 0, 0, 0, p[19]);
      *(_DWORD *)(p_m_bActive[3] + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(p_m_bActive[3] + v7) + 8) = 3;
      result = *(_DWORD *)(p_m_bActive[3] + v7);
      *(_DWORD *)(result + 16) = p_m_bActive[1];
    }
  }
  return result;
}

// 0x004D2ED0
int CEffect::sub_4D2ED0(int a2)
{
  int result; // eax

  switch ( a2 )
  {
    case 0:
      result = (int)dword_5D5050;
      break;
    case 1:
      result = (int)dword_5D4E40;
      break;
    case 2:
      result = (int)dword_5D4E38;
      break;
    case 3:
      result = (int)dword_5D4E30;
      break;
    case 4:
      result = (int)dword_5D4E24;
      break;
    case 5:
      result = (int)dword_5D5048;
      break;
    case 6:
      result = (int)dword_5D5040;
      break;
    case 7:
      result = (int)dword_5D5038;
      break;
    case 8:
      result = (int)dword_5D4E00;
      break;
    case 9:
      result = (int)&g_EffEditorState;
      break;
    case 10:
      result = (int)(&pTarget.m_pfnStageCleanup + 4);
      break;
    case 11:
      result = (int)dword_5D5020;
      break;
    case 12:
      result = (int)dword_5D4DD4;
      break;
    case 13:
      result = (int)dword_5D4DCC;
      break;
    case 14:
      result = (int)dword_5D4DC4;
      break;
    case 15:
      result = (int)dword_5D4DB8;
      break;
    case 16:
      result = (int)dword_5D4DAC;
      break;
    case 17:
      result = (int)dword_5D5014;
      break;
    case 18:
      result = (int)dword_5D5008;
      break;
    case 19:
      result = (int)dword_5D4FFC;
      break;
    case 20:
      result = (int)&g_pszEditorDesc;
      break;
    case 21:
      result = (int)dword_5D4FF0;
      break;
    case 22:
      result = (int)dword_5D4FE0;
      break;
    case 23:
      result = (int)dword_5D4FD0;
      break;
    default:
      result = (int)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004D3950
void CEffect::DestroyCallback()
{
  _BYTE *p_m_bActive; // edi
  char *pPic; // eax
  int v4; // ebp
  float fZ; // ecx
  _BYTE *v6; // esi
  int v7; // eax
  bool v8; // cc
  int v9; // edi

  p_m_bActive = &this->m_bActive;
  pPic = this->m_Partical[86].pPic;
  v4 = 0;
  if ( pPic )
    operator delete(pPic);
  if ( this->m_Partical[86].nQuadIndex )
    operator delete((void *)this->m_Partical[86].nQuadIndex);
  fZ = this->m_Partical[85].fZ;
  if ( fZ != 0.0 )
    ((gbRefObject *)LODWORD(fZ))->Release();
  if ( LODWORD(this->m_Partical[85].fSize) )
    operator delete((void *)LODWORD(this->m_Partical[85].fSize));
  v6 = this != 0 ? p_m_bActive : 0;
  v7 = *((_DWORD *)v6 + 7);
  v8 = v7 <= 0;
  if ( !v7 )
  {
    if ( !*(this != 0 ? (_DWORD *)(p_m_bActive + 32) : (_DWORD *)32) )
      return;
    v8 = 1;
  }
  if ( !v8 )
  {
    v9 = 0;
    do
    {
      operator delete(*(void **)(*((_DWORD *)v6 + 3) + v9));
      ++v4;
      *(_DWORD *)(*((_DWORD *)v6 + 3) + v9) = 0;
      v9 += 152;
    }
    while ( v4 < *((_DWORD *)v6 + 7) );
  }
  operator delete(*((void **)v6 + 3));
  *((_DWORD *)v6 + 3) = 0;
  *((_DWORD *)v6 + 7) = 0;
  *((_DWORD *)v6 + 8) = 0;
}

// 0x004D3A50
int CEffect::Init(float *pType, float fx, float fy, float fz)
{
  int result; // eax

  this->m_eKind = 0;
  this->m_Partical[87].nQuadIndex = (int)pType[50];
  this->m_Partical[87].fCurFrame = fx + pType[46];
  *(float *)&this->m_Partical[87].dwColor = fy + pType[47];
  this->m_Partical[87].fX = fz + pType[48];
  *(float *)&this->m_Partical[87].bValid = pType[54];
  *(float *)&this->m_Partical[87].byMaxFrame = pType[49];
  this->m_Partical[87].fFramePerSec = pType[55];
  result = *((_DWORD *)pType + 51);
  LODWORD(this->m_Partical[86].fY) = result;
  return result;
}

// 0x004D3AD0
char CEffect::Create_3ad0(tagEffObjType *pEffObjType)
{
  void *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // ebx
  char *v12; // eax
  int v13; // ebx
  int v14; // ebp
  int v15; // ebx
  int v16; // edi
  void *v17; // eax
  char *pPic; // ecx
  size_t v20; // [esp-0x4] [ebp-0x820]
  char *v21; // [esp+0xC] [ebp-0x810]
  char pExceptionObject[1024]; // [esp+0x10] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x410] [ebp-0x40C] BYREF
  int v24; // [esp+0x818] [ebp-0x4]

  v3 = operator new(0x4C0u);
  this->m_nPartical = (int)v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v5 + this->m_nPartical) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v5 + this->m_nPartical) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *(_DWORD *)&this->m_Partical[0].byMaxFrame = 8;
        LODWORD(this->m_Partical[0].fFramePerSec) = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(v7 + this->m_nPartical + 148) = 0;
          v8 = 0;
          if ( SLODWORD(this->m_Partical[0].fFramePerSec) > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(*(_DWORD *)(v7 + this->m_nPartical) + v9 - 8) = 0;
            }
            while ( v8 < SLODWORD(this->m_Partical[0].fFramePerSec) );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *(_DWORD *)&this->m_Partical[0].byMaxFrame );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v16 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v16 + this->m_nPartical));
        v16 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete((void *)this->m_nPartical);
  }
LABEL_10:
  *(_DWORD *)&this->m_Partical[87].byAlpha = (__int64)pEffObjType->fSacleX;
  this->m_Partical[88].pPic = (char *)(__int64)pEffObjType->fSacleY;
  this->m_Partical[88].nQuadIndex = LODWORD(pEffObjType->fSacleZ);
  *(float *)&this->m_Partical[88].bValid = pEffObjType->fTopRadius;
  v10 = *(_DWORD *)&this->m_Partical[87].byAlpha * (int)this->m_Partical[88].pPic;
  *(float *)&this->m_Partical[88].byMaxFrame = pEffObjType->fBottomRadius;
  this->m_Partical[88].fFramePerSec = pEffObjType->fTextureRepeat;
  *(_DWORD *)&this->m_Partical[85].byAlpha = v10;
  *(float *)&this->m_Partical[86].byMaxFrame = pEffObjType->fFramePerSec;
  this->m_Partical[87].fCurFrame = pEffObjType->fX;
  this->m_Partical[87].dwColor = LODWORD(pEffObjType->fY);
  this->m_Partical[87].fX = pEffObjType->fZ;
  *(float *)&this->m_Partical[87].bValid = pEffObjType->fStartXRot;
  *(float *)&this->m_Partical[87].byMaxFrame = pEffObjType->fStartYRot;
  this->m_Partical[87].fFramePerSec = pEffObjType->fStartZRot;
  this->m_Partical[86].bVisible = pEffObjType->bAdditiveBlend;
  this->m_Partical[86].bAniFrame = pEffObjType->bNoZTest;
  LOBYTE(this->m_Partical[86].fFramePerSec) = pEffObjType->nFrame;
  LODWORD(this->m_Partical[86].fCurFrame) = 0xFFFF;
  LODWORD(this->m_Partical[86].fY) = pEffObjType->dwColor;
  ((CEffShock *)this)->CreateGeom(pEffObjType->nFramePerRow, pEffObjType->nFramePerCol);
  v11 = *(_DWORD *)&this->m_Partical[85].byAlpha;
  v12 = (char *)operator new(68 * v11);
  v21 = v12;
  v24 = 0;
  if ( v12 )
  {
    v13 = v11 - 1;
    v14 = (int)v12;
    if ( v13 >= 0 )
    {
      v15 = v13 + 1;
      do
      {
        v14 += 68;
        --v15;
      }
      while ( v15 );
      v12 = v21;
    }
  }
  else
  {
    v12 = 0;
  }
  this->m_Partical[86].pPic = v12;
  v20 = 8 * *(_DWORD *)&this->m_Partical[85].byAlpha;
  v24 = -1;
  v17 = operator new(v20);
  pPic = this->m_Partical[86].pPic;
  this->m_Partical[86].nQuadIndex = (int)v17;
  if ( !pPic || !v17 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException((char *)&pTarget.m_pfnStageCleanup + 88, (char *)&pTarget.m_nTargetType + 12, 91),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  sub_4D4AB0(pEffObjType->szTexture);
  sub_4D48B0(this);
  return 1;
}

// 0x004D4340
void CEffect::CreateTarget(int *pnVal)
{
  _BYTE *p_m_bActive; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  p_m_bActive = &this->m_bActive;
  v3 = *(_DWORD *)&this->m_Partical[0].byMaxFrame;
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *((_DWORD *)p_m_bActive + 3);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*((_DWORD *)p_m_bActive + 3) + v7 + 148) = 1;
    *(_BYTE *)(*((_DWORD *)p_m_bActive + 3) + v7 + 149) = 1;
    v8 = ++g_nEffShockCount;
    if ( !g_nEffShockCount || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nEffShockCount = 1;
    }
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 16) = v8;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4) = 0;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 8) = 0;
    *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 20) = 0;
    if ( pnVal )
      qmemcpy((void *)(*((_DWORD *)p_m_bActive + 3) + v7 + 24), pnVal, 0x7Cu);
    else
      memset((void *)(*((_DWORD *)p_m_bActive + 3) + v7 + 24), 0, 0x7Cu);
    ++*((_DWORD *)p_m_bActive + 6);
    if ( v4 != -1 )
    {
      v9 = *((_DWORD *)p_m_bActive + 8);
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nEffShockCount;
        if ( !g_nEffShockCount || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nEffShockCount = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4);
      }
LABEL_22:
      v15 = *((_DWORD *)p_m_bActive + 8);
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_nEffShockCount;
        if ( !g_nEffShockCount || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nEffShockCount = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 4);
      }
LABEL_31:
      ((CEffShock *)p_m_bActive)->LoadTexture(v4, 0 /* TODO: (int)CEffShock::UpdateSegment */, 0, 0, pnVal[18], pnVal[19]);
      *(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)p_m_bActive + 3) + v7) + 16) = *((_DWORD *)p_m_bActive + 1);
    }
  }
}

// 0x0053D580
void CEffect::ReleaseResources()
{
  int v2; // ebp
  _BYTE *p_byMaxFrame; // edi
  gbRefObject **v4; // esi
  char *pPic; // ecx

  v2 = 6;
  p_byMaxFrame = &this->m_Partical[1].byMaxFrame;
  v4 = (gbRefObject **)&this->m_Partical[1].byMaxFrame;
  do
  {
    if ( *v4 )
      ((gbRefObject *)*v4)->Release();
    ++v4;
    --v2;
  }
  while ( v2 );
  memset(p_byMaxFrame, 0, 0x18u);
  pPic = this->m_Partical[2].pPic;
  if ( pPic )
  {
    ((gbRefObject *)pPic)->Release();
    this->m_Partical[2].pPic = 0;
  }
}
