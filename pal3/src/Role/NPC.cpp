#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/NPC.h"

int * AssignInt(int *pDst, int *pSrc); // from annotations
gbVec3D * __stdcall Vec3D_CopyStruct(gbVec3D *pDst, gbVec3D *pSrc, gbVec3D *pExtra); // from annotations

// Unnamed globals (extern)
void __cdecl nullsub_2(...);

// 0x0040EB90
unsigned int NPC::Create(int index)
{
  int v2; // ebp
  _BYTE *v3; // edx
  unsigned int result; // eax
  signed int v5; // ebx
  int PropertyByIndex; // edi
  int RoleNum; // eax
  int v8; // ecx
  int indexa; // [esp+0x14] [ebp+0x4]

  v2 = 0;
  v3 = &Buffer.m_partyActor.m_bDirFlag + 1408 * index + 24;
  memset(&Buffer.m_partyActor.m_bDirFlag + 1408 * index, 0, 0x18u);
  *(_DWORD *)v3 = 0;
  *((_WORD *)v3 + 2) = 0;
// [IDA_MISID]   result = ((Concurrency *)&g_pGDB)->details::VirtualProcessor::GetExecutionResourceId();
  v5 = 0;
  for ( indexa = result; v5 < indexa; ++v5 )
  {
    PropertyByIndex = ((NPC *)&g_pGDB)->GetPropertyByIndex(v5);
    RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(PropertyByIndex);
    if ( *(_BYTE *)(index + RoleNum + 572) )
    {
      if ( !*(_BYTE *)(RoleNum + 4) )
      {
        v8 = v2 + 352 * index;
        ++v2;
        *((_DWORD *)&Buffer.m_partyActor.m_bDirFlag + v8) = PropertyByIndex;
      }
    }
    result = indexa;
  }
  return result;
}

// 0x0040EC20
void * NPC::Init(int index)
{
  signed int v2; // ebx
  int PropertyByIndex; // ebp
  int RoleNum; // eax
  char v5; // cl
  int v6; // edi
  _DWORD *v7; // ecx
  int v8; // edx
  int v9; // ecx
  int i; // ecx
  char v11; // bl
  int v12; // edi
  _BYTE *v13; // esi
  void *result; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // [esp+0x10] [ebp-0x1C]
  _DWORD v18[6]; // [esp+0x14] [ebp-0x18] BYREF
  int indexa; // [esp+0x30] [ebp+0x4]

  v2 = 0;
  memset(v18, 0, sizeof(v18));
  v17 = 1408 * index;
  memset(&Buffer.m_partyActor.m_bDirFlag + 1408 * index + 32, 0, 0xC0u);
  memset(&Buffer.m_FrameA.m_rect + 88 * index, 0, 0x30u);
  memset(&Buffer.m_FrameA.m_bfocus + 352 * index, 0, 0x30u);
  memset(&Buffer.m_fMoveRadius + 352 * index, 0, 0x30u);
// [IDA_MISID]   indexa = ((Concurrency *)&g_pGDB)->details::VirtualProcessor::GetExecutionResourceId();
  if ( indexa > 0 )
  {
    do
    {
      PropertyByIndex = ((NPC *)&g_pGDB)->GetPropertyByIndex(v2);
      RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(PropertyByIndex);
      if ( *(_BYTE *)(index + RoleNum + 572) )
      {
        v5 = *(_BYTE *)(RoleNum + 4);
        if ( v5 == 1 || v5 == 2 || v5 == 3 )
        {
          v6 = 0;
          v7 = (_DWORD *)(RoleNum + 8);
          v8 = 5;
          do
          {
            if ( *v7 == 1 )
              ++v6;
            ++v7;
            --v8;
          }
          while ( v8 );
          if ( v6 <= 1 )
          {
            for ( i = 0; i < 5; ++i )
            {
              if ( *(_DWORD *)(RoleNum + 4 * i + 8) == 1 )
              {
                if ( i == 2 )
                {
                  *(&Buffer.m_partyActor.m_nUpdateMode + 352 * index + v18[2] + 7) = PropertyByIndex;
                }
                else if ( i == 3 )
                {
                  *((_DWORD *)&Buffer.m_partyActor.m_pRoleState + 352 * index + v18[3] + 1) = PropertyByIndex;
                }
                else
                {
                  *((_DWORD *)&Buffer.m_partyActor.m_bDirFlag + 352 * index + 8 * i + v18[i] + 8) = PropertyByIndex;
                }
                ++v18[i];
              }
            }
          }
          else
          {
            v9 = v18[5] + 352 * index;
            ++v18[5];
            *((_DWORD *)&Buffer.m_fRotAxisY + v9) = PropertyByIndex;
          }
        }
      }
      ++v2;
    }
    while ( v2 < indexa );
  }
  do
  {
    v11 = 1;
    v12 = 6;
    v13 = &Buffer.m_partyActor.m_bDirFlag + v17 + 36;
    do
    {
      result = v13;
      v15 = 7;
      do
      {
        if ( *(_DWORD *)result )
        {
          if ( *((_DWORD *)result - 1) > *(_DWORD *)result )
          {
            v16 = *((_DWORD *)result - 1);
            *((_DWORD *)result - 1) = *(_DWORD *)result;
            v11 = 0;
            *(_DWORD *)result = v16;
          }
        }
        result = (char *)result + 4;
        --v15;
      }
      while ( v15 );
      v13 += 32;
      --v12;
    }
    while ( v12 );
  }
  while ( !v11 );
  return result;
}

