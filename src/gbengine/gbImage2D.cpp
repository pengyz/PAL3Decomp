/**
 * gbengine.dll - gbImage2D
 * 2D image loading and manipulation (IJL15.dll JPEG support)
 */

#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <d3dx9.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// External globals
extern gbVFileSystem* g_pVFileSys;

// IJL15.dll - Intel JPEG Library types
struct JPEG_CORE_PROPERTIES {
    char reserved[12];
    void* DIBBytes;
    int DIBWidth;
    int DIBHeight;
    int DIBPadBytes;
    int DIBChannels;
    int DIBColor;
    char reserved2[36];
    char* JPGFile;
    unsigned char* JPGBytes;
    int JPGSizeBytes;
    int JPGWidth;
    int JPGHeight;
    int JPGChannels;
    int JPGColor;
    int JPGSubsampling;
    int jquality;
    char reserved3[28096];
};

static JPEG_CORE_PROPERTIES g_jpegProps;

extern "C" {
    int ijlInit(void* jcprops);
    int ijlRead(void* jcprops, int readtype);
    int ijlWrite(void* jcprops, int writetype);
    int ijlFree(void* jcprops);
}

void gbImage2D::Release(void) {
    /* STUB */
    if (pBits) {
        free(pBits);
        pBits = NULL;
    }
    if (pPalette) {
        free(pPalette);
        pPalette = NULL;
    }
    Width = 0;
    Height = 0;
    BitCount = 0;
    numPalEntry = 0;
}

int gbImage2D::GetWidth(void) {
    /* STUB */
    return Width;
}

int gbImage2D::GetHeight(void) {
    /* STUB */
    return Height;
}

int gbImage2D::GetBitCount(void) {
    /* STUB */
    return BitCount;
}

unsigned char* gbImage2D::GetBits(void) {
    /* STUB */
    return (unsigned char*)pBits;
}

// 0x10004150 (44B) - Get pointer to pixel at (x, y)
unsigned char* gbImage2D::GetBits(int x, int y) {
    /* STUB */
    if (!pBits || x < 0 || y < 0 || x >= Width || y >= Height) {
        return NULL;
    }
    int stride = (Width * BitCount + 7) / 8;
    return (unsigned char*)pBits + y * stride + (x * BitCount) / 8;
}

// 0x10004180 (16B) - Get palette entry
gbColorQuad* gbImage2D::GetPalEntry(int index) {
    /* STUB */
    if (!pPalette)
        return NULL;
    return &pPalette[index];
}

gbImage2DInfo* gbImage2D::GetImgInfo(void) {
    /* STUB */
    return &ImgInfo;
}

gbPixelFmtType gbImage2D::GetPixelFmtType(void) {
    /* STUB */
    return PixelFmt.Type;
}

// 0x1001ea30 (131B) - Create image buffer
unsigned char* gbImage2D::CreateImage(int w, int h, int bpp) {
    /* STUB */
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

    return (unsigned char*)pBits;
}

// 0x1001e490 (1262B) - Load image file via extension dispatch
int gbImage2D::LoadImageFile(char* filename, int flags) {
    /* STUB */
    char localPath[256];
    char ext[32];
    int formatType = 0;

    strncpy(localPath, filename, sizeof(localPath) - 1);
    localPath[sizeof(localPath) - 1] = '\0';

    char* dot = strrchr(localPath, '.');
    if (!dot) return 0;

    strncpy(ext, dot, sizeof(ext) - 1);
    ext[sizeof(ext) - 1] = '\0';
    *dot = '\0';

    D3DXIMAGE_INFO info;
    HRESULT hr = D3DXGetImageInfoFromFile(filename, &info);
    if (FAILED(hr))
        return 0;

    Width = info.Width;
    Height = info.Height;

    D3DFORMAT targetFmt;
    if (flags & 1) {
        targetFmt = D3DFMT_A8R8G8B8;
        BitCount = 32;
    } else {
        switch (info.Format) {
        case D3DFMT_A8R8G8B8:
        case D3DFMT_A8B8G8R8:
            targetFmt = D3DFMT_A8R8G8B8;
            BitCount = 32;
            break;
        case D3DFMT_R8G8B8:
            targetFmt = D3DFMT_R8G8B8;
            BitCount = 24;
            break;
        default:
            targetFmt = D3DFMT_A8R8G8B8;
            BitCount = 32;
            break;
        }
    }

    int bytesPerPixel = (BitCount + 7) / 8;
    int bufSize = Width * Height * bytesPerPixel;
    pBits = (char*)malloc(bufSize);
    if (!pBits)
        return 0;

    IDirect3DSurface9* pSurf = NULL;
    IDirect3DDevice9* pDev = NULL;

    hr = D3DXLoadSurfaceFromFile(pSurf, NULL, NULL, filename, NULL,
                                  D3DX_FILTER_NONE, 0, &info);
    if (FAILED(hr)) {
        memset(pBits, 0, bufSize);
    }

    if (BitCount == 32) {
        unsigned char* pixels = (unsigned char*)pBits;
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                int idx = (y * Width + x) * 4;
                unsigned char alpha = pixels[idx + 3];
                if (alpha > 0 && alpha < 255) {
                    for (int c = 0; c < 3; c++) {
                        unsigned int val = ((unsigned int)pixels[idx + c] * 255) / alpha;
                        if (val > 255) val = 255;
                        pixels[idx + c] = (unsigned char)val;
                    }
                }
            }
        }
    }

    PixelFmt.Init(BitCount, 0x00FF0000, 0x0000FF00, 0x000000FF,
                  (BitCount != 24) ? 0xFF000000 : 0);

    formatType = (BitCount == 32) ? 2 : 1;
    return formatType;
}

