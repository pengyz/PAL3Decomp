#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageScene.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/CIniFile.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/PAL_GDB.h"

// Forward declarations for unnamed functions
int sub_4DFB70(...);
int sub_511340(...);
int sub_511630(...);
int sub_511CA0(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aCbsceneFivelin[];
extern char aCbsceneFivelin_0[];
extern char aCouldnTCreateT[];
extern char aDProjectPal3Co_1[];
extern char aDatascriptComb_1[];
extern char aEnemyfivelineu[];
extern char aFivelineup[];
extern char aGfxscriptAddit_1[];
extern char aRadius[];
extern char aRolepos[];
extern char aRoll[];
extern char aUiCombatPointe[];
extern unsigned char byte_17ABD00;
extern unsigned char byte_17ABE00;
extern unsigned char byte_17ABF00;
extern void *off_56A66C;

// 0x0050FE50
int CCBStageScene::Update()
{
  this->m_EnemyFiveLineupQuad.eu = 0.0;
  this->m_EnemyFiveLineupQuad.ev = 0.0;
  this->m_EnemyFiveLineupQuad.color.ColorQuadFmt = 0;
  BYTE1(this->m_EnemyFiveLineupQuad.color.Blue) = 1;
  BYTE2(this->m_EnemyFiveLineupQuad.color.Blue) = 1;
  HIBYTE(this->m_EnemyFiveLineupQuad.color.Blue) = 1;
  this->m_EnemyFiveLineupQuad.color.Red = 0;
  LOBYTE(this->m_EnemyFiveLineupQuad.color.Blue) = 0;
  LOBYTE(this->m_EnemyFiveLineupQuad.color.Green) = 0;
  this->m_FiveLineupQuad.vec[1].y = 0.0;
  this->m_FiveLineupQuad.vec[1].z = 0.0;
  this->m_FiveLineupQuad.vec[2].x = 1.0;
  this->m_FiveLineupQuad.vec[2].y = 1.0;
  this->m_FiveLineupCenterQuad.color.ColorQuadFmt = 0;
  this->m_FiveLineupCenterQuad.color.Blue = 0;
  this->m_FiveLineupCenterQuad.color.Green = 1065353216;
  this->m_FiveLineupCenterQuad.color.Red = 1065353216;
  this->m_FiveLineupQuad.color.Color = 0;
  this->m_FiveLineupCenterQuad.vec[0].x = 0.0;
  this->m_FiveLineupCenterQuad.vec[0].y = 1.0;
  this->m_FiveLineupCenterQuad.vec[0].z = 1.0;
  return 0;
}

// 0x0050FEE0
CCBStageScene::CCBStageScene()
{
  gbTexture *v2; // eax
  float *v3; // eax
  float x; // ecx
  gbTexture *v5; // eax
  float *v6; // eax
  float z; // ecx
  char pExceptionObject[1024]; // [esp+18h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+418h] [ebp-400h] BYREF

  this->Update();
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
  this->Render();
  this->ShowAxis();
  this->m_pFling = (gbGeomNode *)((gbEffectMgr *)*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200))->NewRenderEffect(aGfxscriptAddit_1, 0);
  v2 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                      g_Input.KeyInfo[177].Data,
                      aCbsceneFivelin);
  LODWORD(this->m_vecFling.x) = v2;
  v2->LoadTexture(1);
  v3 = (float *)operator new(0x44u);
  if ( v3 )
  {
    x = this->m_vecFling.x;
    *((_DWORD *)v3 + 16) = 1;
    *v3 = x;
  }
  else
  {
    v3 = 0;
  }
  LODWORD(this->m_vecFling.y) = v3;
  v5 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                      g_Input.KeyInfo[177].Data,
                      aCbsceneFivelin_0);
  LODWORD(this->m_vecFling.z) = v5;
  v5->LoadTexture(1);
  v6 = (float *)operator new(0x44u);
  if ( v6 )
  {
    z = this->m_vecFling.z;
    *((_DWORD *)v6 + 16) = 1;
    *v6 = z;
  }
  else
  {
    v6 = 0;
  }
  LODWORD(this->m_rotFling.x) = v6;
  if ( !v6 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCouldnTCreateT, aDProjectPal3Co_1, 135),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->Create();
  1;
}

// 0x005100D0
CCBStageScene::~CCBStageScene()
{
  gbGeomNode *m_pPointer; // ecx
  gbGeomNode *m_pGeomNode; // ecx
  gbGeomNode *m_pCvd; // ecx
  gbGeomNode **m_pCorpse; // esi
  int v6; // edi

  sub_511630(this);
  ((gbRefObject *)LODWORD(this->m_vecFling.x))->Release();
  ((gbRefObject *)this->m_pFling)->Release();
  if ( LODWORD(this->m_vecFling.y) )
  {
    operator delete((void *)LODWORD(this->m_vecFling.y));
    this->m_vecFling.y = 0.0;
  }
  m_pPointer = (gbGeomNode *)this->m_pPointer;
  if ( m_pPointer )
  {
    ((void (*)(gbGeomNode *, int))m_pPointer->next->next)(m_pPointer, 1);
    this->m_pPointer = 0;
  }
  m_pGeomNode = (gbGeomNode *)this->m_pGeomNode;
  if ( m_pGeomNode )
  {
    ((void (*)(gbGeomNode *, int))m_pGeomNode->next->next)(m_pGeomNode, 1);
    this->m_pGeomNode = 0;
  }
  m_pCvd = (gbGeomNode *)this->m_pCvd;
  if ( m_pCvd )
  {
    ((void (*)(gbGeomNode *, int))m_pCvd->next->next)(m_pCvd, 1);
    this->m_pCvd = 0;
  }
  m_pCorpse = this->m_pCorpse;
  v6 = 11;
  do
  {
    if ( *m_pCorpse )
    {
      ((void (*)(gbGeomNode *, int))(*m_pCorpse)->next->next)(*m_pCorpse, 1);
      *m_pCorpse = 0;
    }
    ++m_pCorpse;
    --v6;
  }
  while ( v6 );
  1;
}

