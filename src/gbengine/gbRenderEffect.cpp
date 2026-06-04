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
    m_pEffect = pEffect;
    m_dwFlags = flags;
    m_pDecl = 0;

    int i = 0;
    do {
        m_ParamHandle[i] = pEffect->GetParameterByName(0, s_paramNames[i]);
    } while (++i < 8);
}

gbRenderEffect::gbRenderEffect(const gbRenderEffect& other) : gbResource(other) {
    m_pEffect = other.m_pEffect;
    m_dwFlags = other.m_dwFlags;
    m_pDecl = other.m_pDecl;
    memcpy(m_ParamHandle, other.m_ParamHandle, 0x20);
}

gbRenderEffect::~gbRenderEffect() {
    m_pEffect->Release();
}

gbRenderEffect& gbRenderEffect::operator=(const gbRenderEffect& other) {
    refCount = other.refCount;
    name = other.name;
    nameCrc = other.nameCrc;
    isLoaded = other.isLoaded;
    manager = other.manager;
    m_pEffect = other.m_pEffect;
    m_dwFlags = other.m_dwFlags;
    m_pDecl = other.m_pDecl;
    for (int i = 0; i < 8; i++) {
        m_ParamHandle[i] = other.m_ParamHandle[i];
    }
    return *this;
}

void gbRenderEffect::SetDeclHandle(IDirect3DVertexDeclaration9* decl) {
    m_pDecl = decl;
}

int gbRenderEffect::Compare(gbRenderEffect* other) {
    unsigned int a = (unsigned int)m_pEffect;
    unsigned int b = (unsigned int)other->m_pEffect;
    if (a < b) return -1;
    return a != b;
}

int gbRenderEffect::Validate(void) {
    D3DXHANDLE hTechnique = NULL;
    D3DXHANDLE h;
    int hr;
    hr = m_pEffect->FindNextValidTechnique(NULL, &hTechnique);
    while (hr >= 0) {
        h = hTechnique;
        if (hTechnique) {
            if (m_pEffect->ValidateTechnique(hTechnique) >= 0) {
                m_pEffect->SetTechnique(hTechnique);
                return 1;
            }
            h = hTechnique;
        }
        hr = m_pEffect->FindNextValidTechnique(h, &hTechnique);
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
    m_pEffect->Begin(&numPasses, D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESHADERSTATE);
    for (unsigned int i = 0; i < numPasses; i++) {
        m_pEffect->Pass(i);
    }
    m_pEffect->End();
}

void gbRenderEffect::GetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    m_pEffect->GetValue(m_ParamHandle[handle], pValue, (UINT)-1);
}

void gbRenderEffect::SetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    m_pEffect->SetValue(m_ParamHandle[handle], pValue, (UINT)-1);
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
