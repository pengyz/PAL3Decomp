#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Script/PalScriptMgr.h"

// Forward declarations for unnamed functions
void FightInfo(void); // from annotations
void * GetSaveDataManager(void); // from annotations
int UISceneUpdate(void); // from annotations
int sub_445DB0(void *a2); // from annotations
int sub_445FA0(void *a2); // from annotations
int todo_024(...);
int todo_058(...);

void FreeScriptInstance(int *pInstance); // from annotations
BOOL PointInRect(int *pRect, int *pPoint); // from annotations

// Unnamed globals (extern)
extern char byte_DBA25C;
extern int dword_D8BC38;
extern float flt_D8BEC4;
extern float flt_D8C17C;
extern RoleSystem stru_C059A0;
extern GRPinput stru_D8C2B8;
extern RoleCameraCtrl stru_DBA134;
extern int unknown_libname_343;
extern int unknown_libname_344;

// 0x004100A0
int PalScriptMgr::RunScript(int nVal, int nVal2, int nVal3)
{
  int result; // eax
  char *v4; // edx
  int v5; // edi
  int v6; // ebx
  int v7; // esi
  int v8; // ecx
  int v9; // eax
  GRPinput *v10; // eax
  GRPinput *v11; // esi
  CScreenMode *Instance; // eax
  const void *v13; // [esp-0x8] [ebp-0x13C]
  void *pData[6]; // [esp+0x10] [ebp-0x124]
  char Buffer[256]; // [esp+0x28] [ebp-0x10C] BYREF
  int v16; // [esp+0x130] [ebp-0x4]

  v4 = &::Buffer.m_partyActor.m_curact[39];
  v5 = g_nCurrentRoleSlot;
  v6 = 0;
  v7 = 0;
  do
  {
    LOBYTE(result) = *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v7);
    if ( (_BYTE)result )
    {
      LOBYTE(result) = nVal3;
      if ( !(_BYTE)nVal3 || v7 == v5 )
      {
        v8 = *(_DWORD *)v4;
        v9 = *(_DWORD *)v4 - nVal;
        if ( v9 < 1 )
          v9 = 1;
        *(_DWORD *)v4 = v9;
        result = v9 - v8;
        if ( v7 == v5 )
          v6 = result;
      }
    }
    v4 += 1408;
    ++v7;
  }
  while ( (int)v4 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[220] );
  if ( v6 < 0 )
  {
    sprintf(Buffer, &dir[20], v6);
    v10 = (GRPinput *)operator new(0x24u);
    pData[5] = v10;
    v16 = 0;
    if ( v10 )
      v11 = ((GRPinput *)v10)->SetMousePos();
    else
      v11 = 0;
    v16 = -1;
    ((GRPinput *)v11)->SetJoystickPos(Buffer, 0);
    ((PtrArray *)&g_pScriptObjArray)->SetAt((int)g_pScriptEventObj, (int)v11);
    LOBYTE(result) = nVal2;
    if ( (_BYTE)nVal2 )
    {
      pData[0] = "we015";
      pData[1] = "we016";
      pData[2] = "we017";
      pData[3] = "we018";
      pData[4] = "we019";
      v13 = pData[g_nCurrentRoleSlot];
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v13, 1);
    }
  }
  return result;
}

// 0x00410920
int * PalScriptMgr::LoadYlfScript()
{
  const char *v1; // eax

  int *result; // eax
  char Buffer[128]; // [esp+0x0] [ebp-0x80] BYREF

  v1 = (const char *)UISceneUpdate();
  sprintf(Buffer, "_ylf_%s_%s", v1, v1 + 32);
  ((PtrArray *)Buffer)->IsArrayReady();

  return result;
}

// 0x0041BDE0
int * PalScriptMgr::Get_result()
{
  *(_DWORD *)&this->m_bGetSceneScript = 0;
  this->m_script.m_pData = 0;
  this->m_script.capacity = 0;
  this->m_script.m_nSize = 0;
  return (int *)this;
}

// 0x00420B40
void PalScriptMgr::CheckTileScript(RoleSystem *pRole, float fVal, char bExecute)
{
  int v5; // esi
  __int64 v6; // rax
  unsigned __int8 Tile; // bl
  char *v8; // eax
  char *v9; // eax
  char v10; // al
  int nX; // [esp+0xC] [ebp-0x8]

  if ( pRole )
  {
    v5 = *(_DWORD *)pRole->m_partyActor.m_szTexture;
    nX = (__int64)((*(float *)((char *)&pRole[1].m_partyUI3._todo_05C + 79) - *((float *)this + 41 * v5 + 123226))
                 / g_fTileScale);
    v6 = (__int64)((*(float *)((char *)&pRole[1].m_partyUI3._todo_05C + 87) - *((float *)this + 41 * v5 + 123228))
                 / g_fTileScale);
    if ( nX < 0
      || nX >= *((_DWORD *)this + 41 * v5 + 123232)
      || (int)v6 < 0
      || (int)v6 >= *((_DWORD *)this + 41 * v5 + 123233) )
    {
      Tile = -1;
    }
    else
    {
      Tile = ((RoleSystem *)(&this->m_RoleAnimData + 5 * v5 + 1))->GetTile(nX, v6);
    }
    if ( bExecute )
    {
      if ( Tile != 0xFF )
      {
        v8 = &this->m_bGetSceneScript + 896 * Tile;
        if ( v8[397] )
        {
          if ( v8[468] == 38 )
            ((PalScriptMgr *)(v8 + 224))->ExecuteBlock();
        }
      }
    }
    else
    {
      if ( Tile != 0xFF )
      {
        v9 = &this->m_bGetSceneScript + 896 * Tile;
        if ( v9[397] )
        {
          ((PalScriptMgr *)(v9 + 224))->ExecuteBlock();
          ((RoleSystem *)pRole)->GetActiveRole();
        }
      }
      v10 = *((_BYTE *)this + 493148);
      if ( v10 != Tile && v10 != -1 )
        ((PalScriptMgr *)(&this->m_fAngle + 224 * *((unsigned __int8 *)this + 493148)))->GetScriptState();
      *((_BYTE *)this + 493148) = Tile;
    }
  }
}

