#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Script/PalScript.h"

// Forward declarations for unnamed functions
void * GetSaveDataManager(void); // from annotations
int UISceneUpdate(void); // from annotations
_BYTE * sub_430C10(_BYTE *_this, _DWORD *a2, _BYTE *a3); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445AA0(void); // from annotations
void sub_445BF0(int _this, int newElement); // from annotations
int sub_445D20(_DWORD *_this, int a2, int a3); // from annotations
int sub_445DB0(void *a2); // from annotations
int sub_445E50(int a2); // from annotations
void * sub_445EA0(void); // from annotations
int sub_445F60(unsigned int a2); // from annotations
unsigned __int8 __stdcall sub_4A4770(unsigned __int8 a1); // from annotations
int sub_523E70(_DWORD *_this); // from annotations
void sub_536D20(Actor *_this, const char *a2, int a3); // from annotations
int sub_53D2F0(...);
int todo_028(...);
int todo_451730(...);

void AddMoney(int nAmount); // from annotations
int * AddNPCToPartySlot(int nRoleSlot, int nNpcId); // from annotations
int ConvertDirection(int nDir); // from annotations
int * ctor_0x431870(int *_this); // from annotations
int FindOpcodeByName(char *pszCmdName); // from annotations
void FreeScriptInstance(int *pInstance); // from annotations
void * GetSceneObject(unsigned __int16 nObjID); // from annotations
struct gbVFileSystem * LoadScene(double sceneNames, char *arg8, char *pszBuf, char pData, char pData2); // from annotations
int LoadScriptFile(const char *pszFileName); // from annotations
char * MovePartyFollowers(char *bNotifyScript); // from annotations
void RestorePartyFollowMode(int bNotifyScript); // from annotations
void SetGameSwitch(int nSwitchIdx); // from annotations
char * SetRoleLevelAndRefresh(int nRoleIdx, int nLevel); // from annotations
char SetupPartyFormation(int bNotifyScript); // from annotations
char SetupPartyFormationWide(int bNotifyScript); // from annotations

// Unnamed globals (extern)
extern CHAR asc_5B1E74[2];
extern char byte_1010101;
extern char byte_5967B0[3];
extern char byte_BFDA40;
extern char byte_BFDA41;
extern int dword_C1171C;
extern int dword_D8BC38;
extern PalScript * dword_D8C2B0;
extern int dword_DBA118;
extern int dword_DBA240;
extern int dword_DBA244;
extern int dword_DBA248;
extern PalScriptMgr * dword_DBA24C;
extern PalScriptMgr * dword_DBA254;
extern int dword_DBA830[];
void __cdecl nullsub_11(...);
void __cdecl nullsub_2(...);
extern const char * off_56ABA4;
extern const char * off_58B448;
extern const char * off_592DA4;
extern const char * off_596420;
extern const char * off_596424;
extern TextureLibDataBase stru_1894B78;
extern RoleSystem stru_C059A0;
extern RoleSystem stru_C08160;
extern PalScript stru_C11720;
extern GRPinput stru_D8C2B8;
extern PalScriptIdleObj stru_DBA0D4;
extern RoleCameraCtrl stru_DBA134;
extern CHAR unk_5E2540[];
extern CHAR unk_5E25F4[];
extern CHAR unk_5E286C[];
extern CHAR unk_5E28E4[];
extern int unknown_libname_339;
void __cdecl unknown_libname_340(void);

// 0x00410840
PalScript * PalScript::InitParticleSlht(PalScript *pPalScript)
{
  PalScript *result; // eax
  gbParticleEffect *v3; // eax
  gbParticleEffect *v4; // esi
  PalScript *v5; // ecx

  result = pPalScript;
  if ( pPalScript )
  {
    v3 = (gbParticleEffect *)operator new(0x160u);
    v4 = v3;
    if ( v3 )
    {
      v5 = (PalScript *)v4;
    }
    else
    {
      v5 = 0;
    }
    g_pCurrentScript = v5;
    ((gbParticleEffect *)v5)->LoadFromFile("effect\\gbParticle\\slht.par");
    result = g_pCurrentScript;
    g_pCurrentScript->m_fScaleY = 8.0;
  }
  else
  {
    if ( g_pCurrentScript )
      result = (PalScript *)(*(int ( **)(PalScript *, int))g_pCurrentScript->m_bLoadSceneScript)(
                              g_pCurrentScript,
                              1);
    g_pCurrentScript = 0;
  }
  return result;
}

// 0x00412680
int PalScript::DestroyScript()
{
  int ( ***v2)(_DWORD, int); // ecx
  int result; // eax

  v2 = *(int ( ****)(_DWORD, int))&this->m_szDialog1[140];
  this->m_fSceneCfg[17] = 0.0;
  if ( v2 )
  {
    result = (**v2)(v2, 1);
    *(_DWORD *)&this->m_szDialog1[140] = 0;
  }
  *(_DWORD *)&this->m_szDialog1[152] = 0;
  *(_DWORD *)&this->m_szDialog1[148] = 0;
  *(&this->_todo_468 + 35) = 0;
  *(_DWORD *)&this->m_szDialog1[160] = 0;
  this->m_nPathState = 0;
  return result;
}