// 0x0040EE00
int NPC::FreeBuffer()
{
  operator delete(this->m_pBuffer);
  this->m_pBuffer = 0;
  this->m_nBufStart = 0;
  this->m_nBufEnd = 0;
  return 0;
}

// 0x0040EE30
char NPC::ShiftBufferData(int nVal)
{
  int m_nBufStart; // eax
  gbVec3D *v5; // edi
  char *m_pBuffer; // edx
  unsigned int v7; // ecx
  int v8; // eax
  int v9; // eax
  char *v10; // eax
  int *v11; // ebp
  int i; // ebx
  char *v13; // eax
  int v14; // ecx
  int v15; // eax
  char *v16; // [esp+0x4] [ebp-0x8]
  int v17; // [esp+0x8] [ebp-0x4]

  if ( this->HasBufferData(nVal) )
    return 0;
  m_nBufStart = this->m_nBufStart;
  v5 = (gbVec3D *)m_nBufStart;
  if ( (this->m_nBufEnd - m_nBufStart) >> 2 )
  {
    Vec3D_CopyStruct((gbVec3D *)m_nBufStart, (gbVec3D *)m_nBufStart, (gbVec3D *)(m_nBufStart + 4));
    ((Actor *)this)->StoreParam(this->m_nBufStart, 1 - ((this->m_nBufStart - (int)v5) >> 2));
    v15 = this->m_nBufStart;
    if ( v5 == (gbVec3D *)v15 )
    {
      this->m_nBufStart += 4;
      return 1;
    }
    else
    {
      do
      {
        LODWORD(v5->x) = nVal;
        v5 = (gbVec3D *)((char *)v5 + 4);
      }
      while ( v5 != (gbVec3D *)v15 );
      this->m_nBufStart += 4;
      return 1;
    }
  }
  else
  {
    m_pBuffer = this->m_pBuffer;
    if ( !m_pBuffer || (v7 = (m_nBufStart - (int)m_pBuffer) >> 2, v7 <= 1) )
      v7 = 1;
    if ( m_pBuffer )
      v8 = (m_nBufStart - (int)m_pBuffer) >> 2;
    else
      v8 = 0;
    v9 = v7 + v8;
    v17 = v9;
    if ( v9 < 0 )
      v9 = 0;
    v10 = (char *)operator new(4 * v9);
    v11 = (int *)this->m_pBuffer;
    v16 = v10;
    for ( i = (int)v10; v11 != (int *)v5; i += 4 )
      AssignInt((int *)i, v11++);
    ((Actor *)this)->StoreParam(i, 1);
    Vec3D_CopyStruct(v5, (gbVec3D *)this->m_nBufStart, (gbVec3D *)(i + 4));
    nullsub_2(this->m_pBuffer, this->m_nBufStart);
    operator delete(this->m_pBuffer);
    v13 = this->m_pBuffer;
    this->m_nBufEnd = (int)&v16[4 * v17];
    if ( v13 )
    {
      v14 = this->m_nBufStart;
      this->m_pBuffer = v16;
      this->m_nBufStart = (int)&v16[4 * ((v14 - (int)v13) >> 2) + 4];
    }
    else
    {
      this->m_pBuffer = v16;
      this->m_nBufStart = (int)(v16 + 4);
    }
    return 1;
  }
}

