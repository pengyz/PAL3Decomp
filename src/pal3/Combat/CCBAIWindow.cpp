#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBAIWindow.h"

// 0x004DFE00
int CCBAIWindow::SetText(int a2, int a3)
{
  int result; // eax
  int v5; // [esp+10h] [ebp+Ch]
  int v6; // [esp+14h] [ebp+10h]

  sprintf((char *const)&this->m_wndcolor + 280 * this->m_fontcolor.Alpha, "%d", v5);
  *((float *)this + 70 * this->m_fontcolor.Alpha + 71) = ((double)a2 + (double)a2) / (double)g_Input.KeyInfo[120].Data
                                                       - 1.0;
  *((float *)this + 70 * this->m_fontcolor.Alpha + 72) = 1.0
                                                       - ((double)a3 + (double)a3)
                                                       / (double)g_Input.KeyInfo[120].HoldTime;
  *(&this->m_fontcolor.Color + 70 * this->m_fontcolor.Alpha) = 2;
  *((_DWORD *)this + 70 * this->m_fontcolor.Alpha + 74) = 1094713344;
  *((_DWORD *)this + 70 * this->m_fontcolor.Alpha + 70) = v6;
  result = this->m_fontcolor.Alpha + 1;
  this->m_fontcolor.Alpha = result;
  return result;
}
