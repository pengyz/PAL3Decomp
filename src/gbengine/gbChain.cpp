/**
 * gbengine.dll - gbChain
 * Linked lists, trees, and static chain implementations
 * Functions: 41
 */

#include "gbengine/gbengine_types.h"
#include <stdlib.h>

// Forward declarations
class gbChain1DNode;
class gbChain1D;
class gbChain2DNode;
class gbChain2D;
class gbNBTreeNode;
class gbNBTree;
class gbBinaryTreeNode;
class gbBinaryTree;
class gbStaticChainNode;
class gbStaticChain;


/* ======== gbChain1DNode ======== */
// Single-linked list node (8 bytes)

class gbChain1DNode {
public:
    void* vtable;           // +0x00: dummy vtable pointer
    gbChain1DNode* pNext;   // +0x04: next node

    // Constructor
    gbChain1DNode(void) {
        vtable = NULL;
        pNext = NULL;
    }

    // Copy constructor
    gbChain1DNode(gbChain1DNode* src) {
        vtable = NULL;
        if (src) {
            pNext = src->pNext;
        } else {
            pNext = NULL;
        }
    }
};


/* ======== gbChain1D ======== */
// Single-linked list (16 bytes)

class gbChain1D {
public:
    gbChain1DNode* pHead;      // +0x00
    gbChain1DNode* pTail;      // +0x04
    int nCount;                // +0x08
    gbChain1DNode* pIterator;  // +0x0C

    // Constructor
    gbChain1D(void) {
        pHead = NULL;
        pTail = NULL;
        nCount = 0;
        pIterator = NULL;
    }

    // Clear all node pointers
    void ClearAllNodePtr(void) {
        pTail = NULL;
        pHead = NULL;
        nCount = 0;
        pIterator = NULL;
    }

    // Add node to head
    void AddNodeOnHead(gbChain1DNode* node) {
        if (!node) return;
        node->pNext = pHead;
        pHead = node;
        if (!pTail) {
            pTail = node;
        }
        nCount++;
    }

