#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/SceneObj.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445AA0(void); // from annotations
int todo_0(...);

// Unnamed globals (extern)
extern const char * off_5F4D20;

// 0x00407B50
char SceneObj::UpdateAutoDelete(unsigned int deltatime)
{
  gbImage2D *m_needscriptdel; // eax
  char Color_high; // cl
  _BYTE *v6; // ecx
  char v7; // al
  unsigned int v8; // ecx
  _BYTE *v9; // ecx
  char v10; // al
  char v11; // [esp+0x14] [ebp+0x8]

  if ( deltatime > 0xFFFFFFFD )
// [IDA_MISID]     std::_Xlen();
  m_needscriptdel = this->m_needscriptdel;
  if ( m_needscriptdel )
  {
    Color_high = HIBYTE(m_needscriptdel[-1].ColorKey.Color);
    if ( Color_high )
    {
      if ( Color_high != -1 )
      {
        if ( !deltatime )
        {
          HIBYTE(m_needscriptdel[-1].ColorKey.Color) = Color_high - 1;
          this->m_needscriptdel = 0;
// [VFTABLE] this->__vftable = 0;
          *(_DWORD *)&this->m_bEnable = 0;
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
      if ( *(_DWORD *)&this->m_bEnable >= deltatime )
        return 1;
LABEL_29:
      ((GRPinput *)this)->PollInputState(deltatime);
      return 1;
    }
    v8 = *(_DWORD *)&this->m_bEnable;
    if ( v8 <= 0x1F && v8 >= deltatime )
      return 1;
    if ( m_needscriptdel )
    {
      v9 = (char *)&m_needscriptdel[-1].ColorKey.Color + 3;
      v10 = HIBYTE(m_needscriptdel[-1].ColorKey.Color);
      if ( v10 && v10 != -1 )
      {
        *v9 = v10 - 1;
        this->m_needscriptdel = 0;
// [VFTABLE] this->__vftable = 0;
        *(_DWORD *)&this->m_bEnable = 0;
        ((GRPinput *)this)->PollInputState(deltatime);
        return 1;
      }
      operator delete(v9);
    }
    this->m_needscriptdel = 0;
// [VFTABLE] this->__vftable = 0;
    *(_DWORD *)&this->m_bEnable = 0;
    ((GRPinput *)this)->PollInputState(deltatime);
    return 1;
  }
  else if ( v11 )
  {
    if ( m_needscriptdel )
    {
      v6 = (char *)&m_needscriptdel[-1].ColorKey.Color + 3;
      v7 = HIBYTE(m_needscriptdel[-1].ColorKey.Color);
      if ( v7 && v7 != -1 )
      {
        *v6 = v7 - 1;
        this->m_needscriptdel = 0;
// [VFTABLE] this->__vftable = 0;
        *(_DWORD *)&this->m_bEnable = 0;
        return 0;
      }
      operator delete(v6);
    }
    this->m_needscriptdel = 0;
// [VFTABLE] this->__vftable = 0;
    *(_DWORD *)&this->m_bEnable = 0;
    return 0;
  }
  else
  {
    if ( m_needscriptdel )
    {
// [VFTABLE] this->__vftable = 0;
      LOBYTE(m_needscriptdel->ImgInfo.isdiskinfo) = 0;
    }
    return 0;
  }
}

// 0x00452FD0
int SceneObj::ctor()
{
  char v3; // [esp+0x7] [ebp-0x1]

  sub_445AA0();
  *((_BYTE *)&this->8 + 60) = v3;
  *((_DWORD *)&this->8 + 16) = 0;
  this->_SaveTaskInfo.mTouchCounter = 0;
  this->_SaveTaskInfo.m_iState = 0;
  this->_SaveTaskInfo.m_bCVDOver = v3;
  this->m_fTime = 0.0;
  this->m_fDeltaTime = 0.0;
  this->m_fTimeScale = 0.0;
  LOBYTE(this->m_deltatime) = 1;
  return (int)this;
}

// 0x00453030
void SceneObj::ctor_3030()
{
  float m_fTime; // eax
  _BYTE *v3; // ecx
  char v4; // al
  int v5; // eax
  _BYTE *v6; // ecx
  char v7; // al

  m_fTime = this->m_fTime;
  if ( m_fTime != 0.0 )
  {
    v3 = (_BYTE *)(LODWORD(m_fTime) - 1);
    v4 = *(_BYTE *)(LODWORD(m_fTime) - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  this->m_fTime = 0.0;
  this->m_fDeltaTime = 0.0;
  this->m_fTimeScale = 0.0;
  v5 = *((_DWORD *)&this->8 + 16);
  if ( v5 )
  {
    v6 = (_BYTE *)(v5 - 1);
    v7 = *(_BYTE *)(v5 - 1);
    if ( v7 && v7 != -1 )
    {
      *v6 = v7 - 1;
      *((_DWORD *)&this->8 + 16) = 0;
      this->_SaveTaskInfo.mTouchCounter = 0;
      this->_SaveTaskInfo.m_iState = 0;
      ((UIWnd *)this)->_UIWnd();
      return;
    }
    operator delete(v6);
  }
  *((_DWORD *)&this->8 + 16) = 0;
  this->_SaveTaskInfo.mTouchCounter = 0;
  this->_SaveTaskInfo.m_iState = 0;
  ((UIWnd *)this)->_UIWnd();
}

// 0x00453200
char SceneObj::ValidateState()
{
  unsigned int todo_0; // eax
  SceneObj *v3; // edi
  unsigned int vftable; // eax
  unsigned int v5; // ebx
  void **p_m_bCVDOver; // ebp
  unsigned __int8 *m_needscriptdel; // eax
  unsigned __int8 *v8; // eax
  unsigned __int8 *v9; // esi
  _BYTE *v10; // ecx
  char v11; // al
  unsigned int v12; // ebx
  gbImage2D *v13; // ebp
  char Color_high; // al
  unsigned int v15; // edi
  gbImage2D *v16; // ecx
  unsigned int v18; // [esp+0xC] [ebp-0x24]
  PalScriptIdleObj *v19; // [esp+0x10] [ebp-0x20]
  char v20; // [esp+0x14] [ebp-0x1C] BYREF
  int v21; // [esp+0x18] [ebp-0x18]
  int v22; // [esp+0x1C] [ebp-0x14]
  int v23; // [esp+0x20] [ebp-0x10]
  int v24; // [esp+0x2C] [ebp-0x4]

  todo_0 = *((_DWORD *)&this->8 + 12);
  if ( todo_0 )
  {
    if ( LOBYTE(this->m_deltatime) )
    {
      LOBYTE(this->m_deltatime) = 0;
      v19 = (PalScriptIdleObj *)((char *)&this->8 + 60);
      v18 = ((CCCTData *)this)->ProcessTask((int)&this->8 + 60);
      v3 = ((SceneObj *)((char *)&this->8 + 60))->InsertAt((SceneObj *)&v20, 0, v18);
// [VFTABLE] vftable = (unsigned int)v3->__vftable;
      v5 = vftable;
      v24 = 0;
      p_m_bCVDOver = (void **)&this->_SaveTaskInfo.m_bCVDOver;
      if ( &this->_SaveTaskInfo.m_bCVDOver == (_BYTE *)v3 )
      {
        ((PalScript *)&this->_SaveTaskInfo.m_bCVDOver)->SetWaitRange(vftable, 0xFFFFFFFF);
        ((PalScript *)&this->_SaveTaskInfo.m_bCVDOver)->SetWaitRange(0, 0);
      }
      else
      {
        if ( !vftable )
          goto LABEL_34;
        m_needscriptdel = (unsigned __int8 *)v3->m_needscriptdel;
        if ( !m_needscriptdel )
          m_needscriptdel = &g_bActorFlag;
        if ( *(m_needscriptdel - 1) < 0xFEu )
        {
          ((std *)1)->string::_Tidy();
          v8 = (unsigned __int8 *)v3->m_needscriptdel;
          if ( !v8 )
            v8 = &g_bActorFlag;
          LODWORD(this->m_fTime) = v8;
// [VFTABLE] LODWORD(this->m_fDeltaTime) = v3->__vftable;
          this->m_fTimeScale = *(float *)&v3->m_bEnable;
          ++*(v8 - 1);
        }
        else
        {
LABEL_34:
          if ( ((SceneObj *)&this->_SaveTaskInfo.m_bCVDOver)->UpdateAutoDelete(v5) )
          {
            v9 = (unsigned __int8 *)v3->m_needscriptdel;
            if ( !v9 )
              v9 = &g_bActorFlag;
            qmemcpy(p_m_bCVDOver[1], v9, v5);
            ((std *)v5)->string::_Eos();
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
      v12 = v18;
      v21 = 0;
      v22 = 0;
      v13 = v19->m_needscriptdel;
      v23 = 0;
      if ( v13 )
      {
        Color_high = HIBYTE(v13[-1].ColorKey.Color);
        if ( Color_high )
        {
          if ( Color_high != -1 )
          {
            ((std *)1)->string::_Tidy();
            ((PalScriptIdleObj *)v19)->UpdateWait(v13, strlen((const char *)v13));
          }
        }
      }
      todo_0 = v19->_todo_0;
      if ( todo_0 < v18 )
        v12 = v19->_todo_0;
      if ( v12 )
      {
        memcpy(v19->m_needscriptdel, (char *)v19->m_needscriptdel + v12, todo_0 - v12);
        v15 = v19->_todo_0 - v12;
        LOBYTE(todo_0) = ((SceneObj *)v19)->UpdateAutoDelete(v15);
        if ( (_BYTE)todo_0 )
        {
          v16 = v19->m_needscriptdel;
          v19->_todo_0 = v15;
          *((_BYTE *)&v16->ImgInfo.isdiskinfo + v15) = 0;
        }
      }
    }
    else
    {
      LOBYTE(todo_0) = ((CCCTData *)this)->ProcessTask((int)&this->_SaveTaskInfo.m_bCVDOver);
    }
  }
  return todo_0;
}

// 0x004538E0
char SceneObj::LoadData()
{
  char *v2; // esi
  int v3; // eax
  char v4; // al
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  char v9; // al
  int v10; // eax
  int v11; // ebp
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

  v2 = (char *)&this->8 + 60;
  LOBYTE(this->m_deltatime) = 1;
  v3 = *((_DWORD *)&this->8 + 16);
  if ( v3 )
  {
    v4 = *(_BYTE *)(v3 - 1);
    if ( v4 )
    {
      if ( v4 != -1 )
        ((SceneObj *)((char *)&this->8 + 60))->UpdateAutoDelete(this->_SaveTaskInfo.mTouchCounter);
    }
  }
  v5 = *((_DWORD *)v2 + 1);
  if ( v5 )
    *(_BYTE *)(v5 - 1) = -1;
  v6 = *((_DWORD *)v2 + 1);
  if ( v6 )
    v7 = v6 + *((_DWORD *)v2 + 2);
  else
    v7 = 0;
  v8 = *((_DWORD *)v2 + 1);
  if ( v8 )
  {
    v9 = *(_BYTE *)(v8 - 1);
    if ( v9 )
    {
      if ( v9 != -1 )
        ((SceneObj *)v2)->UpdateAutoDelete(*((_DWORD *)v2 + 2));
    }
  }
  v10 = *((_DWORD *)v2 + 1);
  if ( v10 )
    *(_BYTE *)(v10 - 1) = -1;
  v11 = *((_DWORD *)v2 + 1);
  ((std *)v2)->string::_Freeze();
  if ( v11 )
    v12 = v11 - *((_DWORD *)v2 + 1);
  else
    v12 = 0;
  if ( v7 )
    v13 = v7 - v11;
  else
    v13 = 0;
  ((PalScript *)v2)->SetWaitRange(v12, v13);
  m_fTime = this->m_fTime;
  p_m_bCVDOver = (GRPinput *)&this->_SaveTaskInfo.m_bCVDOver;
  if ( m_fTime != 0.0 )
  {
    v16 = *(_BYTE *)(LODWORD(m_fTime) - 1);
    if ( v16 )
    {
      if ( v16 != -1 )
        ((SceneObj *)&this->_SaveTaskInfo.m_bCVDOver)->UpdateAutoDelete(LODWORD(this->m_fDeltaTime));
    }
  }
  v17 = this->m_fTime;
  if ( v17 != 0.0 )
    *(_BYTE *)(LODWORD(v17) - 1) = -1;
  v18 = this->m_fTime;
  if ( v18 == 0.0 )
    v19 = 0;
  else
    v19 = LODWORD(v18) + LODWORD(this->m_fDeltaTime);
  v20 = this->m_fTime;
  if ( v20 != 0.0 )
  {
    v21 = *(_BYTE *)(LODWORD(v20) - 1);
    if ( v21 )
    {
      if ( v21 != -1 )
        ((SceneObj *)&this->_SaveTaskInfo.m_bCVDOver)->UpdateAutoDelete(LODWORD(this->m_fDeltaTime));
    }
  }
  v22 = this->m_fTime;
  if ( v22 != 0.0 )
    *(_BYTE *)(LODWORD(v22) - 1) = -1;
  v23 = this->m_fTime;
  ((std *)p_m_bCVDOver)->string::_Freeze();
  if ( v23 == 0.0 )
    v24 = 0;
  else
    v24 = (IDirectInputDevice8 *)(LODWORD(v23) - (unsigned int)p_m_bCVDOver->m_lpDIDKeyboard);
  if ( v19 )
    v25 = v19 - LODWORD(v23);
  else
    v25 = 0;
  if ( p_m_bCVDOver->m_lpDIDMouse < v24 )
// [IDA_MISID]     std::_Xran();
  ((std *)p_m_bCVDOver)->string::_Split();
  m_lpDIDMouse = p_m_bCVDOver->m_lpDIDMouse;
  if ( m_lpDIDMouse - v24 < v25 )
    v25 = p_m_bCVDOver->m_lpDIDMouse - v24;
  if ( v25 )
  {
    memcpy(
      &v24[(unsigned int)p_m_bCVDOver->m_lpDIDKeyboard],
      &v24[(unsigned int)&p_m_bCVDOver->m_lpDIDKeyboard[v25]],
      &m_lpDIDMouse[-v25] - v24);
    v27 = (unsigned int)&p_m_bCVDOver->m_lpDIDMouse[-v25];
    LOBYTE(m_lpDIDMouse) = ((SceneObj *)p_m_bCVDOver)->UpdateAutoDelete(v27);
    if ( (_BYTE)m_lpDIDMouse )
    {
      m_lpDIDMouse = p_m_bCVDOver->m_lpDIDKeyboard;
      p_m_bCVDOver->m_lpDIDMouse = (IDirectInputDevice8 *)v27;
      m_lpDIDMouse[v27] = 0;
    }
  }
  return (char)m_lpDIDMouse;
}

// 0x00453A70
SceneObj * SceneObj::InsertAt(SceneObj *pSceneObj, unsigned int dwVal, unsigned int dwVal2)
{
  char *v5; // ebx
  int v6; // esi
  char *v7; // ebx
  char *v8; // eax
  char *v9; // ebx
  unsigned int v10; // ebx
  void *vftable; // eax
  char *v12; // esi
  char *m_needscriptdel; // eax
  gbImage2D *v15; // eax
  char *v16; // eax
  gbImage2D *v17; // ecx

// [VFTABLE] LOBYTE(pSceneObj->__vftable) = (_BYTE)pSceneObj;
  pSceneObj->m_needscriptdel = 0;
// [VFTABLE] pSceneObj->__vftable = 0;
  *(_DWORD *)&pSceneObj->m_bEnable = 0;
// [VFTABLE] if ( this->__vftable < (void *)dwVal )
// [IDA_MISID]     std::_Xran();
// [VFTABLE] v5 = (char *)this->__vftable - dwVal;
  if ( dwVal2 < (unsigned int)v5 )
    v5 = (char *)dwVal2;
  if ( pSceneObj == this )
  {
    v6 = -1;
    v7 = &v5[dwVal];
// [VFTABLE] if ( pSceneObj->__vftable < v7 )
// [IDA_MISID]       std::_Xran();
    ((std *)pSceneObj)->string::_Split();
// [VFTABLE] v8 = (char *)((char *)pSceneObj->__vftable - (char *)v7);
    if ( v8 != (char *)-1 )
// [VFTABLE] v6 = (char *)pSceneObj->__vftable - (char *)v7;
    if ( v6 )
    {
      memcpy(
        (char *)pSceneObj->m_needscriptdel + (unsigned int)v7,
        (char *)pSceneObj->m_needscriptdel + (unsigned int)v7 + v6,
        (size_t)&v8[-v6]);
// [VFTABLE] v9 = (char *)pSceneObj->__vftable - v6;
      if ( ((SceneObj *)pSceneObj)->UpdateAutoDelete((unsigned int)v9) )
        ((std *)v9)->string::_Eos();
    }
    v10 = dwVal;
    ((std *)pSceneObj)->string::_Split();
// [VFTABLE] vftable = pSceneObj->__vftable;
    if ( (unsigned int)vftable < dwVal )
// [VFTABLE] v10 = (unsigned int)pSceneObj->__vftable;
    if ( v10 )
    {
      memcpy(pSceneObj->m_needscriptdel, (char *)pSceneObj->m_needscriptdel + v10, (size_t)vftable - v10);
// [VFTABLE] v12 = (char *)pSceneObj->__vftable - v10;
      if ( ((SceneObj *)pSceneObj)->UpdateAutoDelete((unsigned int)v12) )
      {
        ((std *)v12)->string::_Eos();
        return pSceneObj;
      }
    }
    return pSceneObj;
  }
// [VFTABLE] if ( !v5 || v5 != this->__vftable )
    goto LABEL_33;
  m_needscriptdel = (char *)this->m_needscriptdel;
  if ( !m_needscriptdel )
    m_needscriptdel = (char *)&g_bActorFlag;
  if ( (unsigned __int8)*(m_needscriptdel - 1) >= 0xFEu )
  {
LABEL_33:
    if ( ((SceneObj *)pSceneObj)->UpdateAutoDelete((unsigned int)v5) )
    {
      v16 = (char *)this->m_needscriptdel;
      if ( !v16 )
        v16 = (char *)&g_bActorFlag;
      qmemcpy(pSceneObj->m_needscriptdel, &v16[dwVal], (unsigned int)v5);
      v17 = pSceneObj->m_needscriptdel;
// [VFTABLE] pSceneObj->__vftable = v5;
      v5[(_DWORD)v17] = 0;
    }
    return pSceneObj;
  }
  ((std *)1)->string::_Tidy();
  v15 = this->m_needscriptdel;
  if ( !v15 )
    v15 = (gbImage2D *)&g_bActorFlag;
  pSceneObj->m_needscriptdel = v15;
// [VFTABLE] pSceneObj->__vftable = this->__vftable;
  *(_DWORD *)&pSceneObj->m_bEnable = *(_DWORD *)&this->m_bEnable;
  ++HIBYTE(v15[-1].ColorKey.Color);
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
int SceneObj::fn_527D60()
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
    ((gbGeomNode *)v4)->LoadFromFile(Buffer, 0, 0);
    ((gbGeomNode *)v4)->GetOBBox(v5);
    ++v3;
    ++v5;
    v4 = (gbGeomNode *)((char *)v4 + 280);
  }
  while ( v3 < 6 );
  v12 = -1;
  return result;
}

// 0x0052FB70
gbVFileSystem * SceneObj::LoadObstruction()
{
  this->LoadGeomFromFile("obstruct");
  ((RoleAtt *)this)->LoadGeomNode((int)"treasure");
  return ((s_RoleState *)this)->LoadSkeletonModel();
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
  v4 = v3;
  v8 = v3;
  LOBYTE(v10) = 1;
  if ( v3 )
  {
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v10) = 0;
// [VFTABLE] this->__vftable = v5;
  ((gbGeomNode *)v5)->LoadFromFile(pszFilename, 0, 0);
  v10 = -1;
  return result;
}

// 0x00530330
gbGeomNode * SceneObj::LoadDefaultModel()
{
  return this->LoadGeomNode(pszFilename);
}

// 0x00530340
int SceneObj::SetScriptDel(int nVal)
{
  this->m_needscriptdel = (gbImage2D *)nVal;
  return nVal;
}

// 0x00536260
int SceneObj::CreateUI()
{
  ((ARC_PlayerAtt *)&this->mOBBox.trans.m[0][3])->Refresh();
  ((ARC_PlayerAtt *)&this->m_common[20])->Refresh();
  ((UIButton *)(UIButton *)this + 9)->ctor_17();
  sub_4422E0((char *)this + 3340);
  ((Actor *)this)->ResetDefaultState();
  *((_BYTE *)this + 3492) = 1;
  return (int)this;
}

// 0x005362F0
SceneObj * SceneObj::Destructor()
{
  char v3; // [esp+0x8] [ebp+0x4]

  ((Actor *)this)->DestroyInternalData();
  if ( (v3 & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x005363C0
int SceneObj::CleanupInternal()
{
  if ( this->m_iState )
    operator delete((void *)this->m_iState);
  return ((Actor *)this)->ResetDefaultState();
}

// 0x005368A0
BOOL SceneObj::HandleEvent(int nVal, int nVal2)
{
  int m_iState; // edi
  DWORD TickCount; // eax
  DWORD v7; // eax
  unsigned int v8; // edx
  char v9; // al
  char v10; // al
  char mTouchCounter_high; // al

  if ( LOBYTE(this->mOBBox.trans.m[0][2]) )
    return ((UIListBox *)this)->Update(nVal, nVal2);
  if ( !*(&this->m_bCVDOver + 1) && ((UIParabolaCtrl *)&this->m_common[20])->GetState() == 2 )
    *(&this->m_bCVDOver + 1) = 1;
  sprintf((char *const)&this->8 + 64, "%d/%d", (int)*((float *)this + 813), this->mOBBox.trans.m[0][1]);
  ((UICaption *)((char *)this + 3340))->SetEnable((int)(&this->8 + 2), 1);
  if ( LOBYTE(this->mRetrorse) )
  {
    m_iState = this->m_iState;
    if ( !*(_BYTE *)(m_iState + 8) )
    {
      TickCount = GetTickCount();
      *(_DWORD *)m_iState = TickCount;
      *(_DWORD *)(m_iState + 4) = TickCount;
      *(_BYTE *)(m_iState + 8) = 1;
    }
    v7 = GetTickCount();
    v8 = v7 - *(_DWORD *)(m_iState + 4);
    *(_DWORD *)m_iState = v7;
    if ( v8 <= 0x7D0 )
    {
      v9 = BYTE1(this->mRetrorse);
      this->m_bCVDOver = 0;
      if ( v9 )
      {
        v10 = HIBYTE(this->mTouchCounter) + 20;
        HIBYTE(this->mTouchCounter) = v10;
        if ( v10 == -1 )
        {
          HIBYTE(this->mTouchCounter) = -1;
          BYTE1(this->mRetrorse) = 0;
        }
      }
      else
      {
        mTouchCounter_high = HIBYTE(this->mTouchCounter);
        HIBYTE(this->mTouchCounter) = mTouchCounter_high - 20;
        if ( mTouchCounter_high == 20 )
        {
          HIBYTE(this->mTouchCounter) = 0;
          BYTE1(this->mRetrorse) = 1;
        }
      }
    }
    else
    {
      *(_DWORD *)(m_iState + 4) = v7;
      *(_BYTE *)(m_iState + 8) = 0;
      LOBYTE(this->mRetrorse) = 0;
      this->m_bCVDOver = 1;
      HIBYTE(this->mTouchCounter) = -1;
    }
  }
  LOBYTE(this->mOBBox.trans.m[0][2]) = ((UIParabolaCtrl *)&this->mOBBox.trans.m[0][3])->GetState() == 2;
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x0053EE60
char * SceneObj::StringCopyReplace(SceneObj *pSceneObj, char *pszBuf, char *pszBuf2)
{
  char *result; // eax
  SceneObj *i; // ebp
  char *v6; // esi
  unsigned int v7; // ebx
  unsigned __int8 *v8; // eax
  gbImage2D *m_needscriptdel; // eax
  _BYTE *v10; // ecx
  char Color_high; // al
  unsigned __int8 *v12; // eax
  unsigned __int8 *v13; // esi
  gbImage2D *v14; // ecx

  result = pszBuf;
  for ( i = pSceneObj; i != (SceneObj *)pszBuf; i = (SceneObj *)((char *)i + 20) )
  {
    v6 = pszBuf2;
    if ( i != (SceneObj *)pszBuf2 )
    {
      v7 = *((_DWORD *)pszBuf2 + 2);
      if ( !v7 )
        goto LABEL_23;
      v8 = (unsigned __int8 *)*((_DWORD *)pszBuf2 + 1);
      if ( !v8 )
        v8 = &g_bActorFlag;
      if ( *(v8 - 1) < 0xFEu )
      {
        m_needscriptdel = i->m_needscriptdel;
        if ( m_needscriptdel )
        {
          v10 = (char *)&m_needscriptdel[-1].ColorKey.Color + 3;
          Color_high = HIBYTE(m_needscriptdel[-1].ColorKey.Color);
          if ( !Color_high || Color_high == -1 )
            operator delete(v10);
          else
            *v10 = Color_high - 1;
        }
        i->m_needscriptdel = 0;
// [VFTABLE] i->__vftable = 0;
        *(_DWORD *)&i->m_bEnable = 0;
        v12 = (unsigned __int8 *)*((_DWORD *)pszBuf2 + 1);
        if ( !v12 )
          v12 = &g_bActorFlag;
        i->m_needscriptdel = (gbImage2D *)v12;
// [VFTABLE] i->__vftable = (void *)*((_DWORD *)pszBuf2 + 2);
        *(_DWORD *)&i->m_bEnable = *((_DWORD *)pszBuf2 + 3);
        ++*(v12 - 1);
      }
      else
      {
LABEL_23:
        if ( ((SceneObj *)i)->UpdateAutoDelete(v7) )
        {
          v13 = (unsigned __int8 *)*((_DWORD *)pszBuf2 + 1);
          if ( !v13 )
            v13 = &g_bActorFlag;
          qmemcpy(i->m_needscriptdel, v13, v7);
          v14 = i->m_needscriptdel;
          v6 = pszBuf2;
// [VFTABLE] i->__vftable = (void *)v7;
          *((_BYTE *)&v14->ImgInfo.isdiskinfo + v7) = 0;
        }
      }
      i->m_nStepSize = *((_DWORD *)v6 + 4);
    }
    result = pszBuf;
  }
  return result;
}

// 0x0053EF60
int SceneObj::LoadFromConfig(int *p_DWORD2, int nVal)
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

  v3 = p_DWORD2;
  if ( p_DWORD == p_DWORD2 )
    return nVal;
  v4 = nVal;
  do
  {
    v3 -= 5;
    v4 -= 20;
    p_DWORD2a = v3;
    if ( (int *)v4 != v3 )
    {
      v5 = v3[2];
      if ( !v5 )
        goto LABEL_26;
      v6 = (unsigned __int8 *)v3[1];
      if ( !v6 )
        v6 = &g_bActorFlag;
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
          v10 = &g_bActorFlag;
        *(_DWORD *)(v4 + 4) = v10;
        *(_DWORD *)(v4 + 8) = v3[2];
        *(_DWORD *)(v4 + 12) = v3[3];
        ++*(v10 - 1);
      }
      else
      {
LABEL_26:
        if ( ((SceneObj *)v4)->UpdateAutoDelete(v5) )
        {
          v11 = (unsigned __int8 *)v3[1];
          if ( !v11 )
            v11 = &g_bActorFlag;
          qmemcpy(*(void **)(v4 + 4), v11, v5);
          v12 = *(_DWORD *)(v4 + 4);
          v3 = p_DWORD2a;
          *(_DWORD *)(v4 + 8) = v5;
          *(_BYTE *)(v5 + v12) = 0;
        }
      }
      *(_DWORD *)(v4 + 16) = v3[4];
    }
  }
  while ( v3 != p_DWORD );
  return v4;
}

// 0x0053F060
void SceneObj::StringCopyCat(SceneObj *pSceneObj, SceneObj *pSceneObj2)
{
  SceneObj *v3; // edi
  int v4; // esi
  void *vftable; // ebx
  void *v6; // eax
  char *v7; // ebx
  char *m_needscriptdel; // eax
  gbImage2D *v9; // eax
  const void *v10; // esi
  gbImage2D *v11; // ecx

  if ( pSceneObj )
  {
// [VFTABLE] LOBYTE(pSceneObj->__vftable) = (_BYTE)pSceneObj2;
    pSceneObj->m_needscriptdel = 0;
// [VFTABLE] pSceneObj->__vftable = 0;
    *(_DWORD *)&pSceneObj->m_bEnable = 0;
    v3 = pSceneObj2;
    v4 = -1;
// [VFTABLE] vftable = pSceneObj2->__vftable;
    if ( pSceneObj == pSceneObj2 )
    {
      if ( vftable )
// [IDA_MISID]         std::_Xran();
      ((std *)pSceneObj)->string::_Split();
// [VFTABLE] v6 = pSceneObj->__vftable;
      if ( v6 != (void *)-1 )
// [VFTABLE] v4 = (int)pSceneObj->__vftable;
      if ( v4 )
      {
        memcpy(pSceneObj->m_needscriptdel, (char *)pSceneObj->m_needscriptdel + v4, (size_t)v6 - v4);
// [VFTABLE] v7 = (char *)pSceneObj->__vftable - v4;
        if ( ((SceneObj *)pSceneObj)->UpdateAutoDelete((unsigned int)v7) )
          ((std *)v7)->string::_Eos();
      }
      ((std *)pSceneObj)->string::_Split();
    }
    else
    {
      if ( !vftable )
        goto LABEL_25;
      m_needscriptdel = (char *)pSceneObj2->m_needscriptdel;
      if ( !m_needscriptdel )
        m_needscriptdel = (char *)&g_bActorFlag;
      if ( (unsigned __int8)*(m_needscriptdel - 1) < 0xFEu )
      {
        ((std *)1)->string::_Tidy();
        v9 = pSceneObj2->m_needscriptdel;
        if ( !v9 )
          v9 = (gbImage2D *)&g_bActorFlag;
        pSceneObj->m_needscriptdel = v9;
// [VFTABLE] pSceneObj->__vftable = pSceneObj2->__vftable;
        *(_DWORD *)&pSceneObj->m_bEnable = *(_DWORD *)&pSceneObj2->m_bEnable;
        ++HIBYTE(v9[-1].ColorKey.Color);
      }
      else
      {
LABEL_25:
        if ( ((SceneObj *)pSceneObj)->UpdateAutoDelete((unsigned int)vftable) )
        {
          v10 = pSceneObj2->m_needscriptdel;
          if ( !v10 )
            v10 = &g_bActorFlag;
          qmemcpy(pSceneObj->m_needscriptdel, v10, (unsigned int)vftable);
          v11 = pSceneObj->m_needscriptdel;
          v3 = pSceneObj2;
// [VFTABLE] pSceneObj->__vftable = vftable;
          *((_BYTE *)vftable + (_DWORD)v11) = 0;
        }
      }
    }
    pSceneObj->m_nStepSize = v3->m_nStepSize;
  }
}
