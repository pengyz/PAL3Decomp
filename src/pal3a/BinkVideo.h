#ifndef PAL3A_BINKVIDEO_H
#define PAL3A_BINKVIDEO_H

#include "pal3a_types.h"

class gbBinkVideo {
public:
    char _data[1835912];

    void SetVolume(int vol);
    void Release();
    int SFLB_OpenFile(char * szFileName, HWND * hWnd, int bChangeScreenMode, int nOpenFlag);
    ~gbBinkVideo();
    void Goto(int nFrame);
    gbBinkVideo();
    int Height();
    void SetPos(int nDestLeft, int nDestTop);
    int DoModal(int bCanSkip);
    int OpenFile(char * szFileName, HWND * hWnd, int bChangeScreenMode, int nOpenFlag);
    int BinkWait();
    int Width();
    int DrawFrame(void * pDestBuf, int nDestPitch, int nDestHeight, int nDestLeft, int nDestTop, int nDestSurfaceType);
    int DrawFrame();
    void InitBinkSys(void * hSndDriver, int bSndChoose);
};

#endif // PAL3A_BINKVIDEO_H
