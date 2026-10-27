#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PalScriptAnimTimer.h"
#include "Role/NPC.h"

// 0x00438E30
void PalScriptAnimTimer::UpdateAnimTimer(float a2)
{
  float v2; // st7
  int v3; // [esp+0x4] [ebp+0x4]

  v2 = a2 + this->m_fTime;
  this->m_fTime = v2;
  if ( v2 >= 4.0f )
  {
    this->m_bDone = 1;
    this->m_fTime = 4.0f;
  }
  v3 = -1;
  HIBYTE(v3) = (__int64)(sin(this->m_fTime * 0.78539819) * 160.0);
  (((NPC *)LODWORD(g_fGameSpeed)))->NPC::UpdateAnim(v3);
}

// 0x00438E90
PalScriptAnimTimer::~PalScriptAnimTimer()
{
  char v2; // [esp+0x8] [ebp+0x4]

  (((filebuf *)this))->filebuf::~filebuf();
  if ( (v2 & 1) != 0 )
    operator delete(this);
}
