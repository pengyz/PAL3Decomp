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

#pragma auto_inline(off)

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
    gbChain1DNode* prev;
    gbChain1DNode* cur;

    if (beforeNode != NULL) {
        prev = pHead;
        if (prev != beforeNode) {
            cur = prev->pNext;
            while (cur != beforeNode) {
                prev = cur;
                cur = cur->pNext;
            }
            prev->pNext = newNode;
            newNode->pNext = beforeNode;
            nCount++;
            return;
        }
        pHead = newNode;
        newNode->pNext = beforeNode;
        return;
    }

    newNode->pNext = NULL;
    if (pTail != NULL) {
        pTail->pNext = newNode;
        pTail = newNode;
        nCount++;
        return;
    }
    pTail = newNode;
    pHead = newNode;
    nCount++;
}

void gbChain1D::InsertAfter(gbChain1DNode* newNode, gbChain1DNode* afterNode) {
    if (afterNode) {
        newNode->pNext = afterNode->pNext;
        afterNode->pNext = newNode;
        if (pTail == afterNode)
            pTail = newNode;
    } else {
        newNode->pNext = pHead;
        gbChain1DNode* t = pTail;
        pHead = newNode;
        if (!t) {
            pTail = newNode;
            nCount++;
            return;
        }
    }
    nCount++;
}

void gbChain1D::DelNodeFromChain(gbChain1DNode* node) {
    gbChain1DNode* prev;
    gbChain1DNode* cur;

    if (node == pHead) {
        if (node == pTail) {
            pTail = NULL;
            pHead = NULL;
            nCount--;
            return;
        }
        pHead = node->pNext;
        nCount--;
        return;
    }

    prev = pHead;
    cur = prev->pNext;
    if (cur != NULL) {
        while (cur != node) {
            prev = cur;
            cur = cur->pNext;
            if (cur == NULL) {
                nCount--;
                return;
            }
        }
        if (node == pTail) {
            pTail = prev;
        }
        prev->pNext = node->pNext;
    }
    nCount--;
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
    if (node == pHead) {
        if (node == pTail) {
            pTail = NULL;
            pHead = NULL;
            nCount--;
            return;
        }
        pHead = node->pNext;
        node->pNext->pPrev = NULL;
        nCount--;
        return;
    }

    if (node == pTail) {
        pTail = node->pPrev;
        node->pPrev->pNext = NULL;
        nCount--;
        return;
    }

    node->pPrev->pNext = node->pNext;
    node->pNext->pPrev = node->pPrev;
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
    children.pHead = other.children.pHead;
    children.pTail = other.children.pTail;
    children.nCount = other.children.nCount;
    children.pIterator = other.children.pIterator;
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
    int i;
    int last;

    nMaxNodes = maxNodes;
    nNodeSize = nodeSize;
    nUsedCount = 0;

    pBuffer = malloc(maxNodes * nodeSize);

    // Build forward links: nodes[i].pNext -> nodes[i+1]
    last = maxNodes - 1;
    i = 0;
    if (i < last) {
        do {
            gbStaticChainNode* next = (gbStaticChainNode*)((char*)pBuffer + (i + 1) * nNodeSize);
            gbStaticChainNode* cur = (gbStaticChainNode*)((char*)pBuffer + i * nNodeSize);
            cur->pNext = next;
            i++;
        } while (i < last);
    }

    // Last node's pNext = NULL
    gbStaticChainNode* lastNode = (gbStaticChainNode*)((char*)pBuffer + last * nNodeSize);
    lastNode->pNext = NULL;

    // Build backward links: nodes[i].pPrev -> nodes[i-1]
    i = 1;
    if (i < maxNodes) {
        do {
            gbStaticChainNode* cur = (gbStaticChainNode*)((char*)pBuffer + i * nNodeSize);
            gbStaticChainNode* prev = (gbStaticChainNode*)((char*)pBuffer + (i - 1) * nNodeSize);
            cur->pPrev = prev;
            i++;
        } while (i < maxNodes);
    }

    // First node's pPrev = NULL
    ((gbStaticChainNode*)pBuffer)->pPrev = NULL;

    // Free list starts at buffer[0]
    pFreeHead = (gbStaticChainNode*)pBuffer;
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
