#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Script/ScriptObj.h"

// 0x00411CA0
void ScriptObj::_ScriptObj()
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  void **v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // edx
  void **v10; // eax
  ScriptObj v11; // ecx
  void *v12; // [esp-0xC] [ebp-0x38]
  _DWORD v13[4]; // [esp+0x10] [ebp-0x1C] BYREF
  int v14; // [esp+0x28] [ebp-0x4]

  v14 = 3;
  ((PalScript *)this)->DestroyScript();
  ((NPC *)(this + 170))->FreeBuffer();
  v2 = *((_DWORD *)this + 35);
  for ( LOBYTE(v14) = 2; v2; v2 = *((_DWORD *)this + 35) )
  {
    v3 = *((_DWORD *)this + 27) + 16;
    v4 = v2 - 1;
    *((_DWORD *)this + 27) = v3;
    *((_DWORD *)this + 35) = v4;
    if ( !v4 || v3 == *((_DWORD *)this + 26) )
    {
      v5 = (void **)*((_DWORD *)this + 28);
      *((_DWORD *)this + 28) = v5 + 1;
      operator delete(*v5);
      if ( *((_DWORD *)this + 35) )
      {
        v10 = (void **)*((_DWORD *)this + 28);
// [VFTABLE] v11.__vftable = *v10;
        *((_DWORD *)this + 25) = *v10;
// [VFTABLE] *((_DWORD *)this + 26) = (char *)v11.__vftable + 4096;
        *(this + 27) = v11;
        *((_DWORD *)this + 28) = v10;
      }
      else
      {
        ((PalScriptMgr *)v13)->Get_result();
        v6 = v13[0];
        v7 = v13[1];
        v8 = v13[3];
        v9 = v13[2];
        *(this + 25) = (ScriptObj)v13[0];
        *((_DWORD *)this + 26) = v7;
        *((_DWORD *)this + 27) = v9;
        *((_DWORD *)this + 28) = v8;
        *((_DWORD *)this + 29) = v6;
        v12 = (void *)*((_DWORD *)this + 33);
        *((_DWORD *)this + 30) = v7;
        *((_DWORD *)this + 31) = v9;
        *((_DWORD *)this + 32) = v8;
        operator delete(v12);
      }
    }
  }
  LOBYTE(v14) = 1;
  nearby_4b6ca0(this != 0 ? (void **)this + 16 : 0);
}
