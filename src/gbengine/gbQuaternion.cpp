/**
 * gbQuaternion - Quaternion class implementation
 *
 * Matching decompilation of gbengine.dll gbQuaternion methods.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * Memory layout: { float x, y, z, w } (16 bytes)
 *   x=+0x00, y=+0x04, z=+0x08, w=+0x0C
 *
 * Convention: (x,y,z) is the vector part, w is the scalar part.
 * Unit quaternion: x^2 + y^2 + z^2 + w^2 == 1
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

gbQuaternion::gbQuaternion(void)
{
    z = 0.0f;
    y = 0.0f;
    x = 0.0f;
    w = 1.0f;
}

void gbQuaternion::SetUnit(void)
{
    w = 1.0f;
    z = 0.0f;
    y = 0.0f;
    x = 0.0f;
}

gbQuaternion &gbQuaternion::operator=(const gbQuaternion &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

int gbQuaternion::IsNormal(void)
{
    float mag = Magnitude();
    if (fabs(mag - 1.0f) < 0.005) {
        return 1;
    }
    return 0;
}

static float s_fHalf = 0.5f;
static float s_fDeg2Rad = 0.017453292f;

void gbQuaternion::SetAxisAngle(gbVec3D *axis, float angle)
{
    float halfRad = angle * s_fHalf * s_fDeg2Rad;
    w = (float)cos(halfRad);
    float s = (float)sin(halfRad);
    x = s * axis->x;
    y = s * axis->y;
    z = s * axis->z;
}

void gbQuaternion::GetAxisAngle(gbVec3D *axis, float *angle)
{
    float halfAngle = (float)acos(w) * 57.295776f;
    if (halfAngle > 1e-05) {
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

bool const gbQuaternion::IsValid(void) const
{
    if (this == NULL) return false;
    if (x * x < 0.0f) return false;
    if (y * y < 0.0f) return false;
    if (z * z < 0.0f) return false;
    if (w * w < 0.0f) return false;
    return true;
}

bool const gbQuaternion::IsUnit(void) const
{
    float lenSq = x * x + y * y + z * z + w * w;
    if (lenSq < 1.005 && lenSq > 0.995) {
        return true;
    }
    return false;
}

void gbQuaternion::SetVec3D(float scalar, gbVec3D *vec)
{
    w = scalar;
    x = vec->x;
    y = vec->y;
    z = vec->z;
}

void gbQuaternion::GetVec3D(float *scalar, gbVec3D *vec)
{
    *scalar = w;
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

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
    float *pm = (float *)mat->m;
    if (pm[i * 5] < mat->m[2][2]) {
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
    q[3] = (pm[i + k * 4] - pm[k + i * 4]) * s;
    q[j] = (pm[j + i * 4] + pm[i + j * 4]) * s;
    q[k] = (pm[k + i * 4] + pm[i + k * 4]) * s;

    x = q[0];
    y = q[1];
    z = q[2];
    w = q[3];
}

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

void gbQuaternion::SetYawPitchRoll(float yaw, float pitch, float roll)
{
    gbQuaternion qPitch, qYaw, qRoll, temp;
    gbVec3D axisX; axisX.x = 1.0f; axisX.y = 0.0f; axisX.z = 0.0f;
    gbVec3D axisY; axisY.x = 0.0f; axisY.y = 1.0f; axisY.z = 0.0f;
    gbVec3D axisZ; axisZ.x = 0.0f; axisZ.y = 0.0f; axisZ.z = 1.0f;

    qPitch.SetAxisAngle(&axisX, pitch);
    qYaw.SetAxisAngle(&axisY, yaw);
    qRoll.SetAxisAngle(&axisZ, roll);

    qPitch.MultiplyBy(&qYaw, &temp);
    temp.MultiplyBy(&qRoll, this);
}

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

void gbQuaternion::MultiplyBy(gbQuaternion *other, gbQuaternion *result)
{
    float ax = x;
    float ay = y;
    float az = z;
    float aw = w;
    float bx = other->x;
    float by = other->y;
    float bz = other->z;
    float bw = other->w;

    result->w = ((bw * aw - bx * ax) - by * ay) - bz * az;
    result->x = ((bz * ay + ax * bw) + bx * aw) - az * by;
    result->y = ((by * aw - bz * ax) + az * bx) + ay * bw;
    result->z = ((by * ax + bz * aw) - ay * bx) + az * bw;
}

float const gbQuaternion::Magnitude(void)
{
    return x * x + y * y + z * z + w * w;
}

float gbQuaternion::Normalize(void)
{
    float mag = Magnitude();
    float len = (float)sqrt(mag);
    if (len < 1e-05 && len > -1e-05) {
        return 0.0f;
    }
    float invLen = 1.0f / len;
    w = invLen * w;
    x = invLen * x;
    y = invLen * y;
    z = invLen * z;
    return len;
}

void gbQuaternion::Inverse(void)
{
    x = -x;
    y = -y;
    z = -z;
}

void gbQuaternion::RotateVector(gbVec3D *in, gbVec3D *out)
{
    gbMatrix4 mat;
    memset(&mat, 0, sizeof(mat));
    mat.m[0][0] = 1.0f;
    mat.m[1][1] = 1.0f;
    mat.m[2][2] = 1.0f;
    mat.m[3][3] = 1.0f;
    GetMatrix(&mat);
    out->x = mat.m[0][0] * in->x + mat.m[1][0] * in->y + mat.m[2][0] * in->z;
    out->y = mat.m[0][1] * in->x + mat.m[1][1] * in->y + mat.m[2][1] * in->z;
    out->z = mat.m[0][2] * in->x + mat.m[1][2] * in->y + mat.m[2][2] * in->z;
}
