/**
 * gbengine.dll - gbCamera, gbCamControler, gbCamQuakeControl, gbCamSpringControl
 *
 * Functional decompilation from Ghidra analysis and PAL3A.PDB symbols.
 * Method names and signatures match original DLL exports exactly.
 *
 * Compiler: MSVC 6.0 SP5
 *
 * Class layout (gbCamera, sizeof = 0x178):
 *   +0x00: float fov
 *   +0x04: float OrthoSize
 *   +0x08: float Wscreen
 *   +0x0C: float Hscreen
 *   +0x10: float zNear
 *   +0x14: float zFar
 *   +0x18: gbViewPort Viewport (0x18 bytes)
 *   +0x30: float Plane[6][4] (0x60 bytes) - 6 frustum planes (nx, ny, nz, d)
 *   +0x90: int numPlane
 *   +0x94: gbMatrix4 ViewMatrix (0x40 bytes)
 *   +0xD4: gbMatrix4 InvVMatrix (0x40 bytes)
 *   +0x114: gbCamControler* pControl[16] (0x40 bytes)
 *   +0x154: int CurCtrl
 *   +0x158: gbGfxManager* pGfxMgr
 *   +0x15C: gbVec3D eyeLoc (0x0C bytes)
 *   +0x168: gbQuaternion eyeDir (0x10 bytes)
 * Total: 0x178 = 376 bytes
 */

#include "gbengine/gbCamera.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_internal.h"
#include <math.h>
#include <string.h>

// External globals
extern gbGfxManager* g_pGfxManager;


/* ======================================================================== */
/* gbCamControler method implementations                                    */
/* ======================================================================== */

// 0x10005b20 (9B) - Default constructor
gbCamControler::gbCamControler(void) {
}

// 0x10005b30 (45B) - Copy constructor
gbCamControler::gbCamControler(const gbCamControler& other) {
    pCamera = other.pCamera;
    curTime = other.curTime;
    blendTime = other.blendTime;
}

// 0x10005b60 - operator=
gbCamControler& gbCamControler::operator=(const gbCamControler& other) {
    pCamera = other.pCamera;
    curTime = other.curTime;
    blendTime = other.blendTime;
    return *this;
}

// Virtual destructor
gbCamControler::~gbCamControler() {
}

void gbCamControler::Update(double deltaTime) { (void)deltaTime; }


/* ======================================================================== */
/* gbCamSpringControl method implementations                                */
/* ======================================================================== */

// 0x10005b90 (43B) - Default constructor
gbCamSpringControl::gbCamSpringControl(void) : gbCamControler() {
    type = 1;
    targetPos.x = 0.0f;
    targetPos.y = 0.0f;
    targetPos.z = 0.0f;
    targetQuat.x = 0.0f;
    targetQuat.y = 0.0f;
    targetQuat.z = 0.0f;
    targetQuat.w = 1.0f;
    speed = -1.0f;
}

// 0x10005bc0 (111B) - Copy constructor
gbCamSpringControl::gbCamSpringControl(const gbCamSpringControl& other) : gbCamControler(other) {
    targetPos.x = other.targetPos.x;
    targetPos.y = other.targetPos.y;
    targetPos.z = other.targetPos.z;
    targetQuat.x = other.targetQuat.x;
    targetQuat.y = other.targetQuat.y;
    targetQuat.z = other.targetQuat.z;
    targetQuat.w = other.targetQuat.w;
    speed = other.speed;
}

// 0x10005c30 - operator= (96B)
gbCamSpringControl& gbCamSpringControl::operator=(const gbCamSpringControl& other) {
    pCamera = other.pCamera;
    curTime = other.curTime;
    blendTime = other.blendTime;
    targetPos.x = other.targetPos.x;
    targetPos.y = other.targetPos.y;
    targetPos.z = other.targetPos.z;
    targetQuat.x = other.targetQuat.x;
    targetQuat.y = other.targetQuat.y;
    targetQuat.z = other.targetQuat.z;
    targetQuat.w = other.targetQuat.w;
    speed = other.speed;
    return *this;
}

// 0x10021700 (295B) - Spring update
void gbCamSpringControl::Update(double deltaTime) {
    if (speed >= 0.0f) {
        float t = speed * (float)deltaTime;
        if (t > 1.0f)
            t = 1.0f;

        float* camPos = (float*)&pCamera->eyeLoc;
        camPos[0] = (targetPos.x - camPos[0]) * t + camPos[0];
        camPos[1] = (targetPos.y - camPos[1]) * t + camPos[1];
        camPos[2] = (targetPos.z - camPos[2]) * t + camPos[2];

        float slerpT = t;
        gbQuaternion* camQuat = &pCamera->eyeDir;
        gbQuaternion identity;
        identity.x = 0.0f;
        identity.y = 0.0f;
        identity.z = 0.0f;
        identity.w = 1.0f;
        identity.Slerp(camQuat, &targetQuat, slerpT);
        int* dst = (int*)&pCamera->eyeDir;
        dst[0] = *(int*)&identity.x;
        dst[1] = *(int*)&identity.y;
        dst[2] = *(int*)&identity.z;
        dst[3] = *(int*)&identity.w;
    } else {
        int* dst = (int*)&pCamera->eyeLoc;
        dst[0] = *(int*)&targetPos.x;
        dst[1] = *(int*)&targetPos.y;
        dst[2] = *(int*)&targetPos.z;
        int* qdst = (int*)&pCamera->eyeDir;
        qdst[0] = *(int*)&targetQuat.x;
        qdst[1] = *(int*)&targetQuat.y;
        qdst[2] = *(int*)&targetQuat.z;
        qdst[3] = *(int*)&targetQuat.w;
    }
}


