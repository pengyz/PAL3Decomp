#pragma once
// Auto-generated: BINK

#include "BINKIO.h"
#include "BINKRECT.h"
#include "BINKSND.h"
#include "BUNDLEPOINTERS.h"

class BINK {
public:
    unsigned long Width; // +0x0
    unsigned long Height; // +0x4
    unsigned long Frames; // +0x8
    unsigned long FrameNum; // +0xC
    unsigned long LastFrameNum; // +0x10
    unsigned long FrameRate; // +0x14
    unsigned long FrameRateDiv; // +0x18
    unsigned long ReadError; // +0x1C
    unsigned long OpenFlags; // +0x20
    unsigned long BinkType; // +0x24
    unsigned long Size; // +0x28
    unsigned long FrameSize; // +0x2C
    unsigned long SndSize; // +0x30
    BINKRECT FrameRects[8]; // +0x34
    long NumRects; // +0xB4
    unsigned long PlaneNum; // +0xB8
    void * YPlane[2]; // +0xBC
    void * APlane[2]; // +0xC4
    unsigned long YWidth; // +0xCC
    unsigned long YHeight; // +0xD0
    unsigned long UVWidth; // +0xD4
    unsigned long UVHeight; // +0xD8
    void * MaskPlane; // +0xDC
    unsigned long MaskPitch; // +0xE0
    unsigned long MaskLength; // +0xE4
    unsigned long LargestFrameSize; // +0xE8
    unsigned long InternalFrames; // +0xEC
    long NumTracks; // +0xF0
    unsigned long Highest1SecRate; // +0xF4
    unsigned long Highest1SecFrame; // +0xF8
    long Paused; // +0xFC
    unsigned long BackgroundThread; // +0x100
    void * compframe; // +0x104
    void * preloadptr; // +0x108
    unsigned long * frameoffsets; // +0x10C
    BINKIO bio; // +0x110
    unsigned char * ioptr; // +0x1DC
    unsigned long iosize; // +0x1E0
    unsigned long decompwidth; // +0x1E4
    unsigned long decompheight; // +0x1E8
    long trackindex; // +0x1EC
    unsigned long * tracksizes; // +0x1F0
    unsigned long * tracktypes; // +0x1F4
    long * trackIDs; // +0x1F8
    unsigned long numrects; // +0x1FC
    unsigned long playedframes; // +0x200
    unsigned long firstframetime; // +0x204
    unsigned long startframetime; // +0x208
    unsigned long startblittime; // +0x20C
    unsigned long startsynctime; // +0x210
    unsigned long startsyncframe; // +0x214
    unsigned long twoframestime; // +0x218
    unsigned long entireframetime; // +0x21C
    unsigned long slowestframetime; // +0x220
    unsigned long slowestframe; // +0x224
    unsigned long slowest2frametime; // +0x228
    unsigned long slowest2frame; // +0x22C
    unsigned long soundon; // +0x230
    unsigned long videoon; // +0x234
    unsigned long totalmem; // +0x238
    unsigned long timevdecomp; // +0x23C
    unsigned long timeadecomp; // +0x240
    unsigned long timeblit; // +0x244
    unsigned long timeopen; // +0x248
    unsigned long fileframerate; // +0x24C
    unsigned long fileframeratediv; // +0x250
    unsigned long threadcontrol; // +0x254
    unsigned long runtimeframes; // +0x258
    unsigned long runtimemoveamt; // +0x25C
    unsigned long * rtframetimes; // +0x260
    unsigned long * rtadecomptimes; // +0x264
    unsigned long * rtvdecomptimes; // +0x268
    unsigned long * rtblittimes; // +0x26C
    unsigned long * rtreadtimes; // +0x270
    unsigned long * rtidlereadtimes; // +0x274
    unsigned long * rtthreadreadtimes; // +0x278
    unsigned long lastblitflags; // +0x27C
    unsigned long lastdecompframe; // +0x280
    unsigned long sndbufsize; // +0x284
    unsigned char * sndbuf; // +0x288
    unsigned char * sndend; // +0x28C
    unsigned char * sndwritepos; // +0x290
    unsigned char * sndreadpos; // +0x294
    unsigned long sndcomp; // +0x298
    unsigned long sndamt; // +0x29C
    unsigned long sndreenter; // +0x2A0
    unsigned long sndconvert8; // +0x2A4
    BINKSND bsnd; // +0x2A8
    unsigned long skippedlastblit; // +0x368
    unsigned long skippedblits; // +0x36C
    unsigned long soundskips; // +0x370
    unsigned long sndendframe; // +0x374
    unsigned long sndprime; // +0x378
    unsigned long sndpad; // +0x37C
    BUNDLEPOINTERS bunp; // +0x380
    // total size: 0x3A4 (932)

};
