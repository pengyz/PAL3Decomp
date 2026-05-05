#include "rolecamera.h"

int RoleCamera::StateStackDepth()
{
    /* stub */
    return 0;
}

void RoleCamera::Use(int flag)
{
    /* stub */
}

gbVec3D RoleCamera::ComputeFrom(gbVec3D * __$ReturnUdt)
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

void RoleCamera::SetClientSize(int width, int height)
{
    /* stub */
}

RoleCamera::~RoleCamera()
{
    /* stub */
}

void RoleCamera::FlushSpring()
{
    /* stub */
}

void RoleCamera::Default(int type)
{
    /* stub */
}

void RoleCamera::SetYaw(float yaw)
{
    /* stub */
}

void RoleCamera::LockCenter(gbVec3D center, uchar bDefault)
{
    /* stub */
}

void RoleCamera::UpdateRoomMode(float deltatime)
{
    /* stub */
}

void RoleCamera::MakeCollideTriangleData(NavigationInfo * pNav)
{
    /* stub */
}

void RoleCamera::ComputeInfo(int from)
{
    /* stub */
}

void RoleCamera::Set(float yaw, float pitch, float dist, float fromx, float fromy, float fromz, int isFrom)
{
    /* stub */
}

bool RoleCamera::Ctrl_IsReverse(float delta)
{
    /* stub */
    return FALSE;
}

void RoleCamera::InverseComputerInfo(gbVec3D vecLookFrom, gbVec3D vecLookAt, float * fYaw, float * fPitch)
{
    /* stub */
}

void RoleCamera::InverseComputerInfo(gbVec3D vecLookAt, float * fYaw, float * fPitch)
{
    /* stub */
}

void RoleCamera::SampleCollide()
{
    /* stub */
}

void RoleCamera::SetPitch(float pitch)
{
    /* stub */
}

gbRay RoleCamera::GetMouserRay(gbRay * __$ReturnUdt)
{
    /* stub */
    gbRay _ret = {0}; return _ret;
}

gbVec3D RoleCamera::ClientToWorld(gbVec3D * __$ReturnUdt)
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

void RoleCamera::SetDist(float fDist)
{
    /* stub */
}

void RoleCamera::PopState()
{
    /* stub */
}

void RoleCamera::SampleCollide2()
{
    /* stub */
}

void RoleCamera::PushState()
{
    /* stub */
}

RoleCamera::RoleCamera(gbGfxManager * gfxmgr)
{
    /* stub */
}

void RoleCamera::ClearCollisionData()
{
    /* stub */
}

void RoleCamera::LockForward(gbVec3D forward, uchar bDefault)
{
    /* stub */
}

void RoleCamera::Lock(gbVec3D * target)
{
    /* stub */
}

void RoleCamera::Lock(SceneObj * obj)
{
    /* stub */
}

void RoleCamera::Lock(Role * prole)
{
    /* stub */
}

void RoleCamera::Ctrl_SetYaw(float delta)
{
    /* stub */
}

void RoleCamera::Update(float deltatime)
{
    /* stub */
}

void RoleCamera::Set2(float fYaw, float fPitch, float fRoll, float fFromX, float fFromY, float fFromZ)
{
    /* stub */
}

void RoleCameraCtrl::UpdateValue(float * val, float start, float target, float r)
{
    /* stub */
}

void RoleCameraCtrl::Interpolate(RoleCamera * pcamera, float yaw, float pitch, float dist, gbVec3D * from, float time)
{
    /* stub */
}

void RoleCameraCtrl::ScriptUpdate(float deltatime)
{
    /* stub */
}

void RoleCameraCtrl::Move(RoleCamera * pcamera, gbVec3D * targetfrom, float time, int itype)
{
    /* stub */
}

void RoleCameraCtrl::HorizonRotate(RoleCamera * pcamera, float targetyaw, float targetpitch, float targetdist, float time, int itype)
{
    /* stub */
}

void RoleCameraCtrl::Wag(RoleCamera * pcamera, float targetyaw, float targetpitch, float time, int itype)
{
    /* stub */
}

void RoleCameraCtrl::Rotate(RoleCamera * pcamera, float targetyaw, float targetpitch, float time, int itype)
{
    /* stub */
}

void RoleCameraCtrl::Quake(RoleCamera * pcamera, float time, float amplitude)
{
    /* stub */
}

void RoleCameraCtrl::Push(RoleCamera * pcamera, float targetdist, float time, int itype)
{
    /* stub */
}

void RoleCameraCtrl::FocusRole(RoleCamera * pcamera, Role * ptarget)
{
    /* stub */
}

RoleCameraCtrl::~RoleCameraCtrl()
{
    /* stub */
}

int RoleCameraCtrl::IsWaiting()
{
    /* stub */
    return 0;
}

RoleCameraCtrl::RoleCameraCtrl()
{
    /* stub */
}

void RoleCameraCtrl::VerticalRotate(RoleCamera * pcamera, float targetyaw, float targetpitch, float targetdist, float time, int itype)
{
    /* stub */
}

void AdjustCameraInfo(matrix<3,1,float> after_collide_pos)
{
    /* stub */
}

