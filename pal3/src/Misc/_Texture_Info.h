#pragma once
// Auto-generated: _Texture_Info

#include "_Tex_uv.h"

class _Texture_Info {
public:
    char _tex_name[512]; // +0x0
    char _tex_lib[512]; // +0x200
    UINT _tex_libw; // +0x400
    UINT _tex_libh; // +0x404
    UINT _tex_origin_x; // +0x408
    UINT _tex_origin_y; // +0x40C
    UINT _tex_width; // +0x410
    UINT _tex_height; // +0x414
    _Tex_uv _tex_uvLT; // +0x418
    char _gap_41C[4]; // +0x41C
    _Tex_uv _tex_uvLB; // +0x420
    char _gap_424[4]; // +0x424
    _Tex_uv _tex_uvRB; // +0x428
    char _gap_42C[4]; // +0x42C
    _Tex_uv _tex_uvRT; // +0x430
    char _gap_434[4]; // +0x434
    UINT _tex_mode; // +0x438
    BYTE _tex_valid; // +0x43C
    char _tail_43D[3]; // +0x43D
    // total size: 0x440 (1088)

};
