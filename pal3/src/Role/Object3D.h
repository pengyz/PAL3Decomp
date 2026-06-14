#pragma once
// Auto-generated: Object3D

#include "gbengine/gbGeomNode.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbVisNode.h"

class ObjectCamera;
class OpenNULLFile;

class Object3D {
public:
    BYTE m_isLoadObj; // +0x0
    char _gap_001[3]; // +0x1
    UINT m_type; // +0x4
    gbGeomNode * m_pol; // +0x8
    gbGeomNode * m_subObj; // +0xC
    UINT m_subType; // +0x10
    BYTE m_isLoadSubObj; // +0x14
    BYTE m_showSubObj; // +0x15
    char _gap_016[2]; // +0x16
    float m_subObjHeight; // +0x18
    float m_height; // +0x1C
    gbVec3D m_position; // +0x20
    char _gap_024[8]; // +0x24
    gbVec3D RelativePos; // +0x2C
    char _gap_030[8]; // +0x30
    float m_roty; // +0x38
    float m_rotx; // +0x3C
    float m_rotz; // +0x40
    float m_dropx; // +0x44
    float m_dropy; // +0x48
    float m_dropz; // +0x4C
    BYTE m_visible; // +0x50
    char _gap_051[3]; // +0x51
    ObjectCamera * m_pCamera; // +0x54
    float m_yaw; // +0x58
    float m_pitch; // +0x5C
    float m_roll; // +0x60
    float m_dist; // +0x64
    gbVec3D m_forward; // +0x68
    char _gap_06C[8]; // +0x6C
    float m_degreeToScreen; // +0x74
    BYTE m_isActionRelativeRot; // +0x78
    BYTE m_bRotDstDegree; // +0x79
    char _gap_07A[2]; // +0x7A
    float m_rotRelative; // +0x7C
    float m_rotDegree; // +0x80
    float m_rotDstDegree; // +0x84
    float m_rotDstSpeed; // +0x88
    int m_rotDstDir; // +0x8C
    int m_rotDstMode; // +0x90
    int m_action; // +0x94
    // total size: 0x98 (152)

    void SetTransform(gbMatrix4 *pMatrix); // 0x00429EE0
    BOOL IsVisible(); // 0x0042B1F0
    void GetOrientedOBBox(gbOBBox *pOBBox); // 0x0042B2F0
    Object3D(); // 0x0047CB70
    OpenNULLFile * _Object3D(const char *pszName, int actionIdx); // 0x0047CB90
    unsigned __int8 LoadObject(const char *filename, int act); // 0x0047CD70
    void LoadSubObject(); // 0x0047CEE0
    void Destroy(); // 0x0047CF40
    long double IsOverCVD(float fVal, float fVal2, float fVal3, float fVal4, float fVal5, float fVal6); // 0x0047CFB0
    void VecAngle(float fVal, float fVal2, float fVal3); // 0x0047D030
    void SetObjectPosition(float position, float fVal, float fVal2); // 0x0047D130
    long double SetCentrePos(); // 0x0047D230
    void GetScreenDegree(); // 0x0047D320
    void GetScreenDegree(int a2, int a3, int a4, gbMatrixStack *a5); // 0x0047D440
    void CaculateRelative(float fVal); // 0x0047D690
    void * SetupCamera(); // 0x0047D9D0
    bool Update(); // 0x0047DA60
    bool GetMouseRay(struct gbRay *a2, int a3); // 0x0047DB40
    bool CheckMouseLPressed(); // 0x0047DC60
    bool CheckMousePressed(); // 0x0047DC70
    int fn_47DD60(unsigned __int8 *thisa); // 0x0047DD60
    void * LoadActorModel(int nParam); // 0x0047FD90
    int RenderTransformed(int nLOD); // 0x004B7F80
    gbVisNode * GetVisNode(); // 0x00537060
    int CheckMessage(const char *pszMsgName); // 0x00537070
};
