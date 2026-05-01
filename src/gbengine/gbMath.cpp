/**
 * gbengine.dll - gbMath
 * Auto-generated from Ghidra decompilation
 * Functions: 105
 */

#include "gbengine/gbengine_types.h"
#include <math.h>
#include <string.h>

// Forward declarations
class BEZIER;
class CIniFile;
class CPK;
class CPKFile;
class gbActor;
class gbActorMgr;
class gbAnimNodeGroup;
class gbAudioManager;
class gbAudioMgrDesc;
class gbBaseMesh;
class gbBinaryTree;
class gbBinaryTreeNode;
class gbCamControler;
class gbCamQuakeControl;
class gbCamSpringControl;
class gbCamera;
class gbChain1D;
class gbChain1DNode;
class gbChain2D;
class gbChain2DNode;
class gbDropGroup;
class gbDropUnit;
class gbDynVertBuf;
class gbEffectMgr;
class gbEmitterData;
class gbEmitterSquare;
class gbGeomNode;
class gbGfxManager;
class gbGfxManager_D3D;
class gbImage2D;
class gbImage2DInfo;
class gbIndexBubble;
class gbIndexPool;
class gbLightObj;
class gbMatrixStack;
class gbNBTree;
class gbNBTreeNode;
class gbNameVarBuf;
class gbPartEmitter;
class gbPartGroupParam;
class gbPartParamControl;
class gbParticleEffect;
class gbParticleGroup;
class gbParticleUnit;
class gbPrintFont;
class gbPrintFontMgr;
class gbRain;
class gbRefObject;
class gbRenderEffect;
class gbResManager;
class gbResource;
class gbSceneGraph;
class gbSnow;
class gbSound2DNode;
class gbSound3DNode;
class gbStaticChain;
class gbStaticMesh;
class gbTexture;
class gbTextureArray;
class gbTexture_D3D;
class gbTimeCounter;
class gbVFile;
class gbVFile1;
class gbVFileSystem;
class gbVTextFile;
class gbVertPoolMgr;
class gbVertexPool;
class gbVisNode;


/* ======== gbAABBox (defined in header) ======== */


/* ======== gbMatrix4 (defined in header) ======== */


/* ======== gbMatrixStack ======== */

class gbMatrixStack {
public:
    gbMatrix4 *m_pStack;
    int m_nMaxDepth;
    int m_nCurrent;
    int m_bDirty;

    // 0x10026fe0 (149B)
    gbMatrixStack(int nMaxDepth) {
        m_nMaxDepth = nMaxDepth;
        m_nCurrent = 0;
        m_pStack = (gbMatrix4 *)operator new(nMaxDepth * sizeof(gbMatrix4));
        if (m_pStack) {
            float *p = (float *)&m_pStack[0];
            for (int i = 0; i < 16; i++)
                p[i] = 0.0f;
            p[0] = 1.0f;
            p[5] = 1.0f;
            p[10] = 1.0f;
            p[15] = 1.0f;
        }
    }

    // 0x10027080 (10B)
    ~gbMatrixStack() {
        operator delete(m_pStack);
    }

    // 0x10027090 (41B)
    void Push() {
        float *src = (float *)&m_pStack[m_nCurrent];
        float *dst = (float *)&m_pStack[m_nCurrent + 1];
        for (int i = 16; i != 0; i--) {
            *dst = *src;
            src++;
            dst++;
        }
        m_nCurrent++;
    }

    // 0x100270c0 (15B)
    void Pop() {
        m_bDirty = 0;
        m_nCurrent--;
    }

    // 0x100270d0 (51B)
    void LoadIdentity() {
        float *p = (float *)&m_pStack[m_nCurrent];
        for (int i = 16; i != 0; i--) {
            *p = 0.0f;
            p++;
        }
        float *top = (float *)&m_pStack[m_nCurrent];
        top[0] = 1.0f;
        top[5] = 1.0f;
        top[10] = 1.0f;
        top[15] = 1.0f;
    }

    // 0x10027110 (37B)
    void LoadMatrix(gbMatrix4 *pMat) {
        float *dst = (float *)&m_pStack[m_nCurrent];
        float *src = (float *)pMat;
        for (int i = 16; i != 0; i--) {
            *dst = *src;
            src++;
            dst++;
        }
    }

