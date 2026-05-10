#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageEffect.h"
#include "pal3/gen/CCBStageRole.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"

// Forward declarations for unnamed functions
int sub_5090A0(...);

// Unnamed globals (extern)
extern char aCbdataEfflinke[];
extern char aCouldnTOpenCbE_0[];
extern char aCouldnTOpenEff_0[];
extern char aDProjectPal3Co_7[];
extern int dword_17AB584;
extern int dword_17ABC64;
extern float flt_17ABC60;

// 0x00508E30
CCBStageEffect::CCBStageEffect()
{
  struct gbVFile *v2; // eax
  struct gbVFile *v3; // esi
  OpenBaseFile v5; // [esp+24h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+28h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+428h] [ebp-40Ch] BYREF
  int v8; // [esp+830h] [ebp-4h]

  ((OpenBaseFile *)&v5)->OpenBaseFile();
  v8 = 0;
  v2 = (struct gbVFile *)g_pVFileSys->OpenFile(aCbdataEfflinke, 0x201u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCouldnTOpenEff_0, aDProjectPal3Co_7, 366),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Read(&this->m_Light[6].m_ToWorld.zx, 0x5A00u, v3);
  g_pVFileSys->CloseFile(v3);
  dword_17AB584 = 1;
  v8 = -1;
  ((OpenNULLFile **)&v5)->OpenNULLFile();
  return (CCBStageEffect *)1;
}

// 0x00508F30
CCBStageEffect::~CCBStageEffect(int _this)
{
  struct gbVFile *v2; // eax
  struct gbVFile *v3; // esi
  OpenBaseFile v5; // [esp+24h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+28h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+428h] [ebp-40Ch] BYREF
  int v8; // [esp+830h] [ebp-4h]

  ((OpenBaseFile *)&v5)->OpenBaseFile();
  v8 = 0;
  v2 = (struct gbVFile *)g_pVFileSys->OpenFile(aCbdataEfflinke, 0x202u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCouldnTOpenCbE_0, aDProjectPal3Co_7, 390),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Write((void *)(this + 2444), 0x5A00u, v3);
  g_pVFileSys->CloseFile(v3);
  v8 = -1;
  ((OpenNULLFile **)&v5)->OpenNULLFile();
  return 1;
}

// 0x00509050
// attributes: thunk
int CCBStageEffect::Create()
{
  return CCBStageEffect::Destroy();
}

// 0x00509060
int CCBStageEffect::Destroy()
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
void CCBStageEffect::GetLinkerIndex()
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
