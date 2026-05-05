#include "PathFinder.h"

PathFinder::~PathFinder()
{
    /* stub */
}

unsigned char PathFinder::GetTileValue(int x, int y)
{
    /* stub */
    return 0;
}

int PathFinder::CanGoTile(int x, int y)
{
    /* stub */
    return 0;
}

int PathFinder::FindPathInLayer(int layer, gbVec3D * start, gbVec3D * end, PathObj * path, Role * pRole)
{
    /* stub */
    return 0;
}

PathFinder::PathFinder()
{
    /* stub */
}

void PathObj::MapPathDistance2Point(float pathDistance, gbVec3D * point)
{
    /* stub */
}

void PathObj::CachePathStats()
{
    /* stub */
}

float PathObj::Point2SegmentDistance(gbVec3D * point, gbVec3D * ep0, gbVec3D * ep1)
{
    /* stub */
    return 0.0f;
}

int PathObj::MapPoint2Path(gbVec3D * point, gbVec3D * onpath, gbVec3D * tangent)
{
    /* stub */
    return 0;
}

float PathObj::MapPoint2PathDistance(gbVec3D * point)
{
    /* stub */
    return 0.0f;
}

void PathObj::MapPathDistance2Point(float pathDistance, gbVec3D * point, gbVec3D * _normal)
{
    /* stub */
}

