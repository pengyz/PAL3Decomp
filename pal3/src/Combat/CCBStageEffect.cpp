#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBStageEffect.h"

// Unnamed globals (extern)
extern int dword_17AB584;
extern int dword_17ABC64;
extern float flt_17ABC60;

// 0x00508E30
CCBStageEffect::CCBStageEffect()
{
  gbVFile *v2; // eax
  gbVFile *v3; // esi
  OpenBaseFile v4; // [esp+0x24] [ebp-0x810] BYREF
  char pExceptionObject[1024]; // [esp+0x28] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x428] [ebp-0x40C] BYREF
  int v7; // [esp+0x830] [ebp-0x4]

  v7 = 0;
  v2 = ((gbVFileSystem *)g_pVFileSys)->OpenFile("cbdata\\efflinker.dat", 0x201u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(aCouldnTOpenEff, aDProjectPal3Co_4, 366),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((gbVFileSystem *)g_pVFileSys)->Seek(v2, 0, 1);
  ((gbVFileSystem *)g_pVFileSys)->Read(this->m_Linker, 0x5A00u, v3);
  ((gbVFileSystem *)g_pVFileSys)->CloseFile(v3);
  dword_17AB584 = 1;
  v7 = -1;
}

// 0x00508F30
void CCBStageEffect::_CCBStageEffect()
{
  gbVFile *v2; // eax
  gbVFile *v3; // esi
  OpenBaseFile v4; // [esp+0x24] [ebp-0x810] BYREF
  char pExceptionObject[1024]; // [esp+0x28] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x428] [ebp-0x40C] BYREF
  int v7; // [esp+0x830] [ebp-0x4]

  v7 = 0;
  v2 = ((gbVFileSystem *)g_pVFileSys)->OpenFile("cbdata\\efflinker.dat", 0x202u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(aCouldnTOpenCbE, aDProjectPal3Co_4, 390),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((gbVFileSystem *)g_pVFileSys)->Seek(v2, 0, 1);
  ((gbVFileSystem *)g_pVFileSys)->Write(this->m_Linker, 0x5A00u, v3);
  ((gbVFileSystem *)g_pVFileSys)->CloseFile(v3);
  v7 = -1;
}

// 0x00509050
// attributes: thunk
bool CCBStageEffect::Create()
{
  return this->Destroy();
}

// 0x00509060
bool CCBStageEffect::Destroy()
{
  dword_17ABC64 = 1094713344;
  return 0;
}

// 0x00509070
// attributes: thunk
void CCBStageEffect::Init()
{

}

// 0x00509080
void CCBStageEffect::GetLinkerIndex()
{
  flt_17ABC60 = 12.0 + 12.0;
}

// 0x00509090
// attributes: thunk
void CCBStageEffect::PreLoadEffGroup()
{
  compiler_init_005090A0(this);
}

// 0x005090E0
// attributes: thunk
void CCBStageEffect::LoadLinker()
{
  ((CCBStageRole *)this)->Proceed();
}
