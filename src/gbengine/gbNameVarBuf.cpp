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

gbNameVarBuf::~gbNameVarBuf() {
    /* STUB */
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
    /* STUB */
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

