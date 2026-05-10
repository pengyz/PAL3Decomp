#pragma once
// Auto-generated: _D3DLIGHT9

#include "_D3DCOLORVALUE.h"
#include "_D3DLIGHTTYPE.h"
#include "_D3DVECTOR.h"

class _D3DLIGHT9 {
public:
    _D3DLIGHTTYPE Type; // +0x0
    _D3DCOLORVALUE Diffuse; // +0x4
    _D3DCOLORVALUE Specular; // +0x14
    _D3DCOLORVALUE Ambient; // +0x24
    _D3DVECTOR Position; // +0x34
    _D3DVECTOR Direction; // +0x40
    float Range; // +0x4C
    float Falloff; // +0x50
    float Attenuation0; // +0x54
    float Attenuation1; // +0x58
    float Attenuation2; // +0x5C
    float Theta; // +0x60
    float Phi; // +0x64
    // total size: 0x68 (104)

};
