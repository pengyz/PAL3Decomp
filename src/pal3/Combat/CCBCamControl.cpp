#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBCamControl.h"

// Unnamed globals (extern)
extern int nullsub_3;

// 0x005083B0
char * CCBCamControl::SetCircle(int a2)
{
  float *p_fFromZ; // eax
  int v4; // ecx

  ((gbVolModNode *)&this->m_CCT.m_Pool[0].bFinished)->gbVolModNode();
  `eh vector constructor iterator'(
    (char *)&this->m_CCT.m_Pool[0].fCircleCentreY,
    0xDCu,
    10,
    gbVolModNode::gbVolModNode,
    gbVolModNode::~gbVolModNode);
  p_fFromZ = (float *)&this->m_CCT.m_Pool[8].EndPos.fFromZ;
  v4 = 384;
  do
  {
    *(p_fFromZ - 2) = 0.0;
    *(p_fFromZ - 1) = 0.0;
    *p_fFromZ = 0.0;
    p_fFromZ[5] = 0.0;
    p_fFromZ[6] = 0.0;
    p_fFromZ[7] = 0.0;
    p_fFromZ += 15;
    --v4;
  }
  while ( v4 );
  nullsub_3(this);
  this->m_CCT.m_Pool[8].StartPos.pit = 0.0;
  this->m_CCT.m_Pool[8].StartPos.fRoll = 0.0;
  this->m_CCT.m_Pool[0].bValid = a2;
  return (char *)this;
}
