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
    if (this->m_bFocusable != 0) {
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
int C2DSpark::CreateSingle(void* sparkData)
{
    char* base = (char*)this;

    for (unsigned int i = 0; i < 0x200; i++) {
        char* slot = base + i * 0x2C;
        if (*(slot + 0x29) == 0) {
            memcpy(slot, sparkData, 0x2C);
            *(slot + 0x29) = 1;
            if ((int)i >= this->nHighWaterMark) {
                this->nHighWaterMark = i + 1;
            }
            return 1;
        }
    }
    return 0;
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
