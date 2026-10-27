#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Data/PAL_GDB.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Role/Actor.h"
#include "Combat/CCBAI.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageCam.h"
#include "Combat/CCBSystem.h"
#include "Scene/Camera.h"
#include "Combat/Combat.h"
#include "GameBase/Logger.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneMgr.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/UICaption.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x00457410
char PAL_GDB::LoadLanguage(char *path)
{
  char *pScriptData; // esi
  char *v4; // edi
  char result; // al

  pScriptData = this->m_ItemData[508].desc.scriptWS.pScriptData;
  (((PalScript *)this->m_ItemData[508].desc.scriptWS.pScriptData))->PalScript::LoadFromFile(path);
  (((PalScript *)pScriptData))->PalScript::SetDirectory("sec1");
  if ( (((PalScript *)pScriptData))->PalScript::HasNext() )
  {
    v4 = Destination;
    do
    {
      if ( !_strcmpi(g_LanguageCode, pScriptData) )
        break;
      (((PalScript *)pScriptData))->PalScript::LoadNext();
      strncpy(v4, pScriptData, 0x100u);
      v4 += 256;
    }
    while ( (((PalScript *)pScriptData))->PalScript::HasNext() );
  }
  result = 1;
  this->m_ItemData[508].desc.scriptWS.bLoaded = 1;
  return result;
}

// 0x00457F00
void PAL_GDB::RefreshSkillNumbers()
{
  char v2; // al
  int v3; // ebx
  int *v4; // edi
  int v5; // ebx
  int *v6; // edi

  if ( this->m_head.str[0] )
  {
    ((PAL_GDB *)((char *)&this->m_RoleData[0].Remark + 362))->PAL_GDB::PAL_GDB();
    if ( v2 )
    {
      v3 = 0;
      if ( this[1].m_RoleData[6].Remark.skillCount.skillCount.nSkillCount1 > 0 )
      {
        v4 = (int *)((char *)&this[1].m_RoleData[8].Remark.skillCount + 194);
        do
        {
          *v4 = (((PAL_GDB *)((char *)&this->m_RoleData[0].Remark + 362)))->PAL_GDB::GDB_GetSkillNum(*(v4 - 400));
          ++v3;
          ++v4;
        }
        while ( v3 < this[1].m_RoleData[6].Remark.skillCount.skillCount.nSkillCount1 );
      }
      v5 = 0;
      if ( this[1].m_RoleData[6].Remark.skillCount.skillCount.nSkillCount2 > 0 )
      {
        v6 = (int *)((char *)&this[1].m_RoleData[9].Remark.skillCount + 142);
        do
        {
          *v6 = (((PAL_GDB *)((char *)&this->m_RoleData[0].Remark + 362)))->PAL_GDB::GDB_GetSkillNum(*(v6 - 400));
          ++v5;
          ++v6;
        }
        while ( v5 < this[1].m_RoleData[6].Remark.skillCount.skillCount.nSkillCount2 );
      }
    }
  }
}

// 0x00478E00
PAL_GDB::PAL_GDB()
{
  gbVFile *v2; // eax
  gbVFile *v3; // edi
  OpenBaseFile v4; // [esp+0x84] [ebp-0x810] BYREF
  char pExceptionObject[1024]; // [esp+0x88] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x488] [ebp-0x40C] BYREF
  int v7; // [esp+0x890] [ebp-0x4]

  v7 = 0;
  v2 = (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::OpenFile("cbdata\\pal3_softstar.gdb", 0x201u);
  v3 = (gbVFile *)v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException("Combat data couldn't found", "D:\\Project\\PAL3\\Fight\\LoadData.cpp", 38),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v2, 0, 1);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(this, 0xA0u, v3);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v3, this->m_head.RolePos, 1);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(this->m_RoleData, 852 * this->m_head.RoleNum, v3);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v3, this->m_head.SkillPos, 1);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(this->m_SkillData, 760 * this->m_head.SkillNum, v3);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v3, this->m_head.ItemPos, 1);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(this->m_ItemData, 800 * this->m_head.ItemNum, v3);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v3, this->m_head.ComboPos, 1);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&this->m_ItemData[500], 632 * this->m_head.ComboNum, v3);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::CloseFile(v3);
  v7 = -1;
  ((OpenNULLFile *)&v4)->OpenNULLFile::OpenNULLFile();
}

// 0x00478FD0
void PAL_GDB::_todo_00478FD0(int nVal)
{
  int RoleNum; // esi
  int v3; // edx

  if ( nVal )
  {
    RoleNum = this->m_head.RoleNum;
    *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
    if ( RoleNum > 0 )
    {
      do
      {
        v3 = *(_DWORD *)&this->m_ItemData[507].fightstate[10];
        if ( nVal == this->m_RoleData[v3].id )
          break;
        *(_DWORD *)&this->m_ItemData[507].fightstate[10] = v3 + 1;
      }
      while ( v3 + 1 < RoleNum );
    }
  }
}

// 0x00479040
bool PAL_GDB::GDB_LoadFile()
{
  return this->m_head.RoleNum;
}

// 0x00479050
int PAL_GDB::GDB_GetRole(unsigned int ID)
{
  if ( ID > 0xC8 )
    return 0;
  else
    return this->m_RoleData[ID].id;
}

// 0x00479080
int PAL_GDB::GDB_GetRoleNum(int nVal)
{
  int SkillNum; // edx
  int v3; // eax
  int v4; // eax

  if ( !nVal )
    return 0;
  SkillNum = this->m_head.SkillNum;
  *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
  if ( SkillNum <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *(_DWORD *)&this->m_ItemData[507].fightstate[10];
    if ( nVal == this->m_SkillData[v3].id )
      break;
    v4 = v3 + 1;
    *(_DWORD *)&this->m_ItemData[507].fightstate[10] = v4;
    if ( v4 >= SkillNum )
      return 0;
  }
  return (int)&this->m_SkillData[*(_DWORD *)&this->m_ItemData[507].fightstate[10]];
}

// 0x00479130
int PAL_GDB::GDB_GetSkillNum(int nVal)
{
  int ItemNum; // esi
  int v3; // eax
  int v4; // eax

  if ( !nVal )
    return 0;
  ItemNum = this->m_head.ItemNum;
  *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
  if ( ItemNum <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *(_DWORD *)&this->m_ItemData[507].fightstate[10];
    if ( nVal == this->m_ItemData[v3].id )
      break;
    v4 = v3 + 1;
    *(_DWORD *)&this->m_ItemData[507].fightstate[10] = v4;
    if ( v4 >= ItemNum )
      return 0;
  }
  return (int)&this->m_ItemData[*(_DWORD *)&this->m_ItemData[507].fightstate[10]];
}

// 0x004791A0
unsigned int PAL_GDB::GDB_GetSkillID()
{
  return this->m_head.ItemNum;
}

// 0x004791B0
int PAL_GDB::GetItemID(unsigned int index)
{
  if ( index > 0x1F4 )
    return 0;
  else
    return this->m_ItemData[index].id;
}

// 0x004791E0
int PAL_GDB::GDB_GetItemNum(int nVal)
{
  int ComboNum; // edx
  int v3; // eax
  int v4; // eax

  if ( !nVal )
    return 0;
  ComboNum = this->m_head.ComboNum;
  *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
  if ( ComboNum <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *(_DWORD *)&this->m_ItemData[507].fightstate[10];
    if ( nVal == *(_DWORD *)&this->m_ItemData[500].name[632 * v3 + 28] )
      break;
    v4 = v3 + 1;
    *(_DWORD *)&this->m_ItemData[507].fightstate[10] = v4;
    if ( v4 >= ComboNum )
      return 0;
  }
  return (int)&this->m_ItemData[500] + 632 * *(_DWORD *)&this->m_ItemData[507].fightstate[10];
}

