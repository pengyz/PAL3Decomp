#ifndef PAL3A_NAVIGATIONINFO_H
#define PAL3A_NAVIGATIONINFO_H

#include "pal3a_types.h"

class LayerNode {
public:
    char _data[60];

    ~LayerNode();
    void PassTri(Triangle * tri);
    void Build(NavFaceLayer * exp);
    LayerNode();
    void RayCol(gbRay * ray, ColRet * out);
};

class NavFaceLayer {
public:
    char _data[64];

    int MapPoint2Surface(gbVec3D * pt, NavTriangle * ptri);
    int RayCol(gbRay * ray, gbVec3D * colpt, NavTriangle * ptri);
};

class NavTileLayer {
public:
    char _data[64];

    int CanGoTile(int x, int y);
    unsigned char GetTile(int x, int y);
};

class NavigationInfo {
public:
    char _data[364];

    void Save(char * filename);
    void Load(char * filename, uchar isMakeTree);
    ~NavigationInfo();
    NavigationInfo();
    void Destroy();
};

gbAABBox CalTriBound(gbAABBox * __$ReturnUdt);
int IfBoxInBox(gbAABBox * s, gbAABBox * b);

#endif // PAL3A_NAVIGATIONINFO_H
