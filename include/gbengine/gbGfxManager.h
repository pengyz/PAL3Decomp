#pragma once

#include "gbengine/gbengine_types.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbPrintFont.h"
#include <d3d9.h>

// Forward declarations (defined in gbengine_internal.h, circular dep)
class gbMatrixStack;

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
    gbPrintFont* GetPrintFont(gbFontType fontType);

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

// ============================================================================
// gbGfxManager_D3D - D3D9 derived graphics manager
// sizeof = 0x8F0 (from PAL3A PDB)
// Inherits gbGfxManager (0x5F0), adds D3D-specific state.
// ============================================================================
struct CD3DEnumeration {
    char _data[0x2C];
};

struct D3DDriverBug {
    int flags;
};

struct CD3DSettings {
    char _data[0x6C];
};

class gbCursorRes;

class gbGfxManager_D3D : public gbGfxManager {
public:
    CD3DEnumeration m_d3dEnumeration;              // +0x5F0 (0x2C)
    int m_bWindowed;                               // +0x61C
    RECT m_rcWindowClient;                         // +0x620
    RECT m_rcWindowBounds;                         // +0x630
    unsigned int m_dwWindowStyle;                  // +0x640
    HWND m_hWnd;                                   // +0x644
    unsigned char m_bMinimized;                    // +0x648
    unsigned char m_bMaximized;                    // +0x649
    unsigned char m_bClipCursorWhenFullscreen;     // +0x64A
    unsigned char m_bShowCursorWhenFullscreen;     // +0x64B
    unsigned char m_bActive;                       // +0x64C
    char _pad64D[3];                               // +0x64D: alignment padding
    unsigned int m_dwCreateFlags;                  // +0x650
    D3DDriverBug m_DriverBug;                      // +0x654
    char m_CursorMgr[0xC];                         // +0x658: gbResManager (0xC)
    gbCursorRes* m_pActiveCursor;                  // +0x664
    int m_bShowCursor;                             // +0x668
    int m_bSoftVPMode;                             // +0x66C
    CD3DSettings m_d3dSettings;                    // +0x670 (0x6C)
    D3DPRESENT_PARAMETERS m_d3dpp;                 // +0x6DC (0x38)
    IDirect3D9* m_pD3D;                            // +0x714
    IDirect3DDevice9* m_pd3dDevice;                // +0x718
    D3DCAPS9 m_d3dCaps;                            // +0x71C (0x130)
    D3DSURFACE_DESC m_d3dsdBackBuffer;             // +0x84C (0x20)
    char m_strDeviceStats[0x5A];                   // +0x86C
    char _pad8C6[2];                               // +0x8C6: alignment
    int m_ErrorCode;                               // +0x8C8
    int m_bDeviceLost;                             // +0x8CC
    IDirect3DSurface9* m_pBackBuffer;              // +0x8D0
    int m_DXTSupported[5];                         // +0x8D4
    IDirect3DVertexBuffer9* m_pCacheVB;            // +0x8E8
    IDirect3DIndexBuffer9* m_pCacheIB;             // +0x8EC
    // total sizeof = 0x8F0

    void SetTexture(struct gbTextureArray* p0);
};

// Global pointer to the graphics manager
extern gbGfxManager* g_pGfxManager;
