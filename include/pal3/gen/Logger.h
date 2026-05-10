#pragma once
// Auto-generated: Logger

class Logger {
public:
    int Render(); // 0x0053C990
    int RegisterCallback(int pfn, char *name, char *desc); // 0x0053CC10
    char * Write(char *fmt, ...); // 0x0053CC70
    int RegisterCallbacks(); // 0x0053CE90
    char * FormatException(char *msg, char *file, int line); // 0x0053CEF0
};
