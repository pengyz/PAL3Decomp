#pragma once
// Auto-generated: SceneInfo

#include "SCENE_TYPE.h"

class SceneInfo {
public:
    char cityname[32]; // +0x0
    char name[32]; // +0x20
    char mdl[32]; // +0x40
    SCENE_TYPE type; // +0x60
    UINT lightmap; // +0x64
    UINT skybox; // +0x68
    UINT reserve[6]; // +0x6C
    // total size: 0x84 (132)

    char ProcessCollision(int nVal, int nVal2); // 0x00443CE0
    char ProcessSceneChange(float fVal, int nVal, int nVal2); // 0x00443FC0
    bool CheckHitLeft(float fVal); // 0x004441E0
    bool UpdateScaling(float fVal); // 0x004442B0
    bool CheckHitRight(float fVal); // 0x00444380
    bool CheckHitBottom(float fVal); // 0x00444450
    char CheckBoundsHorizontal(float fVal); // 0x00444520
    char CheckBoundsLeftCombo(float fVal); // 0x00444660
    char CheckBoundsRightCombo(float fVal); // 0x004447A0
    char CheckBoundsBottomCombo(float fVal); // 0x004448E0
};