// 0x0040F000
bool NPC::HasBufferData(int nVal)
{
  unsigned int m_nBufStart; // edx
  char *m_pBuffer; // eax
  bool v4; // cf

  m_nBufStart = this->m_nBufStart;
  m_pBuffer = this->m_pBuffer;
  v4 = (unsigned int)m_pBuffer < m_nBufStart;
  if ( m_pBuffer != (char *)m_nBufStart )
  {
    do
    {
      if ( *(_DWORD *)m_pBuffer == nVal )
        break;
      m_pBuffer += 4;
    }
    while ( m_pBuffer != (char *)m_nBufStart );
    return (unsigned int)m_pBuffer < m_nBufStart;
  }
  return v4;
}

// 0x0040F030
int NPC::GetBufferCount()
{
  char *m_pBuffer; // edx

  m_pBuffer = this->m_pBuffer;
  if ( m_pBuffer )
    return (this->m_nBufStart - (int)m_pBuffer) >> 2;
  else
    return 0;
}

// 0x0040F050
int NPC::GetBufferAt(int nIndex)
{
  return *(_DWORD *)&this->m_pBuffer[4 * nIndex];
}

// 0x0040F060
int NPC::SetRoleMode(int nVal)
{
  int result; // eax

  ::nVal = nVal;
  result = nVal;
  if ( nVal )
  {
    if ( nVal == 1 )
    {
      *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4] = 1;
      g_RoleSystemMain.m_FrameA.m_rect.bottom = 10;
      ((RoleSystem *)&g_RoleSystemMain)->SetActorTexture((const char *)&g_pszScene2);
    }
    else
    {
      result = nVal - 2;
      if ( nVal == 2 )
      {
        g_RoleSystemMain.m_FrameA.m_rect.bottom = 0;
        *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4] = 1;
        g_RoleSystemMain.m_FrameA.m_rect.right = 1;
        return 1;
      }
    }
  }
  else
  {
    *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4] = 0;
    g_RoleSystemMain.m_FrameA.m_rect.bottom = 0;
  }
  return result;
}

// 0x0040F620
int NPC::InitAll(int nMaxCount)
{
  int result; // eax
  _BYTE *v2; // ebx
  char *v3; // edi
  int v4; // ebp
  int v5; // eax
  _DWORD *v6; // ecx
  int v7; // edx
  _DWORD *v8; // esi
  int v9; // eax
  _DWORD *v10; // ecx
  int v11; // eax
  int v12; // [esp+0x10] [ebp-0xC]
  char **p_m_pData; // [esp+0x14] [ebp-0x8]
  char *v14; // [esp+0x18] [ebp-0x4]

  result = (int)&g_SceneMgrPrefix.m_pData;
  v12 = 0;
  v2 = &Buffer.m_partyActor.m_bDirFlag + 24;
  p_m_pData = &g_SceneMgrPrefix.m_pData;
  do
  {
    v3 = *(char **)(result - 4);
    v14 = *(char **)result;
    if ( v3 != *(char **)result )
    {
      do
      {
        v4 = *(_DWORD *)v3;
        v5 = 0;
        v6 = v2 - 24;
        do
        {
          if ( v4 == *v6 )
          {
            v2[v5] = 1;
            goto LABEL_14;
          }
          ++v5;
          ++v6;
        }
        while ( v5 < 6 );
        v7 = 0;
        v8 = v2 + 8;
        while ( 2 )
        {
          v9 = 0;
          v10 = v8;
          do
          {
            if ( v4 == *v10 )
            {
              v11 = v9 + 8 * (v7 + v12);
              *((_BYTE *)&Buffer.m_FrameA.m_rect.left + v11) = 1;
              *((_BYTE *)&Buffer.m_fMoveRadius + v11) = v3[4];
              *((_BYTE *)&Buffer.m_FrameA.m_bfocus + v11) = v3[6];
              goto LABEL_14;
            }
            ++v9;
            ++v10;
          }
          while ( v9 < 8 );
          ++v7;
          v8 += 8;
          if ( v7 < 6 )
            continue;
          break;
        }
LABEL_14:
        v3 += 12;
      }
      while ( v3 != v14 );
      result = (int)p_m_pData;
    }
    result += 16;
    v2 += 1408;
    p_m_pData = (char **)result;
    v12 += 176;
  }
  while ( result < (int)&Buffer.m_wndcolor );
  return result;
}

