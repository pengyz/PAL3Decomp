#pragma once
// Auto-generated: ASISTAGE

class ASISTAGE {
public:
    char * ASI_stream_open; // +0x0
    char * ASI_stream_process; // +0x4
    char * ASI_stream_seek; // +0x8
    char * ASI_stream_close; // +0xC
    char * ASI_stream_attribute; // +0x10
    char * ASI_stream_set_preference; // +0x14
    UINT INPUT_BIT_RATE; // +0x18
    UINT INPUT_SAMPLE_RATE; // +0x1C
    UINT INPUT_BITS; // +0x20
    UINT INPUT_CHANNELS; // +0x24
    UINT OUTPUT_BIT_RATE; // +0x28
    UINT OUTPUT_SAMPLE_RATE; // +0x2C
    UINT OUTPUT_BITS; // +0x30
    UINT OUTPUT_CHANNELS; // +0x34
    UINT POSITION; // +0x38
    UINT PERCENT_DONE; // +0x3C
    UINT MIN_INPUT_BLOCK_SIZE; // +0x40
    UINT RAW_RATE; // +0x44
    UINT RAW_BITS; // +0x48
    UINT RAW_CHANNELS; // +0x4C
    UINT REQUESTED_RATE; // +0x50
    UINT REQUESTED_BITS; // +0x54
    UINT REQUESTED_CHANS; // +0x58
    int stream; // +0x5C
    // total size: 0x60 (96)

};
