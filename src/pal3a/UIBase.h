#ifndef PAL3A_UIBASE_H
#define PAL3A_UIBASE_H

#include "pal3a_types.h"

class UICursor {
public:
    char _data[32];

    UICursor * Inst();
    void Init();
    void Show(uchar bShow);
    ~UICursor();
    void SetCursor(CURSOR_TYPE cur);
    void IRender();
    void Destroy();
    UICursor();
};

class UIRenderObj {
public:
    char _data[1];

    ~UIRenderObj();
    UIRenderObj();
};

void UIDrawRichText(char * text, tagRECT * rect, int bcenter);
void UIRenderQuadFlip(tagRECT * rect, gbColorQuad * color, gbTextureArray * atex, int flip, _PlugInfo * pTInfo);
void UIDestorySystem();
void UIRenderQuadList(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex);
void UIRenderQuadA(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo);
void UIRenderQuad(int left, int top, int right, int bottom, int offsetx, int offsety, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo);
void UIRenderQuad(int left, int top, int right, int bottom, float sv, float ev, gbColorQuad * color, gbTextureArray * atex, int mode);
void UIRenderQuad(tagRECT * rect, tagRECT * draw, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo);
void UIRenderQuad(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex, int mode, _PlugInfo * pTInfo);
void UIRenderQuad(tagRECT * rc, gbColorQuad * color, gbTextureArray * atex, int FVF, _PlugInfo * pTInfo, uchar on);
void UIRenderQuad(tagRECT * origin, tagRECT * draw, gbTextureArray * atex, gbColorQuad color, int FVF, _PlugInfo * pTInfo);
void UIRenderQuad(int left, int top, int right, int bottom, gbColorQuad * color);
void UIPrint(int x, int y, char * str, gbColorQuad * color, int fontsize, uchar rightalign);
void UIDrawText(char * text, tagRECT * rect, gbPrintFont * font, int fontsize, int align);
void UIDrawText(char * text, tagRECT * rect, gbColorQuad * color, gbFontType fonttype, int align);
void UIRenderQuadAlpha(int left, int top, int right, int bottom, gbColorQuad * alpha, gbTextureArray * atex, _PlugInfo * pTInfo, uchar on);
void UIRenderQuadSmall(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo);
void UIInitSystem();
void UIRenderQuadEX(tagRECT * rect, gbTextureArray * atex, gbColorQuad color, _PlugInfo * pTInfo);
void UIRenderPar(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo);

#endif // PAL3A_UIBASE_H
