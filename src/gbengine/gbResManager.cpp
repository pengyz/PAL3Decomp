/**
 * gbengine.dll - gbResManager, gbRefObject, gbResource
 * Reference counting and resource management implementation
 */

#include "gbengine/gbengine_types.h"
#include <string.h>
#include <stdlib.h>

// Forward declarations
class gbRefObject;
class gbResource;
class gbResManager;

// External functions
extern unsigned int gbCrc32Compute(const char* str);

/* ======== gbRefObject ======== */

class gbRefObject {
public:
    void* vtable;      // +0x00
    int refCount;      // +0x04

    gbRefObject();
    gbRefObject(const gbRefObject& other);
    virtual ~gbRefObject();

    void IncRef();
    void DecRef();
    int GetRef();
    void Release();

    gbRefObject& operator=(const gbRefObject& other);
};

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

class gbResource : public gbRefObject {
public:
    char* name;           // +0x08
    unsigned int nameCrc; // +0x0c
    void* unknown10;      // +0x10 (unused in observed code)
    gbResManager* manager; // +0x14

    gbResource();
    gbResource(const gbResource& other);
    virtual ~gbResource();

    void SetName(const char* name);
    const char* GetName();
    unsigned int GetNameCrc32();

    gbResource& operator=(const gbResource& other);
};

// Constructor - 0x10001840
gbResource::gbResource() : gbRefObject() {
    refCount = 1;
    // vtable set by compiler
    name = NULL;
    unknown10 = NULL;
    manager = NULL;
}

// Copy constructor - 0x10001860
gbResource::gbResource(const gbResource& other) : gbRefObject(other) {
    name = other.name;
    nameCrc = other.nameCrc;
    unknown10 = other.unknown10;
    manager = other.manager;
    // vtable updated by compiler
}

// Destructor - 0x100200d0
gbResource::~gbResource() {
    // Remove from manager if attached
    if (manager != NULL) {
        int count = *((int*)manager + 2); // manager->count at +8
        for (int i = 0; i < count; i++) {
            gbResource** array = *(gbResource***)manager;
            if (array[i] == this) {
                // Remove this resource
                manager = NULL;
                count--;

                // Shift last element to fill gap
                if (i < count) {
                    array[i] = array[count];
                }

                // Update count
                *((int*)manager + 2) = count;
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
        unknown10 = other.unknown10;
        manager = other.manager;
    }
    return *this;
}


/* ======== gbResManager ======== */

class gbResManager {
public:
    gbResource** array;  // +0x00
    int capacity;        // +0x04
    int count;           // +0x08

    gbResManager();
    gbResManager(const gbResManager& other);
    ~gbResManager();

    void AddResource(gbResource* res);
    void DelResource(gbResource* res);
    gbResource* FindResByName(const char* name);
    void CleanAllResource();

    gbResManager& operator=(const gbResManager& other);
};

// Constructor - 0x10020190
gbResManager::gbResManager() {
    array = NULL;
    capacity = 0;
    count = 0;
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