    // 0x10027140 (145B)
    void MultMatrix(gbMatrix4 *pMat) {
        float result[16];
        float *a = (float *)&m_pStack[m_nCurrent];
        float *b = (float *)pMat;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++) {
                    sum += a[i * 4 + k] * b[k * 4 + j];
                }
                result[i * 4 + j] = sum;
            }
        }
        float *dst = (float *)&m_pStack[m_nCurrent];
        for (int i = 0; i < 16; i++) {
            dst[i] = result[i];
        }
    }

    // 0x100271e0 (276B)
    void Rotate(float angle, gbVec3D &axis) {
        float rad = angle * 0.017453292f;
        float c = (float)cos(rad);
        float s = (float)sin(rad);
        float t = 1.0f - c;
        float x = axis.x, y = axis.y, z = axis.z;

        gbMatrix4 rot;
        float *r = (float *)&rot;
        for (int i = 0; i < 16; i++) r[i] = 0.0f;
        r[0]  = t * x * x + c;
        r[1]  = t * x * y + s * z;
        r[2]  = t * x * z - s * y;
        r[4]  = t * x * y - s * z;
        r[5]  = t * y * y + c;
        r[6]  = t * y * z + s * x;
        r[8]  = t * x * z + s * y;
        r[9]  = t * y * z - s * x;
        r[10] = t * z * z + c;
        r[15] = 1.0f;

        MultMatrix(&rot);
    }

    // 0x10027300 (221B)
    void Rotate(gbQuaternion &q) {
        float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
        float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
        float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

        gbMatrix4 rot;
        float *r = (float *)&rot;
        for (int i = 0; i < 16; i++) r[i] = 0.0f;
        r[0]  = 1.0f - 2.0f * (yy + zz);
        r[1]  = 2.0f * (xy + wz);
        r[2]  = 2.0f * (xz - wy);
        r[4]  = 2.0f * (xy - wz);
        r[5]  = 1.0f - 2.0f * (xx + zz);
        r[6]  = 2.0f * (yz + wx);
        r[8]  = 2.0f * (xz + wy);
        r[9]  = 2.0f * (yz - wx);
        r[10] = 1.0f - 2.0f * (xx + yy);
        r[15] = 1.0f;

        MultMatrix(&rot);
    }

    // 0x100273e0 (104B)
    void Translate(gbVec3D &v) {
        float *p = (float *)&m_pStack[m_nCurrent];
        p[12] = p[0] * v.x + p[4] * v.y + p[8]  * v.z + p[12];
        p[13] = p[1] * v.x + p[5] * v.y + p[9]  * v.z + p[13];
        p[14] = p[2] * v.x + p[6] * v.y + p[10] * v.z + p[14];
    }

    // 0x100274b0 (112B)
    void Translate(float x, float y, float z) {
        float *p = (float *)&m_pStack[m_nCurrent];
        p[12] = x * p[0] + z * p[8]  + y * p[4]  + p[12];
        p[13] = z * p[9]  + y * p[5]  + x * p[1]  + p[13];
        p[14] = z * p[10] + y * p[6]  + x * p[2]  + p[14];
    }

    // 0x10027450 (96B)
    void Scale(gbVec3D &v) {
        float *p = (float *)&m_pStack[m_nCurrent];
        p[0] *= v.x; p[1] *= v.x; p[2] *= v.x;
        p[4] *= v.y; p[5] *= v.y; p[6] *= v.y;
        p[8] *= v.z; p[9] *= v.z; p[10] *= v.z;
    }

    // 0x10027520 (108B)
    void Scale(float x, float y, float z) {
        float *p = (float *)&m_pStack[m_nCurrent];
        p[0] *= x; p[1] *= x; p[2] *= x;
        p[4] *= y; p[5] *= y; p[6] *= y;
        p[8] *= z; p[9] *= z; p[10] *= z;
    }

    // 0x10027590 (11B)
    gbMatrix4 *GetTop() {
        return &m_pStack[m_nCurrent];
    }
};


/* ======== gbOBBox (defined in header) ======== */


/* ======== gbPlane (defined in header) ======== */


/* ======== gbQuaternion (defined in header) ======== */


/* ======== gbRay (defined in header) ======== */


/* ======== gbRotMatrix (defined in header) ======== */


/* ======== gbSphere (defined in header) ======== */


/* ======== gbVec3D (defined in header) ======== */

