#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/SceneMgr.h"

// Forward declarations for unnamed functions
int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc); // from annotations
int UISceneUpdate(void); // from annotations

// Unnamed globals (extern)
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern int dword_C10BD8;
extern int dword_D8BC30;
extern int dword_D8BC34;
extern int dword_D8BC38;
extern RoleSystem stru_C059A0;

// 0x00408850
int SceneMgr::ResetPlayerAtts()
{
  void **p_m_pParticleData; // esi
  int result; // eax
  int v2; // [esp+0x10] [ebp-0x4]

  p_m_pParticleData = &Buffer.m_partyActor.m_pParticleData;
  v2 = 5;
  do
  {
    *(p_m_pParticleData - 215) = 0;
    *((_WORD *)p_m_pParticleData - 428) = 0;
    lstrcpyA((LPSTR)p_m_pParticleData - 854, g_szSceneUIText);
    lstrcpyA((LPSTR)p_m_pParticleData - 342, g_szSceneUIText);
    lstrcpyA((LPSTR)p_m_pParticleData - 312, g_szSceneUIText);
    lstrcpyA((LPSTR)p_m_pParticleData - 260, g_szSceneUIText);
    memset(p_m_pParticleData - 56, 0, 0x30u);
    *(p_m_pParticleData - 20) = 0;
    *(p_m_pParticleData - 2) = (void *)0xFFFF;
    *(p_m_pParticleData - 1) = 0;
    *p_m_pParticleData = 0;
    p_m_pParticleData[1] = (void *)0xFFFF;
    p_m_pParticleData[2] = 0;
    p_m_pParticleData[3] = 0;
    p_m_pParticleData[4] = (void *)0xFFFF;
    p_m_pParticleData[5] = 0;
    p_m_pParticleData[6] = 0;
    ArraySort((int)(p_m_pParticleData + 7), 12, 2, 0 /* TODO: (int)exception::exception */);
    p_m_pParticleData[13] = (void *)0xFFFF;
    p_m_pParticleData[14] = 0;
    p_m_pParticleData[15] = 0;
    memset(p_m_pParticleData - 215, 0, 0x580u);
    p_m_pParticleData += 352;
    result = --v2;
  }
  while ( v2 );
  return result;
}

// 0x0040CA40
int SceneMgr::InitSceneRoles()
{
  int *v0; // esi
  ScriptSystem *v1; // ecx
  int *v2; // eax
  int *v3; // ebp
  int v4; // edx
  bool v5; // zf
  int v6; // ecx
  void **v7; // eax
  int *v8; // ebx
  int *v9; // ebx
  int *v10; // eax
  int *v11; // edi
  int v12; // ecx
  void *v14; // [esp-0x4] [ebp-0x14]

  v0 = &((RoleSystem *)&stru_C059A0)->m_teamSlots[151];
  do
  {
    if ( *v0 )
      ((RoleSystem *)(v0 - 158))->NotifyMoveComplete();
    if ( v0 - 158 != (int *)g_pRoleSystem )
      *v0 = 0;
    ((RoleSystem *)(v0 - 158))->NotifySceneChange();
    v1 = (ScriptSystem *)*(v0 - 123);
    v2 = v0 - 123;
    if ( v1 )
    {
      v3 = v0 - 123;
      do
      {
        v4 = *(v2 - 8) + 16;
        v6 = *v3 - 1;
        v5 = *v3 == 1;
        *(v2 - 8) = v4;
        *v3 = v6;
        if ( v5 || v4 == *(v0 - 132) )
        {
          v7 = (void **)*(v0 - 130);
          *(v0 - 130) = (int)(v7 + 1);
          operator delete(*v7);
          v3 = v0 - 123;
          if ( *(v0 - 123) )
          {
            v10 = (int *)*(v0 - 130);
            v11 = v0 - 133;
            v12 = *v10;
            *v11 = *v10;
            v11[1] = v12 + 4096;
            v11[2] = v12;
            v11[3] = (int)v10;
          }
          else
          {
            v8 = v0 - 133;
            *v8 = 0;
            v8[1] = 0;
            v8[2] = 0;
            v8[3] = 0;
            v9 = v0 - 129;
            *(v0 - 129) = 0;
            v14 = (void *)*(v0 - 125);
            v9[1] = 0;
            v9[2] = 0;
            v9[3] = 0;
            operator delete(v14);
          }
        }
        v1 = (ScriptSystem *)*(v0 - 123);
        v2 = v0 - 123;
      }
      while ( v1 );
    }
    v0[207] = 0;
    v0 += 2176;
  }
  while ( (int)v0 < (int)&dword_C10BD8 );
  *(_DWORD *)&g_RoleSystemExtra1.m_partyActor.m_szTexture[4] = 0;
  return ((ScriptSystem *)v1)->Cleanup();
}

// 0x0040FC70
int SceneMgr::GetValidPartyCount()
{
  int result; // eax
  int i; // ecx

  result = 0;
  for ( i = 0; i < 5; ++i )
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + i) )
      ++result;
  }
  return result;
}

