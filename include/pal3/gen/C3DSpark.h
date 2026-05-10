#pragma once
// Auto-generated: C3DSpark

class gbTextureArray;

class C3DSpark {
public:
    char m_Spark[7168]; // +0x0 (C3DSpark::tagSpark[128])
    int m_nCurrentSpark; // +0x1C00
    gbRenderEffect * m_pAdditiveBlend; // +0x1C04
    gbTexture * m_pRedBig; // +0x1C08
    gbTextureArray * m_pRedBigArray; // +0x1C0C
    gbTexture * m_pBlue16; // +0x1C10
    gbTextureArray * m_pBlue16Array; // +0x1C14
    gbTexture * m_pGreen16; // +0x1C18
    gbTextureArray * m_pGreen16Array; // +0x1C1C
    gbTexture * m_pRed16; // +0x1C20
    gbTextureArray * m_pRed16Array; // +0x1C24
    gbTexture * m_pYellow16; // +0x1C28
    gbTextureArray * m_pYellow16Array; // +0x1C2C
    gbGeomQuad m_GeomQuad[128]; // +0x1C30
    // total size: 0x3E30 (15920)

    char CreateSingle(const void *a2); // 0x004D6A60
    char CreateOne(int a2, int a3, int a4); // 0x004D6AC0
    _BYTE * DestroyAll(); // 0x004D6BA0
    // [IDA_USERPURGE] Render; // 0x004D6BC0
    int Update(float a2); // 0x004D6D30
};
