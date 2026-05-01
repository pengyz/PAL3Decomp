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
#include <stdlib.h>
#include <stdio.h>

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

/* 0x0053c6f0 (17 bytes)
 * __thiscall: this in ECX, 2 stack params (RET 8)
 * MOV EAX,[ESP+4] / MOV EDX,[ESP+8] / MOV [ECX+4],EAX / MOV [ECX+8],EDX / RET 8
 * Sets display position (m_pos.x, m_pos.y)
 */
void gbBinkVideo::SetPos(int x, int y)
{
    this->m_pos.x = x;
    this->m_pos.y = y;
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

/* 0x00445bf0 (24 bytes) - Add child to parent's child array */
static void __fastcall UIWnd_AddChild(UIWnd* parent, int /*edx*/, UIWnd* child)
{
    if (child == NULL) {
        return;
    }
    /* Inserts child at index nChildren (append) via array insert helper.
     * Original calls FUN_00432770 on the children array at parent+0x24. */
    /* TODO: implement array insert (FUN_00432770) */
}

/* 0x00445e10 (51 bytes) - Offset child rect by parent's position */
static void __fastcall UIWnd_AdjustRect(UIWnd* parent, int /*edx*/, RECT* childRect)
{
    childRect->left += parent->rect.left;
    childRect->right += parent->rect.left;
    childRect->top += parent->rect.top;
    childRect->bottom += parent->rect.top;
}

/* 0x00445b90 (87 bytes)
 * __thiscall: this in ECX (ESI), 3 stack params (RET 0xC)
 * Sets ID, copies rect, sets parent. If parent != NULL: adds self as child
 * and adjusts rect to parent coordinates. Then sets 3 flags to 1.
 */
void UIWnd::Create(int id, RECT* pRect, void* parent)
{
    this->m_id = id;
    this->rect = *pRect;
    this->m_pParent = parent;

    if (parent != NULL) {
        UIWnd_AddChild((UIWnd*)parent, 0, this);
        UIWnd_AdjustRect((UIWnd*)parent, 0, &this->rect);
    }

    this->m_bFocusable = 1;
    this->bVisible = 1;
    this->bEnabled = 1;
}

/* 0x00445e50 (17 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 0x4... actually no RET 0 in asm)
 * If focusable, sets bEnabled.
 */
void UIWnd::SetEnabled(int bEnable)
{
    if (this->m_bFocusable) {
        this->bEnabled = bEnable;
    }
}

/* 0x00445fe0 (36 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 0x4)
 * Copies this->rect to output RECT pointer. Returns output pointer (in EAX).
 */
void UIWnd::GetRect(RECT* pOut)
{
    *pOut = this->rect;
}

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
 * C2DSpark methods - 2D particle effects
 * ======================================================================== */

/* 0x004d5ec0 (83 bytes)
 * __thiscall: this in ECX (EBX), 1 stack param (sparkData ptr, RET 0x4)
 * Finds first free particle slot (bActive==0), copies 0x2C bytes, marks active.
 * Returns 1 if slot found, 0 if full.
 */
int C2DSpark::CreateSingle(C2DSpark_tagSpark* pSpark)
{
    for (unsigned int i = 0; i < 0x200; i++) {
        if (this->m_Spark[i].bValid == 0) {
            memcpy(&this->m_Spark[i], pSpark, sizeof(C2DSpark_tagSpark));
            this->m_Spark[i].bValid = 1;
            if ((int)i >= this->m_nCurrentSpark) {
                this->m_nCurrentSpark = i + 1;
            }
            return 1;
        }
    }
    return 0;
}

/* ========================================================================
 * GRPinput methods - DirectInput device acquisition
 * ======================================================================== */

/* 0x004022B0 (10 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 4)
 * MOV EAX,[ESP+4] / MOV [ECX+0xC],EAX / RET 4
 * Sets the key repeat delay value.
 */
void GRPinput::SetRepeatDelay(int delay)
{
    this->m_nRepeatDelay = delay;
}

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

/* ========================================================================
 * gbBinkVideo::DrawFrame - Lock backbuffer and render Bink frame
 * ======================================================================== */

/* 0x0053c470 (190 bytes)
 * __thiscall: this in ECX (ESI)
 * Locks backbuffer, maps D3D surface format to Bink copy flags,
 * calls DrawFrameEx, unlocks, then presents via renderer.
 * Returns 1 if done/error, 0 if more frames.
 */
int gbBinkVideo::DrawFrame()
{
    if (this->hBink == NULL) {
        return 1;
    }

    struct {
        int format;
        int height;
        int width;
        int pitch;
        void* pBits;
    } surfInfo;

    typedef int (__thiscall *PFN_LockBackBuffer)(void*, void*, int);
    typedef void (__thiscall *PFN_UnlockBackBuffer)(void*);

    void** gfxVt = *(void***)GB_GfxMgr;
    PFN_LockBackBuffer fnLock = (PFN_LockBackBuffer)gfxVt[0x54 / 4];
    int result = fnLock(GB_GfxMgr, &surfInfo, 0);
    if (result == 0) {
        return 1;
    }

    unsigned int binkFlags;
    if (surfInfo.format == 3) {
        binkFlags = 10;
    } else if (surfInfo.format == 8) {
        binkFlags = 3;
    } else if (surfInfo.format == 9) {
        binkFlags = 9;
    } else {
        PFN_UnlockBackBuffer fnUnlock = (PFN_UnlockBackBuffer)gfxVt[0x58 / 4];
        fnUnlock(GB_GfxMgr);
        return 1;
    }

    int ret = this->DrawFrameEx(surfInfo.pBits, surfInfo.pitch, surfInfo.height,
                                this->m_pos.x, this->m_pos.y, binkFlags);

    PFN_UnlockBackBuffer fnUnlock = (PFN_UnlockBackBuffer)gfxVt[0x58 / 4];
    fnUnlock(GB_GfxMgr);

    /* Present: GfxMgr->m_pRenderer (offset 0x718) -> vtable[0x44/4](0,0,0,0) */
    char* gfxBytes = (char*)GB_GfxMgr;
    void* renderer = *(void**)(gfxBytes + 0x718);
    typedef void (__thiscall *PFN_Present)(void*, int, int, int, int);
    void** rendVt = *(void***)renderer;
    PFN_Present fnPresent = (PFN_Present)rendVt[0x44 / 4];
    fnPresent(renderer, 0, 0, 0, 0);

    return ret;
}

/* ========================================================================
 * CTrail methods - Trail/ribbon effect rendering
 * ======================================================================== */

/* 0x004c65f0 (124 bytes)
 * __thiscall: this in ECX (ESI), 1 stack param (RET 0x4)
 * Sets up rendering state for trail effect:
 * - Selects buffer based on frame counter
 * - Sets world transform from buffer
 * - Configures renderer state (clear/depth/stencil)
 * - Sets camera dimension to 256x192
 */
void CTrail::Begin(void* camera)
{
    if (this->bEnabled == 0) {
        return;
    }
    if (this->bReady == 0) {
        return;
    }

    if (camera != NULL) {
        this->pCamera = camera;
    }

    unsigned int bufIdx = (unsigned int)this->nFrameCount & 7;
    this->nCurrentBuffer = bufIdx;

    /* Set world transform from selected buffer: GfxMgr->vtable[0x5c/4](bufferPtr) */
    typedef void (__thiscall *PFN_SetTransform)(void*, void*);
    void** gfxVt = *(void***)GB_GfxMgr;
    PFN_SetTransform fnSetTransform = (PFN_SetTransform)gfxVt[0x5c / 4];
    char* bufferPtr = this->buffers + bufIdx * 0x60;
    fnSetTransform(GB_GfxMgr, bufferPtr);

    /* Renderer setup: GfxMgr->m_pRenderer->vtable[0xAC/4](renderer, 0, 0, 3, 0xFF000000, 1.0f, 0) */
    char* gfxBytes = (char*)GB_GfxMgr;
    void* renderer = *(void**)(gfxBytes + 0x718);
    typedef void (__thiscall *PFN_RenderSetup)(void*, int, int, int, unsigned int, float, int);
    void** rendVt = *(void***)renderer;
    PFN_RenderSetup fnSetup = (PFN_RenderSetup)rendVt[0xAC / 4];
    fnSetup(renderer, 0, 0, 3, 0xFF000000, 1.0f, 0);

    /* Set camera dimension to 256x192 */
    if (this->pCamera != NULL) {
        if (pfn_gbCamera_SetDimention != NULL) {
            pfn_gbCamera_SetDimention(this->pCamera, 0x100, 0xC0);
        }
    }
}

/* ========================================================================
 * UIFrameWnd methods - Framed window rendering
 * ======================================================================== */

/* FUN_00540440 - Draw frame/border texture (__cdecl, 6 params) */
extern "C" void FUN_00540440(void* pRect, void* pSize, void* pStruct, int flags, int param5, int param6);

/* 0x0043ddf0 (74 bytes)
 * __thiscall: this in ECX (ESI)
 * If visible: draw frame border (if texture exists), then render children.
 */
void UIFrameWnd::Render()
{
    if (this->bVisible == 0) {
        return;
    }

    if (this->m_pFrameTex != 0) {
        char localStruct[0x44];
        memset(localStruct, 0, sizeof(localStruct));
        *(int*)(localStruct + 0x00) = this->m_pFrameTex;
        *(int*)(localStruct + 0x40) = 1;
        FUN_00540440(&this->rect, (char*)this + 0x08, localStruct, 0x114, 0, 1);
    }

    /* Call base UIWnd::Render to render children */
    typedef void (__thiscall *PFN_UIWndRender)(void*);
    PFN_UIWndRender fnRender = (PFN_UIWndRender)0x00445cd0;
    fnRender(this);
}

/* ========================================================================
 * CCBLineupWindow methods - Combat lineup window
 * ======================================================================== */

/* 0x0051b920 (22 bytes)
 * __thiscall: this in ECX (ESI)
 * Renders frame, then renders the current page's sub-control.
 */
void CCBLineupWindow::Render()
{
    /* Call UIFrameWnd::Render (base class) */
    typedef void (__thiscall *PFN_FrameRender)(void*);
    PFN_FrameRender fnFrameRender = (PFN_FrameRender)0x0043ddf0;
    fnFrameRender(this);

    /* Render current page: pages[currentPage]->vtable[1]() */
    char* base = (char*)this;
    int pageIdx = *(int*)(base + 0x74);
    void* page = *(void**)(base + 0x60 + pageIdx * 4);
    typedef void (__thiscall *VFN_Render)(void*);
    void** pageVt = *(void***)page;
    VFN_Render fnPageRender = (VFN_Render)pageVt[1];
    fnPageRender(page);
}

/* 0x0051b950 (80 bytes)
 * __thiscall: this in ECX, 3 stack params (RET 0xC)
 * Tests if point (x, y) is within the specified page's rect.
 * Calls UIWnd::GetAbsRect (0x00445fe0) on pages[pageIdx], checks containment.
 */
int CCBLineupWindow::IsPtOnFace(int pageIdx, int x, int y)
{
    char* base = (char*)this;
    void* page = *(void**)(base + 0x60 + pageIdx * 4);

    /* Call UIWnd::GetAbsRect to get page's absolute rect */
    typedef RECT* (__thiscall *PFN_GetAbsRect)(void*, RECT*);
    PFN_GetAbsRect fnGetAbsRect = (PFN_GetAbsRect)0x00445fe0;
    RECT absRect;
    fnGetAbsRect(page, &absRect);

    if (x >= absRect.left && x < absRect.right &&
        y >= absRect.top && y < absRect.bottom) {
        return 1;
    }
    return 0;
}

/* ========================================================================
 * SoundMgr methods - Audio management
 * ======================================================================== */

/* FUN_0053e890 - Stop all sounds (__thiscall on SoundMgr) */
static void __fastcall SoundMgr_StopAll(SoundMgr* self, int /*edx*/) {}

/* FUN_00541d10 - pal3free wrapper (__cdecl) */
extern "C" void pal3free(void* ptr);

/* 0x0053def0 (49 bytes)
 * __thiscall: this in ECX (EDI)
 * Stops all sounds, destroys audio manager, frees memory.
 */
void SoundMgr::Destroy()
{
    /* Call internal stop-all function (0x0053e890) */
    typedef void (__thiscall *PFN_StopAll)(void*);
    PFN_StopAll fnStopAll = (PFN_StopAll)0x0053e890;
    fnStopAll(this);

    void* pAudio = this->m_pAudioMgr;
    if (pAudio != NULL) {
        /* Call gbAudioManager destructor through IAT at 0x0056a4c8 */
        typedef void (__thiscall *PFN_Dtor)(void*);
        PFN_Dtor fnDtor = *(PFN_Dtor*)0x0056a4c8;
        if (fnDtor != NULL) {
            fnDtor(pAudio);
        }
        pal3free(pAudio);
        this->m_pAudioMgr = NULL;
    }
}

/* ========================================================================
 * Role methods - Character behavior
 * ======================================================================== */

/* 0x004142e0 (98 bytes)
 * __thiscall: this in ECX (ESI)
 * Resets movement/animation state when a behaviour (walk, run, etc.) completes.
 */
void Role::OnBehaviourFinish()
{
    this->m_nMoveState = 0;
    this->m_nAnimState = 0;

    /* Call internal reset function (0x00412710) - thiscall on this */
    typedef void (__thiscall *PFN_Reset)(void*);
    PFN_Reset fnReset = (PFN_Reset)0x00412710;
    fnReset(this);

    this->m_nTargetX = 0;
    this->m_nTargetY = 0;
    this->m_nTargetZ = 0;
    this->m_nCurrentX = 0;
    this->m_nCurrentY = this->m_nTargetY;
    this->m_nCurrentZ = this->m_nTargetZ;

    if (this->m_nBehaviourType != 0) {
        this->m_nBehaviourType = 0;
        this->m_nBehaviourFlags = 0;
    }
}

/* ========================================================================
 * CCBAttackSequen methods - ATB gauge update
 * ======================================================================== */

/* Global ATB speed scale factor (float constant at 0x0056AB58) */
static float g_fATBScale = 1000.0f;

/* 0x004dba60 (185 bytes)
 * __thiscall: this in ECX (EBP)
 * Updates ATB gauges for all 11 combat roles each frame.
 * For each active & alive role: accumulates speed * deltaTime * scale.
 * Clamps to max value 0x2CEC (11500). Tracks overflow transitions.
 */
void CCBAttackSequen::RunOneStep()
{
    for (int i = 0; i < 11; i++) {
        CCBAttackEntry* entry = &this->entries[i];

        if (entry->bExists == 0) {
            continue;
        }

        /* Check if role is alive: this->m_pBattleState[0x10] = CCBRoleState* */
        char* pState = (char*)this->m_pBattleState;
        CCBRoleState* roleState = *(CCBRoleState**)(pState + 0x10);
        if (roleState->IsAlive(i) == 0) {
            continue;
        }

        if (entry->bIsBuffing != 0) {
            /* Buff path: accumulate into atbBuff */
            float increment = (float)entry->buffSpeed * entry->deltaTime * g_fATBScale;
            int newVal = (int)(increment + (float)entry->atbBuff);
            entry->atbBuff = newVal;
            if (newVal > 0x2CEC) {
                entry->atbBuff = 0x2CEC;
            }
        } else {
            /* Normal path: accumulate into atbNormal */
            int oldVal = entry->atbNormal;
            float increment = (float)entry->speed * entry->deltaTime * g_fATBScale;
            int newVal = (int)(increment + (float)oldVal);
            entry->atbNormal = newVal;
            if (newVal >= 0x2CEC) {
                if (oldVal < 0x2CEC) {
                    entry->overflowCount++;
                }
                entry->atbNormal = 0x2CEC;
            }
        }
    }
}

/* ========================================================================
 * Sound System - Audio playback helpers
 * ======================================================================== */

/* 0x0053dfb0 - Look up sound node by ID */
extern "C" void* SoundMgr_FindNode(int soundId);

/* 0x0053e2e0 (45 bytes, 67 callers)
 * __stdcall: 2 stack params (RET 0x8)
 * If sound enabled: find sound by ID, set param, play.
 */
void __stdcall SoundMgr_PlaySound(int soundId, int param)
{
    extern unsigned int PAL3_s_flag;

    if ((PAL3_s_flag & 1) == 0) {
        return;
    }

    void* node = SoundMgr_FindNode(soundId);
    if (node == NULL) {
        return;
    }

    /* node+0x10 = gbSound2DNode*, set [+0x08] = param (volume/loop) */
    void* soundNode = *(void**)((char*)node + 0x10);
    *(int*)((char*)soundNode + 0x08) = param;

    /* Call gbSound2DNode::Play through IAT at 0x0056a2f4 */
    typedef void (__thiscall *PFN_Play)(void*);
    PFN_Play fnPlay = *(PFN_Play*)0x0056a2f4;
    if (fnPlay != NULL) {
        fnPlay(soundNode);
    }
}

/* ========================================================================
 * CRT/Utility Functions - Low-level runtime support
 * ======================================================================== */

/* 0x005541f8 (30 bytes, 69 callers)
 * MSVC CRT rand() implementation - Linear Congruential Generator.
 * seed = seed * 0x343FD + 0x269EC3; return (seed >> 16) & 0x7FFF;
 */
static unsigned int g_randSeed = 1;

int pal3_rand(void)
{
    g_randSeed = g_randSeed * 0x343FD + 0x269EC3;
    return (g_randSeed >> 16) & 0x7FFF;
}

/* ========================================================================
 * Global Accessor Functions - Singleton getters and array accessors
 * ======================================================================== */

/* 0x0053df70 (6 bytes, 95 callers)
 * __cdecl: returns pointer to static SoundMgr instance
 * MOV EAX,0x17b41e8 / RET
 */
static char s_SoundMgrData[0x32C];
void* SoundMgr_GetInstance(void)
{
    return (void*)s_SoundMgrData;
}

/* 0x004ee870 (28 bytes, 37 callers)
 * __thiscall: this in ECX, 1 stack param (RET 0x4)
 * Returns pointer to role state entry: this + 0x228 + roleIndex * 0x37C
 * Used to access per-role combat data.
 */
void* CCBRoleState_GetEntry(void* self, int roleIndex)
{
    return (char*)self + 0x228 + roleIndex * 0x37C;
}

/* 0x00420f30 (20 bytes, 43 callers)
 * __thiscall: this in ECX, 1 stack param (RET 0x4)
 * Returns pointer to scene role entry: this + 0x784E8 + index * 0xA4
 */
void* SceneMgr_GetRoleEntry(void* self, int index)
{
    return (char*)self + 0x784E8 + index * 0xA4;
}

/* ========================================================================
 * UI3DCtrl methods - 3D viewport embedded in UI
 * ======================================================================== */

/* 0x00439FE0 (140 bytes)
 * __thiscall: this in ECX
 * Converts screen POINT to a ray in 3D space using the control's camera.
 * gbx = x*2/width - 1.0, gby = 1.0 - y*2/height
 * Then calls gbCamera::GetRayToScreen(gbx, gby, &ray)
 */
gbRay* UI3DCtrl::GetMouseRay(gbRay* mray, POINT* cursorpt)
{
    gbRay localRay;
    memset(&localRay, 0, sizeof(localRay));

    float gby = 1.0f - (float)(cursorpt->y * 2) / (float)PAL3_s_drvinfo.height;
    float gbx = (float)(cursorpt->x * 2) / (float)PAL3_s_drvinfo.width - 1.0f;

    if (pfn_gbCamera_GetRayToScreen != NULL) {
        pfn_gbCamera_GetRayToScreen(this->m_camera, gbx, gby, &localRay);
    }

    memcpy(mray, &localRay, sizeof(gbRay));
    return mray;
}

/* 0x00439850 (224 bytes)
 * __thiscall: this in ECX
 * Converts screen (x,y) to normalized device coords, scales by orthosize,
 * builds eye/lookAt/up vectors, calls SetLookAt on camera,
 * then computes and normalizes the view direction into m_raydir.
 */
void UI3DCtrl::SetOriginPt_XY(int x, int y)
{
    float gbx = (float)(x * 2) / (float)PAL3_s_drvinfo.width - 1.0f;
    float gby = 1.0f - (float)(y * 2) / (float)PAL3_s_drvinfo.height;

    float sx = gbx * this->m_orthosize;
    float sy = gby * this->m_orthosize;

    gbVec3D vFrom;
    vFrom.x = -sy;
    vFrom.y = 0.0f;
    vFrom.z = -sx;

    gbVec3D vLookAt;
    vLookAt.x = 0.0f;
    vLookAt.y = 1.0f;
    vLookAt.z = 0.0f;

    gbVec3D vUp;
    vUp.x = 0.0f;
    vUp.y = 0.0f;
    vUp.z = 1600.0f;

    if (pfn_gbCamera_SetLookAt != NULL) {
        pfn_gbCamera_SetLookAt(this->m_camera, &vFrom, &vLookAt, &vUp);
    }

    this->m_raydir.x = vFrom.x;
    this->m_raydir.y = vFrom.y;
    this->m_raydir.z = vFrom.z;

    this->m_raydir.x -= -sy;
    this->m_raydir.y -= 0.0f;
    this->m_raydir.z -= -sx;

    if (pfn_gbVec3D_Normalize != NULL) {
        pfn_gbVec3D_Normalize(&this->m_raydir);
    }
}

/* 0x00439930 (232 bytes)
 * __thiscall: this in ECX
 * Like SetOriginPt_XY but with explicit from_y parameter for vertical offset.
 */
void UI3DCtrl::SetOriginPt_XYFromY(int x, int y, int from_y)
{
    float gbx = (float)(x * 2) / (float)PAL3_s_drvinfo.width - 1.0f;
    float gby = 1.0f - (float)(y * 2) / (float)PAL3_s_drvinfo.height;
    float gbFromY = 1.0f - (float)(from_y * 2) / (float)PAL3_s_drvinfo.height;

    float sx = gbx * this->m_orthosize;
    float sy = gby * this->m_orthosize;
    float sfrom_y = gbFromY * this->m_orthosize;

    gbVec3D vFrom;
    vFrom.x = -sfrom_y;
    vFrom.y = 0.0f;
    vFrom.z = -sx;

    gbVec3D vLookAt;
    vLookAt.x = -sy;
    vLookAt.y = 1.0f;
    vLookAt.z = -sx;

    gbVec3D vUp;
    vUp.x = 0.0f;
    vUp.y = 0.0f;
    vUp.z = 1600.0f;

    if (pfn_gbCamera_SetLookAt != NULL) {
        pfn_gbCamera_SetLookAt(this->m_camera, &vFrom, &vLookAt, &vUp);
    }

    this->m_raydir.x = vLookAt.x - vFrom.x;
    this->m_raydir.y = vLookAt.y - vFrom.y;
    this->m_raydir.z = vLookAt.z - vFrom.z;

    if (pfn_gbVec3D_Normalize != NULL) {
        pfn_gbVec3D_Normalize(&this->m_raydir);
    }
}

/* ========================================================================
 * C2DSpark methods - 2D particle star effects
 * ======================================================================== */

/* 0x004D6050 (330 bytes)
 * __thiscall: this in ECX
 * Creates a single "star" particle at position (x,y) with random velocity/gravity.
 * Builds a C2DSpark_tagSpark struct and calls CreateSingle.
 *
 * Constants from original binary:
 *   0.5f (0x56a610), 250.0f (0x56fb84), 19.0f (0x56fb80)
 *   Inline floats: 200.0 (lum), -10.0 (vx range), -50.0 (ay), -100.0 (lumInc)
 */
void C2DSpark::CreateStars(int x, int y, int nWidth, float fStarSize)
{
    C2DSpark_tagSpark spark;

    spark.fSize = fStarSize;
    spark.fLum = 200.0f;
    spark.fVx = 0.0f;
    spark.fVy = -10.0f;
    spark.fAx = 0.0f;
    spark.fAy = -50.0f;
    spark.fLumInc = -100.0f;
    spark.fSizeInc = 0.0f;
    spark.byColor = 2;

    float halfWidth = (float)nWidth * 0.5f;
    float halfHeight = (float)y * 0.5f;

    /* Random luminosity offset: rand() % 50, subtract from 250 */
    int rLum = pal3_rand() % 50;
    spark.fLum = 250.0f - (float)rLum;

    /* Random X position: base + rand() % nWidth, offset by halfWidth */
    float fHalfW = (float)nWidth;
    int rX = pal3_rand();
    int modX = rX % nWidth;
    spark.fx = (float)modX + (float)x * 0.5f - halfWidth;

    /* Random Y position: rand() % (nWidth*2), offset */
    int rY = pal3_rand();
    int modY = rY % (nWidth * 2);
    spark.fy = (float)modY + halfHeight - fHalfW;

    /* Random vertical acceleration based on fStarSize comparison with 19.0f */
    if (fStarSize < 19.0f) {
        int rA = pal3_rand() % 50;
        spark.fAy = (float)(-rA);
    } else {
        int rA = pal3_rand() % 100;
        spark.fAy = (float)(-rA);
    }

    this->CreateSingle(&spark);
}

/* ========================================================================
 * Memory Management Wrappers
 * ======================================================================== */

/* pal3free (0x00541D10) is defined in pal3_stubs.cpp */

/* ========================================================================
 * UIWnd::Ctor - Zero-initialize UIWnd struct (0x44 bytes = 17 DWORDs)
 * ======================================================================== */

/* 0x00445EA0 (18 bytes)
 * __thiscall: this in ECX
 * MOV EDX,ECX / PUSH EDI / MOV ECX,0x11 / XOR EAX,EAX
 * MOV EDI,EDX / REP STOSD / MOV EAX,EDX / POP EDI / RET
 */
static void* __fastcall UIWnd_Ctor(void* self, int /*edx*/)
{
    memset(self, 0, 0x44);
    return self;
}

/* ========================================================================
 * UIWnd::SetVisible - Set visibility flag with vtable notification
 * ======================================================================== */

/* 0x00445E70 (37 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 4)
 * If not focusable: return. If new value == old value: return.
 * Otherwise: store new value, call vtable[6](this, 0x3E8, newVal, 0)
 */
static void __fastcall UIWnd_SetVisible(UIWnd* self, int /*edx*/, int bShow)
{
    if (self->m_bFocusable == 0) {
        return;
    }
    if (self->bVisible == bShow) {
        return;
    }
    self->bVisible = bShow;
    typedef void (__thiscall *VFN)(void*, int, int, int);
    VFN fn = (VFN)self->vtable[6];
    fn(self, 0x3E8, bShow, 0);
}

/* ========================================================================
 * UIWnd_MoveInternal - Move rect by delta and notify
 * ======================================================================== */

/* 0x00445D40 (66 bytes)
 * __thiscall: this in ECX, 2 stack params (dx, dy) (RET 8)
 * Offsets all 4 rect fields, then calls vtable[6](this, 0x3FE, 0, 0)
 * Also recursively moves children (iterates children array).
 */
static void __fastcall UIWnd_MoveInternal(UIWnd* self, int /*edx*/, int dx, int dy)
{
    self->rect.left += dx;
    self->rect.top += dy;
    self->rect.right += dx;
    self->rect.bottom += dy;

    if (self != NULL) {
        typedef void (__thiscall *VFN)(void*, int, int, int);
        VFN fn = (VFN)self->vtable[6];
        fn(self, 0x3FE, 0, 0);
    }

    for (int i = 0; i < self->nChildren; i++) {
        UIWnd* child = (UIWnd*)self->children[i];
        UIWnd_MoveInternal(child, 0, dx, dy);
    }
}

/* ========================================================================
 * C2DSpark::ResetBigLum - Reset luminosity counter and set color mode
 * ======================================================================== */

/* 0x004D5F20 (21 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 4)
 * MOV AL,[ESP+4] / MOV [ECX+0x580C],0 / MOV [ECX+0x5818],AL / RET 4
 * Resets m_fBigLum to 0 and sets byte at offset 0x5818 (color mode)
 */
void C2DSpark::ResetBigLum(char colorMode)
{
    *(int*)((char*)this + 0x580C) = 0;
    *((char*)this + 0x5818) = colorMode;
}

/* ========================================================================
 * UICursor::Ctor - Initialize cursor instance fields
 * ======================================================================== */

/* 0x00541470 (31 bytes)
 * __thiscall: this in ECX
 * MOV EAX,ECX / XOR ECX,ECX / LEA EDX,[EAX+0x10]
 * MOV [EAX+0xC],3 / MOV [EAX+0x1D],0 / MOV [EAX+0x1C],1
 * MOV [EDX],ECX / MOV [EDX+4],ECX / MOV [EDX+8],ECX / RET
 */
static void __fastcall UICursor_Ctor(UICursor* self, int /*edx*/)
{
    char* base = (char*)self;
    *(int*)(base + 0x0C) = 3;
    *(char*)(base + 0x1D) = 0;
    self->bVisible = 1;
    *(int*)(base + 0x10) = 0;
    *(int*)(base + 0x14) = 0;
    *(int*)(base + 0x18) = 0;
}

/* ========================================================================
 * GRPinput::GetKeyState - Read key state by scan code
 * ======================================================================== */

/* 0x004022C0 (16 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 4)
 * MOV EAX,[ESP+4] / AND EAX,0xFFFF / MOVZX AX,[EAX+ECX+0x68] / RET 4
 * Returns byte value from m_keyStates[keyCode & 0xFFFF]
 */
unsigned short GRPinput::GetKeyState(int keyCode)
{
    int idx = keyCode & 0xFFFF;
    unsigned char val = *((unsigned char*)this + 0x68 + idx);
    return val;
}

/* ========================================================================
 * GRPinput::GetShiftedKeyState - Read shifted key state
 * ======================================================================== */

/* Similar pattern at likely 0x004022D0, reading from +0x176 */

/* ========================================================================
 * PAL3_GameLoop helpers
 * ======================================================================== */

/* 0x00404610 (10 bytes)
 * MOV ECX,0x8ACD40 / JMP 0x457340
 * Jumps to a method on the global at 0x8ACD40 - likely a scene/state update
 */

/* 0x00404630 (10 bytes)
 * MOV ECX,0x8ACD30 / JMP 0x430180
 * Jumps to a method on the global at 0x8ACD30 - likely a UI update
 */

/* ========================================================================
 * UIWnd::GetChild - Get child by index with bounds check
 * ======================================================================== */

/* 0x00445F60 (20 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 4)
 * MOV EAX,[ESP+4] / TEST EAX,EAX / JL fail
 * CMP EAX,0x10 / JGE fail / MOV EAX,[ECX+EAX*4] / RET 4
 * fail: (returns garbage/0)
 * Note: This accesses this+index*4 directly, suggesting a small inline array.
 */
static void* __fastcall UIWnd_GetChild(void* self, int /*edx*/, int index)
{
    if (index < 0) {
        return NULL;
    }
    if (index >= 0x10) {
        return NULL;
    }
    return ((void**)self)[index];
}

/* PAL3_CheckCD (0x541860) and PAL3_OpenRegistry (0x541C40) are in winmain.cpp */

/* ========================================================================
 * UIWnd - Simple field setters (COMDAT)
 * ======================================================================== */

/* 0x00446010 (10 bytes)
 * __thiscall: this in ECX, 1 stack param (RECT* ptr, RET 4)
 * MOV EAX,[ESP+4] / MOV EDX,[EAX] / MOV [ECX+4],EDX / RET 4
 * Copies first DWORD from pointed-to struct into this+4
 */
__declspec(noinline) void __fastcall UIWnd_SetPadding1(void* self, int /*edx*/, int* pVal)
{
    int val = *pVal;
    *(int*)((char*)self + 4) = val;
}

/* 0x00446020 (10 bytes)
 * __thiscall: this in ECX, 1 stack param (int, RET 4)
 * MOV EAX,[ESP+4] / MOV [ECX+8],EAX / RET 4
 * Sets field at offset 0x08
 */
__declspec(noinline) void __fastcall UIWnd_SetField08(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 8) = value;
}

