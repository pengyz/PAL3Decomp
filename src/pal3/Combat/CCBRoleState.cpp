#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBRoleState.h"

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
int sub_4F2C30(...);
int sub_4F4820(...);
int sub_4F4AA0(...);
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
int sub_4FA930(...);
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
  if ( this->m_sCombatDialog[892 * roleIdx + 577] )
    return this->m_sCombatDialog[892 * roleIdx + 578];
  else
    return 0;
}

// 0x004ED060
char CCBRoleState::GetRoleType(int roleIdx)
{
  char *v2; // eax

  v2 = &this->m_sCombatDialog[892 * roleIdx];
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
    result = (int)&this->m_sCombatDialog[5048];
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
    result = (int)&this->m_sCombatDialog[5038];
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

  v1 = &this->m_sCombatDialog[1112];
  v2 = &g_SceneMgr.m_info[936];
  v26 = &this->m_sCombatDialog[1112];
  do
  {
    LOBYTE(v3) = *(v1 - 535);
    v4 = v1 - 4;
    if ( (_BYTE)v3 )
    {
      memset(v4, 0, 0x1Cu);
      if ( (int)v2 < (int)&g_SceneMgr.m_info[936] || (int)v2 >= (int)&g_SceneMgr.m_info[7976] )
      {
        v21 = 580;
        v25 = v1;
        do
        {
          v22 = *(_DWORD *)(PAL_GDB::~PAL_GDB(g_GDB, *((_DWORD *)v4 - 139)) + v21) << 16;
          v23 = *(_DWORD *)(PAL_GDB::~PAL_GDB(g_GDB, *((_DWORD *)v4 - 139)) + v21);
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
  while ( (int)v2 < (int)&g_SceneMgr.m_info[16424] );
  return v3;
}

// 0x004EDF10
char CCBRoleState::~CCBRoleState()
{
  int v2; // ebp
  char *v3; // edi
  char *v4; // esi
  char result; // al

  v2 = 0;
  v3 = &g_SceneMgr.m_info[888];
  v4 = &this->m_sCombatDialog[656];
  do
  {
    result = *(v4 - 79);
    if ( result )
    {
      if ( *((_DWORD *)v3 - 5) )
      {
        *(float *)v4 = (double)*(__int16 *)(*((_DWORD *)v3 - 3) + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(*((_DWORD *)v3 - 3) + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(*((_DWORD *)v3 - 3) + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(*((_DWORD *)v3 - 3) + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(*((_DWORD *)v3 - 3) + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(*((_DWORD *)v3 - 3) + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(*((_DWORD *)v3 - 3) + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(*((_DWORD *)v3 - 3) + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(*((_DWORD *)v3 - 3) + 628));
      }
      if ( *((_DWORD *)v3 - 2) )
      {
        *(float *)v4 = (double)*(__int16 *)(*(_DWORD *)v3 + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(*(_DWORD *)v3 + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(*(_DWORD *)v3 + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(*(_DWORD *)v3 + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(*(_DWORD *)v3 + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(*(_DWORD *)v3 + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(*(_DWORD *)v3 + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(*(_DWORD *)v3 + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(*(_DWORD *)v3 + 628));
      }
      if ( *((_DWORD *)v3 + 1) )
      {
        *(float *)v4 = (double)*(__int16 *)(*((_DWORD *)v3 + 3) + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(*((_DWORD *)v3 + 3) + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(*((_DWORD *)v3 + 3) + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(*((_DWORD *)v3 + 3) + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(*((_DWORD *)v3 + 3) + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(*((_DWORD *)v3 + 3) + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(*((_DWORD *)v3 + 3) + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(*((_DWORD *)v3 + 3) + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(*((_DWORD *)v3 + 3) + 628));
      }
      if ( *((_DWORD *)v3 + 4) )
      {
        *(float *)v4 = (double)*(__int16 *)(*((_DWORD *)v3 + 6) + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(*((_DWORD *)v3 + 6) + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(*((_DWORD *)v3 + 6) + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(*((_DWORD *)v3 + 6) + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(*((_DWORD *)v3 + 6) + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(*((_DWORD *)v3 + 6) + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(*((_DWORD *)v3 + 6) + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(*((_DWORD *)v3 + 6) + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(*((_DWORD *)v3 + 6) + 628));
      }
      if ( *((_DWORD *)v3 + 7) )
      {
        *(float *)v4 = (double)*(__int16 *)(*((_DWORD *)v3 + 9) + 768) + *(float *)v4;
        *((float *)v4 + 1) = (double)*(__int16 *)(*((_DWORD *)v3 + 9) + 770) + *((float *)v4 + 1);
        *((float *)v4 + 3) = (double)*(__int16 *)(*((_DWORD *)v3 + 9) + 774) + *((float *)v4 + 3);
        *((float *)v4 + 2) = (double)*(__int16 *)(*((_DWORD *)v3 + 9) + 772) + *((float *)v4 + 2);
        *((float *)v4 + 4) = (double)*(__int16 *)(*((_DWORD *)v3 + 9) + 644) + *((float *)v4 + 4);
        *((float *)v4 + 5) = (double)*(__int16 *)(*((_DWORD *)v3 + 9) + 646) + *((float *)v4 + 5);
        *((float *)v4 + 6) = (double)*(__int16 *)(*((_DWORD *)v3 + 9) + 648) + *((float *)v4 + 6);
        if ( *(_WORD *)(*((_DWORD *)v3 + 9) + 750) )
        {
          v4[511] = 1;
          *((_WORD *)v4 + 309) = 0x7FFF;
        }
        this->Reset(v2, (float *)*(unsigned __int8 *)(*((_DWORD *)v3 + 9) + 628));
      }
      if ( *((_DWORD *)v3 - 5) == 80015 )
      {
        if ( *((_DWORD *)v3 - 2) == 84018
          && *((_DWORD *)v3 + 1) == 83012
          && *((_DWORD *)v3 + 4) == 8153
          && *((_DWORD *)v3 + 7) == 8154 )
        {
          v4[44] = 1;
        }
        if ( *((_DWORD *)v3 - 5) == 80015
          && *((_DWORD *)v3 - 2) == 84018
          && *((_DWORD *)v3 + 1) == 83012
          && *((_DWORD *)v3 + 4) == 8154
          && *((_DWORD *)v3 + 7) == 8153 )
        {
          v4[44] = 1;
        }
      }
      result = -82;
      if ( *((_DWORD *)v3 + 4) == 8110 || *((_DWORD *)v3 + 7) == 8110 )
        v4[45] = 1;
    }
    v3 += 1408;
    ++v2;
    v4 += 892;
  }
  while ( (int)v3 < (int)&g_SceneMgr.m_info[7928] );
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
      result = (float *)&this->m_sCombatDialog[892 * a2 + 684];
      * result = (*)*result + 5.0;
      break;
    case 0x15u:
      v4 = (float *)&this->m_sCombatDialog[892 * a2];
      v4[171] = v4[171] + 15.0;
      v4[172] = v4[172] + 5.0;
      goto LABEL_4;
    case 0x16u:
LABEL_4:
      result = (float *)&this->m_sCombatDialog[892 * a2 + 692];
      * result = (*)*result + 10.0;
      break;
    case 0x17u:
      result = (float *)&this->m_sCombatDialog[892 * a2 + 696];
      *(_DWORD *)result += 5;
      break;
    case 0x18u:
      result = (float *)&this->m_sCombatDialog[892 * a2 + 684];
      * result = (*)*result + 20.0;
      break;
    default:
      result = a3;
      break;
  }
  return result;
}

// 0x004EE540
char CCBRoleState::Create(gbGeomNode **this)
{
  int *v1; // ebp
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
  char ArgList; // [esp+A14h] [ebp-80Ch] BYREF
  char v16; // [esp+E14h] [ebp-40Ch] BYREF
  int v17; // [esp+121Ch] [ebp-4h]

  v1 = MEMORY[0xC04738];
  v2 = this + 350;
  do
  {
    LOBYTE(v3) = *((_BYTE *)v2 - 823);
    if ( (_BYTE)v3 )
    {
      v3 = *(v1 - 2);
      if ( v3 )
      {
        sprintf(Buffer, "weapon\\%s\\%s.pol", (const char *)(*v1 + 36), (const char *)(*v1 + 36));
        sprintf(
          v12,
          "weapon\\%s\\%s%s.tga",
          (const char *)(*v1 + 36),
          (const char *)(*v1 + 36),
          (const char *)(*v1 + 66));
        v4 = (gbGeomNode *)operator new(0x118u);
        v5 = v4;
        v17 = 0;
        if ( v4 )
        {
          v4->gbGeomNode();
          *(_DWORD *)v5->gbVisNode = &off_56A66C;
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
            (const void *)Logger::FormatException((char)&ArgList, (int)aFailToCreateWe, (int)aDProjectPal3Co_2, 1484),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        v6->LoadFromFile(Buffer, 0, 0);
        gbGeomNode::ReplaceTexture(*v2, v12);
        v7 = (gbGeomNode *)operator new(0x118u);
        v8 = v7;
        v17 = 1;
        if ( v7 )
        {
          v7->gbGeomNode();
          *(_DWORD *)v8->gbVisNode = &off_56A66C;
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
          qmemcpy(
            v14,
            (const void *)Logger::FormatException((char)&v16, (int)aFailToCreateWe, (int)aDProjectPal3Co_2, 1494),
            sizeof(v14));
          _CxxThrowException(v14, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        v9->LoadFromFile(Buffer, 0, 0);
        gbGeomNode::ReplaceTexture(v2[3], v12);
        LOBYTE(v3) = 1;
        *(_DWORD *)&(*v2)->gbVisNode[260] = 1;
        *(_DWORD *)&v2[3]->gbVisNode[260] = 1;
      }
    }
    v1 += 352;
    v2 += 223;
  }
  while ( (int)v1 < (int)&MEMORY[0xC062B8] );
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

  v1 = &this->m_sCombatDialog[1412];
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
  int v3; // esi

  v3 = *(_DWORD *)(*((_DWORD *)this + 130) + 4);
  if ( a3 == 1 )
  {
    if ( !a2 )
      (***(void (****)(_DWORD, int))(v3 + 1068))(*(_DWORD *)(v3 + 1068), 1);
    (***(void (****)(_DWORD, int))(v3 + 4 * a2 + 120))(*(_DWORD *)(v3 + 4 * a2 + 120), 1);
    (***(void (****)(_DWORD, int))(v3 + 4 * a2 + 1020))(*(_DWORD *)(v3 + 4 * a2 + 1020), 1);
    (***(void (****)(_DWORD, int))(v3 + 4 * a2 + 1052))(*(_DWORD *)(v3 + 4 * a2 + 1052), 1);
    return (***(int (****)(_DWORD, int))(v3 + 4 * a2 + 1036))(*(_DWORD *)(v3 + 4 * a2 + 1036), 1);
  }
  else
  {
    if ( !a2 )
      (***(void (****)(_DWORD, _DWORD))(v3 + 1068))(*(_DWORD *)(v3 + 1068), 0);
    (***(void (****)(_DWORD, _DWORD))(v3 + 4 * a2 + 120))(*(_DWORD *)(v3 + 4 * a2 + 120), 0);
    (***(void (****)(_DWORD, _DWORD))(v3 + 4 * a2 + 1020))(*(_DWORD *)(v3 + 4 * a2 + 1020), 0);
    (***(void (****)(_DWORD, _DWORD))(v3 + 4 * a2 + 1052))(*(_DWORD *)(v3 + 4 * a2 + 1052), 0);
    return (***(int (****)(_DWORD, _DWORD))(v3 + 4 * a2 + 1036))(*(_DWORD *)(v3 + 4 * a2 + 1036), 0);
  }
}

// 0x004EE870
int CCBRoleState::InitUI(int a2)
{
  return (int)&this->m_sCombatDialog[892 * a2 + 552];
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

  RoleNum = g_GDB->GDB_GetRoleNum(a2[1]);
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
  int v8; // eax
  int v9; // edi
  _DWORD *v10; // ebp
  int v11; // ecx
  _BYTE *v12; // esi
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
  Proxy = Concurrency::details::(Concurrency::details::InternalContextBase *->GetProxy()g_GDB);
  v23 = 0;
  if ( (int)Proxy <= 0 )
    return 0;
  while ( 2 )
  {
    v6 = 1;
    v7 = sub_479260(g_GDB, v5);
    *a4 = v7;
    v8 = g_GDB->GDB_GetItemNum(v7);
    if ( *(_DWORD *)(v8 + 56) != a3 )
      goto LABEL_53;
    if ( *(_DWORD *)(v8 + 36) != *(this + 223 * v4 + 138) )
      goto LABEL_52;
    v9 = 0;
    v10 = (_DWORD *)(v8 + 36);
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
      v12 = this + 223 * v11;
      if ( !v12[577] )
        v6 = 0;
      v13 = *(_BYTE *)(v8 + v9 + 52);
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
      if ( *(_BYTE *)(v8 + v9 + 60) != v12[648] )
        v6 = 0;
LABEL_33:
      ++v9;
      ++v10;
    }
    while ( v9 < 4 );
    if ( !v6 )
      goto LABEL_51;
    v17 = (int *)(v8 + 68);
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
          if ( *v17 >= 0 && v20 < 26 && !(unsigned __int8)v19->GetRoleField(v20 + 1) )
            v6 = 0;
          if ( *v17 == 26 && !(unsigned __int8)v19->IsRoleInForce() )
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
  v4 = &this->m_sCombatDialog[892 * a3];
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
  result = CCBRoleState::CalSneakAttack((int)this, a2[2], a3);
  if ( result )
    return 1;
  return result;
}

// 0x004EEE60
char CCBRoleState::IsAlive(int _this, int a2, int a3)
{
  char result; // al
  int v5; // eax

  if ( !*(_BYTE *)(this + 577) )
    return 0;
  v5 = *(_DWORD *)(this + 636);
  if ( !v5 )
    return 0;
  if ( v5 != a2 )
    return 0;
  result = (CCBRoleState *->IsRoleAlive()this, 0);
  if ( result )
  {
    if ( *(_DWORD *)(this + 1136) == 6 )
    {
      if ( (CCBRoleState *->GetRoleField()this, 0, 14) )
      {
        return 0;
      }
      else
      {
        result = CCBStageRole::EndTask(*(float **)(*(_DWORD *)(this + 524) + 24), a2, a3);
        if ( result )
        {
          result = CCBStageRole::ForceEndTaskByPFN(*(float **)(*(_DWORD *)(this + 524) + 4 * a2 + 24));
          if ( result )
            return CCBStage::ForceDelTask(*(char **)(this + 524), 18) != 0;
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
char CCBRoleState::IsBoss(_DWORD *a1, int a2)
{
  int v2; // edi
  int v3; // ebp
  int v4; // esi
  __int16 *v5; // ebx
  __int16 *v6; // ebp
  int v7; // eax
  int v8; // eax
  char result; // al
  char v10; // [esp+12h] [ebp-Ah]
  char v11; // [esp+13h] [ebp-9h]
  char v12; // [esp+14h] [ebp-8h]
  char v13; // [esp+15h] [ebp-7h]
  char v14; // [esp+16h] [ebp-6h]
  char v15; // [esp+17h] [ebp-5h]

  v2 = 0;
  v3 = 0;
  if ( *a1 == 262 )
    v3 = g_GDB->GDB_GetSkillNum(a1[1]);
  else
    v2 = g_GDB->GDB_GetRoleNum(a1[1]);
  v4 = 0;
  v5 = (__int16 *)(v2 + 618);
  v15 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v6 = (__int16 *)(v3 + 700);
  do
  {
    if ( *a1 == 262 )
      v7 = *v6;
    else
      v7 = *v5;
    v8 = v7 - 1;
    if ( v8 )
    {
      if ( v8 == 1 )
      {
        a2->ProcessRound(v4 + 1, 0, 1);
        switch ( v4 )
        {
          case 13:
            v15 = 1;
            break;
          case 14:
            v10 = 1;
            break;
          case 15:
            v11 = 1;
            break;
          case 16:
            v12 = 1;
            break;
          case 17:
            v14 = 1;
            break;
          case 18:
            v13 = 1;
            break;
          default:
            break;
        }
      }
    }
    else
    {
      a2->ProcessRound(v4 + 1, 1, 1);
    }
    ++v4;
    ++v6;
    ++v5;
  }
  while ( v4 < 25 );
  if ( v15 )
  {
    if ( v10 && v11 && v12 && v13 && v14 )
    {
      CScreenMode::GetInstance();
      return aWd019->AudioSetPosition(1);
    }
    CScreenMode::GetInstance();
    aWd017->AudioSetPosition(1);
  }
  if ( v10 )
  {
    CScreenMode::GetInstance();
    aWd017->AudioSetPosition(1);
  }
  if ( v11 )
  {
    CScreenMode::GetInstance();
    aWd017->AudioSetPosition(1);
  }
  if ( v12 )
  {
    CScreenMode::GetInstance();
    aWd018->AudioSetPosition(1);
  }
  if ( v13 )
  {
    CScreenMode::GetInstance();
    aWd018->AudioSetPosition(1);
  }
  result = v14;
  if ( v14 )
  {
    CScreenMode::GetInstance();
    return aWd018->AudioSetPosition(1);
  }
  return result;
}

// 0x004EF6A0
int CCBRoleState::IsAllWeDead(int a2)
{
  return *(this + 223 * a2 + 284);
}

// 0x004EF6C0
_DWORD * CCBRoleState::IsAllEnemyDead(int a1, int *a2, int *a3)
{
  int v3; // eax
  int v4; // ecx
  _DWORD *result; // eax

  v3 = g_GDB->GDB_GetRoleNum(a1);
  v4 = 1;
  result = (_DWORD *)(v3 + 8);
  *a3 = 0;
  *a2 = 0;
  do
  {
    if ( *result == 1 )
    {
      if ( *a2 )
        *a3 = v4;
      else
        *a2 = v4;
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
  for ( i = &this->m_sCombatDialog[892 * a3 + 1112]; !*(_DWORD *)i; i += 4 )
  {
    if ( ++v5 >= 6 )
      return 0;
  }
  v7 = 1;
  for ( j = &this->m_sCombatDialog[892 * a2 + 1112]; (*(_DWORD *)j & 0xFFFF0000) == 0; j += 4 )
  {
    if ( ++v7 >= 6 )
      return 0;
  }
  v9 = this->CheckDeath(v7);
  return (*(_DWORD *)&this->m_sCombatDialog[892 * a3 + 1108 + 4 * v9] != 0)
       - (*(_DWORD *)&this->m_sCombatDialog[892 * a3 + 1108 + 4 * sub_4FA700(v7)] != 0);
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
    v6 = *(_DWORD *)(*(_DWORD *)&g_SceneMgr.m_info[1408 * dmg + 936] + 764);
    if ( v6 > 1 )
      result /= v6;
  }
  if ( this->m_sCombatDialog[892 * dmg + 1160] )
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
char CCBRoleState::RandSetEnemyPos(const void *a1)
{
  char result; // al
  _DWORD v2[11]; // [esp+8h] [ebp-2Ch] BYREF

  result = 0;
  qmemcpy(v2, a1, sizeof(v2));
  switch ( v2[0] )
  {
    case 0x103:
      result = sub_4F0A10(v2);
      break;
    case 0x104:
      result = v2->GetDeadRoleNumInForce();
      break;
    case 0x105:
      result = v2->GetAliveRoleNumInForce();
      break;
    case 0x106:
      result = v2->GetCastFightSkillSuccess();
      break;
    case 0x10D:
      result = v2->SetCoAttack();
      break;
    case 0x10E:
      result = sub_4F1C40(v2);
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
  v4 = &this->m_sCombatDialog[892 * *(_DWORD *)(roleIdx + 8)];
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
  v10 = &v18;
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
  if ( !(unsigned __int8)v18->WriteBackConfig(v19) )
    goto LABEL_47;
  if ( v7 == 2 )
  {
    *a3 = v15;
    *a4 = v14;
    return 100;
  }
  if ( *(this + 223 * v15 + 284) == 6 )
    return v15;
  if ( *(this + 223 * v14 + 284) == 6 )
    return v14;
  result = v20;
  if ( *(this + 223 * v20 + 284) != 6 )
  {
LABEL_47:
    v16 = *(this + 223 * v15 + 284);
    if ( v16 != *((_DWORD *)this + 5154) && v16 != *((_DWORD *)this + 5156) )
    {
      v17 = v16 == *((_DWORD *)this + 5158);
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
  roleIdxa = *(_DWORD *)&this->m_sCombatDialog[892 * roleIdx + 1136];
  v16 = *(_DWORD *)&this->m_sCombatDialog[892 * a3 + 1136];
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
    v10 = &this->m_sCombatDialog[20580];
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
    for ( i = &this->m_sCombatDialog[12 * v14 + 20580]; *(_DWORD *)i != v16; i += 4 )
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
  roleIdxa = *(_DWORD *)&this->m_sCombatDialog[892 * roleIdx + 1136];
  v16 = *(_DWORD *)&this->m_sCombatDialog[892 * a3 + 1136];
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
    v10 = &this->m_sCombatDialog[20616];
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
    for ( i = &this->m_sCombatDialog[8 * v14 + 20616]; *(_DWORD *)i != v16; i += 4 )
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
bool CCBRoleState::CalSneakAttack(int _this, int a2, unsigned int a3)
{
  int v4; // esi
  int v5; // ebx
  _BYTE *v6; // esi

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
      if ( *(_BYTE *)(this + 892 * a2 + 650) || *(_BYTE *)(this + 892 * a2 + 651) )
        return 1;
      if ( *(_DWORD *)(this + 892 * a3 + 1136) == (CCBRoleState *->CheckDeath()this,
                                                    *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 520) + 112) + 64)) )
      {
        v5 = 0;
        v6 = (_BYTE *)(this + 1432);
        while ( !*(v6 - 855)
             || *v6
             || *(v6 - 1)
             || *((_DWORD *)v6 - 74) != 6
             || (CCBRoleState *->SetRoleField()this, v5, 0) <= 0 )
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
      || *(_BYTE *)(this + 892 * a2 + 650)
      || *(_BYTE *)(this + 892 * a2 + 651)
      || v4 != 6
      || !*(_BYTE *)(this + 9497)
      || *(_BYTE *)(this + 10352)
      || *(_BYTE *)(this + 10351)
      || (CCBRoleState *->SetRoleField()this, 10, 0) <= 0;
}

// 0x004F0360
unsigned int CCBRoleState::InitRoleFiveMagic(int a2)
{
  unsigned int result; // eax

  result = *(unsigned __int8 *)(g_GDB->GDB_GetItemNum(*(_DWORD *)(a2 + 4)) + 592);
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
char CCBRoleState::sub_4F05A0(_DWORD *a1)
{
  char v1; // al
  char result; // al
  char v3; // al

  switch ( *a1 )
  {
    case 0x104:
    case 0x105:
    case 0x10D:
      v1 = *(_BYTE *)(g_GDB->GDB_GetRoleNum(a1[1]) + 577);
      goto LABEL_4;
    case 0x106:
      v1 = *(_BYTE *)(g_GDB->GDB_GetSkillNum(a1[1]) + 629);
LABEL_4:
      if ( v1 != 2 && v1 != 4 )
        goto LABEL_10;
      result = 1;
      break;
    case 0x10E:
      v3 = *(_BYTE *)(g_GDB->GDB_GetItemNum(a1[1]) + 592);
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
  char *i; // eax

  v2 = *(_DWORD *)(a2 + 12);
  if ( v2 > 0xA )
  {
    v5 = 0;
    for ( i = &this->m_sCombatDialog[588]; !*(_BYTE *)(a2 + v5 + 29) || !*(i - 11) || *(int *)i <= 0 || i[844]; i += 892 )
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
  int v2; // esi
  _DWORD *i; // edi

  v2 = 0;
  for ( i = this + 284; !*((_BYTE *)i - 559) || *i != a2 || (unsigned __int8)v2->SetVisible(); i += 223 )
  {
    if ( ++v2 >= 5 )
      return 0;
  }
  return 1;
}

// 0x004F0750
bool CCBRoleState::SetVisible(int roleIdx)
{
  if ( !this->m_sCombatDialog[892 * roleIdx + 578] )
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
    RoleNum = g_GDB->GDB_GetRoleNum(a2[1]);
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
    SkillNum = g_GDB->GDB_GetSkillNum(a2[1]);
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
  return byte_5D8EC8->CreateObj(0, 0x40u);
}

// 0x004F1070
char CCBRoleState::GetAliveRoleNumInForce(int a2)
{
  int v3; // edi
  int v4; // ecx
  _DWORD *v5; // esi
  _DWORD *v6; // ecx
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
  _DWORD v18[11]; // [esp+38h] [ebp-58h] BYREF
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
  v26 = &this->m_sCombatDialog[1092];
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
    if ( CCBStageRole::ForceEndTaskByPFN(*(float **)(v4 + *(_DWORD *)&this->m_sCombatDialog[524]))
      || *(_WORD *)(g_GDB->GDB_GetRoleNum(*(_DWORD *)(a2 + 4)) + 666) == 2 )
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
          && !CCBSystem::IsCmdEmpty(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v8)
          && !CCBSystem::IsCmdReady(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v8) )
        {
          g_GDB->GDB_GetRoleNum(*(_DWORD *)(a2 + 4));
          CCBSystem::GetCmdData(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v8);
        }
        if ( v23 >= 44 && v23 < 68 && this->SetRoleField(idx, 0) <= 0 )
        {
          if ( (unsigned __int8)this->Revive(v16) )
          {
            v9 = PAL_GDB::~PAL_GDB(g_GDB, *((_DWORD *)v26 - 135));
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
      memset(v18, 0, sizeof(v18));
      v18[2] = idx;
      v6 = *(_DWORD **)&this->m_sCombatDialog[524];
      LOBYTE(v18[10]) = 1;
      v18[1] = 0;
      RoleIndex = v6->GetRoleIndex(7, v18, 1);
      if ( RoleIndex == -1 )
        goto LABEL_27;
      this->CheckRoleStatus((int)roleIdx);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)CCBStage::SelectRole,
        0,
        0,
        0,
        roleIdx,
        0,
        1065353216);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], RoleIndex);
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
  if ( *(_DWORD *)&this->m_sCombatDialog[892 * v5[2] + 552] == 7312 && *v5 == 261 && v5[1] == 210 )
    sub_4F90F0(this, v5[2]);
  return 1;
}

// 0x004F1420
char CCBRoleState::GetDeadRoleNumInForce(int a2)
{
  int v3; // edx
  _DWORD *v4; // ecx
  int v5; // esi
  _DWORD *v6; // ecx
  int RoleIndex; // esi
  int v8; // esi
  int v9; // eax
  int v10; // ecx
  bool v11; // cc
  int v13; // [esp+0h] [ebp-C0h]
  _DWORD v14[11]; // [esp+Ch] [ebp-B4h] BYREF
  _DWORD v15[11]; // [esp+38h] [ebp-88h] BYREF
  _DWORD v16[11]; // [esp+64h] [ebp-5Ch] BYREF
  int v17[3]; // [esp+90h] [ebp-30h] BYREF
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
  v22 = &this->m_sCombatDialog[1092];
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
      if ( (_DWORD *->sub_4F05A0()a2)
        || CCBStageRole::ForceEndTaskByPFN(*(float **)(v23 + *(_DWORD *)&this->m_sCombatDialog[524]))
        || *(_WORD *)(g_GDB->GDB_GetRoleNum(*(_DWORD *)(a2 + 4)) + 666) == 2 )
      {
        v8 = idx;
        v20 = sub_4F2690(this, (_DWORD *)a2, idx);
        if ( v20 < 0
          && !CCBSystem::IsCmdEmpty(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v8)
          && !CCBSystem::IsCmdReady(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v8) )
        {
          CCBSystem::GetCmdData(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v8);
        }
        if ( *(_DWORD *)(a2 + 4) == 4101 )
          this->GetFirstAliveRoleInForce(0, *(_DWORD *)(a2 + 12));
        if ( v23 >= 44 && v23 < 68 && this->SetRoleField(idx, 0) <= 0 )
        {
          if ( (unsigned __int8)this->Revive(v13) )
          {
            v9 = PAL_GDB::~PAL_GDB(g_GDB, *((_DWORD *)v22 - 135));
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
        v6 = *(_DWORD **)&this->m_sCombatDialog[524];
        LOBYTE(v15[10]) = 1;
        v15[2] = idx;
        v15[1] = 0;
        RoleIndex = v6->GetRoleIndex(7, v15, 1);
        if ( RoleIndex != -1 )
        {
          this->CheckRoleStatus((int)v17);
          CCBStage::GetRoleName(
            *(_DWORD **)&this->m_sCombatDialog[524],
            RoleIndex,
            (int)CCBStage::SelectRole,
            0,
            0,
            0,
            v17,
            0,
            1065353216);
          CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], RoleIndex);
        }
      }
    }
    else
    {
      memset(v16, 0, sizeof(v16));
      v4 = *(_DWORD **)&this->m_sCombatDialog[524];
      v16[1] = 0;
      LOBYTE(v16[10]) = 1;
      v16[2] = idx;
      v5 = v4->GetRoleIndex(7, v16, 1);
      if ( v5 != -1 )
      {
        this->CheckRoleStatus((int)roleIdx);
        CCBStage::GetRoleName(
          *(_DWORD **)&this->m_sCombatDialog[524],
          v5,
          (int)CCBStage::SelectRole,
          0,
          0,
          0,
          roleIdx,
          0,
          1065353216);
        CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v5);
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
char CCBRoleState::GetFirstAliveRoleInForce(int roleIdx, int a3)
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
  int v15; // [esp+10h] [ebp-44h] BYREF
  int v16; // [esp+14h] [ebp-40h]
  int v17; // [esp+18h] [ebp-3Ch]
  int v18; // [esp+1Ch] [ebp-38h] BYREF
  int v19; // [esp+20h] [ebp-34h]
  int v20; // [esp+24h] [ebp-30h]
  _DWORD v21[11]; // [esp+28h] [ebp-2Ch] BYREF

  v15 = 0;
  v16 = 0;
  v17 = 0;
  memset(v21, 0, sizeof(v21));
  v4 = -1;
  v21[3] = a3;
  v18 = 0xFFFF;
  v19 = 0;
  v20 = 0;
  v5 = *(_DWORD *)&this->m_sCombatDialog[892 * a3 + 1096];
  LOBYTE(v21[10]) = 1;
  v6 = &this->m_sCombatDialog[892 * a3];
  v21[0] = 260;
  v21[1] = 0;
  if ( v5 > 0 )
  {
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    v7 = *((_DWORD *)v6 + 274);
    v8 = ((g_RandSeed >> 16) & 0x7FFF) % v7 + 1;
    *((_DWORD *)v6 + 274) = v7 - v8;
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 28, v21, 1);
    v4 = RoleIndex;
    if ( RoleIndex != -1 )
    {
      v15 = 1;
      v17 = v8;
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)sub_5027E0,
        0,
        0,
        0,
        &v15,
        -1082130432,
        0x40000000);
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
      v4 = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 28, v21, 1);
      if ( v4 == -1 )
        return 0;
    }
    Instance = CScreenMode::GetInstance();
    (CScreenMode *->AudioSetPosition()Instance, aWa006, 1);
    v16 = *((_DWORD *)v6 + 275);
    v15 = 0;
    v17 = v11;
    CCBStage::GetRoleName(
      *(_DWORD **)&this->m_sCombatDialog[524],
      v4,
      (int)sub_5027E0,
      0,
      0,
      0,
      &v15,
      -1082130432,
      0x40000000);
    SkillNum = g_GDB->GDB_GetSkillNum(*((_DWORD *)v6 + 275));
    v18 = *((_DWORD *)v6 + 275);
    v20 = SkillNum;
    v19 = v11;
    CCBStageRole_GetAlive((int)&g_SceneMgr.m_info[7072], &v18);
  }
  if ( v4 != -1 )
  {
    CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v4);
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
  int v8; // [esp+14h] [ebp+4h]

  v8 = *(_DWORD *)(a2 + 8);
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
    if ( ((_DWORD *->sub_4F05A0()a2)
       || (unsigned __int8)CCBStageRole::ForceEndTaskByPFN(*(_DWORD *)(*((_DWORD *)this + 131) + i))
       || *(_WORD *)(g_GDB->GDB_GetSkillNum(*(_DWORD *)(a2 + 4)) + 748) == 2)
      && (int)sub_4F2750(a2, v4) < 0
      && !CCBSystem::IsCmdEmpty(*(_BYTE **)(*((_DWORD *)this + 130) + 12), v4)
      && !CCBSystem::IsCmdReady(*(_DWORD **)(*((_DWORD *)this + 130) + 12), v4) )
    {
      CCBSystem::GetCmdData(*(char **)(*((_DWORD *)this + 130) + 12), v4, 0, 0, 1);
    }
LABEL_13:
    ++v4;
  }
  v6 = *(_DWORD *)(*((_DWORD *)this + 132) + 1120);
  if ( *(_DWORD *)(v6 + 56) == 1 )
    sub_4F95F0(v8, *(_DWORD *)(v6 + 104));
  return 1;
}

// 0x004F1B20
char CCBRoleState::SetCoAttack(int a2)
{
  int v4; // edi
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
    if ( ((_DWORD *->sub_4F05A0()a2)
       || CCBStageRole::ForceEndTaskByPFN(*(float **)(*(_DWORD *)&this->m_sCombatDialog[524] + i)))
      && sub_4F27B0(this, (_DWORD *)a2, v4) < 0
      && !CCBSystem::IsCmdEmpty(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v4)
      && !CCBSystem::IsCmdReady(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v4) )
    {
      CCBSystem::GetCmdData(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), v4);
    }
LABEL_12:
    ++v4;
  }
  this->SetRoleHP(*(_DWORD *)(a2 + 8), *(_DWORD *)(a2 + 4));
  sub_43FE90(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 1068));
  UIWnd::FindChild(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 1068), 50.0);
  UIWnd::FindChildByName(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 1068), 0.0);
  *(_DWORD *)&this->m_sCombatDialog[892 * *(_DWORD *)(a2 + 8) + 1088] = 0;
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
  v6 = &this->m_sCombatDialog[892 * arg0];
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
      result = CCBRoleState::CheckRoleValid((int)this, arg0, a2, 27);
      break;
    case 0x392:
      result = CCBRoleState::CheckRoleValid((int)this, arg0, a2, 28);
      break;
    case 0x393:
      result = CCBRoleState::CheckRoleValid((int)this, arg0, a2, 1);
      break;
    case 0x3A1:
      result = CCBRoleState::CheckRoleValid((int)this, arg0, a2, 30);
      break;
    default:
LABEL_8:
      result = 1;
      break;
  }
  return result;
}

// 0x004F1FA0
char CCBRoleState::CheckRoleValid(int _this, int a2, unsigned int roleIdx, int a4)
{
  char result; // al
  _DWORD *v6; // edx
  _DWORD *v7; // ecx
  int RoleIndex; // edi
  _DWORD *v9; // ecx
  int v10; // edi
  int v11; // edi
  void *TargetRole; // eax
  _DWORD v13[3]; // [esp+10h] [ebp-70h] BYREF
  _DWORD pOut[3]; // [esp+1Ch] [ebp-64h] BYREF
  _DWORD v15[11]; // [esp+28h] [ebp-58h] BYREF
  _DWORD v16[11]; // [esp+54h] [ebp-2Ch] BYREF

  switch ( a4 )
  {
    case 1:
      return (CCBRoleState *->CanRoleAct()this, roleIdx);
    case 2:
      v6 = *(_DWORD **)(this + 520);
      if ( *(_BYTE *)(v6[28] + 80) )
      {
        memset(v16, 0, sizeof(v16));
        v16[2] = a2;
        v7 = *(_DWORD **)(this + 524);
        LOBYTE(v16[10]) = 1;
        v16[0] = 267;
        v16[1] = 0;
        v16[3] = -1;
        RoleIndex = v7->GetRoleIndex(26, v16, 1);
        if ( RoleIndex != -1 )
        {
          memset(v13, 0, sizeof(v13));
          CCBStage::GetRoleName(*(_DWORD **)(this + 524), RoleIndex, (int)sub_5024D0, 0, 0, 0, v13, 0, 1077936128);
          CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)(this + 524), RoleIndex);
        }
        goto LABEL_6;
      }
      *(_BYTE *)(this + 549) = 1;
      memset(v15, 0, sizeof(v15));
      LOBYTE(v15[10]) = 1;
      LOWORD(v15[4]) = 0;
      v15[1] = v6->ProcProtect();
      v15[3] = roleIdx;
      v15[2] = a2;
      v9 = *(_DWORD **)(this + 520);
      v15[0] = 267;
      v9->CreateObj(CCBSystem::PassCmdToThread, 0, 0, 0, v15);
      return 1;
    case 24:
    case 30:
      return 1;
    case 25:
      sub_4F2390((_DWORD *)this);
      return 1;
    case 27:
      if ( roleIdx > 4 )
        return 1;
      v10 = (CCBRoleState *->GetTotalRounds()this) / 200;
      v11 = v10 - (CCBRoleState *->GetTotalRounds()this) / 100;
      if ( v11 > 0 )
      {
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        v11 = ((g_RandSeed >> 16) & 0x7FFF) % v11;
      }
      if ( v11 + (CCBRoleState *->GetTotalRounds()this) / 200 <= 0 )
        return 1;
      (CCBRoleState *->CheckBuff()this, roleIdx);
      return 1;
    case 28:
      if ( roleIdx > 4 )
        return 1;
      if ( CCBStageRole_CheckValid((int *)&g_SceneMgr.m_info[7072], 14) <= 0 )
        goto LABEL_6;
      ++g_nRandCallCount;
      g_RandSeed = 214013 * g_RandSeed + 2531011;
      TargetRole = (CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], pOut);
      CCBStageRole_PassCmd(&g_SceneMgr.m_info[7072], (int)TargetRole);
      result = 1;
      break;
    case 29:
      if ( (CCBRoleState *->Update()this, 2) == 1 )
        sub_4F8FD0((char *)this, a2, roleIdx);
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

  SkillNum = g_GDB->GDB_GetSkillNum(*(_DWORD *)(a2 + 4));
  return CCBRoleState::CheckRoleValid((int)this, *(_DWORD *)(a2 + 8), a3, *(unsigned __int8 *)(SkillNum + 628));
}

// 0x004F2350
char CCBRoleState::CanBeSelect(int a2, unsigned int a3)
{
  int RoleNum; // eax

  RoleNum = g_GDB->GDB_GetRoleNum(*(_DWORD *)(a2 + 4));
  return CCBRoleState::CheckRoleValid((int)this, *(_DWORD *)(a2 + 8), a3, *(unsigned __int8 *)(RoleNum + 578));
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
  RoleNum = g_GDB->GDB_GetRoleNum(value);
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
        result = byte_5D8F0C->CreateObj(0, 0x40u);
        break;
      case 5:
        LOBYTE(result) = this->CanUseSkill(roleIdx);
        break;
      case 6:
        result = (int)&this->m_sCombatDialog[892 * roleIdx + 708];
        *(_DWORD *)result -= *(_DWORD *)(RoleNum + 704);
        break;
      case 7:
        result = this->GetRoleLevel(roleIdx);
        break;
      case 8:
        result = (int)&this->m_sCombatDialog[892 * roleIdx + 624];
        *(_DWORD *)result -= *(_DWORD *)(RoleNum + 704);
        break;
      case 9:
        result = byte_5D8EF8->CreateObj(0, 0x40u);
        break;
      case 10:
        LOBYTE(result) = this->CheckBuff(roleIdx);
        break;
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
        result = byte_5D8EE0->CreateObj(0, 0x40u);
        break;
      case 16:
        v7 = 6113;
        result = (int)CCBStageRole_GetByIndex(&g_SceneMgr.m_info[7072], &v7);
        if ( result )
        {
          v9 = *(_DWORD *)(result + 8);
          v8 = 1;
          v7 = 6113;
          CCBStageRole_PassCmd(&g_SceneMgr.m_info[7072], (int)&v7);
          result = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 8, 0, 1);
          v6 = result;
          if ( result != -1 )
          {
            this->CheckRoleStatus((int)roleIdxa);
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v6,
              (int)CCBStage::ProcWait,
              0,
              0,
              0,
              roleIdxa,
              0,
              1080033280);
            LOBYTE(result) = CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v6);
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
    return *(_DWORD *)&this->m_sCombatDialog[892 * roleIdx + 592];
  else
    return *(_DWORD *)&this->m_sCombatDialog[892 * roleIdx + 588];
}

// 0x004F3020
int CCBRoleState::CalcAttackPower(int roleIdx)
{
  int v2; // edi
  LPARAM v4; // edx
  char *v5; // esi
  int v6; // eax
  int v7; // ecx
  _DWORD *v8; // ecx
  int RoleIndex; // edi
  int v10; // esi
  _DWORD v12[11]; // [esp+Ch] [ebp-40h] BYREF
  int roleIdxa[3]; // [esp+38h] [ebp-14h] BYREF
  int v14; // [esp+44h] [ebp-8h]
  int v15; // [esp+48h] [ebp-4h]
  int v16; // [esp+58h] [ebp+Ch]
  float v17; // [esp+58h] [ebp+Ch]
  char v18; // [esp+5Ch] [ebp+10h]

  v2 = v16;
  if ( !v16 )
    return 0;
  v4 = roleIdx;
  v5 = &this->m_sCombatDialog[892 * roleIdx];
  if ( !v5[578] )
    return 0;
  v15 = *((_DWORD *)v5 + 149);
  if ( v16 < 0 )
  {
    v17 = (double)v16 * *((float *)v5 + 164) * 0.0099999998;
    v14 = (int)v17;
    v2 -= v14;
    v16 = v2;
  }
  v6 = v2 + *((_DWORD *)v5 + 149);
  *((_DWORD *)v5 + 149) = v6;
  v7 = *((_DWORD *)v5 + 150);
  if ( v6 <= v7 )
    v7 = v6 < 0 ? 0 : v6;
  *((_DWORD *)v5 + 149) = v7;
  if ( v18 )
  {
    memset(v12, 0, sizeof(v12));
    v8 = *(_DWORD **)&this->m_sCombatDialog[524];
    v12[2] = roleIdx;
    v12[3] = roleIdx;
    LOBYTE(v12[10]) = 1;
    v12[0] = 259;
    v12[1] = 0;
    LOWORD(v12[4]) = 0;
    RoleIndex = v8->GetRoleIndex(6, v12, 1);
    if ( RoleIndex != -1 )
    {
      if ( v16 <= 0 )
      {
        if ( v15 + v16 < 0 )
          v16 = -v15;
      }
      else
      {
        v10 = *((_DWORD *)v5 + 150) - v15;
        if ( v16 > v10 )
          v16 = v10;
      }
      this->CheckRoleStatus((int)roleIdxa);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)CCBStage::GetRoleTaskNum,
        0,
        0,
        0,
        roleIdxa,
        -1082130432,
        1075838976);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], RoleIndex);
    }
    v4 = roleIdx;
    v2 = v16;
  }
  if ( *(_BYTE *)(*(_DWORD *)&this->m_sCombatDialog[520] + 133) )
    sub_4E2AE0(v4);
  return v2;
}

// 0x004F31C0
int CCBRoleState::CalcDefensePower(int roleIdx)
{
  int v2; // edi
  char *v4; // esi
  int v5; // eax
  int v6; // ecx
  _DWORD *v7; // ecx
  int RoleIndex; // edi
  int v9; // esi
  _DWORD v11[11]; // [esp+Ch] [ebp-40h] BYREF
  int v12[3]; // [esp+38h] [ebp-14h] BYREF
  int v13; // [esp+44h] [ebp-8h]
  int v14; // [esp+48h] [ebp-4h]
  int v15; // [esp+58h] [ebp+Ch]
  float v16; // [esp+58h] [ebp+Ch]
  char v17; // [esp+5Ch] [ebp+10h]

  v2 = v15;
  if ( !v15 )
    return 0;
  v4 = &this->m_sCombatDialog[892 * roleIdx];
  if ( !v4[578] || this->GetRoleField(roleIdx, 23) && v15 > 0 )
    return 0;
  v14 = *((_DWORD *)v4 + 151);
  if ( v15 < 0 )
  {
    v16 = (double)v15 * *((float *)v4 + 165) * 0.0099999998;
    v13 = (int)v16;
    v2 -= v13;
    v15 = v2;
  }
  v5 = v2 + *((_DWORD *)v4 + 151);
  *((_DWORD *)v4 + 151) = v5;
  v6 = *((_DWORD *)v4 + 152);
  if ( v5 <= v6 )
    v6 = v5 < 0 ? 0 : v5;
  *((_DWORD *)v4 + 151) = v6;
  if ( v17 )
  {
    memset(v11, 0, sizeof(v11));
    v7 = *(_DWORD **)&this->m_sCombatDialog[524];
    v11[2] = roleIdx;
    v11[3] = roleIdx;
    LOBYTE(v11[10]) = 1;
    v11[0] = 259;
    v11[1] = 0;
    LOWORD(v11[4]) = 0;
    RoleIndex = v7->GetRoleIndex(6, v11, 1);
    if ( RoleIndex != -1 )
    {
      if ( v15 <= 0 )
      {
        if ( v14 + v15 < 0 )
          v15 = -v14;
      }
      else
      {
        v9 = *((_DWORD *)v4 + 152) - v14;
        if ( v15 > v9 )
          v15 = v9;
      }
      this->CheckRoleStatus((int)v12);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)CCBStage::GetRoleTaskNum,
        0,
        0,
        0,
        v12,
        -1082130432,
        1075838976);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], RoleIndex);
    }
    v2 = v15;
  }
  if ( *(_BYTE *)(*(_DWORD *)&this->m_sCombatDialog[520] + 133) )
    sub_4E2AE0(roleIdx);
  return v2;
}

// 0x004F3380
int CCBRoleState::GetMaxHP(int roleIdx)
{
  int v4; // [esp+14h] [ebp+8h]
  int v5; // [esp+18h] [ebp+Ch]

  if ( sub_4F2C30(this, roleIdx, 0) < (int)abs32(v5) )
    sub_4F2C30(this, roleIdx, 0);
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
  return *(_DWORD *)&this->m_sCombatDialog[632];
}

// 0x004F3430
char CCBRoleState::CheckBuff(int roleIdx)
{
  int RoleIndex; // edi
  char result; // al
  int roleIdxa[3]; // [esp+10h] [ebp-Ch] BYREF
  int v6; // [esp+24h] [ebp+8h]

  *(_DWORD *)&this->m_sCombatDialog[632] += v6;
  if ( v6 < 0 )
  {
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 8, 0, 1);
    if ( RoleIndex != -1 )
    {
      this->CheckRoleStatus((int)roleIdxa);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)CCBStage::ProcWait,
        0,
        0,
        0,
        roleIdxa,
        0,
        1077936128);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], RoleIndex);
    }
  }
  result = *(_BYTE *)(*(_DWORD *)&this->m_sCombatDialog[520] + 133);
  if ( result )
    return sub_4E2C10();
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

  result = this->m_sCombatDialog[577];
  if ( result )
  {
    result = roleIdx;
    if ( roleIdx != 4 )
    {
      v3 = &this->m_sCombatDialog[892 * roleIdx + 628];
      v4 = v7 < 0;
      *(_DWORD *)v3 += v7;
      if ( v7 > 0 )
      {
        Instance = CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()Instance, aWa010, 1);
        v4 = v7 < 0;
      }
      if ( v4 )
      {
        v6 = CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v6, aWa048, 1);
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

  v2 = &this->m_sCombatDialog[892 * roleIdx];
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

  v2 = &this->m_sCombatDialog[892 * roleIdx];
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

  v2 = &this->m_sCombatDialog[892 * roleIdx];
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

  v2 = &this->m_sCombatDialog[892 * roleIdx];
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
  char *v3; // edx
  int v5; // [esp+10h] [ebp+8h]

  v2 = *(_DWORD *)&this->m_sCombatDialog[892 * roleIdx + 620];
  v3 = &this->m_sCombatDialog[892 * roleIdx + 620];
  *(_DWORD *)v3 = v2 + v5;
  if ( v2 + v5 < 0 )
    *(_DWORD *)v3 = 0;
  CCBSystem::GetCmdSlot(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), roleIdx);
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
    result += (unsigned __int8)this->m_sCombatDialog[892 * roleIdx + 984 + 8 * v4 + i];
  return result;
}

// 0x004F3A30
char CCBRoleState::SetRoleFlag(int roleIdx, char flag)
{
  this->m_sCombatDialog[892 * roleIdx + 1140] = flag;
  return flag;
}

// 0x004F3A50
int CCBRoleState::GetRoleAttr(int roleIdx)
{
  int v3; // ecx
  int v4; // esi

  v3 = this->SetRoleField(roleIdx, 0);
  v4 = *(_DWORD *)&this->m_sCombatDialog[892 * roleIdx + 592];
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
  if ( this->m_sCombatDialog[892 * roleIdx + 577] )
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
  v3 = &this->m_sCombatDialog[892 * roleIdx + 1141];
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
  v3 = &this->m_sCombatDialog[892 * roleIdx];
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
  return this->m_sCombatDialog[892 * roleIdx + 1141 + fieldOff];
}

// 0x004F3DC0
int CCBRoleState::GetRoleSpeed(int roleIdx)
{
  int v3; // esi

  if ( !this->m_sCombatDialog[578] )
    return 0;
  v3 = 1;
  while ( !this->m_sCombatDialog[892 * roleIdx + 1141 + v3] || v3->IsPlayerTeam() )
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
  _DWORD *v5; // ecx
  int RoleIndex; // eax
  int v7; // edi
  int v8; // ecx
  unsigned int v9; // ebp
  unsigned int v10; // edi
  char *Instance; // eax
  int v12; // edi
  int v13; // edx
  char *v14; // edi
  void (***v15)(_DWORD, int); // ecx
  _DWORD *v16; // ecx
  int v17; // edi
  int v18; // edi
  char *v19; // eax
  char *v21; // [esp-8h] [ebp-50h]
  char *v22; // [esp-8h] [ebp-50h]
  int v23[3]; // [esp+10h] [ebp-38h] BYREF
  _DWORD v24[11]; // [esp+1Ch] [ebp-2Ch] BYREF
  int v25; // [esp+50h] [ebp+8h]
  unsigned int v26; // [esp+50h] [ebp+8h]
  char v27; // [esp+54h] [ebp+Ch]
  char v28; // [esp+58h] [ebp+10h]

  LOBYTE(v3) = this->GetRoleField(a2, 23);
  if ( (_BYTE)v3 && v25 != 23 )
    return (char)v3;
  if ( v25 < 1 || v25 > 5 )
    goto LABEL_7;
  if ( v27 )
  {
    LOBYTE(v3) = this->m_sCombatDialog->IsRoleInForce(a2);
    if ( (_BYTE)v3 )
      return (char)v3;
LABEL_7:
    if ( v27 )
    {
      if ( v25 >= 1 && v25 <= 5 )
      {
        v3 = &this->m_sCombatDialog[892 * a2];
        *(_DWORD *)(v3 + 1142) = 0;
        v3[1146] = 0;
        if ( v3[1167] )
          return (char)v3;
      }
      if ( v25 >= 14 && v25 <= 23 )
      {
        for ( i = 14; i <= 23; ++i )
          this->ProcessRound(a2);
      }
      if ( !v25->IsPlayerTeam()
        && v25 != 24
        && v25 != 25
        && *(int *)&this->m_sCombatDialog[892 * a2 + 588] > 0 )
      {
        memset(v24, 0, sizeof(v24));
        v5 = *(_DWORD **)&this->m_sCombatDialog[524];
        LOBYTE(v24[10]) = 1;
        v24[2] = a2;
        v24[0] = 0;
        v24[1] = 0;
        v24[3] = a2;
        LOWORD(v24[4]) = 0;
        RoleIndex = v5->GetRoleIndex(10, v24, 1);
        v7 = RoleIndex;
        if ( RoleIndex != -1 )
        {
          CCBStage::GetRoleName(
            *(_DWORD **)&this->m_sCombatDialog[524],
            RoleIndex,
            (int)CCBStage::HandleKeyFriend,
            0,
            0,
            0,
            v23,
            -1082130432,
            0);
          CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v7);
        }
      }
    }
  }
  v8 = v25;
  v9 = 892 * a2;
  v3 = &this->m_sCombatDialog[892 * a2 + 1141 + v25];
  *v3 = v27;
  v10 = v25 + 446 * a2;
  v26 = v10;
  *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1168] = 0;
  *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 0;
  if ( v27 )
  {
    switch ( v8 )
    {
      case 1:
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1168] = 3;
        goto LABEL_24;
      case 2:
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1168] = 3;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 2;
        goto LABEL_25;
      case 3:
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1168] = 0;
LABEL_24:
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        goto LABEL_25;
      case 4:
      case 5:
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1168] = 0;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 0x7FFF;
LABEL_25:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd005;
        break;
      case 6:
        this->m_sCombatDialog[v9 + 1147] = 0;
        this->m_sCombatDialog[v9 + 1148] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        goto LABEL_38;
      case 7:
        this->m_sCombatDialog[v9 + 1147] = 0;
        this->m_sCombatDialog[v9 + 1148] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        goto LABEL_41;
      case 8:
        this->m_sCombatDialog[v9 + 1149] = 0;
        this->m_sCombatDialog[v9 + 1150] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        goto LABEL_38;
      case 9:
        this->m_sCombatDialog[v9 + 1149] = 0;
        this->m_sCombatDialog[v9 + 1150] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        goto LABEL_41;
      case 10:
        this->m_sCombatDialog[v9 + 1151] = 0;
        this->m_sCombatDialog[v9 + 1152] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        goto LABEL_38;
      case 11:
        this->m_sCombatDialog[v9 + 1151] = 0;
        this->m_sCombatDialog[v9 + 1152] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        goto LABEL_41;
      case 12:
        this->m_sCombatDialog[v9 + 1153] = 0;
        this->m_sCombatDialog[v9 + 1154] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        CCBSystem::GetCmdSlot(*(char **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), a2);
LABEL_38:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd021;
        break;
      case 13:
        this->m_sCombatDialog[v9 + 1153] = 0;
        this->m_sCombatDialog[v9 + 1154] = 0;
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        CCBSystem::GetCmdSlot(*(char **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), a2);
LABEL_41:
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd022;
        break;
      case 14:
        sub_4F4820((int)this, a2);
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 4;
        if ( !v28 )
          return (char)v3;
        v21 = aWd007;
        break;
      case 15:
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = aWd008;
        break;
      case 16:
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = aWd009;
        break;
      case 17:
        sub_4F4820((int)this, a2);
        ++g_nRandCallCount;
        g_RandSeed = 214013 * g_RandSeed + 2531011;
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = ((g_RandSeed >> 16) & 0x7FFF) % 7 + 2;
        if ( !v28 )
          return (char)v3;
        v21 = aWd010;
        break;
      case 18:
        sub_4F4820((int)this, a2);
        CCBStageRole::DangerForceRelease(*(_BYTE **)(*(_DWORD *)&this->m_sCombatDialog[524] + 4 * a2 + 24), 0);
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = aWd012;
        break;
      case 19:
        sub_4F4820((int)this, a2);
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 0x7FFF;
        if ( !v28 )
          return (char)v3;
        v21 = aWd011;
        break;
      case 20:
        if ( a2 > 4 )
          *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        else
          *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 3;
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd016;
        break;
      case 21:
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 4;
        if ( !v28 )
          return (char)v3;
        v21 = aWd013;
        break;
      case 22:
        LOBYTE(v3) = v28;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 4;
        if ( !v28 )
          return (char)v3;
        v21 = aWd014;
        break;
      case 23:
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 5;
        if ( this->IsRoleAlive(a2) )
        {
          v12 = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 22, 0, 1);
          if ( v12 != -1 )
          {
            this->CheckRoleStatus((int)v23);
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v12,
              (int)sub_501330,
              0,
              0,
              0,
              v23,
              0,
              1065353216);
            CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v12);
          }
        }
        LOBYTE(v3) = v28;
        if ( !v28 )
          return (char)v3;
        v21 = aWd015;
        break;
      case 24:
        v3 = &this->m_sCombatDialog[v9 + 588];
        v13 = *(_DWORD *)&this->m_sCombatDialog[v9 + 592] / 10;
        if ( *(_DWORD *)v3 > v13 )
          *(_DWORD *)v3 = v13;
        return (char)v3;
      case 25:
        v3 = *(char **)&this->m_sCombatDialog[v9 + 588];
        if ( (int)v3 > 0 )
          *(_DWORD *)&this->m_sCombatDialog[v9 + 588] = 0;
        return (char)v3;
      case 26:
        *v3 = 1;
        *(_WORD *)&this->m_sCombatDialog[2 * v10 + 1222] = 0x7FFF;
        return (char)v3;
      default:
        return (char)v3;
    }
    Instance = CScreenMode::GetInstance();
    (CScreenMode *->AudioSetPosition()Instance, v21, 1);
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
        CCBSystem::GetCmdSlot(*(char **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), a2);
        goto LABEL_91;
      case 14:
        CCBStageRole::DangerForceRelease(*(_BYTE **)(*(_DWORD *)&this->m_sCombatDialog[524] + 4 * a2 + 24), 0);
        goto LABEL_91;
      case 20:
      case 21:
      case 22:
        goto LABEL_86;
      case 23:
        if ( this->IsRoleAlive(a2) )
        {
          v18 = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 22, 0, 1);
          if ( v18 != -1 )
          {
            this->CheckRoleStatus((int)v23);
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v18,
              (int)sub_501410,
              0,
              0,
              0,
              v23,
              0,
              1065353216);
            CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v18);
          }
        }
LABEL_86:
        if ( !v28 )
          goto LABEL_91;
        v22 = aWd020;
        break;
      case 25:
        if ( this->m_sCombatDialog[v9 + 578] )
          goto LABEL_91;
        this->m_sCombatDialog[v9 + 578] = 1;
        *(_DWORD *)&this->m_sCombatDialog[v9 + 588] = 0;
        memset(&this->m_sCombatDialog[v9 + 1141], 0, 0x18u);
        v14 = &this->m_sCombatDialog[v9 + 1165];
        *(_WORD *)v14 = 0;
        v14[2] = 0;
        memset(&this->m_sCombatDialog[v9 + 1168], 0, 0x34u);
        *(_WORD *)&this->m_sCombatDialog[v9 + 1220] = 0;
        memset(&this->m_sCombatDialog[v9 + 1222], 0, 0x34u);
        *(_WORD *)&this->m_sCombatDialog[v9 + 1274] = 0;
        this->m_sCombatDialog[v9 + 1140] = 0;
        CCBStageRole::DangerForceRelease(*(_BYTE **)(*(_DWORD *)&this->m_sCombatDialog[524] + 4 * a2 + 24), 0);
        CCBStageRole::Release(*(_BYTE **)(*(_DWORD *)&this->m_sCombatDialog[524] + 4 * a2 + 24), 1);
        v15 = *(void (****)(_DWORD, int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * a2 + 76);
        (**v15)(v15, 1);
        CCBSystem::SetCmdParam(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), a2, 0);
        CCBSystem::GetCmdData(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), a2);
        if ( !CCBStageRole::ForceEndTaskByPFN(*(float **)(*(_DWORD *)&this->m_sCombatDialog[524] + 4 * a2 + 24)) )
        {
          memset(v24, 0, sizeof(v24));
          v16 = *(_DWORD **)&this->m_sCombatDialog[524];
          LOBYTE(v24[10]) = 1;
          v24[2] = a2;
          v24[1] = 259;
          v17 = v16->GetRoleIndex(9, v24, 1);
          if ( v17 != -1 )
          {
            v23[2] = v24[3];
            v23[1] = v24[2];
            v23[0] = 0;
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v17,
              (int)CCBStage::ProcFiveLienupFadeIn,
              0,
              0,
              0,
              v23,
              -1082130432,
              0);
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v17,
              (int)CCBStage::ProcShowItemName,
              0,
              0,
              0,
              v23,
              -1082130432,
              0);
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v17,
              (int)CCBStage::ProcFiveLienupFadeOut,
              0,
              0,
              0,
              v23,
              -1082130432,
              0);
            CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v17);
          }
        }
        if ( !v28 )
          goto LABEL_91;
        v22 = aWd004;
        break;
      default:
        goto LABEL_91;
    }
    v19 = CScreenMode::GetInstance();
    (CScreenMode *->AudioSetPosition()v19, v22, 1);
