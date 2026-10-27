#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Script/ScriptSystem.h"
#include "Role/Actor.h"
#include "Render/CScreenMode.h"
#include "GameBase/GRPinput.h"
#include "GameBase/InputSystem.h"
#include "GameBase/PAL3.h"
#include "Script/PalScript.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget3.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Misc/String.h"
#include "Misc/TxtFile.h"
#include "Misc/UITextArea.h"
#include "Misc/scAsmDecoder.h"
#include "Misc/scVarStack.h"
#include "Misc/tagRoleSystemData.h"

// 0x0040C630
void ScriptSystem::Render(gbMatrixStack *pMatrixStack)
{
  scAsmDecoder *v2; // edx
  scAsmDecoder *v3; // ebx
  RoleSystem *v4; // edi
  RenderTarget3 *Instance; // eax
  int m_ptr_4; // edi
  gbRenderEffect *v7; // ecx
  struct gbVec3D v8; // [esp+0xC] [ebp-0x10] BYREF
  int v9; // [esp+0x18] [ebp-0x4]

  v2 = dword_C10CC8;
  v3 = 0;
  v4 = (RoleSystem *)(&g_RoleSlotBuf.dword_17AA450 + 150);
  do
  {
    if ( v3 != v2 )
    {
      (((RoleSystem *)v4))->RoleSystem::RenderRole(pMatrixStack, 0);
      v2 = dword_C10CC8;
    }
    v4 = (RoleSystem *)((char *)v4 + 8704);
    v3 = (scAsmDecoder *)((char *)v3 + 1);
  }
  while ( (int)v4 < (int)&g_RoleSystemArrayEnd );
  if ( g_fEffectTimer >= 1.2f )
  {
    (((RoleSystem *)&g_RoleSlotBuf.m_teamData3[2176 * (_DWORD)v2 + 588]))->RoleSystem::RenderRole(pMatrixStack, 0);
  }
  else if ( rand() % 3 )
  {
    (((RoleSystem *)&g_RoleSlotBuf.m_teamData3[2176 * (_DWORD)dword_C10CC8 + 588]))->RoleSystem::RenderRole(pMatrixStack, 0);
  }
  else
  {
    Instance = (((RenderTarget3 *)3))->RenderTarget3::GetInstance();
    m_ptr_4 = (int)Instance->m_ptr_4;
    if ( m_ptr_4 )
    {
      v7 = (gbRenderEffect *)Instance->m_ptr_4;
      v8.x = 0.69999999;
      v8.y = 0.1;
      v8.z = 0.1;
      v9 = 1056964608;
      (((gbRenderEffect *)v7))->gbRenderEffect::SetVariant((GBPARAMHANDLE)(GBPARAM_TEXTURE1|GBPARAM_PROJMATRIX), &v8);
      (((RoleSystem *)&g_RoleSlotBuf.m_teamData3[2176 * (_DWORD)dword_C10CC8 + 588]))->RoleSystem::RenderRole(pMatrixStack, m_ptr_4);
    }
  }
  (((RoleSystem *)&g_RoleSystemExtra1))->RoleSystem::RenderRole(pMatrixStack, 0);
  (((RoleSystem *)&g_RoleSystemExtra0))->RoleSystem::RenderRole(pMatrixStack, 0);
  if ( dword_C10CBC )
  {
    v8 = *(gbVec3D *)&g_RoleSlotBuf.m_teamData3[2176 * (_DWORD)dword_C10CC8 + 628];
    (((gbMatrixStack *)pMatrixStack))->gbMatrixStack::Push();
    v8.y = v8.y + 40.0;
    (((gbMatrixStack *)pMatrixStack))->gbMatrixStack::Translate(v8);
    (*(void ( **)(int, _DWORD))(*(_DWORD *)dword_C10CBC + 16))(dword_C10CBC, 0);
    (((gbMatrixStack *)pMatrixStack))->gbMatrixStack::Pop();
  }
}

