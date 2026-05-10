#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CMeteorChain.h"

// 0x004CD0A0
CMeteorChain::CMeteorChain()
{
  tagMeteorNode *m_pFirstNode; // esi
  tagMeteorNode *v3; // eax

  m_pFirstNode = (tagMeteorNode *)this->m_pFirstNode;
  while ( m_pFirstNode )
  {
    v3 = m_pFirstNode;
    m_pFirstNode = (tagMeteorNode *)m_pFirstNode->pNext;
    operator delete(v3);
  }
  if ( this->m_pGeomQuad )
    operator delete(this->m_pGeomQuad);
}
