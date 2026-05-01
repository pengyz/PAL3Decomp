/**
 * gbengine.dll - gbMath
 * Math library implementation for gbengine
 * Includes: gbVec3D, gbMatrix4, gbRotMatrix, gbQuaternion, BEZIER, collision primitives
 */

#include <windows.h>
#include <math.h>
#include <string.h>
#include <float.h>

// ========== Forward Declarations ==========
struct gbVec3D;
struct gbMatrix4;
struct gbRotMatrix;
struct gbQuaternion;
struct gbRay;
struct gbAABBox;
struct gbOBBox;
struct gbSphere;
struct gbPlane;
class BEZIER;
class gbMatrixStack;

enum gbAxis { GB_AXIS_X = 0, GB_AXIS_Y = 1, GB_AXIS_Z = 2 };

// ========== gbVec3D ==========
struct gbVec3D {
    float x, y, z;

    // 0x10001f20 (25B) - Constructor
    gbVec3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    gbVec3D() : x(0), y(0), z(0) {}

    // 0x10001f40 (20B) - operator=
    gbVec3D& operator=(const gbVec3D& v) {
        x = v.x; y = v.y; z = v.z;
        return *this;
    }

    // 0x10001f60 (74B) - operator-=
    gbVec3D& operator-=(const gbVec3D& v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }

    // 0x10001fc0 (75B) - operator==
    bool operator==(const gbVec3D& v) const {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    // 0x10002010 (91B) - operator-
    gbVec3D operator-(const gbVec3D& v) const {
        return gbVec3D(x - v.x, y - v.y, z - v.z);
    }

    // 0x10002050 (29B) - LengthSquare
    float LengthSquare() const {
        return x * x + y * y + z * z;
    }

    // 0x10002070 (27B) - DotProduct
    float DotProduct(const gbVec3D* v) const {
        return x * v->x + y * v->y + z * v->z;
    }

    // 0x10002090 (73B) - IsNormal
    bool IsNormal() const {
        float lenSq = x * x + y * y + z * z;
        return (lenSq >= 0.99f && lenSq <= 1.01f);
    }

    // 0x100020d0 (26B) - Inverse
    void Inverse() {
        x = -x; y = -y; z = -z;
    }

    // 0x100020f0 (15B) - Zero
    void Zero() {
        x = 0; y = 0; z = 0;
    }

    // 0x10002110 (25B) - operator()
    void operator()(float _x, float _y, float _z) {
        x = _x; y = _y; z = _z;
    }

    // 0x10002150 (42B) - IsNormal (duplicate signature, different threshold?)
    bool IsValid() const {
        return (x != 0.0f || y != 0.0f || z != 0.0f);
    }

    // 0x10002180 (29B) - SetUnit
    void SetUnit() {
        x = 0; y = 1.0f; z = 0;
    }

    // 0x10024fe0 (33B) - Length
    float Length() const {
        return sqrtf(x * x + y * y + z * z);
    }

    // 0x10025060 (57B) - CrossProduct
    void CrossProduct(const gbVec3D* v, gbVec3D* result) const {
        result->x = y * v->z - v->y * z;
        result->y = v->x * z - x * v->z;
        result->z = v->y * x - v->x * y;
    }

    // 0x100250a0 (97B) - Normalize
    void Normalize() {
        float len = sqrtf(x * x + y * y + z * z);
        if (fabsf(len) < 0.005f) {
            x = 0; y = 1.0f; z = 0;
            return;
        }
        x /= len; y /= len; z /= len;
    }
};

// ========== gbMatrix4 ==========
struct gbMatrix4 {
    float m[4][4];

