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
// gbGfxManager - main graphics manager (abstract base)
// sizeof = 0x5F0 (from PAL3A PDB), derived gbGfxManager_D3D = 0x8F0
// Vtable: 29 slots (verified from binary). Only gbGfxManager_D3D is concrete.
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

    gbGfxManager(int& result, gbGfxDriverInfo* driverInfo);

    // === Virtual functions (29 slots, order matches binary vtable) ===
    virtual ~gbGfxManager() = 0;                                    // slot 0
    virtual void _vf_EndScene() = 0;                                // slot 1
    virtual gbTexture* NewTexture(const char* name) = 0;            // slot 2
    virtual gbBaseMesh* NewMesh(const char* name, gbMeshType type); // slot 3
    virtual void _vf04() = 0;                                       // slot 4
    virtual void _vf05() = 0;                                       // slot 5
    virtual void _vf06() = 0;                                       // slot 6
    virtual void _vf07() = 0;                                       // slot 7
    virtual void _vf08() = 0;                                       // slot 8
    virtual void _vf09() = 0;                                       // slot 9
    virtual void _vf10() = 0;                                       // slot 10
    virtual void _vf11() = 0;                                       // slot 11
    virtual int BeginScene(void);                                    // slot 12
    virtual void _vf13() = 0;                                       // slot 13
    virtual void _vf14() = 0;                                       // slot 14
    virtual void _vf15() = 0;                                       // slot 15
    virtual void _vf16() = 0;                                       // slot 16
    virtual int GetGfxCaps(gbGfxCaps* caps);                         // slot 17
    virtual void _vf18() = 0;                                       // slot 18
    virtual void _vf19() = 0;                                       // slot 19
    virtual void _vf20() = 0;                                       // slot 20
    virtual void _vf21() = 0;                                       // slot 21
    virtual void _vf22() = 0;                                       // slot 22
    virtual void _vf23() = 0;                                       // slot 23
    virtual void _vf24() = 0;                                       // slot 24
    virtual void _vf25() = 0;                                       // slot 25
    virtual void _vf26() = 0;                                       // slot 26
    virtual void _vf27() = 0;                                       // slot 27
    virtual void SetFog(gbFogParam* pFogParam);                      // slot 28

    // === Non-virtual methods ===
    void EndScene(void);
    void SetTransform(int type, gbMatrix4* matrix);
    int ClipBoundVolume(gbAABBox* box);
    void EnableEmissive(int enable);
    void SetEmissiveFactor(float factor);
    gbColorFlt GetAmbientLight(void);
    void SetAmbientLight(const gbColorFlt& color);
    double GetDeltaTime(void);
    unsigned int GetDeltaTick(void);
    void SetSceneGraph(gbSceneGraph* sg);
    gbMatrixStack* GetMatrixStack(int index);
    gbPrintFont* GetPrintFont(gbFontType fontType);
    const gbLight* GetLight(int index) const;
    int IsLightEnable(int index) const;
    void GetTMMatrix(int type, gbMatrix4* out);
    void GetViewport(gbViewPort& pViewport);
    void SetClearParam(gbClearParam* pParam);
    void OffsetZBuffer(int enable);
    void SetWireMode(int mode);
    const gbMatrix4& GetWorldMatrix(void);
    void IdentityWorldMatrix(void);
    const gbMatrix4& GetViewMatrix(void);
    void SetCameraMatrix(const gbMatrix4& view, const gbMatrix4& proj);
    unsigned int GetCurTick(void);
    double GetCurTime(void);
    const gbGfxDriverInfo* GetDriverInfo(void);
    gbEffectMgr* GetEffectMgr(void);
    float GetEmissiveFactor(void);
    gbFogParam* GetFog(void);
    unsigned int GetGraphWnd(void);
    gbPrintFontMgr* GetPrintFontMgr(void);
    gbResManager* GetResManager(void);
    gbSceneGraph* GetSceneGraph(void);
    gbGfxStatistic* GetStatistic(void);
    gbVertPoolMgr* GetVertPoolMgr(void);
    int IsWireMode(void);
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
