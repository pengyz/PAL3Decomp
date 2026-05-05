#ifndef PAL3A_ASTARPATHFINDER_H
#define PAL3A_ASTARPATHFINDER_H

#include "pal3a_types.h"

class AStarPathFinder {
public:
    char _data[24];

    void* ReturnBestNode();
    int GenerateSucc(void* BestNode, int x, int y, int dx, int dy);
    ~AStarPathFinder();
    void DeleteNode(void* node);
    AStarPathFinder();
    void InsertOpen(void* node);
    void PropagateDown(void* Old);
    void* CheckOPEN(int sum);
    unsigned char GetTileValue(int x, int y);
    int CanGoTile(int x, int y);
    int FindPath(int sx, int sy, int dx, int dy);
    void Destroy();
    void* CheckCLOSED(int sum);
    void* Pop();
    void Push(void* Node);
    int FindPathNear(int sx, int sy, int dx, int dy, int rangle);
};

void TileNum(int x, int y);

#endif // PAL3A_ASTARPATHFINDER_H
