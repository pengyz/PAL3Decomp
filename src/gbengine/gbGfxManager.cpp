/**
 * gbengine.dll - gbGfxManager, gbRenderEffect, gbEffectMgr
 *
 * Functional decompilation of graphics management and effect classes.
 * Based on PAL3patch struct definitions and Ghidra export analysis.
 *
 * Compiler: MSVC 6.0 SP5
 * Graphics: DirectX 9 (Summer 2003 SDK)
 */

#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable: 4234)

// Forward declarations for types used only in implementations
class gbTexture;
class gbTexture_D3D;
struct gbTextureArray;
class gbImage2D;
class gbStaticMesh;
class gbResource;
class gbVFileSystem;
class gbVFile;
class gbVertexPool;
class gbDynVertBuf;
class gbVisNode;
class gbGeomNode;
class gbRefObject;

struct gbVertexElement;

// Global definition
gbGfxManager* g_pGfxManager = NULL;


// ============================================================================
// gbGfxManager method implementations
// ============================================================================

// 0x1001d910 (394B) - Constructor
gbGfxManager::gbGfxManager(int& result, gbGfxDriverInfo* driverInfo) {
    /* STUB */
    m_nState = 0;
    hGfxWnd = 0;

    if (driverInfo) {
        memcpy(&DrvInfo, driverInfo, sizeof(gbGfxDriverInfo));
    } else {
        memset(&DrvInfo, 0, sizeof(gbGfxDriverInfo));
    }

    pVertPoolMgr = NULL;
    pEffectMgr = NULL;
    pTexResMgr = NULL;
    pFontMgr = NULL;
    pSceneGraph = NULL;

    memset(pMatrixStack, 0, sizeof(pMatrixStack));

    AmbientLight.r = 0.2f;
    AmbientLight.g = 0.2f;
    AmbientLight.b = 0.2f;
    AmbientLight.a = 1.0f;

    fSelfIllum = 0.0f;

    LastTime = 0.0;
    CurTime = 0.0;
    LastTick = 0;
    CurTick = 0;

    CurZBias = 0;
    bWireMode = 0;

    result = 1; // success
}

gbGfxManager::~gbGfxManager() {
    /* STUB */
    // Cleanup is handled by derived class (gbGfxManager_D3D)
}

// 0x1001db10 (222B) - Begin a rendering scene
int gbGfxManager::BeginScene(void) {
    /* STUB */
    if (m_nState)
        return 0;

    m_nState = 1;
    return 1;
}

// EndScene: finish the rendering scene
void gbGfxManager::EndScene(void) {
    /* STUB */
    if (!m_nState)
        return;

    m_nState = 0;
}

// SetTransform: set a transform matrix (world/view/projection)
void gbGfxManager::SetTransform(int type, gbMatrix4* matrix) {
    /* STUB */
    if (!matrix)
        return;

    switch (type) {
    case GB_TM_WORLD:
        memcpy(&WorldMatrix, matrix, sizeof(gbMatrix4));
        break;
    case GB_TM_VIEW:
        memcpy(&ViewMatrix, matrix, sizeof(gbMatrix4));
        break;
    case GB_TM_PROJECTION:
        memcpy(&InvViewMatrix, matrix, sizeof(gbMatrix4));
        break;
    }
}

// 0x1001e220 (158B) - Clip a bounding volume against the view frustum
// Returns: 1 = outside frustum (clipped), 0 = inside (visible)
int gbGfxManager::ClipBoundVolume(gbAABBox* box) {
    /* STUB */
    float planes[24];
    float* pBox = (float*)box;

    // Get frustum planes from camera via virtual call (vtable offset 0x40 = slot 16)
    // This retrieves 6 planes, each with (nx, ny, nz, d) = 24 floats
    typedef void (__thiscall *GetFrustumPlanesFn)(void*, float*, int);
    void** vtable = *(void***)this;
    GetFrustumPlanesFn getFrustumPlanes = (GetFrustumPlanesFn)vtable[16];
    getFrustumPlanes(this, planes, 0);

    for (int i = 0; i < 6; i++) {
        float nx = planes[i * 4 + 0];
        float ny = planes[i * 4 + 1];
        float nz = planes[i * 4 + 2];
        float d  = planes[i * 4 + 3];

        float px = (nx <= 0.0f) ? pBox[0] : pBox[3];
        float py = (ny <= 0.0f) ? pBox[1] : pBox[4];
        float pz = (nz <= 0.0f) ? pBox[2] : pBox[5];

        if (px * nx + py * ny + pz * nz + d < 0.0f) {
            return 1;
        }
    }
    return 0;
}

