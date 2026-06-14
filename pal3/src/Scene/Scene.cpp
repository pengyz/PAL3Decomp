#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/Scene.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations

// Unnamed globals (extern)
extern std::ios_base dword_BFDAB0;
void __cdecl nullsub_2(...);

// 0x0040C7D0
void Scene::Render2()
{
  int i; // esi
  double v2; // st7
  gbPrintFont *v3; // edi
  int v4; // ebx
  int v5; // ebp
  _DWORD *v6; // esi
  float v7; // [esp+0xC] [ebp-B8h]
  float v8; // [esp+0x30] [ebp-0x94] BYREF
  int v9; // [esp+0x34] [ebp-0x90] BYREF
  struct gbVec3D pOut; // [esp+0x38] [ebp-0x8C] BYREF
  char Buffer[128]; // [esp+0x44] [ebp-0x80] BYREF

  ((UITextArea *)dword_BFDAB0)->Render();
  for ( i = 0; i < (int)g_pScriptEventObj; ++i )
    ((GRPinput *)g_pScriptObjArray[i])->SetMouseSensitivity();
  ((PalScript *)&g_UIScript)->RenderUI();
  if ( BYTE1(::Buffer.m_partyActor.m_vecPos.x) )
  {
    v2 = 32.0 / (double)g_DrvInfo.height;
    v3 = gfxMgr->pFontMgr->pAllFont[3];
    v3->ScaleX = 32.0 / (double)g_DrvInfo.width;
    v3->ScaleY = v2;
    v3->curColor.Color = -2134325048;
    v4 = UISceneUpdate();
    v5 = 0;
    if ( *(int *)(v4 + 57568) > 0 )
    {
      v6 = (_DWORD *)(v4 + 58204);
      do
      {
        if ( *(v6 - 122) && *v6 && *((_BYTE *)v6 - 459) == 2 )
        {
          memset(&pOut, 0, sizeof(pOut));
          ((RoleSystem *)(v6 - 158))->GetDirection(&pOut.x);
          ((gbCamera *)&g_pCameraCtrl->m_fMinDist)->PointWorldToScr(&pOut, &v8, (float *)&v9);
          sprintf(Buffer, &dir[20], *((unsigned __int8 *)v6 - 332));
          v7 = v8 - 0.050000001;
          ((void ( *)(gbPrintFont *, char *, _DWORD, int, int, int))v3->pGfxMgr->DrvInfo.subtype)(
            v3,
            Buffer,
            LODWORD(v7),
            v9,
            1176256512,
            1176256512);
        }
        ++v5;
        v6 += 2176;
      }
      while ( v5 < *(_DWORD *)(v4 + 57568) );
    }
    ((void ( *)(gbPrintFont *))v3->pGfxMgr->hGfxWnd)(v3);
  }
}

// 0x00410990
int Scene::AddRoleEntry(const int pRoleTriple[3])
{
  char *m_pDataEnd; // ecx
  char *v4; // edi
  char *m_pDataBegin; // ebx
  unsigned int v6; // ebp
  int v7; // edx
  unsigned int v8; // eax
  char *v9; // eax
  char *v10; // ebp
  char *i; // ebx
  char *v12; // eax
  int result; // eax
  char *v14; // ecx
  char *v15; // ecx
  char *v16; // eax
  int *v17; // edi
  unsigned int v18; // [esp+0x10] [ebp-0x8]
  char *v19; // [esp+0x14] [ebp-0x4]

  m_pDataEnd = this->m_pDataEnd;
  v4 = m_pDataEnd;
  if ( (this->m_pCapacity[0] - m_pDataEnd) / 12 )
  {
    ((Array *)this)->Insert(m_pDataEnd, m_pDataEnd);
    ((Array *)this)->Erase((int)this->m_pDataEnd, 1 - (this->m_pDataEnd - v4) / 12);
    v15 = this->m_pDataEnd;
    v16 = v4;
    if ( v4 == v15 )
    {
      result = (int)(this->m_pDataEnd + 12);
      this->m_pDataEnd = (char *)result;
    }
    else
    {
      do
      {
        v17 = (int *)v16;
        v16 += 12;
        *v17 = *pRoleTriple;
        v17[1] = pRoleTriple[1];
        v17[2] = pRoleTriple[2];
      }
      while ( v16 != v15 );
      result = (int)(this->m_pDataEnd + 12);
      this->m_pDataEnd = (char *)result;
    }
  }
  else
  {
    m_pDataBegin = this->m_pDataBegin;
    if ( !m_pDataBegin || (v6 = (m_pDataEnd - m_pDataBegin) / 12, v6 <= 1) )
      v6 = 1;
    if ( m_pDataBegin )
      v7 = (m_pDataEnd - m_pDataBegin) / 12;
    else
      v7 = 0;
    v8 = v7 + v6;
    v18 = v7 + v6;
    if ( (int)(v7 + v6) < 0 )
      v8 = 0;
    v9 = (char *)operator new(12 * v8);
    v10 = this->m_pDataBegin;
    v19 = v9;
    for ( i = v9; v10 != v4; i += 12 )
    {
      ((Array *)i)->Copy(v10);
      v10 += 12;
    }
    ((Array *)this)->Erase((int)i, 1);
    ((Array *)this)->Insert(v4, this->m_pDataEnd);
    nullsub_2(this->m_pDataBegin, this->m_pDataEnd);
    operator delete(this->m_pDataBegin);
    this->m_pCapacity[0] = &v19[12 * v18];
    v12 = this->m_pDataBegin;
    if ( v12 )
    {
      v14 = this->m_pDataEnd;
      this->m_pDataBegin = v19;
      result = (int)&v19[12 * ((v14 - v12) / 12) + 12];
      this->m_pDataEnd = (char *)result;
    }
    else
    {
      this->m_pDataBegin = v19;
      this->m_pDataEnd = v19 + 12;
      return (int)(v19 + 12);
    }
  }
  return result;
}

