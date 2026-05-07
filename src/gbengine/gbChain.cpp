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
}

gbChain1DNode::gbChain1DNode(const gbChain1DNode& src) {
    pNext = src.pNext;
}

gbChain1DNode::~gbChain1DNode() {
}

gbChain1DNode& gbChain1DNode::operator=(const gbChain1DNode& other) {
    pNext = other.pNext;
    return *this;
}


/* ================================================================
 * Implementation: gbChain1D
 * ================================================================ */

gbChain1D::gbChain1D(void) {
    pTail = NULL;
    pHead = NULL;
    nCount = 0;
}

gbChain1D::~gbChain1D() {
    gbChain1DNode* node = pHead;
    while (node) {
        gbChain1DNode* next = node->pNext;
        delete node;
        node = next;
    }
}

gbChain1D& gbChain1D::operator=(const gbChain1D& other) {
    pHead = other.pHead;
    pTail = other.pTail;
    nCount = other.nCount;
    pIterator = other.pIterator;
    return *this;
}

void gbChain1D::ClearAllNodePtr(void) {
    pTail = NULL;
    pHead = NULL;
    nCount = 0;
}

void gbChain1D::AddNodeOnHead(gbChain1DNode* node) {
    node->pNext = pHead;
    gbChain1DNode* v2 = pTail;
    pHead = node;
    if (!v2)
        pTail = node;
    nCount++;
}

void gbChain1D::AddNodeOnTail(gbChain1DNode* node) {
    node->pNext = NULL;
    gbChain1DNode* v2 = pTail;
    if (!v2) {
        pTail = node;
        pHead = node;
    } else {
        v2->pNext = node;
        pTail = node;
    }
    nCount++;
}

