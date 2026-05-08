/**
 * gbengine.dll - D3D Framework utilities
 *
 * DXSDK sample framework code compiled directly into the engine.
 * Includes CArrayList (dynamic array) and CD3DEnumeration (device enumeration).
 *
 * Compiler: MSVC 6.0 SP5
 */

#include "gbengine/gbGfxManager.h"
#include <windows.h>
#include <d3d9.h>
#include <string.h>
#include <stdlib.h>

// ============================================================================
// 0x10016c20 (69B) - D3DXVec3Subtract helper
// Computes a1 = a2 - a3 (3-component vector subtraction)
// ============================================================================
float* D3DXVec3Subtract(float* a1, float* a2, float* a3) {
    float x = a2[0] - a3[0];
    float y = a2[1] - a3[1];
    float z = a2[2] - a3[2];
    a1[0] = x;
    a1[1] = y;
    a1[2] = z;
    return a1;
}

// ============================================================================
// 0x10016eb0 (34B) - CArrayList::GetPtr
// Returns pointer to element at given index.
// If m_bPtrArray==0: contiguous array, compute offset via stride
// If m_bPtrArray!=0: pointer array, dereference
// __thiscall, RET 0x4 (1 stack param: index)
// ============================================================================
void* CArrayList::GetPtr(int index) {
    if (m_bPtrArray == 0) {
        return (char*)m_pData + m_BytesPerEntry * index;
    }
    return *(void**)((char*)m_pData + index * 4);
}

// ============================================================================
// 0x10016dc0 (238B) - CArrayList::Add
// Adds an element to the array. Grows buffer if needed.
// __thiscall, RET 0x4 (1 stack param: pEntry)
// Returns: S_OK on success, E_FAIL if no entry size, E_OUTOFMEMORY if OOM
// ============================================================================
int CArrayList::Add(void* pEntry) {
    if (m_BytesPerEntry == 0) {
        return E_FAIL;
    }

    if (m_pData == NULL || (unsigned int)m_MaxEntries < (unsigned int)(m_NumEntries + 1)) {
        int newMax;
        if (m_MaxEntries == 0) {
            newMax = 0x10;
        } else {
            newMax = m_MaxEntries * 2;
        }

        void* pNewData = operator new(m_BytesPerEntry * newMax);
        if (pNewData == NULL) {
            return E_OUTOFMEMORY;
        }

        if (m_pData != NULL) {
            memcpy(pNewData, m_pData, m_NumEntries * m_BytesPerEntry);
            operator delete(m_pData);
        }

        m_pData = pNewData;
        m_MaxEntries = newMax;
    }

    if (m_bPtrArray == 0) {
        memcpy((char*)m_pData + m_BytesPerEntry * m_NumEntries, pEntry, m_BytesPerEntry);
        m_NumEntries++;
        return 0;
    }

    // Pointer array: store the pointer directly
    *((void**)m_pData + m_NumEntries) = pEntry;
    m_NumEntries++;
    return 0;
}