// 0x00424C20
void PalScriptMgr::ExecuteBlock()
{
  char m_bExecuteBlock; // al
  int v3; // eax
  char *v4; // eax
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
  int todo_058; // eax
  gbVec3D *p_m_fField44; // ecx
  float v30; // edx
  char m_bBigMapState; // dl
  int m_nBlockHandle; // eax
  CScreenMode *v37; // ecx
  char v38; // al
  PtrArray *v39; // eax
  float m_fCamZ; // eax
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
  float v66; // edx
  int v68; // ebp
  float v72; // eax
  scSCEFile *v73; // ecx
  char v83; // al
  char *v84; // eax
  int *p_m_nFrameCounter; // edi
  float v90; // ecx
  PtrArray *v92; // eax
  int v93; // eax

  char *v95; // eax
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

  int v113; // eax
  char *v114; // eax
  PtrArray *v115; // eax
  int v116; // ecx
  char v117; // al
  float v118; // edx
  float v120; // eax
  float y; // ecx
  float v122; // edx
  PtrArray *v123; // eax
  char *v125; // eax
  float v129; // eax
  float v130; // ecx
  float v131; // edx
  CScreenMode *v134; // ecx
  PtrArray *v136; // eax
  bool v137; // al
  float v140; // ecx
  float v142; // eax
  char v144; // al
  char v145; // al
  CScreenMode *v146; // ecx
  PtrArray *v147; // eax
  CScreenMode *v148; // ecx
  PtrArray *v149; // eax
  __int64 v153; // rax
  int v154; // ecx
  int v155; // ecx
  int v156; // eax
  int v157; // edx
  float v160; // edx
  float v161; // eax
  float v163; // edi
  float v164; // ebx
  RoleSystem *m_pSceneMgr; // ecx
  int v167; // ecx
  RoleSystem *v170; // edx
  int x_low; // edi
  float v172; // ecx
  float v175; // ecx
  PtrArray *v178; // eax
  char *v179; // eax
  int m_nCmdValue; // [esp-0x4] [ebp-0x114]
  float nType; // [esp+0x0] [ebp-0x110]
  int nTypea; // [esp+0x0] [ebp-0x110]
  int fVal; // [esp+0x4] [ebp-0x10C]
  float fVala; // [esp+0x4] [ebp-0x10C]
  int m_pClearResult; // [esp+0x8] [ebp-0x108]
  int v186; // [esp+0x8] [ebp-0x108]
  unsigned __int8 v187; // [esp+0xC] [ebp-0x104]
  unsigned __int8 v188; // [esp+0xC] [ebp-0x104]
  unsigned __int8 v189; // [esp+0xC] [ebp-0x104]
  gbVec3D pfVal2; // [esp+0x1C] [ebp-F4h] BYREF
  gbVec3D pParams; // [esp+0x28] [ebp-E8h] BYREF
  gbVec3D nSceneIdx; // [esp+0x34] [ebp-DCh] BYREF
  gbVec3D v193; // [esp+0x40] [ebp-D0h] BYREF
  gbVec3D v194; // [esp+0x4C] [ebp-C4h] BYREF
  int v195; // [esp+0x58] [ebp-B8h]
  int v196; // [esp+0x5C] [ebp-B4h]
  float pData[3]; // [esp+0x60] [ebp-B0h] BYREF
  float v198[3]; // [esp+0x6C] [ebp-A4h] BYREF
  gbMatrix4 v199; // [esp+0x78] [ebp-0x98] BYREF
  gbMatrix4 pMatrix; // [esp+C4h] [ebp-0x4C] BYREF
  RoleSystem *v206; // [esp+0x114] [ebp+0x4]
  char v207; // [esp+0x118] [ebp+0x8]
  int v208; // [esp+0x11C] [ebp+0xC]
m_bExecuteBlock = this->m_bExecuteBlock;
  if ( !m_bExecuteBlock )
    return;
  switch ( this->m_nCmdType )
  {
    case 0:
      if ( !v208 )
      {
        ((PalScriptMgr *)this->m_pClearResult)->ClearAllScript();
        if ( !v3 )
        {
          ((PalScriptMgr *)this->m_pScriptObj)->Destroy();
          this->m_pClearResult = v4;
          ((RoleSystem *)&g_pRoleSystem)->Notify();
          m_pClearResult = (int)this->m_pClearResult;
          SoundList = ((CScreenMode *)v5)->GetSoundList();
          ((PtrArray *)SoundList)->SetResolution(0, m_pClearResult);
          ((PalScriptMgr *)_ESI)->ExecuteScriptByID();
          goto LABEL_99;
        }
      }
      return;
    case 1:
      if ( !v208 )
      {
        if ( this->m_bBigMapState )
          goto LABEL_254;
        ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(1.0);
        (*(void (**)(char *, _DWORD))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, 0);
        this->m_bBigMapState = 4;
        goto LABEL_55;
      }
      return;
    case 2:
      if ( !v208 )
      {
        if ( this->m_bBigMapState )
          goto LABEL_254;
        ((gbGeomNode *)this->m_pExecSystem)->SetAnimLoop(1);
        ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(1.0);
        (*(void (**)(char *, _DWORD))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, 0);
        goto LABEL_54;
      }
      return;
    case 3:
      if ( this->m_bBigMapState )
        goto LABEL_254;
      __asm
      {
        fld     g_fEffectTimer
        fcomp   _flt_1_2
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0 )
      {
        this->m_bBigMapState = 1;
        this->m_nFrameCounter = this->m_nExecuteBlock;
        LODWORD(this->m_fField3C) = this->m_nSavedDataA;
        this->m_pBigMapSce = (scSCEFile *)this->m_nSavedDataB;
        __asm
        {
          fld     dword ptr [esi+0x0E0]
          fmul    _flt_0_01745329f
        }
        this->m_fPosZ = 0.0;
        __asm
        {
          fst     [esp+0x108+var_D0]
          fsin
          fld     [esp+0x108+var_D0]
          fcos
          fstp    [esp+0x108+var_BC]
        }
        z = v194.z;
        // __asm { fstp    dword ptr [esi+0x44] }
        this->m_fField44 = _ET1;
        *(float *)&this->m_scepath = z;
        __asm
        {
          fld     dword ptr [esi+0x44]
          fmul    _flt_280_0
          fstp    dword ptr [esi+0x44]
        }
        this->m_fField44 = _ET1;
        __asm
        {
          fld     dword ptr [esi+0x48]
          fmul    _flt_280_0
          fstp    dword ptr [esi+0x48]
        }
        this->m_fPosZ = _ET1;
        __asm
        {
          fld     dword ptr [esi+0x4C]
          fmul    _flt_280_0
          fstp    dword ptr [esi+0x4C]
        }
        *(float *)&this->m_scepath = _ET1;
        this->_todo_054 = 0;
        ((PalScriptMgr *)_ESI)->RunCommand();
        goto LABEL_55;
      }
      return;
    case 4:
      if ( this->m_bBigMapState )
        goto LABEL_254;
      __asm
      {
        fld     g_fEffectTimer
        fcomp   _flt_1_2
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0 )
      {
        this->m_bBigMapState = 1;
        this->m_nFrameCounter = this->m_nExecuteBlock;
        LODWORD(this->m_fField3C) = this->m_nSavedDataA;
        this->m_pBigMapSce = (scSCEFile *)this->m_nSavedDataB;
        RolePtr = ((RoleSystem *)this->m_pSceneMgr->m_rect.left)->GetRolePtr((unsigned __int8)this->m_bExecuteOpcode);
        // __asm { fld     dword ptr [esi+0x38] }
        _EDI = (_DWORD *)RolePtr;
        __asm
        {
          fsub    dword ptr [edi+0x80]
          fdiv    g_ScriptSystemData
        }
        LODWORD(v16) = _ftol();
        __asm
        {
          fld     dword ptr [esi+0x40]
          fsub    dword ptr [edi+0x88]
        }
        v17 = LODWORD(v16);
        nSceneIdx.x = v16;
        __asm { fdiv    g_ScriptSystemData }
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
          fmul    g_ScriptSystemData
          fadd    dword ptr [edi+0x80]
          fstp    [esp+0x104+pParams]
          fild    [esp+0x104+var_D8]
          fadd    _flt_0_5
          fmul    g_ScriptSystemData
          fadd    dword ptr [edi+0x88]
          fstp    [esp+0x104+var_E0]
        }
        if ( v17 >= 0 )
        {
          v19 = _EDI[38];
          if ( v17 < v19 && v18 >= 0.0 && SLODWORD(v18) < _EDI[39] )
          {
            __asm { fstp    st }
            _EDX = _EDI[40];
            _ECX = v17 + LODWORD(v18) * v19;
            __asm { fld     dword ptr [edx+ecx*8] }
          }
        }
        x = pParams.x;
        v23 = pParams.z;
        // __asm { fstp    dword ptr [esi+0x3C] }
        this->m_fField3C = _ET1;
        *(float *)&this->m_nFrameCounter = x;
        *(float *)&this->m_pBigMapSce = v23;
        __asm
        {
          fld     dword ptr [esi+0x3C]
          fsub    _flt_10_0
          fstp    dword ptr [esi+0x3C]
        }
        this->m_fField3C = _ET1;
        LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
        LODWORD(this->m_fCamY) = this->m_nSavedDataA;
        LODWORD(this->m_fCamZ) = this->m_nSavedDataB;
        this->m_fField44 = 0.0;
        this->m_fPosZ = 280.0;
        this->m_scepath = 0;
        todo_058 = this->_todo_058;
        this->_todo_054 = 0;
        if ( todo_058 == 3 )
        {
          ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(0.0);
          (*(void (**)(char *, _DWORD))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, 0);
        }
        ((PalScriptMgr *)_ESI)->RunCommand();
        goto LABEL_55;
      }
      return;
    case 5:
      if ( this->m_nCmdValue == 1 )
      {
        if ( !v207 && ((ScriptVM *)this)->IsRunning() )
        {
          _EAX = g_pRoleSystem;
          _EDI = &this->m_fCamX;
          p_m_fField44 = (gbVec3D *)&this->m_fField44;
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
          this->m_fPosZ = pParams.y;
          // __asm { fstp    [esp+0x104+var_E0] }
          v30 = pParams.z;
          __asm { fstp    dword ptr [ecx] }
          p_m_fField44->x = _ET1;
          *(float *)&this->m_scepath = v30;
          __asm
          {
            fld     dword ptr [esi+0x48]
            fcomp   _flt_40_0
            fnstsw  ax
          }
          if ( (BYTE1(_EAX) & 0x41) != 0 )
          {
            this->m_fPosZ = 0.0;
            ((gbVec3D *)p_m_fField44)->Normalize();
            ((ScriptVM *)_ESI)->GetRolePosition(1u);
            FightInfo();
            ((ScriptVM *)_ESI)->CallFunction(0xBu, 0);
            goto LABEL_247;
          }
          p_m_fField44->x = 0.0;
          this->m_fPosZ = 0.0;
          this->m_scepath = 0;
        }
      }
      else
      {
        if ( !this->m_bScriptPause )
          goto LABEL_254;
        m_bBigMapState = this->m_bBigMapState;
        if ( m_bBigMapState )
        {
          if ( m_bBigMapState != 3 )
            goto LABEL_254;
        }
        _EDI = g_pRoleSystem;
        _ECX = &this->m_fCamX;
        __asm
        {
          fld     dword ptr [ecx+4]
          fsub    dword ptr [edi+0x0A4]
          fcomp   _flt_40_0
          fnstsw  ax
        }
        if ( (_AX & 0x4100) != 0 )
        {
          if ( m_bBigMapState )
          {
            m_nBlockHandle = this->m_nBlockHandle;
            this->m_nExecState = 2;
            this->m_nFrameCounter = *(_DWORD *)(m_nBlockHandle + 3076);
          }
          else
          {
            this->m_nExecState = 1;
            this->m_nFrameCounter = 0;
          }
          this->m_nSavedPosX = 1;
          this->m_bBigMapState = 4;
          ((RoleSystem *)_EDI)->SetMoveTarget(&this->m_fCamX, 1);
          ((RoleSystem *)_EDI)->GetMoveState();
          v38 = this->m_bExecuteBlock;
          if ( v38 != -1 )
          {
            this->m_bExecuteBlock = v38 - 1;
            v39 = ((CScreenMode *)v37)->GetSoundList();
            ((PtrArray *)v39)->SetResolution((int)_ESI, 0);
            goto LABEL_254;
          }
          goto LABEL_248;
        }
      }
      return;
    case 6:
      if ( !this->m_bBigMapState )
      {
        pfVal2.x = this->m_fCamX;
        // __asm { fld     [esp+0x104+pfVal2] }
        m_fCamZ = this->m_fCamZ;
        pfVal2.y = this->m_fCamY;
        pfVal2.z = m_fCamZ;
        _EAX = v206;
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
        ((gbVec3D *)&pfVal2)->Length();
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
          g_pRoleSystem->m_FrameA.m_childs.m_nSize = 0;
          ((RoleSystem *)v44)->UpdateTransform();
          this->m_bBigMapState = 1;
          this->m_fField44 = 0.0;
          this->m_fPosZ = 0.0;
          this->m_scepath = 0;
          this->m_nFrameCounter = LODWORD(v43->m_fPosX);
          this->m_fField3C = v43->m_fPosY;
          this->m_pBigMapSce = (scSCEFile *)LODWORD(v43->m_fPosZ);
          ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(2.0);
          (*(void (**)(char *, _DWORD))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, 0);
          v46 = this->m_bExecuteBlock;
          if ( v46 != -1 )
            this->m_bExecuteBlock = v46 - 1;
          v47 = ((CScreenMode *)v45)->GetSoundList();
          ((PtrArray *)v47)->SetResolution((int)_ESI, 0);
          ((PalScriptMgr *)_ESI)->RunCommand();
        }
      }
      return;
    case 7:
    case 8:
      if ( v207 == 2 && !this->m_bBigMapState )
      {
        __asm
        {
          fld     dword ptr [esi+0x0E0]
          fadd    _flt_90_0
        }
        this->m_bBigMapState = 1;
        // __asm { fstp    dword ptr [esi+0x38] }
        this->m_nFrameCounter = _ET1;
        v49 = g_pRoleSystem;
        g_pRoleSystem->m_FrameA.m_childs.m_nSize = 0;
        ((RoleSystem *)v49)->UpdateTransform();
        ((RoleSystem *)_ESI)->ProcessAction();
        ((PalScriptMgr *)_ESI)->RunCommand();
        v50 = this->m_bExecuteBlock;
        if ( v50 != -1 )
          this->m_bExecuteBlock = v50 - 1;
        v51 = (CScreenMode *)g_pCameraCtrl;
        if ( !*((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
          goto LABEL_89;
        ((CameraCtrl *)&g_pCameraCtrl)->InitParams(&this->m_fCamX);
        v53 = ((CScreenMode *)v52)->GetSoundList();
        ((PtrArray *)v53)->SetResolution((int)_ESI, 0);
      }
      return;
    case 9:
      if ( this->m_bBigMapState )
        goto LABEL_254;
      pfVal2.x = this->m_fCamX;
      // __asm { fld     [esp+0x104+pfVal2] }
      pfVal2.y = this->m_fCamY;
      _EAX = v206;
      __asm { fsub    dword ptr [eax+4] }
      pfVal2.z = this->m_fCamZ;
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
      ((gbVec3D *)&pfVal2)->Length();
      __asm
      {
        fld     _flt_12_0
        fmul    _flt_0_5
        fcompp
        fnstsw  ax
      }
      if ( (_AX & 0x4100) == 0 )
      {
        ((PalScriptMgr *)_ESI)->ExecuteScriptByID();
LABEL_54:
        this->m_bBigMapState = 1;
LABEL_55:
        m_bExecuteBlock = this->m_bExecuteBlock;
        goto LABEL_56;
      }
      return;
    case 0xA:
      if ( !this->m_bBigMapState )
      {
        __asm
        {
          fld     dword ptr [esi+0x140]
          fsub    dword ptr [esi+0x134]
          fld     dword ptr [esi+0x144]
          fsub    dword ptr [esi+0x138]
        }
        _EDI = &this->m_fField44;
        __asm
        {
          fstp    [esp+0x104+var_E4]
          fld     dword ptr [esi+0x148]
          fsub    dword ptr [esi+0x13C]
        }
        this->m_fPosZ = pParams.y;
        // __asm { fstp    [esp+0x104+var_E0] }
        v57 = pParams.z;
        __asm { fstp    dword ptr [edi] }
        *_EDI = _ET1;
        *(float *)&this->m_scepath = v57;
        ((gbVec3D *)&this->m_fField44)->Normalize();
        __asm
        {
          fld     g_nRoleSystem_58B38C
          fld     st
          fmul    dword ptr [edi]
        }
        __asm { fstp    dword ptr [edi] }
        *_EDI = _ET1;
        __asm
        {
          fld     st
          fmul    dword ptr [edi+4]
          fstp    dword ptr [edi+4]
        }
        this->m_fPosZ = _ET1;
        __asm
        {
          fmul    dword ptr [edi+8]
          fstp    dword ptr [edi+8]
        }
        *(float *)&this->m_scepath = _ET1;
        v206->m_FrameA.m_childs.m_nSize = 0;
        ((RoleSystem *)v206)->UpdateTransform();
        this->m_bBigMapState = 1;
        goto LABEL_99;
      }
      return;
    case 0xB:
      if ( v207 == 1 && !this->m_bBigMapState )
      {
        v62 = &v199;
        v63 = 4;
        do
        {
          v62 = (gbMatrix4 *)((char *)v62 + 12);
          --v63;
        }
        while ( v63 );
        p_xy = &v199.xy;
        v65 = 4;
        do
        {
          *(p_xy - 1) = this->m_fCamX;
          v66 = this->m_fCamZ;
          *p_xy = 0.0;
          p_xy[1] = v66;
          p_xy += 3;
          --v65;
        }
        while ( v65 );
        ((Object3D *)_ESI)->SetTransform(&pMatrix);
        v194.x = -12.0;
        // __asm { fld     [esp+0x104+var_C] }
        _EAX = (char *)(&v194.x + g_nCurrentRoleSlot);
        v194.y = 4.0;
        v194.z = 4.0;
        v195 = 1091567616;
        v196 = 1094713344;
        __asm
        {
          fadd    dword ptr [eax]
          fld     dword ptr [esp+0x104+var_98]
        }
        v193.x = 100000.0;
        v68 = 0;
        __asm { fsub    st, st(1) }
        _EBX = (float *)&v206->m_fontcolor.Color;
        _EDI = &v199.xz;
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
          ((gbVec3D *)&pfVal2)->Length();
          __asm
          {
            fcom    [esp+0x104+var_D0]
            fnstsw  ax
          }
          if ( (_AX & 0x100) != 0 )
          {
            v72 = *(_EDI - 1);
            v73 = *(scSCEFile **)_EDI;
            this->m_nFrameCounter = *(int *)(_EDI - 2);
            // __asm { fstp    [esp+0x104+var_D0] }
            this->m_fField3C = v72;
            this->m_pBigMapSce = v73;
            this->m_nExecState = v68;
          }
          else
          {
            __asm { fstp    st }
          }
          ++v68;
          _EDI += 3;
        }
        while ( v68 < 4 );
        __asm
        {
          fld     [esp+0x104+var_D0]
          fcomp   dword ptr [flt_56AB24]
          fnstsw  ax
        }
        if ( (_AX & 0x100) == 0 )
          goto LABEL_103;
        _EBP = &this->m_nFrameCounter;
        if ( !((PalScriptMgr *)_ESI)->CmdUpdateRolePath(_EBX, (float *)&this->m_nFrameCounter) )
          goto LABEL_103;
        _EDI = &this->m_fField44;
        this->m_fField44 = this->m_fCamX;
        this->m_fPosZ = this->m_fCamY;
        this->m_scepath = (scSCEFile *)LODWORD(this->m_fCamZ);
        __asm
        {
          fld     dword ptr [edi]
          fsub    dword ptr [ebp+0]
          fstp    dword ptr [edi]
        }
        *_EDI = _ET1;
        __asm
        {
          fld     dword ptr [edi+4]
          fsub    dword ptr [ebp+4]
          fstp    dword ptr [edi+4]
        }
        _EDI[1] = _ET1;
        __asm
        {
          fld     dword ptr [edi+8]
          fsub    dword ptr [ebp+8]
          fstp    dword ptr [edi+8]
        }
        _EDI[2] = _ET1;
        this->m_fPosZ = 0.0;
        ((gbVec3D *)&this->m_fField44)->Normalize();
        __asm
        {
          fld     g_nRoleSystem_58B38C
          fld     st
          fmul    dword ptr [edi]
        }
        __asm { fstp    dword ptr [edi] }
        *_EDI = _ET1;
        __asm
        {
          fld     st
          fmul    dword ptr [edi+4]
          fstp    dword ptr [edi+4]
        }
        this->m_fPosZ = _ET1;
        __asm
        {
          fmul    dword ptr [edi+8]
          fstp    dword ptr [edi+8]
        }
        *(float *)&this->m_scepath = _ET1;
        ((RoleSystem *)v206)->SetMoveTarget((float *)&this->m_nFrameCounter, 1);
        ((RoleSystem *)v206)->GetMoveState();
        ((RoleSystem *)_ESI)->ProcessAction();
        v83 = this->m_bExecuteBlock;
        this->m_bBigMapState = 1;
        if ( v83 == -1 )
          goto LABEL_89;
        goto LABEL_88;
      }
      return;
    case 0xC:
      if ( v207 == 1 )
      {
        if ( g_nCurrentRoleSlot != this->m_nCmdValue )
        {
          v84 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("cantopen");
          goto LABEL_179;
        }
        if ( !this->m_bBigMapState )
        {
          p_m_nFrameCounter = &this->m_nFrameCounter;
          _EBP = v206;
          this->m_nFrameCounter = LODWORD(this->m_fCamX);
          this->m_fField3C = this->m_fCamY;
          this->m_pBigMapSce = (scSCEFile *)LODWORD(this->m_fCamZ);
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
          ((gbVec3D *)&pfVal2)->Length();
          __asm
          {
            fcomp   _flt_600_0
            fnstsw  ax
          }
          if ( (_AX & 0x100) == 0 )
            goto LABEL_103;
          _EBX = &v206->m_fontcolor;
          if ( !((PalScriptMgr *)_ESI)->CmdUpdateRolePath((float *)&v206->m_fontcolor.Color, (float *)&this->m_nFrameCounter) )
            goto LABEL_103;
          this->_todo_054 = 0;
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
          pfVal2.y = 0.0;
          pfVal2.z = pParams.z;
          ((gbVec3D *)&pfVal2)->Length();
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
            this->m_bBigMapState = 2;
            ((RoleSystem *)v206)->GetMoveState();
            ((RoleSystem *)v206)->GetActionByIndex(8);
          }
          else
          {
            ((gbVec3D *)&pfVal2)->Normalize();
            if ( this->m_nCmdValue == 2 )
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
            this->m_fField3C = pParams.y;
            // __asm { fstp    [esp+0x110+var_E0] }
            v90 = pParams.z;
            __asm { fstp    dword ptr [edi] }
            *(float *)p_m_nFrameCounter = _ET1;
            *(float *)&this->m_pBigMapSce = v90;
            FightInfo();
            ((ScriptVM *)_ESI)->CallFunction(1u, 0);
            ((PalScriptMgr *)_ESI)->ExecuteOpcode();
          }
          v83 = this->m_bExecuteBlock;
          if ( v83 != -1 )
LABEL_88:
            this->m_bExecuteBlock = v83 - 1;
          goto LABEL_89;
        }
      }
      return;
    case 0xE:
      if ( !v208 && !this->m_bBigMapState )
      {
        if ( this->m_nCmdValue )
        {
          ((PalScriptMgr *)this->m_pClearResult)->ClearAllScript();
          if ( !v93 )
          {
            ((RoleSystem *)v206)->Notify();
            goto LABEL_96;
          }
        }
        else
        {
          this->m_bBigMapState = 1;
          ((RoleSystem *)v206)->Notify();
          v97 = ((CScreenMode *)v96)->GetSoundList();
          ((PtrArray *)v97)->SetResolution((int)_ESI, 0);
          if ( this->_todo_058 == 3 )
          {
            ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(2.0);
            (*(void (**)(char *, _DWORD))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, 0);
          }
LABEL_99:
          v98 = this->m_bExecuteBlock;
          if ( v98 != -1 )
            this->m_bExecuteBlock = v98 - 1;
        }
      }
      return;
    case 0xF:
      if ( v207 == 1 )
      {
        _EDI = v206;
        pfVal2.x = this->m_fCamX;
        __asm
        {
          fld     [esp+0x104+pfVal2]
          fsub    dword ptr [edi+4]
        }
        pfVal2.y = this->m_fCamY;
        v100 = this->m_fCamZ;
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
        ((gbVec3D *)&pfVal2)->Length();
        __asm
        {
          fcomp   _flt_600_0
          fnstsw  ax
        }
        if ( (_AX & 0x4100) == 0 )
          goto LABEL_103;
        if ( this->m_pScriptObj )
          goto LABEL_254;
        __asm
        {
          fld     dword ptr [esi+0x0E0]
          fadd    _flt_180_0
        }
        // __asm { fstp    [esp+0x10C+fVal]; fVal }
        RoleSystem::StartPathMove(
          v206,
          (char *)this->m_nCmdValue,
          *(_DWORD *)&this->m_nCmdParam0,
          *(char **)&this->m_nCmdParam1,
          this->m_nCmdParam2,
          fVala,
          (int)_ESI);
      }
      return;
    case 0x10:
      if ( v207 == 1 )
      {
        ((PalScriptMgr *)this->m_pClearResult)->ClearAllScript();
        if ( !v102 )
        {
LABEL_96:

          this->m_pClearResult = v95;
          v186 = (int)v95;
          fVal = 0;
          goto LABEL_90;
        }
        goto LABEL_254;
      }
      return;
    case 0x11:
      if ( v207 == 2 && ((ScriptVM *)this)->IsRunning() )
      {
        ((PalScriptMgr *)_ESI)->CmdPushCmd07(1u);
        this->m_bBigMapState = 1;
        goto LABEL_253;
      }
      return;
    case 0x13:
      if ( v207 == 2 && ((ScriptVM *)this)->IsRunning() )
      {
        ((ScriptVM *)_ESI)->SetRolePosition(0);
        ((RoleSystem *)_ESI)->ExecScriptDataCmd((int *)&this->m_fCamX);
        ((PalScriptMgr *)_ESI)->CmdRoleMoveSmooth(0, v187);
        ((PalScriptMgr *)_ESI)->CmdPushCmd07(1u);
        ((PalScriptMgr *)_ESI)->CmdPushCmd10(1u);
        ((ScriptVM *)_ESI)->SetRolePosition(1u);
        ((ScriptVM *)_ESI)->CallFunction(1u, 0);
        ((PalScriptMgr *)_ESI)->ExecuteOpcode();
      }
      return;
    case 0x14:
      if ( v207 == 1 )
      {
LABEL_56:
        if ( m_bExecuteBlock != -1 )
          this->m_bExecuteBlock = m_bExecuteBlock - 1;
        goto LABEL_254;
      }
      return;
    case 0x15:
    case 0x1E:
    case 0x25:
      return;
    case 0x16:
      if ( v207 != 2 )
        return;
      pParams.x = this->m_fCamX;
      v103 = (unsigned __int8)this->m_bBigMapState;
      pParams.y = this->m_fCamY;
      pParams.z = this->m_fCamZ;
      if ( !v103 )
      {
        // __asm { fild    dword ptr [esi+0x0F8] }
        this->m_bBigMapState = 1;
        // __asm { fstp    [esp+0x104+var_E4] }
        goto LABEL_119;
      }
      if ( v103 == 2 )
      {
        this->m_bBigMapState = 3;
LABEL_119:

        this->m_nSavedPosX = ((PalScriptMgr *)_ESI)->IsPosInBounds((float *)v206);
        v104 = this->m_bExecuteBlock;
        if ( v104 != -1 )
          this->m_bExecuteBlock = v104 - 1;
        v51 = (CScreenMode *)g_pCameraCtrl;
        if ( *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
          ((CameraCtrl *)&g_pCameraCtrl)->InitParams(&pParams);
        goto LABEL_89;
      }
      return;
    case 0x17:
      ((Object3D *)_ESI)->SetTransform(&v199);
      __asm
      {
        fld     [esp+0x104+var_50]
        fcomp   [esp+0x104+var_58]
        fnstsw  ax
      }
      if ( (_AX & 0x4100) != 0 )
        // __asm { fld     [esp+0x104+var_58] }
      else
        // __asm { fld     [esp+0x104+var_50] }
      __asm { fmul    _flt_0_5 }
      _EDI = v206;
      _EBP = &this->m_fCamX;
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
      ((gbVec3D *)&pfVal2)->Length();
      v109 = *(_DWORD *)&this->m_nCmdParam0;
      // __asm { fstp    [esp+0x104+var_D0] }
      if ( !v109 )
      {
        if ( v207 != 1 )
          return;
        goto LABEL_143;
      }
      v110 = v109 - 1;
      if ( !v110 )
      {
        if ( v207 != 2 )
          return;
        goto LABEL_143;
      }
      if ( v110 != 1 )
        goto LABEL_143;
      if ( v207 != 1 )
      {
        if ( v207 != 2 )
          return;
LABEL_143:
        if ( !this->m_bBigMapState )
        {
          v115 = ((CScreenMode *)v108)->GetSoundList();
          ((PtrArray *)v115)->SetResolution((int)_ESI, 0);
          if ( v207 == 2 )
          {
            this->m_bScriptPause = this->m_bScriptPause == 0;
            v116 = this->_todo_058;
            this->m_bBigMapState = 3;
            if ( v116 == 3 )
            {
              (*(void (**)(char *, _DWORD))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, 0);
              ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(2.0);
              ((PalScriptMgr *)_ESI)->RunCommand();
            }
            v117 = this->m_bExecuteBlock;
            if ( v117 != -1 )
              this->m_bExecuteBlock = v117 - 1;
            if ( this->m_nCmdValue == 1 )
              this->m_bOpcodeFlag = this->m_bScriptPause;
          }
          else
          {
            pfVal2.x = *_EBP;
            // __asm { fld     [esp+0x104+pfVal2] }
            // __asm { fsub    dword ptr [edi+0x0A0] }
            v118 = this->m_fCamZ;
            pfVal2.y = this->m_fCamY;
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
              fdiv    [esp+0x104+var_D0]
              fstp    [esp+0x104+pfVal2]
              fld     [esp+0x104+var_F0]
              fdiv    [esp+0x104+var_D0]
              fstp    [esp+0x104+var_F0]
              fld     [esp+0x104+var_EC]
              fdiv    [esp+0x104+var_D0]
              fstp    [esp+0x104+var_EC]
              fld     [esp+0x104+var_D0]
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
              this->_todo_054 = 0;
              *(float *)&this->m_nFrameCounter = v120;
              this->m_fField3C = y;
              *(float *)&this->m_pBigMapSce = v122;
              v123 = ((CScreenMode *)LODWORD(y))->GetSoundList();
              ((PtrArray *)v123)->SetResolution((int)_ESI, 0);
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
              pfVal2.y = 0.0;
              pfVal2.z = pParams.z;
              ((gbVec3D *)&pfVal2)->Length();
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
                this->m_bBigMapState = 2;
                ((RoleSystem *)v206)->IsPathComplete(&this->m_fCamX, 1);
                ((RoleSystem *)v206)->GetMoveState();
                ((RoleSystem *)v206)->GetActionByIndex(11);
                ((ScriptVM *)_ESI)->UpdatePauseState();
              }
              else
              {
                FightInfo();
                ((PalScriptMgr *)_ESI)->CmdRoleMoveDirect(v187);
                ((ScriptVM *)_ESI)->CallFunction(0x4Du, 0);
                ((PalScriptMgr *)_ESI)->ExecuteOpcode();
              }
            }
          }
        }
        return;
      }
      if ( *(_DWORD *)v206->m_partyActor.m_szTexture != (unsigned __int8)this->m_bExecuteOpcode )
        goto LABEL_103;
      __asm
      {
        fld     [esp+0x104+var_D0]
        fcomp   dword ptr [flt_56AB40]
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0
        || !((PalScriptMgr *)_ESI)->CmdUpdateRolePath((float *)&v206->m_fontcolor.Color, &this->m_fCamX) )
      {
LABEL_103:
        v84 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("outdist");
        goto LABEL_179;
      }
      ((PalScriptMgr *)this->m_pClearResult)->ClearAllScript();
      if ( !v113 )
      {

        this->m_pClearResult = v114;
      }
      return;
    case 0x18:
      if ( v207 == 11 )
      {
        *(_DWORD *)&g_RoleSystemExtra1.m_partyActor.m_szTexture[4] = 1;
        ((RoleSystem *)&g_RoleSystemExtra1)->GetActionByIndex(51);
        ((RoleSystem *)&g_RoleSystemExtra1)->NotifySceneChange();
        ((RoleSystem *)&g_RoleSystemExtra1)->SetTargetRotation((gbVec3D *)&this->m_fCamX);
        ((PalScriptMgr *)_ESI)->CmdPushCmd15(0);
        ((PalScriptMgr *)_ESI)->CmdCameraOrbitPos(LODWORD(this->m_fCamX), this->m_fCamY, this->m_fCamZ, 1u);
        ((PalScriptMgr *)_ESI)->CmdCameraOrbitPos(LODWORD(g_pRoleSystem->m_fPosX), g_pRoleSystem->m_fPosY, g_pRoleSystem->m_fPosZ, 0);
        ((RoleSystem *)_ESI)->ExecScriptDataIdx(1065353216);
        ((PalScriptMgr *)_ESI)->CmdPushCmd15(1u);
        ((ScriptVM *)_ESI)->CallFunction(0xBu, 0);
        ((PalScriptMgr *)_ESI)->ExecuteOpcode();
        return;
      }
      if ( v207 != 1 || this->m_bBigMapState )
        return;
      ((PalScriptMgr *)this->m_pScriptObj)->Destroy();
      this->m_pClearResult = v125;
      if ( !v125 )
        goto LABEL_245;
