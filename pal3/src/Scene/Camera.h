#pragma once
// Auto-generated: Camera

#include "gbengine/gbCamera.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_types.h"

class Camera {
public:
    char _gap_000[4]; // +0x0
    float m_fCameraEyePosition; // +0x4
    float m_fCameraAtPosition; // +0x8
    float m_fCameraUpPosition; // +0xC
    int m_nStepRotate; // +0x10
    int m_nCameraAtPosition; // +0x14
    int m_nStepDirection; // +0x18
    float m_fStepDuration; // +0x1C
    int m_nTransitionState; // +0x20
    float m_fTransitionTime; // +0x24
    int _todo_40; // +0x28
    int _todo_44; // +0x2C
    int _todo_48; // +0x30
    float m_fStepRotate; // +0x34
    int m_nTransitionStep; // +0x38
    int m_nTransitionFlags; // +0x3C
    float m_fLookAtStart; // +0x40
    float m_fLookAtEnd; // +0x44
    float m_fLookAtProgress; // +0x48
    char * m_pLookAtData; // +0x4C
    char _gap_050[24]; // +0x50
    float m_fCameraHeight; // +0x68
    char _gap_06C[8]; // +0x6C
    int m_nTargetRole; // +0x74
    BYTE m_bCreate; // +0x78
    char _gap_079[7]; // +0x79
    float m_fFov; // +0x80
    int m_fZoomTarget; // +0x84
    float m_fAspect; // +0x88
    int m_nShakeAmplitude; // +0x8C
    int m_nShakeDuration; // +0x90
    char _gap_094[4]; // +0x94
    int m_nShakeType; // +0x98
    char _gap_09C[4]; // +0x9C
    float m_fShakeFrequency; // +0xA0
    float m_fZoomSpeed; // +0xA4
    float m_fShakeOffset; // +0xA8
    char _gap_0AC[48]; // +0xAC
    int m_nPosition; // +0xDC
    char _gap_0E0[8]; // +0xE0
    float m_fFovTan; // +0xE8
    char _gap_0EC[8]; // +0xEC
    int m_nCollisionFlags; // +0xF4
    char _gap_0F8[24]; // +0xF8
    int m_nFollowMode; // +0x110
    char _gap_114[16]; // +0x114
    gbCamera * m_pCamera; // +0x124
    gbVec3D m_vRayDir; // +0x128
    char _gap_12C[32]; // +0x12C
    void * m_pCollisionMesh; // +0x14C
    char _gap_150[12]; // +0x150
    void * m_pRayHitPoint; // +0x15C
    char _gap_160[28]; // +0x160
    int m_nCameraTick; // +0x17C
    int m_nPrevCameraTick; // +0x180
    float m_fCameraTimer; // +0x184
    float m_fLerpSpeed; // +0x188
    float m_fLerpProgress; // +0x18C
    BYTE m_bLerpActive; // +0x190
    char _gap_191[3]; // +0x191
    int m_ScriptResult; // +0x194
    char _tail_198[12548]; // +0x198
    // total size: 0x329C (12956)

    void InitFromScene(const char *pszSceneName); // 0x004125D0
    Camera(struct gbGfxManager *p); // 0x0041BE80
    static int CheckCollision1(float *pPos, void *pBounds, float *pDist); // 0x0041E7D0
    static int CheckCollision2(float *pPos, int rolePtr, void *pBounds); // 0x0041EA00
    char IsTransitioning(); // 0x0041EE60
    void UpdateCameraLookAt(int nScreenX, int nScreenY); // 0x00439850
    void UpdateCameraLookAt(int nScreenX, int nScreenY, int nOffsetY); // 0x00439930
    void InitUIElements(); // 0x0052BEB0
};
