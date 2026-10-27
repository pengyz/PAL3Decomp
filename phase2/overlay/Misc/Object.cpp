#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/Object.h"
#include "Script/ScriptObj.h"

// 0x0041BE20
void Object::Object_adjthunk_1be20()
{
  int v1; // [esp+0x4] [ebp+0x4]

  // [overlay-fix 2026-10-27] C2039: _scalar_dtor_1BD0 无定义/声明（scalar deleting dtor 合成名）——待归属定谳
  // (((ScriptObj *)&this[-1]))->ScriptObj::_scalar_dtor_1BD0(v1);
}

// 0x004AF760
void Object::Update(int nVal1)
{
  ;
}

// 0x0055434F
void Object::FatalExit()
{
  _amsg_exit(0x19u);
}
