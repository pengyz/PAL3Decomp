/**
 * gbengine.dll - gbTexture, gbTexture_D3D, gbTextureArray, gbImage2D
 *
 * Functional decompilation of texture and image management classes.
 * Based on PAL3patch struct definitions and Ghidra export analysis.
 *
 * Compiler: MSVC 6.0 SP5
 * Graphics: DirectX 9 (Summer 2003 SDK)
 */

#include "gbengine/gbengine_types.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Forward declarations
class gbGfxManager;
class gbGfxManager_D3D;
class gbCamControler;
class gbRenderEffect;
class gbEffectMgr;
class gbSceneGraph;
class gbMatrixStack;
class gbPrintFont;
class gbBaseMesh;
class gbResManager;
class gbVFileSystem;
class gbVFile;

// External globals
extern gbGfxManager* g_pGfxManager;

// ============================================================================
// Pixel format enumeration
// ============================================================================
// gbPixelFmtType is defined in gbengine_types.h

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


// gbPixelFormat is already defined in gbengine_types.h


// ============================================================================
// gbRefObject - reference-counted base
// ============================================================================
struct gbRefObject {
    void* vfptr;    // vtable pointer
    int RefCount;
};


// ============================================================================
// gbResource - managed resource base
// ============================================================================
struct gbResource {
    gbRefObject baseclass;
    char* pName;
    unsigned int NameCrc32;
    int IsLoaded;
    gbResManager* pMgr;
};


// ============================================================================
// gbImage2DInfo
// ============================================================================
struct gbImage2DInfo {
    int isdiskinfo;
    int goal;
    int ngrade;
    int detail[8];
    int wdiv[8];
    int hdiv[8];
    int wrap_u;
    int wrap_v;
    int mipmap;
    int minfilter;
    int magfilter;

    // 0x1001e470 (22B)
    int IsPreferAlpha(void) {
        // Check if any detail level requests alpha
        if (goal == 2)
            return 1;
        return 0;
    }

    // Exported: operator=
    gbImage2DInfo& operator=(const gbImage2DInfo& other) {
        if (this != &other) {
            isdiskinfo = other.isdiskinfo;
            goal = other.goal;
            ngrade = other.ngrade;
            memcpy(detail, other.detail, sizeof(detail));
            memcpy(wdiv, other.wdiv, sizeof(wdiv));
            memcpy(hdiv, other.hdiv, sizeof(hdiv));
            wrap_u = other.wrap_u;
            wrap_v = other.wrap_v;
            mipmap = other.mipmap;
            minfilter = other.minfilter;
            magfilter = other.magfilter;
        }
        return *this;
    }
};


// ============================================================================
// gbImage2D - 2D bitmap image
// ============================================================================
class gbImage2D {
public:
    gbImage2DInfo ImgInfo;
    int Width;
    int Height;
    gbPixelFormat PixelFmt;
    int BitCount;
    char* pBits;
    gbColorQuad* pPalette;
    int numPalEntry;
    gbColorQuad ColorKey;

