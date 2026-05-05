#include "gbengine/gbMesh.h"
#include <d3d9.h>

// gbIndexBubble::Lock32 - Lock 32-bit index buffer

unsigned int* gbIndexBubble::Lock32() {
    if (!pPool || !pPool->pIndexBuffer) {
        return NULL;
    }

    // Lock the D3D index buffer
    void* pData = NULL;
    HRESULT hr = pPool->pIndexBuffer->Lock(
        startIndex * sizeof(unsigned int),  // Offset in bytes
        count * sizeof(unsigned int),        // Size in bytes
        &pData,
        0                                    // Flags
    );

    if (FAILED(hr)) {
        return NULL;
    }

    return (unsigned int*)pData;
}
