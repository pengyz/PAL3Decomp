#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UISceneFrm

#include "UISceneFace.h"
#include "UISceneMap.h"

class RoleTask;
class RoleTaskLine;

class UISceneFrm : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UISceneMap m_map; // +0x48
    char _gap_04C[1008]; // +0x4C
    UISceneFace m_face; // +0x43C
    char _tail_440[1776]; // +0x440
    // total size: 0xB30 (2864)

    virtual ~UISceneFrm() {}

    virtual void Render(); // 0x0045A490
    static void fill(RoleTask *a1, RoleTask *a2, RoleTask *a3); // 0x0045A4F0
    void Destroy(); // 0x00459360
    static void _Construct_2(RoleTaskLine *a1, RoleTaskLine *a2); // 0x0045A600
    int ctor(); // 0x004590D0
    void ctor_9260(); // 0x00459260
    int InitGraph_Base(); // 0x004BB330
    int InitGraph_Rotation(); // 0x004BB4E0
    int InitGraph_VertexAlpha(); // 0x004BB690
    int InitGraph_RGBColor(); // 0x004BB830
    int InitGraph_Direction(); // 0x004BBA50
    int InitGraph_RandomVelocity(); // 0x004BBCA0
    int InitGraph_EmissionRate(); // 0x004BBEB0
    int InitGraph_Lifetime(); // 0x004BC0C0
    int InitGraph_SizeMultiplier(); // 0x004BC2D0
    int InitGraph_RotationMultiplier(); // 0x004BC4E0
    int CallFaceMethod(int nVal, unsigned __int8 pData); // 0x00528CD0
    int ShowAndRelease(); // 0x00535630
    LPSTR InitTemplateStrings(); // 0x00535650
};
