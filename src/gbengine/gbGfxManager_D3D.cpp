/**
 * gbengine.dll - gbGfxManager_D3D
 * D3D9 graphics manager implementation
 *
 * Key functions:
 *   InitD3D         - 0x100189A0 (522B) - Full D3D initialization entry point
 *   InitSubsystems  - 0x1001DBF0 (628B) - Create engine subsystems
 *   ReleaseSubsystems - 0x1001DE70 (201B) - Destroy engine subsystems
 *   SetTexture      - 0x10005480 (115B) - Set texture stages
 *   CreateD3DDevice - 0x10019920 (479B) - D3D device creation & window setup
 */

#include "gbengine/gbGfxManager.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbengine_internal.h"
#include <windows.h>
#include <d3d9.h>
#include <string.h>

// External globals
extern gbGfxManager* g_pGfxManager;
extern gbGfxManager_D3D* g_pGfxManager_D3D;

// D3D subclasses of pool types (constructors defined in their respective .cpp files)
class gbVertexPool_D3D : public gbVertexPool {
public:
    gbVertexPool_D3D(gbPoolType type, unsigned int vertType, int total);
};

class gbIndexPool_D3D : public gbIndexPool {
public:
    gbIndexPool_D3D(gbPoolType type, int indexSz, int total);
};

class gbDynVertBuf_D3D : public gbDynVertBuf {
public:
    gbDynVertBuf_D3D(unsigned int fvfFlags, int maxVertices);
    int m_field3C;  // +0x3C: D3D vertex buffer handle
};

// Stub constructors (real implementations in separate compilation units)
gbVertexPool_D3D::gbVertexPool_D3D(gbPoolType type, unsigned int vertType, int total)
    : gbVertexPool(type, vertType, total) {}
gbIndexPool_D3D::gbIndexPool_D3D(gbPoolType type, int indexSz, int total)
    : gbIndexPool(type, indexSz, total) {}
gbDynVertBuf_D3D::gbDynVertBuf_D3D(unsigned int fvfFlags, int maxVertices)
    : gbDynVertBuf(fvfFlags, maxVertices) {}

// 0x1001B750 (226B) - Handle window size change (stub, calls Reset/GetClientRect)
void gbGfxManager_D3D::HandleSizeChange(void) {
    /* TODO: GetWindowRect, GetClientRect, device Reset */
}

// DXT compressed texture format FourCC codes
#define FOURCC_DXT1  0x31545844  // 'DXT1'
#define FOURCC_DXT2  0x32545844  // 'DXT2'
#define FOURCC_DXT3  0x33545844  // 'DXT3'
#define FOURCC_DXT4  0x34545844  // 'DXT4'
#define FOURCC_DXT5  0x35545844  // 'DXT5'

// ============================================================================
// 0x10005480 (115B) - gbGfxManager_D3D::SetTexture
// Sets texture stages on D3D device, clears unused stages
// ============================================================================
void gbGfxManager_D3D::SetTexture(gbTextureArray* texArray) {
    int stage = 0;

    if (!texArray || texArray->numTextures <= 0)
        goto clearRemaining;

    do {
        gbTexture* tex = texArray->pTex[stage];
        if (tex != m_pCurTexture[stage]) {
            if (tex)
                m_pd3dDevice->SetTexture(stage, (IDirect3DBaseTexture9*)tex->GetTexture());
            else
                m_pd3dDevice->SetTexture(stage, NULL);
            m_pCurTexture[stage] = tex;
        }
        stage++;
    } while (stage < texArray->numTextures);

    if (stage >= 4) return;

clearRemaining:
    do {
        if (m_pCurTexture[stage]) {
            m_pd3dDevice->SetTexture(stage, NULL);
            m_pCurTexture[stage] = NULL;
        }
        stage++;
    } while (stage < 4);
}

// ============================================================================
// gbGfxManager_D3D default constructor (used by operator new in factory)
// ============================================================================
gbGfxManager_D3D::gbGfxManager_D3D() {
    memset(&m_d3dEnumeration, 0, sizeof(m_d3dEnumeration));
    m_bWindowed = 1;
    m_hWnd = NULL;
    m_bMinimized = 0;
    m_bMaximized = 0;
    m_bActive = 0;
    m_dwCreateFlags = 0;
    m_pD3D = NULL;
    m_pd3dDevice = NULL;
    m_pBackBuffer = NULL;
    m_pCacheVB = NULL;
    m_pCacheIB = NULL;
    m_bDeviceLost = 0;
    m_ErrorCode = 0;
    m_bShowCursor = 0;
    m_pActiveCursor = NULL;
    m_bSoftVPMode = 0;
}

// ============================================================================
// 0x100189A0 (522B) - gbGfxManager_D3D::InitD3D
// Full D3D initialization: base class init, D3D device creation, subsystems
// __thiscall, params: int* pResult (success flag), gbGfxDriverInfo* info
// Called from gbCreateGraphManager
// ============================================================================
gbGfxManager* gbGfxManager_D3D::InitD3D(int* pResult, gbGfxDriverInfo* info) {
    int result = 0;

    // Initialize base class with driver info
    gbGfxManager::gbGfxManager(result, info);

    // Initialize CD3DEnumeration at +0x5F0
    // FUN_100170d0 initializes the D3D enumeration structure
    memset(&m_d3dEnumeration, 0, sizeof(m_d3dEnumeration));

    // Initialize cursor resource manager at +0x658
    // gbResManager::gbResManager inline - just zeroes
    memset(m_CursorMgr, 0, sizeof(m_CursorMgr));

    // Set vtable to gbGfxManager_D3D's vtable (done by compiler)

    // Initialize D3D-specific state
    m_bDeviceLost = 0;
    m_hWnd = NULL;
    m_bActive = 0;
    m_bMinimized = 0;
    m_bMaximized = 0;
    m_bShowCursorWhenFullscreen = 0;
    m_bClipCursorWhenFullscreen = 1;
    m_pActiveCursor = NULL;
    m_bShowCursor = 1;

    // Set global pointer
    g_pGfxManager_D3D = this;
    gbColorQuad::ColorQuadFmt = 0;

    // Clear D3D pointers
    m_pD3D = NULL;
    m_pd3dDevice = NULL;

    // Create D3D device and window
    int hwnd = CreateD3DDevice();
    hGfxWnd = hwnd;

    if (hwnd == 0) {
        *pResult = 0;
        return this;
    }

    // Create texture resource manager (0x828 bytes for gbResManager with texture cache)
    gbResManager* texResMgr = new gbResManager();
    pEffectMgr = (gbEffectMgr*)texResMgr;

    // Initialize all subsystems (MatrixStack, VertPoolMgr, EffectMgr, FontMgr, SceneGraph)
    InitSubsystems();

    // Check DXT texture format support
    {
        unsigned int dxtFormats[5] = { FOURCC_DXT1, FOURCC_DXT2, FOURCC_DXT3, FOURCC_DXT4, FOURCC_DXT5 };
        int i;

        for (i = 0; i < 5; i++) {
            D3DFORMAT adapterFormat;
            if (*(unsigned char*)((char*)&m_d3dSettings + 0) == 0) {
                // Fullscreen: use format from fullscreen settings
                adapterFormat = *(D3DFORMAT*)((char*)&m_d3dSettings + 0x44);
            } else {
                // Windowed: use format from windowed settings
                adapterFormat = *(D3DFORMAT*)((char*)&m_d3dSettings + 0x0C);
            }

            HRESULT hr = m_pD3D->CheckDeviceFormat(
                0,  // adapter
                D3DDEVTYPE_HAL,
                adapterFormat,
                0,  // usage
                D3DRTYPE_TEXTURE,
                (D3DFORMAT)dxtFormats[i]
            );
            m_DXTSupported[i] = (hr >= 0) ? 1 : 0;
        }
    }

    *pResult = 1;
    m_bActive = 1;

    return this;
}

