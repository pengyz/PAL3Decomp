#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/RoleSystem.h"
#include "Misc/AStarPathFinder.h"
#include "Role/Actor.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Misc/CG_Entry.h"
#include "Render/CScreenMode.h"
#include "Scene/Camera.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/Config.h"
#include "GameBase/GRPinput.h"
#include "GameBase/InputSystem.h"
#include "Misc/NPCInfo.h"
#include "Role/Object3D.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PathObj.h"
#include "Misc/PlayerItem.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget2.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Misc/RoleCameraCtrl.h"
#include "Scene/Scene.h"
#include "Scene/SceneObj.h"
#include "Effect/ScreenEffect.h"
#include "Effect/ScreenEffectMgr.h"
#include "Misc/ScriptPoolPage.h"
#include "Script/ScriptSystem.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/ScriptVM.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UISceneMap.h"
#include "UI/UIWnd.h"
#include "Misc/_Console.h"
#include "Misc/tagCCBStageData.h"
#include "Misc/tagRoleSystemData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_401070(...);
int sub_407EC0(...);
int sub_408010(...);
int sub_4080F0(...);
int sub_420250(...);
int sub_420380(...);
int sub_4204B0(...);
int todo_00537120(...);

class RoleCameraCtrl;

// Unnamed globals (extern)
extern CHAR byte_DC7D3C[512];
extern CHAR byte_DCD03C[256];
void __cdecl nullsub_4(void);
void __cdecl nullsub_5(void);
void __cdecl nullsub_6(void);
extern RoleCameraCtrl stru_DBA134;

// 0x004083E0
BOOL RoleSystem::CheckSceneCollision(int *nFlag, int nVal)
{
  RoleSystem *v3; // eax
  int *bottom; // [esp-0x10] [ebp-0x10]

  bottom = *((int **)this + 7);
  v3 = (RoleSystem *)UISceneUpdate();
  return (((RoleSystem *)v3))->RoleSystem::CheckCollision(bottom, (int)nFlag);
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
  int v11; // eax
  RoleSystem *v12; // eax
  int v14; // ecx
  unsigned int m_id; // eax
  int v16; // edi
  LONG v17; // eax
  float v18; // st7
  float v19; // st6
  int v20; // eax
  float v21; // ecx
  unsigned int v22; // eax
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
  this->m_rect.right = (((RoleSystem *)v7))->RoleSystem::GetRolePtr(index);
  *(_DWORD *)(nVal + 3072) = 0;
  right = this->m_rect.right;
  v24 = (__int64)((*pfVal - *(float *)(right + 128)) / g_fRoleGridScale);
  nVal2 = (__int64)((pfVal[2] - *(float *)(right + 136)) / g_fRoleGridScale);
  v9 = (int *)(__int64)((*pfVal2 - *(float *)(right + 128)) / g_fRoleGridScale);
  v10 = (int *)(__int64)((pfVal2[2] - *(float *)(right + 136)) / g_fRoleGridScale);
  v11 = (int)((UIWnd *)this);
  a7 = (int *)v9;
  v27 = (int *)v10;
  if ( !(*(int ( **)(RoleSystem *, int, int))(v11 + 4))(this, v24, nVal2) )
    return 0;
  if ( !(*(int ( **)(RoleSystem *, int *, int *))(*(_DWORD *)((UIWnd *)this) + 4))(this, v9, v10) )
  {
    a7 = (int *)v9;
    bottom = *((int **)this + 7);
    v27 = (int *)v10;
    v12 = (RoleSystem *)UISceneUpdate();
    (((RoleSystem *)v12))->RoleSystem::ValidatePath(bottom, v9, v10, v24, nVal2, &a7);
  }
  if ( (int)sub_401070((AStarPathFinder *)this, v24, nVal2, a7, v27) < 0 )
  {
    (((AStarPathFinder *)this))->AStarPathFinder::Reset();
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
      v16 = *(_DWORD *)(m_id + 16);
      pDataa = *(_DWORD *)(m_id + 12);
      v17 = this->m_rect.right;
      v18 = ((float)pDataa + 0.5f) * g_fRoleGridScale + *(float *)(v17 + 128);
      v19 = ((float)v16 + 0.5f) * g_fRoleGridScale + *(float *)(v17 + 136);
      v20 = nVal + 12 * v14;
      *(_DWORD *)(v20 + 4) = 0;
      v28 = v19;
      v21 = v28;
      *(float *)v20 = v18;
      *(float *)(v20 + 8) = v21;
      ++*(_DWORD *)(nVal + 3072);
      v22 = *(_DWORD *)(this->m_id + 28);
      this->m_id = v22;
    }
    while ( v22 );
  }
  (((AStarPathFinder *)this))->AStarPathFinder::Reset();
  if ( *(int *)(nVal + 3072) <= 1 )
    return 0;
  (((PathObj *)nVal))->PathObj::CalcLength();
  return 1;
}

// 0x0040BE50
int * RoleSystem::Init()
{
  int *result; // eax
  int v2; // esi
  int v3; // edx

  result = (int *)&this->m_partyActor.m_dwMatMsg[2];
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
  __int16 *m_pSelfAtt; // esi
  int v4; // eax
  bool v5; // cf
  int v6; // esi
  RoleAtt *v7; // esi
  bool v8; // cf
  RoleAtt *m_pEquipAtt0; // esi
  bool v10; // cf
  RoleAtt *v11; // esi
  bool v12; // cf
  RoleAtt *v13; // esi
  bool v14; // cf
  float m_fBlendWeight; // esi
  bool v16; // cf
  int result; // eax

  for ( i = 0; i < 12; ++i )
  {
    m_pSelfAtt = (__int16 *)this->m_partyActor.m_pSelfAtt;
    v4 = 0;
    if ( !m_pSelfAtt )
      goto LABEL_33;
    if ( !*((_BYTE *)m_pSelfAtt + i + 631) && i < 7 )
      v4 = (unsigned long)m_pSelfAtt[i + 322];
    switch ( i )
    {
      case 7:
        v5 = *((_BYTE *)m_pSelfAtt + 619) != 0;
        goto LABEL_12;
      case 8:
        v5 = *((_BYTE *)m_pSelfAtt + 620) != 0;
        goto LABEL_12;
      case 9:
        v5 = *((_BYTE *)m_pSelfAtt + 621) != 0;
        goto LABEL_12;
      case 10:
        v5 = *((_BYTE *)m_pSelfAtt + 622) != 0;
        goto LABEL_12;
      case 11:
        v5 = *((_BYTE *)m_pSelfAtt + 623) != 0;
LABEL_12:
        v4 += v5;
        break;
      default:
        break;
    }
    v6 = *(_DWORD *)m_pSelfAtt;
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
    v7 = (RoleAtt *)this->m_partyActor.m_pEquipAtt1[0];
    if ( v7 )
    {
      if ( !v7->name[i + 31] )
        v4 += *((__int16 *)&v7->rolevalue[2] + i);
      switch ( i )
      {
        case 7:
          v8 = v7->name[19] != 0;
          goto LABEL_42;
        case 8:
          v8 = v7->name[20] != 0;
          goto LABEL_42;
        case 9:
          v8 = v7->name[21] != 0;
          goto LABEL_42;
        case 10:
          v8 = v7->name[22] != 0;
          goto LABEL_42;
        case 11:
          v8 = v7->name[23] != 0;
LABEL_42:
          v4 += v8;
          break;
        default:
          break;
      }
    }
    m_pEquipAtt0 = (RoleAtt *)this->m_partyActor.m_pEquipAtt0;
    if ( m_pEquipAtt0 )
    {
      if ( !m_pEquipAtt0->name[i + 31] )
        v4 += *((__int16 *)&m_pEquipAtt0->rolevalue[2] + i);
      switch ( i )
      {
        case 7:
          v10 = m_pEquipAtt0->name[19] != 0;
          goto LABEL_52;
        case 8:
          v10 = m_pEquipAtt0->name[20] != 0;
          goto LABEL_52;
        case 9:
          v10 = m_pEquipAtt0->name[21] != 0;
          goto LABEL_52;
        case 10:
          v10 = m_pEquipAtt0->name[22] != 0;
          goto LABEL_52;
        case 11:
          v10 = m_pEquipAtt0->name[23] != 0;
LABEL_52:
          v4 += v10;
          break;
        default:
          break;
      }
    }
    v11 = (RoleAtt *)this->m_partyActor.m_pEquipAtt2[0];
    if ( v11 )
    {
      if ( !v11->name[i + 31] )
        v4 += *((__int16 *)&v11->rolevalue[2] + i);
      switch ( i )
      {
        case 7:
          v12 = v11->name[19] != 0;
          goto LABEL_62;
        case 8:
          v12 = v11->name[20] != 0;
          goto LABEL_62;
        case 9:
          v12 = v11->name[21] != 0;
          goto LABEL_62;
        case 10:
          v12 = v11->name[22] != 0;
          goto LABEL_62;
        case 11:
          v12 = v11->name[23] != 0;
LABEL_62:
          v4 += v12;
          break;
        default:
          break;
      }
    }
    v13 = (RoleAtt *)this->m_partyActor.m_pEquipAtt2[3];
    if ( v13 )
    {
      if ( !v13->name[i + 31] )
        v4 += *((__int16 *)&v13->rolevalue[2] + i);
      switch ( i )
      {
        case 7:
          v14 = v13->name[19] != 0;
          goto LABEL_72;
        case 8:
          v14 = v13->name[20] != 0;
          goto LABEL_72;
        case 9:
          v14 = v13->name[21] != 0;
          goto LABEL_72;
        case 10:
          v14 = v13->name[22] != 0;
          goto LABEL_72;
        case 11:
          v14 = v13->name[23] != 0;
LABEL_72:
          v4 += v14;
          break;
        default:
          break;
      }
    }
    m_fBlendWeight = this->m_partyActor.m_fBlendWeight;
    if ( m_fBlendWeight != 0.0f )
    {
      if ( !*(_BYTE *)(LODWORD(m_fBlendWeight) + i + 631) )
        v4 += *(__int16 *)(LODWORD(m_fBlendWeight) + 2 * i + 644);
      switch ( i )
      {
        case 7:
          v16 = *(_BYTE *)(LODWORD(m_fBlendWeight) + 619) != 0;
          goto LABEL_82;
        case 8:
          v16 = *(_BYTE *)(LODWORD(m_fBlendWeight) + 620) != 0;
          goto LABEL_82;
        case 9:
          v16 = *(_BYTE *)(LODWORD(m_fBlendWeight) + 621) != 0;
          goto LABEL_82;
        case 10:
          v16 = *(_BYTE *)(LODWORD(m_fBlendWeight) + 622) != 0;
          goto LABEL_82;
        case 11:
          v16 = *(_BYTE *)(LODWORD(m_fBlendWeight) + 623) != 0;
LABEL_82:
          v4 += v16;
          break;
        default:
          break;
      }
    }
    result = *(&this->m_partyActor.m_nPathEnabled + i) + v4;
    *((_DWORD *)&this->m_partyActor.m_nAnimFrame + i) = result;
    if ( pData || (unsigned int)i > 2 )
      this->m_partyActor.m_dwMatMsg[i + 2] = result;
  }
  return result;
}

// 0x0040C9A0
int RoleSystem::ForceStopRole(int nVal)
{
  RoleSystem *v1; // edi
  int result; // eax

  v1 = (RoleSystem *)&g_RoleSlotBuf.m_teamData3[2176 * nVal + 588];
  if ( (((RoleSystem *)v1))->RoleSystem::IsPathMoving() )
    (((RoleSystem *)v1))->RoleSystem::StopPathMovement(1);
  else
    *(&g_nUnk61D8 + 2176 * nVal) = 1;
  result = *(&g_nUnk61D8 + 2176 * nVal);
  if ( !result )
    result = (((RoleSystem *)v1))->RoleSystem::Notify();
  if ( nVal == 1 && (::nVal == 1 || g_RoleSystemMain.m_nMoveSubMode == 10) )
  {
    (((ScriptSystem *)&g_RoleSystemMain))->ScriptSystem::UpdatePositions();
    (((RoleSystem *)&g_RoleSystemMain))->RoleSystem::UpdateMovement(fDeltaTime, 1);
    g_RoleSystemMain.m_nCoreState = 0;
    return (((RoleSystem *)&g_RoleSystemMain))->RoleSystem::UpdateTransform();
  }
  return result;
}

// 0x00410430
void RoleSystem::RenderMainRole(void *pMatrixStack)
{
  if ( g_RoleSystemMain.m_nMoveSubMode != 10 || unk_C08160.m_partyActor.m_pRoleObj )
    (((RoleSystem *)&g_RoleSystemMain))->RoleSystem::RenderRole((gbMatrixStack *)pMatrixStack, 0);
}

// 0x00410E40
int RoleSystem::CheckVisible()
{
  _DWORD *v0; // ecx
  _DWORD *v1; // ebx
  _DWORD *v2; // ecx
  unsigned int v3; // esi
  int v4; // edi
  unsigned int v5; // ebp
  int v6; // edx
  unsigned int v7; // eax
  _DWORD *v8; // ebp
  _DWORD *v9; // edx
  _DWORD *k; // eax
  _DWORD *v11; // eax
  _DWORD *v12; // ebx
  _DWORD *v13; // edi
  _DWORD *v14; // eax
  int result; // eax
  int v16; // ecx
  int v17; // kr00_4
  int v18; // edi
  int v19; // ebp
  _DWORD *v20; // edx
  _DWORD *v21; // eax
  _DWORD *v22; // ebx
  unsigned int j; // esi
  _DWORD *v24; // eax
  _DWORD *v25; // ecx
  _DWORD *v26; // edi
  int v27; // esi
  _DWORD *v28; // eax
  _DWORD *i; // edx
  _DWORD *v30; // ecx
  _DWORD *v31; // eax
  _DWORD *v32; // ebx
  _DWORD *v33; // [esp+0x10] [ebp-0x8]
  _DWORD *v34; // [esp+0x14] [ebp-0x4]
  int v35; // [esp+0x1C] [ebp+0x4]
  unsigned int v36; // [esp+0x1C] [ebp+0x4]
  int v37; // [esp+0x1C] [ebp+0x4]
  unsigned int v38; // [esp+0x20] [ebp+0x8]
  unsigned int v39; // [esp+0x20] [ebp+0x8]
  _DWORD *v40; // [esp+0x20] [ebp+0x8]
  _DWORD *v41; // [esp+0x24] [ebp+0xC]

  v1 = (_DWORD *)v0;
  v2 = (_DWORD *)v0[2];
  v3 = v38;
  v33 = (_DWORD *)v1;
  if ( (v1[3] - (int)v2) / 12 >= v38 )
  {
    v18 = v35;
    result = (unsigned int)((unsigned __int64)(715827883i64 * ((int)v2 - v35)) >> 32) >> 31;
    if ( ((int)v2 - v35) / 12 >= v38 )
    {
      if ( v38 )
      {
        v27 = 12 * v38;
        v28 = (_DWORD *)&v2[-3 * v38];
        for ( i = v2; v28 != v2; i += 3 )
        {
          if ( i )
          {
            *i = *v28;
            i[1] = (unsigned long)v28[1];
            i[2] = (unsigned long)v28[2];
            v27 = 12 * v38;
            v1 = (_DWORD *)v33;
          }
          v28 += 3;
        }
        v30 = (_DWORD *)v1[2];
        v31 = (_DWORD *)&v30[v27 / 0xFFFFFFFC];
        if ( (_DWORD *)v35 != &v30[v27 / 0xFFFFFFFC] )
        {
          do
          {
            v31 -= 3;
            v30 -= 3;
            *v30 = *v31;
            v30[1] = (unsigned long)v31[1];
            v30[2] = (unsigned long)v31[2];
          }
          while ( v31 != (_DWORD *)v35 );
          v1 = (_DWORD *)v33;
        }
        result = v35;
        if ( v35 != v27 + v35 )
        {
          do
          {
            v32 = (_DWORD *)result;
            result += 12;
            *v32 = *v41;
            v32[1] = (unsigned long)v41[1];
            v32[2] = (unsigned long)v41[2];
          }
          while ( result != v27 + v35 );
          v1 = (_DWORD *)v33;
        }
        v1[2] += v27;
      }
    }
    else
    {
      v19 = 12 * v38;
      v37 = 12 * v38;
      v20 = (_DWORD *)(v18 + 12 * v38);
      v40 = (_DWORD *)v20;
      if ( (_DWORD *)v18 != v2 )
      {
        v21 = (_DWORD *)((char *)v20 - v19);
        do
        {
          if ( v20 )
          {
            *v20 = *v21;
            v20[1] = (unsigned long)v21[1];
            v19 = v37;
            v20[2] = (unsigned long)v21[2];
            v20 = (_DWORD *)v40;
            v1 = (_DWORD *)v33;
          }
          v21 += 3;
          v20 += 3;
          v40 = (_DWORD *)v20;
        }
        while ( v21 != v2 );
      }
      v22 = (_DWORD *)v1[2];
      for ( j = v3 - ((int)v22 - v18) / 12; j; --j )
      {
        if ( v22 )
        {
          *v22 = *v41;
          v22[1] = (unsigned long)v41[1];
          v22[2] = (unsigned long)v41[2];
        }
        v22 += 3;
      }
      v24 = (_DWORD *)v18;
      v25 = (_DWORD *)v33[2];
      if ( (_DWORD *)v18 != v25 )
      {
        do
        {
          v26 = (_DWORD *)v24;
          v24 += 3;
          *v26 = *v41;
          v26[1] = (unsigned long)v41[1];
          v26[2] = (unsigned long)v41[2];
        }
        while ( v24 != v25 );
      }
      result = v19 + v33[2];
      v33[2] = result;
    }
  }
  else
  {
    v4 = (unsigned long)v1[1];
    if ( !v4 || (v5 = ((int)v2 - v4) / 12, v38 >= v5) )
      v5 = v38;
    if ( v4 )
      v6 = ((int)v2 - v4) / 12;
    else
      v6 = 0;
    v7 = v6 + v5;
    v39 = v6 + v5;
    if ( (int)(v6 + v5) < 0 )
      v7 = 0;
    v8 = (_DWORD *)v35;
    v34 = (_DWORD *)operator new(12 * v7);
    v9 = (_DWORD *)v34;
    for ( k = (_DWORD *)v1[1]; k != (_DWORD *)v35; v9 += 3 )
    {
      if ( v9 )
      {
        *v9 = *k;
        v9[1] = (unsigned long)k[1];
        v9[2] = (unsigned long)k[2];
      }
      k += 3;
    }
    v11 = (_DWORD *)v9;
    if ( v3 )
    {
      v36 = v3;
      do
      {
        if ( v11 )
        {
          *v11 = *v41;
          v11[1] = (unsigned long)v41[1];
          v11[2] = (unsigned long)v41[2];
        }
        v11 += 3;
        --v36;
      }
      while ( v36 );
    }
    v12 = (_DWORD *)v1[2];
    v13 = (_DWORD *)&v9[3 * v3];
    if ( v8 != v12 )
    {
      v14 = (_DWORD *)v8;
      do
      {
        if ( v13 )
        {
          *v13 = *v14;
          v13[1] = (unsigned long)v14[1];
          v13[2] = (unsigned long)v14[2];
        }
        v14 += 3;
        v13 += 3;
      }
      while ( v14 != v12 );
    }
    operator delete((void *)v33[1]);
    result = (unsigned long)v33[1];
    v33[3] = (_DWORD)&v34[3 * v39];
    if ( result )
    {
      v16 = (unsigned long)v33[2];
      v33[1] = (_DWORD)v34;
      v17 = v16 - result;
      result = (unsigned int)((unsigned __int64)(715827883i64 * (v16 - result)) >> 32) >> 31;
      v3 += v17 / 12;
    }
    else
    {
      v33[1] = (_DWORD)v34;
    }
    v33[2] = (_DWORD)&v34[3 * v3];
  }
  return result;
}

// 0x00411E00
void RoleSystem::ApplyMoveStep(double fInput, int nVal, float fVal, char bCollide)
{
    unsigned long reg_EAX = 0;
    RoleSystem *reg_ESI = this;

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
  reg_ESI = this;
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
    fmul    dword ptr [flt_56A648]
  }
  pB.z = v18;
  // __asm { fstp    dword ptr [esp+0x1C+fInput] }
  (((gbVec3D *)&pB))->gbVec3D::Length();
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
  reg_EAX = (unsigned long)(&reg_ESI[1].m_partyActor.m_fSpeed + 2);
  __asm
  {
    fstp    st
    fld     [esp+0x1C+pB]
  }
  *((_DWORD *)&reg_ESI[1].m_partyActor.m_fSpeed + 2) = this->m_fontcolor.Color;
  *((_DWORD *)&reg_ESI[1].m_partyActor.m_fSpeed + 3) = this->m_wndcolor.Color;
  LODWORD(reg_ESI[1].m_partyActor.m_fAngleDeg) = this->m_id;
  __asm { fadd    dword ptr [eax] }
  __asm { fstp    dword ptr [eax] }
  // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EAX = _ET1;` 已由上方 asm 存储覆盖

  __asm
  {
    fld     [esp+0x1C+var_14]
    fadd    dword ptr [eax+4]
    fstp    dword ptr [eax+4]
  }
  reg_EAX[1] = _ET1;
  __asm
  {
    fld     [esp+0x1C+var_10]
    fadd    dword ptr [eax+8]
    fstp    dword ptr [eax+8]
  }
  reg_EAX[2] = _ET1;
  if ( BYTE4(fInput) )
  {
    LODWORD(v13) = (unsigned long)((char *)this + 8692);
    (((RoleSystem *)this))->RoleSystem::UpdateMovement(v13, (gbVec3D *)LODWORD(pB.x));
    if ( v12 )
    {
      (((RoleSystem *)this))->RoleSystem::UpdatePosition();
      (((RoleSystem *)this))->RoleSystem::SetMoveSpeed(0.0, reg_ESI == g_pRoleSystem, v14);
    }
  }
  else
  {
    this->m_fCachePosX = this->m_fPosX;
    this->m_fCachePosY = this->m_fPosY;
    this->m_fCachePosZ = this->m_fPosZ;
    this->m_fontcolor.Color = *(unsigned int *)reg_EAX;
    this->m_wndcolor.Color = *((_DWORD *)&reg_ESI[1].m_partyActor.m_fSpeed + 3);
    this->m_id = LODWORD(reg_ESI[1].m_partyActor.m_fAngleDeg);
    (((RoleSystem *)this))->RoleSystem::UpdatePosition();
    (((RoleSystem *)this))->RoleSystem::SetMoveSpeed(0.0, reg_ESI == g_pRoleSystem, SHIDWORD(v13));
  }
}

// 0x00412230
void RoleSystem::SetMoveSpeed(float fSpeed, int nRoleIndex, int nFlag)
{
  RoleSystem *v5; // eax
  int m_nState; // [esp-0x10] [ebp-0x14]
if ( !this->m_partyActor.m_nPathEnabled )
  {
    this->m_nDispFontColor = this->m_fontcolor.Color;
    this->m_nDispWndColor = this->m_wndcolor.Color;
    this->m_nTodo_9C = this->m_id;
    m_nState = this->m_partyActor.m_nState;
    v5 = (RoleSystem *)UISceneUpdate();
    (((RoleSystem *)v5))->RoleSystem::SetRoleParam(m_nState, (float *)&this->m_fontcolor.Color, (int *)&this->m_bRenderFlag2, 0);
    // __asm { fstp    dword ptr [esi+0x98] }
    *(float *)&this->m_nDispWndColor = _ET1;
    if ( fSpeed == 0.0f )
    {
      LODWORD(this->m_fPosX) = this->m_nDispFontColor;
      LODWORD(this->m_fPosY) = this->m_nDispWndColor;
      LODWORD(this->m_fPosZ) = this->m_nTodo_9C;
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
  float v3; // st7
  float v4; // st6
  float v5; // st5
  long double v6; // st7
  float v7; // [esp+0x8] [ebp-0x8]
  int v8; // [esp+0xC] [ebp-0x4]

  if ( this->m_nMoveSubMode != 8 )
  {
    p_top = (LONG *)&this->m_rect.top;
    this->m_rect.top = LODWORD(this->m_fRotAxisX);
    this->m_rect.right = LODWORD(this->m_fRotAxisY);
    this->m_rect.bottom = LODWORD(this->m_fRotAxisZ);
    (((gbVec3D *)&this->m_rect.top))->gbVec3D::Normalize();
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
    (((gbVec3D *)&this->m_pfather))->gbVec3D::Normalize();
    if ( (byte_C10DA4 & 1) == 0 )
    {
      dword_C10D98 = 0;
      byte_C10DA4 |= 1u;
      dword_C10D9C = 0;
      dword_C10DA0 = 1065353216;
      atexit(nullsub_4);
    }
    v6 = acos(
           *(float *)&dword_C10DA0 * *(float *)&this->m_rect.bottom
         + *(float *)&dword_C10D9C * *(float *)&this->m_rect.right
         + *(float *)&dword_C10D98 * *(float *)&this->m_rect.top);
    *(&this[1].m_partyActor.m_fSpeed + 1) = v6;
    if ( *(float *)p_top < 0.0f )
      *(&this[1].m_partyActor.m_fSpeed + 1) = 6.2831855 - v6;
    *(&this[1].m_partyActor.m_fSpeed + 1) = *(&this[1].m_partyActor.m_fSpeed + 1) * 57.29578;
  }
}

// 0x00412400
void RoleSystem::RenderRole(gbMatrixStack *pStack, int nVal)
{
  gbMatrix4 v4; // [esp+0x38] [ebp-0x40] BYREF

  if ( this->m_partyActor.m_pRoleObj )
  {
    if ( (byte_C10D94 & 1) == 0 )
    {
      dword_C10D88.x = 0.0;
      byte_C10D94 |= 1u;
      dword_C10D8C = 1065353216;
      dword_C10D90 = 0;
      atexit(nullsub_5);
    }
    (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
    (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_fPosX);
    if ( this->m_nMoveMode == 4 && *(&this->m_partyActor.m_nUpdateMode + 5) == 11 )
      (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->m_FrameA.m_rect.bottom, * (gbVec3D *)&this->m_fRotAxisX);
    (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(&this[1].m_partyActor.m_fSpeed + 1),  dword_C10D88);
    (((gbMatrixStack *)pStack))->gbMatrixStack::Scale(*(float *)&this->m_partyActor.m_fScale,   *(float *)&this->m_partyActor.m_fScale,   *(float *)&this->m_partyActor.m_fScale);
    this->m_nActionResult = (((Actor *)&this->m_partyActor.m_Actor))->Actor::DispatchAction(nVal);
    if ( this->m_pRenderObj )
    {
      if ( BYTE1(this->m_bRenderFlag1) )
      {
        (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
        (((gbActor *)this->m_partyActor.m_pActor))->gbActor::GetTagNodeTM(&v4, "tag_weapon1");
        (((gbMatrixStack *)pStack))->gbMatrixStack::MultMatrix(&v4);
        (*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)((gbChain1DNode *)this->m_pRenderObj) + 16))(
          this->m_pRenderObj,
          0);
        (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
      }
      if ( LOBYTE(this->m_bRenderFlag1) )
      {
        (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
        (((gbActor *)this->m_partyActor.m_pActor))->gbActor::GetTagNodeTM(&v4, "tag_weapon2");
        (((gbMatrixStack *)pStack))->gbMatrixStack::MultMatrix(&v4);
        (*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)((gbChain1DNode *)this->m_pRenderObj) + 16))(
          this->m_pRenderObj,
          0);
        (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
      }
    }
    (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
  }
}

// 0x004125B0
int RoleSystem::NotifySceneChange(int nVal1)
{
  int result; // eax

  UISceneUpdate();
  result = nVal1;
  this->m_partyActor.m_nState = nVal1;
  return result;
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
  __int64 m_nCoreState; // rax
  char m_nActionState; // al
  int v4; // [esp-0x4] [ebp-0xC]
  int v5; // [esp-0x4] [ebp-0xC]
  int v6; // [esp-0x4] [ebp-0xC]
  int v7; // [esp-0x4] [ebp-0xC]

  m_nCoreState = (unsigned int)this->m_nCoreState;
  if ( (unsigned int)m_nCoreState > 0x3A )
    this->m_nCoreState = 0;
  switch ( this->m_nCoreState )
  {
    case 0:
    case 5:
    case 7:
      this->m_nTransformState = 0.0f;
      this->m_fMovement = 0.0f;
      this->m_fRotAxisX = 0.0f;
      this->m_fRotAxisY = 0.0f;
      this->m_fRotAxisZ = 0.0f;
      this->m_nMovement = 0.0f;
      this->m_fSavedRotX = this->m_fRotAxisY;
      *(float *)((UIWnd *)&this->m_FrameA) = this->m_fRotAxisZ;
      return this->RoleSystem::UpdatePath(this->m_nCoreState);
    case 1:
    case 3:
      LODWORD(this->m_fMovement) = g_RoleSystemData._todo_154;
      m_nActionState = this->m_nActionState;
      if ( m_nActionState == -1 )
      {
        HIDWORD(m_nCoreState) = g_RoleSystemData._todo_17C;
LABEL_7:
        this->m_nTransformState = *((float *)&m_nCoreState + 1);
        return this->RoleSystem::UpdatePath(this->m_nCoreState);
      }
      if ( m_nActionState == 2 )
      {
        if ( this->m_nTransformMode == 1 )
        {
          if ( this->m_pLinkedSystem[756] == 1 )
          {
            v5 = this->m_nCoreState;
            LODWORD(this->m_nTransformState) = g_RoleSystemData.m_nEffParamDC;
            return this->RoleSystem::UpdatePath(v5);
          }
          else if ( this->m_pLinkedSystem[756] == 2 )
          {
            LODWORD(this->m_nTransformState) = g_RoleSystemData.m_nEffParamF0;
            return this->RoleSystem::UpdatePath(this->m_nCoreState);
          }
          else
          {
            v4 = this->m_nCoreState;
            LODWORD(this->m_nTransformState) = g_RoleSystemData.m_nEffParamC8;
            return this->RoleSystem::UpdatePath(v4);
          }
        }
        else
        {
          switch ( this->m_pLinkedSystem[755] )
          {
            case 0:
              goto LABEL_7;
            case 1:
              LODWORD(this->m_nTransformState) = g_RoleSystemData.m_nEffParam3C;
              return this->RoleSystem::UpdatePath(this->m_nCoreState);
            case 2:
              v6 = this->m_nCoreState;
              LODWORD(this->m_nTransformState) = g_RoleSystemData.m_nEffParam50;
              return this->RoleSystem::UpdatePath(v6);
            default:
              LODWORD(this->m_nTransformState) = g_RoleSystemData._todo_064;
              return this->RoleSystem::UpdatePath(this->m_nCoreState);
          }
        }
      }
      else
      {
        LODWORD(m_nCoreState) = this->m_partyActor.m_nTransform;
        v7 = this->m_nCoreState;
        if ( (_DWORD)m_nCoreState == HIDWORD(m_nCoreState) )
          this->m_nTransformState = *(&g_RoleSystemData._todo_118 + 5);
        else
          this->m_nTransformState = (float)m_nCoreState;
        return this->RoleSystem::UpdatePath(v7);
      }
    case 2:
      LODWORD(this->m_nTransformState) = g_RoleSystemData._todo_190;
      LODWORD(this->m_fMovement) = g_RoleSystemData._todo_168;
      return this->RoleSystem::UpdatePath(this->m_nCoreState);
    default:
      return this->RoleSystem::UpdatePath(this->m_nCoreState);
  }
}

// 0x00412940
int RoleSystem::UpdatePath(int nVal)
{
  int AnimOffset; // ebp
  int *p_m_Actor; // edi
  int result; // eax
  int v6; // [esp-0x8] [ebp-0x14]

  if ( this->m_nAnimState == 49 )
  {
    (((Actor *)&this->m_partyActor.m_Actor))->Actor::CompareActionName(nVal, 2);
    (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(1.0);
    BYTE1(this->m_bRenderFlag1) = 0;
    LOBYTE(this->m_bRenderFlag1) = 0;
    return result;
  }
  AnimOffset = RoleSystem::GetAnimOffset(nVal, this->m_nActionState);
  if ( this->m_nAnimState == 50 )
    goto LABEL_10;
  if ( AnimOffset == 50 )
  {
    p_m_Actor = (int *)&this->m_partyActor.m_Actor;
    if ( !SetMaterialName((Actor *)&this->m_partyActor.m_Actor, "z0", 0) )
      (((Actor *)p_m_Actor))->Actor::CompareActionName(50, 0);
    goto LABEL_12;
  }
  if ( AnimOffset != 52 && AnimOffset != 58 )
  {
LABEL_10:
    p_m_Actor = (int *)&this->m_partyActor.m_Actor;
    v6 = 2;
    goto LABEL_11;
  }
  p_m_Actor = (int *)&this->m_partyActor.m_Actor;
  if ( !SetMaterialName((Actor *)&this->m_partyActor.m_Actor, "z4", 0) )
  {
    v6 = 0;
LABEL_11:
    (((Actor *)p_m_Actor))->Actor::CompareActionName(AnimOffset, v6);
  }
LABEL_12:
  if ( this->m_nCoreState == 2 )
    (((Actor *)p_m_Actor))->Actor::SetTimeScale(2.4000001);
  else
    (((Actor *)p_m_Actor))->Actor::SetTimeScale(1.0);
  BYTE1(this->m_bRenderFlag1) = 0;
  LOBYTE(this->m_bRenderFlag1) = 0;
  return result;
}

// 0x00412A50
int RoleSystem::StartHalfSpeedMovement()
{
  int result; // eax

  this->m_nMoveSubMode = 1;
  this->m_nCoreState = 1;
  result = this->RoleSystem::UpdateTransform();
  this->m_nTransformState = this->m_nTransformState * 0.5f;
  this->m_fMovement = this->m_fMovement * 0.5f;
  return result;
}

// 0x00412A90
void RoleSystem::MoveToTile(__int64 tileXY, int nMode)
{
  int m_nState; // eax
  RoleSystem *v5; // eax
  int RolePtr; // edi
  float v7; // st7
  float v8; // st6
  int v9; // [esp-0x4] [ebp-0x28]
  float pTargetPos; // [esp+0xC] [ebp-0x18] BYREF
  int v11; // [esp+0x10] [ebp-0x14]
  float v12; // [esp+0x14] [ebp-0x10]
  float v13; // [esp+0x20] [ebp-0x4]

  pTargetPos = 0.0f;
  v11 = 0;
  m_nState = this->m_partyActor.m_nState;
  v12 = 0.0f;
  v9 = m_nState;
  v5 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v5))->RoleSystem::GetRolePtr(v9);
  if ( __PAIR64__(
         (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize),
         (__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize)) != tileXY )
  {
    v7 = ((float)(int)tileXY + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 128);
    v8 = ((float)SHIDWORD(tileXY) + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 136);
    v11 = 0;
    v13 = v8;
    pTargetPos = v7;
    v12 = v13;
    this->RoleSystem::SetMoveTarget(&pTargetPos, nMode);
  }
}

// 0x00412B60
void RoleSystem::SetMoveTarget(float *pTargetPos, int nFlags)
{
  float v4; // st7
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
  if ( (((gbVec3D *)&v6))->gbVec3D::Length() >= 12.0 )
  {
    this->m_nMoveSubMode = 4;
    this->m_nCoreState = nFlags;
    this->m_FrameA.m_rect.bottom = *(LONG *)pTargetPos;
    this->m_FrameA.m_pfather = ((UIWnd *)((UIWnd *)pTargetPos[1]));
    this->m_FrameA.m_childs.m_pData = ((char *)((char *)pTargetPos[2]));
    this->m_FrameA.m_childs.m_needscriptdel = this->m_fontcolor.Color;
    this->m_FrameA.m_bcreateok = this->m_wndcolor.Color;
    this->m_FrameA.m_bvisible = this->m_id;
    this->m_FrameA.m_pfather = ((UIWnd *)0);
    this->m_FrameA.m_bcreateok = 0;
    this->RoleSystem::UpdateTransform();
  }
  else
  {
    this->m_nMoveSubMode = 0;
  }
}

// 0x00412C30
int RoleSystem::SetPathWaypoint(float fVal)
{
  long double v2; // st7
  int result; // eax
  float v4; // [esp+0x4] [ebp-0x8]
  float v5; // [esp+0x8] [ebp-0x4]

  v2 = *(&this[1].m_partyActor.m_fSpeed + 1) * 0.017453292;
  this->m_nMoveSubMode = 8;
  this->m_fRotAxisY = 0.0f;
  this->m_fRotAxisX = sin(v2);
  this->m_fRotAxisZ = cos(v2);
  this->m_fRotAxisX = this->m_fRotAxisX * -1.0f;
  this->m_fRotAxisY = this->m_fRotAxisY * -1.0f;
  this->m_fRotAxisZ = this->m_fRotAxisZ * -1.0f;
  this->m_FrameA.m_childs.m_needscriptdel = this->m_fontcolor.Color;
  this->m_FrameA.m_bcreateok = this->m_wndcolor.Color;
  this->m_FrameA.m_bvisible = this->m_id;
  this->m_FrameA.m_rect.bottom = this->m_fontcolor.Color;
  this->m_FrameA.m_pfather = ((UIWnd *)((UIWnd *)this->m_wndcolor.Color));
  this->m_FrameA.m_childs.m_pData = ((char *)((char *)this->m_id));
  v4 = fVal * this->m_fRotAxisY;
  v5 = fVal * this->m_fRotAxisZ;
  *(float *)&this->m_FrameA.m_rect.bottom = fVal * this->m_fRotAxisX + *(float *)&this->m_FrameA.m_rect.bottom;
  *(float *)&this->m_FrameA.m_pfather = v4 + *(float *)&this->m_FrameA.m_pfather;
  *(float *)&this->m_FrameA.m_childs.m_pData = v5 + *(float *)&this->m_FrameA.m_childs.m_pData;
  this->m_FrameA.m_pfather = ((UIWnd *)0);
  this->m_FrameA.m_bcreateok = 0;
  this->m_fRotAxisX = this->m_fRotAxisX * 70.0f;
  this->m_fRotAxisY = this->m_fRotAxisY * 70.0f;
  this->m_fRotAxisZ = this->m_fRotAxisZ * 70.0f;
  this->m_nMovement = this->m_fRotAxisX;
  this->m_fSavedRotX = this->m_fRotAxisY;
  result = LODWORD(this->m_fRotAxisZ);
  *(_DWORD *)((UIWnd *)&this->m_FrameA) = result;
  return result;
}

// 0x00412D90
char RoleSystem::BindPartyToScene(float *pfVal, int nVal)
{
  float *p_Color; // ecx
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  int m_nCoreState; // ecx

  p_Color = (float *)&this->m_fontcolor.Color;
  if ( !(v6 | v7) )
    return 1;
  if ( (((RoleSystem *)&g_pathFinder))->RoleSystem::BindRoleToScene(this->m_partyActor.m_nState, p_Color, pfVal, (int)&this->m_fMoveTargetX, this->m_nFacing) )
  {
    m_nCoreState = this->m_nCoreState;
    this->m_nMoveSubMode = 2;
    if ( m_nCoreState != nVal )
    {
      this->m_nCoreState = nVal;
      this->RoleSystem::UpdateTransform();
    }
    return 1;
  }
  else
  {
    this->RoleSystem::NotifyMoveComplete();
    return 0;
  }
}

// 0x00412E60
int RoleSystem::MoveRole(float *pPos, int nVal, int nVal2, int nVal3)
{
  int result; // eax
  int m_nMoveSubMode; // ecx
  RoleSystem *v8; // eax
  int RolePtr; // ebx
  RoleSystem *v10; // eax
  int v11; // edx
  int *v12; // [esp-0x18] [ebp-0x34]
  char *v13; // [esp-0x14] [ebp-0x30]
  int v14; // [esp-0x10] [ebp-0x2C]
  char *v15; // [esp-0xC] [ebp-0x28]
  int m_nState; // [esp-0x8] [ebp-0x24]
  int v17; // [esp-0x8] [ebp-0x24]

  this->m_FrameA.m_rect.bottom = *(LONG *)pPos;
  result = nVal;
  this->m_FrameA.m_pfather = ((UIWnd *)((UIWnd *)pPos[1]));
  this->m_FrameA.m_childs.m_pData = ((char *)((char *)pPos[2]));
  m_nMoveSubMode = this->m_nMoveSubMode;
  this->m_FrameA.m_childs.capacity = nVal;
  this->m_nMoveRole = 1;
  if ( m_nMoveSubMode != 2 )
  {
    LOBYTE(result) = this->RoleSystem::UpdateRole(pPos, nVal, nVal2);
    this->m_nRetryCount = 0;
    return result;
  }
  if ( nVal == this->m_partyActor.m_nState )
  {
    m_nState = this->m_partyActor.m_nState;
    v8 = (RoleSystem *)UISceneUpdate();
    RolePtr = (((RoleSystem *)v8))->RoleSystem::GetRolePtr(m_nState);
    v17 = (__int64)((pPos[2] - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
    v15 = (char *)(__int64)((*pPos - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
    v14 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
    v13 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
    v12 = (int *)this->m_partyActor.m_nState;
    v10 = (RoleSystem *)UISceneUpdate();
    if ( (((RoleSystem *)v10))->RoleSystem::AdvanceOnPath(v12, v13, v14, v15, v17) )
    {
      this->m_partyUI3.m_pfather = ((UIWnd *)((UIWnd *)2));
      LODWORD(this->m_fMoveTargetX) = this->m_fontcolor.Color;
      this->m_fMoveTargetY = this->m_wndcolor.Color;
      LODWORD(this->m_fMoveTargetZ) = this->m_id;
      this->m_fMoveRole = *pPos;
      this->m_fMoveParamY = pPos[1];
      this->m_fMoveParamZ = pPos[2];
      return (((PathObj *)&this->m_fMoveTargetX))->PathObj::CalcLength();
    }
    result = nVal;
  }
  if ( nVal3 || (v11 = this->m_nRetryCount + 1, this->m_nRetryCount = v11, v11 > 30) )
  {
    this->m_nRetryCount = 0;
    LOBYTE(result) = this->RoleSystem::UpdateRole(pPos, result, nVal2);
  }
  return result;
}

// 0x00413010
char RoleSystem::UpdateRole(float *pfVal, int nVal, int nVal2)
{
  char *v5; // eax
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
  char *v16; // eax
  int m_nState; // [esp-0x4] [ebp-0x48]
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

  if ( nVal == this->m_partyActor.m_nState )
  {
    LOBYTE(v5) = this->RoleSystem::BindPartyToScene(pfVal, nVal2);
  }
  else
  {
    m_nState = this->m_partyActor.m_nState;
    v6 = (RoleSystem *)UISceneUpdate();
    RolePtr = (((RoleSystem *)v6))->RoleSystem::GetRolePtr(m_nState);
    v21 = RolePtr;
    v24 = (__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
    v8 = v22;
    v9 = 0x7FFFF;
    v25 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
    v20 = 0x7FFFF;
    v19 = 0;
    v10 = (int *)(RolePtr + 8);
    do
    {
      v11 = *(v10 - 2);
      v12 = (unsigned long)*v10;
      if ( v11 != *v10 || v12 )
      {
        v8 = (v12 + v11) / 2;
        v13 = (unsigned long)(v10[1] + *(v10 - 1));
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
          this->m_FrameA.m_childs.m_nSize = v19;
        }
      }
      v10 += 4;
      LOBYTE(v5) = ++v19;
    }
    while ( v19 < 8 );
    if ( v9 <= 32 )
    {
      v29 = 0.0f;
      v28 = ((float)v22 + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 128);
      v30 = ((float)v23 + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 136);
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
        this->RoleSystem::PlaceAtRegion(nVal, this->m_FrameA.m_childs.m_nSize);
        LOBYTE(v5) = this->RoleSystem::BindPartyToScene(pfVal2, nVal2);
      }
      else
      {
        v16 = (char *)LODWORD(v27);
        *(float *)&this->m_FrameA.m_rect.bottom = pfVal2[0];
        this->m_FrameA.m_pfather = ((UIWnd *)0);
        this->m_FrameA.m_childs.m_pData = ((char *)(v16));
        if ( (((RoleSystem *)&g_pathFinder))->RoleSystem::BindRoleToScene(this->m_partyActor.m_nState, (float *)&this->m_fontcolor.Color, pfVal2, (int)&this->m_fMoveTargetX, this->m_nFacing) )
        {
          this->m_nMoveSubMode = 7;
          this->m_nCoreState = nVal2;
          this->RoleSystem::UpdateTransform();
          this->m_FrameA.m_rect.bottom = *(LONG *)pfVal;
          this->m_FrameA.m_pfather = ((UIWnd *)((UIWnd *)pfVal[1]));
          v5 = (char *)*((_DWORD *)pfVal + 2);
          this->m_FrameA.m_childs.m_pData = ((char *)(v5));
          this->m_FrameA.m_pfather = ((UIWnd *)0);
          this->m_FrameA.m_childs.capacity = nVal;
        }
        else
        {
          LOBYTE(v5) = this->RoleSystem::NotifyMoveComplete();
        }
      }
    }
  }
  return (char)v5;
}

// 0x004132B0
char RoleSystem::MoveToTileCheck(int nTileX, int nTileY, int nMode)
{
  int m_nState; // eax
  RoleSystem *v6; // eax
  int RolePtr; // edi
  float v9; // st7
  float v10; // st6
  int v11; // [esp-0x4] [ebp-0x28]
  float pfVal; // [esp+0xC] [ebp-0x18] BYREF
  int v13; // [esp+0x10] [ebp-0x14]
  float v14; // [esp+0x14] [ebp-0x10]
  float v15; // [esp+0x20] [ebp-0x4]

  pfVal = 0.0f;
  v13 = 0;
  m_nState = this->m_partyActor.m_nState;
  v14 = 0.0f;
  v11 = m_nState;
  v6 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v6))->RoleSystem::GetRolePtr(v11);
  if ( (unsigned int)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize) == nTileX
    && (unsigned int)(__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize) == nTileY )
  {
    return 1;
  }
  v9 = ((float)nTileX + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 128);
  v10 = ((float)nTileY + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 136);
  v13 = 0;
  v15 = v10;
  pfVal = v9;
  v14 = v15;
  return this->RoleSystem::BindPartyToScene(&pfVal, nMode);
}

// 0x00413390
void RoleSystem::InterpolateMoveFrame(float fVal)
{
  float v3; // st7
  float *p_m_nMovement; // esi
  float v5; // st6
  float v6; // st7
  float v7; // [esp+0xC] [ebp-0x8]
  float v8; // [esp+0x10] [ebp-0x4]

  v3 = *(float *)&this->m_FrameA.m_rect.bottom - *(float *)&this->m_fontcolor.Color;
  p_m_nMovement = (float *)&this->m_nMovement;
  v7 = *(float *)&this->m_FrameA.m_pfather - *(float *)&this->m_wndcolor.Color;
  v5 = *(float *)&this->m_FrameA.m_childs.m_pData - *(float *)&this->m_id;
  this->m_fSavedRotX = v7;
  v8 = v5;
  this->m_nMovement = v3;
  *(float *)((UIWnd *)&this->m_FrameA) = v8;
  v6 = this->m_nTransformState / (((gbVec3D *)&this->m_nMovement))->gbVec3D::Length();
  *p_m_nMovement = v6 * *p_m_nMovement;
  p_m_nMovement[1] = v6 * p_m_nMovement[1];
  p_m_nMovement[2] = v6 * p_m_nMovement[2];
  *p_m_nMovement = fVal * *p_m_nMovement;
  p_m_nMovement[1] = fVal * p_m_nMovement[1];
  p_m_nMovement[2] = fVal * p_m_nMovement[2];
  this->RoleSystem::NormalizeDirection(p_m_nMovement);
}

// 0x00413420
int RoleSystem::StepAlongPath(double fStepSize, float fVal)
{
  float v4; // st7
  gbVec3D *p_m_fontcolor; // edi
  float *p_m_fMoveTargetX; // ebx
  float v7; // st6
  float v8; // st7
  int v9; // eax
  int result; // eax
  double m_nTransformState; // st7
  float v12; // st7
  char *v13; // eax
  gbVec3D *v14; // ebx
  float v15; // st7
  float v16; // st7
  float *v17; // eax
  float v18; // st7
  float v19; // st7
  float v20; // edx
  float v21; // eax
  gbVec3D *v22; // eax
  float v23; // [esp+0x4] [ebp-0x7C]
  float v24; // [esp+0x8] [ebp-0x78]
  float v25; // [esp+0xC] [ebp-0x74]
  float v26; // [esp+0x1C] [ebp-0x64]
  float v27; // [esp+0x1C] [ebp-0x64]
  int v28; // [esp+0x20] [ebp-0x60] BYREF
  float v29; // [esp+0x24] [ebp-0x5C]
  float v30; // [esp+0x28] [ebp-0x58]
  float v31; // [esp+0x2C] [ebp-0x54] BYREF
  float v32; // [esp+0x30] [ebp-0x50]
  float v33; // [esp+0x34] [ebp-0x4C]
  gbVec3D v34; // [esp+0x38] [ebp-0x48] BYREF
  _DWORD v35[3]; // [esp+0x44] [ebp-0x3C] BYREF
  float v36[3]; // [esp+0x50] [ebp-0x30] BYREF
  struct gbVec3D v37; // [esp+0x5C] [ebp-0x24] BYREF
  gbVec3D pOut; // [esp+0x68] [ebp-0x18] BYREF
  gbVec3D v39; // [esp+0x74] [ebp-0xC] BYREF
  float fStepSizea; // [esp+0x84] [ebp+0x4]
  float fStepSizeb; // [esp+0x84] [ebp+0x4]

  v26 = 12.0f * 3.0f;
  v4 = 12.0f * 3.0f * *(float *)&this->m_rect.top;
  p_m_fontcolor = (gbVec3D *)&this->m_fontcolor;
  p_m_fMoveTargetX = (float *)&this->m_fMoveTargetX;
  v34.y = v26 * *(float *)&this->m_rect.right;
  v7 = v26 * *(float *)&this->m_rect.bottom;
  memset(v35, 0, sizeof(v35));
  v34.z = v7;
  v8 = v4 + *(float *)&this->m_fontcolor.Color;
  v31 = 0.0f;
  v32 = 0.0f;
  v33 = 0.0f;
  v36[0] = v8;
  v36[1] = v34.y + *(float *)&this->m_wndcolor.Color;
  v36[2] = v34.z + *(float *)&this->m_id;
  v9 = sub_407EC0(v36, v35, &v31);
  v31 = v31 * *(float *)&fStepSize;
  v32 = v32 * *(float *)&fStepSize;
  v33 = v33 * *(float *)&fStepSize;
  if ( v9
    && v33 * *(float *)&this->m_rect.bottom + v32 * *(float *)&this->m_rect.right + v31 * *(float *)&this->m_rect.top > 0.5 )
  {
    LODWORD(this->m_nMovement) = this->m_rect.top;
    LODWORD(this->m_fSavedRotX) = this->m_rect.right;
    *(_DWORD *)((UIWnd *)&this->m_FrameA) = this->m_rect.bottom;
    result = 0;
    m_nTransformState = this->m_nTransformState;
    this->m_nMovement = m_nTransformState * this->m_nMovement;
    this->m_fSavedRotX = m_nTransformState * this->m_fSavedRotX;
    *(float *)((UIWnd *)&this->m_FrameA) = m_nTransformState * *(float *)((UIWnd *)&this->m_FrameA);
    return result;
  }
  *(float *)&v28 = 0.0;
  v29 = 0.0f;
  v30 = 0.0f;
  v12 = sub_408010(p_m_fontcolor) + v26 * *(float *)&fStepSize;
  if ( *(float *)&fStepSize > 0.0f )
  {
    if ( v12 >= *(float *)&this->m_partyUI3.m_childs.m_pData )
    {
      v13 = (char *)this + 12 * (int)this->m_partyUI3.m_pfather;
      v14 = (gbVec3D *)(v13 + 1456);
      v34 = *Vec3Cross(&pOut, (gbVec3D *)(v13 + 1468), (gbVec3D *)(v13 + 1456));
      v37 = *Vec3Cross(&v39, p_m_fontcolor, v14);
      v15 = (((gbVec3D *)&v34))->gbVec3D::Length();
      fStepSizea = v15;
      if ( v15 < 0.000049999999f )
        return 1;
      v16 = (((gbVec3D *)&v34))->gbVec3D::DotProduct(&v37) / fStepSizea;
      if ( v16 >= 0.0f && v16 - fStepSizea > -0.1 )
        return 1;
      v17 = (float *)(&this->m_fCachePosX + 3 * (int)this->m_partyUI3.m_pfather);
      v28 = *(int *)v17;
      v29 = v17[1];
      v30 = v17[2];
      goto LABEL_18;
    }
    goto LABEL_6;
  }
  if ( v12 > 0.0f )
  {
LABEL_6:
    v27 = v12;
    sub_4080F0(v27, (int)&v28);
    goto LABEL_18;
  }
  v34 = *Vec3Cross(&v39, (gbVec3D *)p_m_fMoveTargetX, (gbVec3D *)&this->m_fMoveRole);
  v37 = *Vec3Cross(&pOut, p_m_fontcolor, (gbVec3D *)&this->m_fMoveRole);
  v18 = (((gbVec3D *)&v34))->gbVec3D::Length();
  fStepSizeb = v18;
  if ( v18 < 0.000049999999f )
    return 1;
  v19 = (((gbVec3D *)&v34))->gbVec3D::DotProduct(&v37) / fStepSizeb;
  if ( v19 >= 0.0f && v19 - fStepSizeb > -0.1 )
    return 1;
  v20 = p_m_fMoveTargetX[1];
  v21 = p_m_fMoveTargetX[2];
  v28 = *(int *)p_m_fMoveTargetX;
  v29 = v20;
  v30 = v21;
LABEL_18:
  v25 = v30 - p_m_fontcolor->z;
  v24 = v29 - p_m_fontcolor->y;
  v23 = *(float *)&v28 - p_m_fontcolor->x;
  v37 = *v22;
  (((gbVec3D *)&this->m_nMovement))->gbVec3D::operator=(*(&v37));
  (((gbVec3D *)&this->m_nMovement))->gbVec3D::Normalize();
  (((gbVec3D *)&this->m_nMovement))->gbVec3D::operator*=(this->m_nTransformState);
  return 0;
}

// 0x00413850
double RoleSystem::AdvanceToTarget(double fDelta)
{
    unsigned long reg_EAX = 0;
    unsigned long reg_EBX = 0;
    unsigned long reg_EDI = 0;
    RoleSystem *reg_ESI = this;

  float result; // st7
  gbVec3D *v12; // eax
  _DWORD *v16; // ecx
  int v17; // eax
  int *v18; // eax
  float z; // edx
  float v24; // [esp+0x0] [ebp-0x7C]
  float v25; // [esp+0x4] [ebp-0x78]
  double v26; // [esp+0x8] [ebp-0x74]
  float v27; // [esp+0x8] [ebp-0x74]
  int v28; // [esp+0xC] [ebp-0x70]
  gbVec3D *v29; // [esp+0x10] [ebp-0x6C]
  float v31; // [esp+0x18] [ebp-0x64]
  int v33; // [esp+0x1C] [ebp-0x60] BYREF
  int v34; // [esp+0x20] [ebp-0x5C]
  int v35; // [esp+0x24] [ebp-0x58]
  LONG bottom; // [esp+0x28] [ebp-0x54] BYREF
  UIWnd *m_pfather; // [esp+0x2C] [ebp-0x50]
  char *v38; // [esp+0x30] [ebp-0x4C]
  gbVec3D v39; // [esp+0x34] [ebp-0x48] BYREF
  _DWORD v40[3]; // [esp+0x40] [ebp-0x3C] BYREF
  float v41[3]; // [esp+0x4C] [ebp-0x30] BYREF
  struct gbVec3D v42; // [esp+0x58] [ebp-0x24] BYREF
  gbVec3D v43; // [esp+0x64] [ebp-0x18] BYREF
  gbVec3D pOut; // [esp+0x70] [ebp-0xC] BYREF

  reg_ESI = this;
  if ( !this->m_nMoveRole )
    goto LABEL_24;
  bottom = this->m_FrameA.m_rect.bottom;
  // __asm { fld     [esp+0x70+var_54] }
  __asm
  {
    fsub    dword ptr [esi+4]
    fld     dword ptr [esi+8]
  }
  reg_EAX = this->m_FrameA.m_childs.m_pData;
  m_pfather = this->m_FrameA.m_pfather;
  __asm { fchs }
  v38 = reg_EAX;
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
  if ( (BYTE1(reg_EAX) & 0x41) != 0 )
  {
LABEL_24:
    if ( !this->m_nCollisionState || this->m_nActionResult )
    {
      __asm
      {
        fld     _flt_12_0
        fmul    _flt_3_0
      }
      reg_EDI = (unsigned long)&this->m_fontcolor;
      __asm
      {
        fst     [esp+0x74+var_64]
        fmul    dword ptr [esi+0x14]
        fld     [esp+0x74+var_64]
        fmul    dword ptr [esi+0x18]
      }
      memset(v40, 0, sizeof(v40));
      __asm
      {
        fstp    [esp+0x7C+var_48+4]
        fld     [esp+0x7C+var_64]
        fmul    dword ptr [esi+0x1C]
      }
      bottom = 0;
      m_pfather = 0;
      // __asm { fstp    [esp+0x7C+var_48+8] }
      v38 = 0;
      __asm
      {
        fadd    dword ptr [edi]
        fstp    [esp+0x7C+var_30]
        fld     [esp+0x7C+var_48+4]
        fadd    dword ptr [edi+4]
        fstp    [esp+0x7C+var_2C]
        fld     [esp+0x7C+var_48+8]
        fadd    dword ptr [edi+8]
        fstp    [esp+0x7C+var_28]
      }
      if ( sub_407EC0(v41, v40, &bottom) )
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
          reg_EDI = (unsigned long)&this->m_nMovement;
          LODWORD(this->m_nMovement) = this->m_rect.top;
          LODWORD(this->m_fSavedRotX) = this->m_rect.right;
          *(_DWORD *)((UIWnd *)&this->m_FrameA) = this->m_rect.bottom;
          // __asm { fld     dword ptr [esi+0x508] }
LABEL_20:
          __asm
          {
            fld     st
            fmul    dword ptr [edi]
          }
          __asm { fstp    dword ptr [edi] }
          // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EDI = _ET1;` 已由上方 asm 存储覆盖

          __asm
          {
            fld     st
            fmul    dword ptr [edi+4]
            fstp    dword ptr [edi+4]
          }
          reg_EDI[1] = _ET1;
          __asm
          {
            fmul    dword ptr [edi+8]
            fstp    dword ptr [edi+8]
          }
          reg_EDI[2] = _ET1;
          (((RoleSystem *)this))->RoleSystem::NormalizeDirection(reg_EDI);
          return result;
        }
      }
      v33 = 0;
      v34 = 0;
      v35 = 0;
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
        sub_4080F0(v31, (int)&v33);
LABEL_19:
        __asm
        {
          fld     [esp+0x70+var_60]
          fsub    dword ptr [edi]
          fld     [esp+0x70+var_5C]
          fsub    dword ptr [edi+4]
          fstp    [esp+0x70+var_24+4]
          fld     [esp+0x70+var_58]
          fsub    dword ptr [edi+8]
        }
        reg_EDI = (unsigned long)&this->m_nMovement;
        // __asm { fstp    [esp+0x70+var_24+8] }
        z = v42.z;
        this->m_fSavedRotX = v42.y;
        __asm { fstp    dword ptr [edi] }
        // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EDI = _ET1;` 已由上方 asm 存储覆盖

        *(float *)((UIWnd *)&this->m_FrameA) = z;
        (((gbVec3D *)&this->m_nMovement))->gbVec3D::Normalize();
        // __asm { fld     dword ptr [esi+0x508] }
        goto LABEL_20;
      }
      if ( this->m_nMoveRole )
      {
        (((RoleSystem *)this))->RoleSystem::MoveRole((float *)&this->m_FrameA.m_rect.bottom, this->m_FrameA.m_childs.capacity, this->m_nCoreState, 1);
        return result;
      }
      reg_EAX = 3 * (int)this->m_partyUI3.m_pfather;
      // __asm { fld     dword ptr [esi+eax*4+0x5C4] }
      reg_EAX = (unsigned long)(char *)this + 12 * (int)this->m_partyUI3.m_pfather;
      // __asm { fsub    dword ptr [eax+0x5B8] }
      reg_EBX = (unsigned long)(gbVec3D *)(reg_EAX + 1456);
      __asm
      {
        fstp    [esp+0x74+var_74]; float
        fld     dword ptr [eax+0x5C0]
        fsub    dword ptr [ebx+4]
      }
      __asm
      {
        fstp    [esp+0x78+var_78]; float
        fld     dword ptr [eax+0x5BC]
        fsub    dword ptr [ebx]
      }
      // __asm { fstp    [esp+0x7C+var_7C]; float }
      gbVec3D::gbVec3D(&v43, v24, v25, v27);
      v39 = *v12;
      v42 = *Vec3Cross(&pOut, (gbVec3D *)&this->m_fontcolor, reg_EBX);
      (((gbVec3D *)&v39))->gbVec3D::Length();
      __asm
      {
        fst     [esp+0x70+var_64]
        fcomp   dword ptr [flt_56A9F8]
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
        goto LABEL_14;
      result = (((gbVec3D *)&v39))->gbVec3D::DotProduct(&v42);
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
          LODWORD(v26) = (unsigned long)((char *)this + 8692);
          v16 = (_DWORD *)(&this->m_fCachePosX + 3 * (int)this->m_partyUI3.m_pfather);
          *((_DWORD *)&reg_ESI[1].m_partyActor.m_fSpeed + 2) = (unsigned long)*v16;
          *((_DWORD *)&reg_ESI[1].m_partyActor.m_fSpeed + 3) = (unsigned long)v16[1];
          reg_ESI[1].m_partyActor.m_fAngleDeg = (float)v16[2];
          result = (((RoleSystem *)this))->RoleSystem::UpdateMovement(v26, v29);
          if ( v17 )
            (((RoleSystem *)this))->RoleSystem::SetMoveSpeed(0.0, 0, v28);
          return result;
        }
      }
      v18 = (int *)(&this->m_fCachePosX + 3 * (int)this->m_partyUI3.m_pfather);
      v33 = (unsigned long)*v18;
      v34 = (unsigned long)v18[1];
      v35 = (unsigned long)v18[2];
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
  float v8; // st7
  int result; // eax
  unsigned int v10; // [esp+0x14] [ebp-0x4]

  this->m_partyActor.m_nState = nSceneIdx;
  v4 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v4))->RoleSystem::GetRolePtr(nSceneIdx);
  v6 = (_DWORD *)(16 * nRegion + RolePtr);
  v7 = *v6 + v6[2];
  v8 = ((float)(((int)v7 - HIDWORD(v7)) >> 1) + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 128);
  *(float *)&v10 = ((double)((v6[1] + v6[3]) / 2) + 0.5) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 136);
  this->m_wndcolor.Color = 0;
  *(float *)&this->m_fontcolor.Color = v8;
  this->m_id = v10;
  result = this->m_fontcolor.Color;
  *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 2) = result;
  *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 3) = this->m_wndcolor.Color;
  LODWORD(this[1].m_partyActor.m_fAngleDeg) = this->m_id;
  return result;
}

// 0x00413CD0
void RoleSystem::PathFollowUpdate()
{
    unsigned long reg_EAX = 0;
    unsigned long reg_EDI = 0;
    RoleSystem *reg_ESI = this;

  RoleSystem *v5; // eax
  RoleSystem *v6; // eax
  int v10; // eax
  int v11; // eax
  int m_bfocus; // edx
  const gbVec3D *v16; // eax
  const gbVec3D *v17; // eax
  const gbVec3D *v18; // eax
  LONG right; // edx
  _BYTE fScale[12]; // [esp+0x14] [ebp-0x50]
  float fScalea; // [esp+0x14] [ebp-0x50]
  int v29; // [esp+0x18] [ebp-0x4C]
  float v30; // [esp+0x18] [ebp-0x4C]
  float v31; // [esp+0x18] [ebp-0x4C]
  int v35; // [esp+0x28] [ebp-0x3C]
  int v36; // [esp+0x28] [ebp-0x3C]
  int v37; // [esp+0x28] [ebp-0x3C]
  float v38; // [esp+0x2C] [ebp-0x38]
  float v39; // [esp+0x30] [ebp-0x34]
  gbVec3D v40; // [esp+0x34] [ebp-0x30] BYREF
  gbVec3D v41; // [esp+0x40] [ebp-0x24] BYREF
  gbVec3D pOut; // [esp+0x4C] [ebp-0x18] BYREF
  gbVec3D v43; // [esp+0x58] [ebp-0xC] BYREF

  reg_ESI = this;
  switch ( this->m_nMoveSubMode )
  {
    case 1:
      __asm
      {
        fld     dword ptr [esi+0x50C]; jumptable 00413CE8 case 1
        fmul    dword ptr [flt_56AA08]
        fstp    [esp+0x4C+var_40]
      }
      v35 = rand();
      __asm
      {
        fild    [esp+0x4C+var_3C]
        fmul    dword ptr [flt_56AA04]
        fsub    _flt_1_0
        fstp    [esp+0x4C+var_34]
      }
      v36 = rand();
      __asm
      {
        fild    [esp+0x4C+var_3C]
        fmul    dword ptr [flt_56AA04]
        fsub    _flt_1_0
        fstp    [esp+0x4C+var_38]
      }
      v37 = rand();
      // __asm { fild    [esp+0x4C+var_3C] }
      v41.z = v39;
      __asm { fmul    dword ptr [flt_56AA04] }
      v41.y = v38;
      __asm
      {
        fsub    _flt_1_0
        fstp    [esp+0x4C+var_24]
      }
      gbVec3D::Normalize(&v41);
      // __asm { fld     [esp+0x4C+var_24] }
      reg_EDI = (unsigned long)(float *)&this->m_FrameA.m_benable;
      __asm { fmul    dword ptr [flt_56AA08] }
      pOut.z = v41.z;
      __asm
      {
        fld     [esp+0x4C+pOut+8]
        fmul    dword ptr [flt_56AA08]
      }
      pOut.x = v41.x;
      m_bfocus = this->m_FrameA.m_bfocus;
      pOut.y = v41.y;
      this->m_FrameA.m_bfocus = m_bfocus;
      __asm
      {
        fstp    [esp+0x4C+pOut+8]
        fadd    dword ptr [edi]
        fstp    dword ptr [edi]
      }
      // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EDI = _ET1;` 已由上方 asm 存储覆盖

      __asm
      {
        fld     [esp+0x4C+pOut+8]
        fadd    dword ptr [edi+8]
        fstp    dword ptr [edi+8]
      }
      reg_EDI[2] = _ET1;
      (((gbVec3D *)&this->m_FrameA.m_benable))->gbVec3D::Normalize();
      *(_DWORD *)fScale = this->m_FrameA.m_benable;
      memset(&v40, 0, sizeof(v40));
      memset(&v41, 0, sizeof(v41));
      v16 = (const gbVec3D *)Vec3Lerp(&v43.x, (float *)&this->m_pfather, *(float *)fScale, *(float *)&fScale[4]);
      (((gbVec3D *)&v40))->gbVec3D::operator=(*(v16));
      v17 = (const gbVec3D *)Vec3Lerp(
                                      &v43.x,
                                      (float *)&this->m_childs.m_nSize,
                                      *(float *)&this->m_FrameA.m_bfocus,
                                      v30);
      (((gbVec3D *)&v41))->gbVec3D::operator=(*(v17));
      (((gbVec3D *)&v40))->gbVec3D::operator+=(*(&v41));
      v18 = (const gbVec3D *)Vec3Lerp(
                                      &v43.x,
                                      (float *)&this->m_rect.top,
                                      *(float *)&this->m_FrameA.m_pbktex,
                                      v31);
      (((gbVec3D *)&v41))->gbVec3D::operator=(*(v18));
      (((gbVec3D *)&v40))->gbVec3D::operator+=(*(&v41));
      __asm
      {
        fld     [esp+0x4C+var_30]
        fmul    [esp+0x4C+var_40]
      }
      reg_EAX = (unsigned long)(float *)&this->m_FrameA.m_fontcolor.Color;
      this->m_FrameA.m_fontcolor.Color = this->m_rect.top;
      right = this->m_rect.right;
      __asm
      {
        fstp    [esp+0x4C+var_30]
        fld     [esp+0x4C+var_30+4]
        fmul    [esp+0x4C+var_40]
      }
      this->m_FrameA.m_wndcolor.Color = right;
      this->m_FrameA.m_id = this->m_rect.bottom;
      __asm
      {
        fstp    [esp+0x50+var_30+4]
        fld     [esp+0x50+var_30+8]
        fmul    [esp+0x50+var_40]
        fstp    [esp+0x50+var_30+8]
        fld     [esp+0x50+var_40]
        fmul    dword ptr [flt_56AA00]
        fld     st
        fmul    dword ptr [eax]
        fstp    dword ptr [eax]
      }
      // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EAX = _ET1;` 已由上方 asm 存储覆盖

      __asm
      {
        fld     st
        fmul    dword ptr [eax+4]
        fstp    dword ptr [eax+4]
      }
      reg_EAX[1] = _ET1;
      __asm
      {
        fmul    dword ptr [eax+8]
        fstp    dword ptr [eax+8]
      }
      reg_EAX[2] = _ET1;
      __asm
      {
        fld     [esp+0x50+var_30]
        fadd    dword ptr [eax]
        fstp    dword ptr [eax]
      }
      // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EAX = _ET1;` 已由上方 asm 存储覆盖

      __asm
      {
        fld     [esp+0x50+var_30+4]
        fadd    dword ptr [eax+4]
        fstp    dword ptr [eax+4]
      }
      reg_EAX[1] = _ET1;
      __asm
      {
        fld     [esp+0x50+var_30+8]
        fadd    dword ptr [eax+8]
        fstp    dword ptr [eax+8]
      }
      reg_EAX[2] = _ET1;
      __asm
      {
        fld     dword ptr [esi+0x50C]
        fmul    _flt_0_3
        fstp    [esp+0x50+fScale]; fScale
      }
      RoleSystem::ScaleVector((float *)&this->m_FrameA.m_fontcolor.Color, fScalea);
      this->m_FrameA.m_wndcolor.Color = 0;
      return;
    case 2:
      this->RoleSystem::AdvanceToTarget(*(double *)&fScale[4]);
      goto LABEL_22;
    case 4:
      this->RoleSystem::InterpolateMoveFrame(1.0);
      v41 = *Vec3Cross(
               &v43,
               (gbVec3D *)&this->m_FrameA.m_rect.bottom,
               (gbVec3D *)&this->m_FrameA.m_childs.m_needscriptdel);
      v40 = *Vec3Cross(&pOut, (gbVec3D *)&this->m_fontcolor, (gbVec3D *)&this->m_FrameA.m_childs.m_needscriptdel);
      (((gbVec3D *)&v41))->gbVec3D::Length();
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
        fld     [esp+0x4C+var_24+8]
        fmul    [esp+0x4C+var_30+8]
        fld     [esp+0x4C+var_24+4]
        fmul    [esp+0x4C+var_30+4]
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
        (((RoleSystem *)this))->RoleSystem::NotifyMoveComplete();
        *((_DWORD *)&reg_ESI[1].m_partyActor.m_fSpeed + 2) = this->m_FrameA.m_rect.bottom;
        *((_DWORD *)&reg_ESI[1].m_partyActor.m_fSpeed + 3) = this->m_FrameA.m_pfather;
        LODWORD(reg_ESI[1].m_partyActor.m_fAngleDeg) = this->m_FrameA.m_childs.m_pData;
        if ( this->m_nMoveMode != 4 || *(&this->m_partyActor.m_nUpdateMode + 5) != 7 )
        {
          *(_DWORD *)fScale = (unsigned long)((char *)this + 8692);
          (((RoleSystem *)this))->RoleSystem::UpdateMovement(*(double *)fScale, *(gbVec3D **)&fScale[8]);
          if ( v10 )
            (((RoleSystem *)this))->RoleSystem::SetMoveSpeed(0.0, 0, v29);
        }
      }
      return;
    case 5:
      v6 = g_pRoleSystem;
      if ( g_pRoleSystem )
      {
        this->m_FrameA.m_rect.bottom = g_pRoleSystem->m_fontcolor.Color;
        this->m_FrameA.m_pfather = ((UIWnd *)((UIWnd *)v6->m_wndcolor.Color));
        this->m_FrameA.m_childs.m_pData = ((char *)((char *)v6->m_id));
        this->RoleSystem::InterpolateMoveFrame(1.0);
      }
      return;
    case 6:
      v5 = g_pRoleSystem;
      if ( g_pRoleSystem )
      {
        this->m_FrameA.m_rect.bottom = g_pRoleSystem->m_fontcolor.Color;
        this->m_FrameA.m_pfather = ((UIWnd *)((UIWnd *)v5->m_wndcolor.Color));
        this->m_FrameA.m_childs.m_pData = ((char *)((char *)v5->m_id));
        this->RoleSystem::InterpolateMoveFrame(-1.0);
      }
      return;
    case 7:
      this->RoleSystem::AdvanceToTarget(*(double *)&fScale[4]);
      if ( this->m_partyActor.m_nState == this->m_FrameA.m_childs.capacity )
      {
LABEL_22:
        if ( v11 )
LABEL_20:
          (((RoleSystem *)this))->RoleSystem::NotifyMoveComplete();
      }
      else if ( (((RoleSystem *)this))->RoleSystem::ApproachTarget(this->m_FrameA.m_childs.m_nSize)
             && !(((RoleSystem *)&g_pathFinder))->RoleSystem::BindRoleToScene(this->m_partyActor.m_nState, (float *)&this->m_fontcolor.Color, (float *)&this->m_FrameA.m_rect.bottom, (int)&this->m_fMoveTargetX, this->m_nFacing) )
      {
        goto LABEL_20;
      }
      return;
    case 8:
      v41 = *Vec3Cross(
               &pOut,
               (gbVec3D *)&this->m_FrameA.m_rect.bottom,
               (gbVec3D *)&this->m_FrameA.m_childs.m_needscriptdel);
      v40 = *Vec3Cross(&v43, (gbVec3D *)&this->m_fontcolor, (gbVec3D *)&this->m_FrameA.m_childs.m_needscriptdel);
      (((gbVec3D *)&v41))->gbVec3D::Length();
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
        fld     [esp+0x4C+var_24+8]
        fmul    [esp+0x4C+var_30+8]
        fld     [esp+0x4C+var_24+4]
        fmul    [esp+0x4C+var_30+4]
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
          this->m_nMoveSubMode = 0;
          this->m_fRotAxisX = 0.0f;
          this->m_fRotAxisY = 0.0f;
          this->m_fRotAxisZ = 0.0f;
          this->m_nMovement = 0.0f;
          this->m_fSavedRotX = this->m_fRotAxisY;
          *(float *)((UIWnd *)&this->m_FrameA) = this->m_fRotAxisZ;
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
  float *p_Color; // esi
  float v3; // st7
  float v4; // st6
  float v5; // st7
  float v6; // st7
  unsigned int v7; // [esp+0x8] [ebp-0x8]
  unsigned int v8; // [esp+0xC] [ebp-0x4]
  float pfDira; // [esp+0x14] [ebp+0x4]

  p_Color = (float *)&this->m_FrameA.m_fontcolor.Color;
  v3 = *pfDir - this->m_fRotAxisX;
  *(float *)&v7 = pfDir[1] - this->m_fRotAxisY;
  v4 = pfDir[2] - this->m_fRotAxisZ;
  this->m_FrameA.m_wndcolor.Color = v7;
  *(float *)&v8 = v4;
  *(float *)&this->m_FrameA.m_fontcolor.Color = v3;
  this->m_FrameA.m_id = v8;
  pfDira = this->m_fMovement;
  v5 = (((gbVec3D *)&this->m_FrameA.m_fontcolor))->gbVec3D::Length();
  if ( v5 > pfDira )
  {
    v6 = pfDira / v5;
    *p_Color = v6 * *p_Color;
    p_Color[1] = v6 * p_Color[1];
    p_Color[2] = v6 * p_Color[2];
  }
}

// 0x004142E0
int RoleSystem::NotifyMoveComplete()
{
  int result; // eax

  this->m_nMoveSubMode = 0;
  this->m_nCoreState = 0;
  this->RoleSystem::UpdateTransform();
  this->m_fRotAxisX = 0.0f;
  this->m_fRotAxisY = 0.0f;
  this->m_fRotAxisZ = 0.0f;
  this->m_nMovement = 0.0f;
  this->m_fSavedRotX = this->m_fRotAxisY;
  *(float *)((UIWnd *)&this->m_FrameA) = this->m_fRotAxisZ;
  result = this->m_nCollisionState;
  if ( result )
  {
    this->m_nCollisionState = 0;
    this->m_partyActor.m_pRoleObj = 0;
  }
  return result;
}

// 0x00414350
double RoleSystem::UpdateMovement(double result, gbVec3D *pB)
{
  RoleSystem *v4; // ebp
  unsigned int *v5; // edi
  int RolePtr; // ebx
  float v7; // st7
  float v8; // st7
  float v9; // st7
  float v10; // st7
  float v11; // st7
  float *v12; // edi
  int v13; // edx
  float v14; // st6
  float v15; // st6
  float v16; // st7
  float v17; // edx
  float v18; // st7
  float v19; // ecx
  float v20; // st6
  float z; // eax
  float v22; // ecx
  float v23; // edx
  float x; // eax
  float y; // ecx
  float v26; // edx
  int *m_nState; // [esp-0xC] [ebp-0x40]
  gbVec3D nFlag; // [esp+0x10] [ebp-0x24] BYREF
  gbVec3D pfVal2; // [esp+0x1C] [ebp-0x18] BYREF
  gbVec3D v30; // [esp+0x28] [ebp-0xC] BYREF
  float resulta; // [esp+0x38] [ebp+0x4]

  v4 = (RoleSystem *)UISceneUpdate();
  v5 = (unsigned int *)LODWORD(result);
  RolePtr = (((RoleSystem *)v4))->RoleSystem::GetRolePtr(this->m_partyActor.m_nState);
  v7 = *(float *)(LODWORD(result) + 8) - *(float *)(RolePtr + 136);
  LODWORD(nFlag.x) = (__int64)((*(float *)LODWORD(result) - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v8 = v7 / *(float *)&g_palScript.m_fSceneTileSize;
  if ( (((RoleSystem *)v4))->RoleSystem::CheckCollision((int *)this->m_partyActor.m_nState, SLODWORD(nFlag.x)) )
    goto LABEL_2;
  if ( this->m_nMoveSubMode != 2 )
    goto LABEL_23;
  v5 = (unsigned int *)(&this[1].m_partyActor.m_fSpeed + 2);
  nFlag.x = sub_408010(&this[1].m_partyActor.m_fSpeed + 2);
  sub_4080F0(nFlag.x, (int)(&this[1].m_partyActor.m_fSpeed + 2));
  *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 3) = 0;
  nFlag.x = *(&this[1].m_partyActor.m_fSpeed + 2) - *(float *)&this->m_fontcolor.Color;
  v9 = *(&this[1].m_partyActor.m_fSpeed + 3) - *(float *)&this->m_wndcolor.Color;
  pfVal2.x = nFlag.x;
  nFlag.y = v9;
  v10 = this[1].m_partyActor.m_fAngleDeg - *(float *)&this->m_id;
  pfVal2.y = nFlag.y;
  nFlag.z = v10;
  pfVal2.z = nFlag.z;
  v8 = (((gbVec3D *)&pfVal2))->gbVec3D::Length();
  if ( v8 <= 0.050000001f )
    goto LABEL_23;
  (((gbVec3D *)&pfVal2))->gbVec3D::Normalize();
  v8 = pfVal2.y * *(float *)&this->m_rect.right
     + pfVal2.z * *(float *)&this->m_rect.bottom
     + pfVal2.x * *(float *)&this->m_rect.top;
  if ( v8 > 0.0f
    && (v11 = this[1].m_partyActor.m_fAngleDeg - *(float *)(RolePtr + 136),
        LODWORD(nFlag.x) = (__int64)((*(float *)v5 - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize),
        v8 = v11 / *(float *)&g_palScript.m_fSceneTileSize,
        (((RoleSystem *)v4))->RoleSystem::CheckCollision((int *)this->m_partyActor.m_nState, SLODWORD(nFlag.x)))
    && (v30 = *Vec3Cross(&nFlag, (gbVec3D *)(&this[1].m_partyActor.m_fSpeed + 2), (gbVec3D *)LODWORD(result)),
        v8 = (((gbVec3D *)&v30))->gbVec3D::Length(),
        v8 < 12.0) )
  {
LABEL_2:
    this->m_fCachePosX = this->m_fPosX;
    this->m_fCachePosY = this->m_fPosY;
    this->m_fCachePosZ = this->m_fPosZ;
    this->m_fontcolor.Color = *v5;
    this->m_wndcolor.Color = v5[1];
    this->m_id = v5[2];
  }
  else
  {
LABEL_23:
    if ( this->m_nMoveMode != 3 )
      goto LABEL_20;
    nFlag.x = 0.0f;
    memset(&pfVal2, 0, sizeof(pfVal2));
    if ( (LOBYTE(byte_C10D80[0]) & 1) == 0 )
    {
      LOBYTE(byte_C10D80[0]) |= 1u;
      v30.x = 12.0f * 0.5f;
      v30.z = v30.x;
      dword_C10D50 = v30.x;
      dword_C10D54 = 0;
      v30.x = 12.0f * -0.5f;
      dword_C10D58 = LODWORD(v30.z);
      v30.z = 12.0f * 0.5f;
      dword_C10D5C = LODWORD(v30.x);
      dword_C10D60 = 0;
      dword_C10D64 = LODWORD(v30.z);
      *(float *)&dword_C10D68 = 12.0;
      v30.x = -12.0f;
      dword_C10D6C = 0;
      dword_C10D70 = 0;
      v30.y = 0.0f;
      v30.z = 0.0f;
      dword_C10D74 = LODWORD(v30.x);
      dword_C10D78 = 0;
      dword_C10D7C = 0;
      atexit(nullsub_6);
    }
    v12 = (float *)&dword_C10D50;
    do
    {
      this->RoleSystem::UpdateMoveInterpolation(v12, &pfVal2.x);
      LOBYTE(v13) = this->m_nFacing;
      m_nState = (int *)this->m_partyActor.m_nState;
      pfVal2.x = pfVal2.x + *(float *)&this->m_fontcolor.Color;
      pfVal2.y = pfVal2.y + *(float *)&this->m_wndcolor.Color;
      v8 = pfVal2.z + *(float *)&this->m_id;
      pfVal2.z = v8;
      if ( (((RoleSystem *)v4))->RoleSystem::CheckMoveCollision(m_nState, &pfVal2.x, v13) )
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
    while ( (int)v12 < (int)byte_C10D80 );
    if ( !LODWORD(nFlag.x) )
      goto LABEL_20;
    v16 = *(float *)LODWORD(result) - *(float *)&this->m_fontcolor.Color;
    v17 = *(float *)(LODWORD(result) + 8);
    nFlag.y = *(float *)(LODWORD(result) + 4);
    nFlag.z = v17;
    nFlag.x = v16;
    nFlag.y = nFlag.y - *(float *)&this->m_wndcolor.Color;
    nFlag.z = v17 - *(float *)&this->m_id;
    resulta = (((gbVec3D *)&nFlag))->gbVec3D::Length();
    (((gbVec3D *)&pfVal2))->gbVec3D::Normalize();
    v18 = 0.0f;
    if ( pfVal2.z * *(float *)&this->m_FrameA.m_rect.right + pfVal2.x * *(float *)&this->m_FrameA.m_rect.left < -0.1 )
    {
      v19 = *(float *)&this->m_FrameA.m_rect.right;
      v18 = *(float *)&this->m_FrameA.m_rect.top;
      LODWORD(pfVal2.x) = this->m_FrameA.m_rect.left;
      pfVal2.z = v19;
    }
    *(float *)&this->m_FrameA.m_rect.top = v18;
    v20 = pfVal2.x * resulta;
    z = pfVal2.z;
    this->m_FrameA.m_rect.left = LODWORD(pfVal2.x);
    *(float *)&this->m_FrameA.m_rect.right = z;
    v22 = *(float *)&this->m_wndcolor.Color;
    v23 = *(float *)&this->m_id;
    pfVal2.x = v20;
    nFlag.y = v22;
    nFlag.z = v23;
    pfVal2.y = v18 * resulta;
    pfVal2.z = pfVal2.z * resulta;
    nFlag.x = *(float *)&this->m_fontcolor.Color + pfVal2.x;
    nFlag.y = v22 + pfVal2.y;
    nFlag.z = v23 + pfVal2.z;
    v8 = (nFlag.z - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize;
    if ( (((RoleSystem *)v4))->RoleSystem::CheckCollision((int *)this->m_partyActor.m_nState, (__int64)((nFlag.x - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize)) )
    {
      LODWORD(this->m_fCachePosX) = this->m_fontcolor.Color;
      x = nFlag.x;
      LODWORD(this->m_fCachePosY) = this->m_wndcolor.Color;
      y = nFlag.y;
      LODWORD(this->m_fCachePosZ) = this->m_id;
      v26 = nFlag.z;
      *(float *)&this->m_fontcolor.Color = x;
      *(float *)&this->m_wndcolor.Color = y;
      *(float *)&this->m_id = v26;
    }
    else
    {
LABEL_20:
      this->RoleSystem::NotifyMoveComplete();
    }
  }
  return v8;
}

// 0x004148C0
float * RoleSystem::UpdateMoveInterpolation(float *pfVal, float *pfVal2)
{
  float *result; // eax
  float v5; // st7
  float v6; // st7
  float v7; // st6
  float v8; // st6
  float v9; // st7
  float v10; // st6
  float v11; // st6
  float v12; // [esp+0x4] [ebp-0x18]
  float v13; // [esp+0x8] [ebp-0x14]
  float v14; // [esp+0x10] [ebp-0xC]
  float v15; // [esp+0x10] [ebp-0xC]
  float v16; // [esp+0x14] [ebp-0x8]
  float v17; // [esp+0x14] [ebp-0x8]
  float pfVala; // [esp+0x20] [ebp+0x4]
  float pfVal2a; // [esp+0x24] [ebp+0x8]

  result = (float *)pfVal2;
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
void RoleSystem::GetPosition(float *pOut, int nVal)
{
  gbVec3D *p_m_nMovement; // esi
  double m_nTransformState; // st7

  p_m_nMovement = (gbVec3D *)&this->m_nMovement;
  this->m_nMovement = *pOut;
  this->m_fSavedRotX = pOut[1];
  *(float *)((UIWnd *)&this->m_FrameA) = pOut[2];
  this->m_nCoreState = nVal;
  this->RoleSystem::UpdateTransform();
  if ( nVal )
  {
    this->m_fSavedRotX = 0.0f;
    (((gbVec3D *)p_m_nMovement))->gbVec3D::Normalize();
    m_nTransformState = this->m_nTransformState;
    p_m_nMovement->x = m_nTransformState * p_m_nMovement->x;
    p_m_nMovement->y = m_nTransformState * p_m_nMovement->y;
    p_m_nMovement->z = m_nTransformState * p_m_nMovement->z;
    this->m_nMoveSubMode = 12;
  }
  else
  {
    this->m_nMoveSubMode = 0;
  }
}

// 0x00414A10
void RoleSystem::UpdateMoveTimer()
{
  flt_C10D48 = 12.0 * 14.0;
}

// 0x00414A30
int RoleSystem::PathFind(float *pTarget)
{
  float v2; // st6
  int m_nMoveMode; // eax
  float v5; // st7
  float v6; // st7
  float y; // ecx
  float v8; // st7
  float v9; // st6
  float *v10; // ebp
  float v11; // ecx
  float v12; // st6
  RoleSystem *v13; // eax
  RoleSystem *v14; // eax
  int RolePtr; // edi
  int *v16; // ebx
  float v17; // st7
  __int64 v18; // rax
  float v19; // st7
  RoleSystem *v20; // eax
  float v21; // st7
  int *v22; // ecx
  int v23; // edx
  int v24; // eax
  float v25; // eax
  Scene *v26; // eax
  long double v27; // st7
  long double v28; // st6
  long double v29; // rt0
  long double v30; // st6
  float v31; // st7
  float v32; // st7
  float v33; // edx
  long double v34; // st6
  float v35; // st6
  int result; // eax
  float v37; // st6
  int *v38; // [esp-0x18] [ebp-0x5C]
  int m_nState; // [esp-0x10] [ebp-0x54]
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

  m_nMoveMode = this->m_nMoveMode;
  *(&this->m_partyActor.m_nUpdateMode + 5) = 0;
  *(&this->m_partyActor.m_nUpdateMode + 6) = 0;
  if ( m_nMoveMode != 4 )
    this->m_nPrevMoveMode = m_nMoveMode;
  this->m_nMoveMode = 4;
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
  v8 = (((gbVec3D *)&v53))->gbVec3D::Length();
  if ( v2 <= flt_C10D48 )
  {
    v10 = (float *)(&this->m_partyActor.m_nUpdateMode + 8);
    *((float *)&this->m_partyActor.m_nUpdateMode + 8) = *pTarget;
    this->m_fPathTargetY = pTarget[1];
    this->m_fPathTargetZ = pTarget[2];
  }
  else
  {
    v9 = flt_C10D48 / v2;
    v10 = (float *)(&this->m_partyActor.m_nUpdateMode + 8);
    v53.x = v53.x * v9;
    v53.y = v53.y * v9;
    v53.x = v53.x + *(float *)&this->m_fontcolor.Color;
    v53.y = v53.y + *(float *)&this->m_wndcolor.Color;
    v11 = v53.y;
    v12 = v9 * v53.z + *(float *)&this->m_id;
    *(&this->m_partyActor.m_nUpdateMode + 8) = LODWORD(v53.x);
    this->m_fPathTargetY = v11;
    v53.z = v12;
    this->m_fPathTargetZ = v12;
  }
  m_nState = this->m_partyActor.m_nState;
  v13 = (RoleSystem *)UISceneUpdate();
  (((RoleSystem *)v13))->RoleSystem::SetRoleParam(m_nState, v10, 0, 0);
  this->m_fPathTargetY = v8;
  if ( !g_bPathEnabled )
  {
    v46 = this->m_partyActor.m_nState;
    v14 = (RoleSystem *)UISceneUpdate();
    RolePtr = (((RoleSystem *)v14))->RoleSystem::GetRolePtr(v46);
    v16 = (int *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
    v17 = *v10 - *(float *)(RolePtr + 128);
    pnVal = (int *)(__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
    v18 = (__int64)(v17 / *(float *)&g_palScript.m_fSceneTileSize);
    v19 = v10[2] - *(float *)(RolePtr + 136);
    pszBuf = (char *)v18;
    v44 = (__int64)(v19 / *(float *)&g_palScript.m_fSceneTileSize);
    v42 = (char *)v18;
    v40 = (int *)pnVal;
    v38 = (int *)this->m_partyActor.m_nState;
    v20 = (RoleSystem *)UISceneUpdate();
    if ( !(((RoleSystem *)v20))->RoleSystem::GetPathTarget(v38, v16, v40, v42, v44, &a7) )
    {
      v21 = 0.0f;
      v22 = (int *)a7;
      v23 = nY;
      v50 = ((float)(int)a7 + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 128);
      v52 = ((float)nY + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 136);
      if ( (int)a7 >= 0 )
      {
        v24 = *(_DWORD *)(RolePtr + 152);
        if ( (int)a7 < v24 && nY >= 0 && nY < *(_DWORD *)(RolePtr + 156) )
          v21 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * ((_DWORD)a7 + nY * v24));
      }
      v25 = v50;
      v10[1] = v21;
      *v10 = v25;
      v45 = v23;
      v10[2] = v52;
      v43 = (int)v22;
      v41 = this->m_partyActor.m_nState;
      v26 = UISceneUpdate();
      this->m_fPathTargetY = (((Scene *)v26))->Scene::GetTileHeight(v41, v43, v45, 0);
    }
  }
  this->m_fRotAxisX = *v10;
  this->m_fRotAxisY = v10[1];
  this->m_fRotAxisZ = v10[2];
  this->m_fRotAxisX = this->m_fRotAxisX - this->m_fPosX;
  this->m_fRotAxisY = this->m_fRotAxisY - this->m_fPosY;
  this->m_fRotAxisZ = this->m_fRotAxisZ - this->m_fPosZ;
  this->m_fRotAxisY = 0.0f;
  (((gbVec3D *)&this->m_fRotAxisX))->gbVec3D::Normalize();
  this->RoleSystem::UpdatePosition();
  v27 = sqrt((50.0 + 50.0) / 490.0);
  this->m_fPathAngle = v27;
  v28 = fabs(this->m_fPathTargetY - this->m_fPosY);
  this->m_fPathSpeed = 0.0f;
  v29 = sqrt((v28 + 50.0 + v28 + 50.0) / 490.0);
  v30 = v27;
  this->m_fPathAngle = v29 + v27;
  v50 = *v10 - this->m_fPosX;
  v31 = v10[1] - this->m_fPosY;
  v54.x = v50;
  *(float *)&pnVal = v31;
  v32 = v10[2] - this->m_fPosZ;
  this->m_fRotAxisY = 0.0f;
  v52 = v32;
  v33 = v52;
  this->m_fRotAxisX = v54.x;
  v54.z = v33;
  v54.y = 0.0f;
  this->m_fRotAxisZ = v33;
  (((gbVec3D *)&this->m_fRotAxisX))->gbVec3D::Normalize();
  (((gbVec3D *)&v54))->gbVec3D::Length();
  v34 = v30 / this->m_fPathAngle;
  this->m_fRotAxisX = v34 * this->m_fRotAxisX;
  this->m_fRotAxisY = v34 * this->m_fRotAxisY;
  this->m_fRotAxisZ = v34 * this->m_fRotAxisZ;
  v35 = 50.0f;
  if ( this->m_fPathTargetY > (double)this->m_fPosY )
    v35 = this->m_fPathTargetY - this->m_fPosY + 50.0f;
  this->m_nCoreState = 4;
  this->m_fRotAxisY = sqrt((v35 + v35) / 490.0f) * 490.0f;
  (((Actor *)&this->m_partyActor.m_Actor))->Actor::CompareActionName(4, 2);
  (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(4.0);
  v37 = this->m_fPathAngle + 0.5f;
  this->m_fPathAngle = v37;
  this->m_fPathAngle = v37 + 0.5f;
  return result;
}

// 0x00414E30
int RoleSystem::GetActionByIndex(int nParam)
{
  int nMode; // [esp+0x8] [ebp+0x8]

  return this->RoleSystem::PlayAction((&pszAction)[nParam], nMode);
}

// 0x00414F90
int RoleSystem::PlayAction(char *pszAction, int nMode)
{
  int m_nMoveMode; // eax
  double v5; // st7
  int result; // eax
  int m_pRoleObj; // edx

  m_nMoveMode = this->m_nMoveMode;
  this->m_bPathActive = 0;
  this->m_nActionResult = 1;
  *(&this->m_partyActor.m_nUpdateMode + 5) = 2;
  if ( m_nMoveMode != 4 )
    this->m_nPrevMoveMode = m_nMoveMode;
  this->m_nCoreState = 0;
  this->m_nMoveMode = 4;
  *(&this->m_partyActor.m_nUpdateMode + 6) = nMode;
  *(&this->m_partyActor.m_nUpdateMode + 7) = 0;
  this->m_nMoveReset = 0;
  if ( nMode == -2 )
    SetActionByName((Actor *)&this->m_partyActor.m_Actor, pszAction, 0, pszOpt1);
  else
    SetMaterialName((Actor *)&this->m_partyActor.m_Actor, pszAction, 0);
  v5 = (double)(((gbActor *)this->m_partyActor.m_pActor))->gbActor::GetActionDuration(pszAction) * 0.0002083333333333333;
  this->m_fPathAngle = v5;
  if ( v5 > 10.0 )
    this->m_fPathAngle = 10.0f;
  this->m_fPathSpeed = 0.0f;
  (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(1.0);
  this->RoleSystem::LoadWeaponModel(pszAction);
  result = _strcmpi(pszAction, "c07");
  if ( !result )
  {
    result = _strcmpi(&this->m_nAnimState, (const char *)&g_pszSceneSlot1);
    if ( !result )
    {
      m_pRoleObj = g_RoleSystemMain.m_partyActor.m_pRoleObj;
      g_RoleSystemMain.m_partyActor.m_pRoleObj = 0;
      g_palScript._todo_768 = m_pRoleObj;
    }
  }
  return result;
}

// 0x004150C0
void RoleSystem::UpdateActionState(float fVal)
{
  double v3; // st7
  int v4; // eax
  bool v5; // zf
  long double v6; // st7
  int m_nMoveMode; // eax
  int v8; // eax
  double v9; // st7
  float v10; // ecx
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st7
  int v15; // edx
  long double v16; // st7
  float v17; // ecx
  float v18; // edx
  int v19; // eax
  int v20; // eax
  float v21; // eax
  float v22; // ecx
  int v23; // edx
  int v24; // eax
  float v25; // ecx
  int v26; // eax
  double m_fPosY; // st7
  float v28; // edx
  float v29; // eax
  int v30; // eax
  double v31; // st7
  PalScriptMgr *v32; // eax
  int v33; // ecx
  gbActor *m_pActor; // edi
  unsigned int v35; // eax
  int m_nPrevMoveMode; // eax
  unsigned int v37; // eax
  int v38; // eax
  double v39; // st7
  double v40; // st7
  int v41; // eax
  int m_nCollisionParam; // eax
  double v43; // st7
  int v44; // edx
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

  switch ( *(&this->m_partyActor.m_nUpdateMode + 5) )
  {
    case 0:
      v30 = *(&this->m_partyActor.m_nUpdateMode + 6);
      switch ( v30 )
      {
        case 0:
          if ( (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::CheckMessage(pszMsgName) || this->m_fPathSpeed > 0.5f )
          {
            (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(1.0);
            *(&this->m_partyActor.m_nUpdateMode + 6) = 1;
          }
LABEL_69:
          this->m_fPathSpeed = fVal + this->m_fPathSpeed;
          return;
        case 1:
          if ( (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::CheckMessage(pszOpt1) )
            (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(0.0);
          v53 = fVal * this->m_fRotAxisY;
          v59 = fVal * this->m_fRotAxisZ;
          this->m_fPosX = fVal * this->m_fRotAxisX + this->m_fPosX;
          this->m_fPosY = v53 + this->m_fPosY;
          this->m_fPosZ = v59 + this->m_fPosZ;
          v31 = this->m_fRotAxisY - 490.0 * fVal;
          this->m_fRotAxisY = v31;
          if ( v31 < 0.0 )
            *(&this->m_partyActor.m_nUpdateMode + 6) = 2;
          break;
        case 2:
          if ( (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::CheckMessage(pszOpt1) )
            (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(0.0);
          v54 = fVal * this->m_fRotAxisY;
          v60 = fVal * this->m_fRotAxisZ;
          this->m_fPosX = fVal * this->m_fRotAxisX + this->m_fPosX;
          this->m_fPosY = v54 + this->m_fPosY;
          this->m_fPosZ = v60 + this->m_fPosZ;
          this->m_fRotAxisY = this->m_fRotAxisY - 490.0f * fVal;
          if ( this->m_fPosY < (double)this->m_fPathTargetY )
          {
            this->m_fPosX = *((float *)&this->m_partyActor.m_nUpdateMode + 8);
            this->m_fPosY = this->m_fPathTargetY;
            this->m_fPosZ = this->m_fPathTargetZ;
            *(&this->m_partyActor.m_nUpdateMode + 6) = 3;
            this->m_fPathSpeed = 0.0f;
            (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(2.0);
          }
          break;
        default:
          if ( v30 == 3 && (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::GetVisNode() )
          {
            this->m_nMoveMode = this->m_nPrevMoveMode;
            this->RoleSystem::NotifyMoveComplete();
            this->m_fontcolor.Color = LODWORD(this->m_fPosX);
            this->m_wndcolor.Color = LODWORD(this->m_fPosY);
            this->m_id = LODWORD(this->m_fPosZ);
            this->m_wndcolor.Color = 0;
            *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 2) = this->m_fontcolor.Color;
            *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 3) = this->m_wndcolor.Color;
            LODWORD(this[1].m_partyActor.m_fAngleDeg) = this->m_id;
            v32 = (PalScriptMgr *)UISceneUpdate();
            (((PalScriptMgr *)v32))->PalScriptMgr::CheckTileScript(this, fVal, 1);
          }
          goto LABEL_69;
      }
      this->m_fontcolor.Color = LODWORD(this->m_fPosX);
      this->m_wndcolor.Color = LODWORD(this->m_fPosY);
      this->m_id = LODWORD(this->m_fPosZ);
      this->m_wndcolor.Color = 0;
      *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 2) = this->m_fontcolor.Color;
      *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 3) = this->m_wndcolor.Color;
      LODWORD(this[1].m_partyActor.m_fAngleDeg) = this->m_id;
      this->RoleSystem::SetMoveSpeed(_pal3_coerce_f32(1), 0, v48);
      goto LABEL_69;
    case 2:
      v33 = *(&this->m_partyActor.m_nUpdateMode + 6);
      if ( v33 == -1 )
      {
        (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::GetVisNode();
      }
      else if ( v33 == -2 )
      {
        m_pActor = (gbActor *)this->m_partyActor.m_pActor;
        if ( (((gbVisNode *)m_pActor))->gbVisNode::PopMessage(v62) )
        {
          while ( v62.msgid != 1 )
          {
            if ( !(((gbVisNode *)m_pActor))->gbVisNode::PopMessage(v62) )
              return;
          }
          v35 = gbCrc32Compute(pszOpt1);
          if ( v62.param[0] == v35 )
          {
            (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(0.0);
            m_nPrevMoveMode = this->m_nPrevMoveMode;
            this->m_bPathActive = 1;
            this->m_nMoveMode = m_nPrevMoveMode;
          }
          else
          {
            v37 = gbCrc32Compute("over");
            if ( v62.param[0] == v37 )
            {
              (*(void ( **)(gbActor *))(*(_DWORD *)((gbChain1DNode *)this->m_partyActor.m_pActor) + 24))(this->m_partyActor.m_pActor);
              (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(0.0);
              (((Actor *)&this->m_partyActor.m_Actor))->Actor::QueryState(-1082130432);
              v38 = this->m_nPrevMoveMode;
              this->m_bPathActive = 0;
              this->m_nMoveMode = v38;
            }
          }
        }
      }
      else
      {
        v39 = fVal + this->m_fPathSpeed;
        this->m_fPathSpeed = v39;
        if ( v39 >= this->m_fPathAngle )
        {
          v40 = v39 - this->m_fPathAngle;
          v41 = *(&this->m_partyActor.m_nUpdateMode + 7) + 1;
          *(&this->m_partyActor.m_nUpdateMode + 7) = v41;
          this->m_fPathSpeed = v40;
          if ( v41 >= v33 )
          {
            if ( !_strcmpi((const char *)&this->m_partyActor.m_nUpdateMode + 12, "c07")
              && !_strcmpi(&this->m_nAnimState, (const char *)&g_pszSceneSlot1) )
            {
              g_RoleSystemMain.m_partyActor.m_pRoleObj = g_palScript._todo_768;
            }
            m_nCollisionParam = this->m_nCollisionParam;
            this->m_nMoveMode = this->m_nPrevMoveMode;
            if ( m_nCollisionParam )
              goto LABEL_91;
            this->m_nMoveSubMode = 0;
            this->m_fRotAxisX = 0.0f;
            this->m_fRotAxisY = 0.0f;
            this->m_fRotAxisZ = 0.0f;
            this->m_nMovement = 0.0f;
            this->m_fSavedRotX = this->m_fRotAxisY;
            *(float *)((UIWnd *)&this->m_FrameA) = this->m_fRotAxisZ;
          }
        }
      }
      return;
    case 3:
      v43 = fVal + this->m_fPathSpeed;
      this->m_fPathSpeed = v43;
      if ( v43 < this->m_fPathAngle )
      {
        *(&this[1].m_partyActor.m_fSpeed + 1) = (1.0 - v43 / this->m_fPathAngle) * this->m_fPathTargetY
                                              + v43
                                              / this->m_fPathAngle
                                              * *((float *)&this->m_partyActor.m_nUpdateMode + 8);
      }
      else
      {
        v44 = this->m_nPrevMoveMode;
        *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 1) = *(&this->m_partyActor.m_nUpdateMode + 8);
        this->m_nMoveMode = v44;
        this->RoleSystem::NotifyMoveComplete();
      }
      return;
    case 4:
      this->RoleSystem::PathFollowUpdate();
      if ( this->m_nMoveSubMode )
      {
        this->m_fRotAxisX = this->m_nMovement;
        this->m_fRotAxisY = this->m_fSavedRotX;
        LODWORD(this->m_fRotAxisZ) = (unsigned long)((UIWnd *)&this->m_FrameA);
      }
      else
      {
        this->m_fontcolor.Color = this->m_FrameA.m_rect.bottom;
        this->m_wndcolor.Color = (unsigned int)this->m_FrameA.m_pfather;
        this->m_id = (unsigned int)this->m_FrameA.m_childs.m_pData;
        this->m_wndcolor.Color = 0;
        this->RoleSystem::SetMoveSpeed(0.0, 0, v48);
        LODWORD(this->m_fRotAxisX) = this->m_rect.top;
        LODWORD(this->m_fRotAxisY) = this->m_rect.right;
        LODWORD(this->m_fRotAxisZ) = this->m_rect.bottom;
        this->m_fRotAxisX = this->m_fRotAxisX * -1.0f;
        this->m_fRotAxisY = this->m_fRotAxisY * -1.0f;
        this->m_fRotAxisZ = this->m_fRotAxisZ * -1.0f;
        this->RoleSystem::UpdatePosition();
        this->RoleSystem::Notify();
        this->m_nMoveMode = this->m_nPrevMoveMode;
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
      v47 = (((gbVec3D *)&v62))->gbVec3D::Length();
      if ( this->m_nMoveSubMode && v47 >= 12.0 * 1.5 )
      {
        this->RoleSystem::PathFollowUpdate();
        this->m_fRotAxisX = this->m_nMovement;
        this->m_fRotAxisY = this->m_fSavedRotX;
        LODWORD(this->m_fRotAxisZ) = (unsigned long)((UIWnd *)&this->m_FrameA);
      }
      else
      {
        this->m_nMoveMode = this->m_nPrevMoveMode;
        this->RoleSystem::NotifyMoveComplete();
        this->m_partyActor.m_pRoleObj = 0;
      }
      return;
    case 7:
      v20 = *(&this->m_partyActor.m_nUpdateMode + 6);
      if ( v20 )
      {
        if ( v20 == 1 )
        {
          v52 = this->m_fRotAxisY * fVal;
          v58 = this->m_fRotAxisZ * fVal;
          this->m_fPosX = this->m_fRotAxisX * fVal + this->m_fPosX;
          this->m_fPosY = v52 + this->m_fPosY;
          this->m_fPosZ = v58 + this->m_fPosZ;
          m_fPosY = this->m_fPosY;
          if ( *(&this->m_partyActor.m_nUpdateMode + 7) == 1 )
          {
            if ( m_fPosY <= this->m_fPathTargetY )
              return;
          }
          else if ( m_fPosY >= this->m_fPathTargetY )
          {
            return;
          }
          this->m_fPosY = this->m_fPathTargetY;
          *(&this->m_partyActor.m_nUpdateMode + 6) = 2;
          this->RoleSystem::SetMoveTarget((float *)&this->m_partyActor.m_nUpdateMode + 8, 1);
          return;
        }
        if ( v20 == 2 )
        {
          this->RoleSystem::PathFollowUpdate();
          if ( !this->m_nMoveSubMode )
          {
            if ( LODWORD(this->m_pLinkedRole[1].m_forward.z) )
              this->m_partyActor.m_nState = *(&this->m_partyActor.m_nUpdateMode + 7) == 1;
            this->m_fontcolor.Color = *(&this->m_partyActor.m_nUpdateMode + 8);
            this->m_wndcolor.Color = LODWORD(this->m_fPathTargetY);
            this->m_id = LODWORD(this->m_fPathTargetZ);
            this->m_wndcolor.Color = 0;
            *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 2) = this->m_fontcolor.Color;
            *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 3) = this->m_wndcolor.Color;
            LODWORD(this[1].m_partyActor.m_fAngleDeg) = this->m_id;
            this->RoleSystem::SetMoveSpeed(0.0, 0, v48);
            this->m_nMoveMode = this->m_nPrevMoveMode;
            this->RoleSystem::NotifyMoveComplete();
            goto LABEL_28;
          }
          this->m_fRotAxisX = this->m_nMovement;
          this->m_fRotAxisY = this->m_fSavedRotX;
          LODWORD(this->m_fRotAxisZ) = (unsigned long)((UIWnd *)&this->m_FrameA);
          this->RoleSystem::UpdatePosition();
          this->m_fRotAxisX = fVal * this->m_fRotAxisX;
          this->m_fRotAxisY = fVal * this->m_fRotAxisY;
          this->m_fRotAxisZ = fVal * this->m_fRotAxisZ;
          *(float *)&this->m_fontcolor.Color = this->m_fRotAxisX + *(float *)&this->m_fontcolor.Color;
          *(float *)&this->m_wndcolor.Color = this->m_fRotAxisY + *(float *)&this->m_wndcolor.Color;
          *(float *)&this->m_id = this->m_fRotAxisZ + *(float *)&this->m_id;
          v28 = *(float *)&this->m_fontcolor.Color;
          v29 = *(float *)&this->m_id;
          this->m_fPosX = v28;
          this->m_wndcolor.Color = 0;
          this->m_fPosZ = v29;
          *(float *)&this->m_nDispFontColor = v28;
          *(float *)&this->m_nTodo_9C = v29;
        }
      }
      else
      {
        this->RoleSystem::PathFollowUpdate();
        if ( !this->m_nMoveSubMode )
        {
          this->RoleSystem::UpdateMovement(this->m_fPathAngle, 1);
          v26 = *(&this->m_partyActor.m_nUpdateMode + 7);
          *(&this->m_partyActor.m_nUpdateMode + 6) = 1;
          this->m_fRotAxisX = 0.0f;
          if ( v26 == 1 )
          {
            this->m_fRotAxisY = 1.0f;
            this->m_fRotAxisZ = 0.0f;
            this->m_nCoreState = 5;
          }
          else
          {
            this->m_fRotAxisY = -1.0f;
            this->m_fRotAxisZ = 0.0f;
            this->m_nCoreState = 6;
          }
          this->RoleSystem::UpdatePath(this->m_nCoreState);
          goto LABEL_25;
        }
        this->m_fRotAxisX = this->m_nMovement;
        this->m_fRotAxisY = this->m_fSavedRotX;
        LODWORD(this->m_fRotAxisZ) = (unsigned long)((UIWnd *)&this->m_FrameA);
        this->RoleSystem::UpdatePosition();
        this->m_fRotAxisX = fVal * this->m_fRotAxisX;
        this->m_fRotAxisY = fVal * this->m_fRotAxisY;
        this->m_fRotAxisZ = fVal * this->m_fRotAxisZ;
        *(float *)&this->m_fontcolor.Color = this->m_fRotAxisX + *(float *)&this->m_fontcolor.Color;
        *(float *)&this->m_wndcolor.Color = this->m_fRotAxisY + *(float *)&this->m_wndcolor.Color;
        *(float *)&this->m_id = this->m_fRotAxisZ + *(float *)&this->m_id;
        v21 = *(float *)&this->m_fontcolor.Color;
        v22 = *(float *)&this->m_id;
        this->m_fPosX = v21;
        v23 = LODWORD(v21);
        this->m_fPosZ = v22;
        v24 = LODWORD(v22);
        v25 = this->m_fPosY;
        this->m_wndcolor.Color = 0;
        fVala = v25;
        this->m_nDispFontColor = v23;
        this->m_nTodo_9C = v24;
        this->RoleSystem::SetMoveSpeed(0.0, 0, v48);
        if ( fabs(fVala - this->m_fPosY) > 20.0 )
          this->m_fPosY = fVala;
      }
      return;
    case 8:
      if ( *(&this->m_partyActor.m_nUpdateMode + 6) )
      {
        v51 = this->m_fRotAxisY * fVal;
        v57 = this->m_fRotAxisZ * fVal;
        this->m_fPosX = this->m_fRotAxisX * fVal + this->m_fPosX;
        this->m_fPosY = v51 + this->m_fPosY;
        this->m_fPosZ = v57 + this->m_fPosZ;
        if ( fabs(this->m_fPosY - *(float *)&this->m_nDispWndColor) > this->m_fPathTargetY )
        {
          this->m_nMoveMode = this->m_nPrevMoveMode;
LABEL_28:
          (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(1.0);
        }
      }
      else
      {
        this->RoleSystem::PathFollowUpdate();
        if ( this->m_nMoveSubMode )
        {
          this->m_fRotAxisX = this->m_nMovement;
          this->m_fRotAxisY = this->m_fSavedRotX;
          LODWORD(this->m_fRotAxisZ) = (unsigned long)((UIWnd *)&this->m_FrameA);
          this->RoleSystem::UpdatePosition();
          this->m_fRotAxisX = fVal * this->m_fRotAxisX;
          this->m_fRotAxisY = fVal * this->m_fRotAxisY;
          this->m_fRotAxisZ = fVal * this->m_fRotAxisZ;
          *(float *)&this->m_fontcolor.Color = this->m_fRotAxisX + *(float *)&this->m_fontcolor.Color;
          *(float *)&this->m_wndcolor.Color = this->m_fRotAxisY + *(float *)&this->m_wndcolor.Color;
          *(float *)&this->m_id = this->m_fRotAxisZ + *(float *)&this->m_id;
          v17 = *(float *)&this->m_fontcolor.Color;
          v18 = *(float *)&this->m_id;
          this->m_fPosX = v17;
          this->m_wndcolor.Color = 0;
          this->m_fPosZ = v18;
          *(float *)&this->m_nDispFontColor = v17;
          *(float *)&this->m_nTodo_9C = v18;
        }
        else
        {
          this->RoleSystem::UpdateMovement(this->m_fPathAngle, 1);
          v19 = *(&this->m_partyActor.m_nUpdateMode + 7);
          *(&this->m_partyActor.m_nUpdateMode + 6) = 1;
          if ( v19 == 1 )
          {
            this->m_nCoreState = 5;
            this->RoleSystem::UpdateTransform();
            this->m_fRotAxisX = 0.0f;
            this->m_fRotAxisY = 1.0f;
          }
          else
          {
            this->m_nCoreState = 6;
            this->RoleSystem::UpdateTransform();
            this->m_fRotAxisX = 0.0f;
            this->m_fRotAxisY = -1.0f;
          }
          this->m_fRotAxisZ = 0.0f;
LABEL_25:
          this->m_fRotAxisX = this->m_fRotAxisX * 40.0f;
          this->m_fRotAxisY = this->m_fRotAxisY * 40.0f;
          this->m_fRotAxisZ = this->m_fRotAxisZ * 40.0f;
        }
      }
      return;
    case 9:
      v14 = fVal + this->m_fPathSpeed;
      this->m_fPathSpeed = v14;
      if ( v14 < this->m_fPathAngle )
      {
        v16 = (1.0 - cos(v14 / this->m_fPathAngle * 3.1415927)) * 0.5;
        *(float *)&this->m_partyActor.m_fScale = (1.0 - v16) * this->m_fPathTargetY
                                               + *((float *)&this->m_partyActor.m_nUpdateMode + 8) * v16;
      }
      else
      {
        v15 = this->m_nPrevMoveMode;
        *(_DWORD *)&this->m_partyActor.m_fScale = *(&this->m_partyActor.m_nUpdateMode + 8);
        this->m_nMoveMode = v15;
      }
      return;
    case 0xA:
      v9 = fVal + this->m_fPathSpeed;
      this->m_fPathSpeed = v9;
      if ( v9 < this->m_fPathAngle )
      {
        v11 = v9 / this->m_fPathAngle;
        v12 = (*(float *)&this->m_FrameA.m_rect.bottom - *(float *)&this->m_FrameA.m_childs.m_needscriptdel) * v11
            + *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
        v50 = (*(float *)&this->m_FrameA.m_pfather - *(float *)&this->m_FrameA.m_bcreateok) * v11
            + *(float *)&this->m_FrameA.m_bcreateok;
        v13 = (*(float *)&this->m_FrameA.m_childs.m_pData - *(float *)&this->m_FrameA.m_bvisible) * v11
            + *(float *)&this->m_FrameA.m_bvisible;
        this->m_fPosY = v50;
        v56 = v13;
        this->m_fPosX = v12;
        this->m_fPosZ = v56;
        this->m_fontcolor.Color = LODWORD(this->m_fPosX);
        this->m_wndcolor.Color = LODWORD(this->m_fPosY);
        this->m_id = LODWORD(this->m_fPosZ);
        this->m_wndcolor.Color = 0;
        this->RoleSystem::SetMoveSpeed(0.0, 0, v48);
      }
      else
      {
        v10 = *(float *)&this->m_FrameA.m_rect.bottom;
        this->m_fPosX = v10;
        LODWORD(this->m_fPosY) = this->m_FrameA.m_pfather;
        LODWORD(this->m_fPosZ) = this->m_FrameA.m_childs.m_pData;
        *(float *)&this->m_fontcolor.Color = v10;
        this->m_wndcolor.Color = LODWORD(this->m_fPosY);
        this->m_id = LODWORD(this->m_fPosZ);
        this->m_nMoveMode = this->m_nPrevMoveMode;
        this->m_wndcolor.Color = 0;
        this->RoleSystem::Notify();
        this->m_partyActor.m_pRoleObj = 0;
        this->RoleSystem::GetCurrentTile();
      }
      return;
    case 0xB:
      v3 = fVal + this->m_fPathSpeed;
      this->m_fPathSpeed = v3;
      if ( v3 >= this->m_fPathAngle )
      {
        v4 = this->m_nPrevMoveMode;
        this->m_fPathSpeed = this->m_fPathAngle;
        this->m_nMoveMode = v4;
        *(_DWORD *)&this->m_partyActor.m_fScale = 1065353216;
        this->RoleSystem::Notify();
      }
      v5 = *(&this->m_partyActor.m_nUpdateMode + 6) == 1;
      v6 = (1.0 - cos(this->m_fPathSpeed / this->m_fPathAngle * 3.1415927)) * 0.5;
      this->m_fPosX = *(float *)&this->m_FrameA.m_childs.m_needscriptdel * (1.0f - v6)
                    + *((float *)&this->m_partyActor.m_nUpdateMode + 8) * v6;
      this->m_fPosY = *(float *)&this->m_FrameA.m_bcreateok * (1.0f - v6) + this->m_fPathTargetY * v6;
      this->m_fPosZ = *(float *)&this->m_FrameA.m_bvisible * (1.0f - v6) + this->m_fPathTargetZ * v6;
      if ( v5 )
      {
        m_nMoveMode = this->m_nMoveMode;
        *(float *)&this->m_FrameA.m_rect.bottom = (float)(int)(__int64)(v6 * 90.0);
        if ( m_nMoveMode == 4 )
          *(float *)&this->m_partyActor.m_fScale = 1.0 - v6 + v6 * 0.69999999;
      }
      else
      {
        v8 = this->m_nMoveMode;
        *(float *)&this->m_FrameA.m_rect.bottom = (float)(int)(__int64)((1.0 - v6) * 90.0);
        if ( v8 == 4 )
          *(float *)&this->m_partyActor.m_fScale = (1.0 - v6) * 0.69999999 + v6;
      }
      return;
    case 0x15:
      this->m_fPathSpeed = fVal + this->m_fPathSpeed;
      if ( (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::GetVisNode() || this->m_fPathSpeed > 10.0f )
      {
        this->m_nMoveMode = this->m_nPrevMoveMode;
LABEL_91:
        this->RoleSystem::NotifyMoveComplete();
      }
      return;
    case 0x2C:
      this->m_fPathSpeed = fVal + this->m_fPathSpeed;
      if ( (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::GetVisNode() )
        this->RoleSystem::Notify();
      return;
    default:
      return;
  }
}

// 0x004161E0
void RoleSystem::ScaleVector(float *pVec, float fScale)
{
  float v2; // st7
  float v3; // st7

  v2 = (((gbVec3D *)pVec))->gbVec3D::Length();
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
  float v5; // st7
  gbColorQuad *p_m_fontcolor; // edi
  float v7; // st6
  float v8; // st7
  float v9; // st6
  float v10; // st5
  float v11; // eax
  RoleSystem *v12; // eax
  float v13; // eax
  unsigned int v14; // ecx
  unsigned int v15; // edx
  int *m_nState; // [esp-0xC] [ebp-0x48]
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

  if ( !this->m_pCtrlPoint && !*(_DWORD *)(thisa + 1456) && this->m_partyActor.m_nState == *(_DWORD *)(thisa + 628) )
  {
    v5 = *(float *)&this->m_fontcolor.Color - *(float *)(thisa + 4);
    p_m_fontcolor = (gbColorQuad *)&this->m_fontcolor;
    v19 = *(float *)&this->m_wndcolor.Color - *(float *)(thisa + 8);
    v7 = *(float *)&this->m_id - *(float *)(thisa + 12);
    v21.y = v19;
    v20 = v7;
    v21.x = v5;
    v21.z = v20;
    v8 = (((gbVec3D *)&v21))->gbVec3D::Length();
    *(float *)&thisb = *(float *)(thisa + 16) + *(float *)&this->m_rect.left;
    if ( v8 <= *(float *)&thisb )
    {
      v9 = *(float *)&p_m_fontcolor->Color - *(float *)(thisa + 4);
      v22 = *(float *)&this->m_wndcolor.Color - *(float *)(thisa + 8);
      v10 = *(float *)&this->m_id - *(float *)(thisa + 12);
      v18 = *(float *)&p_m_fontcolor->Color;
      v23 = v10;
      v19 = *(float *)&this->m_wndcolor.Color;
      v11 = *(float *)&this->m_id;
      m_nState = (int *)this->m_partyActor.m_nState;
      thisc = (*(float *)&thisb * 1.100000023841858f - v8) / v8;
      v24 = v22 * thisc;
      v25 = v23 * thisc;
      v18 = v18 + v9 * thisc;
      v19 = v19 + v24;
      v20 = v11 + v25;
      v12 = (RoleSystem *)UISceneUpdate();
      if ( (((RoleSystem *)v12))->RoleSystem::CheckMoveCollision(m_nState, &v18, 255) )
      {
        this->m_fCachePosX = this->m_fPosX;
        v13 = v18;
        this->m_fCachePosY = this->m_fPosY;
        v14 = LODWORD(v19);
        this->m_fCachePosZ = this->m_fPosZ;
        v15 = LODWORD(v20);
        this->m_wndcolor.Color = v14;
        *(float *)&p_m_fontcolor->Color = v13;
        this->m_id = v15;
        this->RoleSystem::SetMoveSpeed(0.0, 0, v17);
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
  int m_nState; // [esp-0x4] [ebp-0x24]
  _BYTE v9[12]; // [esp+0x8] [ebp-0x18]
  gbVec3D pTarget; // [esp+0x14] [ebp-0xC] BYREF

  m_nState = this->m_partyActor.m_nState;
  v4 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v4))->RoleSystem::GetRolePtr(m_nState);
  *(_DWORD *)&v9[4] = 0;
  if ( nTileX >= 0 )
  {
    v6 = *(_DWORD *)(RolePtr + 152);
    if ( nTileX < v6 && nTileY >= 0 && nTileY < *(_DWORD *)(RolePtr + 156) )
      *(float *)&v9[4] = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (nTileX + nTileY * v6));
  }
  *(float *)v9 = ((double)nTileX + 0.5) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 128);
  *(float *)&v9[8] = ((double)nTileY + 0.5) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 136);
  pTarget = *(gbVec3D *)v9;
  this->RoleSystem::SetTargetRotation(&pTarget);
  result = (int)g_pRoleSystem;
  if ( this == g_pRoleSystem )
  {
    result = *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1);
    if ( result )
      ScriptPoolPage_Alloc((_Console *)g_pCameraCtrl);
  }
  return result;
}

// 0x004164E0
BOOL RoleSystem::IsPathMoving()
{
  return this->m_nMoveMode == 4 && *(&this->m_partyActor.m_nUpdateMode + 5) == 10;
}

// 0x00416500
int RoleSystem::IsActionBlocked()
{
  int v2; // ecx

  if ( this->m_partyActor.m_nAnimBuffer )
  {
    if ( this->m_partyActor.m_nUpdateMode == 4 )
    {
      if ( *(&this->m_partyActor.m_nAnimCounter + 6) != 2 || *(&this->m_partyActor.m_nAnimCounter + 7) != -1 )
        return 1;
    }
    else
    {
      v2 = *(&this->m_partyActor.m_nUpdateMode + 1);
      if ( v2 && v2 != 12 && v2 != 3 )
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
  float m_fRotAxisZ; // edx
  float z; // edx
  float v9; // ecx
  float v10; // edx
  gbVec3D v11; // [esp+0x4] [ebp-0x18] BYREF
  float m_fPosX; // [esp+0x10] [ebp-0xC]
  float m_fPosY; // [esp+0x14] [ebp-0x8]
  float v14; // [esp+0x18] [ebp-0x4]

  m_fPosX = this->m_fPosX;
  m_fPosY = this->m_fPosY;
  m_fPosZ = this->m_fPosZ;
  v11.x = *pTargetPos;
  v14 = m_fPosZ;
  v11.y = 0.0f;
  v5 = pTargetPos[2];
  v11.x = v11.x - m_fPosX;
  v11.z = v5 - m_fPosZ;
  if ( (((gbVec3D *)&v11))->gbVec3D::Length() >= 0.0049999999 )
  {
    m_fPosX = this->m_fRotAxisX;
    x = v11.x;
    m_fPosY = this->m_fRotAxisY;
    m_fRotAxisZ = this->m_fRotAxisZ;
    this->m_fRotAxisY = v11.y;
    v14 = m_fRotAxisZ;
    z = v11.z;
    this->m_fRotAxisX = x;
    this->m_fRotAxisZ = z;
    this->RoleSystem::UpdatePosition();
    v9 = m_fPosY;
    v10 = v14;
    this->m_fRotAxisX = m_fPosX;
    this->m_fRotAxisY = v9;
    this->m_fRotAxisZ = v10;
  }
}

// 0x00416620
int RoleSystem::UpdateMovement(float fDeltaTime, int nMode)
{
  int m_nMoveMode; // eax
  long double v5; // st7
  float v6; // edx
  long double v7; // st7
  float v8; // st7
  float v9; // st6
  float v10; // st5
  int result; // eax
  int v12; // [esp+0xC] [ebp-0x8]
  int v13; // [esp+0x10] [ebp-0x4]

  if ( nMode )
  {
    *(&this[1].m_partyActor.m_fSpeed + 1) = fDeltaTime;
  }
  else
  {
    m_nMoveMode = this->m_nMoveMode;
    *(&this->m_partyActor.m_nUpdateMode + 5) = 3;
    if ( m_nMoveMode != 4 )
      this->m_nPrevMoveMode = m_nMoveMode;
    v5 = fDeltaTime - *(&this[1].m_partyActor.m_fSpeed + 1);
    v6 = *(&this[1].m_partyActor.m_fSpeed + 1);
    this->m_nMoveMode = 4;
    *((float *)&this->m_partyActor.m_nUpdateMode + 8) = fDeltaTime;
    this->m_fPathTargetY = v6;
    this->m_fPathSpeed = 0.0f;
    this->m_nTransformState = 0.0f;
    this->m_fMovement = 0.0f;
    this->m_fPathAngle = fabs(v5) * 0.008333333767950535f;
    this->m_fRotAxisX = 0.0f;
    this->m_fRotAxisY = 0.0f;
    this->m_fRotAxisZ = 0.0f;
    this->m_nMovement = 0.0f;
    this->m_fSavedRotX = this->m_fRotAxisY;
    *(float *)((UIWnd *)&this->m_FrameA) = this->m_fRotAxisZ;
    this->RoleSystem::UpdatePath(1);
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
  result = v12;
  this->m_childs.m_pData = ((char *)((char *)v12));
  *(float *)&v13 = v9 - v10;
  *(float *)&this->m_pfather = v8;
  this->m_childs.capacity = v13;
  return result;
}

// 0x00416790
void RoleSystem::UpdateAnimation(float *pfVal)
{
  float v4; // eax
  float v5; // st7
  int m_nRoleCount; // ecx
  float v7; // st7
  int v8; // eax
  CScreenMode *m_nAnimation; // ecx
  PtrArray *SoundList; // eax
  float v11; // st7
  float v12; // edx
  int v13; // ecx
  RoleSystem *v14; // ebx
  int RolePtr; // edi
  bool v16; // cc
  _DWORD *v17; // eax
  int v18; // ecx
  float *v19; // eax
  float v20; // st7
  float v21; // st6
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
    if ( this->m_nActiveRole && pfVal != (float *)this->m_nRoleCount )
      this->RoleSystem::GetActiveRole();
    this->m_nActiveRole = 1;
    this->m_nRoleCount = (int)pfVal;
    LODWORD(v23.x) = this->m_fontcolor.Color;
    v4 = *(float *)&this->m_id;
    LODWORD(v23.y) = this->m_wndcolor.Color;
    v23.z = v4;
    v23.x = v23.x - pfVal[1];
    v23.y = v23.y - pfVal[2];
    v23.z = v4 - pfVal[3];
    v5 = (((gbVec3D *)&v23))->gbVec3D::Length();
    m_nRoleCount = this->m_nRoleCount;
    v7 = v5 - *(float *)(m_nRoleCount + 16);
    if ( v7 >= 0.0f )
      pfVala = v7;
    else
      pfVala = 0.0f;
    *(_DWORD *)(m_nRoleCount + 1388) = 4;
    if ( *((_BYTE *)pfVal + 173) == 1 )
    {
      if ( pfVala >= (double)flt_C10D44 )
      {
        v11 = pfVal[5];
        v12 = pfVal[7];
        v25 = 0.0f;
        v26 = v12;
        v27 = pfVal[5];
        v13 = *((_DWORD *)pfVal + 6);
        pfValc = *(float *)&g_palScript.m_fSceneTileSize + *(float *)&g_palScript.m_fSceneTileSize;
        v29 = v12;
        v28 = v13;
        v26 = v12 * pfValc;
        v24 = v11 * pfValc + pfVal[1];
        v25 = pfVal[2] + 0.0f;
        v26 = v26 + pfVal[3];
        v27 = *(float *)&g_palScript.m_fSceneTileSize * v27;
        v29 = v12 * *(float *)&g_palScript.m_fSceneTileSize;
        v14 = (RoleSystem *)UISceneUpdate();
        RolePtr = (((RoleSystem *)v14))->RoleSystem::GetRolePtr(*((_DWORD *)pfVal + 157));
        pfValb = 0;
        do
        {
          if ( (((RoleSystem *)v14))->RoleSystem::CheckCollision((int *)this->m_partyActor.m_nState, (__int64)((v24 - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize)) )
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
        this->RoleSystem::MoveToTileCheck((__int64)((v27 + v24 - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize), (__int64)((v26 - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize), 1);
      }
      else
      {
        (((PalScriptMgr *)this->m_nRoleCount))->PalScriptMgr::Destroy();
        this->m_nAnimation = v8;
        if ( v8 )
        {
          this->RoleSystem::IsPathComplete((float *)(this->m_nRoleCount + 4), 1);
          this->RoleSystem::Notify();
          m_nAnimation = (CScreenMode *)this->m_nAnimation;
          this->m_nActiveRole = 2;
          v22 = (int)m_nAnimation;
          SoundList = (((CScreenMode *)m_nAnimation))->CScreenMode::GetSoundList();
          (((PtrArray *)SoundList))->PtrArray::SetResolution(0, v22);
        }
        else
        {
          this->RoleSystem::GetActiveRole();
        }
      }
    }
    else
    {
      v17 = (_DWORD *)this->m_nRoleCount;
      if ( !v17[125] )
      {
        v18 = (unsigned long)v17[317];
        if ( v18 != 3 )
        {
          this->m_nAnimCopy1 = v18;
          this->m_nAnimCopy3 = v17[2172];
          this->m_nAnimCopy2 = v17[321];
          v17[324] = this->m_fontcolor.Color;
          v17[325] = this->m_wndcolor.Color;
          v17[326] = this->m_id;
          v19 = (float *)this->m_nRoleCount;
          v19[324] = v19[324] - v19[1];
          v19[325] = v19[325] - v19[2];
          v19[326] = v19[326] - v19[3];
          (((RoleSystem *)this->m_nRoleCount))->RoleSystem::UpdatePosition();
          (((RoleSystem *)this->m_nRoleCount))->RoleSystem::Notify();
        }
      }
      if ( pfVala >= (double)flt_C10D44 )
      {
        v23.y = v23.y * -1.0f;
        v23.z = v23.z * -1.0f;
        v20 = v23.x * -1.0f / pfVala;
        v23.y = v23.y / pfVala;
        v23.z = v23.z / pfVala;
        v21 = flt_C10D44 - 10.0f;
        pfVald = v21;
        v23.y = v23.y * pfVald;
        v23.z = v23.z * pfVald;
        v23.x = v20 * v21 + pfVal[1];
        v23.y = v23.y + pfVal[2];
        v23.z = v23.z + pfVal[3];
        this->RoleSystem::BindPartyToScene(&v23.x, 1);
      }
      else
      {
        this->m_nActiveRole = 2;
      }
    }
  }
}

// 0x00416BC0
void RoleSystem::ProcessInteraction()
{
  int m_nRoleCount; // eax
  float v3; // st7
  int v4; // ecx
  float v5; // st7
  int m_nActiveRole; // eax
  int v7; // eax
  int v8; // eax
  PalScriptMgr *v9; // ecx
  int v10; // eax
  CScreenMode *v11; // ecx
  PtrArray *SoundList; // eax
  int v13; // eax
  _DWORD *v14; // eax
  int v15; // eax
  CScreenMode *v16; // ecx
  PtrArray *v17; // eax
  float *v18; // eax
  int v19; // eax
  int v20; // eax
  _DWORD *v21; // esi
  int v22; // [esp-0x4] [ebp-0x24]
  int v23; // [esp-0x4] [ebp-0x24]
  _BYTE v24[12]; // [esp+0x8] [ebp-0x18]
  gbVec3D v25; // [esp+0x14] [ebp-0xC] BYREF

  m_nRoleCount = this->m_nRoleCount;
  if ( !m_nRoleCount )
  {
    this->RoleSystem::GetActiveRole();
    return;
  }
  *(float *)v24 = *(float *)(m_nRoleCount + 4) - *(float *)&this->m_fontcolor.Color;
  *(float *)&v24[4] = *(float *)(m_nRoleCount + 8) - *(float *)&this->m_wndcolor.Color;
  v25 = *(gbVec3D *)v24;
  v3 = (((gbVec3D *)&v25))->gbVec3D::Length();
  v4 = this->m_nRoleCount;
  v5 = v3 - *(float *)(v4 + 16);
  if ( v5 < 0.0f )
    v5 = 0.0f;
  m_nActiveRole = this->m_nActiveRole;
  if ( *(_BYTE *)(v4 + 173) == 1 )
  {
    v7 = m_nActiveRole - 1;
    if ( v7 )
    {
      if ( v7 == 1 )
      {
        PalScriptMgr::ClearAllScript();
        if ( !v8 )
        {
          *(_DWORD *)(this->m_nRoleCount + 1388) = 0;
LABEL_10:
          this->m_nActiveRole = 0;
          this->m_nRoleCount = 0;
          this->m_nAnimation = 0;
        }
      }
    }
    else if ( !this->m_nMoveSubMode || v5 < flt_C10D44 )
    {
      this->RoleSystem::IsPathComplete((float *)(v4 + 4), 1);
      this->RoleSystem::Notify();
      (((PalScriptMgr *)v9))->PalScriptMgr::Destroy();
      this->m_nAnimation = v10;
      v22 = v10;
      SoundList = (((CScreenMode *)v11))->CScreenMode::GetSoundList();
      (((PtrArray *)SoundList))->PtrArray::SetResolution(0, v22);
      this->m_nActiveRole = 2;
    }
  }
  else if ( m_nActiveRole > 0 )
  {
    if ( m_nActiveRole <= 2 )
    {
      if ( v5 < flt_C10D44 )
      {
        (((PalScriptMgr *)*(PalScriptMgr **)(v4 + 264)))->PalScriptMgr::Destroy();
        this->m_nAnimation = v15;
        if ( v15 )
        {
          v23 = v15;
          v17 = (((CScreenMode *)v16))->CScreenMode::GetSoundList();
          (((PtrArray *)v17))->PtrArray::SetResolution(0, v23);
          v18 = (float *)this->m_nRoleCount;
          this->m_nActiveRole = 3;
          this->m_fRotAxisX = *++v18;
          this->m_fRotAxisY = v18[1];
          this->m_fRotAxisZ = v18[2];
          this->m_fRotAxisX = this->m_fRotAxisX - *(float *)&this->m_fontcolor.Color;
          this->m_fRotAxisY = this->m_fRotAxisY - *(float *)&this->m_wndcolor.Color;
          this->m_fRotAxisZ = this->m_fRotAxisZ - *(float *)&this->m_id;
          this->RoleSystem::UpdatePosition();
          v19 = this->m_nRoleCount;
          if ( !*(_DWORD *)(v19 + 500) && *(_DWORD *)(v19 + 1268) != 3 )
          {
            *(float *)(v19 + 1296) = this->m_fRotAxisX;
            *(float *)(v19 + 1300) = this->m_fRotAxisY;
            *(float *)(v19 + 1304) = this->m_fRotAxisZ;
          }
          this->RoleSystem::Notify();
          v20 = this->m_nRoleCount;
          if ( !*(_DWORD *)(v20 + 500) && *(_DWORD *)(v20 + 1268) != 3 )
          {
            *(float *)(v20 + 1296) = *(float *)(v20 + 1296) * -1.0;
            *(float *)(v20 + 1300) = *(float *)(v20 + 1300) * -1.0;
            *(float *)(v20 + 1304) = *(float *)(v20 + 1304) * -1.0;
            (((RoleSystem *)this->m_nRoleCount))->RoleSystem::UpdatePosition();
            v21 = (_DWORD *)this->m_nRoleCount;
            v21[324] = 0;
            v21 += 324;
            v21[1] = 0;
            v21[2] = 0;
          }
        }
        else
        {
          this->RoleSystem::GetActiveRole();
        }
      }
    }
    else if ( m_nActiveRole == 3 )
    {
      PalScriptMgr::ClearAllScript();
      if ( !v13 )
      {
        v14 = (_DWORD *)this->m_nRoleCount;
        if ( !v14[125] && v14[317] != 3 )
        {
          v14[321] = this->m_nAnimCopy2;
          *(_DWORD *)(this->m_nRoleCount + 1268) = this->m_nAnimCopy1;
          (((RoleSystem *)this->m_nRoleCount))->RoleSystem::UpdateMovement(*(float *)&this->m_nAnimCopy3, 1);
          (((RoleSystem *)this->m_nRoleCount))->RoleSystem::UpdateTransform();
        }
        *(_DWORD *)(this->m_nRoleCount + 1388) = 0;
        goto LABEL_10;
      }
    }
  }
}

// 0x00416F10
int RoleSystem::GetActiveRole()
{
  int result; // eax

  result = this->m_nRoleCount;
  this->m_nActiveRole = 0;
  if ( result )
  {
    if ( *(_BYTE *)(result + 173) != 1 && !*(_DWORD *)(result + 500) && *(_DWORD *)(result + 1268) != 3 )
    {
      *(_DWORD *)(result + 1284) = this->m_nAnimCopy2;
      *(_DWORD *)(this->m_nRoleCount + 1268) = this->m_nAnimCopy1;
      (((RoleSystem *)this->m_nRoleCount))->RoleSystem::UpdateMovement(*(float *)&this->m_nAnimCopy3, 1);
      result = (((RoleSystem *)this->m_nRoleCount))->RoleSystem::UpdateTransform();
    }
    *(_DWORD *)(this->m_nRoleCount + 1388) = 0;
    this->m_nRoleCount = 0;
  }
  return result;
}

// 0x00416FA0
void RoleSystem::InitPathTracking(float *nFlags)
{
  int m_nMoveMode; // eax

  m_nMoveMode = this->m_nMoveMode;
  *(&this->m_partyActor.m_nUpdateMode + 5) = 4;
  *(&this->m_partyActor.m_nUpdateMode + 6) = 0;
  if ( m_nMoveMode != 4 )
    this->m_nPrevMoveMode = m_nMoveMode;
  this->m_nMoveMode = 4;
  this->RoleSystem::SetMoveTarget(nFlags, 1);
}

// 0x00416FE0
void RoleSystem::RestoreMoveMode(float *nFlags)
{
  int m_nMoveMode; // eax

  if ( this->m_nMoveMode == 4 )
  {
    this->m_nMoveMode = this->m_nPrevMoveMode;
    this->RoleSystem::NotifyMoveComplete();
  }
  m_nMoveMode = this->m_nMoveMode;
  *(&this->m_partyActor.m_nUpdateMode + 5) = 5;
  *(&this->m_partyActor.m_nUpdateMode + 6) = 0;
  if ( m_nMoveMode != 4 )
    this->m_nPrevMoveMode = m_nMoveMode;
  this->m_nMoveMode = 4;
  this->RoleSystem::SetMoveTarget(nFlags, 1);
}

// 0x00417040
void RoleSystem::SetupMoveState(float *pfVal)
{
  char *p_m_nFacing; // eax
  int v5; // edi
  char *p_m_nAnimState; // esi
  _BYTE *p_m_byStateArray; // esi
  int *p_m_szModelPath; // esi
  int *p_m_nParamArray; // ecx
  int v10; // edx
  float *v11; // edx
  gbVec3D *p_m_vecPosArray; // ecx
  float v13; // esi
  int *p_m_nRoleState0; // eax
  int v15; // ecx
  unsigned int v16; // edx
  int v17; // ecx
  unsigned int m_nSpawnParam; // eax
  float *v19; // edi
  int *v20; // esi
  char v21; // cl
  int v22; // eax
  int *p_m_fMoveTargetY; // ecx
  char *v24; // eax
  char *m_pLinkedSystem; // ecx
  int v26; // [esp+0x0] [ebp-0x20]
  int pfVala; // [esp+0x24] [ebp+0x4]

  this->RoleSystem::InitDefaultState();
  p_m_nFacing = (char *)&this->m_nFacing;
  v5 = (char *)pfVal - &this->m_nFacing;
  this->m_nFacing = *(_BYTE *)pfVal;
  this->m_nActionState = *((_BYTE *)pfVal + 1);
  p_m_nAnimState = (char *)&this->m_nAnimState;
  do
  {
    *p_m_nAnimState = p_m_nAnimState[v5];
    ++p_m_nAnimState;
  }
  while ( (unsigned int)&p_m_nAnimState[-2 - (_DWORD)&this->m_nFacing] < 0x20 );
  p_m_byStateArray = (_BYTE *)&this->m_byStateArray;
  do
  {
    *p_m_byStateArray = p_m_byStateArray[v5];
    ++p_m_byStateArray;
  }
  while ( (unsigned int)&p_m_byStateArray[-34 - (_DWORD)p_m_nFacing] < 0x20 );
  p_m_szModelPath = (int *)&this->m_szModelPath;
  *(float *)&this->m_nSpawnFlags = pfVal[17];
  this->m_nRoleAction = *((_BYTE *)pfVal + 72);
  this->m_fWaypointX = pfVal[19];
  this->m_fWaypointZ = pfVal[20];
  this->m_nActionParam = *((_BYTE *)pfVal + 84);
  *(float *)&this->m_nInitMoveMode = pfVal[22];
  this->m_nSpawnExtra = (int)pfVal[23];
  this->m_nSpawnParam2 = (int)pfVal[24];
  do
  {
    *(_BYTE *)p_m_szModelPath = *((_BYTE *)p_m_szModelPath + v5);
    p_m_szModelPath = (int *)((char *)p_m_szModelPath + 1);
  }
  while ( (unsigned int)p_m_szModelPath - 100 - (unsigned int)p_m_nFacing < 0x10 );
  p_m_nParamArray = (int *)&this->m_nParamArray;
  v10 = 3;
  do
  {
    *p_m_nParamArray = *(int *)((char *)p_m_nParamArray + v5);
    ++p_m_nParamArray;
    --v10;
  }
  while ( v10 );
  this->m_bSpawnByteA = *((_BYTE *)pfVal + 128);
  this->m_bSpawnByteB = *((_BYTE *)pfVal + 129);
  this->m_nSpawnParam = (int)pfVal[33];
  v11 = (float *)(pfVal + 34);
  p_m_vecPosArray = (gbVec3D *)&this->m_vecPosArray;
  pfVala = 16;
  do
  {
    v13 = *v11;
    v11 += 3;
    p_m_vecPosArray[-1].z = v13;
    p_m_vecPosArray->x = *(float *)((char *)&p_m_vecPosArray->x + (char *)(pfVal + 33) - (char *)&this->m_nSpawnParam);
    p_m_vecPosArray->y = *(v11 - 1);
    ++p_m_vecPosArray;
    --pfVala;
  }
  while ( pfVala );
  this->m_partyActor.m_nCachedA = (int)pfVal[82];
  *(float *)&this->m_partyActor.m_nCachedB = pfVal[83];
  this->m_partyActor.m_nTransform = (int)pfVal[84];
  p_m_nRoleState0 = (int *)&this->m_partyActor.m_nRoleState0;
  v15 = 29;
  do
  {
    *p_m_nRoleState0 = *(int *)((char *)p_m_nRoleState0 + v5);
    ++p_m_nRoleState0;
    --v15;
  }
  while ( v15 );
  (((Camera *)this))->Camera::InitFromScene((const char *)pfVal + 2);
  memset(&this->m_partyActor.m_nUpdateMode + 5, 0, 0x24u);
  this->RoleSystem::NotifySceneChange(*((unsigned __int8 *)pfVal + 72));
  v16 = *((unsigned int *)pfVal + 20);
  this->m_fontcolor.Color = (unsigned int)pfVal[19];
  this->m_wndcolor.Color = 0;
  this->m_id = v16;
  *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 2) = this->m_fontcolor.Color;
  *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 3) = this->m_wndcolor.Color;
  LODWORD(this[1].m_partyActor.m_fAngleDeg) = this->m_id;
  this->m_partyActor.m_pRoleObj = *((unsigned __int8 *)pfVal + 84);
  this->RoleSystem::UpdateMovement(pfVal[17], 1);
  if ( *((_BYTE *)pfVal + 1) == 2 )
  {
    this->m_nTransformMode = 0;
    (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)pfVal + 29));
    this->m_pLinkedSystem = ((char *)(v24));
    this->RoleSystem::Notify();
    m_pLinkedSystem = (char *)this->m_pLinkedSystem;
    switch ( m_pLinkedSystem[753] )
    {
      case 0:
      case 1:
        LODWORD(this->m_fAnimSpeed) = g_RoleSystemData.m_nEffParamBase0;
        break;
      case 2:
        LODWORD(this->m_fAnimSpeed) = g_RoleSystemData.m_nEffParam14;
        break;
      case 3:
        LODWORD(this->m_fAnimSpeed) = g_RoleSystemData.m_nEffTypeCode;
        break;
      default:
        this->m_fAnimSpeed = 0.0f;
        break;
    }
    if ( m_pLinkedSystem[753] )
      this->RoleSystem::StartHalfSpeedMovement();
    this->m_nMoveMode = 5;
  }
  else
  {
    this->m_nMoveMode = 1;
    switch ( *((_DWORD *)pfVal + 22) )
    {
      case 0:
        this->m_nMoveSubMode = *(_DWORD *)&this->m_nInitMoveMode;
        break;
      case 1:
        this->RoleSystem::StartHalfSpeedMovement();
        this->m_nMoveSubMode = *(_DWORD *)&this->m_nInitMoveMode;
        break;
      case 2:
        m_nSpawnParam = this->m_nSpawnParam;
        this->m_partyUI3.m_pfather = ((UIWnd *)((UIWnd *)m_nSpawnParam));
        m_nSpawnParam *= 12;
        qmemcpy(&this->m_fMoveTargetX, &this->m_nActionTimer, 4 * (m_nSpawnParam >> 2));
        v20 = (int *)(&this->m_nActionTimer + (m_nSpawnParam >> 2));
        v19 = (float *)(&this->m_fMoveTargetX + (m_nSpawnParam >> 2));
        v21 = m_nSpawnParam;
        v22 = 0;
        qmemcpy(v19, v20, v21 & 3);
        if ( (int)this->m_partyUI3.m_pfather > 0 )
        {
          p_m_fMoveTargetY = (int *)&this->m_fMoveTargetY;
          do
          {
            *p_m_fMoveTargetY = 0;
            ++v22;
            p_m_fMoveTargetY += 3;
          }
          while ( v22 < (int)this->m_partyUI3.m_pfather );
        }
        (((PathObj *)&this->m_fMoveTargetX))->PathObj::CalcLength();
        this->m_nMoveSubMode = 9;
        this->m_nMoveReset = 0;
        break;
      case 3:
        SetMaterialName((Actor *)&this->m_partyActor.m_Actor, &this->m_szModelPath, 0);
        if ( !*((_DWORD *)pfVal + 83) )
        {
          (*(void ( **)(gbActor *, int))(*(_DWORD *)((gbChain1DNode *)this->m_partyActor.m_pActor) + 24))(
            this->m_partyActor.m_pActor,
            -1082130432);
          (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(0.0);
        }
        LODWORD(this->m_fPosX) = this->m_fontcolor.Color;
        LODWORD(this->m_fPosY) = this->m_wndcolor.Color;
        LODWORD(this->m_fPosZ) = this->m_id;
        v17 = *(_DWORD *)&this->m_nInitMoveMode;
        this->m_fPosY = pfVal[24];
        this->m_nMoveSubMode = v17;
        break;
      default:
        break;
    }
  }
  this->m_nPrevMoveMode = this->m_nMoveMode;
  this->m_fMoveRadius = g_RoleSystemData._todo_104 * this->m_fAnimSpeed;
  LODWORD(this->m_fMoveSpeed) = g_RoleSystemData.m_nEffParamB4;
  if ( *((_DWORD *)pfVal + 22) != 3 )
    this->RoleSystem::SetMoveSpeed(0.0, 0, v26);
}

// 0x00417420
void RoleSystem::UpdateTransform(float arg0)
{
  gbTexture *bottom; // ecx
  float v4; // ecx
  float v5; // edx
  float v6; // st7
  float v7; // edx
  float v8; // eax
  float m_nTransformState; // ecx
  float v10; // st7
  float v11; // st7
  RoleSystem *v12; // ebx
  CScreenMode *SoundList; // eax
  float v14; // st7
  float v15; // st6
  float v16; // st7
  int v17; // eax
  BOOL v18; // eax
  BOOL v19; // ebx
  BOOL v20; // eax
  float *p_Color; // [esp-0x4] [ebp-0x38]
  gbVec3D v22; // [esp+0x10] [ebp-0x24] BYREF
  gbVec3D pfVal; // [esp+0x1C] [ebp-0x18] BYREF
  float m_fWaypointX; // [esp+0x28] [ebp-0xC] BYREF
  float v25; // [esp+0x2C] [ebp-0x8]
  float m_fWaypointZ; // [esp+0x30] [ebp-0x4]
  float arg0a; // [esp+0x38] [ebp+0x4]
  float arg0b; // [esp+0x38] [ebp+0x4]

  if ( this->m_nActionResult )
  {
    this->RoleSystem::PathFollowUpdate();
    switch ( this->m_nTransformMode )
    {
      case 0:
        if ( this->RoleSystem::CheckVisibility() )
          goto LABEL_16;
        this->RoleSystem::UpdateFollowVelocityEx();
        if ( g_nCameraUpdateCount > 0 )
          goto LABEL_20;
        this->RoleSystem::NotifyMoveComplete();
        this->RoleSystem::Notify();
        this->m_nTransformMode = 3;
        goto LABEL_19;
      case 1:
        if ( g_RoleSlotBuf.m_partyActor.m_szTexture[8] )
        {
          v4 = *(float *)&this->m_fontcolor.Color;
          v5 = *(float *)&this->m_wndcolor.Color;
          LODWORD(v22.z) = this->m_id;
          v22.x = v4;
          v22.y = v5;
          v22.x = v4 - *(float *)&g_pRoleSystem->m_fontcolor.Color;
          v22.y = v5 - *(float *)&g_pRoleSystem->m_wndcolor.Color;
          v22.z = v22.z - *(float *)&g_pRoleSystem->m_id;
          if ( this->m_fMoveSpeed * 1.4 >= (((gbVec3D *)&v22))->gbVec3D::Length() )
            goto LABEL_11;
        }
        else
        {
          this->RoleSystem::MoveRole((float *)&g_pRoleSystem->m_fontcolor.Color, g_pRoleSystem->m_partyActor.m_nState, 1, 0);
          v6 = *(float *)&this->m_fontcolor.Color - this->m_fWaypointX;
          v7 = *(float *)&this->m_wndcolor.Color;
          LODWORD(v22.z) = this->m_id;
          v22.y = v7;
          v22.x = v6;
          v22.z = v22.z - this->m_fWaypointZ;
          if ( (((gbVec3D *)&v22))->gbVec3D::Length() <= (double)this->m_fMoveRadius )
            goto LABEL_11;
        }
        pfVal.x = this->m_fWaypointX;
        pfVal.z = this->m_fWaypointZ;
        this->m_nTransformMode = 2;
        this->m_nMoveRole = 0;
        pfVal.y = 0.0f;
        this->RoleSystem::BindPartyToScene(&pfVal.x, 1);
        goto LABEL_11;
      case 2:
        if ( this->m_nMoveSubMode )
        {
          if ( this->RoleSystem::CheckVisibility() )
          {
LABEL_16:
            this->m_nTransformMode = 1;
            this->RoleSystem::EnterSubMode6();
            goto LABEL_19;
          }
        }
        else
        {
          this->m_nTransformMode = 0;
          this->RoleSystem::StartHalfSpeedMovement();
          this->m_FrameA.m_benable = this->m_rect.top;
          this->m_FrameA.m_bfocus = this->m_rect.right;
          bottom = *((gbTexture **)this + 7);
          this->m_FrameA.m_pbktex = ((gbTexture *)(bottom));
        }
LABEL_11:
        if ( g_nCameraUpdateCount > 0 )
          goto LABEL_20;
        this->RoleSystem::NotifyMoveComplete();
        this->RoleSystem::Notify();
        this->m_nTransformMode = 3;
LABEL_19:
        if ( g_nCameraUpdateCount <= 0 )
          return;
LABEL_20:
        if ( this->m_nMoveSubMode )
        {
          LODWORD(v22.x) = this->m_FrameA.m_fontcolor.Color;
          v8 = *(float *)&this->m_FrameA.m_id;
          LODWORD(v22.y) = this->m_FrameA.m_wndcolor.Color;
          v22.y = v22.y * arg0;
          v22.z = v8 * arg0;
          this->m_fRotAxisX = v22.x * arg0 + this->m_fRotAxisX;
          this->m_fRotAxisY = v22.y + this->m_fRotAxisY;
          this->m_fRotAxisZ = v22.z + this->m_fRotAxisZ;
          m_nTransformState = this->m_nTransformState;
          this->m_fRotAxisY = 0.0f;
          arg0a = m_nTransformState;
          v10 = (((gbVec3D *)&this->m_fRotAxisX))->gbVec3D::Length();
          if ( v10 > arg0a )
          {
            v11 = arg0a / v10;
            this->m_fRotAxisX = v11 * this->m_fRotAxisX;
            this->m_fRotAxisY = v11 * this->m_fRotAxisY;
            this->m_fRotAxisZ = v11 * this->m_fRotAxisZ;
          }
        }
        v12 = g_pRoleSystem;
        if ( !g_pRoleSystem )
          return;
        if ( g_pRoleSystem->m_nMoveMode == 4 )
          return;
        if ( g_nSceneState != 2 )
          return;
        SoundList = (CScreenMode *)(((CScreenMode *)bottom))->CScreenMode::GetSoundList();
        if ( !(((CScreenMode *)SoundList))->CScreenMode::IsAudioReady() )
          return;
        if ( 12.0 + 12.0 <= fabs(this->m_fPosY - v12->m_fPosY) )
          return;
        v14 = *(float *)&this->m_fontcolor.Color - *(float *)&v12->m_fontcolor.Color;
        v25 = *(float *)&this->m_wndcolor.Color - *(float *)&v12->m_wndcolor.Color;
        v15 = *(float *)&this->m_id - *(float *)&v12->m_id;
        pfVal.y = v25;
        m_fWaypointZ = v15;
        pfVal.x = v14;
        pfVal.z = m_fWaypointZ;
        v16 = (((gbVec3D *)&pfVal))->gbVec3D::Length();
        if ( v16 >= *(float *)&v12->m_rect.left + *(float *)&this->m_rect.left )
          return;
        (((RoleSystem *)v12))->RoleSystem::Notify();
        arg0b = v16;
        if ( arg0b < 12.0f )
        {
          v17 = 0;
          goto LABEL_37;
        }
        v18 = (((RoleSystem *)v12))->RoleSystem::InterpolateHeight((float *)&this->m_fontcolor.Color);
        p_Color = (float *)&v12->m_fontcolor.Color;
        v19 = v18;
        v20 = this->RoleSystem::InterpolateHeight(p_Color);
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
        byte_C11748 = 0;
        byte_C11750 = 0;
        dword_C1171C = 0x7FFFFFFF;
        g_nKeyMap3 = 1;
        PAL3::StartCombatFromNPC((const NPCInfo *)&this->m_nFacing, v17, (Role *)this);
        break;
      case 3:
        if ( g_nCameraUpdateCount <= 0 )
          return;
        m_fWaypointX = this->m_fWaypointX;
        m_fWaypointZ = this->m_fWaypointZ;
        this->m_nTransformMode = 2;
        this->m_nMoveRole = 0;
        v25 = 0.0f;
        this->RoleSystem::BindPartyToScene(&m_fWaypointX, 1);
        goto LABEL_19;
      default:
        goto LABEL_19;
    }
  }
}

// 0x00417850
int RoleSystem::EnterSubMode6()
{
  if ( g_RoleSlotBuf.m_partyActor.m_szTexture[8] )
  {
    this->m_nMoveSubMode = 6;
    this->m_nCoreState = 1;
    return this->RoleSystem::UpdateTransform();
  }
  else
  {
    this->RoleSystem::MoveRole((float *)&g_pRoleSystem->m_fontcolor.Color, g_pRoleSystem->m_partyActor.m_nState, 1, 1);
    return this->RoleSystem::UpdateTransform();
  }
}

// 0x004178A0
BOOL RoleSystem::CheckVisibility()
{
  float *v2; // ebx
  float v3; // st7
  float v4; // st6
  float v5; // st7
  RoleSystem *v7; // eax
  int RolePtr; // edi
  RoleSystem *v9; // eax
  int *v10; // [esp-0x1C] [ebp-0x44]
  char *v11; // [esp-0x18] [ebp-0x40]
  int v12; // [esp-0x14] [ebp-0x3C]
  char *v13; // [esp-0x10] [ebp-0x38]
  int m_nState; // [esp-0xC] [ebp-0x34]
  int v15; // [esp-0xC] [ebp-0x34]
  float pszBuf; // [esp+0x8] [ebp-0x20]
  float m_fWaypointZ; // [esp+0x18] [ebp-0x10]
  gbVec3D v18; // [esp+0x1C] [ebp-0xC] BYREF

  if ( g_RoleSlotBuf.m_partyActor.m_szTexture[7] )
    return 0;
  v2 = (float *)g_pRoleSystem;
  if ( !g_pRoleSystem )
    return 0;
  if ( g_pRoleSystem->m_partyActor.m_nState != this->m_partyActor.m_nState )
    return 0;
  memset(&v18, 0, sizeof(v18));
  LODWORD(v18.x) = g_pRoleSystem->m_fontcolor.Color;
  v3 = *(float *)&g_pRoleSystem->m_wndcolor.Color;
  v18.y = *(float *)&g_pRoleSystem->m_wndcolor.Color;
  v4 = *(float *)&g_pRoleSystem->m_id;
  m_fWaypointZ = this->m_fWaypointZ;
  v18.x = v18.x - this->m_fWaypointX;
  v18.y = v3;
  v18.z = v4 - m_fWaypointZ;
  if ( this->m_fMoveRadius * 0.80000001 < (((gbVec3D *)&v18))->gbVec3D::Length() )
    return 0;
  v18.x = v2[1];
  v18.y = v2[2];
  v5 = v2[3];
  v18.x = v18.x - *(float *)&this->m_fontcolor.Color;
  v18.y = v18.y - *(float *)&this->m_wndcolor.Color;
  v18.z = v5 - *(float *)&this->m_id;
  pszBuf = (((gbVec3D *)&v18))->gbVec3D::Length();
  if ( 12.0 * 10.0 > pszBuf )
    return 1;
  if ( pszBuf >= (double)this->m_fMoveSpeed )
    return 0;
  v18.x = v18.x / pszBuf;
  v18.y = v18.y / pszBuf;
  v18.z = v18.z / pszBuf;
  if ( v18.y * *(float *)&this->m_rect.right
     + v18.z * *(float *)&this->m_rect.bottom
     + v18.x * *(float *)&this->m_rect.top <= 0.69999999 )
    return 0;
  m_nState = this->m_partyActor.m_nState;
  v7 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v7))->RoleSystem::GetRolePtr(m_nState);
  v15 = (__int64)((v2[3] - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  v13 = (char *)(__int64)((v2[1] - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v12 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  v11 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v10 = (int *)this->m_partyActor.m_nState;
  v9 = (RoleSystem *)UISceneUpdate();
  return (((RoleSystem *)v9))->RoleSystem::AdvanceOnPath(v10, v11, v12, v13, v15) != 0;
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
  int m_nState; // [esp-0x4] [ebp-0x1C]
  int v11; // [esp+0x10] [ebp-0x8]
  int v12; // [esp+0x14] [ebp-0x4]
  int statea; // [esp+0x1C] [ebp+0x4]

  if ( *(_BYTE *)(state + 244) == 14 )
  {
    m_nState = this->m_partyActor.m_nState;
    v4 = (RoleSystem *)UISceneUpdate();
    (((RoleSystem *)v4))->RoleSystem::GetRolePtr(m_nState);
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
        v9 = (int *)this->m_partyActor.m_nState;
        v8 = (RoleSystem *)UISceneUpdate();
        if ( (((RoleSystem *)v8))->RoleSystem::CheckCollision(v9, v7) )
          break;
        if ( --statea < 0 )
        {
          v5 = v12;
          goto LABEL_7;
        }
      }
      this->RoleSystem::MoveToTileCheck(v7, v6, 1);
    }
  }
  else if ( this->m_nMoveMode != 4 )
  {
    (((ScriptVM *)state))->ScriptVM::ExecuteBlock();
  }
}

// 0x00417BC0
void RoleSystem::StopAndResetPath()
{
  int m_nMoveMode; // eax

  if ( this->m_bPathActive )
  {
    m_nMoveMode = this->m_nMoveMode;
    this->m_fPathSpeed = 0.0f;
    if ( m_nMoveMode != 4 )
      this->m_nPrevMoveMode = m_nMoveMode;
    this->m_nMoveMode = 4;
    *(&this->m_partyActor.m_nUpdateMode + 5) = 21;
    SetActionByName((Actor *)&this->m_partyActor.m_Actor, 0, pszOpt1, 0);
    (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(1.0);
    this->m_bPathActive = 0;
  }
  else
  {
    this->m_nMoveMode = this->m_nPrevMoveMode;
    this->RoleSystem::NotifyMoveComplete();
    this->m_bPathActive = 0;
  }
}

// 0x00417C50
double RoleSystem::UpdateMoveSubMode(double result, float result_4)
{
  float v4; // st7
  bool v5; // zf
  signed int v6; // eax
  char *m_pData; // ecx
  bool v8; // zf
  signed int v9; // eax
  float m_fWaypointX; // st7
  float v11; // ecx
  float v12; // eax
  int m_nMoveSubMode; // eax
  float v14; // st7
  double m_nTransformState; // st7
  double v16; // [esp-0x4] [ebp-0x34]
  int v17; // [esp+0x0] [ebp-0x30]
  int v18; // [esp+0x0] [ebp-0x30]
  float v19; // [esp+0x4] [ebp-0x2C]
  float v20; // [esp+0x4] [ebp-0x2C]
  float v21; // [esp+0x4] [ebp-0x2C]
  char v22; // [esp+0x8] [ebp-0x28]
  gbVec3D v23; // [esp+0xC] [ebp-0x24] BYREF
  float pTargetPos[4]; // [esp+0x18] [ebp-0x18] BYREF
  float m_fWaypointZ; // [esp+0x28] [ebp-0x8]

  if ( this->m_nActiveRole == 4 )
  {
LABEL_39:
    m_nMoveSubMode = this->m_nMoveSubMode;
    if ( m_nMoveSubMode && m_nMoveSubMode != 3 )
    {
      this->RoleSystem::PathFollowUpdate();
      if ( this->m_nMoveSubMode == 1 )
        this->RoleSystem::UpdateFollowVelocity();
      if ( this->m_nMoveSubMode != 8 )
      {
        v23 = *(gbVec3D *)&this->m_FrameA.m_fontcolor.Color;
        v23.x = v23.x * *(float *)&result;
        v23.y = v23.y * *(float *)&result;
        v14 = *(float *)&result * v23.z;
        this->m_fRotAxisX = v23.x + this->m_fRotAxisX;
        this->m_fRotAxisY = v23.y + this->m_fRotAxisY;
        this->m_fRotAxisZ = v14 + this->m_fRotAxisZ;
        this->m_fRotAxisY = 0.0f;
        (((gbVec3D *)&this->m_fRotAxisX))->gbVec3D::Normalize();
        m_nTransformState = this->m_nTransformState;
        this->m_fRotAxisX = m_nTransformState * this->m_fRotAxisX;
        this->m_fRotAxisY = m_nTransformState * this->m_fRotAxisY;
        v4 = m_nTransformState * this->m_fRotAxisZ;
        this->m_fRotAxisZ = v4;
      }
    }
    return v4;
  }
  if ( this->m_nActionState != 3 || *(_DWORD *)&this->m_nInitMoveMode )
  {
    if ( *(_DWORD *)&this->m_nInitMoveMode == 1 )
    {
      v4 = *(float *)&result + *(float *)&this->m_nMoveReset;
      *(float *)&this->m_nMoveReset = v4;
      if ( v4 > 8.0f )
      {
        if ( this->m_nMoveSubMode )
        {
          this->RoleSystem::NotifyMoveComplete();
        }
        else
        {
          v9 = rand() & 0x80000001;
          v8 = v9 == 0;
          if ( v9 < 0 )
            v8 = (((_BYTE)v9 - 1) | 0xFFFFFFFE) == -1;
          if ( v8 )
          {
            m_fWaypointX = this->m_fWaypointX;
            v11 = *(float *)&this->m_fontcolor.Color;
            m_fWaypointZ = this->m_fWaypointZ;
            v23.x = v11;
            v12 = *(float *)&this->m_id;
            LODWORD(v23.y) = this->m_wndcolor.Color;
            v23.z = v12;
            v23.x = v11 - m_fWaypointX;
            v23.y = v23.y - m_fWaypointZ;
            v4 = (((gbVec3D *)&v23))->gbVec3D::Length();
            if ( v4 >= 100.0f )
            {
              pTargetPos[0] = this->m_fWaypointX;
              v4 = this->m_fWaypointZ;
              pTargetPos[1] = this->m_fWaypointZ;
              pTargetPos[2] = 0.0;
              this->RoleSystem::SetMoveTarget(pTargetPos, 1);
            }
            else
            {
              this->RoleSystem::StartHalfSpeedMovement();
            }
          }
        }
        this->m_nMoveReset = 0;
      }
    }
    else if ( *(_DWORD *)&this->m_nInitMoveMode == 2 )
    {
      switch ( *(&this->m_partyActor.m_nUpdateMode + 6) )
      {
        case 0:
          v4 = *(float *)&result + *(float *)&this->m_nMoveReset;
          *(float *)&this->m_nMoveReset = v4;
          if ( v4 > 4.0f )
          {
            this->m_nCoreState = 1;
            this->RoleSystem::UpdateTransform();
            *(&this->m_partyActor.m_nUpdateMode + 6) = 1;
            *(&this->m_partyActor.m_nUpdateMode + 8) = 0;
          }
          break;
        case 1:
          LODWORD(v16) = 1065353216;
          if ( this->RoleSystem::StepAlongPath(v16, v19) )
          {
            this->m_nCoreState = 0;
            this->RoleSystem::UpdateTransform();
            this->m_nMoveReset = 0;
            *(&this->m_partyActor.m_nUpdateMode + 6) = 2;
          }
          else
          {
            this->m_fRotAxisX = this->m_nMovement;
            this->m_fRotAxisY = this->m_fSavedRotX;
            LODWORD(this->m_fRotAxisZ) = (unsigned long)((UIWnd *)&this->m_FrameA);
            this->RoleSystem::ApplyMoveStep(_pal3_coerce_f64((unsigned __int64)LODWORD(result)), v17, v20, v22);
          }
          break;
        case 2:
          v4 = *(float *)&result + *(float *)&this->m_nMoveReset;
          *(float *)&this->m_nMoveReset = v4;
          if ( v4 > 4.0f )
          {
            this->m_nCoreState = 1;
            this->RoleSystem::UpdateTransform();
            m_pData = this->m_partyUI3.m_childs.m_pData;
            *(&this->m_partyActor.m_nUpdateMode + 6) = 3;
            *(&this->m_partyActor.m_nUpdateMode + 8) = (int)m_pData;
          }
          break;
        case 3:
          LODWORD(v16) = -1082130432;
          if ( this->RoleSystem::StepAlongPath(v16, v19) )
          {
            this->m_nCoreState = 0;
            this->RoleSystem::UpdateTransform();
            this->m_nMoveReset = 0;
            *(&this->m_partyActor.m_nUpdateMode + 6) = 0;
          }
          else
          {
            this->m_fRotAxisX = this->m_nMovement;
            this->m_fRotAxisY = this->m_fSavedRotX;
            LODWORD(this->m_fRotAxisZ) = (unsigned long)((UIWnd *)&this->m_FrameA);
            this->RoleSystem::ApplyMoveStep(_pal3_coerce_f64((unsigned __int64)LODWORD(result)), v18, v21, v22);
          }
          break;
        default:
          return v4;
      }
      return v4;
    }
    goto LABEL_39;
  }
  if ( this->m_nCoreState == 51 )
  {
    if ( (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::GetVisNode() )
    {
      this->m_nCoreState = 0;
      this->RoleSystem::UpdateTransform();
    }
  }
  else
  {
    v4 = *(float *)&result + *(float *)&this->m_nMoveReset;
    *(float *)&this->m_nMoveReset = v4;
    if ( v4 <= 3.0f )
      return v4;
    v6 = rand() & 0x80000001;
    v5 = v6 == 0;
    if ( v6 < 0 )
      v5 = (((_BYTE)v6 - 1) | 0xFFFFFFFE) == -1;
    if ( v5 )
    {
      this->m_nCoreState = 51;
      if ( strlen((const char *)&this->m_szModelPath) )
      {
        SetMaterialName((Actor *)&this->m_partyActor.m_Actor, &this->m_szModelPath, 2);
        this->m_nMoveReset = 0;
        return v4;
      }
      (((Actor *)&this->m_partyActor.m_Actor))->Actor::CompareActionName(51, 2);
    }
    this->m_nMoveReset = 0;
  }
  return v4;
}

// 0x004180B0
int RoleSystem::CheckWidgetReady(gbRay *pRay)
{
  struct gbOBBox actionId; // [esp+0x4] [ebp-0x4C] BYREF

  if ( !this->m_partyActor.m_pRoleObj )
    return 0;
  (((Actor *)&this->m_partyActor.m_Actor))->Actor::PlayAction((int)&actionId);
  actionId.trans.tx = actionId.trans.tx + this->m_fPosX;
  actionId.trans.ty = actionId.trans.ty + this->m_fPosY;
  actionId.trans.tz = actionId.trans.tz + this->m_fPosZ;
  return (((gbRay *)pRay))->gbRay::IsColOBB_H(actionId);
}

// 0x00418130
int RoleSystem::GetMoveState(int nVal1)
{
  int result; // eax

  if ( nVal1 )
  {
    result = this->m_nMoveMode;
    if ( result != 4 )
      this->m_nPrevMoveMode = result;
    this->m_nMoveMode = 4;
    *(&this->m_partyActor.m_nUpdateMode + 5) = 6;
  }
  else
  {
    result = this->m_nPrevMoveMode;
    this->m_nMoveMode = result;
  }
  return result;
}

// 0x004181E0
int RoleSystem::Notify()
{
  int result; // eax

  this->RoleSystem::NotifyMoveComplete();
  this->m_nCoreState = 0;
  this->RoleSystem::UpdateTransform();
  *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 2) = this->m_fontcolor.Color;
  *((_DWORD *)&this[1].m_partyActor.m_fSpeed + 3) = this->m_wndcolor.Color;
  LODWORD(this[1].m_partyActor.m_fAngleDeg) = this->m_id;
  result = this->m_nMoveMode;
  if ( result == 4 )
  {
    result = this->m_nPrevMoveMode;
    this->m_nMoveMode = result;
    if ( result == 4 )
      this->m_nMoveMode = 1;
  }
  if ( this->m_nActionState == 3 )
    this->m_nActionState = 0;
  this->m_nMoveRole = 0;
  return result;
}

// 0x00418970
void RoleSystem::AddVec3ToTarget(int nVal, int nVal2)
{
  float v3; // st7
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
  float v15; // st6
  long double v16; // st7
  Object3D *m_pLinkedRole; // eax
  float m_rotx; // edx
  float v19; // st6
  RoleSystem *v20; // eax
  int v21; // edi
  RoleSystem *v22; // eax
  float v23; // eax
  float v24; // ecx
  float m_dropx; // st6
  RoleSystem *v26; // eax
  int v27; // edi
  RoleSystem *v28; // eax
  char *v29; // eax
  int result; // eax
  float v31; // edx
  float v32; // eax
  int *v33; // [esp-0x14] [ebp-0x54]
  int *v34; // [esp-0x14] [ebp-0x54]
  char *v35; // [esp-0x10] [ebp-0x50]
  char *v36; // [esp-0x10] [ebp-0x50]
  int v37; // [esp-0xC] [ebp-0x4C]
  int v38; // [esp-0xC] [ebp-0x4C]
  int v39; // [esp-0x4] [ebp-0x44]
  int m_nState; // [esp-0x4] [ebp-0x44]
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

  this->m_pLinkedRole = ((Object3D *)((Object3D *)nVal3));
  if ( *(_DWORD *)(nVal3 + 264) )
  {
    v8 = (RoleSystem *)UISceneUpdate();
    RolePtr = (((RoleSystem *)v8))->RoleSystem::GetRolePtr(0);
    v39 = 1;
  }
  else
  {
    m_nState = this->m_partyActor.m_nState;
    v10 = (RoleSystem *)UISceneUpdate();
    RolePtr = (((RoleSystem *)v10))->RoleSystem::GetRolePtr(m_nState);
    v39 = this->m_partyActor.m_nState;
  }
  v11 = (RoleSystem *)UISceneUpdate();
  v12 = (((RoleSystem *)v11))->RoleSystem::GetRolePtr(v39);
  v53 = 0.0f;
  v52 = ((float)(int)pszBuf + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 128);
  v54 = ((float)nVal + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(RolePtr + 136);
  if ( (int)pszBuf >= 0 )
  {
    v13 = *(_DWORD *)(RolePtr + 152);
    if ( (int)pszBuf < v13 && nVal >= 0 && nVal < *(_DWORD *)(RolePtr + 156) )
      v53 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (_DWORD)&pszBuf[nVal * v13]);
  }
  pTargetPos = v52;
  v44 = v53;
  v45 = v54;
  v50 = 0.0f;
  v49 = ((float)(int)pszBuf2 + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(v12 + 128);
  v51 = ((float)nVal2 + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(v12 + 136);
  if ( (((RoleSystem *)v12))->RoleSystem::IsInBounds((int)pszBuf2, nVal2) )
    v50 = *(float *)(*(_DWORD *)(v12 + 160) + 8 * (_DWORD)&pszBuf2[nVal2 * *(_DWORD *)(v12 + 152)]);
  v14 = fVal * 0.017453292;
  v47 = v50;
  v46 = v49;
  v48 = v51;
  v53 = 0.0f;
  v52 = sin(v14);
  v15 = -(12.0f + 12.0f);
  v52 = v15 * v52;
  v16 = cos(v14) * v15;
  m_pLinkedRole = (Object3D *)this->m_pLinkedRole;
  m_rotx = m_pLinkedRole[1].m_rotx;
  if ( fabs(v50 - this->m_fPosY) <= fabs(v44 - this->m_fPosY) )
  {
    v46 = m_pLinkedRole[1].m_rotx;
    m_dropx = m_pLinkedRole[1].m_dropx;
    v42 = this->m_partyActor.m_nState;
    v46 = m_rotx + v52;
    v47 = v47 + v53;
    v48 = m_dropx + v16;
    v26 = (RoleSystem *)UISceneUpdate();
    v27 = (((RoleSystem *)v26))->RoleSystem::GetRolePtr(v42);
    v38 = (__int64)((*(float *)&this->m_id - *(float *)(v27 + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
    v36 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(v27 + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
    v34 = (int *)this->m_partyActor.m_nState;
    v28 = (RoleSystem *)UISceneUpdate();
    if ( (((RoleSystem *)v28))->RoleSystem::AdvanceOnPath(v34, v36, v38, pszBuf2, nVal2) )
    {
      this->RoleSystem::SetMoveTarget(&v46, 1);
      v31 = v44;
      v32 = v45;
      *((float *)&this->m_partyActor.m_nUpdateMode + 8) = pTargetPos;
      this->m_fPathTargetY = v31;
      this->m_fPathTargetZ = v32;
      goto LABEL_17;
    }
LABEL_15:
    v29 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("outdist");
    return (((PalScriptMgr *)&stru_DBA134))->PalScriptMgr::ShowTextBox(v29);
  }
  pTargetPos = m_pLinkedRole[1].m_rotx;
  v19 = m_pLinkedRole[1].m_dropx;
  v41 = this->m_partyActor.m_nState;
  pTargetPos = m_rotx + v52;
  v44 = v44 + v53;
  v45 = v19 + v16;
  v20 = (RoleSystem *)UISceneUpdate();
  v21 = (((RoleSystem *)v20))->RoleSystem::GetRolePtr(v41);
  v37 = (__int64)((*(float *)&this->m_id - *(float *)(v21 + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  v35 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(v21 + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v33 = (int *)this->m_partyActor.m_nState;
  v22 = (RoleSystem *)UISceneUpdate();
  if ( !(((RoleSystem *)v22))->RoleSystem::AdvanceOnPath(v33, v35, v37, pszBuf, nVal) )
    goto LABEL_15;
  this->RoleSystem::SetMoveTarget(&pTargetPos, 1);
  v23 = v47;
  v24 = v48;
  *((float *)&this->m_partyActor.m_nUpdateMode + 8) = v46;
  this->m_fPathTargetY = v23;
  this->m_fPathTargetZ = v24;
LABEL_17:
  if ( this->m_fPathTargetY <= (double)this->m_fPosY )
    *(&this->m_partyActor.m_nUpdateMode + 7) = 2;
  else
    *(&this->m_partyActor.m_nUpdateMode + 7) = 1;
  result = this->m_nMoveMode;
  this->m_fPathAngle = fVal;
  *(&this->m_partyActor.m_nUpdateMode + 5) = 7;
  *(&this->m_partyActor.m_nUpdateMode + 6) = 0;
  if ( result != 4 )
    this->m_nPrevMoveMode = result;
  this->m_nMoveMode = 4;
  return result;
}

// 0x00418D90
BOOL RoleSystem::IsInBounds(int nVal, int nVal2)
{
  return nVal >= 0 && nVal < this->m_nDispWndColor && nVal2 >= 0 && nVal2 < this->m_nTodo_9C;
}

// 0x00418DC0
char RoleSystem::TryMoveToTarget(__int16 pData, int nVal)
{
  PalScript *v4; // eax
  Object3D *v5; // eax
  float v7; // st7
  float m_dropx; // edx
  long double v9; // st7
  float v10; // st7
  float v11; // st7
  float v12; // st7
  RoleSystem *v13; // eax
  int RolePtr; // edi
  RoleSystem *v15; // eax
  char *v16; // eax
  int m_nMoveMode; // eax
  int *v18; // [esp-0x20] [ebp-A0h]
  char *v19; // [esp-0x1C] [ebp-0x9C]
  int v20; // [esp-0x18] [ebp-0x98]
  char *v21; // [esp-0x14] [ebp-0x94]
  int m_nState; // [esp-0x10] [ebp-0x90]
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
  (((PalScript *)v4))->PalScript::SetAction(pData);
  this->m_pLinkedRole = ((Object3D *)(v5));
  if ( !v5 )
    return 0;
  v7 = v5[1].m_dropy + 180.0f;
  pTargetPos = 0.0f;
  v27 = 0.0f;
  v28 = 0.0f;
  pTargetPos = v5[1].m_rotx;
  m_dropx = v5[1].m_dropx;
  v25 = v7;
  v9 = v7 * 0.017453292;
  v30 = sin(v9);
  v31 = cos(v9);
  v10 = -(12.0f + 12.0f);
  pszBuf = v10;
  v31 = pszBuf * v31;
  pTargetPos = pTargetPos + v10 * v30;
  v27 = 0.0f;
  v28 = m_dropx + v31;
  (((Object3D *)this->m_pLinkedRole))->Object3D::SetTransform(&pMatrix);
  v11 = v33 * 0.6000000238418579f;
  if ( v11 > 100.0f )
    v11 = 100.0f;
  this->m_fPathTargetY = v11;
  v12 = pTargetPos - *(float *)&this->m_fontcolor.Color;
  v29.y = v27;
  v29.z = v28;
  v29.x = v12;
  v29.y = -*(float *)&this->m_wndcolor.Color;
  v29.z = v28 - *(float *)&this->m_id;
  if ( 12.0 * 5.0 >= (((gbVec3D *)&v29))->gbVec3D::Length() )
    goto LABEL_8;
  m_nState = this->m_partyActor.m_nState;
  v13 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v13))->RoleSystem::GetRolePtr(m_nState);
  v23 = (__int64)((v28 - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  v21 = (char *)(__int64)((pTargetPos - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v20 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  v19 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v18 = (int *)this->m_partyActor.m_nState;
  v15 = (RoleSystem *)UISceneUpdate();
  if ( (((RoleSystem *)v15))->RoleSystem::AdvanceOnPath(v18, v19, v20, v21, v23) )
  {
LABEL_8:
    this->RoleSystem::SetMoveTarget(&pTargetPos, 1);
    *(&this->m_partyActor.m_nUpdateMode + 7) = nVal;
    m_nMoveMode = this->m_nMoveMode;
    this->m_fPathAngle = v25;
    *(&this->m_partyActor.m_nUpdateMode + 5) = 8;
    *(&this->m_partyActor.m_nUpdateMode + 6) = 0;
    if ( m_nMoveMode != 4 )
      this->m_nPrevMoveMode = m_nMoveMode;
    this->m_nMoveMode = 4;
    return 1;
  }
  else
  {
    v16 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("outdist");
    (((PalScriptMgr *)&stru_DBA134))->PalScriptMgr::ShowTextBox(v16);
    return 0;
  }
}

// 0x00419030
int RoleSystem::ResetPathParams(int nVal)
{
  int m_nMoveMode; // eax
  int result; // eax
  float v4; // edx

  m_nMoveMode = this->m_nMoveMode;
  this->m_fPathAngle = 2.0f;
  this->m_fPathSpeed = 0.0f;
  *(&this->m_partyActor.m_nUpdateMode + 5) = 9;
  if ( m_nMoveMode != 4 )
    this->m_nPrevMoveMode = m_nMoveMode;
  result = nVal;
  v4 = *(float *)&this->m_partyActor.m_fScale;
  this->m_nMoveMode = 4;
  *(&this->m_partyActor.m_nUpdateMode + 8) = nVal;
  this->m_fPathTargetY = v4;
  return result;
}

// 0x00419790
int RoleSystem::ProcessMoveCommand(int *p_DWORD)
{
  float v3; // st7
  float v4; // st7
  float v5; // st7
  float v6; // st7
  float v7; // st6
  float z; // edx
  float v10; // [esp+0x8] [ebp-0x18]
  float v11; // [esp+0xC] [ebp-0x14]
  float v12; // [esp+0x10] [ebp-0x10]
  gbVec3D v13; // [esp+0x14] [ebp-0xC] BYREF

  this->m_FrameA.m_rect.bottom = *p_DWORD;
  this->m_FrameA.m_pfather = ((UIWnd *)((UIWnd *)p_DWORD[1]));
  this->m_FrameA.m_childs.m_pData = ((char *)((char *)p_DWORD[2]));
  this->m_FrameA.m_childs.m_needscriptdel = LODWORD(this->m_fPosX);
  this->m_FrameA.m_bcreateok = LODWORD(this->m_fPosY);
  this->m_FrameA.m_bvisible = LODWORD(this->m_fPosZ);
  this->m_nMoveSubMode = 11;
  v10 = *(float *)&this->m_FrameA.m_rect.bottom - *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
  v3 = *(float *)&this->m_FrameA.m_pfather - *(float *)&this->m_FrameA.m_bcreateok;
  v13.x = v10;
  v11 = v3;
  v4 = *(float *)&this->m_FrameA.m_childs.m_pData - *(float *)&this->m_FrameA.m_bvisible;
  v13.y = v11;
  v12 = v4;
  v13.z = v12;
  v5 = (((gbVec3D *)&v13))->gbVec3D::Length();
  this->m_fPathSpeed = 0.0f;
  this->m_fPathAngle = v5 * 0.0069444444961845875f;
  v6 = *(float *)&this->m_FrameA.m_rect.bottom - *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
  v13.y = *(float *)&this->m_FrameA.m_pfather - *(float *)&this->m_FrameA.m_bcreateok;
  v7 = *(float *)&this->m_FrameA.m_childs.m_pData - *(float *)&this->m_FrameA.m_bvisible;
  this->m_fRotAxisY = v13.y;
  v13.z = v7;
  z = v13.z;
  this->m_fRotAxisX = v6;
  this->m_fRotAxisZ = z;
  this->RoleSystem::UpdatePosition();
  this->m_fRotAxisX = 0.0f;
  this->m_fRotAxisY = 0.0f;
  this->m_fRotAxisZ = 0.0f;
  return (((Actor *)&this->m_partyActor.m_Actor))->Actor::CompareActionName(2, 0);
}

// 0x004198C0
void RoleSystem::StartLinearMove(int *pTargetPos, int nMode)
{
  int m_nMoveMode; // eax
  float v5; // st7
  float v6; // st7
  float v7; // st7
  float v8; // st7
  float v9; // st6
  float z; // eax
  float v11; // [esp+0x8] [ebp-0x18]
  float v12; // [esp+0xC] [ebp-0x14]
  float v13; // [esp+0x10] [ebp-0x10]
  gbVec3D v14; // [esp+0x14] [ebp-0xC] BYREF

  m_nMoveMode = this->m_nMoveMode;
  if ( m_nMoveMode != 4 )
    this->m_nPrevMoveMode = m_nMoveMode;
  this->m_nMoveMode = 4;
  *(&this->m_partyActor.m_nUpdateMode + 5) = 10;
  *(&this->m_partyActor.m_nUpdateMode + 6) = 0;
  *(&this->m_partyActor.m_nUpdateMode + 7) = 0;
  this->m_FrameA.m_childs.m_needscriptdel = LODWORD(this->m_fPosX);
  this->m_FrameA.m_bcreateok = LODWORD(this->m_fPosY);
  this->m_FrameA.m_bvisible = LODWORD(this->m_fPosZ);
  this->m_FrameA.m_rect.bottom = *pTargetPos;
  this->m_FrameA.m_pfather = ((UIWnd *)((UIWnd *)pTargetPos[1]));
  this->m_FrameA.m_childs.m_pData = ((char *)((char *)pTargetPos[2]));
  this->m_nCoreState = nMode;
  this->RoleSystem::UpdateTransform();
  v11 = *(float *)&this->m_FrameA.m_rect.bottom - *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
  v5 = *(float *)&this->m_FrameA.m_pfather - *(float *)&this->m_FrameA.m_bcreateok;
  v14.x = v11;
  v12 = v5;
  v6 = *(float *)&this->m_FrameA.m_childs.m_pData - *(float *)&this->m_FrameA.m_bvisible;
  v14.y = v12;
  v13 = v6;
  v14.z = v13;
  v7 = (((gbVec3D *)&v14))->gbVec3D::Length() / this->m_nTransformState;
  this->m_fPathSpeed = 0.0f;
  this->m_fPathAngle = v7;
  v8 = *(float *)&this->m_FrameA.m_rect.bottom - *(float *)&this->m_FrameA.m_childs.m_needscriptdel;
  v14.y = *(float *)&this->m_FrameA.m_pfather - *(float *)&this->m_FrameA.m_bcreateok;
  v9 = *(float *)&this->m_FrameA.m_childs.m_pData - *(float *)&this->m_FrameA.m_bvisible;
  this->m_fRotAxisY = v14.y;
  v14.z = v9;
  z = v14.z;
  this->m_fRotAxisX = v8;
  this->m_fRotAxisZ = z;
  this->RoleSystem::UpdatePosition();
  this->m_fRotAxisX = 0.0f;
  this->m_fRotAxisY = 0.0f;
  this->m_fRotAxisZ = 0.0f;
}

// 0x00419A20
void RoleSystem::GetActorState(double thisa, int nVal, int nVal2, int nVal3)
{
  RoleSystem *v6; // eax
  int m_nState; // [esp-0x10] [ebp-0x20]
  int pfVal; // [esp+0x4] [ebp-0xC] BYREF
  float v9; // [esp+0x8] [ebp-0x8]
  int v10; // [esp+0xC] [ebp-0x4]

  pfVal = LODWORD(thisa);
  m_nState = this->m_partyActor.m_nState;
  v9 = 0.0f;
  v10 = HIDWORD(thisa);
  v6 = (RoleSystem *)UISceneUpdate();
  (((RoleSystem *)v6))->RoleSystem::SetRoleParam(m_nState, (float *)&pfVal, 0, 0);
  // __asm { fstp    [esp+0x10+var_8] }
  this->RoleSystem::StartLinearMove(&pfVal, nVal);
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
  result = (((Actor *)&this->m_partyActor.m_Actor))->Actor::PlayAction((int)&actionId);
  pOut[1] = v5 + pOut[1];
  return result;
}

// 0x00419AE0
int RoleSystem::NotifyAndSetMode6()
{
  int result; // eax

  result = this->RoleSystem::Notify();
  this->m_nMoveMode = 6;
  return result;
}

// 0x00419B10
__int64 RoleSystem::SetCollisionRadius()
{
  __int64 result; // rax

  result = (__int64)(12.0 * 12.0);
  dword_C10D40 = result;
  return result;
}

// 0x00419B30
void RoleSystem::UpdateFollowBehavior(float fDelta)
{
  float v3; // st7
  int m_nCoreState; // eax
  _BYTE v5[12]; // [esp+0x4] [ebp-0x18]
  gbVec3D v6; // [esp+0x10] [ebp-0xC] BYREF

  if ( g_pRoleSystem )
  {
    *(float *)v5 = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
    *(float *)&v5[4] = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
    v6 = *(gbVec3D *)v5;
    v3 = (((gbVec3D *)&v6))->gbVec3D::Length();
    m_nCoreState = this->m_nCoreState;
    if ( m_nCoreState )
    {
      if ( m_nCoreState == 2 )
      {
        if ( v3 <= (double)dword_C10D40 * 1.4 )
        {
          this->RoleSystem::ScanMoveDirections(fDelta);
        }
        else
        {
          this->m_nCoreState = 0;
          this->RoleSystem::UpdateTransform();
          this->m_nMoveSubMode = 0;
        }
      }
    }
    else if ( v3 < (double)dword_C10D40 )
    {
      this->m_nCoreState = 2;
      this->RoleSystem::UpdateTransform();
      this->m_nMoveSubMode = 6;
    }
  }
}

// 0x00419EF0
BOOL RoleSystem::AdvancePathStep(float *pfVal)
{
  float v4; // st7
  float v5; // st6
  float v7; // eax
  RoleSystem *v8; // eax
  int RolePtr; // edi
  RoleSystem *v10; // eax
  int *v11; // [esp-0x1C] [ebp-0x3C]
  char *v12; // [esp-0x18] [ebp-0x38]
  int v13; // [esp-0x14] [ebp-0x34]
  char *v14; // [esp-0x10] [ebp-0x30]
  int m_nState; // [esp-0xC] [ebp-0x2C]
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
  pfVala = (((gbVec3D *)&v19))->gbVec3D::Length();
  if ( 0.87 * 500.0 < pfVala )
    return 0;
  if ( 12.0 + 12.0 > pfVala )
    return 1;
  if ( v19.z / pfVala * *(float *)&this->m_rect.bottom
     + v19.y / pfVala * *(float *)&this->m_rect.right
     + v19.x / pfVala * *(float *)&this->m_rect.top <= 0.87 )
    return 0;
  v7 = pfVal[2];
  m_nState = this->m_partyActor.m_nState;
  v19.x = *pfVal;
  v19.z = v7;
  v19.y = 0.0f;
  v8 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v8))->RoleSystem::GetRolePtr(m_nState);
  v16 = (__int64)((v19.z - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  v14 = (char *)(__int64)((v19.x - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v13 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  v12 = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v11 = (int *)this->m_partyActor.m_nState;
  v10 = (RoleSystem *)UISceneUpdate();
  return (((RoleSystem *)v10))->RoleSystem::AdvanceOnPath(v11, v12, v13, v14, v16) != 0;
}

// 0x0041A150
void RoleSystem::SetActorTexture(const char *pszName)
{
  char Buffer[260]; // [esp+0x4] [ebp-0x104] BYREF

  sprintf(Buffer, "role\\%s\\%s.tga", &this->m_nAnimState, pszName);
  todo_00537120((Actor *)&this->m_partyActor.m_Actor, (int)Buffer);
}

// 0x0041A1A0
void RoleSystem::ScanMoveDirections(float fRadius)
{
  RoleSystem *v3; // ebp
  int RolePtr; // edi
  long double v5; // st7
  float v6; // st6
  gbVec3D *v7; // eax
  float v8; // st7
  UIWnd *v9; // edx
  char *v10; // eax
  float v11; // st7
  float v12; // st7
  float v13; // st7
  float v14; // st7
  float v15; // st7
  float v16; // [esp+0x0] [ebp-0x6C]
  float v17; // [esp+0x4] [ebp-0x68]
  float v18; // [esp+0x8] [ebp-0x64]
  int i; // [esp+0x1C] [ebp-0x50]
  float v20; // [esp+0x20] [ebp-0x4C]
  float *v21; // [esp+0x24] [ebp-0x48]
  char *nFlag; // [esp+0x28] [ebp-0x44]
  int nVal; // [esp+0x2C] [ebp-0x40]
  LONG pfVal2; // [esp+0x30] [ebp-0x3C] BYREF
  float v25; // [esp+0x34] [ebp-0x38]
  float v26; // [esp+0x38] [ebp-0x34]
  LONG v27; // [esp+0x3C] [ebp-0x30]
  float v28; // [esp+0x40] [ebp-0x2C]
  float v29; // [esp+0x44] [ebp-0x28]
  float pfVal; // [esp+0x48] [ebp-0x24] BYREF
  float v31; // [esp+0x4C] [ebp-0x20]
  float v32; // [esp+0x50] [ebp-0x1C]
  gbVec3D v33; // [esp+0x54] [ebp-0x18] BYREF
  gbVec3D v34; // [esp+0x60] [ebp-0xC] BYREF
  float fRadiusa; // [esp+0x70] [ebp+0x4]

  v21 = (float *)g_pRoleSystem;
  v3 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v3))->RoleSystem::GetRolePtr(this->m_partyActor.m_nState);
  nFlag = (char *)(__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  nVal = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  v31 = 0.0f;
  *(float *)&pfVal2 = 0.0;
  v25 = 0.0f;
  v26 = 0.0f;
  v20 = -1.0f;
  v27 = 0;
  v28 = 0.0f;
  v29 = 0.0f;
  for ( i = 0; i < 360; i += 30 )
  {
    v5 = (double)i * 0.017453292;
    pfVal = cos(v5);
    v6 = (float)dword_C10D40;
    pfVal = v6 * pfVal;
    v31 = v31 * v6;
    v32 = v6 * sin(v5);
    this->RoleSystem::UpdateMoveInterpolation(&pfVal, (float *)&pfVal2);
    *(float *)&pfVal2 = *(float *)&pfVal2 + *(float *)&this->m_fontcolor.Color;
    v25 = v25 + *(float *)&this->m_wndcolor.Color;
    v26 = v26 + *(float *)&this->m_id;
    if ( (((RoleSystem *)v3))->RoleSystem::AdvanceOnPath((int *)this->m_partyActor.m_nState, nFlag, nVal, (char *)(__int64)((*(float *)&pfVal2 - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize), (__int64)((v26 - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize)) )
    {
      v18 = v26 - v21[3];
      v17 = v25 - v21[2];
      v16 = *(float *)&pfVal2 - v21[1];
      v33 = *v7;
      v8 = (((gbVec3D *)&v33))->gbVec3D::Length();
      if ( v8 > v20 )
      {
        v27 = pfVal2;
        v20 = v8;
        v28 = v25;
        v29 = v26;
      }
    }
  }
  v9 = (UIWnd *)LODWORD(v28);
  v10 = (char *)LODWORD(v29);
  this->m_FrameA.m_rect.bottom = v27;
  this->m_FrameA.m_pfather = ((UIWnd *)(v9));
  this->m_FrameA.m_childs.m_pData = ((char *)(v10));
  this->RoleSystem::InterpolateMoveFrame(1.0);
  v11 = fRadius * 4.0f;
  v33.x = v11 * *(float *)&this->m_FrameA.m_fontcolor.Color;
  v33.y = v11 * *(float *)&this->m_FrameA.m_wndcolor.Color;
  v12 = v11 * *(float *)&this->m_FrameA.m_id;
  this->m_fRotAxisX = v33.x + this->m_fRotAxisX;
  this->m_fRotAxisY = v33.y + this->m_fRotAxisY;
  this->m_fRotAxisZ = v12 + this->m_fRotAxisZ;
  v13 = this->m_nTransformState * 1.399999976158142f;
  this->m_fRotAxisY = 0.0f;
  fRadiusa = v13;
  v14 = (((gbVec3D *)&this->m_fRotAxisX))->gbVec3D::Length();
  if ( v14 > fRadiusa )
  {
    v15 = fRadiusa / v14;
    this->m_fRotAxisX = v15 * this->m_fRotAxisX;
    this->m_fRotAxisY = v15 * this->m_fRotAxisY;
    this->m_fRotAxisZ = v15 * this->m_fRotAxisZ;
  }
}

// 0x0041A450
void RoleSystem::UpdateFollowerMovement(float fVal)
{
  int v3; // eax
  float v4; // ecx
  float m_nTransformState; // edx
  float v6; // st7
  float v7; // st7
  float v8; // st7
  char *p_m_nAnimState; // esi
  int v10; // eax
  char *v11; // eax
  float v12; // st7
  float v13; // st7
  int v14; // eax
  float v15; // st7
  long double v16; // st7
  float v17; // st7
  float v18; // st7
  float v19; // st7
  float v20; // st7
  float v21; // st7
  int v22; // eax
  int v23; // edi
  int nCurCount; // ecx
  int v25; // ecx
  char *v26; // eax
  char *v27; // eax
  char *v28; // eax
  char *v29; // eax
  char *v30; // eax
  float v31; // st7
  int v32; // [esp-0x8] [ebp-0x134]
  int v33; // [esp-0x8] [ebp-0x134]
  gbVec3D pConfig; // [esp+0xC] [ebp-0x120] BYREF
  int v35; // [esp+0x18] [ebp-0x114]
  gbVec3D v36; // [esp+0x1C] [ebp-0x110] BYREF
  float v37; // [esp+0x28] [ebp-0x104]
  char Buffer[256]; // [esp+0x2C] [ebp-0x100] BYREF

  v3 = *(&this->m_partyActor.m_nUpdateMode + 5);
  *(float *)&v35 = 12.0 * 8.0;
  switch ( v3 )
  {
    case 0:
      this->m_nCoreState = 1;
      this->RoleSystem::UpdateTransform();
      *(&this->m_partyActor.m_nUpdateMode + 5) = 1;
      this->m_fAnimSpeed = 160.0f;
      this->RoleSystem::StartHalfSpeedMovement();
      break;
    case 1:
      this->RoleSystem::PathFollowUpdate();
      this->RoleSystem::UpdateFollowVelocityEx();
      LODWORD(pConfig.x) = this->m_FrameA.m_fontcolor.Color;
      v4 = *(float *)&this->m_FrameA.m_id;
      pConfig.y = *(float *)&this->m_FrameA.m_wndcolor.Color * fVal;
      pConfig.z = v4 * fVal;
      this->m_fRotAxisX = pConfig.x * fVal + this->m_fRotAxisX;
      this->m_fRotAxisY = pConfig.y + this->m_fRotAxisY;
      this->m_fRotAxisZ = pConfig.z + this->m_fRotAxisZ;
      m_nTransformState = this->m_nTransformState;
      this->m_fRotAxisY = 0.0f;
      v37 = m_nTransformState;
      v6 = (((gbVec3D *)&this->m_fRotAxisX))->gbVec3D::Length();
      if ( v6 > v37 )
      {
        v7 = v37 / v6;
        this->m_fRotAxisX = v7 * this->m_fRotAxisX;
        this->m_fRotAxisY = v7 * this->m_fRotAxisY;
        this->m_fRotAxisZ = v7 * this->m_fRotAxisZ;
      }
      pConfig.x = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
      pConfig.y = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
      v8 = *(float *)&this->m_id - *(float *)&g_pRoleSystem->m_id;
      v36 = pConfig;
      pConfig.z = v8;
      if ( (((gbVec3D *)&v36))->gbVec3D::Length() < (double)*(float *)&v35 )
      {
        *(&this->m_partyActor.m_nUpdateMode + 5) = 2;
        this->RoleSystem::Notify();
        SetActionByName((Actor *)&this->m_partyActor.m_Actor, (const char *)&g_CCBStageData, 0, 0);
        p_m_nAnimState = (char *)&this->m_nAnimState;
        v10 = atoi(p_m_nAnimState);
        if ( g_ScriptCounters[(v10 - 415) % 0xAu].nCurCount < g_ScriptCounters[(v10 - 415) % 0xAu].nMaxCount )
          sprintf(Buffer, "%s_3", p_m_nAnimState);
        else
          sprintf(Buffer, "%s_1", p_m_nAnimState);
        v11 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(Buffer);
        (((UISceneMap *)&g_UISceneMapDlg))->UISceneMap::LoadCompass(v11, 0);
        (**(void ( ***)(UISceneMap *, int))((UIWnd *)&g_UISceneMapDlg))((UISceneMap *)(&g_UISceneMapDlg), (int)(1));
        (*(void ( **)(UISceneMap *, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)&g_UISceneMapDlg) + 8))(
          &g_UISceneMapDlg,
          0,
          0);
      }
      break;
    case 2:
      if ( (((Object3D *)&this->m_partyActor.m_Actor))->Object3D::GetVisNode() )
      {
        (*(void ( **)(gbActor *, int))(*(_DWORD *)((gbChain1DNode *)this->m_partyActor.m_pActor) + 24))(
          this->m_partyActor.m_pActor,
          1075137304);
        (((Actor *)&this->m_partyActor.m_Actor))->Actor::SetTimeScale(0.0);
        this->m_fPathSpeed = 0.0f;
        *(&this->m_partyActor.m_nUpdateMode + 5) = 3;
        this->m_fPathAngle = (float)(rand() % 100) * 0.09999999403953552f + 10.0f;
      }
      break;
    case 3:
      this->m_fPathSpeed = fVal + this->m_fPathSpeed;
      pConfig.x = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
      v12 = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
      v36.x = pConfig.x;
      pConfig.y = v12;
      v13 = *(float *)&this->m_id - *(float *)&g_pRoleSystem->m_id;
      v36.y = pConfig.y;
      pConfig.z = v13;
      v36.z = pConfig.z;
      if ( (((gbVec3D *)&v36))->gbVec3D::Length() < (double)*(float *)&v35 )
        this->m_fPathSpeed = 0.0f;
      if ( this->m_fPathSpeed >= (double)this->m_fPathAngle )
      {
        *(&this->m_partyActor.m_nUpdateMode + 5) = 4;
        v14 = rand();
        this->m_fRotAxisY = 0.0f;
        this->m_nCoreState = 2;
        v35 = v14 % 360;
        v15 = (float)(v14 % 360);
        *(&this[1].m_partyActor.m_fSpeed + 1) = v15;
        v16 = v15 * 0.017453292;
        this->m_fRotAxisX = sin(v16);
        this->m_fRotAxisZ = cos(v16);
        this->RoleSystem::UpdateTransform();
        v17 = this->m_nTransformState * 0.4000000059604645f;
        this->m_fRotAxisX = v17 * this->m_fRotAxisX;
        this->m_fRotAxisY = v17 * this->m_fRotAxisY;
        this->m_fRotAxisZ = v17 * this->m_fRotAxisZ;
        this->m_nMoveSubMode = 6;
        this->m_fPathSpeed = 0.0f;
      }
      break;
    case 4:
      v18 = fVal + this->m_fPathSpeed;
      this->m_fPathSpeed = v18;
      if ( v18 <= 30.0f )
      {
        pConfig.x = *(float *)&this->m_fontcolor.Color - *(float *)&g_pRoleSystem->m_fontcolor.Color;
        v19 = *(float *)&this->m_wndcolor.Color - *(float *)&g_pRoleSystem->m_wndcolor.Color;
        v36.x = pConfig.x;
        pConfig.y = v19;
        v20 = *(float *)&this->m_id - *(float *)&g_pRoleSystem->m_id;
        v36.y = pConfig.y;
        pConfig.z = v20;
        v36.z = pConfig.z;
        v21 = (((gbVec3D *)&v36))->gbVec3D::Length();
        *(float *)&v35 = v21;
        if ( v21 >= *(float *)&g_pRoleSystem->m_rect.left + *(float *)&this->m_rect.left )
        {
          if ( this->m_nMoveSubMode != 6 )
          {
            this->m_nCoreState = 2;
            this->RoleSystem::UpdateTransform();
            this->m_nMoveSubMode = 6;
          }
          this->RoleSystem::ScanMoveDirections(fVal);
          v31 = 2.0f - *(float *)&v35 / (float)dword_C10D40;
          if ( v31 >= 0.0f )
          {
            if ( v31 > 1.0f )
              v31 = 1.0f;
          }
          else
          {
            v31 = 0.0f;
          }
          this->m_fRotAxisX = v31 * this->m_fRotAxisX;
          this->m_fRotAxisY = v31 * this->m_fRotAxisY;
          this->m_fRotAxisZ = v31 * this->m_fRotAxisZ;
          if ( v31 == 0.0f )
            this->RoleSystem::IsPathComplete((float *)&g_pRoleSystem->m_fontcolor.Color, 1);
        }
        else
        {
          v22 = atoi(&this->m_nAnimState) - 415;
          v23 = v22;
          nCurCount = g_ScriptCounters[v22].nCurCount;
          if ( nCurCount >= g_ScriptCounters[v22].nMaxCount )
          {
            if ( v22 >= 2 )
            {
              if ( v22 >= 4 )
              {
                LODWORD(pConfig.x) = *(&g_ScriptCounters[0].nResourceID + 4 * v22);
                LODWORD(pConfig.y) = 1;
                LODWORD(pConfig.z) = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(SLODWORD(pConfig.x));
                (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive((int *)&pConfig);
                v33 = LODWORD(pConfig.z) + 4;
                v29 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("getitem");
                _snprintf(Buffer, 0xFFu, v29, v33);
                InputSystem::ProcessFrame(Buffer);
              }
              else
              {
                *(&g_RoleSlotBuf.dword_17AA450 + 147) += 9999;
                v28 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("getmoney");
                sprintf(Buffer, v28, 9999);
                InputSystem::ProcessFrame(Buffer);
              }
            }
            else
            {
              *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z + 352 * (_DWORD)dword_C10CC8) += 9999;
              v27 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("getexp");
              sprintf(Buffer, v27, 9999);
              InputSystem::ProcessFrame(Buffer);
            }
            g_ScriptCounters[v23].nState = 0;
            sprintf(Buffer, "%s_4", &this->m_nAnimState);
          }
          else
          {
            v25 = nCurCount + 1;
            g_ScriptCounters[v22].nCurCount = v25;
            v32 = v25;
            if ( v22 >= 4 )
            {
              *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z + 352 * (_DWORD)dword_C10CC8) += v25;
              v26 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("getexp");
            }
            else
            {
              *(&g_RoleSlotBuf.dword_17AA450 + 147) += v25;
              v26 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("getmoney");
            }
            sprintf(Buffer, v26, v32);
            InputSystem::ProcessFrame(Buffer);
            sprintf(Buffer, "%s_2", &this->m_nAnimState);
          }
          v30 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(Buffer);
          (((UISceneMap *)&g_UISceneMapDlg))->UISceneMap::LoadCompass(v30, 0);
          (**(void ( ***)(UISceneMap *, int))((UIWnd *)&g_UISceneMapDlg))((UISceneMap *)(&g_UISceneMapDlg), (int)(1));
          (*(void ( **)(UISceneMap *, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)&g_UISceneMapDlg) + 8))(
            &g_UISceneMapDlg,
            0,
            0);
          this->m_partyActor.m_pRoleObj = 0;
        }
      }
      else
      {
        this->m_partyActor.m_pRoleObj = 0;
      }
      break;
    default:
      return;
  }
}

// 0x0041ABE0
void RoleSystem::UpdateFollowVelocity()
{
  float v2; // st7
  float m_fWaypointZ; // ecx
  float v4; // st7
  float v5; // st7
  float v6; // [esp+0x8] [ebp-0x1C]
  float v7; // [esp+0x8] [ebp-0x1C]
  float m_fMovement; // [esp+0x8] [ebp-0x1C]
  float v9; // [esp+0x10] [ebp-0x14]
  float v10; // [esp+0x14] [ebp-0x10]
  float v11; // [esp+0x14] [ebp-0x10]
  float v12; // [esp+0x14] [ebp-0x10]
  gbVec3D v13; // [esp+0x18] [ebp-0xC] BYREF

  v13.y = 0.0f;
  v10 = this->m_fRotAxisZ * 1.399999976158142f;
  v11 = v10 + *(float *)&this->m_id;
  v13.x = this->m_fRotAxisX * 1.399999976158142f + *(float *)&this->m_fontcolor.Color - this->m_fWaypointX;
  v13.z = v11 - this->m_fWaypointZ;
  v2 = (((gbVec3D *)&v13))->gbVec3D::Length();
  if ( v2 > 100.0f )
  {
    m_fWaypointZ = this->m_fWaypointZ;
    *(float *)&this->m_FrameA.m_benable = this->m_fWaypointX;
    this->m_FrameA.m_bfocus = 0;
    *(float *)&this->m_FrameA.m_pbktex = m_fWaypointZ;
    *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable - *(float *)&this->m_fontcolor.Color;
    *(float *)&this->m_FrameA.m_bfocus = *(float *)&this->m_FrameA.m_bfocus - *(float *)&this->m_wndcolor.Color;
    *(float *)&this->m_FrameA.m_pbktex = *(float *)&this->m_FrameA.m_pbktex - *(float *)&this->m_id;
    (((gbVec3D *)&this->m_FrameA.m_benable))->gbVec3D::Normalize();
    v6 = v2;
    v7 = (v6 - 100.0f) * 1.399999976158142f;
    v9 = *(float *)&this->m_FrameA.m_bfocus * v7;
    v12 = *(float *)&this->m_FrameA.m_pbktex * v7;
    *(float *)&this->m_FrameA.m_fontcolor.Color = *(float *)&this->m_FrameA.m_benable * v7
                                                + *(float *)&this->m_FrameA.m_fontcolor.Color;
    *(float *)&this->m_FrameA.m_wndcolor.Color = v9 + *(float *)&this->m_FrameA.m_wndcolor.Color;
    *(float *)&this->m_FrameA.m_id = v12 + *(float *)&this->m_FrameA.m_id;
    m_fMovement = this->m_fMovement;
    v4 = (((gbVec3D *)&this->m_FrameA.m_fontcolor))->gbVec3D::Length();
    if ( v4 > m_fMovement )
    {
      v5 = m_fMovement / v4;
      *(float *)&this->m_FrameA.m_fontcolor.Color = v5 * *(float *)&this->m_FrameA.m_fontcolor.Color;
      *(float *)&this->m_FrameA.m_wndcolor.Color = v5 * *(float *)&this->m_FrameA.m_wndcolor.Color;
      *(float *)&this->m_FrameA.m_id = v5 * *(float *)&this->m_FrameA.m_id;
    }
  }
}

// 0x0041AD40
void RoleSystem::UpdateFollowVelocityEx()
{
  float v2; // st7
  float m_fWaypointZ; // ecx
  float v4; // st7
  float v5; // st7
  float v6; // [esp+0x8] [ebp-0x1C]
  float v7; // [esp+0x8] [ebp-0x1C]
  float m_fMovement; // [esp+0x8] [ebp-0x1C]
  float v9; // [esp+0x10] [ebp-0x14]
  float v10; // [esp+0x14] [ebp-0x10]
  float v11; // [esp+0x14] [ebp-0x10]
  float v12; // [esp+0x14] [ebp-0x10]
  gbVec3D v13; // [esp+0x18] [ebp-0xC] BYREF

  v13.y = 0.0f;
  v10 = this->m_fRotAxisZ * 1.399999976158142f;
  v11 = v10 + *(float *)&this->m_id;
  v13.x = this->m_fRotAxisX * 1.399999976158142f + *(float *)&this->m_fontcolor.Color - this->m_fWaypointX;
  v13.z = v11 - this->m_fWaypointZ;
  v2 = (((gbVec3D *)&v13))->gbVec3D::Length();
  if ( v2 > this->m_fAnimSpeed )
  {
    m_fWaypointZ = this->m_fWaypointZ;
    *(float *)&this->m_FrameA.m_benable = this->m_fWaypointX;
    this->m_FrameA.m_bfocus = 0;
    *(float *)&this->m_FrameA.m_pbktex = m_fWaypointZ;
    *(float *)&this->m_FrameA.m_benable = *(float *)&this->m_FrameA.m_benable - *(float *)&this->m_fontcolor.Color;
    *(float *)&this->m_FrameA.m_bfocus = *(float *)&this->m_FrameA.m_bfocus - *(float *)&this->m_wndcolor.Color;
    *(float *)&this->m_FrameA.m_pbktex = *(float *)&this->m_FrameA.m_pbktex - *(float *)&this->m_id;
    (((gbVec3D *)&this->m_FrameA.m_benable))->gbVec3D::Normalize();
    v6 = v2;
    v7 = (v6 - this->m_fAnimSpeed) * 1.399999976158142f;
    v9 = *(float *)&this->m_FrameA.m_bfocus * v7;
    v12 = *(float *)&this->m_FrameA.m_pbktex * v7;
    *(float *)&this->m_FrameA.m_fontcolor.Color = *(float *)&this->m_FrameA.m_benable * v7
                                                + *(float *)&this->m_FrameA.m_fontcolor.Color;
    *(float *)&this->m_FrameA.m_wndcolor.Color = v9 + *(float *)&this->m_FrameA.m_wndcolor.Color;
    *(float *)&this->m_FrameA.m_id = v12 + *(float *)&this->m_FrameA.m_id;
    m_fMovement = this->m_fMovement;
    v4 = (((gbVec3D *)&this->m_FrameA.m_fontcolor))->gbVec3D::Length();
    if ( v4 > m_fMovement )
    {
      v5 = m_fMovement / v4;
      *(float *)&this->m_FrameA.m_fontcolor.Color = v5 * *(float *)&this->m_FrameA.m_fontcolor.Color;
      *(float *)&this->m_FrameA.m_wndcolor.Color = v5 * *(float *)&this->m_FrameA.m_wndcolor.Color;
      *(float *)&this->m_FrameA.m_id = v5 * *(float *)&this->m_FrameA.m_id;
    }
  }
}

// 0x0041AEA0
void RoleSystem::SetBlendMode(float fAlpha)
{
  if ( fAlpha < 1.0f )
    (((gbVisNode *)this->m_partyActor.m_pActor))->gbVisNode::SetBlend(BLEND_ALPHA, fAlpha);
  else
    (((gbVisNode *)this->m_partyActor.m_pActor))->gbVisNode::SetBlend(BLEND_NONE, 1.0);
}

// 0x0041AEE0
int RoleSystem::SetTransform(int *p_DWORD)
{
  int result; // eax

  this->m_fontcolor.Color = p_DWORD[1];
  this->m_wndcolor.Color = p_DWORD[2];
  this->m_id = p_DWORD[3];
  LODWORD(this->m_fPosX) = (unsigned long)p_DWORD[40];
  LODWORD(this->m_fPosY) = (unsigned long)p_DWORD[41];
  LODWORD(this->m_fPosZ) = (unsigned long)p_DWORD[42];
  this->m_nDispFontColor = p_DWORD[37];
  this->m_nDispWndColor = p_DWORD[38];
  result = (unsigned long)p_DWORD[39];
  this->m_nTodo_9C = result;
  return result;
}

// 0x0041AF50
int RoleSystem::AllocPathPage(int nVal, int nVal2)
{
  float *p_m_fDirZ; // esi
  _DWORD *m_nTodo_7C; // eax
  int m_nPathFlag; // edx
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

  p_m_fDirZ = (float *)&this->m_fDirZ;
  if ( !this->m_pPathListHead
    || (m_nTodo_7C = (_DWORD *)this->m_nTodo_7C, m_nPathFlag = this->m_nPathFlag, m_nTodo_7C == (_DWORD *)m_nPathFlag) )
  {
    v8 = (int *)operator new(0x1000u);
    if ( *((_DWORD *)p_m_fDirZ + 11) )
    {
      v14 = *((_DWORD *)p_m_fDirZ + 8);
      if ( v14 >= *((_DWORD *)p_m_fDirZ + 9) + 4 * *((_DWORD *)p_m_fDirZ + 10) - 4 )
      {
        v19 = ((int)(v14 - *((_DWORD *)p_m_fDirZ + 4)) >> 2) + 1;
        v20 = (char *)&(((RoleSystem *)p_m_fDirZ))->RoleSystem::GetRoleName(2 * v19)[4 * v19];
        *(_DWORD *)v20 = (_DWORD)v8;
        (((ScreenEffect *)&v25))->ScreenEffect::CopyParams(*((int **)p_m_fDirZ + 3));
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
        *((_DWORD *)p_m_fDirZ + 7) = (unsigned long)v8;
        *((_DWORD *)p_m_fDirZ + 8) = (unsigned long)v20;
      }
      else
      {
        v15 = (int **)(v14 + 4);
        *((_DWORD *)p_m_fDirZ + 8) = (unsigned long)v15;
        *v15 = v8;
        (((ScreenEffect *)&v25))->ScreenEffect::CopyParams(v8);
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
      v9 = (_DWORD *)operator new(8u);
      *((_DWORD *)p_m_fDirZ + 9) = (unsigned long)v9;
      v9[1] = (_DWORD)v8;
      (((ScreenEffect *)&v25))->ScreenEffect::CopyParams(v8 + 512);
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
    m_nTodo_7C = (_DWORD *)*((_DWORD *)p_m_fDirZ + 7);
    *((_DWORD *)p_m_fDirZ + 7) = (unsigned long)(m_nTodo_7C + 4);
    if ( !m_nTodo_7C )
      goto LABEL_17;
    *m_nTodo_7C = 1;
    m_nTodo_7C[1] = nVal;
    m_nTodo_7C[2] = nVal2;
    goto LABEL_16;
  }
  this->m_nTodo_7C = (int)(m_nTodo_7C + 4);
  if ( m_nTodo_7C + 4 != (_DWORD *)m_nPathFlag )
  {
    if ( !m_nTodo_7C )
    {
LABEL_17:
      result = *((_DWORD *)p_m_fDirZ + 11) + 1;
      *((_DWORD *)p_m_fDirZ + 11) = result;
      return result;
    }
    *m_nTodo_7C = 1;
    m_nTodo_7C[1] = nVal;
    m_nTodo_7C[2] = nVal2;
LABEL_16:
    m_nTodo_7C[3] = v28;
    goto LABEL_17;
  }
  if ( m_nTodo_7C )
  {
    v6 = v28;
    *m_nTodo_7C = 1;
    m_nTodo_7C[1] = nVal;
    m_nTodo_7C[2] = nVal2;
    m_nTodo_7C[3] = v6;
  }
  (((ScreenEffectMgr *)p_m_fDirZ))->ScreenEffectMgr::AllocEffectBlock();
  result = *((_DWORD *)p_m_fDirZ + 11) + 1;
  *((_DWORD *)p_m_fDirZ + 11) = result;
  return result;
}

// 0x0041B120
int RoleSystem::StopPathMovement(int nVal)
{
  float *p_m_fDirZ; // esi
  _DWORD *m_nTodo_7C; // eax
  int m_nPathFlag; // edx
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

  p_m_fDirZ = (float *)&this->m_fDirZ;
  if ( !this->m_pPathListHead
    || (m_nTodo_7C = (_DWORD *)this->m_nTodo_7C, m_nPathFlag = this->m_nPathFlag, m_nTodo_7C == (_DWORD *)m_nPathFlag) )
  {
    v10 = (int *)operator new(0x1000u);
    if ( *((_DWORD *)p_m_fDirZ + 11) )
    {
      v16 = *((_DWORD *)p_m_fDirZ + 8);
      if ( v16 >= *((_DWORD *)p_m_fDirZ + 9) + 4 * *((_DWORD *)p_m_fDirZ + 10) - 4 )
      {
        v21 = ((int)(v16 - *((_DWORD *)p_m_fDirZ + 4)) >> 2) + 1;
        v22 = (char *)&(((RoleSystem *)p_m_fDirZ))->RoleSystem::GetRoleName(2 * v21)[4 * v21];
        *(_DWORD *)v22 = (_DWORD)v10;
        (((ScreenEffect *)&v30))->ScreenEffect::CopyParams(*((int **)p_m_fDirZ + 3));
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
        *((_DWORD *)p_m_fDirZ + 7) = (unsigned long)v10;
        *((_DWORD *)p_m_fDirZ + 8) = (unsigned long)v22;
      }
      else
      {
        v17 = (int **)(v16 + 4);
        *((_DWORD *)p_m_fDirZ + 8) = (unsigned long)v17;
        *v17 = v10;
        (((ScreenEffect *)&v30))->ScreenEffect::CopyParams(v10);
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
      v11 = (_DWORD *)operator new(8u);
      *((_DWORD *)p_m_fDirZ + 9) = (unsigned long)v11;
      v11[1] = (_DWORD)v10;
      (((ScreenEffect *)&v30))->ScreenEffect::CopyParams(v10 + 512);
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
    *((_DWORD *)p_m_fDirZ + 7) = (unsigned long)(v27 + 4);
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
  this->m_nTodo_7C = (int)(m_nTodo_7C + 4);
  if ( m_nTodo_7C + 4 != (_DWORD *)m_nPathFlag )
  {
    if ( m_nTodo_7C )
    {
      v8 = v31;
      v9 = v32;
      *m_nTodo_7C = 2;
      m_nTodo_7C[1] = v8;
      m_nTodo_7C[2] = v9;
      m_nTodo_7C[3] = nVal;
      result = *((_DWORD *)p_m_fDirZ + 11) + 1;
      *((_DWORD *)p_m_fDirZ + 11) = result;
      return result;
    }
    goto LABEL_16;
  }
  if ( m_nTodo_7C )
  {
    v5 = v31;
    v6 = v32;
    *m_nTodo_7C = 2;
    m_nTodo_7C[1] = v5;
    m_nTodo_7C[2] = v6;
    m_nTodo_7C[3] = nVal;
  }
  (((ScreenEffectMgr *)p_m_fDirZ))->ScreenEffectMgr::AllocEffectBlock();
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
    m_pPathCurrent = (char *)this->m_pPathCurrent;
    v4 = *(_DWORD *)m_pPathCurrent;
    nTileX = *((_DWORD *)m_pPathCurrent + 1);
    v12 = *((_DWORD *)m_pPathCurrent + 3);
    nTileY = *((_DWORD *)m_pPathCurrent + 2);
    v5 = this->m_pPathListHead - 1;
    this->m_pPathCurrent = ((char *)(m_pPathCurrent + 16));
    this->m_pPathListHead = ((char *)(v5));
    if ( !v5 || m_pPathCurrent + 16 == (char *)this->m_nPathCount )
    {
      m_pPathNext = (char *)this->m_pPathNext;
      this->m_pPathNext = ((char *)(m_pPathNext + 4));
      operator delete(*(void **)m_pPathNext);
      if ( this->m_pPathListHead )
      {
        v7 = (char **)this->m_pPathNext;
        v8 = (char *)*v7;
        this->m_pPathPoints = ((char *)(*v7));
        this->m_nPathCount = (int)(v8 + 4096);
        this->m_pPathCurrent = ((char *)(v8));
        this->m_pPathNext = ((char *)((char *)v7));
      }
      else
      {
        this->m_pPathPoints = ((char *)0);
        this->m_nPathCount = 0;
        this->m_pPathCurrent = ((char *)0);
        this->m_pPathNext = ((char *)0);
        this->m_nTodo_074 = 0;
        m_nPathState = (void *)this->m_nPathState;
        this->m_nPathFlag = 0;
        this->m_nTodo_7C = 0;
        this->m_fMoveX = 0.0f;
        operator delete(m_nPathState);
      }
    }
    if ( v4 == 1 )
    {
      this->RoleSystem::CalcTileDistance(nTileX, nTileY);
    }
    else if ( v4 == 2 )
    {
      this->m_partyActor.m_pRoleObj = v12;
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
  void **v9; // edi
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
    if ( (int)v5 >= (int)&dword_56A898 )
      goto LABEL_6;
  }
  v2 = v4;
LABEL_6:
  if ( this->m_nAnimState != 49 )
    return;
  if ( v2 != 32 && v2 != 46 )
  {
    if ( v2 != 29 || _strcmpi(&this->m_nAnimState, dword_58619C) )
    {
LABEL_24:
      LOBYTE(this->m_bRenderFlag1) = 0;
      BYTE1(this->m_bRenderFlag1) = 0;
      return;
    }
    LOBYTE(this->m_bRenderFlag1) = 0;
    BYTE1(this->m_bRenderFlag1) = 1;
    goto LABEL_19;
  }
  v6 = *(&dword_56A898 + v2) - 1;
  if ( *(&dword_56A898 + v2) == 1 )
  {
    LOBYTE(this->m_bRenderFlag1) = 1;
  }
  else
  {
    LOBYTE(this->m_bRenderFlag1) = 0;
    if ( v6 == 1 )
    {
      BYTE1(this->m_bRenderFlag1) = 1;
      goto LABEL_17;
    }
  }
  BYTE1(this->m_bRenderFlag1) = 0;
LABEL_17:
  if ( !_strcmpi(&this->m_nAnimState, (const char *)&g_pszSceneSlot1) )
  {
    LOBYTE(this->m_bRenderFlag1) = 1;
    BYTE1(this->m_bRenderFlag1) = 1;
  }
LABEL_19:
  v7 = 0;
  v8 = (char *)&g_RoleSlotBuf.dword_17AA450 + 774;
  while ( _strcmpi(&this->m_nAnimState, v8) )
  {
    v8 += 8704;
    ++v7;
    if ( (int)v8 >= (int)byte_C10A0E )
    {
      LOBYTE(this->m_bRenderFlag1) = 0;
      BYTE1(this->m_bRenderFlag1) = 0;
      return;
    }
  }
  if ( v7 == -1 )
    goto LABEL_24;
  v9 = (void **)(&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * v7);
  if ( *v9 )
  {
    sprintf(Buffer, "weapon\\%s\\%s.pol", (const char *)*v9 + 36, (const char *)*v9 + 36);
    sprintf(v14, "weapon\\%s\\%s%s.tga", (const char *)*v9 + 36, (const char *)*v9 + 36, (const char *)*v9 + 66);
    v10 = (gbGeomNode *)operator new(0x118u);
    v11 = (gbGeomNode *)v10;
    v15 = 0;
    if ( v10 )
    {
      v10->gbGeomNode::gbGeomNode();
      v12 = (gbGeomNode *)v11;
    }
    else
    {
      v12 = 0;
    }
    v15 = -1;
    this->m_pRenderObj = ((gbGeomNode *)(v12));
    (((gbGeomNode *)v12))->gbGeomNode::LoadFromFile(Buffer, 0, 0);
    (((gbGeomNode *)this->m_pRenderObj))->gbGeomNode::ReplaceTexture(v14);
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
  float v11; // st7
  int v12; // ebp
  int *v13; // esi
  int v14; // ecx
  __int64 v15; // rax
  int v16; // esi
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  float v20; // st7
  float v21; // st7
  float v22; // st7
  float v23; // st7
  int m_nState; // [esp-0x4] [ebp-0x74]
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

  m_nState = this->m_partyActor.m_nState;
  v3 = (RoleSystem *)UISceneUpdate();
  RolePtr = (((RoleSystem *)v3))->RoleSystem::GetRolePtr(m_nState);
  v5 = (__int64)((*(float *)&this->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_palScript.m_fSceneTileSize);
  pPoint = (__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
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
  v25 = (this->m_partyActor.m_nState + 1) % 2;
  v28 = v25;
  v9 = (RoleSystem *)UISceneUpdate();
  v10 = (((RoleSystem *)v9))->RoleSystem::GetRolePtr(v25);
  v11 = *(float *)&this->m_id - *(float *)(v10 + 136);
  v12 = (__int64)((*(float *)&this->m_fontcolor.Color - *(float *)(v10 + 128)) / *(float *)&g_palScript.m_fSceneTileSize);
  v36 = *(float *)&v12;
  v15 = (__int64)(v11 / *(float *)&g_palScript.m_fSceneTileSize);
  v13 = (int *)(v10 + 16 * v6);
  pPoint = v12;
  v35 = v15;
  v29 = v12;
  v31 = v15;
  v42 = (unsigned long)*v13;
  v14 = (unsigned long)v13[1];
  nVala = v14;
  v43 = (unsigned long)v13[2];
  HIDWORD(v15) = (unsigned long)v13[3];
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
  v37 = 0.0f;
  v36 = ((float)v29 + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(v10 + 128);
  v38 = ((float)v31 + 0.5f) * *(float *)&g_palScript.m_fSceneTileSize + *(float *)(v10 + 136);
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
  (((gbVec3D *)&v39))->gbVec3D::Normalize();
  if ( v39.z * *(float *)&this->m_rect.bottom
     + v39.y * *(float *)&this->m_rect.right
     + v39.x * *(float *)&this->m_rect.top > 0.30000001
    && 12.0 * 6.0 > (((gbVec3D *)&v40))->gbVec3D::Length() )
  {
    this->m_partyActor.m_nState = v28;
    this->RoleSystem::SetTargetRotation(&pTarget);
  }
  return 1;
}

// 0x0041BA10
BOOL RoleSystem::InterpolateHeight(float *pfVal)
{
  float v3; // st7
  float v4; // st6
  float v5; // st7
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
  v5 = (((gbVec3D *)&v7))->gbVec3D::Length();
  pfVala = v5;
  if ( v5 > 500.0f )
    return 0;
  if ( pfVala < 1.0f )
    return 1;
  return v7.z / pfVala * *(float *)&this->m_rect.bottom
       + v7.y / pfVala * *(float *)&this->m_rect.right
       + v7.x / pfVala * *(float *)&this->m_rect.top > 0.0;
}

// 0x0041BAD0
int RoleSystem::InitDefaultState()
{
  int result; // eax

  this->m_nMoveMode = 0;
  this->m_partyActor.m_nState = 0;
  memset(&this->m_nFacing, 0, 0x1C8u);
  this->m_nActionResult = 1;
  this->m_nRoleCount = 0;
  this->m_nActiveRole = 0;
  this->m_partyActor.m_pRoleObj = 1;
  this->m_nTransformMode = 0;
  this->m_pLinkedSystem = ((char *)0);
  memset(&this->m_partyActor.m_nUpdateMode + 5, 0, 0x24u);
  result = 1065353216;
  this->m_partyActor.m_fMatrixA = 0.0f;
  *(_DWORD *)&this->m_partyActor.m_fMatrixB = 1065353216;
  this->m_partyActor.m_fMatrixC = 0.0f;
  this->m_partyActor.m_fMatrixE = 1.0f;
  this->m_partyActor.m_fMatrixF = 0.0f;
  this->m_partyActor.m_fMatrixParamC = 0.0f;
  this->m_partyActor.m_nMatrixParam = 0;
  this->m_partyActor.m_fMatrixParamA = 0.0f;
  this->m_partyActor.m_fMatrixParamB = 1.0f;
  this->m_nMoveReset = 0;
  this->m_FrameA.m_rect.left = this->m_rect.top;
  this->m_FrameA.m_rect.top = this->m_rect.right;
  this->m_FrameA.m_rect.right = this->m_rect.bottom;
  this->m_FrameA.m_childs.m_nSize = 0;
  this->m_nRetryCount = 0;
  this->m_nMoveRole = 0;
  this->m_pCtrlPoint = ((char *)0);
  this->m_nCollisionState = 0;
  this->m_partyActor.m_nPathEnabled = 0;
  this->m_pRenderObj = ((gbGeomNode *)0);
  BYTE1(this->m_bRenderFlag1) = 0;
  LOBYTE(this->m_bRenderFlag1) = 0;
  this->m_bPathActive = 0;
  *(_DWORD *)&this->m_partyActor.m_fScale = 1065353216;
  this->m_nCollisionParam = 1;
  return result;
}

// 0x0041BBE0
int RoleSystem::GetCount()
{
  int result; // eax

  result = this->m_nMoveMode;
  if ( result != 4 )
  {
    this->m_nPrevMoveMode = result;
    this->m_nMoveMode = 4;
    this->m_fPathAngle = 2.0f;
    this->m_fPathSpeed = 0.0f;
    *(&this->m_partyActor.m_nUpdateMode + 5) = 44;
    SetActionByName((Actor *)&this->m_partyActor.m_Actor, "c08", 0, 0);
  }
  return result;
}

// 0x0041BC30
int RoleSystem::ExportRoleData(float *pfVal)
{
  int result; // eax
  float m_fPosZ; // edx

  result = (int)pfVal;
  *(_BYTE *)pfVal = this->m_partyActor.m_pRoleObj;
  *((_BYTE *)pfVal + 16) = this->m_partyActor.m_nState;
  if ( this->m_nMoveSubMode == 3 )
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
  pfVal[5] = *(&this[1].m_partyActor.m_fSpeed + 1);
  pfVal[6] = *(float *)&this->m_nSpawnExtra;
  return result;
}

// 0x0041BD40
int * RoleSystem::ClearColors(_BYTE *p_BYTE)
{
  int *result; // eax

  result = (int *)this;
  *(_BYTE *)((UIWnd *)this) = *p_BYTE;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 0;
  this->m_id = 0;
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
  this->m_pfather = ((UIWnd *)0);
  this->m_childs.m_pData = ((char *)0);
  this->m_childs.capacity = 0;
  this->m_childs.m_nSize = 0;
  return result;
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
  left = *((gbColorQuad **)this + 4);
  p_m_fontcolor = (gbColorQuad *)&this->m_pfather->UIWnd::m_fontcolor;
  v8 = (char *)&v5[4 * (nRoleIndex >> 2)];
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
  this->m_childs.m_pData = ((char *)(v5));
  this->m_childs.capacity = v2;
  return &v5[4 * (nRoleIndex >> 2)];
}

// 0x0041C190
int RoleSystem::SetInactive(int nVal)
{
  int result; // eax

  result = nVal;
  this->m_nActive = 0;
  LODWORD(this->m_fInactiveTime) = nVal;
  return result;
}

// 0x0041D220
int RoleSystem::AddCameraKeyframe()
{
  float m_fMoveSpeed; // edx
  float v2; // st7
  float m_fRoleParam2; // eax
  float m_fRoleParam; // edx
  void **p_m_pCmdQueue; // ebx
  int v6; // eax
  float m_fRoleParam3; // edx
  Actor *m_actarray_begin; // edi
  Actor *v9; // ecx
  int result; // eax
  void *v11; // esi
  void *v12; // eax
  void *v13; // eax
  void *v14; // edx
  void *v15; // ecx
  void *v16; // esi
  unsigned int v17; // eax
  _DWORD *v18; // eax
  void *v19; // eax
  void *v20; // edx
  void *v21; // eax
  int v22; // edi
  int *RoleName; // eax
  int *v24; // edi
  void *v25; // edx
  void *v26; // ecx
  void *v27; // edx
  void *v28; // edx
  void *v29; // ecx
  void *v30; // edx
  void *v31; // [esp+0xC] [ebp-0x2C] BYREF
  void *v32; // [esp+0x10] [ebp-0x28]
  void *v33; // [esp+0x14] [ebp-0x24]
  void *v34; // [esp+0x18] [ebp-0x20]
  float v35[7]; // [esp+0x1C] [ebp-0x1C] BYREF

  m_fMoveSpeed = this->m_partyActor.m_fMoveSpeed;
  v2 = *(float *)&this->m_fontcolor.Color;
  v35[1] = this->m_partyActor.m_fMoveRange;
  v35[3] = this->m_partyActor.m_fTransitionPos;
  m_fRoleParam2 = this->m_partyActor.m_fRoleParam2;
  v35[2] = m_fMoveSpeed;
  m_fRoleParam = this->m_partyActor.m_fRoleParam;
  p_m_pCmdQueue = (void **)&this->m_pCmdQueue;
  v35[5] = m_fRoleParam2;
  v35[4] = m_fRoleParam;
  v6 = *(_DWORD *)this->m_partyActor.m_name;
  m_fRoleParam3 = this->m_partyActor.m_fRoleParam3;
  v35[0] = v2;
  v35[6] = m_fRoleParam3;
  if ( !v6
    || (m_actarray_begin = this->m_partyActor.m_actarray_begin,
        v9 = (Actor *)(*(Actor **)&this->m_partyActor.m_actarray_type),
        m_actarray_begin == v9) )
  {
    v11 = (void *)operator new(0xFF8u);
    if ( p_m_pCmdQueue[11] )
    {
      v17 = (unsigned int)p_m_pCmdQueue[8];
      if ( v17 >= (unsigned int)p_m_pCmdQueue[9] + 4 * (_DWORD)p_m_pCmdQueue[10] - 4 )
      {
        v22 = ((int)(v17 - (_DWORD)p_m_pCmdQueue[4]) >> 2) + 1;
        RoleName = (int *)(((RoleSystem *)p_m_pCmdQueue))->RoleSystem::GetRoleName(2 * v22);
        v24 = (int *)&RoleName[v22];
        *v24 = (int)v11;
        (((CameraCtrl *)&v31))->CameraCtrl::SetCameraSource((int)p_m_pCmdQueue[3], RoleName);
        v25 = (void *)v32;
        p_m_pCmdQueue[1] = v31;
        v26 = (void *)v33;
        p_m_pCmdQueue[2] = v25;
        v27 = (void *)v34;
        p_m_pCmdQueue[3] = v26;
        p_m_pCmdQueue[4] = v27;
        (((CameraCtrl *)&v31))->CameraCtrl::SetCameraSource((int)v11, v24);
        v28 = (void *)v32;
        p_m_pCmdQueue[5] = v31;
        v29 = (void *)v33;
        p_m_pCmdQueue[6] = v28;
        v30 = (void *)v34;
        p_m_pCmdQueue[7] = v29;
        p_m_pCmdQueue[8] = v30;
      }
      else
      {
        v18 = (_DWORD *)(v17 + 4);
        p_m_pCmdQueue[8] = v18;
        *v18 = (_DWORD)v11;
        (((CameraCtrl *)&v31))->CameraCtrl::SetCameraSource((int)v11, (int *)p_m_pCmdQueue[8]);
        v19 = (void *)v32;
        p_m_pCmdQueue[5] = v31;
        v20 = (void *)v33;
        p_m_pCmdQueue[6] = v19;
        v21 = (void *)v34;
        p_m_pCmdQueue[7] = v20;
        p_m_pCmdQueue[8] = v21;
      }
    }
    else
    {
      p_m_pCmdQueue[10] = (void *)2;
      v12 = (void *)operator new(8u);
      p_m_pCmdQueue[9] = v12;
      *((_DWORD *)v12 + 1) = (unsigned long)v11;
      (((CameraCtrl *)&v31))->CameraCtrl::SetCameraSource((int)v11 + 2044, (int *)p_m_pCmdQueue[9] + 1);
      v13 = (void *)v31;
      v14 = (void *)v33;
      v15 = (void *)v32;
      v16 = (void *)v34;
      p_m_pCmdQueue[1] = v31;
      p_m_pCmdQueue[2] = v15;
      p_m_pCmdQueue[3] = v14;
      p_m_pCmdQueue[4] = v16;
      p_m_pCmdQueue[5] = v13;
      p_m_pCmdQueue[6] = v15;
      p_m_pCmdQueue[7] = v14;
      p_m_pCmdQueue[8] = v16;
    }
    m_actarray_begin = (Actor *)p_m_pCmdQueue[7];
    p_m_pCmdQueue[7] = &m_actarray_begin->m_fMoveSpeed;
    if ( !m_actarray_begin )
      goto LABEL_16;
    goto LABEL_15;
  }
  p_m_pCmdQueue[7] = &m_actarray_begin->m_fMoveSpeed;
  if ( (Actor *)&m_actarray_begin->m_fMoveSpeed != v9 )
  {
    if ( !m_actarray_begin )
    {
LABEL_16:
      result = (int)p_m_pCmdQueue[11] + 1;
      p_m_pCmdQueue[11] = (void *)result;
      return result;
    }
LABEL_15:
    qmemcpy(m_actarray_begin, v35, 0x1Cu);
    goto LABEL_16;
  }
  if ( m_actarray_begin )
    qmemcpy(m_actarray_begin, v35, 0x1Cu);
  (((CameraCtrl *)p_m_pCmdQueue))->CameraCtrl::UpdateFOVLerp();
  result = (int)p_m_pCmdQueue[11] + 1;
  p_m_pCmdQueue[11] = (void *)result;
  return result;
}

// 0x00420290
RoleSystem::RoleSystem()
{
  ;
}

// 0x004202A0
void * RoleSystem::AllocSlotData(int nVal)
{
  unsigned int v3; // ecx
  unsigned int v4; // eax
  unsigned int v5; // ebx
  void *result; // eax
  void *v7; // edi

  (**(void ( ***)(RoleSystem *))((UIWnd *)this))((RoleSystem *)(this));
  v3 = *(_DWORD *)(nVal + 152);
  this->m_fontcolor.Color = v3;
  v4 = *(_DWORD *)(nVal + 156);
  this->m_wndcolor.Color = v4;
  v5 = v4 * v3;
  result = (void *)malloc(v4 * v3);
  v7 = (void *)result;
  this->m_id = (unsigned int)result;
  if ( result )
  {
    result = 0;
    memset(v7, 0, v5);
  }
  return result;
}

// 0x00420320
int RoleSystem::GetCurrentID(int *pnVal, char pData)
{
  int result; // eax
  int v5; // ecx
  int i; // eax
  unsigned int v7; // ebx

  result = this->m_id;
  if ( result )
  {
    sub_420380(pnVal);
    v5 = (unsigned long)pnVal[1];
    for ( result = pnVal[3]; v5 <= result; ++v5 )
    {
      for ( i = *pnVal; i <= pnVal[2]; *(_BYTE *)(v7 + this->m_id) = (_BYTE)pData )
      {
        v7 = i + v5 * this->m_fontcolor.Color;
        ++i;
      }
      result = (unsigned long)pnVal[3];
    }
  }
  return result;
}

// 0x004203C0
void RoleSystem::InitRoleImage()
{
  sub_420250();
  ((gbImage2D *)&this->m_bvisible)->gbImage2D::gbImage2D();
  *(_DWORD *)&this->m_nActionParam = 0;
  this->m_rect.left = 0;
  memset(&this->m_nInitMoveMode + 1, 0, 0x80u);
}

// 0x004207D0
unsigned __int8 * RoleSystem::LoadRoleImage(int nIndex, const char *pszPath)
{
  unsigned __int8 *result; // eax
  unsigned __int8 *v5; // ebp
  unsigned __int8 *v6; // edx
  int v7; // ecx

  (**(void ( ***)(RoleSystem *))((UIWnd *)this))((RoleSystem *)(this));
  this->RoleSystem::AllocSlotData(nIndex);
  *(_DWORD *)&this->m_nActionParam = nIndex;
  result = (unsigned __int8 *)gfxMgr->NewTexture(0);
  v5 = (unsigned __int8 *)result;
  if ( result )
  {
    result = (((gbImage2D *)&this->m_bvisible))->gbImage2D::CreateImage(256, 256, 32);
    v6 = (unsigned __int8 *)result;
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
      return (unsigned __int8 *)sprintf((char *const)&this->m_nInitMoveMode + 1, "%s%s", pszPath, pszPath + 32);
    }
  }
  return result;
}

// 0x004208A0
void RoleSystem::Reset()
{
  gbRefObject *m_bcreateok; // ecx

  m_bcreateok = (gbRefObject *)this->m_bcreateok;
  if ( m_bcreateok )
  {
    (((gbRefObject *)m_bcreateok))->gbRefObject::Release();
    this->m_bcreateok = 0;
  }
  (((gbImage2D *)&this->m_bvisible))->gbImage2D::Release();
  (((gbRenderEffect *)this))->gbRenderEffect::sub_4202F0();
  *(_DWORD *)&this->m_nActionParam = 0;
  memset(&this->m_nInitMoveMode + 1, 0, 0x80u);
  this->m_nInitMoveMode = 0;
}

// 0x00420930
void RoleSystem::InitInternal(int nVal1)
{
  this->RoleSystem::RoleSystem();
}

// 0x00420940
int RoleSystem::CopyRoleToSlot(RoleSystem *pRoleSystem, int index)
{
  int RolePtr; // eax
  int v5; // ebp
  int result; // eax
  RoleSystem *p_m_nSpawnData; // edi

  RolePtr = (((RoleSystem *)pRoleSystem))->RoleSystem::GetRolePtr(index);
  this->RoleSystem::AllocSlotData(RolePtr);
  memset((void *)this->m_id, 0xFFu, this->m_fontcolor.Color * this->m_wndcolor.Color);
  v5 = 0;
  this->m_rect.left = (LONG)pRoleSystem;
  result = LODWORD(pRoleSystem->m_fTileHeight);
  if ( result > 0 )
  {
    p_m_nSpawnData = (RoleSystem *)&pRoleSystem->m_nSpawnData;
    do
    {
      if ( (unsigned __int8)p_m_nSpawnData->m_nRoleSlot == index
        && !(((RoleSystem *)p_m_nSpawnData))->RoleSystem::SetActionState((int)this, v5)
        && (p_m_nSpawnData->m_bFlags & 1) != 0 )
      {
        this->RoleSystem::GetCurrentID(&p_m_nSpawnData->m_nActionType, v5);
      }
      result = LODWORD(pRoleSystem->m_fTileHeight);
      ++v5;
      p_m_nSpawnData = (RoleSystem *)((char *)p_m_nSpawnData + 896);
    }
    while ( v5 < result );
  }
  return result;
}

// 0x004209E0
void RoleSystem::ResetState(int nVal1)
{
  this->m_rect.left = 0;
  (((gbRenderEffect *)this))->gbRenderEffect::sub_4202F0();
}

// 0x004209F0
char RoleSystem::GetTile(int nX, int nY)
{
  return *(_BYTE *)(this->m_id + nY * this->m_fontcolor.Color + nX);
}

// 0x00420A10
int * RoleSystem::IsTileInBounds(int nVal, int nY, int nVal2)
{
  int Tile; // eax

  if ( nY < 0 )
    return 0;
  if ( nY >= this[64].m_teamData3[41 * nVal + 444] )
    return 0;
  if ( nVal2 < 0 )
    return 0;
  if ( nVal2 >= this[64].m_teamData3[41 * nVal + 445] )
    return 0;
  Tile = (unsigned __int8)(((RoleSystem *)(&this->m_mapData + 5 * nVal)))->RoleSystem::GetTile(nY, nVal2);
  if ( Tile >= SLODWORD(this->m_fTileHeight) )
    return 0;
  else
    return &this->m_nSpawnData + 224 * Tile;
}

// 0x00420A90
void RoleSystem::SetRoleGridPosition(float fVal, int nVal, float fVal2, int nVal2)
{
  int v6; // ebp
  __int64 v7; // rax
  unsigned __int8 nVal2a; // [esp+0x1C] [ebp+0x10]

  v6 = (__int64)((fVal - *(float *)&this[64].m_teamData3[41 * nVal2 + 438]) / g_fTileScale);
  v7 = (__int64)((fVal2 - *(float *)&this[64].m_teamData3[41 * nVal2 + 440]) / g_fTileScale);
  if ( v6 >= 0
    && v6 < this[64].m_teamData3[41 * nVal2 + 444]
    && (int)v7 >= 0
    && (int)v7 < this[64].m_teamData3[41 * nVal2 + 445] )
  {
    nVal2a = (((RoleSystem *)(&this->m_mapData + 5 * nVal2)))->RoleSystem::GetTile(v6, v7);
    if ( nVal2a != 0xFF )
      (((ScriptVM *)(&this->m_nSpawnData + 224 * nVal2a)))->ScriptVM::ExecuteBlock();
  }
}

// 0x00420F30
int RoleSystem::GetRolePtr(int index)
{
  return (int)&this[64].m_teamData3[41 * index + 406];
}

// 0x00420F50
char * RoleSystem::GetMapNodePtr(int nIndex)
{
  return (char *)&this[64].m_teamData3[4 * nIndex + 488];
}

// 0x00420F70
BOOL RoleSystem::IsRoleInRange(int index, int *pnVal, int nVal)
{
  int RolePtr; // eax

  RolePtr = this->RoleSystem::GetRolePtr(index);
  return (int)pnVal >= 0
      && (int)pnVal < *(_DWORD *)(RolePtr + 152)
      && nVal >= 0
      && nVal < *(_DWORD *)(RolePtr + 156)
      && (((GRPinput *)RolePtr))->GRPinput::GetJoystickFreePos((int)pnVal, nVal);
}

// 0x00420FB0
BOOL RoleSystem::CheckMoveCollision(int *index, float *pfVal, int nVal)
{
  int RolePtr; // edi

  RolePtr = this->RoleSystem::GetRolePtr((int)index);
  return this->RoleSystem::CheckCollision(index, (__int64)((*pfVal - *(float *)(RolePtr + 128)) / g_fTileScale));
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

  RolePtr = this->RoleSystem::GetRolePtr((int)pResult);
  if ( nFlag < 0 || nFlag >= *(_DWORD *)(RolePtr + 152) || y < 0 || y >= *(_DWORD *)(RolePtr + 156) )
    return 0;
  pResulta = (int *)(((GRPinput *)RolePtr))->GRPinput::GetJoystickFreePos(nFlag, y);
  nFlaga = (((RoleSystem *)(&this->m_mapData + 5 * (_DWORD)pResult)))->RoleSystem::GetTile(nFlag, y);
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

  RolePtr = this->RoleSystem::GetRolePtr(nSceneIdx);
  if ( nX < 0 || nX >= *(_DWORD *)(RolePtr + 152) || nY < 0 || nY >= *(_DWORD *)(RolePtr + 156) )
    return 0;
  nSceneIdxa = (((GRPinput *)RolePtr))->GRPinput::GetJoystickFreePos(nX, nY);
  Tile = (((RoleSystem *)(&this->m_mapData + 5 * nSceneIdx)))->RoleSystem::GetTile(nX, nY);
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

  RolePtr = this->RoleSystem::GetRolePtr(index);
  v7 = (__int64)((*pfVal - *(float *)(RolePtr + 128)) / g_fTileScale);
  v8 = (__int64)((pfVal[2] - *(float *)(RolePtr + 136)) / g_fTileScale);
  if ( pnVal )
  {
    *pnVal = v7;
    pnVal[1] = v8;
  }
  (((Scene *)this))->Scene::GetTileHeight(index, v7, v8, p_DWORD);
}

// 0x004214B0
BOOL RoleSystem::ValidatePathIndex(int index, int nY, int nVal)
{
  int RolePtr; // eax
  int v6; // esi
  BOOL result; // eax
  int v8; // ecx
  unsigned __int8 indexa; // [esp+0x14] [ebp+0x4]

  RolePtr = this->RoleSystem::GetRolePtr(index);
  v6 = RolePtr;
  if ( nY < 0 || nY >= *(_DWORD *)(RolePtr + 152) || nVal < 0 || nVal >= *(_DWORD *)(RolePtr + 156) )
    return 0;
  indexa = (((RoleSystem *)(&this->m_mapData + 5 * index)))->RoleSystem::GetTile(nY, nVal);
  result = 1;
  if ( indexa == 0xFF || *((_BYTE *)&this->m_partyActor.m_fTransitionPos + 896 * indexa) != 44 )
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

  if ( this->RoleSystem::CheckCollision(pResult, (int)nFlag) && this->RoleSystem::CheckCollision(pResult, (int)pszBuf) )
  {
    if ( (int)pszBuf < (int)nFlag )
    {
      v6 = (unsigned long)(nFlag - pszBuf);
      v13 = -1;
    }
    else
    {
      v13 = 1;
      v6 = (unsigned long)(pszBuf - nFlag);
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
    while ( this->RoleSystem::CheckCollision(pResult, (int)nFlag) )
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
  if ( !this->RoleSystem::CheckCollision(pResult, (int)nFlag) )
    return 0;
  v9 = (int *)nFlag;
  v10 = (int *)pnVal;
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
    while ( this->RoleSystem::CheckCollision(pResult, (int)v9) )
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

  v7 = (int *)nFlag;
  v8 = (int *)pnVal;
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
    v9 = (unsigned long)(pszBuf - (char *)nFlag);
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
    while ( this->RoleSystem::ValidatePathIndex((int)pResult, (int)v7, (int)v8) )
    {
      if ( this->RoleSystem::CheckCollision(pResult, (int)v7) )
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
        v7 = (int *)nFlag;
        goto LABEL_24;
      }
    }
    return 0;
  }
LABEL_24:
  if ( !this->RoleSystem::CheckCollision(pResult, (int)v7) )
    return 0;
  return this->RoleSystem::CheckCollision(pResult, (int)pszBuf);
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

  if ( this->RoleSystem::IsTilePassable(arg0, index, (int)pszBuf, nVal)
    && this->RoleSystem::IsTilePassable(arg0, index, (int)pszBuf2, nVal2) )
  {
    if ( (int)pszBuf2 < (int)pszBuf )
    {
      v7 = (unsigned long)(pszBuf - pszBuf2);
      v14 = -1;
    }
    else
    {
      v14 = 1;
      v7 = (unsigned long)(pszBuf2 - pszBuf);
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
    while ( this->RoleSystem::IsTilePassable(arg0, index, (int)pszBuf, nVal) )
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

  v3 = (int *)pnVal;
  Color = this->m_wndcolor.Color;
  nVal2[1] = 0;
  nVal2[0] = 0;
  v15 = (int *)this->m_fontcolor.Color;
  v16 = Color;
  (((Config *)pnVal))->Config::InitDefaults(&p_DWORD, (int *)&pnVal);
  v6 = p_DWORD;
  if ( p_DWORD < nVal2[0] )
  {
    v6 = nVal2[0];
    p_DWORD = nVal2[0];
  }
  result = (int *)pnVal;
  if ( (int)pnVal > (int)v15 )
  {
    result = (int *)v15;
    pnVal = (int)v15;
  }
  if ( v6 < (int)result )
  {
    v8 = (char)pData;
    do
    {
      if ( (((Config *)v3))->Config::ReadFloatArray(v6, (int)nVal2, &v13, &pnVal2) )
      {
        for ( i = v13; i < pnVal2; *(_BYTE *)(v10 + this->m_id) = v8 )
          v10 = v6 + this->m_fontcolor.Color * i++;
      }
      result = (int *)pnVal;
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

  result = this->m_id;
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
              *(_BYTE *)(this->m_id + v10 + v7 * this->m_fontcolor.Color) = (_BYTE)pData;
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
  float m_fTileHeight; // esi
  int v2; // edx
  float *p_m_fTransitionPos; // eax
  char *v4; // eax

  m_fTileHeight = this->m_fTileHeight;
  v2 = 0;
  if ( SLODWORD(m_fTileHeight) <= 0 )
  {
LABEL_7:
    v4 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("XMouse");
    InputSystem::ProcessFrame(v4);
  }
  else
  {
    p_m_fTransitionPos = (float *)&this->m_partyActor.m_fTransitionPos;
    while ( !*((_BYTE *)p_m_fTransitionPos - 71)
         || *(_BYTE *)p_m_fTransitionPos != 24
         || *((_DWORD *)p_m_fTransitionPos + 2) != 1 )
    {
      ++v2;
      p_m_fTransitionPos += 224;
      if ( v2 >= SLODWORD(m_fTileHeight) )
        goto LABEL_7;
    }
    (((ScriptVM *)(&this->m_nSpawnData + 224 * v2)))->ScriptVM::ExecuteBlock();
  }
}

// 0x00421F20
size_t RoleSystem::GetFontColor(FILE *Stream)
{
  gbColorQuad *p_m_fontcolor; // edi

  p_m_fontcolor = (gbColorQuad *)&this->m_fontcolor;
  fwrite(&this->m_fontcolor, 4u, 1u, Stream);
  fwrite(&this->m_wndcolor, 4u, 1u, Stream);
  return fwrite((const void *)this->m_id, p_m_fontcolor->Color * this->m_wndcolor.Color, 1u, Stream);
}

// 0x00421F70
char RoleSystem::ClearPathData(FILE *Buffer)
{
  FILE *v2; // edi
  unsigned int Color; // ecx
  unsigned int v5; // eax
  int v7; // [esp+0xC] [ebp-0x4] BYREF

  v2 = (FILE *)Buffer;
  fread(&Buffer, 4u, 1u, Buffer);
  fread(&v7, 4u, 1u, v2);
  Color = this->m_fontcolor.Color;
  if ( Buffer == (FILE *)Color )
  {
    v5 = this->m_wndcolor.Color;
    if ( v7 == v5 )
      fread((void *)this->m_id, Color * v5, 1u, v2);
  }
  return sub_4204B0(
           0,
           0,
           *(_DWORD *)(*(_DWORD *)&this->m_nActionParam + 152),
           *(_DWORD *)(*(_DWORD *)&this->m_nActionParam + 156),
           1);
}

// 0x00422000
BOOL RoleSystem::BuildModelPath(const char *pszName)
{
  char Buffer[128]; // [esp+0x4] [ebp-0x80] BYREF

  sprintf(Buffer, "%s%s", pszName, pszName + 32);
  return _strcmpi(Buffer, (const char *)&this->m_nInitMoveMode + 1) == 0;
}

// 0x00422140
int * RoleSystem::ResetModelPaths()
{
  int v2; // edi
  int *p_m_szModelPath; // esi
  char *p_m_szText; // esi
  int v5; // ebx

  v2 = 50;
  p_m_szModelPath = (int *)&this->m_szModelPath;
  do
  {
    p_m_szModelPath += 114;
    --v2;
  }
  while ( v2 );
  p_m_szText = (char *)&this[3].m_partyActor.m_szText;
  v5 = 64;
  do
  {
    *((_DWORD *)p_m_szText - 86) = 0;
    *((_DWORD *)p_m_szText - 85) = 0;
    *((_DWORD *)p_m_szText - 84) = 0;
    *((_DWORD *)p_m_szText - 5) = 0;
    *((_DWORD *)p_m_szText - 4) = 0;
    *((_DWORD *)p_m_szText - 3) = 0;
    *((_DWORD *)p_m_szText - 2) = 0;
    *((_DWORD *)p_m_szText - 1) = 0;
    *(_DWORD *)p_m_szText = 0;
    p_m_szText += 620;
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
  g_ScriptSystemData.m_fTimerA = 12.0 + 12.0;
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
    return (((ScriptPoolPage *)g_pCameraCtrl))->ScriptPoolPage::ScriptPoolPage_Manage(1);
  else
    return (((ScriptPoolPage *)g_pCameraCtrl))->ScriptPoolPage::ScriptPoolPage_Manage(0);
}

// 0x0042A010
void RoleSystem::ProcessAction()
{
  int *p_m_szModelName; // esi
  int RolePtr; // ebp
  int m_nRoleAction; // eax
  double v5; // st7
  double v6; // st6
  double v8; // st7
  unsigned __int8 v9; // c0
  unsigned __int8 v10; // c3
  double v11; // st7
  unsigned __int8 v13; // c0
  unsigned __int8 v14; // c3
  double v15; // st6
  float v16; // esi
  double v17; // st7
  float v18; // ebx
  __int64 v19; // rax
  float v20; // ecx
  float y; // ecx
  char v22; // al
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

  p_m_szModelName = (int *)&this->m_szModelName;
  if ( _strcmpi((const char *)&this->m_szModelName, "g01.cvd")
    && (LODWORD(this->m_fDirX) != 4 || _strcmpi((const char *)p_m_szModelName, a4_0)) )
  {
    (((Object3D *)this))->Object3D::SetTransform(&pMatrix.trans);
    RolePtr = (((RoleSystem *)*(RoleSystem **)(LODWORD(this->m_partyActor.m_vecPos.z) + 16)))->RoleSystem::GetRolePtr((unsigned __int8)this->m_nRoleSlot);
    m_nRoleAction = (unsigned __int8)this->m_nRoleAction;
    v54 = RolePtr;
    switch ( m_nRoleAction )
    {
      case 5:
      case 23:
        goto LABEL_14;
      case 7:
        v8 = g_ScriptSystemData.m_g_fTimeDelta;
        if ( !(v9 | v10) )
        {
          pMatrix.xlen = v8 * 4.5f + pMatrix.xlen;
          v11 = pMatrix.zlen - g_ScriptSystemData.m_g_fTimeDelta * 2.5;
          goto LABEL_20;
        }
        pMatrix.xlen = pMatrix.xlen - v8 * 2.5f;
        v5 = g_ScriptSystemData.m_g_fTimeDelta * 4.5;
        goto LABEL_19;
      case 11:
        if ( LODWORD(this->m_fWaypointX) != 1 )
          goto LABEL_21;
LABEL_14:
        v5 = g_ScriptSystemData.m_g_fTimeDelta * 2.5;
LABEL_17:
        v15 = v5 + pMatrix.xlen;
        goto LABEL_18;
      case 19:
        pMatrix.xlen = pMatrix.xlen - g_ScriptSystemData.m_g_fTimeDelta * 3.5f;
        v5 = g_ScriptSystemData.m_g_fTimeDelta * 1.5;
        goto LABEL_19;
      case 22:
      case 34:
        v5 = g_ScriptSystemData.m_g_fTimeDelta * 1.5;
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
        (((gbOBBox *)&pMatrix))->gbOBBox::GetAABBox(v55);
        LODWORD(v16) = (__int64)((v55.max.x - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_g_fTimeDelta);
        v17 = v55.min.x - *(float *)(RolePtr + 128);
        LODWORD(v52.y) = (__int64)((v55.max.z - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta);
        LODWORD(v18) = (__int64)(v17 / g_ScriptSystemData.m_g_fTimeDelta);
        v19 = (__int64)((v55.min.z - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta);
        v20 = v16;
        if ( SLODWORD(v16) >= SLODWORD(v18) )
          LODWORD(v20) = (__int64)(v17 / g_ScriptSystemData.m_g_fTimeDelta);
        this->m_partyActor.m_vecRot.z = v20;
        if ( SLODWORD(v16) <= SLODWORD(v18) )
          v16 = v18;
        y = v52.y;
        this->m_partyActor.m_fActionAssignParam = v16;
        *((float *)&v19 + 1) = y;
        if ( SLODWORD(y) >= (int)v19 )
          HIDWORD(v19) = v19;
        this->m_partyActor.m_nCloneParam = HIDWORD(v19);
        if ( SLODWORD(y) > (int)v19 )
          *(float *)&v19 = y;
        this->m_partyActor.m_nCloneParamB = v19;
        if ( this->m_nRoleAction == 23 && UIScene::ProcessInput("m15", a2) )
        {
          if ( !v120 )
          {
LABEL_32:
            (((RoleSystem *)LODWORD(this->m_partyActor.m_vecPos.z)))->RoleSystem::GetCurrentID((int *)&this->m_partyActor.m_vecRot.z, LOBYTE(this->m_partyActor.m_vecRot.x));
            return;
          }
          goto LABEL_42;
        }
        if ( this->m_nRoleAction == 22 && UIScene::ProcessInput("M22", a3) )
        {
          if ( !v120 )
            goto LABEL_32;
          goto LABEL_42;
        }
        v22 = this->m_nRoleAction;
        if ( v22 == 37 || v22 == 38 || v22 == 42 )
        {
          memset(&v52, 0, sizeof(v52));
          (((gbMatrix4 *)&pMatrix.trans))->gbMatrix4::Transform(&v52, 1);
          v34 = (__int64)((v52.x - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_g_fTimeDelta);
          v35 = (__int64)((v52.z - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta);
          v36 = (__int64)(pMatrix.zlen / g_ScriptSystemData.m_g_fTimeDelta);
          if ( (int)(__int64)(pMatrix.xlen / g_ScriptSystemData.m_g_fTimeDelta) < (int)v36 )
            LODWORD(v36) = (__int64)(pMatrix.xlen / g_ScriptSystemData.m_g_fTimeDelta);
          v37 = this->m_nRoleAction;
          v38 = (int)v36 / 2;
          if ( v37 == 38 )
            ++v38;
          if ( v37 == 42 )
            v38 = 3;
          if ( v120 )
            (((RoleSystem *)LODWORD(this->m_partyActor.m_vecPos.z)))->RoleSystem::ClearWaypointBuffer(v34, v35, v38, 255);
          else
            (((RoleSystem *)LODWORD(this->m_partyActor.m_vecPos.z)))->RoleSystem::ClearWaypointBuffer(v34, v35, v38, LOBYTE(this->m_partyActor.m_vecRot.x));
        }
        else
        {
          if ( v22 == 11 )
          {
            if ( !v120 )
              goto LABEL_32;
LABEL_42:
            (((RoleSystem *)LODWORD(this->m_partyActor.m_vecPos.z)))->RoleSystem::GetCurrentID((int *)&this->m_partyActor.m_vecRot.z, 255);
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
          v43 = pMatrix.ylen * 0.5f;
          v40 = pMatrix.xlen * -0.5f;
          *(float *)base = v40;
          *(float *)&base[1] = v43;
          v59[5] = v40;
          v57 = pMatrix.zlen * 0.5f;
          v59[13] = v40;
          v67 = v40;
          v76 = v40;
          v50 = pMatrix.xlen * 0.5f;
          v58 = v50;
          v59[0] = v43;
          v59[2] = v50;
          v59[1] = v57;
          v61 = v50;
          v64 = v50;
          v70 = v40;
          v73 = v40;
          v79 = v40;
          v47 = pMatrix.ylen * -0.5f;
          v59[3] = v47;
          v59[4] = v57;
          v59[6] = v47;
          v59[7] = v57;
          v59[14] = v43;
          v60 = pMatrix.zlen * -0.5f;
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
          v51 = 40000.0f;
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
            (((gbMatrix4 *)&pMatrix.trans))->gbMatrix4::Transform((gbVec3D *)(v27 - 4), 4);
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
          (((Config *)&v118))->Config::ResetField7();
          v119 = 0;
          v42 = 4;
          v33 = (float *)&base[17 * v32];
          do
          {
            (((Config *)&v118))->Config::SetSlotValue((__int64)((*v33 - *(float *)(v54 + 128)) / g_ScriptSystemData.m_g_fTimeDelta), (__int64)((v33[2] - *(float *)(v54 + 136)) / g_ScriptSystemData.m_g_fTimeDelta));
            v33 += 3;
            --v42;
          }
          while ( v42 );
          if ( v120 )
            (((RoleSystem *)LODWORD(this->m_partyActor.m_vecPos.z)))->RoleSystem::BuildPathSegment((int *)&v118, 255);
          else
            (((RoleSystem *)LODWORD(this->m_partyActor.m_vecPos.z)))->RoleSystem::BuildPathSegment((int *)&v118, LOBYTE(this->m_partyActor.m_vecRot.x));
          v119 = -1;
          NullCallback(v39);
        }
        break;
      case 26:
        goto LABEL_21;
      case 29:
      case 33:
        v5 = g_ScriptSystemData.m_g_fTimeDelta * 1.5;
        v6 = pMatrix.xlen - v5;
        goto LABEL_11;
      default:
        v5 = g_ScriptSystemData.m_g_fTimeDelta * 1.5;
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
  v15 = 0.0f;
  v16 = 0.0f;
  v17 = 0;
  v18 = 0.0f;
  (*(void ( **)(float, float *))(*(_DWORD *)LODWORD(m_fDirY) + 32))(_pal3_coerce_f32(LODWORD(m_fDirY)), v14);
  pnVala = v16 + p->x;
  v11 = v18 + p->z;
  v12 = v14[0] + p->x;
  v13 = v15 + p->z;
  RolePtr = (((RoleSystem *)*(RoleSystem **)(LODWORD(this->m_partyActor.m_vecPos.z) + 16)))->RoleSystem::GetRolePtr((unsigned __int8)this->m_nRoleSlot);
  v5 = (int *)(__int64)((pnVala - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_g_fTimeDelta);
  nVal = (__int64)((v11 - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta);
  pnVal = (int *)(__int64)((v12 - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_g_fTimeDelta);
  v6 = (__int64)((v13 - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta);
  result = (((PalScriptMgr *)this))->PalScriptMgr::CheckTileCollision(v5, nVal, p);
  if ( result )
  {
    result = (((PalScriptMgr *)this))->PalScriptMgr::CheckTileCollision(pnVal, v6, p);
    if ( result )
    {
      result = (((PalScriptMgr *)this))->PalScriptMgr::CheckTileCollision(v5, v6, p);
      if ( result )
        return (((PalScriptMgr *)this))->PalScriptMgr::CheckTileCollision(pnVal, nVal, p);
    }
  }
  return result;
}

// 0x0042AD40
int RoleSystem::SetActionState(int nVal, char pData)
{
  int result; // eax
  float z; // eax
  int m_nRoleSlot; // [esp-0x10] [ebp-0x14]
LODWORD(this->m_partyActor.m_vecPos.z) = nVal;
  LOBYTE(this->m_partyActor.m_vecRot.x) = pData;
  if ( !_strcmpi((const char *)&this->m_szModelName, a3_0) )
    return 1;
  switch ( this->m_nRoleAction )
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
      this->m_partyActor.m_pEquipAtt2[1] = (RoleAtt *)this->m_nSpawnData;
      (((RoleSystem *)this))->RoleSystem::ProcessAction();
      goto LABEL_5;
    case 0xB:
      (((RoleSystem *)this))->RoleSystem::ProcessAction();
      this->m_bActionState = LODWORD(this->m_fWaypointX) == 1;
      return 1;
    case 0xD:
      (((RoleSystem *)this))->RoleSystem::ProcessAction();
      return 1;
    case 0x11:
      (((RoleSystem *)this))->RoleSystem::ProcessAction();
      result = 1;
      this->m_bActionState = LOBYTE(this->m_fWaypointX);
      return result;
    case 0x16:
      (((RoleSystem *)this))->RoleSystem::ProcessAction();
      result = 1;
      this->m_bActionState = this->m_nInitMoveMode;
      return result;
    case 0x18:
      return 1;
    case 0x19:
      if ( !LODWORD(this->m_fWaypointX) )
      {
LABEL_12:
        (((RoleSystem *)this))->RoleSystem::ProcessAction();
        this->m_bActionState = 0;
      }
      return 1;
    case 0x1C:
      if ( LODWORD(this->m_fWaypointX) == 1 )
      {
        this->m_bActionState = this->m_bActionPause;
        (((RoleSystem *)this))->RoleSystem::ProcessAction();
        if ( !this->m_bActionPause )
        {
          __asm
          {
            fld     dword ptr [esi+0x54]
            fsin
          }
          z = this->m_partyActor.m_vecPos.z;
          m_nRoleSlot = (unsigned __int8)this->m_nRoleSlot;
          __asm
          {
            fadd    _flt_1_0
            fmul    dword ptr [esi+0x0D8]
            fmul    _flt_0_5
            fstp    dword ptr [esi+0x2C]
          }
          *(float *)&this->m_childs.m_nSize = _ET1;
          (((RoleSystem *)*(RoleSystem **)(LODWORD(z) + 16)))->RoleSystem::SetRoleParam(m_nRoleSlot, (float *)&this->m_childs.capacity, 0, 0);
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
      (((RoleSystem *)this))->RoleSystem::ProcessAction();
      this->m_bActionState = 1;
      return 1;
    case 0x1F:
      if ( !_strcmpi(*(const char **)(LODWORD(this->m_partyActor.m_vecPos.z) + 16), "m09") )
        (((RoleSystem *)this))->RoleSystem::SetTileTypeVisible(2, 0);
      return 1;
    case 0x24:
LABEL_5:
      this->m_bActionState = 1;
      goto LABEL_6;
    case 0x25:
      (((PalScriptMgr *)this))->PalScriptMgr::LoadSceneGeometry(g_ScriptSystemData.m_nScriptFlag);
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
  float z; // eax
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
  if ( this->m_partyActor.m_nCloneState )
  {
    v4 = g_pRoleSystem;
    g_pRoleSystem->m_partyActor.m_nState = v2;
    (((RoleSystem *)v4))->RoleSystem::SetMoveSpeed(0.0, 0, v7);
  }
  z = this->m_partyActor.m_vecPos.z;
  this->m_nRoleSlot = v2;
  v6 = (RoleSystem *)*(RoleSystem **)(LODWORD(z) + 16);
  LODWORD(this->m_partyActor.m_vecPos.z) = (unsigned long)(((RoleSystem *)v6))->RoleSystem::NotifyPathEnd(v3);
  this->RoleSystem::ProcessAction();
  LODWORD(this->m_partyActor.m_vecPos.z) = (unsigned long)(((RoleSystem *)v6))->RoleSystem::NotifyPathEnd(v2);
  this->RoleSystem::ProcessAction();
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

  result = (int *)(((RoleSystem *)*(RoleSystem **)(LODWORD(this->m_partyActor.m_vecPos.z) + 16)))->RoleSystem::GetRolePtr(0);
  if ( bVisible )
  {
    for ( i = 0; i < result[39]; ++i )
    {
      v5 = (unsigned long)result[38];
      for ( j = 0; j < v5; ++j )
      {
        v7 = (unsigned long)(result[40] + 8 * (j + i * v5));
        if ( *(unsigned __int8 *)(v7 + 5) == nTileType && *(_BYTE *)(v7 + 4) < 2u )
          *(_BYTE *)(v7 + 4) = 2;
        v5 = (unsigned long)result[38];
      }
    }
  }
  else
  {
    for ( k = 0; k < result[39]; ++k )
    {
      v9 = (unsigned long)result[38];
      for ( m = 0; m < v9; ++m )
      {
        v11 = (unsigned long)(result[40] + 8 * (m + k * v9));
        if ( *(unsigned __int8 *)(v11 + 5) == nTileType && *(_BYTE *)(v11 + 4) >= 2u )
          *(_BYTE *)(v11 + 4) = 0;
        v9 = (unsigned long)result[38];
      }
    }
  }
  return result;
}

// 0x0042D9F0
int RoleSystem::ExecScriptDataCmd(int *p_DWORD)
{
  int *p_m_nCloneFlag1; // ebx
  int v4; // edx
  int v5; // eax
  RoleAtt *v6; // eax
  char *m_nRoleState1; // edi
  int m_nModelParamB; // ecx
  int result; // eax
  void *v10; // esi
  _DWORD *v11; // eax
  float x; // eax
  float v13; // ecx
  int v14; // esi
  float v15; // edx
  unsigned int v16; // eax
  _DWORD *v17; // eax
  float v18; // edx
  float v19; // ecx
  int v20; // edx
  int v21; // edi
  gbVec3D *RoleName; // eax
  gbVec3D *v23; // edi
  float y; // ecx
  float z; // eax
  int v26; // ecx
  float v27; // ecx
  float v28; // eax
  int v29; // ecx
  gbVec3D v30; // [esp+0xC] [ebp-0x5C] BYREF
  int v31; // [esp+0x18] [ebp-0x50]
  _DWORD v32[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v32))->CG_Entry::GetCGEntry();
  p_m_nCloneFlag1 = (int *)&this->m_partyActor.m_nCloneFlag1;
  LOBYTE(v32[0]) = 11;
  v4 = (unsigned long)p_DWORD[1];
  v5 = (unsigned long)p_DWORD[2];
  v32[3] = (unsigned long)*p_DWORD;
  v32[5] = v5;
  v6 = (RoleAtt *)this->m_partyActor.m_pEquipAtt1[0];
  v32[4] = v4;
  if ( !v6
    || (m_nRoleState1 = (char *)this->m_partyActor.m_nRoleState1,
        m_nModelParamB = this->m_partyActor.m_nModelParamB,
        m_nRoleState1 == (char *)m_nModelParamB) )
  {
    v10 = (void *)operator new(0xFBCu);
    if ( p_m_nCloneFlag1[11] )
    {
      v16 = (unsigned long)p_m_nCloneFlag1[8];
      if ( v16 >= p_m_nCloneFlag1[9] + 4 * p_m_nCloneFlag1[10] - 4 )
      {
        v21 = ((int)(v16 - p_m_nCloneFlag1[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nCloneFlag1))->RoleSystem::GetRoleName(2 * v21);
        v23 = (gbVec3D *)((char *)RoleName + 4 * v21);
        LODWORD(v23->x) = (unsigned long)v10;
        (((gbVec3D *)&v30))->gbVec3D::Copy(p_m_nCloneFlag1[3], RoleName);
        y = v30.y;
        p_m_nCloneFlag1[1] = LODWORD(v30.x);
        z = v30.z;
        *((float *)p_m_nCloneFlag1 + 2) = y;
        v26 = v31;
        *((float *)p_m_nCloneFlag1 + 3) = z;
        p_m_nCloneFlag1[4] = v26;
        (((gbVec3D *)&v30))->gbVec3D::Copy((int)v10, v23);
        v27 = v30.y;
        p_m_nCloneFlag1[5] = LODWORD(v30.x);
        v28 = v30.z;
        *((float *)p_m_nCloneFlag1 + 6) = v27;
        v29 = v31;
        *((float *)p_m_nCloneFlag1 + 7) = v28;
        p_m_nCloneFlag1[8] = v29;
      }
      else
      {
        v17 = (_DWORD *)(v16 + 4);
        p_m_nCloneFlag1[8] = (int)v17;
        *v17 = (_DWORD)v10;
        (((gbVec3D *)&v30))->gbVec3D::Copy((int)v10, (gbVec3D *)p_m_nCloneFlag1[8]);
        v18 = v30.y;
        p_m_nCloneFlag1[5] = LODWORD(v30.x);
        v19 = v30.z;
        *((float *)p_m_nCloneFlag1 + 6) = v18;
        v20 = v31;
        *((float *)p_m_nCloneFlag1 + 7) = v19;
        p_m_nCloneFlag1[8] = v20;
      }
    }
    else
    {
      p_m_nCloneFlag1[10] = 2;
      v11 = (_DWORD *)operator new(8u);
      p_m_nCloneFlag1[9] = (int)v11;
      v11[1] = (_DWORD)v10;
      (((gbVec3D *)&v30))->gbVec3D::Copy((int)v10 + 1976, (gbVec3D *)(p_m_nCloneFlag1[9] + 4));
      x = v30.x;
      v13 = v30.y;
      v14 = v31;
      v15 = v30.z;
      p_m_nCloneFlag1[1] = LODWORD(v30.x);
      *((float *)p_m_nCloneFlag1 + 2) = v13;
      *((float *)p_m_nCloneFlag1 + 3) = v15;
      p_m_nCloneFlag1[4] = v14;
      *((float *)p_m_nCloneFlag1 + 5) = x;
      *((float *)p_m_nCloneFlag1 + 6) = v13;
      *((float *)p_m_nCloneFlag1 + 7) = v15;
      p_m_nCloneFlag1[8] = v14;
    }
    m_nRoleState1 = (char *)p_m_nCloneFlag1[7];
    p_m_nCloneFlag1[7] = (int)(m_nRoleState1 + 76);
    if ( !m_nRoleState1 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_partyActor.m_nRoleState1 = (int)(m_nRoleState1 + 76);
  if ( m_nRoleState1 + 76 != (char *)m_nModelParamB )
  {
    if ( !m_nRoleState1 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nCloneFlag1[11] + 1);
      p_m_nCloneFlag1[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nRoleState1, v32, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nRoleState1 )
    qmemcpy(m_nRoleState1, v32, 0x4Cu);
  (((ScriptVM *)p_m_nCloneFlag1))->ScriptVM::GetString();
  result = (int)&this->m_partyActor.m_pEquipAtt1[0]->id + 1;
  this->m_partyActor.m_pEquipAtt1[0] = (RoleAtt *)result;
  return result;
}

// 0x0042DBD0
int RoleSystem::ExecScriptDataA()
{
  RoleAtt *v2; // eax
  int *p_m_nCloneFlag1; // ebx
  char *m_nRoleState1; // edi
  int m_nModelParamB; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // edx
  float v11; // ecx
  int v12; // esi
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // eax
  float v16; // edx
  int v17; // eax
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // edx
  float z; // ecx
  int v23; // edx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  char v27[76]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  v2 = (RoleAtt *)this->m_partyActor.m_pEquipAtt1[0];
  p_m_nCloneFlag1 = (int *)&this->m_partyActor.m_nCloneFlag1;
  v27[0] = 12;
  if ( !v2
    || (m_nRoleState1 = (char *)this->m_partyActor.m_nRoleState1,
        m_nModelParamB = this->m_partyActor.m_nModelParamB,
        m_nRoleState1 == (char *)m_nModelParamB) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nCloneFlag1[11] )
    {
      v13 = (unsigned long)p_m_nCloneFlag1[8];
      if ( v13 >= p_m_nCloneFlag1[9] + 4 * p_m_nCloneFlag1[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nCloneFlag1[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nCloneFlag1))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nCloneFlag1[3], RoleName);
        y = v25.y;
        p_m_nCloneFlag1[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nCloneFlag1 + 2) = y;
        v23 = v26;
        *((float *)p_m_nCloneFlag1 + 3) = z;
        p_m_nCloneFlag1[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nCloneFlag1[5] = (unsigned long)*v20;
        p_m_nCloneFlag1[6] = v24;
        p_m_nCloneFlag1[7] = (int)v7;
        p_m_nCloneFlag1[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nCloneFlag1[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nCloneFlag1[8]);
        v15 = v25.y;
        p_m_nCloneFlag1[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nCloneFlag1 + 6) = v15;
        v17 = v26;
        *((float *)p_m_nCloneFlag1 + 7) = v16;
        p_m_nCloneFlag1[8] = v17;
      }
    }
    else
    {
      p_m_nCloneFlag1[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nCloneFlag1[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nCloneFlag1[9] + 4));
      x = v25.x;
      v10 = v25.z;
      v11 = v25.y;
      v12 = v26;
      p_m_nCloneFlag1[1] = LODWORD(v25.x);
      *((float *)p_m_nCloneFlag1 + 2) = v11;
      *((float *)p_m_nCloneFlag1 + 3) = v10;
      p_m_nCloneFlag1[4] = v12;
      *((float *)p_m_nCloneFlag1 + 5) = x;
      *((float *)p_m_nCloneFlag1 + 6) = v11;
      *((float *)p_m_nCloneFlag1 + 7) = v10;
      p_m_nCloneFlag1[8] = v12;
    }
    m_nRoleState1 = (char *)p_m_nCloneFlag1[7];
    p_m_nCloneFlag1[7] = (int)(m_nRoleState1 + 76);
    if ( !m_nRoleState1 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_partyActor.m_nRoleState1 = (int)(m_nRoleState1 + 76);
  if ( m_nRoleState1 + 76 != (char *)m_nModelParamB )
  {
    if ( !m_nRoleState1 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nCloneFlag1[11] + 1);
      p_m_nCloneFlag1[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nRoleState1, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nRoleState1 )
    qmemcpy(m_nRoleState1, v27, 0x4Cu);
  (((ScriptVM *)p_m_nCloneFlag1))->ScriptVM::GetString();
  result = (int)&this->m_partyActor.m_pEquipAtt1[0]->id + 1;
  this->m_partyActor.m_pEquipAtt1[0] = (RoleAtt *)result;
  return result;
}

// 0x0042DD80
int RoleSystem::ExecScriptDataB()
{
  RoleAtt *v2; // eax
  int *p_m_nCloneFlag1; // ebx
  char *m_nRoleState1; // edi
  int m_nModelParamB; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // edx
  float v11; // ecx
  int v12; // esi
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // eax
  float v16; // edx
  int v17; // eax
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // edx
  float z; // ecx
  int v23; // edx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  char v27[76]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  v2 = (RoleAtt *)this->m_partyActor.m_pEquipAtt1[0];
  p_m_nCloneFlag1 = (int *)&this->m_partyActor.m_nCloneFlag1;
  v27[0] = 13;
  if ( !v2
    || (m_nRoleState1 = (char *)this->m_partyActor.m_nRoleState1,
        m_nModelParamB = this->m_partyActor.m_nModelParamB,
        m_nRoleState1 == (char *)m_nModelParamB) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nCloneFlag1[11] )
    {
      v13 = (unsigned long)p_m_nCloneFlag1[8];
      if ( v13 >= p_m_nCloneFlag1[9] + 4 * p_m_nCloneFlag1[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nCloneFlag1[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nCloneFlag1))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nCloneFlag1[3], RoleName);
        y = v25.y;
        p_m_nCloneFlag1[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nCloneFlag1 + 2) = y;
        v23 = v26;
        *((float *)p_m_nCloneFlag1 + 3) = z;
        p_m_nCloneFlag1[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nCloneFlag1[5] = (unsigned long)*v20;
        p_m_nCloneFlag1[6] = v24;
        p_m_nCloneFlag1[7] = (int)v7;
        p_m_nCloneFlag1[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nCloneFlag1[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nCloneFlag1[8]);
        v15 = v25.y;
        p_m_nCloneFlag1[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nCloneFlag1 + 6) = v15;
        v17 = v26;
        *((float *)p_m_nCloneFlag1 + 7) = v16;
        p_m_nCloneFlag1[8] = v17;
      }
    }
    else
    {
      p_m_nCloneFlag1[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nCloneFlag1[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nCloneFlag1[9] + 4));
      x = v25.x;
      v10 = v25.z;
      v11 = v25.y;
      v12 = v26;
      p_m_nCloneFlag1[1] = LODWORD(v25.x);
      *((float *)p_m_nCloneFlag1 + 2) = v11;
      *((float *)p_m_nCloneFlag1 + 3) = v10;
      p_m_nCloneFlag1[4] = v12;
      *((float *)p_m_nCloneFlag1 + 5) = x;
      *((float *)p_m_nCloneFlag1 + 6) = v11;
      *((float *)p_m_nCloneFlag1 + 7) = v10;
      p_m_nCloneFlag1[8] = v12;
    }
    m_nRoleState1 = (char *)p_m_nCloneFlag1[7];
    p_m_nCloneFlag1[7] = (int)(m_nRoleState1 + 76);
    if ( !m_nRoleState1 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_partyActor.m_nRoleState1 = (int)(m_nRoleState1 + 76);
  if ( m_nRoleState1 + 76 != (char *)m_nModelParamB )
  {
    if ( !m_nRoleState1 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nCloneFlag1[11] + 1);
      p_m_nCloneFlag1[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nRoleState1, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nRoleState1 )
    qmemcpy(m_nRoleState1, v27, 0x4Cu);
  (((ScriptVM *)p_m_nCloneFlag1))->ScriptVM::GetString();
  result = (int)&this->m_partyActor.m_pEquipAtt1[0]->id + 1;
  this->m_partyActor.m_pEquipAtt1[0] = (RoleAtt *)result;
  return result;
}

// 0x0042E870
int RoleSystem::ExecScriptDataIdx(int nVal)
{
  int *p_m_nCloneFlag1; // ebx
  RoleAtt *v4; // eax
  char *m_nRoleState1; // edi
  int m_nModelParamB; // ecx
  int result; // eax
  void *v8; // esi
  _DWORD *v9; // eax
  float x; // eax
  float v11; // ecx
  int v12; // esi
  float v13; // edx
  unsigned int v14; // eax
  _DWORD *v15; // eax
  float v16; // edx
  float v17; // ecx
  int v18; // edx
  int v19; // edi
  gbVec3D *RoleName; // eax
  int *v21; // edi
  float y; // ecx
  float z; // eax
  int v24; // ecx
  int v25; // ecx
  gbVec3D v26; // [esp+0xC] [ebp-0x5C] BYREF
  int v27; // [esp+0x18] [ebp-0x50]
  _DWORD v28[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v28))->CG_Entry::GetCGEntry();
  p_m_nCloneFlag1 = (int *)&this->m_partyActor.m_nCloneFlag1;
  v28[1] = nVal;
  LOBYTE(v28[0]) = 20;
  v4 = (RoleAtt *)this->m_partyActor.m_pEquipAtt1[0];
  v28[2] = 0;
  if ( !v4
    || (m_nRoleState1 = (char *)this->m_partyActor.m_nRoleState1,
        m_nModelParamB = this->m_partyActor.m_nModelParamB,
        m_nRoleState1 == (char *)m_nModelParamB) )
  {
    v8 = (void *)operator new(0xFBCu);
    if ( p_m_nCloneFlag1[11] )
    {
      v14 = (unsigned long)p_m_nCloneFlag1[8];
      if ( v14 >= p_m_nCloneFlag1[9] + 4 * p_m_nCloneFlag1[10] - 4 )
      {
        v19 = ((int)(v14 - p_m_nCloneFlag1[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nCloneFlag1))->RoleSystem::GetRoleName(2 * v19);
        v21 = (int *)(&RoleName->x + v19);
        *v21 = (int)v8;
        (((gbVec3D *)&v26))->gbVec3D::Copy(p_m_nCloneFlag1[3], RoleName);
        y = v26.y;
        p_m_nCloneFlag1[1] = LODWORD(v26.x);
        z = v26.z;
        *((float *)p_m_nCloneFlag1 + 2) = y;
        v24 = v27;
        *((float *)p_m_nCloneFlag1 + 3) = z;
        p_m_nCloneFlag1[4] = v24;
        v25 = (unsigned long)(*v21 + 4028);
        p_m_nCloneFlag1[5] = (unsigned long)*v21;
        p_m_nCloneFlag1[6] = v25;
        p_m_nCloneFlag1[7] = (int)v8;
        p_m_nCloneFlag1[8] = (int)v21;
      }
      else
      {
        v15 = (_DWORD *)(v14 + 4);
        p_m_nCloneFlag1[8] = (int)v15;
        *v15 = (_DWORD)v8;
        (((gbVec3D *)&v26))->gbVec3D::Copy((int)v8, (gbVec3D *)p_m_nCloneFlag1[8]);
        v16 = v26.y;
        p_m_nCloneFlag1[5] = LODWORD(v26.x);
        v17 = v26.z;
        *((float *)p_m_nCloneFlag1 + 6) = v16;
        v18 = v27;
        *((float *)p_m_nCloneFlag1 + 7) = v17;
        p_m_nCloneFlag1[8] = v18;
      }
    }
    else
    {
      p_m_nCloneFlag1[10] = 2;
      v9 = (_DWORD *)operator new(8u);
      p_m_nCloneFlag1[9] = (int)v9;
      v9[1] = (_DWORD)v8;
      (((gbVec3D *)&v26))->gbVec3D::Copy((int)v8 + 1976, (gbVec3D *)(p_m_nCloneFlag1[9] + 4));
      x = v26.x;
      v11 = v26.y;
      v12 = v27;
      v13 = v26.z;
      p_m_nCloneFlag1[1] = LODWORD(v26.x);
      *((float *)p_m_nCloneFlag1 + 2) = v11;
      *((float *)p_m_nCloneFlag1 + 3) = v13;
      p_m_nCloneFlag1[4] = v12;
      *((float *)p_m_nCloneFlag1 + 5) = x;
      *((float *)p_m_nCloneFlag1 + 6) = v11;
      *((float *)p_m_nCloneFlag1 + 7) = v13;
      p_m_nCloneFlag1[8] = v12;
    }
    m_nRoleState1 = (char *)p_m_nCloneFlag1[7];
    p_m_nCloneFlag1[7] = (int)(m_nRoleState1 + 76);
    if ( !m_nRoleState1 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_partyActor.m_nRoleState1 = (int)(m_nRoleState1 + 76);
  if ( m_nRoleState1 + 76 != (char *)m_nModelParamB )
  {
    if ( !m_nRoleState1 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nCloneFlag1[11] + 1);
      p_m_nCloneFlag1[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nRoleState1, v28, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nRoleState1 )
    qmemcpy(m_nRoleState1, v28, 0x4Cu);
  (((ScriptVM *)p_m_nCloneFlag1))->ScriptVM::GetString();
  result = (int)&this->m_partyActor.m_pEquipAtt1[0]->id + 1;
  this->m_partyActor.m_pEquipAtt1[0] = (RoleAtt *)result;
  return result;
}

// 0x0042EA30
int RoleSystem::ExecScriptDataC()
{
  RoleAtt *v2; // eax
  int *p_m_nCloneFlag1; // ebx
  char *m_nRoleState1; // edi
  int m_nModelParamB; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // edx
  float v11; // ecx
  int v12; // esi
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // eax
  float v16; // edx
  int v17; // eax
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // edx
  float z; // ecx
  int v23; // edx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  char v27[76]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  v2 = (RoleAtt *)this->m_partyActor.m_pEquipAtt1[0];
  p_m_nCloneFlag1 = (int *)&this->m_partyActor.m_nCloneFlag1;
  v27[0] = 21;
  if ( !v2
    || (m_nRoleState1 = (char *)this->m_partyActor.m_nRoleState1,
        m_nModelParamB = this->m_partyActor.m_nModelParamB,
        m_nRoleState1 == (char *)m_nModelParamB) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nCloneFlag1[11] )
    {
      v13 = (unsigned long)p_m_nCloneFlag1[8];
      if ( v13 >= p_m_nCloneFlag1[9] + 4 * p_m_nCloneFlag1[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nCloneFlag1[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nCloneFlag1))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nCloneFlag1[3], RoleName);
        y = v25.y;
        p_m_nCloneFlag1[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nCloneFlag1 + 2) = y;
        v23 = v26;
        *((float *)p_m_nCloneFlag1 + 3) = z;
        p_m_nCloneFlag1[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nCloneFlag1[5] = (unsigned long)*v20;
        p_m_nCloneFlag1[6] = v24;
        p_m_nCloneFlag1[7] = (int)v7;
        p_m_nCloneFlag1[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nCloneFlag1[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nCloneFlag1[8]);
        v15 = v25.y;
        p_m_nCloneFlag1[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nCloneFlag1 + 6) = v15;
        v17 = v26;
        *((float *)p_m_nCloneFlag1 + 7) = v16;
        p_m_nCloneFlag1[8] = v17;
      }
    }
    else
    {
      p_m_nCloneFlag1[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nCloneFlag1[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nCloneFlag1[9] + 4));
      x = v25.x;
      v10 = v25.z;
      v11 = v25.y;
      v12 = v26;
      p_m_nCloneFlag1[1] = LODWORD(v25.x);
      *((float *)p_m_nCloneFlag1 + 2) = v11;
      *((float *)p_m_nCloneFlag1 + 3) = v10;
      p_m_nCloneFlag1[4] = v12;
      *((float *)p_m_nCloneFlag1 + 5) = x;
      *((float *)p_m_nCloneFlag1 + 6) = v11;
      *((float *)p_m_nCloneFlag1 + 7) = v10;
      p_m_nCloneFlag1[8] = v12;
    }
    m_nRoleState1 = (char *)p_m_nCloneFlag1[7];
    p_m_nCloneFlag1[7] = (int)(m_nRoleState1 + 76);
    if ( !m_nRoleState1 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_partyActor.m_nRoleState1 = (int)(m_nRoleState1 + 76);
  if ( m_nRoleState1 + 76 != (char *)m_nModelParamB )
  {
    if ( !m_nRoleState1 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nCloneFlag1[11] + 1);
      p_m_nCloneFlag1[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nRoleState1, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nRoleState1 )
    qmemcpy(m_nRoleState1, v27, 0x4Cu);
  (((ScriptVM *)p_m_nCloneFlag1))->ScriptVM::GetString();
  result = (int)&this->m_partyActor.m_pEquipAtt1[0]->id + 1;
  this->m_partyActor.m_pEquipAtt1[0] = (RoleAtt *)result;
  return result;
}

// 0x0044B470
int RoleSystem::ProcessWaypoint()
{
  int m_nPathFlag; // edx
  float m_fDirY; // ecx
  int m_nTodo_074; // eax
  int v5; // edx
  int v6; // edx
  char *m_pPathCurrent; // ecx
  char *a2; // [esp+0x1C] [ebp-0x20] BYREF
  int v10; // [esp+0x20] [ebp-0x1C]
  char *v11; // [esp+0x24] [ebp-0x18]
  int v12; // [esp+0x28] [ebp-0x14]
  char *v13; // [esp+0x2C] [ebp-0x10] BYREF
  int v14; // [esp+0x30] [ebp-0xC]
  char *v15; // [esp+0x34] [ebp-0x8]
  int v16; // [esp+0x38] [ebp-0x4]

  *(&this->dword_17AA450 + 227) = 0;
  *((_BYTE *)&this->dword_17AA450 + 912) = 0;
  (*(void ( **)(int *, int))this->m_nTodo_7C)(&this->m_nTodo_7C, 1);
  m_nPathFlag = this->m_nPathFlag;
  m_fDirY = this->m_fDirY;
  v10 = LODWORD(this->m_fDirZ) + 32;
  m_nTodo_074 = this->m_nTodo_074;
  a2 = (char *)(LODWORD(m_fDirY) - 10);
  v12 = v10 + m_nPathFlag;
  v11 = (char *)(LODWORD(m_fDirY) - 10 + m_nTodo_074);
  (((UIWnd *)this->m_partyActor.m_pEquipAtt2))->UIWnd::sub_445FA0(&a2);
  ((void ( *)(RoleAtt **, int))this->m_partyActor.m_pEquipAtt2[0]->id)(this->m_partyActor.m_pEquipAtt2, 1);
  v14 = v10 + 1;
  v13 = (char *)(a2 + 1);
  v15 = (char *)(a2 + 87);
  v16 = v12 - 1;
  (((UIWnd *)&this->m_partyActor.m_actarray_begin))->UIWnd::sub_445FA0(&v13);
  ((void ( *)(Actor **, int))this->m_partyActor.m_actarray_begin->m_actarray_type)(
    &this->m_partyActor.m_actarray_begin,
    1);
  v5 = this->m_nPathFlag;
  v10 = v12;
  v12 += v5;
  (((UIWnd *)(&this->m_partyActor.m_nUpdateMode + 5)))->UIWnd::sub_445FA0(&a2);
  (**((void ( ***)(int *, int))&this->m_partyActor.m_nUpdateMode + 5))((int *)(&this->m_partyActor.m_nUpdateMode + 5), (int)(1));
  v14 = v10 + 1;
  v13 = (char *)(a2 + 1);
  v15 = (char *)(a2 + 87);
  v16 = v12 - 1;
  (((UIWnd *)&this->m_partyActor.m_nParticleBuffer))->UIWnd::sub_445FA0(&v13);
  (*(void ( **)(int *, int))this->m_partyActor.m_nParticleBuffer)(
    &this->m_partyActor.m_nParticleBuffer,
    1);
  v6 = this->m_nPathFlag;
  v10 = v12;
  v12 += v6;
  (((UIWnd *)&this->m_nTodo_624))->UIWnd::sub_445FA0(&a2);
  (**(void ( ***)(UIWnd *, int))&this->m_nTodo_624)((UIWnd *)(&this->m_nTodo_624), (int)(1));
  v14 = v10 + 1;
  v13 = (char *)(a2 + 1);
  v15 = (char *)(a2 + 87);
  v16 = v12 - 1;
  (((UIWnd *)&this->m_partyActor.m_vecLocalPos))->UIWnd::sub_445FA0(&v13);
  (*(void ( **)(gbVec3D *, int))LODWORD(this->m_partyActor.m_vecLocalPos.x))(
    &this->m_partyActor.m_vecLocalPos,
    1);
  m_pPathCurrent = (char *)this->m_pPathCurrent;
  v10 = v12;
  a2 = (char *)m_pPathCurrent;
  v12 += 11;
  v11 = (char *)(m_pPathCurrent + 68);
  (((UIWnd *)&this->m_pWaypointWnd))->UIWnd::sub_445FA0(&a2);
  (*(void ( **)(UIWnd **, int))this->m_pWaypointWnd)(&this->m_pWaypointWnd, 1);
  return (**(int ( ***)(RoleSystem *, int))((UIWnd *)this))((RoleSystem *)(this), (int)(1));
}

// 0x0044CD90
int RoleSystem::InitUICtrlArray()
{
  int *v2; // ebp
  char *p_m_fActionAssignParam; // esi
  int v4; // eax
  char v5; // al
  int v6; // edx
  int v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  _DWORD *v11; // edx
  int v12; // eax
  int v13; // ecx
  int v15; // [esp+0x0] [ebp-0x24]
  int v16; // [esp+0x10] [ebp-0x14]
  int v17; // [esp+0x14] [ebp-0x10] BYREF
  int v18; // [esp+0x18] [ebp-0xC]
  int v19; // [esp+0x1C] [ebp-0x8]
  int v20; // [esp+0x20] [ebp-0x4]

  v17 = 0;
  v18 = 0;
  v19 = 128;
  v20 = 128;
  UIEmote_InitParticleSlots(v15);
  v2 = (int *)&off_59DD80;
  p_m_fActionAssignParam = (char *)&this[1].m_partyActor.m_fActionAssignParam;
  do
  {
    v4 = (*(int ( **)(char *, _DWORD, int *, RoleSystem *))(*(_DWORD *)p_m_fActionAssignParam + 16))(
           p_m_fActionAssignParam,
           0,
           &v17,
           this);
    if ( (int)v2 < (int)&off_59DDA0 )
    {
      LOBYTE(v4) = g_bSceneLoaded;
      (((UIPushButton *)p_m_fActionAssignParam))->UIPushButton::CreateFromTemplate((void *)*v2, v4);
    }
    else
    {
      v5 = rand();
      LOBYTE(v6) = g_bSceneLoaded;
      v7 = v5 & 7;
      (((UIPushButton *)p_m_fActionAssignParam))->UIPushButton::CreateFromTemplate((void *)*(&off_59DD80 + v7), v6);
      *((_DWORD *)p_m_fActionAssignParam + 43) = this[1].m_partyActor.m_dwMatMsg[52 * v7 + 6];
      *((_DWORD *)p_m_fActionAssignParam + 44) = this[1].m_partyActor.m_dwMatMsg[52 * v7 + 7];
    }
    *((float *)p_m_fActionAssignParam + 46) = (float)(rand() % 255);
    ++v2;
    v8 = rand() % 10;
    v9 = v17;
    v10 = v18;
    v16 = v8 + 10;
    v11 = (_DWORD *)p_m_fActionAssignParam + 152;
    p_m_fActionAssignParam += 208;
    *((float *)p_m_fActionAssignParam - 5) = (double)v16 * 0.1;
    *(p_m_fActionAssignParam - 16) = 1;
    *v11 = v9;
    v12 = v19;
    v11[1] = v10;
    v13 = v20;
    v11[2] = v12;
    v11[3] = v13;
  }
  while ( (int)v2 < (int)&off_59DDA8 );
  return this->RoleSystem::InitRandomParticles();
}

// 0x0044D380
int RoleSystem::InitRandomParticles()
{
  DWORD Time; // eax
  unsigned int *v3; // esi
  int v4; // ebp
  int result; // eax
  int v6; // [esp+0xC] [ebp-0x4]

  Time = timeGetTime();
  CRT_set_new_handler(Time);
  v3 = (unsigned int *)&this[1].m_partyActor.m_dwMatMsg[6];
  v4 = 10;
  do
  {
    *(v3 - 4) = rand() % 40 + 70;
    v6 = rand() % 500 + 150;
    *(v3 - 5) = v6;
    *((float *)v3 - 1) = (float)v6;
    *(v3 - 3) = *v3 + *(v3 - 5);
    *(v3 - 2) = *(v3 - 4) + v3[1];
    *((float *)v3 + 2) = (double)(rand() % 16) * 0.1 + 1.0;
    *((float *)v3 + 3) = (float)(rand() % 255);
    *((float *)v3 + 4) = (double)(rand() % 10 + 10) * 0.1;
    *((_BYTE *)v3 + 20) = 1;
    result = (((UIWnd *)(v3 - 43)))->UIWnd::sub_445FA0(v3 - 5);
    v3 += 52;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x005110B0
void RoleSystem::SetColor(int nColor)
{
  gbDynVertBuf *DynVertBuf; // eax
  float m_fMatrixF; // edx

  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x15u);
  m_fMatrixF = this->m_partyActor.m_fMatrixF;
  BYTE2(this->m_partyActor.m_pEquipAtt2[0]) = -1;
  BYTE1(this->m_partyActor.m_pEquipAtt2[0]) = -1;
  LOBYTE(this->m_partyActor.m_pEquipAtt2[0]) = -1;
  HIBYTE(this->m_partyActor.m_pEquipAtt2[0]) = nColor;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&this->m_partyActor.m_nCloneParamB, 1, (gbRenderEffect *)LODWORD(this->m_partyActor.m_fMatrixParamB), (gbTextureArray *)LODWORD(m_fMatrixF));
}

// 0x00531D20
void RoleSystem::_todo_531D20()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  this->m_bVisFlag = 0;
  this->m_nVisState = 0;
  this->m_nSavedState = 0;
  (((UIFrameContainer *)&this->m_pWndFrame))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_FrameA))->UIFrameContainer::ResetContainerState();
  LOBYTE(this->m_partyUI3.m_rect.left) = 0;
  this->m_partyUI3.m_id = 0;
  this->m_partyUI3.m_wndcolor.Color = 0;
  ((UIRoleDialog *)&this->m_partyUI3.m_rect.top)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this->m_teamData3[289])->UIRoleDialog::UIRoleDialog();
  (((UIFrameContainer *)(&this->dword_17AA450 + 194)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->dword_17AA450 + 232)))->UIFrameContainer::ResetContainerState();
  *((_BYTE *)&this->dword_17AA450 + 1088) = 0;
  *(&this->dword_17AA450 + 271) = 0;
  *(&this->dword_17AA450 + 270) = 0;
  this->m_nMovement = 0.0f;
  *((_BYTE *)&this->dword_17AA450 + 1094) = 1;
}

// 0x00531E70
RoleSystem::~RoleSystem()
{
  (((UIFrameContainer *)(&this->dword_17AA450 + 232)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(&this->dword_17AA450 + 194)))->UIFrameContainer::~UIFrameContainer();
  (((UIRoleDialog *)&this->m_teamData3[289]))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)&this->m_partyUI3.m_rect.top))->UIRoleDialog::~UIRoleDialog();
  (((UIFrameContainer *)&this->m_FrameA))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_pWndFrame))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x00532360
int RoleSystem::ApplyRotationAxis(int nVal, char pData)
{
  int m_fRotAxisZ_low; // ecx
  int result; // eax
  float *p_m_fMovement; // edx
  const char *v7; // edi
  CScreenMode *Instance; // eax
  const void *v9; // [esp-0xC] [ebp-0x18]

  m_fRotAxisZ_low = LODWORD(this->m_fRotAxisZ);
  *((_BYTE *)&this->dword_17AA450 + 1093) = pData;
  result = 0;
  if ( m_fRotAxisZ_low <= 0 )
  {
LABEL_5:
    v7 = (const char *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal) + 4);
    sprintf((char *const)&this->m_fDirZ, "%s%s", byte_DCD03C, v7);
    InputSystem::ProcessFrame((char *)&this->m_fDirZ);
    v9 = off_5F7790;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v9, 1);
    lstrcpyA(&this->m_partyActor.m_szText + 256 * LODWORD(this->m_fRotAxisZ), v7);
    *((_DWORD *)&this->m_fMovement + LODWORD(this->m_fRotAxisZ)) = nVal;
    result = LODWORD(this->m_fRotAxisZ) + 1;
    LODWORD(this->m_fRotAxisZ) = result;
  }
  else
  {
    p_m_fMovement = (float *)&this->m_fMovement;
    while ( *(_DWORD *)p_m_fMovement != nVal )
    {
      ++result;
      ++p_m_fMovement;
      if ( result >= m_fRotAxisZ_low )
        goto LABEL_5;
    }
  }
  return result;
}

// 0x00532410
int RoleSystem::ShowHideUI(char pData)
{
  int m_nMoveParam2; // eax
  float m_fRotAxisZ; // eax
  int v5; // ebp
  int *p_m_fMovement; // ebx
  char v7; // al
  UIWnd *p_m_StaticSlotArray; // edi
  int v9; // ebx
  int result; // eax
  char *lpString2; // [esp+0xC] [ebp-0x214]
  int pConfig; // [esp+0x10] [ebp-0x210] BYREF
  int v13; // [esp+0x14] [ebp-0x20C]
  int SkillNum; // [esp+0x18] [ebp-0x208]
  int v15; // [esp+0x1C] [ebp-0x204]
  CHAR String1[253]; // [esp+0x20] [ebp-0x200] BYREF
  __int16 v17; // [esp+0x11D] [ebp-0x103]
  char v18; // [esp+0x11F] [ebp-0x101]
  CHAR String2[253]; // [esp+0x120] [ebp-0x100] BYREF
  __int16 v20; // [esp+0x21D] [ebp-0x3]
  char v21; // [esp+0x21F] [ebp-0x1]

  memset(String1, 0, sizeof(String1));
  v17 = 0;
  v18 = 0;
  memset(String2, 0, sizeof(String2));
  v20 = 0;
  v21 = 0;
  m_nMoveParam2 = this->m_nMoveParam2;
  v15 = 100 * LODWORD(this->m_fRotAxisZ) + 30 * m_nMoveParam2;
  if ( m_nMoveParam2 > 0 && pData )
  {
    sprintf(
      (char *const)&this->m_fDirZ,
      "\\n    %s%s\\n\\n    %s\\n",
      (const char *)&dword_DD293C,
      (const char *)&dword_DCEF3C,
      (const char *)&dword_DCF13C);
    m_fRotAxisZ = this->m_fRotAxisZ;
    v5 = 0;
    String1[0] = 0;
    if ( SLODWORD(m_fRotAxisZ) > 0 )
    {
      p_m_fMovement = (int *)&this->m_fMovement;
      lpString2 = (char *)&this->m_partyActor.m_szText;
      do
      {
        v13 = 0;
        SkillNum = 0;
        pConfig = (unsigned long)*p_m_fMovement;
        SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(pConfig);
        v7 = *((_BYTE *)&this->dword_17AA450 + 1093);
        v13 = 1;
        if ( v7 )
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&pConfig);
        lstrcatA(String1, "    ");
        lstrcatA(String1, lpString2);
        lstrcatA(String1, aN);
        ++v5;
        ++p_m_fMovement;
        lpString2 += 256;
      }
      while ( v5 < SLODWORD(this->m_fRotAxisZ) );
    }
    if ( lstrlenA(String1) > 0 )
    {
      lstrcatA((LPSTR)&this->m_fDirZ, String1);
    }
    else
    {
      lstrcatA((LPSTR)&this->m_fDirZ, "       ");
      lstrcatA((LPSTR)&this->m_fDirZ, byte_DC7D3C);
    }
    sprintf(String2, "\\n    %s %d", (const char *)&dword_DCF33C, v15);
    lstrcatA((LPSTR)&this->m_fDirZ, String2);
  }
  else
  {
    sprintf(
      (char *const)&this->m_fDirZ,
      "\\n    %s%s\\n\\n    %s",
      (const char *)&dword_DD293C,
      (const char *)&dword_DCF03C,
      (const char *)&dword_DCF13C);
    lstrcatA((LPSTR)&this->m_fDirZ, "\\n       ");
    lstrcatA((LPSTR)&this->m_fDirZ, byte_DC7D3C);
    sprintf(String2, "\\n    %s %d", (const char *)&dword_DCF33C, 0);
    lstrcatA((LPSTR)&this->m_fDirZ, String2);
  }
  SetEnable((UICaption *)&this->m_teamData3[61]);
  (((UIRoleSelect *)&this->m_partyUI3.m_rect.top))->UIRoleSelect::SetByte(1);
  (**(void ( ***)(UIFrameWnd *, _DWORD))((UIWnd *)&this->m_FrameA))((UIFrameWnd *)(&this->m_FrameA), (_DWORD)(0));
  p_m_StaticSlotArray = (UIWnd *)&this->m_StaticSlotArray;
  v9 = 10;
  do
  {
    (*(void ( **)(int *, _DWORD))p_m_StaticSlotArray[-23].m_childs.m_nSize)(
      &p_m_StaticSlotArray[-23].m_childs.m_nSize,
      0);
    (**(void ( ***)(UIWnd *, _DWORD))p_m_StaticSlotArray)((UIWnd *)(p_m_StaticSlotArray), (_DWORD)(0));
    p_m_StaticSlotArray = (UIWnd *)((char *)p_m_StaticSlotArray + 152);
    --v9;
  }
  while ( v9 );
  (**((void ( ***)(int *, _DWORD))&this->dword_17AA450 + 194))((int *)(&this->dword_17AA450 + 194), (_DWORD)(0));
  result = (**((int ( ***)(int *, _DWORD))&this->dword_17AA450 + 232))((int *)(&this->dword_17AA450 + 232), (_DWORD)(0));
  LOBYTE(this->m_partyUI3.m_fontcolor.Color) = 1;
  return result;
}

// 0x005326A0
int RoleSystem::StartBlinkUI()
{
  void ( **v2)(int *, int); // eax

  v2 = (void ( **)(int *, int))*(&this->dword_17AA450 + 194);
  *((_BYTE *)&this->dword_17AA450 + 773) = 1;
  *((_BYTE *)&this->dword_17AA450 + 1092) = 0;
  (*v2)(&this->dword_17AA450 + 194, 1);
  return (**((int ( ***)(int *, _DWORD))&this->dword_17AA450 + 232))((int *)(&this->dword_17AA450 + 232), (_DWORD)(0));
}

// 0x005326E0
int RoleSystem::StopBlinkUI()
{
  void ( **v2)(int *, _DWORD); // eax

  v2 = (void ( **)(int *, _DWORD))*(&this->dword_17AA450 + 194);
  *((_BYTE *)&this->dword_17AA450 + 773) = 0;
  (*v2)(&this->dword_17AA450 + 194, 0);
  return (**((int ( ***)(int *, _DWORD))&this->dword_17AA450 + 232))((int *)(&this->dword_17AA450 + 232), (_DWORD)(0));
}

// 0x00532710
BOOL RoleSystem::UpdateTimer(int nVal, int nVal2)
{
  int v3; // edi
  DWORD TickCount; // eax
  DWORD v6; // eax
  int v7; // ebp
  DWORD v8; // eax
  DWORD v9; // eax
  int m_nVisState; // ebp
  char *m_pWndFrame; // edx
  unsigned __int8 v12; // al
  char m_fAnimParam_high; // al
  DWORD v14; // eax
  DWORD v15; // eax
  unsigned int v16; // ecx
  int v17; // eax
  float m_nMovement; // ecx
  int v20; // [esp+0x0] [ebp-0x8]

  if ( UIParabolaCtrl_GetState(v20) == 2 )
    *((_BYTE *)&this->dword_17AA450 + 772) = 1;
  if ( *((_BYTE *)&this->dword_17AA450 + 772) )
  {
    if ( *((_BYTE *)&this->dword_17AA450 + 773) )
    {
      if ( !*((_BYTE *)&this->dword_17AA450 + 1088) )
      {
        TickCount = GetTickCount();
        *(&this->dword_17AA450 + 270) = TickCount;
        *(&this->dword_17AA450 + 271) = TickCount;
        *((_BYTE *)&this->dword_17AA450 + 1088) = 1;
      }
      v6 = GetTickCount();
      v7 = *(&this->dword_17AA450 + 271);
      *(&this->dword_17AA450 + 270) = v6;
      if ( v6 - v7 > 0xA0 )
      {
        *(&this->dword_17AA450 + 271) = v6;
        *((_BYTE *)&this->dword_17AA450 + 1088) = 0;
        (**((void ( ***)(_DWORD))&this->dword_17AA450 + 194))((_DWORD)(*((unsigned __int8 *)&this->dword_17AA450 + 1092)));
        (**((void ( ***)(int *, bool))&this->dword_17AA450 + 232))((int *)(&this->dword_17AA450 + 232), (bool)(*((_BYTE *)&this->dword_17AA450 + 1092) == 0));
        *((_BYTE *)&this->dword_17AA450 + 1092) = *((_BYTE *)&this->dword_17AA450 + 1092) == 0;
      }
    }
    if ( this->m_partyActor.m_bUIFlagA )
    {
      if ( !this->m_bVisFlag )
      {
        v8 = GetTickCount();
        this->m_nSavedState = v8;
        this->m_nVisState = v8;
        this->m_bVisFlag = 1;
      }
      v9 = GetTickCount();
      m_nVisState = this->m_nVisState;
      this->m_nSavedState = v9;
      if ( v9 - m_nVisState <= 0xBB8 )
      {
        if ( this->m_partyActor.m_bUIFlagB )
        {
          v12 = HIBYTE(this->m_partyActor.m_fAnimParam) + 20;
          HIBYTE(this->m_partyActor.m_fAnimParam) = v12;
          if ( v12 >= 0xC8u )
            this->m_partyActor.m_bUIFlagB = 0;
        }
        else
        {
          m_fAnimParam_high = HIBYTE(this->m_partyActor.m_fAnimParam);
          HIBYTE(this->m_partyActor.m_fAnimParam) = m_fAnimParam_high - 20;
          if ( m_fAnimParam_high == 20 )
            this->m_partyActor.m_bUIFlagB = 1;
        }
        AllocObject(&this->m_pWndFrame);
      }
      else
      {
        this->m_nVisState = v9;
        this->m_bVisFlag = 0;
        m_pWndFrame = (char *)this->m_pWndFrame;
        this->m_partyActor.m_bUIFlagA = 0;
        (*(void ( **)(_DWORD))m_pWndFrame)(0);
        HIBYTE(this->m_partyActor.m_fAnimParam) = -56;
      }
    }
    if ( !LOBYTE(this->m_partyUI3.m_fontcolor.Color) )
    {
      if ( !LOBYTE(this->m_partyUI3.m_rect.left) )
      {
        v14 = GetTickCount();
        this->m_partyUI3.m_wndcolor.Color = v14;
        this->m_partyUI3.m_id = v14;
        LOBYTE(this->m_partyUI3.m_rect.left) = 1;
      }
      v15 = GetTickCount();
      v16 = v15 - this->m_partyUI3.m_id;
      this->m_partyUI3.m_wndcolor.Color = v15;
      if ( v16 > 0x3E8 )
      {
        this->m_partyUI3.m_id = v15;
        LOBYTE(this->m_partyUI3.m_rect.left) = 0;
        v17 = this->m_nMoveParam2 - 1;
        this->m_nMoveParam2 = v17;
        if ( v17 <= 0 )
        {
          m_nMovement = this->m_nMovement;
          this->m_nMoveParam2 = 0;
          LOBYTE(this->m_partyUI3.m_fontcolor.Color) = 1;
          UpdateAnimState((Actor *)LODWORD(m_nMovement), 1);
        }
      }
      RoleSystem::ScaleValue(this->m_nMoveParam2, (int *)&this->m_bMoveFlag2, (int *)&this->m_partyUI3);
      (((RoleAtt *)this))->RoleAtt::SwitchPage(*(_DWORD *)&this->m_bMoveFlag2, *(_DWORD *)((UIWnd *)&this->m_partyUI3)) /* [ROWTABLE] */;
    }
    if ( UIParabolaCtrl_GetState(v3) == 2 )
      *(_BYTE *)(LODWORD(this->m_fSavedRotX) + 24) = 1;
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
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
    return HandleDllEntryRoleSystem((HINSTANCE)0x3E8, fdwReason, lpvReserved);
  else
    return this->UIWnd::OnMessage((int)hinstDLL, fdwReason, (int)lpvReserved);
}

// 0x00532C80
void RoleSystem::AdjustHeight(int nVal)
{
  unsigned int RolePtr; // edi
  float v4; // st7

  if ( nVal )
  {
    this->m_fontcolor.Color = nVal;
    *(_DWORD *)((UIWnd *)this) = *(_DWORD *)(nVal + 4);
    RolePtr = (((RoleSystem *)*(RoleSystem **)nVal))->RoleSystem::GetRolePtr(0);
    this->m_wndcolor.Color = RolePtr;
    v4 = (((Scene *)*(_DWORD *)this->m_fontcolor.Color))->Scene::GetTileHeight(0, (__int64)((*(float *)&this->m_childs.m_pData - *(float *)(RolePtr + 128)) / g_fSceneScale), (__int64)((*(float *)&this->m_childs.m_nSize - *(float *)(RolePtr + 136)) / g_fSceneScale), 0)
       + this->m_fStateX;
    *(float *)&this->m_childs.capacity = v4;
    this->m_fStateY = v4;
  }
}

// 0x00532D40
void RoleSystem::NegateStateMode()
{
  *(float *)&this->m_rect.right = -*(float *)&this->m_nStateMode;
}
