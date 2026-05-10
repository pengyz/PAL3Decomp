#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/SoundSystem.h"

// 0x0041ED00
int sub_41ED00()
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

  memset(MEMORY[0xC113C0], 0, sizeof(MEMORY[0xC113C0]));
  memset(MEMORY[0xC11360], 0, sizeof(MEMORY[0xC11360]));
  v0 = 97;
  MEMORY[0xC116F4] = 0;
  v1 = 0;
  do
  {
    sprintf(Buffer, "snd\\we021%c.wav", v0);
    v2 = (gbSound2DNode *)operator new(0x10u);
    v9 = 0;
    if ( v2 )
      v3 = v2->gbSound2DNode();
    else
      v3 = 0;
    v9 = -1;
    MEMORY[0xC113C0][v1] = (int)v3;
    v3->LoadFromFile(Buffer);
    *(_DWORD *)(MEMORY[0xC113C0][v1] + 8) = 0;
    v4 = (gbSound2DNode *)operator new(0x10u);
    v9 = 1;
    if ( v4 )
      v5 = v4->gbSound2DNode();
    else
      v5 = 0;
    v9 = -1;
    MEMORY[0xC11360][v1] = (int)v5;
    sprintf(Buffer, "snd\\we022%c.wav", v0);
    result = (gbSound2DNode *->LoadFromFile()MEMORY[0xC11360][v1], Buffer);
    v7 = MEMORY[0xC11360][v1];
    ++v0;
    ++v1;
    *(_DWORD *)(v7 + 8) = 0;
  }
  while ( v0 - 97 < 4 );
  return result;
}
