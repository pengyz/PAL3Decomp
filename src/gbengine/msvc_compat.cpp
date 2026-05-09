#if _MSC_VER >= 1900

#include "gbengine/gbMesh.h"

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