// ============================================================================
// 0x1001DBF0 (628B) - gbGfxManager_D3D::InitSubsystems
// Creates all engine subsystems: MatrixStack, VertPoolMgr, EffectMgr, FontMgr, SceneGraph
// Called from InitD3D after D3D device is successfully created
// ============================================================================
void gbGfxManager_D3D::InitSubsystems(void) {
    // Create 4 matrix stacks (view=8 deep, world=16 deep, tex0=4, tex1=4)
    pMatrixStack[0] = new gbMatrixStack(8);
    pMatrixStack[1] = new gbMatrixStack(16);
    pMatrixStack[2] = new gbMatrixStack(4);
    pMatrixStack[3] = new gbMatrixStack(4);

    // Create vertex pool manager
    pVertPoolMgr = new gbVertPoolMgr(this, 0x10000, 0x10000, 0x4000, 0x4000);

    // Query D3D caps via virtual call (slot 17 = GetGfxCaps)
    gbGfxCaps caps;
    GetGfxCaps(&caps);

    // Create texture resource manager
    pTexResMgr = new gbResManager();

    // Set global pointer
    g_pGfxManager = this;

    // Initialize effect manager (at pEffectMgr, already allocated)
    pEffectMgr->Init(this);

    // Create print font manager
    gbPrintFontMgr* fontMgr = new gbPrintFontMgr();
    pFontMgr = fontMgr;
    fontMgr->Init(this);

    // Create scene graph
    gbVec3D origin;
    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;
    pSceneGraph = new gbSceneGraph(this, origin, 10000.0f);

    // Initialize clear parameters (black color, depth 1.0, stencil 0, flags 3)
    ClearParam.color = 0xFF000000;
    ClearParam.depth = 1.0f;
    ClearParam.stencil = 0;
    ClearParam.flags = 3;

    // Clear all light enable flags
    memset(LightEnable, 0, sizeof(LightEnable));

    // Reset Z-bias
    CurZBias = 0;
}

// ============================================================================
// 0x1001DE70 (201B) - gbGfxManager_D3D::ReleaseSubsystems
// Destroys all engine subsystems in reverse order
// Called from destructor
// ============================================================================
void gbGfxManager_D3D::ReleaseSubsystems(void) {
    int i;

    // Delete scene graph
    if (pSceneGraph) {
        pSceneGraph->~gbSceneGraph();
        operator delete(pSceneGraph);
    }
    pSceneGraph = NULL;

    // Release and delete print font manager
    if (pFontMgr) {
        pFontMgr->Release();
        operator delete(pFontMgr);
    }
    pFontMgr = NULL;

    // Release effect manager (don't delete - it's the texture res mgr)
    if (pEffectMgr) {
        pEffectMgr->Release();
    }

    // Delete texture resource manager
    if (pTexResMgr) {
        delete pTexResMgr;
    }
    pTexResMgr = NULL;

    // Delete vertex pool manager
    if (pVertPoolMgr) {
        delete pVertPoolMgr;
    }
    pVertPoolMgr = NULL;

    // Delete all matrix stacks
    for (i = 0; i < 4; i++) {
        if (pMatrixStack[i]) {
            delete pMatrixStack[i];
        }
        pMatrixStack[i] = NULL;
    }
}

// ============================================================================
// 0x10019920 (479B) - gbGfxManager_D3D::CreateD3DDevice
// Creates D3D9 interface, window, and device
// Returns: HWND handle on success, 0 on failure
// ============================================================================
int gbGfxManager_D3D::CreateD3DDevice(void) {
    RECT rc;

    // 1. Create D3D9 interface
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (m_pD3D == NULL) {
        DisplayErrorMsg(D3DAPPERR_NODIRECT3D, 2);
        return 0;
    }

    // 2. Enumerate and choose best device settings
    int hr = ChooseBestDevice();
    if (hr < 0) {
        DisplayErrorMsg(hr, 2);
        return 0;
    }

    // 3. Set window style based on fullscreen mode
    if (DrvInfo.fullscreen == 0) {
        // Fullscreen style (WS_POPUP | WS_VISIBLE typically)
        m_dwWindowStyle = WS_POPUP | WS_SYSMENU;
    } else {
        // Windowed style (WS_OVERLAPPEDWINDOW typically)
        m_dwWindowStyle = WS_OVERLAPPEDWINDOW;
    }

    // 4. Create or reuse window
    if (DrvInfo.newwindow == 0) {
        // Use existing window handle
        m_hWnd = (HWND)DrvInfo.hgfxwnd;
    } else {
        // Create a new window
        SetRect(&rc, 0, 0, DrvInfo.width, DrvInfo.height);
        AdjustWindowRect(&rc, m_dwWindowStyle, FALSE);

        m_hWnd = CreateWindowExA(
            0,
            DrvInfo.winname,     // class name
            DrvInfo.winname,     // window title
            m_dwWindowStyle,
            0, 0,
            rc.right - rc.left,
            rc.bottom - rc.top,
            NULL,
            NULL,
            (HINSTANCE)DrvInfo.hinst,
            NULL
        );

        if (m_hWnd == NULL) {
            return 0;
        }

        ShowWindow(m_hWnd, SW_SHOW);
    }

    // 5. Get actual window style and dimensions
    m_dwWindowStyle = GetWindowLongA(m_hWnd, GWL_STYLE);
    GetWindowRect(m_hWnd, &m_rcWindowBounds);
    GetClientRect(m_hWnd, &m_rcWindowClient);

    // Update driver info with actual client dimensions
    DrvInfo.height = m_rcWindowClient.bottom - m_rcWindowClient.top;
    DrvInfo.hgfxwnd = (unsigned int)m_hWnd;
    DrvInfo.width = m_rcWindowClient.right - m_rcWindowClient.left;

    // 6. Initialize D3D device (fullscreen or windowed)
    char success;
    if (DrvInfo.fullscreen != 0) {
        success = InitDeviceWindowed(1, 0);
    } else {
        success = InitDeviceFullscreen(1, 0);
    }

    if (!success) {
        // If fullscreen failed, try windowed as fallback
        if (DrvInfo.fullscreen == 0) {
            DrvInfo.fullscreen = 1;
            success = InitDeviceWindowed(1, 0);
            if (!success) {
                return 0;
            }
        } else {
            return 0;
        }
    }

    // 7. Final device creation step (back buffer, caps, etc.)
    hr = CreateDevice();
    if (hr < 0) {
        DisplayErrorMsg(hr, 2);
        return 0;
    }

    return (int)m_hWnd;
}

// ============================================================================
// Internal helper methods
// ============================================================================

// Callback for D3D enumeration (at 0x10019b00)
static int __cdecl ConfirmDeviceCallback(void) { return 1; }

// 0x10019b70 (232B) - Initialize enumeration params and enumerate devices
int gbGfxManager_D3D::ChooseBestDevice(void) {
    // Store D3D object pointer into enumeration structure
    m_d3dEnumeration.m_pD3D = m_pD3D;

    if (DrvInfo.fullscreen != 0) {
        // Windowed mode: set desired resolution
        m_d3dEnumeration.m_nMinWidth = DrvInfo.width;
        m_d3dEnumeration.m_nMinHeight = DrvInfo.height;
    }

    // Set color depth preference (16bit -> 5 channel bits, else 8)
    if (DrvInfo.colorbits == 16) {
        m_d3dEnumeration.m_nMinColorChannelBits = 5;
    } else {
        m_d3dEnumeration.m_nMinColorChannelBits = 8;
    }

    // Set depth buffer bits
    m_d3dEnumeration.m_nMinAlphaChannelBits = 0;
    m_d3dEnumeration.m_nMinDepthBits = 16;
    m_d3dEnumeration.m_nMinStencilBits = 0;
    m_d3dEnumeration.m_bMultisampleEnabled = 1;

    if (DrvInfo.fullscreen == 0) {
        m_d3dEnumeration.m_bRequireWindowed = 1;
    }

    // Set confirm device callback
    m_d3dEnumeration.ConfirmDeviceCallback = (CONFIRMDEVICECALLBACK)ConfirmDeviceCallback;

    // Run enumeration
    int hr = m_d3dEnumeration.Enumerate();
    if (hr < 0) {
        m_pD3D->Release();
        m_pD3D = NULL;
        DisplayErrorMsg(hr, 2);
        return hr;
    }

    return 0;
}

