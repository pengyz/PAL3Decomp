#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Script/ScriptSystem.h"

int * ctor_0x431870(int *_this); // from annotations

// Unnamed globals (extern)
extern int dword_58B260[];
extern char dword_58B440[];
extern std::ios_base dword_BFDAB0;
extern int dword_DC9F3C;
extern float flt_58B378[];
extern const char * off_5861F8;
extern int off_58B444;
extern const char * off_58B448;
extern RoleSystem stru_C059A0;
extern RoleSystem stru_C08160;

// 0x0040C630
void ScriptSystem::Render(gbMatrixStack *pMatrixStack)
{
  int v2; // edx
  int v3; // ebx
  int *p_capacity; // edi
  RenderTarget3 *Instance; // eax
  int m_ptr_4; // edi
  gbRenderEffect *v7; // ecx
  struct gbVec3D v8; // [esp+0xC] [ebp-0x10] BYREF
  int v9; // [esp+0x18] [ebp-0x4]

  v2 = g_nCurrentRoleSlot;
  v3 = 0;
  p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
  do
  {
    if ( v3 != v2 )
    {
      ((RoleSystem *)p_capacity)->RenderRole(pMatrixStack, 0);
      v2 = g_nCurrentRoleSlot;
    }
    p_capacity += 2176;
    ++v3;
  }
  while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
  if ( g_fEffectTimer >= 1.2 )
  {
    ((RoleSystem *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * v2 - 7])->RenderRole(pMatrixStack, 0);
  }
  else if ( rand() % 3 )
  {
    ((RoleSystem *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * g_nCurrentRoleSlot - 7])->RenderRole(pMatrixStack, 0);
  }
  else
  {
    Instance = ((RenderTarget3 *)3)->GetInstance();
    m_ptr_4 = (int)Instance->m_ptr_4;
    if ( m_ptr_4 )
    {
      v7 = Instance->m_ptr_4;
      v8.x = 0.69999999;
      v8.y = 0.1;
      v8.z = 0.1;
      v9 = 1056964608;
      ((gbRenderEffect *)v7)->SetVariant(6, &v8);
      ((RoleSystem *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * g_nCurrentRoleSlot - 7])->RenderRole(pMatrixStack, m_ptr_4);
    }
  }
  ((RoleSystem *)&g_RoleSystemExtra1)->RenderRole(pMatrixStack, 0);
  ((RoleSystem *)&g_RoleSystemExtra0)->RenderRole(pMatrixStack, 0);
  if ( g_pCurrentScript )
  {
    v8 = *(gbVec3D *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * g_nCurrentRoleSlot + 33];
    ((gbMatrixStack *)pMatrixStack)->Push();
    v8.y = v8.y + 40.0;
    ((gbMatrixStack *)pMatrixStack)->Translate(v8);
    (*(void ( **)(PalScript *, _DWORD))(g_pCurrentScript->m_bLoadSceneScript + 16))(g_pCurrentScript, 0);
    ((gbMatrixStack *)pMatrixStack)->Pop();
  }
}

// 0x0040C790
int ScriptSystem::Cleanup()
{
  int i; // esi
  void ( ***v2)(void *, int); // ecx
  int result; // eax

  for ( i = 0; i < (int)g_pScriptEventObj; ++i )
  {
    v2 = (void ( ***)(void *, int))g_pScriptObjArray[i];
    if ( v2 )
      (**v2)(v2, 1);
  }
  ((String *)&g_pScriptObjArray)->Assign(0, -1);
  return result;
}

// 0x0040C960
void ScriptSystem::Destroy()
{

  PalScript *p_capacity; // esi

  ((UITextArea *)dword_BFDAB0)->Destroy();
  ((PalScript *)&g_UIScript)->MoveAndHide();

  p_capacity = (PalScript *)&((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
  do
  {
    ((PalScript *)p_capacity)->DestroyScript();
    p_capacity = (PalScript *)((char *)p_capacity + 8704);
  }
  while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
}

// 0x0040CB80
RoleSystem * ScriptSystem::GetMainRoleSystem(unsigned __int16 pData)
{
  if ( pData == 5 )
    return &g_RoleSystemMain;
  else
    return (RoleSystem *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * pData - 7];
}

// 0x0040CBB0
int ScriptSystem::GetScriptContext(unsigned __int16 pData, int nVal)
{
  return *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * pData + 39 + 4 * nVal];
}

// 0x0040CBD0
int ScriptSystem::PassThrough(unsigned __int16 pData, int nVal, int nVal2)
{
  *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * pData + 39 + 4 * nVal] = nVal2;
  return nVal2;
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
      if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + result) )
        *v3 = *(v3 - 12);
      ++result;
      v3 += 352;
    }
    while ( result < 5 );
  }
  else
  {
    result = 4 * (nVal + 352 * pData);
    *(_DWORD *)&Buffer.m_partyActor.m_curact[result + 39] = *(unsigned int *)((char *)&Buffer.m_partyActor.m_dwMatMsg[9]
                                                                                + result);
  }
  return result;
}

// 0x0040CC60
int ScriptSystem::ClearTimerSlot(int nVal)
{
  *(_BYTE *)nVal = HIBYTE(nVal);
  *(_DWORD *)(nVal + 4) = 0;
  *(_DWORD *)(nVal + 8) = 0;
  *(_DWORD *)(nVal + 12) = 0;
  *(_BYTE *)(nVal + 20) = HIBYTE(nVal);
  *(_DWORD *)(nVal + 24) = 0;
  *(_DWORD *)(nVal + 28) = 0;
  *(_DWORD *)(nVal + 32) = 0;
  *(_DWORD *)(nVal + 16) = -1;
  *(_DWORD *)(nVal + 36) = 0;
  return nVal;
}

