#pragma once
// Auto-generated: _DIG_DRIVER

#include "DPINFO.h"
#include "pcmwaveformat_tag.h"

class HWAVEOUT__;
class _SAMPLE;
class wavehdr_tag;

class _DIG_DRIVER {
public:
    char tag[4]; // +0x0
    long backgroundtimer; // +0x4
    long quiet; // +0x8
    long n_active_samples; // +0xC
    long master_volume; // +0x10
    long DMA_rate; // +0x14
    long hw_format; // +0x18
    unsigned long hw_mode_flags; // +0x1C
    long channels_per_sample; // +0x20
    long bytes_per_channel; // +0x24
    long channels_per_buffer; // +0x28
    long samples_per_buffer; // +0x2C
    long playing; // +0x30
    _SAMPLE * samples; // +0x34
    long n_samples; // +0x38
    long build_size; // +0x3C
    long * build_buffer; // +0x40
    long system_data[8]; // +0x44
    long buffer_size; // +0x64
    HWAVEOUT__ * hWaveOut; // +0x68
    unsigned long reset_works; // +0x6C
    unsigned long request_reset; // +0x70
    wavehdr_tag * first; // +0x74
    long n_buffers; // +0x78
    wavehdr_tag * * return_list; // +0x7C
    long return_head; // +0x80
    long return_tail; // +0x84
    unsigned long deviceid; // +0x88
    pcmwaveformat_tag wformat; // +0x8C
    unsigned long guid; // +0x9C
    void * pDS; // +0xA0
    unsigned long ds_priority; // +0xA4
    long emulated_ds; // +0xA8
    void * lppdsb; // +0xAC
    unsigned long dsHwnd; // +0xB0
    void * * lpbufflist; // +0xB4
    _SAMPLE * * samp_list; // +0xB8
    long * sec_format; // +0xBC
    long max_buffs; // +0xC0
    long released; // +0xC4
    unsigned long foreground_timer; // +0xC8
    _DIG_DRIVER * next; // +0xCC
    long callingCT; // +0xD0
    long callingDS; // +0xD4
    long DS_initialized; // +0xD8
    void * DS_sec_buff; // +0xDC
    void * DS_out_buff; // +0xE0
    long DS_buffer_size; // +0xE4
    long DS_frag_cnt; // +0xE8
    long DS_frag_size; // +0xEC
    long DS_last_frag; // +0xF0
    long DS_last_write; // +0xF4
    long DS_last_timer; // +0xF8
    long DS_skip_time; // +0xFC
    long DS_use_default_format; // +0x100
    long use_MMX; // +0x104
    void * decode_buffer; // +0x108
    long decode_buffer_size; // +0x10C
    unsigned long us_count; // +0x110
    unsigned long ms_count; // +0x114
    unsigned long last_ms_polled; // +0x118
    unsigned long last_percent; // +0x11C
    DPINFO pipeline[4]; // +0x120
    long * reverb_buffer; // +0x2C0
    long reverb_buffer_size; // +0x2C4
    long reverb_buffer_position; // +0x2C8
    long no_wom_done; // +0x2CC
    unsigned long wom_done_buffers; // +0x2D0
    // total size: 0x2D4 (724)

};
