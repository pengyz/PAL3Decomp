// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Script/PalScript.h"
#include "Role/Actor.h"
#include "Misc/Array.h"
#include "Misc/CCBEditor.h"
#include "Combat/CCBItemWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Misc/CEffGroupNode.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffect.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Scene/CameraCtrl.h"
#include "Misc/ComposeUI.h"
#include "GameBase/Config.h"
#include "Misc/DealData.h"
#include "GameBase/GRPinput.h"
#include "GameBase/InputSystem.h"
#include "GameBase/Logger.h"
#include "Role/NPC.h"
#include "Misc/Object.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Misc/OpenSceneFile.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PlayerItem.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget2.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Misc/RoleCameraCtrl.h"
#include "Role/RoleSystem.h"
#include "Scene/Scene.h"
#include "Scene/SceneObj.h"
#include "Effect/ScreenEffect.h"
#include "Effect/ScreenEffectMgr.h"
#include "Misc/ScriptPoolPage.h"
#include "Script/ScriptSystem.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/ScriptVM.h"
#include "Misc/String.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/TxtFile.h"
#include "Misc/UIBigMap.h"
#include "Misc/UICoverFrm.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "UI/UIScene.h"
#include "Misc/UISceneMap.h"
#include "Misc/UIStatic.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "Misc/_Console.h"
#include "Misc/_PlugInfo.h"
#include "Misc/_Texture_Info.h"
#include "Misc/scAsmDecoder.h"
#include "Misc/scScriptBlock.h"
#include "Misc/scScriptInstance.h"
#include "Misc/scUserVarInfo.h"
#include "Misc/unchar.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_53D2F0(...);

class TextureLibDataBase;
class RoleCameraCtrl;

// Unnamed globals (extern)
extern int dword_D8E48C;
extern int dword_D8E490;
extern int dword_D8E494;
extern int dword_D8E498;
extern int dword_D8E4A4;
extern int dword_D8E4AC;
extern int dword_D8E4B0;
extern int dword_D8E4B4;
extern int dword_D8E4B8;
extern int dword_D92780;
extern PalScriptMgr * dword_DBA24C;
extern PalScriptMgr * dword_DBA254;
extern float flt_D8EB94;
void __cdecl nullsub_2(...);
extern TextureLibDataBase stru_1894B78;
extern RoleCameraCtrl stru_DBA134;

// 0x00410840
PalScript * PalScript::InitParticleSlht(PalScript *pPalScript)
{
  PalScript *result; // eax
  gbParticleEffect *v3; // eax
  gbParticleEffect *v4; // esi
  gbParticleEffect *v5; // ecx

  result = (PalScript *)pPalScript;
  if ( pPalScript )
  {
    v3 = (gbParticleEffect *)operator new(0x160u);
    v4 = (gbParticleEffect *)v3;
    if ( v3 )
    {
      v3->gbParticleEffect::gbParticleEffect();
      v5 = (gbParticleEffect *)v4;
    }
    else
    {
      v5 = 0;
    }
    dword_C10CBC = (int)v5;
    (((gbParticleEffect *)v5))->gbParticleEffect::LoadFromFile("effect\\gbParticle\\slht.par");
    result = (PalScript *)dword_C10CBC;
    *(_DWORD *)(dword_C10CBC + 280) = 1090519040;
  }
  else
  {
    if ( dword_C10CBC )
      result = (PalScript *)(**(int ( ***)(int, int))dword_C10CBC)((int)(dword_C10CBC), (int)(1));
    dword_C10CBC = 0;
  }
  return result;
}

// 0x00412680
int PalScript::DestroyScript()
{
  int ( ***pScriptVtable)(void *, int); // ecx
  int result; // eax

  pScriptVtable = (int ( ***)(void *, int))this->m_szDialog1.overlay.pScriptVtable;
  this->m_RoleSlotArray.overlay.m_fSceneCfg[17] = 0.0;
  if ( pScriptVtable )
  {
    result = (**pScriptVtable)((void *)(pScriptVtable), (int)(1));
    this->m_szDialog1.overlay.pScriptVtable = 0;
  }
  this->m_szDialog1.overlay.pScriptPtrB = 0;
  this->m_szDialog1.overlay.pScriptPtrA = 0;
  *((_DWORD *)&this->m_RoleSlotArray.script_state + 218) = 0;
  this->m_szDialog1.overlay.pScriptPtrC = 0;
  this->m_RoleSlotArray.overlay.m_nPathState = 0;
  return result;
}

// 0x00421560
void PalScript::SetAction(int nRoleID)
{
  int m_nRoleCount; // esi
  int v3; // eax
  _inline_PalScript_m_RoleSlotArray *pSlots; // edx

  m_nRoleCount = this->m_nRoleCount;
  v3 = 0;
  if ( m_nRoleCount > 0 )
  {
    pSlots = (_inline_PalScript_m_RoleSlotArray *)&this->m_RoleSlotArray;
    do
    {
      if ( LOBYTE(pSlots->slot.nRoleID) == (_WORD)nRoleID )
        break;
      ++v3;
      ++pSlots;
    }
    while ( v3 < m_nRoleCount );
  }
}

// 0x00421CA0
void PalScript::BindRolesToStage()
{
  int v2; // ebp
  bool v3; // bl
  _BYTE *p_m_RoleActionType; // esi
  char v5; // al
  int v6; // eax

  v2 = 0;
  v3 = 1;
  if ( this->m_nRoleCount > 0 )
  {
    p_m_RoleActionType = (_BYTE *)&this->m_RoleSlotArray.overlay.m_RoleActionType;
    do
    {
      if ( *(p_m_RoleActionType - 72) != 32 && *p_m_RoleActionType == 25 )
      {
        v5 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::Find(p_m_RoleActionType - 68);
        *(p_m_RoleActionType - 71) = v5;
        v3 = v3 && v5;
      }
      ++v2;
      p_m_RoleActionType += 896;
    }
    while ( v2 < this->m_nRoleCount );
  }
  this->PalScript::SetAction(32);
  if ( v6 )
    *(_BYTE *)(v6 + 173) = v3;
}

// 0x00429D10
int * PalScript::GetCount(int nVal)
{
  int *result; // eax

  if ( (*(void **)(this)) == (void *)3 )
    return (int *)(*(int ( **)(scScriptInstance *))&this->m_pinst->pblock->desc[16])(this->m_pinst);
  result = (int *)&this->__vftable[-1]._scalar_dtor_4D50;
  if ( (*(void **)(this)) == (void *)4 )
    return (int *)(*(int ( **)(scScriptInstance *, int))&this->m_pinst->pblock->desc[44])(this->m_pinst, nVal);
  return result;
}

// 0x00429D40
void PalScript::SetIndex(int nVal)
{
  switch ( (unsigned int)(*(void **)(this)) )
  {
    case 1u:
    case 2u:
    case 3u:
      (*(void ( **)(scScriptInstance *, int))&this->m_pinst->pblock->desc[12])(this->m_pinst, nVal);
      break;
    case 4u:
      (*(void ( **)(scScriptInstance *, _DWORD))&this->m_pinst->pblock->desc[12])(this->m_pinst, 0);
      break;
    default:
      return;
  }
}

// 0x0042C700
void PalScript::StopSound3D()
{
  gbSound3DNode *m_EncampSound; // ecx

  if ( this->m_bSoundType == 43 )
  {
    m_EncampSound = (gbSound3DNode *)this->m_RoleSlotArray.overlay.m_EncampSound;
    if ( m_EncampSound )
    {
      if ( (g_dwGameFlags & 1) != 0 )
        (((gbSound3DNode *)m_EncampSound))->gbSound3DNode::Stop();
    }
  }
}

// 0x00430290
int PalScript::LoadScript(int pathAddr)
{
  unsigned int v2; // kr04_4
  unsigned int v3; // ebp
  unsigned int v4; // kr08_4
  unsigned int v5; // ebp
  char *v6; // ecx
  char v7; // al
  char *v8; // ecx
  char v9; // al
  int result; // eax
  char v11; // [esp+0x13] [ebp-0x265]
  int p_DWORD; // [esp+0x14] [ebp-0x264] BYREF
  char *v13; // [esp+0x18] [ebp-0x260]
  unsigned int v14; // [esp+0x1C] [ebp-0x25C]
  int v15; // [esp+0x20] [ebp-0x258]
  int nVal; // [esp+0x24] [ebp-0x254] BYREF
  char *v17; // [esp+0x28] [ebp-0x250]
  unsigned int v18; // [esp+0x2C] [ebp-0x24C]
  int v19; // [esp+0x30] [ebp-0x248]
  PalScript *v20; // [esp+0x34] [ebp-0x244]
  char pszBuf[16]; // [esp+0x38] [ebp-0x240] BYREF
  Config v22; // [esp+0x48] [ebp-0x230] BYREF
  int v23; // [esp+0x274] [ebp-0x4]
((TxtFile *)(&v22.m_ptr_4 + 5))->TxtFile::TxtFile();
  v23 = 0;
  (((PalScript *)(&v22.m_ptr_4 + 5)))->PalScript::LoadFromFile((char *)pathAddr);
  (((PalScript *)(&v22.m_ptr_4 + 5)))->PalScript::SetDirectory("pal3lang");
  LOBYTE(p_DWORD) = v11;
  (((std::string *)0))->_Tidy();
  for ( LOBYTE(v23) = 1; (((PalScript *)(&v22.m_ptr_4 + 5)))->PalScript::HasNext(); v19 = 0 )
  {
    if ( !_strcmpi((const char *)&v22.m_ptr_4 + 20, g_LanguageCode) )
      break;
    v2 = strlen((const char *)&v22.m_ptr_4 + 20) + 1;
    v3 = v2 - 1;
    if ( (((SceneObj *)&p_DWORD))->SceneObj::UpdateAutoDelete(v2 - 1) )
    {
      qmemcpy(v13, &v22.m_ptr_4 + 5, v3);
      v14 = v2 - 1;
      v13[v3] = 0;
    }
    (((PalScript *)(&v22.m_ptr_4 + 5)))->PalScript::LoadNext();
    LOBYTE(nVal) = v11;
    (((std::string *)0))->_Tidy();
    v4 = strlen((const char *)&v22.m_ptr_4 + 20) + 1;
    v5 = v4 - 1;
    if ( (((SceneObj *)&nVal))->SceneObj::UpdateAutoDelete(v4 - 1) )
    {
      qmemcpy(v17, &v22.m_ptr_4 + 5, v5);
      v18 = v4 - 1;
      v17[v5] = 0;
    }
    LOBYTE(v23) = 2;
    pszBuf[0] = p_DWORD;
    (((std::string *)0))->_Tidy();
    (((PalScript *)pszBuf))->PalScript::InitScriptObj(&p_DWORD, 0, 0xFFFFFFFF);
    LOBYTE(v23) = 3;
    (((Config *)&v22))->Config::ParseSection((int)&nVal);
    LOBYTE(v23) = 4;
    (((PalScript *)this))->PalScript::EvalExpression((int *)&v22.m_ptr_4 + 3, pszBuf);
    LOBYTE(v23) = 5;
    (((std::string *)1))->_Tidy();
    LOBYTE(v23) = 2;
    (((std::string *)1))->_Tidy();
    LOBYTE(v23) = 1;
    if ( v17 )
    {
      v6 = (char *)(v17 - 1);
      v7 = *(v17 - 1);
      if ( !v7 || v7 == -1 )
        operator delete(v6);
      else
        *v6 = v7 - 1;
    }
    v17 = 0;
    v18 = 0;
  }
  if ( v13 )
  {
    v8 = (char *)(v13 - 1);
    v9 = *(v13 - 1);
    if ( !v9 || v9 == -1 )
      operator delete(v8);
    else
      *v8 = v9 - 1;
  }
  v13 = 0;
  v14 = 0;
  v15 = 0;
  v23 = -1;
  (((PalScript *)(&v22.m_ptr_4 + 5)))->PalScript::Cleanup();
  return result;
}

// 0x00430500
void PalScript::ReleaseFrame()
{
  int m_nFrameCount; // eax
  _BYTE *v3; // ecx
  char v4; // al
  scScriptInstance *m_pinst; // eax
  _BYTE *v6; // ecx
  char uservar_high; // al

  m_nFrameCount = this->m_nFrameCount;
  if ( m_nFrameCount )
  {
    v3 = (_BYTE *)(m_nFrameCount - 1);
    v4 = *(_BYTE *)(m_nFrameCount - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  this->m_nFrameCount = 0;
  this->m_CamObj = ((PtrArray *)0);
  this->m_fScriptTimer = 0.0f;
  m_pinst = (scScriptInstance *)this->m_pinst;
  if ( m_pinst )
  {
    v6 = (char *)&m_pinst[-1].uservar + 3;
    uservar_high = HIBYTE(m_pinst[-1].uservar);
    if ( uservar_high && uservar_high != -1 )
    {
      *v6 = uservar_high - 1;
      this->m_pinst = ((scScriptInstance *)0);
      this->m_waitobj = ((PtrArray *)0);
      this->m_fBlendFactor = 0.0f;
      return;
    }
    operator delete(v6);
  }
  this->m_pinst = ((scScriptInstance *)0);
  this->m_waitobj = ((PtrArray *)0);
  this->m_fBlendFactor = 0.0f;
}

// 0x00430570
char * PalScript::SetAppName(char *name)
{
  char *v3; // esi
  unsigned int v4; // kr04_4
  unsigned int v5; // ebx
  char *v6; // eax
  scScriptInstance *m_pinst; // ecx
  char **p_name; // eax
  char *v9; // esi
  char *v10; // esi
  char *result; // eax
  scScriptInstance *v12; // [esp+0x10] [ebp-0x24] BYREF
  int pOut; // [esp+0x14] [ebp-0x20] BYREF
  int nIdx; // [esp+0x18] [ebp-0x1C] BYREF
  char *v15; // [esp+0x1C] [ebp-0x18]
  unsigned int v16; // [esp+0x20] [ebp-0x14]
  int v17; // [esp+0x30] [ebp-0x4]

  LOBYTE(nIdx) = (_BYTE)name;
  (((std::string *)0))->_Tidy();
  v3 = (char *)name;
  v4 = strlen(name) + 1;
  v5 = v4 - 1;
  if ( (((SceneObj *)&nIdx))->SceneObj::UpdateAutoDelete(v4 - 1) )
  {
    qmemcpy(v15, v3, v5);
    v16 = v4 - 1;
    v15[v5] = 0;
  }
  v17 = 0;
  v6 = (char *)*this->PalScript::GetVarRef(&pOut, (int)&nIdx);
  m_pinst = (scScriptInstance *)this->m_pinst;
  name = v6;
  if ( v6 == (char *)m_pinst || (((PalScript *)&nIdx))->PalScript::CompareBuffer((int)(v6 + 12)) < 0 )
  {
    v12 = (scScriptInstance *)this->m_pinst;
    p_name = (char **)&v12;
  }
  else
  {
    p_name = (char **)&name;
  }
  v9 = (char *)*p_name;
  v17 = -1;
  (((std::string *)1))->_Tidy();
  if ( v9 == (char *)this->m_pinst )
    return "LANG_NULL";
  v10 = (char *)*((_DWORD *)v9 + 8);
  result = (char *)&g_bActorFlag;
  if ( v10 )
    return v10;
  return result;
}

// 0x004307D0
int PalScript::InitScriptObj(int *p_DWORD, unsigned int dwVal, unsigned int dwVal2)
{
  unsigned int v4; // esi
  PtrArray *v6; // ebx
  int v7; // edi
  PtrArray *v8; // ebx
  char *v9; // eax
  PtrArray *v10; // esi
  scScriptInstance *m_pinst; // eax
  PtrArray *v12; // edi
  PtrArray *m_waitobj; // eax
  char *v14; // esi
  unsigned __int8 *v16; // eax
  scScriptInstance *v17; // eax
  _BYTE *v18; // ecx
  char v19; // al
  unsigned __int8 *v20; // eax
  scScriptInstance *v21; // ecx
  char uservar_high; // al
  float m_fBlendFactor; // eax
  unsigned __int8 *v24; // eax
  scScriptInstance *v25; // ecx

  v4 = dwVal;
  if ( p_DWORD[2] < dwVal )
    std::_Xran();
  v6 = (PtrArray *)(p_DWORD[2] - dwVal);
  if ( dwVal2 < (unsigned int)v6 )
    v6 = (PtrArray *)dwVal2;
  if ( this == (PalScript *)p_DWORD )
  {
    v7 = -1;
    v8 = (PtrArray *)((char *)v6 + dwVal);
    if ( this->m_waitobj < v8 )
      std::_Xran();
    (((GRPinput *)this))->_Split();
    v9 = (char *)((char *)this->m_waitobj - (char *)v8);
    if ( v9 != (char *)-1 )
      v7 = (char *)this->m_waitobj - (char *)v8;
    if ( v7 )
    {
      memcpy((char *)v8 + (unsigned int)this->m_pinst, (char *)v8 + (unsigned int)this->m_pinst + v7, (size_t)&v9[-v7]);
      v10 = (PtrArray *)((char *)this->m_waitobj - v7);
      if ( (((SceneObj *)this))->SceneObj::UpdateAutoDelete((unsigned int)v10) /* [ROWTABLE] */ )
      {
        m_pinst = (scScriptInstance *)this->m_pinst;
        this->m_waitobj = ((PtrArray *)(v10));
        *((_BYTE *)&m_pinst->pblock + (_DWORD)v10) = 0;
      }
      v4 = dwVal;
    }
    v12 = (PtrArray *)v4;
    (((GRPinput *)this))->_Split();
    m_waitobj = (PtrArray *)this->m_waitobj;
    if ( (unsigned int)m_waitobj < v4 )
      v12 = (PtrArray *)this->m_waitobj;
    if ( v12 )
    {
      memcpy(this->m_pinst, (char *)this->m_pinst + (unsigned int)v12, (char *)m_waitobj - (char *)v12);
      v14 = (char *)((char *)this->m_waitobj - (char *)v12);
      if ( (((SceneObj *)this))->SceneObj::UpdateAutoDelete((unsigned int)v14) /* [ROWTABLE] */ )
      {
        (((std::string *)v14))->_Eos();
        return (int)this;
      }
    }
    return (int)this;
  }
  if ( !v6 || v6 != (PtrArray *)p_DWORD[2] )
    goto LABEL_32;
  v16 = (unsigned __int8 *)p_DWORD[1];
  if ( !v16 )
    v16 = (unsigned __int8 *)&g_bActorFlag;
  if ( *(v16 - 1) >= 0xFEu )
  {
LABEL_32:
    if ( /* [MISATTRIBUTED] std::string::max_size on PalScript::this -> fix IDB name of callee */ std::string::max_size(this) < (unsigned int)v6 )
      std::_Xlen();
    v21 = (scScriptInstance *)this->m_pinst;
    if ( v21 && (uservar_high = HIBYTE(v21[-1].uservar)) != 0 && uservar_high != -1 )
    {
      if ( !v6 )
      {
        HIBYTE(v21[-1].uservar) = uservar_high - 1;
        (((std::string *)0))->_Tidy();
        return (int)this;
      }
    }
    else
    {
      if ( !v6 )
      {
        (((std::string *)1))->_Tidy();
        return (int)this;
      }
      m_fBlendFactor = this->m_fBlendFactor;
      if ( LODWORD(m_fBlendFactor) <= 0x1F && LODWORD(m_fBlendFactor) >= (unsigned int)v6 )
        goto LABEL_45;
      (((std::string *)1))->_Tidy();
    }
    (((GRPinput *)this))->GRPinput::PollInputState((unsigned int)v6);
LABEL_45:
    v24 = (unsigned __int8 *)p_DWORD[1];
    if ( !v24 )
      v24 = (unsigned __int8 *)&g_bActorFlag;
    qmemcpy(this->m_pinst, &v24[dwVal], (unsigned int)v6);
    v25 = (scScriptInstance *)this->m_pinst;
    this->m_waitobj = ((PtrArray *)(v6));
    *((_BYTE *)&v25->pblock + (_DWORD)v6) = 0;
    return (int)this;
  }
  v17 = (scScriptInstance *)this->m_pinst;
  if ( v17 )
  {
    v18 = (char *)&v17[-1].uservar + 3;
    v19 = HIBYTE(v17[-1].uservar);
    if ( !v19 || v19 == -1 )
      operator delete(v18);
    else
      *v18 = v19 - 1;
  }
  this->m_pinst = ((scScriptInstance *)0);
  this->m_waitobj = ((PtrArray *)0);
  this->m_fBlendFactor = 0.0f;
  v20 = (unsigned __int8 *)p_DWORD[1];
  if ( !v20 )
    v20 = (unsigned __int8 *)&g_bActorFlag;
  this->m_pinst = ((scScriptInstance *)((scScriptInstance *)v20));
  this->m_waitobj = ((PtrArray *)((PtrArray *)p_DWORD[2]));
  LODWORD(this->m_fBlendFactor) = (unsigned long)p_DWORD[3];
  ++*(v20 - 1);
  return (int)this;
}

// 0x004309D0
int * PalScript::EvalExpression(int *p_DWORD, char *pszBuf)
{
  scScriptInstance *m_pinst; // ebp
  bool v5; // al
  PalScript *v6; // esi
  char *v7; // edi
  unsigned __int8 *m_nState; // eax
  char m_waitobj; // cl
  int v10; // ecx
  int *result; // eax
  int v12; // edx
  int *v13; // eax
  int *v14; // ecx
  int *v15; // [esp-0x8] [ebp-0x44]
  _BYTE *v16; // [esp+0x0] [ebp-0x3C]
  _BYTE a2[5]; // [esp+0x13] [ebp-0x29] BYREF
  int v18; // [esp+0x18] [ebp-0x24] BYREF
  int v19; // [esp+0x1C] [ebp-0x20]
  char v20; // [esp+0x20] [ebp-0x1C] BYREF
  char v21; // [esp+0x28] [ebp-0x14] BYREF
  int v22; // [esp+0x38] [ebp-0x4]

  m_pinst = (scScriptInstance *)this->m_pinst;
  v5 = 1;
  v6 = (PalScript *)(*(PalScript **)&m_pinst->runmode);
  v7 = (char *)pszBuf;
  v22 = 0;
  while ( v6 != g_ScriptSystemData.m_pCurrentBlock )
  {
    m_nState = (unsigned __int8 *)v6->m_nState;
    m_pinst = (scScriptInstance *)v6;
    if ( !m_nState )
      m_nState = (unsigned __int8 *)&g_bActorFlag;
    v5 = (int)(((std::string *)0))->_Grow(*((_DWORD *)v7 + 2), m_nState, v6->m_nFrameCount) < 0;
    if ( v5 )
      v6 = (PalScript *)(*(void **)(v6));
    else
      v6 = (PalScript *)v6->m_waitobj;
  }
  m_waitobj = (char)this->m_waitobj;
  v22 = -1;
  if ( m_waitobj )
    goto LABEL_9;
  *(_DWORD *)&a2[1] = (_DWORD)m_pinst;
  if ( v5 )
  {
    if ( m_pinst == (scScriptInstance *)this->m_pinst->pblock )
    {
LABEL_9:
      v10 = *this->PalScript::EvalExprTree((int *)&pszBuf, v6, (int *)m_pinst, v7);
      result = (int *)p_DWORD;
      LOBYTE(v19) = 1;
      v12 = v19;
      *p_DWORD = v10;
      p_DWORD[1] = v12;
      return result;
    }
    (((PalScript *)&a2[1]))->PalScript::IteratorNext();
  }
  if ( (((PalScript *)(*(_DWORD *)&a2[1] + 12)))->PalScript::CompareBuffer((int)v7) >= 0 )
  {
    a2[0] = 0;
    v13 = (int *)(((PalScript *)&v21))->PalScript::sub_430C10(&a2[1], a2, v16);
  }
  else
  {
    LOBYTE(pszBuf) = 1;
    v15 = (int *)this->PalScript::EvalExprTree(&v18, v6, (int *)m_pinst, v7);
    v13 = (int *)(((PalScript *)&v20))->PalScript::sub_430C10(v15, &pszBuf, v16);
  }
  v14 = (int *)v13;
  result = (int *)p_DWORD;
  *p_DWORD = *v14;
  p_DWORD[1] = v14[1];
  return result;
}

// 0x00430C10
_BYTE * PalScript::sub_430C10(_BYTE *thisa, _DWORD *a2, _BYTE *a3)
{
  _BYTE *result; // eax
(*(void **)(this)) = (void *)(*(void **)thisa);
  LOBYTE(this->m_pinst) = *(_BYTE *)a2;
  return result;
}

// 0x00431040
int * PalScript::GetVarRef(int *pOut, int nIdx)
{
  *pOut = (int)this->PalScript::ResolveScope(nIdx);
  return pOut;
}

// 0x00431100
int * PalScript::EvalExprTree(int *p_DWORD, void *pData, int *p_DWORD2, char *pszBuf)
{
  void *v6; // ebp
  PalScript *v7; // ecx
  int *m_pinst; // eax
  scScriptInstance *v9; // eax
  int *v10; // eax
  scScriptInstance *v11; // eax
  scScriptInstance **v12; // ecx
  scScriptInstance *v13; // esi
  scScriptInstance **pblock; // edx
  scScriptInstance *pcaller; // edx
  scScriptInstance **v16; // ecx
  scScriptInstance *v17; // edx
  scScriptInstance **v18; // edx
  scScriptInstance *v19; // ecx
  scScriptInstance **v20; // edx
  PalScript *v21; // esi
  scScriptInstance *v22; // esi
  scScriptInstance ***v23; // esi
  scScriptInstance *v24; // ecx
  PalScript *v25; // edx
  scScriptInstance *v26; // edx
  scScriptInstance **v27; // edx
  scScriptInstance *v28; // esi
  scScriptInstance **v29; // esi
  int *result; // eax

  v6 = (void *)operator new(0x30u);
  *((_DWORD *)v6 + 1) = (unsigned long)p_DWORD2;
  *((_DWORD *)v6 + 11) = 0;
  *(_DWORD *)v6 = (_DWORD)g_ScriptSystemData.m_pCurrentBlock;
  v7 = (PalScript *)g_ScriptSystemData.m_pCurrentBlock;
  *((_DWORD *)v6 + 2) = (unsigned long)g_ScriptSystemData.m_pCurrentBlock;
  (((PalScript *)v7))->PalScript::ConstructStringObj((char *)v6 + 12);
  m_pinst = (int *)this->m_pinst;
  ++LODWORD(this->m_fBlendFactor);
  if ( p_DWORD2 == m_pinst
    || pData != g_ScriptSystemData.m_pCurrentBlock
    || (((PalScript *)pszBuf))->PalScript::CompareBuffer((int)(p_DWORD2 + 3)) < 0 )
  {
    *p_DWORD2 = (int)v6;
    v10 = (int *)this->m_pinst;
    if ( p_DWORD2 == v10 )
    {
      v10[1] = (int)v6;
      this->m_pinst->pcaller = ((scScriptInstance *)((scScriptInstance *)v6));
    }
    else if ( p_DWORD2 == (int *)*v10 )
    {
      *v10 = (int)v6;
    }
  }
  else
  {
    p_DWORD2[2] = (int)v6;
    v9 = (scScriptInstance *)this->m_pinst;
    if ( p_DWORD2 == (int *)v9->pcaller )
      v9->pcaller = (scScriptInstance *)v6;
  }
  v11 = (scScriptInstance *)v6;
  if ( v6 != *(void **)&this->m_pinst->runmode )
  {
    do
    {
      v12 = (scScriptInstance **)(*(scScriptInstance ***)&v11->runmode);
      if ( v12[11] )
        break;
      v13 = (scScriptInstance *)v12[1];
      pblock = (scScriptInstance **)v13->pblock;
      if ( v12 == (scScriptInstance **)v13->pblock )
      {
        pcaller = (scScriptInstance *)v13->pcaller;
        if ( LODWORD(pcaller->reg[3].data.as_int) )
        {
          if ( v11 == v12[2] )
          {
            v11 = (scScriptInstance *)(*(scScriptInstance **)&v11->runmode);
            v16 = (scScriptInstance **)v12[2];
            v11->pcaller = *v16;
            if ( *v16 != (scScriptInstance *)g_ScriptSystemData.m_pCurrentBlock )
              *(_DWORD *)&(*v16)->runmode = (_DWORD)v11;
            v16[1] = *(scScriptInstance **)&v11->runmode;
            v17 = (scScriptInstance *)this->m_pinst;
            if ( v11 == *(scScriptInstance **)&v17->runmode )
            {
              *(_DWORD *)&v17->runmode = (unsigned long)v16;
            }
            else
            {
              v18 = (scScriptInstance **)(*(scScriptInstance ***)&v11->runmode);
              if ( v11 == *v18 )
                *v18 = (scScriptInstance *)v16;
              else
                v18[2] = (scScriptInstance *)v16;
            }
            *v16 = v11;
            *(_DWORD *)&v11->runmode = (unsigned long)v16;
          }
          *(_DWORD *)(*(_DWORD *)&v11->runmode + 44) = 1;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v11->runmode + 4) + 44) = 0;
          v19 = (scScriptInstance *)*(scScriptInstance **)(*(_DWORD *)&v11->runmode + 4);
          v20 = (scScriptInstance **)v19->pblock;
          v19->pblock = *(scScriptBlock **)&v19->pblock->desc[4];
          v21 = (PalScript *)v20[2];
          if ( v21 != g_ScriptSystemData.m_pCurrentBlock )
            v21->m_pinst = v19;
          v20[1] = *(scScriptInstance **)&v19->runmode;
          v22 = (scScriptInstance *)this->m_pinst;
          if ( v19 == *(scScriptInstance **)&v22->runmode )
          {
            *(_DWORD *)&v22->runmode = (unsigned long)v20;
            v20[2] = v19;
          }
          else
          {
            v23 = (scScriptInstance ***)(*(scScriptInstance ****)&v19->runmode);
            if ( v19 == (scScriptInstance *)v23[2] )
              v23[2] = v20;
            else
              *v23 = v20;
            v20[2] = v19;
          }
LABEL_51:
          *(_DWORD *)&v19->runmode = (unsigned long)v20;
          continue;
        }
        v12[11] = (scScriptInstance *)1;
        LODWORD(pcaller->reg[3].data.as_int) = 1;
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v11->runmode + 4) + 44) = 0;
        v11 = (scScriptInstance *)*(scScriptInstance **)(*(_DWORD *)&v11->runmode + 4);
      }
      else
      {
        if ( pblock[11] )
        {
          if ( v11 == *v12 )
          {
            v11 = (scScriptInstance *)(*(scScriptInstance **)&v11->runmode);
            v24 = (scScriptInstance *)*v12;
            v11->pblock = (scScriptBlock *)v24->pcaller;
            v25 = (PalScript *)v24->pcaller;
            if ( v25 != g_ScriptSystemData.m_pCurrentBlock )
              v25->m_pinst = v11;
            *(_DWORD *)&v24->runmode = *(_DWORD *)&v11->runmode;
            v26 = (scScriptInstance *)this->m_pinst;
            if ( v11 == *(scScriptInstance **)&v26->runmode )
            {
              *(_DWORD *)&v26->runmode = (_DWORD)v24;
            }
            else
            {
              v27 = (scScriptInstance **)(*(scScriptInstance ***)&v11->runmode);
              if ( v11 == v27[2] )
                v27[2] = v24;
              else
                *v27 = v24;
            }
            v24->pcaller = v11;
            *(_DWORD *)&v11->runmode = (_DWORD)v24;
          }
          *(_DWORD *)(*(_DWORD *)&v11->runmode + 44) = 1;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v11->runmode + 4) + 44) = 0;
          v19 = (scScriptInstance *)*(scScriptInstance **)(*(_DWORD *)&v11->runmode + 4);
          v20 = (scScriptInstance **)v19->pcaller;
          v19->pcaller = *v20;
          if ( *v20 != (scScriptInstance *)g_ScriptSystemData.m_pCurrentBlock )
            *(_DWORD *)&(*v20)->runmode = (_DWORD)v19;
          v20[1] = *(scScriptInstance **)&v19->runmode;
          v28 = (scScriptInstance *)this->m_pinst;
          if ( v19 == *(scScriptInstance **)&v28->runmode )
          {
            *(_DWORD *)&v28->runmode = (unsigned long)v20;
          }
          else
          {
            v29 = (scScriptInstance **)(*(scScriptInstance ***)&v19->runmode);
            if ( v19 == *v29 )
              *v29 = (scScriptInstance *)v20;
            else
              v29[2] = (scScriptInstance *)v20;
          }
          *v20 = v19;
          goto LABEL_51;
        }
        v12[11] = (scScriptInstance *)1;
        pblock[11] = (scScriptInstance *)1;
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v11->runmode + 4) + 44) = 0;
        v11 = (scScriptInstance *)*(scScriptInstance **)(*(_DWORD *)&v11->runmode + 4);
      }
    }
    while ( v11 != *(scScriptInstance **)&this->m_pinst->runmode );
  }
  *(_DWORD *)(*(_DWORD *)&this->m_pinst->runmode + 44) = 1;
  result = (int *)p_DWORD;
  *p_DWORD = (int)v6;
  return result;
}

