#pragma once
// Auto-generated: ObjectInfo

#include "ObjectInfoBase.h"
#include "PolyLine.h"

class ObjectInfo : public ObjectInfoBase {
public:
    char name[32]; // +0x4
    BYTE ctype; // +0x24
    BYTE cango; // +0x25
    gbVec3D pos; // +0x28
    float rotate; // +0x34
    tagRECT rect; // +0x38
    BYTE type; // +0x48
    BYTE savestate; // +0x49
    BYTE onlayer; // +0x4A
    BYTE wuling; // +0x4B
    float param[6]; // +0x4C
    BYTE needspecalact; // +0x64
    WORD needitem; // +0x66
    WORD needgold; // +0x68
    WORD needlv; // +0x6A
    WORD needwu; // +0x6C
    BYTE needallopen; // +0x6E
    char failed[16]; // +0x6F
    DWORD dwNeedItem; // +0x80
    BYTE groupid; // +0x84
    DWORD scriptid; // +0x88
    PolyLine path; // +0x8C
    WORD linkobj; // +0x150
    char depend_scenename[32]; // +0x152
    BYTE depend_id; // +0x172
    gbAABBox box; // +0x174
    float rotateX; // +0x18C
    float rotateZ; // +0x190
    BYTE snd[8]; // +0x194
    DWORD effect; // +0x19C
    DWORD bScriptChangeActive; // +0x1A0
    DWORD bScriptMoved; // +0x1A4
    BYTE bCalculateExp; // +0x1A8
    DWORD reserve[44]; // +0x1AC
    // total size: 0x25C (604)

};