// 0x004792C0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
unsigned int PAL_GDB::GDB_GetComboID()
{
  return accessor_004792D0();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x0049C2C0
char PAL_GDB::LoadByType(unsigned int dwVal, char pData)
{
  int v4; // ebp
  char v5; // al
  int *v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // ebp
  int i; // edi
  char v11; // al
  int j; // edi
  int v13; // ecx
  char v14; // cl
  char v16; // al
  int k; // edi
  int v18; // [esp+0x10] [ebp-0x1C]
  int nItemID; // [esp+0x14] [ebp-0x18] BYREF
  int v20; // [esp+0x18] [ebp-0x14]
  int v21; // [esp+0x1C] [ebp-0x10]
  char pOut[12]; // [esp+0x20] [ebp-0xC] BYREF

  v4 = 0;
  v5 = *((_BYTE *)&this->m_RoleData[0].Remark + 486);
  nItemID = 0xFFFF;
  v20 = 0;
  v21 = 0;
  v18 = 0;
  if ( !v5 )
  {
    if ( pData )
      *((_BYTE *)&this->m_RoleData[0].Remark + 488) = 1;
    else
      *((_BYTE *)&this->m_RoleData[0].Remark + 488) = 0;
  }
  v6 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, dwVal);
  v7 = (unsigned long)*v6;
  nItemID = (unsigned long)*v6;
  v20 = (unsigned long)v6[1];
  v8 = (unsigned long)v6[2];
  v21 = v8;
  if ( !v8 )
    return 0;
  switch ( *(_DWORD *)((char *)&this->m_RoleData[0].Remark + 474) )
  {
    case 0:
      if ( pData )
      {
        v9 = 0;
        for ( i = 0; i < 5; ++i )
        {
          if ( *((_BYTE *)&this->m_RoleData[0].Remark + i + 455) )
          {
            if ( this->PAL_GDB::IsValidItem((int)&nItemID, i) )
              ++v9;
            v8 = v21;
          }
        }
        if ( v9 <= 0 )
          goto LABEL_74;
      }
      v11 = *(_BYTE *)(v8 + 629);
      if ( v11 != 1 && v11 != 2 )
      {
        if ( !pData )
          goto LABEL_76;
        goto LABEL_74;
      }
      for ( j = 0; j < 5; ++j )
      {
        if ( *((_BYTE *)&this->m_RoleData[0].Remark + j + 455) && this->PAL_GDB::IsValidItem((int)&nItemID, j) )
          ++v18;
      }
      if ( v18 > 0 )
        return 1;
      if ( !pData )
        goto LABEL_71;
      goto LABEL_69;
    case 1:
      if ( v7 == 6408 )
      {
        if ( !pData )
          goto LABEL_76;
LABEL_74:
        sprintf(&this->m_head.str[108], "\\n      %s", &dword_DC9F3C);
LABEL_75:
        SetEnable((UICaption *)((char *)&this->m_RoleData[182].Remark.skillCount + 10));
        (((UIRoleSelect *)((char *)&this->m_RoleData[181].Remark + 406)))->UIRoleSelect::SetByte(1);
LABEL_76:
        if ( !*((_BYTE *)&this->m_RoleData[0].Remark + 486) )
          *((_BYTE *)&this->m_RoleData[0].Remark + 488) = 0;
        return 0;
      }
      v13 = *(_DWORD *)v8;
      if ( *(_DWORD *)v8 == 6427 )
      {
        if ( UIScene::ProcessInput("M22", 0) )
        {
          if ( !pData )
            goto LABEL_76;
          goto LABEL_74;
        }
      }
      else if ( v13 != 6401 && v13 != 6405 )
      {
        v14 = *(_BYTE *)(v8 + 628);
        if ( v14 != 7 && v14 != 8 )
        {
          if ( v14 == 9 )
          {
            if ( !this->PAL_GDB::IsValidItem((int)&nItemID, *(_DWORD *)((char *)&this->m_RoleData[0].Remark + 462)) )
            {
              if ( !pData )
                goto LABEL_76;
              sprintf(&this->m_head.str[108], "\\n   %s", &dword_DD4B3C);
              goto LABEL_75;
            }
            *((_BYTE *)&this->m_RoleData[0].Remark + 488) = 1;
            *((_BYTE *)&this->m_RoleData[0].Remark + 486) = 1;
            return 1;
          }
          if ( v14 != 10 && v14 != 11 )
          {
            if ( v14 != 15
              && !*(_WORD *)(v8 + 754)
              && !*(_WORD *)(v8 + 756)
              && !*(_WORD *)(v8 + 758)
              && !*(_WORD *)(v8 + 760) )
            {
              v16 = *(_BYTE *)(v8 + 629);
              if ( v16 != 1 && v16 != 2 )
              {
                if ( !pData )
                  goto LABEL_76;
                goto LABEL_74;
              }
              for ( k = 0; k < 5; ++k )
              {
                if ( *((_BYTE *)&this->m_RoleData[0].Remark + k + 455) && this->PAL_GDB::IsValidItem((int)&nItemID, k) )
                  ++v4;
              }
              if ( v4 <= 0 )
              {
                if ( !*((_BYTE *)&this->m_RoleData[0].Remark + 486) )
                {
                  *((_BYTE *)&this->m_RoleData[0].Remark + 488) = 0;
                  return 0;
                }
                return 0;
              }
            }
            return 1;
          }
        }
        if ( this->PAL_GDB::IsValidItem((int)&nItemID, *(_DWORD *)((char *)&this->m_RoleData[0].Remark + 462)) )
          return 1;
        if ( pData )
        {
          sprintf(&this->m_head.str[108], "\\n   %s", &dword_DD4B3C);
LABEL_70:
          SetEnable((UICaption *)((char *)&this->m_RoleData[182].Remark.skillCount + 10));
          (((UIRoleSelect *)((char *)&this->m_RoleData[181].Remark + 406)))->UIRoleSelect::SetByte(1);
          goto LABEL_71;
        }
        goto LABEL_71;
      }
      if ( g_ScriptSystemData.m_nGameMode == 2 )
        return 1;
      if ( pData )
      {
LABEL_69:
        sprintf(&this->m_head.str[108], "\\n      %s", &dword_DC9F3C);
        goto LABEL_70;
      }
LABEL_71:
      if ( !*((_BYTE *)&this->m_RoleData[0].Remark + 486) )
      {
        *((_BYTE *)&this->m_RoleData[0].Remark + 488) = 0;
        return 0;
      }
      return 0;
    case 2:
    case 3:
    case 4:
    case 5:
      if ( pData )
        goto LABEL_74;
      goto LABEL_76;
    default:
      return 1;
  }
}

// 0x0049C660
int PAL_GDB::SelectBestTarget(int nVal)
{
  PAL_GDB *v3; // ebx
  int *v4; // eax
  int v5; // edx
  int result; // eax
  char *v7; // esi
  int v8; // edi
  _BYTE *v9; // eax
  unsigned __int8 *v10; // edi
  int v11; // edx
  int v12; // ebx
  _DWORD *v13; // eax
  int *v14; // esi
  __int16 v15; // bp
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  char *v21; // esi
  int v22; // edi
  int v23; // esi
  int v24; // eax
  int *v25; // ecx
  int v26; // eax
  int *v27; // edx
  int v28; // eax
  char v29; // al
  int v30; // esi
  char *v31; // edi
  int a2; // [esp+0x10] [ebp-0x60]
  __int16 *v33; // [esp+0x14] [ebp-0x5C]
  int v34; // [esp+0x18] [ebp-0x58]
  int v35; // [esp+0x1C] [ebp-0x54]
  char *v36; // [esp+0x20] [ebp-0x50]
  __int16 v37; // [esp+0x24] [ebp-0x4C]
  __int16 v38; // [esp+0x28] [ebp-0x48]
  __int16 v39; // [esp+0x2C] [ebp-0x44]
  __int16 v40; // [esp+0x30] [ebp-0x40]
  __int16 v41; // [esp+0x34] [ebp-0x3C]
  int nItemID[2]; // [esp+0x3C] [ebp-0x34] BYREF
  int v44; // [esp+0x44] [ebp-0x2C]
  _DWORD pOut[5]; // [esp+0x48] [ebp-0x28] BYREF
  _DWORD v46[5]; // [esp+0x5C] [ebp-0x14] BYREF
  char nVala; // [esp+0x74] [ebp+0x4]
v4 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, nVal);
  nItemID[0] = (unsigned long)*v4;
  v5 = (unsigned long)v4[1];
  memset(v46, 0, sizeof(v46));
  nItemID[1] = v5;
  v44 = (unsigned long)v4[2];
  memset(pOut, 0, sizeof(pOut));
  a2 = 0;
  v35 = 0;
  nVala = 1;
  *((_BYTE *)&this->m_RoleData[0].Remark + 488) = 1;
  if ( nVal < 0 )
    return -1;
  v7 = (char *)&this->m_RoleData[188].ModelID[22];
  v8 = 5;
  do
  {
    (**(void ( ***)(char *, _DWORD))v7)((char *)(v7), (_DWORD)(0));
    v7 += 4892;
    --v8;
  }
  while ( v8 );
  v9 = (char *)&this->m_RoleData[0].Remark + 455;
  v34 = 0;
  v36 = (char *)&this->m_RoleData[0].Remark + 455;
  v10 = (unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 7;
  v11 = 0;
  do
  {
    if ( *v9 )
    {
      v12 = 0;
      v37 = *(_WORD *)(v44 + 704);
      v38 = *(_WORD *)(v44 + 706);
      v39 = *(_WORD *)(v44 + 700);
      v40 = *(_WORD *)(v44 + 702);
      v41 = *(_WORD *)(v44 + 708);
      v13 = (_DWORD *)&v46[v11];
      v14 = (int *)&v46[v11];
      v33 = (__int16 *)(v44 + 644);
      do
      {
        v15 = *v33;
        if ( *v33 > 0 )
        {
          v14 = (int *)&v46[v11];
          pOut[v11] += *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v12 + v34)
                     - g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v12 + 2 + v34];
          *v13 += v15;
        }
        if ( v37 )
        {
          v14 = (int *)&v46[v11];
          v16 = *(v10 - 1);
          *v13 += v37;
          pOut[v11] += v16;
        }
        if ( v38 )
        {
          v14 = (int *)&v46[v11];
          v17 = (unsigned long)*v10;
          *v13 += v38;
          pOut[v11] += v17;
        }
        if ( v39 )
        {
          v14 = (int *)&v46[v11];
          v18 = *(v10 - 3);
          *v13 += v39;
          pOut[v11] += v18;
        }
        if ( v40 )
        {
          v14 = (int *)&v46[v11];
          v19 = *(v10 - 2);
          *v13 += v40;
          pOut[v11] += v19;
        }
        if ( v41 )
        {
          v14 = (int *)&v46[v11];
          v20 = (unsigned long)v10[1];
          *v13 += v41;
          pOut[v11] += v20;
        }
        if ( *v14 > 0 )
          nVala = 0;
        ++v12;
        ++v33;
      }
      while ( v12 < 12 );
}
    v10 += 1408;
    v9 = (_BYTE *)v36 + 1;
    ++v11;
    ++v36;
    v34 += 352;
  }
  while ( (int)v10 < (int)byte_C061CF );
  if ( nVala )
  {
    v21 = (char *)&this->m_RoleData[188].ModelID[22];
    v22 = 5;
    do
    {
      (**(void ( ***)(char *, _DWORD))v21)((char *)(v21), (_DWORD)(0));
      v21 += 4892;
      --v22;
    }
    while ( v22 );
    *((_BYTE *)&this->m_RoleData[0].Remark + 488) = 0;
    return -2;
  }
  else
  {
    v23 = 0;
    v24 = 0;
    v25 = pOut;
    while ( !*((_BYTE *)&this->m_RoleData[0].Remark + v24 + 455) || *v25 <= 0 )
    {
      ++v24;
      ++v25;
      if ( v24 >= 5 )
        goto LABEL_35;
    }
    v23 = v24;
    v35 = pOut[v24];
LABEL_35:
    v26 = 0;
    v27 = pOut;
    do
    {
      if ( *((_BYTE *)&this->m_RoleData[0].Remark + v26 + 455) && *v27 >= v35 )
      {
        v35 = (unsigned long)*v27;
        a2 = v26;
      }
      ++v26;
      ++v27;
    }
    while ( v26 < 5 );
    v28 = pOut[a2];
    if ( v28 )
    {
      if ( v28 == pOut[v23] )
        a2 = v23;
    }
    else
    {
      a2 = 0;
    }
    v29 = *(_BYTE *)(v44 + 629);
    if ( v29 == 1 )
    {
      if ( (((PAL_GDB *)this))->PAL_GDB::IsValidItem((int)nItemID, a2) )
        (**(void ( ***)(int, int))&this->m_RoleData[188].ModelID[4892 * a2 + 22])((int)((int)&this->m_RoleData[188].ModelID[4892 * a2 + 22]), (int)(1));
      result = a2;
      *((_BYTE *)&this->m_RoleData[0].Remark + 489) = 0;
    }
    else if ( v29 == 2 )
    {
      v30 = 0;
      v31 = (char *)&this->m_RoleData[188].ModelID[22];
      do
      {
        if ( *((_BYTE *)&this->m_RoleData[0].Remark + v30 + 455) && (((PAL_GDB *)this))->PAL_GDB::IsValidItem((int)nItemID, a2) )
          (**(void ( ***)(char *, int))v31)((char *)(v31), (int)(1));
        ++v30;
        v31 += 4892;
      }
      while ( v30 < 5 );
      result = -1;
      *((_BYTE *)&this->m_RoleData[0].Remark + 489) = 1;
    }
    else
    {
      return -3;
    }
  }
  return result;
}

