#pragma once
/**
 * Auto-generated from topo.dll export table
 * 100 exported functions
 *
 * NOTE: This is a reference file showing the DLL's API surface.
 * Parameter names are inferred and may not match original source.
 */

#ifndef TOPO_API_H
#define TOPO_API_H

#include "pal3_types.h"

// 37 methods
class gbMatrix4 {
public:
    __thiscall gbMatrix4::gbMatrix4(void);  // 0x1110
    struct gbVec3D * __thiscall gbMatrix4::GetColumn(struct gbVec3D *,int)const;  // 0x21D0
    struct gbVec4D * __thiscall gbMatrix4::GetColumn(struct gbVec4D *,int)const;  // 0x2180
    struct gbVec3D * __thiscall gbMatrix4::GetRow(struct gbVec3D *,int)const;  // 0x21B0
    struct gbVec4D * __thiscall gbMatrix4::GetRow(struct gbVec4D *,int)const;  // 0x2150
    void __thiscall gbMatrix4::Invert(struct gbMatrix4 *);  // 0x1C50
    void __thiscall gbMatrix4::Invert(void);  // 0x1AB0
    bool __thiscall gbMatrix4::IsIdentity(void)const;  // 0x1640
    bool __thiscall gbMatrix4::IsOrthonormal(void)const;  // 0x1760
    bool __thiscall gbMatrix4::IsValid(void)const;  // 0x1700
    void __thiscall gbMatrix4::LeftMultiply(struct gbMatrix4 const &);  // 0x1240
    void __thiscall gbMatrix4::LeftMultiply(struct gbQuaternion const &);  // 0x1F20
    void __thiscall gbMatrix4::LeftScale(float,float,float);  // 0x20F0
    void __thiscall gbMatrix4::LeftTranslate(struct gbVec3D &);  // 0x1F50
    void __thiscall gbMatrix4::LeftTranslate(float,float,float);  // 0x1FB0
    void __thiscall gbMatrix4::LoadIdentity(void);  // 0x15E0
    void __thiscall gbMatrix4::MakeMatrix(struct gbVec3D &,struct gbVec3D &,struct gbVec3D &);  // 0x1E20
    void __thiscall gbMatrix4::RightMultiply(struct gbMatrix4 const &);  // 0x11C0
    void __thiscall gbMatrix4::RightMultiply(struct gbQuaternion const &);  // 0x1EF0
    void __thiscall gbMatrix4::RightScale(float,float,float);  // 0x2070
    void __thiscall gbMatrix4::RightTranslate(struct gbVec3D &);  // 0x2010
    void __thiscall gbMatrix4::RightTranslate(float,float,float);  // 0x2040
    void __thiscall gbMatrix4::Rotate(struct gbVec3D const *,struct gbVec3D *)const;  // 0x14F0
    void __thiscall gbMatrix4::SetAxisAngle(struct gbVec3D *,float);  // 0x1A60
    void __thiscall gbMatrix4::SetAxisAngle(enum gbAxis,float);  // 0x1A30
    void __thiscall gbMatrix4::SetAxisAngle(enum gbAxis,float,float);  // 0x1910
    void __thiscall gbMatrix4::Transform(struct gbVec3D *,struct gbVec3D *,int)const;  // 0x12B0
    void __thiscall gbMatrix4::Transform(struct gbVec3D *,int)const;  // 0x13F0
    void __thiscall gbMatrix4::Transform(struct gbVec3D const *,struct gbVec3D *)const;  // 0x1250
    void __thiscall gbMatrix4::Transform_W(struct gbVec3D *,struct gbVec3D *,int)const;  // 0x1330
    void __thiscall gbMatrix4::Transpose(void);  // 0x1DB0
    void __thiscall gbMatrix4::Transpose(struct gbMatrix4 *)const;  // 0x1DF0
    float __thiscall gbMatrix4::operator()(int,int);  // 0x18D0
    void __thiscall gbMatrix4::operator*=(struct gbMatrix4 const &);  // 0x1140
    void __thiscall gbMatrix4::operator*=(struct gbQuaternion const &);  // 0x1F20
    void __thiscall gbMatrix4::operator*=(float const *);  // 0x1140
    void __thiscall gbMatrix4::operator=(struct gbMatrix4 const &);  // 0x1120
};

