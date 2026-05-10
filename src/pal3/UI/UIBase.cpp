#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIBase.h"

// Forward declarations for unnamed functions
int sub_484E10(...);
int sub_488C70(...);
int sub_492E10(...);
int sub_49A980(...);

// 0x004A3900
int UIBase::SetItemData(int id, unsigned int data)
{
  UIBase *v4; // edi
  int result; // eax

  if ( id <= 5 )
  {
    v4 = this + 3788 * id;
    (**(void (***)(int, _DWORD))&v4[155140])((int)&v4[155140], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[155292])((int)&v4[155292], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[155444])((int)&v4[155444], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[155748])((int)&v4[155748], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[155992])((int)&v4[155992], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[156844])((int)&v4[156844], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[157088])((int)&v4[157088], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[156296])((int)&v4[156296], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[156540])((int)&v4[156540], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[157240])((int)&v4[157240], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[157392])((int)&v4[157392], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[157544])((int)&v4[157544], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[157696])((int)&v4[157696], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[157848])((int)&v4[157848], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[158000])((int)&v4[158000], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[158152])((int)&v4[158152], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[158304])((int)&v4[158304], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[158608])((int)&v4[158608], (unsigned __int8)data);
    (**(void (***)(int, _DWORD))&v4[158456])((int)&v4[158456], (unsigned __int8)data);
    sub_488C70(*((char **)this + 44015), id, data);
    sub_492E10(*((char **)this + 44016), id, (unsigned __int8)data);
    sub_49A980(*((char **)this + 44017), id, data);
    return sub_484E10(*((char **)this + 44014), id, data);
  }
  return result;
}

// 0x004A4890
int UIBase::GetSelected()
{
  int result; // eax
  int v2; // edx
  int v3; // edx

  result = 0;
  *((_DWORD *)this + 24) = 0;
  do
  {
    v2 = *((_DWORD *)this + 24);
    if ( *((_BYTE *)this + v2 + 361) )
      ++result;
    v3 = v2 + 1;
    *((_DWORD *)this + 24) = v3;
  }
  while ( v3 < 5 );
  return result;
}