    // 0x10025110 (34B) - Constructor
    gbMatrix4() {
        memset(m, 0, sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }

    // 0x10025140 (20B) - operator=
    gbMatrix4& operator=(const gbMatrix4& mat) {
        memcpy(m, mat.m, sizeof(m));
        return *this;
    }

    // 0x10025160 (126B) - RightMultiply
    void RightMultiply(const gbMatrix4& mat) {
        float temp[16];
        memcpy(temp, m, sizeof(temp));
        float* a = temp;
        const float* b = &mat.m[0][0];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++) {
                    sum += a[i * 4 + k] * b[k * 4 + j];
                }
                m[i][j] = sum;
            }
        }
    }

    // 0x10025260 (90B) - Transform (gbVec3D -> gbVec3D)
    void Transform(const gbVec3D& v, gbVec3D* result) const {
        result->x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0];
        result->y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1];
        result->z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2];
    }

    // 0x100252c0 (126B) - Transform (gbVec3D* array)
    void Transform(gbVec3D* verts, int count) const {
        for (int i = 0; i < count; i++) {
            gbVec3D temp = verts[i];
            verts[i].x = m[0][0] * temp.x + m[1][0] * temp.y + m[2][0] * temp.z + m[3][0];
            verts[i].y = m[0][1] * temp.x + m[1][1] * temp.y + m[2][1] * temp.z + m[3][1];
            verts[i].z = m[0][2] * temp.x + m[1][2] * temp.y + m[2][2] * temp.z + m[3][2];
        }
    }

    // 0x10025340 (187B) - Transform_W (with W component)
    void Transform_W(const gbVec3D& v, gbVec3D* result, float* w) const {
        result->x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0];
        result->y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1];
        result->z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2];
        *w = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3];
    }

    // 0x10025400 (122B) - Transform (direction vector, no translation)
    void Transform(const gbVec3D& v, gbVec3D* result, int flag) const {
        result->x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z;
        result->y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z;
        result->z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z;
    }

    // 0x10025480 (93B) - Rotate (vector transformation)
    void Rotate(const gbVec3D& v, gbVec3D* result) const {
        result->x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z;
        result->y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z;
        result->z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z;
    }

    // 0x100254e0 (79B) - RotateIn (inverse rotation)
    void RotateIn(const gbVec3D& v, gbVec3D* result) const {
        result->x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
        result->y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
        result->z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
    }

    // 0x10025530 (257B) - TransformPlane
    void TransformPlane(const gbPlane* plane, gbPlane* result) const;

    // 0x10025640 (29B) - LoadIdentity
    void LoadIdentity() {
        memset(m, 0, sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }

    // 0x10025660 (61B) - IsIdentity
    bool IsIdentity() const {
        return m[0][0] == 1.0f && m[1][1] == 1.0f && m[2][2] == 1.0f && m[3][3] == 1.0f &&
               m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
               m[1][0] == 0.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
               m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][3] == 0.0f &&
               m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f;
    }

    // 0x100256a0 (47B) - IsValid
    bool IsValid() const {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (!isfinite(m[i][j])) return false;
        return true;
    }

    // 0x100256d0 (565B) - IsOrthonormal
    bool IsOrthonormal() const {
        gbVec3D r0(m[0][0], m[0][1], m[0][2]);
        gbVec3D r1(m[1][0], m[1][1], m[1][2]);
        gbVec3D r2(m[2][0], m[2][1], m[2][2]);
        float len0 = r0.Length();
        float len1 = r1.Length();
        float len2 = r2.Length();
        if (fabsf(len0 - 1.0f) > 0.01f) return false;
        if (fabsf(len1 - 1.0f) > 0.01f) return false;
        if (fabsf(len2 - 1.0f) > 0.01f) return false;
        if (fabsf(r0.DotProduct(&r1)) > 0.01f) return false;
        if (fabsf(r0.DotProduct(&r2)) > 0.01f) return false;
        if (fabsf(r1.DotProduct(&r2)) > 0.01f) return false;
        return true;
    }

    // 0x10025910 (140B) - SetAxisAngle (gbAxis, angle)
    void SetAxisAngle(gbAxis axis, float angle) {
        LoadIdentity();
        float rad = angle * 0.017453292f;
        float c = cosf(rad);
        float s = sinf(rad);
        if (axis == GB_AXIS_X) {
            m[1][1] = c; m[1][2] = s;
            m[2][1] = -s; m[2][2] = c;
        } else if (axis == GB_AXIS_Y) {
            m[0][0] = c; m[0][2] = -s;
            m[2][0] = s; m[2][2] = c;
        } else {
            m[0][0] = c; m[0][1] = s;
            m[1][0] = -s; m[1][1] = c;
        }
    }

    // 0x100259a0 (43B) - SetAxisAngle (gbVec3D, angle)
    void SetAxisAngle(const gbVec3D& axis, float angle) {
        float rad = angle * 0.017453292f;
        float c = cosf(rad);
        float s = sinf(rad);
        float t = 1.0f - c;
        float x = axis.x, y = axis.y, z = axis.z;

        m[0][0] = t * x * x + c;
        m[0][1] = t * x * y + s * z;
        m[0][2] = t * x * z - s * y;
        m[0][3] = 0;

        m[1][0] = t * x * y - s * z;
        m[1][1] = t * y * y + c;
        m[1][2] = t * y * z + s * x;
        m[1][3] = 0;

        m[2][0] = t * x * z + s * y;
        m[2][1] = t * y * z - s * x;
        m[2][2] = t * z * z + c;
        m[2][3] = 0;

        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1.0f;
    }

    // 0x100259d0 (72B) - SetAxisAngle (short form)
    void SetAxisAngle(float angle, const gbVec3D& axis) {
        SetAxisAngle(axis, angle);
    }

    // 0x10025a20 (402B) - Invert
    void Invert() {
        float temp[16];
        memcpy(temp, m, sizeof(temp));
        float* a = temp;

        float m00 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
        float m01 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
        float m02 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

        float det = 1.0f / (m00 * a[0] - m01 * a[4] + m02 * a[8]);

        m[0][0] = m00 * det;
        m[0][1] = -(a[1] * a[10] - a[2] * a[9]) * det;
        m[0][2] = (a[1] * a[6] - a[2] * a[5]) * det;
        m[0][3] = 0;

        m[1][0] = -m01 * det;
        m[1][1] = (a[0] * a[10] - a[2] * a[8]) * det;
        m[1][2] = -(a[0] * a[6] - a[2] * a[4]) * det;
        m[1][3] = 0;

        m[2][0] = m02 * det;
        m[2][1] = -(a[0] * a[9] - a[1] * a[8]) * det;
        m[2][2] = (a[0] * a[5] - a[1] * a[4]) * det;
        m[2][3] = 0;

        m[3][0] = -(m[1][0] * a[13] + m[2][0] * a[14] + m[0][0] * a[12]);
        m[3][1] = -(m[1][1] * a[13] + m[2][1] * a[14] + m[0][1] * a[12]);
        m[3][2] = -(m[1][2] * a[13] + m[2][2] * a[14] + m[0][2] * a[12]);
        m[3][3] = 1.0f;
    }

    // 0x10025bc0 (349B) - Invert (affine)
    void Invert(int flag) {
        Invert();
    }

    // 0x10025d20 (63B) - Transpose
    void Transpose() {
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                float temp = m[i][j];
                m[i][j] = m[j][i];
                m[j][i] = temp;
            }
        }
    }

    // 0x10025d60 (47B) - Transpose (to result)
    void Transpose(gbMatrix4* result) const {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result->m[i][j] = m[j][i];
    }

    // 0x10025d90 (307B) - MakeMatrix (from position, rotation, scale)
    void MakeMatrix(const gbVec3D* pos, const gbRotMatrix* rot, const gbVec3D* scale);

    // 0x10025ed0 (416B) - RightMultiply (optimized)
    void RightMultiply(const gbMatrix4* mat, int flag) {
        RightMultiply(*mat);
    }

    // 0x10026070 (92B) - LeftTranslate (gbVec3D)
    void LeftTranslate(const gbVec3D& v) {
        m[3][0] += v.x;
        m[3][1] += v.y;
        m[3][2] += v.z;
    }

    // 0x100260d0 (92B) - LeftTranslate (x, y, z)
    void LeftTranslate(float x, float y, float z) {
        m[3][0] += x;
        m[3][1] += y;
        m[3][2] += z;
    }

    // 0x10026130 (44B) - RightTranslate (gbVec3D)
    void RightTranslate(const gbVec3D& v) {
        m[3][0] += m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z;
        m[3][1] += m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z;
        m[3][2] += m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z;
    }

    // 0x10026160 (44B) - RightTranslate (x, y, z)
    void RightTranslate(float x, float y, float z) {
        RightTranslate(gbVec3D(x, y, z));
    }

    // 0x10026190 (119B) - RightScale
    void RightScale(const gbVec3D& v) {
        for (int i = 0; i < 3; i++) {
            m[0][i] *= v.x;
            m[1][i] *= v.y;
            m[2][i] *= v.z;
        }
    }

    // 0x10026210 (91B) - LeftScale
    void LeftScale(const gbVec3D& v) {
        for (int i = 0; i < 4; i++) {
            m[i][0] *= v.x;
            m[i][1] *= v.y;
            m[i][2] *= v.z;
        }
    }

    // 0x10026270 (38B) - GetRow (gbVec3D)
    void GetRow(int row, gbVec3D* v) const {
        v->x = m[row][0];
        v->y = m[row][1];
        v->z = m[row][2];
    }

    // 0x100262a0 (38B) - GetColumn (gbVec3D)
    void GetColumn(int col, gbVec3D* v) const {
        v->x = m[0][col];
        v->y = m[1][col];
        v->z = m[2][col];
    }

    // 0x100262d0 (29B) - GetRow (pointer)
    const float* GetRow(int row) const {
        return &m[row][0];
    }

    // 0x100262f0 (25B) - GetColumn (pointer - requires temp storage)
    void GetColumn(int col, float* v) const {
        v[0] = m[0][col];
        v[1] = m[1][col];
        v[2] = m[2][col];
        v[3] = m[3][col];
    }
};

