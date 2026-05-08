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

// Static globals
static int g_nImageTotal = 0;
// External globals
extern gbVFileSystem* g_pVFileSys;

// Forward declarations
void __cdecl gbScalePixelData(int mode, int bytesPerPixel, int srcW, int srcH, void* srcData, int dstW, int dstH, void* dstData);

// IJL15.dll - Intel JPEG Library types (sizeof = 0x4E68 = 20072)
struct JPEG_CORE_PROPERTIES {
    int reserved0;              // +0
    void* DIBBytes;             // +4
    int DIBWidth;               // +8
    int DIBHeight;              // +12
    int DIBPadBytes;            // +16
    int DIBChannels;            // +20
    int DIBColor;               // +24
    int DIBSubsampling;         // +28
    char* JPGFile;              // +32
    unsigned char* JPGBytes;    // +36
    int JPGSizeBytes;           // +40
    int JPGWidth;               // +44
    int JPGHeight;              // +48
    int JPGChannels;            // +52
    int JPGColor;               // +56
    int JPGSubsampling;         // +60
    char reserved1[16];         // +64
    int jquality;               // +80
    char reserved2[19988];      // +84
};

static JPEG_CORE_PROPERTIES g_jpegProps;

extern "C" {
    int __stdcall ijlInit(void* jcprops);
    int __stdcall ijlRead(void* jcprops, int readtype);
    int __stdcall ijlWrite(void* jcprops, int writetype);
    int __stdcall ijlFree(void* jcprops);
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

// Internal format-specific loaders (member functions, __thiscall)

// 0x1001EAC0 (183B) - Expand paletted (8-bit indexed) image to 24-bit RGB
void gbImage2D::ConvertPaletteToRGB24(void) {
    if (pPalette) {
        char* newBits = (char*)malloc(3 * Height * Width);
        int i = 0;
        char* savedBits = newBits;
        if (Height * Width > 0) {
            char* dst = newBits + 2;
            do {
                dst += 3;
                unsigned int idx = *((unsigned char*)pBits + i++);
                char* entry = (char*)pPalette + 4 * idx;
                *(dst - 5) = *entry;
                *(dst - 4) = entry[1];
                *(dst - 3) = entry[2];
            } while (i < Height * Width);
        }
        free(pBits);
        pBits = savedBits;
        free(pPalette);
        pPalette = NULL;
        BitCount = 24;
    }
}

// 0x1001EB80 (460B) - Load BMP file
int gbImage2D::LoadBMPFile(char* filename) {
    int result;
    gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vf)
        return 0;

    g_pVFileSys->Seek(vf, 0, 3);
    char* fileSize = (char*)g_pVFileSys->TellPos(vf);
    g_pVFileSys->Seek(vf, 0, 1);

    result = (int)malloc(0x0E);
    int fileHdr = result;
    void* Block = (void*)result;
    if (!result)
        return result;

    g_pVFileSys->Read((void*)result, 0x0E, vf);
    int pixelOffset = *(int*)(fileHdr + 10);

    result = (int)malloc(pixelOffset - 14);
    int infoHdr = result;
    if (!result)
        return result;

    g_pVFileSys->Read((void*)result, pixelOffset - 14, vf);

    result = (int)malloc((size_t)&fileSize[-pixelOffset]);
    pBits = (char*)result;
    if (!result)
        return result;

    g_pVFileSys->Read((void*)result, (size_t)&fileSize[-pixelOffset], vf);
    Width = *(int*)(infoHdr + 4);
    Height = *(int*)(infoHdr + 8);
    int bpp = *(unsigned short*)(infoHdr + 14);
    BitCount = bpp;

    if (bpp == 1 || bpp == 2 || bpp == 4 || bpp == 8) {
        numPalEntry = 1 << bpp;
        result = (int)malloc(4 * (1 << bpp));
        pPalette = (gbColorQuad*)result;
        if (!result)
            return result;

        int i = 0;
        if (numPalEntry > 0) {
            int palSrc = infoHdr + 41;
            do {
                unsigned char b = *(unsigned char*)(palSrc - 1);
                palSrc += 4;
                *((unsigned char*)pPalette + 4 * i) = b;
                *((unsigned char*)pPalette + 4 * i + 1) = *(unsigned char*)(palSrc - 4);
                *((unsigned char*)pPalette + 4 * i + 2) = *(unsigned char*)(palSrc - 3);
                *((unsigned char*)pPalette + 4 * i++ + 3) = 0xFF;
            } while (i < numPalEntry);
        }
    }

    free(Block);
    free((void*)infoHdr);
    g_pVFileSys->CloseFile(vf);
    return 1;
}

