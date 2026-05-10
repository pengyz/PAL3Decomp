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
  OpenBaseFile v8; // [esp+10h] [ebp-110h] BYREF
  char Buffer[256]; // [esp+14h] [ebp-10Ch] BYREF
  int v10; // [esp+11Ch] [ebp-4h]

  ((UIWnd *)this)->Create(id, (void *)a3, a4);
  ((OpenBaseFile *)&v8)->OpenBaseFile();
  v6 = 0;
  v10 = 0;
  do
  {
    sprintf(Buffer, "%s%d.tga", tex, v6);
    sub_445ED0();
    ++v6;
  }
  while ( v6 < 9 );
  *(_DWORD *)&this->m_static[112] = *(_DWORD *)(sub_445F60(&this->m_static[32], 0) + 24);
  *(_DWORD *)&this->m_static[100] = 0;
  *(_DWORD *)&this->_base[56] = 0;
  v10 = -1;
  return ((OpenNULLFile *)&v8)->OpenNULLFile();
}
