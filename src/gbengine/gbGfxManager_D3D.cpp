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
        DisplayErrorMsg(0x82000001, 2);
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
// Stubs for internal helper methods (to be implemented later)
// ============================================================================

// 0x10019b70 - Enumerate D3D adapters and choose best device
int gbGfxManager_D3D::ChooseBestDevice(void) {
    // TODO: D3D device enumeration
    return 0;
}

// 0x1001a790 (1208B) - Create actual D3D device with chosen settings
int gbGfxManager_D3D::CreateDevice(void) {
    // TODO: CreateDevice9 call and back buffer setup
    return 0;
}

// 0x10019e70 - Initialize device in windowed mode
char gbGfxManager_D3D::InitDeviceWindowed(int p1, int p2) {
    // TODO: Windowed device initialization
    return 0;
}

// 0x10019c60 - Initialize device in fullscreen mode
char gbGfxManager_D3D::InitDeviceFullscreen(int p1, int p2) {
    // TODO: Fullscreen device initialization
    return 0;
}

// 0x1001ad80 (393B) - Display error message via MessageBox
void gbGfxManager_D3D::DisplayErrorMsg(int hr, int type) {
    // TODO: Error message display
}
