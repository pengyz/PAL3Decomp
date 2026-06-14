#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PalScriptIdleObj.h"

// 0x0044A970
gbVFileSystem * PalScriptIdleObj::LoadScriptTexture(int nTexID, int nParam)
{
  gbTexture *v4; // eax
  int v5; // ecx
  int v6; // edx
  void ( **vftable)(PalScriptIdleObj *, int); // eax
  gbVFileSystem *result; // eax
  OpenBaseFile v9; // [esp+0xC] [ebp-0x10] BYREF
  int v10; // [esp+0x18] [ebp-0x4]

// [VFTABLE] (*((void ( **)(PalScriptIdleObj *))this->__vftable + 3))(this);
  *((_DWORD *)this + 21) = 42;
  *((_DWORD *)this + 20) = nParam;
  v10 = 0;
  v4 = (gbTexture *)(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr + 8))(gfxMgr, nTexID);
  *((_DWORD *)this + 19) = v4;
  ((gbTexture *)v4)->LoadTexture(1);
  v5 = *((_DWORD *)this + 19);
  v6 = *((_DWORD *)this + 5);
  *((_DWORD *)this + 23) = 0;
  *((_DWORD *)this + 22) = 0;
// [VFTABLE] vftable = (void ( **)(PalScriptIdleObj *, int))this->__vftable;
  *((_DWORD *)this + 7) = *(_DWORD *)(v5 + 28) + v6;
  (*vftable)(this, 1);
  v10 = -1;
  return result;
}

// 0x00453C00
int PalScriptIdleObj::UpdateWait(const void *pData, unsigned int dwVal)
{
  gbImage2D *m_needscriptdel; // ecx
  char Color_high; // al
  unsigned int m_passedtime_low; // eax
  gbImage2D *v8; // ecx

  if ( dwVal > 0xFFFFFFFD )
// [IDA_MISID]     std::_Xlen();
  m_needscriptdel = this->m_needscriptdel;
  if ( m_needscriptdel )
  {
    Color_high = HIBYTE(m_needscriptdel[-1].ColorKey.Color);
    if ( Color_high )
    {
      if ( Color_high != -1 )
      {
        if ( !dwVal )
        {
          HIBYTE(m_needscriptdel[-1].ColorKey.Color) = Color_high - 1;
          this->m_needscriptdel = 0;
          this->_todo_0 = 0;
          this->m_passedtime = 0.0;
          return (int)this;
        }
        goto LABEL_13;
      }
    }
  }
  if ( !dwVal )
  {
    ((std *)1)->string::_Tidy();
    return (int)this;
  }
  m_passedtime_low = LODWORD(this->m_passedtime);
  if ( m_passedtime_low > 0x1F || m_passedtime_low < dwVal )
  {
    ((std *)1)->string::_Tidy();
LABEL_13:
    ((GRPinput *)this)->PollInputState(dwVal);
  }
  qmemcpy(this->m_needscriptdel, pData, dwVal);
  v8 = this->m_needscriptdel;
  this->_todo_0 = dwVal;
  *((_BYTE *)&v8->ImgInfo.isdiskinfo + dwVal) = 0;
  return (int)this;
}

// 0x00535600
UISceneFrm * PalScriptIdleObj::ResetTimers()
{
  int v2; // ecx
  float *p_m_passedtime; // eax

  v2 = 6;
  p_m_passedtime = &this->m_passedtime;
  do
  {
    *(_BYTE *)p_m_passedtime = 0;
    *((_BYTE *)p_m_passedtime + 256) = 0;
    p_m_passedtime += 128;
    --v2;
  }
  while ( v2 );
  ((UISceneFrm *)this)->InitTemplateStrings();
  return (UISceneFrm *)this;
}