// 0x00421560
void PalScript::SetAction(int nRoleID)
{
  int m_nRoleCount; // esi
  int v3; // eax
  unsigned __int8 *p_m_RoleSlotArray; // edx

  m_nRoleCount = this->m_nRoleCount;
  v3 = 0;
  if ( m_nRoleCount > 0 )
  {
    p_m_RoleSlotArray = &this->m_RoleSlotArray;
    do
    {
      if ( *p_m_RoleSlotArray == (_WORD)nRoleID )
        break;
      ++v3;
      p_m_RoleSlotArray += 896;
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
    p_m_RoleActionType = &this->m_RoleActionType;
    do
    {
      if ( *(p_m_RoleActionType - 72) != 32 && *p_m_RoleActionType == 25 )
      {
        v5 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Find(p_m_RoleActionType - 68);
        *(p_m_RoleActionType - 71) = v5;
        v3 = v3 && v5;
      }
      ++v2;
      p_m_RoleActionType += 896;
    }
    while ( v2 < this->m_nRoleCount );
  }
  this->SetAction(32);
  if ( v6 )
    *(_BYTE *)(v6 + 173) = v3;
}

// 0x00429D10
int * PalScript::GetCount(int nVal)
{
  int *result; // eax

  if ( this->m_bLoadSceneScript == 3 )
    return (*(int *( **)(scScriptInstance *))&this->m_pinst->pblock->desc[16])(this->m_pinst);
  result = (int *)(this->m_bLoadSceneScript - 4);
  if ( this->m_bLoadSceneScript == 4 )
    return (*(int *( **)(scScriptInstance *, int))&this->m_pinst->pblock->desc[44])(this->m_pinst, nVal);
  return result;
}

// 0x00429D40
void PalScript::SetIndex(int nVal)
{
  switch ( this->m_bLoadSceneScript )
  {
    case 1:
    case 2:
    case 3:
      (*(void ( **)(scScriptInstance *, int))&this->m_pinst->pblock->desc[12])(this->m_pinst, nVal);
      break;
    case 4:
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
    m_EncampSound = (gbSound3DNode *)this->m_EncampSound;
    if ( m_EncampSound )
    {
      if ( (g_dwGameFlags & 1) != 0 )
        ((gbSound3DNode *)m_EncampSound)->Stop();
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
ctor_0x431870((int *)&v22.m_ptr_4 + 5);
  v23 = 0;
  ((PalScript *)(&v22.m_ptr_4 + 5))->LoadFromFile((char *)pathAddr);
  ((PalScript *)(&v22.m_ptr_4 + 5))->SetDirectory("pal3lang");
  LOBYTE(p_DWORD) = v11;
  ((std *)0)->string::_Tidy();
  for ( LOBYTE(v23) = 1; ((PalScript *)(&v22.m_ptr_4 + 5))->HasNext(); v19 = 0 )
  {
    if ( !_strcmpi((const char *)&v22.m_ptr_4 + 20, (const char *)&off_58B448) )
      break;
    v2 = strlen((const char *)&v22.m_ptr_4 + 20) + 1;
    v3 = v2 - 1;
    if ( ((SceneObj *)&p_DWORD)->UpdateAutoDelete(v2 - 1) )
    {
      qmemcpy(v13, &v22.m_ptr_4 + 5, v3);
      v14 = v2 - 1;
      v13[v3] = 0;
    }
    ((PalScript *)(&v22.m_ptr_4 + 5))->LoadNext();
    LOBYTE(nVal) = v11;
    ((std *)0)->string::_Tidy();
    v4 = strlen((const char *)&v22.m_ptr_4 + 20) + 1;
    v5 = v4 - 1;
    if ( ((SceneObj *)&nVal)->UpdateAutoDelete(v4 - 1) )
    {
      qmemcpy(v17, &v22.m_ptr_4 + 5, v5);
      v18 = v4 - 1;
      v17[v5] = 0;
    }
    LOBYTE(v23) = 2;
    pszBuf[0] = p_DWORD;
    ((std *)0)->string::_Tidy();
    ((PalScript *)pszBuf)->InitScriptObj(&p_DWORD, 0, 0xFFFFFFFF);
    LOBYTE(v23) = 3;
    ((Config *)&v22)->ParseSection((int)&nVal);
    LOBYTE(v23) = 4;
    ((PalScript *)v20)->EvalExpression((int *)&v22.m_ptr_4 + 3, pszBuf);
    LOBYTE(v23) = 5;
    ((std *)1)->string::_Tidy();
    LOBYTE(v23) = 2;
    ((std *)1)->string::_Tidy();
    LOBYTE(v23) = 1;
    if ( v17 )
    {
      v6 = v17 - 1;
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
    v8 = v13 - 1;
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
  ((PalScript *)(&v22.m_ptr_4 + 5))->Cleanup();
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
  this->m_CamObj = 0;
  this->m_fScriptTimer = 0.0;
  m_pinst = this->m_pinst;
  if ( m_pinst )
  {
    v6 = (char *)&m_pinst[-1].uservar + 3;
    uservar_high = HIBYTE(m_pinst[-1].uservar);
    if ( uservar_high && uservar_high != -1 )
    {
      *v6 = uservar_high - 1;
      this->m_pinst = 0;
      this->m_waitobj = 0;
      this->m_fBlendFactor = 0.0;
      return;
    }
    operator delete(v6);
  }
  this->m_pinst = 0;
  this->m_waitobj = 0;
  this->m_fBlendFactor = 0.0;
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
  ((std *)0)->string::_Tidy();
  v3 = name;
  v4 = strlen(name) + 1;
  v5 = v4 - 1;
  if ( ((SceneObj *)&nIdx)->UpdateAutoDelete(v4 - 1) )
  {
    qmemcpy(v15, v3, v5);
    v16 = v4 - 1;
    v15[v5] = 0;
  }
  v17 = 0;
  v6 = (char *)*this->GetVarRef(&pOut, (int)&nIdx);
  m_pinst = this->m_pinst;
  name = v6;
  if ( v6 == (char *)m_pinst || ((PalScript *)&nIdx)->CompareBuffer((int)(v6 + 12)) < 0 )
  {
    v12 = this->m_pinst;
    p_name = (char **)&v12;
  }
  else
  {
    p_name = &name;
  }
  v9 = *p_name;
  v17 = -1;
  ((std *)1)->string::_Tidy();
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
// [IDA_MISID]     std::_Xran();
  v6 = (PtrArray *)(p_DWORD[2] - dwVal);
  if ( dwVal2 < (unsigned int)v6 )
    v6 = (PtrArray *)dwVal2;
  if ( this == (PalScript *)p_DWORD )
  {
    v7 = -1;
    v8 = (PtrArray *)((char *)v6 + dwVal);
    if ( this->m_waitobj < v8 )
// [IDA_MISID]       std::_Xran();
    ((std *)this)->string::_Split();
    v9 = (char *)((char *)this->m_waitobj - (char *)v8);
    if ( v9 != (char *)-1 )
      v7 = (char *)this->m_waitobj - (char *)v8;
    if ( v7 )
    {
      memcpy((char *)v8 + (unsigned int)this->m_pinst, (char *)v8 + (unsigned int)this->m_pinst + v7, (size_t)&v9[-v7]);
      v10 = (PtrArray *)((char *)this->m_waitobj - v7);
      if ( ((SceneObj *)this)->UpdateAutoDelete((unsigned int)v10) )
      {
        m_pinst = this->m_pinst;
        this->m_waitobj = v10;
        *((_BYTE *)&m_pinst->pblock + (_DWORD)v10) = 0;
      }
      v4 = dwVal;
    }
    v12 = (PtrArray *)v4;
    ((std *)this)->string::_Split();
    m_waitobj = this->m_waitobj;
    if ( (unsigned int)m_waitobj < v4 )
      v12 = this->m_waitobj;
    if ( v12 )
    {
      memcpy(this->m_pinst, (char *)this->m_pinst + (unsigned int)v12, (char *)m_waitobj - (char *)v12);
      v14 = (char *)((char *)this->m_waitobj - (char *)v12);
      if ( ((SceneObj *)this)->UpdateAutoDelete((unsigned int)v14) )
      {
        ((std *)v14)->string::_Eos();
        return (int)this;
      }
    }
    return (int)this;
  }
  if ( !v6 || v6 != (PtrArray *)p_DWORD[2] )
    goto LABEL_32;
  v16 = (unsigned __int8 *)p_DWORD[1];
  if ( !v16 )
    v16 = &g_bActorFlag;
  if ( *(v16 - 1) >= 0xFEu )
  {
LABEL_32:
    if ( ((std *)this)->string::max_size() < (unsigned int)v6 )
// [IDA_MISID]       std::_Xlen();
    v21 = this->m_pinst;
    if ( v21 && (uservar_high = HIBYTE(v21[-1].uservar)) != 0 && uservar_high != -1 )
    {
      if ( !v6 )
      {
        HIBYTE(v21[-1].uservar) = uservar_high - 1;
        ((std *)0)->string::_Tidy();
        return (int)this;
      }
    }
    else
    {
      if ( !v6 )
      {
        ((std *)1)->string::_Tidy();
        return (int)this;
      }
      m_fBlendFactor = this->m_fBlendFactor;
      if ( LODWORD(m_fBlendFactor) <= 0x1F && LODWORD(m_fBlendFactor) >= (unsigned int)v6 )
        goto LABEL_45;
      ((std *)1)->string::_Tidy();
    }
    ((GRPinput *)this)->PollInputState((unsigned int)v6);
LABEL_45:
    v24 = (unsigned __int8 *)p_DWORD[1];
    if ( !v24 )
      v24 = &g_bActorFlag;
    qmemcpy(this->m_pinst, &v24[dwVal], (unsigned int)v6);
    v25 = this->m_pinst;
    this->m_waitobj = v6;
    *((_BYTE *)&v25->pblock + (_DWORD)v6) = 0;
    return (int)this;
  }
  v17 = this->m_pinst;
  if ( v17 )
  {
    v18 = (char *)&v17[-1].uservar + 3;
    v19 = HIBYTE(v17[-1].uservar);
    if ( !v19 || v19 == -1 )
      operator delete(v18);
    else
      *v18 = v19 - 1;
  }
  this->m_pinst = 0;
  this->m_waitobj = 0;
  this->m_fBlendFactor = 0.0;
  v20 = (unsigned __int8 *)p_DWORD[1];
  if ( !v20 )
    v20 = &g_bActorFlag;
  this->m_pinst = (scScriptInstance *)v20;
  this->m_waitobj = (PtrArray *)p_DWORD[2];
  LODWORD(this->m_fBlendFactor) = p_DWORD[3];
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
  int v12; // edx
  int *v13; // eax
  int *v14; // [esp-0x8] [ebp-0x44]
  char a3; // [esp+0x13] [ebp-0x29] BYREF
  scScriptInstance *a2; // [esp+0x14] [ebp-0x28] BYREF
  int v17; // [esp+0x18] [ebp-0x24] BYREF
  int v18; // [esp+0x1C] [ebp-0x20]
  _BYTE v19[8]; // [esp+0x20] [ebp-0x1C] BYREF
  _BYTE v20[8]; // [esp+0x28] [ebp-0x14] BYREF
  int v21; // [esp+0x38] [ebp-0x4]

  m_pinst = this->m_pinst;
  v5 = 1;
  v6 = *(PalScript **)&m_pinst->runmode;
  v7 = pszBuf;
  v21 = 0;
  while ( v6 != dword_D8C2B0 )
  {
    m_nState = (unsigned __int8 *)v6->m_nState;
    m_pinst = (scScriptInstance *)v6;
    if ( !m_nState )
      m_nState = &g_bActorFlag;
    v5 = (int)((std *)0)->string::_Grow(*((_DWORD *)v7 + 2), m_nState, v6->m_nFrameCount) < 0;
    if ( v5 )
      v6 = (PalScript *)v6->m_bLoadSceneScript;
    else
      v6 = (PalScript *)v6->m_waitobj;
  }
  m_waitobj = (char)this->m_waitobj;
  v21 = -1;
  if ( m_waitobj )
    goto LABEL_9;
  a2 = m_pinst;
  if ( v5 )
  {
    if ( m_pinst == (scScriptInstance *)this->m_pinst->pblock )
    {
LABEL_9:
      v10 = *this->EvalExprTree((int *)&pszBuf, v6, (int *)m_pinst, v7);
      LOBYTE(v18) = 1;
      v12 = v18;
      *p_DWORD = v10;
      p_DWORD[1] = v12;
      return p_DWORD;
    }
    ((PalScript *)&a2)->IteratorNext();
  }
  if ( ((PalScript *)&a2->codeptr)->CompareBuffer((int)v7) >= 0 )
  {
    a3 = 0;
    v13 = (int *)sub_430C10(v20, &a2, &a3);
  }
  else
  {
    LOBYTE(pszBuf) = 1;
    v14 = this->EvalExprTree(&v17, v6, (int *)m_pinst, v7);
    v13 = (int *)sub_430C10(v19, v14, &pszBuf);
  }
  *p_DWORD = *v13;
  p_DWORD[1] = v13[1];
  return p_DWORD;
}

// 0x00431040
int * PalScript::GetVarRef(int *pOut, int nIdx)
{
  *pOut = (int)this->ResolveScope(nIdx);
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

  v6 = operator new(0x30u);
  *((_DWORD *)v6 + 1) = p_DWORD2;
  *((_DWORD *)v6 + 11) = 0;
  *(_DWORD *)v6 = dword_D8C2B0;
  v7 = dword_D8C2B0;
  *((_DWORD *)v6 + 2) = dword_D8C2B0;
  ((PalScript *)v7)->ConstructStringObj((char *)v6 + 12);
  m_pinst = (int *)this->m_pinst;
  ++LODWORD(this->m_fBlendFactor);
  if ( p_DWORD2 == m_pinst
    || pData != dword_D8C2B0
    || ((PalScript *)pszBuf)->CompareBuffer((int)(p_DWORD2 + 3)) < 0 )
  {
    *p_DWORD2 = (int)v6;
    v10 = (int *)this->m_pinst;
    if ( p_DWORD2 == v10 )
    {
      v10[1] = (int)v6;
      this->m_pinst->pcaller = (scScriptInstance *)v6;
    }
    else if ( p_DWORD2 == (int *)*v10 )
    {
      *v10 = (int)v6;
    }
  }
  else
  {
    p_DWORD2[2] = (int)v6;
    v9 = this->m_pinst;
    if ( p_DWORD2 == (int *)v9->pcaller )
      v9->pcaller = (scScriptInstance *)v6;
  }
  v11 = (scScriptInstance *)v6;
  if ( v6 != *(void **)&this->m_pinst->runmode )
  {
    do
    {
      v12 = *(scScriptInstance ***)&v11->runmode;
      if ( v12[11] )
        break;
      v13 = v12[1];
      pblock = (scScriptInstance **)v13->pblock;
      if ( v12 == (scScriptInstance **)v13->pblock )
      {
        pcaller = v13->pcaller;
        if ( pcaller->reg[3].data.as_int )
        {
          if ( v11 == v12[2] )
          {
            v11 = *(scScriptInstance **)&v11->runmode;
            v16 = (scScriptInstance **)v12[2];
            v11->pcaller = *v16;
            if ( *v16 != (scScriptInstance *)dword_D8C2B0 )
              *(_DWORD *)&(*v16)->runmode = v11;
            v16[1] = *(scScriptInstance **)&v11->runmode;
            v17 = this->m_pinst;
            if ( v11 == *(scScriptInstance **)&v17->runmode )
            {
              *(_DWORD *)&v17->runmode = v16;
            }
            else
            {
              v18 = *(scScriptInstance ***)&v11->runmode;
              if ( v11 == *v18 )
                *v18 = (scScriptInstance *)v16;
              else
                v18[2] = (scScriptInstance *)v16;
            }
            *v16 = v11;
            *(_DWORD *)&v11->runmode = v16;
          }
          *(_DWORD *)(*(_DWORD *)&v11->runmode + 44) = 1;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v11->runmode + 4) + 44) = 0;
          v19 = *(scScriptInstance **)(*(_DWORD *)&v11->runmode + 4);
          v20 = (scScriptInstance **)v19->pblock;
          v19->pblock = *(scScriptBlock **)&v19->pblock->desc[4];
          v21 = (PalScript *)v20[2];
          if ( v21 != dword_D8C2B0 )
            v21->m_pinst = v19;
          v20[1] = *(scScriptInstance **)&v19->runmode;
          v22 = this->m_pinst;
          if ( v19 == *(scScriptInstance **)&v22->runmode )
          {
            *(_DWORD *)&v22->runmode = v20;
            v20[2] = v19;
          }
          else
          {
            v23 = *(scScriptInstance ****)&v19->runmode;
            if ( v19 == (scScriptInstance *)v23[2] )
              v23[2] = v20;
            else
              *v23 = v20;
            v20[2] = v19;
          }
LABEL_51:
          *(_DWORD *)&v19->runmode = v20;
          continue;
        }
        v12[11] = (scScriptInstance *)1;
        pcaller->reg[3].data.as_int = (char *)1;
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v11->runmode + 4) + 44) = 0;
        v11 = *(scScriptInstance **)(*(_DWORD *)&v11->runmode + 4);
      }
      else
      {
        if ( pblock[11] )
        {
          if ( v11 == *v12 )
          {
            v11 = *(scScriptInstance **)&v11->runmode;
            v24 = *v12;
            v11->pblock = (scScriptBlock *)v24->pcaller;
            v25 = (PalScript *)v24->pcaller;
            if ( v25 != dword_D8C2B0 )
              v25->m_pinst = v11;
            *(_DWORD *)&v24->runmode = *(_DWORD *)&v11->runmode;
            v26 = this->m_pinst;
            if ( v11 == *(scScriptInstance **)&v26->runmode )
            {
              *(_DWORD *)&v26->runmode = v24;
            }
            else
            {
              v27 = *(scScriptInstance ***)&v11->runmode;
              if ( v11 == v27[2] )
                v27[2] = v24;
              else
                *v27 = v24;
            }
            v24->pcaller = v11;
            *(_DWORD *)&v11->runmode = v24;
          }
          *(_DWORD *)(*(_DWORD *)&v11->runmode + 44) = 1;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v11->runmode + 4) + 44) = 0;
          v19 = *(scScriptInstance **)(*(_DWORD *)&v11->runmode + 4);
          v20 = (scScriptInstance **)v19->pcaller;
          v19->pcaller = *v20;
          if ( *v20 != (scScriptInstance *)dword_D8C2B0 )
            *(_DWORD *)&(*v20)->runmode = v19;
          v20[1] = *(scScriptInstance **)&v19->runmode;
          v28 = this->m_pinst;
          if ( v19 == *(scScriptInstance **)&v28->runmode )
          {
            *(_DWORD *)&v28->runmode = v20;
          }
          else
          {
            v29 = *(scScriptInstance ***)&v19->runmode;
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
        v11 = *(scScriptInstance **)(*(_DWORD *)&v11->runmode + 4);
      }
    }
    while ( v11 != *(scScriptInstance **)&this->m_pinst->runmode );
  }
  *(_DWORD *)(*(_DWORD *)&this->m_pinst->runmode + 44) = 1;
  *p_DWORD = (int)v6;
  return p_DWORD;
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
  v11 = result;
  v3 = result[1];
  if ( (PalScript *)v3 != dword_D8C2B0 )
  {
    v4 = *(_DWORD *)(nVal + 8);
    v5 = *(unsigned __int8 **)(nVal + 4);
    for ( nVala = (int)v5; ; v5 = (unsigned __int8 *)nVala )
    {
      v6 = &g_bActorFlag;
      if ( v5 )
        v6 = v5;
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
      if ( (PalScript *)v3 == dword_D8C2B0 )
        return v11;
    }
  }
  return result;
}

// 0x00431440
int * PalScript::IteratorNext()
{
  int m_bLoadSceneScript; // eax
  int *result; // eax
  PalScript *v3; // edx

  m_bLoadSceneScript = this->m_bLoadSceneScript;
  if ( *(_DWORD *)(this->m_bLoadSceneScript + 44)
    || *(_DWORD *)(*(_DWORD *)(m_bLoadSceneScript + 4) + 4) != m_bLoadSceneScript )
  {
    v3 = *(PalScript **)m_bLoadSceneScript;
    if ( *(PalScript **)m_bLoadSceneScript == dword_D8C2B0 )
    {
      for ( result = *(int **)(m_bLoadSceneScript + 4); this->m_bLoadSceneScript == *result; result = (int *)result[1] )
        this->m_bLoadSceneScript = (int)result;
      this->m_bLoadSceneScript = (int)result;
    }
    else
    {
      for ( result = (int *)v3->m_waitobj; result != (int *)dword_D8C2B0; result = (int *)result[2] )
        v3 = (PalScript *)result;
      this->m_bLoadSceneScript = (int)v3;
    }
  }
  else
  {
    result = *(int **)(m_bLoadSceneScript + 8);
    this->m_bLoadSceneScript = (int)result;
  }
  return result;
}

// 0x004314A0
int * PalScript::IteratorPrev()
{
  PalScript *v1; // edx
  int *result; // eax

  v1 = *(PalScript **)(this->m_bLoadSceneScript + 8);
  if ( v1 == dword_D8C2B0 )
  {
    for ( result = *(int **)(this->m_bLoadSceneScript + 4); this->m_bLoadSceneScript == result[2]; result = (int *)result[1] )
      this->m_bLoadSceneScript = (int)result;
    if ( *(int **)(this->m_bLoadSceneScript + 8) != result )
      this->m_bLoadSceneScript = (int)result;
  }
  else
  {
    for ( result = (int *)v1->m_bLoadSceneScript; result != (int *)dword_D8C2B0; result = (int *)*result )
      v1 = (PalScript *)result;
    this->m_bLoadSceneScript = (int)v1;
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
    ((PalScript *)pszBuf)->InitScriptObj(p_DWORD, 0, 0xFFFFFFFF);
    pszBuf[16] = *((_BYTE *)p_DWORD + 16);
    *((_DWORD *)pszBuf + 5) = 0;
    *((_DWORD *)pszBuf + 6) = 0;
    *((_DWORD *)pszBuf + 7) = 0;
    v3 = p_DWORD[6];
    if ( pszBuf + 16 == (char *)(p_DWORD + 4) )
    {
      ((PalScript *)(pszBuf + 16))->SetWaitRange(v3, 0xFFFFFFFF);
      ((PalScript *)(pszBuf + 16))->SetWaitRange(0, 0);
    }
    else
    {
      if ( !v3 )
        goto LABEL_17;
      v4 = (unsigned __int8 *)p_DWORD[5];
      if ( !v4 )
        v4 = &g_bActorFlag;
      if ( *(v4 - 1) < 0xFEu )
      {
        *((_DWORD *)pszBuf + 5) = 0;
        *((_DWORD *)pszBuf + 6) = 0;
        *((_DWORD *)pszBuf + 7) = 0;
        v5 = (unsigned __int8 *)p_DWORD[5];
        if ( !v5 )
          v5 = &g_bActorFlag;
        *((_DWORD *)pszBuf + 5) = v5;
        *((_DWORD *)pszBuf + 6) = p_DWORD[6];
        *((_DWORD *)pszBuf + 7) = p_DWORD[7];
        ++*(v5 - 1);
      }
      else
      {
LABEL_17:
        if ( ((SceneObj *)(pszBuf + 16))->UpdateAutoDelete(v3) )
        {
          v6 = &g_bActorFlag;
          if ( p_DWORD[5] )
            v6 = (unsigned __int8 *)p_DWORD[5];
          qmemcpy(*((void **)pszBuf + 5), v6, v3);
          ((std *)v3)->string::_Eos();
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
  scScriptInstance *v14; // ecx

  if ( this->m_waitobj < (PtrArray *)dwVal )
// [IDA_MISID]     std::_Xran();
  m_pinst = this->m_pinst;
  if ( m_pinst )
  {
    uservar_high = HIBYTE(m_pinst[-1].uservar);
    if ( uservar_high )
    {
      if ( uservar_high != -1 )
      {
        v6 = this->m_pinst;
        HIBYTE(m_pinst[-1].uservar) = uservar_high - 1;
        this->m_pinst = 0;
        this->m_waitobj = 0;
        this->m_fBlendFactor = 0.0;
        v7 = strlen((const char *)v6);
        if ( ((SceneObj *)this)->UpdateAutoDelete(v7) )
        {
          qmemcpy(this->m_pinst, m_pinst, v7);
          ((std *)v7)->string::_Eos();
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
// [IDA_MISID]     std::_Xlen();
  v11 = this->m_pinst;
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
          ((std *)0)->string::_Tidy();
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
      v14 = this->m_pinst;
      this->m_waitobj = v10;
      *((_BYTE *)&v14->pblock + (_DWORD)v10) = 0;
      return (int)this;
    }
LABEL_22:
    ((GRPinput *)this)->PollInputState((char *)this->m_waitobj - v8);
    goto LABEL_23;
  }
  if ( v11 )
  {
    this->m_waitobj = 0;
    LOBYTE(v11->pblock) = 0;
    return (int)this;
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
  v4 = *(unsigned __int8 **)(nDescriptor + 4);
  if ( !v4 )
    v4 = &g_bActorFlag;
  m_waitobj = this->m_waitobj;
  v5 = m_waitobj;
  if ( (unsigned int)m_waitobj >= v3 )
    m_waitobj = *(PtrArray **)(nDescriptor + 8);
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
// attributes: thunk
void PalScript::Cleanup()
{

}

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

  v9 = 0;
  v3 = ((gbVFileSystem *)g_pVFileSys)->OpenFile(filename, 0x201u);
  v4 = v3;
  if ( v3 )
  {
    ((gbVFileSystem *)g_pVFileSys)->Seek(v3, 0, 3);
    v5 = ((gbVFileSystem *)g_pVFileSys)->TellPos(v4);
    ((gbVFileSystem *)g_pVFileSys)->Seek(v4, 0, 1);
    v6 = malloc(v5 + 1);
    this->m_nLoadFromFile = (int)v6;
    if ( v6 )
    {
      memset(v6, 0, v5 + 1);
      ((gbVFileSystem *)g_pVFileSys)->Read((void *)this->m_nLoadFromFile, v5, v4);
      this->m_nLoadState = this->m_nLoadFromFile;
      ((gbVFileSystem *)g_pVFileSys)->CloseFile(v4);
    }
  }
  v9 = -1;
  return result;
}

// 0x004319C0
void PalScript::FreeLoadBuffer()
{
  if ( this->m_nLoadFromFile )
  {
    free((void *)this->m_nLoadFromFile);
    this->m_nLoadFromFile = 0;
  }
  this->m_nLoadState = 0;
  this->m_nNext = 0;
}

// 0x004319F0
int PalScript::SetDirectory(char *dir)
{
  BOOL v3; // edi
  int result; // eax

  v3 = 0;
  this->m_nNext = this->m_nLoadFromFile;
  for ( result = this->HasNext(); result; result = this->HasNext() )
  {
    if ( v3 )
    {
      result = _strcmpi((const char *)this, dir);
      if ( !result )
      {
        this->m_nLoadState = this->m_nNext;
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
  if ( *(_BYTE *)this->m_nNext )
  {
do
    {
      if ( v2 > 2 )
      {
        if ( v2 != 3 )
          return 1;
        if ( *(_BYTE *)this->m_nNext == 38 )
          goto LABEL_30;
      }
      else
      {
        if ( v2 == 2 )
        {
          v5 = *(_BYTE *)this->m_nNext;
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
            LOBYTE(this->m_bLoadSceneScript) = v5;
            v3 = (PalScript *)((char *)v3 + 1);
          }
          goto LABEL_31;
        }
        if ( !v2 )
        {
          v4 = *(_BYTE *)this->m_nNext;
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
            LOBYTE(this->m_bLoadSceneScript) = v4;
            v3 = (PalScript *)((char *)v3 + 1);
            v2 = 2;
          }
          goto LABEL_31;
        }
        if ( *(_BYTE *)this->m_nNext == 10 )
LABEL_30:
          v2 = 0;
      }
LABEL_31:
      v6 = (_BYTE *)(this->m_nNext + 1);
      this->m_nNext = (int)v6;
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
  if ( *(_BYTE *)this->m_nNext )
  {
do
    {
      if ( result > 2 )
        break;
      if ( result == 2 )
      {
        v5 = *(_BYTE *)this->m_nNext;
        if ( v5 == 38 )
        {
          result = 255;
        }
        else
        {
          LOBYTE(this->m_bLoadSceneScript) = v5;
          v3 = (PalScript *)((char *)v3 + 1);
        }
      }
      else if ( result )
      {
        result = *(_BYTE *)this->m_nNext != 10;
      }
      else
      {
        v4 = *(_BYTE *)this->m_nNext;
        if ( v4 == 59 )
        {
          result = 1;
        }
        else if ( v4 == 36 )
        {
          result = 2;
        }
      }
      v6 = (_BYTE *)(this->m_nNext + 1);
      this->m_nNext = (int)v6;
    }
    while ( *v6 );
  }
  return result;
}

// 0x00431C00
int PalScript::SaveLoadState()
{
  int result; // eax

  result = this->m_nLoadState;
  this->m_nNext = result;
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

  v6 = 0;
  while ( 1 )
  {
    if ( !this->HasNext() )
      return 0;
    if ( !_strcmpi((const char *)this, (const char *)String1) )
      break;
    if ( _strcmpi((const char *)this, (const char *)&off_592DA4) )
    {
      if ( ++v6 < 1024 )
        continue;
    }
    return 0;
  }

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
    this->m_pinst = 0;
  }
  for ( i = 0; i < SLODWORD(this->m_fBlendFactor); ++i )
  {
    if ( i < 0 || i >= SLODWORD(this->m_fBlendFactor) )
      v3 = 0;
    else
      v3 = *((_DWORD *)&this->m_waitobj->m_pData + i);
    if ( *(_DWORD *)(v3 + 4) && v3 )
      (**(void ( ***)(int, int))v3)(v3, 1);
  }
  ((String *)&this->m_waitobj)->Assign(0, -1);
}

// 0x00431D80
void PalScript::PalScript_1d80()
{
  unknown_libname_339(this);
  atexit(unknown_libname_340);
}

// 0x00431F00
void PalScript::AddWaitObj()
{

  atexit((void ( *)())PalScript::ClearAllCamObj);
}

// 0x00431F10
int PalScript::AddCamObj()
{
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_lpDI) = HIBYTE(this);
  ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard = 0;
  ((GRPinput *)&stru_D8C2B8)->m_lpDIDMouse = 0;
  ((GRPinput *)&stru_D8C2B8)->m_mouseSensitivity = 0.0;
  return 0;
}

// 0x00431F40
void PalScript::ClearAllCamObj()
{
  IDirectInputDevice8 v1; // al

  if ( (((GRPinput *)&stru_D8C2B8)->m_keyStates[4] & 0x10) == 0 )
  {
    ((GRPinput *)&stru_D8C2B8)->m_keyStates[4] |= 0x10u;
    if ( ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard )
    {
      v1 = ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard[-1];
      if ( !*(_BYTE *)&v1 || v1 == 0xFF )
        operator delete(&((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard[-1]);
      else
        ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard[-1] = (IDirectInputDevice8)(*(_BYTE *)&v1 - 1);
    }
    ((GRPinput *)&stru_D8C2B8)->m_lpDIDKeyboard = 0;
    ((GRPinput *)&stru_D8C2B8)->m_lpDIDMouse = 0;
    ((GRPinput *)&stru_D8C2B8)->m_mouseSensitivity = 0.0;
  }
}

// 0x00431FA0
// attributes: thunk
void PalScript::ClearAllWaitObj()
{
  ((PalScriptMgr *)this)->_CON_ReLoadScript();
}

// 0x00431FB0
void PalScript::Update()
{
  int v1; // eax
  int v2; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x800] BYREF
  char ArgList[1024]; // [esp+0x408] [ebp-0x400] BYREF

  ((PalScriptMgr *)this)->_CON_ReLoadScript();
  if ( !LoadScriptFile(pszFileName) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("Script sys init failed.", "D:\\Project\\PAL3\\script\\PalScript.cpp", 71),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_mousept)->InsertAt("init.sce");
  if ( !v1 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("System script load failed.", "D:\\Project\\PAL3\\script\\PalScript.cpp", 73),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_mouseMinX)->InsertAt("ui\\bigmap\\bigmap.sce");
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("BigMap script load failed.", "D:\\Project\\PAL3\\script\\PalScript.cpp", 75),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x00433F90
int PalScript::ProcessGBKString()
{
  unsigned __int16 *v0; // ecx
  unsigned __int16 v1; // ax
  unsigned __int16 *v2; // ecx
  unsigned __int16 v3; // si
  int v4; // ebx
  int i; // edi
  char v6; // al
  unsigned __int16 *v7; // eax
  unsigned __int16 v8; // dx
  int v9; // esi
  int v10; // ebp
  char *v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  bool v15; // cc
  int v16; // eax
  int v17; // edx
  char bOwned; // [esp+0xC] [ebp-0x10]
  unsigned __int16 v20; // [esp+0x10] [ebp-0xC]
  int nInitSize; // [esp+0x14] [ebp-0x8] BYREF
  int v22; // [esp+0x18] [ebp-0x4]

  v0 = *(unsigned __int16 **)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8);
  v1 = *v0;
  *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8) = v0 + 1;
  v2 = *(unsigned __int16 **)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8);
  v3 = *v2;
  v4 = 16 * v1;
  *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8) = v2 + 1;
  v20 = v3;
  for ( i = *(unsigned __int16 *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[v4 + 68] - 1; i >= 0; --i )
  {
    v6 = ((GRPinput *)&stru_D8C2B8)->m_keyRaw[v4 + 60 + i];
    if ( v6 == -6 )
    {
      v7 = *(unsigned __int16 **)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8);
      v8 = *v7;
      *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8) = v7 + 1;
      v9 = v8;
      if ( v8 )
      {
        v10 = v8;
        do
        {
          v11 = *(char **)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8);
          bOwned = *v11;
          *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8) = v11 + 1;
          v12 = ++*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64];
          if ( *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] >= 32 )
          {
            *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] = 31;
          }
          else
          {
            v13 = v22;
            *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8 * v12 + 68] = nInitSize;
            *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8 * *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] + 72] = v13;
          }
          --v10;
        }
        while ( v10 );
      }
      v22 = v9;
      v14 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] + 1;
      HIWORD(nInitSize) = 4;
      v15 = *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] + 1 < 32;
      LOBYTE(nInitSize) = 1;
      ++*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64];
      if ( !v15 )
      {
LABEL_16:
        *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] = 31;
        continue;
      }
      *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8 * v14 + 68] = nInitSize;
      *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8 * *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] + 72] = v9;
    }
    else
    {
      if ( (v20 & (unsigned __int16)(1 << i)) != 0 )
      {
      }
      else
      v16 = ++*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64];
      if ( *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] >= 32 )
        goto LABEL_16;
      v17 = v22;
      *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8 * v16 + 68] = nInitSize;
      *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[8 * *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] + 72] = v17;
    }
  }
  return (*(int (**)(void))&((GRPinput *)&stru_D8C2B8)->m_keyRaw[v4 + 56])();
}