// 0x0040C790
int ScriptSystem::Cleanup()
{
  int i; // esi
  void ( ***v2)(void *, int); // ecx
  int result; // eax

  for ( i = 0; i < nIndex; ++i )
  {
    v2 = (void ( ***)(void *, int))g_pScriptObjArray[i];
    if ( v2 )
      (**v2)((void *)(v2), (int)(1));
  }
  (((String *)&g_pScriptObjArray))->String::Assign(0, -1);
  return result;
}

// 0x0040C960
void ScriptSystem::Destroy()
{

  PalScript *v2; // esi
  int v3; // [esp+0x0] [ebp-0x4]

  (((UITextArea *)&dword_BFDAB0))->UITextArea::Destroy(v3);
  (((PalScript *)&g_palScript))->PalScript::MoveAndHide();
  this->ScriptSystem::Cleanup();
  v2 = (PalScript *)(&g_RoleSlotBuf.dword_17AA450 + 150);
  do
  {
    (((PalScript *)v2))->PalScript::DestroyScript();
    v2 += 4;
  }
  while ( (int)v2 < (int)&g_RoleSystemArrayEnd );
}

// 0x0040CB80
RoleSystem * ScriptSystem::GetMainRoleSystem(unsigned __int16 pData)
{
  if ( pData == 5 )
    return &g_RoleSystemMain;
  else
    return (RoleSystem *)&g_RoleSlotBuf.m_teamData3[2176 * pData + 588];
}

// 0x0040CBB0
int ScriptSystem::GetScriptContext(unsigned __int16 pData, int nVal)
{
  return g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * pData + 2 + nVal];
}

// 0x0040CBD0
int ScriptSystem::PassThrough(unsigned __int16 pData, int nVal, int nVal2)
{
  int result; // eax

  result = nVal2;
  g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * pData + 2 + nVal] = nVal2;
  return result;
}

// 0x0040CC00
int ScriptSystem::CheckEventType(unsigned __int16 pData, int nVal)
{
  int result; // eax
  _DWORD *v3; // ecx

  if ( pData == 6 )
  {
    result = 0;
    v3 = (_DWORD *)(4 * nVal + 12601196);
    do
    {
      if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + result) )
        *v3 = *(v3 - 12);
      ++result;
      v3 += 352;
    }
    while ( result < 5 );
  }
  else
  {
    result = 4 * (nVal + 352 * pData);
    *(unsigned int *)((char *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2] + result) = *(_DWORD *)((char *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame
                                                                                                  + result);
  }
  return result;
}

// 0x0040CC60
int ScriptSystem::ClearTimerSlot()
{
  int v0; // ecx
  int result; // eax

  result = v0;
  *(_BYTE *)v0 = HIBYTE(v0);
  *(_DWORD *)(v0 + 4) = 0;
  *(_DWORD *)(v0 + 8) = 0;
  *(_DWORD *)(v0 + 12) = 0;
  *(_BYTE *)(v0 + 20) = HIBYTE(v0);
  *(_DWORD *)(v0 + 24) = 0;
  *(_DWORD *)(v0 + 28) = 0;
  *(_DWORD *)(v0 + 32) = 0;
  *(_DWORD *)(v0 + 16) = -1;
  *(_DWORD *)(v0 + 36) = 0;
  return result;
}

