#pragma once
// Auto-generated: SceneInfo

#include "SCENE_TYPE.h"

class SceneInfo {
public:
    char cityname[32]; // +0x0
    char name[32]; // +0x20
    char mdl[32]; // +0x40
    SCENE_TYPE type; // +0x60
    unsigned long lightmap; // +0x64
    unsigned long skybox; // +0x68
    unsigned long reserve[6]; // +0x6C
    // total size: 0x84 (132)

};