// ========== gbRotMatrix ==========
struct gbRotMatrix {
    float m[3][3];

    // 0x10026310 (28B) - Constructor
    gbRotMatrix() {
        memset(m, 0, sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = 1.0f;
    }

    // 0x10026330 (152B) - operator=
    gbRotMatrix& operator=(const gbRotMatrix& mat) {
        memcpy(m, mat.m, sizeof(m));
        return *this;
    }

    // operator*= (implied, not found in exports)
    gbRotMatrix& operator*=(const gbRotMatrix& mat) {
        float temp[9];
        memcpy(temp, m, sizeof(temp));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                float sum = 0.0f;
                for (int k = 0; k < 3; k++) {
                    sum += temp[i * 3 + k] * mat.m[k][j];
                }
                m[i][j] = sum;
            }
        }
        return *this;
    }

    // 0x100263d0 (87B) - Rotate (transform vector)
    void Rotate(const gbVec3D& v, gbVec3D* result) const {
        result->x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z;
        result->y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z;
        result->z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z;
    }

    // 0x10026430 (29B) - LoadIdentity
    void LoadIdentity() {
        memset(m, 0, sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = 1.0f;
    }

    // 0x10026450 (47B) - IsValid
    bool IsValid() const {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!isfinite(m[i][j])) return false;
        return true;
    }

    // 0x10026480 (494B) - IsOrthonormal
    bool IsOrthonormal() const {
        gbVec3D r0(m[0][0], m[0][1], m[0][2]);
        gbVec3D r1(m[1][0], m[1][1], m[1][2]);
        gbVec3D r2(m[2][0], m[2][1], m[2][2]);
        float len0 = r0.Length();
        float len1 = r1.Length();
        float len2 = r2.Length();
        if (fabsf(len0 - 1.0f) > 0.01f) return false;
        if (fabsf(len1 - 1.0f) > 0.01f) return false;
        if (fabsf(len2 - 1.0f) > 0.01f) return false;
        if (fabsf(r0.DotProduct(&r1)) > 0.01f) return false;
        if (fabsf(r0.DotProduct(&r2)) > 0.01f) return false;
        if (fabsf(r1.DotProduct(&r2)) > 0.01f) return false;
        return true;
    }
};

// ========== gbQuaternion ==========
struct gbQuaternion {
    float x, y, z, w;

    // 0x10002130 (20B) - Constructor
    gbQuaternion() : x(0), y(0), z(0), w(1.0f) {}

    gbQuaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

    // 0x100021a0 (20B) - operator=
    gbQuaternion& operator=(const gbQuaternion& q) {
        x = q.x; y = q.y; z = q.z; w = q.w;
        return *this;
    }

    // 0x10026670 (220B) - SetYawPitchRoll
    void SetYawPitchRoll(float yaw, float pitch, float roll) {
        float cy = cosf(yaw * 0.5f * 0.017453292f);
        float sy = sinf(yaw * 0.5f * 0.017453292f);
        float cp = cosf(pitch * 0.5f * 0.017453292f);
        float sp = sinf(pitch * 0.5f * 0.017453292f);
        float cr = cosf(roll * 0.5f * 0.017453292f);
        float sr = sinf(roll * 0.5f * 0.017453292f);

        w = cy * cp * cr + sy * sp * sr;
        x = cy * cp * sr - sy * sp * cr;
        y = sy * cp * sr + cy * sp * cr;
        z = sy * cp * cr - cy * sp * sr;
    }

    // 0x10026750 (252B) - SetTwoVector
    void SetTwoVector(const gbVec3D* from, const gbVec3D* to) {
        gbVec3D axis;
        from->CrossProduct(to, &axis);
        axis.Normalize();

        float dot = from->DotProduct(to);
        float angle = acosf(dot);

        SetAxisAngle(axis, angle * 57.295776f);
    }

    // 0x10026850 (60B) - SetAxisAngle
    void SetAxisAngle(const gbVec3D& axis, float angle) {
        float halfAngle = angle * 0.5f * 0.017453292f;
        float s = sinf(halfAngle);
        x = axis.x * s;
        y = axis.y * s;
        z = axis.z * s;
        w = cosf(halfAngle);
    }

    // 0x10026890 (122B) - GetAxisAngle
    void GetAxisAngle(gbVec3D* axis, float* angle) const {
        float scale = sqrtf(x * x + y * y + z * z);
        if (scale < 0.0001f) {
            axis->x = 0; axis->y = 1.0f; axis->z = 0;
            *angle = 0;
        } else {
            axis->x = x / scale;
            axis->y = y / scale;
            axis->z = z / scale;
            *angle = 2.0f * acosf(w) * 57.295776f;
        }
    }

    // 0x10026910 (106B) - IsValid
    bool IsValid() const {
        return isfinite(x) && isfinite(y) && isfinite(z) && isfinite(w);
    }

    // 0x10026980 (75B) - IsUnit
    bool IsUnit() const {
        float mag = x * x + y * y + z * z + w * w;
        return (mag >= 0.99f && mag <= 1.01f);
    }

    // 0x100269d0 (29B) - SetVec3D
    void SetVec3D(const gbVec3D& v) {
        x = v.x; y = v.y; z = v.z;
    }

    // 0x100269f0 (29B) - GetVec3D
    void GetVec3D(gbVec3D* v) const {
        v->x = x; v->y = y; v->z = z;
    }

    // 0x10026a10 (334B) - SetMatrix
    void SetMatrix(const gbMatrix4* mat) {
        float trace = mat->m[0][0] + mat->m[1][1] + mat->m[2][2];

        if (trace > 0.0f) {
            float s = sqrtf(trace + 1.0f) * 2.0f;
            w = 0.25f * s;
            x = (mat->m[2][1] - mat->m[1][2]) / s;
            y = (mat->m[0][2] - mat->m[2][0]) / s;
            z = (mat->m[1][0] - mat->m[0][1]) / s;
        } else if (mat->m[0][0] > mat->m[1][1] && mat->m[0][0] > mat->m[2][2]) {
            float s = sqrtf(1.0f + mat->m[0][0] - mat->m[1][1] - mat->m[2][2]) * 2.0f;
            w = (mat->m[2][1] - mat->m[1][2]) / s;
            x = 0.25f * s;
            y = (mat->m[0][1] + mat->m[1][0]) / s;
            z = (mat->m[0][2] + mat->m[2][0]) / s;
        } else if (mat->m[1][1] > mat->m[2][2]) {
            float s = sqrtf(1.0f + mat->m[1][1] - mat->m[0][0] - mat->m[2][2]) * 2.0f;
            w = (mat->m[0][2] - mat->m[2][0]) / s;
            x = (mat->m[0][1] + mat->m[1][0]) / s;
            y = 0.25f * s;
            z = (mat->m[1][2] + mat->m[2][1]) / s;
        } else {
            float s = sqrtf(1.0f + mat->m[2][2] - mat->m[0][0] - mat->m[1][1]) * 2.0f;
            w = (mat->m[1][0] - mat->m[0][1]) / s;
            x = (mat->m[0][2] + mat->m[2][0]) / s;
            y = (mat->m[1][2] + mat->m[2][1]) / s;
            z = 0.25f * s;
        }
    }