LABEL_238:
      this->m_bBigMapState = 1;
      goto LABEL_254;
    case 0x1A:
      if ( v207 != 1 || this->m_bBigMapState )
        return;
      ((PalScriptMgr *)_ESI)->BuildCmdTransform(&pMatrix);
      __asm
      {
        fld     [esp+0x104+var_C]
        fmul    _flt_0_5
      }
      _EDI = &this->m_fCamX;
      pParams.y = 0.0;
      _EBP = v206;
      __asm
      {
        fstp    [esp+0x104+nSceneIdx]
        fld     dword ptr [esi+0x0E0]
        fmul    _flt_0_01745329f
      }
      pfVal2 = *(gbVec3D *)&this->m_fCamX;
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
      v193.x = pParams.x;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     dword ptr [edi+8]
        fsub    dword ptr [ebp+0x0A8]
      }
      v193.y = pParams.y;
      // __asm { fstp    [esp+0x104+var_E0] }
      v193.z = pParams.z;
      ((gbVec3D *)&v193)->Length();
      __asm
      {
        fcomp   _flt_600_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) == 0 || !((PalScriptMgr *)_ESI)->CmdUpdateRolePath((float *)&v206->m_fontcolor.Color, &pfVal2.x) )
        goto LABEL_249;
      v129 = pfVal2.x;
      v130 = pfVal2.y;
      v131 = pfVal2.z;
      this->_todo_054 = 0;
      *(float *)&this->m_nFrameCounter = v129;
      this->m_fField3C = v130;
      *(float *)&this->m_pBigMapSce = v131;
      __asm
      {
        fld     dword ptr [ebp+4]
        fsub    dword ptr [edi]
        fstp    [esp+0x104+pParams]
        fld     dword ptr [ebp+8]
        fsub    dword ptr [edi+4]
      }
      v193.x = pParams.x;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     dword ptr [ebp+0x0C]
        fsub    dword ptr [edi+8]
      }
      // __asm { fstp    [esp+0x104+var_E0] }
      v193.y = 0.0;
      v193.z = pParams.z;
      ((gbVec3D *)&v193)->Length();
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
        this->m_bBigMapState = 2;
        ((RoleSystem *)v206)->IsPathComplete(&this->m_fCamX, 1);
        ((RoleSystem *)v206)->GetMoveState();
        ((RoleSystem *)v206)->GetActionByIndex(11);
        goto LABEL_254;
      }
      FightInfo();
      ((ScriptVM *)_ESI)->CallFunction(2u, 0);
      goto LABEL_247;
    case 0x1B:
      if ( v207 != 1 || this->m_bBigMapState )
        return;
      __asm
      {
        fld     dword ptr [esi+0x218]
        fadd    dword ptr [esi+0x224]
        fld     dword ptr [esi+0x228]
        fadd    dword ptr [esi+0x21C]
      }
      _EDI = v206;
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
      ((gbVec3D *)&nSceneIdx)->Length();
      __asm
      {
        fcomp   _flt_100_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
      {
        this->_todo_054 = 0;
        this->m_bBigMapState = 1;
        v136 = ((CScreenMode *)v134)->GetSoundList();
        ((PtrArray *)v136)->SetResolution((int)_ESI, 0);
        ((RoleSystem *)v206)->IsPathComplete(&pfVal2.x, 1);
        ((RoleSystem *)v206)->GetActionByIndex(11);
      }
      goto LABEL_254;
    case 0x1C:
      if ( v207 != 2 )
        return;
      if ( this->m_nCmdValue == 1 )
      {
        v137 = this->m_bScriptPause == 0;
        this->m_bScriptPause = v137;
        this->m_bOpcodeFlag = v137;
      }
      goto LABEL_254;
    case 0x1D:
      if ( v207 || !((ScriptVM *)this)->IsRunning() )
        return;
      if ( SceneMgr::GetValidPartyCount() >= this->m_nCmdValue )
      {
        _EDI = &this->m_fCamX;
        pfVal2.x = this->m_fCamX;
        pfVal2.y = this->m_fCamY;
        _EAX = v206;
        v140 = this->m_fCamZ;
        pfVal2.y = 0.0;
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
        ((gbVec3D *)&nSceneIdx)->Length();
        __asm
        {
          fld     _flt_12_0
          fmul    _flt_3_0
          fcompp
          fnstsw  ax
        }
        if ( (_AX & 0x100) == 0 )
        {
          ((ScriptVM *)_ESI)->SetRolePosition(0);
          FightInfo();
          ((PalScriptMgr *)_ESI)->CmdRoleMoveSmooth(1, v187);
          ((PalScriptMgr *)_ESI)->CmdPushCmd07(1u);
          ((ScriptVM *)_ESI)->CallFunction(1u, 0);
          __asm
          {
            fld     dword ptr [edi+4]
            fsub    _flt_7_0
          }
          v142 = this->m_fCamZ;
          pfVal2.x = *_EDI;
          pfVal2.z = v142;
          // __asm { fstp    [esp+0x108+var_F0] }
          ((PalScriptMgr *)_ESI)->CmdRoleMoveSmooth(0, v188);
          ((ScriptVM *)_ESI)->ExecuteOpcode(&pfVal2, 0, 0);
          ((PalScriptMgr *)_ESI)->CmdPushCmd05(0);
          ((ScriptVM *)_ESI)->SetRolePosition(1u);
LABEL_253:
          ((PalScriptMgr *)_ESI)->ExecuteOpcode();
LABEL_254:
          ((PalScriptMgr *)this->m_pScriptObj)->Destroy();
        }
      }
      else
      {
        v84 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("lessweight");
LABEL_179:
        ((PalScriptMgr *)&stru_DBA134)->ShowTextBox(v84);
      }
      return;
    case 0x1F:
      if ( v207 != 2 || this->m_bBigMapState )
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
      ScriptVM::ExecuteOpcode((ScriptVM *)this, pData, LOBYTE(nType), 0);
      ((PalScriptMgr *)_ESI)->CmdPushCmd05(0);
      ((ScriptVM *)_ESI)->CallFunction(1u, 0);
      ((PalScriptMgr *)_ESI)->RunCommand();
      goto LABEL_253;
    case 0x20:
      if ( v207 || this->m_bBigMapState )
        return;
      this->m_bBigMapState = 1;
      ((UIBigMap *)v206)->Update((int *)&this->m_fCamX, 1);
      ((PalScriptMgr *)_ESI)->RunCommand();
      goto LABEL_254;
    case 0x21:
      if ( !v208 && !v207 && ((ScriptVM *)this)->IsRunning() )
      {
        __asm
        {
          fld     dword ptr [esi+0x2C]
          fsub    _flt_5_0
        }
        _EDI = &this->m_fCamX;
        // __asm { fstp    [esp+0x110+nSceneIdx] }
        FightInfo();
        __asm { fld     dword ptr [edi] }
        __asm
        {
          fstp    [esp+0x104+var_A4]
          fld     dword ptr [esi+0x30]
        }
        v198[1] = nSceneIdx.x;
        // __asm { fstp    [esp+0x110+var_9C] }
        ((ScriptVM *)_ESI)->ExecuteOpcode(v198, 0, 0);
        ((PalScriptMgr *)_ESI)->CmdPushCmd04((int)this->m_pScriptObj, 0);
        ((PalScriptMgr *)_ESI)->CmdPushCmd05(0);
        v144 = this->m_bExecuteBlock;
        if ( v144 != -1 )
          this->m_bExecuteBlock = v144 - 1;
        ((PalScriptMgr *)_ESI)->ExecuteOpcode();
LABEL_89:
        v186 = 0;
        fVal = (int)_ESI;
LABEL_90:
        v92 = ((CScreenMode *)v51)->GetSoundList();
        ((PtrArray *)v92)->SetResolution(fVal, v186);
      }
      return;
    case 0x22:
      if ( v207 == 2 && ((ScriptVM *)this)->IsRunning() )
      {
        __asm
        {
          fld     _flt_12_0
          fmul    _flt_10_0
        }
        LODWORD(nSceneIdx.x) = this->m_nCmdValue;
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
        pfVal2.y = 0.0;
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
        ((ScriptVM *)_ESI)->GetRolePosition(1u);
        ((ScriptVM *)_ESI)->ExecuteOpcode(&pfVal2, 0, 0);
        ((ScriptVM *)_ESI)->GetRolePosition(0);
        ((PalScriptMgr *)_ESI)->CmdPushCmd05(0);
        v145 = this->m_bExecuteBlock;
        if ( v145 != -1 )
          this->m_bExecuteBlock = v145 - 1;
        ((PalScriptMgr *)_ESI)->RunCommand();
        ((PalScriptMgr *)_ESI)->ExecuteOpcode();
      }
      return;
    case 0x23:
      if ( !v207 && ((ScriptVM *)this)->IsRunning() )
      {
        ((RoleSystem *)_ESI)->ExecScriptDataA();
        ((PalScriptMgr *)_ESI)->CmdPushCmd04((int)this->m_pScriptObj, 1u);
        v147 = ((CScreenMode *)v146)->GetSoundList();
        ((PtrArray *)v147)->SetResolution((int)_ESI, 0);
        ((PalScriptMgr *)_ESI)->ExecuteOpcode();
      }
      return;
    case 0x24:
      if ( (!v207 || v207 == 2) && ((ScriptVM *)this)->IsRunning() )
      {
        ((RoleSystem *)&g_pRoleSystem)->Notify();
        ((RoleSystem *)_ESI)->ExecScriptDataB();
        ((ScriptVM *)_ESI)->CallFunction(1u, 1);
        ((ScriptVM *)_ESI)->GetRolePosition(0);
        ((PalScriptMgr *)_ESI)->CmdPushCmd10(0);
        ((PalScriptMgr *)_ESI)->CmdPushCmd04((int)this->m_pScriptObj, 0);
        ((PalScriptMgr *)_ESI)->RunCommand();
        ((PalScriptMgr *)_ESI)->ExecuteOpcode();
        v149 = ((CScreenMode *)v148)->GetSoundList();
        ((PtrArray *)v149)->SetResolution((int)_ESI, 0);
        ((PalScriptMgr *)_ESI)->ExecuteScriptByID();
      }
      return;
    case 0x26:
      if ( !((ScriptVM *)this)->IsRunning() )
        return;
      if ( v207 )
      {
        if ( v207 != 3 || !*(_DWORD *)&this->m_nCmdParam0 )
          return;
        this->_todo_054 = 0;
        pParams = *(gbVec3D *)&this->m_fCamX;
        __asm
        {
          fld     [esp+0x108+var_E4]
          fsub    _flt_200_0
        }
        // __asm { fstp    [esp+0x108+var_E4] }
        ((ScriptVM *)_ESI)->SetRolePosition(0);
        FightInfo();
        ((ScriptVM *)_ESI)->ExecuteOpcode(&pParams, 0, 1);
        ((PalScriptMgr *)_ESI)->CmdPushCmd04(*(_DWORD *)&this->m_nCmdParam0, 0);
      }
      else
      {
        if ( !this->m_nCmdValue )
          return;
        if ( !v208 )
          return;
        __asm
        {
          fld     [esp+0x104+arg_C]
          fadd    dword ptr [esi+0x54]
          fst     dword ptr [esi+0x54]
        }
        *(float *)&this->_todo_054 = _ET1;
        __asm
        {
          fcomp   _flt_4_0
          fnstsw  ax
        }
        if ( (_AX & 0x100) != 0 )
          return;
        this->_todo_054 = 0;
        pParams = *(gbVec3D *)&this->m_fCamX;
        __asm
        {
          fld     [esp+0x108+var_E4]
          fadd    _flt_200_0
        }
        // __asm { fstp    [esp+0x108+var_E4] }
        ((ScriptVM *)_ESI)->SetRolePosition(0);
        FightInfo();
        ((ScriptVM *)_ESI)->ExecuteOpcode(&pParams, 0, 1);
        ((PalScriptMgr *)_ESI)->CmdPushCmd04(this->m_nCmdValue, 0);
      }
      ((ScriptVM *)_ESI)->SetRolePosition(1u);
      ((PalScriptMgr *)_ESI)->ExecuteOpcode();
      return;
    case 0x27:
      if ( !((ScriptVM *)this)->IsRunning() )
        return;
      _EDI = (_DWORD *)((RoleSystem *)this->m_pSceneMgr->m_rect.left)->GetRolePtr((unsigned __int8)this->m_bExecuteOpcode);
      v153 = this->m_nExecRangeA + this->m_nExecRangeC;
      __asm { fld     _flt_0_0 }
      LODWORD(v153) = v153 - HIDWORD(v153);
      HIDWORD(v153) = this->m_nExecRangeB;
      v154 = v153;
      LODWORD(v153) = this->m_nExecRangeD;
      v155 = v154 >> 1;
      LODWORD(nSceneIdx.x) = v155;
      // __asm { fild    [esp+0x104+nSceneIdx] }
      __asm { fadd    _flt_0_5 }
      v156 = (HIDWORD(v153) + (int)v153) / 2;
      __asm { fmul    g_ScriptSystemData }
      LODWORD(nSceneIdx.y) = v156;
      __asm
      {
        fadd    dword ptr [edi+0x80]
        fstp    [esp+0x104+pParams]
        fild    [esp+0x104+var_D8]
        fadd    _flt_0_5
        fmul    g_ScriptSystemData
        fadd    dword ptr [edi+0x88]
        fstp    [esp+0x104+var_E0]
      }
      if ( v155 >= 0 )
      {
        v157 = _EDI[38];
        if ( v155 < v157 && v156 >= 0 && v156 < _EDI[39] )
        {
          __asm { fstp    st }
          _EAX = v155 + v157 * v156;
          _ECX = _EDI[40];
          __asm { fld     dword ptr [ecx+eax*8] }
        }
      }
      v160 = pParams.x;
      v161 = pParams.z;
      // __asm { fstp    dword ptr [esi+0x2C] }
      this->m_fCamY = _ET1;
      this->m_fCamX = v160;
      this->m_fCamZ = v161;
      pfVal2.x = this->m_fCamX;
      pfVal2.y = this->m_fCamY;
      m_nCmdValue = this->m_nCmdValue;
      pfVal2.z = this->m_fCamZ;
      ((RoleSystem *)this->m_pSceneMgr->m_rect.left)->SetRoleParam(m_nCmdValue, &pfVal2.x, 0, 0);
      __asm
      {
        fst     [esp+0x104+var_F0]
        fstp    [esp+0x104+var_CC]
        fld     [esp+0x104+var_EC]
        fadd    _flt_80_0
      }
      v193.x = pfVal2.x;
      // __asm { fstp    [esp+0x110+var_C8] }
      FightInfo();
      ((PalScriptMgr *)_ESI)->CmdRoleMoveSmooth(0, v187);
      ((ScriptVM *)_ESI)->ExecuteOpcode(&pfVal2, 0, 1);
      ((PalScriptMgr *)_ESI)->CmdPushCmd14(this->m_nCmdValue, 0);
      FightInfo();
      goto LABEL_247;
    case 0x28:
      if ( !((ScriptVM *)this)->IsRunning() || v207 )
        return;
      LODWORD(nSceneIdx.x) = ((unsigned __int8)this->m_bExecuteOpcode + 1) % 2;
      if ( LODWORD(nSceneIdx.x) )
      {
        v163 = *(float *)&this->m_nCmdParam1;
        v164 = *(float *)&this->m_nCmdParam2;
      }
      else
      {
        v163 = *(float *)&this->m_nCmdValue;
        v164 = *(float *)&this->m_nCmdParam0;
      }
      v193.x = v163;
      m_pSceneMgr = this->m_pSceneMgr;
      v193.y = v164;
      _EAX = (_DWORD *)((RoleSystem *)m_pSceneMgr->m_rect.left)->GetRolePtr(SLODWORD(nSceneIdx.x));
      // __asm { fild    [esp+0x104+var_D0] }
      pfVal2.y = 0.0;
      __asm
      {
        fadd    _flt_0_5
        fmul    g_ScriptSystemData
        fadd    dword ptr [eax+0x80]
        fstp    [esp+0x104+pfVal2]
        fild    [esp+0x104+var_CC]
        fadd    _flt_0_5
        fmul    g_ScriptSystemData
        fadd    dword ptr [eax+0x88]
        fstp    [esp+0x104+var_EC]
      }
      if ( v163 >= 0.0 )
      {
        v167 = _EAX[38];
        if ( SLODWORD(v163) < v167 && v164 >= 0.0 && SLODWORD(v164) < _EAX[39] )
        {
          _EAX = _EAX[40];
          _EDX = LODWORD(v163) + v167 * LODWORD(v164);
          __asm
          {
            fld     dword ptr [eax+edx*8]
            fstp    [esp+0x104+var_F0]
          }
        }
      }
      v194 = pfVal2;
      pParams.x = this->m_fCamX;
      v170 = this->m_pSceneMgr;
      nTypea = LODWORD(v163);
      x_low = LODWORD(nSceneIdx.x);
      v172 = this->m_fCamZ;
      pParams.y = this->m_fCamY;
      pParams.z = v172;
      ((Scene *)v170->m_rect.left)->GetTileHeight(SLODWORD(nSceneIdx.x), nTypea, SLODWORD(v164), 0);
      ((gbMatrix4 *)&pMatrix)->gbMatrix4();
      ((PalScriptMgr *)_ESI)->BuildCmdTransform(&pMatrix);
      __asm
      {
        fld     [esp+0x104+var_8]
        fadd    [esp+0x104+var_E4]
      }
      // __asm { fstp    [esp+0x108+var_E4] }
      ((ScriptVM *)_ESI)->SetRolePosition(0);
      FightInfo();
      ((ScriptVM *)_ESI)->ExecuteOpcode(&pParams, 0, 1);
      ((ScriptVM *)_ESI)->GetRolePosition(1u);
      ((PalScriptMgr *)_ESI)->CmdPushCmd14(x_low, 1u);
      ((ScriptVM *)_ESI)->GetRolePosition(0);
      FightInfo();
      ((ScriptVM *)_ESI)->SetRolePosition(1u);
      goto LABEL_253;
    case 0x29:
      if ( !((ScriptVM *)this)->IsRunning() )
        return;
      if ( v207 == 10 )
        goto LABEL_238;
      FightInfo();
      ((PalScriptMgr *)_ESI)->CmdRoleMoveDirect(v187);
      ((PalScriptMgr *)_ESI)->CmdRoleMoveSmooth(0, v189);
      ((PalScriptMgr *)_ESI)->CmdPushCmd07(1u);
      goto LABEL_246;
    case 0x2A:
      if ( v207 != 1 )
        return;
      if ( !((ScriptVM *)this)->IsRunning() )
        return;
      _EAX = g_pRoleSystem;
      if ( (unsigned __int8)this->m_bExecuteOpcode != *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture )
        return;
      __asm
      {
        fld     dword ptr [esi+0x28]
        fsub    dword ptr [eax+0x0A0]
        fstp    [esp+0x104+pParams]
        fld     dword ptr [esi+0x2C]
        fsub    dword ptr [eax+0x0A4]
      }
      v194.x = pParams.x;
      __asm
      {
        fstp    [esp+0x104+var_E4]
        fld     dword ptr [esi+0x30]
        fsub    dword ptr [eax+0x0A8]
      }
      v194.y = pParams.y;
      // __asm { fstp    [esp+0x104+var_E0] }
      v194.z = pParams.z;
      ((gbVec3D *)&v194)->Length();
      __asm
      {
        fcomp   _flt_600_0
        fnstsw  ax
      }
      if ( (_AX & 0x100) != 0 )
      {
        v175 = this->m_fCamZ;
        _EAX = g_pRoleSystem;
        nSceneIdx.x = this->m_fCamX;
        // __asm { fld     [esp+0x104+nSceneIdx] }
        nSceneIdx.z = v175;
        nSceneIdx.y = 0.0;
        __asm
        {
          fsub    dword ptr [eax+4]
          fld     dword ptr [eax+8]
          fchs
          fstp    [esp+0x104+var_C0]
          fld     [esp+0x104+var_D4]
          fsub    dword ptr [eax+0x0C]
        }
        // __asm { fstp    [esp+0x104+var_BC] }
        nSceneIdx.y = v194.y;
        // __asm { fstp    [esp+0x104+nSceneIdx] }
        nSceneIdx.z = v194.z;
        ((gbVec3D *)&nSceneIdx)->Length();
        __asm
        {
          fld     [esp+0x104+nSceneIdx]
          fdiv    st, st(1)
        }
        _EAX = g_pRoleSystem;
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
          fstp    [esp+0x10C+var_C0]
          fld     [esp+0x10C+var_D4]
          fadd    dword ptr [eax+0x0C]
        }
        nSceneIdx.y = v194.y;
        // __asm { fstp    [esp+0x110+var_BC] }
        // __asm { fstp    [esp+0x110+nSceneIdx] }
        nSceneIdx.z = v194.z;
LABEL_245:
        FightInfo();
        ((PalScriptMgr *)_ESI)->CmdRoleMoveDirect(v187);
LABEL_246:
        ((ScriptVM *)_ESI)->CallFunction(1u, 0);
LABEL_247:
        ((PalScriptMgr *)_ESI)->ExecuteOpcode();
LABEL_248:
        v178 = ((CScreenMode *)v37)->GetSoundList();
        ((PtrArray *)v178)->SetResolution((int)_ESI, 0);
      }
      else
      {
LABEL_249:
        v179 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("outdist");
        ((PalScriptMgr *)&stru_DBA134)->ShowTextBox(v179);
      }
      goto LABEL_254;
    default:
      goto LABEL_254;
  }
}

// 0x00429D80
int PalScriptMgr::InitControlBlock()
{
  memset(this, 0, 0x54u);
  return (int)this;
}

// 0x00429DB0
void PalScriptMgr::BuildCmdTransform(gbMatrix4 *pMatrix)
{
  char m_nCmdType; // al
  int todo_058; // eax
  int *p_todo_060; // esi
  double v5; // st6
  float v6; // [esp+0x4] [ebp-0x18]
  float v7; // [esp+0x8] [ebp-0x14]
  float v8; // [esp+0x8] [ebp-0x14]
  float v9; // [esp+0xC] [ebp-0x10]
  float v10; // [esp+0xC] [ebp-0x10]
  struct gbVec3D v11; // [esp+0x10] [ebp-0xC] BYREF

  m_nCmdType = this->m_nCmdType;
  if ( m_nCmdType == 20 || m_nCmdType == 27 )
  {
    v6 = this->m_fPosBX - this->m_fPosAX;
    v7 = this->m_fPosBY - this->m_fPosAY;
    v5 = this->m_fPosBZ - this->m_fPosAZ;
    v11.x = v6;
    v11.y = v7;
    v9 = v5;
    *(float *)&pMatrix[1] = v6;
    v11.z = v9;
    pMatrix[1].xy = v7;
    pMatrix[1].xz = v9;
    v8 = this->m_fPosBY + this->m_fPosAY;
    v10 = this->m_fPosBZ + this->m_fPosAZ;
    v11.x = (this->m_fPosAX + this->m_fPosBX) * 0.5;
    v11.y = v8 * 0.5;
    v11.z = v10 * 0.5;
    ((gbMatrix4 *)pMatrix)->LoadIdentity();
    ((gbMatrix4 *)pMatrix)->RightTranslate(v11);
  }
  else
  {
    todo_058 = this->_todo_058;
    if ( todo_058 )
    {
      if ( todo_058 == 2 || todo_058 == 3 )
      {
        p_todo_060 = &this->_todo_060;
        ((gbMatrix4 *)pMatrix)->operator=(&this->_todo_060);
        *(_DWORD *)&pMatrix[1] = p_todo_060[16];
        LODWORD(pMatrix[1].xy) = p_todo_060[17];
        LODWORD(pMatrix[1].xz) = p_todo_060[18];
      }
      else
      {
        (*(void ( **)(char *, gbMatrix4 *))(*(_DWORD *)this->m_pExecSystem + 56))(
          this->m_pExecSystem,
          pMatrix);
      }
    }
  }
}

// 0x00429F90
void PalScriptMgr::BuildFullTransform(gbMatrix4 *pMatrix, gbVec3D *pPos)
{
  gbMatrix4 v4; // [esp+0x14] [ebp-0x40] BYREF

  this->BuildCmdTransform(pMatrix);
  ((gbMatrix4 *)&v4)->LoadIdentity();
  ((gbMatrix4 *)&v4)->SetAxisAngle(0, this->m_nMatrixData);
  ((gbMatrix4 *)pMatrix)->RightMultiply(&v4);
  ((gbMatrix4 *)&v4)->SetAxisAngle(1, LODWORD(this->m_fAngle));
  ((gbMatrix4 *)pMatrix)->RightMultiply(&v4);
  ((gbMatrix4 *)pMatrix)->RightTranslate(pPos);
}

// 0x0042AAE0
BOOL PalScriptMgr::CheckTileCollision(int *pnVal, int nVal, gbVec3D *p)
{
  GRPinput *RolePtr; // eax
  BOOL result; // eax
  int v7; // edx
  LONG left; // ecx
  Object3D *v9; // ebx
  int v10; // edi
  LONG v11; // eax
  int i; // ebx
  unsigned __int8 Tile; // [esp+0x10] [ebp-0x9C]
  struct gbOBBox v14; // [esp+0x14] [ebp-0x98] BYREF
  gbOBBox pMatrix; // [esp+0x60] [ebp-0x4C] BYREF

  RolePtr = (GRPinput *)((RoleSystem *)this->m_pSceneMgr->m_rect.left)->GetRolePtr((unsigned __int8)this->m_bExecuteOpcode);
  result = ((GRPinput *)RolePtr)->GetJoystickFreePos((int)pnVal, nVal);
  if ( result )
  {
    Tile = ((RoleSystem *)this->m_pSceneMgr)->GetTile((int)pnVal, nVal);
    if ( Tile != 0xFF )
    {
      v7 = 896 * Tile;
      left = this->m_pSceneMgr->m_rect.left;
      v9 = (Object3D *)(v7 + left + 224);
      if ( !*(_BYTE *)(v7 + left + 433) && (*(_BYTE *)(v7 + left + 432) & 2) != 0 )
      {
        this->BuildFullTransform((gbMatrix4 *)&pMatrix, p);
        ((Object3D *)v9)->SetTransform((gbMatrix4 *)&v14);
        if ( ((gbOBBox *)&pMatrix)->IsColOBB(v14) )
          return 0;
      }
    }
    if ( this->m_nCmdType == 11 )
    {
      this->BuildFullTransform((gbMatrix4 *)&v14, p);
      v10 = 0;
      v11 = this->m_pSceneMgr->m_rect.left;
      if ( *(int *)(v11 + 220) > 0 )
      {
        for ( i = 0; ; i += 896 )
        {
          if ( v10 != (unsigned __int8)this->m_bRoleCmd_42ac80 && *(_BYTE *)(i + v11 + 468) == 11 )
          {
            ((Object3D *)(i + v11 + 224))->SetTransform((gbMatrix4 *)&pMatrix);
            if ( ((gbOBBox *)&v14)->IsColOBB(pMatrix) )
              break;
          }
          ++v10;
          v11 = this->m_pSceneMgr->m_rect.left;
          if ( v10 >= *(_DWORD *)(v11 + 220) )
            return 1;
        }
        return 0;
      }
    }
    return 1;
  }
  return result;
}

