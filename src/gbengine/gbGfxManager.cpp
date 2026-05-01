/**
 * gbengine.dll - gbGfxManager, gbCamera, gbRenderEffect, gbEffectMgr
 *
 * Functional decompilation of graphics management, camera, and effect classes.
 * Based on PAL3patch struct definitions and Ghidra export analysis.
 *
 * Compiler: MSVC 6.0 SP5
 * Graphics: DirectX 9 (Summer 2003 SDK)
 */

#include "gbengine/gbengine_types.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Forward declarations
class gbTexture;
class gbTexture_D3D;
class gbTextureArray;
class gbImage2D;
class gbBaseMesh;
class gbStaticMesh;
class gbResManager;
class gbResource;
class gbVFileSystem;
class gbVFile;
class gbVertPoolMgr;
class gbVertexPool;
class gbDynVertBuf;
class gbPrintFont;
class gbPrintFontMgr;
class gbMatrixStack;
class gbVisNode;
class gbGeomNode;
class gbRefObject;

// Forward declarations for classes defined in this file
class gbGfxManager;
class gbCamera;
class gbRenderEffect;
class gbEffectMgr;
class gbCamControler;
class gbSceneGraph;

// Pixel format enum (matches gbengine's internal enum)
// gbPixelFmtType is defined in gbengine_types.h

// External globals
extern gbGfxManager* g_pGfxManager;
extern double g_CurrentTime;
extern unsigned int g_CurrentTick;

// D3D transform type constants used by the engine
// (maps to D3DTS_WORLD, D3DTS_VIEW, D3DTS_PROJECTION, etc.)
enum gbTransformType {
    GB_TM_WORLD = 0,
    GB_TM_VIEW = 1,
    GB_TM_PROJECTION = 2,
    GB_TM_TEXTURE0 = 3
};

// ============================================================================
// gbGfxDriverInfo - graphics driver initialization info
// ============================================================================
struct gbGfxDriverInfo {
    int type;
    int subtype;
    int width;
    int height;
    int colorbits;
    int depthbits;
    int stensilbits;
    int nbackbuf;
    int fullscreen;
    int refreshrate;
    char winname[0x80];
    unsigned int hinst;     // HINSTANCE
    unsigned int hgfxwnd;   // HWND
    int newwindow;
    int waitforverticalblank;
};

// ============================================================================
// gbViewPort
// ============================================================================
struct gbViewPort {
    int x;
    int y;
    int width;
    int height;
    float minz;
    float maxz;
};

// ============================================================================
// gbCamControler - camera controller base
// ============================================================================
class gbCamControler {
public:
    gbCamera* pCamera;
    int type;

    gbCamControler(void) {
        pCamera = NULL;
        type = 0;
    }

    virtual ~gbCamControler() {}

    virtual void Update(double deltaTime) {}
};


// ============================================================================
// gbGfxManager - main graphics manager
//
// Layout from PAL3patch (sizeof gbGfxManager_D3D = 0x8F0):
//   +0x00: vtable
//   +0x04: flags/state
//   +0x08: scene state
//   +0x0C: gbGfxDriverInfo DrvInfo (0xA4 bytes)
//   +0xB0: gbVertPoolMgr*
//   +0xB4: gbEffectMgr*
//   +0xB8: gbResManager* pTexResMgr
//   +0xBC: gbPrintFontMgr*
//   +0xC0: gbMatrixStack* pMatrixStack[4]
//   ... many more fields in derived gbGfxManager_D3D ...
//   +0x84C: IDirect3DDevice9* m_pd3dDevice (in D3D subclass)
// ============================================================================
class gbGfxManager {
public:
    // Vtable pointer is implicit in C++
    int m_nState;               // +0x04: general state flags
    int m_bInScene;             // +0x08: true while between BeginScene/EndScene

    gbGfxDriverInfo DrvInfo;    // +0x0C: driver info (0xA4 bytes)

    gbVertPoolMgr* pVertPoolMgr;        // +0xB0
    gbEffectMgr* pEffectMgr;            // +0xB4
    gbResManager* pTexResMgr;           // +0xB8
    gbPrintFontMgr* pFontMgr;          // +0xBC
    gbMatrixStack* pMatrixStack[4];     // +0xC0

    gbSceneGraph* pSceneGraph;          // scene graph
    gbCamera* pCamera;                  // active camera

    gbColorFlt m_ambientLight;          // ambient light color
    int m_bEmissiveEnable;              // emissive lighting flag
    float m_fEmissiveFactor;            // emissive scale factor

    double m_lastTime;                  // last frame time
    double m_deltaTime;                 // time between frames
    unsigned int m_lastTick;            // last tick count
    unsigned int m_deltaTick;           // tick delta

    gbMatrix4 m_worldMatrix;            // current world transform
    gbMatrix4 m_viewMatrix;             // current view transform
    gbMatrix4 m_projMatrix;             // current projection transform

    int m_nWireMode;                    // wireframe rendering mode

    // Padding to approximate real struct size
    // gbGfxManager_D3D is 0x8F0 bytes total; the D3D-specific fields
    // (IDirect3D9*, IDirect3DDevice9*, D3DCAPS9, etc.) live in the derived class.
    // We only model the base class here.

    // 0x1001d910 (394B) - Constructor
    gbGfxManager(int& result, gbGfxDriverInfo* driverInfo) {
        m_nState = 0;
        m_bInScene = 0;

        if (driverInfo) {
            memcpy(&DrvInfo, driverInfo, sizeof(gbGfxDriverInfo));
        } else {
            memset(&DrvInfo, 0, sizeof(gbGfxDriverInfo));
        }

        pVertPoolMgr = NULL;
        pEffectMgr = NULL;
        pTexResMgr = NULL;
        pFontMgr = NULL;
        pSceneGraph = NULL;
        pCamera = NULL;

        memset(pMatrixStack, 0, sizeof(pMatrixStack));

        m_ambientLight.r = 0.2f;
        m_ambientLight.g = 0.2f;
        m_ambientLight.b = 0.2f;
        m_ambientLight.a = 1.0f;

        m_bEmissiveEnable = 0;
        m_fEmissiveFactor = 1.0f;

        m_lastTime = 0.0;
        m_deltaTime = 0.0;
        m_lastTick = 0;
        m_deltaTick = 0;

        // Initialize world matrix to identity
        memset(&m_worldMatrix, 0, sizeof(gbMatrix4));
        m_worldMatrix.m[0][0] = 1.0f;
        m_worldMatrix.m[1][1] = 1.0f;
        m_worldMatrix.m[2][2] = 1.0f;
        m_worldMatrix.m[3][3] = 1.0f;

        memset(&m_viewMatrix, 0, sizeof(gbMatrix4));
        m_viewMatrix.m[0][0] = 1.0f;
        m_viewMatrix.m[1][1] = 1.0f;
        m_viewMatrix.m[2][2] = 1.0f;
        m_viewMatrix.m[3][3] = 1.0f;

        memset(&m_projMatrix, 0, sizeof(gbMatrix4));
        m_projMatrix.m[0][0] = 1.0f;
        m_projMatrix.m[1][1] = 1.0f;
        m_projMatrix.m[2][2] = 1.0f;
        m_projMatrix.m[3][3] = 1.0f;

        m_nWireMode = 0;

        result = 1; // success
    }

