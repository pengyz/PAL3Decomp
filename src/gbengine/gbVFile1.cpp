#include "gbengine/gbVFileSystem.h"
#include <string.h>

// gbVFile1::GetEntry - Get entry number/hash for this file

unsigned int gbVFile1::GetEntry() {
    // This method likely returns the CRC32 hash of the file path
    // Used for file identification in the virtual file system

    // Calculate CRC32 of the full path
    unsigned int crc = 0xFFFFFFFF;

    for (const char* p = fullPath; *p; p++) {
        unsigned char byte = (unsigned char)*p;
        // Convert to lowercase for case-insensitive hashing
        if (byte >= 'A' && byte <= 'Z') {
            byte = byte - 'A' + 'a';
        }
        // Convert backslash to forward slash
        if (byte == '\\') {
            byte = '/';
        }

        crc ^= byte;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc = crc >> 1;
            }
        }
    }

    return ~crc;
}