// 0x00431390
int * PalScript::ResolveScope(int nVal)
{
  int *result; // eax
  int v3; // ebp
  unsigned int v4; // eax
  unsigned __int8 *v5; // ecx
  unsigned __int8 *v6; // edi
  unsigned int v7; // ebx
  int v8; // ecx
  int v9; // edx
  bool v10; // sf
  int *v11; // [esp+0x4] [ebp-0x10]
  int nVala; // [esp+0x18] [ebp+0x4]

  result = (int *)this->m_pinst;
  v11 = (int *)result;
  v3 = (unsigned long)result[1];
  if ( (PalScript *)v3 != g_ScriptSystemData.m_pCurrentBlock )
  {
    v4 = *(_DWORD *)(nVal + 8);
    v5 = (unsigned __int8 *)*(unsigned __int8 **)(nVal + 4);
    for ( nVala = (int)v5; ; v5 = (unsigned __int8 *)nVala )
    {
      v6 = (unsigned __int8 *)&g_bActorFlag;
      if ( v5 )
        v6 = (unsigned __int8 *)v5;
      v7 = *(_DWORD *)(v3 + 20);
      v8 = v7;
      if ( v7 >= v4 )
        v8 = v4;
      v9 = memcmp(*(const char **)(v3 + 16), (const char *)v6, v8);
      v10 = v9 < 0;
      if ( !v9 )
      {
        if ( v7 < v4 )
          goto LABEL_12;
        LOBYTE(v9) = v7 != v4;
        v10 = v9 < 0;
      }
      if ( v10 )
      {
LABEL_12:
        v3 = *(_DWORD *)(v3 + 8);
        goto LABEL_14;
      }
      v11 = (int *)v3;
      v3 = *(_DWORD *)v3;
LABEL_14:
      if ( (PalScript *)v3 == g_ScriptSystemData.m_pCurrentBlock )
        return v11;
    }
  }
  return result;
}

// 0x00431440
int * PalScript::IteratorNext()
{
  void *vftable; // eax
  int *result; // eax
  int *scalar_dtor; // edx

  vftable = (*(void **)(this));
  if ( this->__vftable[2]._scalar_dtor_4D50 || *((void **)vftable->IsProgressDone + 1) != vftable )
  {
    scalar_dtor = (int *)vftable->_scalar_dtor;
    if ( (PalScript *)vftable->_scalar_dtor == g_ScriptSystemData.m_pCurrentBlock )
    {
      for ( result = (int *)vftable->IsProgressDone; (*(void **)(this)) == (void *)*result; result = (int *)result[1] )
        (*(void **)(this)) = (void *)result;
      (*(void **)(this)) = (void *)result;
    }
    else
    {
      for ( result = (int *)scalar_dtor[2]; result != (int *)g_ScriptSystemData.m_pCurrentBlock; result = (int *)result[2] )
        scalar_dtor = (int *)result;
      (*(void **)(this)) = (void *)scalar_dtor;
    }
  }
  else
  {
    result = (int *)vftable->UpdateProgress;
    (*(void **)(this)) = (void *)result;
  }
  return result;
}

// 0x004314A0
int * PalScript::IteratorPrev()
{
  int *UpdateProgress; // edx
  int *result; // eax

  UpdateProgress = (int *)this->__vftable->UpdateProgress;
  if ( UpdateProgress == (int *)g_ScriptSystemData.m_pCurrentBlock )
  {
    for ( result = (int *)this->__vftable->IsProgressDone;
          (*(void **)(this)) == (void *)result[2];
          result = (int *)result[1] )
    {
      (*(void **)(this)) = (void *)result;
    }
    if ( (int *)this->__vftable->UpdateProgress != result )
      (*(void **)(this)) = (void *)result;
  }
  else
  {
    for ( result = (int *)*UpdateProgress; result != (int *)g_ScriptSystemData.m_pCurrentBlock; result = (int *)*result )
      UpdateProgress = (int *)result;
    (*(void **)(this)) = (void *)UpdateProgress;
  }
  return result;
}

// 0x004314F0
void PalScript::ConstructStringObj(char *pszBuf)
{
  char v2; // al
  unsigned int v3; // ebp
  unsigned __int8 *v4; // eax
  unsigned __int8 *v5; // eax
  unsigned __int8 *v6; // esi
  int *p_DWORD; // [esp+0x28] [ebp+0x8]

  if ( pszBuf )
  {
    v2 = *(_BYTE *)p_DWORD;
    *((_DWORD *)pszBuf + 1) = 0;
    *pszBuf = v2;
    *((_DWORD *)pszBuf + 2) = 0;
    *((_DWORD *)pszBuf + 3) = 0;
    (((PalScript *)pszBuf))->PalScript::InitScriptObj(p_DWORD, 0, 0xFFFFFFFF);
    pszBuf[16] = *((_BYTE *)p_DWORD + 16);
    *((_DWORD *)pszBuf + 5) = 0;
    *((_DWORD *)pszBuf + 6) = 0;
    *((_DWORD *)pszBuf + 7) = 0;
    v3 = (unsigned long)p_DWORD[6];
    if ( pszBuf + 16 == (char *)(p_DWORD + 4) )
    {
      (((PalScript *)(pszBuf + 16)))->PalScript::SetWaitRange(v3, 0xFFFFFFFF);
      (((PalScript *)(pszBuf + 16)))->PalScript::SetWaitRange(0, 0);
    }
    else
    {
      if ( !v3 )
        goto LABEL_17;
      v4 = (unsigned __int8 *)p_DWORD[5];
      if ( !v4 )
        v4 = (unsigned __int8 *)&g_bActorFlag;
      if ( *(v4 - 1) < 0xFEu )
      {
        *((_DWORD *)pszBuf + 5) = 0;
        *((_DWORD *)pszBuf + 6) = 0;
        *((_DWORD *)pszBuf + 7) = 0;
        v5 = (unsigned __int8 *)p_DWORD[5];
        if ( !v5 )
          v5 = (unsigned __int8 *)&g_bActorFlag;
        *((_DWORD *)pszBuf + 5) = (unsigned long)v5;
        *((_DWORD *)pszBuf + 6) = (unsigned long)p_DWORD[6];
        *((_DWORD *)pszBuf + 7) = (unsigned long)p_DWORD[7];
        ++*(v5 - 1);
      }
      else
      {
LABEL_17:
        if ( (((SceneObj *)(pszBuf + 16)))->SceneObj::UpdateAutoDelete(v3) )
        {
          v6 = (unsigned __int8 *)&g_bActorFlag;
          if ( p_DWORD[5] )
            v6 = (unsigned __int8 *)p_DWORD[5];
          qmemcpy(*((void **)pszBuf + 5), v6, v3);
          (((std::string *)v3))->_Eos();
        }
      }
    }
  }
}

// 0x00431640
int PalScript::SetWaitRange(unsigned int dwVal, unsigned int dwVal2)
{
  scScriptInstance *m_pinst; // esi
  char uservar_high; // al
  scScriptInstance *v6; // edi
  unsigned int v7; // ebx
  char *v8; // edi
  char *v9; // eax
  PtrArray *v10; // esi
  scScriptInstance *v11; // ecx
  char v12; // al
  int result; // eax
  scScriptInstance *v14; // ecx

  if ( this->m_waitobj < (PtrArray *)dwVal )
    std::_Xran();
  m_pinst = (scScriptInstance *)this->m_pinst;
  if ( m_pinst )
  {
    uservar_high = HIBYTE(m_pinst[-1].uservar);
    if ( uservar_high )
    {
      if ( uservar_high != -1 )
      {
        v6 = (scScriptInstance *)this->m_pinst;
        HIBYTE(m_pinst[-1].uservar) = uservar_high - 1;
        this->m_pinst = ((scScriptInstance *)0);
        this->m_waitobj = ((PtrArray *)0);
        this->m_fBlendFactor = 0.0f;
        v7 = strlen((const char *)v6);
        if ( (((SceneObj *)this))->SceneObj::UpdateAutoDelete(v7) /* [ROWTABLE] */ )
        {
          qmemcpy(this->m_pinst, m_pinst, v7);
          (((std::string *)v7))->_Eos();
        }
      }
    }
  }
  v8 = (char *)dwVal2;
  v9 = (char *)this->m_waitobj - dwVal;
  if ( (unsigned int)v9 < dwVal2 )
    v8 = (char *)this->m_waitobj - dwVal;
  if ( !v8 )
    return (int)this;
  memcpy((char *)this->m_pinst + dwVal, (char *)this->m_pinst + dwVal + (unsigned int)v8, v9 - v8);
  v10 = (PtrArray *)((char *)this->m_waitobj - v8);
  if ( (unsigned int)v10 > 0xFFFFFFFD )
    std::_Xlen();
  v11 = (scScriptInstance *)this->m_pinst;
  if ( v11 )
  {
    v12 = HIBYTE(v11[-1].uservar);
    if ( v12 )
    {
      if ( v12 != -1 )
      {
        if ( !v10 )
        {
          HIBYTE(v11[-1].uservar) = v12 - 1;
          (((std::string *)0))->_Tidy();
          return (int)this;
        }
        goto LABEL_22;
      }
    }
  }
  if ( v10 )
  {
    if ( LODWORD(this->m_fBlendFactor) >= (unsigned int)v10 )
    {
LABEL_23:
      v14 = (scScriptInstance *)this->m_pinst;
      this->m_waitobj = ((PtrArray *)(v10));
      *((_BYTE *)&v14->pblock + (_DWORD)v10) = 0;
      return (int)this;
    }
LABEL_22:
    (((GRPinput *)this))->GRPinput::PollInputState((char *)this->m_waitobj - v8);
    goto LABEL_23;
  }
  if ( v11 )
  {
    this->m_waitobj = ((PtrArray *)0);
    result = (int)this;
    LOBYTE(v11->pblock) = 0;
    return result;
  }
  return (int)this;
}

// 0x00431780
int PalScript::CompareBuffer(int nDescriptor)
{
  unsigned int v3; // ebx
  unsigned __int8 *v4; // eax
  PtrArray *v5; // edx
  PtrArray *m_waitobj; // ecx
  int result; // eax

  v3 = *(_DWORD *)(nDescriptor + 8);
  v4 = (unsigned __int8 *)*(unsigned __int8 **)(nDescriptor + 4);
  if ( !v4 )
    v4 = (unsigned __int8 *)&g_bActorFlag;
  m_waitobj = (PtrArray *)this->m_waitobj;
  v5 = (PtrArray *)m_waitobj;
  if ( (unsigned int)m_waitobj >= v3 )
    m_waitobj = (PtrArray *)*(PtrArray **)(nDescriptor + 8);
  result = memcmp((const char *)this->m_pinst, (const char *)v4, (int)m_waitobj);
  if ( !result )
  {
    if ( (unsigned int)v5 >= v3 )
      return v5 != (PtrArray *)v3;
    else
      return -1;
  }
  return result;
}

