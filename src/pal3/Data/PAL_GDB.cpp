#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PAL_GDB.h"

// Forward declarations for unnamed functions
int sub_4792D0(...);

// Unnamed globals (extern)
extern char aCombatDataCoul[];
extern char aDProjectPal3Fi[];
extern char aSec1[];
extern unsigned char byte_DC333C;
extern void *off_58B448;

// 0x00457410
char PAL_GDB::LoadLanguage(char *path)
{
  PalScript *v3; // esi
  char *v4; // edi

  v3 = (PalScript *)&this->m_head[805416];
  (PalScript *->LoadFromFile()&this->m_head[805416], path);
  v3->SetDirectory(aSec1);
  if ( v3->HasNext() )
  {
    v4 = byte_DC333C;
    do
    {
      if ( !_strcmpi(off_58B448, v3->m_bLoadSceneScript) )
        break;
      v3->LoadNext();
      strncpy(v4, v3->m_bLoadSceneScript, 0x100u);
      v4 += 256;
    }
    while ( v3->HasNext() );
  }
  this->m_head[805412] = 1;
  return 1;
}

// 0x00478E00
PAL_GDB::PAL_GDB()
{
  struct gbVFile *v2; // eax
  struct gbVFile *v3; // edi
  struct gbVFileSystem *v5; // [esp+84h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+88h] [ebp-80Ch] BYREF
  char ArgList; // [esp+488h] [ebp-40Ch] BYREF
  int v8; // [esp+890h] [ebp-4h]

  OpenBaseFile::OpenBaseFile(&v5);
  v8 = 0;
  v2 = g_pVFileSys->OpenFile("cbdata\\pal3_softstar.gdb", 0x201u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCombatDataCoul, (int)aDProjectPal3Fi, 38),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Read(this, 0xA0u, v3);
  g_pVFileSys->Seek(v3, *((_DWORD *)this + 32), 1);
  g_pVFileSys->Read(this + 40, 852 * *((_DWORD *)this + 33), v3);
  g_pVFileSys->Seek(v3, *((_DWORD *)this + 34), 1);
  g_pVFileSys->Read(this + 42640, 760 * *((_DWORD *)this + 35), v3);
  g_pVFileSys->Seek(v3, *((_DWORD *)this + 36), 1);
  g_pVFileSys->Read(this + 99640, 800 * *((_DWORD *)this + 37), v3);
  g_pVFileSys->Seek(v3, *((_DWORD *)this + 38), 1);
  g_pVFileSys->Read(this + 199640, 632 * *((_DWORD *)this + 39), v3);
  g_pVFileSys->CloseFile(v3);
  v8 = -1;
  OpenNULLFile::OpenNULLFile(&v5);
  return 1;
}

// 0x00478FD0
PAL_GDB::~PAL_GDB(int a2)
{
  int v2; // esi
  int v3; // edx

  if ( !a2 )
    return 0;
  v2 = *((_DWORD *)this + 33);
  *((_DWORD *)this + 201220) = 0;
  if ( v2 <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *((_DWORD *)this + 201220);
    if ( a2 == *(this + 213 * v3 + 40) )
      break;
    *((_DWORD *)this + 201220) = v3 + 1;
    if ( v3 + 1 >= v2 )
      return 0;
  }
  return (int)(this + 213 * *((_DWORD *)this + 201220) + 40);
}

// 0x00479040
int PAL_GDB::GDB_LoadFile()
{
  return *((_DWORD *)this + 33);
}

// 0x00479050
int PAL_GDB::GDB_GetRole(unsigned int a2)
{
  if ( a2 > 0xC8 )
    return 0;
  else
    return *(this + 213 * a2 + 40);
}

// 0x00479080
int PAL_GDB::GDB_GetRoleNum(int a2)
{
  int v2; // edx
  int v3; // eax
  int v4; // eax

  if ( !a2 )
    return 0;
  v2 = *((_DWORD *)this + 35);
  *((_DWORD *)this + 201220) = 0;
  if ( v2 <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *((_DWORD *)this + 201220);
    if ( a2 == *(this + 190 * v3 + 42640) )
      break;
    v4 = v3 + 1;
    *((_DWORD *)this + 201220) = v4;
    if ( v4 >= v2 )
      return 0;
  }
  return (int)(this + 190 * *((_DWORD *)this + 201220) + 42640);
}

// 0x00479130
int PAL_GDB::GDB_GetSkillNum(int a2)
{
  int v2; // esi
  int v3; // eax
  int v4; // eax

  if ( !a2 )
    return 0;
  v2 = *((_DWORD *)this + 37);
  *((_DWORD *)this + 201220) = 0;
  if ( v2 <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *((_DWORD *)this + 201220);
    if ( a2 == *(this + 200 * v3 + 99640) )
      break;
    v4 = v3 + 1;
    *((_DWORD *)this + 201220) = v4;
    if ( v4 >= v2 )
      return 0;
  }
  return (int)(this + 200 * *((_DWORD *)this + 201220) + 99640);
}

// 0x004791A0
int PAL_GDB::GDB_GetSkillID()
{
  return *((_DWORD *)this + 37);
}

// 0x004791E0
int PAL_GDB::GDB_GetItemNum(int a2)
{
  int v2; // edx
  int v3; // eax
  int v4; // eax

  if ( !a2 )
    return 0;
  v2 = *((_DWORD *)this + 39);
  *((_DWORD *)this + 201220) = 0;
  if ( v2 <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *((_DWORD *)this + 201220);
    if ( a2 == *(this + 158 * v3 + 199648) )
      break;
    v4 = v3 + 1;
    *((_DWORD *)this + 201220) = v4;
    if ( v4 >= v2 )
      return 0;
  }
  return (int)(this + 158 * *((_DWORD *)this + 201220) + 199640);
}

// 0x004792C0
// attributes: thunk
int PAL_GDB::GDB_GetComboID()
{
  return sub_4792D0();
}
