/**
 * gbVec3D - 3D Vector class implementation
 *
 * Matching decompilation of gbengine.dll gbVec3D methods.
 * Compiler: MSVC 6.0 SP5, /O2
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

#define GB_FLOAT_EPSILON 0.005

float gbVec3D::Length(void) const
{
    /* STUB */
    return sqrtf(x * x + y * y + z * z);
}

bool gbVec3D::IsValid(void) const
{
    if (x * x < 0.0f) return false;
    if (y * y < 0.0f) return false;
    if (z * z < 0.0f) return false;
    return true;
}

void gbVec3D::Normalize(void)
{
    float len = Length();
    if (fabs(len) < GB_FLOAT_EPSILON) {
        z = 0.0f;
        x = 0.0f;
        y = 1.0f;
        return;
    }
    x = x / len;
    y = y / len;
    z = z / len;
}

gbVec3D::gbVec3D(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

void gbVec3D::operator=(const gbVec3D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

void gbVec3D::operator+=(const gbVec3D &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}

void gbVec3D::operator-=(const gbVec3D &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

void gbVec3D::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
}

void gbVec3D::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
}

bool gbVec3D::operator==(const gbVec3D &other)
{
    /* STUB */
    return (x == other.x && y == other.y && z == other.z);
}

gbVec3D gbVec3D::operator-(void) const
{
    gbVec3D result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    return result;
}

float gbVec3D::LengthSquare(void) const
{
    /* STUB */
    return x * x + y * y + z * z;
}

float gbVec3D::DotProduct(const gbVec3D *other) const
{
    /* STUB */
    return other->x * x + other->y * y + other->z * z;
}

int gbVec3D::IsNormal(void)
{
    float lenSq = x * x + y * y + z * z;
    if (fabs(lenSq - 1.0f) < GB_FLOAT_EPSILON) {
        return 1;
    }
    return 0;
}

void gbVec3D::Inverse(void)
{
    x = -x;
    y = -y;
    z = -z;
}

void gbVec3D::Zero(void)
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}
