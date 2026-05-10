#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/OpenBaseFile.h"

// Forward declarations for unnamed functions
int sub_401F50(...);
int sub_401F70(...);

// Unnamed globals (extern)
extern int dword_7CC178;
extern int unk_60BDC8;

// 0x00401F50
// likely UIListBox method (near SetItemOffset)
// write access to const memory has been detected, the output may be wrong!
_DWORD *sub_401F50(_DWORD *this)
{
  *this = g_pVFileSys;
  g_pVFileSys = (struct gbVFileSystem *)&dword_7CC178;
  return this;
}

// 0x00401F70
// write access to const memory has been detected, the output may be wrong!
_DWORD *sub_401F70(_DWORD *this)
{
  *this = g_pVFileSys;
  g_pVFileSys = (struct gbVFileSystem *)&unk_60BDC8;
  return this;
}
