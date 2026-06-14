#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/RoleSystem.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations
int sub_401070(...);
int sub_407EC0(...);
int sub_408010(...);
int sub_4080F0(...);
int sub_420250(...);
int sub_4202F0(...);
int sub_420380(...);
int sub_4204B0(...);
int sub_420910(...);
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
int todo_074(...);
int todo_078(...);
int todo_408BD0(...);

BOOL PointInRect(int *pRect, int *pPoint); // from annotations
gbVec3D * Vec3D_Cross(gbVec3D *pOut, gbVec3D *pA, gbVec3D *pB); // from annotations
float * Vec3D_Lerp(float *pOut, float *pSrc, float fLerpFactor); // from annotations

// Unnamed globals (extern)
extern CHAR asc_5C9190[];
extern CHAR asc_5F9D04[];
extern char byte_AABC03;
extern char byte_ABC00B;
extern char byte_ABC00C;
extern char byte_ABC00D;
extern CHAR byte_DC7D3C[512];
extern CHAR byte_DCD03C[256];
extern int dword_56A898[];
extern int dword_5888A8;
extern int dword_58B260[];
extern int dword_58B274;
extern int dword_58B288;
extern int dword_58B29C;
extern int dword_58B2B0;
extern int dword_58B2C4;
extern int dword_58B314;
extern int dword_58B328;
extern int dword_58B33C;
extern int dword_58B350;
extern int dword_58B3B4;
extern int dword_58B3C8;
extern int dword_58B3DC;
extern int dword_58B3F0;
extern int dword_AABC04;
extern int dword_C0205C[];
extern int dword_C110D0;
extern int dword_C1171C;
extern int dword_D8BC38;
extern int dword_DCEF3C;
extern int dword_DCF03C;
extern int dword_DCF13C;
extern int dword_DCF33C;
extern int dword_DD293C;
extern int dword_DD313C;
extern int dword_DD323C;
extern int dword_DD333C;
extern int dword_DD343C;
extern float flt_58B364;
extern float flt_BFDAAC;
extern float flt_D8BEC4;
void __cdecl nullsub_4(void);
void __cdecl nullsub_5(void);
void __cdecl nullsub_6(void);
extern LPCSTR off_59DD80;
extern int off_59DDA0;
extern int off_59DDA8;
extern void * off_5F7790;
extern RoleSystem stru_C059A0;
extern RoleSystem stru_C08160;
extern PalScript stru_C11720;
extern RoleCameraCtrl stru_DBA134;
extern int word_ABC00E;

// 0x004083E0
BOOL RoleSystem::CheckSceneCollision(int *nFlag, int nVal)
{
  RoleSystem *v3; // eax
  int *bottom; // [esp-0x10] [ebp-0x10]

  bottom = (int *)this->m_rect.bottom;
  v3 = (RoleSystem *)UISceneUpdate();
  return ((RoleSystem *)v3)->CheckCollision(bottom, (int)nFlag);
}

// 0x00408460
int RoleSystem::BindRoleToScene(
        
        int index,
        float *pfVal,
        float *pfVal2,
        int nVal,
        char pData)
{
  RoleSystem *v7; // eax
  LONG right; // edi
  int *v9; // ebp
  int *v10; // edi
  void *vftable; // eax
  RoleSystem *v12; // eax
  int v14; // ecx
  _DWORD *m_id; // eax
  int v16; // edi
  LONG v17; // eax
  double v18; // st7
  double v19; // st6
  int v20; // eax
  float v21; // ecx
  void *v22; // eax
  int *bottom; // [esp-0x18] [ebp-0x3C]
  int v24; // [esp+0x10] [ebp-0x14]
  int nVal2; // [esp+0x14] [ebp-0x10]
  int *a7; // [esp+0x18] [ebp-0xC] BYREF
  int *v27; // [esp+0x1C] [ebp-0x8]
  float v28; // [esp+0x20] [ebp-0x4]
  int pDataa; // [esp+0x38] [ebp+0x14]

  LOBYTE(this->m_pfather) = pData;
  this->m_rect.bottom = index;
  v7 = (RoleSystem *)UISceneUpdate();
  this->m_rect.right = ((RoleSystem *)v7)->GetRolePtr(index);
  *(_DWORD *)(nVal + 3072) = 0;
  right = this->m_rect.right;
  v24 = (__int64)((*pfVal - *(float *)(right + 128)) / flt_BFDAAC);
  nVal2 = (__int64)((pfVal[2] - *(float *)(right + 136)) / flt_BFDAAC);
  v9 = (int *)(__int64)((*pfVal2 - *(float *)(right + 128)) / flt_BFDAAC);
  v10 = (int *)(__int64)((pfVal2[2] - *(float *)(right + 136)) / flt_BFDAAC);
// [VFTABLE] vftable = this->__vftable;
  a7 = v9;
  v27 = v10;
  if ( !((int ( *)(RoleSystem *, int, int))vftable->Render)(this, v24, nVal2) )
    return 0;
  if ( !this->Render(v9, v10) )
  {
    a7 = v9;
    bottom = (int *)this->m_rect.bottom;
    v27 = v10;
    v12 = (RoleSystem *)UISceneUpdate();
    ((RoleSystem *)v12)->ValidatePath(bottom, v9, v10, v24, nVal2, &a7);
  }
  if ( (int)sub_401070((AStarPathFinder *)this, v24, nVal2, a7, v27) < 0 )
  {
    ((AStarPathFinder *)this)->Reset();
    return 0;
  }
  if ( this->m_id )
  {
    do
    {
      v14 = *(_DWORD *)(nVal + 3072);
      if ( v14 >= 256 )
        break;
      m_id = this->m_id;
      v16 = m_id[4];
      pDataa = m_id[3];
      v17 = this->m_rect.right;
      v18 = ((double)pDataa + 0.5) * flt_BFDAAC + *(float *)(v17 + 128);
      v19 = ((double)v16 + 0.5) * flt_BFDAAC + *(float *)(v17 + 136);
      v20 = nVal + 12 * v14;
      *(_DWORD *)(v20 + 4) = 0;
      v28 = v19;
      v21 = v28;
      *(float *)v20 = v18;
      *(float *)(v20 + 8) = v21;
      ++*(_DWORD *)(nVal + 3072);
      v22 = (void *)*((_DWORD *)this->m_id + 7);
      this->m_id = v22;
    }
    while ( v22 );
  }
  ((AStarPathFinder *)this)->Reset();
  if ( *(int *)(nVal + 3072) <= 1 )
    return 0;
  ((PathObj *)nVal)->CalcLength();
  return 1;
}

// 0x0040BE50
int * RoleSystem::Init()
{
  int *result; // eax
  int v2; // esi
  int v3; // edx

  result = (int *)&this->m_partyActor.m_curact[39];
  v2 = 12;
  do
  {
    v3 = *(result - 12);
    if ( *result < v3 )
    {
      if ( *result <= 0 )
        *result = 0;
    }
    else
    {
      *result = v3;
    }
    ++result;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x0040BE80
int RoleSystem::RecalcAggregatedStats(char pData)
{
  int i; // edx
  unsigned int v3; // esi
  int v4; // eax
  bool v5; // cf
  int v6; // esi
  _BYTE *v7; // esi
  bool v8; // cf
  _BYTE *m_pParticleData; // esi
  bool v10; // cf
  float m_fAnimDelta; // esi
  bool v12; // cf
  _BYTE *v13; // esi
  bool v14; // cf
  _BYTE *v15; // esi
  bool v16; // cf
  int result; // eax

  for ( i = 0; i < 12; ++i )
  {
    v3 = this->m_partyActor.m_dwMatMsg[8];
    v4 = 0;
    if ( !v3 )
      goto LABEL_33;
    if ( !*(_BYTE *)(v3 + i + 631) && i < 7 )
      v4 = *(__int16 *)(v3 + 2 * i + 644);
    switch ( i )
    {
      case 7:
        v5 = *(_BYTE *)(v3 + 619) != 0;
        goto LABEL_12;
      case 8:
        v5 = *(_BYTE *)(v3 + 620) != 0;
        goto LABEL_12;
      case 9:
        v5 = *(_BYTE *)(v3 + 621) != 0;
        goto LABEL_12;
      case 10:
        v5 = *(_BYTE *)(v3 + 622) != 0;
        goto LABEL_12;
      case 11:
        v5 = *(_BYTE *)(v3 + 623) != 0;
LABEL_12:
        v4 += v5;
        break;
      default:
        break;
    }
    v6 = *(_DWORD *)v3;
    if ( v6 == 6603 && !g_nFiveNimbusCount && i == 7 )
    {
      ++v4;
      goto LABEL_33;
    }
    if ( v6 != 6603 )
      goto LABEL_31;
    if ( g_nFiveNimbusCount == 1 && i == 8 )
    {
      ++v4;
      goto LABEL_33;
    }
    if ( g_nFiveNimbusCount == 3 && i == 9 )
    {
      ++v4;
      goto LABEL_33;
    }
    if ( g_nFiveNimbusCount == 2 && i == 10 )
    {
      ++v4;
      goto LABEL_33;
    }
    if ( g_nFiveNimbusCount == 4 && i == 11 )
    {
      ++v4;
    }
    else
    {
LABEL_31:
      if ( i == 3 && v6 == 6603 )
        v4 += g_nUpdateInterval;
    }
LABEL_33:
    v7 = (_BYTE *)*((_DWORD *)&this->m_partyActor.m_pParticleData + 3);
    if ( v7 )
    {
      if ( !v7[i + 631] )
        v4 += *(__int16 *)&v7[2 * i + 644];
      switch ( i )
      {
        case 7:
          v8 = v7[619] != 0;
          goto LABEL_42;
        case 8:
          v8 = v7[620] != 0;
          goto LABEL_42;
        case 9:
          v8 = v7[621] != 0;
          goto LABEL_42;
        case 10:
          v8 = v7[622] != 0;
          goto LABEL_42;
        case 11:
          v8 = v7[623] != 0;
LABEL_42:
          v4 += v8;
          break;
        default:
          break;
      }
    }
    m_pParticleData = this->m_partyActor.m_pParticleData;
    if ( m_pParticleData )
    {
      if ( !m_pParticleData[i + 631] )
        v4 += *(__int16 *)&m_pParticleData[2 * i + 644];
      switch ( i )
      {
        case 7:
          v10 = m_pParticleData[619] != 0;
          goto LABEL_52;
        case 8:
          v10 = m_pParticleData[620] != 0;
          goto LABEL_52;
        case 9:
          v10 = m_pParticleData[621] != 0;
          goto LABEL_52;
        case 10:
          v10 = m_pParticleData[622] != 0;
          goto LABEL_52;
        case 11:
          v10 = m_pParticleData[623] != 0;
LABEL_52:
          v4 += v10;
          break;
        default:
          break;
      }
    }
    m_fAnimDelta = this->m_partyActor.m_fAnimDelta;
    if ( m_fAnimDelta != 0.0 )
    {
      if ( !*(_BYTE *)(LODWORD(m_fAnimDelta) + i + 631) )
        v4 += *(__int16 *)(LODWORD(m_fAnimDelta) + 2 * i + 644);
      switch ( i )
      {
        case 7:
          v12 = *(_BYTE *)(LODWORD(m_fAnimDelta) + 619) != 0;
          goto LABEL_62;
        case 8:
          v12 = *(_BYTE *)(LODWORD(m_fAnimDelta) + 620) != 0;
          goto LABEL_62;
        case 9:
          v12 = *(_BYTE *)(LODWORD(m_fAnimDelta) + 621) != 0;
          goto LABEL_62;
        case 10:
          v12 = *(_BYTE *)(LODWORD(m_fAnimDelta) + 622) != 0;
          goto LABEL_62;
        case 11:
          v12 = *(_BYTE *)(LODWORD(m_fAnimDelta) + 623) != 0;
LABEL_62:
          v4 += v12;
          break;
        default:
          break;
      }
    }
    v13 = (_BYTE *)this->m_partyActor.m_dwMatMsg[2];
    if ( v13 )
    {
      if ( !v13[i + 631] )
        v4 += *(__int16 *)&v13[2 * i + 644];
      switch ( i )
      {
        case 7:
          v14 = v13[619] != 0;
          goto LABEL_72;
        case 8:
          v14 = v13[620] != 0;
          goto LABEL_72;
        case 9:
          v14 = v13[621] != 0;
          goto LABEL_72;
        case 10:
          v14 = v13[622] != 0;
          goto LABEL_72;
        case 11:
          v14 = v13[623] != 0;
LABEL_72:
          v4 += v14;
          break;
        default:
          break;
      }
    }
    v15 = (_BYTE *)this->m_partyActor.m_dwMatMsg[5];
    if ( v15 )
    {
      if ( !v15[i + 631] )
        v4 += *(__int16 *)&v15[2 * i + 644];
      switch ( i )
      {
        case 7:
          v16 = v15[619] != 0;
          goto LABEL_82;
        case 8:
          v16 = v15[620] != 0;
          goto LABEL_82;
        case 9:
          v16 = v15[621] != 0;
          goto LABEL_82;
        case 10:
          v16 = v15[622] != 0;
          goto LABEL_82;
        case 11:
          v16 = v15[623] != 0;
LABEL_82:
          v4 += v16;
          break;
        default:
          break;
      }
    }
    result = *(_DWORD *)&this->m_partyActor.m_szTexture[4 * i + 8] + v4;
    this->m_partyActor.m_dwMatMsg[i + 9] = result;
    if ( pData || (unsigned int)i > 2 )
      *(_DWORD *)&this->m_partyActor.m_curact[4 * i + 39] = result;
  }
  return result;
}

// 0x0040C9A0
int RoleSystem::ForceStopRole(int nVal)
{
  RoleSystem *v1; // edi
  int result; // eax

  v1 = (RoleSystem *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * nVal - 7];
  if ( ((RoleSystem *)v1)->IsPathMoving() )
    ((RoleSystem *)v1)->StopPathMovement(1);
  else
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * nVal + 151] = 1;
  result = ((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * nVal + 151];
  if ( !result )
    result = ((RoleSystem *)v1)->Notify();
  if ( nVal == 1 && (::nVal == 1 || g_RoleSystemMain.m_FrameA.m_rect.bottom == 10) )
  {
    ((ScriptSystem *)&g_RoleSystemMain)->UpdatePositions();
    ((RoleSystem *)&g_RoleSystemMain)->UpdateMovement(fDeltaTime, 1);
    g_RoleSystemMain.m_FrameA.m_childs.m_nSize = 0;
    return ((RoleSystem *)&g_RoleSystemMain)->UpdateTransform();
  }
  return result;
}

// 0x00410430
void RoleSystem::RenderMainRole()
{
  if ( g_RoleSystemMain.m_FrameA.m_rect.bottom != 10 || *(_DWORD *)&((RoleSystem *)&stru_C08160)->m_partyActor.m_szTexture[4] )
    ((RoleSystem *)&g_RoleSystemMain)->RenderRole((gbMatrixStack *)pMatrixStack, 0);
}

// 0x00410E40
int RoleSystem::CheckVisible(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // ebx
  _DWORD *v3; // ecx
  unsigned int v4; // esi
  int v5; // edi
  unsigned int v6; // ebp
  int v7; // edx
  unsigned int v8; // eax
  _DWORD *v10; // edx
  _DWORD *k; // eax
  _DWORD *v12; // eax
  _DWORD *v13; // ebx
  _DWORD *v14; // edi
  _DWORD *v15; // eax
  int result; // eax
  int v17; // ecx
  int v18; // kr00_4
  int v20; // ebp
  _DWORD *v21; // edx
  _DWORD *v22; // eax
  _DWORD *v23; // ebx
  unsigned int j; // esi
  int v25; // eax
  int v26; // ecx
  _DWORD *v27; // edi
  int v28; // esi
  _DWORD *v29; // eax
  _DWORD *i; // edx
  _DWORD *v31; // ecx
  _DWORD *v32; // eax
  _DWORD *v33; // ebx
  _DWORD *v34; // [esp+0x10] [ebp-0x8]
  _DWORD *v35; // [esp+0x14] [ebp-0x4]
  int nVala; // [esp+0x1C] [ebp+0x4]
  int nValb; // [esp+0x1C] [ebp+0x4]
  unsigned int v38; // [esp+0x20] [ebp+0x8]
  unsigned int v39; // [esp+0x20] [ebp+0x8]
  _DWORD *v40; // [esp+0x20] [ebp+0x8]
  _DWORD *v41; // [esp+0x24] [ebp+0xC]

  v2 = v1;
  v3 = (_DWORD *)v1[2];
  v4 = v38;
  v34 = v2;
  if ( (v2[3] - (int)v3) / 12 >= v38 )
  {
    result = (unsigned int)((unsigned __int64)(715827883LL * ((int)v3 - nVal)) >> 32) >> 31;
    if ( ((int)v3 - nVal) / 12 >= v38 )
    {
      if ( v38 )
      {
        v28 = 12 * v38;
        v29 = &v3[-3 * v38];
        for ( i = v3; v29 != v3; i += 3 )
        {
          if ( i )
          {
            *i = *v29;
            i[1] = v29[1];
            i[2] = v29[2];
            v28 = 12 * v38;
            v2 = v34;
          }
          v29 += 3;
        }
        v31 = (_DWORD *)v2[2];
        v32 = &v31[v28 / 0xFFFFFFFC];
        if ( (_DWORD *)nVal != &v31[v28 / 0xFFFFFFFC] )
        {
          do
          {
            v32 -= 3;
            v31 -= 3;
            *v31 = *v32;
            v31[1] = v32[1];
            v31[2] = v32[2];
          }
          while ( v32 != (_DWORD *)nVal );
          v2 = v34;
        }
        result = nVal;
        if ( nVal != v28 + nVal )
        {
          do
          {
            v33 = (_DWORD *)result;
            result += 12;
            *v33 = *v41;
            v33[1] = v41[1];
            v33[2] = v41[2];
          }
          while ( result != v28 + nVal );
          v2 = v34;
        }
        v2[2] += v28;
      }
    }
    else
    {
      v20 = 12 * v38;
      nValb = 12 * v38;
      v21 = (_DWORD *)(nVal + 12 * v38);
      v40 = v21;
      if ( (_DWORD *)nVal != v3 )
      {
        v22 = (_DWORD *)((char *)v21 - v20);
        do
        {
          if ( v21 )
          {
            *v21 = *v22;
            v21[1] = v22[1];
            v20 = nValb;
            v21[2] = v22[2];
            v21 = v40;
            v2 = v34;
          }
          v22 += 3;
          v21 += 3;
          v40 = v21;
        }
        while ( v22 != v3 );
      }
      v23 = (_DWORD *)v2[2];
      for ( j = v4 - ((int)v23 - nVal) / 12; j; --j )
      {
        if ( v23 )
        {
          *v23 = *v41;
          v23[1] = v41[1];
          v23[2] = v41[2];
        }
        v23 += 3;
      }
      v25 = nVal;
      v26 = v34[2];
      if ( nVal != v26 )
      {
        do
        {
          v27 = (_DWORD *)v25;
          v25 += 12;
          *v27 = *v41;
          v27[1] = v41[1];
          v27[2] = v41[2];
        }
        while ( v25 != v26 );
      }
      result = v20 + v34[2];
      v34[2] = result;
    }
  }
  else
  {
    v5 = v2[1];
    if ( !v5 || (v6 = ((int)v3 - v5) / 12, v38 >= v6) )
      v6 = v38;
    if ( v5 )
      v7 = ((int)v3 - v5) / 12;
    else
      v7 = 0;
    v8 = v7 + v6;
    v39 = v7 + v6;
    if ( (int)(v7 + v6) < 0 )
      v8 = 0;
    v35 = operator new(12 * v8);
    v10 = v35;
    for ( k = (_DWORD *)v2[1]; k != (_DWORD *)nVal; v10 += 3 )
    {
      if ( v10 )
      {
        *v10 = *k;
        v10[1] = k[1];
        v10[2] = k[2];
      }
      k += 3;
    }
    v12 = v10;
    if ( v4 )
    {
      nVala = v4;
      do
      {
        if ( v12 )
        {
          *v12 = *v41;
          v12[1] = v41[1];
          v12[2] = v41[2];
        }
        v12 += 3;
        --nVala;
      }
      while ( nVala );
    }
    v13 = (_DWORD *)v2[2];
    v14 = &v10[3 * v4];
    if ( (_DWORD *)nVal != v13 )
    {
      v15 = (_DWORD *)nVal;
      do
      {
        if ( v14 )
        {
          *v14 = *v15;
          v14[1] = v15[1];
          v14[2] = v15[2];
        }
        v15 += 3;
        v14 += 3;
      }
      while ( v15 != v13 );
    }
    operator delete((void *)v34[1]);
    result = v34[1];
    v34[3] = &v35[3 * v39];
    if ( result )
    {
      v17 = v34[2];
      v34[1] = v35;
      v18 = v17 - result;
      result = (unsigned int)((unsigned __int64)(715827883LL * (v17 - result)) >> 32) >> 31;
      v4 += v18 / 12;
    }
    else
    {
      v34[1] = v35;
    }
    v34[2] = &v35[3 * v4];
  }
  return result;
}

// 0x00411E00
void RoleSystem::ApplyMoveStep(double fInput, int nVal, float fVal, char bCollide)
{
  int v5; // esi
  int v12; // eax
  double v13; // [esp-0x8] [ebp-0x20]
  int v14; // [esp-0x4] [ebp-0x1C]
  gbVec3D pB; // [esp+0x0] [ebp-0x18] BYREF
  float v16; // [esp+0xC] [ebp-0xC]
  float v17; // [esp+0x10] [ebp-0x8]
  float v18; // [esp+0x14] [ebp-0x4]

  // __asm { fld     dword ptr [esp+0x18+fInput] }
  HIDWORD(v13) = v5;
__asm
  {
    fmul    dword ptr [esi+0x510]
    fstp    [esp+0x1C+var_C]
    fld     dword ptr [esp+0x1C+fInput]
    fmul    dword ptr [esi+0x514]
  }
  pB.x = v16;
  __asm
  {
    fstp    [esp+0x1C+var_8]
    fld     dword ptr [esp+0x1C+fInput]
    fmul    dword ptr [esi+0x518]
  }
  pB.y = v17;
  __asm
  {
    fstp    [esp+0x1C+var_4]
    fld     dword ptr [flt_56A984]
    fmul    _flt_1_5
  }
  pB.z = v18;
  // __asm { fstp    dword ptr [esp+0x1C+fInput] }
  ((gbVec3D *)&pB)->Length();
  __asm
  {
    fcom    dword ptr [esp+0x1C+fInput]
    fnstsw  ax
  }
  if ( (_AX & 0x4100) == 0 )
  {
    __asm
    {
      fdivr   dword ptr [esp+0x1C+fInput]
      fld     [esp+0x1C+pB]
      fmul    st, st(1)
      fstp    [esp+0x1C+pB]; pB
      fld     [esp+0x1C+var_14]
      fmul    st, st(1)
      fstp    [esp+0x1C+var_14]
      fld     [esp+0x1C+var_10]
      fmul    st, st(1)
      fstp    [esp+0x1C+var_10]
    }
  }
  _EAX = (float *)((char *)&_ESI[1].m_partyUI3._todo_05C + 79);
  __asm
  {
    fstp    st
    fld     [esp+0x1C+pB]
  }
  *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 79) = this->m_fontcolor.Color;
  *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 83) = this->m_wndcolor.Color;
  *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 87) = (int)this->m_id;
  __asm { fadd    dword ptr [eax] }
  __asm { fstp    dword ptr [eax] }
  *_EAX = _ET1;
  __asm
  {
    fld     [esp+0x1C+var_14]
    fadd    dword ptr [eax+4]
    fstp    dword ptr [eax+4]
  }
  _EAX[1] = _ET1;
  __asm
  {
    fld     [esp+0x1C+var_10]
    fadd    dword ptr [eax+8]
    fstp    dword ptr [eax+8]
  }
  _EAX[2] = _ET1;
  if ( BYTE4(fInput) )
  {
    LODWORD(v13) = (char *)_ESI + 8692;
    ((RoleSystem *)_ESI)->UpdateMovement(v13, (gbVec3D *)LODWORD(pB.x));
    if ( v12 )
    {
      ((RoleSystem *)_ESI)->UpdatePosition();
      ((RoleSystem *)_ESI)->SetMoveSpeed(0.0, _ESI == g_pRoleSystem, v14);
    }
  }
  else
  {
    this->_embed_UIWnd_624.m_childs.m_pData = (char *)LODWORD(this->m_fPosX);
    this->_embed_UIWnd_624.m_childs.capacity = LODWORD(this->m_fPosY);
    this->_embed_UIWnd_624.m_childs.m_nSize = LODWORD(this->m_fPosZ);
    this->m_fontcolor.Color = *(unsigned int *)_EAX;
    this->m_wndcolor.Color = *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 83);
    this->m_id = *(void **)((char *)&_ESI[1].m_partyUI3._todo_05C + 87);
    ((RoleSystem *)_ESI)->UpdatePosition();
    ((RoleSystem *)_ESI)->SetMoveSpeed(0.0, _ESI == g_pRoleSystem, SHIDWORD(v13));
  }
}

// 0x00412230
void RoleSystem::SetMoveSpeed(float fSpeed, int nRoleIndex, int nFlag)
{
  RoleSystem *v5; // eax
  int v8; // [esp-0x10] [ebp-0x14]
if ( !*(_DWORD *)&this->m_partyActor.m_szTexture[8] )
  {
    this->m_nDispFontColor = this->m_fontcolor.Color;
    this->m_nDispWndColor = this->m_wndcolor.Color;
    this->m_nField9C = (int)this->m_id;
    v8 = *(_DWORD *)this->m_partyActor.m_szTexture;
    v5 = (RoleSystem *)UISceneUpdate();
    ((RoleSystem *)v5)->SetRoleParam(v8, (float *)&this->m_fontcolor.Color, &this->_embed_UIWnd_624.m_rect.left, 0);
    // __asm { fstp    dword ptr [esi+0x98] }
    *(float *)&this->m_nDispWndColor = _ET1;
    if ( fSpeed == 0.0 )
    {
      LODWORD(this->m_fPosX) = this->m_nDispFontColor;
      LODWORD(this->m_fPosY) = this->m_nDispWndColor;
      LODWORD(this->m_fPosZ) = this->m_nField9C;
      __asm
      {
        fld     dword ptr [esi+0x0A4]
        fadd    _flt_1_0
        fstp    dword ptr [esi+0x0A4]
      }
      this->m_fPosY = _ET1;
    }
  }
}

// 0x004122C0
void RoleSystem::UpdatePosition()
{
  LONG *p_top; // esi
  double v3; // st7
  double v4; // st6
  double v5; // st5
  long double v6; // st7
  float v7; // [esp+0x8] [ebp-0x8]
  int v8; // [esp+0xC] [ebp-0x4]

  if ( this->m_FrameA.m_rect.bottom != 8 )
  {
    p_top = &this->m_rect.top;
    this->m_rect.top = this->m_FrameA.m_bvisible;
    this->m_rect.right = this->m_FrameA.m_benable;
    this->m_rect.bottom = this->m_FrameA.m_bfocus;
    ((gbVec3D *)&this->m_rect.top)->Normalize();
    v3 = *(float *)&this->m_bcreateok * *(float *)&this->m_rect.right
       - *(float *)&this->m_rect.bottom * *(float *)&this->m_childs.m_needscriptdel;
    v7 = *(float *)&this->m_rect.bottom * *(float *)&this->m_childs.m_nSize
       - *(float *)&this->m_bcreateok * *(float *)&this->m_rect.top;
    v4 = *(float *)p_top * *(float *)&this->m_childs.m_needscriptdel;
    v5 = *(float *)&this->m_childs.m_nSize * *(float *)&this->m_rect.right;
    *(float *)&this->m_childs.m_pData = v7;
    *(float *)&v8 = v4 - v5;
    *(float *)&this->m_pfather = v3;
    this->m_childs.capacity = v8;
    ((gbVec3D *)&this->m_pfather)->Normalize();
    if ( (g_szSceneUIText[108] & 1) == 0 )
    {
      *(_DWORD *)&g_szSceneUIText[96] = 0;
      g_szSceneUIText[108] |= 1u;
      *(_DWORD *)&g_szSceneUIText[100] = 0;
      *(_DWORD *)&g_szSceneUIText[104] = 1065353216;
      atexit(nullsub_4);
    }
    v6 = acos(
           *(float *)&g_szSceneUIText[104] * *(float *)&this->m_rect.bottom
         + *(float *)&g_szSceneUIText[100] * *(float *)&this->m_rect.right
         + *(float *)&g_szSceneUIText[96] * *(float *)&this->m_rect.top);
    *((float *)this + 2172) = v6;
    if ( *(float *)p_top < 0.0 )
      *((float *)this + 2172) = 6.2831855 - v6;
    *((float *)this + 2172) = *((float *)this + 2172) * 57.29578;
  }
}

// 0x00412400
void RoleSystem::RenderRole(gbMatrixStack *pStack, int nVal)
{
  gbMatrix4 v4; // [esp+0x38] [ebp-0x40] BYREF

  if ( *(_DWORD *)&this->m_partyActor.m_szTexture[4] )
  {
    if ( (g_szSceneUIText[92] & 1) == 0 )
    {
      *(_DWORD *)&g_szSceneUIText[80] = 0;
      g_szSceneUIText[92] |= 1u;
      *(_DWORD *)&g_szSceneUIText[84] = 1065353216;
      *(_DWORD *)&g_szSceneUIText[88] = 0;
      atexit(nullsub_5);
    }
    ((gbMatrixStack *)pStack)->Push();
    ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_fPosX);
    if ( this->m_FrameA.m_rect.right == 4 && LODWORD(this->m_fRotAxisZ) == 11 )
      ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->m_pLinkedSystem, (gbVec3D *)&this->m_FrameA.m_bvisible);
    ((gbMatrixStack *)pStack)->Rotate(*((float *)this + 2172), (gbVec3D *)&g_szSceneUIText[80]);
    ((gbMatrixStack *)pStack)->Scale(*(float *)&this->m_partyActor.m_szTexture[12],   *(float *)&this->m_partyActor.m_szTexture[12],   *(float *)&this->m_partyActor.m_szTexture[12]);
    this->m_nActionResult = ((Actor *)&this->m_partyActor.m_nActionType)->DispatchAction(nVal);
    if ( this->_embed_UIWnd_624.m_wndcolor.Color )
    {
      if ( BYTE1(this->_embed_UIWnd_624.m_id) )
      {
        ((gbMatrixStack *)pStack)->Push();
        ((gbActor *)this->m_partyActor.m_nHP)->GetTagNodeTM(&v4, "tag_weapon1");
        ((gbMatrixStack *)pStack)->MultMatrix(&v4);
        (*(void ( **)(unsigned int, _DWORD))(*(_DWORD *)this->_embed_UIWnd_624.m_wndcolor.Color + 16))(
          this->_embed_UIWnd_624.m_wndcolor.Color,
          0);
        ((gbMatrixStack *)pStack)->Pop();
      }
      if ( LOBYTE(this->_embed_UIWnd_624.m_id) )
      {
        ((gbMatrixStack *)pStack)->Push();
        ((gbActor *)this->m_partyActor.m_nHP)->GetTagNodeTM(&v4, "tag_weapon2");
        ((gbMatrixStack *)pStack)->MultMatrix(&v4);
        (*(void ( **)(unsigned int, _DWORD))(*(_DWORD *)this->_embed_UIWnd_624.m_wndcolor.Color + 16))(
          this->_embed_UIWnd_624.m_wndcolor.Color,
          0);
        ((gbMatrixStack *)pStack)->Pop();
      }
    }
    ((gbMatrixStack *)pStack)->Pop();
  }
}

// 0x004125B0
int RoleSystem::NotifySceneChange()
{
  int v3; // [esp+0x8] [ebp+0x4]

  UISceneUpdate();
  *(_DWORD *)this->m_partyActor.m_szTexture = v3;
  return v3;
}

// 0x004126D0
int RoleSystem::GetAnimOffset(int nType, unsigned __int8 nMode)
{
  if ( (nMode < 2u || nMode == 4 || nMode == 2) && nType )
  {
    if ( nType == 1 )
      return 52;
    if ( nType == 2 )
      return 58;
  }
  return 50;
}

// 0x00412710
int RoleSystem::UpdateTransform()
{
  __int64 m_nSize; // rax
  char m_nActionState; // al
  int v4; // [esp-0x4] [ebp-0xC]
  int v5; // [esp-0x4] [ebp-0xC]
  int v6; // [esp-0x4] [ebp-0xC]
  int v7; // [esp-0x4] [ebp-0xC]

  m_nSize = (unsigned int)this->m_FrameA.m_childs.m_nSize;
  if ( (unsigned int)m_nSize > 0x3A )
    this->m_FrameA.m_childs.m_nSize = 0;
  switch ( this->m_FrameA.m_childs.m_nSize )
  {
    case 0:
    case 5:
    case 7:
      this->m_FrameA.m_childs.m_needscriptdel = 0;
      this->m_FrameA.m_bcreateok = 0;
      this->m_FrameA.m_bvisible = 0;
      this->m_FrameA.m_benable = 0;
      this->m_FrameA.m_bfocus = 0;
      this->m_FrameA.m_pbktex = 0;
      this->m_nActiveRole = this->m_FrameA.m_benable;
      this->m_nRoleCount = this->m_FrameA.m_bfocus;
      return this->UpdatePath(this->m_FrameA.m_childs.m_nSize);
    case 1:
    case 3:
      this->m_FrameA.m_bcreateok = dword_58B3B4;
      m_nActionState = this->m_nActionState;
      if ( m_nActionState == -1 )
      {
        HIDWORD(m_nSize) = dword_58B3DC;
LABEL_7:
        this->m_FrameA.m_childs.m_needscriptdel = HIDWORD(m_nSize);
        return this->UpdatePath(this->m_FrameA.m_childs.m_nSize);
      }
      if ( m_nActionState == 2 )
      {
        if ( LODWORD(this->m_fMoveRole) == 1 )
        {
          if ( *(_BYTE *)(LODWORD(this->m_fMoveParamY) + 756) == 1 )
          {
            v5 = this->m_FrameA.m_childs.m_nSize;
            this->m_FrameA.m_childs.m_needscriptdel = dword_58B33C;
            return this->UpdatePath(v5);
          }
          else if ( *(_BYTE *)(LODWORD(this->m_fMoveParamY) + 756) == 2 )
          {
            this->m_FrameA.m_childs.m_needscriptdel = dword_58B350;
            return this->UpdatePath(this->m_FrameA.m_childs.m_nSize);
          }
          else
          {
            v4 = this->m_FrameA.m_childs.m_nSize;
            this->m_FrameA.m_childs.m_needscriptdel = dword_58B328;
            return this->UpdatePath(v4);
          }
        }
        else
        {
          switch ( *(_BYTE *)(LODWORD(this->m_fMoveParamY) + 755) )
          {
            case 0:
              goto LABEL_7;
            case 1:
              this->m_FrameA.m_childs.m_needscriptdel = dword_58B29C;
              return this->UpdatePath(this->m_FrameA.m_childs.m_nSize);
            case 2:
              v6 = this->m_FrameA.m_childs.m_nSize;
              this->m_FrameA.m_childs.m_needscriptdel = dword_58B2B0;
              return this->UpdatePath(v6);
            default:
              this->m_FrameA.m_childs.m_needscriptdel = dword_58B2C4;
              return this->UpdatePath(this->m_FrameA.m_childs.m_nSize);
          }
        }
      }
      else
      {
        *(float *)&m_nSize = this->m_partyActor.m_vecTargetPos.x;
        v7 = this->m_FrameA.m_childs.m_nSize;
        if ( (_DWORD)m_nSize == HIDWORD(m_nSize) )
          this->m_FrameA.m_childs.m_needscriptdel = g_nRoleSystem_58B38C;
        else
          *(float *)&this->m_FrameA.m_childs.m_needscriptdel = (float)m_nSize;
        return this->UpdatePath(v7);
      }
    case 2:
      this->m_FrameA.m_childs.m_needscriptdel = dword_58B3F0;
      this->m_FrameA.m_bcreateok = dword_58B3C8;
      return this->UpdatePath(this->m_FrameA.m_childs.m_nSize);
    default:
      return this->UpdatePath(this->m_FrameA.m_childs.m_nSize);
  }
}

// 0x00412940
int RoleSystem::UpdatePath(int nVal)
{
  int AnimOffset; // ebp
  Actor *p_m_nActionType; // edi
  int result; // eax
  int v6; // [esp-0x8] [ebp-0x14]

  if ( this->m_nAnimState == 49 )
  {
    ((Actor *)&this->m_partyActor.m_nActionType)->CompareActionName(nVal, 2);
    ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(1.0);
    BYTE1(this->_embed_UIWnd_624.m_id) = 0;
    LOBYTE(this->_embed_UIWnd_624.m_id) = 0;
    return result;
  }
  AnimOffset = ((RoleSystem *)nVal)->GetAnimOffset(this->m_nActionState);
  if ( this->m_nAnimState == 50 )
    goto LABEL_10;
  if ( AnimOffset == 50 )
  {
    p_m_nActionType = (Actor *)&this->m_partyActor.m_nActionType;
    if ( !((Actor *)&this->m_partyActor.m_nActionType)->SetMaterialName("z0") )
      ((Actor *)p_m_nActionType)->CompareActionName(50, 0);
    goto LABEL_12;
  }
  if ( AnimOffset != 52 && AnimOffset != 58 )
  {
LABEL_10:
    p_m_nActionType = (Actor *)&this->m_partyActor.m_nActionType;
    v6 = 2;
    goto LABEL_11;
  }
  p_m_nActionType = (Actor *)&this->m_partyActor.m_nActionType;
  if ( !((Actor *)&this->m_partyActor.m_nActionType)->SetMaterialName("z4") )
  {
    v6 = 0;
LABEL_11:
    ((Actor *)p_m_nActionType)->CompareActionName(AnimOffset, v6);
  }
LABEL_12:
  if ( this->m_FrameA.m_childs.m_nSize == 2 )
    ((Actor *)p_m_nActionType)->SetTimeScale(2.4000001);
  else
    ((Actor *)p_m_nActionType)->SetTimeScale(1.0);
  BYTE1(this->_embed_UIWnd_624.m_id) = 0;
  LOBYTE(this->_embed_UIWnd_624.m_id) = 0;
  return result;
}

// 0x00412A50
int RoleSystem::StartHalfSpeedMovement()
{
  int result; // eax

  this->m_FrameA.m_rect.bottom = 1;
  this->m_FrameA.m_childs.m_nSize = 1;
  result = this->UpdateTransform();
  *(float *)&this->m_FrameA.m_childs.m_needscriptdel = *(float *)&this->m_FrameA.m_childs.m_needscriptdel * 0.5;
  *(float *)&this->m_FrameA.m_bcreateok = *(float *)&this->m_FrameA.m_bcreateok * 0.5;
  return result;
}

// 0x00412A90
void RoleSystem::MoveToTile(__int64 tileXY, int nMode)
{
  int v4; // eax
  RoleSystem *v5; // eax
  int RolePtr; // edi
  double v7; // st7
  double v8; // st6
  int v9; // [esp-0x4] [ebp-0x28]
  float pTargetPos; // [esp+0xC] [ebp-0x18] BYREF
  int v11; // [esp+0x10] [ebp-0x14]
  float v12; // [esp+0x14] [ebp-0x10]
  float v13; // [esp+0x20] [ebp-0x4]

  pTargetPos = 0.0;
  v11 = 0;
  v4 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v12 = 0.0;
  v9 = v4;
  v5 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v5)->GetRolePtr(v9);
  if ( __PAIR64__(
         (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize),
         (__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize)) != tileXY )
  {
    v7 = ((double)(int)tileXY + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 128);
    v8 = ((double)SHIDWORD(tileXY) + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 136);
    v11 = 0;
    v13 = v8;
    pTargetPos = v7;
    v12 = v13;
    this->SetMoveTarget(&pTargetPos, nMode);
  }
}

// 0x00412B60
void RoleSystem::SetMoveTarget(float *pTargetPos, int nFlags)
{
  double v4; // st7
  float v5; // eax
  gbVec3D v6; // [esp+0x8] [ebp-0xC] BYREF

  v6.x = *pTargetPos;
  v4 = v6.x - *(float *)&this->m_fontcolor.Color;
  v6.y = pTargetPos[1];
  v5 = pTargetPos[2];
  v6.x = v4;
  v6.y = -*(float *)&this->m_wndcolor.Color;
  v6.z = v5;
  v6.z = v5 - *(float *)&this->m_id;
  if ( ((gbVec3D *)&v6)->Length() >= 12.0 )
  {
    this->m_FrameA.m_rect.bottom = 4;
    this->m_FrameA.m_childs.m_nSize = nFlags;
    this->m_pLinkedSystem = *(char **)pTargetPos;
    this->m_fAnimSpeed = pTargetPos[1];
    this->m_fMoveRadius = pTargetPos[2];
    this->m_pRenderObj = (gbGeomNode *)this->m_fontcolor.Color;
    this->m_bRenderFlag1 = this->m_wndcolor.Color;
    *(_DWORD *)&this->m_bRenderFlag2 = this->m_id;
    this->m_fAnimSpeed = 0.0;
    this->m_bRenderFlag1 = 0;

  }
  else
  {
    this->m_FrameA.m_rect.bottom = 0;
  }
}

// 0x00412C30
int RoleSystem::SetPathWaypoint(float fVal)
{
  long double v2; // st7
  int result; // eax
  float v4; // [esp+0x4] [ebp-0x8]
  float v5; // [esp+0x8] [ebp-0x4]

  v2 = *((float *)this + 2172) * 0.017453292;
  this->m_FrameA.m_rect.bottom = 8;
  this->m_FrameA.m_benable = 0;
  *(float *)&this->m_FrameA.m_bvisible = sin(v2);
  *(float *)&this->m_FrameA.m_bfocus = cos(v2);
  *(float *)&this->m_FrameA.m_bvisible = *(float *)&this->m_FrameA.m_bvisible * -1.0;
  *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable * -1.0;
  *(float *)&this->m_FrameA.m_bfocus = *(float *)&this->m_FrameA.m_bfocus * -1.0;
  this->m_pRenderObj = (gbGeomNode *)this->m_fontcolor.Color;
  this->m_bRenderFlag1 = this->m_wndcolor.Color;
  *(_DWORD *)&this->m_bRenderFlag2 = this->m_id;
  this->m_pLinkedSystem = (char *)this->m_fontcolor.Color;
  LODWORD(this->m_fAnimSpeed) = this->m_wndcolor.Color;
  LODWORD(this->m_fMoveRadius) = this->m_id;
  v4 = fVal * *(float *)&this->m_FrameA.m_benable;
  v5 = fVal * *(float *)&this->m_FrameA.m_bfocus;
  *(float *)&this->m_pLinkedSystem = fVal * *(float *)&this->m_FrameA.m_bvisible + *(float *)&this->m_pLinkedSystem;
  this->m_fAnimSpeed = v4 + this->m_fAnimSpeed;
  this->m_fMoveRadius = v5 + this->m_fMoveRadius;
  this->m_fAnimSpeed = 0.0;
  this->m_bRenderFlag1 = 0;
  *(float *)&this->m_FrameA.m_bvisible = *(float *)&this->m_FrameA.m_bvisible * 70.0;
  *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable * 70.0;
  *(float *)&this->m_FrameA.m_bfocus = *(float *)&this->m_FrameA.m_bfocus * 70.0;
  this->m_FrameA.m_pbktex = (gbTexture *)this->m_FrameA.m_bvisible;
  this->m_nActiveRole = this->m_FrameA.m_benable;
  result = this->m_FrameA.m_bfocus;
  this->m_nRoleCount = result;
  return result;
}

// 0x00412D90
char RoleSystem::BindPartyToScene(float *pfVal, int nVal)
{
  float *p_Color; // ecx
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  int m_nSize; // ecx

  p_Color = (float *)&this->m_fontcolor.Color;
  if ( !(v6 | v7) )
    return 1;
  if ( ((RoleSystem *)&g_szSceneUIText[184])->BindRoleToScene(*(_DWORD *)this->m_partyActor.m_szTexture, p_Color, pfVal, (int)&this->_embed_UIWnd_624.m_childs.m_needscriptdel, this->m_nFacing) )
  {
    m_nSize = this->m_FrameA.m_childs.m_nSize;
    this->m_FrameA.m_rect.bottom = 2;
    if ( m_nSize != nVal )
    {
      this->m_FrameA.m_childs.m_nSize = nVal;

    }
    return 1;
  }
  else
  {

    return 0;
  }
}

// 0x00412E60
int RoleSystem::MoveRole(float *pPos, int nVal, int nVal2, int nVal3)
{
  int result; // eax
  LONG bottom; // ecx
  RoleSystem *v8; // eax
  int RolePtr; // ebx
  RoleSystem *v10; // eax
  UIWnd *v11; // edx
  int *v12; // [esp-0x18] [ebp-0x34]
  char *v13; // [esp-0x14] [ebp-0x30]
  int v14; // [esp-0x10] [ebp-0x2C]
  char *v15; // [esp-0xC] [ebp-0x28]
  int v16; // [esp-0x8] [ebp-0x24]
  int v17; // [esp-0x8] [ebp-0x24]

  this->m_pLinkedSystem = *(char **)pPos;
  result = nVal;
  this->m_fAnimSpeed = pPos[1];
  this->m_fMoveRadius = pPos[2];
  bottom = this->m_FrameA.m_rect.bottom;
  LODWORD(this->m_fMoveSpeed) = nVal;
  this->_embed_UIWnd_624.m_rect.bottom = 1;
  if ( bottom != 2 )
  {
    LOBYTE(result) = this->UpdateRole(pPos, nVal, nVal2);
    this->_embed_UIWnd_624.m_pfather = 0;
    return result;
  }
  if ( nVal == *(_DWORD *)this->m_partyActor.m_szTexture )
  {
    v16 = *(_DWORD *)this->m_partyActor.m_szTexture;
    v8 = (RoleSystem *)UISceneUpdate();
    RolePtr = ((RoleSystem *)v8)->GetRolePtr(v16);
    v17 = (__int64)((pPos[2] - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
    v15 = (char *)(__int64)((*pPos - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
    v14 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
    v13 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
    v12 = *(int **)this->m_partyActor.m_szTexture;
    v10 = (RoleSystem *)UISceneUpdate();
    if ( ((RoleSystem *)v10)->AdvanceOnPath(v12, v13, v14, v15, v17) )
    {
      *((_DWORD *)this + 1138) = 2;
      this->_embed_UIWnd_624.m_childs.m_needscriptdel = this->m_fontcolor.Color;
      this->_embed_UIWnd_624.m_bcreateok = this->m_wndcolor.Color;
      this->_embed_UIWnd_624.m_bvisible = (int)this->m_id;
      this->_embed_UIWnd_624.m_benable = *(int *)pPos;
      this->_embed_UIWnd_624.m_bfocus = (int)pPos[1];
      this->m_teamSlots[0] = (int)pPos[2];
      return ((PathObj *)&this->_embed_UIWnd_624.m_childs.m_needscriptdel)->CalcLength();
    }
    result = nVal;
  }
  if ( nVal3
// [VFTABLE] || (v11 = (UIWnd *)((char *)&this->_embed_UIWnd_624.m_pfather->__vftable + 1),
// [VFTABLE]   this->_embed_UIWnd_624.m_pfather = v11,
// [VFTABLE]   (int)v11 > 30) )
  {
    this->_embed_UIWnd_624.m_pfather = 0;
    LOBYTE(result) = this->UpdateRole(pPos, result, nVal2);
  }
  return result;
}

// 0x00413010
char RoleSystem::UpdateRole(float *pfVal, int nVal, int nVal2)
{
  float v5; // eax
  RoleSystem *v6; // eax
  int RolePtr; // ebp
  int v8; // esi
  int v9; // edx
  int *v10; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // kr00_4
  int v14; // eax
  int v15; // ecx
  float v16; // eax
  int v18; // [esp-0x4] [ebp-0x48]
  int v19; // [esp+0x10] [ebp-0x34]
  int v20; // [esp+0x14] [ebp-0x30]
  int v21; // [esp+0x18] [ebp-0x2C]
  int v22; // [esp+0x1C] [ebp-0x28]
  int v23; // [esp+0x20] [ebp-0x24]
  int v24; // [esp+0x24] [ebp-0x20]
  int v25; // [esp+0x28] [ebp-0x1C]
  float pfVal2[2]; // [esp+0x2C] [ebp-0x18] BYREF
  float v27; // [esp+0x34] [ebp-0x10]
  float v28; // [esp+0x38] [ebp-0xC]
  float v29; // [esp+0x3C] [ebp-0x8]
  float v30; // [esp+0x40] [ebp-0x4]

  if ( nVal == *(_DWORD *)this->m_partyActor.m_szTexture )
    return this->BindPartyToScene(pfVal, nVal2);
  v18 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v6 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v6)->GetRolePtr(v18);
  v21 = RolePtr;
  v24 = (__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v8 = v22;
  v9 = 0x7FFFF;
  v25 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  v20 = 0x7FFFF;
  v19 = 0;
  v10 = (int *)(RolePtr + 8);
  do
  {
    v11 = *(v10 - 2);
    v12 = *v10;
    if ( v11 != *v10 || v12 )
    {
      v8 = (v12 + v11) / 2;
      v13 = v10[1] + *(v10 - 1);
      v9 = v20;
      RolePtr = v21;
      if ( (v8 - v24) * (v8 - v24) + (v13 / 2 - v25) * (v13 / 2 - v25) >= v20 )
      {
        v8 = v22;
      }
      else
      {
        v23 = v13 / 2;
        v9 = (v8 - v24) * (v8 - v24) + (v13 / 2 - v25) * (v13 / 2 - v25);
        v20 = v9;
        v22 = (v12 + v11) / 2;
        this->m_nMoveReset = v19;
      }
    }
    v10 += 4;
    LOBYTE(v5) = ++v19;
  }
  while ( v19 < 8 );
  if ( v9 <= 32 )
  {
    v29 = 0.0;
    v28 = ((double)v22 + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 128);
    v30 = ((double)v23 + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 136);
    if ( v8 < 0 || (v14 = *(_DWORD *)(RolePtr + 152), v8 >= v14) )
    {
      v15 = v23;
    }
    else
    {
      v15 = v23;
      if ( v23 >= 0 && v23 < *(_DWORD *)(RolePtr + 156) )
        v29 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (v8 + v23 * v14));
    }
    pfVal2[0] = v28;
    v27 = v30;
    pfVal2[1] = 0.0;
    if ( v24 == v8 && v25 == v15 )
    {
      this->PlaceAtRegion(nVal, this->m_nMoveReset);
      LOBYTE(v5) = this->BindPartyToScene(pfVal2, nVal2);
    }
    else
    {
      v16 = v27;
      *(float *)&this->m_pLinkedSystem = pfVal2[0];
      this->m_fAnimSpeed = 0.0;
      this->m_fMoveRadius = v16;
      if ( ((RoleSystem *)&g_szSceneUIText[184])->BindRoleToScene(*(_DWORD *)this->m_partyActor.m_szTexture, (float *)&this->m_fontcolor.Color, pfVal2, (int)&this->_embed_UIWnd_624.m_childs.m_needscriptdel, this->m_nFacing) )
      {
        this->m_FrameA.m_rect.bottom = 7;
        this->m_FrameA.m_childs.m_nSize = nVal2;

        this->m_pLinkedSystem = *(char **)pfVal;
        this->m_fAnimSpeed = pfVal[1];
        v5 = pfVal[2];
        this->m_fMoveRadius = v5;
        this->m_fAnimSpeed = 0.0;
        LODWORD(this->m_fMoveSpeed) = nVal;
      }
      else
      {
        LOBYTE(v5) = this->NotifyMoveComplete();
      }
    }
  }
  return LOBYTE(v5);
}

// 0x004132B0
char RoleSystem::MoveToTileCheck(int nTileX, int nTileY, int nMode)
{
  int v5; // eax
  RoleSystem *v6; // eax
  int RolePtr; // edi
  double v9; // st7
  double v10; // st6
  int v11; // [esp-0x4] [ebp-0x28]
  float pfVal; // [esp+0xC] [ebp-0x18] BYREF
  int v13; // [esp+0x10] [ebp-0x14]
  float v14; // [esp+0x14] [ebp-0x10]
  float v15; // [esp+0x20] [ebp-0x4]

  pfVal = 0.0;
  v13 = 0;
  v5 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v14 = 0.0;
  v11 = v5;
  v6 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v6)->GetRolePtr(v11);
  if ( (unsigned int)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize) == nTileX
    && (unsigned int)(__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize) == nTileY )
  {
    return 1;
  }
  v9 = ((double)nTileX + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 128);
  v10 = ((double)nTileY + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 136);
  v13 = 0;
  v15 = v10;
  pfVal = v9;
  v14 = v15;
  return this->BindPartyToScene(&pfVal, nMode);
}

// 0x00413390
void RoleSystem::InterpolateMoveFrame(float fVal)
{
  double v3; // st7
  float *p_m_pbktex; // esi
  double v5; // st6
  double v6; // st7
  int v7; // [esp+0xC] [ebp-0x8]
  int v8; // [esp+0x10] [ebp-0x4]

  v3 = *(float *)&this->m_pLinkedSystem - *(float *)&this->m_fontcolor.Color;
  p_m_pbktex = (float *)&this->m_FrameA.m_pbktex;
  *(float *)&v7 = this->m_fAnimSpeed - *(float *)&this->m_wndcolor.Color;
  v5 = this->m_fMoveRadius - *(float *)&this->m_id;
  this->m_nActiveRole = v7;
  *(float *)&v8 = v5;
  *(float *)&this->m_FrameA.m_pbktex = v3;
  this->m_nRoleCount = v8;
  v6 = *(float *)&this->m_FrameA.m_childs.m_needscriptdel / ((gbVec3D *)&this->m_FrameA.m_pbktex)->Length();
  *p_m_pbktex = v6 * *p_m_pbktex;
  p_m_pbktex[1] = v6 * p_m_pbktex[1];
  p_m_pbktex[2] = v6 * p_m_pbktex[2];
  *p_m_pbktex = fVal * *p_m_pbktex;
  p_m_pbktex[1] = fVal * p_m_pbktex[1];
  p_m_pbktex[2] = fVal * p_m_pbktex[2];
  this->NormalizeDirection(p_m_pbktex);
}

// 0x00413420
int RoleSystem::StepAlongPath(double fStepSize, float fVal)
{
  double v4; // st7
  gbVec3D *p_m_fontcolor; // edi
  int *p_m_needscriptdel; // ebx
  double v7; // st6
  double v8; // st7
  int v9; // eax
  double v11; // st7
  double v12; // st7
  char *v13; // eax
  gbVec3D *v14; // ebx
  double v15; // st7
  double v16; // st7
  float *v17; // eax
  double v18; // st7
  double v19; // st7
  float v20; // edx
  float v21; // eax
  float v22; // [esp+0x4] [ebp-0x7C]
  float v23; // [esp+0x8] [ebp-0x78]
  float v24; // [esp+0xC] [ebp-0x74]
  float v25; // [esp+0x1C] [ebp-0x64]
  float v26; // [esp+0x1C] [ebp-0x64]
  int v27; // [esp+0x20] [ebp-0x60] BYREF
  float v28; // [esp+0x24] [ebp-0x5C]
  float v29; // [esp+0x28] [ebp-0x58]
  float v30; // [esp+0x2C] [ebp-0x54] BYREF
  float v31; // [esp+0x30] [ebp-0x50]
  float v32; // [esp+0x34] [ebp-0x4C]
  gbVec3D v33; // [esp+0x38] [ebp-0x48] BYREF
  _DWORD v34[3]; // [esp+0x44] [ebp-0x3C] BYREF
  float v35[3]; // [esp+0x50] [ebp-0x30] BYREF
  struct gbVec3D v36; // [esp+0x5C] [ebp-0x24] BYREF
  gbVec3D pOut; // [esp+0x68] [ebp-0x18] BYREF
  gbVec3D v38; // [esp+0x74] [ebp-0xC] BYREF
  float fStepSizea; // [esp+0x84] [ebp+0x4]
  float fStepSizeb; // [esp+0x84] [ebp+0x4]

  v25 = 12.0 * 3.0;
  v4 = 12.0 * 3.0 * *(float *)&this->m_rect.top;
  p_m_fontcolor = (gbVec3D *)&this->m_fontcolor;
  p_m_needscriptdel = &this->_embed_UIWnd_624.m_childs.m_needscriptdel;
  v33.y = v25 * *(float *)&this->m_rect.right;
  v7 = v25 * *(float *)&this->m_rect.bottom;
  memset(v34, 0, sizeof(v34));
  v33.z = v7;
  v8 = v4 + *(float *)&this->m_fontcolor.Color;
  v30 = 0.0;
  v31 = 0.0;
  v32 = 0.0;
  v35[0] = v8;
  v35[1] = v33.y + *(float *)&this->m_wndcolor.Color;
  v35[2] = v33.z + *(float *)&this->m_id;
  v9 = sub_407EC0(v35, v34, &v30);
  v30 = v30 * *(float *)&fStepSize;
  v31 = v31 * *(float *)&fStepSize;
  v32 = v32 * *(float *)&fStepSize;
  if ( v9
    && v32 * *(float *)&this->m_rect.bottom + v31 * *(float *)&this->m_rect.right + v30 * *(float *)&this->m_rect.top > 0.5 )
  {
    this->m_FrameA.m_pbktex = (gbTexture *)this->m_rect.top;
    this->m_nActiveRole = this->m_rect.right;
    this->m_nRoleCount = this->m_rect.bottom;
    v11 = *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
    *(float *)&this->m_FrameA.m_pbktex = v11 * *(float *)&this->m_FrameA.m_pbktex;
    *(float *)&this->m_nActiveRole = v11 * *(float *)&this->m_nActiveRole;
    *(float *)&this->m_nRoleCount = v11 * *(float *)&this->m_nRoleCount;
    return 0;
  }
  *(float *)&v27 = 0.0;
  v28 = 0.0;
  v29 = 0.0;
  v12 = sub_408010(p_m_fontcolor) + v25 * *(float *)&fStepSize;
  if ( *(float *)&fStepSize > 0.0 )
  {
    if ( v12 >= *((float *)this + 1139) )
    {
      v13 = (char *)this + 12 * *((_DWORD *)this + 1138);
      v14 = (gbVec3D *)(v13 + 1456);
      v33 = *Vec3D_Cross(&pOut, (gbVec3D *)(v13 + 1468), (gbVec3D *)(v13 + 1456));
      v36 = *Vec3D_Cross(&v38, p_m_fontcolor, v14);
      v15 = ((gbVec3D *)&v33)->Length();
      fStepSizea = v15;
      if ( v15 < 0.000049999999 )
        return 1;
      v16 = ((gbVec3D *)&v33)->DotProduct(&v36) / fStepSizea;
      if ( v16 >= 0.0 && v16 - fStepSizea > -0.1 )
        return 1;
      v17 = (float *)&this->_embed_UIWnd_624.m_childs + 3 * *((_DWORD *)this + 1138);
      v27 = *(int *)v17;
      v28 = v17[1];
      v29 = v17[2];
      goto LABEL_18;
    }
    goto LABEL_6;
  }
  if ( v12 > 0.0 )
  {
LABEL_6:
    v26 = v12;
    sub_4080F0(v26, (int)&v27);
    goto LABEL_18;
  }
  v33 = *Vec3D_Cross(&v38, (gbVec3D *)p_m_needscriptdel, (gbVec3D *)&this->_embed_UIWnd_624.m_benable);
  v36 = *Vec3D_Cross(&pOut, p_m_fontcolor, (gbVec3D *)&this->_embed_UIWnd_624.m_benable);
  v18 = ((gbVec3D *)&v33)->Length();
  fStepSizeb = v18;
  if ( v18 < 0.000049999999 )
    return 1;
  v19 = ((gbVec3D *)&v33)->DotProduct(&v36) / fStepSizeb;
  if ( v19 >= 0.0 && v19 - fStepSizeb > -0.1 )
    return 1;
  v20 = *((float *)p_m_needscriptdel + 1);
  v21 = *((float *)p_m_needscriptdel + 2);
  v27 = *p_m_needscriptdel;
  v28 = v20;
  v29 = v21;
LABEL_18:
  v24 = v29 - p_m_fontcolor->z;
  v23 = v28 - p_m_fontcolor->y;
  v22 = *(float *)&v27 - p_m_fontcolor->x;
  // [AUTO-COMMENTED] v36 = *((gbVec3D *)&v38)->gbVec3D(v22, v23, v24);
  ((gbVec3D *)&this->m_FrameA.m_pbktex)->operator=(&v36);
  ((gbVec3D *)&this->m_FrameA.m_pbktex)->Normalize();
  ((gbVec3D *)&this->m_FrameA.m_pbktex)->operator*=(this->m_FrameA.m_childs.m_needscriptdel);
  return 0;
}

// 0x00413850
double RoleSystem::AdvanceToTarget(double fDelta)
{
  double result; // st7
  int *v15; // ecx
  int v16; // eax
  int *v17; // eax
  float z; // edx
  float v23; // [esp+0x0] [ebp-0x7C]
  float v24; // [esp+0x4] [ebp-0x78]
  double v25; // [esp+0x8] [ebp-0x74]
  float v26; // [esp+0x8] [ebp-0x74]
  int v27; // [esp+0xC] [ebp-0x70]
  gbVec3D *v28; // [esp+0x10] [ebp-0x6C]
  float v30; // [esp+0x18] [ebp-0x64]
  int v32; // [esp+0x1C] [ebp-0x60] BYREF
  int v33; // [esp+0x20] [ebp-0x5C]
  int v34; // [esp+0x24] [ebp-0x58]
  char *m_pLinkedSystem; // [esp+0x28] [ebp-0x54] BYREF
  float m_fAnimSpeed; // [esp+0x2C] [ebp-0x50]
  float v37; // [esp+0x30] [ebp-0x4C]
  gbVec3D v38; // [esp+0x34] [ebp-0x48] BYREF
  _DWORD v39[3]; // [esp+0x40] [ebp-0x3C] BYREF
  float v40[3]; // [esp+0x4C] [ebp-0x30] BYREF
  struct gbVec3D v41; // [esp+0x58] [ebp-0x24] BYREF
  gbVec3D v42; // [esp+0x64] [ebp-0x18] BYREF
  gbVec3D pOut; // [esp+0x70] [ebp-0xC] BYREF
if ( !this->_embed_UIWnd_624.m_rect.bottom )
    goto LABEL_24;
  m_pLinkedSystem = this->m_pLinkedSystem;
  // __asm { fld     [esp+0x70+var_54] }
  __asm
  {
    fsub    dword ptr [esi+4]
    fld     dword ptr [esi+8]
  }
  _EAX = this->m_fMoveRadius;
  m_fAnimSpeed = this->m_fAnimSpeed;
  __asm { fchs }
  v37 = _EAX;
  __asm
  {
    fld     [esp+0x70+var_4C]
    fsub    dword ptr [esi+0x0C]
    fld     st
    fmul    st, st(1)
    fld     st(3)
    fmul    st, st(4)
    faddp   st(1), st
    fld     st(2)
    fmul    st, st(3)
    faddp   st(1), st
    fld     _flt_12_0
    fmul    _flt_12_0
    fcompp
    fstp    st
    fnstsw  ax
    fstp    st
  }
  __asm { fstp    st }
  if ( (BYTE1(_EAX) & 0x41) != 0 )
  {
LABEL_24:
    if ( !this->m_FrameA.m_pfather || this->m_nActionResult )
    {
      __asm
      {
        fld     _flt_12_0
        fmul    _flt_3_0
      }
      _EDI = &this->m_fontcolor;
      __asm
      {
        fst     [esp+0x74+var_64]
        fmul    dword ptr [esi+0x14]
        fld     [esp+0x74+var_64]
        fmul    dword ptr [esi+0x18]
      }
      memset(v39, 0, sizeof(v39));
      __asm
      {
        fstp    [esp+0x7C+var_44]
        fld     [esp+0x7C+var_64]
        fmul    dword ptr [esi+0x1C]
      }
      m_pLinkedSystem = 0;
      m_fAnimSpeed = 0.0;
      // __asm { fstp    [esp+0x7C+var_40] }
      v37 = 0.0;
      __asm
      {
        fadd    dword ptr [edi]
        fstp    [esp+0x7C+var_30]
        fld     [esp+0x7C+var_44]
        fadd    dword ptr [edi+4]
        fstp    [esp+0x7C+var_2C]
        fld     [esp+0x7C+var_40]
        fadd    dword ptr [edi+8]
        fstp    [esp+0x7C+var_28]
      }
      if ( sub_407EC0(v40, v39, &m_pLinkedSystem) )
      {
        __asm
        {
          fld     [esp+0x70+var_4C]
          fmul    dword ptr [esi+0x1C]
          fld     [esp+0x70+var_50]
          fmul    dword ptr [esi+0x18]
          faddp   st(1), st
          fld     [esp+0x70+var_54]
          fmul    dword ptr [esi+0x14]
          faddp   st(1), st
          fcomp   _flt_0_5
          fnstsw  ax
        }
        if ( (_AX & 0x4100) == 0 )
        {
          _EDI = (float *)&this->m_FrameA.m_pbktex;
          this->m_FrameA.m_pbktex = (gbTexture *)this->m_rect.top;
          this->m_nActiveRole = this->m_rect.right;
          this->m_nRoleCount = this->m_rect.bottom;
          // __asm { fld     dword ptr [esi+0x508] }
LABEL_20:
          __asm
          {
            fld     st
            fmul    dword ptr [edi]
          }
          __asm { fstp    dword ptr [edi] }
          *_EDI = _ET1;
          __asm
          {
            fld     st
            fmul    dword ptr [edi+4]
            fstp    dword ptr [edi+4]
          }
          _EDI[1] = _ET1;
          __asm
          {
            fmul    dword ptr [edi+8]
            fstp    dword ptr [edi+8]
          }
          _EDI[2] = _ET1;
          ((RoleSystem *)_ESI)->NormalizeDirection(_EDI);
          return result;
        }
      }
      v32 = 0;
      v33 = 0;
      v34 = 0;
      result = sub_408010(&this->m_fontcolor);
      __asm
      {
        fadd    [esp+0x70+var_64]
        fst     [esp+0x70+var_64]
        fcomp   dword ptr [esi+0x11CC]
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
      {
        sub_4080F0(v30, (int)&v32);
LABEL_19:
        __asm
        {
          fld     [esp+0x70+var_60]
          fsub    dword ptr [edi]
          fld     [esp+0x70+var_5C]
          fsub    dword ptr [edi+4]
          fstp    [esp+0x70+var_20]
          fld     [esp+0x70+var_58]
          fsub    dword ptr [edi+8]
        }
        _EDI = (float *)&this->m_FrameA.m_pbktex;
        // __asm { fstp    [esp+0x70+var_1C] }
        z = v41.z;
        this->m_nActiveRole = LODWORD(v41.y);
        __asm { fstp    dword ptr [edi] }
        *_EDI = _ET1;
        *(float *)&this->m_nRoleCount = z;
        ((gbVec3D *)&this->m_FrameA.m_pbktex)->Normalize();
        // __asm { fld     dword ptr [esi+0x508] }
        goto LABEL_20;
      }
      if ( this->_embed_UIWnd_624.m_rect.bottom )
      {
        ((RoleSystem *)_ESI)->MoveRole((float *)&this->m_pLinkedSystem, LODWORD(this->m_fMoveSpeed), this->m_FrameA.m_childs.m_nSize, 1);
        return result;
      }
      _EAX = 3 * _ESI[1]._todo_074;
      // __asm { fld     dword ptr [esi+eax*4+0x5C4] }
      _EAX = (char *)_ESI + 12 * _ESI[1]._todo_074;
      // __asm { fsub    dword ptr [eax+0x5B8] }
      _EBX = (gbVec3D *)(_EAX + 1456);
      __asm
      {
        fstp    [esp+0x74+var_74]
        fld     dword ptr [eax+0x5C0]
        fsub    dword ptr [ebx+4]
      }
      __asm
      {
        fstp    [esp+0x78+var_78]
        fld     dword ptr [eax+0x5BC]
        fsub    dword ptr [ebx]
      }
      // __asm { fstp    [esp+0x7C+var_7C] }
      // [AUTO-COMMENTED] v38 = *((gbVec3D *)&v42)->gbVec3D(v23, v24, v26);
      v41 = *Vec3D_Cross(&pOut, (gbVec3D *)&this->m_fontcolor, _EBX);
      ((gbVec3D *)&v38)->Length();
      __asm
      {
        fst     [esp+0x70+var_64]
        fcomp   dword ptr [flt_56A9F8]
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
        goto LABEL_14;
      result = ((gbVec3D *)&v38)->DotProduct(&v41);
      __asm
      {
        fdiv    [esp+0x70+var_64]
        fcom    dword ptr [flt_56A644]
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
      {
        __asm { fstp    st }
      }
      else
      {
        __asm
        {
          fsub    [esp+0x70+var_64]
          fcomp   dword ptr [flt_56A9F4]
          fnstsw  ax
        }
        if ( (_AX & 0x4100) == 0 )
        {
LABEL_14:
          LODWORD(v25) = (char *)_ESI + 8692;
          v15 = (int *)&this->_embed_UIWnd_624.m_childs + 3 * _ESI[1]._todo_074;
          *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 79) = *v15;
          *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 83) = v15[1];
          *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 87) = v15[2];
          result = ((RoleSystem *)_ESI)->UpdateMovement(v25, v28);
          if ( v16 )
            ((RoleSystem *)_ESI)->SetMoveSpeed(0.0, 0, v27);
          return result;
        }
      }
      v17 = (int *)&this->_embed_UIWnd_624.m_childs + 3 * _ESI[1]._todo_074;
      v32 = *v17;
      v33 = v17[1];
      v34 = v17[2];
      goto LABEL_19;
    }
  }
  return result;
}

// 0x00413C00
int RoleSystem::PlaceAtRegion(int nSceneIdx, int nRegion)
{
  RoleSystem *v4; // eax
  int RolePtr; // esi
  _DWORD *v6; // ecx
  __int64 v7; // rax
  double v8; // st7
  int result; // eax
  float v10; // [esp+0x14] [ebp-0x4]

  *(_DWORD *)this->m_partyActor.m_szTexture = nSceneIdx;
  v4 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v4)->GetRolePtr(nSceneIdx);
  v6 = (_DWORD *)(16 * nRegion + RolePtr);
  v7 = *v6 + v6[2];
  v8 = ((double)(((int)v7 - HIDWORD(v7)) >> 1) + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 128);
  v10 = ((double)((v6[1] + v6[3]) / 2) + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 136);
  this->m_wndcolor.Color = 0;
  *(float *)&this->m_fontcolor.Color = v8;
  *(float *)&this->m_id = v10;
  result = this->m_fontcolor.Color;
  *((_DWORD *)this + 2173) = result;
  *((_DWORD *)this + 2174) = this->m_wndcolor.Color;
  *((_DWORD *)this + 2175) = this->m_id;
  return result;
}

// 0x00413CD0
void RoleSystem::PathFollowUpdate()
{
  RoleSystem *v5; // eax
  RoleSystem *v6; // eax
  int v10; // eax
  int v11; // eax
  char *m_pCtrlPoint; // edx
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  LONG right; // edx
  _BYTE fScale[12]; // [esp+0x14] [ebp-0x50]
  float fScalea; // [esp+0x14] [ebp-0x50]
  float fScaleb; // [esp+0x14] [ebp-0x50]
  int v30; // [esp+0x18] [ebp-0x4C]
  int v34; // [esp+0x28] [ebp-0x3C]
  int v35; // [esp+0x28] [ebp-0x3C]
  int v36; // [esp+0x28] [ebp-0x3C]
  float v37; // [esp+0x2C] [ebp-0x38]
  float v38; // [esp+0x30] [ebp-0x34]
  gbVec3D v39; // [esp+0x34] [ebp-0x30] BYREF
  gbVec3D v40; // [esp+0x40] [ebp-0x24] BYREF
  gbVec3D pOut; // [esp+0x4C] [ebp-0x18] BYREF
  gbVec3D v42; // [esp+0x58] [ebp-0xC] BYREF
switch ( this->m_FrameA.m_rect.bottom )
  {
    case 1:
      __asm
      {
        fld     dword ptr [esi+0x50C]; jumptable 00413CE8 case 1
        fmul    _flt_0_2
        fstp    [esp+0x4C+var_40]
      }
      v34 = rand();
      __asm
      {
        fild    [esp+0x4C+var_3C]
        fmul    dword ptr [flt_56AA04]
        fsub    _flt_1_0
        fstp    [esp+0x4C+var_34]
      }
      v35 = rand();
      __asm
      {
        fild    [esp+0x4C+var_3C]
        fmul    dword ptr [flt_56AA04]
        fsub    _flt_1_0
        fstp    [esp+0x4C+var_38]
      }
      v36 = rand();
      // __asm { fild    [esp+0x4C+var_3C] }
      v40.z = v38;
      __asm { fmul    _flt_6_103702eneg05 }
      v40.y = v37;
      __asm
      {
        fsub    _flt_1_0
        fstp    [esp+0x4C+var_24]
      }
      gbVec3D::Normalize(&v40);
      // __asm { fld     [esp+0x4C+var_24] }
      _EDI = (float *)&this->_todo_5AC;
      __asm { fmul    _flt_0_2 }
      pOut.z = v40.z;
      __asm
      {
        fld     [esp+0x4C+pOut.z]
        fmul    _flt_0_2
      }
      pOut.x = v40.x;
      m_pCtrlPoint = this->m_pCtrlPoint;
      pOut.y = v40.y;
      this->m_pCtrlPoint = m_pCtrlPoint;
      __asm
      {
        fstp    [esp+0x4C+pOut.z]
        fadd    dword ptr [edi]
        fstp    dword ptr [edi]
      }
      *_EDI = _ET1;
      __asm
      {
        fld     [esp+0x4C+pOut.z]
        fadd    dword ptr [edi+8]
        fstp    dword ptr [edi+8]
      }
      _EDI[2] = _ET1;
      ((gbVec3D *)&this->_todo_5AC)->Normalize();
      fScalea = *(float *)&this->_todo_5AC;
      memset(&v39, 0, sizeof(v39));
      memset(&v40, 0, sizeof(v40));
      v16 = Vec3D_Lerp(&v42.x, (float *)&this->m_pfather, fScalea);
      ((gbVec3D *)&v39)->operator=(v16);
      v17 = Vec3D_Lerp(&v42.x, (float *)&this->m_childs.m_nSize, *(float *)&this->m_pCtrlPoint);
      ((gbVec3D *)&v40)->operator=(v17);
      ((gbVec3D *)&v39)->operator+=(&v40);
      v18 = Vec3D_Lerp(&v42.x, (float *)&this->m_rect.top, *(float *)&this->m_nMoveRole);
      ((gbVec3D *)&v40)->operator=(v18);
      ((gbVec3D *)&v39)->operator+=(&v40);
      __asm
      {
        fld     [esp+0x4C+var_30]
        fmul    [esp+0x4C+var_40]
      }
      _EAX = (float *)&this->m_nAnimation;
      this->m_nAnimation = this->m_rect.top;
      right = this->m_rect.right;
      __asm
      {
        fstp    [esp+0x4C+var_30]
        fld     [esp+0x4C+var_2C]
        fmul    [esp+0x4C+var_40]
      }
      this->m_nAnimCopy1 = right;
      this->m_nAnimCopy2 = this->m_rect.bottom;
      __asm
      {
        fstp    [esp+0x50+var_2C]
        fld     [esp+0x50+var_28]
        fmul    [esp+0x50+var_40]
        fstp    [esp+0x50+var_28]
        fld     [esp+0x50+var_40]
        fmul    dword ptr [flt_56AA00]
        fld     st
        fmul    dword ptr [eax]
        fstp    dword ptr [eax]
      }
      *_EAX = _ET1;
      __asm
      {
        fld     st
        fmul    dword ptr [eax+4]
        fstp    dword ptr [eax+4]
      }
      _EAX[1] = _ET1;
      __asm
      {
        fmul    dword ptr [eax+8]
        fstp    dword ptr [eax+8]
      }
      _EAX[2] = _ET1;
      __asm
      {
        fld     [esp+0x50+var_30]
        fadd    dword ptr [eax]
        fstp    dword ptr [eax]
      }
      *_EAX = _ET1;
      __asm
      {
        fld     [esp+0x50+var_2C]
        fadd    dword ptr [eax+4]
        fstp    dword ptr [eax+4]
      }
      _EAX[1] = _ET1;
      __asm
      {
        fld     [esp+0x50+var_28]
        fadd    dword ptr [eax+8]
        fstp    dword ptr [eax+8]
      }
      _EAX[2] = _ET1;
      __asm
      {
        fld     dword ptr [esi+0x50C]
        fmul    _flt_0_3
        fstp    [esp+0x50+fScale]; fScale
      }
      RoleSystem::ScaleVector((float *)&this->m_nAnimation, fScaleb);
      this->m_nAnimCopy1 = 0;
      return;
    case 2:
      this->AdvanceToTarget(*(double *)&fScale[4]);
      goto LABEL_22;
    case 4:
      this->InterpolateMoveFrame(1.0);
      v40 = *Vec3D_Cross(&v42, (gbVec3D *)&this->m_pLinkedSystem, (gbVec3D *)&this->m_pRenderObj);
      v39 = *Vec3D_Cross(&pOut, (gbVec3D *)&this->m_fontcolor, (gbVec3D *)&this->m_pRenderObj);
      ((gbVec3D *)&v40)->Length();
      __asm
      {
        fst     [esp+0x4C+var_40]
        fcomp   dword ptr [flt_56A9F8]
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
        goto LABEL_13;
      __asm
      {
        fld     [esp+0x4C+var_1C]
        fmul    [esp+0x4C+var_28]
        fld     [esp+0x4C+var_20]
        fmul    [esp+0x4C+var_2C]
        faddp   st(1), st
        fld     [esp+0x4C+var_30]
        fmul    [esp+0x4C+var_24]
        faddp   st(1), st
        fdiv    [esp+0x4C+var_40]
        fcom    _flt_0_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
        goto LABEL_25;
      __asm
      {
        fsub    [esp+0x4C+var_40]
        fcomp   dword ptr [flt_56A9F4]
        fnstsw  ax
      }
      if ( (_AX & 0x4100) == 0 )
      {
LABEL_13:
        ((RoleSystem *)_ESI)->NotifyMoveComplete();
        *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 79) = (int)this->m_pLinkedSystem;
        *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 83) = LODWORD(this->m_fAnimSpeed);
        *(int *)((char *)&_ESI[1].m_partyUI3._todo_05C + 87) = LODWORD(this->m_fMoveRadius);
        if ( this->m_FrameA.m_rect.right != 4 || LODWORD(this->m_fRotAxisZ) != 7 )
        {
          *(_DWORD *)fScale = (char *)_ESI + 8692;
          ((RoleSystem *)_ESI)->UpdateMovement(*(double *)fScale, *(gbVec3D **)&fScale[8]);
          if ( v10 )
            ((RoleSystem *)_ESI)->SetMoveSpeed(0.0, 0, v30);
        }
      }
      return;
    case 5:
      v6 = g_pRoleSystem;
      if ( g_pRoleSystem )
      {
        this->m_pLinkedSystem = (char *)g_pRoleSystem->m_fontcolor.Color;
        LODWORD(this->m_fAnimSpeed) = v6->m_wndcolor.Color;
        LODWORD(this->m_fMoveRadius) = v6->m_id;
        this->InterpolateMoveFrame(1.0);
      }
      return;
    case 6:
      v5 = g_pRoleSystem;
      if ( g_pRoleSystem )
      {
        this->m_pLinkedSystem = (char *)g_pRoleSystem->m_fontcolor.Color;
        LODWORD(this->m_fAnimSpeed) = v5->m_wndcolor.Color;
        LODWORD(this->m_fMoveRadius) = v5->m_id;
        this->InterpolateMoveFrame(-1.0);
      }
      return;
    case 7:
      this->AdvanceToTarget(*(double *)&fScale[4]);
      if ( *(_DWORD *)this->m_partyActor.m_szTexture == LODWORD(this->m_fMoveSpeed) )
      {
LABEL_22:
        if ( v11 )
LABEL_20:
          ((RoleSystem *)_ESI)->NotifyMoveComplete();
      }
      else if ( ((RoleSystem *)_ESI)->ApproachTarget(this->m_nMoveReset)
             && !((RoleSystem *)&g_szSceneUIText[184])->BindRoleToScene(*(_DWORD *)this->m_partyActor.m_szTexture, (float *)&this->m_fontcolor.Color, (float *)&this->m_pLinkedSystem, (int)&this->_embed_UIWnd_624.m_childs.m_needscriptdel, this->m_nFacing) )
      {
        goto LABEL_20;
      }
      return;
    case 8:
      v40 = *Vec3D_Cross(&pOut, (gbVec3D *)&this->m_pLinkedSystem, (gbVec3D *)&this->m_pRenderObj);
      v39 = *Vec3D_Cross(&v42, (gbVec3D *)&this->m_fontcolor, (gbVec3D *)&this->m_pRenderObj);
      ((gbVec3D *)&v40)->Length();
      __asm
      {
        fst     [esp+0x4C+var_40]
        fcomp   dword ptr [flt_56A9F8]
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
        goto LABEL_5;
      __asm
      {
        fld     [esp+0x4C+var_1C]
        fmul    [esp+0x4C+var_28]
        fld     [esp+0x4C+var_20]
        fmul    [esp+0x4C+var_2C]
        faddp   st(1), st
        fld     [esp+0x4C+var_30]
        fmul    [esp+0x4C+var_24]
        faddp   st(1), st
        fdiv    [esp+0x4C+var_40]
        fcom    _flt_0_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
      {
LABEL_25:
        __asm { fstp    st }
      }
      else
      {
        __asm
        {
          fsub    [esp+0x4C+var_40]
          fcomp   dword ptr [flt_56A9F4]
          fnstsw  ax
        }
        if ( (_AX & 0x4100) == 0 )
        {
LABEL_5:
          this->m_FrameA.m_rect.bottom = 0;
          this->m_FrameA.m_bvisible = 0;
          this->m_FrameA.m_benable = 0;
          this->m_FrameA.m_bfocus = 0;
          this->m_FrameA.m_pbktex = 0;
          this->m_nActiveRole = this->m_FrameA.m_benable;
          this->m_nRoleCount = this->m_FrameA.m_bfocus;
        }
      }
      return;
    default:
      return;
  }
}

// 0x00414250
void RoleSystem::NormalizeDirection(float *pfDir)
{
  float *p_m_nAnimation; // esi
  double v3; // st7
  double v4; // st6
  double v5; // st7
  double v6; // st7
  int v7; // [esp+0x8] [ebp-0x8]
  int v8; // [esp+0xC] [ebp-0x4]
  float *pfDira; // [esp+0x14] [ebp+0x4]

  p_m_nAnimation = (float *)&this->m_nAnimation;
  v3 = *pfDir - *(float *)&this->m_FrameA.m_bvisible;
  *(float *)&v7 = pfDir[1] - *(float *)&this->m_FrameA.m_benable;
  v4 = pfDir[2] - *(float *)&this->m_FrameA.m_bfocus;
  this->m_nAnimCopy1 = v7;
  *(float *)&v8 = v4;
  *(float *)&this->m_nAnimation = v3;
  this->m_nAnimCopy2 = v8;
  pfDira = (float *)this->m_FrameA.m_bcreateok;
  v5 = ((gbVec3D *)&this->m_nAnimation)->Length();
  if ( v5 > *(float *)&pfDira )
  {
    v6 = *(float *)&pfDira / v5;
    *p_m_nAnimation = v6 * *p_m_nAnimation;
    p_m_nAnimation[1] = v6 * p_m_nAnimation[1];
    p_m_nAnimation[2] = v6 * p_m_nAnimation[2];
  }
}

// 0x004142E0
int RoleSystem::NotifyMoveComplete()
{
  int result; // eax

  this->m_FrameA.m_rect.bottom = 0;
  this->m_FrameA.m_childs.m_nSize = 0;

  this->m_FrameA.m_bvisible = 0;
  this->m_FrameA.m_benable = 0;
  this->m_FrameA.m_bfocus = 0;
  this->m_FrameA.m_pbktex = 0;
  this->m_nActiveRole = this->m_FrameA.m_benable;
  this->m_nRoleCount = this->m_FrameA.m_bfocus;
  result = (int)this->m_FrameA.m_pfather;
  if ( result )
  {
    this->m_FrameA.m_pfather = 0;
    *(_DWORD *)&this->m_partyActor.m_szTexture[4] = 0;
  }
  return result;
}

// 0x00414350
double RoleSystem::UpdateMovement(double result, gbVec3D *pB)
{
  RoleSystem *v4; // ebp
  char *v5; // edi
  int RolePtr; // ebx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  float *v12; // edi
  int v13; // edx
  double v14; // st6
  double v15; // st6
  double v16; // st7
  float v17; // edx
  double v18; // st7
  float v19; // ecx
  double v20; // st6
  float z; // eax
  float v22; // ecx
  void *m_id; // edx
  float x; // eax
  float y; // ecx
  float v26; // edx
  int *v27; // [esp-0xC] [ebp-0x40]
  gbVec3D nFlag; // [esp+0x10] [ebp-0x24] BYREF
  gbVec3D pfVal2; // [esp+0x1C] [ebp-0x18] BYREF
  gbVec3D v30; // [esp+0x28] [ebp-0xC] BYREF
  float resulta; // [esp+0x38] [ebp+0x4]

  v4 = (RoleSystem *)UISceneUpdate();
  v5 = (char *)LODWORD(result);
  RolePtr = ((RoleSystem *)v4)->GetRolePtr(*(_DWORD *)this->m_partyActor.m_szTexture);
  v7 = *(float *)(LODWORD(result) + 8) - *(float *)(RolePtr + 136);
  LODWORD(nFlag.x) = (__int64)((*(float *)LODWORD(result) - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v8 = v7 / g_fSceneTileSize;
  if ( ((RoleSystem *)v4)->CheckCollision(*(int **)this->m_partyActor.m_szTexture, SLODWORD(nFlag.x)) )
    goto LABEL_2;
  if ( this->m_FrameA.m_rect.bottom != 2 )
    goto LABEL_23;
  v5 = (char *)this + 8692;
  nFlag.x = sub_408010((char *)this + 8692);
  sub_4080F0(nFlag.x, (int)this + 8692);
  *((_DWORD *)this + 2174) = 0;
  nFlag.x = *((float *)this + 2173) - *(float *)&this->m_fontcolor.Color;
  v9 = *((float *)this + 2174) - *(float *)&this->m_wndcolor.Color;
  pfVal2.x = nFlag.x;
  nFlag.y = v9;
  v10 = *((float *)this + 2175) - *(float *)&this->m_id;
  pfVal2.y = nFlag.y;
  nFlag.z = v10;
  pfVal2.z = nFlag.z;
  v8 = ((gbVec3D *)&pfVal2)->Length();
  if ( v8 <= 0.050000001 )
    goto LABEL_23;
  ((gbVec3D *)&pfVal2)->Normalize();
  v8 = pfVal2.y * *(float *)&this->m_rect.right
     + pfVal2.z * *(float *)&this->m_rect.bottom
     + pfVal2.x * *(float *)&this->m_rect.top;
  if ( v8 > 0.0
    && (v11 = *((float *)this + 2175) - *(float *)(RolePtr + 136),
        LODWORD(nFlag.x) = (__int64)((*(float *)v5 - *(float *)(RolePtr + 128)) / g_fSceneTileSize),
        v8 = v11 / g_fSceneTileSize,
        ((RoleSystem *)v4)->CheckCollision(*(int **)this->m_partyActor.m_szTexture, SLODWORD(nFlag.x)))
    && (v30 = *Vec3D_Cross(&nFlag, (gbVec3D *)((char *)this + 8692), (gbVec3D *)LODWORD(result)),
        v8 = ((gbVec3D *)&v30)->Length(),
        v8 < 12.0) )
  {
LABEL_2:
    this->_embed_UIWnd_624.m_childs.m_pData = (char *)LODWORD(this->m_fPosX);
    this->_embed_UIWnd_624.m_childs.capacity = LODWORD(this->m_fPosY);
    this->_embed_UIWnd_624.m_childs.m_nSize = LODWORD(this->m_fPosZ);
    this->m_fontcolor.Color = *(_DWORD *)v5;
    this->m_wndcolor.Color = *((_DWORD *)v5 + 1);
    this->m_id = (void *)*((_DWORD *)v5 + 2);
  }
  else
  {
LABEL_23:
    if ( this->m_FrameA.m_rect.right != 3 )
      goto LABEL_20;
    nFlag.x = 0.0;
    memset(&pfVal2, 0, sizeof(pfVal2));
    if ( (g_szSceneUIText[72] & 1) == 0 )
    {
      g_szSceneUIText[72] |= 1u;
      v30.x = 12.0 * 0.5;
      v30.z = v30.x;
      *(float *)&g_szSceneUIText[24] = v30.x;
      *(_DWORD *)&g_szSceneUIText[28] = 0;
      v30.x = 12.0 * -0.5;
      *(float *)&g_szSceneUIText[32] = v30.z;
      v30.z = 12.0 * 0.5;
      *(float *)&g_szSceneUIText[36] = v30.x;
      *(_DWORD *)&g_szSceneUIText[40] = 0;
      *(float *)&g_szSceneUIText[44] = v30.z;
      *(float *)&g_szSceneUIText[48] = 12.0;
      v30.x = -12.0;
      *(_DWORD *)&g_szSceneUIText[52] = 0;
      *(_DWORD *)&g_szSceneUIText[56] = 0;
      v30.y = 0.0;
      v30.z = 0.0;
      *(float *)&g_szSceneUIText[60] = v30.x;
      *(_DWORD *)&g_szSceneUIText[64] = 0;
      *(_DWORD *)&g_szSceneUIText[68] = 0;
      atexit(nullsub_6);
    }
    v12 = (float *)&g_szSceneUIText[24];
    do
    {
      this->UpdateMoveInterpolation(v12, &pfVal2.x);
      LOBYTE(v13) = this->m_nFacing;
      v27 = *(int **)this->m_partyActor.m_szTexture;
      pfVal2.x = pfVal2.x + *(float *)&this->m_fontcolor.Color;
      pfVal2.y = pfVal2.y + *(float *)&this->m_wndcolor.Color;
      v8 = pfVal2.z + *(float *)&this->m_id;
      pfVal2.z = v8;
      if ( ((RoleSystem *)v4)->CheckMoveCollision(v27, &pfVal2.x, v13) )
      {
        v8 = pfVal2.x - *(float *)&this->m_fontcolor.Color;
        v14 = pfVal2.y - *(float *)&this->m_wndcolor.Color;
        LODWORD(nFlag.x) = 1;
        v30.y = v14;
        v15 = pfVal2.z - *(float *)&this->m_id;
        pfVal2.y = v30.y;
        v30.z = v15;
        pfVal2.x = v8;
        pfVal2.z = v30.z;
      }
      v12 += 3;
    }
    while ( (int)v12 < (int)&g_szSceneUIText[72] );
    if ( !LODWORD(nFlag.x) )
      goto LABEL_20;
    v16 = *(float *)LODWORD(result) - *(float *)&this->m_fontcolor.Color;
    v17 = *(float *)(LODWORD(result) + 8);
    nFlag.y = *(float *)(LODWORD(result) + 4);
    nFlag.z = v17;
    nFlag.x = v16;
    nFlag.y = nFlag.y - *(float *)&this->m_wndcolor.Color;
    nFlag.z = v17 - *(float *)&this->m_id;
    resulta = ((gbVec3D *)&nFlag)->Length();
    ((gbVec3D *)&pfVal2)->Normalize();
    v18 = 0.0;
    if ( pfVal2.z * *(float *)&this->m_nTransformMode + pfVal2.x * *(float *)&this->m_nAnimCopy3 < -0.1 )
    {
      v19 = *(float *)&this->m_nTransformMode;
      v18 = *(float *)&this->m_pLinkedRole;
      LODWORD(pfVal2.x) = this->m_nAnimCopy3;
      pfVal2.z = v19;
    }
    *(float *)&this->m_pLinkedRole = v18;
    v20 = pfVal2.x * resulta;
    z = pfVal2.z;
    this->m_nAnimCopy3 = LODWORD(pfVal2.x);
    *(float *)&this->m_nTransformMode = z;
    v22 = *(float *)&this->m_wndcolor.Color;
    m_id = this->m_id;
    pfVal2.x = v20;
    nFlag.y = v22;
    LODWORD(nFlag.z) = m_id;
    pfVal2.y = v18 * resulta;
    pfVal2.z = pfVal2.z * resulta;
    nFlag.x = *(float *)&this->m_fontcolor.Color + pfVal2.x;
    nFlag.y = v22 + pfVal2.y;
    nFlag.z = *(float *)&m_id + pfVal2.z;
    v8 = (nFlag.z - *(float *)(RolePtr + 136)) / g_fSceneTileSize;
    if ( ((RoleSystem *)v4)->CheckCollision(*(int **)this->m_partyActor.m_szTexture, (__int64)((nFlag.x - *(float *)(RolePtr + 128)) / g_fSceneTileSize)) )
    {
      this->_embed_UIWnd_624.m_childs.m_pData = (char *)this->m_fontcolor.Color;
      x = nFlag.x;
      this->_embed_UIWnd_624.m_childs.capacity = this->m_wndcolor.Color;
      y = nFlag.y;
      this->_embed_UIWnd_624.m_childs.m_nSize = (int)this->m_id;
      v26 = nFlag.z;
      *(float *)&this->m_fontcolor.Color = x;
      *(float *)&this->m_wndcolor.Color = y;
      *(float *)&this->m_id = v26;
    }
    else
    {
LABEL_20:

    }
  }
  return v8;
}

// 0x004148C0
float * RoleSystem::UpdateMoveInterpolation(float *pfVal, float *pfVal2)
{
  float *result; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st6
  double v8; // st6
  double v9; // st7
  double v10; // st6
  double v11; // st6
  float v12; // [esp+0x4] [ebp-0x18]
  float v13; // [esp+0x8] [ebp-0x14]
  float v14; // [esp+0x10] [ebp-0xC]
  float v15; // [esp+0x10] [ebp-0xC]
  float v16; // [esp+0x14] [ebp-0x8]
  float v17; // [esp+0x14] [ebp-0x8]
  float pfVala; // [esp+0x20] [ebp+0x4]
  float pfVal2a; // [esp+0x24] [ebp+0x8]

  result = pfVal2;
  v5 = *pfVal;
  v12 = v5 * *(float *)&this->m_pfather;
  v13 = v5 * *(float *)&this->m_childs.m_pData;
  v6 = v5 * *(float *)&this->m_childs.capacity;
  pfVal2[1] = v13;
  *pfVal2 = v12;
  pfVal2[2] = v6;
  v7 = pfVal[1];
  v14 = v7 * *(float *)&this->m_childs.m_nSize;
  v16 = v7 * *(float *)&this->m_childs.m_needscriptdel;
  v8 = v7 * *(float *)&this->m_bcreateok;
  pfVala = v14 + v12;
  *pfVal2 = pfVala;
  pfVal2a = v16 + v13;
  result[1] = pfVal2a;
  v9 = v6 + v8;
  result[2] = v9;
  v10 = pfVal[2];
  v15 = v10 * *(float *)&this->m_rect.top;
  v17 = v10 * *(float *)&this->m_rect.right;
  v11 = v10 * *(float *)&this->m_rect.bottom;
  *result = pfVala + v15;
  result[1] = pfVal2a + v17;
  result[2] = v9 + v11;
  return result;
}

// 0x00414980
void RoleSystem::GetPosition(float *pOut,   int nVal)
{
  gbVec3D *p_m_pbktex; // esi
  double v5; // st7

  p_m_pbktex = (gbVec3D *)&this->m_FrameA.m_pbktex;
  this->m_FrameA.m_pbktex = *(gbTexture **)pOut;
  this->m_nActiveRole = (int)pOut[1];
  this->m_nRoleCount = (int)pOut[2];
  this->m_FrameA.m_childs.m_nSize = nVal;

  if ( nVal )
  {
    this->m_nActiveRole = 0;
    ((gbVec3D *)p_m_pbktex)->Normalize();
    v5 = *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
    p_m_pbktex->x = v5 * p_m_pbktex->x;
    p_m_pbktex->y = v5 * p_m_pbktex->y;
    p_m_pbktex->z = v5 * p_m_pbktex->z;
    this->m_FrameA.m_rect.bottom = 12;
  }
  else
  {
    this->m_FrameA.m_rect.bottom = 0;
  }
}

// 0x00414A10
void RoleSystem::UpdateMoveTimer()
{
  *(float *)&g_szSceneUIText[16] = 12.0 * 14.0;
}

// 0x00414A30
int RoleSystem::PathFind(float *pTarget)
{
  double v2; // st6
  LONG right; // eax
  double v5; // st7
  double v6; // st7
  float y; // ecx
  double v8; // st7
  double v9; // st6
  UIFrameWnd *p_m_FrameA; // ebp
  float v11; // ecx
  double v12; // st6
  RoleSystem *v13; // eax
  RoleSystem *v14; // eax
  int RolePtr; // edi
  int *v16; // ebx
  double v17; // st7
  __int64 v18; // rax
  double v19; // st7
  RoleSystem *v20; // eax
  double v21; // st7
  int *v22; // ecx
  int v23; // edx
  int v24; // eax
  float v25; // eax
  Scene *v26; // eax
  long double v27; // st7
  long double v28; // st6
  long double v29; // rt0
  long double v30; // st6
  double v31; // st7
  double v32; // st7
  float v33; // edx
  long double v34; // st6
  double v35; // st6
  int result; // eax
  double v37; // st6
  int *v38; // [esp-0x18] [ebp-0x5C]
  int v39; // [esp-0x10] [ebp-0x54]
  int *v40; // [esp-0x10] [ebp-0x54]
  int v41; // [esp-0x10] [ebp-0x54]
  char *v42; // [esp-0xC] [ebp-0x50]
  int v43; // [esp-0xC] [ebp-0x50]
  int v44; // [esp-0x8] [ebp-0x4C]
  int v45; // [esp-0x8] [ebp-0x4C]
  int v46; // [esp-0x4] [ebp-0x48]
  int *a7; // [esp+0x10] [ebp-0x34] BYREF
  int nY; // [esp+0x14] [ebp-0x30]
  char *pszBuf; // [esp+0x18] [ebp-0x2C]
  float v50; // [esp+0x20] [ebp-0x24]
  int *pnVal; // [esp+0x24] [ebp-0x20]
  float v52; // [esp+0x28] [ebp-0x1C]
  gbVec3D v53; // [esp+0x2C] [ebp-0x18] BYREF
  gbVec3D v54; // [esp+0x38] [ebp-0xC] BYREF

  right = this->m_FrameA.m_rect.right;
  this->m_fRotAxisZ = 0.0;
  this->m_nMovement = 0;
  if ( right != 4 )
    this->m_FrameA.m_rect.top = right;
  this->m_FrameA.m_rect.right = 4;
  v54.x = *pTarget - *(float *)&this->m_fontcolor.Color;
  v5 = pTarget[1] - *(float *)&this->m_wndcolor.Color;
  v53.x = v54.x;
  v54.y = v5;
  v6 = pTarget[2] - *(float *)&this->m_id;
  y = v54.y;
  pTarget[1] = 0.0;
  v53.y = y;
  v54.z = v6;
  v53.z = v54.z;
  v8 = ((gbVec3D *)&v53)->Length();
  if ( v2 <= *(float *)&g_szSceneUIText[16] )
  {
    p_m_FrameA = &this->m_FrameA;
// [VFTABLE] this->m_FrameA.__vftable = *(vtbl_0056AE2C **)pTarget;
    this->m_FrameA.m_fontcolor.Color = (unsigned int)pTarget[1];
    this->m_FrameA.m_wndcolor.Color = (unsigned int)pTarget[2];
  }
  else
  {
    v9 = *(float *)&g_szSceneUIText[16] / v2;
    p_m_FrameA = &this->m_FrameA;
    v53.x = v53.x * v9;
    v53.y = v53.y * v9;
    v53.x = v53.x + *(float *)&this->m_fontcolor.Color;
    v53.y = v53.y + *(float *)&this->m_wndcolor.Color;
    v11 = v53.y;
    v12 = v9 * v53.z + *(float *)&this->m_id;
// [VFTABLE] this->m_FrameA.__vftable = (vtbl_0056AE2C *)LODWORD(v53.x);
    *(float *)&this->m_FrameA.m_fontcolor.Color = v11;
    v53.z = v12;
    *(float *)&this->m_FrameA.m_wndcolor.Color = v12;
  }
  v39 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v13 = (RoleSystem *)UISceneUpdate();
  ((RoleSystem *)v13)->SetRoleParam(v39, (float *)p_m_FrameA, 0, 0);
  *(float *)&this->m_FrameA.m_fontcolor.Color = v8;
  if ( !m_bPathEnabled )
  {
    v46 = *(_DWORD *)this->m_partyActor.m_szTexture;
    v14 = (RoleSystem *)UISceneUpdate();
    RolePtr = ((RoleSystem *)v14)->GetRolePtr(v46);
    v16 = (int *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
// [VFTABLE] v17 = *(float *)&p_m_FrameA->__vftable - *(float *)(RolePtr + 128);
    pnVal = (int *)(__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
    v18 = (__int64)(v17 / g_fSceneTileSize);
    v19 = *(float *)&p_m_FrameA->m_wndcolor.Color - *(float *)(RolePtr + 136);
    pszBuf = (char *)v18;
    v44 = (__int64)(v19 / g_fSceneTileSize);
    v42 = (char *)v18;
    v40 = pnVal;
    v38 = *(int **)this->m_partyActor.m_szTexture;
    v20 = (RoleSystem *)UISceneUpdate();
    if ( !((RoleSystem *)v20)->GetPathTarget(v38, v16, v40, v42, v44, &a7) )
    {
      v21 = 0.0;
      v22 = a7;
      v23 = nY;
      v50 = ((double)(int)a7 + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 128);
      v52 = ((double)nY + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 136);
      if ( (int)a7 >= 0 )
      {
        v24 = *(_DWORD *)(RolePtr + 152);
        if ( (int)a7 < v24 && nY >= 0 && nY < *(_DWORD *)(RolePtr + 156) )
          v21 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * ((_DWORD)a7 + nY * v24));
      }
      v25 = v50;
      *(float *)&p_m_FrameA->m_fontcolor.Color = v21;
// [VFTABLE] *(float *)&p_m_FrameA->__vftable = v25;
      v45 = v23;
      *(float *)&p_m_FrameA->m_wndcolor.Color = v52;
      v43 = (int)v22;
      v41 = *(_DWORD *)this->m_partyActor.m_szTexture;
      v26 = (Scene *)UISceneUpdate();
      *(float *)&this->m_FrameA.m_fontcolor.Color = ((Scene *)v26)->GetTileHeight(v41, v43, v45, 0);
    }
  }
// [VFTABLE] this->m_FrameA.m_bvisible = (int)p_m_FrameA->__vftable;
  this->m_FrameA.m_benable = p_m_FrameA->m_fontcolor.Color;
  this->m_FrameA.m_bfocus = p_m_FrameA->m_wndcolor.Color;
  *(float *)&this->m_FrameA.m_bvisible = *(float *)&this->m_FrameA.m_bvisible - this->m_fPosX;
  *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable - this->m_fPosY;
  *(float *)&this->m_FrameA.m_bfocus = *(float *)&this->m_FrameA.m_bfocus - this->m_fPosZ;
  this->m_FrameA.m_benable = 0;
  ((gbVec3D *)&this->m_FrameA.m_bvisible)->Normalize();

  v27 = sqrt((50.0 + 50.0) / 490.0);
  *(float *)&this->m_FrameA.m_id = v27;
  v28 = fabs(*(float *)&this->m_FrameA.m_fontcolor.Color - this->m_fPosY);
  this->m_FrameA.m_rect.left = 0;
  v29 = sqrt((v28 + 50.0 + v28 + 50.0) / 490.0);
  v30 = v27;
  *(float *)&this->m_FrameA.m_id = v29 + v27;
// [VFTABLE] v50 = *(float *)&p_m_FrameA->__vftable - this->m_fPosX;
  v31 = *(float *)&p_m_FrameA->m_fontcolor.Color - this->m_fPosY;
  v54.x = v50;
  *(float *)&pnVal = v31;
  v32 = *(float *)&p_m_FrameA->m_wndcolor.Color - this->m_fPosZ;
  this->m_FrameA.m_benable = 0;
  v52 = v32;
  v33 = v52;
  this->m_FrameA.m_bvisible = LODWORD(v54.x);
  v54.z = v33;
  v54.y = 0.0;
  *(float *)&this->m_FrameA.m_bfocus = v33;
  ((gbVec3D *)&this->m_FrameA.m_bvisible)->Normalize();
  ((gbVec3D *)&v54)->Length();
  v34 = v30 / *(float *)&this->m_FrameA.m_id;
  *(float *)&this->m_FrameA.m_bvisible = v34 * *(float *)&this->m_FrameA.m_bvisible;
  *(float *)&this->m_FrameA.m_benable = v34 * *(float *)&this->m_FrameA.m_benable;
  *(float *)&this->m_FrameA.m_bfocus = v34 * *(float *)&this->m_FrameA.m_bfocus;
  v35 = 50.0;
  if ( *(float *)&this->m_FrameA.m_fontcolor.Color > (double)this->m_fPosY )
    v35 = *(float *)&this->m_FrameA.m_fontcolor.Color - this->m_fPosY + 50.0;
  this->m_FrameA.m_childs.m_nSize = 4;
  *(float *)&this->m_FrameA.m_benable = sqrt((v35 + v35) / 490.0) * 490.0;
  ((Actor *)&this->m_partyActor.m_nActionType)->CompareActionName(4, 2);
  ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(4.0);
  v37 = *(float *)&this->m_FrameA.m_id + 0.5;
  *(float *)&this->m_FrameA.m_id = v37;
  *(float *)&this->m_FrameA.m_id = v37 + 0.5;
  return result;
}

// 0x00414E30
int RoleSystem::GetActionByIndex(int nParam)
{
  int nMode; // [esp+0x8] [ebp+0x8]

  return this->PlayAction((&pszAction)[nParam], nMode);
}

// 0x00414F90
int RoleSystem::PlayAction(char *pszAction, int nMode)
{
  LONG right; // eax
  double v5; // st7
  int result; // eax
  int v7; // edx

  right = this->m_FrameA.m_rect.right;
  LOBYTE(this->m_FrameA.m_childs.capacity) = 0;
  this->m_nActionResult = 1;
  LODWORD(this->m_fRotAxisZ) = 2;
  if ( right != 4 )
    this->m_FrameA.m_rect.top = right;
  this->m_FrameA.m_childs.m_nSize = 0;
  this->m_FrameA.m_rect.right = 4;
  this->m_nMovement = nMode;
  this->m_fSavedRotX = 0.0;
  this->_embed_UIWnd_624.m_fontcolor.Color = 0;
  if ( nMode == -2 )
    ((Actor *)&this->m_partyActor.m_nActionType)->SetVisible((int)pszAction);
  else
    ((Actor *)&this->m_partyActor.m_nActionType)->SetMaterialName(pszAction);
  v5 = (double)((gbActor *)this->m_partyActor.m_nHP)->GetActionDuration(pszAction) * 0.0002083333333333333;
  *(float *)&this->m_FrameA.m_id = v5;
  if ( v5 > 10.0 )
    this->m_FrameA.m_id = (void *)1092616192;
  this->m_FrameA.m_rect.left = 0;
  ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(1.0);
  this->LoadWeaponModel(pszAction);
  result = _strcmpi(pszAction, "c07");
  if ( !result )
  {
    result = _strcmpi(&this->m_nAnimState, (const char *)&g_pfnUpdateFuncs[3]);
    if ( !result )
    {
      v7 = *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4];
      *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4] = 0;
      dword_C110D0 = v7;
    }
  }
  return result;
}

// 0x004150C0
void RoleSystem::UpdateActionState(float fVal)
{
  double v3; // st7
  LONG v4; // eax
  bool v5; // zf
  long double v6; // st7
  LONG right; // eax
  LONG v8; // eax
  double v9; // st7
  char *m_pLinkedSystem; // ecx
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st7
  LONG v15; // edx
  long double v16; // st7
  float v17; // ecx
  void *v18; // edx
  float v19; // eax
  int v20; // eax
  float v21; // eax
  void *v22; // ecx
  int v23; // edx
  int v24; // eax
  float v25; // ecx
  float m_fSavedRotX; // eax
  double m_fPosY; // st7
  float v28; // edx
  void *m_id; // eax
  int m_nMovement; // eax
  double v31; // st7
  PalScriptMgr *v32; // eax
  int v33; // ecx
  gbVisNode *m_nHP; // edi
  unsigned int v35; // eax
  LONG top; // eax
  unsigned int v37; // eax
  LONG v38; // eax
  double v39; // st7
  double v40; // st7
  float v41; // eax
  char *m_pData; // eax
  double v43; // st7
  LONG v44; // edx
  double v45; // st7
  double v46; // st7
  double v47; // st7
  int v48; // [esp+0x0] [ebp-0x28]
  int v49; // [esp+0xC] [ebp-0x1C]
  float v50; // [esp+0x10] [ebp-0x18]
  float v51; // [esp+0x10] [ebp-0x18]
  float v52; // [esp+0x10] [ebp-0x18]
  float v53; // [esp+0x10] [ebp-0x18]
  float v54; // [esp+0x10] [ebp-0x18]
  float v55; // [esp+0x10] [ebp-0x18]
  float v56; // [esp+0x14] [ebp-0x14]
  float v57; // [esp+0x14] [ebp-0x14]
  float v58; // [esp+0x14] [ebp-0x14]
  float v59; // [esp+0x14] [ebp-0x14]
  float v60; // [esp+0x14] [ebp-0x14]
  unsigned int v61; // [esp+0x14] [ebp-0x14]
  struct gbNodeMsgObj v62; // [esp+0x18] [ebp-0x10] BYREF
  float fVala; // [esp+0x2C] [ebp+0x4]

  switch ( LODWORD(this->m_fRotAxisZ) )
  {
    case 0:
      m_nMovement = this->m_nMovement;
      switch ( m_nMovement )
      {
        case 0:
          if ( ((Object3D *)&this->m_partyActor.m_nActionType)->CheckMessage(pszMsgName)
            || *(float *)&this->m_FrameA.m_rect.left > 0.5 )
          {
            ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(1.0);
            this->m_nMovement = 1;
          }
LABEL_69:
          *(float *)&this->m_FrameA.m_rect.left = fVal + *(float *)&this->m_FrameA.m_rect.left;
          return;
        case 1:
          if ( ((Object3D *)&this->m_partyActor.m_nActionType)->CheckMessage("hold") )
            ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(0.0);
          v53 = fVal * *(float *)&this->m_FrameA.m_benable;
          v59 = fVal * *(float *)&this->m_FrameA.m_bfocus;
          this->m_fPosX = fVal * *(float *)&this->m_FrameA.m_bvisible + this->m_fPosX;
          this->m_fPosY = v53 + this->m_fPosY;
          this->m_fPosZ = v59 + this->m_fPosZ;
          v31 = *(float *)&this->m_FrameA.m_benable - 490.0 * fVal;
          *(float *)&this->m_FrameA.m_benable = v31;
          if ( v31 < 0.0 )
            this->m_nMovement = 2;
          break;
        case 2:
          if ( ((Object3D *)&this->m_partyActor.m_nActionType)->CheckMessage("hold") )
            ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(0.0);
          v54 = fVal * *(float *)&this->m_FrameA.m_benable;
          v60 = fVal * *(float *)&this->m_FrameA.m_bfocus;
          this->m_fPosX = fVal * *(float *)&this->m_FrameA.m_bvisible + this->m_fPosX;
          this->m_fPosY = v54 + this->m_fPosY;
          this->m_fPosZ = v60 + this->m_fPosZ;
          *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable - 490.0 * fVal;
          if ( this->m_fPosY < (double)*(float *)&this->m_FrameA.m_fontcolor.Color )
          {
// [VFTABLE] LODWORD(this->m_fPosX) = this->m_FrameA.__vftable;
            LODWORD(this->m_fPosY) = this->m_FrameA.m_fontcolor.Color;
            LODWORD(this->m_fPosZ) = this->m_FrameA.m_wndcolor.Color;
            this->m_nMovement = 3;
            this->m_FrameA.m_rect.left = 0;
            ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(2.0);
          }
          break;
        default:
          if ( m_nMovement == 3 && ((Object3D *)&this->m_partyActor.m_nActionType)->GetVisNode() )
          {
            this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;

            this->m_fontcolor.Color = LODWORD(this->m_fPosX);
            this->m_wndcolor.Color = LODWORD(this->m_fPosY);
            this->m_id = (void *)LODWORD(this->m_fPosZ);
            this->m_wndcolor.Color = 0;
            *((_DWORD *)this + 2173) = this->m_fontcolor.Color;
            *((_DWORD *)this + 2174) = this->m_wndcolor.Color;
            *((_DWORD *)this + 2175) = this->m_id;
            v32 = (PalScriptMgr *)UISceneUpdate();
            ((PalScriptMgr *)v32)->CheckTileScript(this, fVal, 1);
          }
          goto LABEL_69;
      }
      this->m_fontcolor.Color = LODWORD(this->m_fPosX);
      this->m_wndcolor.Color = LODWORD(this->m_fPosY);
      this->m_id = (void *)LODWORD(this->m_fPosZ);
      this->m_wndcolor.Color = 0;
      *((_DWORD *)this + 2173) = this->m_fontcolor.Color;
      *((_DWORD *)this + 2174) = this->m_wndcolor.Color;
      *((_DWORD *)this + 2175) = this->m_id;
      this->SetMoveSpeed(1.0f, 0, v48);
      goto LABEL_69;
    case 2:
      v33 = this->m_nMovement;
      if ( v33 == -1 )
      {
        ((Object3D *)&this->m_partyActor.m_nActionType)->GetVisNode();
      }
      else if ( v33 == -2 )
      {
        m_nHP = (gbVisNode *)this->m_partyActor.m_nHP;
        if ( ((gbVisNode *)m_nHP)->PopMessage(v62) )
        {
          while ( v62.msgid != 1 )
          {
            if ( !((gbVisNode *)m_nHP)->PopMessage(v62) )
              return;
          }
          v35 = gbCrc32Compute("hold");
          if ( v62.param[0] == v35 )
          {
            ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(0.0);
            top = this->m_FrameA.m_rect.top;
            LOBYTE(this->m_FrameA.m_childs.capacity) = 1;
            this->m_FrameA.m_rect.right = top;
          }
          else
          {
            v37 = gbCrc32Compute("over");
            if ( v62.param[0] == v37 )
            {
              (*(void ( **)(int, int))(*(_DWORD *)this->m_partyActor.m_nHP + 24))(
                this->m_partyActor.m_nHP,
                -1082130432);
              ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(0.0);
              ((Actor *)&this->m_partyActor.m_nActionType)->QueryState();
              v38 = this->m_FrameA.m_rect.top;
              LOBYTE(this->m_FrameA.m_childs.capacity) = 0;
              this->m_FrameA.m_rect.right = v38;
            }
          }
        }
      }
      else
      {
        v39 = fVal + *(float *)&this->m_FrameA.m_rect.left;
        *(float *)&this->m_FrameA.m_rect.left = v39;
        if ( v39 >= *(float *)&this->m_FrameA.m_id )
        {
          v40 = v39 - *(float *)&this->m_FrameA.m_id;
          LODWORD(v41) = LODWORD(this->m_fSavedRotX) + 1;
          this->m_fSavedRotX = v41;
          *(float *)&this->m_FrameA.m_rect.left = v40;
          if ( SLODWORD(v41) >= v33 )
          {
            if ( !_strcmpi((const char *)&this->m_fRotAxisX, "c07")
              && !_strcmpi(&this->m_nAnimState, (const char *)&g_pfnUpdateFuncs[3]) )
            {
              *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4] = dword_C110D0;
            }
            m_pData = this->m_FrameA.m_childs.m_pData;
            this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;
            if ( m_pData )
              goto LABEL_91;
            this->m_FrameA.m_rect.bottom = 0;
            this->m_FrameA.m_bvisible = 0;
            this->m_FrameA.m_benable = 0;
            this->m_FrameA.m_bfocus = 0;
            this->m_FrameA.m_pbktex = 0;
            this->m_nActiveRole = this->m_FrameA.m_benable;
            this->m_nRoleCount = this->m_FrameA.m_bfocus;
          }
        }
      }
      return;
    case 3:
      v43 = fVal + *(float *)&this->m_FrameA.m_rect.left;
      *(float *)&this->m_FrameA.m_rect.left = v43;
      if ( v43 < *(float *)&this->m_FrameA.m_id )
      {
        *((float *)this + 2172) = (1.0 - v43 / *(float *)&this->m_FrameA.m_id)
                                * *(float *)&this->m_FrameA.m_fontcolor.Color
// [VFTABLE] + v43 / *(float *)&this->m_FrameA.m_id * *(float *)&this->m_FrameA.__vftable;
      }
      else
      {
        v44 = this->m_FrameA.m_rect.top;
// [VFTABLE] *((_DWORD *)this + 2172) = this->m_FrameA.__vftable;
        this->m_FrameA.m_rect.right = v44;

      }
      return;
    case 4:

      if ( this->m_FrameA.m_rect.bottom )
      {
        this->m_FrameA.m_bvisible = (int)this->m_FrameA.m_pbktex;
        this->m_FrameA.m_benable = this->m_nActiveRole;
        this->m_FrameA.m_bfocus = this->m_nRoleCount;
      }
      else
      {
        this->m_fontcolor.Color = (unsigned int)this->m_pLinkedSystem;
        this->m_wndcolor.Color = LODWORD(this->m_fAnimSpeed);
        this->m_id = (void *)LODWORD(this->m_fMoveRadius);
        this->m_wndcolor.Color = 0;
        this->SetMoveSpeed(0.0, 0, v48);
        this->m_FrameA.m_bvisible = this->m_rect.top;
        this->m_FrameA.m_benable = this->m_rect.right;
        this->m_FrameA.m_bfocus = this->m_rect.bottom;
        *(float *)&this->m_FrameA.m_bvisible = *(float *)&this->m_FrameA.m_bvisible * -1.0;
        *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable * -1.0;
        *(float *)&this->m_FrameA.m_bfocus = *(float *)&this->m_FrameA.m_bfocus * -1.0;


        this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;
      }
      return;
    case 5:
      *(float *)&v49 = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
      v45 = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
      v62.msgid = v49;
      v55 = v45;
      v46 = *(float *)&this->m_id - *(float *)&g_pRoleSystem->m_id;
      *(float *)v62.param = v55;
      *(float *)&v61 = v46;
      v62.param[1] = v61;
      v47 = ((gbVec3D *)&v62)->Length();
      if ( this->m_FrameA.m_rect.bottom && v47 >= 12.0 * 1.5 )
      {

        this->m_FrameA.m_bvisible = (int)this->m_FrameA.m_pbktex;
        this->m_FrameA.m_benable = this->m_nActiveRole;
        this->m_FrameA.m_bfocus = this->m_nRoleCount;
      }
      else
      {
        this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;

        *(_DWORD *)&this->m_partyActor.m_szTexture[4] = 0;
      }
      return;
    case 7:
      v20 = this->m_nMovement;
      if ( v20 )
      {
        if ( v20 == 1 )
        {
          v52 = *(float *)&this->m_FrameA.m_benable * fVal;
          v58 = *(float *)&this->m_FrameA.m_bfocus * fVal;
          this->m_fPosX = *(float *)&this->m_FrameA.m_bvisible * fVal + this->m_fPosX;
          this->m_fPosY = v52 + this->m_fPosY;
          this->m_fPosZ = v58 + this->m_fPosZ;
          m_fPosY = this->m_fPosY;
          if ( LODWORD(this->m_fSavedRotX) == 1 )
          {
            if ( m_fPosY <= *(float *)&this->m_FrameA.m_fontcolor.Color )
              return;
          }
          else if ( m_fPosY >= *(float *)&this->m_FrameA.m_fontcolor.Color )
          {
            return;
          }
          LODWORD(this->m_fPosY) = this->m_FrameA.m_fontcolor.Color;
          this->m_nMovement = 2;
          this->SetMoveTarget((float *)&this->m_FrameA, 1);
          return;
        }
        if ( v20 == 2 )
        {

          if ( !this->m_FrameA.m_rect.bottom )
          {
            if ( *(_DWORD *)(LODWORD(this->m_fMoveTargetZ) + 264) )
              *(_DWORD *)this->m_partyActor.m_szTexture = LODWORD(this->m_fSavedRotX) == 1;
// [VFTABLE] this->m_fontcolor.Color = (unsigned int)this->m_FrameA.__vftable;
            this->m_wndcolor.Color = this->m_FrameA.m_fontcolor.Color;
            this->m_id = (void *)this->m_FrameA.m_wndcolor.Color;
            this->m_wndcolor.Color = 0;
            *((_DWORD *)this + 2173) = this->m_fontcolor.Color;
            *((_DWORD *)this + 2174) = this->m_wndcolor.Color;
            *((_DWORD *)this + 2175) = this->m_id;
            this->SetMoveSpeed(0.0, 0, v48);
            this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;

            goto LABEL_28;
          }
          this->m_FrameA.m_bvisible = (int)this->m_FrameA.m_pbktex;
          this->m_FrameA.m_benable = this->m_nActiveRole;
          this->m_FrameA.m_bfocus = this->m_nRoleCount;

          *(float *)&this->m_FrameA.m_bvisible = fVal * *(float *)&this->m_FrameA.m_bvisible;
          *(float *)&this->m_FrameA.m_benable = fVal * *(float *)&this->m_FrameA.m_benable;
          *(float *)&this->m_FrameA.m_bfocus = fVal * *(float *)&this->m_FrameA.m_bfocus;
          *(float *)&this->m_fontcolor.Color = *(float *)&this->m_FrameA.m_bvisible + *(float *)&this->m_fontcolor.Color;
          *(float *)&this->m_wndcolor.Color = *(float *)&this->m_FrameA.m_benable + *(float *)&this->m_wndcolor.Color;
          *(float *)&this->m_id = *(float *)&this->m_FrameA.m_bfocus + *(float *)&this->m_id;
          v28 = *(float *)&this->m_fontcolor.Color;
          m_id = this->m_id;
          this->m_fPosX = v28;
          this->m_wndcolor.Color = 0;
          LODWORD(this->m_fPosZ) = m_id;
          *(float *)&this->m_nDispFontColor = v28;
          this->m_nField9C = (int)m_id;
        }
      }
      else
      {

        if ( !this->m_FrameA.m_rect.bottom )
        {
          this->UpdateMovement(*(float *)&this->m_FrameA.m_id, 1);
          m_fSavedRotX = this->m_fSavedRotX;
          this->m_nMovement = 1;
          this->m_FrameA.m_bvisible = 0;
          if ( LODWORD(m_fSavedRotX) == 1 )
          {
            this->m_FrameA.m_benable = 1065353216;
            this->m_FrameA.m_bfocus = 0;
            this->m_FrameA.m_childs.m_nSize = 5;
          }
          else
          {
            this->m_FrameA.m_benable = -1082130432;
            this->m_FrameA.m_bfocus = 0;
            this->m_FrameA.m_childs.m_nSize = 6;
          }
          this->UpdatePath(this->m_FrameA.m_childs.m_nSize);
          goto LABEL_25;
        }
        this->m_FrameA.m_bvisible = (int)this->m_FrameA.m_pbktex;
        this->m_FrameA.m_benable = this->m_nActiveRole;
        this->m_FrameA.m_bfocus = this->m_nRoleCount;

        *(float *)&this->m_FrameA.m_bvisible = fVal * *(float *)&this->m_FrameA.m_bvisible;
        *(float *)&this->m_FrameA.m_benable = fVal * *(float *)&this->m_FrameA.m_benable;
        *(float *)&this->m_FrameA.m_bfocus = fVal * *(float *)&this->m_FrameA.m_bfocus;
        *(float *)&this->m_fontcolor.Color = *(float *)&this->m_FrameA.m_bvisible + *(float *)&this->m_fontcolor.Color;
        *(float *)&this->m_wndcolor.Color = *(float *)&this->m_FrameA.m_benable + *(float *)&this->m_wndcolor.Color;
        *(float *)&this->m_id = *(float *)&this->m_FrameA.m_bfocus + *(float *)&this->m_id;
        v21 = *(float *)&this->m_fontcolor.Color;
        v22 = this->m_id;
        this->m_fPosX = v21;
        v23 = LODWORD(v21);
        LODWORD(this->m_fPosZ) = v22;
        v24 = (int)v22;
        v25 = this->m_fPosY;
        this->m_wndcolor.Color = 0;
        fVala = v25;
        this->m_nDispFontColor = v23;
        this->m_nField9C = v24;
        this->SetMoveSpeed(0.0, 0, v48);
        if ( fabs(fVala - this->m_fPosY) > 20.0 )
          this->m_fPosY = fVala;
      }
      return;
    case 8:
      if ( this->m_nMovement )
      {
        v51 = *(float *)&this->m_FrameA.m_benable * fVal;
        v57 = *(float *)&this->m_FrameA.m_bfocus * fVal;
        this->m_fPosX = *(float *)&this->m_FrameA.m_bvisible * fVal + this->m_fPosX;
        this->m_fPosY = v51 + this->m_fPosY;
        this->m_fPosZ = v57 + this->m_fPosZ;
        if ( fabs(this->m_fPosY - *(float *)&this->m_nDispWndColor) > *(float *)&this->m_FrameA.m_fontcolor.Color )
        {
          this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;
LABEL_28:
          ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(1.0);
        }
      }
      else
      {

        if ( this->m_FrameA.m_rect.bottom )
        {
          this->m_FrameA.m_bvisible = (int)this->m_FrameA.m_pbktex;
          this->m_FrameA.m_benable = this->m_nActiveRole;
          this->m_FrameA.m_bfocus = this->m_nRoleCount;

          *(float *)&this->m_FrameA.m_bvisible = fVal * *(float *)&this->m_FrameA.m_bvisible;
          *(float *)&this->m_FrameA.m_benable = fVal * *(float *)&this->m_FrameA.m_benable;
          *(float *)&this->m_FrameA.m_bfocus = fVal * *(float *)&this->m_FrameA.m_bfocus;
          *(float *)&this->m_fontcolor.Color = *(float *)&this->m_FrameA.m_bvisible + *(float *)&this->m_fontcolor.Color;
          *(float *)&this->m_wndcolor.Color = *(float *)&this->m_FrameA.m_benable + *(float *)&this->m_wndcolor.Color;
          *(float *)&this->m_id = *(float *)&this->m_FrameA.m_bfocus + *(float *)&this->m_id;
          v17 = *(float *)&this->m_fontcolor.Color;
          v18 = this->m_id;
          this->m_fPosX = v17;
          this->m_wndcolor.Color = 0;
          LODWORD(this->m_fPosZ) = v18;
          *(float *)&this->m_nDispFontColor = v17;
          this->m_nField9C = (int)v18;
        }
        else
        {
          this->UpdateMovement(*(float *)&this->m_FrameA.m_id, 1);
          v19 = this->m_fSavedRotX;
          this->m_nMovement = 1;
          if ( LODWORD(v19) == 1 )
          {
            this->m_FrameA.m_childs.m_nSize = 5;

            this->m_FrameA.m_bvisible = 0;
            this->m_FrameA.m_benable = 1065353216;
          }
          else
          {
            this->m_FrameA.m_childs.m_nSize = 6;

            this->m_FrameA.m_bvisible = 0;
            this->m_FrameA.m_benable = -1082130432;
          }
          this->m_FrameA.m_bfocus = 0;
LABEL_25:
          *(float *)&this->m_FrameA.m_bvisible = *(float *)&this->m_FrameA.m_bvisible * 40.0;
          *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable * 40.0;
          *(float *)&this->m_FrameA.m_bfocus = *(float *)&this->m_FrameA.m_bfocus * 40.0;
        }
      }
      return;
    case 9:
      v14 = fVal + *(float *)&this->m_FrameA.m_rect.left;
      *(float *)&this->m_FrameA.m_rect.left = v14;
      if ( v14 < *(float *)&this->m_FrameA.m_id )
      {
        v16 = (1.0 - cos(v14 / *(float *)&this->m_FrameA.m_id * 3.1415927)) * 0.5;
        *(float *)&this->m_partyActor.m_szTexture[12] = (1.0 - v16) * *(float *)&this->m_FrameA.m_fontcolor.Color
// [VFTABLE] + *(float *)&this->m_FrameA.__vftable * v16;
      }
      else
      {
        v15 = this->m_FrameA.m_rect.top;
// [VFTABLE] *(_DWORD *)&this->m_partyActor.m_szTexture[12] = this->m_FrameA.__vftable;
        this->m_FrameA.m_rect.right = v15;
      }
      return;
    case 0xA:
      v9 = fVal + *(float *)&this->m_FrameA.m_rect.left;
      *(float *)&this->m_FrameA.m_rect.left = v9;
      if ( v9 < *(float *)&this->m_FrameA.m_id )
      {
        v11 = v9 / *(float *)&this->m_FrameA.m_id;
        v12 = (*(float *)&this->m_pLinkedSystem - *(float *)&this->m_pRenderObj) * v11 + *(float *)&this->m_pRenderObj;
        v50 = (this->m_fAnimSpeed - *(float *)&this->m_bRenderFlag1) * v11 + *(float *)&this->m_bRenderFlag1;
        v13 = (this->m_fMoveRadius - *(float *)&this->m_bRenderFlag2) * v11 + *(float *)&this->m_bRenderFlag2;
        this->m_fPosY = v50;
        v56 = v13;
        this->m_fPosX = v12;
        this->m_fPosZ = v56;
        this->m_fontcolor.Color = LODWORD(this->m_fPosX);
        this->m_wndcolor.Color = LODWORD(this->m_fPosY);
        this->m_id = (void *)LODWORD(this->m_fPosZ);
        this->m_wndcolor.Color = 0;
        this->SetMoveSpeed(0.0, 0, v48);
      }
      else
      {
        m_pLinkedSystem = this->m_pLinkedSystem;
        LODWORD(this->m_fPosX) = m_pLinkedSystem;
        this->m_fPosY = this->m_fAnimSpeed;
        this->m_fPosZ = this->m_fMoveRadius;
        this->m_fontcolor.Color = (unsigned int)m_pLinkedSystem;
        this->m_wndcolor.Color = LODWORD(this->m_fPosY);
        this->m_id = (void *)LODWORD(this->m_fPosZ);
        this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;
        this->m_wndcolor.Color = 0;

        *(_DWORD *)&this->m_partyActor.m_szTexture[4] = 0;

      }
      return;
    case 0xB:
      v3 = fVal + *(float *)&this->m_FrameA.m_rect.left;
      *(float *)&this->m_FrameA.m_rect.left = v3;
      if ( v3 >= *(float *)&this->m_FrameA.m_id )
      {
        v4 = this->m_FrameA.m_rect.top;
        this->m_FrameA.m_rect.left = (LONG)this->m_FrameA.m_id;
        this->m_FrameA.m_rect.right = v4;
        *(_DWORD *)&this->m_partyActor.m_szTexture[12] = 1065353216;

      }
      v5 = this->m_nMovement == 1;
      v6 = (1.0 - cos(*(float *)&this->m_FrameA.m_rect.left / *(float *)&this->m_FrameA.m_id * 3.1415927)) * 0.5;
// [VFTABLE] this->m_fPosX = *(float *)&this->m_pRenderObj * (1.0 - v6) + *(float *)&this->m_FrameA.__vftable * v6;
      this->m_fPosY = *(float *)&this->m_bRenderFlag1 * (1.0 - v6) + *(float *)&this->m_FrameA.m_fontcolor.Color * v6;
      this->m_fPosZ = *(float *)&this->m_bRenderFlag2 * (1.0 - v6) + *(float *)&this->m_FrameA.m_wndcolor.Color * v6;
      if ( v5 )
      {
        right = this->m_FrameA.m_rect.right;
        *(float *)&this->m_pLinkedSystem = (float)(int)(__int64)(v6 * 90.0);
        if ( right == 4 )
          *(float *)&this->m_partyActor.m_szTexture[12] = 1.0 - v6 + v6 * 0.69999999;
      }
      else
      {
        v8 = this->m_FrameA.m_rect.right;
        *(float *)&this->m_pLinkedSystem = (float)(int)(__int64)((1.0 - v6) * 90.0);
        if ( v8 == 4 )
          *(float *)&this->m_partyActor.m_szTexture[12] = (1.0 - v6) * 0.69999999 + v6;
      }
      return;
    case 0x15:
      *(float *)&this->m_FrameA.m_rect.left = fVal + *(float *)&this->m_FrameA.m_rect.left;
      if ( ((Object3D *)&this->m_partyActor.m_nActionType)->GetVisNode()
        || *(float *)&this->m_FrameA.m_rect.left > 10.0 )
      {
        this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;
LABEL_91:

      }
      return;
    case 0x2C:
      *(float *)&this->m_FrameA.m_rect.left = fVal + *(float *)&this->m_FrameA.m_rect.left;
      if ( ((Object3D *)&this->m_partyActor.m_nActionType)->GetVisNode() )

      return;
    default:
      return;
  }
}

// 0x004161E0
void RoleSystem::ScaleVector(float fScale)
{
  double v2; // st7
  double v3; // st7

  v2 = ((gbVec3D *)pVec)->Length();
  if ( v2 > fScale )
  {
    v3 = fScale / v2;
    *pVec = v3 * *pVec;
    pVec[1] = v3 * pVec[1];
    pVec[2] = v3 * pVec[2];
  }
}

// 0x00416220
void RoleSystem::CheckMoveCollisionDist(int thisa, float *pfVal)
{
  double v5; // st7
  gbColorQuad *p_m_fontcolor; // edi
  double v7; // st6
  double v8; // st7
  double v9; // st6
  double v10; // st5
  void *m_id; // eax
  RoleSystem *v12; // eax
  float v13; // eax
  unsigned int v14; // ecx
  float v15; // edx
  int *v16; // [esp-0xC] [ebp-0x48]
  int v17; // [esp+0x0] [ebp-0x3C]
  float v18; // [esp+0xC] [ebp-0x30] BYREF
  float v19; // [esp+0x10] [ebp-0x2C]
  float v20; // [esp+0x14] [ebp-0x28]
  gbVec3D v21; // [esp+0x18] [ebp-0x24] BYREF
  float v22; // [esp+0x28] [ebp-0x14]
  float v23; // [esp+0x2C] [ebp-0x10]
  float v24; // [esp+0x34] [ebp-0x8]
  float v25; // [esp+0x38] [ebp-0x4]
  int thisb; // [esp+0x40] [ebp+0x4]
  float thisc; // [esp+0x40] [ebp+0x4]

  if ( !this->_embed_UIWnd_624.m_rect.right
    && !*(_DWORD *)(thisa + 1456)
    && *(_DWORD *)this->m_partyActor.m_szTexture == *(_DWORD *)(thisa + 628) )
  {
    v5 = *(float *)&this->m_fontcolor.Color - *(float *)(thisa + 4);
    p_m_fontcolor = &this->m_fontcolor;
    v19 = *(float *)&this->m_wndcolor.Color - *(float *)(thisa + 8);
    v7 = *(float *)&this->m_id - *(float *)(thisa + 12);
    v21.y = v19;
    v20 = v7;
    v21.x = v5;
    v21.z = v20;
    v8 = ((gbVec3D *)&v21)->Length();
    *(float *)&thisb = *(float *)(thisa + 16) + *(float *)&this->m_rect.left;
    if ( v8 <= *(float *)&thisb )
    {
      v9 = *(float *)&p_m_fontcolor->Color - *(float *)(thisa + 4);
      v22 = *(float *)&this->m_wndcolor.Color - *(float *)(thisa + 8);
      v10 = *(float *)&this->m_id - *(float *)(thisa + 12);
      v18 = *(float *)&p_m_fontcolor->Color;
      v23 = v10;
      v19 = *(float *)&this->m_wndcolor.Color;
      m_id = this->m_id;
      v16 = *(int **)this->m_partyActor.m_szTexture;
      thisc = (*(float *)&thisb * 1.1 - v8) / v8;
      v24 = v22 * thisc;
      v25 = v23 * thisc;
      v18 = v18 + v9 * thisc;
      v19 = v19 + v24;
      v20 = *(float *)&m_id + v25;
      v12 = (RoleSystem *)UISceneUpdate();
      if ( ((RoleSystem *)v12)->CheckMoveCollision(v16, &v18, 255) )
      {
        this->_embed_UIWnd_624.m_childs.m_pData = (char *)LODWORD(this->m_fPosX);
        v13 = v18;
        this->_embed_UIWnd_624.m_childs.capacity = LODWORD(this->m_fPosY);
        v14 = LODWORD(v19);
        this->_embed_UIWnd_624.m_childs.m_nSize = LODWORD(this->m_fPosZ);
        v15 = v20;
        this->m_wndcolor.Color = v14;
        *(float *)&p_m_fontcolor->Color = v13;
        *(float *)&this->m_id = v15;
        this->SetMoveSpeed(0.0, 0, v17);
      }
    }
  }
}

// 0x004163B0
int RoleSystem::CalcTileDistance(int nTileX, int nTileY)
{
  RoleSystem *v4; // eax
  int RolePtr; // eax
  int v6; // ecx
  int result; // eax
  int v8; // [esp-0x4] [ebp-0x24]
  _BYTE v9[12]; // [esp+0x8] [ebp-0x18]
  gbVec3D pTarget; // [esp+0x14] [ebp-0xC] BYREF

  v8 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v4 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v4)->GetRolePtr(v8);
  *(_DWORD *)&v9[4] = 0;
  if ( nTileX >= 0 )
  {
    v6 = *(_DWORD *)(RolePtr + 152);
    if ( nTileX < v6 && nTileY >= 0 && nTileY < *(_DWORD *)(RolePtr + 156) )
      *(float *)&v9[4] = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (nTileX + nTileY * v6));
  }
  *(float *)v9 = ((double)nTileX + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 128);
  *(float *)&v9[8] = ((double)nTileY + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 136);
  pTarget = *(gbVec3D *)v9;
  this->SetTargetRotation(&pTarget);
  result = (int)g_pRoleSystem;
  if ( this == g_pRoleSystem )
  {
    result = *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1);
    if ( result )
      return old_sbh_page_alloc((__old_sbh_page_struct *)g_pCameraCtrl);
  }
  return result;
}

// 0x004164E0
BOOL RoleSystem::IsPathMoving()
{
  return this->m_FrameA.m_rect.right == 4 && LODWORD(this->m_fRotAxisZ) == 10;
}

// 0x00416500
int RoleSystem::IsActionBlocked()
{
  int m_nTransformState; // ecx

  if ( LODWORD(this->m_partyActor.m_fMatrixC) )
  {
    if ( this->m_nCoreState == 4 )
    {
      if ( LODWORD(this->m_fPathTargetZ) != 2 || LODWORD(this->m_fPathAngle) != -1 )
        return 1;
    }
    else
    {
      m_nTransformState = this->m_nTransformState;
      if ( m_nTransformState && m_nTransformState != 12 && m_nTransformState != 3 )
        return 1;
    }
  }
  return 0;
}

// 0x00416550
void RoleSystem::IsPathComplete(float *pTargetPos, int nMode)
{
  float m_fPosZ; // eax
  float v5; // ecx
  float x; // eax
  int m_bfocus; // edx
  float z; // edx
  int v9; // ecx
  int v10; // edx
  gbVec3D v11; // [esp+0x4] [ebp-0x18] BYREF
  int m_fPosX_low; // [esp+0x10] [ebp-0xC]
  float m_fPosY; // [esp+0x14] [ebp-0x8]
  float v14; // [esp+0x18] [ebp-0x4]

  m_fPosX_low = SLODWORD(this->m_fPosX);
  m_fPosY = this->m_fPosY;
  m_fPosZ = this->m_fPosZ;
  v11.x = *pTargetPos;
  v14 = m_fPosZ;
  v11.y = 0.0;
  v5 = pTargetPos[2];
  v11.x = v11.x - *(float *)&m_fPosX_low;
  v11.z = v5 - m_fPosZ;
  if ( ((gbVec3D *)&v11)->Length() >= 0.0049999999 )
  {
    m_fPosX_low = this->m_FrameA.m_bvisible;
    x = v11.x;
    m_fPosY = *(float *)&this->m_FrameA.m_benable;
    m_bfocus = this->m_FrameA.m_bfocus;
    this->m_FrameA.m_benable = LODWORD(v11.y);
    v14 = *(float *)&m_bfocus;
    z = v11.z;
    *(float *)&this->m_FrameA.m_bvisible = x;
    *(float *)&this->m_FrameA.m_bfocus = z;

    v9 = LODWORD(m_fPosY);
    v10 = LODWORD(v14);
    this->m_FrameA.m_bvisible = m_fPosX_low;
    this->m_FrameA.m_benable = v9;
    this->m_FrameA.m_bfocus = v10;
  }
}

// 0x00416620
int RoleSystem::UpdateMovement(float fDeltaTime, int nMode)
{
  LONG right; // eax
  long double v5; // st7
  unsigned int v6; // edx
  long double v7; // st7
  double v8; // st7
  double v9; // st6
  double v10; // st5
  int v12; // [esp+0xC] [ebp-0x8]
  int v13; // [esp+0x10] [ebp-0x4]

  if ( nMode )
  {
    *((float *)this + 2172) = fDeltaTime;
  }
  else
  {
    right = this->m_FrameA.m_rect.right;
    LODWORD(this->m_fRotAxisZ) = 3;
    if ( right != 4 )
      this->m_FrameA.m_rect.top = right;
    v5 = fDeltaTime - *((float *)this + 2172);
    v6 = *((_DWORD *)this + 2172);
    this->m_FrameA.m_rect.right = 4;
// [VFTABLE] *(float *)&this->m_FrameA.__vftable = fDeltaTime;
    this->m_FrameA.m_fontcolor.Color = v6;
    this->m_FrameA.m_rect.left = 0;
    this->m_FrameA.m_childs.m_needscriptdel = 0;
    this->m_FrameA.m_bcreateok = 0;
    *(float *)&this->m_FrameA.m_id = fabs(v5) * 0.0083333338;
    this->m_FrameA.m_bvisible = 0;
    this->m_FrameA.m_benable = 0;
    this->m_FrameA.m_bfocus = 0;
    this->m_FrameA.m_pbktex = 0;
    this->m_nActiveRole = this->m_FrameA.m_benable;
    this->m_nRoleCount = this->m_FrameA.m_bfocus;
    this->UpdatePath(1);
  }
  v7 = fDeltaTime * 0.017453292;
  this->m_rect.right = 0;
  this->m_bcreateok = 0;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_needscriptdel = 1065353216;
  *(float *)&this->m_rect.top = sin(v7);
  *(float *)&this->m_rect.bottom = cos(v7);
  v8 = *(float *)&this->m_rect.right * *(float *)&this->m_bcreateok
     - *(float *)&this->m_rect.bottom * *(float *)&this->m_childs.m_needscriptdel;
  *(float *)&v12 = *(float *)&this->m_rect.bottom * *(float *)&this->m_childs.m_nSize
                 - *(float *)&this->m_rect.top * *(float *)&this->m_bcreateok;
  v9 = *(float *)&this->m_rect.top * *(float *)&this->m_childs.m_needscriptdel;
  v10 = *(float *)&this->m_rect.right * *(float *)&this->m_childs.m_nSize;
  this->m_childs.m_pData = (char *)v12;
  *(float *)&v13 = v9 - v10;
  *(float *)&this->m_pfather = v8;
  this->m_childs.capacity = v13;
  return v12;
}

// 0x00416790
void RoleSystem::UpdateAnimation(float *pfVal)
{
  void *m_id; // eax
  double v5; // st7
  float m_fCachePosX; // ecx
  double v7; // st7
  float v8; // eax
  float m_fCachePosY; // ecx
  PtrArray *SoundList; // eax
  double v11; // st7
  float v12; // edx
  int v13; // ecx
  RoleSystem *v14; // ebx
  int RolePtr; // edi
  bool v16; // cc
  float v17; // eax
  float v18; // ecx
  float v19; // eax
  double v20; // st7
  double v21; // st6
  int v22; // [esp-0x4] [ebp-0x38]
  gbVec3D v23; // [esp+0x10] [ebp-0x24] BYREF
  float v24; // [esp+0x1C] [ebp-0x18]
  float v25; // [esp+0x20] [ebp-0x14]
  float v26; // [esp+0x24] [ebp-0x10]
  float v27; // [esp+0x28] [ebp-0xC]
  int v28; // [esp+0x2C] [ebp-0x8]
  float v29; // [esp+0x30] [ebp-0x4]
  float pfVala; // [esp+0x38] [ebp+0x4]
  float pfValc; // [esp+0x38] [ebp+0x4]
  float *pfValb; // [esp+0x38] [ebp+0x4]
  float pfVald; // [esp+0x38] [ebp+0x4]

  if ( pfVal && *((_DWORD *)pfVal + 347) != 4 && *((_BYTE *)pfVal + 173) != 2 )
  {
    if ( this->m_nRetryCount && pfVal != (float *)LODWORD(this->m_fCachePosX) )

    this->m_nRetryCount = 1;
    LODWORD(this->m_fCachePosX) = pfVal;
    LODWORD(v23.x) = this->m_fontcolor.Color;
    m_id = this->m_id;
    LODWORD(v23.y) = this->m_wndcolor.Color;
    LODWORD(v23.z) = m_id;
    v23.x = v23.x - pfVal[1];
    v23.y = v23.y - pfVal[2];
    v23.z = *(float *)&m_id - pfVal[3];
    v5 = ((gbVec3D *)&v23)->Length();
    m_fCachePosX = this->m_fCachePosX;
    v7 = v5 - *(float *)(LODWORD(m_fCachePosX) + 16);
    if ( v7 >= 0.0 )
      pfVala = v7;
    else
      pfVala = 0.0;
    *(_DWORD *)(LODWORD(m_fCachePosX) + 1388) = 4;
    if ( *((_BYTE *)pfVal + 173) == 1 )
    {
      if ( pfVala >= (double)*(float *)&g_szSceneUIText[12] )
      {
        v11 = pfVal[5];
        v12 = pfVal[7];
        v25 = 0.0;
        v26 = v12;
        v27 = pfVal[5];
        v13 = *((_DWORD *)pfVal + 6);
        pfValc = g_fSceneTileSize + g_fSceneTileSize;
        v29 = v12;
        v28 = v13;
        v26 = v12 * pfValc;
        v24 = v11 * pfValc + pfVal[1];
        v25 = pfVal[2] + 0.0;
        v26 = v26 + pfVal[3];
        v27 = g_fSceneTileSize * v27;
        v29 = v12 * g_fSceneTileSize;
        v14 = (RoleSystem *)UISceneUpdate();
        RolePtr = ((RoleSystem *)v14)->GetRolePtr(*((_DWORD *)pfVal + 157));
        pfValb = 0;
        do
        {
          if ( ((RoleSystem *)v14)->CheckCollision(*(int **)this->m_partyActor.m_szTexture, (__int64)((v24 - *(float *)(RolePtr + 128)) / g_fSceneTileSize)) )
          {
            break;
          }
          v24 = v27 + v24;
          v16 = (int)pfValb + 1 < 10;
          pfValb = (float *)((char *)pfValb + 1);
          v26 = v29 + v26;
        }
        while ( v16 );
        v26 = v29 + v26;
        this->MoveToTileCheck((__int64)((v27 + v24 - *(float *)(RolePtr + 128)) / g_fSceneTileSize), (__int64)((v26 - *(float *)(RolePtr + 136)) / g_fSceneTileSize), 1);
      }
      else
      {
        ((PalScriptMgr *)LODWORD(this->m_fCachePosX))->Destroy();
        this->m_fCachePosY = v8;
        if ( v8 == 0.0 )
        {

        }
        else
        {
          this->IsPathComplete((float *)(LODWORD(this->m_fCachePosX) + 4), 1);

          m_fCachePosY = this->m_fCachePosY;
          this->m_nRetryCount = 2;
          v22 = LODWORD(m_fCachePosY);
          SoundList = ((CScreenMode *)LODWORD(m_fCachePosY))->GetSoundList();
          ((PtrArray *)SoundList)->SetResolution(0, v22);
        }
      }
    }
    else
    {
      v17 = this->m_fCachePosX;
      if ( !*(_DWORD *)(LODWORD(v17) + 500) )
      {
        v18 = *(float *)(LODWORD(v17) + 1268);
        if ( LODWORD(v18) != 3 )
        {
          this->m_fCachePosZ = v18;
          this->m_fMoveTargetY = *(_DWORD *)(LODWORD(v17) + 8688);
          this->m_fMoveTargetX = *(float *)(LODWORD(v17) + 1284);
          *(_DWORD *)(LODWORD(v17) + 1296) = this->m_fontcolor.Color;
          *(_DWORD *)(LODWORD(v17) + 1300) = this->m_wndcolor.Color;
          *(_DWORD *)(LODWORD(v17) + 1304) = this->m_id;
          v19 = this->m_fCachePosX;
          *(float *)(LODWORD(v19) + 1296) = *(float *)(LODWORD(v19) + 1296) - *(float *)(LODWORD(v19) + 4);
          *(float *)(LODWORD(v19) + 1300) = *(float *)(LODWORD(v19) + 1300) - *(float *)(LODWORD(v19) + 8);
          *(float *)(LODWORD(v19) + 1304) = *(float *)(LODWORD(v19) + 1304) - *(float *)(LODWORD(v19) + 12);
          ((RoleSystem *)LODWORD(this->m_fCachePosX))->UpdatePosition();
          ((RoleSystem *)LODWORD(this->m_fCachePosX))->Notify();
        }
      }
      if ( pfVala >= (double)*(float *)&g_szSceneUIText[12] )
      {
        v23.y = v23.y * -1.0;
        v23.z = v23.z * -1.0;
        v20 = v23.x * -1.0 / pfVala;
        v23.y = v23.y / pfVala;
        v23.z = v23.z / pfVala;
        v21 = *(float *)&g_szSceneUIText[12] - 10.0;
        pfVald = v21;
        v23.y = v23.y * pfVald;
        v23.z = v23.z * pfVald;
        v23.x = v20 * v21 + pfVal[1];
        v23.y = v23.y + pfVal[2];
        v23.z = v23.z + pfVal[3];
        this->BindPartyToScene(&v23.x, 1);
      }
      else
      {
        this->m_nRetryCount = 2;
      }
    }
  }
}

// 0x00416BC0
void RoleSystem::ProcessInteraction()
{
  float m_fCachePosX; // eax
  double v3; // st7
  float v4; // ecx
  double v5; // st7
  int m_nRetryCount; // eax
  int v7; // eax
  int v8; // eax
  PalScriptMgr *v9; // ecx
  float v10; // eax
  CScreenMode *v11; // ecx
  PtrArray *SoundList; // eax
  int v13; // eax
  float v14; // eax
  float v15; // eax
  CScreenMode *v16; // ecx
  PtrArray *v17; // eax
  float v18; // eax
  float v19; // eax
  float v20; // eax
  float v21; // esi
  int v22; // [esp-0x4] [ebp-0x24]
  int v23; // [esp-0x4] [ebp-0x24]
  _BYTE v24[12]; // [esp+0x8] [ebp-0x18]
  gbVec3D v25; // [esp+0x14] [ebp-0xC] BYREF

  m_fCachePosX = this->m_fCachePosX;
  if ( m_fCachePosX == 0.0 )
  {

    return;
  }
  *(float *)v24 = *(float *)(LODWORD(m_fCachePosX) + 4) - *(float *)&this->m_fontcolor.Color;
  *(float *)&v24[4] = *(float *)(LODWORD(m_fCachePosX) + 8) - *(float *)&this->m_wndcolor.Color;
  v25 = *(gbVec3D *)v24;
  v3 = ((gbVec3D *)&v25)->Length();
  v4 = this->m_fCachePosX;
  v5 = v3 - *(float *)(LODWORD(v4) + 16);
  if ( v5 < 0.0 )
    v5 = 0.0;
  m_nRetryCount = this->m_nRetryCount;
  if ( *(_BYTE *)(LODWORD(v4) + 173) == 1 )
  {
    v7 = m_nRetryCount - 1;
    if ( v7 )
    {
      if ( v7 == 1 )
      {
        ((PalScriptMgr *)LODWORD(this->m_fCachePosY))->ClearAllScript();
        if ( !v8 )
        {
          *(_DWORD *)(LODWORD(this->m_fCachePosX) + 1388) = 0;
LABEL_10:
          this->m_nRetryCount = 0;
          this->m_fCachePosX = 0.0;
          this->m_fCachePosY = 0.0;
        }
      }
    }
    else if ( !this->m_FrameA.m_rect.bottom || v5 < *(float *)&g_szSceneUIText[12] )
    {
      this->IsPathComplete((float *)(LODWORD(v4) + 4), 1);

      ((PalScriptMgr *)v9)->Destroy();
      this->m_fCachePosY = v10;
      v22 = LODWORD(v10);
      SoundList = ((CScreenMode *)v11)->GetSoundList();
      ((PtrArray *)SoundList)->SetResolution(0, v22);
      this->m_nRetryCount = 2;
    }
  }
  else if ( m_nRetryCount > 0 )
  {
    if ( m_nRetryCount <= 2 )
    {
      if ( v5 < *(float *)&g_szSceneUIText[12] )
      {
        ((PalScriptMgr *)*(PalScriptMgr **)(LODWORD(v4) + 264))->Destroy();
        this->m_fCachePosY = v15;
        if ( v15 == 0.0 )
        {

        }
        else
        {
          v23 = LODWORD(v15);
          v17 = ((CScreenMode *)v16)->GetSoundList();
          ((PtrArray *)v17)->SetResolution(0, v23);
          v18 = this->m_fCachePosX;
          this->m_nRetryCount = 3;
          LODWORD(v18) += 4;
          this->m_FrameA.m_bvisible = *(_DWORD *)LODWORD(v18);
          this->m_FrameA.m_benable = *(_DWORD *)(LODWORD(v18) + 4);
          this->m_FrameA.m_bfocus = *(_DWORD *)(LODWORD(v18) + 8);
          *(float *)&this->m_FrameA.m_bvisible = *(float *)&this->m_FrameA.m_bvisible
                                               - *(float *)&this->m_fontcolor.Color;
          *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable - *(float *)&this->m_wndcolor.Color;
          *(float *)&this->m_FrameA.m_bfocus = *(float *)&this->m_FrameA.m_bfocus - *(float *)&this->m_id;

          v19 = this->m_fCachePosX;
          if ( !*(_DWORD *)(LODWORD(v19) + 500) && *(_DWORD *)(LODWORD(v19) + 1268) != 3 )
          {
            *(_DWORD *)(LODWORD(v19) + 1296) = this->m_FrameA.m_bvisible;
            *(_DWORD *)(LODWORD(v19) + 1300) = this->m_FrameA.m_benable;
            *(_DWORD *)(LODWORD(v19) + 1304) = this->m_FrameA.m_bfocus;
          }

          v20 = this->m_fCachePosX;
          if ( !*(_DWORD *)(LODWORD(v20) + 500) && *(_DWORD *)(LODWORD(v20) + 1268) != 3 )
          {
            *(float *)(LODWORD(v20) + 1296) = *(float *)(LODWORD(v20) + 1296) * -1.0;
            *(float *)(LODWORD(v20) + 1300) = *(float *)(LODWORD(v20) + 1300) * -1.0;
            *(float *)(LODWORD(v20) + 1304) = *(float *)(LODWORD(v20) + 1304) * -1.0;
            ((RoleSystem *)LODWORD(this->m_fCachePosX))->UpdatePosition();
            v21 = this->m_fCachePosX;
            *(_DWORD *)(LODWORD(v21) + 1296) = 0;
            LODWORD(v21) += 1296;
            *(_DWORD *)(LODWORD(v21) + 4) = 0;
            *(_DWORD *)(LODWORD(v21) + 8) = 0;
          }
        }
      }
    }
    else if ( m_nRetryCount == 3 )
    {
      ((PalScriptMgr *)LODWORD(this->m_fCachePosY))->ClearAllScript();
      if ( !v13 )
      {
        v14 = this->m_fCachePosX;
        if ( !*(_DWORD *)(LODWORD(v14) + 500) && *(_DWORD *)(LODWORD(v14) + 1268) != 3 )
        {
          *(float *)(LODWORD(v14) + 1284) = this->m_fMoveTargetX;
          *(float *)(LODWORD(this->m_fCachePosX) + 1268) = this->m_fCachePosZ;
          ((RoleSystem *)LODWORD(this->m_fCachePosX))->UpdateMovement(*(float *)&this->m_fMoveTargetY, 1);
          ((RoleSystem *)LODWORD(this->m_fCachePosX))->UpdateTransform();
        }
        *(_DWORD *)(LODWORD(this->m_fCachePosX) + 1388) = 0;
        goto LABEL_10;
      }
    }
  }
}

// 0x00416F10
int RoleSystem::GetActiveRole()
{
  int result; // eax

  result = LODWORD(this->m_fCachePosX);
  this->m_nRetryCount = 0;
  if ( result )
  {
    if ( *(_BYTE *)(result + 173) != 1 && !*(_DWORD *)(result + 500) && *(_DWORD *)(result + 1268) != 3 )
    {
      *(float *)(result + 1284) = this->m_fMoveTargetX;
      *(float *)(LODWORD(this->m_fCachePosX) + 1268) = this->m_fCachePosZ;
      ((RoleSystem *)LODWORD(this->m_fCachePosX))->UpdateMovement(*(float *)&this->m_fMoveTargetY, 1);
      result = ((RoleSystem *)LODWORD(this->m_fCachePosX))->UpdateTransform();
    }
    *(_DWORD *)(LODWORD(this->m_fCachePosX) + 1388) = 0;
    this->m_fCachePosX = 0.0;
  }
  return result;
}

// 0x00416FA0
void RoleSystem::InitPathTracking(float *nFlags)
{
  LONG right; // eax

  right = this->m_FrameA.m_rect.right;
  LODWORD(this->m_fRotAxisZ) = 4;
  this->m_nMovement = 0;
  if ( right != 4 )
    this->m_FrameA.m_rect.top = right;
  this->m_FrameA.m_rect.right = 4;
  this->SetMoveTarget(nFlags, 1);
}

// 0x00416FE0
void RoleSystem::RestoreMoveMode(float *nFlags)
{
  LONG right; // eax

  if ( this->m_FrameA.m_rect.right == 4 )
  {
    this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;

  }
  right = this->m_FrameA.m_rect.right;
  LODWORD(this->m_fRotAxisZ) = 5;
  this->m_nMovement = 0;
  if ( right != 4 )
    this->m_FrameA.m_rect.top = right;
  this->m_FrameA.m_rect.right = 4;
  this->SetMoveTarget(nFlags, 1);
}

// 0x00417040
void RoleSystem::SetupMoveState(float *pfVal)
{
  char *p_m_nFacing; // eax
  int v5; // edi
  char *p_m_nAnimState; // esi
  _BYTE *v7; // esi
  gbVec3D *p_m_vecPosArray; // esi
  int *p_m_nMoveDst; // ecx
  int v10; // edx
  float *v11; // edx
  int *p_todo_170; // ecx
  int v13; // esi
  float *p_y; // eax
  int v15; // ecx
  float v16; // edx
  LONG v17; // ecx
  unsigned int v18; // eax
  int *v19; // edi
  _BYTE *v20; // esi
  char v21; // cl
  int v22; // eax
  int *p_m_bcreateok; // ecx
  float v24; // eax
  float m_fMoveParamY; // ecx
  int v26; // [esp+0x0] [ebp-0x20]
  int pfVala; // [esp+0x24] [ebp+0x4]

  p_m_nFacing = &this->m_nFacing;
  v5 = (char *)pfVal - &this->m_nFacing;
  this->m_nFacing = *(_BYTE *)pfVal;
  this->m_nActionState = *((_BYTE *)pfVal + 1);
  p_m_nAnimState = &this->m_nAnimState;
  do
  {
    *p_m_nAnimState = p_m_nAnimState[v5];
    ++p_m_nAnimState;
  }
  while ( (unsigned int)&p_m_nAnimState[-2 - (_DWORD)&this->m_nFacing] < 0x20 );
  v7 = (char *)&this->m_fTileHeight + 2;
  do
  {
    *v7 = v7[v5];
    ++v7;
  }
  while ( (unsigned int)&v7[-34 - (_DWORD)p_m_nFacing] < 0x20 );
  p_m_vecPosArray = &this->m_vecPosArray;
  this->m_nSpawnExtra = (int)pfVal[17];
  LOBYTE(this->m_nSpawnParam2) = *((_BYTE *)pfVal + 72);
  this->m_szModelPath = (int)pfVal[19];
  this->m_pWaypointWnd = (UIWnd *)pfVal[20];
  LOBYTE(this->m_nParamArray) = *((_BYTE *)pfVal + 84);
  *(float *)&this->m_bSpawnByteA = pfVal[22];
  this->m_nSpawnParam = (int)pfVal[23];
  this->m_nActionTimer = (int)pfVal[24];
  do
  {
    LOBYTE(p_m_vecPosArray->x) = *((_BYTE *)&p_m_vecPosArray->x + v5);
    p_m_vecPosArray = (gbVec3D *)((char *)p_m_vecPosArray + 1);
  }
  while ( (unsigned int)p_m_vecPosArray - 100 - (unsigned int)p_m_nFacing < 0x10 );
  p_m_nMoveDst = &this->m_nMoveDst;
  v10 = 3;
  do
  {
    *p_m_nMoveDst = *(int *)((char *)p_m_nMoveDst + v5);
    ++p_m_nMoveDst;
    --v10;
  }
  while ( v10 );
  LOBYTE(this->m_nVisState) = *((_BYTE *)pfVal + 128);
  BYTE1(this->m_nVisState) = *((_BYTE *)pfVal + 129);
  *(float *)&this->m_bVisFlag = pfVal[33];
  v11 = pfVal + 34;
  p_todo_170 = &this->_todo_170;
  pfVala = 16;
  do
  {
    v13 = *(_DWORD *)v11;
    v11 += 3;
    *(p_todo_170 - 1) = v13;
    *p_todo_170 = *(int *)((char *)p_todo_170 + (char *)(pfVal + 33) - &this->m_bVisFlag);
    p_todo_170[1] = *((_DWORD *)v11 - 1);
    p_todo_170 += 3;
    --pfVala;
  }
  while ( pfVala );
  this->m_partyActor.m_nAnimBuffer = (int)pfVal[82];
  this->m_partyActor.m_nParticleBuffer = (int)pfVal[83];
  this->m_partyActor.m_vecTargetPos.x = pfVal[84];
  p_y = &this->m_partyActor.m_vecTargetPos.y;
  v15 = 29;
  do
  {
    *p_y = *(float *)((char *)p_y + v5);
    ++p_y;
    --v15;
  }
  while ( v15 );
  ((Camera *)this)->InitFromScene((const char *)pfVal + 2);
  memset(&this->m_fRotAxisZ, 0, 0x24u);

  v16 = pfVal[20];
  this->m_fontcolor.Color = (unsigned int)pfVal[19];
  this->m_wndcolor.Color = 0;
  *(float *)&this->m_id = v16;
  *((_DWORD *)this + 2173) = this->m_fontcolor.Color;
  *((_DWORD *)this + 2174) = this->m_wndcolor.Color;
  *((_DWORD *)this + 2175) = this->m_id;
  *(_DWORD *)&this->m_partyActor.m_szTexture[4] = *((unsigned __int8 *)pfVal + 84);
  this->UpdateMovement(pfVal[17], 1);
  if ( *((_BYTE *)pfVal + 1) == 2 )
  {
    this->m_fMoveRole = 0.0;
    ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)pfVal + 29));
    this->m_fMoveParamY = v24;

    m_fMoveParamY = this->m_fMoveParamY;
    switch ( *(_BYTE *)(LODWORD(m_fMoveParamY) + 753) )
    {
      case 0:
      case 1:
        LODWORD(this->m_fMoveParamZ) = dword_58B260;
        break;
      case 2:
        LODWORD(this->m_fMoveParamZ) = dword_58B274;
        break;
      case 3:
        LODWORD(this->m_fMoveParamZ) = dword_58B288;
        break;
      default:
        this->m_fMoveParamZ = 0.0;
        break;
    }
    if ( *(_BYTE *)(LODWORD(m_fMoveParamY) + 753) )

    this->m_FrameA.m_rect.right = 5;
  }
  else
  {
    this->m_FrameA.m_rect.right = 1;
    switch ( *((_DWORD *)pfVal + 22) )
    {
      case 0:
        this->m_FrameA.m_rect.bottom = *(_DWORD *)&this->m_bSpawnByteA;
        break;
      case 1:

        this->m_FrameA.m_rect.bottom = *(_DWORD *)&this->m_bSpawnByteA;
        break;
      case 2:
        v18 = *(_DWORD *)&this->m_bVisFlag;
        *((_DWORD *)this + 1138) = v18;
        v18 *= 12;
        qmemcpy(&this->_embed_UIWnd_624.m_childs.m_needscriptdel, &this->m_pWndFrame, 4 * (v18 >> 2));
        v20 = &this->_gap_169[4 * (v18 >> 2) + 3];
        v19 = &this->_embed_UIWnd_624.m_childs.m_needscriptdel + (v18 >> 2);
        v21 = v18;
        v22 = 0;
        qmemcpy(v19, v20, v21 & 3);
        if ( *((int *)this + 1138) > 0 )
        {
          p_m_bcreateok = &this->_embed_UIWnd_624.m_bcreateok;
          do
          {
            *p_m_bcreateok = 0;
            ++v22;
            p_m_bcreateok += 3;
          }
          while ( v22 < *((_DWORD *)this + 1138) );
        }
        ((PathObj *)&this->_embed_UIWnd_624.m_childs.m_needscriptdel)->CalcLength();
        this->m_FrameA.m_rect.bottom = 9;
        this->_embed_UIWnd_624.m_fontcolor.Color = 0;
        break;
      case 3:
        ((Actor *)&this->m_partyActor.m_nActionType)->SetMaterialName(&this->m_vecPosArray);
        if ( !*((_DWORD *)pfVal + 83) )
        {
          (*(void ( **)(int, int))(*(_DWORD *)this->m_partyActor.m_nHP + 24))(
            this->m_partyActor.m_nHP,
            -1082130432);
          ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(0.0);
        }
        LODWORD(this->m_fPosX) = this->m_fontcolor.Color;
        LODWORD(this->m_fPosY) = this->m_wndcolor.Color;
        LODWORD(this->m_fPosZ) = this->m_id;
        v17 = *(_DWORD *)&this->m_bSpawnByteA;
        this->m_fPosY = pfVal[24];
        this->m_FrameA.m_rect.bottom = v17;
        break;
      default:
        break;
    }
  }
  this->m_FrameA.m_rect.top = this->m_FrameA.m_rect.right;
  *(float *)&this->_todo_61C = flt_58B364 * this->m_fMoveParamZ;
// [VFTABLE] this->_embed_UIWnd_624.__vftable = (vtbl_0056AE2C *)dword_58B314;
  if ( *((_DWORD *)pfVal + 22) != 3 )
    this->SetMoveSpeed(0.0, 0, v26);
}

// 0x00417420
void RoleSystem::UpdateTransform(float arg0)
{
  CScreenMode *bottom; // ecx
  float v4; // ecx
  float v5; // edx
  double v6; // st7
  float v7; // edx
  float v8; // eax
  int m_needscriptdel; // ecx
  double v10; // st7
  double v11; // st7
  RoleSystem *v12; // ebx
  CScreenMode *SoundList; // eax
  double v14; // st7
  double v15; // st6
  double v16; // st7
  int v17; // eax
  BOOL v18; // eax
  BOOL v19; // ebx
  BOOL v20; // eax
  float *p_Color; // [esp-0x4] [ebp-0x38]
  gbVec3D v22; // [esp+0x10] [ebp-0x24] BYREF
  gbVec3D pfVal; // [esp+0x1C] [ebp-0x18] BYREF
  int m_szModelPath; // [esp+0x28] [ebp-0xC] BYREF
  float v25; // [esp+0x2C] [ebp-0x8]
  float v26; // [esp+0x30] [ebp-0x4]
  float arg0a; // [esp+0x38] [ebp+0x4]
  float arg0b; // [esp+0x38] [ebp+0x4]

  if ( this->m_nActionResult )
  {

    switch ( LODWORD(this->m_fMoveRole) )
    {
      case 0:
        if ( this->CheckVisibility() )
          goto LABEL_16;

        if ( g_nCameraUpdateCount > 0 )
          goto LABEL_20;


        LODWORD(this->m_fMoveRole) = 3;
        goto LABEL_19;
      case 1:
        if ( LOBYTE(Buffer.m_partyActor.m_vecPos.x) )
        {
          v4 = *(float *)&this->m_fontcolor.Color;
          v5 = *(float *)&this->m_wndcolor.Color;
          LODWORD(v22.z) = this->m_id;
          v22.x = v4;
          v22.y = v5;
          v22.x = v4 - *(float *)&g_pRoleSystem->m_fontcolor.Color;
          v22.y = v5 - *(float *)&g_pRoleSystem->m_wndcolor.Color;
          v22.z = v22.z - *(float *)&g_pRoleSystem->m_id;
// [VFTABLE] if ( *(float *)&this->_embed_UIWnd_624.__vftable * 1.4 >= ((gbVec3D *)&v22)->Length() )
            goto LABEL_11;
        }
        else
        {
          this->MoveRole((float *)&g_pRoleSystem->m_fontcolor.Color, *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture, 1, 0);
          v6 = *(float *)&this->m_fontcolor.Color - *(float *)&this->m_szModelPath;
          v7 = *(float *)&this->m_wndcolor.Color;
          LODWORD(v22.z) = this->m_id;
          v22.y = v7;
          v22.x = v6;
          v22.z = v22.z - *(float *)&this->m_pWaypointWnd;
          if ( ((gbVec3D *)&v22)->Length() <= (double)*(float *)&this->_todo_61C )
            goto LABEL_11;
        }
        pfVal.x = *(float *)&this->m_szModelPath;
        pfVal.z = *(float *)&this->m_pWaypointWnd;
        LODWORD(this->m_fMoveRole) = 2;
        this->_embed_UIWnd_624.m_rect.bottom = 0;
        pfVal.y = 0.0;
        this->BindPartyToScene(&pfVal.x, 1);
        goto LABEL_11;
      case 2:
        if ( this->m_FrameA.m_rect.bottom )
        {
          if ( this->CheckVisibility() )
          {
LABEL_16:
            LODWORD(this->m_fMoveRole) = 1;

            goto LABEL_19;
          }
        }
        else
        {
          this->m_fMoveRole = 0.0;

          this->_todo_5AC = this->m_rect.top;
          this->m_pCtrlPoint = (char *)this->m_rect.right;
          bottom = (CScreenMode *)this->m_rect.bottom;
          this->m_nMoveRole = (int)bottom;
        }
LABEL_11:
        if ( g_nCameraUpdateCount > 0 )
          goto LABEL_20;


        LODWORD(this->m_fMoveRole) = 3;
LABEL_19:
        if ( g_nCameraUpdateCount <= 0 )
          return;
LABEL_20:
        if ( this->m_FrameA.m_rect.bottom )
        {
          LODWORD(v22.x) = this->m_nAnimation;
          v8 = *(float *)&this->m_nAnimCopy2;
          LODWORD(v22.y) = this->m_nAnimCopy1;
          v22.y = v22.y * arg0;
          v22.z = v8 * arg0;
          *(float *)&this->m_FrameA.m_bvisible = v22.x * arg0 + *(float *)&this->m_FrameA.m_bvisible;
          *(float *)&this->m_FrameA.m_benable = v22.y + *(float *)&this->m_FrameA.m_benable;
          *(float *)&this->m_FrameA.m_bfocus = v22.z + *(float *)&this->m_FrameA.m_bfocus;
          m_needscriptdel = this->m_FrameA.m_childs.m_needscriptdel;
          this->m_FrameA.m_benable = 0;
          arg0a = *(float *)&m_needscriptdel;
          v10 = ((gbVec3D *)&this->m_FrameA.m_bvisible)->Length();
          if ( v10 > arg0a )
          {
            v11 = arg0a / v10;
            *(float *)&this->m_FrameA.m_bvisible = v11 * *(float *)&this->m_FrameA.m_bvisible;
            *(float *)&this->m_FrameA.m_benable = v11 * *(float *)&this->m_FrameA.m_benable;
            *(float *)&this->m_FrameA.m_bfocus = v11 * *(float *)&this->m_FrameA.m_bfocus;
          }
        }
        v12 = g_pRoleSystem;
        if ( !g_pRoleSystem )
          return;
        if ( g_pRoleSystem->m_FrameA.m_rect.right == 4 )
          return;
        if ( g_nSceneState != 2 )
          return;
        SoundList = (CScreenMode *)((CScreenMode *)bottom)->GetSoundList();
        if ( !((CScreenMode *)SoundList)->IsAudioReady() )
          return;
        if ( 12.0 + 12.0 <= fabs(this->m_fPosY - v12->m_fPosY) )
          return;
        v14 = *(float *)&this->m_fontcolor.Color - *(float *)&v12->m_fontcolor.Color;
        v25 = *(float *)&this->m_wndcolor.Color - *(float *)&v12->m_wndcolor.Color;
        v15 = *(float *)&this->m_id - *(float *)&v12->m_id;
        pfVal.y = v25;
        v26 = v15;
        pfVal.x = v14;
        pfVal.z = v26;
        v16 = ((gbVec3D *)&pfVal)->Length();
        if ( v16 >= *(float *)&v12->m_rect.left + *(float *)&this->m_rect.left )
          return;
        ((RoleSystem *)v12)->Notify();
        arg0b = v16;
        if ( arg0b < 12.0 )
        {
          v17 = 0;
          goto LABEL_37;
        }
        v18 = ((RoleSystem *)v12)->InterpolateHeight((float *)&this->m_fontcolor.Color);
        p_Color = (float *)&v12->m_fontcolor.Color;
        v19 = v18;
        v20 = this->InterpolateHeight(p_Color);
        if ( v19 )
        {
          if ( !v20 )
          {
            v17 = 1;
            goto LABEL_37;
          }
          goto LABEL_35;
        }
        if ( !v20 )
        {
LABEL_35:
          v17 = 0;
          goto LABEL_37;
        }
        v17 = 2;
LABEL_37:
        LOBYTE(((PalScript *)&stru_C11720)->_todo_028) = 0;
        LOBYTE(((PalScript *)&stru_C11720)->_todo_48) = 0;
        dword_C1171C = 0x7FFFFFFF;
        g_nKeyMap3 = 1;
        ((PAL3 *)&this->m_nFacing)->StartCombatFromNPC(v17, (Role *)this);
        break;
      case 3:
        if ( g_nCameraUpdateCount <= 0 )
          return;
        m_szModelPath = this->m_szModelPath;
        v26 = *(float *)&this->m_pWaypointWnd;
        LODWORD(this->m_fMoveRole) = 2;
        this->_embed_UIWnd_624.m_rect.bottom = 0;
        v25 = 0.0;
        this->BindPartyToScene((float *)&m_szModelPath, 1);
        goto LABEL_19;
      default:
        goto LABEL_19;
    }
  }
}

// 0x00417850
int RoleSystem::EnterSubMode6()
{
  if ( LOBYTE(Buffer.m_partyActor.m_vecPos.x) )
  {
    this->m_FrameA.m_rect.bottom = 6;
    this->m_FrameA.m_childs.m_nSize = 1;
    return this->UpdateTransform();
  }
  else
  {
    this->MoveRole((float *)&g_pRoleSystem->m_fontcolor.Color, *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture, 1, 1);
    return this->UpdateTransform();
  }
}

// 0x004178A0
BOOL RoleSystem::CheckVisibility()
{
  float *v2; // ebx
  double v3; // st7
  double v4; // st6
  double v5; // st7
  RoleSystem *v7; // eax
  int RolePtr; // edi
  RoleSystem *v9; // eax
  int *v10; // [esp-0x1C] [ebp-0x44]
  char *v11; // [esp-0x18] [ebp-0x40]
  int v12; // [esp-0x14] [ebp-0x3C]
  char *v13; // [esp-0x10] [ebp-0x38]
  int v14; // [esp-0xC] [ebp-0x34]
  int v15; // [esp-0xC] [ebp-0x34]
  float pszBuf; // [esp+0x8] [ebp-0x20]
  UIWnd *m_pWaypointWnd; // [esp+0x18] [ebp-0x10]
  gbVec3D v18; // [esp+0x1C] [ebp-0xC] BYREF

  if ( HIBYTE(Buffer.m_partyActor.m_nHandleEvent) )
    return 0;
  v2 = (float *)g_pRoleSystem;
  if ( !g_pRoleSystem )
    return 0;
  if ( *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture != *(_DWORD *)this->m_partyActor.m_szTexture )
    return 0;
  memset(&v18, 0, sizeof(v18));
  LODWORD(v18.x) = g_pRoleSystem->m_fontcolor.Color;
  v3 = *(float *)&g_pRoleSystem->m_wndcolor.Color;
  v18.y = *(float *)&g_pRoleSystem->m_wndcolor.Color;
  v4 = *(float *)&g_pRoleSystem->m_id;
  m_pWaypointWnd = this->m_pWaypointWnd;
  v18.x = v18.x - *(float *)&this->m_szModelPath;
  v18.y = v3;
  v18.z = v4 - *(float *)&m_pWaypointWnd;
  if ( *(float *)&this->_todo_61C * 0.80000001 < ((gbVec3D *)&v18)->Length() )
    return 0;
  v18.x = v2[1];
  v18.y = v2[2];
  v5 = v2[3];
  v18.x = v18.x - *(float *)&this->m_fontcolor.Color;
  v18.y = v18.y - *(float *)&this->m_wndcolor.Color;
  v18.z = v5 - *(float *)&this->m_id;
  pszBuf = ((gbVec3D *)&v18)->Length();
  if ( 12.0 * 10.0 > pszBuf )
    return 1;
// [VFTABLE] if ( pszBuf >= (double)*(float *)&this->_embed_UIWnd_624.__vftable )
    return 0;
  v18.x = v18.x / pszBuf;
  v18.y = v18.y / pszBuf;
  v18.z = v18.z / pszBuf;
  if ( v18.y * *(float *)&this->m_rect.right
     + v18.z * *(float *)&this->m_rect.bottom
     + v18.x * *(float *)&this->m_rect.top <= 0.69999999 )
    return 0;
  v14 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v7 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v7)->GetRolePtr(v14);
  v15 = (__int64)((v2[3] - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  v13 = (char *)(__int64)((v2[1] - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v12 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  v11 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v10 = *(int **)this->m_partyActor.m_szTexture;
  v9 = (RoleSystem *)UISceneUpdate();
  return ((RoleSystem *)v9)->AdvanceOnPath(v10, v11, v12, v13, v15) != 0;
}

// 0x00417AC0
void RoleSystem::SetState(int state)
{
  RoleSystem *v4; // eax
  int v5; // eax
  int v6; // edi
  int v7; // esi
  RoleSystem *v8; // eax
  int *v9; // [esp-0x10] [ebp-0x28]
  int v10; // [esp-0x4] [ebp-0x1C]
  int v11; // [esp+0x10] [ebp-0x8]
  int v12; // [esp+0x14] [ebp-0x4]
  int statea; // [esp+0x1C] [ebp+0x4]

  if ( *(_BYTE *)(state + 244) == 14 )
  {
    v10 = *(_DWORD *)this->m_partyActor.m_szTexture;
    v4 = (RoleSystem *)UISceneUpdate();
    ((RoleSystem *)v4)->GetRolePtr(v10);
    v5 = *(_DWORD *)(state + 236) - *(_DWORD *)(state + 228);
    v12 = v5;
    v11 = *(_DWORD *)(state + 240) - *(_DWORD *)(state + 232);
    if ( v11 >= 0 )
    {
      while ( 1 )
      {
        statea = v5;
        if ( v5 >= 0 )
          break;
LABEL_7:
        if ( --v11 < 0 )
          return;
      }
      while ( 1 )
      {
        v6 = v11 + *(_DWORD *)(state + 232);
        v7 = *(_DWORD *)(state + 228) + statea;
        v9 = *(int **)this->m_partyActor.m_szTexture;
        v8 = (RoleSystem *)UISceneUpdate();
        if ( ((RoleSystem *)v8)->CheckCollision(v9, v7) )
          break;
        if ( --statea < 0 )
        {
          v5 = v12;
          goto LABEL_7;
        }
      }
      this->MoveToTileCheck(v7, v6, 1);
    }
  }
  else if ( this->m_FrameA.m_rect.right != 4 )
  {
    ((PalScriptMgr *)state)->ExecuteBlock();
  }
}

// 0x00417BC0
void RoleSystem::StopAndResetPath()
{
  LONG right; // eax

  if ( LOBYTE(this->m_FrameA.m_childs.capacity) )
  {
    right = this->m_FrameA.m_rect.right;
    this->m_FrameA.m_rect.left = 0;
    if ( right != 4 )
      this->m_FrameA.m_rect.top = right;
    this->m_FrameA.m_rect.right = 4;
    LODWORD(this->m_fRotAxisZ) = 21;
    ((Actor *)&this->m_partyActor.m_nActionType)->SetVisible(0);
    ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(1.0);
    LOBYTE(this->m_FrameA.m_childs.capacity) = 0;
  }
  else
  {
    this->m_FrameA.m_rect.right = this->m_FrameA.m_rect.top;

    LOBYTE(this->m_FrameA.m_childs.capacity) = 0;
  }
}

// 0x00417C50
double RoleSystem::UpdateMoveSubMode(double result, float result_4)
{
  double v4; // st7
  bool v5; // zf
  signed int v6; // eax
  void *v7; // ecx
  bool v8; // zf
  signed int v9; // eax
  double v10; // st7
  float v11; // ecx
  void *m_id; // eax
  LONG bottom; // eax
  double v14; // st7
  double v15; // st7
  double v16; // [esp-0x4] [ebp-0x34]
  int v17; // [esp+0x0] [ebp-0x30]
  int v18; // [esp+0x0] [ebp-0x30]
  float v19; // [esp+0x4] [ebp-0x2C]
  float v20; // [esp+0x4] [ebp-0x2C]
  float v21; // [esp+0x4] [ebp-0x2C]
  char v22; // [esp+0x8] [ebp-0x28]
  gbVec3D v23; // [esp+0xC] [ebp-0x24] BYREF
  float pTargetPos[4]; // [esp+0x18] [ebp-0x18] BYREF
  UIWnd *m_pWaypointWnd; // [esp+0x28] [ebp-0x8]

  if ( this->m_nRetryCount == 4 )
  {
LABEL_39:
    bottom = this->m_FrameA.m_rect.bottom;
    if ( bottom && bottom != 3 )
    {

      if ( this->m_FrameA.m_rect.bottom == 1 )

      if ( this->m_FrameA.m_rect.bottom != 8 )
      {
        v23 = *(gbVec3D *)&this->m_nAnimation;
        v23.x = v23.x * *(float *)&result;
        v23.y = v23.y * *(float *)&result;
        v14 = *(float *)&result * v23.z;
        *(float *)&this->m_FrameA.m_bvisible = v23.x + *(float *)&this->m_FrameA.m_bvisible;
        *(float *)&this->m_FrameA.m_benable = v23.y + *(float *)&this->m_FrameA.m_benable;
        *(float *)&this->m_FrameA.m_bfocus = v14 + *(float *)&this->m_FrameA.m_bfocus;
        this->m_FrameA.m_benable = 0;
        ((gbVec3D *)&this->m_FrameA.m_bvisible)->Normalize();
        v15 = *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
        *(float *)&this->m_FrameA.m_bvisible = v15 * *(float *)&this->m_FrameA.m_bvisible;
        *(float *)&this->m_FrameA.m_benable = v15 * *(float *)&this->m_FrameA.m_benable;
        v4 = v15 * *(float *)&this->m_FrameA.m_bfocus;
        *(float *)&this->m_FrameA.m_bfocus = v4;
      }
    }
    return v4;
  }
  if ( this->m_nActionState != 3 || *(_DWORD *)&this->m_bSpawnByteA )
  {
    if ( *(_DWORD *)&this->m_bSpawnByteA == 1 )
    {
      v4 = *(float *)&result + *(float *)&this->_embed_UIWnd_624.m_fontcolor.Color;
      *(float *)&this->_embed_UIWnd_624.m_fontcolor.Color = v4;
      if ( v4 > 8.0 )
      {
        if ( this->m_FrameA.m_rect.bottom )
        {

        }
        else
        {
          v9 = rand() & 0x80000001;
          v8 = v9 == 0;
          if ( v9 < 0 )
            v8 = (((_BYTE)v9 - 1) | 0xFFFFFFFE) == -1;
          if ( v8 )
          {
            v10 = *(float *)&this->m_szModelPath;
            v11 = *(float *)&this->m_fontcolor.Color;
            m_pWaypointWnd = this->m_pWaypointWnd;
            v23.x = v11;
            m_id = this->m_id;
            LODWORD(v23.y) = this->m_wndcolor.Color;
            LODWORD(v23.z) = m_id;
            v23.x = v11 - v10;
            v23.y = v23.y - *(float *)&m_pWaypointWnd;
            v4 = ((gbVec3D *)&v23)->Length();
            if ( v4 >= 100.0 )
            {
              pTargetPos[0] = *(float *)&this->m_szModelPath;
              v4 = *(float *)&this->m_pWaypointWnd;
              pTargetPos[1] = *(float *)&this->m_pWaypointWnd;
              pTargetPos[2] = 0.0;
              this->SetMoveTarget(pTargetPos, 1);
            }
            else
            {

            }
          }
        }
        this->_embed_UIWnd_624.m_fontcolor.Color = 0;
      }
    }
    else if ( *(_DWORD *)&this->m_bSpawnByteA == 2 )
    {
      switch ( this->m_nMovement )
      {
        case 0:
          v4 = *(float *)&result + *(float *)&this->_embed_UIWnd_624.m_fontcolor.Color;
          *(float *)&this->_embed_UIWnd_624.m_fontcolor.Color = v4;
          if ( v4 > 4.0 )
          {
            this->m_FrameA.m_childs.m_nSize = 1;

            this->m_nMovement = 1;
// [VFTABLE] this->m_FrameA.__vftable = 0;
          }
          break;
        case 1:
          LODWORD(v16) = 1065353216;
          if ( this->StepAlongPath(v16, v19) )
          {
            this->m_FrameA.m_childs.m_nSize = 0;

            this->_embed_UIWnd_624.m_fontcolor.Color = 0;
            this->m_nMovement = 2;
          }
          else
          {
            this->m_FrameA.m_bvisible = (int)this->m_FrameA.m_pbktex;
            this->m_FrameA.m_benable = this->m_nActiveRole;
            this->m_FrameA.m_bfocus = this->m_nRoleCount;
            this->ApplyMoveStep(COERCE_DOUBLE((unsigned __int64)LODWORD(result)), v17, v20, v22);
          }
          break;
        case 2:
          v4 = *(float *)&result + *(float *)&this->_embed_UIWnd_624.m_fontcolor.Color;
          *(float *)&this->_embed_UIWnd_624.m_fontcolor.Color = v4;
          if ( v4 > 4.0 )
          {
            this->m_FrameA.m_childs.m_nSize = 1;

            v7 = (void *)*((_DWORD *)this + 1139);
            this->m_nMovement = 3;
// [VFTABLE] this->m_FrameA.__vftable = v7;
          }
          break;
        case 3:
          LODWORD(v16) = -1082130432;
          if ( this->StepAlongPath(v16, v19) )
          {
            this->m_FrameA.m_childs.m_nSize = 0;

            this->_embed_UIWnd_624.m_fontcolor.Color = 0;
            this->m_nMovement = 0;
          }
          else
          {
            this->m_FrameA.m_bvisible = (int)this->m_FrameA.m_pbktex;
            this->m_FrameA.m_benable = this->m_nActiveRole;
            this->m_FrameA.m_bfocus = this->m_nRoleCount;
            this->ApplyMoveStep(COERCE_DOUBLE((unsigned __int64)LODWORD(result)), v18, v21, v22);
          }
          break;
        default:
          return v4;
      }
      return v4;
    }
    goto LABEL_39;
  }
  if ( this->m_FrameA.m_childs.m_nSize == 51 )
  {
    if ( ((Object3D *)&this->m_partyActor.m_nActionType)->GetVisNode() )
    {
      this->m_FrameA.m_childs.m_nSize = 0;

    }
  }
  else
  {
    v4 = *(float *)&result + *(float *)&this->_embed_UIWnd_624.m_fontcolor.Color;
    *(float *)&this->_embed_UIWnd_624.m_fontcolor.Color = v4;
    if ( v4 <= 3.0 )
      return v4;
    v6 = rand() & 0x80000001;
    v5 = v6 == 0;
    if ( v6 < 0 )
      v5 = (((_BYTE)v6 - 1) | 0xFFFFFFFE) == -1;
    if ( v5 )
    {
      this->m_FrameA.m_childs.m_nSize = 51;
      if ( strlen((const char *)&this->m_vecPosArray) )
      {
        ((Actor *)&this->m_partyActor.m_nActionType)->SetMaterialName(&this->m_vecPosArray);
        this->_embed_UIWnd_624.m_fontcolor.Color = 0;
        return v4;
      }
      ((Actor *)&this->m_partyActor.m_nActionType)->CompareActionName(51, 2);
    }
    this->_embed_UIWnd_624.m_fontcolor.Color = 0;
  }
  return v4;
}

// 0x004180B0
int RoleSystem::CheckWidgetReady(gbRay *pRay)
{
  struct gbOBBox actionId; // [esp+0x4] [ebp-0x4C] BYREF

  if ( !*(_DWORD *)&this->m_partyActor.m_szTexture[4] )
    return 0;
  ((Actor *)&this->m_partyActor.m_nActionType)->PlayAction((int)&actionId);
  actionId.trans.m[3][0] = actionId.trans.m[3][0] + this->m_fPosX;
  actionId.trans.m[3][1] = actionId.trans.m[3][1] + this->m_fPosY;
  actionId.trans.m[3][2] = actionId.trans.m[3][2] + this->m_fPosZ;
  return ((gbRay *)pRay)->IsColOBB_H(actionId);
}

// 0x00418130
int RoleSystem::GetMoveState()
{
  int result; // eax
  int v2; // [esp+0x4] [ebp+0x4]

  if ( v2 )
  {
    result = this->m_FrameA.m_rect.right;
    if ( result != 4 )
      this->m_FrameA.m_rect.top = result;
    this->m_FrameA.m_rect.right = 4;
    LODWORD(this->m_fRotAxisZ) = 6;
  }
  else
  {
    result = this->m_FrameA.m_rect.top;
    this->m_FrameA.m_rect.right = result;
  }
  return result;
}

// 0x004181E0
int RoleSystem::Notify()
{
  int result; // eax

  this->m_FrameA.m_childs.m_nSize = 0;

  *((_DWORD *)this + 2173) = this->m_fontcolor.Color;
  *((_DWORD *)this + 2174) = this->m_wndcolor.Color;
  *((_DWORD *)this + 2175) = this->m_id;
  result = this->m_FrameA.m_rect.right;
  if ( result == 4 )
  {
    result = this->m_FrameA.m_rect.top;
    this->m_FrameA.m_rect.right = result;
    if ( result == 4 )
      this->m_FrameA.m_rect.right = 1;
  }
  if ( this->m_nActionState == 3 )
    this->m_nActionState = 0;
  this->_embed_UIWnd_624.m_rect.bottom = 0;
  return result;
}

// 0x00418970
void RoleSystem::AddVec3ToTarget(int nVal, int nVal2)
{
  double v3; // st7
  float v4; // [esp+0x0] [ebp-0xC]
  float v5; // [esp+0x4] [ebp-0x8]
  float v6; // [esp+0x8] [ebp-0x4]
  float *v7; // [esp+0x18] [ebp+0xC]

  v4 = *(float *)nVal2 + *v7;
  v5 = *(float *)(nVal2 + 4) + v7[1];
  v3 = *(float *)(nVal2 + 8) + v7[2];
  *(float *)nVal = v4;
  v6 = v3;
  *(float *)(nVal + 4) = v5;
  *(float *)(nVal + 8) = v6;
}

// 0x004189C0
int RoleSystem::StartPathMove(
        
        char *pszBuf,
        int nVal,
        char *pszBuf2,
        int nVal2,
        float fVal,
        int nVal3)
{
  RoleSystem *v8; // eax
  int RolePtr; // edi
  RoleSystem *v10; // eax
  RoleSystem *v11; // eax
  int v12; // ebx
  int v13; // eax
  long double v14; // st7
  double v15; // st6
  long double v16; // st7
  float m_fMoveTargetZ; // eax
  float v18; // edx
  double v19; // st6
  RoleSystem *v20; // eax
  int v21; // edi
  RoleSystem *v22; // eax
  unsigned int v23; // eax
  unsigned int v24; // ecx
  double v25; // st6
  RoleSystem *v26; // eax
  int v27; // edi
  RoleSystem *v28; // eax
  char *v29; // eax
  int result; // eax
  unsigned int v31; // edx
  unsigned int v32; // eax
  int *v33; // [esp-0x14] [ebp-0x54]
  int *v34; // [esp-0x14] [ebp-0x54]
  char *v35; // [esp-0x10] [ebp-0x50]
  char *v36; // [esp-0x10] [ebp-0x50]
  int v37; // [esp-0xC] [ebp-0x4C]
  int v38; // [esp-0xC] [ebp-0x4C]
  int v39; // [esp-0x4] [ebp-0x44]
  int v40; // [esp-0x4] [ebp-0x44]
  int v41; // [esp-0x4] [ebp-0x44]
  int v42; // [esp-0x4] [ebp-0x44]
  float pTargetPos; // [esp+0x10] [ebp-0x30] BYREF
  float v44; // [esp+0x14] [ebp-0x2C]
  float v45; // [esp+0x18] [ebp-0x28]
  float v46; // [esp+0x1C] [ebp-0x24] BYREF
  float v47; // [esp+0x20] [ebp-0x20]
  float v48; // [esp+0x24] [ebp-0x1C]
  float v49; // [esp+0x28] [ebp-0x18]
  float v50; // [esp+0x2C] [ebp-0x14]
  float v51; // [esp+0x30] [ebp-0x10]
  float v52; // [esp+0x34] [ebp-0xC]
  float v53; // [esp+0x38] [ebp-0x8]
  float v54; // [esp+0x3C] [ebp-0x4]

  LODWORD(this->m_fMoveTargetZ) = nVal3;
  if ( *(_DWORD *)(nVal3 + 264) )
  {
    v8 = (RoleSystem *)UISceneUpdate();
    RolePtr = ((RoleSystem *)v8)->GetRolePtr(0);
    v39 = 1;
  }
  else
  {
    v40 = *(_DWORD *)this->m_partyActor.m_szTexture;
    v10 = (RoleSystem *)UISceneUpdate();
    RolePtr = ((RoleSystem *)v10)->GetRolePtr(v40);
    v39 = *(_DWORD *)this->m_partyActor.m_szTexture;
  }
  v11 = (RoleSystem *)UISceneUpdate();
  v12 = ((RoleSystem *)v11)->GetRolePtr(v39);
  v53 = 0.0;
  v52 = ((double)(int)pszBuf + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 128);
  v54 = ((double)nVal + 0.5) * g_fSceneTileSize + *(float *)(RolePtr + 136);
  if ( (int)pszBuf >= 0 )
  {
    v13 = *(_DWORD *)(RolePtr + 152);
    if ( (int)pszBuf < v13 && nVal >= 0 && nVal < *(_DWORD *)(RolePtr + 156) )
      v53 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (_DWORD)&pszBuf[nVal * v13]);
  }
  pTargetPos = v52;
  v44 = v53;
  v45 = v54;
  v50 = 0.0;
  v49 = ((double)(int)pszBuf2 + 0.5) * g_fSceneTileSize + *(float *)(v12 + 128);
  v51 = ((double)nVal2 + 0.5) * g_fSceneTileSize + *(float *)(v12 + 136);
  if ( ((RoleSystem *)v12)->IsInBounds((int)pszBuf2, nVal2) )
    v50 = *(float *)(*(_DWORD *)(v12 + 160) + 8 * (_DWORD)&pszBuf2[nVal2 * *(_DWORD *)(v12 + 152)]);
  v14 = fVal * 0.017453292;
  v47 = v50;
  v46 = v49;
  v48 = v51;
  v53 = 0.0;
  v52 = sin(v14);
  v15 = -(12.0 + 12.0);
  v52 = v15 * v52;
  v16 = cos(v14) * v15;
  m_fMoveTargetZ = this->m_fMoveTargetZ;
  v18 = *(float *)(LODWORD(m_fMoveTargetZ) + 212);
  if ( fabs(v50 - this->m_fPosY) <= fabs(v44 - this->m_fPosY) )
  {
    v46 = *(float *)(LODWORD(m_fMoveTargetZ) + 212);
    v25 = *(float *)(LODWORD(m_fMoveTargetZ) + 220);
    v42 = *(_DWORD *)this->m_partyActor.m_szTexture;
    v46 = v18 + v52;
    v47 = v47 + v53;
    v48 = v25 + v16;
    v26 = (RoleSystem *)UISceneUpdate();
    v27 = ((RoleSystem *)v26)->GetRolePtr(v42);
    v38 = (__int64)((*(float *)&this->m_id - *(float *)(v27 + 136)) / g_fSceneTileSize);
    v36 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(v27 + 128)) / g_fSceneTileSize);
    v34 = *(int **)this->m_partyActor.m_szTexture;
    v28 = (RoleSystem *)UISceneUpdate();
    if ( ((RoleSystem *)v28)->AdvanceOnPath(v34, v36, v38, pszBuf2, nVal2) )
    {
      this->SetMoveTarget(&v46, 1);
      v31 = LODWORD(v44);
      v32 = LODWORD(v45);
// [VFTABLE] *(float *)&this->m_FrameA.__vftable = pTargetPos;
      this->m_FrameA.m_fontcolor.Color = v31;
      this->m_FrameA.m_wndcolor.Color = v32;
      goto LABEL_17;
    }
LABEL_15:
    v29 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("outdist");
    return ((PalScriptMgr *)&stru_DBA134)->ShowTextBox(v29);
  }
  pTargetPos = *(float *)(LODWORD(m_fMoveTargetZ) + 212);
  v19 = *(float *)(LODWORD(m_fMoveTargetZ) + 220);
  v41 = *(_DWORD *)this->m_partyActor.m_szTexture;
  pTargetPos = v18 + v52;
  v44 = v44 + v53;
  v45 = v19 + v16;
  v20 = (RoleSystem *)UISceneUpdate();
  v21 = ((RoleSystem *)v20)->GetRolePtr(v41);
  v37 = (__int64)((*(float *)&this->m_id - *(float *)(v21 + 136)) / g_fSceneTileSize);
  v35 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(v21 + 128)) / g_fSceneTileSize);
  v33 = *(int **)this->m_partyActor.m_szTexture;
  v22 = (RoleSystem *)UISceneUpdate();
  if ( !((RoleSystem *)v22)->AdvanceOnPath(v33, v35, v37, pszBuf, nVal) )
    goto LABEL_15;
  this->SetMoveTarget(&pTargetPos, 1);
  v23 = LODWORD(v47);
  v24 = LODWORD(v48);
// [VFTABLE] *(float *)&this->m_FrameA.__vftable = v46;
  this->m_FrameA.m_fontcolor.Color = v23;
  this->m_FrameA.m_wndcolor.Color = v24;
LABEL_17:
  if ( *(float *)&this->m_FrameA.m_fontcolor.Color <= (double)this->m_fPosY )
    LODWORD(this->m_fSavedRotX) = 2;
  else
    LODWORD(this->m_fSavedRotX) = 1;
  result = this->m_FrameA.m_rect.right;
  *(float *)&this->m_FrameA.m_id = fVal;
  LODWORD(this->m_fRotAxisZ) = 7;
  this->m_nMovement = 0;
  if ( result != 4 )
    this->m_FrameA.m_rect.top = result;
  this->m_FrameA.m_rect.right = 4;
  return result;
}

// 0x00418D90
BOOL RoleSystem::IsInBounds(int nVal, int nVal2)
{
  return nVal >= 0 && nVal < this->m_nDispWndColor && nVal2 >= 0 && nVal2 < this->m_nField9C;
}

// 0x00418DC0
char RoleSystem::TryMoveToTarget(__int16 pData, int nVal)
{
  PalScript *v4; // eax
  float *v5; // eax
  double v7; // st7
  float v8; // edx
  long double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  RoleSystem *v13; // eax
  int RolePtr; // edi
  RoleSystem *v15; // eax
  char *v16; // eax
  LONG right; // eax
  int *v18; // [esp-0x20] [ebp-A0h]
  char *v19; // [esp-0x1C] [ebp-0x9C]
  int v20; // [esp-0x18] [ebp-0x98]
  char *v21; // [esp-0x14] [ebp-0x94]
  int v22; // [esp-0x10] [ebp-0x90]
  int v23; // [esp-0x10] [ebp-0x90]
  float pszBuf; // [esp+0x4] [ebp-0x7C]
  float v25; // [esp+0xC] [ebp-0x74]
  float pTargetPos; // [esp+0x10] [ebp-0x70] BYREF
  float v27; // [esp+0x14] [ebp-0x6C]
  float v28; // [esp+0x18] [ebp-0x68]
  gbVec3D v29; // [esp+0x1C] [ebp-0x64] BYREF
  float v30; // [esp+0x28] [ebp-0x58]
  float v31; // [esp+0x30] [ebp-0x50]
  gbMatrix4 pMatrix; // [esp+0x34] [ebp-0x4C] BYREF
  float v33; // [esp+0x78] [ebp-0x8]

  v4 = (PalScript *)UISceneUpdate();
  ((PalScript *)v4)->SetAction(pData);
  LODWORD(this->m_fMoveTargetZ) = v5;
  if ( !v5 )
    return 0;
  v7 = v5[56] + 180.0;
  pTargetPos = 0.0;
  v27 = 0.0;
  v28 = 0.0;
  pTargetPos = v5[53];
  v8 = v5[55];
  v25 = v7;
  v9 = v7 * 0.017453292;
  v30 = sin(v9);
  v31 = cos(v9);
  v10 = -(12.0 + 12.0);
  pszBuf = v10;
  v31 = pszBuf * v31;
  pTargetPos = pTargetPos + v10 * v30;
  v27 = 0.0;
  v28 = v8 + v31;
  ((Object3D *)LODWORD(this->m_fMoveTargetZ))->SetTransform(&pMatrix);
  v11 = v33 * 0.60000002;
  if ( v11 > 100.0 )
    v11 = 100.0;
  *(float *)&this->m_FrameA.m_fontcolor.Color = v11;
  v12 = pTargetPos - *(float *)&this->m_fontcolor.Color;
  v29.y = v27;
  v29.z = v28;
  v29.x = v12;
  v29.y = -*(float *)&this->m_wndcolor.Color;
  v29.z = v28 - *(float *)&this->m_id;
  if ( 12.0 * 5.0 >= ((gbVec3D *)&v29)->Length() )
    goto LABEL_8;
  v22 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v13 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v13)->GetRolePtr(v22);
  v23 = (__int64)((v28 - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  v21 = (char *)(__int64)((pTargetPos - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v20 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  v19 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v18 = *(int **)this->m_partyActor.m_szTexture;
  v15 = (RoleSystem *)UISceneUpdate();
  if ( ((RoleSystem *)v15)->AdvanceOnPath(v18, v19, v20, v21, v23) )
  {
LABEL_8:
    this->SetMoveTarget(&pTargetPos, 1);
    LODWORD(this->m_fSavedRotX) = nVal;
    right = this->m_FrameA.m_rect.right;
    *(float *)&this->m_FrameA.m_id = v25;
    LODWORD(this->m_fRotAxisZ) = 8;
    this->m_nMovement = 0;
    if ( right != 4 )
      this->m_FrameA.m_rect.top = right;
    this->m_FrameA.m_rect.right = 4;
    return 1;
  }
  else
  {
    v16 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("outdist");
    ((PalScriptMgr *)&stru_DBA134)->ShowTextBox(v16);
    return 0;
  }
}

// 0x00419030
int RoleSystem::ResetPathParams(int nVal)
{
  LONG right; // eax
  unsigned int v4; // edx

  right = this->m_FrameA.m_rect.right;
  this->m_FrameA.m_id = (void *)0x40000000;
  this->m_FrameA.m_rect.left = 0;
  LODWORD(this->m_fRotAxisZ) = 9;
  if ( right != 4 )
    this->m_FrameA.m_rect.top = right;
  v4 = *(_DWORD *)&this->m_partyActor.m_szTexture[12];
  this->m_FrameA.m_rect.right = 4;
// [VFTABLE] this->m_FrameA.__vftable = (vtbl_0056AE2C *)nVal;
  this->m_FrameA.m_fontcolor.Color = v4;
  return nVal;
}

// 0x00419790
int RoleSystem::ProcessMoveCommand(int *p_DWORD)
{
  double v3; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st6
  float z; // edx
  float v10; // [esp+0x8] [ebp-0x18]
  float v11; // [esp+0xC] [ebp-0x14]
  float v12; // [esp+0x10] [ebp-0x10]
  gbVec3D v13; // [esp+0x14] [ebp-0xC] BYREF

  this->m_pLinkedSystem = (char *)*p_DWORD;
  LODWORD(this->m_fAnimSpeed) = p_DWORD[1];
  LODWORD(this->m_fMoveRadius) = p_DWORD[2];
  this->m_pRenderObj = (gbGeomNode *)LODWORD(this->m_fPosX);
  this->m_bRenderFlag1 = LODWORD(this->m_fPosY);
  *(float *)&this->m_bRenderFlag2 = this->m_fPosZ;
  this->m_FrameA.m_rect.bottom = 11;
  v10 = *(float *)&this->m_pLinkedSystem - *(float *)&this->m_pRenderObj;
  v3 = this->m_fAnimSpeed - *(float *)&this->m_bRenderFlag1;
  v13.x = v10;
  v11 = v3;
  v4 = this->m_fMoveRadius - *(float *)&this->m_bRenderFlag2;
  v13.y = v11;
  v12 = v4;
  v13.z = v12;
  v5 = ((gbVec3D *)&v13)->Length();
  this->m_FrameA.m_rect.left = 0;
  *(float *)&this->m_FrameA.m_id = v5 * 0.0069444445;
  v6 = *(float *)&this->m_pLinkedSystem - *(float *)&this->m_pRenderObj;
  v13.y = this->m_fAnimSpeed - *(float *)&this->m_bRenderFlag1;
  v7 = this->m_fMoveRadius - *(float *)&this->m_bRenderFlag2;
  this->m_FrameA.m_benable = LODWORD(v13.y);
  v13.z = v7;
  z = v13.z;
  *(float *)&this->m_FrameA.m_bvisible = v6;
  *(float *)&this->m_FrameA.m_bfocus = z;

  this->m_FrameA.m_bvisible = 0;
  this->m_FrameA.m_benable = 0;
  this->m_FrameA.m_bfocus = 0;
  return ((Actor *)&this->m_partyActor.m_nActionType)->CompareActionName(2, 0);
}

// 0x004198C0
void RoleSystem::StartLinearMove(int *pTargetPos, int nMode)
{
  LONG right; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st6
  float z; // eax
  float v11; // [esp+0x8] [ebp-0x18]
  float v12; // [esp+0xC] [ebp-0x14]
  float v13; // [esp+0x10] [ebp-0x10]
  gbVec3D v14; // [esp+0x14] [ebp-0xC] BYREF

  right = this->m_FrameA.m_rect.right;
  if ( right != 4 )
    this->m_FrameA.m_rect.top = right;
  this->m_FrameA.m_rect.right = 4;
  LODWORD(this->m_fRotAxisZ) = 10;
  this->m_nMovement = 0;
  this->m_fSavedRotX = 0.0;
  this->m_pRenderObj = (gbGeomNode *)LODWORD(this->m_fPosX);
  this->m_bRenderFlag1 = LODWORD(this->m_fPosY);
  *(float *)&this->m_bRenderFlag2 = this->m_fPosZ;
  this->m_pLinkedSystem = (char *)*pTargetPos;
  LODWORD(this->m_fAnimSpeed) = pTargetPos[1];
  LODWORD(this->m_fMoveRadius) = pTargetPos[2];
  this->m_FrameA.m_childs.m_nSize = nMode;

  v11 = *(float *)&this->m_pLinkedSystem - *(float *)&this->m_pRenderObj;
  v5 = this->m_fAnimSpeed - *(float *)&this->m_bRenderFlag1;
  v14.x = v11;
  v12 = v5;
  v6 = this->m_fMoveRadius - *(float *)&this->m_bRenderFlag2;
  v14.y = v12;
  v13 = v6;
  v14.z = v13;
  v7 = ((gbVec3D *)&v14)->Length() / *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
  this->m_FrameA.m_rect.left = 0;
  *(float *)&this->m_FrameA.m_id = v7;
  v8 = *(float *)&this->m_pLinkedSystem - *(float *)&this->m_pRenderObj;
  v14.y = this->m_fAnimSpeed - *(float *)&this->m_bRenderFlag1;
  v9 = this->m_fMoveRadius - *(float *)&this->m_bRenderFlag2;
  this->m_FrameA.m_benable = LODWORD(v14.y);
  v14.z = v9;
  z = v14.z;
  *(float *)&this->m_FrameA.m_bvisible = v8;
  *(float *)&this->m_FrameA.m_bfocus = z;

  this->m_FrameA.m_bvisible = 0;
  this->m_FrameA.m_benable = 0;
  this->m_FrameA.m_bfocus = 0;
}

// 0x00419A20
void RoleSystem::GetActorState(double thisa, int nVal, int nVal2, int nVal3)
{
  RoleSystem *v6; // eax
  int v7; // [esp-0x10] [ebp-0x20]
  int pfVal; // [esp+0x4] [ebp-0xC] BYREF
  float v9; // [esp+0x8] [ebp-0x8]
  int v10; // [esp+0xC] [ebp-0x4]

  pfVal = LODWORD(thisa);
  v7 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v9 = 0.0;
  v10 = HIDWORD(thisa);
  v6 = (RoleSystem *)UISceneUpdate();
  ((RoleSystem *)v6)->SetRoleParam(v7, (float *)&pfVal, 0, 0);
  // __asm { fstp    [esp+0x10+var_8] }
  this->StartLinearMove(&pfVal, nVal);
}

// 0x00419A80
int RoleSystem::GetDirection(float *pOut)
{
  int result; // eax
  gbMatrix4 actionId; // [esp+0x8] [ebp-0x4C] BYREF
  float v5; // [esp+0x4C] [ebp-0x8]

  *pOut = this->m_fPosX;
  pOut[1] = this->m_fPosY;
  pOut[2] = this->m_fPosZ;
  result = ((Actor *)&this->m_partyActor.m_nActionType)->PlayAction((int)&actionId);
  pOut[1] = v5 + pOut[1];
  return result;
}

// 0x00419AE0
int RoleSystem::NotifyAndSetMode6()
{
  int result; // eax

  result = this->Notify();
  this->m_FrameA.m_rect.right = 6;
  return result;
}

// 0x00419B10
__int64 RoleSystem::SetCollisionRadius()
{
  __int64 result; // rax

  result = (__int64)(12.0 * 12.0);
  *(_DWORD *)&g_szSceneUIText[8] = result;
  return result;
}

// 0x00419B30
void RoleSystem::UpdateFollowBehavior(float fDelta)
{
  double v3; // st7
  int m_nSize; // eax
  _BYTE v5[12]; // [esp+0x4] [ebp-0x18]
  gbVec3D v6; // [esp+0x10] [ebp-0xC] BYREF

  if ( g_pRoleSystem )
  {
    *(float *)v5 = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
    *(float *)&v5[4] = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
    v6 = *(gbVec3D *)v5;
    v3 = ((gbVec3D *)&v6)->Length();
    m_nSize = this->m_FrameA.m_childs.m_nSize;
    if ( m_nSize )
    {
      if ( m_nSize == 2 )
      {
        if ( v3 <= (double)*(int *)&g_szSceneUIText[8] * 1.4 )
        {
          this->ScanMoveDirections(fDelta);
        }
        else
        {
          this->m_FrameA.m_childs.m_nSize = 0;

          this->m_FrameA.m_rect.bottom = 0;
        }
      }
    }
    else if ( v3 < (double)*(int *)&g_szSceneUIText[8] )
    {
      this->m_FrameA.m_childs.m_nSize = 2;

      this->m_FrameA.m_rect.bottom = 6;
    }
  }
}

// 0x00419EF0
BOOL RoleSystem::AdvancePathStep(float *pfVal)
{
  double v4; // st7
  double v5; // st6
  float v7; // eax
  RoleSystem *v8; // eax
  int RolePtr; // edi
  RoleSystem *v10; // eax
  int *v11; // [esp-0x1C] [ebp-0x3C]
  char *v12; // [esp-0x18] [ebp-0x38]
  int v13; // [esp-0x14] [ebp-0x34]
  char *v14; // [esp-0x10] [ebp-0x30]
  int v15; // [esp-0xC] [ebp-0x2C]
  int v16; // [esp-0xC] [ebp-0x2C]
  float v17; // [esp+0xC] [ebp-0x14]
  float v18; // [esp+0x10] [ebp-0x10]
  gbVec3D v19; // [esp+0x14] [ebp-0xC] BYREF
  float pfVala; // [esp+0x24] [ebp+0x4]

  v4 = *pfVal - *(float *)&this->m_fontcolor.Color;
  v17 = pfVal[1] - *(float *)&this->m_wndcolor.Color;
  v5 = pfVal[2] - *(float *)&this->m_id;
  v19.y = v17;
  v18 = v5;
  v19.x = v4;
  v19.z = v18;
  pfVala = ((gbVec3D *)&v19)->Length();
  if ( 0.87 * 500.0 < pfVala )
    return 0;
  if ( 12.0 + 12.0 > pfVala )
    return 1;
  if ( v19.z / pfVala * *(float *)&this->m_rect.bottom
     + v19.y / pfVala * *(float *)&this->m_rect.right
     + v19.x / pfVala * *(float *)&this->m_rect.top <= 0.87 )
    return 0;
  v7 = pfVal[2];
  v15 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v19.x = *pfVal;
  v19.z = v7;
  v19.y = 0.0;
  v8 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v8)->GetRolePtr(v15);
  v16 = (__int64)((v19.z - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  v14 = (char *)(__int64)((v19.x - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v13 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  v12 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v11 = *(int **)this->m_partyActor.m_szTexture;
  v10 = (RoleSystem *)UISceneUpdate();
  return ((RoleSystem *)v10)->AdvanceOnPath(v11, v12, v13, v14, v16) != 0;
}

// 0x0041A150
void RoleSystem::SetActorTexture(const char *pszName)
{
  char Buffer[260]; // [esp+0x4] [ebp-0x104] BYREF

  sprintf(Buffer, "role\\%s\\%s.tga", &this->m_nAnimState, pszName);
  ((Actor *)&this->m_partyActor.m_nActionType)->SetTextureName(Buffer);
}

// 0x0041A1A0
void RoleSystem::ScanMoveDirections(float fRadius)
{
  RoleSystem *v3; // ebp
  int RolePtr; // edi
  long double v5; // st7
  double v6; // st6
  double v7; // st7
  float v8; // edx
  float v9; // eax
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  float v15; // [esp+0x0] [ebp-0x6C]
  float v16; // [esp+0x4] [ebp-0x68]
  float v17; // [esp+0x8] [ebp-0x64]
  int i; // [esp+0x1C] [ebp-0x50]
  float v19; // [esp+0x20] [ebp-0x4C]
  float *v20; // [esp+0x24] [ebp-0x48]
  char *nFlag; // [esp+0x28] [ebp-0x44]
  int nVal; // [esp+0x2C] [ebp-0x40]
  float pfVal2; // [esp+0x30] [ebp-0x3C] BYREF
  float v24; // [esp+0x34] [ebp-0x38]
  float v25; // [esp+0x38] [ebp-0x34]
  float v26; // [esp+0x3C] [ebp-0x30]
  float v27; // [esp+0x40] [ebp-0x2C]
  float v28; // [esp+0x44] [ebp-0x28]
  float pfVal; // [esp+0x48] [ebp-0x24] BYREF
  float v30; // [esp+0x4C] [ebp-0x20]
  float v31; // [esp+0x50] [ebp-0x1C]
  gbVec3D v32; // [esp+0x54] [ebp-0x18] BYREF
  gbVec3D v33; // [esp+0x60] [ebp-0xC] BYREF
  float fRadiusa; // [esp+0x70] [ebp+0x4]

  v20 = (float *)g_pRoleSystem;
  v3 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v3)->GetRolePtr(*(_DWORD *)this->m_partyActor.m_szTexture);
  nFlag = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  nVal = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  v30 = 0.0;
  pfVal2 = 0.0;
  v24 = 0.0;
  v25 = 0.0;
  v19 = -1.0;
  v26 = 0.0;
  v27 = 0.0;
  v28 = 0.0;
  for ( i = 0; i < 360; i += 30 )
  {
    v5 = (double)i * 0.017453292;
    pfVal = cos(v5);
    v6 = (double)*(int *)&g_szSceneUIText[8];
    pfVal = v6 * pfVal;
    v30 = v30 * v6;
    v31 = v6 * sin(v5);
    this->UpdateMoveInterpolation(&pfVal, &pfVal2);
    pfVal2 = pfVal2 + *(float *)&this->m_fontcolor.Color;
    v24 = v24 + *(float *)&this->m_wndcolor.Color;
    v25 = v25 + *(float *)&this->m_id;
    if ( ((RoleSystem *)v3)->AdvanceOnPath(*(int **)this->m_partyActor.m_szTexture, nFlag, nVal, (char *)(__int64)((pfVal2 - *(float *)(RolePtr + 128)) / g_fSceneTileSize), (__int64)((v25 - *(float *)(RolePtr + 136)) / g_fSceneTileSize)) )
    {
      v17 = v25 - v20[3];
      v16 = v24 - v20[2];
      v15 = pfVal2 - v20[1];
      // [AUTO-COMMENTED] v32 = *((gbVec3D *)&v33)->gbVec3D(v15, v16, v17);
      v7 = ((gbVec3D *)&v32)->Length();
      if ( v7 > v19 )
      {
        v26 = pfVal2;
        v19 = v7;
        v27 = v24;
        v28 = v25;
      }
    }
  }
  v8 = v27;
  v9 = v28;
  *(float *)&this->m_pLinkedSystem = v26;
  this->m_fAnimSpeed = v8;
  this->m_fMoveRadius = v9;
  this->InterpolateMoveFrame(1.0);
  v10 = fRadius * 4.0;
  v32.x = v10 * *(float *)&this->m_nAnimation;
  v32.y = v10 * *(float *)&this->m_nAnimCopy1;
  v11 = v10 * *(float *)&this->m_nAnimCopy2;
  *(float *)&this->m_FrameA.m_bvisible = v32.x + *(float *)&this->m_FrameA.m_bvisible;
  *(float *)&this->m_FrameA.m_benable = v32.y + *(float *)&this->m_FrameA.m_benable;
  *(float *)&this->m_FrameA.m_bfocus = v11 + *(float *)&this->m_FrameA.m_bfocus;
  v12 = *(float *)&this->m_FrameA.m_childs.m_needscriptdel * 1.4;
  this->m_FrameA.m_benable = 0;
  fRadiusa = v12;
  v13 = ((gbVec3D *)&this->m_FrameA.m_bvisible)->Length();
  if ( v13 > fRadiusa )
  {
    v14 = fRadiusa / v13;
    *(float *)&this->m_FrameA.m_bvisible = v14 * *(float *)&this->m_FrameA.m_bvisible;
    *(float *)&this->m_FrameA.m_benable = v14 * *(float *)&this->m_FrameA.m_benable;
    *(float *)&this->m_FrameA.m_bfocus = v14 * *(float *)&this->m_FrameA.m_bfocus;
  }
}

// 0x0041A450
void RoleSystem::UpdateFollowerMovement(float fVal)
{
  int *v2; // ebx
  float m_fRotAxisZ; // eax
  float v5; // ecx
  int m_needscriptdel; // edx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  char *p_m_nAnimState; // esi
  int v11; // eax
  char *v12; // eax
  double v13; // st7
  double v14; // st7
  int v15; // eax
  double v16; // st7
  long double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  int v23; // eax
  int v24; // edi
  int nCurCount; // ecx
  int v26; // ecx
  char *v27; // eax
  char *v28; // eax
  char *v29; // eax
  char *v30; // eax
  char *v31; // eax
  double v32; // st7
  int v33; // [esp-0x8] [ebp-0x134]
  int v34; // [esp-0x8] [ebp-0x134]
  gbVec3D v35; // [esp+0xC] [ebp-0x120] BYREF
  int v36; // [esp+0x18] [ebp-0x114]
  gbVec3D v37; // [esp+0x1C] [ebp-0x110] BYREF
  float v38; // [esp+0x28] [ebp-0x104]
  char Buffer[256]; // [esp+0x2C] [ebp-0x100] BYREF

  m_fRotAxisZ = this->m_fRotAxisZ;
  *(float *)&v36 = 12.0 * 8.0;
  switch ( LODWORD(m_fRotAxisZ) )
  {
    case 0:
      this->m_FrameA.m_childs.m_nSize = 1;

      LODWORD(this->m_fRotAxisZ) = 1;
      this->m_fMoveParamZ = 160.0;

      break;
    case 1:


      LODWORD(v35.x) = this->m_nAnimation;
      v5 = *(float *)&this->m_nAnimCopy2;
      v35.y = *(float *)&this->m_nAnimCopy1 * fVal;
      v35.z = v5 * fVal;
      *(float *)&this->m_FrameA.m_bvisible = v35.x * fVal + *(float *)&this->m_FrameA.m_bvisible;
      *(float *)&this->m_FrameA.m_benable = v35.y + *(float *)&this->m_FrameA.m_benable;
      *(float *)&this->m_FrameA.m_bfocus = v35.z + *(float *)&this->m_FrameA.m_bfocus;
      m_needscriptdel = this->m_FrameA.m_childs.m_needscriptdel;
      this->m_FrameA.m_benable = 0;
      v38 = *(float *)&m_needscriptdel;
      v7 = ((gbVec3D *)&this->m_FrameA.m_bvisible)->Length();
      if ( v7 > v38 )
      {
        v8 = v38 / v7;
        *(float *)&this->m_FrameA.m_bvisible = v8 * *(float *)&this->m_FrameA.m_bvisible;
        *(float *)&this->m_FrameA.m_benable = v8 * *(float *)&this->m_FrameA.m_benable;
        *(float *)&this->m_FrameA.m_bfocus = v8 * *(float *)&this->m_FrameA.m_bfocus;
      }
      v35.x = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
      v35.y = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
      v9 = *(float *)&this->m_id - *(float *)&g_pRoleSystem->m_id;
      v37 = v35;
      v35.z = v9;
      if ( ((gbVec3D *)&v37)->Length() < (double)*(float *)&v36 )
      {
        LODWORD(this->m_fRotAxisZ) = 2;

        ((Actor *)&this->m_partyActor.m_nActionType)->SetVisible((int)&dword_5888A8);
        p_m_nAnimState = &this->m_nAnimState;
        v11 = atoi(p_m_nAnimState);
        if ( g_ScriptCounters[(v11 - 415) % 0xAu].nCurCount < g_ScriptCounters[(v11 - 415) % 0xAu].nMaxCount )
          sprintf(Buffer, "%s_3", p_m_nAnimState);
        else
          sprintf(Buffer, "%s_1", p_m_nAnimState);
        v12 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(Buffer);
        ((UISceneMap *)&g_UISceneMapDlg)->LoadCompass(v12, 0);
// [VFTABLE] ((void ( *)(UISceneMap *, int))g_UISceneMapDlg.__vftable->ShowWindow)(&g_UISceneMapDlg, 1);
// [VFTABLE] ((void ( *)(UISceneMap *, _DWORD, _DWORD))g_UISceneMapDlg.__vftable->Update_2ff0)(
// [VFTABLE]   &g_UISceneMapDlg,
// [VFTABLE]   0,
// [VFTABLE]   0);
      }
      break;
    case 2:
      if ( ((Object3D *)&this->m_partyActor.m_nActionType)->GetVisNode() )
      {
        (*(void ( **)(int, int))(*(_DWORD *)this->m_partyActor.m_nHP + 24))(
          this->m_partyActor.m_nHP,
          1075137304);
        ((Actor *)&this->m_partyActor.m_nActionType)->SetTimeScale(0.0);
        this->m_FrameA.m_rect.left = 0;
        LODWORD(this->m_fRotAxisZ) = 3;
        *(float *)&this->m_FrameA.m_id = (double)(rand() % 100) * 0.099999994 + 10.0;
      }
      break;
    case 3:
      *(float *)&this->m_FrameA.m_rect.left = fVal + *(float *)&this->m_FrameA.m_rect.left;
      v35.x = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
      v13 = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
      v37.x = v35.x;
      v35.y = v13;
      v14 = *(float *)&this->m_id - *(float *)&g_pRoleSystem->m_id;
      v37.y = v35.y;
      v35.z = v14;
      v37.z = v35.z;
      if ( ((gbVec3D *)&v37)->Length() < (double)*(float *)&v36 )
        this->m_FrameA.m_rect.left = 0;
      if ( *(float *)&this->m_FrameA.m_rect.left >= (double)*(float *)&this->m_FrameA.m_id )
      {
        LODWORD(this->m_fRotAxisZ) = 4;
        v15 = rand();
        this->m_FrameA.m_benable = 0;
        this->m_FrameA.m_childs.m_nSize = 2;
        v36 = v15 % 360;
        v16 = (double)(v15 % 360);
        *((float *)this + 2172) = v16;
        v17 = v16 * 0.017453292;
        *(float *)&this->m_FrameA.m_bvisible = sin(v17);
        *(float *)&this->m_FrameA.m_bfocus = cos(v17);

        v18 = *(float *)&this->m_FrameA.m_childs.m_needscriptdel * 0.40000001;
        *(float *)&this->m_FrameA.m_bvisible = v18 * *(float *)&this->m_FrameA.m_bvisible;
        *(float *)&this->m_FrameA.m_benable = v18 * *(float *)&this->m_FrameA.m_benable;
        *(float *)&this->m_FrameA.m_bfocus = v18 * *(float *)&this->m_FrameA.m_bfocus;
        this->m_FrameA.m_rect.bottom = 6;
        this->m_FrameA.m_rect.left = 0;
      }
      break;
    case 4:
      v19 = fVal + *(float *)&this->m_FrameA.m_rect.left;
      *(float *)&this->m_FrameA.m_rect.left = v19;
      if ( v19 <= 30.0 )
      {
        v35.x = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
        v20 = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
        v37.x = v35.x;
        v35.y = v20;
        v21 = *(float *)&this->m_id - *(float *)&g_pRoleSystem->m_id;
        v37.y = v35.y;
        v35.z = v21;
        v37.z = v35.z;
        v22 = ((gbVec3D *)&v37)->Length();
        *(float *)&v36 = v22;
        if ( v22 >= *(float *)&g_pRoleSystem->m_rect.left + *(float *)&this->m_rect.left )
        {
          if ( this->m_FrameA.m_rect.bottom != 6 )
          {
            this->m_FrameA.m_childs.m_nSize = 2;

            this->m_FrameA.m_rect.bottom = 6;
          }
          this->ScanMoveDirections(fVal);
          v32 = 2.0 - *(float *)&v36 / (double)*(int *)&g_szSceneUIText[8];
          if ( v32 >= 0.0 )
          {
            if ( v32 > 1.0 )
              v32 = 1.0;
          }
          else
          {
            v32 = 0.0;
          }
          *(float *)&this->m_FrameA.m_bvisible = v32 * *(float *)&this->m_FrameA.m_bvisible;
          *(float *)&this->m_FrameA.m_benable = v32 * *(float *)&this->m_FrameA.m_benable;
          *(float *)&this->m_FrameA.m_bfocus = v32 * *(float *)&this->m_FrameA.m_bfocus;
          if ( v32 == 0.0 )
            this->IsPathComplete((float *)&g_pRoleSystem->m_fontcolor.Color, 1);
        }
        else
        {
          v23 = atoi(&this->m_nAnimState) - 415;
          v24 = v23;
          nCurCount = g_ScriptCounters[v23].nCurCount;
          if ( nCurCount >= g_ScriptCounters[v23].nMaxCount )
          {
            if ( v23 >= 2 )
            {
              if ( v23 >= 4 )
              {
                LODWORD(v35.x) = dword_C0205C[4 * v23];
                LODWORD(v35.y) = 1;
                LODWORD(v35.z) = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(SLODWORD(v35.x));
                ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&v35, v2);
                v34 = LODWORD(v35.z) + 4;
                v30 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("getitem");
                _snprintf(Buffer, 0xFFu, v30, v34);
                ((InputSystem *)Buffer)->ProcessFrame();
              }
              else
              {
                ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += 9999;
                v29 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("getmoney");
                sprintf(Buffer, v29, 9999);
                ((InputSystem *)Buffer)->ProcessFrame();
              }
            }
            else
            {
              *((_DWORD *)&::Buffer.m_partyActor.m_fActionAssignParam + 352 * g_nCurrentRoleSlot) += 9999;
              v28 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("getexp");
              sprintf(Buffer, v28, 9999);
              ((InputSystem *)Buffer)->ProcessFrame();
            }
            g_ScriptCounters[v24].nState = 0;
            sprintf(Buffer, "%s_4", &this->m_nAnimState);
          }
          else
          {
            v26 = nCurCount + 1;
            g_ScriptCounters[v23].nCurCount = v26;
            v33 = v26;
            if ( v23 >= 4 )
            {
              *((_DWORD *)&::Buffer.m_partyActor.m_fActionAssignParam + 352 * g_nCurrentRoleSlot) += v26;
              v27 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("getexp");
            }
            else
            {
              ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += v26;
              v27 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("getmoney");
            }
            sprintf(Buffer, v27, v33);
            ((InputSystem *)Buffer)->ProcessFrame();
            sprintf(Buffer, "%s_2", &this->m_nAnimState);
          }
          v31 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(Buffer);
          ((UISceneMap *)&g_UISceneMapDlg)->LoadCompass(v31, 0);
// [VFTABLE] ((void ( *)(UISceneMap *, int))g_UISceneMapDlg.__vftable->ShowWindow)(&g_UISceneMapDlg, 1);
// [VFTABLE] ((void ( *)(UISceneMap *, _DWORD, _DWORD))g_UISceneMapDlg.__vftable->Update_2ff0)(
// [VFTABLE]   &g_UISceneMapDlg,
// [VFTABLE]   0,
// [VFTABLE]   0);
          *(_DWORD *)&this->m_partyActor.m_szTexture[4] = 0;
        }
      }
      else
      {
        *(_DWORD *)&this->m_partyActor.m_szTexture[4] = 0;
      }
      break;
    default:
      return;
  }
}

// 0x0041ABE0
void RoleSystem::UpdateFollowVelocity()
{
  double v2; // st7
  UIWnd *m_pWaypointWnd; // ecx
  double v4; // st7
  double v5; // st7
  float v6; // [esp+0x8] [ebp-0x1C]
  float v7; // [esp+0x8] [ebp-0x1C]
  float v8; // [esp+0x8] [ebp-0x1C]
  float v9; // [esp+0x10] [ebp-0x14]
  float v10; // [esp+0x14] [ebp-0x10]
  float v11; // [esp+0x14] [ebp-0x10]
  float v12; // [esp+0x14] [ebp-0x10]
  gbVec3D v13; // [esp+0x18] [ebp-0xC] BYREF

  v13.y = 0.0;
  v10 = *(float *)&this->m_FrameA.m_bfocus * 1.4;
  v11 = v10 + *(float *)&this->m_id;
  v13.x = *(float *)&this->m_FrameA.m_bvisible * 1.4
        + *(float *)&this->m_fontcolor.Color
        - *(float *)&this->m_szModelPath;
  v13.z = v11 - *(float *)&this->m_pWaypointWnd;
  v2 = ((gbVec3D *)&v13)->Length();
  if ( v2 > 100.0 )
  {
    m_pWaypointWnd = this->m_pWaypointWnd;
    this->_todo_5AC = this->m_szModelPath;
    this->m_pCtrlPoint = 0;
    this->m_nMoveRole = (int)m_pWaypointWnd;
    *(float *)&this->_todo_5AC = *(float *)&this->_todo_5AC - *(float *)&this->m_fontcolor.Color;
    *(float *)&this->m_pCtrlPoint = *(float *)&this->m_pCtrlPoint - *(float *)&this->m_wndcolor.Color;
    *(float *)&this->m_nMoveRole = *(float *)&this->m_nMoveRole - *(float *)&this->m_id;
    ((gbVec3D *)&this->_todo_5AC)->Normalize();
    v6 = v2;
    v7 = (v6 - 100.0) * 1.4;
    v9 = *(float *)&this->m_pCtrlPoint * v7;
    v12 = *(float *)&this->m_nMoveRole * v7;
    *(float *)&this->m_nAnimation = *(float *)&this->_todo_5AC * v7 + *(float *)&this->m_nAnimation;
    *(float *)&this->m_nAnimCopy1 = v9 + *(float *)&this->m_nAnimCopy1;
    *(float *)&this->m_nAnimCopy2 = v12 + *(float *)&this->m_nAnimCopy2;
    v8 = *(float *)&this->m_FrameA.m_bcreateok;
    v4 = ((gbVec3D *)&this->m_nAnimation)->Length();
    if ( v4 > v8 )
    {
      v5 = v8 / v4;
      *(float *)&this->m_nAnimation = v5 * *(float *)&this->m_nAnimation;
      *(float *)&this->m_nAnimCopy1 = v5 * *(float *)&this->m_nAnimCopy1;
      *(float *)&this->m_nAnimCopy2 = v5 * *(float *)&this->m_nAnimCopy2;
    }
  }
}

// 0x0041AD40
void RoleSystem::UpdateFollowVelocityEx()
{
  double v2; // st7
  UIWnd *m_pWaypointWnd; // ecx
  double v4; // st7
  double v5; // st7
  float v6; // [esp+0x8] [ebp-0x1C]
  float v7; // [esp+0x8] [ebp-0x1C]
  float v8; // [esp+0x8] [ebp-0x1C]
  float v9; // [esp+0x10] [ebp-0x14]
  float v10; // [esp+0x14] [ebp-0x10]
  float v11; // [esp+0x14] [ebp-0x10]
  float v12; // [esp+0x14] [ebp-0x10]
  gbVec3D v13; // [esp+0x18] [ebp-0xC] BYREF

  v13.y = 0.0;
  v10 = *(float *)&this->m_FrameA.m_bfocus * 1.4;
  v11 = v10 + *(float *)&this->m_id;
  v13.x = *(float *)&this->m_FrameA.m_bvisible * 1.4
        + *(float *)&this->m_fontcolor.Color
        - *(float *)&this->m_szModelPath;
  v13.z = v11 - *(float *)&this->m_pWaypointWnd;
  v2 = ((gbVec3D *)&v13)->Length();
  if ( v2 > this->m_fMoveParamZ )
  {
    m_pWaypointWnd = this->m_pWaypointWnd;
    this->_todo_5AC = this->m_szModelPath;
    this->m_pCtrlPoint = 0;
    this->m_nMoveRole = (int)m_pWaypointWnd;
    *(float *)&this->_todo_5AC = *(float *)&this->_todo_5AC - *(float *)&this->m_fontcolor.Color;
    *(float *)&this->m_pCtrlPoint = *(float *)&this->m_pCtrlPoint - *(float *)&this->m_wndcolor.Color;
    *(float *)&this->m_nMoveRole = *(float *)&this->m_nMoveRole - *(float *)&this->m_id;
    ((gbVec3D *)&this->_todo_5AC)->Normalize();
    v6 = v2;
    v7 = (v6 - this->m_fMoveParamZ) * 1.4;
    v9 = *(float *)&this->m_pCtrlPoint * v7;
    v12 = *(float *)&this->m_nMoveRole * v7;
    *(float *)&this->m_nAnimation = *(float *)&this->_todo_5AC * v7 + *(float *)&this->m_nAnimation;
    *(float *)&this->m_nAnimCopy1 = v9 + *(float *)&this->m_nAnimCopy1;
    *(float *)&this->m_nAnimCopy2 = v12 + *(float *)&this->m_nAnimCopy2;
    v8 = *(float *)&this->m_FrameA.m_bcreateok;
    v4 = ((gbVec3D *)&this->m_nAnimation)->Length();
    if ( v4 > v8 )
    {
      v5 = v8 / v4;
      *(float *)&this->m_nAnimation = v5 * *(float *)&this->m_nAnimation;
      *(float *)&this->m_nAnimCopy1 = v5 * *(float *)&this->m_nAnimCopy1;
      *(float *)&this->m_nAnimCopy2 = v5 * *(float *)&this->m_nAnimCopy2;
    }
  }
}

// 0x0041AEA0
void RoleSystem::SetBlendMode(float fAlpha)
{
  if ( fAlpha < 1.0 )
    ((gbVisNode *)this->m_partyActor.m_nHP)->SetBlend(1, LODWORD(fAlpha));
  else
    ((gbVisNode *)this->m_partyActor.m_nHP)->SetBlend(0, 1065353216);
}

// 0x0041AEE0
int RoleSystem::SetTransform(int *p_DWORD)
{
  int result; // eax

  this->m_fontcolor.Color = p_DWORD[1];
  this->m_wndcolor.Color = p_DWORD[2];
  this->m_id = (void *)p_DWORD[3];
  LODWORD(this->m_fPosX) = p_DWORD[40];
  LODWORD(this->m_fPosY) = p_DWORD[41];
  LODWORD(this->m_fPosZ) = p_DWORD[42];
  this->m_nDispFontColor = p_DWORD[37];
  this->m_nDispWndColor = p_DWORD[38];
  result = p_DWORD[39];
  this->m_nField9C = result;
  return result;
}

// 0x0041AF50
int RoleSystem::AllocPathPage(int nVal, int nVal2)
{
  float *p_m_fDirZ; // esi
  _DWORD *m_nPathField7C; // eax
  int todo_078; // edx
  int v6; // ecx
  int result; // eax
  int *v8; // edi
  _DWORD *v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // edi
  unsigned int v14; // eax
  int **v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // ebx
  char *v20; // ebx
  int v21; // edx
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int v25; // [esp+0x10] [ebp-0x10] BYREF
  int v26; // [esp+0x14] [ebp-0xC]
  int v27; // [esp+0x18] [ebp-0x8]
  int v28; // [esp+0x1C] [ebp-0x4]

  p_m_fDirZ = &this->m_fDirZ;
  if ( !this->m_pPathListHead
    || (m_nPathField7C = (_DWORD *)this->m_nPathField7C, todo_078 = this->_todo_078,
                                                         m_nPathField7C == (_DWORD *)todo_078) )
  {
    v8 = (int *)operator new(0x1000u);
    if ( *((_DWORD *)p_m_fDirZ + 11) )
    {
      v14 = *((_DWORD *)p_m_fDirZ + 8);
      if ( v14 >= *((_DWORD *)p_m_fDirZ + 9) + 4 * *((_DWORD *)p_m_fDirZ + 10) - 4 )
      {
        v19 = ((int)(v14 - *((_DWORD *)p_m_fDirZ + 4)) >> 2) + 1;
        v20 = (char *)&((RoleSystem *)p_m_fDirZ)->GetRoleName(2 * v19)[4 * v19];
        *(_DWORD *)v20 = v8;
        ((ScreenEffect *)&v25)->CopyParams(*((int **)p_m_fDirZ + 3));
        v21 = v26;
        *((_DWORD *)p_m_fDirZ + 1) = v25;
        v22 = v27;
        *((_DWORD *)p_m_fDirZ + 2) = v21;
        v23 = v28;
        *((_DWORD *)p_m_fDirZ + 3) = v22;
        *((_DWORD *)p_m_fDirZ + 4) = v23;
        v24 = *(_DWORD *)v20 + 4096;
        p_m_fDirZ[5] = *(float *)v20;
        *((_DWORD *)p_m_fDirZ + 6) = v24;
        *((_DWORD *)p_m_fDirZ + 7) = v8;
        *((_DWORD *)p_m_fDirZ + 8) = v20;
      }
      else
      {
        v15 = (int **)(v14 + 4);
        *((_DWORD *)p_m_fDirZ + 8) = v15;
        *v15 = v8;
        ((ScreenEffect *)&v25)->CopyParams(v8);
        v16 = v26;
        *((_DWORD *)p_m_fDirZ + 5) = v25;
        v17 = v27;
        *((_DWORD *)p_m_fDirZ + 6) = v16;
        v18 = v28;
        *((_DWORD *)p_m_fDirZ + 7) = v17;
        *((_DWORD *)p_m_fDirZ + 8) = v18;
      }
    }
    else
    {
      *((_DWORD *)p_m_fDirZ + 10) = 2;
      v9 = operator new(8u);
      *((_DWORD *)p_m_fDirZ + 9) = v9;
      v9[1] = v8;
      ((ScreenEffect *)&v25)->CopyParams(v8 + 512);
      v10 = v25;
      v11 = v27;
      v12 = v26;
      v13 = v28;
      *((_DWORD *)p_m_fDirZ + 1) = v25;
      *((_DWORD *)p_m_fDirZ + 2) = v12;
      *((_DWORD *)p_m_fDirZ + 3) = v11;
      *((_DWORD *)p_m_fDirZ + 4) = v13;
      *((_DWORD *)p_m_fDirZ + 5) = v10;
      *((_DWORD *)p_m_fDirZ + 6) = v12;
      *((_DWORD *)p_m_fDirZ + 7) = v11;
      *((_DWORD *)p_m_fDirZ + 8) = v13;
    }
    m_nPathField7C = (_DWORD *)*((_DWORD *)p_m_fDirZ + 7);
    *((_DWORD *)p_m_fDirZ + 7) = m_nPathField7C + 4;
    if ( !m_nPathField7C )
      goto LABEL_17;
    *m_nPathField7C = 1;
    m_nPathField7C[1] = nVal;
    m_nPathField7C[2] = nVal2;
    goto LABEL_16;
  }
  this->m_nPathField7C = (int)(m_nPathField7C + 4);
  if ( m_nPathField7C + 4 != (_DWORD *)todo_078 )
  {
    if ( !m_nPathField7C )
    {
LABEL_17:
      result = *((_DWORD *)p_m_fDirZ + 11) + 1;
      *((_DWORD *)p_m_fDirZ + 11) = result;
      return result;
    }
    *m_nPathField7C = 1;
    m_nPathField7C[1] = nVal;
    m_nPathField7C[2] = nVal2;
LABEL_16:
    m_nPathField7C[3] = v28;
    goto LABEL_17;
  }
  if ( m_nPathField7C )
  {
    v6 = v28;
    *m_nPathField7C = 1;
    m_nPathField7C[1] = nVal;
    m_nPathField7C[2] = nVal2;
    m_nPathField7C[3] = v6;
  }
  ((ScreenEffectMgr *)p_m_fDirZ)->AllocEffectBlock();
  result = *((_DWORD *)p_m_fDirZ + 11) + 1;
  *((_DWORD *)p_m_fDirZ + 11) = result;
  return result;
}

// 0x0041B120
int RoleSystem::StopPathMovement(int nVal)
{
  float *p_m_fDirZ; // esi
  _DWORD *m_nPathField7C; // eax
  int todo_078; // edx
  int v5; // ecx
  int v6; // edx
  int result; // eax
  int v8; // ecx
  int v9; // edx
  int *v10; // edi
  _DWORD *v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // edi
  unsigned int v16; // eax
  int **v17; // eax
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // ebx
  char *v22; // ebx
  int v23; // edx
  int v24; // ecx
  int v25; // edx
  int v26; // ecx
  _DWORD *v27; // eax
  int v28; // edx
  int v29; // ecx
  int v30; // [esp+0xC] [ebp-0x10] BYREF
  int v31; // [esp+0x10] [ebp-0xC]
  int v32; // [esp+0x14] [ebp-0x8]
  int v33; // [esp+0x18] [ebp-0x4]

  p_m_fDirZ = &this->m_fDirZ;
  if ( !this->m_pPathListHead
    || (m_nPathField7C = (_DWORD *)this->m_nPathField7C, todo_078 = this->_todo_078,
                                                         m_nPathField7C == (_DWORD *)todo_078) )
  {
    v10 = (int *)operator new(0x1000u);
    if ( *((_DWORD *)p_m_fDirZ + 11) )
    {
      v16 = *((_DWORD *)p_m_fDirZ + 8);
      if ( v16 >= *((_DWORD *)p_m_fDirZ + 9) + 4 * *((_DWORD *)p_m_fDirZ + 10) - 4 )
      {
        v21 = ((int)(v16 - *((_DWORD *)p_m_fDirZ + 4)) >> 2) + 1;
        v22 = (char *)&((RoleSystem *)p_m_fDirZ)->GetRoleName(2 * v21)[4 * v21];
        *(_DWORD *)v22 = v10;
        ((ScreenEffect *)&v30)->CopyParams(*((int **)p_m_fDirZ + 3));
        v23 = v31;
        *((_DWORD *)p_m_fDirZ + 1) = v30;
        v24 = v32;
        *((_DWORD *)p_m_fDirZ + 2) = v23;
        v25 = v33;
        *((_DWORD *)p_m_fDirZ + 3) = v24;
        *((_DWORD *)p_m_fDirZ + 4) = v25;
        v26 = *(_DWORD *)v22 + 4096;
        p_m_fDirZ[5] = *(float *)v22;
        *((_DWORD *)p_m_fDirZ + 6) = v26;
        *((_DWORD *)p_m_fDirZ + 7) = v10;
        *((_DWORD *)p_m_fDirZ + 8) = v22;
      }
      else
      {
        v17 = (int **)(v16 + 4);
        *((_DWORD *)p_m_fDirZ + 8) = v17;
        *v17 = v10;
        ((ScreenEffect *)&v30)->CopyParams(v10);
        v18 = v31;
        *((_DWORD *)p_m_fDirZ + 5) = v30;
        v19 = v32;
        *((_DWORD *)p_m_fDirZ + 6) = v18;
        v20 = v33;
        *((_DWORD *)p_m_fDirZ + 7) = v19;
        *((_DWORD *)p_m_fDirZ + 8) = v20;
      }
    }
    else
    {
      *((_DWORD *)p_m_fDirZ + 10) = 2;
      v11 = operator new(8u);
      *((_DWORD *)p_m_fDirZ + 9) = v11;
      v11[1] = v10;
      ((ScreenEffect *)&v30)->CopyParams(v10 + 512);
      v12 = v30;
      v13 = v32;
      v14 = v31;
      v15 = v33;
      *((_DWORD *)p_m_fDirZ + 1) = v30;
      *((_DWORD *)p_m_fDirZ + 2) = v14;
      *((_DWORD *)p_m_fDirZ + 3) = v13;
      *((_DWORD *)p_m_fDirZ + 4) = v15;
      *((_DWORD *)p_m_fDirZ + 5) = v12;
      *((_DWORD *)p_m_fDirZ + 6) = v14;
      *((_DWORD *)p_m_fDirZ + 7) = v13;
      *((_DWORD *)p_m_fDirZ + 8) = v15;
    }
    v27 = (_DWORD *)*((_DWORD *)p_m_fDirZ + 7);
    *((_DWORD *)p_m_fDirZ + 7) = v27 + 4;
    if ( v27 )
    {
      v28 = v31;
      v29 = v32;
      *v27 = 2;
      v27[1] = v28;
      v27[2] = v29;
      v27[3] = nVal;
    }
LABEL_16:
    result = *((_DWORD *)p_m_fDirZ + 11) + 1;
    *((_DWORD *)p_m_fDirZ + 11) = result;
    return result;
  }
  this->m_nPathField7C = (int)(m_nPathField7C + 4);
  if ( m_nPathField7C + 4 != (_DWORD *)todo_078 )
  {
    if ( m_nPathField7C )
    {
      v8 = v31;
      v9 = v32;
      *m_nPathField7C = 2;
      m_nPathField7C[1] = v8;
      m_nPathField7C[2] = v9;
      m_nPathField7C[3] = nVal;
      result = *((_DWORD *)p_m_fDirZ + 11) + 1;
      *((_DWORD *)p_m_fDirZ + 11) = result;
      return result;
    }
    goto LABEL_16;
  }
  if ( m_nPathField7C )
  {
    v5 = v31;
    v6 = v32;
    *m_nPathField7C = 2;
    m_nPathField7C[1] = v5;
    m_nPathField7C[2] = v6;
    m_nPathField7C[3] = nVal;
  }
  ((ScreenEffectMgr *)p_m_fDirZ)->AllocEffectBlock();
  result = *((_DWORD *)p_m_fDirZ + 11) + 1;
  *((_DWORD *)p_m_fDirZ + 11) = result;
  return result;
}

// 0x0041B300
int RoleSystem::GetCurrentTile()
{
  int result; // eax
  char *m_pPathCurrent; // eax
  int v4; // ebx
  char *v5; // ecx
  char *m_pPathNext; // eax
  char **v7; // eax
  char *v8; // ecx
  void *m_nPathState; // [esp-0x10] [ebp-0x34]
  int nTileX; // [esp+0x8] [ebp-0x1C]
  int nTileY; // [esp+0xC] [ebp-0x18]
  int v12; // [esp+0x10] [ebp-0x14]

  for ( result = (int)this->m_pPathListHead; result; result = (int)this->m_pPathListHead )
  {
    m_pPathCurrent = this->m_pPathCurrent;
    v4 = *(_DWORD *)m_pPathCurrent;
    nTileX = *((_DWORD *)m_pPathCurrent + 1);
    v12 = *((_DWORD *)m_pPathCurrent + 3);
    nTileY = *((_DWORD *)m_pPathCurrent + 2);
    v5 = this->m_pPathListHead - 1;
    this->m_pPathCurrent = m_pPathCurrent + 16;
    this->m_pPathListHead = v5;
    if ( !v5 || m_pPathCurrent + 16 == (char *)this->m_nPathCount )
    {
      m_pPathNext = this->m_pPathNext;
      this->m_pPathNext = m_pPathNext + 4;
      operator delete(*(void **)m_pPathNext);
      if ( this->m_pPathListHead )
      {
        v7 = (char **)this->m_pPathNext;
        v8 = *v7;
        this->m_pPathPoints = *v7;
        this->m_nPathCount = (int)(v8 + 4096);
        this->m_pPathCurrent = v8;
        this->m_pPathNext = (char *)v7;
      }
      else
      {
        this->m_pPathPoints = 0;
        this->m_nPathCount = 0;
        this->m_pPathCurrent = 0;
        this->m_pPathNext = 0;
        this->_todo_074 = 0;
        m_nPathState = (void *)this->m_nPathState;
        this->_todo_078 = 0;
        this->m_nPathField7C = 0;
        this->m_fMoveX = 0.0;
        operator delete(m_nPathState);
      }
    }
    if ( v4 == 1 )
    {
      this->CalcTileDistance(nTileX, nTileY);
    }
    else if ( v4 == 2 )
    {
      *(_DWORD *)&this->m_partyActor.m_szTexture[4] = v12;
    }
  }
  return result;
}

// 0x0041B420
void RoleSystem::LoadWeaponModel(char *pszRoleName)
{
  int v2; // ebx
  int v4; // ebp
  const char **v5; // edi
  int v6; // eax
  int v7; // edi
  const char *v8; // ebp
  unsigned int *v9; // edi
  gbGeomNode *v10; // eax
  gbGeomNode *v11; // edi
  gbGeomNode *v12; // ecx
  char Buffer[256]; // [esp+0x14] [ebp-0x20C] BYREF
  char v14[256]; // [esp+0x114] [ebp-0x10C] BYREF
  int v15; // [esp+0x21C] [ebp-0x4]

  v2 = 0;
  v4 = 0;
  v5 = (const char **)&pszAction;
  while ( _strcmpi(pszRoleName, *v5) )
  {
    ++v5;
    ++v4;
    if ( (int)v5 >= (int)dword_56A898 )
      goto LABEL_6;
  }
  v2 = v4;
LABEL_6:
  if ( this->m_nAnimState != 49 )
    return;
  if ( v2 != 32 && v2 != 46 )
  {
    if ( v2 != 29 || _strcmpi(&this->m_nAnimState, (const char *)&g_pfnUpdateFuncs[4]) )
    {
LABEL_24:
      LOBYTE(this->_embed_UIWnd_624.m_id) = 0;
      BYTE1(this->_embed_UIWnd_624.m_id) = 0;
      return;
    }
    LOBYTE(this->_embed_UIWnd_624.m_id) = 0;
    BYTE1(this->_embed_UIWnd_624.m_id) = 1;
    goto LABEL_19;
  }
  v6 = dword_56A898[v2] - 1;
  if ( dword_56A898[v2] == 1 )
  {
    LOBYTE(this->_embed_UIWnd_624.m_id) = 1;
  }
  else
  {
    LOBYTE(this->_embed_UIWnd_624.m_id) = 0;
    if ( v6 == 1 )
    {
      BYTE1(this->_embed_UIWnd_624.m_id) = 1;
      goto LABEL_17;
    }
  }
  BYTE1(this->_embed_UIWnd_624.m_id) = 0;
LABEL_17:
  if ( !_strcmpi(&this->m_nAnimState, (const char *)&g_pfnUpdateFuncs[3]) )
  {
    LOBYTE(this->_embed_UIWnd_624.m_id) = 1;
    BYTE1(this->_embed_UIWnd_624.m_id) = 1;
  }
LABEL_19:
  v7 = 0;
  v8 = (char *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[36] + 2;
  while ( _strcmpi(&this->m_nAnimState, v8) )
  {
    v8 += 8704;
    ++v7;
    if ( (int)v8 >= (int)&g_pRoleSystemArrayEnd )
    {
      LOBYTE(this->_embed_UIWnd_624.m_id) = 0;
      BYTE1(this->_embed_UIWnd_624.m_id) = 0;
      return;
    }
  }
  if ( v7 == -1 )
    goto LABEL_24;
  v9 = &::Buffer.m_partyActor.m_dwMatMsg[352 * v7 + 8];
  if ( *v9 )
  {
    sprintf(Buffer, "weapon\\%s\\%s.pol", (const char *)(*v9 + 36), (const char *)(*v9 + 36));
    sprintf(v14, "weapon\\%s\\%s%s.tga", (const char *)(*v9 + 36), (const char *)(*v9 + 36), (const char *)(*v9 + 66));
    v10 = (gbGeomNode *)operator new(0x118u);
    v11 = v10;
    v15 = 0;
    if ( v10 )
    {
      v12 = v11;
    }
    else
    {
      v12 = 0;
    }
    v15 = -1;
    this->_embed_UIWnd_624.m_wndcolor.Color = (unsigned int)v12;
    ((gbGeomNode *)v12)->LoadFromFile(Buffer, 0, 0);
    ((gbGeomNode *)this->_embed_UIWnd_624.m_wndcolor.Color)->ReplaceTexture(v14);
  }
}

// 0x0041B6C0
char RoleSystem::ApproachTarget(int nVal)
{
  RoleSystem *v3; // eax
  int RolePtr; // ebx
  __int64 v5; // rax
  int v6; // esi
  int v8; // eax
  RoleSystem *v9; // eax
  int v10; // ebx
  double v11; // st7
  int v12; // ebp
  int *v13; // esi
  int v14; // ecx
  __int64 v15; // rax
  int v16; // esi
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  int v24; // [esp-0x4] [ebp-0x74]
  int v25; // [esp-0x4] [ebp-0x74]
  int v26; // [esp+0x10] [ebp-0x60]
  int v27; // [esp+0x14] [ebp-0x5C]
  int v28; // [esp+0x18] [ebp-0x58]
  int v29; // [esp+0x1C] [ebp-0x54]
  float v30; // [esp+0x1C] [ebp-0x54]
  int v31; // [esp+0x20] [ebp-0x50]
  float v32; // [esp+0x20] [ebp-0x50]
  float v33; // [esp+0x24] [ebp-0x4C]
  int pPoint; // [esp+0x28] [ebp-0x48] BYREF
  int v35; // [esp+0x2C] [ebp-0x44]
  float v36; // [esp+0x30] [ebp-0x40]
  float v37; // [esp+0x34] [ebp-0x3C]
  float v38; // [esp+0x38] [ebp-0x38]
  gbVec3D v39; // [esp+0x3C] [ebp-0x34] BYREF
  gbVec3D v40; // [esp+0x48] [ebp-0x28] BYREF
  gbVec3D pTarget; // [esp+0x54] [ebp-0x1C] BYREF
  int v42; // [esp+0x60] [ebp-0x10]
  int v43; // [esp+0x68] [ebp-0x8]
  int v44; // [esp+0x6C] [ebp-0x4]
  int nVala; // [esp+0x74] [ebp+0x4]

  v24 = *(_DWORD *)this->m_partyActor.m_szTexture;
  v3 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v3)->GetRolePtr(v24);
  v5 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / g_fSceneTileSize);
  pPoint = (__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fSceneTileSize);
  v6 = nVal;
  v35 = v5;
  if ( nVal == -1 )
  {
    v6 = 0;
    while ( 1 )
    {
      v8 = *(_DWORD *)(RolePtr + 8);
      if ( *(_DWORD *)RolePtr != v8 || v8 )
      {
        if ( PointInRect((int *)RolePtr, &pPoint) )
          break;
      }
      ++v6;
      RolePtr += 16;
      if ( v6 >= 8 )
        return 0;
    }
  }
  else if ( !PointInRect((int *)(RolePtr + 16 * nVal), &pPoint) )
  {
    return 0;
  }
  if ( v6 == -1 )
    return 0;
  v25 = (*(_DWORD *)this->m_partyActor.m_szTexture + 1) % 2;
  v28 = v25;
  v9 = (RoleSystem *)UISceneUpdate();
  v10 = ((RoleSystem *)v9)->GetRolePtr(v25);
  v11 = *(float *)&this->m_id - *(float *)(v10 + 136);
  v12 = (__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(v10 + 128)) / g_fSceneTileSize);
  v36 = *(float *)&v12;
  v15 = (__int64)(v11 / g_fSceneTileSize);
  v13 = (int *)(v10 + 16 * v6);
  pPoint = v12;
  v35 = v15;
  v29 = v12;
  v31 = v15;
  v42 = *v13;
  v14 = v13[1];
  nVala = v14;
  v43 = v13[2];
  HIDWORD(v15) = v13[3];
  v16 = 0x7FFFF;
  v44 = HIDWORD(v15);
  if ( v14 > SHIDWORD(v15) )
    return 0;
  v17 = v42;
  v26 = v15 - v14;
  do
  {
    if ( v17 <= v43 )
    {
      v27 = v26 * v26;
      v18 = v12 - v42;
      do
      {
        if ( v27 + v18 * v18 < v16 )
        {
          v16 = v27 + v18 * v18;
          v29 = v17;
          v31 = nVala;
        }
        ++v17;
        --v18;
      }
      while ( v17 <= v43 );
      v17 = v42;
      v12 = LODWORD(v36);
    }
    --v26;
    ++nVala;
  }
  while ( nVala <= v44 );
  if ( v16 == 0x7FFFF )
    return 0;
  v37 = 0.0;
  v36 = ((double)v29 + 0.5) * g_fSceneTileSize + *(float *)(v10 + 128);
  v38 = ((double)v31 + 0.5) * g_fSceneTileSize + *(float *)(v10 + 136);
  if ( v29 >= 0 )
  {
    v19 = *(_DWORD *)(v10 + 152);
    if ( v29 < v19 && v31 >= 0 && v31 < *(_DWORD *)(v10 + 156) )
      v37 = *(float *)(*(_DWORD *)(v10 + 160) + 8 * (v29 + v31 * v19));
  }
  v20 = v36 - this->m_fPosX;
  v39.x = v36;
  v30 = v20;
  v21 = v37 - this->m_fPosY;
  v39.y = v37;
  v39.z = v38;
  v40.x = v30;
  v32 = v21;
  v22 = v38 - this->m_fPosZ;
  pTarget.y = v37;
  v40.y = v32;
  v33 = v22;
  v23 = v36 - *(float *)&this->m_fontcolor.Color;
  pTarget.x = v36;
  pTarget.z = v38;
  v40.z = v33;
  v39.x = v23;
  v39.y = -*(float *)&this->m_wndcolor.Color;
  v39.z = v38 - *(float *)&this->m_id;
  ((gbVec3D *)&v39)->Normalize();
  if ( v39.z * *(float *)&this->m_rect.bottom
     + v39.y * *(float *)&this->m_rect.right
     + v39.x * *(float *)&this->m_rect.top > 0.30000001
    && 12.0 * 6.0 > ((gbVec3D *)&v40)->Length() )
  {
    *(_DWORD *)this->m_partyActor.m_szTexture = v28;
    this->SetTargetRotation(&pTarget);
  }
  return 1;
}

// 0x0041BA10
BOOL RoleSystem::InterpolateHeight(float *pfVal)
{
  double v3; // st7
  double v4; // st6
  double v5; // st7
  gbVec3D v7; // [esp+0x4] [ebp-0x18] BYREF
  float v8; // [esp+0x14] [ebp-0x8]
  float v9; // [esp+0x18] [ebp-0x4]
  float pfVala; // [esp+0x20] [ebp+0x4]

  v3 = *pfVal - *(float *)&this->m_fontcolor.Color;
  v8 = pfVal[1] - *(float *)&this->m_wndcolor.Color;
  v4 = pfVal[2] - *(float *)&this->m_id;
  v7.y = v8;
  v9 = v4;
  v7.x = v3;
  v7.z = v9;
  v5 = ((gbVec3D *)&v7)->Length();
  pfVala = v5;
  if ( v5 > 500.0 )
    return 0;
  if ( pfVala < 1.0 )
    return 1;
  return v7.z / pfVala * *(float *)&this->m_rect.bottom
       + v7.y / pfVala * *(float *)&this->m_rect.right
       + v7.x / pfVala * *(float *)&this->m_rect.top > 0.0;
}

// 0x0041BAD0
int RoleSystem::InitDefaultState()
{
  this->m_FrameA.m_rect.right = 0;
  *(_DWORD *)this->m_partyActor.m_szTexture = 0;
  memset(&this->m_nFacing, 0, 0x1C8u);
  this->m_nActionResult = 1;
  this->m_fCachePosX = 0.0;
  this->m_nRetryCount = 0;
  *(_DWORD *)&this->m_partyActor.m_szTexture[4] = 1;
  this->m_fMoveRole = 0.0;
  this->m_fMoveParamY = 0.0;
  memset(&this->m_fRotAxisZ, 0, 0x24u);
  *(_DWORD *)&this->m_partyActor.m_szTexture[16] = 0;
  *(_DWORD *)&this->m_partyActor.m_szTexture[20] = 1065353216;
  *(_DWORD *)&this->m_partyActor.m_szTexture[24] = 0;
  *((_DWORD *)&this->m_partyActor.m_vecLocalPos + 3) = 1065353216;
  *((_DWORD *)&this->m_partyActor.m_vecLocalPos + 4) = 0;
  *(_DWORD *)&this->m_partyActor.m_nAnimState = 0;
  this->m_partyActor.m_vecLocalPos.x = 0.0;
  this->m_partyActor.m_vecLocalPos.y = 0.0;
  this->m_partyActor.m_vecLocalPos.z = 1.0;
  this->_embed_UIWnd_624.m_fontcolor.Color = 0;
  this->m_nAnimCopy3 = this->m_rect.top;
  this->m_pLinkedRole = (Object3D *)this->m_rect.right;
  this->m_nTransformMode = this->m_rect.bottom;
  this->m_nMoveReset = 0;
  this->_embed_UIWnd_624.m_pfather = 0;
  this->_embed_UIWnd_624.m_rect.bottom = 0;
  this->_embed_UIWnd_624.m_rect.right = 0;
  this->m_FrameA.m_pfather = 0;
  *(_DWORD *)&this->m_partyActor.m_szTexture[8] = 0;
  this->_embed_UIWnd_624.m_wndcolor.Color = 0;
  BYTE1(this->_embed_UIWnd_624.m_id) = 0;
  LOBYTE(this->_embed_UIWnd_624.m_id) = 0;
  LOBYTE(this->m_FrameA.m_childs.capacity) = 0;
  *(_DWORD *)&this->m_partyActor.m_szTexture[12] = 1065353216;
  this->m_FrameA.m_childs.m_pData = (char *)1;
  return 1065353216;
}

// 0x0041BBE0
int RoleSystem::GetCount()
{
  int result; // eax

  result = this->m_FrameA.m_rect.right;
  if ( result != 4 )
  {
    this->m_FrameA.m_rect.top = result;
    this->m_FrameA.m_rect.right = 4;
    this->m_FrameA.m_id = (void *)0x40000000;
    this->m_FrameA.m_rect.left = 0;
    LODWORD(this->m_fRotAxisZ) = 44;
    ((Actor *)&this->m_partyActor.m_nActionType)->SetVisible((int)"c08");
  }
  return result;
}

// 0x0041BC30
int RoleSystem::ExportRoleData(float *pfVal)
{
  int result; // eax
  float m_fPosZ; // edx

  result = (int)pfVal;
  *(_BYTE *)pfVal = this->m_partyActor.m_szTexture[4];
  *((_BYTE *)pfVal + 16) = this->m_partyActor.m_szTexture[0];
  if ( this->m_FrameA.m_rect.bottom == 3 )
  {
    pfVal[1] = this->m_fPosX;
    pfVal[2] = this->m_fPosY;
    m_fPosZ = this->m_fPosZ;
  }
  else
  {
    pfVal[1] = *(float *)&this->m_fontcolor.Color;
    pfVal[2] = *(float *)&this->m_wndcolor.Color;
    m_fPosZ = *(float *)&this->m_id;
  }
  pfVal[3] = m_fPosZ;
  pfVal[5] = *((float *)this + 2172);
  pfVal[6] = *(float *)&this->m_nSpawnParam;
  return result;
}

// 0x0041BD40
int * RoleSystem::ClearColors(_BYTE *p_BYTE)
{
// [VFTABLE] LOBYTE(this->__vftable) = *p_BYTE;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 0;
  this->m_id = 0;
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
  this->m_pfather = 0;
  this->m_childs.m_pData = 0;
  this->m_childs.capacity = 0;
  this->m_childs.m_nSize = 0;
  return (int *)this;
}

// 0x0041BD70
const char * RoleSystem::GetRoleName(unsigned int nRoleIndex)
{
  unsigned int v2; // ebp
  size_t v4; // eax
  char *v5; // edi
  gbColorQuad *left; // ecx
  gbColorQuad *p_m_fontcolor; // eax
  char *v8; // edx
  unsigned int Color; // ebp

  v2 = nRoleIndex;
  v4 = 4 * nRoleIndex;
  if ( (nRoleIndex & 0x20000000) != 0 )
    v4 = 0;
  v5 = (char *)operator new(v4);
  left = (gbColorQuad *)this->m_rect.left;
  p_m_fontcolor = &this->m_pfather->m_fontcolor;
  v8 = &v5[4 * (nRoleIndex >> 2)];
  if ( left != p_m_fontcolor )
  {
    do
    {
      Color = left->Color;
      ++left;
      *(_DWORD *)v8 = Color;
      v8 += 4;
    }
    while ( left != p_m_fontcolor );
    v2 = nRoleIndex;
  }
  operator delete(this->m_childs.m_pData);
  this->m_childs.m_pData = v5;
  this->m_childs.capacity = v2;
  return &v5[4 * (nRoleIndex >> 2)];
}

// 0x0041C090
int RoleSystem::FlushCommandQueue()
{
  int result; // eax
  float v3; // edi
  float v4; // eax
  void **m_nRoleParam2; // eax
  float *v6; // eax
  float v7; // ecx
  void *m_nRoleState0; // [esp-0xC] [ebp-0x10]

  for ( result = LODWORD(this->m_partyActor.m_fAnimParam); result; result = LODWORD(this->m_partyActor.m_fAnimParam) )
  {
    LODWORD(v3) = LODWORD(this->m_partyActor.m_fRoleParam3) + 28;
    LODWORD(v4) = result - 1;
    this->m_partyActor.m_fRoleParam3 = v3;
    this->m_partyActor.m_fAnimParam = v4;
    if ( v4 == 0.0 || LODWORD(v3) == LODWORD(this->m_partyActor.m_fRoleParam2) )
    {
      m_nRoleParam2 = (void **)this->m_partyActor.m_nRoleParam2;
      this->m_partyActor.m_nRoleParam2 = (int)(m_nRoleParam2 + 1);
      operator delete(*m_nRoleParam2);
      if ( LODWORD(this->m_partyActor.m_fAnimParam) )
      {
        v6 = (float *)this->m_partyActor.m_nRoleParam2;
        v7 = *v6;
        this->m_partyActor.m_fRoleParam = *v6;
        LODWORD(this->m_partyActor.m_fRoleParam2) = LODWORD(v7) + 4088;
        this->m_partyActor.m_fRoleParam3 = v7;
        this->m_partyActor.m_nRoleParam2 = (int)v6;
      }
      else
      {
        this->m_partyActor.m_fRoleParam = 0.0;
        this->m_partyActor.m_fRoleParam2 = 0.0;
        this->m_partyActor.m_fRoleParam3 = 0.0;
        this->m_partyActor.m_nRoleParam2 = 0;
        this->m_partyActor.m_pRoleParam3 = 0;
        m_nRoleState0 = (void *)this->m_partyActor.m_nRoleState0;
        this->m_partyActor.m_nCachedA = 0;
        *(_DWORD *)&this->m_partyActor.m_nCachedB = 0;
        this->m_partyActor.m_nTransform = 0;
        operator delete(m_nRoleState0);
      }
    }
  }
  return result;
}

// 0x0041C190
int RoleSystem::SetInactive(int nVal)
{
  this->m_partyActor.m_fMoveRange = 0.0;
  this->m_partyActor.m_pAllocBuf = (char *)nVal;
  return nVal;
}

// 0x0041D220
int RoleSystem::AddCameraKeyframe()
{
  float v1; // edx
  double v2; // st7
  float x; // eax
  int m_nAnimParam1; // edx
  float *p_m_fRoleParam1; // ebx
  float m_fAnimParam; // eax
  float y; // edx
  float *v8; // edi
  int m_nCachedA; // ecx
  int result; // eax
  void *v11; // esi
  _DWORD *v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // esi
  unsigned int v17; // eax
  _DWORD *v18; // eax
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // edi
  int *RoleName; // eax
  int *v24; // edi
  int v25; // edx
  int v26; // ecx
  int v27; // edx
  int v28; // edx
  int v29; // ecx
  int v30; // edx
  int v31; // [esp+0xC] [ebp-0x2C] BYREF
  int v32; // [esp+0x10] [ebp-0x28]
  int v33; // [esp+0x14] [ebp-0x24]
  int v34; // [esp+0x18] [ebp-0x20]
  float v35[7]; // [esp+0x1C] [ebp-0x1C] BYREF

  v1 = *(&this->m_partyActor.m_szText + 1);
  v2 = *(float *)&this->m_fontcolor.Color;
  v35[1] = *(&this->m_partyActor.m_szText + 2);
  v35[3] = *((float *)&this->m_partyActor.m_nModelId + 1);
  x = this->m_partyActor.m_vecBonePos.x;
  v35[2] = v1;
  m_nAnimParam1 = this->m_partyActor.m_nAnimParam1;
  p_m_fRoleParam1 = &this->m_partyActor.m_fRoleParam1;
  v35[5] = x;
  LODWORD(v35[4]) = m_nAnimParam1;
  m_fAnimParam = this->m_partyActor.m_fAnimParam;
  y = this->m_partyActor.m_vecBonePos.y;
  v35[0] = v2;
  v35[6] = y;
  if ( m_fAnimParam == 0.0
    || (v8 = *(float **)&this->m_partyActor.m_nCachedB,
        m_nCachedA = this->m_partyActor.m_nCachedA,
        v8 == (float *)m_nCachedA) )
  {
    v11 = operator new(0xFF8u);
    if ( *((_DWORD *)p_m_fRoleParam1 + 11) )
    {
      v17 = *((_DWORD *)p_m_fRoleParam1 + 8);
      if ( v17 >= *((_DWORD *)p_m_fRoleParam1 + 9) + 4 * *((_DWORD *)p_m_fRoleParam1 + 10) - 4 )
      {
        v22 = ((int)(v17 - *((_DWORD *)p_m_fRoleParam1 + 4)) >> 2) + 1;
        RoleName = (int *)((RoleSystem *)p_m_fRoleParam1)->GetRoleName(2 * v22);
        v24 = &RoleName[v22];
        *v24 = (int)v11;
        ((CameraCtrl *)&v31)->SetCameraSource(*((_DWORD *)p_m_fRoleParam1 + 3), RoleName);
        v25 = v32;
        *((_DWORD *)p_m_fRoleParam1 + 1) = v31;
        v26 = v33;
        *((_DWORD *)p_m_fRoleParam1 + 2) = v25;
        v27 = v34;
        *((_DWORD *)p_m_fRoleParam1 + 3) = v26;
        *((_DWORD *)p_m_fRoleParam1 + 4) = v27;
        ((CameraCtrl *)&v31)->SetCameraSource((int)v11, v24);
        v28 = v32;
        *((_DWORD *)p_m_fRoleParam1 + 5) = v31;
        v29 = v33;
        *((_DWORD *)p_m_fRoleParam1 + 6) = v28;
        v30 = v34;
        *((_DWORD *)p_m_fRoleParam1 + 7) = v29;
        *((_DWORD *)p_m_fRoleParam1 + 8) = v30;
      }
      else
      {
        v18 = (_DWORD *)(v17 + 4);
        *((_DWORD *)p_m_fRoleParam1 + 8) = v18;
        *v18 = v11;
        ((CameraCtrl *)&v31)->SetCameraSource((int)v11, *((int **)p_m_fRoleParam1 + 8));
        v19 = v32;
        *((_DWORD *)p_m_fRoleParam1 + 5) = v31;
        v20 = v33;
        *((_DWORD *)p_m_fRoleParam1 + 6) = v19;
        v21 = v34;
        *((_DWORD *)p_m_fRoleParam1 + 7) = v20;
        *((_DWORD *)p_m_fRoleParam1 + 8) = v21;
      }
    }
    else
    {
      *((_DWORD *)p_m_fRoleParam1 + 10) = 2;
      v12 = operator new(8u);
      *((_DWORD *)p_m_fRoleParam1 + 9) = v12;
      v12[1] = v11;
      ((CameraCtrl *)&v31)->SetCameraSource((int)v11 + 2044, (int *)(*((_DWORD *)p_m_fRoleParam1 + 9) + 4));
      v13 = v31;
      v14 = v33;
      v15 = v32;
      v16 = v34;
      *((_DWORD *)p_m_fRoleParam1 + 1) = v31;
      *((_DWORD *)p_m_fRoleParam1 + 2) = v15;
      *((_DWORD *)p_m_fRoleParam1 + 3) = v14;
      *((_DWORD *)p_m_fRoleParam1 + 4) = v16;
      *((_DWORD *)p_m_fRoleParam1 + 5) = v13;
      *((_DWORD *)p_m_fRoleParam1 + 6) = v15;
      *((_DWORD *)p_m_fRoleParam1 + 7) = v14;
      *((_DWORD *)p_m_fRoleParam1 + 8) = v16;
    }
    v8 = (float *)*((_DWORD *)p_m_fRoleParam1 + 7);
    *((_DWORD *)p_m_fRoleParam1 + 7) = v8 + 7;
    if ( !v8 )
      goto LABEL_16;
    goto LABEL_15;
  }
  *((_DWORD *)p_m_fRoleParam1 + 7) = v8 + 7;
  if ( v8 + 7 != (float *)m_nCachedA )
  {
    if ( !v8 )
    {
LABEL_16:
      result = *((_DWORD *)p_m_fRoleParam1 + 11) + 1;
      *((_DWORD *)p_m_fRoleParam1 + 11) = result;
      return result;
    }
LABEL_15:
    qmemcpy(v8, v35, 0x1Cu);
    goto LABEL_16;
  }
  if ( v8 )
    qmemcpy(v8, v35, 0x1Cu);
  ((CameraCtrl *)p_m_fRoleParam1)->UpdateFOVLerp();
  result = *((_DWORD *)p_m_fRoleParam1 + 11) + 1;
  *((_DWORD *)p_m_fRoleParam1 + 11) = result;
  return result;
}

// 0x00420290
RoleSystem::RoleSystem()
{
  ;
}

// 0x00420320
int RoleSystem::GetCurrentID(int *pnVal, char pData)
{
  int result; // eax
  int v5; // ecx
  int i; // eax
  unsigned int v7; // ebx

  result = (int)this->m_id;
  if ( result )
  {
    sub_420380(pnVal);
    v5 = pnVal[1];
    for ( result = pnVal[3]; v5 <= result; ++v5 )
    {
      for ( i = *pnVal; i <= pnVal[2]; *((_BYTE *)this->m_id + v7) = pData )
      {
        v7 = i + v5 * this->m_fontcolor.Color;
        ++i;
      }
      result = pnVal[3];
    }
  }
  return result;
}

// 0x004203C0
void RoleSystem::InitRoleImage()
{
  sub_420250();
  this->m_nParamArray = 0;
  this->m_rect.left = 0;
  memset(&this->m_bSpawnByteB, 0, 0x80u);
}

// 0x004207D0
unsigned __int8 * RoleSystem::LoadRoleImage(int nIndex, const char *pszPath)
{
  unsigned __int8 *result; // eax
  unsigned __int8 *v5; // ebp
  unsigned __int8 *v6; // edx
  int v7; // ecx

// [VFTABLE] ((void ( *)(RoleSystem *))this->__vftable->ShowWindow)(this);
  this->AllocSlotData(nIndex);
  this->m_nParamArray = nIndex;
  result = (unsigned __int8 *)(*(int ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr + 8))(gfxMgr, 0);
  v5 = result;
  if ( result )
  {
    result = ((gbImage2D *)&this->m_bvisible)->CreateImage(256, 256, 32);
    v6 = result;
    v7 = LODWORD(this->m_fScale) * this->m_nImageIdx;
    if ( v7 > 0 )
    {
      result = 0;
      memset(v6, 0, 4 * v7);
    }
    if ( v6 )
    {
      (*(void ( **)(unsigned __int8 *, _DWORD, int, int, _DWORD, int, unsigned __int8 *))(*(_DWORD *)v5 + 4))(
        v5,
        LODWORD(this->m_fScale),
        this->m_nImageIdx,
        2,
        0,
        2,
        v6);
      this->m_bcreateok = (int)v5;
      this->m_childs.m_needscriptdel = 1;
      this->m_childs.m_nSize = 1;
      return (unsigned __int8 *)sprintf(&this->m_bSpawnByteB, "%s%s", pszPath, pszPath + 32);
    }
  }
  return result;
}

// 0x00420910
RoleSystem * RoleSystem::sub_420910(char a2)
{
  ((RoleSystem *)Block)->InitInternal();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00420930
void RoleSystem::InitInternal()
{

}

// 0x00420940
int RoleSystem::CopyRoleToSlot(RoleSystem *pRoleSystem, int index)
{
  int RolePtr; // eax
  int v5; // ebp
  int result; // eax
  int *p_m_nSpawnFlags; // edi

  RolePtr = ((RoleSystem *)pRoleSystem)->GetRolePtr(index);
  this->AllocSlotData(RolePtr);
  memset(this->m_id, 0xFFu, this->m_fontcolor.Color * this->m_wndcolor.Color);
  v5 = 0;
  this->m_rect.left = (LONG)pRoleSystem;
  result = LODWORD(pRoleSystem->m_fActionParam);
  if ( result > 0 )
  {
    p_m_nSpawnFlags = (int *)&pRoleSystem->m_nSpawnFlags;
    do
    {
      if ( *((unsigned __int8 *)p_m_nSpawnFlags + 246) == index
        && !((RoleSystem *)p_m_nSpawnFlags)->SetActionState((int)this, v5)
        && (p_m_nSpawnFlags[52] & 1) != 0 )
      {
        this->GetCurrentID(p_m_nSpawnFlags + 57, v5);
      }
      result = LODWORD(pRoleSystem->m_fActionParam);
      ++v5;
      p_m_nSpawnFlags += 224;
    }
    while ( v5 < result );
  }
  return result;
}

// 0x004209E0
void RoleSystem::ResetState()
{
  this->m_rect.left = 0;
  sub_4202F0(this);
}

// 0x004209F0
char RoleSystem::GetTile(int nX, int nY)
{
  return *((_BYTE *)this->m_id + nY * this->m_fontcolor.Color + nX);
}

// 0x00420A10
int * RoleSystem::IsTileInBounds(int nVal, int nY, int nVal2)
{
  int Tile; // eax

  if ( nY < 0 )
    return 0;
  if ( nY >= *((_DWORD *)this + 41 * nVal + 123232) )
    return 0;
  if ( nVal2 < 0 )
    return 0;
  if ( nVal2 >= *((_DWORD *)this + 41 * nVal + 123233) )
    return 0;
  Tile = (unsigned __int8)((RoleSystem *)(&this->m_mapData + 5 * nVal))->GetTile(nY, nVal2);
  if ( Tile >= SLODWORD(this->m_fActionParam) )
    return 0;
  else
    return (int *)(&this->m_nSpawnFlags + 896 * Tile);
}

// 0x00420A90
void RoleSystem::SetRoleGridPosition(float fVal, int nVal, float fVal2, int nVal2)
{
  int v6; // ebp
  __int64 v7; // rax
  unsigned __int8 nVal2a; // [esp+0x1C] [ebp+0x10]

  v6 = (__int64)((fVal - *((float *)this + 41 * nVal2 + 123226)) / g_fTileScale);
  v7 = (__int64)((fVal2 - *((float *)this + 41 * nVal2 + 123228)) / g_fTileScale);
  if ( v6 >= 0
    && v6 < *((_DWORD *)this + 41 * nVal2 + 123232)
    && (int)v7 >= 0
    && (int)v7 < *((_DWORD *)this + 41 * nVal2 + 123233) )
  {
    nVal2a = ((RoleSystem *)(&this->m_mapData + 5 * nVal2))->GetTile(v6, v7);
    if ( nVal2a != 0xFF )
      ((PalScriptMgr *)(&this->m_nSpawnFlags + 896 * nVal2a))->ExecuteBlock();
  }
}

// 0x00420F30
int RoleSystem::GetRolePtr(int index)
{
  return (int)this + 164 * index + 492776;
}

// 0x00420F50
char * RoleSystem::GetMapNodePtr(int nIndex)
{
  return (char *)this + 16 * nIndex + 493104;
}

// 0x00420F70
BOOL RoleSystem::IsRoleInRange(int index, int *pnVal, int nVal)
{
  int RolePtr; // eax

  RolePtr = this->GetRolePtr(index);
  return (int)pnVal >= 0
      && (int)pnVal < *(_DWORD *)(RolePtr + 152)
      && nVal >= 0
      && nVal < *(_DWORD *)(RolePtr + 156)
      && ((GRPinput *)RolePtr)->GetJoystickFreePos((int)pnVal, nVal);
}

// 0x00420FB0
BOOL RoleSystem::CheckMoveCollision(int *index, float *pfVal, int nVal)
{
  int RolePtr; // edi

  RolePtr = this->GetRolePtr((int)index);
  return this->CheckCollision(index, (__int64)((*pfVal - *(float *)(RolePtr + 128)) / g_fTileScale));
}

// 0x00421020
BOOL RoleSystem::CheckCollision(int *pResult, int nFlag)
{
  int RolePtr; // eax
  char *v7; // ebx
  char v8; // al
  int *pResulta; // [esp+0x10] [ebp+0x4]
  unsigned __int8 nFlaga; // [esp+0x14] [ebp+0x8]
  int y; // [esp+0x18] [ebp+0xC]

  RolePtr = this->GetRolePtr((int)pResult);
  if ( nFlag < 0 || nFlag >= *(_DWORD *)(RolePtr + 152) || y < 0 || y >= *(_DWORD *)(RolePtr + 156) )
    return 0;
  pResulta = (int *)((GRPinput *)RolePtr)->GetJoystickFreePos(nFlag, y);
  nFlaga = ((RoleSystem *)(&this->m_mapData + 5 * (_DWORD)pResult))->GetTile(nFlag, y);
  if ( nFlaga == 0xFF )
    return (BOOL)pResulta;
  v7 = (char *)this + 896 * nFlaga;
  if ( !v7[397] )
    return (BOOL)pResulta;
  v8 = v7[468];
  if ( v8 == 22 || v8 == 5 || v8 == 7 || v8 == 19 || v8 == 34 || v8 == 37 || v8 == 38 || v8 == 40 )
  {
    if ( pResulta )
      return 1;
    pResulta = 0;
    if ( v7[433] )
      return 1;
    return (BOOL)pResulta;
  }
  if ( v8 == 11 && *((_DWORD *)v7 + 118) == 1 )
  {
    if ( !pResulta && !v7[433] )
      return 0;
  }
  else if ( !pResulta || !v7[433] )
  {
    return 0;
  }
  return 1;
}

// 0x00421150
BOOL RoleSystem::IsTilePassable(char nTileType, int nSceneIdx, int nX, int nY)
{
  int RolePtr; // eax
  unsigned __int8 Tile; // al
  char *v10; // ebx
  char v11; // al
  int nSceneIdxa; // [esp+0x14] [ebp+0x8]

  RolePtr = this->GetRolePtr(nSceneIdx);
  if ( nX < 0 || nX >= *(_DWORD *)(RolePtr + 152) || nY < 0 || nY >= *(_DWORD *)(RolePtr + 156) )
    return 0;
  nSceneIdxa = ((GRPinput *)RolePtr)->GetJoystickFreePos(nX, nY);
  Tile = ((RoleSystem *)(&this->m_mapData + 5 * nSceneIdx))->GetTile(nX, nY);
  if ( Tile == 0xFF || Tile == nTileType )
    return nSceneIdxa;
  v10 = (char *)this + 896 * Tile;
  v11 = v10[468];
  if ( v11 == 22 || v11 == 5 )
  {
    if ( !nSceneIdxa )
    {
      nSceneIdxa = 0;
      if ( !v10[433] )
        return nSceneIdxa;
    }
  }
  else if ( !nSceneIdxa || !v10[433] )
  {
    return 0;
  }
  return 1;
}

// 0x00421440
void RoleSystem::SetRoleParam(int index, float *pfVal, int *pnVal, int *p_DWORD)
{
  int RolePtr; // esi
  int v7; // ebp
  __int64 v8; // rax

  RolePtr = this->GetRolePtr(index);
  v7 = (__int64)((*pfVal - *(float *)(RolePtr + 128)) / g_fTileScale);
  v8 = (__int64)((pfVal[2] - *(float *)(RolePtr + 136)) / g_fTileScale);
  if ( pnVal )
  {
    *pnVal = v7;
    pnVal[1] = v8;
  }
  ((Scene *)this)->GetTileHeight(index, v7, v8, p_DWORD);
}

// 0x004214B0
BOOL RoleSystem::ValidatePathIndex(int index, int nY, int nVal)
{
  int RolePtr; // eax
  int v6; // esi
  BOOL result; // eax
  int v8; // ecx
  unsigned __int8 indexa; // [esp+0x14] [ebp+0x4]

  RolePtr = this->GetRolePtr(index);
  v6 = RolePtr;
  if ( nY < 0 || nY >= *(_DWORD *)(RolePtr + 152) || nVal < 0 || nVal >= *(_DWORD *)(RolePtr + 156) )
    return 0;
  indexa = ((RoleSystem *)(&this->m_mapData + 5 * index))->GetTile(nY, nVal);
  result = 1;
  if ( indexa == 0xFF || *((_BYTE *)&this->m_partyActor.m_nModelId + 896 * indexa + 4) != 44 )
  {
    v8 = *(_DWORD *)(v6 + 160) + 8 * (nY + nVal * *(_DWORD *)(v6 + 152));
    if ( *(_BYTE *)(v8 + 4) <= 1u && *(_BYTE *)(v8 + 5) != 1 )
      return 0;
  }
  return result;
}

// 0x004215B0
int RoleSystem::AdvanceOnPath(
        
        int *pResult,
        char *nFlag,
        int nVal,
        char *pszBuf,
        int nVal2)
{
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // edi
  int v10; // ebp
  int v11; // ebx
  int v13; // [esp+0x10] [ebp-0x8]
  int pszBufa; // [esp+0x28] [ebp+0x10]
  int nVal2a; // [esp+0x2C] [ebp+0x14]

  if ( this->CheckCollision(pResult, (int)nFlag) && this->CheckCollision(pResult, (int)pszBuf) )
  {
    if ( (int)pszBuf < (int)nFlag )
    {
      v6 = nFlag - pszBuf;
      v13 = -1;
    }
    else
    {
      v13 = 1;
      v6 = pszBuf - nFlag;
    }
    if ( nVal2 < nVal )
    {
      pszBufa = -1;
      v7 = nVal - nVal2;
    }
    else
    {
      pszBufa = 1;
      v7 = nVal2 - nVal;
    }
    if ( v7 <= v6 )
    {
      nVal2a = 0;
    }
    else
    {
      v8 = v6;
      v6 = v7;
      v7 = v8;
      nVal2a = 1;
    }
    v9 = 2 * v7;
    v10 = 1;
    v11 = 2 * v7 - v6;
    if ( v6 < 1 )
      return 1;
    while ( this->CheckCollision(pResult, (int)nFlag) )
    {
      if ( v11 >= 0 )
      {
        if ( nVal2a )
          nFlag += v13;
        else
          nVal += pszBufa;
        v11 -= 2 * v6;
      }
      if ( nVal2a )
        nVal += pszBufa;
      else
        nFlag += v13;
      v11 += v9;
      if ( ++v10 > v6 )
        return 1;
    }
  }
  return 0;
}

// 0x00421710
int RoleSystem::ValidatePath(
        
        int *pResult,
        int *nFlag,
        int *pnVal,
        int nVal,
        int nVal2,
        int **a7)
{
  int *v9; // ebx
  int *v10; // ebp
  int v11; // esi
  int v12; // edi
  int v13; // eax
  int v14; // edi
  int v16; // [esp+0x14] [ebp-0x4]
  int nFlaga; // [esp+0x20] [ebp+0x8]
  int pnVala; // [esp+0x24] [ebp+0xC]
  int nVala; // [esp+0x28] [ebp+0x10]
  int nVal2a; // [esp+0x2C] [ebp+0x14]

  *a7 = nFlag;
  a7[1] = pnVal;
  if ( !this->CheckCollision(pResult, (int)nFlag) )
    return 0;
  v9 = nFlag;
  v10 = pnVal;
  if ( nVal < (int)nFlag )
  {
    v11 = (int)nFlag - nVal;
    nVala = -1;
  }
  else
  {
    v11 = nVal - (_DWORD)nFlag;
    nVala = 1;
  }
  if ( nVal2 < (int)pnVal )
  {
    v12 = (int)pnVal - nVal2;
    pnVala = -1;
  }
  else
  {
    pnVala = 1;
    v12 = nVal2 - (_DWORD)pnVal;
  }
  if ( v12 <= v11 )
  {
    nFlaga = 0;
  }
  else
  {
    v13 = v11;
    v11 = v12;
    v12 = v13;
    nFlaga = 1;
  }
  nVal2a = 1;
  v16 = 2 * v12;
  v14 = 2 * v12 - v11;
  if ( v11 >= 1 )
  {
    while ( this->CheckCollision(pResult, (int)v9) )
    {
      *a7 = v9;
      a7[1] = v10;
      if ( v14 >= 0 )
      {
        if ( nFlaga )
          v9 = (int *)((char *)v9 + nVala);
        else
          v10 = (int *)((char *)v10 + pnVala);
        v14 -= 2 * v11;
      }
      if ( nFlaga )
        v10 = (int *)((char *)v10 + pnVala);
      else
        v9 = (int *)((char *)v9 + nVala);
      v14 += v16;
      if ( ++nVal2a > v11 )
        return 1;
    }
    return 0;
  }
  return 1;
}

// 0x004218B0
BOOL RoleSystem::GetPathTarget(
        
        int *pResult,
        int *nFlag,
        int *pnVal,
        char *pszBuf,
        int nVal,
        int **a7)
{
  int *v7; // ebx
  int *v8; // ebp
  int v9; // esi
  int v10; // eax
  int v11; // ecx
  int v12; // edi
  int v15; // [esp+0x14] [ebp-0x14]
  int v16; // [esp+0x18] [ebp-0x10]
  int v17; // [esp+0x1C] [ebp-0xC]
  int v18; // [esp+0x20] [ebp-0x8]
  int v19; // [esp+0x24] [ebp-0x4]

  v7 = nFlag;
  v8 = pnVal;
  *a7 = nFlag;
  a7[1] = pnVal;
  if ( (int)pszBuf < (int)nFlag )
  {
    v17 = -1;
    v9 = (char *)nFlag - pszBuf;
  }
  else
  {
    v17 = 1;
    v9 = pszBuf - (char *)nFlag;
  }
  if ( nVal < (int)pnVal )
  {
    v16 = -1;
    v10 = (int)pnVal - nVal;
  }
  else
  {
    v16 = 1;
    v10 = nVal - (_DWORD)pnVal;
  }
  if ( v10 <= v9 )
  {
    v15 = 0;
  }
  else
  {
    v11 = v9;
    v9 = v10;
    v10 = v11;
    v15 = 1;
  }
  v18 = 1;
  v19 = 2 * v10;
  v12 = 2 * v10 - v9;
  if ( v9 >= 1 )
  {
    while ( this->ValidatePathIndex((int)pResult, (int)v7, (int)v8) )
    {
      if ( this->CheckCollision(pResult, (int)v7) )
      {
        *a7 = v7;
        a7[1] = v8;
      }
      if ( v12 >= 0 )
      {
        if ( v15 )
          v7 = (int *)((char *)v7 + v17);
        else
          v8 = (int *)((char *)v8 + v16);
        v12 -= 2 * v9;
      }
      if ( v15 )
        v8 = (int *)((char *)v8 + v16);
      else
        v7 = (int *)((char *)v7 + v17);
      v12 += v19;
      if ( ++v18 > v9 )
      {
        v7 = nFlag;
        goto LABEL_24;
      }
    }
    return 0;
  }
LABEL_24:
  if ( !this->CheckCollision(pResult, (int)v7) )
    return 0;
  return this->CheckCollision(pResult, (int)pszBuf);
}

// 0x00421A90
int RoleSystem::UpdatePathProgress(
        
        char arg0,
        int index,
        char *pszBuf,
        int nVal,
        char *pszBuf2,
        int nVal2)
{
  int v7; // esi
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  int v11; // ebp
  int v12; // ebx
  int v14; // [esp+0x10] [ebp-0x8]
  int pszBuf2a; // [esp+0x2C] [ebp+0x14]
  int nVal2a; // [esp+0x30] [ebp+0x18]

  if ( this->IsTilePassable(arg0, index, (int)pszBuf, nVal)
    && this->IsTilePassable(arg0, index, (int)pszBuf2, nVal2) )
  {
    if ( (int)pszBuf2 < (int)pszBuf )
    {
      v7 = pszBuf - pszBuf2;
      v14 = -1;
    }
    else
    {
      v14 = 1;
      v7 = pszBuf2 - pszBuf;
    }
    if ( nVal2 < nVal )
    {
      pszBuf2a = -1;
      v8 = nVal - nVal2;
    }
    else
    {
      pszBuf2a = 1;
      v8 = nVal2 - nVal;
    }
    if ( v8 <= v7 )
    {
      nVal2a = 0;
    }
    else
    {
      v9 = v7;
      v7 = v8;
      v8 = v9;
      nVal2a = 1;
    }
    v10 = 2 * v8;
    v11 = 1;
    v12 = 2 * v8 - v7;
    if ( v7 < 1 )
      return 1;
    while ( this->IsTilePassable(arg0, index, (int)pszBuf, nVal) )
    {
      if ( v12 >= 0 )
      {
        if ( nVal2a )
          pszBuf += v14;
        else
          nVal += pszBuf2a;
        v12 -= 2 * v7;
      }
      if ( nVal2a )
        nVal += pszBuf2a;
      else
        pszBuf += v14;
      v12 += v10;
      if ( ++v11 > v7 )
        return 1;
    }
  }
  return 0;
}

// 0x00421BF0
char * RoleSystem::NotifyPathEnd(int nVal)
{
  return (char *)(&this->m_mapData + 5 * nVal);
}

// 0x00421D10
int * RoleSystem::BuildPathSegment(int *pnVal, char pData)
{
  int *v3; // ebp
  unsigned int Color; // ecx
  int v6; // edi
  int *result; // eax
  char v8; // bl
  int i; // eax
  unsigned int v10; // ecx
  int p_DWORD; // [esp+0xC] [ebp-0x1C] BYREF
  int pnVal2; // [esp+0x10] [ebp-0x18] BYREF
  int v13; // [esp+0x14] [ebp-0x14] BYREF
  int nVal2[2]; // [esp+0x18] [ebp-0x10] BYREF
  int *v15; // [esp+0x20] [ebp-0x8]
  unsigned int v16; // [esp+0x24] [ebp-0x4]

  v3 = pnVal;
  Color = this->m_wndcolor.Color;
  nVal2[1] = 0;
  nVal2[0] = 0;
  v15 = (int *)this->m_fontcolor.Color;
  v16 = Color;
  ((Config *)pnVal)->InitDefaults(&p_DWORD, (int *)&pnVal);
  v6 = p_DWORD;
  if ( p_DWORD < nVal2[0] )
  {
    v6 = nVal2[0];
    p_DWORD = nVal2[0];
  }
  result = pnVal;
  if ( (int)pnVal > (int)v15 )
  {
    result = v15;
    pnVal = v15;
  }
  if ( v6 < (int)result )
  {
    v8 = pData;
    do
    {
      if ( ((Config *)v3)->ReadFloatArray(v6, (int)nVal2, &v13, &pnVal2) )
      {
        for ( i = v13; i < pnVal2; *((_BYTE *)this->m_id + v10) = v8 )
          v10 = v6 + this->m_fontcolor.Color * i++;
      }
      result = pnVal;
      ++v6;
    }
    while ( v6 < (int)pnVal );
  }
  return result;
}

// 0x00421DD0
int RoleSystem::ClearWaypointBuffer(int nVal, int nVal2, int nVal3, char pData)
{
  int result; // eax
  int v7; // esi
  int v8; // ebp
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // [esp+0xC] [ebp-0x18]
  int v14; // [esp+0x10] [ebp-0x14]
  int v15; // [esp+0x14] [ebp-0x10] BYREF
  int v16; // [esp+0x18] [ebp-0xC]
  int v17; // [esp+0x1C] [ebp-0x8]
  int v18; // [esp+0x20] [ebp-0x4]
  int nVal3a; // [esp+0x30] [ebp+0xC]

  result = (int)this->m_id;
  if ( result )
  {
    v15 = nVal - nVal3;
    v17 = nVal3 + nVal;
    v16 = nVal2 - nVal3;
    v18 = nVal2 + nVal3;
    sub_420380(&v15);
    result = nVal3 * nVal3;
    v7 = v16;
    v13 = nVal3 * nVal3;
    if ( v16 <= v18 )
    {
      v8 = v15;
      v9 = nVal2 - v16;
      nVal3a = nVal2 - v16;
      do
      {
        v10 = v8;
        if ( v8 <= v17 )
        {
          v11 = v9 * v9;
          v14 = v11;
          v12 = nVal - v8;
          do
          {
            if ( v11 + v12 * v12 <= v13 )
            {
              *((_BYTE *)this->m_id + v10 + v7 * this->m_fontcolor.Color) = pData;
              v8 = v15;
              v11 = v14;
            }
            ++v10;
            --v12;
          }
          while ( v10 <= v17 );
          v9 = nVal3a;
        }
        result = v18;
        ++v7;
        nVal3a = --v9;
      }
      while ( v7 <= v18 );
    }
  }
  return result;
}

// 0x00421EA0
void RoleSystem::ResetTransition()
{
  float m_fActionParam; // esi
  int v2; // edx
  int *v3; // eax
  char *v4; // eax

  m_fActionParam = this->m_fActionParam;
  v2 = 0;
  if ( SLODWORD(m_fActionParam) <= 0 )
  {
LABEL_7:
    v4 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("XMouse");
    ((InputSystem *)v4)->ProcessFrame();
  }
  else
  {
    v3 = &this->m_partyActor.m_nModelId + 1;
    while ( !*((_BYTE *)v3 - 71) || *(_BYTE *)v3 != 24 || v3[2] != 1 )
    {
      ++v2;
      v3 += 224;
      if ( v2 >= SLODWORD(m_fActionParam) )
        goto LABEL_7;
    }
    ((PalScriptMgr *)(&this->m_nSpawnFlags + 896 * v2))->ExecuteBlock();
  }
}

// 0x00421F20
size_t RoleSystem::GetFontColor(FILE *Stream)
{
  gbColorQuad *p_m_fontcolor; // edi

  p_m_fontcolor = &this->m_fontcolor;
  fwrite(&this->m_fontcolor, 4u, 1u, Stream);
  fwrite(&this->m_wndcolor, 4u, 1u, Stream);
  return fwrite(this->m_id, p_m_fontcolor->Color * this->m_wndcolor.Color, 1u, Stream);
}

// 0x00421F70
char RoleSystem::ClearPathData(FILE *Buffer)
{
  FILE *v2; // edi
  unsigned int Color; // ecx
  unsigned int v5; // eax
  int v7; // [esp+0xC] [ebp-0x4] BYREF

  v2 = Buffer;
  fread(&Buffer, 4u, 1u, Buffer);
  fread(&v7, 4u, 1u, v2);
  Color = this->m_fontcolor.Color;
  if ( Buffer == (FILE *)Color )
  {
    v5 = this->m_wndcolor.Color;
    if ( v7 == v5 )
      fread(this->m_id, Color * v5, 1u, v2);
  }
  return sub_4204B0(0, 0, *(_DWORD *)(this->m_nParamArray + 152), *(_DWORD *)(this->m_nParamArray + 156), 1);
}

// 0x00422000
BOOL RoleSystem::BuildModelPath(const char *pszName)
{
  char Buffer[128]; // [esp+0x4] [ebp-0x80] BYREF

  sprintf(Buffer, "%s%s", pszName, pszName + 32);
  return _strcmpi(Buffer, &this->m_bSpawnByteB) == 0;
}

// 0x00422140
int * RoleSystem::ResetModelPaths()
{
  int v2; // edi
  gbVec3D *p_m_vecPosArray; // esi
  RoleSystem *v4; // esi
  int v5; // ebx

  v2 = 50;
  p_m_vecPosArray = &this->m_vecPosArray;
  do
  {
    p_m_vecPosArray += 38;
    --v2;
  }
  while ( v2 );
  v4 = (RoleSystem *)((char *)this + 23324);
  v5 = 64;
  do
  {
    *(unsigned int *)((char *)&v4[-1].m_partyUI3.m_fontcolor.Color + 3) = 0;
    *(unsigned int *)((char *)&v4[-1].m_partyUI3.m_wndcolor.Color + 3) = 0;
    *(void **)((char *)&v4[-1].m_partyUI3.m_id + 3) = 0;
    v4[-1].m_teamData3[24] = 0;
    v4[-1].m_teamData3[25] = 0;
    v4[-1].m_teamData3[26] = 0;
    v4[-1].m_teamData3[27] = 0;
    v4[-1].m_teamData3[28] = 0;
// [VFTABLE] v4->__vftable = 0;
    v4 = (RoleSystem *)((char *)v4 + 620);
    --v5;
  }
  while ( v5 );
  memset(this, 0, 0xF49Cu);
  return (int *)this;
}

// 0x00422430
char RoleSystem::SetAnimBlend(int nVal)
{
  char result; // al
  unsigned __int8 v2; // cl

  result = 0;
  v2 = *(_BYTE *)(nVal + 72);
  if ( v2 <= 6u
    || v2 == 13
    || v2 == 14
    || v2 == 29
    || v2 == 32
    || v2 == 33
    || v2 == 35
    || v2 == 36
    || v2 == 37
    || v2 == 38
    || v2 == 39
    || v2 == 44 )
  {
    result = 1;
  }
  if ( v2 == 14
    || v2 == 15
    || v2 == 16
    || v2 == 11
    || v2 == 12
    || v2 == 19
    || v2 == 20
    || v2 == 23
    || v2 == 24
    || v2 == 26
    || v2 == 27
    || v2 == 41
    || v2 == 42 )
  {
    return result | 2;
  }
  return result;
}

// 0x00422540
void RoleSystem::SetAnimFrame()
{
  g_ScriptSystemData.m_fD8BBC0 = 12.0 + 12.0;
}

// 0x00422740
void RoleSystem::ResetGlobalPos()
{
  g_fPalScript_C12B28 = 0.0;
  g_fPalScript_C12B2C = 0.0;
  g_fPalScript_C12B30 = 0.0;
}

// 0x004234A0
int RoleSystem::SetCameraMode(int nVal)
{
  if ( nVal == 1 )
    return old_sbh_page_manage((__old_sbh_page_struct *)g_pCameraCtrl, 1);
  else
    return old_sbh_page_manage((__old_sbh_page_struct *)g_pCameraCtrl, 0);
}

// 0x0042A010
void RoleSystem::ProcessAction()
{
  int *p_m_szModelName; // esi
  int RolePtr; // ebp
  int m_nSpawnParam2_low; // eax
  double v5; // st7
  double v6; // st6
  double v8; // st7
  unsigned __int8 v9; // c0
  unsigned __int8 v10; // c3
  double v11; // st7
  unsigned __int8 v13; // c0
  unsigned __int8 v14; // c3
  double v15; // st6
  RoleAtt *v16; // esi
  double v17; // st7
  RoleAtt *v18; // ebx
  __int64 v19; // rax
  RoleAtt *v20; // ecx
  float y; // ecx
  char m_nSpawnParam2; // al
  int *v23; // esi
  int v24; // ebx
  float v25; // edx
  int v26; // ebp
  float *v27; // esi
  long double v28; // st7
  long double v29; // st7
  long double v30; // st7
  long double v31; // st6
  int v32; // esi
  float *v33; // esi
  int v34; // ebx
  int v35; // ebp
  __int64 v36; // rax
  char v37; // cl
  int v38; // eax
  void *v39; // [esp+0x8] [ebp-0x25C]
  float v40; // [esp+0x18] [ebp-0x24C]
  int v41; // [esp+0x18] [ebp-0x24C]
  int v42; // [esp+0x18] [ebp-0x24C]
  float v43; // [esp+0x1C] [ebp-0x248]
  float v44; // [esp+0x1C] [ebp-0x248]
  float v45; // [esp+0x1C] [ebp-0x248]
  float v46; // [esp+0x1C] [ebp-0x248]
  float v47; // [esp+0x20] [ebp-0x244]
  float v48; // [esp+0x20] [ebp-0x244]
  float v49; // [esp+0x20] [ebp-0x244]
  float v50; // [esp+0x24] [ebp-0x240]
  float v51; // [esp+0x24] [ebp-0x240]
  struct gbVec3D v52; // [esp+0x28] [ebp-0x23C] BYREF
  gbOBBox pMatrix; // [esp+0x34] [ebp-0x230] BYREF
  int v54; // [esp+0x80] [ebp-0x1E4]
  struct gbAABBox v55; // [esp+0x84] [ebp-0x1E0] BYREF
  int base[2]; // [esp+0x9C] [ebp-0x1C8] BYREF
  float v57; // [esp+A4h] [ebp-0x1C0]
  float v58; // [esp+A8h] [ebp-0x1BC]
  float v59[15]; // [esp+ACh] [ebp-0x1B8] BYREF
  float v60; // [esp+E8h] [ebp-0x17C]
  float v61; // [esp+ECh] [ebp-0x178]
  float v62; // [esp+F0h] [ebp-0x174]
  float v63; // [esp+F4h] [ebp-0x170]
  float v64; // [esp+F8h] [ebp-0x16C]
  float v65; // [esp+FCh] [ebp-0x168]
  float v66; // [esp+0x100] [ebp-0x164]
  float v67; // [esp+0x104] [ebp-0x160]
  float v68; // [esp+0x108] [ebp-0x15C]
  float v69; // [esp+0x10C] [ebp-0x158]
  float v70; // [esp+0x124] [ebp-0x140]
  float v71; // [esp+0x128] [ebp-0x13C]
  float v72; // [esp+0x12C] [ebp-0x138]
  float v73; // [esp+0x130] [ebp-0x134]
  float v74; // [esp+0x134] [ebp-0x130]
  float v75; // [esp+0x138] [ebp-0x12C]
  float v76; // [esp+0x13C] [ebp-0x128]
  float v77; // [esp+0x140] [ebp-0x124]
  float v78; // [esp+0x144] [ebp-0x120]
  float v79; // [esp+0x148] [ebp-0x11C]
  float v80; // [esp+0x14C] [ebp-0x118]
  float v81; // [esp+0x150] [ebp-0x114]
  float v82; // [esp+0x168] [ebp-FCh]
  float v83; // [esp+0x16C] [ebp-F8h]
  float v84; // [esp+0x170] [ebp-F4h]
  float v85; // [esp+0x174] [ebp-F0h]
  float v86; // [esp+0x178] [ebp-ECh]
  float v87; // [esp+0x17C] [ebp-E8h]
  float v88; // [esp+0x180] [ebp-E4h]
  float v89; // [esp+0x184] [ebp-E0h]
  float v90; // [esp+0x188] [ebp-DCh]
  float v91; // [esp+0x18C] [ebp-D8h]
  float v92; // [esp+0x190] [ebp-D4h]
  float v93; // [esp+0x194] [ebp-D0h]
  float v94; // [esp+0x1AC] [ebp-B8h]
  float v95; // [esp+0x1B0] [ebp-B4h]
  float v96; // [esp+0x1B4] [ebp-B0h]
  float v97; // [esp+0x1B8] [ebp-ACh]
  float v98; // [esp+0x1BC] [ebp-A8h]
  float v99; // [esp+0x1C0] [ebp-A4h]
  float v100; // [esp+0x1C4] [ebp-A0h]
  float v101; // [esp+0x1C8] [ebp-0x9C]
  float v102; // [esp+0x1CC] [ebp-0x98]
  float v103; // [esp+0x1D0] [ebp-0x94]
  float v104; // [esp+0x1D4] [ebp-0x90]
  float v105; // [esp+0x1D8] [ebp-0x8C]
  float v106; // [esp+0x1F0] [ebp-0x74]
  float v107; // [esp+0x1F4] [ebp-0x70]
  float v108; // [esp+0x1F8] [ebp-0x6C]
  float v109; // [esp+0x1FC] [ebp-0x68]
  float v110; // [esp+0x200] [ebp-0x64]
  float v111; // [esp+0x204] [ebp-0x60]
  float v112; // [esp+0x208] [ebp-0x5C]
  float v113; // [esp+0x20C] [ebp-0x58]
  float v114; // [esp+0x210] [ebp-0x54]
  float v115; // [esp+0x214] [ebp-0x50]
  float v116; // [esp+0x218] [ebp-0x4C]
  float v117[6]; // [esp+0x21C] [ebp-0x48]
  Config v118; // [esp+0x234] [ebp-0x30] BYREF
  int v119; // [esp+0x260] [ebp-0x4]
  int v120; // [esp+0x268] [ebp+0x4]

  p_m_szModelName = &this->m_szModelName;
  if ( _strcmpi((const char *)&this->m_szModelName, "g01.cvd")
    && (LODWORD(this->m_fDirX) != 4 || _strcmpi((const char *)p_m_szModelName, a4_0)) )
  {
    ((Object3D *)this)->SetTransform((gbMatrix4 *)&pMatrix);
    RolePtr = ((RoleSystem *)*(RoleSystem **)&this->m_partyActor.m_pEquipAtt1[0]->Remark[10])->GetRolePtr(BYTE2(this->m_nSpawnParam2));
    m_nSpawnParam2_low = LOBYTE(this->m_nSpawnParam2);
    v54 = RolePtr;
    switch ( m_nSpawnParam2_low )
    {
      case 5:
      case 23:
        goto LABEL_14;
      case 7:
        v8 = flt_D8BEC4;
        if ( !(v9 | v10) )
        {
          pMatrix.xlen = v8 * 4.5 + pMatrix.xlen;
          v11 = pMatrix.zlen - flt_D8BEC4 * 2.5;
          goto LABEL_20;
        }
        pMatrix.xlen = pMatrix.xlen - v8 * 2.5;
        v5 = flt_D8BEC4 * 4.5;
        goto LABEL_19;
      case 11:
        if ( this->m_szModelPath != 1 )
          goto LABEL_21;
LABEL_14:
        v5 = flt_D8BEC4 * 2.5;
LABEL_17:
        v15 = v5 + pMatrix.xlen;
        goto LABEL_18;
      case 19:
        pMatrix.xlen = pMatrix.xlen - flt_D8BEC4 * 3.5;
        v5 = flt_D8BEC4 * 1.5;
        goto LABEL_19;
      case 22:
      case 34:
        v5 = flt_D8BEC4 * 1.5;
        if ( v13 | v14 )
        {
          v15 = pMatrix.xlen - v5;
LABEL_18:
          pMatrix.xlen = v15;
LABEL_19:
          v11 = v5 + pMatrix.zlen;
LABEL_20:
          pMatrix.zlen = v11;
        }
        else
        {
          v6 = v5 + pMatrix.xlen;
LABEL_11:
          pMatrix.xlen = v6;
          pMatrix.zlen = pMatrix.zlen - v5;
        }
LABEL_21:
        memset(&v55, 0, 12);
        ((gbOBBox *)&pMatrix)->GetAABBox(v55);
        v16 = (RoleAtt *)(__int64)((v55.max.x - *(float *)(RolePtr + 128)) / flt_D8BEC4);
        v17 = v55.min.x - *(float *)(RolePtr + 128);
        LODWORD(v52.y) = (__int64)((v55.max.z - *(float *)(RolePtr + 136)) / flt_D8BEC4);
        v18 = (RoleAtt *)(__int64)(v17 / flt_D8BEC4);
        v19 = (__int64)((v55.min.z - *(float *)(RolePtr + 136)) / flt_D8BEC4);
        v20 = v16;
        if ( (int)v16 >= (int)v18 )
          v20 = (RoleAtt *)(__int64)(v17 / flt_D8BEC4);
        this->m_partyActor.m_pEquipAtt2[0] = v20;
        if ( (int)v16 <= (int)v18 )
          v16 = v18;
        y = v52.y;
        this->m_partyActor.m_pEquipAtt2[2] = v16;
        *((float *)&v19 + 1) = y;
        if ( SLODWORD(y) >= (int)v19 )
          HIDWORD(v19) = v19;
        this->m_partyActor.m_pEquipAtt2[1] = (RoleAtt *)HIDWORD(v19);
        if ( SLODWORD(y) > (int)v19 )
          *(float *)&v19 = y;
        this->m_partyActor.m_pEquipAtt2[3] = (RoleAtt *)v19;
        if ( LOBYTE(this->m_nSpawnParam2) == 23 && ((UIScene *)"m15")->ProcessInput(a2) )
        {
          if ( !v120 )
          {
LABEL_32:
            ((RoleSystem *)this->m_partyActor.m_pEquipAtt1[0])->GetCurrentID((int *)this->m_partyActor.m_pEquipAtt2, (char)this->m_partyActor.m_pEquipAtt1[1]);
            return;
          }
          goto LABEL_42;
        }
        if ( LOBYTE(this->m_nSpawnParam2) == 22 && ((UIScene *)"M22")->ProcessInput(a3) )
        {
          if ( !v120 )
            goto LABEL_32;
          goto LABEL_42;
        }
        m_nSpawnParam2 = this->m_nSpawnParam2;
        if ( m_nSpawnParam2 == 37 || m_nSpawnParam2 == 38 || m_nSpawnParam2 == 42 )
        {
          memset(&v52, 0, sizeof(v52));
          ((gbMatrix4 *)&pMatrix)->Transform(&v52, 1);
          v34 = (__int64)((v52.x - *(float *)(RolePtr + 128)) / flt_D8BEC4);
          v35 = (__int64)((v52.z - *(float *)(RolePtr + 136)) / flt_D8BEC4);
          v36 = (__int64)(pMatrix.zlen / flt_D8BEC4);
          if ( (int)(__int64)(pMatrix.xlen / flt_D8BEC4) < (int)v36 )
            LODWORD(v36) = (__int64)(pMatrix.xlen / flt_D8BEC4);
          v37 = this->m_nSpawnParam2;
          v38 = (int)v36 / 2;
          if ( v37 == 38 )
            ++v38;
          if ( v37 == 42 )
            v38 = 3;
          if ( v120 )
            ((RoleSystem *)this->m_partyActor.m_pEquipAtt1[0])->ClearWaypointBuffer(v34, v35, v38, 255);
          else
            ((RoleSystem *)this->m_partyActor.m_pEquipAtt1[0])->ClearWaypointBuffer(v34, v35, v38, (char)this->m_partyActor.m_pEquipAtt1[1]);
        }
        else
        {
          if ( m_nSpawnParam2 == 11 )
          {
            if ( !v120 )
              goto LABEL_32;
LABEL_42:
            ((RoleSystem *)this->m_partyActor.m_pEquipAtt1[0])->GetCurrentID((int *)this->m_partyActor.m_pEquipAtt2, 255);
            return;
          }
          v23 = base;
          v24 = 6;
          do
          {
            v23 += 17;
            --v24;
          }
          while ( v24 );
          v43 = pMatrix.ylen * 0.5;
          v40 = pMatrix.xlen * -0.5;
          *(float *)base = v40;
          *(float *)&base[1] = v43;
          v59[5] = v40;
          v57 = pMatrix.zlen * 0.5;
          v59[13] = v40;
          v67 = v40;
          v76 = v40;
          v50 = pMatrix.xlen * 0.5;
          v58 = v50;
          v59[0] = v43;
          v59[2] = v50;
          v59[1] = v57;
          v61 = v50;
          v64 = v50;
          v70 = v40;
          v73 = v40;
          v79 = v40;
          v47 = pMatrix.ylen * -0.5;
          v59[3] = v47;
          v59[4] = v57;
          v59[6] = v47;
          v59[7] = v57;
          v59[14] = v43;
          v60 = pMatrix.zlen * -0.5;
          v62 = v43;
          v63 = v60;
          v65 = v47;
          v66 = v60;
          v68 = v47;
          v69 = v60;
          v71 = v43;
          v72 = v57;
          v74 = v43;
          v75 = v60;
          v77 = v47;
          v78 = v60;
          v80 = v47;
          v81 = v57;
          v25 = v50;
          v51 = 40000.0;
          v83 = v43;
          v84 = v57;
          v85 = v25;
          v88 = v25;
          v97 = v25;
          v86 = v43;
          v94 = v40;
          v103 = v40;
          v87 = v60;
          v82 = v25;
          v91 = v25;
          v89 = v47;
          v100 = v25;
          v106 = v40;
          v90 = v60;
          v109 = v25;
          v112 = v25;
          v92 = v47;
          v115 = v40;
          v41 = -1;
          v93 = v57;
          v26 = 0;
          v27 = v59;
          v95 = v43;
          v96 = v60;
          v98 = v43;
          v99 = v60;
          v101 = v43;
          v102 = v57;
          v104 = v43;
          v105 = v57;
          v107 = v47;
          v108 = v60;
          v110 = v47;
          v111 = v60;
          v113 = v47;
          v114 = v57;
          v116 = v47;
          v117[0] = v57;
          do
          {
            ((gbMatrix4 *)&pMatrix)->Transform((gbVec3D *)(v27 - 4), 4);
            v44 = fabs(*v27 - v27[3]);
            v48 = fabs(v27[3] - v27[6]);
            v28 = fabs(fabs(*(v27 - 3) - *v27) + v48 + v44);
            v49 = v28;
            if ( v28 < v51 )
            {
              v29 = *(v27 - 4) - *(v27 - 1);
              v52.x = fabs(*(v27 - 1) - v27[2]);
              v45 = fabs(v27[2] - v27[5]);
              v30 = fabs(v29) + v45 + v52.x;
              v31 = *(v27 - 2) - v27[1];
              v46 = fabs(v27[1] - v27[4]);
              v52.x = fabs(v27[4] - v27[7]);
              v52.x = fabs(v31) + v52.x + v46;
              if ( fabs(v30) > 0.05000000074505806 && fabs(v52.x) > 0.050000001 )
              {
                v41 = v26;
                v51 = v49;
              }
            }
            ++v26;
            v27 += 17;
          }
          while ( v26 < 6 );
          v32 = v41;
          if ( v41 == -1 )
            v32 = 0;
          ((Config *)&v118)->ResetField7();
          v119 = 0;
          v42 = 4;
          v33 = (float *)&base[17 * v32];
          do
          {
            ((Config *)&v118)->SetSlotValue((__int64)((*v33 - *(float *)(v54 + 128)) / flt_D8BEC4), (__int64)((v33[2] - *(float *)(v54 + 136)) / flt_D8BEC4));
            v33 += 3;
            --v42;
          }
          while ( v42 );
          if ( v120 )
            ((RoleSystem *)this->m_partyActor.m_pEquipAtt1[0])->BuildPathSegment((int *)&v118, 255);
          else
            ((RoleSystem *)this->m_partyActor.m_pEquipAtt1[0])->BuildPathSegment((int *)&v118, (char)this->m_partyActor.m_pEquipAtt1[1]);
          v119 = -1;
          todo_408BD0(v39);
        }
        break;
      case 26:
        goto LABEL_21;
      case 29:
      case 33:
        v5 = flt_D8BEC4 * 1.5;
        v6 = pMatrix.xlen - v5;
        goto LABEL_11;
      default:
        v5 = flt_D8BEC4 * 1.5;
        goto LABEL_17;
    }
  }
}

// 0x0042A950
BOOL RoleSystem::CheckScriptTrigger(gbVec3D *p)
{
  float m_fDirY; // ecx
  int RolePtr; // ebx
  int *v5; // ebp
  int v6; // ebx
  BOOL result; // eax
  int nVal; // [esp+0x14] [ebp-0x34]
  float pnVala; // [esp+0x18] [ebp-0x30]
  int *pnVal; // [esp+0x18] [ebp-0x30]
  float v11; // [esp+0x20] [ebp-0x28]
  float v12; // [esp+0x24] [ebp-0x24]
  float v13; // [esp+0x2C] [ebp-0x1C]
  float v14[2]; // [esp+0x30] [ebp-0x18] BYREF
  float v15; // [esp+0x38] [ebp-0x10]
  float v16; // [esp+0x3C] [ebp-0xC]
  int v17; // [esp+0x40] [ebp-0x8]
  float v18; // [esp+0x44] [ebp-0x4]

  v14[0] = 0.0;
  v14[1] = 0.0;
  m_fDirY = this->m_fDirY;
  v15 = 0.0;
  v16 = 0.0;
  v17 = 0;
  v18 = 0.0;
  (*(void ( **)(float, float *))(*(_DWORD *)LODWORD(m_fDirY) + 32))(COERCE_FLOAT(LODWORD(m_fDirY)), v14);
  pnVala = v16 + p->x;
  v11 = v18 + p->z;
  v12 = v14[0] + p->x;
  v13 = v15 + p->z;
  RolePtr = ((RoleSystem *)*(RoleSystem **)&this->m_partyActor.m_pEquipAtt1[0]->Remark[10])->GetRolePtr(BYTE2(this->m_nSpawnParam2));
  v5 = (int *)(__int64)((pnVala - *(float *)(RolePtr + 128)) / flt_D8BEC4);
  nVal = (__int64)((v11 - *(float *)(RolePtr + 136)) / flt_D8BEC4);
  pnVal = (int *)(__int64)((v12 - *(float *)(RolePtr + 128)) / flt_D8BEC4);
  v6 = (__int64)((v13 - *(float *)(RolePtr + 136)) / flt_D8BEC4);
  result = ((PalScriptMgr *)this)->CheckTileCollision(v5, nVal, p);
  if ( result )
  {
    result = ((PalScriptMgr *)this)->CheckTileCollision(pnVal, v6, p);
    if ( result )
    {
      result = ((PalScriptMgr *)this)->CheckTileCollision(v5, v6, p);
      if ( result )
        return ((PalScriptMgr *)this)->CheckTileCollision(pnVal, nVal, p);
    }
  }
  return result;
}

// 0x0042AD40
int RoleSystem::SetActionState(int nVal, char pData)
{
  int result; // eax
  RoleAtt *v5; // eax
  int v8; // [esp-0x10] [ebp-0x14]
this->m_partyActor.m_pEquipAtt1[0] = (RoleAtt *)nVal;
  LOBYTE(this->m_partyActor.m_pEquipAtt1[1]) = pData;
  if ( !_strcmpi((const char *)&this->m_szModelName, a3_0) )
    return 1;
  switch ( LOBYTE(this->m_nSpawnParam2) )
  {
    case 1:
    case 2:
    case 8:
    case 0xC:
    case 0x10:
    case 0x13:
    case 0x17:
    case 0x1A:
    case 0x1E:
    case 0x29:
    case 0x2A:
      goto LABEL_12;
    case 5:
    case 7:
      this->m_partyActor.m_dwMatMsg[0] = *(_DWORD *)&this->m_nSpawnFlags;
      ((RoleSystem *)_ESI)->ProcessAction();
      goto LABEL_5;
    case 0xB:
      ((RoleSystem *)_ESI)->ProcessAction();
      BYTE1(this->m_nSpawnData) = this->m_szModelPath == 1;
      return 1;
    case 0xD:
      ((RoleSystem *)_ESI)->ProcessAction();
      return 1;
    case 0x11:
      ((RoleSystem *)_ESI)->ProcessAction();
      BYTE1(this->m_nSpawnData) = this->m_szModelPath;
      return 1;
    case 0x16:
      ((RoleSystem *)_ESI)->ProcessAction();
      BYTE1(this->m_nSpawnData) = this->m_bSpawnByteA;
      return 1;
    case 0x18:
      return 1;
    case 0x19:
      if ( !this->m_szModelPath )
      {
LABEL_12:
        ((RoleSystem *)_ESI)->ProcessAction();
        BYTE1(this->m_nSpawnData) = 0;
      }
      return 1;
    case 0x1C:
      if ( this->m_szModelPath == 1 )
      {
        BYTE1(this->m_nSpawnData) = this->m_bActionPause;
        ((RoleSystem *)_ESI)->ProcessAction();
        if ( !this->m_bActionPause )
        {
          __asm
          {
            fld     dword ptr [esi+0x54]
            fsin
          }
          v5 = this->m_partyActor.m_pEquipAtt1[0];
          v8 = BYTE2(this->m_nSpawnParam2);
          __asm
          {
            fadd    _flt_1_0
            fmul    dword ptr [esi+0x0D8]
            fmul    _flt_0_5
            fstp    dword ptr [esi+0x2C]
          }
          *(float *)&this->m_childs.m_nSize = _ET1;
          ((RoleSystem *)*(RoleSystem **)&v5->Remark[10])->SetRoleParam(v8, (float *)&this->m_childs.capacity, 0, 0);
          // __asm { fstp    dword ptr [esi+0x2C] }
          *(float *)&this->m_childs.m_nSize = _ET1;
        }
      }
      return 1;
    case 0x1D:
    case 0x21:
    case 0x22:
    case 0x26:
    case 0x28:
      ((RoleSystem *)_ESI)->ProcessAction();
      BYTE1(this->m_nSpawnData) = 1;
      return 1;
    case 0x1F:
      if ( !_strcmpi(*(const char **)&this->m_partyActor.m_pEquipAtt1[0]->Remark[10], "m09") )
        ((RoleSystem *)_ESI)->SetTileTypeVisible(2, 0);
      return 1;
    case 0x24:
LABEL_5:
      BYTE1(this->m_nSpawnData) = 1;
      goto LABEL_6;
    case 0x25:
      ((PalScriptMgr *)_ESI)->LoadSceneGeometry(dword_D8BC38);
      return 1;
    default:
LABEL_6:
      result = 0;
      break;
  }
  return result;
}

// 0x0042B510
void RoleSystem::UpdateStateMode()
{
  int v2; // ebx
  int v3; // ebp
  RoleSystem *v4; // ecx
  RoleAtt *v5; // eax
  RoleSystem *v6; // edi
  int v7; // [esp+0x0] [ebp-0x14]
  int v8; // [esp+0x10] [ebp-0x4]

  if ( this->m_nStateMode )
  {
    if ( this->m_nStateMode == 2 )
    {
      v2 = 1;
      v3 = 0;
    }
    else
    {
      v2 = v8;
      v3 = v8;
    }
  }
  else
  {
    v2 = 0;
    v3 = 1;
  }
  if ( this->m_partyActor.m_pEquipAtt2[4] )
  {
    v4 = g_pRoleSystem;
    *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture = v2;
    ((RoleSystem *)v4)->SetMoveSpeed(0.0, 0, v7);
  }
  v5 = this->m_partyActor.m_pEquipAtt1[0];
  BYTE2(this->m_nSpawnParam2) = v2;
  v6 = *(RoleSystem **)&v5->Remark[10];
  this->m_partyActor.m_pEquipAtt1[0] = (RoleAtt *)((RoleSystem *)v6)->NotifyPathEnd(v3);

  this->m_partyActor.m_pEquipAtt1[0] = (RoleAtt *)((RoleSystem *)v6)->NotifyPathEnd(v2);

}

// 0x0042C0C0
int * RoleSystem::SetTileTypeVisible(int nTileType, int bVisible)
{
  int *result; // eax
  int i; // edi
  int v5; // ecx
  int j; // esi
  int v7; // ecx
  int k; // edi
  int v9; // ecx
  int m; // esi
  int v11; // ecx

  result = (int *)((RoleSystem *)*(RoleSystem **)&this->m_partyActor.m_pEquipAtt1[0]->Remark[10])->GetRolePtr(0);
  if ( bVisible )
  {
    for ( i = 0; i < result[39]; ++i )
    {
      v5 = result[38];
      for ( j = 0; j < v5; ++j )
      {
        v7 = result[40] + 8 * (j + i * v5);
        if ( *(unsigned __int8 *)(v7 + 5) == nTileType && *(_BYTE *)(v7 + 4) < 2u )
          *(_BYTE *)(v7 + 4) = 2;
        v5 = result[38];
      }
    }
  }
  else
  {
    for ( k = 0; k < result[39]; ++k )
    {
      v9 = result[38];
      for ( m = 0; m < v9; ++m )
      {
        v11 = result[40] + 8 * (m + k * v9);
        if ( *(unsigned __int8 *)(v11 + 5) == nTileType && *(_BYTE *)(v11 + 4) >= 2u )
          *(_BYTE *)(v11 + 4) = 0;
        v9 = result[38];
      }
    }
  }
  return result;
}

// 0x0042D9F0
int RoleSystem::ExecScriptDataCmd(int *p_DWORD)
{
  RoleAtt **v3; // ebx
  int v4; // edx
  int v5; // eax
  int v6; // eax
  RoleAtt *v7; // edi
  RoleAtt *v8; // ecx
  int result; // eax
  void *v10; // esi
  RoleAtt *v11; // eax
  float x; // eax
  float v13; // ecx
  RoleAtt *v14; // esi
  float v15; // edx
  unsigned int v16; // eax
  RoleAtt *v17; // eax
  float v18; // edx
  float v19; // ecx
  RoleAtt *v20; // edx
  int v21; // edi
  gbVec3D *RoleName; // eax
  gbVec3D *v23; // edi
  float y; // ecx
  float z; // eax
  RoleAtt *v26; // ecx
  float v27; // ecx
  float v28; // eax
  RoleAtt *v29; // ecx
  gbVec3D v30; // [esp+0xC] [ebp-0x5C] BYREF
  RoleAtt *v31; // [esp+0x18] [ebp-0x50]
  _DWORD v32[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v32);
  v3 = &this->m_partyActor.m_pEquipAtt2[5];
  LOBYTE(v32[0]) = 11;
  v4 = p_DWORD[1];
  v5 = p_DWORD[2];
  v32[3] = *p_DWORD;
  v32[5] = v5;
  v6 = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3);
  v32[4] = v4;
  if ( !v6
    || (v7 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2),
        v8 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 1),
        v7 == v8) )
  {
    v10 = operator new(0xFBCu);
    if ( v3[11] )
    {
      v16 = (unsigned int)v3[8];
      if ( v16 >= (unsigned int)v3[9] + 4 * (_DWORD)v3[10] - 4 )
      {
        v21 = ((int)(v16 - (_DWORD)v3[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)v3)->GetRoleName(2 * v21);
        v23 = (gbVec3D *)((char *)RoleName + 4 * v21);
        LODWORD(v23->x) = v10;
        ((gbVec3D *)&v30)->Copy((int)v3[3], RoleName);
        y = v30.y;
        v3[1] = (RoleAtt *)LODWORD(v30.x);
        z = v30.z;
        *((float *)v3 + 2) = y;
        v26 = v31;
        *((float *)v3 + 3) = z;
        v3[4] = v26;
        ((gbVec3D *)&v30)->Copy((int)v10, v23);
        v27 = v30.y;
        v3[5] = (RoleAtt *)LODWORD(v30.x);
        v28 = v30.z;
        *((float *)v3 + 6) = v27;
        v29 = v31;
        *((float *)v3 + 7) = v28;
        v3[8] = v29;
      }
      else
      {
        v17 = (RoleAtt *)(v16 + 4);
        v3[8] = v17;
        v17->id = (unsigned int)v10;
        ((gbVec3D *)&v30)->Copy((int)v10, (gbVec3D *)v3[8]);
        v18 = v30.y;
        v3[5] = (RoleAtt *)LODWORD(v30.x);
        v19 = v30.z;
        *((float *)v3 + 6) = v18;
        v20 = v31;
        *((float *)v3 + 7) = v19;
        v3[8] = v20;
      }
    }
    else
    {
      v3[10] = (RoleAtt *)2;
      v11 = (RoleAtt *)operator new(8u);
      v3[9] = v11;
      *(_DWORD *)&v11->type = v10;
      ((gbVec3D *)&v30)->Copy((int)v10 + 1976, (gbVec3D *)&v3[9]->type);
      x = v30.x;
      v13 = v30.y;
      v14 = v31;
      v15 = v30.z;
      v3[1] = (RoleAtt *)LODWORD(v30.x);
      *((float *)v3 + 2) = v13;
      *((float *)v3 + 3) = v15;
      v3[4] = v14;
      *((float *)v3 + 5) = x;
      *((float *)v3 + 6) = v13;
      *((float *)v3 + 7) = v15;
      v3[8] = v14;
    }
    v7 = v3[7];
    v3[7] = (RoleAtt *)&v7->Remark[70];
    if ( !v7 )
      goto LABEL_16;
    goto LABEL_15;
  }
  *((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2) = &v7->Remark[70];
  if ( &v7->Remark[70] != (char *)v8 )
  {
    if ( !v7 )
    {
LABEL_16:
      result = (int)&v3[11]->id + 1;
      v3[11] = (RoleAtt *)result;
      return result;
    }
LABEL_15:
    qmemcpy(v7, v32, 0x4Cu);
    goto LABEL_16;
  }
  if ( v7 )
    qmemcpy(v7, v32, 0x4Cu);
  ((ScriptVM *)v3)->GetString();
  result = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) + 1;
  *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) = result;
  return result;
}

// 0x0042DBD0
int RoleSystem::ExecScriptDataA()
{
  int v2; // eax
  RoleAtt **v3; // ebx
  RoleAtt *v4; // edi
  RoleAtt *v5; // ecx
  int result; // eax
  RoleAtt *v7; // esi
  RoleAtt *v8; // eax
  float x; // eax
  float v10; // edx
  float v11; // ecx
  RoleAtt *v12; // esi
  unsigned int v13; // eax
  RoleAtt *v14; // eax
  float v15; // eax
  float v16; // edx
  RoleAtt *v17; // eax
  int v18; // edi
  gbVec3D *RoleName; // eax
  RoleAtt *v20; // edi
  float y; // edx
  float z; // ecx
  RoleAtt *v23; // edx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  RoleAtt *v26; // [esp+0x18] [ebp-0x50]
  char v27[76]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry(v27);
  v2 = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3);
  v3 = &this->m_partyActor.m_pEquipAtt2[5];
  v27[0] = 12;
  if ( !v2
    || (v4 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2),
        v5 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 1),
        v4 == v5) )
  {
    v7 = (RoleAtt *)operator new(0xFBCu);
    if ( v3[11] )
    {
      v13 = (unsigned int)v3[8];
      if ( v13 >= (unsigned int)v3[9] + 4 * (_DWORD)v3[10] - 4 )
      {
        v18 = ((int)(v13 - (_DWORD)v3[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)v3)->GetRoleName(2 * v18);
        v20 = (RoleAtt *)(&RoleName->x + v18);
        v20->id = (unsigned int)v7;
        ((gbVec3D *)&v25)->Copy((int)v3[3], RoleName);
        y = v25.y;
        v3[1] = (RoleAtt *)LODWORD(v25.x);
        z = v25.z;
        *((float *)v3 + 2) = y;
        v23 = v26;
        *((float *)v3 + 3) = z;
        v3[4] = v23;
        v24 = v20->id + 4028;
        v3[5] = (RoleAtt *)v20->id;
        v3[6] = (RoleAtt *)v24;
        v3[7] = v7;
        v3[8] = v20;
      }
      else
      {
        v14 = (RoleAtt *)(v13 + 4);
        v3[8] = v14;
        v14->id = (unsigned int)v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)v3[8]);
        v15 = v25.y;
        v3[5] = (RoleAtt *)LODWORD(v25.x);
        v16 = v25.z;
        *((float *)v3 + 6) = v15;
        v17 = v26;
        *((float *)v3 + 7) = v16;
        v3[8] = v17;
      }
    }
    else
    {
      v3[10] = (RoleAtt *)2;
      v8 = (RoleAtt *)operator new(8u);
      v3[9] = v8;
      *(_DWORD *)&v8->type = v7;
      ((gbVec3D *)&v25)->Copy((int)&v7[2].Remark[266], (gbVec3D *)&v3[9]->type);
      x = v25.x;
      v10 = v25.z;
      v11 = v25.y;
      v12 = v26;
      v3[1] = (RoleAtt *)LODWORD(v25.x);
      *((float *)v3 + 2) = v11;
      *((float *)v3 + 3) = v10;
      v3[4] = v12;
      *((float *)v3 + 5) = x;
      *((float *)v3 + 6) = v11;
      *((float *)v3 + 7) = v10;
      v3[8] = v12;
    }
    v4 = v3[7];
    v3[7] = (RoleAtt *)&v4->Remark[70];
    if ( !v4 )
      goto LABEL_16;
    goto LABEL_15;
  }
  *((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2) = &v4->Remark[70];
  if ( &v4->Remark[70] != (char *)v5 )
  {
    if ( !v4 )
    {
LABEL_16:
      result = (int)&v3[11]->id + 1;
      v3[11] = (RoleAtt *)result;
      return result;
    }
LABEL_15:
    qmemcpy(v4, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( v4 )
    qmemcpy(v4, v27, 0x4Cu);
  ((ScriptVM *)v3)->GetString();
  result = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) + 1;
  *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) = result;
  return result;
}

// 0x0042DD80
int RoleSystem::ExecScriptDataB()
{
  int v2; // eax
  RoleAtt **v3; // ebx
  RoleAtt *v4; // edi
  RoleAtt *v5; // ecx
  int result; // eax
  RoleAtt *v7; // esi
  RoleAtt *v8; // eax
  float x; // eax
  float v10; // edx
  float v11; // ecx
  RoleAtt *v12; // esi
  unsigned int v13; // eax
  RoleAtt *v14; // eax
  float v15; // eax
  float v16; // edx
  RoleAtt *v17; // eax
  int v18; // edi
  gbVec3D *RoleName; // eax
  RoleAtt *v20; // edi
  float y; // edx
  float z; // ecx
  RoleAtt *v23; // edx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  RoleAtt *v26; // [esp+0x18] [ebp-0x50]
  char v27[76]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry(v27);
  v2 = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3);
  v3 = &this->m_partyActor.m_pEquipAtt2[5];
  v27[0] = 13;
  if ( !v2
    || (v4 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2),
        v5 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 1),
        v4 == v5) )
  {
    v7 = (RoleAtt *)operator new(0xFBCu);
    if ( v3[11] )
    {
      v13 = (unsigned int)v3[8];
      if ( v13 >= (unsigned int)v3[9] + 4 * (_DWORD)v3[10] - 4 )
      {
        v18 = ((int)(v13 - (_DWORD)v3[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)v3)->GetRoleName(2 * v18);
        v20 = (RoleAtt *)(&RoleName->x + v18);
        v20->id = (unsigned int)v7;
        ((gbVec3D *)&v25)->Copy((int)v3[3], RoleName);
        y = v25.y;
        v3[1] = (RoleAtt *)LODWORD(v25.x);
        z = v25.z;
        *((float *)v3 + 2) = y;
        v23 = v26;
        *((float *)v3 + 3) = z;
        v3[4] = v23;
        v24 = v20->id + 4028;
        v3[5] = (RoleAtt *)v20->id;
        v3[6] = (RoleAtt *)v24;
        v3[7] = v7;
        v3[8] = v20;
      }
      else
      {
        v14 = (RoleAtt *)(v13 + 4);
        v3[8] = v14;
        v14->id = (unsigned int)v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)v3[8]);
        v15 = v25.y;
        v3[5] = (RoleAtt *)LODWORD(v25.x);
        v16 = v25.z;
        *((float *)v3 + 6) = v15;
        v17 = v26;
        *((float *)v3 + 7) = v16;
        v3[8] = v17;
      }
    }
    else
    {
      v3[10] = (RoleAtt *)2;
      v8 = (RoleAtt *)operator new(8u);
      v3[9] = v8;
      *(_DWORD *)&v8->type = v7;
      ((gbVec3D *)&v25)->Copy((int)&v7[2].Remark[266], (gbVec3D *)&v3[9]->type);
      x = v25.x;
      v10 = v25.z;
      v11 = v25.y;
      v12 = v26;
      v3[1] = (RoleAtt *)LODWORD(v25.x);
      *((float *)v3 + 2) = v11;
      *((float *)v3 + 3) = v10;
      v3[4] = v12;
      *((float *)v3 + 5) = x;
      *((float *)v3 + 6) = v11;
      *((float *)v3 + 7) = v10;
      v3[8] = v12;
    }
    v4 = v3[7];
    v3[7] = (RoleAtt *)&v4->Remark[70];
    if ( !v4 )
      goto LABEL_16;
    goto LABEL_15;
  }
  *((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2) = &v4->Remark[70];
  if ( &v4->Remark[70] != (char *)v5 )
  {
    if ( !v4 )
    {
LABEL_16:
      result = (int)&v3[11]->id + 1;
      v3[11] = (RoleAtt *)result;
      return result;
    }
LABEL_15:
    qmemcpy(v4, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( v4 )
    qmemcpy(v4, v27, 0x4Cu);
  ((ScriptVM *)v3)->GetString();
  result = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) + 1;
  *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) = result;
  return result;
}

// 0x0042E870
int RoleSystem::ExecScriptDataIdx(int nVal)
{
  RoleAtt **v3; // ebx
  int v4; // eax
  RoleAtt *v5; // edi
  RoleAtt *v6; // ecx
  int result; // eax
  RoleAtt *v8; // esi
  RoleAtt *v9; // eax
  float x; // eax
  float v11; // ecx
  RoleAtt *v12; // esi
  float v13; // edx
  unsigned int v14; // eax
  RoleAtt *v15; // eax
  float v16; // edx
  float v17; // ecx
  RoleAtt *v18; // edx
  int v19; // edi
  gbVec3D *RoleName; // eax
  RoleAtt *v21; // edi
  float y; // ecx
  float z; // eax
  RoleAtt *v24; // ecx
  int v25; // ecx
  gbVec3D v26; // [esp+0xC] [ebp-0x5C] BYREF
  RoleAtt *v27; // [esp+0x18] [ebp-0x50]
  _DWORD v28[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v28);
  v3 = &this->m_partyActor.m_pEquipAtt2[5];
  v28[1] = nVal;
  LOBYTE(v28[0]) = 20;
  v4 = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3);
  v28[2] = 0;
  if ( !v4
    || (v5 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2),
        v6 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 1),
        v5 == v6) )
  {
    v8 = (RoleAtt *)operator new(0xFBCu);
    if ( v3[11] )
    {
      v14 = (unsigned int)v3[8];
      if ( v14 >= (unsigned int)v3[9] + 4 * (_DWORD)v3[10] - 4 )
      {
        v19 = ((int)(v14 - (_DWORD)v3[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)v3)->GetRoleName(2 * v19);
        v21 = (RoleAtt *)(&RoleName->x + v19);
        v21->id = (unsigned int)v8;
        ((gbVec3D *)&v26)->Copy((int)v3[3], RoleName);
        y = v26.y;
        v3[1] = (RoleAtt *)LODWORD(v26.x);
        z = v26.z;
        *((float *)v3 + 2) = y;
        v24 = v27;
        *((float *)v3 + 3) = z;
        v3[4] = v24;
        v25 = v21->id + 4028;
        v3[5] = (RoleAtt *)v21->id;
        v3[6] = (RoleAtt *)v25;
        v3[7] = v8;
        v3[8] = v21;
      }
      else
      {
        v15 = (RoleAtt *)(v14 + 4);
        v3[8] = v15;
        v15->id = (unsigned int)v8;
        ((gbVec3D *)&v26)->Copy((int)v8, (gbVec3D *)v3[8]);
        v16 = v26.y;
        v3[5] = (RoleAtt *)LODWORD(v26.x);
        v17 = v26.z;
        *((float *)v3 + 6) = v16;
        v18 = v27;
        *((float *)v3 + 7) = v17;
        v3[8] = v18;
      }
    }
    else
    {
      v3[10] = (RoleAtt *)2;
      v9 = (RoleAtt *)operator new(8u);
      v3[9] = v9;
      *(_DWORD *)&v9->type = v8;
      ((gbVec3D *)&v26)->Copy((int)&v8[2].Remark[266], (gbVec3D *)&v3[9]->type);
      x = v26.x;
      v11 = v26.y;
      v12 = v27;
      v13 = v26.z;
      v3[1] = (RoleAtt *)LODWORD(v26.x);
      *((float *)v3 + 2) = v11;
      *((float *)v3 + 3) = v13;
      v3[4] = v12;
      *((float *)v3 + 5) = x;
      *((float *)v3 + 6) = v11;
      *((float *)v3 + 7) = v13;
      v3[8] = v12;
    }
    v5 = v3[7];
    v3[7] = (RoleAtt *)&v5->Remark[70];
    if ( !v5 )
      goto LABEL_16;
    goto LABEL_15;
  }
  *((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2) = &v5->Remark[70];
  if ( &v5->Remark[70] != (char *)v6 )
  {
    if ( !v5 )
    {
LABEL_16:
      result = (int)&v3[11]->id + 1;
      v3[11] = (RoleAtt *)result;
      return result;
    }
LABEL_15:
    qmemcpy(v5, v28, 0x4Cu);
    goto LABEL_16;
  }
  if ( v5 )
    qmemcpy(v5, v28, 0x4Cu);
  ((ScriptVM *)v3)->GetString();
  result = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) + 1;
  *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) = result;
  return result;
}

// 0x0042EA30
int RoleSystem::ExecScriptDataC()
{
  int v2; // eax
  RoleAtt **v3; // ebx
  RoleAtt *v4; // edi
  RoleAtt *v5; // ecx
  int result; // eax
  RoleAtt *v7; // esi
  RoleAtt *v8; // eax
  float x; // eax
  float v10; // edx
  float v11; // ecx
  RoleAtt *v12; // esi
  unsigned int v13; // eax
  RoleAtt *v14; // eax
  float v15; // eax
  float v16; // edx
  RoleAtt *v17; // eax
  int v18; // edi
  gbVec3D *RoleName; // eax
  RoleAtt *v20; // edi
  float y; // edx
  float z; // ecx
  RoleAtt *v23; // edx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  RoleAtt *v26; // [esp+0x18] [ebp-0x50]
  char v27[76]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry(v27);
  v2 = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3);
  v3 = &this->m_partyActor.m_pEquipAtt2[5];
  v27[0] = 21;
  if ( !v2
    || (v4 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2),
        v5 = (RoleAtt *)*((_DWORD *)&this->m_partyActor.m_nAnimFrame + 1),
        v4 == v5) )
  {
    v7 = (RoleAtt *)operator new(0xFBCu);
    if ( v3[11] )
    {
      v13 = (unsigned int)v3[8];
      if ( v13 >= (unsigned int)v3[9] + 4 * (_DWORD)v3[10] - 4 )
      {
        v18 = ((int)(v13 - (_DWORD)v3[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)v3)->GetRoleName(2 * v18);
        v20 = (RoleAtt *)(&RoleName->x + v18);
        v20->id = (unsigned int)v7;
        ((gbVec3D *)&v25)->Copy((int)v3[3], RoleName);
        y = v25.y;
        v3[1] = (RoleAtt *)LODWORD(v25.x);
        z = v25.z;
        *((float *)v3 + 2) = y;
        v23 = v26;
        *((float *)v3 + 3) = z;
        v3[4] = v23;
        v24 = v20->id + 4028;
        v3[5] = (RoleAtt *)v20->id;
        v3[6] = (RoleAtt *)v24;
        v3[7] = v7;
        v3[8] = v20;
      }
      else
      {
        v14 = (RoleAtt *)(v13 + 4);
        v3[8] = v14;
        v14->id = (unsigned int)v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)v3[8]);
        v15 = v25.y;
        v3[5] = (RoleAtt *)LODWORD(v25.x);
        v16 = v25.z;
        *((float *)v3 + 6) = v15;
        v17 = v26;
        *((float *)v3 + 7) = v16;
        v3[8] = v17;
      }
    }
    else
    {
      v3[10] = (RoleAtt *)2;
      v8 = (RoleAtt *)operator new(8u);
      v3[9] = v8;
      *(_DWORD *)&v8->type = v7;
      ((gbVec3D *)&v25)->Copy((int)&v7[2].Remark[266], (gbVec3D *)&v3[9]->type);
      x = v25.x;
      v10 = v25.z;
      v11 = v25.y;
      v12 = v26;
      v3[1] = (RoleAtt *)LODWORD(v25.x);
      *((float *)v3 + 2) = v11;
      *((float *)v3 + 3) = v10;
      v3[4] = v12;
      *((float *)v3 + 5) = x;
      *((float *)v3 + 6) = v11;
      *((float *)v3 + 7) = v10;
      v3[8] = v12;
    }
    v4 = v3[7];
    v3[7] = (RoleAtt *)&v4->Remark[70];
    if ( !v4 )
      goto LABEL_16;
    goto LABEL_15;
  }
  *((_DWORD *)&this->m_partyActor.m_nAnimFrame + 2) = &v4->Remark[70];
  if ( &v4->Remark[70] != (char *)v5 )
  {
    if ( !v4 )
    {
LABEL_16:
      result = (int)&v3[11]->id + 1;
      v3[11] = (RoleAtt *)result;
      return result;
    }
LABEL_15:
    qmemcpy(v4, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( v4 )
    qmemcpy(v4, v27, 0x4Cu);
  ((ScriptVM *)v3)->GetString();
  result = *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) + 1;
  *((_DWORD *)&this->m_partyActor.m_pParticleData + 3) = result;
  return result;
}

// 0x0044B470
int RoleSystem::ProcessWaypoint()
{
  int todo_078; // edx
  float m_fDirY; // ecx
  int todo_074; // eax
  int v5; // edx
  int v6; // edx
  char *m_pPathCurrent; // ecx
  char *v9; // [esp+0x1C] [ebp-0x20]
  int v10; // [esp+0x20] [ebp-0x1C]
  char *v11; // [esp+0x24] [ebp-0x18]
  int v12; // [esp+0x28] [ebp-0x14]
  char *v13; // [esp+0x2C] [ebp-0x10]
  int v14; // [esp+0x30] [ebp-0xC]
  char *v15; // [esp+0x34] [ebp-0x8]
  int v16; // [esp+0x38] [ebp-0x4]

  *((_DWORD *)this + 1853) = 0;
  *((_BYTE *)this + 7416) = 0;
  (*(void ( **)(int *, int))this->m_nPathField7C)(&this->m_nPathField7C, 1);
  todo_078 = this->_todo_078;
  m_fDirY = this->m_fDirY;
  v10 = LODWORD(this->m_fDirZ) + 32;
  todo_074 = this->_todo_074;
  v9 = (char *)(LODWORD(m_fDirY) - 10);
  v12 = v10 + todo_078;
  v11 = (char *)(LODWORD(m_fDirY) - 10 + todo_074);
  sub_445FA0(&this->m_partyActor.m_fAnimDelta);
  (*(void ( **)(float *, int))LODWORD(this->m_partyActor.m_fAnimDelta))(&this->m_partyActor.m_fAnimDelta, 1);
  v14 = v10 + 1;
  v13 = v9 + 1;
  v15 = v9 + 87;
  v16 = v12 - 1;
  sub_445FA0(&this->m_partyActor.m_nCachedB);
  (**(void ( ***)(_BYTE *, int))&this->m_partyActor.m_nCachedB)(&this->m_partyActor.m_nCachedB, 1);
  v5 = this->_todo_078;
  v10 = v12;
  v12 += v5;
  sub_445FA0(&this->m_fRotAxisZ);
  (*(void ( **)(float *, int))LODWORD(this->m_fRotAxisZ))(&this->m_fRotAxisZ, 1);
  v14 = v10 + 1;
  v13 = v9 + 1;
  v15 = v9 + 87;
  v16 = v12 - 1;
  sub_445FA0(&this->m_partyActor.m_nMatrixParam);
  (*(void ( **)(int *, int))this->m_partyActor.m_nMatrixParam)(
    &this->m_partyActor.m_nMatrixParam,
    1);
  v6 = this->_todo_078;
  v10 = v12;
  v12 += v6;
  sub_445FA0(&this->m_teamSlots[18]);
  (*(void ( **)(int *, int))this->m_teamSlots[18])(&this->m_teamSlots[18], 1);
  v14 = v10 + 1;
  v13 = v9 + 1;
  v15 = v9 + 87;
  v16 = v12 - 1;
  sub_445FA0(&this->m_partyActor.m_vecRot.z);
  (*(void ( **)(float *, int))LODWORD(this->m_partyActor.m_vecRot.z))(&this->m_partyActor.m_vecRot.z, 1);
  m_pPathCurrent = this->m_pPathCurrent;
  v10 = v12;
  v9 = m_pPathCurrent;
  v12 += 11;
  v11 = m_pPathCurrent + 68;
  sub_445FA0(&this->m_vecPosArray.y);
  (*(void ( **)(float *, int))LODWORD(this->m_vecPosArray.y))(&this->m_vecPosArray.y, 1);
  return this->ShowWindow(1);
}

// 0x0044CD90
int RoleSystem::InitUICtrlArray()
{
  LPCSTR *v2; // ebp
  UIStatic *v3; // esi
  int v4; // edi
  int v5; // edx
  void *v6; // eax
  unsigned int v7; // ecx
  UIStatic *v8; // edx
  int v9; // eax
  int v10; // ecx
  int v12; // [esp+0x10] [ebp-0x14]
  void *v13; // [esp+0x14] [ebp-0x10] BYREF
  unsigned int v14; // [esp+0x18] [ebp-0xC]
  int v15; // [esp+0x1C] [ebp-0x8]
  int v16; // [esp+0x20] [ebp-0x4]

  v13 = 0;
  v14 = 0;
  v15 = 128;
  v16 = 128;
  ((UIEmote *)this)->InitParticleSlots();
  v2 = &off_59DD80;
  v3 = (UIStatic *)((char *)this + 8416);
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD, vtbl_0056AE2C **, RoleSystem *))v3->__vftable->Create)(v3, 0, &v13, this);
    if ( (int)v2 < (int)&off_59DDA0 )
    {
      ((UIStatic *)v3)->CreateFromTemplate();
    }
    else
    {
      v4 = rand() & 7;
      ((UIStatic *)v3)->CreateFromTemplate();
      v3[1].m_rect.top = *((_DWORD *)this + 52 * v4 + 2147);
      v3[1].m_rect.right = *((_DWORD *)this + 52 * v4 + 2148);
    }
    *(float *)&v3[1].m_pfather = (float)(rand() % 255);
    ++v2;
    v5 = rand() % 10;
    v6 = v13;
    v7 = v14;
    v12 = v5 + 10;
    v8 = v3 + 1;
    v3 = (UIStatic *)((char *)v3 + 208);
    *(float *)&v3[-1].m_disablepicInfo = (double)v12 * 0.1;
    LOBYTE(v3[-1].m_pbk2) = 1;
// [VFTABLE] v8->__vftable = v6;
    v9 = v15;
    v8->m_fontcolor.Color = v7;
    v10 = v16;
    v8->m_wndcolor.Color = v9;
    v8->m_id = (void *)v10;
  }
  while ( (int)v2 < (int)&off_59DDA8 );
  return this->InitRandomParticles();
}

// 0x0044CEC0
int RoleSystem::InitDefaultPositions()
{
  float *p_z; // eax
  int v2; // edx

  p_z = &this->m_partyActor.m_vecLocalPos.z;
  v2 = 22;
  do
  {
    *((_DWORD *)p_z + 1) = 298;
    *(_DWORD *)p_z = 758;
    p_z[4] = 758.0;
    p_z += 52;
    --v2;
  }
  while ( v2 );
  *(_DWORD *)&this->m_partyActor.m_nActionParam = 256;
  this->m_partyActor.m_nActionState = 105;
  this->m_partyActor.m_dwMatMsg[1] = 256;
  this->m_partyActor.m_dwMatMsg[2] = 64;
  *(&this->m_partyActor.m_nAnimCounter + 7) = 256;
  *(&this->m_partyActor.m_nAnimCounter + 8) = 256;
  this->m_teamSlots[108] = 256;
  this->m_teamSlotsB[91] = 256;
  this->m_teamSlotsB[195] = 256;
  this->m_configData[34] = 256;
  *(int *)((char *)&this->m_partyUI3._todo_05C + 43) = 256;
  this->m_FrameA.m_pbktex = (gbTexture *)128;
  this->m_nActiveRole = 64;
  this->m_teamSlots[4] = 128;
  this->m_teamSlots[5] = 64;
  this->m_teamSlots[56] = 128;
  this->m_teamSlots[57] = 64;
  this->m_teamSlots[109] = 128;
  this->m_teamSlots[160] = 590;
  this->m_teamSlots[161] = 128;
  this->m_teamSlots[212] = 128;
  this->m_teamSlots[213] = 64;
  this->m_teamSlots[264] = 64;
  this->m_teamSlots[265] = 32;
  this->m_StaticSlotArray.m_rect.left = 512;
  this->m_StaticSlotArray.m_rect.top = 128;
  this->m_teamSlotsB[39] = 128;
  this->m_teamSlotsB[40] = 64;
  this->m_teamSlotsB[92] = 64;
  this->m_teamSlotsB[143] = 128;
  this->m_teamSlotsB[144] = 64;
  this->m_teamSlotsB[196] = 128;
  this->m_configData[35] = 128;
  this->m_configData[86] = 512;
  this->m_configData[87] = 128;
  *(int *)((char *)&this->m_partyUI3._todo_05C + 47) = 128;
  return 128;
}

// 0x0044D380
int RoleSystem::InitRandomParticles()
{
  DWORD Time; // eax
  char *v3; // esi
  int v4; // ebp
  int result; // eax
  int v6; // [esp+0xC] [ebp-0x4]

  Time = timeGetTime();
  CRT_set_new_handler(Time);
  v3 = (char *)this + 8588;
  v4 = 10;
  do
  {
    *((_DWORD *)v3 - 4) = rand() % 40 + 70;
    v6 = rand() % 500 + 150;
    *((_DWORD *)v3 - 5) = v6;
    *((float *)v3 - 1) = (float)v6;
    *((_DWORD *)v3 - 3) = *(_DWORD *)v3 + *((_DWORD *)v3 - 5);
    *((_DWORD *)v3 - 2) = *((_DWORD *)v3 - 4) + *((_DWORD *)v3 + 1);
    *((float *)v3 + 2) = (double)(rand() % 16) * 0.1 + 1.0;
    *((float *)v3 + 3) = (float)(rand() % 255);
    *((float *)v3 + 4) = (double)(rand() % 10 + 10) * 0.1;
    v3[20] = 1;
    result = sub_445FA0(v3 - 172);
    v3 += 208;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x00531D20
int RoleSystem::ctor_1D20()
{
  this->m_partyActor.m_actarray[12] = 0;
  *(_DWORD *)&this->m_partyActor.m_actarray[8] = 0;
  *(_DWORD *)&this->m_partyActor.m_actarray[4] = 0;
  sub_4422E0(&this->m_partyActor.m_pact);
  sub_4422E0(&this->m_nRoleCount);
  *((_BYTE *)this + 4536) = 0;
  *((_DWORD *)this + 1133) = 0;
  *((_DWORD *)this + 1132) = 0;
  ((ARC_PlayerAtt *)((char *)this + 4540))->Refresh();
  ((ARC_PlayerAtt *)((char *)this + 5908))->Refresh();
  sub_4422E0((char *)this + 7280);
  sub_4422E0((char *)this + 7432);
  *((_BYTE *)this + 7592) = 0;
  *((_DWORD *)this + 1897) = 0;
  *((_DWORD *)this + 1896) = 0;
  this->m_FrameA.m_pbktex = 0;
  *((_BYTE *)this + 7598) = 1;
  return (int)this;
}

// 0x00531E70
void RoleSystem::ctor()
{
  ((UIFrameWnd *)((char *)this + 7432))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 7280))->UIFrameWnd::_UIFrameWnd();
  ((UIRoleDialog *)((char *)this + 5908))->_UIRoleDialog();
  ((UIRoleDialog *)((char *)this + 4540))->_UIRoleDialog();
  ((UIFrameWnd *)&this->m_nRoleCount)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_partyActor.m_pact)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00531F50
int RoleSystem::InitAllSystems()
{
  int v1; // ebx
  gbActor *m_pact; // eax
  int *p_m_bcreateok; // eax
  float *p_m_fInterpEnd; // ecx
  int v6; // edx
  int m_nRoleCount; // eax
  PtrArray *p_m_childs; // edi
  UIStatic *v9; // edi
  int i; // ebx
  int v11; // edx
  int result; // eax
  int v13; // [esp+0x2C] [ebp-0x60] BYREF
  int v14; // [esp+0x30] [ebp-0x5C]
  int v15; // [esp+0x34] [ebp-0x58]
  int v16; // [esp+0x38] [ebp-0x54]
  int v17; // [esp+0x3C] [ebp-0x50] BYREF
  int v18; // [esp+0x40] [ebp-0x4C]
  int v19; // [esp+0x44] [ebp-0x48]
  int v20; // [esp+0x48] [ebp-0x44]
  _DWORD v21[4]; // [esp+0x4C] [ebp-0x40] BYREF
  _DWORD v22[4]; // [esp+0x5C] [ebp-0x30] BYREF
  int nVal[4]; // [esp+0x6C] [ebp-0x20] BYREF
  int v24[4]; // [esp+0x7C] [ebp-0x10] BYREF

  v1 = 0;
  this->m_fStateY = 0.0;
  this->m_fStateX = 0.0;
  *(_DWORD *)&this->m_nStateMode = 800;
  this->m_nTimerDuration = 600;
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, 800, this->m_nTimerDuration, 0);
  m_pact = this->m_partyActor.m_pact;
  v22[1] = 200;
  v22[0] = 300;
  v22[2] = 556;
  v22[3] = 328;
  ((void ( *)(gbActor **, int, _DWORD *, RoleSystem *))m_pact->children.m_Tail)(
    &this->m_partyActor.m_pact,
    10,
    v22,
    this);
  ((UIScene *)&this->m_partyActor.m_pact)->SetShow(1);
  ((void ( *)(gbActor **, _DWORD))this->m_partyActor.*((_DWORD *)m_pact))(&this->m_partyActor.m_pact, 0);
  LOBYTE(this->m_partyActor.m_vecTargetPos.z) = 0;
  p_m_bcreateok = &this->m_FrameA.m_bcreateok;
  p_m_fInterpEnd = &this->m_partyActor.m_fInterpEnd;
  v6 = 3;
  do
  {
    *(_BYTE *)p_m_fInterpEnd = 0;
    *p_m_bcreateok++ = 0;
    p_m_fInterpEnd += 64;
    --v6;
  }
  while ( v6 );
  m_nRoleCount = this->m_nRoleCount;
  this->m_FrameA.m_bfocus = 0;
  v18 = 0;
  v17 = 681;
  v19 = 800;
  v20 = 92;
  (*(void ( **)(int *, char *, int *, RoleSystem *))(m_nRoleCount + 16))(
    &this->m_nRoleCount,
    &byte_ABC00B,
    &v17,
    this);
  ((UIStatic *)&this->m_nRoleCount)->CreateFromTemplate();
  p_m_childs = &this->_embed_UIWnd_624.m_childs;
  v13 = v17 + 48;
  v14 = v18 + 16;
  v15 = v17 + 80;
  v16 = v18 + 40;
  do
  {
    (*((void ( **)(PtrArray *, char *, int *, RoleSystem *))p_m_childs->m_pData + 4))(
      p_m_childs,
      &byte_ABC00C,
      &v13,
      this);
    (*(void ( **)(PtrArray *, _DWORD))p_m_childs->m_pData)(p_m_childs, 0);
    sprintf((char *const)&this->m_fDirZ, "SubGame\\Appraise\\Number\\%d.tga", v1);
    ((UIStatic *)p_m_childs)->CreateFromTemplate();
    ++v1;
    p_m_childs = (PtrArray *)((char *)p_m_childs + 152);
  }
  while ( v1 < 10 );
  v9 = (UIStatic *)&this->m_teamSlotsB[43];
  v14 = v16;
  v16 += 24;
  for ( i = 0; i < 10; ++i )
  {
// [VFTABLE] ((void ( *)(UIStatic *, char *, int *, RoleSystem *))v9->__vftable->Create)(v9, &byte_ABC00D, &v13, this);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v9->__vftable->ShowWindow)(v9, 0);
    sprintf((char *const)&this->m_fDirZ, "SubGame\\Appraise\\Number\\%d.tga", i);
    ((UIStatic *)v9++)->CreateFromTemplate();
  }
  v11 = *((_DWORD *)this + 1820);
  *((_BYTE *)this + 7277) = 0;
  v21[1] = 200;
  v21[0] = 644;
  v21[2] = 700;
  v21[3] = 264;
  (*(void ( **)(char *, char *, _DWORD *, RoleSystem *))(v11 + 16))(
    (char *)this + 7280,
    &byte_AABC03,
    v21,
    this);
  ((UIStatic *)((char *)this + 7280))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 1820))((char *)this + 7280, 0);
  (*(void ( **)(char *, int *, _DWORD *, RoleSystem *))(*((_DWORD *)this + 1858) + 16))(
    (char *)this + 7432,
    dword_AABC04,
    v21,
    this);
  ((UIStatic *)((char *)this + 7432))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 1858))((char *)this + 7432, 0);
  nVal[1] = 221;
  nVal[0] = 320;
  nVal[2] = 480;
  nVal[3] = 411;
  ((ARC_PlayerAtt *)((char *)this + 4540))->Create((int)&word_ABC00E, (int)nVal);
  ((UIItem *)((char *)this + 4540))->SetData(31);
  v24[1] = 260;
  v24[0] = 186;
  v24[2] = 614;
  v24[3] = 388;
  ((ARC_PlayerAtt *)((char *)this + 5908))->Create(180146190, (int)v24);
  ((UIItem *)((char *)this + 5908))->SetData(31);
  sprintf(
    (char *const)&this->m_fDirZ,
    "%s\\n%s\\n%s\\n%s",
    (const char *)dword_DD313C,
    (const char *)dword_DD323C,
    (const char *)dword_DD333C,
    (const char *)dword_DD343C);
  ((UICaption *)((char *)this + 6364))->SetEnable((int)&this->m_fDirZ, 0);
  result = ((UIRoleSelect *)((char *)this + 5908))->SetByte(1);
  *((_BYTE *)this + 7276) = 0;
  *((_DWORD *)this + 1128) = 59;
  *((_BYTE *)this + 4524) = 0;
  this->m_FrameA.m_pbktex = 0;
  return result;
}

// 0x00532360
int RoleSystem::ApplyRotationAxis(int nVal, char pData)
{
  int m_bfocus; // ecx
  int result; // eax
  int *p_m_bcreateok; // edx
  const char *v7; // edi
  CScreenMode *Instance; // eax
  const void *v9; // [esp-0xC] [ebp-0x18]

  m_bfocus = this->m_FrameA.m_bfocus;
  *((_BYTE *)this + 7597) = pData;
  result = 0;
  if ( m_bfocus <= 0 )
  {
LABEL_5:
    v7 = (const char *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal) + 4);
    sprintf((char *const)&this->m_fDirZ, "%s%s", byte_DCD03C, v7);
    ((InputSystem *)&this->m_fDirZ)->ProcessFrame();
    v9 = off_5F7790;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v9, 1);
    lstrcpyA((LPSTR)&this->m_partyActor.m_fInterpEnd + 256 * this->m_FrameA.m_bfocus, v7);
    *(&this->m_FrameA.m_bcreateok + this->m_FrameA.m_bfocus) = nVal;
    result = this->m_FrameA.m_bfocus + 1;
    this->m_FrameA.m_bfocus = result;
  }
  else
  {
    p_m_bcreateok = &this->m_FrameA.m_bcreateok;
    while ( *p_m_bcreateok != nVal )
    {
      ++result;
      ++p_m_bcreateok;
      if ( result >= m_bfocus )
        goto LABEL_5;
    }
  }
  return result;
}

// 0x00532410
int RoleSystem::ShowHideUI(char pData)
{
  int *v2; // ebp
  int v4; // eax
  int m_bfocus; // eax
  int v6; // ebp
  int *p_m_bcreateok; // ebx
  char v8; // al
  float *p_m_fDirZ; // ebx
  int *v10; // edi
  int v11; // ebx
  int result; // eax
  int *v13; // [esp-0x4] [ebp-0x224]
  const CHAR *lpString2; // [esp+0xC] [ebp-0x214]
  int v15; // [esp+0x10] [ebp-0x210] BYREF
  int v16; // [esp+0x14] [ebp-0x20C]
  int SkillNum; // [esp+0x18] [ebp-0x208]
  int v18; // [esp+0x1C] [ebp-0x204]
  CHAR String1[253]; // [esp+0x20] [ebp-0x200] BYREF
  __int16 v20; // [esp+0x11D] [ebp-0x103]
  char v21; // [esp+0x11F] [ebp-0x101]
  CHAR String2[253]; // [esp+0x120] [ebp-0x100] BYREF
  __int16 v23; // [esp+0x21D] [ebp-0x3]
  char v24; // [esp+0x21F] [ebp-0x1]

  memset(String1, 0, sizeof(String1));
  v20 = 0;
  v21 = 0;
  memset(String2, 0, sizeof(String2));
  v23 = 0;
  v24 = 0;
  v4 = *((_DWORD *)this + 1128);
  v18 = 100 * this->m_FrameA.m_bfocus + 30 * v4;
  if ( v4 > 0 && pData )
  {
    v13 = v2;
    sprintf(
      (char *const)&this->m_fDirZ,
      "\\n    %s%s\\n\\n    %s\\n",
      (const char *)dword_DD293C,
      (const char *)dword_DCEF3C,
      (const char *)dword_DCF13C);
    m_bfocus = this->m_FrameA.m_bfocus;
    v6 = 0;
    String1[0] = 0;
    if ( m_bfocus > 0 )
    {
      p_m_bcreateok = &this->m_FrameA.m_bcreateok;
      lpString2 = (const CHAR *)&this->m_partyActor.m_fInterpEnd;
      do
      {
        v16 = 0;
        SkillNum = 0;
        v15 = *p_m_bcreateok;
        SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v15);
        v8 = *((_BYTE *)this + 7597);
        v16 = 1;
        if ( v8 )
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&v15, v13);
        lstrcatA(String1, asc_5C9190);
        lstrcatA(String1, lpString2);
        lstrcatA(String1, aN);
        ++v6;
        ++p_m_bcreateok;
        lpString2 += 256;
      }
      while ( v6 < this->m_FrameA.m_bfocus );
    }
    p_m_fDirZ = &this->m_fDirZ;
    if ( lstrlenA(String1) > 0 )
    {
      lstrcatA((LPSTR)&this->m_fDirZ, String1);
    }
    else
    {
      lstrcatA((LPSTR)&this->m_fDirZ, asc_5F9D04);
      lstrcatA((LPSTR)&this->m_fDirZ, byte_DC7D3C);
    }
    sprintf(String2, "\\n    %s %d", (const char *)dword_DCF33C, v18);
    lstrcatA((LPSTR)p_m_fDirZ, String2);
    ((UICaption *)((char *)this + 4996))->SetEnable((int)p_m_fDirZ, 0);
  }
  else
  {
    sprintf(
      (char *const)&this->m_fDirZ,
      "\\n    %s%s\\n\\n    %s",
      (const char *)dword_DD293C,
      (const char *)dword_DCF03C,
      (const char *)dword_DCF13C);
    lstrcatA((LPSTR)&this->m_fDirZ, "\\n       ");
    lstrcatA((LPSTR)&this->m_fDirZ, byte_DC7D3C);
    sprintf(String2, "\\n    %s %d", (const char *)dword_DCF33C, 0);
    lstrcatA((LPSTR)&this->m_fDirZ, String2);
    ((UICaption *)((char *)this + 4996))->SetEnable((int)&this->m_fDirZ, 0);
  }
  ((UIRoleSelect *)((char *)this + 4540))->SetByte(1);
  (*(void ( **)(int *, _DWORD))this->m_nRoleCount)(&this->m_nRoleCount, 0);
  v10 = &this->m_teamSlotsB[43];
  v11 = 10;
  do
  {
    (*(void ( **)(int *, _DWORD))*(v10 - 380))(v10 - 380, 0);
    (*(void ( **)(int *, _DWORD))*v10)(v10, 0);
    v10 += 38;
    --v11;
  }
  while ( v11 );
  (**((void ( ***)(char *, _DWORD))this + 1820))((char *)this + 7280, 0);
  result = (**((int ( ***)(char *, _DWORD))this + 1858))((char *)this + 7432, 0);
  *((_BYTE *)this + 4524) = 1;
  return result;
}

// 0x005326A0
int RoleSystem::StartBlinkUI()
{
  void ( **v2)(char *, int); // eax

  v2 = (void ( **)(char *, int))*((_DWORD *)this + 1820);
  *((_BYTE *)this + 7277) = 1;
  *((_BYTE *)this + 7596) = 0;
  (*v2)((char *)this + 7280, 1);
  return (**((int ( ***)(char *, _DWORD))this + 1858))((char *)this + 7432, 0);
}

// 0x005326E0
int RoleSystem::StopBlinkUI()
{
  void ( **v2)(char *, _DWORD); // eax

  v2 = (void ( **)(char *, _DWORD))*((_DWORD *)this + 1820);
  *((_BYTE *)this + 7277) = 0;
  (*v2)((char *)this + 7280, 0);
  return (**((int ( ***)(char *, _DWORD))this + 1858))((char *)this + 7432, 0);
}

// 0x00532710
BOOL RoleSystem::UpdateTimer(int nVal, int nVal2)
{
  DWORD TickCount; // eax
  DWORD v5; // eax
  int v6; // ebp
  DWORD v7; // eax
  DWORD v8; // eax
  int v9; // ebp
  gbActor *m_pact; // edx
  unsigned __int8 v11; // al
  char m_fInterpStart_high; // al
  DWORD v13; // eax
  DWORD v14; // eax
  unsigned int v15; // ecx
  int v16; // eax
  gbTexture *m_pbktex; // ecx

  if ( ((UIParabolaCtrl *)(UIParabolaCtrl *)this + 1477)->GetState() == 2 )
    *((_BYTE *)this + 7276) = 1;
  if ( *((_BYTE *)this + 7276) )
  {
    if ( *((_BYTE *)this + 7277) )
    {
      if ( !*((_BYTE *)this + 7592) )
      {
        TickCount = GetTickCount();
        *((_DWORD *)this + 1896) = TickCount;
        *((_DWORD *)this + 1897) = TickCount;
        *((_BYTE *)this + 7592) = 1;
      }
      v5 = GetTickCount();
      v6 = *((_DWORD *)this + 1897);
      *((_DWORD *)this + 1896) = v5;
      if ( v5 - v6 > 0xA0 )
      {
        *((_DWORD *)this + 1897) = v5;
        *((_BYTE *)this + 7592) = 0;
        (**((void ( ***)(_DWORD))this + 1820))(*((unsigned __int8 *)this + 7596));
        (**((void ( ***)(char *, bool))this + 1858))((char *)this + 7432, *((_BYTE *)this + 7596) == 0);
        *((_BYTE *)this + 7596) = *((_BYTE *)this + 7596) == 0;
      }
    }
    if ( LOBYTE(this->m_partyActor.m_vecTargetPos.z) )
    {
      if ( !this->m_partyActor.m_actarray[12] )
      {
        v7 = GetTickCount();
        *(_DWORD *)&this->m_partyActor.m_actarray[4] = v7;
        *(_DWORD *)&this->m_partyActor.m_actarray[8] = v7;
        this->m_partyActor.m_actarray[12] = 1;
      }
      v8 = GetTickCount();
      v9 = *(_DWORD *)&this->m_partyActor.m_actarray[8];
      *(_DWORD *)&this->m_partyActor.m_actarray[4] = v8;
      if ( v8 - v9 <= 0xBB8 )
      {
        if ( BYTE1(this->m_partyActor.m_vecTargetPos.z) )
        {
          v11 = HIBYTE(this->m_partyActor.m_fInterpStart) + 20;
          HIBYTE(this->m_partyActor.m_fInterpStart) = v11;
          if ( v11 >= 0xC8u )
            BYTE1(this->m_partyActor.m_vecTargetPos.z) = 0;
        }
        else
        {
          m_fInterpStart_high = HIBYTE(this->m_partyActor.m_fInterpStart);
          HIBYTE(this->m_partyActor.m_fInterpStart) = m_fInterpStart_high - 20;
          if ( m_fInterpStart_high == 20 )
            BYTE1(this->m_partyActor.m_vecTargetPos.z) = 1;
        }
        sub_446010(&this->m_partyActor.m_pact);
      }
      else
      {
        *(_DWORD *)&this->m_partyActor.m_actarray[8] = v8;
        this->m_partyActor.m_actarray[12] = 0;
        m_pact = this->m_partyActor.m_pact;
        LOBYTE(this->m_partyActor.m_vecTargetPos.z) = 0;
        ((void ( *)(_DWORD))*((_DWORD *)m_pact))(0);
        HIBYTE(this->m_partyActor.m_fInterpStart) = -56;
      }
    }
    if ( !*((_BYTE *)this + 4524) )
    {
      if ( !*((_BYTE *)this + 4536) )
      {
        v13 = GetTickCount();
        *((_DWORD *)this + 1132) = v13;
        *((_DWORD *)this + 1133) = v13;
        *((_BYTE *)this + 4536) = 1;
      }
      v14 = GetTickCount();
      v15 = v14 - *((_DWORD *)this + 1133);
      *((_DWORD *)this + 1132) = v14;
      if ( v15 > 0x3E8 )
      {
        *((_DWORD *)this + 1133) = v14;
        *((_BYTE *)this + 4536) = 0;
        v16 = *((_DWORD *)this + 1128) - 1;
        *((_DWORD *)this + 1128) = v16;
        if ( v16 <= 0 )
        {
          m_pbktex = this->m_FrameA.m_pbktex;
          *((_DWORD *)this + 1128) = 0;
          *((_BYTE *)this + 4524) = 1;
          ((Actor *)m_pbktex)->UpdateAnimState(1);
        }
      }
      ((RoleSystem *)*((_DWORD *)this + 1128))->ScaleValue((int *)this + 1129, (int *)this + 1130);
      ((RoleAtt *)this)->SwitchPage(*((_DWORD *)this + 1129), *((_DWORD *)this + 1130));
    }
    if ( ((UIParabolaCtrl *)(UIParabolaCtrl *)this + 1135)->GetState() == 2 )
      *(_BYTE *)(this->m_nActiveRole + 24) = 1;
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x00532960
int RoleSystem::ScaleValue(int nVal, int *pnVal, int *p_DWORD)
{
  int result; // eax

  *pnVal = nVal / 10;
  *p_DWORD = 0;
  result = 10 * *pnVal;
  *p_DWORD = nVal - result;
  return result;
}

// 0x005329A0
int RoleSystem::HandleMsgDLL(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  if ( hinstDLL == (HINSTANCE)1000 )
    return DllMain((HINSTANCE)0x3E8, fdwReason, lpvReserved);
  else
    return ((PalScript *)this)->OnMessage((int)hinstDLL, fdwReason, (int)lpvReserved);
}

// 0x00532C80
void RoleSystem::AdjustHeight(int nVal)
{
  unsigned int RolePtr; // edi
  double v4; // st7

  if ( nVal )
  {
    this->m_fontcolor.Color = nVal;
// [VFTABLE] this->__vftable = *(vtbl_0056AE2C **)(nVal + 4);
    RolePtr = ((RoleSystem *)*(RoleSystem **)nVal)->GetRolePtr(0);
    this->m_wndcolor.Color = RolePtr;
    v4 = ((Scene *)*(_DWORD *)this->m_fontcolor.Color)->GetTileHeight(0, (__int64)((*(float *)&this->m_childs.m_pData - *(float *)(RolePtr + 128)) / g_fSceneScale), (__int64)((*(float *)&this->m_childs.m_nSize - *(float *)(RolePtr + 136)) / g_fSceneScale), 0)
       + this->m_fStateX;
    *(float *)&this->m_childs.capacity = v4;
    this->m_fStateY = v4;
  }
}

// 0x00532D30
int RoleSystem::GetStateMode()
{
  int result; // eax

  result = *(_DWORD *)&this->m_nStateMode;
  this->m_rect.right = result;
  return result;
}

// 0x00532D40
void RoleSystem::NegateStateMode()
{
  *(float *)&this->m_rect.right = -*(float *)&this->m_nStateMode;
}

// 0x00532E10
char RoleSystem::ResetPathState()
{
  float v3; // [esp+0x4] [ebp+0x4]
  float v4; // [esp+0xC] [ebp+0xC]
  float v5; // [esp+0x10] [ebp+0x10]
  float v6; // [esp+0x18] [ebp+0x18]
  float v7; // [esp+0x1C] [ebp+0x1C]
  float v8; // [esp+0x24] [ebp+0x24]
  float v9; // [esp+0x28] [ebp+0x28]
  float v10; // [esp+0x30] [ebp+0x30]

  if ( ((RoleSystem *)*(RoleSystem **)this->m_fontcolor.Color)->IsRoleInRange(0, (int *)(__int64)((v3 - *(float *)(this->m_wndcolor.Color + 128)) / g_fSceneScale), (__int64)((v4 - *(float *)(this->m_wndcolor.Color + 136)) / g_fSceneScale)) )
  {
    if ( ((RoleSystem *)*(RoleSystem **)this->m_fontcolor.Color)->IsRoleInRange(0, (int *)(__int64)((v5 - *(float *)(this->m_wndcolor.Color + 128)) / g_fSceneScale), (__int64)((v6 - *(float *)(this->m_wndcolor.Color + 136)) / g_fSceneScale)) )
    {
      if ( ((RoleSystem *)*(RoleSystem **)this->m_fontcolor.Color)->IsRoleInRange(0, (int *)(__int64)((v7 - *(float *)(this->m_wndcolor.Color + 128)) / g_fSceneScale), (__int64)((v8 - *(float *)(this->m_wndcolor.Color + 136)) / g_fSceneScale)) )
      {
        if ( ((RoleSystem *)*(RoleSystem **)this->m_fontcolor.Color)->IsRoleInRange(0, (int *)(__int64)((v9 - *(float *)(this->m_wndcolor.Color + 128)) / g_fSceneScale), (__int64)((v10 - *(float *)(this->m_wndcolor.Color + 136)) / g_fSceneScale)) )
        {
          return 0;
        }
        else
        {
          LOBYTE(this->m_nPathState) = 0;
          return 1;
        }
      }
      else
      {
        LOBYTE(this->m_nPathState) = 1;
        return 1;
      }
    }
    else
    {
      LOBYTE(this->m_nPathState) = 1;
      return 1;
    }
  }
  else
  {
    LOBYTE(this->m_nPathState) = 0;
    return 1;
  }
}
