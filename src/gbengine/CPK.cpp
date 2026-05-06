/**
 * gbengine.dll - CPK
 * CPK archive file system (LZO compression, CRC32 hashing)
 */

#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

// Static members
unsigned long CPK::CrcTable[256];

bool CPK::GetFileSize(unsigned long& packedSize, unsigned long& originSize,
                      unsigned long tableIndex) {
    if (tableIndex >= CPK_MAX_TABLE_NUM) return false;

    CPKTable* entry = &m_CPKTable[tableIndex];
    if (entry->dwFlag & CPK_FLAG_ISDELETED) return false;

    packedSize = entry->dwPackedSize;
    originSize = entry->dwOriginSize;
    return true;
}

