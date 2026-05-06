/**
 * gbengine.dll - gbRenderEffect
 * D3DX Effect wrapper for shader management
 */

#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbGfxManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>

gbRenderEffect::gbRenderEffect(ID3DXEffect* pEffect, unsigned int flags) {
    m_pEffect = pEffect;
    m_nPasses = 0;
    m_dwFlags = flags;
    m_pDecl = NULL;
    m_nTechnique = 0;

    if (m_pEffect) {
        m_pEffect->AddRef();
    }
}

gbRenderEffect::gbRenderEffect(const gbRenderEffect& other) {
    m_pEffect = other.m_pEffect;
    m_nPasses = other.m_nPasses;
    m_dwFlags = other.m_dwFlags;
    m_pDecl = other.m_pDecl;
    m_nTechnique = other.m_nTechnique;

    if (m_pEffect) {
        m_pEffect->AddRef();
    }
}

unsigned int gbRenderEffect::GetFlag(void) {
    return m_dwFlags;
}
