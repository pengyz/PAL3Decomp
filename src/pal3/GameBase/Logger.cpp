#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int sub_423500(...);
int sub_53CE20(...);

// Unnamed globals (extern)
extern char aConsoleErrorCo[];
extern char aPal3ConsoleV10[];
extern unsigned char byte_17B1D23;
extern unsigned char byte_608930;

// 0x0053C990
int Logger::Render()
{
  int v2; // ebp
  int v3; // ecx
  int v4; // edx
  int v5; // edx
  int v6; // eax
  const char *v7; // ebx
  int result; // eax
  int v9; // [esp-10h] [ebp-2Ch]
  float v10; // [esp+8h] [ebp-14h] BYREF
  int v11; // [esp+18h] [ebp-4h]

  v2 = 0;
  if ( *((_DWORD *)this + 1161) && *((_DWORD *)this + 1162) )
  {
    PushMatrixStacks();
    v3 = *((_DWORD *)this + 1160);
    v4 = *((_DWORD *)this + 1159);
    v11 = 0;
    ((_TextureLib_Data *)*((_DWORD *)this + 1157))->~_TextureLib_Data(*((_DWORD *)this + 1158), v4, v3, (float *)this + 1163);
    if ( gbColorQuad::ColorQuadFmt )
      qmemcpy(&v10, "\ndd", 3);
    else
      qmemcpy(&v10, "dd\n", 3);
    v5 = *((_DWORD *)this + 1159);
    v9 = *((_DWORD *)this + 1160);
    v6 = *((_DWORD *)this + 1157);
    HIBYTE(v10) = 0x80;
    v6->~_TextureLib_Data(v9 - 18, v5, v9, &v10);
    UIRenderQuad(
      *((_DWORD *)this + 1157) + 4,
      *((_DWORD *)this + 1160) - 17,
      (int)this + 4656,
      (_BYTE *)this + 6456,
      16);
    UIRenderQuad(
      *((_DWORD *)this + 1159) - 224,
      *((_DWORD *)this + 1158) + 4,
      (int)aPal3ConsoleV10,
      (_BYTE *)this + 6456,
      16);
    v7 = (char *)this + 4756;
    do
    {
      if ( strlen(v7) )
        UIRenderQuad(*((_DWORD *)this + 1157) + 4, v2 + *((_DWORD *)this + 1158), (int)v7, (_BYTE *)this + 6456, 16);
      v2 += 16;
      v7 += 100;
    }
    while ( v2 < 272 );
    v11 = -1;
    return (int)PopMatrixStacks();
  }
  return result;
}

// 0x0053CC10
int Logger::RegisterCallback(int pfn, char *name, char *desc)
{
  int result; // eax
  char *v6; // edi

  if ( *(int *)this >= 34 )
    return (int)this->Write(aConsoleErrorCo);
  v6 = (char *)this + 136 * *(_DWORD *)this + 4;
  *((_DWORD *)v6 + 33) = pfn;
  strncpy(v6, name, 0x20u);
  strncpy(v6 + 32, desc, 0x64u);
  result = *(_DWORD *)this + 1;
  *(_DWORD *)this = result;
  return result;
}

// 0x0053CC70
char *Logger::Write(char *fmt, ...)
{
  char *result; // eax
  va_list ArgList; // [esp+1Ch] [ebp+Ch] BYREF

  va_start(ArgList, fmt);
  vsprintf(Source, fmt, ArgList);
  memcpy((char *)this + 4756, (char *)this + 4856, 0x640u);
  strncpy((char *)this + 6356, Source, 0x63u);
  result = 0;
  if ( (int)(strlen(Source) - 99) > 0 )
  {
    memcpy((char *)this + 4756, (char *)this + 4856, 0x640u);
    return strncpy((char *)this + 6356, byte_17B1D23, 0x63u);
  }
  return result;
}

// 0x0053CE90
int Logger::RegisterCallbacks()
{
  this->RegisterCallback((int)sub_423500, name, &desc);
  return this->RegisterCallback((int)sub_53CE20, aFv, &byte_608930);
}

// 0x0053CEF0
char * Logger::FormatException(char *msg, char *file, int line)
{
  *((_BYTE *)this + 1023) = 0;
  _snprintf((char *const)this, 0x400u, "%s(%d):%s", file, line, msg);
  LogMessage("_Exception: %s\r\n", (const char *)this);
  return (char *)this;
}
