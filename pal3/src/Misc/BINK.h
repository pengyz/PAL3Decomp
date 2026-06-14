#pragma once
// Auto-generated: BINK

#include "BINKIO.h"
#include "BINKRECT.h"
#include "BINKSND.h"
#include "BUNDLEPOINTERS.h"

class BINK {
public:
    UINT Width; // +0x0
    UINT Height; // +0x4
    UINT Frames; // +0x8
    UINT FrameNum; // +0xC
    UINT LastFrameNum; // +0x10
    UINT FrameRate; // +0x14
    UINT FrameRateDiv; // +0x18
    UINT ReadError; // +0x1C
    UINT OpenFlags; // +0x20
    UINT BinkType; // +0x24
    UINT Size; // +0x28
    UINT FrameSize; // +0x2C
    UINT SndSize; // +0x30
    BINKRECT FrameRects[8]; // +0x34
    char _gap_054[96]; // +0x54
    int NumRects; // +0xB4
    UINT PlaneNum; // +0xB8
    char * YPlane[2]; // +0xBC
    char _gap_0C0[4]; // +0xC0
    char * APlane[2]; // +0xC4
    char _gap_0C8[4]; // +0xC8
    UINT YWidth; // +0xCC
    UINT YHeight; // +0xD0
    UINT UVWidth; // +0xD4
    UINT UVHeight; // +0xD8
    char * MaskPlane; // +0xDC
    UINT MaskPitch; // +0xE0
    UINT MaskLength; // +0xE4
    UINT LargestFrameSize; // +0xE8
    UINT InternalFrames; // +0xEC
    int NumTracks; // +0xF0
    UINT Highest1SecRate; // +0xF4
    UINT Highest1SecFrame; // +0xF8
    int Paused; // +0xFC
    UINT BackgroundThread; // +0x100
    char * compframe; // +0x104
    char * preloadptr; // +0x108
    UINT * frameoffsets; // +0x10C
    BINKIO bio; // +0x110
    char _gap_114[200]; // +0x114
    _BYTE * ioptr; // +0x1DC
    UINT iosize; // +0x1E0
    UINT decompwidth; // +0x1E4
    UINT decompheight; // +0x1E8
    int trackindex; // +0x1EC
    UINT * tracksizes; // +0x1F0
    UINT * tracktypes; // +0x1F4
    int * trackIDs; // +0x1F8
    UINT numrects; // +0x1FC
    UINT playedframes; // +0x200
    UINT firstframetime; // +0x204
    UINT startframetime; // +0x208
    UINT startblittime; // +0x20C
    UINT startsynctime; // +0x210
    UINT startsyncframe; // +0x214
    UINT twoframestime; // +0x218
    UINT entireframetime; // +0x21C
    UINT slowestframetime; // +0x220
    UINT slowestframe; // +0x224
    UINT slowest2frametime; // +0x228
    UINT slowest2frame; // +0x22C
    UINT soundon; // +0x230
    UINT videoon; // +0x234
    UINT totalmem; // +0x238
    UINT timevdecomp; // +0x23C
    UINT timeadecomp; // +0x240
    UINT timeblit; // +0x244
    UINT timeopen; // +0x248
    UINT fileframerate; // +0x24C
    UINT fileframeratediv; // +0x250
    UINT threadcontrol; // +0x254
    UINT runtimeframes; // +0x258
    UINT runtimemoveamt; // +0x25C
    UINT * rtframetimes; // +0x260
    UINT * rtadecomptimes; // +0x264
    UINT * rtvdecomptimes; // +0x268
    UINT * rtblittimes; // +0x26C
    UINT * rtreadtimes; // +0x270
    UINT * rtidlereadtimes; // +0x274
    UINT * rtthreadreadtimes; // +0x278
    UINT lastblitflags; // +0x27C
    UINT lastdecompframe; // +0x280
    UINT sndbufsize; // +0x284
    _BYTE * sndbuf; // +0x288
    _BYTE * sndend; // +0x28C
    _BYTE * sndwritepos; // +0x290
    _BYTE * sndreadpos; // +0x294
    UINT sndcomp; // +0x298
    UINT sndamt; // +0x29C
    UINT sndreenter; // +0x2A0
    UINT sndconvert8; // +0x2A4
    BINKSND bsnd; // +0x2A8
    char _gap_2AC[188]; // +0x2AC
    UINT skippedlastblit; // +0x368
    UINT skippedblits; // +0x36C
    UINT soundskips; // +0x370
    UINT sndendframe; // +0x374
    UINT sndprime; // +0x378
    UINT sndpad; // +0x37C
    BUNDLEPOINTERS bunp; // +0x380
    char _tail_384[32]; // +0x384
    // total size: 0x3A4 (932)

    void Reset(); // 0x004236D0
    void Destroy(); // 0x004243E0
    int SetVideoRect(char pData); // 0x004517A0
};
