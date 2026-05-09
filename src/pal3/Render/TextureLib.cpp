#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/TextureLib.h"

// 0x0053F920
char * TextureLib::SetPath(char *path)
{
  char *result; // eax

  result = (char *)lstrlenA(path);
  if ( (int)result > 0 )
  {
    lstrcpyA((LPSTR)this + 12, path);
    result = (char *)lstrlenA((LPCSTR)this + 12);
    if ( *((_BYTE *)this + (_DWORD)result + 11) != 92 )
      return lstrcatA((LPSTR)this + 12, asc_5D41EC);
  }
  return result;
}

// 0x0053F960
char TextureLib::LoadFromFile(char *filename)
{
  struct gbVFile *v2; // eax
  struct gbVFile *v3; // ebp
  size_t FileSize; // esi
  char *v5; // eax
  unsigned int v6; // ecx
  const void *v7; // esi
  TextureLib *v8; // edi
  int v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // ecx
  char *v13; // eax
  char *v14; // esi
  size_t v16; // eax
  size_t v17; // esi
  char *v18; // edi
  TextureLib *v19; // edi
  int v20; // eax
  int v21; // esi
  int v22; // eax
  int v23; // ecx
  char *v24; // eax
  char *v25; // esi
  char *v26; // [esp+8h] [ebp-28h]
  CHAR String2[4]; // [esp+20h] [ebp-10h] BYREF
  TextureLib *v28; // [esp+24h] [ebp-Ch]
  char *String; // [esp+28h] [ebp-8h]
  size_t v30; // [esp+2Ch] [ebp-4h]
  void *Block; // [esp+34h] [ebp+4h]
  char *Blocka; // [esp+34h] [ebp+4h]

  v28 = this;
  memset(String2, 0, sizeof(String2));
  strncpy(String2, &filename[strlen(filename) - 3], 3u);
  if ( lstrcmpA(lpString1, String2) )
    return 0;
  v2 = g_pVFileSys->OpenFile(filename, 0x201u);
  v3 = v2;
  if ( !v2 )
    return 0;
  if ( *(_DWORD *)&v2[304] )
  {
    FileSize = g_pVFileSys->GetFileSize(v2);
    v30 = FileSize;
    Block = malloc(FileSize);
    v5 = (char *)malloc(FileSize);
    v6 = FileSize;
    v7 = *(const void **)&v3[304];
    String = v5;
    qmemcpy(Block, v7, v6);
    qmemcpy(v5, *(const void **)&v3[304], v6);
    g_pVFileSys->CloseFile(v3);
    v8 = v28;
    v9 = sub_53F610(String);
    v10 = v9;
    if ( v9 )
    {
      v11 = operator new(1088 * v9);
      if ( v11 )
      {
        if ( v10 - 1 >= 0 )
        {
          v12 = v11 + 1060;
          do
          {
            *(_DWORD *)(v12 - 12) = 0;
            *(_DWORD *)(v12 - 8) = 0;
            *(_DWORD *)(v12 - 4) = 0;
            *(_DWORD *)v12 = 0;
            *(_DWORD *)(v12 + 4) = 0;
            *(_DWORD *)(v12 + 8) = 0;
            *(_DWORD *)(v12 + 12) = 0;
            *(_DWORD *)(v12 + 16) = 0;
            *(_BYTE *)(v12 - 1060) = 0;
            *(_BYTE *)(v12 - 548) = 0;
            *(_DWORD *)(v12 - 32) = 256;
            *(_DWORD *)(v12 - 36) = 256;
            *(_DWORD *)(v12 - 24) = 0;
            *(_DWORD *)(v12 - 28) = 0;
            *(_DWORD *)(v12 - 20) = 256;
            *(_DWORD *)(v12 + 20) = 0;
            *(_BYTE *)(v12 + 24) = 0;
            v12 += 1088;
            --v10;
          }
          while ( v10 );
        }
      }
      else
      {
        v11 = 0;
      }
      *((_DWORD *)v8 + 132) = v11;
      v13 = strtok((char *)Block, Delimiter);
      if ( lstrcmpA(v13, aEndfile) )
      {
        do
        {
          v14 = strtok(0, Delimiter);
          (**(void (__thiscall ***)(TextureLib *, char *, char *))v8)(v8, v14, Delimiter);
        }
        while ( lstrcmpA(v14, aEndfile) );
      }
      free(Block);
      free(String);
      *((_BYTE *)v8 + 532) = 1;
      return 1;
    }
    return 0;
  }
  v16 = g_pVFileSys->GetFileSize(v2);
  v17 = v16;
  if ( v16 == -1 || !v16 )
  {
    g_pVFileSys->CloseFile(v3);
    return 0;
  }
  v18 = (char *)operator new(v16);
  String = v18;
  Blocka = (char *)operator new(v17);
  g_pVFileSys->Read(v18, v17, v3);
  g_pVFileSys->CloseFile(v3);
  qmemcpy(Blocka, v18, v17);
  v19 = v28;
  v20 = sub_53F610(Blocka);
  v21 = v20;
  if ( !v20 )
    return 0;
  v22 = operator new(1088 * v20);
  if ( v22 )
  {
    if ( v21 - 1 >= 0 )
    {
      v23 = v22 + 1060;
      do
      {
        *(_DWORD *)(v23 - 12) = 0;
        *(_DWORD *)(v23 - 8) = 0;
        *(_DWORD *)(v23 - 4) = 0;
        *(_DWORD *)v23 = 0;
        *(_DWORD *)(v23 + 4) = 0;
        *(_DWORD *)(v23 + 8) = 0;
        *(_DWORD *)(v23 + 12) = 0;
        *(_DWORD *)(v23 + 16) = 0;
        *(_BYTE *)(v23 - 1060) = 0;
        *(_BYTE *)(v23 - 548) = 0;
        *(_DWORD *)(v23 - 32) = 256;
        *(_DWORD *)(v23 - 36) = 256;
        *(_DWORD *)(v23 - 24) = 0;
        *(_DWORD *)(v23 - 28) = 0;
        *(_DWORD *)(v23 - 20) = 256;
        *(_DWORD *)(v23 + 20) = 0;
        *(_BYTE *)(v23 + 24) = 0;
        v23 += 1088;
        --v21;
      }
      while ( v21 );
    }
  }
  else
  {
    v22 = 0;
  }
  v26 = String;
  *((_DWORD *)v19 + 132) = v22;
  v24 = strtok(v26, Delimiter);
  if ( lstrcmpA(v24, aEndfile) )
  {
    do
    {
      v25 = strtok(0, Delimiter);
      (**(void (__thiscall ***)(TextureLib *, char *, char *))v19)(v19, v25, Delimiter);
    }
    while ( lstrcmpA(v25, aEndfile) );
  }
  operator delete(String);
  operator delete(Blocka);
  *((_BYTE *)v28 + 532) = 1;
  return 1;
}