// 0x004101F0
int ScriptSystem::RunWithDelay(float delay, int nVal, int nVal2)
{
  scAsmDecoder *v3; // ebx
  scAsmDecoder *v4; // edi
  unsigned int *v5; // esi
  int v6; // ebp
  __int64 v7; // rax
  int result; // eax
  GRPinput *v9; // eax
  GRPinput *v10; // esi
  CScreenMode *Instance; // eax
  const void *v12; // [esp-0x8] [ebp-0x144]
  int v13; // [esp+0x14] [ebp-0x128]
  void *pData[5]; // [esp+0x1C] [ebp-0x120]
  char Buffer[256]; // [esp+0x30] [ebp-0x10C] BYREF
  int v16; // [esp+0x138] [ebp-0x4]

  v3 = dword_C10CC8;
  v4 = 0;
  v13 = 0;
  v5 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2];
  do
  {
    if ( *((_BYTE *)&v4->m_stack + (_DWORD)(&g_RoleSlotBuf.dword_17AA450 + 148)) && (!(_BYTE)nVal2 || v4 == v3) )
    {
      v6 = (unsigned long)*v5;
      v7 = (__int64)((double)(int)*v5 - (double)(int)*(v5 - 12) * delay);
      *v5 = v7;
      if ( (int)v7 <= 0 )
        *v5 = 1;
      if ( v4 == v3 )
        v13 = (unsigned long)(*v5 - v6);
    }
    v5 += 352;
    v4 = (scAsmDecoder *)((char *)v4 + 1);
  }
  while ( (int)v5 < (int)dword_C062EC );
  result = v13;
  if ( v13 < 0 )
  {
    sprintf(Buffer, (const char *)&dir[20], v13);
    v9 = (GRPinput *)operator new(0x24u);
    v16 = 0;
    if ( v9 )
      v10 = (((GRPinput *)v9))->GRPinput::SetMousePos();
    else
      v10 = 0;
    v16 = -1;
    (((GRPinput *)v10))->GRPinput::SetJoystickPos(Buffer, 0);
    (((PtrArray *)&g_pScriptObjArray))->PtrArray::SetAt(nIndex, (int)v10);
    LOBYTE(result) = nVal;
    if ( (_BYTE)nVal )
    {
      pData[0] = "we015";
      pData[1] = "we016";
      pData[2] = "we017";
      pData[3] = "we018";
      pData[4] = "we019";
      v12 = pData[(_DWORD)dword_C10CC8];
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v12, 1);
    }
  }
  return result;
}

// 0x00410470
int ScriptSystem::RunEvent(int eventId, int nVal)
{
  int result; // eax
  scAsmDecoder *v4; // ecx
  int *v5; // eax
  int v6; // eax
  char *v7; // eax
  char Buffer[32]; // [esp+0x8] [ebp-0x20] BYREF
  int v9; // [esp+0x34] [ebp+0xC]

  LOBYTE(result) = nVal;
  if ( !(_BYTE)nVal || (unsigned int)eventId > 4 || g_nCurrentEventId != eventId )
  {
    memset(&g_nScriptEventParam, 0, 0x20u);
    v4 = dword_C10CC8;
    g_nScriptEventParam = v9;
    g_nCurrentEventId = eventId;
    v5 = (int *)&g_RoleSlotBuf.m_teamData3[2176 * (_DWORD)dword_C10CC8 + 589];
    g_nScriptRolePosX = *v5;
    g_nScriptRolePosY = v5[1];
    g_nScriptRolePosZ = v5[2];
    if ( !v9 )
    {
      v6 = 1408 * (_DWORD)dword_C10CC8;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v6 + 4) = 0;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v6 + 5) = 0;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v6 + 6) = 0;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v6 + 7) = 0;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_nCmdParam + v6) = 0;
    }
    result = 5 * (_DWORD)v4;
    if ( !g_RoleSlotBuf.m_partyActor.m_szTexture[1408 * (_DWORD)v4 + 5] && (unsigned int)eventId <= 4 && !v9 )
    {
      sprintf(Buffer, byte_5861F8, eventId);
      v7 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(Buffer);
      InputSystem::ProcessFrame(v7);
      result = (int)dword_C10CC8;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * (_DWORD)dword_C10CC8 + eventId + 4) = 1;
    }
  }
  return result;
}