    // 0x10026b60 (222B) - GetMatrix
    void GetMatrix(gbMatrix4* mat) const {
        float xx = x * x, yy = y * y, zz = z * z;
        float xy = x * y, xz = x * z, yz = y * z;
        float wx = w * x, wy = w * y, wz = w * z;

        mat->m[0][0] = 1.0f - 2.0f * (yy + zz);
        mat->m[0][1] = 2.0f * (xy + wz);
        mat->m[0][2] = 2.0f * (xz - wy);
        mat->m[0][3] = 0;

        mat->m[1][0] = 2.0f * (xy - wz);
        mat->m[1][1] = 1.0f - 2.0f * (xx + zz);
        mat->m[1][2] = 2.0f * (yz + wx);
        mat->m[1][3] = 0;

        mat->m[2][0] = 2.0f * (xz + wy);
        mat->m[2][1] = 2.0f * (yz - wx);
        mat->m[2][2] = 1.0f - 2.0f * (xx + yy);
        mat->m[2][3] = 0;

        mat->m[3][0] = 0;
        mat->m[3][1] = 0;
        mat->m[3][2] = 0;
        mat->m[3][3] = 1.0f;
    }

    // 0x10026c40 (320B) - Slerp
    void Slerp(const gbQuaternion* from, const gbQuaternion* to, float t) {
        float dot = from->x * to->x + from->y * to->y + from->z * to->z + from->w * to->w;

        gbQuaternion temp;
        if (dot >= 0.0f) {
            temp = *to;
        } else {
            dot = -dot;
            temp.x = -to->x;
            temp.y = -to->y;
            temp.z = -to->z;
            temp.w = -to->w;
        }

        float scale0, scale1;
        if (1.0f - dot <= 1e-05f) {
            scale0 = 1.0f - t;
            scale1 = t;
        } else {
            float theta = acosf(dot);
            float sinTheta = sinf(theta);
            scale0 = sinf((1.0f - t) * theta) / sinTheta;
            scale1 = sinf(t * theta) / sinTheta;
        }

        x = scale0 * from->x + scale1 * temp.x;
        y = scale0 * from->y + scale1 * temp.y;
        z = scale0 * from->z + scale1 * temp.z;
        w = scale0 * from->w + scale1 * temp.w;
    }

    // 0x10026d80 (235B) - MultiplyBy
    void MultiplyBy(const gbQuaternion& q) {
        float tx = w * q.x + x * q.w + y * q.z - z * q.y;
        float ty = w * q.y + y * q.w + z * q.x - x * q.z;
        float tz = w * q.z + z * q.w + x * q.y - y * q.x;
        float tw = w * q.w - x * q.x - y * q.y - z * q.z;
        x = tx; y = ty; z = tz; w = tw;
    }

    // 0x10026e70 (42B) - Magnitude
    float Magnitude() const {
        return sqrtf(x * x + y * y + z * z + w * w);
    }

    // 0x10026ea0 (124B) - Normalize
    void Normalize() {
        float mag = sqrtf(x * x + y * y + z * z + w * w);
        if (mag < 0.0001f) {
            x = 0; y = 0; z = 0; w = 1.0f;
        } else {
            x /= mag; y /= mag; z /= mag; w /= mag;
        }
    }

    // 0x10026f20 (29B) - Inverse
    void Inverse() {
        x = -x; y = -y; z = -z;
    }

    // 0x10026f40 (66B) - RotateVector
    void RotateVector(const gbVec3D& v, gbVec3D* result) const {
        gbQuaternion qv(v.x, v.y, v.z, 0);
        gbQuaternion qinv(-x, -y, -z, w);
        gbQuaternion temp = *this;
        temp.MultiplyBy(qv);
        temp.MultiplyBy(qinv);
        result->x = temp.x;
        result->y = temp.y;
        result->z = temp.z;
    }
};

// ========== gbPlane ==========
struct gbPlane {
    gbVec3D normal;
    float d;

    gbPlane() : normal(0, 1.0f, 0), d(0) {}

    gbPlane(const gbVec3D& n, float _d) : normal(n), d(_d) {}

    gbPlane& operator=(const gbPlane& p) {
        normal = p.normal;
        d = p.d;
        return *this;
    }

    bool IsColAABB(const gbAABBox* box) const;
    bool IsColOBB(const gbOBBox* box) const;
};

// Forward declare TransformPlane implementation
void gbMatrix4::TransformPlane(const gbPlane* plane, gbPlane* result) const {
    gbMatrix4 invTranspose = *this;
    invTranspose.Invert();
    invTranspose.Transpose();

    invTranspose.Transform(plane->normal, &result->normal, 0);
    result->normal.Normalize();

    gbVec3D pointOnPlane(plane->normal.x * -plane->d,
                         plane->normal.y * -plane->d,
                         plane->normal.z * -plane->d);
    gbVec3D transformedPoint;
    Transform(pointOnPlane, &transformedPoint);

    result->d = -result->normal.DotProduct(&transformedPoint);
}

// 0x10025d90 (307B) - MakeMatrix implementation
void gbMatrix4::MakeMatrix(const gbVec3D* pos, const gbRotMatrix* rot, const gbVec3D* scale) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m[i][j] = rot->m[i][j];
        }
    }

    if (scale) {
        for (int i = 0; i < 3; i++) {
            m[i][0] *= scale->x;
            m[i][1] *= scale->y;
            m[i][2] *= scale->z;
        }
    }

    m[3][0] = pos->x;
    m[3][1] = pos->y;
    m[3][2] = pos->z;

    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 1.0f;
}

// ========== gbRay ==========
struct gbRay {
    gbVec3D origin;
    gbVec3D direction;

    gbRay() {}

    gbRay(const gbVec3D& o, const gbVec3D& d) : origin(o), direction(d) {}

    gbRay& operator=(const gbRay& r) {
        origin = r.origin;
        direction = r.direction;
        return *this;
    }

