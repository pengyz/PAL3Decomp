#pragma once

class gbResource;

class gbResManager {
public:
    gbResource** array;  // +0x00: resource array
    int capacity;        // +0x04: array capacity
    int count;           // +0x08: current resource count

    gbResManager();
    gbResManager(const gbResManager& other);
    ~gbResManager();
    gbResManager& operator=(const gbResManager& other);
    void AddResource(gbResource* res);
    void DelResource(gbResource* res);
    gbResource* FindResByName(const char* name);
    void CleanAllResource(void);
};
