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
    /* STUB */
}

gbChain1DNode::gbChain1DNode(const gbChain1DNode& src) {
    /* STUB */
    pNext = src.pNext;
}

gbChain1DNode::~gbChain1DNode() {
    /* STUB */
}

gbChain1DNode& gbChain1DNode::operator=(const gbChain1DNode& other) {
    /* STUB */
    pNext = other.pNext;
    return *this;
}


/* ================================================================
 * Implementation: gbChain1D
 * ================================================================ */

gbChain1D::gbChain1D(void) {
    /* STUB */
    pTail = NULL;
    pHead = NULL;
    nCount = 0;
}

gbChain1D::~gbChain1D() {
    /* STUB */
}

gbChain1D& gbChain1D::operator=(const gbChain1D& other) {
    /* STUB */
    pHead = other.pHead;
    pTail = other.pTail;
    nCount = other.nCount;
    pIterator = other.pIterator;
    return *this;
}

void gbChain1D::ClearAllNodePtr(void) {
    /* STUB */
    pTail = NULL;
    pHead = NULL;
    nCount = 0;
}

void gbChain1D::AddNodeOnHead(gbChain1DNode* node) {
    /* STUB */
    node->pNext = pHead;
    gbChain1DNode* v2 = pTail;
    pHead = node;
    if (!v2)
        pTail = node;
    nCount++;
}

void gbChain1D::AddNodeOnTail(gbChain1DNode* node) {
    /* STUB */
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
    /* STUB */
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
    /* STUB */
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
    /* STUB */
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
    /* STUB */
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
    /* STUB */
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
    /* STUB */
    return nCount;
}

gbChain1DNode* gbChain1D::BeginIterate(void) {
    /* STUB */
    pIterator = pHead;
    return pIterator;
}

gbChain1DNode* gbChain1D::Iterate(void) {
    /* STUB */
    pIterator = pIterator->pNext;
    return pIterator;
}

gbChain1DNode* gbChain1D::operator[](int index) {
    /* STUB */
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
    /* STUB */
}

gbChain2DNode::gbChain2DNode(const gbChain2DNode& src) {
    /* STUB */
    pPrev = src.pPrev;
    pNext = src.pNext;
}

gbChain2DNode::~gbChain2DNode() {
    /* STUB */
}

gbChain2DNode& gbChain2DNode::operator=(const gbChain2DNode& other) {
    /* STUB */
    pPrev = other.pPrev;
    pNext = other.pNext;
    return *this;
}


/* ================================================================
 * Implementation: gbChain2D
 * ================================================================ */

gbChain2D::gbChain2D(void) {
    /* STUB */
    pTail = NULL;
    pHead = NULL;
    nCount = 0;
}

gbChain2D::~gbChain2D() {
    /* STUB */
}

gbChain2D& gbChain2D::operator=(const gbChain2D& other) {
    /* STUB */
    memcpy(this, &other, 0x14);
    return *this;
}

void gbChain2D::AddNode(gbChain2DNode* node) {
    /* STUB */
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
    /* STUB */
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
    /* STUB */
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
    /* STUB */
    return nCount;
}

gbChain2DNode* gbChain2D::BeginIterate(int dir) {
    /* STUB */
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
    /* STUB */
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
    /* STUB */
    pParent = NULL;
}

gbNBTreeNode::gbNBTreeNode(const gbNBTreeNode& src) : gbChain1DNode(src) {
    /* STUB */
    pParent = src.pParent;
    children = src.children;
}

gbNBTreeNode::~gbNBTreeNode() {
    /* STUB */
}

gbNBTreeNode& gbNBTreeNode::operator=(const gbNBTreeNode& other) {
    /* STUB */
    pNext = other.pNext;
    pParent = other.pParent;
    children = other.children;
    return *this;
}

