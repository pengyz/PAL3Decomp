/**
 * gbengine.dll - gbGfxManager_D3D
 * D3D9 graphics manager additional methods
 */

#include "gbengine/gbGfxManager.h"
#include "gbengine/gbTexture.h"
#include <d3d9.h>

void gbGfxManager_D3D::SetTexture(gbTextureArray* texArray) {
    if (!texArray || !m_pd3dDevice) return;

    // gbTextureArray supports up to 2 textures
    for (int i = 0; i < 2; i++) {
        IDirect3DTexture9* d3dTex = NULL;

        if (texArray->pTex[i]) {
            gbTexture* tex = texArray->pTex[i];
            // Get D3D texture from gbTexture
            /* UNCERTAIN: gbTexture to IDirect3DTexture9 conversion */
            // d3dTex = tex->GetD3DTexture();
        }

        m_pd3dDevice->SetTexture(i, d3dTex);
        m_pCurTexture[i] = texArray->pTex[i];
    }

    // Clear remaining texture stages
    for (int i = 2; i < 8; i++) {
        m_pd3dDevice->SetTexture(i, NULL);
        m_pCurTexture[i] = NULL;
    }
}