// 0x00421C00
int SceneMgr::RenderActiveRoles()
{
  int v2; // edi
  int result; // eax
  UIScene *v4; // esi

  v2 = 0;
  result = *((_DWORD *)this + 14392);
  if ( result > 0 )
  {
    v4 = (UIScene *)((char *)this + 57572);
    do
    {
      if ( BYTE1(v4->m_fCameraOffset) == 4 )
        ((UIScene *)v4)->RenderVertexPool();
      result = *((_DWORD *)this + 14392);
      ++v2;
      v4 = (UIScene *)((char *)v4 + 8704);
    }
    while ( v2 < result );
  }
  return result;
}

// 0x00422050
int * SceneMgr::FindRoleByState(char nState)
{
  int v2; // eax
  int v3; // esi
  _BYTE *i; // edx

  v2 = 0;
  v3 = *((_DWORD *)this + 14392);
  if ( v3 <= 0 )
    return 0;
  for ( i = (char *)this + 57744; *i != nState; i += 8704 )
  {
    if ( ++v2 >= v3 )
      return 0;
  }
  return (int *)((char *)this + 8704 * v2 + 57572);
}

// 0x00423500
int SceneMgr::ClearInactiveRoles()
{
  int result; // eax
  int v1; // edx
  _DWORD *v2; // ecx

  result = UISceneUpdate();
  v1 = 0;
  if ( *(int *)(result + 57568) > 0 )
  {
    v2 = (_DWORD *)(result + 58204);
    do
    {
      if ( *((_BYTE *)v2 - 459) == 2 )
        *v2 = 0;
      ++v1;
      v2 += 2176;
    }
    while ( v1 < *(_DWORD *)(result + 57568) );
  }
  return result;
}

// 0x004236B0
int SceneMgr::ResetSceneFlags()
{
  dword_D8BC30 = 0;
  dword_D8BC34 = 0;
  dword_D8BC38 = 1;
  return 0;
}

// 0x00493E40
void SceneMgr::FormatStatusCaption(int a2)
{
  gbGfxManager **v3; // edi
  int v4; // esi
  char *v5; // edi
  char Buffer[300]; // [esp+0xC] [ebp-0x258] BYREF
  int szName[75]; // [esp+0x138] [ebp-0x12C] BYREF

  memset(Buffer, 0, sizeof(Buffer));
  memset(szName, 0, sizeof(szName));
  v3 = &this->m_pGfxMgr + 213 * a2;
  sprintf(Buffer, "%s %d", (const char *)&g_szRoleName1, v3[51463]);
  sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, v3[51462]);
  sprintf(&Buffer[60], "%s %d", (const char *)&g_szRoleName2, v3[51464]);
  sprintf(&Buffer[90], "%s %d", (const char *)&g_szRoleName3, v3[51465]);
  sprintf(
    &Buffer[120],
    "%s %d",
    (const char *)&g_szSceneName,
    *((_DWORD *)&::Buffer.m_partyActor.m_fActionAssignParam + 352 * a2));
  sprintf(&Buffer[150], "%s %d", (const char *)g_bSlotFlag, v3[51466]);
  sprintf(&Buffer[180], "%s %d", (const char *)&g_bSlotFlag[256], v3[51467]);
  sprintf(&Buffer[210], "%s %d", byte_DC3F3C, v3[51469]);
  sprintf(&Buffer[240], "%s %d", (const char *)&g_bSlotFlag[512], v3[51468]);
  sprintf(&Buffer[270], "%s %d", byte_DC403C, v3[51470]);
  v4 = 0;
  v5 = (char *)this + 9980 * a2 + 159232;
  do
  {
    ((UICaption *)(v5 - 1520))->SetEnable((int)&Buffer[v4], 0);
    ((UICaption *)v5)->SetEnable((int)szName + v4, 0);
    ((UICaption *)(v5 + 1520))->SetEnable((int)g_szSceneUIText, 0);
    v4 += 30;
    v5 += 152;
  }
  while ( v4 < 300 );
  ((UICaption *)((char *)this + 204880))->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)((char *)this + 204728))->SetEnable((int)g_szSceneUIText, 0);
}

