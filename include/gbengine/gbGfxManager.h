#pragma once

#include "gbengine/gbengine_types.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbSceneGraph.h"
#include <d3d9.h>

// Forward declarations
class gbEffectMgr;
class gbResManager;
class gbVertPoolMgr;
class gbPrintFontMgr;
class gbPrintFont;
class gbMatrixStack;
class gbBaseMesh;
class gbRenderEffect;

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
    int reserved[7];
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
// gbGfxStatistic - sizeof = 0x30 (from PAL3A PDB)
// ============================================================================
struct gbGfxStatistic {
    int nRFaces;
    int nRVerts;
    int nStaticVerts;
    int nStaticIndex;
    int nSrcVerts;
    int nSrcIndex;
    int nTexSwitch;
    float FPS;
    double TimeAccum;
    unsigned int Frame;
    unsigned int PrevFrame;
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
// sizeof = 0x5F0 (from PAL3A PDB), derived gbGfxManager_D3D = 0x8F0
// Field layout verified against Ghidra disassembly and PAL3A PDB symbols.
// ============================================================================
class gbGfxManager {
public:
    // vtable implicit                          // +0x00
    int m_nState;                               // +0x04
    unsigned int hGfxWnd;                       // +0x08
    gbGfxDriverInfo DrvInfo;                    // +0x0C (0xB8 bytes)
    gbVertPoolMgr* pVertPoolMgr;               // +0xC4
    gbEffectMgr* pEffectMgr;                   // +0xC8
    gbResManager* pTexResMgr;                  // +0xCC
    gbPrintFontMgr* pFontMgr;                 // +0xD0
    gbMatrixStack* pMatrixStack[4];            // +0xD4
    gbMatrix4 ViewMatrix;                      // +0xE4
    gbMatrix4 InvViewMatrix;                   // +0x124
    gbMatrix4 WorldMatrix;                     // +0x164
    int CurZBias;                              // +0x1A4
    int bWireMode;                             // +0x1A8
    gbColorFlt AmbientLight;                   // +0x1AC
    float fSelfIllum;                          // +0x1BC
    gbSceneGraph* pSceneGraph;                 // +0x1C0
    gbViewPort Viewport;                       // +0x1C4
    gbClearParam ClearParam;                   // +0x1DC
    int _pad1EC;                               // +0x1EC: alignment padding for double
    double LastTime;                            // +0x1F0
    double CurTime;                            // +0x1F8
    unsigned int LastTick;                      // +0x200
    unsigned int CurTick;                      // +0x204
    gbGfxStatistic Stat;                       // +0x208 (0x30)
    gbLight AllLight[8];                       // +0x238 (0x68 × 8 = 0x340)
    int LightEnable[8];                        // +0x578 (0x20)
    gbFogParam FogParam;                       // +0x598 (0x34)
    gbTexture* m_pCurTexture[8];               // +0x5CC (0x20)
    char _pad5EC[4];                           // +0x5EC
    // total sizeof = 0x5F0

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
