#pragma once

#include "gbengine/gbengine_types.h"

// Forward declarations
class gbGfxManager;
class gbCamera;

// gbViewPort - viewport structure
struct gbViewPort {
    int x;
    int y;
    int width;
    int height;
    float minz;
    float maxz;
};


/* ======================================================================== */
/* gbCamControler - camera controller base class                            */
/*                                                                          */
/* Has vtable with virtual destructor and virtual Update method.            */
/* Exported: constructor, copy constructor, operator=, vftable              */
/* ======================================================================== */

class gbCamControler {
public:
    int type;               // +0x04: controller type
    gbCamera* pCamera;      // +0x08: owning camera

    gbCamControler(void);
    gbCamControler(const gbCamControler& other);
    gbCamControler& operator=(const gbCamControler& other);
    virtual ~gbCamControler();
    virtual void Update(double deltaTime);
};


/* ======================================================================== */
/* gbCamSpringControl - spring camera controller                            */
/*                                                                          */
/* Inherits gbCamControler. Provides spring-based camera following.         */
/* ======================================================================== */

class gbCamSpringControl : public gbCamControler {
public:
    float springConstant;
    float damping;
    float targetDist;
    gbVec3D velocity;

    gbCamSpringControl(void);
    gbCamSpringControl(const gbCamSpringControl& other);
    gbCamSpringControl& operator=(const gbCamSpringControl& other);
    virtual void Update(double deltaTime);
};


/* ======================================================================== */
/* gbCamQuakeControl - quake/shake camera controller                        */
/*                                                                          */
/* Inherits gbCamControler. Provides camera shake/quake effects.            */
/* ======================================================================== */

class gbCamQuakeControl : public gbCamControler {
public:
    float amplitude;
    float frequency;
    float duration;
    float elapsed;
    gbVec3D offset;

    gbCamQuakeControl(void);
    gbCamQuakeControl(const gbCamQuakeControl& other);
    gbCamQuakeControl& operator=(const gbCamQuakeControl& other);
    virtual void Update(double deltaTime);
};


/* ======================================================================== */
/* gbCamera - view camera with frustum clipping                             */
/*                                                                          */
/* sizeof = 0x178                                                           */
/* All method signatures match the original DLL exports exactly.            */
/* ======================================================================== */

class gbCamera {
public:
    float fov;                      // +0x00
    float OrthoSize;                // +0x04
    float Wscreen;                  // +0x08
    float Hscreen;                  // +0x0C
    float zNear;                    // +0x10
    float zFar;                     // +0x14
    gbViewPort Viewport;            // +0x18 (0x18 bytes)
    float Plane[6][4];             // +0x30 (0x60 bytes) - 6 frustum planes (nx, ny, nz, d)
    int numPlane;                   // +0x90
    gbMatrix4 ViewMatrix;           // +0x94 (0x40 bytes)
    gbMatrix4 InvVMatrix;           // +0xD4 (0x40 bytes)
    gbCamControler* pControl[16];   // +0x114 (0x40 bytes)
    int CurCtrl;                    // +0x154
    gbGfxManager* pGfxMgr;         // +0x158
    gbVec3D eyeLoc;                 // +0x15C (0x0C bytes)
    gbQuaternion eyeDir;            // +0x168 (0x10 bytes)
    // Total: 0x178

    // Helper methods
    void BuildProjMatrix(gbMatrix4* proj);
    void BuildFrustumPlanes(gbMatrix4* viewProj);
    void BuildViewFromQuaternion();

    // Constructor and operator=
    gbCamera(gbGfxManager* gfxMgr);
    gbCamera& operator=(const gbCamera& other);

    // Simple getters/setters
    void SetEyeLoc(float x, float y, float z);
    void SetEyeDir(gbQuaternion* dir);
    void SetOrthoSize(float size);
    void SetFOV(float f);
    void SetZRange(float nearZ, float farZ);
    float GetZNear(void);
    float GetZFar(void);
    float GetFOV(void);
    float GetOrthoSize(void);
    float GetAspect(void);
    void RotateVector(gbVec3D* in, gbVec3D* out);
    gbMatrix4* GetViewMatrix(void);
    gbMatrix4* GetInvViewMatrix(void);
    gbCamControler* GetCurControl(void);
    int IsCurCtrlDefault(void);

    // View setup methods
    void SetLookAt(gbVec3D* eye, gbVec3D* target, gbVec3D* up);
    void GetViewSizeOnNearPlane(float& w, float& h);
    void SetAsCurrent(int mode);
    void SetDimention(int w, int h);

    // Frustum clipping methods
    unsigned int ClipAABBox(gbVec3D* vMin, gbVec3D* vMax, unsigned int flags);
    int ClipOBBox(gbOBBox* obb);
    int ClipPoint(gbVec3D* pt);
    int ClipSphere(gbVec3D* center, float radius);

    // Coordinate transformation methods
    void PointScrToWorld(float sx, float sy, gbVec3D* worldPt);
    void PointWorldToEye(gbVec3D* worldPt, gbVec3D* eyePt);
    void PointScrToEye(float sx, float sy, gbVec3D* eyePt);
    void PointEyeToScr(gbVec3D* eyePt, float& sx, float& sy);
    void PointEyeToScr(gbVec3D* eyePt, gbVec3D* scrPt);
    void PointEyetoWorld(gbVec3D* eyePt, gbVec3D* worldPt);
    void PointWorldToScr(gbVec3D* worldPt, float& sx, float& sy);
    void GetRayToScreen(float sx, float sy, gbRay* ray);
    void GetViewPort(float& x, float& y, float& w, float& h);
    void PointDevToScr(int* dx, int* dy, float sx, float sy);
    void RotateVector(gbVec3D* in, gbVec3D* out, gbAxis axis);
    void OffsetZBuffer(double offset);
    void RecoverZBuffer(void);
    void MoveInEyeDir(float dist);
    void Update(double deltaTime);
    void AddControler(gbCamControler* ctrl, double blendTime);
    void PointWorld2Scr_NR(gbVec3D* worldPt, float& sx, float& sy);
};
