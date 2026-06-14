#include "gbengine/gbCamera.h"
#pragma once
// Auto-generated: RoleCamera

#include "gbengine/gbengine_types.h"

class Role;
class SceneObj;

class RoleCamera : public gbCamera {
public:
    char _gap_000[380]; // +0x0
    Role * m_ptarget; // +0x17C
    SceneObj * m_pobj; // +0x180
    gbVec3D m_targetpos; // +0x184
    char _gap_188[8]; // +0x188
    gbVec3D m_lastFrom; // +0x190
    char _gap_194[8]; // +0x194
    gbVec3D m_fromVec; // +0x19C
    char _gap_1A0[8]; // +0x1A0
    float m_yaw; // +0x1A8
    float m_fCtrlYaw; // +0x1AC
    int m_dist; // +0x1B0
    float m_pitch; // +0x1B4
    int m_roll; // +0x1B8
    float m_nextYAW; // +0x1BC
    float m_lastYAW; // +0x1C0
    gbVec3D m_camVelocity; // +0x1C4
    char _gap_1C8[8]; // +0x1C8
    char m_argstack[36]; // +0x1D0
    int _todo_1F4; // +0x1F4
    char _gap_1F8[8]; // +0x1F8
    int m_bFree; // +0x200
    int m_bLockForward; // +0x204
    int m_bLockCenter; // +0x208
    int m_bProcessCollision; // +0x20C
    int m_CollideTriangleNum; // +0x210
    char polygonList[16]; // +0x214
    char polygonListBackup[16]; // +0x224
    char m_CollideData[12]; // +0x234
    int m_clientwidth; // +0x240
    int m_clientheight; // +0x244
    BYTE CAMERA_LOCK_HALFRADIUS; // +0x248
    BYTE CAMERA_COLLIDE_METHOD; // +0x249
    char _gap_24A[2]; // +0x24A
    gbVec3D m_lookat; // +0x24C
    char _gap_250[8]; // +0x250
    gbVec3D m_from; // +0x258
    char _gap_25C[8]; // +0x25C
    gbVec3D m_forward; // +0x264
    char _gap_268[8]; // +0x268
    gbVec3D m_up; // +0x270
    char _gap_274[8]; // +0x274
    gbVec3D m_side; // +0x27C
    char _gap_280[8]; // +0x280
    gbVec3D m_LockForward; // +0x288
    char _gap_28C[8]; // +0x28C
    gbVec3D m_LockCenter; // +0x294
    char _gap_298[8]; // +0x298
    BYTE m_bCollide; // +0x2A0
    char _gap_2A1[3]; // +0x2A1
    float m_roomHeight; // +0x2A4
    gbVec3D m_lastUP; // +0x2A8
    char _tail_2AC[8]; // +0x2AC
    // total size: 0x2B4 (692)

    int PushState(); // 0x0041D410
    int InitParticles(); // 0x0044D180
    static void SetPitch(float); // 0x004518FE
    void UpdateAudioListener(int nVal, int nVal2); // 0x00534CF0
};
