/**
 * gbengine.dll - gbGfxManager, gbCamera, gbRenderEffect, gbEffectMgr
 *
 * Functional decompilation of graphics management, camera, and effect classes.
 * Based on PAL3patch struct definitions and Ghidra export analysis.
 *
 * Compiler: MSVC 6.0 SP5
 * Graphics: DirectX 9 (Summer 2003 SDK)
 */

#include "gbengine/gbengine_types.h"
#include "gbengine/gbRenderEffect.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Forward declarations
class gbTexture;
class gbTexture_D3D;
struct gbTextureArray;
class gbImage2D;
class gbBaseMesh;
class gbStaticMesh;
class gbResManager;
class gbResource;
class gbVFileSystem;
class gbVFile;
class gbVertPoolMgr;
class gbVertexPool;
class gbDynVertBuf;
class gbPrintFont;
class gbPrintFontMgr;
class gbMatrixStack;
class gbVisNode;
class gbGeomNode;
class gbRefObject;

// Forward declarations for classes defined in this file
class gbGfxManager;
class gbCamera;
class gbRenderEffect;
class gbEffectMgr;
class gbCamControler;
class gbSceneGraph;

struct gbVertexElement;
struct gbLight;

// Pixel format enum (matches gbengine's internal enum)
// gbPixelFmtType is defined in gbengine_types.h

// Forward struct declarations
struct gbClearParam {
    unsigned int color;
    float depth;
    unsigned int stencil;
    unsigned int flags;
};

struct gbFogParam {
    int enable;
    unsigned int color;
    float start;
    float end;
    float density;
    int mode;
};

struct gbGfxCaps {
    int maxTextureWidth;
    int maxTextureHeight;
    int maxLights;
    int hwTnL;
    int vertexShaderVer;
    int pixelShaderVer;
};

struct gbGfxStatistic {
    int numTriangles;
    int numVertices;
    int numDrawCalls;
    int numTexChanges;
};

struct gbLight;

enum gbMeshType {
    GB_MESH_STATIC = 0,
    GB_MESH_SKIN = 1
};

enum gbFontType {
    GB_FONT_DEFAULT = 0,
    GB_FONT_SMALL = 1,
    GB_FONT_LARGE = 2
};

// External globals
gbGfxManager* g_pGfxManager = NULL;
extern double g_CurrentTime;
extern unsigned int g_CurrentTick;

// D3D transform type constants used by the engine
// (maps to D3DTS_WORLD, D3DTS_VIEW, D3DTS_PROJECTION, etc.)
enum gbTransformType {
    GB_TM_WORLD = 0,
    GB_TM_VIEW = 1,
    GB_TM_PROJECTION = 2,
    GB_TM_TEXTURE0 = 3
};

// ============================================================================
// gbGfxDriverInfo - graphics driver initialization info
// ============================================================================
struct gbGfxDriverInfo {
    int type;
    int subtype;
    int width;
    int height;
    int colorbits;
    int depthbits;
    int stensilbits;
    int nbackbuf;
    int fullscreen;
    int refreshrate;
    char winname[0x80];
    unsigned int hinst;     // HINSTANCE
    unsigned int hgfxwnd;   // HWND
    int newwindow;
    int waitforverticalblank;
};

// ============================================================================
// gbViewPort
// ============================================================================
struct gbViewPort {
    int x;
    int y;
    int width;
    int height;
    float minz;
    float maxz;
};

// ============================================================================
// gbGfxManager - main graphics manager
//
// Layout from PAL3patch (sizeof gbGfxManager_D3D = 0x8F0):
//   +0x00: vtable
//   +0x04: flags/state
//   +0x08: scene state
//   +0x0C: gbGfxDriverInfo DrvInfo (0xA4 bytes)
//   +0xB0: gbVertPoolMgr*
//   +0xB4: gbEffectMgr*
//   +0xB8: gbResManager* pTexResMgr
//   +0xBC: gbPrintFontMgr*
//   +0xC0: gbMatrixStack* pMatrixStack[4]
//   ... many more fields in derived gbGfxManager_D3D ...
//   +0x84C: IDirect3DDevice9* m_pd3dDevice (in D3D subclass)
// ============================================================================
class gbGfxManager {
public:
    // Vtable pointer is implicit in C++
    int m_nState;               // +0x04: general state flags
    int m_bInScene;             // +0x08: true while between BeginScene/EndScene