// 0x0049CA70
BOOL PAL_GDB::IsValidItem(int nItemID, int a2)
{
  BOOL result; // eax
  int v4; // ebp
  int v5; // esi
  char v6; // al
  int v7; // esi
  float *v8; // edi
  float *v9; // edx
  int v10; // esi
  float *v11; // edi
  float *v12; // edx
  int v13; // esi
  float *v14; // edi
  float *v15; // edx
  int v16; // esi
  float *v17; // edi
  float *v18; // edx
  int v19; // esi
  float *v20; // edi
  float *v21; // edx
  int v22; // edx
  _BYTE *v23; // ebx
  __int16 *v24; // edi
  int v25; // [esp+0x10] [ebp-0x4]

  result = nItemID;
  v4 = 0;
  v25 = 0;
  if ( *(_DWORD *)nItemID == 6408 )
  {
LABEL_2:
    return 0;
  }
  v5 = *(_DWORD *)(nItemID + 8);
  result = *(_DWORD *)v5;
  if ( *(_DWORD *)v5 == 6427 )
  {
    result = UIScene::ProcessInput("M22", 0);
    if ( result )
    {
      return 0;
    }
    goto LABEL_84;
  }
  if ( result == 6401 || result == 6405 )
  {
LABEL_84:
    result = g_ScriptSystemData.m_nGameMode;
    return g_ScriptSystemData.m_nGameMode == 2;
  }
  v6 = *(_BYTE *)(v5 + 628);
  switch ( v6 )
  {
    case 5:
LABEL_7:
      return 1;
    case 7:
      result = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(306);
      if ( *(_BYTE *)(result + a2 + 572) )
      {
        v7 = 0;
        v8 = (float *)(&g_RoleSlotBuf.m_partyActor.m_fDirZ + 352 * a2);
LABEL_12:
        result = 0;
        v9 = (float *)v8;
        while ( *(_DWORD *)v9 != 306 || !*((_BYTE *)&g_RoleSlotBuf.m_fPathSpeed + 1408 * a2 + 8 * v7 + result) )
        {
          ++result;
          ++v9;
          if ( result >= 8 )
          {
            ++v7;
            v8 += 8;
            if ( v7 < 6 )
              goto LABEL_12;
            return 1;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 8:
      result = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(311);
      if ( *(_BYTE *)(result + a2 + 572) )
      {
        v10 = 0;
        v11 = (float *)(&g_RoleSlotBuf.m_partyActor.m_fDirZ + 352 * a2);
LABEL_22:
        result = 0;
        v12 = (float *)v11;
        while ( *(_DWORD *)v12 != 311 || !*((_BYTE *)&g_RoleSlotBuf.m_fPathSpeed + 1408 * a2 + 8 * v10 + result) )
        {
          ++result;
          ++v12;
          if ( result >= 8 )
          {
            ++v10;
            v11 += 8;
            if ( v10 < 6 )
              goto LABEL_22;
            return 1;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 9:
      result = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(301);
      if ( *(_BYTE *)(result + a2 + 572) )
      {
        v13 = 0;
        v14 = (float *)(&g_RoleSlotBuf.m_partyActor.m_fDirZ + 352 * a2);
LABEL_32:
        result = 0;
        v15 = (float *)v14;
        while ( *(_DWORD *)v15 != 301 || !*((_BYTE *)&g_RoleSlotBuf.m_fPathSpeed + 1408 * a2 + 8 * v13 + result) )
        {
          ++result;
          ++v15;
          if ( result >= 8 )
          {
            ++v13;
            v14 += 8;
            if ( v13 < 6 )
              goto LABEL_32;
            return 1;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 10:
      result = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(316);
      if ( *(_BYTE *)(result + a2 + 572) )
      {
        v16 = 0;
        v17 = (float *)(&g_RoleSlotBuf.m_partyActor.m_fDirZ + 352 * a2);
LABEL_42:
        result = 0;
        v18 = (float *)v17;
        while ( *(_DWORD *)v18 != 316 || !*((_BYTE *)&g_RoleSlotBuf.m_fPathSpeed + 1408 * a2 + 8 * v16 + result) )
        {
          ++result;
          ++v18;
          if ( result >= 8 )
          {
            ++v16;
            v17 += 8;
            if ( v16 < 6 )
              goto LABEL_42;
            return 1;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 11:
      result = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(321);
      if ( *(_BYTE *)(result + a2 + 572) )
      {
        v19 = 0;
        v20 = (float *)(&g_RoleSlotBuf.m_partyActor.m_fDirZ + 352 * a2);
LABEL_52:
        result = 0;
        v21 = (float *)v20;
        while ( *(_DWORD *)v21 != 321 || !*((_BYTE *)&g_RoleSlotBuf.m_fPathSpeed + 1408 * a2 + 8 * v19 + result) )
        {
          ++result;
          ++v21;
          if ( result >= 8 )
          {
            ++v19;
            v20 += 8;
            if ( v19 < 6 )
              goto LABEL_52;
            return 1;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 15:
      LOBYTE(result) = 1;
      break;
    default:
      if ( *(_WORD *)(v5 + 754) || *(_WORD *)(v5 + 756) || *(_WORD *)(v5 + 758) || *(_WORD *)(v5 + 760) )
        goto LABEL_7;
      v22 = 0;
      v23 = (_BYTE *)(v5 + 631);
      v24 = (__int16 *)(v5 + 644);
      do
      {
        if ( *v23 == 3 )
          v25 = ++v4;
        if ( *v24 > 0 )
        {
          v4 = *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * a2 + v22)
             - g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * a2 + 2 + v22]
             + v25;
          v25 = v4;
        }
        ++v22;
        ++v24;
        ++v23;
      }
      while ( v22 < 12 );
      if ( *(_WORD *)(v5 + 704) )
        v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * a2 + 6);
      if ( *(_WORD *)(v5 + 706) )
        v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * a2 + 7);
      if ( *(_WORD *)(v5 + 700) )
        v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * a2 + 4);
      if ( *(_WORD *)(v5 + 702) )
        v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * a2 + 5);
      if ( *(_WORD *)(v5 + 708) )
        v4 += *((unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_nCmdParam + 1408 * a2);
      return v4 > 0;
  }
  return result;
}

// 0x004E50B0
char * PAL_GDB::SetupSkillConfig()
{
  char *result; // eax
  int pConfig[3]; // [esp+0x4] [ebp-0xC] BYREF

  pConfig[0] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GetItemID(index);
  pConfig[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(pConfig[0]);
  pConfig[1] = 1;
  result = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(pConfig);
  LOBYTE(g_bCommandEdited) = 1;
  return result;
}

// 0x004E5500
int PAL_GDB::LoadConfigFromINI()
{
  int result; // eax
  int v3; // ebp
  int v4; // ebx
  char *v5; // edi
  CHAR ReturnedString[256]; // [esp+0x10] [ebp-0x300] BYREF
  CHAR KeyName[256]; // [esp+0x110] [ebp-0x200] BYREF
  CHAR v8[256]; // [esp+0x210] [ebp-0x100] BYREF

  GetPrivateProfileStringA(AppName, ::KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
  result = atoi(ReturnedString);
  v3 = result;
  v4 = 0;
  if ( result > 0 )
  {
    v5 = (char *)&this->m_head.str[12];
    do
    {
      sprintf(KeyName, (const char *)&dir[20], v4);
      GetPrivateProfileStringA(AppName, KeyName, Default, v8, 0xFFu, "datascript\\combatBE.ini");
      sprintf(KeyName, "%sID", v8);
      GetPrivateProfileStringA(AppName, KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
      *((_DWORD *)v5 - 1) = atoi(ReturnedString);
      sprintf(KeyName, "%sHP", v8);
      GetPrivateProfileStringA(AppName, KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
      *(_DWORD *)v5 = atoi(ReturnedString);
      sprintf(KeyName, "%sGP", v8);
      GetPrivateProfileStringA(AppName, KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
      *((_DWORD *)v5 + 1) = atoi(ReturnedString);
      sprintf(KeyName, "%sMP", v8);
      GetPrivateProfileStringA(AppName, KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
      result = atoi(ReturnedString);
      *((_DWORD *)v5 + 2) = result;
      ++v4;
      v5 += 16;
    }
    while ( v4 < v3 );
  }
  return result;
}

// 0x004E56E0
char PAL_GDB::FindItemByID(int nVal, int *p_DWORD)
{
  int v3; // eax
  char *i; // ecx

  v3 = 0;
  for ( i = &this->m_head.str[8]; *(_DWORD *)i != nVal; i += 16 )
  {
    if ( ++v3 >= 500 )
      return 0;
  }
  *p_DWORD = v3;
  return 1;
}

// 0x004E5710
int PAL_GDB::GetItemPrice(int nVal)
{
  int p_DWORD; // [esp+0x8] [ebp-0x4] BYREF

  p_DWORD = -1;
  if ( this->PAL_GDB::FindItemByID(nVal, &p_DWORD) == 1 )
    return *(_DWORD *)&this->m_head.str[16 * p_DWORD + 12];
  else
    return *(__int16 *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal) + 644);
}

// 0x004E5760
int PAL_GDB::GetItemWeight(int nVal)
{
  int p_DWORD; // [esp+0x8] [ebp-0x4] BYREF

  p_DWORD = -1;
  if ( this->PAL_GDB::FindItemByID(nVal, &p_DWORD) == 1 )
    return *(_DWORD *)&this->m_head.str[16 * p_DWORD + 16];
  else
    return *(__int16 *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal) + 646);
}

// 0x004E57B0
int PAL_GDB::GetItemData(int nVal)
{
  int p_DWORD; // [esp+0x8] [ebp-0x4] BYREF

  p_DWORD = -1;
  if ( this->PAL_GDB::FindItemByID(nVal, &p_DWORD) == 1 )
    return *(_DWORD *)&this->m_head.str[16 * p_DWORD + 20];
  else
    return *(__int16 *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal) + 648);
}

// 0x004E5800
int PAL_GDB::PartySetupDialogProc(HWND hDlg, UINT pData, WPARAM a4, LPARAM a5)
{
  HWND DlgItem; // ebp
  HWND v6; // ebx
  char v8; // bl
  int *v9; // eax
  unsigned int v10; // ecx
  LRESULT v11; // eax
  LRESULT v12; // eax
  int v13; // eax
  int Role; // eax
  int v15; // edx
  int *v16; // ecx
  int v17; // eax
  int v18; // eax
  LPARAM lParam[8]; // [esp+0x10] [ebp-0x20] BYREF

  DlgItem = GetDlgItem(hDlg, 1156);
  v6 = GetDlgItem(hDlg, 1155);
  if ( pData == 78 )
  {
    if ( a4 == 1155 )
    {
      if ( *(_DWORD *)(a5 + 8) != -3 )
        return 0;
      v18 = *(_DWORD *)(a5 + 12);
      if ( v18 == -1 )
        return 0;
      if ( v18 < 5 )
      {
        if ( SceneMgr::GetValidPartyCount() > 1 )
        {
          *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + *(_DWORD *)(a5 + 12)) = 0;
          byte_17A994E = 1;
          return 0;
        }
        return 0;
      }
      if ( !*(&g_pRoleSystem + v18) )
        goto LABEL_34;
      *(&g_pRoleSystem + v18) = 0;
      v17 = g_nPartyCount - 1;
    }
    else
    {
      if ( a4 != 1156 )
        return 0;
      if ( *(_DWORD *)(a5 + 8) != -3 )
        return 0;
      v13 = *(_DWORD *)(a5 + 12);
      if ( v13 == -1 )
        return 0;
      if ( v13 < 5 )
      {
        if ( SceneMgr::GetValidPartyCount() < 4 )
        {
          *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + *(_DWORD *)(a5 + 12)) = 1;
          BYTE2(g_RoleSlotBuf.m_nAnimCopy2) = 3;
          *((_BYTE *)&g_RoleSlotBuf.m_teamSlotOverlay.m_state + 1130) = 5;
          BYTE2(g_RoleSlotBuf.m_configData[31]) = 1;
          BYTE2(g_RoleSlotBuf.m_teamData3[219]) = 2;
          *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 534) = 4;
          byte_17A994E = 1;
          return 0;
        }
        return 0;
      }
      Role = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRole(*(_DWORD *)(a5 + 12));
      v15 = 0;
      v16 = g_nPartyRoles;
      while ( *v16 )
      {
        ++v16;
        ++v15;
        if ( (int)v16 >= (int)&g_nPartyCount )
          return 0;
      }
      g_nPartyRoles[v15] = Role;
      v17 = g_nPartyCount + 1;
    }
    g_nPartyCount = v17;
LABEL_34:
    byte_17A994E = 1;
    return 0;
  }
  if ( pData == 272 )
  {
    v11 = SendMessageA(v6, 0x1037u, 0, 0);
    LOBYTE(v11) = v11 | 0x21;
    SendMessageA(v6, 0x1036u, 0, v11);
    v12 = SendMessageA(DlgItem, 0x1037u, 0, 0);
    LOBYTE(v12) = v12 | 0x21;
    SendMessageA(DlgItem, 0x1036u, 0, v12);
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 7;
    lParam[1] = 0;
    lParam[2] = 150;
    lParam[3] = (LPARAM)"Name";
    SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParam);
    lParam[1] = 1;
    lParam[2] = 50;
    lParam[3] = (LPARAM)"Boss";
    SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParam);
    lParam[1] = 1;
    lParam[2] = 60;
    lParam[3] = (LPARAM)"Type";
    SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)lParam);
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 7;
    lParam[1] = 0;
    lParam[2] = 165;
    lParam[3] = (LPARAM)"Name";
    SendMessageA(v6, 0x101Bu, 0, (LPARAM)lParam);
    lParam[1] = 1;
    lParam[2] = 50;
    lParam[3] = (LPARAM)"Boss";
    SendMessageA(v6, 0x101Bu, 1u, (LPARAM)lParam);
    byte_17A994D = 1;
    return 0;
  }
  if ( pData != 273 || (unsigned __int16)a4 != 1 )
    return 0;
  if ( g_nPartyCount )
  {
    do
    {
      v8 = 0;
      v9 = (int *)&g_nPartyRoles[1];
      do
      {
        v10 = *(v9 - 1);
        if ( v10 < *v9 )
        {
          *(v9 - 1) = *v9;
          *v9 = v10;
          v8 = 1;
        }
        ++v9;
      }
      while ( (int)v9 < (int)&g_nPartyCount );
    }
    while ( v8 );
    EndDialog(hDlg, 1);
    g_nActorRenderCount = 0;
    return 0;
  }
  else
  {
    MessageBoxA((HWND)g_todo_BFDA4C, (const char *)&unk_5D8A00, 0, 0);
    return 0;
  }
}

// 0x004E5B20
LRESULT PAL_GDB::RefreshPartyDialog()
{
  HWND DlgItem; // ebp
  HWND v3; // ebx
  int v4; // eax
  signed int v5; // esi
  int Role; // eax
  int v7; // eax
  int v8; // ebx
  char v9; // al
  int v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // esi
  LRESULT result; // eax
  int v15; // [esp+0x10] [ebp-0x34]
  int *v16; // [esp+0x10] [ebp-0x34]
  HWND v17; // [esp+0x14] [ebp-0x30]
  int v18; // [esp+0x14] [ebp-0x30]
  LPARAM lParam[10]; // [esp+0x1C] [ebp-0x28] BYREF

  DlgItem = GetDlgItem((HWND)g_nActorRenderCount, 1156);
  v3 = GetDlgItem((HWND)g_nActorRenderCount, 1155);
  memset(lParam, 0, sizeof(lParam));
  v17 = v3;
  SendMessageA(v3, 0x1009u, 0, 0);
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  LOBYTE(v4) = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_LoadFile();
  v15 = v4;
  this->PAL_GDB::UpdateInventorySlots();
  v5 = 0;
  if ( v15 > 0 )
  {
    do
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
      Role = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRole(v5);
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(Role);
      v8 = v7;
      lParam[1] = v5;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", v7 + 600);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      v9 = *(_BYTE *)(v8 + 518);
      if ( v9 == 98 || v9 == 66 )
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", &off_5D8A3C);
      else
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", g_szCCBStageCamName);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 2;
      switch ( *(_WORD *)(v8 + 4) )
      {
        case 0:
          sprintf((char *const)&g_CCBStageCamBuffer, "%d%s", v5, byte_5D8A30);
          break;
        case 1:
          sprintf((char *const)&g_CCBStageCamBuffer, "%d%s", v5, byte_5D8A2C);
          break;
        case 2:
          sprintf((char *const)&g_CCBStageCamBuffer, "%d%s", v5, byte_5D8A28);
          break;
        case 3:
          sprintf((char *const)&g_CCBStageCamBuffer, "%d%s", v5, byte_5D8A24);
          break;
        case 4:
          sprintf((char *const)&g_CCBStageCamBuffer, "%d%s", v5, byte_5D8A20);
          break;
        case 5:
          sprintf((char *const)&g_CCBStageCamBuffer, "%d%s", v5, byte_5D8A1C);
          break;
        case 6:
          sprintf((char *const)&g_CCBStageCamBuffer, "%d%s", v5, byte_5D8A18);
          break;
        default:
          break;
      }
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v5;
    }
    while ( v5 < v15 );
    v3 = v17;
  }
  v10 = 0;
  v18 = 0;
  v16 = (int *)((char *)&this->m_RoleData[9].Remark.skillCount + 174);
  do
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    v11 = (unsigned long)*v16;
    lParam[1] = v10;
    if ( v11 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(v11);
      v13 = v12;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", v12 + 600);
      SendMessageA(v3, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      if ( *(_DWORD *)(v13 + 772) )
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", &off_5D8A3C);
      else
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", g_szCCBStageCamName);
      result = SendMessageA(v3, 0x1006u, 0, (LPARAM)lParam);
      v10 = v18;
    }
    else
    {
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&unk_5D89B0);
      SendMessageA(v3, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf((char *const)&g_CCBStageCamBuffer, unk_C10D38);
      result = SendMessageA(v3, 0x1006u, 0, (LPARAM)lParam);
    }
    v18 = ++v10;
    ++v16;
  }
  while ( v10 < 11 );
  return result;
}

// 0x004E5E00
int PAL_GDB::PopulateAvailableRoles()
{
  HWND DlgItem; // ebx
  int *v3; // esi
  int v4; // eax
  bool v5; // zf
  int v6; // eax
  int v7; // esi
  int result; // eax
  bool v9; // cc
  LPARAM v10; // [esp+0x10] [ebp-0x30]
  int *v11; // [esp+0x14] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x18] [ebp-0x28] BYREF

  DlgItem = GetDlgItem((HWND)g_nActorRenderCount, 1155);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  this->PAL_GDB::UpdateInventorySlots();
  v3 = (int *)((char *)&this->m_RoleData[9].Remark.skillCount + 174);
  v10 = 0;
  v11 = (int *)v3;
  do
  {
    v4 = (unsigned long)*v3;
    v5 = *v3 == 0;
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_CCBStageCamBuffer;
    lParam[1] = v10;
    if ( v5 )
    {
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&unk_5D89B0);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf((char *const)&g_CCBStageCamBuffer, unk_C10D38);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
    else
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(v4);
      v7 = v6;
      lParam[2] = 0;
      sprintf((char *const)&g_CCBStageCamBuffer, "%s", v6 + 600);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      if ( *(_DWORD *)(v7 + 772) )
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", &off_5D8A3C);
      else
        sprintf((char *const)&g_CCBStageCamBuffer, "%s", g_szCCBStageCamName);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
    result = v10 + 1;
    v3 = (int *)(v11 + 1);
    v9 = ++v10 < 11;
    ++v11;
  }
  while ( v9 );
  return result;
}

// 0x004E5F60
int * PAL_GDB::UpdateInventorySlots()
{
  int *result; // eax
  _DWORD *v2; // ecx
  int v3; // edx

  memset((char *)&this->m_RoleData[9].Remark.skillCount + 174, 0, 0x2Cu);
  if ( *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 592) )
    *(_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount + 174) = 101;
  if ( *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 593) )
    *(_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount + 178) = 104;
  if ( *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 594) )
    *(_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount + 182) = 106;
  if ( *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 595) )
    *(_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount + 186) = 107;
  if ( *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 596) )
    *(_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount + 190) = 102;
  result = g_nPartyRoles;
  v2 = (_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount + 194);
  do
  {
    v3 = (unsigned long)(*result++);
    *v2++ = v3;
  }
  while ( (int)result < (int)&g_nPartyCount );
  return result;
}