// 0x0042AC80
int PalScriptMgr::CmdUpdateRolePath(float *pfVal, float *pfVal2)
{
  int result; // eax
  int RolePtr; // esi

  result = (int)this->m_pSceneMgr;
  if ( result )
  {
    RolePtr = ((RoleSystem *)*(RoleSystem **)(result + 16))->GetRolePtr((unsigned __int8)this->m_bExecuteOpcode);
    return ((RoleSystem *)this->m_pSceneMgr->m_rect.left)->UpdatePathProgress(this->m_bRoleCmd_42ac80, (unsigned __int8)this->m_bExecuteOpcode, (char *)(__int64)((*pfVal - *(float *)(RolePtr + 128)) / flt_D8BEC4), (__int64)((pfVal[2] - *(float *)(RolePtr + 136)) / flt_D8BEC4), (char *)(__int64)((*pfVal2 - *(float *)(RolePtr + 128)) / flt_D8BEC4), (__int64)((pfVal2[2] - *(float *)(RolePtr + 136)) / flt_D8BEC4));
  }
  return result;
}

// 0x0042AF80
char PalScriptMgr::GetScriptState()
{
  char result; // al

  result = this->m_nCmdType;
  if ( result == 9 )
  {
    this->m_bBigMapState = 0;
  }
  else if ( result == 38 )
  {
    this->_todo_054 = 0;
  }
  return result;
}

// 0x0042AFA0
int PalScriptMgr::SaveExecutionState()
{
  RoleSystem *v1; // edi
  int RolePtr; // ebp
  __int64 v4; // rax
  int v5; // ecx
  char *v6; // eax
  double v7; // st7
  int v8; // edx
  float v9; // ecx
  float v10; // edx
  int v11; // ecx
  int v12; // eax
  char *v13; // edx
  int m_nCmdParam0; // ecx
  RoleSystem *m_pSceneMgr; // edx
  int v16; // eax
  PalScriptMgr *v17; // edi
  PalScriptMgr *v18; // eax
  PalScriptMgr *v19; // ebx
  int result; // eax
  int v21; // [esp-0x4] [ebp-0x28]
  int v22; // [esp+0x0] [ebp-0x24]
  float v23; // [esp+0x10] [ebp-0x14] BYREF
  char v24; // [esp+0x14] [ebp-0x10]
  char v25; // [esp+0x15] [ebp-0xF]
  float v26; // [esp+0x18] [ebp-0xC]
  int pPoint; // [esp+0x1C] [ebp-0x8] BYREF
  int v28; // [esp+0x20] [ebp-0x4]

  v1 = g_pRoleSystem;
  ((RoleSystem *)this)->ProcessAction();
  RolePtr = ((RoleSystem *)this->m_pSceneMgr->m_rect.left)->GetRolePtr(*(_DWORD *)v1->m_partyActor.m_szTexture);
  v4 = (__int64)((*(float *)&v1->m_id - *(float *)(RolePtr + 136)) / flt_D8BEC4);
  pPoint = (__int64)((*(float *)&v1->m_fontcolor.Color - *(float *)(RolePtr + 128)) / flt_D8BEC4);
  v28 = v4;
  if ( PointInRect((int *)&this->m_pCmdBuffer, &pPoint) )
  {
    switch ( this->m_nExecState )
    {
      case 0:
        v5 = v28;
        v6 = this->m_pCmdBuffer - 1;
        pPoint = (int)v6;
        goto LABEL_9;
      case 1:
        v5 = v28;
        v6 = (char *)(this->m_nLoopCountB + 1);
        pPoint = (int)v6;
        goto LABEL_9;
      case 2:
        v5 = this->m_nLoopCountA - 1;
        v28 = v5;
        goto LABEL_8;
      case 3:
        v5 = this->m_nLoopCountC + 1;
        v28 = v5;
        goto LABEL_8;
      default:
        v5 = v28;
LABEL_8:
        v6 = (char *)pPoint;
LABEL_9:
        v7 = 0.0;
        v23 = ((double)pPoint + 0.5) * flt_D8BEC4 + *(float *)(RolePtr + 128);
        v26 = ((double)v28 + 0.5) * flt_D8BEC4 + *(float *)(RolePtr + 136);
        if ( (int)v6 >= 0 )
        {
          v8 = *(_DWORD *)(RolePtr + 152);
          if ( (int)v6 < v8 && v5 >= 0 && v5 < *(_DWORD *)(RolePtr + 156) )
            v7 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (_DWORD)&v6[v5 * v8]);
        }
        v9 = v23;
        v10 = v26;
        *(float *)&v1->m_wndcolor.Color = v7;
        *(float *)&v1->m_fontcolor.Color = v9;
        *(float *)&v1->m_id = v10;
        v1->m_wndcolor.Color = 0;
        ((RoleSystem *)v1)->SetMoveSpeed(0.0, 0, v22);
        break;
    }
  }
  this->m_bBigMapState = 0;
  ((RoleSystem *)v1)->Notify();
  if ( this->m_nCmdValue == 2 && this->IsScriptReady() )
  {
    v11 = *(&this->m_bBigMapState + 1);
    v24 = -1;
    v12 = this->m_nExecState - 2;
    v13 = (char *)&v23 + v11;
    m_nCmdParam0 = (unsigned __int16)this->m_nCmdParam0;
    v23 = 9.3672217e-38;
    v25 = 0;
    LOBYTE(v12) = v13[3 * v12];
    m_pSceneMgr = this->m_pSceneMgr;
    *(&this->m_bBigMapState + 1) = v12;
    ((PalScript *)m_pSceneMgr->m_rect.left)->SetAction(m_nCmdParam0);
    v17 = (PalScriptMgr *)v16;
    LOWORD(v16) = this->m_nCmdParam1;
    ((PalScript *)this->m_pSceneMgr->m_rect.left)->SetAction(v16);
    v19 = v18;
    switch ( *(&this->m_bBigMapState + 1) )
    {
      case 0:
        ((PalScriptMgr *)v17)->SetPauseState(0);
        v21 = 0;
        goto LABEL_23;
      case 1:
        ((PalScriptMgr *)v17)->SetPauseState(1);
        break;
      case 2:
        v21 = 1;
LABEL_23:
        ((PalScriptMgr *)v19)->SetPauseState(v21);
        break;
    }
  }
  this->m_nExecuteBlock = LODWORD(this->m_fCamX);
  result = LODWORD(this->m_fCamY);
  this->m_nSavedDataA = result;
  this->m_nSavedDataB = LODWORD(this->m_fCamZ);
  return result;
}

// 0x0042B350
void PalScriptMgr::ProcessRoleLoading()
{
  Actor *SaveDataManager; // eax
  int v3; // eax
  double m_nCmdValue; // st7
  int v5; // eax
  int v6; // eax
  int v7; // edi
  char v8; // cl
  RoleSystem *v9; // eax
  const char *v10; // [esp-0xC] [ebp-0x14]
  int m_bScriptByte; // [esp-0x4] [ebp-0xC]
  int m_bExecuteOpcode; // [esp-0x4] [ebp-0xC]

  if ( this->m_nCmdType == 22 )
  {
    if ( *((_BYTE *)&this->m_nScriptID + 2) )
    {
      if ( this->m_bScriptByte != 0xFF )
      {
        m_bScriptByte = (unsigned __int8)this->m_bScriptByte;
        v10 = (const char *)UISceneUpdate();
        SaveDataManager = (Actor *)GetSaveDataManager();
        v3 = ((Actor *)SaveDataManager)->AddActionByName(v10, (const char *)&this->m_nScriptID + 2, m_bScriptByte);
        if ( v3 )
        {
          if ( *(_BYTE *)(v3 + 3) )
          {
            m_nCmdValue = (double)this->m_nCmdValue;
            v5 = *(_DWORD *)&this->m_nCmdParam0;
            this->m_bOpcodeFlag = 1;
            this->m_fCamY = m_nCmdValue;
            this->m_bBigMapState = 2;
            if ( v5 )
              ((RoleSystem *)this)->UpdateStateMode();
          }
        }
      }
    }
    ((PalScript *)this->m_pSceneMgr->m_rect.left)->SetAction(this->m_nCmdParam1);
    v7 = v6;
    if ( v6 )
    {
      v8 = *(_BYTE *)(v6 + 246);
      *(float *)(v6 + 44) = this->m_fCamY;
      if ( this->m_bExecuteOpcode != v8 )
      {
        ((RoleSystem *)v6)->ProcessAction();
        m_bExecuteOpcode = (unsigned __int8)this->m_bExecuteOpcode;
        v9 = (RoleSystem *)UISceneUpdate();
        *(_DWORD *)(v7 + 796) = ((RoleSystem *)v9)->NotifyPathEnd(m_bExecuteOpcode);
        ((RoleSystem *)v7)->ProcessAction();
        *(_BYTE *)(v7 + 246) = this->m_bExecuteOpcode;
      }
      if ( this->m_nSavedPosX )
        g_pRoleSystem->m_fPosY = this->m_fCamY;
    }
  }
}

// 0x0042B450
BOOL PalScriptMgr::IsPosInBounds(float *pfPos)
{
  int RolePtr; // esi
  int v5; // ebx
  double v6; // st7
  __int64 v7; // rax

  if ( !pfPos )
    return 0;
  if ( (unsigned __int8)this->m_bExecuteOpcode != *((_DWORD *)pfPos + 157) )
    return 0;
  RolePtr = ((RoleSystem *)this->m_pSceneMgr->m_rect.left)->GetRolePtr((unsigned __int8)this->m_bExecuteOpcode);
  v5 = (__int64)((pfPos[1] - *(float *)(RolePtr + 128)) / flt_D8BEC4);
  v6 = (pfPos[3] - *(float *)(RolePtr + 136)) / flt_D8BEC4;
  v7 = (__int64)v6;
  return v5 >= 0
      && v5 < *(_DWORD *)(RolePtr + 152)
      && (int)v7 >= 0
      && (int)v7 < *(_DWORD *)(RolePtr + 156)
      && ((RoleSystem *)this->m_pSceneMgr)->GetTile(v5, (__int64)v6) == this->m_bRoleCmd_42ac80;
}

// 0x0042B5B0
double PalScriptMgr::UpdateScriptRoles(double thisa, int nVal, int nVal2)
{
  char m_nCmdType; // al
  const char *v6; // eax
  char v7; // al
  char *v8; // eax
  int v9; // eax
  int m_nCmdValue; // ecx
  int m_nCmdParam2; // edx
  double result; // st7
  float v13; // eax
  char *v14; // edi
  int v15; // ebx
  int *p_m_RoleAnimData; // eax
  int *p_m_nCmdValue; // eax
  int v18; // ecx
  _BYTE *v19; // eax
  float *v20; // ecx
  float *p_m_fPrevPosY; // eax
  float v22; // edx
  signed __int16 *v23; // eax
  _BYTE *p_m_bRunCommand; // eax
  int *v25; // eax
  int v26; // ecx
  int m_Sub_0034; // eax
  int m_nScriptDepth; // eax
  float v29; // ecx
  int *v30; // eax
  float v31; // eax
  int v32; // eax
  int v33; // edx
  int v34; // edi
  LONG left; // ebx
  PalScriptMgr *v36; // ebp
  RoleSystem *m_pSceneMgr; // ecx
  int v38; // [esp+0x8] [ebp-0x1BC]
  OpenBaseFile v39; // [esp+0xC] [ebp-0x1B8] BYREF
  int nY; // [esp+0x10] [ebp-0x1B4]
  int p_DWORD; // [esp+0x14] [ebp-0x1B0] BYREF
  float m_fCamY; // [esp+0x18] [ebp-0x1AC]
  float m_fCamZ; // [esp+0x1C] [ebp-0x1A8]
  gbMatrix4 v44; // [esp+0x20] [ebp-0x1A4] BYREF
  float v45; // [esp+0x64] [ebp-0x160]
  gbMatrix4 pMatrix; // [esp+0x6C] [ebp-0x158] BYREF
  float v47; // [esp+B0h] [ebp-0x114]
  char Buffer[256]; // [esp+B8h] [ebp-0x10C] BYREF
  int v49; // [esp+0x1C0] [ebp-0x4]

  m_nCmdType = this->m_nCmdType;
  if ( m_nCmdType != 23 || *(_DWORD *)&this->m_nCmdParam1 != 2 )
  {
    if ( m_nCmdType != 11 || !this->m_pScriptObj && (v6 = (const char *)UISceneUpdate(), _strcmpi(v6, "m02")) )
    {
      v7 = this->m_nCmdType;
      if ( v7 != 11 || this->m_nCmdValue > 0 )
      {
        if ( v7 == 40 && *(_BYTE *)(LODWORD(thisa) + 74) != this->m_bExecuteOpcode )
        {
          ((RoleSystem *)this)->ProcessAction();
          v8 = ((RoleSystem *)this->m_pSceneMgr->m_rect.left)->NotifyPathEnd(*(unsigned __int8 *)(LODWORD(thisa) + 74));
          this->m_pSceneMgr = (RoleSystem *)v8;
          ((RoleSystem *)*((RoleSystem **)v8 + 4))->GetRolePtr(*(unsigned __int8 *)(LODWORD(thisa) + 74));
          v9 = *(unsigned __int8 *)(LODWORD(thisa) + 74);
          if ( *(_BYTE *)(LODWORD(thisa) + 74) )
          {
            m_nCmdValue = *(_DWORD *)&this->m_nCmdParam1;
            m_nCmdParam2 = this->m_nCmdParam2;
          }
          else
          {
            m_nCmdValue = this->m_nCmdValue;
            m_nCmdParam2 = *(_DWORD *)&this->m_nCmdParam0;
          }
          nY = m_nCmdParam2;
          p_DWORD = LODWORD(this->m_fCamX);
          m_fCamY = this->m_fCamY;
          m_fCamZ = this->m_fCamZ;
          m_fCamY = ((Scene *)this->m_pSceneMgr->m_rect.left)->GetTileHeight(v9, m_nCmdValue, m_nCmdParam2, 0);
          this->BuildCmdTransform(&pMatrix);
          result = v47 + m_fCamY;
          v13 = m_fCamZ;
          LODWORD(this->m_fCamX) = p_DWORD;
          this->m_fCamZ = v13;
          this->m_fCamY = result;
          this->m_bExecuteOpcode = *(_BYTE *)(LODWORD(thisa) + 74);
          ((RoleSystem *)this)->ProcessAction();
        }
        v14 = &this->m_szScriptFile[4];
        v15 = LODWORD(thisa) - (_DWORD)&this->m_szScriptFile[4];
        *(_DWORD *)&this->m_szScriptFile[4] = *(_DWORD *)LODWORD(thisa);
        p_m_RoleAnimData = &this->m_RoleAnimData;
        do
        {
          *(_BYTE *)p_m_RoleAnimData = *((_BYTE *)p_m_RoleAnimData + v15);
          p_m_RoleAnimData = (int *)((char *)p_m_RoleAnimData + 1);
        }
        while ( (unsigned int)p_m_RoleAnimData - 4 - (unsigned int)&this->m_szScriptFile[4] < 0x20 );
        this->m_pSavedIndex = *(_BYTE *)(LODWORD(thisa) + 36);
        this->m_bOpcodeFlag = *(_BYTE *)(LODWORD(thisa) + 37);
        this->m_nExecuteBlock = *(_DWORD *)(LODWORD(thisa) + 40);
        this->m_nSavedDataA = *(_DWORD *)(LODWORD(thisa) + 44);
        this->m_nSavedDataB = *(_DWORD *)(LODWORD(thisa) + 48);
        this->m_fAngle = *(float *)(LODWORD(thisa) + 52);
        this->m_nExecRangeA = *(_DWORD *)(LODWORD(thisa) + 56);
        this->m_nExecRangeB = *(_DWORD *)(LODWORD(thisa) + 60);
        this->m_nExecRangeC = *(_DWORD *)(LODWORD(thisa) + 64);
        this->m_nExecRangeD = *(_DWORD *)(LODWORD(thisa) + 68);
        this->m_nCmdType = *(_BYTE *)(LODWORD(thisa) + 72);
        this->_todo_0F5 = *(_BYTE *)(LODWORD(thisa) + 73);
        this->m_bExecuteOpcode = *(_BYTE *)(LODWORD(thisa) + 74);
        this->_todo_0F7 = *(_BYTE *)(LODWORD(thisa) + 75);
        p_m_nCmdValue = &this->m_nCmdValue;
        v18 = 6;
        do
        {
          *p_m_nCmdValue = *(int *)((char *)p_m_nCmdValue + v15);
          ++p_m_nCmdValue;
          --v18;
        }
        while ( v18 );
        this->_todo_110 = *(_BYTE *)(LODWORD(thisa) + 100);
        this->_todo_112 = *(_WORD *)(LODWORD(thisa) + 102);
        this->m_Actor = *(_WORD *)(LODWORD(thisa) + 104);
        this->_todo_116 = *(_WORD *)(LODWORD(thisa) + 106);
        this->m_nField_0118 = *(_WORD *)(LODWORD(thisa) + 108);
        this->_todo_11A = *(_BYTE *)(LODWORD(thisa) + 110);
        v19 = &this->_todo_11A + 1;
        do
        {
          *v19 = v19[v15];
          ++v19;
        }
        while ( (unsigned int)&v19[-111 - (_DWORD)v14] < 0x10 );
        this->m_pScriptObj = *(PalScriptMgr **)(LODWORD(thisa) + 128);
        this->m_nScriptDepth = *(_DWORD *)(LODWORD(thisa) + 132);
        v20 = (float *)(LODWORD(thisa) + 136);
        p_m_fPrevPosY = &this->m_fPrevPosY;
        v38 = 16;
        v39.m_plastsys = (gbVFileSystem *)(LODWORD(thisa) + 132 - (_DWORD)&this->m_nScriptDepth);
        do
        {
          v22 = *v20;
          v20 += 3;
          *(p_m_fPrevPosY - 1) = v22;
          *p_m_fPrevPosY = *(float *)((char *)&v39.m_plastsys->IsInit + (unsigned int)p_m_fPrevPosY);
          p_m_fPrevPosY[1] = *(v20 - 1);
          p_m_fPrevPosY += 3;
          --v38;
        }
        while ( v38 );
        this->m_nScriptID = *(_WORD *)(LODWORD(thisa) + 328);
        v23 = &this->m_nScriptID + 1;
        do
        {
          *(_BYTE *)v23 = *((_BYTE *)v23 + v15);
          v23 = (signed __int16 *)((char *)v23 + 1);
        }
        while ( (unsigned int)v23 - 330 - (unsigned int)v14 < 0x20 );
        this->m_bScriptByte = *(_BYTE *)(LODWORD(thisa) + 362);
        ((gbVec3D *)&this->m_fPosAX)->operator=(LODWORD(thisa) + 364);
        ((gbVec3D *)&this->m_fPosBX)->operator=(LODWORD(thisa) + 376);
        this->m_nMatrixData = *(_DWORD *)(LODWORD(thisa) + 388);
        p_m_bRunCommand = &this->m_bRunCommand;
        do
        {
          *p_m_bRunCommand = p_m_bRunCommand[v15];
          ++p_m_bRunCommand;
        }
        while ( (unsigned int)&p_m_bRunCommand[-392 - (_DWORD)v14] < 8 );
        this->_todo_23C = *(_DWORD *)(LODWORD(thisa) + 400);
        this->m_bInputBlock = *(_DWORD *)(LODWORD(thisa) + 404);
        this->m_bRoleLock = *(_DWORD *)(LODWORD(thisa) + 408);
        v25 = &this->m_bRoleLock + 1;
        v26 = 52;
        do
        {
          *v25 = *(int *)((char *)v25 + v15);
          ++v25;
          --v26;
        }
        while ( v26 );
        m_Sub_0034 = this->m_Sub_0034;
        *(_QWORD *)&this->m_Sub_0034 = *(_QWORD *)HIDWORD(thisa);
        *(_QWORD *)&this->m_fField3C = *(_QWORD *)(HIDWORD(thisa) + 8);
        *(_QWORD *)&this->m_fField44 = *(_QWORD *)(HIDWORD(thisa) + 16);
        this->m_scepath = *(scSCEFile **)(HIDWORD(thisa) + 24);
        *(_WORD *)&this->m_bBigMapState = *(_WORD *)(HIDWORD(thisa) + 28);
        this->_todo_054 = *(_DWORD *)(HIDWORD(thisa) + 32);
        this->m_Sub_0034 = m_Sub_0034;
        switch ( this->m_nCmdType )
        {
          case 5:
            if ( this->m_nCmdValue == 1 || *(_BYTE *)(HIDWORD(thisa) + 28) != 3 )
              goto LABEL_31;
            ((RoleSystem *)this)->ProcessAction();
            m_nScriptDepth = this->m_nScriptDepth;
            v29 = *((float *)&this->m_nScriptCount + 3 * m_nScriptDepth);
            v30 = &this->m_nScriptCount + 3 * m_nScriptDepth;
            this->m_fCamX = v29;
            LODWORD(this->m_fCamY) = v30[1];
            LODWORD(this->m_fCamZ) = v30[2];
            ((RoleSystem *)this)->ProcessAction();
            this->m_bBigMapState = *(_BYTE *)(HIDWORD(thisa) + 28);
            goto LABEL_78;
          case 7:
            v31 = *(float *)&this->m_nExecHandle;
            v39.m_plastsys = (gbVFileSystem *)LODWORD(this->m_fAngle);
            this->m_fAngle = v31;
            ((RoleSystem *)this)->ProcessAction();
            LODWORD(this->m_fAngle) = (OpenBaseFile)v39.m_plastsys;
            break;
          case 0xB:
          case 0x22:
LABEL_31:
            ((RoleSystem *)this)->ProcessAction();
            LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
            LODWORD(this->m_fCamY) = this->m_nSavedDataA;
            LODWORD(this->m_fCamZ) = this->m_nSavedDataB;
            break;
          case 0xC:
            if ( !this->m_szScriptFile[5] )
              break;
            goto LABEL_78;
          case 0x11:
            if ( *(_DWORD *)&this->m_nCmdParam0 && this->m_bBigMapState == 1 && this->_todo_058 == 3 )
              goto LABEL_39;
            goto LABEL_78;
          case 0x13:
            if ( this->m_bBigMapState == 1 )
            {
LABEL_39:
              (*(void ( **)(char *, int))(*(_DWORD *)this->m_pExecSystem + 24))(
                this->m_pExecSystem,
                -1082130432);
              ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(0.0);
            }
            goto LABEL_78;
          case 0x16:
            if ( *(_BYTE *)(HIDWORD(thisa) + 28) == 2 )
            {
              result = (double)this->m_nCmdValue;
              v32 = *(_DWORD *)&this->m_nCmdParam0;
              this->m_bOpcodeFlag = 1;
              this->m_fCamY = result;
              if ( v32 )
                ((RoleSystem *)this)->UpdateStateMode();
              this->m_bBigMapState = *(_BYTE *)(HIDWORD(thisa) + 28);

            }
            goto LABEL_78;
          case 0x17:
            if ( !this->m_bExecuteBlock )
            {
              ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(0.0);
              (*(void ( **)(char *, int))(*(_DWORD *)this->m_pExecSystem + 24))(
                this->m_pExecSystem,
                -1082130432);
              ((PalScript *)&this->_todo_058)->GetCount(0);
            }
            if ( this->m_nCmdValue && this->m_bScriptPause )
            {
              ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(0.0);
              (*(void ( **)(char *, int))(*(_DWORD *)this->m_pExecSystem + 24))(
                this->m_pExecSystem,
                -1082130432);
              ((PalScript *)&this->_todo_058)->GetCount(0);
            }
            if ( *(_DWORD *)&this->m_nCmdParam1 == 1 )
            {
              LOBYTE(dword_D8BC38) = this->m_bScriptPause == 0;
              ((ScriptVM *)this)->OpenSceneScript();
              v34 = 0;
              left = this->m_pSceneMgr->m_rect.left;
              if ( *(int *)(left + 220) > 0 )
              {
                v36 = (PalScriptMgr *)(left + 224);
                do
                {
                  if ( v36->m_nCmdType == 37 )
                    ((PalScriptMgr *)v36)->LoadSceneGeometry(dword_D8BC38);
                  ++v34;
                  v36 = (PalScriptMgr *)((char *)v36 + 896);
                }
                while ( v34 < *(_DWORD *)(left + 220) );
              }
            }
            goto LABEL_78;
          case 0x18:
            if ( *(_DWORD *)&this->m_nCmdParam0 == 1 )
            {
              v33 = this->m_nCmdValue;
              m_fCamY = 0.0;
              m_fCamZ = 0.0;
              p_DWORD = v33;
              if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD) )
                this->m_szScriptFile[5] = 0;
            }
            goto LABEL_78;
          case 0x1A:
            if ( *(_BYTE *)(HIDWORD(thisa) + 28) != 1 )
              goto LABEL_78;
            if ( *(&this->m_bBigMapState + 1) >= 3u )
            {
              sprintf(
                Buffer,
                "object\\wz20_%d.cvd",
                this->m_szScriptFile[strlen((const char *)&this->m_RoleAnimData) + 3] - 48);
              v49 = 0;
              ((GeomNode *)&this->_todo_058)->InitFromFile((const gbGeomNode *)Buffer, 0);
              v49 = -1;
            }
            ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(0.0);
            (*(void ( **)(char *, int))(*(_DWORD *)this->m_pExecSystem + 24))(
              this->m_pExecSystem,
              -1082130432);
            ((PalScript *)&this->_todo_058)->GetCount(0);
            break;
          case 0x1E:
            if ( this->m_bBigMapState == 3 )
            {
              this->BuildCmdTransform(&v44);
              result = this->m_fCamY - v45;
              this->m_fCamY = result;
            }
            this->m_bOpcodeFlag = this->m_bScriptPause;
            goto LABEL_78;
          case 0x1F:
            if ( (!this->m_szScriptFile[5] || this->m_bBigMapState == 2)
              && !_strcmpi((const char *)this->m_pSceneMgr->m_rect.left, "m09") )
            {
              ((RoleSystem *)this)->SetTileTypeVisible(2, 1);
            }
            goto LABEL_78;
          case 0x21:
            LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
            LODWORD(this->m_fCamY) = this->m_nSavedDataA;
            LODWORD(this->m_fCamZ) = this->m_nSavedDataB;
            goto LABEL_78;
          case 0x24:
            if ( this->m_bBigMapState != 2 )
              goto LABEL_78;
            LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
            LODWORD(this->m_fCamY) = this->m_nSavedDataA;
            LODWORD(this->m_fCamZ) = this->m_nSavedDataB;
            m_pSceneMgr = this->m_pSceneMgr;
            this->m_bOpcodeFlag = 0;
            ((RoleSystem *)m_pSceneMgr)->GetCurrentID(&this->m_nExecRangeA, 255);
            break;
          case 0x29:
            if ( *(_BYTE *)(HIDWORD(thisa) + 28) != 2 )
              goto LABEL_78;
            ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(0.0);
            (*(void ( **)(char *, int))(*(_DWORD *)this->m_pExecSystem + 24))(
              this->m_pExecSystem,
              -1082130432);
            ((PalScript *)&this->_todo_058)->GetCount(0);
            break;
          default:
            goto LABEL_78;
        }
        ((RoleSystem *)this)->ProcessAction();
LABEL_78:
        if ( this->m_bRoleLock )
        {
          LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
          LODWORD(this->m_fCamY) = this->m_nSavedDataA;
          LODWORD(this->m_fCamZ) = this->m_nSavedDataB;
        }
      }
    }
  }
  return result;
}

