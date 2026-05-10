#pragma once
// Auto-generated: gbLight

class gbLight {
public:
    char type[4]; // +0x0 (gbLight::gbLightType)
    gbColorFlt diffuse; // +0x4
    gbColorFlt specular; // +0x14
    gbColorFlt ambient; // +0x24
    gbVec3D position; // +0x34
    gbVec3D direction; // +0x40
    float range; // +0x4C
    float falloff; // +0x50
    float attenuation0; // +0x54
    float attenuation1; // +0x58
    float attenuation2; // +0x5C
    float theta; // +0x60
    float phi; // +0x64
    // total size: 0x68 (104)

};
