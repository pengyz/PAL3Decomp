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

// Internal format-specific loaders

// sub_1001ED50 (454B) - Load TGA file
static int LoadTGA(gbImage2D* img, char* filename) {
    gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vf)
        return 0;

    // Read 18-byte TGA header
    unsigned char header[18];
    g_pVFileSys->Read(header, 18, vf);

    unsigned char idLength = header[0];
    unsigned char colorMapType = header[1];
    // header[2] = image type (unused explicitly)
    // Color map spec: header[3..7]
    unsigned char colorMapEntrySize = header[7];

    short width = *(short*)&header[12];
    short height = *(short*)&header[14];
    unsigned char bitCount = header[16];
    unsigned char descriptor = header[17];

    // Skip ID field if present
    if (idLength != 0) {
        g_pVFileSys->Seek(vf, idLength, GBVFS_SEEK_CUR);
    }

    img->Width = width;
    img->Height = height;
    img->BitCount = bitCount;

    // Read color map (palette) if present
    if (colorMapType != 0) {
        short numEntries = *(short*)&header[5];
        img->numPalEntry = numEntries;
        img->pPalette = (gbColorQuad*)malloc(numEntries * sizeof(gbColorQuad));
        for (int i = 0; i < numEntries; i++) {
            unsigned char entry[4];
            int entryBytes = colorMapEntrySize / 8;
            g_pVFileSys->Read(entry, entryBytes, vf);
            img->pPalette[i].b = entry[0];
            img->pPalette[i].g = entry[1];
            img->pPalette[i].r = entry[2];
            img->pPalette[i].a = 0xFF;
        }
    }

    // Allocate pixel buffer
    int bytesPerPixel = bitCount / 8;
    int bytesPerRow = bytesPerPixel * width;
    img->pBits = (char*)malloc(bytesPerRow * height);

    // Read pixel data
    if (descriptor & 0x20) {
        // Top-to-bottom: read all at once
        g_pVFileSys->Read(img->pBits, bytesPerRow * height, vf);
    } else {
        // Bottom-to-top: read row by row from last row
        for (int y = height - 1; y >= 0; y--) {
            g_pVFileSys->Read(img->pBits + y * bytesPerRow, bytesPerRow, vf);
        }
    }

    g_pVFileSys->CloseFile(vf);
    return 1;
}

// sub_1001EB80 (460B) - Load BMP file
static int LoadBMP(gbImage2D* img, char* filename) {
    gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vf)
        return 0;

    // Get file size
    g_pVFileSys->Seek(vf, 0, GBVFS_SEEK_END);
    long fileSize = g_pVFileSys->TellPos(vf);
    g_pVFileSys->Seek(vf, 0, GBVFS_SEEK_SET);

    // Read 14-byte file header
    unsigned char* fileHeader = (unsigned char*)malloc(0x0E);
    g_pVFileSys->Read(fileHeader, 0x0E, vf);

    // Get pixel data offset from file header (offset 10)
    unsigned long pixelOffset = *(unsigned long*)&fileHeader[10];

    // Read info header (size = pixelOffset - 14)
    unsigned long infoSize = pixelOffset - 14;
    unsigned char* infoHeader = (unsigned char*)malloc(infoSize);
    g_pVFileSys->Read(infoHeader, infoSize, vf);

    // Read pixel data
    unsigned long dataSize = fileSize - pixelOffset;
    img->pBits = (char*)malloc(dataSize);
    g_pVFileSys->Read(img->pBits, dataSize, vf);

    // Extract dimensions from info header
    img->Width = *(int*)&infoHeader[4];
    img->Height = *(int*)&infoHeader[8];
    img->BitCount = *(short*)&infoHeader[14];

    // If palettized (BitCount <= 8)
    if (img->BitCount <= 8) {
        img->numPalEntry = 1 << img->BitCount;
        img->pPalette = (gbColorQuad*)malloc(img->numPalEntry * 4);
        // Copy palette from info header at offset 0x28
        unsigned char* palSrc = &infoHeader[0x28];
        for (int i = 0; i < img->numPalEntry; i++) {
            img->pPalette[i].b = palSrc[i * 4 + 0];
            img->pPalette[i].g = palSrc[i * 4 + 1];
            img->pPalette[i].r = palSrc[i * 4 + 2];
            img->pPalette[i].a = 0xFF;
        }
    }

    free(fileHeader);
    free(infoHeader);
    g_pVFileSys->CloseFile(vf);
    return 1;
}