// ============================================================================
// 0x100172f0 (1378B) - CD3DEnumeration::Enumerate
// DXSDK Framework code: enumerates all D3D adapters, device types, display modes.
// Iterates IDirect3D9 adapter/device/mode APIs and builds CArrayList structures
// for each adapter's supported configurations.
// ============================================================================
int CD3DEnumeration::Enumerate(void) {
    if (m_pD3D == NULL) {
        return E_FAIL;
    }

    // Create adapter info list (pointer array)
    CArrayList* pAdapterList = (CArrayList*)operator new(0x14);
    if (pAdapterList == NULL) {
        return E_OUTOFMEMORY;
    }
    pAdapterList->m_bPtrArray = 1;
    pAdapterList->m_pData = NULL;
    pAdapterList->m_BytesPerEntry = 4;
    pAdapterList->m_NumEntries = 0;
    pAdapterList->m_MaxEntries = 0;

    m_pAdapterInfoList = pAdapterList;

    // Create allowed adapter formats list (value array, D3DFORMAT entries)
    CArrayList* pFormatList = (CArrayList*)operator new(0x14);
    if (pFormatList == NULL) {
        return E_OUTOFMEMORY;
    }
    pFormatList->m_bPtrArray = 0;
    pFormatList->m_pData = NULL;
    pFormatList->m_BytesPerEntry = 4;
    pFormatList->m_NumEntries = 0;
    pFormatList->m_MaxEntries = 0;

    m_pAllowedAdapterFormatList = pFormatList;

    // Add default allowed adapter formats
    int fmt;
    fmt = (int)D3DFMT_X8R8G8B8;
    pFormatList->Add(&fmt);
    fmt = (int)D3DFMT_X1R5G5B5;
    pFormatList->Add(&fmt);
    fmt = (int)D3DFMT_R5G6B5;
    pFormatList->Add(&fmt);
    fmt = (int)D3DFMT_A2R10G10B10;
    pFormatList->Add(&fmt);

    // Enumerate all adapters
    unsigned int numAdapters = m_pD3D->GetAdapterCount();
    unsigned int iAdapter;

    for (iAdapter = 0; iAdapter < numAdapters; iAdapter++) {
        // Allocate adapter info structure
        D3DAdapterInfo* pAdapterInfo = (D3DAdapterInfo*)operator new(sizeof(D3DAdapterInfo));
        if (pAdapterInfo == NULL) {
            return E_OUTOFMEMORY;
        }

        // Create display mode list (value array, D3DDISPLAYMODE = 0x10 bytes per entry)
        CArrayList* pModeList = (CArrayList*)operator new(0x14);
        if (pModeList == NULL) {
            operator delete(pAdapterInfo);
            return E_OUTOFMEMORY;
        }
        pModeList->m_bPtrArray = 0;
        pModeList->m_pData = NULL;
        pModeList->m_BytesPerEntry = 0x10;
        pModeList->m_NumEntries = 0;
        pModeList->m_MaxEntries = 0;
        pAdapterInfo->pDisplayModeList = pModeList;

        // Create device info list (pointer array)
        CArrayList* pDeviceList = (CArrayList*)operator new(0x14);
        if (pDeviceList == NULL) {
            operator delete(pAdapterInfo);
            return E_OUTOFMEMORY;
        }
        pDeviceList->m_bPtrArray = 1;
        pDeviceList->m_pData = NULL;
        pDeviceList->m_BytesPerEntry = 4;
        pDeviceList->m_NumEntries = 0;
        pDeviceList->m_MaxEntries = 0;
        pAdapterInfo->pDeviceInfoList = pDeviceList;

        // Store adapter ordinal
        pAdapterInfo->AdapterOrdinal = iAdapter;

        // Get adapter identifier
        m_pD3D->GetAdapterIdentifier(iAdapter, 0, &pAdapterInfo->adapterIdentifier);

        // Enumerate display modes for each allowed format
        unsigned int iFmt;
        for (iFmt = 0; iFmt < (unsigned int)m_pAllowedAdapterFormatList->m_NumEntries; iFmt++) {
            D3DFORMAT adapterFmt = *(D3DFORMAT*)m_pAllowedAdapterFormatList->GetPtr(iFmt);

            unsigned int numModes = m_pD3D->GetAdapterModeCount(iAdapter, adapterFmt);
            unsigned int iMode;
            for (iMode = 0; iMode < numModes; iMode++) {
                D3DDISPLAYMODE mode;
                m_pD3D->EnumAdapterModes(iAdapter, adapterFmt, iMode, &mode);

                if (mode.Width >= m_nMinWidth && mode.Height >= m_nMinHeight) {
                    // Determine color channel bit depth for this format
                    unsigned int colorBits;
                    switch (mode.Format) {
                    case D3DFMT_X8R8G8B8:
                    case D3DFMT_A8R8G8B8:
                    case D3DFMT_A2R10G10B10:
                        colorBits = 8; break;
                    case D3DFMT_R5G6B5:
                    case D3DFMT_X1R5G5B5:
                    case D3DFMT_A1R5G5B5:
                        colorBits = 5; break;
                    case D3DFMT_R8G8B8:
                        colorBits = 8; break;
                    case D3DFMT_A4R4G4B4:
                    case D3DFMT_X4R4G4B4:
                        colorBits = 4; break;
                    case D3DFMT_R3G3B2:
                    case D3DFMT_A8R3G3B2:
                        colorBits = 2; break;
                    default:
                        colorBits = 0; break;
                    }

                    if (m_nMinColorChannelBits <= colorBits) {
                        pModeList->Add(&mode);
                    }
                }
            }
        }

        // Add adapter to list
        pAdapterList->Add(&pAdapterInfo);
    }

    return 0;
}

// ============================================================================
// 0x10016db0 (15B) - CArrayList::~CArrayList
// Destructor: frees internal data buffer.
// ============================================================================
CArrayList::~CArrayList() {
    if (m_pData)
        operator delete(m_pData);
}

// ============================================================================
// 0x100170d0 (57B) - CD3DEnumeration::CD3DEnumeration
// Constructor: initializes default display mode constraints.
// ============================================================================
CD3DEnumeration::CD3DEnumeration() {
    m_pAdapterInfoList = NULL;
    m_pAllowedAdapterFormatList = NULL;
    m_nMinWidth = 640;
    m_nMinHeight = 480;
    m_nMinColorChannelBits = 5;
    m_nMinAlphaChannelBits = 0;
    m_nMinDepthBits = 15;
    m_nMinStencilBits = 0;
    m_bMultisampleEnabled = 0;
    _pad25 = 0;
    m_bRequireWindowed = 0;
    m_bRequireFullscreen = 0;
}

