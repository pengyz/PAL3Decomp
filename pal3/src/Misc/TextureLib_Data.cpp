#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/TextureLib_Data.h"

// Forward declarations for unnamed functions
char * Texture_Info_FormatException(char *ArgList, const char *pszName, const char *pszName2, const char *pszName3, int nVal); // from annotations

// 0x0053FCF0
CHAR * TextureLib_Data::_CalculateUV(LPCSTR lpString)
{
  int v3; // edi
  int v4; // ebx
  int v6; // [esp+0x0] [ebp-0x810]
  char pExceptionObject[1024]; // [esp+0x10] [ebp-0x800] BYREF

  if ( !this->_isLoadTLI || lstrlenA(lpString) <= 0 )
    return g_szSceneUIText;
  v3 = 0;
  if ( this->_realNum <= 0 )
  {
LABEL_7:
    qmemcpy(
      pExceptionObject,
      Texture_Info_FormatException(&Delimiter[8], lpString, &Delimiter[36], (const char *)0x228, v6),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v4 = 0;
  while ( _strcmpi(lpString, this->m_pData[v4]._tex_name) )
  {
    ++v3;
    ++v4;
    if ( v3 >= this->_realNum )
      goto LABEL_7;
  }
  return this->m_pData[v3]._tex_lib;
}