// 0x004E5FF0
int PAL_GDB::DlgProcCamera(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  return (((CCBStageCam *)pfVal))->CCBStageCam::UpdateEditorState();
}

// 0x004EC1F0
LRESULT PAL_GDB::ShowDetailPanel(HWND hDlg)
{
  LRESULT result; // eax
  HWND v4; // ebp
  int v5; // esi
  int ItemNum; // ebx
  int RoleNum; // edi
  int SkillNum; // eax
  HWND hWnd; // [esp+0x10] [ebp-0x1C]
  HWND v10; // [esp+0x14] [ebp-0x18]
  HWND DlgItem; // [esp+0x18] [ebp-0x14]
  HWND v12; // [esp+0x1C] [ebp-0x10]
  HWND v13; // [esp+0x20] [ebp-0xC]
  HWND v14; // [esp+0x24] [ebp-0x8]
  HWND v15; // [esp+0x28] [ebp-0x4]
  char hDlga; // [esp+0x30] [ebp+0x4]

  result = *(_DWORD *)((char *)&this->m_RoleData[11].Remark.skillCount + 82);
  if ( result != -1 )
  {
    GetDlgItem(hDlg, 1208);
    GetDlgItem(hDlg, 1279);
    DlgItem = GetDlgItem(hDlg, 1281);
    v12 = GetDlgItem(hDlg, 1280);
    hWnd = GetDlgItem(hDlg, 1283);
    v10 = GetDlgItem(hDlg, 1282);
    GetDlgItem(hDlg, 1209);
    GetDlgItem(hDlg, 1214);
    GetDlgItem(hDlg, 1215);
    GetDlgItem(hDlg, 1216);
    GetDlgItem(hDlg, 1218);
    GetDlgItem(hDlg, 1217);
    v14 = GetDlgItem(hDlg, 1285);
    v15 = GetDlgItem(hDlg, 1284);
    v13 = GetDlgItem(hDlg, 1287);
    v4 = GetDlgItem(hDlg, 1286);
    GetDlgItem(hDlg, 1219);
    GetDlgItem(hDlg, 1220);
    GetDlgItem(hDlg, 1221);
    GetDlgItem(hDlg, 1222);
    v5 = *(_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount
                   + 4 * *(_DWORD *)((char *)&this->m_RoleData[11].Remark.skillCount + 82)
                   + 246);
    ItemNum = 0;
    RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v5);
    if ( RoleNum || (ItemNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(v5)) != 0 )
      SkillNum = 0;
    else
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v5);
    hDlga = 0;
    if ( RoleNum )
    {
      hDlga = *(_BYTE *)(RoleNum + 577);
    }
    else if ( ItemNum )
    {
      hDlga = *(_BYTE *)(ItemNum + 592);
    }
    else if ( SkillNum )
    {
      hDlga = *(_BYTE *)(SkillNum + 629);
    }
    EditBoxSetReadOnly(hWnd, 1);
    EditBoxSetReadOnly(v10, 0);
    EditBoxSetReadOnly(DlgItem, 0);
    EditBoxSetReadOnly(v12, 0);
    EditBoxSetReadOnly(v13, 0);
    EditBoxSetReadOnly(v4, 0);
    EditBoxSetReadOnly(v14, 0);
    EditBoxSetReadOnly(v15, 0);
    switch ( hDlga )
    {
      case 1:
        result = EditBoxSetReadOnly(v13, 1);
        break;
      case 2:
        result = EditBoxSetReadOnly(v14, 1);
        break;
      case 4:
        result = EditBoxSetReadOnly(v15, 1);
        break;
      default:
        result = EditBoxSetReadOnly(v4, 1);
        break;
    }
  }
  return result;
}

