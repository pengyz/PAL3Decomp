#ifndef PAL3A_3DOBJECT_H
#define PAL3A_3DOBJECT_H

#include "pal3a_types.h"

class Object3D {
public:
    char _data[152];

    gbRay GetMouseRay(gbRay * __$ReturnUdt);
    void SetCentrePos(gbVec3D centre);
    void LoadSubObject(char * filename, ACTION_KIND act);
    void LoadObject(char * filename, ACTION_KIND act);
    bool IsOverCVD();
    void Render(gbMatrixStack * pView);
    bool CheckMousePressed(ulong key);
    ~Object3D();
    Object3D();
    void Update(float deltatime);
    float GetScreenDegree(gbVec3D scrVec);
    float GetScreenDegree();
    float VecAngle(gbVec3D v1, gbVec3D v2);
    bool CheckMouseLClick();
    void SetObjectPosition(gbVec3D position);
    void CaculateRelative();
    void Destroy();
    bool CheckMouseLPressed();
};

class ObjectCamera {
public:
    char _data[124];

    void SetCameraEyePosition(gbVec3D position, uchar bActionTo);
    ~ObjectCamera();
    void Update();
    void SetCameraDist(float dist);
    void Create(gbGfxManager * pMgr);
    void SetCameraAtPosition(gbVec3D position);
    void SetCameraRotate(float yaw, float pitch, float roll);
    void SetStepRotate(float steprot, int mode, int axis);
    void ComputeInfo(int from);
    ObjectCamera();
    gbVec3D GetCameraDirect();
    void Destroy();
};

#endif // PAL3A_3DOBJECT_H
