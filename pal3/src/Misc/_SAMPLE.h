#pragma once
// Auto-generated: _SAMPLE

#include "DPINFO.h"
#include "_ADPCMDATATAG.h"

class _DIG_DRIVER;

class _SAMPLE {
public:
    char tag[4]; // +0x0
    _DIG_DRIVER * driver; // +0x4
    UINT status; // +0x8
    char * start[2]; // +0xC
    char _gap_010[4]; // +0x10
    UINT len[2]; // +0x14
    UINT pos[2]; // +0x1C
    UINT done[2]; // +0x24
    int reset_ASI[2]; // +0x2C
    UINT src_fract; // +0x34
    int left_val; // +0x38
    int right_val; // +0x3C
    int current_buffer; // +0x40
    int last_buffer; // +0x44
    int starved; // +0x48
    int loop_count; // +0x4C
    int loop_start; // +0x50
    int loop_end; // +0x54
    int format; // +0x58
    UINT flags; // +0x5C
    int playback_rate; // +0x60
    int volume; // +0x64
    int pan; // +0x68
    int left_scale; // +0x6C
    int right_scale; // +0x70
    int service_type; // +0x74
    char * SOB; // +0x78
    char * EOB; // +0x7C
    char * EOS; // +0x80
    int user_data[8]; // +0x84
    int system_data[8]; // +0xA4
    _ADPCMDATATAG adpcm; // +0xC4
    char _gap_0C8[68]; // +0xC8
    int SOB_IsWin32s; // +0x10C
    int EOB_IsWin32s; // +0x110
    int EOS_IsWin32s; // +0x114
    int secondary_buffer; // +0x118
    int service_interval; // +0x11C
    int service_tick; // +0x120
    int buffer_segment_size; // +0x124
    int prev_segment; // +0x128
    int prev_cursor; // +0x12C
    int bytes_remaining; // +0x130
    int direct_control; // +0x134
    int doeob; // +0x138
    int dosob; // +0x13C
    int doeos; // +0x140
    DPINFO pipeline[3]; // +0x144
    char _gap_150[300]; // +0x150
    float reverb_level; // +0x27C
    float reverb_reflect_time; // +0x280
    float reverb_decay_time; // +0x284
    int base_scale; // +0x288
    // total size: 0x28C (652)

};
