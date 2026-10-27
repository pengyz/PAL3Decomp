// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/SceneObj.h"
#include "Role/Actor.h"
#include "Combat/CCCTData.h"
#include "GameBase/GRPinput.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Script/PalScript.h"
#include "Misc/PalScriptIdleObj.h"
#include "Misc/PtrArray.h"
#include "Misc/RoleAtt.h"
#include "Misc/String.h"
#include "Misc/UIButton.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "Misc/UIRoleDialog.h"
#include "UI/UIWnd.h"
#include "Misc/s_RoleState.h"
#include "free_functions.h"

// 0x00407B50
char SceneObj::UpdateAutoDelete(unsigned int deltatime)
{
  _BYTE *Color; // eax
  char v4; // cl
  _BYTE *v6; // ecx
  char v7; // al
  unsigned int m_id; // ecx
  _BYTE *v9; // ecx
  char v10; // al
  char v11; // [esp+0x14] [ebp+0x8]

  if ( deltatime > 0xFFFFFFFD )
    std::_Xlen();
  Color = (_BYTE *)this->m_fontcolor.Color;
  if ( Color )
  {
    v4 = *(Color - 1);
    if ( v4 )
    {
      if ( v4 != -1 )
      {
        if ( !deltatime )
        {
          *(Color - 1) = v4 - 1;
          this->m_fontcolor.Color = 0;
          this->m_wndcolor.Color = 0;
          this->m_id = 0;
          return 0;
        }
        goto LABEL_29;
      }
    }
  }
  if ( deltatime )
  {
    if ( !v11 )
    {
      if ( this->m_id >= deltatime )
        return 1;
LABEL_29:
      (((GRPinput *)this))->GRPinput::PollInputState(deltatime);
      return 1;
    }
    m_id = this->m_id;
    if ( m_id <= 0x1F && m_id >= deltatime )
      return 1;
    if ( Color )
    {
      v9 = (_BYTE *)(Color - 1);
      v10 = *(Color - 1);
      if ( v10 && v10 != -1 )
      {
        *v9 = v10 - 1;
        this->m_fontcolor.Color = 0;
        this->m_wndcolor.Color = 0;
        this->m_id = 0;
        (((GRPinput *)this))->GRPinput::PollInputState(deltatime);
        return 1;
      }
      operator delete(v9);
    }
    this->m_fontcolor.Color = 0;
    this->m_wndcolor.Color = 0;
    this->m_id = 0;
    (((GRPinput *)this))->GRPinput::PollInputState(deltatime);
    return 1;
  }
  else if ( v11 )
  {
    if ( Color )
    {
      v6 = (_BYTE *)(Color - 1);
      v7 = *(Color - 1);
      if ( v7 && v7 != -1 )
      {
        *v6 = v7 - 1;
        this->m_fontcolor.Color = 0;
        this->m_wndcolor.Color = 0;
        this->m_id = 0;
        return 0;
      }
      operator delete(v6);
    }
    this->m_fontcolor.Color = 0;
    this->m_wndcolor.Color = 0;
    this->m_id = 0;
    return 0;
  }
  else
  {
    if ( Color )
    {
      this->m_wndcolor.Color = 0;
      *Color = 0;
    }
    return 0;
  }
}

// 0x00445C10
void SceneObj::HideAll()
{
  int v2; // edi
  int v3; // ecx

  v2 = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  for ( this->m_benable = 0; v2 < this->m_childs.capacity; ++v2 )
  {
    v3 = *(_DWORD *)&this->m_childs.m_pData[4 * v2];
    (*(void ( **)(int))(*(_DWORD *)v3 + 12))(v3);
  }
  (((String *)&this->m_childs))->String::Assign(0, -1);
}

// 0x00445C60
int SceneObj::Update(int a2, int a3)
{
  int v5; // edi
  int v6; // esi
  int v7; // ecx

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  v5 = this->m_childs.capacity - 1;
  if ( v5 < 0 )
    return a3 == 0;
  v6 = a3;
  do
  {
    v7 = *(_DWORD *)&this->m_childs.m_pData[4 * v5];
    if ( (*(int ( **)(int, int, int))(*(_DWORD *)v7 + 8))(v7, a2, v6) )
      v6 = 0;
    --v5;
  }
  while ( v5 >= 0 );
  return v6 == 0;
}

