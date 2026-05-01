#include <windows.h>

int PAL3A_Bootstrap(void);

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    return PAL3A_Bootstrap();
}