// 0x0042BEA0
void PalScriptMgr::OnAnimFinish()
{
  if ( this->_todo_058 == 3 )
  {
    ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(2.0);
    (*(void ( **)(char *, _DWORD))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, 0);
    this->m_bBigMapState = 2;

  }
}

// 0x0042BEF0
void PalScriptMgr::HandleGetItem(int nSkillGDBID)
{
  char *v1; // eax
  CScreenMode *Instance; // eax
  int v3; // [esp-0x4] [ebp-0x110]
  int *pConfig[2]; // [esp+0x0] [ebp-0x10C] BYREF
  int SkillNum; // [esp+0x8] [ebp-0x104]
  char Buffer[256]; // [esp+0xC] [ebp-0x100] BYREF

  pConfig[0] = (int *)nSkillGDBID;
  pConfig[1] = (int *)1;
  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nSkillGDBID);
  if ( SkillNum )
  {
    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)pConfig, pConfig[0]);
    v3 = SkillNum + 4;
    v1 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("getitem");
    _snprintf(Buffer, 0xFFu, v1, v3);
    ((InputSystem *)Buffer)->ProcessFrame();
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa006", 1);
  }
}

// 0x0042BF90
PalScriptMgr * PalScriptMgr::ExecuteScriptByID()
{
  signed __int16 m_nScriptID; // ax
  PalScriptMgr *v2; // eax
  PalScriptMgr *v3; // esi

  m_nScriptID = this->m_nScriptID;
  if ( m_nScriptID == -1 )
    return 0;
  ((PalScript *)this->m_pSceneMgr->m_rect.left)->SetAction(m_nScriptID);
  v3 = v2;
  if ( !v2 )
    return 0;
  ((PalScriptMgr *)v2)->ExecuteBlock();
  return v3;
}

// 0x0042BFE0
bool PalScriptMgr::IsScriptReady()
{
  int m_nExecState; // ecx

  if ( *(&this->m_bBigMapState + 1) )
  {
    if ( *(&this->m_bBigMapState + 1) == 1 )
      return this->m_nExecState == 2;
    else
      return *(&this->m_bBigMapState + 1) != 2 || this->m_nExecState == 3;
  }
  else
  {
    m_nExecState = this->m_nExecState;
    return m_nExecState == 2 || m_nExecState == 3;
  }
}

// 0x0042C030
void PalScriptMgr::SetPauseState(int bPause)
{
  double v3; // st7
  gbMatrix4 pMatrix; // [esp+0x4] [ebp-0x4C] BYREF
  float v5; // [esp+0x48] [ebp-0x8]

  if ( bPause != (unsigned __int8)this->m_bScriptPause )
  {
    this->m_bScriptPause = bPause;
    if ( (_BYTE)bPause )
      this->m_bBigMapState = 1;
    else
      this->m_bBigMapState = 2;
    this->_todo_054 = 0;
    this->m_nFrameCounter = LODWORD(this->m_fCamX);
    this->m_fField3C = this->m_fCamY;
    this->m_pBigMapSce = (scSCEFile *)LODWORD(this->m_fCamZ);
    this->BuildCmdTransform(&pMatrix);
    v3 = v5 - 2.0;
    this->m_bOpcodeFlag = this->m_bScriptPause;
    this->m_fField44 = v3;

  }
}

// 0x0042C280
gbVFileSystem * PalScriptMgr::LoadSceneGeometry(char bNoPol)
{
  LONG left; // ecx
  gbVFileSystem *result; // eax
  char v5; // [esp+0x7] [ebp-0x115] BYREF
  OpenSceneFile v6; // [esp+0x8] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0xC] [ebp-0x110] BYREF
  int v8; // [esp+0x118] [ebp-0x4]

  if ( this->_todo_058 )
    ((RoleSystem *)this)->ProcessAction();
  sprintf(Buffer, "%s%s", "scene\\", (const char *)this->m_pSceneMgr->m_rect.left);
  left = this->m_pSceneMgr->m_rect.left;
  v8 = 0;
  sprintf(Buffer, "%s\\%s", (const char *)(left + 64), (const char *)&this->m_RoleAnimData);
  if ( !bNoPol )
    strcpy(&v5 + strlen(Buffer), a2Pol);
  ((GeomNode *)&this->_todo_058)->InitFromFile((const gbGeomNode *)Buffer, 0);
  ((RoleSystem *)this)->ProcessAction();
  this->m_bOpcodeFlag = bNoPol;
  v8 = -1;
  ((OpenSceneFile *)&v6)->_OpenSceneFile();
  return result;
}

// 0x0042C3A0
bool PalScriptMgr::IsInputBlocked()
{
  bool result; // al

  if ( this->m_bInputBlock || this->m_bRoleLock )
    return 1;
  switch ( this->m_nCmdType )
  {
    case 0:
      result = ((UIScene *)"m22")->ProcessInput(pszName2);
      break;
    case 1:
    case 2:
    case 3:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x12:
    case 0x15:
    case 0x19:
    case 0x1B:
    case 0x2A:
    case 0x2B:
      result = 0;
      break;
    case 0x11:
      result = *(_DWORD *)&this->m_nCmdParam0 == 1;
      break;
    default:
      return 1;
  }
  return result;
}

// 0x0042C440
void PalScriptMgr::RunCommand()
{
  const char *p_m_bRunCommand; // edi
  int todo_058; // ecx
  CScreenMode *Instance; // eax
  _DWORD pData[4]; // [esp+0x8] [ebp-0x10] BYREF
  int v5; // [esp+0x1C] [ebp+0x4]

  memset(pData, 0, sizeof(pData));
  p_m_bRunCommand = &this->m_bRunCommand;
  if ( !this->m_bRunCommand )
  {
    switch ( this->m_nCmdType )
    {
      case 3:
        goto LABEL_4;
      case 4:
        todo_058 = this->_todo_058;
        if ( todo_058 != 3 )
          goto LABEL_20;
LABEL_4:
        p_m_bRunCommand = "wg006";
        break;
      case 6:
        p_m_bRunCommand = "wg007";
        break;
      case 7:
        p_m_bRunCommand = "wg004";
        break;
      case 0xB:
        p_m_bRunCommand = "We025";
        break;
      case 0xC:
        switch ( this->m_nCmdValue )
        {
          case 0:
            p_m_bRunCommand = "We026";
            goto LABEL_30;
          case 1:
            p_m_bRunCommand = "We027";
            goto LABEL_30;
          case 2:
            p_m_bRunCommand = "We028";
            goto LABEL_30;
          case 3:
            p_m_bRunCommand = "We029";
            goto LABEL_30;
          case 4:
            p_m_bRunCommand = "We030";
            goto LABEL_30;
          default:
            goto LABEL_31;
        }
        goto LABEL_31;
      case 0xD:
        p_m_bRunCommand = "Wb002";
        break;
      case 0x13:
        p_m_bRunCommand = "Wg001";
        break;
      case 0x16:
      case 0x1E:
        goto LABEL_24;
      case 0x1A:
        if ( v5 )
          goto LABEL_29;
        p_m_bRunCommand = "wa004";
        break;
      case 0x1C:
        todo_058 = this->_todo_058;
        if ( todo_058 == 3 )
        {
          p_m_bRunCommand = "wg010";
          break;
        }
LABEL_20:
        if ( todo_058 != 2 )
          goto LABEL_31;
LABEL_21:
        p_m_bRunCommand = "wg009";
        break;
      case 0x1D:
        if ( v5 )
          p_m_bRunCommand = "We026";
        else
LABEL_24:
          p_m_bRunCommand = "Wg005";
        break;
      case 0x1F:
        p_m_bRunCommand = "Wc007";
        break;
      case 0x20:
        p_m_bRunCommand = "WG008";
        break;
      case 0x22:
        p_m_bRunCommand = "wg005";
        break;
      case 0x24:
        goto LABEL_21;
      case 0x27:
        p_m_bRunCommand = "wc014";
        break;
      case 0x29:
LABEL_29:
        p_m_bRunCommand = "wg011";
        break;
      default:
        goto LABEL_31;
    }
  }
LABEL_30:
  strcpy((char *)pData, p_m_bRunCommand);
LABEL_31:
  if ( LOBYTE(pData[0]) )
  {
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(pData, 1);
  }
}

// 0x0042CF60
int PalScriptMgr::CmdPushCmd04(int nVal, unsigned __int8 pData)
{
  PalScriptMgr **p_m_pSubScriptB; // ebx
  int m_nWaitCount; // eax
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  int result; // eax
  PalScriptMgr *v9; // esi
  PalScriptMgr *v10; // eax
  float v11; // ecx
  float v12; // edx
  float x; // eax
  PalScriptMgr *v14; // esi
  unsigned int v15; // eax
  PalScriptMgr *v16; // eax
  float v17; // edx
  float v18; // ecx
  PalScriptMgr *v19; // edx
  int v20; // edi
  gbVec3D *RoleName; // eax
  PalScriptMgr *v22; // edi
  float y; // ecx
  float z; // eax
  PalScriptMgr *v25; // ecx
  int v26; // ecx
  gbVec3D v27; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v28; // [esp+0x18] [ebp-0x50]
  _DWORD v29[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v29);
  p_m_pSubScriptB = &this->m_pSubScriptB;
  v29[15] = pData;
  LOBYTE(v29[0]) = 4;
  m_nWaitCount = this->m_nWaitCount;
  v29[16] = nVal;
  if ( !m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v9 = (PalScriptMgr *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v15 = (unsigned int)p_m_pSubScriptB[8];
      if ( v15 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v20 = ((int)(v15 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v20);
        v22 = (PalScriptMgr *)(&RoleName->x + v20);
        *(_DWORD *)&v22->m_bGetSceneScript = v9;
        ((gbVec3D *)&v27)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v27.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v27.x);
        z = v27.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v25 = v28;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v25;
        v26 = *(_DWORD *)&v22->m_bGetSceneScript + 4028;
        p_m_pSubScriptB[5] = *(PalScriptMgr **)&v22->m_bGetSceneScript;
        p_m_pSubScriptB[6] = (PalScriptMgr *)v26;
        p_m_pSubScriptB[7] = v9;
        p_m_pSubScriptB[8] = v22;
      }
      else
      {
        v16 = (PalScriptMgr *)(v15 + 4);
        p_m_pSubScriptB[8] = v16;
        *(_DWORD *)&v16->m_bGetSceneScript = v9;
        ((gbVec3D *)&v27)->Copy((int)v9, (gbVec3D *)p_m_pSubScriptB[8]);
        v17 = v27.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v27.x);
        v18 = v27.z;
        *((float *)p_m_pSubScriptB + 6) = v17;
        v19 = v28;
        *((float *)p_m_pSubScriptB + 7) = v18;
        p_m_pSubScriptB[8] = v19;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v10 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v10;
      v10->m_script.m_pData = &v9->m_bGetSceneScript;
      ((gbVec3D *)&v27)->Copy((int)(&v9->m_ctrlParabola + 15), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      v11 = v27.y;
      v12 = v27.z;
      x = v27.x;
      v14 = v28;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v27.x);
      *((float *)p_m_pSubScriptB + 2) = v11;
      *((float *)p_m_pSubScriptB + 3) = v12;
      p_m_pSubScriptB[4] = v14;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v11;
      *((float *)p_m_pSubScriptB + 7) = v12;
      p_m_pSubScriptB[8] = v14;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = (int)(&p_m_pSubScriptB[11]->m_bGetSceneScript + 1);
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v29, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v29, 0x4Cu);
  ((ScriptVM *)p_m_pSubScriptB)->GetString();
  result = this->m_nWaitCount + 1;
  this->m_nWaitCount = result;
  return result;
}

// 0x0042D130
int PalScriptMgr::CmdPushCmd05(unsigned __int8 pData)
{
  PalScriptMgr **p_m_pSubScriptB; // ebx
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  int result; // eax
  PalScriptMgr *v7; // esi
  PalScriptMgr *v8; // eax
  float x; // eax
  float v10; // ecx
  PalScriptMgr *v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  PalScriptMgr *v14; // eax
  float v15; // edx
  float v16; // ecx
  PalScriptMgr *v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  PalScriptMgr *v20; // edi
  float y; // ecx
  float z; // eax
  PalScriptMgr *v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v27);
  p_m_pSubScriptB = &this->m_pSubScriptB;
  LOBYTE(v27[0]) = 5;
  v27[15] = pData;
  if ( !this->m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v7 = (PalScriptMgr *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v13 = (unsigned int)p_m_pSubScriptB[8];
      if ( v13 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v18 = ((int)(v13 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v18);
        v20 = (PalScriptMgr *)(&RoleName->x + v18);
        *(_DWORD *)&v20->m_bGetSceneScript = v7;
        ((gbVec3D *)&v25)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v25.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v23 = v26;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v23;
        v24 = *(_DWORD *)&v20->m_bGetSceneScript + 4028;
        p_m_pSubScriptB[5] = *(PalScriptMgr **)&v20->m_bGetSceneScript;
        p_m_pSubScriptB[6] = (PalScriptMgr *)v24;
        p_m_pSubScriptB[7] = v7;
        p_m_pSubScriptB[8] = v20;
      }
      else
      {
        v14 = (PalScriptMgr *)(v13 + 4);
        p_m_pSubScriptB[8] = v14;
        *(_DWORD *)&v14->m_bGetSceneScript = v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)p_m_pSubScriptB[8]);
        v15 = v25.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_pSubScriptB + 6) = v15;
        v17 = v26;
        *((float *)p_m_pSubScriptB + 7) = v16;
        p_m_pSubScriptB[8] = v17;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v8 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v8;
      v8->m_script.m_pData = &v7->m_bGetSceneScript;
      ((gbVec3D *)&v25)->Copy((int)(&v7->m_ctrlParabola + 15), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v25.x);
      *((float *)p_m_pSubScriptB + 2) = v10;
      *((float *)p_m_pSubScriptB + 3) = v12;
      p_m_pSubScriptB[4] = v11;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v10;
      *((float *)p_m_pSubScriptB + 7) = v12;
      p_m_pSubScriptB[8] = v11;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = (int)(&p_m_pSubScriptB[11]->m_bGetSceneScript + 1);
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v27, 0x4Cu);
  ((ScriptVM *)p_m_pSubScriptB)->GetString();
  result = this->m_nWaitCount + 1;
  this->m_nWaitCount = result;
  return result;
}

// 0x0042D2F0
int PalScriptMgr::CmdPushCmd07(unsigned __int8 pData)
{
  PalScriptMgr **p_m_pSubScriptB; // ebx
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  int result; // eax
  PalScriptMgr *v7; // esi
  PalScriptMgr *v8; // eax
  float x; // eax
  float v10; // ecx
  PalScriptMgr *v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  PalScriptMgr *v14; // eax
  float v15; // edx
  float v16; // ecx
  PalScriptMgr *v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  PalScriptMgr *v20; // edi
  float y; // ecx
  float z; // eax
  PalScriptMgr *v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v27);
  p_m_pSubScriptB = &this->m_pSubScriptB;
  LOBYTE(v27[0]) = 7;
  v27[15] = pData;
  if ( !this->m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v7 = (PalScriptMgr *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v13 = (unsigned int)p_m_pSubScriptB[8];
      if ( v13 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v18 = ((int)(v13 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v18);
        v20 = (PalScriptMgr *)(&RoleName->x + v18);
        *(_DWORD *)&v20->m_bGetSceneScript = v7;
        ((gbVec3D *)&v25)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v25.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v23 = v26;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v23;
        v24 = *(_DWORD *)&v20->m_bGetSceneScript + 4028;
        p_m_pSubScriptB[5] = *(PalScriptMgr **)&v20->m_bGetSceneScript;
        p_m_pSubScriptB[6] = (PalScriptMgr *)v24;
        p_m_pSubScriptB[7] = v7;
        p_m_pSubScriptB[8] = v20;
      }
      else
      {
        v14 = (PalScriptMgr *)(v13 + 4);
        p_m_pSubScriptB[8] = v14;
        *(_DWORD *)&v14->m_bGetSceneScript = v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)p_m_pSubScriptB[8]);
        v15 = v25.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_pSubScriptB + 6) = v15;
        v17 = v26;
        *((float *)p_m_pSubScriptB + 7) = v16;
        p_m_pSubScriptB[8] = v17;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v8 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v8;
      v8->m_script.m_pData = &v7->m_bGetSceneScript;
      ((gbVec3D *)&v25)->Copy((int)(&v7->m_ctrlParabola + 15), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v25.x);
      *((float *)p_m_pSubScriptB + 2) = v10;
      *((float *)p_m_pSubScriptB + 3) = v12;
      p_m_pSubScriptB[4] = v11;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v10;
      *((float *)p_m_pSubScriptB + 7) = v12;
      p_m_pSubScriptB[8] = v11;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = (int)(&p_m_pSubScriptB[11]->m_bGetSceneScript + 1);
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v27, 0x4Cu);
  ((ScriptVM *)p_m_pSubScriptB)->GetString();
  result = this->m_nWaitCount + 1;
  this->m_nWaitCount = result;
  return result;
}

