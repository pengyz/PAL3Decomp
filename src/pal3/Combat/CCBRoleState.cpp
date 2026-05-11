#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/C2DSpark.h"
#include "pal3/gen/CCBAI.h"
#include "pal3/gen/CCBAIWindow.h"
#include "pal3/gen/CCBStage.h"
#include "pal3/gen/CCBStageCam.h"
#include "pal3/gen/CCBStageRole.h"
#include "pal3/gen/CCBStageScene.h"
#include "pal3/gen/CCBSystem.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/InternalContextBase.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/NPC.h"
#include "pal3/gen/PAL_GDB.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_40CCD0(...);
int sub_43FE90(...);
int sub_479260(...);
int sub_4DB940(...);
int sub_4E2AE0(...);
int sub_4E2C10(...);
int sub_4ED0A0(...);
int sub_4ED680(...);
int sub_4ED800(...);
int sub_4ED870(...);
int sub_4F05A0(...);
int sub_4F0A10(...);
int sub_4F1C40(...);
int sub_4F2390(...);
int sub_4F2660(...);
int sub_4F2690(...);
int sub_4F2750(...);
int sub_4F27B0(...);
int sub_4F2BF0(...);
int sub_4F4820(...);
int sub_4F4B90(...);
int sub_4F4C80(...);
int sub_4F6A40(...);
int sub_4F6A60(...);
int sub_4F6AD0(...);
int sub_4F6B70(...);
int sub_4F6C60(...);
int sub_4F6CD0(...);
int sub_4F6DA0(...);
int sub_4F6E80(...);
int sub_4F6FB0(...);
int sub_4F7050(...);
int sub_4F70A0(...);
int sub_4F7200(...);
int sub_4F7480(...);
int sub_4F8AF0(...);
int sub_4F8FD0(...);
int sub_4F90F0(...);
int sub_4F95F0(...);
int sub_4FA620(...);
int sub_4FA700(...);
int sub_4FB370(...);
int sub_4FCA40(...);
int sub_501330(...);
int sub_501410(...);
int sub_501CF0(...);
int sub_501E60(...);
int sub_501F30(...);
int sub_502000(...);
int sub_5021C0(...);
int sub_502300(...);
int sub_502430(...);
int sub_5024D0(...);
int sub_5027E0(...);

// Unnamed globals (extern)
extern char aDProjectPal3Co_2[];
extern char aFailToCreateWe[];
extern char aWa006[];
extern char aWa010[];
extern char aWa048[];
extern char aWd004[];
extern char aWd005[];
extern char aWd006[];
extern char aWd007[];
extern char aWd008[];
extern char aWd009[];
extern char aWd010[];
extern char aWd011[];
extern char aWd012[];
extern char aWd013[];
extern char aWd014[];
extern char aWd015[];
extern char aWd016[];
extern char aWd017[];
extern char aWd018[];
extern char aWd019[];
extern char aWd020[];
extern char aWd021[];
extern char aWd022[];
extern unsigned char byte_5D8EC8;
extern unsigned char byte_5D8EE0;
extern unsigned char byte_5D8EF8;
extern unsigned char byte_5D8F0C;
extern unsigned char byte_5DFDEB;
extern int dword_17AA050;
extern int dword_17AA150;
extern int dword_17AA350;
extern int dword_17AA450;
extern int dword_17AA808;
extern int dword_17AA818;
extern int dword_17AA828;
extern int dword_17AA838;
extern int dword_17AA848;
extern int dword_17AA858;
extern void *off_56A66C;
extern int unk_FFFFFF;

// 0x004ECB00
int CCBRoleState::Update()
{
  this->CheckStatus();
  this->ProcessActions();
  return this->UpdateEffects();
}

// 0x004ED010
char CCBRoleState::IsRoleAlive(int roleIdx)
{
  if ( *(&this->m_Role[0].bValid + 892 * roleIdx) )
    return *(&this->m_Role[0].bAlive + 892 * roleIdx);
  else
    return 0;
}

// 0x004ED060
char CCBRoleState::GetRoleType(int roleIdx)
{
  char *v2; // eax

  v2 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  if ( !v2[577] )
    return 0;
  if ( v2[579] == 1 )
    return 0;
  return v2[580];
}

// 0x004ED100
int CCBRoleState::GetForce(int roleIdx)
{
  int v2; // edx
  int result; // eax

  v2 = 5;
  if ( (_BYTE)roleIdx )
  {
    result = (int)&this->m_Role[5].sModel[8];
    while ( !*(_BYTE *)(result - 11) || *(int *)result <= 0 || *(_BYTE *)(result + 844) )
    {
      ++v2;
      result += 892;
      if ( v2 >= 11 )
      {
        LOBYTE(result) = 1;
        return result;
      }
    }
  }
  else
  {
    result = (int)&this->m_Role[5].nIndex + 2;
    while ( !*(_BYTE *)(result - 1) || *(_BYTE *)result != 1 || *(_BYTE *)(result + 854) )
    {
      ++v2;
      result += 892;
      if ( v2 >= 11 )
      {
        LOBYTE(result) = 1;
        return result;
      }
    }
  }
  LOBYTE(result) = 0;
  return result;
}

// 0x004EDD60
CCBRoleState::CCBRoleState()
{
  char *v1; // ebp
  char *v2; // esi
  int v3; // eax
  char *v4; // ebx
  int v5; // eax
  char *v6; // ecx
  int v7; // eax
  char *v8; // ecx
  int v9; // edx
  int v10; // eax
  char *v11; // ecx
  int v12; // edx
  int v13; // eax
  char *v14; // ecx
  int v15; // edx
  int v16; // eax
  char *v17; // ecx
  int v18; // edx
  char *v19; // ecx
  int v20; // edx
  int v21; // edi
  int v22; // ebp
  int v23; // ecx
  _DWORD *v25; // [esp+10h] [ebp-8h]
  char *v26; // [esp+14h] [ebp-4h]

  v1 = (char *)&this->m_Role[0]._rest[484];
  v2 = (char *)&g_SceneMgr.m_slot[0]._tail[16];
  v26 = (char *)&this->m_Role[0]._rest[484];
  do
  {
    LOBYTE(v3) = *(v1 - 535);
    v4 = (char *)v1 - 4;
    if ( (_BYTE)v3 )
    {
      memset(v4, 0, 0x1Cu);
      if ( (int)v2 < (int)&g_SceneMgr.m_slot[0]._tail[16] || (int)v2 >= (int)&g_SceneMgr.m_RoleSystem[0]._pad_284[180] )
      {
        v21 = 580;
        v25 = v1;
        do
        {
          v22 = *(_DWORD *)(((PAL_GDB *)&g_GDB)->~PAL_GDB(*((_DWORD *)v4 - 139)) + v21) << 16;
          v23 = *(_DWORD *)(((PAL_GDB *)&g_GDB)->~PAL_GDB(*((_DWORD *)v4 - 139)) + v21);
          v21 += 4;
          * v25 = (*)v23 | v22;
          LOBYTE(v3) = (_BYTE)v25++ + 4;
        }
        while ( v21 < 600 );
        v1 = v26;
      }
      else
      {
        if ( *((_DWORD *)v2 - 2) )
        {
          v5 = 0;
          v6 = v1;
          do
          {
            v6 += 4;
            *((_DWORD *)v6 - 1) = *(unsigned __int8 *)(*(_DWORD *)v2 + v5++ + 619) << 16;
          }
          while ( v5 < 5 );
        }
        if ( *((_DWORD *)v2 - 17) )
        {
          v7 = 0;
          v8 = v1;
          do
          {
            v8 += 4;
            v9 = *(unsigned __int8 *)(*((_DWORD *)v2 - 15) + v7++ + 619) + *((_DWORD *)v8 - 1);
            *((_DWORD *)v8 - 1) = v9;
          }
          while ( v7 < 5 );
        }
        if ( *((_DWORD *)v2 - 14) )
        {
          v10 = 0;
          v11 = v1;
          do
          {
            v11 += 4;
            v12 = *(unsigned __int8 *)(*((_DWORD *)v2 - 12) + v10++ + 619) + *((_DWORD *)v11 - 1);
            *((_DWORD *)v11 - 1) = v12;
          }
          while ( v10 < 5 );
        }
        if ( *((_DWORD *)v2 - 11) )
        {
          v13 = 0;
          v14 = v1;
          do
          {
            v14 += 4;
            v15 = *(unsigned __int8 *)(v13 + *((_DWORD *)v2 - 9) + 619) + *((_DWORD *)v14 - 1);
            ++v13;
            *((_DWORD *)v14 - 1) = v15;
          }
          while ( v13 < 5 );
        }
        if ( *((_DWORD *)v2 - 8) )
        {
          v16 = 0;
          v17 = v1;
          do
          {
            v17 += 4;
            v18 = *(unsigned __int8 *)(*((_DWORD *)v2 - 6) + v16++ + 619) + *((_DWORD *)v17 - 1);
            *((_DWORD *)v17 - 1) = v18;
          }
          while ( v16 < 5 );
        }
        v3 = *((_DWORD *)v2 - 5);
        if ( v3 )
        {
          v3 = 0;
          v19 = v1;
          do
          {
            v19 += 4;
            v20 = *(unsigned __int8 *)(*((_DWORD *)v2 - 3) + v3++ + 619) + *((_DWORD *)v19 - 1);
            *((_DWORD *)v19 - 1) = v20;
          }
          while ( v3 < 5 );
        }
      }
    }
    v2 += 1408;
    v1 += 892;
    v26 = v1;
  }
  while ( (int)v2 < (int)&g_SceneMgr.m_RoleSystem[1]._pad_200[56] );
  v3;
}

