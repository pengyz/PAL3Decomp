#ifndef PAL3A_COLLIDEPACK_H
#define PAL3A_COLLIDEPACK_H

#include "pal3a_types.h"

class collision {
public:
    char _data[1];

    void traceCollision(std::vector<sCollision,std::allocator<sCollision> > * cl);
    std::vector<struct sCollision,class std::allocator<struct sCollision> > calcColliders(void* __$ReturnUdt, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * polygonList);
    matrix<3,1,float> collideAndSlide(void* __$ReturnUdt, matrix<3,1,float> * radiusVector, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * polygonList, Collide_Ray<3,float> * r, matrix<3,1,float> * lastDir, uchar * bCollide);
    matrix<3,1,float> collideAndStop(void* __$ReturnUdt, matrix<3,1,float> * radiusVector, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * polygonList);
    bool isEmbedded(primitive<3,float> * p, matrix<3,1,float> * sphereCenter, matrix<3,1,float> * innerMostPoint);
    bool unitSphereIntersection(matrix<3,1,float> * center, Collide_Ray<3,float> * r, float * time);
};

float frand();
matrix<3,1,float> closestPointOnLineSegment(void* __$ReturnUdt, matrix<3,1,float> * a, matrix<3,1,float> * b, matrix<3,1,float> * p);
float GetPlaneDistance(matrix<3,1,float> V, matrix<3,1,float> tA, matrix<3,1,float> tN);
matrix<3,1,float> closestPointOnLine(void* __$ReturnUdt, matrix<3,1,float> * a, matrix<3,1,float> * b);
matrix<3,1,float> DoCollideBySphere(matrix<3,1,float> * __$ReturnUdt, matrix<3,1,float> * _position, matrix<3,1,float> * _velocityVector, float _sphere_radius, matrix<3,1,float> _radiusVector, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * _polygonList, uint _collisionType, uchar _filterPulseJumps);
void CalculateNormal(matrix<3,1,float> * normal, matrix<3,1,float> tA, matrix<3,1,float> tB, matrix<3,1,float> tC);
bool isPointInsideEdge(matrix<3,1,float> * a, matrix<3,1,float> * b, matrix<3,1,float> * p);
bool Line_Pass_Tri(matrix<3,1,float> start, matrix<3,1,float> end, matrix<3,1,float> tA, matrix<3,1,float> tN);
matrix<3,1,float> DoCollideByRay(matrix<3,1,float> * __$ReturnUdt, matrix<3,1,float> * _position, matrix<3,1,float> * _velocityVector, matrix<3,1,float> _radiusVector, std::vector<primitive<3,float>,std::allocator<primitive<3,float> > > * _polygonList, uint _collisionType, uchar _filterPulseJumps);

#endif // PAL3A_COLLIDEPACK_H
