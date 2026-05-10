#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffMgr.h"

// Forward declarations for unnamed functions
int sub_4C04C0(...);
int sub_4C1570(...);
int sub_4C3C90(...);
int sub_4CDCA0(...);
int sub_4D5950(...);
int sub_4D5A00(...);

// Unnamed globals (extern)
extern char aCbdataFlexeffD[];
extern char aCouldnTOpenCbE[];
extern char aCouldnTOpenEff[];
extern char aDProjectPal3Co_3[];
extern unsigned char byte_174D404;
extern unsigned char byte_17A7C24;
extern unsigned char byte_5D55AC;
extern int dword_174D330;
extern int dword_174D334;
extern int dword_174D354;
extern int dword_17A7B50;
extern int dword_17A7B74;
extern int dword_1895980;
extern int dword_EC9E70;
extern int dword_EC9E74;
extern int nullsub_1;
extern int unk_8834C0;
extern int unk_8DDCE0;
extern int unk_DE9CB0;
extern int unk_EC9EB4;

// 0x004CE100
CEffMgr::CEffMgr()
{
  struct gbVFile *v1; // esi
  void *v2; // ebx
  char *v3; // eax
  char *v4; // ebp
  struct gbVFileSystem *v5; // [esp+30h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+34h] [ebp-80Ch] BYREF
  char ArgList; // [esp+434h] [ebp-40Ch] BYREF
  int v8; // [esp+83Ch] [ebp-4h]

  if ( dword_17A7B50 )
    return 1;
  OpenBaseFile::OpenBaseFile(&v5);
  v8 = 0;
  v1 = (struct gbVFile *)g_pVFileSys->OpenFile(aCbdataFlexeffD, 0x201u);
  if ( !v1 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCouldnTOpenEff, (int)aDProjectPal3Co_3, 447),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v2 = (void *)malloc(0x2C047u);
  v3 = (char *)malloc((size_t)&unk_8DDCE0);
  v4 = v3;
  if ( !v2 || !v3 )
    goto LABEL_9;
  g_pVFileSys->Seek(v1, 0, 1);
  g_pVFileSys->Read(v2, 0x2C047u, v1);
  g_pVFileSys->CloseFile(v1);
  if ( (_UNKNOWN *)(CPK *->DeCompress()&unk_DE9CB0, v4, v2, 0x2C047u) != &unk_8DDCE0 )
  {
    free(v2);
    free(v4);
LABEL_9:
    v8 = -1;
    OpenNULLFile::OpenNULLFile(&v5);
    return 0;
  }
  qmemcpy(dword_174D330, v4, 0x5A820u);
  qmemcpy(&dword_EC9E70, v4 + 370720, 0x8834C0u);
  free(v2);
  free(v4);
  dword_17A7B50 = 1;
  v8 = -1;
  OpenNULLFile::OpenNULLFile(&v5);
  return 1;
}

// 0x004CE2A0
CEffMgr::~CEffMgr()
{
  FILE *v0; // eax
  FILE *v1; // esi
  char pExceptionObject[1024]; // [esp+4h] [ebp-800h] BYREF
  char ArgList; // [esp+404h] [ebp-400h] BYREF

  v0 = (FILE *)fopen(FileName, Mode);
  v1 = v0;
  if ( !v0 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCouldnTOpenCbE, (int)aDProjectPal3Co_3, 521),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  fseek(v0, 0, 0);
  fwrite(dword_174D330, 0x5A820u, 1u, v1);
  fwrite(&dword_EC9E70, (size_t)&unk_8834C0, 1u, v1);
  fclose(v1);
  return 1;
}