/* ======================================================================== */
/* gbCamQuakeControl method implementations                                 */
/* ======================================================================== */

// 0x10005c90 (29B) - Default constructor
gbCamQuakeControl::gbCamQuakeControl(void) : gbCamControler() {
    type = 2;
    basePosition.x = 0.0f;
    basePosition.y = 0.0f;
    basePosition.z = 0.0f;
    amplitude.x = 0.0f;
    amplitude.y = 0.0f;
    amplitude.z = 0.0f;
    angle = 0.0;
}

// 0x10005cb0 (111B) - Copy constructor
gbCamQuakeControl::gbCamQuakeControl(const gbCamQuakeControl& other) : gbCamControler(other) {
    basePosition.x = other.basePosition.x;
    basePosition.y = other.basePosition.y;
    basePosition.z = other.basePosition.z;
    amplitude.x = other.amplitude.x;
    amplitude.y = other.amplitude.y;
    amplitude.z = other.amplitude.z;
    *(int*)&angle = *(int*)&other.angle;
    *((int*)&angle + 1) = *((int*)&other.angle + 1);
}

// 0x10005d20 - operator=
gbCamQuakeControl& gbCamQuakeControl::operator=(const gbCamQuakeControl& other) {
    pCamera = other.pCamera;
    curTime = other.curTime;
    blendTime = other.blendTime;
    basePosition.x = other.basePosition.x;
    basePosition.y = other.basePosition.y;
    basePosition.z = other.basePosition.z;
    amplitude.x = other.amplitude.x;
    amplitude.y = other.amplitude.y;
    amplitude.z = other.amplitude.z;
    *(int*)&angle = *(int*)&other.angle;
    *((int*)&angle + 1) = *((int*)&other.angle + 1);
    return *this;
}

// 0x10021830 (149B) - Quake update
void gbCamQuakeControl::Update(double deltaTime) {
    float* eyePos = &pCamera->eyeLoc.x;
    double ratio = (blendTime - curTime) / blendTime;
    float ampX = (float)(ratio * ratio * amplitude.x);
    float ampY = (float)(ratio * ratio * amplitude.y);
    double ampZ = ratio * ratio * amplitude.z;
    float sinVal = (float)sin(angle * 0.01745329300562541);
    float offX = ampX * sinVal;
    float offY = ampY * sinVal;
    offY = offY + basePosition.y;
    float resX = offX + basePosition.x;
    float resZ = (float)(ampZ * sinVal + basePosition.z);
    eyePos[1] = offY;
    float zStore = resZ;
    *eyePos = resX;
    eyePos[2] = zStore;
    angle = deltaTime * 3600.0 + angle;
}


/* ======================================================================== */
/* gbCamera method implementations                                          */
/* ======================================================================== */

// ---- Helper: build projection matrix (not stored, computed on the fly) ----

void gbCamera::BuildProjMatrix(gbMatrix4* proj) {
    float aspect = GetAspect();
    float h = 1.0f / (float)tan(fov * 0.5f);
    float w = h / aspect;
    float Q = zFar / (zFar - zNear);

    memset(proj, 0, sizeof(gbMatrix4));
    proj->m[0][0] = w;
    proj->m[1][1] = h;
    proj->m[2][2] = Q;
    proj->m[2][3] = 1.0f;
    proj->m[3][2] = -Q * zNear;
}

// ---- Helper: extract frustum planes from view-projection matrix ----

void gbCamera::BuildFrustumPlanes(gbMatrix4* viewProj) {
    float (*M)[4] = viewProj->m;

    // Left: row3 + row0
    Plane[0][0] = M[0][3] + M[0][0];
    Plane[0][1] = M[1][3] + M[1][0];
    Plane[0][2] = M[2][3] + M[2][0];
    Plane[0][3] = M[3][3] + M[3][0];

    // Right: row3 - row0
    Plane[1][0] = M[0][3] - M[0][0];
    Plane[1][1] = M[1][3] - M[1][0];
    Plane[1][2] = M[2][3] - M[2][0];
    Plane[1][3] = M[3][3] - M[3][0];

    // Bottom: row3 + row1
    Plane[2][0] = M[0][3] + M[0][1];
    Plane[2][1] = M[1][3] + M[1][1];
    Plane[2][2] = M[2][3] + M[2][1];
    Plane[2][3] = M[3][3] + M[3][1];

    // Top: row3 - row1
    Plane[3][0] = M[0][3] - M[0][1];
    Plane[3][1] = M[1][3] - M[1][1];
    Plane[3][2] = M[2][3] - M[2][1];
    Plane[3][3] = M[3][3] - M[3][1];

    // Near: row2
    Plane[4][0] = M[0][2];
    Plane[4][1] = M[1][2];
    Plane[4][2] = M[2][2];
    Plane[4][3] = M[3][2];

    // Far: row3 - row2
    Plane[5][0] = M[0][3] - M[0][2];
    Plane[5][1] = M[1][3] - M[1][2];
    Plane[5][2] = M[2][3] - M[2][2];
    Plane[5][3] = M[3][3] - M[3][2];

    // Normalize planes
    for (int p = 0; p < 6; p++) {
        float len = (float)sqrt(Plane[p][0] * Plane[p][0]
                              + Plane[p][1] * Plane[p][1]
                              + Plane[p][2] * Plane[p][2]);
        if (len > 1e-6f) {
            float invLen = 1.0f / len;
            Plane[p][0] *= invLen;
            Plane[p][1] *= invLen;
            Plane[p][2] *= invLen;
            Plane[p][3] *= invLen;
        }
    }
    numPlane = 6;
}