// 0x004101F0
int ScriptSystem::RunWithDelay(float delay, int nVal, int nVal2)
{
  int v3; // ebx
  int v4; // edi
  char *v5; // esi
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

  v3 = g_nCurrentRoleSlot;
  v4 = 0;
  v13 = 0;
  v5 = &::Buffer.m_partyActor.m_curact[39];
  do
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v4) && (!(_BYTE)nVal2 || v4 == v3) )
    {
      v6 = *(_DWORD *)v5;
      v7 = (__int64)((double)*(int *)v5 - (double)*((int *)v5 - 12) * delay);
      *(_DWORD *)v5 = v7;
      if ( (int)v7 <= 0 )
        *(_DWORD *)v5 = 1;
      if ( v4 == v3 )
        v13 = *(_DWORD *)v5 - v6;
    }
    v5 += 1408;
    ++v4;
  }
  while ( (int)v5 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[220] );
  result = v13;
  if ( v13 < 0 )
  {
    sprintf(Buffer, &dir[20], v13);
    v9 = (GRPinput *)operator new(0x24u);
    v16 = 0;
    if ( v9 )
      v10 = ((GRPinput *)v9)->SetMousePos();
    else
      v10 = 0;
    v16 = -1;
    ((GRPinput *)v10)->SetJoystickPos(Buffer, 0);
    ((PtrArray *)&g_pScriptObjArray)->SetAt((int)g_pScriptEventObj, (int)v10);
    LOBYTE(result) = nVal;
    if ( (_BYTE)nVal )
    {
      pData[0] = "we015";
      pData[1] = "we016";
      pData[2] = "we017";
      pData[3] = "we018";
      pData[4] = "we019";
      v12 = pData[g_nCurrentRoleSlot];
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v12, 1);
    }
  }
  return result;
}

// 0x00410470
int ScriptSystem::RunEvent(int eventId, int nVal)
{
  int result; // eax
  int v4; // ecx
  int *v5; // eax
  int v6; // eax
  char *v7; // eax
  char Buffer[32]; // [esp+0x8] [ebp-0x20] BYREF
  int v9; // [esp+0x34] [ebp+0xC]

  LOBYTE(result) = nVal;
  if ( !(_BYTE)nVal || (unsigned int)eventId > 4 || g_nCurrentEventId != eventId )
  {
    memset(&g_nScriptEventParam, 0, 0x20u);
    v4 = g_nCurrentRoleSlot;
    g_nScriptEventParam = v9;
    g_nCurrentEventId = eventId;
    v5 = &((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * g_nCurrentRoleSlot - 6];
    g_nScriptRolePosX = *v5;
    g_nScriptRolePosY = v5[1];
    g_nScriptRolePosZ = v5[2];
    if ( !v9 )
    {
      v6 = 1408 * g_nCurrentRoleSlot;
      *(&::Buffer.m_partyActor.m_nActionParam + v6) = 0;
      *(&::Buffer.m_partyActor.m_bActionFlag2 + v6) = 0;
      *(&::Buffer.m_partyActor.m_bActionFlag3 + v6) = 0;
      *(&::Buffer.m_partyActor.m_bActionActive + v6) = 0;
      *((_BYTE *)&::Buffer.m_partyActor.m_nActionState + v6) = 0;
    }
    result = 5 * v4;
    if ( !*((_BYTE *)&::Buffer.m_partyActor.m_nHandleEvent + 1408 * v4 + 1) && (unsigned int)eventId <= 4 && !v9 )
    {
      sprintf(Buffer, (const char *const)&off_5861F8, eventId);
      v7 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(Buffer);
      ((InputSystem *)v7)->ProcessFrame();
      result = g_nCurrentRoleSlot;
      *(&::Buffer.m_partyActor.m_nActionParam + 1408 * g_nCurrentRoleSlot + eventId) = 1;
    }
  }
  return result;
}

// 0x00411F60
int ScriptSystem::UpdateTimers(float dt)
{
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

  _ESI = v1;
  result = *(_DWORD *)(v1 + 632);
  if ( result )
  {
    if ( *(_DWORD *)(v1 + 144) || *(_DWORD *)(v1 + 1264) == 4 )
      ((Actor *)(v1 + 680))->QueryState();
    switch ( *(_DWORD *)(_ESI + 1264) )
    {
      case 0:
        ((RoleSystem *)_ESI)->SetMoveSpeed(0.0, 0, SHIDWORD(v9));
        return result;
      case 1:
        *(float *)&v9 = dt;
        ((RoleSystem *)_ESI)->UpdateMoveSubMode(v9, v10);
        if ( result )
          goto LABEL_23;
        return result;
      case 2:
        ((RoleSystem *)_ESI)->PathFollowUpdate();
        if ( !*(_DWORD *)(_ESI + 1268) )
          goto LABEL_16;
        goto LABEL_13;
      case 3:
        if ( *(_DWORD *)(_ESI + 1268) == 12 )
        {
LABEL_13:
          *(_DWORD *)(_ESI + 1296) = *(_DWORD *)(_ESI + 1308);
          *(_DWORD *)(_ESI + 1300) = *(_DWORD *)(_ESI + 1312);
          *(_DWORD *)(_ESI + 1304) = *(_DWORD *)(_ESI + 1316);
        }
        else
        {
          ((RoleSystem *)_ESI)->PathFollowUpdate();
          if ( *(_DWORD *)(_ESI + 1268) )
          {
            *(_DWORD *)(_ESI + 1296) = *(_DWORD *)(_ESI + 1308);
            *(_DWORD *)(_ESI + 1300) = *(_DWORD *)(_ESI + 1312);
            *(_DWORD *)(_ESI + 1304) = *(_DWORD *)(_ESI + 1316);
          }
        }
LABEL_16:
        v6 = *(_DWORD *)(_ESI + 1388);
        if ( v6 && v6 != 4 )
          ((RoleSystem *)_ESI)->ProcessInteraction();
        goto LABEL_23;
      case 4:
        ((RoleSystem *)_ESI)->UpdateActionState(dt);
        if ( result )
          goto LABEL_23;
        return result;
      case 5:
        ((RoleSystem *)_ESI)->UpdateTransform(dt);
        goto LABEL_23;
      case 6:
        ((RoleSystem *)_ESI)->UpdateFollowBehavior(dt);
        goto LABEL_23;
      case 7:
        ((RoleSystem *)_ESI)->UpdateFollowerMovement(dt);
        goto LABEL_23;
      default:
LABEL_23:
        *(_DWORD *)(_ESI + 1300) = 0;
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
          if ( *(_DWORD *)(_ESI + 636) || *(_DWORD *)(_ESI + 1264) == 4 )
          {
            ((RoleSystem *)_ESI)->ApplyMoveStep(COERCE_DOUBLE(LODWORD(dt) | 0x100000000LL), v3, v2, SBYTE4(v9));
          }
          else
          {
            v14 = *(_DWORD *)(_ESI + 4);
            v15 = *(_DWORD *)(_ESI + 8);
            v17 = *(_DWORD *)(_ESI + 148);
            v16 = *(_DWORD *)(_ESI + 12);
            v18 = *(_DWORD *)(_ESI + 152);
            v19 = *(_DWORD *)(_ESI + 156);
            v11 = *(_DWORD *)(_ESI + 160);
            v12 = *(_DWORD *)(_ESI + 164);
            v13 = *(_DWORD *)(_ESI + 168);
            ((RoleSystem *)_ESI)->ApplyMoveStep(COERCE_DOUBLE(LODWORD(dt) | 0x100000000LL), v3, v2, SBYTE4(v9));
            __asm
            {
              fld     dword ptr [esi+0x0A4]
              fsub    [esp+0x34+var_20]
              fabs
              fcomp   _flt_45_0
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              *(_DWORD *)(_ESI + 12) = v16;
              *(_DWORD *)(_ESI + 4) = v14;
              *(_DWORD *)(_ESI + 8) = v15;
              *(_DWORD *)(_ESI + 156) = v19;
              *(_DWORD *)(_ESI + 148) = v17;
              *(_DWORD *)(_ESI + 152) = v18;
              *(_DWORD *)(_ESI + 168) = v13;
              *(_DWORD *)(_ESI + 160) = v11;
              *(_DWORD *)(_ESI + 164) = v12;
              ((RoleSystem *)_ESI)->NotifyMoveComplete();
            }
          }
        }
        result = (*(int ( **)(int))(*(_DWORD *)(_ESI + 56) + 4))(_ESI + 56);
        if ( !result )
          result = ((RoleSystem *)_ESI)->GetCurrentTile();
        if ( *(_DWORD *)(_ESI + 1264) == 3 )
          LOBYTE(result) = ((RoleSystem *)_ESI)->ApproachTarget(-1);
        break;
    }
  }
  return result;
}

