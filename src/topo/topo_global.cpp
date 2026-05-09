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
// TODO: implement actual vtables
void *vtbl_TopoGeomSimple = NULL;    // 0x10012154
void *vtbl_TopoGeomComplex = NULL;   // 0x10012148

// Global instance pointer
static ITopoGeom *g_pTopoGeom = NULL;  // 0x10017f08

// Internal initialization (thiscall) - implemented in topo_internal.cpp
extern int __fastcall TopoGeom_Init(void *pThis, int edx, int *pDesc);

// ============================================================================
// 0x100034A0  GetTopoVersion  (8 bytes)
// int __stdcall FUN_100034a0(void)
//
// Returns constant value 1. Possibly a version check or success flag.
// Called by entry point (0x1000a5c4).
// ============================================================================
int __stdcall GetTopoVersion(void)
{
    return 1;
}

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
            struct TopoGeom *pSimple = (struct TopoGeom *)pObj;
            pSimple->faceVector.pBegin = NULL;
            pSimple->faceVector.pEnd = NULL;
            pSimple->faceVector.pAlloc = NULL;
            pSimple->type = type;
            pSimple->vtable = &vtbl_TopoGeomSimple;
            TopoGeom_Init(pObj, 0, (int *)pDesc);
            return pObj;
        }
    } else if (type == TOPO_COMPLEX) {
        pObj = (ITopoGeom *)operator new(0x2C);
        if (pObj != NULL) {
            struct TopoGeomComplex *pComplex = (struct TopoGeomComplex *)pObj;
            pComplex->type = type;
            pComplex->faceVector.pBegin = NULL;
            pComplex->faceVector.pEnd = NULL;
            pComplex->faceVector.pAlloc = NULL;
            pComplex->field_1C = 0;
            pComplex->field_20 = 0;
            pComplex->field_24 = 0;
            pComplex->type2 = type;
            pComplex->vtable = &vtbl_TopoGeomComplex;
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
