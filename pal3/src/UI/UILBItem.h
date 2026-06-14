#pragma once
// Auto-generated: UILBItem

#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"

class UILBColumn;

class UILBItem {
public:
    gbTexture * picon; // +0x0
    char text[64]; // +0x4
    gbColorQuad itemColor; // +0x44
    // total size: 0x48 (72)

    UILBColumn * _UILBItem(); // 0x0043DC90
};
