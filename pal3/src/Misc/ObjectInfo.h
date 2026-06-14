#include "ObjectInfoBase.h"
#pragma once
// Auto-generated: ObjectInfo

#include "PolyLine.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_types.h"

class ObjectInfo : public ObjectInfoBase {
public:
    char _gap_000[4]; // +0x0
    char name[32]; // +0x4
    BYTE ctype; // +0x24
    BYTE cango; // +0x25
    char _gap_026[2]; // +0x26
    gbVec3D pos; // +0x28
    char _gap_02C[8]; // +0x2C
    float rotate; // +0x34
    tagRECT rect; // +0x38
    char _gap_03C[12]; // +0x3C
    BYTE type; // +0x48
    BYTE savestate; // +0x49
    BYTE onlayer; // +0x4A
    BYTE wuling; // +0x4B
    float param[6]; // +0x4C
    BYTE needspecalact; // +0x64
    char _gap_065[1]; // +0x65
    WORD needitem; // +0x66
    WORD needgold; // +0x68
    WORD needlv; // +0x6A
    WORD needwu; // +0x6C
    BYTE needallopen; // +0x6E
    char failed[16]; // +0x6F
    char _gap_07F[1]; // +0x7F
    UINT dwNeedItem; // +0x80
    BYTE groupid; // +0x84
    char _gap_085[3]; // +0x85
    UINT scriptid; // +0x88
    PolyLine path; // +0x8C
    char _gap_090[192]; // +0x90
    WORD linkobj; // +0x150
    char depend_scenename[32]; // +0x152
    BYTE depend_id; // +0x172
    char _gap_173[1]; // +0x173
    gbAABBox box; // +0x174
    char _gap_178[20]; // +0x178
    float rotateX; // +0x18C
    float rotateZ; // +0x190
    _BYTE snd[8]; // +0x194
    UINT effect; // +0x19C
    UINT bScriptChangeActive; // +0x1A0
    UINT bScriptMoved; // +0x1A4
    BYTE bCalculateExp; // +0x1A8
    char _gap_1A9[3]; // +0x1A9
    UINT reserve[44]; // +0x1AC
    // total size: 0x25C (604)

};