// ============================================================================
// 0x100178c0 (100B) - SortModesCallback
// Compare function for qsort on D3DDISPLAYMODE array.
// Sort order: Width > Height > RefreshRate > Format
// ============================================================================
static int __cdecl SortModesCallback(const void* a1, const void* a2) {
    const unsigned int* p1 = (const unsigned int*)a1;
    const unsigned int* p2 = (const unsigned int*)a2;

    // Compare Width
    if (p1[0] > p2[0]) return 1;
    if (p1[0] < p2[0]) return -1;
    // Compare Height
    if (p1[1] > p2[1]) return 1;
    if (p1[1] < p2[1]) return -1;
    // Compare Format (at offset 3)
    if ((int)p1[3] > (int)p2[3]) return 1;
    if ((int)p1[3] < (int)p2[3]) return -1;
    // Compare RefreshRate (at offset 2)
    if (p1[2] > p2[2]) return 1;
    if (p1[2] < p2[2]) return -1;
    return 0;
}

// ============================================================================
// 0x10017000 (199B) - D3DDeviceCombo::Cleanup
// Frees the 6 CArrayList pointers inside a D3DDeviceCombo.
// __thiscall (ecx = D3DDeviceCombo*)
// ============================================================================
void D3DDeviceCombo::Cleanup() {
    CArrayList* pList;

    pList = pDepthStencilFormatList;
    if (pList) {
        if (pList->m_pData)
            operator delete(pList->m_pData);
        operator delete(pList);
    }
    pList = pMultiSampleTypeList;
    if (pList) {
        if (pList->m_pData)
            operator delete(pList->m_pData);
        operator delete(pList);
    }
    pList = pMultiSampleQualityList;
    if (pList) {
        if (pList->m_pData)
            operator delete(pList->m_pData);
        operator delete(pList);
    }
    pList = pConflictList;
    if (pList) {
        if (pList->m_pData)
            operator delete(pList->m_pData);
        operator delete(pList);
    }
    pList = pVertexProcessingTypeList;
    if (pList) {
        if (pList->m_pData)
            operator delete(pList->m_pData);
        operator delete(pList);
    }
    pList = pPresentIntervalList;
    if (pList) {
        if (pList->m_pData)
            operator delete(pList->m_pData);
        operator delete(pList);
    }
}

// ============================================================================
// 0x10016EE0 (281B) - D3DAdapterInfo::Cleanup
// Frees an adapter's display mode list and device info list.
// Iterates each D3DDeviceInfo's device combo list, calling D3DDeviceCombo::Cleanup.
// __thiscall (ecx = D3DAdapterInfo*)
// ============================================================================
void D3DAdapterInfo::Cleanup() {
    CArrayList* pList;
    CArrayList* pDeviceInfoList;
    D3DDeviceInfo* pDeviceInfo;
    CArrayList* pDeviceComboList;
    D3DDeviceCombo* pCombo;
    unsigned int i, j;

    // Free display mode list
    pList = pDisplayModeList;
    if (pList) {
        if (pList->m_pData)
            operator delete(pList->m_pData);
        operator delete(pList);
    }

    // Free device info list and all device combos
    pDeviceInfoList = this->pDeviceInfoList;
    if (pDeviceInfoList) {
        for (i = 0; i < (unsigned int)pDeviceInfoList->m_NumEntries; i++) {
            pDeviceInfo = (D3DDeviceInfo*)pDeviceInfoList->GetPtr(i);
            if (pDeviceInfo) {
                pDeviceComboList = pDeviceInfo->pDeviceComboList;
                if (pDeviceComboList) {
                    for (j = 0; j < (unsigned int)pDeviceComboList->m_NumEntries; j++) {
                        pCombo = (D3DDeviceCombo*)pDeviceComboList->GetPtr(j);
                        if (pCombo) {
                            pCombo->Cleanup();
                            operator delete(pCombo);
                        }
                        pDeviceComboList = pDeviceInfo->pDeviceComboList;
                    }
                    pList = pDeviceInfo->pDeviceComboList;
                    if (pList) {
                        if (pList->m_pData)
                            operator delete(pList->m_pData);
                        operator delete(pList);
                    }
                }
                operator delete(pDeviceInfo);
            }
            pDeviceInfoList = this->pDeviceInfoList;
        }
        pList = this->pDeviceInfoList;
        if (pList) {
            if (pList->m_pData)
                operator delete(pList->m_pData);
            operator delete(pList);
        }
    }
}

