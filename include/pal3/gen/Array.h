#pragma once
// Auto-generated from IDA decomp - Array
// 4 methods

class Array {
public:
    static void *__stdcall(void *arr, void *elem, void *end) Insert();  // 0x00411170
    int Size();  // 0x004111C0
    static void *__stdcall(void *arr, int index, void *pConfig) Erase();  // 0x004111E0
    static void *__cdecl(void *dst, void *src) Copy();  // 0x00411240
};