// 0x00419090
void ScriptSystem::UpdatePositions()
{
  gbVec3D *v1; // eax
  float y; // edx
  float z; // eax
  gbVec3D *v4; // eax
  double v5; // st7
  float v6; // edx
  float v7; // eax
  double v8; // st7
  float v9; // [esp+0x18] [ebp-0x34]
  float v10; // [esp+0x18] [ebp-0x34]
  float v11; // [esp+0x1C] [ebp-0x30]
  float v12; // [esp+0x1C] [ebp-0x30]
  float v13; // [esp+0x20] [ebp-0x2C]
  float v14; // [esp+0x20] [ebp-0x2C]
  gbVec3D v15; // [esp+0x28] [ebp-0x24] BYREF
  float x; // [esp+0x34] [ebp-0x18] BYREF
  float v17; // [esp+0x38] [ebp-0x14]
  float v18; // [esp+0x3C] [ebp-0x10]
  gbVec3D v19; // [esp+0x40] [ebp-0xC] BYREF
  float *v20; // [esp+0x50] [ebp+0x4]

  x = 0.0;
  v17 = 0.0;
  v18 = 0.0;
  v13 = *(float *)&((RoleSystem *)&stru_C08160)->m_childs.capacity * 20.0;
  v11 = *(float *)&((RoleSystem *)&stru_C08160)->m_childs.m_pData * 20.0;
  v9 = *(float *)&((RoleSystem *)&stru_C08160)->m_pfather * 20.0;
  // [AUTO-COMMENTED] v1 = ((gbVec3D *)&v19)->gbVec3D(v9, v11, v13);
  v15.x = v1->x;
  y = v1->y;
  z = v1->z;
  *v20 = v15.x;
  v15.y = y;
  v20[1] = y;
  v15.z = z;
  v20[2] = z;
  // [AUTO-COMMENTED] v4 = ((gbVec3D *)&v19)->gbVec3D(0.0, 0.0, 0.0);
  v15.x = v4->x;
  v5 = v15.x + *v20;
  v15.y = v4->y;
  v6 = v15.y;
  v7 = v4->z;
  x = v15.x;
  *v20 = v5;
  v8 = v15.y + v20[1];
  v15.z = v7;
  v17 = v6;
  v18 = v7;
  v20[1] = v8;
  v20[2] = v15.z + v20[2];
  v14 = *(float *)&((RoleSystem *)&stru_C08160)->m_rect.bottom * -10.0;
  v12 = *(float *)&((RoleSystem *)&stru_C08160)->m_rect.right * -10.0;
  v10 = *(float *)&((RoleSystem *)&stru_C08160)->m_rect.top * -10.0;
  // [AUTO-COMMENTED] v15 = *((gbVec3D *)&v19)->gbVec3D(v10, v12, v14);
  ((gbVec3D *)&x)->operator=(&v15);
  ((gbVec3D *)v20)->operator+=(&x);
  *v20 = *(float *)&((RoleSystem *)&stru_C08160)->m_fontcolor.Color + *v20;
  v20[1] = *(float *)&((RoleSystem *)&stru_C08160)->m_wndcolor.Color + v20[1];
  v20[2] = *(float *)&((RoleSystem *)&stru_C08160)->m_id + v20[2];
  v20[1] = ((RoleSystem *)&stru_C08160)->m_fPosY + 60.0;
}