// ============================================================================
// 0x10017110 (275B) - CD3DEnumeration::Cleanup
// Cleans up the enumeration: frees adapter info list and format list.
// __thiscall (ecx = CD3DEnumeration*)
// ============================================================================
void CD3DEnumeration::Cleanup() {
    CArrayList* pAdapterInfoList;
    D3DAdapterInfo* pAdapterInfo;
    CArrayList* pDisplayModeList;
    CArrayList* pDeviceInfoList;
    D3DDeviceInfo* pDeviceInfo;
    CArrayList* pDeviceComboList;
    D3DDeviceCombo* pCombo;
    CArrayList* pList;
    unsigned int i, j;

    pAdapterInfoList = m_pAdapterInfoList;
    if (pAdapterInfoList) {
        for (i = 0; i < (unsigned int)pAdapterInfoList->m_NumEntries; i++) {
            pAdapterInfo = (D3DAdapterInfo*)pAdapterInfoList->GetPtr(i);
            if (pAdapterInfo) {
                // Free display mode list
                pDisplayModeList = pAdapterInfo->pDisplayModeList;
                if (pDisplayModeList) {
                    if (pDisplayModeList->m_pData)
                        operator delete(pDisplayModeList->m_pData);
                    operator delete(pDisplayModeList);
                }
                // Free device info list
                pDeviceInfoList = pAdapterInfo->pDeviceInfoList;
                if (pDeviceInfoList) {
                    for (j = 0; j < (unsigned int)pDeviceInfoList->m_NumEntries; j++) {
                        pDeviceInfo = (D3DDeviceInfo*)pDeviceInfoList->GetPtr(j);
                        if (pDeviceInfo) {
                            // Cleanup device info: iterate combos
                            pDeviceComboList = pDeviceInfo->pDeviceComboList;
                            if (pDeviceComboList) {
                                for (unsigned int k = 0; k < (unsigned int)pDeviceComboList->m_NumEntries; k++) {
                                    pCombo = (D3DDeviceCombo*)pDeviceComboList->GetPtr(k);
                                    if (pCombo) {
                                        pCombo->Cleanup();
                                        operator delete(pCombo);
                                    }
                                    pDeviceComboList = pDeviceInfo->pDeviceComboList;
                                }
                                pList = pDeviceInfo->pDeviceComboList;
                                if (pList) {
                                    if (pList->m_pData)
                                        operator delete(pList->m_pData);
                                    operator delete(pList);
                                }
                            }
                            operator delete(pDeviceInfo);
                        }
                        pDeviceInfoList = pAdapterInfo->pDeviceInfoList;
                    }
                    pList = pAdapterInfo->pDeviceInfoList;
                    if (pList) {
                        if (pList->m_pData)
                            operator delete(pList->m_pData);
                        operator delete(pList);
                    }
                }
                operator delete(pAdapterInfo);
            }
            pAdapterInfoList = m_pAdapterInfoList;
        }
        pList = m_pAdapterInfoList;
        if (pList) {
            if (pList->m_pData)
                operator delete(pList->m_pData);
            operator delete(pList);
        }
    }
    pList = m_pAllowedAdapterFormatList;
    if (pList) {
        if (pList->m_pData)
            operator delete(pList->m_pData);
        operator delete(pList);
    }
    m_pAllowedAdapterFormatList = NULL;
}

// ============================================================================
// 0x10017FE0 (259B) - CD3DEnumeration::CheckDepthStencilFormats
// Checks which depth/stencil formats are compatible with a device combo.
// __thiscall (ecx = CD3DEnumeration*)
// ============================================================================
void CD3DEnumeration::CheckDepthStencilFormats(D3DDeviceCombo* pCombo) {
    D3DFORMAT depthFmts[] = {
        (D3DFORMAT)80,  // D3DFMT_D16
        (D3DFORMAT)73,  // D3DFMT_D15S1
        (D3DFORMAT)77,  // D3DFMT_D24X8
        (D3DFORMAT)75,  // D3DFMT_D24S8
        (D3DFORMAT)79,  // D3DFMT_D24X4S4
        (D3DFORMAT)71   // D3DFMT_D32
    };
    D3DFORMAT* p = depthFmts;
    int count = 6;
    int result;
    D3DFORMAT fmtVal;
    unsigned int depthBits, stencilBits;

    do {
        fmtVal = *p;

        // Determine depth bits
        switch ((int)fmtVal) {
        case 80: // D3DFMT_D16
            depthBits = 16; break;
        case 73: // D3DFMT_D15S1
            depthBits = 15; break;
        case 75: // D3DFMT_D24S8
        case 77: // D3DFMT_D24X8
        case 79: // D3DFMT_D24X4S4
            depthBits = 24; break;
        case 71: // D3DFMT_D32
            depthBits = 32; break;
        default:
            depthBits = 0; break;
        }

        if (depthBits >= m_nMinDepthBits) {
            // Determine stencil bits
            switch ((int)fmtVal) {
            case 73: // D3DFMT_D15S1
                stencilBits = 1; break;
            case 75: // D3DFMT_D24S8
                stencilBits = 8; break;
            case 77: // D3DFMT_D24X8
            case 80: // D3DFMT_D16
            case 71: // D3DFMT_D32
                stencilBits = 0; break;
            case 79: // D3DFMT_D24X4S4
                stencilBits = 4; break;
            default:
                stencilBits = 0; break;
            }

            if (stencilBits >= m_nMinStencilBits) {
                // CheckDeviceFormat (vtable offset 40)
                result = m_pD3D->CheckDeviceFormat(
                    pCombo->AdapterOrdinal,
                    pCombo->DevType,
                    pCombo->AdapterFormat,
                    D3DUSAGE_DEPTHSTENCIL,
                    D3DRTYPE_SURFACE,
                    fmtVal);
                if (result >= 0) {
                    // CheckDepthStencilMatch (vtable offset 48)
                    result = m_pD3D->CheckDepthStencilMatch(
                        pCombo->AdapterOrdinal,
                        pCombo->DevType,
                        pCombo->AdapterFormat,
                        pCombo->BackBufferFormat,
                        fmtVal);
                    if (result >= 0) {
                        result = pCombo->pDepthStencilFormatList->Add(&fmtVal);
                    }
                }
            }
        }
        ++p;
        --count;
    } while (count);
}

