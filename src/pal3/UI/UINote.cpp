#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UINote.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_445ED0(...);
int sub_445F60(...);

// 0x004450A0
void * UINote::Create(int id, int a3, int a4, char *tex)
{
  int v6; // esi
  struct gbVFileSystem *v8; // [esp+10h] [ebp-110h] BYREF
  char Buffer[256]; // [esp+14h] [ebp-10Ch] BYREF
  int v10; // [esp+11Ch] [ebp-4h]

  UIWnd::Create((UIWnd *)this, id, (void *)a3, a4);
  OpenBaseFile::OpenBaseFile(&v8);
  v6 = 0;
  v10 = 0;
  do
  {
    sprintf(Buffer, "%s%d.tga", tex, v6);
    sub_445ED0();
    ++v6;
  }
  while ( v6 < 9 );
  *(_DWORD *)&this->UIWnd[184] = *(_DWORD *)(sub_445F60(&this->UIWnd[104], 0) + 24);
  *(_DWORD *)&this->UIWnd[172] = 0;
  *(_DWORD *)&this->UIWnd[56] = 0;
  v10 = -1;
  return OpenNULLFile::OpenNULLFile(&v8);
}
