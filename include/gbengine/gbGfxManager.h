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

    gbGfxManager();
    gbGfxManager(int& result, gbGfxDriverInfo* driverInfo);

    // === Virtual functions (29 slots, order matches binary vtable) ===
    virtual ~gbGfxManager();                                                        // slot 0
    virtual void MsgProc(int msg, int wParam, int lParam);                          // slot 1
    virtual gbTexture* NewTexture(const char* name);                                // slot 2
    virtual gbBaseMesh* NewMesh(const char* name, gbMeshType type);                 // slot 3
    virtual void* NewVertexPool(int poolType, int fvf, int count);                  // slot 4
    virtual void* NewIndexPool(int poolType, int indexSize, int count);             // slot 5
    virtual void* NewDynVertBuf(int fvf, int maxVerts);                             // slot 6
    virtual void SetFrustum(double l, double r, double b, double t, double n, double f);  // slot 7
    virtual void SetOrtho(double l, double r, double b, double t, double n, double f);    // slot 8
    virtual void SetViewport(void* pViewportData);                                  // slot 9
    virtual void SetLight(int index, void* pLightData);                             // slot 10
    virtual void SetMaterial(D3DMATERIAL9* pMaterial);                               // slot 11
    virtual int BeginScene(void);                                                   // slot 12
    virtual void Present();                                                         // slot 13
    virtual void DrawIndexedPrimitive(int, int, int, int, int, int, int);           // slot 14
    virtual void DrawPrimitive();                                                   // slot 15
    virtual void GetFrustumPlanes(float* outPlanes, int bNormalize);                // slot 16
    virtual int GetGfxCaps(gbGfxCaps* caps);                                        // slot 17
    virtual void ApplyTransform();                                                  // slot 18
    virtual void SetGammaRamp(void* pData);                                         // slot 19
    virtual void GetGammaRamp(int p1, int p2);                                      // slot 20
    virtual void CreateDepthStencil(int index, int param2);                         // slot 21
    virtual void RestoreDepthStencil();                                             // slot 22
    virtual void SetRenderTarget(void* pParam);                                     // slot 23
    virtual void* LoadCursor(const char* name);                                     // slot 24
    virtual void SetCursor(void* pCursor);                                          // slot 25
    virtual void ShowCursor(int bShow);                                             // slot 26
    virtual void SetSoftwareVP(int bSoftVP);                                        // slot 27
    virtual void SetFog(gbFogParam* pFogParam);                                     // slot 28

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

// ============================================================================
// CArrayList - DXSDK Summer 2003 framework dynamic array (sizeof = 0x14)
// Used extensively by CD3DEnumeration and related D3D code.
// From DXSDK\Samples\C++\Common\Include\DXUtil.h
// ============================================================================
class CArrayList {
public:
    int m_bPtrArray;      // +0x00: 0=value array, 1=pointer array
    void* m_pData;        // +0x04: data buffer
    int m_BytesPerEntry;  // +0x08: element size in bytes
    int m_NumEntries;     // +0x0C: current count
    int m_MaxEntries;     // +0x10: capacity

    void* GetPtr(int index);      // 0x10016eb0 (34B)
    int Add(void* pEntry);        // 0x10016dc0 (238B)
};

// ============================================================================
// D3DAdapterInfo - per-adapter data from D3D enumeration (sizeof = 0x458)
// From DXSDK\Samples\C++\Common\Src\D3DEnumeration.cpp
// ============================================================================
struct D3DAdapterInfo {
    unsigned int AdapterOrdinal;                   // +0x000
    D3DADAPTER_IDENTIFIER9 adapterIdentifier;      // +0x004 (sizeof=0x44C)
    CArrayList* pDisplayModeList;                  // +0x450: value array, 0x10 bytes/entry (D3DDISPLAYMODE)
    CArrayList* pDeviceInfoList;                   // +0x454: pointer array
};

// ============================================================================
// D3DDeviceInfo - per-device data from D3D enumeration (sizeof = 0x13C)
// Contains device type, caps, and list of compatible device combos.
// ============================================================================
struct D3DDeviceInfo {
    unsigned int AdapterOrdinal;                   // +0x000
    D3DDEVTYPE DevType;                            // +0x004: 1=HAL, 2=REF
    D3DCAPS9 Caps;                                 // +0x008 (sizeof=0x130)
    CArrayList* pDeviceComboList;                  // +0x138: pointer array
};

