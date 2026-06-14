#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/scAsmDecoder.h"

// Forward declarations for unnamed functions
void sub_536D20(Actor *_this, const char *a2, int a3); // from annotations

// Unnamed globals (extern)
extern int dword_C08150[];
extern int dword_C08154[];
extern int dword_C08158[];
extern int dword_C0815C[];
extern RoleSystem stru_C059A0;
extern RoleSystem stru_C0A360;

// 0x0040E5F0
int scAsmDecoder::Execute(int nVal, char pData)
{
  RoleSystem *v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  ScriptSystem *v8; // ecx

  v3 = g_pRoleSystem;
  g_fEffectTimer = 10.0;
  if ( pData )
  {
    v4 = 2176 * nVal;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 - 2] = g_pRoleSystem->m_rect.top;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 - 1] = v3->m_rect.right;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4] = v3->m_rect.bottom;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 1] = (int)v3->m_pfather;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 2] = (int)v3->m_childs.m_pData;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 3] = v3->m_childs.capacity;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 - 6] = v3->m_fontcolor.Color;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 - 5] = v3->m_wndcolor.Color;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 - 4] = (int)v3->m_id;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 33] = LODWORD(v3->m_fPosX);
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 34] = LODWORD(v3->m_fPosY);
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 35] = LODWORD(v3->m_fPosZ);
    dword_C08154[v4] = *(int *)((char *)&v3[1].m_partyUI3._todo_05C + 79);
    dword_C08158[v4] = *(int *)((char *)&v3[1].m_partyUI3._todo_05C + 83);
    dword_C0815C[v4] = *(int *)((char *)&v3[1].m_partyUI3._todo_05C + 87);
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 30] = v3->m_nDispFontColor;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 31] = v3->m_nDispWndColor;
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 32] = v3->m_nField9C;
    dword_C08150[v4] = *(int *)((char *)&v3[1].m_partyUI3._todo_05C + 75);
    ((RoleSystem *)&stru_C059A0)->m_teamSlots[v4 + 150] = *(_DWORD *)v3->m_partyActor.m_szTexture;
  }
  ((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * g_nCurrentRoleSlot + 151] = 0;
  ((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * nVal + 151] = 1;
  ((RoleSystem *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * nVal - 7])->Notify();
  ((CameraSystem *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * nVal - 7])->BindToRoleSlot();
  g_nCurrentRoleSlot = nVal;
  if ( *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
    ((_Console *)g_pCameraCtrl)->SetActive((int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * nVal - 7]);
  if ( nVal == 1 && g_RoleSystemMain.m_FrameA.m_rect.bottom == 10 )
  {
    ((ScriptSystem *)&g_RoleSystemMain)->UpdatePositions();
    g_fScriptTimeAccum = fDeltaTime;
  }
  v5 = ((CGameData *)&g_gamefrm)->SetMode(0);
  if ( v5 )
    ((UITitle_BBTY *)(v5 + 1084))->SetRemarkTextures(g_nCurrentRoleSlot);
  v6 = g_nCurrentRoleSlot;
  if ( g_nCurrentRoleSlot == 2 )
  {
    if ( _strcmpi(&((RoleSystem *)&stru_C0A360)->m_nAnimState, (const char *)&g_pfnUpdateFuncs[2]) )
    {
      sub_536D20((Actor *)&((RoleSystem *)&stru_C0A360)->m_partyActor.m_nActionType, &g_pfnUpdateFuncs[2], 0);
      strcpy(&((RoleSystem *)&stru_C0A360)->m_nAnimState, (const char *)&g_pfnUpdateFuncs[2]);
      ((RoleSystem *)&stru_C0A360)->UpdateTransform();
    }
    v6 = g_nCurrentRoleSlot;
  }
  v7 = 0;
  v8 = (ScriptSystem *)(&Buffer.m_partyActor.m_nActionParam + 1408 * v6);
  while ( !*((_BYTE *)&v8->m_nSlotID + v7) )
  {
    if ( ++v7 > 4 )
      return ((ScriptSystem *)v8)->RunEvent(31, 0);
  }
  return ((ScriptSystem *)v8)->RunEvent(v7, 1);
}
