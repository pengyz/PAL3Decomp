#include "gbengine/gbMesh.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

char const * gbBaseMesh::GetObjectName() { return 0; }

gbMeshType gbBaseMesh::GetMeshType() { return 0; }

int gbBaseMesh::GetNumSection() { return 0; }

gbAABBox * gbBaseMesh::GetAABBox() { return 0; }

gbMeshMemCache * gbBaseMesh::GetMemoryCache() { return 0; }

void gbBaseMesh::RenderShadowVolume(gbVisNode * p1, gbRenderInfoObj * p2) { }

void gbBaseMesh::SetCurTime(float p1) { }

