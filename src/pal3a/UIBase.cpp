#include "UIBase.h"

UICursor * UICursor::Inst()
{
    /* stub */
    return NULL;
}

void UICursor::Init()
{
    /* stub */
}

void UICursor::Show(uchar bShow)
{
    /* stub */
}

UICursor::~UICursor()
{
    /* stub */
}

void UICursor::SetCursor(CURSOR_TYPE cur)
{
    /* stub */
}

void UICursor::IRender()
{
    /* stub */
}

void UICursor::Destroy()
{
    /* stub */
}

UICursor::UICursor()
{
    /* stub */
}

UIRenderObj::~UIRenderObj()
{
    /* stub */
}

UIRenderObj::UIRenderObj()
{
    /* stub */
}

void UIDrawRichText(char * text, tagRECT * rect, int bcenter)
{
    /* stub */
}

void UIRenderQuadFlip(tagRECT * rect, gbColorQuad * color, gbTextureArray * atex, int flip, _PlugInfo * pTInfo)
{
    /* stub */
}

void UIDestorySystem()
{
    /* stub */
}

void UIRenderQuadList(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex)
{
    /* stub */
}

void UIRenderQuadA(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo)
{
    /* stub */
}

void UIRenderQuad(int left, int top, int right, int bottom, int offsetx, int offsety, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo)
{
    /* stub */
}

void UIRenderQuad(int left, int top, int right, int bottom, float sv, float ev, gbColorQuad * color, gbTextureArray * atex, int mode)
{
    /* stub */
}

void UIRenderQuad(tagRECT * rect, tagRECT * draw, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo)
{
    /* stub */
}

void UIRenderQuad(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex, int mode, _PlugInfo * pTInfo)
{
    /* stub */
}

void UIRenderQuad(tagRECT * rc, gbColorQuad * color, gbTextureArray * atex, int FVF, _PlugInfo * pTInfo, uchar on)
{
    /* stub */
}

void UIRenderQuad(tagRECT * origin, tagRECT * draw, gbTextureArray * atex, gbColorQuad color, int FVF, _PlugInfo * pTInfo)
{
    /* stub */
}

void UIRenderQuad(int left, int top, int right, int bottom, gbColorQuad * color)
{
    /* stub */
}

void UIPrint(int x, int y, char * str, gbColorQuad * color, int fontsize, uchar rightalign)
{
    /* stub */
}

void UIDrawText(char * text, tagRECT * rect, gbPrintFont * font, int fontsize, int align)
{
    /* stub */
}

void UIDrawText(char * text, tagRECT * rect, gbColorQuad * color, gbFontType fonttype, int align)
{
    /* stub */
}

void UIRenderQuadAlpha(int left, int top, int right, int bottom, gbColorQuad * alpha, gbTextureArray * atex, _PlugInfo * pTInfo, uchar on)
{
    /* stub */
}

void UIRenderQuadSmall(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo)
{
    /* stub */
}

void UIInitSystem()
{
    /* stub */
}

void UIRenderQuadEX(tagRECT * rect, gbTextureArray * atex, gbColorQuad color, _PlugInfo * pTInfo)
{
    /* stub */
}

void UIRenderPar(int left, int top, int right, int bottom, gbColorQuad * color, gbTextureArray * atex, _PlugInfo * pTInfo)
{
    /* stub */
}