// 0x004318A0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void PalScript::Cleanup()
{
  this->PalScript::FreeLoadBuffer();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x004318B0
void * PalScript::LoadFromFile(char *filename)
{
  gbVFile *v3; // eax
  gbVFile *v4; // esi
  unsigned int v5; // ebp
  void *v6; // edi
  void *result; // eax
  OpenBaseFile v8; // [esp+0x34] [ebp-0x10] BYREF
  int v9; // [esp+0x40] [ebp-0x4]

  this->PalScript::FreeLoadBuffer();
  v9 = 0;
  v3 = (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::OpenFile(filename, 0x201u);
  v4 = (gbVFile *)v3;
  if ( v3 )
  {
    (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v3, 0, 3);
    v5 = (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::TellPos(v4);
    (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v4, 0, 1);
    v6 = (void *)malloc(v5 + 1);
    this->m_RoleSlotArray.overlay.m_nLoadFromFile = (int)v6;
    if ( v6 )
    {
      memset(v6, 0, v5 + 1);
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read((void *)this->m_RoleSlotArray.overlay.m_nLoadFromFile, v5, v4);
      this->m_RoleSlotArray.overlay.m_nLoadState = this->m_RoleSlotArray.overlay.m_nLoadFromFile;
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::CloseFile(v4);
    }
  }
  v9 = -1;
  ((OpenNULLFile *)&v8)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x004319C0
void PalScript::FreeLoadBuffer()
{
  if ( this->m_RoleSlotArray.overlay.m_nLoadFromFile )
  {
    free((void *)this->m_RoleSlotArray.overlay.m_nLoadFromFile);
    this->m_RoleSlotArray.overlay.m_nLoadFromFile = 0;
  }
  this->m_RoleSlotArray.overlay.m_nLoadState = 0;
  this->m_RoleSlotArray.overlay.m_nNext = 0;
}

// 0x004319F0
int PalScript::SetDirectory(char *dir)
{
  BOOL v3; // edi
  int result; // eax

  v3 = 0;
  this->m_RoleSlotArray.overlay.m_nNext = this->m_RoleSlotArray.overlay.m_nLoadFromFile;
  for ( result = this->PalScript::HasNext(); result; result = this->PalScript::HasNext() )
  {
    if ( v3 )
    {
      result = _strcmpi((const char *)this, dir);
      if ( !result )
      {
        this->m_RoleSlotArray.overlay.m_nLoadState = this->m_RoleSlotArray.overlay.m_nNext;
        return result;
      }
      v3 = 0;
    }
    else
    {
      v3 = _strcmpi((const char *)this, "Begin") == 0;
    }
  }
  return result;
}

// 0x00431A60
int PalScript::HasNext()
{
  int v2; // ecx
  PalScript *v3; // esi
  char v4; // al
  char v5; // al
  _BYTE *v6; // eax

  memset(this, 0, 0x200u);
  v2 = 0;
  if ( *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext )
  {
do
    {
      if ( v2 > 2 )
      {
        if ( v2 != 3 )
          return 1;
        if ( *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext == 38 )
          goto LABEL_30;
      }
      else
      {
        if ( v2 == 2 )
        {
          v5 = *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext;
          if ( v5 == 59 )
          {
            v2 = 1;
          }
          else if ( v5 == 10 || v5 == 32 || v5 == 9 || v5 == 44 )
          {
            v2 = 255;
          }
          else if ( v5 != 13 )
          {
            LOBYTE((*(void **)(v3))) = v5;
            v3 = (PalScript *)((char *)this + 1);
          }
          goto LABEL_31;
        }
        if ( !v2 )
        {
          v4 = *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext;
          if ( v4 == 36 )
          {
            v2 = 3;
          }
          else if ( v4 == 59 )
          {
            v2 = 1;
          }
          else if ( v4 != 32 && v4 != 9 && v4 != 44 && v4 != 13 && v4 != 10 )
          {
            LOBYTE((*(void **)(v3))) = v4;
            v3 = (PalScript *)((char *)this + 1);
            v2 = 2;
          }
          goto LABEL_31;
        }
        if ( *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext == 10 )
LABEL_30:
          v2 = 0;
      }
LABEL_31:
      v6 = (_BYTE *)(this->m_RoleSlotArray.overlay.m_nNext + 1);
      this->m_RoleSlotArray.overlay.m_nNext = (int)v6;
    }
    while ( *v6 );
  }
  return 0;
}

// 0x00431B60
int PalScript::LoadNext()
{
  int result; // eax
  PalScript *v3; // esi
  char v4; // cl
  char v5; // cl
  _BYTE *v6; // ecx

  result = 0;
  memset(this, 0, 0x200u);
  if ( *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext )
  {
do
    {
      if ( result > 2 )
        break;
      if ( result == 2 )
      {
        v5 = *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext;
        if ( v5 == 38 )
        {
          result = 255;
        }
        else
        {
          LOBYTE((*(void **)(v3))) = v5;
          v3 = (PalScript *)((char *)this + 1);
        }
      }
      else if ( result )
      {
        result = *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext != 10;
      }
      else
      {
        v4 = *(_BYTE *)this->m_RoleSlotArray.overlay.m_nNext;
        if ( v4 == 59 )
        {
          result = 1;
        }
        else if ( v4 == 36 )
        {
          result = 2;
        }
      }
      v6 = (_BYTE *)(this->m_RoleSlotArray.overlay.m_nNext + 1);
      this->m_RoleSlotArray.overlay.m_nNext = (int)v6;
    }
    while ( *v6 );
  }
  return result;
}

// 0x00431C00
int PalScript::SaveLoadState()
{
  int result; // eax

  result = this->m_RoleSlotArray.overlay.m_nLoadState;
  this->m_RoleSlotArray.overlay.m_nNext = result;
  return result;
}

// 0x00431C10
char PalScript::FindSaveStateString(
        
        PalScript *String1,
        char *String2,
        char *Destination,
        int nVal)
{
  int v6; // edi

  this->PalScript::SaveLoadState();
  v6 = 0;
  while ( 1 )
  {
    if ( !this->PalScript::HasNext() )
      return 0;
    if ( !_strcmpi((const char *)this, (const char *)String1) )
      break;
    if ( _strcmpi((const char *)this, byte_592DA4) )
    {
      if ( ++v6 < 1024 )
        continue;
    }
    return 0;
  }
  this->PalScript::LoadNext();
  strncpy(String2, (const char *)this, (size_t)(Destination - 1));
  return 1;
}

// 0x00431D20
void PalScript::CleanupInstances()
{
  int i; // edi
  int v3; // ecx

  if ( this->m_pinst )
  {
    FreeScriptInstance((int *)this->m_pinst);
    this->m_pinst = ((scScriptInstance *)0);
  }
  for ( i = 0; i < SLODWORD(this->m_fBlendFactor); ++i )
  {
    if ( i < 0 || i >= SLODWORD(this->m_fBlendFactor) )
      v3 = 0;
    else
      v3 = *((_DWORD *)&this->m_waitobj->m_pData + i);
    if ( *(_DWORD *)(v3 + 4) && v3 )
      (**(void ( ***)(int, int))v3)((int)(v3), (int)(1));
  }
  (((String *)&this->m_waitobj))->String::Assign(0, -1);
}

// 0x00431D80
void PalScript::_StaticInit()
{
  SingletonThunk_00431D90(this);
  atexit(SingletonThunk_00431DB0);
}

// 0x00431F00
void PalScript::AddWaitObj()
{
  this->PalScript::AddCamObj();
  atexit(ClearAllCamObj);
}

// 0x00431F10
int PalScript::AddCamObj()
{
  int result; // eax

  g_ScriptSystemData.m_nCmdFA0 = HIBYTE(this);
  result = 0;
  g_ScriptSystemData.m_nScriptState = 0;
  g_ScriptSystemData.m_nCmdFA8 = 0;
  g_ScriptSystemData.m_pScriptData = ((char *)0);
  return result;
}

// 0x00431FA0
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void PalScript::ClearAllWaitObj()
{
  (((PalScriptMgr *)this))->PalScriptMgr::_CON_ReLoadScript();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00431FB0
void PalScript::Update()
{
  int v1; // eax
  int v2; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x800] BYREF
  char ArgList[1024]; // [esp+0x408] [ebp-0x400] BYREF

  (((PalScriptMgr *)this))->PalScriptMgr::_CON_ReLoadScript();
  if ( !LoadScriptFile(pszFileName) )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException("Script sys init failed.", "D:\\Project\\PAL3\\script\\PalScript.cpp", 71),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (((PtrArray *)&unk_D8C2E8))->PtrArray::InsertAt(pszName);
  if ( !v1 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException("System script load failed.", "D:\\Project\\PAL3\\script\\PalScript.cpp", 73),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (((PtrArray *)&unk_D8C2C8))->PtrArray::InsertAt("ui\\bigmap\\bigmap.sce");
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException("BigMap script load failed.", "D:\\Project\\PAL3\\script\\PalScript.cpp", 75),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x00433F90
int PalScript::ProcessGBKString()
{
  unsigned __int16 *v1; // ecx
  unsigned __int16 v2; // ax
  unsigned __int16 *v3; // ecx
  unsigned __int16 v4; // si
  unsigned int v5; // ebx
  int i; // edi
  char v7; // al
  unsigned __int16 *v8; // eax
  unsigned __int16 v9; // dx
  int v10; // esi
  int v11; // ebp
  char *v12; // eax
  DWORD v13; // eax
  int v14; // edx
  DWORD v15; // eax
  bool v16; // cc
  DWORD v17; // eax
  int v18; // edx
  char bOwned; // [esp+0xC] [ebp-0x10]
  unsigned __int16 v21; // [esp+0x10] [ebp-0xC]
  int nInitSize; // [esp+0x14] [ebp-0x8] BYREF
  int v23; // [esp+0x18] [ebp-0x4]

  v1 = (unsigned __int16 *)*(unsigned __int16 **)(g_pLoadBuffer + 8);
  v2 = *v1;
  *(_DWORD *)(g_pLoadBuffer + 8) = (_DWORD)v1 + 1;
  v3 = (unsigned __int16 *)*(unsigned __int16 **)(g_pLoadBuffer + 8);
  v4 = *v3;
  v5 = 16 * v2;
  *(_DWORD *)(g_pLoadBuffer + 8) = (_DWORD)v3 + 1;
  v21 = v4;
  for ( i = (unsigned __int16)word_D8C474[v5 / 2] - 1; i >= 0; --i )
  {
    v7 = byte_D8C46C[v5 + i];
    if ( v7 == -6 )
    {
      v8 = (unsigned __int16 *)*(unsigned __int16 **)(g_pLoadBuffer + 8);
      v9 = *v8;
      *(_DWORD *)(g_pLoadBuffer + 8) = (_DWORD)v8 + 1;
      v10 = v9;
      if ( v9 )
      {
        v11 = v9;
        do
        {
          v12 = (char *)*(char **)(g_pLoadBuffer + 8);
          bOwned = *v12;
          *(_DWORD *)(g_pLoadBuffer + 8) = (_DWORD)v12 + 1;
          (((PtrArray *)g_pLoadBuffer))->PtrArray::_todo_434130((int)&nInitSize, g_pLoadBuffer, bOwned);
          v13 = ++g_ScriptSystemData.m_nScriptResult;
          if ( (int)g_ScriptSystemData.m_nScriptResult >= 32 )
          {
            g_ScriptSystemData.m_nScriptResult = 31;
          }
          else
          {
            v14 = v23;
            g_ScriptSystemData.m_nTodo_104C[2 * v13] = nInitSize;
            (&g_ScriptSystemData.m_nTodo_1050)[2 * dword_D8C360]mData.m_nScriptResult] = v14;
          }
          --v11;
        }
        while ( v11 );
      }
      v23 = v10;
      v15 = g_ScriptSystemData.m_nScriptResult + 1;
      HIWORD(nInitSize) = 4;
      v16 = (int)(g_ScriptSystemData.m_nScriptResult + 1) < 32;
      LOBYTE(nInitSize) = 1;
      ++g_ScriptSystemData.m_nScriptResult;
      if ( !v16 )
      {
LABEL_16:
        g_ScriptSystemData.m_nScriptResult = 31;
        continue;
      }
      g_ScriptSystemData.m_nTodo_104C[2 * v15] = nInitSize;
      (&g_ScriptSystemData.m_nTodo_1050)[2 * dword_D8C360]mData.m_nScriptResult] = v10;
    }
    else
    {
      if ( (v21 & (unsigned __int16)(1 << i)) != 0 )
        (((PtrArray *)&nInitSize))->PtrArray::_todo_434130((int)&nInitSize, g_pLoadBuffer, 5);
      else
        (((PtrArray *)i))->PtrArray::_todo_434130((int)&nInitSize, g_pLoadBuffer, v7);
      v17 = ++g_ScriptSystemData.m_nScriptResult;
      if ( (int)g_ScriptSystemData.m_nScriptResult >= 32 )
        goto LABEL_16;
      v18 = v23;
      g_ScriptSystemData.m_nTodo_104C[2 * v17] = nInitSize;
      (&g_ScriptSystemData.m_nTodo_1050)[2 * dword_D8C360]mData.m_nScriptResult] = v18;
    }
  }
  return ((int (*)(void))g_ScriptSystemData.m_CmdTable[v5 / 4])();
}

// 0x00434C00
char * PalScript::GetString()
{
  char *result; // eax

  if ( (g_ScriptSystemData.m_nScriptResult & 0x80000000) != 0 )
  {
    result = 0;
  }
  else
  {
    --g_ScriptSystemData.m_nScriptResult;
    result = (char *)(8 * g_ScriptSystemData.m_nScriptResult + 14205804);
  }
  if ( result )
  {
    if ( *result == 5 )
      return PtrArray::SetAtGrow(*((_WORD *)result + 2), 0);
  }
  return result;
}

// 0x00434CE0
void PalScript::Op_Idle()
{
  char *String; // esi
  float *v2; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    v2 = (float *)operator new(0x10u);
    if ( v2 )
    {
      v2[2] = *((float *)String + 1);
      v2[3] = 0.0;
      *((_DWORD *)v2 + 1) = 1;
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00434D70
void PalScript::Op_ScriptRunMode()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    *(_BYTE *)(g_pLoadBuffer + 4) = String[4];
}

// 0x00434D90
void PalScript::Op_RolePathOut()
{
  char *String; // edi

  char *v3; // ebx

  char *v5; // eax
  char *v6; // ebp
  RoleSystem *SceneObject; // eax
  RoleSystem *v8; // esi

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v6 = (char *)v5;
  if ( String )
  {
    if ( v3 )
    {
      if ( v5 )
      {
        SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
        v8 = (RoleSystem *)SceneObject;
        if ( SceneObject )
        {
          if ( SceneObject == &g_RoleSystemMain )
          {
            if ( unk_C08160.m_partyActor.m_pRoleObj )
            {
              SceneObject->m_partyActor.m_nState = unk_C08160.m_partyActor.m_nState;
            }
            else if ( SceneObject->m_partyActor.m_nState >= *(_DWORD *)((Object *)&UISceneUpdate()->m_roles[50]) )
            {
              v8->m_partyActor.m_nState = 0;
            }
          }
          if ( *((_DWORD *)String + 1) < 5u && (((RoleSystem *)v8))->RoleSystem::IsPathMoving() )
            (((RoleSystem *)v8))->RoleSystem::AllocPathPage(*((_DWORD *)v3 + 1), *((_DWORD *)v6 + 1));
          else
            (((RoleSystem *)v8))->RoleSystem::CalcTileDistance(*((_DWORD *)v3 + 1), *((_DWORD *)v6 + 1));
        }
      }
    }
  }
}

// 0x00434E50
char * PalScript::Op_RoleScript()
{
  char *String; // esi

  char *result; // eax
  char *v4; // edi

  String = (char *)this->PalScript::GetString();
  result = (char *)this->PalScript::GetString();
  v4 = (char *)result;
  if ( String && result )
  {
    result = (char *)GetSceneObject(*((_WORD *)String + 2));
    if ( result )
      *((_DWORD *)result + 157) = *((_DWORD *)v4 + 1);
  }
  return result;
}

// 0x00434E90
char * PalScript::Op_RoleCtrl()
{
  char *String; // esi

  char *result; // eax
  char *v4; // edi

  String = (char *)this->PalScript::GetString();
  result = (char *)this->PalScript::GetString();
  v4 = (char *)result;
  if ( String && result )
  {
    result = (char *)GetSceneObject(*((_WORD *)String + 2));
    if ( result )
      return (char *)(((RoleSystem *)result))->RoleSystem::ResetPathParams(*((_DWORD *)v4 + 1));
  }
  return result;
}

// 0x00434ED0
void PalScript::Op_RolePathOutToTile()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // eax
  char *v8; // ebp
  RoleSystem *SceneObject; // esi

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  v8 = (char *)v7;
  if ( String )
  {
    if ( v3 )
    {
      if ( v5 )
      {
        if ( v7 )
        {
          SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
          if ( SceneObject )
          {
            if ( *((_DWORD *)v8 + 1) == 1 )
              (((RoleSystem *)SceneObject))->RoleSystem::MoveToTileCheck(*((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1), 2);
            else
              (((RoleSystem *)SceneObject))->RoleSystem::MoveToTileCheck(*((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1), 1);
            SceneObject->m_nMoveRole = 0;
            SceneObject->m_nCollisionState = 1;
            PalScriptMgr::NotifyEvent();
          }
        }
      }
    }
  }
}

// 0x00434F90
void PalScript::Op_RolePathTo()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // eax
  char *v8; // ebp
  RoleSystem *SceneObject; // esi
  int v10; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  v8 = (char *)v7;
  if ( String && v3 && v5 && v7 )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      v10 = ConvertDirection(*((_DWORD *)v8 + 1));
      (((RoleSystem *)SceneObject))->RoleSystem::MoveToTileCheck(*((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1), v10);
      SceneObject->m_nMoveRole = 0;
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00435010
void PalScript::Op_TeamCloseA()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // eax
  char *v8; // ebp
  RoleSystem *SceneObject; // esi
  int v10; // eax
  __int64 v11; // [esp-0xC] [ebp-0x1C]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  v8 = (char *)v7;
  if ( String && v3 && v5 && v7 )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      v10 = ConvertDirection(*((_DWORD *)v8 + 1));
      HIDWORD(v11) = *((_DWORD *)v5 + 1);
      LODWORD(v11) = *((_DWORD *)v3 + 1);
      (((RoleSystem *)SceneObject))->RoleSystem::MoveToTile(v11, v10);
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00435080
void PalScript::Op_RoleSetPos()
{
  char *String; // esi

  char *v3; // ebp

  char *v5; // eax
  char *v6; // ebx
  RoleSystem *SceneObject; // eax
  int v8; // esi

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v6 = (char *)v5;
  if ( String )
  {
    if ( v3 )
    {
      if ( v5 )
      {
        SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
        if ( SceneObject )
        {
          v8 = *((_DWORD *)v6 + 1);
          if ( v8 )
          {
            (((RoleSystem *)SceneObject))->RoleSystem::PlayAction(*((char **)v3 + 1), *((_DWORD *)v6 + 1));
            if ( v8 > 0 || v8 == -2 )
              PalScriptMgr::NotifyEvent();
          }
        }
      }
    }
  }
}

// 0x004350F0
char * PalScript::Op_RoleOverlap()
{
  char *String; // esi

  char *result; // eax
  char *v4; // edi

  String = (char *)this->PalScript::GetString();
  result = (char *)this->PalScript::GetString();
  v4 = (char *)result;
  if ( String && result )
  {
    result = (char *)GetSceneObject(*((_WORD *)String + 2));
    if ( result )
      *((_DWORD *)result + 319) = *((_DWORD *)v4 + 1);
  }
  return result;
}

// 0x00435130
void PalScript::CmdGetSceneObject()
{
  char *String; // eax
  RoleSystem *SceneObject; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      (((RoleSystem *)SceneObject))->RoleSystem::StopAndResetPath();
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00435170
void PalScript::Op_GetDislike()
{
  char *String; // eax
  RoleSystem *SceneObject; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
      (((RoleSystem *)SceneObject))->RoleSystem::Notify();
  }
}

// 0x004351A0
void PalScript::Op_RoleActive()
{
  char *String; // esi

  char *v3; // eax
  int v4; // edx
  unsigned __int8 *v5; // ecx
  int v6; // ecx
  int v7; // eax
  char *v8; // [esp-0x8] [ebp-0x118]
  char *v9; // [esp-0x4] [ebp-0x114]
  char v10; // [esp+0x7] [ebp-0x109]
  int *v11; // [esp+0x8] [ebp-0x108]
  unsigned __int16 v12; // [esp+0xC] [ebp-0x104]
  char Buffer[256]; // [esp+0x10] [ebp-0x100] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    v4 = 0;
    v11 = (int *)&byte_1010101;
    v5 = (unsigned __int8 *)&g_RoleSlotBuf.m_nAnimCopy2 + 2;
    v12 = (unsigned __int16)&byte_1010101;
    do
    {
      if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v4) )
        *(&v10 + *v5) = 0;
      v5 += 1408;
      ++v4;
    }
    while ( (int)v5 < (int)byte_C0649E );
    v6 = 0;
    while ( !*((_BYTE *)&v11 + v6)
         || !*((_DWORD *)v3 + 1)
         || *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + *((_DWORD *)String + 1)) )
    {
      if ( ++v6 >= 6 )
        goto LABEL_14;
    }
    *((_BYTE *)&g_RoleSlotBuf.m_nAnimCopy2 + 1408 * *((_DWORD *)String + 1) + 2) = v6 + 1;
LABEL_14:
    *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + *((_DWORD *)String + 1)) = *((_DWORD *)v3 + 1) != 0;
    v7 = *((_DWORD *)String + 1);
    if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v7) )
    {
      v9 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName((char *)(&off_56ABA4)[v7]);
      v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("AddTeam");
    }
    else
    {
      v9 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName((char *)(&off_56ABA4)[v7]);
      v8 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("RemoveTeam");
    }
    _snprintf(Buffer, 0xFFu, v8, v9);
    InputSystem::ProcessFrame(Buffer);
  }
}

// 0x004352D0
char * PalScript::Op_RoleScriptInitCam()
{
  char *String; // esi

  char *v3; // edi

  char *result; // eax
  float pParams[3]; // [esp+0x8] [ebp-0xC] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  result = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    if ( result )
    {
      pParams[0] = *((float *)String + 1);
      pParams[1] = *((float *)v3 + 1);
      pParams[2] = *((float *)result + 1);
      return (char *)(((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::InitParams(pParams);
    }
  }
  return result;
}

// 0x00435320
void PalScript::Op_RoleActiveShort()
{
  char *String; // eax
  void *SceneObject; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    SceneObject = GetSceneObject(*((_WORD *)String + 2));
    (((_Console *)g_pCameraCtrl))->_Console::SetActive((int)SceneObject);
  }
}

// 0x004353A0
void PalScript::Op_InTeam()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    if ( v5 )
    {
      (((CameraCtrl *)&g_GameData))->CameraCtrl::SetupFollow((int)g_pCameraCtrl, *((_DWORD *)String + 1), *((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1));
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x004353F0
void PalScript::Op_RoleSetLayer()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // eax
  int nVal2; // [esp+0x0] [ebp-0x1C]
  int nVal3; // [esp+0x4] [ebp-0x18]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 )
  {
    if ( v7 )
    {
      *(float *)&nVal3 = *((float *)v3 + 1) * 0.017453292;
      *(float *)&nVal2 = *((float *)String + 1) * 0.017453292;
      (((CameraCtrl *)&g_GameData))->CameraCtrl::SetupOrbit((int)g_pCameraCtrl, nVal2, nVal3, *((_DWORD *)v5 + 1), *((_DWORD *)v7 + 1));
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00435470
void PalScript::Op_RoleOverlapEx()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // eax
  int nVal2; // [esp+0x0] [ebp-0x1C]
  int nVal3; // [esp+0x4] [ebp-0x18]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 )
  {
    if ( v7 )
    {
      *(float *)&nVal3 = *((float *)v3 + 1) * 0.017453292;
      *(float *)&nVal2 = *((float *)String + 1) * 0.017453292;
      (((CameraCtrl *)&g_GameData))->CameraCtrl::SetupTrack((int)g_pCameraCtrl, nVal2, nVal3, *((_DWORD *)v5 + 1), *((_DWORD *)v7 + 1));
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x004354F0
void PalScript::Op_RoleCtrlEx()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // ebp

  char *v9; // eax
  int v10; // eax
  int v11; // ecx
  int p_DWORD[3]; // [esp+0x10] [ebp-0xC] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  v9 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 )
  {
    if ( v7 )
    {
      v10 = *((_DWORD *)v9 + 1);
      v11 = *((_DWORD *)v7 + 1);
      p_DWORD[0] = *((int *)String + 1);
      p_DWORD[1] = *((int *)v3 + 1);
      p_DWORD[2] = *((int *)v5 + 1);
      (((CameraCtrl *)&g_GameData))->CameraCtrl::SetupLerp((int)g_pCameraCtrl, p_DWORD, v11, v10);
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00435570
void PalScript::Op_RoleScale()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // ebp


  char *v10; // eax
  int nMode; // [esp+0x0] [ebp-0x30]
  int nStart; // [esp+0x4] [ebp-0x2C]
  char *v13; // [esp+0x2C] [ebp-0x4]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  v13 = (char *)this->PalScript::GetString();
  v10 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 && v7 && v13 )
  {
    if ( v10 )
    {
      *(float *)&nStart = *((float *)v3 + 1) * 0.017453292;
      *(float *)&nMode = *((float *)String + 1) * 0.017453292;
      (((InputSystem *)g_pCameraCtrl))->InputSystem::SetCameraTransition(nMode, nStart, *((_DWORD *)v5 + 1), *((_DWORD *)v7 + 1), *((_DWORD *)v13 + 1), *((_DWORD *)v10 + 1), 1);
    }
  }
}

// 0x00435600
void PalScript::Op_CameraPush()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // ebp



  char *v11; // eax
  int v12; // eax
  int v13; // edx
  int nVal2; // [esp+0x0] [ebp-0x38]
  int nVal3; // [esp+0x4] [ebp-0x34]
  char *v16; // [esp+0x24] [ebp-0x14]
  char *v17; // [esp+0x28] [ebp-0x10]
  int p_DWORD[3]; // [esp+0x2C] [ebp-0xC] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  v16 = (char *)this->PalScript::GetString();
  v17 = (char *)this->PalScript::GetString();
  v11 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 && v7 && v16 && v17 )
  {
    if ( v11 )
    {
      p_DWORD[0] = *((int *)v7 + 1);
      v12 = *((_DWORD *)v11 + 1);
      v13 = *((_DWORD *)v5 + 1);
      p_DWORD[1] = *((int *)v16 + 1);
      p_DWORD[2] = *((int *)v17 + 1);
      *(float *)&nVal3 = *((float *)v3 + 1) * 0.017453292;
      *(float *)&nVal2 = *((float *)String + 1) * 0.017453292;
      (((CameraCtrl *)&g_GameData))->CameraCtrl::SmoothTransition((int)g_pCameraCtrl, nVal2, nVal3, v13, p_DWORD, v12);
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x004356C0
void PalScript::Op_ShowActAutoStand()
{
  char *String; // esi

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    UISceneUpdate();
    (((_Console *)g_pCameraCtrl))->_Console::SetActive((int)g_pRoleSystem);
    (((ScriptPoolPage *)g_pCameraCtrl))->ScriptPoolPage::ScriptPoolPage_Manage(*((_DWORD *)String + 1));
    *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) = 1;
  }
}

// 0x00435710
void PalScript::Op_RoleMoveBack()
{
  (((RoleSystem *)g_pCameraCtrl))->RoleSystem::AddCameraKeyframe();
}

// 0x00435720
void PalScript::Op_RoleFaceRole()
{
  int v1; // [esp+0x4] [ebp+0x4]

  RoleCamera_PushState(v1);
}

// 0x00435730
void PalScript::Op_RoleTurnFaceA()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    if ( v5 )
      *((_DWORD *)String + 1) = ScriptSystem::GetScriptContext(*((_WORD *)v3 + 2), *((_DWORD *)v5 + 1));
  }
}

// 0x00435770
void PalScript::Op_TeamOpenA()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    if ( v5 )
      ScriptSystem::PassThrough(*((_WORD *)String + 2), *((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1));
  }
}

// 0x004357B0
void PalScript::Op_CameraPushState()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      ScriptSystem::CheckEventType(*((_WORD *)String + 2), *((_DWORD *)v3 + 1));
  }
}

// 0x004357E0
void PalScript::Op_CameraFocusRole()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax
  char *v6; // ebx
  int ScriptContext; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v6 = (char *)v5;
  if ( String && v3 )
  {
    if ( v5 )
    {
      ScriptContext = ScriptSystem::GetScriptContext(*((_WORD *)String + 2), *((_DWORD *)v3 + 1));
      ScriptSystem::PassThrough(*((_WORD *)String + 2), *((_DWORD *)v3 + 1), ScriptContext + *((_DWORD *)v6 + 1));
    }
  }
}