// 0x004CE340
int CEffMgr::Init(int a2, int a3, int a4, int a5, int a6)
{
  int v6; // eax
  int v7; // ebx
  char *v8; // esi
  int v9; // edi
  int v10; // ebp
  int v13; // [esp+10h] [ebp-Ch]
  int v15; // [esp+18h] [ebp-4h]
  int *a6a; // [esp+30h] [ebp+14h]

  v13 = a6;
  if ( !a6 )
  {
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      (CEffMgr *->Reset()&g_nCursorState);
      atexit(nullsub_1);
    }
    v6 = dword_1895980;
    if ( dword_1895980 == -1 )
      v6 = 1;
    v13 = v6;
    dword_1895980 = v6 + 1;
  }
  v15 = 0;
  v7 = 3985 * a2;
  if ( dword_EC9E70[3985 * a2] <= 0 )
    return v13;
  v8 = (char *)&unk_EC9EB4 + v7 * 4;
  for ( a6a = &dword_EC9E74[v7]; ; ++a6a )
  {
    v9 = sub_4CDCA0((int *)this, *a6a, v13, a3, a4, a5);
    if ( v9 == -1 )
      break;
    v10 = 8;
    do
    {
      if ( v8[88] )
        (*(void (**)(_DWORD, char *))(**(_DWORD **)&this->m_EffClass[30].szChineseName[20 * v9 + 10] + 48))(
          *(_DWORD *)&this->m_EffClass[30].szChineseName[20 * v9 + 10],
          v8);
      v8 += 124;
      --v10;
    }
    while ( v10 );
    if ( ++v15 >= dword_EC9E70[3985 * a2] )
      return v13;
  }
  return 0;
}

// 0x004CE580
char CEffMgr::Render(int a2)
{
  int v2; // edx
  char *i; // eax

  if ( !a2 )
    return 0;
  v2 = 0;
  for ( i = &this->m_pDisplay[2344]; *((_DWORD *)i - 1) != a2 || !*i || i[1]; i += 20 )
  {
    if ( ++v2 >= 2048 )
      return 0;
  }
  return 1;
}

// 0x004CE5F0
int CEffMgr::SetTimeScale(int a1)
{
  int v1; // esi
  int v2; // ebx
  int *v3; // edx
  int v4; // eax
  int *v5; // ecx
  CHAR Text[256]; // [esp+Ch] [ebp-100h] BYREF

  v1 = dword_174D354[70 * a1];
  if ( v1 )
  {
    v2 = 0;
    v3 = dword_EC9E74;
    while ( 2 )
    {
      v4 = 0;
      v5 = v3;
      do
      {
        if ( *v5 == v1 )
        {
          sprintf(Text, &byte_5D55AC, v2, v4);
          return MessageBoxA(0, Text, Caption, 0);
        }
        ++v4;
        ++v5;
      }
      while ( v4 < 16 );
      v3 += 3985;
      ++v2;
      if ( (int)v3 < (int)dword_174D334 )
        continue;
      break;
    }
  }
  memset(&dword_174D330[70 * a1], 0, 0x118u);
  return 0;
}

// 0x004CE690
char CEffMgr::CreateEff(int a1)
{
  int v1; // ebx
  char *v2; // eax
  int v3; // ecx
  char v4; // al
  int v5; // ebp
  bool v6; // zf
  int *v7; // ecx

  v1 = 70 * a1;
  LOBYTE(v2) = byte_174D404[280 * a1];
  if ( (_BYTE)v2 )
  {
    v3 = 0;
    v2 = byte_174D404;
    while ( *v2 )
    {
      v2 += 280;
      ++v3;
      if ( (int)v2 >= (int)byte_17A7C24 )
        return (char)v2;
    }
    v4 = g_bCursorVisible;
    v5 = 70 * v3;
    v6 = (g_bCursorVisible & 1) == 0;
    qmemcpy(&dword_174D330[70 * v3], &dword_174D330[v1], 0x118u);
    if ( v6 )
    {
      g_bCursorVisible = v4 | 1;
      CEffMgr::Reset(&g_nCursorState);
      atexit(nullsub_1);
    }
    sub_4D5950((char *)&dword_174D334[v5], (int)&dword_174D334[v1]);
    if ( (g_bCursorVisible & 1) == 0 )
    {
LABEL_9:
      g_bCursorVisible |= 1u;
      CEffMgr::Reset(&g_nCursorState);
      atexit(nullsub_1);
    }
LABEL_10:
    v2 = (char *)CEffSParticle::GetEditorTaskDescription(&dword_174D334[v5]);
    v7 = dword_174D354;
    do
    {
      if ( *((_BYTE *)v7 + 176) && (char *)*v7 == v2 )
      {
        if ( (g_bCursorVisible & 1) == 0 )
        {
          g_bCursorVisible |= 1u;
          CEffMgr::Reset(&g_nCursorState);
          atexit(nullsub_1);
        }
        sub_4D5950((char *)&dword_174D334[v5], (int)&dword_174D334[v5]);
        if ( (g_bCursorVisible & 1) != 0 )
          goto LABEL_10;
        goto LABEL_9;
      }
      v7 += 70;
    }
    while ( (int)v7 < (int)&dword_17A7B74 );
    dword_174D354[v5] = (int)v2;
  }
  return (char)v2;
}