/* ========================================================================
 * SceneMgr - Scene data accessor
 * ======================================================================== */

/* 0x00420F50 (17 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 4)
 * MOV EAX,[ESP+4] / ADD EAX,0x7863 / SHL EAX,4 / ADD EAX,ECX / RET 4
 * Returns pointer to scene data entry: this + (index + 0x7863) * 16
 */
struct SceneMgrData {
    void* GetDataEntry(int index);
};
__declspec(noinline) void* SceneMgrData::GetDataEntry(int index)
{
    return (char*)this + ((index + 0x7863) << 4);
}

/* ========================================================================
 * CCBRoleState - Combat ATB readiness check
 * ======================================================================== */

/* 0x004ED100 (104 bytes)
 * __thiscall: this in ECX, 1 stack param (char bCheckEnemies, RET 4)
 * Checks if all enemies (or allies) have their ATB gauge full.
 * If bCheckEnemies: checks roles 5-10, tests bExists(offset-0xB), ATB>0, and extraFlag(+0x34C)
 * If !bCheckEnemies: checks roles 5-10 differently (bAlive at -1, bAlive==1, extraFlag+0x356)
 * Returns 0 if any qualifying role found with flag==0, else returns 1.
 *
 * Layout per entry (stride 0x37C from CCBRoleState base):
 *   Base for role 5: this + 0x13B8  (= 0x228 + 5*0x37C + some offset)
 *   [base - 0x0B] = bExists
 *   [base + 0x00] = ATB value (int)
 *   [base + 0x34C] = flag for bCheckEnemies path
 *   For !bCheckEnemies path, starts at this+0x13AE:
 *   [base - 0x01] = bExists
 *   [base + 0x00] = bAlive (must == 1)
 *   [base + 0x356] = flag
 */
