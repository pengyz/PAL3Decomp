#include "gbengine/gbMesh.h"

// gbMesh methods - declared in header but bodies were missing
gbMesh::gbMesh(gbGfxManager* gfxMgr) : gbBaseMesh(gfxMgr) {
    m_field78 = 0;
    m_pVertBubbles = NULL;
    m_pFrameTimes = NULL;
    m_numVertFrames = 0;
    m_pLODKeys = NULL;
}

gbMesh::~gbMesh() {
    if (m_pVertBubbles) { free(m_pVertBubbles); m_pVertBubbles = NULL; }
    if (m_pFrameTimes) { free(m_pFrameTimes); m_pFrameTimes = NULL; }
    if (m_pLODKeys) { free(m_pLODKeys); m_pLODKeys = NULL; }
}

void gbMesh::DrawSubSet(int index, gbRenderInfoObj* renderInfo) {}
void gbMesh::ComputeShadowVolume() {}
void gbMesh::RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo) {}

#if _MSC_VER >= 1900

// Modern MSVC compatibility stubs for VC6-era CRT symbols

extern "C" {

// __ftol2: float-to-long via x87 FPU (truncation mode)
__declspec(naked) long __cdecl _ftol2(double) {
    __asm {
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        fnstcw  word ptr [ebp-2]
        mov     ax, word ptr [ebp-2]
        or      ax, 0C00h
        mov     word ptr [ebp-4], ax
        fldcw   word ptr [ebp-4]
        fistp   qword ptr [ebp-12]
        fldcw   word ptr [ebp-2]
        mov     eax, dword ptr [ebp-12]
        mov     esp, ebp
        pop     ebp
        ret
    }
}

// __ftol2_sse: same as __ftol2 for our purposes
long __cdecl _ftol2_sse(double v) {
    return (long)v;
}

// eh vector constructor iterator (5-param stdcall version)
void __stdcall __ehvec_ctor(
    void* ptr, unsigned int size, unsigned int count,
    void (__thiscall* ctor)(void*),
    void (__thiscall* dtor)(void*))
{
    unsigned int i = 0;
    __try {
        for (; i < count; i++) {
            ctor(ptr);
            ptr = (char*)ptr + size;
        }
    } __except(1) {
        for (; i > 0; i--) {
            ptr = (char*)ptr - size;
            dtor(ptr);
        }
    }
}

// eh vector destructor iterator (4-param stdcall version)
void __stdcall __ehvec_dtor(
    void* ptr, unsigned int size, unsigned int count,
    void (__thiscall* dtor)(void*))
{
    ptr = (char*)ptr + size * count;
    for (unsigned int i = 0; i < count; i++) {
        ptr = (char*)ptr - size;
        dtor(ptr);
    }
}

} // extern "C"

// Provide the mangled names that the linker expects
#pragma comment(linker, "/alternatename:__ftol2=__ftol2")
#pragma comment(linker, "/alternatename:__ftol2_sse=__ftol2_sse")

#endif // _MSC_VER >= 1900
