#include "pal3/gen/CCBStageEffect.h"

// 0x00508E30
char sub_508E30(int this)
{
  struct gbVFile *v2; // eax
  struct gbVFile *v3; // esi
  struct gbVFileSystem *v5; // [esp+24h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+28h] [ebp-80Ch] BYREF
  char ArgList; // [esp+428h] [ebp-40Ch] BYREF
  int v8; // [esp+830h] [ebp-4h]

  OpenBaseFile::OpenBaseFile(&v5);
  v8 = 0;
  v2 = g_pVFileSys->OpenFile(aCbdataEfflinke, 0x201u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCouldnTOpenEff_0, (int)aDProjectPal3Co_7, 366),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Read((void *)(this + 2444), 0x5A00u, v3);
  g_pVFileSys->CloseFile(v3);
  dword_17AB584 = 1;
  v8 = -1;
  OpenNULLFile::OpenNULLFile(&v5);
  return 1;
}

// 0x00508F30
char sub_508F30(int this)
{
  struct gbVFile *v2; // eax
  struct gbVFile *v3; // esi
  struct gbVFileSystem *v5; // [esp+24h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+28h] [ebp-80Ch] BYREF
  char ArgList; // [esp+428h] [ebp-40Ch] BYREF
  int v8; // [esp+830h] [ebp-4h]

  OpenBaseFile::OpenBaseFile(&v5);
  v8 = 0;
  v2 = g_pVFileSys->OpenFile(aCbdataEfflinke, 0x202u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCouldnTOpenCbE_0, (int)aDProjectPal3Co_7, 390),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Write((void *)(this + 2444), 0x5A00u, v3);
  g_pVFileSys->CloseFile(v3);
  v8 = -1;
  OpenNULLFile::OpenNULLFile(&v5);
  return 1;
}

// 0x00509050
// attributes: thunk
int CCBStageEffect::Create()
{
  return CCBStageEffect::Destroy();
}

// 0x00509060
int sub_509060()
{
  dword_17ABC64 = 1094713344;
  return 1094713344;
}

// 0x00509070
// attributes: thunk
void CCBStageEffect::Init()
{
  CCBStageEffect::GetLinkerIndex();
}

// 0x00509080
void sub_509080()
{
  flt_17ABC60 = 12.0 + 12.0;
}

// 0x00509090
// attributes: thunk
int CCBStageEffect::PreLoadEffGroup()
{
  return sub_5090A0();
}

// 0x005090E0
// attributes: thunk
int CCBStageEffect::LoadLinker()
{
  return CCBStageRole::Proceed();
}
