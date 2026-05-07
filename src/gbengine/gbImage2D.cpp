/**
 * gbengine.dll - gbImage2D
 * 2D image loading and manipulation (IJL15.dll JPEG support)
 */

#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbMisc.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// External globals
extern gbVFileSystem* g_pVFileSys;

// Forward declarations
void __cdecl gbScalePixelData(int mode, int bytesPerPixel, int srcW, int srcH, void* srcData, int dstW, int dstH, void* dstData);

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
    return Width;
}

int gbImage2D::GetHeight(void) {
    return Height;
}

int gbImage2D::GetBitCount(void) {
    return BitCount;
}

unsigned char* gbImage2D::GetBits(void) {
    return (unsigned char*)pBits;
}

// 0x10004150 (44B) - Get pointer to pixel at (x, y)
unsigned char* gbImage2D::GetBits(int x, int y) {
    int offset = (Width * y + x) * BitCount;
    return (unsigned char*)pBits + offset / 8;
}

// 0x10004180 (16B) - Get palette entry
gbColorQuad* gbImage2D::GetPalEntry(int index) {
    return &pPalette[index];
}

gbImage2DInfo* gbImage2D::GetImgInfo(void) {
    return &ImgInfo;
}

gbPixelFmtType gbImage2D::GetPixelFmtType(void) {
    return PixelFmt.Type;
}

