/**
 * gbengine.dll - gbPrintFont
 * Decompiled from Ghidra analysis
 * Functions: 17
 */

#include "gbengine/gbPrintFont.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include <stdlib.h>
#include <string.h>


extern gbGfxManager* g_pGfxManager;


/* ======== gbPrintFont ======== */

// 0x10022a20
gbPrintFont::gbPrintFont(int maxStr, int max3D, int bufSize)
{
    maxStrings = maxStr;
    max3DStrings = max3D;
    maxChars = bufSize;

    stringInfoBuffer = (gbPrintStringInfo*)malloc(maxStr * sizeof(gbPrintStringInfo));
    charInfoBuffer = malloc(maxStr * 8);
    string3DInfoBuffer = (gbPrint3DStringInfo*)malloc(max3D * sizeof(gbPrint3DStringInfo));
    textBuffer = (char*)malloc(bufSize);

    currentStringCount = 0;
    current3DStringCount = 0;
    currentTextOffset = 0;

    colorR = 0xFF;
    colorG = 0xFF;
    colorB = 0xFF;
    colorA = 0xFF;

    scaleX = 1.0f;
    scaleY = 1.0f;
    pitchX = 0.0f;
    pitchY = 0.0f;
    depth = 0.0f;
}

// destructor
gbPrintFont::~gbPrintFont()
{
    free(textBuffer);
    free(string3DInfoBuffer);
    free(charInfoBuffer);
    free(stringInfoBuffer);
}

// 0x10022b00
int gbPrintFont::Init(void)
{
    pFontEffect = g_pGfxManager->pEffectMgr->NewRenderEffect("gfxscript\\font.gbf", 0);
    pFont1Effect = g_pGfxManager->pEffectMgr->NewRenderEffect("gfxscript\\font1.gbf", 0);
    return 1;
}

// 0x10022b40
void gbPrintFont::Release(void)
{
    free(textBuffer);
    free(string3DInfoBuffer);
    free(charInfoBuffer);
    free(stringInfoBuffer);

    stringInfoBuffer = NULL;
    charInfoBuffer = NULL;
    string3DInfoBuffer = NULL;
    textBuffer = NULL;
}

// 0x10022bf0
void gbPrintFont::PrintString(char* text, float x, float y, float w, float h)
{
    if (currentStringCount >= maxStrings) {
        return;
    }

    int len = (int)strlen(text) + 1;

    memcpy(textBuffer + currentTextOffset, text, len);

    gbPrintStringInfo* record = &stringInfoBuffer[currentStringCount];

    record->x = x;
    record->y = y;
    record->depth = depth;
    record->width = w;
    record->height = h;

    record->color = *(unsigned int*)&colorR;

    record->scaleX = scaleX;
    record->scaleY = scaleY;
    record->textBufferOffset = currentTextOffset;

    currentStringCount++;
    currentTextOffset += len;
}

// 0x10022d60
void gbPrintFont::Print3DString(char* text, float x, float y, float z)
{
    if (current3DStringCount >= max3DStrings) {
        return;
    }

    int len = (int)strlen(text) + 1;

    // Copy string text into textBuffer
    memcpy(textBuffer + currentTextOffset, text, len);

    // Store 3D string info record
    gbPrint3DStringInfo* record = &string3DInfoBuffer[current3DStringCount];

    record->x = x;
    record->y = y;
    record->z = z;

    // Pack color
    record->color = (unsigned int)colorR |
                    ((unsigned int)colorG << 8) |
                    ((unsigned int)colorB << 16) |
                    ((unsigned int)colorA << 24);

    record->scaleX = scaleX;
    record->scaleY = scaleY;
    record->pitchX = pitchX;
    record->pitchY = pitchY;
    record->textBufferOffset = currentTextOffset;

    current3DStringCount++;
    currentTextOffset += len;
}

// 0x10022b70
void gbPrintFont::PrintCenterLine(char* text, float left, float top, float right, float bottom)
{
    int len = (int)strlen(text);

    // Calculate centered X position
    // Each char is scaleX * 0.5 wide, with pitchX spacing between chars
    float textWidth = len * scaleX * 0.5f + (len - 1) * pitchX;
    float newX = (right - left - textWidth) * 0.5f + left;

    // Calculate centered Y position
    float newY = (bottom - top - scaleY) * 0.5f + top;

    PrintString(text, newX, newY, 10000.0f, 10000.0f);
}

// 0x10004340
void gbPrintFont::SetFontColor(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned char local[4];
    if (gbColorQuad::ColorQuadFmt == 0) {
        local[2] = r;
        local[1] = g;
        local[0] = b;
        local[3] = 0xFF;
    } else {
        local[2] = b;
        local[1] = g;
        local[0] = r;
        local[3] = 0xFF;
    }
    *(unsigned int*)&colorR = *(unsigned int*)local;
}

// 0x100043a0
void gbPrintFont::SetFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    unsigned char local[4];
    if (gbColorQuad::ColorQuadFmt == 0) {
        local[2] = r;
        local[1] = g;
        local[0] = b;
        local[3] = a;
    } else {
        local[2] = b;
        local[1] = g;
        local[0] = r;
        local[3] = a;
    }
    *(unsigned int*)&colorR = *(unsigned int*)local;
}

// 0x10004400
void gbPrintFont::SetCurFontScale(float sx, float sy)
{
    scaleX = sx;
    scaleY = sy;
}

// 0x10004420
void gbPrintFont::SetCurFontPitch(float px, float py)
{
    pitchX = px;
    pitchY = py;
}

// 0x10004440
void gbPrintFont::SetCurFontDepth(float d)
{
    depth = d;
}


/* ======== gbPrintFontMgr ======== */

// 0x10022f40
gbPrintFontMgr::gbPrintFontMgr(void)
{
    fonts[0] = NULL;
    fonts[1] = NULL;
    fonts[2] = NULL;
    fonts[3] = NULL;
    gfxMgr = NULL;
}

// 0x10022f60
int gbPrintFontMgr::Init(gbGfxManager* mgr)
{
    gfxMgr = mgr;

    // Allocate default font with reasonable defaults
    fonts[GB_FONT_DEFAULT] = new gbPrintFont(256, 64, 8192);
    fonts[GB_FONT_1] = new gbPrintFont(256, 64, 8192);
    fonts[GB_FONT_2] = new gbPrintFont(256, 64, 8192);
    fonts[GB_FONT_3] = new gbPrintFont(256, 64, 8192);

    // Initialize all fonts
    fonts[GB_FONT_DEFAULT]->Init();
    fonts[GB_FONT_1]->Init();
    fonts[GB_FONT_2]->Init();
    fonts[GB_FONT_3]->Init();

    return 1;
}

// 0x10023150
void gbPrintFontMgr::Release(void)
{
    for (int i = 0; i < 5; i++) {
        if (fonts[i]) {
            fonts[i]->Release();
            delete fonts[i];
            fonts[i] = NULL;
        }
    }
}

// 0x100231b0
void gbPrintFontMgr::Flush(void)
{
    for (int i = 0; i < 5; i++) {
        if (fonts[i]) {
            fonts[i]->currentStringCount = 0;
            fonts[i]->currentTextOffset = 0;
        }
    }
}

// 0x100231d0
void gbPrintFontMgr::Flush3D(void)
{
    for (int i = 0; i < 5; i++) {
        if (fonts[i]) {
            fonts[i]->current3DStringCount = 0;
        }
    }
}

// 0x10004450
gbPrintFont* gbPrintFontMgr::GetFont(gbFontType type)
{
    return fonts[type];
}
