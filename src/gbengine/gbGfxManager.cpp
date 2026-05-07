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

gbGfxManager::gbGfxManager() {
    memset(this, 0, sizeof(gbGfxManager));
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

    gbRenderEffect* pEffect = pEffectMgr->m_pDefaultEffect;
    pEffect->Apply();
    pEffectMgr->m_nFrameCounter = 0;
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

    // Get frustum planes via virtual call (slot 16)
    // 6 planes × (nx, ny, nz, d) = 24 floats
    GetFrustumPlanes(planes, 0);

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
    if (dt >= 0.5) return 0.1;
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
        pMatrixStack[0]->dirty = 0;
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
gbEffectMgr::gbEffectMgr(void) : gbResManager() {
}

// 0x10004d30 (148B) - Copy constructor
gbEffectMgr::gbEffectMgr(const gbEffectMgr& other) {
    memcpy(this, &other, sizeof(gbEffectMgr));
}

// Destructor
gbEffectMgr::~gbEffectMgr() {
    Release();
}

// operator=
gbEffectMgr& gbEffectMgr::operator=(const gbEffectMgr& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbEffectMgr));
    }
    return *this;
}

// 0x1001d1f0 (786B) - Initialize the effect manager
void gbEffectMgr::Init(gbGfxManager* gfxMgr) {
    m_pGfxMgr = gfxMgr;
    m_nNumVertFormats = 0;
    m_nMaxVertFormats = 0;

    // Create white texture and load it
    m_pWhiteTexture = gfxMgr->NewTexture("gfx/script/white.tga");
    m_pWhiteTexture->LoadTexture(1);

    // Create gray texture and load it
    m_pGrayTexture = gfxMgr->NewTexture("gfx/script/gray.tga");
    m_pGrayTexture->LoadTexture(1);

    // Create default effect and all standard effects
    m_pDefaultEffect = NewRenderEffect("gfx/script/default.gbf", 0);
    NewRenderEffect("gfx/script/geom1.gbf", 3);
    NewRenderEffect("gfx/script/geom1s.gbf", 7);
    NewRenderEffect("gfx/script/geomT.gbf", 0x43);
    NewRenderEffect("gfx/script/geomTs.gbf", 0x47);
    NewRenderEffect("gfx/script/geomT2.gbf", 0x83);
    NewRenderEffect("gfx/script/geomT3.gbf", 0x103);
    NewRenderEffect("gfx/script/geomT2.gbf", 0x87);
    NewRenderEffect("gfx/script/geomT3.gbf", 0x107);
    NewRenderEffect("gfx/script/geom1a.gbf", 5);
    NewRenderEffect("gfx/script/geomTa.gbf", 0x45);
    NewRenderEffect("gfx/script/geom2.gbf", 0xD);
    NewRenderEffect("gfx/script/geomT2a.gbf", 0x4D);
    NewRenderEffect("gfx/script/newge.gbf", 1);
    NewRenderEffect("gfx/script/geomTn.gbf", 0x41);
    NewRenderEffect("gfx/script/geom1f.gbf", 0x23);
    NewRenderEffect("gfx/script/geom1fs.gbf", 0x27);
    NewRenderEffect("gfx/script/geomTf.gbf", 0x63);
    NewRenderEffect("gfx/script/geomTfs.gbf", 0x67);
    NewRenderEffect("gfx/script/geomTf2.gbf", 0xA3);
    NewRenderEffect("gfx/script/geomTf3.gbf", 0x123);
    NewRenderEffect("gfx/script/geomTf2.gbf", 0xA7);
    NewRenderEffect("gfx/script/geomTf3.gbf", 0x127);
    NewRenderEffect("gfx/script/geom1fa.gbf", 0x25);
    NewRenderEffect("gfx/script/geomTfa.gbf", 0x65);
    NewRenderEffect("gfx/script/geom2f.gbf", 0x2D);
    NewRenderEffect("gfx/script/geomTf2a.gbf", 0x6D);
    NewRenderEffect("gfx/script/geomFn.gbf", 0x21);
    NewRenderEffect("gfx/script/geomTfn.gbf", 0x61);
    NewRenderEffect("gfx/script/skinG.gbf", 0x200);
    NewRenderEffect("gfx/script/skin1.gbf", 0x204);
    NewRenderEffect("gfx/script/skin2.gbf", 0x20C);
    NewRenderEffect("gfx/script/skinFn.gbf", 0x220);
    NewRenderEffect("gfx/script/skin1f.gbf", 0x224);
    NewRenderEffect("gfx/script/skin2f.gbf", 0x22C);
    NewRenderEffect("gfx/script/skinT.gbf", 0x240);
    NewRenderEffect("gfx/script/skinT1.gbf", 0x244);
    NewRenderEffect("gfx/script/skinT2.gbf", 0x24C);
    NewRenderEffect("gfx/script/skinTf.gbf", 0x260);
    NewRenderEffect("gfx/script/skinTf1.gbf", 0x264);
    NewRenderEffect("gfx/script/skinTf2.gbf", 0x26C);
    NewRenderEffect("gfx/script/geomC.gbf", 0x401);
    NewRenderEffect("gfx/script/geomTC.gbf", 0x441);
    NewRenderEffect("gfx/script/geomC.gbf", 0x421);
    NewRenderEffect("gfx/script/geomTC.gbf", 0x461);

    m_nFrameCounter = 0;
}