// 0x0042D830
int PalScriptMgr::CmdPushCmd10(unsigned __int8 pData)
{
  PalScriptMgr **p_m_pSubScriptB; // ebx
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  int result; // eax
  PalScriptMgr *v7; // esi
  PalScriptMgr *v8; // eax
  float x; // eax
  float v10; // ecx
  PalScriptMgr *v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  PalScriptMgr *v14; // eax
  float v15; // edx
  float v16; // ecx
  PalScriptMgr *v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  PalScriptMgr *v20; // edi
  float y; // ecx
  float z; // eax
  PalScriptMgr *v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v27);
  p_m_pSubScriptB = &this->m_pSubScriptB;
  LOBYTE(v27[0]) = 10;
  v27[15] = pData;
  if ( !this->m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v7 = (PalScriptMgr *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v13 = (unsigned int)p_m_pSubScriptB[8];
      if ( v13 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v18 = ((int)(v13 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v18);
        v20 = (PalScriptMgr *)(&RoleName->x + v18);
        *(_DWORD *)&v20->m_bGetSceneScript = v7;
        ((gbVec3D *)&v25)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v25.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v23 = v26;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v23;
        v24 = *(_DWORD *)&v20->m_bGetSceneScript + 4028;
        p_m_pSubScriptB[5] = *(PalScriptMgr **)&v20->m_bGetSceneScript;
        p_m_pSubScriptB[6] = (PalScriptMgr *)v24;
        p_m_pSubScriptB[7] = v7;
        p_m_pSubScriptB[8] = v20;
      }
      else
      {
        v14 = (PalScriptMgr *)(v13 + 4);
        p_m_pSubScriptB[8] = v14;
        *(_DWORD *)&v14->m_bGetSceneScript = v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)p_m_pSubScriptB[8]);
        v15 = v25.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_pSubScriptB + 6) = v15;
        v17 = v26;
        *((float *)p_m_pSubScriptB + 7) = v16;
        p_m_pSubScriptB[8] = v17;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v8 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v8;
      v8->m_script.m_pData = &v7->m_bGetSceneScript;
      ((gbVec3D *)&v25)->Copy((int)(&v7->m_ctrlParabola + 15), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v25.x);
      *((float *)p_m_pSubScriptB + 2) = v10;
      *((float *)p_m_pSubScriptB + 3) = v12;
      p_m_pSubScriptB[4] = v11;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v10;
      *((float *)p_m_pSubScriptB + 7) = v12;
      p_m_pSubScriptB[8] = v11;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = (int)(&p_m_pSubScriptB[11]->m_bGetSceneScript + 1);
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v27, 0x4Cu);
  ((ScriptVM *)p_m_pSubScriptB)->GetString();
  result = this->m_nWaitCount + 1;
  this->m_nWaitCount = result;
  return result;
}

// 0x0042DF30
int PalScriptMgr::CmdPushCmd14(int nVal, unsigned __int8 pData)
{
  PalScriptMgr **p_m_pSubScriptB; // ebx
  int m_nWaitCount; // eax
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  int result; // eax
  PalScriptMgr *v9; // esi
  PalScriptMgr *v10; // eax
  float v11; // ecx
  float v12; // edx
  float x; // eax
  PalScriptMgr *v14; // esi
  unsigned int v15; // eax
  PalScriptMgr *v16; // eax
  float v17; // edx
  float v18; // ecx
  PalScriptMgr *v19; // edx
  int v20; // edi
  gbVec3D *RoleName; // eax
  PalScriptMgr *v22; // edi
  float y; // ecx
  float z; // eax
  PalScriptMgr *v25; // ecx
  int v26; // ecx
  gbVec3D v27; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v28; // [esp+0x18] [ebp-0x50]
  _DWORD v29[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v29);
  p_m_pSubScriptB = &this->m_pSubScriptB;
  v29[15] = nVal;
  LOBYTE(v29[0]) = 14;
  m_nWaitCount = this->m_nWaitCount;
  v29[16] = pData;
  if ( !m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v9 = (PalScriptMgr *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v15 = (unsigned int)p_m_pSubScriptB[8];
      if ( v15 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v20 = ((int)(v15 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v20);
        v22 = (PalScriptMgr *)(&RoleName->x + v20);
        *(_DWORD *)&v22->m_bGetSceneScript = v9;
        ((gbVec3D *)&v27)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v27.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v27.x);
        z = v27.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v25 = v28;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v25;
        v26 = *(_DWORD *)&v22->m_bGetSceneScript + 4028;
        p_m_pSubScriptB[5] = *(PalScriptMgr **)&v22->m_bGetSceneScript;
        p_m_pSubScriptB[6] = (PalScriptMgr *)v26;
        p_m_pSubScriptB[7] = v9;
        p_m_pSubScriptB[8] = v22;
      }
      else
      {
        v16 = (PalScriptMgr *)(v15 + 4);
        p_m_pSubScriptB[8] = v16;
        *(_DWORD *)&v16->m_bGetSceneScript = v9;
        ((gbVec3D *)&v27)->Copy((int)v9, (gbVec3D *)p_m_pSubScriptB[8]);
        v17 = v27.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v27.x);
        v18 = v27.z;
        *((float *)p_m_pSubScriptB + 6) = v17;
        v19 = v28;
        *((float *)p_m_pSubScriptB + 7) = v18;
        p_m_pSubScriptB[8] = v19;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v10 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v10;
      v10->m_script.m_pData = &v9->m_bGetSceneScript;
      ((gbVec3D *)&v27)->Copy((int)(&v9->m_ctrlParabola + 15), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      v11 = v27.y;
      v12 = v27.z;
      x = v27.x;
      v14 = v28;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v27.x);
      *((float *)p_m_pSubScriptB + 2) = v11;
      *((float *)p_m_pSubScriptB + 3) = v12;
      p_m_pSubScriptB[4] = v14;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v11;
      *((float *)p_m_pSubScriptB + 7) = v12;
      p_m_pSubScriptB[8] = v14;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = (int)(&p_m_pSubScriptB[11]->m_bGetSceneScript + 1);
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v29, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v29, 0x4Cu);
  ((ScriptVM *)p_m_pSubScriptB)->GetString();
  result = this->m_nWaitCount + 1;
  this->m_nWaitCount = result;
  return result;
}

// 0x0042E100
int PalScriptMgr::CmdPushCmd15(unsigned __int8 pData)
{
  PalScriptMgr **p_m_pSubScriptB; // ebx
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  int result; // eax
  PalScriptMgr *v7; // esi
  PalScriptMgr *v8; // eax
  float x; // eax
  float v10; // ecx
  PalScriptMgr *v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  PalScriptMgr *v14; // eax
  float v15; // edx
  float v16; // ecx
  PalScriptMgr *v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  PalScriptMgr *v20; // edi
  float y; // ecx
  float z; // eax
  PalScriptMgr *v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v27);
  p_m_pSubScriptB = &this->m_pSubScriptB;
  LOBYTE(v27[0]) = 15;
  v27[15] = pData;
  if ( !this->m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v7 = (PalScriptMgr *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v13 = (unsigned int)p_m_pSubScriptB[8];
      if ( v13 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v18 = ((int)(v13 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v18);
        v20 = (PalScriptMgr *)(&RoleName->x + v18);
        *(_DWORD *)&v20->m_bGetSceneScript = v7;
        ((gbVec3D *)&v25)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v25.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v23 = v26;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v23;
        v24 = *(_DWORD *)&v20->m_bGetSceneScript + 4028;
        p_m_pSubScriptB[5] = *(PalScriptMgr **)&v20->m_bGetSceneScript;
        p_m_pSubScriptB[6] = (PalScriptMgr *)v24;
        p_m_pSubScriptB[7] = v7;
        p_m_pSubScriptB[8] = v20;
      }
      else
      {
        v14 = (PalScriptMgr *)(v13 + 4);
        p_m_pSubScriptB[8] = v14;
        *(_DWORD *)&v14->m_bGetSceneScript = v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)p_m_pSubScriptB[8]);
        v15 = v25.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_pSubScriptB + 6) = v15;
        v17 = v26;
        *((float *)p_m_pSubScriptB + 7) = v16;
        p_m_pSubScriptB[8] = v17;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v8 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v8;
      v8->m_script.m_pData = &v7->m_bGetSceneScript;
      ((gbVec3D *)&v25)->Copy((int)(&v7->m_ctrlParabola + 15), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v25.x);
      *((float *)p_m_pSubScriptB + 2) = v10;
      *((float *)p_m_pSubScriptB + 3) = v12;
      p_m_pSubScriptB[4] = v11;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v10;
      *((float *)p_m_pSubScriptB + 7) = v12;
      p_m_pSubScriptB[8] = v11;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = (int)(&p_m_pSubScriptB[11]->m_bGetSceneScript + 1);
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v27, 0x4Cu);
  ((ScriptVM *)p_m_pSubScriptB)->GetString();
  result = this->m_nWaitCount + 1;
  this->m_nWaitCount = result;
  return result;
}

// 0x0042E2C0
char * PalScriptMgr::CmdCameraOrbitPos(
        
        int nVal,
        float fVal,
        float fVal2,
        unsigned __int8 pData)
{
  float *v6; // eax
  PalScriptMgr **p_m_pSubScriptB; // ebx
  int m_nWaitCount; // eax
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  char *result; // eax
  char *v12; // esi
  PalScriptMgr *v13; // eax
  float v14; // ecx
  float v15; // edx
  float x; // eax
  PalScriptMgr *v17; // esi
  unsigned int v18; // eax
  PalScriptMgr *v19; // eax
  float v20; // edx
  float v21; // ecx
  PalScriptMgr *v22; // edx
  int v23; // edi
  gbVec3D *RoleName; // eax
  gbVec3D *v25; // edi
  float y; // ecx
  float z; // eax
  PalScriptMgr *v28; // ecx
  float v29; // ecx
  float v30; // eax
  PalScriptMgr *v31; // ecx
  gbVec3D v32; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v33; // [esp+0x18] [ebp-0x50]
  _DWORD v34[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v34);
  LOBYTE(v34[0]) = 16;
  v6 = ((CameraCtrl *)&g_pCameraCtrl)->CalcOrbitalPos((float *)&nVal, *(float *)&nVal, fVal, fVal2);
  p_m_pSubScriptB = &this->m_pSubScriptB;
  *(float *)&v34[3] = *v6;
  *(float *)&v34[4] = v6[1];
  *(float *)&v34[5] = v6[2];
  m_nWaitCount = this->m_nWaitCount;
  v34[15] = pData;
  if ( !m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v12 = (char *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v18 = (unsigned int)p_m_pSubScriptB[8];
      if ( v18 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v23 = ((int)(v18 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v23);
        v25 = (gbVec3D *)((char *)RoleName + 4 * v23);
        LODWORD(v25->x) = v12;
        ((gbVec3D *)&v32)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v32.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v32.x);
        z = v32.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v28 = v33;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v28;
        ((gbVec3D *)&v32)->Copy((int)v12, v25);
        v29 = v32.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v32.x);
        v30 = v32.z;
        *((float *)p_m_pSubScriptB + 6) = v29;
        v31 = v33;
        *((float *)p_m_pSubScriptB + 7) = v30;
        p_m_pSubScriptB[8] = v31;
      }
      else
      {
        v19 = (PalScriptMgr *)(v18 + 4);
        p_m_pSubScriptB[8] = v19;
        *(_DWORD *)&v19->m_bGetSceneScript = v12;
        ((gbVec3D *)&v32)->Copy((int)v12, (gbVec3D *)p_m_pSubScriptB[8]);
        v20 = v32.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v32.x);
        v21 = v32.z;
        *((float *)p_m_pSubScriptB + 6) = v20;
        v22 = v33;
        *((float *)p_m_pSubScriptB + 7) = v21;
        p_m_pSubScriptB[8] = v22;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v13 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v13;
      v13->m_script.m_pData = v12;
      ((gbVec3D *)&v32)->Copy((int)(v12 + 1976), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      v14 = v32.y;
      v15 = v32.z;
      x = v32.x;
      v17 = v33;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v32.x);
      *((float *)p_m_pSubScriptB + 2) = v14;
      *((float *)p_m_pSubScriptB + 3) = v15;
      p_m_pSubScriptB[4] = v17;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v14;
      *((float *)p_m_pSubScriptB + 7) = v15;
      p_m_pSubScriptB[8] = v17;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = &p_m_pSubScriptB[11]->m_bGetSceneScript + 1;
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v34, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v34, 0x4Cu);
  result = ((ScriptVM *)p_m_pSubScriptB)->GetString();
  ++this->m_nWaitCount;
  return result;
}

