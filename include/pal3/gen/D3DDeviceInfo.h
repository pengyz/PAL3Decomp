#pragma once
// Auto-generated: D3DDeviceInfo

#include "_D3DCAPS9.h"
#include "_D3DDEVTYPE.h"

class CArrayList;

class D3DDeviceInfo {
public:
    int AdapterOrdinal; // +0x0
    _D3DDEVTYPE DevType; // +0x4
    _D3DCAPS9 Caps; // +0x8
    CArrayList * pDeviceComboList; // +0x138
    // total size: 0x13C (316)

};