    // 0x100281d0 (139B) - IntersectPlane
    bool IntersectPlane(const gbPlane* plane, gbVec3D* point) const {
        float denom = direction.DotProduct(&plane->normal);
        if (fabsf(denom) < 0.0001f) return false;

        float t = -(origin.DotProduct(&plane->normal) + plane->d) / denom;
        if (t < 0) return false;

        point->x = origin.x + direction.x * t;
        point->y = origin.y + direction.y * t;
        point->z = origin.z + direction.z * t;
        return true;
    }

    bool IsColAABB(const gbAABBox* box, gbVec3D* point) const;
    bool IsColOBB(const gbOBBox* box, gbVec3D* point) const;
    bool IsColOBB_H(const gbOBBox* box) const;
    bool IsColQuad(const gbVec3D* v0, const gbVec3D* v1, const gbVec3D* v2, const gbVec3D* v3, gbVec3D* point) const;
    bool IsColSphere(const gbSphere* sphere, gbVec3D* point) const;
    bool IsColTriangle(const gbVec3D* v0, const gbVec3D* v1, const gbVec3D* v2, gbVec3D* point) const;
    bool IsColTriangle(const gbVec3D* v0, const gbVec3D* v1, const gbVec3D* v2, gbVec3D* point, gbVec3D* bary) const;
};

// ========== gbAABBox ==========
struct gbAABBox {
    gbVec3D vMin;
    gbVec3D vMax;

    gbAABBox() {}

    gbAABBox(const gbVec3D& min, const gbVec3D& max) : vMin(min), vMax(max) {}

    gbAABBox& operator=(const gbAABBox& box) {
        vMin = box.vMin;
        vMax = box.vMax;
        return *this;
    }

    bool IsColAABB(const gbAABBox* box) const {
        return (vMin.x <= box->vMax.x && vMax.x >= box->vMin.x &&
                vMin.y <= box->vMax.y && vMax.y >= box->vMin.y &&
                vMin.z <= box->vMax.z && vMax.z >= box->vMin.z);
    }

    // 0x10027860 (76B) - IsColPoint
    bool IsColPoint(const gbVec3D* point) const {
        return (point->x >= vMin.x && point->x <= vMax.x &&
                point->y >= vMin.y && point->y <= vMax.y &&
                point->z >= vMin.z && point->z <= vMax.z);
    }

    // 0x100279e0 (285B) - Transform
    void Transform(const gbMatrix4* mat) {
        gbVec3D corners[8];
        corners[0] = gbVec3D(vMin.x, vMin.y, vMin.z);
        corners[1] = gbVec3D(vMax.x, vMin.y, vMin.z);
        corners[2] = gbVec3D(vMin.x, vMax.y, vMin.z);
        corners[3] = gbVec3D(vMax.x, vMax.y, vMin.z);
        corners[4] = gbVec3D(vMin.x, vMin.y, vMax.z);
        corners[5] = gbVec3D(vMax.x, vMin.y, vMax.z);
        corners[6] = gbVec3D(vMin.x, vMax.y, vMax.z);
        corners[7] = gbVec3D(vMax.x, vMax.y, vMax.z);

        mat->Transform(corners[0], &corners[0]);
        vMin = vMax = corners[0];

        for (int i = 1; i < 8; i++) {
            mat->Transform(corners[i], &corners[i]);
            if (corners[i].x < vMin.x) vMin.x = corners[i].x;
            if (corners[i].y < vMin.y) vMin.y = corners[i].y;
            if (corners[i].z < vMin.z) vMin.z = corners[i].z;
            if (corners[i].x > vMax.x) vMax.x = corners[i].x;
            if (corners[i].y > vMax.y) vMax.y = corners[i].y;
            if (corners[i].z > vMax.z) vMax.z = corners[i].z;
        }
    }
};

// ========== gbOBBox ==========
struct gbOBBox {
    gbVec3D center;
    gbVec3D axis[3];
    gbVec3D extent;

    gbOBBox() : center(0, 0, 0), extent(1, 1, 1) {
        axis[0] = gbVec3D(1, 0, 0);
        axis[1] = gbVec3D(0, 1, 0);
        axis[2] = gbVec3D(0, 0, 1);
    }

    gbOBBox& operator=(const gbOBBox& box) {
        center = box.center;
        axis[0] = box.axis[0];
        axis[1] = box.axis[1];
        axis[2] = box.axis[2];
        extent = box.extent;
        return *this;
    }

    // 0x10027c00 (61B) - GetCenter
    void GetCenter(gbVec3D* v) const {
        *v = center;
    }

    // 0x10027c40 (245B) - IsColPoint
    bool IsColPoint(const gbVec3D* point) const {
        gbVec3D d(point->x - center.x, point->y - center.y, point->z - center.z);
        float proj[3];
        for (int i = 0; i < 3; i++) {
            proj[i] = d.DotProduct(&axis[i]);
            if (fabsf(proj[i]) > extent.x * (i == 0 ? 1.0f : (i == 1 ? 1.0f : 1.0f))) return false;
        }
        return true;
    }

    // 0x10027d10 (76B) - GetSphere
    void GetSphere(gbSphere* sphere) const;

    // 0x10027d60 (92B) - GetAABBox
    void GetAABBox(gbAABBox* box) const {
        gbVec3D e(
            extent.x * fabsf(axis[0].x) + extent.y * fabsf(axis[1].x) + extent.z * fabsf(axis[2].x),
            extent.x * fabsf(axis[0].y) + extent.y * fabsf(axis[1].y) + extent.z * fabsf(axis[2].y),
            extent.x * fabsf(axis[0].z) + extent.y * fabsf(axis[1].z) + extent.z * fabsf(axis[2].z)
        );
        box->vMin.x = center.x - e.x;
        box->vMin.y = center.y - e.y;
        box->vMin.z = center.z - e.z;
        box->vMax.x = center.x + e.x;
        box->vMax.y = center.y + e.y;
        box->vMax.z = center.z + e.z;
    }

    // 0x10027dc0 (43B) - GetRadius
    float GetRadius() const {
        return extent.Length();
    }

    // 0x10027df0 (208B) - GetRadiusInDirection
    float GetRadiusInDirection(const gbVec3D* dir) const {
        float r = 0;
        for (int i = 0; i < 3; i++) {
            float proj = fabsf(dir->DotProduct(&axis[i]));
            r += proj * (i == 0 ? extent.x : (i == 1 ? extent.y : extent.z));
        }
        return r;
    }

    // 0x10027ec0 (1009B) - IsColOBB
    bool IsColOBB(const gbOBBox* box) const;
};

// ========== gbSphere ==========
struct gbSphere {
    gbVec3D center;
    float radius;

