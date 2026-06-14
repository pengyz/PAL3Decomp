#pragma once
// Auto-generated: NavTileLayer

#include "gbengine/gbengine_types.h"

class NavTile;

class NavTileLayer {
public:
    tagRECT portal[8]; // +0x0
    char _gap_020[96]; // +0x20
    gbVec3D min; // +0x80
    char _gap_084[8]; // +0x84
    gbVec3D max; // +0x8C
    char _gap_090[8]; // +0x90
    int width; // +0x98
    int height; // +0x9C
    NavTile * tile; // +0xA0
    // total size: 0xA4 (164)

};
