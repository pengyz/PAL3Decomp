#pragma once
// Auto-generated from IDA decomp - Logger
// 5 methods

class Logger {
public:
    int Render();  // 0x0053C990
    int RegisterCallback(int pfn, char *name, char *desc);  // 0x0053CC10
    static char *(void *this, char *fmt, ...) Write();  // 0x0053CC70
    int RegisterCallbacks();  // 0x0053CE90
    static char *__thiscall(char *this, char *msg, char *file, int line) FormatException();  // 0x0053CEF0
};
