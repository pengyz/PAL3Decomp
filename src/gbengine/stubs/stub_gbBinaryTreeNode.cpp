#include "gbengine/gbChain.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbBinaryTreeNode::gbBinaryTreeNode(gbBinaryTreeNode const & p1) {}

gbBinaryTreeNode::gbBinaryTreeNode() {}

gbBinaryTreeNode & gbBinaryTreeNode::operator=(gbBinaryTreeNode const & p1) { static gbBinaryTreeNode _d; return _d; }

gbBinaryTreeNode * gbBinaryTreeNode::GetFather() { return 0; }

gbBinaryTreeNode * gbBinaryTreeNode::GetLeft() { return 0; }

gbBinaryTreeNode * gbBinaryTreeNode::GetRight() { return 0; }

gbBinaryTreeNode::~gbBinaryTreeNode() {}

