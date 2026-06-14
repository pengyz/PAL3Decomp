#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBStageScene.h"

// Forward declarations for unnamed functions
int sub_511630(...);
int sub_511E20(...);

struct gbVFileSystem * LoadScene(double sceneNames, char *arg8, char *pszBuf, char pData, char pData2); // from annotations

// Unnamed globals (extern)
extern char aEnemyfivelineu[];
extern char aFivelineup[];
extern char byte_17ABD00[256];
extern char byte_17ABE00[256];
extern char byte_5967B0[3];
extern void * off_5EFAB4;
extern RoleSystem stru_C059A0;

// 0x004FBA70
int CCBStageScene::ResetSceneState()
{
  CCBStageScene *v2; // eax
  unsigned int v3; // edi
  CCBStageScene *v4; // eax
  int result; // eax
  float *i; // ebx
  CCBStageRole *v7; // eax
  CCBStageRole *OBBox; // eax
  CCBStage *v9; // eax
  CameraCtrl *v10; // eax
  CCBCamControl *v11; // eax
  CCBStageCam *v12; // eax
  CCBStage *v13; // eax
  int *inited; // eax
  CCBStageShadow *v15; // eax
  CCBCamControl *v16; // eax
  CCBCamControl *v17; // eax
  char pExceptionObject[1024]; // [esp+0x10] [ebp-0x100C] BYREF
  char ArgList[1024]; // [esp+0x410] [ebp-C0Ch] BYREF
  char v20[1024]; // [esp+0x810] [ebp-0x80C] BYREF
  char v21; // [esp+C10h] [ebp-0x40C] BYREF
  int v22; // [esp+0x1018] [ebp-0x4]

  v2 = (CCBStageScene *)operator new(0x3CCu);
  v3 = 0;
  v22 = 0;
  if ( v2 )
    // [AUTO-COMMENTED] v4 = ((CCBStageScene *)v2)->CCBStageScene((CCBStage *)this);
  else
    v4 = 0;
  v22 = -1;
  LODWORD(this->m_vecFiveLineup[1].x) = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_2, 6003),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( (_BYTE)result )
  {
    for ( i = &this->m_vecFiveLineup[1].y; ; ++i )
    {
      v7 = (CCBStageRole *)operator new(0x1A18u);
      v22 = 1;
      if ( v7 )
        OBBox = ((CCBStageRole *)v7)->GetOBBox((int)this);
      else
        OBBox = 0;
      v22 = -1;
      *(_DWORD *)i = OBBox;
      if ( !OBBox )
      {
        qmemcpy(
          pExceptionObject,
          ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_2, 109),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      if ( !((CCBStageRole *)OBBox)->IsIdle(v3) )
        break;
      if ( (int)++v3 >= 11 )
      {
        v9 = (CCBStage *)operator new(0x17E8u);
        v22 = 2;
        if ( v9 )
          v10 = (CameraCtrl *)((CCBStage *)v9)->ResetTurnData((int **)this, gfxMgr);
        else
          v10 = 0;
        LODWORD(this->m_vecFiveLineup[0].y) = v10;
        v22 = -1;
        if ( !v10 )
        {
          qmemcpy(
            pExceptionObject,
            ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_2, 124),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        LOBYTE(result) = ((CameraCtrl *)v10)->InitFromConfig();
        if ( (_BYTE)result )
        {
          v11 = (CCBCamControl *)operator new(0x690B0u);
          v22 = 3;
          if ( v11 )
            v12 = ((CCBCamControl *)v11)->SetCamPos((int **)this, LODWORD(this->m_vecFiveLineup[0].y));
          else
            v12 = 0;
          v22 = -1;
          LODWORD(this->m_vecFiveLineup[0].z) = v12;
          if ( !v12 )
          {
            qmemcpy(
              pExceptionObject,
              ((Logger *)ArgList)->FormatException(aNewFailedAtCre, aDProjectPal3Co_2, 135),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          LOBYTE(result) = ((CCBStageCam *)v12)->Destroy();
          if ( (_BYTE)result )
          {
            v13 = (CCBStage *)operator new(0x4618u);
            v22 = 4;
            if ( v13 )
              inited = ((CCBStage *)v13)->InitStage((int)this);
            else
              inited = 0;
            v22 = -1;
            LODWORD(this->m_vecFiveLineup[5].x) = inited;
            if ( !inited )
            {
              qmemcpy(
                pExceptionObject,
                ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_2, 6003),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            LOBYTE(result) = ((std *)inited)->codecvt_base::do_always_noconv();
            if ( (_BYTE)result )
            {
              v22 = 5;
              if ( operator new(0x614u) )
                v15 = (CCBStageShadow *)sub_511E20(this);
              else
                v15 = 0;
              v22 = -1;
              LODWORD(this->m_vecFiveLineup[5].y) = v15;
              if ( !v15 )
              {
                qmemcpy(
                  pExceptionObject,
                  ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_2, 6003),
                  sizeof(pExceptionObject));
                _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              if ( (_BYTE)result )
              {
                v16 = (CCBCamControl *)operator new(0x6390u);
                v22 = 6;
                if ( v16 )
                  v17 = ((CCBCamControl *)v16)->SetCircle((int)this);
                else
                  v17 = 0;
                v22 = -1;
                LODWORD(this->m_vecFiveLineup[5].z) = v17;
                if ( !v17 )
                {
                  qmemcpy(
                    v20,
                    ((Logger *)&v21)->FormatException(&path[164], aDProjectPal3Co_2, 6003),
                    sizeof(v20));
                  _CxxThrowException(v20, (_ThrowInfo *)&_TI1_AV_Exception__);
                }
                LOBYTE(result) = ((CCBCamControl *)v17)->IsPointerUnderMouse();
              }
            }
          }
        }
        return result;
      }
    }
  }
  LOBYTE(result) = 0;
  return result;
}

// 0x0050FD00
CCBStageScene::CCBStageScene(CCBStage *pCBStage)
{
  gbVec3D *m_vecFiveLineup; // esi
  int v4; // edi
  gbVec3D *m_vecInitFiveLineup; // esi
  int v6; // edi
  gbVec3D *m_vecEnemyLineup; // esi
  int v8; // edi
  gbVec3D *m_vecInitEnemyLineup; // esi
  int v10; // edi
  float *p_m_fDirSinA; // esi
  int v12; // edi
  int *p_m_nInit; // esi
  int v14; // edi
  float *p_m_fDirSinC; // esi
  int v16; // edi

  m_vecFiveLineup = this->m_vecFiveLineup;
  v4 = 7;
  do
  {
    --v4;
  }
  while ( v4 );
  m_vecInitFiveLineup = this->m_vecInitFiveLineup;
  v6 = 7;
  do
  {
    --v6;
  }
  while ( v6 );
  m_vecEnemyLineup = this->m_vecEnemyLineup;
  v8 = 7;
  do
  {
    --v8;
  }
  while ( v8 );
  m_vecInitEnemyLineup = this->m_vecInitEnemyLineup;
  v10 = 7;
  do
  {
    --v10;
  }
  while ( v10 );
  p_m_fDirSinA = &this->m_fDirSinA;
  v12 = 4;
  do
  {
    p_m_fDirSinA += 3;
    --v12;
  }
  while ( v12 );
  p_m_nInit = &this->m_nInit;
  v14 = 4;
  do
  {
    p_m_nInit += 3;
    --v14;
  }
  while ( v14 );
  p_m_fDirSinC = &this->m_fDirSinC;
  v16 = 4;
  do
  {
    p_m_fDirSinC += 3;
    --v16;
  }
  while ( v16 );
  this->m_fCurAxisX = 0.0;
  this->m_fCurAxisY = 0.0;
  this->m_fCurAxisZ = 0.0;
  this->m_fInitAxisX = 0.0;
  this->m_fInitAxisY = 0.0;
  this->m_fInitAxisZ = 0.0;
  this->m_vecFiveLineupPos.z = 0.0;
  this->m_vecFiveLineupInitPos.x = 0.0;
  this->m_vecFiveLineupInitPos.y = 0.0;
  this->m_fFiveLineupInitRadius = 0.0;
  this->m_fFiveLineupRoll = 0.0;
  this->m_fFiveLineupInitRoll = 0.0;
  memset(this, 0, 0x3CCu);

  this->m_pStage = pCBStage;
  this->m_pUtil = (CUtil *)pCBStage->m_pCBSystem->m_pUtil;
  strcpy(this->m_sLastScene, "???");
  this;
}

// 0x0050FE50
void CCBStageScene::Update()
{
  this->m_fFiveLineupInitRadius = 0.0;
  this->m_fFiveLineupRoll = 0.0;
  this->m_fFiveLineupInitRoll = 0.0;
  BYTE1(this->m_vecEnemyFiveLineupPos.x) = 1;
  BYTE2(this->m_vecEnemyFiveLineupPos.x) = 1;
  HIBYTE(this->m_vecEnemyFiveLineupPos.x) = 1;
  this->m_vecEnemyFiveLineupPos.z = 0.0;
  LOBYTE(this->m_vecEnemyFiveLineupPos.x) = 0;
  LOBYTE(this->m_vecEnemyFiveLineupPos.y) = 0;
  this->m_fBlendRectAX = 0.0;
  this->m_fBlendRectAY = 0.0;
  this->m_fBlendRectAW = 1.0;
  this->m_fBlendRectAH = 1.0;
  this->m_fBlendWeight0 = 0.0;
  this->m_fBlendWeight1 = 0.0;
  this->m_fBlendWeight2 = 1.0;
  this->m_fBlendWeight3 = 1.0;
  this->m_fBlendRectBX = 0.0;
  this->m_fBlendRectBY = 0.0;
  this->m_fBlendRectBW = 1.0;
  this->m_fBlendRectBH = 1.0;
}

// 0x0050FEE0
CCBStageScene::CCBStageScene()
{
  gbTexture *v2; // eax
  float *v3; // eax
  float m_vecFling; // ecx
  gbTexture *v5; // eax
  int *v6; // eax
  int m_nFlingState; // ecx
  char pExceptionObject[1024]; // [esp+0x18] [ebp-0x800] BYREF
  char ArgList; // [esp+0x418] [ebp-0x400] BYREF

  this->m_vecFiveLineup[1].x = -110.0;
  this->m_vecFiveLineup[1].y = 0.0;
  this->m_vecFiveLineup[1].z = -130.0;
  this->m_vecFiveLineup[2].x = 30.0;
  this->m_vecFiveLineup[2].z = -110.0;
  this->m_vecFiveLineup[2].y = 0.0;
  this->m_vecFiveLineup[3].x = -110.0;
  this->m_vecFiveLineup[3].y = 0.0;
  this->m_vecFiveLineup[3].z = 30.0;
  this->m_vecFiveLineup[4].x = 30.0;
  this->m_vecFiveLineup[4].y = 0.0;
  this->m_vecFiveLineup[4].z = 10.0;
  this->m_vecFiveLineup[5].x = -150.0;
  this->m_vecFiveLineup[5].y = 0.0;
  this->m_vecFiveLineup[5].z = -50.0;
  this->m_vecFiveLineup[6].x = -50.0;
  this->m_vecFiveLineup[6].z = -50.0;
  this->m_vecFiveLineup[6].y = 0.0;
  this->m_vecEnemyLineup[1].x = 140.0;
  this->m_vecEnemyLineup[1].y = 0.0;
  this->m_vecEnemyLineup[1].z = 120.0;
  this->m_vecEnemyLineup[2].x = 280.0;
  this->m_vecEnemyLineup[2].y = 0.0;
  this->m_vecEnemyLineup[2].z = 140.0;
  this->m_vecEnemyLineup[3].x = 140.0;
  this->m_vecEnemyLineup[3].y = 0.0;
  this->m_vecEnemyLineup[3].z = 280.0;
  this->m_vecEnemyLineup[4].x = 280.0;
  this->m_vecEnemyLineup[4].y = 0.0;
  this->m_vecEnemyLineup[4].z = 260.0;
  this->m_vecEnemyLineup[5].x = 100.0;
  this->m_vecEnemyLineup[5].y = 0.0;
  this->m_vecEnemyLineup[5].z = 200.0;
  this->m_vecEnemyLineup[6].x = 200.0;
  this->m_vecEnemyLineup[6].y = 0.0;
  this->m_vecEnemyLineup[6].z = 200.0;


  this->m_pFling = (gbGeomNode *)((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\additiveblend.gbf", 0);
  v2 = (gbTexture *)(*(int (**)(gbGfxManager *, void *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, &g_EffMgr);
  LODWORD(this->m_vecFling) = v2;
  ((gbTexture *)v2)->LoadTexture(1);
  v3 = (float *)operator new(0x44u);
  if ( v3 )
  {
    m_vecFling = this->m_vecFling;
    *((_DWORD *)v3 + 16) = 1;
    *v3 = m_vecFling;
  }
  else
  {
    v3 = 0;
  }
  this->m_nLoadPointer = (int)v3;
  v5 = (gbTexture *)(*(int (**)(gbGfxManager *, void *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, &g_EffMgr);
  this->m_nFlingState = (int)v5;
  ((gbTexture *)v5)->LoadTexture(1);
  v6 = (int *)operator new(0x44u);
  if ( v6 )
  {
    m_nFlingState = this->m_nFlingState;
    v6[16] = 1;
    *v6 = m_nFlingState;
  }
  else
  {
    v6 = 0;
  }
  LODWORD(this->m_rotFling) = v6;
  if ( !v6 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(aCouldnTCreateT, aDProjectPal3Co_6, 135),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }

}

// 0x005100D0
void CCBStageScene::_CCBStageScene()
{
  gbGeomNode *m_pPointer; // ecx
  gbGeomNode *m_pGeomNode; // ecx
  gbGeomNode *m_pCvd; // ecx
  gbGeomNode **m_pCorpse; // esi
  int v6; // edi

  sub_511630(this);
  ((gbRefObject *)LODWORD(this->m_vecFling))->Release();
  ((gbRefObject *)this->m_pFling)->Release();
  if ( this->m_nLoadPointer )
  {
    operator delete((void *)this->m_nLoadPointer);
    this->m_nLoadPointer = 0;
  }
  m_pPointer = this->m_pPointer;
  if ( m_pPointer )
  {
    (**(void ( ***)(gbGeomNode *, int))m_pPointer)(m_pPointer, 1);
    this->m_pPointer = 0;
  }
  m_pGeomNode = this->m_pGeomNode;
  if ( m_pGeomNode )
  {
    (**(void ( ***)(gbGeomNode *, int))m_pGeomNode)(m_pGeomNode, 1);
    this->m_pGeomNode = 0;
  }
  m_pCvd = this->m_pCvd;
  if ( m_pCvd )
  {
    (**(void ( ***)(gbGeomNode *, int))m_pCvd)(m_pCvd, 1);
    this->m_pCvd = 0;
  }
  m_pCorpse = this->m_pCorpse;
  v6 = 11;
  do
  {
    if ( *m_pCorpse )
    {
      // [VTBL_DISPATCH] (**(void ( ***)(gbGeomNode *, int))&(*m_pCorpse)->0)(*m_pCorpse, 1);
      *m_pCorpse = 0;
    }
    ++m_pCorpse;
    --v6;
  }
  while ( v6 );
}

// 0x00510180
void CCBStageScene::Reset()
{
  CCBStage *m_pStage; // ecx
  FightInfo *m_pFightInfo; // edi
  float v4; // eax
  int v5; // eax
  float z; // ecx
  gbGeomNode **m_pCorpse; // esi
  int v8; // edi



  m_pStage = this->m_pStage;
  m_pFightInfo = this->m_pStage->m_pCBSystem->m_pFightInfo;
  v4 = *(float *)&m_pFightInfo->eSceneFiveMagic;
  this->m_vecEnemyFiveLineupPos.z = v4;
  switch ( LODWORD(v4) )
  {
    case 1:
      this->m_nReset = 2134481581;
      break;
    case 2:
      this->m_nReset = 2145285425;
      break;
    case 3:
      this->m_nReset = 2136127083;
      break;
    case 4:
      this->m_nReset = 2145285565;
      break;
    case 5:
      this->m_nReset = 2144775770;
      break;
    default:
      break;
  }
  v5 = ((CCBRoleState *)m_pStage->m_pCBSystem->m_pRoleState)->CheckDeath(LODWORD(this->m_vecEnemyFiveLineupPos.z));
  this->m_vecFiveLineup[6].x = this->m_fLineupExtraX;
  this->m_vecFiveLineup[6].y = this->m_fLineupExtraY;
  this->m_vecFiveLineup[6].z = this->m_fLineupExtraZ;
  switch ( v5 )
  {
    case 1:
      this->m_vecFiveLineupPos.x = this->m_vecFiveLineupPos.x + 1.256636;
      this->m_vecFiveLineup[1].x = this->m_fLineupDefaultX;
      this->m_vecFiveLineup[1].y = this->m_fLineupDefaultY;
      this->m_vecFiveLineup[1].z = this->m_fLineupDefaultZ;
      LODWORD(this->m_vecFiveLineup[5].x) = this->m_nRender;
      this->m_vecFiveLineup[5].y = this->m_fLineupCamY;
      this->m_vecFiveLineup[5].z = this->m_fLineupCamZ;
      this->m_vecFiveLineup[3].x = this->m_fRender;
      this->m_vecFiveLineup[3].y = this->m_fLineupPrevY;
      this->m_vecFiveLineup[3].z = this->m_fLineupPrevZ;
      this->m_vecFiveLineup[4].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[4].y = this->m_vecInitFiveLineup[2].y;
      this->m_vecFiveLineup[4].z = this->m_vecInitFiveLineup[2].z;
      this->m_vecFiveLineup[2].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[2].y = this->m_vecInitFiveLineup[1].y;
      z = this->m_vecInitFiveLineup[1].z;
      goto LABEL_13;
    case 2:
      this->m_vecFiveLineupPos.x = this->m_vecFiveLineupPos.x + 2.513272;
      LODWORD(this->m_vecFiveLineup[1].x) = this->m_nRender;
      this->m_vecFiveLineup[1].y = this->m_fLineupCamY;
      this->m_vecFiveLineup[1].z = this->m_fLineupCamZ;
      this->m_vecFiveLineup[5].x = this->m_fRender;
      this->m_vecFiveLineup[5].y = this->m_fLineupPrevY;
      this->m_vecFiveLineup[5].z = this->m_fLineupPrevZ;
      this->m_vecFiveLineup[3].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[3].y = this->m_vecInitFiveLineup[2].y;
      this->m_vecFiveLineup[3].z = this->m_vecInitFiveLineup[2].z;
      this->m_vecFiveLineup[4].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[4].y = this->m_vecInitFiveLineup[1].y;
      this->m_vecFiveLineup[4].z = this->m_vecInitFiveLineup[1].z;
      this->m_vecFiveLineup[2].x = this->m_fLineupDefaultX;
      this->m_vecFiveLineup[2].y = this->m_fLineupDefaultY;
      z = this->m_fLineupDefaultZ;
      goto LABEL_13;
    case 3:
      this->m_vecFiveLineupPos.x = this->m_vecFiveLineupPos.x + 5.0265441;
      this->m_vecFiveLineup[1].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[1].y = this->m_vecInitFiveLineup[2].y;
      this->m_vecFiveLineup[1].z = this->m_vecInitFiveLineup[2].z;
      this->m_vecFiveLineup[5].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[5].y = this->m_vecInitFiveLineup[1].y;
      this->m_vecFiveLineup[5].z = this->m_vecInitFiveLineup[1].z;
      this->m_vecFiveLineup[3].x = this->m_fLineupDefaultX;
      this->m_vecFiveLineup[3].y = this->m_fLineupDefaultY;
      this->m_vecFiveLineup[3].z = this->m_fLineupDefaultZ;
      LODWORD(this->m_vecFiveLineup[4].x) = this->m_nRender;
      this->m_vecFiveLineup[4].y = this->m_fLineupCamY;
      this->m_vecFiveLineup[4].z = this->m_fLineupCamZ;
      this->m_vecFiveLineup[2].x = this->m_fRender;
      this->m_vecFiveLineup[2].y = this->m_fLineupPrevY;
      z = this->m_fLineupPrevZ;
      goto LABEL_13;
    case 4:
      this->m_vecFiveLineupPos.x = this->m_vecFiveLineupPos.x + 3.769908;
      this->m_vecFiveLineup[1].x = this->m_fRender;
      this->m_vecFiveLineup[1].y = this->m_fLineupPrevY;
      this->m_vecFiveLineup[1].z = this->m_fLineupPrevZ;
      this->m_vecFiveLineup[5].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[5].y = this->m_vecInitFiveLineup[2].y;
      this->m_vecFiveLineup[5].z = this->m_vecInitFiveLineup[2].z;
      this->m_vecFiveLineup[3].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[3].y = this->m_vecInitFiveLineup[1].y;
      this->m_vecFiveLineup[3].z = this->m_vecInitFiveLineup[1].z;
      this->m_vecFiveLineup[4].x = this->m_fLineupDefaultX;
      this->m_vecFiveLineup[4].y = this->m_fLineupDefaultY;
      this->m_vecFiveLineup[4].z = this->m_fLineupDefaultZ;
      LODWORD(this->m_vecFiveLineup[2].x) = this->m_nRender;
      this->m_vecFiveLineup[2].y = this->m_fLineupCamY;
      z = this->m_fLineupCamZ;
      goto LABEL_13;
    case 5:
      this->m_vecFiveLineup[1].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[1].y = this->m_vecInitFiveLineup[1].y;
      this->m_vecFiveLineup[1].z = this->m_vecInitFiveLineup[1].z;
      this->m_vecFiveLineup[5].x = this->m_fLineupDefaultX;
      this->m_vecFiveLineup[5].y = this->m_fLineupDefaultY;
      this->m_vecFiveLineup[5].z = this->m_fLineupDefaultZ;
      LODWORD(this->m_vecFiveLineup[3].x) = this->m_nRender;
      this->m_vecFiveLineup[3].y = this->m_fLineupCamY;
      this->m_vecFiveLineup[3].z = this->m_fLineupCamZ;
      this->m_vecFiveLineup[4].x = this->m_fRender;
      this->m_vecFiveLineup[4].y = this->m_fLineupPrevY;
      this->m_vecFiveLineup[4].z = this->m_fLineupPrevZ;
      this->m_vecFiveLineup[2].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[2].y = this->m_vecInitFiveLineup[2].y;
      z = this->m_vecInitFiveLineup[2].z;
LABEL_13:
      this->m_vecFiveLineup[2].z = z;
      break;
    default:
      break;
  }
  if ( strlen(m_pFightInfo->sSceneName) )
    this->LoadModel(m_pFightInfo->sSceneName);
  else
    this->LoadModel(&dir[32]);
  m_pCorpse = this->m_pCorpse;
  v8 = 11;
  do
  {
    if ( *m_pCorpse )
    {
      // [VTBL_DISPATCH] (**(void ( ***)(gbGeomNode *, int))&(*m_pCorpse)->0)(*m_pCorpse, 1);
      *m_pCorpse = 0;
    }
    ++m_pCorpse;
    --v8;
  }
  while ( v8 );
}

// 0x00510540
bool CCBStageScene::Create()
{
  gbGeomNode *v2; // eax
  gbGeomNode *v3; // esi
  gbGeomNode *v4; // ecx
  char pExceptionObject[1024]; // [esp+0xC] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x40C] [ebp-0x40C] BYREF
  int v8; // [esp+0x814] [ebp-0x4]

  v2 = (gbGeomNode *)operator new(0x118u);
  v3 = v2;
  v8 = 0;
  if ( v2 )
  {
    v4 = v3;
  }
  else
  {
    v4 = 0;
  }
  v8 = -1;
  this->m_pPointer = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], aDProjectPal3Co_6, 293),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return ((gbGeomNode *)v4)->LoadFromFile("ui\\combat\\pointer\\pointer.cvd", 0, 0);
}

// 0x00510610
void CCBStageScene::Destroy()
{
  CCBStageScene *v1; // esi
  int v2; // ebx
  gbGeomNode **m_pCorpse; // edi
  CCBRoleState *m_pRoleState; // ecx
  int v5; // eax
  int SkillNum; // ebp
  gbGeomNode *v7; // eax
  gbGeomNode *v8; // esi
  int nVal; // [esp+0x18] [ebp-0x918]
  char v11[256]; // [esp+0x24] [ebp-0x90C] BYREF
  char pExceptionObject[1024]; // [esp+0x124] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x524] [ebp-0x40C] BYREF
  int v14; // [esp+0x92C] [ebp-0x4]
v2 = 0;
  nVal = 0;
  m_pCorpse = this->m_pCorpse;
  do
  {
    if ( *m_pCorpse )
    {
      // [VTBL_DISPATCH] (**(void ( ***)(gbGeomNode *, int))&(*m_pCorpse)->0)(*m_pCorpse, 1);
      *m_pCorpse = 0;
    }
    m_pRoleState = this->m_pStage->m_pCBSystem->m_pRoleState;
    if ( m_pRoleState->m_Role[0].bMagicMastered[5][v2 + 4] )
    {
      v5 = *(_DWORD *)&((CCBRoleState *)m_pRoleState)->InitUI(nVal)->byMagicUseTime[4][5];
      if ( v5 )
      {
        SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v5);
        if ( SkillNum )
        {
          v7 = (gbGeomNode *)operator new(0x118u);
          v8 = v7;
          v14 = 0;
          if ( v7 )
          {
          }
          else
            v8 = 0;
          v14 = -1;
          *m_pCorpse = v8;
          if ( !v8 )
          {
            qmemcpy(
              pExceptionObject,
              ((Logger *)&ArgList)->FormatException(&path[164], aDProjectPal3Co_6, 330),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          sprintf(v11, "item\\%s\\%s.pol", (const char *)(SkillNum + 36), (const char *)(SkillNum + 36));
          if ( !((gbGeomNode *)*m_pCorpse)->LoadFromFile(v11, 0, 0) )
          {
            if ( *m_pCorpse )
            {
              // [VTBL_DISPATCH] (**(void ( ***)(gbGeomNode *, int))&(*m_pCorpse)->0)(*m_pCorpse, 1);
              *m_pCorpse = 0;
            }
          }
          sprintf(
            v11,
            "item\\%s\\%s%s.tga",
            (const char *)(SkillNum + 36),
            (const char *)(SkillNum + 36),
            (const char *)(SkillNum + 66));
          ((gbGeomNode *)*m_pCorpse)->ReplaceTexture(v11);
}
      }
    }
    v2 += 892;
    ++m_pCorpse;
    ++nVal;
  }
  while ( v2 < 9812 );
}

// 0x005107C0
bool CCBStageScene::Init()
{
  double m_fCurRotParam; // st7
  long double v3; // st6
  double v4; // st6
  double v5; // st5
  double v6; // st7
  double v7; // st6
  double v8; // st5
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double v15; // st7
  double v16; // st6
  double v17; // st5
  double v18; // st7
  double v19; // st6
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st6
  double v24; // st7
  double v25; // st6
  double z; // st7
  float y; // esi
  double v28; // st7
  double v29; // st6
  double v30; // st5
  double v31; // st7
  double v32; // st6
  double v33; // st5
  double v34; // st7
  double v35; // st6
  double v36; // st5
  double v37; // st7
  double v38; // st6
  double v39; // st5
  double v40; // st7
  double v41; // st7
  double v42; // st6
  double v43; // st7
  double v44; // st6
  double v45; // st7
  double v46; // st6
  float v47; // [esp+0x4] [ebp-0x18]
  float v48; // [esp+0x4] [ebp-0x18]
  float v49; // [esp+0x8] [ebp-0x14]
  float v50; // [esp+0x8] [ebp-0x14]
  float m_fCurAxisZ; // [esp+0xC] [ebp-0x10]
  float m_fCurAxisX; // [esp+0x10] [ebp-0xC]
  float v53; // [esp+0x10] [ebp-0xC]
  float v54; // [esp+0x14] [ebp-0x8]
  float v55; // [esp+0x18] [ebp-0x4]
  float v56; // [esp+0x18] [ebp-0x4]

  m_fCurRotParam = this->m_fCurRotParam;
  m_fCurAxisX = this->m_fCurAxisX;
  m_fCurAxisZ = this->m_fCurAxisZ;
  v47 = sin(this->m_vecFiveLineupPos.x);
  v3 = cos(this->m_vecFiveLineupPos.x);
  this->m_nCamState = 0;
  v49 = v3;
  v54 = m_fCurRotParam * 0.5;
  v4 = m_fCurAxisX - v54;
  *(float *)&this->m_nInit = v4;
  v5 = m_fCurAxisZ - v54;
  this->m_fCamPosX = v5;
  this->m_fInit = 0.0;
  v55 = v54 + m_fCurAxisX;
  this->m_fCamPosZ = v55;
  this->m_fCamTargX = v5;
  this->m_fCamTargZ = v55;
  this->m_fInitBlend = 0.0;
  v56 = v54 + m_fCurAxisZ;
  *(float *)&this->m_FiveLineupCenterQuad = v56;
  this->m_nBlendState = 0;
  this->m_fBlendTime = v4;
  this->m_fBlendSpeed = v56;
  this->m_fBlendA = 0.0;
  this->m_fDirSinA = -m_fCurRotParam;
  *(float *)&this->m_bShowFling = -m_fCurRotParam;
  this->m_pFiveLineupTexture = 0;
  *(float *)&this->m_pFiveLineupEffect = m_fCurRotParam;
  *(float *)&this->m_pFiveLineupTextureArray = -m_fCurRotParam;
  this->m_pFiveLineupCenterTextureArray = 0;
  *(float *)&this->m_pFiveLineupCenterTexture = m_fCurRotParam;
  *(float *)&this->m_FiveLineupQuad = m_fCurRotParam;
  this->m_fBlendB = 0.0;
  this->m_fDirSinB = -m_fCurRotParam;
  this->m_fDirCosB = m_fCurRotParam;
  v6 = v49 * *(float *)&this->m_bShowFling - v47 * this->m_fDirSinA;
  v7 = v47 * *(float *)&this->m_bShowFling;
  v8 = v49 * this->m_fDirSinA;
  this->m_fBlendA = 0.0;
  this->m_fDirSinA = v7 + v8;
  *(float *)&this->m_bShowFling = v6;
  v9 = v49 * *(float *)&this->m_pFiveLineupTextureArray - v47 * *(float *)&this->m_pFiveLineupEffect;
  v10 = v47 * *(float *)&this->m_pFiveLineupTextureArray;
  v11 = v49 * *(float *)&this->m_pFiveLineupEffect;
  this->m_pFiveLineupTexture = 0;
  *(float *)&this->m_pFiveLineupEffect = v10 + v11;
  *(float *)&this->m_pFiveLineupTextureArray = v9;
  v12 = v49 * *(float *)&this->m_FiveLineupQuad - v47 * *(float *)&this->m_pFiveLineupCenterTexture;
  v13 = v49 * *(float *)&this->m_pFiveLineupCenterTexture;
  v14 = v47 * *(float *)&this->m_FiveLineupQuad;
  this->m_pFiveLineupCenterTextureArray = 0;
  *(float *)&this->m_pFiveLineupCenterTexture = v13 + v14;
  *(float *)&this->m_FiveLineupQuad = v12;
  v15 = v49 * this->m_fDirCosB - v47 * this->m_fDirSinB;
  v16 = v47 * this->m_fDirCosB;
  v17 = v49 * this->m_fDirSinB;
  this->m_fBlendB = 0.0;
  this->m_fDirSinB = v16 + v17;
  this->m_fDirCosB = v15;
  v18 = m_fCurAxisZ + *(float *)&this->m_bShowFling;
  v19 = m_fCurAxisX + this->m_fDirSinA;
  this->m_fBlendA = 0.5;
  this->m_fDirSinA = v19;
  *(float *)&this->m_bShowFling = v18;
  v20 = m_fCurAxisZ + *(float *)&this->m_pFiveLineupTextureArray;
  v21 = m_fCurAxisX + *(float *)&this->m_pFiveLineupEffect;
  this->m_pFiveLineupTexture = (gbTexture *)1056964608;
  *(float *)&this->m_pFiveLineupEffect = v21;
  *(float *)&this->m_pFiveLineupTextureArray = v20;
  v22 = m_fCurAxisZ + *(float *)&this->m_FiveLineupQuad;
  v23 = m_fCurAxisX + *(float *)&this->m_pFiveLineupCenterTexture;
  this->m_pFiveLineupCenterTextureArray = (gbTextureArray *)1056964608;
  *(float *)&this->m_pFiveLineupCenterTexture = v23;
  *(float *)&this->m_FiveLineupQuad = v22;
  v24 = m_fCurAxisZ + this->m_fDirCosB;
  v25 = m_fCurAxisX + this->m_fDirSinB;
  this->m_fBlendB = 0.5;
  this->m_fDirSinB = v25;
  this->m_fDirCosB = v24;
  z = this->m_vecFiveLineupInitPos.z;
  v48 = sin(this->m_fFiveLineupRadius);
  v50 = cos(this->m_fFiveLineupRadius);
  v53 = this->m_vecFiveLineupPos.z;
  y = this->m_vecFiveLineupInitPos.y;
  this->m_fDirSinC = -z;
  this->m_fDirCosC = -z;
  this->m_fBlendC = 0.0;
  this->m_fBlendD = 0.0;
  this->m_fDirSinD = z;
  this->m_fDirCosD = -z;
  this->m_fBlendE = 0.0;
  this->m_fDirSinE = z;
  *(float *)&this->m_EnemyFiveLineupQuad = z;
  this->m_fBlendF = 0.0;
  this->m_fDirSinF = -z;
  this->m_fDirCosF = z;
  v28 = v50 * this->m_fDirCosC - v48 * this->m_fDirSinC;
  v29 = v50 * this->m_fDirSinC;
  v30 = v48 * this->m_fDirCosC;
  this->m_fBlendC = 0.0;
  this->m_fDirSinC = v29 + v30;
  this->m_fDirCosC = v28;
  v31 = v50 * this->m_fDirCosD - v48 * this->m_fDirSinD;
  v32 = v48 * this->m_fDirCosD;
  v33 = v50 * this->m_fDirSinD;
  this->m_fBlendD = 0.0;
  this->m_fDirSinD = v32 + v33;
  this->m_fDirCosD = v31;
  v34 = v50 * *(float *)&this->m_EnemyFiveLineupQuad - v48 * this->m_fDirSinE;
  v35 = v50 * this->m_fDirSinE;
  v36 = v48 * *(float *)&this->m_EnemyFiveLineupQuad;
  this->m_fBlendE = 0.0;
  this->m_fDirSinE = v35 + v36;
  *(float *)&this->m_EnemyFiveLineupQuad = v34;
  v37 = v50 * this->m_fDirCosF - v48 * this->m_fDirSinF;
  v38 = v48 * this->m_fDirCosF;
  v39 = v50 * this->m_fDirSinF;
  this->m_fBlendF = 0.0;
  this->m_fDirSinF = v38 + v39;
  this->m_fDirCosF = v37;
  v40 = y + this->m_fDirCosC;
  this->m_fDirSinC = v53 + this->m_fDirSinC;
  this->m_fBlendC = 0.5;
  this->m_fDirCosC = v40;
  v41 = y + this->m_fDirCosD;
  v42 = v53 + this->m_fDirSinD;
  this->m_fBlendD = 0.5;
  this->m_fDirSinD = v42;
  this->m_fDirCosD = v41;
  v43 = y + *(float *)&this->m_EnemyFiveLineupQuad;
  v44 = v53 + this->m_fDirSinE;
  this->m_fBlendE = 0.5;
  this->m_fDirSinE = v44;
  *(float *)&this->m_EnemyFiveLineupQuad = v43;
  v45 = y + this->m_fDirCosF;
  v46 = v53 + this->m_fDirSinF;
  this->m_fBlendF = 0.5;
  this->m_fDirSinF = v46;
  this->m_fDirCosF = v45;
  return 0;
}

// 0x00510C80
void CCBStageScene::SetBattleFieldAttr()
{
  gbGeomNode *m_pPointer; // ecx

  m_pPointer = this->m_pPointer;
  if ( m_pPointer )
    (*(void ( **)(gbGeomNode *))(*(_DWORD *)m_pPointer + 20))(m_pPointer);
}

// 0x00510CA0
void CCBStageScene::GetBattleFieldSubdueAttr(gbMatrixStack *pMatrixStack)
{
  int v3; // ebp
  gbGeomNode *m_pGeomNode; // ecx
  gbVisNode *m_pLights; // ecx
  gbGeomNode **m_pCorpse; // ebx
  long double v8; // st7
  float v9; // [esp+0x18] [ebp-0x24]
  float v10; // [esp+0x18] [ebp-0x24]
  float v11; // [esp+0x30] [ebp-0xC]
  float m_fCurAxisY; // [esp+0x34] [ebp-0x8]
  float v13; // [esp+0x38] [ebp-0x4]
  gbMatrixStack *pMatrixStacka; // [esp+0x40] [ebp+0x4]

  v3 = 0;
  m_pGeomNode = this->m_pGeomNode;
  if ( m_pGeomNode && this->m_bLoaded )
  {
    (*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)m_pGeomNode + 16))(m_pGeomNode, 0);
    m_pLights = this->m_pLights;
    if ( m_pLights )
      (*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)m_pLights + 16))(m_pLights, 0);
    if ( LOBYTE(this->m_vecEnemyFiveLineupPos.x) && this->m_pPointer )
    {
      ((gbMatrixStack *)pMatrixStack)->Push();
      v9 = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 10.0) * 5.0 + this->m_fFiveLineupRoll + 6.0;
      ((gbMatrixStack *)pMatrixStack)->Translate(this->m_fFiveLineupInitRadius,   v9,   this->m_fFiveLineupInitRoll);
      (*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)this->m_pPointer + 16))(this->m_pPointer, 0);
      ((gbMatrixStack *)pMatrixStack)->Pop();
    }
    pMatrixStacka = 0;
    m_fCurAxisY = this->m_fCurAxisY;
    m_pCorpse = this->m_pCorpse;
    do
    {
      if ( v3 >= 5 )
      {
        if ( *m_pCorpse )
        {
          v8 = (double)(int)pMatrixStacka * 0.017453292;
          v11 = sin(v8) * 20.0 + this->m_fCurAxisX;
          v13 = cos(v8) * 20.0 + this->m_fCurAxisZ;
          ((gbMatrixStack *)pMatrixStack)->Push();
          v10 = m_fCurAxisY + 2.0;
          ((gbMatrixStack *)pMatrixStack)->Translate(v11,   v10,   v13);
          // [VTBL_DISPATCH] (*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)&(*m_pCorpse)->0 + 16))(*m_pCorpse, 0);
          ((gbMatrixStack *)pMatrixStack)->Pop();
          pMatrixStacka = (gbMatrixStack *)((char *)pMatrixStacka + 60);
        }
      }
      ++v3;
      ++m_pCorpse;
    }
    while ( v3 < 11 );
  }
}

// 0x00510E00
void CCBStageScene::GetBFASubdueFM()
{
  gbRenderEffect *v1; // esi
  _DWORD *v2; // edi
  int v3; // ebp
  gbDynVertBuf *DynVertBuf; // eax
  gbDynVertBuf *v5; // edi
  unsigned int v6; // ecx
  unsigned int v7; // ecx
  gbColorQuad v8; // [esp+0x10] [ebp-0x3C] BYREF
  _DWORD *v9; // [esp+0x14] [ebp-0x38]
  int v10; // [esp+0x18] [ebp-0x34]
  gbRenderEffect *v11; // [esp+0x1C] [ebp-0x30]
  struct gbColorQuad v12; // [esp+0x20] [ebp-0x2C]
  gbVec3D *v13; // [esp+0x24] [ebp-0x28]
  int v14; // [esp+0x28] [ebp-0x24]
  gbRenderEffect *v15; // [esp+0x2C] [ebp-0x20]
  struct gbColorQuad v16; // [esp+0x30] [ebp-0x1C] BYREF
  _DWORD v17[3]; // [esp+0x34] [ebp-0x18] BYREF
  int v18; // [esp+0x40] [ebp-0xC]
  int v19; // [esp+0x44] [ebp-0x8]
  int v20; // [esp+0x48] [ebp-0x4]

  if ( gfxMgr && BYTE1(this->m_vecEnemyFiveLineupPos.x) )
  {
    v1 = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewTrivalEffect(3);
    HIBYTE(v16.Color) = 80;
    v2 = v17;
    v3 = 2;
    do
    {
      v2 += 3;
      --v3;
    }
    while ( v3 );
    memset(v17, 0, sizeof(v17));
    DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(5u);
    v11 = v1;
    v10 = 2;
    v9 = v17;
    v8.Color = (unsigned int)v17;
    v5 = DynVertBuf;
    LOWORD(v16.Color) = 255;
    BYTE2(v16.Color) = 0;
    v19 = 0;
    v18 = 0;
    v20 = 1176256512;
    ((gbDynVertBuf *)v5)->RenderLineStrip(v12, v13, v14, v15);
    v11 = v1;
    v10 = 2;
    v9 = v17;
    v8.Color = v6;
    LOBYTE(v16.Color) = 0;
    *(_WORD *)((char *)&v16.Color + 1) = -256;
    v20 = 0;
    v19 = 0;
    v18 = 1176256512;
    ((gbDynVertBuf *)v5)->RenderLineStrip(v12, v13, v14, v15);
    v11 = v1;
    v10 = 2;
    v9 = v17;
    v8.Color = v7;
    LOWORD(v16.Color) = -256;
    BYTE2(v16.Color) = 0;
    v20 = 0;
    v18 = 0;
    v19 = 1176256512;
    ((gbDynVertBuf *)v5)->RenderLineStrip(v12, v13, v14, v15);
// [VFTABLE] ((gbRefObject *)&v1->__vftable)->Release();
  }
}

// 0x00510F50
bool CCBStageScene::IsSameBattleFieldAttr()
{
  bool result; // al
  int v3; // esi
  int v4; // edi
  CCBRoleState *m_pRoleState; // ebp
  tagRoleState *inited; // eax
  _BYTE *v7; // [esp+0xC] [ebp-0xC]
  float fVal2; // [esp+0x10] [ebp-0x8] BYREF
  float fVal; // [esp+0x14] [ebp-0x4] BYREF

  result = (char)gfxMgr;
  fVal = 0.0;
  fVal2 = 0.0;
  if ( gfxMgr )
  {
    result = BYTE2(this->m_vecEnemyFiveLineupPos.x);
    if ( result )
    {
      v3 = 0;
      v4 = 24;
      m_pRoleState = this->m_pStage->m_pCBSystem->m_pRoleState;
      v7 = &m_pRoleState->m_Role[0].bMagicMastered[5][4];
      do
      {
        result = (char)v7;
        if ( *v7 )
        {
          inited = ((CCBRoleState *)m_pRoleState)->InitUI(v3);
          sprintf((char *const)&g_CCBStageSceneData, "%d(%s)", v3, inited->sModel);
          ((gbCamera *)&this->m_pStage->m_pCam->OrthoSize)->PointWorldToScr((gbVec3D *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + v4))->m_Thread[73].fp[2], &fVal, &fVal2);
          result = ((CCBStage *)this->m_pStage->m_TempStorageNGH)->UpdateTurnFlags((const char *)&g_CCBStageSceneData, fVal, fVal2, 16.0);
        }
        v4 += 4;
        ++v3;
        v7 += 892;
      }
      while ( v4 < 68 );
    }
  }
  return result;
}

// 0x00511030
void CCBStageScene::LoadPointer(char pData)
{
  gbTextureArray *m_nLoadPointer; // ecx
  gbGeomNode *m_pFling; // edx

  ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
  m_nLoadPointer = (gbTextureArray *)this->m_nLoadPointer;
  m_pFling = this->m_pFling;
  this->m_nPointerIndex2 = -1;
  this->m_nPointerIndex1 = -1;
  this->m_bLoadPointer = -1;
  this->m_nPointerData = pData;
  HIBYTE(this->m_nReset) = pData;
  ((gbDynVertBuf *)&this->m_fDirSinA)->RenderGeomQuad(1, (gbRenderEffect *)m_pFling, m_nLoadPointer);
  ((gbDynVertBuf *)&this->m_nInit)->RenderGeomQuad(1, (gbRenderEffect *)this->m_pFling, (gbTextureArray *)LODWORD(this->m_rotFling));
}

// 0x00511110
bool CCBStageScene::LoadFlingNode()
{
  CCBStage *m_pStage; // eax
  double v3; // st7
  double v4; // st6
  double v5; // st5
  float v7; // [esp+0x0] [ebp-0x74]
  float v8; // [esp+0x4] [ebp-0x70]
  Actor *pPos; // [esp+0x8] [ebp-0x6C] BYREF
  gbVec3D v10; // [esp+0xC] [ebp-0x68] BYREF
  struct gbVec3D v11; // [esp+0x20] [ebp-0x54] BYREF
  struct gbVec3D v12; // [esp+0x2C] [ebp-0x48] BYREF
  float pTarget[6]; // [esp+0x38] [ebp-0x3C] BYREF
  gbRay v14; // [esp+0x50] [ebp-0x24] BYREF
  gbVec3D v15; // [esp+0x68] [ebp-0xC] BYREF

  pTarget[1] = 1.0;
  pTarget[0] = 0.0;
  pTarget[2] = 0.0;
  v12.y = 0.0;
  v12.x = 1.0;
  v12.z = 1.0;
  memset(&v11, 0, sizeof(v11));
  memset(&v14.Direction, 0, sizeof(v14.Direction));
  m_pStage = this->m_pStage;
  pPos = this->m_pStage->m_WPXVariance;
  LODWORD(v10.x) = m_pStage->m_pDisplayChain;
  v14 = *(gbRay *)((CameraCtrl *)m_pStage->m_pCam)->GetViewTarget(pTarget, (float *)&pPos);
  v3 = ((gbRay *)&v14)->IntersectPlane(v12, v11);
  v7 = v14.Origin.y * v3;
  v8 = v14.Origin.z * v3;
  v12.y = v7 + pTarget[4];
  v12.z = pTarget[5] + v8;
  v4 = this->m_fCurAxisX - v12.y;
  v12.z = this->m_fCurAxisY - v12.z;
  v5 = this->m_fCurAxisZ - (v3 * v14.Direction.x + v14.Origin.x);
  v10.y = v12.z;
  pTarget[0] = v5;
  v10.x = v4;
  v10.z = pTarget[0];
  return ((gbVec3D *)&v10)->Length() < 30.0;
}

// 0x005112B0
void CCBStageScene::SetFlingRotX()
{
  float y; // edx
  float *p_m_fInitAxisX; // eax
  float *p_m_fCurAxisX; // ecx

  y = this->m_vecFiveLineupPos.y;
  this->m_fCurRotParam = this->m_fInitRotParam;
  p_m_fInitAxisX = &this->m_fInitAxisX;
  this->m_vecFiveLineupPos.x = y;
  p_m_fCurAxisX = &this->m_fCurAxisX;
  *p_m_fCurAxisX = *p_m_fInitAxisX;
  p_m_fCurAxisX[1] = p_m_fInitAxisX[1];
  p_m_fCurAxisX[2] = p_m_fInitAxisX[2];
}

// 0x005112F0
int * CCBStageScene::SetFlingRotY()
{
  int *result; // eax
  int v2; // ecx

  result = (int *)&this->m_vecFiveLineup[0].y;
  v2 = 7;
  do
  {
    *(result - 1) = result[20];
    *result = result[21];
    result[1] = result[22];
    result[41] = result[62];
    result[42] = result[63];
    result[43] = result[64];
    result += 3;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x00511340
bool CCBStageScene::LoadModel(const char *pszName)
{
  gbGeomNode *v4; // eax
  gbGeomNode *v5; // esi
  gbGeomNode *v6; // ecx
  gbGeomNode *v7; // eax
  gbGeomNode *v8; // esi
  gbGeomNode *v9; // ecx
  CCBStageScene *v10; // esi
  int v12; // [esp+0x14] [ebp-0x920]
  OpenBaseFile v13; // [esp+0x18] [ebp-0x91C] BYREF
  char *m_sLastScene; // [esp+0x1C] [ebp-0x918]
  gbGeomNode *v15; // [esp+0x20] [ebp-0x914]
  char Buffer[260]; // [esp+0x24] [ebp-0x910] BYREF
  char pExceptionObject[1024]; // [esp+0x128] [ebp-0x80C] BYREF
  char ArgList[1024]; // [esp+0x528] [ebp-0x40C] BYREF
  int v19; // [esp+0x930] [ebp-0x4]

  if ( !pszName )
    return 0;
  m_sLastScene = this->m_sLastScene;
  if ( strcmp(this->m_sLastScene, pszName) )
  {
    sub_511630(this);
    strcpy(Buffer, "cbscene\\");
    strcat(Buffer, pszName);
    v19 = 0;
    sprintf(Buffer, "cbscene\\%s\\%s.pol", pszName, pszName);
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = v4;
    LOBYTE(v19) = 1;
    if ( v4 )
    {
      v6 = v5;
    }
    else
    {
      v6 = 0;
    }
    LOBYTE(v19) = 0;
    this->m_pGeomNode = v6;
    if ( !v6 )
    {
      qmemcpy(
        pExceptionObject,
        ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_6, 772),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    v12 = ((gbGeomNode *)v6)->LoadFromFile(Buffer, 0, 0);
    sprintf(Buffer, "cbscene\\%s\\%s.cvd", pszName, pszName);
    if ( ((gbVFileSystem *)g_pVFileSys)->FileExistNum(Buffer) )
    {
      v7 = (gbGeomNode *)operator new(0x118u);
      v8 = v7;
      v15 = v7;
      LOBYTE(v19) = 2;
      if ( v7 )
      {
        v9 = v8;
      }
      else
      {
        v9 = 0;
      }
LOBYTE(v19) = 0;
      this->m_pCvd = v9;
      if ( !v9 )
      {
        qmemcpy(
          pExceptionObject,
          ((Logger *)ArgList)->FormatException(&path[164], aDProjectPal3Co_6, 783),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      ((gbGeomNode *)v9)->LoadFromFile(Buffer, 0, 0);
    }
    else
    {
}
    sprintf(Buffer, "cbscene\\%s\\%s.lgt", pszName, pszName);
    if ( ((gbVFileSystem *)g_pVFileSys)->FileExistNum(Buffer) )
      this->m_pLights = gbLoadLightFile(Buffer);
    if ( v12 == 1 )
      this->m_bLoaded = 1;
    v19 = -1;
    strcpy(m_sLastScene, pszName);
  }
  return 1;
}

// 0x00511690
char CCBStageScene::Update()
{
  int v3; // edi
  int i; // esi
  CIniFile v5; // [esp+0x18] [ebp-0x14] BYREF
  int v6; // [esp+0x28] [ebp-0x4]

  if ( (g_dwGameFlags & 2) != 0 )
    return 1;
  v3 = 0;
  v6 = 0;
  ((CIniFile *)&v5)->OpenFileWrite("datascript\\combat.ini");
  ((CIniFile *)&v5)->WriteSection("RolePos");
  for ( i = 24; i < 68; i += 4 )
  {
    sprintf(byte_17ABE00, "Role%d-x", v3);
    ((CIniFile *)&v5)->WriteLine(byte_17ABE00, *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[73].fp[2]);
    sprintf(byte_17ABE00, "Role%d-z", v3);
    ((CIniFile *)&v5)->WriteLine(byte_17ABE00, *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[73].dwID);
    ++v3;
  }
  v6 = -1;
  return 1;
}

// 0x00511790
void CCBStageScene::Render()
{
  int v2; // ebp
  int v3; // edi
  gbVec3D *v4; // eax
  float v5; // edx
  float v6; // ecx
  float v7; // edx
  float v8; // eax
  float v9; // eax
  double m_fRender; // st7
  float m_fLineupPrevZ; // edx
  float m_fLineupCamY; // ecx
  float v13; // eax
  float v14; // ecx
  CIniFile v15; // [esp+0x2C] [ebp-0x20] BYREF
  float v16; // [esp+0x34] [ebp-0x18] BYREF
  float m_fLineupPrevY; // [esp+0x38] [ebp-0x14]
  float v18; // [esp+0x3C] [ebp-0x10] BYREF
  int v19; // [esp+0x48] [ebp-0x4]

  v16 = 0.0;
  m_fLineupPrevY = 0.0;
  v18 = 0.0;
  v2 = 0;
  v3 = 0;
  v19 = 0;
  ((CIniFile *)&v15)->OpenFileRead("datascript\\combat.ini");
  do
  {
    ((CIniFile *)&v15)->ReadStart();
    ((CIniFile *)&v15)->ReadSection("RolePos");
    sprintf(byte_17ABD00, "Role%d-x", v2);
    ((CIniFile *)&v15)->ReadLine(byte_17ABD00, &v16);
    m_fLineupPrevY = 0.0;
    sprintf(byte_17ABD00, "Role%d-z", v2);
    ((CIniFile *)&v15)->ReadLine(byte_17ABD00, &v18);
    if ( ++v3 >= 6 )
      v4 = &this->m_vecEnemyLineup[v3 + 2];
    else
      v4 = &this->m_vecInitFiveLineup[v3];
    v5 = m_fLineupPrevY;
    v4->x = v16;
    v6 = v18;
    v4->y = v5;
    v4->z = v6;
    if ( v3 == 6 )
    {
      ((CIniFile *)&v15)->ReadStart();
      ((CIniFile *)&v15)->ReadSection(aFivelineup);
      ((CIniFile *)&v15)->ReadLine("x", &v16);
      ((CIniFile *)&v15)->ReadLine("z", &v18);
      v7 = m_fLineupPrevY;
      v8 = v18;
      this->m_fLineupExtraX = v16;
      this->m_fLineupExtraY = v7;
      this->m_fLineupExtraZ = v8;
    }
    ++v2;
  }
  while ( v2 < 11 );
  v9 = *(float *)&this->m_nRender;
  m_fRender = this->m_fRender;
  m_fLineupPrevZ = this->m_fLineupPrevZ;
  m_fLineupPrevY = this->m_fLineupPrevY;
  v16 = m_fRender;
  this->m_fRender = v9;
  m_fLineupCamY = this->m_fLineupCamY;
  v13 = m_fLineupPrevY;
  v18 = m_fLineupPrevZ;
  this->m_fLineupPrevY = m_fLineupCamY;
  v14 = v18;
  this->m_fLineupPrevZ = this->m_fLineupCamZ;
  *(float *)&this->m_nRender = m_fRender;
  this->m_fLineupCamZ = v14;
  this->m_fLineupCamY = v13;
  v19 = -1;
}

// 0x00511970
void CCBStageScene::ShowAxis()
{
  float m_fInitAxisX; // eax
  float m_fInitAxisY; // ecx
  float m_fInitAxisZ; // eax
  CIniFile v5; // [esp+0x5C] [ebp-0x14] BYREF
  int v6; // [esp+0x6C] [ebp-0x4]

  v6 = 0;
  ((CIniFile *)&v5)->OpenFileRead("datascript\\combat.ini");
  ((CIniFile *)&v5)->ReadSection(aFivelineup);
  ((CIniFile *)&v5)->ReadLine("x", &this->m_fInitAxisX);
  ((CIniFile *)&v5)->ReadLine("y", &this->m_fInitAxisY);
  ((CIniFile *)&v5)->ReadLine("z", &this->m_fInitAxisZ);
  ((CIniFile *)&v5)->ReadLine("radius", &this->m_fInitRotParam);
  this->m_fCurRotParam = this->m_fInitRotParam;
  ((CIniFile *)&v5)->ReadLine("roll", &this->m_vecFiveLineupPos.y);
  m_fInitAxisX = this->m_fInitAxisX;
  this->m_vecFiveLineupPos.x = this->m_vecFiveLineupPos.y;
  m_fInitAxisY = this->m_fInitAxisY;
  this->m_fCurAxisX = m_fInitAxisX;
  m_fInitAxisZ = this->m_fInitAxisZ;
  this->m_fCurAxisY = m_fInitAxisY;
  this->m_fCurAxisZ = m_fInitAxisZ;
  ((CIniFile *)&v5)->ReadSection(aEnemyfivelineu);
  ((CIniFile *)&v5)->ReadLine("x", &this->m_vecFiveLineupPos.z);
  ((CIniFile *)&v5)->ReadLine("y", &this->m_vecFiveLineupInitPos.x);
  ((CIniFile *)&v5)->ReadLine("z", &this->m_vecFiveLineupInitPos.y);
  ((CIniFile *)&v5)->ReadLine("radius", &this->m_vecFiveLineupInitPos.z);
  ((CIniFile *)&v5)->ReadLine("roll", &this->m_fFiveLineupRadius);
  v6 = -1;
}

// 0x00511AE0
void CCBStageScene::ShowRoleIndex()
{
  CIniFile v2; // [esp+0x30] [ebp-0x14] BYREF
  int v3; // [esp+0x40] [ebp-0x4]

  if ( (g_dwGameFlags & 2) == 0 )
  {
    v3 = 0;
    ((CIniFile *)&v2)->OpenFileWrite("datascript\\combat.ini");
    ((CIniFile *)&v2)->WriteSection(aFivelineup);
    ((CIniFile *)&v2)->WriteLine("x", this->m_fCurAxisX);
    ((CIniFile *)&v2)->WriteLine("y", this->m_fCurAxisY);
    ((CIniFile *)&v2)->WriteLine("z", this->m_fCurAxisZ);
    ((CIniFile *)&v2)->WriteLine("radius", this->m_fCurRotParam);
    ((CIniFile *)&v2)->WriteLine("roll", this->m_vecFiveLineupPos.x);
    v3 = -1;
  }
}

// 0x00511C00
// attributes: thunk
void CCBStageScene::ShowEnemyFiveLineupEx(unsigned __int8 byAlpha)
{

}

// 0x00511C10
bool CCBStageScene::IsFiveLineupUnderMouse()
{
  *((_DWORD *)&g_CCBStageSceneData + 411) = 1094713344;
  return 0;
}

// 0x00511C20
// attributes: thunk
void CCBStageScene::ResetFiveLineupToInit()
{

}

// 0x00511C30
void CCBStageScene::ResetRolePosToInit()
{
  *((float *)&g_CCBStageSceneData + 410) = 12.0 + 12.0;
}

// 0x00511C40
// attributes: thunk
bool CCBStageScene::LoadScene(const char *const pFilename)
{
  bool result; // al

  return result;
}

// 0x00511C50
void CCBStageScene::DestroyScene()
{
  *(_QWORD *)(&g_CCBStageSceneData + 1652) = 0x13A00000077LL;
  *(_QWORD *)(&g_CCBStageSceneData + 1660) = 0x2C3000001FELL;
}

// 0x00511C90
// attributes: thunk
bool CCBStageScene::SaveRolePos()
{
  return compiler_init_00511CA0(this);
}

// 0x00511CE0
// attributes: thunk
bool CCBStageScene::LoadFiveLineupData()
{
  return this->SaveFiveLineupDate();
}

// 0x00511CF0
bool CCBStageScene::SaveFiveLineupDate()
{
  *(_QWORD *)(&g_CCBStageSceneData + 1684) = 0x14300000080LL;
  *(_QWORD *)(&g_CCBStageSceneData + 1692) = 0x2CC00000207LL;
  return -52;
}

// 0x0052B1E0
int * CCBStageScene::InitCameraPositions()
{
  float *p_m_fCamTargZ; // edi
  int v3; // ebx

  p_m_fCamTargZ = &this->m_fCamTargZ;
  v3 = 5;
  do
  {
    p_m_fCamTargZ += 3;
    --v3;
  }
  while ( v3 );
  ((ObjectCamera *)&this->m_fDirSinF)->Update();
  *(_DWORD *)&this->m_eBFAForce = 0;
  *((_DWORD *)this + 253) = 0;
  *((_DWORD *)this + 254) = 0;
  *((_DWORD *)this + 255) = 0;
  *((_DWORD *)this + 256) = 0;
  *((_DWORD *)this + 257) = 0;
  *((_DWORD *)this + 258) = 0;
  *((_DWORD *)this + 259) = 0;
  *((_DWORD *)this + 260) = 0;

  return (int *)this;
}

// 0x0052B2A0
void CCBStageScene::CleanupCamera()
{
  float y; // ecx
  float v3; // edi
  float x; // ecx

  y = this->m_vecFiveLineup[0].y;
  if ( y != 0.0 )
  {
    ((ObjectCamera *)LODWORD(y))->Destroy();
    v3 = this->m_vecFiveLineup[0].y;
    if ( v3 != 0.0 )
    {
      ((ObjectCamera *)LODWORD(this->m_vecFiveLineup[0].y))->GetCameraDirect();
      operator delete((void *)LODWORD(v3));
    }
    this->m_vecFiveLineup[0].y = 0.0;
  }
  x = this->m_vecFiveLineup[0].x;
  if ( x != 0.0 )
  {
    (**(void ( ***)(float, int))LODWORD(x))(COERCE_FLOAT(LODWORD(x)), 1);
    this->m_vecFiveLineup[0].x = 0.0;
  }
}

// 0x0052B350
int CCBStageScene::SetCameraDefaults()
{
  *((_DWORD *)this + 253) = 1120403456;
  *(_DWORD *)&this->m_eBFAForce = 0;
  *((_DWORD *)this + 254) = 1133903872;
  *((_DWORD *)this + 255) = 0;
  *((_DWORD *)this + 256) = -1032847360;
  *((_DWORD *)this + 257) = 0;
  *((_DWORD *)this + 258) = 0;
  *((_DWORD *)this + 259) = 1065353216;
  *((_DWORD *)this + 260) = 0;
  this->m_vecFiveLineup[0].x = 0.0;
  this->m_vecFiveLineup[0].y = 0.0;
  this->m_pStage = 0;
  this->m_pUtil = 0;
  return 0;
}

// 0x0052B3B0
char CCBStageScene::CreateCamera()
{
  ObjectCamera *v2; // eax
  int v3; // ebp
  float *v4; // eax
  float *p_y; // edi
  UIDialog *v6; // eax
  int *v7; // eax
  gbVisNode *v8; // eax
  float v9; // edi
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v12; // edi
  UICoverFrm *v13; // eax
  CUtil *v14; // eax
  CScreenMode *v15; // eax
  gbVec3D v17; // [esp-0x10] [ebp-0x178]
  const void *v18; // [esp-0x8] [ebp-0x170]
  float *p_m_fCamTargZ; // [esp+0x10] [ebp-0x158]
  char *pszName; // [esp+0x20] [ebp-0x148]
  float *p_m_fBlendD; // [esp+0x24] [ebp-0x144]
  _DWORD v22[2]; // [esp+0x28] [ebp-0x140] BYREF
  __int16 v23; // [esp+0x30] [ebp-0x138]
  void *v24; // [esp+0x32] [ebp-0x136]
  int v25; // [esp+0x36] [ebp-0x132]
  __int16 v26; // [esp+0x3A] [ebp-0x12E]
  void *v27; // [esp+0x3C] [ebp-0x12C]
  int v28; // [esp+0x40] [ebp-0x128]
  __int16 v29; // [esp+0x44] [ebp-0x124]
  void *v30; // [esp+0x46] [ebp-0x122]
  int v31; // [esp+0x4A] [ebp-0x11E]
  __int16 v32; // [esp+0x4E] [ebp-0x11A]
  void *v33; // [esp+0x50] [ebp-0x118]
  int v34; // [esp+0x54] [ebp-0x114]
  __int16 v35; // [esp+0x58] [ebp-0x110]
  char Buffer[253]; // [esp+0x5C] [ebp-0x10C] BYREF
  __int16 v37; // [esp+0x159] [ebp-0xF]
  char v38; // [esp+0x15B] [ebp-0xD]
  int v39; // [esp+0x164] [ebp-0x4]
  int v40; // [esp+0x16C] [ebp+0x4]

  v2 = (ObjectCamera *)operator new(0x7Cu);
  v3 = 0;
  v39 = 0;
  if ( v2 )
    v4 = ((ObjectCamera *)v2)->Create();
  else
    v4 = 0;
  LODWORD(this->m_vecFiveLineup[0].y) = v4;
  v39 = -1;
  ((ObjectCamera *)v4)->SetCameraEyePosition(gfxMgr);
  ((ObjectCamera *)LODWORD(this->m_vecFiveLineup[0].y))->SetCameraRotate(86.0, 0.0, -200.0);
  v17.x = 0.0;
  *(_QWORD *)&v17.y = 0xC42F000041A00000uLL;
  ((ObjectCamera *)LODWORD(this->m_vecFiveLineup[0].y))->SetCameraAtPosition(v17, 1);
  ((ObjectCamera *)LODWORD(this->m_vecFiveLineup[0].y))->SetCameraDist(1142341632, -1052770304, 0);
  this->m_fCamTargZ = 106.0;
  this->m_fInitBlend = 0.0;
  this->m_FiveLineupCenterQuad = (gbGeomQuad *)-1018429440;
  this->m_fBlendTime = 4.0;
  this->m_nBlendState = 0;
  this->m_fBlendSpeed = -167.0;
  this->m_fBlendRectBX = -89.0;
  this->m_fBlendRectBY = 0.0;
  this->m_fBlendRectBW = -196.0;
  this->m_fBlendRectBH = -86.0;
  this->m_nReset = 0;
  this->m_fDirSinC = -276.0;
  this->m_fBlendC = 89.0;
  this->m_fDirCosC = 0.0;
  this->m_fDirSinD = -270.0;
  this->m_fBlendD = 256.0;
  this->m_fDirCosD = 170.0;
  this->m_fDirSinE = 116.0;
  this->m_fBlendE = 80.0;
  this->m_EnemyFiveLineupQuad = (gbGeomQuad *)1133510656;
  v22[0] = g_pfnUpdateFuncs[4];
  v22[1] = 0;
  v23 = 0;
  v24 = g_pfnUpdateFuncs[3];
  v25 = 0;
  v26 = 0;
  v27 = g_pfnUpdateFuncs[2];
  v28 = 0;
  v29 = 0;
  v30 = g_pfnUpdateFuncs[1];
  v31 = 0;
  v32 = 0;
  v33 = g_pfnUpdateFuncs[0];
  v34 = 0;
  p_m_fBlendD = &this->m_fBlendD;
  v35 = 0;
  pszName = (char *)v22;
  p_m_fCamTargZ = &this->m_fCamTargZ;
  p_y = &this->m_vecInitFiveLineup[0].y;
  do
  {
    ((Object3D *)(p_y - 20))->_Object3D(pszName, 10);
    ((Object3D *)(p_y - 20))->VecAngle(*p_m_fCamTargZ, p_m_fCamTargZ[1], p_m_fCamTargZ[2]);
    *(p_y - 6) = *p_m_fBlendD;
    p_y[1] = this->m_vecFiveLineup[0].y;
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v3) )
    {
      *(_BYTE *)p_y = 1;
    }
    else
    {
      *(_BYTE *)p_y = 0;
      *((_BYTE *)p_y - 59) = 0;
    }
    ++v3;
    p_y += 38;
    ++p_m_fBlendD;
    pszName += 10;
    p_m_fCamTargZ += 3;
  }
  while ( v3 < 5 );
  v6 = (UIDialog *)operator new(0x118u);
  v39 = 1;
  if ( v6 )
    v7 = ((UIDialog *)v6)->ResetState();
  else
    v7 = 0;
  v39 = -1;
  this->m_pStage = (CCBStage *)v7;
  ((UI3DCtrl *)v7)->LoadModel(pszModelName);
  switch ( v40 )
  {
    case 0:
      ((Object3D *)&this->m_fDirSinF)->_Object3D("SubGame\\Encampment\\EncampFlag\\WZ07\\WZ07.pol", 0);
      break;
    case 1:
      ((Object3D *)&this->m_fDirSinF)->_Object3D("SubGame\\Encampment\\EncampFlag\\WZ08\\WZ08.pol", 0);
      break;
    case 2:
      ((Object3D *)&this->m_fDirSinF)->_Object3D("SubGame\\Encampment\\EncampFlag\\WZ09\\WZ09.pol", 0);
      break;
    case 3:
      ((Object3D *)&this->m_fDirSinF)->_Object3D("SubGame\\Encampment\\EncampFlag\\WZ10\\WZ10.pol", 0);
      break;
    default:
      break;
  }
  ((Object3D *)&this->m_fDirSinF)->VecAngle(0.0, 0.0, 0.0);
  this->m_vecFiveLineupInitPos.z = this->m_vecFiveLineup[0].y;
  memset(Buffer, 0, sizeof(Buffer));
  v37 = 0;
  v38 = 0;
  sprintf(Buffer, byte_5967B0, "SubGame\\Encampment\\Encamp_scene\\Encamp_scene.lgt");
  if ( ((gbVFileSystem *)g_pVFileSys)->FileExistNum(Buffer) )
  {
    v8 = (gbVisNode *)operator new(0x58u);
    v9 = *(float *)&v8;
    v39 = 2;
    if ( v8 )
    {
    }
    else
      v9 = 0.0;
    v39 = -1;
    this->m_vecFiveLineup[0].x = v9;
    LODWORD(this->m_vecFiveLineup[0].x) = gbLoadLightFile(Buffer);
  }
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    v12 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->DetachAll3D();
      ((gbAudioManager *)v12)->StopSoundStream(0);
      ((gbAudioManager *)v12)->StopSoundStream(2);
    }
  }
  v13 = (UICoverFrm *)operator new(0x329Cu);
  v39 = 3;
  if ( v13 )
    v14 = (CUtil *)((UICoverFrm *)v13)->ctor();
  else
    v14 = 0;
  v39 = -1;
  this->m_pUtil = v14;
  ((Camera *)v14)->InitUIElements();
  v18 = off_5EFAB4;
  v15 = CScreenMode::GetInstance();
  ((CScreenMode *)v15)->AudioSetPosition(v18, 1);
  return 1;
}