// ---- Helper: build view matrix from eyeLoc and eyeDir quaternion ----

void gbCamera::BuildViewFromQuaternion() {
    gbMatrix4 rotMat;
    eyeDir.GetMatrix(&rotMat);

    // View matrix = transpose(rotation) with translation
    ViewMatrix.m[0][0] = rotMat.m[0][0];
    ViewMatrix.m[0][1] = rotMat.m[1][0];
    ViewMatrix.m[0][2] = rotMat.m[2][0];
    ViewMatrix.m[0][3] = 0.0f;

    ViewMatrix.m[1][0] = rotMat.m[0][1];
    ViewMatrix.m[1][1] = rotMat.m[1][1];
    ViewMatrix.m[1][2] = rotMat.m[2][1];
    ViewMatrix.m[1][3] = 0.0f;

    ViewMatrix.m[2][0] = rotMat.m[0][2];
    ViewMatrix.m[2][1] = rotMat.m[1][2];
    ViewMatrix.m[2][2] = rotMat.m[2][2];
    ViewMatrix.m[2][3] = 0.0f;

    ViewMatrix.m[3][0] = -(ViewMatrix.m[0][0] * eyeLoc.x + ViewMatrix.m[1][0] * eyeLoc.y + ViewMatrix.m[2][0] * eyeLoc.z);
    ViewMatrix.m[3][1] = -(ViewMatrix.m[0][1] * eyeLoc.x + ViewMatrix.m[1][1] * eyeLoc.y + ViewMatrix.m[2][1] * eyeLoc.z);
    ViewMatrix.m[3][2] = -(ViewMatrix.m[0][2] * eyeLoc.x + ViewMatrix.m[1][2] * eyeLoc.y + ViewMatrix.m[2][2] * eyeLoc.z);
    ViewMatrix.m[3][3] = 1.0f;

    // Inverse view: rotation part (not transposed) + eye position
    InvVMatrix.m[0][0] = rotMat.m[0][0];
    InvVMatrix.m[0][1] = rotMat.m[0][1];
    InvVMatrix.m[0][2] = rotMat.m[0][2];
    InvVMatrix.m[0][3] = 0.0f;

    InvVMatrix.m[1][0] = rotMat.m[1][0];
    InvVMatrix.m[1][1] = rotMat.m[1][1];
    InvVMatrix.m[1][2] = rotMat.m[1][2];
    InvVMatrix.m[1][3] = 0.0f;

    InvVMatrix.m[2][0] = rotMat.m[2][0];
    InvVMatrix.m[2][1] = rotMat.m[2][1];
    InvVMatrix.m[2][2] = rotMat.m[2][2];
    InvVMatrix.m[2][3] = 0.0f;

    InvVMatrix.m[3][0] = eyeLoc.x;
    InvVMatrix.m[3][1] = eyeLoc.y;
    InvVMatrix.m[3][2] = eyeLoc.z;
    InvVMatrix.m[3][3] = 1.0f;
}

// ======================================================================
// Constructor and operator=
// ======================================================================

// 0x100218d0 (157B) - Constructor
gbCamera::gbCamera(gbGfxManager* gfxMgr) {
    pGfxMgr = gfxMgr;

    fov = 45.0f * 3.14159265f / 180.0f;
    OrthoSize = 1.0f;
    Wscreen = 640.0f;
    Hscreen = 480.0f;
    zNear = 1.0f;
    zFar = 10000.0f;

    memset(&Viewport, 0, sizeof(Viewport));
    Viewport.width = 640;
    Viewport.height = 480;
    Viewport.minz = 0.0f;
    Viewport.maxz = 1.0f;

    memset(Plane, 0, sizeof(Plane));
    numPlane = 6;

    memset(&ViewMatrix, 0, sizeof(gbMatrix4));
    ViewMatrix.m[0][0] = 1.0f;
    ViewMatrix.m[1][1] = 1.0f;
    ViewMatrix.m[2][2] = 1.0f;
    ViewMatrix.m[3][3] = 1.0f;

    memset(&InvVMatrix, 0, sizeof(gbMatrix4));
    InvVMatrix.m[0][0] = 1.0f;
    InvVMatrix.m[1][1] = 1.0f;
    InvVMatrix.m[2][2] = 1.0f;
    InvVMatrix.m[3][3] = 1.0f;

    memset(pControl, 0, sizeof(pControl));
    CurCtrl = 0;

    eyeLoc.x = 0.0f;
    eyeLoc.y = 0.0f;
    eyeLoc.z = 0.0f;

    eyeDir.x = 0.0f;
    eyeDir.y = 0.0f;
    eyeDir.z = 0.0f;
    eyeDir.w = 1.0f;
}