// 0x00434C00
char * PalScript::GetString()
{
  char *result; // eax

  if ( *(int *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] < 0 )
  {
    result = 0;
  }
  else
  {
    --*(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64];
    result = (char *)(8 * *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[64] + 14205804);
  }
  if ( result )
  {
    if ( *result == 5 )
      return ((PtrArray *)*((_WORD *)result + 2))->SetAtGrow(0);
  }
  return result;
}

// 0x00434CE0
void PalScript::Op_Idle()
{
  char *String; // esi
  float *v2; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    v2 = (float *)operator new(0x10u);
    if ( v2 )
    {
      v2[2] = *((float *)g_ScriptSystemData.m_String + 1);
      v2[3] = 0.0;
      *((_DWORD *)v2 + 1) = 1;
      ((PalScriptMgr *)v2)->NotifyEvent();
    }
  }
}

// 0x00434D50
void * PalScript::Destroy_28(char a2)
{
  Array::_nearby_411ba0();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00434D70
void PalScript::Op_ScriptRunMode()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    *(_BYTE *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 4) = g_ScriptSystemData.m_String[4];
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v6 = v5;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      if ( v5 )
      {
        SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
        v8 = SceneObject;
        if ( SceneObject )
        {
          if ( SceneObject == &g_RoleSystemMain )
          {
            if ( *(_DWORD *)&((RoleSystem *)&stru_C08160)->m_partyActor.m_szTexture[4] )
            {
              *(_DWORD *)SceneObject->m_partyActor.m_szTexture = *(_DWORD *)((RoleSystem *)&stru_C08160)->m_partyActor.m_szTexture;
            }
            else if ( *(_DWORD *)SceneObject->m_partyActor.m_szTexture >= *(_DWORD *)(UISceneUpdate() + 492772) )
            {
              *(_DWORD *)v8->m_partyActor.m_szTexture = 0;
            }
          }
          if ( *((_DWORD *)g_ScriptSystemData.m_String + 1) < 5u && ((RoleSystem *)v8)->IsPathMoving() )
            ((RoleSystem *)v8)->AllocPathPage(*((_DWORD *)v3 + 1), *((_DWORD *)v6 + 1));
          else
            ((RoleSystem *)v8)->CalcTileDistance(*((_DWORD *)v3 + 1), *((_DWORD *)v6 + 1));
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

  g_ScriptSystemData.m_String = this->GetString();
  result = this->GetString();
  v4 = result;
  if ( g_ScriptSystemData.m_String && result )
  {
    result = (char *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
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

  g_ScriptSystemData.m_String = this->GetString();
  result = this->GetString();
  v4 = result;
  if ( g_ScriptSystemData.m_String && result )
  {
    result = (char *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( result )
      return (char *)((RoleSystem *)result)->ResetPathParams(*((_DWORD *)v4 + 1));
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  v8 = v7;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      if ( v5 )
      {
        if ( v7 )
        {
          SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
          if ( SceneObject )
          {
            if ( *((_DWORD *)v8 + 1) == 1 )
              ((RoleSystem *)SceneObject)->MoveToTileCheck(*((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1), 2);
            else
              ((RoleSystem *)SceneObject)->MoveToTileCheck(*((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1), 1);
            SceneObject->_embed_UIWnd_624.m_rect.bottom = 0;
            SceneObject->m_FrameA.m_pfather = (UIWnd *)1;
            ((PalScriptMgr *)&SceneObject->m_bvisible)->NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  v8 = v7;
  if ( g_ScriptSystemData.m_String && v3 && v5 && v7 )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
    {
      v10 = ConvertDirection(*((_DWORD *)v8 + 1));
      ((RoleSystem *)SceneObject)->MoveToTileCheck(*((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1), v10);
      SceneObject->_embed_UIWnd_624.m_rect.bottom = 0;
      ((PalScriptMgr *)&SceneObject->m_bvisible)->NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  v8 = v7;
  if ( g_ScriptSystemData.m_String && v3 && v5 && v7 )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
    {
      v10 = ConvertDirection(*((_DWORD *)v8 + 1));
      HIDWORD(v11) = *((_DWORD *)v5 + 1);
      LODWORD(v11) = *((_DWORD *)v3 + 1);
      ((RoleSystem *)SceneObject)->MoveToTile(v11, v10);
      ((PalScriptMgr *)&SceneObject->m_bvisible)->NotifyEvent();
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
  RoleSystem *v8; // edi
  int v9; // esi

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v6 = v5;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      if ( v5 )
      {
        SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
        v8 = SceneObject;
        if ( SceneObject )
        {
          v9 = *((_DWORD *)v6 + 1);
          if ( v9 )
          {
            ((RoleSystem *)SceneObject)->PlayAction(*((char **)v3 + 1), *((_DWORD *)v6 + 1));
            if ( v9 > 0 || v9 == -2 )
              ((PalScriptMgr *)&v8->m_bvisible)->NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  result = this->GetString();
  v4 = result;
  if ( g_ScriptSystemData.m_String && result )
  {
    result = (char *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
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
  RoleSystem *v3; // esi

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    v3 = SceneObject;
    if ( SceneObject )
    {
      ((RoleSystem *)SceneObject)->StopAndResetPath();
      ((PalScriptMgr *)&v3->m_bvisible)->NotifyEvent();
    }
  }
}

// 0x00435170
void PalScript::Op_GetDislike()
{
  char *String; // eax
  RoleSystem *SceneObject; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
      ((RoleSystem *)SceneObject)->Notify();
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
  char *v11; // [esp+0x8] [ebp-0x108]
  unsigned __int16 v12; // [esp+0xC] [ebp-0x104]
  char Buffer[256]; // [esp+0x10] [ebp-0x100] BYREF

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    v4 = 0;
    v11 = byte_1010101;
    v5 = (unsigned __int8 *)&::Buffer.m_fMoveTargetX + 2;
    v12 = (unsigned __int16)byte_1010101;
    do
    {
      if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v4) )
        *(&v10 + *v5) = 0;
      v5 += 1408;
      ++v4;
    }
    while ( (int)v5 < (int)((unsigned __int8 *)&((RoleSystem *)&stru_C059A0)->m_StaticSlotArray.m_bfocus + 2) );
    v6 = 0;
    while ( !*((_BYTE *)&v11 + v6)
         || !*((_DWORD *)v3 + 1)
         || *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + *((_DWORD *)g_ScriptSystemData.m_String + 1)) )
    {
      if ( ++v6 >= 6 )
        goto LABEL_14;
    }
    *((_BYTE *)&::Buffer.m_fMoveTargetX + 1408 * *((_DWORD *)g_ScriptSystemData.m_String + 1) + 2) = v6 + 1;
LABEL_14:
    *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + *((_DWORD *)g_ScriptSystemData.m_String + 1)) = *((_DWORD *)v3 + 1) != 0;
    v7 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v7) )
    {
      v9 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName((char *)(&off_56ABA4)[v7]);
      v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("AddTeam");
    }
    else
    {
      v9 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName((char *)(&off_56ABA4)[v7]);
      v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("RemoveTeam");
    }
    _snprintf(Buffer, 0xFFu, v8, v9);
    ((InputSystem *)Buffer)->ProcessFrame();
  }
}

// 0x004352D0
char * PalScript::Op_RoleScriptInitCam()
{
  char *String; // esi

  char *v3; // edi

  char *result; // eax
  float pParams[3]; // [esp+0x8] [ebp-0xC] BYREF

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  result = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    if ( result )
    {
      pParams[0] = *((float *)g_ScriptSystemData.m_String + 1);
      pParams[1] = *((float *)v3 + 1);
      pParams[2] = *((float *)result + 1);
      return (char *)((CameraCtrl *)&g_pCameraCtrl)->InitParams(pParams);
    }
  }
  return result;
}

// 0x00435320
void PalScript::Op_RoleActiveShort()
{
  char *String; // eax
  void *SceneObject; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    SceneObject = GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    ((_Console *)g_pCameraCtrl)->SetActive((int)SceneObject);
  }
}

// 0x004353A0
void PalScript::Op_InTeam()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    if ( v5 )
    {
      ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->SetupFollow((int)g_pCameraCtrl, *((_DWORD *)g_ScriptSystemData.m_String + 1), *((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1));
      ((PalScriptMgr *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    if ( v7 )
    {
      *(float *)&nVal3 = *((float *)v3 + 1) * 0.017453292;
      *(float *)&nVal2 = *((float *)g_ScriptSystemData.m_String + 1) * 0.017453292;
      ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->SetupOrbit((int)g_pCameraCtrl, nVal2, nVal3, *((_DWORD *)v5 + 1), *((_DWORD *)v7 + 1));
      ((PalScriptMgr *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    if ( v7 )
    {
      *(float *)&nVal3 = *((float *)v3 + 1) * 0.017453292;
      *(float *)&nVal2 = *((float *)g_ScriptSystemData.m_String + 1) * 0.017453292;
      ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->SetupTrack((int)g_pCameraCtrl, nVal2, nVal3, *((_DWORD *)v5 + 1), *((_DWORD *)v7 + 1));
      ((PalScriptMgr *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  v9 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    if ( v7 )
    {
      v10 = *((_DWORD *)v9 + 1);
      v11 = *((_DWORD *)v7 + 1);
      p_DWORD[0] = *((int *)g_ScriptSystemData.m_String + 1);
      p_DWORD[1] = *((int *)v3 + 1);
      p_DWORD[2] = *((int *)v5 + 1);
      ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->SetupLerp((int)g_pCameraCtrl, p_DWORD, v11, v10);
      ((PalScriptMgr *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  v13 = this->GetString();
  v10 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 && v7 && v13 )
  {
    if ( v10 )
    {
      *(float *)&nStart = *((float *)v3 + 1) * 0.017453292;
      *(float *)&nMode = *((float *)g_ScriptSystemData.m_String + 1) * 0.017453292;
      ((InputSystem *)g_pCameraCtrl)->SetCameraTransition(nMode, nStart, *((_DWORD *)v5 + 1), *((_DWORD *)v7 + 1), *((_DWORD *)v13 + 1), *((_DWORD *)v10 + 1), 1);
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  v16 = this->GetString();
  v17 = this->GetString();
  v11 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 && v7 && v16 && v17 )
  {
    if ( v11 )
    {
      p_DWORD[0] = *((int *)v7 + 1);
      v12 = *((_DWORD *)v11 + 1);
      v13 = *((_DWORD *)v5 + 1);
      p_DWORD[1] = *((int *)v16 + 1);
      p_DWORD[2] = *((int *)v17 + 1);
      *(float *)&nVal3 = *((float *)v3 + 1) * 0.017453292;
      *(float *)&nVal2 = *((float *)g_ScriptSystemData.m_String + 1) * 0.017453292;
      ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->SmoothTransition((int)g_pCameraCtrl, nVal2, nVal3, v13, p_DWORD, v12);
      ((PalScriptMgr *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->NotifyEvent();
    }
  }
}

// 0x004356C0
void PalScript::Op_ShowActAutoStand()
{
  char *String; // esi

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    UISceneUpdate();
    ((_Console *)g_pCameraCtrl)->SetActive((int)g_pRoleSystem);
    old_sbh_page_manage((__old_sbh_page_struct *)g_pCameraCtrl, *((_DWORD *)g_ScriptSystemData.m_String + 1));
    *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) = 1;
  }
}

// 0x00435710
void PalScript::Op_RoleMoveBack()
{
  ((RoleSystem *)g_pCameraCtrl)->AddCameraKeyframe();
}

// 0x00435720
void PalScript::Op_RoleFaceRole()
{
  ((RoleCamera *)g_pCameraCtrl)->PushState();
}

// 0x00435730
void PalScript::Op_RoleTurnFaceA()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    if ( v5 )
      *((_DWORD *)g_ScriptSystemData.m_String + 1) = ((ScriptSystem *)*((_WORD *)v3 + 2))->GetScriptContext(*((_DWORD *)v5 + 1));
  }
}

// 0x00435770
void PalScript::Op_TeamOpenA()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    if ( v5 )
      ((ScriptSystem *)*((_WORD *)g_ScriptSystemData.m_String + 2))->PassThrough(*((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1));
  }
}

// 0x004357B0
void PalScript::Op_CameraPushState()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      ((ScriptSystem *)*((_WORD *)g_ScriptSystemData.m_String + 2))->CheckEventType(*((_DWORD *)v3 + 1));
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v6 = v5;
  if ( g_ScriptSystemData.m_String && v3 )
  {
    if ( v5 )
    {
      ScriptContext = ((ScriptSystem *)*((_WORD *)g_ScriptSystemData.m_String + 2))->GetScriptContext(*((_DWORD *)v3 + 1));
      ((ScriptSystem *)*((_WORD *)g_ScriptSystemData.m_String + 2))->PassThrough(*((_DWORD *)v3 + 1), ScriptContext + *((_DWORD *)v6 + 1));
    }
  }
}

// 0x00435830
void PalScript::Op_CameraFocusPoint()
{
  char *pszItemParam; // esi

  char *pszCountParam; // eax
  int pSkillData; // eax
  int nAttrIdx; // eax
  int nCurAttrVal; // ecx
  void *nMaxAttrVal; // edx
  int nItemType; // eax
  int *v9; // ecx
  char *pszEventName; // eax
  ScreenEffectMgr *pScrEffMgr; // ecx
  ScreenEffect *pScrEffect; // eax
  CScreenMode *pScrMode; // eax
  unsigned int nNextEventID; // [esp-0x4] [ebp-0x124]
  int *v15; // [esp+0x0] [ebp-0x120]
  int *v16; // [esp+0x0] [ebp-0x120]
  int *v17; // [esp+0x0] [ebp-0x120]
  int *v18; // [esp+0x0] [ebp-0x120]
  int *v19; // [esp+0x0] [ebp-0x120]
  int *v20; // [esp+0x0] [ebp-0x120]
  int nSkillGDB_ID; // [esp+0x8] [ebp-0x118] BYREF
  int nSkillCount; // [esp+0xC] [ebp-0x114]
  int pSkillResult; // [esp+0x10] [ebp-0x110]
  int nItemGDB_ID; // [esp+0x14] [ebp-0x10C] BYREF
  unsigned int nItemCount; // [esp+0x18] [ebp-0x108]
  unsigned int pSkillDataStored; // [esp+0x1C] [ebp-0x104]
  char szEventName[256]; // [esp+0x20] [ebp-0x100] BYREF

  pszItemParam = this->GetString();
  pszCountParam = this->GetString();
  if ( pszItemParam )
  {
    if ( pszCountParam )
    {
      nItemGDB_ID = 0xFFFF;
      nItemCount = 0;
      pSkillDataStored = 0;
      nItemGDB_ID = *((_DWORD *)pszItemParam + 1);
      nItemCount = *((_DWORD *)pszCountParam + 1);
      pSkillData = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nItemGDB_ID);
      pSkillDataStored = pSkillData;
      if ( pSkillData )
      {
        if ( *(_BYTE *)(pSkillData + 612) == 11 && *(_BYTE *)(pSkillData + 614) )
        {
          if ( ::Buffer.m_partyActor.m_dwMatMsg[8] )
          {
            pSkillResult = ::Buffer.m_partyActor.m_dwMatMsg[8];
            nSkillGDB_ID = ::Buffer.m_partyActor.m_dwMatMsg[6];
            nSkillCount = 1;
            if ( *(_DWORD *)::Buffer.m_partyActor.m_dwMatMsg[8] == 6603 )
            {
              ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nItemGDB_ID, v15);
            }
            else if ( *(_DWORD *)::Buffer.m_partyActor.m_dwMatMsg[8] != 6602 || *(_DWORD *)pSkillData == 6603 )
            {
              ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nSkillGDB_ID, v15);
              ::Buffer.m_partyActor.m_dwMatMsg[6] = nItemGDB_ID;
              ::Buffer.m_partyActor.m_dwMatMsg[7] = nItemCount;
              ::Buffer.m_partyActor.m_dwMatMsg[8] = pSkillDataStored;
            }
          }
          else
          {
            ::Buffer.m_partyActor.m_dwMatMsg[6] = nItemGDB_ID;
            ::Buffer.m_partyActor.m_dwMatMsg[7] = nItemCount;
            ::Buffer.m_partyActor.m_dwMatMsg[8] = pSkillData;
          }
          ((RoleSystem *)&::Buffer)->RecalcAggregatedStats(0);
          for ( nAttrIdx = 972; nAttrIdx < 1020; nAttrIdx += 4 )
          {
// [VFTABLE] nCurAttrVal = *(int *)((char *)&::Buffer.__vftable + nAttrIdx);
            nMaxAttrVal = *(void **)((char *)&g_nSceneFlags.m_pDataStart + nAttrIdx);
            if ( nCurAttrVal < (int)nMaxAttrVal )
            {
              if ( nCurAttrVal <= 0 )
// [VFTABLE] *(vtbl_0056AE2C **)((char *)&::Buffer.__vftable + nAttrIdx) = 0;
            }
            else
            {
// [VFTABLE] *(vtbl_0056AE2C **)((char *)&::Buffer.__vftable + nAttrIdx) = nMaxAttrVal;
            }
          }
          goto LABEL_35;
        }
        nItemType = *(_DWORD *)pSkillData;
        switch ( nItemType )
        {
          case 6119:
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nItemGDB_ID, v15);
            nSkillGDB_ID = 8146;
            nSkillCount = 1;
            pSkillResult = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8146);
            v9 = &nSkillGDB_ID;
            break;
          case 6120:
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nItemGDB_ID, v15);
            nSkillGDB_ID = 8147;
            nSkillCount = 1;
            pSkillResult = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8147);
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nSkillGDB_ID, v16);
            goto LABEL_35;
          case 6122:
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nItemGDB_ID, v15);
            nSkillGDB_ID = 8149;
            nSkillCount = 1;
            pSkillResult = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8149);
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nSkillGDB_ID, v17);
            goto LABEL_35;
          case 6123:
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nItemGDB_ID, v15);
            nSkillGDB_ID = 8150;
            nSkillCount = 1;
            pSkillResult = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8150);
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nSkillGDB_ID, v18);
            nSkillGDB_ID = 6427;
            nSkillCount = 1;
            pSkillResult = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(6427);
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nSkillGDB_ID, v19);
            goto LABEL_35;
          case 6124:
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nItemGDB_ID, v15);
            nSkillGDB_ID = 8151;
            nSkillCount = 1;
            pSkillResult = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8151);
            v9 = &nSkillGDB_ID;
            break;
          case 6125:
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nItemGDB_ID, v15);
            nSkillGDB_ID = 8152;
            nSkillCount = 1;
            pSkillResult = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8152);
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&nSkillGDB_ID, v20);
            goto LABEL_35;
          default:
            v9 = &nItemGDB_ID;
            break;
        }
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)v9, v15);
LABEL_35:
        nNextEventID = pSkillDataStored + 4;
        pszEventName = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("getitem");
        _snprintf(szEventName, 0xFFu, pszEventName, nNextEventID);
        ((InputSystem *)szEventName)->ProcessFrame();
        pScrEffect = ((ScreenEffectMgr *)pScrEffMgr)->GetInstance();
        if ( !((ScreenEffectMgr *)pScrEffect)->IsFadeWhiteHolding() )
        {
          pScrMode = CScreenMode::GetInstance();
          ((CScreenMode *)pScrMode)->AudioSetPosition("wa006", 1);
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
  unsigned int *v3; // ecx
  _DWORD *v4; // edx
  _DWORD *v5; // edx
  _DWORD *v6; // edx
  _DWORD *v7; // edx
  _DWORD *v8; // edx
  int v9; // eax
  _DWORD *v10; // edx
  unsigned int *v11; // eax
  _DWORD *v12; // ecx
  _DWORD *v13; // edx
  unsigned int *v14; // eax
  _DWORD *v15; // ecx
  _DWORD *v16; // edx
  unsigned int *v17; // eax
  _DWORD *v18; // ecx
  unsigned int *v19; // eax
  _DWORD *v20; // ecx
  _DWORD *v21; // edx
  unsigned int *v22; // eax
  _DWORD *v23; // ecx
  _DWORD *v24; // edx
  unsigned int *v25; // eax
  _DWORD *v26; // ecx
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

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    p_DWORD = 0xFFFF;
    v36 = 0;
    v37 = 0;
    p_DWORD = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    v36 = 1;
    SkillNum = (_DWORD *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(p_DWORD);
    v37 = SkillNum;
    if ( SkillNum )
    {
      v3 = &::Buffer.m_partyActor.m_dwMatMsg[8];
      do
      {
        if ( *v3 && *(_DWORD *)*v3 == *SkillNum )
        {
          *(v3 - 2) = 0;
          *v3 = 0;
          *(v3 - 1) = 0;
        }
        v4 = (_DWORD *)*(v3 - 12);
        if ( v4 && *v4 == *SkillNum )
        {
          *(v3 - 14) = 0;
          *(v3 - 12) = 0;
          *(v3 - 13) = 0;
        }
        v5 = (_DWORD *)*(v3 - 15);
        if ( v5 && *v5 == *SkillNum )
        {
          *(v3 - 17) = 0;
          *(v3 - 15) = 0;
          *(v3 - 16) = 0;
        }
        v6 = (_DWORD *)*(v3 - 9);
        if ( v6 && *v6 == *SkillNum )
        {
          *(v3 - 11) = 0;
          *(v3 - 9) = 0;
          *(v3 - 10) = 0;
        }
        v7 = (_DWORD *)*(v3 - 6);
        if ( v7 && *v7 == *SkillNum )
        {
          *(v3 - 8) = 0;
          *(v3 - 6) = 0;
          *(v3 - 7) = 0;
        }
        v8 = (_DWORD *)*(v3 - 3);
        if ( v8 && *v8 == *SkillNum )
        {
          *(v3 - 5) = 0;
          *(v3 - 3) = 0;
          *(v3 - 4) = 0;
        }
        v3 += 352;
      }
      while ( (int)v3 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[207] );
      v9 = *SkillNum;
      switch ( v9 )
      {
        case 6119:
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          v32 = 8146;
          v33 = 1;
          v34 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8146);
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v32);
          v10 = (_DWORD *)v34;
          v11 = &::Buffer.m_partyActor.m_dwMatMsg[2];
          do
          {
            if ( *v11 && *(_DWORD *)*v11 == *v10 )
            {
              *(v11 - 2) = 0;
              *v11 = 0;
              *(v11 - 1) = 0;
            }
            v12 = (_DWORD *)v11[3];
            if ( v12 && *v12 == *v10 )
            {
              v11[1] = 0;
              v11[3] = 0;
              v11[2] = 0;
            }
            v11 += 352;
          }
          while ( (int)v11 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[201] );
          break;
        case 6120:
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          v32 = 8147;
          v33 = 1;
          v34 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8147);
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v32);
          v13 = (_DWORD *)v34;
          v14 = &::Buffer.m_partyActor.m_dwMatMsg[2];
          do
          {
            if ( *v14 && *(_DWORD *)*v14 == *v13 )
            {
              *(v14 - 2) = 0;
              *v14 = 0;
              *(v14 - 1) = 0;
            }
            v15 = (_DWORD *)v14[3];
            if ( v15 && *v15 == *v13 )
            {
              v14[1] = 0;
              v14[3] = 0;
              v14[2] = 0;
            }
            v14 += 352;
          }
          while ( (int)v14 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[201] );
          break;
        case 6122:
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          v32 = 8149;
          v33 = 1;
          v34 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8149);
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v32);
          v16 = (_DWORD *)v34;
          v17 = &::Buffer.m_partyActor.m_dwMatMsg[2];
          do
          {
            if ( *v17 && *(_DWORD *)*v17 == *v16 )
            {
              *(v17 - 2) = 0;
              *v17 = 0;
              *(v17 - 1) = 0;
            }
            v18 = (_DWORD *)v17[3];
            if ( v18 && *v18 == *v16 )
            {
              v17[1] = 0;
              v17[3] = 0;
              v17[2] = 0;
            }
            v17 += 352;
          }
          while ( (int)v17 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[201] );
          break;
        case 6123:
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          v32 = 8150;
          v33 = 1;
          v34 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8150);
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v32);
          v32 = 6427;
          v33 = 1;
          v34 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(6427);
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v32);
          v19 = &::Buffer.m_partyActor.m_dwMatMsg[2];
          do
          {
            if ( *v19 && *(_DWORD *)*v19 == 8150 )
            {
              *(v19 - 2) = 0;
              *v19 = 0;
              *(v19 - 1) = 0;
            }
            v20 = (_DWORD *)v19[3];
            if ( v20 && *v20 == 8150 )
            {
              v19[1] = 0;
              v19[3] = 0;
              v19[2] = 0;
            }
            v19 += 352;
          }
          while ( (int)v19 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[201] );
          break;
        case 6124:
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          v32 = 8151;
          v33 = 1;
          v34 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8151);
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v32);
          v21 = (_DWORD *)v34;
          v22 = &::Buffer.m_partyActor.m_dwMatMsg[2];
          do
          {
            if ( *v22 && *(_DWORD *)*v22 == *v21 )
            {
              *(v22 - 2) = 0;
              *v22 = 0;
              *(v22 - 1) = 0;
            }
            v23 = (_DWORD *)v22[3];
            if ( v23 && *v23 == *v21 )
            {
              v22[1] = 0;
              v22[3] = 0;
              v22[2] = 0;
            }
            v22 += 352;
          }
          while ( (int)v22 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[201] );
          break;
        case 6125:
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          v32 = 8152;
          v33 = 1;
          v34 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(8152);
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v32);
          v24 = (_DWORD *)v34;
          v25 = &::Buffer.m_partyActor.m_dwMatMsg[2];
          do
          {
            if ( *v25 && *(_DWORD *)*v25 == *v24 )
            {
              *(v25 - 2) = 0;
              *v25 = 0;
              *(v25 - 1) = 0;
            }
            v26 = (_DWORD *)v25[3];
            if ( v26 && *v26 == *v24 )
            {
              v25[1] = 0;
              v25[3] = 0;
              v25[2] = 0;
            }
            v25 += 352;
          }
          while ( (int)v25 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[201] );
          break;
        default:
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          break;
      }
      v31 = v37 + 1;
      v27 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("loseitem");
      _snprintf(Buffer, 0xFFu, v27, v31);
      ((InputSystem *)Buffer)->ProcessFrame();
      Instance = ((ScreenEffectMgr *)v28)->GetInstance();
      if ( !((ScreenEffectMgr *)Instance)->IsFadeWhiteHolding() )
      {
        v30 = CScreenMode::GetInstance();
        ((CScreenMode *)v30)->AudioSetPosition("wa007", 1);
      }
    }
  }
}

