#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/NPC.h"

// Forward declarations for unnamed functions
int sub_41A150(...);
int sub_479100(...);

// Unnamed globals (extern)
extern int dword_C020F8;
extern int dword_C02370;
extern int dword_C025E8;
extern int dword_C025EC;

// 0x0040EB90
unsigned int NPC::Create(int index)
{
  int v2; // ebp
  char *v3; // edx
  unsigned int result; // eax
  signed int v5; // ebx
  int v6; // edi
  int RoleNum; // eax
  int v8; // ecx
  int indexa; // [esp+14h] [ebp+4h]

  v2 = 0;
  v3 = &g_SceneMgr.m_info[1408 * index + 1072];
  memset(&g_SceneMgr.m_info[1408 * index + 1048], 0, 0x18u);
  *(_DWORD *)v3 = 0;
  *((_WORD *)v3 + 2) = 0;
  result = Concurrency::details::(Concurrency::details::VirtualProcessor *->GetExecutionResourceId()g_GDB);
  v5 = 0;
  for ( indexa = result; v5 < indexa; ++v5 )
  {
    v6 = sub_479100(g_GDB, v5);
    RoleNum = g_GDB->GDB_GetRoleNum(v6);
    if ( *(_BYTE *)(index + RoleNum + 572) )
    {
      if ( !*(_BYTE *)(RoleNum + 4) )
      {
        v8 = v2 + 352 * index;
        ++v2;
        *(_DWORD *)&g_SceneMgr.m_info[4 * v8 + 1048] = v6;
      }
    }
    result = indexa;
  }
  return result;
}

// 0x0040EC20
void * NPC::Init(int index)
{
  signed int v2; // ebx
  int v3; // ebp
  int RoleNum; // eax
  char v5; // cl
  int v6; // edi
  _DWORD *v7; // ecx
  int v8; // edx
  int v9; // ecx
  int i; // ecx
  char v11; // bl
  int v12; // edi
  char *v13; // esi
  void *result; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // [esp+10h] [ebp-1Ch]
  _DWORD v18[6]; // [esp+14h] [ebp-18h] BYREF
  int indexa; // [esp+30h] [ebp+4h]

  v2 = 0;
  memset(v18, 0, sizeof(v18));
  v17 = 1408 * index;
  memset(&g_SceneMgr.m_info[1408 * index + 1080], 0, 0xC0u);
  memset(&g_SceneMgr.m_info[1408 * index + 1272], 0, 0x30u);
  memset(&g_SceneMgr.m_info[1408 * index + 1320], 0, 0x30u);
  memset(&g_SceneMgr.m_info[1408 * index + 1368], 0, 0x30u);
  indexa = Concurrency::details::(Concurrency::details::VirtualProcessor *->GetExecutionResourceId()g_GDB);
  if ( indexa > 0 )
  {
    do
    {
      v3 = sub_479100(g_GDB, v2);
      RoleNum = g_GDB->GDB_GetRoleNum(v3);
      if ( *(_BYTE *)(index + RoleNum + 572) )
      {
        v5 = *(_BYTE *)(RoleNum + 4);
        if ( v5 == 1 || v5 == 2 || v5 == 3 )
        {
          v6 = 0;
          v7 = (_DWORD *)(RoleNum + 8);
          v8 = 5;
          do
          {
            if ( *v7 == 1 )
              ++v6;
            ++v7;
            --v8;
          }
          while ( v8 );
          if ( v6 <= 1 )
          {
            for ( i = 0; i < 5; ++i )
            {
              if ( *(_DWORD *)(RoleNum + 4 * i + 8) == 1 )
              {
                if ( i == 2 )
                {
                  *(_DWORD *)&g_SceneMgr.m_info[1408 * index + 1176 + 4 * v18[2]] = v3;
                }
                else if ( i == 3 )
                {
                  *(_DWORD *)&g_SceneMgr.m_info[1408 * index + 1144 + 4 * v18[3]] = v3;
                }
                else
                {
                  *(_DWORD *)&g_SceneMgr.m_info[1408 * index + 1080 + 32 * i + 4 * v18[i]] = v3;
                }
                ++v18[i];
              }
            }
          }
          else
          {
            v9 = v18[5] + 352 * index;
            ++v18[5];
            *(_DWORD *)&g_SceneMgr.m_info[4 * v9 + 1240] = v3;
          }
        }
      }
      ++v2;
    }
    while ( v2 < indexa );
  }
  do
  {
    v11 = 1;
    v12 = 6;
    v13 = &g_SceneMgr.m_info[v17 + 1084];
    do
    {
      result = v13;
      v15 = 7;
      do
      {
        if ( *(_DWORD *)result )
        {
          if ( *((_DWORD *)result - 1) > *(_DWORD *)result )
          {
            v16 = *((_DWORD *)result - 1);
            *((_DWORD *)result - 1) = *(_DWORD *)result;
            v11 = 0;
            *(_DWORD *)result = v16;
          }
        }
        result = (char *)result + 4;
        --v15;
      }
      while ( v15 );
      v13 += 32;
      --v12;
    }
    while ( v12 );
  }
  while ( !v11 );
  return result;
}