// 0x1001ea30 (131B) - Create image buffer
unsigned char* gbImage2D::CreateImage(int w, int h, int bpp) {
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

// Internal format-specific loaders (stubs for now)
static int LoadTGA(gbImage2D* img, char* filename) {
    /* STUB - sub_1001ED50: loads TGA file into img */
    return 0;
}

static int LoadBMP(gbImage2D* img, char* filename) {
    /* STUB - sub_1001EB80: loads BMP file into img */
    return 0;
}

static int LoadPCX(gbImage2D* img, char* filename) {
    /* STUB - sub_1001F0A0: loads PCX file into img */
    return 0;
}

static int LoadJPEG(gbImage2D* img, char* filename) {
    /* STUB - sub_1001F410: loads JPEG file into img */
    return 0;
}

// sub_1001EAC0 - computes ImgInfo derived values
static void gbImage2D_ComputeImgInfo(gbImage2D* img) {
    /* STUB - sub_1001EAC0 */
}

// 0x1001e490 (1262B) - Load image file via extension dispatch
int gbImage2D::LoadImageFile(char* filename, int a3) {
    char Str[256];
    char ext[32];
    int v35 = 0;

    strcpy(Str, filename);
    char* dot = strrchr(Str, '.');
    strcpy(ext, dot);
    *dot = 0;

    if (!gbstricmp(ext, ".tga")) {
        if (!LoadTGA(this, filename))
            return 0;
        v35 = 2;
    } else if (!gbstricmp(ext, ".bmp")) {
        if (!LoadBMP(this, filename))
            return 0;
        v35 = 1;
    } else if (!gbstricmp(ext, ".pcx")) {
        if (!LoadPCX(this, filename))
            return 0;
        v35 = 3;
    } else if (!gbstricmp(ext, ".bit")) {
        gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
        if (!vf)
            return 0;
        g_pVFileSys->Read(&Width, 4u, vf);
        g_pVFileSys->Read(&Height, 4u, vf);
        g_pVFileSys->Read(&BitCount, 4u, vf);
        pBits = (char*)malloc(Width * Height * (BitCount / 8));
        g_pVFileSys->Read(pBits, Width * Height * (BitCount / 8), vf);
        g_pVFileSys->CloseFile(vf);
        v35 = 4;
    } else if (!gbstricmp(ext, ".jpg")) {
        if (!LoadJPEG(this, filename))
            return 0;
        v35 = 5;
    }

    // Initialize ImgInfo
    ImgInfo.isdiskinfo = 0;
    ImgInfo.goal = 0;
    ImgInfo.ngrade = 8;

    int div = 1;
    for (int i = 0; i < ImgInfo.ngrade; i++) {
        ImgInfo.detail[i] = i;
        ImgInfo.wdiv[i] = div;
        ImgInfo.hdiv[i] = div;
        div *= 2;
    }

    ImgInfo.wrap_u = 1;
    ImgInfo.wrap_v = 1;
    ImgInfo.mipmap = 1;
    ImgInfo.minfilter = 1;
    ImgInfo.magfilter = 1;

    gbImage2D_ComputeImgInfo(this);

    // 8-bit expansion
    if (BitCount == 8) {
        unsigned char* src = (unsigned char*)pBits;
        unsigned char* dst;

        if (ImgInfo.goal == 1) {
            // Expand 8bpp to 32bpp ARGB
            dst = (unsigned char*)malloc(4 * Width * Height);
            unsigned char* pDst = dst;
            for (int i = 0; i < Width * Height; i++) {
                *pDst++ = 0xFF;  // B (or first byte)
                *pDst++ = 0xFF;  // G
                *pDst++ = 0xFF;  // R
                *pDst++ = *src;  // A = palette index
                src++;
            }
            BitCount = 32;
        } else {
            // Expand 8bpp to 24bpp grayscale (R=G=B=index)
            dst = (unsigned char*)malloc(3 * Width * Height);
            unsigned char* pDst = dst;
            for (int i = 0; i < Width * Height; i++) {
                *pDst++ = *src;
                *pDst++ = *src;
                *pDst++ = *src;
                src++;
            }
            BitCount = 24;
        }

        free(pBits);
        pBits = (char*)dst;
    }

    // Premultiplied alpha reversal for 32bpp
    if (BitCount == 32) {
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                unsigned char* pixel = (unsigned char*)pBits + 4 * (x + y * Width);
                unsigned char alpha = pixel[3];
                if (alpha != 0 && alpha != 0xFF) {
                    for (int c = 0; c < 3; c++) {
                        int val = 255 * (unsigned int)pixel[c] / (unsigned int)alpha;
                        if (val > 255)
                            val = 255;
                        pixel[c] = (unsigned char)val;
                    }
                }
            }
        }
    }

    // Mipmap downscale
    int level = a3;
    if (level > ImgInfo.ngrade - 1)
        level = ImgInfo.ngrade - 1;
    if (level > 0) {
        int newW = Width / ImgInfo.wdiv[level];
        int newH = Height / ImgInfo.hdiv[level];
        if (pBits) {
            if (newW != Width || newH != Height) {
                void* newBits = malloc(newW * newH * (BitCount / 8));
                gbScalePixelData(5, BitCount / 8, Width, Height, pBits, newW, newH, newBits);
                void* oldBits = pBits;
                Width = newW;
                Height = newH;
                free(oldBits);
                pBits = (char*)newBits;
            }
        }
    }

    // Initialize pixel format
    PixelFmt.Init(BitCount, 0x00FF0000u, 0x0000FF00u, 0x000000FFu,
                  (BitCount != 24) ? 0xFF000000u : 0u);

    return v35;
}

// Internal scaling function (0x100244D0, not exported)
void __cdecl gbScalePixelData(int mode, int bytesPerPixel, int srcW, int srcH, void* srcData, int dstW, int dstH, void* dstData) {
    /* STUB - bilinear pixel scaler, 0x100244D0 */
}

void gbImage2D::ScaleTo(int newW, int newH) {
    if (!pBits) return;
    if (newW == Width && newH == Height) return;

    void* newBits = malloc(BitCount * newH * newW / 8);
    gbScalePixelData(5, BitCount / 8, Width, Height, pBits, newW, newH, newBits);

    void* oldBits = pBits;
    Width = newW;
    Height = newH;
    free(oldBits);
    pBits = (char*)newBits;
}

// 0x1001efc0 (224B) - Write TGA image
void gbImage2D::WriteTGAImage(char* filename) {
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
