/**
 * gbQuaternion - Quaternion class implementation
 *
 * Matching decompilation of topo.dll gbQuaternion methods.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * Verified against: topo.dll (ImageBase 0x10000000)
 *
 * Memory layout: { float x, y, z, w } (16 bytes)
 *   x=+0x00, y=+0x04, z=+0x08, w=+0x0C
 *
 * Convention: (x,y,z) is the vector part, w is the scalar part.
 * Unit quaternion: x^2 + y^2 + z^2 + w^2 == 1
 */

#include "pal3.h"
#include <math.h>

// FUN_10009bb0 is acos() - wrapper around CRT acos
extern "C" float acos(float);

// Constants used:
// 0x10012100 = 1.0f
// 0x10012104 = 0.017453292f (PI/180)
// 0x100120f0 = 0.0f (as dword)
// 0x100120f8 = 0.005 (double, GB_FLOAT_EPSILON)
// 0x10012108 = 57.295776f (180/PI)
// 0x1001210c = 0.5f
// 0x10012110 = 1e-05 (double)
// 0x10012118 = 0.995 (double)
// 0x10012120 = 1.005 (double)
// 0x10012128 = 1.0 (double)
// 0x10012130 = 0.0 (double)
// 0x10012138 = -1e-05 (double)

// ============================================================================
// 0x100018F0  gbQuaternion()  (20 bytes)
// public: __thiscall gbQuaternion::gbQuaternion(void)
// ============================================================================
gbQuaternion::gbQuaternion(void)
{
    z = 0.0f;
    y = 0.0f;
    x = 0.0f;
    w = 1.0f;
}

// ============================================================================
// 0x100019D0  SetUnit  (18 bytes)
// public: void __thiscall gbQuaternion::SetUnit(void)
// ============================================================================
void gbQuaternion::SetUnit(void)
{
    w = 1.0f;
    z = 0.0f;
    y = 0.0f;
    x = 0.0f;
}

