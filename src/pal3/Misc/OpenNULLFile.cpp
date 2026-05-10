#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/OpenNULLFile.h"

// 0x00401F90
// likely UIListBox method (near SetItemOffset)
// write access to const memory has been detected, the output may be wrong!
OpenNULLFile::OpenNULLFile()
{
  struct gbVFileSystem *result; // eax

  result = (struct gbVFileSystem *)*this;
  g_pVFileSys = (struct gbVFileSystem *)*this;
  return result;
}
