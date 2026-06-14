#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/Logger.h"

int crt_sub_00540070(void); // from annotations
int crt_sub_00540FD0(void); // from annotations

// Unnamed globals (extern)
extern char byte_17B1D23[413];
extern char dword_608930[];
extern char dword_608940[];

// 0x0053C990
int Logger::Render()
{
  int v2; // ebp
  int *p_m_nRenderState; // ebx
  int result; // eax
  _BYTE v5[4]; // [esp+0x8] [ebp-0x14] BYREF
  _BYTE v6[4]; // [esp+0xC] [ebp-0x10] BYREF
  int v7; // [esp+0x18] [ebp-0x4]

  v2 = 0;
  if ( this->m_nRenderMode && this->m_nRenderCount )
  {
    PushMatrixStacks(v6);
    v7 = 0;
    crt_sub_00540070();
    if ( gbColorQuad::ColorQuadFmt )
      qmemcpy(v5, "\ndd", 3);
    else
      qmemcpy(v5, "dd\n", 3);
    v5[3] = 0x80;
    crt_sub_00540070();
    crt_sub_00540FD0();
    crt_sub_00540FD0();
    p_m_nRenderState = &this->m_nRenderState;
    do
    {
      if ( strlen((const char *)p_m_nRenderState) )
        crt_sub_00540FD0();
      v2 += 16;
      p_m_nRenderState += 25;
    }
    while ( v2 < 272 );
    v7 = -1;
    return PopMatrixStacks(v6);
  }
  return result;
}

// 0x0053CC10
int Logger::RegisterCallback(void (*f)(), char *name, char *desc)
{
  int result; // eax
  tagLoggerCallback *v6; // edi
  char v7; // [esp+0x0] [ebp-0x4]

  if ( this->m_nCallbackCount >= 34 )
    return ((Logger *)this)->Write("CONSOLE error:Command buffer full.", v7);
  v6 = &this->m_callbacks[this->m_nCallbackCount];
  v6->pfn = (int *)f;
  strncpy(v6->szName, name, 0x20u);
  strncpy(v6->szDesc, desc, 0x64u);
  result = this->m_nCallbackCount + 1;
  this->m_nCallbackCount = result;
  return result;
}

// 0x0053CC70
char *Logger::Write(char *Format, ...)
{
  char *result; // eax
  va_list va; // [esp+0x1C] [ebp+0xC] BYREF

  va_start(va, Format);
  vsprintf(Source, Format, va);
  memcpy(a1 + 4756, a1 + 4856, 0x640u);
  strncpy(a1 + 6356, Source, 0x63u);
  result = 0;
  if ( (int)(strlen(Source) - 99) > 0 )
  {
    memcpy(a1 + 4756, a1 + 4856, 0x640u);
    return strncpy(a1 + 6356, byte_17B1D23, 0x63u);
  }
  return result;
}

// 0x0053CE20
char * Logger::WriteRoleNames()
{
  char *result; // eax
  int i; // esi
  char ArgList[4]; // [esp+0x4] [ebp-0x14]
  char *v4; // [esp+0x8] [ebp-0x10]
  char *v5; // [esp+0xC] [ebp-0xC]
  char *v6; // [esp+0x10] [ebp-0x8]
  char *v7; // [esp+0x14] [ebp-0x4]

  result = pszBuf;
  *(_DWORD *)ArgList = "Xuejian";
  v4 = "Longkui";
  v5 = "Zixuan";
  v6 = "Changqing";
  v7 = "HuaYing";
  if ( !pszBuf )
  {
    for ( i = 0; i < 5; ++i )
      result = ((Logger *)&g_InputState)->Write("%s = %d", *(const char **)&ArgList[i * 4], g_nRoleInitLevel[i + 1]);
  }
  return result;
}

// 0x0053CE90
int Logger::RegisterCallbacks()
{
  this->RegisterCallback((void (*)())SceneMgr::ClearInactiveRoles, dword_608940, desc);
  return this->RegisterCallback((void (*)())Logger::WriteRoleNames, "FV", dword_608930);
}

// 0x0053CEF0
char * Logger::FormatException(char *msg, char *file, int line)
{
  this->m_callbacks[7].szDesc[35] = 0;
  _snprintf((char *const)this, 0x400u, "%s(%d):%s", file, line, msg);
  LogMessage("_Exception: %s\r\n", (const char *)this);
  return (char *)this;
}