// 0x10004ff0 (34B) - Enable/disable emissive lighting
void gbGfxManager::EnableEmissive(int enable) {
    /* STUB */
    if (enable) {
        fSelfIllum = 1.0f;
    } else {
        fSelfIllum = 0.0f;
    }
}

// 0x10005020 (13B) - Set emissive factor
void gbGfxManager::SetEmissiveFactor(float factor) {
    /* STUB */
    fSelfIllum = factor;
}

// 0x10004fc0 (39B) - Get ambient light color
gbColorFlt gbGfxManager::GetAmbientLight(void) {
    /* STUB */
    return AmbientLight;
}

// 0x10004f90 (35B) - Set ambient light color
void gbGfxManager::SetAmbientLight(const gbColorFlt& color) {
    /* STUB */
    AmbientLight = color;
}

// 0x1001dac0 (34B) - Get delta time since last frame
double gbGfxManager::GetDeltaTime(void) {
    /* STUB */
    double dt = CurTime - LastTime;
    if (dt > 0.5) dt = 0.5;
    return dt;
}

// 0x1001daf0 (27B) - Get delta tick since last frame
unsigned int gbGfxManager::GetDeltaTick(void) {
    /* STUB */
    return CurTick - LastTick;
}

// 0x10004ea0 (13B) - Set scene graph
void gbGfxManager::SetSceneGraph(gbSceneGraph* sg) {
    /* STUB */
    pSceneGraph = sg;
}

// 0x10004ed0 (14B) - Get matrix stack by index
gbMatrixStack* gbGfxManager::GetMatrixStack(int index) {
    /* STUB */
    if (index < 0 || index >= 4)
        return NULL;
    return pMatrixStack[index];
}

// 0x10004ee0 (16B) - Get print font by type
gbPrintFont* gbGfxManager::GetPrintFont(gbFontType fontType) {
    /* STUB */
    return ((gbPrintFont**)pFontMgr)[fontType];
}

// 0x10004f50 (20B) - Get light object by index
const gbLight* gbGfxManager::GetLight(int index) const {
    /* STUB */
    return &AllLight[index];
}

// 0x10004f70 (14B) - Check if a light is enabled
int gbGfxManager::IsLightEnable(int index) const {
    /* STUB */
    return LightEnable[index];
}

// 0x1001df40 (37B) - Get a combined transform matrix
void gbGfxManager::GetTMMatrix(int type, gbMatrix4* out) {
    /* STUB */
    if (!out)
        return;
    switch (type) {
    case GB_TM_WORLD:
        memcpy(out, &WorldMatrix, sizeof(gbMatrix4));
        break;
    case GB_TM_VIEW:
        memcpy(out, &ViewMatrix, sizeof(gbMatrix4));
        break;
    case GB_TM_PROJECTION:
        memcpy(out, &InvViewMatrix, sizeof(gbMatrix4));
        break;
    }
}

// 0x1001e070 (24B) - Get current viewport
void gbGfxManager::GetViewport(gbViewPort& pViewport) {
    /* STUB */
    memcpy(&pViewport, &Viewport, sizeof(gbViewPort));
}

// 0x1001e090 (35B) - Set clear parameters (color, depth, stencil)
void gbGfxManager::SetClearParam(gbClearParam* pParam) {
    /* STUB */
    memcpy(&ClearParam, pParam, sizeof(gbClearParam));
}

// 0x1001e160 (189B) - Create a new mesh resource
gbBaseMesh* gbGfxManager::NewMesh(const char* name, gbMeshType type) {
    /* STUB */
    if (type == MESH_STATIC) {
        gbStaticMesh* mesh = new gbStaticMesh(this);
        return mesh;
    } else if (type == MESH_SKINNED) {
        gbStaticMesh* mesh = new gbStaticMesh(this);
        return mesh;
    }
    return NULL;
}

// 0x1001e2c0 (36B) - Offset Z-buffer for decal rendering
void gbGfxManager::OffsetZBuffer(int enable) {
    /* STUB */
    if (enable != CurZBias) {
        CurZBias = enable;
    }
}

