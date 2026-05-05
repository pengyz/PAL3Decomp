#include "gbengine/gbChain.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

bool gbChain1D::IsContainNode(gbChain1DNode * p1) { return false; }

gbChain1D & gbChain1D::operator=(gbChain1D const & p1) { static gbChain1D _d; return _d; }

gbChain1DNode * gbChain1D::BeginIterate() { return 0; }

gbChain1DNode * gbChain1D::Iterate() { return 0; }

gbChain1DNode * gbChain1D::operator[](int p1) { return 0; }

int gbChain1D::GetNumNode() { return 0; }

void gbChain1D::AddNodeOnHead(gbChain1DNode * p1) { }

void gbChain1D::AddNodeOnTail(gbChain1DNode * p1) { }

void gbChain1D::ClearAllNodePtr() { }

void gbChain1D::InsertBefore(gbChain1DNode * p1, gbChain1DNode * p2) { }