// 0x0040F6F0
int NPC::ReadBufferData(FILE *Stream)
{
  int v3; // esi
  char *m_pBuffer; // eax
  int result; // eax
  int Buffer; // [esp+0xC] [ebp-0x4] BYREF

  v3 = 0;
  m_pBuffer = this->m_pBuffer;
  if ( m_pBuffer )
    Buffer = (this->m_nBufStart - (int)m_pBuffer) >> 2;
  else
    Buffer = 0;
  fwrite(&Buffer, 4u, 1u, Stream);
  result = Buffer;
  if ( Buffer > 0 )
  {
    do
    {
      fwrite(&this->m_pBuffer[4 * v3], 4u, 1u, Stream);
      result = Buffer;
      ++v3;
    }
    while ( v3 < Buffer );
  }
  return result;
}

// 0x0040F760
int NPC::LoadBufferFromStream(FILE *fp)
{
  int m_nBufStart; // eax
  int result; // eax
  int v5; // eax
  gbVec3D *v6; // edi
  char *m_pBuffer; // edx
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  gbVec3D *v11; // ebx
  gbVec3D *v12; // ebp
  int ArrayCount; // eax
  int v14; // ecx
  _DWORD *p_x; // eax
  int v16; // [esp+0x10] [ebp-0x10] BYREF
  int Buffer; // [esp+0x14] [ebp-0xC] BYREF
  int i; // [esp+0x18] [ebp-0x8]
  int v19; // [esp+0x1C] [ebp-0x4]

  Buffer = 0;
  fread(&Buffer, 4u, 1u, fp);
  m_nBufStart = this->m_nBufStart;
  this->m_nBufStart = (int)this->m_pBuffer;
  v19 = m_nBufStart;
  result = Buffer;
  for ( i = 0; i < Buffer; ++i )
  {
    fread(&v16, 4u, 1u, fp);
    v5 = this->m_nBufStart;
    v6 = (gbVec3D *)v5;
    if ( (this->m_nBufEnd - v5) >> 2 )
    {
      Vec3D_CopyStruct((gbVec3D *)v5, (gbVec3D *)v5, (gbVec3D *)(v5 + 4));
      ((Actor *)this)->StoreParam(this->m_nBufStart, 1 - ((this->m_nBufStart - (int)v6) >> 2));
      v14 = this->m_nBufStart;
      p_x = (_DWORD *)&v6->x;
      if ( v6 != (gbVec3D *)v14 )
      {
        do
          *p_x++ = v16;
        while ( p_x != (_DWORD *)v14 );
      }
      this->m_nBufStart += 4;
    }
    else
    {
      m_pBuffer = this->m_pBuffer;
      if ( !m_pBuffer || (v8 = (v5 - (int)m_pBuffer) >> 2, v8 <= 1) )
        v8 = 1;
      if ( m_pBuffer )
        v9 = (v5 - (int)m_pBuffer) >> 2;
      else
        v9 = 0;
      v10 = v8 + v9;
      v19 = v10;
      if ( v10 < 0 )
        v10 = 0;
      v11 = (gbVec3D *)operator new(4 * v10);
      v12 = Vec3D_CopyStruct((gbVec3D *)this->m_pBuffer, v6, v11);
      ((Actor *)this)->StoreParam((int)v12, 1);
      Vec3D_CopyStruct(v6, (gbVec3D *)this->m_nBufStart, (gbVec3D *)&v12->y);
      nullsub_2(this->m_pBuffer, this->m_nBufStart);
      operator delete(this->m_pBuffer);
      this->m_nBufEnd = (int)v11 + 4 * v19;
      ArrayCount = ((Actor *)this)->GetArrayCount();
      this->m_pBuffer = (char *)v11;
      this->m_nBufStart = (int)(&v11->y + ArrayCount);
    }
    result = i + 1;
  }
  return result;
}

// 0x0040F950
size_t NPC::SaveToStream(FILE *Stream)
{
  int v3; // edi
  char *m_pBuffer; // eax
  int i; // esi
  int Buffer; // [esp+0x10] [ebp-0x4] BYREF

  v3 = 0;
  m_pBuffer = this->m_pBuffer;
  if ( m_pBuffer )
    Buffer = (this->m_nBufStart - (int)m_pBuffer) / 12;
  else
    Buffer = 0;
  fwrite(&Buffer, 4u, 1u, Stream);
  for ( i = 0; i < Buffer; v3 += 12 )
  {
    fwrite(&this->m_pBuffer[v3], 0xCu, 1u, Stream);
    ++i;
  }
  return fwrite(&this->_todo_24, 4u, 1u, Stream);
}

