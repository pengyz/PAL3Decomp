#include "UIWnd.h"
#pragma once
// Auto-generated: LineupComp

#include "Object3D.h"
#include "gbengine/gbengine_types.h"

class ObjectCamera;

class LineupComp : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    gbVec3D m_ObjPos[4]; // +0x44
    char _gap_054[36]; // +0x54
    Object3D m_LineupObj; // +0x78
    char _gap_07C[148]; // +0x7C
    Object3D m_3DRole[5]; // +0x110
    char _gap_124[740]; // +0x124
    _BYTE m_isRoleIn[5]; // +0x408
    char _gap_40D[3]; // +0x40D
    Object3D m_3DNone[6]; // +0x410
    char _gap_428[888]; // +0x428
    _BYTE m_is3DNoneIn[6]; // +0x7A0
    char _gap_7A6[2]; // +0x7A6
    ObjectCamera * m_pCamera; // +0x7A8
    float m_objCamPitch; // +0x7AC
    float m_objRotSpeed; // +0x7B0
    float m_pointerHeight; // +0x7B4
    BYTE m_isRotLineup; // +0x7B8
    char _gap_7B9[3]; // +0x7B9
    int m_RoleId; // +0x7BC
    int m_nRole; // +0x7C0
    BYTE m_bClickRole; // +0x7C4
    char _tail_7C5[23]; // +0x7C5
    // total size: 0x7DC (2012)

    LineupComp(int thisa); // 0x0044B850
    int SetVisible(int thisa, unsigned __int8 pData); // 0x004543C0
    int ShowById(int id); // 0x00483FA0
    int CallSlotMethod(int nIndex, unsigned int dwParam); // 0x00484140
    int PositionAt(int arg0, int nVal, int nVal2); // 0x004841B0
    int DispatchSlotMethod(int nIndex, unsigned int dwParam); // 0x00484E10
    int GetSlotWidget(int nIndex, unsigned int dwParam); // 0x00484E30
};