    gbSphere() : center(0, 0, 0), radius(1.0f) {}

    gbSphere(const gbVec3D& c, float r) : center(c), radius(r) {}

    gbSphere& operator=(const gbSphere& s) {
        center = s.center;
        radius = s.radius;
        return *this;
    }

    // 0x10027b40 (89B) - IsColPoint
    bool IsColPoint(const gbVec3D* point) const {
        gbVec3D d(point->x - center.x, point->y - center.y, point->z - center.z);
        return d.LengthSquare() <= radius * radius;
    }

    // 0x100278b0 (97B) - IsColSphere
    bool IsColSphere(const gbSphere* sphere) const {
        gbVec3D d(sphere->center.x - center.x,
                  sphere->center.y - center.y,
                  sphere->center.z - center.z);
        float dist = d.Length();
        return dist <= (radius + sphere->radius);
    }

    // 0x10027920 (584B) - IsColTriangle
    bool IsColTriangle(const gbVec3D* v0, const gbVec3D* v1, const gbVec3D* v2) const {
        gbVec3D e0(v1->x - v0->x, v1->y - v0->y, v1->z - v0->z);
        gbVec3D e1(v2->x - v1->x, v2->y - v1->y, v2->z - v1->z);
        gbVec3D e2(v0->x - v2->x, v0->y - v2->y, v0->z - v2->z);

        gbVec3D normal;
        e0.CrossProduct(&e1, &normal);
        normal.Normalize();

        float dist = fabsf(normal.DotProduct(&center) - normal.DotProduct(v0));
        if (dist > radius) return false;

        // Additional edge and vertex checks would go here
        return true;
    }
};

// Implement gbOBBox::GetSphere
void gbOBBox::GetSphere(gbSphere* sphere) const {
    sphere->center = center;
    sphere->radius = extent.Length();
}

// ========== BEZIER ==========
class BEZIER {
private:
    float controlPoints[4][3];  // 4 control points, each with x,y,z
    int coefficients[4];         // Bezier coefficients
    int needsUpdate;             // Flag for recomputing coefficients

public:
    // 0x100241e0 (50B) - Constructor
    BEZIER(gbVec3D* points) {
        memset(controlPoints, 0, sizeof(controlPoints));
        for (int i = 0; i < 4; i++) {
            controlPoints[i][0] = points[i].x;
            controlPoints[i][1] = points[i].y;
            controlPoints[i][2] = points[i].z;
        }
        needsUpdate = 1;
    }

    // 0x10024220 (45B) - Constructor (default)
    BEZIER() {
        memset(controlPoints, 0, sizeof(controlPoints));
        needsUpdate = 1;
    }

    ~BEZIER() {}

    // operator=
    BEZIER& operator=(const BEZIER& b) {
        memcpy(controlPoints, b.controlPoints, sizeof(controlPoints));
        memcpy(coefficients, b.coefficients, sizeof(coefficients));
        needsUpdate = b.needsUpdate;
        return *this;
    }

    // GetControlPt
    void GetControlPt(int index, gbVec3D* point) const {
        point->x = controlPoints[index][0];
        point->y = controlPoints[index][1];
        point->z = controlPoints[index][2];
    }

    // 0x10024250 (29B) - SetControlPt
    void SetControlPt(int index, const gbVec3D* point) {
        controlPoints[index][0] = point->x;
        controlPoints[index][1] = point->y;
        controlPoints[index][2] = point->z;
        needsUpdate = 1;
    }

    // 0x100241c0 (29B) - computerCoefficient
    void computerCoefficient() {
        coefficients[0] = 1;
        coefficients[1] = 3;
        coefficients[2] = 3;
        coefficients[3] = 1;
        needsUpdate = 0;
    }

    // 0x10024270 (233B) - getInterpolatePoint
    gbVec3D getInterpolatePoint(float t) {
        if (needsUpdate) {
            computerCoefficient();
        }

        gbVec3D result(0, 0, 0);
        float u = 1.0f - t;

        for (int i = 0; i <= 3; i++) {
            float tPow = powf(t, (float)i);
            float uPow = powf(u, (float)(3 - i));
            float blend = (float)coefficients[i] * tPow * uPow;

            result.x += controlPoints[i][0] * blend;
            result.y += controlPoints[i][1] * blend;
            result.z += controlPoints[i][2] * blend;
        }

        return result;
    }

    // 0x10024360 (238B) - getTangentVector
    gbVec3D getTangentVector(float t) {
        if (needsUpdate) {
            computerCoefficient();
        }

        gbVec3D result(0, 0, 0);

        for (int i = 0; i < 3; i++) {
            gbVec3D p0(controlPoints[i][0], controlPoints[i][1], controlPoints[i][2]);
            gbVec3D p1(controlPoints[i + 1][0], controlPoints[i + 1][1], controlPoints[i + 1][2]);
            gbVec3D diff = p1 - p0;

            float tPow = powf(t, (float)i);
            float uPow = powf(1.0f - t, (float)(2 - i));
            float blend = 3.0f * tPow * uPow;

            result.x += diff.x * blend;
            result.y += diff.y * blend;
            result.z += diff.z * blend;
        }

        result.Normalize();
        return result;
    }
};

// ========== gbMatrixStack (from original file) ==========
class gbMatrixStack {
public:
    gbMatrix4 *m_pStack;
    int m_nMaxDepth;
    int m_nCurrent;
    int m_bDirty;

    // 0x10026fe0 (149B)
    gbMatrixStack(int nMaxDepth) {
        m_nMaxDepth = nMaxDepth;
        m_nCurrent = 0;
        m_pStack = (gbMatrix4 *)operator new(nMaxDepth * sizeof(gbMatrix4));
        if (m_pStack) {
            float *p = (float *)&m_pStack[0];
            for (int i = 0; i < 16; i++)
                p[i] = 0.0f;
            p[0] = 1.0f;
            p[5] = 1.0f;
            p[10] = 1.0f;
            p[15] = 1.0f;
        }
    }

    // 0x10027080 (10B)
    ~gbMatrixStack() {
        operator delete(m_pStack);
    }

    // 0x10027090 (41B)
    void Push() {
        float *src = (float *)&m_pStack[m_nCurrent];
        float *dst = (float *)&m_pStack[m_nCurrent + 1];
        for (int i = 16; i != 0; i--) {
            *dst = *src;
            src++;
            dst++;
        }
        m_nCurrent++;
    }

    // 0x100270c0 (15B)
    void Pop() {
        m_bDirty = 0;
        m_nCurrent--;
    }