    // Virtual destructor
    virtual ~gbGfxManager() {
        // Cleanup is handled by derived class (gbGfxManager_D3D)
    }

    // 0x1001db10 (222B) - Begin a rendering scene
    int BeginScene(void) {
        if (m_bInScene)
            return 0;

        // Update time tracking
        double currentTime = g_CurrentTime;
        m_deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        unsigned int currentTick = g_CurrentTick;
        m_deltaTick = currentTick - m_lastTick;
        m_lastTick = currentTick;

        // In the real D3D implementation, this calls IDirect3DDevice9::BeginScene()
        // and clears the render target. The actual D3D calls are in gbGfxManager_D3D.
        m_bInScene = 1;
        return 1;
    }

    // EndScene: finish the rendering scene
    // Note: The actual EndScene (0x10018F00) is in gbGfxManager_D3D and calls
    // IDirect3DDevice9::EndScene() followed by Present(). We model the base behavior.
    void EndScene(void) {
        if (!m_bInScene)
            return;

        // In gbGfxManager_D3D, this calls:
        //   m_pd3dDevice->EndScene();
        //   m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
        m_bInScene = 0;
    }

    // SetTransform: set a transform matrix (world/view/projection)
    void SetTransform(int type, gbMatrix4* matrix) {
        if (!matrix)
            return;

        switch (type) {
        case GB_TM_WORLD:
            memcpy(&m_worldMatrix, matrix, sizeof(gbMatrix4));
            break;
        case GB_TM_VIEW:
            memcpy(&m_viewMatrix, matrix, sizeof(gbMatrix4));
            break;
        case GB_TM_PROJECTION:
            memcpy(&m_projMatrix, matrix, sizeof(gbMatrix4));
            break;
        }

        // In the real engine, this also calls IDirect3DDevice9::SetTransform()
        // with the appropriate D3DTRANSFORMSTATETYPE
    }

    // 0x1001e220 (158B) - Clip a bounding volume against the view frustum
    // Returns: 0 = fully outside, 1 = partially inside, 2 = fully inside
    int ClipBoundVolume(gbAABBox* box) {
        if (!box || !pCamera)
            return 0;

        // Delegate to camera's clip method
        // The camera maintains 6 frustum planes and tests the AABB against them
        gbVec3D minPt, maxPt;
        minPt = box->vMin;
        maxPt = box->vMax;

        // Quick test: call the camera's AABB clip
        // flags parameter 0x3F means test all 6 planes
        // Return value uses same convention: 0=out, 1=partial, 2=in
        // We implement a simplified version here; real logic is in gbCamera::ClipAABBox
        return 1; // assume partially visible as fallback
    }

    // 0x10004ff0 (34B) - Enable/disable emissive lighting
    void EnableEmissive(int enable) {
        m_bEmissiveEnable = enable;
        // In the real engine, this also sets D3D render state
        // D3DRS_EMISSIVEMATERIALSOURCE etc.
    }

    // 0x10005020 (13B) - Set emissive factor
    void SetEmissiveFactor(float factor) {
        m_fEmissiveFactor = factor;
    }

    // 0x10004fc0 (39B) - Get ambient light color
    gbColorFlt GetAmbientLight(int dummy = 0) {
        return m_ambientLight;
    }

    // 0x10004f90 (35B) - Set ambient light color
    void SetAmbientLight(gbColorFlt* color) {
        if (!color)
            return;
        m_ambientLight = *color;

        // In the real engine, this converts to D3DCOLOR and calls
        // IDirect3DDevice9::SetRenderState(D3DRS_AMBIENT, d3dColor)
    }

    // 0x1001dac0 (34B) - Get delta time since last frame
    double GetDeltaTime(void) {
        return m_deltaTime;
    }

    // 0x1001daf0 (27B) - Get delta tick since last frame
    unsigned int GetDeltaTick(void) {
        return m_deltaTick;
    }

    // 0x10004ea0 (13B) - Set scene graph
    void SetSceneGraph(gbSceneGraph* sg) {
        pSceneGraph = sg;
    }

    // 0x10004ed0 (14B) - Get matrix stack by index
    gbMatrixStack* GetMatrixStack(int index) {
        if (index < 0 || index >= 4)
            return NULL;
        return pMatrixStack[index];
    }

    // 0x10004ee0 (16B) - Get print font by type
    gbPrintFont* GetPrintFont(int fontType) {
        // In the real engine, this calls pFontMgr->GetFont(fontType)
        // We return NULL as a stub since we don't have the font manager fully defined
        return NULL;
    }

    // 0x10004f50 (20B) - Get light object by index
    void* GetLight(int index) {
        // Light objects are stored in an array inside the GfxManager
        // Stub: return NULL
        return NULL;
    }

    // 0x10004f70 (14B) - Check if a light is enabled
    int IsLightEnable(int index) {
        return 0;
    }

    // 0x1001df40 (37B) - Get a combined transform matrix
    void GetTMMatrix(int type, gbMatrix4* out) {
        if (!out)
            return;
        switch (type) {
        case GB_TM_WORLD:
            memcpy(out, &m_worldMatrix, sizeof(gbMatrix4));
            break;
        case GB_TM_VIEW:
            memcpy(out, &m_viewMatrix, sizeof(gbMatrix4));
            break;
        case GB_TM_PROJECTION:
            memcpy(out, &m_projMatrix, sizeof(gbMatrix4));
            break;
        }
    }

    // 0x1001e070 (24B) - Get current viewport
    void GetViewport(void* pViewport) {
        // In the real engine, calls IDirect3DDevice9::GetViewport()
        // and converts to the gbViewPort structure
    }

    // 0x1001e090 (35B) - Set clear parameters (color, depth, stencil)
    void SetClearParam(void* pParam) {
        // Stores clear color/depth/stencil values for BeginScene's Clear call
    }

    // 0x1001e160 (189B) - Create a new mesh resource
    gbBaseMesh* NewMesh(char* name, int type) {
        // In the real engine, allocates a gbStaticMesh or derived class
        // and registers it with the resource manager
        return NULL;
    }

    // 0x1001e2c0 (36B) - Offset Z-buffer for decal rendering
    void OffsetZBuffer(int enable) {
        // Sets D3DRS_DEPTHBIAS / D3DRS_SLOPESCALEDEPTHBIAS
    }

    // 0x1001e2f0 (13B) - Set wireframe rendering mode
    void SetWireMode(int mode) {
        m_nWireMode = mode;
        // In real engine: SetRenderState(D3DRS_FILLMODE, mode ? D3DFILL_WIREFRAME : D3DFILL_SOLID)
    }

    // 0x1001e300 (38B) - Set fog parameters
    void SetFog(void* pFogParam) {
        // Sets D3DRS_FOGENABLE, D3DRS_FOGCOLOR, D3DRS_FOGSTART, D3DRS_FOGEND, etc.
    }

    // 0x1001e330 (55B) - Get world matrix pointer (from top of matrix stack)
    gbMatrix4* GetWorldMatrix(void) {
        if (pMatrixStack[0]) {
            // In the real engine: return pMatrixStack[0]->GetTop()
            // Simplified: return our local copy
        }
        return &m_worldMatrix;
    }

