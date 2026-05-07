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

// CD3DEnumeration::Enumerate is in d3dframework.cpp