    gbGfxDriverInfo DrvInfo;    // +0x0C: driver info (0xA4 bytes)

    gbVertPoolMgr* pVertPoolMgr;        // +0xB0
    gbEffectMgr* pEffectMgr;            // +0xB4
    gbResManager* pTexResMgr;           // +0xB8
    gbPrintFontMgr* pFontMgr;          // +0xBC
    gbMatrixStack* pMatrixStack[4];     // +0xC0

    gbSceneGraph* pSceneGraph;          // scene graph
    gbCamera* pCamera;                  // active camera

    gbColorFlt m_ambientLight;          // ambient light color
    int m_bEmissiveEnable;              // emissive lighting flag
    float m_fEmissiveFactor;            // emissive scale factor

    double m_lastTime;                  // last frame time
    double m_deltaTime;                 // time between frames
    unsigned int m_lastTick;            // last tick count
    unsigned int m_deltaTick;           // tick delta

    gbMatrix4 m_worldMatrix;            // current world transform
    gbMatrix4 m_viewMatrix;             // current view transform
    gbMatrix4 m_projMatrix;             // current projection transform

    int m_nWireMode;                    // wireframe rendering mode

    // Padding to approximate real struct size
    // gbGfxManager_D3D is 0x8F0 bytes total; the D3D-specific fields
    // (IDirect3D9*, IDirect3DDevice9*, D3DCAPS9, etc.) live in the derived class.
    // We only model the base class here.

    // 0x1001d910 (394B) - Constructor
    gbGfxManager(int& result, gbGfxDriverInfo* driverInfo);

    // Virtual destructor
    virtual ~gbGfxManager();

    // EndScene: finish the rendering scene (declared below via virtual)

    // SetTransform: set a transform matrix (world/view/projection)
    void SetTransform(int type, gbMatrix4* matrix);

    // 0x1001e220 (158B) - Clip a bounding volume against the view frustum
    // Returns: 0 = fully outside, 1 = partially inside, 2 = fully inside
    int ClipBoundVolume(gbAABBox* box);

    // 0x10004ff0 (34B) - Enable/disable emissive lighting
    void EnableEmissive(int enable);

    // 0x10005020 (13B) - Set emissive factor
    void SetEmissiveFactor(float factor);

    // 0x10004fc0 (39B) - Get ambient light color
    gbColorFlt GetAmbientLight(void);

    // 0x10004f90 (35B) - Set ambient light color
    void SetAmbientLight(const gbColorFlt& color);

    // 0x1001dac0 (34B) - Get delta time since last frame
    double GetDeltaTime(void);

    // 0x1001daf0 (27B) - Get delta tick since last frame
    unsigned int GetDeltaTick(void);

    // 0x10004ea0 (13B) - Set scene graph
    void SetSceneGraph(gbSceneGraph* sg);

    // 0x10004ed0 (14B) - Get matrix stack by index
    gbMatrixStack* GetMatrixStack(int index);

    // 0x10004ee0 (16B) - Get print font by type
    gbPrintFont* GetPrintFont(int fontType);

    // 0x10004f50 (20B) - Get light object by index (const method)
    const gbLight* GetLight(int index) const;

    // 0x10004f70 (14B) - Check if a light is enabled (const method)
    int IsLightEnable(int index) const;

    // 0x1001df40 (37B) - Get a combined transform matrix
    void GetTMMatrix(int type, gbMatrix4* out);

    // 0x1001e070 (24B) - Get current viewport
    void GetViewport(gbViewPort& pViewport);

    // 0x1001e090 (35B) - Set clear parameters (color, depth, stencil)
    void SetClearParam(gbClearParam* pParam);

