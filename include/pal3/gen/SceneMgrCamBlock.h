#pragma once
// Auto-generated: SceneMgrCamBlock

#include "CameraCmd.h"
#include "CameraParam.h"

class SceneMgrCamBlock {
public:
    char m_CameraList[160]; // +0x0
    CameraParam m_Params[25]; // +0xA0
    CameraCmd m_Cmds[33]; // +0x230
    int m_nCurrentScene; // +0x338
    char _gap_033C[16]; // +0x33C
    int m_pCameraScript; // +0x34C
    char m_bCameraFlags[2]; // +0x350
    char m_nActiveCamera[4]; // +0x352
    char _end[2]; // +0x356
    // total size: 0x358 (856)

};