    // 0x1001e380 (19B) - Reset world matrix to identity
    void IdentityWorldMatrix(void) {
        memset(&m_worldMatrix, 0, sizeof(gbMatrix4));
        m_worldMatrix.m[0][0] = 1.0f;
        m_worldMatrix.m[1][1] = 1.0f;
        m_worldMatrix.m[2][2] = 1.0f;
        m_worldMatrix.m[3][3] = 1.0f;

        // Also set on the D3D device
        // SetTransform(GB_TM_WORLD, &m_worldMatrix);
    }

    // 0x1001e3a0 (43B) - Set view and projection matrices from camera
    void SetCameraMatrix(gbMatrix4* view, gbMatrix4* proj) {
        if (view)
            memcpy(&m_viewMatrix, view, sizeof(gbMatrix4));
        if (proj)
            memcpy(&m_projMatrix, proj, sizeof(gbMatrix4));

        // In the real engine, also calls:
        // IDirect3DDevice9::SetTransform(D3DTS_VIEW, (D3DMATRIX*)view)
        // IDirect3DDevice9::SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)proj)
    }
};


// ============================================================================
// gbCamera - view camera with frustum clipping
//
// From PAL3patch: sizeof(gbCamera) = 0x178
//   +0x00: float fov
//   +0x04: float OrthoSize
//   +0x08: float Wscreen
//   +0x0C: float Hscreen
//   +0x10: float zNear
//   +0x14: float zFar
//   +0x18: gbViewPort Viewport (0x18 bytes)
//   +0x30: float Plane[6][4] (0x60 bytes) - 6 frustum planes (nx, ny, nz, d)
//   +0x90: int numPlane
//   +0x94: gbMatrix4 ViewMatrix (0x40 bytes)
//   +0xD4: gbMatrix4 InvVMatrix (0x40 bytes)
//   +0x114: gbCamControler* pControl[16] (0x40 bytes)
//   +0x154: int CurCtrl
//   +0x158: gbGfxManager* pGfxMgr
//   +0x15C: gbVec3D eyeLoc (0x0C bytes)
//   +0x168: gbQuaternion eyeDir (0x10 bytes)
// Total: 0x178
// ============================================================================
class gbCamera {
public:
    float fov;
    float OrthoSize;
    float Wscreen;
    float Hscreen;
    float zNear;
    float zFar;
    gbViewPort Viewport;
    float Plane[6][4];      // 6 frustum planes: (nx, ny, nz, d)
    int numPlane;
    gbMatrix4 ViewMatrix;
    gbMatrix4 InvVMatrix;   // inverse view matrix
    gbCamControler* pControl[16];
    int CurCtrl;
    gbGfxManager* pGfxMgr;
    gbVec3D eyeLoc;
    gbQuaternion eyeDir;

    // Helper: projection matrix (not stored in the original struct, but computed)
    gbMatrix4 ProjMatrix;

    // 0x100218d0 (157B) - Constructor
    gbCamera(gbGfxManager* gfxMgr) {
        pGfxMgr = gfxMgr;

        fov = 45.0f * 3.14159265f / 180.0f; // 45 degrees in radians
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

        // Identity view matrix
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

        memset(&ProjMatrix, 0, sizeof(gbMatrix4));
        ProjMatrix.m[0][0] = 1.0f;
        ProjMatrix.m[1][1] = 1.0f;
        ProjMatrix.m[2][2] = 1.0f;
        ProjMatrix.m[3][3] = 1.0f;

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

    // operator=
    gbCamera& operator=(const gbCamera& other) {
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
            memcpy(&ProjMatrix, &other.ProjMatrix, sizeof(gbMatrix4));
            memcpy(pControl, other.pControl, sizeof(pControl));
            CurCtrl = other.CurCtrl;
            pGfxMgr = other.pGfxMgr;
            eyeLoc = other.eyeLoc;
            eyeDir = other.eyeDir;
        }
        return *this;
    }

    // --- FOV ---

    // 0x10005940 (16B) - Set field of view (in radians)
    void SetFov(float f) {
        fov = f;
    }

    float GetFov(void) {
        return fov;
    }

    // --- Aspect ---

    void SetAspect(float aspect) {
        if (aspect > 0.0f) {
            Wscreen = Hscreen * aspect;
        }
    }

    float GetAspect(void) {
        if (Hscreen > 0.0f)
            return Wscreen / Hscreen;
        return 1.0f;
    }

    // --- Position ---

    void SetPos(gbVec3D* pos) {
        if (pos) {
            eyeLoc = *pos;
        }
    }

    gbVec3D GetPos(void) {
        return eyeLoc;
    }

    // --- Target ---
    // The camera target is derived from eyeLoc + forward direction from eyeDir quaternion.
    // For get/set we store it implicitly via the view matrix.

    void SetTarget(gbVec3D* target) {
        if (!target)
            return;
        // Recompute eye direction from current position to target
        // This would update eyeDir quaternion. Simplified:
        // In the real engine, SetLookAt computes the full view matrix.
    }

    gbVec3D GetTarget(void) {
        // Derive from view matrix: target = eyeLoc + forward
        gbVec3D target;
        // Forward direction is the third row of the inverse view matrix
        target.x = eyeLoc.x + InvVMatrix.m[2][0];
        target.y = eyeLoc.y + InvVMatrix.m[2][1];
        target.z = eyeLoc.z + InvVMatrix.m[2][2];
        return target;
    }

    // --- Up ---

    void SetUp(gbVec3D* up) {
        if (!up)
            return;
        // Store up vector; will be used when MakeView() is called
    }

    gbVec3D GetUp(void) {
        // Up direction is the second row of the inverse view matrix
        gbVec3D up;
        up.x = InvVMatrix.m[1][0];
        up.y = InvVMatrix.m[1][1];
        up.z = InvVMatrix.m[1][2];
        return up;
    }

    // --- Z Range ---

    // 0x10005950 (17B)
    void SetZRange(float nearZ, float farZ) {
        zNear = nearZ;
        zFar = farZ;
    }

    float GetZNear(void) {
        return zNear;
    }

    float GetZFar(void) {
        return zFar;
    }

    // --- View / Projection matrix construction ---

