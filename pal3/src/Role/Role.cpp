#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/Role.h"

// Unnamed globals (extern)
extern int dword_C110CC;

// 0x00408D10
int Role::CalcXueJianInit(int nVal, int nVal2)
{
  int result; // eax

  result = 0;
  switch ( nVal )
  {
    case 0:
      result = 8 * nVal2 + 80;
      break;
    case 1:
      result = 7 * nVal2 + 75;
      break;
    case 2:
      result = 9 * nVal2 + 80;
      break;
    case 3:
      result = 7 * nVal2 + 60;
      break;
    case 4:
      result = 9 * nVal2 + 100;
      break;
    default:
      return result;
  }
  return result;
}

// 0x00408D80
int Role::CalcLongKuiInit(int nVal, int nVal2)
{
  double v2; // st7
  long double v3; // st7
  float v5; // [esp+0x0] [ebp-0x4]
  float nVal2a; // [esp+0x10] [ebp+0xC]

  v2 = (double)nVal2;
  nVal2a = 0.0;
  v5 = v2;
  switch ( nVal )
  {
    case 0:
      v3 = sqrt(v5) * 9.0 + 8.0;
      goto LABEL_7;
    case 1:
      v3 = sqrt(v5) * 9.0 + 6.0;
      goto LABEL_7;
    case 2:
      v3 = sqrt(v5) * 9.0 + 7.0;
      goto LABEL_7;
    case 3:
      v3 = sqrt(v5) * 9.0 + 5.0;
      goto LABEL_7;
    case 4:
      v3 = (sqrt(v5) + 1.0) * 9.0;
LABEL_7:
      nVal2a = v3;
      break;
    default:
      return (int)nVal2a;
  }
  return (int)nVal2a;
}

// 0x00408E30
int Role::CalcZiXuanInit(int nVal, int nVal2)
{
  int result; // eax

  result = 0;
  switch ( nVal )
  {
    case 0:
      result = 4 * nVal2 + 25;
      break;
    case 1:
      result = 5 * nVal2 + 25;
      break;
    case 2:
      result = 4 * nVal2 + 22;
      break;
    case 3:
      result = 2 * (3 * nVal2 + 15);
      break;
    case 4:
      result = 4 * nVal2 + 20;
      break;
    default:
      return result;
  }
  return result;
}

// 0x00408E90
int Role::CalcChangQingInit(int nVal, int nVal2)
{
  double v2; // st7
  float v4; // [esp+0x0] [ebp-0x4]
  float nVal2a; // [esp+0x10] [ebp+0xC]

  v4 = 0.0;
  nVal2a = (float)nVal2;
  switch ( nVal )
  {
    case 0:
      v2 = nVal2a * 4.5 + 26.0;
      goto LABEL_7;
    case 1:
      v2 = nVal2a * 4.0 + 24.0;
      goto LABEL_7;
    case 2:
      v2 = nVal2a * 4.5 + 20.0;
      goto LABEL_7;
    case 3:
      v2 = nVal2a * 4.0 + 22.0;
      goto LABEL_7;
    case 4:
      v2 = nVal2a * 5.0 + 35.0;
LABEL_7:
      v4 = v2;
      break;
    default:
      return (int)v4;
  }
  return (int)v4;
}

// 0x00408F30
int Role::CalcHuaYingInit(int nVal, int nVal2)
{
  double v2; // st7
  float v4; // [esp+0x0] [ebp-0x4]
  float nVal2a; // [esp+0x10] [ebp+0xC]

  v4 = 0.0;
  nVal2a = (float)nVal2;
  switch ( nVal )
  {
    case 0:
      v2 = nVal2a * 3.3 + 17.0;
      goto LABEL_7;
    case 1:
      v2 = nVal2a * 3.0 + 13.0;
      goto LABEL_7;
    case 2:
      v2 = nVal2a * 3.5 + 16.0;
      goto LABEL_7;
    case 3:
      v2 = nVal2a * 3.0 + 16.0;
      goto LABEL_7;
    case 4:
      v2 = nVal2a * 3.0 + 18.0;
LABEL_7:
      v4 = v2;
      break;
    default:
      return (int)v4;
  }
  return (int)v4;
}