// 0x004ED8C0
int PAL_GDB::LoadSkillData()
{
  PAL_GDB *v1; // edx
  int v2; // esi
  char *v3; // eax
  int v4; // ecx
  int v5; // ecx
  int i; // edi
  int SkillNum; // eax
  char *v8; // eax
  int result; // eax
  char *v10; // ebx
  unsigned int v11; // edx
  char *v12; // edi
  const char *v13; // edi
  char *v14; // edi
  char *v15; // esi
  char v16; // cl
  int v17; // eax
  unsigned int v18; // eax
  const char *v19; // edi
  int v21; // [esp+0x1C] [ebp-0x4]
v2 = 0;
  v3 = (char *)&this->m_RoleData[0].Remark + 474;
  do
  {
    if ( v2 >= 5 )
    {
      v3[749] = 1;
      v3[744] = 1;
      v3[745] = 1;
      v3[748] = 1;
      v3[746] = 1;
      v3[747] = 1;
      v3[11] = 0;
      v3[10] = 0;
      v3[9] = 0;
      v4 = *(_DWORD *)v3;
      if ( *(_DWORD *)v3 == 916 || v4 == 917 || v4 == 921 || v4 == 922 || v4 == 926 || v4 == 927 )
        v3[9] = 1;
      v5 = *(_DWORD *)v3;
      if ( *(_DWORD *)v3 == 918 || v5 == 919 || v5 == 920 || v5 == 923 || v5 == 928 )
        v3[10] = 1;
    }
    ++v2;
    v3 += 892;
  }
  while ( v2 < 11 );
  for ( i = 0; i < 5; ++i )
  {
    if ( !*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * i) )
    {
      *(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * i) = 6603;
      *(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * i + 1) = 1;
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * i));
*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * i) = SkillNum;
    }
    v8 = (char *)&this->m_head.str[892 * i];
    v8[648] = *(_BYTE *)(*((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt + 352 * i) + 613);
    v8[651] = 0;
    v8[650] = 0;
    v8[649] = 0;
    switch ( v8[648] )
    {
      case 0:
        ++*(_DWORD *)&g_TempBuffer1024[912];
        g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
        if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)307.19998 )
          goto LABEL_22;
        ++*(_DWORD *)&g_TempBuffer1024[912];
        g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
        goto LABEL_24;
      case 1:
      case 3:
