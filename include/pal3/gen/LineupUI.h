#pragma once
// Auto-generated: LineupUI

#include "LINEUPINFO.h"
#include "LINEUP_SEQUENCE.h"
#include "LineupPlank.h"
#include "MUIDialog.h"
#include "Object3D.h"
#include "ProtectPanel.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIParticle.h"
#include "UIStatic.h"

class ObjectCamera;
class StateUI;

class LineupUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    BYTE m_IsMsg; // +0x168
    BYTE m_Is[5]; // +0x169
    UIStatic m_Frame; // +0x170
    UIStatic m_TimeMoney; // +0x210
    UIStatic m_OutFrameT; // +0x2B0
    UIStatic m_OutFrameR; // +0x350
    UIStatic m_OutFrameL; // +0x3F0
    UIStatic m_OutFrameB; // +0x490
    UIStatic stp_BarL; // +0x530
    UIFlexBar stp_BarM; // +0x5D0
    UIStatic stp_BarR; // +0x624
    UIButton stp_State; // +0x6C4
    UIButton stp_Magic; // +0x81C
    UIButton stp_Equip; // +0x974
    UIButton stp_Prop; // +0xACC
    UIButton stp_BattleArray; // +0xC24
    UIButton stp_TaskBook; // +0xD7C
    UIButton stp_System; // +0xED4
    UIButton stp_Exit; // +0x102C
    UIStatic stp_Effect; // +0x1184
    tagRECT stp_Rect; // +0x1224
    UIStatic m_GameTime; // +0x1234
    UIStatic m_GameMoney; // +0x12D4
    MUIDialog m_DlgEx; // +0x1374
    UIStatic m_ZhenLie; // +0x18DC
    UIParticle m_btnPar[16][7]; // +0x197C
    UIParticle m_btnPar2[16][7]; // +0x11C7C
    tagRECT m_btnParRc[7]; // +0x21F7C
    BYTE _isParBtn[7]; // +0x21FEC
    int _curParEffect; // +0x21FF4
    LINEUPINFO m_LineupInfo[5]; // +0x21FF8
    LINEUP_SEQUENCE m_Sequence; // +0x22016
    tagRECT roleRc; // +0x2201C
    UIStatic m_RoleFrame; // +0x2202C
    UIButton m_RoleBtn[5]; // +0x220CC
    int m_RoleBtnIndex[5]; // +0x22784
    UIStatic m_NoBody[5]; // +0x22798
    UIStatic m_RoleLeader[5]; // +0x22AB8
    tagRECT m_headRc[5]; // +0x22DD8
    int m_headRole; // +0x22E28
    MUIDialog m_Msg; // +0x22E2C
    float m_objCamPitch; // +0x23394
    float m_objRotSpeed; // +0x23398
    ObjectCamera * m_pCamera; // +0x2339C
    float m_pointerHeight; // +0x233A0
    BYTE m_bPeek; // +0x233A4
    int m_nPeek; // +0x233A8
    int m_nLastPeek; // +0x233AC
    BYTE m_isRotLineup; // +0x233B0
    gbVec3D m_ObjPos[6]; // +0x233B4
    Object3D m_LineupObj; // +0x233FC
    Object3D m_3DRole[5]; // +0x23494
    BYTE m_IsRole[6]; // +0x2378C
    int m_RoleId[6]; // +0x23794
    Object3D m_3DNone[6]; // +0x237AC
    LineupPlank m_CtrlPlank[5]; // +0x23B3C
    ProtectPanel m_ProtectPanel; // +0x26224
    BYTE m_ProFlag; // +0x2672C
    StateUI * pStateUI; // +0x26730
    // total size: 0x26734 (157492)

};
