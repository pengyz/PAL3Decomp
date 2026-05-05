#include "gbengine/gbChain.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbNBTree::gbNBTree() {}

gbNBTree::~gbNBTree() {}

gbNBTree & gbNBTree::operator=(gbNBTree const & p1) { static gbNBTree _d; return _d; }

gbNBTreeNode * gbNBTree::GetRoot() { return 0; }

void gbNBTree::SetRoot(gbNBTreeNode * p1) { }