// 0x004CEDA0
int CEffMgr::RunEffGroup(const char *a2, int a3, const char *a4)
{
  int v4; // ebp
  char *i; // eax
  char *v7; // ebx
  char *v8; // edi
  _DWORD *v9; // eax
  _DWORD *v10; // eax

  v4 = 0;
  for ( i = &this->m_pDisplay[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->m_pDisplay[72 * v4];
  strcpy(v7 + 28, a2);
  v8 = (char *)a4;
  if ( !a4 )
    v8 = (char *)&g_SceneMgr.m_info[51624];
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (_DWORD *)operator new(0x34u);
  if ( v9 )
    v10 = (_DWORD *)sub_4C04C0(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *((_DWORD *)v7 + 23) = CEffSParticle::GetEditorTaskDescription(&g_nCursorState, (unsigned __int8 *)a2);
  return v4;
}

// 0x004CF100
int CEffMgr::IsAllEffGroupStop(const char *a2, int a3, const char *a4)
{
  int v4; // ebp
  char *i; // eax
  char *v7; // ebx
  char *v8; // edi
  _DWORD *v9; // eax
  _DWORD *v10; // eax

  v4 = 0;
  for ( i = &this->m_pDisplay[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->m_pDisplay[72 * v4];
  strcpy(v7 + 28, a2);
  v8 = (char *)a4;
  if ( !a4 )
    v8 = (char *)&g_SceneMgr.m_info[51624];
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (_DWORD *)operator new(0x10C4u);
  if ( v9 )
    v10 = (_DWORD *)sub_4C3C90(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *((_DWORD *)v7 + 23) = CEffSParticle::GetEditorTaskDescription(&g_nCursorState, (unsigned __int8 *)a2);
  return v4;
}

// 0x004CF7C0
int CEffMgr::CopyObjInGroup(const char *a2, int a3, const char *a4)
{
  int v4; // ebp
  char *i; // eax
  char *v7; // ebx
  char *v8; // edi
  _DWORD *v9; // eax
  _DWORD *v10; // eax

  v4 = 0;
  for ( i = &this->m_pDisplay[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->m_pDisplay[72 * v4];
  strcpy(v7 + 28, a2);
  v8 = (char *)a4;
  if ( !a4 )
    v8 = (char *)&g_SceneMgr.m_info[51624];
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (_DWORD *)operator new(0x130u);
  if ( v9 )
    v10 = (_DWORD *)sub_4C1570(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    CEffMgr::Reset(&g_nCursorState);
    atexit(nullsub_1);
  }
  *((_DWORD *)v7 + 23) = CEffSParticle::GetEditorTaskDescription(&g_nCursorState, (unsigned __int8 *)a2);
  return v4;
}

// 0x004D58A0
_DWORD * CEffMgr::Reset()
{
  sub_4D5A00((int *)this->m_pDisplay);
  *(_DWORD *)&this->m_pDisplay[1024] = 1;
  *(_DWORD *)&this->m_pDisplay[1028] = timeGetTime();
  *(_DWORD *)&this->m_pDisplay[1032] = 0;
  return this->m_pDisplay;
}