// ============================================================================
// D3DDeviceCombo - adapter format + back buffer format + windowed/fullscreen
// combination with compatible depth/stencil, multisample, etc. (sizeof >= 0x2C)
// ============================================================================
struct D3DDeviceCombo {
    unsigned int AdapterOrdinal;                   // +0x00
    D3DDEVTYPE DevType;                            // +0x04
    D3DFORMAT AdapterFormat;                       // +0x08
    D3DFORMAT BackBufferFormat;                    // +0x0C
    char bIsWindowed;                              // +0x10
    char _pad11[3];                                // +0x11: alignment
    CArrayList* pDepthStencilFormatList;           // +0x14: value array, 4 bytes/entry (D3DFORMAT)
    CArrayList* pMultiSampleTypeList;              // +0x18: value array, 4 bytes/entry
    CArrayList* pMultiSampleQualityList;           // +0x1C: value array, 4 bytes/entry
    CArrayList* pConflictList;                     // +0x20: conflict pairs
    CArrayList* pPresentIntervalList;              // +0x24: value array, 4 bytes/entry
    CArrayList* pVertexProcessingTypeList;         // +0x28: value array, 4 bytes/entry
};

// ============================================================================
// CD3DEnumeration - D3D device enumeration manager (sizeof = 0x2C)
// From DXSDK\Samples\C++\Common\Src\D3DEnumeration.cpp
// ============================================================================
typedef int (__cdecl *CONFIRMDEVICECALLBACK)(D3DCAPS9* pCaps, int vertexProcessingType,
                                             D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat);

struct CD3DEnumeration {
    IDirect3D9* m_pD3D;                            // +0x00
    CArrayList* m_pAdapterInfoList;                // +0x04: pointer array of D3DAdapterInfo*
    CONFIRMDEVICECALLBACK ConfirmDeviceCallback;   // +0x08: device filter callback
    unsigned int m_nMinWidth;                      // +0x0C
    unsigned int m_nMinHeight;                     // +0x10
    unsigned int m_nMinColorChannelBits;           // +0x14
    unsigned int m_nMinAlphaChannelBits;           // +0x18
    unsigned int m_nMinDepthBits;                  // +0x1C
    unsigned int m_nMinStencilBits;                // +0x20
    unsigned char m_bMultisampleEnabled;           // +0x24
    unsigned char _pad25;                          // +0x25
    unsigned char m_bRequireWindowed;              // +0x26
    unsigned char m_bRequireFullscreen;            // +0x27
    CArrayList* m_pAllowedAdapterFormatList;      // +0x28: value array, 4 bytes/entry (D3DFORMAT)

    int Enumerate(void);   // 0x100172f0 (1378B)
};

// ============================================================================
// D3DAPP error codes - from DXSDK\Samples\C++\Common\Include\D3DApp.h
// ============================================================================
#define D3DAPPERR_NODIRECT3D          0x82000001
#define D3DAPPERR_NOWINDOW            0x82000002
#define D3DAPPERR_NOCOMPATIBLEDEVICES 0x82000003
#define D3DAPPERR_NOWINDOWABLEDEVICES 0x82000004
#define D3DAPPERR_NOHARDWAREDEVICE    0x82000005
#define D3DAPPERR_HALNOTCOMPATIBLE    0x82000006
#define D3DAPPERR_NOWINDOWEDHAL       0x82000007
#define D3DAPPERR_NODESKTOPHAL        0x82000008
#define D3DAPPERR_NOHALTHISMODE       0x82000009
#define D3DAPPERR_NONZEROREFCOUNT     0x8200000A
#define D3DAPPERR_MEDIANOTFOUND       0x8200000B
#define D3DAPPERR_RESETFAILED         0x8200000C
#define D3DAPPERR_NULLREFDEVICE       0x8200000D

// ============================================================================
// D3DDriverBug - driver bug workaround flags
// ============================================================================
struct D3DDriverBug {
    int flags;
};

// ============================================================================
// CD3DSettings - chosen D3D device settings for fullscreen and windowed modes
// (sizeof = 0x6C)
// Layout derived from InitDeviceFullscreen/InitDeviceWindowed offset writes.
// ============================================================================
struct CD3DSettings {
    unsigned char bIsWindowed;                      // +0x00
    char _pad01[3];                                // +0x01: alignment

    // Fullscreen settings
    D3DAdapterInfo* pFullscreen_AdapterInfo;       // +0x04
    D3DDeviceInfo* pFullscreen_DeviceInfo;         // +0x08
    D3DDeviceCombo* pFullscreen_DeviceCombo;       // +0x0C
    D3DDISPLAYMODE Fullscreen_DisplayMode;         // +0x10 (Width/Height/RefreshRate/Format, 0x10 bytes)
    D3DFORMAT Fullscreen_DepthStencilFormat;       // +0x20
    D3DMULTISAMPLE_TYPE Fullscreen_MultisampleType;// +0x24
    unsigned int Fullscreen_MultisampleQuality;    // +0x28
    int Fullscreen_VertexProcessingType;           // +0x2C
    unsigned int Fullscreen_PresentInterval;       // +0x30
    int Fullscreen_Width;                          // +0x34: back buffer width
    int Fullscreen_Height;                         // +0x38: back buffer height