LABEL_24:
        v8[650] = 1;
        break;
      case 4:
      case 7:
LABEL_22:
        v8[649] = 1;
        break;
      default:
        break;
    }
    v8[652] = 0;
    if ( !i )
    {
      if ( *(_DWORD *)g_RoleSlotBuf.m_partyActor.m_pSelfAtt == 6603 )
      {
        *((_BYTE *)&this->m_RoleData[0].Remark + 486) = 1;
        *(_DWORD *)((char *)&this->m_RoleData[1].Remark.skillCount + 62) = *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[11];
        *(_DWORD *)((char *)&this->m_RoleData[1].Remark.skillCount + 66) = *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[15];
        *(_DWORD *)((char *)&this->m_RoleData[1].Remark.skillCount + 70) = *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[19];
      }
      else
      {
        *((_BYTE *)&this->m_RoleData[0].Remark + 486) = 0;
      }
      *((_BYTE *)&this->m_RoleData[0].Remark + 484) = 1;
      *((_BYTE *)&this->m_RoleData[0].Remark + 483) = 0;
    }
  }
  result = -4;
  v10 = (char *)&this->m_RoleData[0].Remark + 394;
  v21 = -4;
  do
  {
    if ( result > 0 && result < 7 )
      *((_DWORD *)v10 + 144) = result;
    if ( v10[17] )
    {
      switch ( *((_DWORD *)v10 - 2) )
      {
        case 'e':
          v11 = strlen(dword_58619C) + 1;
          v12 = (char *)&dword_58619C[v11];
          goto LABEL_42;
        case 'f':
          v11 = strlen((const char *)g_pfnUpdateFuncs) + 1;
          v12 = (char *)g_pfnUpdateFuncs + v11;
          goto LABEL_42;
        case 'h':
          v13 = (const char *)&g_pszSceneSlot1;
          goto LABEL_45;
        case 'j':
          v11 = strlen(a106) + 1;
          v12 = (char *)&a106[v11];
LABEL_42:
          qmemcpy(v10, &v12[-v11], 4 * (v11 >> 2));
          v15 = (char *)&v12[4 * (v11 >> 2) - v11];
          v14 = (char *)&v10[4 * (v11 >> 2)];
          v16 = v11;
          goto LABEL_46;
        case 'k':
          v13 = g_szFormat105;
          goto LABEL_45;
        default:
          (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*((_DWORD *)v10 - 2));
          if ( !v17 )
            break;
          v13 = (const char *)(v17 + 518);
LABEL_45:
          v18 = strlen(v13) + 1;
          v19 = (const char *)&v13[v18];
          qmemcpy(v10, &v19[-v18], 4 * (v18 >> 2));
          v15 = (char *)&v19[4 * (v18 >> 2) - v18];
          v14 = (char *)&v10[4 * (v18 >> 2)];
          v16 = v18;
LABEL_46:
          qmemcpy(v14, v15, v16 & 3);
          break;
      }
    }
    v10 += 892;
    result = v21 + 1;
    v21 = result;
  }
  while ( result + 4 < 11 );
  return result;
}

// 0x004F69F0
bool PAL_GDB::IsItemConsumable(int nItemId)
{
  char v2; // al

  v2 = *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nItemId) + 4);
  return v2 == 3 || v2 == 2 || v2 == 1;
}

// 0x004F6A20
bool PAL_GDB::IsItemEquipment(int nItemId)
{
  return *(_BYTE *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nItemId) + 4) == 2;
}

// 0x004F6A40
bool PAL_GDB::IsRoleAlive(int nRoleId)
{
  return *(_WORD *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nRoleId) + 592) > 0;
}

// 0x004F6A60
bool PAL_GDB::IsRoleDead(int nRoleId)
{
  return *(__int16 *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nRoleId) + 592) < 0;
}

// 0x004F6A80
bool PAL_GDB::IsRoleAlive2(int nVal)
{
  int RoleNum; // eax

  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nVal);
  return !RoleNum || *(_BYTE *)(RoleNum + 577) > 2u;
}

// 0x004F6AB0
bool PAL_GDB::IsItemConsumed(int nItemId)
{
  return *(__int16 *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetItemNum(nItemId) + 606) < 0;
}

// 0x004F6AD0
bool PAL_GDB::GetSkillLevel(int nVal)
{
  int SkillNum; // eax
  unsigned __int8 v3; // cl

  SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal);
  if ( SkillNum && *(_BYTE *)(SkillNum + 612) == 1 )
  {
    v3 = *(_BYTE *)(SkillNum + 631);
    if ( v3 <= 1u )
      return *(_WORD *)(SkillNum + 644) > 0;
    if ( v3 == 2 )
      return 1;
  }
  return 0;
}

// 0x004F6B20
bool PAL_GDB::GetSkillType(int nVal)
{
  int SkillNum; // eax
  unsigned __int8 v3; // cl

  SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal);
  if ( SkillNum && *(_BYTE *)(SkillNum + 612) == 1 )
  {
    v3 = *(_BYTE *)(SkillNum + 633);
    if ( v3 <= 1u )
      return *(_WORD *)(SkillNum + 648) > 0;
    if ( v3 == 2 )
      return 1;
  }
  return 0;
}

// 0x004F6B70
bool PAL_GDB::IsSkillUsable(int nVal)
{
  int SkillNum; // eax

  SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal);
  return *(_BYTE *)(SkillNum + 612) == 2 && *(_BYTE *)(SkillNum + 631) <= 1u && *(__int16 *)(SkillNum + 644) < 0;
}

// 0x004F6BB0
bool PAL_GDB::IsSkillEmpty(int nVal)
{
  int SkillNum; // eax

  SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal);
  return !SkillNum || *(_BYTE *)(SkillNum + 612) == 2;
}

// 0x004F6BE0
char PAL_GDB::SearchAllItems(int nVal, int *p_DWORD, int *pnVal, int *p_DWORD2)
{
  int v5; // edi
  int v6; // ebx
  int v7; // esi
  int v8; // eax
  int *v9; // edx
  int v11; // [esp+0x10] [ebp-0x4]

  v5 = 0;
  v11 = 0;
LABEL_2:
  v6 = 0;
  v7 = 0;
LABEL_3:
  v8 = 0;
  v9 = (int *)&this->m_RoleData[0].att[v5 + 1 + v7];
  while ( *v9 != nVal )
  {
    ++v8;
    ++v9;
    if ( v8 >= 8 )
    {
      v7 += 8;
      ++v6;
      if ( v7 < 48 )
        goto LABEL_3;
      v5 += 223;
      ++v11;
      if ( v5 >= 1115 )
        return 0;
      goto LABEL_2;
    }
  }
  *p_DWORD = v6;
  *pnVal = v8;
  *p_DWORD2 = v11;
  return 1;
}

// 0x004F6C60
char PAL_GDB::SearchItemLoop(int nVal, int nVal2, int *p_DWORD, int *pnVal)
{
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int *v8; // edx

  v5 = 0;
  v6 = 0;
  while ( 2 )
  {
    v7 = 0;
    v8 = (int *)&this->m_RoleData[0].att[223 * nVal + 1 + v6];
    do
    {
      if ( *v8 == nVal2 )
      {
        *p_DWORD = v5;
        *pnVal = v7;
        return 1;
      }
      ++v7;
      ++v8;
    }
    while ( v7 < 8 );
    v6 += 8;
    ++v5;
    if ( v6 < 48 )
      continue;
    break;
  }
  return 0;
}

// 0x004F6D30
char PAL_GDB::IsRoleSkillValid(unsigned int *pdwVal, int nVal)
{
  unsigned int v3; // eax

  v3 = (unsigned long)*pdwVal;
  if ( *pdwVal >= 0x104 )
  {
    if ( v3 <= 0x105 )
    {
      if ( *(_WORD *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(pdwVal[1]) + 2 * nVal + 616) == 2 )
        return 1;
    }
    else if ( v3 == 262 && *(_WORD *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(pdwVal[1]) + 2 * nVal + 698) == 2 )
    {
      return 1;
    }
  }
  return 0;
}

// 0x004F6E80
char PAL_GDB::IterateInventory(int *p_DWORD)
{
  unsigned int v3; // edx
  int v4; // esi
  int v5; // eax
  char *j; // edx
  int v7; // eax
  int v8; // ebx
  int v9; // esi
  int *v10; // edi
  int v11; // ecx
  int v12; // eax
  _DWORD *i; // eax
  int *p_DWORDa; // [esp+0x18] [ebp+0x4]

  if ( *p_DWORD != 262 )
  {
    v3 = (unsigned long)p_DWORD[2];
    v4 = 0;
    if ( v3 > 4 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::_todo_00478FD0(*(_DWORD *)((char *)&this->m_RoleData[0].Remark + 892 * v3 + 386));
      v11 = 0;
      for ( i = (_DWORD *)(v12 + 760); *i != p_DWORD[1]; ++i )
      {
        if ( ++v11 >= 4 )
          return 0;
      }
    }
    else if ( *p_DWORD == 260 )
    {
      v5 = 892 * v3;
      for ( j = &this->m_RoleData[0].ImageID[892 * v3 + 4];
            *(_DWORD *)j != (unsigned long)(p_DWORD[1] || !this->m_RoleData[0].ImageID[v5 + 28 + v4]);
            j += 4 )
      {
        if ( ++v4 >= 6 )
          return 0;
      }
    }
    else
    {
      v7 = (unsigned long)p_DWORD[1];
      p_DWORDa = 0;
      v8 = 936;
LABEL_11:
      v9 = 0;
      v10 = (int *)((char *)&p_DWORDa[223 * v3 + 186] + (_DWORD)this);
      while ( *v10 != v7 || !this->m_head.str[892 * v3 + v9 + v8] )
      {
        ++v9;
        ++v10;
        if ( v9 >= 8 )
        {
          v8 += 8;
          p_DWORDa += 8;
          if ( v8 < 984 )
            goto LABEL_11;
          return 0;
        }
      }
    }
  }
  return 1;
}

