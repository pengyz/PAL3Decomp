#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/OpenSceneFile.h"

// Unnamed globals (extern)
extern unsigned char byte_8AC5D8;
extern int dword_6EBFA0;

// 0x00401DF0
// strings: .cpk
// write access to const memory has been detected, the output may be wrong!
OpenSceneFile::OpenSceneFile(char *String1)
{
  char v4[260]; // [esp+Ch] [ebp-248h] BYREF
  char Buffer[324]; // [esp+110h] [ebp-144h] BYREF

  if ( _strcmpi(String1, byte_8AC5D8) )
  {
    strcpy(byte_8AC5D8, String1);
    if ( dword_6EBFA0 )
      ((gbVFileSystem *)&dword_6EBFA0)->Release();
    strcpy(v4, String1);
    if ( (g_nGameFlags & 2) != 0 )
      strcat(v4, aCpk);
    if ( !((gbVFileSystem *)&dword_6EBFA0)->Init(v4) )
    {
      sprintf(Buffer, "%s%s", Data, v4);
      ((gbVFileSystem *)&dword_6EBFA0)->Init(v4);
    }
    g_pVFileSys = (struct gbVFileSystem *)&dword_6EBFA0;
  this;
  }
  else
  {
    g_pVFileSys = (struct gbVFileSystem *)&dword_6EBFA0;
  this;
  }
}
