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
#include "gbengine/gbengine_internal.h"
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

// External declarations
extern double gbUpdateCurTime(void);
extern unsigned int g_CurrentTick;

// Global definition
gbGfxManager* g_pGfxManager = NULL;
gbGfxManager_D3D* g_pGfxManager_D3D = NULL;


// ============================================================================
// gbGfxManager method implementations
// ============================================================================

// 0x1001d910 (394B) - Constructor
gbGfxManager::gbGfxManager(int& result, gbGfxDriverInfo* driverInfo) {
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
    g_pGfxManager = NULL;
}

// 0x1001db10 (222B) - Begin a rendering scene
int gbGfxManager::BeginScene(void) {
    LastTime = CurTime;
    LastTick = CurTick;

    double updated = gbUpdateCurTime();
    CurTime = updated;
    double delta = updated - LastTime;
    CurTick = g_CurrentTick;

    unsigned int frame = Stat.Frame + 1;
    Stat.nRFaces = 0;
    Stat.Frame = frame;
    double accum = delta + Stat.TimeAccum;
    Stat.nRVerts = 0;
    Stat.nTexSwitch = 0;
    if (accum >= 1.0) {
        __int64 frameDiff = (unsigned int)(frame - Stat.PrevFrame);
        Stat.TimeAccum = 0.0;
        Stat.PrevFrame = frame;
        Stat.FPS = (float)((double)frameDiff / accum);
    } else {
        Stat.TimeAccum = accum;
    }

    gbRenderEffect* pEffect = *(gbRenderEffect**)((char*)pEffectMgr + 0x18);
    pEffect->Apply();
    *(int*)((char*)pEffectMgr + 0x824) = 0;
    return 1;
}

// EndScene: finish the rendering scene
void gbGfxManager::EndScene(void) {
    if (!m_nState)
        return;

    m_nState = 0;
}

// SetTransform: set a transform matrix (world/view/projection)
void gbGfxManager::SetTransform(int type, gbMatrix4* matrix) {
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
    if (enable) {
        fSelfIllum = 1.0f;
    } else {
        fSelfIllum = 0.0f;
    }
}

// 0x10005020 (13B) - Set emissive factor
void gbGfxManager::SetEmissiveFactor(float factor) {
    fSelfIllum = factor;
}

// 0x10004fc0 (39B) - Get ambient light color
gbColorFlt gbGfxManager::GetAmbientLight(void) {
    return AmbientLight;
}

// 0x10004f90 (35B) - Set ambient light color
void gbGfxManager::SetAmbientLight(const gbColorFlt& color) {
    memcpy(&AmbientLight, &color, sizeof(gbColorFlt));
}

// 0x1001dac0 (34B) - Get delta time since last frame
double gbGfxManager::GetDeltaTime(void) {
    double dt = CurTime - LastTime;
    if (dt >= 0.5) dt = 0.5;
    return dt;
}

// 0x1001daf0 (27B) - Get delta tick since last frame
unsigned int gbGfxManager::GetDeltaTick(void) {
    unsigned int dt = CurTick - LastTick;
    if (dt > 500) dt = 100;
    return dt;
}

// 0x10004ea0 (13B) - Set scene graph
void gbGfxManager::SetSceneGraph(gbSceneGraph* sg) {
    pSceneGraph = sg;
}

// 0x10004ed0 (14B) - Get matrix stack by index
gbMatrixStack* gbGfxManager::GetMatrixStack(int index) {
    return pMatrixStack[index];
}

// 0x10004ee0 (16B) - Get print font by type
gbPrintFont* gbGfxManager::GetPrintFont(gbFontType fontType) {
    return ((gbPrintFont**)pFontMgr)[fontType];
}

// 0x10004f50 (20B) - Get light object by index
const gbLight* gbGfxManager::GetLight(int index) const {
    return &AllLight[index];
}

// 0x10004f70 (14B) - Check if a light is enabled
int gbGfxManager::IsLightEnable(int index) const {
    return LightEnable[index];
}

// 0x1001df40 (265B) - Get a combined transform matrix
void gbGfxManager::GetTMMatrix(int type, gbMatrix4* out) {
    gbMatrix4 tmp;
    switch (type) {
    case 0:
        memcpy(out, pMatrixStack[1]->GetTop(), sizeof(gbMatrix4));
        break;
    case 1:
        memcpy(out, pMatrixStack[0]->GetTop(), sizeof(gbMatrix4));
        break;
    case 2:
        memcpy(out, pMatrixStack[1]->GetTop(), sizeof(gbMatrix4));
        out->RightMultiply(*pMatrixStack[0]->GetTop());
        break;
    case 3:
        pMatrixStack[0]->GetTop()->Invert(out);
        break;
    case 4:
        pMatrixStack[1]->GetTop()->Invert(out);
        break;
    case 5:
        pMatrixStack[0]->GetTop()->Invert(out);
        pMatrixStack[1]->GetTop()->Invert(&tmp);
        out->RightMultiply(tmp);
        break;
    }
}