    // Build the view matrix from eye position, target, and up
    void MakeView(void) {
        // The real engine builds the view matrix from eyeLoc and eyeDir quaternion.
        // It constructs a rotation matrix from the quaternion, then combines with translation.
        // We use the D3DX helper as a reference for the math:

        gbVec3D target = GetTarget();
        gbVec3D up = GetUp();

        // Compute forward (z-axis): normalize(target - eye)
        float fx = target.x - eyeLoc.x;
        float fy = target.y - eyeLoc.y;
        float fz = target.z - eyeLoc.z;
        float flen = (float)sqrt(fx * fx + fy * fy + fz * fz);
        if (flen < 1e-6f)
            return;
        fx /= flen; fy /= flen; fz /= flen;

        // Compute right (x-axis): normalize(cross(up, forward))
        float rx = up.y * fz - up.z * fy;
        float ry = up.z * fx - up.x * fz;
        float rz = up.x * fy - up.y * fx;
        float rlen = (float)sqrt(rx * rx + ry * ry + rz * rz);
        if (rlen < 1e-6f)
            return;
        rx /= rlen; ry /= rlen; rz /= rlen;

        // Recompute up: cross(forward, right)
        float ux = fy * rz - fz * ry;
        float uy = fz * rx - fx * rz;
        float uz = fx * ry - fy * rx;

        // Build view matrix (row-major, matches D3D convention)
        ViewMatrix.m[0][0] = rx;  ViewMatrix.m[0][1] = ux;  ViewMatrix.m[0][2] = fx;  ViewMatrix.m[0][3] = 0.0f;
        ViewMatrix.m[1][0] = ry;  ViewMatrix.m[1][1] = uy;  ViewMatrix.m[1][2] = fy;  ViewMatrix.m[1][3] = 0.0f;
        ViewMatrix.m[2][0] = rz;  ViewMatrix.m[2][1] = uz;  ViewMatrix.m[2][2] = fz;  ViewMatrix.m[2][3] = 0.0f;
        ViewMatrix.m[3][0] = -(rx * eyeLoc.x + ry * eyeLoc.y + rz * eyeLoc.z);
        ViewMatrix.m[3][1] = -(ux * eyeLoc.x + uy * eyeLoc.y + uz * eyeLoc.z);
        ViewMatrix.m[3][2] = -(fx * eyeLoc.x + fy * eyeLoc.y + fz * eyeLoc.z);
        ViewMatrix.m[3][3] = 1.0f;

        // Inverse view matrix (transpose of rotation part, negate translation)
        InvVMatrix.m[0][0] = rx;  InvVMatrix.m[0][1] = ry;  InvVMatrix.m[0][2] = rz;  InvVMatrix.m[0][3] = 0.0f;
        InvVMatrix.m[1][0] = ux;  InvVMatrix.m[1][1] = uy;  InvVMatrix.m[1][2] = uz;  InvVMatrix.m[1][3] = 0.0f;
        InvVMatrix.m[2][0] = fx;  InvVMatrix.m[2][1] = fy;  InvVMatrix.m[2][2] = fz;  InvVMatrix.m[2][3] = 0.0f;
        InvVMatrix.m[3][0] = eyeLoc.x;
        InvVMatrix.m[3][1] = eyeLoc.y;
        InvVMatrix.m[3][2] = eyeLoc.z;
        InvVMatrix.m[3][3] = 1.0f;

        // Extract frustum planes from view-projection matrix
        BuildFrustumPlanes();
    }

    // Build perspective projection matrix
    void MakeProj(void) {
        float aspect = GetAspect();
        float h = 1.0f / (float)tan(fov * 0.5f);
        float w = h / aspect;
        float Q = zFar / (zFar - zNear);

        memset(&ProjMatrix, 0, sizeof(gbMatrix4));
        ProjMatrix.m[0][0] = w;
        ProjMatrix.m[1][1] = h;
        ProjMatrix.m[2][2] = Q;
        ProjMatrix.m[2][3] = 1.0f;
        ProjMatrix.m[3][2] = -Q * zNear;
        ProjMatrix.m[3][3] = 0.0f;

        // After building projection, update frustum planes
        BuildFrustumPlanes();
    }

    gbMatrix4* GetViewMatrix(void) {
        return &ViewMatrix;
    }

    gbMatrix4* GetProjMatrix(void) {
        return &ProjMatrix;
    }

    // --- Frustum Clipping ---

    // Helper: extract 6 frustum planes from the combined view-projection matrix
    void BuildFrustumPlanes(void) {
        // Combine view * projection
        // M = ViewMatrix * ProjMatrix
        float combo[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                combo[i][j] = ViewMatrix.m[i][0] * ProjMatrix.m[0][j]
                            + ViewMatrix.m[i][1] * ProjMatrix.m[1][j]
                            + ViewMatrix.m[i][2] * ProjMatrix.m[2][j]
                            + ViewMatrix.m[i][3] * ProjMatrix.m[3][j];
            }
        }

        // Left plane: row3 + row0
        Plane[0][0] = combo[0][3] + combo[0][0];
        Plane[0][1] = combo[1][3] + combo[1][0];
        Plane[0][2] = combo[2][3] + combo[2][0];
        Plane[0][3] = combo[3][3] + combo[3][0];

        // Right plane: row3 - row0
        Plane[1][0] = combo[0][3] - combo[0][0];
        Plane[1][1] = combo[1][3] - combo[1][0];
        Plane[1][2] = combo[2][3] - combo[2][0];
        Plane[1][3] = combo[3][3] - combo[3][0];

        // Bottom plane: row3 + row1
        Plane[2][0] = combo[0][3] + combo[0][1];
        Plane[2][1] = combo[1][3] + combo[1][1];
        Plane[2][2] = combo[2][3] + combo[2][1];
        Plane[2][3] = combo[3][3] + combo[3][1];

        // Top plane: row3 - row1
        Plane[3][0] = combo[0][3] - combo[0][1];
        Plane[3][1] = combo[1][3] - combo[1][1];
        Plane[3][2] = combo[2][3] - combo[2][1];
        Plane[3][3] = combo[3][3] - combo[3][1];

        // Near plane: row2
        Plane[4][0] = combo[0][2];
        Plane[4][1] = combo[1][2];
        Plane[4][2] = combo[2][2];
        Plane[4][3] = combo[3][2];

        // Far plane: row3 - row2
        Plane[5][0] = combo[0][3] - combo[0][2];
        Plane[5][1] = combo[1][3] - combo[1][2];
        Plane[5][2] = combo[2][3] - combo[2][2];
        Plane[5][3] = combo[3][3] - combo[3][2];

