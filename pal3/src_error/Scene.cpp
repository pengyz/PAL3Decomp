#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/Scene.h"
#include "Misc/Array.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Script/ScriptObj.h"
#include "Misc/UITextArea.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
void __cdecl nullsub_2(...);

// 0x0040C7D0
void Scene::Render2()
{
  int i; // esi
  float v2; // st7
  gbPrintFont *v3; // edi
  Scene *v4; // ebx
  int v5; // ebp
  int *p_m_active; // esi
  float v7; // [esp+0xC] [ebp-B8h]
  float v8; // [esp+0x30] [ebp-0x94] BYREF
  int v9; // [esp+0x34] [ebp-0x90] BYREF
  struct gbVec3D pOut; // [esp+0x38] [ebp-0x8C] BYREF
  char Buffer[128]; // [esp+0x44] [ebp-0x80] BYREF

  (((UITextArea *)&dword_BFDAB0))->UITextArea::Render();
  for ( i = 0; i < nIndex; ++i )
    (((GRPinput *)g_pScriptObjArray[i]))->GRPinput::SetMouseSensitivity();
  (((PalScript *)&g_palScript))->PalScript::RenderUI();
  if ( g_RoleSlotBuf.m_partyActor.m_szTexture[9] )
  {
    v2 = 32.0f / (float)g_DrvInfo.height;
    v3 = gfxMgr->pFontMgr->pAllFont[3];
    v3->ScaleX = 32.0f / (float)g_DrvInfo.width;
    v3->ScaleY = v2;
    v3->curColor.Color = -2134325048;
    v4 = UISceneUpdate();
    v5 = 0;
    if ( v4->m_nTodo_e0e0 > 0 )
    {
      p_m_active = (int *)&v4->m_roles[0].m_active;
      do
      {
        if ( *(p_m_active - 122) && *p_m_active && *((_BYTE *)p_m_active - 459) == 2 )
        {
          memset(&pOut, 0, sizeof(pOut));
          (((RoleSystem *)(p_m_active - 158)))->RoleSystem::GetDirection(&pOut.x);
          (((gbCamera *)&g_pCameraCtrl->m_fMinDist))->gbCamera::PointWorldToScr(&pOut, &v8, (float *)&v9);
          sprintf(Buffer, (const char *)&dir[20], *((unsigned __int8 *)p_m_active - 332));
          v7 = v8 - 0.05000000074505806f;
          ((void ( *)(gbPrintFont *, char *, _DWORD, int, int, int))v3->pGfxMgr->DrvInfo.subtype)(
            v3,
            Buffer,
            LODWORD(v7),
            v9,
            1176256512,
            1176256512);
        }
        ++v5;
        p_m_active += 2176;
      }
      while ( v5 < v4->m_nTodo_e0e0 );
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

  m_pDataEnd = (char *)this->m_pDataEnd;
  v4 = (char *)m_pDataEnd;
  if ( (this->m_pCapacity[0] - m_pDataEnd) / 12 )
  {
    (((Array *)this))->Array::Insert(m_pDataEnd, m_pDataEnd);
    (((Array *)this))->Array::Erase((int)this->m_pDataEnd, 1 - (this->m_pDataEnd - v4) / 12);
    v15 = (char *)this->m_pDataEnd;
    v16 = (char *)v4;
    if ( v4 == v15 )
    {
      result = (int)(this->m_pDataEnd + 12);
      this->m_pDataEnd = ((char *)((char *)result));
    }
    else
    {
      do
      {
        v17 = (int *)v16;
        v16 += 12;
        *v17 = *pRoleTriple;
        v17[1] = (unsigned long)pRoleTriple[1];
        v17[2] = (unsigned long)pRoleTriple[2];
      }
      while ( v16 != v15 );
      result = (int)(this->m_pDataEnd + 12);
      this->m_pDataEnd = ((char *)((char *)result));
    }
  }
  else
  {
    m_pDataBegin = (char *)this->m_pDataBegin;
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
    v10 = (char *)this->m_pDataBegin;
    v19 = (char *)v9;
    for ( i = v9; v10 != v4; i += 12 )
    {
      Array::Copy(i);
      v10 += 12;
    }
    (((Array *)this))->Array::Erase((int)i, 1);
    (((Array *)this))->Array::Insert(v4, this->m_pDataEnd);
    nullsub_2(this->m_pDataBegin, this->m_pDataEnd);
    operator delete(this->m_pDataBegin);
    this->m_pCapacity[0] = &v19[12 * v18];
    v12 = (char *)this->m_pDataBegin;
    if ( v12 )
    {
      v14 = (char *)this->m_pDataEnd;
      this->m_pDataBegin = ((char *)(v19));
      result = (int)&v19[12 * ((v14 - v12) / 12) + 12];
      this->m_pDataEnd = ((char *)((char *)result));
    }
    else
    {
      this->m_pDataBegin = ((char *)(v19));
      result = (int)(v19 + 12);
      this->m_pDataEnd = ((char *)(v19 + 12));
    }
  }
  return result;
}

// 0x00421230
double Scene::GetTileHeight(int nSceneIdx, int nX, int nY, int *pFlags)
{
  int RolePtr; // eax
  int v7; // edi
  float result; // st7
  char *v9; // esi
  int v10; // ecx
  gbMatrix4 pMatrix; // [esp+0x10] [ebp-0x4C] BYREF
  float v12; // [esp+0x54] [ebp-0x8]
  unsigned __int8 nSceneIdxa; // [esp+0x60] [ebp+0x4]
  float pFlagsa; // [esp+0x6C] [ebp+0x10]

  RolePtr = (((RoleSystem *)this))->RoleSystem::GetRolePtr(nSceneIdx) /* [ROWTABLE] */;
  v7 = RolePtr;
  if ( nX >= 0 && nX < *(_DWORD *)(RolePtr + 152) && nY >= 0 && nY < *(_DWORD *)(RolePtr + 156) )
  {
    if ( pFlags )
      *pFlags = 2;
    nSceneIdxa = (((RoleSystem *)&this->m_objmap[nSceneIdx]))->RoleSystem::GetTile(nX, nY);
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
          (((PalScriptMgr *)(v9 + 224)))->PalScriptMgr::BuildCmdTransform(&pMatrix);
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
          result = *((float *)v9 + 67) + 24.0f;
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

// 0x00421870
void Scene::_todo_421870()
{
  gbGeomNode *m_geomnode; // eax

  m_geomnode = (gbGeomNode *)this->m_geomnode;
  if ( m_geomnode && this->m_nTodo_78658 )
    (((gbSceneGraph *)gfxMgr->pSceneGraph))->gbSceneGraph::DelVisNode(m_geomnode);
  this->m_nTodo_78658 = 0;
}
