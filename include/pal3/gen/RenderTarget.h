#pragma once
// Auto-generated: RenderTarget

class RenderTarget {
public:
    int m_iMode; // +0x0
    gbTexture_D3D m_Texture; // +0x4
    gbTexture_D3D m_ScreenPlane; // +0x64
    int m_nState; // +0xC4
    // total size: 0xC8 (200)

    RenderTarget(); // 0x004BDAC0
    int Create(); // 0x004BDB60
    void OnDeviceLost(int a2); // 0x004BDC10
    bool OnResetDevice(int a2); // 0x004BDC40
    _DWORD * Destroy(); // 0x004BDF10
};
