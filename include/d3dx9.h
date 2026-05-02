#pragma once
// Minimal D3DX9 stub for gbengine decompilation
// The real SDK is "DirectX SDK (Summer 2003)" but d3dx9.h is unavailable
// This provides the minimal type declarations needed for compilation

#include <d3d9.h>

#ifndef D3DX_DEFAULT
#define D3DX_DEFAULT ((UINT)-1)
#define D3DX_DEFAULT_NONPOW2 ((UINT)-2)
#define D3DX_FROM_FILE ((UINT)-3)
#endif

// D3DX Matrix/Vector types (identical to our gbMatrix4/gbVec3D)
typedef struct D3DXVECTOR3 {
    float x, y, z;
} D3DXVECTOR3;

typedef struct D3DXVECTOR4 {
    float x, y, z, w;
} D3DXVECTOR4;

typedef struct D3DXMATRIX {
    float m[4][4];
} D3DXMATRIX;

// D3DX Effect interface
typedef DWORD D3DXHANDLE;

typedef struct ID3DXEffect ID3DXEffect;
typedef struct ID3DXEffectPool ID3DXEffectPool;
typedef struct ID3DXBuffer ID3DXBuffer;

// ID3DXEffect interface (minimal vtable stub)
#undef INTERFACE
#define INTERFACE ID3DXEffect
DECLARE_INTERFACE_(ID3DXEffect, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXBaseEffect
    STDMETHOD(GetDesc)(THIS_ void* pDesc) PURE;
    STDMETHOD(GetParameterDesc)(THIS_ D3DXHANDLE hParam, void* pDesc) PURE;
    STDMETHOD(GetTechniqueDesc)(THIS_ D3DXHANDLE hTech, void* pDesc) PURE;
    STDMETHOD(GetPassDesc)(THIS_ D3DXHANDLE hPass, void* pDesc) PURE;
    STDMETHOD(GetFunctionDesc)(THIS_ D3DXHANDLE hFunc, void* pDesc) PURE;
    STDMETHOD_(D3DXHANDLE, GetParameter)(THIS_ D3DXHANDLE hParent, UINT index) PURE;
    STDMETHOD_(D3DXHANDLE, GetParameterByName)(THIS_ D3DXHANDLE hParent, LPCSTR name) PURE;
    STDMETHOD_(D3DXHANDLE, GetParameterBySemantic)(THIS_ D3DXHANDLE hParent, LPCSTR semantic) PURE;
    STDMETHOD_(D3DXHANDLE, GetParameterElement)(THIS_ D3DXHANDLE hParam, UINT index) PURE;
    STDMETHOD_(D3DXHANDLE, GetTechnique)(THIS_ UINT index) PURE;
    STDMETHOD_(D3DXHANDLE, GetTechniqueByName)(THIS_ LPCSTR name) PURE;
    STDMETHOD_(D3DXHANDLE, GetPass)(THIS_ D3DXHANDLE hTech, UINT index) PURE;
    STDMETHOD_(D3DXHANDLE, GetFunction)(THIS_ UINT index) PURE;
    STDMETHOD_(D3DXHANDLE, GetAnnotation)(THIS_ D3DXHANDLE hObj, UINT index) PURE;
    STDMETHOD_(D3DXHANDLE, GetAnnotationByName)(THIS_ D3DXHANDLE hObj, LPCSTR name) PURE;
    STDMETHOD(SetValue)(THIS_ D3DXHANDLE hParam, LPCVOID pData, UINT bytes) PURE;
    STDMETHOD(GetValue)(THIS_ D3DXHANDLE hParam, LPVOID pData, UINT bytes) PURE;
    STDMETHOD(SetBool)(THIS_ D3DXHANDLE hParam, BOOL b) PURE;
    STDMETHOD(GetBool)(THIS_ D3DXHANDLE hParam, BOOL* pb) PURE;
    STDMETHOD(SetBoolArray)(THIS_ D3DXHANDLE hParam, const BOOL* pb, UINT count) PURE;
    STDMETHOD(GetBoolArray)(THIS_ D3DXHANDLE hParam, BOOL* pb, UINT count) PURE;
    STDMETHOD(SetInt)(THIS_ D3DXHANDLE hParam, INT n) PURE;
    STDMETHOD(GetInt)(THIS_ D3DXHANDLE hParam, INT* pn) PURE;
    STDMETHOD(SetIntArray)(THIS_ D3DXHANDLE hParam, const INT* pn, UINT count) PURE;
    STDMETHOD(GetIntArray)(THIS_ D3DXHANDLE hParam, INT* pn, UINT count) PURE;
    STDMETHOD(SetFloat)(THIS_ D3DXHANDLE hParam, FLOAT f) PURE;
    STDMETHOD(GetFloat)(THIS_ D3DXHANDLE hParam, FLOAT* pf) PURE;
    STDMETHOD(SetFloatArray)(THIS_ D3DXHANDLE hParam, const FLOAT* pf, UINT count) PURE;
    STDMETHOD(GetFloatArray)(THIS_ D3DXHANDLE hParam, FLOAT* pf, UINT count) PURE;
    STDMETHOD(SetVector)(THIS_ D3DXHANDLE hParam, const D3DXVECTOR4* pVec) PURE;
    STDMETHOD(GetVector)(THIS_ D3DXHANDLE hParam, D3DXVECTOR4* pVec) PURE;
    STDMETHOD(SetVectorArray)(THIS_ D3DXHANDLE hParam, const D3DXVECTOR4* pVec, UINT count) PURE;
    STDMETHOD(GetVectorArray)(THIS_ D3DXHANDLE hParam, D3DXVECTOR4* pVec, UINT count) PURE;
    STDMETHOD(SetMatrix)(THIS_ D3DXHANDLE hParam, const D3DXMATRIX* pMat) PURE;
    STDMETHOD(GetMatrix)(THIS_ D3DXHANDLE hParam, D3DXMATRIX* pMat) PURE;
    STDMETHOD(SetMatrixArray)(THIS_ D3DXHANDLE hParam, const D3DXMATRIX* pMat, UINT count) PURE;
    STDMETHOD(GetMatrixArray)(THIS_ D3DXHANDLE hParam, D3DXMATRIX* pMat, UINT count) PURE;
    STDMETHOD(SetMatrixPointerArray)(THIS_ D3DXHANDLE hParam, const D3DXMATRIX** ppMat, UINT count) PURE;
    STDMETHOD(GetMatrixPointerArray)(THIS_ D3DXHANDLE hParam, D3DXMATRIX** ppMat, UINT count) PURE;
    STDMETHOD(SetMatrixTranspose)(THIS_ D3DXHANDLE hParam, const D3DXMATRIX* pMat) PURE;
    STDMETHOD(GetMatrixTranspose)(THIS_ D3DXHANDLE hParam, D3DXMATRIX* pMat) PURE;
    STDMETHOD(SetMatrixTransposeArray)(THIS_ D3DXHANDLE hParam, const D3DXMATRIX* pMat, UINT count) PURE;
    STDMETHOD(GetMatrixTransposeArray)(THIS_ D3DXHANDLE hParam, D3DXMATRIX* pMat, UINT count) PURE;
    STDMETHOD(SetMatrixTransposePointerArray)(THIS_ D3DXHANDLE hParam, const D3DXMATRIX** ppMat, UINT count) PURE;
    STDMETHOD(GetMatrixTransposePointerArray)(THIS_ D3DXHANDLE hParam, D3DXMATRIX** ppMat, UINT count) PURE;
    STDMETHOD(SetString)(THIS_ D3DXHANDLE hParam, LPCSTR pStr) PURE;
    STDMETHOD(GetString)(THIS_ D3DXHANDLE hParam, LPCSTR* ppStr) PURE;
    STDMETHOD(SetTexture)(THIS_ D3DXHANDLE hParam, LPDIRECT3DBASETEXTURE9 pTex) PURE;
    STDMETHOD(GetTexture)(THIS_ D3DXHANDLE hParam, LPDIRECT3DBASETEXTURE9* ppTex) PURE;
    STDMETHOD(GetPixelShader)(THIS_ D3DXHANDLE hParam, LPDIRECT3DPIXELSHADER9* ppPS) PURE;
    STDMETHOD(GetVertexShader)(THIS_ D3DXHANDLE hParam, LPDIRECT3DVERTEXSHADER9* ppVS) PURE;
    STDMETHOD(SetArrayRange)(THIS_ D3DXHANDLE hParam, UINT start, UINT end) PURE;

    // ID3DXEffect
    STDMETHOD_(D3DXHANDLE, FindNextValidTechnique)(THIS_ D3DXHANDLE hTech, D3DXHANDLE* pTech) PURE;
    STDMETHOD(ValidateTechnique)(THIS_ D3DXHANDLE hTech) PURE;
    STDMETHOD(SetTechnique)(THIS_ D3DXHANDLE hTech) PURE;
    STDMETHOD_(D3DXHANDLE, GetCurrentTechnique)(THIS) PURE;
    STDMETHOD(Begin)(THIS_ UINT* pPasses, DWORD flags) PURE;
    STDMETHOD(BeginPass)(THIS_ UINT pass) PURE;
    STDMETHOD(CommitChanges)(THIS) PURE;
    STDMETHOD(EndPass)(THIS) PURE;
    STDMETHOD(End)(THIS) PURE;
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE9* ppDev) PURE;
    STDMETHOD(OnLostDevice)(THIS) PURE;
    STDMETHOD(OnResetDevice)(THIS) PURE;
    STDMETHOD(SetStateManager)(THIS_ void* pMgr) PURE;
    STDMETHOD(GetStateManager)(THIS_ void** ppMgr) PURE;
    STDMETHOD(BeginParameterBlock)(THIS) PURE;
    STDMETHOD_(D3DXHANDLE, EndParameterBlock)(THIS) PURE;
    STDMETHOD(ApplyParameterBlock)(THIS_ D3DXHANDLE hBlock) PURE;
    STDMETHOD(DeleteParameterBlock)(THIS_ D3DXHANDLE hBlock) PURE;
    STDMETHOD(CloneEffect)(THIS_ LPDIRECT3DDEVICE9 pDev, ID3DXEffect** ppEffect) PURE;
};

