/**
 * gbengine.dll - gbTexture_D3D
 * D3D9 texture implementation
 */

#include "gbengine/gbTexture.h"
#include "gbengine/gbGfxManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>

extern gbGfxManager* g_pGfxManager;

gbTexture_D3D::gbTexture_D3D(void) {
    // Base gbTexture constructor already called
    /* UNCERTAIN: D3D-specific field initialization */
    // m_pD3DTexture = NULL;
    // m_pD3DSurface = NULL;
}

gbTexture_D3D::~gbTexture_D3D(void) {
    /* UNCERTAIN: D3D texture cleanup */
    // if (m_pD3DTexture) m_pD3DTexture->Release();
    // if (m_pD3DSurface) m_pD3DSurface->Release();
}

IDirect3DBaseTexture9* gbTexture_D3D::GetTexName(void) {
    /* UNCERTAIN: Return D3D texture handle */
    // return m_pD3DTexture;
    return NULL;
}

IDirect3DSurface9* gbTexture_D3D::GetMiscTexName(void) {
    /* UNCERTAIN: Return D3D surface handle */
    // return m_pD3DSurface;
    return NULL;
}

unsigned char gbTexture_D3D::GetByte(int x, int y) {
    /* UNCERTAIN: Read pixel byte from texture */
    // Would lock texture, read pixel, unlock
    return 0;
}

int gbTexture_D3D::CreateForRenderTarget(int width, int height, gbPixelFmtType format) {
    if (!g_pGfxManager) return 0;

    /* UNCERTAIN: Create render target texture */
    // gbGfxManager_D3D* d3dMgr = (gbGfxManager_D3D*)g_pGfxManager;
    // IDirect3DDevice9* device = d3dMgr->m_pd3dDevice;
    //
    // D3DFORMAT d3dFormat = D3DFMT_A8R8G8B8;
    // HRESULT hr = device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET,
    //                                    d3dFormat, D3DPOOL_DEFAULT, &m_pD3DTexture, NULL);
    // if (FAILED(hr)) return 0;
    //
    // Width = width;
    // Height = height;
    // IsLoaded = 1;

    return 1;
}

void gbTexture_D3D::CreateFromMemory(int width, int height, gbPixelFmtType srcFmt,
                                      int mipLevels, gbPixelFmtType dstFmt, void* pData) {
    if (!g_pGfxManager || !pData) return;

    /* UNCERTAIN: Create texture from memory data */
    // gbGfxManager_D3D* d3dMgr = (gbGfxManager_D3D*)g_pGfxManager;
    // IDirect3DDevice9* device = d3dMgr->m_pd3dDevice;
    //
    // D3DFORMAT d3dFormat = D3DFMT_A8R8G8B8;
    // HRESULT hr = device->CreateTexture(width, height, mipLevels,
    //                                    0, d3dFormat, D3DPOOL_MANAGED, &m_pD3DTexture, NULL);
    // if (FAILED(hr)) return;
    //
    // // Lock and copy data
    // D3DLOCKED_RECT locked;
    // if (SUCCEEDED(m_pD3DTexture->LockRect(0, &locked, NULL, 0))) {
    //     memcpy(locked.pBits, pData, width * height * 4);
    //     m_pD3DTexture->UnlockRect(0);
    // }
    //
    // Width = width;
    // Height = height;
    // IsLoaded = 1;
}

void gbTexture_D3D::CreateFromFileMemory(void* pFileData, int fileSize) {
    if (!g_pGfxManager || !pFileData || fileSize <= 0) return;

    /* UNCERTAIN: Load texture from file memory using D3DX */
    // gbGfxManager_D3D* d3dMgr = (gbGfxManager_D3D*)g_pGfxManager;
    // IDirect3DDevice9* device = d3dMgr->m_pd3dDevice;
    //
    // D3DXIMAGE_INFO info;
    // HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(
    //     device, pFileData, fileSize, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
    //     0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
    //     0, &info, NULL, (IDirect3DTexture9**)&m_pD3DTexture);
    //
    // if (SUCCEEDED(hr)) {
    //     Width = info.Width;
    //     Height = info.Height;
    //     IsLoaded = 1;
    // }
}

void gbTexture_D3D::UpdateTexture(int x, int y, int width, int height,
                                   gbPixelFmtType format, void* pData) {
    if (!pData) return;

    /* UNCERTAIN: Update texture subregion */
    // RECT rect = { x, y, x + width, y + height };
    // D3DLOCKED_RECT locked;
    // if (SUCCEEDED(m_pD3DTexture->LockRect(0, &locked, &rect, 0))) {
    //     memcpy(locked.pBits, pData, width * height * 4);
    //     m_pD3DTexture->UnlockRect(0);
    // }
}