// ============================================================================
// 0x100019F0  operator=  (35 bytes)
// public: struct gbQuaternion & __thiscall gbQuaternion::operator=(struct gbQuaternion const &)
// Note: shared implementation with gbMatrixStack::operator=
// ============================================================================
gbQuaternion &gbQuaternion::operator=(const gbQuaternion &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

// ============================================================================
// 0x100019A0  IsNormal  (35 bytes)
// public: int __thiscall gbQuaternion::IsNormal(void)
//
// Checks if the quaternion has unit magnitude (within epsilon).
// ============================================================================
int gbQuaternion::IsNormal(void)
{
    float mag = Magnitude();
    if (fabs(mag - 1.0f) < 0.005) {
        return 1;
    }
    return 0;
}

// ============================================================================
// 0x10002640  SetAxisAngle(gbVec3D*, float)  (52 bytes)
// public: void __thiscall gbQuaternion::SetAxisAngle(struct gbVec3D *,float)
//
// Sets the quaternion from an axis and angle (degrees).
// q = (axis * sin(angle/2), cos(angle/2))
// ============================================================================
void gbQuaternion::SetAxisAngle(gbVec3D *axis, float angle)
{
    float halfRad = angle * 0.5f * 0.017453292f;
    w = (float)cos(halfRad);
    float s = (float)sin(halfRad);
    x = s * axis->x;
    y = s * axis->y;
    z = s * axis->z;
}

// ============================================================================
// 0x10002680  GetAxisAngle  (122 bytes)
// public: void __thiscall gbQuaternion::GetAxisAngle(struct gbVec3D *,float *)
//
// Extracts axis and angle (degrees) from the quaternion.
// ============================================================================
void gbQuaternion::GetAxisAngle(gbVec3D *axis, float *angle)
{
    float halfAngle = (float)acos(w) * 57.295776f;
    if (halfAngle > 1e-05f) {
        float invSin = 1.0f / (float)sin(halfAngle * 0.017453292f);
        axis->x = invSin * x;
        axis->y = invSin * y;
        axis->z = invSin * z;
        *angle = halfAngle + halfAngle;
    } else {
        axis->y = 0.0f;
        axis->x = 0.0f;
        axis->z = 1.0f;
        *angle = 0.0f;
    }
}

// ============================================================================
// 0x10002700  IsValid  (109 bytes)
// public: bool const __thiscall gbQuaternion::IsValid(void)const
//
// NaN check: each component squared must be >= 0.
// ============================================================================
bool gbQuaternion::IsValid(void) const
{
    if (this == NULL) return false;
    if (x * x < 0.0f) return false;
    if (y * y < 0.0f) return false;
    if (z * z < 0.0f) return false;
    if (w * w < 0.0f) return false;
    return true;
}

// ============================================================================
// 0x10002770  IsUnit  (75 bytes)
// public: bool const __thiscall gbQuaternion::IsUnit(void)const
//
// Checks if the quaternion length^2 is within [0.995, 1.005).
// ============================================================================
bool gbQuaternion::IsUnit(void) const
{
    float lenSq = x * x + y * y + z * z + w * w;
    if (lenSq < 1.005f && lenSq >= 0.995f) {
        return true;
    }
    return false;
}

// ============================================================================
// 0x100027C0  SetVec3D  (30 bytes)
// public: void __thiscall gbQuaternion::SetVec3D(float,struct gbVec3D *)
//
// Sets quaternion from scalar w and vector (x,y,z).
// ============================================================================
void gbQuaternion::SetVec3D(float scalar, gbVec3D *vec)
{
    w = scalar;
    x = vec->x;
    y = vec->y;
    z = vec->z;
}

// ============================================================================
// 0x100027E0  GetVec3D  (32 bytes)
// public: void __thiscall gbQuaternion::GetVec3D(float *,struct gbVec3D *)
//
// Extracts scalar w and vector part into separate outputs.
// ============================================================================
void gbQuaternion::GetVec3D(float *scalar, gbVec3D *vec)
{
    *scalar = w;
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

// ============================================================================
// 0x10002800  SetMatrix  (326 bytes)
// public: void __thiscall gbQuaternion::SetMatrix(struct gbMatrix4 *)
//
// Converts a rotation matrix to a quaternion.
// Uses the standard Shepperd method (trace-based with fallback).
// ============================================================================
void gbQuaternion::SetMatrix(gbMatrix4 *mat)
{
    int nxt[3] = { 1, 2, 0 };
    float trace = mat->m[0][0] + mat->m[1][1] + mat->m[2][2];

    if (trace > 0.0f) {
        float s = (float)sqrt(trace + 1.0f);
        w = s * 0.5f;
        s = 0.5f / s;
        x = (mat->m[1][2] - mat->m[2][1]) * s;
        y = (mat->m[2][0] - mat->m[0][2]) * s;
        z = (mat->m[0][1] - mat->m[1][0]) * s;
        return;
    }

    int i = (int)(mat->m[0][0] < mat->m[1][1]);
    if (mat->m[i * 4 + i] < mat->m[2][2]) {
        i = 2;
    }
    int j = nxt[i];
    int k = nxt[j];

    float q[4];
    float s = (float)sqrt(mat->m[i][i] - (mat->m[j][j] + mat->m[k][k]) + 1.0f);
    q[i] = s * 0.5f;
    if (s != 0.0f) {
        s = 0.5f / s;
    }
    q[3] = (mat->m[i + k * 4] - mat->m[k + i * 4]) * s;
    q[j] = (mat->m[j + i * 4] + mat->m[i + j * 4]) * s;
    q[k] = (mat->m[k + i * 4] + mat->m[i + k * 4]) * s;

    x = q[0];
    y = q[1];
    z = q[2];
    w = q[3];
}

// ============================================================================
// 0x10002950  GetMatrix  (211 bytes)
// public: void __thiscall gbQuaternion::GetMatrix(struct gbMatrix4 *)const
//
// Converts the quaternion to a 4x4 rotation matrix.
// Standard formula: 1-2(yy+zz), 2(xy+wz), 2(xz-wy), etc.
// ============================================================================
void gbQuaternion::GetMatrix(gbMatrix4 *mat) const
{
    float x2 = x + x;
    float xx = x2 * x;
    float xy = x2 * y;
    float xz = x2 * z;
    float xw = x2 * w;

    float y2 = y + y;
    float yy = y2 * y;
    float yz = y2 * z;
    float yw = y2 * w;

    float z2 = z + z;
    float zz = z2 * z;
    float zw = z2 * w;

    mat->m[3][3] = 1.0f;
    mat->m[3][2] = 0.0f;
    mat->m[3][1] = 0.0f;
    mat->m[3][0] = 0.0f;

    mat->m[0][0] = 1.0f - yy - zz;
    mat->m[0][1] = zw + xy;
    mat->m[0][2] = xz - yw;
    mat->m[1][0] = xy - zw;
    mat->m[1][1] = (1.0f - xx) - zz;
    mat->m[1][2] = yz + xw;
    mat->m[2][0] = yw + xz;
    mat->m[2][1] = yz - xw;
    mat->m[2][2] = (1.0f - xx) - yy;
}

// ============================================================================
// 0x10002490  SetYawPitchRoll  (304 bytes)
// public: void __thiscall gbQuaternion::SetYawPitchRoll(float,float,float)
//
// Builds quaternion from Euler angles (yaw, pitch, roll in degrees).
// Creates three axis-angle quaternions and multiplies them together.
// ============================================================================
void gbQuaternion::SetYawPitchRoll(float yaw, float pitch, float roll)
{
    gbQuaternion qPitch, qYaw, qRoll, temp;
    gbVec3D axisX = { 1.0f, 0.0f, 0.0f };
    gbVec3D axisY = { 0.0f, 1.0f, 0.0f };
    gbVec3D axisZ = { 0.0f, 0.0f, 1.0f };

    qPitch.SetAxisAngle(&axisX, pitch);
    qYaw.SetAxisAngle(&axisY, yaw);
    qRoll.SetAxisAngle(&axisZ, roll);

    qPitch.MultiplyBy(&qYaw, &temp);
    temp.MultiplyBy(&qRoll, this);
}

// ============================================================================
// 0x100025C0  SetTwoVector  (118 bytes)
// public: void __thiscall gbQuaternion::SetTwoVector(struct gbVec3D *,struct gbVec3D *)
//
// Sets quaternion representing rotation from one vector to another.
// Computes the cross product (rotation axis) and angle via dot product.
// ============================================================================
void gbQuaternion::SetTwoVector(gbVec3D *from, gbVec3D *to)
{
    gbVec3D axis;
    axis.x = 0.0f;
    axis.y = 0.0f;
    axis.z = 0.0f;

    from->CrossProduct(to, &axis);
    axis.Normalize();

    float dot = from->z * to->z + from->y * to->y + from->x * to->x;
    float angle = (float)acos(dot) * 57.295776f;
    SetAxisAngle(&axis, angle);
}

// ============================================================================
// 0x10002A30  Slerp  (320 bytes)
// public: void __thiscall gbQuaternion::Slerp(struct gbQuaternion *,struct gbQuaternion *,float)
//
// Spherical linear interpolation between two quaternions.
// this = slerp(q1, q2, t)
// ============================================================================
void gbQuaternion::Slerp(gbQuaternion *q1, gbQuaternion *q2, float t)
{
    float dot = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;

    float bx, by, bz, bw;
    if (dot >= 0.0f) {
        bx = q2->x;
        by = q2->y;
        bz = q2->z;
        bw = q2->w;
    } else {
        dot = -dot;
        bx = -q2->x;
        by = -q2->y;
        bz = -q2->z;
        bw = -q2->w;
    }

    float scaleA, scaleB;
    if (1.0f - dot <= 1e-05f) {
        scaleA = 1.0f - t;
        scaleB = t;
    } else {
        float omega = (float)acos(dot) * 57.295776f;
        float sinOmega = (float)sin(omega * 0.017453292f);
        scaleA = (float)sin((1.0f - t) * omega * 0.017453292f) / sinOmega;
        scaleB = (float)sin(omega * t * 0.017453292f) / sinOmega;
    }

    x = scaleA * q1->x + scaleB * bx;
    y = scaleA * q1->y + scaleB * by;
    z = scaleA * q1->z + scaleB * bz;
    w = scaleA * q1->w + scaleB * bw;
}

// ============================================================================
// 0x10002B70  MultiplyBy  (234 bytes)
// public: void __thiscall gbQuaternion::MultiplyBy(struct gbQuaternion *,struct gbQuaternion *)
//
// Quaternion multiplication: result = this * param_1
// Stores result in param_2.
// ============================================================================
void gbQuaternion::MultiplyBy(gbQuaternion *other, gbQuaternion *result)
{
    float ax = x, ay = y, az = z, aw = w;
    float bx = other->x, by = other->y, bz = other->z, bw = other->w;

    result->w = (bw * aw - bx * ax) - by * ay - bz * az;
    result->x = bx * aw + ax * bw + bz * ay - az * by;
    result->y = by * aw - bz * ax + az * bx + ay * bw;
    result->z = az * bw + (bz * aw + by * ax) - ay * bx;
}

// ============================================================================
// 0x10002C60  Magnitude  (42 bytes)
// public: float const __thiscall gbQuaternion::Magnitude(void)
//
// Returns the squared magnitude (x^2 + y^2 + z^2 + w^2).
// Note: Despite the name, this returns length^2, not length.
// ============================================================================
float gbQuaternion::Magnitude(void)
{
    return x * x + y * y + z * z + w * w;
}

// ============================================================================
// 0x10002C90  Normalize  (84 bytes)
// public: float __thiscall gbQuaternion::Normalize(void)
//
// Normalizes the quaternion to unit length.
// Returns the original length (sqrt of magnitude), or 0 if too small.
// ============================================================================
float gbQuaternion::Normalize(void)
{
    float mag = Magnitude();
    float len = (float)sqrt(mag);
    if (len < 1e-05f && len > -1e-05f) {
        return 0.0f;
    }
    float invLen = 1.0f / len;
    w = invLen * w;
    x = invLen * x;
    y = invLen * y;
    z = invLen * z;
    return len;
}

// ============================================================================
// 0x10002CF0  Inverse  (23 bytes)
// public: void __thiscall gbQuaternion::Inverse(void)
//
// Conjugate/inverse for unit quaternions: negates the vector part.
// ============================================================================
void gbQuaternion::Inverse(void)
{
    x = -x;
    y = -y;
    z = -z;
}

// ============================================================================
// 0x10002D10  RotateVector  (53 bytes)
// public: void __thiscall gbQuaternion::RotateVector(struct gbVec3D *,struct gbVec3D *)
//
// Rotates a vector by this quaternion (via matrix conversion).
// ============================================================================
void gbQuaternion::RotateVector(gbVec3D *in, gbVec3D *out)
{
    gbMatrix4 mat;
    GetMatrix(&mat);
    mat.Rotate(in, out);
}
