/**
 * gbengine.dll - gbBaseMesh and gbStaticMesh
 * Mesh base class and static mesh implementation
 */

#include "gbengine/gbMesh.h"
#include <string.h>

void gbBaseMesh::Release(void) {
    if (--m_refCount <= 0)
        delete this;
}

gbMeshType gbBaseMesh::GetMeshType() {
    return MESH_STATIC;
}

gbAABBox* gbBaseMesh::GetAABBox() {
    return &m_aabb;
}

void gbBaseMesh::RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo) {
    (void)0;
}

void gbBaseMesh::DrawSubSetBase(int index, void* renderInfo) {
    (void)0;
}

