/**
 * PAL3 Decompilation - Game Class Method Implementations
 *
 * Small, high-frequency class methods decompiled from Ghidra output.
 * Named using PAL3patch symbol information.
 */

#include "pal3/pal3_classes.h"
#include "pal3/pal3_game.h"

/* ========================================================================
 * gbBinkVideo methods
 * ======================================================================== */

/* 0x0053c710 (11 bytes)
 * MOV EAX,[ECX+0xC] / TEST EAX,EAX / JNZ +1 / RET / MOV EAX,[EAX] / RET
 */
int gbBinkVideo::GetWidth()
{
    int* bink = (int*)this->hBink;
    if (bink == NULL) {
        return 0;
    }
    return *bink;
}

/* 0x0053c720 (12 bytes)
 * MOV EAX,[ECX+0xC] / TEST EAX,EAX / JNZ +1 / RET / MOV EAX,[EAX+4] / RET
 */
int gbBinkVideo::GetHeight()
{
    int* bink = (int*)this->hBink;
    if (bink == NULL) {
        return 0;
    }
    return *(bink + 1);
}

/* 0x0053c460 (16 bytes)
 * MOV EAX,[ECX+0xC] / TEST EAX,EAX / JNZ +1 / RET / PUSH EAX / CALL [0x0056a1d4] / RET
 */
void gbBinkVideo::BinkWait()
{
    if (this->hBink == NULL) {
        return;
    }
    /* Original calls _BinkWait@4 through IAT */
}

/* ========================================================================
 * CCBRoleState methods
 * ======================================================================== */

/* 0x004ed010 (46 bytes)
 * LEA EDX,[EAX*8] / SUB EDX,EAX / SHL EDX,5 / SUB EDX,EAX / LEA EAX,[ECX+EDX*4]
 * => offset = roleIndex * 0x37C
 * MOV CL,[ECX+EDX*4+0x241] / TEST CL,CL / JNZ +5 / XOR AL,AL / RET 4
 * MOV AL,[EAX+0x242] / RET 4
 */
int CCBRoleState::IsAlive(int roleIndex)
{
    char* base = (char*)this;
    int offset = roleIndex * 0x37C;

    if (*(base + offset + 0x241) == 0) {
        return 0;
    }
    return (unsigned char)*(base + offset + 0x242);
}

/* ========================================================================
 * UIWnd methods
 * ======================================================================== */

/* 0x00445d20 (28 bytes)
 * MOV EAX,[ESP+8] / MOV EDX,[ECX+0x14] / SUB EAX,EDX
 * MOV EDX,[ESP+4] / PUSH EAX / MOV EAX,[ECX+0x10] / SUB EDX,EAX
 * PUSH EDX / CALL 0x00445d40 / RET 8
 */
void UIWnd::MoveWindow(int x, int y)
{
    int dx = x - this->rect.left;
    int dy = y - this->rect.top;
    /* Original calls internal move function at 0x00445d40 */
    this->rect.left += dx;
    this->rect.top += dy;
    this->rect.right += dx;
    this->rect.bottom += dy;
}

/* 0x00445fa0 (52 bytes)
 * Copies RECT, then calls vtable[6](0x3FE, 0, 0)
 */
void UIWnd::SetRect(RECT* pRect)
{
    this->rect = *pRect;

    if (this != NULL) {
        typedef void (__thiscall *VFN)(void*, int, int, int);
        VFN fn = (VFN)this->vtable[6];
        fn(this, 0x3FE, 0, 0);
    }
}

/* ========================================================================
 * UICursor methods
 * ======================================================================== */

/* 0x00541710 (51 bytes)
 * Calls UICursor_Inst(), checks bSoftwareCursor flag.
 * If software cursor: sets bVisible directly.
 * If hardware cursor: calls GB_GfxMgr->vtable[0x68/4](bShow) to show/hide D3D cursor.
 */
void UICursor::Show(int bShow)
{
    UICursor* inst = UICursor_Inst();
    if (inst->bSoftwareCursor != 0) {
        this->bVisible = (char)bShow;
        return;
    }
    /* Call GB_GfxMgr->ShowCursor(bShow) through vtable */
    if (GB_GfxMgr != NULL) {
        typedef void (__thiscall *VFN)(void*, int);
        void** vt = *(void***)GB_GfxMgr;
        VFN fn = (VFN)vt[0x68 / 4];
        fn(GB_GfxMgr, bShow);
    }
}

/* 0x005415F0 - UICursor singleton accessor (stub) */
static UICursor s_cursor;
UICursor* UICursor_Inst(void)
{
    return &s_cursor;
}
