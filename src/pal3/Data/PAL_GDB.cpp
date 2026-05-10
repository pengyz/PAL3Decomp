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
  OpenBaseFile v5; // [esp+84h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+88h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+488h] [ebp-40Ch] BYREF
  int v8; // [esp+890h] [ebp-4h]

  OpenBaseFile::OpenBaseFile(&v5);
  v8 = 0;
  v2 = (struct gbVFile *)g_pVFileSys->OpenFile("cbdata\\pal3_softstar.gdb", 0x201u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (Logger *->FormatException()ArgList, aCombatDataCoul, aDProjectPal3Fi, 38),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Read(this, 0xA0u, v3);
  g_pVFileSys->Seek(v3, this->m_head.RolePos, 1);
  g_pVFileSys->Read(this->m_RoleData, 852 * this->m_head.RoleNum, v3);
  g_pVFileSys->Seek(v3, this->m_head.SkillPos, 1);
  g_pVFileSys->Read(&this->m_RoleData[175].Remark[292], 760 * this->m_head.SkillNum, v3);
  g_pVFileSys->Seek(v3, this->m_head.ItemPos, 1);
  g_pVFileSys->Read(&this->m_SkillData[235].att[3], 800 * this->m_head.ItemNum, v3);
  g_pVFileSys->Seek(v3, this->m_head.ComboPos, 1);
  g_pVFileSys->Read(&this->m_ItemData[353].desc[388], 632 * this->m_head.ComboNum, v3);
  g_pVFileSys->CloseFile(v3);
  v8 = -1;
  (OpenNULLFile **->OpenNULLFile()&v5);
  return 1;
}

// 0x00478FD0
PAL_GDB::~PAL_GDB(int a2)
{
  int RoleNum; // esi
  __int32 id; // edx

  if ( !a2 )
    return 0;
  RoleNum = this->m_head.RoleNum;
  this->m_ItemData[360].id = 0;
  if ( RoleNum <= 0 )
    return 0;
  while ( 1 )
  {
    id = this->m_ItemData[360].id;
    if ( a2 == *(&this->m_RoleData[0].id + 213 * id) )
      break;
    this->m_ItemData[360].id = id + 1;
    if ( id + 1 >= RoleNum )
      return 0;
  }
  return (int)this->m_RoleData + 852 * this->m_ItemData[360].id;
}

// 0x00479040
int PAL_GDB::GDB_LoadFile()
{
  return this->m_head.RoleNum;
}

// 0x00479050
int PAL_GDB::GDB_GetRole(unsigned int a2)
{
  if ( a2 > 0xC8 )
    return 0;
  else
    return *(&this->m_RoleData[0].id + 213 * a2);
}

// 0x00479080
int PAL_GDB::GDB_GetRoleNum(int a2)
{
  int SkillNum; // edx
  __int32 id; // eax
  __int32 v4; // eax

  if ( !a2 )
    return 0;
  SkillNum = this->m_head.SkillNum;
  this->m_ItemData[360].id = 0;
  if ( SkillNum <= 0 )
    return 0;
  while ( 1 )
  {
    id = this->m_ItemData[360].id;
    if ( a2 == *(_DWORD *)&this->m_RoleData[175].Remark[760 * id + 292] )
      break;
    v4 = id + 1;
    this->m_ItemData[360].id = v4;
    if ( v4 >= SkillNum )
      return 0;
  }
  return (int)&this->m_RoleData[175].Remark[760 * this->m_ItemData[360].id + 292];
}

// 0x00479130
int PAL_GDB::GDB_GetSkillNum(int a2)
{
  int ItemNum; // esi
  __int32 id; // eax
  __int32 v4; // eax

  if ( !a2 )
    return 0;
  ItemNum = this->m_head.ItemNum;
  this->m_ItemData[360].id = 0;
  if ( ItemNum <= 0 )
    return 0;
  while ( 1 )
  {
    id = this->m_ItemData[360].id;
    if ( a2 == this->m_SkillData[235].att[200 * id + 3] )
      break;
    v4 = id + 1;
    this->m_ItemData[360].id = v4;
    if ( v4 >= ItemNum )
      return 0;
  }
  return (int)&this->m_SkillData[235].att[200 * this->m_ItemData[360].id + 3];
}

// 0x004791A0
int PAL_GDB::GDB_GetSkillID()
{
  return this->m_head.ItemNum;
}

// 0x004791E0
int PAL_GDB::GDB_GetItemNum(int a2)
{
  int ComboNum; // edx
  __int32 id; // eax
  __int32 v4; // eax

  if ( !a2 )
    return 0;
  ComboNum = this->m_head.ComboNum;
  this->m_ItemData[360].id = 0;
  if ( ComboNum <= 0 )
    return 0;
  while ( 1 )
  {
    id = this->m_ItemData[360].id;
    if ( a2 == *(_DWORD *)&this->m_ItemData[353].desc[632 * id + 420] )
      break;
    v4 = id + 1;
    this->m_ItemData[360].id = v4;
    if ( v4 >= ComboNum )
      return 0;
  }
  return (int)&this->m_ItemData[353].desc[632 * this->m_ItemData[360].id + 388];
}

// 0x004792C0
// attributes: thunk
int PAL_GDB::GDB_GetComboID()
{
  return sub_4792D0();
}
