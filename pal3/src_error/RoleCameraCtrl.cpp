// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/RoleCameraCtrl.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIScene.h"
#include "Misc/UITextArea.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

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

  p_z = (float *)&this->m_startfrom.z;
  v3 = strlen(pszName) + 1;
  v4 = v3 - 1;
  if ( v3 - 1 > 0xFFFFFFFD )
    std::_Xlen();
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
    (((std::string *)1))->_Tidy();
    return;
  }
  v7 = *((_DWORD *)p_z + 3);
  if ( v7 > 0x1F || v7 < v4 )
  {
    (((std::string *)1))->_Tidy();
LABEL_13:
    (((GRPinput *)p_z))->GRPinput::PollInputState(v4);
  }
  qmemcpy(*((void **)p_z + 1), pszName, v4);
  v8 = *((_DWORD *)p_z + 1);
  *((_DWORD *)p_z + 2) = v4;
  *(_BYTE *)(v8 + v4) = 0;
}

// 0x00445910
int RoleCameraCtrl::SetTargetDistance(int nVal)
{
  int result; // eax

  result = nVal;
  LODWORD(this[2].m_targetdist) = nVal;
  return result;
}

// 0x00450A25
RoleCameraCtrl::~RoleCameraCtrl()
{
  accessor_00450A30();
}

// 0x00450A60
RoleCameraCtrl * RoleCameraCtrl::InitFrameUI()
{
  ((UIFrameWnd *)this)->UIFrameWnd::UIFrameWnd();
  (((UITextArea *)&this->m_startfrom.z))->UITextArea::InitAfterClear();
  return this;
}

// 0x00450AD0
void RoleCameraCtrl::InitBaseWidget()
{
  UITextArea_Destroy();
  (((UIFrameWnd *)this))->UIFrameWnd::UIFrameWnd();
}

// 0x00450C60
int RoleCameraCtrl::OnMessage(int nVal, int nVal2, int nVal3)
{
  if ( nVal == 1000 )
    this[3].m_targetyaw = 0.0f;
  return (((UIWnd *)this))->UIWnd::OnMessage(nVal, nVal2, nVal3) /* [ROWTABLE] */;
}

// 0x00450C90
BOOL RoleCameraCtrl::UpdatePosition(int nVal, int nVal2)
{
  float v5; // st7
  void ( **m_nTodo_000)(RoleCameraCtrl *, _DWORD); // eax

  if ( !LODWORD(this->m_targetfrom.y) )
    return 0;
  if ( !LODWORD(this->m_targetfrom.z) )
    return 0;
  if ( LODWORD(this[3].m_time) == 2 )
  {
    v5 = *(float *)&nVal + this[3].m_targetyaw;
    this[3].m_targetyaw = v5;
    if ( v5 > 4.0f )
    {
      m_nTodo_000 = (void ( **)(RoleCameraCtrl *, _DWORD))this->m_nTodo_000;
      this[3].m_targetyaw = 0.0f;
      (*m_nTodo_000)(this, 0);
    }
  }
  return (((UIFrameWnd *)this))->UIFrameWnd::Update_bbc0(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x00450D00
void RoleCameraCtrl::ShowWindow(int a1)
{
  void ( **m_nTodo_000)(int, int, _DWORD); // eax
  int i; // edi
  void ( ***v5)(_DWORD, int); // ecx

  if ( LODWORD(this->m_targetfrom.x) )
  {
    if ( LODWORD(this->m_targetfrom.y) != a1 )
    {
      m_nTodo_000 = (void ( **)(int, int, _DWORD))this->m_nTodo_000;
      LODWORD(this->m_targetfrom.y) = a1;
      m_nTodo_000[6](1000, a1, 0);
      for ( i = 0; i < SLODWORD(this->m_startyaw); ++i )
      {
        v5 = *(void ( ****)(_DWORD, int))(LODWORD(this->m_targetyaw) + 4 * i);
        (**v5)((_DWORD)((_DWORD)(v5)), (int)(a1));
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

  p_z = (float *)&this->m_startfrom.z;
  v2 = 5;
  do
  {
    result = MoveToAbsolute(
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
  float v6; // st7
  float v7; // ecx
  float v8; // st7
  float v9; // st7
  gbVec3D v11; // [esp+0x4] [ebp-0xC] BYREF
  float nVala; // [esp+0x14] [ebp+0x4]
  float nVal2a; // [esp+0x18] [ebp+0x8]
  float nVal3a; // [esp+0x1C] [ebp+0xC]

  this->m_needscriptdel = ((gbImage2D *)((gbImage2D *)nVal));
  this->m_pVtable_i = nVal2;
  *(_DWORD *)&this->m_type = nVal3;
  if ( pData )
  {
    v6 = this->m_startfrom.x + *(float *)&this->m_type;
    v7 = *(float *)&this->m_pVtable_i;
    LODWORD(this->m_time) = this->m_needscriptdel;
    this->m_passtime = v7;
    this->m_itype = v6;
  }
  nVala = this->m_time - *(float *)&this->m_needscriptdel;
  v8 = this->m_passtime - *(float *)&this->m_pVtable_i;
  v11.x = nVala;
  nVal2a = v8;
  v9 = this->m_itype - *(float *)&this->m_type;
  v11.y = nVal2a;
  nVal3a = v9;
  v11.z = nVal3a;
  this->m_startfrom.x = (((gbVec3D *)&v11))->gbVec3D::Length();
  return (((UIScene *)this))->UIScene::CalcViewTransform(1) /* [ROWTABLE] */;
}

// 0x0052E080
int RoleCameraCtrl::ComputeViewVector(int nVal, int nVal2, int nVal3)
{
  float v5; // st7
  float v6; // st7
  gbVec3D v8; // [esp+0x4] [ebp-0xC] BYREF
  float nVala; // [esp+0x14] [ebp+0x4]
  float nVal2a; // [esp+0x18] [ebp+0x8]
  float nVal3a; // [esp+0x1C] [ebp+0xC]

  LODWORD(this->m_time) = nVal;
  LODWORD(this->m_passtime) = nVal2;
  LODWORD(this->m_itype) = nVal3;
  nVala = this->m_time - *(float *)&this->m_needscriptdel;
  v5 = this->m_passtime - *(float *)&this->m_pVtable_i;
  v8.x = nVala;
  nVal2a = v5;
  v6 = this->m_itype - *(float *)&this->m_type;
  v8.y = nVal2a;
  nVal3a = v6;
  v8.z = nVal3a;
  this->m_startfrom.x = (((gbVec3D *)&v8))->gbVec3D::Length();
  return (((UIScene *)this))->UIScene::CalcViewTransform(1) /* [ROWTABLE] */;
}