__declspec(noinline) int __fastcall CCBRoleState_AllReady(void* self, int /*edx*/, char bCheckEnemies)
{
    char* base;
    int i;

    if (bCheckEnemies) {
        base = (char*)self + 0x13B8;
        for (i = 5; i < 11; i++) {
            if (*(base - 0x0B) != 0) {
                if (*(int*)base > 0) {
                    if (*(base + 0x34C) == 0) {
                        return 0;
                    }
                }
            }
            base += 0x37C;
        }
    } else {
        base = (char*)self + 0x13AE;
        for (i = 5; i < 11; i++) {
            if (*(base - 1) != 0) {
                if (*base == 1) {
                    if (*(base + 0x356) == 0) {
                        return 0;
                    }
                }
            }
            base += 0x37C;
        }
    }
    return 1;
}

/* ========================================================================
 * SoundMgr - String comparison helper for name sorting
 * ======================================================================== */

/* 0x0053DF80 (48 bytes)
 * __cdecl: 2 stack params (pointers to structs with char* at offset +4)
 * If either +4 is NULL, uses static empty string at 0x56a634.
 * Calls _stricmp and returns (result > 0) ? 0 : 1
 */
__declspec(noinline) int __cdecl SoundMgr_CompareNames(void* a, void* b)
{
    static char s_empty[4] = {0};
    char* nameA = *(char**)((char*)a + 4);
    char* nameB = *(char**)((char*)b + 4);

    if (nameB == NULL) nameB = s_empty;
    if (nameA == NULL) nameA = s_empty;

    int result = _stricmp(nameA, nameB);
    if (result > 0) return 0;
    return 1;
}

