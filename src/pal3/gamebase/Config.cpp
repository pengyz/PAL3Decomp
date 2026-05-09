#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Config.h"

// 0x0042FDA0
int Config::ReadINIInt(char *filename, char *key)
{
  memset(this, 0, 0x104u);
  return (int)this;
}

// 0x0042FDC0
char * Config::ReadINIString(char *filename, char *key)
{
  return (char *)sprintf((char *const)this, "%s\\%s", Filename, filename);
}

// 0x0042FDE0
bool Config::ReadINI(char *filename, char *section)
{
  DWORD PrivateProfileStringA; // edi
  int *v5; // [esp+18h] [ebp+Ch]
  int v6; // [esp+1Ch] [ebp+10h]

  PrivateProfileStringA = GetPrivateProfileStringA(filename, section, lpDefault, String, 0xFFu, (LPCSTR)this);
  if ( !strcmp(String, lpDefault) )
    *v5 = v6;
  else
    *v5 = atoi(String);
  return PrivateProfileStringA < 0xFF;
}