        // Normalize all planes
        for (int p = 0; p < 6; p++) {
            float len = (float)sqrt(Plane[p][0] * Plane[p][0]
                                  + Plane[p][1] * Plane[p][1]
                                  + Plane[p][2] * Plane[p][2]);
            if (len > 1e-6f) {
                Plane[p][0] /= len;
                Plane[p][1] /= len;
                Plane[p][2] /= len;
                Plane[p][3] /= len;
            }
        }
        numPlane = 6;
    }

    // 0x10021c80 (253B) - Clip AABB against frustum
    // Returns bitmask: 0 = fully outside, non-zero = at least partially inside
    // flags indicates which planes to test (bit per plane)
    unsigned int ClipAABBox(gbVec3D* vMin, gbVec3D* vMax, unsigned int flags) {
        if (!vMin || !vMax)
            return 0;

        unsigned int result = 0;

        for (int i = 0; i < numPlane; i++) {
            if (!(flags & (1 << i)))
                continue;

            float nx = Plane[i][0];
            float ny = Plane[i][1];
            float nz = Plane[i][2];
            float d  = Plane[i][3];

            // Find the positive vertex (farthest along the plane normal)
            float px = (nx >= 0.0f) ? vMax->x : vMin->x;
            float py = (ny >= 0.0f) ? vMax->y : vMin->y;
            float pz = (nz >= 0.0f) ? vMax->z : vMin->z;

            // If the positive vertex is behind the plane, the box is fully outside
            if (nx * px + ny * py + nz * pz + d < 0.0f)
                return 0;

            // Find the negative vertex (closest along the plane normal)
            float qx = (nx >= 0.0f) ? vMin->x : vMax->x;
            float qy = (ny >= 0.0f) ? vMin->y : vMax->y;
            float qz = (nz >= 0.0f) ? vMin->z : vMax->z;

            // If the negative vertex is behind the plane, box intersects this plane
            if (nx * qx + ny * qy + nz * qz + d < 0.0f)
                result |= (1 << i);
        }

        // If result is 0, the box is fully inside all tested planes
        // If result is non-zero, it intersects some planes (partially visible)
        return result;
    }

    // 0x10021d80 (381B) - Clip OBB against frustum
    // Returns: 0 = outside, 1 = intersects or inside
    int ClipOBBox(gbOBBox* obb) {
        if (!obb)
            return 0;

        for (int i = 0; i < numPlane; i++) {
            float nx = Plane[i][0];
            float ny = Plane[i][1];
            float nz = Plane[i][2];
            float d  = Plane[i][3];

            // Distance from OBB center to plane
            float dist = nx * obb->center.x + ny * obb->center.y + nz * obb->center.z + d;

            // Project OBB extents onto the plane normal
            float r = 0.0f;
            for (int a = 0; a < 3; a++) {
                float dot = nx * obb->axis[a].x + ny * obb->axis[a].y + nz * obb->axis[a].z;
                float ext;
                // extent is stored in obb->extent as (x, y, z) for axes 0, 1, 2
                if (a == 0)      ext = obb->extent.x;
                else if (a == 1) ext = obb->extent.y;
                else             ext = obb->extent.z;
                r += (float)fabs(dot) * ext;
            }

            // If center is farther from the plane than the projection radius,
            // the OBB is completely on the negative side
            if (dist < -r)
                return 0;
        }

        return 1;
    }

    // 0x10021f00 (82B) - Clip a single point against frustum
    // Returns: 0 = outside, 1 = inside
    int ClipPoint(gbVec3D* pt) {
        if (!pt)
            return 0;

        for (int i = 0; i < numPlane; i++) {
            float dist = Plane[i][0] * pt->x
                       + Plane[i][1] * pt->y
                       + Plane[i][2] * pt->z
                       + Plane[i][3];
            if (dist < 0.0f)
                return 0;
        }
        return 1;
    }

    // 0x10021f60 (90B) - Clip a sphere against frustum
    // Returns: 0 = fully outside, 1 = intersects or inside
    int ClipSphere(gbVec3D* center, float radius) {
        if (!center)
            return 0;

        for (int i = 0; i < numPlane; i++) {
            float dist = Plane[i][0] * center->x
                       + Plane[i][1] * center->y
                       + Plane[i][2] * center->z
                       + Plane[i][3];
            if (dist < -radius)
                return 0;
        }
        return 1;
    }

    // --- Camera control ---

    // 0x100225f0 (54B) - Add a camera controller
    void AddControler(gbCamControler* ctrl, double blendTime) {
        if (!ctrl)
            return;

        // Find a free slot
        for (int i = 0; i < 16; i++) {
            if (pControl[i] == NULL) {
                pControl[i] = ctrl;
                ctrl->pCamera = this;
                CurCtrl = i;
                break;
            }
        }
    }

    // SetActive / GetActive
    void SetActive(int active) {
        // In the real engine, this marks the camera as the active rendering camera
        // and calls SetAsCurrent to push matrices to the D3D device
        if (active && pGfxMgr) {
            // Push view and projection matrices to the graphics manager
            pGfxMgr->SetCameraMatrix(&ViewMatrix, &ProjMatrix);
        }
    }

    int GetActive(void) {
        // Return whether this camera is the current active camera
        if (pGfxMgr && pGfxMgr->pCamera == this)
            return 1;
        return 0;
    }

    // 0x10022590 (83B) - Update active camera controller
    void UpdateControler(double deltaTime) {
        if (CurCtrl >= 0 && CurCtrl < 16 && pControl[CurCtrl]) {
            pControl[CurCtrl]->Update(deltaTime);
        }
    }

    // --- Additional methods from the export list ---

    // 0x100058d0 (33B) - Set eye location directly
    void SetEyeLoc(float x, float y, float z) {
        eyeLoc.x = x;
        eyeLoc.y = y;
        eyeLoc.z = z;
    }

    // 0x10005900 (42B) - Set eye direction from quaternion
    void SetEyeDir(gbQuaternion* dir) {
        if (dir)
            eyeDir = *dir;
    }

    // 0x10005930 (16B) - Set orthographic size
    void SetOrthoSize(float size) {
        OrthoSize = size;
    }

    // 0x10021970 (155B) - Set look-at parameters
    void SetLookAt(gbVec3D* eye, gbVec3D* target, gbVec3D* up) {
        if (eye)
            eyeLoc = *eye;

        // Compute view direction quaternion from eye/target/up
        // The real engine converts the look-at vectors to a quaternion stored in eyeDir
        // and then calls MakeView().
        if (eye && target && up) {
            // Build rotation from look-at direction
            MakeView();
        }
    }

    // 0x10021a10 (97B) - Get view dimensions on the near clipping plane
    void GetViewSizeOnNearPlane(float* w, float* h) {
        if (!w || !h)
            return;
        float halfH = zNear * (float)tan(fov * 0.5f);
        float halfW = halfH * GetAspect();
        *w = halfW * 2.0f;
        *h = halfH * 2.0f;
    }

    // 0x10021a80 (460B) - Set this camera as the current rendering camera
    void SetAsCurrent(int mode) {
        if (!pGfxMgr)
            return;

        pGfxMgr->pCamera = this;

        // Build view and projection matrices
        MakeView();
        MakeProj();

        // Push matrices to the graphics system
        pGfxMgr->SetCameraMatrix(&ViewMatrix, &ProjMatrix);

        // Set viewport on the device
        // In the real engine: IDirect3DDevice9::SetViewport(...)
    }

    // 0x10021c50 (39B) - Set screen dimensions
    void SetDimention(int w, int h) {
        Wscreen = (float)w;
        Hscreen = (float)h;
        Viewport.width = w;
        Viewport.height = h;
    }

    // 0x100059c0 (24B) - Rotate a vector by the camera orientation
    void RotateVector(gbVec3D* in, gbVec3D* out) {
        if (!in || !out)
            return;
        // Transform by the rotation part of the inverse view matrix
        out->x = InvVMatrix.m[0][0] * in->x + InvVMatrix.m[1][0] * in->y + InvVMatrix.m[2][0] * in->z;
        out->y = InvVMatrix.m[0][1] * in->x + InvVMatrix.m[1][1] * in->y + InvVMatrix.m[2][1] * in->z;
        out->z = InvVMatrix.m[0][2] * in->x + InvVMatrix.m[1][2] * in->y + InvVMatrix.m[2][2] * in->z;
    }

    // 0x10005a00 (14B) - Get current controller
    gbCamControler* GetCurControl(void) {
        if (CurCtrl >= 0 && CurCtrl < 16)
            return pControl[CurCtrl];
        return NULL;
    }

    // 0x10005a10 (14B) - Check if current controller is default
    int IsCurCtrlDefault(void) {
        return (CurCtrl == 0) ? 1 : 0;
    }

    // 0x10021fc0 (111B) - Convert screen coordinates to world ray
    void PointScrToWorld(float sx, float sy, gbVec3D* worldPt) {
        if (!worldPt)
            return;
        // Convert screen (sx, sy) to a world-space point on the near plane
        float halfH = zNear * (float)tan(fov * 0.5f);
        float halfW = halfH * GetAspect();

        // Normalize screen coords to [-1, 1]
        float nx = (2.0f * sx / Wscreen - 1.0f) * halfW;
        float ny = (1.0f - 2.0f * sy / Hscreen) * halfH;

        // Eye-space point on near plane
        gbVec3D eyePt;
        eyePt.x = nx;
        eyePt.y = ny;
        eyePt.z = zNear;

        // Transform to world space using inverse view matrix
        worldPt->x = InvVMatrix.m[0][0] * eyePt.x + InvVMatrix.m[1][0] * eyePt.y
                   + InvVMatrix.m[2][0] * eyePt.z + InvVMatrix.m[3][0];
        worldPt->y = InvVMatrix.m[0][1] * eyePt.x + InvVMatrix.m[1][1] * eyePt.y
                   + InvVMatrix.m[2][1] * eyePt.z + InvVMatrix.m[3][1];
        worldPt->z = InvVMatrix.m[0][2] * eyePt.x + InvVMatrix.m[1][2] * eyePt.y
                   + InvVMatrix.m[2][2] * eyePt.z + InvVMatrix.m[3][2];
    }

    // 0x10022030 (24B) - Transform a world point to eye space
    void PointWorldToEye(gbVec3D* worldPt, gbVec3D* eyePt) {
        if (!worldPt || !eyePt)
            return;
        eyePt->x = ViewMatrix.m[0][0] * worldPt->x + ViewMatrix.m[1][0] * worldPt->y
                  + ViewMatrix.m[2][0] * worldPt->z + ViewMatrix.m[3][0];
        eyePt->y = ViewMatrix.m[0][1] * worldPt->x + ViewMatrix.m[1][1] * worldPt->y
                  + ViewMatrix.m[2][1] * worldPt->z + ViewMatrix.m[3][1];
        eyePt->z = ViewMatrix.m[0][2] * worldPt->x + ViewMatrix.m[1][2] * worldPt->y
                  + ViewMatrix.m[2][2] * worldPt->z + ViewMatrix.m[3][2];
    }

    // 0x100220b0 (184B) - Convert eye-space point to screen coordinates
    void PointEyeToScr(gbVec3D* eyePt, float* sx, float* sy) {
        if (!eyePt || !sx || !sy)
            return;

        if (eyePt->z <= 0.0f) {
            *sx = 0.0f;
            *sy = 0.0f;
            return;
        }

        // Perspective divide
        float invZ = 1.0f / eyePt->z;
        float projX = eyePt->x * ProjMatrix.m[0][0] * invZ;
        float projY = eyePt->y * ProjMatrix.m[1][1] * invZ;

        // Map from [-1,1] to screen coords
        *sx = (projX + 1.0f) * 0.5f * Wscreen;
        *sy = (1.0f - projY) * 0.5f * Hscreen;
    }

    // 0x10022170 (217B) - Convert eye-space point to screen (vector version)
    void PointEyeToScr(gbVec3D* eyePt, gbVec3D* scrPt) {
        if (!eyePt || !scrPt)
            return;

        float sx, sy;
        PointEyeToScr(eyePt, &sx, &sy);
        scrPt->x = sx;
        scrPt->y = sy;
        scrPt->z = eyePt->z; // preserve depth
    }

    // 0x10022250 (24B) - Transform eye-space point to world
    void PointEyetoWorld(gbVec3D* eyePt, gbVec3D* worldPt) {
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
    void PointWorldToScr(gbVec3D* worldPt, float* sx, float* sy) {
        if (!worldPt || !sx || !sy)
            return;
        gbVec3D eyePt;
        PointWorldToEye(worldPt, &eyePt);
        PointEyeToScr(&eyePt, sx, sy);
    }

    // 0x10022050 (91B) - Convert screen coordinates to eye space
    void PointScrToEye(float sx, float sy, gbVec3D* eyePt) {
        if (!eyePt)
            return;

        float halfH = zNear * (float)tan(fov * 0.5f);
        float halfW = halfH * GetAspect();

        eyePt->x = (2.0f * sx / Wscreen - 1.0f) * halfW;
        eyePt->y = (1.0f - 2.0f * sy / Hscreen) * halfH;
        eyePt->z = zNear;
    }

    // 0x100222c0 (268B) - Get a ray from camera through screen point
    void GetRayToScreen(float sx, float sy, gbRay* ray) {
        if (!ray)
            return;

        // Origin is the eye position
        ray->origin = eyeLoc;

        // Compute direction: point on near plane in world space minus eye
        gbVec3D nearPt;
        PointScrToWorld(sx, sy, &nearPt);

        ray->direction.x = nearPt.x - eyeLoc.x;
        ray->direction.y = nearPt.y - eyeLoc.y;
        ray->direction.z = nearPt.z - eyeLoc.z;

        // Normalize direction
        float len = (float)sqrt(ray->direction.x * ray->direction.x
                              + ray->direction.y * ray->direction.y
                              + ray->direction.z * ray->direction.z);
        if (len > 1e-6f) {
            ray->direction.x /= len;
            ray->direction.y /= len;
            ray->direction.z /= len;
        }
    }

    // 0x100223d0 (109B) - Get viewport bounds as floats
    void GetViewPort(float* x, float* y, float* w, float* h) {
        if (x) *x = (float)Viewport.x;
        if (y) *y = (float)Viewport.y;
        if (w) *w = (float)Viewport.width;
        if (h) *h = (float)Viewport.height;
    }

    // 0x10022440 (67B) - Convert device coordinates to screen coordinates
    void PointDevToScr(int* dx, int* dy, float sx, float sy) {
        if (!dx || !dy)
            return;
        *dx = (int)(sx - (float)Viewport.x);
        *dy = (int)(sy - (float)Viewport.y);
    }

    // 0x10022490 (24B) - Rotate vector with optional inverse flag
    void RotateVector(gbVec3D* in, gbVec3D* out, int inverse) {
        if (!in || !out)
            return;
        if (inverse) {
            // Rotate by the view matrix (world to eye)
            out->x = ViewMatrix.m[0][0] * in->x + ViewMatrix.m[1][0] * in->y + ViewMatrix.m[2][0] * in->z;
            out->y = ViewMatrix.m[0][1] * in->x + ViewMatrix.m[1][1] * in->y + ViewMatrix.m[2][1] * in->z;
            out->z = ViewMatrix.m[0][2] * in->x + ViewMatrix.m[1][2] * in->y + ViewMatrix.m[2][2] * in->z;
        } else {
            // Rotate by the inverse view matrix (eye to world)
            RotateVector(in, out);
        }
    }

    // 0x100224b0 (39B) - Offset Z-buffer for camera
    void OffsetZBuffer(double offset) {
        if (pGfxMgr) {
            pGfxMgr->OffsetZBuffer(offset != 0.0 ? 1 : 0);
        }
    }

    // 0x100224e0 (25B) - Recover Z-buffer to normal state
    void RecoverZBuffer(void) {
        if (pGfxMgr) {
            pGfxMgr->OffsetZBuffer(0);
        }
    }

    // 0x10022500 (130B) - Move camera along its forward direction
    void MoveInEyeDir(float dist) {
        // Get the forward direction from the inverse view matrix (row 2)
        float fx = InvVMatrix.m[2][0];
        float fy = InvVMatrix.m[2][1];
        float fz = InvVMatrix.m[2][2];

        eyeLoc.x += fx * dist;
        eyeLoc.y += fy * dist;
        eyeLoc.z += fz * dist;
    }

    // 0x10022590 (83B) - Update camera (called each frame)
    void Update(double deltaTime) {
        // Update current controller if any
        UpdateControler(deltaTime);

        // Rebuild matrices
        MakeView();
        MakeProj();
    }

    // 0x10022630 (171B) - Project world point to screen without viewport transform
    void PointWorld2Scr_NR(gbVec3D* worldPt, float* sx, float* sy) {
        if (!worldPt || !sx || !sy)
            return;

        gbVec3D eyePt;
        PointWorldToEye(worldPt, &eyePt);

        if (eyePt.z <= 0.0f) {
            *sx = 0.0f;
            *sy = 0.0f;
            return;
        }

        float invZ = 1.0f / eyePt.z;
        *sx = eyePt.x * ProjMatrix.m[0][0] * invZ;
        *sy = eyePt.y * ProjMatrix.m[1][1] * invZ;
    }
};