// 0x004CDA10
CEffMgr * SceneMgr::Create(int gfxMgr, int cam, int nVal)
{
  gbGfxManager *m_pGfxMgr; // eax
  gbRenderEffect *v6; // eax
  gbGfxManager *v7; // ecx
  gbRenderEffect *v8; // eax
  gbGfxManager *v9; // edx

  this->m_pGfxMgr = (gbGfxManager *)gfxMgr;
  this->m_pCamera = (gbCamera *)cam;
  this->m_pAddEffect = 0;
  this->m_pAlphaEffect = 0;
  this->m_pSceneRoot = (gbSceneGraph *)nVal;
  memset(&this->m_aSceneSlots, 0, 0x900u);
  memset(&this->((RoleSystem *)&stru_C059A0)->m_teamSlots[64], 0, 0xA000u);
  m_pGfxMgr = this->m_pGfxMgr;
  *((_DWORD *)this + 10823) = 0;
  *((_DWORD *)this + 10824) = 0;
  *((_DWORD *)this + 10825) = 0;
  *((_DWORD *)this + 10826) = 0;
  *((_DWORD *)this + 10827) = 1065353216;
  v6 = ((gbEffectMgr *)m_pGfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\AdditiveBlend.gbf", 0);
  v7 = this->m_pGfxMgr;
  this->m_pAddEffect = v6;
  v8 = ((gbEffectMgr *)v7->pEffectMgr)->NewRenderEffect("gfxscript\\AlphaBlend.gbf", 0);
  v9 = this->m_pGfxMgr;
  this->m_pAlphaEffect = v8;
  this->m_pAddEffect2 = ((gbEffectMgr *)v9->pEffectMgr)->NewRenderEffect("gfxscript\\AdditiveBlendNoZ.gbf", 0);
  this->m_pAlphaEffect2 = ((gbEffectMgr *)this->m_pGfxMgr->pEffectMgr)->NewRenderEffect((const char *)g_TargetData, 0);
  ((CEffMgr *)this)->InitEffClass();
  return (CEffMgr *)this;
}

// 0x004CDBF0
char SceneMgr::RenderAll()
{
  int *v1; // esi
  int v2; // edi
  char result; // al

  v1 = &this->((RoleSystem *)&stru_C059A0)->m_teamSlots[68];
  v2 = 2048;
  do
  {
    result = *((_BYTE *)v1 - 4);
    if ( result )
      result = (*(int ( **)(int))(*(_DWORD *)*v1 + 24))(*v1);
    v1 += 5;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x004CDC20
char SceneMgr::RenderUpdate()
{
  int *v1; // esi
  int v2; // edi
  char result; // al

  v1 = &this->((RoleSystem *)&stru_C059A0)->m_teamSlots[68];
  v2 = 2048;
  do
  {
    result = *((_BYTE *)v1 - 4);
    if ( result )
      result = (*(int ( **)(int))(*(_DWORD *)*v1 + 16))(*v1);
    v1 += 5;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x00528D50
SceneMgr * SceneMgr::LoadMainUITexture()
{
  SceneMgr *v1; // esi
  int *v2; // ebx
  int v3; // edi
  RenderTarget *v4; // ebp
  int v5; // eax
  int *p_m_nHalfWidth; // edi
  RenderTarget *v7; // esi
  bool v8; // zf
  float fX; // [esp+0x0] [ebp-0x28]
  int fXa; // [esp+0x0] [ebp-0x28]
  float fY; // [esp+0x4] [ebp-0x24]
  int v13; // [esp+0x18] [ebp-0x10]
  int v15; // [esp+0x20] [ebp-0x8]
v2 = (int *)((char *)this + 56172);
  v3 = *((_DWORD *)this + 14045) - *((_DWORD *)this + 14043);
  v15 = v3;
  v4 = (RenderTarget *)((char *)this + 14124);
  v13 = 36;
  while ( 1 )
  {
    ((RenderTarget *)v4)->LoadTexture("UI\\GameMainUI\\Par_Effect\\spark_16.tga");
    ((RenderTarget *)v4)->SetSize(16);
    ((RenderTarget *)v4)->SetColor(0x19u, 0x75u, 0xFCu);
    v5 = rand();
    ((RenderTarget *)v4)->SetAlpha(v5 % 100 - 101);
    *((_BYTE *)&v4->m_ScreenPlane + 4) = 1;
    ((RenderTarget *)v4)->SetField084();
    ((RenderTarget *)v4)->SetState();
    fY = (float)v1[9].m_partyInitData[37];
    fX = (float)(*v2 + rand() % v3);
    ((RenderTarget *)v4)->UpdateTransform(fX, fY);
    ((RenderTarget *)v4)->Render(*v2, v2[1], v2[2]);
    rand();
    *(float *)&fXa = (float)(rand() % 2 + 1);
    ((RenderTarget *)v4)->SetOffset(fXa);
    ((RenderTarget *)v4)->SetScale(0);
    ((RenderTarget *)v4)->SetVisible(1);
    p_m_nHalfWidth = &v4[105].m_nHalfWidth;
    v7 = v4;
    v4 = (RenderTarget *)((char *)v4 + 584);
    v8 = v13 == 1;
    qmemcpy(p_m_nHalfWidth, v7, 0x248u);
    --v13;
    if ( v8 )
      break;
    v3 = v15;
}
  *((_BYTE *)this + 56189) = 0;
  return this;
}

// 0x0052EC90
int * SceneMgr::GetCurrentNode()
{
  this->m_PlayerAtts._todo_0C0 = 0;
  this->m_PlayerAtts._todo_0C4 = 0;
  this->m_PlayerAtts._todo_0CC = 0;
  LOBYTE(this->m_aRoleSlotStat[1]) = 1;
  BYTE1(this->m_aRoleSlotStat[1]) = 1;
  BYTE2(this->m_aRoleSlotStat[1]) = 0;
  this->m_pGfxMgr = 0;
  this->m_pSceneRoot = 0;
  this->m_pAddEffect2 = 0;
  this->m_pAlphaEffect2 = 0;
  this->m_pAddEffect = 0;
  return (int *)this;
}
