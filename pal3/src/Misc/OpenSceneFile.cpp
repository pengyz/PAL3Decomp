#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/OpenSceneFile.h"

// Unnamed globals (extern)
extern char byte_8AC5D8[1556];

// 0x00401DF0
// write access to const memory has been detected, the output may be wrong!
OpenSceneFile::OpenSceneFile(char *pszPath)
{
  char v2[260]; // [esp+0xC] [ebp-0x248] BYREF
  char Buffer[324]; // [esp+0x110] [ebp-0x144] BYREF

  if ( _strcmpi(pszPath, byte_8AC5D8) )
  {
    strcpy(byte_8AC5D8, pszPath);
    if ( g_VFileSystem )
      ((gbVFileSystem *)&g_VFileSystem)->Release();
    strcpy(v2, pszPath);
    if ( (g_dwGameFlags & 2) != 0 )
      strcat(v2, ".cpk");
    if ( !((gbVFileSystem *)&g_VFileSystem)->Init(v2) )
    {
      sprintf(Buffer, "%s%s", (const char *)&Data, v2);
      ((gbVFileSystem *)&g_VFileSystem)->Init(v2);
    }
    g_pVFileSys = (gbVFileSystem *)&g_VFileSystem;
  }
  else
  {
    g_pVFileSys = (gbVFileSystem *)&g_VFileSystem;
  }
}

// 0x00401F40
// write access to const memory has been detected, the output may be wrong!
void OpenSceneFile::_OpenSceneFile()
{
  g_pVFileSys = (gbVFileSystem *)&g_BaseVFileSystem;
}
