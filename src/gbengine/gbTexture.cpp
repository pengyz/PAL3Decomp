/**
 * gbengine.dll - gbTexture, gbTexture_D3D, gbTextureArray, gbImage2D
 *
 * Functional decompilation of texture and image management classes.
 * Based on PAL3patch struct definitions and Ghidra export analysis.
 *
 * Compiler: MSVC 6.0 SP5
 * Graphics: DirectX 9 (Summer 2003 SDK)
 */

#include "gbengine/gbTexture.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbGfxManager_impl.h"
#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Intel JPEG Library 1.5 declarations (ijl15.dll)
#pragma pack(push, 4)
typedef struct {
    char pad0[4];                   // 0x00: internal
    void* DIBBytes;                 // 0x04
    int DIBWidth;                   // 0x08
    int DIBHeight;                  // 0x0C (negative = bottom-up)
    int DIBPadBytes;                // 0x10
    int DIBChannels;                // 0x14
    int DIBColor;                   // 0x18
    char pad1[4];                   // 0x1C
    char* JPGFile;                  // 0x20
    void* JPGBytes;                 // 0x24
    int JPGSizeBytes;               // 0x28
    int JPGWidth;                   // 0x2C
    int JPGHeight;                  // 0x30
    int JPGChannels;                // 0x34
    int JPGColor;                   // 0x38
    int JPGSubsampling;             // 0x3C
    char pad2[16];                  // 0x40-0x4F
    int jquality;                   // 0x50
    char pad3[0x4e68 - 0x54];       // rest of structure
} JPEG_CORE_PROPERTIES;
#pragma pack(pop)

extern "C" {
    __declspec(dllimport) int __cdecl ijlInit(JPEG_CORE_PROPERTIES* jcprops);
    __declspec(dllimport) int __cdecl ijlFree(JPEG_CORE_PROPERTIES* jcprops);
    __declspec(dllimport) int __cdecl ijlWrite(JPEG_CORE_PROPERTIES* jcprops, int iotype);
}

static JPEG_CORE_PROPERTIES g_jpegProps;

// Forward declarations
class gbGfxManager_D3D;
class gbCamControler;
class gbRenderEffect;
class gbEffectMgr;
class gbSceneGraph;
class gbMatrixStack;
class gbPrintFont;
class gbBaseMesh;
// External globals
extern gbGfxManager* g_pGfxManager;
extern int dword_10140DB0;

static char Str[260];

// ============================================================================
// Helper: convert gbPixelFmtType to D3DFORMAT
// ============================================================================
static D3DFORMAT gbPixelFmtToD3D(gbPixelFmtType fmt)
{
    switch (fmt) {
    case GB_PFT_R8G8B8:     return D3DFMT_R8G8B8;
    case GB_PFT_A8R8G8B8:   return D3DFMT_A8R8G8B8;
    case GB_PFT_R5G6B5:     return D3DFMT_R5G6B5;
    case GB_PFT_A1R5G5B5:   return D3DFMT_A1R5G5B5;
    case GB_PFT_A4R4G4B4:   return D3DFMT_A4R4G4B4;
    case GB_PFT_P8:          return D3DFMT_P8;
    case GB_PFT_A8:          return D3DFMT_A8;
    case GB_PFT_X8R8G8B8:   return D3DFMT_X8R8G8B8;
    case GB_PFT_X1R5G5B5:   return D3DFMT_X1R5G5B5;
    case GB_PFT_X4R4G4B4:   return D3DFMT_X4R4G4B4;
    default:                 return D3DFMT_UNKNOWN;
    }
}

