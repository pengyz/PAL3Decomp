#pragma once
// Auto-generated: C2DSpark

class gbTextureArray;

class C2DSpark {
public:
    char m_Spark[24576]; // +0x0 (C2DSpark::tagSpark[512])
    float m_fDisplayWidth; // +0x6000
    float m_fDisplayHeight; // +0x6004
    int m_nCurrentSpark; // +0x6008
    float m_fBigLum; // +0x600C
    int m_nBigLumX; // +0x6010
    int m_nBigLumY; // +0x6014
    unsigned char m_bMouseTrack; // +0x6018
    gbRenderEffect * m_pAdditiveBlend; // +0x601C
    gbTexture * m_pRedBig; // +0x6020
    gbTextureArray * m_pRedBigArray; // +0x6024
    gbTexture * m_pBlue16; // +0x6028
    gbTextureArray * m_pBlue16Array; // +0x602C
    gbTexture * m_pGreen16; // +0x6030
    gbTextureArray * m_pGreen16Array; // +0x6034
    gbTexture * m_pRed16; // +0x6038
    gbTextureArray * m_pRed16Array; // +0x603C
    gbTexture * m_pYellow16; // +0x6040
    gbTextureArray * m_pYellow16Array; // +0x6044
    gbUIQuad m_Quad; // +0x6048
    // total size: 0x6070 (24688)

    char CreateSingle(const void *a2); // 0x004D5EC0
    char CreateTrack(char a2); // 0x004D5F20
    int SetEnableMouseTrack(int a2, int a3); // 0x004D5F40
    char CreateMore(int a2, int a3, int a4, int a5); // 0x004D6050
    _BYTE * CreateStars(); // 0x004D61A0
    int DestroyAll(); // 0x004D61C0
    int Render(float a2); // 0x004D6380
};
