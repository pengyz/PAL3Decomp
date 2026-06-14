#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/RoleCameraCtrl.h"

// Forward declarations for unnamed functions
int sub_445D20(_DWORD *_this, int a2, int a3); // from annotations

// 0x00445860
void RoleCameraCtrl::SetName(const char *pszName)
{
  float *p_z; // ebp
  unsigned int v3; // kr04_4
  unsigned int v4; // ebx
  int v5; // ecx
  char v6; // al
  unsigned int v7; // eax
  int v8; // ecx

  p_z = &this->m_startfrom.z;
  v3 = strlen(pszName) + 1;
  v4 = v3 - 1;
  if ( v3 - 1 > 0xFFFFFFFD )
// [IDA_MISID]     std::_Xlen();
  v5 = *((_DWORD *)p_z + 1);
  if ( v5 )
  {
    v6 = *(_BYTE *)(v5 - 1);
    if ( v6 )
    {
      if ( v6 != -1 )
      {
        if ( v3 == 1 )
        {
          *(_BYTE *)(v5 - 1) = v6 - 1;
          p_z[1] = 0.0;
          p_z[2] = 0.0;
          p_z[3] = 0.0;
          return;
        }
        goto LABEL_13;
      }
    }
  }
  if ( v3 == 1 )
  {
    ((std *)1)->string::_Tidy();
    return;
  }
  v7 = *((_DWORD *)p_z + 3);
  if ( v7 > 0x1F || v7 < v4 )
  {
    ((std *)1)->string::_Tidy();
LABEL_13:
    ((GRPinput *)p_z)->PollInputState(v4);
  }
  qmemcpy(*((void **)p_z + 1), pszName, v4);
  v8 = *((_DWORD *)p_z + 1);
  *((_DWORD *)p_z + 2) = v4;
  *(_BYTE *)(v8 + v4) = 0;
}

// 0x00445910
int RoleCameraCtrl::SetTargetDistance(int nVal)
{
  *((_DWORD *)this + 45) = nVal;
  return nVal;
}

// 0x00450A60
RoleCameraCtrl * RoleCameraCtrl::InitFrameUI()
{
  ((UITextArea *)&this->m_startfrom.z)->InitAfterClear();
  return this;
}

// 0x00450AB0
RoleCameraCtrl * RoleCameraCtrl::_sdtor_26(RoleCameraCtrl *Block, char a2)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00450AD0
void RoleCameraCtrl::InitBaseWidget()
{
  ((UITextArea *)&this->m_startfrom.z)->Destroy();
  ((UIWnd *)this)->Destroy();
}

// 0x00450C60
int RoleCameraCtrl::OnMessage(int nVal, int nVal2, int nVal3)
{
  if ( nVal == 1000 )
    *((_DWORD *)this + 66) = 0;
  return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
}

// 0x00450C90
BOOL RoleCameraCtrl::UpdatePosition(int nVal, int nVal2)
{
  double v5; // st7
  void ( **vftable)(RoleCameraCtrl *, _DWORD); // eax

  if ( !LODWORD(this->m_targetfrom.y) )
    return 0;
  if ( !LODWORD(this->m_targetfrom.z) )
    return 0;
  if ( *((_DWORD *)this + 61) == 2 )
  {
    v5 = *(float *)&nVal + *((float *)this + 66);
    *((float *)this + 66) = v5;
    if ( v5 > 4.0 )
    {
// [VFTABLE] vftable = (void ( **)(RoleCameraCtrl *, _DWORD))this->__vftable;
      *((_DWORD *)this + 66) = 0;
      (*vftable)(this, 0);
    }
  }
  return ((UIFrameWnd *)this)->Update_bbc0(nVal, nVal2);
}