// 0x00435830
void PalScript::Op_CameraFocusPoint()
{
  char *pszItemParam; // esi

  char *pszCountParam; // eax
  char *pSkillData; // eax
  int nAttrIdx; // eax
  int nCurAttrVal; // ecx
  int nMaxAttrVal; // edx
  int nItemType; // eax
  int *p_m_obbox; // ecx
  char *pszEventName; // eax
  ScreenEffectMgr *pScrEffMgr; // ecx
  ScreenEffect *pScrEffect; // eax
  CScreenMode *pScrMode; // eax
  char *nNextEventID; // [esp-0x4] [ebp-0x124]
  int nSkillGDB_ID; // [esp+0x8] [ebp-0x118] BYREF
  int nSkillCount; // [esp+0xC] [ebp-0x114]
  void *pSkillResult; // [esp+0x10] [ebp-0x110]
  int nItemGDB_ID; // [esp+0x14] [ebp-0x10C] BYREF
  int nItemCount; // [esp+0x18] [ebp-0x108]
  char *pSkillDataStored; // [esp+0x1C] [ebp-0x104]
  char szEventName[256]; // [esp+0x20] [ebp-0x100] BYREF

  pszItemParam = (char *)this->PalScript::GetString();
  pszCountParam = (char *)this->PalScript::GetString();
  if ( pszItemParam )
  {
    if ( pszCountParam )
    {
      nItemGDB_ID = 0xFFFF;
      nItemCount = 0;
      pSkillDataStored = 0;
      nItemGDB_ID = *((_DWORD *)pszItemParam + 1);
      nItemCount = *((_DWORD *)pszCountParam + 1);
      pSkillData = (char *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nItemGDB_ID);
      pSkillDataStored = (char *)pSkillData;
      if ( pSkillData )
      {
        if ( pSkillData[612] == 11 && pSkillData[614] )
        {
          if ( g_RoleSlotBuf.m_partyActor.m_pSelfAtt )
          {
            pSkillResult = (void *)g_RoleSlotBuf.m_partyActor.m_pSelfAtt;
            nSkillGDB_ID = g_RoleSlotBuf.m_partyActor.m_obbox;
            nSkillCount = 1;
            if ( *(_DWORD *)g_RoleSlotBuf.m_partyActor.m_pSelfAtt == 6603 )
            {
              (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nItemGDB_ID);
            }
            else if ( *(_DWORD *)g_RoleSlotBuf.m_partyActor.m_pSelfAtt != 6602 || *(_DWORD *)pSkillData == 6603 )
            {
              (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nSkillGDB_ID);
              g_RoleSlotBuf.m_partyActor.m_obbox = nItemGDB_ID;
              *(&g_RoleSlotBuf.m_partyActor.m_obbox + 1) = nItemCount;
              g_RoleSlotBuf.m_partyActor.m_pSelfAtt = ((void *)((void *)pSkillDataStored));
            }
          }
          else
          {
            g_RoleSlotBuf.m_partyActor.m_obbox = nItemGDB_ID;
            *(&g_RoleSlotBuf.m_partyActor.m_obbox + 1) = nItemCount;
            g_RoleSlotBuf.m_partyActor.m_pSelfAtt = ((void *)((void *)pSkillData));
          }
          (((RoleSystem *)&g_RoleSlotBuf))->RoleSystem::RecalcAggregatedStats(0);
          for ( nAttrIdx = 972; nAttrIdx < 1020; nAttrIdx += 4 )
          {
            nCurAttrVal = *(_DWORD *)((char *)((UIWnd *)&g_RoleSlotBuf) + nAttrIdx);
            nMaxAttrVal = *(int *)((char *)&g_nSceneFlags.m_pDataStart + nAttrIdx);
            if ( nCurAttrVal < nMaxAttrVal )
            {
              if ( nCurAttrVal <= 0 )
                *(_DWORD *)((char *)((UIWnd *)&g_RoleSlotBuf) + nAttrIdx) = 0;
            }
            else
            {
              *(_DWORD *)((char *)((UIWnd *)&g_RoleSlotBuf) + nAttrIdx) = nMaxAttrVal;
            }
          }
          goto LABEL_35;
        }
        nItemType = *(_DWORD *)pSkillData;
        switch ( nItemType )
        {
          case 6119:
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nItemGDB_ID);
            nSkillGDB_ID = 8146;
            nSkillCount = 1;
            pSkillResult = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8146);
            p_m_obbox = (int *)&nSkillGDB_ID;
            break;
          case 6120:
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nItemGDB_ID);
            nSkillGDB_ID = 8147;
            nSkillCount = 1;
            pSkillResult = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8147);
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nSkillGDB_ID);
            goto LABEL_35;
          case 6122:
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nItemGDB_ID);
            nSkillGDB_ID = 8149;
            nSkillCount = 1;
            pSkillResult = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8149);
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nSkillGDB_ID);
            goto LABEL_35;
          case 6123:
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nItemGDB_ID);
            nSkillGDB_ID = 8150;
            nSkillCount = 1;
            pSkillResult = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8150);
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nSkillGDB_ID);
            nSkillGDB_ID = 6427;
            nSkillCount = 1;
            pSkillResult = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(6427);
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nSkillGDB_ID);
            goto LABEL_35;
          case 6124:
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nItemGDB_ID);
            nSkillGDB_ID = 8151;
            nSkillCount = 1;
            pSkillResult = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8151);
            p_m_obbox = (int *)&nSkillGDB_ID;
            break;
          case 6125:
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nItemGDB_ID);
            nSkillGDB_ID = 8152;
            nSkillCount = 1;
            pSkillResult = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8152);
            (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&nSkillGDB_ID);
            goto LABEL_35;
          default:
            p_m_obbox = (int *)&nItemGDB_ID;
            break;
        }
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(p_m_obbox);
LABEL_35:
        nNextEventID = (char *)(pSkillDataStored + 4);
        pszEventName = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("getitem");
        _snprintf(szEventName, 0xFFu, pszEventName, nNextEventID);
        InputSystem::ProcessFrame(szEventName);
        pScrEffect = (((ScreenEffectMgr *)pScrEffMgr))->ScreenEffectMgr::GetInstance();
        if ( !(((ScreenEffectMgr *)pScrEffect))->ScreenEffectMgr::IsFadeWhiteHolding() )
        {
          pScrMode = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)pScrMode))->CScreenMode::AudioSetPosition("wa006", 1);
        }
      }
    }
  }
}

// 0x00435BF0
void PalScript::Op_LoseItem()
{
  char *String; // eax
  _DWORD *SkillNum; // eax
  void **p_m_pSelfAtt; // ecx
  _DWORD *v4; // edx
  _DWORD *v5; // edx
  _DWORD *v6; // edx
  _DWORD *v7; // edx
  _DWORD *v8; // edx
  int v9; // eax
  _DWORD *v10; // edx
  RoleAtt **v11; // eax
  RoleAtt *v12; // ecx
  _DWORD *v13; // edx
  RoleAtt **v14; // eax
  RoleAtt *v15; // ecx
  _DWORD *v16; // edx
  RoleAtt **v17; // eax
  RoleAtt *v18; // ecx
  RoleAtt **v19; // eax
  RoleAtt *v20; // ecx
  _DWORD *v21; // edx
  RoleAtt **v22; // eax
  RoleAtt *v23; // ecx
  _DWORD *v24; // edx
  RoleAtt **v25; // eax
  RoleAtt *v26; // ecx
  char *v27; // eax
  ScreenEffectMgr *v28; // ecx
  ScreenEffect *Instance; // eax
  CScreenMode *v30; // eax
  _DWORD *v31; // [esp-0x8] [ebp-0x128]
  int v32; // [esp+0x8] [ebp-0x118] BYREF
  int v33; // [esp+0xC] [ebp-0x114]
  int v34; // [esp+0x10] [ebp-0x110]
  int p_DWORD; // [esp+0x14] [ebp-0x10C] BYREF
  int v36; // [esp+0x18] [ebp-0x108]
  _DWORD *v37; // [esp+0x1C] [ebp-0x104]
  char Buffer[256]; // [esp+0x20] [ebp-0x100] BYREF

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    p_DWORD = 0xFFFF;
    v36 = 0;
    v37 = 0;
    p_DWORD = *((_DWORD *)String + 1);
    v36 = 1;
    SkillNum = (_DWORD *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_DWORD);
    v37 = (_DWORD *)SkillNum;
    if ( SkillNum )
    {
      p_m_pSelfAtt = (void **)&g_RoleSlotBuf.m_partyActor.m_pSelfAtt;
      do
      {
        if ( *p_m_pSelfAtt && *(_DWORD *)*p_m_pSelfAtt == *SkillNum )
        {
          *(p_m_pSelfAtt - 2) = 0;
          *p_m_pSelfAtt = 0;
          *(p_m_pSelfAtt - 1) = 0;
        }
        v4 = *(p_m_pSelfAtt - 12);
        if ( v4 && *v4 == *SkillNum )
        {
          *(p_m_pSelfAtt - 14) = 0;
          *(p_m_pSelfAtt - 12) = 0;
          *(p_m_pSelfAtt - 13) = 0;
        }
        v5 = *(p_m_pSelfAtt - 15);
        if ( v5 && *v5 == *SkillNum )
        {
          *(p_m_pSelfAtt - 17) = 0;
          *(p_m_pSelfAtt - 15) = 0;
          *(p_m_pSelfAtt - 16) = 0;
        }
        v6 = *(p_m_pSelfAtt - 9);
        if ( v6 && *v6 == *SkillNum )
        {
          *(p_m_pSelfAtt - 11) = 0;
          *(p_m_pSelfAtt - 9) = 0;
          *(p_m_pSelfAtt - 10) = 0;
        }
        v7 = *(p_m_pSelfAtt - 6);
        if ( v7 && *v7 == *SkillNum )
        {
          *(p_m_pSelfAtt - 8) = 0;
          *(p_m_pSelfAtt - 6) = 0;
          *(p_m_pSelfAtt - 7) = 0;
        }
        v8 = *(p_m_pSelfAtt - 3);
        if ( v8 && *v8 == *SkillNum )
        {
          *(p_m_pSelfAtt - 5) = 0;
          *(p_m_pSelfAtt - 3) = 0;
          *(p_m_pSelfAtt - 4) = 0;
        }
        p_m_pSelfAtt += 352;
      }
      while ( (int)p_m_pSelfAtt < (int)&dword_C062B8 );
      v9 = (unsigned long)*SkillNum;
      switch ( v9 )
      {
        case 6119:
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          v32 = 8146;
          v33 = 1;
          v34 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8146);
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v32);
          v10 = (_DWORD *)v34;
          v11 = (RoleAtt **)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[3];
          do
          {
            if ( *v11 && (*v11)->id == *v10 )
            {
              *(v11 - 2) = 0;
              *v11 = 0;
              *(v11 - 1) = 0;
            }
            v12 = (RoleAtt *)v11[3];
            if ( v12 && v12->id == *v10 )
            {
              v11[1] = 0;
              v11[3] = 0;
              v11[2] = 0;
            }
            v11 += 352;
          }
          while ( (int)v11 < (int)&dword_C062A0 );
          break;
        case 6120:
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          v32 = 8147;
          v33 = 1;
          v34 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8147);
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v32);
          v13 = (_DWORD *)v34;
          v14 = (RoleAtt **)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[3];
          do
          {
            if ( *v14 && (*v14)->id == *v13 )
            {
              *(v14 - 2) = 0;
              *v14 = 0;
              *(v14 - 1) = 0;
            }
            v15 = (RoleAtt *)v14[3];
            if ( v15 && v15->id == *v13 )
            {
              v14[1] = 0;
              v14[3] = 0;
              v14[2] = 0;
            }
            v14 += 352;
          }
          while ( (int)v14 < (int)&dword_C062A0 );
          break;
        case 6122:
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          v32 = 8149;
          v33 = 1;
          v34 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8149);
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v32);
          v16 = (_DWORD *)v34;
          v17 = (RoleAtt **)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[3];
          do
          {
            if ( *v17 && (*v17)->id == *v16 )
            {
              *(v17 - 2) = 0;
              *v17 = 0;
              *(v17 - 1) = 0;
            }
            v18 = (RoleAtt *)v17[3];
            if ( v18 && v18->id == *v16 )
            {
              v17[1] = 0;
              v17[3] = 0;
              v17[2] = 0;
            }
            v17 += 352;
          }
          while ( (int)v17 < (int)&dword_C062A0 );
          break;
        case 6123:
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          v32 = 8150;
          v33 = 1;
          v34 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8150);
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v32);
          v32 = 6427;
          v33 = 1;
          v34 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(6427);
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v32);
          v19 = (RoleAtt **)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[3];
          do
          {
            if ( *v19 && (*v19)->id == 8150 )
            {
              *(v19 - 2) = 0;
              *v19 = 0;
              *(v19 - 1) = 0;
            }
            v20 = (RoleAtt *)v19[3];
            if ( v20 && v20->id == 8150 )
            {
              v19[1] = 0;
              v19[3] = 0;
              v19[2] = 0;
            }
            v19 += 352;
          }
          while ( (int)v19 < (int)&dword_C062A0 );
          break;
        case 6124:
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          v32 = 8151;
          v33 = 1;
          v34 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8151);
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v32);
          v21 = (_DWORD *)v34;
          v22 = (RoleAtt **)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[3];
          do
          {
            if ( *v22 && (*v22)->id == *v21 )
            {
              *(v22 - 2) = 0;
              *v22 = 0;
              *(v22 - 1) = 0;
            }
            v23 = (RoleAtt *)v22[3];
            if ( v23 && v23->id == *v21 )
            {
              v22[1] = 0;
              v22[3] = 0;
              v22[2] = 0;
            }
            v22 += 352;
          }
          while ( (int)v22 < (int)&dword_C062A0 );
          break;
        case 6125:
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          v32 = 8152;
          v33 = 1;
          v34 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(8152);
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v32);
          v24 = (_DWORD *)v34;
          v25 = (RoleAtt **)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[3];
          do
          {
            if ( *v25 && (*v25)->id == *v24 )
            {
              *(v25 - 2) = 0;
              *v25 = 0;
              *(v25 - 1) = 0;
            }
            v26 = (RoleAtt *)v25[3];
            if ( v26 && v26->id == *v24 )
            {
              v25[1] = 0;
              v25[3] = 0;
              v25[2] = 0;
            }
            v25 += 352;
          }
          while ( (int)v25 < (int)&dword_C062A0 );
          break;
        default:
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
          break;
      }
      v31 = (_DWORD *)(v37 + 1);
      v27 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("loseitem");
      _snprintf(Buffer, 0xFFu, v27, v31);
      InputSystem::ProcessFrame(Buffer);
      Instance = (((ScreenEffectMgr *)v28))->ScreenEffectMgr::GetInstance();
      if ( !(((ScreenEffectMgr *)Instance))->ScreenEffectMgr::IsFadeWhiteHolding() )
      {
        v30 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v30))->CScreenMode::AudioSetPosition("wa007", 1);
      }
    }
  }
}

// 0x004360F0
void PalScript::Op_RoleSpaceWalk()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      CScreenMode::ProcessGameMode(*((_DWORD *)String + 1), *((_DWORD *)v3 + 1));
  }
}

// 0x00436120
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void PalScript::Op_RoleMoveTo()
{
  this->PalScript::Op_RoleActive();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00436130
unsigned int PalScript::Op_RoleMoveBackEx()
{
  char *String; // edi

  unsigned int result; // eax
  unsigned int v4; // esi
  float fDeltaTime; // [esp+0x0] [ebp-0x14]

  String = (char *)this->PalScript::GetString();
  result = (unsigned int)this->PalScript::GetString();
  v4 = result;
  if ( String )
  {
    if ( result )
    {
      result = *(_DWORD *)(result + 4);
      if ( result < 8 )
      {
        result = (unsigned int)GetSceneObject(*((_WORD *)String + 2));
        if ( result )
        {
          fDeltaTime = (float)(45 * *(_DWORD *)(v4 + 4));
          return (((RoleSystem *)result))->RoleSystem::UpdateMovement(fDeltaTime, 1);
        }
      }
    }
  }
  return result;
}

// 0x00436190
void PalScript::Op_RoleShowAction()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  RoleSystem *SceneObject; // esi
  float fDeltaTime; // [esp+0x0] [ebp-0x14]
  float v7; // [esp+0x4] [ebp-0x10]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String && v3 && *((_DWORD *)v3 + 1) < 8u )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      fDeltaTime = (float)(45 * *((_DWORD *)v4 + 1));
      (((RoleSystem *)SceneObject))->RoleSystem::UpdateMovement(fDeltaTime, 1);
    }
    if ( SceneObject == g_pRoleSystem && *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
    {
      if ( *(_BYTE *)PalScriptMgr::_CON_State((const char *)g_pLoadBuffer) )
      {
        v7 = *(&SceneObject[1].m_partyActor.m_fSpeed + 1) * -0.01745329238474369f;
        ProcessKeyboard_2(LODWORD(v7));
      }
    }
  }
}

// 0x00436240
float * PalScript::Op_RoleScaleEx()
{
  char *String; // esi

  float *result; // eax
  float *v4; // edi

  String = (char *)this->PalScript::GetString();
  result = (float *)this->PalScript::GetString();
  v4 = (float *)result;
  if ( String && result )
  {
    result = (float *)GetSceneObject(*((_WORD *)String + 2));
    if ( result )
      return (float *)(((RoleSystem *)result))->RoleSystem::SetPathWaypoint(v4[1]);
  }
  return result;
}

// 0x00436280
void PalScript::Op_RoleEndAction()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  float *SceneObject; // eax
  float fDeltaTime; // [esp+0x0] [ebp-0x10]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String && v3 )
  {
    SceneObject = (float *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      fDeltaTime = (float)*((int *)v4 + 1) + SceneObject[2172];
      (((RoleSystem *)SceneObject))->RoleSystem::UpdateMovement(fDeltaTime, 1);
    }
  }
}

// 0x004362D0
void PalScript::Op_ShowActAutoStandEx()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  RoleSystem *SceneObject; // esi
  float *v6; // eax
  char *v7; // eax
  float pTargetPos; // [esp+0x8] [ebp-0xC] BYREF
  int v9; // [esp+0xC] [ebp-0x8]
  int v10; // [esp+0x10] [ebp-0x4]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String )
  {
    if ( v3 )
    {
      SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
      v6 = (float *)GetSceneObject(*((_WORD *)v4 + 2));
      if ( SceneObject )
      {
        if ( v6 )
        {
          if ( *((_DWORD *)v4 + 1) == 5 )
          {
            v7 = (char *)(v6 + 40);
            pTargetPos = *(float *)v7;
            v9 = *((_DWORD *)v7 + 1);
            v10 = *((_DWORD *)v7 + 2);
            v9 = 0;
            (((RoleSystem *)SceneObject))->RoleSystem::IsPathComplete(&pTargetPos, 1);
          }
          else
          {
            (((RoleSystem *)SceneObject))->RoleSystem::IsPathComplete(v6 + 1, 1);
          }
        }
      }
    }
  }
}

// 0x00436360
void PalScript::Op_TestGoto()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      *((_DWORD *)String + 1) = *((_DWORD *)v3 + 1);
  }
}

// 0x00436380
void PalScript::Op_Let()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      *((_DWORD *)String + 1) += *((_DWORD *)v3 + 1);
  }
}

// 0x004363B0
void PalScript::Op_AddEx()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      *((_DWORD *)String + 1) -= *((_DWORD *)v3 + 1);
  }
}

// 0x004363E0
void PalScript::Op_GetSwitch()
{
  char *String; // esi

  char *v3; // eax
  int v4; // ecx

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    v4 = *((_DWORD *)String + 1) - *((_DWORD *)v3 + 1);
    *((_DWORD *)String + 1) = v4;
    if ( v4 < 0 )
      *((_DWORD *)String + 1) = -v4;
  }
}

// 0x00436410
void PalScript::Op_Call()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      *((_DWORD *)String + 1) = rand() % *((_DWORD *)v3 + 1);
  }
}

// 0x00436440
void PalScript::Op_LK_Ghost()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      MoveToAbsolute(&g_UISceneMapDlg, *((_DWORD *)String + 1), *((_DWORD *)v3 + 1));
  }
}

// 0x00436470
void PalScript::Op_FavorAdd()
{
  if ( this->PalScript::GetString() )
    (((CEffGroupNode *)&g_UISceneMapDlg))->CEffGroupNode::nullsub();
}

// 0x00436490
void PalScript::Op_Team()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    (((UISceneMap *)&g_UISceneMapDlg))->UISceneMap::LoadCompass(*((const char **)String + 1), 0);
    (**(void ( ***)(UISceneMap *, int))((UIWnd *)&g_UISceneMapDlg))((UISceneMap *)(&g_UISceneMapDlg), (int)(1));
    (*(void ( **)(UISceneMap *, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)&g_UISceneMapDlg) + 8))(
      &g_UISceneMapDlg,
      0,
      0);
    PalScriptMgr::NotifyEvent();
  }
}

// 0x004364E0
void PalScript::Op_AddRoleAtt()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  const char **v5; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String && v3 )
  {
    v5 = (const char **)PalScriptMgr::_CON_State((const char *)g_pLoadBuffer);
    if ( v5 )
      *(_BYTE *)v5 = 1;
    LoadScene(*((char **)String + 1), *((char **)v4 + 1), 1);
  }
}

// 0x00436530
void PalScript::Op_AddItem()
{
  char *String; // esi

  char *v3; // eax
  CCBItemWindow *v4; // esi

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
    {
      v4 = (CCBItemWindow *)(&dword_DBA830 + 88 * *((unsigned __int16 *)String + 2));
      (((CCBItemWindow *)v4))->CCBItemWindow::SetItemName(*((char **)v3 + 1));
      (**(void ( ***)(CCBItemWindow *, int))((UIWnd *)v4))((CCBItemWindow *)(v4), (int)(1));
      (*(void ( **)(CCBItemWindow *, _DWORD, _DWORD))(*(_DWORD *)((UIWnd *)v4) + 8))(v4, 0, 0);
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x004365A0
void PalScript::Op_RoleSetFace()
{
  MovePartyFollowers((char *)1);
}

// 0x004365B0
void PalScript::Op_RoleTurnFace()
{
  RestorePartyFollowMode(1);
}

// 0x004365C0
char PalScript::Op_RoleFaceRoleEx()
{
  return SetupPartyFormation(1);
}

// 0x004365D0
char PalScript::Op_RoleTurnFaceAEx()
{
  return SetupPartyFormationWide(1);
}

// 0x004365E0
void PalScript::Op_TeamOpen()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    CameraCtrl::AttachToRole(*((_DWORD *)String + 1));
}

// 0x00436600
void PalScript::Op_TeamClose()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // ebx
  RoleSystem *SceneObject; // edi
  unsigned int v6; // esi

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String )
  {
    if ( v3 )
    {
      SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
      if ( SceneObject )
      {
        v6 = *((_DWORD *)String + 1);
        if ( v6 >= 5 )
          goto LABEL_9;
        if ( *((_DWORD *)v4 + 1) )
        {
          RoleSystem::ForceStopRole(v6);
          return;
        }
        if ( (((RoleSystem *)SceneObject))->RoleSystem::IsPathMoving() )
          (((RoleSystem *)SceneObject))->RoleSystem::StopPathMovement(*((_DWORD *)v4 + 1));
        else
LABEL_9:
          SceneObject->m_partyActor.m_pRoleObj = *((_DWORD *)v4 + 1);
      }
    }
  }
}

// 0x00436680
void PalScript::Op_RoleInput()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  _DWORD *SceneObject; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String && v3 )
  {
    SceneObject = GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
      SceneObject[66] = *((_DWORD *)v4 + 1);
  }
}

// 0x00436710
void PalScript::Op_GoTo()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    *(_DWORD *)(g_pLoadBuffer + 8) = *((_DWORD *)String + 1) + *(_DWORD *)(*(_DWORD *)g_pLoadBuffer + 72);
}

// 0x00436730
void PalScript::Op_FCZero()
{
  *(_DWORD *)(g_pLoadBuffer + 24) = 0;
}

// 0x00436740
void PalScript::Op_Rand()
{
  *(_DWORD *)(g_pLoadBuffer + 24) = *(_DWORD *)(g_pLoadBuffer + 24) == 0;
}

// 0x00436760
void PalScript::Op_FNOT()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    *(_DWORD *)(g_pLoadBuffer + 16) = *((_DWORD *)String + 1);
}

// 0x00436780
void PalScript::Op_FOP()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      ScriptVM::GetObjectByID(*((_DWORD *)v3 + 1) < *((_DWORD *)String + 1));
  }
}

// 0x004367B0
void PalScript::Op_GT()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      ScriptVM::GetObjectByID(*((_DWORD *)String + 1) < *((_DWORD *)v3 + 1));
  }
}

// 0x004367E0
void PalScript::Op_LS()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      ScriptVM::GetObjectByID(*((_DWORD *)String + 1) == *((_DWORD *)v3 + 1));
  }
}

// 0x00436810
void PalScript::Op_Between()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax
  int v6; // esi

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 )
  {
    v6 = *((_DWORD *)String + 1);
    if ( v6 < *((_DWORD *)v3 + 1) || v6 > *((_DWORD *)v5 + 1) )
      ScriptVM::GetObjectByID(0);
    else
      ScriptVM::GetObjectByID(1);
  }
}

// 0x00436860
void PalScript::Op_EQ()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      ScriptVM::GetObjectByID(*((_DWORD *)String + 1) != *((_DWORD *)v3 + 1));
  }
}

// 0x00436890
void PalScript::Op_NEQ()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      ScriptVM::GetObjectByID(*((_DWORD *)String + 1) >= *((_DWORD *)v3 + 1));
  }
}

// 0x004368C0
void PalScript::Op_Music()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    ScriptVM::GetObjectByID(*((unsigned __int8 *)&g_RoleSlotBuf.m_teamData3[586] + *((_DWORD *)String + 1)));
}

// 0x004368E0
void PalScript::Op_GEQ()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      ScriptVM::GetObjectByID(*((_DWORD *)v3 + 1) >= *((_DWORD *)String + 1));
  }
}

