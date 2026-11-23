#ifndef T
#define T
typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;
typedef unsigned long long _QWORD;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef void code;
typedef struct Vec3 {
  float x;
  float y;
  float z;
} Vec3;
typedef struct Complex {
  _DWORD id;
  _DWORD pos;
  _BYTE _pad8[8];
  _BYTE fval[4];
  _DWORD name;
  _BYTE _tail[12];
} Complex;
typedef struct Derived {
  _BYTE _pad0[12];
  _DWORD m_complex;
  _BYTE _pad16[32];
  void *m_pNext;
  _DWORD m_flags;
  _BYTE _tail[4];
} Derived;
typedef struct Base {
  _BYTE _pad0[8];
  _DWORD m_baseVal;
  _BYTE _tail[4];
} Base;
#endif