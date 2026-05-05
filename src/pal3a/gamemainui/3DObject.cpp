#include "3DObject.h"

gbRay Object3D::GetMouseRay(gbRay * __$ReturnUdt)
{
    /* stub */
    gbRay _ret = {0}; return _ret;
}

void Object3D::SetCentrePos(gbVec3D centre)
{
    /* stub */
}

void Object3D::LoadSubObject(char * filename, ACTION_KIND act)
{
    /* stub */
}

void Object3D::LoadObject(char * filename, ACTION_KIND act)
{
    /* stub */
}

bool Object3D::IsOverCVD()
{
    /* stub */
    return FALSE;
}

void Object3D::Render(gbMatrixStack * pView)
{
    /* stub */
}

bool Object3D::CheckMousePressed(ulong key)
{
    /* stub */
    return FALSE;
}

Object3D::~Object3D()
{
    /* stub */
}

Object3D::Object3D()
{
    /* stub */
}

void Object3D::Update(float deltatime)
{
    /* stub */
}

float Object3D::GetScreenDegree(gbVec3D scrVec)
{
    /* stub */
    return 0.0f;
}

float Object3D::GetScreenDegree()
{
    /* stub */
    return 0.0f;
}

float Object3D::VecAngle(gbVec3D v1, gbVec3D v2)
{
    /* stub */
    return 0.0f;
}

bool Object3D::CheckMouseLClick()
{
    /* stub */
    return FALSE;
}

void Object3D::SetObjectPosition(gbVec3D position)
{
    /* stub */
}

void Object3D::CaculateRelative()
{
    /* stub */
}

void Object3D::Destroy()
{
    /* stub */
}

bool Object3D::CheckMouseLPressed()
{
    /* stub */
    return FALSE;
}

void ObjectCamera::SetCameraEyePosition(gbVec3D position, uchar bActionTo)
{
    /* stub */
}

ObjectCamera::~ObjectCamera()
{
    /* stub */
}

void ObjectCamera::Update()
{
    /* stub */
}

void ObjectCamera::SetCameraDist(float dist)
{
    /* stub */
}

void ObjectCamera::Create(gbGfxManager * pMgr)
{
    /* stub */
}

void ObjectCamera::SetCameraAtPosition(gbVec3D position)
{
    /* stub */
}

void ObjectCamera::SetCameraRotate(float yaw, float pitch, float roll)
{
    /* stub */
}

void ObjectCamera::SetStepRotate(float steprot, int mode, int axis)
{
    /* stub */
}

void ObjectCamera::ComputeInfo(int from)
{
    /* stub */
}

ObjectCamera::ObjectCamera()
{
    /* stub */
}

gbVec3D ObjectCamera::GetCameraDirect()
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

void ObjectCamera::Destroy()
{
    /* stub */
}

