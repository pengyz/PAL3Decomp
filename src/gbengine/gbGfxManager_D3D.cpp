/**
 * gbengine.dll - gbGfxManager_D3D
 * D3D9 graphics manager additional methods
 */

#include "gbengine/gbGfxManager.h"
#include "gbengine/gbTexture.h"
#include <d3d9.h>

void gbGfxManager_D3D::SetTexture(gbTextureArray* texArray) {
    if (!texArray || !m_pd3dDevice) return;

    // Set textures on device
    for (int i = 0; i < 8; i++) {
        IDirect3DTexture9* d3dTex = NULL;

        if (i < texArray->numTextures && texArray->textures[i]) {
            gbTexture* tex = texArray->textures[i];
            // Get D3D texture from gbTexture
            /* UNCERTAIN: gbTexture to IDirect3DTexture9 conversion */
            // d3dTex = tex->GetD3DTexture();
        }

        m_pd3dDevice->SetTexture(i, d3dTex);
        m_pCurTexture[i] = (i < texArray->numTextures) ? texArray->textures[i] : NULL;
    }
}
