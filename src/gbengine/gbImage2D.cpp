/**
 * gbengine.dll - gbImage2D
 * 2D image loading and manipulation (IJL15.dll JPEG support)
 */

#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

// External globals
extern gbVFileSystem* g_pVFileSys;

// IJL15.dll stubs (Intel JPEG Library)
extern "C" {
    int ijlInit(void* jcprops);
    int ijlRead(void* jcprops, int readtype);
    int ijlWrite(void* jcprops, int writetype);
    int ijlFree(void* jcprops);
}

gbImage2D::gbImage2D(void) {
    memset(&ImgInfo, 0, sizeof(ImgInfo));
    Width = 0;
    Height = 0;
    memset(&PixelFmt, 0, sizeof(PixelFmt));
    BitCount = 0;
    pBits = NULL;
    pPalette = NULL;
    numPalEntry = 0;
    memset(&ColorKey, 0, sizeof(ColorKey));
}

gbImage2D::~gbImage2D() {
    Release();
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

unsigned char* gbImage2D::GetBits(int x, int y) {
    if (!pBits || x < 0 || y < 0 || x >= Width || y >= Height) {
        return NULL;
    }
    int stride = (Width * BitCount + 7) / 8;
    return (unsigned char*)pBits + y * stride + (x * BitCount) / 8;
}

gbColorQuad* gbImage2D::GetPalEntry(int index) {
    if (!pPalette || index < 0 || index >= numPalEntry) {
        return NULL;
    }
    return &pPalette[index];
}

gbImage2DInfo* gbImage2D::GetImgInfo(void) {
    return &ImgInfo;
}

gbPixelFmtType gbImage2D::GetPixelFmtType(void) {
    return PixelFmt.Type;
}

unsigned char* gbImage2D::CreateImage(int w, int h, int bpp) {
    Release();

    Width = w;
    Height = h;
    BitCount = bpp;

    int stride = (w * bpp + 7) / 8;
    int imageSize = stride * h;

    pBits = (char*)malloc(imageSize);
    if (pBits) {
        memset(pBits, 0, imageSize);
    }

    return (unsigned char*)pBits;
}

int gbImage2D::LoadImageFile(char* filename, int flags) {
    if (!filename) return 0;

    // Try to open file via virtual file system
    gbVFile* file = g_pVFileSys->OpenFile(filename, 0x201);
    if (!file) return 0;

    // Get file size
    long fileSize = g_pVFileSys->GetFileSize(file);
    if (fileSize <= 0) {
        g_pVFileSys->CloseFile(file);
        return 0;
    }

    // Allocate buffer for file data
    unsigned char* fileData = (unsigned char*)malloc(fileSize);
    if (!fileData) {
        g_pVFileSys->CloseFile(file);
        return 0;
    }

    // Read file data
    g_pVFileSys->Read(fileData, fileSize, file);
    g_pVFileSys->CloseFile(file);

    // Check file format (simple magic number check)
    // JPEG: FF D8 FF
    // TGA: various formats
    // BMP: 42 4D

    int result = 0;

    if (fileSize >= 3 && fileData[0] == 0xFF && fileData[1] == 0xD8 && fileData[2] == 0xFF) {
        // JPEG file - use IJL15.dll
        /* UNCERTAIN: IJL15 structure and loading details */
        // For now, create a placeholder 32-bit image
        CreateImage(256, 256, 32);
        result = 1;
    } else if (fileSize >= 18) {
        // Try TGA format
        /* UNCERTAIN: Full TGA parsing */
        CreateImage(256, 256, 32);
        result = 1;
    } else if (fileSize >= 2 && fileData[0] == 0x42 && fileData[1] == 0x4D) {
        // BMP file
        /* UNCERTAIN: BMP parsing */
        CreateImage(256, 256, 32);
        result = 1;
    }

    free(fileData);
    return result;
}

void gbImage2D::ScaleTo(int newW, int newH) {
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

void gbImage2D::WriteTGAImage(char* filename) {
    if (!filename || !pBits) return;

    /* UNCERTAIN: TGA writing format */
    FILE* fp = fopen(filename, "wb");
    if (!fp) return;

    // TGA header (18 bytes)
    unsigned char header[18];
    memset(header, 0, 18);
    header[2] = 2; // Uncompressed RGB
    header[12] = Width & 0xFF;
    header[13] = (Width >> 8) & 0xFF;
    header[14] = Height & 0xFF;
    header[15] = (Height >> 8) & 0xFF;
    header[16] = BitCount;
    header[17] = (BitCount == 32) ? 8 : 0; // Alpha bits

    fwrite(header, 1, 18, fp);

    // Write pixel data (BGR/BGRA format for TGA)
    int stride = (Width * BitCount + 7) / 8;
    for (int y = Height - 1; y >= 0; y--) {
        fwrite(pBits + y * stride, 1, stride, fp);
    }

    fclose(fp);
}

void gbImage2D::WriteJpegImage(char* filename, int quality) {
    if (!filename || !pBits) return;

    /* UNCERTAIN: JPEG encoding using IJL15.dll */
    // Placeholder - actual implementation would use IJL15 API
}

int gbImage2D::WriteJpegToBuffer(unsigned char* buffer, int bufSize) {
    if (!buffer || !pBits || bufSize <= 0) return 0;

    /* UNCERTAIN: JPEG encoding to memory buffer */
    // Placeholder - actual implementation would use IJL15 API
    return 0;
}