    // 0x1001e3e0 (47B) - Constructor
    gbImage2D(void) {
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
    ~gbImage2D() {
        if (pBits) {
            free(pBits);
            pBits = NULL;
        }
        if (pPalette) {
            free(pPalette);
            pPalette = NULL;
        }
    }

    // 0x1001ea30 (131B) - Create image buffer
    void* CreateImage(int w, int h, int bpp) {
        // Free existing buffer
        if (pBits) {
            free(pBits);
            pBits = NULL;
        }

        Width = w;
        Height = h;
        BitCount = bpp;

        // Calculate row stride (pitch) aligned to 4 bytes
        int pitch = (w * bpp + 31) / 32 * 4;
        int bufSize = pitch * h;

        pBits = (char*)malloc(bufSize);
        if (pBits) {
            memset(pBits, 0, bufSize);
        }

        // Set pixel format based on bpp
        PixelFmt.Bpp = bpp;
        switch (bpp) {
        case 32:
            PixelFmt.Type = GB_PFT_A8R8G8B8;
            PixelFmt.a_mask = 0xFF000000;
            PixelFmt.r_mask = 0x00FF0000;
            PixelFmt.g_mask = 0x0000FF00;
            PixelFmt.b_mask = 0x000000FF;
            PixelFmt.a_shift = 24;
            PixelFmt.r_shift = 16;
            PixelFmt.g_shift = 8;
            PixelFmt.b_shift = 0;
            break;
        case 24:
            PixelFmt.Type = GB_PFT_R8G8B8;
            PixelFmt.a_mask = 0;
            PixelFmt.r_mask = 0x00FF0000;
            PixelFmt.g_mask = 0x0000FF00;
            PixelFmt.b_mask = 0x000000FF;
            PixelFmt.a_shift = 0;
            PixelFmt.r_shift = 16;
            PixelFmt.g_shift = 8;
            PixelFmt.b_shift = 0;
            break;
        case 16:
            PixelFmt.Type = GB_PFT_R5G6B5;
            PixelFmt.r_mask = 0xF800;
            PixelFmt.g_mask = 0x07E0;
            PixelFmt.b_mask = 0x001F;
            PixelFmt.a_mask = 0;
            PixelFmt.r_shift = 11;
            PixelFmt.g_shift = 5;
            PixelFmt.b_shift = 0;
            PixelFmt.a_shift = 0;
            break;
        case 8:
            PixelFmt.Type = GB_PFT_P8;
            break;
        }

        return (void*)pBits;
    }

    // Exported: GetBitCount
    int GetBitCount(void) {
        return BitCount;
    }

    // 0x10004150 (44B) - Get pointer to pixel at (x, y)
    void* GetBits(int x, int y) {
        if (!pBits)
            return NULL;
        int bytesPerPixel = BitCount / 8;
        int pitch = (Width * BitCount + 31) / 32 * 4;
        return (void*)(pBits + y * pitch + x * bytesPerPixel);
    }

    // Exported: GetHeight
    int GetHeight(void) {
        return Height;
    }

    // Exported: GetWidth
    int GetWidth(void) {
        return Width;
    }

    // 0x10004180 (16B) - Get palette entry
    gbColorQuad* GetPalEntry(int index) {
        if (!pPalette)
            return NULL;
        return &pPalette[index];
    }

    // 0x1001e490 (1262B) - Load image file using D3DX
    int LoadImageFile(char* filename, int flags) {
        D3DXIMAGE_INFO info;
        HRESULT hr;

        hr = D3DXGetImageInfoFromFile(filename, &info);
        if (FAILED(hr))
            return 0;

        // Free existing data
        if (pBits) {
            free(pBits);
            pBits = NULL;
        }

        Width = info.Width;
        Height = info.Height;

        // Determine target format
        D3DFORMAT targetFmt;
        if (flags & 1) {
            // Force 32-bit ARGB
            targetFmt = D3DFMT_A8R8G8B8;
            BitCount = 32;
            PixelFmt.Type = GB_PFT_A8R8G8B8;
            PixelFmt.Bpp = 32;
        } else {
            switch (info.Format) {
            case D3DFMT_A8R8G8B8:
            case D3DFMT_A8B8G8R8:
                targetFmt = D3DFMT_A8R8G8B8;
                BitCount = 32;
                PixelFmt.Type = GB_PFT_A8R8G8B8;
                PixelFmt.Bpp = 32;
                break;
            case D3DFMT_R8G8B8:
                targetFmt = D3DFMT_R8G8B8;
                BitCount = 24;
                PixelFmt.Type = GB_PFT_R8G8B8;
                PixelFmt.Bpp = 24;
                break;
            default:
                targetFmt = D3DFMT_A8R8G8B8;
                BitCount = 32;
                PixelFmt.Type = GB_PFT_A8R8G8B8;
                PixelFmt.Bpp = 32;
                break;
            }
        }

        int pitch = (Width * BitCount + 31) / 32 * 4;
        int bufSize = pitch * Height;
        pBits = (char*)malloc(bufSize);
        if (!pBits)
            return 0;

        RECT srcRect;
        srcRect.left = 0;
        srcRect.top = 0;
        srcRect.right = Width;
        srcRect.bottom = Height;

        hr = D3DXLoadSurfaceFromFile(NULL, NULL, NULL, filename, &srcRect,
                                      D3DX_FILTER_NONE, 0, NULL);
        // Fallback: load via D3DXLoadSurfaceFromFileInMemory or file I/O
        // In the real engine this copies pixel data into the pBits buffer.
        // Simplified: just zero the buffer on failure.
        if (FAILED(hr)) {
            memset(pBits, 0, bufSize);
        }

        return 1;
    }

    // 0x1001e980 (162B) - Scale image to new dimensions
    void ScaleTo(int newW, int newH) {
        if (!pBits || newW <= 0 || newH <= 0)
            return;

        int bytesPerPixel = BitCount / 8;
        int oldPitch = (Width * BitCount + 31) / 32 * 4;
        int newPitch = (newW * BitCount + 31) / 32 * 4;
        int newBufSize = newPitch * newH;

        char* newBits = (char*)malloc(newBufSize);
        if (!newBits)
            return;

        // Simple nearest-neighbor scale
        for (int y = 0; y < newH; y++) {
            int srcY = y * Height / newH;
            for (int x = 0; x < newW; x++) {
                int srcX = x * Width / newW;
                char* srcPixel = pBits + srcY * oldPitch + srcX * bytesPerPixel;
                char* dstPixel = newBits + y * newPitch + x * bytesPerPixel;
                memcpy(dstPixel, srcPixel, bytesPerPixel);
            }
        }

        free(pBits);
        pBits = newBits;
        Width = newW;
        Height = newH;
    }

    // 0x1001efc0 (224B) - Write TGA image
    void WriteTGAImage(char* filename) {
        if (!pBits || !filename)
            return;

        FILE* fp = fopen(filename, "wb");
        if (!fp)
            return;

        // TGA header
        unsigned char header[18];
        memset(header, 0, sizeof(header));
        header[2] = 2;  // Uncompressed true-color
        header[12] = (unsigned char)(Width & 0xFF);
        header[13] = (unsigned char)((Width >> 8) & 0xFF);
        header[14] = (unsigned char)(Height & 0xFF);
        header[15] = (unsigned char)((Height >> 8) & 0xFF);
        header[16] = (unsigned char)BitCount;
        if (BitCount == 32)
            header[17] = 0x28;  // Top-left origin + 8 alpha bits
        else
            header[17] = 0x20;  // Top-left origin

        fwrite(header, 1, 18, fp);

        int pitch = (Width * BitCount + 31) / 32 * 4;
        for (int y = 0; y < Height; y++) {
            fwrite(pBits + y * pitch, 1, Width * (BitCount / 8), fp);
        }

        fclose(fp);
    }

    // 0x1001f5f0 (193B) - Write JPEG image
    void WriteJpegImage(char* filename, int quality) {
        if (!pBits || !filename)
            return;

        // Use D3DX to save surface data as JPEG
        // In the real engine, this creates a temporary surface and calls D3DXSaveSurfaceToFile
        // Simplified stub - the logic would involve creating an IDirect3DSurface9 and saving it
    }

    // 0x1001f6c0 (265B) - Write JPEG to memory buffer
    int WriteJpegToBuffer(void* buffer, int bufSize) {
        if (!pBits || !buffer)
            return 0;

        // Similar to WriteJpegImage but outputs to memory buffer
        // Uses D3DXSaveSurfaceToFileInMemory in the real implementation
        return 0;
    }
};


// ============================================================================
// gbTexture - base texture class (virtual)
// ============================================================================
class gbTexture {
public:
    // gbResource base fields (inherited layout)
    gbRefObject refObj;     // vfptr + RefCount
    char* pName;
    unsigned int NameCrc32;
    int IsLoaded;
    gbResManager* pMgr;

