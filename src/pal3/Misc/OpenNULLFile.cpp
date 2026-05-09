#include "pal3/gen/OpenNULLFile.h"

// 0x00401F90
// likely UIListBox method (near SetItemOffset)
// write access to const memory has been detected, the output may be wrong!
struct gbVFileSystem *__thiscall sub_401F90(struct gbVFileSystem **this)
{
  struct gbVFileSystem *result; // eax

  result = *this;
  g_pVFileSys = *this;
  return result;
}