void gbNBTreeNode::AddChildOnHead(gbNBTreeNode* child) {
    /* STUB */
    children.AddNodeOnHead((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::AddChildOnTail(gbNBTreeNode* child) {
    /* STUB */
    children.AddNode((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::AddChild(gbNBTreeNode* child) {
    /* STUB */
    children.AddNode((gbChain1DNode*)child);
    child->pParent = this;
}

void gbNBTreeNode::DelChildFromChain(gbNBTreeNode* child) {
    /* STUB */
    children.DelNodeFromChain((gbChain1DNode*)child);
}

int gbNBTreeNode::IsChild(gbNBTreeNode* child) {
    /* STUB */
    return children.IsContainNode((gbChain1DNode*)child);
}

int gbNBTreeNode::GetNumChildren(void) {
    /* STUB */
    return children.GetNumNode();
}

gbChain1D& gbNBTreeNode::GetChildren(void) {
    /* STUB */
    return children;
}

gbNBTreeNode* gbNBTreeNode::GetFather(void) {
    /* STUB */
    return pParent;
}

gbNBTreeNode* gbNBTreeNode::BeginIterateChild(void) {
    /* STUB */
    children.pIterator = children.pHead;
    return (gbNBTreeNode*)children.pIterator;
}

gbNBTreeNode* gbNBTreeNode::IterateChild(void) {
    /* STUB */
    children.pIterator = children.pIterator->pNext;
    return (gbNBTreeNode*)children.pIterator;
}

gbNBTreeNode* gbNBTreeNode::GetChild(int index) {
    /* STUB */
    return (gbNBTreeNode*)children[index];
}


/* ================================================================
 * Implementation: gbNBTree
 * ================================================================ */

gbNBTree::gbNBTree(void) {
    /* STUB */
    pRoot = NULL;
}

gbNBTree::~gbNBTree() {
    /* STUB */
}

gbNBTree& gbNBTree::operator=(const gbNBTree& other) {
    /* STUB */
    pRoot = other.pRoot;
    return *this;
}

void gbNBTree::SetRoot(gbNBTreeNode* node) {
    /* STUB */
    pRoot = node;
}

gbNBTreeNode* gbNBTree::GetRoot(void) {
    /* STUB */
    return pRoot;
}


/* ================================================================
 * Implementation: gbBinaryTreeNode
 * ================================================================ */

gbBinaryTreeNode::gbBinaryTreeNode(void) {
    /* STUB */
    pRight = NULL;
    pParent = NULL;
    pLeft = NULL;
}

gbBinaryTreeNode::gbBinaryTreeNode(const gbBinaryTreeNode& src) {
    /* STUB */
    pLeft = src.pLeft;
    pParent = src.pParent;
    pRight = src.pRight;
}

gbBinaryTreeNode::~gbBinaryTreeNode() {
    /* STUB */
}

gbBinaryTreeNode& gbBinaryTreeNode::operator=(const gbBinaryTreeNode& other) {
    /* STUB */
    pLeft = other.pLeft;
    pParent = other.pParent;
    pRight = other.pRight;
    return *this;
}

gbBinaryTreeNode* gbBinaryTreeNode::GetFather(void) {
    /* STUB */
    return pParent;
}

gbBinaryTreeNode* gbBinaryTreeNode::GetLeft(void) {
    /* STUB */
    return pLeft;
}

gbBinaryTreeNode* gbBinaryTreeNode::GetRight(void) {
    /* STUB */
    return pRight;
}


/* ================================================================
 * Implementation: gbBinaryTree
 * ================================================================ */

gbBinaryTree::gbBinaryTree(void) {
    /* STUB */
    pRoot = NULL;
}

gbBinaryTree::~gbBinaryTree() {
    /* STUB */
}

gbBinaryTree& gbBinaryTree::operator=(const gbBinaryTree& other) {
    /* STUB */
    pRoot = other.pRoot;
    return *this;
}

void gbBinaryTree::SetRoot(gbBinaryTreeNode* node) {
    /* STUB */
    pRoot = node;
}

gbBinaryTreeNode* gbBinaryTree::GetRoot(void) {
    /* STUB */
    return pRoot;
}


/* ================================================================
 * Implementation: gbStaticChain
 * ================================================================ */

gbStaticChain::gbStaticChain(void) {
    /* STUB */
    pBuffer = NULL;
    pIterator = NULL;
    pUsedHead = NULL;
    pFreeHead = NULL;
}

gbStaticChain& gbStaticChain::operator=(const gbStaticChain& other) {
    /* STUB */
    memcpy(this, &other, 0x1C);
    return *this;
}

void gbStaticChain::InitBuffer(int maxNodes, int nodeSize) {
    /* STUB */
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
    /* STUB */
    free(pBuffer);
}

gbStaticChainNode* gbStaticChain::NewOneNode(void) {
    /* STUB */
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
    /* STUB */
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
    /* STUB */
    pIterator = pUsedHead;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::Iterate(void) {
    /* STUB */
    pIterator = pIterator->pNext;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::BeginReverseIterate(void) {
    /* STUB */
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
    /* STUB */
    pIterator = pIterator->pPrev;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::GetOldestNode(void) {
    /* STUB */
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
    /* STUB */
    return pUsedHead;
}

gbStaticChainNode* gbStaticChain::GetNode(int index) {
    /* STUB */
    return (gbStaticChainNode*)((char*)pBuffer + nNodeSize * index);
}