// Helper: get bits per pixel from format type
static int gbPixelFmtBpp(gbPixelFmtType fmt)
{
    switch (fmt) {
    case GB_PFT_R8G8B8:     return 24;
    case GB_PFT_A8R8G8B8:   return 32;
    case GB_PFT_R5G6B5:     return 16;
    case GB_PFT_A1R5G5B5:   return 16;
    case GB_PFT_A4R4G4B4:   return 16;
    case GB_PFT_P8:          return 8;
    case GB_PFT_A8:          return 8;
    case GB_PFT_X8R8G8B8:   return 32;
    case GB_PFT_X1R5G5B5:   return 16;
    case GB_PFT_X4R4G4B4:   return 16;
    default:                 return 0;
    }
}


// ============================================================================
// gbImage2DInfo method implementations
// ============================================================================

// 0x1001e470 (22B)
int gbImage2DInfo::IsPreferAlpha(void) {
    return (goal == 1 || goal == 3);
}



// ============================================================================
// gbImage2D method implementations
// ============================================================================

// 0x1001e3e0 (47B) - Constructor
gbImage2D::gbImage2D(void) {
    Width = 0;
    Height = 0;
    BitCount = 0;
    pBits = NULL;
    pPalette = NULL;
    numPalEntry = 0;
    memset(&PixelFmt, 0, sizeof(PixelFmt));
    memset(&ImgInfo, 0, sizeof(ImgInfo));
    memset(&ColorKey, 0, sizeof(ColorKey));
}

// Destructor
gbImage2D::~gbImage2D() {
    if (pBits) {
        free(pBits);
        pBits = NULL;
    }
    if (pPalette) {
        free(pPalette);
        pPalette = NULL;
    }
}


// ============================================================================
// gbTexture method implementations
// ============================================================================

// 0x10020370 (37B) - Constructor
gbTexture::gbTexture(void) {
    refCount = 0;
    name = NULL;
    nameCrc = 0;
    isLoaded = 0;
    manager = NULL;
    Width = 0;
    Height = 0;
    pTexImage = NULL;
    memset(&InFmt, 0, sizeof(InFmt));
    nLevels = 1;
}

// Virtual destructor
gbTexture::~gbTexture() {
    if (pTexImage) {
        delete pTexImage;
        pTexImage = NULL;
    }
    if (name) {
        free(name);
        name = NULL;
    }
}

// 0x10004190 (12B) - Check if texture is initialized
int gbTexture::IsInit(void) {
    return nLevels != -1;
}

// 0x10020760 (102B) - Create empty texture
void gbTexture::CreateTexture(int w, int h, gbPixelFmtType fmt, int mips) {
    Width = w;
    Height = h;
    InFmt.Type = fmt;
    InFmt.Bpp = gbPixelFmtBpp(fmt);
    nLevels = mips;
    isLoaded = 1;
}

// Get the D3D texture interface (base returns NULL, overridden in D3D subclass)
IDirect3DTexture9* gbTexture::GetTexture(void) {
    return NULL;
}

// Exported: GetHeight
int gbTexture::GetHeight(void) {
    return Height;
}

// Exported: GetWidth
int gbTexture::GetWidth(void) {
    return Width;
}

// 0x10020430 (85B) - Get internal D3D format from image
static int g_texInternalFmtMode = 0;

gbPixelFmtType gbTexture::GetInternalFormat(gbImage2D* img) {
    switch (img->BitCount) {
    case 24:
        if (g_texInternalFmtMode == 0)
            return GB_PFT_R8G8B8;
        if (g_texInternalFmtMode == 1)
            return GB_PFT_R5G6B5;
        break;
    case 32:
        if (g_texInternalFmtMode == 0)
            return GB_PFT_A8R8G8B8;
        if (g_texInternalFmtMode == 1)
            return GB_PFT_A4R4G4B4;
        break;
    }
    return GB_PFT_UNKNOWN;
}

// 0x100207d0 (15B) - Get raw bits pointer
unsigned char* gbTexture::GetBits(void) {
    if (!pTexImage)
        return NULL;
    return (unsigned char*)pTexImage->pBits;
}