// 0x0042E4D0
int PalScriptMgr::CmdRoleMoveSmooth(int nVal, unsigned __int8 pData)
{
  PalScriptMgr **p_m_pSubScriptB; // ebx
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  int result; // eax
  PalScriptMgr *v8; // esi
  PalScriptMgr *v9; // eax
  float x; // eax
  float v11; // ecx
  PalScriptMgr *v12; // esi
  float v13; // edx
  unsigned int v14; // eax
  PalScriptMgr *v15; // eax
  float v16; // edx
  float v17; // ecx
  PalScriptMgr *v18; // edx
  int v19; // edi
  gbVec3D *RoleName; // eax
  PalScriptMgr *v21; // edi
  float y; // ecx
  float z; // eax
  PalScriptMgr *v24; // ecx
  int v25; // ecx
  gbVec3D v26; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v27; // [esp+0x18] [ebp-0x50]
  _DWORD v28[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry((char *)v28);
  p_m_pSubScriptB = &this->m_pSubScriptB;
  v28[15] = nVal;
  LOBYTE(v28[0]) = 18;
  if ( !this->m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v8 = (PalScriptMgr *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v14 = (unsigned int)p_m_pSubScriptB[8];
      if ( v14 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v19 = ((int)(v14 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v19);
        v21 = (PalScriptMgr *)(&RoleName->x + v19);
        *(_DWORD *)&v21->m_bGetSceneScript = v8;
        ((gbVec3D *)&v26)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v26.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v26.x);
        z = v26.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v24 = v27;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v24;
        v25 = *(_DWORD *)&v21->m_bGetSceneScript + 4028;
        p_m_pSubScriptB[5] = *(PalScriptMgr **)&v21->m_bGetSceneScript;
        p_m_pSubScriptB[6] = (PalScriptMgr *)v25;
        p_m_pSubScriptB[7] = v8;
        p_m_pSubScriptB[8] = v21;
      }
      else
      {
        v15 = (PalScriptMgr *)(v14 + 4);
        p_m_pSubScriptB[8] = v15;
        *(_DWORD *)&v15->m_bGetSceneScript = v8;
        ((gbVec3D *)&v26)->Copy((int)v8, (gbVec3D *)p_m_pSubScriptB[8]);
        v16 = v26.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v26.x);
        v17 = v26.z;
        *((float *)p_m_pSubScriptB + 6) = v16;
        v18 = v27;
        *((float *)p_m_pSubScriptB + 7) = v17;
        p_m_pSubScriptB[8] = v18;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v9 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v9;
      v9->m_script.m_pData = &v8->m_bGetSceneScript;
      ((gbVec3D *)&v26)->Copy((int)(&v8->m_ctrlParabola + 15), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      x = v26.x;
      v11 = v26.y;
      v12 = v27;
      v13 = v26.z;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v26.x);
      *((float *)p_m_pSubScriptB + 2) = v11;
      *((float *)p_m_pSubScriptB + 3) = v13;
      p_m_pSubScriptB[4] = v12;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v11;
      *((float *)p_m_pSubScriptB + 7) = v13;
      p_m_pSubScriptB[8] = v12;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = (int)(&p_m_pSubScriptB[11]->m_bGetSceneScript + 1);
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v28, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v28, 0x4Cu);
  ((ScriptVM *)p_m_pSubScriptB)->GetString();
  result = this->m_nWaitCount + 1;
  this->m_nWaitCount = result;
  return result;
}

// 0x0042E6C0
int PalScriptMgr::CmdRoleMoveDirect(unsigned __int8 pData)
{
  int m_nWaitCount; // eax
  PalScriptMgr **p_m_pSubScriptB; // ebx
  float m_fExecPosZ; // edi
  float m_fExecPosY; // ecx
  int result; // eax
  PalScriptMgr *v8; // esi
  PalScriptMgr *v9; // eax
  float x; // eax
  float v11; // edx
  float v12; // ecx
  PalScriptMgr *v13; // esi
  unsigned int v14; // eax
  PalScriptMgr *v15; // eax
  float v16; // eax
  float v17; // edx
  PalScriptMgr *v18; // eax
  int v19; // edi
  gbVec3D *RoleName; // eax
  PalScriptMgr *v21; // edi
  float y; // edx
  float z; // ecx
  PalScriptMgr *v24; // edx
  int v25; // ecx
  gbVec3D v26; // [esp+0xC] [ebp-0x5C] BYREF
  PalScriptMgr *v27; // [esp+0x18] [ebp-0x50]
  char v28[76]; // [esp+0x1C] [ebp-0x4C] BYREF

  GetCGEntry(v28);
  m_nWaitCount = this->m_nWaitCount;
  p_m_pSubScriptB = &this->m_pSubScriptB;
  v28[0] = 19;
  if ( !m_nWaitCount
    || (m_fExecPosZ = this->m_fExecPosZ, m_fExecPosY = this->m_fExecPosY, LODWORD(m_fExecPosZ) == LODWORD(m_fExecPosY)) )
  {
    v8 = (PalScriptMgr *)operator new(0xFBCu);
    if ( p_m_pSubScriptB[11] )
    {
      v14 = (unsigned int)p_m_pSubScriptB[8];
      if ( v14 >= (unsigned int)p_m_pSubScriptB[9] + 4 * (_DWORD)p_m_pSubScriptB[10] - 4 )
      {
        v19 = ((int)(v14 - (_DWORD)p_m_pSubScriptB[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_pSubScriptB)->GetRoleName(2 * v19);
        v21 = (PalScriptMgr *)(&RoleName->x + v19);
        *(_DWORD *)&v21->m_bGetSceneScript = v8;
        ((gbVec3D *)&v26)->Copy((int)p_m_pSubScriptB[3], RoleName);
        y = v26.y;
        p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v26.x);
        z = v26.z;
        *((float *)p_m_pSubScriptB + 2) = y;
        v24 = v27;
        *((float *)p_m_pSubScriptB + 3) = z;
        p_m_pSubScriptB[4] = v24;
        v25 = *(_DWORD *)&v21->m_bGetSceneScript + 4028;
        p_m_pSubScriptB[5] = *(PalScriptMgr **)&v21->m_bGetSceneScript;
        p_m_pSubScriptB[6] = (PalScriptMgr *)v25;
        p_m_pSubScriptB[7] = v8;
        p_m_pSubScriptB[8] = v21;
      }
      else
      {
        v15 = (PalScriptMgr *)(v14 + 4);
        p_m_pSubScriptB[8] = v15;
        *(_DWORD *)&v15->m_bGetSceneScript = v8;
        ((gbVec3D *)&v26)->Copy((int)v8, (gbVec3D *)p_m_pSubScriptB[8]);
        v16 = v26.y;
        p_m_pSubScriptB[5] = (PalScriptMgr *)LODWORD(v26.x);
        v17 = v26.z;
        *((float *)p_m_pSubScriptB + 6) = v16;
        v18 = v27;
        *((float *)p_m_pSubScriptB + 7) = v17;
        p_m_pSubScriptB[8] = v18;
      }
    }
    else
    {
      p_m_pSubScriptB[10] = (PalScriptMgr *)2;
      v9 = (PalScriptMgr *)operator new(8u);
      p_m_pSubScriptB[9] = v9;
      v9->m_script.m_pData = &v8->m_bGetSceneScript;
      ((gbVec3D *)&v26)->Copy((int)(&v8->m_ctrlParabola + 15), (gbVec3D *)&p_m_pSubScriptB[9]->m_script);
      x = v26.x;
      v11 = v26.z;
      v12 = v26.y;
      v13 = v27;
      p_m_pSubScriptB[1] = (PalScriptMgr *)LODWORD(v26.x);
      *((float *)p_m_pSubScriptB + 2) = v12;
      *((float *)p_m_pSubScriptB + 3) = v11;
      p_m_pSubScriptB[4] = v13;
      *((float *)p_m_pSubScriptB + 5) = x;
      *((float *)p_m_pSubScriptB + 6) = v12;
      *((float *)p_m_pSubScriptB + 7) = v11;
      p_m_pSubScriptB[8] = v13;
    }
    m_fExecPosZ = *((float *)p_m_pSubScriptB + 7);
    p_m_pSubScriptB[7] = (PalScriptMgr *)(LODWORD(m_fExecPosZ) + 76);
    if ( m_fExecPosZ == 0.0 )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosZ) = LODWORD(m_fExecPosZ) + 76;
  if ( LODWORD(m_fExecPosZ) + 76 != LODWORD(m_fExecPosY) )
  {
    if ( m_fExecPosZ == 0.0 )
    {
LABEL_16:
      result = (int)(&p_m_pSubScriptB[11]->m_bGetSceneScript + 1);
      p_m_pSubScriptB[11] = (PalScriptMgr *)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosZ), v28, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosZ != 0.0 )
    qmemcpy((void *)LODWORD(m_fExecPosZ), v28, 0x4Cu);
  ((ScriptVM *)p_m_pSubScriptB)->GetString();
  result = this->m_nWaitCount + 1;
  this->m_nWaitCount = result;
  return result;
}

// 0x0042EBE0
int PalScriptMgr::ExecuteOpcode()
{
  int result; // eax
  char *m_pScriptBlock; // edi
  PalScriptMgr *p_m_pSubScriptB; // ecx
  int v5; // edx
  char *v6; // eax
  unsigned __int8 v7; // al
  RoleSystem *m_pSceneMgr; // ecx
  int v9; // edx
  char *v10; // edx
  int v11; // ecx
  char *v12; // eax
  int *v13; // eax
  char *v14; // ecx
  RoleSystem *v15; // esi
  CScreenMode *v16; // ecx
  char *v17; // eax
  char *v18; // edi
  int v19; // edx
  PtrArray *SoundList; // eax
  RoleSystem *v21; // esi
  RoleSystem *v22; // ebx
  int v23; // ebp
  int *m_teamSlots; // edx
  int *p_m_nExecuteOpcode; // eax
  double v26; // st7
  int RolePtr; // ebx
  double v28; // st7
  float v29; // ebp
  __int64 v30; // rax
  double v31; // st7
  int v32; // ecx
  float z; // ecx
  double v34; // st7
  double v35; // st7
  double v36; // st7
  char *v37; // edx
  int v38; // ecx
  char *v39; // eax
  float v40; // eax
  float v41; // edx
  float v42; // ecx
  char *v43; // edi
  float v44; // eax
  float v45; // edx
  char *v46; // eax
  char *v47; // eax
  char *v48; // edx
  int v49; // ecx
  char *v50; // eax
  float y; // ecx
  float v52; // edx
  float x; // eax
  char *v54; // edi
  float v55; // edx
  float v56; // ecx
  char *v57; // edx
  char *v58; // [esp-0x4] [ebp-0x8C]
  char *m_pClearResult; // [esp-0x4] [ebp-0x8C]
  char *v60; // [esp-0x4] [ebp-0x8C]
  char *m_pWaitObj; // [esp-0x4] [ebp-0x8C]
  gbVec3D nVal2; // [esp+0x10] [ebp-0x78] BYREF
  char *v63; // [esp+0x1C] [ebp-0x6C]
  gbVec3D v64; // [esp+0x20] [ebp-0x68] BYREF
  gbVec3D v65; // [esp+0x2C] [ebp-0x5C] BYREF
  char *m_pExecObj; // [esp+0x38] [ebp-0x50]
  gbMatrix4 pMatrix; // [esp+0x3C] [ebp-0x4C] BYREF
  float v68; // [esp+0x7C] [ebp-0xC]
  float v69; // [esp+0x84] [ebp-0x4]

  result = this->m_nWaitCount;
  if ( result )
  {
    while ( 2 )
    {
      LODWORD(v65.x) = this->m_nScriptCamX;
      LODWORD(v65.y) = this->m_nScriptCamY;
      m_pScriptBlock = this->m_pScriptBlock;
      m_pExecObj = this->m_pExecObj;
      result = (unsigned __int8)*m_pScriptBlock - 2;
      switch ( *m_pScriptBlock )
      {
        case 2:
          v15 = g_pRoleSystem;
          ((RoleSystem *)&g_pRoleSystem)->Notify();
          ((RoleSystem *)v15)->GetMoveState();
          ((RoleSystem *)v15)->SetMoveTarget((float *)m_pScriptBlock + 6, 1);
          return result;
        case 3:
          this->SetBigMapState(m_pScriptBlock[60]);
          result = *((_DWORD *)m_pScriptBlock + 16);
          goto LABEL_4;
        case 4:
          ((PalScriptMgr *)*((PalScriptMgr **)m_pScriptBlock + 16))->Destroy();
          this->m_pClearResult = v17;
          if ( !*((_DWORD *)m_pScriptBlock + 15) )
          {
            v18 = this->m_pScriptBlock + 76;
            v19 = this->m_nWaitCount - 1;
            this->m_pScriptBlock = v18;
            this->m_nWaitCount = v19;
            if ( !v19 || v18 == (char *)this->m_nScriptCamY )
              ((PalScriptMgr *)&this->m_pSubScriptB)->PopScript();

          }
          m_pClearResult = this->m_pClearResult;
          SoundList = ((CScreenMode *)v16)->GetSoundList();
          ((PtrArray *)SoundList)->SetResolution(0, (int)m_pClearResult);
          return result;
        case 5:

          result = *((_DWORD *)m_pScriptBlock + 15);
LABEL_4:
          if ( !result )
            goto LABEL_5;
          return result;
        case 6:
          v21 = g_pRoleSystem;
          ((RoleSystem *)&g_pRoleSystem)->Notify();
          return ((RoleSystem *)v21)->GetActionByIndex(*((_DWORD *)m_pScriptBlock + 15));
        case 7:
          (*(void ( **)(char *, _DWORD))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, 0);
          ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(2.0);
          return result;
        case 8:
          ((CameraCtrl *)*((_DWORD *)m_pScriptBlock + 15))->AttachToRole();
          goto LABEL_5;
        case 9:
          ((RoleSystem *)this)->ProcessAction();
          goto LABEL_5;
        case 10:
          this->m_bOpcodeFlag = m_pScriptBlock[60];
          goto LABEL_5;
        case 11:
          ((RoleSystem *)&g_pRoleSystem)->IsPathComplete((float *)m_pScriptBlock + 3, 1);
          goto LABEL_5;
        case 12:
          v22 = g_pRoleSystem;
          ((RoleSystem *)&g_pRoleSystem)->Notify();
          v23 = 0;
          v22[1]._todo_074 = this->m_nScriptDepth + 1;
          v22->_embed_UIWnd_624.m_childs.m_needscriptdel = LODWORD(v22->m_fPosX);
          v22->_embed_UIWnd_624.m_bcreateok = LODWORD(v22->m_fPosY);
          v22->_embed_UIWnd_624.m_bvisible = LODWORD(v22->m_fPosZ);
          if ( this->m_nScriptDepth > 0 )
          {
            m_teamSlots = v22->m_teamSlots;
            p_m_nExecuteOpcode = &this->m_nExecuteOpcode;
            do
            {
              ++v23;
              *(m_teamSlots - 2) = *(p_m_nExecuteOpcode - 2);
              *(m_teamSlots - 1) = *(p_m_nExecuteOpcode - 1);
              *m_teamSlots = *p_m_nExecuteOpcode;
              p_m_nExecuteOpcode += 3;
              m_teamSlots += 3;
            }
            while ( v23 < this->m_nScriptDepth );
          }
          ((PathObj *)&v22->_embed_UIWnd_624.m_childs.m_needscriptdel)->CalcLength();
          v26 = *(float *)&v22[1]._todo_078 * 0.0016666667;
          *((_DWORD *)m_pScriptBlock + 2) = 0;
          *((float *)m_pScriptBlock + 1) = v26;
          v22->m_FrameA.m_childs.m_nSize = 2;
          ((RoleSystem *)v22)->UpdateTransform();
          return ((RoleSystem *)v22)->GetMoveState();
        case 13:
          RolePtr = ((RoleSystem *)this->m_pSceneMgr->m_rect.left)->GetRolePtr((unsigned __int8)this->m_bExecuteOpcode);
          v28 = this->m_fCamZ - *(float *)(RolePtr + 136);
          LODWORD(v29) = (__int64)((this->m_fCamX - *(float *)(RolePtr + 128)) / flt_D8C17C);
          nVal2.x = v29;
          v30 = (__int64)(v28 / flt_D8C17C);
          v31 = 0.0;
          LODWORD(nVal2.y) = v30;
          v64.x = ((double)SLODWORD(v29) + 0.5) * flt_D8C17C + *(float *)(RolePtr + 128);
          v64.z = ((double)(int)v30 + 0.5) * flt_D8C17C + *(float *)(RolePtr + 136);
          if ( v29 >= 0.0 )
          {
            v32 = *(_DWORD *)(RolePtr + 152);
            if ( SLODWORD(v29) < v32 && (int)v30 >= 0 && (int)v30 < *(_DWORD *)(RolePtr + 156) )
              v31 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (LODWORD(v29) + v30 * v32));
          }
          result = LODWORD(v64.x);
          z = v64.z;
          *((float *)m_pScriptBlock + 4) = v31;
          *((_DWORD *)m_pScriptBlock + 3) = result;
          *((float *)m_pScriptBlock + 5) = z;
          *((float *)m_pScriptBlock + 4) = *((float *)m_pScriptBlock + 4) - 4.0;
          return result;
        case 14:
          ((RoleSystem *)&g_pRoleSystem)->NotifySceneChange();
          if ( *((_DWORD *)m_pScriptBlock + 16) )
          {
            v7 = m_pScriptBlock[60];
            m_pSceneMgr = this->m_pSceneMgr;
            this->m_bExecuteOpcode = v7;
            this->m_pSceneMgr = (RoleSystem *)((RoleSystem *)m_pSceneMgr->m_rect.left)->NotifyPathEnd(v7);
          }
          goto LABEL_5;
        case 15:
          *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) = *((_DWORD *)m_pScriptBlock + 15);
          goto LABEL_5;
        case 16:
          if ( *((_DWORD *)m_pScriptBlock + 15) )
          {
            v64.x = g_pCameraCtrl->m_vecLookAt.x - *((float *)m_pScriptBlock + 3);
            v34 = g_pCameraCtrl->m_vecLookAt.y - *((float *)m_pScriptBlock + 4);
            nVal2.x = v64.x;
            v64.y = v34;
            v35 = g_pCameraCtrl->m_vecLookAt.z - *((float *)m_pScriptBlock + 5);
            nVal2.y = v64.y;
            v64.z = v35;
            nVal2.z = v64.z;
            nVal2.x = ((gbVec3D *)&nVal2)->Length() * 0.02;
            return ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->SetupLerp((int)g_pCameraCtrl, (int *)m_pScriptBlock + 3, SLODWORD(nVal2.x), 1);
          }
          else
          {
            g_pCameraCtrl->m_vecLookAt = *(gbVec3D *)(m_pScriptBlock + 1);
            ((InputSystem *)g_pCameraCtrl)->InputSystem::ProcessKeyboard();
          }
          return result;
        case 17:
          this->m_szScriptFile[5] = m_pScriptBlock[60];
LABEL_5:
          p_m_pSubScriptB = (PalScriptMgr *)&this->m_pSubScriptB;
          v5 = this->m_nWaitCount - 1;
          v6 = this->m_pScriptBlock + 76;
          this->m_pScriptBlock = v6;
          this->m_nWaitCount = v5;
          if ( v5 )
            goto LABEL_17;
          goto LABEL_18;
        case 18:

          p_m_pSubScriptB = (PalScriptMgr *)&this->m_pSubScriptB;
          v9 = this->m_nWaitCount - 1;
          v6 = this->m_pScriptBlock + 76;
          this->m_pScriptBlock = v6;
          this->m_nWaitCount = v9;
          if ( !v9 )
            goto LABEL_18;
LABEL_17:
          if ( v6 == (char *)p_m_pSubScriptB->m_script.capacity )
LABEL_18:
            ((PalScriptMgr *)p_m_pSubScriptB)->PopScript();
LABEL_26:
          result = this->m_nWaitCount;
          if ( !result )
            return result;
          continue;
        case 19:
          v64.x = this->m_fCamX;
          v64.z = this->m_fCamZ;
          v64.y = 0.0;
          v64.x = v64.x - *(float *)&g_pRoleSystem->m_fontcolor.Color;
          v64.y = -*(float *)&g_pRoleSystem->m_wndcolor.Color;
          v64.z = v64.z - *(float *)&g_pRoleSystem->m_id;
          nVal2.x = ((gbVec3D *)&v64)->Length();
          ((Object3D *)this)->SetTransform(&pMatrix);
          if ( v69 <= (double)v68 )
            v36 = v68;
          else
            v36 = v69;
          if ( nVal2.x - v36 * 0.5 <= g_ScriptSystemData.m_fD8BEF0 )
          {
            v48 = this->m_pScriptBlock + 76;
            v49 = this->m_nWaitCount - 1;
            this->m_pScriptBlock = v48;
            this->m_nWaitCount = v49;
            if ( !v49 || v48 == (char *)this->m_nScriptCamY )
            {
              v50 = this->m_pExecObj;
              this->m_pExecObj = v50 + 4;
              operator delete(*(void **)v50);
              if ( !this->m_nWaitCount )
              {
                ((PalScriptMgr *)&v65)->Get_result();
                y = v65.y;
                v52 = v65.z;
                x = v65.x;
                v54 = m_pExecObj;
                this->m_nScriptCamX = LODWORD(v65.x);
                *(float *)&this->m_nScriptCamY = y;
                *(float *)&this->m_pScriptBlock = v52;
                this->m_pExecObj = v54;
                this->m_fExecParam = x;
                this->m_fExecPosY = y;
                m_pWaitObj = this->m_pWaitObj;
                this->m_fExecPosZ = v52;
                this->m_nExecState2 = (int)v54;
                operator delete(m_pWaitObj);
                return this->ExecuteOpcode();
              }
              ((gbVec3D *)&v65)->Copy(*(_DWORD *)this->m_pExecObj, (gbVec3D *)this->m_pExecObj);
              v55 = v65.y;
              this->m_nScriptCamX = LODWORD(v65.x);
              v56 = v65.z;
              *(float *)&this->m_nScriptCamY = v55;
              v57 = m_pExecObj;
              *(float *)&this->m_pScriptBlock = v56;
              this->m_pExecObj = v57;
            }
            result = this->ExecuteOpcode();
          }
          else
          {
            while ( this->m_nWaitCount )
            {
              v37 = this->m_pScriptBlock + 76;
              v38 = this->m_nWaitCount - 1;
              this->m_pScriptBlock = v37;
              this->m_nWaitCount = v38;
              if ( !v38 || v37 == (char *)this->m_nScriptCamY )
              {
                v39 = this->m_pExecObj;
                this->m_pExecObj = v39 + 4;
                operator delete(*(void **)v39);
                if ( this->m_nWaitCount )
                {
                  ((gbVec3D *)&v65)->Copy(*(_DWORD *)this->m_pExecObj, (gbVec3D *)this->m_pExecObj);
                  v44 = v65.y;
                  this->m_nScriptCamX = LODWORD(v65.x);
                  v45 = v65.z;
                  *(float *)&this->m_nScriptCamY = v44;
                  v46 = m_pExecObj;
                  *(float *)&this->m_pScriptBlock = v45;
                  this->m_pExecObj = v46;
                }
                else
                {
                  ((PalScriptMgr *)&nVal2)->Get_result();
                  v40 = nVal2.x;
                  v41 = nVal2.z;
                  v42 = nVal2.y;
                  v43 = v63;
                  this->m_nScriptCamX = LODWORD(nVal2.x);
                  *(float *)&this->m_nScriptCamY = v42;
                  *(float *)&this->m_pScriptBlock = v41;
                  this->m_pExecObj = v43;
                  this->m_fExecParam = v40;
                  this->m_fExecPosY = v42;
                  this->m_fExecPosZ = v41;
                  v60 = this->m_pWaitObj;
                  this->m_nExecState2 = (int)v43;
                  operator delete(v60);
                }
              }
            }
            v47 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("outdist");
            result = ((PalScriptMgr *)&stru_DBA134)->ShowTextBox(v47);
          }
          break;
        case 21:
          if ( *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
            ((_Console *)g_pCameraCtrl)->SetActive((int)g_pRoleSystem);
          v10 = this->m_pScriptBlock + 76;
          v11 = this->m_nWaitCount - 1;
          this->m_pScriptBlock = v10;
          this->m_nWaitCount = v11;
          if ( !v11 || v10 == (char *)this->m_nScriptCamY )
          {
            v12 = this->m_pExecObj;
            this->m_pExecObj = v12 + 4;
            operator delete(*(void **)v12);
            if ( this->m_nWaitCount )
            {
              v13 = (int *)this->m_pExecObj;
              v14 = (char *)*v13;
              this->m_nScriptCamX = *v13;
              this->m_nScriptCamY = (int)(v14 + 4028);
              this->m_pScriptBlock = v14;
              this->m_pExecObj = (char *)v13;
            }
            else
            {
              this->m_nScriptCamX = 0;
              this->m_nScriptCamY = 0;
              this->m_pScriptBlock = 0;
              this->m_pExecObj = 0;
              this->m_fExecParam = 0.0;
              v58 = this->m_pWaitObj;
              this->m_fExecPosY = 0.0;
              this->m_fExecPosZ = 0.0;
              this->m_nExecState2 = 0;
              operator delete(v58);
            }
          }
          goto LABEL_26;
        default:
          return result;
      }
      break;
    }
  }
  return result;
}

// 0x0042F460
void PalScriptMgr::ExecuteFrame(float fVal)
{
  bool IsRunning; // bl
  int m_nScriptCamY; // edx
  char *m_pScriptBlock; // ebp
  double v6; // st7
  float *p_m_fCamX; // esi
  long double v8; // st7
  RoleSystem *v9; // edx
  char m_nCmdType; // al
  RoleSystem *v11; // esi
  double v12; // st7
  int RolePtr; // ebx
  void *m_id; // eax
  float v15; // ecx
  int v16; // ebp
  bool v17; // zf
  BOOL IsAngleBelowTarget; // eax
  PalScript *v19; // eax
  ScriptVM *v20; // eax
  int v21; // eax
  BOOL IsVisible; // eax
  RoleSystem *v23; // esi
  double v24; // st7
  float v25; // eax
  char *v26; // edx
  int v27; // ecx
  char *v28; // eax
  int *v29; // eax
  char *v30; // ecx
  float pPos; // [esp+0x0] [ebp-0x40]
  int v32; // [esp+0x8] [ebp-0x38]
  char *m_pWaitObj; // [esp+0x8] [ebp-0x38]
  int v34; // [esp+0xC] [ebp-0x34]
  int nFlag; // [esp+0x1C] [ebp-0x24]
  float pfVal; // [esp+0x24] [ebp-0x1C] BYREF
  float v37; // [esp+0x28] [ebp-0x18]
  float v38; // [esp+0x2C] [ebp-0x14]
  int p_DWORD; // [esp+0x30] [ebp-0x10] BYREF
  float v40; // [esp+0x34] [ebp-0xC]
  int v41; // [esp+0x38] [ebp-0x8]
  char *m_pExecObj; // [esp+0x3C] [ebp-0x4]

  if ( this->m_nWaitCount )
  {
    IsRunning = 0;
    p_DWORD = this->m_nScriptCamX;
    m_nScriptCamY = this->m_nScriptCamY;
    v40 = *(float *)&m_nScriptCamY;
    m_pScriptBlock = this->m_pScriptBlock;
    v6 = fVal + *((float *)m_pScriptBlock + 2);
    m_pExecObj = this->m_pExecObj;
    *((float *)m_pScriptBlock + 2) = v6;
    if ( v6 >= *((float *)m_pScriptBlock + 1) )
    {
      IsRunning = 1;
      *((_DWORD *)m_pScriptBlock + 2) = *((_DWORD *)m_pScriptBlock + 1);
    }
    *(float *)&nFlag = *((float *)m_pScriptBlock + 2) / *((float *)m_pScriptBlock + 1);
    switch ( *m_pScriptBlock )
    {
      case 1:
        p_m_fCamX = &this->m_fCamX;
        v8 = (1.0 - cos(*(float *)&nFlag * 3.1415927)) * 0.5;
        this->m_fCamX = *((float *)m_pScriptBlock + 3) * (1.0 - v8) + *((float *)m_pScriptBlock + 6) * v8;
        this->m_fCamY = *((float *)m_pScriptBlock + 4) * (1.0 - v8) + *((float *)m_pScriptBlock + 7) * v8;
        this->m_fCamZ = *((float *)m_pScriptBlock + 5) * (1.0 - v8) + *((float *)m_pScriptBlock + 8) * v8;
        if ( *((_DWORD *)m_pScriptBlock + 15) )
        {
          ((RoleSystem *)&g_pRoleSystem)->SetTargetRotation((gbVec3D *)&this->m_fCamX);
          v9 = g_pRoleSystem;
          g_pRoleSystem->m_fPosX = *p_m_fCamX;
          v9->m_fPosY = this->m_fCamY;
          v9->m_fPosZ = this->m_fCamZ;
        }
        if ( *((_DWORD *)m_pScriptBlock + 16) )
        {
          this->m_nExecuteBlock = *(int *)p_m_fCamX;
          this->m_nSavedDataA = LODWORD(this->m_fCamY);
          this->m_nSavedDataB = LODWORD(this->m_fCamZ);
        }
        m_nCmdType = this->m_nCmdType;
        if ( m_nCmdType == 33 || m_nCmdType == 29 )
          ((RoleSystem *)&g_pRoleSystem)->SetMoveSpeed(0.0, 0, v34);
        goto LABEL_40;
      case 2:
        v11 = g_pRoleSystem;
        ((RoleSystem *)&g_pRoleSystem)->PathFollowUpdate();
        if ( v11->m_FrameA.m_rect.bottom == 4 )
        {
          v11->m_FrameA.m_bvisible = (int)v11->m_FrameA.m_pbktex;
          v11->m_FrameA.m_benable = v11->m_nActiveRole;
          v11->m_FrameA.m_bfocus = v11->m_nRoleCount;
          v11->m_FrameA.m_benable = 0;
          *(int *)((char *)&v11[1].m_partyUI3._todo_05C + 79) = v11->m_fontcolor.Color;
          *(int *)((char *)&v11[1].m_partyUI3._todo_05C + 83) = v11->m_wndcolor.Color;
          *(int *)((char *)&v11[1].m_partyUI3._todo_05C + 87) = (int)v11->m_id;
          v12 = fVal * *(float *)&v11->m_FrameA.m_bvisible;
          v40 = fVal * *(float *)&v11->m_FrameA.m_benable;
          *(float *)&v41 = fVal * *(float *)&v11->m_FrameA.m_bfocus;
          *(float *)((char *)&v11[1].m_partyUI3._todo_05C + 79) = v12
                                                                + *(float *)((char *)&v11[1].m_partyUI3._todo_05C + 79);
          *(float *)((char *)&v11[1].m_partyUI3._todo_05C + 83) = v40
                                                                + *(float *)((char *)&v11[1].m_partyUI3._todo_05C + 83);
          *(float *)((char *)&v11[1].m_partyUI3._todo_05C + 87) = *(float *)&v41
                                                                + *(float *)((char *)&v11[1].m_partyUI3._todo_05C + 87);
          if ( *((_DWORD *)m_pScriptBlock + 15) )
          {
            RolePtr = ((RoleSystem *)this->m_pSceneMgr->m_rect.left)->GetRolePtr(*(_DWORD *)v11->m_partyActor.m_szTexture);
            if ( !((RoleSystem *)this->m_pSceneMgr->m_rect.left)->CheckCollision(*(int **)v11->m_partyActor.m_szTexture, (__int64)((*(float *)((char *)&v11[1].m_partyUI3._todo_05C + 79) - *(float *)(RolePtr + 128))
                            / flt_D8C17C)) )
            {
              ((RoleSystem *)v11)->NotifyMoveComplete();
              *(int *)((char *)&v11[1].m_partyUI3._todo_05C + 79) = v11->m_fontcolor.Color;
              *(int *)((char *)&v11[1].m_partyUI3._todo_05C + 83) = v11->m_wndcolor.Color;
              *(int *)((char *)&v11[1].m_partyUI3._todo_05C + 87) = (int)v11->m_id;
            }
          }
          v11->m_fontcolor.Color = *(int *)((char *)&v11[1].m_partyUI3._todo_05C + 79);
          v11->m_wndcolor.Color = *(int *)((char *)&v11[1].m_partyUI3._todo_05C + 83);
          v11->m_id = *(void **)((char *)&v11[1].m_partyUI3._todo_05C + 87);
          v11->m_wndcolor.Color = 0;
          ((RoleSystem *)v11)->UpdatePosition();
          if ( *((_DWORD *)m_pScriptBlock + 16) )
          {
            ((RoleSystem *)v11)->SetMoveSpeed(0.0, 0, v34);
          }
          else
          {
            m_id = v11->m_id;
            v15 = *(float *)&v11->m_fontcolor.Color;
            v11->m_fPosX = v15;
            LODWORD(v11->m_fPosZ) = m_id;
            *(float *)&v11->m_nDispFontColor = v15;
            v11->m_nDispWndColor = LODWORD(v11->m_fPosY);
            v11->m_nField9C = LODWORD(v11->m_fPosZ);
          }
        }
        IsRunning = v11->m_FrameA.m_rect.bottom != 4;
        if ( v11->m_FrameA.m_rect.bottom == 4 )
          return;
        ((RoleSystem *)v11)->GetMoveState();
        goto LABEL_40;
      case 3:
        v16 = *((_DWORD *)m_pScriptBlock + 15) - 1;
        if ( v16 )
        {
          if ( v16 == 1 )
          {
            v17 = this->m_bBigMapState == 0;
LABEL_39:
            IsRunning = v17;
          }
        }
        else
        {
          IsRunning = this->m_bBigMapState != 1;
        }
LABEL_40:
        if ( !IsRunning )
          return;
LABEL_41:
        v26 = this->m_pScriptBlock + 76;
        v27 = this->m_nWaitCount - 1;
        this->m_pScriptBlock = v26;
        this->m_nWaitCount = v27;
        if ( v27 && v26 != (char *)this->m_nScriptCamY )
          goto LABEL_46;
        v28 = this->m_pExecObj;
        this->m_pExecObj = v28 + 4;
        operator delete(*(void **)v28);
        if ( this->m_nWaitCount )
        {
          v29 = (int *)this->m_pExecObj;
          v30 = (char *)*v29;
          this->m_nScriptCamX = *v29;
          this->m_nScriptCamY = (int)(v30 + 4028);
          this->m_pScriptBlock = v30;
          this->m_pExecObj = (char *)v29;
LABEL_46:

        }
        else
        {
          this->m_nScriptCamX = 0;
          this->m_nScriptCamY = 0;
          this->m_pScriptBlock = 0;
          this->m_pExecObj = 0;
          this->m_fExecParam = 0.0;
          m_pWaitObj = this->m_pWaitObj;
          this->m_fExecPosY = 0.0;
          this->m_fExecPosZ = 0.0;
          this->m_nExecState2 = 0;
          operator delete(m_pWaitObj);

        }
        break;
      case 4:
        ((PalScriptMgr *)this->m_pClearResult)->ClearAllScript();
        goto LABEL_38;
      case 5:
        LOWORD(m_nScriptCamY) = this->m_nScriptID;
        v32 = m_nScriptCamY;
        v19 = (PalScript *)UISceneUpdate();
        ((PalScript *)v19)->SetAction(v32);
        if ( !v20 )
          goto LABEL_41;
        IsRunning = ((ScriptVM *)v20)->IsRunning();
        goto LABEL_40;
      case 6:
        v21 = (*(int ( **)(int *))(g_pRoleSystem->m_bvisible + 4))(&g_pRoleSystem->m_bvisible);
        IsRunning = v21 == 1;
        if ( v21 != 1 )
          return;
        ((RoleSystem *)&g_pRoleSystem)->Notify();
        goto LABEL_40;
      case 7:
        IsVisible = ((Object3D *)&this->_todo_058)->IsVisible();
        IsRunning = IsVisible;
        if ( !IsVisible )
          return;
        if ( *((_DWORD *)m_pScriptBlock + 15) )
        {
          ((gbVisNode *)this->m_pExecSystem)->SetTimeScale(0.0);
          (*(void ( **)(char *, int))(*(_DWORD *)this->m_pExecSystem + 24))(this->m_pExecSystem, -1082130432);
          ((PalScript *)&this->_todo_058)->GetCount(0);
        }
        goto LABEL_40;
      case 12:
        v23 = g_pRoleSystem;
        v24 = *(float *)&g_pRoleSystem[1]._todo_078;
        pfVal = 0.0;
        v37 = 0.0;
        v38 = 0.0;
        p_DWORD = 0;
        v40 = 0.0;
        *(float *)&v41 = 0.0;
        pPos = (1.0 - cos(*(float *)&nFlag * 3.1415927)) * 0.5 * v24;
        ((PathObj *)&g_pRoleSystem->_embed_UIWnd_624.m_childs.m_needscriptdel)->GetPosition(pPos,   &pfVal,   &p_DWORD);
        *(float *)&v23->m_fontcolor.Color = pfVal;
        *(float *)&v23->m_wndcolor.Color = v37;
        *(float *)&v23->m_id = v38;
        v23->m_fPosX = pfVal;
        v23->m_fPosY = v37;
        v23->m_fPosZ = v38;
        v23->m_wndcolor.Color = 0;
        v23->m_FrameA.m_bvisible = p_DWORD;
        *(float *)&v23->m_FrameA.m_benable = v40;
        v23->m_FrameA.m_bfocus = v41;
        ((RoleSystem *)v23)->SetMoveSpeed(0.0, 0, v34);
        ((RoleSystem *)v23)->UpdatePosition();
        if ( !IsRunning )
          return;
        ((RoleSystem *)v23)->GetMoveState();
        ((RoleSystem *)v23)->Notify();
        goto LABEL_40;
      case 13:
        *((float *)m_pScriptBlock + 7) = *((float *)m_pScriptBlock + 7) - 490.0 * fVal;
        pfVal = *((float *)m_pScriptBlock + 6);
        v25 = *((float *)m_pScriptBlock + 8);
        v37 = *((float *)m_pScriptBlock + 7) * fVal;
        v38 = v25 * fVal;
        this->m_fCamX = pfVal * fVal + this->m_fCamX;
        this->m_fCamY = v37 + this->m_fCamY;
        this->m_fCamZ = v38 + this->m_fCamZ;
        if ( this->m_fCamY > (double)*((float *)m_pScriptBlock + 4) )
          return;
        this->m_fCamY = *((float *)m_pScriptBlock + 4);
        this->m_nExecuteBlock = LODWORD(this->m_fCamX);
        this->m_nSavedDataA = LODWORD(this->m_fCamY);
        this->m_nSavedDataB = LODWORD(this->m_fCamZ);
        goto LABEL_41;
      case 16:
        ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->UpdateTransition(fVal);
        IsAngleBelowTarget = ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->IsAngleBelowTarget();
LABEL_38:
        v17 = !IsAngleBelowTarget;
        goto LABEL_39;
      default:
        goto LABEL_40;
    }
  }
}

// 0x0042FB40
char PalScriptMgr::SetBigMapState(char nState)
{
  this->_todo_054 = 0;
  this->m_bBigMapState = nState;
  return nState;
}

// 0x0042FCC0
void PalScriptMgr::PopScript()
{
  void **m_needscriptdel; // eax
  char **v3; // eax
  PtrArray *p_m_script; // esi
  char *v5; // ecx
  void *todo_024; // [esp-0x8] [ebp-0x10]

  m_needscriptdel = (void **)this->m_script.m_needscriptdel;
  this->m_script.m_needscriptdel = (int)(m_needscriptdel + 1);
  operator delete(*m_needscriptdel);
  if ( LODWORD(this->m_fCamY) )
  {
    v3 = (char **)this->m_script.m_needscriptdel;
    p_m_script = &this->m_script;
    v5 = *v3;
    p_m_script->m_pData = *v3;
    p_m_script->capacity = (int)(v5 + 4028);
    p_m_script->m_nSize = (int)v5;
    p_m_script->m_needscriptdel = (int)v3;
  }
  else
  {
    this->m_script.m_pData = 0;
    this->m_script.capacity = 0;
    this->m_script.m_nSize = 0;
    this->m_script.m_needscriptdel = 0;
    this->m_scefile = 0;
    todo_024 = (void *)this->_todo_024;
    this->_todo_018 = 0.0;
    this->_todo_01C = 0.0;
    this->_todo_020 = 0.0;
    operator delete(todo_024);
  }
}

// 0x00431E60
PalScriptMgr::PalScriptMgr()
{
  unknown_libname_343(this);
  atexit((void (__cdecl *)())PtrArray::ConditionalCleanup);
}

// 0x00431EB0
void PalScriptMgr::OpenSCE()
{
  unknown_libname_344(this);
  atexit((void ( *)())PalScriptMgr::FindScript);
}

// 0x00431EE0
void PalScriptMgr::FindScript()
{
  if ( (((GRPinput *)&stru_D8C2B8)->m_keyStates[4] & 8) == 0 )
  {
    ((GRPinput *)&stru_D8C2B8)->m_keyStates[4] |= 8u;
    ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_mouseMinX)->Remove();
  }
}

// 0x004320A0
void PalScriptMgr::Update()
{
  int v1; // eax
  unsigned int v2; // kr04_4
  unsigned int v3; // ebp
  IDirectInputDevice8 *m_lpDIDKeyboard; // edi
  IDirectInputDevice8 v5; // al

  ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_joystickX)->InsertAt(pszName);
  if ( v1 )
  {
    v2 = strlen(pszName) + 1;
    v3 = v2 - 1;
    if ( v2 - 1 > 0xFFFFFFFD )
// [IDA_MISID]       std::_Xlen();
    m_lpDIDKeyboard = ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard;
    if ( ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard && (v5 = ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard[-1]) != 0 && v5 != 0xFF )
    {
      if ( v2 == 1 )
      {
        ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard[-1] = (IDirectInputDevice8)(*(_BYTE *)&v5 - 1);
        ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard = 0;
        ((GRPinput *)&stru_D8C2B8)->m_lpDIDMouse = 0;
        ((GRPinput *)&stru_D8C2B8)->m_mouseSensitivity = 0.0;
        return;
      }
    }
    else
    {
      if ( v2 == 1 )
      {
        ((std *)1)->string::_Tidy();
        return;
      }
      if ( LODWORD(((GRPinput *)&stru_D8C2B8)->m_mouseSensitivity) <= 0x1F && LODWORD(((GRPinput *)&stru_D8C2B8)->m_mouseSensitivity) >= v2 - 1 )
        goto LABEL_15;
      ((std *)1)->string::_Tidy();
    }
    ((GRPinput *)&stru_D8C2B8)->PollInputState(v3);
    m_lpDIDKeyboard = ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard;
LABEL_15:
    qmemcpy(m_lpDIDKeyboard, pszName, v3);
    ((GRPinput *)&stru_D8C2B8)->m_lpDIDMouse = (IDirectInputDevice8 *)(v2 - 1);
    ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard[v3] = 0;
  }
}

