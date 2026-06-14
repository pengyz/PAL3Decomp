#pragma once
// Auto-generated: _FLTPROVIDER

class _DIG_DRIVER;

class _FLTPROVIDER {
public:
    char * PROVIDER_query_attribute; // +0x0
    char * startup; // +0x4
    char * error; // +0x8
    char * shutdown; // +0xC
    char * set_provider_preference; // +0x10
    char * open_driver; // +0x14
    char * close_driver; // +0x18
    char * premix_process; // +0x1C
    char * postmix_process; // +0x20
    char * open_sample; // +0x24
    char * close_sample; // +0x28
    char * sample_process; // +0x2C
    char * sample_attribute; // +0x30
    char * set_sample_preference; // +0x34
    _DIG_DRIVER * dig; // +0x38
    UINT provider; // +0x3C
    int driver_state; // +0x40
    _FLTPROVIDER * next; // +0x44
    // total size: 0x48 (72)

};
