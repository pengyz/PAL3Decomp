/**
 * D3DX9 stub implementations for gbengine.dll
 * These provide no-op implementations of D3DX functions
 * so the DLL links without requiring the real DirectX SDK.
 */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

extern "C" {

HRESULT WINAPI D3DXCreateTextureFromFileInMemory(
    LPDIRECT3DDEVICE9 pDevice,
    LPCVOID pSrcData,
    UINT SrcDataSize,
    LPDIRECT3DTEXTURE9* ppTexture)
{
    if (ppTexture) *ppTexture = NULL;
    return E_NOTIMPL;
}

HRESULT WINAPI D3DXCreateTextureFromFileInMemoryEx(
    LPDIRECT3DDEVICE9 pDevice,
    LPCVOID pSrcData,
    UINT SrcDataSize,
    UINT Width,
    UINT Height,
    UINT MipLevels,
    DWORD Usage,
    D3DFORMAT Format,
    D3DPOOL Pool,
    DWORD Filter,
    DWORD MipFilter,
    D3DCOLOR ColorKey,
    void* pSrcInfo,
    PALETTEENTRY* pPalette,
    LPDIRECT3DTEXTURE9* ppTexture)
{
    if (ppTexture) *ppTexture = NULL;
    return E_NOTIMPL;
}

HRESULT WINAPI D3DXCreateEffectFromFileA(
    LPDIRECT3DDEVICE9 pDevice,
    LPCSTR pSrcFile,
    const void* pDefines,
    void* pInclude,
    DWORD Flags,
    ID3DXEffectPool* pPool,
    ID3DXEffect** ppEffect,
    ID3DXBuffer** ppCompilationErrors)
{
    if (ppEffect) *ppEffect = NULL;
    if (ppCompilationErrors) *ppCompilationErrors = NULL;
    return E_NOTIMPL;
}

HRESULT WINAPI D3DXGetImageInfoFromFileA(
    LPCSTR pSrcFile,
    D3DXIMAGE_INFO* pSrcInfo)
{
    if (pSrcInfo) memset(pSrcInfo, 0, sizeof(D3DXIMAGE_INFO));
    return E_NOTIMPL;
}

HRESULT WINAPI D3DXLoadSurfaceFromFileA(
    LPDIRECT3DSURFACE9 pDestSurface,
    const PALETTEENTRY* pDestPalette,
    const RECT* pDestRect,
    LPCSTR pSrcFile,
    const RECT* pSrcRect,
    DWORD Filter,
    D3DCOLOR ColorKey,
    D3DXIMAGE_INFO* pSrcInfo)
{
    return E_NOTIMPL;
}

HRESULT WINAPI D3DXCreateEffect(
    LPDIRECT3DDEVICE9 pDevice,
    LPCVOID pSrcData,
    UINT SrcDataLen,
    const void* pDefines,
    void* pInclude,
    DWORD Flags,
    ID3DXEffectPool* pPool,
    ID3DXEffect** ppEffect,
    ID3DXBuffer** ppCompilationErrors)
{
    if (ppEffect) *ppEffect = NULL;
    if (ppCompilationErrors) *ppCompilationErrors = NULL;
    return E_NOTIMPL;
}

}
