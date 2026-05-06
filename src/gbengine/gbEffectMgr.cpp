/**
 * gbengine.dll - gbEffectMgr
 * Effect manager for shader/render effect management
 */

#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include <stdlib.h>

extern gbVFileSystem* g_pVFileSys;

gbRenderEffect* gbEffectMgr::GetDefaultEffect(void) {
    if (m_nNumEffects > 0) {
        return m_pEffects[0];
    }
    return NULL;
}

gbTexture* gbEffectMgr::GetWhiteTexture(void) {
    return m_pWhiteTexture;
}

gbTexture* gbEffectMgr::GetGrayTexture(void) {
    return m_pGrayTexture;
}

gbRenderEffect* gbEffectMgr::GetRenderEffect(unsigned int flags) {
    for (int i = 0; i < m_nNumEffects; i++) {
        gbRenderEffect* effect = m_pEffects[i];
        if (effect->GetFlag() == flags)
            return effect;
    }
    return NULL;
}

int gbEffectMgr::OnLostDevice(void) {
    for (int i = 0; i < m_nNumEffects; i++) {
        gbRenderEffect* effect = m_pEffects[i];
        if (effect) {
            effect->GetD3DEffect()->OnLostDevice();
        }
    }
    return 1;
}

int gbEffectMgr::OnResetDevice(void) {
    for (int i = 0; i < m_nNumEffects; i++) {
        gbRenderEffect* effect = m_pEffects[i];
        if (effect) {
            effect->GetD3DEffect()->OnResetDevice();
        }
    }
    return 1;
}

IDirect3DVertexDeclaration9* gbEffectMgr::RegisterVertexFormat(const char* name, gbVertexElement* pElements) {
    if (!name || !pElements)
        return NULL;

    if (m_nNumDecls >= m_nMaxDecls)
        return NULL;

    m_pVertDecls[m_nNumDecls] = pElements;
    m_nNumDecls++;
    return NULL;
}

gbRenderEffect* gbEffectMgr::NewRenderEffect(const char* filename, unsigned int flags) {
    if (!filename || !m_pGfxMgr)
        return NULL;

    if (m_nNumEffects >= m_nMaxEffects)
        return NULL;

    IDirect3DDevice9* pDevice = NULL;
    if (m_pGfxMgr) {
        pDevice = ((gbGfxManager_D3D*)m_pGfxMgr)->m_pd3dDevice;
    }
    if (!pDevice)
        return NULL;

    ID3DXEffect* pEffect = NULL;
    ID3DXBuffer* pErrors = NULL;

    HRESULT hr = D3DXCreateEffectFromFile(
        pDevice,
        filename,
        NULL,
        NULL,
        0,
        NULL,
        &pEffect,
        &pErrors
    );

    if (FAILED(hr)) {
        if (pErrors) pErrors->Release();
        return NULL;
    }

    gbRenderEffect* effect = new gbRenderEffect(pEffect, flags);

    m_pEffects[m_nNumEffects] = effect;
    m_nNumEffects++;
    return effect;
}

gbRenderEffect* gbEffectMgr::NewTrivalEffect(int type) {
    if (type == 0) {
        return NewRenderEffect("gfxscript\\ui.gbf", 0);
    }
    if (type == 1) {
        return NewRenderEffect("gfxscript\\font.gbf", 0);
    }
    if (type == 2) {
        return NewRenderEffect("gfxscript\\geom.gbf", 0);
    }
    if (type == 3) {
        return NewRenderEffect("gfxscript\\line.gbf", 0);
    }
    if (type == 4) {
        return NewRenderEffect("gfxscript\\sprite.gbf", 0);
    }
    return NULL;
}

