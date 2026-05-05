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
    if (!other) {
        return;
    }

    Type = other->Type;
    Bpp = other->Bpp;
    r_mask = other->r_mask;
    g_mask = other->g_mask;
    b_mask = other->b_mask;
    a_mask = other->a_mask;
    r_shift = other->r_shift;
    g_shift = other->g_shift;
    b_shift = other->b_shift;
    a_shift = other->a_shift;

    if (other->Pal) {
        Pal = (gbColorQuad*)malloc(256 * sizeof(gbColorQuad));
        if (Pal) {
            memcpy(Pal, other->Pal, 256 * sizeof(gbColorQuad));
        }
    } else {
        Pal = NULL;
    }
}

void gbPixelFormat::Release() {
    if (Pal) {
        free(Pal);
        Pal = NULL;
    }
}

void gbPixelFormat::Convert(unsigned char* src, gbPixelFormat* dstFmt, unsigned char* dst, int numPixels) {
    if (!src || !dst || !dstFmt || numPixels <= 0) {
        return;
    }

    int srcBytesPerPixel = Bpp / 8;
    int dstBytesPerPixel = dstFmt->Bpp / 8;

    for (int i = 0; i < numPixels; i++) {
        unsigned int r, g, b, a;

        // Extract from source format
        if (Type == GB_PFT_P8 && Pal) {
            unsigned char index = src[i];
            r = Pal[index].r;
            g = Pal[index].g;
            b = Pal[index].b;
            a = Pal[index].a;
        } else {
            unsigned int pixel = 0;
            memcpy(&pixel, src + i * srcBytesPerPixel, srcBytesPerPixel);

            r = (pixel & r_mask) >> r_shift;
            g = (pixel & g_mask) >> g_shift;
            b = (pixel & b_mask) >> b_shift;
            a = a_mask ? ((pixel & a_mask) >> a_shift) : 0xFF;

            // Scale to 8-bit
            if (r_mask) {
                unsigned int rBits = 0;
                unsigned int temp = r_mask;
                while (temp) { rBits++; temp >>= 1; }
                r = (r * 255) / ((1 << rBits) - 1);
            }
            if (g_mask) {
                unsigned int gBits = 0;
                unsigned int temp = g_mask;
                while (temp) { gBits++; temp >>= 1; }
                g = (g * 255) / ((1 << gBits) - 1);
            }
            if (b_mask) {
                unsigned int bBits = 0;
                unsigned int temp = b_mask;
                while (temp) { bBits++; temp >>= 1; }
                b = (b * 255) / ((1 << bBits) - 1);
            }
            if (a_mask) {
                unsigned int aBits = 0;
                unsigned int temp = a_mask;
                while (temp) { aBits++; temp >>= 1; }
                a = (a * 255) / ((1 << aBits) - 1);
            }
        }

        // Pack into destination format
        unsigned int dstPixel = 0;
        if (dstFmt->r_mask) {
            unsigned int rBits = 0;
            unsigned int temp = dstFmt->r_mask >> dstFmt->r_shift;
            while (temp) { rBits++; temp >>= 1; }
            r = (r * ((1 << rBits) - 1)) / 255;
            dstPixel |= (r << dstFmt->r_shift) & dstFmt->r_mask;
        }
        if (dstFmt->g_mask) {
            unsigned int gBits = 0;
            unsigned int temp = dstFmt->g_mask >> dstFmt->g_shift;
            while (temp) { gBits++; temp >>= 1; }
            g = (g * ((1 << gBits) - 1)) / 255;
            dstPixel |= (g << dstFmt->g_shift) & dstFmt->g_mask;
        }
        if (dstFmt->b_mask) {
            unsigned int bBits = 0;
            unsigned int temp = dstFmt->b_mask >> dstFmt->b_shift;
            while (temp) { bBits++; temp >>= 1; }
            b = (b * ((1 << bBits) - 1)) / 255;
            dstPixel |= (b << dstFmt->b_shift) & dstFmt->b_mask;
        }
        if (dstFmt->a_mask) {
            unsigned int aBits = 0;
            unsigned int temp = dstFmt->a_mask >> dstFmt->a_shift;
            while (temp) { aBits++; temp >>= 1; }
            a = (a * ((1 << aBits) - 1)) / 255;
            dstPixel |= (a << dstFmt->a_shift) & dstFmt->a_mask;
        }

        memcpy(dst + i * dstBytesPerPixel, &dstPixel, dstBytesPerPixel);
    }
}

gbPixelFormat& gbPixelFormat::operator=(const gbPixelFormat& other) {
    if (this != &other) {
        Release();
        Init((gbPixelFormat*)&other);
    }
    return *this;
}
