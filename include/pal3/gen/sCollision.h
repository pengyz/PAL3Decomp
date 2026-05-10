#pragma once
// Auto-generated: sCollision

#include "CollisionType.h"

class sCollision {
public:
    char collider[4]; // +0x0 (primitive<3,float> *)
    char collisionPlane[52]; // +0x4 (Collide_Ray<3,float>)
    float collisionDistance; // +0x38
    CollisionType collisionType; // +0x3C
    // total size: 0x40 (64)

};
