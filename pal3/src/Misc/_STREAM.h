#pragma once
// Auto-generated: _STREAM

class ASISTAGE;
class _SAMPLE;

class _STREAM {
public:
    int block_oriented; // +0x0
    int using_ASI; // +0x4
    ASISTAGE * ASI; // +0x8
    _SAMPLE * samp; // +0xC
    UINT fileh; // +0x10
    _BYTE * bufs[3]; // +0x14
    char _gap_018[8]; // +0x18
    UINT bufsizes[3]; // +0x20
    int reset_ASI[3]; // +0x2C
    int bufstart[3]; // +0x38
    char * asyncs[3]; // +0x44
    char _gap_048[8]; // +0x48
    int loadedbufstart[2]; // +0x50
    int loadedorder[2]; // +0x58
    int loadorder; // +0x60
    int bufsize; // +0x64
    int readsize; // +0x68
    UINT buf1; // +0x6C
    int size1; // +0x70
    UINT buf2; // +0x74
    int size2; // +0x78
    UINT buf3; // +0x7C
    int size3; // +0x80
    UINT datarate; // +0x84
    int filerate; // +0x88
    int filetype; // +0x8C
    UINT fileflags; // +0x90
    int totallen; // +0x94
    int substart; // +0x98
    int sublen; // +0x9C
    int subpadding; // +0xA0
    UINT blocksize; // +0xA4
    int padding; // +0xA8
    int padded; // +0xAC
    int loadedsome; // +0xB0
    UINT startpos; // +0xB4
    UINT totalread; // +0xB8
    UINT loopsleft; // +0xBC
    UINT error; // +0xC0
    int preload; // +0xC4
    UINT preloadpos; // +0xC8
    int noback; // +0xCC
    int alldone; // +0xD0
    int primeamount; // +0xD4
    int readatleast; // +0xD8
    int playcontrol; // +0xDC
    char * callback; // +0xE0
    int user_data[8]; // +0xE4
    char * next; // +0x104
    int autostreaming; // +0x108
    int cb_IsWin32s; // +0x10C
    int docallback; // +0x110
    // total size: 0x114 (276)

};
