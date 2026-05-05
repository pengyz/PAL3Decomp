#include "gbengine/gbChain.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbChain2D::gbChain2D() {}

gbChain2D::~gbChain2D() {}

bool gbChain2D::IsContainNode(gbChain2DNode * p1) { return false; }

gbChain2D & gbChain2D::operator=(gbChain2D const & p1) { static gbChain2D _d; return _d; }

gbChain2DNode * gbChain2D::BeginIterate(int p1) { return 0; }

gbChain2DNode * gbChain2D::Iterate() { return 0; }

int gbChain2D::GetNumNode() { return 0; }

void gbChain2D::AddNode(gbChain2DNode * p1) { }

void gbChain2D::DelNodeFromChain(gbChain2DNode * p1) { }

