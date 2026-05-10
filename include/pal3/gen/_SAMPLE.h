#pragma once
// Auto-generated: _SAMPLE

#include "DPINFO.h"
#include "_ADPCMDATATAG.h"

class _DIG_DRIVER;

class _SAMPLE {
public:
    char tag[4]; // +0x0
    _DIG_DRIVER * driver; // +0x4
    DWORD status; // +0x8
    void * start[2]; // +0xC
    DWORD len[2]; // +0x14
    DWORD pos[2]; // +0x1C
    DWORD done[2]; // +0x24
    long reset_ASI[2]; // +0x2C
    DWORD src_fract; // +0x34
    long left_val; // +0x38
    long right_val; // +0x3C
    long current_buffer; // +0x40
    long last_buffer; // +0x44
    long starved; // +0x48
    long loop_count; // +0x4C
    long loop_start; // +0x50
    long loop_end; // +0x54
    long format; // +0x58
    DWORD flags; // +0x5C
    long playback_rate; // +0x60
    long volume; // +0x64
    long pan; // +0x68
    long left_scale; // +0x6C
    long right_scale; // +0x70
    long service_type; // +0x74
    void * * SOB; // +0x78
    void * * EOB; // +0x7C
    void * * EOS; // +0x80
    long user_data[8]; // +0x84
    long system_data[8]; // +0xA4
    _ADPCMDATATAG adpcm; // +0xC4
    long SOB_IsWin32s; // +0x10C
    long EOB_IsWin32s; // +0x110
    long EOS_IsWin32s; // +0x114
    long secondary_buffer; // +0x118
    long service_interval; // +0x11C
    long service_tick; // +0x120
    long buffer_segment_size; // +0x124
    long prev_segment; // +0x128
    long prev_cursor; // +0x12C
    long bytes_remaining; // +0x130
    long direct_control; // +0x134
    long doeob; // +0x138
    long dosob; // +0x13C
    long doeos; // +0x140
    DPINFO pipeline[3]; // +0x144
    float reverb_level; // +0x27C
    float reverb_reflect_time; // +0x280
    float reverb_decay_time; // +0x284
    long base_scale; // +0x288
    // total size: 0x28C (652)

};
