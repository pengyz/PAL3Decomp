#include "NavigationInfo.h"

LayerNode::~LayerNode()
{
    /* stub */
}

void LayerNode::PassTri(Triangle * tri)
{
    /* stub */
}

void LayerNode::Build(NavFaceLayer * exp)
{
    /* stub */
}

LayerNode::LayerNode()
{
    /* stub */
}

void LayerNode::RayCol(gbRay * ray, ColRet * out)
{
    /* stub */
}

int NavFaceLayer::MapPoint2Surface(gbVec3D * pt, NavTriangle * ptri)
{
    /* stub */
    return 0;
}

int NavFaceLayer::RayCol(gbRay * ray, gbVec3D * colpt, NavTriangle * ptri)
{
    /* stub */
    return 0;
}

int NavTileLayer::CanGoTile(int x, int y)
{
    /* stub */
    return 0;
}

unsigned char NavTileLayer::GetTile(int x, int y)
{
    /* stub */
    return 0;
}

void NavigationInfo::Save(char * filename)
{
    /* stub */
}

void NavigationInfo::Load(char * filename, uchar isMakeTree)
{
    /* stub */
}

NavigationInfo::~NavigationInfo()
{
    /* stub */
}

NavigationInfo::NavigationInfo()
{
    /* stub */
}

void NavigationInfo::Destroy()
{
    /* stub */
}

gbAABBox CalTriBound(gbAABBox * __$ReturnUdt)
{
    /* stub */
    gbAABBox _ret = {0}; return _ret;
}

int IfBoxInBox(gbAABBox * s, gbAABBox * b)
{
    /* stub */
    return 0;
}