    // Add node to tail
    void AddNode(gbChain1DNode* node) {
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

    // Insert new node before specified node
    void InsertBefore(gbChain1DNode* newNode, gbChain1DNode* beforeNode) {
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

    // Insert new node after specified node
    void InsertAfter(gbChain1DNode* newNode, gbChain1DNode* afterNode) {
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

    // Remove node from chain
    void DelNodeFromChain(gbChain1DNode* node) {
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

    // Check if node is in chain
    int IsContainNode(gbChain1DNode* node) {
        gbChain1DNode* curr = pHead;
        while (curr) {
            if (curr == node) {
                return 1;
            }
            curr = curr->pNext;
        }
        return 0;
    }

    // Iterate to next node
    gbChain1DNode* Iterate(void) {
        if (pIterator) {
            pIterator = pIterator->pNext;
        }
        return pIterator;
    }
};


/* ======== gbChain2DNode ======== */
// Double-linked list node (12 bytes)

class gbChain2DNode {
public:
    void* vtable;           // +0x00: dummy vtable pointer
    gbChain2DNode* pPrev;   // +0x04: previous node
    gbChain2DNode* pNext;   // +0x08: next node

    // Constructor
    gbChain2DNode(void) {
        vtable = NULL;
        pPrev = NULL;
        pNext = NULL;
    }

    // Copy constructor
    gbChain2DNode(gbChain2DNode* src) {
        vtable = NULL;
        if (src) {
            pPrev = src->pPrev;
            pNext = src->pNext;
        } else {
            pPrev = NULL;
            pNext = NULL;
        }
    }
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

    // Constructor
    gbChain2D(void) {
        pHead = NULL;
        pTail = NULL;
        nDirection = 0;
        nCount = 0;
        pIterator = NULL;
    }

    // Add node to tail
    void AddNode(gbChain2DNode* node) {
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

    // Remove node from chain
    void DelNodeFromChain(gbChain2DNode* node) {
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

    // Check if node is in chain
    int IsContainNode(gbChain2DNode* node) {
        gbChain2DNode* curr = pHead;
        while (curr) {
            if (curr == node) {
                return 1;
            }
            curr = curr->pNext;
        }
        return 0;
    }

    // Begin iteration with direction
    gbChain2DNode* BeginIterate(int dir) {
        nDirection = dir;
        if (dir == 0) {
            pIterator = pHead;
        } else {
            pIterator = pTail;
        }
        return pIterator;
    }

    // Iterate to next/previous node based on direction
    gbChain2DNode* Iterate(void) {
        if (pIterator) {
            if (nDirection == 0) {
                pIterator = pIterator->pNext;
            } else {
                pIterator = pIterator->pPrev;
            }
        }
        return pIterator;
    }
};


/* ======== gbNBTreeNode ======== */
// N-ary tree node (28 bytes, inherits gbChain1DNode)

class gbNBTreeNode : public gbChain1DNode {
public:
    gbNBTreeNode* pParent;         // +0x08
    gbChain1D children;            // +0x0C (12 bytes: head at +0C, tail at +10, count at +14)
    gbNBTreeNode* pChildIterator;  // +0x18

    // Constructor
    gbNBTreeNode(void) : gbChain1DNode() {
        pParent = NULL;
        pChildIterator = NULL;
    }

    // Copy constructor
    gbNBTreeNode(gbNBTreeNode* src) : gbChain1DNode((gbChain1DNode*)src) {
        if (src) {
            pParent = src->pParent;
            children = src->children;
            pChildIterator = src->pChildIterator;
        } else {
            pParent = NULL;
            pChildIterator = NULL;
        }
    }

    // Add child to head
    void AddChildOnHead(gbNBTreeNode* child) {
        if (!child) return;
        children.AddNodeOnHead((gbChain1DNode*)child);
        child->pParent = this;
    }

    // Add child to tail
    void AddChild(gbNBTreeNode* child) {
        if (!child) return;
        children.AddNode((gbChain1DNode*)child);
        child->pParent = this;
    }

    // Remove child from chain
    void DelChildFromChain(gbNBTreeNode* child) {
        if (!child) return;
        children.DelNodeFromChain((gbChain1DNode*)child);
    }

    // Check if node is a child
    int IsChild(gbNBTreeNode* child) {
        return children.IsContainNode((gbChain1DNode*)child);
    }

    // Iterate to next child
    gbNBTreeNode* IterateChild(void) {
        if (pChildIterator) {
            pChildIterator = (gbNBTreeNode*)pChildIterator->pNext;
        }
        return pChildIterator;
    }

    // Get child by index
    gbNBTreeNode* GetChild(int index) {
        if (index < 0 || index >= children.nCount) {
            return NULL;
        }
        gbChain1DNode* node = children.pHead;
        for (int i = 0; i < index && node; i++) {
            node = node->pNext;
        }
        return (gbNBTreeNode*)node;
    }
};


/* ======== gbNBTree ======== */
// N-ary tree (4 bytes)

class gbNBTree {
public:
    gbNBTreeNode* pRoot;  // +0x00

    // Constructor
    gbNBTree(void) {
        pRoot = NULL;
    }

    // Set root node
    void SetRoot(gbNBTreeNode* node) {
        pRoot = node;
    }
};


/* ======== gbBinaryTreeNode ======== */
// Binary tree node (16 bytes)

class gbBinaryTreeNode {
public:
    void* vtable;                  // +0x00: dummy vtable pointer
    gbBinaryTreeNode* pLeft;       // +0x04
    gbBinaryTreeNode* pRight;      // +0x08
    gbBinaryTreeNode* pParent;     // +0x0C

    // Constructor
    gbBinaryTreeNode(void) {
        vtable = NULL;
        pLeft = NULL;
        pRight = NULL;
        pParent = NULL;
    }

    // Copy constructor
    gbBinaryTreeNode(gbBinaryTreeNode* src) {
        vtable = NULL;
        if (src) {
            pLeft = src->pLeft;
            pRight = src->pRight;
            pParent = src->pParent;
        } else {
            pLeft = NULL;
            pRight = NULL;
            pParent = NULL;
        }
    }
};


/* ======== gbBinaryTree ======== */
// Binary tree (4 bytes)

class gbBinaryTree {
public:
    gbBinaryTreeNode* pRoot;  // +0x00

    // Constructor
    gbBinaryTree(void) {
        pRoot = NULL;
    }

    // Set root node
    void SetRoot(gbBinaryTreeNode* node) {
        pRoot = node;
    }
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
    int nUsedCount;                 // +0x18: used count (uncertain)

    // Constructor
    gbStaticChain(void) {
        pBuffer = NULL;
        pFreeHead = NULL;
        pUsedHead = NULL;
        pIterator = NULL;
        nMaxNodes = 0;
        nNodeSize = 0;
        nUsedCount = 0;
    }

    // Initialize buffer with max nodes and node size
    void InitBuffer(int maxNodes, int nodeSize) {
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

    // Release buffer
    void ReleaseBuffer(void) {
        if (pBuffer) {
            free(pBuffer);
            pBuffer = NULL;
        }
        pFreeHead = NULL;
        pUsedHead = NULL;
        pIterator = NULL;
    }

    // Allocate one node from free list
    void* NewOneNode(void) {
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
        return (void*)node;
    }

    // Free one node back to free list
    void DelOneNode(void* ptr) {
        if (!ptr) return;
        gbStaticChainNode* node = (gbStaticChainNode*)ptr;

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

    // Iterate to next used node
    void* Iterate(void) {
        if (pIterator) {
            pIterator = pIterator->pNext;
        }
        return (void*)pIterator;
    }

    // Begin reverse iteration (start from tail of used list)
    void* BeginReverseIterate(void) {
        pIterator = pUsedHead;
        if (!pIterator) return NULL;

        // Walk to end of used list
        while (pIterator->pNext) {
            pIterator = pIterator->pNext;
        }
        return (void*)pIterator;
    }

    // Reverse iterate to previous used node
    void* ReverseIterate(void) {
        if (pIterator) {
            pIterator = pIterator->pPrev;
        }
        return (void*)pIterator;
    }

    // Get oldest node (last in used list)
    void* GetOldestNode(void) {
        if (!pUsedHead) return NULL;

        gbStaticChainNode* node = pUsedHead;
        while (node->pNext) {
            node = node->pNext;
        }
        return (void*)node;
    }

    // Get node by index in buffer
    void* GetNode(int index) {
        if (index < 0 || index >= nMaxNodes || !pBuffer) {
            return NULL;
        }
        return (void*)((char*)pBuffer + nNodeSize * index);
    }
};