// 0x00436910
void PalScript::Op_LEQ()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( !*(_DWORD *)(g_pLoadBuffer + 24) )
      *(_DWORD *)(g_pLoadBuffer + 8) = *((_DWORD *)String + 1) + *(_DWORD *)(*(_DWORD *)g_pLoadBuffer + 72);
  }
}

// 0x00436940
void PalScript::Op_RemoveItem()
{
  char *String; // esi

  int i; // esi
  char *v4; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    (((UIListBox *)&g_UIListBoxDlg))->UIListBox::ReinitScrollbar();
    for ( i = *((_DWORD *)String + 1) - 1; i >= 0; --i )
    {
      v4 = (char *)this->PalScript::GetString();
      if ( !v4 )
        break;
      (((UIListBox *)&g_UIListBoxDlg))->UIListBox::CalcVisibleRange(*((char **)v4 + 1), 1);
    }
    (**(void ( ***)(UIListBox *, int))((UIWnd *)&g_UIListBoxDlg))((UIListBox *)(&g_UIListBoxDlg), (int)(1));
    PalScriptMgr::NotifyEvent();
  }
}

// 0x004369A0
void PalScript::Op_AddMoney()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    *((_DWORD *)String + 1) = (unsigned long)((UIWnd *)&g_UIListBoxDlg.m_scrollbar);
}

// 0x004369C0
void PalScript::Op_Movie()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 )
  {
    if ( v7 )
      (((CCBEditor *)&g_CCBEditorInst))->CCBEditor::UpdateItemScript(*((CHAR **)String + 1), *((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1), *((_DWORD *)v7 + 1));
  }
}

// 0x00436A10
void PalScript::Op_CEft_Pos()
{
  char *String; // esi
  PalScriptMgr *v2; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)3);
    dword_DBA240 = *((_DWORD *)String + 1);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
      (((PalScriptMgr *)v2))->PalScriptMgr::InitVtable(3);
    PalScriptMgr::NotifyEvent();
  }
}

// 0x00436A60
void PalScript::Op_Sub()
{
  PalScriptMgr *v1; // ecx
  int v2; // eax
  int v3; // esi
  CScreenMode *v4; // ecx
  CScreenMode *v5; // ecx
  PtrArray *SoundList; // eax
  const char **v7; // [esp-0x4] [ebp-0x8]

  if ( this->PalScript::GetString() )
  {
    (((PalScriptMgr *)v1))->PalScriptMgr::Destroy();
    v3 = v2;
    v7 = (const char **)PalScriptMgr::_CON_State((const char *)g_pLoadBuffer);
    (((CScreenMode *)v4))->CScreenMode::GetSoundList();
    if ( (unsigned __int8)sub_53D2F0(v7) )
    {
      SoundList = (((CScreenMode *)v5))->CScreenMode::GetSoundList();
      (((PtrArray *)SoundList))->PtrArray::SetResolution(0, v3);
    }
  }
}

// 0x00436AB0
void PalScript::Op_GetMoney()
{
  char *String; // esi

  char *v3; // ebx

  char *v5; // eax
  char *v6; // ebp
  const char *SceneObject; // eax
  char Buffer[260]; // [esp+0xC] [ebp-0x104] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v6 = (char *)v5;
  if ( String && v3 && v5 )
  {
    memset(Buffer, 0, sizeof(Buffer));
    SceneObject = (const char *)GetSceneObject(*((_DWORD *)String + 1));
    if ( SceneObject )
    {
      sprintf(Buffer, "role\\%s\\%s.tga", SceneObject + 174, *((const char **)v3 + 1));
      (((UIBigMap *)&g_UISceneMapDlg))->UIBigMap::LayoutBinkVideo(Buffer, *((_DWORD *)v6 + 1));
    }
  }
}

// 0x00436B40
void PalScript::Op_TeamCloseAEx()
{
  char *String; // esi
  char *SceneObject; // ebx
  char *v3; // edx
  const char *v4; // edi

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    SceneObject = (char *)GetSceneObject(2u);
    if ( *((_DWORD *)String + 1) )
    {
      LoadActionSequences((Actor *)(SceneObject + 680), a106, 0);
      v3 = (char *)(SceneObject + 174);
      v4 = a106;
    }
    else
    {
      LoadActionSequences((Actor *)(SceneObject + 680), (const char *)&g_pszSceneSlot2, 0);
      v3 = (char *)(SceneObject + 174);
      v4 = (const char *)&g_pszSceneSlot2;
    }
    strcpy(v3, v4);
    (((RoleSystem *)SceneObject))->RoleSystem::UpdateTransform();
  }
}

// 0x00436BD0
void PalScript::Op_GetHS_Period_type()
{
  char *String; // esi

  char *v3; // eax
  unsigned __int8 *v4; // eax
  int v5; // ecx

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
    {
      v4 = (unsigned __int8 *)*((_DWORD *)v3 + 1);
      v5 = *((_DWORD *)String + 1);
      (&g_pSceneTransitionBegin)[v5] = v4;
      *((_BYTE *)&g_pSceneTransitionEnd + v5) = v4 != 0;
    }
  }
}

// 0x00436C00
void PalScript::Op_HY_Mode()
{
  char *String; // eax
  PalScriptMgr *v2; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    (((DealData *)g_PAL3_Instance.m_nTodo_150))->DealData::LoadStoreConfig(*((CHAR **)String + 1));
    (((PAL_GDB *)g_PAL3_Instance.m_nTodo_150))->PAL_GDB::RefreshSkillNumbers();
    (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)2);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
      (((PalScriptMgr *)v2))->PalScriptMgr::InitVtable(2);
    PalScriptMgr::NotifyEvent();
  }
}

// 0x00436C60
void PalScript::Op_FadeNormal()
{
  char *String; // esi
  PalScriptMgr *v2; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)7);
    dword_DBA244 = *((_DWORD *)String + 1);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
      (((PalScriptMgr *)v2))->PalScriptMgr::InitVtable(7);
    PalScriptMgr::NotifyEvent();
  }
}

// 0x00436CB0
void PalScript::Op_HY_FLY()
{
  char *String; // esi
  _DWORD *v2; // eax
  int *ScriptBufferAddr; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = (_DWORD *)(((CGameData *)&g_gamefrm))->CGameData::SetMode(7);
      ScriptBufferAddr = (int *)GetScriptBufferAddr(v2);
    }
    else
    {
      ScriptBufferAddr = (int *)&g_SceneTransitionBuffer;
    }
    switch ( ScriptBufferAddr[2] )
    {
      case 0:
        *((_DWORD *)String + 1) = 0;
        break;
      case 1:
        *((_DWORD *)String + 1) = 1;
        break;
      case 2:
        *((_DWORD *)String + 1) = 2;
        break;
      case 3:
        *((_DWORD *)String + 1) = 3;
        break;
      case 4:
        *((_DWORD *)String + 1) = 4;
        break;
      default:
        return;
    }
  }
}

// 0x00436D30
void PalScript::Op_SetRoleTexture()
{
  char *String; // esi
  _DWORD *v2; // eax
  int *ScriptBufferAddr; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = (_DWORD *)(((CGameData *)&g_gamefrm))->CGameData::SetMode(7);
      ScriptBufferAddr = (int *)GetScriptBufferAddr(v2);
    }
    else
    {
      ScriptBufferAddr = (int *)&g_SceneTransitionBuffer;
    }
    switch ( ScriptBufferAddr[40465] )
    {
      case 0:
        *((_DWORD *)String + 1) = 0;
        break;
      case 1:
        *((_DWORD *)String + 1) = 1;
        break;
      case 2:
        *((_DWORD *)String + 1) = 2;
        break;
      case 3:
        *((_DWORD *)String + 1) = 3;
        break;
      default:
        return;
    }
  }
}

// 0x00436DB0
void PalScript::Op_Rotate()
{
  char *String; // esi
  _DWORD *v2; // eax
  int *ScriptBufferAddr; // eax
  int v4; // eax
  int v5; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = (_DWORD *)(((CGameData *)&g_gamefrm))->CGameData::SetMode(7);
      ScriptBufferAddr = (int *)GetScriptBufferAddr(v2);
    }
    else
    {
      ScriptBufferAddr = (int *)&g_SceneTransitionBuffer;
    }
    v4 = (unsigned long)ScriptBufferAddr[40462];
    if ( v4 )
    {
      v5 = v4 - 1;
      if ( v5 )
      {
        if ( v5 == 1 )
          *((_DWORD *)String + 1) = 2;
      }
      else
      {
        *((_DWORD *)String + 1) = 1;
      }
    }
    else
    {
      *((_DWORD *)String + 1) = 0;
    }
  }
}

// 0x00436E10
void PalScript::Op_Quake()
{
  char *String; // esi
  _DWORD *v2; // eax
  int *ScriptBufferAddr; // eax
  int v4; // eax
  int v5; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = (_DWORD *)(((CGameData *)&g_gamefrm))->CGameData::SetMode(7);
      ScriptBufferAddr = (int *)GetScriptBufferAddr(v2);
    }
    else
    {
      ScriptBufferAddr = (int *)&g_SceneTransitionBuffer;
    }
    v4 = (unsigned long)ScriptBufferAddr[40463];
    if ( v4 )
    {
      v5 = v4 - 1;
      if ( v5 )
      {
        if ( v5 == 1 )
          *((_DWORD *)String + 1) = 2;
      }
      else
      {
        *((_DWORD *)String + 1) = 1;
      }
    }
    else
    {
      *((_DWORD *)String + 1) = 0;
    }
  }
}

// 0x00436E70
void PalScript::Op_ShowChatRest()
{
  char *String; // esi
  _DWORD *v2; // eax
  int *ScriptBufferAddr; // eax
  int v4; // eax
  int v5; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = (_DWORD *)(((CGameData *)&g_gamefrm))->CGameData::SetMode(7);
      ScriptBufferAddr = (int *)GetScriptBufferAddr(v2);
    }
    else
    {
      ScriptBufferAddr = (int *)&g_SceneTransitionBuffer;
    }
    v4 = (unsigned long)ScriptBufferAddr[40464];
    if ( v4 )
    {
      v5 = v4 - 1;
      if ( v5 )
      {
        if ( v5 == 1 )
          *((_DWORD *)String + 1) = 2;
      }
      else
      {
        *((_DWORD *)String + 1) = 1;
      }
    }
    else
    {
      *((_DWORD *)String + 1) = 0;
    }
  }
}

// 0x00436ED0
void PalScript::Op_GetHS_UnHock_type()
{

  char *String; // esi
  char *v3; // eax
  int v4; // ecx

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    v3 = (char *)this->PalScript::GetString();
    if ( v3 )
    {
      v4 = *((_DWORD *)String + 1);
      if ( v4 )
      {
        if ( v4 == 1 )
          g_nMiniGameParam = 3;
      }
      else
      {
        g_nMiniGameParam = 1;
      }
      g_nMiniGameState = 0;
      dword_D92780 = g_nMiniGameParam;
      dword_DBA24C = (PalScriptMgr *)*((_DWORD *)v3 + 1);
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)0xC);
    }
  }
}

// 0x00436F40
void PalScript::Op_SetBigMapElement()
{
  char *String; // eax
  PalScriptMgr *v2; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    dword_DBA254 = (PalScriptMgr *)*((_DWORD *)String + 1);
    (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)0xB);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
      (((PalScriptMgr *)v2))->PalScriptMgr::InitVtable(11);
    PalScriptMgr::NotifyEvent();
  }
}

// 0x00436F90
void PalScript::Op_ObjectMove()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    (((CGameData *)&g_gamefrm))->CGameData::Load(*((CUtil **)String + 1));
}

// 0x00436FB0
void PalScript::Op_KF_Entry()
{
  char *String; // eax
  unsigned __int8 v2; // bl

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    v2 = *((_DWORD *)String + 1) != 0;
    (((CGameData *)&g_gamefrm))->CGameData::SetMode(5);
    g_bRoleFlag1 = v2;
  }
}

// 0x00436FE0
void PalScript::Op_ENCAMP_Entry()
{
  char *String; // eax
  unsigned __int8 v2; // bl

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    v2 = *((_DWORD *)String + 1) != 0;
    (((CGameData *)&g_gamefrm))->CGameData::SetMode(5);
    g_bRoleFlag2 = v2;
  }
}

// 0x00437010
void PalScript::Op_StopMusic()
{
  char *String; // eax
  unsigned __int8 v2; // [esp-0x4] [ebp-0x4]

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    v2 = *((_DWORD *)String + 1) != 0;
    (((CGameData *)&g_gamefrm))->CGameData::SetMode(5);
    SetUIWndFlag(v2);
  }
}

// 0x00437040
void PalScript::Op_SKEE_Entry()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    (((ComposeUI *)&g_pComposeUI))->ComposeUI::RefreshRecipeList(*((_DWORD *)String + 1));
    PalScriptMgr::NotifyEvent();
  }
}

// 0x00437080
void PalScript::Op_Deal()
{
  PalScriptMgr *v1; // eax

  (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)8);
  v1 = (PalScriptMgr *)operator new(0xCu);
  if ( v1 )
    (((PalScriptMgr *)v1))->PalScriptMgr::InitVtable(8);
  PalScriptMgr::NotifyEvent();
}

// 0x004370C0
void PalScript::Op_APPR_Entry()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    *((_DWORD *)String + 1) = (unsigned __int8)p_BYTE;
}

// 0x004370E0
void PalScript::Op_GetHSLv()
{
  PalScriptMgr *v1; // eax

  (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)9);
  v1 = (PalScriptMgr *)operator new(0xCu);
  if ( v1 )
    (((PalScriptMgr *)v1))->PalScriptMgr::InitVtable(9);
  PalScriptMgr::NotifyEvent();
}

// 0x00437120
void PalScript::Op_SwitchRS()
{
  char *String; // eax
  PalScriptMgr *v2; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    dword_DBA248 = *((_DWORD *)String + 1);
    (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)0xA);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
      (((PalScriptMgr *)v2))->PalScriptMgr::InitVtable(10);
    PalScriptMgr::NotifyEvent();
  }
}

// 0x00437170
void PalScript::Op_GetFavor()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    (((PalScriptMgr *)&stru_DBA134))->PalScriptMgr::ShowTextBox(*((const char **)String + 1));
}

// 0x00437190
void PalScript::Op_AddSkill()
{
  ScreenEffect *Instance; // eax

  Instance = (((ScreenEffectMgr *)this))->ScreenEffectMgr::GetInstance();
  if ( (((ScreenEffectMgr *)Instance))->ScreenEffectMgr::ProcessEffect(1) )
    PalScriptMgr::NotifyEvent();
}

// 0x004371B0
void PalScript::Op_GetFavorite()
{
  ScreenEffect *Instance; // eax

  Instance = (((ScreenEffectMgr *)this))->ScreenEffectMgr::GetInstance();
  if ( (((ScreenEffectMgr *)Instance))->ScreenEffectMgr::ProcessEffect(2) )
    PalScriptMgr::NotifyEvent();
}

// 0x004371D0
void PalScript::Op_Note()
{
  ScreenEffect *Instance; // eax

  Instance = (((ScreenEffectMgr *)this))->ScreenEffectMgr::GetInstance();
  if ( (((ScreenEffectMgr *)Instance))->ScreenEffectMgr::ProcessEffect(3) )
    PalScriptMgr::NotifyEvent();
}

// 0x004371F0
void PalScript::Op_PlaySound()
{
  ScreenEffect *Instance; // eax

  Instance = (((ScreenEffectMgr *)this))->ScreenEffectMgr::GetInstance();
  if ( (((ScreenEffectMgr *)Instance))->ScreenEffectMgr::ProcessEffect(4) )
    PalScriptMgr::NotifyEvent();
}

// 0x00437210
void PalScript::Op_FullRoleAtt()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // ebx
  void *SceneObject; // edi
  int *ActiveSlot; // esi

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String && v3 )
  {
    SceneObject = GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      ActiveSlot = (((UICoverFrm *)&g_gamefrm))->UICoverFrm::FindActiveSlot();
      (((CScreenMode *)ActiveSlot))->CScreenMode::HideUIBars((int)SceneObject, *((_DWORD *)v4 + 1));
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00437280
void PalScript::Op_DlgPos()
{
  char *String; // ebp

  char *v3; // esi

  char *v5; // edi

  char *v7; // eax
  PalScriptMgr *v8; // eax
  unsigned int pdwVal[8]; // [esp+0x1C] [ebp-0x58] BYREF
  char v10[4]; // [esp+0x3C] [ebp-0x38] BYREF
  int v11; // [esp+0x5C] [ebp-0x18]
  int v12; // [esp+0x60] [ebp-0x14]
  char v13; // [esp+0x64] [ebp-0x10]
  int v14; // [esp+0x68] [ebp-0xC]
  char v15; // [esp+0x6C] [ebp-0x8]
  char v16; // [esp+0x6E] [ebp-0x6]
  int v17; // [esp+0x70] [ebp-0x4]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v7 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 && v7 )
  {
    v13 = 0;
    pdwVal[7] = 0x7FFFFFFF;
    strcpy((char *)v10, (const char *)&dir[32]);
    v11 = 1;
    v14 = -1;
    v12 = 0;
    v17 = 0;
    v15 = 0;
    v16 = 1;
    (((PAL3 *)*((PAL3 **)String + 1)))->PAL3::UpdateSubsystems();
    byte_C11750 = 1;
    PAL3::StartCombat(pdwVal, 0, 0, 0);
    v8 = (PalScriptMgr *)operator new(0xCu);
    if ( v8 )
      (((PalScriptMgr *)v8))->PalScriptMgr::InitVtable(6);
    PalScriptMgr::NotifyEvent();
  }
}

// 0x004373A0
void PalScript::Op_FadeOut()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    dword_C1171C = *((_DWORD *)String + 1);
}

// 0x004373C0
void PalScript::Op_FadeIn()
{
  byte_C11748 = 1;
}

// 0x004373D0
void PalScript::Op_DlgFace()
{
  int v1; // esi
  char *String; // eax
  PalScriptMgr *v3; // eax
  unsigned int pdwVal[12]; // [esp+0x4] [ebp-0x30] BYREF

  v1 = 0;
  while ( 1 )
  {
    String = (char *)this->PalScript::GetString();
    pdwVal[v1 + 6] = (unsigned int)String;
    if ( !String )
      break;
    pdwVal[v1++] = *((_DWORD *)String + 1);
    if ( v1 >= 6 )
    {
      byte_C11750 = 1;
      PAL3::StartCombat(pdwVal, 0, 0, 1);
      v3 = (PalScriptMgr *)operator new(0xCu);
      if ( v3 )
        (((PalScriptMgr *)v3))->PalScriptMgr::InitVtable(6);
      PalScriptMgr::NotifyEvent();
      return;
    }
  }
}

// 0x00437440
void PalScript::Op_DlgFont()
{
  char *String; // edi

  char *v3; // eax
  char *v4; // ebx
  RoleSystem *SceneObject; // esi

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String )
  {
    if ( v3 )
    {
      SceneObject = (RoleSystem *)GetSceneObject(0xFFFFu);
      if ( SceneObject )
      {
        if ( (((RoleSystem *)SceneObject))->RoleSystem::TryMoveToTarget(*((_DWORD *)String + 1), *((_DWORD *)v4 + 1)) )
          PalScriptMgr::NotifyEvent();
        else
          PalScriptMgr::UpdateLoadProgress();
      }
    }
  }
}

// 0x004374A0
void PalScript::Op_LoadScene()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    (((UISceneMap *)&g_UISceneMapDlg))->UISceneMap::LoadCompass(*((const char **)String + 1), 1);
    (**(void ( ***)(UISceneMap *, int))((UIWnd *)&g_UISceneMapDlg))((UISceneMap *)(&g_UISceneMapDlg), (int)(1));
    PalScriptMgr::NotifyEvent();
  }
}

// 0x004374E0
void PalScript::Op_DlgHead()
{
  char *String; // esi

  String = (char *)this->PalScript::GetString();
  if ( String )
    *((_DWORD *)String + 1) = (((UIWnd *)&g_UISceneMapDlg))->UIWnd::_todo_451730();
}

// 0x00437500
void PalScript::Op_DlgSel()
{
  char *String; // eax
  int *v2; // eax
  int p_DWORD[3]; // [esp+0x0] [ebp-0xC] BYREF

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    p_DWORD[0] = 0xFFFF;
    p_DWORD[1] = 0;
    p_DWORD[2] = 0;
    p_DWORD[0] = *((_DWORD *)String + 1);
    v2 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(p_DWORD);
    ScriptVM::GetObjectByID(v2 != 0);
  }
}

// 0x00437550
void PalScript::Op_CameraSet()
{
  char *String; // edi

  char *v3; // eax
  char *v4; // esi
  int RoleNum; // eax
  char *v6; // eax
  char *v7; // [esp-0x8] [ebp-0x110]
  int v8; // [esp-0x4] [ebp-0x10C]
  char Buffer[256]; // [esp+0x8] [ebp-0x100] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String && v3 )
  {
    AddNPCToPartySlot(*((_DWORD *)String + 1), *((_DWORD *)v3 + 1));
    RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*((_DWORD *)v4 + 1));
    if ( RoleNum )
    {
      v8 = RoleNum + 28;
      v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName((char *)(&off_56ABA4)[*((_DWORD *)String + 1)]);
      v6 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("AddSkill");
      _snprintf(Buffer, 0xFFu, v6, v7, v8);
      InputSystem::ProcessFrame(Buffer);
    }
  }
}

// 0x004375E0
void PalScript::Op_CameraWag()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
      *((_DWORD *)String + 1) = g_nRoleInitLevel[*((_DWORD *)v3 + 1)];
  }
}

// 0x00437610
void PalScript::Op_CameraMove()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    *((_DWORD *)String + 1) = *(&g_RoleSlotBuf.dword_17AA450 + 147);
}

// 0x00437630
void PalScript::Op_CameraRotate()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    AddMoney(*((_DWORD *)String + 1));
}

// 0x00437650
void PalScript::Op_GetDlgSel()
{
  char *String; // esi

  char *v3; // eax
  int v4; // eax
  CCBStage *Instance; // eax
  CScreenMode *v6; // eax
  void *v7; // [esp-0x8] [ebp-0xC]
  char *v8; // [esp-0x4] [ebp-0x8]
  int v9; // [esp-0x4] [ebp-0x8]
  int v10; // [esp+0x0] [ebp-0x4]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    v4 = *((_DWORD *)v3 + 1);
    if ( v4 == -1 )
    {
      v8 = (char *)*((_DWORD *)String + 1);
      Instance = (CCBStage *)CScreenMode::GetInstance();
      (((CCBStage *)Instance))->CCBStage::PlaySound(v8, v10);
    }
    else
    {
      v9 = v4;
      v7 = (void *)*((_DWORD *)String + 1);
      v6 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v6))->CScreenMode::PlaySoundIfEnabled(v7, v9);
    }
  }
}

// 0x004376A0
void PalScript::Op_CameraTrans()
{
  char *String; // eax
  int v2; // ebx
  int v3; // edi
  int v4; // esi
  int *v5; // ecx

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    v2 = 1;
    v3 = -10000;
    v4 = 1;
    v5 = (int *)&g_nRoleInitLevel[1];
    do
    {
      if ( v5 != &g_nRoleInitLevel[4] && *v5 > v3 )
      {
        v2 = v4;
        v3 = (unsigned long)*v5;
      }
      ++v5;
      ++v4;
    }
    while ( (int)v5 <= (int)&g_nRoleInitLevel[5] );
    *((_DWORD *)String + 1) = v2;
  }
}

// 0x004376F0
void PalScript::Op_CameraDefault()
{
  char *String; // eax
  int v2; // edi
  int v3; // ebx
  int v4; // esi
  int *v5; // ecx

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    v2 = 10000;
    v3 = 0;
    v4 = 1;
    v5 = (int *)&g_nRoleInitLevel[1];
    do
    {
      if ( v5 != &g_nRoleInitLevel[4] && *v5 < v2 )
      {
        v3 = v4;
        v2 = (unsigned long)*v5;
      }
      ++v5;
      ++v4;
    }
    while ( (int)v5 <= (int)&g_nRoleInitLevel[5] );
    *((_DWORD *)String + 1) = v3;
  }
}

// 0x00437740
void PalScript::Op_RoleStop()
{
  char *String; // eax
  int v2; // eax
  void *v3; // esi
  void *SkillNum; // esi

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    v2 = *((_DWORD *)String + 1);
    if ( v2 )
    {
      if ( v2 == 1 )
      {
        SkillNum = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(6602);
        if ( g_RoleSlotBuf.m_partyActor.m_pSelfAtt )
          (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&g_RoleSlotBuf.m_partyActor.m_obbox);
        g_RoleSlotBuf.m_partyActor.m_obbox = 6602;
        g_RoleSlotBuf.m_partyActor.m_pSelfAtt = ((void *)(SkillNum));
        *(&g_RoleSlotBuf.m_partyActor.m_obbox + 1) = 1;
      }
    }
    else
    {
      v3 = (void *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(6603);
      if ( g_RoleSlotBuf.m_partyActor.m_pSelfAtt )
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&g_RoleSlotBuf.m_partyActor.m_obbox);
      g_RoleSlotBuf.m_partyActor.m_pSelfAtt = ((void *)(v3));
      g_RoleSlotBuf.m_partyActor.m_obbox = 6603;
      *(&g_RoleSlotBuf.m_partyActor.m_obbox + 1) = 1;
    }
  }
}

