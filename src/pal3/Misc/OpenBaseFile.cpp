#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/OpenBaseFile.h"

// 0x00401F50
// likely UIListBox method (near SetItemOffset)
// write access to const memory has been detected, the output may be wrong!
_DWORD *__thiscall sub_401F50(_DWORD *this)
{
  *this = g_pVFileSys;
  g_pVFileSys = (struct gbVFileSystem *)&dword_7CC178;
  return this;
}

// 0x00401F70
// write access to const memory has been detected, the output may be wrong!
_DWORD *__thiscall sub_401F70(_DWORD *this)
{
  *this = g_pVFileSys;
  g_pVFileSys = (struct gbVFileSystem *)&unk_60BDC8;
  return this;
}
