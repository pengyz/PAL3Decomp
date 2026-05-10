#pragma once
// Auto-generated: ASISTAGE

class ASISTAGE {
public:
    void * * ASI_stream_open; // +0x0
    void * * ASI_stream_process; // +0x4
    void * * ASI_stream_seek; // +0x8
    void * * ASI_stream_close; // +0xC
    void * * ASI_stream_attribute; // +0x10
    void * * ASI_stream_set_preference; // +0x14
    DWORD INPUT_BIT_RATE; // +0x18
    DWORD INPUT_SAMPLE_RATE; // +0x1C
    DWORD INPUT_BITS; // +0x20
    DWORD INPUT_CHANNELS; // +0x24
    DWORD OUTPUT_BIT_RATE; // +0x28
    DWORD OUTPUT_SAMPLE_RATE; // +0x2C
    DWORD OUTPUT_BITS; // +0x30
    DWORD OUTPUT_CHANNELS; // +0x34
    DWORD POSITION; // +0x38
    DWORD PERCENT_DONE; // +0x3C
    DWORD MIN_INPUT_BLOCK_SIZE; // +0x40
    DWORD RAW_RATE; // +0x44
    DWORD RAW_BITS; // +0x48
    DWORD RAW_CHANNELS; // +0x4C
    DWORD REQUESTED_RATE; // +0x50
    DWORD REQUESTED_BITS; // +0x54
    DWORD REQUESTED_CHANS; // +0x58
    long stream; // +0x5C
    // total size: 0x60 (96)

};
