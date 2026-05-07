#pragma once

#include "gbengine/gbengine_types.h"

// Forward declarations (circular dep / defined in gbengine_internal.h)
class gbGfxManager;
class gbMatrixStack;
class gbRenderEffect;

// sizeof = 0x2C
struct gbPrintStringInfo {
    int _pad00;                 // +0x00
    float x;                    // +0x04
    float y;                    // +0x08
    float depth;                // +0x0C
    float width;                // +0x10
    float height;               // +0x14
    unsigned int color;         // +0x18 (RGBA packed)
    float scaleX;               // +0x1C
    float scaleY;               // +0x20
    float pitchX;               // +0x24
    int textBufferOffset;       // +0x28
};

// sizeof = 0x24
struct gbPrint3DStringInfo {
    float x;                    // +0x00
    float y;                    // +0x04
    float z;                    // +0x08
    unsigned int color;         // +0x0C (RGBA packed)
    float scaleX;               // +0x10
    float scaleY;               // +0x14
    float pitchX;               // +0x18
    float pitchY;               // +0x1C
    int textBufferOffset;       // +0x20
};

class gbPrintFont {
public:
    gbPrintStringInfo* stringInfoBuffer; // +0x04
    void*           charInfoBuffer;     // +0x08
    int             maxStrings;         // +0x0C
    int             currentStringCount; // +0x10
    gbPrint3DStringInfo* string3DInfoBuffer; // +0x14
    int             current3DStringCount; // +0x18
    int             max3DStrings;       // +0x1C
    char*           textBuffer;         // +0x20
    int             maxChars;           // +0x24
    int             currentTextOffset;  // +0x28
    unsigned char   colorR;             // +0x2C
    unsigned char   colorG;             // +0x2D
    unsigned char   colorB;             // +0x2E
    unsigned char   colorA;             // +0x2F
    float           scaleX;             // +0x30
    float           scaleY;             // +0x34
    float           pitchX;             // +0x38
    float           pitchY;             // +0x3C
    float           depth;              // +0x40
    gbRenderEffect* pFontEffect;        // +0x44
    gbRenderEffect* pFont1Effect;       // +0x48

    // 0x10022a20 (147B)
    gbPrintFont(int maxStr, int max3D, int bufSize);
    // destructor
    ~gbPrintFont();
    // 0x10022b00 (63B)
    virtual int Init(void);
    // 0x10022b40 (36B)
    virtual void Release(void);
    // 0x10022bf0 (285B)
    virtual void PrintString(char* text, float x, float y, float w, float h);
    // 0x10022d60 (472B)
    virtual void Print3DString(char* text, float x, float y, float z);

    // 0x10022b70 (123B)
    void PrintCenterLine(char* text, float left, float top, float right, float bottom);
    // 0x10004340 (90B)
    void SetFontColor(unsigned char r, unsigned char g, unsigned char b);
    // 0x100043a0 (96B)
    void SetFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    // 0x10004400 (17B)
    void SetCurFontScale(float sx, float sy);
    // 0x10004420 (17B)
    void SetCurFontPitch(float px, float py);
    // 0x10004440 (10B)
    void SetCurFontDepth(float d);
};


enum gbFontType {
    GB_FONT_DEFAULT = 0,
    GB_FONT_1 = 1,
    GB_FONT_2 = 2,
    GB_FONT_3 = 3
};

class gbPrintFontMgr {
public:
    gbPrintFont*    fonts[5];   // +0x00
    gbGfxManager*   gfxMgr;    // +0x14

    // 0x10022f40 (21B)
    gbPrintFontMgr(void);
    // 0x10022f60 (484B)
    int Init(gbGfxManager* mgr);
    // 0x10023150 (94B)
    void Release(void);
    // 0x100231b0 (26B)
    void Flush(void);
    // 0x100231d0 (25B)
    void Flush3D(void);
    // 0x10004450 (10B)
    gbPrintFont* GetFont(gbFontType type);
};