// 0x004360F0
void PalScript::Op_RoleSpaceWalk()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      ((CScreenMode *)*((_DWORD *)g_ScriptSystemData.m_String + 1))->ProcessGameMode(*((_DWORD *)v3 + 1));
  }
}

// 0x00436120
// attributes: thunk
void PalScript::Op_RoleMoveTo()
{

}

// 0x00436130
unsigned int PalScript::Op_RoleMoveBackEx()
{
  char *String; // edi

  unsigned int result; // eax
  unsigned int v4; // esi
  float fDeltaTime; // [esp+0x0] [ebp-0x14]

  g_ScriptSystemData.m_String = this->GetString();
  result = (unsigned int)this->GetString();
  v4 = result;
  if ( g_ScriptSystemData.m_String )
  {
    if ( result )
    {
      result = *(_DWORD *)(result + 4);
      if ( result < 8 )
      {
        result = (unsigned int)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
        if ( result )
        {
          fDeltaTime = (float)(45 * *(_DWORD *)(v4 + 4));
          return ((RoleSystem *)result)->UpdateMovement(fDeltaTime, 1);
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String && v3 && *((_DWORD *)v3 + 1) < 8u )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
    {
      fDeltaTime = (float)(45 * *((_DWORD *)v4 + 1));
      ((RoleSystem *)SceneObject)->UpdateMovement(fDeltaTime, 1);
    }
    if ( SceneObject == g_pRoleSystem && *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
    {
      if ( *(_BYTE *)((PalScriptMgr *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode)->_CON_State() )
      {
        v7 = *(float *)((char *)&SceneObject[1].m_partyUI3._todo_05C + 75) * -0.017453292;
        ((j_InputSystem *)LODWORD(v7))->InputSystem::ProcessKeyboard_2();
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

  g_ScriptSystemData.m_String = this->GetString();
  result = (float *)this->GetString();
  v4 = result;
  if ( g_ScriptSystemData.m_String && result )
  {
    result = (float *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( result )
      return (float *)((RoleSystem *)result)->SetPathWaypoint(v4[1]);
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String && v3 )
  {
    SceneObject = (float *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
    {
      fDeltaTime = (double)*((int *)v4 + 1) + SceneObject[2172];
      ((RoleSystem *)SceneObject)->UpdateMovement(fDeltaTime, 1);
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
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
            ((RoleSystem *)SceneObject)->IsPathComplete(&pTargetPos, 1);
          }
          else
          {
            ((RoleSystem *)SceneObject)->IsPathComplete(v6 + 1, 1);
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      *((_DWORD *)g_ScriptSystemData.m_String + 1) = *((_DWORD *)v3 + 1);
  }
}

// 0x00436380
void PalScript::Op_Let()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      *((_DWORD *)g_ScriptSystemData.m_String + 1) += *((_DWORD *)v3 + 1);
  }
}

// 0x004363B0
void PalScript::Op_AddEx()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      *((_DWORD *)g_ScriptSystemData.m_String + 1) -= *((_DWORD *)v3 + 1);
  }
}

// 0x004363E0
void PalScript::Op_GetSwitch()
{
  char *String; // esi

  char *v3; // eax
  int v4; // ecx

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    v4 = *((_DWORD *)g_ScriptSystemData.m_String + 1) - *((_DWORD *)v3 + 1);
    *((_DWORD *)g_ScriptSystemData.m_String + 1) = v4;
    if ( v4 < 0 )
      *((_DWORD *)g_ScriptSystemData.m_String + 1) = -v4;
  }
}

// 0x00436410
void PalScript::Op_Call()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      *((_DWORD *)g_ScriptSystemData.m_String + 1) = rand() % *((_DWORD *)v3 + 1);
  }
}

// 0x00436440
void PalScript::Op_LK_Ghost()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      sub_445D20(*((_DWORD *)g_ScriptSystemData.m_String + 1), *((_DWORD *)v3 + 1));
  }
}

// 0x00436470
void PalScript::Op_FavorAdd()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    nullsub_11(*((_DWORD *)g_ScriptSystemData.m_String + 1));
}

// 0x00436490
void PalScript::Op_Team()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    ((UISceneMap *)&g_UISceneMapDlg)->LoadCompass(*((const char **)g_ScriptSystemData.m_String + 1), 0);
// [VFTABLE] ((void ( *)(UISceneMap *, int))g_UISceneMapDlg.__vftable->ShowWindow)(&g_UISceneMapDlg, 1);
// [VFTABLE] ((void ( *)(UISceneMap *, _DWORD, _DWORD))g_UISceneMapDlg.__vftable->Update_2ff0)(&g_UISceneMapDlg, 0, 0);
    ((PalScriptMgr *)&g_UISceneMapDlg != 0 ? (unsigned int)&g_UISceneMapDlg.m_probe.m_fontcolor : 0)->NotifyEvent();
  }
}

// 0x004364E0
void PalScript::Op_AddRoleAtt()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  const char **v5; // eax
  double v6; // [esp-0x10] [ebp-0x18]
  char v7; // [esp+0x0] [ebp-0x8]
  char v8; // [esp+0x4] [ebp-0x4]

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String && v3 )
  {
    v5 = ((PalScriptMgr *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode)->_CON_State();
    if ( v5 )
      *(_BYTE *)v5 = 1;
    HIDWORD(v6) = *((_DWORD *)v4 + 1);
    LODWORD(v6) = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    LoadScene(v6, (char *)1, (char *)1, v7, v8);
  }
}

// 0x00436530
void PalScript::Op_AddItem()
{
  char *String; // esi

  char *v3; // eax
  CCBItemWindow *v4; // esi

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    v4 = (CCBItemWindow *)&dword_DBA830[88 * *((unsigned __int16 *)g_ScriptSystemData.m_String + 2)];
    ((CCBItemWindow *)v4)->SetItemName(*((char **)v3 + 1));
// [VFTABLE] ((void ( *)(CCBItemWindow *, int))v4->__vftable->ShowWindow)(v4, 1);
// [VFTABLE] ((void ( *)(CCBItemWindow *, _DWORD, _DWORD))v4->__vftable->Update_2ff0)(v4, 0, 0);
    if ( v4 )
      ((PalScriptMgr *)&v4->m_pBack)->NotifyEvent();
    else
      PalScriptMgr::NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((CameraCtrl *)*((_DWORD *)g_ScriptSystemData.m_String + 1))->AttachToRole();
}

// 0x00436600
void PalScript::Op_TeamClose()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // ebx
  RoleSystem *SceneObject; // edi
  unsigned int v6; // esi

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
      if ( SceneObject )
      {
        v6 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
        if ( v6 >= 5 )
          goto LABEL_9;
        if ( *((_DWORD *)v4 + 1) )
        {
          ((RoleSystem *)v6)->ForceStopRole();
          return;
        }
        if ( ((RoleSystem *)SceneObject)->IsPathMoving() )
          ((RoleSystem *)SceneObject)->StopPathMovement(*((_DWORD *)v4 + 1));
        else
LABEL_9:
          *(_DWORD *)&SceneObject->m_partyActor.m_szTexture[4] = *((_DWORD *)v4 + 1);
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String && v3 )
  {
    SceneObject = GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
      SceneObject[66] = *((_DWORD *)v4 + 1);
  }
}

// 0x00436710
void PalScript::Op_GoTo()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8) = *((_DWORD *)g_ScriptSystemData.m_String + 1)
                                                        + *(_DWORD *)(*(_DWORD *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 72);
}

// 0x00436730
void PalScript::Op_FCZero()
{
  *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) = 0;
}

// 0x00436740
void PalScript::Op_Rand()
{
  *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) = *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) == 0;
}

// 0x00436760
void PalScript::Op_FNOT()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 16) = *((_DWORD *)g_ScriptSystemData.m_String + 1);
}

// 0x00436780
void PalScript::Op_FOP()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      ((ScriptVM *)*((_DWORD *)v3 + 1) < *((_DWORD *)g_ScriptSystemData.m_String + 1))->GetObjectByID();
  }
}

// 0x004367B0
void PalScript::Op_GT()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      ((ScriptVM *)*((_DWORD *)g_ScriptSystemData.m_String + 1) < *((_DWORD *)v3 + 1))->GetObjectByID();
  }
}

// 0x004367E0
void PalScript::Op_LS()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      ((ScriptVM *)*((_DWORD *)g_ScriptSystemData.m_String + 1) == *((_DWORD *)v3 + 1))->GetObjectByID();
  }
}

// 0x00436810
void PalScript::Op_Between()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax
  int v6; // esi

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    v6 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    if ( v6 < *((_DWORD *)v3 + 1) || v6 > *((_DWORD *)v5 + 1) )
      ScriptVM::GetObjectByID();
    else
      ((ScriptVM *)1)->GetObjectByID();
  }
}

// 0x00436860
void PalScript::Op_EQ()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      ((ScriptVM *)*((_DWORD *)g_ScriptSystemData.m_String + 1) != *((_DWORD *)v3 + 1))->GetObjectByID();
  }
}

// 0x00436890
void PalScript::Op_NEQ()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      ((ScriptVM *)*((_DWORD *)g_ScriptSystemData.m_String + 1) >= *((_DWORD *)v3 + 1))->GetObjectByID();
  }
}

// 0x004368C0
void PalScript::Op_Music()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((ScriptVM *)*((unsigned __int8 *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + *((_DWORD *)g_ScriptSystemData.m_String + 1)))->GetObjectByID();
}

// 0x004368E0
void PalScript::Op_GEQ()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      ((ScriptVM *)*((_DWORD *)v3 + 1) >= *((_DWORD *)g_ScriptSystemData.m_String + 1))->GetObjectByID();
  }
}

// 0x00436910
void PalScript::Op_LEQ()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( !*(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) )
      *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 8) = *((_DWORD *)g_ScriptSystemData.m_String + 1)
                                                          + *(_DWORD *)(*(_DWORD *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode
                                                                      + 72);
  }
}

// 0x00436940
void PalScript::Op_RemoveItem()
{
  char *String; // esi

  int i; // esi
  char *v4; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    ((UIListBox *)&g_UIListBoxDlg)->ReinitScrollbar();
    for ( i = *((_DWORD *)g_ScriptSystemData.m_String + 1) - 1; i >= 0; --i )
    {
      v4 = this->GetString();
      if ( !v4 )
        break;
      ((UIListBox *)&g_UIListBoxDlg)->CalcVisibleRange(*((char **)v4 + 1), 1);
    }
// [VFTABLE] ((void ( *)(UIListBox *, int))g_UIListBoxDlg.__vftable->ShowWindow)(&g_UIListBoxDlg, 1);
    ((PalScriptMgr *)&g_UIListBoxDlg != 0 ? (unsigned int)&g_UIListBoxDlg.m_showGrayBk : 0)->NotifyEvent();
  }
}

// 0x004369A0
void PalScript::Op_AddMoney()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
// [VFTABLE] *((_DWORD *)String + 1) = g_UIListBoxDlg.m_scrollbar.__vftable;
}

// 0x004369C0
void PalScript::Op_Movie()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // ebx

  char *v7; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    if ( v7 )
      ((CCBEditor *)&g_CCBEditorInst)->UpdateItemScript(*((CHAR **)g_ScriptSystemData.m_String + 1), *((_DWORD *)v3 + 1), *((_DWORD *)v5 + 1), *((_DWORD *)v7 + 1));
  }
}