// 0x00411F60
// positive sp value has been detected, the output may be wrong!
int ScriptSystem::UpdateTimers(float dt)
{
    unsigned long reg_ESI = 0;

  int v1; // ecx
  float v2; // ebx
  int v3; // ebp
  int result; // eax
  int v6; // eax
  double v9; // [esp-0x4] [ebp-0x30]
  float v10; // [esp+0x4] [ebp-0x28]
  int v11; // [esp+0x8] [ebp-0x24]
  int v12; // [esp+0xC] [ebp-0x20]
  int v13; // [esp+0x10] [ebp-0x1C]
  int v14; // [esp+0x14] [ebp-0x18]
  int v15; // [esp+0x18] [ebp-0x14]
  int v16; // [esp+0x1C] [ebp-0x10]
  int v17; // [esp+0x20] [ebp-0xC]
  int v18; // [esp+0x24] [ebp-0x8]
  int v19; // [esp+0x28] [ebp-0x4]

  reg_ESI = v1;
  result = *(_DWORD *)(v1 + 632);
  if ( result )
  {
    if ( *(_DWORD *)(v1 + 144) || *(_DWORD *)(v1 + 1264) == 4 )
      (((Actor *)(v1 + 680)))->Actor::QueryState(SLODWORD(v9));
    switch ( *(_DWORD *)(reg_ESI + 1264) )
    {
      case 0:
        (((RoleSystem *)reg_ESI))->RoleSystem::SetMoveSpeed(0.0, 0, SHIDWORD(v9));
        return result;
      case 1:
        *(float *)&v9 = dt;
        (((RoleSystem *)reg_ESI))->RoleSystem::UpdateMoveSubMode(v9, v10);
        if ( result )
          goto LABEL_23;
        return result;
      case 2:
        (((RoleSystem *)reg_ESI))->RoleSystem::PathFollowUpdate();
        if ( !*(_DWORD *)(reg_ESI + 1268) )
          goto LABEL_16;
        goto LABEL_13;
      case 3:
        if ( *(_DWORD *)(reg_ESI + 1268) == 12 )
        {
LABEL_13:
          *(_DWORD *)(reg_ESI + 1296) = *(_DWORD *)(reg_ESI + 1308);
          *(_DWORD *)(reg_ESI + 1300) = *(_DWORD *)(reg_ESI + 1312);
          *(_DWORD *)(reg_ESI + 1304) = *(_DWORD *)(reg_ESI + 1316);
        }
        else
        {
          (((RoleSystem *)reg_ESI))->RoleSystem::PathFollowUpdate();
          if ( *(_DWORD *)(reg_ESI + 1268) )
          {
            *(_DWORD *)(reg_ESI + 1296) = *(_DWORD *)(reg_ESI + 1308);
            *(_DWORD *)(reg_ESI + 1300) = *(_DWORD *)(reg_ESI + 1312);
            *(_DWORD *)(reg_ESI + 1304) = *(_DWORD *)(reg_ESI + 1316);
          }
        }
LABEL_16:
        v6 = *(_DWORD *)(reg_ESI + 1388);
        if ( v6 && v6 != 4 )
          (((RoleSystem *)reg_ESI))->RoleSystem::ProcessInteraction();
        goto LABEL_23;
      case 4:
        (((RoleSystem *)reg_ESI))->RoleSystem::UpdateActionState(dt);
        if ( result )
          goto LABEL_23;
        return result;
      case 5:
        (((RoleSystem *)reg_ESI))->RoleSystem::UpdateTransform(dt);
        goto LABEL_23;
      case 6:
        (((RoleSystem *)reg_ESI))->RoleSystem::UpdateFollowBehavior(dt);
        goto LABEL_23;
      case 7:
        (((RoleSystem *)reg_ESI))->RoleSystem::UpdateFollowerMovement(dt);
        goto LABEL_23;
      default:
LABEL_23:
        *(_DWORD *)(reg_ESI + 1300) = 0;
        __asm
        {
          fld     dword ptr [esi+0x518]
          fld     dword ptr [esi+0x514]
          fld     dword ptr [esi+0x510]
          fld     st
          fmul    st, st(1)
          fld     st(2)
          fmul    st, st(3)
        }
        __asm
        {
          faddp   st(1), st
          fld     st(3)
          fmul    st, st(4)
          faddp   st(1), st
          fcomp   _flt_0_005
          fstp    st
          fnstsw  ax
          fstp    st
        }
        __asm { fstp    st }
        if ( (_AX & 0x4100) == 0 )
        {
          if ( *(_DWORD *)(reg_ESI + 636) || *(_DWORD *)(reg_ESI + 1264) == 4 )
          {
            (((RoleSystem *)reg_ESI))->RoleSystem::ApplyMoveStep(_pal3_coerce_f64(LODWORD(dt) | 0x100000000i64), v3, v2, SBYTE4(v9));
          }
          else
          {
            v14 = *(_DWORD *)(reg_ESI + 4);
            v15 = *(_DWORD *)(reg_ESI + 8);
            v17 = *(_DWORD *)(reg_ESI + 148);
            v16 = *(_DWORD *)(reg_ESI + 12);
            v18 = *(_DWORD *)(reg_ESI + 152);
            v19 = *(_DWORD *)(reg_ESI + 156);
            v11 = *(_DWORD *)(reg_ESI + 160);
            v12 = *(_DWORD *)(reg_ESI + 164);
            v13 = *(_DWORD *)(reg_ESI + 168);
            (((RoleSystem *)reg_ESI))->RoleSystem::ApplyMoveStep(_pal3_coerce_f64(LODWORD(dt) | 0x100000000i64), v3, v2, SBYTE4(v9));
            __asm
            {
              fld     dword ptr [esi+0x0A4]
              fsub    [esp+0x30+var_1C]
              fabs
              fcomp   _flt_45_0
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              *(_DWORD *)(reg_ESI + 12) = v16;
              *(_DWORD *)(reg_ESI + 4) = v14;
              *(_DWORD *)(reg_ESI + 8) = v15;
              *(_DWORD *)(reg_ESI + 156) = v19;
              *(_DWORD *)(reg_ESI + 148) = v17;
              *(_DWORD *)(reg_ESI + 152) = v18;
              *(_DWORD *)(reg_ESI + 168) = v13;
              *(_DWORD *)(reg_ESI + 160) = v11;
              *(_DWORD *)(reg_ESI + 164) = v12;
              (((RoleSystem *)reg_ESI))->RoleSystem::NotifyMoveComplete();
            }
          }
        }
        result = (*(int ( **)(int))(*(_DWORD *)(reg_ESI + 56) + 4))(reg_ESI + 56);
        if ( !result )
          result = (((RoleSystem *)reg_ESI))->RoleSystem::GetCurrentTile();
        if ( *(_DWORD *)(reg_ESI + 1264) == 3 )
          LOBYTE(result) = (((RoleSystem *)reg_ESI))->RoleSystem::ApproachTarget(-1);
        break;
    }
  }
  return result;
}