// 0x1001ED50 (545B) - Load TGA file
int gbImage2D::LoadTGAFile(char* filename) {
    gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vf)
        return 0;

    // Read 18-byte TGA header
    unsigned char header[18];
    g_pVFileSys->Read(header, 0x12, vf);

    unsigned char idLength = header[0];
    unsigned char colorMapType = header[1];
    unsigned short colorMapLength = *(unsigned short*)&header[3];
    unsigned char colorMapEntrySize = header[7];
    unsigned short width = *(unsigned short*)&header[12];
    unsigned short height = *(unsigned short*)&header[14];
    unsigned char bitCount = header[16];
    unsigned char descriptor = header[17];

    if (idLength)
        g_pVFileSys->Seek(vf, idLength, 2);

    int bytesPerPixel = bitCount >> 3;
    int bytesPerRow = height * bytesPerPixel;
    Width = width;
    int totalSize = width * bytesPerRow;
    Height = height;
    BitCount = bitCount;

    if (colorMapType) {
        if (colorMapEntrySize != 24)
            return 0;

        numPalEntry = colorMapLength;
        pPalette = (gbColorQuad*)malloc(4 * colorMapLength);
        if (!pPalette)
            return 0;

        int i = 0;
        if (numPalEntry > 0) {
            do {
                int off = 4 * i;
                g_pVFileSys->Read((void*)((char*)pPalette + off), 3u, vf);
                ((unsigned char*)pPalette)[off + 3] = 0xFF;
                i++;
            } while (i < numPalEntry);
        }
    }

    pBits = (char*)malloc(totalSize);
    if (!pBits)
        return 0;

    int rowBytes = Width * bytesPerPixel;

    switch (descriptor & 0x30) {
    case 0x20:
        g_pVFileSys->Read(pBits, totalSize, vf);
        break;
    case 0x10:
        return 0;
    case 0x00: {
        int rowSize = rowBytes;
        int y = Height - 1;
        if (y >= 0) {
            int offset = rowSize * y;
            int negRow = -rowSize;
            int count = Height;
            do {
                g_pVFileSys->Read(pBits + offset, rowSize, vf);
                offset += negRow;
                count--;
            } while (count);
        }
        break;
    }
    case 0x30:
        break;
    }

    g_pVFileSys->CloseFile(vf);
    return 1;
}