    // 0x1001e160 (189B) - Create a new mesh resource
    virtual gbBaseMesh* NewMesh(const char* name, gbMeshType type);

    // 0x1001e2c0 (36B) - Offset Z-buffer for decal rendering
    void OffsetZBuffer(int enable);

    // 0x1001e2f0 (13B) - Set wireframe rendering mode
    void SetWireMode(int mode);

    // 0x1001e300 (38B) - Set fog parameters
    virtual void SetFog(gbFogParam* pFogParam);

    // 0x1001e330 (55B) - Get world matrix (const reference)
    const gbMatrix4& GetWorldMatrix(void);

    // 0x1001e380 (19B) - Reset world matrix to identity
    void IdentityWorldMatrix(void);

    // Exported: GetViewMatrix
    const gbMatrix4& GetViewMatrix(void);

    // 0x1001e3a0 (43B) - Set view and projection matrices from camera
    void SetCameraMatrix(const gbMatrix4& view, const gbMatrix4& proj);

    // Exported: GetGfxCaps
    virtual int GetGfxCaps(gbGfxCaps* caps);

    // Exported: GetCurTick
    unsigned int GetCurTick(void);

    // Exported: GetCurTime
    double GetCurTime(void);

    // Exported: GetDriverInfo
    const gbGfxDriverInfo* GetDriverInfo(void);

    // Exported: GetEffectMgr
    gbEffectMgr* GetEffectMgr(void);

    // Exported: GetEmissiveFactor
    float GetEmissiveFactor(void);

    // Exported: GetFog
    gbFogParam* GetFog(void);

    // Exported: GetGraphWnd
    unsigned int GetGraphWnd(void);

    // Exported: GetPrintFontMgr
    gbPrintFontMgr* GetPrintFontMgr(void);

    // Exported: GetResManager
    gbResManager* GetResManager(void);

    // Exported: GetSceneGraph
    gbSceneGraph* GetSceneGraph(void);

    // Exported: GetStatistic
    gbGfxStatistic* GetStatistic(void);

    // Exported: GetVertPoolMgr
    gbVertPoolMgr* GetVertPoolMgr(void);

    // Exported: IsWireMode
    int IsWireMode(void);

    // virtual BeginScene
    virtual int BeginScene(void);

    // EndScene (not in vtable in some builds)
    void EndScene(void);
};


// gbCamera class is defined in gbCamera.cpp




// gbRenderEffect and gbEffectMgr declarations are in gbRenderEffect.h


// ============================================================================
// gbGfxManager method implementations
// ============================================================================

// 0x1001d910 (394B) - Constructor
gbGfxManager::gbGfxManager(int& result, gbGfxDriverInfo* driverInfo) {
    m_nState = 0;
    m_bInScene = 0;

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
    pCamera = NULL;

    memset(pMatrixStack, 0, sizeof(pMatrixStack));

    m_ambientLight.r = 0.2f;
    m_ambientLight.g = 0.2f;
    m_ambientLight.b = 0.2f;
    m_ambientLight.a = 1.0f;

    m_bEmissiveEnable = 0;
    m_fEmissiveFactor = 1.0f;

    m_lastTime = 0.0;
    m_deltaTime = 0.0;
    m_lastTick = 0;
    m_deltaTick = 0;

    // Initialize world matrix to identity
    memset(&m_worldMatrix, 0, sizeof(gbMatrix4));
    m_worldMatrix.m[0][0] = 1.0f;
    m_worldMatrix.m[1][1] = 1.0f;
    m_worldMatrix.m[2][2] = 1.0f;
    m_worldMatrix.m[3][3] = 1.0f;

    memset(&m_viewMatrix, 0, sizeof(gbMatrix4));
    m_viewMatrix.m[0][0] = 1.0f;
    m_viewMatrix.m[1][1] = 1.0f;
    m_viewMatrix.m[2][2] = 1.0f;
    m_viewMatrix.m[3][3] = 1.0f;

    memset(&m_projMatrix, 0, sizeof(gbMatrix4));
    m_projMatrix.m[0][0] = 1.0f;
    m_projMatrix.m[1][1] = 1.0f;
    m_projMatrix.m[2][2] = 1.0f;
    m_projMatrix.m[3][3] = 1.0f;

    m_nWireMode = 0;

    result = 1; // success
}

