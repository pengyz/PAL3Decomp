#pragma once
// Auto-generated: RoleCamera

class Role;
class SceneObj;

class RoleCamera : public gbCamera {
public:
    Role * m_ptarget; // +0x17C
    SceneObj * m_pobj; // +0x180
    gbVec3D m_targetpos; // +0x184
    gbVec3D m_lastFrom; // +0x190
    gbVec3D m_fromVec; // +0x19C
    float m_yaw; // +0x1A8
    float m_fCtrlYaw; // +0x1AC
    float m_dist; // +0x1B0
    float m_pitch; // +0x1B4
    float m_roll; // +0x1B8
    float m_nextYAW; // +0x1BC
    float m_lastYAW; // +0x1C0
    gbVec3D m_camVelocity; // +0x1C4
    char m_argstack[48]; // +0x1D0 (std::stack<RC_ARG,std::deque<RC_ARG,std::allocator<RC_ARG> > >)
    int m_bFree; // +0x200
    int m_bLockForward; // +0x204
    int m_bLockCenter; // +0x208
    int m_bProcessCollision; // +0x20C
    int m_CollideTriangleNum; // +0x210
    char polygonList[16]; // +0x214 (std::vector<primitive<3,float>,std::allocator<primitive<3,float> > >)
    char polygonListBackup[16]; // +0x224 (std::vector<primitive<3,float>,std::allocator<primitive<3,float> > >)
    char m_CollideData[12]; // +0x234 (std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >)
    int m_clientwidth; // +0x240
    int m_clientheight; // +0x244
    BYTE CAMERA_LOCK_HALFRADIUS; // +0x248
    BYTE CAMERA_COLLIDE_METHOD; // +0x249
    gbVec3D m_lookat; // +0x24C
    gbVec3D m_from; // +0x258
    gbVec3D m_forward; // +0x264
    gbVec3D m_up; // +0x270
    gbVec3D m_side; // +0x27C
    gbVec3D m_LockForward; // +0x288
    gbVec3D m_LockCenter; // +0x294
    BYTE m_bCollide; // +0x2A0
    float m_roomHeight; // +0x2A4
    gbVec3D m_lastUP; // +0x2A8
    // total size: 0x2B4 (692)

};
