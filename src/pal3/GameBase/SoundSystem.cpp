#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/SoundSystem.h"

// Unnamed globals (extern)
extern int dword_C11360;
extern int dword_C113C0;

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

  memset(dword_C113C0, 0, sizeof(dword_C113C0));
  memset(dword_C11360, 0, sizeof(dword_C11360));
  v0 = 97;
  g_pSceneNode = 0;
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
    dword_C113C0[v1] = (int)v3;
    v3->LoadFromFile(Buffer);
    *(_DWORD *)(dword_C113C0[v1] + 8) = 0;
    v4 = (gbSound2DNode *)operator new(0x10u);
    v9 = 1;
    if ( v4 )
      v5 = (gbSound2DNode *)v4->gbSound2DNode();
    else
      v5 = 0;
    v9 = -1;
    dword_C11360[v1] = (int)v5;
    sprintf(Buffer, "snd\\we022%c.wav", v0);
    result = ((gbSound2DNode *)dword_C11360[v1])->LoadFromFile(Buffer);
    v7 = dword_C11360[v1];
    ++v0;
    ++v1;
    *(_DWORD *)(v7 + 8) = 0;
  }
  while ( v0 - 97 < 4 );
  return result;
}
