#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UIBigMap

#include "MUIDialog.h"
#include "UIAnimateCtrl.h"
#include "UIStatic.h"
#include "_BIGMAP_ELEMENT.h"
#include "_MapElement.h"
#include "gbengine/gbengine_internal.h"

class UIBigMap : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT screenrect; // +0x48
    char _gap_04C[12]; // +0x4C
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    UIStatic ms_BigMap; // +0x168
    char _gap_16C[156]; // +0x16C
    _MapElement m_Element[16]; // +0x208
    char _gap_248[6208]; // +0x248
    tagRECT m_spiritRect; // +0x1A88
    char _gap_1A8C[12]; // +0x1A8C
    UIAnimateCtrl m_spirit; // +0x1A98
    char _gap_1A9C[160]; // +0x1A9C
    float m_spiritPosX; // +0x1B3C
    float m_spiritPosY; // +0x1B40
    tagPOINT m_spiritPos; // +0x1B44
    char _gap_1B48[4]; // +0x1B48
    tagPOINT m_movetopos; // +0x1B4C
    char _gap_1B50[4]; // +0x1B50
    float m_movetoX; // +0x1B54
    float m_movetoY; // +0x1B58
    int m_spiritspeed; // +0x1B5C
    float m_speedFX; // +0x1B60
    float m_speedFY; // +0x1B64
    BYTE m_bSpiritCanMove; // +0x1B68
    BYTE m_isSpiritMoveTo; // +0x1B69
    char _gap_1B6A[2]; // +0x1B6A
    float m_timescale; // +0x1B6C
    int m_stopdir; // +0x1B70
    _BIGMAP_ELEMENT m_curElement; // +0x1B74
    MUIDialog m_Answer; // +0x1B78
    char _tail_1B7C[3212]; // +0x1B7C
    // total size: 0x2808 (10248)

    virtual ~UIBigMap() {}

    int Update(int *deltatime, int haveinput); // 0x00414E50
    int Update(int deltatime, float *haveinput); // 0x00418260
    void LoadScene(int element, const char *visible); // 0x00423A70
    void RenderRole(gbMatrixStack *pStack, int visible); // 0x00424570
    int Update(int deltatime, int haveinput); // 0x0043BF90
    int SetScrollRange(int nMin, int nMax); // 0x00441240
    int SetViewParams(int deltatime, int haveinput); // 0x004431E0
    int LayoutBinkVideo(LPCSTR lpString1, int haveinput); // 0x00451360
    int InitUI(int id, int parent); // 0x004528F0
    void UpdateElement(int element, int visible); // 0x00489BA0
    UIBigMap(); // 0x00490E90
    void _UIBigMap(); // 0x004910B0
    int GetChildCount(int nVal, int nVal2); // 0x00491C30
    int ProcessChildItem(int arg0, int *p_DWORD); // 0x004929E0
    int SetEntryVisible(int nIndex, unsigned __int8 bParam); // 0x00492E10
    virtual void Render(); // 0x00496FA0
    virtual BOOL ProcessInput(int nVal, int nVal2); // 0x004971E0
    int UpdateNPCAnimations(int nVal, int nVal2); // 0x00497450
    virtual int OnMessage(int nVal, char *pszBuf, int nItemID); // 0x004974A0
    void DestroyFrames(); // 0x0052C8A0
    int SetBounds(int msg, int wparam, int lparam); // 0x0052E0F0
    void SetElementVisible(FILE *Buffer, FILE *Stream); // 0x00539810
};
