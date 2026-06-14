#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_QCYM.h"

// Unnamed globals (extern)
extern char byte_A00630;
extern void * off_5AE380;

// 0x004568C0
int UITitle_QCYM::OnMsgSaveData(unsigned int uMsg, unsigned int wParam, int lParam)
{
  int v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // ecx
  unsigned int v10; // eax
  CScreenMode *Instance; // eax
  const void *v12; // [esp-0x8] [ebp-0xC]

  if ( uMsg == 1000 )
  {
    if ( wParam )
    {
      ((TaskBookUI *)this)->SaveData();
      ((TaskBookUI *)this)->_TaskBookUI_6220();
      *((_DWORD *)this + 32590) = 0;
    }
    return 1;
  }
  if ( uMsg == 1001 )
  {
    if ( wParam == 209 )
    {
      v12 = off_5AE380;
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v12, 1);
      ((ChoseCompose *)*((ChoseCompose **)this + 33275))->Init(0);
      return 1;
    }
    v10 = wParam - 209 - (_DWORD)&byte_A00630;
    if ( !v10 )
    {
      ((TaskBookUI *)this)->ScrollUp(1);
      return 1;
    }
    if ( v10 == 1 )
    {
      ((TaskBookUI *)this)->ScrollDown(1);
      return 1;
    }
    return 1;
  }
  if ( uMsg != 1019 )
    return ((PalScript *)this)->OnMessage(uMsg, wParam, lParam);
  if ( (ARC_PlayerAtt *)wParam == &g_PlayerAttBuffer2 )
  {
    v6 = (__int64)*((float *)this + 32573);
    v7 = *((_DWORD *)this + 32583);
    if ( v6 <= v7 )
    {
      if ( v6 < v7 && v6 <= (*((_DWORD *)this + 32584) - 1) * *((_DWORD *)this + 32585) )
      {
        ((TaskBookUI *)this)->ScrollDown(0);
        v9 = *((_DWORD *)this + 32584);
        *((_DWORD *)this + 32583) = v6;
        *((_DWORD *)this + 32584) = v9 - 1;
        if ( v9 - 1 <= 1 )
          *((_DWORD *)this + 32584) = 1;
      }
    }
    else if ( v6 >= *((_DWORD *)this + 32584) * *((_DWORD *)this + 32585) )
    {
      ((TaskBookUI *)this)->ScrollUp(0);
      v8 = *((_DWORD *)this + 32584);
      *((_DWORD *)this + 32583) = v6;
      *((_DWORD *)this + 32584) = v8 + 1;
      if ( v8 + 1 > 36 )
      {
        *((_DWORD *)this + 32584) = 36;
        return 1;
      }
    }
  }
  return 1;
}

// 0x00529BE0
int UITitle_QCYM::HandleDeviceLostC()
{
  PAL3 *Instance_db10; // eax
  PAL3 *v3; // ecx
  float m_snaph; // ecx
  int v5; // eax
  PAL3 *v6; // eax
  int result; // eax
  PAL3 *v8; // ecx
  unsigned __int8 v9; // bl
  PAL3 *v10; // ecx
  PAL3 *v11; // eax
  PAL3 *v12; // ecx
  PAL3 *v13; // eax

  Instance_db10 = ((PAL3 *)this)->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->OnDeviceLost(1);
  m_snaph = ((PAL3 *)v3)->GetInstance_db10()->m_snaph;
  v5 = 1061158912;
  if ( m_snaph != 0.0 )
    v5 = 1065353216;
  this->m_btn[2].m_texarray.m_ptex[11] = (gbTexture *)v5;
  this->m_btn[2].m_texarray.m_ptex[10] = (gbTexture *)v5;
  v6 = ((PAL3 *)LODWORD(m_snaph))->GetInstance_db10();
  LOBYTE(result) = ((RenderTarget *)v6)->OnResetDevice(1);
  if ( (_BYTE)result )
  {
    v9 = g_bGameFlag2;
    g_bGameFlag2 = 0;
    ((PAL3 *)v8)->Render();
    g_bGameFlag2 = v9;
    v11 = ((PAL3 *)v10)->GetInstance_db10();
    ((RenderTarget *)v11)->RenderToScreen();
    this->m_btn[2].m_texarray.m_ptex[9] = 0;
    v13 = ((PAL3 *)v12)->GetInstance_db10();
    result = (int)((RenderTarget *)v13)->GetActiveTexture();
    if ( result )
    {
      if ( *(_DWORD *)(result + 84) )
        this->m_btn[2].m_texarray.m_ptex[9] = (gbTexture *)result;
    }
  }
  else
  {
    this->m_btn[2].m_texarray.m_ptex[9] = 0;
  }
  return result;
}