    // 0x100270d0 (51B)
    void LoadIdentity() {
        float *p = (float *)&m_pStack[m_nCurrent];
        for (int i = 16; i != 0; i--) {
            *p = 0.0f;
            p++;
        }
        float *top = (float *)&m_pStack[m_nCurrent];
        top[0] = 1.0f;
        top[5] = 1.0f;
        top[10] = 1.0f;
        top[15] = 1.0f;
    }

    // 0x10027110 (37B)
    void LoadMatrix(gbMatrix4 *pMat) {
        float *dst = (float *)&m_pStack[m_nCurrent];
        float *src = (float *)pMat;
        for (int i = 16; i != 0; i--) {
            *dst = *src;
            src++;
            dst++;
        }
    }

    // 0x10027140 (145B)
    void MultMatrix(gbMatrix4 *pMat) {
        float result[16];
        float *a = (float *)&m_pStack[m_nCurrent];
        float *b = (float *)pMat;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++) {
                    sum += a[i * 4 + k] * b[k * 4 + j];
                }
                result[i * 4 + j] = sum;
            }
        }
        float *dst = (float *)&m_pStack[m_nCurrent];
        for (int i = 0; i < 16; i++) {
            dst[i] = result[i];
        }
    }

    // 0x100271e0 (276B)
    void Rotate(float angle, gbVec3D &axis) {
        float rad = angle * 0.017453292f;
        float c = (float)cos(rad);
        float s = (float)sin(rad);
        float t = 1.0f - c;
        float x = axis.x, y = axis.y, z = axis.z;

        gbMatrix4 rot;
        float *r = (float *)&rot;
        for (int i = 0; i < 16; i++) r[i] = 0.0f;
        r[0]  = t * x * x + c;
        r[1]  = t * x * y + s * z;
        r[2]  = t * x * z - s * y;
        r[4]  = t * x * y - s * z;
        r[5]  = t * y * y + c;
        r[6]  = t * y * z + s * x;
        r[8]  = t * x * z + s * y;
        r[9]  = t * y * z - s * x;
        r[10] = t * z * z + c;
        r[15] = 1.0f;

        MultMatrix(&rot);
    }

    // 0x10027300 (221B)
    void Rotate(gbQuaternion &q) {
        float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
        float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
        float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

        gbMatrix4 rot;
        float *r = (float *)&rot;
        for (int i = 0; i < 16; i++) r[i] = 0.0f;
        r[0]  = 1.0f - 2.0f * (yy + zz);
        r[1]  = 2.0f * (xy + wz);
        r[2]  = 2.0f * (xz - wy);
        r[4]  = 2.0f * (xy - wz);
        r[5]  = 1.0f - 2.0f * (xx + zz);
        r[6]  = 2.0f * (yz + wx);
        r[8]  = 2.0f * (xz + wy);
        r[9]  = 2.0f * (yz - wx);
        r[10] = 1.0f - 2.0f * (xx + yy);
        r[15] = 1.0f;

        MultMatrix(&rot);
    }

    // 0x100273e0 (104B)
    void Translate(gbVec3D &v) {
        float *p = (float *)&m_pStack[m_nCurrent];
        p[12] = p[0] * v.x + p[4] * v.y + p[8]  * v.z + p[12];
        p[13] = p[1] * v.x + p[5] * v.y + p[9]  * v.z + p[13];
        p[14] = p[2] * v.x + p[6] * v.y + p[10] * v.z + p[14];
    }

    // 0x100274b0 (112B)
    void Translate(float x, float y, float z) {
        float *p = (float *)&m_pStack[m_nCurrent];
        p[12] = x * p[0] + z * p[8]  + y * p[4]  + p[12];
        p[13] = z * p[9]  + y * p[5]  + x * p[1]  + p[13];
        p[14] = z * p[10] + y * p[6]  + x * p[2]  + p[14];
    }

    // 0x10027450 (96B)
    void Scale(gbVec3D &v) {
        float *p = (float *)&m_pStack[m_nCurrent];
        p[0] *= v.x; p[1] *= v.x; p[2] *= v.x;
        p[4] *= v.y; p[5] *= v.y; p[6] *= v.y;
        p[8] *= v.z; p[9] *= v.z; p[10] *= v.z;
    }

    // 0x10027520 (108B)
    void Scale(float x, float y, float z) {
        float *p = (float *)&m_pStack[m_nCurrent];
        p[0] *= x; p[1] *= x; p[2] *= x;
        p[4] *= y; p[5] *= y; p[6] *= y;
        p[8] *= z; p[9] *= z; p[10] *= z;
    }

    // 0x10027590 (11B)
    gbMatrix4 *GetTop() {
        return &m_pStack[m_nCurrent];
    }
};

// ========== Collision and Free Functions ==========

// 0x10028f80 (1067B) - gbIntersectTriangle
extern "C" int __cdecl gbIntersectTriangle(
    gbVec3D* rayOrigin, gbVec3D* rayDir,
    gbVec3D* v0, gbVec3D* v1, gbVec3D* v2,
    gbVec3D* intersection)
{
    // Compute edge vectors
    gbVec3D e1(v1->x - v0->x, v1->y - v0->y, v1->z - v0->z);
    gbVec3D e2(v2->x - v0->x, v2->y - v0->y, v2->z - v0->z);

    // Compute normal
    gbVec3D normal;
    e1.CrossProduct(&e2, &normal);

    // Compute ray parameter t
    gbVec3D toOrigin(rayOrigin->x - v0->x, rayOrigin->y - v0->y, rayOrigin->z - v0->z);
    float nDotRay = normal.DotProduct(rayDir);

    if (fabsf(nDotRay) < 0.0001f) return 0;

    float t = -normal.DotProduct(&toOrigin) / nDotRay;

    if (t < 0.0f || t > 1.0f) return 0;

    // Compute intersection point
    intersection->x = rayOrigin->x + rayDir->x * t;
    intersection->y = rayOrigin->y + rayDir->y * t;
    intersection->z = rayOrigin->z + rayDir->z * t;

    // Check if point is inside triangle using barycentric coordinates
    gbVec3D v0v1(v1->x - v0->x, v1->y - v0->y, v1->z - v0->z);
    gbVec3D v0v2(v2->x - v0->x, v2->y - v0->y, v2->z - v0->z);
    gbVec3D v0p(intersection->x - v0->x, intersection->y - v0->y, intersection->z - v0->z);

    gbVec3D cross1, cross2, cross3;
    v0v1.CrossProduct(&v0v2, &cross1);
    v0v1.CrossProduct(&v0p, &cross2);
    v0p.CrossProduct(&v0v2, &cross3);

    float d1 = normal.DotProduct(&cross2);
    float d2 = normal.DotProduct(&cross3);

    if (d1 >= 0.0f && d2 >= 0.0f) {
        gbVec3D v1v2(v2->x - v1->x, v2->y - v1->y, v2->z - v1->z);
        gbVec3D v1p(intersection->x - v1->x, intersection->y - v1->y, intersection->z - v1->z);
        gbVec3D cross4;
        v1v2.CrossProduct(&v1p, &cross4);
        float d3 = normal.DotProduct(&cross4);
        if (d3 >= 0.0f) {
            return 1;
        }
    }

    return 0;
}

