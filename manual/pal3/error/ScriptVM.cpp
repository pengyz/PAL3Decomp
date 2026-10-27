#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ScriptVM.h"
#include "Misc/BINK.h"
#include "Combat/CCBStageRole.h"
#include "Misc/CG_Entry.h"
#include "Render/CScreenMode.h"
#include "Scene/CameraCtrl.h"
#include "Misc/FightInfo.h"
#include "Misc/GeomNode.h"
#include "Role/Object3D.h"
#include "Misc/OpenSceneFile.h"
#include "GameBase/PAL3.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget3.h"
#include "Role/Role.h"
#include "Misc/RoleCameraCtrl.h"
#include "Role/RoleSystem.h"
#include "Scene/Scene.h"
#include "Scene/SceneMgr.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/UIBigMap.h"
#include "Misc/scAsmDecoder.h"
#include "Misc/tagRoleSystemData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

class RoleCameraCtrl;

// Unnamed globals (extern)
extern RoleCameraCtrl stru_DBA134;

// 0x00423880
void ScriptVM::ProcessFrame()
{
  int i; // eax
  float v3; // edi
  int v4; // eax
  void **m_nPathParam; // eax
  float *v6; // eax
  float v7; // ecx
  char *m_pPathKeys; // [esp-0xC] [ebp-0x24]
  void **v9; // [esp+0x0] [ebp-0x18]

  (((BINK *)this))->BINK::Destroy();
  for ( i = this->m_nPathStep; i; i = this->m_nPathStep )
  {
    LODWORD(v3) = LODWORD(this->m_fPathStartZ) + 76;
    v4 = i - 1;
    this->m_fPathStartZ = v3;
    this->m_nPathStep = v4;
    if ( !v4 || LODWORD(v3) == LODWORD(this->m_fPathStartY) )
    {
      m_nPathParam = (void **)this->m_nPathParam;
      this->m_nPathParam = (int)(m_nPathParam + 1);
      operator delete(*m_nPathParam);
      if ( this->m_nPathStep )
      {
        v6 = (float *)this->m_nPathParam;
        v7 = *v6;
        this->m_fPathStartX = *v6;
        LODWORD(this->m_fPathStartY) = LODWORD(v7) + 4028;
        this->m_fPathStartZ = v7;
        this->m_nPathParam = (int)v6;
      }
      else
      {
        this->m_fPathStartX = 0.0f;
        this->m_fPathStartY = 0.0f;
        this->m_fPathStartZ = 0.0f;
        this->m_nPathParam = 0;
        this->m_fPathEndX = 0.0f;
        m_pPathKeys = (char *)this->m_pPathKeys;
        this->m_fPathEndY = 0.0f;
        this->m_nTodo_358 = ((char *)0);
        this->m_pPathCurrent = ((char *)0);
        operator delete(m_pPathKeys);
      }
    }
  }
  GetActorMgr();
  (((RenderTarget3 *)this != 0 ? (RenderTarget3 *)&this->m_bufTail : 0))->RenderTarget3::_nearby_4b6ca0(v9);
}