// 0x10005a20 - operator= (243B)
gbCamera& gbCamera::operator=(const gbCamera& other) {
    fov = other.fov;
    OrthoSize = other.OrthoSize;
    Wscreen = other.Wscreen;
    Hscreen = other.Hscreen;
    zNear = other.zNear;
    zFar = other.zFar;
    memcpy(&Viewport, &other.Viewport, 0x18);
    int* planePtr = (int*)&Plane[0][0];
    int srcOffset = (int)((char*)&other - (char*)this);
    int planeCount = 24;
    do {
        *planePtr = *(int*)((char*)planePtr + srcOffset);
        ++planePtr;
        --planeCount;
    } while (planeCount);
    numPlane = other.numPlane;
    ViewMatrix = other.ViewMatrix;
    InvVMatrix = other.InvVMatrix;
    int* ctrlPtr = (int*)&pControl[0];
    int ctrlCount = 16;
    do {
        *ctrlPtr = *(int*)((char*)ctrlPtr + srcOffset);
        ++ctrlPtr;
        --ctrlCount;
    } while (ctrlCount);
    CurCtrl = other.CurCtrl;
    pGfxMgr = other.pGfxMgr;
    eyeLoc.x = other.eyeLoc.x;
    eyeLoc.y = other.eyeLoc.y;
    eyeLoc.z = other.eyeLoc.z;
    eyeDir.x = other.eyeDir.x;
    eyeDir.y = other.eyeDir.y;
    eyeDir.z = other.eyeDir.z;
    eyeDir.w = other.eyeDir.w;
    return *this;
}

// ======================================================================
// Simple getters/setters (exported as small functions)
// ======================================================================

// 0x100058d0 (33B)
void gbCamera::SetEyeLoc(float x, float y, float z) {
    eyeLoc.x = x;
    eyeLoc.y = y;
    eyeLoc.z = z;
}

