/**
 * gbengine.dll - gbGfxManager_D3D
 * D3D9 graphics manager additional methods
 */

#include "gbengine/gbGfxManager.h"
#include "gbengine/gbTexture.h"
#include <d3d9.h>

void gbGfxManager_D3D::SetTexture(gbTextureArray* texArray) {
    int stage = 0;

    if (!texArray || texArray->numTextures <= 0)
        goto clearRemaining;

    do {
        gbTexture* tex = texArray->pTex[stage];
        if (tex != m_pCurTexture[stage]) {
            if (tex)
                m_pd3dDevice->SetTexture(stage, (IDirect3DBaseTexture9*)tex->GetTexture());
            else
                m_pd3dDevice->SetTexture(stage, NULL);
            m_pCurTexture[stage] = tex;
        }
        stage++;
    } while (stage < texArray->numTextures);

    if (stage >= 4) return;

clearRemaining:
    do {
        if (m_pCurTexture[stage]) {
            m_pd3dDevice->SetTexture(stage, NULL);
            m_pCurTexture[stage] = NULL;
        }
        stage++;
    } while (stage < 4);
}

gbGfxManager_D3D::gbGfxManager_D3D() {
    memset(&m_d3dEnumeration, 0, sizeof(m_d3dEnumeration));
    m_bWindowed = 1;
    m_hWnd = NULL;
    m_bMinimized = 0;
    m_bMaximized = 0;
    m_bActive = 0;
    m_dwCreateFlags = 0;
    m_pD3D = NULL;
    m_pd3dDevice = NULL;
    m_pBackBuffer = NULL;
    m_pCacheVB = NULL;
    m_pCacheIB = NULL;
    m_bDeviceLost = 0;
    m_ErrorCode = 0;
    m_bShowCursor = 0;
    m_pActiveCursor = NULL;
    m_bSoftVPMode = 0;
}

void gbGfxManager_D3D::Init(gbGfxDriverInfo* info) {
    // Stub - full D3D initialization
}