gbGfxManager::~gbGfxManager() {
    // Cleanup is handled by derived class (gbGfxManager_D3D)
}

// 0x1001db10 (222B) - Begin a rendering scene
int gbGfxManager::BeginScene(void) {
    if (m_bInScene)
        return 0;

    // Update time tracking
    double currentTime = g_CurrentTime;
    m_deltaTime = currentTime - m_lastTime;
    m_lastTime = currentTime;

    unsigned int currentTick = g_CurrentTick;
    m_deltaTick = currentTick - m_lastTick;
    m_lastTick = currentTick;

    // In the real D3D implementation, this calls IDirect3DDevice9::BeginScene()
    // and clears the render target. The actual D3D calls are in gbGfxManager_D3D.
    m_bInScene = 1;
    return 1;
}

// EndScene: finish the rendering scene
void gbGfxManager::EndScene(void) {
    if (!m_bInScene)
        return;

    // In gbGfxManager_D3D, this calls:
    //   m_pd3dDevice->EndScene();
    //   m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
    m_bInScene = 0;
}

// SetTransform: set a transform matrix (world/view/projection)
void gbGfxManager::SetTransform(int type, gbMatrix4* matrix) {
    if (!matrix)
        return;

    switch (type) {
    case GB_TM_WORLD:
        memcpy(&m_worldMatrix, matrix, sizeof(gbMatrix4));
        break;
    case GB_TM_VIEW:
        memcpy(&m_viewMatrix, matrix, sizeof(gbMatrix4));
        break;
    case GB_TM_PROJECTION:
        memcpy(&m_projMatrix, matrix, sizeof(gbMatrix4));
        break;
    }

    // In the real engine, this also calls IDirect3DDevice9::SetTransform()
    // with the appropriate D3DTRANSFORMSTATETYPE
}

// 0x1001e220 (158B) - Clip a bounding volume against the view frustum
// Returns: 0 = fully outside, 1 = partially inside, 2 = fully inside
int gbGfxManager::ClipBoundVolume(gbAABBox* box) {
    if (!box || !pCamera)
        return 0;

    // Delegate to camera's clip method
    // The camera maintains 6 frustum planes and tests the AABB against them
    gbVec3D minPt, maxPt;
    minPt = box->vMin;
    maxPt = box->vMax;

    // Quick test: call the camera's AABB clip
    // flags parameter 0x3F means test all 6 planes
    // Return value uses same convention: 0=out, 1=partial, 2=in
    // We implement a simplified version here; real logic is in gbCamera::ClipAABBox
    return 1; // assume partially visible as fallback
}

// 0x10004ff0 (34B) - Enable/disable emissive lighting
void gbGfxManager::EnableEmissive(int enable) {
    m_bEmissiveEnable = enable;
    // In the real engine, this also sets D3D render state
    // D3DRS_EMISSIVEMATERIALSOURCE etc.
}

// 0x10005020 (13B) - Set emissive factor
void gbGfxManager::SetEmissiveFactor(float factor) {
    m_fEmissiveFactor = factor;
}

// 0x10004fc0 (39B) - Get ambient light color
gbColorFlt gbGfxManager::GetAmbientLight(void) {
    return m_ambientLight;
}

// 0x10004f90 (35B) - Set ambient light color
void gbGfxManager::SetAmbientLight(const gbColorFlt& color) {
    m_ambientLight = color;

    // In the real engine, this converts to D3DCOLOR and calls
    // IDirect3DDevice9::SetRenderState(D3DRS_AMBIENT, d3dColor)
}

// 0x1001dac0 (34B) - Get delta time since last frame
double gbGfxManager::GetDeltaTime(void) {
    return m_deltaTime;
}

