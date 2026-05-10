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
    unsigned long INPUT_BIT_RATE; // +0x18
    unsigned long INPUT_SAMPLE_RATE; // +0x1C
    unsigned long INPUT_BITS; // +0x20
    unsigned long INPUT_CHANNELS; // +0x24
    unsigned long OUTPUT_BIT_RATE; // +0x28
    unsigned long OUTPUT_SAMPLE_RATE; // +0x2C
    unsigned long OUTPUT_BITS; // +0x30
    unsigned long OUTPUT_CHANNELS; // +0x34
    unsigned long POSITION; // +0x38
    unsigned long PERCENT_DONE; // +0x3C
    unsigned long MIN_INPUT_BLOCK_SIZE; // +0x40
    unsigned long RAW_RATE; // +0x44
    unsigned long RAW_BITS; // +0x48
    unsigned long RAW_CHANNELS; // +0x4C
    unsigned long REQUESTED_RATE; // +0x50
    unsigned long REQUESTED_BITS; // +0x54
    unsigned long REQUESTED_CHANS; // +0x58
    long stream; // +0x5C
    // total size: 0x60 (96)

};
