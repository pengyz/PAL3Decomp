/**
 * gbVec3D - 3D Vector class implementation
 *
 * Matching decompilation of topo.dll gbVec3D methods.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * Verified against: topo.dll (ImageBase 0x10000000)
 */

#include "pal3.h"
#include <math.h>

// MSVC 6.0 uses 0.005 as the epsilon threshold
// Stored as a double constant at 0x100120f8 in topo.dll
#define GB_FLOAT_EPSILON 0.005

// ============================================================================
// gbVec3D struct (12 bytes: 3 floats)
// ============================================================================
// struct gbVec3D {
//     float x, y, z;
// };

// ============================================================================
// 0x10001000  Length  (33 bytes)
// public: float __thiscall gbVec3D::Length(void)const
// ============================================================================
float gbVec3D::Length(void) const
{
    return sqrtf(x * x + y * y + z * z);
}

// ============================================================================
// 0x10001030  IsValid  (77 bytes)
// public: bool __thiscall gbVec3D::IsValid(void)const
//
// Checks that squaring each component doesn't produce a negative result,
// which detects NaN/Inf values (NaN * NaN is NaN, which compares as < 0
// in the x87 FPU with the flags used).
// ============================================================================
bool gbVec3D::IsValid(void) const
{
    if (x * x < 0.0f) return false;
    if (y * y < 0.0f) return false;
    if (z * z < 0.0f) return false;
    return true;
}

// ============================================================================
// 0x10001080  CrossProduct  (57 bytes)
// public: void __thiscall gbVec3D::CrossProduct(struct gbVec3D const *,struct gbVec3D *)const
// ============================================================================
void gbVec3D::CrossProduct(const gbVec3D *other, gbVec3D *result) const
{
    result->x = y * other->z - other->y * z;
    result->y = other->x * z - x * other->z;
    result->z = other->y * x - other->x * y;
}

// ============================================================================
// 0x100010C0  Normalize  (75 bytes)
// public: void __thiscall gbVec3D::Normalize(void)
// ============================================================================
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

// ============================================================================
// 0x10001470  gbVec3D(float,float,float)  (20 bytes)
// public: __thiscall gbVec3D::gbVec3D(float,float,float)
// ============================================================================
gbVec3D::gbVec3D(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

// ============================================================================
// 0x10001490  operator=  (20 bytes)
// public: void __thiscall gbVec3D::operator=(struct gbVec3D const &)
// ============================================================================
void gbVec3D::operator=(const gbVec3D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

// ============================================================================
// 0x100014B0  operator+=  (24 bytes)
// public: void __thiscall gbVec3D::operator+=(struct gbVec3D const &)
// ============================================================================
void gbVec3D::operator+=(const gbVec3D &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}

// ============================================================================
// 0x100014D0  operator-=  (24 bytes)
// public: void __thiscall gbVec3D::operator-=(struct gbVec3D const &)
// ============================================================================
void gbVec3D::operator-=(const gbVec3D &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

// ============================================================================
// 0x10001550  operator*=  (21 bytes)
// public: void __thiscall gbVec3D::operator*=(float)
// ============================================================================
void gbVec3D::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
}

// ============================================================================
// 0x10001570  operator/=  (21 bytes)
// public: void __thiscall gbVec3D::operator/=(float)
// ============================================================================
void gbVec3D::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
}

// ============================================================================
// 0x10001590  operator==  (30 bytes)
// public: bool __thiscall gbVec3D::operator==(struct gbVec3D const &)
// ============================================================================
bool gbVec3D::operator==(const gbVec3D &other)
{
    return (x == other.x && y == other.y && z == other.z);
}

// ============================================================================
// 0x10001600  operator- (unary)  (30 bytes)
// public: struct gbVec3D __thiscall gbVec3D::operator-(void)const
// ============================================================================
gbVec3D gbVec3D::operator-(void) const
{
    gbVec3D result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    return result;
}

// ============================================================================
// 0x10001680  LengthSquare  (23 bytes)
// public: float __thiscall gbVec3D::LengthSquare(void)const
// ============================================================================
float gbVec3D::LengthSquare(void) const
{
    return x * x + y * y + z * z;
}

// ============================================================================
// 0x100016A0  DotProduct  (27 bytes)
// public: float __thiscall gbVec3D::DotProduct(struct gbVec3D const *)const
// ============================================================================
float gbVec3D::DotProduct(const gbVec3D *other) const
{
    return other->x * x + other->y * y + other->z * z;
}

// ============================================================================
// 0x100016C0  IsNormal  (60 bytes)
// public: int __thiscall gbVec3D::IsNormal(void)
// Checks if vector length squared is approximately 1.0
// Uses LengthSquare inline instead of calling Length() to avoid sqrtf
// ============================================================================
int gbVec3D::IsNormal(void)
{
    float lenSq = x * x + y * y + z * z;
    if (fabs(lenSq - 1.0f) < GB_FLOAT_EPSILON) {
        return 1;
    }
    return 0;
}

// ============================================================================
// 0x10001730  Inverse  (24 bytes)
// public: void __thiscall gbVec3D::Inverse(void)
// ============================================================================
void gbVec3D::Inverse(void)
{
    x = -x;
    y = -y;
    z = -z;
}

// ============================================================================
// 0x10001750  Zero  (16 bytes)
// public: void __thiscall gbVec3D::Zero(void)
// ============================================================================
void gbVec3D::Zero(void)
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}
