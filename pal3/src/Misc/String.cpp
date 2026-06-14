#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/String.h"

// 0x004326A0
void String::Assign(char *src, int len)
{
  String v5; // eax
  int v6; // eax
  char *v7; // eax
  char *srca; // [esp+0x10] [ebp+0x4]
  int lena; // [esp+0x14] [ebp+0x8]

  if ( len > 0 )
    *((_DWORD *)this + 3) = len;
  v5 = *this;
  if ( g_SceneMgr.m_pSceneRoot )
  {
    if ( v5 )
    {
      if ( (int)g_SceneMgr.m_pSceneRoot > *((_DWORD *)this + 2) )
      {
        lena = (int)g_SceneMgr.m_pSceneRoot;
        if ( (int)g_SceneMgr.m_pSceneRoot <= *((_DWORD *)this + 3) + *((_DWORD *)this + 1) )
          lena = *((_DWORD *)this + 3) + *((_DWORD *)this + 1);
        srca = (char *)malloc(4 * lena);
        qmemcpy(srca, *(const void **)this, 4 * *((_DWORD *)this + 1));
        free(*(void **)this);
        *((_DWORD *)this + 1) = g_SceneMgr.m_pSceneRoot;
        *this = (String)srca;
        *((_DWORD *)this + 2) = lena;
      }
      else
      {
        *((_DWORD *)this + 1) = g_SceneMgr.m_pSceneRoot;
      }
    }
    else
    {
      v6 = *((_DWORD *)this + 3);
      *((_DWORD *)this + 1) = g_SceneMgr.m_pSceneRoot;
      v7 = &g_SceneMgr.m_pSceneRoot[v6];
      *((_DWORD *)this + 2) = v7;
      *this = (String)malloc(4 * (_DWORD)v7);
    }
  }
  else
  {
    if ( v5 )
    {
      free(*(void **)this);
      *this = 0;
    }
    *((_DWORD *)this + 2) = 0;
    *((_DWORD *)this + 1) = 0;
  }
}