// 0x00436A10
void PalScript::Op_CEft_Pos()
{
  char *String; // esi
  PalScriptMgr *v2; // eax
  int v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    ((CGameData *)&g_gamefrm)->Load((CUtil *)3);
    dword_DBA240 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
    {
      ((PalScriptMgr *)v2)->InitVtable();
      ((PalScriptMgr *)v3)->NotifyEvent();
    }
    else
    {
      PalScriptMgr::NotifyEvent();
    }
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

  if ( this->GetString() )
  {
    ((PalScriptMgr *)v1)->Destroy();
    v3 = v2;
    v7 = ((PalScriptMgr *)((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode)->_CON_State();
    ((CScreenMode *)v4)->GetSoundList();
    if ( (unsigned __int8)sub_53D2F0(v7) )
    {
      SoundList = ((CScreenMode *)v5)->GetSoundList();
      ((PtrArray *)SoundList)->SetResolution(0, v3);
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v6 = v5;
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    memset(Buffer, 0, sizeof(Buffer));
    SceneObject = (const char *)GetSceneObject(*((_DWORD *)g_ScriptSystemData.m_String + 1));
    if ( SceneObject )
    {
      sprintf(Buffer, "role\\%s\\%s.tga", SceneObject + 174, *((const char **)v3 + 1));
      ((UIBigMap *)&g_UISceneMapDlg)->LayoutBinkVideo(Buffer, *((_DWORD *)v6 + 1));
    }
  }
}

// 0x00436B40
void PalScript::Op_TeamCloseAEx()
{
  char *String; // esi
  char *SceneObject; // ebx
  char *v3; // edx
  char *v4; // edi

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    SceneObject = (char *)GetSceneObject(2u);
    if ( *((_DWORD *)g_ScriptSystemData.m_String + 1) )
    {
      sub_536D20((Actor *)(SceneObject + 680), a106, 0);
      v3 = SceneObject + 174;
      v4 = a106;
    }
    else
    {
      sub_536D20((Actor *)(SceneObject + 680), &g_pfnUpdateFuncs[2], 0);
      v3 = SceneObject + 174;
      v4 = (char *)&g_pfnUpdateFuncs[2];
    }
    strcpy(v3, v4);
    ((RoleSystem *)SceneObject)->UpdateTransform();
  }
}

// 0x00436BD0
void PalScript::Op_GetHS_Period_type()
{
  char *String; // esi

  char *v3; // eax
  unsigned __int8 *v4; // eax
  int v5; // ecx

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      v4 = (unsigned __int8 *)*((_DWORD *)v3 + 1);
      v5 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
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
  int v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    ((DealData *)&g_PAL3_Instance.s_drvinfo.winname[68])->LoadStoreConfig(*((CHAR **)g_ScriptSystemData.m_String + 1));
    ((PAL_GDB *)&g_PAL3_Instance.s_drvinfo.winname[68])->RefreshSkillNumbers();
    ((CGameData *)&g_gamefrm)->Load((CUtil *)2);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
    {
      ((PalScriptMgr *)v2)->InitVtable();
      ((PalScriptMgr *)v3)->NotifyEvent();
    }
    else
    {
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00436C60
void PalScript::Op_FadeNormal()
{
  char *String; // esi
  PalScriptMgr *v2; // eax
  int v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    ((CGameData *)&g_gamefrm)->Load((CUtil *)7);
    dword_DBA244 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
    {
      ((PalScriptMgr *)v2)->InitVtable();
      ((PalScriptMgr *)v3)->NotifyEvent();
    }
    else
    {
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00436CB0
void PalScript::Op_HY_FLY()
{
  char *String; // esi
  int v2; // eax
  unsigned __int8 *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = ((CGameData *)&g_gamefrm)->SetMode(7);
      v3 = (unsigned __int8 *)sub_523E70(v2);
    }
    else
    {
      v3 = pCmd;
    }
    switch ( *((_DWORD *)v3 + 2) )
    {
      case 0:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 0;
        break;
      case 1:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 1;
        break;
      case 2:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 2;
        break;
      case 3:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 3;
        break;
      case 4:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 4;
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
  int v2; // eax
  unsigned __int8 *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = ((CGameData *)&g_gamefrm)->SetMode(7);
      v3 = (unsigned __int8 *)sub_523E70(v2);
    }
    else
    {
      v3 = pCmd;
    }
    switch ( *((_DWORD *)v3 + 40465) )
    {
      case 0:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 0;
        break;
      case 1:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 1;
        break;
      case 2:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 2;
        break;
      case 3:
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 3;
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
  int v2; // eax
  unsigned __int8 *v3; // eax
  int v4; // eax
  int v5; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = ((CGameData *)&g_gamefrm)->SetMode(7);
      v3 = (unsigned __int8 *)sub_523E70(v2);
    }
    else
    {
      v3 = pCmd;
    }
    v4 = *((_DWORD *)v3 + 40462);
    if ( v4 )
    {
      v5 = v4 - 1;
      if ( v5 )
      {
        if ( v5 == 1 )
          *((_DWORD *)g_ScriptSystemData.m_String + 1) = 2;
      }
      else
      {
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 1;
      }
    }
    else
    {
      *((_DWORD *)g_ScriptSystemData.m_String + 1) = 0;
    }
  }
}

// 0x00436E10
void PalScript::Op_Quake()
{
  char *String; // esi
  int v2; // eax
  unsigned __int8 *v3; // eax
  int v4; // eax
  int v5; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = ((CGameData *)&g_gamefrm)->SetMode(7);
      v3 = (unsigned __int8 *)sub_523E70(v2);
    }
    else
    {
      v3 = pCmd;
    }
    v4 = *((_DWORD *)v3 + 40463);
    if ( v4 )
    {
      v5 = v4 - 1;
      if ( v5 )
      {
        if ( v5 == 1 )
          *((_DWORD *)g_ScriptSystemData.m_String + 1) = 2;
      }
      else
      {
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 1;
      }
    }
    else
    {
      *((_DWORD *)g_ScriptSystemData.m_String + 1) = 0;
    }
  }
}

// 0x00436E70
void PalScript::Op_ShowChatRest()
{
  char *String; // esi
  int v2; // eax
  unsigned __int8 *v3; // eax
  int v4; // eax
  int v5; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( g_CCBEditorInst.m_dwTrickID[361] == 7 )
    {
      v2 = ((CGameData *)&g_gamefrm)->SetMode(7);
      v3 = (unsigned __int8 *)sub_523E70(v2);
    }
    else
    {
      v3 = pCmd;
    }
    v4 = *((_DWORD *)v3 + 40464);
    if ( v4 )
    {
      v5 = v4 - 1;
      if ( v5 )
      {
        if ( v5 == 1 )
          *((_DWORD *)g_ScriptSystemData.m_String + 1) = 2;
      }
      else
      {
        *((_DWORD *)g_ScriptSystemData.m_String + 1) = 1;
      }
    }
    else
    {
      *((_DWORD *)g_ScriptSystemData.m_String + 1) = 0;
    }
  }
}

// 0x00436ED0
void PalScript::Op_GetHS_UnHock_type()
{

  char *String; // esi
  char *v3; // eax
  int v4; // ecx

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    v3 = this->GetString();
    if ( v3 )
    {
      v4 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
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
      LODWORD(thisa) = g_nMiniGameParam;
      dword_DBA24C = (PalScriptMgr *)*((_DWORD *)v3 + 1);
      ((CGameData *)&g_gamefrm)->Load((CUtil *)0xC);
    }
  }
}

// 0x00436F40
void PalScript::Op_SetBigMapElement()
{
  char *String; // eax
  PalScriptMgr *v2; // eax
  int v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    dword_DBA254 = (PalScriptMgr *)*((_DWORD *)g_ScriptSystemData.m_String + 1);
    ((CGameData *)&g_gamefrm)->Load((CUtil *)0xB);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
    {
      ((PalScriptMgr *)v2)->InitVtable();
      ((PalScriptMgr *)v3)->NotifyEvent();
    }
    else
    {
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00436F90
void PalScript::Op_ObjectMove()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((CGameData *)&g_gamefrm)->Load(*((CUtil **)g_ScriptSystemData.m_String + 1));
}

// 0x00436FB0
void PalScript::Op_KF_Entry()
{
  char *String; // eax
  unsigned __int8 v2; // bl

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    v2 = *((_DWORD *)g_ScriptSystemData.m_String + 1) != 0;
    ((CGameData *)&g_gamefrm)->SetMode(5);
    g_bRoleFlag1 = v2;
  }
}

// 0x00436FE0
void PalScript::Op_ENCAMP_Entry()
{
  char *String; // eax
  unsigned __int8 v2; // bl

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    v2 = *((_DWORD *)g_ScriptSystemData.m_String + 1) != 0;
    ((CGameData *)&g_gamefrm)->SetMode(5);
    g_bRoleFlag2 = v2;
  }
}

// 0x00437010
void PalScript::Op_StopMusic()
{
  char *String; // eax
  char v2; // [esp-0x4] [ebp-0x4]

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    v2 = *((_DWORD *)g_ScriptSystemData.m_String + 1) != 0;
    ((CGameData *)&g_gamefrm)->SetMode(5);
    sub_4A4770(v2);
  }
}

// 0x00437040
void PalScript::Op_SKEE_Entry()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    ((ComposeUI *)&g_pComposeUI)->RefreshRecipeList(*((_DWORD *)g_ScriptSystemData.m_String + 1));
    if ( g_pComposeUI )
      ((PalScriptMgr *)&g_pComposeUI->m_CurRender)->NotifyEvent();
    else
      PalScriptMgr::NotifyEvent();
  }
}

// 0x00437080
void PalScript::Op_Deal()
{
  PalScriptMgr *v1; // eax
  int v2; // eax

  ((CGameData *)&g_gamefrm)->Load((CUtil *)8);
  v1 = (PalScriptMgr *)operator new(0xCu);
  if ( v1 )
  {
    ((PalScriptMgr *)v1)->InitVtable();
    ((PalScriptMgr *)v2)->NotifyEvent();
  }
  else
  {
    PalScriptMgr::NotifyEvent();
  }
}

// 0x004370C0
void PalScript::Op_APPR_Entry()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    *((_DWORD *)g_ScriptSystemData.m_String + 1) = (unsigned __int8)p_BYTE;
}

// 0x004370E0
void PalScript::Op_GetHSLv()
{
  PalScriptMgr *v1; // eax
  int v2; // eax

  ((CGameData *)&g_gamefrm)->Load((CUtil *)9);
  v1 = (PalScriptMgr *)operator new(0xCu);
  if ( v1 )
  {
    ((PalScriptMgr *)v1)->InitVtable();
    ((PalScriptMgr *)v2)->NotifyEvent();
  }
  else
  {
    PalScriptMgr::NotifyEvent();
  }
}

// 0x00437120
void PalScript::Op_SwitchRS()
{
  char *String; // eax
  PalScriptMgr *v2; // eax
  int v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    dword_DBA248 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    ((CGameData *)&g_gamefrm)->Load((CUtil *)0xA);
    v2 = (PalScriptMgr *)operator new(0xCu);
    if ( v2 )
    {
      ((PalScriptMgr *)v2)->InitVtable();
      ((PalScriptMgr *)v3)->NotifyEvent();
    }
    else
    {
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x00437170
void PalScript::Op_GetFavor()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((PalScriptMgr *)&stru_DBA134)->ShowTextBox(*((const char **)g_ScriptSystemData.m_String + 1));
}

// 0x00437190
void PalScript::Op_AddSkill()
{
  ScreenEffect *Instance; // eax
  int v2; // eax

  Instance = ((ScreenEffectMgr *)this)->GetInstance();
  v2 = ((ScreenEffectMgr *)Instance)->ProcessEffect();
  if ( v2 )
    ((PalScriptMgr *)v2)->NotifyEvent();
}

// 0x004371B0
void PalScript::Op_GetFavorite()
{
  ScreenEffect *Instance; // eax
  int v2; // eax

  Instance = ((ScreenEffectMgr *)this)->GetInstance();
  v2 = ((ScreenEffectMgr *)Instance)->ProcessEffect();
  if ( v2 )
    ((PalScriptMgr *)v2)->NotifyEvent();
}

// 0x004371D0
void PalScript::Op_Note()
{
  ScreenEffect *Instance; // eax
  int v2; // eax

  Instance = ((ScreenEffectMgr *)this)->GetInstance();
  v2 = ((ScreenEffectMgr *)Instance)->ProcessEffect();
  if ( v2 )
    ((PalScriptMgr *)v2)->NotifyEvent();
}

// 0x004371F0
void PalScript::Op_PlaySound()
{
  ScreenEffect *Instance; // eax
  int v2; // eax

  Instance = ((ScreenEffectMgr *)this)->GetInstance();
  v2 = ((ScreenEffectMgr *)Instance)->ProcessEffect();
  if ( v2 )
    ((PalScriptMgr *)v2)->NotifyEvent();
}

// 0x00437210
void PalScript::Op_FullRoleAtt()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // ebx
  void *SceneObject; // edi
  int *ActiveSlot; // esi

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      SceneObject = GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
      if ( SceneObject )
      {
        ActiveSlot = ((UICoverFrm *)&g_gamefrm)->FindActiveSlot();
        ((CScreenMode *)ActiveSlot)->HideUIBars((int)SceneObject, *((_DWORD *)v4 + 1));
        if ( ActiveSlot )
          ((PalScriptMgr *)(ActiveSlot + 17))->NotifyEvent();
        else
          PalScriptMgr::NotifyEvent();
      }
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
  int v9; // eax
  unsigned int pdwVal[8]; // [esp+0x1C] [ebp-0x58] BYREF
  char v11[4]; // [esp+0x3C] [ebp-0x38] BYREF
  int v12; // [esp+0x5C] [ebp-0x18]
  int v13; // [esp+0x60] [ebp-0x14]
  char v14; // [esp+0x64] [ebp-0x10]
  int v15; // [esp+0x68] [ebp-0xC]
  char v16; // [esp+0x6C] [ebp-0x8]
  char v17; // [esp+0x6E] [ebp-0x6]
  int v18; // [esp+0x70] [ebp-0x4]

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v7 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 && v7 )
  {
    v14 = 0;
    pdwVal[7] = 0x7FFFFFFF;
    strcpy(v11, &dir[32]);
    v12 = 1;
    v15 = -1;
    v13 = 0;
    v18 = 0;
    v16 = 0;
    v17 = 1;
    ((PAL3 *)*((PAL3 **)g_ScriptSystemData.m_String + 1))->UpdateSubsystems();
    LOBYTE(((PalScript *)&stru_C11720)->_todo_48) = 1;
    ((PAL3 *)pdwVal)->StartCombat(0, 0, 0);
    v8 = (PalScriptMgr *)operator new(0xCu);
    if ( v8 )
    {
      ((PalScriptMgr *)v8)->InitVtable();
      ((PalScriptMgr *)v9)->NotifyEvent();
    }
    else
    {
      PalScriptMgr::NotifyEvent();
    }
  }
}

// 0x004373A0
void PalScript::Op_FadeOut()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    dword_C1171C = *((_DWORD *)g_ScriptSystemData.m_String + 1);
}

// 0x004373C0
void PalScript::Op_FadeIn()
{
  LOBYTE(((PalScript *)&stru_C11720)->_todo_028) = 1;
}

// 0x004373D0
void PalScript::Op_DlgFace()
{
  int v1; // esi
  char *String; // eax
  PalScriptMgr *v3; // eax
  int v4; // eax
  unsigned int pdwVal[12]; // [esp+0x4] [ebp-0x30] BYREF

  v1 = 0;
  while ( 1 )
  {
    g_ScriptSystemData.m_String = this->GetString();
    pdwVal[v1 + 6] = (unsigned int)g_ScriptSystemData.m_String;
    if ( !g_ScriptSystemData.m_String )
      break;
    pdwVal[v1++] = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    if ( v1 >= 6 )
    {
      LOBYTE(((PalScript *)&stru_C11720)->_todo_48) = 1;
      ((PAL3 *)pdwVal)->StartCombat(0, 0, 1);
      v3 = (PalScriptMgr *)operator new(0xCu);
      if ( v3 )
      {
        ((PalScriptMgr *)v3)->InitVtable();
        ((PalScriptMgr *)v4)->NotifyEvent();
      }
      else
      {
        PalScriptMgr::NotifyEvent();
      }
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      SceneObject = (RoleSystem *)GetSceneObject(0xFFFFu);
      if ( SceneObject )
      {
        if ( ((RoleSystem *)SceneObject)->TryMoveToTarget(*((_DWORD *)g_ScriptSystemData.m_String + 1), *((_DWORD *)v4 + 1)) )
          ((PalScriptMgr *)&SceneObject->m_bvisible)->NotifyEvent();
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

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    ((UISceneMap *)&g_UISceneMapDlg)->LoadCompass(*((const char **)g_ScriptSystemData.m_String + 1), 1);
// [VFTABLE] ((void ( *)(UISceneMap *, int))g_UISceneMapDlg.__vftable->ShowWindow)(&g_UISceneMapDlg, 1);
    ((PalScriptMgr *)&g_UISceneMapDlg != 0 ? (unsigned int)&g_UISceneMapDlg.m_probe.m_fontcolor : 0)->NotifyEvent();
  }
}

// 0x004374E0
void PalScript::Op_DlgHead()
{
  char *String; // esi

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
// [VFTABLE] *((_DWORD *)String + 1) = todo_451730((UIWnd *)&g_UISceneMapDlg.__vftable);
}

// 0x00437500
void PalScript::Op_DlgSel()
{
  char *String; // eax
  int *v2; // eax
  int p_DWORD[3]; // [esp+0x0] [ebp-0xC] BYREF

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    p_DWORD[0] = 0xFFFF;
    p_DWORD[1] = 0;
    p_DWORD[2] = 0;
    p_DWORD[0] = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    v2 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(p_DWORD);
    ((ScriptVM *)v2 != 0)->GetObjectByID();
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String && v3 )
  {
    AddNPCToPartySlot(*((_DWORD *)g_ScriptSystemData.m_String + 1), *((_DWORD *)v3 + 1));
    RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*((_DWORD *)v4 + 1));
    if ( RoleNum )
    {
      v8 = RoleNum + 28;
      v7 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName((char *)(&off_56ABA4)[*((_DWORD *)g_ScriptSystemData.m_String + 1)]);
      v6 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("AddSkill");
      _snprintf(Buffer, 0xFFu, v6, v7, v8);
      ((InputSystem *)Buffer)->ProcessFrame();
    }
  }
}

// 0x004375E0
void PalScript::Op_CameraWag()
{
  char *String; // esi

  char *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
      *((_DWORD *)g_ScriptSystemData.m_String + 1) = g_nRoleInitLevel[*((_DWORD *)v3 + 1)];
  }
}

// 0x00437610
void PalScript::Op_CameraMove()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    *((_DWORD *)g_ScriptSystemData.m_String + 1) = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom;
}

// 0x00437630
void PalScript::Op_CameraRotate()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    AddMoney(*((_DWORD *)g_ScriptSystemData.m_String + 1));
}

// 0x00437650
void PalScript::Op_GetDlgSel()
{
  char *String; // esi

  char *v3; // eax
  int v4; // eax
  CCBStageRole *Instance; // eax
  CScreenMode *v6; // eax
  void *v7; // [esp-0x8] [ebp-0xC]
  char *v8; // [esp-0x4] [ebp-0x8]
  int v9; // [esp-0x4] [ebp-0x8]
  int v10; // [esp+0x0] [ebp-0x4]

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    v4 = *((_DWORD *)v3 + 1);
    if ( v4 == -1 )
    {
      v8 = (char *)*((_DWORD *)g_ScriptSystemData.m_String + 1);
      Instance = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)Instance)->PlaySound(v8, v10);
    }
    else
    {
      v9 = v4;
      v7 = (void *)*((_DWORD *)g_ScriptSystemData.m_String + 1);
      v6 = CScreenMode::GetInstance();
      ((CScreenMode *)v6)->PlaySoundIfEnabled(v7, v9);
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

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    v2 = 1;
    v3 = -10000;
    v4 = 1;
    v5 = &g_nRoleInitLevel[1];
    do
    {
      if ( v5 != &g_nRoleInitLevel[4] && *v5 > v3 )
      {
        v2 = v4;
        v3 = *v5;
      }
      ++v5;
      ++v4;
    }
    while ( (int)v5 <= (int)&g_nRoleInitLevel[5] );
    *((_DWORD *)g_ScriptSystemData.m_String + 1) = v2;
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

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    v2 = 10000;
    v3 = 0;
    v4 = 1;
    v5 = &g_nRoleInitLevel[1];
    do
    {
      if ( v5 != &g_nRoleInitLevel[4] && *v5 < v2 )
      {
        v3 = v4;
        v2 = *v5;
      }
      ++v5;
      ++v4;
    }
    while ( (int)v5 <= (int)&g_nRoleInitLevel[5] );
    *((_DWORD *)g_ScriptSystemData.m_String + 1) = v3;
  }
}

