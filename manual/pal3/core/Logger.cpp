// manual/pal3/core/Logger.cpp - Logger (migrated from codegen)
// Source: pal3/src/GameBase/Logger.cpp
// Semantic equivalence target (ignore register allocation)

#include <windows.h>
#include <string.h>

typedef unsigned char _BYTE;

class Logger {
public:
    int m_nRenderMode;
    int m_nRenderCount;
    int m_nRenderState;
    // [R116 修] 真实布局：szCmdBuf2[104] @ +0x122C, szCmdBuf[100] @ +0x1230（重叠）
    // szCmdBuf == &szCmdBuf2 + 4
    char m_szCmdBuf2[104];  // +0x122C
    char m_szCmdBuf[100];   // +0x1230 (重叠)
    
    int Render();
    int WinProc_HWND_InputLine(char pData);
    char *Write();
    char *WinProc_HWND_ExecCommand();
};

// [N=0] WinProc_HWND_InputLine - codegen migration
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

// Mock implementations (ensure compilability)
char *Logger::Write() { return NULL; }
char *Logger::WinProc_HWND_ExecCommand() { return NULL; }
int Logger::Render() { return 0; }
