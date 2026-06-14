#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/OpenBaseFile.h"

// Unnamed globals (extern)
extern int dword_60BDC8;

// 0x00401F50
// write access to const memory has been detected, the output may be wrong!
OpenBaseFile::OpenBaseFile()
{
  this->m_plastsys = g_pVFileSys;
  g_pVFileSys = (gbVFileSystem *)&g_BaseVFileSystem;
}

// 0x00401F70
// write access to const memory has been detected, the output may be wrong!
void OpenBaseFile::_OpenBaseFile()
{
  this->m_plastsys = g_pVFileSys;
  g_pVFileSys = (gbVFileSystem *)dword_60BDC8;
}
