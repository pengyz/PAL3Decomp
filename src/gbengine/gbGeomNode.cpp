/**
 * gbengine.dll - gbGeomNode
 * Geometry node implementation
 */

#include "gbengine/gbengine_types.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Forward declarations
class gbVisNode;
class gbBaseMesh;
class gbStaticMesh;
class gbRenderEffect;
class gbTexture;
class gbVFile;

struct gbRenderInfoObj {
    gbVisNode* node;
    void* renderData;
    int flags;
    float distance;
};

// gbVisNode forward declaration (base class)
class gbVisNode {
public:
    void* vtable;
    // ... other members defined in gbVisNode.cpp
    gbVisNode();
    virtual ~gbVisNode();
};

/* ======== gbGeomNode ======== */

class gbGeomNode : public gbVisNode {
public:
    // Memory layout based on decompilation
    gbMatrix4 localTransform;              // +0x58 (64 bytes)
    gbMatrix4 worldTransform;              // +0x98 (64 bytes)
    gbBaseMesh* mesh;                      // +0xd8
    void* animController;                  // +0xdc
    void* materialData;                    // +0xe0
    float animTime;                        // +0xe4
    void* bladeEffect;                     // +0xe8
    void* shadowData;                      // +0xec
    int shadowEnabled;                     // +0xf0
    int bladeEnabled;                      // +0xf4
    void* textureOverride;                 // +0xf8
    int animLoop;                          // +0xfc
    int loopPast;                          // +0x100
    void* boundingBox;                     // +0x104
    float bladeTime;                       // +0x108
    float bladeTimeScale;                  // +0x10c
    gbVec3D* lastBladePos;                 // +0x110

    // Constructor
    gbGeomNode(void) {
        // Call base class constructor (gbVisNode at 0x10016590)
        // Base class is 0x58 bytes

        // Initialize matrices (constructors at 0x10025110)
        memset(&localTransform, 0, sizeof(gbMatrix4));
        memset(&worldTransform, 0, sizeof(gbMatrix4));

        // Set vtable pointer (0x100f5588)
        // vtable = (void*)0x100f5588;

        // Load identity matrices (LoadIdentity at 0x10025640)
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                localTransform.m[i][j] = (i == j) ? 1.0f : 0.0f;
                worldTransform.m[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }

        // Initialize remaining fields (from decompilation)
        mesh = NULL;                    // +0xd8
        animController = NULL;          // +0xdc
        materialData = NULL;            // +0xe0
        animTime = 1.0f;                // +0xe4 = 0x3f800000
        bladeEffect = NULL;             // +0xe8
        shadowData = NULL;              // +0xec
        shadowEnabled = 0;              // +0xf0
        bladeEnabled = 0;               // +0xf4
        textureOverride = NULL;         // +0xf8
        animLoop = 0;                   // +0xfc
        loopPast = 0;                   // +0x100
        boundingBox = NULL;             // +0x104
        bladeTime = 0.0f;               // +0x108
        bladeTimeScale = 0.0f;          // +0x10c
        lastBladePos = NULL;            // +0x110
    }

    // Copy constructor
    gbGeomNode(const gbGeomNode& other) {
        // Copy base class members (gbVisNode portion)
        // This is a shallow copy of the inheritance hierarchy

        // Copy matrices
        memcpy(&localTransform, &other.localTransform, sizeof(gbMatrix4));
        memcpy(&worldTransform, &other.worldTransform, sizeof(gbMatrix4));

        // Copy all other fields
        mesh = other.mesh;
        animController = other.animController;
        materialData = other.materialData;
        animTime = other.animTime;
        bladeEffect = other.bladeEffect;
        shadowData = other.shadowData;
        shadowEnabled = other.shadowEnabled;
        bladeEnabled = other.bladeEnabled;
        textureOverride = other.textureOverride;
        animLoop = other.animLoop;
        loopPast = other.loopPast;
        boundingBox = other.boundingBox;
        bladeTime = other.bladeTime;
        bladeTimeScale = other.bladeTimeScale;
        lastBladePos = other.lastBladePos;

        // Set vtable
        // vtable = (void*)0x100f5588;
    }

    // Assignment operator
    gbGeomNode& operator=(const gbGeomNode& other) {
        if (this != &other) {
            // Same as copy constructor but for existing object
            memcpy(&localTransform, &other.localTransform, sizeof(gbMatrix4));
            memcpy(&worldTransform, &other.worldTransform, sizeof(gbMatrix4));

            mesh = other.mesh;
            animController = other.animController;
            materialData = other.materialData;
            animTime = other.animTime;
            bladeEffect = other.bladeEffect;
            shadowData = other.shadowData;
            shadowEnabled = other.shadowEnabled;
            bladeEnabled = other.bladeEnabled;
            textureOverride = other.textureOverride;
            animLoop = other.animLoop;
            loopPast = other.loopPast;
            boundingBox = other.boundingBox;
            bladeTime = other.bladeTime;
            bladeTimeScale = other.bladeTimeScale;
            lastBladePos = other.lastBladePos;
        }
        return *this;
    }

    // Destructor
    virtual ~gbGeomNode(void) {
        // Clean up mesh and other resources
        if (mesh) {
            // mesh->Release() or delete
        }
        if (bladeEffect) {
            // Release blade effect
        }
        if (shadowData) {
            // Release shadow data
        }
        if (lastBladePos) {
            delete lastBladePos;
            lastBladePos = NULL;
        }
    }

