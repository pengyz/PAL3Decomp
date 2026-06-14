#pragma once
// Auto-generated: WAVEFORMAT

class WAVEFORMAT {
public:
    WORD wFormatTag; // +0x0
    WORD nChannels; // +0x2
    UINT nSamplesPerSec; // +0x4
    UINT nAvgBytesPerSec; // +0x8
    WORD nBlockAlign; // +0xC
    char _tail_00E[2]; // +0xE
    // total size: 0x10 (16)

};