// 0x00419200
int ScriptSystem::SmoothTrackTarget(
        
        float fDeltaTime,
        float fMaxAccel,
        float fVal3,
        float fVal4)
{
  double v6; // st7
  float *p_m_vSrcPos_x; // edi
  double v8; // st6
  double v9; // st7
  double v11; // st6
  double v12; // st7
  double v13; // st7
  float *p_m_vMoveDir_x; // edi
  double v15; // st7
  double v16; // st7
  gbVec3D *v17; // eax
  double v18; // st7
  float z; // eax
  char v21; // c0
  float v22; // [esp+0xC] [ebp-0x20]
  float v23; // [esp+0x10] [ebp-0x1C]
  float v24; // [esp+0x14] [ebp-0x18]
  float v25; // [esp+0x18] [ebp-0x14]
  float v26; // [esp+0x18] [ebp-0x14]
  float y; // [esp+0x18] [ebp-0x14]
  float v28; // [esp+0x1C] [ebp-0x10]
  float v29; // [esp+0x1C] [ebp-0x10]
  float v30; // [esp+0x24] [ebp-0x8]
  float v31; // [esp+0x28] [ebp-0x4]
  _UNKNOWN *retaddr; // [esp+0x2C] [ebp+0x0] BYREF

  if ( fDeltaTime < 0.00050000002 )
    fDeltaTime = 0.00050000002;
  v6 = this->m_vTargetPos - this->m_vDir_x;
  p_m_vSrcPos_x = &this->m_vSrcPos_x;
  v25 = this->m_fObjects - this->m_vDir_y;
  v8 = this->m_fTargetDir - this->m_vDir_z;
  this->m_vSrcPos_y = v25;
  v28 = v8;
  this->m_vSrcPos_x = v6;
  this->m_vSrcPos_z = v28;
  v9 = ((gbVec3D *)&this->m_vSrcPos_x)->Length();
  if ( v9 >= 0.0049999999 )
  {
    v11 = (v9 * 0.016666668 - 0.0099999998) * fMaxAccel;
    if ( fMaxAccel < v11 )
      v11 = fMaxAccel;
    v12 = v11 / v9;
    *p_m_vSrcPos_x = v12 * *p_m_vSrcPos_x;
    this->m_vSrcPos_y = v12 * this->m_vSrcPos_y;
    this->m_vSrcPos_z = v12 * this->m_vSrcPos_z;
    v13 = *p_m_vSrcPos_x - this->m_vSavePos1_x;
    v26 = this->m_vSrcPos_y - this->m_vSavePos1_y;
    p_m_vMoveDir_x = &this->m_vMoveDir_x;
    v29 = this->m_vSrcPos_z - this->m_vSavePos1_z;
    this->m_vMoveDir_y = v26;
    this->m_vMoveDir_x = v13;
    this->m_vMoveDir_z = v29;
    this->m_vMoveDir_x = this->m_vMoveDir_x / fDeltaTime;
    this->m_vMoveDir_y = this->m_vMoveDir_y / fDeltaTime;
    this->m_vMoveDir_z = this->m_vMoveDir_z / fDeltaTime;
    v15 = ((gbVec3D *)&this->m_vMoveDir_x)->Length();
    if ( v15 > 470.0 )
    {
      v16 = 470.0 / v15;
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
    // [AUTO-COMMENTED] v17 = ((gbVec3D *)&retaddr)->gbVec3D(v22, v23, v24);
    v18 = v17->x + this->m_nSaveRot_y;
    y = v17->y;
    z = v17->z;
    this->m_nSaveRot_y = v18;
    this->m_nSaveRot_z = y + this->m_nSaveRot_z;
    *(float *)&this->m_nSaveDir = z + *(float *)&this->m_nSaveDir;
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
  gbVec3D *v4; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  int result; // eax
  float v10; // [esp+0xC] [ebp-0x44]
  float v11; // [esp+0xC] [ebp-0x44]
  float v12; // [esp+0x10] [ebp-0x40]
  float v13; // [esp+0x10] [ebp-0x40]
  float v14; // [esp+0x14] [ebp-0x3C]
  float v15; // [esp+0x14] [ebp-0x3C]
  float v16; // [esp+0x18] [ebp-0x38]
  float v17; // [esp+0x1C] [ebp-0x34]
  gbVec3D v18; // [esp+0x20] [ebp-0x30] BYREF
  struct gbVec3D v19; // [esp+0x2C] [ebp-0x24] BYREF
  gbVec3D v20; // [esp+0x38] [ebp-0x18] BYREF
  gbVec3D v21; // [esp+0x44] [ebp-0xC] BYREF
  float dta; // [esp+0x54] [ebp+0x4]

  v2 = v1;
  ((Actor *)(v1 + 680))->QueryState();
  if ( ((RoleSystem *)&stru_C08160)->m_FrameA.m_childs.m_nSize <= 2u && *(_DWORD *)(v2 + 1284) != ((RoleSystem *)&stru_C08160)->m_FrameA.m_childs.m_nSize )
  {
    *(_DWORD *)(v2 + 1284) = ((RoleSystem *)&stru_C08160)->m_FrameA.m_childs.m_nSize;
    ((RoleSystem *)v2)->UpdatePath(((RoleSystem *)&stru_C08160)->m_FrameA.m_childs.m_nSize);
  }
  v3 = (float *)(v2 + 1344);
  ((ScriptSystem *)v2)->UpdatePositions();
  if ( !((ScriptSystem *)v2)->SmoothTrackTarget(dt, 300.0, v16, v17) )
    goto LABEL_9;
  v14 = *(float *)(v2 + 1352) - *(float *)(v2 + 168);
  v12 = *(float *)(v2 + 1348) - *(float *)(v2 + 164);
  v10 = *v3 - *(float *)(v2 + 160);
  // [AUTO-COMMENTED] v4 = ((gbVec3D *)&v20)->gbVec3D(v10, v12, v14);
  v5 = *(float *)(v2 + 8700) - *(float *)(v2 + 168);
  v18.x = v4->x;
  v18.y = v4->y;
  v15 = v5;
  v6 = *(float *)(v2 + 8696) - *(float *)(v2 + 164);
  v18.z = v4->z;
  v13 = v6;
  v11 = *(float *)(v2 + 8692) - *(float *)(v2 + 160);
  // [AUTO-COMMENTED] v19 = *((gbVec3D *)&v21)->gbVec3D(v11, v13, v15);
  v7 = ((gbVec3D *)&v18)->Length();
  dta = v7;
  if ( v7 < 0.000049999999 || (v8 = ((gbVec3D *)&v18)->DotProduct(&v19) / dta, v8 >= 0.0) && v8 - dta > -0.1 )
  {
    *(float *)(v2 + 160) = *v3;
    *(_DWORD *)(v2 + 164) = *(_DWORD *)(v2 + 1348);
    *(_DWORD *)(v2 + 168) = *(_DWORD *)(v2 + 1352);
LABEL_9:
    *(_DWORD *)(v2 + 1296) = ((RoleSystem *)&stru_C08160)->m_rect.top;
    *(_DWORD *)(v2 + 1300) = ((RoleSystem *)&stru_C08160)->m_rect.right;
    *(_DWORD *)(v2 + 1304) = ((RoleSystem *)&stru_C08160)->m_rect.bottom;
    ((RoleSystem *)v2)->UpdatePosition();
    return result;
  }
  *(_DWORD *)(v2 + 160) = *(_DWORD *)(v2 + 8692);
  *(_DWORD *)(v2 + 164) = *(_DWORD *)(v2 + 8696);
  *(_DWORD *)(v2 + 168) = *(_DWORD *)(v2 + 8700);
  ((RoleSystem *)v2)->UpdatePosition();
  return result;
}

// 0x0041EFA0
void ScriptSystem::Init()
{
  int v1; // edi
  const char *v2; // esi
  int v3; // edi
  const char *v4; // esi
  char String[524]; // [esp+0x8] [ebp-0x218] BYREF
  int v6; // [esp+0x21C] [ebp-0x4]

  ctor_0x431870((int *)g_ScriptSystemData.m_String);
  v6 = 0;
  ((PalScript *)g_ScriptSystemData.m_String)->LoadFromFile("datascript\\scene.txt");
  ((PalScript *)g_ScriptSystemData.m_String)->SetDirectory("role");
  while ( ((PalScript *)g_ScriptSystemData.m_String)->HasNext() )
  {
    if ( !_strcmpi(g_ScriptSystemData.m_String, (const char *)&off_58B448) )
      break;
    v1 = 0;
    v2 = "TalkRange";
    while ( _strcmpi(g_ScriptSystemData.m_String, v2) )
    {
      v2 += 20;
      ++v1;
      if ( (int)v2 >= (int)&off_58B444 )
        goto LABEL_8;
    }
    ((PalScript *)g_ScriptSystemData.m_String)->LoadNext();
    flt_58B378[5 * v1] = atof(g_ScriptSystemData.m_String);
LABEL_8:
    ;
  }
  ((PalScript *)g_ScriptSystemData.m_String)->SetDirectory(dword_58B440);
  while ( ((PalScript *)g_ScriptSystemData.m_String)->HasNext() )
  {
    if ( !_strcmpi(g_ScriptSystemData.m_String, (const char *)&off_58B448) )
      break;
    v3 = 0;
    v4 = "FreeRangeS";
    while ( _strcmpi(g_ScriptSystemData.m_String, v4) )
    {
      v4 += 20;
      ++v3;
      if ( (int)v4 >= (int)"TalkRange" )
        goto LABEL_16;
    }
    ((PalScript *)g_ScriptSystemData.m_String)->LoadNext();
    *(float *)&dword_58B260[5 * v3] = atof(g_ScriptSystemData.m_String);
LABEL_16:
    ;
  }
  v6 = -1;
  ((PalScript *)g_ScriptSystemData.m_String)->Cleanup();
}

// 0x004890A0
char ScriptSystem::ProcessScriptEvent(int nVal, int nVal2, int nParam)
{
  ScriptSystem *v4; // ebp
  int v5; // ebx
  int m_pScriptEvent; // eax
  int v7; // ecx
  int v8; // esi
  char v9; // al
  char v10; // al
  CScreenMode *Instance; // eax
  int v13; // eax
  char *v14; // edi
  int v15; // ecx
  int v16; // ebp
  char *v17; // eax
  int v18; // esi
  char v19; // al
  char *v20; // esi
  int v21; // edi
  int v22; // esi
  _BYTE *p_todo_36D; // eax
  int v24; // ecx
  __int16 *v25; // edx
  char *v26; // esi
  int v27; // edi
  bool v28; // al
  char *v29; // esi
  int v30; // edi
  char v31; // al
  int v32; // edi
  int v33; // ebx
  char *v34; // ebp
  int v35; // esi
  int v36; // eax
  int v37; // esi
  int v38; // ecx
  char *v39; // eax
  int v40; // edx
  int v41; // ecx
  int i; // eax
  ScriptSystem *v43; // ecx
  int v44; // edi
  bool v45; // zf
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // esi
  char *v51; // eax
  int v52; // edx
  int v53; // edx
  int v54; // edi
  ScriptSystem *v55; // esi
  char *v56; // ebx
  char v57; // al
  char *v58; // ebp
  int j; // edi
  int v60; // esi
  int v61; // eax
  int v62; // esi
  char *v63; // eax
  int v64; // edx
  char *v65; // edi
  ScriptSystem *v66; // esi
  int v67; // ecx
  int k; // eax
  float m_vPos_y; // ecx
  ScriptSystem *v70; // ecx
  ScriptSystem *v71; // ecx
  int v72; // esi
  char *v73; // eax
  int v74; // edx
  ScriptSystem *v75; // ebx
  float v76; // ebp
  int v77; // esi
  unsigned __int8 *p_m_bActionActive; // edi
  int v79; // ecx
  __int16 *v80; // edx
  void (***v81)(_DWORD, _DWORD); // esi
  int v82; // edi
  void (***v83)(_DWORD, _DWORD); // esi
  int v84; // edi
  const char *v85; // [esp-0x8] [ebp-0x30]
  ScriptSystem *v87; // [esp+0x14] [ebp-0x14]
  int v88; // [esp+0x18] [ebp-0x10]
  char *v89; // [esp+0x18] [ebp-0x10]
  int v90; // [esp+0x1C] [ebp-0xC]
  int nVala; // [esp+0x2C] [ebp+0x4]
  int nValb; // [esp+0x2C] [ebp+0x4]
  int nVal2a; // [esp+0x30] [ebp+0x8]
  _BYTE *nVal2b; // [esp+0x30] [ebp+0x8]
  ScriptSystem *nVal2c; // [esp+0x30] [ebp+0x8]
v5 = 0;
  if ( nParam < 0 )
    return 0;
  m_pScriptEvent = this->m_pScriptEvent;
  if ( m_pScriptEvent < 0 )
    return 0;
  if ( this->m_nEventParam < 0 )
    return 0;
  v7 = 12 * nParam + 1192 * (8 * nVal + m_pScriptEvent);
  v8 = (int)&this->_todo_5C8 + v7 + 1876;
  v87 = (ScriptSystem *)v8;
  v9 = *(_BYTE *)(*(int *)((char *)&this->_todo_5C8 + v7 + 1884) + 577);
  if ( v9 != 1 && v9 != 2 )
    return 0;
  ((CameraCtrl *)v4)->CalcStatPower(v8);
  if ( !v10 && *(_BYTE *)(*(_DWORD *)(v8 + 8) + 577) == 1 )
  {
    sprintf(this->m_szFmtBuf, "\\n        %s", (const char *)dword_DC9F3C);
    ((UICaption *)(&v4[23]._todo_5C8 + 1485))->SetEnable((int)this->m_szFmtBuf, 0);
    ((UIRoleSelect *)(&v4[23]._todo_5C8 + 1371))->SetByte(1);
    v85 = g_pCScreenMode_5C7768;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v85, 1);
    return 0;
  }
  v13 = *(_DWORD *)(v8 + 8);
  v90 = 1408 * nVal;
  if ( *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nVal + 12] < *(_DWORD *)(v13 + 688)
    || *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nVal + 16] < *(_DWORD *)(v13 + 692) )
  {
    goto LABEL_162;
  }
  if ( *(_DWORD *)(v13 + 696) != 10 )
    goto LABEL_44;
  if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom < *(_DWORD *)(v13 + 704) )
  {
LABEL_162:
    this->m_bExecFlag = 0;
    return 0;
  }
  if ( !*(_BYTE *)(v13 + 700) )
  {
    nVal2a = 0;
    v14 = &Buffer.m_partyActor.m_curact[39];
    v88 = 2 * *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nVal + 4] + 40;
    while ( 1 )
    {
      if ( *(&this->_todo_36D + v5) )
      {
        v15 = *((_DWORD *)v14 - 12) - *(_DWORD *)v14;
        if ( v15 >= v88 )
          v15 = v88;
        v16 = 12;
        *(_DWORD *)v14 += v15;
        v17 = v14;
        do
        {
          v18 = *((_DWORD *)v17 - 12);
          if ( *(_DWORD *)v17 < v18 )
          {
            if ( *(int *)v17 <= 0 )
              *(_DWORD *)v17 = 0;
          }
          else
          {
            *(_DWORD *)v17 = v18;
          }
          v17 += 4;
          --v16;
        }
        while ( v16 );
        nVal2a += v15;
        ((CameraCtrl *)this)->CalcStatPower((int)v87);
        if ( v19 )
          ((CEffect *)this)->UpdateState(v5);
      }
      v14 += 1408;
      ++v5;
      if ( (int)v14 >= (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[220] )
        break;
}
    ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom -= nVal2a;
    sprintf(this->m_szFmtBuf, &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
    ((UICaption *)((char *)this + 55988))->SetEnable((int)this->m_szFmtBuf, 0);
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 43] -= *(_DWORD *)(LODWORD(v87->m_vPos_y) + 688);
    ++HIWORD(v87->m_vPos_x);
    ((MainPropUI *)this)->InitNPCs(nVal, this->m_pScriptEvent, nParam);
    v20 = (char *)this + 217324;
    v21 = 5;
    do
    {
      (**(void ( ***)(char *, _DWORD))v20)(v20, 0);
      v20 += 4892;
      --v21;
    }
    while ( v21 );
    v22 = 0;
    p_todo_36D = &this->_todo_36D;
    nVala = 0;
    nVal2b = &this->_todo_36D;
    do
    {
      if ( *p_todo_36D )
      {
        v24 = 0;
        v25 = (__int16 *)(LODWORD(v87->m_vPos_y) + 592);
        do
        {
          if ( *v25 > 0 )
            nVala += Buffer.m_partyActor.m_dwMatMsg[v22 + 9 + v24]
                   - *(_DWORD *)&Buffer.m_partyActor.m_curact[4 * v22 + 39 + 4 * v24];
          ++v24;
          ++v25;
        }
        while ( v24 < 12 );
      }
      v22 += 352;
      p_todo_36D = ++nVal2b;
    }
    while ( v22 < 1760 );
    if ( nVala <= 0 )
    {
      v26 = (char *)this + 217324;
      this->m_bOpcodeFlag = 0;
      v27 = 5;
      do
      {
        (**(void ( ***)(char *, _DWORD))v26)(v26, 0);
        v26 += 4892;
        --v27;
      }
      while ( v27 );
    }
    v28 = ((CameraCtrl *)this)->HandleCameraEvent(nParam, this->m_pScriptEvent);
    this->m_bOpcodeFlag = v28;
    if ( !v28 )
    {
      this->m_bBlockFlag = 0;
      this->m_bExecFlag = 0;
      ((MainPropUI *)this)->SetPage(1u);
      v29 = (char *)this + 217324;
      v30 = 5;
      do
      {
        (**(void ( ***)(char *, _DWORD))v29)(v29, 0);
        v29 += 4892;
        --v30;
      }
      while ( v30 );
    }
    return 1;
  }
