/**
 * gbengine.dll - gbBaseMesh and gbStaticMesh
 * Mesh base class and static mesh implementation
 */

#include "gbengine/gbMesh.h"
#include <string.h>

gbMeshType gbBaseMesh::GetMeshType() {
    return m_meshType;
}

gbAABBox* gbBaseMesh::GetAABBox() {
    return &m_aabb;
}

void gbBaseMesh::RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo) {
    (void)0;
}