// 0x004EDF10
char CCBRoleState::_CCBRoleState()
{
  int v2; // ebp
  int *p_d0F0; // edi
  char *v4; // esi
  char result; // al

  v2 = 0;
  p_d0F0 = (int *)&g_SceneMgr.m_slot[0]._d0F0;
  v4 = (char *)&this->m_Role[0]._rest[28];
  do
  {
    result = *(v4 - 79);
    if ( result )
    {
      if ( *(p_d0F0 - 5) )
      {
        *(float *)v4 = (double)*(__int16 *)(*(p_d0F0 - 3) + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(*(p_d0F0 - 3) + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(*(p_d0F0 - 3) + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(*(p_d0F0 - 3) + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(*(p_d0F0 - 3) + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(*(p_d0F0 - 3) + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(*(p_d0F0 - 3) + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(*(p_d0F0 - 3) + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(*(p_d0F0 - 3) + 628));
      }
      if ( *(p_d0F0 - 2) )
      {
        *(float *)v4 = (double)*(__int16 *)(*p_d0F0 + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(*p_d0F0 + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(*p_d0F0 + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(*p_d0F0 + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(*p_d0F0 + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(*p_d0F0 + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(*p_d0F0 + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(*p_d0F0 + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(*p_d0F0 + 628));
      }
      if ( p_d0F0[1] )
      {
        *(float *)v4 = (double)*(__int16 *)(p_d0F0[3] + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(p_d0F0[3] + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(p_d0F0[3] + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(p_d0F0[3] + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(p_d0F0[3] + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(p_d0F0[3] + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(p_d0F0[3] + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(p_d0F0[3] + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(p_d0F0[3] + 628));
      }
      if ( p_d0F0[4] )
      {
        *(float *)v4 = (double)*(__int16 *)(p_d0F0[6] + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(p_d0F0[6] + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(p_d0F0[6] + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(p_d0F0[6] + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(p_d0F0[6] + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(p_d0F0[6] + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(p_d0F0[6] + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(p_d0F0[6] + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(p_d0F0[6] + 628));
      }
      if ( p_d0F0[7] )
      {
        *(float *)v4 = (double)*(__int16 *)(p_d0F0[9] + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(p_d0F0[9] + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(p_d0F0[9] + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(p_d0F0[9] + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(p_d0F0[9] + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(p_d0F0[9] + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(p_d0F0[9] + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(p_d0F0[9] + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(p_d0F0[9] + 628));
      }
      if ( *(p_d0F0 - 5) == 80015 )
      {
        if ( *(p_d0F0 - 2) == 84018 && p_d0F0[1] == 83012 && p_d0F0[4] == 8153 && p_d0F0[7] == 8154 )
          v4[44] = 1;
        if ( *(p_d0F0 - 5) == 80015
          && *(p_d0F0 - 2) == 84018
          && p_d0F0[1] == 83012
          && p_d0F0[4] == 8154
          && p_d0F0[7] == 8153 )
        {
          v4[44] = 1;
        }
      }
      result = -82;
      if ( p_d0F0[4] == 8110 || p_d0F0[7] == 8110 )
        v4[45] = 1;
    }
    p_d0F0 += 352;
    ++v2;
    v4 += 892;
  }
  while ( (int)p_d0F0 < (int)&g_SceneMgr.m_RoleSystem[0]._pad_284[132] );
  return result;
}

// 0x004EE430
float * CCBRoleState::Reset(int a2, float *a3)
{
  float *result; // eax
  float *v4; // edx

  switch ( (unsigned int)a3 )
  {
    case 0x14u:
      result = (float *)&this->m_Role[0]._rest[892 * a2 + 56];
      * result = (*)*result + 5.0;
      break;
    case 0x15u:
      v4 = (float *)&this->m_sCombatDialog[892 * a2];
      v4[171] = v4[171] + 15.0;
      v4[172] = v4[172] + 5.0;
      goto LABEL_4;
    case 0x16u:
LABEL_4:
      result = (float *)&this->m_Role[0]._rest[892 * a2 + 64];
      * result = (*)*result + 10.0;
      break;
    case 0x17u:
      result = (float *)&this->m_Role[0]._rest[892 * a2 + 68];
      *(_DWORD *)result += 5;
      break;
    case 0x18u:
      result = (float *)&this->m_Role[0]._rest[892 * a2 + 56];
      * result = (*)*result + 20.0;
      break;
    default:
      result = a3;
      break;
  }
  return result;
}

// 0x004EE540
char CCBRoleState::Create()
{
  char *v1; // ebp
  gbGeomNode **v2; // edi
  int v3; // eax
  gbGeomNode *v4; // eax
  gbGeomNode *v5; // esi
  gbGeomNode *v6; // ecx
  gbGeomNode *v7; // eax
  gbGeomNode *v8; // esi
  gbGeomNode *v9; // ecx
  char Buffer[256]; // [esp+14h] [ebp-120Ch] BYREF
  char v12[256]; // [esp+114h] [ebp-110Ch] BYREF
  _BYTE pExceptionObject[1024]; // [esp+214h] [ebp-100Ch] BYREF
  char v14[1024]; // [esp+614h] [ebp-C0Ch] BYREF
  char ArgList[1024]; // [esp+A14h] [ebp-80Ch] BYREF
  char v16[1024]; // [esp+E14h] [ebp-40Ch] BYREF
  int v17; // [esp+121Ch] [ebp-4h]

  v1 = (char *)&g_SceneMgr.m_slot[0]._tail[16];
  v2 = (gbGeomNode **)(this + 350);
  do
  {
    LOBYTE(v3) = *((_BYTE *)v2 - 823);
    if ( (_BYTE)v3 )
    {
      v3 = *((_DWORD *)v1 - 2);
      if ( v3 )
      {
        sprintf(Buffer, "weapon\\%s\\%s.pol", (const char *)(*(_DWORD *)v1 + 36), (const char *)(*(_DWORD *)v1 + 36));
        sprintf(
          v12,
          "weapon\\%s\\%s%s.tga",
          (const char *)(*(_DWORD *)v1 + 36),
          (const char *)(*(_DWORD *)v1 + 36),
          (const char *)(*(_DWORD *)v1 + 66));
        v4 = (gbGeomNode *)operator new(0x118u);
        v5 = v4;
        v17 = 0;
        if ( v4 )
        {
          v4->gbGeomNode();
          *(_DWORD *)v5->_base = &off_56A66C;
          v6 = v5;
        }
        else
        {
          v6 = 0;
        }
        v17 = -1;
        *v2 = v6;
        if ( !v6 )
        {
          qmemcpy(
            pExceptionObject,
            ((Logger *)ArgList)->FormatException(aFailToCreateWe, aDProjectPal3Co_2, 1484),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        v6->LoadFromFile(Buffer, 0, 0);
        ((gbGeomNode *)*v2)->ReplaceTexture(v12);
        v7 = (gbGeomNode *)operator new(0x118u);
        v8 = v7;
        v17 = 1;
        if ( v7 )
        {
          v7->gbGeomNode();
          *(_DWORD *)v8->_base = &off_56A66C;
          v9 = v8;
        }
        else
        {
          v9 = 0;
        }
        v17 = -1;
        v2[3] = v9;
        if ( !v9 )
        {
          qmemcpy(v14, ((Logger *)v16)->FormatException(aFailToCreateWe, aDProjectPal3Co_2, 1494), sizeof(v14));
          _CxxThrowException(v14, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        v9->LoadFromFile(Buffer, 0, 0);
        ((gbGeomNode *)v2[3])->ReplaceTexture(v12);
        LOBYTE(v3) = 1;
        (*v2)->bBlade = 1;
        v2[3]->bBlade = 1;
      }
    }
    v1 += 1408;
    v2 += 223;
  }
  while ( (int)v1 < (int)&g_SceneMgr.m_RoleSystem[0]._pad_284[180] );
  return v3;
}

// 0x004EE760
int CCBRoleState::Destroy()
{
  char *v1; // ebp
  char *v2; // esi
  int v3; // edi
  void (***v4)(_DWORD, int); // ecx
  int result; // eax
  int v6; // [esp+10h] [ebp-4h]

  v1 = (char *)&this->m_Role[0]._rest[784];
  v6 = 5;
  do
  {
    v2 = v1;
    v3 = 3;
    do
    {
      v4 = (void (***)(_DWORD, int))*((_DWORD *)v2 - 3);
      if ( v4 )
      {
        (**v4)(v4, 1);
        *((_DWORD *)v2 - 3) = 0;
      }
      if ( *(_DWORD *)v2 )
      {
        (***(void (****)(_DWORD, int))v2)(*(_DWORD *)v2, 1);
        *(_DWORD *)v2 = 0;
      }
      v2 += 4;
      --v3;
    }
    while ( v3 );
    v1 += 892;
    result = --v6;
  }
  while ( v6 );
  return result;
}

// 0x004EE7C0
int CCBRoleState::Init(int a2, char a3)
{
  CCBUI *m_pUI; // esi

  m_pUI = (CCBUI *)this->m_pCBSystem->m_pUI;
  if ( a3 == 1 )
  {
    if ( !a2 )
      (**(void (***)(void *, int))m_pUI->m_pRoleStateGP[1])(m_pUI->m_pRoleStateGP[1], 1);
    (**(void (***)(void *, int))m_pUI->m_pAttackSequenFace[a2 + 4])(m_pUI->m_pAttackSequenFace[a2 + 4], 1);
    (**(void (***)(void *, int))m_pUI->m_pRoleStateImmunity[a2 + 6])(m_pUI->m_pRoleStateImmunity[a2 + 6], 1);
    (**(void (***)(void *, int))m_pUI->m_pRoleStateHP[a2 + 1])(m_pUI->m_pRoleStateHP[a2 + 1], 1);
    return (**(int (***)(void *, int))m_pUI->m_pRoleStateImmunity[a2 + 10])(
             m_pUI->m_pRoleStateImmunity[a2 + 10],
             1);
  }
  else
  {
    if ( !a2 )
      (**(void (***)(void *, _DWORD))m_pUI->m_pRoleStateGP[1])(m_pUI->m_pRoleStateGP[1], 0);
    (**(void (***)(void *, _DWORD))m_pUI->m_pAttackSequenFace[a2 + 4])(m_pUI->m_pAttackSequenFace[a2 + 4], 0);
    (**(void (***)(void *, _DWORD))m_pUI->m_pRoleStateImmunity[a2 + 6])(
      m_pUI->m_pRoleStateImmunity[a2 + 6],
      0);
    (**(void (***)(void *, _DWORD))m_pUI->m_pRoleStateHP[a2 + 1])(m_pUI->m_pRoleStateHP[a2 + 1], 0);
    return (**(int (***)(void *, _DWORD))m_pUI->m_pRoleStateImmunity[a2 + 10])(
             m_pUI->m_pRoleStateImmunity[a2 + 10],
             0);
  }
}

// 0x004EE870
int CCBRoleState::InitUI(int a2)
{
  return (int)this->m_Role + 892 * a2;
}

// 0x004EE890
int CCBRoleState::Update(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return 0;
}

// 0x004EE990
bool CCBRoleState::VarianceRoundCounter(_DWORD *a2)
{
  int RoleNum; // eax
  unsigned __int8 v5; // al
  int v6; // [esp+14h] [ebp+8h]
  float v7; // [esp+14h] [ebp+8h]

  RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(a2[1]);
  if ( *a2 == 261 )
    return 1;
  v5 = *(_BYTE *)(RoleNum + 616);
  if ( v5 <= 1u )
  {
    v6 = this->ApplyDamage(1, a2[2]);
    if ( v6 > 0 )
    {
      v7 = (double)v6 * 10.24;
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      return ((g_RandSeed >> 16) & 0x3FF) < (int)v7;
    }
  }
  else if ( v5 == 100 )
  {
    return 1;
  }
  return 0;
}

// 0x004EEA70
char CCBRoleState::CheckVarianceRound(int a2, int a3, int *a4)
{
  int v4; // edi
  signed int v5; // esi
  char v6; // bl
  int v7; // eax
  int ItemNum; // eax
  int v9; // edi
  _DWORD *v10; // ebp
  int v11; // ecx
  char *v12; // esi
  unsigned __int8 v13; // cl
  bool v14; // zf
  int v15; // edx
  int v16; // ecx
  int *v17; // edi
  int v18; // ebp
  int v19; // esi
  int v20; // eax
  signed int v23; // [esp+14h] [ebp-8h]
  struct Concurrency::IThreadProxy *Proxy; // [esp+18h] [ebp-4h]

  v4 = a2;
  if ( a2 >= 5 && a2 < 11 )
    return 0;
  v5 = 0;
  Proxy = ((Concurrency *)&g_GDB)->details::InternalContextBase::GetProxy();
  v23 = 0;
  if ( (int)Proxy <= 0 )
    return 0;
  while ( 2 )
  {
    v6 = 1;
    v7 = sub_479260(&g_GDB, v5);
    *a4 = v7;
    ItemNum = ((PAL_GDB *)&g_GDB)->GDB_GetItemNum(v7);
    if ( *(_DWORD *)(ItemNum + 56) != a3 )
      goto LABEL_53;
    if ( *(_DWORD *)(ItemNum + 36) != *(&this->m_Role[0].dwID + 223 * v4) )
      goto LABEL_52;
    v9 = 0;
    v10 = (_DWORD *)(ItemNum + 36);
    do
    {
      if ( !*v10 )
        goto LABEL_33;
      v11 = -1;
      switch ( *v10 )
      {
        case 'e':
          v11 = 0;
          break;
        case 'f':
          v11 = 4;
          break;
        case 'h':
          v11 = 1;
          break;
        case 'i':
        case 'j':
          v11 = 2;
          break;
        case 'k':
          v11 = 3;
          break;
        default:
          break;
      }
      v12 = (char *)&this->m_sCombatDialog[892 * v11];
      if ( !v12[577] )
        v6 = 0;
      v13 = *(_BYTE *)(ItemNum + v9 + 52);
      if ( v13 )
      {
        v14 = v13 == 7;
        if ( v13 >= 7u )
          goto LABEL_21;
        if ( v13 != v12[1136] )
          v6 = 0;
      }
      v14 = v13 == 7;
LABEL_21:
      if ( v14 )
      {
        v15 = *((_DWORD *)v12 + 284);
        if ( v15 != 3 && v15 != 2 && v15 != 4 )
          v6 = 0;
      }
      if ( v13 == 8 )
      {
        v16 = *((_DWORD *)v12 + 284);
        if ( v16 != 1 && v16 != 2 && v16 != 5 )
          v6 = 0;
      }
      if ( *(_BYTE *)(ItemNum + v9 + 60) != v12[648] )
        v6 = 0;
LABEL_33:
      ++v9;
      ++v10;
    }
    while ( v9 < 4 );
    if ( !v6 )
      goto LABEL_51;
    v17 = (int *)(ItemNum + 68);
    v18 = 3;
    do
    {
      switch ( *(v17 - 7) )
      {
        case 'e':
          v19 = 0;
          goto LABEL_42;
        case 'f':
          v19 = 4;
          goto LABEL_42;
        case 'h':
          v19 = 1;
          goto LABEL_42;
        case 'i':
        case 'j':
          v19 = 2;
          goto LABEL_42;
        case 'k':
          v19 = 3;
LABEL_42:
          v20 = *v17;
          if ( *v17 >= 0 && v20 < 26 && !this->GetRoleField(v19, v20 + 1) )
            v6 = 0;
          if ( *v17 == 26 && !this->IsRoleInForce(v19) )
            v6 = 0;
          break;
        default:
          break;
      }
      ++v17;
      --v18;
    }
    while ( v18 );
    if ( !v6 )
    {
LABEL_51:
      v5 = v23;
LABEL_52:
      v4 = a2;
LABEL_53:
      v23 = ++v5;
      if ( v5 >= (int)Proxy )
        return 0;
      continue;
    }
    return 1;
  }
}

// 0x004EECB0
char CCBRoleState::CancelVariance(_DWORD *a2, unsigned int a3)
{
  char result; // al
  char *v4; // eax

  if ( a3 > 0xA )
    return 0;
  v4 = (char *)&this->m_sCombatDialog[892 * a3];
  if ( !v4[577] )
    return 0;
  if ( !v4[578] )
    return 0;
  if ( v4[1432] )
    return 0;
  if ( v4[1431] )
    return 0;
  if ( v4[1164] == 1 && a2[1] != 4401 )
    return 0;
  if ( *a2 != 259 )
    return 1;
  result = this->CalSneakAttack(a2[2], a3);
  if ( result )
    return 1;
  return result;
}

// 0x004EEE60
char CCBRoleState::IsAlive(int a2, int a3)
{
  char result; // al
  int v5; // eax

  if ( !this->m_Role[0].bValid )
    return 0;
  v5 = *(_DWORD *)&this->m_Role[0]._rest[8];
  if ( !v5 )
    return 0;
  if ( v5 != a2 )
    return 0;
  result = this->IsRoleAlive(0);
  if ( result )
  {
    if ( *(_DWORD *)&this->m_Role[0]._rest[508] == 6 )
    {
      if ( this->GetRoleField(0, 14) )
      {
        return 0;
      }
      else
      {
        result = ((CCBStageRole *)this->m_pStage->m_pRole[0])->EndTask(a2, a3);
        if ( result )
        {
          result = ((CCBStageRole *)this->m_pStage->m_pRole[a2])->ForceEndTaskByPFN();
          if ( result )
            return ((CCBStage *)this->m_pStage)->ForceDelTask(18) != 0;
        }
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x004EF4A0
void CCBRoleState::IsBoss(_DWORD *arg0, unsigned int a2)
{
  int RoleNum; // edi
  int SkillNum; // ebp
  int v5; // esi
  __int16 *v6; // ebx
  __int16 *v7; // ebp
  int v8; // eax
  int v9; // eax
  char *Instance; // eax
  char *v11; // eax
  char *v12; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // eax
  char *v16; // eax
  char v17; // [esp+12h] [ebp-Ah]
  char v18; // [esp+13h] [ebp-9h]
  char v19; // [esp+14h] [ebp-8h]
  char v20; // [esp+15h] [ebp-7h]
  char v21; // [esp+16h] [ebp-6h]
  char v22; // [esp+17h] [ebp-5h]

  RoleNum = 0;
  SkillNum = 0;
  if ( *arg0 == 262 )
    SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(arg0[1]);
  else
    RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(arg0[1]);
  v5 = 0;
  v6 = (__int16 *)(RoleNum + 618);
  v22 = 0;
  v17 = 0;
  v18 = 0;
  v19 = 0;
  v20 = 0;
  v21 = 0;
  v7 = (__int16 *)(SkillNum + 700);
  do
  {
    if ( *arg0 == 262 )
      v8 = *v7;
    else
      v8 = *v6;
    v9 = v8 - 1;
    if ( v9 )
    {
      if ( v9 == 1 )
      {
        this->ProcessRound(a2);
        switch ( v5 )
        {
          case 13:
            v22 = 1;
            break;
          case 14:
            v17 = 1;
            break;
          case 15:
            v18 = 1;
            break;
          case 16:
            v19 = 1;
            break;
          case 17:
            v21 = 1;
            break;
          case 18:
            v20 = 1;
            break;
          default:
            break;
        }
      }
    }
    else
    {
      this->ProcessRound(a2);
    }
    ++v5;
    ++v7;
    ++v6;
  }
  while ( v5 < 25 );
  if ( v22 )
  {
    if ( v17 && v18 && v19 && v20 && v21 )
    {
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(aWd019, 1);
      return;
    }
    v11 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v11)->AudioSetPosition(aWd017, 1);
  }
  if ( v17 )
  {
    v12 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v12)->AudioSetPosition(aWd017, 1);
  }
  if ( v18 )
  {
    v13 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v13)->AudioSetPosition(aWd017, 1);
  }
  if ( v19 )
  {
    v14 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v14)->AudioSetPosition(aWd018, 1);
  }
  if ( v20 )
  {
    v15 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v15)->AudioSetPosition(aWd018, 1);
  }
  if ( v21 )
  {
    v16 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v16)->AudioSetPosition(aWd018, 1);
  }
}

// 0x004EF6A0
int CCBRoleState::IsAllWeDead(int a2)
{
  return *(_DWORD *)&this->m_Role[0]._rest[892 * a2 + 508];
}

// 0x004EF6C0
_DWORD * CCBRoleState::IsAllEnemyDead(int a2, int *arg4, int *a3)
{
  int RoleNum; // eax
  int v4; // ecx
  _DWORD *result; // eax

  RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(a2);
  v4 = 1;
  result = (_DWORD *)(RoleNum + 8);
  *a3 = 0;
  *arg4 = 0;
  do
  {
    if ( *result == 1 )
    {
      if ( *arg4 )
        *a3 = v4;
      else
        *arg4 = v4;
    }
    ++result;
    ++v4;
  }
  while ( v4 - 1 <= 4 );
  return result;
}

// 0x004EF710
int CCBRoleState::CanAction(int a2, int a3, int a4)
{
  int v5; // eax
  char *i; // ecx
  int v7; // edi
  char *j; // eax
  int v9; // ebp

  v5 = 1;
  for ( i = &this->m_Role[0]._rest[892 * a3 + 484]; !*(_DWORD *)i; i += 4 )
  {
    if ( ++v5 >= 6 )
      return 0;
  }
  v7 = 1;
  for ( j = &this->m_Role[0]._rest[892 * a2 + 484]; (*(_DWORD *)j & 0xFFFF0000) == 0; j += 4 )
  {
    if ( ++v7 >= 6 )
      return 0;
  }
  v9 = this->CheckDeath(v7);
  return (*(_DWORD *)&this->m_Role[0]._rest[892 * a3 + 480 + 4 * v9] != 0)
       - (*(_DWORD *)&this->m_Role[0]._rest[892 * a3 + 480 + 4 * sub_4FA700(v7)] != 0);
}

// 0x004EF7E0
int CCBRoleState::SetCanAction(unsigned int dmg, int roleIdx, int a4)
{
  int result; // eax
  int v6; // ecx

  if ( this->GetRoleField(roleIdx, 21) == 1 || this->GetRoleField(roleIdx, 23) == 1 )
    return 0;
  result = this->ApplyDamage(7, dmg);
  if ( dmg <= 4 )
  {
    v6 = *(_DWORD *)(*(_DWORD *)&g_SceneMgr.m_slot[0]._tail[1408 * dmg + 16] + 764);
    if ( v6 > 1 )
      result /= v6;
  }
  if ( this->m_Role[0]._rest[892 * dmg + 532] )
    result *= 2;
  if ( result >= 0 )
  {
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    return ((g_RandSeed >> 16) & 0x7FFF) % 5 + 1;
  }
  return result;
}

// 0x004EF8B0
char CCBRoleState::RandSetEnemyPos(const void *arg0)
{
  char result; // al
  int a2[11]; // [esp+8h] [ebp-2Ch] BYREF

  result = 0;
  qmemcpy(a2, arg0, sizeof(a2));
  switch ( a2[0] )
  {
    case 0x103:
      result = sub_4F0A10((int)this, (int)a2);
      break;
    case 0x104:
      result = this->GetDeadRoleNumInForce((int)a2);
      break;
    case 0x105:
      result = this->GetAliveRoleNumInForce((int)a2);
      break;
    case 0x106:
      result = this->GetCastFightSkillSuccess((int)a2);
      break;
    case 0x10D:
      result = this->SetCoAttack((int)a2);
      break;
    case 0x10E:
      result = sub_4F1C40(this, (int)a2);
      break;
    default:
      return result;
  }
  return result;
}

// 0x004EF980
int CCBRoleState::CalcHealAmount(int roleIdx)
{
  int RoleHP; // eax
  char *v4; // eax
  int result; // eax
  int v6; // [esp+Ch] [ebp-Ch]

  *(_DWORD *)(roleIdx + 29) = 0;
  *(_DWORD *)(roleIdx + 33) = 0;
  *(_WORD *)(roleIdx + 37) = 0;
  *(_BYTE *)(roleIdx + 39) = 0;
  RoleHP = this->GetRoleHP(*(_DWORD *)(roleIdx + 12));
  this->GetRoleMP(RoleHP);
  v4 = (char *)&this->m_sCombatDialog[892 * *(_DWORD *)(roleIdx + 8)];
  if ( v4[651] )
  {
    v6 = 1;
  }
  else if ( v4[649] )
  {
    v6 = 2;
  }
  else
  {
    v6 = v4[650] != 0 ? 3 : 0;
  }
  result = v6;
  if ( v6 )
  {
    *(_BYTE *)(roleIdx + 17) = 1;
    *(_DWORD *)(roleIdx + 12) = -1;
  }
  else
  {
    *(_BYTE *)(roleIdx + 17) = 0;
  }
  return result;
}

// 0x004EFAF0
int CCBRoleState::WriteBackRoleData(int a2, _DWORD *a3, int *a4)
{
  int *v4; // edi
  int result; // eax
  int v7; // ebx
  char v8; // dl
  int v9; // eax
  int *v10; // esi
  char v11; // bl
  char v12; // al
  char v13; // dl
  int v14; // edi
  int v15; // esi
  int v16; // eax
  bool v17; // zf
  int v18; // [esp+10h] [ebp-2Ch] BYREF
  int v19; // [esp+14h] [ebp-28h]
  int v20; // [esp+18h] [ebp-24h]

  v4 = a4;
  *a4 = -1;
  *a3 = -1;
  if ( !*(_BYTE *)(a2 + 17) )
    return *(_DWORD *)(a2 + 12);
  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = (int *)&v18;
  do
  {
    if ( *(_BYTE *)(a2 + v9 + 29) )
    {
      *v10 = v9;
      ++v7;
      ++v10;
      if ( (unsigned int)v9 <= 4 )
      {
        v4 = a4;
        v8 = 1;
      }
    }
    ++v9;
  }
  while ( v9 < 11 );
  if ( v7 == 1 )
    return v18;
  if ( !v8 )
  {
    v11 = *(_BYTE *)(a2 + 37);
    if ( v11 && *(_BYTE *)(a2 + 38) )
    {
      *a3 = 8;
      *v4 = 9;
      return 100;
    }
    v12 = *(_BYTE *)(a2 + 34);
    if ( v12 && (*(_BYTE *)(a2 + 39) && *(_BYTE *)(a2 + 36) || !*(_BYTE *)(a2 + 39) && *(_BYTE *)(a2 + 36)) )
      return 10;
    v13 = *(_BYTE *)(a2 + 35);
    if ( v13 && !*(_BYTE *)(a2 + 39) )
      return 6;
    if ( v12 )
    {
      if ( *(_BYTE *)(a2 + 39) && !*(_BYTE *)(a2 + 36) )
      {
        *a3 = 5;
        *v4 = 10;
        return 100;
      }
    }
    else if ( *(_BYTE *)(a2 + 39) && *(_BYTE *)(a2 + 36) )
    {
      *a3 = 10;
      *v4 = 7;
      return 100;
    }
    if ( v11 && v12 )
      return 8;
    if ( *(_BYTE *)(a2 + 38) && *(_BYTE *)(a2 + 36) )
      return 9;
    if ( !*(_BYTE *)(a2 + 39) || !v13 )
      return v18;
    return 10;
  }
  v14 = v19;
  v15 = v18;
  if ( !this->WriteBackConfig(v18, v19) )
    goto LABEL_47;
  if ( v7 == 2 )
  {
    *a3 = v15;
    *a4 = v14;
    return 100;
  }
  if ( *(_DWORD *)&this->m_Role[0]._rest[892 * v15 + 508] == 6 )
    return v15;
  if ( *(_DWORD *)&this->m_Role[0]._rest[892 * v14 + 508] == 6 )
    return v14;
  result = v20;
  if ( *(_DWORD *)&this->m_Role[0]._rest[892 * v20 + 508] != 6 )
  {
LABEL_47:
    v16 = *(_DWORD *)&this->m_Role[0]._rest[892 * v15 + 508];
    if ( v16 != *(_DWORD *)&this->m_dwEXPTable[352] && v16 != *(_DWORD *)&this->m_dwEXPTable[360] )
    {
      v17 = v16 == *(_DWORD *)&this->m_dwEXPTable[368];
      result = v14;
      if ( !v17 )
        return result;
    }
    return v15;
  }
  return result;
}

// 0x004EFD70
bool CCBRoleState::WriteBackConfig(int roleIdx, int a3)
{
  int RoleHP; // ebp
  int v7; // eax
  bool result; // al
  int v9; // ecx
  char *v10; // eax
  int v11; // edx
  int v12; // eax
  char *i; // ecx
  int v14; // [esp+10h] [ebp-4h]
  int roleIdxa; // [esp+18h] [ebp+4h]
  int v16; // [esp+1Ch] [ebp+8h]

  v14 = -1;
  RoleHP = this->GetRoleHP(roleIdx);
  v7 = this->GetRoleHP(a3);
  roleIdxa = *(_DWORD *)&this->m_Role[0]._rest[892 * roleIdx + 508];
  v16 = *(_DWORD *)&this->m_Role[0]._rest[892 * a3 + 508];
  if ( roleIdx == a3 )
    return 1;
  if ( RoleHP != v7 )
    return 0;
  if ( RoleHP == 2 )
  {
    switch ( roleIdx )
    {
      case 5:
      case 7:
      case 10:
        return a3 == 5 || a3 == 10 || a3 == 7;
      case 8:
      case 9:
        if ( a3 != 9 && a3 != 8 )
          return 0;
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    v9 = 0;
    v10 = (char *)&this->m_dwEXPTable[316];
    do
    {
      v11 = 3;
      do
      {
        if ( *(_DWORD *)v10 == roleIdxa )
          v14 = v9;
        v10 += 4;
        --v11;
      }
      while ( v11 );
      ++v9;
    }
    while ( v9 < 3 );
    v12 = 0;
    for ( i = &this->m_dwEXPTable[12 * v14 + 316]; *(_DWORD *)i != v16; i += 4 )
    {
      if ( ++v12 >= 3 )
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004EFE90
bool CCBRoleState::ReviveAllFriendAtEnd(int roleIdx, int a3)
{
  int RoleHP; // ebp
  int v7; // eax
  bool result; // al
  int v9; // ecx
  char *v10; // eax
  int v11; // edx
  int v12; // eax
  char *i; // ecx
  int v14; // [esp+10h] [ebp-4h]
  int roleIdxa; // [esp+18h] [ebp+4h]
  int v16; // [esp+1Ch] [ebp+8h]

  v14 = -1;
  RoleHP = this->GetRoleHP(roleIdx);
  v7 = this->GetRoleHP(a3);
  roleIdxa = *(_DWORD *)&this->m_Role[0]._rest[892 * roleIdx + 508];
  v16 = *(_DWORD *)&this->m_Role[0]._rest[892 * a3 + 508];
  if ( roleIdx == a3 )
    return 1;
  if ( RoleHP != v7 )
    return 0;
  if ( RoleHP == 2 )
  {
    switch ( roleIdx )
    {
      case 5:
      case 8:
        if ( a3 != 8 && a3 != 5 )
          return 0;
        result = 1;
        break;
      case 6:
      case 10:
        if ( a3 != 10 && a3 != 6 )
          return 0;
        result = 1;
        break;
      case 7:
      case 9:
        return a3 == 9 || a3 == 7;
      default:
        return 0;
    }
  }
  else
  {
    v9 = 0;
    v10 = (char *)&this->m_dwEXPTable[352];
    do
    {
      v11 = 2;
      do
      {
        if ( *(_DWORD *)v10 == roleIdxa )
          v14 = v9;
        v10 += 4;
        --v11;
      }
      while ( v11 );
      ++v9;
    }
    while ( v9 < 3 );
    v12 = 0;
    for ( i = &this->m_dwEXPTable[8 * v14 + 352]; *(_DWORD *)i != v16; i += 4 )
    {
      if ( ++v12 >= 2 )
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004EFFC0
bool CCBRoleState::IsRoleReady(int roleIdx)
{
  int *v2; // eax

  v2 = (int *)&this->m_sCombatDialog[892 * roleIdx];
  return *((_BYTE *)v2 + 577)
      && !*((_BYTE *)v2 + 1432)
      && !*((_BYTE *)v2 + 1431)
      && v2[147] > 0
      && this->GetRoleField(roleIdx, 23) == 0;
}

// 0x004F0020
int CCBRoleState::SetEnemyBeImbibeNimbus(char a2, char a3)
{
  int v4; // ebp
  int v5; // esi
  int v6; // edi
  int v7; // ecx
  int result; // eax
  int v9; // ebp
  int v10; // edi
  int v11; // esi
  _DWORD v12[9]; // [esp+14h] [ebp-24h] BYREF

  memset(v12, 0xFFu, sizeof(v12));
  if ( !a3 )
    return -1;
  if ( a2 )
  {
    v4 = 0;
    if ( this->IsRoleReady(8) )
    {
      v12[0] = 8;
      v4 = 1;
    }
    if ( this->IsRoleReady(9) )
      v12[v4++] = 9;
    v5 = 0;
    if ( this->IsRoleReady(5) )
    {
      v12[3] = 5;
      v5 = 1;
    }
    if ( this->IsRoleReady(10) )
      v12[v5++ + 3] = 10;
    if ( this->IsRoleReady(7) )
      v12[v5++ + 3] = 7;
    v6 = 0;
    if ( this->IsRoleReady(6) )
    {
      v7 = 6;
      v6 = 1;
    }
    else
    {
      v7 = v12[6];
    }
    if ( v4 < v5 || (result = v12[0], v4 < v6) )
      result = -1;
    if ( v5 >= v4 && v5 >= v6 )
      result = v12[3];
    if ( v6 >= v4 && v6 >= v5 )
      return v7;
  }
  else
  {
    v9 = 0;
    if ( this->IsRoleReady(5) )
    {
      v12[0] = 5;
      v9 = 1;
    }
    if ( this->IsRoleReady(8) )
      v12[v9++] = 8;
    v10 = 0;
    if ( this->IsRoleReady(6) )
    {
      v12[3] = 6;
      v10 = 1;
    }
    if ( this->IsRoleReady(10) )
      v12[v10++ + 3] = 10;
    v11 = 0;
    if ( this->IsRoleReady(7) )
    {
      v12[6] = 7;
      v11 = 1;
    }
    if ( this->IsRoleReady(9) )
      v12[v11++ + 6] = 9;
    if ( v9 < v10 || (result = v12[0], v9 < v11) )
      result = -1;
    if ( v10 >= v9 && v10 >= v11 )
      result = v12[3];
    if ( v11 >= v9 && v11 >= v10 )
      return v12[6];
  }
  return result;
}

// 0x004F0210
bool CCBRoleState::CalSneakAttack(int a2, unsigned int a3)
{
  signed int v4; // esi
  int v5; // ebx
  char *v6; // esi

  if ( a2 < 5 || a2 >= 11 )
  {
LABEL_14:
    v4 = a3;
  }
  else
  {
    v4 = a3;
    if ( a3 <= 4 )
    {
      if ( this->m_Role[0]._rest[892 * a2 + 22] || this->m_Role[0]._rest[892 * a2 + 23] )
        return 1;
      if ( *(_DWORD *)&this->m_Role[0]._rest[892 * a3 + 508] == this->CheckDeath(*(_DWORD *)this->m_pCBSystem->m_pFightInfo->eSceneFiveMagic) )
      {
        v5 = 0;
        v6 = (char *)&this->m_Role[0]._rest[804];
        while ( !*(v6 - 855)
             || *v6
             || *(v6 - 1)
             || *((_DWORD *)v6 - 74) != 6
             || this->SetRoleField(v5, 0) <= 0 )
        {
          ++v5;
          v6 += 892;
          if ( v5 >= 5 )
            goto LABEL_14;
        }
        return 0;
      }
    }
  }
  return (unsigned int)a2 > 4
      || v4 < 5
      || v4 >= 11
      || this->m_Role[0]._rest[892 * a2 + 22]
      || this->m_Role[0]._rest[892 * a2 + 23]
      || v4 != 6
      || !this->m_Role[9]._rest[805]
      || this->m_Role[10]._rest[764]
      || this->m_Role[10]._rest[763]
      || this->SetRoleField(10, 0) <= 0;
}

// 0x004F0360
unsigned int CCBRoleState::InitRoleFiveMagic(int a2)
{
  unsigned int result; // eax

  result = *(unsigned __int8 *)(((PAL_GDB *)&g_GDB)->GDB_GetItemNum(*(_DWORD *)(a2 + 4)) + 592);
  switch ( result )
  {
    case 0u:
      goto LABEL_12;
    case 1u:
      this->GetRoleMP(1);
      *(_BYTE *)(a2 + 17) = 1;
      *(_DWORD *)(a2 + 29) = 0;
      *(_DWORD *)(a2 + 33) = 0;
      *(_WORD *)(a2 + 37) = 0;
      *(_BYTE *)(a2 + 39) = 0;
      result = 0;
      goto LABEL_14;
    case 2u:
      result = *(_DWORD *)(a2 + 12);
      if ( result <= 4 )
      {
        this->GetRoleMP(2);
        result = *(_DWORD *)(a2 + 12);
        if ( result <= 4 )
        {
          result = 0;
          *(_DWORD *)(a2 + 12) = 0;
        }
      }
      if ( *(_DWORD *)(a2 + 12) != -1 )
        goto LABEL_12;
      result = 0;
      break;
    case 3u:
      this->GetRoleMP(2);
      *(_BYTE *)(a2 + 17) = 1;
      *(_DWORD *)(a2 + 29) = 0;
      *(_DWORD *)(a2 + 33) = 0;
      *(_WORD *)(a2 + 37) = 0;
      *(_BYTE *)(a2 + 39) = 0;
      result = 0;
LABEL_14:
      *(_DWORD *)(a2 + 12) = -1;
      return result;
    default:
      return result;
  }
  while ( !*(_BYTE *)(result + a2 + 29) )
  {
    if ( (int)++result >= 11 )
    {
      *(_BYTE *)(a2 + 17) = 0;
      return result;
    }
  }
  *(_DWORD *)(a2 + 12) = result;
LABEL_12:
  *(_BYTE *)(a2 + 17) = 0;
  return result;
}

// 0x004F05A0
char CCBRoleState::CCBRoleState::sub_4F05A0(_DWORD *a1)
{
  char v1; // al
  char result; // al
  char v3; // al

  switch ( *a1 )
  {
    case 0x104:
    case 0x105:
    case 0x10D:
      v1 = *(_BYTE *)(((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(a1[1]) + 577);
      goto LABEL_4;
    case 0x106:
      v1 = *(_BYTE *)(((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(a1[1]) + 629);
LABEL_4:
      if ( v1 != 2 && v1 != 4 )
        goto LABEL_10;
      result = 1;
      break;
    case 0x10E:
      v3 = *(_BYTE *)(((PAL_GDB *)&g_GDB)->GDB_GetItemNum(a1[1]) + 592);
      if ( v3 != 1 && v3 != 3 )
        goto LABEL_10;
      result = 1;
      break;
    default:
LABEL_10:
      result = 0;
      break;
  }
  return result;
}

// 0x004F0640
bool CCBRoleState::InitRoleSpecEquipAttrib(int a2)
{
  unsigned int v2; // eax
  int *v3; // eax
  int v5; // edx
  int *i; // eax

  v2 = *(_DWORD *)(a2 + 12);
  if ( v2 > 0xA )
  {
    v5 = 0;
    for ( i = &this->m_Role[0].nHP;
          !*(_BYTE *)(a2 + v5 + 29) || !*((_BYTE *)i - 11) || *i <= 0 || *((_BYTE *)i + 844);
          i += 223 )
    {
      if ( ++v5 >= 11 )
        return 1;
    }
    return 0;
  }
  v3 = (int *)&this->m_sCombatDialog[892 * v2];
  return v3[147] <= 0 || *((_BYTE *)v3 + 1432);
}

// 0x004F0700
char CCBRoleState::UnloadWeaponModel(int a2)
{
  int v3; // esi
  char *i; // edi

  v3 = 0;
  for ( i = &this->m_Role[0]._rest[508]; !*(i - 559) || *(_DWORD *)i != a2 || this->SetVisible(v3); i += 892 )
  {
    if ( ++v3 >= 5 )
      return 0;
  }
  return 1;
}

// 0x004F0750
bool CCBRoleState::SetVisible(int roleIdx)
{
  if ( !*(&this->m_Role[0].bAlive + 892 * roleIdx) )
    return 0;
  if ( this->GetRoleField(roleIdx, 14) )
    return 0;
  if ( this->GetRoleField(roleIdx, 18) )
    return 0;
  if ( this->GetRoleField(roleIdx, 19) )
    return 0;
  return this->GetRoleField(roleIdx, 17) == 0;
}

// 0x004F07D0
char CCBRoleState::GetRole(int a1, int a2)
{
  switch ( a1 )
  {
    case 1:
      if ( a2 == 1 )
        return 1;
      break;
    case 2:
      if ( a2 == 2 )
        return 1;
      break;
    case 4:
      if ( a2 == 4 )
        return 1;
      break;
    case 3:
      if ( a2 == 3 )
        return 1;
      break;
    default:
      if ( a1 == 5 && a2 == 5 )
        return 1;
      break;
  }
  return 0;
}

// 0x004F0830
unsigned __int8 CCBRoleState::GetRoleNum(int *a2)
{
  int v2; // eax
  int SkillNum; // ebp
  unsigned __int8 result; // al
  int RoleHP; // eax
  int RoleNum; // ebp

  v2 = *a2;
  if ( *a2 == 261 || v2 == 260 || v2 == 269 )
  {
    RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(a2[1]);
    result = *(_BYTE *)(RoleNum + 577);
    if ( result && result <= 4u )
    {
      if ( result != 1 && result != 3 )
      {
        RoleHP = this->GetRoleHP(a2[2]);
        if ( *(_BYTE *)(RoleNum + 577) > 2u )
          RoleHP = RoleHP->IsForce1();
        goto LABEL_10;
      }
      goto LABEL_18;
    }
  }
  else
  {
    SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(a2[1]);
    result = *(_BYTE *)(SkillNum + 629);
    if ( result && result <= 4u )
    {
      if ( result != 1 && result != 3 )
      {
        RoleHP = this->GetRoleHP(a2[2]);
        if ( *(_BYTE *)(SkillNum + 629) > 2u )
          RoleHP = RoleHP->IsForce1();
LABEL_10:
        this->GetRoleMP(RoleHP);
        *((_BYTE *)a2 + 17) = 1;
        return 0;
      }
LABEL_18:
      *((_BYTE *)a2 + 17) = 0;
      return result;
    }
  }
  return ((CCBSystem *)this->m_pCBSystem)->CreateObj(byte_5D8EC8, 0, 0x40u);
}

// 0x004F1070
char CCBRoleState::GetAliveRoleNumInForce(int a2)
{
  int v3; // edi
  int v4; // ecx
  _DWORD *v5; // esi
  CCBStage *m_pStage; // ecx
  int RoleIndex; // edi
  int v8; // esi
  int v9; // eax
  int v10; // ecx
  bool v11; // cc
  unsigned int v12; // eax
  int v13; // edx
  char v14; // al
  int v16; // [esp+0h] [ebp-90h]
  _DWORD v17[11]; // [esp+Ch] [ebp-84h] BYREF
  _DWORD a3[11]; // [esp+38h] [ebp-58h] BYREF
  int roleIdx[3]; // [esp+64h] [ebp-2Ch] BYREF
  int v20; // [esp+70h] [ebp-20h]
  int v21; // [esp+74h] [ebp-1Ch]
  float v22; // [esp+78h] [ebp-18h]
  int v23; // [esp+7Ch] [ebp-14h]
  int v24; // [esp+80h] [ebp-10h] BYREF
  int v25; // [esp+84h] [ebp-Ch] BYREF
  char *v26; // [esp+88h] [ebp-8h]
  int idx; // [esp+8Ch] [ebp-4h]

  memset(v17, 0, sizeof(v17));
  v3 = 0;
  v4 = 24;
  v21 = 0;
  v25 = 0;
  v24 = 6;
  idx = 0;
  v23 = 24;
  v26 = (char *)&this->m_Role[0]._rest[464];
  do
  {
    v5 = (_DWORD *)a2;
    if ( *(_BYTE *)(a2 + 17) )
    {
      if ( !*(_BYTE *)(v3 + a2 + 29) )
        goto LABEL_27;
    }
    else if ( *(_DWORD *)(a2 + 12) != v3 )
    {
      goto LABEL_27;
    }
    if ( ((CCBStageRole *)*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + v4))->ForceEndTaskByPFN()
      || *(_WORD *)(((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*(_DWORD *)(a2 + 4)) + 666) == 2 )
    {
      if ( this->GetRoleField(v3, 22) )
        goto LABEL_27;
      qmemcpy(v17, (const void *)a2, sizeof(v17));
      v17[3] = idx;
      if ( this->VarianceRoundCounter(v17) )
      {
        v8 = idx;
        v21 = sub_4F2660(this, (_DWORD *)a2, idx);
        if ( v21 < 0
          && !((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->IsCmdEmpty(v8)
          && !((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->IsCmdReady(v8) )
        {
          ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*(_DWORD *)(a2 + 4));
          ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdData(v8);
        }
        if ( v23 >= 44 && v23 < 68 && this->SetRoleField(idx, 0) <= 0 )
        {
          if ( (unsigned __int8)this->Revive(v16) )
          {
            v9 = ((PAL_GDB *)&g_GDB)->~PAL_GDB(*((_DWORD *)v26 - 135));
            if ( v9 )
            {
              if ( *(_DWORD *)(v9 + 832) )
              {
                if ( *(_DWORD *)(v9 + 836) == *(_DWORD *)(a2 + 4) )
                {
                  v10 = *(__int16 *)(v9 + 840);
                  v22 = *(float *)&v10;
                  if ( v10 > 0 )
                  {
                    v22 = (double)SLODWORD(v22) * 10.24;
                    v20 = (int)v22;
                    ++g_nRandCallCount;
                    g_RandSeed = 214013 * g_RandSeed + 2531011;
                    if ( ((g_RandSeed >> 16) & 0x3FF) < v20 )
                      *(_DWORD *)v26 = *(_DWORD *)(v9 + 832);
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      memset(a3, 0, sizeof(a3));
      a3[2] = idx;
      m_pStage = (CCBStage *)this->m_pStage;
      LOBYTE(a3[10]) = 1;
      a3[1] = 0;
      RoleIndex = m_pStage->GetRoleIndex(7, a3, 1);
      if ( RoleIndex == -1 )
        goto LABEL_27;
      this->CheckRoleStatus((int)roleIdx);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::SelectRole, 0, 0, 0, roleIdx, 0, 1065353216);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
    }
    v5 = (_DWORD *)a2;
LABEL_27:
    v4 = v23 + 4;
    v3 = idx + 1;
    v11 = v23 + 4 < 68;
    ++idx;
    v23 += 4;
    v26 += 892;
  }
  while ( v11 );
  this->SetRoleHP(v5[2], v5[1]);
  v12 = v5[2];
  if ( v12 <= 4 )
  {
    sub_4F6C60(this->m_sCombatDialog, v12, v5[1], &v24, &v25);
    v13 = v25 + 892 * v5[2] + 8 * v24 + 984;
    v14 = this->m_sCombatDialog[v13];
    if ( v14 != -1 )
      this->m_sCombatDialog[v13] = v14 + 1;
  }
  if ( *(&this->m_Role[0].dwID + 223 * v5[2]) == 7312 && *v5 == 261 && v5[1] == 210 )
    sub_4F90F0(this, v5[2]);
  return 1;
}

// 0x004F1420
char CCBRoleState::GetDeadRoleNumInForce(int a2)
{
  int v3; // edx
  CCBStage *v4; // ecx
  int v5; // esi
  CCBStage *m_pStage; // ecx
  int RoleIndex; // esi
  int v8; // esi
  int v9; // eax
  int v10; // ecx
  bool v11; // cc
  int v13; // [esp+0h] [ebp-C0h]
  _DWORD v14[11]; // [esp+Ch] [ebp-B4h] BYREF
  _DWORD v15[11]; // [esp+38h] [ebp-88h] BYREF
  _DWORD a3[11]; // [esp+64h] [ebp-5Ch] BYREF
  int a7[3]; // [esp+90h] [ebp-30h] BYREF
  int roleIdx[3]; // [esp+9Ch] [ebp-24h] BYREF
  int v19; // [esp+A8h] [ebp-18h]
  int v20; // [esp+ACh] [ebp-14h]
  float v21; // [esp+B0h] [ebp-10h]
  char *v22; // [esp+B4h] [ebp-Ch]
  int v23; // [esp+B8h] [ebp-8h]
  int idx; // [esp+BCh] [ebp-4h]

  v3 = 0;
  memset(v14, 0, sizeof(v14));
  v20 = 0;
  idx = 0;
  v23 = 24;
  v22 = (char *)&this->m_Role[0]._rest[464];
  do
  {
    if ( *(_BYTE *)(a2 + 17) )
    {
      if ( !*(_BYTE *)(v3 + a2 + 29) )
        goto LABEL_30;
    }
    else if ( *(_DWORD *)(a2 + 12) != v3 )
    {
      goto LABEL_30;
    }
    qmemcpy(v14, (const void *)a2, sizeof(v14));
    v14[3] = v3;
    if ( this->VarianceRoundCounter(v14) )
    {
      if ( ((CCBRoleState *)a2)->sub_4F05A0()
        || ((CCBStageRole *)*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + v23))->ForceEndTaskByPFN()
        || *(_WORD *)(((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*(_DWORD *)(a2 + 4)) + 666) == 2 )
      {
        v8 = idx;
        v20 = sub_4F2690(this, (_DWORD *)a2, idx);
        if ( v20 < 0
          && !((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->IsCmdEmpty(v8)
          && !((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->IsCmdReady(v8) )
        {
          ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdData(v8);
        }
        if ( *(_DWORD *)(a2 + 4) == 4101 )
          this->GetFirstAliveRoleInForce(0, *(_DWORD *)(a2 + 12));
        if ( v23 >= 44 && v23 < 68 && this->SetRoleField(idx, 0) <= 0 )
        {
          if ( (unsigned __int8)this->Revive(v13) )
          {
            v9 = ((PAL_GDB *)&g_GDB)->~PAL_GDB(*((_DWORD *)v22 - 135));
            if ( v9 )
            {
              if ( *(_DWORD *)(v9 + 832) )
              {
                if ( *(_DWORD *)(v9 + 836) == *(_DWORD *)(a2 + 4) )
                {
                  v10 = *(__int16 *)(v9 + 840);
                  v21 = *(float *)&v10;
                  if ( v10 > 0 )
                  {
                    v21 = (double)SLODWORD(v21) * 10.24;
                    v19 = (int)v21;
                    ++g_nRandCallCount;
                    g_RandSeed = 214013 * g_RandSeed + 2531011;
                    if ( ((g_RandSeed >> 16) & 0x3FF) < v19 )
                      *(_DWORD *)v22 = *(_DWORD *)(v9 + 832);
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        memset(v15, 0, sizeof(v15));
        m_pStage = (CCBStage *)this->m_pStage;
        LOBYTE(v15[10]) = 1;
        v15[2] = idx;
        v15[1] = 0;
        RoleIndex = m_pStage->GetRoleIndex(7, v15, 1);
        if ( RoleIndex != -1 )
        {
          this->CheckRoleStatus((int)a7);
          ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::SelectRole, 0, 0, 0, a7, 0, 1065353216);
          ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
        }
      }
    }
    else
    {
      memset(a3, 0, sizeof(a3));
      v4 = (CCBStage *)this->m_pStage;
      a3[1] = 0;
      LOBYTE(a3[10]) = 1;
      a3[2] = idx;
      v5 = v4->GetRoleIndex(7, a3, 1);
      if ( v5 != -1 )
      {
        this->CheckRoleStatus((int)roleIdx);
        ((CCBStage *)this->m_pStage)->GetRoleName(v5, (int)CCBStage::SelectRole, 0, 0, 0, roleIdx, 0, 1065353216);
        ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v5);
      }
    }
LABEL_30:
    v3 = idx + 1;
    v11 = v23 + 4 < 68;
    ++idx;
    v23 += 4;
    v22 += 892;
  }
  while ( v11 );
  this->SetRoleHP(*(_DWORD *)(a2 + 8), *(_DWORD *)(a2 + 4));
  return 1;
}

// 0x004F17C0
char CCBRoleState::GetFirstAliveRoleInForce(int roleIdx, int arg4)
{
  int v4; // ebp
  int v5; // eax
  char *v6; // esi
  int v7; // ecx
  int v8; // edi
  int RoleIndex; // eax
  int v10; // ecx
  int v11; // edi
  char *Instance; // eax
  int SkillNum; // eax
  int a7; // [esp+10h] [ebp-44h] BYREF
  int v16; // [esp+14h] [ebp-40h]
  int v17; // [esp+18h] [ebp-3Ch]
  int v18; // [esp+1Ch] [ebp-38h] BYREF
  int v19; // [esp+20h] [ebp-34h]
  int v20; // [esp+24h] [ebp-30h]
  _DWORD a3[11]; // [esp+28h] [ebp-2Ch] BYREF

  a7 = 0;
  v16 = 0;
  v17 = 0;
  memset(a3, 0, sizeof(a3));
  v4 = -1;
  a3[3] = arg4;
  v18 = 0xFFFF;
  v19 = 0;
  v20 = 0;
  v5 = *(_DWORD *)&this->m_Role[0]._rest[892 * arg4 + 468];
  LOBYTE(a3[10]) = 1;
  v6 = (char *)&this->m_sCombatDialog[892 * arg4];
  a3[0] = 260;
  a3[1] = 0;
  if ( v5 > 0 )
  {
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    v7 = *((_DWORD *)v6 + 274);
    v8 = ((g_RandSeed >> 16) & 0x7FFF) % v7 + 1;
    *((_DWORD *)v6 + 274) = v7 - v8;
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(28, a3, 1);
    v4 = RoleIndex;
    if ( RoleIndex != -1 )
    {
      a7 = 1;
      v17 = v8;
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)sub_5027E0, 0, 0, 0, &a7, -1082130432, 0x40000000);
      this->CheckBuff(roleIdx);
    }
  }
  if ( *((_DWORD *)v6 + 275) && *((int *)v6 + 276) > 0 )
  {
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    v10 = *((_DWORD *)v6 + 276);
    v11 = ((g_RandSeed >> 16) & 0x7FFF) % v10 + 1;
    *((_DWORD *)v6 + 276) = v10 - v11;
    if ( v4 == -1 )
    {
      v4 = ((CCBStage *)this->m_pStage)->GetRoleIndex(28, a3, 1);
      if ( v4 == -1 )
        return 0;
    }
    Instance = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(aWa006, 1);
    v16 = *((_DWORD *)v6 + 275);
    a7 = 0;
    v17 = v11;
    ((CCBStage *)this->m_pStage)->GetRoleName(v4, (int)sub_5027E0, 0, 0, 0, &a7, -1082130432, 0x40000000);
    SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(*((_DWORD *)v6 + 275));
    v18 = *((_DWORD *)v6 + 275);
    v20 = SkillNum;
    v19 = v11;
    CCBStageRole_GetAlive((int)&g_SceneMgr._gap_1888[760], &v18);
  }
  if ( v4 != -1 )
  {
    ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v4);
    return 1;
  }
  return 0;
}

// 0x004F1A30
char CCBRoleState::GetCastFightSkillSuccess(int a2)
{
  int v4; // esi
  int i; // ebp
  int v6; // eax
  int a2a; // [esp+14h] [ebp+4h]

  a2a = *(_DWORD *)(a2 + 8);
  v4 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( *(_BYTE *)(a2 + 17) )
    {
      if ( !*(_BYTE *)(v4 + a2 + 29) )
        goto LABEL_13;
    }
    else if ( *(_DWORD *)(a2 + 12) != v4 )
    {
      goto LABEL_13;
    }
    if ( (((CCBRoleState *)a2)->sub_4F05A0()
       || ((CCBStageRole *)*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + i))->ForceEndTaskByPFN()
       || *(_WORD *)(((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(*(_DWORD *)(a2 + 4)) + 748) == 2)
      && sub_4F2750(this, (_DWORD *)a2, v4) < 0
      && !((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->IsCmdEmpty(v4)
      && !((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->IsCmdReady(v4) )
    {
      ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdData(v4);
    }
LABEL_13:
    ++v4;
  }
  v6 = *((_DWORD *)this->m_pUI + 280);
  if ( *(_DWORD *)(v6 + 56) == 1 )
    sub_4F95F0(this, a2a, *(_DWORD *)(v6 + 104));
  return 1;
}

// 0x004F1B20
char CCBRoleState::SetCoAttack(int a2)
{
  unsigned int v4; // edi
  int i; // [esp+14h] [ebp+4h]

  v4 = 0;
  for ( i = 24; i < 68; i += 4 )
  {
    if ( *(_BYTE *)(a2 + 17) )
    {
      if ( !*(_BYTE *)(v4 + a2 + 29) )
        goto LABEL_12;
    }
    else if ( *(_DWORD *)(a2 + 12) != v4 )
    {
      goto LABEL_12;
    }
    if ( (((CCBRoleState *)a2)->sub_4F05A0()
       || ((CCBStageRole *)*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + i))->ForceEndTaskByPFN())
      && sub_4F27B0(this, (_DWORD *)a2, v4) < 0
      && !((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->IsCmdEmpty(v4)
      && !((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->IsCmdReady(v4) )
    {
      ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdData(v4);
    }
LABEL_12:
    ++v4;
  }
  this->SetRoleHP(*(_DWORD *)(a2 + 8), *(_DWORD *)(a2 + 4));
  sub_43FE90(*((_DWORD *)this->m_pUI + 267));
  ((UIWnd *)*((UIWnd **)this->m_pUI + 267))->FindChild(50.0);
  ((UIWnd *)*((UIWnd **)this->m_pUI + 267))->FindChildByName(0.0);
  *(_DWORD *)&this->m_Role[0]._rest[892 * *(_DWORD *)(a2 + 8) + 460] = 0;
  return 1;
}

// 0x004F1CC0
char CCBRoleState::CanBeImbibeNimbus(int arg0, unsigned int a2)
{
  char result; // al
  char *v6; // [esp+Ch] [ebp-4h]
  int dmg; // [esp+18h] [ebp+8h]
  float dmga; // [esp+18h] [ebp+8h]

  if ( arg0 < 5 )
    return 0;
  if ( arg0 >= 11 )
    return 0;
  v6 = (char *)&this->m_sCombatDialog[892 * arg0];
  if ( !v6[577] )
    return 0;
  dmg = this->ApplyDamage(4, arg0);
  if ( dmg <= 0 )
    return 0;
  dmga = (double)dmg * 10.24;
  ++g_nRandCallCount;
  g_RandSeed = 214013 * g_RandSeed + 2531011;
  if ( ((g_RandSeed >> 16) & 0x3FF) >= (int)dmga )
    return 0;
  switch ( *((_DWORD *)v6 + 160) )
  {
    case 0x385:
      this->ProcessRound(a2);
      goto LABEL_8;
    case 0x386:
    case 0x387:
    case 0x388:
    case 0x389:
    case 0x38A:
    case 0x38B:
    case 0x38C:
    case 0x38D:
    case 0x38E:
    case 0x38F:
    case 0x394:
    case 0x395:
    case 0x396:
    case 0x397:
    case 0x398:
    case 0x399:
    case 0x39E:
    case 0x39F:
    case 0x3A0:
      this->ProcessRound(a2);
      result = 1;
      break;
    case 0x390:
      this->GetMaxHP(a2);
      this->GetMaxMP(a2);
      result = 1;
      break;
    case 0x391:
      result = this->CheckRoleValid(arg0, a2, 27);
      break;
    case 0x392:
      result = this->CheckRoleValid(arg0, a2, 28);
      break;
    case 0x393:
      result = this->CheckRoleValid(arg0, a2, 1);
      break;
    case 0x3A1:
      result = this->CheckRoleValid(arg0, a2, 30);
      break;
    default:
LABEL_8:
      result = 1;
      break;
  }
  return result;
}

// 0x004F1FA0
char CCBRoleState::CheckRoleValid(int a2, unsigned int roleIdx, int a4)
{
  char result; // al
  CCBSystem *m_pCBSystem; // edx
  CCBStage *m_pStage; // ecx
  int RoleIndex; // edi
  CCBSystem *v9; // ecx
  int v10; // edi
  int v11; // edi
  _DWORD *TargetRole; // eax
  _DWORD a7[3]; // [esp+10h] [ebp-70h] BYREF
  _DWORD pOut[3]; // [esp+1Ch] [ebp-64h] BYREF
  _DWORD a6[11]; // [esp+28h] [ebp-58h] BYREF
  _DWORD a3[11]; // [esp+54h] [ebp-2Ch] BYREF

  switch ( a4 )
  {
    case 1:
      return this->CanRoleAct(roleIdx);
    case 2:
      m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
      if ( LOBYTE(m_pCBSystem->m_pFightInfo->nRoleWillNotBeAttack) )
      {
        memset(a3, 0, sizeof(a3));
        a3[2] = a2;
        m_pStage = (CCBStage *)this->m_pStage;
        LOBYTE(a3[10]) = 1;
        a3[0] = 267;
        a3[1] = 0;
        a3[3] = -1;
        RoleIndex = m_pStage->GetRoleIndex(26, a3, 1);
        if ( RoleIndex != -1 )
        {
          memset(a7, 0, sizeof(a7));
          ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)sub_5024D0, 0, 0, 0, a7, 0, 1077936128);
          ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
        }
        goto LABEL_6;
      }
      this->m_bFleeAlwaysSuccess = 1;
      memset(a6, 0, sizeof(a6));
      LOBYTE(a6[10]) = 1;
      LOWORD(a6[4]) = 0;
      a6[1] = m_pCBSystem->ProcProtect();
      a6[3] = roleIdx;
      a6[2] = a2;
      v9 = (CCBSystem *)this->m_pCBSystem;
      a6[0] = 267;
      v9->CreateObj((int (*)(int, int))CCBSystem::PassCmdToThread, 0, 0, 0, a6);
      return 1;
    case 24:
    case 30:
      return 1;
    case 25:
      sub_4F2390(this);
      return 1;
    case 27:
      if ( roleIdx > 4 )
        return 1;
      v10 = this->GetTotalRounds() / 200;
      v11 = v10 - this->GetTotalRounds() / 100;
      if ( v11 > 0 )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        v11 = ((g_RandSeed >> 16) & 0x7FFF) % v11;
      }
      if ( v11 + this->GetTotalRounds() / 200 <= 0 )
        return 1;
      this->CheckBuff(roleIdx);
      return 1;
    case 28:
      if ( roleIdx > 4 )
        return 1;
      if ( CCBStageRole_CheckValid((int *)&g_SceneMgr._gap_1888[760], 14) <= 0 )
        goto LABEL_6;
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      TargetRole = ((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(pOut);
      CCBStageRole_PassCmd(&g_SceneMgr._gap_1888[760], TargetRole);
      result = 1;
      break;
    case 29:
      if ( this->Update(2) == 1 )
        sub_4F8FD0(this, a2, roleIdx);
      return 1;
    default:
LABEL_6:
      result = 0;
      break;
  }
  return result;
}

// 0x004F2310
char CCBRoleState::CheckRoleNimbus(int a2, unsigned int a3)
{
  int SkillNum; // eax

  SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(*(_DWORD *)(a2 + 4));
  return this->CheckRoleValid(*(_DWORD *)(a2 + 8), a3, *(unsigned __int8 *)(SkillNum + 628));
}

// 0x004F2350
char CCBRoleState::CanBeSelect(int a2, unsigned int a3)
{
  int RoleNum; // eax

  RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*(_DWORD *)(a2 + 4));
  return this->CheckRoleValid(*(_DWORD *)(a2 + 8), a3, *(unsigned __int8 *)(RoleNum + 578));
}

// 0x004F2910
int CCBRoleState::SetRoleHP(int roleIdx, int value)
{
  int RoleNum; // ebx
  int result; // eax
  int v6; // ebx
  int v7; // [esp+10h] [ebp-18h] BYREF
  int v8; // [esp+14h] [ebp-14h]
  int v9; // [esp+18h] [ebp-10h]
  int roleIdxa[3]; // [esp+1Ch] [ebp-Ch] BYREF

  v7 = 0xFFFF;
  v8 = 0;
  v9 = 0;
  RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(value);
  this->CalcAttackPower(roleIdx);
  this->CalcDefensePower(roleIdx);
  result = *(_DWORD *)(RoleNum + 696);
  if ( result != -1 )
  {
    switch ( result )
    {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
        result = ((CCBSystem *)this->m_pCBSystem)->CreateObj(byte_5D8F0C, 0, 0x40u);
        break;
      case 5:
        LOBYTE(result) = this->CanUseSkill(roleIdx);
        break;
      case 6:
        result = (int)&this->m_Role[0]._rest[892 * roleIdx + 80];
        *(_DWORD *)result -= *(_DWORD *)(RoleNum + 704);
        break;
      case 7:
        result = this->GetRoleLevel(roleIdx);
        break;
      case 8:
        result = (int)(&this->m_Role[0].nSpeed + 223 * roleIdx);
        *(_DWORD *)result -= *(_DWORD *)(RoleNum + 704);
        break;
      case 9:
        result = ((CCBSystem *)this->m_pCBSystem)->CreateObj(byte_5D8EF8, 0, 0x40u);
        break;
      case 10:
        LOBYTE(result) = this->CheckBuff(roleIdx);
        break;
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
        result = ((CCBSystem *)this->m_pCBSystem)->CreateObj(byte_5D8EE0, 0, 0x40u);
        break;
      case 16:
        v7 = 6113;
        result = (int)CCBStageRole_GetByIndex(&g_SceneMgr._gap_1888[760], &v7);
        if ( result )
        {
          v9 = *(_DWORD *)(result + 8);
          v8 = 1;
          v7 = 6113;
          CCBStageRole_PassCmd(&g_SceneMgr._gap_1888[760], &v7);
          result = ((CCBStage *)this->m_pStage)->GetRoleIndex(8, 0, 1);
          v6 = result;
          if ( result != -1 )
          {
            this->CheckRoleStatus((int)roleIdxa);
            ((CCBStage *)this->m_pStage)->GetRoleName(v6, (int)CCBStage::ProcWait, 0, 0, 0, roleIdxa, 0, 1080033280);
            LOBYTE(result) = ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v6);
          }
        }
        break;
      default:
        return result;
    }
  }
  return result;
}

// 0x004F2BB0
int CCBRoleState::SetRoleField(int roleIdx, int value)
{
  if ( (_BYTE)value == 1 )
    return *(&this->m_Role[0].nFullHP + 223 * roleIdx);
  else
    return *(&this->m_Role[0].nHP + 223 * roleIdx);
}

// 0x004F3020
int CCBRoleState::CalcAttackPower(int roleIdx)
{
  int v2; // edi
  LPARAM v4; // edx
  char *v5; // esi
  int v6; // eax
  int v7; // ecx
  CCBStage *m_pStage; // ecx
  int RoleIndex; // edi
  int v10; // esi
  CCBSystem *m_pCBSystem; // ebx
  _DWORD a3[11]; // [esp+Ch] [ebp-40h] BYREF
  int roleIdxa[3]; // [esp+38h] [ebp-14h] BYREF
  int v15; // [esp+44h] [ebp-8h]
  int v16; // [esp+48h] [ebp-4h]
  int v17; // [esp+58h] [ebp+Ch]
  float v18; // [esp+58h] [ebp+Ch]
  char v19; // [esp+5Ch] [ebp+10h]

  v2 = v17;
  if ( !v17 )
    return 0;
  v4 = roleIdx;
  v5 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  if ( !v5[578] )
    return 0;
  v16 = *((_DWORD *)v5 + 149);
  if ( v17 < 0 )
  {
    v18 = (double)v17 * *((float *)v5 + 164) * 0.0099999998;
    v15 = (int)v18;
    v2 -= v15;
    v17 = v2;
  }
  v6 = v2 + *((_DWORD *)v5 + 149);
  *((_DWORD *)v5 + 149) = v6;
  v7 = *((_DWORD *)v5 + 150);
  if ( v6 <= v7 )
    v7 = v6 < 0 ? 0 : v6;
  *((_DWORD *)v5 + 149) = v7;
  if ( v19 )
  {
    memset(a3, 0, sizeof(a3));
    m_pStage = (CCBStage *)this->m_pStage;
    a3[2] = roleIdx;
    a3[3] = roleIdx;
    LOBYTE(a3[10]) = 1;
    a3[0] = 259;
    a3[1] = 0;
    LOWORD(a3[4]) = 0;
    RoleIndex = m_pStage->GetRoleIndex(6, a3, 1);
    if ( RoleIndex != -1 )
    {
      if ( v17 <= 0 )
      {
        if ( v16 + v17 < 0 )
          v17 = -v16;
      }
      else
      {
        v10 = *((_DWORD *)v5 + 150) - v16;
        if ( v17 > v10 )
          v17 = v10;
      }
      this->CheckRoleStatus((int)roleIdxa);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::GetRoleTaskNum, 0, 0, 0, roleIdxa, -1082130432, 1075838976);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
    }
    v4 = roleIdx;
    v2 = v17;
  }
  m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
  if ( BYTE1(m_pCBSystem->m_nTimesOfCombat) )
    sub_4E2AE0((int *)m_pCBSystem->m_pEditor, v4);
  return v2;
}

// 0x004F31C0
int CCBRoleState::CalcDefensePower(int roleIdx)
{
  int v2; // edi
  char *v4; // esi
  int v5; // eax
  int v6; // ecx
  CCBStage *m_pStage; // ecx
  int RoleIndex; // edi
  int v9; // esi
  CCBSystem *m_pCBSystem; // ebx
  _DWORD a3[11]; // [esp+Ch] [ebp-40h] BYREF
  _DWORD a7[3]; // [esp+38h] [ebp-14h] BYREF
  int v14; // [esp+44h] [ebp-8h]
  int v15; // [esp+48h] [ebp-4h]
  int v16; // [esp+58h] [ebp+Ch]
  float v17; // [esp+58h] [ebp+Ch]
  char v18; // [esp+5Ch] [ebp+10h]

  v2 = v16;
  if ( !v16 )
    return 0;
  v4 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  if ( !v4[578] || this->GetRoleField(roleIdx, 23) && v16 > 0 )
    return 0;
  v15 = *((_DWORD *)v4 + 151);
  if ( v16 < 0 )
  {
    v17 = (double)v16 * *((float *)v4 + 165) * 0.0099999998;
    v14 = (int)v17;
    v2 -= v14;
    v16 = v2;
  }
  v5 = v2 + *((_DWORD *)v4 + 151);
  *((_DWORD *)v4 + 151) = v5;
  v6 = *((_DWORD *)v4 + 152);
  if ( v5 <= v6 )
    v6 = v5 < 0 ? 0 : v5;
  *((_DWORD *)v4 + 151) = v6;
  if ( v18 )
  {
    memset(a3, 0, sizeof(a3));
    m_pStage = (CCBStage *)this->m_pStage;
    a3[2] = roleIdx;
    a3[3] = roleIdx;
    LOBYTE(a3[10]) = 1;
    a3[0] = 259;
    a3[1] = 0;
    LOWORD(a3[4]) = 0;
    RoleIndex = m_pStage->GetRoleIndex(6, a3, 1);
    if ( RoleIndex != -1 )
    {
      if ( v16 <= 0 )
      {
        if ( v15 + v16 < 0 )
          v16 = -v15;
      }
      else
      {
        v9 = *((_DWORD *)v4 + 152) - v15;
        if ( v16 > v9 )
          v16 = v9;
      }
      this->CheckRoleStatus((int)a7);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::GetRoleTaskNum, 0, 0, 0, a7, -1082130432, 1075838976);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
    }
    v2 = v16;
  }
  m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
  if ( BYTE1(m_pCBSystem->m_nTimesOfCombat) )
    sub_4E2AE0((int *)m_pCBSystem->m_pEditor, roleIdx);
  return v2;
}

// 0x004F3380
int CCBRoleState::GetMaxHP(int roleIdx)
{
  int v4; // [esp+14h] [ebp+8h]
  int v5; // [esp+18h] [ebp+Ch]

  if ( (int)CCBRoleState_GetRole(this, roleIdx) < (int)abs32(v5) )
    CCBRoleState_GetRole(this, roleIdx);
  this->CalcDefensePower(roleIdx);
  return this->CalcDefensePower(v4);
}

// 0x004F33D0
int CCBRoleState::GetMaxMP(int roleIdx)
{
  int v4; // [esp+14h] [ebp+8h]
  int v5; // [esp+18h] [ebp+Ch]

  if ( sub_4F2BF0(this, roleIdx, 0) < (int)abs32(v5) )
    sub_4F2BF0(this, roleIdx, 0);
  this->CalcAttackPower(roleIdx);
  return this->CalcAttackPower(v4);
}

// 0x004F3420
int CCBRoleState::GetTotalRounds()
{
  return *(_DWORD *)&this->m_Role[0]._rest[4];
}

// 0x004F3430
char CCBRoleState::CheckBuff(int roleIdx)
{
  int RoleIndex; // edi
  CCBSystem *m_pCBSystem; // esi
  char result; // al
  int roleIdxa[3]; // [esp+10h] [ebp-Ch] BYREF
  int v7; // [esp+24h] [ebp+8h]

  *(_DWORD *)&this->m_Role[0]._rest[4] += v7;
  if ( v7 < 0 )
  {
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(8, 0, 1);
    if ( RoleIndex != -1 )
    {
      this->CheckRoleStatus((int)roleIdxa);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::ProcWait, 0, 0, 0, roleIdxa, 0, 1077936128);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
    }
  }
  m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
  result = BYTE1(m_pCBSystem->m_nTimesOfCombat);
  if ( result )
    return sub_4E2C10(m_pCBSystem->m_pEditor);
  return result;
}

// 0x004F34E0
char CCBRoleState::CanUseSkill(int roleIdx)
{
  char result; // al
  char *v3; // esi
  bool v4; // sf
  char *Instance; // eax
  char *v6; // eax
  int v7; // [esp+Ch] [ebp+8h]

  result = this->m_Role[0].bValid;
  if ( result )
  {
    result = roleIdx;
    if ( roleIdx != 4 )
    {
      v3 = (char *)&this->m_Role[0]._rest[892 * roleIdx];
      v4 = v7 < 0;
      *(_DWORD *)v3 += v7;
      if ( v7 > 0 )
      {
        Instance = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(aWa010, 1);
        v4 = v7 < 0;
      }
      if ( v4 )
      {
        v6 = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)v6)->AudioSetPosition(aWa048, 1);
      }
      if ( *(int *)v3 < 0 )
        *(_DWORD *)v3 = 0;
      if ( *(int *)v3 > 999 )
        *(_DWORD *)v3 = 999;
    }
  }
  return result;
}

// 0x004F3570
int CCBRoleState::CalcMagicAttack(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return 0;
}

// 0x004F3620
int CCBRoleState::CalcMPRegen(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return 0;
}

// 0x004F36D0
int CCBRoleState::CalcMagicDefense(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return 99999;
}

// 0x004F37A0
int CCBRoleState::GetAttackBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+Ch] [ebp+8h]
  float roleIdxb; // [esp+Ch] [ebp+8h]

  v2 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  if ( v2[1147] )
  {
    v3 = *((_DWORD *)v2 + 153);
    roleIdxa = (double)v3 * 0.25;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1148];
    result = *((_DWORD *)v2 + 153);
    if ( v5 )
    {
      roleIdxb = (double)result * -0.25;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F3820
int CCBRoleState::GetDefenseBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+Ch] [ebp+8h]
  float roleIdxb; // [esp+Ch] [ebp+8h]

  v2 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  if ( v2[1149] )
  {
    v3 = *((_DWORD *)v2 + 154);
    roleIdxa = (double)v3 * 0.25;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1150];
    result = *((_DWORD *)v2 + 154);
    if ( v5 )
    {
      roleIdxb = (double)result * -0.25;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F38A0
int CCBRoleState::GetRoleState(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+Ch] [ebp+8h]
  float roleIdxb; // [esp+Ch] [ebp+8h]

  v2 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  if ( v2[1151] )
  {
    v3 = *((_DWORD *)v2 + 156);
    roleIdxa = (double)v3 * 0.25;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1152];
    result = *((_DWORD *)v2 + 156);
    if ( v5 )
    {
      roleIdxb = (double)result * -0.25;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F3920
int CCBRoleState::GetSpeedBonus(int roleIdx)
{
  char *v2; // eax
  int v3; // eax
  int result; // eax
  char v5; // cl
  float roleIdxa; // [esp+Ch] [ebp+8h]
  float roleIdxb; // [esp+Ch] [ebp+8h]

  v2 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  if ( v2[1153] )
  {
    v3 = *((_DWORD *)v2 + 155);
    roleIdxa = (double)v3 * 0.25;
    return (int)roleIdxa + v3;
  }
  else
  {
    v5 = v2[1154];
    result = *((_DWORD *)v2 + 155);
    if ( v5 )
    {
      roleIdxb = (double)result * -0.25;
      result += (int)roleIdxb;
    }
  }
  return result;
}

// 0x004F39A0
int CCBRoleState::GetRoleLevel(int roleIdx)
{
  int v2; // edi
  int *v3; // edx
  int v5; // [esp+10h] [ebp+8h]

  v2 = *(&this->m_Role[0].nLuck + 223 * roleIdx);
  v3 = (int *)&this->m_Role[0].nLuck + 223 * roleIdx;
  * v3 = (*)v2 + v5;
  if ( v2 + v5 < 0 )
    *v3 = 0;
  ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdSlot(roleIdx);
  return v2;
}

// 0x004F39F0
int CCBRoleState::GetRoleExp(int roleIdx)
{
  int result; // eax
  int i; // edx
  int v4; // [esp+10h] [ebp+8h]

  result = 0;
  for ( i = 0; i < 8; ++i )
    result += (unsigned __int8)this->m_Role[0]._rest[892 * roleIdx + 356 + 8 * v4 + i];
  return result;
}

// 0x004F3A30
char CCBRoleState::SetRoleFlag(int roleIdx, char flag)
{
  this->m_Role[0]._rest[892 * roleIdx + 512] = flag;
  return flag;
}

// 0x004F3A50
int CCBRoleState::GetRoleAttr(int roleIdx)
{
  int v3; // ecx
  int v4; // esi

  v3 = this->SetRoleField(roleIdx, 0);
  v4 = *(&this->m_Role[0].nFullHP + 223 * roleIdx);
  if ( v3 == v4 )
    return 1;
  if ( v3 >= v4 / 2 && v3 < v4 )
    return 2;
  if ( v3 < v4 / 4 )
    return (v3 <= 0) + 4;
  return 3;
}

// 0x004F3AD0
int CCBRoleState::CalcMPCost(int roleIdx)
{
  this->GetRoleMP(roleIdx);
  return -1;
}

// 0x004F3B90
int CCBRoleState::GetRoleMP(int roleIdx)
{
  int result; // eax
  _DWORD *v3; // [esp+8h] [ebp+8h]
  _DWORD *v4; // [esp+Ch] [ebp+Ch]

  *v3 = 0;
  result = roleIdx - 1;
  *v4 = 11;
  if ( roleIdx == 1 )
  {
    *v4 = 5;
  }
  else
  {
    result = roleIdx - 2;
    if ( roleIdx == 2 )
      *v3 = 5;
  }
  return result;
}

// 0x004F3BC0
int CCBRoleState::GetRoleHP(int roleIdx)
{
  if ( *(&this->m_Role[0].bValid + 892 * roleIdx) )
    return (roleIdx >= 5) + 1;
  else
    return 0;
}

// 0x004F3C00
int CCBRoleState::IsForce1(int force)
{
  if ( force == 1 )
    return 2;
  else
    return force == 2;
}

// 0x004F3C20
char CCBRoleState::IsPlayerTeam(int force)
{
  char result; // al

  switch ( force )
  {
    case 0:
    case 6:
    case 8:
    case 10:
    case 12:
    case 20:
    case 21:
    case 22:
    case 23:
    case 26:
    case 27:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x004F3C70
char CCBRoleState::GetRoleForce(int roleIdx)
{
  int v2; // esi
  char *v3; // ebx

  v2 = 1;
  v3 = (char *)&this->m_Role[0]._rest[892 * roleIdx + 513];
  while ( v3[v2] != 1 || v2->IsPlayerTeam() )
  {
    if ( ++v2 >= 27 )
      return 0;
  }
  return 1;
}

// 0x004F3CC0
bool CCBRoleState::IsRoleInForce(int roleIdx)
{
  bool result; // al
  char *v3; // ecx

  result = 1;
  v3 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  if ( v3[1142] != 1 && v3[1143] != 1 && v3[1144] != 1 && v3[1145] != 1 )
    return v3[1146] == 1;
  return result;
}

// 0x004F3D10
char CCBRoleState::CanRoleAct(int roleIdx)
{
  if ( this->GetRoleField(roleIdx, 26) )
    return 0;
  if ( !this->IsRoleInForce(roleIdx) )
  {
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    this->ProcessRound(roleIdx);
  }
  return 1;
}

// 0x004F3D90
char CCBRoleState::GetRoleField(int roleIdx, int fieldOff)
{
  return this->m_Role[0]._rest[892 * roleIdx + 513 + fieldOff];
}

// 0x004F3DC0
int CCBRoleState::GetRoleSpeed(int roleIdx)
{
  int v3; // esi

  if ( !this->m_Role[0].bAlive )
    return 0;
  v3 = 1;
  while ( !this->m_Role[0]._rest[892 * roleIdx + 513 + v3] || v3->IsPlayerTeam() )
  {
    if ( ++v3 >= 27 )
      return 0;
  }
  return v3;
}

// 0x004F3E20
char CCBRoleState::ProcessRound(unsigned int a2)
{
  char *v3; // eax
  int i; // edi
  CCBStage *m_pStage; // ecx
  int RoleIndex; // eax
  int v7; // edi
  int v8; // ecx
  unsigned int v9; // ebp
  int v10; // edi
  char *Instance; // eax
  int v12; // edi
  int v13; // edx
  char *v14; // edi
  void (***v15)(_DWORD, int); // ecx
  CCBStage *v16; // ecx
  int v17; // edi
  int v18; // edi
  char *v19; // eax
  char *v21; // [esp-8h] [ebp-50h]
  char *v22; // [esp-8h] [ebp-50h]
  _DWORD a7[3]; // [esp+10h] [ebp-38h] BYREF
  _DWORD a3[11]; // [esp+1Ch] [ebp-2Ch] BYREF
  int force; // [esp+50h] [ebp+8h]
  int forcea; // [esp+50h] [ebp+8h]
  char v27; // [esp+54h] [ebp+Ch]
  char v28; // [esp+58h] [ebp+10h]

  LOBYTE(v3) = this->GetRoleField(a2, 23);
  if ( (_BYTE)v3 && force != 23 )
    return (char)v3;
  if ( force < 1 || force > 5 )
    goto LABEL_7;
  if ( v27 )
  {
    LOBYTE(v3) = this->IsRoleInForce(a2);
    if ( (_BYTE)v3 )
      return (char)v3;
LABEL_7:
    if ( v27 )
    {
      if ( force >= 1 && force <= 5 )
      {
        v3 = (char *)&this->m_sCombatDialog[892 * a2];
        *(_DWORD *)(v3 + 1142) = 0;
        v3[1146] = 0;
        if ( v3[1167] )
          return (char)v3;
      }
      if ( force >= 14 && force <= 23 )
      {
        for ( i = 14; i <= 23; ++i )
          this->ProcessRound(a2);
      }
      if ( !force->IsPlayerTeam() && force != 24 && force != 25 && *(&this->m_Role[0].nHP + 223 * a2) > 0 )
      {
        memset(a3, 0, sizeof(a3));
        m_pStage = (CCBStage *)this->m_pStage;
        LOBYTE(a3[10]) = 1;
        a3[2] = a2;
        a3[0] = 0;
        a3[1] = 0;
        a3[3] = a2;
        LOWORD(a3[4]) = 0;
        RoleIndex = m_pStage->GetRoleIndex(10, a3, 1);
        v7 = RoleIndex;
        if ( RoleIndex != -1 )
        {
          ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)CCBStage::HandleKeyFriend, 0, 0, 0, a7, -1082130432, 0);
          ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v7);
        }
      }
    }
  }
  v8 = force;
  v9 = 892 * a2;
  v3 = (char *)&this->m_Role[0]._rest[892 * a2 + 513 + force];
  *v3 = v27;
  v10 = force + 446 * a2;
  forcea = v10;
  *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 540] = 0;
  *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 0;
  if ( v27 )
  {
    switch ( v8 )
    {
      case 1:
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 540] = 3;
        goto LABEL_24;
      case 2:
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 540] = 3;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 2;
        goto LABEL_25;
      case 3:
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 540] = 0;
LABEL_24:
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        goto LABEL_25;
      case 4:
      case 5:
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 540] = 0;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 0x7FFF;
LABEL_25:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd005;
        break;
      case 6:
        this->m_Role[0]._rest[v9 + 519] = 0;
        this->m_Role[0]._rest[v9 + 520] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        goto LABEL_38;
      case 7:
        this->m_Role[0]._rest[v9 + 519] = 0;
        this->m_Role[0]._rest[v9 + 520] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        goto LABEL_41;
      case 8:
        this->m_Role[0]._rest[v9 + 521] = 0;
        this->m_Role[0]._rest[v9 + 522] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        goto LABEL_38;
      case 9:
        this->m_Role[0]._rest[v9 + 521] = 0;
        this->m_Role[0]._rest[v9 + 522] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        goto LABEL_41;
      case 10:
        this->m_Role[0]._rest[v9 + 523] = 0;
        this->m_Role[0]._rest[v9 + 524] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        goto LABEL_38;
      case 11:
        this->m_Role[0]._rest[v9 + 523] = 0;
        this->m_Role[0]._rest[v9 + 524] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        goto LABEL_41;
      case 12:
        this->m_Role[0]._rest[v9 + 525] = 0;
        this->m_Role[0]._rest[v9 + 526] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdSlot(a2);
LABEL_38:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd021;
        break;
      case 13:
        this->m_Role[0]._rest[v9 + 525] = 0;
        this->m_Role[0]._rest[v9 + 526] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdSlot(a2);
LABEL_41:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd022;
        break;
      case 14:
        sub_4F4820((int)this, a2);
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 4;
        if ( !v28 )
          return (char)v3;
        v21 = aWd007;
        break;
      case 15:
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = aWd008;
        break;
      case 16:
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = aWd009;
        break;
      case 17:
        sub_4F4820((int)this, a2);
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = ((g_RandSeed >> 16) & 0x7FFF) % 7 + 2;
        if ( !v28 )
          return (char)v3;
        v21 = aWd010;
        break;
      case 18:
        sub_4F4820((int)this, a2);
        ((CCBStageRole *)this->m_pStage->m_pRole[a2])->DangerForceRelease(0);
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = aWd012;
        break;
      case 19:
        sub_4F4820((int)this, a2);
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = aWd011;
        break;
      case 20:
        if ( a2 > 4 )
          *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        else
          *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 3;
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd016;
        break;
      case 21:
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 4;
        if ( !v28 )
          return (char)v3;
        v21 = aWd013;
        break;
      case 22:
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 4;
        if ( !v28 )
          return (char)v3;
        v21 = aWd014;
        break;
      case 23:
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 5;
        if ( this->IsRoleAlive(a2) )
        {
          v12 = ((CCBStage *)this->m_pStage)->GetRoleIndex(22, 0, 1);
          if ( v12 != -1 )
          {
            this->CheckRoleStatus((int)a7);
            ((CCBStage *)this->m_pStage)->GetRoleName(v12, (int)sub_501330, 0, 0, 0, a7, 0, 1065353216);
            ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v12);
          }
        }
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd015;
        break;
      case 24:
        v3 = (char *)&this->m_Role[0].nHP + v9;
        v13 = *(int *)((char *)&this->m_Role[0].nFullHP + v9) / 10;
        if ( *(_DWORD *)v3 > v13 )
          *(_DWORD *)v3 = v13;
        return (char)v3;
      case 25:
        v3 = (char *)*(char **)((char *)&this->m_Role[0].nHP + v9);
        if ( (int)v3 > 0 )
          *(int *)((char *)&this->m_Role[0].nHP + v9) = 0;
        return (char)v3;
      case 26:
        *v3 = 1;
        *(_WORD *)&this->m_Role[0]._rest[2 * v10 + 594] = 0x7FFF;
        return (char)v3;
      default:
        return (char)v3;
    }
    Instance = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v21, 1);
  }
  else
  {
    switch ( v8 )
    {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        if ( v28 )
        {
          v22 = aWd006;
          break;
        }
        goto LABEL_91;
      case 12:
      case 13:
        ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdSlot(a2);
        goto LABEL_91;
      case 14:
        ((CCBStageRole *)this->m_pStage->m_pRole[a2])->DangerForceRelease(0);
        goto LABEL_91;
      case 20:
      case 21:
      case 22:
        goto LABEL_86;
      case 23:
        if ( this->IsRoleAlive(a2) )
        {
          v18 = ((CCBStage *)this->m_pStage)->GetRoleIndex(22, 0, 1);
          if ( v18 != -1 )
          {
            this->CheckRoleStatus((int)a7);
            ((CCBStage *)this->m_pStage)->GetRoleName(v18, (int)sub_501410, 0, 0, 0, a7, 0, 1065353216);
            ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v18);
          }
        }
LABEL_86:
        if ( !v28 )
          goto LABEL_91;
        v22 = aWd020;
        break;
      case 25:
        if ( *(&this->m_Role[0].bAlive + v9) )
          goto LABEL_91;
        *(&this->m_Role[0].bAlive + v9) = 1;
        *(int *)((char *)&this->m_Role[0].nHP + v9) = 0;
        memset(&this->m_Role[0]._rest[v9 + 513], 0, 0x18u);
        v14 = (char *)&this->m_Role[0]._rest[v9 + 537];
        *(_WORD *)v14 = 0;
        v14[2] = 0;
        memset(&this->m_Role[0]._rest[v9 + 540], 0, 0x34u);
        *(_WORD *)&this->m_Role[0]._rest[v9 + 592] = 0;
        memset(&this->m_Role[0]._rest[v9 + 594], 0, 0x34u);
        *(_WORD *)&this->m_Role[0]._rest[v9 + 646] = 0;
        this->m_Role[0]._rest[v9 + 512] = 0;
        ((CCBStageRole *)this->m_pStage->m_pRole[a2])->DangerForceRelease(0);
        ((CCBStageRole *)this->m_pStage->m_pRole[a2])->Release(1);
        v15 = (void (***)(_DWORD, int))*((_DWORD *)this->m_pUI + a2 + 19);
        (**v15)(v15, 1);
        ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->SetCmdParam(a2, 0);
        ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetCmdData(a2);
        if ( !((CCBStageRole *)this->m_pStage->m_pRole[a2])->ForceEndTaskByPFN() )
        {
          memset(a3, 0, sizeof(a3));
          v16 = (CCBStage *)this->m_pStage;
          LOBYTE(a3[10]) = 1;
          a3[2] = a2;
          a3[1] = 259;
          v17 = v16->GetRoleIndex(9, a3, 1);
          if ( v17 != -1 )
          {
            a7[2] = a3[3];
            a7[1] = a3[2];
            a7[0] = 0;
            ((CCBStage *)this->m_pStage)->GetRoleName(v17, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, a7, -1082130432, 0);
            ((CCBStage *)this->m_pStage)->GetRoleName(v17, (int)CCBStage::ProcShowItemName, 0, 0, 0, a7, -1082130432, 0);
            ((CCBStage *)this->m_pStage)->GetRoleName(v17, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, a7, -1082130432, 0);
            ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v17);
          }
        }
        if ( !v28 )
          goto LABEL_91;
        v22 = aWd004;
        break;
      default:
        goto LABEL_91;
    }
    v19 = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)v19)->AudioSetPosition(v22, 1);
LABEL_91:
    *(_WORD *)&this->m_Role[0]._rest[2 * forcea + 540] = 0;
    *(_WORD *)&this->m_Role[0]._rest[2 * forcea + 594] = 0;
    LOBYTE(v3) = forcea;
  }
  return (char)v3;
}

// 0x004F4DA0
int CCBRoleState::ProcessAttackResult(int roleIdx)
{
  int v2; // ebx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int RoleNum; // eax
  int v10; // ebp
  int v11; // esi
  int *v12; // ebx
  int v13; // edi
  int v14; // eax
  bool v15; // cc
  int v16; // esi
  int *v17; // ebp
  CCBStageRole *Role; // ecx
  int v19; // [esp+10h] [ebp-48h]
  int v21; // [esp+18h] [ebp-40h]
  int v22; // [esp+1Ch] [ebp-3Ch]
  int *v23; // [esp+20h] [ebp-38h]
  signed int v24; // [esp+24h] [ebp-34h]
  int v25; // [esp+28h] [ebp-30h]
  _DWORD pOut[11]; // [esp+2Ch] [ebp-2Ch] BYREF
  int *roleIdxa; // [esp+5Ch] [ebp+4h]
  char v28; // [esp+60h] [ebp+8h]
  int v29; // [esp+64h] [ebp+Ch]

  v2 = roleIdx;
  memset(pOut, 0, sizeof(pOut));
  v19 = 0;
  v25 = -1;
  v24 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 261;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v5 = this->GetRoleHP(roleIdx) - 1;
  if ( v5 )
  {
    if ( v5 != 1 )
      return 0;
    roleIdxa = dword_17AA450;
    v6 = 760;
    while ( 1 )
    {
      v7 = ((PAL_GDB *)&g_GDB)->~PAL_GDB(*(&this->m_Role[0].dwID + 223 * v2));
      v8 = *(_DWORD *)(v6 + v7);
      if ( v8 )
      {
        RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*(_DWORD *)(v6 + v7));
        if ( *(_BYTE *)(RoleNum + 4) == 3 )
        {
          if ( v28 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) == 2 )
              goto LABEL_14;
          }
          else if ( !v28 && *(_BYTE *)(RoleNum + 577) == 1 )
          {
LABEL_14:
            pOut[1] = v8;
            if ( this->GetRoleAI(pOut) )
            {
              *roleIdxa = v8;
              ++v19;
              ++roleIdxa;
            }
          }
        }
      }
      v6 += 4;
      if ( v6 >= 776 )
      {
        if ( !v19 )
          return 0;
LABEL_37:
        v16 = 0;
        if ( v19 <= 0 )
          return 0;
        v17 = dword_17AA450;
        do
        {
          Role = (CCBStageRole *)CCBStage_GetRole((CCBStage *)this, v2);
          if ( (int)abs32((int)Role - v29) < v24 )
          {
            v25 = v16;
            v24 = abs32(abs32((int)Role) - abs32(v29));
          }
          ++v16;
          ++v17;
        }
        while ( v16 < v19 );
        if ( v25 == -1 )
          return 0;
        else
          return dword_17AA450[v25];
      }
    }
  }
  v21 = 0;
  v22 = 936;
  while ( 2 )
  {
    v10 = 0;
    v11 = 892 * v2;
    v23 = (int *)(4 * v19 + 24814672);
    v12 = (int *)&this->m_Role[0]._rest[892 * v2 + 116 + v21];
    do
    {
      v13 = *v12;
      if ( *v12 )
      {
        if ( this->m_sCombatDialog[v10 + v11 + v22] )
        {
          v14 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*v12);
          if ( *(_BYTE *)(v14 + 4) == 3 )
          {
            if ( v28 == 1 )
            {
              if ( *(_BYTE *)(v14 + 577) != 2 )
                goto LABEL_32;
            }
            else if ( v28 || *(_BYTE *)(v14 + 577) != 1 )
            {
              goto LABEL_32;
            }
            pOut[1] = v13;
            if ( this->GetRoleAI(pOut) )
            {
              *v23 = v13;
              ++v19;
              ++v23;
            }
          }
        }
      }
LABEL_32:
      ++v10;
      ++v12;
    }
    while ( v10 < 8 );
    v15 = v22 + 8 < 984;
    v21 += 32;
    v22 += 8;
    if ( v15 )
    {
      v2 = roleIdx;
      continue;
    }
    break;
  }
  if ( v19 )
  {
    v2 = roleIdx;
    goto LABEL_37;
  }
  return 0;
}

// 0x004F5070
int CCBRoleState::ProcessMagicResult(int roleIdx)
{
  int v2; // ebx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int RoleNum; // eax
  int v10; // ebp
  int v11; // esi
  int *v12; // ebx
  int v13; // edi
  int v14; // eax
  bool v15; // cc
  int v16; // edi
  int *v17; // esi
  unsigned int v18; // ebp
  __int64 v19; // rax
  int v20; // eax
  int v21; // [esp+10h] [ebp-48h]
  int v23; // [esp+18h] [ebp-40h]
  int v24; // [esp+1Ch] [ebp-3Ch]
  int *v25; // [esp+20h] [ebp-38h]
  int v26; // [esp+24h] [ebp-34h]
  int v27; // [esp+28h] [ebp-30h]
  _DWORD pOut[11]; // [esp+2Ch] [ebp-2Ch] BYREF
  int *roleIdxa; // [esp+5Ch] [ebp+4h]
  char v30; // [esp+60h] [ebp+8h]
  int v31; // [esp+64h] [ebp+Ch]

  v2 = roleIdx;
  memset(pOut, 0, sizeof(pOut));
  v21 = 0;
  v27 = -1;
  v26 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 261;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v5 = this->GetRoleHP(roleIdx) - 1;
  if ( v5 )
  {
    if ( v5 != 1 )
      return 0;
    roleIdxa = dword_17AA350;
    v6 = 760;
    while ( 1 )
    {
      v7 = ((PAL_GDB *)&g_GDB)->~PAL_GDB(*(&this->m_Role[0].dwID + 223 * v2));
      v8 = *(_DWORD *)(v6 + v7);
      if ( v8 )
      {
        RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*(_DWORD *)(v6 + v7));
        if ( *(_BYTE *)(RoleNum + 4) == 2 )
        {
          if ( v30 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) == 4 )
              goto LABEL_14;
          }
          else if ( !v30 && *(_BYTE *)(RoleNum + 577) == 3 )
          {
LABEL_14:
            pOut[1] = v8;
            if ( this->GetRoleAI(pOut) )
            {
              *roleIdxa = v8;
              ++v21;
              ++roleIdxa;
            }
          }
        }
      }
      v6 += 4;
      if ( v6 >= 776 )
      {
        if ( !v21 )
          return 0;
LABEL_37:
        v16 = 0;
        if ( v21 <= 0 )
          return 0;
        v17 = dword_17AA350;
        v18 = abs32(v31);
        do
        {
          v19 = (int)(abs32((int)CCBStage_GetRole((CCBStage *)this, v2)) - v18);
          v20 = (HIDWORD(v19) ^ v19) - HIDWORD(v19);
          if ( v20 < v26 )
          {
            v26 = v20;
            v27 = v16;
          }
          ++v16;
          ++v17;
        }
        while ( v16 < v21 );
        if ( v27 == -1 )
          return 0;
        else
          return dword_17AA350[v27];
      }
    }
  }
  v23 = 0;
  v24 = 936;
  while ( 2 )
  {
    v10 = 0;
    v11 = 892 * v2;
    v25 = (int *)(4 * v21 + 24814416);
    v12 = (int *)&this->m_Role[0]._rest[892 * v2 + 116 + v23];
    do
    {
      v13 = *v12;
      if ( *v12 )
      {
        if ( this->m_sCombatDialog[v10 + v11 + v24] )
        {
          v14 = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*v12);
          if ( *(_BYTE *)(v14 + 4) == 2 )
          {
            if ( v30 == 1 )
            {
              if ( *(_BYTE *)(v14 + 577) != 4 )
                goto LABEL_32;
            }
            else if ( v30 || *(_BYTE *)(v14 + 577) != 3 )
            {
              goto LABEL_32;
            }
            pOut[1] = v13;
            if ( this->GetRoleAI(pOut) )
            {
              *v25 = v13;
              ++v21;
              ++v25;
            }
          }
        }
      }
LABEL_32:
      ++v10;
      ++v12;
    }
    while ( v10 < 8 );
    v15 = v24 + 8 < 984;
    v23 += 32;
    v24 += 8;
    if ( v15 )
    {
      v2 = roleIdx;
      continue;
    }
    break;
  }
  if ( v21 )
  {
    v2 = roleIdx;
    goto LABEL_37;
  }
  return 0;
}

// 0x004F55D0
int CCBRoleState::CalcPhysicalDamage(int roleIdx)
{
  signed int v2; // ebp
  int result; // eax
  int v4; // ebx
  char *v5; // eax
  int v6; // esi
  int RoleNum; // edi
  int v8; // esi
  int *v9; // ebx
  CCBStageRole *Role; // ecx
  int v12; // [esp+14h] [ebp-40h]
  int *v13; // [esp+18h] [ebp-3Ch]
  int *v14; // [esp+1Ch] [ebp-38h]
  int v15; // [esp+20h] [ebp-34h]
  _DWORD pOut[11]; // [esp+28h] [ebp-2Ch] BYREF
  char v17; // [esp+5Ch] [ebp+8h]
  int v18; // [esp+60h] [ebp+Ch]

  memset(pOut, 0, sizeof(pOut));
  v12 = 0;
  v15 = -1;
  v2 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  pOut[3] = -1;
  v4 = 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 260;
  v5 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  pOut[1] = 0;
  pOut[2] = roleIdx;
  LOWORD(pOut[4]) = 0;
  v14 = dword_17AA150;
  v13 = (int *)(v5 + 712);
  while ( 1 )
  {
    v6 = *v13;
    if ( *v13 )
    {
      if ( v5[v4 + 736] )
      {
        RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*v13);
        if ( !*(_BYTE *)(RoleNum + 4) && sub_4F6A40(v6) )
        {
          if ( v17 == 1 )
          {
            if ( *(_BYTE *)(RoleNum + 577) != 2 )
              goto LABEL_16;
          }
          else if ( v17 || *(_BYTE *)(RoleNum + 577) != 1 )
          {
            goto LABEL_16;
          }
          pOut[1] = v6;
          if ( this->GetRoleAI(pOut) )
          {
            *v14 = v6;
            ++v12;
            ++v14;
          }
        }
      }
    }
LABEL_16:
    ++v4;
    ++v13;
    if ( v4 >= 6 )
      break;
    v5 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  }
  result = v12;
  if ( v12 )
  {
    v8 = 0;
    if ( v12 <= 0 )
      return 0;
    v9 = dword_17AA150;
    do
    {
      Role = (CCBStageRole *)CCBStage_GetRole((CCBStage *)this, roleIdx);
      if ( (int)abs32((int)Role - v18) < v2 )
      {
        v15 = v8;
        v2 = abs32(abs32((int)Role) - abs32(v18));
      }
      ++v8;
      ++v9;
    }
    while ( v8 < v12 );
    if ( v15 == -1 )
      return 0;
    else
      return dword_17AA150[v15];
  }
  return result;
}

// 0x004F57A0
int CCBRoleState::CalcMagicDamage(int roleIdx)
{
  signed int v3; // ebx
  int result; // eax
  int v5; // eax
  char *v6; // ecx
  int v7; // esi
  int RoleNum; // edi
  char v9; // al
  bool v10; // cc
  int v11; // esi
  int *v12; // ebp
  CCBStageRole *Role; // ecx
  int v14; // [esp+10h] [ebp-48h]
  int *v15; // [esp+14h] [ebp-44h]
  int *v16; // [esp+18h] [ebp-40h]
  int v17; // [esp+1Ch] [ebp-3Ch]
  int v18; // [esp+20h] [ebp-38h]
  _DWORD pOut[11]; // [esp+2Ch] [ebp-2Ch] BYREF
  char v21; // [esp+60h] [ebp+8h]
  int v22; // [esp+64h] [ebp+Ch]

  memset(pOut, 0, sizeof(pOut));
  v14 = 0;
  v18 = -1;
  v3 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  v5 = 0;
  LOBYTE(pOut[10]) = 1;
  pOut[0] = 260;
  pOut[1] = 0;
  pOut[2] = roleIdx;
  v6 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  pOut[3] = -1;
  LOWORD(pOut[4]) = 0;
  v17 = 0;
  v16 = dword_17AA050;
  v15 = (int *)(v6 + 712);
  while ( 1 )
  {
    v7 = *v15;
    if ( *v15 )
    {
      if ( v6[v5 + 736] )
      {
        RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*v15);
        if ( !*(_BYTE *)(RoleNum + 4) && sub_4F6A60(v7) )
        {
          v9 = *(_BYTE *)(RoleNum + 577);
          if ( v21 == 1 )
          {
            if ( v9 != 4 )
              goto LABEL_15;
          }
          else if ( v9 != 3 )
          {
            goto LABEL_15;
          }
          pOut[1] = v7;
          if ( this->GetRoleAI(pOut) )
          {
            *v16 = v7;
            ++v14;
            ++v16;
          }
        }
      }
    }
LABEL_15:
    v5 = v17 + 1;
    v10 = ++v17 < 6;
    ++v15;
    if ( !v10 )
      break;
    v6 = (char *)&this->m_sCombatDialog[892 * roleIdx];
  }
  result = v14;
  if ( v14 )
  {
    v11 = 0;
    if ( v14 <= 0 )
      return 0;
    v12 = dword_17AA050;
    do
    {
      Role = (CCBStageRole *)CCBStage_GetRole((CCBStage *)this, roleIdx);
      if ( (int)abs32((int)Role - v22) < v3 )
      {
        v18 = v11;
        v3 = abs32(abs32((int)Role) - abs32(v22));
      }
      ++v11;
      ++v12;
    }
    while ( v11 < v14 );
    if ( v18 == -1 )
      return 0;
    else
      return dword_17AA050[v18];
  }
  return result;
}

// 0x004F5970
int CCBRoleState::ProcessSkillEffect(int roleIdx)
{
  CCBRoleState *v2; // ebp
  int v3; // edi
  int v5; // ebx
  int v6; // esi
  char v7; // al
  int v8; // ebp
  unsigned int v9; // ecx
  __int64 v10; // rax
  signed int v12; // [esp+14h] [ebp-88h]
  int v13; // [esp+18h] [ebp-84h]
  int v14; // [esp+1Ch] [ebp-80h]
  _DWORD v15[11]; // [esp+20h] [ebp-7Ch] BYREF
  _DWORD v16[3]; // [esp+4Ch] [ebp-50h] BYREF
  unsigned int v17[11]; // [esp+58h] [ebp-44h] BYREF
  _DWORD pOut[3]; // [esp+84h] [ebp-18h] BYREF
  _DWORD v19[3]; // [esp+90h] [ebp-Ch] BYREF
  char v20; // [esp+A4h] [ebp+8h]
  int v21; // [esp+A8h] [ebp+Ch]

  v2 = this;
  memset(v15, 0, sizeof(v15));
  v3 = roleIdx;
  v13 = -1;
  v12 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  v5 = 0;
  LOBYTE(v15[10]) = 1;
  v15[0] = 262;
  v15[1] = 0;
  v15[2] = roleIdx;
  v15[3] = -1;
  LOWORD(v15[4]) = 0;
  v14 = sub_40CCD0((int *)&g_SceneMgr._gap_1888[760]);
  if ( v14 <= 0 )
    return 0;
  while ( 1 )
  {
    if ( *((int *)((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(pOut) + 1) > 0 )
    {
      v6 = *(_DWORD *)((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(v19);
      v15[1] = v6;
      if ( v2->GetRoleAI(v15) )
      {
        v7 = *(_BYTE *)(*((_DWORD *)((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(v16) + 2) + 629);
        if ( v20 )
        {
          if ( v7 == 1 || v7 == 3 )
            goto LABEL_21;
        }
        else if ( v7 == 2 || v7 == 4 )
        {
          goto LABEL_21;
        }
        if ( sub_4F6AD0(v6) )
        {
          v8 = sub_4F4C80(v2, v3, v6);
          memset(v17, 0, sizeof(v17));
          v17[0] = 262;
          v17[1] = v6;
          if ( sub_4F6CD0(v17) )
            v8 += 100000;
          v9 = abs32(v8);
          if ( (int)abs32(v9 - v21) < v12 )
          {
            v13 = v5;
            v10 = (int)(v9 - abs32(v21));
            v12 = (HIDWORD(v10) ^ v10) - HIDWORD(v10);
          }
          v2 = this;
        }
      }
    }
LABEL_21:
    if ( ++v5 >= v14 )
      break;
    v3 = roleIdx;
  }
  if ( v13 == -1 )
    return 0;
  else
    return *(_DWORD *)((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(v16);
}

// 0x004F5B70
int CCBRoleState::ProcessItemEffect(int roleIdx)
{
  signed int v3; // esi
  int i; // edi
  int v6; // ebp
  char v7; // al
  unsigned int v8; // ecx
  int v9; // [esp+10h] [ebp-58h]
  int v10; // [esp+14h] [ebp-54h]
  _DWORD pOut[3]; // [esp+18h] [ebp-50h] BYREF
  _DWORD v12[3]; // [esp+24h] [ebp-44h] BYREF
  _DWORD v13[3]; // [esp+30h] [ebp-38h] BYREF
  _DWORD v14[11]; // [esp+3Ch] [ebp-2Ch] BYREF
  char v15; // [esp+70h] [ebp+8h]
  int v16; // [esp+74h] [ebp+Ch]

  memset(v14, 0, sizeof(v14));
  v9 = -1;
  v3 = 0x7FFFFFFF;
  if ( !this->IsRoleAlive(roleIdx) )
    return 0;
  LOBYTE(v14[10]) = 1;
  v14[0] = 262;
  v14[1] = 0;
  v14[2] = roleIdx;
  v14[3] = -1;
  LOWORD(v14[4]) = 0;
  v10 = sub_40CCD0((int *)&g_SceneMgr._gap_1888[760]);
  if ( v10 <= 0 )
    return 0;
  for ( i = 0; i < v10; ++i )
  {
    if ( *((int *)((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(pOut) + 1) > 0 )
    {
      v6 = *(_DWORD *)((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(v12);
      v14[1] = v6;
      if ( this->GetRoleAI(v14) )
      {
        v7 = *(_BYTE *)(*((_DWORD *)((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(v13) + 2) + 629);
        if ( v15 )
        {
          if ( v7 == 1 || v7 == 3 )
            continue;
        }
        else if ( v7 == 2 || v7 == 4 )
        {
          continue;
        }
        if ( sub_4F6B70(v6) )
        {
          v8 = abs32(sub_4F4B90(this, roleIdx, v6));
          if ( (int)abs32(v8 - v16) < v3 )
          {
            v9 = i;
            v3 = abs32(v8 - abs32(v16));
          }
        }
      }
    }
  }
  if ( v9 == -1 )
    return 0;
  else
    return *(_DWORD *)((CCBAI *)&g_SceneMgr._gap_1888[760])->GetTargetRole(v13);
}

// 0x004F7500
char CCBRoleState::GetRoleAI(void *pOut)
{
  int v3; // eax
  char v4; // dl
  char *v5; // ecx
  char result; // al

  v3 = *((_DWORD *)pOut + 2);
  v4 = *(&this->m_Role[0].bAlive + 892 * v3);
  v5 = (char *)&this->m_sCombatDialog[892 * v3];
  if ( !v4 )
    return 0;
  if ( v5[1432] )
    return 0;
  this->GetRoleHP(*((_DWORD *)pOut + 2));
  result = sub_4F6E80(this, pOut);
  if ( result )
  {
    switch ( *(_DWORD *)pOut )
    {
      case 0x104:
        result = sub_4F6DA0(this, pOut);
        if ( !result )
          return result;
        result = sub_4F7480(this, pOut);
        if ( !result )
          return result;
        result = sub_4F7200(this, (int)pOut);
        if ( !result )
          return result;
        ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(*((_DWORD *)pOut + 1));
        break;
      case 0x105:
        result = sub_4F6DA0(this, pOut);
        if ( !result )
          return result;
        result = sub_4F7480(this, pOut);
        if ( !result )
          return result;
        result = sub_4F7200(this, (int)pOut);
        if ( !result )
          return result;
        if ( this->GetRoleField(*((_DWORD *)pOut + 2), 15) )
          return 0;
        if ( *((_DWORD *)pOut + 1) == 7710 )
        {
          if ( this->Update(2) != 1 )
            return 0;
          if ( BYTE2(this->m_Role[5].nIndex) && !this->m_Role[5]._rest[784] )
            return 0;
          if ( this->m_Role[6]._rest[818] && !this->m_Role[7]._rest[776] )
            return 0;
        }
        break;
      case 0x106:
        result = sub_4F6FB0((int)pOut);
        if ( result )
        {
          if ( this->GetRoleField(*((_DWORD *)pOut + 2), 16) )
          {
            return 0;
          }
          else if ( !sub_4F7050((int)pOut) || (result = sub_4F70A0((int)pOut)) != 0 )
          {
            ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(*((_DWORD *)pOut + 1));
            return 1;
          }
        }
        return result;
      default:
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x004F7880
unsigned int CCBRoleState::CheckStatus()
{
  int *p_nMP; // ecx
  int v2; // edi
  int v3; // esi
  unsigned int result; // eax

  p_nMP = (int *)&this->m_Role[0].nMP;
  v2 = 11;
  do
  {
    *(p_nMP - 4) = *(p_nMP - 4) < 0 ? 0 : *(p_nMP - 4);
    *(p_nMP - 2) = *(p_nMP - 2) < 0 ? 0 : *(p_nMP - 2);
    * p_nMP = (*)*p_nMP < 0 ? 0 : *p_nMP;
    if ( *(p_nMP - 4) <= 0 )
    {
      *((_BYTE *)p_nMP - 26) = 0;
      *((_BYTE *)p_nMP + 562) = 1;
      *((_BYTE *)p_nMP + 561) = 0;
    }
    v3 = *(p_nMP - 4);
    result = (unsigned int)((unsigned __int64)(1717986919LL * *(p_nMP - 3)) >> 32) >> 31;
    if ( v3 < *(p_nMP - 3) / 10 && v3 > 0 )
      *((_BYTE *)p_nMP + 561) = 1;
    p_nMP += 223;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x004F7910
void * CCBRoleState::ProcessActions()
{
  int RoleIndex; // edi
  int v3; // edi
  unsigned __int8 *p_bValid; // ebx
  int v5; // ebx
  unsigned __int8 *p_bAlive; // ebp
  CCBStage *m_pStage; // ecx
  int v8; // edi
  int v9; // edi
  int v10; // edi
  void *result; // eax
  int v12; // ecx
  CCBUI *v13; // [esp+0h] [ebp-44h]
  int v14; // [esp+4h] [ebp-40h]
  int v15; // [esp+10h] [ebp-34h]
  unsigned __int8 *v16; // [esp+14h] [ebp-30h]
  _DWORD a3[11]; // [esp+18h] [ebp-2Ch] BYREF

  memset(a3, 0, sizeof(a3));
  if ( sub_4ED0A0(this->m_sCombatDialog, 0) == 1
    && this->m_pCBSystem->m_eState == CBS_END
    && !((CCBStage *)this->m_pStage)->ForceDelTask(12) )
  {
    sub_4ED800(this->m_sCombatDialog);
    RoleIndex = ((CCBStage *)this->m_pStage)->GetRoleIndex(25, a3, 1);
    if ( RoleIndex != -1 )
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)sub_502300, 0, 0, 0, 0, -1082130432, 1056964608);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)sub_501F30, 0, 0, 0, 0, -1082130432, 1084227584);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)sub_502000, 0, 0, 0, 0, -1082130432, 1065353216);
      ((CCBStage *)this->m_pStage)->GetRoleName(RoleIndex, (int)sub_5021C0, 0, 0, 0, 0, -1082130432, 1045220557);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(RoleIndex);
    }
    ((CCBStageCam *)this->m_pStage->m_pCamControl)->ClearFinishedTask(10);
    v3 = 24;
    p_bValid = (unsigned __int8 *)&this->m_Role[0].bValid;
    this->m_pCBSystem->m_eState = CBS_END|CBS_RUNNING|0x4;
    do
    {
      if ( *p_bValid )
      {
        (*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + v3))->m_Thread[128] = 0;
        (*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + v3))->m_Thread[122] = 0;
        ((CCBStageRole *)*(CCBStageRole **)((char *)&this->m_pStage->m_pCBSystem + v3))->TryRelease();
      }
      v3 += 4;
      p_bValid += 892;
    }
    while ( v3 < 68 );
  }
  if ( ((unsigned __int8)this->GetForce(0) == 1
     || this->m_nBossRound >= this->m_nMaxRound && !this->m_bMustFail)
    && this->m_pCBSystem->m_eState == CBS_END
    && !((CCBStage *)this->m_pStage)->ForceDelTask(12) )
  {
    sub_4F8AF0(this);
    CCBStage_Method_4FA930(this, 1, -1);
    ((CCBStageCam *)this->m_pStage->m_pCamControl)->ClearFinishedTask(3);
    v5 = 0;
    p_bAlive = (unsigned __int8 *)&this->m_Role[0].bAlive;
    v15 = 0;
    v16 = (unsigned __int8 *)&this->m_Role[0].bAlive;
    do
    {
      if ( *(p_bAlive - 1) )
      {
        if ( *p_bAlive )
        {
          m_pStage = (CCBStage *)this->m_pStage;
          a3[2] = v5;
          v8 = m_pStage->GetRoleIndex(24, a3, 1);
          if ( v8 != -1 )
          {
            ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, 0, -1082130432, 0);
            ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)sub_501CF0, 0, 0, 0, 0, -1082130432, 0);
            ((CCBStage *)this->m_pStage)->GetRoleName(v8, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, 0, -1082130432, 0);
            ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v8);
            p_bAlive = v16;
            v5 = v15;
          }
        }
      }
      ++v5;
      p_bAlive += 892;
      v15 = v5;
      v16 = p_bAlive;
    }
    while ( v5 < 5 );
    v9 = ((CCBStage *)this->m_pStage)->GetRoleIndex(23, a3, 1);
    if ( v9 != -1 )
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, (int)sub_502300, 0, 0, 0, 0, -1082130432, 1056964608);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, (int)sub_501E60, 0, 0, 0, 0, -1082130432, 1077936128);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, (int)sub_502430, 0, 0, 0, 0, -1082130432, 0x40000000);
      CCBStage_Method_4FA930(this, 0, v9);
      sub_4FB370(this, v9);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, (int)CCBStage::StartSubTask, 0, 0, 0, 0, -1082130432, 1084227584);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, (int)sub_5021C0, 0, 0, 0, 0, -1082130432, 1045220557);
      ((CCBStage *)this->m_pStage)->GetRoleName(v9, (int)sub_502000, 0, 0, 0, 0, -1082130432, 1065353216);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v9);
      *(_DWORD *)&this->m_dwEXPTable[312] = ((CCBStage *)this->m_pStage)->EndTask(v9);
    }
    sub_4ED870(this);
    sub_4ED680(this);
    ((C2DSpark *)this->m_pCBSystem->m_p2DSpark)->CreateStars();
    ((C2DSpark *)this->m_pCBSystem->m_p2DSpark)->CreateTrack(1);
    this->m_pCBSystem->m_eState = 5;
    ((CCBStageScene *)this->m_pCBSystem->m_pStage->m_pScene)->Destroy();
  }
  if ( this->m_pCBSystem->m_eState == 4 )
  {
    CCBStage_Method_4FA930(this, 1, -1);
    ((CCBStageCam *)this->m_pCBSystem->m_pStage->m_pCamControl)->ClearFinishedTask(8);
    ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->GetDeltaTime();
    sub_4DB940(this->m_pCBSystem->m_pAttackSequen, 0);
    v13->CreateMagicWindow(v14);
    v10 = ((CCBStage *)this->m_pStage)->GetRoleIndex(23, a3, 1);
    if ( v10 != -1 )
    {
      ((CCBStage *)this->m_pStage)->GetRoleName(v10, (int)sub_502430, 0, 0, 0, 0, -1082130432, 0x40000000);
      CCBStage_Method_4FA930(this, 0, v10);
      sub_4FB370(this, v10);
      ((CCBStage *)this->m_pStage)->GetRoleName(v10, (int)CCBStage::StartSubTask, 0, 0, 0, 0, -1082130432, 1097859072);
      ((CCBSystem *)this->m_pStage)->GetStageRoleByIdx(v10);
    }
    sub_4ED680(this);
    this->m_pCBSystem->m_eState = 5;
    ((CCBStageScene *)this->m_pCBSystem->m_pStage->m_pScene)->Destroy();
  }
  result = (void *)this->m_pCBSystem;
  v12 = *((_DWORD *)result + 30);
  if ( v12 == 5 )
  {
    LOBYTE(result) = sub_4FCA40((char *)this->m_pStage, *(_DWORD *)&this->m_dwEXPTable[312]);
    if ( (_BYTE)result )
      return result;
    this->m_pCBSystem->m_eResult = CBR_LOSE;
    return (void *)CCBSystem::GetRenderFlag();
  }
  if ( v12 == 7 )
  {
    if ( *(int *)(*((_DWORD *)result + 5) + 156) > 0 )
      return result;
    *((_DWORD *)result + 31) = 3;
    return (void *)CCBSystem::GetRenderFlag();
  }
  if ( v12 == 6 && *(int *)(*((_DWORD *)result + 5) + 156) <= 0 )
  {
    *((_DWORD *)result + 31) = 4;
    sub_4ED870(this);
    return (void *)CCBSystem::GetRenderFlag();
  }
  return result;
}

// 0x004F8480
int CCBRoleState::UpdateEffects()
{
  int v2; // ebx
  int result; // eax
  int v4; // edi
  UIWnd **m_pUI; // eax
  CCBSystem *m_pCBSystem; // ecx
  char RoleField; // al
  void (__stdcall **v8)(int); // edx
  char v9; // al
  void (__stdcall **v10)(int); // edx
  char v11; // al
  void (__stdcall **v12)(int); // edx
  char v13; // al
  void (__stdcall **v14)(int); // edx
  char v15; // al
  void (__stdcall **v16)(int); // edx
  char v17; // al
  void (__stdcall **v18)(int); // edx
  char v19; // al
  void (__stdcall **v20)(int); // edx
  char v21; // al
  void (__stdcall **v22)(int); // edx
  char v23; // al
  void (__stdcall **v24)(int); // edx
  char v25; // al
  void (__stdcall **v26)(int); // edx
  char v27; // al
  void (__stdcall **v28)(int); // edx
  char v29; // al
  void (__stdcall **v30)(int); // edx
  char v31; // al
  void (__stdcall **v32)(int); // edx
  char v33; // al
  void (__stdcall **v34)(int); // edx
  char v35; // al
  void (__stdcall **v36)(int); // edx
  char v37; // al
  void (__stdcall **v38)(int); // edx
  char v39; // al
  void (__stdcall **v40)(int); // edx
  char v41; // al
  void (__stdcall **v42)(int); // edx
  char v43; // al
  int (__stdcall **v44)(int); // edx
  float a5; // [esp+0h] [ebp-30h]
  float a5a; // [esp+0h] [ebp-30h]
  float a5b; // [esp+0h] [ebp-30h]
  float a5c; // [esp+0h] [ebp-30h]
  float a5d; // [esp+0h] [ebp-30h]
  float a5e; // [esp+0h] [ebp-30h]
  float a5f; // [esp+0h] [ebp-30h]
  int a5g; // [esp+0h] [ebp-30h]
  int a5h; // [esp+0h] [ebp-30h]
  CCBAIWindow *m_TempStorageNGH; // [esp+28h] [ebp-8h]
  int *a1; // [esp+2Ch] [ebp-4h]

  v2 = 0;
  m_TempStorageNGH = (CCBAIWindow *)this->m_pCBSystem->m_pStage->m_TempStorageNGH;
  do
  {
    result = (int)&this->m_sCombatDialog[892 * v2];
    a1 = (int *)result;
    if ( *(_BYTE *)(result + 577) )
    {
      v4 = *(unsigned __int8 *)(result + 576);
      a5 = (float)*(int *)(result + 592);
      ((UIWnd *)*((UIWnd **)this->m_pUI + v4 + 255))->FindChild(a5);
      a5a = (float)a1[150];
      ((UIWnd *)*((UIWnd **)this->m_pUI + v4 + 259))->FindChild(a5a);
      a5b = (float)a1[152];
      ((UIWnd *)*((UIWnd **)this->m_pUI + v4 + 263))->FindChild(a5b);
      a5c = (float)a1[147];
      ((UIWnd *)*((UIWnd **)this->m_pUI + v4 + 255))->FindChildByName(a5c);
      a5d = (float)a1[149];
      ((UIWnd *)*((UIWnd **)this->m_pUI + v4 + 259))->FindChildByName(a5d);
      a5e = (float)a1[151];
      ((UIWnd *)*((UIWnd **)this->m_pUI + v4 + 263))->FindChildByName(a5e);
      if ( !v2 )
      {
        m_pUI = (UIWnd **)this->m_pUI;
        if ( m_pUI[30]->m_bvisible == 1 )
        {
          a5f = *(float *)&this->m_Role[0]._rest[460] * 0.25;
          ((UIWnd *)m_pUI[267])->FindChildByName(a5f);
          if ( this->m_Role[0].nHP > 0 )
          {
            m_pCBSystem = (CCBSystem *)this->m_pCBSystem;
            if ( m_pCBSystem->m_fTimeFund - *(float *)&this->m_dwEXPTable[376] > 0.1 )
            {
              *(float *)&a5g = *(float *)&this->m_Role[0]._rest[460] * 0.1;
              ((C2DSpark *)m_pCBSystem->m_p2DSpark)->CreateMore(25, 570, 20, a5g);
              if ( *(float *)&this->m_Role[0]._rest[460] > 199.89999 )
              {
                *(float *)&a5h = *(float *)&this->m_Role[0]._rest[460] * 0.1;
                ((C2DSpark *)this->m_pCBSystem->m_p2DSpark)->CreateMore(25, 570, 20, a5h);
              }
              *(float *)&this->m_dwEXPTable[376] = this->m_pCBSystem->m_fTimeFund;
            }
          }
        }
      }
      result = (int)this->m_pUI;
      if ( *(_DWORD *)(*(_DWORD *)(result + 4 * v4 + 120) + 56) == 1 )
      {
        m_TempStorageNGH->SetText(dword_17AA808[v4] + 22, dword_17AA818[v4] + 5);
        m_TempStorageNGH->SetText(dword_17AA828[v4] + 31, dword_17AA838[v4] + 5);
        m_TempStorageNGH->SetText(dword_17AA848[v4] + 23, dword_17AA858[v4] + 5);
        if ( this->GetRoleField(v2, 3) )
        {
          ((NPC *)-13002067)->UpdateAnim();
        }
        else if ( this->GetRoleField(v2, 4) )
        {
          ((NPC *)-2198223)->UpdateAnim();
        }
        else if ( this->GetRoleField(v2, 2) )
        {
          ((NPC *)-6002966)->UpdateAnim();
        }
        else if ( this->GetRoleField(v2, 1) )
        {
          ((NPC *)-11356565)->UpdateAnim();
        }
        else if ( this->GetRoleField(v2, 5) )
        {
          ((NPC *)-2707878)->UpdateAnim();
        }
        else
        {
          ((NPC *)-1)->UpdateAnim();
        }
        if ( a1[147] <= 0 )
          ((NPC *)-11513776)->UpdateAnim();
        RoleField = this->GetRoleField(v2, 6);
        v8 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 44);
        if ( RoleField )
          (*v8)(1);
        else
          (*v8)(0);
        v9 = this->GetRoleField(v2, 7);
        v10 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 55);
        if ( v9 )
          (*v10)(1);
        else
          (*v10)(0);
        v11 = this->GetRoleField(v2, 8);
        v12 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 66);
        if ( v11 )
          (*v12)(1);
        else
          (*v12)(0);
        v13 = this->GetRoleField(v2, 9);
        v14 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 77);
        if ( v13 )
          (*v14)(1);
        else
          (*v14)(0);
        v15 = this->GetRoleField(v2, 12);
        v16 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 110);
        if ( v15 )
          (*v16)(1);
        else
          (*v16)(0);
        v17 = this->GetRoleField(v2, 13);
        v18 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 121);
        if ( v17 )
          (*v18)(1);
        else
          (*v18)(0);
        v19 = this->GetRoleField(v2, 10);
        v20 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 88);
        if ( v19 )
          (*v20)(1);
        else
          (*v20)(0);
        v21 = this->GetRoleField(v2, 11);
        v22 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 99);
        if ( v21 )
          (*v22)(1);
        else
          (*v22)(0);
        v23 = this->GetRoleField(v2, 14);
        v24 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 132);
        if ( v23 )
          (*v24)(1);
        else
          (*v24)(0);
        v25 = this->GetRoleField(v2, 15);
        v26 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 143);
        if ( v25 )
          (*v26)(1);
        else
          (*v26)(0);
        v27 = this->GetRoleField(v2, 16);
        v28 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 154);
        if ( v27 )
          (*v28)(1);
        else
          (*v28)(0);
        v29 = this->GetRoleField(v2, 17);
        v30 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 165);
        if ( v29 )
          (*v30)(1);
        else
          (*v30)(0);
        v31 = this->GetRoleField(v2, 18);
        v32 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 176);
        if ( v31 )
          (*v32)(1);
        else
          (*v32)(0);
        v33 = this->GetRoleField(v2, 19);
        v34 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 187);
        if ( v33 )
          (*v34)(1);
        else
          (*v34)(0);
        v35 = this->GetRoleField(v2, 20);
        v36 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 198);
        if ( v35 )
          (*v36)(1);
        else
          (*v36)(0);
        v37 = this->GetRoleField(v2, 21);
        v38 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 209);
        if ( v37 )
          (*v38)(1);
        else
          (*v38)(0);
        v39 = this->GetRoleField(v2, 22);
        v40 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 220);
        if ( v39 )
          (*v40)(1);
        else
          (*v40)(0);
        v41 = this->GetRoleField(v2, 23);
        v42 = (void (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 231);
        if ( v41 )
          (*v42)(1);
        else
          (*v42)(0);
        v43 = this->GetRoleField(v2, 26);
        v44 = (int (__stdcall **)(int))**((_DWORD **)this->m_pUI + v4 + 242);
        if ( v43 )
          result = (*v44)(1);
        else
          result = (*v44)(0);
      }
    }
    ++v2;
  }
  while ( v2 < 5 );
  return result;
}

// 0x004F98B0
int CCBRoleState::ApplyDamage(int roleIdx, int dmg)
{
  int v3; // ebx
  int v4; // edi
  int RoleState; // eax
  int v7; // ebx
  signed int v8; // esi
  int v9; // edx
  int v10; // edi
  __int64 v11; // rax
  unsigned int v12; // ebx
  int v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int RoleHP; // eax
  int v19; // ecx
  int *v20; // edx
  int v21; // eax
  int v22; // edi
  int v23; // ebx
  int v24; // eax
  int v25; // edi
  int SpeedBonus; // edi
  int v27; // edi
  int v28; // ebx
  int AttackBonus; // edi
  int v30; // edi
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int CanAction; // eax
  int v36; // [esp-4h] [ebp-1Ch]
  int v37; // [esp-4h] [ebp-1Ch]
  int v38; // [esp+Ch] [ebp-Ch]
  int v39; // [esp+10h] [ebp-8h] BYREF
  int v40; // [esp+14h] [ebp-4h] BYREF
  int *v41; // [esp+20h] [ebp+8h]
  int v42; // [esp+20h] [ebp+8h]
  int *v43; // [esp+20h] [ebp+8h]
  int roleIdxa; // [esp+28h] [ebp+10h] BYREF
  int v45; // [esp+2Ch] [ebp+14h]
  int a2; // [esp+30h] [ebp+18h]

  v3 = 0;
  v4 = 0;
  v39 = 0;
  v40 = 0;
  switch ( roleIdx )
  {
    case 1:
      RoleState = this->GetRoleState(roleIdxa);
      v7 = dmg;
      v45 = 10 * (this->GetRoleState(dmg) + 8 - RoleState);
      *(float *)&dmg = (double)v45 * *(float *)&this->m_Role[0]._rest[892 * v7 + 40] * 0.0099999998;
      roleIdxa = (int)*(float *)&dmg;
      v4 = roleIdxa + v45;
      dmg = roleIdxa + v45;
      if ( !byte_5DFDEB )
        goto LABEL_76;
      *(float *)&dmg = (double)dmg * 0.2;
      roleIdxa = (int)*(float *)&dmg;
      v8 = abs32(roleIdxa);
      if ( !v8 )
        goto LABEL_76;
      v9 = (((214013 * g_RandSeed + 2531011) >> 16) & 0x7FFF) % v8;
      g_nRandCallCount += 2;
      g_RandSeed = 214013 * (214013 * g_RandSeed + 2531011) + 2531011;
      if ( ((g_RandSeed >> 16) & 0x3FFu) < 0x200 )
        v10 = v4 - v9;
      else
        v10 = v9 + v4;
      LODWORD(v11) = v10;
      return v11;
    case 2:
      if ( *(float *)&v45 == 0.0 )
        goto LABEL_54;
      ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(a2);
      v12 = dmg;
      if ( (unsigned int)dmg > 4 )
      {
        v41 = (int *)&this->m_sCombatDialog[892 * dmg];
        v4 = abs32((__int64)(((double)v41[146] * 0.050000001 + 0.1) * (double)v45));
        dmg = v4;
        if ( byte_5DFDEB )
        {
          *(float *)&dmg = (double)dmg * 0.1;
          *(float *)&dmg = COERCE_FLOAT(abs32((int)*(float *)&dmg));
          if ( *(float *)&dmg != 0.0 )
          {
            v14 = (((214013 * g_RandSeed + 2531011) >> 16) & 0x7FFF) % dmg;
            g_nRandCallCount += 2;
            g_RandSeed = 214013 * (214013 * g_RandSeed + 2531011) + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FFu) < 0x200 )
              v4 -= v14;
            else
              v4 += v14;
          }
        }
        if ( v45 <= 0 )
          goto LABEL_23;
      }
      else
      {
        v41 = (int *)&this->m_sCombatDialog[892 * dmg];
        v4 = abs32((__int64)(((double)v41[146] * 0.050000001 + 1.0) * (double)v45));
        dmg = v4;
        if ( byte_5DFDEB )
        {
          *(float *)&dmg = (double)dmg * 0.1;
          *(float *)&dmg = COERCE_FLOAT(abs32((int)*(float *)&dmg));
          if ( *(float *)&dmg != 0.0 )
          {
            v13 = (((214013 * g_RandSeed + 2531011) >> 16) & 0x7FFF) % dmg;
            g_nRandCallCount += 2;
            g_RandSeed = 214013 * (214013 * g_RandSeed + 2531011) + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FFu) < 0x200 )
              v4 -= v13;
            else
              v4 += v13;
          }
        }
        if ( v45 <= 0 )
LABEL_23:
          v4 = -v4;
      }
      if ( v12 > 4 )
        goto LABEL_76;
      *(float *)&dmg = 0.0;
      roleIdxa = 0;
      sub_4FA620(this->m_sCombatDialog, v12, a2, &dmg, &roleIdxa);
      a2->IsAllEnemyDead(&v39, &v40);
      if ( v39->GetRole(v41[284]) || v40->GetRole(v41[284]) )
        v4 += v4 / 2;
      if ( v39 > 0 && v39 < 6 )
      {
        v36 = v41[284];
        v15 = this->CheckDeath(v39);
        if ( v15->GetRole(v36) )
          v4 += v4 / -2;
      }
      if ( v40 <= 0 )
        goto LABEL_76;
      if ( v40 >= 6 )
        goto LABEL_76;
      v37 = v41[284];
      v16 = this->CheckDeath(v40);
      if ( !v16->GetRole(v37) )
        goto LABEL_76;
      LODWORD(v11) = v4 / -2 + v4;
      return v11;
    case 3:
      v17 = dmg;
      this->GetRoleHP(dmg);
      RoleHP = this->GetRoleHP(roleIdxa);
      *(float *)&v45 = 0.0;
      *(float *)&dmg = 0.0;
      roleIdxa = 0;
      v42 = *(&this->m_Role[0].nLevel + 223 * v17);
      this->GetRoleMP(RoleHP);
      if ( v45 < dmg )
      {
        v19 = dmg - v45;
        v20 = (int *)&this->m_Role[0].nLevel + 223 * v45;
        do
        {
          if ( *((_BYTE *)v20 - 7) )
          {
            ++roleIdxa;
            v3 += *v20;
          }
          v20 += 223;
          --v19;
        }
        while ( v19 );
      }
      v38 = v3 / roleIdxa;
      v21 = this->GetRoleState(v17);
      v22 = v45;
      v23 = v21;
      a2 = (int)&unk_FFFFFF;
      if ( v45 < dmg )
      {
        roleIdxa = (int)(&this->m_Role[0].bValid + 892 * v45);
        do
        {
          if ( *(_BYTE *)roleIdxa )
          {
            v24 = this->GetRoleState(v22);
            if ( v24 < a2 )
              a2 = this->GetRoleState(v22);
          }
          ++v22;
          roleIdxa += 892;
        }
        while ( v22 < dmg );
      }
      LODWORD(v11) = 10 * ((v42 - v38) * (v23 - a2) + 3);
      return v11;
    case 4:
      v25 = 5 - this->GetRoleState(roleIdxa);
      LODWORD(v11) = this->GetRoleState(dmg) + v25;
      return v11;
    case 5:
      SpeedBonus = this->GetSpeedBonus(dmg);
      v4 = 5 * (this->GetSpeedBonus(roleIdxa) - SpeedBonus);
      if ( v4 >= 0 )
        goto LABEL_76;
      LODWORD(v11) = 0;
      return v11;
    case 6:
      v27 = dmg;
      if ( this->GetRoleState(dmg) > 0 )
        return (__int64)(sqrt((double)(this->GetRoleState(v27) / 2)) * 10.0);
      else
LABEL_54:
        LODWORD(v11) = 0;
      return v11;
    case 7:
      v28 = dmg;
      v43 = (int *)&this->m_sCombatDialog[892 * dmg];
      AttackBonus = this->GetAttackBonus(dmg);
      *(float *)&v45 = (double)(AttackBonus - this->GetDefenseBonus(roleIdxa))
                     * ((double)v43[146] * 0.0049999999 + 1.0);
      a2 = (int)*(float *)&v45;
      v30 = -a2;
      v45 = -a2;
      if ( byte_5DFDEB )
      {
        *(float *)&v45 = (double)v45 * 0.1;
        a2 = (int)*(float *)&v45;
        *(float *)&v45 = COERCE_FLOAT(abs32(a2));
        if ( *(float *)&v45 == 0.0 )
        {
          v45 = v30;
        }
        else
        {
          v31 = (((214013 * g_RandSeed + 2531011) >> 16) & 0x7FFF) % v45;
          g_nRandCallCount += 2;
          g_RandSeed = 214013 * (214013 * g_RandSeed + 2531011) + 2531011;
          if ( ((g_RandSeed >> 16) & 0x3FFu) < 0x200 )
            v30 -= v31;
          else
            v30 += v31;
          v28 = dmg;
          v45 = v30;
        }
      }
      else
      {
        v45 = -a2;
      }
      if ( *((_BYTE *)v43 + 650) || *((_BYTE *)v43 + 649) )
      {
        if ( byte_5DFDEB )
        {
          a2 = (int)5.0;
          *(float *)&v45 = COERCE_FLOAT(abs32((int)5.0));
          if ( *(float *)&v45 == 0.0 )
          {
            v32 = 100;
          }
          else
          {
            v33 = (((214013 * g_RandSeed + 2531011) >> 16) & 0x7FFF) % v45;
            g_nRandCallCount += 2;
            g_RandSeed = 214013 * (214013 * g_RandSeed + 2531011) + 2531011;
            if ( ((g_RandSeed >> 16) & 0x3FFu) < 0x200 )
              v32 = 100 - v33;
            else
              v32 = v33 + 100;
            v28 = dmg;
          }
        }
        else
        {
          v32 = 100;
        }
        v45 = v30 * (v32 - 45) / 100;
      }
      CanAction = this->CanAction(v28, roleIdxa, 0);
      *(float *)&dmg = (1.0 - (double)CanAction * 0.050000001) * (double)v45;
      roleIdxa = (int)*(float *)&dmg;
      v4 = roleIdxa;
      goto LABEL_76;
    default:
LABEL_76:
      LODWORD(v11) = v4;
      return v11;
  }
}

// 0x004FA540
int CCBRoleState::CheckRoleStatus(int roleIdx)
{
  int v3; // [esp+8h] [ebp+8h]
  int v4; // [esp+Ch] [ebp+Ch]
  int v5; // [esp+10h] [ebp+10h]

  *(_DWORD *)roleIdx = v3;
  *(_DWORD *)(roleIdx + 4) = v4;
  *(_DWORD *)(roleIdx + 8) = v5;
  return roleIdx;
}

// 0x004FA6A0
int CCBRoleState::CheckDeath(int roleIdx)
{
  int result; // eax

  switch ( roleIdx )
  {
    case 1:
      result = 5;
      break;
    case 2:
      result = 1;
      break;
    case 3:
      result = 4;
      break;
    case 4:
      result = 2;
      break;
    case 5:
      result = 3;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x004FA8B0
int CCBRoleState::Revive(int roleIdx)
{
  this->GetRoleMP(1);
  return 1;
}