// 0x00424C20
void ScriptVM::ExecuteBlock()
{
    unsigned long reg_EAX = 0;
    unsigned long reg_EBP = 0;
    unsigned long reg_EBX = 0;
    unsigned long reg_ECX = 0;
    unsigned long reg_EDI = 0;
    unsigned long reg_EDX = 0;

  char v2; // al
  int v3; // eax
  int v4; // eax
  CScreenMode *v5; // ecx
  PtrArray *SoundList; // eax
  float z; // ecx
  int RolePtr; // eax
  float v16; // eax
  int v17; // ebx
  float v18; // eax
  int v19; // ecx
  float x; // eax
  float v23; // ecx
  int v26; // eax
  gbVec3D *v29; // ecx
  float v30; // edx
  char v32; // dl
  int v36; // eax
  CScreenMode *v37; // ecx
  char v38; // al
  PtrArray *v39; // eax
  float v40; // eax
  RoleSystem *v43; // edi
  RoleSystem *v44; // ecx
  CScreenMode *v45; // ecx
  char v46; // al
  PtrArray *v47; // eax
  RoleSystem *v49; // ecx
  char v50; // al
  CScreenMode *v51; // ecx
  CScreenMode *v52; // ecx
  PtrArray *v53; // eax
  float v57; // eax
  gbMatrix4 *v62; // edi
  int v63; // ebx
  float *p_xy; // eax
  int v65; // ecx
  int v66; // edx
  int v68; // ebp
  int v72; // eax
  int v73; // ecx
  char v83; // al
  char *v84; // eax
  float *v85; // edi
  float v90; // ecx
  PtrArray *v92; // eax
  int v93; // eax
  PalScriptMgr *v94; // ecx
  int v95; // eax
  CScreenMode *v96; // ecx
  PtrArray *v97; // eax
  char v98; // al
  float v100; // eax
  int v102; // eax
  int v103; // eax
  char v104; // al
  CScreenMode *v108; // ecx
  int v109; // eax
  int v110; // eax
  PalScriptMgr *v112; // ecx
  int v113; // eax
  int v114; // eax
  PtrArray *v115; // eax
  int v116; // ecx
  char v117; // al
  float v118; // edx
  float v120; // eax
  float y; // ecx
  float v122; // edx
  PtrArray *v123; // eax
  int v125; // eax
  float v129; // eax
  float v130; // ecx
  float v131; // edx
  CScreenMode *v134; // ecx
  PtrArray *v136; // eax
  bool v137; // al
  float v140; // ecx
  float v142; // eax
  char v144; // bl
  int v145; // edx
  char v146; // al
  char v147; // al
  CScreenMode *v148; // ecx
  PtrArray *v149; // eax
  CScreenMode *v150; // ecx
  PtrArray *v151; // eax
  __int64 v155; // rax
  int v156; // ecx
  int v157; // ecx
  int v158; // eax
  int v159; // edx
  float v162; // edx
  float v163; // eax
  float v165; // edi
  float v166; // ebx
  RoleSystem *m_pCmdList; // ecx
  int v169; // ecx
  RoleSystem *v172; // edx
  int x_low; // edi
  float v174; // ecx
  float v177; // ecx
  PtrArray *v180; // eax
  char *v181; // eax
  int v182; // [esp-0x4] [ebp-0x114]
  float nType; // [esp+0x0] [ebp-0x110]
  int nTypea; // [esp+0x0] [ebp-0x110]
  int fVal; // [esp+0x4] [ebp-0x10C]
  float fVala; // [esp+0x4] [ebp-0x10C]
  int v187; // [esp+0x8] [ebp-0x108]
  int v188; // [esp+0x8] [ebp-0x108]
  unsigned __int8 v189; // [esp+0xC] [ebp-0x104]
  unsigned __int8 v190; // [esp+0xC] [ebp-0x104]
  unsigned __int8 v191; // [esp+0xC] [ebp-0x104]
  gbVec3D pfVal2; // [esp+0x1C] [ebp-F4h] BYREF
  gbVec3D pParams; // [esp+0x28] [ebp-E8h] BYREF
  gbVec3D nSceneIdx; // [esp+0x34] [ebp-DCh] BYREF
  gbVec3D nVal1; // [esp+0x40] [ebp-D0h] BYREF
  gbVec3D v196; // [esp+0x4C] [ebp-C4h] BYREF
  int v197; // [esp+0x58] [ebp-B8h]
  int v198; // [esp+0x5C] [ebp-B4h]
  float pData[3]; // [esp+0x60] [ebp-B0h] BYREF
  float v200[3]; // [esp+0x6C] [ebp-A4h] BYREF
  gbMatrix4 v201; // [esp+0x78] [ebp-0x98] BYREF
  gbMatrix4 pMatrix; // [esp+C4h] [ebp-0x4C] BYREF
  RoleSystem *v208; // [esp+0x114] [ebp+0x4]
  char v209; // [esp+0x118] [ebp+0x8]
  int v210; // [esp+0x11C] [ebp+0xC]
v2 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
  if ( !v2 )
    return;
  switch ( this->m_nTodo_0F4 )
  {
    case 0:
      if ( !v210 )
      {
        PalScriptMgr::ClearAllScript();
        if ( !v3 )
        {
          (((PalScriptMgr *)*((PalScriptMgr **)&this->m_nPauseState + 11)))->PalScriptMgr::Destroy();
          *(&this->m_nPathStep + 3) = v4;
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
          v187 = *(&this->m_nPathStep + 3);
          SoundList = (((CScreenMode *)v5))->CScreenMode::GetSoundList();
          (((PtrArray *)SoundList))->PtrArray::SetResolution(0, v187);
          (((PalScriptMgr *)this))->PalScriptMgr::ExecuteScriptByID();
          goto LABEL_99;
        }
      }
      return;
    case 1:
      if ( !v210 )
      {
        if ( *((_BYTE *)&this->m_nTodo_20 + 48) )
          goto LABEL_254;
        (((gbVisNode *)*((gbVisNode **)&this->m_nTodo_20 + 15)))->gbVisNode::SetTimeScale(1.0);
        (*(void (**)(_DWORD, _DWORD))(**(&this->m_nTodo_20 + 15) + 24))(
          *((_DWORD *)&this->m_nTodo_20 + 15),
          0);
        *((_BYTE *)&this->m_nTodo_20 + 48) = 4;
        goto LABEL_55;
      }
      return;
    case 2:
      if ( !v210 )
      {
        if ( *((_BYTE *)&this->m_nTodo_20 + 48) )
          goto LABEL_254;
        (((gbGeomNode *)*((gbGeomNode **)&this->m_nTodo_20 + 15)))->gbGeomNode::SetAnimLoop(1);
        (((gbVisNode *)*((gbVisNode **)&this->m_nTodo_20 + 15)))->gbVisNode::SetTimeScale(1.0);
        (*(void (**)(_DWORD, _DWORD))(**(&this->m_nTodo_20 + 15) + 24))(
          *((_DWORD *)&this->m_nTodo_20 + 15),
          0);
        goto LABEL_54;
      }
      return;
    case 3:
      if ( *((_BYTE *)&this->m_nTodo_20 + 48) )
        goto LABEL_254;
      __asm
      {
        fld     g_fEffectTimer
        fcomp   _flt_1_2
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0 )
      {
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
        *((_DWORD *)&this->m_nTodo_20 + 6) = *(&this->m_nTodo_0A8 + 11);
        *((_DWORD *)&this->m_nTodo_20 + 7) = *(&this->m_nTodo_0A8 + 12);
        *((_DWORD *)&this->m_nTodo_20 + 8) = this->m_nTodo_0DC;
        __asm
        {
          fld     dword ptr [esi+0x0E0]
          fmul    _flt_0_01745329f
        }
        *((_DWORD *)&this->m_nTodo_20 + 10) = 0;
        __asm
        {
          fst     [esp+0x108+nVal1]
          fsin
          fld     [esp+0x108+nVal1]
          fcos
          fstp    [esp+0x108+var_C4+8]
        }
        z = v196.z;
        // __asm { fstp    dword ptr [esi+0x44] }
        *((float *)&this->m_nTodo_20 + 9) = _ET1;
        *((float *)&this->m_nTodo_20 + 11) = z;
        __asm
        {
          fld     dword ptr [esi+0x44]
          fmul    _flt_280_0
          fstp    dword ptr [esi+0x44]
        }
        *((float *)&this->m_nTodo_20 + 9) = _ET1;
        __asm
        {
          fld     dword ptr [esi+0x48]
          fmul    _flt_280_0
          fstp    dword ptr [esi+0x48]
        }
        *((float *)&this->m_nTodo_20 + 10) = _ET1;
        __asm
        {
          fld     dword ptr [esi+0x4C]
          fmul    _flt_280_0
          fstp    dword ptr [esi+0x4C]
        }
        *((float *)&this->m_nTodo_20 + 11) = _ET1;
        *((_DWORD *)&this->m_nTodo_20 + 13) = 0;
        (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
        goto LABEL_55;
      }
      return;
    case 4:
      if ( *((_BYTE *)&this->m_nTodo_20 + 48) )
        goto LABEL_254;
      __asm
      {
        fld     g_fEffectTimer
        fcomp   _flt_1_2
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0 )
      {
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
        *((_DWORD *)&this->m_nTodo_20 + 6) = *(&this->m_nTodo_0A8 + 11);
        *((_DWORD *)&this->m_nTodo_20 + 7) = *(&this->m_nTodo_0A8 + 12);
        *((_DWORD *)&this->m_nTodo_20 + 8) = this->m_nTodo_0DC;
        RolePtr = (((RoleSystem *)this->m_pCmdList->m_rect.left))->RoleSystem::GetRolePtr(*(&this->m_nTodo_0F4 + 2));
        // __asm { fld     dword ptr [esi+0x38] }
        reg_EDI = (unsigned long)(_DWORD *)RolePtr;
        __asm
        {
          fsub    dword ptr [edi+0x80]
          fdiv    g_fScriptTileSize
        }
        LODWORD(v16) = _ftol();
        __asm
        {
          fld     dword ptr [esi+0x40]
          fsub    dword ptr [edi+0x88]
        }
        v17 = LODWORD(v16);
        nSceneIdx.x = v16;
        __asm { fdiv    g_fScriptTileSize }
        LODWORD(v18) = _ftol();
        __asm
        {
          fld     _flt_0_0
          fild    [esp+0x104+nSceneIdx]
        }
        nSceneIdx.y = v18;
        __asm
        {
          fadd    _flt_0_5
          fmul    g_fScriptTileSize
          fadd    dword ptr [edi+0x80]
          fstp    [esp+0x104+pParams]
          fild    [esp+0x104+var_D8]
          fadd    _flt_0_5
          fmul    g_fScriptTileSize
          fadd    dword ptr [edi+0x88]
          fstp    [esp+0x104+var_E0]
        }
        if ( v17 >= 0 )
        {
          v19 = reg_EDI[38];
          if ( v17 < v19 && v18 >= 0.0f && SLODWORD(v18) < reg_EDI[39] )
          {
            __asm { fstp    st }
            reg_EDX = reg_EDI[40];
            reg_ECX = v17 + LODWORD(v18) * v19;
            __asm { fld     dword ptr [edx+ecx*8] }
          }
        }
        x = pParams.x;
        v23 = pParams.z;
        // __asm { fstp    dword ptr [esi+0x3C] }
        *((float *)&this->m_nTodo_20 + 7) = _ET1;
        *((float *)&this->m_nTodo_20 + 6) = x;
        *((float *)&this->m_nTodo_20 + 8) = v23;
        __asm
        {
          fld     dword ptr [esi+0x3C]
          fsub    dword ptr [flt_56AA3C]
          fstp    dword ptr [esi+0x3C]
        }
        *((float *)&this->m_nTodo_20 + 7) = _ET1;
        *((_DWORD *)&this->m_nTodo_20 + 2) = *(&this->m_nTodo_0A8 + 11);
        *((_DWORD *)&this->m_nTodo_20 + 3) = *(&this->m_nTodo_0A8 + 12);
        *((_DWORD *)&this->m_nTodo_20 + 4) = this->m_nTodo_0DC;
        *((_DWORD *)&this->m_nTodo_20 + 9) = 0;
        *((_DWORD *)&this->m_nTodo_20 + 10) = 1133248512;
        *((_DWORD *)&this->m_nTodo_20 + 11) = 0;
        v26 = *((_DWORD *)&this->m_nTodo_20 + 14);
        *((_DWORD *)&this->m_nTodo_20 + 13) = 0;
        if ( v26 == 3 )
        {
          (((gbVisNode *)*((gbVisNode **)&this->m_nTodo_20 + 15)))->gbVisNode::SetTimeScale(0.0);
          (*(void (**)(_DWORD, _DWORD))(**(&this->m_nTodo_20 + 15) + 24))(
            *((_DWORD *)&this->m_nTodo_20 + 15),
            0);
        }
        (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
        goto LABEL_55;
      }
      return;
    case 5:
      if ( *((_DWORD *)&this->m_nTodo_0F4 + 1) == 1 )
      {
        if ( !v209 && this->ScriptVM::IsRunning() )
        {
          reg_EAX = g_pRoleSystem;
          reg_EDI = (unsigned long)(&this->m_nTodo_20 + 2);
          v29 = (gbVec3D *)(&this->m_nTodo_20 + 9);
          __asm
          {
            fld     dword ptr [edi]
            fsub    dword ptr [eax+0x0A0]
            fld     dword ptr [edi+4]
            fsub    dword ptr [eax+0x0A4]
            fstp    [esp+0x104+var_E4]
            fld     dword ptr [edi+8]
            fsub    dword ptr [eax+0x0A8]
          }
          *((_DWORD *)&this->m_nTodo_20 + 10) = LODWORD(pParams.y);
          // __asm { fstp    [esp+0x104+var_E0] }
          v30 = pParams.z;
          __asm { fstp    dword ptr [ecx] }
          v29->x = _ET1;
          *((float *)&this->m_nTodo_20 + 11) = v30;
          __asm
          {
            fld     dword ptr [esi+0x48]
            fcomp   _flt_40_0
            fnstsw  ax
          }
          if ( (BYTE1(reg_EAX) & 0x41) != 0 )
          {
            *((_DWORD *)&this->m_nTodo_20 + 10) = 0;
            (((gbVec3D *)v29))->gbVec3D::Normalize();
            (((ScriptVM *)this))->ScriptVM::GetRolePosition(1u);
            (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 0, 1);
            (((ScriptVM *)this))->ScriptVM::CallFunction(0xBu, 0);
            goto LABEL_247;
          }
          v29->x = 0.0f;
          *((_DWORD *)&this->m_nTodo_20 + 10) = 0;
          *((_DWORD *)&this->m_nTodo_20 + 11) = 0;
        }
      }
      else
      {
        if ( !*((_BYTE *)&this->m_nTodo_0A8 + 7) )
          goto LABEL_254;
        v32 = *((_BYTE *)&this->m_nTodo_20 + 48);
        if ( v32 )
        {
          if ( v32 != 3 )
            goto LABEL_254;
        }
        reg_EDI = g_pRoleSystem;
        reg_ECX = (unsigned long)(&this->m_nTodo_20 + 2);
        __asm
        {
          fld     dword ptr [ecx+4]
          fsub    dword ptr [edi+0x0A4]
          fcomp   _flt_40_0
          fnstsw  ax
        }
        if ( (_AX & 0x4100) != 0 )
        {
          if ( v32 )
          {
            v36 = *(&this->m_nPauseState + 134);
            *((_DWORD *)&this->m_pCmdList + 2) = 2;
            *((_DWORD *)&this->m_nTodo_20 + 6) = *(_DWORD *)(v36 + 3076);
          }
          else
          {
            *((_DWORD *)&this->m_pCmdList + 2) = 1;
            *((_DWORD *)&this->m_nTodo_20 + 6) = 0;
          }
          *((_DWORD *)&this->m_pCmdList + 7) = 1;
          *((_BYTE *)&this->m_nTodo_20 + 48) = 4;
          (((RoleSystem *)reg_EDI))->RoleSystem::SetMoveTarget((float *)&this->m_nTodo_20 + 2, 1);
          (((RoleSystem *)reg_EDI))->RoleSystem::GetMoveState(1);
          v38 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
          if ( v38 != -1 )
          {
            *((_BYTE *)&this->m_nTodo_0A8 + 6) = v38 - 1;
            v39 = (((CScreenMode *)v37))->CScreenMode::GetSoundList();
            (((PtrArray *)v39))->PtrArray::SetResolution((int)_ESI, 0);
            goto LABEL_254;
          }
          goto LABEL_248;
        }
      }
      return;
    case 6:
      if ( !*((_BYTE *)&this->m_nTodo_20 + 48) )
      {
        pfVal2.x = *((float *)&this->m_nTodo_20 + 2);
        // __asm { fld     [esp+0x104+pfVal2] }
        v40 = *((float *)&this->m_nTodo_20 + 4);
        pfVal2.y = *((float *)&this->m_nTodo_20 + 3);
        pfVal2.z = v40;
        reg_EAX = (unsigned long)v208;
        __asm
        {
          fsub    dword ptr [eax+4]
          fstp    [esp+0x104+pfVal2]
          fld     dword ptr [eax+8]
          fchs
          fstp    [esp+0x104+var_F0]
          fld     [esp+0x104+var_EC]
          fsub    dword ptr [eax+0x0C]
          fstp    [esp+0x104+var_EC]
        }
        (((gbVec3D *)&pfVal2))->gbVec3D::Length();
        __asm
        {
          fld     _flt_12_0
          fmul    _flt_4_0
          fcompp
          fnstsw  ax
        }
        if ( (_AX & 0x4100) == 0 )
        {
          v43 = g_pRoleSystem;
          v44 = g_pRoleSystem;
          g_pRoleSystem->m_nCoreState = 0;
          (((RoleSystem *)v44))->RoleSystem::UpdateTransform();
          *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
          *((_DWORD *)&this->m_nTodo_20 + 9) = 0;
          *((_DWORD *)&this->m_nTodo_20 + 10) = 0;
          *((_DWORD *)&this->m_nTodo_20 + 11) = 0;
          *((_DWORD *)&this->m_nTodo_20 + 6) = LODWORD(v43->m_fPosX);
          *((_DWORD *)&this->m_nTodo_20 + 7) = LODWORD(v43->m_fPosY);
          *((_DWORD *)&this->m_nTodo_20 + 8) = LODWORD(v43->m_fPosZ);
          (((gbVisNode *)*((gbVisNode **)&this->m_nTodo_20 + 15)))->gbVisNode::SetTimeScale(2.0);
          (*(void (**)(_DWORD, _DWORD))(**(&this->m_nTodo_20 + 15) + 24))(
            *((_DWORD *)&this->m_nTodo_20 + 15),
            0);
          v46 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
          if ( v46 != -1 )
            *((_BYTE *)&this->m_nTodo_0A8 + 6) = v46 - 1;
          v47 = (((CScreenMode *)v45))->CScreenMode::GetSoundList();
          (((PtrArray *)v47))->PtrArray::SetResolution((int)_ESI, 0);
          (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
        }
      }
      return;
    case 7:
    case 8:
      if ( v209 == 2 && !*((_BYTE *)&this->m_nTodo_20 + 48) )
      {
        __asm
        {
          fld     dword ptr [esi+0x0E0]
          fadd    _flt_90_0
        }
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
        // __asm { fstp    dword ptr [esi+0x38] }
        *((float *)&this->m_nTodo_20 + 6) = _ET1;
        v49 = g_pRoleSystem;
        g_pRoleSystem->m_nCoreState = 0;
        (((RoleSystem *)v49))->RoleSystem::UpdateTransform();
        (((RoleSystem *)this))->RoleSystem::ProcessAction();
        (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
        v50 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
        if ( v50 != -1 )
          *((_BYTE *)&this->m_nTodo_0A8 + 6) = v50 - 1;
        v51 = (CScreenMode *)g_pCameraCtrl;
        if ( !*((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
          goto LABEL_89;
        (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::InitParams(&this->m_nTodo_20 + 2);
        v53 = (((CScreenMode *)v52))->CScreenMode::GetSoundList();
        (((PtrArray *)v53))->PtrArray::SetResolution((int)_ESI, 0);
      }
      return;
    case 9:
      if ( *((_BYTE *)&this->m_nTodo_20 + 48) )
        goto LABEL_254;
      pfVal2.x = *((float *)&this->m_nTodo_20 + 2);
      // __asm { fld     [esp+0x104+pfVal2] }
      pfVal2.y = *((float *)&this->m_nTodo_20 + 3);
      reg_EAX = (unsigned long)v208;
      __asm { fsub    dword ptr [eax+4] }
      pfVal2.z = *((float *)&this->m_nTodo_20 + 4);
      __asm
      {
        fstp    [esp+0x104+pfVal2]
        fld     dword ptr [eax+8]
        fchs
        fstp    [esp+0x104+var_F0]
        fld     [esp+0x104+var_EC]
        fsub    dword ptr [eax+0x0C]
        fstp    [esp+0x104+var_EC]
      }
      (((gbVec3D *)&pfVal2))->gbVec3D::Length();
      __asm
      {
        fld     _flt_12_0
        fmul    _flt_0_5
        fcompp
        fnstsw  ax
      }
      if ( (_AX & 0x4100) == 0 )
      {
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteScriptByID();
LABEL_54:
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
LABEL_55:
        v2 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
        goto LABEL_56;
      }
      return;
    case 0xA:
      if ( !*((_BYTE *)&this->m_nTodo_20 + 48) )
      {
        __asm
        {
          fld     dword ptr [esi+0x140]
          fsub    dword ptr [esi+0x134]
          fld     dword ptr [esi+0x144]
          fsub    dword ptr [esi+0x138]
        }
        reg_EDI = (unsigned long)(float *)(&this->m_nTodo_20 + 9);
        __asm
        {
          fstp    [esp+0x104+var_E4]
          fld     dword ptr [esi+0x148]
          fsub    dword ptr [esi+0x13C]
        }
        *((_DWORD *)&this->m_nTodo_20 + 10) = LODWORD(pParams.y);
        // __asm { fstp    [esp+0x104+var_E0] }
        v57 = pParams.z;
        __asm { fstp    dword ptr [edi] }
        // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EDI = _ET1;` 已由上方 asm 存储覆盖

        *((float *)&this->m_nTodo_20 + 11) = v57;
        ((gbVec3D *)((gbVec3D *)&this->m_nTodo_20 + 3))->gbVec3D::Normalize();
        __asm
        {
          fld     dword ptr g_RoleSystemData+0x12C
          fld     st
          fmul    dword ptr [edi]
        }
        __asm { fstp    dword ptr [edi] }
        // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EDI = _ET1;` 已由上方 asm 存储覆盖

        __asm
        {
          fld     st
          fmul    dword ptr [edi+4]
          fstp    dword ptr [edi+4]
        }
        *((float *)&this->m_nTodo_20 + 10) = _ET1;
        __asm
        {
          fmul    dword ptr [edi+8]
          fstp    dword ptr [edi+8]
        }
        *((float *)&this->m_nTodo_20 + 11) = _ET1;
        v208->m_nCoreState = 0;
        (((RoleSystem *)v208))->RoleSystem::UpdateTransform();
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
        goto LABEL_99;
      }
      return;
    case 0xB:
      if ( v209 == 1 && !*((_BYTE *)&this->m_nTodo_20 + 48) )
      {
        v62 = (gbMatrix4 *)&v201;
        v63 = 4;
        do
        {
          v62 = (gbMatrix4 *)((char *)v62 + 12);
          --v63;
        }
        while ( v63 );
        p_xy = (float *)&v201.xy;
        v65 = 4;
        do
        {
          *(p_xy - 1) = *((float *)&this->m_nTodo_20 + 2);
          v66 = *((_DWORD *)&this->m_nTodo_20 + 4);
          *p_xy = 0.0;
          *((_DWORD *)p_xy + 1) = v66;
          p_xy += 3;
          --v65;
        }
        while ( v65 );
        (((Object3D *)this))->Object3D::SetTransform(&pMatrix);
        v196.x = -12.0f;
        // __asm { fld     [esp+0x104+var_C] }
        reg_EAX = (unsigned long)(char *)(&v196.x + (_DWORD)dword_C10CC8);
        v196.y = 4.0f;
        v196.z = 4.0f;
        v197 = 1091567616;
        v198 = 1094713344;
        __asm
        {
          fadd    dword ptr [eax]
          fld     dword ptr [esp+0x104+var_98]
        }
        nVal1.x = 100000.0f;
        v68 = 0;
        __asm { fsub    st, st(1) }
        reg_EBX = (unsigned long)(float *)&v208->m_fontcolor.Color;
        reg_EDI = (unsigned long)&v201.xz;
        __asm
        {
          fstp    dword ptr [esp+0x104+var_98]
          fadd    [esp+0x104+var_98.xw]
          fstp    [esp+0x104+var_98.xw]
          fld     [esp+0x104+var_4]
          fadd    dword ptr [eax]
          fld     [esp+0x104+var_98.zx]
          fsub    st, st(1)
          fstp    [esp+0x104+var_98.zx]
          fadd    [esp+0x104+var_98.zw]
          fstp    [esp+0x104+var_98.zw]
        }
        do
        {
          __asm
          {
            fld     dword ptr [ebx]
            fsub    dword ptr [edi-8]
            fstp    [esp+0x104+pParams]
            fld     dword ptr [ebx+4]
            fsub    dword ptr [edi-4]
          }
          pfVal2.x = pParams.x;
          __asm
          {
            fstp    [esp+0x104+var_E4]
            fld     dword ptr [ebx+8]
            fsub    dword ptr [edi]
          }
          pfVal2.y = pParams.y;
          // __asm { fstp    [esp+0x104+var_E0] }
          pfVal2.z = pParams.z;
          (((gbVec3D *)&pfVal2))->gbVec3D::Length();
          __asm
          {
            fcom    [esp+0x104+nVal1]
            fnstsw  ax
          }
          if ( (_AX & 0x100) != 0 )
          {
            v72 = *((_DWORD *)reg_EDI - 1);
            v73 = *(_DWORD *)reg_EDI;
            *((float *)&this->m_nTodo_20 + 6) = *(reg_EDI - 2);
            // __asm { fstp    [esp+0x104+nVal1] }
            *((_DWORD *)&this->m_nTodo_20 + 7) = v72;
            *((_DWORD *)&this->m_nTodo_20 + 8) = v73;
            *((_DWORD *)&this->m_pCmdList + 2) = v68;
          }
          else
          {
            __asm { fstp    st }
          }
          ++v68;
          reg_EDI += 3;
        }
        while ( v68 < 4 );
        __asm
        {
          fld     [esp+0x104+nVal1]
          fcomp   dword ptr [flt_56AB24]
          fnstsw  ax
        }
        if ( (_AX & 0x100) == 0 )
          goto LABEL_103;
        reg_EBP = (unsigned long)(&this->m_nTodo_20 + 6);
        if ( !(((PalScriptMgr *)this))->PalScriptMgr::CmdUpdateRolePath(reg_EBX, (float *)&this->m_nTodo_20 + 6) )
          goto LABEL_103;
        reg_EDI = (unsigned long)(float *)(&this->m_nTodo_20 + 9);
        *((_DWORD *)&this->m_nTodo_20 + 9) = *((_DWORD *)&this->m_nTodo_20 + 2);
        *((_DWORD *)&this->m_nTodo_20 + 10) = *((_DWORD *)&this->m_nTodo_20 + 3);
        *((_DWORD *)&this->m_nTodo_20 + 11) = *((_DWORD *)&this->m_nTodo_20 + 4);
        __asm
        {
          fld     dword ptr [edi]
          fsub    dword ptr [ebp+0]
          fstp    dword ptr [edi]
        }
        // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EDI = _ET1;` 已由上方 asm 存储覆盖

        __asm
        {
          fld     dword ptr [edi+4]
          fsub    dword ptr [ebp+4]
          fstp    dword ptr [edi+4]
        }
        reg_EDI[1] = _ET1;
        __asm
        {
          fld     dword ptr [edi+8]
          fsub    dword ptr [ebp+8]
          fstp    dword ptr [edi+8]
        }
        reg_EDI[2] = _ET1;
        *((_DWORD *)&this->m_nTodo_20 + 10) = 0;
        ((gbVec3D *)((gbVec3D *)&this->m_nTodo_20 + 3))->gbVec3D::Normalize();
        __asm
        {
          fld     dword ptr g_RoleSystemData+0x12C
          fld     st
          fmul    dword ptr [edi]
        }
        __asm { fstp    dword ptr [edi] }
        // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EDI = _ET1;` 已由上方 asm 存储覆盖

        __asm
        {
          fld     st
          fmul    dword ptr [edi+4]
          fstp    dword ptr [edi+4]
        }
        *((float *)&this->m_nTodo_20 + 10) = _ET1;
        __asm
        {
          fmul    dword ptr [edi+8]
          fstp    dword ptr [edi+8]
        }
        *((float *)&this->m_nTodo_20 + 11) = _ET1;
        (((RoleSystem *)v208))->RoleSystem::SetMoveTarget((float *)&this->m_nTodo_20 + 6, 1);
        (((RoleSystem *)v208))->RoleSystem::GetMoveState(1);
        (((RoleSystem *)this))->RoleSystem::ProcessAction();
        v83 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
        if ( v83 == -1 )
          goto LABEL_89;
        goto LABEL_88;
      }
      return;
    case 0xC:
      if ( v209 == 1 )
      {
        if ( dword_C10CC8 != *((scAsmDecoder **)&this->m_nTodo_0F4 + 1) )
        {
          v84 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("cantopen");
          goto LABEL_179;
        }
        if ( !*((_BYTE *)&this->m_nTodo_20 + 48) )
        {
          reg_EBP = (unsigned long)v208;
          *((_DWORD *)&this->m_nTodo_20 + 6) = *((_DWORD *)&this->m_nTodo_20 + 2);
          *((_DWORD *)&this->m_nTodo_20 + 7) = *((_DWORD *)&this->m_nTodo_20 + 3);
          *((_DWORD *)&this->m_nTodo_20 + 8) = *((_DWORD *)&this->m_nTodo_20 + 4);
          __asm
          {
            fld     dword ptr [esi+0x28]
            fsub    dword ptr [ebp+0x0A0]
            fstp    [esp+0x104+pParams]
            fld     dword ptr [esi+0x2C]
            fsub    dword ptr [ebp+0x0A4]
          }
          pfVal2.x = pParams.x;
          __asm
          {
            fstp    [esp+0x104+var_E4]
            fld     dword ptr [esi+0x30]
            fsub    dword ptr [ebp+0x0A8]
          }
          pfVal2.y = pParams.y;
          // __asm { fstp    [esp+0x104+var_E0] }
          pfVal2.z = pParams.z;
          (((gbVec3D *)&pfVal2))->gbVec3D::Length();
          __asm
          {
            fcomp   _flt_600_0
            fnstsw  ax
          }
          if ( (_AX & 0x100) == 0 )
            goto LABEL_103;
          reg_EBX = (unsigned long)&v208->m_fontcolor;
          if ( !(((PalScriptMgr *)this))->PalScriptMgr::CmdUpdateRolePath((float *)&v208->m_fontcolor.Color, (float *)&this->m_nTodo_20 + 6) )
            goto LABEL_103;
          *((_DWORD *)&this->m_nTodo_20 + 13) = 0;
          __asm
          {
            fld     dword ptr [ebx]
            fsub    dword ptr [esi+0x28]
            fstp    [esp+0x104+pParams]
            fld     dword ptr [ebx+4]
            fsub    dword ptr [esi+0x2C]
          }
          pfVal2.x = pParams.x;
          __asm
          {
            fstp    [esp+0x104+var_E4]
            fld     dword ptr [ebx+8]
            fsub    dword ptr [esi+0x30]
          }
          // __asm { fstp    [esp+0x104+var_E0] }
          pfVal2.y = 0.0f;
          pfVal2.z = pParams.z;
          (((gbVec3D *)&pfVal2))->gbVec3D::Length();
          __asm
          {
            fld     _flt_12_0
            fmul    _flt_3_0
            fsubp   st(1), st
            fcomp   _flt_1_0
            fnstsw  ax
          }
          if ( (_AX & 0x100) != 0 )
          {
            *((_BYTE *)&this->m_nTodo_20 + 48) = 2;
            (((RoleSystem *)v208))->RoleSystem::GetMoveState(0);
            (((RoleSystem *)v208))->RoleSystem::GetActionByIndex(8);
          }
          else
          {
            (((gbVec3D *)&pfVal2))->gbVec3D::Normalize();
            if ( *((_DWORD *)&this->m_nTodo_0F4 + 1) == 2 )
            {
              __asm
              {
                fld     dword ptr [esi+0x370]
                fchs
                fld     [esp+0x104+pfVal2]
                fmul    st, st(1)
              }
            }
            else
            {
              __asm
              {
                fld     _flt_12_0
                fchs
                fld     st
                fmul    [esp+0x104+pfVal2]
              }
            }
            __asm
            {
              fstp    [esp+0x104+pfVal2]
              fld     [esp+0x104+var_F0]
              fmul    st, st(1)
            }
            __asm
            {
              fstp    [esp+0x110+var_F0]
              fld     [esp+0x110+var_EC]
              fmul    st, st(1)
              fstp    [esp+0x110+var_EC]
              fstp    st
              fld     [esp+0x110+pfVal2]
              fadd    dword ptr [esi+0x28]
              fld     [esp+0x110+var_F0]
              fadd    dword ptr [esi+0x2C]
              fstp    [esp+0x110+var_E4]
              fld     [esp+0x110+var_EC]
              fadd    dword ptr [esi+0x30]
            }
            *((_DWORD *)&this->m_nTodo_20 + 7) = LODWORD(pParams.y);
            // __asm { fstp    [esp+0x110+var_E0] }
            v90 = pParams.z;
            __asm { fstp    dword ptr [edi] }
            v85 = (float *)(&this->m_nTodo_20 + 6);
            *v85 = _ET1;
            *((float *)&this->m_nTodo_20 + 8) = v90;
            (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 6), 1, 1);
            (((ScriptVM *)this))->ScriptVM::CallFunction(1u, 0);
            (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
          }
          v83 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
          if ( v83 != -1 )
LABEL_88:
            *((_BYTE *)&this->m_nTodo_0A8 + 6) = v83 - 1;
          goto LABEL_89;
        }
      }
      return;
    case 0xE:
      if ( !v210 && !*((_BYTE *)&this->m_nTodo_20 + 48) )
      {
        if ( *((_DWORD *)&this->m_nTodo_0F4 + 1) )
        {
          PalScriptMgr::ClearAllScript();
          if ( !v93 )
          {
            (((RoleSystem *)v208))->RoleSystem::Notify();
            goto LABEL_96;
          }
        }
        else
        {
          *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
          (((RoleSystem *)v208))->RoleSystem::Notify();
          v97 = (((CScreenMode *)v96))->CScreenMode::GetSoundList();
          (((PtrArray *)v97))->PtrArray::SetResolution((int)_ESI, 0);
          if ( *((_DWORD *)&this->m_nTodo_20 + 14) == 3 )
          {
            (((gbVisNode *)*((gbVisNode **)&this->m_nTodo_20 + 15)))->gbVisNode::SetTimeScale(2.0);
            (*(void (**)(_DWORD, _DWORD))(**(&this->m_nTodo_20 + 15) + 24))(
              *((_DWORD *)&this->m_nTodo_20 + 15),
              0);
          }
LABEL_99:
          v98 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
          if ( v98 != -1 )
            *((_BYTE *)&this->m_nTodo_0A8 + 6) = v98 - 1;
        }
      }
      return;
    case 0xF:
      if ( v209 == 1 )
      {
        reg_EDI = (unsigned long)v208;
        pfVal2.x = *((float *)&this->m_nTodo_20 + 2);
        __asm
        {
          fld     [esp+0x104+pfVal2]
          fsub    dword ptr [edi+4]
        }
        pfVal2.y = *((float *)&this->m_nTodo_20 + 3);
        v100 = *((float *)&this->m_nTodo_20 + 4);
        __asm
        {
          fstp    [esp+0x104+pParams]
          fld     dword ptr [edi+8]
          fchs
          fstp    [esp+0x104+var_E4]
        }
        pfVal2.z = v100;
        __asm
        {
          fld     [esp+0x104+var_EC]
          fsub    dword ptr [edi+0x0C]
        }
        // __asm { fstp    [esp+0x104+var_E0] }
        pfVal2 = pParams;
        (((gbVec3D *)&pfVal2))->gbVec3D::Length();
        __asm
        {
          fcomp   _flt_600_0
          fnstsw  ax
        }
        if ( (_AX & 0x4100) == 0 )
          goto LABEL_103;
        if ( *(&this->m_nPauseState + 11) )
          goto LABEL_254;
        __asm
        {
          fld     dword ptr [esi+0x0E0]
          fadd    dword ptr [flt_56AA54]
        }
        // __asm { fstp    [esp+0x10C+fVal]; fVal }
        RoleSystem::StartPathMove(
          v208,
          *((char **)&this->m_nTodo_0F4 + 1),
          *((_DWORD *)&this->m_nTodo_0F4 + 2),
          (char *)this->m_nPauseState,
          *(&this->m_nPauseState + 1),
          fVala,
          (int)_ESI);
      }
      return;
    case 0x10:
      if ( v209 == 1 )
      {
        PalScriptMgr::ClearAllScript();
        if ( !v102 )
        {
LABEL_96:
          (((PalScriptMgr *)v94))->PalScriptMgr::Destroy();
          *(&this->m_nPathStep + 3) = v95;
          v188 = v95;
          fVal = 0;
          goto LABEL_90;
        }
        goto LABEL_254;
      }
      return;
    case 0x11:
      if ( v209 == 2 && this->ScriptVM::IsRunning() )
      {
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd07(1u);
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
        goto LABEL_253;
      }
      return;
    case 0x13:
      if ( v209 == 2 && this->ScriptVM::IsRunning() )
      {
        (((ScriptVM *)this))->ScriptVM::SetRolePosition(0);
        (((RoleSystem *)this))->RoleSystem::ExecScriptDataCmd((int *)&this->m_nTodo_20 + 2);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdRoleMoveSmooth(0, v189);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd07(1u);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd10(1u);
        (((ScriptVM *)this))->ScriptVM::SetRolePosition(1u);
        (((ScriptVM *)this))->ScriptVM::CallFunction(1u, 0);
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
      }
      return;
    case 0x14:
      if ( v209 == 1 )
      {
LABEL_56:
        if ( v2 != -1 )
          *((_BYTE *)&this->m_nTodo_0A8 + 6) = v2 - 1;
        goto LABEL_254;
      }
      return;
    case 0x15:
    case 0x1E:
    case 0x25:
      return;
    case 0x16:
      if ( v209 != 2 )
        return;
      pParams.x = *((float *)&this->m_nTodo_20 + 2);
      v103 = *((unsigned __int8 *)&this->m_nTodo_20 + 48);
      pParams.y = *((float *)&this->m_nTodo_20 + 3);
      pParams.z = *((float *)&this->m_nTodo_20 + 4);
      if ( !v103 )
      {
        // __asm { fild    dword ptr [esi+0x0F8] }
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
        // __asm { fstp    [esp+0x104+var_E4] }
        goto LABEL_119;
      }
      if ( v103 == 2 )
      {
        *((_BYTE *)&this->m_nTodo_20 + 48) = 3;
LABEL_119:
        (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
        *((_DWORD *)&this->m_pCmdList + 7) = (((PalScriptMgr *)this))->PalScriptMgr::IsPosInBounds((float *)v208);
        v104 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
        if ( v104 != -1 )
          *((_BYTE *)&this->m_nTodo_0A8 + 6) = v104 - 1;
        v51 = (CScreenMode *)g_pCameraCtrl;
        if ( *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
          (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::InitParams(&pParams);
        goto LABEL_89;
      }
      return;
    case 0x17:
      (((Object3D *)this))->Object3D::SetTransform(&v201);
      __asm
      {
        fld     [esp+0x104+var_50]
        fcomp   [esp+0x104+var_58]
        fnstsw  ax
      }
      if ( (_AX & 0x4100) != 0 )
      {
        // __asm { fld     [esp+0x104+var_58] }
      }
      else
        // __asm { fld     [esp+0x104+var_50] }
      __asm { fmul    _flt_0_5 }
      reg_EDI = (unsigned long)v208;
      reg_EBP = (unsigned long)(float *)(&this->m_nTodo_20 + 2);
      __asm
      {
        fstp    [esp+0x104+nSceneIdx]
        fld     dword ptr [ebp+0]
        fsub    dword ptr [edi+0x0A0]
        fstp    [esp+0x104+pParams]
        fld     dword ptr [ebp+4]
        fsub    dword ptr [edi+0x0A4]
      }
      pfVal2.x = pParams.x;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     dword ptr [ebp+8]
        fsub    dword ptr [edi+0x0A8]
      }
      pfVal2.y = pParams.y;
      // __asm { fstp    [esp+0x104+var_E0] }
      pfVal2.z = pParams.z;
      (((gbVec3D *)&pfVal2))->gbVec3D::Length();
      v109 = *((_DWORD *)&this->m_nTodo_0F4 + 2);
      // __asm { fstp    [esp+0x104+nVal1] }
      if ( !v109 )
      {
        if ( v209 != 1 )
          return;
        goto LABEL_143;
      }
      v110 = v109 - 1;
      if ( !v110 )
      {
        if ( v209 != 2 )
          return;
        goto LABEL_143;
      }
      if ( v110 != 1 )
        goto LABEL_143;
      if ( v209 != 1 )
      {
        if ( v209 != 2 )
          return;
LABEL_143:
        if ( !*((_BYTE *)&this->m_nTodo_20 + 48) )
        {
          v115 = (((CScreenMode *)v108))->CScreenMode::GetSoundList();
          (((PtrArray *)v115))->PtrArray::SetResolution((int)_ESI, 0);
          if ( v209 == 2 )
          {
            *((_BYTE *)&this->m_nTodo_0A8 + 7) = *((_BYTE *)&this->m_nTodo_0A8 + 7) == 0;
            v116 = *((_DWORD *)&this->m_nTodo_20 + 14);
            *((_BYTE *)&this->m_nTodo_20 + 48) = 3;
            if ( v116 == 3 )
            {
              (*(void (**)(_DWORD, _DWORD))(**(&this->m_nTodo_20 + 15) + 24))(
                *((_DWORD *)&this->m_nTodo_20 + 15),
                0);
              (((gbVisNode *)*((gbVisNode **)&this->m_nTodo_20 + 15)))->gbVisNode::SetTimeScale(2.0);
              (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
            }
            v117 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
            if ( v117 != -1 )
              *((_BYTE *)&this->m_nTodo_0A8 + 6) = v117 - 1;
            if ( *((_DWORD *)&this->m_nTodo_0F4 + 1) == 1 )
              *((_BYTE *)&this->m_nTodo_0A8 + 41) = *((_BYTE *)&this->m_nTodo_0A8 + 7);
          }
          else
          {
            pfVal2.x = *(float *)reg_EBP;
            // __asm { fld     [esp+0x104+pfVal2] }
            // __asm { fsub    dword ptr [edi+0x0A0] }
            v118 = *((float *)&this->m_nTodo_20 + 4);
            pfVal2.y = *((float *)&this->m_nTodo_20 + 3);
            __asm
            {
              fld     [esp+0x104+var_F0]
              fsub    dword ptr [edi+0x0A4]
            }
            pfVal2.z = v118;
            __asm
            {
              fstp    [esp+0x104+var_F0]
              fld     [esp+0x104+var_EC]
              fsub    dword ptr [edi+0x0A8]
              fstp    [esp+0x104+var_EC]
              fdiv    [esp+0x104+nVal1]
              fstp    [esp+0x104+pfVal2]
              fld     [esp+0x104+var_F0]
              fdiv    [esp+0x104+nVal1]
              fstp    [esp+0x104+var_F0]
              fld     [esp+0x104+var_EC]
              fdiv    [esp+0x104+nVal1]
              fstp    [esp+0x104+var_EC]
              fld     [esp+0x104+nVal1]
              fsub    [esp+0x104+nSceneIdx]
              fld     st
              fmul    [esp+0x104+pfVal2]
              fld     [esp+0x104+var_F0]
              fmul    st, st(2)
              fstp    [esp+0x104+var_F0]
              fld     [esp+0x104+var_EC]
              fmul    st, st(2)
              fstp    [esp+0x104+var_EC]
              fadd    dword ptr [edi+0x0A0]
              fstp    [esp+0x104+pfVal2]
              fld     [esp+0x104+var_F0]
              fadd    dword ptr [edi+0x0A4]
              fstp    [esp+0x104+var_F0]
              fld     [esp+0x104+var_EC]
              fadd    dword ptr [edi+0x0A8]
              fstp    [esp+0x104+var_EC]
              fcomp   _flt_600_0
              fnstsw  ax
            }
            if ( (_AX & 0x100) != 0 )
            {
              v120 = pfVal2.x;
              y = pfVal2.y;
              v122 = pfVal2.z;
              *((_DWORD *)&this->m_nTodo_20 + 13) = 0;
              *((float *)&this->m_nTodo_20 + 6) = v120;
              *((float *)&this->m_nTodo_20 + 7) = y;
              *((float *)&this->m_nTodo_20 + 8) = v122;
              v123 = (((CScreenMode *)LODWORD(y)))->CScreenMode::GetSoundList();
              (((PtrArray *)v123))->PtrArray::SetResolution((int)_ESI, 0);
              __asm
              {
                fld     dword ptr [edi+4]
                fsub    dword ptr [ebp+0]
                fstp    [esp+0x104+pParams]
                fld     dword ptr [edi+8]
                fsub    dword ptr [ebp+4]
              }
              pfVal2.x = pParams.x;
              __asm
              {
                fstp    [esp+0x104+var_E4]
                fld     dword ptr [edi+0x0C]
                fsub    dword ptr [ebp+8]
              }
              // __asm { fstp    [esp+0x104+var_E0] }
              pfVal2.y = 0.0f;
              pfVal2.z = pParams.z;
              (((gbVec3D *)&pfVal2))->gbVec3D::Length();
              __asm
              {
                fsub    [esp+0x104+nSceneIdx]
                fld     dword ptr [flt_56AB10]
                fadd    st, st
                fsubp   st(1), st
                fcomp   _flt_0_0
                fnstsw  ax
              }
              if ( (_AX & 0x100) != 0 )
              {
                *((_BYTE *)&this->m_nTodo_20 + 48) = 2;
                (((RoleSystem *)v208))->RoleSystem::IsPathComplete((float *)&this->m_nTodo_20 + 2, 1);
                (((RoleSystem *)v208))->RoleSystem::GetMoveState(0);
                (((RoleSystem *)v208))->RoleSystem::GetActionByIndex(11);
                (((ScriptVM *)this))->ScriptVM::UpdatePauseState();
              }
              else
              {
                (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 6), 1, 1);
                (((PalScriptMgr *)this))->PalScriptMgr::CmdRoleMoveDirect(v189);
                (((ScriptVM *)this))->ScriptVM::CallFunction(0x4Du, 0);
                (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
              }
            }
          }
        }
        return;
      }
      if ( v208->m_partyActor.m_nState != *(&this->m_nTodo_0F4 + 2) )
        goto LABEL_103;
      __asm
      {
        fld     [esp+0x104+nVal1]
        fcomp   dword ptr [flt_56AB40]
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0
        || !(((PalScriptMgr *)this))->PalScriptMgr::CmdUpdateRolePath((float *)&v208->m_fontcolor.Color, (float *)&this->m_nTodo_20 + 2) )
      {
LABEL_103:
        v84 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("outdist");
        goto LABEL_179;
      }
      PalScriptMgr::ClearAllScript();
      if ( !v113 )
      {
        (((PalScriptMgr *)v112))->PalScriptMgr::Destroy();
        *(&this->m_nPathStep + 3) = v114;
      }
      return;
    case 0x18:
      if ( v209 == 11 )
      {
        g_RoleSystemExtra1.m_partyActor.m_pRoleObj = 1;
        (((RoleSystem *)&g_RoleSystemExtra1))->RoleSystem::GetActionByIndex(51);
        (((RoleSystem *)&g_RoleSystemExtra1))->RoleSystem::NotifySceneChange(*(&this->m_nTodo_0F4 + 2));
        (((RoleSystem *)&g_RoleSystemExtra1))->RoleSystem::SetTargetRotation((gbVec3D *)(&this->m_nTodo_20 + 2));
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd15(0);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdCameraOrbitPos(*((_DWORD *)&this->m_nTodo_20 + 2), *((float *)&this->m_nTodo_20 + 3), *((float *)&this->m_nTodo_20 + 4), 1u);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdCameraOrbitPos(LODWORD(g_pRoleSystem->m_fPosX), g_pRoleSystem->m_fPosY, g_pRoleSystem->m_fPosZ, 0);
        (((RoleSystem *)this))->RoleSystem::ExecScriptDataIdx(1065353216);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd15(1u);
        (((ScriptVM *)this))->ScriptVM::CallFunction(0xBu, 0);
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
        return;
      }
      if ( v209 != 1 || *((_BYTE *)&this->m_nTodo_20 + 48) )
        return;
      (((PalScriptMgr *)*((PalScriptMgr **)&this->m_nPauseState + 11)))->PalScriptMgr::Destroy();
      *(&this->m_nPathStep + 3) = v125;
      if ( !v125 )
      {
        (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 1, 1);
        goto LABEL_245;
      }
LABEL_238:
      *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
      goto LABEL_254;
    case 0x1A:
      if ( v209 != 1 || *((_BYTE *)&this->m_nTodo_20 + 48) )
        return;
      (((PalScriptMgr *)this))->PalScriptMgr::BuildCmdTransform(&pMatrix);
      __asm
      {
        fld     [esp+0x104+var_C]
        fmul    _flt_0_5
      }
      reg_EDI = (unsigned long)(&this->m_nTodo_20 + 2);
      pParams.y = 0.0f;
      reg_EBP = (unsigned long)v208;
      __asm
      {
        fstp    [esp+0x104+nSceneIdx]
        fld     dword ptr [esi+0x0E0]
        fmul    _flt_0_01745329f
      }
      pfVal2 = *(gbVec3D *)(&this->m_nTodo_20 + 2);
      __asm
      {
        fld     st
        fcos
      }
      __asm
      {
        fchs
        fstp    [esp+0x104+var_C4]
        fsin
        fld     _flt_12_0
        fadd    st, st
        fadd    [esp+0x104+nSceneIdx]
        fld     [esp+0x104+var_C4]
        fmul    st, st(1)
        fstp    [esp+0x104+pParams]
        fxch    st(1)
        fmul    st, st(1)
        fxch    st(1)
        fstp    st
        fld     [esp+0x104+pParams]
        fadd    [esp+0x104+pfVal2]
        fstp    [esp+0x104+pfVal2]
        fld     [esp+0x104+var_F0]
        fadd    [esp+0x104+var_E4]
        fstp    [esp+0x104+var_F0]
        fld     [esp+0x104+var_EC]
        fadd    st, st(1)
        fstp    [esp+0x104+var_EC]
        fstp    st
        fld     dword ptr [edi]
        fsub    dword ptr [ebp+0x0A0]
        fstp    [esp+0x104+pParams]
        fld     dword ptr [edi+4]
        fsub    dword ptr [ebp+0x0A4]
      }
      nVal1.x = pParams.x;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     dword ptr [edi+8]
        fsub    dword ptr [ebp+0x0A8]
      }
      nVal1.y = pParams.y;
      // __asm { fstp    [esp+0x104+var_E0] }
      nVal1.z = pParams.z;
      (((gbVec3D *)&nVal1))->gbVec3D::Length();
      __asm
      {
        fcomp   _flt_600_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0
        || !(((PalScriptMgr *)this))->PalScriptMgr::CmdUpdateRolePath((float *)&v208->m_fontcolor.Color, &pfVal2.x) )
      {
        goto LABEL_249;
      }
      v129 = pfVal2.x;
      v130 = pfVal2.y;
      v131 = pfVal2.z;
      *((_DWORD *)&this->m_nTodo_20 + 13) = 0;
      *((float *)&this->m_nTodo_20 + 6) = v129;
      *((float *)&this->m_nTodo_20 + 7) = v130;
      *((float *)&this->m_nTodo_20 + 8) = v131;
      __asm
      {
        fld     dword ptr [ebp+4]
        fsub    dword ptr [edi]
        fstp    [esp+0x104+pParams]
        fld     dword ptr [ebp+8]
        fsub    dword ptr [edi+4]
      }
      nVal1.x = pParams.x;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     dword ptr [ebp+0x0C]
        fsub    dword ptr [edi+8]
      }
      // __asm { fstp    [esp+0x104+var_E0] }
      nVal1.y = 0.0f;
      nVal1.z = pParams.z;
      (((gbVec3D *)&nVal1))->gbVec3D::Length();
      __asm
      {
        fsub    [esp+0x104+nSceneIdx]
        fld     dword ptr [flt_56AB10]
        fadd    st, st
        fsubp   st(1), st
        fcomp   _flt_0_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
      {
        *((_BYTE *)&this->m_nTodo_20 + 48) = 2;
        (((RoleSystem *)v208))->RoleSystem::IsPathComplete((float *)&this->m_nTodo_20 + 2, 1);
        (((RoleSystem *)v208))->RoleSystem::GetMoveState(0);
        (((RoleSystem *)v208))->RoleSystem::GetActionByIndex(11);
        goto LABEL_254;
      }
      (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 6), 1, 1);
      (((ScriptVM *)this))->ScriptVM::CallFunction(2u, 0);
      goto LABEL_247;
    case 0x1B:
      if ( v209 != 1 || *((_BYTE *)&this->m_nTodo_20 + 48) )
        return;
      __asm
      {
        fld     dword ptr [esi+0x218]
        fadd    dword ptr [esi+0x224]
        fld     dword ptr [esi+0x228]
        fadd    dword ptr [esi+0x21C]
      }
      reg_EDI = (unsigned long)v208;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     dword ptr [esi+0x22C]
        fadd    dword ptr [esi+0x220]
        fstp    [esp+0x104+var_E0]
        fmul    _flt_0_5
        fstp    [esp+0x104+pfVal2]
        fld     [esp+0x104+var_E4]
        fmul    _flt_0_5
        fstp    [esp+0x104+var_F0]
        fld     [esp+0x104+var_E0]
        fmul    _flt_0_5
        fstp    [esp+0x104+var_EC]
        fld     [esp+0x104+pfVal2]
        fsub    dword ptr [edi+0x0A0]
        fstp    [esp+0x104+pParams]
        fld     [esp+0x104+var_F0]
        fsub    dword ptr [edi+0x0A4]
      }
      nSceneIdx.x = pParams.x;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     [esp+0x104+var_EC]
        fsub    dword ptr [edi+0x0A8]
      }
      nSceneIdx.y = pParams.y;
      // __asm { fstp    [esp+0x104+var_E0] }
      nSceneIdx.z = pParams.z;
      (((gbVec3D *)&nSceneIdx))->gbVec3D::Length();
      __asm
      {
        fcomp   _flt_100_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
      {
        *((_DWORD *)&this->m_nTodo_20 + 13) = 0;
        *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
        v136 = (((CScreenMode *)v134))->CScreenMode::GetSoundList();
        (((PtrArray *)v136))->PtrArray::SetResolution((int)_ESI, 0);
        (((RoleSystem *)v208))->RoleSystem::IsPathComplete(&pfVal2.x, 1);
        (((RoleSystem *)v208))->RoleSystem::GetActionByIndex(11);
      }
      goto LABEL_254;
    case 0x1C:
      if ( v209 != 2 )
        return;
      if ( *((_DWORD *)&this->m_nTodo_0F4 + 1) == 1 )
      {
        v137 = *((_BYTE *)&this->m_nTodo_0A8 + 7) == 0;
        *((_BYTE *)&this->m_nTodo_0A8 + 7) = v137;
        *((_BYTE *)&this->m_nTodo_0A8 + 41) = v137;
      }
      goto LABEL_254;
    case 0x1D:
      if ( v209 || !this->ScriptVM::IsRunning() )
        return;
      if ( SceneMgr::GetValidPartyCount() >= *((_DWORD *)&this->m_nTodo_0F4 + 1) )
      {
        reg_EDI = (unsigned long)(float *)(&this->m_nTodo_20 + 2);
        pfVal2.x = *((float *)&this->m_nTodo_20 + 2);
        pfVal2.y = *((float *)&this->m_nTodo_20 + 3);
        reg_EAX = (unsigned long)v208;
        v140 = *((float *)&this->m_nTodo_20 + 4);
        pfVal2.y = 0.0f;
        __asm
        {
          fld     dword ptr [eax+4]
          fsub    [esp+0x104+pfVal2]
        }
        pfVal2.z = v140;
        __asm
        {
          fstp    [esp+0x104+pParams]
          fld     dword ptr [eax+8]
          fstp    [esp+0x104+var_E4]
          fld     dword ptr [eax+0x0C]
          fsub    [esp+0x104+var_EC]
        }
        // __asm { fstp    [esp+0x104+var_E0] }
        nSceneIdx = pParams;
        (((gbVec3D *)&nSceneIdx))->gbVec3D::Length();
        __asm
        {
          fld     _flt_12_0
          fmul    _flt_3_0
          fcompp
          fnstsw  ax
        }
        if ( (_AX & 0x100) == 0 )
        {
          (((ScriptVM *)this))->ScriptVM::SetRolePosition(0);
          (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 1, 1);
          (((PalScriptMgr *)this))->PalScriptMgr::CmdRoleMoveSmooth(1, v189);
          (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd07(1u);
          (((ScriptVM *)this))->ScriptVM::CallFunction(1u, 0);
          __asm
          {
            fld     dword ptr [edi+4]
            fsub    _flt_7_0
          }
          v142 = *((float *)&this->m_nTodo_20 + 4);
          pfVal2.x = *(float *)reg_EDI;
          pfVal2.z = v142;
          // __asm { fstp    [esp+0x108+var_F0] }
          (((PalScriptMgr *)this))->PalScriptMgr::CmdRoleMoveSmooth(0, v190);
          (((ScriptVM *)this))->ScriptVM::ExecuteOpcode(&pfVal2, 0, 0, 1);
          (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd05(0);
          (((ScriptVM *)this))->ScriptVM::SetRolePosition(1u);
LABEL_253:
          (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
LABEL_254:
          (((PalScriptMgr *)*((PalScriptMgr **)&this->m_nPauseState + 11)))->PalScriptMgr::Destroy();
        }
      }
      else
      {
        v84 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("lessweight");
LABEL_179:
        (((PalScriptMgr *)&stru_DBA134))->PalScriptMgr::ShowTextBox(v84);
      }
      return;
    case 0x1F:
      if ( v209 != 2 || *((_BYTE *)&this->m_nTodo_20 + 48) )
        return;
      __asm
      {
        fild    dword ptr [esi+0x0F8]
        fld     dword ptr [esi+0x28]
        fstp    [esp+0x104+pData]
      }
      __asm
      {
        fst     [esp+0x10C+var_AC]
        fld     dword ptr [esi+0x30]
        fstp    [esp+0x10C+var_A8]
      }
      // __asm { fsub    dword ptr [esi+0x2C] }
      __asm
      {
        fabs
        fmul    _flt_0_25
        fstp    dword ptr [esp+0x110+nType]; nType
      }
      ScriptVM::ExecuteOpcode(this, pData, LOBYTE(nType), 0, 0);
      (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd05(0);
      (((ScriptVM *)this))->ScriptVM::CallFunction(1u, 0);
      (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
      goto LABEL_253;
    case 0x20:
      if ( v209 || *((_BYTE *)&this->m_nTodo_20 + 48) )
        return;
      *((_BYTE *)&this->m_nTodo_20 + 48) = 1;
      (((UIBigMap *)v208))->UIBigMap::UpdateActions((int *)&this->m_nTodo_20 + 2, 1);
      (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
      goto LABEL_254;
    case 0x21:
      if ( !v210 && !v209 && this->ScriptVM::IsRunning() )
      {
        __asm
        {
          fld     dword ptr [esi+0x2C]
          fsub    _flt_5_0
        }
        reg_EDI = (unsigned long)(&this->m_nTodo_20 + 2);
        // __asm { fstp    [esp+0x110+nSceneIdx] }
        (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 1, 1);
        v144 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
        __asm { fld     dword ptr [edi] }
        __asm
        {
          fstp    [esp+0x104+var_A4]
          fld     dword ptr [esi+0x30]
        }
        LOBYTE(v145) = v144 == 1;
        v200[1] = nSceneIdx.x;
        // __asm { fstp    [esp+0x110+var_9C] }
        (((ScriptVM *)this))->ScriptVM::ExecuteOpcode(v200, 0, 0, v145);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd04(*(&this->m_nPauseState + 11), 0);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd05(0);
        v146 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
        if ( v146 != -1 )
          *((_BYTE *)&this->m_nTodo_0A8 + 6) = v146 - 1;
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
LABEL_89:
        v188 = 0;
        fVal = (int)_ESI;
LABEL_90:
        v92 = (((CScreenMode *)v51))->CScreenMode::GetSoundList();
        (((PtrArray *)v92))->PtrArray::SetResolution(fVal, v188);
      }
      return;
    case 0x22:
      if ( v209 == 2 && this->ScriptVM::IsRunning() )
      {
        __asm
        {
          fld     _flt_12_0
          fmul    dword ptr [flt_56AA3C]
        }
        nSceneIdx.x = *((float *)&this->m_nTodo_0F4 + 1);
        if ( SLODWORD(nSceneIdx.x) > 0 )
        {
          __asm
          {
            fstp    st
            fild    [esp+0x104+nSceneIdx]
          }
        }
        __asm
        {
          fld     dword ptr [esi+0x0E0]
          fcos
        }
        pfVal2.y = 0.0f;
        __asm
        {
          fld     dword ptr [esi+0x0E0]
          fsin
          fstp    [esp+0x108+var_EC]
          fld     st(1)
          fmul    st, st(1)
          fstp    [esp+0x108+pfVal2]
          fstp    st
          fmul    [esp+0x108+var_EC]
          fld     [esp+0x108+pfVal2]
          fadd    dword ptr [esi+0x28]
          fstp    [esp+0x108+pfVal2]
          fld     [esp+0x108+var_F0]
          fadd    dword ptr [esi+0x2C]
          fstp    [esp+0x108+var_F0]
          fadd    dword ptr [esi+0x30]
          fstp    [esp+0x108+var_EC]
        }
        (((ScriptVM *)this))->ScriptVM::GetRolePosition(1u);
        (((ScriptVM *)this))->ScriptVM::ExecuteOpcode(&pfVal2, 0, 0, 1);
        (((ScriptVM *)this))->ScriptVM::GetRolePosition(0);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd05(0);
        v147 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
        if ( v147 != -1 )
          *((_BYTE *)&this->m_nTodo_0A8 + 6) = v147 - 1;
        (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
      }
      return;
    case 0x23:
      if ( !v209 && this->ScriptVM::IsRunning() )
      {
        (((RoleSystem *)this))->RoleSystem::ExecScriptDataA();
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd04(*(&this->m_nPauseState + 11), 1u);
        v149 = (((CScreenMode *)v148))->CScreenMode::GetSoundList();
        (((PtrArray *)v149))->PtrArray::SetResolution((int)_ESI, 0);
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
      }
      return;
    case 0x24:
      if ( (!v209 || v209 == 2) && this->ScriptVM::IsRunning() )
      {
        (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
        (((RoleSystem *)this))->RoleSystem::ExecScriptDataB();
        (((ScriptVM *)this))->ScriptVM::CallFunction(1u, 1);
        (((ScriptVM *)this))->ScriptVM::GetRolePosition(0);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd10(0);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd04(*(&this->m_nPauseState + 11), 0);
        (((PalScriptMgr *)this))->PalScriptMgr::RunCommand(0);
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
        v151 = (((CScreenMode *)v150))->CScreenMode::GetSoundList();
        (((PtrArray *)v151))->PtrArray::SetResolution((int)_ESI, 0);
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteScriptByID();
      }
      return;
    case 0x26:
      if ( !this->ScriptVM::IsRunning() )
        return;
      if ( v209 )
      {
        if ( v209 != 3 || !*((_DWORD *)&this->m_nTodo_0F4 + 2) )
          return;
        *((_DWORD *)&this->m_nTodo_20 + 13) = 0;
        pParams = *(gbVec3D *)(&this->m_nTodo_20 + 2);
        __asm
        {
          fld     [esp+0x108+var_E4]
          fsub    _flt_200_0
        }
        // __asm { fstp    [esp+0x108+var_E4] }
        (((ScriptVM *)this))->ScriptVM::SetRolePosition(0);
        (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 0, 1);
        (((ScriptVM *)this))->ScriptVM::ExecuteOpcode(&pParams, 0, 1, 0);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd04(*((_DWORD *)&this->m_nTodo_0F4 + 2), 0);
      }
      else
      {
        if ( !*((_DWORD *)&this->m_nTodo_0F4 + 1) )
          return;
        if ( !v210 )
          return;
        __asm
        {
          fld     [esp+0x104+arg_C]
          fadd    dword ptr [esi+0x54]
          fst     dword ptr [esi+0x54]
        }
        *((float *)&this->m_nTodo_20 + 13) = _ET1;
        __asm
        {
          fcomp   _flt_4_0
          fnstsw  ax
        }
        if ( (_AX & 0x100) != 0 )
          return;
        *((_DWORD *)&this->m_nTodo_20 + 13) = 0;
        pParams = *(gbVec3D *)(&this->m_nTodo_20 + 2);
        __asm
        {
          fld     [esp+0x108+var_E4]
          fadd    _flt_200_0
        }
        // __asm { fstp    [esp+0x108+var_E4] }
        (((ScriptVM *)this))->ScriptVM::SetRolePosition(0);
        (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 0, 1);
        (((ScriptVM *)this))->ScriptVM::ExecuteOpcode(&pParams, 0, 1, 0);
        (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd04(*((_DWORD *)&this->m_nTodo_0F4 + 1), 0);
      }
      (((ScriptVM *)this))->ScriptVM::SetRolePosition(1u);
      (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
      return;
    case 0x27:
      if ( !this->ScriptVM::IsRunning() )
        return;
      reg_EDI = (unsigned long)(_DWORD *)(((RoleSystem *)this->m_pCmdList->m_rect.left))->RoleSystem::GetRolePtr(*(&this->m_nTodo_0F4 + 2));
      v155 = *((_DWORD *)&this->m_nTodo_0E0 + 1) + *((_DWORD *)&this->m_nTodo_0E0 + 3);
      __asm { fld     _flt_0_0 }
      LODWORD(v155) = v155 - HIDWORD(v155);
      HIDWORD(v155) = *((_DWORD *)&this->m_nTodo_0E0 + 2);
      v156 = v155;
      LODWORD(v155) = *((_DWORD *)&this->m_nTodo_0E0 + 4);
      v157 = v156 >> 1;
      LODWORD(nSceneIdx.x) = v157;
      // __asm { fild    [esp+0x104+nSceneIdx] }
      __asm { fadd    _flt_0_5 }
      v158 = (HIDWORD(v155) + (int)v155) / 2;
      __asm { fmul    g_fScriptTileSize }
      LODWORD(nSceneIdx.y) = v158;
      __asm
      {
        fadd    dword ptr [edi+0x80]
        fstp    [esp+0x104+pParams]
        fild    [esp+0x104+var_D8]
        fadd    _flt_0_5
        fmul    g_fScriptTileSize
        fadd    dword ptr [edi+0x88]
        fstp    [esp+0x104+var_E0]
      }
      if ( v157 >= 0 )
      {
        v159 = reg_EDI[38];
        if ( v157 < v159 && v158 >= 0 && v158 < reg_EDI[39] )
        {
          __asm { fstp    st }
          reg_EAX = v157 + v159 * v158;
          reg_ECX = reg_EDI[40];
          __asm { fld     dword ptr [ecx+eax*8] }
        }
      }
      v162 = pParams.x;
      v163 = pParams.z;
      // __asm { fstp    dword ptr [esi+0x2C] }
      *((float *)&this->m_nTodo_20 + 3) = _ET1;
      *((float *)&this->m_nTodo_20 + 2) = v162;
      *((float *)&this->m_nTodo_20 + 4) = v163;
      pfVal2.x = *((float *)&this->m_nTodo_20 + 2);
      pfVal2.y = *((float *)&this->m_nTodo_20 + 3);
      v182 = *((_DWORD *)&this->m_nTodo_0F4 + 1);
      pfVal2.z = *((float *)&this->m_nTodo_20 + 4);
      (((RoleSystem *)this->m_pCmdList->m_rect.left))->RoleSystem::SetRoleParam(v182, &pfVal2.x, 0, 0);
      __asm
      {
        fst     [esp+0x104+var_F0]
        fstp    [esp+0x104+var_CC]
        fld     [esp+0x104+var_EC]
        fadd    _flt_80_0
      }
      nVal1.x = pfVal2.x;
      // __asm { fstp    [esp+0x110+var_C8] }
      (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 0, 1);
      (((PalScriptMgr *)this))->PalScriptMgr::CmdRoleMoveSmooth(0, v189);
      (((ScriptVM *)this))->ScriptVM::ExecuteOpcode(&pfVal2, 0, 1, 0);
      (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd14(*((_DWORD *)&this->m_nTodo_0F4 + 1), 0);
      (((ScriptVM *)this))->ScriptVM::FightInfo((int)&nVal1, 0, 1);
      goto LABEL_247;
    case 0x28:
      if ( !this->ScriptVM::IsRunning() || v209 )
        return;
      LODWORD(nSceneIdx.x) = (*(&this->m_nTodo_0F4 + 2) + 1) % 2;
      if ( LODWORD(nSceneIdx.x) )
      {
        v165 = *(float *)&this->m_nPauseState;
        v166 = *((float *)&this->m_nPauseState + 1);
      }
      else
      {
        v165 = *((float *)&this->m_nTodo_0F4 + 1);
        v166 = *((float *)&this->m_nTodo_0F4 + 2);
      }
      nVal1.x = v165;
      m_pCmdList = (RoleSystem *)this->m_pCmdList;
      nVal1.y = v166;
      reg_EAX = (unsigned long)(_DWORD *)((*((RoleSystem **)m_pCmdList + 4)))->RoleSystem::GetRolePtr(SLODWORD(nSceneIdx.x));
      // __asm { fild    [esp+0x104+nVal1] }
      pfVal2.y = 0.0f;
      __asm
      {
        fadd    _flt_0_5
        fmul    g_fScriptTileSize
        fadd    dword ptr [eax+0x80]
        fstp    [esp+0x104+pfVal2]
        fild    [esp+0x104+var_CC]
        fadd    _flt_0_5
        fmul    g_fScriptTileSize
        fadd    dword ptr [eax+0x88]
        fstp    [esp+0x104+var_EC]
      }
      if ( v165 >= 0.0f )
      {
        v169 = reg_EAX[38];
        if ( SLODWORD(v165) < v169 && v166 >= 0.0f && SLODWORD(v166) < reg_EAX[39] )
        {
          reg_EAX = reg_EAX[40];
          reg_EDX = LODWORD(v165) + v169 * LODWORD(v166);
          __asm
          {
            fld     dword ptr [eax+edx*8]
            fstp    [esp+0x104+var_F0]
          }
        }
      }
      v196 = pfVal2;
      pParams.x = *((float *)&this->m_nTodo_20 + 2);
      v172 = (RoleSystem *)this->m_pCmdList;
      nTypea = LODWORD(v165);
      x_low = LODWORD(nSceneIdx.x);
      v174 = *((float *)&this->m_nTodo_20 + 4);
      pParams.y = *((float *)&this->m_nTodo_20 + 3);
      pParams.z = v174;
      ((*((Scene **)v172 + 4)))->Scene::GetTileHeight(SLODWORD(nSceneIdx.x), nTypea, SLODWORD(v166), 0);
      // __asm { fstp    [esp+0x104+var_E4] }
      (((PalScriptMgr *)this))->PalScriptMgr::BuildCmdTransform(&pMatrix);
      __asm
      {
        fld     [esp+0x104+var_8]
        fadd    [esp+0x104+var_E4]
      }
      // __asm { fstp    [esp+0x108+var_E4] }
      (((ScriptVM *)this))->ScriptVM::SetRolePosition(0);
      (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 0, 0);
      (((ScriptVM *)this))->ScriptVM::ExecuteOpcode(&pParams, 0, 1, 0);
      (((ScriptVM *)this))->ScriptVM::GetRolePosition(1u);
      (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd14(x_low, 1u);
      (((ScriptVM *)this))->ScriptVM::GetRolePosition(0);
      (((ScriptVM *)this))->ScriptVM::FightInfo((int)&v196, 0, 0);
      (((ScriptVM *)this))->ScriptVM::SetRolePosition(1u);
      goto LABEL_253;
    case 0x29:
      if ( !this->ScriptVM::IsRunning() )
        return;
      if ( v209 == 10 )
        goto LABEL_238;
      (((ScriptVM *)this))->ScriptVM::FightInfo((int)(&this->m_nTodo_20 + 2), 1, 1);
      (((PalScriptMgr *)this))->PalScriptMgr::CmdRoleMoveDirect(v189);
      (((PalScriptMgr *)this))->PalScriptMgr::CmdRoleMoveSmooth(0, v191);
      (((PalScriptMgr *)this))->PalScriptMgr::CmdPushCmd07(1u);
      goto LABEL_246;
    case 0x2A:
      if ( v209 != 1 )
        return;
      if ( !this->ScriptVM::IsRunning() )
        return;
      reg_EAX = g_pRoleSystem;
      if ( *(&this->m_nTodo_0F4 + 2) != g_pRoleSystem->m_partyActor.m_nState )
        return;
      __asm
      {
        fld     dword ptr [esi+0x28]
        fsub    dword ptr [eax+0x0A0]
        fstp    [esp+0x104+pParams]
        fld     dword ptr [esi+0x2C]
        fsub    dword ptr [eax+0x0A4]
      }
      v196.x = pParams.x;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     dword ptr [esi+0x30]
        fsub    dword ptr [eax+0x0A8]
      }
      v196.y = pParams.y;
      // __asm { fstp    [esp+0x104+var_E0] }
      v196.z = pParams.z;
      (((gbVec3D *)&v196))->gbVec3D::Length();
      __asm
      {
        fcomp   _flt_600_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
      {
        v177 = *((float *)&this->m_nTodo_20 + 4);
        reg_EAX = g_pRoleSystem;
        nSceneIdx.x = *((float *)&this->m_nTodo_20 + 2);
        // __asm { fld     [esp+0x104+nSceneIdx] }
        nSceneIdx.z = v177;
        nSceneIdx.y = 0.0f;
        __asm
        {
          fsub    dword ptr [eax+4]
          fld     dword ptr [eax+8]
          fchs
          fstp    [esp+0x104+var_C4+4]
          fld     [esp+0x104+var_D4]
          fsub    dword ptr [eax+0x0C]
        }
        // __asm { fstp    [esp+0x104+var_C4+8] }
        nSceneIdx.y = v196.y;
        // __asm { fstp    [esp+0x104+nSceneIdx] }
        nSceneIdx.z = v196.z;
        (((gbVec3D *)&nSceneIdx))->gbVec3D::Length();
        __asm
        {
          fld     [esp+0x104+nSceneIdx]
          fdiv    st, st(1)
        }
        reg_EAX = g_pRoleSystem;
        __asm
        {
          fstp    [esp+0x10C+nSceneIdx]
          fld     [esp+0x10C+var_D8]
          fdiv    st, st(1)
          fstp    [esp+0x10C+var_D8]
          fld     [esp+0x10C+var_D4]
          fdiv    st, st(1)
          fstp    [esp+0x10C+var_D4]
          fsub    dword ptr [flt_56AB44]
          fld     st
          fmul    [esp+0x10C+nSceneIdx]
          fstp    [esp+0x10C+nSceneIdx]
          fld     st
          fmul    [esp+0x10C+var_D8]
          fstp    [esp+0x10C+var_D8]
          fmul    [esp+0x10C+var_D4]
          fstp    [esp+0x10C+var_D4]
          fld     [esp+0x10C+nSceneIdx]
          fadd    dword ptr [eax+4]
          fld     [esp+0x10C+var_D8]
          fadd    dword ptr [eax+8]
          fstp    [esp+0x10C+var_C4+4]
          fld     [esp+0x10C+var_D4]
          fadd    dword ptr [eax+0x0C]
        }
        nSceneIdx.y = v196.y;
        // __asm { fstp    [esp+0x110+var_C4+8] }
        // __asm { fstp    [esp+0x110+nSceneIdx] }
        nSceneIdx.z = v196.z;
        (((ScriptVM *)this))->ScriptVM::FightInfo((int)&nSceneIdx, 1, 1);
LABEL_245:
        (((PalScriptMgr *)this))->PalScriptMgr::CmdRoleMoveDirect(v189);
LABEL_246:
        (((ScriptVM *)this))->ScriptVM::CallFunction(1u, 0);
LABEL_247:
        (((PalScriptMgr *)this))->PalScriptMgr::ExecuteOpcode();
LABEL_248:
        v180 = (((CScreenMode *)v37))->CScreenMode::GetSoundList();
        (((PtrArray *)v180))->PtrArray::SetResolution((int)_ESI, 0);
      }
      else
      {
LABEL_249:
        v181 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("outdist");
        (((PalScriptMgr *)&stru_DBA134))->PalScriptMgr::ShowTextBox(v181);
      }
      goto LABEL_254;
    default:
      goto LABEL_254;
  }
}

// 0x0042C1A0
BOOL ScriptVM::IsRunning()
{
  return !this->m_nPathStep && !*((_BYTE *)&this->m_nTodo_20 + 48);
}

// 0x0042C730
gbVFileSystem * ScriptVM::OpenSceneScript()
{
  Scene *v2; // eax
  const char *v3; // edi
  gbVFileSystem *result; // eax
  OpenSceneFile v5; // [esp+0xC] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x10] [ebp-0x110] BYREF
  int v7; // [esp+0x11C] [ebp-0x4]

  v2 = UISceneUpdate();
  sprintf(Buffer, "%s%s", "scene\\", (const char *)v2);
  v7 = 0;
  v3 = a4CCvd;
  if ( !(_BYTE)g_ScriptSystemData.m_nScriptFlag )
    v3 = a4C1Cvd;
  strcpy((char *)Buffer, v3);
  (((GeomNode *)(&this->m_nTodo_20 + 14)))->GeomNode::InitFromFile((const gbGeomNode *)Buffer, 0);
  (*(void ( **)(_DWORD, _DWORD))(**(&this->m_nTodo_20 + 15) + 24))(*((_DWORD *)&this->m_nTodo_20 + 15), 0);
  (((gbVisNode *)*((gbVisNode **)&this->m_nTodo_20 + 15)))->gbVisNode::SetTimeScale(0.0);
  v7 = -1;
  (((OpenSceneFile *)&v5))->OpenSceneFile::~OpenSceneFile();
  return result;
}

// 0x0042C810
char ScriptVM::UpdatePauseState()
{
  char v1; // al
  int m_nPauseState; // edx
  int v3; // eax
  int v4; // ebp
  LONG left; // edi
  int v6; // esi

  v1 = *((_BYTE *)&this->m_nTodo_0A8 + 6);
  if ( v1 != -1 )
    *((_BYTE *)&this->m_nTodo_0A8 + 6) = v1 - 1;
  m_nPauseState = this->m_nPauseState;
  LOBYTE(v3) = *((_BYTE *)&this->m_nTodo_0A8 + 7) == 0;
  *((_BYTE *)&this->m_nTodo_0A8 + 7) = v3;
  if ( m_nPauseState == 1 )
  {
    LOBYTE(g_ScriptSystemData.m_nScriptFlag) = (_BYTE)v3 == 0;
    v4 = 0;
    left = this->m_pCmdList->m_rect.left;
    v3 = *(_DWORD *)(left + 220);
    if ( v3 > 0 )
    {
      v6 = left + 224;
      do
      {
        if ( *(_BYTE *)(v6 + 244) == 37 )
          (((PalScriptMgr *)v6))->PalScriptMgr::LoadSceneGeometry(g_ScriptSystemData.m_nScriptFlag);
        v3 = *(_DWORD *)(left + 220);
        ++v4;
        v6 += 896;
      }
      while ( v4 < v3 );
    }
  }
  return v3;
}

// 0x0042C950
int ScriptVM::ExecuteOpcode(void *pData, unsigned __int8 nType, int nCount, int a5)
{
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int *p_m_nPathMode; // ebx
  int v10; // edx
  int v11; // eax
  int m_nPathStep; // eax
  char *m_nTodo_358; // edi
  float m_fPathEndY; // ecx
  int result; // eax
  void *v16; // esi
  _DWORD *v17; // eax
  float x; // eax
  float v19; // edx
  float v20; // ecx
  int v21; // esi
  unsigned int v22; // eax
  _DWORD *v23; // eax
  float v24; // eax
  float v25; // edx
  int v26; // eax
  int v27; // edi
  gbVec3D *RoleName; // eax
  gbVec3D *v29; // edi
  float y; // edx
  float z; // ecx
  int v32; // edx
  float v33; // edx
  float v34; // ecx
  int v35; // edx
  gbVec3D v36; // [esp+0xC] [ebp-0x5C] BYREF
  int v37; // [esp+0x18] [ebp-0x50]
  _DWORD v38[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v38))->CG_Entry::GetCGEntry();
  v6 = *((_DWORD *)&this->m_nTodo_20 + 2);
  v7 = *((_DWORD *)&this->m_nTodo_20 + 3);
  v38[1] = nType;
  v8 = *((_DWORD *)&this->m_nTodo_20 + 4);
  v38[3] = v6;
  v38[5] = v8;
  v38[4] = v7;
  p_m_nPathMode = (int *)&this->m_nPathMode;
  v10 = *((_DWORD *)pData + 1);
  v11 = *((_DWORD *)pData + 2);
  v38[6] = *(_DWORD *)pData;
  v38[7] = v10;
  v38[8] = v11;
  m_nPathStep = this->m_nPathStep;
  LOBYTE(v38[0]) = 1;
  v38[2] = 0;
  v38[15] = (unsigned __int8)nCount;
  v38[16] = (unsigned __int8)a5;
  if ( !m_nPathStep
    || (m_nTodo_358 = this->m_nTodo_358, m_fPathEndY = this->m_fPathEndY, m_nTodo_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v16 = (void *)operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v22 = (unsigned long)p_m_nPathMode[8];
      if ( v22 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v27 = ((int)(v22 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nPathMode))->RoleSystem::GetRoleName(2 * v27);
        v29 = (gbVec3D *)((char *)RoleName + 4 * v27);
        LODWORD(v29->x) = (unsigned long)v16;
        (((gbVec3D *)&v36))->gbVec3D::Copy(p_m_nPathMode[3], RoleName);
        y = v36.y;
        p_m_nPathMode[1] = LODWORD(v36.x);
        z = v36.z;
        *((float *)p_m_nPathMode + 2) = y;
        v32 = v37;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v32;
        (((gbVec3D *)&v36))->gbVec3D::Copy((int)v16, v29);
        v33 = v36.y;
        p_m_nPathMode[5] = LODWORD(v36.x);
        v34 = v36.z;
        *((float *)p_m_nPathMode + 6) = v33;
        v35 = v37;
        *((float *)p_m_nPathMode + 7) = v34;
        p_m_nPathMode[8] = v35;
      }
      else
      {
        v23 = (_DWORD *)(v22 + 4);
        p_m_nPathMode[8] = (int)v23;
        *v23 = (_DWORD)v16;
        (((gbVec3D *)&v36))->gbVec3D::Copy((int)v16, (gbVec3D *)p_m_nPathMode[8]);
        v24 = v36.y;
        p_m_nPathMode[5] = LODWORD(v36.x);
        v25 = v36.z;
        *((float *)p_m_nPathMode + 6) = v24;
        v26 = v37;
        *((float *)p_m_nPathMode + 7) = v25;
        p_m_nPathMode[8] = v26;
      }
    }
    else
    {
      p_m_nPathMode[10] = 2;
      v17 = (_DWORD *)operator new(8u);
      p_m_nPathMode[9] = (int)v17;
      v17[1] = (_DWORD)v16;
      (((gbVec3D *)&v36))->gbVec3D::Copy((int)v16 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
      x = v36.x;
      v19 = v36.z;
      v20 = v36.y;
      v21 = v37;
      p_m_nPathMode[1] = LODWORD(v36.x);
      *((float *)p_m_nPathMode + 2) = v20;
      *((float *)p_m_nPathMode + 3) = v19;
      p_m_nPathMode[4] = v21;
      *((float *)p_m_nPathMode + 5) = x;
      *((float *)p_m_nPathMode + 6) = v20;
      *((float *)p_m_nPathMode + 7) = v19;
      p_m_nPathMode[8] = v21;
    }
    m_nTodo_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_nTodo_358 + 76);
    if ( !m_nTodo_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_nTodo_358 = ((char *)(m_nTodo_358 + 76));
  if ( m_nTodo_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_nTodo_358 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nPathMode[11] + 1);
      p_m_nPathMode[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nTodo_358, v38, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nTodo_358 )
    qmemcpy(m_nTodo_358, v38, 0x4Cu);
  (((ScriptVM *)p_m_nPathMode))->ScriptVM::GetString();
  result = this->m_nPathStep + 1;
  this->m_nPathStep = result;
  return result;
}

// 0x0042CB70
void ScriptVM::FightInfo(int nVal1, int nVal2, int nVal3)
{
  int *p_m_nPathMode; // ebp
  int v6; // edx
  int v7; // eax
  int m_nPathStep; // eax
  char *m_nTodo_358; // edi
  float m_fPathEndY; // ecx
  void *v11; // esi
  _DWORD *v12; // eax
  float x; // eax
  float v14; // edx
  float v15; // ecx
  int v16; // esi
  unsigned int v17; // eax
  _DWORD *v18; // eax
  float v19; // eax
  float v20; // edx
  int v21; // eax
  int v22; // edi
  gbVec3D *RoleName; // eax
  gbVec3D *v24; // edi
  float y; // edx
  float z; // ecx
  int v27; // edx
  float v28; // edx
  float v29; // ecx
  int v30; // edx
  gbVec3D v31; // [esp+0xC] [ebp-0x5C] BYREF
  int v32; // [esp+0x18] [ebp-0x50]
  _DWORD v33[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v33))->CG_Entry::GetCGEntry();
  LOBYTE(v33[0]) = 2;
  v33[2] = 0;
  p_m_nPathMode = (int *)&this->m_nPathMode;
  v33[3] = LODWORD(g_pRoleSystem->m_fPosX);
  v33[4] = LODWORD(g_pRoleSystem->m_fPosY);
  v33[5] = LODWORD(g_pRoleSystem->m_fPosZ);
  v6 = *(_DWORD *)(nVal1 + 4);
  v7 = *(_DWORD *)(nVal1 + 8);
  v33[6] = *(_DWORD *)nVal1;
  v33[7] = v6;
  v33[8] = v7;
  m_nPathStep = this->m_nPathStep;
  v33[15] = (unsigned __int8)nVal2;
  v33[16] = (unsigned __int8)nVal3;
  if ( !m_nPathStep
    || (m_nTodo_358 = this->m_nTodo_358, m_fPathEndY = this->m_fPathEndY, m_nTodo_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v11 = (void *)operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v17 = (unsigned long)p_m_nPathMode[8];
      if ( v17 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v22 = ((int)(v17 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nPathMode))->RoleSystem::GetRoleName(2 * v22);
        v24 = (gbVec3D *)((char *)RoleName + 4 * v22);
        LODWORD(v24->x) = (unsigned long)v11;
        (((gbVec3D *)&v31))->gbVec3D::Copy(p_m_nPathMode[3], RoleName);
        y = v31.y;
        p_m_nPathMode[1] = LODWORD(v31.x);
        z = v31.z;
        *((float *)p_m_nPathMode + 2) = y;
        v27 = v32;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v27;
        (((gbVec3D *)&v31))->gbVec3D::Copy((int)v11, v24);
        v28 = v31.y;
        p_m_nPathMode[5] = LODWORD(v31.x);
        v29 = v31.z;
        *((float *)p_m_nPathMode + 6) = v28;
        v30 = v32;
        *((float *)p_m_nPathMode + 7) = v29;
        p_m_nPathMode[8] = v30;
      }
      else
      {
        v18 = (_DWORD *)(v17 + 4);
        p_m_nPathMode[8] = (int)v18;
        *v18 = (_DWORD)v11;
        (((gbVec3D *)&v31))->gbVec3D::Copy((int)v11, (gbVec3D *)p_m_nPathMode[8]);
        v19 = v31.y;
        p_m_nPathMode[5] = LODWORD(v31.x);
        v20 = v31.z;
        *((float *)p_m_nPathMode + 6) = v19;
        v21 = v32;
        *((float *)p_m_nPathMode + 7) = v20;
        p_m_nPathMode[8] = v21;
      }
    }
    else
    {
      p_m_nPathMode[10] = 2;
      v12 = (_DWORD *)operator new(8u);
      p_m_nPathMode[9] = (int)v12;
      v12[1] = (_DWORD)v11;
      (((gbVec3D *)&v31))->gbVec3D::Copy((int)v11 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
      x = v31.x;
      v14 = v31.z;
      v15 = v31.y;
      v16 = v32;
      p_m_nPathMode[1] = LODWORD(v31.x);
      *((float *)p_m_nPathMode + 2) = v15;
      *((float *)p_m_nPathMode + 3) = v14;
      p_m_nPathMode[4] = v16;
      *((float *)p_m_nPathMode + 5) = x;
      *((float *)p_m_nPathMode + 6) = v15;
      *((float *)p_m_nPathMode + 7) = v14;
      p_m_nPathMode[8] = v16;
    }
    m_nTodo_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_nTodo_358 + 76);
    if ( !m_nTodo_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_nTodo_358 = ((char *)(m_nTodo_358 + 76));
  if ( m_nTodo_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_nTodo_358 )
    {
LABEL_16:
      ++p_m_nPathMode[11];
      return;
    }
LABEL_15:
    qmemcpy(m_nTodo_358, v33, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nTodo_358 )
    qmemcpy(m_nTodo_358, v33, 0x4Cu);
  (((ScriptVM *)p_m_nPathMode))->ScriptVM::GetString();
  ++this->m_nPathStep;
}

// 0x0042CD90
int ScriptVM::CallFunction(unsigned __int8 nFuncID, int nArgCount)
{
  int *p_m_nPathMode; // ebx
  int m_nPathStep; // eax
  char *m_nTodo_358; // edi
  float m_fPathEndY; // ecx
  int result; // eax
  void *v9; // esi
  _DWORD *v10; // eax
  float v11; // ecx
  float v12; // edx
  float x; // eax
  int v14; // esi
  unsigned int v15; // eax
  _DWORD *v16; // eax
  float v17; // edx
  float v18; // ecx
  int v19; // edx
  int v20; // edi
  gbVec3D *RoleName; // eax
  int *v22; // edi
  float y; // ecx
  float z; // eax
  int v25; // ecx
  int v26; // ecx
  gbVec3D v27; // [esp+0xC] [ebp-0x5C] BYREF
  int v28; // [esp+0x18] [ebp-0x50]
  _DWORD v29[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v29))->CG_Entry::GetCGEntry();
  p_m_nPathMode = (int *)&this->m_nPathMode;
  v29[15] = nFuncID;
  LOBYTE(v29[0]) = 3;
  m_nPathStep = this->m_nPathStep;
  v29[16] = nArgCount;
  if ( !m_nPathStep
    || (m_nTodo_358 = this->m_nTodo_358, m_fPathEndY = this->m_fPathEndY, m_nTodo_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v9 = (void *)operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v15 = (unsigned long)p_m_nPathMode[8];
      if ( v15 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v20 = ((int)(v15 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nPathMode))->RoleSystem::GetRoleName(2 * v20);
        v22 = (int *)(&RoleName->x + v20);
        *v22 = (int)v9;
        (((gbVec3D *)&v27))->gbVec3D::Copy(p_m_nPathMode[3], RoleName);
        y = v27.y;
        p_m_nPathMode[1] = LODWORD(v27.x);
        z = v27.z;
        *((float *)p_m_nPathMode + 2) = y;
        v25 = v28;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v25;
        v26 = (unsigned long)(*v22 + 4028);
        p_m_nPathMode[5] = (unsigned long)*v22;
        p_m_nPathMode[6] = v26;
        p_m_nPathMode[7] = (int)v9;
        p_m_nPathMode[8] = (int)v22;
      }
      else
      {
        v16 = (_DWORD *)(v15 + 4);
        p_m_nPathMode[8] = (int)v16;
        *v16 = (_DWORD)v9;
        (((gbVec3D *)&v27))->gbVec3D::Copy((int)v9, (gbVec3D *)p_m_nPathMode[8]);
        v17 = v27.y;
        p_m_nPathMode[5] = LODWORD(v27.x);
        v18 = v27.z;
        *((float *)p_m_nPathMode + 6) = v17;
        v19 = v28;
        *((float *)p_m_nPathMode + 7) = v18;
        p_m_nPathMode[8] = v19;
      }
    }
    else
    {
      p_m_nPathMode[10] = 2;
      v10 = (_DWORD *)operator new(8u);
      p_m_nPathMode[9] = (int)v10;
      v10[1] = (_DWORD)v9;
      (((gbVec3D *)&v27))->gbVec3D::Copy((int)v9 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
      v11 = v27.y;
      v12 = v27.z;
      x = v27.x;
      v14 = v28;
      p_m_nPathMode[1] = LODWORD(v27.x);
      *((float *)p_m_nPathMode + 2) = v11;
      *((float *)p_m_nPathMode + 3) = v12;
      p_m_nPathMode[4] = v14;
      *((float *)p_m_nPathMode + 5) = x;
      *((float *)p_m_nPathMode + 6) = v11;
      *((float *)p_m_nPathMode + 7) = v12;
      p_m_nPathMode[8] = v14;
    }
    m_nTodo_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_nTodo_358 + 76);
    if ( !m_nTodo_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_nTodo_358 = ((char *)(m_nTodo_358 + 76));
  if ( m_nTodo_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_nTodo_358 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nPathMode[11] + 1);
      p_m_nPathMode[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nTodo_358, v29, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nTodo_358 )
    qmemcpy(m_nTodo_358, v29, 0x4Cu);
  (((ScriptVM *)p_m_nPathMode))->ScriptVM::GetString();
  result = this->m_nPathStep + 1;
  this->m_nPathStep = result;
  return result;
}

// 0x0042D4B0
int ScriptVM::SetRolePosition(unsigned __int8 pData)
{
  int *p_m_nPathMode; // ebx
  char *m_nTodo_358; // edi
  float m_fPathEndY; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // ecx
  int v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // edx
  float v16; // ecx
  int v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // ecx
  float z; // eax
  int v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  p_m_nPathMode = (int *)&this->m_nPathMode;
  LOBYTE(v27[0]) = 8;
  v27[15] = pData;
  if ( !this->m_nPathStep
    || (m_nTodo_358 = this->m_nTodo_358, m_fPathEndY = this->m_fPathEndY, m_nTodo_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v13 = (unsigned long)p_m_nPathMode[8];
      if ( v13 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nPathMode))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nPathMode[3], RoleName);
        y = v25.y;
        p_m_nPathMode[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nPathMode + 2) = y;
        v23 = v26;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nPathMode[5] = (unsigned long)*v20;
        p_m_nPathMode[6] = v24;
        p_m_nPathMode[7] = (int)v7;
        p_m_nPathMode[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nPathMode[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nPathMode[8]);
        v15 = v25.y;
        p_m_nPathMode[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nPathMode + 6) = v15;
        v17 = v26;
        *((float *)p_m_nPathMode + 7) = v16;
        p_m_nPathMode[8] = v17;
      }
    }
    else
    {
      p_m_nPathMode[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nPathMode[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_nPathMode[1] = LODWORD(v25.x);
      *((float *)p_m_nPathMode + 2) = v10;
      *((float *)p_m_nPathMode + 3) = v12;
      p_m_nPathMode[4] = v11;
      *((float *)p_m_nPathMode + 5) = x;
      *((float *)p_m_nPathMode + 6) = v10;
      *((float *)p_m_nPathMode + 7) = v12;
      p_m_nPathMode[8] = v11;
    }
    m_nTodo_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_nTodo_358 + 76);
    if ( !m_nTodo_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_nTodo_358 = ((char *)(m_nTodo_358 + 76));
  if ( m_nTodo_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_nTodo_358 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nPathMode[11] + 1);
      p_m_nPathMode[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nTodo_358, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nTodo_358 )
    qmemcpy(m_nTodo_358, v27, 0x4Cu);
  (((ScriptVM *)p_m_nPathMode))->ScriptVM::GetString();
  result = this->m_nPathStep + 1;
  this->m_nPathStep = result;
  return result;
}

// 0x0042D670
int ScriptVM::GetRolePosition(unsigned __int8 pData)
{
  int *p_m_nPathMode; // ebx
  char *m_nTodo_358; // edi
  float m_fPathEndY; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // ecx
  int v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // edx
  float v16; // ecx
  int v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // ecx
  float z; // eax
  int v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  p_m_nPathMode = (int *)&this->m_nPathMode;
  LOBYTE(v27[0]) = 9;
  v27[15] = pData;
  if ( !this->m_nPathStep
    || (m_nTodo_358 = this->m_nTodo_358, m_fPathEndY = this->m_fPathEndY, m_nTodo_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v13 = (unsigned long)p_m_nPathMode[8];
      if ( v13 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nPathMode))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nPathMode[3], RoleName);
        y = v25.y;
        p_m_nPathMode[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nPathMode + 2) = y;
        v23 = v26;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nPathMode[5] = (unsigned long)*v20;
        p_m_nPathMode[6] = v24;
        p_m_nPathMode[7] = (int)v7;
        p_m_nPathMode[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nPathMode[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nPathMode[8]);
        v15 = v25.y;
        p_m_nPathMode[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nPathMode + 6) = v15;
        v17 = v26;
        *((float *)p_m_nPathMode + 7) = v16;
        p_m_nPathMode[8] = v17;
      }
    }
    else
    {
      p_m_nPathMode[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nPathMode[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_nPathMode[1] = LODWORD(v25.x);
      *((float *)p_m_nPathMode + 2) = v10;
      *((float *)p_m_nPathMode + 3) = v12;
      p_m_nPathMode[4] = v11;
      *((float *)p_m_nPathMode + 5) = x;
      *((float *)p_m_nPathMode + 6) = v10;
      *((float *)p_m_nPathMode + 7) = v12;
      p_m_nPathMode[8] = v11;
    }
    m_nTodo_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_nTodo_358 + 76);
    if ( !m_nTodo_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_nTodo_358 = ((char *)(m_nTodo_358 + 76));
  if ( m_nTodo_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_nTodo_358 )
    {
LABEL_16:
      result = (unsigned long)(p_m_nPathMode[11] + 1);
      p_m_nPathMode[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_nTodo_358, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_nTodo_358 )
    qmemcpy(m_nTodo_358, v27, 0x4Cu);
  (((ScriptVM *)p_m_nPathMode))->ScriptVM::GetString();
  result = this->m_nPathStep + 1;
  this->m_nPathStep = result;
  return result;
}

// 0x0042FB60
char * ScriptVM::GetString()
{
  char *v2; // ebx
  _DWORD *v3; // eax
  char *v4; // edi
  char *result; // eax
  int *v6; // ebx
  int *v7; // esi
  int v8; // ecx
  int *m_nTodo_20; // eax
  int *v10; // eax
  int *v11; // esi
  int v12; // ecx
  int v13; // ebp
  size_t v14; // eax
  char *v15; // eax
  int *m_bufReadPtr; // ecx
  char *v17; // edi
  int *v18; // eax
  char *v19; // edx
  int v20; // ebp
  int *p_m_bufHead; // ebp
  int *p_m_bufWritePtr; // esi
  int v23; // edx
  int v24; // ecx
  int v25; // [esp+0xC] [ebp-0x18]
  char *v26; // [esp+0x10] [ebp-0x14]
  int m_bufCapacity; // [esp+0x1C] [ebp-0x8]

  v2 = (char *)operator new(0xFBCu);
  if ( *((_DWORD *)&this->m_nTodo_20 + 3) )
  {
    m_nTodo_20 = (int *)this->m_nTodo_20;
    if ( (unsigned int)m_nTodo_20 >= *((_DWORD *)&this->m_nTodo_20 + 1) + 4 * *((_DWORD *)&this->m_nTodo_20 + 2) - 4 )
    {
      v13 = (((int)m_nTodo_20 - this->m_bufReadPtr) >> 2) + 1;
      v25 = v13;
      v14 = 8 * v13;
      if ( (v13 & 0x10000000) != 0 )
        v14 = 0;
      v15 = (char *)operator new(v14);
      m_bufReadPtr = (int *)this->m_bufReadPtr;
      v26 = (char *)v15;
      v17 = (char *)&v15[4 * ((unsigned int)(2 * v13) >> 2)];
      v18 = this->m_nTodo_20 + 1;
      v19 = (char *)v17;
      if ( m_bufReadPtr != v18 )
      {
        do
        {
          v20 = (unsigned long)(*m_bufReadPtr++);
          *(_DWORD *)v19 = v20;
          v19 += 4;
        }
        while ( m_bufReadPtr != v18 );
        v13 = v25;
      }
      operator delete(*((void **)&this->m_nTodo_20 + 1));
      *((_DWORD *)&this->m_nTodo_20 + 1) = (unsigned long)v26;
      *((_DWORD *)&this->m_nTodo_20 + 2) = 2 * v13;
      result = (char *)&v17[4 * v13];
      *(_DWORD *)result = (_DWORD)v2;
      m_bufCapacity = this->m_bufCapacity;
      p_m_bufHead = (int *)&this->m_bufHead;
      p_m_bufWritePtr = (int *)&this->m_bufWritePtr;
      v23 = *(_DWORD *)v17 + 4028;
      *p_m_bufHead = *(_DWORD *)v17;
      p_m_bufHead[1] = v23;
      p_m_bufHead[2] = m_bufCapacity;
      p_m_bufHead[3] = (int)v17;
      v24 = *(_DWORD *)result;
      *p_m_bufWritePtr = *(_DWORD *)result;
      p_m_bufWritePtr[1] = v24 + 4028;
      p_m_bufWritePtr[2] = (int)v2;
      p_m_bufWritePtr[3] = (int)result;
    }
    else
    {
      v10 = (int *)(m_nTodo_20 + 1);
      this->m_nTodo_20 = ((int *)(v10));
      v11 = (int *)&this->m_bufWritePtr;
      *v10 = (int)v2;
      result = (char *)v11[3];
      v12 = *(_DWORD *)result;
      *v11 = *(_DWORD *)result;
      v11[1] = v12 + 4028;
      v11[2] = (int)v2;
      v11[3] = (int)result;
    }
  }
  else
  {
    *((_DWORD *)&this->m_nTodo_20 + 2) = 2;
    v3 = (_DWORD *)operator new(8u);
    *((_DWORD *)&this->m_nTodo_20 + 1) = (unsigned long)v3;
    v3[1] = (_DWORD)v2;
    v4 = (char *)(v2 + 1976);
    result = (char *)(*((_DWORD *)&this->m_nTodo_20 + 1) + 4);
    v6 = (int *)&this->m_bufHead;
    v7 = (int *)&this->m_bufWritePtr;
    v8 = *(_DWORD *)result;
    *v7 = *(_DWORD *)result;
    *v6 = v8;
    v7[1] = v8 + 4028;
    v6[1] = v8 + 4028;
    v7[2] = (int)v4;
    v6[2] = (int)v4;
    v7[3] = (int)result;
    v6[3] = (int)result;
  }
  return result;
}

// 0x004366C0
int ScriptVM::GetObjectByID(int nObjID)
{
  int v1; // eax
  int v2; // eax
  int result; // eax

  v1 = *(_DWORD *)(g_pLoadBuffer + 16);
  if ( v1 )
  {
    v2 = v1 - 1;
    if ( v2 )
    {
      result = v2 - 1;
      if ( result )
        return result;
      if ( !nObjID && !*(_DWORD *)(g_pLoadBuffer + 24) )
        goto LABEL_6;
    }
    else if ( !nObjID || !*(_DWORD *)(g_pLoadBuffer + 24) )
    {
LABEL_6:
      result = 0;
      *(_DWORD *)(g_pLoadBuffer + 24) = 0;
      return result;
    }
    result = 1;
    *(_DWORD *)(g_pLoadBuffer + 24) = 1;
  }
  else
  {
    result = nObjID;
    *(_DWORD *)(g_pLoadBuffer + 24) = nObjID;
  }
  return result;
}
