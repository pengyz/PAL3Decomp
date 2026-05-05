#include "gbengine/gbChain.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbNBTreeNode::gbNBTreeNode(gbNBTreeNode const & p1) {}

gbChain1D & gbNBTreeNode::GetChildren() { static gbChain1D _d; return _d; }

gbNBTreeNode & gbNBTreeNode::operator=(gbNBTreeNode const & p1) { static gbNBTreeNode _d; return _d; }

gbNBTreeNode * gbNBTreeNode::BeginIterateChild() { return 0; }

gbNBTreeNode * gbNBTreeNode::GetChild(int p1) { return 0; }

gbNBTreeNode * gbNBTreeNode::GetFather() { return 0; }

gbNBTreeNode * gbNBTreeNode::IterateChild() { return 0; }

int gbNBTreeNode::GetNumChildren() { return 0; }

int gbNBTreeNode::IsChild(gbNBTreeNode * p1) { return 0; }

void gbNBTreeNode::AddChild(gbNBTreeNode * p1) { }

void gbNBTreeNode::AddChildOnHead(gbNBTreeNode * p1) { }

void gbNBTreeNode::AddChildOnTail(gbNBTreeNode * p1) { }

void gbNBTreeNode::DelChildFromChain(gbNBTreeNode * p1) { }

