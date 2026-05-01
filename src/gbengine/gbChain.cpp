/**
 * gbengine.dll - gbChain
 * Linked lists, trees, and static chain implementations
 * Functions: 41
 */

#include "gbengine/gbChain.h"
#include <stdlib.h>
#include <string.h>


/* ================================================================
 * Implementation: gbChain1DNode
 * ================================================================ */

gbChain1DNode::gbChain1DNode(void) {
    pNext = NULL;
}

gbChain1DNode::gbChain1DNode(const gbChain1DNode& src) {
    pNext = src.pNext;
}

gbChain1DNode::~gbChain1DNode() {
}

gbChain1DNode& gbChain1DNode::operator=(const gbChain1DNode& other) {
    if (this != &other) {
        pNext = other.pNext;
    }
    return *this;
}


/* ================================================================
 * Implementation: gbChain1D
 * ================================================================ */

gbChain1D::gbChain1D(void) {
    pHead = NULL;
    pTail = NULL;
    nCount = 0;
    pIterator = NULL;
}

gbChain1D::~gbChain1D() {
}

gbChain1D& gbChain1D::operator=(const gbChain1D& other) {
    if (this != &other) {
        pHead = other.pHead;
        pTail = other.pTail;
        nCount = other.nCount;
        pIterator = other.pIterator;
    }
    return *this;
}

void gbChain1D::ClearAllNodePtr(void) {
    pTail = NULL;
    pHead = NULL;
    nCount = 0;
    pIterator = NULL;
}

void gbChain1D::AddNodeOnHead(gbChain1DNode* node) {
    if (!node) return;
    node->pNext = pHead;
    pHead = node;
    if (!pTail) {
        pTail = node;
    }
    nCount++;
}

void gbChain1D::AddNodeOnTail(gbChain1DNode* node) {
    AddNode(node);
}

void gbChain1D::AddNode(gbChain1DNode* node) {
    if (!node) return;
    node->pNext = NULL;
    if (!pTail) {
        pTail = node;
        pHead = node;
    } else {
        pTail->pNext = node;
        pTail = node;
    }
    nCount++;
}

void gbChain1D::InsertBefore(gbChain1DNode* newNode, gbChain1DNode* beforeNode) {
    if (!newNode) return;

    if (!beforeNode || beforeNode == pHead) {
        AddNodeOnHead(newNode);
        return;
    }

    // Find node preceding beforeNode
    gbChain1DNode* prev = pHead;
    while (prev && prev->pNext != beforeNode) {
        prev = prev->pNext;
    }

    if (prev) {
        newNode->pNext = beforeNode;
        prev->pNext = newNode;
        nCount++;
    }
}

void gbChain1D::InsertAfter(gbChain1DNode* newNode, gbChain1DNode* afterNode) {
    if (!newNode) return;

    if (!afterNode) {
        AddNodeOnHead(newNode);
        return;
    }

    newNode->pNext = afterNode->pNext;
    afterNode->pNext = newNode;
    if (afterNode == pTail) {
        pTail = newNode;
    }
    nCount++;
}

void gbChain1D::DelNodeFromChain(gbChain1DNode* node) {
    if (!node) return;

    if (node == pHead) {
        pHead = node->pNext;
        if (!pHead) {
            pTail = NULL;
        }
        nCount--;
        return;
    }

    // Find previous node
    gbChain1DNode* prev = pHead;
    while (prev && prev->pNext != node) {
        prev = prev->pNext;
    }

    if (prev) {
        prev->pNext = node->pNext;
        if (node == pTail) {
            pTail = prev;
        }
        nCount--;
    }
}

bool gbChain1D::IsContainNode(gbChain1DNode* node) {
    gbChain1DNode* curr = pHead;
    while (curr) {
        if (curr == node) {
            return true;
        }
        curr = curr->pNext;
    }
    return false;
}

int gbChain1D::GetNumNode(void) {
    return nCount;
}

gbChain1DNode* gbChain1D::BeginIterate(void) {
    pIterator = pHead;
    return pIterator;
}