// 0x1001a790 (1208B) - Create actual D3D device with chosen settings
// Builds D3DPRESENT_PARAMETERS, calls IDirect3D9::CreateDevice,
// gets caps, back buffer desc, builds device stats string.
int gbGfxManager_D3D::CreateDevice(void) {
    D3DDeviceCombo* pDeviceCombo;

    if (m_d3dSettings.bIsWindowed == 0) {
        pDeviceCombo = m_d3dSettings.pWindowed_DeviceCombo;
    } else {
        pDeviceCombo = m_d3dSettings.pFullscreen_DeviceCombo;
    }

    // Set window style
    m_bWindowed = (unsigned int)m_d3dSettings.bIsWindowed;
    if (m_d3dSettings.bIsWindowed == 0) {
        // Fullscreen
        HWND hWnd = m_hWnd;
        SetWindowLongA(hWnd, GWL_STYLE, (int)m_dwWindowStyle);
    } else {
        // Windowed - remove borders
        HWND hWnd = m_hWnd;
        SetWindowLongA(hWnd, GWL_STYLE, WS_POPUP | WS_SYSMENU);
    }

    // Zero out D3DPRESENT_PARAMETERS
    memset(&m_d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));

    // Build present parameters based on settings
    // TODO: BuildPresentParamsFromSettings (complex sub-function at 0x1001a190)
    // For now, set basic parameters
    m_d3dpp.Windowed = m_d3dSettings.bIsWindowed ? FALSE : TRUE;
    m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    m_d3dpp.hDeviceWindow = m_hWnd;

    if (m_d3dSettings.bIsWindowed == 0) {
        // Windowed mode
        m_d3dpp.BackBufferWidth = 0;
        m_d3dpp.BackBufferHeight = 0;
        m_d3dpp.BackBufferFormat = m_d3dSettings.Windowed_DisplayMode.Format;
        m_d3dpp.EnableAutoDepthStencil = TRUE;
        m_d3dpp.AutoDepthStencilFormat = m_d3dSettings.Windowed_DepthStencilFormat;
        m_d3dpp.MultiSampleType = m_d3dSettings.Windowed_MultisampleType;
        m_d3dpp.MultiSampleQuality = m_d3dSettings.Windowed_MultisampleQuality;
        m_d3dpp.PresentationInterval = m_d3dSettings.Windowed_PresentInterval;
    } else {
        // Fullscreen mode
        m_d3dpp.BackBufferWidth = m_d3dSettings.Fullscreen_Width;
        m_d3dpp.BackBufferHeight = m_d3dSettings.Fullscreen_Height;
        m_d3dpp.BackBufferFormat = m_d3dSettings.Fullscreen_DisplayMode.Format;
        m_d3dpp.FullScreen_RefreshRateInHz = m_d3dSettings.Fullscreen_DisplayMode.RefreshRate;
        m_d3dpp.EnableAutoDepthStencil = TRUE;
        m_d3dpp.AutoDepthStencilFormat = m_d3dSettings.Fullscreen_DepthStencilFormat;
        m_d3dpp.MultiSampleType = m_d3dSettings.Fullscreen_MultisampleType;
        m_d3dpp.MultiSampleQuality = m_d3dSettings.Fullscreen_MultisampleQuality;
        m_d3dpp.PresentationInterval = m_d3dSettings.Fullscreen_PresentInterval;
    }

    m_d3dpp.BackBufferCount = 1;

    // Check device combo behavior flags for pure device
    if ((*(unsigned int*)&pDeviceCombo->pVertexProcessingTypeList & 0x1000) != 0) {
        // TODO: handle pure device case
    }

    // Determine vertex processing type
    m_bSoftVPMode = 0;
    int vertexProcessingType;
    if (m_d3dSettings.bIsWindowed == 0) {
        vertexProcessingType = m_d3dSettings.Windowed_VertexProcessingType;
    } else {
        vertexProcessingType = m_d3dSettings.Fullscreen_VertexProcessingType;
    }

    // Set create flags based on vertex processing type
    if (vertexProcessingType == 0) {
        m_dwCreateFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
        m_bSoftVPMode = 1;
    } else if (vertexProcessingType == 1) {
        m_dwCreateFlags = D3DCREATE_MIXED_VERTEXPROCESSING;
    } else if (vertexProcessingType == 2) {
        m_dwCreateFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    } else {
        m_dwCreateFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
    }

    // Create the D3D device
    HRESULT hr = m_pD3D->CreateDevice(
        0,                  // adapter
        D3DDEVTYPE_HAL,
        m_hWnd,
        m_dwCreateFlags,
        &m_d3dpp,
        &m_pd3dDevice
    );

    if (FAILED(hr)) {
        return hr;
    }

    // Get device caps
    m_pd3dDevice->GetDeviceCaps(&m_d3dCaps);

    // Get back buffer surface desc
    IDirect3DSurface9* pBackBuffer = NULL;
    m_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
    if (pBackBuffer) {
        pBackBuffer->GetDesc(&m_d3dsdBackBuffer);
        pBackBuffer->Release();
    }

    // Update DrvInfo with actual dimensions
    DrvInfo.width = m_d3dpp.BackBufferWidth;
    DrvInfo.height = m_d3dpp.BackBufferHeight;

    // Set window position for fullscreen
    if (!m_d3dSettings.bIsWindowed) {
        SetWindowPos(m_hWnd, NULL,
            m_rcWindowBounds.left, m_rcWindowBounds.top,
            m_rcWindowBounds.right - m_rcWindowBounds.left,
            m_rcWindowBounds.bottom - m_rcWindowBounds.top,
            SWP_NOZORDER);
    }

    // Build device stats string
    m_strDeviceStats[0] = '\0';

    // Clip cursor in fullscreen if requested
    if (m_bShowCursorWhenFullscreen && m_bWindowed == 0) {
        DWORD dwIcon = GetClassLongA(m_hWnd, GCL_HICON);
        // TODO: cursor setup
    }
    if (m_bClipCursorWhenFullscreen) {
        if (m_bWindowed == 0) {
            RECT rc;
            GetWindowRect(m_hWnd, &rc);
            ClipCursor(&rc);
        } else {
            ClipCursor(NULL);
        }
    }

    return 0;
}