// ============================================================================
// 0x10018140 (252B) - CD3DEnumeration::CheckMultisampleTypes
// Checks which multisample types are compatible with a device combo.
// __thiscall (ecx = CD3DEnumeration*)
// ============================================================================
void CD3DEnumeration::CheckMultisampleTypes(D3DDeviceCombo* pCombo) {
    int msTypes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int* p = msTypes;
    int count = 17;
    int msType;
    DWORD qualityLevels;

    do {
        msType = *p;
        if (m_pD3D->CheckDeviceMultiSampleType(
                pCombo->AdapterOrdinal,
                pCombo->DevType,
                pCombo->BackBufferFormat,
                (BOOL)pCombo->bIsWindowed,
                (D3DMULTISAMPLE_TYPE)msType,
                &qualityLevels) >= 0) {
            pCombo->pMultiSampleTypeList->Add(&msType);
            pCombo->pMultiSampleQualityList->Add(&qualityLevels);
        }
        ++p;
        --count;
    } while (count);
}

// ============================================================================
// 0x10018240 (193B) - CD3DEnumeration::CheckConflictPairs
// Checks for depth/stencil + multisample conflicts for a device combo.
// __thiscall (ecx = CD3DEnumeration*)
// ============================================================================
void CD3DEnumeration::CheckConflictPairs(D3DDeviceCombo* pCombo) {
    CArrayList* pDSList;
    CArrayList* pMSList;
    unsigned int iDS, iMS;
    int dsFmt, msFmt;
    int result;
    int conflictPair[2];

    iDS = 0;
    pDSList = pCombo->pDepthStencilFormatList;
    if (pDSList->m_NumEntries > 0) {
        do {
            dsFmt = *(int*)pDSList->GetPtr(iDS);
            pMSList = pCombo->pMultiSampleTypeList;
            iMS = 0;
            if (pMSList->m_NumEntries > 0) {
                do {
                    msFmt = *(int*)pMSList->GetPtr(iMS);
                    result = m_pD3D->CheckDeviceMultiSampleType(
                        pCombo->AdapterOrdinal,
                        pCombo->DevType,
                        (D3DFORMAT)dsFmt,
                        (BOOL)pCombo->bIsWindowed,
                        (D3DMULTISAMPLE_TYPE)msFmt,
                        NULL);
                    if (result < 0) {
                        conflictPair[0] = dsFmt;
                        conflictPair[1] = msFmt;
                        pCombo->pConflictList->Add(conflictPair);
                    }
                    pMSList = pCombo->pMultiSampleTypeList;
                    ++iMS;
                } while (iMS < (unsigned int)pMSList->m_NumEntries);
            }
            pDSList = pCombo->pDepthStencilFormatList;
            ++iDS;
        } while (iDS < (unsigned int)pDSList->m_NumEntries);
    }
}

// ============================================================================
// 0x10018310 (251B) - CD3DEnumeration::CheckPresentIntervals
// Checks which vertex processing types are valid for the device combo.
// __thiscall (ecx = CD3DEnumeration*)
// ============================================================================
void CD3DEnumeration::CheckPresentIntervals(D3DDeviceInfo* pDeviceInfo, D3DDeviceCombo* pCombo) {
    CONFIRMDEVICECALLBACK pCallback;
    int vpType;
    unsigned char result;

    // Check hardware vertex processing types based on DevCaps
    int devCaps = *(int *)((char *)pDeviceInfo + 36);

    if (devCaps & 0x10000) {  // D3DDEVCAPS_HWTRANSFORMANDLIGHT
        if (devCaps & 0x100000) {  // D3DDEVCAPS_PUREDEVICE
            pCallback = ConfirmDeviceCallback;
            if (!pCallback || pCallback(&pDeviceInfo->Caps, 3, pCombo->AdapterFormat, pCombo->BackBufferFormat)) {
                vpType = 3;  // PURE_HARDWARE_VP
                pCombo->pVertexProcessingTypeList->Add(&vpType);
            }
        }
        pCallback = ConfirmDeviceCallback;
        if (!pCallback || pCallback(&pDeviceInfo->Caps, 2, pCombo->AdapterFormat, pCombo->BackBufferFormat)) {
            vpType = 2;  // HARDWARE_VP
            pCombo->pVertexProcessingTypeList->Add(&vpType);
        }
        if (_pad25) {  // byte offset 0x25
            pCallback = ConfirmDeviceCallback;
            if (!pCallback || pCallback(&pDeviceInfo->Caps, 1, pCombo->AdapterFormat, pCombo->BackBufferFormat)) {
                vpType = 1;  // MIXED_VP
                pCombo->pVertexProcessingTypeList->Add(&vpType);
            }
        }
    }
    pCallback = ConfirmDeviceCallback;
    if (!pCallback || (result = pCallback(&pDeviceInfo->Caps, 0, pCombo->AdapterFormat, pCombo->BackBufferFormat), result)) {
        vpType = 0;  // SOFTWARE_VP
        pCombo->pVertexProcessingTypeList->Add(&vpType);
    }
}