// 0x100207e0 (53B) - Get pixel channel value at (x, y)
unsigned char gbTexture::GetPixelChannel(int x, int y, int channel) {
    if (!pTexImage || !pTexImage->pBits)
        return 0;

    int bpp = pTexImage->BitCount;
    int pitch = (pTexImage->Width * bpp + 31) / 32 * 4;
    unsigned char* pixel = (unsigned char*)pTexImage->pBits + y * pitch + x * (bpp / 8);

    if (bpp == 32) {
        // BGRA order
        return pixel[channel];
    } else if (bpp == 24) {
        if (channel < 3)
            return pixel[channel];
    }
    return 0;
}

// Exported: GetLevels
int gbTexture::GetLevels(void) {
    return nLevels;
}

// 0x10020490 (269B) - Load texture data from gbImage2D
void gbTexture::LoadFromImage2D(gbImage2D* img) {
    if (!img)
        return;
    Width = img->Width;
    Height = img->Height;
    InFmt.Type = img->PixelFmt.Type;
    InFmt.Bpp = img->PixelFmt.Bpp;
    isLoaded = 1;
}

// 0x100205a0 (443B)
void gbTexture::LoadTexture(int a2) {
    if (isLoaded)
        return;

    strcpy(Str, name);
    char* dot = strrchr(Str, '.');
    if (!dot)
        return;

    strcpy(dot, ".dds");
    gbVFile* vf = g_pVFileSys->OpenFile(Str, 0x201u);
    if (vf) {
        if (vf->cpkFile.lpRealData) {
            int fileSize = g_pVFileSys->GetFileSize(vf);
            ((gbTexture_D3D*)this)->CreateFromFileMemory(vf->cpkFile.lpRealData, fileSize);
            g_pVFileSys->CloseFile(vf);
        } else {
            size_t fileSize = g_pVFileSys->GetFileSize(vf);
            void* buf = malloc(fileSize);
            g_pVFileSys->Read(buf, fileSize, vf);
            g_pVFileSys->CloseFile(vf);
            ((gbTexture_D3D*)this)->CreateFromFileMemory(buf, fileSize);
            free(buf);
        }
        isLoaded = 1;
        return;
    }
    if (!pTexImage) {
        gbImage2D* img = new gbImage2D();
        pTexImage = img;
    }
    if (pTexImage->LoadImageFile(name, dword_10140DB0) && a2) {
        LoadFromImage2D(pTexImage);
        if (a2 == 1) {
            pTexImage->Release();
            gbImage2D* img = pTexImage;
            if (img) {
                img->Release();
                delete img;
            }
            pTexImage = NULL;
        }
        isLoaded = 1;
    }
}

// Virtual: base implementation does nothing
void gbTexture::UpdateTexture(int x, int y, int w, int h, gbPixelFmtType srcFmt, void* data) {
}

// 0x10020820 (52B) - Update texture sub-region from image
void gbTexture::UpdateTexture(int x, int y, gbImage2D* img) {
    UpdateTexture(x, y, img->Width, img->Height, img->PixelFmt.Type, img->pBits);
}

// 0x10020860 (40B) - Update entire texture from image
void gbTexture::UpdateTexture(gbImage2D* img) {
    UpdateTexture(0, 0, Width, Height, img->PixelFmt.Type, img->pBits);
}


// ============================================================================
// gbTexture_D3D method implementations
// ============================================================================

// 0x1001ba60 (29B) - Constructor
gbTexture_D3D::gbTexture_D3D(void) : gbTexture() {
    pTex = NULL;
    pDS = NULL;
    m_ImgFormat = 0;
}

// 0x1001baa0 - Virtual destructor: release D3D resources
gbTexture_D3D::~gbTexture_D3D() {
    if (pDS) {
        pDS->Release();
        pDS = NULL;
    }
    if (pTex) {
        pTex->Release();
        pTex = NULL;
    }
}

