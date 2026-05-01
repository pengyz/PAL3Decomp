#pragma once

#include <windows.h>
#include <d3d9.h>

#ifdef GBENGINE_EXPORTS
#define GBAPI __declspec(dllexport)
#else
#define GBAPI __declspec(dllimport)
#endif

// Forward declarations for method parameters
struct gbQuaternion;
struct gbAABBox;
struct gbOBBox;
struct gbSphere;
class gbGfxManager;
class gbTexture;

enum gbAxis {
    GB_AXIS_X = 0,
    GB_AXIS_Y = 1,
    GB_AXIS_Z = 2
};

// Basic math types
struct gbVec2D {
    float x, y;
};

struct gbVec3D {
    float x, y, z;

    // Methods (auto-generated)
    gbVec3D() {}
    gbVec3D(float p0, float p1, float p2);
    void operator=(struct gbVec3D const & p0);
    bool operator==(struct gbVec3D const & p0);
    struct gbVec3D operator-() const;
    void operator*=(float p0);
    void operator+=(struct gbVec3D const & p0);
    void operator-=(struct gbVec3D const & p0);
    void operator/=(float p0);
    void CrossProduct(struct gbVec3D const * p0, struct gbVec3D * p1) const;
    float DotProduct(struct gbVec3D const * p0) const;
    void Inverse();
    int IsNormal();
    bool IsValid() const;
    float Length() const;
    float LengthSquare() const;
    void Normalize();
    void Zero();
};

struct gbVec4D {
    float x, y, z, w;
};

struct gbColorQuad {
    unsigned char b, g, r, a;

    // Methods (auto-generated)
    gbColorQuad(struct gbColorQuad & p0);
    gbColorQuad(unsigned char p0, unsigned char p1, unsigned char p2);
    gbColorQuad(unsigned char p0, unsigned char p1, unsigned char p2, unsigned char p3);
    gbColorQuad();
    struct gbColorQuad & operator=(struct gbColorQuad const & p0);
    static int ColorQuadFmt;
};

struct gbColorFlt {
    float r, g, b, a;

    // Methods (auto-generated)
    gbColorFlt(float p0, float p1, float p2);
    gbColorFlt(float p0, float p1, float p2, float p3);
    gbColorFlt();
    struct gbColorFlt & operator=(struct gbColorFlt const & p0);
    int operator!=(struct gbColorFlt & p0);
    void operator+=(struct gbColorFlt const & p0);
};

struct gbMatrix4 {
    float m[4][4];

    // Methods (auto-generated)
    gbMatrix4();
    void operator=(struct gbMatrix4 const & p0);
    float operator()(int p0, int p1);
    void operator*=(struct gbMatrix4 const & p0);
    void operator*=(struct gbQuaternion const & p0);
    void operator*=(float const * p0);
    struct gbVec3D * GetColumn(struct gbVec3D * p0, int p1) const;
    struct gbVec4D * GetColumn(struct gbVec4D * p0, int p1) const;
    struct gbVec3D * GetRow(struct gbVec3D * p0, int p1) const;
    struct gbVec4D * GetRow(struct gbVec4D * p0, int p1) const;
    void Invert();
    void Invert(struct gbMatrix4 * p0) const;
    bool IsIdentity() const;
    bool IsOrthonormal() const;
    bool IsValid() const;
    void LeftMultiply(struct gbMatrix4 const & p0);
    void LeftMultiply(struct gbQuaternion const & p0);
    void LeftScale(float p0, float p1, float p2);
    void LeftTranslate(struct gbVec3D & p0);
    void LeftTranslate(float p0, float p1, float p2);
    void LoadIdentity();
    void MakeMatrix(struct gbVec3D & p0, struct gbVec3D & p1, struct gbVec3D & p2);
    void RightMultiply(struct gbMatrix4 const & p0);
    void RightMultiply(struct gbQuaternion const & p0);
    void RightScale(float p0, float p1, float p2);
    void RightTranslate(struct gbVec3D & p0);
    void RightTranslate(float p0, float p1, float p2);
    void Rotate(struct gbVec3D const * p0, struct gbVec3D * p1) const;
    void RotateIn(struct gbVec3D * p0);
    void SetAxisAngle(struct gbVec3D * p0, float p1);
    void SetAxisAngle(enum gbAxis p0, float p1);
    void SetAxisAngle(enum gbAxis p0, float p1, float p2);
    void Transform(struct gbVec3D * p0, struct gbVec3D * p1, int p2) const;
    void Transform(struct gbVec3D * p0, int p1) const;
    void Transform(struct gbVec3D const * p0, struct gbVec3D * p1) const;
    void TransformPlane(float * const p0);
    void Transform_W(struct gbVec3D * p0, struct gbVec3D * p1, int p2) const;
    void Transpose();
    void Transpose(struct gbMatrix4 * p0) const;
};

struct gbRotMatrix {
    float m[3][3];

    // Methods (auto-generated)
    gbRotMatrix();
    void operator=(struct gbRotMatrix & p0);
    void operator*=(struct gbRotMatrix & p0);
    bool const IsOrthonormal();
    bool const IsValid();
    void LoadIdentity();
    void Rotate(struct gbVec3D * p0, struct gbVec3D * p1);
};

struct gbQuaternion {
    float x, y, z, w;

