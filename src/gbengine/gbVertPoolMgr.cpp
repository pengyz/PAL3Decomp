/**
 * gbengine.dll - gbVertPoolMgr
 * Vertex pool manager - additional implementation
 */

#include "gbengine/gbMesh.h"

// Find which vertex pool index contains the given FVF
int gbVertPoolMgr::FindVertexPoolIndex(unsigned int* pFVF, unsigned int fvf) {
    for (int i = 0; i < 32; i++) {
        if (vertexPools[i] && vertexPools[i]->fvf == fvf) {
            if (pFVF) *pFVF = fvf;
            return i;
        }
    }

    // Not found - return first available slot
    for (int i = 0; i < 32; i++) {
        if (!vertexPools[i]) {
            if (pFVF) *pFVF = 0;
            return i;
        }
    }

    // No slots available
    if (pFVF) *pFVF = 0;
    return -1;
}
