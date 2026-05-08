/**
 * gbengine.dll - gbVertPoolMgr
 * Vertex pool manager - additional implementation
 */

#include "gbengine/gbMesh.h"

// 0x100212A0 (58B) - Find or allocate a slot in the FVF array for the given fvf value
int gbVertPoolMgr::FindVertexPoolIndex(unsigned int* fvfArray, unsigned int fvf)
{
    int result;

    // First pass: search for existing matching entry
    result = 0;
    for (unsigned int* p = fvfArray; *p != fvf; p++) {
        if (++result >= 32) {
            // Not found - second pass: find empty slot
            result = 0;
            for (unsigned int* q = fvfArray; *q; q++) {
                if (++result >= 32) {
                    return -1;
                }
            }
            fvfArray[result] = fvf;
            return result;
        }
    }
    return result;
}

