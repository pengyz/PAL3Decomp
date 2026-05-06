/**
 * gbengine.dll - gbRenderEffect
 * D3DX Effect wrapper for shader management
 */

#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbGfxManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>

extern gbGfxManager_D3D* g_pGfxManager_D3D;

static const char* s_paramNames[] = {
    "WorldMatrix",
    "ViewMatrix",
    "ProjMatrix",
    "Texture0",
    "Texture1",
    "FogColor",
    "LightDir",
    "LightAtten"
};

gbRenderEffect::gbRenderEffect(ID3DXEffect* pEffect, unsigned int flags) {
    m_refCount = 1;
    m_resName = NULL;
    m_resPrev = NULL;
    m_resNext = NULL;
    m_pEffect = pEffect;
    m_dwFlags = flags;
    m_pDecl = NULL;

    for (int i = 0; i < 8; i++) {
        m_paramHandles[i] = m_pEffect->GetParameterByName(NULL, s_paramNames[i]);
    }
}

gbRenderEffect::gbRenderEffect(const gbRenderEffect& other) {
    m_refCount = other.m_refCount;
    m_resName = other.m_resName;
    m_resCrc = other.m_resCrc;
    m_resPrev = other.m_resPrev;
    m_resNext = other.m_resNext;
    m_pEffect = other.m_pEffect;
    m_dwFlags = other.m_dwFlags;
    m_pDecl = other.m_pDecl;
    for (int i = 0; i < 8; i++) {
        m_paramHandles[i] = other.m_paramHandles[i];
    }

    if (m_pEffect) {
        m_pEffect->AddRef();
    }
}

gbRenderEffect::~gbRenderEffect() {
    if (m_pEffect) {
        m_pEffect->Release();
    }
}

gbRenderEffect& gbRenderEffect::operator=(const gbRenderEffect& other) {
    m_refCount = other.m_refCount;
    m_resName = other.m_resName;
    m_resCrc = other.m_resCrc;
    m_resPrev = other.m_resPrev;
    m_resNext = other.m_resNext;
    m_pEffect = other.m_pEffect;
    m_dwFlags = other.m_dwFlags;
    m_pDecl = other.m_pDecl;
    for (int i = 0; i < 8; i++) {
        m_paramHandles[i] = other.m_paramHandles[i];
    }
    return *this;
}

void gbRenderEffect::SetDeclHandle(IDirect3DVertexDeclaration9* decl) {
    m_pDecl = decl;
}

int gbRenderEffect::Compare(gbRenderEffect* other) {
    if (m_dwFlags < other->m_dwFlags)
        return -1;
    if (m_dwFlags > other->m_dwFlags)
        return 1;
    return 0;
}

int gbRenderEffect::Validate(void) {
    D3DXHANDLE hTechnique = NULL;
    if (m_pEffect->FindNextValidTechnique(NULL, &hTechnique) < 0)
        return 0;

    while (hTechnique) {
        if (m_pEffect->ValidateTechnique(hTechnique) >= 0) {
            m_pEffect->SetTechnique(hTechnique);
            return 1;
        }
        D3DXHANDLE hNext = hTechnique;
        if (m_pEffect->FindNextValidTechnique(hNext, &hTechnique) < 0)
            return 0;
    }
    return 0;
}

int gbRenderEffect::Begin(void) {
    unsigned int numPasses;
    m_pEffect->Begin(&numPasses, 0);
    return (int)numPasses;
}

void gbRenderEffect::Pass(int passIndex) {
    m_pEffect->Pass(passIndex);
    if (m_pDecl) {
        g_pGfxManager_D3D->m_pd3dDevice->SetVertexDeclaration(m_pDecl);
    }
}

void gbRenderEffect::End(void) {
    m_pDecl = NULL;
    m_pEffect->End();
}

void gbRenderEffect::Apply(void) {
    unsigned int numPasses;
    m_pEffect->Begin(&numPasses, D3DXFX_DONOTSAVESTATE);
    for (unsigned int i = 0; i < numPasses; i++) {
        m_pEffect->Pass(i);
    }
    m_pEffect->End();
}

void gbRenderEffect::GetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    m_pEffect->GetValue(m_paramHandles[handle], pValue, (UINT)-1);
}

void gbRenderEffect::SetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    m_pEffect->SetValue(m_paramHandles[handle], pValue, (UINT)-1);
}

void gbRenderEffect::GetVariant(char* name, void* pValue) {
    D3DXHANDLE h = m_pEffect->GetParameterByName(NULL, name);
    m_pEffect->GetValue(h, pValue, (UINT)-1);
}

void gbRenderEffect::SetVariant(char* name, void* pValue) {
    D3DXHANDLE h = m_pEffect->GetParameterByName(NULL, name);
    m_pEffect->SetValue(h, pValue, (UINT)-1);
}

ID3DXEffect* gbRenderEffect::GetD3DEffect(void) {
    return m_pEffect;
}

unsigned int gbRenderEffect::GetFlag(void) {
    return m_dwFlags;
}