// 0x00437740
void PalScript::Op_RoleStop()
{
  char *String; // eax
  int v2; // eax
  int v3; // esi
  int SkillNum; // esi
  int *v5; // [esp+0x0] [ebp-0x4]

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    v2 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    if ( v2 )
    {
      if ( v2 == 1 )
      {
        SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(6602);
        if ( Buffer.m_partyActor.m_dwMatMsg[8] )
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&Buffer.m_partyActor.m_dwMatMsg[6], v5);
        Buffer.m_partyActor.m_dwMatMsg[6] = 6602;
        Buffer.m_partyActor.m_dwMatMsg[8] = SkillNum;
        Buffer.m_partyActor.m_dwMatMsg[7] = 1;
      }
    }
    else
    {
      v3 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(6603);
      if ( Buffer.m_partyActor.m_dwMatMsg[8] )
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&Buffer.m_partyActor.m_dwMatMsg[6], v5);
      Buffer.m_partyActor.m_dwMatMsg[8] = v3;
      Buffer.m_partyActor.m_dwMatMsg[6] = 6603;
      Buffer.m_partyActor.m_dwMatMsg[7] = 1;
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      LOWORD(v3) = *((_WORD *)g_ScriptSystemData.m_String + 2);
      v9 = (int)v3;
      v5 = (PalScript *)UISceneUpdate();
      ((PalScript *)v5)->SetAction(v9);
      v7 = v6;
      if ( v6 )
      {
        v8 = v4[4];
        *(_DWORD *)(v6 + 576) = 1;
        *(_BYTE *)(v6 + 173) = v8;
        if ( !v8 )
          ((PalScript *)v6)->StopSound3D();
        if ( *(_BYTE *)(v7 + 244) == 31 && !_strcmpi(*(const char **)(*(_DWORD *)(v7 + 796) + 16), "m09") )
          ((RoleSystem *)v7)->SetTileTypeVisible(2, *(_BYTE *)(v7 + 173) == 0);
        if ( *(_BYTE *)(v7 + 173) && *(_DWORD *)(v7 + 88) == 4 && !_strcmpi((const char *)(v7 + 176), a4_0) )
          ((CEffMgr *)*(CEffMgr **)(v7 + 92))->SetEffectClass(*(_DWORD *)(v7 + 212), *(_DWORD *)(v7 + 216), *(_DWORD *)(v7 + 220));
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
    g_ScriptSystemData.m_String = this->GetString();
    *i = g_ScriptSystemData.m_String;
    if ( !g_ScriptSystemData.m_String )
      break;
    if ( ++v1 >= 5 )
    {
      LOWORD(this) = *(_WORD *)(v12[0] + 4);
v4 = (PalScript *)UISceneUpdate();
      ((PalScript *)v4)->SetAction((int)v8);
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
        ((ScriptVM *)v5)->GetRolePosition(1u);
        ((ScriptVM *)v6)->ExecuteOpcode(&pData, *(_DWORD *)(v12[4] + 4), 0);
        ((ScriptVM *)v6)->GetRolePosition(0);
        ((PalScriptMgr *)v6)->ExecuteOpcode();
        if ( !((UIScene *)"m15")->ProcessInput(aA)
          && !((UIScene *)"m15")->ProcessInput(aB)
          && !((UIScene *)"m15")->ProcessInput("C")
          && !((UIScene *)"m15")->ProcessInput("D")
          && !((UIScene *)"m15")->ProcessInput("A1")
          && !((UIScene *)"m15")->ProcessInput("B1")
          && !((UIScene *)"m15")->ProcessInput("C1")
          && !((UIScene *)"m15")->ProcessInput("D1")
          && !((UIScene *)"m08")->ProcessInput(a3) )
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
  int v4; // esi
  int v5; // [esp-0x4] [ebp-0x8]

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    LOWORD(g_ScriptSystemData.m_String) = *((_WORD *)g_ScriptSystemData.m_String + 2);
    v5 = (int)g_ScriptSystemData.m_String;
    v2 = (PalScript *)UISceneUpdate();
    ((PalScript *)v2)->SetAction(v5);
    v4 = (int)v3;
    if ( v3 )
    {
      ((PalScriptMgr *)v3)->OnAnimFinish();
      ((PalScriptMgr *)v4)->NotifyEvent();
    }
  }
}

// 0x00437AC0
char * PalScript::Op_InTeamExecScript()
{
  char *result; // eax
  scAsmDecoder *v2; // ecx

  result = this->GetString();
  if ( result )
    return (char *)((scAsmDecoder *)v2)->Execute(*((_DWORD *)result + 1), 1);
  return result;
}

// 0x00437AE0
char * PalScript::Op_RoleSetLayerByObj()
{
  char *String; // esi

  char *result; // eax
  char *v4; // edi

  g_ScriptSystemData.m_String = this->GetString();
  result = this->GetString();
  v4 = result;
  if ( g_ScriptSystemData.m_String && result )
  {
    result = (char *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
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
  char *v4; // edi
  char Buffer[260]; // [esp+0x8] [ebp-0x104] BYREF

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      sprintf(Buffer, "caption\\%s.tga", *((const char **)g_ScriptSystemData.m_String + 1));
      ((PalScriptIdleObj *)&stru_DBA0D4)->LoadScriptTexture((int)Buffer, *((_DWORD *)v4 + 1));
      ((PalScriptMgr *)&stru_DBA0D4 != 0 ? (unsigned int)dword_DBA118 : 0)->NotifyEvent();
    }
  }
}

// 0x00437B90
void PalScript::Op_DlgTime()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((NPC *)*((_DWORD *)g_ScriptSystemData.m_String + 1))->SetRoleMode();
}

// 0x00437BB0
void PalScript::Op_GetTimeSel()
{
  char *String; // esi

  char *v3; // edi

  char *v5; // eax
  int p_DWORD[3]; // [esp+0x8] [ebp-0xC] BYREF

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    if ( v5 )
    {
      p_DWORD[0] = *((int *)g_ScriptSystemData.m_String + 1);
      p_DWORD[1] = *((int *)v3 + 1);
      p_DWORD[2] = *((int *)v5 + 1);
      ((RoleSystem *)&g_RoleSystemMain)->ProcessMoveCommand(p_DWORD);
      ((PalScriptMgr *)&g_RoleSystemMain != 0 ? (unsigned int)&g_RoleSystemMain.m_bvisible : 0)->NotifyEvent();
    }
  }
}

// 0x00437C20
void PalScript::Op_Get_Appr()
{
  PAL3::SnapScreen();
}

// 0x00437C30
// attributes: thunk
void PalScript::Op_Enable_Sword()
{
  ((PAL3 *)this)->StartHideFight();
}

// 0x00437C40
void PalScript::Op_Enable_JusticeBook()
{
  PalScript *v1; // eax

  v1 = (PalScript *)UISceneUpdate();
  ((PalScript *)v1)->BindRolesToStage();
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

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    v5 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->StopSoundStream(1);
      ((gbAudioManager *)v5)->StopSoundStream(2);
      ((gbAudioManager *)v5)->StopSoundStream(0);
      ((gbAudioManager *)v5)->DetachAll3D();
      v6 = CScreenMode::GetInstance();
      ((CScreenMode *)v6)->StopAll();
    }
    v7 = g_nSceneState;
    g_nSceneState = 0;
    ((PAL3 *)v4)->Render();
    g_nSceneState = v7;
    sprintf(Buffer, "movie\\%s.bik", *((const char **)g_ScriptSystemData.m_String + 1));
    OpcodeByName = FindOpcodeByName(*((char **)g_ScriptSystemData.m_String + 1));
    if ( OpcodeByName >= 0 )
      SetGameSwitch(OpcodeByName);
    ((CScreenMode *)&g_ScreenMode)->CreateDevice((int)Buffer, (int)hWnd, 0, 0);
    v12 = (600 - ((CScreenMode *)&g_ScreenMode)->GetHeight()) / 2;
    Width = ((CScreenMode *)&g_ScreenMode)->GetWidth();
    ((CScreenMode *)&g_ScreenMode)->SetViewport((800 - Width) / 2, v12);
    ((CScreenMode *)&g_ScreenMode)->PlayVideo(1);
    if ( CScreenMode::GetInstance()->m_bRenderAlt )
    {
      v10 = CScreenMode::GetInstance();
      ((CScreenMode *)v10)->AudioFadeOut();
    }
    else
    {
      v11 = CScreenMode::GetInstance();
      ((CScreenMode *)v11)->AudioStopAll();
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String && v3 )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
      ((RoleSystem *)SceneObject)->SetActorTexture(*((const char **)v4 + 1));
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    v7 = (float)*((int *)g_ScriptSystemData.m_String + 1);
    v8 = (float)*((int *)v3 + 1);
    v9 = (float)*((int *)v5 + 1);
    v6 = operator new(0x1Cu);
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
      ((PalScriptMgr *)v6)->NotifyEvent();
    }
    else
    {
      PalScriptMgr::NotifyEvent();
    }
  }
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
    this->m_waitobj = (PtrArray *)1084227584;
  }
  v3 = (1.0 - cos(*(float *)&this->m_waitobj * 0.2 * 3.1415927)) * 0.5;
  g_fPalScript_C12B28 = (1.0 - v3) * *(float *)&this->m_nState;
  g_fPalScript_C12B2C = (1.0 - v3) * *(float *)&this->m_nFrameCount;
  g_fPalScript_C12B30 = (1.0 - v3) * *(float *)&this->m_CamObj;
}

// 0x00438190
PalScript * PalScript::vfunc_0(char a2)
{
  ((PalScript *)Block)->ClearFloatParams();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    v7 = (float)*((int *)g_ScriptSystemData.m_String + 1);
    v8 = (float)*((int *)v3 + 1);
    v9 = (float)*((int *)v5 + 1);
    v6 = operator new(0x1Cu);
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
      ((PalScriptMgr *)v6)->NotifyEvent();
    }
    else
    {
      PalScriptMgr::NotifyEvent();
    }
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
    this->m_waitobj = (PtrArray *)1084227584;
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      ((CameraCtrl *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->SetupDirect((int *)g_pCameraCtrl, *((_DWORD *)g_ScriptSystemData.m_String + 1), *((_DWORD *)v3 + 1));
      ((PalScriptMgr *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[153])->NotifyEvent();
    }
  }
}

// 0x00438350
void PalScript::Op_GetHS_ManageType()
{
  char *String; // eax
  PalScript *v2; // eax
  PalScriptMgr *v3; // eax
  int v4; // [esp-0x4] [ebp-0x4]

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    LOWORD(g_ScriptSystemData.m_String) = *((_WORD *)g_ScriptSystemData.m_String + 2);
    v4 = (int)g_ScriptSystemData.m_String;
    v2 = (PalScript *)UISceneUpdate();
    ((PalScript *)v2)->SetAction(v4);
    if ( v3 )
      ((PalScriptMgr *)v3)->ExecuteBlock();
  }
}

// 0x00438390
void PalScript::Op_GetHS_Accrual_type()
{
  char **v1; // esi
  int v2; // edi
  int v3; // eax
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
    *v1++ = this->GetString();
    --v2;
  }
  while ( v2 );
  v3 = UISceneUpdate();
  v4 = v11;
  v5 = (char *)v3;
  if ( _strcmpi((const char *)(v3 + 32), *(const char **)(v11 + 4)) )
  {
    v10 = *(_DWORD *)(v12 + 4);
    v9 = *(const char **)(v4 + 4);
    SaveDataManager = (Actor *)GetSaveDataManager();
    v8 = ((Actor *)SaveDataManager)->AddActionByName(v5, v9, v10);
    if ( v8 )
    {
      *(_DWORD *)(v13 + 4) = *(unsigned __int8 *)(v8 + 3);
      return;
    }
  }
  else
  {
    ((PalScript *)v5)->SetAction(*(unsigned __int16 *)(v12 + 4));
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

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    *((_DWORD *)g_ScriptSystemData.m_String + 1) = (unsigned __int8)g_szGamePath[0];
}

// 0x00438470
void PalScript::Op_EntrySkee()
{
  char *String; // esi

  char *v3; // eax
  CScreenMode *Instance; // eax
  char *v5; // [esp-0x8] [ebp-0xC]
  gbAudioManager *v6; // [esp-0x4] [ebp-0x8]

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  if ( g_ScriptSystemData.m_String && v3 )
  {
    if ( (g_dwGameFlags & 4) != 0 )
    {
      v6 = (gbAudioManager *)*((_DWORD *)v3 + 1);
      v5 = (char *)*((_DWORD *)g_ScriptSystemData.m_String + 1);
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->PlayAmbientSound(v5, v6);
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
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioStopAll();
  }
}

// 0x004384D0
void PalScript::Op_CombatNotGameOver()
{
  char *String; // eax
  void *SceneObject; // esi
  _DWORD *v3; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    SceneObject = GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
    {
      v3 = operator new(0x14u);
      if ( v3 )
      {
        v3[3] = SceneObject;
        v3[2] = 0;
        v3[1] = 1;
        *((_BYTE *)v3 + 16) = 0;
        ((PalScriptMgr *)v3)->NotifyEvent();
      }
      else
      {
        PalScriptMgr::NotifyEvent();
      }
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
    this->m_waitobj = (PtrArray *)1084227584;
  }
  fAlpha = 1.0 - (1.0 - cos(*(float *)&this->m_waitobj * 0.2 * 3.1415927)) * 0.5;
  ((RoleSystem *)LODWORD(this->m_fBlendFactor))->SetBlendMode(fAlpha);
}

// 0x004385A0
void PalScript::Op_GetCombat()
{
  char *String; // eax
  RoleSystem *SceneObject; // edi
  _DWORD *v3; // esi

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    SceneObject = (RoleSystem *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
    {
      v3 = operator new(0x14u);
      if ( v3 )
      {
        v3[3] = SceneObject;
        v3[2] = 0;
        v3[1] = 1;
        *((_BYTE *)v3 + 16) = 0;
        ((RoleSystem *)SceneObject)->SetBlendMode(0.0);
      }
      else
      {
        v3 = 0;
      }
      ((PalScriptMgr *)v3)->NotifyEvent();
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
    fAlpha = (1.0 - cos(v2 * 0.2 * 3.1415927)) * 0.5;
    ((RoleSystem *)LODWORD(this->m_fBlendFactor))->SetBlendMode(fAlpha);
  }
  else
  {
    LOBYTE(this->m_nState) = 1;
    this->m_waitobj = (PtrArray *)1084227584;
    ((RoleSystem *)LODWORD(this->m_fBlendFactor))->SetBlendMode(1.0);
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
    *v1++ = this->GetString();
    --v2;
  }
  while ( v2 );
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[149].CountMode = 2;
  v5 = *(unsigned int *)(v9[1] + 4);
  v3 = (double)v5;
  LODWORD(v5) = *(_DWORD *)(v9[2] + 4);
  v4 = *(_DWORD *)(v9[3] + 4);
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[152].HoldTime = 0;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[151].PressTime = 0;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[152].Data = 1065353216;
  *(float *)&v6 = v3 * 0.0039215689;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[149].PressTime = v6;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[150].CountMode = 1065353216;
  *(float *)&v7 = (double)v5 * 0.0039215689;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[150].Data = v7;
  *(float *)&v8 = (double)v4 * 0.0039215689;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[150].HoldTime = v8;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[152].CountMode = *(_DWORD *)(v9[0] + 4);
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[151].HoldTime = 1120403456;
}

// 0x004387B0
void PalScript::Op_RoleFadeIn()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    byte_BFDA40 = *((_DWORD *)g_ScriptSystemData.m_String + 1) != 0;
}

// 0x004387D0
void PalScript::Op_TeamOpenAStartMove()
{
  int *p_pTargetPos; // esi
  int v2; // edi
  RoleSystem *SceneObject; // eax
  double v4; // st7
  int v5; // [esp+0x8] [ebp-0x14]
  int pTargetPos; // [esp+0xC] [ebp-0x10] BYREF
  float v7; // [esp+0x10] [ebp-0xC]
  int v8; // [esp+0x14] [ebp-0x8]
  int v9; // [esp+0x18] [ebp-0x4]

  p_pTargetPos = &pTargetPos;
  v2 = 4;
  do
  {
    *p_pTargetPos++ = (int)this->GetString();
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
    ((RoleSystem *)SceneObject)->StartLinearMove(&pTargetPos, 1);
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
  char *v9; // ecx
  int v10; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String )
  {
    if ( v3 )
    {
      v5 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
      if ( v5 < 5 )
      {
        v6 = 0;
        v7 = 0;
        v8 = 0;
        v9 = &Buffer.m_partyActor.m_szTexture[4];
        do
        {
          if ( v8 != v5 && *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v8) )
          {
            v6 += *(_DWORD *)v9;
            ++v7;
          }
          v9 += 1408;
          ++v8;
        }
        while ( (int)v9 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[135] );
        if ( v7 )
        {
          v10 = *((_DWORD *)v4 + 1) + v6 / v7;
          if ( *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * v5 + 4] > v10 )
            v10 = *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * v5 + 4];
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

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    LOBYTE(((PAL3 *)v1)->GetInstance_fd20()->m_pVtable) = 0;
// [VFTABLE] LOBYTE(((PAL3 *)v3)->GetInstance()->__vftable) = 0;
    v5 = *((_DWORD *)g_ScriptSystemData.m_String + 1);
    if ( v5 )
    {
      if ( v5 == 1 )
// [VFTABLE] LOBYTE(((PAL3 *)v4)->GetInstance()->__vftable) = 1;
    }
    else
    {
      LOBYTE(((PAL3 *)v4)->GetInstance_fd20()->m_pVtable) = 1;
    }
  }
}

// 0x00438910
void PalScript::ClearIntParams()
{
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].CountMode = 0;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].PressTime = 0;
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[149].Data = 0;
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
    *v1++ = this->GetString();
    --v2;
  }
  while ( v2 );
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].CountMode = *(_DWORD *)(v3[0] + 4);
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].PressTime = *(_DWORD *)(v3[1] + 4);
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[149].Data = *(_DWORD *)(v3[2] + 4);
}

// 0x00438980
void PalScript::Op_CEft_Role()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((CEffect *)g_pSceneManager)->Render(*((_DWORD *)g_ScriptSystemData.m_String + 1));
}

// 0x004389A0
void PalScript::Op_FogH()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((CEffMgr *)g_pSceneManager)->Init(*((_DWORD *)g_ScriptSystemData.m_String + 1), ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].CountMode, ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].PressTime, ((GRPinput *)&stru_D8C2B8)->KeyInfo[149].Data, 0);
}