// Override: return the D3D texture pointer
IDirect3DTexture9* gbTexture_D3D::GetTexture(void) {
    return (IDirect3DTexture9*)pTex;
}

// 0x1001bd30 (356B) - Create texture from raw memory data
void gbTexture_D3D::CreateFromMemory(int w, int h, gbPixelFmtType srcFmt, int levels,
                                      gbPixelFmtType dstFmt, void* data)
{
    if (!data)
        return;

    // Release existing
    if (pTex) {
        pTex->Release();
        pTex = NULL;
    }
    if (pDS) {
        pDS->Release();
        pDS = NULL;
    }

    Width = w;
    Height = h;
    nLevels = levels;
    InFmt.Type = dstFmt;
    InFmt.Bpp = gbPixelFmtBpp(dstFmt);

    D3DFORMAT d3dDstFmt = gbPixelFmtToD3D(dstFmt);
    D3DFORMAT d3dSrcFmt = gbPixelFmtToD3D(srcFmt);

    // Get the D3D device from the global gfx manager
    // In the real engine: ((gbGfxManager_D3D*)g_pGfxManager)->m_pd3dDevice
    IDirect3DDevice9* pDevice = NULL;
    if (g_pGfxManager) {
        // Access device at known offset in gbGfxManager_D3D
        // gbGfxManager_D3D has m_pd3dDevice at a large offset after many fields
        // We use a cast to access it (offset determined from PAL3patch struct layout)
        pDevice = ((gbGfxManager_D3D*)g_pGfxManager)->m_pd3dDevice;
    }
    if (!pDevice)
        return;

    IDirect3DTexture9* pTexture = NULL;
    HRESULT hr = pDevice->CreateTexture(w, h, levels, 0, d3dDstFmt,
                                         D3DPOOL_MANAGED, &pTexture, NULL);
    if (FAILED(hr))
        return;

    pTex = pTexture;

    // Lock the texture and copy pixel data
    D3DLOCKED_RECT lockedRect;
    hr = pTexture->LockRect(0, &lockedRect, NULL, 0);
    if (SUCCEEDED(hr)) {
        int srcBpp = gbPixelFmtBpp(srcFmt);
        int srcPitch = (w * srcBpp + 7) / 8;
        int dstPitch = lockedRect.Pitch;
        int copyBytes = (w * InFmt.Bpp + 7) / 8;

        if (d3dSrcFmt == d3dDstFmt) {
            // Direct copy, row by row
            for (int row = 0; row < h; row++) {
                memcpy((char*)lockedRect.pBits + row * dstPitch,
                       (char*)data + row * srcPitch,
                       copyBytes < srcPitch ? copyBytes : srcPitch);
            }
        } else {
            // Format conversion would happen here
            // For simplicity, do a raw copy (real engine does format conversion)
            for (int row = 0; row < h; row++) {
                memcpy((char*)lockedRect.pBits + row * dstPitch,
                       (char*)data + row * srcPitch,
                       srcPitch < dstPitch ? srcPitch : dstPitch);
            }
        }

        pTexture->UnlockRect(0);
    }

    m_ImgFormat = (ULONG)d3dDstFmt;
    isLoaded = 1;
}

// 0x1001bea0 (219B) - Update existing texture with new data
void gbTexture_D3D::UpdateTexture(int x, int y, int w, int h, gbPixelFmtType srcFmt, void* data) {
    if (!pTex || !data)
        return;

    IDirect3DTexture9* pTexture = (IDirect3DTexture9*)pTex;
    RECT rc;
    rc.left = x;
    rc.top = y;
    rc.right = x + w;
    rc.bottom = y + h;

    D3DLOCKED_RECT lockedRect;
    HRESULT hr = pTexture->LockRect(0, &lockedRect, &rc, 0);
    if (SUCCEEDED(hr)) {
        int srcBpp = gbPixelFmtBpp(srcFmt);
        int srcPitch = (w * srcBpp + 7) / 8;
        int dstPitch = lockedRect.Pitch;

        for (int row = 0; row < h; row++) {
            memcpy((char*)lockedRect.pBits + row * dstPitch,
                   (char*)data + row * srcPitch,
                   srcPitch);
        }

        pTexture->UnlockRect(0);
    }
}

