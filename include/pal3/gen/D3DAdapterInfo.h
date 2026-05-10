#pragma once
// Auto-generated: D3DAdapterInfo

#include "_D3DADAPTER_IDENTIFIER9.h"

class CArrayList;

class D3DAdapterInfo {
public:
    int AdapterOrdinal; // +0x0
    _D3DADAPTER_IDENTIFIER9 AdapterIdentifier; // +0x4
    CArrayList * pDisplayModeList; // +0x450
    CArrayList * pDeviceInfoList; // +0x454
    // total size: 0x458 (1112)

};
