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
    next = src.next;
}

gbChain1DNode::~gbChain1DNode() {
}

gbChain1DNode& gbChain1DNode::operator=(const gbChain1DNode& other) {
    next = other.next;
    return *this;
}


/* ================================================================
 * Implementation: gbChain1D
 * ================================================================ */

gbChain1D::gbChain1D(void) {
    m_Tail = NULL;
    m_Head = NULL;
    m_numNode = 0;
}

gbChain1D::~gbChain1D() {
    gbChain1DNode* node = m_Head;
    while (node) {
        gbChain1DNode* next = node->next;
        delete node;
        node = next;
    }
}

gbChain1D& gbChain1D::operator=(const gbChain1D& other) {
    m_Head = other.m_Head;
    m_Tail = other.m_Tail;
    m_numNode = other.m_numNode;
    m_Cur = other.m_Cur;
    return *this;
}

void gbChain1D::ClearAllNodePtr(void) {
    m_Tail = NULL;
    m_Head = NULL;
    m_numNode = 0;
}

#pragma auto_inline(off)

void gbChain1D::AddNodeOnHead(gbChain1DNode* node) {
    node->next = m_Head;
    gbChain1DNode* v2 = m_Tail;
    m_Head = node;
    if (!v2)
        m_Tail = node;
    m_numNode++;
}

void gbChain1D::AddNodeOnTail(gbChain1DNode* node) {
    node->next = NULL;
    gbChain1DNode* v2 = m_Tail;
    if (!v2) {
        m_Tail = node;
        m_Head = node;
    } else {
        v2->next = node;
        m_Tail = node;
    }
    m_numNode++;
}

void gbChain1D::AddNode(gbChain1DNode* node) {
    node->next = NULL;
    gbChain1DNode* v2 = m_Tail;
    if (!v2) {
        m_Tail = node;
        m_Head = node;
    } else {
        v2->next = node;
        m_Tail = node;
    }
    m_numNode++;
}

void gbChain1D::InsertBefore(gbChain1DNode* newNode, gbChain1DNode* beforeNode) {
    gbChain1DNode* prev;
    gbChain1DNode* cur;

    if (!beforeNode) {
        newNode->next = NULL;
        gbChain1DNode* tail = m_Tail;
        if (tail) {
            tail->next = newNode;
            m_Tail = newNode;
        } else {
            m_Tail = newNode;
            m_Head = newNode;
        }
        m_numNode++;
        return;
    }

    prev = m_Head;
    if (prev == beforeNode) {
        m_Head = newNode;
        newNode->next = beforeNode;
        return;
    }

    cur = prev->next;
    while (cur != beforeNode) {
        prev = cur;
        cur = cur->next;
    }
    prev->next = newNode;
    newNode->next = beforeNode;
    m_numNode++;
}

void gbChain1D::InsertAfter(gbChain1DNode* newNode, gbChain1DNode* afterNode) {
    gbChain1DNode* tail;

    if (!afterNode) {
        newNode->next = m_Head;
        tail = m_Tail;
        m_Head = newNode;
        if (!tail) {
            m_Tail = newNode;
            m_numNode++;
            return;
        }
    } else {
        newNode->next = afterNode->next;
        afterNode->next = newNode;
        if (m_Tail == afterNode)
            m_Tail = newNode;
    }
    m_numNode++;
}

void gbChain1D::DelNodeFromChain(gbChain1DNode* node) {
    gbChain1DNode* prev;
    gbChain1DNode* cur;

    if (node == m_Head) {
        if (node == m_Tail) {
            m_Tail = NULL;
            m_Head = NULL;
            m_numNode--;
            return;
        }
        m_Head = node->next;
        m_numNode--;
        return;
    }

    prev = m_Head;
    cur = prev->next;
    if (cur) {
        while (cur != node) {
            prev = cur;
            cur = cur->next;
            if (!cur) {
                m_numNode--;
                return;
            }
        }
        if (node == m_Tail)
            m_Tail = prev;
        prev->next = node->next;
    }
    m_numNode--;
}

bool gbChain1D::IsContainNode(gbChain1DNode* node) {
    gbChain1DNode* curr = m_Head;
    while (curr) {
        if (curr == node) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

int gbChain1D::GetNumNode(void) {
    return m_numNode;
}

gbChain1DNode* gbChain1D::BeginIterate(void) {
    m_Cur = m_Head;
    return m_Cur;
}

gbChain1DNode* gbChain1D::Iterate(void) {
    m_Cur = m_Cur->next;
    return m_Cur;
}

gbChain1DNode* gbChain1D::operator[](int index) {
    gbChain1DNode* result = m_Head;
    int v3 = 0;
    if (index > 0) {
        while (result) {
            result = result->next;
            if (++v3 >= index)
                return result;
        }
        return NULL;
    }
    return result;
}


/* ================================================================
 * MARKER_STARTNode
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
 * MARKER_START
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
        gbChain2DNode* next = node->pNext;
        pHead = next;
        next->pPrev = NULL;
        nCount--;
        return;
    }

    if (node == pTail) {
        gbChain2DNode* prev = node->pPrev;
        pTail = prev;
        prev->pNext = NULL;
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
    pFather = NULL;
}

gbNBTreeNode::gbNBTreeNode(const gbNBTreeNode& src) : gbChain1DNode(src) {
    pFather = src.pFather;
    children = src.children;
}

gbNBTreeNode::~gbNBTreeNode() {
}

gbNBTreeNode& gbNBTreeNode::operator=(const gbNBTreeNode& other) {
    next = other.next;
    pFather = other.pFather;
    children.m_Head = other.children.m_Head;
    children.m_Tail = other.children.m_Tail;
    children.m_numNode = other.children.m_numNode;
    children.m_Cur = other.children.m_Cur;
    return *this;
}

void gbNBTreeNode::AddChildOnHead(gbNBTreeNode* child) {
    children.AddNodeOnHead((gbChain1DNode*)child);
    child->pFather = this;
}

void gbNBTreeNode::AddChildOnTail(gbNBTreeNode* child) {
    children.AddNodeOnTail((gbChain1DNode*)child);
    child->pFather = this;
}

void gbNBTreeNode::AddChild(gbNBTreeNode* child) {
    children.AddNode((gbChain1DNode*)child);
    child->pFather = this;
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
    return pFather;
}

gbNBTreeNode* gbNBTreeNode::BeginIterateChild(void) {
    children.m_Cur = children.m_Head;
    return (gbNBTreeNode*)children.m_Cur;
}

gbNBTreeNode* gbNBTreeNode::IterateChild(void) {
    children.m_Cur = children.m_Cur->next;
    return (gbNBTreeNode*)children.m_Cur;
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

void gbStaticChain::DelOneNode(gbStaticChainNode* node) {
    if (node->pPrev) {
        node->pPrev->pNext = node->pNext;
    }
    gbStaticChainNode* next = node->pNext;
    if (next) {
        next->pPrev = node->pPrev;
    }
    if (pUsedHead == node) {
        pUsedHead = node->pNext;
    }
    gbStaticChainNode* freeHead = pFreeHead;
    if (freeHead) {
        freeHead->pPrev = node;
    }
    gbStaticChainNode* oldFreeHead = pFreeHead;
    node->pPrev = NULL;
    node->pNext = oldFreeHead;
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