// 0x00419090
void ScriptSystem::UpdatePositions()
{
  float *v1; // eax
  float v2; // edx
  float v3; // eax
  float *v4; // eax
  float v5; // st7
  float y; // edx
  float v7; // eax
  float v8; // st7
  gbVec3D *v9; // eax
  float v10; // [esp+0x18] [ebp-0x34]
  float v11; // [esp+0x18] [ebp-0x34]
  float v12; // [esp+0x1C] [ebp-0x30]
  float v13; // [esp+0x1C] [ebp-0x30]
  float v14; // [esp+0x20] [ebp-0x2C]
  float v15; // [esp+0x20] [ebp-0x2C]
  struct gbVec3D v16; // [esp+0x28] [ebp-0x24] BYREF
  gbVec3D v17; // [esp+0x34] [ebp-0x18] BYREF
  gbVec3D v18; // [esp+0x40] [ebp-0xC] BYREF
  gbVec3D *v19; // [esp+0x50] [ebp+0x4]

  memset(&v17, 0, sizeof(v17));
  v14 = flt_C08188 * 20.0f;
  v12 = flt_C08184 * 20.0f;
  v10 = flt_C08180 * 20.0f;
  v16.x = *v1;
  v2 = v1[1];
  v3 = v1[2];
  v19->x = v16.x;
  v16.y = v2;
  v19->y = v2;
  v16.z = v3;
  v19->z = v3;
  v16.x = *v4;
  v5 = v16.x + v19->x;
  v16.y = v4[1];
  y = v16.y;
  v7 = v4[2];
  v17.x = v16.x;
  v19->x = v5;
  v8 = v16.y + v19->y;
  v16.z = v7;
  v17.y = y;
  v17.z = v7;
  v19->y = v8;
  v19->z = v16.z + v19->z;
  v15 = flt_C0817C * -10.0f;
  v13 = flt_C08178 * -10.0f;
  v11 = flt_C08174 * -10.0f;
  v16 = *v9;
  (((gbVec3D *)&v17))->gbVec3D::operator=(*(&v16));
  (((gbVec3D *)v19))->gbVec3D::operator+=(*(&v17));
  v19->x = flt_C08164 + v19->x;
  v19->y = flt_C08168 + v19->y;
  v19->z = flt_C0816C + v19->z;
  v19->y = unk_C08160.m_fPosY + 60.0f;
}