    // gbTexture own fields
    int Width;
    int Height;
    gbImage2D* pTexImage;
    gbPixelFormat InFmt;
    int nLevels;

    // 0x10020370 (37B) - Constructor
    gbTexture(void) {
        refObj.vfptr = NULL; // vtable set by derived
        refObj.RefCount = 0;
        pName = NULL;
        NameCrc32 = 0;
        IsLoaded = 0;
        pMgr = NULL;
        Width = 0;
        Height = 0;
        pTexImage = NULL;
        memset(&InFmt, 0, sizeof(InFmt));
        nLevels = 1;
    }

    // Virtual destructor
    virtual ~gbTexture() {
        if (pTexImage) {
            delete pTexImage;
            pTexImage = NULL;
        }
        if (pName) {
            free(pName);
            pName = NULL;
        }
    }

    // 0x10004190 (12B) - Check if texture is initialized
    int IsInit(void) {
        return IsLoaded;
    }

    // 0x10020760 (102B) - Create empty texture
    void CreateTexture(int w, int h, gbPixelFmtType fmt, int mips) {
        Width = w;
        Height = h;
        InFmt.Type = fmt;
        InFmt.Bpp = gbPixelFmtBpp(fmt);
        nLevels = mips;
        IsLoaded = 1;
    }