/* ========================================================================
 * CCBRoleState - Additional combat role accessors
 * ======================================================================== */

/* 0x004ED040 (26 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 4)
 * Returns byte at this + roleIndex*0x37C + 0x243
 * (Role flag: e.g. "is defending" or "is acting")
 */
__declspec(noinline) char __fastcall CCBRoleState_GetFlag243(void* self, int /*edx*/, int roleIndex)
{
    char* base = (char*)self;
    int offset = roleIndex * 0x37C;
    return *(base + offset + 0x243);
}

/* 0x004ED060 (58 bytes)
 * __thiscall: this in ECX, 1 stack param (RET 4)
 * If !bExists: return 0
 * If [+0x243] == 1: return 0
 * Else: return byte at [+0x244]
 */
__declspec(noinline) char __fastcall CCBRoleState_GetActionState(void* self, int /*edx*/, int roleIndex)
{
    char* base = (char*)self;
    int offset = roleIndex * 0x37C;

    if (*(base + offset + 0x241) == 0) {
        return 0;
    }
    if (*(unsigned char*)(base + offset + 0x243) == 1) {
        return 0;
    }
    return *(base + offset + 0x244);
}

/* 0x004ED0A0 (82 bytes)
 * __thiscall: this in ECX, 1 stack param (char bCheckEnemies, RET 4)
 * Checks player party (roles 0-4) for ATB readiness.
 * If bCheckEnemies: checks bExists and ATB>0
 * If !bCheckEnemies: checks bAlive and bAlive==1
 * Returns 0 if any qualifying role found, else 1.
 */
__declspec(noinline) int __fastcall CCBRoleState_AnyPartyReady(void* self, int /*edx*/, char bCheckEnemies)
{
    char* base;
    int i;

    if (bCheckEnemies) {
        base = (char*)self + 0x24C;
        for (i = 0; i < 5; i++) {
            if (*(base - 0x0B) != 0) {
                if (*(int*)base > 0) {
                    return 0;
                }
            }
            base += 0x37C;
        }
    } else {
        base = (char*)self + 0x242;
        for (i = 0; i < 5; i++) {
            if (*(base - 1) != 0) {
                if (*base == 1) {
                    return 0;
                }
            }
            base += 0x37C;
        }
    }
    return 1;
}

/* ========================================================================
 * Game Loop Thunks - Thin wrappers that set ECX to global and jump
 * ======================================================================== */

/* 0x00404610 (10 bytes) - MOV ECX,0x8ACD40 / JMP 0x457340
 * Dispatches to CGameState::Update on global game state object */

/* 0x00404630 (10 bytes) - MOV ECX,0x8ACD30 / JMP 0x430180
 * Dispatches to CUIManager::Update on global UI manager object */

/* 0x00404650 (10 bytes) - MOV ECX,0x8ACD30 / JMP 0x430230
 * Dispatches to CUIManager::Render on global UI manager object */

/* 0x00404670 (10 bytes) - MOV ECX,0x8ACC10 / JMP target
 * Dispatches to another global object method */

/* Note: These thunks cannot be implemented as standalone C functions since
 * they use tail-call jumps (JMP instead of CALL+RET). They need inline asm
 * or naked functions which require the original compiler for byte-matching. */

/* ========================================================================
 * GRPinput::UnacquireKeyboard - Release keyboard and clear states
 * ======================================================================== */

/* 0x004023D0 (33 bytes)
 * __thiscall: this in ECX (ESI)
 * Calls ClearKeyStates, sets m_bKeyboard=0,
 * then calls IDirectInputDevice8::Unacquire on keyboard device.
 */
void GRPinput::UnacquireKeyboard()
{
    this->ClearKeyStates();
    this->m_bKeyboard = 0;

    void* pDev = this->m_lpDIDKeyboard;
    if (pDev != NULL) {
        typedef long (__stdcall *PFNUNACQUIRE)(void*);
        void** vtable = *(void***)pDev;
        PFNUNACQUIRE fnUnacquire = (PFNUNACQUIRE)vtable[0x20 / 4];
        fnUnacquire(pDev);
    }
}

/* ========================================================================
 * GRPinput::UnacquireMouse - Release mouse device
 * ======================================================================== */

/* 0x004023F4 (27 bytes, estimated)
 * __thiscall: this in ECX (ESI)
 * Sets m_bMouse=0, then calls IDirectInputDevice8::Unacquire on mouse.
 */
void GRPinput::UnacquireMouse()
{
    this->m_bMouse = 0;

    void* pDev = this->m_lpDIDMouse;
    if (pDev != NULL) {
        typedef long (__stdcall *PFNUNACQUIRE)(void*);
        void** vtable = *(void***)pDev;
        PFNUNACQUIRE fnUnacquire = (PFNUNACQUIRE)vtable[0x20 / 4];
        fnUnacquire(pDev);
    }
}