// 0x00419200
int ScriptSystem::SmoothTrackTarget(
        
        float fDeltaTime,
        float fMaxAccel,
        float fVal3,
        float fVal4)
{
  float v6; // st7
  float *p_m_vSrcPos_x; // edi
  float v8; // st6
  float v9; // st7
  float v11; // st6
  float v12; // st7
  float v13; // st7
  float *p_m_vMoveDir_x; // edi
  float v15; // st7
  float v16; // st7
  float *v17; // eax
  float v18; // st7
  float v19; // eax
  char v21; // c0
  float v22; // [esp+0xC] [ebp-0x20]
  float v23; // [esp+0x10] [ebp-0x1C]
  float v24; // [esp+0x14] [ebp-0x18]
  float v25; // [esp+0x18] [ebp-0x14]
  float v26; // [esp+0x18] [ebp-0x14]
  float v27; // [esp+0x18] [ebp-0x14]
  float v28; // [esp+0x1C] [ebp-0x10]
  float v29; // [esp+0x1C] [ebp-0x10]
  float v30; // [esp+0x24] [ebp-0x8]
  float v31; // [esp+0x28] [ebp-0x4]
  _UNKNOWN *retaddr; // [esp+0x2C] [ebp+0x0] BYREF

  if ( fDeltaTime < 0.00050000002f )
    fDeltaTime = 0.0005000000237487257f;
  v6 = this->m_vTargetPos - this->m_vDir_x;
  p_m_vSrcPos_x = (float *)&this->m_vSrcPos_x;
  v25 = this->m_fObjects - this->m_vDir_y;
  v8 = this->m_fTargetDir - this->m_vDir_z;
  this->m_vSrcPos_y = v25;
  v28 = v8;
  this->m_vSrcPos_x = v6;
  this->m_vSrcPos_z = v28;
  v9 = (((gbVec3D *)&this->m_vSrcPos_x))->gbVec3D::Length();
  if ( v9 >= 0.0049999999f )
  {
    v11 = (v9 * 0.01666666753590107f - 0.009999999776482582f) * fMaxAccel;
    if ( fMaxAccel < v11 )
      v11 = fMaxAccel;
    v12 = v11 / v9;
    *p_m_vSrcPos_x = v12 * *p_m_vSrcPos_x;
    this->m_vSrcPos_y = v12 * this->m_vSrcPos_y;
    this->m_vSrcPos_z = v12 * this->m_vSrcPos_z;
    v13 = *p_m_vSrcPos_x - this->m_vSavePos1_x;
    v26 = this->m_vSrcPos_y - this->m_vSavePos1_y;
    p_m_vMoveDir_x = (float *)&this->m_vMoveDir_x;
    v29 = this->m_vSrcPos_z - this->m_vSavePos1_z;
    this->m_vMoveDir_y = v26;
    this->m_vMoveDir_x = v13;
    this->m_vMoveDir_z = v29;
    this->m_vMoveDir_x = this->m_vMoveDir_x / fDeltaTime;
    this->m_vMoveDir_y = this->m_vMoveDir_y / fDeltaTime;
    this->m_vMoveDir_z = this->m_vMoveDir_z / fDeltaTime;
    v15 = (((gbVec3D *)&this->m_vMoveDir_x))->gbVec3D::Length();
    if ( v15 > 470.0f )
    {
      v16 = 470.0f / v15;
      *p_m_vMoveDir_x = v16 * *p_m_vMoveDir_x;
      this->m_vMoveDir_y = v16 * this->m_vMoveDir_y;
      this->m_vMoveDir_z = v16 * this->m_vMoveDir_z;
    }
    v30 = fVal4 * this->m_vMoveDir_y;
    v31 = fVal4 * this->m_vMoveDir_z;
    this->m_vSavePos1_x = fVal4 * *p_m_vMoveDir_x + this->m_vSavePos1_x;
    this->m_vSavePos1_y = v30 + this->m_vSavePos1_y;
    this->m_vSavePos1_z = v31 + this->m_vSavePos1_z;
    this->m_nSaveRot_y = this->m_vDir_x;
    this->m_nSaveRot_z = this->m_vDir_y;
    this->m_nSaveDir = LODWORD(this->m_vDir_z);
    v24 = fVal4 * this->m_vSavePos1_z;
    v23 = fVal4 * this->m_vSavePos1_y;
    v22 = fVal4 * this->m_vSavePos1_x;
    ((gbVec3D *)&retaddr)->gbVec3D::gbVec3D(v22, v23, v24);
    v18 = *v17 + this->m_nSaveRot_y;
    v27 = v17[1];
    v19 = v17[2];
    this->m_nSaveRot_y = v18;
    this->m_nSaveRot_z = v27 + this->m_nSaveRot_z;
    *(float *)&this->m_nSaveDir = v19 + *(float *)&this->m_nSaveDir;
    if ( v21 )
    {
      this->m_nSaveRot_y = this->m_vTargetPos;
      this->m_nSaveRot_z = this->m_fObjects;
      this->m_nSaveDir = LODWORD(this->m_fTargetDir);
    }
    return 1;
  }
  else
  {
    this->m_vDir_x = this->m_vTargetPos;
    this->m_vDir_y = this->m_fObjects;
    this->m_vDir_z = this->m_fTargetDir;
    return 0;
  }
}