// 0x00510180
char CCBStageScene::Reset()
{
  CCBStage *m_pStage; // ecx
  FightInfo *m_pFightInfo; // edi
  __int32 eSceneFiveMagic; // eax
  int v5; // eax
  float z; // ecx
  gbGeomNode **m_pCorpse; // esi
  int v8; // edi

  this->Update();
  this->SetFlingRotX();
  this->SetFlingRotY();
  m_pStage = (CCBStage *)this->m_pStage;
  m_pFightInfo = (FightInfo *)this->m_pStage->m_pCBSystem->m_pFightInfo;
  eSceneFiveMagic = m_pFightInfo->eSceneFiveMagic;
  this->m_EnemyFiveLineupQuad.color.Red = eSceneFiveMagic;
  switch ( eSceneFiveMagic )
  {
    case 1:
      this->m_FiveLineupCenterQuad.vec[1].x = 2.467103e38;
      break;
    case 2:
      this->m_FiveLineupCenterQuad.vec[1].x = NAN;
      break;
    case 3:
      this->m_FiveLineupCenterQuad.vec[1].x = 2.8008505e38;
      break;
    case 4:
      this->m_FiveLineupCenterQuad.vec[1].x = NAN;
      break;
    case 5:
      this->m_FiveLineupCenterQuad.vec[1].x = NAN;
      break;
    default:
      break;
  }
  v5 = ((CCBRoleState *)m_pStage->m_pCBSystem->m_pRoleState)->CheckDeath(this->m_EnemyFiveLineupQuad.color.Red);
  this->m_vecFiveLineup[6].x = this->m_vecInitFiveLineup[6].x;
  this->m_vecFiveLineup[6].y = this->m_vecInitFiveLineup[6].y;
  this->m_vecFiveLineup[6].z = this->m_vecInitFiveLineup[6].z;
  switch ( v5 )
  {
    case 1:
      this->m_EnemyFiveLineupQuad.vec[2].y = this->m_EnemyFiveLineupQuad.vec[2].y + 1.256636;
      this->m_vecFiveLineup[1].x = this->m_vecInitFiveLineup[5].x;
      this->m_vecFiveLineup[1].y = this->m_vecInitFiveLineup[5].y;
      this->m_vecFiveLineup[1].z = this->m_vecInitFiveLineup[5].z;
      this->m_vecFiveLineup[5].x = this->m_vecInitFiveLineup[3].x;
      this->m_vecFiveLineup[5].y = this->m_vecInitFiveLineup[3].y;
      this->m_vecFiveLineup[5].z = this->m_vecInitFiveLineup[3].z;
      this->m_vecFiveLineup[3].x = this->m_vecInitFiveLineup[4].x;
      this->m_vecFiveLineup[3].y = this->m_vecInitFiveLineup[4].y;
      this->m_vecFiveLineup[3].z = this->m_vecInitFiveLineup[4].z;
      this->m_vecFiveLineup[4].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[4].y = this->m_vecInitFiveLineup[2].y;
      this->m_vecFiveLineup[4].z = this->m_vecInitFiveLineup[2].z;
      this->m_vecFiveLineup[2].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[2].y = this->m_vecInitFiveLineup[1].y;
      z = this->m_vecInitFiveLineup[1].z;
      goto LABEL_13;
    case 2:
      this->m_EnemyFiveLineupQuad.vec[2].y = this->m_EnemyFiveLineupQuad.vec[2].y + 2.513272;
      this->m_vecFiveLineup[1].x = this->m_vecInitFiveLineup[3].x;
      this->m_vecFiveLineup[1].y = this->m_vecInitFiveLineup[3].y;
      this->m_vecFiveLineup[1].z = this->m_vecInitFiveLineup[3].z;
      this->m_vecFiveLineup[5].x = this->m_vecInitFiveLineup[4].x;
      this->m_vecFiveLineup[5].y = this->m_vecInitFiveLineup[4].y;
      this->m_vecFiveLineup[5].z = this->m_vecInitFiveLineup[4].z;
      this->m_vecFiveLineup[3].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[3].y = this->m_vecInitFiveLineup[2].y;
      this->m_vecFiveLineup[3].z = this->m_vecInitFiveLineup[2].z;
      this->m_vecFiveLineup[4].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[4].y = this->m_vecInitFiveLineup[1].y;
      this->m_vecFiveLineup[4].z = this->m_vecInitFiveLineup[1].z;
      this->m_vecFiveLineup[2].x = this->m_vecInitFiveLineup[5].x;
      this->m_vecFiveLineup[2].y = this->m_vecInitFiveLineup[5].y;
      z = this->m_vecInitFiveLineup[5].z;
      goto LABEL_13;
    case 3:
      this->m_EnemyFiveLineupQuad.vec[2].y = this->m_EnemyFiveLineupQuad.vec[2].y + 5.0265441;
      this->m_vecFiveLineup[1].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[1].y = this->m_vecInitFiveLineup[2].y;
      this->m_vecFiveLineup[1].z = this->m_vecInitFiveLineup[2].z;
      this->m_vecFiveLineup[5].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[5].y = this->m_vecInitFiveLineup[1].y;
      this->m_vecFiveLineup[5].z = this->m_vecInitFiveLineup[1].z;
      this->m_vecFiveLineup[3].x = this->m_vecInitFiveLineup[5].x;
      this->m_vecFiveLineup[3].y = this->m_vecInitFiveLineup[5].y;
      this->m_vecFiveLineup[3].z = this->m_vecInitFiveLineup[5].z;
      this->m_vecFiveLineup[4].x = this->m_vecInitFiveLineup[3].x;
      this->m_vecFiveLineup[4].y = this->m_vecInitFiveLineup[3].y;
      this->m_vecFiveLineup[4].z = this->m_vecInitFiveLineup[3].z;
      this->m_vecFiveLineup[2].x = this->m_vecInitFiveLineup[4].x;
      this->m_vecFiveLineup[2].y = this->m_vecInitFiveLineup[4].y;
      z = this->m_vecInitFiveLineup[4].z;
      goto LABEL_13;
    case 4:
      this->m_EnemyFiveLineupQuad.vec[2].y = this->m_EnemyFiveLineupQuad.vec[2].y + 3.769908;
      this->m_vecFiveLineup[1].x = this->m_vecInitFiveLineup[4].x;
      this->m_vecFiveLineup[1].y = this->m_vecInitFiveLineup[4].y;
      this->m_vecFiveLineup[1].z = this->m_vecInitFiveLineup[4].z;
      this->m_vecFiveLineup[5].x = this->m_vecInitFiveLineup[2].x;
      this->m_vecFiveLineup[5].y = this->m_vecInitFiveLineup[2].y;
      this->m_vecFiveLineup[5].z = this->m_vecInitFiveLineup[2].z;
      this->m_vecFiveLineup[3].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[3].y = this->m_vecInitFiveLineup[1].y;
      this->m_vecFiveLineup[3].z = this->m_vecInitFiveLineup[1].z;
      this->m_vecFiveLineup[4].x = this->m_vecInitFiveLineup[5].x;
      this->m_vecFiveLineup[4].y = this->m_vecInitFiveLineup[5].y;
      this->m_vecFiveLineup[4].z = this->m_vecInitFiveLineup[5].z;
      this->m_vecFiveLineup[2].x = this->m_vecInitFiveLineup[3].x;
      this->m_vecFiveLineup[2].y = this->m_vecInitFiveLineup[3].y;
      z = this->m_vecInitFiveLineup[3].z;
      goto LABEL_13;
    case 5:
      this->m_vecFiveLineup[1].x = this->m_vecInitFiveLineup[1].x;
      this->m_vecFiveLineup[1].y = this->m_vecInitFiveLineup[1].y;
      this->m_vecFiveLineup[1].z = this->m_vecInitFiveLineup[1].z;
      this->m_vecFiveLineup[5].x = this->m_vecInitFiveLineup[5].x;
      this->m_vecFiveLineup[5].y = this->m_vecInitFiveLineup[5].y;
      this->m_vecFiveLineup[5].z = this->m_vecInitFiveLineup[5].z;
      this->m_vecFiveLineup[3].x = this->m_vecInitFiveLineup[3].x;
      this->m_vecFiveLineup[3].y = this->m_vecInitFiveLineup[3].y;
      this->m_vecFiveLineup[3].z = this->m_vecInitFiveLineup[3].z;
      this->m_vecFiveLineup[4].x = this->m_vecInitFiveLineup[4].x;
      this->m_vecFiveLineup[4].y = this->m_vecInitFiveLineup[4].y;
      this->m_vecFiveLineup[4].z = this->m_vecInitFiveLineup[4].z;
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
    sub_511340((int)this, m_pFightInfo->sSceneName);
  else
    sub_511340((int)this, aZ27);
  m_pCorpse = this->m_pCorpse;
  v8 = 11;
  do
  {
    if ( *m_pCorpse )
    {
      ((void (*)(gbGeomNode *, int))(*m_pCorpse)->next->next)(*m_pCorpse, 1);
      *m_pCorpse = 0;
    }
    ++m_pCorpse;
    --v8;
  }
  while ( v8 );
  return 1;
}

// 0x00510540
int CCBStageScene::Create()
{
  gbGeomNode *v2; // eax
  gbGeomNode *v3; // esi
  gbGeomNode *v4; // ecx
  char pExceptionObject[1024]; // [esp+Ch] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+40Ch] [ebp-40Ch] BYREF
  int v8; // [esp+814h] [ebp-4h]

  v2 = (gbGeomNode *)operator new(0x118u);
  v3 = v2;
  v8 = 0;
  if ( v2 )
  {
    v2->gbGeomNode();
    v3->next = (gbChain1DNode *)&off_56A66C;
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
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_1, 293),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return v4->LoadFromFile(aUiCombatPointe, 0, 0);
}

// 0x00510610
void CCBStageScene::Destroy()
{
  CCBStageScene **v1; // esi
  int v2; // ebx
  gbGeomNode **v3; // edi
  CCBRoleState *m_pCamControl; // ecx
  int v5; // eax
  int SkillNum; // ebp
  gbGeomNode *v7; // eax
  gbGeomNode *v8; // esi
  int a2; // [esp+18h] [ebp-918h]
  char v11[256]; // [esp+24h] [ebp-90Ch] BYREF
  char pExceptionObject[1024]; // [esp+124h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+524h] [ebp-40Ch] BYREF
  int v14; // [esp+92Ch] [ebp-4h]

  v1 = this;
  v2 = 0;
  a2 = 0;
  v3 = (gbGeomNode **)(this + 155);
  do
  {
    if ( *v3 )
    {
      ((void (*)(gbGeomNode *, int))(*v3)->next->next)(*v3, 1);
      *v3 = 0;
    }
    m_pCamControl = (CCBRoleState *)(*v1)->m_pStage->m_pCamControl;
    if ( m_pCamControl->m_Role[v2].bValid )
    {
      v5 = *(_DWORD *)(m_pCamControl->InitUI(a2) + 540);
      if ( v5 )
      {
        SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(v5);
        if ( SkillNum )
        {
          v7 = (gbGeomNode *)operator new(0x118u);
          v8 = v7;
          v14 = 0;
          if ( v7 )
          {
            v7->gbGeomNode();
            v8->next = (gbChain1DNode *)&off_56A66C;
          }
          else
          {
            v8 = 0;
          }
          v14 = -1;
          *v3 = v8;
          if ( !v8 )
          {
            qmemcpy(
              pExceptionObject,
              ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_1, 330),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          sprintf(v11, "item\\%s\\%s.pol", (const char *)(SkillNum + 36), (const char *)(SkillNum + 36));
          if ( !((gbGeomNode *)*v3)->LoadFromFile(v11, 0, 0) )
          {
            if ( *v3 )
            {
              ((void (*)(gbGeomNode *, int))(*v3)->next->next)(*v3, 1);
              *v3 = 0;
            }
          }
          sprintf(
            v11,
            "item\\%s\\%s%s.tga",
            (const char *)(SkillNum + 36),
            (const char *)(SkillNum + 36),
            (const char *)(SkillNum + 66));
          ((gbGeomNode *)*v3)->ReplaceTexture(v11);
          v1 = this;
        }
      }
    }
    ++v2;
    ++v3;
    ++a2;
  }
  while ( v2 < 11 );
}

// 0x005107C0
int CCBStageScene::Init()
{
  double z; // st7
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
  double su; // st7
  float v27; // esi
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
  float v47; // [esp+4h] [ebp-18h]
  float v48; // [esp+4h] [ebp-18h]
  float v49; // [esp+8h] [ebp-14h]
  float v50; // [esp+8h] [ebp-14h]
  float y; // [esp+Ch] [ebp-10h]
  __int32 Color; // [esp+10h] [ebp-Ch]
  float x; // [esp+10h] [ebp-Ch]
  float v54; // [esp+14h] [ebp-8h]
  float v55; // [esp+18h] [ebp-4h]
  __int32 v56; // [esp+18h] [ebp-4h]

  z = this->m_EnemyFiveLineupQuad.vec[1].z;
  Color = this->m_FiveLineupCenterQuad.color.Color;
  y = this->m_EnemyFiveLineupQuad.vec[0].y;
  v47 = sin(this->m_EnemyFiveLineupQuad.vec[2].y);
  v3 = cos(this->m_EnemyFiveLineupQuad.vec[2].y);
  this->m_FiveLineupQuad.vec[3].y = 0.0;
  v49 = v3;
  v54 = z * 0.5;
  v4 = *(float *)&Color - v54;
  this->m_FiveLineupQuad.vec[3].x = v4;
  v5 = y - v54;
  this->m_FiveLineupQuad.vec[3].z = v5;
  this->m_FiveLineupQuad.sv = 0.0;
  v55 = v54 + *(float *)&Color;
  this->m_FiveLineupQuad.su = v55;
  this->m_FiveLineupQuad.eu = v5;
  this->m_FiveLineupQuad.ev = v55;
  this->m_FiveLineupQuad.color.ColorQuadFmt = 0;
  *(float *)&v56 = v54 + y;
  this->m_FiveLineupQuad.color.Blue = v56;
  this->m_FiveLineupQuad.color.Red = 0;
  *(float *)&this->m_FiveLineupQuad.color.Green = v4;
  this->m_FiveLineupQuad.color.Alpha = v56;
  this->m_rotFling.z = 0.0;
  this->m_rotFling.y = -z;
  *(float *)&this->m_bShowFling = -z;
  this->m_pFiveLineupTexture = 0;
  *(float *)&this->m_pFiveLineupEffect = z;
  *(float *)&this->m_pFiveLineupTextureArray = -z;
  this->m_pFiveLineupCenterTextureArray = 0;
  *(float *)&this->m_pFiveLineupCenterTexture = z;
  this->m_FiveLineupQuad.vec[0].x = z;
  this->m_FiveLineupQuad.vec[0].z = 0.0;
  this->m_FiveLineupQuad.vec[0].y = -z;
  this->m_FiveLineupQuad.vec[1].x = z;
  v6 = v49 * *(float *)&this->m_bShowFling - v47 * this->m_rotFling.y;
  v7 = v47 * *(float *)&this->m_bShowFling;
  v8 = v49 * this->m_rotFling.y;
  this->m_rotFling.z = 0.0;
  this->m_rotFling.y = v7 + v8;
  *(float *)&this->m_bShowFling = v6;
  v9 = v49 * *(float *)&this->m_pFiveLineupTextureArray - v47 * *(float *)&this->m_pFiveLineupEffect;
  v10 = v47 * *(float *)&this->m_pFiveLineupTextureArray;
  v11 = v49 * *(float *)&this->m_pFiveLineupEffect;
  this->m_pFiveLineupTexture = 0;
  *(float *)&this->m_pFiveLineupEffect = v10 + v11;
  *(float *)&this->m_pFiveLineupTextureArray = v9;
  v12 = v49 * this->m_FiveLineupQuad.vec[0].x - v47 * *(float *)&this->m_pFiveLineupCenterTexture;
  v13 = v49 * *(float *)&this->m_pFiveLineupCenterTexture;
  v14 = v47 * this->m_FiveLineupQuad.vec[0].x;
  this->m_pFiveLineupCenterTextureArray = 0;
  *(float *)&this->m_pFiveLineupCenterTexture = v13 + v14;
  this->m_FiveLineupQuad.vec[0].x = v12;
  v15 = v49 * this->m_FiveLineupQuad.vec[1].x - v47 * this->m_FiveLineupQuad.vec[0].y;
  v16 = v47 * this->m_FiveLineupQuad.vec[1].x;
  v17 = v49 * this->m_FiveLineupQuad.vec[0].y;
  this->m_FiveLineupQuad.vec[0].z = 0.0;
  this->m_FiveLineupQuad.vec[0].y = v16 + v17;
  this->m_FiveLineupQuad.vec[1].x = v15;
  v18 = y + *(float *)&this->m_bShowFling;
  v19 = *(float *)&Color + this->m_rotFling.y;
  this->m_rotFling.z = 0.5;
  this->m_rotFling.y = v19;
  *(float *)&this->m_bShowFling = v18;
  v20 = y + *(float *)&this->m_pFiveLineupTextureArray;
  v21 = *(float *)&Color + *(float *)&this->m_pFiveLineupEffect;
  this->m_pFiveLineupTexture = (gbTexture *)1056964608;
  *(float *)&this->m_pFiveLineupEffect = v21;
  *(float *)&this->m_pFiveLineupTextureArray = v20;
  v22 = y + this->m_FiveLineupQuad.vec[0].x;
  v23 = *(float *)&Color + *(float *)&this->m_pFiveLineupCenterTexture;
  this->m_pFiveLineupCenterTextureArray = (gbTextureArray *)1056964608;
  *(float *)&this->m_pFiveLineupCenterTexture = v23;
  this->m_FiveLineupQuad.vec[0].x = v22;
  v24 = y + this->m_FiveLineupQuad.vec[1].x;
  v25 = *(float *)&Color + this->m_FiveLineupQuad.vec[0].y;
  this->m_FiveLineupQuad.vec[0].z = 0.5;
  this->m_FiveLineupQuad.vec[0].y = v25;
  this->m_FiveLineupQuad.vec[1].x = v24;
  su = this->m_EnemyFiveLineupQuad.su;
  v48 = sin(this->m_EnemyFiveLineupQuad.sv);
  v50 = cos(this->m_EnemyFiveLineupQuad.sv);
  x = this->m_EnemyFiveLineupQuad.vec[3].x;
  v27 = this->m_EnemyFiveLineupQuad.vec[3].z;
  this->m_FiveLineupCenterQuad.vec[1].y = -su;
  this->m_FiveLineupCenterQuad.vec[2].x = -su;
  this->m_FiveLineupCenterQuad.vec[1].z = 0.0;
  this->m_FiveLineupCenterQuad.vec[2].z = 0.0;
  this->m_FiveLineupCenterQuad.vec[2].y = su;
  this->m_FiveLineupCenterQuad.vec[3].x = -su;
  this->m_FiveLineupCenterQuad.vec[3].z = 0.0;
  this->m_FiveLineupCenterQuad.vec[3].y = su;
  this->m_FiveLineupCenterQuad.su = su;
  this->m_FiveLineupCenterQuad.eu = 0.0;
  this->m_FiveLineupCenterQuad.sv = -su;
  this->m_FiveLineupCenterQuad.ev = su;
  v28 = v50 * this->m_FiveLineupCenterQuad.vec[2].x - v48 * this->m_FiveLineupCenterQuad.vec[1].y;
  v29 = v50 * this->m_FiveLineupCenterQuad.vec[1].y;
  v30 = v48 * this->m_FiveLineupCenterQuad.vec[2].x;
  this->m_FiveLineupCenterQuad.vec[1].z = 0.0;
  this->m_FiveLineupCenterQuad.vec[1].y = v29 + v30;
  this->m_FiveLineupCenterQuad.vec[2].x = v28;
  v31 = v50 * this->m_FiveLineupCenterQuad.vec[3].x - v48 * this->m_FiveLineupCenterQuad.vec[2].y;
  v32 = v48 * this->m_FiveLineupCenterQuad.vec[3].x;
  v33 = v50 * this->m_FiveLineupCenterQuad.vec[2].y;
  this->m_FiveLineupCenterQuad.vec[2].z = 0.0;
  this->m_FiveLineupCenterQuad.vec[2].y = v32 + v33;
  this->m_FiveLineupCenterQuad.vec[3].x = v31;
  v34 = v50 * this->m_FiveLineupCenterQuad.su - v48 * this->m_FiveLineupCenterQuad.vec[3].y;
  v35 = v50 * this->m_FiveLineupCenterQuad.vec[3].y;
  v36 = v48 * this->m_FiveLineupCenterQuad.su;
  this->m_FiveLineupCenterQuad.vec[3].z = 0.0;
  this->m_FiveLineupCenterQuad.vec[3].y = v35 + v36;
  this->m_FiveLineupCenterQuad.su = v34;
  v37 = v50 * this->m_FiveLineupCenterQuad.ev - v48 * this->m_FiveLineupCenterQuad.sv;
  v38 = v48 * this->m_FiveLineupCenterQuad.ev;
  v39 = v50 * this->m_FiveLineupCenterQuad.sv;
  this->m_FiveLineupCenterQuad.eu = 0.0;
  this->m_FiveLineupCenterQuad.sv = v38 + v39;
  this->m_FiveLineupCenterQuad.ev = v37;
  v40 = v27 + this->m_FiveLineupCenterQuad.vec[2].x;
  this->m_FiveLineupCenterQuad.vec[1].y = x + this->m_FiveLineupCenterQuad.vec[1].y;
  this->m_FiveLineupCenterQuad.vec[1].z = 0.5;
  this->m_FiveLineupCenterQuad.vec[2].x = v40;
  v41 = v27 + this->m_FiveLineupCenterQuad.vec[3].x;
  v42 = x + this->m_FiveLineupCenterQuad.vec[2].y;
  this->m_FiveLineupCenterQuad.vec[2].z = 0.5;
  this->m_FiveLineupCenterQuad.vec[2].y = v42;
  this->m_FiveLineupCenterQuad.vec[3].x = v41;
  v43 = v27 + this->m_FiveLineupCenterQuad.su;
  v44 = x + this->m_FiveLineupCenterQuad.vec[3].y;
  this->m_FiveLineupCenterQuad.vec[3].z = 0.5;
  this->m_FiveLineupCenterQuad.vec[3].y = v44;
  this->m_FiveLineupCenterQuad.su = v43;
  v45 = v27 + this->m_FiveLineupCenterQuad.ev;
  v46 = x + this->m_FiveLineupCenterQuad.sv;
  this->m_FiveLineupCenterQuad.eu = 0.5;
  this->m_FiveLineupCenterQuad.sv = v46;
  this->m_FiveLineupCenterQuad.ev = v45;
  return 0;
}

// 0x00510C80
int CCBStageScene::SetBattleFieldAttr()
{
  int result; // eax
  gbGeomNode *m_pPointer; // ecx

  result = this->Init();
  m_pPointer = (gbGeomNode *)this->m_pPointer;
  if ( m_pPointer )
    return ((int (*)(gbGeomNode *))m_pPointer->next[5].next)(m_pPointer);
  return result;
}

// 0x00510CA0
void CCBStageScene::GetBattleFieldSubdueAttr(gbMatrixStack *a2)
{
  int v3; // ebp
  gbGeomNode *m_pGeomNode; // ecx
  gbVisNode *m_pLights; // ecx
  gbGeomNode **m_pCorpse; // ebx
  long double v8; // st7
  float v9; // [esp+18h] [ebp-24h]
  float v10; // [esp+18h] [ebp-24h]
  float v11; // [esp+30h] [ebp-Ch]
  float x; // [esp+34h] [ebp-8h]
  float v13; // [esp+38h] [ebp-4h]
  gbMatrixStack *a2a; // [esp+40h] [ebp+4h]

  v3 = 0;
  m_pGeomNode = (gbGeomNode *)this->m_pGeomNode;
  if ( m_pGeomNode && LOBYTE(this->m_bLoaded) )
  {
    ((void (*)(gbGeomNode *, _DWORD))m_pGeomNode->next[4].next)(m_pGeomNode, 0);
    m_pLights = (gbVisNode *)this->m_pLights;
    if ( m_pLights )
      ((void (*)(gbVisNode *, _DWORD))m_pLights->next[4].next)(m_pLights, 0);
    if ( LOBYTE(this->m_EnemyFiveLineupQuad.color.Blue) && this->m_pPointer )
    {
      a2->Push();
      v9 = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 10.0) * 5.0 + this->m_EnemyFiveLineupQuad.ev + 6.0;
      a2->Translate(this->m_EnemyFiveLineupQuad.eu, v9, *(float *)&this->m_EnemyFiveLineupQuad.color.ColorQuadFmt);
      ((void (*)(gbGeomNode *, _DWORD))this->m_pPointer->next[4].next)(this->m_pPointer, 0);
      a2->Pop();
    }
    a2a = 0;
    x = this->m_EnemyFiveLineupQuad.vec[0].x;
    m_pCorpse = this->m_pCorpse;
    do
    {
      if ( v3 >= 5 )
      {
        if ( *m_pCorpse )
        {
          v8 = (double)(int)a2a * 0.017453292;
          v11 = sin(v8) * 20.0 + *(float *)&this->m_FiveLineupCenterQuad.color.Color;
          v13 = cos(v8) * 20.0 + this->m_EnemyFiveLineupQuad.vec[0].y;
          a2->Push();
          v10 = x + 2.0;
          a2->Translate(v11, v10, v13);
          ((void (*)(gbGeomNode *, _DWORD))(*m_pCorpse)->next[4].next)(*m_pCorpse, 0);
          a2->Pop();
          a2a = (gbMatrixStack *)((char *)a2a + 60);
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
  struct gbRenderEffect *v1; // esi
  __int32 *p_Blue; // edi
  int v3; // ebp
  struct gbDynVertBuf *DynVertBuf; // eax
  struct gbDynVertBuf *v5; // edi
  int v6; // ecx
  int v7; // ecx
  gbColorQuad v8; // [esp+10h] [ebp-3Ch] BYREF
  struct gbColorQuad v9; // [esp+30h] [ebp-1Ch] BYREF
  int v10; // [esp+48h] [ebp-4h]

  if ( g_Input.KeyInfo[177].Data && BYTE1(this->m_EnemyFiveLineupQuad.color.Blue) )
  {
    v1 = ((gbEffectMgr *)*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200))->NewTrivalEffect(3);
    HIBYTE(v9.ColorQuadFmt) = 80;
    p_Blue = (__int32 *)&v9.Blue;
    v3 = 2;
    do
    {
      ((void (*)(__int32 *))gbVec3D::`default constructor closure')(p_Blue);
      p_Blue += 3;
      --v3;
    }
    while ( v3 );
    memset(&v9.Blue, 0, 12);
    DynVertBuf = ((gbVertPoolMgr *)*(gbVertPoolMgr **)(g_Input.KeyInfo[177].Data + 196))->GetDynVertBuf(5u);
    v8.Red = (__int32)v1;
    v8.Green = 2;
    v8.Blue = (__int32)&v9.Blue;
    v8.ColorQuadFmt = (int)&v9.Blue;
    v5 = DynVertBuf;
    LOWORD(v9.ColorQuadFmt) = 255;
    BYTE2(v9.ColorQuadFmt) = 0;
    v9.Color = 0;
    v9.Alpha = 0;
    v10 = 1176256512;
    ((gbColorQuad *)&v8)->gbColorQuad(&v9);
    v5->RenderLineStrip();
    v8.Red = (__int32)v1;
    v8.Green = 2;
    v8.Blue = (__int32)&v9.Blue;
    v8.ColorQuadFmt = v6;
    LOBYTE(v9.ColorQuadFmt) = 0;
    *(_WORD *)((char *)&v9.ColorQuadFmt + 1) = -256;
    v10 = 0;
    v9.Color = 0;
    v9.Alpha = 1176256512;
    ((gbColorQuad *)&v8)->gbColorQuad(&v9);
    v5->RenderLineStrip();
    v8.Red = (__int32)v1;
    v8.Green = 2;
    v8.Blue = (__int32)&v9.Blue;
    v8.ColorQuadFmt = v7;
    LOWORD(v9.ColorQuadFmt) = -256;
    BYTE2(v9.ColorQuadFmt) = 0;
    v10 = 0;
    v9.Alpha = 0;
    v9.Color = 1176256512;
    ((gbColorQuad *)&v8)->gbColorQuad(&v9);
    v5->RenderLineStrip();
    v1->Release();
  }
}

// 0x00510F50
char CCBStageScene::IsSameBattleFieldAttr()
{
  char result; // al
  int v3; // esi
  int v4; // edi
  CCBRoleState *m_pRoleState; // ebp
  int inited; // eax
  unsigned __int8 *p_bValid; // [esp+Ch] [ebp-Ch]
  float v8; // [esp+10h] [ebp-8h] BYREF
  float v9; // [esp+14h] [ebp-4h] BYREF

  result = g_Input.KeyInfo[177].Data;
  v9 = 0.0;
  v8 = 0.0;
  if ( g_Input.KeyInfo[177].Data )
  {
    result = BYTE2(this->m_EnemyFiveLineupQuad.color.Blue);
    if ( result )
    {
      v3 = 0;
      v4 = 24;
      m_pRoleState = (CCBRoleState *)this->m_pStage->m_pCBSystem->m_pRoleState;
      p_bValid = (unsigned __int8 *)&m_pRoleState->m_Role[0].bValid;
      do
      {
        result = (char)p_bValid;
        if ( *p_bValid )
        {
          inited = m_pRoleState->InitUI(v3);
          sprintf(byte_17ABF00, "%d(%s)", v3, (const char *)(inited + 8));
          ((gbCamera *)&this->m_pStage->m_pCam->OrthoSize)->PointWorldToScr((struct gbVec3D *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + v4))->m_Thread[42].bExecuted, &v9, &v8);
          result = sub_4DFB70((char *)this->m_pStage->m_TempStorageNGH, byte_17ABF00, v9, v8, 16.0);
        }
        v4 += 4;
        ++v3;
        p_bValid += 892;
      }
      while ( v4 < 68 );
    }
  }
  return result;
}

// 0x00511030
void CCBStageScene::LoadPointer(char a2)
{
  float y; // ecx
  gbGeomNode *m_pFling; // edx

  ((gbVertPoolMgr *)*(gbVertPoolMgr **)(g_Input.KeyInfo[177].Data + 196))->GetDynVertBuf(0x15u);
  y = this->m_vecFling.y;
  m_pFling = (gbGeomNode *)this->m_pFling;
  BYTE2(this->m_FiveLineupQuad.vec[2].z) = -1;
  BYTE1(this->m_FiveLineupQuad.vec[2].z) = -1;
  LOBYTE(this->m_FiveLineupQuad.vec[2].z) = -1;
  HIBYTE(this->m_FiveLineupQuad.vec[2].z) = a2;
  HIBYTE(this->m_FiveLineupCenterQuad.vec[1].x) = a2;
  ((gbDynVertBuf *)&this->m_rotFling.y)->RenderGeomQuad(1, (struct gbRenderEffect *)m_pFling, (struct gbTextureArray *)LODWORD(y));
  ((gbDynVertBuf *)&this->m_FiveLineupQuad.vec[3])->RenderGeomQuad(1, (struct gbRenderEffect *)this->m_pFling, (struct gbTextureArray *)LODWORD(this->m_rotFling.x));
}

// 0x00511110
bool CCBStageScene::LoadFlingNode()
{
  CCBStage *m_pStage; // eax
  double v3; // st7
  double v4; // st6
  double v5; // st5
  float v7; // [esp+0h] [ebp-74h]
  float v8; // [esp+4h] [ebp-70h]
  Actor *pPos; // [esp+8h] [ebp-6Ch] BYREF
  gbVec3D v10; // [esp+Ch] [ebp-68h] BYREF
  struct gbVec3D v11; // [esp+20h] [ebp-54h] BYREF
  struct gbVec3D v12; // [esp+2Ch] [ebp-48h] BYREF
  float pTarget[6]; // [esp+38h] [ebp-3Ch] BYREF
  gbRay v14; // [esp+50h] [ebp-24h] BYREF
  gbVec3D v15; // [esp+68h] [ebp-Ch] BYREF

  pTarget[1] = 1.0;
  pTarget[0] = 0.0;
  pTarget[2] = 0.0;
  v12.y = 0.0;
  v12.x = 1.0;
  v12.z = 1.0;
  memset(&v11, 0, sizeof(v11));
  memset(&v14.Direction, 0, sizeof(v14.Direction));
  ((gbVec3D *)&v15)->gbVec3D(0.0, 0.0, 0.0);
  m_pStage = (CCBStage *)this->m_pStage;
  pPos = (Actor *)this->m_pStage->m_WPXVariance;
  LODWORD(v10.x) = m_pStage->m_pDisplayChain;
  v14 = *(gbRay *)((CameraCtrl *)m_pStage->m_pCam)->GetViewTarget(pTarget, (float *)&pPos);
  v3 = ((gbRay *)&v14)->IntersectPlane(&v12, &v11);
  v7 = v14.Origin.y * v3;
  v8 = v14.Origin.z * v3;
  v12.y = v7 + pTarget[4];
  v12.z = pTarget[5] + v8;
  v4 = *(float *)&this->m_FiveLineupCenterQuad.color.Color - v12.y;
  v12.z = this->m_EnemyFiveLineupQuad.vec[0].x - v12.z;
  v5 = this->m_EnemyFiveLineupQuad.vec[0].y - (v3 * v14.Direction.x + v14.Origin.x);
  v10.y = v12.z;
  pTarget[0] = v5;
  v10.x = v4;
  v10.z = pTarget[0];
  return ((gbVec3D *)&v10)->Length() < 30.0;
}

// 0x005112B0
int CCBStageScene::SetFlingRotX()
{
  float z; // edx
  float *p_z; // eax
  __int32 *p_Color; // ecx
  int result; // eax

  z = this->m_EnemyFiveLineupQuad.vec[2].z;
  this->m_EnemyFiveLineupQuad.vec[1].z = this->m_EnemyFiveLineupQuad.vec[2].x;
  p_z = (float *)&this->m_EnemyFiveLineupQuad.vec[0].z;
  this->m_EnemyFiveLineupQuad.vec[2].y = z;
  p_Color = (__int32 *)&this->m_FiveLineupCenterQuad.color.Color;
  * p_Color = (*)*(_DWORD *)p_z;
  p_Color[1] = *((_DWORD *)p_z + 1);
  result = *((_DWORD *)p_z + 2);
  p_Color[2] = result;
  return result;
}

// 0x005112F0
_DWORD * CCBStageScene::SetFlingRotY()
{
  _DWORD *result; // eax
  int v2; // ecx

  result = (_DWORD *)&this->m_vecFiveLineup[0].y;
  v2 = 7;
  do
  {
    *(result - 1) = result[20];
    * result = (*)result[21];
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

// 0x00511690
char CCBStageScene::Update()
{
  int v3; // edi
  int i; // esi
  CIniFile v5; // [esp+18h] [ebp-14h] BYREF
  int v6; // [esp+28h] [ebp-4h]

  if ( (g_nGameFlags & 2) != 0 )
    return 1;
  ((CIniFile *)&v5)->CIniFile();
  v3 = 0;
  v6 = 0;
  ((CIniFile *)&v5)->OpenFileWrite(aDatascriptComb_1);
  ((CIniFile *)&v5)->WriteSection(aRolepos);
  for ( i = 24; i < 68; i += 4 )
  {
    sprintf(byte_17ABE00, "Role%d-x", v3);
    ((CIniFile *)&v5)->WriteLine(byte_17ABE00, *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[42].bExecuted);
    sprintf(byte_17ABE00, "Role%d-z", v3);
    ((CIniFile *)&v5)->WriteLine(byte_17ABE00, *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[42].cmd.dwCmdID);
    ++v3;
  }
  v6 = -1;
  ((CIniFile *)&v5)->~CIniFile();
  return 1;
}

// 0x00511790
char CCBStageScene::Render()
{
  int v2; // ebp
  int v3; // edi
  gbVec3D *v4; // eax
  float v5; // edx
  float v6; // ecx
  float v7; // edx
  float v8; // eax
  float x; // eax
  double v10; // st7
  float z; // edx
  float v12; // ecx
  float v13; // eax
  float v14; // ecx
  CIniFile v16; // [esp+2Ch] [ebp-20h] BYREF
  float v17; // [esp+34h] [ebp-18h] BYREF
  float y; // [esp+38h] [ebp-14h]
  float v19; // [esp+3Ch] [ebp-10h] BYREF
  int v20; // [esp+48h] [ebp-4h]

  v17 = 0.0;
  y = 0.0;
  v19 = 0.0;
  v2 = 0;
  v3 = 0;
  ((CIniFile *)&v16)->CIniFile();
  v20 = 0;
  ((CIniFile *)&v16)->OpenFileRead(aDatascriptComb_1);
  do
  {
    ((CIniFile *)&v16)->ReadStart();
    ((CIniFile *)&v16)->ReadSection(aRolepos);
    sprintf(byte_17ABD00, "Role%d-x", v2);
    ((CIniFile *)&v16)->ReadLine(byte_17ABD00, &v17);
    y = 0.0;
    sprintf(byte_17ABD00, "Role%d-z", v2);
    ((CIniFile *)&v16)->ReadLine(byte_17ABD00, &v19);
    if ( ++v3 >= 6 )
      v4 = (gbVec3D *)&this->m_vecEnemyLineup[v3 + 2];
    else
      v4 = (gbVec3D *)&this->m_vecInitFiveLineup[v3];
    v5 = y;
    v4->x = v17;
    v6 = v19;
    v4->y = v5;
    v4->z = v6;
    if ( v3 == 6 )
    {
      ((CIniFile *)&v16)->ReadStart();
      ((CIniFile *)&v16)->ReadSection(aFivelineup);
      ((CIniFile *)&v16)->ReadLine(asc_5D8B80, &v17);
      ((CIniFile *)&v16)->ReadLine("z", &v19);
      v7 = y;
      v8 = v19;
      this->m_vecInitFiveLineup[6].x = v17;
      this->m_vecInitFiveLineup[6].y = v7;
      this->m_vecInitFiveLineup[6].z = v8;
    }
    ++v2;
  }
  while ( v2 < 11 );
  x = this->m_vecInitFiveLineup[3].x;
  v10 = this->m_vecInitFiveLineup[4].x;
  z = this->m_vecInitFiveLineup[4].z;
  y = this->m_vecInitFiveLineup[4].y;
  v17 = v10;
  this->m_vecInitFiveLineup[4].x = x;
  v12 = this->m_vecInitFiveLineup[3].y;
  v13 = y;
  v19 = z;
  this->m_vecInitFiveLineup[4].y = v12;
  v14 = v19;
  this->m_vecInitFiveLineup[4].z = this->m_vecInitFiveLineup[3].z;
  this->m_vecInitFiveLineup[3].x = v10;
  this->m_vecInitFiveLineup[3].z = v14;
  this->m_vecInitFiveLineup[3].y = v13;
  v20 = -1;
  ((CIniFile *)&v16)->~CIniFile();
  return 1;
}

// 0x00511970
char CCBStageScene::ShowAxis()
{
  __int32 z_low; // eax
  float x; // ecx
  float y; // eax
  CIniFile v6; // [esp+5Ch] [ebp-14h] BYREF
  int v7; // [esp+6Ch] [ebp-4h]

  ((CIniFile *)&v6)->CIniFile();
  v7 = 0;
  ((CIniFile *)&v6)->OpenFileRead(aDatascriptComb_1);
  ((CIniFile *)&v6)->ReadSection(aFivelineup);
  ((CIniFile *)&v6)->ReadLine(asc_5D8B80, &this->m_EnemyFiveLineupQuad.vec[0].z);
  ((CIniFile *)&v6)->ReadLine("y", &this->m_EnemyFiveLineupQuad.vec[1].x);
  ((CIniFile *)&v6)->ReadLine("z", &this->m_EnemyFiveLineupQuad.vec[1].y);
  ((CIniFile *)&v6)->ReadLine(aRadius, &this->m_EnemyFiveLineupQuad.vec[2].x);
  this->m_EnemyFiveLineupQuad.vec[1].z = this->m_EnemyFiveLineupQuad.vec[2].x;
  ((CIniFile *)&v6)->ReadLine(aRoll, &this->m_EnemyFiveLineupQuad.vec[2].z);
  z_low = LODWORD(this->m_EnemyFiveLineupQuad.vec[0].z);
  this->m_EnemyFiveLineupQuad.vec[2].y = this->m_EnemyFiveLineupQuad.vec[2].z;
  x = this->m_EnemyFiveLineupQuad.vec[1].x;
  this->m_FiveLineupCenterQuad.color.Color = z_low;
  y = this->m_EnemyFiveLineupQuad.vec[1].y;
  this->m_EnemyFiveLineupQuad.vec[0].x = x;
  this->m_EnemyFiveLineupQuad.vec[0].y = y;
  ((CIniFile *)&v6)->ReadSection(aEnemyfivelineu);
  ((CIniFile *)&v6)->ReadLine(asc_5D8B80, &this->m_EnemyFiveLineupQuad.vec[3].x);
  ((CIniFile *)&v6)->ReadLine("y", &this->m_EnemyFiveLineupQuad.vec[3].y);
  ((CIniFile *)&v6)->ReadLine("z", &this->m_EnemyFiveLineupQuad.vec[3].z);
  ((CIniFile *)&v6)->ReadLine(aRadius, &this->m_EnemyFiveLineupQuad.su);
  ((CIniFile *)&v6)->ReadLine(aRoll, &this->m_EnemyFiveLineupQuad.sv);
  v7 = -1;
  ((CIniFile *)&v6)->~CIniFile();
  return 1;
}

// 0x00511AE0
char CCBStageScene::ShowRoleIndex()
{
  CIniFile v3; // [esp+30h] [ebp-14h] BYREF
  int v4; // [esp+40h] [ebp-4h]

  if ( (g_nGameFlags & 2) == 0 )
  {
    ((CIniFile *)&v3)->CIniFile();
    v4 = 0;
    ((CIniFile *)&v3)->OpenFileWrite(aDatascriptComb_1);
    ((CIniFile *)&v3)->WriteSection(aFivelineup);
    ((CIniFile *)&v3)->WriteLine(asc_5D8B80, *(float *)&this->m_FiveLineupCenterQuad.color.Color);
    ((CIniFile *)&v3)->WriteLine("y", this->m_EnemyFiveLineupQuad.vec[0].x);
    ((CIniFile *)&v3)->WriteLine("z", this->m_EnemyFiveLineupQuad.vec[0].y);
    ((CIniFile *)&v3)->WriteLine(aRadius, this->m_EnemyFiveLineupQuad.vec[1].z);
    ((CIniFile *)&v3)->WriteLine(aRoll, this->m_EnemyFiveLineupQuad.vec[2].y);
    v4 = -1;
    ((CIniFile *)&v3)->~CIniFile();
  }
  return 1;
}

// 0x00511C00
// attributes: thunk
int CCBStageScene::ShowEnemyFiveLineupEx()
{
  return CCBStageScene::IsFiveLineupUnderMouse();
}

// 0x00511C10
int CCBStageScene::IsFiveLineupUnderMouse()
{
  *(_DWORD *)&byte_17ABF00[1644] = 1094713344;
  return 1094713344;
}

// 0x00511C20
// attributes: thunk
void CCBStageScene::ResetFiveLineupToInit()
{
  CCBStageScene::ResetRolePosToInit();
}

// 0x00511C30
void CCBStageScene::ResetRolePosToInit()
{
  *(float *)&byte_17ABF00[1640] = 12.0 + 12.0;
}

// 0x00511C40
// attributes: thunk
int CCBStageScene::LoadScene()
{
  return CCBStageScene::DestroyScene();
}

// 0x00511C50
int CCBStageScene::DestroyScene()
{
  *(_DWORD *)&byte_17ABF00[1652] = 119;
  *(_DWORD *)&byte_17ABF00[1656] = 314;
  *(_DWORD *)&byte_17ABF00[1660] = 510;
  *(_DWORD *)&byte_17ABF00[1664] = 707;
  return 707;
}

// 0x00511C90
// attributes: thunk
int CCBStageScene::SaveRolePos()
{
  return sub_511CA0();
}

// 0x00511CE0
// attributes: thunk
int CCBStageScene::LoadFiveLineupData()
{
  return CCBStageScene::SaveFiveLineupDate();
}

// 0x00511CF0
int CCBStageScene::SaveFiveLineupDate()
{
  *(_DWORD *)&byte_17ABF00[1684] = 128;
  *(_DWORD *)&byte_17ABF00[1688] = 323;
  *(_DWORD *)&byte_17ABF00[1692] = 519;
  *(_DWORD *)&byte_17ABF00[1696] = 716;
  return 716;
}