/* ========================================================================
 * GRPinput::Poll - Read keyboard state via GetDeviceState
 * ======================================================================== */

/* 0x00402400 (59 bytes)
 * __thiscall: this in ECX (ESI)
 * If keyboard active: call IDirectInputDevice8::GetDeviceState(256, &shiftedKeys)
 * On failure: calls AcquireKeyboard to re-acquire.
 * On success: proceeds to compare old/new key states (continues at 0x40243B+)
 */
void GRPinput::PollKeyboard()
{
    if (this->m_bKeyboard == 0) {
        return;
    }

    void* pDev = this->m_lpDIDKeyboard;
    char* destBuf = (char*)this + 0x176;

    typedef long (__stdcall *PFNGETDEVICESTATE)(void*, int, void*);
    void** vtable = *(void***)pDev;
    PFNGETDEVICESTATE fnGetState = (PFNGETDEVICESTATE)vtable[0x24 / 4];

    long hr = fnGetState(pDev, 0x100, destBuf);
    if (hr != 0) {
        this->AcquireKeyboard();
    }
}

/* ========================================================================
 * Simple setters - 10-byte pattern: mov eax,[esp+4]/mov [ecx+N],eax/ret 4
 * All produce exact byte matches with original.
 * ======================================================================== */

/* 0x00402FA0 (10 bytes) - GRPinput: set field at offset 0x20 */
__declspec(noinline) void __fastcall GRPinput_SetField20(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x20) = value;
}

/* 0x0043A4B0 (10 bytes) - UIAnimateCtrl: set m_pFrameTex at offset 0x44 */
__declspec(noinline) void __fastcall UICtrl_SetField44(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x44) = value;
}

/* 0x00450550 (10 bytes) - Game control: set field at offset 0x50 */
__declspec(noinline) void __fastcall GameCtrl_SetField50(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x50) = value;
}

/* 0x004B73D0 (10 bytes) - Combat/effect: set field at offset 0x5C */
__declspec(noinline) void __fastcall CombatObj_SetField5C(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x5C) = value;
}

/* 0x0051BB40 (10 bytes) - CCBLineupWindow: set currentPage at offset 0x74 */
__declspec(noinline) void __fastcall CCBLineup_SetPage(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x74) = value;
}

/* 0x00530340 (10 bytes) - Resource: set field at offset 0x04 */
__declspec(noinline) void __fastcall Resource_SetField04(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x04) = value;
}

/* ========================================================================
 * 13-byte setters - dword displacement: mov eax,[esp+4]/mov [ecx+NNNN],eax/ret 4
 * Pattern: 8b 44 24 04 89 81 XX XX XX XX c2 04 00
 * All produce exact byte matches with original.
 * ======================================================================== */

/* 0x0041D5B0 (13 bytes) - field offset 0x1CC */
__declspec(noinline) void __fastcall Setter_0041D5B0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x1CC) = value;
}

/* 0x0041D5C0 (13 bytes) - field offset 0x1D4 */
__declspec(noinline) void __fastcall Setter_0041D5C0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x1D4) = value;
}

/* 0x0043A0E0 (13 bytes) - field offset 0xF8 */
__declspec(noinline) void __fastcall Setter_0043A0E0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0xF8) = value;
}

/* 0x0043A680 (13 bytes) - field offset 0x9C */
__declspec(noinline) void __fastcall Setter_0043A680(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x9C) = value;
}

/* 0x0043F640 (13 bytes) - field offset 0x454 */
__declspec(noinline) void __fastcall Setter_0043F640(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x454) = value;
}

/* 0x0043F690 (13 bytes) - field offset 0x4A4 */
__declspec(noinline) void __fastcall Setter_0043F690(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x4A4) = value;
}

/* 0x004421F0 (13 bytes) - field offset 0x150 */
__declspec(noinline) void __fastcall Setter_004421F0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x150) = value;
}

/* 0x00442C80 (13 bytes) - field offset 0x94 */
__declspec(noinline) void __fastcall Setter_00442C80(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x94) = value;
}

/* 0x00445910 (13 bytes) - field offset 0xB4 */
__declspec(noinline) void __fastcall Setter_00445910(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0xB4) = value;
}

/* 0x00449980 (13 bytes) - field offset 0x16C */
__declspec(noinline) void __fastcall Setter_00449980(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x16C) = value;
}

/* 0x00455190 (13 bytes) - field offset 0xB0 */
__declspec(noinline) void __fastcall Setter_00455190(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0xB0) = value;
}

/* 0x004B4840 (13 bytes) - field offset 0x84 */
__declspec(noinline) void __fastcall Setter_004B4840(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x84) = value;
}

/* 0x004B4910 (13 bytes) - field offset 0x244 */
__declspec(noinline) void __fastcall Setter_004B4910(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x244) = value;
}

/* 0x004BB180 (13 bytes) - field offset 0x164 */
__declspec(noinline) void __fastcall Setter_004BB180(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x164) = value;
}

/* 0x004BC7E0 (13 bytes) - field offset 0x58968 */
__declspec(noinline) void __fastcall Setter_004BC7E0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x58968) = value;
}

/* 0x0051F070 (13 bytes) - field offset 0x1F4C */
__declspec(noinline) void __fastcall Setter_0051F070(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x1F4C) = value;
}

/* 0x0051F080 (13 bytes) - field offset 0x1F50 */
__declspec(noinline) void __fastcall Setter_0051F080(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x1F50) = value;
}

/* 0x0051F090 (13 bytes) - field offset 0x1F54 */
__declspec(noinline) void __fastcall Setter_0051F090(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x1F54) = value;
}

/* 0x00524960 (13 bytes) - field offset 0x1484 */
__declspec(noinline) void __fastcall Setter_00524960(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x1484) = value;
}

/* 0x0052F300 (13 bytes) - field offset 0x12C */
__declspec(noinline) void __fastcall Setter_0052F300(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x12C) = value;
}

/* 0x0052FBA0 (13 bytes) - field offset 0x8A0 */
__declspec(noinline) void __fastcall Setter_0052FBA0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x8A0) = value;
}

/* 0x00530990 (13 bytes) - field offset 0x308 */
__declspec(noinline) void __fastcall Setter_00530990(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x308) = value;
}

/* 0x005322D0 (13 bytes) - field offset 0x51C */
__declspec(noinline) void __fastcall Setter_005322D0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x51C) = value;
}

/* 0x005322E0 (13 bytes) - field offset 0x520 */
__declspec(noinline) void __fastcall Setter_005322E0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x520) = value;
}

/* 0x0053CDD0 (13 bytes) - field offset 0x1224 */
__declspec(noinline) void __fastcall Setter_0053CDD0(void* self, int /*edx*/, int value)
{
    *(int*)((char*)self + 0x1224) = value;
}

/* ========================================================================
 * 4-byte getters (__thiscall, no params): mov eax,[ecx+byte]/ret
 * Pattern: 8b 41 XX c3
 * ======================================================================== */

/* 0x0044AB00 (4 bytes) - mov eax,[ecx-0x0C]/ret (negative offset getter) */
__declspec(noinline) int __fastcall Getter_0044AB00(void* self, int)
{
    return *(int*)((char*)self - 0x0C);
}

/* 0x004503C0 (4 bytes) - mov eax,[ecx-0x10]/ret (negative offset getter) */
__declspec(noinline) int __fastcall Getter_004503C0(void* self, int)
{
    return *(int*)((char*)self - 0x10);
}

/* 0x004B7020 (4 bytes) - field 0x58 */
__declspec(noinline) int __fastcall Getter_004B7020(void* self, int)
{
    return *(int*)((char*)self + 0x58);
}

/* 0x004BDF60 (4 bytes) - field 0x08 */
__declspec(noinline) int __fastcall Getter_004BDF60(void* self, int)
{
    return *(int*)((char*)self + 0x08);
}

/* 0x004DC5B0 (4 bytes) - field 0x20 */
__declspec(noinline) int __fastcall Getter_004DC5B0(void* self, int)
{
    return *(int*)((char*)self + 0x20);
}

/* 0x004FE540 (4 bytes) - field 0x04 */
__declspec(noinline) int __fastcall Getter_004FE540(void* self, int)
{
    return *(int*)((char*)self + 0x04);
}

/* 0x0051AC30 (4 bytes) - field 0x7C */
__declspec(noinline) int __fastcall Getter_0051AC30(void* self, int)
{
    return *(int*)((char*)self + 0x7C);
}

/* ========================================================================
 * 7-byte getters (__thiscall, no params): mov eax,[ecx+dword]/ret
 * Pattern: 8b 81 XX XX XX XX c3
 * ======================================================================== */

/* 0x0044FF60 (7 bytes) - field 0x38CC */
__declspec(noinline) int __fastcall Getter_0044FF60(void* self, int)
{
    return *(int*)((char*)self + 0x38CC);
}

/* 0x00451730 (7 bytes) - field 0x450 */
__declspec(noinline) int __fastcall Getter_00451730(void* self, int)
{
    return *(int*)((char*)self + 0x450);
}

/* 0x00479040 (7 bytes) - field 0x84 */
__declspec(noinline) int __fastcall Getter_00479040(void* self, int)
{
    return *(int*)((char*)self + 0x84);
}

/* 0x004790F0 (7 bytes) - field 0x8C */
__declspec(noinline) int __fastcall Getter_004790F0(void* self, int)
{
    return *(int*)((char*)self + 0x8C);
}

/* 0x004791A0 (7 bytes) - field 0x94 */
__declspec(noinline) int __fastcall Getter_004791A0(void* self, int)
{
    return *(int*)((char*)self + 0x94);
}

/* 0x00479250 (7 bytes) - field 0x9C */
__declspec(noinline) int __fastcall Getter_00479250(void* self, int)
{
    return *(int*)((char*)self + 0x9C);
}

/* 0x004F3420 (7 bytes) - field 0x278 */
__declspec(noinline) int __fastcall Getter_004F3420(void* self, int)
{
    return *(int*)((char*)self + 0x278);
}

