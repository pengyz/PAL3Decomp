#pragma once
// Auto-generated: CD3DSettings

#include "VertexProcessingType.h"
#include "_D3DDISPLAYMODE.h"
#include "_D3DFORMAT.h"
#include "_D3DMULTISAMPLE_TYPE.h"

class D3DAdapterInfo;
class D3DDeviceCombo;
class D3DDeviceInfo;

class CD3DSettings {
public:
    unsigned char IsWindowed; // +0x0
    D3DAdapterInfo * pWindowed_AdapterInfo; // +0x4
    D3DDeviceInfo * pWindowed_DeviceInfo; // +0x8
    D3DDeviceCombo * pWindowed_DeviceCombo; // +0xC
    _D3DDISPLAYMODE Windowed_DisplayMode; // +0x10
    _D3DFORMAT Windowed_DepthStencilBufferFormat; // +0x20
    _D3DMULTISAMPLE_TYPE Windowed_MultisampleType; // +0x24
    unsigned long Windowed_MultisampleQuality; // +0x28
    VertexProcessingType Windowed_VertexProcessingType; // +0x2C
    unsigned int Windowed_PresentInterval; // +0x30
    int Windowed_Width; // +0x34
    int Windowed_Height; // +0x38
    D3DAdapterInfo * pFullscreen_AdapterInfo; // +0x3C
    D3DDeviceInfo * pFullscreen_DeviceInfo; // +0x40
    D3DDeviceCombo * pFullscreen_DeviceCombo; // +0x44
    _D3DDISPLAYMODE Fullscreen_DisplayMode; // +0x48
    _D3DFORMAT Fullscreen_DepthStencilBufferFormat; // +0x58
    _D3DMULTISAMPLE_TYPE Fullscreen_MultisampleType; // +0x5C
    unsigned long Fullscreen_MultisampleQuality; // +0x60
    VertexProcessingType Fullscreen_VertexProcessingType; // +0x64
    unsigned int Fullscreen_PresentInterval; // +0x68
    // total size: 0x6C (108)

};