// 0x10019e70 (794B) - Find best windowed mode settings
// Iterates adapters/devices/combos to find best windowed configuration.
// p1: bRequireHAL, p2: bRequireREF
char gbGfxManager_D3D::InitDeviceWindowed(int p1, int p2) {
    D3DAdapterInfo* pBestAdapterInfo = NULL;
    D3DDeviceInfo* pBestDeviceInfo = NULL;
    D3DDeviceCombo* pBestDeviceCombo = NULL;

    unsigned int iAdapter;
    for (iAdapter = 0; iAdapter < (unsigned int)m_d3dEnumeration.m_pAdapterInfoList->m_NumEntries; iAdapter++) {
        D3DAdapterInfo* pAdapterInfo = *(D3DAdapterInfo**)m_d3dEnumeration.m_pAdapterInfoList->GetPtr(iAdapter);

        // Get current desktop display mode for this adapter
        D3DDISPLAYMODE adapterDesktopMode;
        m_pD3D->GetAdapterDisplayMode(pAdapterInfo->AdapterOrdinal, &adapterDesktopMode);

        // Determine target format based on DrvInfo color depth
        D3DFORMAT targetFmt;
        if (DrvInfo.colorbits == 16) {
            targetFmt = D3DFMT_R5G6B5;  // 0x17
        } else {
            targetFmt = D3DFMT_X8R8G8B8; // 0x16
        }

        unsigned int iDevice;
        for (iDevice = 0; iDevice < (unsigned int)pAdapterInfo->pDeviceInfoList->m_NumEntries; iDevice++) {
            D3DDeviceInfo* pDeviceInfo = *(D3DDeviceInfo**)pAdapterInfo->pDeviceInfoList->GetPtr(iDevice);

            if (p1 != 0 && pDeviceInfo->DevType != D3DDEVTYPE_HAL)
                continue;
            if (p2 != 0 && pDeviceInfo->DevType != D3DDEVTYPE_REF)
                continue;

            unsigned int iCombo;
            for (iCombo = 0; iCombo < (unsigned int)pDeviceInfo->pDeviceComboList->m_NumEntries; iCombo++) {
                D3DDeviceCombo* pDeviceCombo = *(D3DDeviceCombo**)pDeviceInfo->pDeviceComboList->GetPtr(iCombo);

                int adapterFmt = (int)pDeviceCombo->AdapterFormat;
                int bBackMatch = ((int)pDeviceCombo->BackBufferFormat == adapterFmt);
                int bFmtTarget = (adapterFmt == (int)targetFmt);

                // Must be windowed mode combo (bIsWindowed == 0 means "not fullscreen only")
                if (pDeviceCombo->bIsWindowed == 0) {
                    // Selection priority: HAL > REF, matching format > not, backbuf match
                    if (pBestDeviceCombo == NULL ||
                        (pBestDeviceInfo->DevType != D3DDEVTYPE_HAL && pDeviceInfo->DevType == D3DDEVTYPE_HAL) ||
                        (pDeviceInfo->DevType == D3DDEVTYPE_HAL &&
                         (((int)pBestDeviceCombo->AdapterFormat != (int)targetFmt && bFmtTarget) ||
                          (bFmtTarget && bBackMatch)))) {
                        pBestAdapterInfo = pAdapterInfo;
                        pBestDeviceInfo = pDeviceInfo;
                        pBestDeviceCombo = pDeviceCombo;

                        if (pDeviceInfo->DevType == D3DDEVTYPE_HAL && bFmtTarget && bBackMatch) {
                            goto LAB_1001a032;
                        }
                    }
                }
            }
        }
    }

LAB_1001a032:
    if (pBestDeviceCombo == NULL) {
        return 0;
    }

    // Find best display mode from adapter's mode list
    int bestWidth = 0;
    int bestHeight = 0;
    int bestRefresh = 0;
    unsigned int iMode;
    for (iMode = 0; iMode < (unsigned int)pBestAdapterInfo->pDisplayModeList->m_NumEntries; iMode++) {
        D3DDISPLAYMODE* pMode = (D3DDISPLAYMODE*)pBestAdapterInfo->pDisplayModeList->GetPtr(iMode);

        if ((D3DFORMAT)pMode->Format == pBestDeviceCombo->AdapterFormat) {
            int w = (int)pMode->Width;
            if (w == DrvInfo.width) {
                if ((int)pMode->Height == DrvInfo.height && (int)pMode->RefreshRate == DrvInfo.refreshrate) {
                    bestWidth = w;
                    bestHeight = (int)pMode->Height;
                    bestRefresh = (int)pMode->RefreshRate;
                    break;
                }
            }
            // Track best candidate
            if (w >= bestWidth) {
                bestWidth = w;
                bestHeight = (int)pMode->Height;
                bestRefresh = (int)pMode->RefreshRate;
            }
        }
    }

    // Store windowed settings
    m_d3dSettings.pWindowed_AdapterInfo = pBestAdapterInfo;
    m_d3dSettings.pWindowed_DeviceInfo = pBestDeviceInfo;
    m_d3dSettings.pWindowed_DeviceCombo = pBestDeviceCombo;
    m_d3dSettings.bIsWindowed = 0;

    m_d3dSettings.Windowed_DisplayMode.Width = bestWidth;
    m_d3dSettings.Windowed_DisplayMode.Height = bestHeight;
    m_d3dSettings.Windowed_DisplayMode.RefreshRate = bestRefresh;
    m_d3dSettings.Windowed_DisplayMode.Format = pBestDeviceCombo->AdapterFormat;

    // Depth/stencil format: first entry from combo's list
    if (m_d3dEnumeration.m_bMultisampleEnabled) {
        m_d3dSettings.Windowed_DepthStencilFormat = *(D3DFORMAT*)pBestDeviceCombo->pDepthStencilFormatList->GetPtr(0);
    }

    // Multisample
    m_d3dSettings.Windowed_MultisampleType = *(D3DMULTISAMPLE_TYPE*)pBestDeviceCombo->pMultiSampleTypeList->GetPtr(0);
    m_d3dSettings.Windowed_MultisampleQuality = 0;

    // Vertex processing: first entry
    m_d3dSettings.Windowed_VertexProcessingType = *(int*)pBestDeviceCombo->pVertexProcessingTypeList->GetPtr(0);
    m_d3dSettings.Windowed_PresentInterval = 0;

    return 1;
}

// 0x10019c60 (525B) - Find best fullscreen mode settings
// Iterates adapters/devices/combos to find best fullscreen configuration.
// p1: bRequireHAL, p2: bRequireREF
char gbGfxManager_D3D::InitDeviceFullscreen(int p1, int p2) {
    // Get current adapter display mode format
    D3DDISPLAYMODE adapterDesktopMode;
    m_pD3D->GetAdapterDisplayMode(0, &adapterDesktopMode);

    D3DAdapterInfo* pBestAdapterInfo = NULL;
    D3DDeviceInfo* pBestDeviceInfo = NULL;
    D3DDeviceCombo* pBestDeviceCombo = NULL;

    unsigned int iAdapter;
    for (iAdapter = 0; iAdapter < (unsigned int)m_d3dEnumeration.m_pAdapterInfoList->m_NumEntries; iAdapter++) {
        D3DAdapterInfo* pAdapterInfo = *(D3DAdapterInfo**)m_d3dEnumeration.m_pAdapterInfoList->GetPtr(iAdapter);

        unsigned int iDevice;
        for (iDevice = 0; iDevice < (unsigned int)pAdapterInfo->pDeviceInfoList->m_NumEntries; iDevice++) {
            D3DDeviceInfo* pDeviceInfo = *(D3DDeviceInfo**)pAdapterInfo->pDeviceInfoList->GetPtr(iDevice);

            if (p1 != 0 && pDeviceInfo->DevType != D3DDEVTYPE_HAL)
                continue;
            if (p2 != 0 && pDeviceInfo->DevType != D3DDEVTYPE_REF)
                continue;

            unsigned int iCombo;
            for (iCombo = 0; iCombo < (unsigned int)pDeviceInfo->pDeviceComboList->m_NumEntries; iCombo++) {
                D3DDeviceCombo* pDeviceCombo = *(D3DDeviceCombo**)pDeviceInfo->pDeviceComboList->GetPtr(iCombo);

                int adapterFmt = (int)pDeviceCombo->AdapterFormat;
                int bFmtMatch = ((int)pDeviceCombo->BackBufferFormat == adapterFmt);

                if (pDeviceCombo->bIsWindowed != 0 &&
                    adapterFmt == (int)adapterDesktopMode.Format) {
                    // Prefer: HAL device, matching formats
                    if (pBestDeviceCombo == NULL ||
                        (pBestDeviceInfo->DevType != D3DDEVTYPE_HAL && pDeviceInfo->DevType == D3DDEVTYPE_HAL) ||
                        (pDeviceInfo->DevType == D3DDEVTYPE_HAL &&
                         ((int)pBestDeviceCombo->AdapterFormat != (int)adapterDesktopMode.Format && adapterFmt == (int)adapterDesktopMode.Format) ||
                         (adapterFmt == (int)adapterDesktopMode.Format && bFmtMatch))) {
                        pBestAdapterInfo = pAdapterInfo;
                        pBestDeviceInfo = pDeviceInfo;
                        pBestDeviceCombo = pDeviceCombo;
                    }
                }
            }
        }
    }

    if (pBestDeviceCombo == NULL) {
        return 0;
    }

    // Store fullscreen settings
    m_d3dSettings.pFullscreen_AdapterInfo = pBestAdapterInfo;
    m_d3dSettings.pFullscreen_DeviceInfo = pBestDeviceInfo;
    m_d3dSettings.pFullscreen_DeviceCombo = pBestDeviceCombo;
    m_d3dSettings.bIsWindowed = 1;

    // Display mode
    m_d3dSettings.Fullscreen_DisplayMode.Width = adapterDesktopMode.Width;
    m_d3dSettings.Fullscreen_DisplayMode.Height = adapterDesktopMode.Height;
    m_d3dSettings.Fullscreen_DisplayMode.RefreshRate = adapterDesktopMode.RefreshRate;
    m_d3dSettings.Fullscreen_DisplayMode.Format = (D3DFORMAT)(int)adapterDesktopMode.Format;

    // Back buffer dimensions from window client rect
    m_d3dSettings.Fullscreen_Width = m_rcWindowClient.right - m_rcWindowClient.left;
    m_d3dSettings.Fullscreen_Height = m_rcWindowClient.bottom - m_rcWindowClient.top;

    // Depth/stencil format: first entry from combo's list
    if (m_d3dEnumeration.m_bMultisampleEnabled) {
        m_d3dSettings.Fullscreen_DepthStencilFormat = *(D3DFORMAT*)pBestDeviceCombo->pDepthStencilFormatList->GetPtr(0);
    }

    // Multisample: first entry
    m_d3dSettings.Fullscreen_MultisampleType = *(D3DMULTISAMPLE_TYPE*)pBestDeviceCombo->pMultiSampleTypeList->GetPtr(0);
    m_d3dSettings.Fullscreen_MultisampleQuality = 0;

    // Vertex processing: first entry
    m_d3dSettings.Fullscreen_VertexProcessingType = *(int*)pBestDeviceCombo->pVertexProcessingTypeList->GetPtr(0);

    // Present interval: first entry
    m_d3dSettings.Fullscreen_PresentInterval = *(unsigned int*)pBestDeviceCombo->pPresentIntervalList->GetPtr(0);

    return 1;
}

