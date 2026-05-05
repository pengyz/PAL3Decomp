#include "UIListBox.h"

void UILBColumn::Destroy()
{
    /* stub */
}

UILBColumn::~UILBColumn()
{
    /* stub */
}

UILBColumn::UILBColumn()
{
    /* stub */
}

UILBItem::~UILBItem()
{
    /* stub */
}

UILBItem::UILBItem()
{
    /* stub */
}

void UIListBox::SetItemOffset(int x, int y)
{
    /* stub */
}

void UIListBox::Destroy()
{
    /* stub */
}

void UIListBox::SetMouseMoveSel(int movesel)
{
    /* stub */
}

void UIListBox::SetSelTexture(char * selfile, uchar opt)
{
    /* stub */
}

void UIListBox::CalScrollBarRange()
{
    /* stub */
}

tagPOINT UIListBox::GetItemPos(tagPOINT * __$ReturnUdt)
{
    /* stub */
    tagPOINT _ret = {0}; return _ret;
}

void UIListBox::UpdateKeyCtrl()
{
    /* stub */
}

int UIListBox::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

void UIListBox::SetScroll(char * srcfile, tagRECT * rect, int btnW, int btnH, uchar opt)
{
    /* stub */
}

UIListBox::~UIListBox()
{
    /* stub */
}

void UIListBox::SetFirstShow(int first)
{
    /* stub */
}

int UIListBox::CalHeightCount()
{
    /* stub */
    return 0;
}

void UIListBox::Render()
{
    /* stub */
}

void UIListBox::DeleteAllItems()
{
    /* stub */
}

int UIListBox::GetLockSel()
{
    /* stub */
    return 0;
}

void UIListBox::SetItemHeight(int height)
{
    /* stub */
}

void UIListBox::AddColumn(char * head, int width, uchar rightalign, int rightoffset)
{
    /* stub */
}

UIListBox::UIListBox()
{
    /* stub */
}

int UIListBox::AddRow(char * str, int isicon)
{
    /* stub */
    return 0;
}

void UIListBox::SetSubItem(int col, int item, char * str, int bicon)
{
    /* stub */
}

int UIListBox::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

void UIListBox::EnableRow(int row, int enable)
{
    /* stub */
}

char * UIListBox::GetSubItemInfo(int col, int item)
{
    /* stub */
    return NULL;
}

int UIListBox::GetSel()
{
    /* stub */
    return 0;
}

void UIListBox::SetScrollPos(int pos)
{
    /* stub */
}

void UIListBox::SetDefaultSel(int start)
{
    /* stub */
}

int UIListBox::GetItemCount()
{
    /* stub */
    return 0;
}

void UIListBox::Create(uint id, tagRECT * rect, UIWnd * pfather, char * bkfile, int scroll, uchar opt, uchar bCalFrameRate)
{
    /* stub */
}

void UIListBox::DeleteRow(int row)
{
    /* stub */
}

void UIListBox::SetSel(int sel)
{
    /* stub */
}