// 0x004377F0
void PalScript::Op_RoleEmote()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  PalScript *v5; // eax
  int v6; // eax
  int v7; // esi
  char v8; // cl
  int v9; // [esp-0x4] [ebp-0xC]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String )
  {
    if ( v3 )
    {
      LOWORD(v3) = *((_WORD *)String + 2);
      v9 = (int)v3;
      v5 = (PalScript *)UISceneUpdate();
      (((PalScript *)v5))->PalScript::SetAction(v9);
      v7 = v6;
      if ( v6 )
      {
        v8 = v4[4];
        *(_DWORD *)(v6 + 576) = 1;
        *(_BYTE *)(v6 + 173) = v8;
        if ( !v8 )
          (((PalScript *)v6))->PalScript::StopSound3D();
        if ( *(_BYTE *)(v7 + 244) == 31 && !_strcmpi(*(const char **)(*(_DWORD *)(v7 + 796) + 16), "m09") )
          (((RoleSystem *)v7))->RoleSystem::SetTileTypeVisible(2, *(_BYTE *)(v7 + 173) == 0);
        if ( *(_BYTE *)(v7 + 173) && *(_DWORD *)(v7 + 88) == 4 && !_strcmpi((const char *)(v7 + 176), a4_0) )
          (((CEffMgr *)*(CEffMgr **)(v7 + 92)))->CEffMgr::SetEffectClass(*(_DWORD *)(v7 + 212), *(_DWORD *)(v7 + 216), *(_DWORD *)(v7 + 220));
      }
    }
  }
}

// 0x004378E0
void PalScript::Op_HaveItem()
{
  int v1; // edi
  char **i; // esi
  char *String; // eax
  PalScript *v4; // eax
  int v5; // eax
  int v6; // esi
  float v7; // edx
  PalScript *v8; // [esp-0x4] [ebp-0x2C]
  float pData; // [esp+0x8] [ebp-0x20] BYREF
  float v10; // [esp+0xC] [ebp-0x1C]
  float v11; // [esp+0x10] [ebp-0x18]
  _DWORD v12[5]; // [esp+0x14] [ebp-0x14] BYREF

  v1 = 0;
  for ( i = (char **)v12; ; ++i )
  {
    String = (char *)this->PalScript::GetString();
    *i = String;
    if ( !String )
      break;
    if ( ++v1 >= 5 )
    {
      LOWORD(this) = *(_WORD *)(v12[0] + 4);
v4 = (PalScript *)UISceneUpdate();
      (((PalScript *)v4))->PalScript::SetAction((int)v8);
      v6 = v5;
      if ( v5 )
      {
        pData = *(float *)(v5 + 40);
        v7 = *(float *)(v5 + 48);
        v10 = *(float *)(v5 + 44);
        v11 = v7;
        pData = pData + *(float *)(v12[1] + 4);
        v10 = v10 + *(float *)(v12[2] + 4);
        v11 = v7 + *(float *)(v12[3] + 4);
        (((ScriptVM *)v5))->ScriptVM::GetRolePosition(1u);
        (((ScriptVM *)v6))->ScriptVM::ExecuteOpcode(&pData, *(_DWORD *)(v12[4] + 4), 0, 1);
        (((ScriptVM *)v6))->ScriptVM::GetRolePosition(0);
        (((PalScriptMgr *)v6))->PalScriptMgr::ExecuteOpcode();
        if ( !UIScene::ProcessInput("m15", aA)
          && !UIScene::ProcessInput("m15", aB)
          && !UIScene::ProcessInput("m15", "C")
          && !UIScene::ProcessInput("m15", "D")
          && !UIScene::ProcessInput("m15", "A1")
          && !UIScene::ProcessInput("m15", "B1")
          && !UIScene::ProcessInput("m15", "C1")
          && !UIScene::ProcessInput("m15", "D1")
          && !UIScene::ProcessInput("m08", a3) )
        {
          *(_DWORD *)(v6 + 580) = 1;
        }
      }
      return;
    }
  }
}

// 0x00437A80
void PalScript::Op_Climb()
{
  char *String; // eax
  PalScript *v2; // eax
  PalScriptMgr *v3; // eax
  int v4; // [esp-0x4] [ebp-0x8]

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    LOWORD(String) = *((_WORD *)String + 2);
    v4 = (int)String;
    v2 = (PalScript *)UISceneUpdate();
    (((PalScript *)v2))->PalScript::SetAction(v4);
    if ( v3 )
    {
      (((PalScriptMgr *)v3))->PalScriptMgr::OnAnimFinish();
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00437AC0
char * PalScript::Op_InTeamExecScript()
{
  char *result; // eax
  scAsmDecoder *v2; // ecx

  result = (char *)this->PalScript::GetString();
  if ( result )
    return (char *)(((scAsmDecoder *)v2))->scAsmDecoder::Execute(*((_DWORD *)result + 1), 1);
  return result;
}

// 0x00437AE0
char * PalScript::Op_RoleSetLayerByObj()
{
  char *String; // esi

  char *result; // eax
  char *v4; // edi

  String = (char *)this->PalScript::GetString();
  result = (char *)this->PalScript::GetString();
  v4 = (char *)result;
  if ( String && result )
  {
    result = (char *)GetSceneObject(*((_WORD *)String + 2));
    if ( result )
      *((_DWORD *)result + 364) = *((_DWORD *)v4 + 1);
  }
  return result;
}

// 0x00437B20
void PalScript::Op_Combat()
{
  char *String; // esi

  char *v3; // eax
  char Buffer[260]; // [esp+0x8] [ebp-0x104] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
    {
      sprintf(Buffer, "caption\\%s.tga", *((const char **)String + 1));
      PalScriptIdleObj_LoadScriptTexture((int)Buffer);
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00437B90
void PalScript::Op_DlgTime()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    NPC::SetRoleMode(*((_DWORD *)String + 1));
}

// 0x00437BB0
void PalScript::Op_GetTimeSel()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax
  int p_DWORD[3]; // [esp+0x8] [ebp-0xC] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    if ( v5 )
    {
      p_DWORD[0] = *((int *)String + 1);
      p_DWORD[1] = *((int *)v3 + 1);
      p_DWORD[2] = *((int *)v5 + 1);
      (((RoleSystem *)&g_RoleSystemMain))->RoleSystem::ProcessMoveCommand(p_DWORD);
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00437C20
void PalScript::Op_Get_Appr()
{
  PAL3::SnapScreen();
}

// 0x00437C30
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void PalScript::Op_Enable_Sword()
{
  (((PAL3 *)this))->PAL3::StartHideFight();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00437C40
void PalScript::Op_Enable_JusticeBook()
{
  PalScript *v1; // eax

  v1 = (PalScript *)UISceneUpdate();
  (((PalScript *)v1))->PalScript::BindRolesToStage();
}

// 0x00437C50
void PalScript::Op_Specify_Compos()
{
  char *String; // ebx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  PAL3 *v4; // ecx
  gbAudioManager *v5; // esi
  CScreenMode *v6; // eax
  int v7; // esi
  int OpcodeByName; // eax
  int Width; // eax
  CScreenMode *v10; // eax
  CScreenMode *v11; // eax
  int v12; // [esp+0x4] [ebp-0x10C]
  char Buffer[260]; // [esp+0xC] [ebp-0x104] BYREF

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    v5 = (gbAudioManager *)AudioManager;
    if ( AudioManager )
    {
      (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(1);
      (((gbAudioManager *)v5))->gbAudioManager::StopSoundStream(2);
      (((gbAudioManager *)v5))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v5))->gbAudioManager::DetachAll3D();
      v6 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v6))->CScreenMode::StopAll();
    }
    v7 = g_nSceneState;
    g_nSceneState = 0;
    (((PAL3 *)v4))->PAL3::Render();
    g_nSceneState = v7;
    sprintf(Buffer, "movie\\%s.bik", *((const char **)String + 1));
    OpcodeByName = FindOpcodeByName(*((char **)String + 1));
    if ( OpcodeByName >= 0 )
      SetGameSwitch(OpcodeByName);
    (((CScreenMode *)&g_ScreenMode))->CScreenMode::CreateDevice((int)Buffer, g_todo_BFDA4C, 0, 0);
    v12 = (600 - (((CScreenMode *)&g_ScreenMode))->CScreenMode::GetHeight()) / 2;
    Width = (((CScreenMode *)&g_ScreenMode))->CScreenMode::GetWidth();
    (((CScreenMode *)&g_ScreenMode))->CScreenMode::SetViewport((800 - Width) / 2, v12);
    (((CScreenMode *)&g_ScreenMode))->CScreenMode::PlayVideo(1);
    if ( CScreenMode::GetInstance()->m_bRenderAlt )
    {
      v10 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v10))->CScreenMode::AudioFadeOut();
    }
    else
    {
      v11 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v11))->CScreenMode::AudioStopAll();
    }
  }
}

// 0x00437FF0
void PalScript::Op_Start_Wolf()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  RoleSystem *SceneObject; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String && v3 )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
      (((RoleSystem *)SceneObject))->RoleSystem::SetActorTexture(*((const char **)v4 + 1));
  }
}

// 0x00438030
void PalScript::Op_Start_HideFight()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax
  _DWORD *v6; // eax
  float v7; // [esp+0xC] [ebp-0xC]
  float v8; // [esp+0x10] [ebp-0x8]
  float v9; // [esp+0x14] [ebp-0x4]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 )
  {
    v7 = (float)*((int *)String + 1);
    v8 = (float)*((int *)v3 + 1);
    v9 = (float)*((int *)v5 + 1);
    v6 = (_DWORD *)operator new(0x1Cu);
    if ( v6 )
    {
      v6[4] = 0;
      v6[5] = 0;
      v6[6] = 0;
      v6[2] = 0;
      v6[1] = 1;
      *((_BYTE *)v6 + 12) = 0;
      g_fPalScript_C12B28 = v7;
      g_fPalScript_C12B2C = v8;
      g_fPalScript_C12B30 = v9;
      *((float *)v6 + 4) = v7;
      *((float *)v6 + 5) = v8;
      *((float *)v6 + 6) = v9;
    }
    PalScriptMgr::NotifyEvent();
  }
}

// 0x00438100
BOOL PalScript::IsAnimDone()
{
  return this[12] == 0;
}

// 0x00438110
void PalScript::UpdateWaitTimer(float fVal)
{
  double v2; // st7
  long double v3; // st7

  v2 = fVal + *(float *)&this->m_waitobj;
  *(float *)&this->m_waitobj = v2;
  if ( v2 >= 5.0 )
  {
    LOBYTE(this->m_fBlendFactor) = 1;
    this->m_waitobj = ((PtrArray *)((PtrArray *)1084227584));
  }
  v3 = (1.0 - cos(*(float *)&this->m_waitobj * 0.2 * 3.1415927)) * 0.5;
  g_fPalScript_C12B28 = (1.0 - v3) * *(float *)&this->m_nState;
  g_fPalScript_C12B2C = (1.0 - v3) * *(float *)&this->m_nFrameCount;
  g_fPalScript_C12B30 = (1.0 - v3) * *(float *)&this->m_CamObj;
}

// 0x004381B0
void PalScript::ClearFloatParams()
{
  g_fPalScript_C12B28 = 0.0;
  g_fPalScript_C12B2C = 0.0;
  g_fPalScript_C12B30 = 0.0;
}

// 0x004381E0
void PalScript::Op_Trigger()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax
  _DWORD *v6; // eax
  float v7; // [esp+0xC] [ebp-0xC]
  float v8; // [esp+0x10] [ebp-0x8]
  float v9; // [esp+0x14] [ebp-0x4]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  if ( String && v3 && v5 )
  {
    v7 = (float)*((int *)String + 1);
    v8 = (float)*((int *)v3 + 1);
    v9 = (float)*((int *)v5 + 1);
    v6 = (_DWORD *)operator new(0x1Cu);
    if ( v6 )
    {
      v6[4] = 0;
      v6[5] = 0;
      v6[6] = 0;
      v6[2] = 0;
      v6[1] = 1;
      *((_BYTE *)v6 + 12) = 0;
      g_fPalScript_C12B28 = 0.0;
      g_fPalScript_C12B2C = 0.0;
      g_fPalScript_C12B30 = 0.0;
      *((float *)v6 + 4) = v7;
      *((float *)v6 + 5) = v8;
      *((float *)v6 + 6) = v9;
    }
    PalScriptMgr::NotifyEvent();
  }
}

// 0x004382A0
void PalScript::UpdateIdleTimer(float fVal)
{
  double v2; // st7
  long double v3; // st7

  v2 = fVal + *(float *)&this->m_waitobj;
  *(float *)&this->m_waitobj = v2;
  if ( v2 >= 5.0 )
  {
    LOBYTE(this->m_fBlendFactor) = 1;
    this->m_waitobj = ((PtrArray *)((PtrArray *)1084227584));
  }
  v3 = (1.0 - cos(*(float *)&this->m_waitobj * 0.2 * 3.1415927)) * 0.5;
  g_fPalScript_C12B28 = *(float *)&this->m_nState * v3;
  g_fPalScript_C12B2C = *(float *)&this->m_nFrameCount * v3;
  g_fPalScript_C12B30 = *(float *)&this->m_CamObj * v3;
}

// 0x00438310
void PalScript::Op_JT_Exhibit()
{
  char *String; // esi

  char *v3; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String )
  {
    if ( v3 )
    {
      (((CameraCtrl *)&g_GameData))->CameraCtrl::SetupDirect((int *)g_pCameraCtrl, *((_DWORD *)String + 1), *((_DWORD *)v3 + 1));
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00438350
void PalScript::Op_GetHS_ManageType()
{
  char *String; // eax
  PalScript *v2; // eax
  ScriptVM *v3; // eax
  int v4; // [esp-0x4] [ebp-0x4]

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    LOWORD(String) = *((_WORD *)String + 2);
    v4 = (int)String;
    v2 = (PalScript *)UISceneUpdate();
    (((PalScript *)v2))->PalScript::SetAction(v4);
    if ( v3 )
      (((ScriptVM *)v3))->ScriptVM::ExecuteBlock();
  }
}

// 0x00438390
void PalScript::Op_GetHS_Accrual_type()
{
  char **v1; // esi
  int v2; // edi
  Scene *v3; // eax
  int v4; // edi
  char *v5; // esi
  int v6; // eax
  Actor *SaveDataManager; // eax
  int v8; // eax
  const char *v9; // [esp-0x8] [ebp-0x1C]
  int v10; // [esp-0x4] [ebp-0x18]
  int v11; // [esp+0x8] [ebp-0xC] BYREF
  int v12; // [esp+0xC] [ebp-0x8]
  int v13; // [esp+0x10] [ebp-0x4]

  v1 = (char **)&v11;
  v2 = 3;
  do
  {
    *v1++ = this->PalScript::GetString();
    --v2;
  }
  while ( v2 );
  v3 = UISceneUpdate();
  v4 = v11;
  v5 = (char *)v3;
  if ( _strcmpi((const char *)&v3->m_pCapacity[5], *(const char **)(v11 + 4)) )
  {
    v10 = *(_DWORD *)(v12 + 4);
    v9 = (const char *)*(const char **)(v4 + 4);
    SaveDataManager = (Actor *)GetSaveDataManager();
    v8 = (((Actor *)SaveDataManager))->Actor::AddActionByName(v5, v9, v10);
    if ( v8 )
    {
      *(_DWORD *)(v13 + 4) = *(unsigned __int8 *)(v8 + 3);
      return;
    }
  }
  else
  {
    (((PalScript *)v5))->PalScript::SetAction(*(unsigned __int16 *)(v12 + 4));
    if ( v6 )
    {
      *(_DWORD *)(v13 + 4) = *(unsigned __int8 *)(v6 + 175);
      return;
    }
  }
  *(_DWORD *)(v13 + 4) = 0;
}

// 0x00438440
void PalScript::Op_EntryRow()
{
  g_nKeyMap3 = 0;
}

// 0x00438450
void PalScript::Op_RotateInv()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    *((_DWORD *)String + 1) = (unsigned __int8)g_szGamePath[0];
}

// 0x00438470
void PalScript::Op_EntrySkee()
{
  char *String; // esi

  char *v3; // eax
  CScreenMode *Instance; // eax
  char *v5; // [esp-0x8] [ebp-0xC]
  gbAudioManager *v6; // [esp-0x4] [ebp-0x8]

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  if ( String && v3 )
  {
    if ( (g_dwGameFlags & 4) != 0 )
    {
      v6 = (gbAudioManager *)*((_DWORD *)v3 + 1);
      v5 = (char *)*((_DWORD *)String + 1);
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::PlayAmbientSound(v5, v6);
    }
    CScreenMode::GetInstance()->m_bRenderAlt = 1;
  }
}

// 0x004384B0
void PalScript::Op_Dist()
{
  CScreenMode *Instance; // eax

  CScreenMode::GetInstance()->m_bRenderAlt = 0;
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioStopAll();
  }
}

// 0x004384D0
void PalScript::Op_CombatNotGameOver()
{
  char *String; // eax
  void *SceneObject; // esi
  _DWORD *v3; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    SceneObject = GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      v3 = (_DWORD *)operator new(0x14u);
      if ( v3 )
      {
        v3[3] = (_DWORD)SceneObject;
        v3[2] = 0;
        v3[1] = 1;
        *((_BYTE *)v3 + 16) = 0;
      }
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00438540
void PalScript::UpdateFadeOut(float fDelta)
{
  double v2; // st7
  float fAlpha; // [esp+0x0] [ebp-0x4]

  v2 = fDelta + *(float *)&this->m_waitobj;
  *(float *)&this->m_waitobj = v2;
  if ( v2 >= 5.0 )
  {
    LOBYTE(this->m_nState) = 1;
    this->m_waitobj = ((PtrArray *)((PtrArray *)1084227584));
  }
  fAlpha = 1.0f - (1.0f - cos(*(float *)&this->m_waitobj * 0.20000000298023224f * 3.1415927410125732f)) * 0.5f;
  (((RoleSystem *)LODWORD(this->m_fBlendFactor)))->RoleSystem::SetBlendMode(fAlpha);
}

// 0x004385A0
void PalScript::Op_GetCombat()
{
  char *String; // eax
  RoleSystem *SceneObject; // edi
  _DWORD *v3; // esi

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      v3 = (_DWORD *)operator new(0x14u);
      if ( v3 )
      {
        v3[3] = (_DWORD)SceneObject;
        v3[2] = 0;
        v3[1] = 1;
        *((_BYTE *)v3 + 16) = 0;
        (((RoleSystem *)SceneObject))->RoleSystem::SetBlendMode(0.0);
      }
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00438640
void PalScript::UpdateFadeIn(float fDelta)
{
  double v2; // st7
  char v4; // c0
  float fAlpha; // [esp+0x0] [ebp-0x4]

  v2 = fDelta + *(float *)&this->m_waitobj;
  *(float *)&this->m_waitobj = v2;
  if ( v4 )
  {
    fAlpha = (1.0f - cos(v2 * 0.20000000298023224f * 3.1415927410125732f)) * 0.5f;
    (((RoleSystem *)LODWORD(this->m_fBlendFactor)))->RoleSystem::SetBlendMode(fAlpha);
  }
  else
  {
    LOBYTE(this->m_nState) = 1;
    this->m_waitobj = ((PtrArray *)((PtrArray *)1084227584));
    (((RoleSystem *)LODWORD(this->m_fBlendFactor)))->RoleSystem::SetBlendMode(1.0);
  }
}

// 0x004386C0
void PalScript::Op_RoleFadeOut()
{
  char **v1; // esi
  int v2; // edi
  double v3; // st7
  unsigned int v4; // ecx
  __int64 v5; // [esp+0x8] [ebp-0x28]
  int v6; // [esp+0x10] [ebp-0x20]
  int v7; // [esp+0x14] [ebp-0x1C]
  int v8; // [esp+0x18] [ebp-0x18]
  _DWORD v9[4]; // [esp+0x20] [ebp-0x10] BYREF

  v1 = (char **)v9;
  v2 = 4;
  do
  {
    *v1++ = this->PalScript::GetString();
    --v2;
  }
  while ( v2 );
  g_nPAL3_D8E488 = 2;
  v5 = *(unsigned int *)(v9[1] + 4);
  v3 = (double)v5;
  LODWORD(v5) = *(_DWORD *)(v9[2] + 4);
  v4 = *(_DWORD *)(v9[3] + 4);
  dword_D8E4B4 = 0;
  dword_D8E4AC = 0;
  dword_D8E4B0 = 1065353216;
  *(float *)&v6 = v3 * 0.0039215689;
  dword_D8E48C = v6;
  dword_D8E498 = 1065353216;
  *(float *)&v7 = (double)v5 * 0.0039215689;
  dword_D8E490 = v7;
  *(float *)&v8 = (double)v4 * 0.0039215689;
  dword_D8E494 = v8;
  dword_D8E4B8 = *(_DWORD *)(v9[0] + 4);
  dword_D8E4A4 = 1120403456;
}

// 0x004387B0
void PalScript::Op_RoleFadeIn()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    LOBYTE(byte_BFDA40) = *((_DWORD *)String + 1) != 0;
}

// 0x004387D0
void PalScript::Op_TeamOpenAStartMove()
{
  int *p_pTargetPos; // esi
  int v2; // edi
  RoleSystem *SceneObject; // eax
  float v4; // st7
  int v5; // [esp+0x8] [ebp-0x14]
  int pTargetPos; // [esp+0xC] [ebp-0x10] BYREF
  float v7; // [esp+0x10] [ebp-0xC]
  int v8; // [esp+0x14] [ebp-0x8]
  int v9; // [esp+0x18] [ebp-0x4]

  p_pTargetPos = (int *)&pTargetPos;
  v2 = 4;
  do
  {
    *p_pTargetPos++ = (int)this->PalScript::GetString();
    --v2;
  }
  while ( v2 );
  SceneObject = (RoleSystem *)GetSceneObject(*(_WORD *)(pTargetPos + 4));
  if ( SceneObject )
  {
    v4 = *(float *)(v8 + 4);
    v5 = *(_DWORD *)(v9 + 4);
    pTargetPos = *(int *)(LODWORD(v7) + 4);
    v8 = v5;
    v7 = v4;
    (((RoleSystem *)SceneObject))->RoleSystem::StartLinearMove(&pTargetPos, 1);
  }
}

// 0x00438840
void PalScript::Op_ScrEft()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // ebx
  unsigned int v5; // esi
  int v6; // eax
  int v7; // edi
  int v8; // edx
  int *p_m_pRoleObj; // ecx
  int v10; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String )
  {
    if ( v3 )
    {
      v5 = *((_DWORD *)String + 1);
      if ( v5 < 5 )
      {
        v6 = 0;
        v7 = 0;
        v8 = 0;
        p_m_pRoleObj = (int *)&g_RoleSlotBuf.m_partyActor.m_pRoleObj;
        do
        {
          if ( v8 != v5 && *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v8) )
          {
            v6 += *p_m_pRoleObj;
            ++v7;
          }
          p_m_pRoleObj += 352;
          ++v8;
        }
        while ( (int)p_m_pRoleObj < (int)&unk_C06198 );
        if ( v7 )
        {
          v10 = *((_DWORD *)v4 + 1) + v6 / v7;
          if ( *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * v5) > v10 )
            v10 = *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * v5);
          SetRoleLevelAndRefresh(v5, v10);
        }
      }
    }
  }
}

// 0x004388C0
void PalScript::Op_IfInTeam()
{
  PAL3 *v1; // ecx
  char *String; // esi
  PAL3 *v3; // ecx
  PAL3 *v4; // ecx
  int v5; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    LOBYTE((((PAL3 *)v1))->PAL3::GetInstance_fd20()->m_pVtable) = 0;
    *(_BYTE *)(((PAL3 *)v3))->PAL3::GetInstance() = 0;
    v5 = *((_DWORD *)String + 1);
    if ( v5 )
    {
      if ( v5 == 1 )
        *(_BYTE *)(((PAL3 *)v4))->PAL3::GetInstance() = 1;
    }
    else
    {
      LOBYTE((((PAL3 *)v4))->PAL3::GetInstance_fd20()->m_pVtable) = 1;
    }
  }
}

// 0x00438910
void PalScript::ClearIntParams()
{
  g_nPalScript_D8E478 = 0;
  g_nPalScript_D8E47C = 0;
  nVal4 = 0;
}