// 0x00411900
Role::Role()
{
  gbVec3D *pt; // ebx
  char p_BYTE; // [esp+0x57] [ebp-0x15] BYREF
  int v4; // [esp+0x58] [ebp-0x14]
  Role *v5; // [esp+0x5C] [ebp-0x10]
  int v6; // [esp+0x68] [ebp-0x4]

  this->position.x = 0.0;
  this->position.y = 0.0;
  this->position.z = 0.0;
this->radius = 12.0;
  v6 = 0;
  this->m_needscriptdel = 0;
// [VFTABLE] ((RenderTarget3 *)&this->__vftable)->ClearEffects();
  LOBYTE(v6) = 2;
  ((RoleSystem *)this->m_cmdqueue)->ClearColors(&p_BYTE);
  this->m_groundpos.x = 0.0;
  this->m_groundpos.y = 0.0;
  this->m_groundpos.z = 0.0;
  LOBYTE(v6) = 3;
  this->m_renderpos.x = 0.0;
  this->m_renderpos.y = 0.0;
  this->m_renderpos.z = 0.0;
  pt = this->m_npcinfo.path.pt;
  v4 = 16;
  do
  {
    --v4;
  }
  while ( v4 );
  ((Actor *)&this->pCG_SceneProp)->FastInit();
  this->m_actor.m_dwMatMsg[4] = 0;
  this->m_actor.m_dwMatMsg[5] = 0;
  this->m_actor.m_dwMatMsg[6] = 0;
  *(_DWORD *)&this->m_actor.m_curact[27] = 0;
  *(_DWORD *)&this->m_actor.m_curact[31] = 0;
  *(_DWORD *)&this->m_actor.m_curact[35] = 0;
  *(_DWORD *)&this->m_actor.m_curact[39] = 0;
  *(_DWORD *)&this->m_actor.m_curact[43] = 0;
  this->m_actor.m_fDirX = 0.0;
  this->m_actor.m_fDirY = 0.0;
  this->m_actor.m_fDirZ = 0.0;
  this->m_actor.m_fNormX = 0.0;
  this->m_actor.m_fNormY = 0.0;
  this->m_actor.m_fNormZ = 0.0;
  this->m_actor.m_fDistAccum = 0.0;
  this->m_actor.m_fSpeed = 0.0;
  *((_DWORD *)&this->m_actor.m_fSpeed + 1) = 0;
  *((_DWORD *)&this->m_actor.m_fSpeed + 2) = 0;
  *((_DWORD *)&this->m_actor.m_fAngleDeg + 1) = 0;
  *(_DWORD *)&this->m_actor.m_bDirFlag = 0;
  *((_DWORD *)&this->m_actor.m_bDirFlag + 1) = 0;
  *((_DWORD *)&this->m_actor.m_bDirFlag + 2) = 0;
  *((_DWORD *)&this->m_actor.m_bDirFlag + 3) = 0;
  *((_DWORD *)&this->m_actor.m_bDirFlag + 4) = 0;
  LOBYTE(v6) = 4;
  this->m_actor.m_nUpdateMode = 0;
  *(&this->m_actor.m_nUpdateMode + 1) = 0;
  *(&this->m_actor.m_nUpdateMode + 2) = 0;
  *(_DWORD *)&this->m_path_region[2936] = 0;
  this->m_wanapos.x = 0.0;
  this->m_wanapos.y = 0.0;
  this->m_wanapos.z = 0.0;
  dword_C110CC = gbCrc32Compute("hold");
  ((RoleSystem *)this)->InitDefaultState();
}

// 0x00418170
int Role::CheckOBBCollision(gbOBBox *p)
{
  gbOBBox actionId; // [esp+0x4] [ebp-0x4C] BYREF

  ((Actor *)&this->pCG_SceneProp)->PlayAction((int)&actionId);
  actionId.trans.m[3][0] = actionId.trans.m[3][0] + this->m_renderpos.x;
  actionId.trans.m[3][1] = actionId.trans.m[3][1] + this->m_renderpos.y;
  actionId.trans.m[3][2] = actionId.trans.m[3][2] + this->m_renderpos.z;
  actionId.xlen = actionId.xlen * 0.60000002;
  return ((gbOBBox *)&actionId)->IsColOBB(p);
}

// 0x0041B640
void Role::UpdateBoundingBox(gbAABBox *pBox)
{
  gbOBBox actionId; // [esp+0x4] [ebp-0x4C] BYREF

  ((Actor *)&this->m_npcinfo.reserve[26])->PlayAction((int)&actionId);
  actionId.trans.m[3][0] = actionId.trans.m[3][0] + *(float *)this->m_cmdqueue;
  actionId.trans.m[3][1] = actionId.trans.m[3][1] + *(float *)&this->m_cmdqueue[4];
  actionId.trans.m[3][2] = actionId.trans.m[3][2] + *(float *)&this->m_cmdqueue[8];
  ((gbOBBox *)&actionId)->GetAABBox(pBox);
}

// 0x0041B6A0
gbGfxManager * Role::GetGfxManager()
{
  gbGfxManager *result; // eax
  int nVal; // [esp+0x4] [ebp+0x4]

  ((RoleSystem *)((char *)this - 64))->RenderRole(gfxMgr->pMatrixStack[1], nVal);
  return result;
}

// 0x0041BE30
ScriptObj * Role::_sdtor_22(char a2)
{
  ScriptObj *v2; // esi

  v2 = (ScriptObj *)((char *)this - 64);
  ((ScriptObj *)(ScriptObj *)this - 16)->_ScriptObj();
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}
