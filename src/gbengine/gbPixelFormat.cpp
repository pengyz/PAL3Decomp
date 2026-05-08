#include "gbengine/gbengine_types.h"
#include <d3d9.h>
#include <string.h>
#include <stdlib.h>

// Pixel format conversion and initialization

void gbPixelFormat::Init(gbPixelFmtType type) {
    Type = type;
    Pal = NULL;

    switch (type) {
        case GB_PFT_R8G8B8:
            Bpp = 24;
            r_mask = 0x00FF0000;
            g_mask = 0x0000FF00;
            b_mask = 0x000000FF;
            a_mask = 0x00000000;
            r_shift = 16;
            g_shift = 8;
            b_shift = 0;
            a_shift = 0;
            break;

        case GB_PFT_A8R8G8B8:
            Bpp = 32;
            r_mask = 0x00FF0000;
            g_mask = 0x0000FF00;
            b_mask = 0x000000FF;
            a_mask = 0xFF000000;
            r_shift = 16;
            g_shift = 8;
            b_shift = 0;
            a_shift = 24;
            break;

        case GB_PFT_X8R8G8B8:
            Bpp = 32;
            r_mask = 0x00FF0000;
            g_mask = 0x0000FF00;
            b_mask = 0x000000FF;
            a_mask = 0x00000000;
            r_shift = 16;
            g_shift = 8;
            b_shift = 0;
            a_shift = 0;
            break;

        case GB_PFT_R5G6B5:
            Bpp = 16;
            r_mask = 0x0000F800;
            g_mask = 0x000007E0;
            b_mask = 0x0000001F;
            a_mask = 0x00000000;
            r_shift = 11;
            g_shift = 5;
            b_shift = 0;
            a_shift = 0;
            break;

        case GB_PFT_A1R5G5B5:
            Bpp = 16;
            r_mask = 0x00007C00;
            g_mask = 0x000003E0;
            b_mask = 0x0000001F;
            a_mask = 0x00008000;
            r_shift = 10;
            g_shift = 5;
            b_shift = 0;
            a_shift = 15;
            break;

        case GB_PFT_X1R5G5B5:
            Bpp = 16;
            r_mask = 0x00007C00;
            g_mask = 0x000003E0;
            b_mask = 0x0000001F;
            a_mask = 0x00000000;
            r_shift = 10;
            g_shift = 5;
            b_shift = 0;
            a_shift = 0;
            break;

        case GB_PFT_A4R4G4B4:
            Bpp = 16;
            r_mask = 0x00000F00;
            g_mask = 0x000000F0;
            b_mask = 0x0000000F;
            a_mask = 0x0000F000;
            r_shift = 8;
            g_shift = 4;
            b_shift = 0;
            a_shift = 12;
            break;

        case GB_PFT_X4R4G4B4:
            Bpp = 16;
            r_mask = 0x00000F00;
            g_mask = 0x000000F0;
            b_mask = 0x0000000F;
            a_mask = 0x00000000;
            r_shift = 8;
            g_shift = 4;
            b_shift = 0;
            a_shift = 0;
            break;

        case GB_PFT_P8:
            Bpp = 8;
            r_mask = 0;
            g_mask = 0;
            b_mask = 0;
            a_mask = 0;
            r_shift = 0;
            g_shift = 0;
            b_shift = 0;
            a_shift = 0;
            break;

        case GB_PFT_A8:
            Bpp = 8;
            r_mask = 0;
            g_mask = 0;
            b_mask = 0;
            a_mask = 0xFF;
            r_shift = 0;
            g_shift = 0;
            b_shift = 0;
            a_shift = 0;
            break;

        default:
            Bpp = 0;
            r_mask = 0;
            g_mask = 0;
            b_mask = 0;
            a_mask = 0;
            r_shift = 0;
            g_shift = 0;
            b_shift = 0;
            a_shift = 0;
            break;
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
    Type = GB_PFT_P8;
    Bpp = bpp;
    r_mask = 0;
    g_mask = 0;
    b_mask = 0;
    a_mask = 0;
    r_shift = 0;
    g_shift = 0;
    b_shift = 0;
    a_shift = 0;

    if (palette) {
        Pal = (gbColorQuad*)malloc(256 * sizeof(gbColorQuad));
        if (Pal) {
            memcpy(Pal, palette, 256 * sizeof(gbColorQuad));
        }
    } else {
        Pal = NULL;
    }
}

void gbPixelFormat::Init(gbPixelFormat* other) {
    Bpp = other->Bpp;
    if (other->Pal) {
        size_t palSize = 4 * (1 << other->Bpp);
        Pal = (gbColorQuad*)malloc(palSize);
        memcpy(Pal, other->Pal, palSize);
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
