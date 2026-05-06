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
    m_dwFlags = flags;
    m_nPasses = 0;
    m_pDecl = NULL;
    m_nTechnique = 0;

    if (m_pEffect) {
        m_pEffect->AddRef();

        // Get number of passes
        // Note: D3DXTECHNIQUE_DESC requires D3DX9 SDK
        // If compilation fails, ensure DirectX SDK August 2007 or later is installed
        #ifdef D3DX_SDK_VERSION
        D3DXHANDLE hTech = m_pEffect->GetCurrentTechnique();
        if (hTech) {
            D3DXTECHNIQUE_DESC desc;
            if (SUCCEEDED(m_pEffect->GetTechniqueDesc(hTech, &desc))) {
                m_nPasses = desc.Passes;
            }
        }
        #else
        // Fallback if D3DX SDK not available
        m_nPasses = 1;
        #endif
    }
}

gbRenderEffect::~gbRenderEffect(void) {
    if (m_pEffect) {
        m_pEffect->Release();
        m_pEffect = NULL;
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

gbRenderEffect& gbRenderEffect::operator=(const gbRenderEffect& other) {
    if (this != &other) {
        if (m_pEffect) {
            m_pEffect->Release();
        }

        m_pEffect = other.m_pEffect;
        m_nPasses = other.m_nPasses;
        m_dwFlags = other.m_dwFlags;
        m_pDecl = other.m_pDecl;
        m_nTechnique = other.m_nTechnique;

        if (m_pEffect) {
            m_pEffect->AddRef();
        }
    }
    return *this;
}

void gbRenderEffect::SetDeclHandle(IDirect3DVertexDeclaration9* decl) {
    m_pDecl = (D3DVERTEXELEMENT9*)decl;
}

int gbRenderEffect::Compare(gbRenderEffect* other) {
    if (!other) return 1;
    if (m_pEffect < other->m_pEffect) return -1;
    if (m_pEffect > other->m_pEffect) return 1;
    return 0;
}

int gbRenderEffect::Validate(void) {
    if (!m_pEffect) return 0;

    DWORD numPasses = 0;
    HRESULT hr = m_pEffect->ValidateTechnique(m_pEffect->GetCurrentTechnique());
    return SUCCEEDED(hr) ? 1 : 0;
}

int gbRenderEffect::Begin(void) {
    if (!m_pEffect) return 0;

    UINT numPasses = 0;
    HRESULT hr = m_pEffect->Begin(&numPasses, 0);
    if (SUCCEEDED(hr)) {
        m_nPasses = numPasses;
        return (int)numPasses;
    }
    return 0;
}

void gbRenderEffect::Pass(int passIndex) {
    if (!m_pEffect) return;
    m_pEffect->Pass(passIndex);
}

void gbRenderEffect::End(void) {
    if (!m_pEffect) return;
    m_pEffect->End();
}

void gbRenderEffect::Apply(void) {
    if (!m_pEffect) return;
    // Summer 2003 SDK has no CommitChanges; state is applied implicitly per Pass()
}

void gbRenderEffect::GetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    if (!m_pEffect || !pValue) return;

    /* UNCERTAIN: GBPARAMHANDLE to shader parameter mapping */
    // Would map to specific D3DX effect parameters
}

void gbRenderEffect::SetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    if (!m_pEffect || !pValue) return;

    /* UNCERTAIN: GBPARAMHANDLE to shader parameter mapping */
    // Example mappings:
    // GBPARAM_WORLDMATRIX -> "g_WorldMatrix"
    // GBPARAM_VIEWMATRIX -> "g_ViewMatrix"
    // GBPARAM_PROJMATRIX -> "g_ProjMatrix"
}

void gbRenderEffect::GetVariant(char* name, void* pValue) {
    if (!m_pEffect || !name || !pValue) return;

    D3DXHANDLE param = m_pEffect->GetParameterByName(NULL, name);
    if (param) {
        m_pEffect->GetValue(param, pValue, sizeof(void*));
    }
}

void gbRenderEffect::SetVariant(char* name, void* pValue) {
    if (!m_pEffect || !name || !pValue) return;

    D3DXHANDLE param = m_pEffect->GetParameterByName(NULL, name);
    if (param) {
        m_pEffect->SetValue(param, pValue, sizeof(void*));
    }
}

ID3DXEffect* gbRenderEffect::GetD3DEffect(void) {
    return m_pEffect;
}

unsigned int gbRenderEffect::GetFlag(void) {
    return m_dwFlags;
}