// 0x1001e2f0 (13B) - Set wireframe rendering mode
void gbGfxManager::SetWireMode(int mode) {
    /* STUB */
    bWireMode = mode;
}

// 0x1001e300 (38B) - Set fog parameters
void gbGfxManager::SetFog(gbFogParam* pFogParam) {
    /* STUB */
    if (pFogParam == NULL) {
        FogParam.enable = 0;
        return;
    }
    memcpy(&FogParam, pFogParam, sizeof(gbFogParam));
}

// 0x1001e330 (55B) - Get world matrix (const reference)
const gbMatrix4& gbGfxManager::GetWorldMatrix(void) {
    /* STUB */
    return WorldMatrix;
}

// Exported: GetViewMatrix
const gbMatrix4& gbGfxManager::GetViewMatrix(void) {
    /* STUB */
    return ViewMatrix;
}

// 0x1001e380 (19B) - Reset world matrix to identity
void gbGfxManager::IdentityWorldMatrix(void) {
    /* STUB */
    memset(&WorldMatrix, 0, sizeof(gbMatrix4));
    WorldMatrix.m[0][0] = 1.0f;
    WorldMatrix.m[1][1] = 1.0f;
    WorldMatrix.m[2][2] = 1.0f;
    WorldMatrix.m[3][3] = 1.0f;
}

// 0x1001e3a0 (43B) - Set view and projection matrices from camera
void gbGfxManager::SetCameraMatrix(const gbMatrix4& view, const gbMatrix4& proj) {
    /* STUB */
    memcpy(&ViewMatrix, &view, sizeof(gbMatrix4));
    memcpy(&InvViewMatrix, &proj, sizeof(gbMatrix4));
}

// Exported: GetGfxCaps
int gbGfxManager::GetGfxCaps(gbGfxCaps* caps) {
    /* STUB */
    if (!caps) return 0;
    memset(caps, 0, sizeof(gbGfxCaps));
    return 1;
}

// Exported: GetCurTick
unsigned int gbGfxManager::GetCurTick(void) {
    /* STUB */
    return CurTick;
}

// Exported: GetCurTime
double gbGfxManager::GetCurTime(void) {
    /* STUB */
    return CurTime;
}

// Exported: GetDriverInfo
const gbGfxDriverInfo* gbGfxManager::GetDriverInfo(void) {
    /* STUB */
    return &DrvInfo;
}

// Exported: GetEffectMgr
gbEffectMgr* gbGfxManager::GetEffectMgr(void) {
    /* STUB */
    return pEffectMgr;
}

// Exported: GetEmissiveFactor
float gbGfxManager::GetEmissiveFactor(void) {
    /* STUB */
    return fSelfIllum;
}

// Exported: GetFog
gbFogParam* gbGfxManager::GetFog(void) {
    /* STUB */
    return &FogParam;
}

// Exported: GetGraphWnd
unsigned int gbGfxManager::GetGraphWnd(void) {
    /* STUB */
    return DrvInfo.hgfxwnd;
}

// Exported: GetPrintFontMgr
gbPrintFontMgr* gbGfxManager::GetPrintFontMgr(void) {
    /* STUB */
    return pFontMgr;
}

// Exported: GetResManager
gbResManager* gbGfxManager::GetResManager(void) {
    /* STUB */
    return pTexResMgr;
}

// Exported: GetSceneGraph
gbSceneGraph* gbGfxManager::GetSceneGraph(void) {
    /* STUB */
    return pSceneGraph;
}

// Exported: GetStatistic
gbGfxStatistic* gbGfxManager::GetStatistic(void) {
    /* STUB */
    return &Stat;
}

// Exported: GetVertPoolMgr
gbVertPoolMgr* gbGfxManager::GetVertPoolMgr(void) {
    /* STUB */
    return pVertPoolMgr;
}

// Exported: IsWireMode
int gbGfxManager::IsWireMode(void) {
    /* STUB */
    return bWireMode;
}


gbRenderEffect::~gbRenderEffect() {
    /* STUB */
    if (m_pEffect) {
        m_pEffect->Release();
        m_pEffect = NULL;
    }
    m_pDecl = NULL;
}

