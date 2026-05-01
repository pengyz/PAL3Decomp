/**
 * PAL3 Decompilation - Game Class Method Implementations
 *
 * Small, high-frequency class methods decompiled from Ghidra output.
 * Named using PAL3patch symbol information.
 */

#include "pal3/pal3_classes.h"
#include "pal3/pal3_game.h"
#include "pal3/gbengine_dynamic.h"
#include <string.h>

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

/* 0x00445c60 (99 bytes)
 * __thiscall: this in ECX (EBX), 2 stack params (RET 0x8)
 * Iterates children in reverse order, calling child->vtable[2] (Update)
 * Returns true if any child consumed the message
 */
int UIWnd::Update(int msg, int param)
{
    if (this->bVisible == 0) {
        return 0;
    }
    if (this->bEnabled == 0) {
        return 0;
    }

    int i = this->nChildren - 1;
    if (i < 0) {
        return (param == 0) ? 1 : 0;
    }

    int consumed = param;
    do {
        UIWnd* child = (UIWnd*)this->children[i];
        typedef int (__thiscall *VFN_Update)(UIWnd*, int, int);
        VFN_Update fnUpdate = (VFN_Update)(*(void***)child)[2];
        int result = fnUpdate(child, msg, consumed);
        if (result != 0) {
            consumed = 0;
        }
        i--;
    } while (i >= 0);

    return (consumed == 0) ? 1 : 0;
}

/* 0x00445cd0 (49 bytes)
 * __thiscall: this in ECX (EDI)
 * If visible, iterate children: for each visible child, call child->vtable[1] (Render)
 */
void UIWnd::Render()
{
    if (this->bVisible == 0) {
        return;
    }

    for (int i = 0; i < this->nChildren; i++) {
        UIWnd* child = (UIWnd*)this->children[i];
        if (child->bVisible != 0) {
            typedef void (__thiscall *VFN_Render)(UIWnd*);
            VFN_Render fnRender = (VFN_Render)(*(void***)child)[1];
            fnRender(child);
        }
    }
}

/* ========================================================================
 * GRPinput methods - DirectInput device acquisition
 * ======================================================================== */

/* 0x00402310 (65 bytes)
 * __thiscall: this in ECX (ESI)
 * MOV EAX,[ESI+0x8] / TEST EAX,EAX / JZ end
 * MOV [ESI+0x186c],1 / Acquire() / if success return
 * retry loop (50x) / if all fail: MOV [ESI+0x186c],0
 *
 * IDirectInputDevice8::Acquire is vtable[7] (offset 0x1c)
 */
void GRPinput::AcquireMouse()
{
    typedef long (__stdcall *PFNACQUIRE)(void*);

    void* pDev = this->m_lpDIDMouse;
    if (pDev == NULL) {
        return;
    }

    this->m_bMouse = 1;

    void** vtable = *(void***)pDev;
    PFNACQUIRE fnAcquire = (PFNACQUIRE)vtable[0x1c / 4];

    long hr = fnAcquire(pDev);
    if (hr == 0) {
        return;
    }

    int i = 0;
    do {
        pDev = this->m_lpDIDMouse;
        vtable = *(void***)pDev;
        fnAcquire = (PFNACQUIRE)vtable[0x1c / 4];
        hr = fnAcquire(pDev);
        if (hr == 0) {
            return;
        }
        i++;
    } while (i < 0x32);

    this->m_bMouse = 0;
}

/* 0x00402380 (75 bytes)
 * __thiscall: this in ECX (ESI)
 * MOV EAX,[ESI+0x4] / TEST EAX,EAX / JZ end
 * MOV [ESI+0x1870],1 / Acquire() / if success -> ClearKeyStates
 * retry loop (50x) / if all fail: MOV [ESI+0x1870],0
 * On success: calls ClearKeyStates (0x00402220)
 */
void GRPinput::AcquireKeyboard()
{
    typedef long (__stdcall *PFNACQUIRE)(void*);

    void* pDev = this->m_lpDIDKeyboard;
    if (pDev == NULL) {
        return;
    }

    this->m_bKeyboard = 1;

    void** vtable = *(void***)pDev;
    PFNACQUIRE fnAcquire = (PFNACQUIRE)vtable[0x1c / 4];

    long hr = fnAcquire(pDev);
    if (hr == 0) {
        this->ClearKeyStates();
        return;
    }

    int i = 0;
    do {
        pDev = this->m_lpDIDKeyboard;
        vtable = *(void***)pDev;
        fnAcquire = (PFNACQUIRE)vtable[0x1c / 4];
        hr = fnAcquire(pDev);
        if (hr == 0) {
            this->ClearKeyStates();
            return;
        }
        i++;
    } while (i < 0x32);

    this->m_bKeyboard = 0;
}