// Placeholder implementations for forward-declared collision functions
bool gbPlane::IsColAABB(const gbAABBox* box) const {
    // Simple plane-AABB test
    gbVec3D center((box->vMin.x + box->vMax.x) * 0.5f,
                   (box->vMin.y + box->vMax.y) * 0.5f,
                   (box->vMin.z + box->vMax.z) * 0.5f);
    gbVec3D extent((box->vMax.x - box->vMin.x) * 0.5f,
                   (box->vMax.y - box->vMin.y) * 0.5f,
                   (box->vMax.z - box->vMin.z) * 0.5f);

    float r = extent.x * fabsf(normal.x) + extent.y * fabsf(normal.y) + extent.z * fabsf(normal.z);
    float s = normal.DotProduct(&center) + d;

    return fabsf(s) <= r;
}

bool gbPlane::IsColOBB(const gbOBBox* box) const {
    float r = box->extent.x * fabsf(normal.DotProduct(&box->axis[0])) +
              box->extent.y * fabsf(normal.DotProduct(&box->axis[1])) +
              box->extent.z * fabsf(normal.DotProduct(&box->axis[2]));

    float s = normal.DotProduct(&box->center) + d;
    return fabsf(s) <= r;
}

bool gbOBBox::IsColOBB(const gbOBBox* box) const {
    // Separating Axis Theorem (SAT) for OBB-OBB collision
    // Simplified implementation
    gbVec3D T(box->center.x - center.x, box->center.y - center.y, box->center.z - center.z);

    // Test axes from this OBB
    for (int i = 0; i < 3; i++) {
        float ra = (i == 0 ? extent.x : (i == 1 ? extent.y : extent.z));
        float rb = box->extent.x * fabsf(axis[i].DotProduct(&box->axis[0])) +
                   box->extent.y * fabsf(axis[i].DotProduct(&box->axis[1])) +
                   box->extent.z * fabsf(axis[i].DotProduct(&box->axis[2]));
        if (fabsf(T.DotProduct(&axis[i])) > ra + rb) return false;
    }

    // Test axes from other OBB
    for (int i = 0; i < 3; i++) {
        float ra = extent.x * fabsf(box->axis[i].DotProduct(&axis[0])) +
                   extent.y * fabsf(box->axis[i].DotProduct(&axis[1])) +
                   extent.z * fabsf(box->axis[i].DotProduct(&axis[2]));
        float rb = (i == 0 ? box->extent.x : (i == 1 ? box->extent.y : box->extent.z));
        if (fabsf(T.DotProduct(&box->axis[i])) > ra + rb) return false;
    }

    return true;
}

bool gbRay::IsColAABB(const gbAABBox* box, gbVec3D* point) const {
    float tmin = -FLT_MAX, tmax = FLT_MAX;

    for (int i = 0; i < 3; i++) {
        float o = ((float*)&origin)[i];
        float d = ((float*)&direction)[i];
        float bmin = ((float*)&box->vMin)[i];
        float bmax = ((float*)&box->vMax)[i];

        if (fabsf(d) < 0.0001f) {
            if (o < bmin || o > bmax) return false;
        } else {
            float t1 = (bmin - o) / d;
            float t2 = (bmax - o) / d;
            if (t1 > t2) { float temp = t1; t1 = t2; t2 = temp; }
            tmin = (t1 > tmin) ? t1 : tmin;
            tmax = (t2 < tmax) ? t2 : tmax;
            if (tmin > tmax) return false;
        }
    }

    if (point && tmin >= 0) {
        point->x = origin.x + direction.x * tmin;
        point->y = origin.y + direction.y * tmin;
        point->z = origin.z + direction.z * tmin;
    }

    return tmin >= 0;
}

bool gbRay::IsColOBB(const gbOBBox* box, gbVec3D* point) const {
    return false; // Placeholder
}

bool gbRay::IsColOBB_H(const gbOBBox* box) const {
    return false; // Placeholder
}

bool gbRay::IsColQuad(const gbVec3D* v0, const gbVec3D* v1, const gbVec3D* v2, const gbVec3D* v3, gbVec3D* point) const {
    return IsColTriangle(v0, v1, v2, point) || IsColTriangle(v0, v2, v3, point);
}

bool gbRay::IsColSphere(const gbSphere* sphere, gbVec3D* point) const {
    gbVec3D m(origin.x - sphere->center.x, origin.y - sphere->center.y, origin.z - sphere->center.z);
    float b = m.DotProduct(&direction);
    float c = m.DotProduct(&m) - sphere->radius * sphere->radius;

    if (c > 0.0f && b > 0.0f) return false;

    float discr = b * b - c;
    if (discr < 0.0f) return false;

    float t = -b - sqrtf(discr);
    if (t < 0.0f) t = 0.0f;

    if (point) {
        point->x = origin.x + direction.x * t;
        point->y = origin.y + direction.y * t;
        point->z = origin.z + direction.z * t;
    }

    return true;
}

bool gbRay::IsColTriangle(const gbVec3D* v0, const gbVec3D* v1, const gbVec3D* v2, gbVec3D* point) const {
    return gbIntersectTriangle((gbVec3D*)&origin, (gbVec3D*)&direction,
                              (gbVec3D*)v0, (gbVec3D*)v1, (gbVec3D*)v2, point) != 0;
}

bool gbRay::IsColTriangle(const gbVec3D* v0, const gbVec3D* v1, const gbVec3D* v2, gbVec3D* point, gbVec3D* bary) const {
    if (!IsColTriangle(v0, v1, v2, point)) return false;

    // Compute barycentric coordinates
    gbVec3D e1(v1->x - v0->x, v1->y - v0->y, v1->z - v0->z);
    gbVec3D e2(v2->x - v0->x, v2->y - v0->y, v2->z - v0->z);
    gbVec3D p(point->x - v0->x, point->y - v0->y, point->z - v0->z);

    float d00 = e1.DotProduct(&e1);
    float d01 = e1.DotProduct(&e2);
    float d11 = e2.DotProduct(&e2);
    float d20 = p.DotProduct(&e1);
    float d21 = p.DotProduct(&e2);

    float denom = d00 * d11 - d01 * d01;
    bary->y = (d11 * d20 - d01 * d21) / denom;
    bary->z = (d00 * d21 - d01 * d20) / denom;
    bary->x = 1.0f - bary->y - bary->z;

    return true;
}
