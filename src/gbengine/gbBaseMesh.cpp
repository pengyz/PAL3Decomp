/**
 * gbengine.dll - gbBaseMesh and gbStaticMesh
 * Mesh base class and static mesh implementation
 */

#include "gbengine/gbMesh.h"
#include <string.h>

// ======== gbBaseMesh ========

const char* gbBaseMesh::GetObjectName(void) {
    /* UNCERTAIN: Return mesh name */
    // return pName;
    return NULL;
}

gbMeshType gbBaseMesh::GetMeshType(void) {
    /* UNCERTAIN: Return mesh type enum */
    // return meshType;
    return MESH_STATIC;
}

int gbBaseMesh::GetNumSection(void) {
    /* UNCERTAIN: Return number of mesh sections */
    // return numSections;
    return 0;
}

gbAABBox* gbBaseMesh::GetAABBox(void) {
    /* UNCERTAIN: Return axis-aligned bounding box */
    // return &aabbBox;
    return NULL;
}

gbMeshMemCache* gbBaseMesh::GetMemoryCache(void) {
    /* UNCERTAIN: Return memory cache for mesh data */
    // return pMemCache;
    return NULL;
}

void gbBaseMesh::RenderShadowVolume(gbVisNode* node, gbRenderInfoObj* renderInfo) {
    /* UNCERTAIN: Render shadow volume for this mesh */
    // Would extrude mesh edges to create shadow volume geometry
}

void gbBaseMesh::SetCurTime(float time) {
    /* UNCERTAIN: Set current animation time */
    // curTime = time;
}

// ======== gbStaticMesh ========

gbVertexBubble* gbStaticMesh::GetVertBubble(void) {
    /* UNCERTAIN: Return vertex bubble for static geometry */
    // return pVertBubble;
    return NULL;
}

void gbStaticMesh::RenderShadowVolume(gbVisNode* node, gbRenderInfoObj* renderInfo) {
    /* UNCERTAIN: Render shadow volume for static mesh */
    // Static mesh shadow volume rendering
}
