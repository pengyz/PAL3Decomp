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
    RefCount = 1;
}

// Copy constructor - 0x100017c0
gbRefObject::gbRefObject(const gbRefObject& other) {
    RefCount = other.RefCount;
}

// Destructor - 0x1002f7e0 (virtual)
gbRefObject::~gbRefObject() {
}

// IncRef - 0x10001600
void gbRefObject::IncRef() {
    RefCount++;
}

// DecRef - 0x10001610
void gbRefObject::DecRef() {
    RefCount--;
}

// GetRef - 0x100017b0
int gbRefObject::GetRef() {
    return RefCount;
}

// Release - 0x1002f7f0
void gbRefObject::Release() {
    RefCount--;
    if (RefCount == 0) {
        // Call virtual destructor through vtable
        // The destructor will delete the object
        delete this;
    }
}

// operator= - 0x10003980
gbRefObject& gbRefObject::operator=(const gbRefObject& other) {
    RefCount = other.RefCount;
    return *this;
}


/* ======== gbResource ======== */

// Constructor - 0x10001840
gbResource::gbResource() : gbRefObject() {
    RefCount = 1;
    // vtable set by compiler
    pName = NULL;
    IsLoaded = NULL;
    pMgr = NULL;
}

// Copy constructor - 0x10001860
gbResource::gbResource(const gbResource& other) : gbRefObject(other) {
    pName = other.pName;
    NameCrc32 = other.NameCrc32;
    IsLoaded = other.IsLoaded;
    pMgr = other.pMgr;
    // vtable updated by compiler
}

// Destructor - 0x100200d0 (191B)
gbResource::~gbResource() {
    if (pMgr) {
        gbResManager* mgr = pMgr;
        int cnt = mgr->count;
        int idx = 0;
        if (cnt > 0) {
            gbResource** p = mgr->array;
            while (*p != this) {
                ++idx;
                ++p;
                if (idx >= cnt)
                    goto done_remove;
            }
            int newCount = cnt - 1;
            pMgr = NULL;
            if (newCount > idx)
                mgr->array[idx] = mgr->array[cnt - 1];
            int newCapacity = cnt - 1;
            if (cnt == 1)
                newCapacity = 16;
            if (newCapacity > mgr->capacity) {
                mgr->capacity = newCapacity;
                gbResource** newArray = (gbResource**)malloc(4 * newCapacity);
                int existCount = mgr->count;
                if (existCount)
                    memcpy(newArray, mgr->array, 4 * existCount);
                if (mgr->array)
                    free(mgr->array);
                mgr->array = newArray;
            }
            mgr->count = newCount;
        }
    }
done_remove:
    if (pName)
        free(pName);

    gbRefObject::~gbRefObject();
}

// SetName - 0x10020040
void gbResource::SetName(const char* newName) {
    // Free old pName
    if (pName != NULL) {
        free(pName);
    }

    // Handle NULL or empty string
    if (newName == NULL || newName[0] == '\0') {
    pName = NULL;
        NameCrc32 = 0;
        return;
    }

    // Calculate string length
    size_t len = strlen(newName) + 1;

    // Minimum allocation size
    size_t allocSize = (len < 16) ? 16 : len;

    // Allocate and copy
    pName = (char*)malloc(allocSize);
    strcpy(pName, newName);

    // Compute CRC32
    NameCrc32 = gbCrc32Compute(newName);
}

// GetName - 0x100039f0
const char* gbResource::GetName() {
    return pName;
}

// GetNameCrc32 - 0x10003cc0
unsigned int gbResource::GetNameCrc32() {
    return NameCrc32;
}

// operator= - 0x100018a0
gbResource& gbResource::operator=(const gbResource& other) {
    gbRefObject::operator=(other);
    pName = other.pName;
    NameCrc32 = other.NameCrc32;
    IsLoaded = other.IsLoaded;
    pMgr = other.pMgr;
    return *this;
}


/* ======== gbResManager ======== */

// Constructor - 0x10020190
gbResManager::gbResManager() {
    capacity = 0;
    count = 0;
    array = NULL;
}

// Copy constructor - 0x100052a0 (79B)
gbResManager::gbResManager(const gbResManager& other) {
    capacity = other.capacity;
    count = other.count;
    if (capacity)
        array = (gbResource**)malloc(4 * capacity);
    else
        array = NULL;
    int usedCount = count;
    if (usedCount)
        memcpy(array, other.array, 4 * usedCount);
}

// Destructor - 0x100201a0
gbResManager::~gbResManager() {
    if (array != NULL) {
        free(array);
    }
}

// AddResource - 0x10020200
void gbResManager::AddResource(gbResource* res) {
    // Set pMgr pointer in resource
    res->pMgr = this;

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

// DelResource - 0x10020280 (147B)
void gbResManager::DelResource(gbResource* res) {
    int idx = 0;
    int cnt = count;
    if (cnt > 0) {
        gbResource** p = array;
        while (*p != res) {
            ++p;
            if (++idx >= cnt)
                return;
        }
        res->pMgr = NULL;
        int newCount = cnt - 1;
        if (cnt - 1 > idx)
            array[idx] = array[cnt - 1];
        int newCapacity = cnt - 1;
        if (cnt == 1)
            newCapacity = 16;
        if (newCapacity > capacity) {
            capacity = newCapacity;
            gbResource** newArray = (gbResource**)malloc(4 * newCapacity);
            int existCount = count;
            if (existCount)
                memcpy(newArray, array, 4 * existCount);
            if (array)
                free(array);
            array = newArray;
        }
        count = newCount;
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
        if (res->NameCrc32 == crc) {
            // Found - increment ref count and return
            res->RefCount++;
            return res;
        }
    }

    return NULL;
}

// CleanAllResource - 0x10020320
void gbResManager::CleanAllResource() {
    while (count != 0) {
        gbResource* res = array[0];

        // Release until RefCount reaches 1
        while (res->RefCount > 1) {
            res->Release();
        }

        // Final release (will delete)
        res->Release();
    }

    count = 0;
}

// operator= - 0x100019b0 (94B)
gbResManager& gbResManager::operator=(const gbResManager& other) {
    if (array)
        free(array);
    int cap = other.capacity;
    capacity = cap;
    count = other.count;
    if (cap)
        array = (gbResource**)malloc(4 * cap);
    else
        array = NULL;
    int usedCount = count;
    if (usedCount)
        memcpy(array, other.array, 4 * usedCount);
    return *this;
}