// 0x00421230
double Scene::GetTileHeight(int nSceneIdx, int nX, int nY, int *pFlags)
{
  int RolePtr; // eax
  int v7; // edi
  double result; // st7
  char *v9; // esi
  int v10; // ecx
  gbMatrix4 pMatrix; // [esp+0x10] [ebp-0x4C] BYREF
  float v12; // [esp+0x54] [ebp-0x8]
  unsigned __int8 nSceneIdxa; // [esp+0x60] [ebp+0x4]
  float pFlagsa; // [esp+0x6C] [ebp+0x10]

  RolePtr = ((RoleSystem *)this)->GetRolePtr(nSceneIdx);
  v7 = RolePtr;
  if ( nX >= 0 && nX < *(_DWORD *)(RolePtr + 152) && nY >= 0 && nY < *(_DWORD *)(RolePtr + 156) )
  {
    if ( pFlags )
      *pFlags = 2;
    nSceneIdxa = ((RoleSystem *)&this->m_objmap[nSceneIdx])->GetTile(nX, nY);
    if ( nSceneIdxa == 0xFF || (v9 = (char *)this + 896 * nSceneIdxa, !v9[397]) )
    {
LABEL_22:
      if ( pFlags )
        *pFlags = 1;
      return *(float *)(*(_DWORD *)(v7 + 160) + 8 * (nX + nY * *(_DWORD *)(v7 + 152)));
    }
    else
    {
      switch ( v9[468] )
      {
        case 5:
        case 7:
        case 19:
        case 33:
        case 38:
        case 40:
          goto LABEL_13;
        case 11:
          if ( *((_DWORD *)v9 + 118) != 1 )
            goto LABEL_22;
          pFlagsa = *((float *)v9 + 67);
          ((PalScriptMgr *)(v9 + 224))->BuildCmdTransform(&pMatrix);
          result = v12 + pFlagsa;
          v10 = *(_DWORD *)(v7 + 160) + 8 * (nX + *(_DWORD *)(v7 + 152) * (__int64)result);
          if ( *(_BYTE *)(v10 + 4) >= 2u && result <= *(float *)v10 )
            goto LABEL_17;
          return result;
        case 22:
        case 34:
        case 37:
          v10 = *(_DWORD *)(v7 + 160) + 8 * (nX + nY * *(_DWORD *)(v7 + 152));
          if ( *(_BYTE *)(v10 + 4) < 2u )
          {
LABEL_13:
            result = *((float *)v9 + 67);
          }
          else if ( *(float *)v10 >= (double)*((float *)v9 + 67) )
          {
LABEL_17:
            result = *(float *)v10;
          }
          else
          {
            result = *((float *)v9 + 67);
          }
          break;
        case 29:
          result = *((float *)v9 + 67) + 24.0;
          break;
        default:
          goto LABEL_22;
      }
    }
  }
  else
  {
    if ( pFlags )
      *pFlags = 0;
    return 0.0;
  }
  return result;
}
