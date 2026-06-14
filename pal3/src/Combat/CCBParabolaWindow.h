#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBParabolaWindow

#include "gbengine/gbVFileSystem.h"

class UIListBox;
class UIStatic;

class CCBParabolaWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pDescription; // +0x4C
    UIListBox * m_pItemList; // +0x50
    // total size: 0x54 (84)

    virtual ~CCBParabolaWindow() {}

    gbVFileSystem * LoadResourceEx(const char *pszName, char pData); // 0x00440BE0
    CCBParabolaWindow(CCBParabolaWindow **thisa, int *pnVal, int nVal); // 0x0051B710
    void _CCBParabolaWindow(); // 0x0051B810
    void Destroy(); // 0x0051B920
    bool OnMessage(int msg, int wparam, int lparam); // 0x0051B950
    int Update(int deltatime, int haveinput); // 0x0051B9A0
};
