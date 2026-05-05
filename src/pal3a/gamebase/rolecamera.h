#ifndef PAL3A_ROLECAMERA_H
#define PAL3A_ROLECAMERA_H

#include "pal3a_types.h"

class RoleCamera {
public:
    char _data[692];

    int StateStackDepth();
    void Use(int flag);
    gbVec3D ComputeFrom(gbVec3D * __$ReturnUdt);
    void SetClientSize(int width, int height);
    ~RoleCamera();
    void FlushSpring();
    void Default(int type);
    void SetYaw(float yaw);
    void LockCenter(gbVec3D center, uchar bDefault);
    void UpdateRoomMode(float deltatime);
    void MakeCollideTriangleData(NavigationInfo * pNav);
    void ComputeInfo(int from);
    void Set(float yaw, float pitch, float dist, float fromx, float fromy, float fromz, int isFrom);
    bool Ctrl_IsReverse(float delta);
    void InverseComputerInfo(gbVec3D vecLookFrom, gbVec3D vecLookAt, float * fYaw, float * fPitch);
    void InverseComputerInfo(gbVec3D vecLookAt, float * fYaw, float * fPitch);
    void SampleCollide();
    void SetPitch(float pitch);
    gbRay GetMouserRay(gbRay * __$ReturnUdt);
    gbVec3D ClientToWorld(gbVec3D * __$ReturnUdt);
    void SetDist(float fDist);
    void PopState();
    void SampleCollide2();
    void PushState();
    RoleCamera(gbGfxManager * gfxmgr);
    void ClearCollisionData();
    void LockForward(gbVec3D forward, uchar bDefault);
    void Lock(gbVec3D * target);
    void Lock(SceneObj * obj);
    void Lock(Role * prole);
    void Ctrl_SetYaw(float delta);
    void Update(float deltatime);
    void Set2(float fYaw, float fPitch, float fRoll, float fFromX, float fFromY, float fFromZ);
};

class RoleCameraCtrl {
public:
    char _data[76];

    void UpdateValue(float * val, float start, float target, float r);
    void Interpolate(RoleCamera * pcamera, float yaw, float pitch, float dist, gbVec3D * from, float time);
    void ScriptUpdate(float deltatime);
    void Move(RoleCamera * pcamera, gbVec3D * targetfrom, float time, int itype);
    void HorizonRotate(RoleCamera * pcamera, float targetyaw, float targetpitch, float targetdist, float time, int itype);
    void Wag(RoleCamera * pcamera, float targetyaw, float targetpitch, float time, int itype);
    void Rotate(RoleCamera * pcamera, float targetyaw, float targetpitch, float time, int itype);
    void Quake(RoleCamera * pcamera, float time, float amplitude);
    void Push(RoleCamera * pcamera, float targetdist, float time, int itype);
    void FocusRole(RoleCamera * pcamera, Role * ptarget);
    ~RoleCameraCtrl();
    int IsWaiting();
    RoleCameraCtrl();
    void VerticalRotate(RoleCamera * pcamera, float targetyaw, float targetpitch, float targetdist, float time, int itype);
};

void AdjustCameraInfo(matrix<3,1,float> after_collide_pos);

#endif // PAL3A_ROLECAMERA_H
