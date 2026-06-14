#pragma once
// Auto-generated: ArcSceneObject

#include "ObjectInfo.h"
#include "SaveTask.h"

class ArcSceneObject {
public:
    ObjectInfo info; // +0x0
    char _gap_004[600]; // +0x4
    SaveTask task; // +0x25C
    char _gap_260[8]; // +0x260
    int subobj; // +0x268
    char _tail_26C[32]; // +0x26C
    // total size: 0x28C (652)

    static CHAR * FormatDescription(int nVal); // 0x00458A20
    void ResetEquipControls(); // 0x0049AAF0
    ArcSceneObject * InitFromConfig(); // 0x005254C0
    void UpdateOscillation(float fDelta); // 0x00533F50
};
