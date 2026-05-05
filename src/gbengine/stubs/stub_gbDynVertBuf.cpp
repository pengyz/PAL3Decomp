#include "gbengine/gbMesh.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbDynVertBuf::gbDynVertBuf(unsigned int p1, int p2) {}

gbDynVertBuf & gbDynVertBuf::operator=(gbDynVertBuf const & p1) { static gbDynVertBuf _d; return _d; }

float * gbDynVertBuf::GetNormal() { return 0; }

float * gbDynVertBuf::GetXYZ() { return 0; }

int gbDynVertBuf::GetVertNum() { return 0; }

int gbDynVertBuf::GetVertexStride() { return 0; }

gbGfxManager * gbDynVertBuf::pGfxMgr;

gbColorQuad * gbDynVertBuf::GetColor1() { return 0; }

gbColorQuad * gbDynVertBuf::GetColor2() { return 0; }

gbDynVertBuf::~gbDynVertBuf() {}

void gbDynVertBuf::RenderGeomQuad(gbGeomQuad * p1, int p2, gbRenderEffect * p3, gbTextureArray * p4) { }

void gbDynVertBuf::RenderGeomQuadViaStrip(gbGeomQuad * p1, int p2, gbRenderEffect * p3, gbTextureArray * p4) { }

void gbDynVertBuf::RenderGeomQuadViaStrip(gbGeomQuad * p1, int p2, gbRenderEffect * p3, gbTextureArray * p4, unsigned long p5) { }

void gbDynVertBuf::RenderLineStrip(gbColorQuad p1, gbVec3D * p2, int p3, gbRenderEffect * p4) { }

void gbDynVertBuf::RenderUIQuad(gbUIQuad * p1, int p2, gbRenderEffect * p3, gbTextureArray * p4) { }