// 0x1001ad80 (393B) - Display D3D error message via MessageBox
void gbGfxManager_D3D::DisplayErrorMsg(int hr, int type) {
    char buf[512];
    const char* msg;

    switch ((unsigned int)hr) {
    case D3DAPPERR_NODIRECT3D: msg = "Could not find a compatible Direct3D device."; break;
    case D3DAPPERR_NOCOMPATIBLEDEVICES: msg = "Could not find any compatible Direct3D devices."; break;
    case D3DAPPERR_NOWINDOWABLEDEVICES: msg = "This sample cannot run in a desktop of this color depth."; break;
    case D3DAPPERR_NOHARDWAREDEVICE: msg = "No hardware-accelerated Direct3D devices were found."; break;
    case D3DAPPERR_HALNOTCOMPATIBLE: msg = "This sample requires functionality not available on your device."; break;
    case D3DAPPERR_NOWINDOWEDHAL: msg = "Your Direct3D hardware accelerator cannot render into a window."; break;
    case D3DAPPERR_NODESKTOPHAL: msg = "Your Direct3D hardware accelerator cannot handle the required texture format."; break;
    case D3DAPPERR_NOHALTHISMODE: msg = "This sample requires functionality not available on your Direct3D hardware accelerator."; break;
    case D3DAPPERR_NONZEROREFCOUNT: msg = "A D3D object has a non-zero reference count."; break;
    case D3DAPPERR_MEDIANOTFOUND: msg = "Could not load required media."; break;
    case D3DAPPERR_RESETFAILED: msg = "Could not reset the Direct3D device."; break;
    case D3DAPPERR_NULLREFDEVICE: msg = "Warning: Nothing will be rendered."; break;
    case (unsigned int)E_OUTOFMEMORY: msg = "Not enough memory."; break;
    case (unsigned int)D3DERR_OUTOFVIDEOMEMORY: msg = "Not enough video memory."; break;
    default: msg = "Generic application error. Enable debug output for more information."; break;
    }

    strcpy(buf, msg);

    if (type == 2) {
        MessageBoxA(NULL, buf, "error", MB_ICONERROR);
    } else {
        if (type == 1) {
            strcat(buf, "\nSwitching to the reference rasterizer.");
        }
        MessageBoxA(NULL, buf, "warning", MB_ICONWARNING);
    }
}

// ============================================================================
// gbGfxManager_D3D virtual function overrides
// These override the base class empty stubs to produce the correct vtable.
// ============================================================================

// Slot 0: 0x10018BB0 (30B) - Destructor
gbGfxManager_D3D::~gbGfxManager_D3D() {
    ReleaseSubsystems();
    if (m_pd3dDevice) {
        m_pd3dDevice->Release();
        m_pd3dDevice = NULL;
    }
    if (m_pD3D) {
        m_pD3D->Release();
        m_pD3D = NULL;
    }
}

// Slot 1: 0x1001B4C0 (653B) - Window message dispatch handler
void gbGfxManager_D3D::MsgProc(int msg, int wParam, int lParam) {
    unsigned int uMsg = (unsigned int)msg;
    unsigned int uWParam = (unsigned int)wParam;

    if (uMsg <= WM_MOUSEMOVE) {
        if (uMsg == WM_MOUSEMOVE) {
            // Update D3D hardware cursor position
            if (m_bActive != 0 && m_pd3dDevice != NULL) {
                POINT pt;
                GetCursorPos(&pt);
                if (m_bWindowed == 0) {
                    ScreenToClient(m_hWnd, &pt);
                }
                m_pd3dDevice->SetCursorPosition(pt.x, pt.y, 0);
            }
            return;
        }

        if (uMsg <= WM_GETMINMAXINFO) {
            if (uMsg == WM_GETMINMAXINFO) {
                // Set minimum window size
                MINMAXINFO* mmi = (MINMAXINFO*)lParam;
                mmi->ptMinTrackSize.x = 100;
                mmi->ptMinTrackSize.y = 100;
                return;
            }

            if (uMsg == WM_SIZE) {
                if (m_bWindowed != 0 && m_hWnd != NULL) {
                    m_dwWindowStyle = GetWindowLongA(m_hWnd, GWL_STYLE);
                }

                if (uWParam == SIZE_MINIMIZED) {
                    if (m_bClipCursorWhenFullscreen != 0 && m_bWindowed == 0) {
                        ClipCursor(NULL);
                    }
                    m_bActive = 0;
                    m_bMinimized = 1;
                    m_bMaximized = 0;
                    return;
                }

                if (uWParam == SIZE_MAXIMIZED) {
                    if (m_bMinimized != 0) {
                        m_bActive = 1;
                    }
                    m_bMinimized = 0;
                    m_bMaximized = 1;
                    HandleSizeChange();
                    return;
                }

                if (uWParam == SIZE_RESTORED) {
                    if (m_bMaximized != 0) {
                        m_bMaximized = 0;
                        HandleSizeChange();
                        return;
                    }
                    if (m_bMinimized != 0) {
                        m_bActive = 1;
                        m_bMinimized = 0;
                        HandleSizeChange();
                        return;
                    }
                }
            } else if (uMsg == WM_SETCURSOR) {
                if (m_bActive != 0) {
                    if (m_pActiveCursor == NULL) {
                        return;
                    }
                    SetCursor(NULL);
                    m_pd3dDevice->ShowCursor(m_bShowCursor);
                    return;
                }
            }
        } else if (uMsg == WM_SYSCOMMAND) {
            // Filter system commands
            if (uWParam > SC_MAXIMIZE) {
                if (uWParam != SC_KEYMENU && uWParam != 0xF170) {
                    return;
                }
            } else {
                if (uWParam != SC_MAXIMIZE && uWParam != SC_SIZE && uWParam != SC_MOVE) {
                    return;
                }
            }
            if (m_bWindowed == 0) {
                return;
            }
        }
    } else if (uMsg == WM_POWERBROADCAST) {
        if (uWParam == PBT_APMQUERYSUSPEND || uWParam == PBT_APMRESUMESUSPEND) {
            return;
        }
    } else {
        if (uMsg == WM_ENTERSIZEMOVE) {
            m_bActive = 0;
            return;
        }
        if (uMsg == WM_EXITSIZEMOVE) {
            m_bActive = 1;
            HandleSizeChange();
            return;
        }
    }
}

// Slot 2: 0x10019040 (133B) - Create gbTexture_D3D object
gbTexture* gbGfxManager_D3D::NewTexture(const char* name) {
    gbTexture_D3D* tex = new gbTexture_D3D();
    if (!tex) return NULL;
    tex->SetName(name);
    return tex;
}

