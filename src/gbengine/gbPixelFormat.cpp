#include "gbengine/gbengine_types.h"
#include <d3d9.h>
#include <string.h>
#include <stdlib.h>

// Pixel format conversion and initialization

void gbPixelFormat::Init(gbPixelFmtType type) {
    if (type == GB_PFT_R8G8B8) {
        Init(24, 0x00FF0000, 0x0000FF00, 0x000000FF, 0x00000000);
    } else if (type == GB_PFT_A8R8G8B8) {
        Init(32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    } else if (type == GB_PFT_R5G6B5) {
        Init(16, 0x0000F800, 0x000007E0, 0x0000001F, 0x00000000);
    } else if (type == GB_PFT_A1R5G5B5) {
        Init(16, 0x00007C00, 0x000003E0, 0x0000001F, 0x00008000);
    } else if (type == GB_PFT_A4R4G4B4) {
        Init(16, 0x00000F00, 0x000000F0, 0x0000000F, 0x0000F000);
    } else if (type == GB_PFT_P8) {
        Init(8, 0, 0, 0, 0);
    } else if (type == GB_PFT_A8) {
        Init(8, 0, 0, 0, 0x000000FF);
    } else if (type == GB_PFT_X8R8G8B8) {
        Init(32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0x00000000);
    } else if (type == GB_PFT_X1R5G5B5) {
        Init(16, 0x00007C00, 0x000003E0, 0x0000001F, 0x00000000);
    } else if (type == GB_PFT_X4R4G4B4) {
        Init(16, 0x00000F00, 0x000000F0, 0x0000000F, 0x00000000);
    } else {
        Init(0, 0, 0, 0, 0);
    }
}

void gbPixelFormat::Init(int bpp, unsigned int rMask, unsigned int gMask, unsigned int bMask, unsigned int aMask) {
    Type = GB_PFT_UNKNOWN;
    Bpp = bpp;
    Pal = NULL;
    r_mask = rMask;
    g_mask = gMask;
    b_mask = bMask;
    a_mask = aMask;

    // Calculate shifts from masks
    r_shift = 0;
    if (rMask) {
        while ((rMask & 1) == 0) {
            rMask >>= 1;
            r_shift++;
        }
    }

    g_shift = 0;
    if (gMask) {
        while ((gMask & 1) == 0) {
            gMask >>= 1;
            g_shift++;
        }
    }

    b_shift = 0;
    if (bMask) {
        while ((bMask & 1) == 0) {
            bMask >>= 1;
            b_shift++;
        }
    }

    a_shift = 0;
    if (aMask) {
        while ((aMask & 1) == 0) {
            aMask >>= 1;
            a_shift++;
        }
    }
}

void gbPixelFormat::Init(int bpp, gbColorQuad* palette) {
    unsigned int size = (1 << bpp) << 2;
    Bpp = bpp;
    void* dst = malloc(size);
    Pal = (gbColorQuad*)dst;
    memcpy(dst, palette, size);
    Type = GB_PFT_P8;
}

void gbPixelFormat::Init(gbPixelFormat* other) {
    int bpp = other->Bpp;
    Bpp = bpp;
    if (other->Pal) {
        unsigned int size = (1 << bpp) << 2;
        void* dst = malloc(size);
        Pal = (gbColorQuad*)dst;
        memcpy(dst, other->Pal, size);
    } else {
        other->Pal = NULL;
    }
    Type = other->Type;
    r_mask = other->r_mask;
    g_mask = other->g_mask;
    b_mask = other->b_mask;
    a_mask = other->a_mask;
    r_shift = other->r_shift;
    g_shift = other->g_shift;
    b_shift = other->b_shift;
    a_shift = other->a_shift;
}

void gbPixelFormat::Release() {
    if (Pal)
        free(Pal);
}

gbPixelFormat& gbPixelFormat::operator=(const gbPixelFormat& other) {
    memcpy(this, &other, sizeof(gbPixelFormat));
    return *this;
}

// 0x10012F30 (199B) - ColorQuadToFloat4
// Converts a 4-byte RGBA/BGRA color to float[4] (0.0-1.0)
// Byte order depends on gbColorQuad::ColorQuadFmt
void gbColorQuadToFloat4(float* a1, unsigned char* a2) {
    int v3;
    if (gbColorQuad::ColorQuadFmt) {
        // RGBA order
        a1[0] = (double)a2[0] * 0.0039215689;
        a1[1] = (double)a2[1] * 0.0039215689;
        v3 = a2[2];
    } else {
        // BGRA order
        a1[0] = (double)a2[2] * 0.0039215689;
        a1[1] = (double)a2[1] * 0.0039215689;
        v3 = a2[0];
    }
    a1[2] = (double)v3 * 0.0039215689;
    a1[3] = (double)a2[3] * 0.0039215689;
}