/* 0x00525080 (7 bytes) - field 0x1490 */
__declspec(noinline) int __fastcall Getter_00525080(void* self, int)
{
    return *(int*)((char*)self + 0x1490);
}

/* 0x0053E500 (7 bytes) - field 0x328 */
__declspec(noinline) int __fastcall Getter_0053E500(void* self, int)
{
    return *(int*)((char*)self + 0x328);
}


/* ========================================================================
 * Miscellaneous small functions from Ghidra exports
 * ======================================================================== */

/* 6-byte constant return functions: mov eax,imm32 / ret */

__declspec(noinline) int __cdecl Func_00407D40() { return -3; }
__declspec(noinline) int __cdecl Func_004126F9() { return 52; }
__declspec(noinline) int __cdecl Func_004126FF() { return 50; }
__declspec(noinline) int __cdecl Func_0041EB66() { return 3; }
__declspec(noinline) int __cdecl Func_0041EB6C() { return 1; }
__declspec(noinline) int __cdecl Func_0041EB72() { return 2; }
__declspec(noinline) int __cdecl Func_0042C024() { return 1; }
__declspec(noinline) int __cdecl Func_00434CD8() { return 1; }
__declspec(noinline) int __cdecl Func_00434F75() { return 2; }
__declspec(noinline) int __cdecl Func_00434F7B() { return 1; }
__declspec(noinline) int __cdecl Func_0053833E() { return 1; }

/* 8-byte constant return with stack cleanup: mov eax,imm32 / ret N
 * These are __thiscall methods returning constants (this in ECX, params on stack) */

/* ret 4 = 1 stack param after this */
__declspec(noinline) int __fastcall Func_004B73E0(void*, int, int) { return 1; }
__declspec(noinline) int __fastcall Func_004DF381(void*, int, int) { return 16; }
__declspec(noinline) int __fastcall Func_004DF389(void*, int, int) { return 2; }
__declspec(noinline) int __fastcall Func_004DF391(void*, int, int) { return 3; }
__declspec(noinline) int __fastcall Func_004DF399(void*, int, int) { return 5; }
__declspec(noinline) int __fastcall Func_004DF3A1(void*, int, int) { return 9; }
__declspec(noinline) int __fastcall Func_004DF3A9(void*, int, int) { return 17; }
__declspec(noinline) int __fastcall Func_004F3C0F(void*, int, int) { return 1; }
__declspec(noinline) int __fastcall Func_004F3C17(void*, int, int) { return 2; }
__declspec(noinline) int __fastcall Func_004FA6B1(void*, int, int) { return 3; }
__declspec(noinline) int __fastcall Func_004FA6B9(void*, int, int) { return 5; }
__declspec(noinline) int __fastcall Func_004FA6C1(void*, int, int) { return 1; }
__declspec(noinline) int __fastcall Func_004FA6C9(void*, int, int) { return 2; }
__declspec(noinline) int __fastcall Func_004FA6D1(void*, int, int) { return 4; }
__declspec(noinline) int __fastcall Func_004FA711(void*, int, int) { return 5; }
__declspec(noinline) int __fastcall Func_004FA719(void*, int, int) { return 1; }
__declspec(noinline) int __fastcall Func_004FA721(void*, int, int) { return 2; }

/* ret 12 = 3 stack params (thiscall with 3 extra params) */
__declspec(noinline) int __fastcall Func_0047E536(void*, int, int, int, int) { return 1; }
__declspec(noinline) int __fastcall Func_004B3A25(void*, int, int, int, int) { return 1; }
__declspec(noinline) int __fastcall Func_005329BE(void*, int, int, int, int) { return 1; }

/* ret 16 = 4 stack params (thiscall with 4 extra params) */
__declspec(noinline) int __fastcall Func_004E114F(void*, int, int, int, int, int) { return 1; }

/* 5-byte return-0 functions: xor eax,eax / ret N */

