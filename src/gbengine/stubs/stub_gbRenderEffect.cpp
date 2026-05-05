#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbRenderEffect::gbRenderEffect(ID3DXEffect * p1, unsigned int p2) {}

gbRenderEffect::~gbRenderEffect() {}

gbRenderEffect::gbRenderEffect(gbRenderEffect const & p1) {}

gbRenderEffect & gbRenderEffect::operator=(gbRenderEffect const & p1) { static gbRenderEffect _d; return _d; }

int gbRenderEffect::Begin() { return 0; }

int gbRenderEffect::Compare(gbRenderEffect * p1) { return 0; }

int gbRenderEffect::Validate() { return 0; }

ID3DXEffect * gbRenderEffect::GetD3DEffect() { return 0; }

unsigned int gbRenderEffect::GetFlag() { return 0; }

void gbRenderEffect::Apply() { }

void gbRenderEffect::End() { }

void gbRenderEffect::GetVariant(char * p1, void * p2) { }

void gbRenderEffect::GetVariant(GBPARAMHANDLE p1, void * p2) { }

void gbRenderEffect::Pass(int p1) { }

void gbRenderEffect::SetDeclHandle(IDirect3DVertexDeclaration9 * p1) { }

void gbRenderEffect::SetVariant(char * p1, void * p2) { }

void gbRenderEffect::SetVariant(GBPARAMHANDLE p1, void * p2) { }

