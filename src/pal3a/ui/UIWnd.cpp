#include "UIWnd.h"

int UITextureArray::Add(char * filepath, int mode)
{
    /* stub */
    return 0;
}

void UITextureArray::FreeAll()
{
    /* stub */
}

UITextureArray::~UITextureArray()
{
    /* stub */
}

int UITextureArray::SetTexAt(int index, char * filepath, int mode)
{
    /* stub */
    return 0;
}

gbTexture * UITextureArray::GetAt(int index)
{
    /* stub */
    return NULL;
}

UITextureArray::UITextureArray()
{
    /* stub */
}

unsigned char UITextureArray::GetPixelChannel(int index, int x, int y, int channel)
{
    /* stub */
    return 0;
}

void UIWnd::Render()
{
    /* stub */
}

UIWnd::~UIWnd()
{
    /* stub */
}

tagRECT UIWnd::GetWindowRect()
{
    /* stub */
    tagRECT _ret = {0}; return _ret;
}

int UIWnd::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

void UIWnd::Destroy()
{
    /* stub */
}

void UIWnd::SetWndColor(ulong dwColor)
{
    /* stub */
}

void UIWnd::SetWndColor(gbColorQuad color)
{
    /* stub */
}

void UIWnd::ShowWindow(int show)
{
    /* stub */
}

void UIWnd::MoveWindowOffset(int offsetx, int offsety)
{
    /* stub */
}

void UIWnd::AddChild(UIWnd * pchild)
{
    /* stub */
}

void UIWnd::Create(uint id, tagRECT * rect, UIWnd * pfather, uchar bCalFrameRate)
{
    /* stub */
}

void UIWnd::SetFontColor(gbColorQuad * color)
{
    /* stub */
}

void UIWnd::BringWindowToTop()
{
    /* stub */
}

void UIWnd::SetRect(tagRECT * rc)
{
    /* stub */
}

void UIWnd::CenterWindow(UIWnd * pwnd)
{
    /* stub */
}

void UIWnd::ClientToScreen(tagPOINT * pt)
{
    /* stub */
}

void UIWnd::ClientToScreen(tagRECT * rect)
{
    /* stub */
}

void UIWnd::ScreenToClient(tagPOINT * pt)
{
    /* stub */
}

void UIWnd::ScreenToClient(tagRECT * rect)
{
    /* stub */
}

int UIWnd::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

void UIWnd::MoveWindow(int x, int y)
{
    /* stub */
}

void UIWnd::SetFrameRate()
{
    /* stub */
}

UIWnd::UIWnd()
{
    /* stub */
}

void UIWnd::EnableWindow(int enable)
{
    /* stub */
}

