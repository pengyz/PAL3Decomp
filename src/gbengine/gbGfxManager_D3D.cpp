/**
 * gbengine.dll - gbGfxManager_D3D
 * D3D9 graphics manager additional methods
 */

#include "gbengine/gbGfxManager.h"
#include "gbengine/gbTexture.h"
#include <d3d9.h>

void gbGfxManager_D3D::SetTexture(gbTextureArray* texArray) {
    int stage = 0;

    if (!texArray || *((int*)texArray + 16) <= 0)
        goto clearRemaining;

    do {
        gbTexture* tex = ((gbTexture**)texArray)[stage];
        if (tex != m_pCurTexture[stage]) {
            if (tex)
                m_pd3dDevice->SetTexture(stage, (IDirect3DBaseTexture9*)(*((DWORD*)tex + 21)));
            else
                m_pd3dDevice->SetTexture(stage, NULL);
            m_pCurTexture[stage] = tex;
        }
        stage++;
    } while (stage < *((int*)texArray + 16));

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