gbChain1DNode* gbChain1D::Iterate(void) {
    if (pIterator) {
        pIterator = pIterator->pNext;
    }
    return pIterator;
}

gbChain1DNode* gbChain1D::operator[](int index) {
    if (index < 0 || index >= nCount) return NULL;
    gbChain1DNode* node = pHead;
    for (int i = 0; i < index && node; i++) {
        node = node->pNext;
    }
    return node;
}


/* ================================================================
 * Implementation: gbChain2DNode
 * ================================================================ */

gbChain2DNode::gbChain2DNode(void) {
    pPrev = NULL;
    pNext = NULL;
}

gbChain2DNode::gbChain2DNode(const gbChain2DNode& src) {
    pPrev = src.pPrev;
    pNext = src.pNext;
}

gbChain2DNode::~gbChain2DNode() {
}

gbChain2DNode& gbChain2DNode::operator=(const gbChain2DNode& other) {
    if (this != &other) {
        pPrev = other.pPrev;
        pNext = other.pNext;
    }
    return *this;
}


/* ================================================================
 * Implementation: gbChain2D
 * ================================================================ */

gbChain2D::gbChain2D(void) {
    pHead = NULL;
    pTail = NULL;
    nDirection = 0;
    nCount = 0;
    pIterator = NULL;
}

gbChain2D::~gbChain2D() {
}

gbChain2D& gbChain2D::operator=(const gbChain2D& other) {
    if (this != &other) {
        pHead = other.pHead;
        pTail = other.pTail;
        nDirection = other.nDirection;
        nCount = other.nCount;
        pIterator = other.pIterator;
    }
    return *this;
}

void gbChain2D::AddNode(gbChain2DNode* node) {
    if (!node) return;
    node->pNext = NULL;
    node->pPrev = NULL;
    if (!pTail) {
        pHead = node;
        pTail = node;
    } else {
        pTail->pNext = node;
        node->pPrev = pTail;
        pTail = node;
    }
    nCount++;
}

void gbChain2D::DelNodeFromChain(gbChain2DNode* node) {
    if (!node) return;

    if (node->pPrev) {
        node->pPrev->pNext = node->pNext;
    } else {
        pHead = node->pNext;
    }

    if (node->pNext) {
        node->pNext->pPrev = node->pPrev;
    } else {
        pTail = node->pPrev;
    }

    nCount--;
}

bool gbChain2D::IsContainNode(gbChain2DNode* node) {
    gbChain2DNode* curr = pHead;
    while (curr) {
        if (curr == node) {
            return true;
        }
        curr = curr->pNext;
    }
    return false;
}

int gbChain2D::GetNumNode(void) {
    return nCount;
}

gbChain2DNode* gbChain2D::BeginIterate(int dir) {
    nDirection = dir;
    if (dir == 0) {
        pIterator = pHead;
    } else {
        pIterator = pTail;
    }
    return pIterator;
}

gbChain2DNode* gbChain2D::Iterate(void) {
    if (pIterator) {
        if (nDirection == 0) {
            pIterator = pIterator->pNext;
        } else {
            pIterator = pIterator->pPrev;
        }
    }
    return pIterator;
}


/* ================================================================
 * Implementation: gbNBTreeNode
 * ================================================================ */

gbNBTreeNode::gbNBTreeNode(void) : gbChain1DNode() {
    pParent = NULL;
    pChildIterator = NULL;
}

gbNBTreeNode::gbNBTreeNode(const gbNBTreeNode& src) : gbChain1DNode(src) {
    pParent = src.pParent;
    children = src.children;
    pChildIterator = src.pChildIterator;
}

gbNBTreeNode::~gbNBTreeNode() {
}

gbNBTreeNode& gbNBTreeNode::operator=(const gbNBTreeNode& other) {
    if (this != &other) {
        gbChain1DNode::operator=(other);
        pParent = other.pParent;
        children = other.children;
        pChildIterator = other.pChildIterator;
    }
    return *this;
}

