#pragma once
// Auto-generated: D3DDeviceCombo

#include "_D3DDEVTYPE.h"
#include "_D3DFORMAT.h"

class CArrayList;

class D3DDeviceCombo {
public:
    int AdapterOrdinal; // +0x0
    _D3DDEVTYPE DevType; // +0x4
    _D3DFORMAT AdapterFormat; // +0x8
    _D3DFORMAT BackBufferFormat; // +0xC
    unsigned char IsWindowed; // +0x10
    CArrayList * pDepthStencilFormatList; // +0x14
    CArrayList * pMultiSampleTypeList; // +0x18
    CArrayList * pMultiSampleQualityList; // +0x1C
    CArrayList * pDSMSConflictList; // +0x20
    CArrayList * pVertexProcessingTypeList; // +0x24
    CArrayList * pPresentIntervalList; // +0x28
    // total size: 0x2C (44)

};