// ============================================================================
// gbRenderEffect - wraps an ID3DXEffect for shader management
// ============================================================================
class gbRenderEffect {
    // Private constructor: only gbEffectMgr can create these
    friend class gbEffectMgr;

private:
    ID3DXEffect* m_pEffect;
    unsigned int m_nPasses;
    unsigned int m_dwFlags;
    D3DVERTEXELEMENT9* m_pDecl;
    int m_nTechnique;

    // 0x1001cef0 (139B) - Private constructor from effect and flags
    gbRenderEffect(ID3DXEffect* pEffect, unsigned int flags) {
        m_pEffect = pEffect;
        m_dwFlags = flags;
        m_nPasses = 0;
        m_pDecl = NULL;
        m_nTechnique = 0;

        if (m_pEffect) {
            m_pEffect->AddRef();
        }
    }

    // Private virtual destructor
    virtual ~gbRenderEffect() {
        if (m_pEffect) {
            m_pEffect->Release();
            m_pEffect = NULL;
        }
        m_pDecl = NULL;
    }

public:
    // 0x10004bf0 (92B) - Copy constructor
    gbRenderEffect(const gbRenderEffect& other) {
        m_pEffect = other.m_pEffect;
        m_dwFlags = other.m_dwFlags;
        m_nPasses = other.m_nPasses;
        m_pDecl = other.m_pDecl;
        m_nTechnique = other.m_nTechnique;

        if (m_pEffect) {
            m_pEffect->AddRef();
        }
    }