// 0x1001F0A0 (867B) - Load PCX file with RLE decoding
int gbImage2D::LoadPCXFile(char* filename) {
    int decoded = 0;
    gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vf)
        return 0;

    int ch1 = g_pVFileSys->ReadChar(vf);
    if (ch1 != 10 || g_pVFileSys->ReadChar(vf) != 5) {
        g_pVFileSys->CloseFile(vf);
        return 0;
    }

    g_pVFileSys->Rewind(vf);
    g_pVFileSys->ReadChar(vf);
    g_pVFileSys->ReadChar(vf);
    g_pVFileSys->ReadChar(vf);
    g_pVFileSys->ReadChar(vf);

    int xmin_lo = g_pVFileSys->ReadChar(vf);
    int xmin_hi = g_pVFileSys->ReadChar(vf);
    int ymin_lo = g_pVFileSys->ReadChar(vf);
    int ymin_hi = g_pVFileSys->ReadChar(vf);
    int xmax_lo = g_pVFileSys->ReadChar(vf);
    int xmax_hi = g_pVFileSys->ReadChar(vf);
    int ymax_lo = g_pVFileSys->ReadChar(vf);
    int ymax_hi = g_pVFileSys->ReadChar(vf);

    int w = (xmax_lo | (xmax_hi << 8)) - (xmin_lo | (xmin_hi << 8)) + 1;
    Width = w;
    int h = (ymax_lo | (ymax_hi << 8)) - (ymin_lo | (ymin_hi << 8)) + 1;
    Height = h;

    void* rawBuf = malloc(w * h);

    g_pVFileSys->Seek(vf, 128, 1);

    if (Height * Width > 0) {
        do {
            int byte = g_pVFileSys->ReadChar(vf);
            if (byte <= 191) {
                *((unsigned char*)rawBuf + decoded) = byte;
                decoded++;
            } else {
                int count = byte & 0x3F;
                char value = g_pVFileSys->ReadChar(vf);
                if (count > 0) {
                    memset((char*)rawBuf + decoded, value, count);
                    decoded += count;
                }
            }
        } while (decoded < Height * Width);
    }

    void* palette = malloc(0x300);
    g_pVFileSys->Seek(vf, -769, 3);

    if (g_pVFileSys->ReadChar(vf) == 12) {
        g_pVFileSys->Read(palette, 0x300, vf);

        BitCount = 24;
        char* outBuf = (char*)malloc(24 * Width * Height / 8);
        pBits = (char*)outBuf;

        int y = 0;
        if (Height > 0) {
            do {
                int x = 0;
                int ww = Width;
                for (; x < ww; x++) {
                    unsigned char idx = *((unsigned char*)rawBuf + x + y * ww);
                    int palOff = 3 * idx;
                    *outBuf = ((char*)palette)[palOff];
                    outBuf++;
                    *outBuf = ((char*)palette)[palOff + 1];
                    *outBuf++;
                    *outBuf = ((char*)palette)[palOff + 2];
                    ww = Width;
                    outBuf++;
                }
                y++;
            } while (y < Height);
        }

        free(rawBuf);
        free(palette);
        g_pVFileSys->CloseFile(vf);
        return 1;
    } else {
        free(rawBuf);
        free(palette);
        g_pVFileSys->CloseFile(vf);
        return 0;
    }
}