// 0x1001daf0 (27B) - Get delta tick since last frame
unsigned int gbGfxManager::GetDeltaTick(void) {
    return m_deltaTick;
}

// 0x10004ea0 (13B) - Set scene graph
void gbGfxManager::SetSceneGraph(gbSceneGraph* sg) {
    pSceneGraph = sg;
}

// 0x10004ed0 (14B) - Get matrix stack by index
gbMatrixStack* gbGfxManager::GetMatrixStack(int index) {
    if (index < 0 || index >= 4)
        return NULL;
    return pMatrixStack[index];
}

// 0x10004ee0 (16B) - Get print font by type
gbPrintFont* gbGfxManager::GetPrintFont(int fontType) {
    // In the real engine, this calls pFontMgr->GetFont(fontType)
    // We return NULL as a stub since we don't have the font manager fully defined
    return NULL;
}

// 0x10004f50 (20B) - Get light object by index
const gbLight* gbGfxManager::GetLight(int index) const {
    // Light objects are stored in an array inside the GfxManager
    // Stub: return NULL
    return NULL;
}

// 0x10004f70 (14B) - Check if a light is enabled
int gbGfxManager::IsLightEnable(int index) const {
    return 0;
}

// 0x1001df40 (37B) - Get a combined transform matrix
void gbGfxManager::GetTMMatrix(int type, gbMatrix4* out) {
    if (!out)
        return;
    switch (type) {
    case GB_TM_WORLD:
        memcpy(out, &m_worldMatrix, sizeof(gbMatrix4));
        break;
    case GB_TM_VIEW:
        memcpy(out, &m_viewMatrix, sizeof(gbMatrix4));
        break;
    case GB_TM_PROJECTION:
        memcpy(out, &m_projMatrix, sizeof(gbMatrix4));
        break;
    }
}

// 0x1001e070 (24B) - Get current viewport
void gbGfxManager::GetViewport(gbViewPort& pViewport) {
    // In the real engine, calls IDirect3DDevice9::GetViewport()
    // and converts to the gbViewPort structure
}

// 0x1001e090 (35B) - Set clear parameters (color, depth, stencil)
void gbGfxManager::SetClearParam(gbClearParam* pParam) {
    // Stores clear color/depth/stencil values for BeginScene's Clear call
}

// 0x1001e160 (189B) - Create a new mesh resource
gbBaseMesh* gbGfxManager::NewMesh(const char* name, gbMeshType type) {
    // In the real engine, allocates a gbStaticMesh or derived class
    // and registers it with the resource manager
    return NULL;
}

// 0x1001e2c0 (36B) - Offset Z-buffer for decal rendering
void gbGfxManager::OffsetZBuffer(int enable) {
    // Sets D3DRS_DEPTHBIAS / D3DRS_SLOPESCALEDEPTHBIAS
}

// 0x1001e2f0 (13B) - Set wireframe rendering mode
void gbGfxManager::SetWireMode(int mode) {
    m_nWireMode = mode;
    // In real engine: SetRenderState(D3DRS_FILLMODE, mode ? D3DFILL_WIREFRAME : D3DFILL_SOLID)
}

// 0x1001e300 (38B) - Set fog parameters
void gbGfxManager::SetFog(gbFogParam* pFogParam) {
    // Sets D3DRS_FOGENABLE, D3DRS_FOGCOLOR, D3DRS_FOGSTART, D3DRS_FOGEND, etc.
}

// 0x1001e330 (55B) - Get world matrix (const reference)
const gbMatrix4& gbGfxManager::GetWorldMatrix(void) {
    return m_worldMatrix;
}

// Exported: GetViewMatrix
const gbMatrix4& gbGfxManager::GetViewMatrix(void) {
    return m_viewMatrix;
}