// 0x004389D0
void PalScript::Op_Snow()
{
  char *String; // eax
  int *SceneObject; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
  {
    SceneObject = (int *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
    {
      ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].CountMode = SceneObject[40];
      ((GRPinput *)&stru_D8C2B8)->KeyInfo[148].PressTime = SceneObject[41];
      ((GRPinput *)&stru_D8C2B8)->KeyInfo[149].Data = SceneObject[42];
      *(float *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[148].PressTime = *(float *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[148].PressTime + 2.0;
    }
  }
}

// 0x00438A20
void PalScript::Op_CEft()
{
  ((CGameData *)&g_gamefrm)->Load((CUtil *)4);
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

  g_ScriptSystemData.m_String = this->GetString();
  v2 = 0;
  if ( g_ScriptSystemData.m_String )
  {
    v10[0] = 6308;
    v10[1] = 6309;
    v10[2] = 6310;
    p_DWORD[1] = 0;
    p_DWORD[2] = 0;
    for ( i = v10; ; ++i )
    {
      p_DWORD[0] = *i;
      v4 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(p_DWORD);
      v5 = v4;
      if ( v4 )
        break;
      if ( ++v2 >= 3 )
        return;
    }
    v8 = v4[2] + 4;
    v6 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("loseitem");
    _snprintf(Buffer, 0xFFu, v6, v8);
    ((InputSystem *)Buffer)->ProcessFrame();
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition("wa007", 1);
    *((_DWORD *)g_ScriptSystemData.m_String + 1) = v2;
    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(v5);
  }
}

// 0x00438B00
void PalScript::Op_EntrySmeltSys()
{
  char *String; // esi

  char *v3; // eax
  char *v4; // edi
  Actor *SceneObject; // eax

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v4 = v3;
  if ( g_ScriptSystemData.m_String && v3 )
  {
    SceneObject = (Actor *)GetSceneObject(*((_WORD *)g_ScriptSystemData.m_String + 2));
    if ( SceneObject )
      ((Actor *)SceneObject)->GetInnerAnimDuration(*((_DWORD *)v4 + 1));
  }
}

// 0x00438B40
void PalScript::Op_Switch2Menu()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    byte_BFDA41 = *((_DWORD *)g_ScriptSystemData.m_String + 1) != 0;
}

// 0x00438B60
void PalScript::Op_CEft_Load()
{
  char *String; // eax


  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    this->InitParticleSlht(*((PalScript **)g_ScriptSystemData.m_String + 1));
}

// 0x00438B80
void PalScript::Op_GiveCloth()
{
  ((ScriptSystem *)6u)->CheckEventType(0);
  ((ScriptSystem *)6u)->CheckEventType(1);
  ((ScriptSystem *)6u)->CheckEventType(2);
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

  g_ScriptSystemData.m_String = this->GetString();
  v3 = this->GetString();
  v5 = this->GetString();
  v6 = v5;
  if ( g_ScriptSystemData.m_String && v3 && v5 )
  {
    v7 = (RoleSystem *)UISceneUpdate();
    v8 = *((_DWORD *)g_ScriptSystemData.m_String + 1) & 1;
    *((_DWORD *)g_ScriptSystemData.m_String + 1) = v8;
    RolePtr = ((RoleSystem *)v7)->GetRolePtr(v8);
    v10 = *((_DWORD *)v3 + 1);
    v11 = *((_DWORD *)v6 + 1);
    v15 = 0.0;
    v16 = ((double)v11 + 0.5) * *(float *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[262].HoldTime + *(float *)(RolePtr + 136);
    if ( v10 >= 0 )
    {
      v12 = *(_DWORD *)(RolePtr + 152);
      if ( v10 < v12 && v11 >= 0 && v11 < *(_DWORD *)(RolePtr + 156) )
        v15 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (v10 + v11 * v12));
    }
    v14 = ((double)v10 + 0.5) * *(float *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[262].HoldTime + *(float *)(RolePtr + 128);
    *(float *)pTargetPos = v14;
    *(float *)&pTargetPos[1] = v15;
    *(float *)&pTargetPos[2] = v16;
    pTarget.x = g_pRoleSystem->m_fPosX;
    pTarget.y = g_pRoleSystem->m_fPosY;
    m_fPosZ = g_pRoleSystem->m_fPosZ;
    *(_DWORD *)&g_RoleSystemExtra0.m_partyActor.m_szTexture[4] = 1;
    pTarget.z = m_fPosZ;
    ((RoleSystem *)&g_RoleSystemExtra0)->NotifySceneChange();
    ((RoleSystem *)&g_RoleSystemExtra0)->SetTargetRotation(&pTarget);
    ((RoleSystem *)&g_RoleSystemExtra0)->Notify();
    *(gbVec3D *)&g_RoleSystemExtra0.m_fPosX = pTarget;
    ((RoleSystem *)&g_RoleSystemExtra0)->StartLinearMove(pTargetPos, 1);
  }
}

// 0x00438D00
void PalScript::Op_Rain()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((j_InputSystem *)*((_DWORD *)g_ScriptSystemData.m_String + 1))->InputSystem::ProcessKeyboard_2();
}

// 0x00438D20
void PalScript::Op_WaterMagic()
{
  _DWORD *v1; // eax
  int v2; // esi
  void *v3; // eax
  int *v4; // eax
  int v5; // edx
  size_t v6; // [esp+0x0] [ebp-0x34] BYREF
  int v7; // [esp+0xC] [ebp-0x28]
  _DWORD *v8; // [esp+0x10] [ebp-0x24]
  size_t *v9; // [esp+0x14] [ebp-0x20]
  _DWORD v10[4]; // [esp+0x18] [ebp-0x1C] BYREF
  int v11; // [esp+0x30] [ebp-0x4]

  v1 = operator new(0x10u);
  v2 = (int)v1;
  v8 = v1;
  v11 = 0;
  if ( v1 )
  {
    v6 = 152;
    v1[1] = 1;
    v1[2] = 0;
    *((_BYTE *)v1 + 12) = 0;
    v3 = operator new(v6);
    v7 = (int)v3;
    LOBYTE(v11) = 2;
    if ( v3 )
      sub_4422E0(v3);
    else
      v4 = 0;
    LODWORD(g_fGameSpeed) = v4;
    v10[2] = 256;
    v10[3] = 256;
    v10[0] = 0;
    v10[1] = 0;
    v5 = *v4;
    LOBYTE(v11) = 1;
    (*(void ( **)(int *, _DWORD, _DWORD *, _DWORD))(v5 + 16))(v4, 0, v10, 0);
    ((UIStatic *)LODWORD(g_fGameSpeed))->CreateFromTemplate();
    sub_445DB0(0);
    v7 = 0xFFFFFF;
    v9 = &v6;
    v6 = 0xFFFFFF;
    ((NPC *)LODWORD(g_fGameSpeed))->NPC::UpdateAnim();
  }
  else
  {
    v2 = 0;
  }
  v11 = -1;
  ((PalScriptMgr *)v2)->NotifyEvent();
}

// 0x00438F10
void PalScript::Op_FullTeamAtt()
{
  char *String; // eax

  g_ScriptSystemData.m_String = this->GetString();
  if ( g_ScriptSystemData.m_String )
    ((InputSystem *)*((char **)g_ScriptSystemData.m_String + 1))->ProcessFrame();
}

// 0x00438F30
void PalScript::Op_BeeInsertFrame()
{
  Actor *SaveDataManager; // eax
  float v2; // [esp-0x4] [ebp-0x4]

  v2 = *((float *)this->GetString() + 1);
  SaveDataManager = (Actor *)GetSaveDataManager();
  ((Actor *)SaveDataManager)->InsertAnimFrame(v2);
}

// 0x00438F50
void PalScript::Op_CameraYaw()
{
  PalScript *v1; // eax
  int v2; // eax
  int v3; // eax
  Actor *SaveDataManager; // eax

  if ( !(_BYTE)dword_D8BC38 )
  {
    if ( ((UIScene *)pszName)->ProcessInput(pszName2) )
    {
      v1 = (PalScript *)UISceneUpdate();
      ((PalScript *)v1)->SetAction(22);
      v3 = v2 + 172;
    }
    else
    {
      SaveDataManager = (Actor *)GetSaveDataManager();
      v3 = ((Actor *)SaveDataManager)->AddActionByName(pszName, pszName2, 22);
    }
    if ( v3 )
      *(_BYTE *)(v3 + 3) = *(_BYTE *)(v3 + 3) == 0;
    LOBYTE(dword_D8BC38) = 1;
  }
}

// 0x00439130
void PalScript::PalScript_Init()
{
  ((UIProgressBar *)this)->Destroy();
  ((UIWnd *)this)->_UIWnd();
}

// 0x004391A0
void PalScript::SetReady()
{
  this->m_nFrameCount = 0;
  this->m_CamObj = 0;
  this->m_fScriptTimer = 0.0;
  this->m_nState = 0;
  this->m_fBlendFactor = 0.0;
  this->m_waitobj = (PtrArray *)1;
  this->m_pinst = (scScriptInstance *)1;
  LOBYTE(this->m_bLoadSceneScript) = 1;
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
      this->m_fBlendFactor = 0.0;
      return;
    }
LABEL_8:
    m_nState = (void ( ***)(_DWORD, int))this->m_nState;
    if ( m_nState )
    {
      (**m_nState)(m_nState, 1);
      this->m_nState = 0;
    }
    goto LABEL_10;
  }
  v2 = (void *)this->m_nState;
  if ( v2 )
  {
    ((NPC *)this->m_nState)->FreeBuffer();
    operator delete(v2);
    this->m_nState = 0;
    this->m_fBlendFactor = 0.0;
    return;
  }
LABEL_10:
  this->m_fBlendFactor = 0.0;
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

  *(_DWORD *)Destination = 0;
  strncpy(Destination, &szFilename[strlen(szFilename) - 3], 3u);
  v12 = 0;
  if ( !_strcmpi(Destination, (const char *)&off_596424) )
  {
    LODWORD(this->m_fBlendFactor) = 1;
    v4 = (gbGeomNode *)operator new(0x118u);
    LOBYTE(v12) = 1;
LABEL_3:
    if ( v4 )
    {
      v5 = v4;
    }
    else
    {
      v5 = 0;
    }
    LOBYTE(v12) = 0;
    this->m_nState = (int)v5;
    ((gbGeomNode *)v5)->LoadFromFile(szFilename, 0, 0);
    goto LABEL_13;
  }
  if ( !_strcmpi(Destination, (const char *)&off_596420) )
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
    ((Actor *)v7)->FastInit();
  else
    v8 = 0;
  LOBYTE(v12) = 0;
  this->m_nState = (int)v8;
  sub_536D20(v8, szFilename, 0);
  ((Actor *)this->m_nState)->CompareActionName(nActionIdx, 0);
LABEL_13:
  ((UICursor *)v6)->IRender();
  v12 = -1;
  return result;
}

// 0x004393A0
char PalScript::CheckAnimOver()
{
  unsigned int v2; // eax
  struct gbNodeMsgObj v4; // [esp+0xC] [ebp-0x10] BYREF

  if ( LODWORD(this->m_fBlendFactor) != 3 || !((gbVisNode *)this->m_nState)->PopMessage(v4) )
    return 0;
  while ( 1 )
  {
    if ( v4.msgid == 1 )
    {
      v2 = gbCrc32Compute("over");
      if ( v4.param[0] == v2 )
        break;
    }
    if ( !((gbVisNode *)this->m_nState)->PopMessage(v4) )
      return 0;
  }
  return 1;
}

// 0x00439FE0
void * PalScript::GetRayToScreen(void *pRay, int *pResult)
{
  float v4; // [esp+0x0] [ebp-0x2C]
  float v5; // [esp+0x4] [ebp-0x28]
  struct gbRay v6; // [esp+0x14] [ebp-0x18] BYREF

  memset(&v6, 0, sizeof(v6));
  v5 = 1.0 - ((double)pResult[1] + (double)pResult[1]) / (double)g_DrvInfo.height;
  v4 = ((double)*pResult + (double)*pResult) / (double)g_DrvInfo.width - 1.0;
  ((gbCamera *)LODWORD(this->m_fInterval))->GetRayToScreen(v4, v5, &v6);
  qmemcpy(pRay, &v6, 0x18u);
  return pRay;
}

// 0x0043A160
PalScript::PalScript()
{
  sub_445AA0();
  sub_445EA0();
  this->m_pCurrentTask = 0;
  this->_todo_048 = 0.0;
  this->m_pTaskPtr = 0;
  this->_todo_044 = 10.0;
  this->m_nWaitTimer = -1;
}

// 0x0043A270
int PalScript::RenderUI()
{
  int result; // eax
  int m_nAnimState; // eax
  gbTexture *v4; // edi
  int v5; // eax
  double v6; // st7
  double m_pCurrentTask; // st6
  gbDynVertBuf *DynVertBuf; // eax
  double m_CamObj; // st7
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
          v4 = (gbTexture *)sub_445F60(0);
          if ( v4 )
          {
            v5 = LODWORD(this->m_fScriptTimer) - this->m_nFrameCount;
            v12.color = -1;
            v12.z = 0.0;
            v12.sv = 0.0;
            v11 = (char *)this->m_CamObj - this->m_nState;
            v12.ev = (double)v5 / (double)v4->Height;
            v6 = (double)(int)v11 / (double)v4->Width;
            m_pCurrentTask = (double)(int)this->m_pCurrentTask;
            v12.su = m_pCurrentTask * v6;
            v12.eu = (m_pCurrentTask + 1.0) * v6;
            DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
            v12.sx = (float)this->m_nState;
            v12.ey = (float)this->m_nFrameCount;
            m_CamObj = (double)(int)this->m_CamObj;
            v13.nTex = 1;
            v13.pTexPt[0] = v4;
            v12.ex = m_CamObj;
            v12.sy = (float)SLODWORD(this->m_fScriptTimer);
            ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v12, 1, g_pRenderEffect_189504C, &v13);
            ((UIWnd *)this)->Render();
            return result;
          }
        }
      }
      else
      {
        v10 = sub_445F60((unsigned int)this->m_pCurrentTask);
        if ( v10 )
        {
          v14 = v10;
          v15 = 1;
          ((TextureLibDataBase *)&this->m_waitobj)->SetLibFolder((char *)&this->m_nState);
        }
      }
      ((UIWnd *)this)->Render();
    }
  }
  return result;
}