// 0x1001d510 (67B) - Release all managed effects
void gbEffectMgr::Release(void) {
    // Effects are reference-counted resources; cleanup via ResManager
    m_nFrameCounter = 0;
}

// gbEffectMgr methods: OnLostDevice, OnResetDevice, NewTrivalEffect,
// GetRenderEffect, GetDefaultEffect, GetWhiteTexture, GetGrayTexture
// are implemented in gbEffectMgr.cpp


// gbCreateGraphManager is implemented in gbGlobals.cpp

// ============================================================
// gbGfxManager base class virtual method defaults
// These are overridden in gbGfxManager_D3D with real D3D9 calls.
// The base class provides no-op defaults for the vtable layout.
// ============================================================

#pragma optimize("", off)
#pragma auto_inline(off)

// slot 1: Window message handler
void gbGfxManager::MsgProc(int msg, int wParam, int lParam) {}

// slot 2: Create texture object
gbTexture* gbGfxManager::NewTexture(const char* name) { return NULL; }

// slot 4: Create vertex pool
void* gbGfxManager::NewVertexPool(int poolType, int fvf, int count) { return NULL; }

// slot 5: Create index pool
void* gbGfxManager::NewIndexPool(int poolType, int indexSize, int count) { return NULL; }

// slot 6: Create dynamic vertex buffer
void* gbGfxManager::NewDynVertBuf(int fvf, int maxVerts) { return NULL; }

// slot 7: Set perspective projection from frustum params
void gbGfxManager::SetFrustum(double l, double r, double b, double t, double n, double f) {}

// slot 8: Set orthographic projection
void gbGfxManager::SetOrtho(double l, double r, double b, double t, double n, double f) {}

// slot 9: Set viewport
void gbGfxManager::SetViewport(void* pViewportData) {}

// slot 10: Set light
void gbGfxManager::SetLight(int index, void* pLightData) {}

// slot 11: Set material
void gbGfxManager::SetMaterial(D3DMATERIAL9* pMaterial) {}

// slot 13: End scene and present
void gbGfxManager::Present() {}

// slot 14: Draw indexed primitive
void gbGfxManager::DrawIndexedPrimitive(int, int, int, int, int, int, int) {}

// slot 15: Draw primitive
void gbGfxManager::DrawPrimitive() {}

// slot 16: Get frustum planes (used by ClipBoundVolume)
void gbGfxManager::GetFrustumPlanes(float* outPlanes, int bNormalize) {}

// slot 18: Apply transform matrices to device
void gbGfxManager::ApplyTransform() {}

// slot 19: Set gamma ramp
void gbGfxManager::SetGammaRamp(void* pData) {}

// slot 20: Get gamma ramp
void gbGfxManager::GetGammaRamp(int p1, int p2) {}

// slot 21: Create depth stencil surface
void gbGfxManager::CreateDepthStencil(int index, int param2) {}

// slot 22: Restore depth stencil surface
void gbGfxManager::RestoreDepthStencil() {}

// slot 23: Set render target
void gbGfxManager::SetRenderTarget(void* pParam) {}

// slot 24: Load cursor resource
void* gbGfxManager::LoadCursor(const char* name) { return NULL; }

// slot 25: Set cursor
void gbGfxManager::SetCursor(void* pCursor) {}

// slot 26: Show cursor
void gbGfxManager::ShowCursor(int bShow) {}

// slot 27: Set software vertex processing mode
void gbGfxManager::SetSoftwareVP(int bSoftVP) {}