// 0x1001e380 (19B) - Reset world matrix to identity
void gbGfxManager::IdentityWorldMatrix(void) {
    memset(&m_worldMatrix, 0, sizeof(gbMatrix4));
    m_worldMatrix.m[0][0] = 1.0f;
    m_worldMatrix.m[1][1] = 1.0f;
    m_worldMatrix.m[2][2] = 1.0f;
    m_worldMatrix.m[3][3] = 1.0f;

    // Also set on the D3D device
    // SetTransform(GB_TM_WORLD, &m_worldMatrix);
}

// 0x1001e3a0 (43B) - Set view and projection matrices from camera
void gbGfxManager::SetCameraMatrix(const gbMatrix4& view, const gbMatrix4& proj) {
    memcpy(&m_viewMatrix, &view, sizeof(gbMatrix4));
    memcpy(&m_projMatrix, &proj, sizeof(gbMatrix4));

    // In the real engine, also calls:
    // IDirect3DDevice9::SetTransform(D3DTS_VIEW, (D3DMATRIX*)view)
    // IDirect3DDevice9::SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)proj)
}

// Exported: GetGfxCaps
int gbGfxManager::GetGfxCaps(gbGfxCaps* caps) {
    if (!caps) return 0;
    memset(caps, 0, sizeof(gbGfxCaps));
    return 1;
}

// Exported: GetCurTick
unsigned int gbGfxManager::GetCurTick(void) {
    return m_lastTick;
}

// Exported: GetCurTime
double gbGfxManager::GetCurTime(void) {
    return m_lastTime;
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
    return m_fEmissiveFactor;
}

// Exported: GetFog
gbFogParam* gbGfxManager::GetFog(void) {
    return NULL;
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
    return NULL;
}

// Exported: GetVertPoolMgr
gbVertPoolMgr* gbGfxManager::GetVertPoolMgr(void) {
    return pVertPoolMgr;
}

// Exported: IsWireMode
int gbGfxManager::IsWireMode(void) {
    return m_nWireMode;
}


// ============================================================================
// gbRenderEffect method implementations
// ============================================================================

// 0x1001cef0 (139B) - Private constructor from effect and flags
gbRenderEffect::gbRenderEffect(ID3DXEffect* pEffect, unsigned int flags) {
    m_pEffect = pEffect;
    m_dwFlags = flags;
    m_nPasses = 0;
    m_pDecl = NULL;
    m_nTechnique = 0;

    if (m_pEffect) {
        m_pEffect->AddRef();
    }
}

gbRenderEffect::~gbRenderEffect() {
    if (m_pEffect) {
        m_pEffect->Release();
        m_pEffect = NULL;
    }
    m_pDecl = NULL;
}

// 0x10004bf0 (92B) - Copy constructor
gbRenderEffect::gbRenderEffect(const gbRenderEffect& other) {
    m_pEffect = other.m_pEffect;
    m_dwFlags = other.m_dwFlags;
    m_nPasses = other.m_nPasses;
    m_pDecl = other.m_pDecl;
    m_nTechnique = other.m_nTechnique;

    if (m_pEffect) {
        m_pEffect->AddRef();
    }
}

// operator=
gbRenderEffect& gbRenderEffect::operator=(const gbRenderEffect& other) {
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
    m_pDecl = (D3DVERTEXELEMENT9*)decl;
}

// 0x1001cfe0 (32B) - Compare two effects for sorting
int gbRenderEffect::Compare(gbRenderEffect* other) {
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
    if (!m_pEffect)
        return 0;

    HRESULT hr = m_pEffect->ValidateTechnique(NULL);
    return SUCCEEDED(hr) ? 1 : 0;
}

// 0x1001d080 (26B) - Begin rendering with this effect
int gbRenderEffect::Begin(void) {
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
    if (!m_pEffect)
        return;
    m_pEffect->BeginPass(passIndex);
}

// 0x1001d0e0 (20B) - End rendering with this effect
void gbRenderEffect::End(void) {
    if (!m_pEffect)
        return;
    m_pEffect->End();
}

// 0x1001d100 (72B) - Apply current effect state (commit changes)
void gbRenderEffect::Apply(void) {
    if (!m_pEffect)
        return;
    m_pEffect->CommitChanges();
}