    // Load geometry from CVD file
    int LoadFromFile(const char* filename, const char* texPath, void* progressCallback) {
        if (!filename) return 0;

        // This is a complex function (1478 bytes) that:
        // 1. Opens the CVD file
        // 2. Parses the file format
        // 3. Loads mesh data
        // 4. Loads animation data
        // 5. Loads materials and textures
        // 6. Builds the geometry hierarchy
        // Implementation stub
        return 0;
    }

    int LoadCVDFile(const char* filename) {
        if (!filename) return 0;

        // Opens CVD file and calls LoadCVDFromStream
        // Implementation stub
        return 0;
    }

    void LoadCVDFromStream(gbVFile* file, float scale) {
        if (!file) return;

        // Reads CVD format from stream:
        // - Header
        // - Mesh data
        // - Animation data
        // - Material data
        // Applies scale factor to geometry
        // Implementation stub
    }

    static void LoadCVDFromStream(gbVFile* file, float scale, gbGeomNode** outNodes, int& outCount) {
        // Static version that can load multiple nodes
        // Implementation stub
        if (outNodes) *outNodes = NULL;
        outCount = 0;
    }

    virtual void Update(void) {
        // Update animation state
        if (animController) {
            // Update animation time
            // Update bone transforms
            // Update blade effects if enabled
        }

        // Update world transform from local transform and parent
        // Update bounding volumes

        // Call base class Update
        // gbVisNode::Update();
    }

    virtual void AttachSelf(gbRenderEffect* effect) {
        if (!effect || !mesh) return;

        // Attach this node's geometry to the render effect
        // This is a complex function (754 bytes) that:
        // 1. Sets up render states
        // 2. Sets material properties
        // 3. Binds textures
        // 4. Sets transform matrices
        // 5. Attaches mesh to effect
        // Implementation stub
    }

    virtual int Attach(gbRenderEffect* effect) {
        if (!effect) return 0;

        // Attach this node and all children to the render effect
        AttachSelf(effect);

        // Recursively attach children
        // return childCount;
        return 1;
    }

    virtual void Render(gbRenderInfoObj* renderInfo) {
        if (!renderInfo || !mesh) return;

        // Render the geometry
        // 1. Set world transform
        // 2. Set material and textures
        // 3. Render mesh
        // Implementation stub
    }

    virtual void RenderShadowVolume(gbRenderInfoObj* renderInfo) {
        if (!renderInfo || !shadowEnabled || !shadowData) return;

        // Render shadow volume for this geometry
        // Implementation stub
    }

    virtual void Reset(float time) {
        // Reset animation to specified time
        animTime = time;
        loopPast = 0;

        if (animController) {
            // Reset animation controller to time
        }

        // Call base class Reset
        // gbVisNode::Reset(time);
    }

    virtual void GetBoundSphere(gbSphere* sphere) {
        if (!sphere) return;

        if (mesh) {
            // Get mesh bounding sphere
            // Transform to world space
            sphere->center.x = worldTransform.m[3][0];
            sphere->center.y = worldTransform.m[3][1];
            sphere->center.z = worldTransform.m[3][2];
            sphere->radius = 1.0f; // Stub: would calculate from mesh bounds
        } else {
            sphere->center.x = sphere->center.y = sphere->center.z = 0.0f;
            sphere->radius = 0.0f;
        }
    }

    void SetAnimLoop(int loop) {
        animLoop = loop;
    }

    virtual void EnableShadow(int enable) {
        shadowEnabled = enable;
    }

    virtual int GetAABBox(gbAABBox* box) {
        if (!box || !mesh) return 0;

        // Get axis-aligned bounding box in world space
        // Implementation stub
        box->vMin.x = box->vMin.y = box->vMin.z = 0.0f;
        box->vMax.x = box->vMax.y = box->vMax.z = 0.0f;
        return 1;
    }

    void SetBladeTime(float time) {
        bladeTime = time;
    }

    void SetBladeTimeScale(float scale) {
        bladeTimeScale = scale;
    }

    gbVec3D* GetLastBladePos(gbGeomNode* node) {
        if (bladeEffect && lastBladePos) {
            return lastBladePos;
        }
        return NULL;
    }

    void ReplaceTexture(const char* textureName) {
        if (!textureName || !mesh) return;

        // Load texture and replace in mesh materials
        // Implementation stub
    }

    void ReplaceTexture(gbTexture* texture) {
        if (!texture || !mesh) return;

        textureOverride = texture;
        // Replace texture in mesh materials
        // Implementation stub
    }

    gbOBBox* GetOBBox(gbOBBox* box) {
        if (!box || !mesh) return NULL;

        // Get oriented bounding box from mesh
        // Transform to world space
        // Implementation stub
        return box;
    }

    gbOBBox* GetTotalOBBox(gbOBBox* box) {
        if (!box) return NULL;

        // Get total bounding box including all children
        // This is a complex function (929 bytes) that:
        // 1. Gets own OBBox
        // 2. Recursively gets children's OBBoxes
        // 3. Merges all boxes into one
        // Implementation stub
        return box;
    }

    void EnableBlade(int enable) {
        bladeEnabled = enable;
    }

    gbMatrix4* GetCacheToWorld() {
        return &worldTransform;
    }

    int GetLoopPast() {
        return loopPast;
    }

    gbBaseMesh* GetMesh() {
        return mesh;
    }

    float GetAnimMaxTime() {
        if (animController) {
            // Return animation max time from controller
            return 1.0f; // Stub
        }
        return 0.0f;
    }
};
