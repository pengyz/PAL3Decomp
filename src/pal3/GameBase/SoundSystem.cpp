#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/SoundSystem.h"

// Unnamed globals (extern)
extern int dword_C116F4;

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

  memset(&g_SceneMgr._gap_cd10[800], 0, 0x60u);
  memset(&g_SceneMgr._gap_cd10[704], 0, 0x60u);
  v0 = 97;
  dword_C116F4 = 0;
  v1 = 0;
  do
  {
    sprintf(Buffer, "snd\\we021%c.wav", v0);
    v2 = (gbSound2DNode *)operator new(0x10u);
    v9 = 0;
    if ( v2 )
      v3 = (gbSound2DNode *)v2->gbSound2DNode();
    else
      v3 = 0;
    v9 = -1;
    *(_DWORD *)&g_SceneMgr._gap_cd10[v1 + 800] = v3;
    v3->LoadFromFile(Buffer);
    *(_DWORD *)(*(_DWORD *)&g_SceneMgr._gap_cd10[v1 + 800] + 8) = 0;
    v4 = (gbSound2DNode *)operator new(0x10u);
    v9 = 1;
    if ( v4 )
      v5 = (gbSound2DNode *)v4->gbSound2DNode();
    else
      v5 = 0;
    v9 = -1;
    *(_DWORD *)&g_SceneMgr._gap_cd10[v1 + 704] = v5;
    sprintf(Buffer, "snd\\we022%c.wav", v0);
    result = ((gbSound2DNode *)*(gbSound2DNode **)&g_SceneMgr._gap_cd10[v1 + 704])->LoadFromFile(Buffer);
    v7 = *(_DWORD *)&g_SceneMgr._gap_cd10[v1 + 704];
    ++v0;
    v1 += 4;
    *(_DWORD *)(v7 + 8) = 0;
  }
  while ( v0 - 97 < 4 );
  return result;
}