LABEL_44:
  if ( !this->m_bBlockFlag || !this->m_bExecFlag )
    return 0;
  v31 = *(_BYTE *)(v13 + 577);
  if ( v31 == 1 )
  {
    v32 = 592;
    v33 = 1408 * nVal2;
    v34 = &Buffer.m_partyActor.m_curact[1408 * nVal2 + 39];
    do
    {
      v35 = *(__int16 *)(v32 + LODWORD(v87->m_vPos_y));
      v36 = ((MainPropUI *)this)->CalcBarWidth(abs32((__int64)((double)*(int *)&Buffer.m_partyActor.m_szTexture[1408 * nVal + 4]
                            * 0.050000001
                            * (double)v35
                            * 1.5)), 0.1);
      if ( v35 <= 0 )
        v36 = -v36;
      v37 = 12;
      v38 = v36 + *(_DWORD *)v34;
      v39 = &Buffer.m_partyActor.m_curact[v33 + 39];
      *(_DWORD *)v34 = v38;
      do
      {
        v40 = *((_DWORD *)v39 - 12);
        if ( *(_DWORD *)v39 < v40 )
        {
          if ( *(int *)v39 <= 0 )
            *(_DWORD *)v39 = 0;
        }
        else
        {
          *(_DWORD *)v39 = v40;
        }
        v39 += 4;
        --v37;
      }
      while ( v37 );
      v32 += 2;
      v34 += 4;
    }
    while ( v32 < 616 );
    v41 = 0;
    for ( i = 618; i < 680; i += 2 )
    {
      if ( i < 618 || i > 642 )
        *(&Buffer.m_partyActor.m_nActionParam + v33 + v41) = *(_BYTE *)(i + LODWORD(v87->m_vPos_y));
      ++v41;
    }
    v43 = v87;
    if ( *(__int16 *)(LODWORD(v87->m_vPos_y) + 622) < 2 )
    {
      v44 = nVal2;
    }
    else
    {
      v44 = nVal2;
      v45 = nVal2 == g_nCurrentRoleSlot;
      *(&Buffer.m_partyActor.m_bActionFlag3 + 1408 * nVal2) = 0;
      if ( v45 )
        ((ScriptSystem *)v87)->RunEvent(31, 1);
      ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
      v43 = v87;
    }
    if ( *(__int16 *)(LODWORD(v43->m_vPos_y) + 624) >= 2 )
    {
      v46 = g_nCurrentRoleSlot;
      *(&Buffer.m_partyActor.m_bActionActive + 1408 * nVal2) = 0;
      if ( v44 == v46 )
        ((ScriptSystem *)v43)->RunEvent(31, 1);
      ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
      v43 = v87;
    }
    if ( *(__int16 *)(LODWORD(v43->m_vPos_y) + 618) >= 2 )
    {
      v47 = g_nCurrentRoleSlot;
      *(&Buffer.m_partyActor.m_nActionParam + 1408 * nVal2) = 0;
      if ( v44 == v47 )
        ((ScriptSystem *)v43)->RunEvent(31, 1);
      ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
      v43 = v87;
    }
    if ( *(__int16 *)(LODWORD(v43->m_vPos_y) + 620) >= 2 )
    {
      v48 = g_nCurrentRoleSlot;
      *(&Buffer.m_partyActor.m_bActionFlag2 + 1408 * nVal2) = 0;
      if ( v44 == v48 )
        ((ScriptSystem *)v43)->RunEvent(31, 1);
      ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
      v43 = v87;
    }
    if ( *(__int16 *)(LODWORD(v43->m_vPos_y) + 626) >= 2 )
    {
      v49 = g_nCurrentRoleSlot;
      *((_BYTE *)&Buffer.m_partyActor.m_nActionState + 1408 * nVal2) = 0;
      if ( v44 == v49 )
        ((ScriptSystem *)v43)->RunEvent(31, 1);
      ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
      v43 = v87;
    }
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 43] -= *(_DWORD *)(LODWORD(v43->m_vPos_y) + 688);
    v50 = 12;
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 47] -= *(_DWORD *)(LODWORD(v43->m_vPos_y) + 692);
    v51 = &Buffer.m_partyActor.m_curact[v90 + 39];
    do
    {
      v52 = *((_DWORD *)v51 - 12);
      if ( *(_DWORD *)v51 < v52 )
      {
        if ( *(int *)v51 <= 0 )
          *(_DWORD *)v51 = 0;
      }
      else
      {
        *(_DWORD *)v51 = v52;
      }
      v51 += 4;
      --v50;
    }
    while ( v50 );
    v53 = 12 * nParam + 1192 * (8 * nVal + this->m_pScriptEvent);
    ++*(_WORD *)((char *)&this->_todo_5C8 + v53 + 1882);
    ((MainPropUI *)this)->InitNPCs(nVal, this->m_pScriptEvent, nParam);
    ((CEffect *)this)->UpdateState(v44);
  }
  else if ( v31 == 2 )
  {
    v54 = v8;
    v55 = 0;
    v56 = &Buffer.m_partyActor.m_curact[39];
    nVal2c = 0;
    v89 = &Buffer.m_partyActor.m_curact[39];
    do
    {
      if ( *(&this->_todo_36D + (_DWORD)v55) )
      {
        ((CameraCtrl *)v4)->CalcStatPower(v54);
        if ( v57 )
        {
          v58 = v56;
          for ( j = 592; j < 616; j += 2 )
          {
            v60 = *(__int16 *)(j + LODWORD(v87->m_vPos_y));
            v61 = ((MainPropUI *)this)->CalcBarWidth(abs32((__int64)((double)*(int *)&Buffer.m_partyActor.m_szTexture[1408 * nVal + 4]
                                  * 0.050000001
                                  * (double)v60
                                  * 1.5)), 0.1);
            if ( v60 <= 0 )
              v61 = -v61;
            v62 = 12;
            *(_DWORD *)v58 += v61;
            v63 = v89;
            do
            {
              v64 = *((_DWORD *)v63 - 12);
              if ( *(_DWORD *)v63 < v64 )
              {
                if ( *(int *)v63 <= 0 )
                  *(_DWORD *)v63 = 0;
              }
              else
              {
                *(_DWORD *)v63 = v64;
              }
              v63 += 4;
              --v62;
            }
            while ( v62 );
            v58 += 4;
          }
          v65 = v89;
          v66 = v87;
          v67 = 0;
          for ( k = 618; k < 680; k += 2 )
          {
            if ( k < 618 || k > 642 )
              v89[v67 - 288] = *(_BYTE *)(k + LODWORD(v87->m_vPos_y));
            ++v67;
          }
          if ( *(__int16 *)(LODWORD(v87->m_vPos_y) + 622) >= 2 )
          {
            v45 = nVal2c == (ScriptSystem *)g_nCurrentRoleSlot;
            *(v89 - 286) = 0;
            if ( v45 )
              ((ScriptSystem *)nVal2c)->RunEvent(31, 1);
            ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
            v65 = v89;
            v66 = v87;
          }
          m_vPos_y = v66->m_vPos_y;
          if ( *(__int16 *)(LODWORD(m_vPos_y) + 624) >= 2 )
          {
            v45 = nVal2c == (ScriptSystem *)g_nCurrentRoleSlot;
            *(v65 - 285) = 0;
            if ( v45 )
              ((ScriptSystem *)LODWORD(m_vPos_y))->RunEvent(31, 1);
            ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
            v65 = v89;
            v66 = v87;
          }
          if ( *(__int16 *)(LODWORD(v66->m_vPos_y) + 618) >= 2 )
          {
            v70 = (ScriptSystem *)g_nCurrentRoleSlot;
            v45 = nVal2c == (ScriptSystem *)g_nCurrentRoleSlot;
            *(v65 - 288) = 0;
            if ( v45 )
              ((ScriptSystem *)v70)->RunEvent(31, 1);
            ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
            v65 = v89;
            v66 = v87;
          }
          if ( *(__int16 *)(LODWORD(v66->m_vPos_y) + 620) >= 2 )
          {
            v45 = nVal2c == (ScriptSystem *)g_nCurrentRoleSlot;
            *(v65 - 287) = 0;
            if ( v45 )
              ((ScriptSystem *)nVal2c)->RunEvent(31, 1);
            ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
            v66 = v87;
          }
          if ( *(__int16 *)(LODWORD(v66->m_vPos_y) + 626) >= 2 )
          {
            v71 = (ScriptSystem *)g_nCurrentRoleSlot;
            v45 = nVal2c == (ScriptSystem *)g_nCurrentRoleSlot;
            *(v89 - 284) = 0;
            if ( v45 )
              ((ScriptSystem *)v71)->RunEvent(31, 1);
            ((Comp_DonateUI *)*((Comp_DonateUI **)this + 12758))->ProcessInput();
          }
          ((CEffect *)this)->UpdateState((int)nVal2c);
          v54 = (int)v87;
v56 = v89;
          v55 = nVal2c;
        }
      }
      v56 += 1408;
      v55 = (ScriptSystem *)((char *)v55 + 1);
      nVal2c = v55;
      v89 = v56;
    }
    while ( (int)v56 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[220] );
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 43] -= *(_DWORD *)(*(_DWORD *)(v54 + 8) + 688);
    v72 = 12;
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 47] -= *(_DWORD *)(*(_DWORD *)(v54 + 8) + 692);
    v73 = &Buffer.m_partyActor.m_curact[v90 + 39];
    do
    {
      v74 = *((_DWORD *)v73 - 12);
      if ( *(_DWORD *)v73 < v74 )
      {
        if ( *(int *)v73 <= 0 )
          *(_DWORD *)v73 = 0;
      }
      else
      {
        *(_DWORD *)v73 = v74;
      }
      v73 += 4;
      --v72;
    }
    while ( v72 );
    ++*(_WORD *)(v54 + 6);
    ((MainPropUI *)v4)->InitNPCs(nVal, this->m_pScriptEvent, nParam);
  }
  v75 = this;
  ((UIBigMap *)this)->UpdateElement((int)v87, nVal);
  v76 = v87->m_vPos_y;
  v77 = 0;
  nValb = 0;
  p_m_bActionActive = &Buffer.m_partyActor.m_bActionActive;
  do
  {
    v79 = 0;
    v80 = (__int16 *)(LODWORD(v76) + 592);
    do
    {
      if ( *v80 > 0 )
      {
        v77 += Buffer.m_partyActor.m_dwMatMsg[v79 + 9 + nValb]
             - *(_DWORD *)&Buffer.m_partyActor.m_curact[4 * v79 + 39 + 4 * nValb];
        v75 = this;
      }
      ++v79;
      ++v80;
    }
    while ( v79 < 12 );
    if ( *(_WORD *)(LODWORD(v76) + 622) )
      v77 += *(p_m_bActionActive - 1);
    if ( *(_WORD *)(LODWORD(v76) + 624) )
      v77 += *p_m_bActionActive;
    if ( *(_WORD *)(LODWORD(v76) + 618) )
      v77 += *(p_m_bActionActive - 3);
    if ( *(_WORD *)(LODWORD(v76) + 620) )
      v77 += *(p_m_bActionActive - 2);
    if ( *(_WORD *)(LODWORD(v76) + 626) )
      v77 += p_m_bActionActive[1];
    p_m_bActionActive += 1408;
    nValb += 352;
  }
  while ( (int)p_m_bActionActive < (int)((unsigned __int8 *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[148] + 3) );
  if ( v77 <= 0 )
  {
    v75->m_bOpcodeFlag = 0;
    v81 = (void ( ***)(_DWORD, _DWORD))(&v75[24]._todo_5C8 + 1737);
    v82 = 5;
    do
    {
      (**v81)(v81, 0);
      v81 += 1223;
      --v82;
    }
    while ( v82 );
  }
  if ( !v75->m_bOpcodeFlag || !((CameraCtrl *)v75)->HandleCameraEvent(nParam, v75->m_pScriptEvent) )
  {
    v75->m_bOpcodeFlag = 0;
    v75->m_bBlockFlag = 0;
    v75->m_bExecFlag = 0;
    ((MainPropUI *)v75)->SetPage(1u);
    v83 = (void ( ***)(_DWORD, _DWORD))(&v75[24]._todo_5C8 + 1737);
    v84 = 5;
    do
    {
      (**v83)(v83, 0);
      v83 += 1223;
      --v84;
    }
    while ( v84 );
  }
  return 1;
}