// 0x1001e070 (24B) - Get current viewport
void gbGfxManager::GetViewport(gbViewPort& pViewport) {
    memcpy(&pViewport, &Viewport, sizeof(gbViewPort));
}

// 0x1001e090 (35B) - Set clear parameters (color, depth, stencil)
void gbGfxManager::SetClearParam(gbClearParam* pParam) {
    memcpy(&ClearParam, pParam, sizeof(gbClearParam));
}

// 0x1001e160 (189B) - Create a new mesh resource
gbBaseMesh* gbGfxManager::NewMesh(const char* name, gbMeshType type) {
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
    if (enable != CurZBias) {
        CurZBias = enable;
        *(int*)((char*)pMatrixStack[0] + 0xC) = 0;
    }
}

// 0x1001e2f0 (13B) - Set wireframe rendering mode
void gbGfxManager::SetWireMode(int mode) {
    bWireMode = mode;
}

// 0x1001e300 (38B) - Set fog parameters
void gbGfxManager::SetFog(gbFogParam* pFogParam) {
    if (pFogParam == NULL) {
        FogParam.enable = 0;
        return;
    }
    memcpy(&FogParam, pFogParam, sizeof(gbFogParam));
}

// 0x1001e330 (55B) - Get world matrix (computes from matrix stack)
const gbMatrix4& gbGfxManager::GetWorldMatrix(void) {
    gbMatrix4* top = pMatrixStack[1]->GetTop();
    memcpy(&WorldMatrix, top, sizeof(gbMatrix4));
    WorldMatrix.RightMultiply(InvViewMatrix);
    return WorldMatrix;
}

// Exported: GetViewMatrix
const gbMatrix4& gbGfxManager::GetViewMatrix(void) {
    return ViewMatrix;
}

// 0x1001e380 (19B) - Load view matrix into world matrix stack
void gbGfxManager::IdentityWorldMatrix(void) {
    pMatrixStack[1]->LoadMatrix(&ViewMatrix);
}

// 0x1001e3a0 (43B) - Set view and projection matrices from camera
void gbGfxManager::SetCameraMatrix(const gbMatrix4& view, const gbMatrix4& proj) {
    memcpy(&InvViewMatrix, &view, sizeof(gbMatrix4));
    memcpy(&ViewMatrix, &proj, sizeof(gbMatrix4));
}

// Exported: GetGfxCaps - base class stub, always returns 0
int gbGfxManager::GetGfxCaps(gbGfxCaps* caps) {
    return 0;
}

// Exported: GetCurTick
unsigned int gbGfxManager::GetCurTick(void) {
    return CurTick;
}

// Exported: GetCurTime
double gbGfxManager::GetCurTime(void) {
    return CurTime;
}

// Exported: GetDriverInfo
const gbGfxDriverInfo* gbGfxManager::GetDriverInfo(void) {
    return &DrvInfo;
}

// Exported: GetEffectMgr
gbEffectMgr* gbGfxManager::GetEffectMgr(void) {
    return pEffectMgr;
}

// Exported: GetEmissiveFactor
float gbGfxManager::GetEmissiveFactor(void) {
    return fSelfIllum;
}

// Exported: GetFog
gbFogParam* gbGfxManager::GetFog(void) {
    return &FogParam;
}

// Exported: GetGraphWnd
unsigned int gbGfxManager::GetGraphWnd(void) {
    return DrvInfo.hgfxwnd;
}

// Exported: GetPrintFontMgr
gbPrintFontMgr* gbGfxManager::GetPrintFontMgr(void) {
    return pFontMgr;
}

// Exported: GetResManager
gbResManager* gbGfxManager::GetResManager(void) {
    return pTexResMgr;
}

// Exported: GetSceneGraph
gbSceneGraph* gbGfxManager::GetSceneGraph(void) {
    return pSceneGraph;
}

// Exported: GetStatistic
gbGfxStatistic* gbGfxManager::GetStatistic(void) {
    return &Stat;
}

// Exported: GetVertPoolMgr
gbVertPoolMgr* gbGfxManager::GetVertPoolMgr(void) {
    return pVertPoolMgr;
}

// Exported: IsWireMode
int gbGfxManager::IsWireMode(void) {
    return bWireMode;
}


// gbRenderEffect methods moved to gbRenderEffect.cpp


// ============================================================================
// gbEffectMgr method implementations
// ============================================================================

// 0x10004d20 (12B) - Default constructor
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

// 0x10004d30 (148B) - Copy constructor
gbEffectMgr::gbEffectMgr(const gbEffectMgr& other) {
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
    Release();
}

// operator=
gbEffectMgr& gbEffectMgr::operator=(const gbEffectMgr& other) {
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

// gbEffectMgr methods moved to gbEffectMgr.cpp


// ============================================================
// Additional export implementations
// ============================================================

#pragma optimize("", off)
#pragma auto_inline(off)

// gbGfxManager_D3D: full definition in gbGfxManager.h
// gbImage2DInfo: full definition in gbTexture.h (included via gbMesh.h)