    // Methods (auto-generated)
    gbQuaternion();
    struct gbQuaternion & operator=(struct gbQuaternion const & p0);
    void GetAxisAngle(struct gbVec3D * p0, float * p1);
    void GetMatrix(struct gbMatrix4 * p0) const;
    void GetVec3D(float * p0, struct gbVec3D * p1);
    void Inverse();
    int IsNormal();
    bool const IsUnit() const;
    bool const IsValid() const;
    float const Magnitude();
    void MultiplyBy(struct gbQuaternion * p0, struct gbQuaternion * p1);
    float Normalize();
    void RotateVector(struct gbVec3D * p0, struct gbVec3D * p1);
    void SetAxisAngle(struct gbVec3D * p0, float p1);
    void SetMatrix(struct gbMatrix4 * p0);
    void SetTwoVector(struct gbVec3D * p0, struct gbVec3D * p1);
    void SetUnit();
    void SetVec3D(float p0, struct gbVec3D * p1);
    void SetYawPitchRoll(float p0, float p1, float p2);
    void Slerp(struct gbQuaternion * p0, struct gbQuaternion * p1, float p2);
};

struct gbRay {
    gbVec3D origin;
    gbVec3D direction;

    // Methods (auto-generated)
    gbRay();
    struct gbRay & operator=(struct gbRay const & p0);
    float IntersectPlane(struct gbVec3D & p0, struct gbVec3D & p1);
    int IsColAABB(struct gbAABBox & p0);
    int IsColOBB(struct gbOBBox & p0);
    int IsColOBB_H(struct gbOBBox & p0);
    int IsColQuad(struct gbVec3D & p0, struct gbVec3D & p1, struct gbVec3D & p2);
    int IsColSphere(struct gbSphere & p0);
    int IsColTriangle(struct gbVec3D & p0, struct gbVec3D & p1, struct gbVec3D & p2, struct gbVec3D & p3);
    int IsColTriangle(struct gbVec3D & p0, struct gbVec3D & p1, struct gbVec3D & p2);
};

struct gbAABBox {
    gbVec3D vMin;
    gbVec3D vMax;

    // Methods (auto-generated)
    gbAABBox();
    struct gbAABBox & operator=(struct gbAABBox const & p0);
    int IsColAABB(struct gbAABBox & p0);
    int IsColPoint(struct gbVec3D & p0);
    void Transform(struct gbMatrix4 * p0);
};

struct gbOBBox {
    gbMatrix4 matrix;    // axis directions in rows 0-2, center in row 3
    gbVec3D extent;      // half-extents at +0x40

    // Methods (auto-generated)
    gbOBBox();
    struct gbOBBox & operator=(struct gbOBBox const & p0);
    void GetAABBox(struct gbAABBox & p0);
    struct gbVec3D GetCenter() const;
    float GetRadius() const;
    float GetRadiusInDirection(struct gbVec3D const & p0) const;
    void GetSphere(struct gbSphere & p0);
    int IsColOBB(struct gbOBBox * p0);
    int IsColPoint(struct gbVec3D & p0);
};

struct gbSphere {
    gbVec3D center;
    float radius;

    // Methods (auto-generated)
    gbSphere();
    struct gbSphere & operator=(struct gbSphere const & p0);
    int IsColPoint(struct gbVec3D & p0);
    int IsColSphere(struct gbVec3D & p0, float p1);
    int IsColTriangle(struct gbVec3D & p0, struct gbVec3D & p1, struct gbVec3D & p2);
};

struct gbPlane {
    gbVec3D normal;
    float d;

    // Methods (auto-generated)
    gbPlane();
    struct gbPlane & operator=(struct gbPlane const & p0);
    int IsColAABB(struct gbAABBox & p0);
    int IsColOBB(struct gbOBBox & p0);
};

class gbUIRect {
public:
    gbTexture* m_pTexture;  // +0x00
    gbGfxManager* m_pGfx;  // +0x04
    float left;             // +0x08
    float top;              // +0x0C
    float width;            // +0x10
    float height;           // +0x14

    // Methods (auto-generated)
    gbUIRect & operator=(gbUIRect const & p0);
    void Init(char * p0, float p1, float p2, float p3, float p4, class gbGfxManager * p5);
    void Release();
    void Render(int p0);
};

enum gbPixelFmtType {
    GB_PFT_UNKNOWN = 0,
    GB_PFT_R8G8B8 = 1,
    GB_PFT_A8R8G8B8 = 2,
    GB_PFT_R5G6B5 = 3,
    GB_PFT_A1R5G5B5 = 4,
    GB_PFT_A4R4G4B4 = 5,
    GB_PFT_P8 = 6,
    GB_PFT_A8 = 7,
    GB_PFT_X8R8G8B8 = 8,
    GB_PFT_X1R5G5B5 = 9,
    GB_PFT_X4R4G4B4 = 10
};

class gbPixelFormat {
public:
    gbPixelFmtType Type;
    int Bpp;
    gbColorQuad* Pal;
    unsigned int r_mask;
    unsigned int g_mask;
    unsigned int b_mask;
    unsigned int a_mask;
    unsigned int r_shift;
    unsigned int g_shift;
    unsigned int b_shift;
    unsigned int a_shift;

    // Methods (auto-generated)
    gbPixelFormat & operator=(gbPixelFormat const & p0);
    void Convert(unsigned char * p0, gbPixelFormat * p1, unsigned char * p2, int p3);
    void Init(int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4);
    void Init(int p0, struct gbColorQuad * p1);
    void Init(gbPixelFormat * p0);
    void Init(enum gbPixelFmtType p0);
    void Release();
};

// Globals
extern double g_CurrentTime;
extern unsigned int g_CurrentTick;
