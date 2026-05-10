#pragma once
// Auto-generated: sCollision

#include "CollisionType.h"

class sCollision {
public:
    primitive<3,float> * collider; // +0x0
    Collide_Ray<3,float> collisionPlane; // +0x4
    float collisionDistance; // +0x38
    CollisionType collisionType; // +0x3C
    // total size: 0x40 (64)

};