// ID3DXBuffer interface
#undef INTERFACE
#define INTERFACE ID3DXBuffer
DECLARE_INTERFACE_(ID3DXBuffer, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD_(LPVOID, GetBufferPointer)(THIS) PURE;
    STDMETHOD_(DWORD, GetBufferSize)(THIS) PURE;
};

// D3DX Functions (stub declarations - will link against d3dx9.lib at final integration)
// D3DXIMAGE_INFO structure
typedef struct _D3DXIMAGE_INFO {
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT MipLevels;
    D3DFORMAT Format;
    D3DRESOURCETYPE ResourceType;
    D3DFORMAT ImageFileFormat;
} D3DXIMAGE_INFO;

#ifdef __cplusplus
extern "C" {
#endif

HRESULT WINAPI D3DXCreateTextureFromFileInMemory(
    LPDIRECT3DDEVICE9 pDevice,
    LPCVOID pSrcData,
    UINT SrcDataSize,
    LPDIRECT3DTEXTURE9* ppTexture);

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
    LPDIRECT3DTEXTURE9* ppTexture);

HRESULT WINAPI D3DXCreateEffectFromFileA(
    LPDIRECT3DDEVICE9 pDevice,
    LPCSTR pSrcFile,
    const void* pDefines,
    void* pInclude,
    DWORD Flags,
    ID3DXEffectPool* pPool,
    ID3DXEffect** ppEffect,
    ID3DXBuffer** ppCompilationErrors);

