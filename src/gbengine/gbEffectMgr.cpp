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

gbEffectMgr::gbEffectMgr(void) {
    m_pGfxMgr = NULL;
    m_pWhiteTexture = NULL;
    m_pGrayTexture = NULL;
    m_pEffects = NULL;
    m_nMaxEffects = 0;
    m_nNumEffects = 0;
    m_pVertDecls = NULL;
    m_nMaxDecls = 0;
    m_nNumDecls = 0;
    m_bInitialized = 0;
}

gbEffectMgr::gbEffectMgr(const gbEffectMgr& other) {
    memcpy(this, &other, sizeof(gbEffectMgr));
}

gbEffectMgr::~gbEffectMgr(void) {
    Release();
}

gbEffectMgr& gbEffectMgr::operator=(const gbEffectMgr& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbEffectMgr));
    }
    return *this;
}

void gbEffectMgr::Init(gbGfxManager* gfxMgr) {
    if (!gfxMgr) return;

    m_pGfxMgr = gfxMgr;
    m_nMaxEffects = 128;
    m_nNumEffects = 0;
    m_pEffects = (gbRenderEffect**)malloc(sizeof(gbRenderEffect*) * m_nMaxEffects);
    if (m_pEffects) {
        memset(m_pEffects, 0, sizeof(gbRenderEffect*) * m_nMaxEffects);
    }

    m_nMaxDecls = 32;
    m_nNumDecls = 0;
    m_pVertDecls = (void**)malloc(sizeof(void*) * m_nMaxDecls);
    if (m_pVertDecls) {
        memset(m_pVertDecls, 0, sizeof(void*) * m_nMaxDecls);
    }

    /* UNCERTAIN: White and gray texture creation */
    // Would create 1x1 white and gray textures for default rendering

    m_bInitialized = 1;
}

void gbEffectMgr::Release(void) {
    // Release all effects
    if (m_pEffects) {
        for (int i = 0; i < m_nNumEffects; i++) {
            if (m_pEffects[i]) {
                delete m_pEffects[i];
            }
        }
        free(m_pEffects);
        m_pEffects = NULL;
    }

    // Release vertex declarations
    if (m_pVertDecls) {
        for (int i = 0; i < m_nNumDecls; i++) {
            if (m_pVertDecls[i]) {
                IDirect3DVertexDeclaration9* decl = (IDirect3DVertexDeclaration9*)m_pVertDecls[i];
                decl->Release();
            }
        }
        free(m_pVertDecls);
        m_pVertDecls = NULL;
    }

    m_nNumEffects = 0;
    m_nNumDecls = 0;
    m_bInitialized = 0;
}

int gbEffectMgr::OnLostDevice(void) {
    // Notify all effects that device is lost
    for (int i = 0; i < m_nNumEffects; i++) {
        if (m_pEffects[i]) {
            ID3DXEffect* effect = m_pEffects[i]->GetD3DEffect();
            if (effect) {
                effect->OnLostDevice();
            }
        }
    }
    return 1;
}

int gbEffectMgr::OnResetDevice(void) {
    // Notify all effects that device is reset
    for (int i = 0; i < m_nNumEffects; i++) {
        if (m_pEffects[i]) {
            ID3DXEffect* effect = m_pEffects[i]->GetD3DEffect();
            if (effect) {
                effect->OnResetDevice();
            }
        }
    }
    return 1;
}

IDirect3DVertexDeclaration9* gbEffectMgr::RegisterVertexFormat(const char* name, gbVertexElement* pElements) {
    if (!m_pGfxMgr || !pElements) return NULL;

    /* UNCERTAIN: Vertex declaration creation from gbVertexElement */
    // Would convert gbVertexElement array to D3DVERTEXELEMENT9 array
    // and create IDirect3DVertexDeclaration9

    return NULL;
}

gbRenderEffect* gbEffectMgr::NewRenderEffect(const char* filename, unsigned int flags) {
    if (!filename || !m_pGfxMgr) return NULL;

    /* UNCERTAIN: Effect file loading */
    // Load .gbf file via virtual file system
    gbVFile* file = g_pVFileSys->OpenFile(filename, 0x201);
    if (!file) return NULL;

    long fileSize = g_pVFileSys->GetFileSize(file);
    if (fileSize <= 0) {
        g_pVFileSys->CloseFile(file);
        return NULL;
    }

    char* fileData = (char*)malloc(fileSize);
    if (!fileData) {
        g_pVFileSys->CloseFile(file);
        return NULL;
    }

    g_pVFileSys->Read(fileData, fileSize, file);
    g_pVFileSys->CloseFile(file);

    // Create D3DX effect from compiled bytecode
    ID3DXEffect* d3dEffect = NULL;
    /* UNCERTAIN: D3DXCreateEffect call */

    free(fileData);

    if (!d3dEffect) return NULL;

    // Create gbRenderEffect wrapper
    gbRenderEffect* effect = new gbRenderEffect(d3dEffect, flags);
    d3dEffect->Release(); // effect now owns a ref

    // Add to effect list
    if (m_nNumEffects < m_nMaxEffects) {
        m_pEffects[m_nNumEffects++] = effect;
    }

    return effect;
}

gbRenderEffect* gbEffectMgr::NewTrivalEffect(int type) {
    /* UNCERTAIN: Fixed-function emulation effect */
    // Would create a simple effect for fixed-function rendering
    return NULL;
}

gbRenderEffect* gbEffectMgr::GetRenderEffect(unsigned int index) {
    if (index >= (unsigned int)m_nNumEffects) return NULL;
    return m_pEffects[index];
}

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