// sub_1001F0A0 (867B) - Load PCX file with RLE decoding
static int LoadPCX(gbImage2D* img, char* filename) {
    gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vf)
        return 0;

    // Read and verify magic byte
    unsigned char magic;
    g_pVFileSys->Read(&magic, 1, vf);
    if (magic != 0x0A) {
        g_pVFileSys->CloseFile(vf);
        return 0;
    }

    // Read version byte
    unsigned char version;
    g_pVFileSys->Read(&version, 1, vf);
    if (version != 5) {
        g_pVFileSys->CloseFile(vf);
        return 0;
    }

    // Rewind and skip first 4 bytes, then read 12 bytes of header fields
    g_pVFileSys->Rewind(vf);
    g_pVFileSys->Seek(vf, 4, GBVFS_SEEK_CUR);

    short headerFields[6]; // xmin, ymin, xmax, ymax, hDPI, vDPI
    g_pVFileSys->Read(headerFields, 12, vf);

    int width = headerFields[2] - headerFields[0] + 1;   // xmax - xmin + 1
    int height = headerFields[3] - headerFields[1] + 1;  // ymax - ymin + 1

    img->Width = width;
    img->Height = height;

    // Allocate raw buffer for 8-bit indexed pixels
    unsigned char* rawBuf = (unsigned char*)malloc(width * height);

    // Seek to offset 128 (skip full PCX header)
    g_pVFileSys->Seek(vf, 128, GBVFS_SEEK_SET);

    // RLE decode loop
    int totalPixels = width * height;
    int decoded = 0;
    while (decoded < totalPixels) {
        unsigned char byte;
        g_pVFileSys->Read(&byte, 1, vf);
        if (byte >= 0xC0) {
            int count = byte & 0x3F;
            unsigned char value;
            g_pVFileSys->Read(&value, 1, vf);
            for (int i = 0; i < count && decoded < totalPixels; i++) {
                rawBuf[decoded++] = value;
            }
        } else {
            rawBuf[decoded++] = byte;
        }
    }

    // Read 768-byte palette from end of file
    // Seek to -769 from end
    g_pVFileSys->Seek(vf, -769, GBVFS_SEEK_END);

    unsigned char marker;
    g_pVFileSys->Read(&marker, 1, vf);
    if (marker != 0x0C) {
        free(rawBuf);
        g_pVFileSys->CloseFile(vf);
        return 0;
    }

    unsigned char palette[768];
    g_pVFileSys->Read(palette, 768, vf);

    // Set bit count to 24 (expanding from 8-bit indexed to RGB)
    img->BitCount = 24;

    // Allocate final RGB buffer
    img->pBits = (char*)malloc(width * height * 3);

    // Expand indexed pixels to RGB using palette
    for (int i = 0; i < width * height; i++) {
        unsigned char idx = rawBuf[i];
        img->pBits[i * 3 + 0] = palette[idx * 3 + 0];
        img->pBits[i * 3 + 1] = palette[idx * 3 + 1];
        img->pBits[i * 3 + 2] = palette[idx * 3 + 2];
    }

    free(rawBuf);
    g_pVFileSys->CloseFile(vf);
    return 1;
}

// sub_1001F410 (473B) - Load JPEG file via Intel JPEG Library (IJL15.dll)
static int LoadJPEG(gbImage2D* img, char* filename) {
    // Open file and read entire contents into buffer
    gbVFile* vf = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vf)
        return 0;

    g_pVFileSys->Seek(vf, 0, GBVFS_SEEK_END);
    long fileSize = g_pVFileSys->TellPos(vf);
    g_pVFileSys->Seek(vf, 0, GBVFS_SEEK_SET);

    unsigned char* fileBuf = (unsigned char*)malloc(fileSize);
    g_pVFileSys->Read(fileBuf, fileSize, vf);
    g_pVFileSys->CloseFile(vf);

    // Initialize JPEG properties
    JPEG_CORE_PROPERTIES props;
    memset(&props, 0, sizeof(props));
    ijlInit(&props);

    // Set up for reading from memory
    props.JPGFile = NULL;
    props.JPGBytes = fileBuf;
    props.JPGSizeBytes = fileSize;

    // Read JPEG parameters (IJL_JFILE_READPARAMS = 1)
    ijlRead(&props, 1);

    int jpgWidth = props.JPGWidth;
    int jpgHeight = props.JPGHeight;

    // Allocate output buffer (24-bit RGB)
    unsigned char* outBuf = (unsigned char*)malloc(jpgWidth * jpgHeight * 3);

    // Set up DIB output parameters
    props.DIBBytes = outBuf;
    props.DIBWidth = jpgWidth;
    props.DIBHeight = -jpgHeight;  // Negative = top-down
    props.DIBChannels = 3;
    props.DIBColor = 2;  // RGB
    props.DIBPadBytes = 0;

    // Handle color space / subsampling
    if (props.JPGColor == 1) {
        props.JPGSubsampling = 4;
    } else if (props.JPGColor == 3) {
        props.JPGSubsampling = 3;
    } else {
        props.DIBColor = 0xFF;
        props.JPGSubsampling = 0xFF;
    }

    // Read whole image (IJL_JFILE_READWHOLEIMAGE = 3)
    ijlRead(&props, 3);
    ijlFree(&props);

    // Set image properties
    img->Width = jpgWidth;
    img->Height = jpgHeight;
    img->BitCount = 24;
    img->pBits = (char*)outBuf;

    free(fileBuf);
    return 1;
}

// sub_1001EAC0 (183B) - Expand paletted (8-bit indexed) image to 24-bit RGB
static void gbImage2D_ExpandPalette(gbImage2D* img) {
    if (img->pPalette != NULL) {
        char* newBits = (char*)malloc(img->Width * img->Height * 3);
        int i = 0;
        if (i < img->Width * img->Height) {
            char* dst = newBits + 2;
            do {
                unsigned char* palEntry;
                unsigned char idx = *((unsigned char*)img->pBits + i);
                i = i + 1;
                palEntry = (unsigned char*)img->pPalette + (unsigned int)idx * 4;
                dst[-2] = palEntry[0];
                dst[-1] = palEntry[1];
                dst[0] = palEntry[2];
                dst = dst + 3;
            } while (i < img->Width * img->Height);
        }
        free(img->pBits);
        img->pBits = newBits;
        free(img->pPalette);
        img->pPalette = NULL;
        img->BitCount = 24;
    }
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

    gbImage2D_ExpandPalette(this);

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