// Slot 4: 0x100190D0 (106B) - Create gbVertexPool_D3D (size 0x3C)
void* gbGfxManager_D3D::_vf04(int p1, int p2, int p3) {
    return new gbVertexPool_D3D((gbPoolType)p1, (unsigned int)p2, p3);
}

// Slot 5: 0x10019140 (106B) - Create gbIndexPool_D3D (size 0x38)
void* gbGfxManager_D3D::_vf05(int p1, int p2, int p3) {
    return new gbIndexPool_D3D((gbPoolType)p1, p2, p3);
}

// Slot 6: 0x100191B0 (101B) - Create gbDynVertBuf_D3D (size 0x40)
void* gbGfxManager_D3D::_vf06(int p1, int p2) {
    return new gbDynVertBuf_D3D((unsigned int)p1, p2);
}

// Slot 7: 0x10019220 (133B) - SetPerspectiveProjection
// Builds perspective projection matrix from frustum params (l,r,b,t,n,f)
// then multiplies into pMatrixStack[0] (projection stack)
void gbGfxManager_D3D::_vf07(double l, double r, double b, double t, double n, double f) {
    float fScale = (float)(f / (f - n));
    gbMatrix4 mat;
    float* m = (float*)&mat;
    int i;
    for (i = 0x10; i != 0; i--) {
        *m = 0.0f;
        m++;
    }
    ((float*)&mat)[0]  = (float)((n + n) / (r - l));
    ((float*)&mat)[5]  = (float)((n + n) / (t - b));
    ((float*)&mat)[11] = 1.0f;
    ((float*)&mat)[10] = fScale;
    ((float*)&mat)[14] = -fScale * (float)n;
    pMatrixStack[0]->MultMatrix(&mat);
}

// Slot 8: 0x100192B0 (195B) - SetOrthographicProjection
// Builds orthographic projection matrix from frustum params (l,r,b,t,n,f)
// then multiplies into pMatrixStack[0] (projection stack)
void gbGfxManager_D3D::_vf08(double l, double r, double b, double t, double n, double f) {
    gbMatrix4 mat;
    float* m = (float*)&mat;
    int i;
    for (i = 0x10; i != 0; i--) {
        *m = 0.0f;
        m++;
    }
    ((float*)&mat)[15] = 1.0f;
    ((float*)&mat)[0]  = (float)(2.0 / (r - l));
    ((float*)&mat)[5]  = (float)(2.0 / (t - b));
    ((float*)&mat)[10] = (float)(1.0 / (f - n));
    ((float*)&mat)[12] = (float)(-((l + r) / (r - l)));
    ((float*)&mat)[13] = (float)(-((b + t) / (t - b)));
    ((float*)&mat)[14] = (float)(-(n / (f - n)));
    pMatrixStack[0]->MultMatrix(&mat);
}

// Slot 9: 0x10019380 (95B) - SetViewport
// Copies 6 DWORDs from param to this->Viewport, then calls device->SetViewport
// D3DVIEWPORT9 = {X, Y, Width, Height, MinZ, MaxZ} = 6 DWORDs
void gbGfxManager_D3D::_vf09(void* pViewportData) {
    // rep movsl: copy 6 DWORDs to this->Viewport
    memcpy(&Viewport, pViewportData, sizeof(D3DVIEWPORT9));
    // Build local copy and call SetViewport
    D3DVIEWPORT9 vp;
    DWORD* src = (DWORD*)pViewportData;
    vp.X      = src[0];
    vp.Y      = src[1];
    vp.Width  = src[2];
    vp.Height = src[3];
    // Disasm stores [4] and [5] in order (no swap): MinZ=src[4], MaxZ=src[5]
    vp.MinZ   = *(float*)&src[4];
    vp.MaxZ   = *(float*)&src[5];
    m_pd3dDevice->SetViewport(&vp);
}

// Slot 10: 0x100193E0 (128B) - SetLight with enable/disable
// if (pLightData == NULL): disable light at index
// else: enable, set light, copy to AllLight[index]
void gbGfxManager_D3D::_vf10(int index, void* pLightData) {
    if (!pLightData) {
        m_pd3dDevice->LightEnable(index, FALSE);
        LightEnable[index] = 0;
    } else {
        m_pd3dDevice->SetLight(index, (const D3DLIGHT9*)pLightData);
        m_pd3dDevice->LightEnable(index, TRUE);
        LightEnable[index] = 1;
        memcpy(&AllLight[index], pLightData, sizeof(gbLight));
    }
}

// Slot 11: 0x10019460 (23B) - SetMaterial (direct passthrough)
void gbGfxManager_D3D::_vf11(D3DMATERIAL9* pMaterial) {
    m_pd3dDevice->SetMaterial(pMaterial);
}

// Slot 12: 0x10018CD0 - D3D BeginScene override
// Calls base gbGfxManager::BeginScene, checks m_bActive, then D3D BeginScene
int gbGfxManager_D3D::BeginScene(void) {
    int result = gbGfxManager::BeginScene();
    if (!result)
        return 0;

    if (!m_bActive)
        return 0;

    if (m_bDeviceLost) {
        // Try to reset the device
        HRESULT hr = m_pd3dDevice->TestCooperativeLevel();
        if (SUCCEEDED(hr)) {
            // Device recovered - not fully handling reset here
        }
        if (hr == D3DERR_DEVICELOST) {
            return 0;
        }
        if (hr == D3DERR_DEVICENOTRESET) {
            // Need reset logic
            /* STUB - device reset */
            return 0;
        }
        m_bDeviceLost = 0;
    }
    m_pd3dDevice->BeginScene();
    m_nState = 1;
    return 1;
}

// Slot 13: 0x10018F00 (57B) - EndScene + Present
// Disasm: calls m_pd3dDevice->EndScene() then m_pd3dDevice->Present(0,0,0,0)
// If Present returns D3DERR_DEVICELOST (0x88760868), sets m_bDeviceLost = 1
void gbGfxManager_D3D::_vf13() {
    m_pd3dDevice->EndScene();
    HRESULT hr = m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
    if (hr == D3DERR_DEVICELOST) {
        m_bDeviceLost = 1;
    }
}

// Slot 14: 0x100194F0 (3B) - RET 0x1C (empty, 7 DWORD params popped)
void gbGfxManager_D3D::_vf14(int, int, int, int, int, int, int) {
    // Empty - original is just RET 0x1C
}

// Slot 15: 0x10019500 (283B) - Flush matrix stacks to D3D device
// Checks dirty flag on each stack; if dirty==0, calls device->SetTransform.
// pMatrixStack[0] → D3DTS_PROJECTION(3), with ZBias adjustment
// pMatrixStack[1] → D3DTS_WORLD(256)
// pMatrixStack[2..3] → D3DTS_TEXTURE0+i (0x10+i)
void gbGfxManager_D3D::_vf15() {
    // Projection matrix stack (pMatrixStack[0])
    if (pMatrixStack[0]->dirty == 0) {
        gbMatrix4 tmp;
        gbMatrix4* top;
        if (CurZBias == 0) {
            top = pMatrixStack[0]->GetTop();
        } else {
            top = pMatrixStack[0]->GetTop();
            float* dst = (float*)&tmp;
            float* src = (float*)top;
            int i;
            for (i = 0x10; i != 0; i--) {
                *dst = *src;
                src++;
                dst++;
            }
            // Adjust near plane Z for decal offset: subtract CurZBias * 7.629453e-06
            ((float*)&tmp)[10] = ((float*)&tmp)[10] - (float)CurZBias * 7.629453e-06f;
            top = &tmp;
        }
        m_pd3dDevice->SetTransform(D3DTS_PROJECTION, (const D3DMATRIX*)top);
        pMatrixStack[0]->dirty = 1;
    }

    // World matrix stack (pMatrixStack[1])
    if (pMatrixStack[1]->dirty == 0) {
        gbMatrix4* top = pMatrixStack[1]->GetTop();
        m_pd3dDevice->SetTransform(D3DTS_WORLD, (const D3DMATRIX*)top);
        pMatrixStack[1]->dirty = 1;
    }

    // Texture matrix stacks (pMatrixStack[2..3])
    int j;
    for (j = 0; j < 2; j++) {
        gbMatrixStack* stk = pMatrixStack[2 + j];
        if (stk->dirty == 0) {
            gbMatrix4* top = stk->GetTop();
            m_pd3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)(0x10 + j), (const D3DMATRIX*)top);
            stk->dirty = 1;
        }
    }
}