// 0x004F6FB0
char PAL_GDB::BuildItemArray(int nVal)
{
  int v3; // eax
  int SlotCount; // ebx
  int v5; // esi
  _BYTE pOut[12]; // [esp+0x10] [ebp-0x18] BYREF
  _BYTE v8[12]; // [esp+0x1C] [ebp-0xC] BYREF

  v3 = *(_DWORD *)(nVal + 8);
  if ( v3 >= 5 && v3 < 11 )
    return 0;
  SlotCount = ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount();
  v5 = 0;
  if ( SlotCount <= 0 )
    return 0;
  while ( *(_DWORD *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut) != *(_DWORD *)(nVal + 4)
       || *((int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(v8) + 1) <= 0
       || (((CCBSystem *)this))->CCBSystem::IsMagicSlotMsg(nVal) && !(((CCBSystem *)this))->CCBSystem::HandleMagicCommand(nVal) )
  {
    if ( ++v5 >= SlotCount )
      return 0;
  }
  return 1;
}

// 0x00526300
gbGeomNode * PAL_GDB::RefreshPartyStats()
{
  char *v1; // esi
  int *p_shikuaisucc; // edi
  float *v3; // ebx
  int v4; // ebp
  int SkillNum; // eax
  int v6; // eax
  int v7; // eax
  gbGeomNode *result; // eax

  v1 = (char *)&this->m_head.str[96];
  p_shikuaisucc = (int *)&this->m_RoleData[7].shikuaisucc;
  v3 = (float *)&this->m_RoleData[4].append[8];
  v4 = 5;
  do
  {
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*p_shikuaisucc);
    sprintf(v1, "SubGame\\Appraise\\Exhibit\\Data\\%s.pol", (const char *)(SkillNum + 36));
    (((PalScript *)(v3 - 77)))->PalScript::LoadModel(v1, 0);
    v6 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_shikuaisucc[1]);
    sprintf(v1, "SubGame\\Appraise\\Exhibit\\Data\\%s.pol", (const char *)(v6 + 36));
    (((PalScript *)v3))->PalScript::LoadModel(v1, 0);
    v7 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*p_shikuaisucc);
    sprintf(v1, "SubGame\\Appraise\\Exhibit\\Data\\%s.pol", (const char *)(v7 + 36));
    result = (((PalScript *)(v3 + 77)))->PalScript::LoadModel(v1, 0);
    p_shikuaisucc += 402;
    v3 += 8;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x00528650
