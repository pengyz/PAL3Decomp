#pragma once
// Auto-generated: UnderWater

class IDirect3DIndexBuffer9;
class IDirect3DTexture9;
class IDirect3DVertexBuffer9;

class UnderWater {
public:
    unsigned char m_bEnable; // +0x0
    IDirect3DIndexBuffer9 * m_pIB; // +0x4
    IDirect3DVertexBuffer9 * m_pVB; // +0x8
    IDirect3DTexture9 * m_pBumpmapTex; // +0xC
    int m_iMode; // +0x10
    float m_fTime; // +0x14
    // total size: 0x18 (24)

};