// Slot 16: 0x10019620 (764B) - ComputeFrustumPlanes
// Builds view*projection matrix, extracts 6 frustum planes into output buffer.
// params: float* outPlanes (6 planes × 4 floats = 24 floats), int bNormalize
// RET 8 → __thiscall with 2 stack params
void gbGfxManager_D3D::_vf16(float* outPlanes, int bNormalize) {
    gbMatrix4 mat;
    mat.LoadIdentity();
    // mat[2][2] = -1.0 (left-handed to right-handed Z flip)
    ((float*)&mat)[10] = -1.0f;

    // mat *= view matrix (pMatrixStack[1] top)
    gbMatrix4* viewTop = pMatrixStack[1]->GetTop();
    mat.operator*=(*viewTop);

    // mat = mat * projection (pMatrixStack[0] top)
    gbMatrix4* projTop = pMatrixStack[0]->GetTop();
    mat.RightMultiply(*projTop);

    float* m = (float*)&mat;

    // Extract 6 frustum planes from the combined matrix
    // Plane 0: left   = col3 + col0
    outPlanes[0]  = m[0]  + m[3];
    outPlanes[1]  = m[4]  + m[7];
    outPlanes[2]  = m[8]  + m[11];
    outPlanes[3]  = m[12] + m[15];
    // Plane 1: right  = col3 - col0
    outPlanes[4]  = m[3]  - m[0];
    outPlanes[5]  = m[7]  - m[4];
    outPlanes[6]  = m[11] - m[8];
    outPlanes[7]  = m[15] - m[12];
    // Plane 2: top    = col3 - col1
    outPlanes[8]  = m[3]  - m[1];
    outPlanes[9]  = m[7]  - m[5];
    outPlanes[10] = m[11] - m[9];
    outPlanes[11] = m[15] - m[13];
    // Plane 3: bottom = col1 + col3
    outPlanes[12] = m[1]  + m[3];
    outPlanes[13] = m[5]  + m[7];
    outPlanes[14] = m[9]  + m[11];
    outPlanes[15] = m[13] + m[15];
    // Plane 4: near   = col3 - col2
    outPlanes[16] = m[3]  - m[2];
    outPlanes[17] = m[7]  - m[6];
    outPlanes[18] = m[11] - m[10];
    outPlanes[19] = m[15] - m[14];
    // Plane 5: far    = col2 + col3 (wait, Ghidra says col3 - row2 which is m[3]-m[2])
    // Actually from Ghidra: plane5 = {m14-m10, m24-m20, m34-m30, m44-m40} hmm
    // Let me re-read: Ghidra output shows outPlanes[0x14..0x17] at offsets 0x50..0x5c
    // Which are: m[3]-m[2] (col3-col2 per row) → that's the near plane
    // outPlanes[0x10..0x13] at offsets 0x40..0x4c = m[2], m[5+1?]...
    // Actually looking more carefully at the Ghidra output:
    // param_1[0x10] = fStack_38 (mat col2 row0)
    // param_1[0x11] = fStack_28 (mat col2 row1)
    // param_1[0x12] = fStack_18 = -1.0 (mat col2 row2)
    // param_1[0x13] = fStack_8 (mat col2 row3)
    // param_1[0x14] = m[3] - m[2] ...
    // So planes 4,5 are: plane4 = col2 directly, plane5 = col3-col2
    outPlanes[16] = m[2];
    outPlanes[17] = m[6];
    outPlanes[18] = m[10];
    outPlanes[19] = m[14];
    // Plane 5: far = col3 - col2
    outPlanes[20] = m[3]  - m[2];
    outPlanes[21] = m[7]  - m[6];
    outPlanes[22] = m[11] - m[10];
    outPlanes[23] = m[15] - m[14];

    // Optionally normalize each plane
    if (bNormalize) {
        int i;
        for (i = 0; i < 6; i++) {
            float* p = &outPlanes[i * 4];
            float len = (float)sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
            p[0] /= len;
            p[1] /= len;
            p[2] /= len;
            p[3] /= len;
        }
    }
}

