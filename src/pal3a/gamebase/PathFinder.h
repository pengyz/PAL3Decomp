#ifndef PAL3A_PATHFINDER_H
#define PAL3A_PATHFINDER_H

#include "pal3a_types.h"

class PathFinder {
public:
    char _data[36];

    ~PathFinder();
    unsigned char GetTileValue(int x, int y);
    int CanGoTile(int x, int y);
    int FindPathInLayer(int layer, gbVec3D * start, gbVec3D * end, PathObj * path, Role * pRole);
    PathFinder();
};

class PathObj {
public:
    char _data[64];

    void MapPathDistance2Point(float pathDistance, gbVec3D * point);
    void CachePathStats();
    float Point2SegmentDistance(gbVec3D * point, gbVec3D * ep0, gbVec3D * ep1);
    int MapPoint2Path(gbVec3D * point, gbVec3D * onpath, gbVec3D * tangent);
    float MapPoint2PathDistance(gbVec3D * point);
    void MapPathDistance2Point(float pathDistance, gbVec3D * point, gbVec3D * _normal);
};

#endif // PAL3A_PATHFINDER_H
