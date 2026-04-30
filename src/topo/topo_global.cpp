/**
 * topo.dll - Global exported functions
 *
 * Matching decompilation of topo.dll global factory functions.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * These are the DLL's public API entry points for creating/destroying
 * geometry objects (ITopoGeom interface).
 */

#include "pal3.h"

// Forward declarations for internal types
class ITopoGeom;
struct TopoDataDesc;
enum TopoType { TOPO_SIMPLE = 0, TOPO_COMPLEX = 1 };

// Vtable pointers (from .rdata section)
extern void *vtbl_TopoGeomSimple;   // 0x10012154
extern void *vtbl_TopoGeomComplex;  // 0x10012148

// Global instance pointer
static ITopoGeom *g_pTopoGeom = NULL;  // 0x10017f08

// Internal initialization (thiscall) - implemented in topo_internal.cpp
extern int __fastcall TopoGeom_Init(void *pThis, int edx, int *pDesc);

// CRT
extern "C" void *operator new(unsigned int size);
extern "C" void operator delete(void *p);

// ============================================================================
// 0x100034B0  CreateTopoGeom  (185 bytes)
// class ITopoGeom * __cdecl CreateTopoGeom(struct TopoDataDesc *,enum TopoType)
//
// Factory: allocates and initializes a TopoGeom object based on type.
// Type 0 = simple (0x18 bytes), Type 1 = complex (0x2C bytes).
// ============================================================================
ITopoGeom *__cdecl CreateTopoGeom(TopoDataDesc *pDesc, TopoType type)
{
    ITopoGeom *pObj;

    if (type == TOPO_SIMPLE) {
        pObj = (ITopoGeom *)operator new(0x18);
        if (pObj != NULL) {
            *((int *)pObj + 2) = 0;
            *((int *)pObj + 3) = 0;
            *((int *)pObj + 4) = 0;
            *((char *)pObj + 4) = (char)type;
            *(void **)pObj = &vtbl_TopoGeomSimple;
            TopoGeom_Init(pObj, 0, (int *)pDesc);
            return pObj;
        }
    } else if (type == TOPO_COMPLEX) {
        pObj = (ITopoGeom *)operator new(0x2C);
        if (pObj != NULL) {
            *((char *)pObj + 4) = (char)type;
            *((int *)pObj + 2) = 0;
            *((int *)pObj + 3) = 0;
            *((int *)pObj + 4) = 0;
            *((int *)pObj + 7) = 0;
            *((int *)pObj + 8) = 0;
            *((int *)pObj + 9) = 0;
            *((char *)pObj + 0x18) = (char)type;
            *(void **)pObj = &vtbl_TopoGeomComplex;
            g_pTopoGeom = pObj;
            TopoGeom_Init(pObj, 0, (int *)pDesc);
            return pObj;
        }
    } else {
        // Unknown type: treat 'type' as an existing object pointer, re-init
        TopoGeom_Init((void *)type, 0, (int *)pDesc);
        return (ITopoGeom *)type;
    }

    // Allocation failed
    TopoGeom_Init(NULL, 0, (int *)pDesc);
    return NULL;
}

// ============================================================================
// 0x10003570  DestroyTopoGeom  (12 bytes)
// int __cdecl DestroyTopoGeom(class ITopoGeom *)
//
// Frees a TopoGeom object.
// ============================================================================
int __cdecl DestroyTopoGeom(ITopoGeom *pObj)
{
    operator delete(pObj);
    return 0;
}
