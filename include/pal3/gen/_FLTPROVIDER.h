#pragma once
// Auto-generated: _FLTPROVIDER

class _DIG_DRIVER;

class _FLTPROVIDER {
public:
    void * * PROVIDER_query_attribute; // +0x0
    void * * startup; // +0x4
    void * * error; // +0x8
    void * * shutdown; // +0xC
    void * * set_provider_preference; // +0x10
    void * * open_driver; // +0x14
    void * * close_driver; // +0x18
    void * * premix_process; // +0x1C
    void * * postmix_process; // +0x20
    void * * open_sample; // +0x24
    void * * close_sample; // +0x28
    void * * sample_process; // +0x2C
    void * * sample_attribute; // +0x30
    void * * set_sample_preference; // +0x34
    _DIG_DRIVER * dig; // +0x38
    unsigned long provider; // +0x3C
    long driver_state; // +0x40
    _FLTPROVIDER * next; // +0x44
    // total size: 0x48 (72)

};
