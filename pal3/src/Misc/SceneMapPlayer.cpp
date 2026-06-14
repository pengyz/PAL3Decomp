#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SceneMapPlayer.h"

// Forward declarations for unnamed functions
int sub_4202F0(...);

// 0x004208A0
void SceneMapPlayer::Reset()
{
  gbRefObject *m_tex; // ecx

  m_tex = (gbRefObject *)this->m_tex;
  if ( m_tex )
  {
    ((gbRefObject *)m_tex)->Release();
    this->m_tex = 0;
  }
  ((gbImage2D *)&this->m_img)->Release();
  sub_4202F0(this);
  this->m_layer = 0;
  memset(this->m_szName, 0, sizeof(this->m_szName));
  this->m_bBuild = 0;
}

// 0x004220F0
void SceneMapPlayer::ClearName()
{
  memset(this->m_szName, 0, sizeof(this->m_szName));
}