// 0x00450D00
void RoleCameraCtrl::ShowWindow()
{
  void ( **vftable)(int, float, _DWORD); // eax
  int i; // edi
  void ( ***v4)(_DWORD, float); // ecx
  float v5; // [esp+0x10] [ebp+0x4]

  if ( LODWORD(this->m_targetfrom.x) )
  {
    if ( LODWORD(this->m_targetfrom.y) != LODWORD(v5) )
    {
// [VFTABLE] vftable = (void ( **)(int, float, _DWORD))this->__vftable;
      this->m_targetfrom.y = v5;
      vftable[6](1000, COERCE_FLOAT(LODWORD(v5)), 0);
      for ( i = 0; i < SLODWORD(this->m_startyaw); ++i )
      {
        v4 = *(void ( ****)(_DWORD, float))(LODWORD(this->m_targetyaw) + 4 * i);
        (**v4)(v4, COERCE_FLOAT(LODWORD(v5)));
      }
    }
  }
}

// 0x0051BB50
int RoleCameraCtrl::InitViewSlots()
{
  float *p_z; // esi
  int v2; // edi
  int result; // eax

  p_z = &this->m_startfrom.z;
  v2 = 5;
  do
  {
    result = sub_445D20(
               *((_DWORD **)p_z + 6),
               g_nUnkTable_24C[*(_DWORD *)p_z] + 9,
               g_nUnkTable_268[*(_DWORD *)p_z] + 232);
    ++p_z;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x0052DFF0
int RoleCameraCtrl::SetViewPosition(int nVal, int nVal2, int nVal3, char pData)
{
  double v6; // st7
  void *m_pVtable; // ecx
  double v8; // st7
  double v9; // st7
  gbVec3D v11; // [esp+0x4] [ebp-0xC] BYREF
  float nVala; // [esp+0x14] [ebp+0x4]
  float nVal2a; // [esp+0x18] [ebp+0x8]
  float nVal3a; // [esp+0x1C] [ebp+0xC]

  this->m_needscriptdel = (gbImage2D *)nVal;
  this->m_pVtable = (void *)nVal2;
  *(_DWORD *)&this->m_type = nVal3;
  if ( pData )
  {
    v6 = this->m_startfrom.x + *(float *)&this->m_type;
    m_pVtable = this->m_pVtable;
    LODWORD(this->m_time) = this->m_needscriptdel;
    LODWORD(this->m_passtime) = m_pVtable;
    this->m_itype = v6;
  }
  nVala = this->m_time - *(float *)&this->m_needscriptdel;
  v8 = this->m_passtime - *(float *)&this->m_pVtable;
  v11.x = nVala;
  nVal2a = v8;
  v9 = this->m_itype - *(float *)&this->m_type;
  v11.y = nVal2a;
  nVal3a = v9;
  v11.z = nVal3a;
  this->m_startfrom.x = ((gbVec3D *)&v11)->Length();
  return ((UIScene *)this)->CalcViewTransform(1);
}

// 0x0052E080
int RoleCameraCtrl::ComputeViewVector(int nVal, int nVal2, int nVal3)
{
  double v5; // st7
  double v6; // st7
  gbVec3D v8; // [esp+0x4] [ebp-0xC] BYREF
  float nVala; // [esp+0x14] [ebp+0x4]
  float nVal2a; // [esp+0x18] [ebp+0x8]
  float nVal3a; // [esp+0x1C] [ebp+0xC]

  LODWORD(this->m_time) = nVal;
  LODWORD(this->m_passtime) = nVal2;
  LODWORD(this->m_itype) = nVal3;
  nVala = this->m_time - *(float *)&this->m_needscriptdel;
  v5 = this->m_passtime - *(float *)&this->m_pVtable;
  v8.x = nVala;
  nVal2a = v5;
  v6 = this->m_itype - *(float *)&this->m_type;
  v8.y = nVal2a;
  nVal3a = v6;
  v8.z = nVal3a;
  this->m_startfrom.x = ((gbVec3D *)&v8)->Length();
  return ((UIScene *)this)->CalcViewTransform(1);
}
