#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIQuadManager.h"

// Forward declarations for unnamed functions
int sub_541470(...);

// Unnamed globals (extern)
extern TextureLibDataBase stru_1894B78;
void __cdecl unknown_libname_522(void);

// 0x005415F0
UIQuadManager * UIQuadManager::GetInstance()
{
  if ( (*(&((TextureLibDataBase *)&stru_1894B78)->_isLoadTLI + 36) & 1) == 0 )
  {
    *(&((TextureLibDataBase *)&stru_1894B78)->_isLoadTLI + 36) |= 1u;
    sub_541470(&((TextureLibDataBase *)&stru_1894B78)->_isLoadTLI + 4);
    atexit(unknown_libname_522);
  }
  return (UIQuadManager *)(&((TextureLibDataBase *)&stru_1894B78)->_isLoadTLI + 4);
}
