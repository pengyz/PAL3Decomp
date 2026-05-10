#pragma once
// Auto-generated: sg_particle_data

class D3DXCOLOR;
class D3DXVECTOR3;

class sg_particle_data {
public:
    int alive; // +0x0
    float elapsetime; // +0x4
    float lifetime; // +0x8
    float tval; // +0xC
    int looptex; // +0x10
    int chainindex; // +0x14
    D3DXVECTOR3 velocity; // +0x18
    D3DXVECTOR3 resistance; // +0x24
    D3DXVECTOR3 curpos; // +0x30
    float cursize; // +0x3C
    float curvertexalpha; // +0x40
    D3DXCOLOR currgbcolor; // +0x44
    float rotation; // +0x54
    int dir; // +0x58
    // total size: 0x5C (92)

};