// 20 methods
class gbQuaternion {
public:
    __thiscall gbQuaternion::gbQuaternion(void);  // 0x18F0
    void __thiscall gbQuaternion::GetAxisAngle(struct gbVec3D *,float *);  // 0x2680
    void __thiscall gbQuaternion::GetMatrix(struct gbMatrix4 *)const;  // 0x2950
    void __thiscall gbQuaternion::GetVec3D(float *,struct gbVec3D *);  // 0x27E0
    void __thiscall gbQuaternion::Inverse(void);  // 0x2CF0
    int __thiscall gbQuaternion::IsNormal(void);  // 0x19A0
    bool const __thiscall gbQuaternion::IsUnit(void)const;  // 0x2770
    bool const __thiscall gbQuaternion::IsValid(void)const;  // 0x2700
    float const __thiscall gbQuaternion::Magnitude(void);  // 0x2C60
    void __thiscall gbQuaternion::MultiplyBy(struct gbQuaternion *,struct gbQuaternion *);  // 0x2B70
    float __thiscall gbQuaternion::Normalize(void);  // 0x2C90
    void __thiscall gbQuaternion::RotateVector(struct gbVec3D *,struct gbVec3D *);  // 0x2D10
    void __thiscall gbQuaternion::SetAxisAngle(struct gbVec3D *,float);  // 0x2640
    void __thiscall gbQuaternion::SetMatrix(struct gbMatrix4 *);  // 0x2800
    void __thiscall gbQuaternion::SetTwoVector(struct gbVec3D *,struct gbVec3D *);  // 0x25C0
    void __thiscall gbQuaternion::SetUnit(void);  // 0x19D0
    void __thiscall gbQuaternion::SetVec3D(float,struct gbVec3D *);  // 0x27C0
    void __thiscall gbQuaternion::SetYawPitchRoll(float,float,float);  // 0x2490
    void __thiscall gbQuaternion::Slerp(struct gbQuaternion *,struct gbQuaternion *,float);  // 0x2A30
    struct gbQuaternion & __thiscall gbQuaternion::operator=(struct gbQuaternion const &);  // 0x19F0
};

// 18 methods
class gbVec3D {
public:
    __thiscall gbVec3D::gbVec3D(float,float,float);  // 0x1470
    void __thiscall gbVec3D::CrossProduct(struct gbVec3D const *,struct gbVec3D *)const;  // 0x1080
    float __thiscall gbVec3D::DotProduct(struct gbVec3D const *)const;  // 0x16A0
    void __thiscall gbVec3D::Inverse(void);  // 0x1730
    int __thiscall gbVec3D::IsNormal(void);  // 0x16C0
    bool __thiscall gbVec3D::IsValid(void)const;  // 0x1030
    float __thiscall gbVec3D::Length(void)const;  // 0x1000
    float __thiscall gbVec3D::LengthSquare(void)const;  // 0x1680
    void __thiscall gbVec3D::Normalize(void);  // 0x10C0
    void __thiscall gbVec3D::Zero(void);  // 0x1750
    void __thiscall gbVec3D::`default constructor closure'(void);  // 0x18C0
    void __thiscall gbVec3D::operator*=(float);  // 0x1550
    void __thiscall gbVec3D::operator+=(struct gbVec3D const &);  // 0x14B0
    struct gbVec3D __thiscall gbVec3D::operator-(void)const;  // 0x1600
    void __thiscall gbVec3D::operator-=(struct gbVec3D const &);  // 0x14D0
    void __thiscall gbVec3D::operator/=(float);  // 0x1570
    void __thiscall gbVec3D::operator=(struct gbVec3D const &);  // 0x1490
    bool __thiscall gbVec3D::operator==(struct gbVec3D const &);  // 0x1590
};

// 16 methods
class gbMatrixStack {
public:
    __thiscall gbMatrixStack::gbMatrixStack(int);  // 0x2D50
    __thiscall gbMatrixStack::~gbMatrixStack(void);  // 0x2DE0
    int __thiscall gbMatrixStack::GetDepth(void);  // 0x1A20
    struct gbMatrix4 * __thiscall gbMatrixStack::GetTop(void);  // 0x2FF0
    void __thiscall gbMatrixStack::LoadIdentity(void);  // 0x2E30
    void __thiscall gbMatrixStack::LoadMatrix(struct gbMatrix4 *);  // 0x2E50
    void __thiscall gbMatrixStack::MultMatrix(struct gbMatrix4 *);  // 0x2E80
    void __thiscall gbMatrixStack::Pop(void);  // 0x2E20
    void __thiscall gbMatrixStack::Push(void);  // 0x2DF0
    void __thiscall gbMatrixStack::Rotate(struct gbQuaternion &);  // 0x2F00
    void __thiscall gbMatrixStack::Rotate(float,struct gbVec3D &);  // 0x2EB0
    void __thiscall gbMatrixStack::Scale(struct gbVec3D &);  // 0x2F60
    void __thiscall gbMatrixStack::Scale(float,float,float);  // 0x2FC0
    void __thiscall gbMatrixStack::Translate(struct gbVec3D &);  // 0x2F30
    void __thiscall gbMatrixStack::Translate(float,float,float);  // 0x2F90
    class gbMatrixStack & __thiscall gbMatrixStack::operator=(class gbMatrixStack const &);  // 0x19F0
};

// 7 methods
class gbRotMatrix {
public:
    __thiscall gbRotMatrix::gbRotMatrix(void);  // 0x21F0
    bool const __thiscall gbRotMatrix::IsOrthonormal(void);  // 0x2350
    bool const __thiscall gbRotMatrix::IsValid(void);  // 0x2320
    void __thiscall gbRotMatrix::LoadIdentity(void);  // 0x2300
    void __thiscall gbRotMatrix::Rotate(struct gbVec3D *,struct gbVec3D *);  // 0x22A0
    void __thiscall gbRotMatrix::operator*=(struct gbRotMatrix &);  // 0x2220
    void __thiscall gbRotMatrix::operator=(struct gbRotMatrix &);  // 0x2200
};

#endif // TOPO_API_H