// 0x0040F9E0
size_t NPC::LoadFromStream(FILE *Stream)
{
  char *m_pBuffer; // edx
  void *m_nBufStart; // eax
  int SkillNum; // eax
  int *v6; // ecx
  int m_nBufEnd; // edx
  int *v8; // edi
  unsigned int v9; // edx
  char *v10; // eax
  unsigned int v11; // ebx
  int v12; // eax
  bool v13; // sf
  unsigned int v14; // ebp
  unsigned int v15; // eax
  char *v16; // ebx
  int v17; // eax
  int j; // eax
  int *v19; // ecx
  int Buffer; // [esp+0x10] [ebp-0x18] BYREF
  int i; // [esp+0x14] [ebp-0x14]
  void *v23; // [esp+0x18] [ebp-0x10]
  int nVal; // [esp+0x1C] [ebp-0xC] BYREF
  int v25; // [esp+0x20] [ebp-0x8]
  int v26; // [esp+0x24] [ebp-0x4]

  Buffer = 0;
  fread(&Buffer, 4u, 1u, Stream);
  m_pBuffer = this->m_pBuffer;
  nVal = 0xFFFF;
  v25 = 0;
  v26 = 0;
  m_nBufStart = (void *)this->m_nBufStart;
  this->m_nBufStart = (int)m_pBuffer;
  v23 = m_nBufStart;
  for ( i = 0; i < Buffer; ++i )
  {
    fread(&nVal, 0xCu, 1u, Stream);
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal);
    v6 = (int *)this->m_nBufStart;
    m_nBufEnd = this->m_nBufEnd;
    v26 = SkillNum;
    v8 = v6;
    v9 = (int)((unsigned __int64)(715827883LL * (m_nBufEnd - (int)v6)) >> 32) >> 1;
    if ( (v9 >> 31) + v9 )
    {
      ((Array *)this)->Insert(v6, v6);
      ((Array *)this)->Erase(this->m_nBufStart, 1 - (this->m_nBufStart - (int)v8) / 12);
      for ( j = this->m_nBufStart; v8 != (int *)j; v19[2] = v26 )
      {
        v19 = v8;
        v8 += 3;
        *v19 = nVal;
        v19[1] = v25;
      }
      this->m_nBufStart += 12;
    }
    else
    {
      v10 = this->m_pBuffer;
      if ( !v10 || (v11 = ((char *)v6 - v10) / 12, v11 <= 1) )
        v11 = 1;
      v12 = ((Array *)this)->Size();
      v13 = (int)(v11 + v12) < 0;
      v14 = v11 + v12;
      v15 = v11 + v12;
      if ( v13 )
        v15 = 0;
      v16 = (char *)operator new(12 * v15);
      v23 = ((Array *)this)->Insert(this->m_pBuffer, v8);
      ((Array *)this)->Erase((int)v23, 1);
      ((Array *)this)->Insert(v8, (void *)this->m_nBufStart);
      nullsub_2(this->m_pBuffer, this->m_nBufStart);
      operator delete(this->m_pBuffer);
      this->m_nBufEnd = (int)&v16[12 * v14];
      v17 = ((Array *)this)->Size();
      this->m_pBuffer = v16;
      this->m_nBufStart = (int)&v16[12 * v17 + 12];
    }
  }
  return fread(&this->_todo_24, 4u, 1u, Stream);
}

// 0x00410580
void NPC::SetSceneFlag()
{
  int v1; // [esp+0x4] [ebp+0x4]

  if ( v1 == 31 )
    g_nSceneTransitionParam2 = 1;
  else
    *(&Buffer.m_partyActor.m_nActionParam + v1) = 1;
  g_fFadeTimer = 0.0;
}

// 0x0043F560
int NPC::CreateChild()
{
  int v1; // edx

  if ( *((int *)&this->m_WndContainer + 30) <= 0 )
    return -1;
  v1 = *((_DWORD *)&this->m_AnimWndC + 65);
  if ( v1 == -1 )
    return -1;
  else
    return v1 + *((_DWORD *)&this->m_AnimWndC + 64);
}