HRESULT WINAPI D3DXGetImageInfoFromFileA(
    LPCSTR pSrcFile,
    D3DXIMAGE_INFO* pSrcInfo);

#define D3DXGetImageInfoFromFile D3DXGetImageInfoFromFileA

HRESULT WINAPI D3DXLoadSurfaceFromFileA(
    LPDIRECT3DSURFACE9 pDestSurface,
    const PALETTEENTRY* pDestPalette,
    const RECT* pDestRect,
    LPCSTR pSrcFile,
    const RECT* pSrcRect,
    DWORD Filter,
    D3DCOLOR ColorKey,
    D3DXIMAGE_INFO* pSrcInfo);

#define D3DXLoadSurfaceFromFile D3DXLoadSurfaceFromFileA

#define D3DXCreateEffectFromFile D3DXCreateEffectFromFileA

HRESULT WINAPI D3DXCreateEffect(
    LPDIRECT3DDEVICE9 pDevice,
    LPCVOID pSrcData,
    UINT SrcDataLen,
    const void* pDefines,
    void* pInclude,
    DWORD Flags,
    ID3DXEffectPool* pPool,
    ID3DXEffect** ppEffect,
    ID3DXBuffer** ppCompilationErrors);

#ifdef __cplusplus
}
#endif

// D3DX Filter flags
#define D3DX_FILTER_NONE        0x00000001
#define D3DX_FILTER_POINT       0x00000002
#define D3DX_FILTER_LINEAR      0x00000003
#define D3DX_FILTER_TRIANGLE    0x00000004
#define D3DX_FILTER_BOX         0x00000005
#define D3DX_DEFAULT_MIP_FILTER 0xFFFFFFFF
