#include "CollidePack.h"

void collision::traceCollision(std::vector<sCollision,std::allocator<sCollision> > * cl)
{
    /* stub */
}

std::vector<struct sCollision,class std::allocator<struct sCollision> > collision::calcColliders(void* __$ReturnUdt, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * polygonList)
{
    /* stub */
    static std::vector<struct sCollision,class std::allocator<struct sCollision> > _ret; return _ret;
}

matrix<3,1,float> collision::collideAndSlide(void* __$ReturnUdt, matrix<3,1,float> * radiusVector, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * polygonList, Collide_Ray<3,float> * r, matrix<3,1,float> * lastDir, uchar * bCollide)
{
    /* stub */
    static matrix<3,1,float> _ret; return _ret;
}

matrix<3,1,float> collision::collideAndStop(void* __$ReturnUdt, matrix<3,1,float> * radiusVector, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * polygonList)
{
    /* stub */
    static matrix<3,1,float> _ret; return _ret;
}

bool collision::isEmbedded(primitive<3,float> * p, matrix<3,1,float> * sphereCenter, matrix<3,1,float> * innerMostPoint)
{
    /* stub */
    return FALSE;
}

bool collision::unitSphereIntersection(matrix<3,1,float> * center, Collide_Ray<3,float> * r, float * time)
{
    /* stub */
    return FALSE;
}

float frand()
{
    /* stub */
    return 0.0f;
}

matrix<3,1,float> closestPointOnLineSegment(void* __$ReturnUdt, matrix<3,1,float> * a, matrix<3,1,float> * b, matrix<3,1,float> * p)
{
    /* stub */
    static matrix<3,1,float> _ret; return _ret;
}

float GetPlaneDistance(matrix<3,1,float> V, matrix<3,1,float> tA, matrix<3,1,float> tN)
{
    /* stub */
    return 0.0f;
}

matrix<3,1,float> closestPointOnLine(void* __$ReturnUdt, matrix<3,1,float> * a, matrix<3,1,float> * b)
{
    /* stub */
    static matrix<3,1,float> _ret; return _ret;
}

matrix<3,1,float> DoCollideBySphere(matrix<3,1,float> * __$ReturnUdt, matrix<3,1,float> * _position, matrix<3,1,float> * _velocityVector, float _sphere_radius, matrix<3,1,float> _radiusVector, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * _polygonList, uint _collisionType, uchar _filterPulseJumps)
{
    /* stub */
    static matrix<3,1,float> _ret; return _ret;
}

void CalculateNormal(matrix<3,1,float> * normal, matrix<3,1,float> tA, matrix<3,1,float> tB, matrix<3,1,float> tC)
{
    /* stub */
}

bool isPointInsideEdge(matrix<3,1,float> * a, matrix<3,1,float> * b, matrix<3,1,float> * p)
{
    /* stub */
    return FALSE;
}

bool Line_Pass_Tri(matrix<3,1,float> start, matrix<3,1,float> end, matrix<3,1,float> tA, matrix<3,1,float> tN)
{
    /* stub */
    return FALSE;
}

matrix<3,1,float> DoCollideByRay(matrix<3,1,float> * __$ReturnUdt, matrix<3,1,float> * _position, matrix<3,1,float> * _velocityVector, matrix<3,1,float> _radiusVector, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * _polygonList, uint _collisionType, uchar _filterPulseJumps)
{
    /* stub */
    static matrix<3,1,float> _ret; return _ret;
}

