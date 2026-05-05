#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbEffectMgr::gbEffectMgr(gbEffectMgr const & p1) {}

gbEffectMgr::gbEffectMgr() {}

gbEffectMgr::~gbEffectMgr() {}

gbEffectMgr & gbEffectMgr::operator=(gbEffectMgr const & p1) { static gbEffectMgr _d; return _d; }

gbRenderEffect * gbEffectMgr::GetDefaultEffect() { return 0; }

gbRenderEffect * gbEffectMgr::GetRenderEffect(unsigned int p1) { return 0; }

gbRenderEffect * gbEffectMgr::NewRenderEffect(char const * p1, unsigned int p2) { return 0; }

gbRenderEffect * gbEffectMgr::NewTrivalEffect(int p1) { return 0; }

gbTexture * gbEffectMgr::GetGrayTexture() { return 0; }

gbTexture * gbEffectMgr::GetWhiteTexture() { return 0; }

int gbEffectMgr::OnLostDevice() { return 0; }

int gbEffectMgr::OnResetDevice() { return 0; }

IDirect3DVertexDeclaration9 * gbEffectMgr::RegisterVertexFormat(char const * p1, gbVertexElement * p2) { return 0; }

void gbEffectMgr::Init(gbGfxManager * p1) { }

void gbEffectMgr::Release() { }

