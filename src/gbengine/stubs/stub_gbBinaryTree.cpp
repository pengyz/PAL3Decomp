#include "gbengine/gbChain.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbBinaryTree::gbBinaryTree() {}

gbBinaryTree::~gbBinaryTree() {}

gbBinaryTree & gbBinaryTree::operator=(gbBinaryTree const & p1) { static gbBinaryTree _d; return _d; }

gbBinaryTreeNode * gbBinaryTree::GetRoot() { return 0; }

void gbBinaryTree::SetRoot(gbBinaryTreeNode * p1) { }

