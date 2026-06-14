#pragma once
// Auto-generated: tagShowItem

#include "ECBShowItemKind.h"

class tagRGBQUAD;

class tagShowItem {
public:
    ECBShowItemKind eKind; // +0x0
    char sTxt[256]; // +0x4
    tagRGBQUAD color; // +0x104
    float fX; // +0x108
    float fY; // +0x10C
    float fZ; // +0x110
    float fSize; // +0x114
    // total size: 0x118 (280)

};
