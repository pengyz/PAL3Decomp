#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/_Texture_Info.h"

// Unnamed globals (extern)
extern char aDProjectPal3Ui_0[];
extern char aNotFoundSInUiO[];

// 0x0053FCF0
Scene * _Texture_Info::_CalculateUV(int _this, LPCSTR lpString)
{
  int v3; // edi
  int v4; // ebx
  char pExceptionObject[1024]; // [esp+10h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+410h] [ebp-400h] BYREF

  if ( !*(_BYTE *)(this + 532) || lstrlenA(lpString) <= 0 )
    return (Scene *)&g_SceneMgr.m_npc[5].m_path.normal[140].y;
  v3 = 0;
  if ( *(int *)(this + 524) <= 0 )
  {
LABEL_7:
    qmemcpy(
      pExceptionObject,
      Texture_Info_53CF30(ArgList, aNotFoundSInUiO, lpString, aDProjectPal3Ui_0, 552),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v4 = 0;
  while ( _strcmpi(lpString, (const char *)(v4 + *(_DWORD *)(this + 528))) )
  {
    ++v3;
    v4 += 1088;
    if ( v3 >= *(_DWORD *)(this + 524) )
      goto LABEL_7;
  }
  return (Scene *)(1088 * v3 + *(_DWORD *)(this + 528) + 512);
}