/* ret 4 (1 stack param) */
__declspec(noinline) int __fastcall Func_00445F73(void*, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_00479075(void*, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_00479121(void*, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_004791D2(void*, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_0047927F(void*, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_004CA447(void*, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_004D364D(void*, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_004FA6D9(void*, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_004FA739(void*, int, int) { return 0; }

/* ret 8 (2 stack params) */
__declspec(noinline) int __fastcall Func_004014E0(void*, int, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_00418DB8(void*, int, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_0043A40F(void*, int, int, int) { return 0; }

/* ret 12 (3 stack params) */
__declspec(noinline) int __fastcall Func_00445D10(void*, int, int, int, int) { return 0; }

/* ret 16 (4 stack params) */
__declspec(noinline) int __fastcall Func_004E110C(void*, int, int, int, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_004E1134(void*, int, int, int, int, int) { return 0; }
__declspec(noinline) int __fastcall Func_004E2471(void*, int, int, int, int, int) { return 0; }

/* ========================================================================
 * 7-byte float getters: fld dword ptr [ecx+dword]/ret
 * Pattern: d9 81 XX XX XX XX c3
 * ======================================================================== */

/* 0x0052E8FB (7 bytes) - float field 0x10C */
__declspec(noinline) float __fastcall FloatGetter_0052E8FB(void* self, int)
{
    return *(float*)((char*)self + 0x10C);
}

/* 0x0052E97B (7 bytes) - float field 0x110 */
__declspec(noinline) float __fastcall FloatGetter_0052E97B(void* self, int)
{
    return *(float*)((char*)self + 0x110);
}

/* 0x0052E9FB (7 bytes) - float field 0x114 */
__declspec(noinline) float __fastcall FloatGetter_0052E9FB(void* self, int)
{
    return *(float*)((char*)self + 0x114);
}

/* 0x0052EA7B (7 bytes) - float field 0x118 */
__declspec(noinline) float __fastcall FloatGetter_0052EA7B(void* self, int)
{
    return *(float*)((char*)self + 0x118);
}

/* 0x00534CA5 (7 bytes) - float field 0x2E0 */
__declspec(noinline) float __fastcall FloatGetter_00534CA5(void* self, int)
{
    return *(float*)((char*)self + 0x2E0);
}

/* 0x0040F050 (13 bytes) - array element access: return this->array[index]
 * mov eax,[ecx+4] / mov ecx,[esp+4] / mov eax,[eax+ecx*4] / ret 4 */
struct ArrayObj { int pad; int** pArray; int GetAt(int index); };
__declspec(noinline) int ArrayObj::GetAt(int index)
{
    return (int)(this->pArray[index]);
}

/* 0x0041BDE0 (16 bytes) - zero-init 4 dwords (RECT or similar)
 * mov eax,ecx / xor ecx,ecx / mov [eax],ecx / mov [eax+4],ecx / mov [eax+8],ecx / mov [eax+0c],ecx / ret
 * __thiscall - zeros the first 16 bytes of a struct */
struct ZeroInit16 { void Clear(); };
__declspec(noinline) void ZeroInit16::Clear()
{
    int* p = (int*)this;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

/* 0x0040F030 (19 bytes) - vector element count
 * if (ptr == 0) return 0; else return (end - begin) >> 2;
 * __thiscall: this->+4 = begin, this->+8 = end */
struct VectorCountObj {
    int vtable;
    int* begin;
    int* end;
    int GetCount();
};
__declspec(noinline) int VectorCountObj::GetCount()
{
    if (this->begin == 0)
        return 0;
    return (int)((char*)this->end - (char*)this->begin) >> 2;
}

/* ========================================================================
 * 6-byte cdecl constant returns: mov eax,imm32 / ret (C3)
 * Pattern: b8 XX XX XX XX c3
 * ======================================================================== */

__declspec(noinline) int __cdecl Func_0055910B() { return 0x404; }
__declspec(noinline) int __cdecl Func_00559111() { return 0x412; }
__declspec(noinline) int __cdecl Func_00559117() { return 0x804; }
__declspec(noinline) int __cdecl Func_0055911D() { return 0x411; }

/* ========================================================================
 * 3-byte cdecl return 0: xor eax,eax / ret (C3)
 * Pattern: 33 c0 c3
 * ======================================================================== */

__declspec(noinline) int __cdecl Func_00416545() { return 0; }
__declspec(noinline) int __cdecl Func_0041CBE3() { return 0; }
__declspec(noinline) int __cdecl Func_004235F8() { return 0; }
__declspec(noinline) int __cdecl Func_0042C1B7() { return 0; }
__declspec(noinline) int __cdecl Func_00434D33() { return 0; }
__declspec(noinline) int __cdecl Func_0052F346() { return 0; }
__declspec(noinline) int __cdecl Func_0053D2E4() { return 0; }
__declspec(noinline) int __cdecl Func_00555860() { return 0; }
__declspec(noinline) int __cdecl Func_00556514() { return 0; }
__declspec(noinline) int __cdecl Func_005579A5() { return 0; }

/* ========================================================================
 * 3-byte return this: mov eax,ecx / ret
 * Pattern: 8b c1 c3
 * ======================================================================== */

__declspec(noinline) void* __fastcall Func_00408BC0(void* self, int)
{
    return self;
}

/* ========================================================================
 * 4-byte LEA getters: lea eax,[ecx+disp8] / ret
 * Pattern: 8d 41 XX c3
 * Returns pointer to a field within this
 * ======================================================================== */

__declspec(noinline) void* __fastcall Func_004BDEC0(void* self, int)
{
    return (char*)self + 0x64;
}

__declspec(noinline) void* __fastcall Func_004BDEC4(void* self, int)
{
    return (char*)self + 0x04;
}

/* ========================================================================
 * 7-byte mov al getters: mov al,[ecx+OFFSET32] / ret
 * Pattern: 8a 81 XX XX XX XX c3
 * Returns a byte field (char return value)
 * ======================================================================== */

__declspec(noinline) char __fastcall Func_00469D40(void* self, int)
{
    return *((char*)self + 0xCD4);
}

__declspec(noinline) char __fastcall Func_004B4830(void* self, int)
{
    return *((char*)self + 0x80);
}

/* 0x0047DD60 (9 bytes) - xor eax,eax / mov al,[ecx+0xEAD] / ret
 * Cannot match with modern MSVC (generates movzx instead of xor+mov al) */

/* ========================================================================
 * 9-byte getters with ret 4: mov eax,[ecx+OFF32] / ret 4
 * Pattern: 8b 81 XX XX XX XX c2 04 00
 * __thiscall getter with 1 unused stack param
 * ======================================================================== */

__declspec(noinline) int __fastcall Func_0044F8B6(void* self, int, int)
{
    return *(int*)((char*)self + 0x6E14);
}

__declspec(noinline) int __fastcall Func_0044F8BF(void* self, int, int)
{
    return *(int*)((char*)self + 0x6E10);
}

/* ========================================================================
 * 5-byte byte setters: mov byte ptr [ecx+disp8],imm8 / ret
 * Pattern: c6 41 XX YY c3
 * ======================================================================== */

__declspec(noinline) void __fastcall Func_0042AF96(void* self, int)
{
    *((char*)self + 0x50) = 0;
}

__declspec(noinline) void __fastcall Func_004531F0(void* self, int)
{
    *((char*)self + 0x64) = 1;
}

/* ========================================================================
 * 8-byte byte setter (32-bit offset): mov byte ptr [ecx+OFF32],imm8 / ret
 * Pattern: c6 81 XX XX XX XX YY c3
 * ======================================================================== */

__declspec(noinline) void __fastcall Func_00444D20(void* self, int)
{
    *((char*)self + 0xAE) = 1;
}

/* ========================================================================
 * 6-byte short dword setter: mov [ecx+disp8],edx / ret 4
 * Pattern: 89 51 XX c2 04 00
 * __thiscall with 1 stack param (value in edx via __fastcall)
 * ======================================================================== */

__declspec(noinline) void __fastcall Func_0041D898(void* self, int value, int)
{
    *(int*)((char*)self + 0x08) = value;
}

/* ========================================================================
 * Medium-size functions (15-17 bytes)
 * ======================================================================== */

/* 0x00444D10 (15 bytes) - cannot match: compiler merges adjacent byte stores into word store */

/* 0x0044DB50 (20 bytes) - set byte field + dword field from param
 * 8b 44 24 04 c6 81 48 36 00 00 01 89 81 4c 36 00 00 c2 04 00
 * mov eax,[esp+4] / mov byte [ecx+0x3648],1 / mov [ecx+0x364C],eax / ret 4 */
__declspec(noinline) void __fastcall Func_0044DB50(void* self, int, int value)
{
    *((char*)self + 0x3648) = 1;
    *(int*)((char*)self + 0x364C) = value;
}

/* 0x00407B30 (17B) - cannot match: compiler reorders load/store and uses different registers */
/* 0x0043EBA0 (16B) - cannot match: compiler folds sub into memory operand (sub eax,[ecx+14]) */

/* 0x0050A8E0 (15 bytes) - setter returns TRUE
 * 8b 44 24 04 89 81 a4 19 00 00 b0 01 c2 04 00
 * mov eax,[esp+4] / mov [ecx+0x19A4],eax / mov al,1 / ret 4 */
__declspec(noinline) char __fastcall Func_0050A8E0(void* self, int, int value)
{
    *(int*)((char*)self + 0x19A4) = value;
    return 1;
}

/* 0x0043DC40, 0x00442C60 (17 bytes each) - cannot match: register scheduling differs
 * Original: load both params then store both. Modern MSVC: sequential load-store pairs */

/* 0x004A1CF0 (17 bytes) - get field value and set to -1
 * 8b 81 30 05 00 00 c7 81 30 05 00 00 ff ff ff ff c3
 * mov eax,[ecx+0x530] / mov dword [ecx+0x530],-1 / ret */
__declspec(noinline) int __fastcall Func_004A1CF0(void* self, int)
{
    int old = *(int*)((char*)self + 0x530);
    *(int*)((char*)self + 0x530) = -1;
    return old;
}

/* 0x00530270 (16 bytes) - cannot match: original uses mov eax,ecx then [eax+X],
 * modern MSVC directly uses ecx (saving the mov eax,ecx) */

/* 0x0042FB40 (17 bytes) - set dword field to 0 and byte field from param
 * 8a 44 24 04 c7 41 54 00 00 00 00 88 41 50 c2 04 00
 * mov al,[esp+4] / mov dword [ecx+54],0 / mov byte [ecx+50],al / ret 4 */
__declspec(noinline) void __fastcall Func_0042FB40(void* self, int, char value)
{
    *(int*)((char*)self + 0x54) = 0;
    *((char*)self + 0x50) = value;
}

/* ========================================================================
 * LEA/arithmetic index functions (17-20 bytes)
 * ======================================================================== */

/* 0x00420F50 (17B) - index calculation: (param + 0x7863) << 4 + this
 * 8b 44 24 04 05 63 78 00 00 c1 e0 04 03 c1 c2 04 00 */
__declspec(noinline) void* __fastcall Func_00420F50(void* self, int, int idx)
{
    return (char*)self + ((idx + 0x7863) << 4);
}

/* 0x00528D30 (17B) - cannot match: compiler reorders add ecx before shl eax */
/* 0x00420F30 (20B) - cannot match: compiler uses imul instead of LEA chain */
/* 0x0052FBB0 (20B) - cannot match: compiler uses imul instead of LEA chain */
/* 0x0052FC30 (20B) - cannot match: compiler uses imul instead of LEA chain */

/* ========================================================================
 * Field clear + set functions (23 bytes)
 * Pattern: load param, store constant 0 to field A, store param to field B
 * ======================================================================== */

/* 0x0041C190 (23B) - clear dword field + set another dword field from param
 * 8b 44 24 04 c7 81 7c 01 00 00 00 00 00 00 89 81 80 01 00 00 c2 04 00 */
__declspec(noinline) void __fastcall Func_0041C190(void* self, int, int value)
{
    *(int*)((char*)self + 0x17C) = 0;
    *(int*)((char*)self + 0x180) = value;
}

/* 0x004D5F20 (23B) - C2DSpark::ResetBigLum - clear dword + set byte from param
 * 8a 44 24 04 c7 81 0c 58 00 00 00 00 00 00 88 81 18 58 00 00 c2 04 00 */
__declspec(noinline) void __fastcall Func_004D5F20(void* self, int, char colorMode)
{
    *(int*)((char*)self + 0x580C) = 0;
    *((char*)self + 0x5818) = colorMode;
}

/* 0x00505800 (23B) - cannot match: compiler uses mov dword,-1 instead of or eax,-1 + store */
/* 0x00530BE0 (25B) - cannot match: compiler reorders param load after first store */
/* 0x0043A660 (18B) - cannot match: compiler uses mov dword,0 instead of xor eax + store */
/* 0x004DB780/4DB920 (18B each) - cannot match: compiler reorders lea before byte load */
/* 0x004DB6A0/4DB6C0 (21B each) - cannot match: compiler inserts xor eax,eax and uses edx */
/* 0x00527D60 (19B) - cannot match: compiler uses eax instead of edx as intermediate */
/* 0x005541F8 (30B) - cannot match: relocation-dependent absolute addresses differ */
/* 0x005363A0 (21B) - cannot match: compiler merges adjacent byte stores into word store */

/* 0x0043F670, 0x004431E0, 0x004B4D80, 0x004B4DA0 (23B each) - cannot match:
 * load-all-then-store-all pattern (mov eax,[esp+4] / mov edx,[esp+8] / store / store) */

/* ========================================================================
 * Field copy / const store functions (7-13 bytes)
 * ======================================================================== */

/* 0x00431C00 (13B) - copy dword field to adjacent field
 * 8b 81 04 02 00 00 89 81 08 02 00 00 c3 */
__declspec(noinline) void __fastcall Func_00431C00(void* self, int)
{
    *(int*)((char*)self + 0x208) = *(int*)((char*)self + 0x204);
}

/* 0x00532D30 (7B) - copy dword field disp8 to disp8
 * 8b 41 50 89 41 18 c3 */
__declspec(noinline) void __fastcall Func_00532D30(void* self, int)
{
    *(int*)((char*)self + 0x18) = *(int*)((char*)self + 0x50);
}

/* 0x00532D50 (8B) - store 0 to dword field disp8
 * c7 41 18 00 00 00 00 c3 */
__declspec(noinline) void __fastcall Func_00532D50(void* self, int)
{
    *(int*)((char*)self + 0x18) = 0;
}

/* 0x0054767B (11B) - store vtable pointer constant
 * c7 81 10 01 00 00 00 ca 54 00 c3 */
static const int g_vtbl_0054CA00 = 0x0054CA00;
__declspec(noinline) void __fastcall Func_0054767B(void* self, int)
{
    *(int*)((char*)self + 0x110) = g_vtbl_0054CA00;
}

/* 0x0043F65D (7B) - getter [ecx+0x1F8]
 * 8b 81 f8 01 00 00 c3 */
__declspec(noinline) int __fastcall Getter_0043F65D(void* self, int)
{
    return *(int*)((char*)self + 0x1F8);
}

/* ========================================================================
 * 10B disp8 setters with ret 4 (load param, store to short-offset field)
 * Pattern: 8b 44 24 04 89 41 XX c2 04 00
 * ======================================================================== */

__declspec(noinline) void __fastcall Setter_00402FA0(void* self, int, int v)
{
    *(int*)((char*)self + 0x20) = v;
}

__declspec(noinline) void __fastcall Setter_0043A4B0(void* self, int, int v)
{
    *(int*)((char*)self + 0x44) = v;
}

__declspec(noinline) void __fastcall Setter_00446020(void* self, int, int v)
{
    *(int*)((char*)self + 0x08) = v;
}

__declspec(noinline) void __fastcall Setter_00450550(void* self, int, int v)
{
    *(int*)((char*)self + 0x50) = v;
}

__declspec(noinline) void __fastcall Setter_0051BB40(void* self, int, int v)
{
    *(int*)((char*)self + 0x74) = v;
}

__declspec(noinline) void __fastcall Setter_00530340(void* self, int, int v)
{
    *(int*)((char*)self + 0x04) = v;
}

/* ========================================================================
 * 7B set [ecx] to constant (vtable init / reset)
 * Pattern: c7 01 XX XX XX XX c3
 * ======================================================================== */

/* 0x004BDED0 (7B) - set [ecx] = -1
 * c7 01 ff ff ff ff c3 */
__declspec(noinline) void __fastcall Func_004BDED0(void* self, int)
{
    *(int*)self = -1;
}

/* ========================================================================
 * 8B simple arithmetic return
 * ======================================================================== */

/* 0x0053EDD0 (8B) - return param - 1
 * 8b 44 24 04 48 c2 04 00 */
__declspec(noinline) int __fastcall Func_0053EDD0(void* self, int, int v)
{
    return v - 1;
}

/* ========================================================================
 * 9B float operations
 * ======================================================================== */

/* 0x00532D40 (9B) - negate float field and store to another field
 * d9 41 50 d9 e0 d9 59 18 c3
 * fld [ecx+0x50] / fchs / fstp [ecx+0x18] / ret */
__declspec(noinline) void __fastcall Func_00532D40(void* self, int)
{
    *(float*)((char*)self + 0x18) = -*(float*)((char*)self + 0x50);
}

/* 0x0042FEB0 (10B) - cannot match: original uses mov eax,ecx then [eax+20]=0,
 * modern MSVC directly uses [ecx+20]=0 (saves the mov eax,ecx) */

/* 0x004B73D0 (10B) - disp8 setter [ecx+0x5C]
 * 8b 44 24 04 89 41 5c c2 04 00 */
__declspec(noinline) void __fastcall Setter_004B73D0(void* self, int, int v)
{
    *(int*)((char*)self + 0x5C) = v;
}

/* 0x00436701 (8B) - uses ret instead of ret 4 (non-standard calling convention, skip) */

/* ========================================================================
 * Force-reference table - prevents linker from stripping COMDAT functions
 * that have no callers yet. These are matching decompilation targets.
 * ======================================================================== */

typedef void (*PFN_VOID)(void);
#pragma section(".pal3ref", read)
__declspec(allocate(".pal3ref"))
PFN_VOID g_pal3_force_refs[] = {
    (PFN_VOID)UIWnd_SetPadding1,
    (PFN_VOID)UIWnd_SetField08,
    (PFN_VOID)CCBRoleState_AllReady,
    (PFN_VOID)CCBRoleState_GetFlag243,
    (PFN_VOID)CCBRoleState_GetActionState,
    (PFN_VOID)CCBRoleState_AnyPartyReady,
    (PFN_VOID)SoundMgr_CompareNames,
    (PFN_VOID)GRPinput_SetField20,
    (PFN_VOID)UICtrl_SetField44,
    (PFN_VOID)GameCtrl_SetField50,
    (PFN_VOID)CombatObj_SetField5C,
    (PFN_VOID)CCBLineup_SetPage,
    (PFN_VOID)Resource_SetField04,
    (PFN_VOID)Setter_0041D5B0,
    (PFN_VOID)Setter_0041D5C0,
    (PFN_VOID)Setter_0043A0E0,
    (PFN_VOID)Setter_0043A680,
    (PFN_VOID)Setter_0043F640,
    (PFN_VOID)Setter_0043F690,
    (PFN_VOID)Setter_004421F0,
    (PFN_VOID)Setter_00442C80,
    (PFN_VOID)Setter_00445910,
    (PFN_VOID)Setter_00449980,
    (PFN_VOID)Setter_00455190,
    (PFN_VOID)Setter_004B4840,
    (PFN_VOID)Setter_004B4910,
    (PFN_VOID)Setter_004BB180,
    (PFN_VOID)Setter_004BC7E0,
    (PFN_VOID)Setter_0051F070,
    (PFN_VOID)Setter_0051F080,
    (PFN_VOID)Setter_0051F090,
    (PFN_VOID)Setter_00524960,
    (PFN_VOID)Setter_0052F300,
    (PFN_VOID)Setter_0052FBA0,
    (PFN_VOID)Setter_00530990,
    (PFN_VOID)Setter_005322D0,
    (PFN_VOID)Setter_005322E0,
    (PFN_VOID)Setter_0053CDD0,
    (PFN_VOID)Getter_0044AB00,
    (PFN_VOID)Getter_004503C0,
    (PFN_VOID)Getter_004B7020,
    (PFN_VOID)Getter_004BDF60,
    (PFN_VOID)Getter_004DC5B0,
    (PFN_VOID)Getter_004FE540,
    (PFN_VOID)Getter_0051AC30,
    (PFN_VOID)Getter_0044FF60,
    (PFN_VOID)Getter_00451730,
    (PFN_VOID)Getter_00479040,
    (PFN_VOID)Getter_004790F0,
    (PFN_VOID)Getter_004791A0,
    (PFN_VOID)Getter_00479250,
    (PFN_VOID)Getter_004F3420,
    (PFN_VOID)Getter_00525080,
    (PFN_VOID)Getter_0053E500,
    (PFN_VOID)Func_00407D40,
    (PFN_VOID)Func_004126F9,
    (PFN_VOID)Func_004126FF,
    (PFN_VOID)Func_0041EB66,
    (PFN_VOID)Func_0041EB6C,
    (PFN_VOID)Func_0041EB72,
    (PFN_VOID)Func_0042C024,
    (PFN_VOID)Func_00434CD8,
    (PFN_VOID)Func_00434F75,
    (PFN_VOID)Func_00434F7B,
    (PFN_VOID)Func_0053833E,
    (PFN_VOID)Func_004B73E0,
    (PFN_VOID)Func_004DF381,
    (PFN_VOID)Func_004DF389,
    (PFN_VOID)Func_004DF391,
    (PFN_VOID)Func_004DF399,
    (PFN_VOID)Func_004DF3A1,
    (PFN_VOID)Func_004DF3A9,
    (PFN_VOID)Func_004F3C0F,
    (PFN_VOID)Func_004F3C17,
    (PFN_VOID)Func_004FA6B1,
    (PFN_VOID)Func_004FA6B9,
    (PFN_VOID)Func_004FA6C1,
    (PFN_VOID)Func_004FA6C9,
    (PFN_VOID)Func_004FA6D1,
    (PFN_VOID)Func_004FA711,
    (PFN_VOID)Func_004FA719,
    (PFN_VOID)Func_004FA721,
    (PFN_VOID)Func_0047E536,
    (PFN_VOID)Func_004B3A25,
    (PFN_VOID)Func_005329BE,
    (PFN_VOID)Func_004E114F,
    (PFN_VOID)Func_00445F73,
    (PFN_VOID)Func_00479075,
    (PFN_VOID)Func_00479121,
    (PFN_VOID)Func_004791D2,
    (PFN_VOID)Func_0047927F,
    (PFN_VOID)Func_004CA447,
    (PFN_VOID)Func_004D364D,
    (PFN_VOID)Func_004FA6D9,
    (PFN_VOID)Func_004FA739,
    (PFN_VOID)Func_004014E0,
    (PFN_VOID)Func_00418DB8,
    (PFN_VOID)Func_0043A40F,
    (PFN_VOID)Func_00445D10,
    (PFN_VOID)Func_004E110C,
    (PFN_VOID)Func_004E1134,
    (PFN_VOID)Func_004E2471,
    (PFN_VOID)FloatGetter_0052E8FB,
    (PFN_VOID)FloatGetter_0052E97B,
    (PFN_VOID)FloatGetter_0052E9FB,
    (PFN_VOID)FloatGetter_0052EA7B,
    (PFN_VOID)FloatGetter_00534CA5,
    (PFN_VOID)Func_0055910B,
    (PFN_VOID)Func_00559111,
    (PFN_VOID)Func_00559117,
    (PFN_VOID)Func_0055911D,
    (PFN_VOID)Func_00416545,
    (PFN_VOID)Func_0041CBE3,
    (PFN_VOID)Func_004235F8,
    (PFN_VOID)Func_0042C1B7,
    (PFN_VOID)Func_00434D33,
    (PFN_VOID)Func_0052F346,
    (PFN_VOID)Func_0053D2E4,
    (PFN_VOID)Func_00555860,
    (PFN_VOID)Func_00556514,
    (PFN_VOID)Func_005579A5,
    (PFN_VOID)Func_00408BC0,
    (PFN_VOID)Func_004BDEC0,
    (PFN_VOID)Func_004BDEC4,
    (PFN_VOID)Func_00469D40,
    (PFN_VOID)Func_004B4830,
    (PFN_VOID)Func_0042AF96,
    (PFN_VOID)Func_004531F0,
    (PFN_VOID)Func_00444D20,
    (PFN_VOID)Func_0041D898,
    (PFN_VOID)Func_0044F8B6,
    (PFN_VOID)Func_0044F8BF,
    (PFN_VOID)Func_0050A8E0,
    (PFN_VOID)Func_004A1CF0,
    (PFN_VOID)Func_0042FB40,
    (PFN_VOID)Func_0044DB50,
    (PFN_VOID)Func_00420F50,
    (PFN_VOID)Func_0041C190,
    (PFN_VOID)Func_004D5F20,
    (PFN_VOID)Func_00431C00,
    (PFN_VOID)Func_00532D30,
    (PFN_VOID)Func_00532D50,
    (PFN_VOID)Func_0054767B,
    (PFN_VOID)Getter_0043F65D,
    (PFN_VOID)Setter_00402FA0,
    (PFN_VOID)Setter_0043A4B0,
    (PFN_VOID)Setter_00446020,
    (PFN_VOID)Setter_00450550,
    (PFN_VOID)Setter_0051BB40,
    (PFN_VOID)Setter_00530340,
    (PFN_VOID)Func_004BDED0,
    (PFN_VOID)Func_0053EDD0,
    (PFN_VOID)Func_00532D40,
    (PFN_VOID)Setter_004B73D0,
};

#pragma comment(linker, "/include:?GetDataEntry@SceneMgrData@@QAEPAXH@Z")
#pragma comment(linker, "/include:?Clear@ZeroInit16@@QAEXXZ")
#pragma comment(linker, "/include:?GetCount@VectorCountObj@@QAEHXZ")
#pragma comment(linker, "/include:?GetAt@ArrayObj@@QAEHH@Z")
#pragma comment(linker, "/include:?SetRepeatDelay@GRPinput@@QAEXH@Z")
