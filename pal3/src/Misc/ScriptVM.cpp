#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ScriptVM.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations

gbActorMgr * GetActorMgr(void); // from annotations

// Unnamed globals (extern)
extern int dword_D8BC38;
extern GRPinput stru_D8C2B8;

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

  ((BINK *)this)->Destroy();
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
        this->m_fPathStartX = 0.0;
        this->m_fPathStartY = 0.0;
        this->m_fPathStartZ = 0.0;
        this->m_nPathParam = 0;
        this->m_fPathEndX = 0.0;
        m_pPathKeys = this->m_pPathKeys;
        this->m_fPathEndY = 0.0;
        this->m_ptr_358 = 0;
        this->m_pPathCurrent = 0;
        operator delete(m_pPathKeys);
      }
    }
  }
  GetActorMgr();
  nearby_4b6ca0(this != 0 ? (void **)&this->m_bufTail : 0);
}

// 0x0042C1A0
BOOL ScriptVM::IsRunning()
{
  return !this->m_nPathStep && !*((_BYTE *)&this->m_ptr_20 + 48);
}

// 0x0042C730
gbVFileSystem * ScriptVM::OpenSceneScript()
{
  const char *v2; // eax
  const char *v3; // edi
  gbVFileSystem *result; // eax
  OpenSceneFile v5; // [esp+0xC] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x10] [ebp-0x110] BYREF
  int v7; // [esp+0x11C] [ebp-0x4]

  v2 = (const char *)UISceneUpdate();
  sprintf(Buffer, "%s%s", "scene\\", v2);
  v7 = 0;
  v3 = a4CCvd;
  if ( !(_BYTE)dword_D8BC38 )
    v3 = a4C1Cvd;
  strcpy(Buffer, v3);
  ((GeomNode *)(&this->m_ptr_20 + 14))->InitFromFile((const gbGeomNode *)Buffer, 0);
  (*(void ( **)(_DWORD, _DWORD))(**(&this->m_ptr_20 + 15) + 24))(*((_DWORD *)&this->m_ptr_20 + 15), 0);
  ((gbVisNode *)*((gbVisNode **)&this->m_ptr_20 + 15))->SetTimeScale(0.0);
  v7 = -1;
  ((OpenSceneFile *)&v5)->_OpenSceneFile();
  return result;
}

// 0x0042C810
char ScriptVM::UpdatePauseState()
{
  char v1; // al
  int m_nPauseState; // edx
  int v3; // eax
  int v4; // ebp
  int v5; // edi
  PalScriptMgr *v6; // esi

  v1 = *((_BYTE *)&this->_todo_0A8 + 6);
  if ( v1 != -1 )
    *((_BYTE *)&this->_todo_0A8 + 6) = v1 - 1;
  m_nPauseState = this->m_nPauseState;
  LOBYTE(v3) = *((_BYTE *)&this->_todo_0A8 + 7) == 0;
  *((_BYTE *)&this->_todo_0A8 + 7) = v3;
  if ( m_nPauseState == 1 )
  {
    LOBYTE(dword_D8BC38) = (_BYTE)v3 == 0;
    v4 = 0;
    v5 = *((_DWORD *)this->m_pCmdList + 4);
    v3 = *(_DWORD *)(v5 + 220);
    if ( v3 > 0 )
    {
      v6 = (PalScriptMgr *)(v5 + 224);
      do
      {
        if ( v6->m_nCmdType == 37 )
          ((PalScriptMgr *)v6)->LoadSceneGeometry(dword_D8BC38);
        v3 = *(_DWORD *)(v5 + 220);
        ++v4;
        v6 = (PalScriptMgr *)((char *)v6 + 896);
      }
      while ( v4 < v3 );
    }
  }
  return v3;
}