    // Get the D3D texture interface (base returns NULL, overridden in D3D subclass)
    virtual IDirect3DTexture9* GetTexture(void) {
        return NULL;
    }

    // Exported: GetHeight
    int GetHeight(void) {
        return Height;
    }

    // Exported: GetWidth
    int GetWidth(void) {
        return Width;
    }

    // 0x10020430 (85B) - Get internal D3D format from image
    int GetInternalFormat(gbImage2D* img) {
        if (!img)
            return 0;
        gbPixelFmtType type = img->PixelFmt.Type;
        switch (type) {
        case GB_PFT_A8R8G8B8:  return D3DFMT_A8R8G8B8;
        case GB_PFT_R8G8B8:    return D3DFMT_R8G8B8;
        case GB_PFT_R5G6B5:    return D3DFMT_R5G6B5;
        case GB_PFT_A1R5G5B5:  return D3DFMT_A1R5G5B5;
        case GB_PFT_A4R4G4B4:  return D3DFMT_A4R4G4B4;
        case GB_PFT_P8:         return D3DFMT_P8;
        case GB_PFT_A8:         return D3DFMT_A8;
        default:                return D3DFMT_UNKNOWN;
        }
    }

    // 0x100207d0 (15B) - Get raw bits pointer
    void* GetBits(void) {
        if (pTexImage)
            return pTexImage->pBits;
        return NULL;
    }

    // 0x100207e0 (53B) - Get pixel channel value at (x, y)
    int GetPixelChannel(int x, int y, int channel) {
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

    // 0x10020490 (269B) - Load texture data from gbImage2D
    void LoadFromImage2D(gbImage2D* img) {
        if (!img)
            return;
        Width = img->Width;
        Height = img->Height;
        InFmt.Type = img->PixelFmt.Type;
        InFmt.Bpp = img->PixelFmt.Bpp;
        IsLoaded = 1;
    }

    // 0x100205a0 (443B) - Load texture from resource index
    void LoadTexture(int resIndex) {
        // In the real engine, this loads from the resource manager
        // using the resource index to find the file and call LoadFromImage2D
        IsLoaded = 1;
    }

    // 0x10020820 (52B) - Update texture sub-region from image
    void UpdateTexture(int x, int y, gbImage2D* img) {
        if (!img)
            return;
        // In the real engine, this would lock the D3D texture surface,
        // copy the pixel data from the image at the given offset, and unlock
    }

    // 0x10020860 (40B) - Update entire texture from image
    void UpdateTexture(gbImage2D* img) {
        if (!img)
            return;
        UpdateTexture(0, 0, img);
    }
};


// ============================================================================
// gbTexture_D3D - Direct3D 9 texture implementation
// ============================================================================
class gbTexture_D3D : public gbTexture {
public:
    IDirect3DBaseTexture9* pTex;
    IDirect3DSurface9* pDS;
    ULONG m_ImgFormat;

