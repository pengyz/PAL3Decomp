#pragma once
// Auto-generated: C2DSpark

#include "C2DSpark_tagSpark.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbMesh.h"

class C2DSpark {
public:
    C2DSpark_tagSpark m_Spark[512]; // +0x0
    char _gap_800[22528]; // +0x800
    float m_fDisplayWidth; // +0x6000
    float m_fDisplayHeight; // +0x6004
    int m_nCurrentSpark; // +0x6008
    float m_fBigLum; // +0x600C
    int m_nBigLumX; // +0x6010
    int m_nBigLumY; // +0x6014
    BYTE m_bMouseTrack; // +0x6018
    char _gap_6019[3]; // +0x6019
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
    char _tail_604C[36]; // +0x604C
    // total size: 0x6070 (24688)

    C2DSpark(int nClientWidth, int nClientHeight); // 0x004D5AB0
    void _C2DSpark(); // 0x004D5DC0
    bool CreateSingle(const void *pSpark); // 0x004D5EC0
    char CreateTrack(char a2, int a3, int a4); // 0x004D5F20
    void SetEnableMouseTrack(int bEnable, int nVal); // 0x004D5F40
    void CreateMore(int x, int y, int color, int nVal); // 0x004D6050
    _BYTE * CreateStars(); // 0x004D61A0
    void DestroyAll(); // 0x004D61C0
    void Render(float fVal); // 0x004D6380
};
