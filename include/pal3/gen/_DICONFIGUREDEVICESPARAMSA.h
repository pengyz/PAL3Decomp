#pragma once
// Auto-generated: _DICONFIGUREDEVICESPARAMSA

#include "_DICOLORSET.h"

class HWND__;
class IUnknown;
class _DIACTIONFORMATA;

class _DICONFIGUREDEVICESPARAMSA {
public:
    unsigned long dwSize; // +0x0
    unsigned long dwcUsers; // +0x4
    char * lptszUserNames; // +0x8
    unsigned long dwcFormats; // +0xC
    _DIACTIONFORMATA * lprgFormats; // +0x10
    HWND__ * hwnd; // +0x14
    _DICOLORSET dics; // +0x18
    IUnknown * lpUnkDDSTarget; // +0x3C
    // total size: 0x40 (64)

};