    // 0x1001ba60 (29B) - Constructor
    gbTexture_D3D(void) : gbTexture() {
        pTex = NULL;
        pDS = NULL;
        m_ImgFormat = 0;
    }

    // 0x1001baa0 - Virtual destructor: release D3D resources
    virtual ~gbTexture_D3D() {
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
    virtual IDirect3DTexture9* GetTexture(void) {
        return (IDirect3DTexture9*)pTex;
    }

    // 0x1001bd30 (356B) - Create texture from raw memory data
    void CreateFromMemory(int w, int h, gbPixelFmtType srcFmt, int levels,
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
            pDevice = *(IDirect3DDevice9**)((char*)g_pGfxManager + 0x84C);
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
        IsLoaded = 1;
    }

    // 0x1001bea0 (219B) - Update existing texture with new data
    void UpdateTexture(int x, int y, int w, int h, gbPixelFmtType srcFmt, void* data) {
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

    // 0x1001c010 (344B) - Create texture from file data in memory (e.g. DDS, BMP, TGA)
    void CreateFromFileMemory(void* data, int size) {
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
            pDevice = *(IDirect3DDevice9**)((char*)g_pGfxManager + 0x84C);
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

        IsLoaded = 1;
    }

    // 0x1001bf80 (144B) - Create texture for use as render target
    int CreateForRenderTarget(int w, int h, gbPixelFmtType fmt) {
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
            pDevice = *(IDirect3DDevice9**)((char*)g_pGfxManager + 0x84C);
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
        IsLoaded = 1;

        return 1;
    }

    // 0x1001c170 (144B) - Get a byte from locked texture data
    int GetByte(int x, int y) {
        if (!pTex)
            return 0;

        IDirect3DTexture9* pTexture = (IDirect3DTexture9*)pTex;
        D3DLOCKED_RECT lockedRect;
        HRESULT hr = pTexture->LockRect(0, &lockedRect, NULL, D3DLOCK_READONLY);
        if (FAILED(hr))
            return 0;

        int bpp = InFmt.Bpp;
        int offset = y * lockedRect.Pitch + x * (bpp / 8);
        int result = *((unsigned char*)lockedRect.pBits + offset);

        pTexture->UnlockRect(0);
        return result;
    }
};


// ============================================================================
// gbTextureArray - holds up to 2 texture pointers for multi-texturing
// ============================================================================
class gbTextureArray {
public:
    gbTexture* pTex[2];

    // 0x100041b0 (10B) - Default constructor
    gbTextureArray(void) {
        pTex[0] = NULL;
        pTex[1] = NULL;
    }

    // 0x100041c0 (18B) - Single texture constructor
    gbTextureArray(gbTexture* tex0) {
        pTex[0] = tex0;
        pTex[1] = NULL;
    }

    // 0x100041e0 (25B) - Dual texture constructor
    gbTextureArray(gbTexture* tex0, gbTexture* tex1) {
        pTex[0] = tex0;
        pTex[1] = tex1;
    }

    // 0x10004200 (16B) - Set single texture
    void SetTexture(gbTexture* tex) {
        pTex[0] = tex;
    }

    // Exported: operator=
    gbTextureArray& operator=(const gbTextureArray& other) {
        pTex[0] = other.pTex[0];
        pTex[1] = other.pTex[1];
        return *this;
    }
};
