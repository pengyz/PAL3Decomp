#pragma once
// Auto-generated: PalScript

#include "PtrArray.h"

class scScriptInstance;

class PalScript {
public:
    unsigned char m_bLoadSceneScript; // +0x0
    scScriptInstance * m_pinst; // +0x4
    PtrArray m_waitobj; // +0x8
    PtrArray m_CamObj; // +0x18
    // total size: 0x28 (40)

    int LoadScript(int pathAddr); // 0x00430290
    char * SetAppName(char *name); // 0x00430570
    void * LoadFromFile(char *filename); // 0x004318B0
    int SetDirectory(char *dir); // 0x004319F0
    int HasNext(); // 0x00431A60
    int LoadNext(); // 0x00431B60
    PalScript(); // 0x00431D80
    static int AddWaitObj(); // 0x00431F00
    static int AddCamObj(int a1); // 0x00431F10
    static void ClearAllCamObj(); // 0x00431F40
    int ClearAllWaitObj(); // 0x00431FA0
    int Update(); // 0x00431FB0
    static char * GetString(); // 0x00434C00
    int Reset(); // 0x0043A250
    struct gbVFileSystem * OpenScript(const char *a2, char a3); // 0x0043AA00
};