// 0x00438930
void PalScript::Op_Enable_SwordSkill()
{
  char **v1; // esi
  int v2; // edi
  _DWORD v3[3]; // [esp+0x8] [ebp-0xC] BYREF

  v1 = (char **)v3;
  v2 = 3;
  do
  {
    *v1++ = this->PalScript::GetString();
    --v2;
  }
  while ( v2 );
  g_nPalScript_D8E478 = *(_DWORD *)(v3[0] + 4);
  g_nPalScript_D8E47C = *(_DWORD *)(v3[1] + 4);
  nVal4 = *(_DWORD *)(v3[2] + 4);
}

// 0x00438980
void PalScript::Op_CEft_Role()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    (((CEffect *)g_pSceneManager))->CEffect::Render(*((_DWORD *)String + 1));
}

// 0x004389A0
void PalScript::Op_FogH()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    (((CEffMgr *)g_pSceneManager))->CEffMgr::Init(*((_DWORD *)String + 1), g_nPalScript_D8E478, g_nPalScript_D8E47C, nVal4, 0);
}

// 0x004389D0
void PalScript::Op_Snow()
{
  char *String; // eax
  int *SceneObject; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
  {
    SceneObject = (int *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
    {
      g_nPalScript_D8E478 = SceneObject[40];
      g_nPalScript_D8E47C = SceneObject[41];
      nVal4 = SceneObject[42];
      *(float *)&g_nPalScript_D8E47C = *(float *)&g_nPalScript_D8E47C + 2.0;
    }
  }
}

// 0x00438A20
void PalScript::Op_CEft()
{
  (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)4);
}

// 0x00438A30
void PalScript::Op_AverageLv()
{
  char *String; // ebp
  int v2; // edi
  int *i; // ebx
  int *v4; // eax
  int *v5; // esi
  char *v6; // eax
  CScreenMode *Instance; // eax
  int v8; // [esp-0x4] [ebp-0x12C]
  int p_DWORD[3]; // [esp+0x10] [ebp-0x118] BYREF
  _DWORD v10[3]; // [esp+0x1C] [ebp-0x10C] BYREF
  char Buffer[256]; // [esp+0x28] [ebp-0x100] BYREF

  String = (char *)this->PalScript::GetString();
  v2 = 0;
  if ( String )
  {
    v10[0] = 6308;
    v10[1] = 6309;
    v10[2] = 6310;
    p_DWORD[1] = 0;
    p_DWORD[2] = 0;
    for ( i = v10; ; ++i )
    {
      p_DWORD[0] = (unsigned long)*i;
      v4 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(p_DWORD);
      v5 = (int *)v4;
      if ( v4 )
        break;
      if ( ++v2 >= 3 )
        return;
    }
    v8 = (unsigned long)(v4[2] + 4);
    v6 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("loseitem");
    _snprintf(Buffer, 0xFFu, v6, v8);
    InputSystem::ProcessFrame(Buffer);
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa007", 1);
    *((_DWORD *)String + 1) = v2;
    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(v5);
  }
}

// 0x00438B00
void PalScript::Op_EntrySmeltSys()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  Actor *SceneObject; // eax

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v4 = (char *)v3;
  if ( String && v3 )
  {
    SceneObject = (Actor *)GetSceneObject(*((_WORD *)String + 2));
    if ( SceneObject )
      (((Actor *)SceneObject))->Actor::GetInnerAnimDuration(*((_DWORD *)v4 + 1));
  }
}

// 0x00438B40
void PalScript::Op_Switch2Menu()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    LOBYTE(byte_BFDA41) = *((_DWORD *)String + 1) != 0;
}

// 0x00438B60
void PalScript::Op_CEft_Load()
{
  char *String; // eax


  String = (char *)this->PalScript::GetString();
  if ( String )
    this->PalScript::InitParticleSlht(*((PalScript **)String + 1));
}

// 0x00438B80
void PalScript::Op_GiveCloth()
{
  ScriptSystem::CheckEventType(6u, 0);
  ScriptSystem::CheckEventType(6u, 1);
  ScriptSystem::CheckEventType(6u, 2);
}

// 0x00438BA0
void PalScript::Op_LoadAct()
{
  char *String; // esi

  char *v3; // ebx

  char *v5; // eax
  char *v6; // edi
  RoleSystem *v7; // eax
  int v8; // ecx
  int RolePtr; // eax
  int v10; // ecx
  int v11; // edi
  int v12; // edx
  float m_fPosZ; // ecx
  float v14; // [esp+0x14] [ebp-0x24]
  float v15; // [esp+0x18] [ebp-0x20]
  float v16; // [esp+0x1C] [ebp-0x1C]
  gbVec3D pTarget; // [esp+0x20] [ebp-0x18] BYREF
  int pTargetPos[3]; // [esp+0x2C] [ebp-0xC] BYREF

  String = (char *)this->PalScript::GetString();
  v3 = (char *)this->PalScript::GetString();
  v5 = (char *)this->PalScript::GetString();
  v6 = (char *)v5;
  if ( String && v3 && v5 )
  {
    v7 = (RoleSystem *)UISceneUpdate();
    v8 = *((_DWORD *)String + 1) & 1;
    *((_DWORD *)String + 1) = v8;
    RolePtr = (((RoleSystem *)v7))->RoleSystem::GetRolePtr(v8);
    v10 = *((_DWORD *)v3 + 1);
    v11 = *((_DWORD *)v6 + 1);
    v15 = 0.0f;
    v16 = ((float)v11 + 0.5f) * flt_D8EB94 + *(float *)(RolePtr + 136);
    if ( v10 >= 0 )
    {
      v12 = *(_DWORD *)(RolePtr + 152);
      if ( v10 < v12 && v11 >= 0 && v11 < *(_DWORD *)(RolePtr + 156) )
        v15 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (v10 + v11 * v12));
    }
    v14 = ((float)v10 + 0.5f) * flt_D8EB94 + *(float *)(RolePtr + 128);
    *(float *)pTargetPos = v14;
    *(float *)&pTargetPos[1] = v15;
    *(float *)&pTargetPos[2] = v16;
    pTarget.x = g_pRoleSystem->m_fPosX;
    pTarget.y = g_pRoleSystem->m_fPosY;
    m_fPosZ = g_pRoleSystem->m_fPosZ;
    g_RoleSystemExtra0.m_partyActor.m_pRoleObj = 1;
    pTarget.z = m_fPosZ;
    (((RoleSystem *)&g_RoleSystemExtra0))->RoleSystem::NotifySceneChange(*((_DWORD *)String + 1));
    (((RoleSystem *)&g_RoleSystemExtra0))->RoleSystem::SetTargetRotation(&pTarget);
    (((RoleSystem *)&g_RoleSystemExtra0))->RoleSystem::Notify();
    *(gbVec3D *)&g_RoleSystemExtra0.m_fPosX = pTarget;
    (((RoleSystem *)&g_RoleSystemExtra0))->RoleSystem::StartLinearMove(pTargetPos, 1);
  }
}

// 0x00438D00
void PalScript::Op_Rain()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    (((InputSystem *)*((_DWORD *)String + 1)))->ProcessKeyboard_2();
}

// 0x00438D20
void PalScript::Op_WaterMagic()
{
  _DWORD *v1; // eax
  size_t v2; // esi
  UIFrameContainer *v3; // eax
  int *v4; // eax
  int v5; // edx
  size_t v6; // [esp+0x0] [ebp-0x34] BYREF
  int v7; // [esp+0xC] [ebp-0x28]
  _DWORD *v8; // [esp+0x10] [ebp-0x24]
  size_t *v9; // [esp+0x14] [ebp-0x20]
  _DWORD v10[4]; // [esp+0x18] [ebp-0x1C] BYREF
  int v11; // [esp+0x30] [ebp-0x4]

  v1 = (_DWORD *)operator new(0x10u);
  v2 = (size_t)v1;
  v8 = (_DWORD *)v1;
  v11 = 0;
  if ( v1 )
  {
    v6 = 152;
    v1[1] = 1;
    v1[2] = 0;
    *((_BYTE *)v1 + 12) = 0;
    v3 = (UIFrameContainer *)operator new(v6);
    v7 = (int)v3;
    LOBYTE(v11) = 2;
    if ( v3 )
      (((UIFrameContainer *)v3))->UIFrameContainer::ResetContainerState();
    else
      v4 = 0;
    LODWORD(g_fGameSpeed) = (unsigned long)v4;
    v10[2] = 256;
    v10[3] = 256;
    v10[0] = 0;
    v10[1] = 0;
    v5 = (unsigned long)*v4;
    LOBYTE(v11) = 1;
    (*(void ( **)(int *, _DWORD, _DWORD *, _DWORD))(v5 + 16))(v4, 0, (_DWORD *)(v10), 0);
    (((UIPushButton *)LODWORD(g_fGameSpeed)))->UIPushButton::CreateFromTemplate(pTemplate, 0);
    sub_445DB0(0);
    v7 = 0xFFFFFF;
    v9 = (size_t *)&v6;
    (((NPC *)LODWORD(g_fGameSpeed)))->NPC::UpdateAnim(0xFFFFFF);
  }
  else
  {
    v2 = 0;
  }
  v6 = v2;
  v11 = -1;
  PalScriptMgr::NotifyEvent();
}

// 0x00438F10
void PalScript::Op_FullTeamAtt()
{
  char *String; // eax

  String = (char *)this->PalScript::GetString();
  if ( String )
    InputSystem::ProcessFrame(*((char **)String + 1));
}

// 0x00438F30
void PalScript::Op_BeeInsertFrame()
{
  Actor *SaveDataManager; // eax
  float v2; // [esp-0x4] [ebp-0x4]

  v2 = *((float *)this->PalScript::GetString() + 1);
  SaveDataManager = (Actor *)GetSaveDataManager();
  InsertAnimFrame(SaveDataManager, v2);
}

// 0x00438F50
void PalScript::Op_CameraYaw()
{
  PalScript *v1; // eax
  int v2; // eax
  int v3; // eax
  Actor *SaveDataManager; // eax

  if ( !(_BYTE)g_ScriptSystemData.m_nScriptFlag )
  {
    if ( UIScene::ProcessInput("m16", pszName2) )
    {
      v1 = (PalScript *)UISceneUpdate();
      (((PalScript *)v1))->PalScript::SetAction(22);
      v3 = v2 + 172;
    }
    else
    {
      SaveDataManager = (Actor *)GetSaveDataManager();
      v3 = (((Actor *)SaveDataManager))->Actor::AddActionByName("m16", pszName2, 22);
    }
    if ( v3 )
      *(_BYTE *)(v3 + 3) = *(_BYTE *)(v3 + 3) == 0;
    LOBYTE(g_ScriptSystemData.m_nScriptFlag) = 1;
  }
}

// 0x00439130
void PalScript::Reset()
{
  (((UIProgressBar *)this))->UIProgressBar::Destroy() /* [ROWTABLE] */;
  (((UIWnd *)this))->UIWnd::_UIWnd() /* [ROWTABLE] */;
}

// 0x004391A0
void PalScript::SetReady()
{
  this->m_nFrameCount = 0;
  this->m_CamObj = ((PtrArray *)0);
  this->m_fScriptTimer = 0.0f;
  this->m_nState = 0;
  this->m_fBlendFactor = 0.0f;
  this->m_waitobj = ((PtrArray *)((PtrArray *)1));
  this->m_pinst = ((scScriptInstance *)((scScriptInstance *)1));
  LOBYTE((*(void **)(this))) = 1;
}

// 0x004391D0
void PalScript::ReleaseStateResource()
{
  void *v2; // edi
  void ( ***m_nState)(_DWORD, int); // ecx

  if ( !this->m_waitobj )
    goto LABEL_10;
  if ( LODWORD(this->m_fBlendFactor) == 1 )
    goto LABEL_8;
  if ( LODWORD(this->m_fBlendFactor) != 2 )
  {
    if ( LODWORD(this->m_fBlendFactor) != 3 )
    {
      this->m_fBlendFactor = 0.0f;
      return;
    }
LABEL_8:
    m_nState = (void ( ***)(_DWORD, int))this->m_nState;
    if ( m_nState )
    {
      (**m_nState)((_DWORD)((_DWORD)(m_nState)), (int)(1));
      this->m_nState = 0;
    }
    goto LABEL_10;
  }
  v2 = (void *)this->m_nState;
  if ( v2 )
  {
    (((NPC *)this->m_nState))->NPC::FreeBuffer();
    operator delete(v2);
    this->m_nState = 0;
    this->m_fBlendFactor = 0.0f;
    return;
  }
LABEL_10:
  this->m_fBlendFactor = 0.0f;
}

// 0x00439230
gbGeomNode * PalScript::LoadModel(const char *szFilename, int nActionIdx)
{
  gbGeomNode *v4; // edi
  gbGeomNode *v5; // ecx
  UICursor *v6; // ecx
  Actor *v7; // eax
  Actor *v8; // eax
  gbGeomNode *result; // eax
  char Destination[4]; // [esp+0x10] [ebp-0x14] BYREF
  OpenBaseFile v11; // [esp+0x14] [ebp-0x10] BYREF
  int v12; // [esp+0x20] [ebp-0x4]

  this->PalScript::ReleaseStateResource();
  *(_DWORD *)Destination = 0;
  strncpy(Destination, &szFilename[strlen(szFilename) - 3], 3u);
  v12 = 0;
  if ( !_strcmpi(Destination, byte_596424) )
  {
    LODWORD(this->m_fBlendFactor) = 1;
    v4 = (gbGeomNode *)operator new(0x118u);
    LOBYTE(v12) = 1;
LABEL_3:
    if ( v4 )
    {
      v4->gbGeomNode::gbGeomNode();
      v5 = (gbGeomNode *)v4;
    }
    else
    {
      v5 = 0;
    }
    LOBYTE(v12) = 0;
    this->m_nState = (int)v5;
    (((gbGeomNode *)v5))->gbGeomNode::LoadFromFile(szFilename, 0, 0);
    goto LABEL_13;
  }
  if ( !_strcmpi(Destination, byte_596420) )
  {
    LODWORD(this->m_fBlendFactor) = 3;
    v4 = (gbGeomNode *)operator new(0x118u);
    LOBYTE(v12) = 2;
    goto LABEL_3;
  }
  LODWORD(this->m_fBlendFactor) = 2;
  v7 = (Actor *)operator new(0x224u);
  LOBYTE(v12) = 3;
  if ( v7 )
    FastInit(v7);
  else
    v8 = 0;
  LOBYTE(v12) = 0;
  this->m_nState = (int)v8;
  LoadActionSequences(v8, szFilename, 0);
  (((Actor *)this->m_nState))->Actor::CompareActionName(nActionIdx, 0);
LABEL_13:
  (((UICursor *)v6))->UICursor::_todo_541CC0();
  v12 = -1;
  ((OpenNULLFile *)&v11)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x004393A0
char PalScript::CheckAnimOver()
{
  unsigned int v2; // eax
  struct gbNodeMsgObj v4; // [esp+0xC] [ebp-0x10] BYREF

  if ( LODWORD(this->m_fBlendFactor) != 3 || !(((gbVisNode *)this->m_nState))->gbVisNode::PopMessage(v4) )
    return 0;
  while ( 1 )
  {
    if ( v4.msgid == 1 )
    {
      v2 = gbCrc32Compute("over");
      if ( v4.param[0] == v2 )
        break;
    }
    if ( !(((gbVisNode *)this->m_nState))->gbVisNode::PopMessage(v4) )
      return 0;
  }
  return 1;
}

// 0x00439FE0
void * PalScript::GetRayToScreen(void *pRay, LPPOINT pResult)
{
  void *result; // eax
  float v4; // [esp+0x0] [ebp-0x2C]
  float v5; // [esp+0x4] [ebp-0x28]
  struct gbRay v6; // [esp+0x14] [ebp-0x18] BYREF

  memset(&v6, 0, sizeof(v6));
  v5 = 1.0f - ((float)pResult->y + (float)pResult->y) / (float)g_DrvInfo.height;
  v4 = ((float)pResult->x + (float)pResult->x) / (float)g_DrvInfo.width - 1.0f;
  (((gbCamera *)LODWORD(this->m_fInterval)))->gbCamera::GetRayToScreen(v4, v5, &v6);
  result = (void *)pRay;
  qmemcpy(pRay, &v6, 0x18u);
  return result;
}

// 0x0043A160
PalScript::PalScript()
{
  ClearSubArraySlot();
  ZeroInitSelf68();
  this->m_pCurrentTask_p = ((char *)0);
  this->m_fTimerAccum = 0.0f;
  this->m_pTaskPtr = ((void *)0);
  this->m_fTimerLimit = 10.0f;
  this->m_nWaitTimer = -1;
}

// 0x0043A250
int PalScript::MoveAndHide()
{
  int result; // eax

  (((UIWnd *)this->m_nTodo_04C))->UIWnd::MoveWindow();
  (((SceneObj *)this))->SceneObj::HideAll() /* [ROWTABLE] */;
  return result;
}

// 0x0043A270
int PalScript::RenderUI()
{
  int result; // eax
  int m_nAnimState; // eax
  gbTexture *TableEntry16; // edi
  int v5; // eax
  float v6; // st7
  double m_pCurrentTask_p; // st6
  gbDynVertBuf *DynVertBuf; // eax
  float m_CamObj; // st7
  int v10; // eax
  char *v11; // [esp+0x4] [ebp-B4h]
  struct gbUIQuad v12; // [esp+0x8] [ebp-B0h] BYREF
  struct gbTextureArray v13; // [esp+0x30] [ebp-0x88] BYREF
  int v14; // [esp+0x74] [ebp-0x44]
  int v15; // [esp+B4h] [ebp-0x4]

  result = this->m_bCreated;
  if ( result )
  {
    result = (int)this->m_pTaskPtr;
    if ( result > 0 )
    {
      m_nAnimState = this->m_nAnimState;
      if ( m_nAnimState )
      {
        if ( m_nAnimState == 1 )
        {
          TableEntry16 = (gbTexture *)GetTableEntry16(0);
          if ( TableEntry16 )
          {
            v5 = LODWORD(this->m_fScriptTimer) - this->m_nFrameCount;
            v12.color = -1;
            v12.z = 0.0;
            v12.sv = 0.0;
            v11 = (char *)this->m_CamObj - this->m_nState;
            v12.ev = (double)v5 / (double)TableEntry16->Height;
            v6 = (float)(int)v11 / (float)TableEntry16->Width;
            m_pCurrentTask_p = (double)(int)this->m_pCurrentTask_p;
            v12.su = m_pCurrentTask_p * v6;
            v12.eu = (m_pCurrentTask_p + 1.0) * v6;
            DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x114u);
            v12.sx = (float)this->m_nState;
            v12.ey = (float)this->m_nFrameCount;
            m_CamObj = (float)(int)this->m_CamObj;
            v13.nTex = 1;
            v13.pTexPt[0] = TableEntry16;
            v12.ex = m_CamObj;
            v12.sy = (float)SLODWORD(this->m_fScriptTimer);
            (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad(&v12, 1, g_pRenderEffect_189504C, &v13);
            (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
            return result;
          }
        }
      }
      else
      {
        v10 = GetTableEntry16((unsigned int)this->m_pCurrentTask_p);
        if ( v10 )
        {
          v14 = v10;
          v15 = 1;
          (((TextureLibDataBase *)&this->m_waitobj))->TextureLibDataBase::SetLibFolder((const char *)&this->m_nState, (int)&this->m_waitobj);
        }
      }
      (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
    }
  }
  return result;
}

// 0x0043A3E0
BOOL PalScript::UpdateTimer(int nVal, int nVal2)
{
  char *m_pTaskPtr; // edx
  float v5; // st7
  char *m_pCurrentTask_p; // eax
  int m_nTimerCount; // eax
  int m_nWaitTimer; // eax

  if ( !this->m_bCreated )
    return 0;
  if ( !*(_DWORD *)&this->m_bInitialized )
    return 0;
  m_pTaskPtr = (char *)this->m_pTaskPtr;
  if ( (int)m_pTaskPtr > 0 )
  {
    if ( this->m_fTimerLimit < 0.000049999999f )
      goto LABEL_11;
    v5 = *(float *)&nVal + this->m_fTimerAccum;
    this->m_fTimerAccum = v5;
    if ( v5 > 1.0 / this->m_fTimerLimit )
    {
      m_pCurrentTask_p = (char *)this->m_pCurrentTask_p;
      this->m_fTimerAccum = 0.0f;
      this->m_pCurrentTask_p = ((char *)(m_pCurrentTask_p + 1));
    }
    if ( (int)this->m_pCurrentTask_p >= (int)m_pTaskPtr )
    {
LABEL_11:
      m_nTimerCount = this->m_nTimerCount;
      this->m_pCurrentTask_p = ((char *)0);
      this->m_nTimerCount = m_nTimerCount + 1;
    }
    m_nWaitTimer = this->m_nWaitTimer;
    if ( m_nWaitTimer > 0 && this->m_nTimerCount >= m_nWaitTimer )
      this->m_pCurrentTask_p = ((char *)(m_pTaskPtr - 1));
    return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  }
  else
  {
    ++this->m_nTimerCount;
    return 0;
  }
}

// 0x0043AA00
gbVFileSystem * PalScript::OpenScript(const char *pszName, char pData)
{
  gbTexture *m_pTexture; // ecx
  int v5; // edi
  CHAR *v6; // eax
  gbTexture *v7; // ecx
  gbVFileSystem *result; // eax
  OpenBaseFile v9; // [esp+0x8] [ebp-0x110] BYREF
  char Buffer[256]; // [esp+0xC] [ebp-0x10C] BYREF
  int v11; // [esp+0x114] [ebp-0x4]

  v11 = 0;
  sprintf(Buffer, "%s", pszName);
  m_pTexture = (gbTexture *)this->m_pTexture;
  if ( m_pTexture )
    (((gbRefObject *)m_pTexture))->gbRefObject::Release();
  if ( pData )
  {
    v5 = *(_DWORD *)*(void**)(gfxMgr);
    v6 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(Buffer);
    this->m_pTexture = ((gbTexture *)((gbTexture *)gfxMgr->NewTexture((const char *)v6)));
    this->m_pTextureInfo = ((_PlugInfo *)((_PlugInfo *)(((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(Buffer)));
  }
  else
  {
    this->m_pTexture = ((gbTexture *)((gbTexture *)gfxMgr->NewTexture((const char *)Buffer)));
  }
  v7 = (gbTexture *)this->m_pTexture;
  if ( v7 )
    (((gbTexture *)v7))->gbTexture::LoadTexture(1);
  v11 = -1;
  ((OpenNULLFile *)&v9)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x0044B8A0
LPSTR PalScript::SetDialogTemplate(CHAR *String1, CHAR *lpString2)
{
  int *p_m_DialogTemplate; // ebp
  LPSTR result; // eax
  CHAR *p_m_DialogByte; // ecx
  PalScript *v7; // [esp-0x8] [ebp-0x14]

  p_m_DialogTemplate = (int *)&this->m_RoleSlotArray.overlay.m_DialogTemplate;
  result = (LPSTR)lstrcmpA((LPCSTR)&this->m_RoleSlotArray.script_state + 128, String1);
  if ( result )
  {
    this->m_RoleSlotArray.overlay.m_nDialogData = 0;
    *((_BYTE *)&this->m_RoleSlotArray.script_state + 386) = 0;
    this->m_RoleSlotArray.overlay.m_nDialogResult = 0;
    this->m_RoleSlotArray.overlay.m_DialogByte = 0;
    *(_BYTE *)&this->m_szDialog1.overlay = 0;
    this->m_szDialog2[0] = 0;
    this->m_DialogSub = 0;
    this->PalScript::LoadFromFile(String1);
    this->PalScript::SetDirectory("sec1");
    while ( this->PalScript::HasNext() )
    {
      switch ( (((DealData *)this))->DealData::CompareString("M_ID", (LPCSTR)this) )
      {
        case 0:
          this->PalScript::LoadNext();
          this->m_RoleSlotArray.overlay.m_nDialogData = atoi((const char *)this);
          break;
        case 1:
          this->PalScript::LoadNext();
          lstrcpyA((LPSTR)&this->m_RoleSlotArray.script_state + 386, (LPCSTR)this);
          break;
        case 2:
          this->PalScript::LoadNext();
          this->m_RoleSlotArray.overlay.m_nDialogResult = atoi((const char *)this);
          break;
        case 3:
          this->PalScript::LoadNext();
p_m_DialogByte = (CHAR *)&this->m_RoleSlotArray.overlay.m_DialogByte;
          goto LABEL_11;
        case 4:
          this->PalScript::LoadNext();
          lstrcpyA((LPSTR)&this->m_szDialog1, (LPCSTR)this);
          break;
        case 5:
          this->PalScript::LoadNext();
          lstrcpyA(this->m_szDialog2, (LPCSTR)this);
          break;
        case 6:
          this->PalScript::LoadNext();
p_m_DialogByte = (CHAR *)&this->m_DialogSub;
LABEL_11:
          lstrcpyA((char *)p_m_DialogByte, (LPCSTR)v7);
          break;
        default:
          break;
      }
    }
    return lstrcpyA((LPSTR)p_m_DialogTemplate, String1);
  }
  return result;
}

// 0x00522130
char PalScript::LoadSceneConfig(char *filename)
{
  int (__stdcall *v4)(LPCSTR, LPCSTR); // ebp
  const CHAR *i; // edi
  int v6; // edx
  const CHAR *j; // edi
  int v8; // ebp
  const CHAR *k; // edi
  int v10; // eax
  int v11; // eax
  int v12; // ebp
  const CHAR *m; // edi
  int v14; // eax
  int v15; // eax
  int v16; // ebp
  const CHAR *n; // edi
  int v18; // eax
  int v19; // eax
  int v20; // ebp
  const CHAR *ii; // edi
  int v22; // eax
  int v23; // eax
  int v24; // ebp
  const CHAR *jj; // edi
  int v26; // ebp
  const CHAR *kk; // edi
  int v28; // ebp
  const CHAR *mm; // edi
  int v30; // ebp
  const CHAR *nn; // edi
  char *filenamea; // [esp+0x8] [ebp+0x4]
  char *filenameb; // [esp+0x8] [ebp+0x4]

  if ( LOBYTE((*(void **)(this))) )
    return 0;
  (((PalScript *)&this->m_pinst))->PalScript::LoadFromFile(filename);
  (((PalScript *)&this->m_pinst))->PalScript::SetDirectory("sec1");
  if ( (((PalScript *)&this->m_pinst))->PalScript::HasNext() )
  {
    v4 = lstrcmpA;
    do
    {
      filenamea = 0;
      for ( i = "HL_E"; ; i += 30 )
      {
        if ( !v4(i, byte_592DA4) )
        {
          v6 = -1;
          goto LABEL_11;
        }
        if ( !v4(i, (LPCSTR)&this->m_pinst) )
          break;
        ++filenamea;
      }
      v6 = (int)filenamea;
LABEL_11:
      this->m_RoleSlotArray.overlay.m_nConfigIndex = v6;
      memset((char *)&this->m_RoleSlotArray.script_state + 220 * v6 + 160, 0, 0xC0u);
      if ( v4((LPCSTR)&this->m_pinst, "#") )
      {
        do
        {
          (((PalScript *)&this->m_pinst))->PalScript::HasNext();
          filenameb = 0;
          for ( j = "Sale"; v4(j, byte_592DA4); j += 30 )
          {
            v4 = lstrcmpA;
            if ( !lstrcmpA(j, (LPCSTR)&this->m_pinst) )
            {
              switch ( (unsigned int)filenameb )
              {
                case 0u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *((_BYTE *)&this->m_RoleSlotArray.script_state
                  + 220 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                  + 136) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 1u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *((_BYTE *)&this->m_RoleSlotArray.script_state
                  + 220 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                  + 137) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 2u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *((_BYTE *)&this->m_RoleSlotArray.script_state
                  + 220 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                  + 138) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 3u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *((_BYTE *)&this->m_RoleSlotArray.script_state
                  + 220 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                  + 139) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 4u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *((_BYTE *)&this->m_RoleSlotArray.script_state
                  + 220 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                  + 140) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 5u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *((_BYTE *)&this->m_RoleSlotArray.script_state
                  + 220 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                  + 141) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 6u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *((_BYTE *)&this->m_RoleSlotArray.script_state
                  + 220 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                  + 142) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 7u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *(&this->m_RoleSlotArray.overlay.m_SceneCfg_fParam0 + 55
                                                                      * this->m_RoleSlotArray.overlay.m_nConfigIndex) = atof((const char *)&this->m_pinst);
                  break;
                case 8u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *(&this->m_RoleSlotArray.overlay.m_SceneCfg_nParam0 + 55
                                                                      * this->m_RoleSlotArray.overlay.m_nConfigIndex) = atoi((const char *)&this->m_pinst);
                  break;
                case 9u:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *(&this->m_RoleSlotArray.overlay.m_SceneCfg_nParam1 + 55
                                                                      * this->m_RoleSlotArray.overlay.m_nConfigIndex) = atoi((const char *)&this->m_pinst);
                  break;
                case 0xAu:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  *(&this->m_RoleSlotArray.overlay.m_SceneCfg_nParam2 + 55
                                                                      * this->m_RoleSlotArray.overlay.m_nConfigIndex) = atoi((const char *)&this->m_pinst);
                  break;
                case 0xBu:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "&") )
                  {
                    (((PalScript *)&this->m_pinst))->PalScript::HasNext();
                    v8 = 0;
                    for ( k = "RESUME"; ; k += 30 )
                    {
                      if ( !lstrcmpA(k, byte_592DA4) )
                      {
                        v10 = -1;
                        goto LABEL_35;
                      }
                      if ( !lstrcmpA(k, (LPCSTR)&this->m_pinst) )
                        break;
                      ++v8;
                    }
                    v10 = v8;
LABEL_35:
                    if ( v10 )
                    {
                      v11 = v10 - 1;
                      if ( v11 )
                      {
                        if ( v11 == 1 )
                        {
                          (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                          this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                  + 13] = atof((const char *)&this->m_pinst);
                        }
                      }
                      else
                      {
                        (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                        this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex + 12] = atof((const char *)&this->m_pinst);
                      }
                    }
                    else
                    {
                      (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                      this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex + 11] = atof((const char *)&this->m_pinst);
                    }
                  }
                  break;
                case 0xCu:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "&") )
                  {
                    (((PalScript *)&this->m_pinst))->PalScript::HasNext();
                    v12 = 0;
                    for ( m = "RESUME"; ; m += 30 )
                    {
                      if ( !lstrcmpA(m, byte_592DA4) )
                      {
                        v14 = -1;
                        goto LABEL_50;
                      }
                      if ( !lstrcmpA(m, (LPCSTR)&this->m_pinst) )
                        break;
                      ++v12;
                    }
                    v14 = v12;
LABEL_50:
                    if ( v14 )
                    {
                      v15 = v14 - 1;
                      if ( v15 )
                      {
                        if ( v15 == 1 )
                        {
                          (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                          this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                  + 25] = atof((const char *)&this->m_pinst);
                        }
                      }
                      else
                      {
                        (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                        this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex + 24] = atof((const char *)&this->m_pinst);
                      }
                    }
                    else
                    {
                      (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                      this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex + 23] = atof((const char *)&this->m_pinst);
                    }
                  }
                  break;
                case 0xDu:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "&") )
                  {
                    (((PalScript *)&this->m_pinst))->PalScript::HasNext();
                    v16 = 0;
                    for ( n = "RESUME"; ; n += 30 )
                    {
                      if ( !lstrcmpA(n, byte_592DA4) )
                      {
                        v18 = -1;
                        goto LABEL_65;
                      }
                      if ( !lstrcmpA(n, (LPCSTR)&this->m_pinst) )
                        break;
                      ++v16;
                    }
                    v18 = v16;
LABEL_65:
                    if ( v18 )
                    {
                      v19 = v18 - 1;
                      if ( v19 )
                      {
                        if ( v19 == 1 )
                        {
                          (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                          this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                  + 37] = atof((const char *)&this->m_pinst);
                        }
                      }
                      else
                      {
                        (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                        this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex + 36] = atof((const char *)&this->m_pinst);
                      }
                    }
                    else
                    {
                      (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                      this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex + 35] = atof((const char *)&this->m_pinst);
                    }
                  }
                  break;
                case 0xEu:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "&") )
                  {
                    (((PalScript *)&this->m_pinst))->PalScript::HasNext();
                    v20 = 0;
                    for ( ii = "RESUME"; ; ii += 30 )
                    {
                      if ( !lstrcmpA(ii, byte_592DA4) )
                      {
                        v22 = -1;
                        goto LABEL_80;
                      }
                      if ( !lstrcmpA(ii, (LPCSTR)&this->m_pinst) )
                        break;
                      ++v20;
                    }
                    v22 = v20;
LABEL_80:
                    if ( v22 )
                    {
                      v23 = v22 - 1;
                      if ( v23 )
                      {
                        if ( v23 == 1 )
                        {
                          (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                          this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                  + 1] = atof((const char *)&this->m_pinst);
                        }
                      }
                      else
                      {
                        (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                        this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex] = atof((const char *)&this->m_pinst);
                      }
                    }
                    else
                    {
                      (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                      *((float *)&this->m_RoleSlotArray.overlay.m_SceneCfg_data
                      + 55 * this->m_RoleSlotArray.overlay.m_nConfigIndex) = atof((const char *)&this->m_pinst);
                    }
                  }
                  break;
                case 0xFu:
                  (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                  this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex + 47] = atof((const char *)&this->m_pinst);
                  break;
                case 0x10u:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "*") )
                  {
                    (((PalScript *)&this->m_pinst))->PalScript::HasNext();
                    v24 = 0;
                    for ( jj = "lo_PeriodPlus"; lstrcmpA(jj, byte_592DA4); jj += 30 )
                    {
                      if ( !lstrcmpA(jj, (LPCSTR)&this->m_pinst) )
                      {
                        switch ( v24 )
                        {
                          case 0:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 16] = atof((const char *)&this->m_pinst);
                            break;
                          case 1:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 15] = atof((const char *)&this->m_pinst);
                            break;
                          case 2:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 14] = atof((const char *)&this->m_pinst);
                            break;
                          case 3:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 19] = atof((const char *)&this->m_pinst);
                            break;
                          case 4:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 18] = atof((const char *)&this->m_pinst);
                            break;
                          case 5:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 17] = atof((const char *)&this->m_pinst);
                            break;
                          case 6:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 22] = atof((const char *)&this->m_pinst);
                            break;
                          case 7:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 21] = atof((const char *)&this->m_pinst);
                            break;
                          case 8:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 20] = atof((const char *)&this->m_pinst);
                            break;
                          default:
                            goto LABEL_104;
                        }
                        break;
                      }
                      ++v24;
                    }
