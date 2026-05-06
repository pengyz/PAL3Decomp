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
