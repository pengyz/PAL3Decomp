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
#include <math.h>
#include <string.h>

// External globals
extern gbGfxManager* g_pGfxManager;


/* ======================================================================== */
/* gbCamControler method implementations                                    */
/* ======================================================================== */

// 0x10005b20 (9B) - Default constructor
gbCamControler::gbCamControler(void) {
    type = 0;
    pCamera = 0;
}

// 0x10005b30 (45B) - Copy constructor
gbCamControler::gbCamControler(const gbCamControler& other) {
    type = other.type;
    pCamera = other.pCamera;
}

// 0x10005b60 - operator=
gbCamControler& gbCamControler::operator=(const gbCamControler& other) {
    if (this != &other) {
        type = other.type;
        pCamera = other.pCamera;
    }
    return *this;
}

// Virtual destructor
gbCamControler::~gbCamControler() {}

// Virtual Update (base does nothing)
void gbCamControler::Update(double deltaTime) {}


/* ======================================================================== */
/* gbCamSpringControl method implementations                                */
/* ======================================================================== */

// 0x10005b90 (43B) - Default constructor
gbCamSpringControl::gbCamSpringControl(void) : gbCamControler() {
    type = 1;
    springConstant = 10.0f;
    damping = 5.0f;
    targetDist = 10.0f;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    velocity.z = 0.0f;
}

// 0x10005bc0 (111B) - Copy constructor
gbCamSpringControl::gbCamSpringControl(const gbCamSpringControl& other) : gbCamControler(other) {
    springConstant = other.springConstant;
    damping = other.damping;
    targetDist = other.targetDist;
    velocity = other.velocity;
}

// 0x10005c30 - operator=
gbCamSpringControl& gbCamSpringControl::operator=(const gbCamSpringControl& other) {
    if (this != &other) {
        gbCamControler::operator=(other);
        springConstant = other.springConstant;
        damping = other.damping;
        targetDist = other.targetDist;
        velocity = other.velocity;
    }
    return *this;
}

// 0x10021700 (295B) - Spring update
void gbCamSpringControl::Update(double deltaTime) {
    // Spring-based camera follow logic
    // The real implementation computes spring force, applies damping,
    // and updates the camera position based on the spring model.
}


/* ======================================================================== */
/* gbCamQuakeControl method implementations                                 */
/* ======================================================================== */

// 0x10005c90 (29B) - Default constructor
gbCamQuakeControl::gbCamQuakeControl(void) : gbCamControler() {
    type = 2;
    amplitude = 0.0f;
    frequency = 0.0f;
    duration = 0.0f;
    elapsed = 0.0f;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = 0.0f;
}

// 0x10005cb0 (111B) - Copy constructor
gbCamQuakeControl::gbCamQuakeControl(const gbCamQuakeControl& other) : gbCamControler(other) {
    amplitude = other.amplitude;
    frequency = other.frequency;
    duration = other.duration;
    elapsed = other.elapsed;
    offset = other.offset;
}

// 0x10005d20 - operator=
gbCamQuakeControl& gbCamQuakeControl::operator=(const gbCamQuakeControl& other) {
    if (this != &other) {
        gbCamControler::operator=(other);
        amplitude = other.amplitude;
        frequency = other.frequency;
        duration = other.duration;
        elapsed = other.elapsed;
        offset = other.offset;
    }
    return *this;
}