// 0x0040F060
int NPC::SetParams(int a1)
{
  int result; // eax

  *(_DWORD *)&g_SceneMgr.m_info[51516] = a1;
  result = a1;
  if ( a1 )
  {
    if ( a1 == 1 )
    {
      dword_C02370 = 1;
      dword_C025EC = 10;
      return sub_41A150((const char *)dword_C020F8, "109");
    }
    else
    {
      result = a1 - 2;
      if ( a1 == 2 )
      {
        dword_C025EC = 0;
        dword_C02370 = 1;
        dword_C025E8 = 1;
        return 1;
      }
    }
  }
  else
  {
    dword_C02370 = 0;
    dword_C025EC = 0;
  }
  return result;
}

// 0x0040F620
int * NPC::InitAll()
{
  int *result; // eax
  char *v1; // ebx
  int *v2; // edi
  int v3; // ebp
  int v4; // eax
  char *v5; // ecx
  int v6; // edx
  char *v7; // esi
  int v8; // eax
  char *v9; // ecx
  int v10; // eax
  int v11; // [esp+10h] [ebp-Ch]
  int *v12; // [esp+14h] [ebp-8h]
  int v13; // [esp+18h] [ebp-4h]

  result = g_RoleTeam2;
  v11 = 0;
  v1 = &g_SceneMgr.m_info[1072];
  v12 = g_RoleTeam2;
  do
  {
    v2 = (int *)*(result - 1);
    v13 = *result;
    if ( v2 != (int *)*result )
    {
      do
      {
        v3 = *v2;
        v4 = 0;
        v5 = v1 - 24;
        do
        {
          if ( v3 == *(_DWORD *)v5 )
          {
            v1[v4] = 1;
            goto LABEL_14;
          }
          ++v4;
          v5 += 4;
        }
        while ( v4 < 6 );
        v6 = 0;
        v7 = v1 + 8;
        while ( 2 )
        {
          v8 = 0;
          v9 = v7;
          do
          {
            if ( v3 == *(_DWORD *)v9 )
            {
              v10 = v8 + 8 * (v6 + v11);
              g_SceneMgr.m_info[v10 + 1272] = 1;
              g_SceneMgr.m_info[v10 + 1368] = *((_BYTE *)v2 + 4);
              g_SceneMgr.m_info[v10 + 1320] = *((_BYTE *)v2 + 6);
              goto LABEL_14;
            }
            ++v8;
            v9 += 4;
          }
          while ( v8 < 8 );
          ++v6;
          v7 += 32;
          if ( v6 < 6 )
            continue;
          break;
        }
LABEL_14:
        v2 += 3;
      }
      while ( v2 != (int *)v13 );
      result = v12;
    }
    result += 4;
    v1 += 1408;
    v12 = result;
    v11 += 176;
  }
  while ( (int)result < (int)&g_SceneMgr.m_info[24] );
  return result;
}

// 0x00446020
int NPC::UpdateAnim(int a1)
{
  int v1; // ecx

  *(_DWORD *)(v1 + 8) = a1;
  return a1;
}