void gbNBTreeNode::AddChildOnHead(gbNBTreeNode* child) {
    if (!child) return;
    children.AddNodeOnHead((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::AddChildOnTail(gbNBTreeNode* child) {
    if (!child) return;
    children.AddNode((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::AddChild(gbNBTreeNode* child) {
    if (!child) return;
    children.AddNode((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::DelChildFromChain(gbNBTreeNode* child) {
    if (!child) return;
    children.DelNodeFromChain((gbChain1DNode*)child);
}

int gbNBTreeNode::IsChild(gbNBTreeNode* child) {
    return children.IsContainNode((gbChain1DNode*)child);
}

int gbNBTreeNode::GetNumChildren(void) {
    return children.GetNumNode();
}

gbChain1D& gbNBTreeNode::GetChildren(void) {
    return children;
}

gbNBTreeNode* gbNBTreeNode::GetFather(void) {
    return pParent;
}

gbNBTreeNode* gbNBTreeNode::BeginIterateChild(void) {
    pChildIterator = (gbNBTreeNode*)children.pHead;
    return pChildIterator;
}

gbNBTreeNode* gbNBTreeNode::IterateChild(void) {
    if (pChildIterator) {
        pChildIterator = (gbNBTreeNode*)pChildIterator->pNext;
    }
    return pChildIterator;
}

gbNBTreeNode* gbNBTreeNode::GetChild(int index) {
    if (index < 0 || index >= children.nCount) {
        return NULL;
    }
    gbChain1DNode* node = children.pHead;
    for (int i = 0; i < index && node; i++) {
        node = node->pNext;
    }
    return (gbNBTreeNode*)node;
}


/* ================================================================
 * Implementation: gbNBTree
 * ================================================================ */

gbNBTree::gbNBTree(void) {
    pRoot = NULL;
}

gbNBTree::~gbNBTree() {
}

gbNBTree& gbNBTree::operator=(const gbNBTree& other) {
    if (this != &other) {
        pRoot = other.pRoot;
    }
    return *this;
}

void gbNBTree::SetRoot(gbNBTreeNode* node) {
    pRoot = node;
}

gbNBTreeNode* gbNBTree::GetRoot(void) {
    return pRoot;
}


/* ================================================================
 * Implementation: gbBinaryTreeNode
 * ================================================================ */

gbBinaryTreeNode::gbBinaryTreeNode(void) {
    pLeft = NULL;
    pRight = NULL;
    pParent = NULL;
}

gbBinaryTreeNode::gbBinaryTreeNode(const gbBinaryTreeNode& src) {
    pLeft = src.pLeft;
    pRight = src.pRight;
    pParent = src.pParent;
}

gbBinaryTreeNode::~gbBinaryTreeNode() {
}

gbBinaryTreeNode& gbBinaryTreeNode::operator=(const gbBinaryTreeNode& other) {
    if (this != &other) {
        pLeft = other.pLeft;
        pRight = other.pRight;
        pParent = other.pParent;
    }
    return *this;
}

gbBinaryTreeNode* gbBinaryTreeNode::GetFather(void) {
    return pParent;
}

gbBinaryTreeNode* gbBinaryTreeNode::GetLeft(void) {
    return pLeft;
}

gbBinaryTreeNode* gbBinaryTreeNode::GetRight(void) {
    return pRight;
}


/* ================================================================
 * Implementation: gbBinaryTree
 * ================================================================ */

gbBinaryTree::gbBinaryTree(void) {
    pRoot = NULL;
}

gbBinaryTree::~gbBinaryTree() {
}

gbBinaryTree& gbBinaryTree::operator=(const gbBinaryTree& other) {
    if (this != &other) {
        pRoot = other.pRoot;
    }
    return *this;
}

void gbBinaryTree::SetRoot(gbBinaryTreeNode* node) {
    pRoot = node;
}

gbBinaryTreeNode* gbBinaryTree::GetRoot(void) {
    return pRoot;
}


/* ================================================================
 * Implementation: gbStaticChain
 * ================================================================ */

gbStaticChain::gbStaticChain(void) {
    pBuffer = NULL;
    pFreeHead = NULL;
    pUsedHead = NULL;
    pIterator = NULL;
    nMaxNodes = 0;
    nNodeSize = 0;
    nUsedCount = 0;
}

gbStaticChain& gbStaticChain::operator=(const gbStaticChain& other) {
    if (this != &other) {
        pBuffer = other.pBuffer;
        pFreeHead = other.pFreeHead;
        pUsedHead = other.pUsedHead;
        pIterator = other.pIterator;
        nMaxNodes = other.nMaxNodes;
        nNodeSize = other.nNodeSize;
        nUsedCount = other.nUsedCount;
    }
    return *this;
}

void gbStaticChain::InitBuffer(int maxNodes, int nodeSize) {
    if (maxNodes <= 0 || nodeSize <= 0) return;

    nMaxNodes = maxNodes;
    nNodeSize = nodeSize;
    nUsedCount = 0;

    // Allocate buffer
    pBuffer = malloc(maxNodes * nodeSize);
    if (!pBuffer) return;

    // Link all nodes into free list
    pFreeHead = NULL;
    char* ptr = (char*)pBuffer;
    for (int i = 0; i < maxNodes; i++) {
        gbStaticChainNode* node = (gbStaticChainNode*)ptr;
        node->pPrev = NULL;
        node->pNext = pFreeHead;
        if (pFreeHead) {
            pFreeHead->pPrev = node;
        }
        pFreeHead = node;
        ptr += nodeSize;
    }

    pUsedHead = NULL;
    pIterator = NULL;
}

void gbStaticChain::ReleaseBuffer(void) {
    if (pBuffer) {
        free(pBuffer);
        pBuffer = NULL;
    }
    pFreeHead = NULL;
    pUsedHead = NULL;
    pIterator = NULL;
}

gbStaticChainNode* gbStaticChain::NewOneNode(void) {
    if (!pFreeHead) return NULL;

    // Pop from free list
    gbStaticChainNode* node = pFreeHead;
    pFreeHead = node->pNext;
    if (pFreeHead) {
        pFreeHead->pPrev = NULL;
    }

    // Push to used list (add to head)
    node->pNext = pUsedHead;
    node->pPrev = NULL;
    if (pUsedHead) {
        pUsedHead->pPrev = node;
    }
    pUsedHead = node;

    nUsedCount++;
    return node;
}

void gbStaticChain::DelOneNode(gbStaticChainNode* ptr) {
    if (!ptr) return;
    gbStaticChainNode* node = ptr;

    // Remove from used list
    if (node->pPrev) {
        node->pPrev->pNext = node->pNext;
    } else {
        pUsedHead = node->pNext;
    }
    if (node->pNext) {
        node->pNext->pPrev = node->pPrev;
    }

    // Add to free list (add to head)
    node->pNext = pFreeHead;
    node->pPrev = NULL;
    if (pFreeHead) {
        pFreeHead->pPrev = node;
    }
    pFreeHead = node;

    nUsedCount--;
}

gbStaticChainNode* gbStaticChain::BeginIterate(void) {
    pIterator = pUsedHead;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::Iterate(void) {
    if (pIterator) {
        pIterator = pIterator->pNext;
    }
    return pIterator;
}

gbStaticChainNode* gbStaticChain::BeginReverseIterate(void) {
    pIterator = pUsedHead;
    if (!pIterator) return NULL;

    // Walk to end of used list
    while (pIterator->pNext) {
        pIterator = pIterator->pNext;
    }
    return pIterator;
}

gbStaticChainNode* gbStaticChain::ReverseIterate(void) {
    if (pIterator) {
        pIterator = pIterator->pPrev;
    }
    return pIterator;
}

gbStaticChainNode* gbStaticChain::GetOldestNode(void) {
    if (!pUsedHead) return NULL;

    gbStaticChainNode* node = pUsedHead;
    while (node->pNext) {
        node = node->pNext;
    }
    return node;
}

gbStaticChainNode* gbStaticChain::GetNewestNode(void) {
    return pUsedHead;
}

gbStaticChainNode* gbStaticChain::GetNode(int index) {
    if (index < 0 || index >= nMaxNodes || !pBuffer) {
        return NULL;
    }
    return (gbStaticChainNode*)((char*)pBuffer + nNodeSize * index);
}
