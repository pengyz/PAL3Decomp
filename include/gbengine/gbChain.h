#pragma once

#include "gbengine/gbengine_types.h"


/* ======== gbChain1DNode ======== */
// Single-linked list node (8 bytes)

class gbChain1DNode {
public:
    gbChain1DNode* pNext;   // +0x04: next node (vptr at +0x00 from virtual dtor)

    gbChain1DNode(void);
    gbChain1DNode(const gbChain1DNode& src);
    virtual ~gbChain1DNode();
    gbChain1DNode& operator=(const gbChain1DNode& other);
};


/* ======== gbChain1D ======== */
// Single-linked list (16 bytes)

class gbChain1D {
public:
    gbChain1DNode* pHead;      // +0x00
    gbChain1DNode* pTail;      // +0x04
    int nCount;                // +0x08
    gbChain1DNode* pIterator;  // +0x0C

    gbChain1D(void);
    ~gbChain1D();
    gbChain1D& operator=(const gbChain1D& other);

    void ClearAllNodePtr(void);
    void AddNodeOnHead(gbChain1DNode* node);
    void AddNodeOnTail(gbChain1DNode* node);
    void AddNode(gbChain1DNode* node);
    void InsertBefore(gbChain1DNode* newNode, gbChain1DNode* beforeNode);
    void InsertAfter(gbChain1DNode* newNode, gbChain1DNode* afterNode);
    void DelNodeFromChain(gbChain1DNode* node);
    bool IsContainNode(gbChain1DNode* node);
    int GetNumNode(void);
    gbChain1DNode* BeginIterate(void);
    gbChain1DNode* Iterate(void);
    gbChain1DNode* operator[](int index);
};


/* ======== gbChain2DNode ======== */
// Double-linked list node (12 bytes)

class gbChain2DNode {
public:
    gbChain2DNode* pPrev;   // +0x04: previous node
    gbChain2DNode* pNext;   // +0x08: next node

    gbChain2DNode(void);
    gbChain2DNode(const gbChain2DNode& src);
    virtual ~gbChain2DNode();
    gbChain2DNode& operator=(const gbChain2DNode& other);
};


/* ======== gbChain2D ======== */
// Double-linked list (20 bytes)

class gbChain2D {
public:
    gbChain2DNode* pHead;      // +0x00
    gbChain2DNode* pTail;      // +0x04
    int nDirection;            // +0x08: 0=forward, 1=backward
    int nCount;                // +0x0C
    gbChain2DNode* pIterator;  // +0x10

    gbChain2D(void);
    ~gbChain2D();
    gbChain2D& operator=(const gbChain2D& other);

    void AddNode(gbChain2DNode* node);
    void DelNodeFromChain(gbChain2DNode* node);
    bool IsContainNode(gbChain2DNode* node);
    int GetNumNode(void);
    gbChain2DNode* BeginIterate(int dir);
    gbChain2DNode* Iterate(void);
};


/* ======== gbNBTreeNode ======== */
// N-ary tree node (28 bytes, inherits gbChain1DNode)

class gbNBTreeNode : public gbChain1DNode {
public:
    gbNBTreeNode* pParent;         // +0x08
    gbChain1D children;            // +0x0C (16 bytes: head at +0C, tail at +10, count at +14, iter at +18)

    gbNBTreeNode(void);
    gbNBTreeNode(const gbNBTreeNode& src);
    virtual ~gbNBTreeNode();
    gbNBTreeNode& operator=(const gbNBTreeNode& other);

    void AddChildOnHead(gbNBTreeNode* child);
    void AddChildOnTail(gbNBTreeNode* child);
    void AddChild(gbNBTreeNode* child);
    void DelChildFromChain(gbNBTreeNode* child);
    int IsChild(gbNBTreeNode* child);
    int GetNumChildren(void);
    gbChain1D& GetChildren(void);
    gbNBTreeNode* GetFather(void);
    gbNBTreeNode* BeginIterateChild(void);
    gbNBTreeNode* IterateChild(void);
    gbNBTreeNode* GetChild(int index);
};


/* ======== gbNBTree ======== */
// N-ary tree (4 bytes)

class gbNBTree {
public:
    gbNBTreeNode* pRoot;  // +0x00

    gbNBTree(void);
    ~gbNBTree();
    gbNBTree& operator=(const gbNBTree& other);

    void SetRoot(gbNBTreeNode* node);
    gbNBTreeNode* GetRoot(void);
};


/* ======== gbBinaryTreeNode ======== */
// Binary tree node (16 bytes)

class gbBinaryTreeNode {
public:
    gbBinaryTreeNode* pParent;     // +0x04
    gbBinaryTreeNode* pLeft;       // +0x08
    gbBinaryTreeNode* pRight;      // +0x0C

    gbBinaryTreeNode(void);
    gbBinaryTreeNode(const gbBinaryTreeNode& src);
    virtual ~gbBinaryTreeNode();
    gbBinaryTreeNode& operator=(const gbBinaryTreeNode& other);

    gbBinaryTreeNode* GetFather(void);
    gbBinaryTreeNode* GetLeft(void);
    gbBinaryTreeNode* GetRight(void);
};


/* ======== gbBinaryTree ======== */
// Binary tree (4 bytes)

class gbBinaryTree {
public:
    gbBinaryTreeNode* pRoot;  // +0x00

    gbBinaryTree(void);
    ~gbBinaryTree();
    gbBinaryTree& operator=(const gbBinaryTree& other);

    void SetRoot(gbBinaryTreeNode* node);
    gbBinaryTreeNode* GetRoot(void);
};


/* ======== gbStaticChainNode ======== */
// Static chain node (variable size, first 8 bytes are prev/next)

struct gbStaticChainNode {
    gbStaticChainNode* pPrev;  // +0x00
    gbStaticChainNode* pNext;  // +0x04
    // Rest of node data follows...
};


/* ======== gbStaticChain ======== */
// Static memory pool with linked list (28 bytes)

class gbStaticChain {
public:
    void* pBuffer;                  // +0x00: allocated memory
    gbStaticChainNode* pFreeHead;   // +0x04: free list head
    gbStaticChainNode* pUsedHead;   // +0x08: used list head
    gbStaticChainNode* pIterator;   // +0x0C: iterator
    int nMaxNodes;                  // +0x10: max nodes
    int nNodeSize;                  // +0x14: node size in bytes
    int nUsedCount;                 // +0x18: used count

    gbStaticChain(void);
    gbStaticChain& operator=(const gbStaticChain& other);

    void InitBuffer(int maxNodes, int nodeSize);
    void ReleaseBuffer(void);
    gbStaticChainNode* NewOneNode(void);
    void DelOneNode(gbStaticChainNode* ptr);
    gbStaticChainNode* BeginIterate(void);
    gbStaticChainNode* Iterate(void);
    gbStaticChainNode* BeginReverseIterate(void);
    gbStaticChainNode* ReverseIterate(void);
    gbStaticChainNode* GetOldestNode(void);
    gbStaticChainNode* GetNewestNode(void);

private:
    gbStaticChainNode* GetNode(int index);
};