// 0x00452FD0
int SceneObj::ctor()
{
  char v3; // [esp+0x7] [ebp-0x1]

  ClearSubArraySlot();
  LOBYTE(this->m_fTimerLimit) = v3;
  *(&this->m_fTimerLimit + 1) = 0;
  this->_SaveTaskInfo.mTouchCounter = 0;
  this->_SaveTaskInfo.m_iState = 0;
  this->_SaveTaskInfo.m_bCVDOver = v3;
  this->m_fTime = 0.0f;
  this->m_fDeltaTime = 0.0f;
  this->m_fTimeScale = 0.0f;
  LOBYTE(this->m_deltatime) = 1;
  return (int)this;
}

// 0x00453030
SceneObj::~SceneObj()
{
  float m_fTime; // eax
  _BYTE *v3; // ecx
  char v4; // al
  int v5; // eax
  _BYTE *v6; // ecx
  char v7; // al

  m_fTime = this->m_fTime;
  if ( m_fTime != 0.0f )
  {
    v3 = (_BYTE *)(LODWORD(m_fTime) - 1);
    v4 = *(_BYTE *)(LODWORD(m_fTime) - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  this->m_fTime = 0.0f;
  this->m_fDeltaTime = 0.0f;
  this->m_fTimeScale = 0.0f;
  v5 = *(&this->m_fTimerLimit + 1);
  if ( v5 )
  {
    v6 = (_BYTE *)(v5 - 1);
    v7 = *(_BYTE *)(v5 - 1);
    if ( v7 && v7 != -1 )
    {
      *v6 = v7 - 1;
      *(&this->m_fTimerLimit + 1) = 0;
      this->_SaveTaskInfo.mTouchCounter = 0;
      this->_SaveTaskInfo.m_iState = 0;
      this->UIWnd::~UIWnd();
      return;
    }
    operator delete(v6);
  }
  *(&this->m_fTimerLimit + 1) = 0;
  this->_SaveTaskInfo.mTouchCounter = 0;
  this->_SaveTaskInfo.m_iState = 0;
  this->UIWnd::~UIWnd();
}

// 0x00453200
char SceneObj::ValidateState()
{
  unsigned int m_bvisible; // eax
  SceneObj *v3; // edi
  unsigned int Color; // eax
  unsigned int v5; // ebx
  void **p_m_bCVDOver; // ebp
  unsigned __int8 *v7; // eax
  unsigned __int8 *v8; // eax
  unsigned __int8 *v9; // esi
  _BYTE *v10; // ecx
  char v11; // al
  unsigned int m_nTodo_008; // ebx
  gbImage2D *m_needscriptdel; // ebp
  char Color_high; // al
  unsigned int v15; // edi
  gbImage2D *v16; // ecx
  unsigned int v18; // [esp+0xC] [ebp-0x24]
  PalScriptIdleObj *p_m_fTimerLimit; // [esp+0x10] [ebp-0x20]
  char v20; // [esp+0x14] [ebp-0x1C] BYREF
  int v21; // [esp+0x18] [ebp-0x18]
  int v22; // [esp+0x1C] [ebp-0x14]
  int v23; // [esp+0x20] [ebp-0x10]
  int v24; // [esp+0x2C] [ebp-0x4]

  m_bvisible = this->m_bvisible;
  if ( m_bvisible )
  {
    if ( LOBYTE(this->m_deltatime) )
    {
      LOBYTE(this->m_deltatime) = 0;
      p_m_fTimerLimit = (PalScriptIdleObj *)&this->m_fTimerLimit;
      v18 = (((CCCTData *)this))->CCCTData::ProcessTask((int)&this->m_fTimerLimit);
      v3 = (((SceneObj *)&this->m_fTimerLimit))->SceneObj::InsertAt((SceneObj *)&v20, 0, v18);
      Color = (unsigned long)v3->m_wndcolor.Color;
      v5 = Color;
      v24 = 0;
      p_m_bCVDOver = (void **)&this->_SaveTaskInfo.m_bCVDOver;
      // [overlay-fix 2026-10-27] 垃圾形条件（成员缺失/类型非法）——待语义修复
      // if ( &this->_SaveTaskInfo.m_bCVDOver == (_BYTE *)v3 )
      if ( 0 )
      {
        (((PalScript *)&this->_SaveTaskInfo.m_bCVDOver))->PalScript::SetWaitRange(Color, 0xFFFFFFFF);
        (((PalScript *)&this->_SaveTaskInfo.m_bCVDOver))->PalScript::SetWaitRange(0, 0);
      }
      else
      {
        if ( !Color )
          goto LABEL_34;
        v7 = (unsigned __int8 *)v3->m_fontcolor.Color;
        if ( !v7 )
          v7 = (unsigned __int8 *)&g_bActorFlag;
        if ( *(v7 - 1) < 0xFEu )
        {
          (((std::string *)1))->_Tidy();
          v8 = (unsigned __int8 *)v3->m_fontcolor.Color;
          if ( !v8 )
            v8 = (unsigned __int8 *)&g_bActorFlag;
          LODWORD(this->m_fTime) = (unsigned long)v8;
          LODWORD(this->m_fDeltaTime) = (unsigned long)v3->m_wndcolor.Color;
          LODWORD(this->m_fTimeScale) = (unsigned long)v3->m_id;
          ++*(v8 - 1);
        }
        else
        {
LABEL_34:
          if ( (((SceneObj *)&this->_SaveTaskInfo.m_bCVDOver))->SceneObj::UpdateAutoDelete(v5) )
          {
            v9 = (unsigned __int8 *)v3->m_fontcolor.Color;
            if ( !v9 )
              v9 = (unsigned __int8 *)&g_bActorFlag;
            qmemcpy(p_m_bCVDOver[1], v9, v5);
            // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
            // (((std::string *)v5))->_Eos();
          }
        }
      }
      v24 = -1;
      if ( v21 )
      {
        v10 = (_BYTE *)(v21 - 1);
        v11 = *(_BYTE *)(v21 - 1);
        if ( !v11 || v11 == -1 )
          operator delete(v10);
        else
          *v10 = v11 - 1;
      }
      m_nTodo_008 = v18;
      v21 = 0;
      v22 = 0;
      m_needscriptdel = (gbImage2D *)p_m_fTimerLimit->m_needscriptdel;
      v23 = 0;
      if ( m_needscriptdel )
      {
        Color_high = HIBYTE(m_needscriptdel[-1].ColorKey.Color);
        if ( Color_high )
        {
          if ( Color_high != -1 )
          {
            (((std::string *)1))->_Tidy();
            (((PalScriptIdleObj *)p_m_fTimerLimit))->PalScriptIdleObj::UpdateWait(m_needscriptdel, strlen((const char *)m_needscriptdel));
          }
        }
      }
      m_bvisible = p_m_fTimerLimit->m_nTodo_008;
      if ( m_bvisible < v18 )
        m_nTodo_008 = p_m_fTimerLimit->m_nTodo_008;
      if ( m_nTodo_008 )
      {
        memcpy(
          p_m_fTimerLimit->m_needscriptdel,
          (char *)p_m_fTimerLimit->m_needscriptdel + m_nTodo_008,
          m_bvisible - m_nTodo_008);
        v15 = (unsigned long)(p_m_fTimerLimit->m_nTodo_008 - m_nTodo_008);
        LOBYTE(m_bvisible) = (((SceneObj *)p_m_fTimerLimit))->SceneObj::UpdateAutoDelete(v15);
        if ( (_BYTE)m_bvisible )
        {
          v16 = (gbImage2D *)p_m_fTimerLimit->m_needscriptdel;
          p_m_fTimerLimit->m_nTodo_008 = v15;
          *((_BYTE *)&v16->ImgInfo.isdiskinfo + v15) = 0;
        }
      }
    }
    else
    {
      LOBYTE(m_bvisible) = (((CCCTData *)this))->CCCTData::ProcessTask((int)&this->_SaveTaskInfo.m_bCVDOver);
    }
  }
  return m_bvisible;
}

// 0x004538E0
char SceneObj::LoadData()
{
  SceneObj *p_m_fTimerLimit; // esi
  int v3; // eax
  char v4; // al
  unsigned int Color; // eax
  unsigned int v6; // eax
  unsigned int v7; // edi
  unsigned int v8; // eax
  char v9; // al
  unsigned int v10; // eax
  unsigned int v11; // ebp
  unsigned int v12; // eax
  unsigned int v13; // ecx
  float m_fTime; // eax
  GRPinput *p_m_bCVDOver; // esi
  char v16; // al
  float v17; // eax
  float v18; // eax
  int v19; // ebp
  float v20; // eax
  char v21; // al
  float v22; // eax
  float v23; // ebx
  IDirectInputDevice8 *v24; // edi
  unsigned int v25; // ebx
  IDirectInputDevice8 *m_lpDIDMouse; // eax
  unsigned int v27; // edi

  p_m_fTimerLimit = (SceneObj *)&this->m_fTimerLimit;
  LOBYTE(this->m_deltatime) = 1;
  v3 = *(&this->m_fTimerLimit + 1);
  if ( v3 )
  {
    v4 = *(_BYTE *)(v3 - 1);
    if ( v4 )
    {
      if ( v4 != -1 )
        (((SceneObj *)&this->m_fTimerLimit))->SceneObj::UpdateAutoDelete(this->_SaveTaskInfo.mTouchCounter);
    }
  }
  Color = (unsigned long)p_m_fTimerLimit->m_fontcolor.Color;
  if ( Color )
    *(_BYTE *)(Color - 1) = -1;
  v6 = (unsigned long)p_m_fTimerLimit->m_fontcolor.Color;
  if ( v6 )
    v7 = v6 + p_m_fTimerLimit->m_wndcolor.Color;
  else
    v7 = 0;
  v8 = (unsigned long)p_m_fTimerLimit->m_fontcolor.Color;
  if ( v8 )
  {
    v9 = *(_BYTE *)(v8 - 1);
    if ( v9 )
    {
      if ( v9 != -1 )
        (((SceneObj *)p_m_fTimerLimit))->SceneObj::UpdateAutoDelete(p_m_fTimerLimit->m_wndcolor.Color);
    }
  }
  v10 = (unsigned long)p_m_fTimerLimit->m_fontcolor.Color;
  if ( v10 )
    *(_BYTE *)(v10 - 1) = -1;
  v11 = (unsigned long)p_m_fTimerLimit->m_fontcolor.Color;
  (((std::string *)p_m_fTimerLimit))->_Freeze();
  if ( v11 )
    v12 = v11 - p_m_fTimerLimit->m_fontcolor.Color;
  else
    v12 = 0;
  if ( v7 )
    v13 = v7 - v11;
  else
    v13 = 0;
  (((PalScript *)p_m_fTimerLimit))->PalScript::SetWaitRange(v12, v13);
  m_fTime = this->m_fTime;
  p_m_bCVDOver = (GRPinput *)&this->_SaveTaskInfo.m_bCVDOver;
  if ( m_fTime != 0.0f )
  {
    v16 = *(_BYTE *)(LODWORD(m_fTime) - 1);
    if ( v16 )
    {
      if ( v16 != -1 )
        (((SceneObj *)&this->_SaveTaskInfo.m_bCVDOver))->SceneObj::UpdateAutoDelete(LODWORD(this->m_fDeltaTime));
    }
  }
  v17 = this->m_fTime;
  if ( v17 != 0.0f )
    *(_BYTE *)(LODWORD(v17) - 1) = -1;
  v18 = this->m_fTime;
  if ( v18 == 0.0f )
    v19 = 0;
  else
    v19 = LODWORD(v18) + LODWORD(this->m_fDeltaTime);
  v20 = this->m_fTime;
  if ( v20 != 0.0f )
  {
    v21 = *(_BYTE *)(LODWORD(v20) - 1);
    if ( v21 )
    {
      if ( v21 != -1 )
        (((SceneObj *)&this->_SaveTaskInfo.m_bCVDOver))->SceneObj::UpdateAutoDelete(LODWORD(this->m_fDeltaTime));
    }
  }
  v22 = this->m_fTime;
  if ( v22 != 0.0f )
    *(_BYTE *)(LODWORD(v22) - 1) = -1;
  v23 = this->m_fTime;
  (((std::string *)p_m_bCVDOver))->_Freeze();
  if ( v23 == 0.0f )
    v24 = 0;
  else
    v24 = (IDirectInputDevice8 *)(LODWORD(v23) - (unsigned int)p_m_bCVDOver->m_lpDIDKeyboard);
  if ( v19 )
    v25 = v19 - LODWORD(v23);
  else
    v25 = 0;
  if ( p_m_bCVDOver->m_lpDIDMouse < v24 )
    std::_Xran();
  (((std::string *)p_m_bCVDOver))->_Split();
  m_lpDIDMouse = (IDirectInputDevice8 *)p_m_bCVDOver->m_lpDIDMouse;
  if ( m_lpDIDMouse - v24 < v25 )
    // [overlay-fix 2026-10-27] 垃圾形表达式——待语义修复
    // v25 = (unsigned int)p_m_bCVDOver->m_lpDIDMouse - v24;
    v25 = 0;
  if ( v25 )
  {
    memcpy(
      &v24[(unsigned int)p_m_bCVDOver->m_lpDIDKeyboard],
      &v24[(unsigned int)&p_m_bCVDOver->m_lpDIDKeyboard[v25]],
      &m_lpDIDMouse[-v25] - v24);
    v27 = (unsigned int)&p_m_bCVDOver->m_lpDIDMouse[-v25];
    LOBYTE(m_lpDIDMouse) = (((SceneObj *)p_m_bCVDOver))->SceneObj::UpdateAutoDelete(v27);
    if ( (_BYTE)m_lpDIDMouse )
    {
      m_lpDIDMouse = (IDirectInputDevice8 *)p_m_bCVDOver->m_lpDIDKeyboard;
      p_m_bCVDOver->m_lpDIDMouse = (IDirectInputDevice8 *)v27;
      ((int *)m_lpDIDMouse)[v27] = 0;
    }
  }
  return (char)m_lpDIDMouse;
}

// 0x00453A70
SceneObj * SceneObj::InsertAt(SceneObj *pSceneObj, unsigned int dwVal, unsigned int dwVal2)
{
  unsigned int v5; // ebx
  int v6; // esi
  unsigned int v7; // ebx
  unsigned int v8; // eax
  unsigned int v9; // ebx
  unsigned int v10; // ebx
  unsigned int Color; // eax
  unsigned int v12; // esi
  unsigned int v14; // eax
  unsigned int v15; // eax
  unsigned int v16; // eax
  unsigned int v17; // ecx

  *(_BYTE *)((UIWnd *)pSceneObj) = (_BYTE)pSceneObj;
  pSceneObj->m_fontcolor.Color = 0;
  pSceneObj->m_wndcolor.Color = 0;
  pSceneObj->m_id = 0;
  if ( this->m_wndcolor.Color < dwVal )
    std::_Xran();
  v5 = this->m_wndcolor.Color - dwVal;
  if ( dwVal2 < v5 )
    v5 = dwVal2;
  if ( pSceneObj == this )
  {
    v6 = -1;
    v7 = dwVal + v5;
    if ( pSceneObj->m_wndcolor.Color < v7 )
      std::_Xran();
    (((std::string *)pSceneObj))->_Split();
    v8 = (unsigned long)(pSceneObj->m_wndcolor.Color - v7);
    if ( v8 != -1 )
      v6 = (unsigned long)(pSceneObj->m_wndcolor.Color - v7);
    if ( v6 )
    {
      memcpy(
        (void *)(pSceneObj->m_fontcolor.Color + v7),
        (const void *)(pSceneObj->m_fontcolor.Color + v7 + v6),
        v8 - v6);
      v9 = (unsigned long)(pSceneObj->m_wndcolor.Color - v6);
      if ( (((SceneObj *)pSceneObj))->SceneObj::UpdateAutoDelete(v9) )
        // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
        // (((std::string *)v9))->_Eos();
        ;   // 空语句体（原为 if 唯一语句，注释后补体防 C2143）
    }
    v10 = dwVal;
    (((std::string *)pSceneObj))->_Split();
    Color = (unsigned long)pSceneObj->m_wndcolor.Color;
    if ( Color < dwVal )
      v10 = (unsigned long)pSceneObj->m_wndcolor.Color;
    if ( v10 )
    {
      memcpy((void *)pSceneObj->m_fontcolor.Color, (const void *)(pSceneObj->m_fontcolor.Color + v10), Color - v10);
      v12 = (unsigned long)(pSceneObj->m_wndcolor.Color - v10);
      if ( (((SceneObj *)pSceneObj))->SceneObj::UpdateAutoDelete(v12) )
      {
        // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
        // (((std::string *)v12))->_Eos();
        return pSceneObj;
      }
    }
    return pSceneObj;
  }
  if ( !v5 || v5 != this->m_wndcolor.Color )
    goto LABEL_33;
  v14 = this->m_fontcolor.Color;
  if ( !v14 )
    v14 = (unsigned int)&g_bActorFlag;
  if ( *(_BYTE *)(v14 - 1) >= 0xFEu )
  {
LABEL_33:
    if ( (((SceneObj *)pSceneObj))->SceneObj::UpdateAutoDelete(v5) )
    {
      v16 = this->m_fontcolor.Color;
      if ( !v16 )
        v16 = (unsigned int)&g_bActorFlag;
      qmemcpy((void *)pSceneObj->m_fontcolor.Color, (const void *)(v16 + dwVal), v5);
      v17 = (unsigned long)pSceneObj->m_fontcolor.Color;
      pSceneObj->m_wndcolor.Color = v5;
      *(_BYTE *)(v17 + v5) = 0;
    }
    return pSceneObj;
  }
  (((std::string *)1))->_Tidy();
  v15 = this->m_fontcolor.Color;
  if ( !v15 )
    v15 = (unsigned int)&g_bActorFlag;
  pSceneObj->m_fontcolor.Color = v15;
  pSceneObj->m_wndcolor.Color = this->m_wndcolor.Color;
  pSceneObj->m_id = this->m_id;
  ++*(_BYTE *)(v15 - 1);
  return pSceneObj;
}

// 0x00527D40
int SceneObj::GetVisibleFlag(_BYTE *p_BYTE)
{
  int result; // eax

  result = *(_DWORD *)&this->m_common[28];
  if ( !result )
  {
    result = (unsigned __int8)this->m_common[24];
    *p_BYTE = result;
  }
  return result;
}

// 0x00527D60
int SceneObj::GetCommonData()
{
  int result; // eax

  result = *(_DWORD *)&this->m_common[20];
  this->m_common[24] = *(_BYTE *)(result + 15038);
  return result;
}

// 0x0052F800
gbVFileSystem * SceneObj::LoadGeomFromFile(const char *pszName)
{
  int v3; // esi
  gbGeomNode *v4; // edi
  gbOBBox *v5; // ebp
  gbVFileSystem *result; // eax
  OpenBaseFile v7; // [esp+0x10] [ebp-0x15C] BYREF
  char Buffer[253]; // [esp+0x14] [ebp-0x158] BYREF
  __int16 v9; // [esp+0x111] [ebp-0x5B]
  char v10; // [esp+0x113] [ebp-0x59]
  gbMatrix4 v11; // [esp+0x114] [ebp-0x58] BYREF
  int v12; // [esp+0x168] [ebp-0x4]

  v3 = 0;
  v12 = 0;
  memset(Buffer, 0, sizeof(Buffer));
  v9 = 0;
  v10 = 0;
  v4 = (gbGeomNode *)this;
  v5 = (gbOBBox *)&this->m_common[44];
  do
  {
    sprintf(Buffer, "%s%s%d.pol", off_5F4D20, pszName, v3);
    (((gbGeomNode *)v4))->gbGeomNode::LoadFromFile(Buffer, 0, 0);
    (((gbGeomNode *)v4))->gbGeomNode::GetOBBox(v5);
    ++v3;
    ++v5;
    v4 = (gbGeomNode *)((char *)v4 + 280);
  }
  while ( v3 < 6 );
  v12 = -1;
  ((OpenNULLFile *)&v7)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x0052FB70
gbVFileSystem * SceneObj::LoadObstruction()
{
  this->SceneObj::LoadGeomFromFile("obstruct");
  RoleAtt_LoadGeomNode((int)"treasure");
  return (((s_RoleState *)this))->s_RoleState::LoadSkeletonModel();
}

// 0x00530280
gbGeomNode * SceneObj::LoadGeomNode(const char *pszFilename)
{
  gbGeomNode *v3; // eax
  gbGeomNode *v4; // esi
  gbGeomNode *v5; // ecx
  gbGeomNode *result; // eax
  OpenBaseFile v7; // [esp+0xC] [ebp-0x60] BYREF
  gbGeomNode *v8; // [esp+0x10] [ebp-0x5C]
  gbMatrix4 v9; // [esp+0x14] [ebp-0x58] BYREF
  int v10; // [esp+0x68] [ebp-0x4]

  v10 = 0;
  v3 = (gbGeomNode *)operator new(0x118u);
  v4 = (gbGeomNode *)v3;
  v8 = (gbGeomNode *)v3;
  LOBYTE(v10) = 1;
  if ( v3 )
  {
    v3->gbGeomNode::gbGeomNode();
    v5 = (gbGeomNode *)v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v10) = 0;
  *(_DWORD *)((UIWnd *)this) = (_DWORD)v5;
  (((gbGeomNode *)v5))->gbGeomNode::LoadFromFile(pszFilename, 0, 0);
  v10 = -1;
  ((OpenNULLFile *)&v7)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x00530330
gbGeomNode * SceneObj::LoadDefaultModel()
{
  return this->SceneObj::LoadGeomNode(pszFilename);
}

// 0x00530340
int SceneObj::SetScriptDel(int nVal)
{
  int result; // eax

  result = nVal;
  this->m_fontcolor.Color = nVal;
  return result;
}

// 0x00536260
int SceneObj::CreateUI()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  ((UIRoleDialog *)&this->mOBBox.trans.xw)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this->m_common[20])->UIRoleDialog::UIRoleDialog();
  (((UIButton *)&this[1].m_info.path.pt[8].y))->UIButton::ctor_17();
  (((UIFrameContainer *)&this[1].m_info.reserve[15]))->UIFrameContainer::ResetContainerState();
  (((Actor *)this))->Actor::ResetDefaultState();
  this[1].m_common[0] = 1;
  return (int)this;
}

// 0x005363C0
int SceneObj::CleanupInternal()
{
  if ( this->m_iState )
    operator delete((void *)this->m_iState);
  return (((Actor *)this))->Actor::ResetDefaultState();
}

// 0x0053EE60
char * SceneObj::StringCopyReplace(SceneObj *pSceneObj, char *pszBuf, char *pszBuf2)
{
  char *result; // eax
  SceneObj *i; // ebp
  char *v6; // esi
  unsigned int v7; // ebx
  unsigned __int8 *v8; // eax
  unsigned int Color; // eax
  _BYTE *v10; // ecx
  char v11; // al
  unsigned __int8 *v12; // eax
  unsigned __int8 *v13; // esi
  unsigned int v14; // ecx

  result = (char *)pszBuf;
  for ( i = pSceneObj; i != (SceneObj *)pszBuf; i = (SceneObj *)((char *)i + 20) )
  {
    v6 = (char *)pszBuf2;
    if ( i != (SceneObj *)pszBuf2 )
    {
      v7 = *((_DWORD *)pszBuf2 + 2);
      if ( !v7 )
        goto LABEL_23;
      v8 = (unsigned __int8 *)*((_DWORD *)pszBuf2 + 1);
      if ( !v8 )
        v8 = (unsigned __int8 *)&g_bActorFlag;
      if ( *(v8 - 1) < 0xFEu )
      {
        Color = (unsigned long)i->m_fontcolor.Color;
        if ( Color )
        {
          v10 = (_BYTE *)(Color - 1);
          v11 = *(_BYTE *)(Color - 1);
          if ( !v11 || v11 == -1 )
            operator delete(v10);
          else
            *v10 = v11 - 1;
        }
        i->m_fontcolor.Color = 0;
        i->m_wndcolor.Color = 0;
        i->m_id = 0;
        v12 = (unsigned __int8 *)*((_DWORD *)pszBuf2 + 1);
        if ( !v12 )
          v12 = (unsigned __int8 *)&g_bActorFlag;
        i->m_fontcolor.Color = (unsigned int)v12;
        i->m_wndcolor.Color = *((_DWORD *)pszBuf2 + 2);
        i->m_id = *((_DWORD *)pszBuf2 + 3);
        ++*(v12 - 1);
      }
      else
      {
LABEL_23:
        if ( (((SceneObj *)i))->SceneObj::UpdateAutoDelete(v7) )
        {
          v13 = (unsigned __int8 *)*((_DWORD *)pszBuf2 + 1);
          if ( !v13 )
            v13 = (unsigned __int8 *)&g_bActorFlag;
          qmemcpy((void *)i->m_fontcolor.Color, v13, v7);
          v14 = (unsigned long)i->m_fontcolor.Color;
          v6 = (char *)pszBuf2;
          i->m_wndcolor.Color = v7;
          *(_BYTE *)(v14 + v7) = 0;
        }
      }
      i->m_rect.left = *((_DWORD *)v6 + 4);
    }
    result = (char *)pszBuf;
  }
  return result;
}

// 0x0053EF60
int SceneObj::LoadFromConfig(int *p_DWORD, int *p_DWORD2, int nVal)
{
  int *v3; // esi
  int v4; // ebp
  unsigned int v5; // ebx
  unsigned __int8 *v6; // eax
  int v7; // eax
  _BYTE *v8; // ecx
  char v9; // al
  unsigned __int8 *v10; // eax
  unsigned __int8 *v11; // esi
  int v12; // ecx
  int *p_DWORD2a; // [esp+0xC] [ebp+0x8]

  v3 = (int *)p_DWORD2;
  if ( p_DWORD == p_DWORD2 )
    return nVal;
  v4 = nVal;
  do
  {
    v3 -= 5;
    v4 -= 20;
    p_DWORD2a = (int *)v3;
    if ( (int *)v4 != v3 )
    {
      v5 = (unsigned long)v3[2];
      if ( !v5 )
        goto LABEL_26;
      v6 = (unsigned __int8 *)v3[1];
      if ( !v6 )
        v6 = (unsigned __int8 *)&g_bActorFlag;
      if ( *(v6 - 1) < 0xFEu )
      {
        v7 = *(_DWORD *)(v4 + 4);
        if ( v7 )
        {
          v8 = (_BYTE *)(v7 - 1);
          v9 = *(_BYTE *)(v7 - 1);
          if ( !v9 || v9 == -1 )
            operator delete(v8);
          else
            *v8 = v9 - 1;
        }
        *(_DWORD *)(v4 + 4) = 0;
        *(_DWORD *)(v4 + 8) = 0;
        *(_DWORD *)(v4 + 12) = 0;
        v10 = (unsigned __int8 *)v3[1];
        if ( !v10 )
          v10 = (unsigned __int8 *)&g_bActorFlag;
        *(_DWORD *)(v4 + 4) = (_DWORD)v10;
        *(_DWORD *)(v4 + 8) = (unsigned long)v3[2];
        *(_DWORD *)(v4 + 12) = (unsigned long)v3[3];
        ++*(v10 - 1);
      }
      else
      {
LABEL_26:
        if ( (((SceneObj *)v4))->SceneObj::UpdateAutoDelete(v5) )
        {
          v11 = (unsigned __int8 *)v3[1];
          if ( !v11 )
            v11 = (unsigned __int8 *)&g_bActorFlag;
          qmemcpy(*(void **)(v4 + 4), v11, v5);
          v12 = *(_DWORD *)(v4 + 4);
          v3 = (int *)p_DWORD2a;
          *(_DWORD *)(v4 + 8) = v5;
          *(_BYTE *)(v5 + v12) = 0;
        }
      }
      *(_DWORD *)(v4 + 16) = (unsigned long)v3[4];
    }
  }
  while ( v3 != p_DWORD );
  return v4;
}

// 0x0053F060
void SceneObj::StringCopyCat(SceneObj *pSceneObj, SceneObj *pSceneObj2)
{
  SceneObj *v3; // edi
  unsigned int v4; // esi
  unsigned int Color; // ebx
  unsigned int v6; // eax
  unsigned int v7; // ebx
  unsigned int v8; // eax
  unsigned int v9; // eax
  const void *v10; // esi
  unsigned int v11; // ecx

  if ( pSceneObj )
  {
    *(_BYTE *)((UIWnd *)pSceneObj) = (_BYTE)pSceneObj2;
    pSceneObj->m_fontcolor.Color = 0;
    pSceneObj->m_wndcolor.Color = 0;
    pSceneObj->m_id = 0;
    v3 = (SceneObj *)pSceneObj2;
    v4 = -1;
    Color = (unsigned long)pSceneObj2->m_wndcolor.Color;
    if ( pSceneObj == pSceneObj2 )
    {
      if ( Color )
        std::_Xran();
      (((std::string *)pSceneObj))->_Split();
      v6 = (unsigned long)pSceneObj->m_wndcolor.Color;
      if ( v6 != -1 )
        v4 = (unsigned long)pSceneObj->m_wndcolor.Color;
      if ( v4 )
      {
        memcpy((void *)pSceneObj->m_fontcolor.Color, (const void *)(pSceneObj->m_fontcolor.Color + v4), v6 - v4);
        v7 = (unsigned long)(pSceneObj->m_wndcolor.Color - v4);
        if ( (((SceneObj *)pSceneObj))->SceneObj::UpdateAutoDelete(v7) )
          // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
          // (((std::string *)v7))->_Eos();
          ;   // 空语句体（原为 if 唯一语句，注释后补体防 C2143）
      }
      (((std::string *)pSceneObj))->_Split();
    }
    else
    {
      if ( !Color )
        goto LABEL_25;
      v8 = (unsigned long)pSceneObj2->m_fontcolor.Color;
      if ( !v8 )
        v8 = (unsigned int)&g_bActorFlag;
      if ( *(_BYTE *)(v8 - 1) < 0xFEu )
      {
        (((std::string *)1))->_Tidy();
        v9 = (unsigned long)pSceneObj2->m_fontcolor.Color;
        if ( !v9 )
          v9 = (unsigned int)&g_bActorFlag;
        pSceneObj->m_fontcolor.Color = v9;
        pSceneObj->m_wndcolor.Color = pSceneObj2->m_wndcolor.Color;
        pSceneObj->m_id = pSceneObj2->m_id;
        ++*(_BYTE *)(v9 - 1);
      }
      else
      {
LABEL_25:
        if ( (((SceneObj *)pSceneObj))->SceneObj::UpdateAutoDelete(Color) )
        {
          v10 = (const void *)pSceneObj2->m_fontcolor.Color;
          if ( !v10 )
            v10 = &g_bActorFlag;
          qmemcpy((void *)pSceneObj->m_fontcolor.Color, v10, Color);
          v11 = (unsigned long)pSceneObj->m_fontcolor.Color;
          v3 = (SceneObj *)pSceneObj2;
          pSceneObj->m_wndcolor.Color = Color;
          *(_BYTE *)(v11 + Color) = 0;
        }
      }
    }
    pSceneObj->m_rect.left = v3->m_rect.left;
  }
}

// 0x0053F4F0
void SceneObj::_nearby_53f4f0(_DWORD *a2)
{
  ;
}
