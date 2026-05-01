#pragma once

#include "gbengine/gbengine_types.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbMesh.h"
#include <d3d9.h>

// Forward declarations
class gbEffectMgr;
class gbResManager;
class gbVertPoolMgr;
class gbPrintFontMgr;
class gbPrintFont;
class gbMatrixStack;
class gbSceneGraph;
class gbBaseMesh;
class gbRenderEffect;

struct gbLight;

// ============================================================================
// gbClearParam
// ============================================================================
struct gbClearParam {
    unsigned int color;
    float depth;
    unsigned int stencil;
    unsigned int flags;
};

// ============================================================================
// gbFogParam
// ============================================================================
struct gbFogParam {
    int enable;
    unsigned int color;
    float start;
    float end;
    float density;
    int mode;
};

// ============================================================================
// gbGfxCaps
// ============================================================================
struct gbGfxCaps {
    int maxTextureWidth;
    int maxTextureHeight;
    int maxLights;
    int hwTnL;
    int vertexShaderVer;
    int pixelShaderVer;
};

// ============================================================================
// gbGfxStatistic
// ============================================================================
struct gbGfxStatistic {
    int numTriangles;
    int numVertices;
    int numDrawCalls;
    int numTexChanges;
};

// ============================================================================
// gbFontType
// ============================================================================
enum gbFontType {
    GB_FONT_DEFAULT = 0,
    GB_FONT_SMALL = 1,
    GB_FONT_LARGE = 2
};

// ============================================================================
// gbTransformType - D3D transform type constants used by the engine
// (maps to D3DTS_WORLD, D3DTS_VIEW, D3DTS_PROJECTION, etc.)
// ============================================================================
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

// Global pointer to the graphics manager
extern gbGfxManager* g_pGfxManager;
