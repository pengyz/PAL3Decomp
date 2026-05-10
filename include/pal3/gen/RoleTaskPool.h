#pragma once
// Auto-generated: RoleTaskPool

#include "TxtFile.h"

class RoleTaskPool {
public:
    char m_TaskData[16]; // +0x0 (std::vector<RoleTask,std::allocator<RoleTask> >)
    char m_TaskLine[16]; // +0x10 (std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >)
    TxtFile m_taskFile; // +0x20
    char _TaskPicFolder[128]; // +0x22C
    // total size: 0x2AC (684)

};