// 0x1001F410 (473B) - Load JPEG file via Intel JPEG Library (IJL15.dll)
int gbImage2D::LoadJPEGFile(char* filename) {
    gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vf)
        return 0;

    long fileSize = g_pVFileSys->GetFileSize(vf);
    void* fileBuf = malloc(fileSize);
    g_pVFileSys->Read(fileBuf, fileSize, vf);
    g_pVFileSys->CloseFile(vf);

    JPEG_CORE_PROPERTIES props;
    if (ijlInit(&props)) {
        free(fileBuf);
        return 0;
    }

    props.JPGFile = NULL;
    props.JPGBytes = (unsigned char*)fileBuf;
    props.JPGSizeBytes = fileSize;

    if (ijlRead(&props, 1)) {
        free(fileBuf);
        return 0;
    }

    int jpgWidth = props.JPGWidth;
    int jpgHeight = props.JPGHeight;
    void* outBuf = malloc(3 * jpgWidth * jpgHeight);

    if (!outBuf) {
        free(fileBuf);
        free(0);
        return 0;
    }

    props.DIBWidth = jpgWidth;
    props.DIBHeight = -jpgHeight;
    props.DIBChannels = 3;
    props.DIBColor = 2;
    props.DIBPadBytes = 0;
    props.DIBBytes = outBuf;

    if (props.JPGColor == 1) {
        props.JPGSubsampling = 4;
    } else if (props.JPGColor == 3) {
        props.JPGSubsampling = 3;
    } else {
        props.DIBColor = 255;
        props.JPGSubsampling = 255;
    }

    if (ijlRead(&props, 3)) {
        free(outBuf);
        free(fileBuf);
        return 0;
    }

    ijlFree(&props);
    Width = jpgWidth;
    Height = jpgHeight;
    BitCount = 24;
    pBits = (char*)outBuf;
    free(fileBuf);
    return 1;
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
        if (!LoadTGAFile(filename))
            return 0;
        v35 = 2;
    } else if (!gbstricmp(ext, ".bmp")) {
        if (!LoadBMPFile(filename))
            return 0;
        v35 = 1;
    } else if (!gbstricmp(ext, ".pcx")) {
        if (!LoadPCXFile(filename))
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
        if (!LoadJPEGFile(filename))
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

    ConvertPaletteToRGB24();

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

// FUN_10024e10 - Convert pixel data to float array based on mode
static void gbPixelToFloat(int mode, int bytesPerPixel, int srcW, int srcH, void* srcData, float* dstFloats) {
    int totalElements = bytesPerPixel * srcW * srcH;
    int i;
    switch (mode) {
    case 0:
        for (i = 0; i < totalElements; i++) {
            dstFloats[i] = (float)(int)((float*)srcData)[i];
        }
        break;
    case 1:
        for (i = 0; i < totalElements; i++) {
            dstFloats[i] = (float)(short)((unsigned short*)srcData)[i];
        }
        break;
    case 2:
        for (i = 0; i < totalElements; i++) {
            dstFloats[i] = (float)(int)((char*)srcData)[i];
        }
        break;
    case 3:
        for (i = 0; i < totalElements; i++) {
            dstFloats[i] = (float)(unsigned int)((float*)srcData)[i];
        }
        break;
    case 4:
        for (i = 0; i < totalElements; i++) {
            dstFloats[i] = (float)((unsigned short*)srcData)[i];
        }
        break;
    case 5:
        for (i = 0; i < totalElements; i++) {
            dstFloats[i] = (float)((unsigned char*)srcData)[i];
        }
        break;
    case 6:
        for (i = 0; i < totalElements; i++) {
            dstFloats[i] = ((float*)srcData)[i];
        }
        break;
    }
}

// Internal scaling function (0x100244D0, not exported)
void __cdecl gbScalePixelData(int mode, int bytesPerPixel, int srcW, int srcH, void* srcData, int dstW, int dstH, void* dstData) {
    float xRatio, yRatio;
    int x, y, c;

    if (dstW >= 2)
        xRatio = (float)(srcW - 1) / (float)(dstW - 1);
    else
        xRatio = (float)(srcW - 1);

    if (dstH >= 2)
        yRatio = (float)(srcH - 1) / (float)(dstH - 1);
    else
        yRatio = (float)(srcH - 1);

    if (mode == 5) {
        // Direct byte-level scaling
        unsigned char* src = (unsigned char*)srcData;
        unsigned char* dst = (unsigned char*)dstData;

        if (xRatio >= 1.0f || yRatio >= 1.0f) {
            // Box filter (downscaling)
            for (y = 0; y < dstH; y++) {
                int srcRowStart = (int)(y * yRatio);
                int srcRowEnd = srcRowStart + 1;
                if (srcRowEnd > srcH - 1)
                    srcRowEnd = srcH - 1;
                for (x = 0; x < dstW; x++) {
                    int srcColStart = (int)(x * xRatio);
                    int srcColEnd = srcColStart + 1;
                    if (srcColEnd > srcW - 1)
                        srcColEnd = srcW - 1;
                    for (c = 0; c < bytesPerPixel; c++) {
                        int sum = 0;
                        int row, col;
                        for (row = srcRowStart; row <= srcRowEnd; row++) {
                            for (col = srcColStart; col <= srcColEnd; col++) {
                                sum += src[(row * srcW + col) * bytesPerPixel + c];
                            }
                        }
                        dst[(y * dstW + x) * bytesPerPixel + c] = (unsigned char)(sum / ((srcRowEnd - srcRowStart + 1) * (srcColEnd - srcColStart + 1)));
                    }
                }
            }
        } else {
            // Bilinear interpolation (upscaling)
            for (y = 0; y < dstH; y++) {
                float srcY_f = y * yRatio;
                int srcY0 = (int)srcY_f;
                int srcY1 = srcY0 + 1;
                if (srcY1 > srcH - 1)
                    srcY1 = srcH - 1;
                float fracY = srcY_f - (float)srcY0;
                for (x = 0; x < dstW; x++) {
                    float srcX_f = x * xRatio;
                    int srcX0 = (int)srcX_f;
                    int srcX1 = srcX0 + 1;
                    if (srcX1 > srcW - 1)
                        srcX1 = srcW - 1;
                    float fracX = srcX_f - (float)srcX0;
                    for (c = 0; c < bytesPerPixel; c++) {
                        float p00 = (float)src[(srcY0 * srcW + srcX0) * bytesPerPixel + c];
                        float p10 = (float)src[(srcY0 * srcW + srcX1) * bytesPerPixel + c];
                        float p01 = (float)src[(srcY1 * srcW + srcX0) * bytesPerPixel + c];
                        float p11 = (float)src[(srcY1 * srcW + srcX1) * bytesPerPixel + c];
                        float top = (1.0f - fracX) * p00 + fracX * p10;
                        float bot = (1.0f - fracX) * p01 + fracX * p11;
                        float val = (1.0f - fracY) * top + fracY * bot;
                        dst[(y * dstW + x) * bytesPerPixel + c] = (unsigned char)(int)val;
                    }
                }
            }
        }
    } else {
        // Float intermediate path
        float* floatSrc = (float*)malloc(bytesPerPixel * srcW * srcH * sizeof(float));
        float* floatDst = (float*)malloc(bytesPerPixel * dstW * dstH * sizeof(float));

        // Convert source to float
        gbPixelToFloat(mode, bytesPerPixel, srcW, srcH, srcData, floatSrc);

        // Scale in float domain
        if (xRatio >= 1.0f || yRatio >= 1.0f) {
            // Box filter (downscaling) on floats
            for (y = 0; y < dstH; y++) {
                int srcRowStart = (int)(y * yRatio);
                int srcRowEnd = srcRowStart + 1;
                if (srcRowEnd > srcH - 1)
                    srcRowEnd = srcH - 1;
                for (x = 0; x < dstW; x++) {
                    int srcColStart = (int)(x * xRatio);
                    int srcColEnd = srcColStart + 1;
                    if (srcColEnd > srcW - 1)
                        srcColEnd = srcW - 1;
                    for (c = 0; c < bytesPerPixel; c++) {
                        float sum = 0.0f;
                        int row, col;
                        for (row = srcRowStart; row <= srcRowEnd; row++) {
                            for (col = srcColStart; col <= srcColEnd; col++) {
                                sum += floatSrc[(row * srcW + col) * bytesPerPixel + c];
                            }
                        }
                        floatDst[(y * dstW + x) * bytesPerPixel + c] = sum / (float)((srcRowEnd - srcRowStart + 1) * (srcColEnd - srcColStart + 1));
                    }
                }
            }
        } else {
            // Bilinear interpolation (upscaling) on floats
            for (y = 0; y < dstH; y++) {
                float srcY_f = y * yRatio;
                int srcY0 = (int)srcY_f;
                int srcY1 = srcY0 + 1;
                if (srcY1 > srcH - 1)
                    srcY1 = srcH - 1;
                float fracY = srcY_f - (float)srcY0;
                for (x = 0; x < dstW; x++) {
                    float srcX_f = x * xRatio;
                    int srcX0 = (int)srcX_f;
                    int srcX1 = srcX0 + 1;
                    if (srcX1 > srcW - 1)
                        srcX1 = srcW - 1;
                    float fracX = srcX_f - (float)srcX0;
                    for (c = 0; c < bytesPerPixel; c++) {
                        float p00 = floatSrc[(srcY0 * srcW + srcX0) * bytesPerPixel + c];
                        float p10 = floatSrc[(srcY0 * srcW + srcX1) * bytesPerPixel + c];
                        float p01 = floatSrc[(srcY1 * srcW + srcX0) * bytesPerPixel + c];
                        float p11 = floatSrc[(srcY1 * srcW + srcX1) * bytesPerPixel + c];
                        float top = (1.0f - fracX) * p00 + fracX * p10;
                        float bot = (1.0f - fracX) * p01 + fracX * p11;
                        floatDst[(y * dstW + x) * bytesPerPixel + c] = (1.0f - fracY) * top + fracY * bot;
                    }
                }
            }
        }

        // Convert float output back to destination format
        int totalElements = bytesPerPixel * dstW * dstH;
        int i;
        switch (mode) {
        case 0:
        case 3:
            for (i = 0; i < totalElements; i++) {
                ((float*)dstData)[i] = floatDst[i];
            }
            break;
        case 1:
        case 4:
            for (i = 0; i < totalElements; i++) {
                ((unsigned short*)dstData)[i] = (unsigned short)(int)floatDst[i];
            }
            break;
        case 2:
            for (i = 0; i < totalElements; i++) {
                ((unsigned char*)dstData)[i] = (unsigned char)(int)floatDst[i];
            }
            break;
        case 6:
            for (i = 0; i < totalElements; i++) {
                ((float*)dstData)[i] = floatDst[i];
            }
            break;
        }

        free(floatSrc);
        free(floatDst);
    }
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

// GlobalImageInit - 0x1001E3D0 (11B)
void GlobalImageInit() {
    g_nImageTotal = 0;
}