// 0x00446020
void NPC::NPC::UpdateAnim()
{
  int v1; // [esp+0x4] [ebp+0x4]

  this->m_nBufStart = v1;
}

// 0x00479100
int NPC::GetPropertyByIndex(unsigned int dwVal)
{
  if ( dwVal > 0x12C )
    return 0;
  else
    return *((_DWORD *)this + 190 * dwVal + 42640);
}

// 0x00517A50
void NPC::DestroyAndRecreateUI()
{
  CCBUI **v1; // esi
  char v2; // al
  CCBUI *v3; // ecx
  int nCount; // [esp+0x8] [ebp-0x10] BYREF
  int v5; // [esp+0xC] [ebp-0xC]
  int v6; // [esp+0x10] [ebp-0x8]
  int v7; // [esp+0x14] [ebp-0x4]

  v1 = (CCBUI **)((char *)&this->m_AnimWndC + 256);
  ((CCBAIWindow *)this)->Destroy();
  if ( v2 )
  {
    v5 = 0;
    v6 = 0;
    v3 = *v1;
    nCount = 10;
    v6 = 266;
    v5 = 225;
    v7 = 481;
    ((CCBUI *)v3)->CreateImbibeNimbus((int)&nCount);
// [VFTABLE] ((void ( *)(CCBUI *, _DWORD))(*v1)->__vftable->ShowWindow)(*v1, 0);
  }
}

// 0x00517AC0
char NPC::HandleAIMessage(int thisa, int nVal)
{
  CCBUI **v4; // esi
  char result; // al
  CCBUI *v6; // ecx
  tagRECT v7; // [esp+0x8] [ebp-0x10] BYREF

  v4 = (CCBUI **)((char *)&this->m_AnimWndC + 260);
  result = ((CCBAIWindow *)this)->OnMessage((UIListBox **)&this->m_AnimWndC + 65);
  if ( result )
  {
    v7.top = 0;
    v7.right = 0;
    v6 = *v4;
    v7.left = 6;
    v7.right = 255;
    v7.top = 278;
    v7.bottom = 484;
    ((CCBUI *)v6)->CreateButton(&v7, this);
// [VFTABLE] ((void ( *)(CCBUI *, _DWORD))(*v4)->__vftable->ShowWindow)(*v4, 0);
    return 1;
  }
  return result;
}

// 0x00517BA0
void NPC::ShowAIWindow()
{
  CCBControlWindow **v2; // esi
  CCBControlWindow *v3; // ecx
  int pRect; // [esp+0x8] [ebp-0x10] BYREF
  int v5; // [esp+0xC] [ebp-0xC]
  int v6; // [esp+0x10] [ebp-0x8]
  int v7; // [esp+0x14] [ebp-0x4]

  v2 = (CCBControlWindow **)((char *)&this->m_AnimWndC + 268);
  if ( ((CCBAIWindow *)this)->ShowWindow((CCBControlWindow **)&this->m_AnimWndC + 67) )
  {
    v5 = 0;
    v6 = 0;
    v3 = *v2;
    pRect = 5;
    v6 = 261;
    v5 = 237;
    v7 = 493;
    ((CCBControlWindow *)v3)->OnMessage(&pRect, (int)this);
// [VFTABLE] ((void ( *)(CCBControlWindow *, _DWORD))(*v2)->__vftable->ShowWindow)(*v2, 0);
  }
}

// 0x00517CF0
void NPC::ResetLineupWindow()
{
  CCBMagicWindow **v2; // esi
  char v3; // al
  CCBMagicWindow *v4; // ecx
  int ppButton; // [esp+0x8] [ebp-0x10] BYREF
  int v6; // [esp+0xC] [ebp-0xC]
  int v7; // [esp+0x10] [ebp-0x8]
  int v8; // [esp+0x14] [ebp-0x4]

  v2 = (CCBMagicWindow **)((char *)&this->m_AnimWndC + 280);
  ((CCBLineupWindow *)this)->Reset((CCBMagicWindow **)&this->m_AnimWndC + 70);
  if ( v3 )
  {
    v6 = 0;
    v7 = 0;
    v4 = *v2;
    ppButton = 10;
    v7 = 240;
    v6 = 271;
    v8 = 471;
    ((CCBMagicWindow *)v4)->CreateButton(&ppButton, (int)this);
// [VFTABLE] ((void ( *)(CCBMagicWindow *, _DWORD))(*v2)->__vftable->ShowWindow)(*v2, 0);
  }
}
