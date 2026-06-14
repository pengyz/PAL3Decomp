#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/SoundSystem.h"

// 0x0041ED00
int SoundSystem::Init()
{
  int v1; // edi
  int v2; // esi
  gbSound2DNode *v3; // eax
  gbSound2DNode *v4; // eax
  gbSound2DNode *v5; // eax
  gbSound2DNode *v6; // eax
  int result; // eax
  gbSound2DNode *v8; // ecx
  char Buffer[256]; // [esp+0x14] [ebp-0x10C] BYREF
  int v10; // [esp+0x11C] [ebp-0x4]

  memset(g_pAmbientTable, 0, sizeof(g_pAmbientTable));
  memset(g_pBGMTable, 0, sizeof(g_pBGMTable));
  v1 = 97;
  g_pCurrentBGM = 0;
  v2 = 0;
  do
  {
    sprintf(Buffer, "snd\\we021%c.wav", v1);
    v3 = (gbSound2DNode *)operator new(0x10u);
    v10 = 0;
    if ( v3 )
      // [AUTO-COMMENTED] v4 = ((gbSound2DNode *)v3)->gbSound2DNode();
    else
      v4 = 0;
    v10 = -1;
    g_pAmbientTable[v2] = v4;
    ((gbSound2DNode *)v4)->LoadFromFile(Buffer);
    g_pAmbientTable[v2]->nLoop = 0;
    v5 = (gbSound2DNode *)operator new(0x10u);
    v10 = 1;
    if ( v5 )
      // [AUTO-COMMENTED] v6 = ((gbSound2DNode *)v5)->gbSound2DNode();
    else
      v6 = 0;
    v10 = -1;
    g_pBGMTable[v2] = v6;
    sprintf(Buffer, "snd\\we022%c.wav", v1);
    result = ((gbSound2DNode *)g_pBGMTable[v2])->LoadFromFile(Buffer);
    v8 = g_pBGMTable[v2];
    ++v1;
    ++v2;
    v8->nLoop = 0;
  }
  while ( v1 - 97 < 4 );
  return result;
}