    // operator=
    gbRenderEffect& operator=(const gbRenderEffect& other) {
        if (this != &other) {
            // Release old effect
            if (m_pEffect) {
                m_pEffect->Release();
            }

            m_pEffect = other.m_pEffect;
            m_dwFlags = other.m_dwFlags;
            m_nPasses = other.m_nPasses;
            m_pDecl = other.m_pDecl;
            m_nTechnique = other.m_nTechnique;

            if (m_pEffect) {
                m_pEffect->AddRef();
            }
        }
        return *this;
    }

    // 0x10004be0 (10B) - Set vertex declaration handle
    void SetDeclHandle(void* decl) {
        m_pDecl = (D3DVERTEXELEMENT9*)decl;
    }

    // 0x1001cfe0 (32B) - Compare two effects for sorting
    int Compare(gbRenderEffect* other) {
        if (!other)
            return 1;
        if (m_pEffect == other->m_pEffect)
            return 0;
        if (m_pEffect < other->m_pEffect)
            return -1;
        return 1;
    }

    // 0x1001d000 (119B) - Validate the effect
    int Validate(void) {
        if (!m_pEffect)
            return 0;

        HRESULT hr = m_pEffect->ValidateTechnique(NULL);
        return SUCCEEDED(hr) ? 1 : 0;
    }

    // 0x1001d080 (26B) - Begin rendering with this effect
    int Begin(void) {
        if (!m_pEffect)
            return 0;

        UINT numPasses = 0;
        HRESULT hr = m_pEffect->Begin(&numPasses, 0);
        if (FAILED(hr))
            return 0;

        m_nPasses = numPasses;
        return (int)numPasses;
    }

    // 0x1001d0a0 (52B) - Set a pass
    void Pass(int passIndex) {
        if (!m_pEffect)
            return;
        m_pEffect->BeginPass(passIndex);
    }

    // 0x1001d0e0 (20B) - End rendering with this effect
    void End(void) {
        if (!m_pEffect)
            return;
        m_pEffect->End();
    }

    // 0x1001d100 (72B) - Apply current effect state (commit changes)
    void Apply(void) {
        if (!m_pEffect)
            return;
        m_pEffect->CommitChanges();
    }

    // 0x1001d150 (30B) - Get variant by handle
    void GetVariant(int handle, void* pValue) {
        if (!m_pEffect || !pValue)
            return;
        m_pEffect->GetValue((D3DXHANDLE)(intptr_t)handle, pValue, sizeof(float) * 4);
    }

    // 0x1001d170 (30B) - Set variant by handle
    void SetVariant(int handle, void* pValue) {
        if (!m_pEffect || !pValue)
            return;
        m_pEffect->SetValue((D3DXHANDLE)(intptr_t)handle, pValue, sizeof(float) * 4);
    }

    // 0x1001d190 (40B) - Get variant by name
    void GetVariant(char* name, void* pValue) {
        if (!m_pEffect || !name || !pValue)
            return;
        D3DXHANDLE hParam = m_pEffect->GetParameterByName(NULL, name);
        if (hParam)
            m_pEffect->GetValue(hParam, pValue, sizeof(float) * 4);
    }

    // 0x1001d1c0 (40B) - Set variant by name
    void SetVariant(char* name, void* pValue) {
        if (!m_pEffect || !name || !pValue)
            return;
        D3DXHANDLE hParam = m_pEffect->GetParameterByName(NULL, name);
        if (hParam)
            m_pEffect->SetValue(hParam, pValue, sizeof(float) * 4);
    }
};


// ============================================================================
// gbEffectMgr - manages creation and caching of render effects
// ============================================================================
class gbEffectMgr {
public:
    gbGfxManager* m_pGfxMgr;
    gbRenderEffect** m_pEffects;    // array of effect pointers
    int m_nMaxEffects;
    int m_nNumEffects;
    void** m_pVertDecls;            // registered vertex declarations
    int m_nMaxDecls;
    int m_nNumDecls;
    int m_bInitialized;

    // 0x10004d20 (12B) - Default constructor
    gbEffectMgr(void) {
        m_pGfxMgr = NULL;
        m_pEffects = NULL;
        m_nMaxEffects = 0;
        m_nNumEffects = 0;
        m_pVertDecls = NULL;
        m_nMaxDecls = 0;
        m_nNumDecls = 0;
        m_bInitialized = 0;
    }