    // Windowed settings
    D3DAdapterInfo* pWindowed_AdapterInfo;         // +0x3C
    D3DDeviceInfo* pWindowed_DeviceInfo;           // +0x40
    D3DDeviceCombo* pWindowed_DeviceCombo;         // +0x44
    D3DDISPLAYMODE Windowed_DisplayMode;           // +0x48 (0x10 bytes)
    D3DFORMAT Windowed_DepthStencilFormat;         // +0x58
    D3DMULTISAMPLE_TYPE Windowed_MultisampleType;  // +0x5C
    unsigned int Windowed_MultisampleQuality;      // +0x60
    int Windowed_VertexProcessingType;             // +0x64
    unsigned int Windowed_PresentInterval;         // +0x68
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

    gbGfxManager_D3D();
    ~gbGfxManager_D3D();                                    // slot 0: 0x10018BB0
    gbGfxManager* InitD3D(int* pResult, gbGfxDriverInfo* info);
    void InitSubsystems(void);
    void ReleaseSubsystems(void);
    int CreateD3DDevice(void);
    void SetTexture(struct gbTextureArray* p0);

    // === Virtual function overrides (must match base class vtable order) ===
    void MsgProc(int msg, int wParam, int lParam);                          // slot 1: 0x1001B4C0
    gbTexture* NewTexture(const char* name);                                // slot 2: 0x10019040
    void* NewVertexPool(int poolType, int fvf, int count);                  // slot 4: 0x100190D0
    void* NewIndexPool(int poolType, int indexSize, int count);             // slot 5: 0x10019140
    void* NewDynVertBuf(int fvf, int maxVerts);                             // slot 6: 0x100191B0
    void SetFrustum(double l, double r, double b, double t, double n, double f);  // slot 7: 0x10019220
    void SetOrtho(double l, double r, double b, double t, double n, double f);    // slot 8: 0x100192B0
    void SetViewport(void* pViewportData);                                  // slot 9: 0x10019380
    void SetLight(int index, void* pLightData);                             // slot 10: 0x100193E0
    void SetMaterial(D3DMATERIAL9* pMaterial);                               // slot 11: 0x10019460
    int BeginScene(void);                                                   // slot 12: 0x10018CD0
    void Present();                                                         // slot 13: 0x10018F00
    void DrawIndexedPrimitive(int, int, int, int, int, int, int);           // slot 14: 0x100194F0
    void DrawPrimitive();                                                   // slot 15: 0x10019500
    void GetFrustumPlanes(float* outPlanes, int bNormalize);                // slot 16: 0x10019620
    int GetGfxCaps(gbGfxCaps* caps);                                        // slot 17: 0x1001B190
    void ApplyTransform();                                                  // slot 18: 0x10009210
    void SetGammaRamp(void* pData);                                         // slot 19: 0x1001B210
    void GetGammaRamp(int p1, int p2);                                      // slot 20: 0x1001B2B0
    void CreateDepthStencil(int index, int param2);                         // slot 21: 0x10018F40
    void RestoreDepthStencil();                                             // slot 22: 0x10019030
    void SetRenderTarget(void* pParam);                                     // slot 23: 0x1001B360
    void* LoadCursor(const char* name);                                     // slot 24: 0x1001B840
    void SetCursor(void* pCursor);                                          // slot 25: 0x1001B9D0
    void ShowCursor(int bShow);                                             // slot 26: 0x1001BA00
    void SetSoftwareVP(int bSoftVP);                                        // slot 27: 0x1001BA20
    void SetFog(gbFogParam* pFogParam);                                     // slot 28: 0x10019480

    // Internal helper methods
    int ChooseBestDevice(void);                  // 0x10019b70
    int CreateDevice(void);                      // 0x1001a790
    void BuildPresentParamsFromSettings(void);   // 0x1001a190
    char InitDeviceWindowed(int, int);           // 0x10019e70
    char InitDeviceFullscreen(int, int);         // 0x10019c60
    void DisplayErrorMsg(int hr, int type);      // 0x1001ad80
    void HandleSizeChange(void);                 // 0x1001b750
};

// Global pointer to the graphics manager
extern gbGfxManager* g_pGfxManager;