// 0x1001c010 (344B) - Create texture from file data in memory (e.Green. DDS, BMP, TGA)
void gbTexture_D3D::CreateFromFileMemory(void* data, int size) {
    if (!data || size <= 0)
        return;

    // Release existing
    if (pTex) {
        pTex->Release();
        pTex = NULL;
    }
    if (pDS) {
        pDS->Release();
        pDS = NULL;
    }

    IDirect3DDevice9* pDevice = NULL;
    if (g_pGfxManager) {
        pDevice = ((gbGfxManager_D3D*)g_pGfxManager)->m_pd3dDevice;
    }
    if (!pDevice)
        return;

    IDirect3DTexture9* pTexture = NULL;
    HRESULT hr = D3DXCreateTextureFromFileInMemory(pDevice, data, size, &pTexture);
    if (FAILED(hr))
        return;

    pTex = pTexture;

    // Query the resulting texture dimensions
    D3DSURFACE_DESC desc;
    hr = pTexture->GetLevelDesc(0, &desc);
    if (SUCCEEDED(hr)) {
        Width = desc.Width;
        Height = desc.Height;
        m_ImgFormat = (ULONG)desc.Format;
    }

    isLoaded = 1;
}

// 0x1001bf80 (144B) - Create texture for use as render target
int gbTexture_D3D::CreateForRenderTarget(int w, int h, gbPixelFmtType fmt) {
    // Release existing
    if (pTex) {
        pTex->Release();
        pTex = NULL;
    }
    if (pDS) {
        pDS->Release();
        pDS = NULL;
    }

    IDirect3DDevice9* pDevice = NULL;
    if (g_pGfxManager) {
        pDevice = ((gbGfxManager_D3D*)g_pGfxManager)->m_pd3dDevice;
    }
    if (!pDevice)
        return 0;

    D3DFORMAT d3dFmt = gbPixelFmtToD3D(fmt);

    IDirect3DTexture9* pTexture = NULL;
    HRESULT hr = pDevice->CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET,
                                         d3dFmt, D3DPOOL_DEFAULT,
                                         &pTexture, NULL);
    if (FAILED(hr))
        return 0;

    pTex = pTexture;
    Width = w;
    Height = h;
    InFmt.Type = fmt;
    InFmt.Bpp = gbPixelFmtBpp(fmt);
    m_ImgFormat = (ULONG)d3dFmt;
    nLevels = 1;
    isLoaded = 1;

    return 1;
}

// 0x1001c170 (144B) - Get a byte from locked texture data
unsigned char gbTexture_D3D::GetByte(int x, int y) {
    if (!pTex)
        return 0;

    IDirect3DTexture9* pTexture = (IDirect3DTexture9*)pTex;
    D3DLOCKED_RECT lockedRect;
    HRESULT hr = pTexture->LockRect(0, &lockedRect, NULL, D3DLOCK_READONLY);
    if (FAILED(hr))
        return 0;

    int bpp = InFmt.Bpp;
    int offset = y * lockedRect.Pitch + x * (bpp / 8);
    unsigned char result = *((unsigned char*)lockedRect.pBits + offset);

    pTexture->UnlockRect(0);
    return result;
}

// Exported: GetTexName
IDirect3DBaseTexture9* gbTexture_D3D::GetTexName(void) {
    return pTex;
}

// Exported: GetMiscTexName
IDirect3DSurface9* gbTexture_D3D::GetMiscTexName(void) {
    return pDS;
}


// ============================================================================
// gbTextureArray method implementations
// gbTextureArray methods moved to gbTextureArray.cpp