// ============================================================================
// 0x10017BD0 (961B) - CD3DEnumeration::EnumerateDeviceComboFormats
// Iterates adapter format list, tries backbuffer/windowed combinations,
// creates D3DDeviceCombo for each valid combo.
// __thiscall (ecx = CD3DEnumeration*)
// ============================================================================
int CD3DEnumeration::EnumerateDeviceComboFormats(D3DDeviceInfo* pDeviceInfo, CArrayList* pAdapterFormatList) {
    D3DFORMAT bbFmts[] = {
        (D3DFORMAT)21, (D3DFORMAT)22, (D3DFORMAT)35,
        (D3DFORMAT)23, (D3DFORMAT)25, (D3DFORMAT)24
    };
    char bWindowed[] = {0, 1};

    unsigned int iFmt = 0;
    unsigned int adapterFmtIdx = 0;
    unsigned int bbFmtIdx = 0;

    if (!pAdapterFormatList->m_NumEntries)
        return 0;

LABEL_2:
    ;
    {
        D3DFORMAT adapterFmt = *(D3DFORMAT*)pAdapterFormatList->GetPtr(iFmt);

        bbFmtIdx = 0;
        D3DFORMAT* pBBFmt = bbFmts;

        while (1) {
            D3DFORMAT bbFmt = *pBBFmt;

            // Determine min color channel bits for bb format
            unsigned int colorBits;
            switch ((int)bbFmt) {
            case 21: // D3DFMT_A8R8G8B8
            case 29: // D3DFMT_A8B8G8R8
                colorBits = 8; break;
            case 25: // D3DFMT_A1R5G5B5
                colorBits = 1; break;
            case 26: // D3DFMT_A4R4G4B4
                colorBits = 4; break;
            case 31: // D3DFMT_A8R3G3B2 (format value)
            case 35: // D3DFMT_A2R10G10B10
                colorBits = 2; break;
            default:
                colorBits = 0; break;
            }

            if (colorBits < m_nMinAlphaChannelBits)
                break;

            char bWnd;
            unsigned int iWindowed = 0;
            while (1) {
                bWnd = bWindowed[iWindowed];
                if (bWnd) {
                    if (m_bRequireFullscreen)
                        goto LABEL_60;
                } else {
                    if (m_bRequireWindowed)
                        goto LABEL_60;
                }

                // CheckDeviceType (vtable offset 36)
                if (m_pD3D->CheckDeviceType(
                        pDeviceInfo->AdapterOrdinal,
                        pDeviceInfo->DevType,
                        adapterFmt,
                        bbFmt,
                        (BOOL)(unsigned char)bWnd) >= 0)
                    break;

            LABEL_60:
                iWindowed++;
                if (iWindowed >= 2) {
                    goto LABEL_62;
                }
            }

            // Found a valid combo - create D3DDeviceCombo
            {
                D3DDeviceCombo* pCombo = (D3DDeviceCombo*)operator new(0x2C);
                if (!pCombo)
                    return E_OUTOFMEMORY;

                // Create pDepthStencilFormatList
                CArrayList* pList = (CArrayList*)operator new(0x14);
                if (pList) {
                    pList->m_bPtrArray = 0;
                    pList->m_pData = NULL;
                    pList->m_BytesPerEntry = 4;
                    pList->m_NumEntries = 0;
                    pList->m_MaxEntries = 0;
                } else {
                    pList = NULL;
                }
                pCombo->pDepthStencilFormatList = pList;

                // Create pMultiSampleTypeList
                pList = (CArrayList*)operator new(0x14);
                if (pList) {
                    pList->m_bPtrArray = 0;
                    pList->m_pData = NULL;
                    pList->m_BytesPerEntry = 4;
                    pList->m_NumEntries = 0;
                    pList->m_MaxEntries = 0;
                } else {
                    pList = NULL;
                }
                pCombo->pMultiSampleTypeList = pList;

                // Create pMultiSampleQualityList
                pList = (CArrayList*)operator new(0x14);
                if (pList) {
                    pList->m_bPtrArray = 0;
                    pList->m_pData = NULL;
                    pList->m_BytesPerEntry = 4;
                    pList->m_NumEntries = 0;
                    pList->m_MaxEntries = 0;
                } else {
                    pList = NULL;
                }
                pCombo->pMultiSampleQualityList = pList;

                // Create pConflictList (8 bytes per entry)
                pList = (CArrayList*)operator new(0x14);
                if (pList) {
                    pList->m_bPtrArray = 0;
                    pList->m_pData = NULL;
                    pList->m_BytesPerEntry = 8;
                    pList->m_NumEntries = 0;
                    pList->m_MaxEntries = 0;
                } else {
                    pList = NULL;
                }
                pCombo->pConflictList = pList;

                // Create pVertexProcessingTypeList
                pList = (CArrayList*)operator new(0x14);
                if (pList) {
                    pList->m_bPtrArray = 0;
                    pList->m_pData = NULL;
                    pList->m_BytesPerEntry = 4;
                    pList->m_NumEntries = 0;
                    pList->m_MaxEntries = 0;
                } else {
                    pList = NULL;
                }
                pCombo->pVertexProcessingTypeList = pList;

                // Create pPresentIntervalList
                pList = (CArrayList*)operator new(0x14);
                if (pList) {
                    pList->m_bPtrArray = 0;
                    pList->m_pData = NULL;
                    pList->m_BytesPerEntry = 4;
                    pList->m_NumEntries = 0;
                    pList->m_MaxEntries = 0;
                } else {
                    pList = NULL;
                }
                pCombo->pPresentIntervalList = pList;

                // Check all lists were allocated
                if (!pCombo->pDepthStencilFormatList || !pCombo->pMultiSampleTypeList ||
                    !pCombo->pMultiSampleQualityList || !pCombo->pConflictList ||
                    !pCombo->pPresentIntervalList || !pCombo->pVertexProcessingTypeList) {
                    pCombo->Cleanup();
                    operator delete(pCombo);
                    return E_OUTOFMEMORY;
                }

                // Fill combo fields
                pCombo->AdapterOrdinal = pDeviceInfo->AdapterOrdinal;
                pCombo->DevType = pDeviceInfo->DevType;
                pCombo->AdapterFormat = adapterFmt;
                pCombo->BackBufferFormat = bbFmt;
                pCombo->bIsWindowed = bWnd;

                // Check depth stencil formats (only if multisample not disabled)
                if (!m_bMultisampleEnabled || (CheckDepthStencilFormats(pCombo), pCombo->pDepthStencilFormatList->m_NumEntries)) {
                    // Check multisample types
                    CheckMultisampleTypes(pCombo);
                    if (pCombo->pMultiSampleTypeList->m_NumEntries) {
                        // Check conflict pairs
                        CheckConflictPairs(pCombo);

                        // Check vertex processing types
                        CheckPresentIntervals(pDeviceInfo, pCombo);
                        if (pCombo->pVertexProcessingTypeList->m_NumEntries) {
                            // Build present interval list based on caps
                            unsigned int presentIntervals[] = {0x80000000, 0, 1, 2, 4, 8};
                            int pi;
                            for (int n = 0; n < 6; n++) {
                                pi = presentIntervals[n];
                                if ((!pCombo->bIsWindowed || (pi != 2 && pi != 4 && pi != 8)) &&
                                    (!pi || ((unsigned int)pi & *(unsigned int*)((char*)pDeviceInfo + 8 + 20)) != 0)) {
                                    pCombo->pPresentIntervalList->Add(&pi);
                                }
                            }

                            // Add combo to device info's combo list
                            pDeviceInfo->pDeviceComboList->Add(&pCombo);
                        } else {
                            pCombo->Cleanup();
                            operator delete(pCombo);
                        }
                    } else {
                        pCombo->Cleanup();
                        operator delete(pCombo);
                    }
                } else {
                    pCombo->Cleanup();
                    operator delete(pCombo);
                }
            }
            goto LABEL_60;

        LABEL_62:
            bbFmtIdx++;
            pBBFmt++;
            if (bbFmtIdx >= 6) {
                iFmt++;
                adapterFmtIdx = iFmt;
                if (iFmt >= (unsigned int)pAdapterFormatList->m_NumEntries)
                    return 0;
                goto LABEL_2;
            }
        }
    }
}

