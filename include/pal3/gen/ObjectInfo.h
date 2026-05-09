#pragma once
// Auto-generated: ObjectInfo

#include "ObjectInfoBase.h"
#include "PolyLine.h"
#include "gbAABBox.h"
#include "gbVec3D.h"
#include "tagRECT.h"

class ObjectInfo : public ObjectInfoBase {
public:
    char name[32]; // +0x4
    unsigned char ctype; // +0x24
    unsigned char cango; // +0x25
    gbVec3D pos; // +0x28
    float rotate; // +0x34
    tagRECT rect; // +0x38
    unsigned char type; // +0x48
    unsigned char savestate; // +0x49
    unsigned char onlayer; // +0x4A
    unsigned char wuling; // +0x4B
    float param[6]; // +0x4C
    unsigned char needspecalact; // +0x64
    unsigned short needitem; // +0x66
    unsigned short needgold; // +0x68
    unsigned short needlv; // +0x6A
    unsigned short needwu; // +0x6C
    unsigned char needallopen; // +0x6E
    char failed[16]; // +0x6F
    unsigned long dwNeedItem; // +0x80
    unsigned char groupid; // +0x84
    unsigned long scriptid; // +0x88
    PolyLine path; // +0x8C
    unsigned short linkobj; // +0x150
    char depend_scenename[32]; // +0x152
    unsigned char depend_id; // +0x172
    gbAABBox box; // +0x174
    float rotateX; // +0x18C
    float rotateZ; // +0x190
    unsigned char snd[8]; // +0x194
    unsigned long effect; // +0x19C
    unsigned long bScriptChangeActive; // +0x1A0
    unsigned long bScriptMoved; // +0x1A4
    unsigned char bCalculateExp; // +0x1A8
    unsigned long reserve[44]; // +0x1AC
    // total size: 0x25C (604)

};
