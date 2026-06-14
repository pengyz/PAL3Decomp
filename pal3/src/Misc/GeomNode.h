#pragma once
// Auto-generated: GeomNode

#include "Matrix4.h"
#include "gbengine/gbGeomNode.h"

class GeomNode {
public:
    GeomNode * pNext; // +0x0
    GeomNode * pParent; // +0x4
    char children[16]; // +0x8
    char _gap_018[68]; // +0x18
    Matrix4 worldTransform; // +0x5C
    char _gap_060[60]; // +0x60
    Matrix4 staticTransform; // +0x9C
    char _gap_0A0[96]; // +0xA0
    int _todo_100; // +0x100
    char _gap_104[12]; // +0x104
    int mesh; // +0x110
    char _tail_114[12]; // +0x114
    // total size: 0x120 (288)

    void InitFromFile(const gbGeomNode *pGeomNode, int nVal); // 0x00429AF0
    bool LoadFromNode(const gbGeomNode *pNode); // 0x004D0950
    void DestroyChildren(); // 0x004D0A80
};
