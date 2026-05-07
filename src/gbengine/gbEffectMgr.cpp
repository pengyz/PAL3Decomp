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
    return m_pDefaultEffect;
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
        if (effect->m_dwFlags == flags)
            return effect;
    }
    return NULL;
}

int gbEffectMgr::OnLostDevice(void) {
    for (int i = 0; i < m_nNumEffects; i++) {
        gbRenderEffect* effect = m_pEffects[i];
        if (effect)
            effect->m_pEffect->OnLostDevice();
    }
    return 1;
}

int gbEffectMgr::OnResetDevice(void) {
    for (int i = 0; i < m_nNumEffects; i++) {
        gbRenderEffect* effect = m_pEffects[i];
        if (effect)
            effect->m_pEffect->OnResetDevice();
    }
    return 1;
}

IDirect3DVertexDeclaration9* gbEffectMgr::RegisterVertexFormat(const char* name, gbVertexElement* pElements) {
    for (int i = 0; i < m_nNumVertFormats; i++) {
        if (strcmp(m_vertFormats[i].name, name) == 0) {
            return m_vertFormats[i].pDecl;
        }
    }

    IDirect3DDevice9* pDevice = ((gbGfxManager_D3D*)m_pGfxMgr)->m_pd3dDevice;
    IDirect3DVertexDeclaration9* pDecl = NULL;
    HRESULT hr = pDevice->CreateVertexDeclaration((D3DVERTEXELEMENT9*)pElements, &pDecl);
    if (FAILED(hr))
        return NULL;

    m_vertFormats[m_nNumVertFormats].pDecl = pDecl;
    strcpy(m_vertFormats[m_nNumVertFormats].name, name);
    m_nNumVertFormats++;
    return pDecl;
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