void gbImage2D::ScaleTo(int newW, int newH) {
    /* STUB */
    if (!pBits || newW <= 0 || newH <= 0) return;
    if (newW == Width && newH == Height) return;

    /* UNCERTAIN: Scaling algorithm */
    // Simple nearest-neighbor scaling
    int oldStride = (Width * BitCount + 7) / 8;
    int newStride = (newW * BitCount + 7) / 8;
    char* newBits = (char*)malloc(newStride * newH);

    if (newBits) {
        for (int y = 0; y < newH; y++) {
            int srcY = (y * Height) / newH;
            for (int x = 0; x < newW; x++) {
                int srcX = (x * Width) / newW;
                int srcOffset = srcY * oldStride + (srcX * BitCount) / 8;
                int dstOffset = y * newStride + (x * BitCount) / 8;

                if (BitCount == 32) {
                    *(unsigned int*)(newBits + dstOffset) = *(unsigned int*)(pBits + srcOffset);
                } else if (BitCount == 24) {
                    newBits[dstOffset] = pBits[srcOffset];
                    newBits[dstOffset + 1] = pBits[srcOffset + 1];
                    newBits[dstOffset + 2] = pBits[srcOffset + 2];
                }
            }
        }

        free(pBits);
        pBits = newBits;
        Width = newW;
        Height = newH;
    }
}

// 0x1001efc0 (224B) - Write TGA image
void gbImage2D::WriteTGAImage(char* filename) {
    /* STUB */
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

// 0x1001f5f0 (193B) - Write JPEG image using Intel JPEG Library
void gbImage2D::WriteJpegImage(char* filename, int quality) {
    /* STUB */
    JPEG_CORE_PROPERTIES props;
    int result = ijlInit(&props);
    if (result != 0)
        return;
    if (BitCount != 24)
        return;

    int stride = (Width * 3 + 3) & ~3;
    int padBytes = stride - Width * 3;

    props.DIBBytes = pBits;
    props.DIBWidth = Width;
    props.DIBHeight = -Height;
    props.DIBPadBytes = padBytes;
    props.DIBChannels = 3;
    props.DIBColor = 2;
    props.JPGFile = filename;
    props.JPGWidth = Width;
    props.JPGHeight = Height;
    props.JPGChannels = 3;
    props.JPGColor = 3;
    props.JPGSubsampling = 1;
    props.jquality = quality;

    result = ijlWrite(&props, 8);
    if (result == 0) {
        ijlFree(&props);
    }
}

// 0x1001f6c0 (265B) - Write JPEG to memory buffer using Intel JPEG Library
int gbImage2D::WriteJpegToBuffer(unsigned char* buffer, int bufSize) {
    /* STUB */
    int result = ijlInit(&g_jpegProps);
    if (result != 0)
        return 0;
    if (BitCount != 24)
        return 0;

    int stride = (Width * 3 + 3) & ~3;
    int padBytes = stride - Width * 3;

    g_jpegProps.DIBBytes = pBits;
    g_jpegProps.DIBWidth = Width;
    g_jpegProps.DIBHeight = -Height;
    g_jpegProps.DIBPadBytes = padBytes;
    g_jpegProps.DIBChannels = 3;
    g_jpegProps.DIBColor = 2;
    g_jpegProps.JPGFile = NULL;
    g_jpegProps.JPGBytes = buffer;
    g_jpegProps.JPGSizeBytes = (BitCount * Height * Width + 7) / 8;
    g_jpegProps.JPGWidth = Width;
    g_jpegProps.JPGHeight = Height;
    g_jpegProps.JPGChannels = 3;
    g_jpegProps.JPGColor = 3;
    g_jpegProps.JPGSubsampling = 1;
    g_jpegProps.jquality = bufSize;

    result = ijlWrite(&g_jpegProps, 9);
    if (result != 0)
        return 0;

    int written = g_jpegProps.JPGSizeBytes;
    ijlFree(&g_jpegProps);
    return written;
}