// 0x00432170
void PalScriptMgr::Destroy()
{
  int *v1; // eax
  int *v2; // edi
  PtrArray *v3; // eax
  int *v4; // esi
  unsigned int nVal; // [esp+0x18] [ebp+0x4]
  char v6; // [esp+0x1C] [ebp+0x8]

  if ( nVal )
  {
    if ( v6 )
      v1 = ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_mouseMinX)->CopyRange(nVal, 0);
    else
      v1 = nVal >= 0x64
         ? ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_joystickX)->CopyRange(nVal, 0)
         : ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_mousept.x)->CopyRange(nVal, 0);
    v2 = v1;
    if ( v1 )
    {
      v3 = (PtrArray *)operator new(0x18u);
      if ( v3 )
        v4 = ((PtrArray *)v3)->Reset();
      else
        v4 = 0;
      if ( v4 )
      {
        v4[1] = (int)v2;
        ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8])->SetAt(*(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12], (int)v4);
      }
      else
      {
        FreeScriptInstance(v2);
      }
    }
  }
}

// 0x00432260
const char ** PalScriptMgr::_CON_State()
{
  int v1; // ecx
  const char ***i; // edx
  const char **result; // eax

  v1 = 0;
  if ( *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] <= 0 )
    return 0;
  for ( i = *(const char ****)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8]; ; ++i )
  {
    if ( v1 >= 0 && v1 < *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] )
    {
      result = *i;
      if ( *i )
      {
        if ( result[1] == pszName )
          break;
      }
    }
    if ( ++v1 >= *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] )
      return 0;
  }
  return result;
}

// 0x004322A0
bool PalScriptMgr::IfAnyScriptRunning(int nVal)
{
  bool result; // al

  ((PtrArray *)&this->m_script.capacity)->SetAt(this->m_script.m_nSize, nVal);
  return result;
}

// 0x004322C0
int PalScriptMgr::IsScriptRuning(int pal)
{
  PalScriptMgr *v2; // ebx
  int m_nSize; // eax
  int v4; // eax
  int v6; // ebp
  int v7; // edi
  PtrArray *p_capacity; // ebx
  _DWORD *v9; // esi
  int v10; // esi
  PalScriptMgr *v11; // [esp+0x10] [ebp-0x4]
m_nSize = this->m_script.m_nSize;
  v11 = this;
  if ( m_nSize )
  {
    v6 = 0;
    v7 = 0;
    if ( m_nSize > 0 )
    {
      p_capacity = (PtrArray *)&this->m_script.capacity;
      do
      {
        if ( v7 < 0 || v7 >= p_capacity->capacity )
          v9 = 0;
        else
          v9 = *(_DWORD **)&p_capacity->m_pData[4 * v7];
        if ( (*(int ( **)(_DWORD *))(*v9 + 4))(v9) )
        {
          (*(void ( **)(_DWORD *, int))(*v9 + 8))(v9, pal);
        }
        else
        {
          if ( v9[1] && v9 )
            (*(void ( **)(_DWORD *, int))*v9)(v9, 1);
          if ( v7 >= 0 && v7 < p_capacity->capacity )
            *(_DWORD *)&p_capacity->m_pData[4 * v7] = 0;
          v6 = 1;
        }
        ++v7;
      }
      while ( v7 < v11->m_script.m_nSize );
      if ( v6 )
      {
        v10 = 0;
        while ( v10 < v11->m_script.m_nSize )
        {
          if ( v10 >= 0 && v10 < p_capacity->capacity && *(_DWORD *)&p_capacity->m_pData[4 * v10] )
            ++v10;
          else
            ((PtrArray *)p_capacity)->RemoveAt(v10, 1);
        }
      }
    }
  }
  else
  {
    while ( 1 )
    {
      ((PtrArray *)this)->_PtrArray();
      if ( v4 == 2 )
        break;
      this = (PalScriptMgr *)this->m_script.m_nSize;
      if ( (int)this > 0 )
        return 0;
    }
    if ( !this->m_script.m_nSize )
      return 1;
  }
  return 0;
}

// 0x004323C0
void PalScriptMgr::RunSceneScript(const char *pszScene)
{
  int v2; // ebp
  int v3; // ebx
  int v4; // esi
  UIListBox *v5; // edi
  int v6; // eax
  int i; // esi

  v2 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12];
  v3 = 0;
  v4 = 0;
  if ( *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] > 0 )
  {
    do
    {
      if ( v4 < 0 || v4 >= *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] )
        v5 = 0;
      else
        v5 = *(UIListBox **)(*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8] + 4 * v4);
      if ( ((PalScriptMgr *)v5)->IsScriptRuning((int)pszScene) )
      {
        if ( v5 )
        {
          ((UIListBox *)v5)->RefreshSelection();
          operator delete(v5);
        }
        if ( v4 >= 0 && v4 < *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] )
          *(_DWORD *)(*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8] + 4 * v4) = 0;
        v3 = 1;
      }
      ++v4;
    }
    while ( v4 < v2 );
    if ( v3 )
    {
      v6 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12];
      for ( i = 0; i < *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12]; v6 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] )
      {
        if ( i >= 0 && i < v6 && *(_DWORD *)(*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8] + 4 * i) )
          ++i;
        else
          ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8])->RemoveAt(i, 1);
      }
    }
  }
}

// 0x00432480
void PalScriptMgr::_CON_ReLoadScript()
{
  PtrArray *v1; // ecx

  ((PtrArray *)v1)->SetSize();
  ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_joystickX)->DestroyAll();
}

// 0x004324A0
BOOL PalScriptMgr::_CON_CloseScript()
{
  return *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] > 0;
}

// 0x004324B0
void PalScriptMgr::ClearAllScript()
{
  int v1; // eax
  void **v2; // esi
  void *v3; // ecx

  if ( pData )
  {
    v1 = 0;
    if ( *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] > 0 )
    {
      v2 = *(void ***)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8];
      do
      {
        if ( v1 < 0 || v1 >= *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] )
          v3 = 0;
        else
          v3 = *v2;
        if ( v3 == pData )
          break;
        ++v1;
        ++v2;
      }
      while ( v1 < *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12] );
    }
  }
}

// 0x00432500
int * PalScriptMgr::FindScriptByDesc(const char *desc)
{
  PalScriptMgr *v2; // ecx
  int *result; // eax
  char Buffer[64]; // [esp+0x0] [ebp-0x40] BYREF

  _snprintf(Buffer, 0x3Fu, "_%s_%s", pszName, desc);
  ((PtrArray *)Buffer)->IsArrayReady();
  ((PalScriptMgr *)v2)->Destroy();
  if ( result )
    ((GRPinput *)&stru_D8C2B8)->m_keyStates[25] = 1;
  return result;
}

// 0x00432550
void PalScriptMgr::IfHaveScript()
{
  int v1; // eax
  int i; // edi
  void *v3; // esi

  v1 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12];
  for ( i = 0; i < v1; ++i )
  {
    if ( i >= 0 && i < v1 )
    {
      v3 = *(void **)(*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8] + 4 * i);
      if ( v3 )
      {
        ((UIListBox *)*(UIListBox **)(*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8] + 4 * i))->RefreshSelection();
        operator delete(v3);
        v1 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[12];
      }
    }
  }
  ((String *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8])->Assign(0, -1);
}

// 0x00434C40
void PalScriptMgr::NotifyEvent(int nEventID)
{
  const char **v1; // eax

  if ( nEventID )
  {
    v1 = ((PalScriptMgr *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode)->_CON_State();
    if ( v1 )
    {
      ((PalScriptMgr *)v1)->IfAnyScriptRunning(nEventID);
    }
    else if ( *(_DWORD *)(nEventID + 4) )
    {
      (**(void ( ***)(int, int))nEventID)(nEventID, 1);
    }
  }
}

// 0x00434C80
void * PalScriptMgr::UpdateLoadProgress()
{
  void *result; // eax

  result = (void *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode;
  *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8) = *(_DWORD *)(*(_DWORD *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 68)
                                                      + *(_DWORD *)(*(_DWORD *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 72);
  return result;
}

// 0x00434CA0
void PalScriptMgr::InitVtable()
{
  int v1; // [esp+0x4] [ebp+0x4]

  this->m_script.capacity = v1;
  this->m_script.m_pData = (char *)1;
}

// 0x00434CC0
BOOL PalScriptMgr::IsWaitComplete()
{
  return byte_DBA25C || g_CCBEditorInst.m_dwTrickID[361] == this->m_script.capacity;
}

// 0x00434D20
BOOL PalScriptMgr::IsBlendComplete()
{
  return *(float *)&this->m_script.m_nSize < (double)*(float *)&this->m_script.capacity;
}

// 0x00434D40
void PalScriptMgr::AccumulateTime(float fDelta)
{
  *(float *)&this->m_script.m_nSize = fDelta + *(float *)&this->m_script.m_nSize;
}

// 0x00450BC0
int PalScriptMgr::ShowTextBox(const char *pszText)
{
  void ( **v3)(PalScriptMgr *, int); // eax
  int result; // eax

  if ( 10 * (strlen(pszText) + 6) >= 0x40 )
    strlen(pszText);
  sub_445FA0(&this->m_fPosZ);
  sub_445DB0(this);
  ((RoleCameraCtrl *)&this->m_fPosZ)->SetName(pszText);
  v3 = *(void ( ***)(PalScriptMgr *, int))&this->m_bGetSceneScript;
  this->m_nExecCounter = 0;
  (*v3)(this, 1);
  ((UIScene *)&this->m_fPosZ)->SetState();
  return result;
}
