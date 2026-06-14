#pragma once
// Auto-generated: C3DSpark

#include "C3DSpark_tagSpark.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"

class C3DSpark {
public:
    C3DSpark_tagSpark m_Spark[128]; // +0x0
    char _gap_200[6656]; // +0x200
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
    char _tail_1E30[8192]; // +0x1E30
    // total size: 0x3E30 (15920)

    C3DSpark(); // 0x004D6670
    void _C3DSpark(); // 0x004D6960
    bool CreateSingle(const void *pSpark); // 0x004D6A60
    void CreateOne(int x, int y, int z); // 0x004D6AC0
    _BYTE * DestroyAll(); // 0x004D6BA0
    void Render(struct gbVec3D *a2); // 0x004D6BC0
    void Update(float fDeltaTime); // 0x004D6D30
};