// Slot 17: 0x1001B190 (42B) - GetGfxCaps
// Disasm: calls m_pd3dDevice->GetDeviceCaps(&caps) then fills gbGfxCaps from D3DCAPS9
int gbGfxManager_D3D::GetGfxCaps(gbGfxCaps* caps) {
    D3DCAPS9 d3dCaps;
    HRESULT hr = m_pd3dDevice->GetDeviceCaps(&d3dCaps);
    if (FAILED(hr))
        return 0;

    caps->maxTextureWidth = d3dCaps.MaxTextureWidth;
    caps->maxTextureHeight = d3dCaps.MaxTextureHeight;
    caps->maxLights = d3dCaps.MaxActiveLights;
    caps->hwTnL = (d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ? 1 : 0;
    caps->vertexShaderVer = d3dCaps.VertexShaderVersion;
    caps->pixelShaderVer = d3dCaps.PixelShaderVersion;
    return 1;
}

// Slot 18: 0x10009210 (6B) - return 1
// Disasm: MOV EAX,1; RET
void gbGfxManager_D3D::_vf18() {
    // Original just returns 1 (MOV EAX,1; RET)
    // Base class decl returns void; this is a calling convention mismatch in vtable
}

// Slot 19: 0x1001B210 (125B) - GetGammaRamp
// Reads device gamma ramp via GetGammaRamp, extracts high byte of each 16-bit
// entry, stores as (highbyte << 8) into caller's buffer (D3DGAMMARAMP layout).
// Returns early if m_DriverBug.flags == 0.
void gbGfxManager_D3D::_vf19(void* pData) {
    if (!m_DriverBug.flags) return;
    // Get current gamma ramp from device
    D3DGAMMARAMP localRamp;
    m_pd3dDevice->GetGammaRamp(0, &localRamp);
    // Copy with high-byte extraction: output[i] = (input[i] & 0xFF00)
    WORD* outRed   = (WORD*)pData;
    WORD* outGreen = outRed + 256;
    WORD* outBlue  = outGreen + 256;
    for (int i = 0; i < 256; i++) {
        outRed[i]   = localRamp.red[i] & 0xFF00;
        outGreen[i] = localRamp.green[i] & 0xFF00;
        outBlue[i]  = localRamp.blue[i] & 0xFF00;
    }
}

// Slot 20: 0x1001B2B0 (164B) - SetGammaRamp
// Reads BYTE[256]*3 (R/G/B) from pData, expands each byte to WORD as (byte<<8)|byte,
// then calls device->SetGammaRamp(0, flags, &ramp).
// Second param controls calibration: if 0 → D3DSGR_CALIBRATE(1), else D3DSGR_NO_CALIBRATION(0)
void gbGfxManager_D3D::_vf20(int pData, int calibrate) {
    D3DGAMMARAMP ramp;
    unsigned char* src = (unsigned char*)pData;
    // Input: src[0..255]=R, src[256..511]=G, src[512..767]=B
    for (int i = 0; i < 256; i++) {
        WORD r = (WORD)((src[i] << 8) | src[i]);
        WORD g = (WORD)((src[i + 256] << 8) | src[i + 256]);
        WORD b = (WORD)((src[i + 512] << 8) | src[i + 512]);
        ramp.red[i] = r;
        ramp.green[i] = g;
        ramp.blue[i] = b;
    }
    // Disasm: if (param2 != 0) flags=0, else flags=1
    // SetGammaRamp(iSwapChain=0, Flags, pRamp)
    DWORD flags = calibrate ? 0 : 1;
    m_pd3dDevice->SetGammaRamp(0, flags, &ramp);
}

// Slot 21: 0x10018F40 (57B) - LockRect on m_pBackBuffer
// if (param2) flags = 0x810 else flags = 0x800
// m_pBackBuffer->LockRect(&lockedRect, NULL, flags)
// Returns lockedRect on success, 0 on failure
void gbGfxManager_D3D::_vf21(int index, int param2) {
    DWORD flags = param2 ? 0x810 : 0x800;
    D3DLOCKED_RECT lockedRect;
    HRESULT hr = m_pBackBuffer->LockRect(&lockedRect, NULL, flags);
    if (FAILED(hr)) {
        // Return 0 - but function is void in base class
        return;
    }
    // Success path - actual original returns lockedRect pointer
    // (mismatch with void return type; needs signature fix later)
}

// Slot 22: 0x10019030 (13B) - UnlockRect on back buffer surface
// mov eax,[ecx+0x8D0]; push eax; mov (%eax),%ecx; call *0x38(%ecx); ret
// IDirect3DSurface9 vtable slot 14 (0x38/4) = UnlockRect
void gbGfxManager_D3D::_vf22() {
    m_pBackBuffer->UnlockRect();
}

// Slot 23: 0x1001B360 (160B) - SetRenderTarget / Restore RenderTarget
// Global at 0x1013BDF4 stores previously saved render target surface.
// if pParam != NULL: save current RT, get surface from pParam->texture, set as new RT
// if pParam == NULL: restore previously saved RT
static IDirect3DSurface9* g_pSavedRenderTarget = NULL;

void gbGfxManager_D3D::_vf23(void* pParam) {
    if (pParam) {
        // Save current render target
        HRESULT hr = m_pd3dDevice->GetRenderTarget(0, &g_pSavedRenderTarget);
        if (FAILED(hr)) {
            g_pSavedRenderTarget = NULL;
            return;  // returns 0 in original
        }
        // Get IDirect3DTexture9* from pParam at offset +0x54
        IDirect3DTexture9* pTex = *(IDirect3DTexture9**)((char*)pParam + 0x54);
        if (!pTex) return;  // returns 0
        // Get surface level 0
        IDirect3DSurface9* pSurface = NULL;
        pTex->GetSurfaceLevel(0, &pSurface);
        if (!pSurface) return;  // returns 0
        // Set as new render target
        m_pd3dDevice->SetRenderTarget(0, pSurface);
    } else {
        // Restore saved render target
        if (g_pSavedRenderTarget) {
            m_pd3dDevice->SetRenderTarget(0, g_pSavedRenderTarget);
        }
        // returns 1
    }
}

// Slot 24: 0x1001B840 (269B) - LoadCursorResource
// Loads a cursor file from VFileSystem, creates a D3D surface, returns gbCursorRes*
// params: const char* name (filename)
// Pattern: FindResByName in cursor mgr, if found return it;
// else new(0x24), SetName, open file, read, create surface, store hotspot, AddResource
void* gbGfxManager_D3D::_vf24(const char* name) {
    // Search in cursor resource manager (at offset +0x658 = m_CursorMgr)
    gbResource* res = ((gbResManager*)m_CursorMgr)->FindResByName(name);
    if (res != NULL) {
        return res;
    }

    // Create new cursor resource (size 0x24)
    gbCursorRes* cursor = (gbCursorRes*)operator new(0x24);
    if (cursor != NULL) {
        *((int*)((char*)cursor + 0x08)) = 0;
        *((int*)((char*)cursor + 0x10)) = 0;
        *((int*)((char*)cursor + 0x14)) = 0;
        *((int*)((char*)cursor + 0x18)) = 0;
        *((int*)((char*)cursor + 0x04)) = 1;
    }
    ((gbResource*)cursor)->SetName(name);

    // Open and read cursor file via virtual file system
    extern gbVFileSystem* g_pVFileSys;
    gbVFile* file = g_pVFileSys->OpenFile(name, 0x201);
    int fileSize = g_pVFileSys->GetFileSize(file);
    void* fileData = malloc(fileSize);
    g_pVFileSys->Read(fileData, fileSize, file);
    g_pVFileSys->CloseFile(file);

    // FUN_10032e69: parse cursor/icon header, extract dimensions
    int width = 0, height = 0;
    // TODO: ParseCursorHeader(fileData, fileSize, &width) at 0x10032e69

    // Create D3D surface for cursor (D3DFMT_A8R8G8B8=21, D3DPOOL_DEFAULT=0)
    IDirect3DSurface9* pSurface = NULL;
    *((IDirect3DSurface9**)((char*)cursor + 0x18)) = NULL;
    m_pd3dDevice->CreateOffscreenPlainSurface(
        width, height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
        (IDirect3DSurface9**)((char*)cursor + 0x18), NULL);

    // FUN_10033461: fill cursor surface with pixel data from file
    // TODO: FillCursorSurface at 0x10033461

    // Store hotspot in cursor resource
    *((int*)((char*)cursor + 0x20)) = height;
    *((int*)((char*)cursor + 0x1C)) = width;

    // Add to cursor resource manager
    ((gbResManager*)m_CursorMgr)->AddResource((gbResource*)cursor);

    return cursor;
}

// Slot 25: 0x1001B9D0 (47B) - SetCursorProperties
// if (pCursor) { device->SetCursorProperties(cursor[0x1C], cursor[0x20], cursor[0x18]);
//               m_pActiveCursor = pCursor; }
void gbGfxManager_D3D::_vf25(void* pCursor) {
    if (pCursor) {
        gbCursorRes* cursor = (gbCursorRes*)pCursor;
        IDirect3DSurface9* pSurf = *(IDirect3DSurface9**)((char*)cursor + 0x18);
        UINT hotX = *(UINT*)((char*)cursor + 0x1C);
        UINT hotY = *(UINT*)((char*)cursor + 0x20);
        m_pd3dDevice->SetCursorProperties(hotX, hotY, pSurf);
        m_pActiveCursor = cursor;
    }
}

// Slot 26: 0x1001BA00 (26B) - ShowCursor
// m_bShowCursor = bShow; device->ShowCursor(bShow);
void gbGfxManager_D3D::_vf26(int bShow) {
    m_bShowCursor = bShow;
    m_pd3dDevice->ShowCursor(bShow);
}

// Slot 27: 0x1001BA20 (58B) - SetSoftwareVertexProcessing
// m_bSoftVPMode = bSoftVP;
// if (bIsWindowed) vpType = *(this+0x69C) else vpType = *(this+0x6D4)
// Per struct layout: +0x69C = settings.Fullscreen_VertexProcessingType
//                    +0x6D4 = settings.Windowed_VertexProcessingType
// if (vpType == 1) device->SetSoftwareVertexProcessing(bSoftVP)
void gbGfxManager_D3D::_vf27(int bSoftVP) {
    m_bSoftVPMode = bSoftVP;
    // Binary: bIsWindowed true → use Fullscreen field; false → Windowed field
    // This matches the original code exactly (possibly intentional: current mode's VP type)
    int vpType;
    if (m_d3dSettings.bIsWindowed) {
        vpType = m_d3dSettings.Fullscreen_VertexProcessingType;
    } else {
        vpType = m_d3dSettings.Windowed_VertexProcessingType;
    }
    if (vpType == 1) {
        m_pd3dDevice->SetSoftwareVertexProcessing(bSoftVP);
    }
}

// Slot 28: 0x10019480 (99B) - SetFog D3D override
// Calls base gbGfxManager::SetFog, then sets D3DRS_FOGCOLOR on device
void gbGfxManager_D3D::SetFog(gbFogParam* pFogParam) {
    gbGfxManager::SetFog(pFogParam);
    if (pFogParam != NULL) {
        // Convert float color (r,g,b at offsets +4,+8,+C) to D3DCOLOR
        float* colorPtr = (float*)((char*)pFogParam + 4);
        int r = (int)(colorPtr[2] * 255.0f);
        int g = (int)(colorPtr[1] * 255.0f);
        int b = (int)(colorPtr[0] * 255.0f);
        DWORD fogColor = (DWORD)((r << 16) | (g << 8) | b);
        // D3DRS_FOGCOLOR = 0x22 = 34
        m_pd3dDevice->SetRenderState(D3DRS_FOGCOLOR, fogColor);
    }
}

// CD3DEnumeration::Enumerate is in d3dframework.cpp