// 0x10005900 (42B)
void gbCamera::SetEyeDir(gbQuaternion* dir) {
    int* dst = (int*)&eyeDir;
    int* src = (int*)dir;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

// 0x10005930 (16B)
void gbCamera::SetOrthoSize(float size) {
    fov = 0.0f;
    OrthoSize = size;
}

// 0x10005940 (16B)
void gbCamera::SetFOV(float f) {
    OrthoSize = 0.0f;
    fov = f;
}

// 0x10005950 (17B)
void gbCamera::SetZRange(float nearZ, float farZ) {
    zNear = nearZ;
    zFar = farZ;
}

// 0x10005970 (10B)
float gbCamera::GetZNear(void) {
    return zNear;
}

// 0x10005980 (10B)
float gbCamera::GetZFar(void) {
    return zFar;
}

// 0x10005990 (10B) - GetFOV (note: uppercase FOV)
float gbCamera::GetFOV(void) {
    return fov;
}

// 0x100059a0 (10B)
float gbCamera::GetOrthoSize(void) {
    return OrthoSize;
}

// 0x100059b0 (7B)
float gbCamera::GetAspect(void) {
    return (float)Viewport.height / (float)Viewport.width;
}

// 0x100059c0 (24B) - Rotate vector by camera orientation (eye to world)
void gbCamera::RotateVector(gbVec3D* in, gbVec3D* out) {
    InvVMatrix.Rotate(in, out);
}

// 0x100059e0 (10B)
gbMatrix4* gbCamera::GetViewMatrix(void) {
    return &ViewMatrix;
}

// 0x100059f0 (10B)
gbMatrix4* gbCamera::GetInvViewMatrix(void) {
    return &InvVMatrix;
}

// 0x10005a00 (14B)
gbCamControler* gbCamera::GetCurControl(void) {
    return pControl[CurCtrl];
}

// 0x10005a10 (14B)
int gbCamera::IsCurCtrlDefault(void) {
    return (CurCtrl == 0) ? 1 : 0;
}

// ======================================================================
// View setup methods
// ======================================================================

// 0x10021970 (155B) - Set look-at parameters and build view matrix
void gbCamera::SetLookAt(gbVec3D* eye, gbVec3D* target, gbVec3D* up) {
    if (!eye || !target || !up)
        return;

    eyeLoc = *eye;

    // Compute forward: normalize(target - eye)
    float fx = target->x - eye->x;
    float fy = target->y - eye->y;
    float fz = target->z - eye->z;
    float flen = (float)sqrt(fx * fx + fy * fy + fz * fz);
    if (flen < 1e-6f)
        return;
    fx /= flen; fy /= flen; fz /= flen;

    // Compute right: normalize(cross(up, forward))
    float rx = up->y * fz - up->z * fy;
    float ry = up->z * fx - up->x * fz;
    float rz = up->x * fy - up->y * fx;
    float rlen = (float)sqrt(rx * rx + ry * ry + rz * rz);
    if (rlen < 1e-6f)
        return;
    rx /= rlen; ry /= rlen; rz /= rlen;

    // Recompute up: cross(forward, right)
    float ux = fy * rz - fz * ry;
    float uy = fz * rx - fx * rz;
    float uz = fx * ry - fy * rx;

    // Build view matrix (row-major, D3D convention)
    ViewMatrix.m[0][0] = rx;  ViewMatrix.m[0][1] = ux;  ViewMatrix.m[0][2] = fx;  ViewMatrix.m[0][3] = 0.0f;
    ViewMatrix.m[1][0] = ry;  ViewMatrix.m[1][1] = uy;  ViewMatrix.m[1][2] = fy;  ViewMatrix.m[1][3] = 0.0f;
    ViewMatrix.m[2][0] = rz;  ViewMatrix.m[2][1] = uz;  ViewMatrix.m[2][2] = fz;  ViewMatrix.m[2][3] = 0.0f;
    ViewMatrix.m[3][0] = -(rx * eyeLoc.x + ry * eyeLoc.y + rz * eyeLoc.z);
    ViewMatrix.m[3][1] = -(ux * eyeLoc.x + uy * eyeLoc.y + uz * eyeLoc.z);
    ViewMatrix.m[3][2] = -(fx * eyeLoc.x + fy * eyeLoc.y + fz * eyeLoc.z);
    ViewMatrix.m[3][3] = 1.0f;

    // Inverse view matrix
    InvVMatrix.m[0][0] = rx;  InvVMatrix.m[0][1] = ry;  InvVMatrix.m[0][2] = rz;  InvVMatrix.m[0][3] = 0.0f;
    InvVMatrix.m[1][0] = ux;  InvVMatrix.m[1][1] = uy;  InvVMatrix.m[1][2] = uz;  InvVMatrix.m[1][3] = 0.0f;
    InvVMatrix.m[2][0] = fx;  InvVMatrix.m[2][1] = fy;  InvVMatrix.m[2][2] = fz;  InvVMatrix.m[2][3] = 0.0f;
    InvVMatrix.m[3][0] = eyeLoc.x;
    InvVMatrix.m[3][1] = eyeLoc.y;
    InvVMatrix.m[3][2] = eyeLoc.z;
    InvVMatrix.m[3][3] = 1.0f;

    // Derive quaternion from the view matrix for eyeDir
    eyeDir.SetMatrix(&InvVMatrix);
}

// 0x10021a10 (97B) - Get view dimensions on near plane (private)
void gbCamera::GetViewSizeOnNearPlane(float& w, float& h) {
    if (fov != 0.0f) {
        float angle = fov * 0.008726646f;
        float sinVal = (float)sin(angle);
        float cosVal = (float)cos(angle);
        float size = sinVal * zNear / cosVal;
        w = size;
        h = (float)Viewport.height * size / (float)Viewport.width;
    } else {
        float size = OrthoSize;
        w = size;
        h = (float)Viewport.height * size / (float)Viewport.width;
    }
}

// 0x10021a80 (460B) - Set this camera as the current rendering camera
void gbCamera::SetAsCurrent(int mode) {
    if (!pGfxMgr)
        return;

    // Compute half-size for projection
    float halfSize;
    if (fov == 0.0f) {
        halfSize = OrthoSize;
    } else {
        float sinVal = (float)sin(fov * 0.008726646f);
        float cosVal = (float)cos(fov * 0.008726646f);
        halfSize = (sinVal * zNear) / cosVal;
    }
    float aspectHalf = ((float)Viewport.height * halfSize) / (float)Viewport.width;

    if (mode & 1) {
        // Load identity into world matrix stack (pMatrixStack[0])
        pGfxMgr->pMatrixStack[0]->LoadIdentity();

        if (fov == 0.0f) {
            pGfxMgr->SetOrtho((double)-halfSize, (double)halfSize, (double)-aspectHalf, (double)aspectHalf,
               (double)zNear, (double)zFar);
        } else {
            pGfxMgr->SetFrustum((double)-halfSize, (double)halfSize, (double)-aspectHalf, (double)aspectHalf,
               (double)zNear, (double)zFar);
        }

        pGfxMgr->SetViewport(&Viewport);
    }

    if (mode & 2) {
        // Get rotation matrix from quaternion → InvVMatrix
        eyeDir.GetMatrix(&InvVMatrix);

        // Build translation matrix and multiply
        gbMatrix4 transMat;
        transMat.LoadIdentity();
        transMat.m[3][0] = eyeLoc.x;
        transMat.m[3][1] = eyeLoc.y;
        transMat.m[3][2] = eyeLoc.z;
        transMat *= InvVMatrix;
        InvVMatrix = transMat;

        // Invert to get ViewMatrix
        InvVMatrix.Invert(&ViewMatrix);

        // Set camera matrices in GfxManager
        pGfxMgr->SetCameraMatrix(InvVMatrix, ViewMatrix);

        // Load ViewMatrix into projection matrix stack (pMatrixStack[1])
        pGfxMgr->pMatrixStack[1]->LoadMatrix(&ViewMatrix);
    }

    pGfxMgr->GetFrustumPlanes((float*)&Viewport, 1);

    numPlane = 6;
}

// 0x10021c50 (39B) - Set screen dimensions
void gbCamera::SetDimention(int w, int h) {
    Viewport.x = 0;
    Viewport.y = 0;
    Wscreen = (float)w;
    Viewport.width = w;
    Viewport.height = h;
    Hscreen = (float)h;
}

// ======================================================================
// Frustum clipping methods
// ======================================================================

// 0x10021c80 (253B) - Clip AABB against frustum
// flags indicates which planes to test (bit per plane)
// Returns bitmask of planes that intersect; 0 if fully outside
unsigned int gbCamera::ClipAABBox(gbVec3D* vMin, gbVec3D* vMax, unsigned int flags) {
    if (!vMin || !vMax)
        return 0;

    unsigned int result = 0;

    for (int i = 0; i < numPlane; i++) {
        if (!(flags & (1u << i)))
            continue;

        float nx = Plane[i][0];
        float ny = Plane[i][1];
        float nz = Plane[i][2];
        float d  = Plane[i][3];

        // Find the positive vertex (farthest along plane normal)
        float px = (nx >= 0.0f) ? vMax->x : vMin->x;
        float py = (ny >= 0.0f) ? vMax->y : vMin->y;
        float pz = (nz >= 0.0f) ? vMax->z : vMin->z;

        if (nx * px + ny * py + nz * pz + d < 0.0f)
            return 0;

        // Find the negative vertex
        float qx = (nx >= 0.0f) ? vMin->x : vMax->x;
        float qy = (ny >= 0.0f) ? vMin->y : vMax->y;
        float qz = (nz >= 0.0f) ? vMin->z : vMax->z;

        if (nx * qx + ny * qy + nz * qz + d < 0.0f)
            result |= (1u << i);
    }

    return result;
}

// 0x10021d80 (381B) - Clip OBB against frustum
int gbCamera::ClipOBBox(gbOBBox* obb) {
    gbVec3D corners[8];
    gbVec3D transformed;
    gbVec3D localPt;
    int outsideCount = 0;

    float* pCorner = (float*)&corners[0];
    int initCount = 8;
    do {
        *(pCorner - 2) = 0.0f;
        *(pCorner - 1) = 0.0f;
        *pCorner = 0.0f;
        pCorner += 3;
        --initCount;
    } while (initCount);

    localPt.x = 0.0f;
    localPt.y = 0.0f;
    localPt.z = 0.0f;

    float hx = obb->extent.x * 0.5f;
    float hy = obb->extent.y * 0.5f;
    float hz = obb->extent.z * 0.5f;

    corners[0].x = hx;   corners[0].y = hy;   corners[0].z = hz;
    corners[1].x = -hx;  corners[1].y = hy;   corners[1].z = hz;
    corners[2].x = hx;   corners[2].y = -hy;  corners[2].z = hz;
    corners[3].x = -hx;  corners[3].y = -hy;  corners[3].z = hz;
    corners[4].x = hx;   corners[4].y = hy;   corners[4].z = -hz;
    corners[5].x = -hx;  corners[5].y = hy;   corners[5].z = -hz;
    corners[6].x = hx;   corners[6].y = -hy;  corners[6].z = -hz;
    corners[7].x = -hx;  corners[7].y = -hy;  corners[7].z = -hz;

    int remaining = 8;
    do {
        obb->matrix.Transform(&localPt, &transformed);
        int planeCount = numPlane;
        int planeIdx = 0;
        if (planeCount > 0) {
            float* pPlane = &Plane[0][2];
            while (transformed.x * *(pPlane - 2) + transformed.y * *(pPlane - 1) + transformed.z * *pPlane + *(pPlane + 1) >= 0.0f) {
                ++planeIdx;
                pPlane += 4;
                if (planeIdx >= planeCount)
                    goto next_corner;
            }
            ++outsideCount;
        }
next_corner:
        --remaining;
    } while (remaining);

    return outsideCount == 8;
}

// 0x10021f00 (82B) - Clip point against frustum
// From Ghidra: iterates planes, returns 1 if any dot < 0 (outside)
int gbCamera::ClipPoint(gbVec3D* pt) {
    int i = 0;
    if (0 < numPlane) {
        float* pPlane = &Plane[0][1]; // start at ny of plane 0 (+0x34 offset)
        do {
            if (*(pPlane - 1) * pt->x +    // nx * x
                *pPlane * pt->y +            // ny * y
                *(pPlane + 1) * pt->z +      // nz * z
                *(pPlane + 2) < 0.0f)        // + d
                return 1;
            i++;
            pPlane += 4; // next plane (4 floats)
        } while (i < numPlane);
    }
    return 0;
}

// 0x10021f60 (90B) - Clip sphere against frustum
// From Ghidra: returns 1 if any plane distance < -radius
int gbCamera::ClipSphere(gbVec3D* center, float radius) {
    int i = 0;
    if (0 < numPlane) {
        float* pPlane = &Plane[0][1]; // start at ny
        do {
            if (*(pPlane - 1) * center->x +
                *pPlane * center->y +
                *(pPlane + 1) * center->z +
                *(pPlane + 2) < -radius)
                return 1;
            i++;
            pPlane += 4;
        } while (i < numPlane);
    }
    return 0;
}

// ======================================================================
// Coordinate transformation methods
// ======================================================================

// 0x10021fc0 (111B) - Convert screen coordinates to world point
void gbCamera::PointScrToWorld(float sx, float sy, gbVec3D* worldPt) {
    if (!worldPt)
        return;

    float halfH = zNear * (float)tan(fov * 0.5f);
    float halfW = halfH * GetAspect();

    float nx = (2.0f * sx / Wscreen - 1.0f) * halfW;
    float ny = (1.0f - 2.0f * sy / Hscreen) * halfH;

    gbVec3D eyePt;
    eyePt.x = nx;
    eyePt.y = ny;
    eyePt.z = zNear;

    worldPt->x = InvVMatrix.m[0][0] * eyePt.x + InvVMatrix.m[1][0] * eyePt.y
               + InvVMatrix.m[2][0] * eyePt.z + InvVMatrix.m[3][0];
    worldPt->y = InvVMatrix.m[0][1] * eyePt.x + InvVMatrix.m[1][1] * eyePt.y
               + InvVMatrix.m[2][1] * eyePt.z + InvVMatrix.m[3][1];
    worldPt->z = InvVMatrix.m[0][2] * eyePt.x + InvVMatrix.m[1][2] * eyePt.y
               + InvVMatrix.m[2][2] * eyePt.z + InvVMatrix.m[3][2];
}

// 0x10022030 (24B) - Transform world point to eye space
void gbCamera::PointWorldToEye(gbVec3D* worldPt, gbVec3D* eyePt) {
    ViewMatrix.Transform(worldPt, eyePt);
}

// 0x10022050 (91B) - Convert screen coordinates to eye space
void gbCamera::PointScrToEye(float sx, float sy, gbVec3D* eyePt) {
    if (!eyePt)
        return;

    float halfH = zNear * (float)tan(fov * 0.5f);
    float halfW = halfH * GetAspect();

    eyePt->x = (2.0f * sx / Wscreen - 1.0f) * halfW;
    eyePt->y = (1.0f - 2.0f * sy / Hscreen) * halfH;
    eyePt->z = zNear;
}

// 0x100220b0 (184B) - Convert eye-space point to screen coordinates (NDC output)
void gbCamera::PointEyeToScr(gbVec3D* eyePt, float& sx, float& sy) {
    if (-zNear < eyePt->z || -zFar > eyePt->z) {
        sx = 100000.0f;
    } else if (fov == 0.0f) {
        double ortho = OrthoSize;
        float aspect = (float)((double)Viewport.height * ortho / (double)Viewport.width);
        sx = (float)(sx / ortho);
        sy = sy / aspect;
    } else {
        double tanFov = sin(fov * 0.0087266462) / cos(fov * 0.0087266462);
        float aspect = (float)((double)Viewport.height * tanFov / (double)Viewport.width);
        sx = (float)(-(eyePt->x / eyePt->z) / tanFov);
        sy = (float)(-((eyePt->y / eyePt->z)) / aspect);
    }
}

// 0x10022170 (217B) - Convert eye-space point to screen (gbVec3D version)
void gbCamera::PointEyeToScr(gbVec3D* eyePt, gbVec3D* scrPt) {
    if (eyePt->z <= -zNear && -zFar <= eyePt->z) {
        if (fov != 0.0f) {
            float angle = fov * 0.008726646f;
            float tanFov = (float)sin(angle) / (float)cos(angle);
            float aspect = (float)Viewport.height * tanFov / (float)Viewport.width;
            scrPt->x = -(eyePt->x / eyePt->z) / tanFov;
            scrPt->y = -(eyePt->y / eyePt->z) / aspect;
            scrPt->z = (-eyePt->z - zNear) / (zFar - zNear);
        } else {
            float aspect = (float)Viewport.height * OrthoSize / (float)Viewport.width;
            scrPt->x = scrPt->x / OrthoSize;
            scrPt->y = scrPt->y / aspect;
            scrPt->z = (-scrPt->z - zNear) / (zFar - zNear);
        }
        return;
    }
    scrPt->x = 100000.0f;
}

// 0x10022250 (24B) - Transform eye-space point to world
void gbCamera::PointEyetoWorld(gbVec3D* eyePt, gbVec3D* worldPt) {
    InvVMatrix.Transform(eyePt, worldPt);
}

// 0x10022270 (80B) - Convert world point to screen coordinates
// Note: uses float& references
void gbCamera::PointWorldToScr(gbVec3D* worldPt, float& sx, float& sy) {
    if (!worldPt) {
        sx = 0.0f;
        sy = 0.0f;
        return;
    }
    gbVec3D eyePt;
    PointWorldToEye(worldPt, &eyePt);
    PointEyeToScr(&eyePt, sx, sy);
}

// 0x100222c0 (268B) - Get a ray from camera through screen point
void gbCamera::GetRayToScreen(float sx, float sy, gbRay* ray) {
    float halfW;
    float halfH;
    gbVec3D origin;
    gbVec3D direction;

    direction.x = 0.0f;
    direction.y = 0.0f;
    direction.z = 0.0f;
    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;

    if (fov == 0.0f) {
        float ortho = OrthoSize;
        halfH = (double)Viewport.height * ortho / (double)Viewport.width;
        direction.x = 0.0f;
        direction.y = 0.0f;
        direction.z = -1.0f;
        origin.x = ortho * sx;
        origin.y = halfH * sy;
        origin.z = -zNear;
    } else {
        GetViewSizeOnNearPlane(halfW, halfH);
        origin.x = 0.0f;
        origin.y = 0.0f;
        origin.z = 0.0f;
        direction.x = halfW * sx;
        direction.y = halfH * sy;
        direction.z = -zNear;
    }

    InvVMatrix.Transform(&origin, (gbVec3D*)ray);
    InvVMatrix.Rotate(&direction, (gbVec3D*)((char*)ray + 12));
    ((gbVec3D*)((char*)ray + 12))->Normalize();
}

// 0x100223d0 (109B) - Get viewport bounds in NDC [-1, 1]
void gbCamera::GetViewPort(float& x, float& y, float& w, float& h) {
    int tmp;
    x = (float)Viewport.x * 2.0f / Wscreen - 1.0f;
    y = (float)Viewport.y * 2.0f / Hscreen - 1.0f;
    tmp = Viewport.width + Viewport.x;
    w = (float)tmp * 2.0f / Wscreen - 1.0f;
    tmp = Viewport.height + Viewport.y;
    h = (float)tmp * 2.0f / Hscreen - 1.0f;
}

// 0x10022440 (67B) - Convert device coordinates to screen coordinates
void gbCamera::PointDevToScr(int* dx, int* dy, float sx, float sy) {
    *dx = (int)((sx + 1.0f) * Wscreen * 0.5f);
    *dy = (int)((sy + 1.0f) * Hscreen * 0.5f);
}

// 0x10022490 (24B) - Rotate vector with axis parameter
// 0x10022490 (24B) - Rotate vector with axis parameter (axis ignored in original)
void gbCamera::RotateVector(gbVec3D* in, gbVec3D* out, gbAxis axis) {
    InvVMatrix.Rotate(in, out);
}

// 0x100224b0 (39B) - Offset Z-buffer
void gbCamera::OffsetZBuffer(double offset) {
    Viewport.maxz = (float)(1.0 - offset * 0.0000152587890625);
    pGfxMgr->SetViewport(&Viewport);
}

// 0x100224e0 (25B) - Recover Z-buffer to normal state
void gbCamera::RecoverZBuffer(void) {
    Viewport.maxz = 1.0f;
    pGfxMgr->SetViewport(&Viewport);
}

// 0x10022500 (130B) - Move camera along its forward direction
void gbCamera::MoveInEyeDir(float dist) {
    gbVec3D result;
    gbVec3D dir;
    result.x = 0.0f;
    result.y = 0.0f;
    result.z = 0.0f;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = dist;
    eyeDir.RotateVector(&dir, &result);
    eyeLoc.x += result.x;
    eyeLoc.y += result.y;
    eyeLoc.z += result.z;
}

// 0x10022590 (83B) - Update camera (called each frame)
void gbCamera::Update(double deltaTime) {
    gbCamControler* ctrl = pControl[CurCtrl];
    ctrl->curTime = ctrl->curTime + deltaTime;
    ctrl->Update(deltaTime);
    if (ctrl->blendTime >= 0.0 && ctrl->curTime > ctrl->blendTime) {
        CurCtrl--;
    }
}

// 0x100225f0 (54B) - Add a camera controller
void gbCamera::AddControler(gbCamControler* ctrl, double blendTime) {
    int idx = CurCtrl + 1;
    CurCtrl = idx;
    pControl[idx] = ctrl;
    ctrl->pCamera = this;
    ((int*)&ctrl->curTime)[0] = 0;
    ((int*)&ctrl->curTime)[1] = 0;
    ctrl->blendTime = blendTime;
}

// 0x10022630 (171B) - Project world point to screen without viewport transform
// Note: uses float& references
void gbCamera::PointWorld2Scr_NR(gbVec3D* worldPt, float& sx, float& sy) {
    if (!worldPt) {
        sx = 0.0f;
        sy = 0.0f;
        return;
    }

    gbVec3D eyePt;
    PointWorldToEye(worldPt, &eyePt);

    if (eyePt.z <= 0.0f) {
        sx = 0.0f;
        sy = 0.0f;
        return;
    }

    float halfH = zNear * (float)tan(fov * 0.5f);
    float halfW = halfH * GetAspect();

    float invZ = 1.0f / eyePt.z;
    sx = eyePt.x * invZ / halfW;
    sy = eyePt.y * invZ / halfH;
}