// 0x0043A3E0
BOOL PalScript::UpdateTimer(int nVal, int nVal2)
{
  char *m_pTaskPtr; // edx
  double v5; // st7
  char *m_pCurrentTask; // eax
  int m_nTimerCount; // eax
  int m_nWaitTimer; // eax

  if ( !this->m_bCreated )
    return 0;
  if ( !*(_DWORD *)&this->m_bInitialized )
    return 0;
  m_pTaskPtr = (char *)this->m_pTaskPtr;
  if ( (int)m_pTaskPtr > 0 )
  {
    if ( this->_todo_044 < 0.000049999999 )
      goto LABEL_11;
    v5 = *(float *)&nVal + this->_todo_048;
    this->_todo_048 = v5;
    if ( v5 > 1.0 / this->_todo_044 )
    {
      m_pCurrentTask = (char *)this->m_pCurrentTask;
      this->_todo_048 = 0.0;
      this->m_pCurrentTask = m_pCurrentTask + 1;
    }
    if ( (int)this->m_pCurrentTask >= (int)m_pTaskPtr )
    {
LABEL_11:
      m_nTimerCount = this->m_nTimerCount;
      this->m_pCurrentTask = 0;
      this->m_nTimerCount = m_nTimerCount + 1;
    }
    m_nWaitTimer = this->m_nWaitTimer;
    if ( m_nWaitTimer > 0 && this->m_nTimerCount >= m_nWaitTimer )
      this->m_pCurrentTask = m_pTaskPtr - 1;
    return ((UIListBox *)this)->Update(nVal, nVal2);
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
  gbRefObject *m_pTexture; // ecx
  int v5; // edi
  CHAR *v6; // eax
  gbTexture *v7; // ecx
  gbVFileSystem *result; // eax
  OpenBaseFile v9; // [esp+0x8] [ebp-0x110] BYREF
  char Buffer[256]; // [esp+0xC] [ebp-0x10C] BYREF
  int v11; // [esp+0x114] [ebp-0x4]

  v11 = 0;
  sprintf(Buffer, byte_5967B0, pszName);
  m_pTexture = (gbRefObject *)this->m_pTexture;
  if ( m_pTexture )
    ((gbRefObject *)m_pTexture)->Release();
  if ( pData )
  {
    v5 = *(_DWORD *)gfxMgr;
    v6 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(Buffer);
    this->m_pTexture = (gbTexture *)(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6);
    this->m_pTextureInfo = (_PlugInfo *)((TextureLibDataBase *)&stru_1894B78)->CreateParentData(Buffer);
  }
  else
  {
    this->m_pTexture = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(
                                      gfxMgr,
                                      Buffer);
  }
  v7 = this->m_pTexture;
  if ( v7 )
    ((gbTexture *)v7)->LoadTexture(1);
  v11 = -1;
  return result;
}

// 0x00445B90
int PalScript::Create(int id, tagRECT *pRect, int parent)
{
  LODWORD(this->m_fBlendFactor) = id;
  *(tagRECT *)&this->m_nState = *pRect;
  this->m_bEnabled = parent;
  if ( parent )
  {
    sub_445BF0(this);
    ((PalScript *)this->m_bEnabled)->OffsetRect(&this->m_nState);
  }
  this->_todo_034 = 1;
  this->m_bCreated = 1;
  *(_DWORD *)&this->m_bInitialized = 1;
  return 1;
}

// 0x00445D10
int PalScript::OnMessage(int nVal, int nMsg, int wParam)
{
  return 0;
}

// 0x00445E10
int * PalScript::OffsetRect(int *p_DWORD)
{
  int v3; // edx

  *p_DWORD += this->m_nState;
  p_DWORD[2] += this->m_nState;
  v3 = p_DWORD[3];
  p_DWORD[1] += this->m_nFrameCount;
  p_DWORD[3] = this->m_nFrameCount + v3;
  return p_DWORD;
}

// 0x00445E70
int PalScript::ShowWindow(int nFlags)
{
  int result; // eax
  int m_bLoadSceneScript; // edx

  result = this->_todo_034;
  if ( result )
  {
    result = nFlags;
    if ( this->m_bCreated != nFlags )
    {
      m_bLoadSceneScript = this->m_bLoadSceneScript;
      this->m_bCreated = nFlags;
      return (*(int ( **)(int, int, _DWORD))(m_bLoadSceneScript + 24))(1000, nFlags, 0);
    }
  }
  return result;
}

// 0x0044B8A0
LPSTR PalScript::SetDialogTemplate(CHAR *String1, CHAR *lpString2)
{
  int *p_m_DialogTemplate; // ebp
  LPSTR result; // eax
  CHAR *p_m_DialogByte; // ecx
  PalScript *v7; // [esp-0x8] [ebp-0x14]

  p_m_DialogTemplate = &this->m_DialogTemplate;
  result = (LPSTR)lstrcmpA((LPCSTR)&this->m_DialogTemplate, String1);
  if ( result )
  {
    this->m_nDialogData = 0;
    *((_BYTE *)&this->m_nDialogData + 2) = 0;
    this->m_nDialogResult = 0;
    this->m_DialogByte = 0;
    this->m_szDialog1[0] = 0;
    this->m_szDialog2[0] = 0;
    this->m_DialogSub = 0;
    this->LoadFromFile(String1);
    this->SetDirectory("sec1");
    while ( this->HasNext() )
    {
      switch ( ((DealData *)this)->CompareString("M_ID", (LPCSTR)this) )
      {
        case 0:

          this->m_nDialogData = atoi((const char *)this);
          break;
        case 1:

          lstrcpyA((LPSTR)&this->m_nDialogData + 2, (LPCSTR)this);
          break;
        case 2:

          this->m_nDialogResult = atoi((const char *)this);
          break;
        case 3:
p_m_DialogByte = &this->m_DialogByte;
          goto LABEL_11;
        case 4:

          lstrcpyA(this->m_szDialog1, (LPCSTR)this);
          break;
        case 5:

          lstrcpyA(this->m_szDialog2, (LPCSTR)this);
          break;
        case 6:
p_m_DialogByte = &this->m_DialogSub;
LABEL_11:
          lstrcpyA(p_m_DialogByte, (LPCSTR)v7);
          break;
        default:
          break;
      }
    }
    return lstrcpyA((LPSTR)p_m_DialogTemplate, String1);
  }
  return result;
}

// 0x004573A0
void PalScript::FreeScriptBuffers()
{
  ((PalScript *)&this->m_pinst)->FreeLoadBuffer();
  ((PalScript *)((char *)this + 805416))->FreeLoadBuffer();
}

// 0x00487B60
int PalScript::InitMainUIScripts()
{
  char *v2; // ecx

  if ( g_bRoleFlag1 )
  {
    v2 = (char *)this + 53324;
  }
  else
  {
    ((PalScript *)((char *)this + 53324))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    v2 = (char *)this + 53324;
  }
  sub_445E50((int)v2);
  if ( !g_bRoleFlag2 )
    ((PalScript *)((char *)this + 53668))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)this + 53668);
  ((PalScript *)((char *)this + 52292))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnMagic.tga", g_bDebugMode);
  sub_445E50((int)this + 52292);
  sub_445E50((int)this + 51948);
  sub_445E50((int)this + 52636);
  sub_445E50((int)this + 52980);
  sub_445E50((int)this + 54356);
  return sub_445E50((int)this + 54700);
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

  if ( LOBYTE(this->m_bLoadSceneScript) )
    return 0;
  ((PalScript *)&this->m_pinst)->LoadFromFile(filename);
  ((PalScript *)&this->m_pinst)->SetDirectory("sec1");
  if ( ((PalScript *)&this->m_pinst)->HasNext() )
  {
    v4 = lstrcmpA;
    do
    {
      filenamea = 0;
      for ( i = unk_5E2540; ; i += 30 )
      {
        if ( !v4(i, (LPCSTR)&off_592DA4) )
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
      this->m_nConfigIndex = v6;
      memset(&this->m_SceneCfg_data + 55 * v6, 0, 0xC0u);
      if ( v4((LPCSTR)&this->m_pinst, asc_5B1E74) )
      {
        do
        {
          ((PalScript *)&this->m_pinst)->HasNext();
          filenameb = 0;
          for ( j = unk_5E25F4; v4(j, (LPCSTR)&off_592DA4); j += 30 )
          {
            v4 = lstrcmpA;
            if ( !lstrcmpA(j, (LPCSTR)&this->m_pinst) )
            {
              switch ( (unsigned int)filenameb )
              {
                case 0u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *((_BYTE *)&this->m_SceneConfig + 220 * this->m_nConfigIndex) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 1u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *((_BYTE *)&this->m_SceneConfig + 220 * this->m_nConfigIndex + 1) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 2u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *((_BYTE *)&this->m_SceneConfig + 220 * this->m_nConfigIndex + 2) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 3u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *((_BYTE *)&this->m_SceneConfig + 220 * this->m_nConfigIndex + 3) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 4u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *((_BYTE *)&this->m_SceneCfg_flags1 + 220 * this->m_nConfigIndex) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 5u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *((_BYTE *)&this->m_SceneCfg_flags1 + 220 * this->m_nConfigIndex + 1) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 6u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *((_BYTE *)&this->m_SceneCfg_flags1 + 220 * this->m_nConfigIndex + 2) = atoi((const char *)&this->m_pinst) != 0;
                  break;
                case 7u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *(&this->m_SceneCfg_fParam0 + 55 * this->m_nConfigIndex) = atof((const char *)&this->m_pinst);
                  break;
                case 8u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *(&this->m_SceneCfg_nParam0 + 55 * this->m_nConfigIndex) = atoi((const char *)&this->m_pinst);
                  break;
                case 9u:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *(&this->m_SceneCfg_nParam1 + 55 * this->m_nConfigIndex) = atoi((const char *)&this->m_pinst);
                  break;
                case 0xAu:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  *(&this->m_SceneCfg_nParam2 + 55 * this->m_nConfigIndex) = atoi((const char *)&this->m_pinst);
                  break;
                case 0xBu:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "&") )
                  {
                    ((PalScript *)&this->m_pinst)->HasNext();
                    v8 = 0;
                    for ( k = unk_5E286C; ; k += 30 )
                    {
                      if ( !lstrcmpA(k, (LPCSTR)&off_592DA4) )
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
                          ((PalScript *)&this->m_pinst)->LoadNext();
                          this->m_fSceneCfg[55 * this->m_nConfigIndex + 13] = atof((const char *)&this->m_pinst);
                        }
                      }
                      else
                      {
                        ((PalScript *)&this->m_pinst)->LoadNext();
                        this->m_fSceneCfg[55 * this->m_nConfigIndex + 12] = atof((const char *)&this->m_pinst);
                      }
                    }
                    else
                    {
                      ((PalScript *)&this->m_pinst)->LoadNext();
                      this->m_fSceneCfg[55 * this->m_nConfigIndex + 11] = atof((const char *)&this->m_pinst);
                    }
                  }
                  break;
                case 0xCu:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "&") )
                  {
                    ((PalScript *)&this->m_pinst)->HasNext();
                    v12 = 0;
                    for ( m = unk_5E286C; ; m += 30 )
                    {
                      if ( !lstrcmpA(m, (LPCSTR)&off_592DA4) )
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
                          ((PalScript *)&this->m_pinst)->LoadNext();
                          this->m_fSceneCfg[55 * this->m_nConfigIndex + 25] = atof((const char *)&this->m_pinst);
                        }
                      }
                      else
                      {
                        ((PalScript *)&this->m_pinst)->LoadNext();
                        this->m_fSceneCfg[55 * this->m_nConfigIndex + 24] = atof((const char *)&this->m_pinst);
                      }
                    }
                    else
                    {
                      ((PalScript *)&this->m_pinst)->LoadNext();
                      this->m_fSceneCfg[55 * this->m_nConfigIndex + 23] = atof((const char *)&this->m_pinst);
                    }
                  }
                  break;
                case 0xDu:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "&") )
                  {
                    ((PalScript *)&this->m_pinst)->HasNext();
                    v16 = 0;
                    for ( n = unk_5E286C; ; n += 30 )
                    {
                      if ( !lstrcmpA(n, (LPCSTR)&off_592DA4) )
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
                          ((PalScript *)&this->m_pinst)->LoadNext();
                          this->m_fSceneCfg[55 * this->m_nConfigIndex + 37] = atof((const char *)&this->m_pinst);
                        }
                      }
                      else
                      {
                        ((PalScript *)&this->m_pinst)->LoadNext();
                        this->m_fSceneCfg[55 * this->m_nConfigIndex + 36] = atof((const char *)&this->m_pinst);
                      }
                    }
                    else
                    {
                      ((PalScript *)&this->m_pinst)->LoadNext();
                      this->m_fSceneCfg[55 * this->m_nConfigIndex + 35] = atof((const char *)&this->m_pinst);
                    }
                  }
                  break;
                case 0xEu:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "&") )
                  {
                    ((PalScript *)&this->m_pinst)->HasNext();
                    v20 = 0;
                    for ( ii = unk_5E286C; ; ii += 30 )
                    {
                      if ( !lstrcmpA(ii, (LPCSTR)&off_592DA4) )
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
                          ((PalScript *)&this->m_pinst)->LoadNext();
                          this->m_fSceneCfg[55 * this->m_nConfigIndex + 1] = atof((const char *)&this->m_pinst);
                        }
                      }
                      else
                      {
                        ((PalScript *)&this->m_pinst)->LoadNext();
                        this->m_fSceneCfg[55 * this->m_nConfigIndex] = atof((const char *)&this->m_pinst);
                      }
                    }
                    else
                    {
                      ((PalScript *)&this->m_pinst)->LoadNext();
                      *((float *)&this->m_SceneCfg_data + 55 * this->m_nConfigIndex) = atof((const char *)&this->m_pinst);
                    }
                  }
                  break;
                case 0xFu:
                  ((PalScript *)&this->m_pinst)->LoadNext();
                  this->m_fSceneCfg[55 * this->m_nConfigIndex + 47] = atof((const char *)&this->m_pinst);
                  break;
                case 0x10u:
                  while ( lstrcmpA((LPCSTR)&this->m_pinst, "*") )
                  {
                    ((PalScript *)&this->m_pinst)->HasNext();
                    v24 = 0;
                    for ( jj = unk_5E28E4; lstrcmpA(jj, (LPCSTR)&off_592DA4); jj += 30 )
                    {
                      if ( !lstrcmpA(jj, (LPCSTR)&this->m_pinst) )
                      {
                        switch ( v24 )
                        {
                          case 0:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 16] = atof((const char *)&this->m_pinst);
                            break;
                          case 1:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 15] = atof((const char *)&this->m_pinst);
                            break;
                          case 2:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 14] = atof((const char *)&this->m_pinst);
                            break;
                          case 3:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 19] = atof((const char *)&this->m_pinst);
                            break;
                          case 4:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 18] = atof((const char *)&this->m_pinst);
                            break;
                          case 5:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 17] = atof((const char *)&this->m_pinst);
                            break;
                          case 6:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 22] = atof((const char *)&this->m_pinst);
                            break;
                          case 7:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 21] = atof((const char *)&this->m_pinst);
                            break;
                          case 8:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 20] = atof((const char *)&this->m_pinst);
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
                    ((PalScript *)&this->m_pinst)->HasNext();
                    v26 = 0;
                    for ( kk = unk_5E28E4; lstrcmpA(kk, (LPCSTR)&off_592DA4); kk += 30 )
                    {
                      if ( !lstrcmpA(kk, (LPCSTR)&this->m_pinst) )
                      {
                        switch ( v26 )
                        {
                          case 0:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 28] = atof((const char *)&this->m_pinst);
                            break;
                          case 1:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 27] = atof((const char *)&this->m_pinst);
                            break;
                          case 2:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 26] = atof((const char *)&this->m_pinst);
                            break;
                          case 3:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 31] = atof((const char *)&this->m_pinst);
                            break;
                          case 4:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 30] = atof((const char *)&this->m_pinst);
                            break;
                          case 5:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 29] = atof((const char *)&this->m_pinst);
                            break;
                          case 6:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 34] = atof((const char *)&this->m_pinst);
                            break;
                          case 7:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 33] = atof((const char *)&this->m_pinst);
                            break;
                          case 8:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 32] = atof((const char *)&this->m_pinst);
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
                    ((PalScript *)&this->m_pinst)->HasNext();
                    v28 = 0;
                    for ( mm = unk_5E28E4; lstrcmpA(mm, (LPCSTR)&off_592DA4); mm += 30 )
                    {
                      if ( !lstrcmpA(mm, (LPCSTR)&this->m_pinst) )
                      {
                        switch ( v28 )
                        {
                          case 0:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 40] = atof((const char *)&this->m_pinst);
                            break;
                          case 1:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 39] = atof((const char *)&this->m_pinst);
                            break;
                          case 2:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 38] = atof((const char *)&this->m_pinst);
                            break;
                          case 3:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 43] = atof((const char *)&this->m_pinst);
                            break;
                          case 4:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 42] = atof((const char *)&this->m_pinst);
                            break;
                          case 5:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 41] = atof((const char *)&this->m_pinst);
                            break;
                          case 6:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 46] = atof((const char *)&this->m_pinst);
                            break;
                          case 7:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 45] = atof((const char *)&this->m_pinst);
                            break;
                          case 8:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 44] = atof((const char *)&this->m_pinst);
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
                    ((PalScript *)&this->m_pinst)->HasNext();
                    v30 = 0;
                    for ( nn = unk_5E28E4; lstrcmpA(nn, (LPCSTR)&off_592DA4); nn += 30 )
                    {
                      if ( !lstrcmpA(nn, (LPCSTR)&this->m_pinst) )
                      {
                        switch ( v30 )
                        {
                          case 0:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 4] = atof((const char *)&this->m_pinst);
                            break;
                          case 1:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 3] = atof((const char *)&this->m_pinst);
                            break;
                          case 2:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 2] = atof((const char *)&this->m_pinst);
                            break;
                          case 3:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 7] = atof((const char *)&this->m_pinst);
                            break;
                          case 4:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 6] = atof((const char *)&this->m_pinst);
                            break;
                          case 5:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 5] = atof((const char *)&this->m_pinst);
                            break;
                          case 6:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 10] = atof((const char *)&this->m_pinst);
                            break;
                          case 7:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 9] = atof((const char *)&this->m_pinst);
                            break;
                          case 8:
                            ((PalScript *)&this->m_pinst)->LoadNext();
                            this->m_fSceneCfg[55 * this->m_nConfigIndex + 8] = atof((const char *)&this->m_pinst);
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
        while ( lstrcmpA((LPCSTR)&this->m_pinst, asc_5B1E74) );
      }
    }
    while ( ((PalScript *)&this->m_pinst)->HasNext() );
  }
  LOBYTE(this->m_bLoadSceneScript) = 1;
  return 1;
}

// 0x00529440
int PalScript::LoadResource(char *filename)
{
  PalScript *v3; // esi
  int result; // eax
  char *v5; // edi

  v3 = (PalScript *)((char *)this + 2900);
  ((PalScript *)((char *)this + 2900))->LoadFromFile(filename);
  ((PalScript *)v3)->SetDirectory("sec1");
  result = ((PalScript *)v3)->HasNext();
  if ( result )
  {
    v5 = (char *)this + 3424;
    do
    {
      result = _strcmpi((const char *)&off_58B448, (const char *)v3);
      if ( !result )
        break;
      ((PalScript *)v3)->LoadNext();
      strncpy(v5, (const char *)v3, 0x100u);
      v5 += 256;
      result = ((PalScript *)v3)->HasNext();
    }
    while ( result );
  }
  return result;
}

// 0x0052BE40
int PalScript::LoadEncampConfig()
{
  PalScript *p_m_EncampConfig; // esi
  int result; // eax

  p_m_EncampConfig = (PalScript *)&this->m_EncampConfig;
  ((PalScript *)&this->m_EncampConfig)->LoadFromFile("SubGame\\Encampment\\Encamp.rmk");
  ((PalScript *)p_m_EncampConfig)->SetDirectory("sec1");
  for ( result = ((PalScript *)p_m_EncampConfig)->HasNext(); result; result = ((PalScript *)p_m_EncampConfig)->HasNext() )
  {
    result = _strcmpi((const char *)&off_58B448, (const char *)p_m_EncampConfig);
    if ( !result )
      break;
    ((PalScript *)p_m_EncampConfig)->LoadNext();
    strncpy((char *)&this->m_EncampSound, (const char *)p_m_EncampConfig, 0x100u);
  }
  return result;
}

// 0x00535010
int PalScript::ResetAll()
{
  this->m_bLoadSceneScript = 0;
  this->m_pinst = 0;
  this->m_waitobj = 0;
  this->m_fBlendFactor = 0.0;
  this->m_nState = 0;
  this->m_nFrameCount = 0;
  *(&this->_todo_024 + 2) = 0;
  this->_todo_024 = 0;
  *(&this->_todo_024 + 1) = 0;
  return 0;
}

// 0x00535710
gbVFileSystem * PalScript::LoadVisNode(double String2, char *pszBuf, char *pszBuf2)
{
  void ( ***v5)(_DWORD, int); // ecx
  gbVisNode *v6; // eax
  gbVisNode *v7; // edi
  gbVFileSystem *result; // eax
  char v9; // [esp+0x0] [ebp-0x434]
  int v10; // [esp+0x0] [ebp-0x434]
  int v11; // [esp+0x0] [ebp-0x434]
  char v12; // [esp+0x4] [ebp-0x430]
  OpenSceneFile v13; // [esp+0x10] [ebp-0x424] BYREF
  gbVisNode *v14; // [esp+0x14] [ebp-0x420]
  char Buffer[253]; // [esp+0x18] [ebp-0x41C] BYREF
  __int16 v16; // [esp+0x115] [ebp-0x31F]
  char v17; // [esp+0x117] [ebp-0x31D]
  char String1[260]; // [esp+0x118] [ebp-0x31C] BYREF
  char v19[524]; // [esp+0x21C] [ebp-0x218] BYREF
  int v20; // [esp+0x430] [ebp-0x4]

  LoadScene(String2, (char *)1, (char *)1, v9, v12);
  this->m_bLoadSceneScript = UISceneUpdate();
  strcpy(String1, "scene\\");
  strcat(String1, (const char *)LODWORD(String2));
  memset(Buffer, 0, sizeof(Buffer));
  v16 = 0;
  v20 = 0;
  v17 = 0;
  sprintf(Buffer, "%s\\%s.lgt", (const char *)HIDWORD(String2), (const char *)HIDWORD(String2));
  if ( ((gbVFileSystem *)g_pVFileSys)->FileExistNum(Buffer) )
  {
    v5 = (void ( ***)(_DWORD, int))*((_DWORD *)this + 804);
    if ( v5 )
    {
      (**v5)(v5, 1);
      *((_DWORD *)this + 804) = 0;
    }
    v6 = (gbVisNode *)operator new(0x58u);
    v7 = v6;
    v14 = v6;
    LOBYTE(v20) = 1;
    if ( v6 )
    {
    }
    else
      v7 = 0;
    LOBYTE(v20) = 0;
    *((_DWORD *)this + 804) = v7;
    *((_DWORD *)this + 804) = gbLoadLightFile(Buffer);
  }
  *((_BYTE *)this + 3084) = 1;
  *((_BYTE *)this + 3085) = 0;
  ctor_0x431870((int *)v19);
  LOBYTE(v20) = 2;
  ((PalScript *)v19)->LoadFromFile("datascript\\SceneName.txt");
  ((PalScript *)v19)->SetDirectory((char *)this->m_bLoadSceneScript);
  if ( !((PalScript *)v19)->FindSaveStateString((PalScript *)(this->m_bLoadSceneScript + 32), (char *)this + 3085, (char *)0x80, v10) )
    ((PalScript *)v19)->FindSaveStateString((PalScript *)&dir[12], (char *)this + 3085, (char *)0x80, v11);
  LOBYTE(v20) = 0;
  ((PalScript *)v19)->Cleanup();
  v20 = -1;
  ((OpenSceneFile *)&v13)->_OpenSceneFile();
  return result;
}

// 0x00538D60
void PalScript::DestroyInstances(double nActionID, int *p_DWORD)
{
  PtrArray *m_waitobj; // esi
  scScriptInstance *i; // edi
  int *v6; // edi
  unsigned __int8 *as_int; // esi
  unsigned __int8 *v8; // ebp
  int v9; // ecx
  PalScriptMgr *v10; // eax
  scVARIANT_data v11; // esi
  int *RoleByState; // eax
  int v13; // ecx
  void *v14; // [esp-0x8] [ebp-D0h]
  int v15; // [esp-0x4] [ebp-CCh]
  void *v16; // [esp-0x4] [ebp-CCh]
  int v17; // [esp+0x0] [ebp-C8h]
  int v18; // [esp+0x4] [ebp-C4h]
  char pActionType; // [esp+0x13] [ebp-B5h] BYREF
  int todo_028; // [esp+0x14] [ebp-B4h]
  char String2[132]; // [esp+0x18] [ebp-B0h] BYREF
  Array v22; // [esp+0x9C] [ebp-0x2C] BYREF
  char v23; // [esp+ACh] [ebp-0x1C] BYREF
  void *Block; // [esp+B0h] [ebp-0x18]
  int v25; // [esp+B4h] [ebp-0x14]
  int v26; // [esp+B8h] [ebp-0x10]
  int v27; // [esp+C4h] [ebp-0x4]

  LOBYTE(v22.m_pDataStart) = pActionType;
  memset(&v22.m_nSize, 0, 12);
  v27 = 0;
  ((Actor *)&v23)->InitAction(&pActionType);
  v27 = 1;
  qmemcpy(String2, (const void *)LODWORD(nActionID), sizeof(String2));
  m_waitobj = this->m_waitobj;
  for ( i = this->m_pinst; i != (scScriptInstance *)m_waitobj; i = (scScriptInstance *)((char *)i + 164) )
  {
    if ( ((Actor *)i)->CompareModelName(String2) )
      break;
  }
  if ( i == (scScriptInstance *)this->m_waitobj )
  {
    v6 = ((Actor *)this->_todo_028)->SelectPointer((int *)this->_todo_028, *(int **)&this->_todo_024);
    nullsub_2(v6, this->_todo_028);
    v15 = v25;
    v14 = Block;
    this->_todo_028 = (int)v6;
    v27 = -1;
    nullsub_2(v14, v15);
    operator delete(Block);
    Block = 0;
    v25 = 0;
    v26 = 0;
    ((Array *)&v22)->Free();
  }
  else
  {
    as_int = (unsigned __int8 *)i[1].reg[4].data.as_int;
    if ( as_int != *(unsigned __int8 **)&i[1].reg[5].type )
    {
      v8 = as_int + 620;
      do
      {
        if ( !((Actor *)this)->IterateAllocBuffer(*as_int) )
        {
          LOWORD(v9) = *as_int;
          ((PalScript *)LODWORD(nActionID))->SetAction(v9);
          if ( v10 )
            ((PalScriptMgr *)v10)->UpdateScriptRoles(COERCE_DOUBLE(__PAIR64__((unsigned int)v8, (unsigned int)as_int)), v17, v18);
        }
        as_int += 656;
        v8 += 656;
      }
      while ( as_int != *(unsigned __int8 **)&i[1].reg[5].type );
    }
    for ( v11.as_int = (char *)i[1].reg[6].data; v11.as_int != *(char **)&i[1].reg[7].type; v11.as_int += 2 )
    {
      RoleByState = ((SceneMgr *)LODWORD(nActionID))->FindRoleByState(*v11.as_int);
      if ( RoleByState )
        RoleByState[158] = *((unsigned __int8 *)v11.as_int + 1);
    }
    v13 = *(_DWORD *)&this->_todo_024;
    v16 = Block;
    todo_028 = this->_todo_028;
    this->_todo_028 = v13;
    operator delete(v16);
    Block = 0;
    v25 = 0;
    v26 = 0;
    operator delete((void *)v22.m_nSize);
  }
}
