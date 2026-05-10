#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageCam.h"
#include "pal3/gen/CCCTData.h"

// 0x00505490
char CCBStageCam::Destroy()
{
  ((int)this)->Create();
  ((int)this)->~CCBStageCam();
  ((CCCTData *)this)->Destroy();
  return 1;
}

// 0x005054E0
char CCBStageCam::Update()
{
  ((int)this)->Create();
  return 1;
}