// 0x0042C950
int ScriptVM::ExecuteOpcode(void *pData, unsigned __int8 nType, int nCount)
{
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int *p_m_nPathMode; // ebx
  int v9; // edx
  int v10; // eax
  int m_nPathStep; // eax
  char *m_ptr_358; // edi
  float m_fPathEndY; // ecx
  int result; // eax
  void *v15; // esi
  _DWORD *v16; // eax
  float x; // eax
  float v18; // edx
  float v19; // ecx
  int v20; // esi
  unsigned int v21; // eax
  _DWORD *v22; // eax
  float v23; // eax
  float v24; // edx
  int v25; // eax
  int v26; // edi
  gbVec3D *RoleName; // eax
  gbVec3D *v28; // edi
  float y; // edx
  float z; // ecx
  int v31; // edx
  float v32; // edx
  float v33; // ecx
  int v34; // edx
  gbVec3D v35; // [esp+0xC] [ebp-0x5C] BYREF
  int v36; // [esp+0x18] [ebp-0x50]
  _DWORD v37[19]; // [esp+0x1C] [ebp-0x4C] BYREF
  unsigned __int8 v38; // [esp+0x78] [ebp+0x10]

  GetCGEntry((char *)v37);
  v5 = *((_DWORD *)&this->m_ptr_20 + 2);
  v6 = *((_DWORD *)&this->m_ptr_20 + 3);
  v37[1] = nType;
  v7 = *((_DWORD *)&this->m_ptr_20 + 4);
  v37[3] = v5;
  v37[5] = v7;
  v37[4] = v6;
  p_m_nPathMode = &this->m_nPathMode;
  v9 = *((_DWORD *)pData + 1);
  v10 = *((_DWORD *)pData + 2);
  v37[6] = *(_DWORD *)pData;
  v37[7] = v9;
  v37[8] = v10;
  m_nPathStep = this->m_nPathStep;
  LOBYTE(v37[0]) = 1;
  v37[2] = 0;
  v37[15] = (unsigned __int8)nCount;
  v37[16] = v38;
  if ( !m_nPathStep
    || (m_ptr_358 = this->m_ptr_358, m_fPathEndY = this->m_fPathEndY, m_ptr_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v15 = operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v21 = p_m_nPathMode[8];
      if ( v21 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v26 = ((int)(v21 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_nPathMode)->GetRoleName(2 * v26);
        v28 = (gbVec3D *)((char *)RoleName + 4 * v26);
        LODWORD(v28->x) = v15;
        ((gbVec3D *)&v35)->Copy(p_m_nPathMode[3], RoleName);
        y = v35.y;
        p_m_nPathMode[1] = LODWORD(v35.x);
        z = v35.z;
        *((float *)p_m_nPathMode + 2) = y;
        v31 = v36;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v31;
        ((gbVec3D *)&v35)->Copy((int)v15, v28);
        v32 = v35.y;
        p_m_nPathMode[5] = LODWORD(v35.x);
        v33 = v35.z;
        *((float *)p_m_nPathMode + 6) = v32;
        v34 = v36;
        *((float *)p_m_nPathMode + 7) = v33;
        p_m_nPathMode[8] = v34;
      }
      else
      {
        v22 = (_DWORD *)(v21 + 4);
        p_m_nPathMode[8] = (int)v22;
        *v22 = v15;
        ((gbVec3D *)&v35)->Copy((int)v15, (gbVec3D *)p_m_nPathMode[8]);
        v23 = v35.y;
        p_m_nPathMode[5] = LODWORD(v35.x);
        v24 = v35.z;
        *((float *)p_m_nPathMode + 6) = v23;
        v25 = v36;
        *((float *)p_m_nPathMode + 7) = v24;
        p_m_nPathMode[8] = v25;
      }
    }
    else
    {
      p_m_nPathMode[10] = 2;
      v16 = operator new(8u);
      p_m_nPathMode[9] = (int)v16;
      v16[1] = v15;
      ((gbVec3D *)&v35)->Copy((int)v15 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
      x = v35.x;
      v18 = v35.z;
      v19 = v35.y;
      v20 = v36;
      p_m_nPathMode[1] = LODWORD(v35.x);
      *((float *)p_m_nPathMode + 2) = v19;
      *((float *)p_m_nPathMode + 3) = v18;
      p_m_nPathMode[4] = v20;
      *((float *)p_m_nPathMode + 5) = x;
      *((float *)p_m_nPathMode + 6) = v19;
      *((float *)p_m_nPathMode + 7) = v18;
      p_m_nPathMode[8] = v20;
    }
    m_ptr_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_ptr_358 + 76);
    if ( !m_ptr_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_ptr_358 = m_ptr_358 + 76;
  if ( m_ptr_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_ptr_358 )
    {
LABEL_16:
      result = p_m_nPathMode[11] + 1;
      p_m_nPathMode[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_ptr_358, v37, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_ptr_358 )
    qmemcpy(m_ptr_358, v37, 0x4Cu);
  ((ScriptVM *)p_m_nPathMode)->GetString();
  result = this->m_nPathStep + 1;
  this->m_nPathStep = result;
  return result;
}

// 0x0042CD90
int ScriptVM::CallFunction(unsigned __int8 nFuncID, int nArgCount)
{
  int *p_m_nPathMode; // ebx
  int m_nPathStep; // eax
  char *m_ptr_358; // edi
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

  GetCGEntry((char *)v29);
  p_m_nPathMode = &this->m_nPathMode;
  v29[15] = nFuncID;
  LOBYTE(v29[0]) = 3;
  m_nPathStep = this->m_nPathStep;
  v29[16] = nArgCount;
  if ( !m_nPathStep
    || (m_ptr_358 = this->m_ptr_358, m_fPathEndY = this->m_fPathEndY, m_ptr_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v9 = operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v15 = p_m_nPathMode[8];
      if ( v15 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v20 = ((int)(v15 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_nPathMode)->GetRoleName(2 * v20);
        v22 = (int *)(&RoleName->x + v20);
        *v22 = (int)v9;
        ((gbVec3D *)&v27)->Copy(p_m_nPathMode[3], RoleName);
        y = v27.y;
        p_m_nPathMode[1] = LODWORD(v27.x);
        z = v27.z;
        *((float *)p_m_nPathMode + 2) = y;
        v25 = v28;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v25;
        v26 = *v22 + 4028;
        p_m_nPathMode[5] = *v22;
        p_m_nPathMode[6] = v26;
        p_m_nPathMode[7] = (int)v9;
        p_m_nPathMode[8] = (int)v22;
      }
      else
      {
        v16 = (_DWORD *)(v15 + 4);
        p_m_nPathMode[8] = (int)v16;
        *v16 = v9;
        ((gbVec3D *)&v27)->Copy((int)v9, (gbVec3D *)p_m_nPathMode[8]);
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
      v10 = operator new(8u);
      p_m_nPathMode[9] = (int)v10;
      v10[1] = v9;
      ((gbVec3D *)&v27)->Copy((int)v9 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
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
    m_ptr_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_ptr_358 + 76);
    if ( !m_ptr_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_ptr_358 = m_ptr_358 + 76;
  if ( m_ptr_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_ptr_358 )
    {
LABEL_16:
      result = p_m_nPathMode[11] + 1;
      p_m_nPathMode[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_ptr_358, v29, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_ptr_358 )
    qmemcpy(m_ptr_358, v29, 0x4Cu);
  ((ScriptVM *)p_m_nPathMode)->GetString();
  result = this->m_nPathStep + 1;
  this->m_nPathStep = result;
  return result;
}

// 0x0042D4B0
int ScriptVM::SetRolePosition(unsigned __int8 pData)
{
  int *p_m_nPathMode; // ebx
  char *m_ptr_358; // edi
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

  GetCGEntry((char *)v27);
  p_m_nPathMode = &this->m_nPathMode;
  LOBYTE(v27[0]) = 8;
  v27[15] = pData;
  if ( !this->m_nPathStep
    || (m_ptr_358 = this->m_ptr_358, m_fPathEndY = this->m_fPathEndY, m_ptr_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v7 = operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v13 = p_m_nPathMode[8];
      if ( v13 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_nPathMode)->GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        ((gbVec3D *)&v25)->Copy(p_m_nPathMode[3], RoleName);
        y = v25.y;
        p_m_nPathMode[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nPathMode + 2) = y;
        v23 = v26;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v23;
        v24 = *v20 + 4028;
        p_m_nPathMode[5] = *v20;
        p_m_nPathMode[6] = v24;
        p_m_nPathMode[7] = (int)v7;
        p_m_nPathMode[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nPathMode[8] = (int)v14;
        *v14 = v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)p_m_nPathMode[8]);
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
      v8 = operator new(8u);
      p_m_nPathMode[9] = (int)v8;
      v8[1] = v7;
      ((gbVec3D *)&v25)->Copy((int)v7 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
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
    m_ptr_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_ptr_358 + 76);
    if ( !m_ptr_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_ptr_358 = m_ptr_358 + 76;
  if ( m_ptr_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_ptr_358 )
    {
LABEL_16:
      result = p_m_nPathMode[11] + 1;
      p_m_nPathMode[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_ptr_358, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_ptr_358 )
    qmemcpy(m_ptr_358, v27, 0x4Cu);
  ((ScriptVM *)p_m_nPathMode)->GetString();
  result = this->m_nPathStep + 1;
  this->m_nPathStep = result;
  return result;
}

// 0x0042D670
int ScriptVM::GetRolePosition(unsigned __int8 pData)
{
  int *p_m_nPathMode; // ebx
  char *m_ptr_358; // edi
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

  GetCGEntry((char *)v27);
  p_m_nPathMode = &this->m_nPathMode;
  LOBYTE(v27[0]) = 9;
  v27[15] = pData;
  if ( !this->m_nPathStep
    || (m_ptr_358 = this->m_ptr_358, m_fPathEndY = this->m_fPathEndY, m_ptr_358 == (char *)LODWORD(m_fPathEndY)) )
  {
    v7 = operator new(0xFBCu);
    if ( p_m_nPathMode[11] )
    {
      v13 = p_m_nPathMode[8];
      if ( v13 >= p_m_nPathMode[9] + 4 * p_m_nPathMode[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nPathMode[4]) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)p_m_nPathMode)->GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        ((gbVec3D *)&v25)->Copy(p_m_nPathMode[3], RoleName);
        y = v25.y;
        p_m_nPathMode[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nPathMode + 2) = y;
        v23 = v26;
        *((float *)p_m_nPathMode + 3) = z;
        p_m_nPathMode[4] = v23;
        v24 = *v20 + 4028;
        p_m_nPathMode[5] = *v20;
        p_m_nPathMode[6] = v24;
        p_m_nPathMode[7] = (int)v7;
        p_m_nPathMode[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nPathMode[8] = (int)v14;
        *v14 = v7;
        ((gbVec3D *)&v25)->Copy((int)v7, (gbVec3D *)p_m_nPathMode[8]);
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
      v8 = operator new(8u);
      p_m_nPathMode[9] = (int)v8;
      v8[1] = v7;
      ((gbVec3D *)&v25)->Copy((int)v7 + 1976, (gbVec3D *)(p_m_nPathMode[9] + 4));
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
    m_ptr_358 = (char *)p_m_nPathMode[7];
    p_m_nPathMode[7] = (int)(m_ptr_358 + 76);
    if ( !m_ptr_358 )
      goto LABEL_16;
    goto LABEL_15;
  }
  this->m_ptr_358 = m_ptr_358 + 76;
  if ( m_ptr_358 + 76 != (char *)LODWORD(m_fPathEndY) )
  {
    if ( !m_ptr_358 )
    {
LABEL_16:
      result = p_m_nPathMode[11] + 1;
      p_m_nPathMode[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy(m_ptr_358, v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_ptr_358 )
    qmemcpy(m_ptr_358, v27, 0x4Cu);
  ((ScriptVM *)p_m_nPathMode)->GetString();
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
  int *m_ptr_20; // eax
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
  if ( *((_DWORD *)&this->m_ptr_20 + 3) )
  {
    m_ptr_20 = this->m_ptr_20;
    if ( (unsigned int)m_ptr_20 >= *((_DWORD *)&this->m_ptr_20 + 1) + 4 * *((_DWORD *)&this->m_ptr_20 + 2) - 4 )
    {
      v13 = (((int)m_ptr_20 - this->m_bufReadPtr) >> 2) + 1;
      v25 = v13;
      v14 = 8 * v13;
      if ( (v13 & 0x10000000) != 0 )
        v14 = 0;
      v15 = (char *)operator new(v14);
      m_bufReadPtr = (int *)this->m_bufReadPtr;
      v26 = v15;
      v17 = &v15[4 * ((unsigned int)(2 * v13) >> 2)];
      v18 = this->m_ptr_20 + 1;
      v19 = v17;
      if ( m_bufReadPtr != v18 )
      {
        do
        {
          v20 = *m_bufReadPtr++;
          *(_DWORD *)v19 = v20;
          v19 += 4;
        }
        while ( m_bufReadPtr != v18 );
        v13 = v25;
      }
      operator delete(*((void **)&this->m_ptr_20 + 1));
      *((_DWORD *)&this->m_ptr_20 + 1) = v26;
      *((_DWORD *)&this->m_ptr_20 + 2) = 2 * v13;
      result = &v17[4 * v13];
      *(_DWORD *)result = v2;
      m_bufCapacity = this->m_bufCapacity;
      p_m_bufHead = &this->m_bufHead;
      p_m_bufWritePtr = &this->m_bufWritePtr;
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
      v10 = m_ptr_20 + 1;
      this->m_ptr_20 = v10;
      v11 = &this->m_bufWritePtr;
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
    *((_DWORD *)&this->m_ptr_20 + 2) = 2;
    v3 = operator new(8u);
    *((_DWORD *)&this->m_ptr_20 + 1) = v3;
    v3[1] = v2;
    v4 = v2 + 1976;
    result = (char *)(*((_DWORD *)&this->m_ptr_20 + 1) + 4);
    v6 = &this->m_bufHead;
    v7 = &this->m_bufWritePtr;
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

  v1 = *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 16);
  if ( v1 )
  {
    v2 = v1 - 1;
    if ( v2 )
    {
      result = v2 - 1;
      if ( result )
        return result;
      if ( !nObjID && !*(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) )
        goto LABEL_6;
    }
    else if ( !nObjID || !*(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) )
    {
LABEL_6:
      *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) = 0;
      return 0;
    }
    *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) = 1;
    return 1;
  }
  else
  {
    *(_DWORD *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode + 24) = nObjID;
    return nObjID;
  }
}
