#ifndef PAL3A_WINMAIN_H
#define PAL3A_WINMAIN_H

#include "pal3a_types.h"

void SFINIT3_OverFlow();
void SkipTime();
long LowLevelKeyboardProc(int nCode, uint wParam, long lParam);
void SFINIT2_SafeExitGame();
void SFINIT1_open_item_data();
void GetDefaultCD();

#endif // PAL3A_WINMAIN_H
