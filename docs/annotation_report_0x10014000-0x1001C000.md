# Annotation Report: gbengine Range 0x10014000-0x1001C000

**Date**: 2026-05-08
**Range**: 0x10014000 - 0x1001C000 (52 functions)
**Status**: All 52 unknown functions annotated

## Summary

All unknown functions in this address range have been analyzed using IDA decompilation and annotated with:
- Inferred class names (based on `this` pointer usage and vtable patterns)
- Proposed function names (based on behavior analysis)
- Detailed functional notes

## Key Findings

### 1. DirectX SDK Components (CD3DEnumeration, CD3DSettings)
Functions 0x100170D0-0x100172F0 implement the DXSDK D3D device enumeration system:
- **CD3DEnumeration::EnumerateDeviceCombos** (0x100172F0) - Main enumeration entry point
- **CD3DEnumeration** helper functions for checking formats, multisample, depth/stencil
- **CD3DSettings::Constructor** (0x100170D0) - Initializes default settings (640x480, depth=5)

### 2. gbDynVertBuf_D3D Class (0x10018410-0x100187E0)
Complete D3D dynamic vertex buffer implementation:
- Constructor/Destructor (0x10018410, 0x100184A0)
- Lock/Unlock with FVF component pointer setup (0x10018550)
- Render methods for indexed and non-indexed primitives (0x100186E0, 0x100187E0)
- Device reset handling (0x10018520)

### 3. gbGfxManager_D3D Class (0x100189A0-0x1001BB10)
Main D3D graphics manager with 30 methods:
- **Constructor** (0x100189A0) - Initializes D3D9, checks DXT support
- **InitializeD3D** (0x10019920) - Creates device, enumerates adapters
- **FindBestWindowedMode/FindBestFullscreenMode** (0x10019C60, 0x10019E70) - Mode selection
- **CreateDevice** (0x1001A790) - Creates D3D9 device with presentation parameters
- **ResetDevice** (0x1001AC50) - Handles device loss
- **BeginScene** (0x10018CD0) - Scene setup with matrix/state initialization
- Matrix operations (SetProjectionMatrix, UpdateDeviceMatrices, ExtractFrustumPlanes)
- Resource creation (CreateTexture, CreateVertexBuffer, LoadTextureFromCPK)
- Device capabilities (GetDeviceCaps, CheckTextureFormat, GetDisplayMode)
- Window management (WndProc, OnWindowResize)
- Gamma ramp management (GetGammaRamp, SetGammaRamp)

### 4. Utility Functions
- **gbVec3D_Subtract** (0x10016C20) - Vector subtraction helper
- **D3DFormatComparator** (0x100178C0) - qsort comparator for D3DFORMAT
- **ShowD3DError** (0x1001AD80) - Error message dialog with localized text
- **ConvertFormatToD3DFORMAT** (0x1001AF60) - Format enum conversion
- **FindBestTextureFormat** (0x1001BB10) - Quality tier based format selection

## Class Breakdown

| Class | Functions | Range |
|-------|-----------|-------|
| gbGfxManager_D3D | 30 | 0x100189A0-0x1001BA20 |
| gbDynVertBuf_D3D | 7 | 0x10018410-0x100187E0 |
| CD3DEnumeration | 9 | 0x10016EE0-0x10018310 |
| CD3DSettings | 1 | 0x100170D0 |
| D3DDeviceCombo | 1 | 0x10017000 |
| CArrayList | 1 | 0x10016DB0 |
| gbVertPoolMgr | 1 | 0x10016C70 |
| Utility (no class) | 2 | Various |

## Implementation Priority

**High Priority** (Core D3D functionality):
1. gbGfxManager_D3D::InitializeD3D (0x10019920)
2. gbGfxManager_D3D::CreateDevice (0x1001A790)
3. gbGfxManager_D3D::BeginScene (0x10018CD0)
4. gbGfxManager_D3D::ResetDevice (0x1001AC50)
5. gbDynVertBuf_D3D methods (0x10018410-0x100187E0)

**Medium Priority** (Device enumeration):
1. CD3DEnumeration::EnumerateDeviceCombos (0x100172F0)
2. CD3DEnumeration::BuildDeviceInfoList (0x10017930)
3. gbGfxManager_D3D::FindBestWindowedMode (0x10019C60)
4. gbGfxManager_D3D::FindBestFullscreenMode (0x10019E70)

**Low Priority** (Utilities and less critical):
1. ShowD3DError (0x1001AD80)
2. Format conversion utilities
3. Cleanup/destructor functions

## Next Steps

1. Begin implementation of high-priority functions
2. Create header file for CD3DEnumeration, CD3DSettings (DXSDK structures)
3. Implement gbDynVertBuf_D3D class (small, self-contained)
4. Implement gbGfxManager_D3D core methods incrementally
5. Test compilation and matching as each function is completed

## Notes

- All functions retain "unknown" status until implementation begins
- Annotations provide sufficient context for implementation without re-reading IDA output
- Many functions are part of DirectX SDK sample code (D3DEnumeration.cpp pattern)
- gbGfxManager_D3D size is 0x8F0 bytes (2256 bytes) with complex state management
