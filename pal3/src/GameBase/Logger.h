#pragma once
// Auto-generated: Logger

#include "tagLoggerCallback.h"

class Logger {
public:
    int m_nCallbackCount; // +0x0
    tagLoggerCallback m_callbacks[34]; // +0x4
    char _gap_08C[4488]; // +0x8C
    int m_nRenderX; // +0x1214
    int m_nRenderY; // +0x1218
    int m_bRenderEnabled; // +0x121C
    void * m_pRenderTarget; // +0x1220
    int m_nRenderMode; // +0x1224
    int m_nRenderCount; // +0x1228
    void * _todo_122C; // +0x122C
    void * _todo_1230; // +0x1230
    char _gap_1234[96]; // +0x1234
    int m_nRenderState; // +0x1294
    char _gap_1298[96]; // +0x1298
    void * _todo_12F8; // +0x12F8
    char _tail_12FC[1500]; // +0x12FC
    // total size: 0x18D8 (6360)

    int Render(); // 0x0053C990
    int RegisterCallback(void (*f)(), char *name, char *desc); // 0x0053CC10
    static char * Write(char *a1, char *Format, ...); // 0x0053CC70
    static char * WriteRoleNames(char *pszBuf); // 0x0053CE20
    int RegisterCallbacks(); // 0x0053CE90
    char * FormatException(char *msg, char *file, int line); // 0x0053CEF0
};