LABEL_91:
    *(_WORD *)&this->m_sCombatDialog[2 * v26 + 1168] = 0;
    *(_WORD *)&this->m_sCombatDialog[2 * v26 + 1222] = 0;
    LOBYTE(v3) = v26;
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
  int v18; // ecx
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
      v7 = PAL_GDB::~PAL_GDB(g_GDB, *(_DWORD *)&this->m_sCombatDialog[892 * v2 + 552]);
      v8 = *(_DWORD *)(v6 + v7);
      if ( v8 )
      {
        RoleNum = g_GDB->GDB_GetRoleNum(*(_DWORD *)(v6 + v7));
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
          v18 = sub_4F4AA0(this, v2, *v17);
          if ( (int)abs32(v18 - v29) < v24 )
          {
            v25 = v16;
            v24 = abs32(abs32(v18) - abs32(v29));
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
    v12 = (int *)&this->m_sCombatDialog[892 * v2 + 744 + v21];
    do
    {
      v13 = *v12;
      if ( *v12 )
      {
        if ( this->m_sCombatDialog[v10 + v11 + v22] )
        {
          v14 = g_GDB->GDB_GetRoleNum(*v12);
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
      v7 = PAL_GDB::~PAL_GDB(g_GDB, *(_DWORD *)&this->m_sCombatDialog[892 * v2 + 552]);
      v8 = *(_DWORD *)(v6 + v7);
      if ( v8 )
      {
        RoleNum = g_GDB->GDB_GetRoleNum(*(_DWORD *)(v6 + v7));
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
          v19 = (int)(abs32(sub_4F4AA0(this, v2, *v17)) - v18);
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
    v12 = (int *)&this->m_sCombatDialog[892 * v2 + 744 + v23];
    do
    {
      v13 = *v12;
      if ( *v12 )
      {
        if ( this->m_sCombatDialog[v10 + v11 + v24] )
        {
          v14 = g_GDB->GDB_GetRoleNum(*v12);
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
  int v10; // ecx
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
  v5 = &this->m_sCombatDialog[892 * roleIdx];
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
        RoleNum = g_GDB->GDB_GetRoleNum(*v13);
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
    v5 = &this->m_sCombatDialog[892 * roleIdx];
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
      v10 = sub_4F4AA0(this, roleIdx, *v9);
      if ( (int)abs32(v10 - v18) < v2 )
      {
        v15 = v8;
        v2 = abs32(abs32(v10) - abs32(v18));
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
  int v13; // ecx
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
  v6 = &this->m_sCombatDialog[892 * roleIdx];
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
        RoleNum = g_GDB->GDB_GetRoleNum(*v15);
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
    v6 = &this->m_sCombatDialog[892 * roleIdx];
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
      v13 = sub_4F4AA0(this, roleIdx, *v12);
      if ( (int)abs32(v13 - v22) < v3 )
      {
        v18 = v11;
        v3 = abs32(abs32(v13) - abs32(v22));
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
  v14 = sub_40CCD0((int *)&g_SceneMgr.m_info[7072]);
  if ( v14 <= 0 )
    return 0;
  while ( 1 )
  {
    if ( *((int *)(CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], pOut) + 1) > 0 )
    {
      v6 = *(_DWORD *)(CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], v19);
      v15[1] = v6;
      if ( v2->GetRoleAI(v15) )
      {
        v7 = *(_BYTE *)(*((_DWORD *)(CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], v16) + 2) + 629);
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
    return *(_DWORD *)(CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], v16);
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
  v10 = sub_40CCD0((int *)&g_SceneMgr.m_info[7072]);
  if ( v10 <= 0 )
    return 0;
  for ( i = 0; i < v10; ++i )
  {
    if ( *((int *)(CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], pOut) + 1) > 0 )
    {
      v6 = *(_DWORD *)(CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], v12);
      v14[1] = v6;
      if ( this->GetRoleAI(v14) )
      {
        v7 = *(_BYTE *)(*((_DWORD *)(CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], v13) + 2) + 629);
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
    return *(_DWORD *)(CCBAI *->GetTargetRole()&g_SceneMgr.m_info[7072], v13);
}

// 0x004F7500
char CCBRoleState::GetRoleAI(void *pOut)
{
  int v3; // eax
  char v4; // dl
  char *v5; // ecx
  char result; // al

  v3 = *((_DWORD *)pOut + 2);
  v4 = this->m_sCombatDialog[892 * v3 + 578];
  v5 = &this->m_sCombatDialog[892 * v3];
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
        result = sub_4F7200((int)this, (int)pOut);
        if ( !result )
          return result;
        g_GDB->GDB_GetRoleNum(*((_DWORD *)pOut + 1));
        break;
      case 0x105:
        result = sub_4F6DA0(this, pOut);
        if ( !result )
          return result;
        result = sub_4F7480(this, pOut);
        if ( !result )
          return result;
        result = sub_4F7200((int)this, (int)pOut);
        if ( !result )
          return result;
        if ( this->GetRoleField(*((_DWORD *)pOut + 2), 15) )
          return 0;
        if ( *((_DWORD *)pOut + 1) == 7710 )
        {
          if ( this->Update(2) != 1 )
            return 0;
          if ( this->m_sCombatDialog[5038] && !this->m_sCombatDialog[5892] )
            return 0;
          if ( this->m_sCombatDialog[6822] && !this->m_sCombatDialog[7676] )
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
            g_GDB->GDB_GetSkillNum(*((_DWORD *)pOut + 1));
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
  char *v1; // ecx
  int v2; // edi
  int v3; // esi
  unsigned int result; // eax

  v1 = &this->m_sCombatDialog[604];
  v2 = 11;
  do
  {
    *((_DWORD *)v1 - 4) &= (*((int *)v1 - 4) < 0) - 1;
    *((_DWORD *)v1 - 2) &= (*((int *)v1 - 2) < 0) - 1;
    *(_DWORD *)v1 &= (*(int *)v1 < 0) - 1;
    if ( *((int *)v1 - 4) <= 0 )
    {
      *(v1 - 26) = 0;
      v1[562] = 1;
      v1[561] = 0;
    }
    v3 = *((_DWORD *)v1 - 4);
    result = (unsigned int)((unsigned __int64)(1717986919LL * *((int *)v1 - 3)) >> 32) >> 31;
    if ( v3 < *((_DWORD *)v1 - 3) / 10 && v3 > 0 )
      v1[561] = 1;
    v1 += 892;
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
  char *v4; // ebx
  int v5; // ebx
  char *v6; // ebp
  _DWORD *v7; // ecx
  int v8; // edi
  int v9; // edi
  int v10; // edi
  void *result; // eax
  int v12; // ecx
  int v13; // [esp+10h] [ebp-34h]
  char *v14; // [esp+14h] [ebp-30h]
  _DWORD v15[11]; // [esp+18h] [ebp-2Ch] BYREF

  memset(v15, 0, sizeof(v15));
  if ( sub_4ED0A0(this->m_sCombatDialog, 0) == 1
    && *(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 120) == 2
    && !CCBStage::ForceDelTask(*(char **)&this->m_sCombatDialog[524], 12) )
  {
    sub_4ED800(this->m_sCombatDialog);
    RoleIndex = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 25, v15, 1);
    if ( RoleIndex != -1 )
    {
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)sub_502300,
        0,
        0,
        0,
        0,
        -1082130432,
        1056964608);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)sub_501F30,
        0,
        0,
        0,
        0,
        -1082130432,
        1084227584);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)sub_502000,
        0,
        0,
        0,
        0,
        -1082130432,
        1065353216);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        RoleIndex,
        (int)sub_5021C0,
        0,
        0,
        0,
        0,
        -1082130432,
        1045220557);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], RoleIndex);
    }
    CCBStageCam::ClearFinishedTask(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[524] + 16), 10);
    v3 = 24;
    v4 = &this->m_sCombatDialog[577];
    *(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 120) = 7;
    do
    {
      if ( *v4 )
      {
        *(_BYTE *)(*(_DWORD *)(v3 + *(_DWORD *)&this->m_sCombatDialog[524]) + 280) = 0;
        *(_BYTE *)(*(_DWORD *)(v3 + *(_DWORD *)&this->m_sCombatDialog[524]) + 274) = 0;
        CCBStageRole::TryRelease(*(_DWORD *)(v3 + *(_DWORD *)&this->m_sCombatDialog[524]));
      }
      v3 += 4;
      v4 += 892;
    }
    while ( v3 < 68 );
  }
  if ( ((unsigned __int8)this->GetForce(0) == 1
     || *(_DWORD *)&this->m_sCombatDialog[544] >= *(_DWORD *)&this->m_sCombatDialog[540] && !this->m_sCombatDialog[548])
    && *(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 120) == 2
    && !CCBStage::ForceDelTask(*(char **)&this->m_sCombatDialog[524], 12) )
  {
    sub_4F8AF0(this);
    sub_4FA930((int)this, 1, -1);
    CCBStageCam::ClearFinishedTask(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[524] + 16), 3);
    v5 = 0;
    v6 = &this->m_sCombatDialog[578];
    v13 = 0;
    v14 = &this->m_sCombatDialog[578];
    do
    {
      if ( *(v6 - 1) )
      {
        if ( *v6 )
        {
          v7 = *(_DWORD **)&this->m_sCombatDialog[524];
          v15[2] = v5;
          v8 = v7->GetRoleIndex(24, v15, 1);
          if ( v8 != -1 )
          {
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v8,
              (int)CCBStage::ProcFiveLienupFadeIn,
              0,
              0,
              0,
              0,
              -1082130432,
              0);
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v8,
              (int)sub_501CF0,
              0,
              0,
              0,
              0,
              -1082130432,
              0);
            CCBStage::GetRoleName(
              *(_DWORD **)&this->m_sCombatDialog[524],
              v8,
              (int)CCBStage::ProcFiveLienupFadeOut,
              0,
              0,
              0,
              0,
              -1082130432,
              0);
            CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v8);
            v6 = v14;
            v5 = v13;
          }
        }
      }
      ++v5;
      v6 += 892;
      v13 = v5;
      v14 = v6;
    }
    while ( v5 < 5 );
    v9 = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 23, v15, 1);
    if ( v9 != -1 )
    {
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        v9,
        (int)sub_502300,
        0,
        0,
        0,
        0,
        -1082130432,
        1056964608);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        v9,
        (int)sub_501E60,
        0,
        0,
        0,
        0,
        -1082130432,
        1077936128);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        v9,
        (int)sub_502430,
        0,
        0,
        0,
        0,
        -1082130432,
        0x40000000);
      sub_4FA930((int)this, 0, v9);
      sub_4FB370(this, v9);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        v9,
        (int)CCBStage::StartSubTask,
        0,
        0,
        0,
        0,
        -1082130432,
        1084227584);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        v9,
        (int)sub_5021C0,
        0,
        0,
        0,
        0,
        -1082130432,
        1045220557);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        v9,
        (int)sub_502000,
        0,
        0,
        0,
        0,
        -1082130432,
        1065353216);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v9);
      *(_DWORD *)&this->m_sCombatDialog[20576] = CCBStage::EndTask(*(_DWORD **)&this->m_sCombatDialog[524], v9);
    }
    sub_4ED870(this);
    sub_4ED680(this);
    C2DSpark::CreateStars(*(_DWORD **)(*(_DWORD *)&this->m_sCombatDialog[520] + 52));
    C2DSpark::CreateTrack(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 52), 1);
    *(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 120) = 5;
    CCBStageScene::Destroy(*(gbGeomNode ***)(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 20) + 20));
  }
  if ( *(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 120) == 4 )
  {
    sub_4FA930((int)this, 1, -1);
    CCBStageCam::ClearFinishedTask(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 20) + 16), 8);
    CCBSystem::GetDeltaTime(*(CCBSystem **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12));
    sub_4DB940(*(_BYTE **)(*(_DWORD *)&this->m_sCombatDialog[520] + 12), 0);
    CCBUI::CreateMagicWindow(*(_DWORD **)(*(_DWORD *)&this->m_sCombatDialog[520] + 4));
    v10 = CCBStage::GetRoleIndex(*(_DWORD **)&this->m_sCombatDialog[524], 23, v15, 1);
    if ( v10 != -1 )
    {
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        v10,
        (int)sub_502430,
        0,
        0,
        0,
        0,
        -1082130432,
        0x40000000);
      sub_4FA930((int)this, 0, v10);
      sub_4FB370(this, v10);
      CCBStage::GetRoleName(
        *(_DWORD **)&this->m_sCombatDialog[524],
        v10,
        (int)CCBStage::StartSubTask,
        0,
        0,
        0,
        0,
        -1082130432,
        1097859072);
      CCBSystem::GetStageRoleByIdx(*(CCBStageRole **)&this->m_sCombatDialog[524], v10);
    }
    sub_4ED680(this);
    *(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 120) = 5;
    CCBStageScene::Destroy(*(gbGeomNode ***)(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 20) + 20));
  }
  result = *(void **)&this->m_sCombatDialog[520];
  v12 = *((_DWORD *)result + 30);
  if ( v12 == 5 )
  {
    LOBYTE(result) = sub_4FCA40(*(char **)&this->m_sCombatDialog[524], *(_DWORD *)&this->m_sCombatDialog[20576]);
    if ( (_BYTE)result )
      return result;
    *(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 124) = 2;
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
  int v5; // eax
  int v6; // ecx
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
  float v45; // [esp+0h] [ebp-30h]
  float v46; // [esp+0h] [ebp-30h]
  float v47; // [esp+0h] [ebp-30h]
  float v48; // [esp+0h] [ebp-30h]
  float v49; // [esp+0h] [ebp-30h]
  float v50; // [esp+0h] [ebp-30h]
  float v51; // [esp+0h] [ebp-30h]
  int v52; // [esp+0h] [ebp-30h]
  int v53; // [esp+0h] [ebp-30h]
  char *v54; // [esp+28h] [ebp-8h]
  int *a1; // [esp+2Ch] [ebp-4h]

  v2 = 0;
  v54 = *(char **)(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[520] + 20) + 68);
  do
  {
    result = (int)&this->m_sCombatDialog[892 * v2];
    a1 = (int *)result;
    if ( *(_BYTE *)(result + 577) )
    {
      v4 = *(unsigned __int8 *)(result + 576);
      v45 = (float)*(int *)(result + 592);
      UIWnd::FindChild(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 1020), v45);
      v46 = (float)a1[150];
      UIWnd::FindChild(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 1036), v46);
      v47 = (float)a1[152];
      UIWnd::FindChild(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 1052), v47);
      v48 = (float)a1[147];
      UIWnd::FindChildByName(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 1020), v48);
      v49 = (float)a1[149];
      UIWnd::FindChildByName(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 1036), v49);
      v50 = (float)a1[151];
      UIWnd::FindChildByName(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 1052), v50);
      if ( !v2 )
      {
        v5 = *(_DWORD *)&this->m_sCombatDialog[528];
        if ( *(_DWORD *)(*(_DWORD *)(v5 + 120) + 56) == 1 )
        {
          v51 = *(float *)&this->m_sCombatDialog[1088] * 0.25;
          UIWnd::FindChildByName(*(_DWORD *)(v5 + 1068), v51);
          if ( *(int *)&this->m_sCombatDialog[588] > 0 )
          {
            v6 = *(_DWORD *)&this->m_sCombatDialog[520];
            if ( *(float *)(v6 + 80) - *(float *)&this->m_sCombatDialog[20640] > 0.1 )
            {
              *(float *)&v52 = *(float *)&this->m_sCombatDialog[1088] * 0.1;
              C2DSpark::CreateMore(*(_DWORD **)(v6 + 52), 25, 570, 20, v52);
              if ( *(float *)&this->m_sCombatDialog[1088] > 199.89999 )
              {
                *(float *)&v53 = *(float *)&this->m_sCombatDialog[1088] * 0.1;
                C2DSpark::CreateMore(*(_DWORD **)(*(_DWORD *)&this->m_sCombatDialog[520] + 52), 25, 570, 20, v53);
              }
              *(float *)&this->m_sCombatDialog[20640] = *(float *)(*(_DWORD *)&this->m_sCombatDialog[520] + 80);
            }
          }
        }
      }
      result = *(_DWORD *)&this->m_sCombatDialog[528];
      if ( *(_DWORD *)(*(_DWORD *)(result + 4 * v4 + 120) + 56) == 1 )
      {
        v54->SetText(dword_17AA808[v4] + 22, dword_17AA818[v4] + 5, (int)*(float *)(*(_DWORD *)(result + 4 * v4 + 1020) + 156),
          -6243078);
        v54->SetText(dword_17AA828[v4] + 31, dword_17AA838[v4] + 5, (int)*(float *)(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 1036) + 156),
          -270174);
        v54->SetText(dword_17AA848[v4] + 23, dword_17AA858[v4] + 5, (int)*(float *)(*(_DWORD *)(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 1052) + 156),
          -349995);
        if ( this->GetRoleField(v2, 3) )
        {
          NPC::UpdateAnim(-13002067);
        }
        else if ( this->GetRoleField(v2, 4) )
        {
          NPC::UpdateAnim(-2198223);
        }
        else if ( this->GetRoleField(v2, 2) )
        {
          NPC::UpdateAnim(-6002966);
        }
        else if ( this->GetRoleField(v2, 1) )
        {
          NPC::UpdateAnim(-11356565);
        }
        else if ( this->GetRoleField(v2, 5) )
        {
          NPC::UpdateAnim(-2707878);
        }
        else
        {
          NPC::UpdateAnim(-1);
        }
        if ( a1[147] <= 0 )
          NPC::UpdateAnim(-11513776);
        RoleField = this->GetRoleField(v2, 6);
        v8 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 176);
        if ( RoleField )
          (*v8)(1);
        else
          (*v8)(0);
        v9 = this->GetRoleField(v2, 7);
        v10 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 220);
        if ( v9 )
          (*v10)(1);
        else
          (*v10)(0);
        v11 = this->GetRoleField(v2, 8);
        v12 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 264);
        if ( v11 )
          (*v12)(1);
        else
          (*v12)(0);
        v13 = this->GetRoleField(v2, 9);
        v14 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 308);
        if ( v13 )
          (*v14)(1);
        else
          (*v14)(0);
        v15 = this->GetRoleField(v2, 12);
        v16 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 440);
        if ( v15 )
          (*v16)(1);
        else
          (*v16)(0);
        v17 = this->GetRoleField(v2, 13);
        v18 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 484);
        if ( v17 )
          (*v18)(1);
        else
          (*v18)(0);
        v19 = this->GetRoleField(v2, 10);
        v20 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 352);
        if ( v19 )
          (*v20)(1);
        else
          (*v20)(0);
        v21 = this->GetRoleField(v2, 11);
        v22 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 396);
        if ( v21 )
          (*v22)(1);
        else
          (*v22)(0);
        v23 = this->GetRoleField(v2, 14);
        v24 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 528);
        if ( v23 )
          (*v24)(1);
        else
          (*v24)(0);
        v25 = this->GetRoleField(v2, 15);
        v26 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 572);
        if ( v25 )
          (*v26)(1);
        else
          (*v26)(0);
        v27 = this->GetRoleField(v2, 16);
        v28 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 616);
        if ( v27 )
          (*v28)(1);
        else
          (*v28)(0);
        v29 = this->GetRoleField(v2, 17);
        v30 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 660);
        if ( v29 )
          (*v30)(1);
        else
          (*v30)(0);
        v31 = this->GetRoleField(v2, 18);
        v32 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 704);
        if ( v31 )
          (*v32)(1);
        else
          (*v32)(0);
        v33 = this->GetRoleField(v2, 19);
        v34 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 748);
        if ( v33 )
          (*v34)(1);
        else
          (*v34)(0);
        v35 = this->GetRoleField(v2, 20);
        v36 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 792);
        if ( v35 )
          (*v36)(1);
        else
          (*v36)(0);
        v37 = this->GetRoleField(v2, 21);
        v38 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 836);
        if ( v37 )
          (*v38)(1);
        else
          (*v38)(0);
        v39 = this->GetRoleField(v2, 22);
        v40 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 880);
        if ( v39 )
          (*v40)(1);
        else
          (*v40)(0);
        v41 = this->GetRoleField(v2, 23);
        v42 = **(void (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 924);
        if ( v41 )
          (*v42)(1);
        else
          (*v42)(0);
        v43 = this->GetRoleField(v2, 26);
        v44 = **(int (__stdcall ****)(int))(*(_DWORD *)&this->m_sCombatDialog[528] + 4 * v4 + 968);
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
  char *v20; // edx
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
  int v46; // [esp+30h] [ebp+18h]

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
      *(float *)&dmg = (double)v45 * *(float *)&this->m_sCombatDialog[892 * v7 + 668] * 0.0099999998;
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
      g_GDB->GDB_GetRoleNum(v46);
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
      sub_4FA620(this->m_sCombatDialog, v12, v46, &dmg, &roleIdxa);
      v46->IsAllEnemyDead(&v39, &v40);
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
      v42 = *(_DWORD *)&this->m_sCombatDialog[892 * v17 + 584];
      this->GetRoleMP(RoleHP);
      if ( v45 < dmg )
      {
        v19 = dmg - v45;
        v20 = &this->m_sCombatDialog[892 * v45 + 584];
        do
        {
          if ( *(v20 - 7) )
          {
            ++roleIdxa;
            v3 += *(_DWORD *)v20;
          }
          v20 += 892;
          --v19;
        }
        while ( v19 );
      }
      v38 = v3 / roleIdxa;
      v21 = this->GetRoleState(v17);
      v22 = v45;
      v23 = v21;
      v46 = (int)&unk_FFFFFF;
      if ( v45 < dmg )
      {
        roleIdxa = (int)&this->m_sCombatDialog[892 * v45 + 577];
        do
        {
          if ( *(_BYTE *)roleIdxa )
          {
            v24 = this->GetRoleState(v22);
            if ( v24 < v46 )
              v46 = this->GetRoleState(v22);
          }
          ++v22;
          roleIdxa += 892;
        }
        while ( v22 < dmg );
      }
      LODWORD(v11) = 10 * ((v42 - v38) * (v23 - v46) + 3);
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
      v46 = (int)*(float *)&v45;
      v30 = -v46;
      v45 = -v46;
      if ( byte_5DFDEB )
      {
        *(float *)&v45 = (double)v45 * 0.1;
        v46 = (int)*(float *)&v45;
        *(float *)&v45 = COERCE_FLOAT(abs32(v46));
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
        v45 = -v46;
      }
      if ( *((_BYTE *)v43 + 650) || *((_BYTE *)v43 + 649) )
      {
        if ( byte_5DFDEB )
        {
          v46 = (int)5.0;
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
