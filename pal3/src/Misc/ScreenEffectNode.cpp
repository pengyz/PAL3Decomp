#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ScreenEffectNode.h"

// 0x004B7C30
ScreenEffectNode::ScreenEffectNode()
{
  char *v2; // esi
  int v3; // ebx
  char *v4; // esi
  int v5; // ebx

  v2 = (char *)this + 172;
  *((_DWORD *)this + 40) = 0;
  v3 = 4;
  do
  {
    v2 += 12;
    --v3;
  }
  while ( v3 );
  v4 = (char *)this + 240;
  v5 = 12;
  do
  {
    v4 += 68;
    --v5;
  }
  while ( v5 );
}

// 0x004B7CE0
void ScreenEffectNode::_ScreenEffectNode()
{
  ((UINote *)this)->ReleaseResources();
  gbChain1DNode::Process();
}
