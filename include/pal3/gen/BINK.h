#pragma once
// Auto-generated: BINK

#include "BINKIO.h"
#include "BINKRECT.h"
#include "BINKSND.h"
#include "BUNDLEPOINTERS.h"

class BINK {
public:
    DWORD Width; // +0x0
    DWORD Height; // +0x4
    DWORD Frames; // +0x8
    DWORD FrameNum; // +0xC
    DWORD LastFrameNum; // +0x10
    DWORD FrameRate; // +0x14
    DWORD FrameRateDiv; // +0x18
    DWORD ReadError; // +0x1C
    DWORD OpenFlags; // +0x20
    DWORD BinkType; // +0x24
    DWORD Size; // +0x28
    DWORD FrameSize; // +0x2C
    DWORD SndSize; // +0x30
    BINKRECT FrameRects[8]; // +0x34
    long NumRects; // +0xB4
    DWORD PlaneNum; // +0xB8
    void * YPlane[2]; // +0xBC
    void * APlane[2]; // +0xC4
    DWORD YWidth; // +0xCC
    DWORD YHeight; // +0xD0
    DWORD UVWidth; // +0xD4
    DWORD UVHeight; // +0xD8
    void * MaskPlane; // +0xDC
    DWORD MaskPitch; // +0xE0
    DWORD MaskLength; // +0xE4
    DWORD LargestFrameSize; // +0xE8
    DWORD InternalFrames; // +0xEC
    long NumTracks; // +0xF0
    DWORD Highest1SecRate; // +0xF4
    DWORD Highest1SecFrame; // +0xF8
    long Paused; // +0xFC
    DWORD BackgroundThread; // +0x100
    void * compframe; // +0x104
    void * preloadptr; // +0x108
    DWORD * frameoffsets; // +0x10C
    BINKIO bio; // +0x110
    BYTE * ioptr; // +0x1DC
    DWORD iosize; // +0x1E0
    DWORD decompwidth; // +0x1E4
    DWORD decompheight; // +0x1E8
    long trackindex; // +0x1EC
    DWORD * tracksizes; // +0x1F0
    DWORD * tracktypes; // +0x1F4
    long * trackIDs; // +0x1F8
    DWORD numrects; // +0x1FC
    DWORD playedframes; // +0x200
    DWORD firstframetime; // +0x204
    DWORD startframetime; // +0x208
    DWORD startblittime; // +0x20C
    DWORD startsynctime; // +0x210
    DWORD startsyncframe; // +0x214
    DWORD twoframestime; // +0x218
    DWORD entireframetime; // +0x21C
    DWORD slowestframetime; // +0x220
    DWORD slowestframe; // +0x224
    DWORD slowest2frametime; // +0x228
    DWORD slowest2frame; // +0x22C
    DWORD soundon; // +0x230
    DWORD videoon; // +0x234
    DWORD totalmem; // +0x238
    DWORD timevdecomp; // +0x23C
    DWORD timeadecomp; // +0x240
    DWORD timeblit; // +0x244
    DWORD timeopen; // +0x248
    DWORD fileframerate; // +0x24C
    DWORD fileframeratediv; // +0x250
    DWORD threadcontrol; // +0x254
    DWORD runtimeframes; // +0x258
    DWORD runtimemoveamt; // +0x25C
    DWORD * rtframetimes; // +0x260
    DWORD * rtadecomptimes; // +0x264
    DWORD * rtvdecomptimes; // +0x268
    DWORD * rtblittimes; // +0x26C
    DWORD * rtreadtimes; // +0x270
    DWORD * rtidlereadtimes; // +0x274
    DWORD * rtthreadreadtimes; // +0x278
    DWORD lastblitflags; // +0x27C
    DWORD lastdecompframe; // +0x280
    DWORD sndbufsize; // +0x284
    BYTE * sndbuf; // +0x288
    BYTE * sndend; // +0x28C
    BYTE * sndwritepos; // +0x290
    BYTE * sndreadpos; // +0x294
    DWORD sndcomp; // +0x298
    DWORD sndamt; // +0x29C
    DWORD sndreenter; // +0x2A0
    DWORD sndconvert8; // +0x2A4
    BINKSND bsnd; // +0x2A8
    DWORD skippedlastblit; // +0x368
    DWORD skippedblits; // +0x36C
    DWORD soundskips; // +0x370
    DWORD sndendframe; // +0x374
    DWORD sndprime; // +0x378
    DWORD sndpad; // +0x37C
    BUNDLEPOINTERS bunp; // +0x380
    // total size: 0x3A4 (932)

};