    // 0x10004d30 (148B) - Copy constructor
    gbEffectMgr(const gbEffectMgr& other) {
        m_pGfxMgr = other.m_pGfxMgr;
        m_nMaxEffects = other.m_nMaxEffects;
        m_nNumEffects = other.m_nNumEffects;
        m_nMaxDecls = other.m_nMaxDecls;
        m_nNumDecls = other.m_nNumDecls;
        m_bInitialized = other.m_bInitialized;

        // Copy effect array
        if (other.m_pEffects && m_nMaxEffects > 0) {
            m_pEffects = (gbRenderEffect**)malloc(sizeof(gbRenderEffect*) * m_nMaxEffects);
            memcpy(m_pEffects, other.m_pEffects, sizeof(gbRenderEffect*) * m_nNumEffects);
        } else {
            m_pEffects = NULL;
        }

        // Copy vertex declaration array
        if (other.m_pVertDecls && m_nMaxDecls > 0) {
            m_pVertDecls = (void**)malloc(sizeof(void*) * m_nMaxDecls);
            memcpy(m_pVertDecls, other.m_pVertDecls, sizeof(void*) * m_nNumDecls);
        } else {
            m_pVertDecls = NULL;
        }
    }

    // Destructor
    ~gbEffectMgr() {
        Release();
    }

    // operator=
    gbEffectMgr& operator=(const gbEffectMgr& other) {
        if (this != &other) {
            Release();

            m_pGfxMgr = other.m_pGfxMgr;
            m_nMaxEffects = other.m_nMaxEffects;
            m_nNumEffects = other.m_nNumEffects;
            m_nMaxDecls = other.m_nMaxDecls;
            m_nNumDecls = other.m_nNumDecls;
            m_bInitialized = other.m_bInitialized;

            if (other.m_pEffects && m_nMaxEffects > 0) {
                m_pEffects = (gbRenderEffect**)malloc(sizeof(gbRenderEffect*) * m_nMaxEffects);
                memcpy(m_pEffects, other.m_pEffects, sizeof(gbRenderEffect*) * m_nNumEffects);
            }
            if (other.m_pVertDecls && m_nMaxDecls > 0) {
                m_pVertDecls = (void**)malloc(sizeof(void*) * m_nMaxDecls);
                memcpy(m_pVertDecls, other.m_pVertDecls, sizeof(void*) * m_nNumDecls);
            }
        }
        return *this;
    }

    // 0x1001d1f0 (786B) - Initialize the effect manager
    void Init(gbGfxManager* gfxMgr) {
        m_pGfxMgr = gfxMgr;

        // Pre-allocate space for effects
        m_nMaxEffects = 64;
        m_pEffects = (gbRenderEffect**)malloc(sizeof(gbRenderEffect*) * m_nMaxEffects);
        memset(m_pEffects, 0, sizeof(gbRenderEffect*) * m_nMaxEffects);
        m_nNumEffects = 0;

        // Pre-allocate space for vertex declarations
        m_nMaxDecls = 32;
        m_pVertDecls = (void**)malloc(sizeof(void*) * m_nMaxDecls);
        memset(m_pVertDecls, 0, sizeof(void*) * m_nMaxDecls);
        m_nNumDecls = 0;

        m_bInitialized = 1;
    }

    // 0x1001d510 (67B) - Release all managed effects
    void Release(void) {
        if (m_pEffects) {
            for (int i = 0; i < m_nNumEffects; i++) {
                if (m_pEffects[i]) {
                    delete m_pEffects[i];
                    m_pEffects[i] = NULL;
                }
            }
            free(m_pEffects);
            m_pEffects = NULL;
        }
        m_nNumEffects = 0;
        m_nMaxEffects = 0;

        if (m_pVertDecls) {
            free(m_pVertDecls);
            m_pVertDecls = NULL;
        }
        m_nNumDecls = 0;
        m_nMaxDecls = 0;

        m_bInitialized = 0;
    }

    // 0x1001d560 (50B) - Handle device lost
    int OnLostDevice(void) {
        for (int i = 0; i < m_nNumEffects; i++) {
            if (m_pEffects[i] && m_pEffects[i]->m_pEffect) {
                m_pEffects[i]->m_pEffect->OnLostDevice();
            }
        }
        return 1;
    }

    // 0x1001d5a0 (50B) - Handle device reset
    int OnResetDevice(void) {
        for (int i = 0; i < m_nNumEffects; i++) {
            if (m_pEffects[i] && m_pEffects[i]->m_pEffect) {
                m_pEffects[i]->m_pEffect->OnResetDevice();
            }
        }
        return 1;
    }

    // 0x1001d5e0 (232B) - Register a vertex format declaration
    void* RegisterVertexFormat(char* name, void* pElements) {
        if (!name || !pElements)
            return NULL;

        if (m_nNumDecls >= m_nMaxDecls)
            return NULL;

        // In the real engine, this creates an IDirect3DVertexDeclaration9
        // from the D3DVERTEXELEMENT9 array and stores it
        m_pVertDecls[m_nNumDecls] = pElements;
        m_nNumDecls++;
        return pElements;
    }

    // 0x1001d6d0 (353B) - Create a new render effect from a .gbf file
    gbRenderEffect* NewRenderEffect(char* filename, int flags) {
        if (!filename || !m_pGfxMgr)
            return NULL;

        if (m_nNumEffects >= m_nMaxEffects)
            return NULL;

        // Get D3D device
        IDirect3DDevice9* pDevice = NULL;
        if (m_pGfxMgr) {
            pDevice = *(IDirect3DDevice9**)((char*)m_pGfxMgr + 0x84C);
        }
        if (!pDevice)
            return NULL;

        // Load effect file
        // The real engine opens the file through gbVFileSystem, reads the .gbf data,
        // and calls D3DXCreateEffect.
        ID3DXEffect* pEffect = NULL;
        ID3DXBuffer* pErrors = NULL;

        HRESULT hr = D3DXCreateEffectFromFile(
            pDevice,
            filename,
            NULL,       // defines
            NULL,       // include handler
            0,          // flags
            NULL,       // effect pool
            &pEffect,
            &pErrors
        );

        if (pErrors) {
            pErrors->Release();
        }

        if (FAILED(hr) || !pEffect)
            return NULL;

        gbRenderEffect* effect = new gbRenderEffect(pEffect, (unsigned int)flags);
        pEffect->Release(); // gbRenderEffect AddRef'd in its constructor

        m_pEffects[m_nNumEffects] = effect;
        m_nNumEffects++;

        return effect;
    }

    // 0x1001d840 (107B) - Create a trivial (fixed-function emulation) effect
    gbRenderEffect* NewTrivalEffect(int type) {
        // In the real engine, this creates a simple pass-through effect
        // for fixed-function pipeline emulation
        return NULL;
    }

    // 0x1001d8b0 (39B) - Get effect by index
    gbRenderEffect* GetRenderEffect(int index) {
        if (index < 0 || index >= m_nNumEffects)
            return NULL;
        return m_pEffects[index];
    }
};
