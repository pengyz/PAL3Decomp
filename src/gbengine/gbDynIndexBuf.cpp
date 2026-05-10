/**
 * gbengine.dll - gbDynIndexBuf
 * Dynamic index buffer for runtime indexed geometry
 *
 * Addresses: 0x1001C2F0 - 0x1001C3C0
 */

#include "gbengine/gbMesh.h"
#include "gbengine/gbGfxManager_impl.h"
#include <stdlib.h>

// gbDynIndexBuf class definition (not yet in header)
// Layout (from disassembly):
//   +0x00: vtable pointer (if virtual) or field
//   +0x04: field_04
//   +0x08: poolType (int, 2 = malloc/sysmem mode)
//   +0x0C: indexCount
//   +0x10: pBuffer (IDirect3DIndexBuffer9* or malloc'd)
//   +0x14: pData (index data pointer)
class gbDynIndexBuf {
public:
    int field_00;
    int field_04;
    int poolType;                    // +0x08: 2 = system memory (malloc)
    int indexCount;                  // +0x0C
    void* pBuffer;                   // +0x10: IDirect3DIndexBuffer9* or malloc'd buffer
    void* pData;                     // +0x14

    ~gbDynIndexBuf();
    void* Lock(int count);
    void Unlock();
};

// 0x1001C3B0 (16B) - Unlock index buffer (D3D mode only)
void gbDynIndexBuf::Unlock() {
    if (poolType != 2) {
        ((IDirect3DIndexBuffer9*)pBuffer)->Unlock();
    }
}
