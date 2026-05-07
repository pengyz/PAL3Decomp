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
