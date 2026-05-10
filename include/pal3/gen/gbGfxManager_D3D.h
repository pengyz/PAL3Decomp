#pragma once
// Auto-generated: gbGfxManager_D3D

#include "CD3DEnumeration.h"
#include "CD3DSettings.h"
#include "D3DDriverBug.h"
#include "_D3DCAPS9.h"
#include "_D3DPRESENT_PARAMETERS_.h"
#include "_D3DSURFACE_DESC.h"

class HWND__;
class IDirect3D9;
class IDirect3DDevice9;
class IDirect3DIndexBuffer9;
class IDirect3DSurface9;
class IDirect3DVertexBuffer9;

class gbGfxManager_D3D : public gbGfxManager {
public:
    CD3DEnumeration m_d3dEnumeration; // +0x5F0
    int m_bWindowed; // +0x61C
    tagRECT m_rcWindowClient; // +0x620
    tagRECT m_rcWindowBounds; // +0x630
    unsigned long m_dwWindowStyle; // +0x640
    HWND__ * m_hWnd; // +0x644
    unsigned char m_bMinimized; // +0x648
    unsigned char m_bMaximized; // +0x649
    unsigned char m_bClipCursorWhenFullscreen; // +0x64A
    unsigned char m_bShowCursorWhenFullscreen; // +0x64B
    unsigned char m_bActive; // +0x64C
    unsigned long m_dwCreateFlags; // +0x650
    D3DDriverBug m_DriverBug; // +0x654
    gbResManager m_CursorMgr; // +0x658
    gbCursorRes * m_pActiveCursor; // +0x664
    int m_bShowCursor; // +0x668
    int m_bSoftVPMode; // +0x66C
    CD3DSettings m_d3dSettings; // +0x670
    _D3DPRESENT_PARAMETERS_ m_d3dpp; // +0x6DC
    IDirect3D9 * m_pD3D; // +0x714
    IDirect3DDevice9 * m_pd3dDevice; // +0x718
    _D3DCAPS9 m_d3dCaps; // +0x71C
    _D3DSURFACE_DESC m_d3dsdBackBuffer; // +0x84C
    char m_strDeviceStats[90]; // +0x86C
    long m_ErrorCode; // +0x8C8
    int m_bDeviceLost; // +0x8CC
    IDirect3DSurface9 * m_pBackBuffer; // +0x8D0
    int m_DXTSupported[5]; // +0x8D4
    IDirect3DVertexBuffer9 * m_pCacheVB; // +0x8E8
    IDirect3DIndexBuffer9 * m_pCacheIB; // +0x8EC
    // total size: 0x8F0 (2288)

};