// 0x10021830 (149B) - Quake update
void gbCamQuakeControl::Update(double deltaTime) {
    // Camera shake logic
    // The real implementation applies sinusoidal offset based on
    // amplitude, frequency, and elapsed time.
    elapsed += (float)deltaTime;
    if (elapsed >= duration) {
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 0.0f;
    }
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

// 0x10005a20 - operator=
gbCamera& gbCamera::operator=(const gbCamera& other) {
    if (this != &other) {
        fov = other.fov;
        OrthoSize = other.OrthoSize;
        Wscreen = other.Wscreen;
        Hscreen = other.Hscreen;
        zNear = other.zNear;
        zFar = other.zFar;
        memcpy(&Viewport, &other.Viewport, sizeof(Viewport));
        memcpy(Plane, other.Plane, sizeof(Plane));
        numPlane = other.numPlane;
        memcpy(&ViewMatrix, &other.ViewMatrix, sizeof(gbMatrix4));
        memcpy(&InvVMatrix, &other.InvVMatrix, sizeof(gbMatrix4));
        memcpy(pControl, other.pControl, sizeof(pControl));
        CurCtrl = other.CurCtrl;
        pGfxMgr = other.pGfxMgr;
        eyeLoc = other.eyeLoc;
        eyeDir = other.eyeDir;
    }
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
    if (dir)
        eyeDir = *dir;
}

// 0x10005930 (16B)
void gbCamera::SetOrthoSize(float size) {
    OrthoSize = size;
}

// 0x10005940 (16B) - SetFOV (note: uppercase FOV)
void gbCamera::SetFOV(float f) {
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

// 0x100059b0 (20B)
float gbCamera::GetAspect(void) {
    if (Hscreen > 0.0f)
        return Wscreen / Hscreen;
    return 1.0f;
}

// 0x100059c0 (24B) - Rotate vector by camera orientation (eye to world)
void gbCamera::RotateVector(gbVec3D* in, gbVec3D* out) {
    if (!in || !out)
        return;
    out->x = InvVMatrix.m[0][0] * in->x + InvVMatrix.m[1][0] * in->y + InvVMatrix.m[2][0] * in->z;
    out->y = InvVMatrix.m[0][1] * in->x + InvVMatrix.m[1][1] * in->y + InvVMatrix.m[2][1] * in->z;
    out->z = InvVMatrix.m[0][2] * in->x + InvVMatrix.m[1][2] * in->y + InvVMatrix.m[2][2] * in->z;
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
    if (CurCtrl >= 0 && CurCtrl < 16)
        return pControl[CurCtrl];
    return 0;
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
// Note: signature uses float& (references), not pointers
void gbCamera::GetViewSizeOnNearPlane(float& w, float& h) {
    float halfH = zNear * (float)tan(fov * 0.5f);
    float halfW = halfH * GetAspect();
    w = halfW * 2.0f;
    h = halfH * 2.0f;
}

// 0x10021a80 (460B) - Set this camera as the current rendering camera
void gbCamera::SetAsCurrent(int mode) {
    if (!pGfxMgr)
        return;

    // Set this camera as the active camera in the gfx manager
    // pGfxMgr->pCamera = this;
    // Access pCamera field at known offset in gbGfxManager
    gbCamera** ppCam = (gbCamera**)((char*)pGfxMgr + 0xD8);
    *ppCam = this;

    // Build view matrix from quaternion orientation
    BuildViewFromQuaternion();

    // Build projection matrix
    gbMatrix4 projMatrix;
    BuildProjMatrix(&projMatrix);

    // Build combined view-projection for frustum planes
    gbMatrix4 viewProj;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            viewProj.m[i][j] = ViewMatrix.m[i][0] * projMatrix.m[0][j]
                             + ViewMatrix.m[i][1] * projMatrix.m[1][j]
                             + ViewMatrix.m[i][2] * projMatrix.m[2][j]
                             + ViewMatrix.m[i][3] * projMatrix.m[3][j];
        }
    }
    BuildFrustumPlanes(&viewProj);

    // Push view and projection to the graphics manager
    // In the real engine this calls SetTransform on the D3D device
}

// 0x10021c50 (39B) - Set screen dimensions
void gbCamera::SetDimention(int w, int h) {
    Wscreen = (float)w;
    Hscreen = (float)h;
    Viewport.width = w;
    Viewport.height = h;
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
    if (!obb)
        return 0;

    for (int i = 0; i < numPlane; i++) {
        float nx = Plane[i][0];
        float ny = Plane[i][1];
        float nz = Plane[i][2];
        float d  = Plane[i][3];

        float dist = nx * obb->center.x + ny * obb->center.y + nz * obb->center.z + d;

        float r = 0.0f;
        for (int a = 0; a < 3; a++) {
            float dot = nx * obb->axis[a].x + ny * obb->axis[a].y + nz * obb->axis[a].z;
            float ext;
            if (a == 0)      ext = obb->extent.x;
            else if (a == 1) ext = obb->extent.y;
            else             ext = obb->extent.z;
            r += (float)fabs(dot) * ext;
        }

        if (dist < -r)
            return 0;
    }

    return 1;
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
    if (!worldPt || !eyePt)
        return;
    eyePt->x = ViewMatrix.m[0][0] * worldPt->x + ViewMatrix.m[1][0] * worldPt->y
              + ViewMatrix.m[2][0] * worldPt->z + ViewMatrix.m[3][0];
    eyePt->y = ViewMatrix.m[0][1] * worldPt->x + ViewMatrix.m[1][1] * worldPt->y
              + ViewMatrix.m[2][1] * worldPt->z + ViewMatrix.m[3][1];
    eyePt->z = ViewMatrix.m[0][2] * worldPt->x + ViewMatrix.m[1][2] * worldPt->y
              + ViewMatrix.m[2][2] * worldPt->z + ViewMatrix.m[3][2];
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

// 0x100220b0 (184B) - Convert eye-space point to screen coordinates
// Note: uses float& references, not pointers
void gbCamera::PointEyeToScr(gbVec3D* eyePt, float& sx, float& sy) {
    if (!eyePt) {
        sx = 0.0f;
        sy = 0.0f;
        return;
    }

    if (eyePt->z <= 0.0f) {
        sx = 0.0f;
        sy = 0.0f;
        return;
    }

    float halfH = zNear * (float)tan(fov * 0.5f);
    float halfW = halfH * GetAspect();

    float invZ = 1.0f / eyePt->z;
    float projX = eyePt->x * invZ;
    float projY = eyePt->y * invZ;

    sx = (projX / halfW + 1.0f) * 0.5f * Wscreen;
    sy = (1.0f - projY / halfH) * 0.5f * Hscreen;
}

// 0x10022170 (217B) - Convert eye-space point to screen (gbVec3D version)
void gbCamera::PointEyeToScr(gbVec3D* eyePt, gbVec3D* scrPt) {
    if (!eyePt || !scrPt)
        return;

    float sx, sy;
    PointEyeToScr(eyePt, sx, sy);
    scrPt->x = sx;
    scrPt->y = sy;
    scrPt->z = eyePt->z;
}

// 0x10022250 (24B) - Transform eye-space point to world
// Note: lowercase 't' in "to" - matches export symbol exactly
void gbCamera::PointEyetoWorld(gbVec3D* eyePt, gbVec3D* worldPt) {
    if (!eyePt || !worldPt)
        return;
    worldPt->x = InvVMatrix.m[0][0] * eyePt->x + InvVMatrix.m[1][0] * eyePt->y
                + InvVMatrix.m[2][0] * eyePt->z + InvVMatrix.m[3][0];
    worldPt->y = InvVMatrix.m[0][1] * eyePt->x + InvVMatrix.m[1][1] * eyePt->y
                + InvVMatrix.m[2][1] * eyePt->z + InvVMatrix.m[3][1];
    worldPt->z = InvVMatrix.m[0][2] * eyePt->x + InvVMatrix.m[1][2] * eyePt->y
                + InvVMatrix.m[2][2] * eyePt->z + InvVMatrix.m[3][2];
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
    if (!ray)
        return;

    ray->origin = eyeLoc;

    gbVec3D nearPt;
    PointScrToWorld(sx, sy, &nearPt);

    ray->direction.x = nearPt.x - eyeLoc.x;
    ray->direction.y = nearPt.y - eyeLoc.y;
    ray->direction.z = nearPt.z - eyeLoc.z;

    float len = (float)sqrt(ray->direction.x * ray->direction.x
                          + ray->direction.y * ray->direction.y
                          + ray->direction.z * ray->direction.z);
    if (len > 1e-6f) {
        float invLen = 1.0f / len;
        ray->direction.x *= invLen;
        ray->direction.y *= invLen;
        ray->direction.z *= invLen;
    }
}

// 0x100223d0 (109B) - Get viewport bounds as float references
void gbCamera::GetViewPort(float& x, float& y, float& w, float& h) {
    x = (float)Viewport.x;
    y = (float)Viewport.y;
    w = (float)Viewport.width;
    h = (float)Viewport.height;
}

// 0x10022440 (67B) - Convert device coordinates to screen coordinates
void gbCamera::PointDevToScr(int* dx, int* dy, float sx, float sy) {
    if (!dx || !dy)
        return;
    *dx = (int)(sx - (float)Viewport.x);
    *dy = (int)(sy - (float)Viewport.y);
}

// 0x10022490 (24B) - Rotate vector with axis parameter
// Note: uses gbAxis enum, not int
void gbCamera::RotateVector(gbVec3D* in, gbVec3D* out, gbAxis axis) {
    if (!in || !out)
        return;

    // When axis parameter is specified, rotate using the corresponding
    // axis from the view/inverse view matrix
    if (axis == GB_AXIS_X) {
        // Rotate by inverse view (eye to world)
        out->x = InvVMatrix.m[0][0] * in->x + InvVMatrix.m[1][0] * in->y + InvVMatrix.m[2][0] * in->z;
        out->y = InvVMatrix.m[0][1] * in->x + InvVMatrix.m[1][1] * in->y + InvVMatrix.m[2][1] * in->z;
        out->z = InvVMatrix.m[0][2] * in->x + InvVMatrix.m[1][2] * in->y + InvVMatrix.m[2][2] * in->z;
    } else {
        // Rotate by view matrix (world to eye)
        out->x = ViewMatrix.m[0][0] * in->x + ViewMatrix.m[1][0] * in->y + ViewMatrix.m[2][0] * in->z;
        out->y = ViewMatrix.m[0][1] * in->x + ViewMatrix.m[1][1] * in->y + ViewMatrix.m[2][1] * in->z;
        out->z = ViewMatrix.m[0][2] * in->x + ViewMatrix.m[1][2] * in->y + ViewMatrix.m[2][2] * in->z;
    }
}

// 0x100224b0 (39B) - Offset Z-buffer
void gbCamera::OffsetZBuffer(double offset) {
    // In the real engine, delegates to gbGfxManager::OffsetZBuffer
    // which sets D3DRS_DEPTHBIAS / D3DRS_SLOPESCALEDEPTHBIAS
}

// 0x100224e0 (25B) - Recover Z-buffer to normal state
void gbCamera::RecoverZBuffer(void) {
    // In the real engine, resets depth bias to 0
}

// 0x10022500 (130B) - Move camera along its forward direction
void gbCamera::MoveInEyeDir(float dist) {
    float fx = InvVMatrix.m[2][0];
    float fy = InvVMatrix.m[2][1];
    float fz = InvVMatrix.m[2][2];

    eyeLoc.x += fx * dist;
    eyeLoc.y += fy * dist;
    eyeLoc.z += fz * dist;
}

// 0x10022590 (83B) - Update camera (called each frame)
void gbCamera::Update(double deltaTime) {
    // Update all active controllers
    for (int i = 0; i <= CurCtrl && i < 16; i++) {
        if (pControl[i]) {
            pControl[i]->Update(deltaTime);
        }
    }
}

// 0x100225f0 (54B) - Add a camera controller
// From Ghidra: stores controller at pControl[CurCtrl+1], increments CurCtrl
void gbCamera::AddControler(gbCamControler* ctrl, double blendTime) {
    if (!ctrl)
        return;

    int idx = CurCtrl;
    CurCtrl = idx + 1;
    pControl[idx + 1] = ctrl;
    ctrl->pCamera = this;
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