/* 0x004022e0 (14 bytes)
 * __thiscall: this in ECX (unused), 1 stack param (LPPOINT)
 * RET 0x4: thiscall with 1 stack param
 * Simply calls Win32 GetCursorPos
 */
void GRPinput::GetCursorPos(POINT* pt)
{
    ::GetCursorPos(pt);
}

/* 0x00402290 (19 bytes)
 * __thiscall: this in ECX (unused), 2 stack params (x, y)
 * RET 0x8: thiscall with 2 stack params
 * Simply calls Win32 SetCursorPos
 */
void GRPinput::SetCursorPos(int x, int y)
{
    ::SetCursorPos(x, y);
}

/* 0x00402220 (77 bytes)
 * __thiscall: this in ECX (EDX)
 * Zeros out key state buffers using REP STOSD:
 *   [this+0x68]:  0x43 dwords + 1 word  (m_keyStates[270])
 *   [this+0x176]: 0x43 dwords + 1 word  (m_shiftedKeyStates[270])
 *   [this+0x278]: 0x10E dwords          (m_keyPressTimes[270])
 *   [this+0x6B0]: 0x21C dwords          (m_keyDragStartPositions[270][2])
 *   [this+0x1878]: 0x438 dwords         (KeyInfo[270])
 */
void GRPinput::ClearKeyStates()
{
    char* base = (char*)this;

    memset(base + 0x68, 0, 270);
    memset(base + 0x176, 0, 270);
    memset(base + 0x278, 0, 0x10E * 4);
    memset(base + 0x6B0, 0, 0x21C * 4);
    memset(base + 0x1878, 0, 0x438 * 4);
}

/* ========================================================================
 * UIRenderObj methods - Matrix stack scope guard for UI rendering
 * ======================================================================== */

/* 0x00540f60 (58 bytes)
 * __thiscall: this in ECX (saved to EBX, returned as EAX)
 * Gets projection stack (GfxMgr+0xD8) and view stack (GfxMgr+0xD4)
 * Pushes both, then LoadIdentity on both
 */
UIRenderObj* UIRenderObj::Ctor()
{
    char* gfx = (char*)GB_GfxMgr;
    void* projStack = *(void**)(gfx + 0xD8);
    void* viewStack = *(void**)(gfx + 0xD4);

    if (pfn_gbMatrixStack_Push != NULL) {
        pfn_gbMatrixStack_Push((struct gbMatrixStack*)projStack);
        pfn_gbMatrixStack_Push((struct gbMatrixStack*)viewStack);
    }
    if (pfn_gbMatrixStack_LoadIdentity != NULL) {
        pfn_gbMatrixStack_LoadIdentity((struct gbMatrixStack*)projStack);
        pfn_gbMatrixStack_LoadIdentity((struct gbMatrixStack*)viewStack);
    }
    return this;
}

/* 0x00540fa0 (34 bytes)
 * __thiscall: this in ECX (unused)
 * Pops view stack (GfxMgr+0xD4) then projection stack (GfxMgr+0xD8)
 */
void UIRenderObj::Dtor()
{
    char* gfx = (char*)GB_GfxMgr;
    void* viewStack = *(void**)(gfx + 0xD4);
    void* projStack = *(void**)(gfx + 0xD8);

    if (pfn_gbMatrixStack_Pop != NULL) {
        pfn_gbMatrixStack_Pop((struct gbMatrixStack*)viewStack);
        pfn_gbMatrixStack_Pop((struct gbMatrixStack*)projStack);
    }
}

/* ========================================================================
 * gbBinkVideo::DrawFrameEx - Render one Bink video frame
 * ======================================================================== */

/* 0x0053c530 (106 bytes)
 * __thiscall, 6 params on stack (RET 0x18)
 * Calls BinkDoFrame, BinkCopyToBuffer (with flag |= 0x80000000), BinkNextFrame
 * Returns 1 if at last frame, 0 if more frames
 */
int gbBinkVideo::DrawFrameEx(void* buf, int pitch, int height, int x, int y, unsigned int flags)
{
    void* bink = this->hBink;
    if (bink == NULL) {
        return 1;
    }

    if (pfn_BinkDoFrame != NULL) {
        pfn_BinkDoFrame(bink);
    }

    if (pfn_BinkCopyToBuffer != NULL) {
        pfn_BinkCopyToBuffer(bink, buf, pitch, height, x, y, flags | 0x80000000);
    }

    int* binkData = (int*)this->hBink;
    int currentFrame = *(binkData + 3);   /* bink+0x0C */
    int totalFrames = *(binkData + 2);    /* bink+0x08 */
    if (currentFrame == totalFrames) {
        return 1;
    }

    if (pfn_BinkNextFrame != NULL) {
        pfn_BinkNextFrame(this->hBink);
    }
    return 0;
}
