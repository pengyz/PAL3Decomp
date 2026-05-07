/**
 * gbengine.dll - gbResManager, gbRefObject, gbResource
 * Reference counting and resource management implementation
 */

#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_internal.h"
#include <string.h>
#include <stdlib.h>

// External functions
extern unsigned int gbCrc32Compute(const char* str);

/* ======== gbRefObject ======== */

// Constructor - 0x100015e0
gbRefObject::gbRefObject() {
    // vtable set by compiler
    refCount = 1;
}

// Copy constructor - 0x100017c0
gbRefObject::gbRefObject(const gbRefObject& other) {
    refCount = other.refCount;
}

// Destructor - 0x1002f7e0 (virtual)
gbRefObject::~gbRefObject() {
}

// IncRef - 0x10001600
void gbRefObject::IncRef() {
    refCount++;
}

// DecRef - 0x10001610
void gbRefObject::DecRef() {
    refCount--;
}

// GetRef - 0x100017b0
int gbRefObject::GetRef() {
    return refCount;
}

// Release - 0x1002f7f0
void gbRefObject::Release() {
    refCount--;
    if (refCount == 0) {
        // Call virtual destructor through vtable
        // The destructor will delete the object
        delete this;
    }
}

// operator= - 0x10003980
gbRefObject& gbRefObject::operator=(const gbRefObject& other) {
    if (this != &other) {
        refCount = other.refCount;
    }
    return *this;
}


/* ======== gbResource ======== */

// Constructor - 0x10001840
gbResource::gbResource() : gbRefObject() {
    refCount = 1;
    // vtable set by compiler
    name = NULL;
    isLoaded = NULL;
    manager = NULL;
}

// Copy constructor - 0x10001860
gbResource::gbResource(const gbResource& other) : gbRefObject(other) {
    name = other.name;
    nameCrc = other.nameCrc;
    isLoaded = other.isLoaded;
    manager = other.manager;
    // vtable updated by compiler
}

// Destructor - 0x100200d0
gbResource::~gbResource() {
    // Remove from manager if attached
    if (manager != NULL) {
        gbResManager* mgr = manager;
        int cnt = mgr->count;
        for (int i = 0; i < cnt; i++) {
            if (mgr->array[i] == this) {
                // Remove this resource
                manager = NULL;
                cnt--;

                // Shift last element to fill gap
                if (i < cnt) {
                    mgr->array[i] = mgr->array[cnt];
                }

                // Update count
                mgr->count = cnt;
                break;
            }
        }
    }

    // Free name string
    if (name != NULL) {
        free(name);
    }

    // Call base destructor
    gbRefObject::~gbRefObject();
}

// SetName - 0x10020040
void gbResource::SetName(const char* newName) {
    // Free old name
    if (name != NULL) {
        free(name);
    }

    // Handle NULL or empty string
    if (newName == NULL || newName[0] == '\0') {
        name = NULL;
        nameCrc = 0;
        return;
    }

    // Calculate string length
    size_t len = strlen(newName) + 1;

    // Minimum allocation size
    size_t allocSize = (len < 16) ? 16 : len;

    // Allocate and copy
    name = (char*)malloc(allocSize);
    strcpy(name, newName);

    // Compute CRC32
    nameCrc = gbCrc32Compute(newName);
}

// GetName - 0x100039f0
const char* gbResource::GetName() {
    return name;
}

// GetNameCrc32 - 0x10003cc0
unsigned int gbResource::GetNameCrc32() {
    return nameCrc;
}

// operator= - 0x100018a0
gbResource& gbResource::operator=(const gbResource& other) {
    if (this != &other) {
        gbRefObject::operator=(other);
        name = other.name;
        nameCrc = other.nameCrc;
        isLoaded = other.isLoaded;
        manager = other.manager;
    }
    return *this;
}


/* ======== gbResManager ======== */

// Constructor - 0x10020190
gbResManager::gbResManager() {
    capacity = 0;
    count = 0;
    array = NULL;
}

// Copy constructor
gbResManager::gbResManager(const gbResManager& other) {
    array = other.array;
    capacity = other.capacity;
    count = other.count;
}

// Destructor - 0x100201a0
gbResManager::~gbResManager() {
    if (array != NULL) {
        free(array);
    }
}

// AddResource - 0x10020200
void gbResManager::AddResource(gbResource* res) {
    // Set manager pointer in resource
    res->manager = this;

    // Check if need to grow array
    if (count == capacity) {
        int newCapacity = capacity * 2;
        if (newCapacity == 0) {
            newCapacity = 16;
        }

        if (capacity < newCapacity) {
            capacity = newCapacity;
            gbResource** newArray = (gbResource**)malloc(newCapacity * sizeof(gbResource*));

            // Copy existing elements
            if (count != 0) {
                memcpy(newArray, array, count * sizeof(gbResource*));
            }

            // Free old array
            if (array != NULL) {
                free(array);
            }

            array = newArray;
        }
    }

    // Add resource
    array[count] = res;
    count++;
}

// DelResource - 0x10020280
void gbResManager::DelResource(gbResource* res) {
    // Find resource in array
    for (int i = 0; i < count; i++) {
        if (array[i] == res) {
            // Clear manager pointer
            res->manager = NULL;

            int newCount = count - 1;

            // Move last element to fill gap
            if (i < newCount) {
                array[i] = array[newCount];
            }

            // Shrink capacity if needed
            int newCapacity = newCount;
            if (newCapacity == 0) {
                newCapacity = 16;
            }

            if (capacity < newCapacity) {
                capacity = newCapacity;
                gbResource** newArray = (gbResource**)malloc(newCapacity * sizeof(gbResource*));

                // Copy elements
                if (count != 0) {
                    memcpy(newArray, array, count * sizeof(gbResource*));
                }

                // Free old array
                if (array != NULL) {
                    free(array);
                }

                array = newArray;
            }

            count = newCount;
            break;
        }
    }
}

// FindResByName - 0x100201b0
gbResource* gbResManager::FindResByName(const char* name) {
    if (name == NULL) {
        return NULL;
    }

    // Compute CRC32 for search
    unsigned int crc = gbCrc32Compute(name);

    // Linear search by CRC
    for (int i = 0; i < count; i++) {
        gbResource* res = array[i];
        if (res->nameCrc == crc) {
            // Found - increment ref count and return
            res->refCount++;
            return res;
        }
    }

    return NULL;
}

// CleanAllResource - 0x10020320
void gbResManager::CleanAllResource() {
    while (count != 0) {
        gbResource* res = array[0];

        // Release until refCount reaches 1
        while (res->refCount > 1) {
            res->Release();
        }

        // Final release (will delete)
        res->Release();
    }

    count = 0;
}

// operator= - 0x100019b0
gbResManager& gbResManager::operator=(const gbResManager& other) {
    if (this != &other) {
        array = other.array;
        capacity = other.capacity;
        count = other.count;
    }
    return *this;
}
