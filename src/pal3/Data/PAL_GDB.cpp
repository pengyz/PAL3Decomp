#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PAL_GDB.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/PalScript.h"

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

  v3 = (PalScript *)((char *)this + 805416);
  ((PalScript *)((char *)this + 805416))->LoadFromFile(path);
  v3->SetDirectory(aSec1);
  if ( v3->HasNext() )
  {
    v4 = byte_DC333C;
    do
    {
      if ( !_strcmpi(off_58B448, v3->_pad_000) )
        break;
      v3->LoadNext();
      strncpy(v4, v3->_pad_000, 0x100u);
      v4 += 256;
    }
    while ( v3->HasNext() );
  }
  *((_BYTE *)this + 805412) = 1;
  return 1;
}

// 0x00478E00
PAL_GDB::PAL_GDB()
{
  struct gbVFile *v2; // eax
  struct gbVFile *v3; // edi
  OpenBaseFile v5; // [esp+84h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+88h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+488h] [ebp-40Ch] BYREF
  int v8; // [esp+890h] [ebp-4h]

  ((OpenBaseFile *)&v5)->OpenBaseFile();
  v8 = 0;
  v2 = (struct gbVFile *)g_pVFileSys->OpenFile("cbdata\\pal3_softstar.gdb", 0x201u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCombatDataCoul, aDProjectPal3Fi, 38),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Read(this, 0xA0u, v3);
  g_pVFileSys->Seek(v3, this->_d080, 1);
  g_pVFileSys->Read(this->_tail, 852 * this->_d084, v3);
  g_pVFileSys->Seek(v3, this->_d088, 1);
  g_pVFileSys->Read((char *)this + 170560, 760 * this->_d08C, v3);
  g_pVFileSys->Seek(v3, this->_d090, 1);
  g_pVFileSys->Read((char *)this + 398560, 800 * this->_d094, v3);
  g_pVFileSys->Seek(v3, this->_d098, 1);
  g_pVFileSys->Read((char *)this + 798560, 632 * this->_d09C, v3);
  g_pVFileSys->CloseFile(v3);
  v8 = -1;
  ((OpenNULLFile *)&v5)->OpenNULLFile();
  1;
}

// 0x00478FD0
PAL_GDB::~PAL_GDB()
{
  int d084; // esi
  int v3; // edx

  if ( !a2 )
  0;
  d084 = this->_d084;
  *((_DWORD *)this + 201220) = 0;
  if ( d084 <= 0 )
  0;
  while ( 1 )
  {
    v3 = *((_DWORD *)this + 201220);
    if ( a2 == *(_DWORD *)&this->_tail[852 * v3] )
      break;
    *((_DWORD *)this + 201220) = v3 + 1;
    if ( v3 + 1 >= d084 )
  0;
  }
  (int)&this->_tail[852 * *((_DWORD *)this + 201220)];
}

// 0x00479040
int PAL_GDB::GDB_LoadFile()
{
  return this->_d084;
}

// 0x00479050
int PAL_GDB::GDB_GetRole(unsigned int a2)
{
  if ( a2 > 0xC8 )
    return 0;
  else
    return *(_DWORD *)&this->_tail[852 * a2];
}

// 0x00479080
int PAL_GDB::GDB_GetRoleNum(int a2)
{
  int d08C; // edx
  int v3; // eax
  int v4; // eax

  if ( !a2 )
    return 0;
  d08C = this->_d08C;
  *((_DWORD *)this + 201220) = 0;
  if ( d08C <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *((_DWORD *)this + 201220);
    if ( a2 == *((_DWORD *)this + 190 * v3 + 42640) )
      break;
    v4 = v3 + 1;
    *((_DWORD *)this + 201220) = v4;
    if ( v4 >= d08C )
      return 0;
  }
  return (int)this + 760 * *((_DWORD *)this + 201220) + 170560;
}

// 0x00479130
int PAL_GDB::GDB_GetSkillNum(int a2)
{
  int d094; // esi
  int v3; // eax
  int v4; // eax

  if ( !a2 )
    return 0;
  d094 = this->_d094;
  *((_DWORD *)this + 201220) = 0;
  if ( d094 <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *((_DWORD *)this + 201220);
    if ( a2 == *((_DWORD *)this + 200 * v3 + 99640) )
      break;
    v4 = v3 + 1;
    *((_DWORD *)this + 201220) = v4;
    if ( v4 >= d094 )
      return 0;
  }
  return (int)this + 800 * *((_DWORD *)this + 201220) + 398560;
}

// 0x004791A0
int PAL_GDB::GDB_GetSkillID()
{
  return this->_d094;
}

// 0x004791E0
int PAL_GDB::GDB_GetItemNum(int a2)
{
  int d09C; // edx
  int v3; // eax
  int v4; // eax

  if ( !a2 )
    return 0;
  d09C = this->_d09C;
  *((_DWORD *)this + 201220) = 0;
  if ( d09C <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *((_DWORD *)this + 201220);
    if ( a2 == *((_DWORD *)this + 158 * v3 + 199648) )
      break;
    v4 = v3 + 1;
    *((_DWORD *)this + 201220) = v4;
    if ( v4 >= d09C )
      return 0;
  }
  return (int)this + 632 * *((_DWORD *)this + 201220) + 798560;
}

// 0x004792C0
// attributes: thunk
int PAL_GDB::GDB_GetComboID()
{
  return sub_4792D0();
}