int PAL_GDB::InitSkillDisplay()
{
  int v2; // eax
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // edx
  float Escape; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  _DWORD *v13; // ebp
  int SkillNum; // eax
  bool v15; // zf
  int v16; // edx
  int v17; // edx
  unsigned int NormalAtkID; // eax
  _DWORD *v19; // ebx
  int *v20; // ebp
  int v21; // eax
  int v22; // ecx
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // ecx
  float v27; // ecx
  int v28; // edx
  int result; // eax
  int *v30; // [esp+0x64] [ebp-0x78]
  int v31; // [esp+0x68] [ebp-0x74]
  int v32; // [esp+0x68] [ebp-0x74]
  int v33; // [esp+0x6C] [ebp-0x70] BYREF
  int v34; // [esp+0x70] [ebp-0x6C]
  int v35; // [esp+0x74] [ebp-0x68]
  int v36; // [esp+0x78] [ebp-0x64]
  int v37; // [esp+0x7C] [ebp-0x60] BYREF
  int v38; // [esp+0x80] [ebp-0x5C]
  int v39; // [esp+0x84] [ebp-0x58]
  int v40; // [esp+0x88] [ebp-0x54]
  int v41; // [esp+0x8C] [ebp-0x50] BYREF
  int v42; // [esp+0x90] [ebp-0x4C]
  int v43; // [esp+0x94] [ebp-0x48]
  int v44; // [esp+0x98] [ebp-0x44]
  _DWORD v45[2]; // [esp+0x9C] [ebp-0x40] BYREF
  int v46; // [esp+A4h] [ebp-0x38]
  int v47; // [esp+A8h] [ebp-0x34]
  _DWORD v48[4]; // [esp+ACh] [ebp-0x30] BYREF
  _DWORD v49[8]; // [esp+BCh] [ebp-0x20] BYREF
  int v50; // [esp+E0h] [ebp+0x4]

  this->m_RoleData[14].rolevalue[5] = v50;
  (((PalScript *)this))->PalScript::LoadResource("SubGame\\Appraise\\Exhibit\\Appraise.dft");
  this->PAL_GDB::SetDefaultEquipment();
  *(_DWORD *)&this->m_head.str[76] = 0;
  *(_DWORD *)&this->m_head.str[72] = 0;
  *(_DWORD *)&this->m_head.str[80] = *(_DWORD *)&this->m_head.str[88];
  *(_DWORD *)&this->m_head.str[84] = *(_DWORD *)&this->m_head.str[76] + *(_DWORD *)&this->m_head.str[92];
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, *(_DWORD *)&this->m_head.str[72], *(_DWORD *)&this->m_head.str[76], *(_DWORD *)&this->m_head.str[80], *(_DWORD *)&this->m_head.str[84]) /* [ROWTABLE] */;
  v2 = *(_DWORD *)((char *)&this->m_RoleData[1].Remark.skillCount + 286);
  v34 = 34;
  v33 = 165;
  v35 = 633;
  v36 = 138;
  v3 = (*(int ( **)(char *, ARC_PlayerAtt *, int *, PAL_GDB *))(v2 + 16))(
         (char *)&this->m_RoleData[1].Remark.skillCount + 286,
         &g_PlayerAttBuffer,
         &v33,
         this);
  LOBYTE(v3) = *(_BYTE *)(this->m_RoleData[14].rolevalue[5] + 1756);
  (((UIPushButton *)((char *)&this->m_RoleData[1].Remark.skillCount + 286)))->UIPushButton::CreateFromTemplate("SubGame\\Appraise\\Exhibit\\ExhibitRemark.tga", v3);
  v4 = *(_DWORD *)((char *)&this->m_RoleData[1].Remark + 438);
  v34 += 6;
  v33 += 22;
  v36 = v34 + 158;
  v35 = v33 + 428;
  (*(void ( **)(char *, ARC_PlayerAtt *, int *, PAL_GDB *))(v4 + 16))(
    (char *)&this->m_RoleData[1].Remark + 438,
    &g_PlayerAttBuffer,
    &v33,
    this);
  (((UIScene *)((char *)&this->m_RoleData[1].Remark + 438)))->UIScene::SetShow(0);
  AllocObject((char *)&this->m_RoleData[1].Remark + 438);
  v5 = *(_DWORD *)((char *)&this->m_RoleData[1].Remark.skillCount + 134);
  v48[1] = 10;
  v48[0] = 32;
  v48[2] = 160;
  v48[3] = 138;
  v6 = (*(int ( **)(char *, ARC_PlayerAtt *, _DWORD *, PAL_GDB *))(v5 + 16))(
         (char *)&this->m_RoleData[1].Remark.skillCount + 134,
         &g_PlayerAttBuffer,
         (_DWORD *)(v48),
         this);
  LOBYTE(v6) = *(_BYTE *)(this->m_RoleData[14].rolevalue[5] + 1756);
  (((UIPushButton *)((char *)&this->m_RoleData[1].Remark.skillCount + 134)))->UIPushButton::CreateFromTemplate("SubGame\\Appraise\\Exhibit\\word_type.tga", v6);
  v7 = *(_DWORD *)&this->m_RoleData[0].ModelID[18];
  v49[1] = 138;
  v49[0] = 86;
  v49[2] = 712;
  v49[3] = 606;
  (*(void ( **)(char *, ARC_PlayerAtt *, _DWORD *, PAL_GDB *))(v7 + 16))(
    &this->m_RoleData[0].ModelID[18],
    &g_PlayerAttBuffer,
    (_DWORD *)(v49),
    this);
  LOBYTE(v8) = *(_BYTE *)(this->m_RoleData[14].rolevalue[5] + 1756);
  (((UIPushButton *)&this->m_RoleData[0].ModelID[18]))->UIPushButton::CreateFromTemplate("SubGame\\Appraise\\Exhibit\\ExhibitBk.tga", v8);
  Escape = this->m_RoleData[2].Escape;
  v45[1] = 0;
  v45[0] = 0;
  v46 = 14;
  v47 = 600;
  (*(void ( **)(float *, ARC_PlayerAtt *, _DWORD *, PAL_GDB *))(LODWORD(Escape) + 16))(
    &this->m_RoleData[2].Escape,
    &g_PlayerAttBuffer,
    (_DWORD *)(v45),
    this);
  LOBYTE(v10) = *(_BYTE *)(this->m_RoleData[14].rolevalue[5] + 1756);
  (((UIPushButton *)&this->m_RoleData[2].Escape))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\smt_Line.tga", v10);
  v11 = *(_DWORD *)((char *)&this->m_RoleData[3].Remark.skillCount + 18);
  v45[0] = 786;
  v46 = 800;
  (*(void ( **)(char *, ARC_PlayerAtt *, _DWORD *, PAL_GDB *))(v11 + 16))(
    (char *)&this->m_RoleData[3].Remark.skillCount + 18,
    &g_PlayerAttBuffer,
    (_DWORD *)(v45),
    this);
  LOBYTE(v12) = *(_BYTE *)(this->m_RoleData[14].rolevalue[5] + 1756);
  (((UIPushButton *)((char *)&this->m_RoleData[3].Remark.skillCount + 18)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\smt_Line.tga", v12);
  (((CCBFiveNimbusWindow *)((char *)&this->m_RoleData[2].Remark.skillCount + 42)))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&g_PlayerAttBuffer._todo_006[2], (int)this);
  (((CCBFiveNimbusWindow *)((char *)&this->m_RoleData[2].Remark.skillCount + 42)))->CCBFiveNimbusWindow::SetFloatParam(1180.0);
  (((Camera *)((char *)&this->m_RoleData[2].Remark.skillCount + 42)))->Camera::UpdateCameraLookAt(400, 300);
  v13 = (_DWORD *)((char *)&this->m_RoleData[2].Remark.skillCount + 118);
  v30 = (int *)((char *)&this->m_RoleData[5].Remark.skillCount + 278);
  v31 = 5;
  do
  {
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*v30);
    sprintf(&this->m_head.str[96], "%s%s.pol", "SubGame\\Appraise\\Exhibit\\Data\\", (const char *)(SkillNum + 36));
    (((PalScript *)(v13 - 1)))->PalScript::LoadModel(&this->m_head.str[96], 0);
    *v13 = 1;
    sub_43A090((int)&this->m_RoleData[2].Remark.skillCount + 42, 1, 180.0);
    *(_DWORD *)((char *)&this->m_RoleData[2].Remark.skillCount + 286) = 58;
    v13 += 8;
    ++*(_DWORD *)((char *)&this->m_RoleData[2].Remark.skillCount + 110);
    v15 = v31 == 1;
    v30 += 402;
    --v31;
  }
  while ( !v15 );
  v16 = this->m_RoleData[1].att[4];
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 354) = 1124597760;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 366) = 1124597760;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 378) = -1006501888;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 390) = -1006501888;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 402) = -1006501888;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 350) = -1010958336;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 358) = 0;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 362) = 1136525312;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 370) = 0;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 374) = -1004863488;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 382) = 0;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 386) = 0;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 394) = 0;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 398) = 1142620160;
  *(_DWORD *)((char *)&this->m_RoleData[2].Remark + 406) = 0;
  v38 = 136;
  v37 = 86;
  v39 = 714;
  v40 = 605;
  (*(void ( **)(int *, ARC_PlayerAtt *, int *, PAL_GDB *))(v16 + 16))(
    &this->m_RoleData[1].att[4],
    &g_PlayerAttBuffer,
    &v37,
    this);
  LOBYTE(v17) = *(_BYTE *)(this->m_RoleData[14].rolevalue[5] + 1756);
  (((UIPushButton *)&this->m_RoleData[1].att[4]))->UIPushButton::CreateFromTemplate("SubGame\\Appraise\\Exhibit\\ExhibitZoom.tga", v17);
  (*(void ( **)(int *, _DWORD))this->m_RoleData[1].att[4])(&this->m_RoleData[1].att[4], 0);
  NormalAtkID = this->m_RoleData[1].NormalAtkID;
  v38 = 164;
  v37 = 325;
  v39 = 481;
  v40 = 196;
  (*(void ( **)(unsigned int *, ARC_PlayerAtt *, int *, PAL_GDB *))(NormalAtkID + 16))(
    &this->m_RoleData[1].NormalAtkID,
    &g_PlayerAttBuffer,
    &v37,
    this);
  (((UIScene *)&this->m_RoleData[1].NormalAtkID))->UIScene::SetShow(0);
  AllocObject(&this->m_RoleData[1].NormalAtkID);
  (*(void ( **)(unsigned int *, _DWORD))this->m_RoleData[1].NormalAtkID)(
    &this->m_RoleData[1].NormalAtkID,
    0);
  (((CCBFiveNimbusWindow *)((char *)&this->m_RoleData[2].Remark + 410)))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&g_PlayerAttBuffer._todo_006[3], (int)this);
  (((CCBFiveNimbusWindow *)((char *)&this->m_RoleData[2].Remark + 410)))->CCBFiveNimbusWindow::SetFloatParam(560.0);
  (((Camera *)((char *)&this->m_RoleData[2].Remark + 410)))->Camera::UpdateCameraLookAt(400, 360);
  v19 = (_DWORD *)((char *)&this->m_RoleData[2].Remark + 486);
  v20 = (int *)((char *)&this->m_RoleData[5].Remark.skillCount + 278);
  v32 = 5;
  do
  {
    v21 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*v20);
    sprintf(&this->m_head.str[96], "%s%s.pol", "SubGame\\Appraise\\Exhibit\\Data\\", (const char *)(v21 + 36));
    (((PalScript *)(v19 - 1)))->PalScript::LoadModel(&this->m_head.str[96], 0);
    *v19 = 0;
    v20 += 402;
    ++*(_DWORD *)((char *)&this->m_RoleData[2].Remark + 478);
    v19 += 8;
    --v32;
  }
  while ( v32 );
  v49[5] = 200;
  v49[4] = 250;
  v49[6] = 550;
  v49[7] = 328;
  Create__ovl_1((ARC_PlayerAtt *)&this->m_RoleData[14].rolevalue[7]);
  (((UIItem *)&this->m_RoleData[14].rolevalue[7]))->UIItem::SetData(31);
  v22 = *(_DWORD *)&this->m_RoleData[14].gold;
  v23 = *(_DWORD *)&this->m_RoleData[14].height;
  this->m_RoleData[14].skill[1] = this->m_RoleData[14].NormalAtkID + 26;
  this->m_RoleData[14].skill[0] = v22 + 6;
  this->m_RoleData[14].skill[3] = *(_DWORD *)&this->m_RoleData[14].speed2 - 38;
  *(_DWORD *)(&this->m_RoleData[16].Remark + 1) = 0;
  *(_DWORD *)((char *)&this->m_RoleData[16].Remark + 302) = 20;
  this->m_RoleData[14].skill[2] = v23 - 6;
  (((UIWnd *)((char *)&this->m_RoleData[15].Remark.skillCount + 262)))->UIWnd::sub_445FA0(this->m_RoleData[14].skill);
  v24 = this->m_RoleData[14].rolevalue[5];
  v25 = *(_DWORD *)((char *)&this->m_RoleData[0].Remark.skillCount + 186);
  v42 = 556;
  v41 = 338;
  v43 = 454;
  v44 = 582;
  LOBYTE(v26) = *(_BYTE *)(v24 + 1756);
  (*(void ( **)(char *, char *, int *, PAL_GDB *, char *, _DWORD, int))(v25 + 28))(
    (char *)&this->m_RoleData[0].Remark.skillCount + 186,
    (char *)&g_PlayerAttBuffer.id + 1,
    &v41,
    this,
    "SubGame\\Appraise\\Exhibit\\Do",
    0,
    v26);
  (**(void ( ***)(char *, _DWORD))((char *)&this->m_RoleData[0].Remark.skillCount + 186))((char *)((char *)&this->m_RoleData[0].Remark.skillCount + 186), (_DWORD)(0));
  v27 = *(float *)&v41;
  v28 = v43;
  this->m_RoleData[65].rolevalue[0] = v42;
  result = v44;
  this->m_RoleData[65].lv = v27;
  this->m_RoleData[65].rolevalue[1] = v28;
  this->m_RoleData[65].rolevalue[2] = result;
  *((_BYTE *)&this->m_RoleData[3].Remark.skillCount + 170) = 0;
  return result;
}

// 0x005294C0
char * PAL_GDB::SetDefaultEquipment()
{
  char *v1; // ebx
  int v2; // ebp
  char *result; // eax
  char *v4; // edi

  *(_DWORD *)((char *)&this->m_RoleData[5].Remark.skillCount + 278) = 6025;
  *(_DWORD *)((char *)&this->m_RoleData[7].Remark.skillCount + 182) = 6021;
  *(_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount + 86) = 6023;
  *(_DWORD *)&this->m_RoleData[10].stealnum = 6010;
  *(_DWORD *)&this->m_RoleData[12].height = 6001;
  *(_DWORD *)((char *)&this->m_RoleData[5].Remark.skillCount + 282) = 6301;
  *(_DWORD *)((char *)&this->m_RoleData[7].Remark.skillCount + 186) = 6302;
  *(_DWORD *)((char *)&this->m_RoleData[9].Remark.skillCount + 90) = 6303;
  this->m_RoleData[11].id = 6304;
  *(_DWORD *)&this->m_RoleData[12].speed2 = 6305;
  v1 = (char *)&this->m_RoleData[5].Remark.skillCount + 286;
  v2 = 5;
  do
  {
    qmemcpy(v1, (const void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*((_DWORD *)v1 - 2)), 0x320u);
    result = (char *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*((_DWORD *)v1 - 1));
    v4 = (char *)(v1 + 800);
    v1 += 1608;
    --v2;
    qmemcpy(v4, result, 0x320u);
  }
  while ( v2 );
  return result;
}

// 0x0052ECE0
BOOL PAL_GDB::SetupSkillData(int nVal)
{
  int p_DWORD[3]; // [esp+0x0] [ebp-0xC] BYREF

  p_DWORD[0] = nVal;
  p_DWORD[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nVal);
  p_DWORD[1] = 1;
  return (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(p_DWORD) != 0;
}
