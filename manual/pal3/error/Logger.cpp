#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/Logger.h"
#include "GameBase/GRPinput.h"
#include "Scene/SceneMgr.h"
#include "Misc/tagLoggerCallback.h"
#include "free_functions.h"

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
    p_m_nRenderState = (int *)&this->m_nRenderState;
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

// 0x0053CB10
int Logger::WinProc_HWND_InputLine(char pData)
{
  int result; // eax
  unsigned int v4; // ecx
  char *m_szCmdBuf; // ebx
  int v6; // ecx

  if ( pData == 96 )
  {
    result = this->m_nRenderMode == 0;
    this->m_nRenderMode = result;
  }
  else
  {
    result = this->m_nRenderMode;
    if ( result )
    {
      switch ( pData )
      {
        case 8:
          result = 0;
          v6 = strlen(this->m_szCmdBuf);
          if ( v6 >= 2 )
          {
            *((_BYTE *)&this->m_szCmdBuf2 + v6 + 3) = 0;
            *((_BYTE *)&this->m_szCmdBuf2 + v6 + 2) = 95;
          }
          break;
        case 13:
          m_szCmdBuf = this->m_szCmdBuf;
          *((_BYTE *)&this->m_szCmdBuf2 + strlen(this->m_szCmdBuf) + 3) = 0;
          this->Logger::Write();
          this->Logger::WinProc_HWND_ExecCommand();
          result = 0;
          memset(m_szCmdBuf, 0, 0x64u);
          *m_szCmdBuf = 95;
          break;
        case 27:
          result = 0;
          memset(this->m_szCmdBuf, 0, sizeof(this->m_szCmdBuf));
          this->m_szCmdBuf[0] = 95;
          break;
        default:
          result = 0;
          v4 = strlen(this->m_szCmdBuf);
          if ( v4 < 0x63 )
          {
            *((_BYTE *)&this->m_szCmdBuf2 + v4 + 3) = pData;
            this->m_szCmdBuf[v4] = 95;
          }
          break;
      }
    }
  }
  return result;
}

// 0x0053CC10
int Logger::RegisterCallback(void (*f)(), char *name, char *desc)
{
  int result; // eax
  tagLoggerCallback *v6; // edi

  if ( this->m_nCallbackCount >= 34 )
    return (int)this->Logger::Write();
  v6 = (tagLoggerCallback *)&this->m_callbacks[this->m_nCallbackCount];
  v6->pfn = (int *)f;
  strncpy(v6->szName, name, 0x20u);
  strncpy(v6->szDesc, desc, 0x64u);
  result = this->m_nCallbackCount + 1;
  this->m_nCallbackCount = result;
  return result;
}

// 0x0053CC70
char *Logger::Write(char *fmt)
{
  char *result; // eax
  char *Format; // [esp+0x18] [ebp+0x8]
  char ArgList; // [esp+0x1C] [ebp+0xC] BYREF

  vsprintf(Source, Format, &ArgList);
  memcpy(fmt + 4756, fmt + 4856, 0x640u);
  strncpy(fmt + 6356, Source, 0x63u);
  result = 0;
  if ( (int)(strlen(Source) - 99) > 0 )
  {
    memcpy(fmt + 4756, fmt + 4856, 0x640u);
    return strncpy(fmt + 6356, byte_17B1D23, 0x63u);
  }
  return result;
}

// 0x0053CCF0
char * Logger::WinProc_HWND_ExecCommand()
{
  char *result; // eax
  char *v3; // eax
  char *v4; // ebp
  int v5; // esi
  tagLoggerCallback *i; // edi
  char Str[100]; // [esp+0x10] [ebp-0x64] BYREF

  if ( this->m_nRenderCount )
  {
    strcpy((char *)Str, this->m_szCmdBuf);
    v3 = strchr(Str, 32);
    v4 = (char *)v3;
    if ( v3 )
    {
      *v3 = 0;
      v4 = (char *)(v3 + 1);
    }
    v5 = 0;
    if ( this->m_nCallbackCount <= 0 )
    {
      return this->Logger::Write();
    }
    else
    {
      for ( i = this->m_callbacks; _strcmpi(i->szName, Str); ++i )
      {
        if ( ++v5 >= this->m_nCallbackCount )
          return this->Logger::Write();
      }
      return (char *)((int ( *)(char *))this->m_callbacks[v5].pfn)(v4);
    }
  }
  else
  {
    result = (char *)gbCrc32Compute(this->m_szCmdBuf);
    this->m_nRenderCount = result + 706426632 == 0;
  }
  return result;
}

// 0x0053CDE0
int Logger::WinProc_HWND_SetAndExec(char *Source)
{
  char *m_szCmdBuf; // esi
  int result; // eax

  m_szCmdBuf = this->m_szCmdBuf;
  strncpy(this->m_szCmdBuf, Source, 0x64u);
  this->Logger::WinProc_HWND_ExecCommand();
  result = 0;
  memset(m_szCmdBuf, 0, 0x64u);
  *m_szCmdBuf = 95;
  return result;
}

// 0x0053CE20
char * Logger::WriteRoleNames(char *pszBuf)
{
  char *result; // eax
  int i; // esi

  result = (char *)pszBuf;
  if ( !pszBuf )
  {
    for ( i = 0; i < 20; i += 4 )
      result = (((Logger *)&g_InputState))->Logger::Write();
  }
  return result;
}

// 0x0053CE90
int Logger::RegisterCallbacks()
{
  this->Logger::RegisterCallback((void (*)())SceneMgr::ClearInactiveRoles, (char *)&dword_608940, desc);
  return this->Logger::RegisterCallback((void (*)())Logger::WriteRoleNames, "FV", byte_608930);
}

// 0x0053CEF0
char * Logger::FormatException(char *msg, char *file, int line)
{
  this->m_callbacks[7].szDesc[35] = 0;
  _snprintf((char *const)this, 0x400u, "%s(%d):%s", file, line, msg);
  LogMessage("_Exception: %s\r\n", (const char *)this);
  return (char *)this;
}
