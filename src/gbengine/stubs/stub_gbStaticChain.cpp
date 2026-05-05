#include "gbengine/gbChain.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbStaticChainNode * gbStaticChain::GetNode(int p1) { return 0; }

gbStaticChain::gbStaticChain() {}

gbStaticChain & gbStaticChain::operator=(gbStaticChain const & p1) { static gbStaticChain _d; return _d; }

gbStaticChainNode * gbStaticChain::BeginIterate() { return 0; }

gbStaticChainNode * gbStaticChain::BeginReverseIterate() { return 0; }

gbStaticChainNode * gbStaticChain::GetNewestNode() { return 0; }

gbStaticChainNode * gbStaticChain::GetOldestNode() { return 0; }

gbStaticChainNode * gbStaticChain::Iterate() { return 0; }

gbStaticChainNode * gbStaticChain::NewOneNode() { return 0; }

gbStaticChainNode * gbStaticChain::ReverseIterate() { return 0; }

void gbStaticChain::DelOneNode(gbStaticChainNode * p1) { }

void gbStaticChain::InitBuffer(int p1, int p2) { }

void gbStaticChain::ReleaseBuffer() { }

