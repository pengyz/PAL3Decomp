#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/scAsmDecoder.h"
#include "Role/Actor.h"
#include "Data/CGameData.h"
#include "Scene/CameraCtrl.h"
#include "Scene/CameraSystem.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Script/ScriptSystem.h"
#include "UI/UIWnd.h"
#include "Misc/_Console.h"
#include "Misc/scAsmDecoder.h"
#include "free_functions.h"

// 0x0040E5F0
int scAsmDecoder::Execute(int nVal, char pData)
{
  RoleSystem *v3; // ecx
  int v4; // eax
  scAsmDecoder *v5; // ecx
  int v6; // eax
  ScriptSystem *v7; // ecx

  v3 = g_pRoleSystem;
  g_fEffectTimer = 10.0;
  if ( pData )
  {
    v4 = 2176 * nVal;
    g_RoleSlotBuf.m_teamData3[v4 + 593] = g_pRoleSystem->m_rect.top;
    g_RoleSlotBuf.m_teamData3[v4 + 594] = v3->m_rect.right;
    g_RoleSlotBuf.m_teamData3[v4 + 595] = v3->m_rect.bottom;
    g_RoleSlotBuf.m_teamData3[v4 + 596] = (int)v3->m_pfather;
    g_RoleSlotBuf.m_teamData3[v4 + 597] = (int)v3->m_childs.m_pData;
    g_RoleSlotBuf.m_teamData3[v4 + 598] = v3->m_childs.capacity;
    g_RoleSlotBuf.m_teamData3[v4 + 589] = v3->m_fontcolor.Color;
    g_RoleSlotBuf.m_teamData3[v4 + 590] = v3->m_wndcolor.Color;
    g_RoleSlotBuf.m_teamData3[v4 + 591] = v3->m_id;
    g_RoleSlotBuf.m_teamData3[v4 + 628] = LODWORD(v3->m_fPosX);
    g_RoleSlotBuf.m_teamData3[v4 + 629] = LODWORD(v3->m_fPosY);
    g_RoleSlotBuf.m_teamData3[v4 + 630] = LODWORD(v3->m_fPosZ);
    *(int *)((char *)&dword_C08154 + v4 * 4) = *((_DWORD *)&v3[1].m_partyActor.m_fSpeed + 2);
    *(int *)((char *)&dword_C08158 + v4 * 4) = *((_DWORD *)&v3[1].m_partyActor.m_fSpeed + 3);
    *(int *)((char *)&dword_C0815C + v4 * 4) = LODWORD(v3[1].m_partyActor.m_fAngleDeg);
    g_RoleSlotBuf.m_teamData3[v4 + 625] = v3->m_nDispFontColor;
    g_RoleSlotBuf.m_teamData3[v4 + 626] = v3->m_nDispWndColor;
    g_RoleSlotBuf.m_teamData3[v4 + 627] = v3->m_nTodo_9C;
    *(int *)((char *)&dword_C08150 + v4 * 4) = *((_DWORD *)&v3[1].m_partyActor.m_fSpeed + 1);
    dword_C061D4[v4] = v3->m_partyActor.m_nState;
  }
  *(&g_nUnk61D8 + 2176 * (_DWORD)dword_C10CC8) = 0;
  *(&g_nUnk61D8 + 2176 * nVal) = 1;
  (((RoleSystem *)&g_RoleSlotBuf.m_teamData3[2176 * nVal + 588]))->RoleSystem::Notify();
  CameraSystem::BindToRoleSlot((int)&g_RoleSlotBuf.m_teamData3[2176 * nVal + 588]);
  dword_C10CC8 = (scAsmDecoder *)nVal;
  if ( *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
    (((_Console *)g_pCameraCtrl))->_Console::SetActive((int)&g_RoleSlotBuf.m_teamData3[2176 * nVal + 588]);
  if ( nVal == 1 && g_RoleSystemMain.m_nMoveSubMode == 10 )
  {
    (((ScriptSystem *)&g_RoleSystemMain))->ScriptSystem::UpdatePositions();
    g_fScriptTimeAccum = fDeltaTime;
  }
  if ( (((CGameData *)&g_gamefrm))->CGameData::SetMode(0) )
    UITitle_BBTY_SetRemarkTextures((int)dword_C10CC8);
  v5 = dword_C10CC8;
  if ( dword_C10CC8 == (scAsmDecoder *)2 )
  {
    // [overlay-fix 2026-10-27] C2664: m_nAnimState 被标 char 传 const char*（类型标注错）——待语义修复
    // if ( _strcmpi(unk_C0A360.m_nAnimState, (const char *)&g_pszSceneSlot2) )
    if ( 0 )
    {
      (((Actor *)&unk_C0A608))->Actor::LoadActionSequences((const char *)&g_pszSceneSlot2, 0);
      // [overlay-fix 2026-10-27] C2664: m_nAnimState 被标 char 传 char*（类型标注错）——待语义修复
      // strcpy(unk_C0A360.m_nAnimState, (const char *)&g_pszSceneSlot2);
      (((RoleSystem *)&unk_C0A360))->RoleSystem::UpdateTransform();
    }
    v5 = dword_C10CC8;
  }
  v6 = 0;
  v7 = (ScriptSystem *)(&g_RoleSlotBuf.m_partyActor.m_Actor + 352 * (_DWORD)v5 + 1);
  while ( !*((_BYTE *)&v7->m_nSlotID + v6) )
  {
    if ( ++v6 > 4 )
      return (((ScriptSystem *)v7))->ScriptSystem::RunEvent(31, 0);
  }
  return (((ScriptSystem *)v7))->ScriptSystem::RunEvent(v6, 1);
}
