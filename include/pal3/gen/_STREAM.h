#pragma once
// Auto-generated: _STREAM

class ASISTAGE;
class _SAMPLE;

class _STREAM {
public:
    long block_oriented; // +0x0
    long using_ASI; // +0x4
    ASISTAGE * ASI; // +0x8
    _SAMPLE * samp; // +0xC
    DWORD fileh; // +0x10
    BYTE * bufs[3]; // +0x14
    DWORD bufsizes[3]; // +0x20
    long reset_ASI[3]; // +0x2C
    long bufstart[3]; // +0x38
    void * asyncs[3]; // +0x44
    long loadedbufstart[2]; // +0x50
    long loadedorder[2]; // +0x58
    long loadorder; // +0x60
    long bufsize; // +0x64
    long readsize; // +0x68
    DWORD buf1; // +0x6C
    long size1; // +0x70
    DWORD buf2; // +0x74
    long size2; // +0x78
    DWORD buf3; // +0x7C
    long size3; // +0x80
    DWORD datarate; // +0x84
    long filerate; // +0x88
    long filetype; // +0x8C
    DWORD fileflags; // +0x90
    long totallen; // +0x94
    long substart; // +0x98
    long sublen; // +0x9C
    long subpadding; // +0xA0
    DWORD blocksize; // +0xA4
    long padding; // +0xA8
    long padded; // +0xAC
    long loadedsome; // +0xB0
    DWORD startpos; // +0xB4
    DWORD totalread; // +0xB8
    DWORD loopsleft; // +0xBC
    DWORD error; // +0xC0
    long preload; // +0xC4
    DWORD preloadpos; // +0xC8
    long noback; // +0xCC
    long alldone; // +0xD0
    long primeamount; // +0xD4
    long readatleast; // +0xD8
    long playcontrol; // +0xDC
    void * * callback; // +0xE0
    long user_data[8]; // +0xE4
    void * next; // +0x104
    long autostreaming; // +0x108
    long cb_IsWin32s; // +0x10C
    long docallback; // +0x110
    // total size: 0x114 (276)

};