// operator=
gbRenderEffect& gbRenderEffect::operator=(const gbRenderEffect& other) {
    /* STUB */
    if (this != &other) {
        // Release old effect
        if (m_pEffect) {
            m_pEffect->Release();
        }

        m_pEffect = other.m_pEffect;
        m_dwFlags = other.m_dwFlags;
        m_nPasses = other.m_nPasses;
        m_pDecl = other.m_pDecl;
        m_nTechnique = other.m_nTechnique;

        if (m_pEffect) {
            m_pEffect->AddRef();
        }
    }
    return *this;
}

// 0x10004be0 (10B) - Set vertex declaration handle
void gbRenderEffect::SetDeclHandle(IDirect3DVertexDeclaration9* decl) {
    /* STUB */
    m_pDecl = (D3DVERTEXELEMENT9*)decl;
}

// 0x1001cfe0 (32B) - Compare two effects for sorting
int gbRenderEffect::Compare(gbRenderEffect* other) {
    /* STUB */
    if (!other)
        return 1;
    if (m_pEffect == other->m_pEffect)
        return 0;
    if (m_pEffect < other->m_pEffect)
        return -1;
    return 1;
}

// 0x1001d000 (119B) - Validate the effect
int gbRenderEffect::Validate(void) {
    /* STUB */
    if (!m_pEffect)
        return 0;

    HRESULT hr = m_pEffect->ValidateTechnique(NULL);
    return SUCCEEDED(hr) ? 1 : 0;
}

// 0x1001d080 (26B) - Begin rendering with this effect
int gbRenderEffect::Begin(void) {
    /* STUB */
    if (!m_pEffect)
        return 0;

    UINT numPasses = 0;
    HRESULT hr = m_pEffect->Begin(&numPasses, 0);
    if (FAILED(hr))
        return 0;

    m_nPasses = numPasses;
    return (int)numPasses;
}

// 0x1001d0a0 (52B) - Set a pass
void gbRenderEffect::Pass(int passIndex) {
    /* STUB */
    if (!m_pEffect)
        return;
    m_pEffect->Pass(passIndex);
}

// 0x1001d0e0 (20B) - End rendering with this effect
void gbRenderEffect::End(void) {
    /* STUB */
    if (!m_pEffect)
        return;
    m_pEffect->End();
}

// 0x1001d100 (72B) - Apply current effect state (commit changes)
void gbRenderEffect::Apply(void) {
    /* STUB */
    if (!m_pEffect)
        return;
    // Summer 2003 SDK has no CommitChanges
}

// Get variant by GBPARAMHANDLE
void gbRenderEffect::GetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    /* STUB */
    if (!m_pEffect || !pValue)
        return;
    m_pEffect->GetValue((D3DXHANDLE)(int)handle, pValue, sizeof(float) * 4);
}

// Set variant by GBPARAMHANDLE
void gbRenderEffect::SetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    /* STUB */
    if (!m_pEffect || !pValue)
        return;
    m_pEffect->SetValue((D3DXHANDLE)(int)handle, pValue, sizeof(float) * 4);
}

// 0x1001d190 (40B) - Get variant by name
void gbRenderEffect::GetVariant(char* name, void* pValue) {
    /* STUB */
    if (!m_pEffect || !name || !pValue)
        return;
    D3DXHANDLE hParam = m_pEffect->GetParameterByName(NULL, name);
    if (hParam)
        m_pEffect->GetValue(hParam, pValue, sizeof(float) * 4);
}

// 0x1001d1c0 (40B) - Set variant by name
void gbRenderEffect::SetVariant(char* name, void* pValue) {
    /* STUB */
    if (!m_pEffect || !name || !pValue)
        return;
    D3DXHANDLE hParam = m_pEffect->GetParameterByName(NULL, name);
    if (hParam)
        m_pEffect->SetValue(hParam, pValue, sizeof(float) * 4);
}

// Exported: GetD3DEffect
ID3DXEffect* gbRenderEffect::GetD3DEffect(void) {
    /* STUB */
    return m_pEffect;
}


// ============================================================================
// gbEffectMgr method implementations
// ============================================================================

