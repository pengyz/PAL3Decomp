#include "pal3/gen/UICursor.h"

// 0x005417B0
void sub_5417B0()
{
  flt_18952F8 = 12.0 + 12.0;
}

// 0x00541860
UINT sub_541860()
{
  char v0; // bl
  UINT result; // eax
  unsigned __int8 v2; // [esp+8h] [ebp-Ch]
  CHAR RootPathName[8]; // [esp+Ch] [ebp-8h] BYREF

  v0 = 65;
  v2 = 65;
  while ( 1 )
  {
    sprintf(RootPathName, "%c:\\", v2);
    result = GetDriveTypeA(RootPathName);
    if ( result == 5 )
      break;
    v2 = ++v0;
    if ( (unsigned __int8)v0 > 0x5Au )
      return result;
  }
  result = strlen(RootPathName) + 1;
  qmemcpy(Data, RootPathName, result);
  return result;
}

// 0x00541C40
char sub_541C40(CHAR *lpSubKey, LPCSTR lpValueName, LPBYTE lpData)
{
  DWORD cbData; // [esp+0h] [ebp-8h] BYREF
  DWORD Type; // [esp+4h] [ebp-4h] BYREF

  if ( RegOpenKeyExA(HKEY_LOCAL_MACHINE, lpSubKey, 0, 0x20019u, (PHKEY)&lpSubKey) )
  {
    *lpData = 0;
    return 0;
  }
  else
  {
    cbData = 324;
    Type = 1;
    RegQueryValueExA((HKEY)lpSubKey, lpValueName, 0, &Type, lpData, &cbData);
    RegCloseKey((HKEY)lpSubKey);
    return 1;
  }
}

// 0x00541CC0
int sub_541CC0()
{
  gbUpdateCurTime();
  dbl_1895070 = g_CurrentTime;
  return LODWORD(g_CurrentTime);
}
