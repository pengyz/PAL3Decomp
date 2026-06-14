#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CMeteorChain.h"

// 0x004CD0A0
CMeteorChain::CMeteorChain()
{
  tagMeteorNode *m_pFirstNode; // esi
  tagMeteorNode *v3; // eax

  m_pFirstNode = this->m_pFirstNode;
  while ( m_pFirstNode )
  {
    v3 = m_pFirstNode;
    m_pFirstNode = m_pFirstNode->pNext;
    operator delete(v3);
  }
  if ( this->m_pGeomQuad )
    operator delete(this->m_pGeomQuad);
}

// 0x004CD7E0
void CMeteorChain::Update(
        
        int fCurTime,
        int nVal,
        int nVal2,
        int *p_DWORD,
        int nVal3,
        int nVal4)
{
  float m_fLastTime; // ecx
  int v9; // esi
  gbTexture *v10; // edx
  unsigned int *i; // eax
  int *v12; // edx
  unsigned int v13; // eax
  int *v14; // edx

  m_fLastTime = this->m_fLastTime;
  v9 = 0;
  if ( SLODWORD(m_fLastTime) > 0 )
  {
    v10 = this->m_pTextureArray->pTexPt[38 * fCurTime];
    for ( i = &v10->InFmt.r_shift; *(_BYTE *)i; i += 18 )
    {
      if ( ++v9 >= SLODWORD(m_fLastTime) )
        return;
    }
    v12 = (int *)((char *)v10 + 72 * v9);
    memset(v12, 0, 0x48u);
    *((_BYTE *)v12 + 65) = 0;
    *((_BYTE *)v12 + 64) = 1;
    *v12 = nVal;
    v12[1] = nVal2;
    v12[2] = 2;
    v13 = ++g_PAL3.m_nMeteorChainCount;
    if ( !g_PAL3.m_nMeteorChainCount || v13 >= 0x7FFFFFFF )
    {
      v13 = 1;
      g_PAL3.m_nMeteorChainCount = 1;
    }
    v12[3] = v13;
    v12[4] = 0;
    v12[5] = nVal3;
    v12[6] = nVal4;
    if ( p_DWORD )
    {
      v14 = v12 + 7;
      *v14 = *p_DWORD;
      v14[1] = p_DWORD[1];
      v14[2] = p_DWORD[2];
      v14[3] = p_DWORD[3];
    }
    ++this->m_pTextureArray->pTexPt[38 * fCurTime + 1];
  }
}