void gbChain1D::AddNode(gbChain1DNode* node) {
    node->pNext = NULL;
    gbChain1DNode* v2 = pTail;
    if (!v2) {
        pTail = node;
        pHead = node;
    } else {
        v2->pNext = node;
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
    pIterator = pIterator->pNext;
    return pIterator;
}

gbChain1DNode* gbChain1D::operator[](int index) {
    gbChain1DNode* result = pHead;
    int v3 = 0;
    if (index > 0) {
        while (result) {
            result = result->pNext;
            if (++v3 >= index)
                return result;
        }
        return NULL;
    }
    return result;
}


/* ================================================================
 * Implementation: gbChain2DNode
 * ================================================================ */

gbChain2DNode::gbChain2DNode(void) {
}

gbChain2DNode::gbChain2DNode(const gbChain2DNode& src) {
    pPrev = src.pPrev;
    pNext = src.pNext;
}

gbChain2DNode::~gbChain2DNode() {
}

gbChain2DNode& gbChain2DNode::operator=(const gbChain2DNode& other) {
    pPrev = other.pPrev;
    pNext = other.pNext;
    return *this;
}


/* ================================================================
 * Implementation: gbChain2D
 * ================================================================ */

gbChain2D::gbChain2D(void) {
    pTail = NULL;
    pHead = NULL;
    nCount = 0;
}

gbChain2D::~gbChain2D() {
    gbChain2DNode* node = pHead;
    while (node) {
        gbChain2DNode* next = node->pNext;
        delete node;
        node = next;
    }
}

gbChain2D& gbChain2D::operator=(const gbChain2D& other) {
    memcpy(this, &other, 0x14);
    return *this;
}

void gbChain2D::AddNode(gbChain2DNode* node) {
    node->pNext = NULL;
    node->pPrev = NULL;
    gbChain2DNode* v2 = pTail;
    if (!v2) {
        pTail = node;
        pHead = node;
    } else {
        v2->pNext = node;
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
    gbChain2DNode* result;
    if (!dir) {
        result = pHead;
    } else {
        result = pTail;
    }
    nDirection = dir;
    pIterator = result;
    return result;
}

gbChain2DNode* gbChain2D::Iterate(void) {
    gbChain2DNode* result;
    if (!nDirection) {
        result = pIterator->pNext;
    } else {
        result = pIterator->pPrev;
    }
    pIterator = result;
    return result;
}


/* ================================================================
 * Implementation: gbNBTreeNode
 * ================================================================ */

gbNBTreeNode::gbNBTreeNode(void) : gbChain1DNode() {
    pParent = NULL;
}

gbNBTreeNode::gbNBTreeNode(const gbNBTreeNode& src) : gbChain1DNode(src) {
    pParent = src.pParent;
    children = src.children;
}

gbNBTreeNode::~gbNBTreeNode() {
}

gbNBTreeNode& gbNBTreeNode::operator=(const gbNBTreeNode& other) {
    pNext = other.pNext;
    pParent = other.pParent;
    children = other.children;
    return *this;
}

void gbNBTreeNode::AddChildOnHead(gbNBTreeNode* child) {
    children.AddNodeOnHead((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::AddChildOnTail(gbNBTreeNode* child) {
    children.AddNodeOnTail((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::AddChild(gbNBTreeNode* child) {
    children.AddNode((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::DelChildFromChain(gbNBTreeNode* child) {
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
    children.pIterator = children.pHead;
    return (gbNBTreeNode*)children.pIterator;
}

gbNBTreeNode* gbNBTreeNode::IterateChild(void) {
    children.pIterator = children.pIterator->pNext;
    return (gbNBTreeNode*)children.pIterator;
}

gbNBTreeNode* gbNBTreeNode::GetChild(int index) {
    return (gbNBTreeNode*)children[index];
}


/* ================================================================
 * Implementation: gbNBTree
 * ================================================================ */

gbNBTree::gbNBTree(void) {
    pRoot = NULL;
}

gbNBTree::~gbNBTree() {
    if (pRoot)
        delete pRoot;
}

gbNBTree& gbNBTree::operator=(const gbNBTree& other) {
    pRoot = other.pRoot;
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
    pRight = NULL;
    pLeft = NULL;
    pParent = NULL;
}

gbBinaryTreeNode::gbBinaryTreeNode(const gbBinaryTreeNode& src) {
    pLeft = src.pLeft;
    pParent = src.pParent;
    pRight = src.pRight;
}

gbBinaryTreeNode::~gbBinaryTreeNode() {
    if (pLeft) {
        delete pLeft;
    }
    if (pRight) {
        delete pRight;
    }
    pRight = NULL;
    pLeft = NULL;
}

gbBinaryTreeNode& gbBinaryTreeNode::operator=(const gbBinaryTreeNode& other) {
    pParent = other.pParent;
    pLeft = other.pLeft;
    pRight = other.pRight;
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
    pRoot = other.pRoot;
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
    pIterator = NULL;
    pUsedHead = NULL;
    pFreeHead = NULL;
}

gbStaticChain& gbStaticChain::operator=(const gbStaticChain& other) {
    memcpy(this, &other, 0x1C);
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
    free(pBuffer);
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
    pIterator = pIterator->pNext;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::BeginReverseIterate(void) {
    gbStaticChainNode* result = pUsedHead;
    if (result) {
        gbStaticChainNode* v2;
        do {
            v2 = result;
            result = result->pNext;
        } while (result);
        pIterator = v2;
        return v2;
    } else {
        pIterator = NULL;
    }
    return result;
}

gbStaticChainNode* gbStaticChain::ReverseIterate(void) {
    pIterator = pIterator->pPrev;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::GetOldestNode(void) {
    gbStaticChainNode* result = pUsedHead;
    if (result) {
        gbStaticChainNode* v2;
        do {
            v2 = result;
            result = result->pNext;
        } while (result);
        return v2;
    }
    return result;
}

gbStaticChainNode* gbStaticChain::GetNewestNode(void) {
    return pUsedHead;
}

gbStaticChainNode* gbStaticChain::GetNode(int index) {
    return (gbStaticChainNode*)((char*)pBuffer + nNodeSize * index);
}
