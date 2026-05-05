#include "gbengine/gbMisc.h"
#include <string.h>
#include <stdlib.h>

// gbNameVarBuf - Name-variable buffer implementation
// Simple hash-based storage for named variables

// Variable descriptor structure (16 bytes per entry)
struct VarDesc {
    unsigned int nameHash;  // +0x00: CRC32 hash of variable name
    int offset;             // +0x04: offset in data buffer
    int size;               // +0x08: size in bytes
    int type;               // +0x0C: variable type
};

gbNameVarBuf::gbNameVarBuf() {
    dataBuf = NULL;
    dataBufCapacity = 0;
    dataBufUsed = 0;
    varTable = NULL;
    varTableCapacity = 0;
    varCount = 0;
    locked = 0;
}

gbNameVarBuf::~gbNameVarBuf() {
    if (dataBuf) {
        free(dataBuf);
        dataBuf = NULL;
    }
    if (varTable) {
        free(varTable);
        varTable = NULL;
    }
}

gbNameVarBuf& gbNameVarBuf::operator=(const gbNameVarBuf& other) {
    if (this != &other) {
        // Clean up existing data
        if (dataBuf) {
            free(dataBuf);
        }
        if (varTable) {
            free(varTable);
        }

        // Copy data buffer
        dataBufCapacity = other.dataBufCapacity;
        dataBufUsed = other.dataBufUsed;
        if (other.dataBuf && other.dataBufCapacity > 0) {
            dataBuf = malloc(dataBufCapacity);
            if (dataBuf) {
                memcpy(dataBuf, other.dataBuf, dataBufUsed);
            }
        } else {
            dataBuf = NULL;
        }

        // Copy variable table
        varTableCapacity = other.varTableCapacity;
        varCount = other.varCount;
        if (other.varTable && other.varTableCapacity > 0) {
            varTable = malloc(varTableCapacity * sizeof(VarDesc));
            if (varTable) {
                memcpy(varTable, other.varTable, varCount * sizeof(VarDesc));
            }
        } else {
            varTable = NULL;
        }

        locked = 0;
    }
    return *this;
}

void gbNameVarBuf::RegVariant(unsigned int nameHash, int size, int type) {
    // Check if variable already exists
    VarDesc* desc = (VarDesc*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (desc[i].nameHash == nameHash) {
            // Variable already registered
            return;
        }
    }

    // Expand variable table if needed
    if (varCount >= varTableCapacity) {
        int newCapacity = varTableCapacity ? (varTableCapacity * 2) : 16;
        void* newTable = realloc(varTable, newCapacity * sizeof(VarDesc));
        if (!newTable) {
            return;
        }
        varTable = newTable;
        varTableCapacity = newCapacity;
        desc = (VarDesc*)varTable;
    }

    // Expand data buffer if needed
    if (dataBufUsed + size > dataBufCapacity) {
        int newCapacity = dataBufCapacity ? (dataBufCapacity * 2) : 1024;
        while (newCapacity < dataBufUsed + size) {
            newCapacity *= 2;
        }
        void* newBuf = realloc(dataBuf, newCapacity);
        if (!newBuf) {
            return;
        }
        dataBuf = newBuf;
        dataBufCapacity = newCapacity;
    }

    // Register new variable
    desc[varCount].nameHash = nameHash;
    desc[varCount].offset = dataBufUsed;
    desc[varCount].size = size;
    desc[varCount].type = type;

    // Zero-initialize the data
    memset((char*)dataBuf + dataBufUsed, 0, size);

    dataBufUsed += size;
    varCount++;
}

int gbNameVarBuf::IsVarExist(unsigned int nameHash) {
    VarDesc* desc = (VarDesc*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (desc[i].nameHash == nameHash) {
            return 1;
        }
    }
    return 0;
}

void gbNameVarBuf::GetVariant(unsigned int nameHash, void* outBuf) {
    if (!outBuf) {
        return;
    }

    VarDesc* desc = (VarDesc*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (desc[i].nameHash == nameHash) {
            memcpy(outBuf, (char*)dataBuf + desc[i].offset, desc[i].size);
            return;
        }
    }
}

void gbNameVarBuf::SetVariant(unsigned int nameHash, void* inBuf) {
    if (!inBuf) {
        return;
    }

    VarDesc* desc = (VarDesc*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (desc[i].nameHash == nameHash) {
            memcpy((char*)dataBuf + desc[i].offset, inBuf, desc[i].size);
            return;
        }
    }
}

void* gbNameVarBuf::LockVariant(unsigned int nameHash, int* outSize) {
    VarDesc* desc = (VarDesc*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (desc[i].nameHash == nameHash) {
            locked = 1;
            if (outSize) {
                *outSize = desc[i].size;
            }
            return (char*)dataBuf + desc[i].offset;
        }
    }

    if (outSize) {
        *outSize = 0;
    }
    return NULL;
}

void gbNameVarBuf::UnlockVariant() {
    locked = 0;
}
