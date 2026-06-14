#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/OpenNULLFile.h"

// 0x00401F90
// write access to const memory has been detected, the output may be wrong!
OpenNULLFile::OpenNULLFile()
{
  g_pVFileSys = this->m_plastsys;
}