// 0x004194C0
int ScriptSystem::UpdateObjects(float dt)
{
  int v1; // ecx
  int v2; // esi
  float *v3; // edi
  float v4; // st7
  float *v5; // eax
  float v6; // edx
  double v7; // st7
  float v8; // eax
  float v9; // st7
  double v10; // st7
  double v11; // st7
  int result; // eax
  float v13; // [esp+0x4] [ebp-0x4C]
  float v14; // [esp+0x8] [ebp-0x48]
  gbVec3D v15; // [esp+0xC] [ebp-0x44] BYREF
  struct gbVec3D v16; // [esp+0x18] [ebp-0x38] BYREF
  gbVec3D v17; // [esp+0x3C] [ebp-0x14] BYREF
  float fDeltaTime; // [esp+0x58] [ebp+0x8]

  v2 = v1;
  (((Actor *)(v1 + 680)))->Actor::QueryState(SLODWORD(v16.x));
  if ( (unsigned int)unk_C08160.m_nCoreState <= 2 && *(_DWORD *)(v2 + 1284) != unk_C08160.m_nCoreState )
  {
    *(_DWORD *)(v2 + 1284) = unk_C08160.m_nCoreState;
    (((RoleSystem *)v2))->RoleSystem::UpdatePath(unk_C08160.m_nCoreState);
  }
  v3 = (float *)(v2 + 1344);
  (((ScriptSystem *)v2))->ScriptSystem::UpdatePositions();
  if ( !(((ScriptSystem *)v2))->ScriptSystem::SmoothTrackTarget(fDeltaTime, 300.0, v16.y, v16.z) )
    goto LABEL_9;
  v16.x = *(float *)(v2 + 1352) - *(float *)(v2 + 168);
  v15.z = *(float *)(v2 + 1348) - *(float *)(v2 + 164);
  v15.y = *v3 - *(float *)(v2 + 160);
  v4 = *(float *)(v2 + 8700) - *(float *)(v2 + 168);
  v16.x = *v5;
  v15.x = v5[1];
  v16.y = v15.x;
  v6 = v5[2];
  v15.x = v4;
  v7 = *(float *)(v2 + 8696) - *(float *)(v2 + 164);
  v16.z = v6;
  v14 = v7;
  v13 = *(float *)(v2 + 8692) - *(float *)(v2 + 160);
  v16 = *v8;
  v9 = (((gbVec3D *)&v15))->gbVec3D::Length();
  v17.y = v9;
  if ( v9 < 0.000049999999
    || (v10 = (((gbVec3D *)&v15))->gbVec3D::DotProduct(&v16), v11 = v10 / v17.x, v11 >= 0.0) && v11 - v17.x > -0.1 )
  {
    *(float *)(v2 + 160) = *v3;
    *(_DWORD *)(v2 + 164) = *(_DWORD *)(v2 + 1348);
    *(_DWORD *)(v2 + 168) = *(_DWORD *)(v2 + 1352);
LABEL_9:
    *(float *)(v2 + 1296) = flt_C08174;
    *(float *)(v2 + 1300) = flt_C08178;
    *(float *)(v2 + 1304) = flt_C0817C;
    (((RoleSystem *)v2))->RoleSystem::UpdatePosition();
    return result;
  }
  *(_DWORD *)(v2 + 160) = *(_DWORD *)(v2 + 8692);
  *(_DWORD *)(v2 + 164) = *(_DWORD *)(v2 + 8696);
  *(_DWORD *)(v2 + 168) = *(_DWORD *)(v2 + 8700);
  (((RoleSystem *)v2))->RoleSystem::UpdatePosition();
  return result;
}