// ============================================================================
// 0x10017930 (640B) - CD3DEnumeration::BuildDeviceInfoList
// Iterates D3D device types (HAL=1, SW=3, REF=2), builds D3DDeviceInfo
// for each that supports GetDeviceCaps, and enumerates device combos.
// __thiscall (ecx = CD3DEnumeration*)
// ============================================================================
int CD3DEnumeration::BuildDeviceInfoList(D3DAdapterInfo* pAdapterInfo, CArrayList* pAdapterFormatList) {
    D3DDEVTYPE devTypes[] = {D3DDEVTYPE_HAL, D3DDEVTYPE_SW, D3DDEVTYPE_REF};
    unsigned int iType;
    int hr;

    for (iType = 0; iType < 3; iType++) {
        // Allocate D3DDeviceInfo
        D3DDeviceInfo* pDeviceInfo = (D3DDeviceInfo*)operator new(0x13C);
        if (!pDeviceInfo)
            return E_OUTOFMEMORY;

        // Create device combo list (pointer array)
        CArrayList* pComboList = (CArrayList*)operator new(0x14);
        if (pComboList) {
            pComboList->m_bPtrArray = 1;
            pComboList->m_pData = NULL;
            pComboList->m_BytesPerEntry = 4;
            pComboList->m_NumEntries = 0;
            pComboList->m_MaxEntries = 0;
        } else {
            pComboList = NULL;
        }
        pDeviceInfo->pDeviceComboList = pComboList;

        if (!pComboList) {
            // Cleanup and return OOM
            CArrayList* pList = pDeviceInfo->pDeviceComboList;
            if (pList) {
                for (unsigned int k = 0; k < pList->m_NumEntries; k++) {
                    D3DDeviceCombo* pCombo = (D3DDeviceCombo*)pList->GetPtr(k);
                    if (pCombo) {
                        pCombo->Cleanup();
                        operator delete(pCombo);
                    }
                    pList = pDeviceInfo->pDeviceComboList;
                }
                CArrayList* pL = pDeviceInfo->pDeviceComboList;
                if (pL) {
                    if (pL->m_pData)
                        operator delete(pL->m_pData);
                    operator delete(pL);
                }
            }
            operator delete(pDeviceInfo);
            return E_OUTOFMEMORY;
        }

        // Fill device info
        pDeviceInfo->AdapterOrdinal = pAdapterInfo->AdapterOrdinal;
        pDeviceInfo->DevType = devTypes[iType];

        // GetDeviceCaps (vtable offset 56)
        if (m_pD3D->GetDeviceCaps(pAdapterInfo->AdapterOrdinal, devTypes[iType], &pDeviceInfo->Caps) < 0) {
            // GetDeviceCaps failed - cleanup device combos and free
            CArrayList* pList = pDeviceInfo->pDeviceComboList;
            if (pList) {
                for (unsigned int k = 0; k < pList->m_NumEntries; k++) {
                    D3DDeviceCombo* pCombo = (D3DDeviceCombo*)pList->GetPtr(k);
                    if (pCombo) {
                        pCombo->Cleanup();
                        operator delete(pCombo);
                    }
                    pList = pDeviceInfo->pDeviceComboList;
                }
                CArrayList* pL = pDeviceInfo->pDeviceComboList;
                if (pL) {
                    if (pL->m_pData)
                        operator delete(pL->m_pData);
                    operator delete(pL);
                }
            }
            operator delete(pDeviceInfo);
            continue;
        }

        // Enumerate device combo formats
        hr = EnumerateDeviceComboFormats(pDeviceInfo, pAdapterFormatList);
        if (hr < 0) {
            // Error during enumeration - cleanup
            CArrayList* pList = pDeviceInfo->pDeviceComboList;
            if (pList) {
                for (unsigned int k = 0; k < pList->m_NumEntries; k++) {
                    D3DDeviceCombo* pCombo = (D3DDeviceCombo*)pList->GetPtr(k);
                    if (pCombo) {
                        pCombo->Cleanup();
                        operator delete(pCombo);
                    }
                    pList = pDeviceInfo->pDeviceComboList;
                }
                CArrayList* pL = pDeviceInfo->pDeviceComboList;
                if (pL) {
                    if (pL->m_pData)
                        operator delete(pL->m_pData);
                    operator delete(pL);
                }
            }
            operator delete(pDeviceInfo);
            return hr;
        }

        // If device has combos, add to adapter's device info list
        if (pDeviceInfo->pDeviceComboList->m_NumEntries) {
            pAdapterInfo->pDeviceInfoList->Add(&pDeviceInfo);
        } else {
            // No valid combos - cleanup
            CArrayList* pList = pDeviceInfo->pDeviceComboList;
            if (pList) {
                for (unsigned int k = 0; k < pList->m_NumEntries; k++) {
                    D3DDeviceCombo* pCombo = (D3DDeviceCombo*)pList->GetPtr(k);
                    if (pCombo) {
                        pCombo->Cleanup();
                        operator delete(pCombo);
                    }
                    pList = pDeviceInfo->pDeviceComboList;
                }
                CArrayList* pL = pDeviceInfo->pDeviceComboList;
                if (pL) {
                    if (pL->m_pData)
                        operator delete(pL->m_pData);
                    operator delete(pL);
                }
            }
            operator delete(pDeviceInfo);
        }
    }

    return 0;
}