// Get variant by GBPARAMHANDLE
void gbRenderEffect::GetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    if (!m_pEffect || !pValue)
        return;
    m_pEffect->GetValue((D3DXHANDLE)(intptr_t)handle, pValue, sizeof(float) * 4);
}

// Set variant by GBPARAMHANDLE
void gbRenderEffect::SetVariant(enum GBPARAMHANDLE handle, void* pValue) {
    if (!m_pEffect || !pValue)
        return;
    m_pEffect->SetValue((D3DXHANDLE)(intptr_t)handle, pValue, sizeof(float) * 4);
}

// 0x1001d190 (40B) - Get variant by name
void gbRenderEffect::GetVariant(char* name, void* pValue) {
    if (!m_pEffect || !name || !pValue)
        return;
    D3DXHANDLE hParam = m_pEffect->GetParameterByName(NULL, name);
    if (hParam)
        m_pEffect->GetValue(hParam, pValue, sizeof(float) * 4);
}

// 0x1001d1c0 (40B) - Set variant by name
void gbRenderEffect::SetVariant(char* name, void* pValue) {
    if (!m_pEffect || !name || !pValue)
        return;
    D3DXHANDLE hParam = m_pEffect->GetParameterByName(NULL, name);
    if (hParam)
        m_pEffect->SetValue(hParam, pValue, sizeof(float) * 4);
}

// Exported: GetD3DEffect
ID3DXEffect* gbRenderEffect::GetD3DEffect(void) {
    return m_pEffect;
}

// Exported: GetFlag
unsigned int gbRenderEffect::GetFlag(void) {
    return m_dwFlags;
}


// ============================================================================
// gbEffectMgr method implementations
// ============================================================================

// 0x10004d20 (12B) - Default constructor
gbEffectMgr::gbEffectMgr(void) {
    m_pGfxMgr = NULL;
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

// 0x1001d560 (50B) - Handle device lost
int gbEffectMgr::OnLostDevice(void) {
    for (int i = 0; i < m_nNumEffects; i++) {
        if (m_pEffects[i] && m_pEffects[i]->m_pEffect) {
            m_pEffects[i]->m_pEffect->OnLostDevice();
        }
    }
    return 1;
}

// 0x1001d5a0 (50B) - Handle device reset
int gbEffectMgr::OnResetDevice(void) {
    for (int i = 0; i < m_nNumEffects; i++) {
        if (m_pEffects[i] && m_pEffects[i]->m_pEffect) {
            m_pEffects[i]->m_pEffect->OnResetDevice();
        }
    }
    return 1;
}

// 0x1001d5e0 (232B) - Register a vertex format declaration
IDirect3DVertexDeclaration9* gbEffectMgr::RegisterVertexFormat(const char* name, gbVertexElement* pElements) {
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
    if (!filename || !m_pGfxMgr)
        return NULL;

    if (m_nNumEffects >= m_nMaxEffects)
        return NULL;

    // Get D3D device
    IDirect3DDevice9* pDevice = NULL;
    if (m_pGfxMgr) {
        pDevice = *(IDirect3DDevice9**)((char*)m_pGfxMgr + 0x84C);
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
    // In the real engine, this creates a simple pass-through effect
    // for fixed-function pipeline emulation
    return NULL;
}

// 0x1001d8b0 (39B) - Get effect by index
gbRenderEffect* gbEffectMgr::GetRenderEffect(unsigned int index) {
    if ((int)index >= m_nNumEffects)
        return NULL;
    return m_pEffects[index];
}

// Exported: GetDefaultEffect
gbRenderEffect* gbEffectMgr::GetDefaultEffect(void) {
    if (m_nNumEffects > 0)
        return m_pEffects[0];
    return NULL;
}

// Exported: GetGrayTexture
gbTexture* gbEffectMgr::GetGrayTexture(void) {
    return NULL;
}

// Exported: GetWhiteTexture
gbTexture* gbEffectMgr::GetWhiteTexture(void) {
    return NULL;
}
