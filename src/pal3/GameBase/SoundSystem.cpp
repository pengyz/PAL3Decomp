#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/SoundSystem.h"

// 0x0041ED00
int SoundSystem::Init()
{
  int v0; // edi
  int v1; // esi
  gbSound2DNode *v2; // eax
  gbSound2DNode *v3; // eax
  gbSound2DNode *v4; // eax
  gbSound2DNode *v5; // eax
  int result; // eax
  int v7; // ecx
  char Buffer[256]; // [esp+14h] [ebp-10Ch] BYREF
  int v9; // [esp+11Ch] [ebp-4h]

  memset(g_SceneMgr.m_npc[6].m_npcinfo.mid, 0, 0x60u);
  memset(&g_SceneMgr.m_npc[6].m_npcinfo.name[16], 0, 0x60u);
  v0 = 97;
  *(_DWORD *)&g_SceneMgr.m_npc[6].m_actor.m_szTexture[140] = 0;
  v1 = 0;
  do
  {
    sprintf(Buffer, "snd\\we021%c.wav", v0);
    v2 = (gbSound2DNode *)((operator *)0x10u)->new();
    v9 = 0;
    if ( v2 )
      v3 = (gbSound2DNode *)v2->gbSound2DNode();
    else
      v3 = 0;
    v9 = -1;
    g_SceneMgr.m_npc[6].m_npcinfo.mid[v1] = (__int32)v3;
    v3->LoadFromFile(Buffer);
    *(_DWORD *)(g_SceneMgr.m_npc[6].m_npcinfo.mid[v1] + 8) = 0;
    v4 = (gbSound2DNode *)((operator *)0x10u)->new();
    v9 = 1;
    if ( v4 )
      v5 = (gbSound2DNode *)v4->gbSound2DNode();
    else
      v5 = 0;
    v9 = -1;
    *(_DWORD *)&g_SceneMgr.m_npc[6].m_npcinfo.name[v1 * 4 + 16] = v5;
    sprintf(Buffer, "snd\\we022%c.wav", v0);
    result = ((gbSound2DNode *)*(gbSound2DNode **)&g_SceneMgr.m_npc[6].m_npcinfo.name[v1 * 4 + 16])->LoadFromFile(Buffer);
    v7 = *(_DWORD *)&g_SceneMgr.m_npc[6].m_npcinfo.name[v1 * 4 + 16];
    ++v0;
    ++v1;
    *(_DWORD *)(v7 + 8) = 0;
  }
  while ( v0 - 97 < 4 );
  return result;
}
