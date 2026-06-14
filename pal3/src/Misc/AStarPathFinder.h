#pragma once
// Auto-generated: AStarPathFinder

class NODE;

class AStarPathFinder {
public:
    // vtable (3 methods, order matches binary layout)

    struct NODE;
    struct STACK;


    struct NODE {
        float f;
        float h;
        float g;
        int x;
        int y;
        int key;
        NODE * parent;
        NODE * stack[8];
        NODE * next;
    };

    struct STACK {
        int sp;
        NODE * top;
    };
    char _gap_000[4]; // +0x0
    NODE * OPEN; // +0x4
    NODE * CLOSED; // +0x8
    NODE * PATH; // +0xC
    STACK * Stack; // +0x10
    int m_TestTimer; // +0x14
    // total size: 0x18 (24)

    virtual void * _AStarPathFinder(char a2); // 0x00401030
    virtual int IsInBounds(int nX, int nY); // 0x004014E0
    virtual unsigned __int8 GetHeuristicIdx(int nX, int nY); // 0x004014F0
    AStarPathFinder(); // 0x00401000
    void ReleaseAll(); // 0x00401050
    int TryExpand(AStarPathFinder::NODE *pNode, int nTileX, int nTileY, int nGoalX, int nGoalY); // 0x004012A0
    int FindInOpen(int nTileIdx); // 0x00401500
    int FindInClosed(int nTileIdx); // 0x00401530
    int PushOpen(AStarPathFinder::NODE *pNode); // 0x00401560
    int Release(AStarPathFinder::NODE *pNode); // 0x00401590
    int UpdateNeighbors(AStarPathFinder::NODE *pNode); // 0x004015B0
    int ResortNode(); // 0x00401750
    AStarPathFinder::NODE * PopStack(); // 0x00401780
    int Reset(); // 0x004017A0
};
