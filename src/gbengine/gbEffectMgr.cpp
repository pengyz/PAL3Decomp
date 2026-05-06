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