// 0x0041EFA0
void ScriptSystem::Init()
{
  int v1; // edi
  const char *v2; // esi
  int v3; // edi
  const char *v4; // esi
  TxtFile String; // [esp+0x8] [ebp-0x218] BYREF
  int v6; // [esp+0x21C] [ebp-0x4]

  v6 = 0;
  (((PalScript *)&String))->PalScript::LoadFromFile(p0);
  (((PalScript *)&String))->PalScript::SetDirectory("role");
  while ( (((PalScript *)&String))->PalScript::HasNext() )
  {
    if ( !_strcmpi(String.m_token, g_LanguageCode) )
      break;
    v1 = 0;
    v2 = (const char *)(&g_RoleSystemData._todo_118 + 1);
    while ( _strcmpi(String.m_token, v2) )
    {
      v2 += 20;
      ++v1;
      if ( (int)v2 >= (int)&off_58B444 )
        goto LABEL_8;
    }
    (((PalScript *)&String))->PalScript::LoadNext();
    *(&g_RoleSystemData._todo_118 + 5 * v1) = atof(String.m_token);
LABEL_8:
    ;
  }
  (((PalScript *)&String))->PalScript::SetDirectory((char *)&dword_58B440);
  while ( (((PalScript *)&String))->PalScript::HasNext() )
  {
    if ( !_strcmpi(String.m_token, g_LanguageCode) )
      break;
    v3 = 0;
    v4 = (const char *)(&g_RoleSystemData.m_nEffParamBase0 + 1);
    while ( _strcmpi(String.m_token, v4) )
    {
      v4 += 20;
      ++v3;
      if ( (int)v4 >= (int)((const char *)&g_RoleSystemData._todo_118 + 4) )
        goto LABEL_16;
    }
    (((PalScript *)&String))->PalScript::LoadNext();
    *((float *)&g_RoleSystemData.m_nEffParamBase0 + 5 * v3) = atof(String.m_token);
LABEL_16:
    ;
  }
  v6 = -1;
  (((PalScript *)&String))->PalScript::Cleanup();
}