LABEL_104:
                    ;
                  }
                  break;
                case 0x11u:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "*") )
                  {
                    (((PalScript *)&this->m_pinst))->PalScript::HasNext();
                    v26 = 0;
                    for ( kk = "lo_PeriodPlus"; lstrcmpA(kk, byte_592DA4); kk += 30 )
                    {
                      if ( !lstrcmpA(kk, (LPCSTR)&this->m_pinst) )
                      {
                        switch ( v26 )
                        {
                          case 0:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 28] = atof((const char *)&this->m_pinst);
                            break;
                          case 1:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 27] = atof((const char *)&this->m_pinst);
                            break;
                          case 2:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 26] = atof((const char *)&this->m_pinst);
                            break;
                          case 3:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 31] = atof((const char *)&this->m_pinst);
                            break;
                          case 4:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 30] = atof((const char *)&this->m_pinst);
                            break;
                          case 5:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 29] = atof((const char *)&this->m_pinst);
                            break;
                          case 6:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 34] = atof((const char *)&this->m_pinst);
                            break;
                          case 7:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 33] = atof((const char *)&this->m_pinst);
                            break;
                          case 8:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 32] = atof((const char *)&this->m_pinst);
                            break;
                          default:
                            goto LABEL_121;
                        }
                        break;
                      }
                      ++v26;
                    }
LABEL_121:
                    ;
                  }
                  break;
                case 0x12u:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "*") )
                  {
                    (((PalScript *)&this->m_pinst))->PalScript::HasNext();
                    v28 = 0;
                    for ( mm = "lo_PeriodPlus"; lstrcmpA(mm, byte_592DA4); mm += 30 )
                    {
                      if ( !lstrcmpA(mm, (LPCSTR)&this->m_pinst) )
                      {
                        switch ( v28 )
                        {
                          case 0:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 40] = atof((const char *)&this->m_pinst);
                            break;
                          case 1:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 39] = atof((const char *)&this->m_pinst);
                            break;
                          case 2:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 38] = atof((const char *)&this->m_pinst);
                            break;
                          case 3:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 43] = atof((const char *)&this->m_pinst);
                            break;
                          case 4:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 42] = atof((const char *)&this->m_pinst);
                            break;
                          case 5:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 41] = atof((const char *)&this->m_pinst);
                            break;
                          case 6:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 46] = atof((const char *)&this->m_pinst);
                            break;
                          case 7:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 45] = atof((const char *)&this->m_pinst);
                            break;
                          case 8:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 44] = atof((const char *)&this->m_pinst);
                            break;
                          default:
                            goto LABEL_138;
                        }
                        break;
                      }
                      ++v28;
                    }
LABEL_138:
                    ;
                  }
                  break;
                case 0x13u:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "*") )
                  {
                    (((PalScript *)&this->m_pinst))->PalScript::HasNext();
                    v30 = 0;
                    for ( nn = "lo_PeriodPlus"; lstrcmpA(nn, byte_592DA4); nn += 30 )
                    {
                      if ( !lstrcmpA(nn, (LPCSTR)&this->m_pinst) )
                      {
                        switch ( v30 )
                        {
                          case 0:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 4] = atof((const char *)&this->m_pinst);
                            break;
                          case 1:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 3] = atof((const char *)&this->m_pinst);
                            break;
                          case 2:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 2] = atof((const char *)&this->m_pinst);
                            break;
                          case 3:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 7] = atof((const char *)&this->m_pinst);
                            break;
                          case 4:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 6] = atof((const char *)&this->m_pinst);
                            break;
                          case 5:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 5] = atof((const char *)&this->m_pinst);
                            break;
                          case 6:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 10] = atof((const char *)&this->m_pinst);
                            break;
                          case 7:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 9] = atof((const char *)&this->m_pinst);
                            break;
                          case 8:
                            (((PalScript *)&this->m_pinst))->PalScript::LoadNext();
                            this->m_RoleSlotArray.overlay.m_fSceneCfg[55 * this->m_RoleSlotArray.overlay.m_nConfigIndex
                                                                    + 8] = atof((const char *)&this->m_pinst);
                            break;
                          default:
                            goto LABEL_155;
                        }
                        break;
                      }
                      ++v30;
                    }
LABEL_155:
                    ;
                  }
                  break;
                default:
                  goto LABEL_156;
              }
              break;
            }
            ++filenameb;
          }
LABEL_156:
          v4 = lstrcmpA;
        }
        while ( lstrcmpA((LPCSTR)&this->m_pinst, "#") );
      }
    }
    while ( (((PalScript *)&this->m_pinst))->PalScript::HasNext() );
  }
  LOBYTE((*(void **)(this))) = 1;
  return 1;
}

// 0x00529440
int PalScript::LoadResource(char *filename)
{
  PalScript *v3; // esi
  int result; // eax
  char *v5; // edi

  v3 = (PalScript *)((char *)this + 2900);
  (((PalScript *)((char *)this + 2900)))->PalScript::LoadFromFile(filename);
  (((PalScript *)v3))->PalScript::SetDirectory("sec1");
  result = (((PalScript *)v3))->PalScript::HasNext();
  if ( result )
  {
    v5 = (char *)&this[1].m_RoleSlotArray.script_state.m_szSceneUIText[272];
    do
    {
      result = _strcmpi(g_LanguageCode, (const char *)v3);
      if ( !result )
        break;
      (((PalScript *)v3))->PalScript::LoadNext();
      strncpy(v5, (const char *)v3, 0x100u);
      v5 += 256;
      result = (((PalScript *)v3))->PalScript::HasNext();
    }
    while ( result );
  }
  return result;
}

// 0x0052BE40
int PalScript::LoadEncampConfig()
{
  int *p_m_EncampConfig; // esi
  int result; // eax

  p_m_EncampConfig = (int *)&this->m_EncampConfig;
  (((PalScript *)&this->m_EncampConfig))->PalScript::LoadFromFile("SubGame\\Encampment\\Encamp.rmk");
  (((PalScript *)p_m_EncampConfig))->PalScript::SetDirectory("sec1");
  for ( result = (((PalScript *)p_m_EncampConfig))->PalScript::HasNext();
        result;
        result = (((PalScript *)p_m_EncampConfig))->PalScript::HasNext() )
  {
    result = _strcmpi(g_LanguageCode, (const char *)p_m_EncampConfig);
    if ( !result )
      break;
    (((PalScript *)p_m_EncampConfig))->PalScript::LoadNext();
    strncpy((char *)&this->m_RoleSlotArray.script_state._todo_36c, (const char *)p_m_EncampConfig, 0x100u);
  }
  return result;
}

// 0x00535010
int PalScript::ResetAll()
{
  int result; // eax

  result = 0;
  (*(void **)(this)) = (void *)(0);
  this->m_pinst = ((scScriptInstance *)0);
  this->m_waitobj = ((PtrArray *)0);
  this->m_fBlendFactor = 0.0f;
  this->m_nState = 0;
  this->m_nFrameCount = 0;
  *(&this->m_nTodo_024 + 2) = 0;
  this->m_nTodo_024 = 0;
  *(&this->m_nTodo_024 + 1) = 0;
  return result;
}

// 0x00535710
gbVFileSystem * PalScript::LoadVisNode(double String2, char *pszBuf, char *pszBuf2)
{
  void ( ***m_nDialogResult)(_DWORD, int); // ecx
  gbVisNode *v6; // eax
  int v7; // edi
  gbVFileSystem *result; // eax
  int v9; // [esp+0x0] [ebp-0x434]
  int v10; // [esp+0x0] [ebp-0x434]
  OpenSceneFile v11; // [esp+0x10] [ebp-0x424] BYREF
  gbVisNode *v12; // [esp+0x14] [ebp-0x420]
  char Buffer[253]; // [esp+0x18] [ebp-0x41C] BYREF
  __int16 v14; // [esp+0x115] [ebp-0x31F]
  char v15; // [esp+0x117] [ebp-0x31D]
  char String1[260]; // [esp+0x118] [ebp-0x31C] BYREF
  TxtFile v17; // [esp+0x21C] [ebp-0x218] BYREF
  int v18; // [esp+0x430] [ebp-0x4]

  LoadScene((char *)LODWORD(String2), (char *)HIDWORD(String2), 1);
  (*(void **)(this)) = (void *)UISceneUpdate();
  strcpy((char *)String1, "scene\\");
  strcat((char *)String1, (const char *)LODWORD(String2));
  memset(Buffer, 0, sizeof(Buffer));
  v14 = 0;
  v18 = 0;
  v15 = 0;
  sprintf(Buffer, "%s\\%s.lgt", (const char *)HIDWORD(String2), (const char *)HIDWORD(String2));
  if ( (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::FileExistNum(Buffer) )
  {
    m_nDialogResult = (void ( ***)(_DWORD, int))this[1].m_RoleSlotArray.overlay.m_nDialogResult;
    if ( m_nDialogResult )
    {
      (**m_nDialogResult)((_DWORD)((_DWORD)(m_nDialogResult)), (int)(1));
      this[1].m_RoleSlotArray.overlay.m_nDialogResult = 0;
    }
    v6 = (gbVisNode *)operator new(0x58u);
    v7 = (int)v6;
    v12 = (gbVisNode *)v6;
    LOBYTE(v18) = 1;
    if ( v6 )
      v6->gbVisNode::gbVisNode();
    else
      v7 = 0;
    LOBYTE(v18) = 0;
    this[1].m_RoleSlotArray.overlay.m_nDialogResult = v7;
    this[1].m_RoleSlotArray.overlay.m_nDialogResult = (int)gbLoadLightFile(Buffer);
  }
  *((_BYTE *)&this[1].m_RoleSlotArray.script_state._todo_36c + 32) = 1;
  *((_BYTE *)&this[1].m_RoleSlotArray.script_state._todo_36c + 33) = 0;
  LOBYTE(v18) = 2;
  (((PalScript *)&v17))->PalScript::LoadFromFile("datascript\\SceneName.txt");
  (((PalScript *)&v17))->PalScript::SetDirectory((char *)(*(void **)(this)));
  if ( !(((PalScript *)&v17))->PalScript::FindSaveStateString((PalScript *)&this->__vftable[2], (char *)&this[1].m_RoleSlotArray.script_state._todo_36c + 33, (char *)0x80, v9) )
    (((PalScript *)&v17))->PalScript::FindSaveStateString((PalScript *)&dir[12], (char *)&this[1].m_RoleSlotArray.script_state._todo_36c + 33, (char *)0x80, v10);
  LOBYTE(v18) = 0;
  (((PalScript *)&v17))->PalScript::Cleanup();
  v18 = -1;
  (((OpenSceneFile *)&v11))->OpenSceneFile::~OpenSceneFile();
  return result;
}

// 0x00538D60
void PalScript::DestroyInstances(double nActionID, int *p_DWORD)
{
  int v4; // edx
  PtrArray *m_waitobj; // esi
  scScriptInstance *i; // edi
  int *v7; // edi
  float as_int; // esi
  unsigned __int8 *v9; // ebp
  int v10; // ecx
  PalScriptMgr *v11; // eax
  float j; // esi
  int RoleByState; // eax
  int v14; // ecx
  void *v15; // [esp-0x8] [ebp-D0h]
  int v16; // [esp-0x4] [ebp-CCh]
  void *v17; // [esp-0x4] [ebp-CCh]
  int v18; // [esp+0x0] [ebp-C8h]
  int v19; // [esp+0x4] [ebp-C4h]
  char pActionType; // [esp+0x13] [ebp-B5h] BYREF
  int m_nTodo_28; // [esp+0x14] [ebp-B4h]
  char String2[132]; // [esp+0x18] [ebp-B0h] BYREF
  Array v23; // [esp+0x9C] [ebp-0x2C] BYREF
  char v24; // [esp+ACh] [ebp-0x1C] BYREF
  void *Block; // [esp+B0h] [ebp-0x18]
  int v26; // [esp+B4h] [ebp-0x14]
  int v27; // [esp+B8h] [ebp-0x10]
  int v28; // [esp+C4h] [ebp-0x4]

  LOBYTE(v23.m_pDataStart) = pActionType;
  memset(&v23.m_nSize, 0, 12);
  v28 = 0;
  InitAction((Actor *)&v24, &pActionType);
  v28 = 1;
  qmemcpy(String2, (const void *)LODWORD(nActionID), sizeof(String2));
  m_waitobj = (PtrArray *)this->m_waitobj;
  for ( i = this->m_pinst; i != (scScriptInstance *)m_waitobj; i = (scScriptInstance *)((char *)i + 164) )
  {
    if ( Actor::CompareModelName((char *)i, String2) )
      break;
  }
  if ( i == (scScriptInstance *)this->m_waitobj )
  {
    v7 = (int *)Actor::SelectPointer((int *)this->m_nTodo_28, (int *)this->m_nTodo_28, *(int **)&this->m_nTodo_024);
    nullsub_2(v7, this->m_nTodo_28);
    v16 = v26;
    v15 = (void *)Block;
    this->m_nTodo_28 = (int)v7;
    v28 = -1;
    nullsub_2(v15, v16);
    operator delete(Block);
    Block = 0;
    v26 = 0;
    v27 = 0;
    (((Array *)&v23))->Array::Free();
  }
  else
  {
    as_int = i[1].reg[4].data.as_int;
    if ( LODWORD(as_int) != *(_DWORD *)&i[1].reg[5].type )
    {
      v9 = (unsigned __int8 *)(LODWORD(as_int) + 620);
      do
      {
        if ( !(((Actor *)this))->Actor::IterateAllocBuffer((unsigned __int8)*(_BYTE *)LODWORD(as_int)) )
        {
          LOWORD(v10) = (unsigned __int8)*(_BYTE *)LODWORD(as_int);
          (((PalScript *)LODWORD(nActionID)))->PalScript::SetAction(v10);
          if ( v11 )
            (((PalScriptMgr *)v11))->PalScriptMgr::UpdateScriptRoles(_pal3_coerce_f64(__PAIR64__((unsigned int)v9, LODWORD(as_int))), v18, v19);
        }
        LODWORD(as_int) += 656;
        v9 += 656;
      }
      while ( LODWORD(as_int) != *(_DWORD *)&i[1].reg[5].type );
    }
    for ( j = i[1].reg[6].data.as_int; LODWORD(j) != *(_DWORD *)&i[1].reg[7].type; LODWORD(j) += 2 )
    {
      LOBYTE(v4) = *(_BYTE *)LODWORD(j);
      RoleByState = SceneMgr_FindRoleByState(v4);
      if ( RoleByState )
        *(_DWORD *)(RoleByState + 632) = *(unsigned __int8 *)(LODWORD(j) + 1);
    }
    v14 = *(_DWORD *)&this->m_nTodo_024;
    v17 = (void *)Block;
    m_nTodo_28 = this->m_nTodo_28;
    this->m_nTodo_28 = v14;
    operator delete(v17);
    Block = 0;
    v26 = 0;
    v27 = 0;
    operator delete((void *)v23.m_nSize);
  }
}