// 0x10004d20 (12B) - Default constructor
gbEffectMgr::gbEffectMgr(void) {
    /* STUB */
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

// 0x10004d30 (148B) - Copy constructor
gbEffectMgr::gbEffectMgr(const gbEffectMgr& other) {
    /* STUB */
    m_pGfxMgr = other.m_pGfxMgr;
    m_nMaxEffects = other.m_nMaxEffects;
    m_nNumEffects = other.m_nNumEffects;
    m_nMaxDecls = other.m_nMaxDecls;
    m_nNumDecls = other.m_nNumDecls;
    m_bInitialized = other.m_bInitialized;

    // Copy effect array
    if (other.m_pEffects && m_nMaxEffects > 0) {
        m_pEffects = (gbRenderEffect**)malloc(sizeof(gbRenderEffect*) * m_nMaxEffects);
        memcpy(m_pEffects, other.m_pEffects, sizeof(gbRenderEffect*) * m_nNumEffects);
    } else {
        m_pEffects = NULL;
    }

    // Copy vertex declaration array
    if (other.m_pVertDecls && m_nMaxDecls > 0) {
        m_pVertDecls = (void**)malloc(sizeof(void*) * m_nMaxDecls);
        memcpy(m_pVertDecls, other.m_pVertDecls, sizeof(void*) * m_nNumDecls);
    } else {
        m_pVertDecls = NULL;
    }
}

// Destructor
gbEffectMgr::~gbEffectMgr() {
    /* STUB */
    Release();
}

// operator=
gbEffectMgr& gbEffectMgr::operator=(const gbEffectMgr& other) {
    /* STUB */
    if (this != &other) {
        Release();

        m_pGfxMgr = other.m_pGfxMgr;
        m_nMaxEffects = other.m_nMaxEffects;
        m_nNumEffects = other.m_nNumEffects;
        m_nMaxDecls = other.m_nMaxDecls;
        m_nNumDecls = other.m_nNumDecls;
        m_bInitialized = other.m_bInitialized;

        if (other.m_pEffects && m_nMaxEffects > 0) {
            m_pEffects = (gbRenderEffect**)malloc(sizeof(gbRenderEffect*) * m_nMaxEffects);
            memcpy(m_pEffects, other.m_pEffects, sizeof(gbRenderEffect*) * m_nNumEffects);
        }
        if (other.m_pVertDecls && m_nMaxDecls > 0) {
            m_pVertDecls = (void**)malloc(sizeof(void*) * m_nMaxDecls);
            memcpy(m_pVertDecls, other.m_pVertDecls, sizeof(void*) * m_nNumDecls);
        }
    }
    return *this;
}

// 0x1001d1f0 (786B) - Initialize the effect manager
void gbEffectMgr::Init(gbGfxManager* gfxMgr) {
    /* STUB */
    m_pGfxMgr = gfxMgr;

    // Pre-allocate space for effects
    m_nMaxEffects = 64;
    m_pEffects = (gbRenderEffect**)malloc(sizeof(gbRenderEffect*) * m_nMaxEffects);
    memset(m_pEffects, 0, sizeof(gbRenderEffect*) * m_nMaxEffects);
    m_nNumEffects = 0;

    // Pre-allocate space for vertex declarations
    m_nMaxDecls = 32;
    m_pVertDecls = (void**)malloc(sizeof(void*) * m_nMaxDecls);
    memset(m_pVertDecls, 0, sizeof(void*) * m_nMaxDecls);
    m_nNumDecls = 0;

    m_bInitialized = 1;
}

// 0x1001d510 (67B) - Release all managed effects
void gbEffectMgr::Release(void) {
    /* STUB */
    if (m_pEffects) {
        for (int i = 0; i < m_nNumEffects; i++) {
            if (m_pEffects[i]) {
                delete m_pEffects[i];
                m_pEffects[i] = NULL;
            }
        }
        free(m_pEffects);
        m_pEffects = NULL;
    }
    m_nNumEffects = 0;
    m_nMaxEffects = 0;

    if (m_pVertDecls) {
        free(m_pVertDecls);
        m_pVertDecls = NULL;
    }
    m_nNumDecls = 0;
    m_nMaxDecls = 0;

    m_bInitialized = 0;
}

// 0x1001d560 (50B) - Handle device lost
int gbEffectMgr::OnLostDevice(void) {
    /* STUB */
    for (int i = 0; i < m_nNumEffects; i++) {
        if (m_pEffects[i] && m_pEffects[i]->m_pEffect) {
            m_pEffects[i]->m_pEffect->OnLostDevice();
        }
    }
    return 1;
}

// 0x1001d5a0 (50B) - Handle device reset
int gbEffectMgr::OnResetDevice(void) {
    /* STUB */
    for (int i = 0; i < m_nNumEffects; i++) {
        if (m_pEffects[i] && m_pEffects[i]->m_pEffect) {
            m_pEffects[i]->m_pEffect->OnResetDevice();
        }
    }
    return 1;
}

// 0x1001d5e0 (232B) - Register a vertex format declaration
IDirect3DVertexDeclaration9* gbEffectMgr::RegisterVertexFormat(const char* name, gbVertexElement* pElements) {
    /* STUB */
    if (!name || !pElements)
        return NULL;

    if (m_nNumDecls >= m_nMaxDecls)
        return NULL;

    // In the real engine, this creates an IDirect3DVertexDeclaration9
    // from the D3DVERTEXELEMENT9 array and stores it
    m_pVertDecls[m_nNumDecls] = pElements;
    m_nNumDecls++;
    return NULL;
}

// 0x1001d6d0 (353B) - Create a new render effect from a .gbf file
gbRenderEffect* gbEffectMgr::NewRenderEffect(const char* filename, unsigned int flags) {
    /* STUB */
    if (!filename || !m_pGfxMgr)
        return NULL;

    if (m_nNumEffects >= m_nMaxEffects)
        return NULL;

    // Get D3D device
    IDirect3DDevice9* pDevice = NULL;
    if (m_pGfxMgr) {
        pDevice = ((gbGfxManager_D3D*)m_pGfxMgr)->m_pd3dDevice;
    }
    if (!pDevice)
        return NULL;

    // Load effect file
    // The real engine opens the file through gbVFileSystem, reads the .gbf data,
    // and calls D3DXCreateEffect.
    ID3DXEffect* pEffect = NULL;
    ID3DXBuffer* pErrors = NULL;

    HRESULT hr = D3DXCreateEffectFromFile(
        pDevice,
        filename,
        NULL,       // defines
        NULL,       // include handler
        0,          // flags
        NULL,       // effect pool
        &pEffect,
        &pErrors
    );

    if (pErrors) {
        pErrors->Release();
    }

    if (FAILED(hr) || !pEffect)
        return NULL;

    gbRenderEffect* effect = new gbRenderEffect(pEffect, (unsigned int)flags);
    pEffect->Release(); // gbRenderEffect AddRef'd in its constructor

    m_pEffects[m_nNumEffects] = effect;
    m_nNumEffects++;

    return effect;
}

// 0x1001d840 (107B) - Create a trivial (fixed-function emulation) effect
gbRenderEffect* gbEffectMgr::NewTrivalEffect(int type) {
    /* STUB */
    if (type == 0) {
        return NewRenderEffect("gfxscript\\ui.gbf", 0);
    }
    if (type == 1) {
        return NewRenderEffect("gfxscript\\font.gbf", 0);
    }
    if (type == 2) {
        return NewRenderEffect("gfxscript\\geom.gbf", 0);
    }
    if (type == 3) {
        return NewRenderEffect("gfxscript\\line.gbf", 0);
    }
    if (type == 4) {
        return NewRenderEffect("gfxscript\\sprite.gbf", 0);
    }
    return NULL;
}

// 0x1001d8b0 (39B) - Get effect by index
gbRenderEffect* gbEffectMgr::GetRenderEffect(unsigned int index) {
    /* STUB */
    if ((int)index >= m_nNumEffects)
        return NULL;
    return m_pEffects[index];
}

// Exported: GetGrayTexture
// Returns cached gray texture from internal field (not yet mapped in header)
gbTexture* gbEffectMgr::GetGrayTexture(void) {
    /* STUB */
    return m_pGrayTexture;
}

// Exported: GetWhiteTexture
// Returns cached white texture from internal field (not yet mapped in header)
gbTexture* gbEffectMgr::GetWhiteTexture(void) {
    /* STUB */
    return m_pWhiteTexture;
}


// ============================================================
// Additional export implementations
// ============================================================

#pragma optimize("", off)
#pragma auto_inline(off)

// gbGfxManager_D3D: full definition in gbGfxManager.h

struct gbImage2DInfo {
    char _stub_data[128];

public:
    struct gbImage2DInfo & operator=(struct gbImage2DInfo const & p0);

public:
    int IsPreferAlpha();

};

