#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageScene.h"

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
  *(_DWORD *)&this->m_pStage[948] = 0;
  *(_DWORD *)&this->m_pStage[952] = 0;
  *(_DWORD *)&this->m_pStage[956] = 0;
  this->m_pStage[961] = 1;
  this->m_pStage[962] = 1;
  this->m_pStage[963] = 1;
  *(_DWORD *)&this->m_pStage[968] = 0;
  this->m_pStage[960] = 0;
  this->m_pStage[964] = 0;
  *(_DWORD *)&this->m_pStage[732] = 0;
  *(_DWORD *)&this->m_pStage[736] = 0;
  *(_DWORD *)&this->m_pStage[740] = 1065353216;
  *(_DWORD *)&this->m_pStage[744] = 1065353216;
  *(_DWORD *)&this->m_pStage[868] = 0;
  *(_DWORD *)&this->m_pStage[872] = 0;
  *(_DWORD *)&this->m_pStage[876] = 1065353216;
  *(_DWORD *)&this->m_pStage[880] = 1065353216;
  *(_DWORD *)&this->m_pStage[800] = 0;
  *(_DWORD *)&this->m_pStage[804] = 0;
  *(_DWORD *)&this->m_pStage[808] = 1065353216;
  *(_DWORD *)&this->m_pStage[812] = 1065353216;
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
  CCBStageScene::Render((int)this);
  CCBStageScene::ShowAxis((int)this);
  this->m_pFling = (gbGeomNode *)gbEffectMgr::NewRenderEffect(
                                   *(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200),
                                   aGfxscriptAddit_1,
                                   0);
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
      (Logger *->FormatException()ArgList, aCouldnTCreateT, aDProjectPal3Co_1, 135),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->Create();
  return 1;
}

// 0x005100D0
CCBStageScene::~CCBStageScene(int _this)
{
  void (***v2)(_DWORD, int); // ecx
  void (***v3)(_DWORD, int); // ecx
  void (***v4)(_DWORD, int); // ecx
  _DWORD *v5; // esi
  int v6; // edi

  sub_511630(this);
  gbRefObject::Release(*(gbRefObject **)(this + 668));
  gbRefObject::Release(*(gbRefObject **)(this + 664));
  if ( *(_DWORD *)(this + 672) )
  {
    operator delete(*(void **)(this + 672));
    *(_DWORD *)(this + 672) = 0;
  }
  v2 = *(void (****)(_DWORD, int))(this + 616);
  if ( v2 )
  {
    (**v2)(v2, 1);
    *(_DWORD *)(this + 616) = 0;
  }
  v3 = *(void (****)(_DWORD, int))(this + 604);
  if ( v3 )
  {
    (**v3)(v3, 1);
    *(_DWORD *)(this + 604) = 0;
  }
  v4 = *(void (****)(_DWORD, int))(this + 608);
  if ( v4 )
  {
    (**v4)(v4, 1);
    *(_DWORD *)(this + 608) = 0;
  }
  v5 = (_DWORD *)(this + 620);
  v6 = 11;
  do
  {
    if ( *v5 )
    {
      (**(void (***)(_DWORD, int))*v5)(*v5, 1);
      *v5 = 0;
    }
    ++v5;
    --v6;
  }
  while ( v6 );
  return 1;
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
  v5 = m_pStage->m_pCBSystem->m_pRoleState->CheckDeath(this->m_EnemyFiveLineupQuad.color.Red);
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
      (Logger *->FormatException()ArgList, aCNewFailed, aDProjectPal3Co_1, 293),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return v4->LoadFromFile(aUiCombatPointe, 0, 0);
}

// 0x00510610
void CCBStageScene::Destroy(CCBStageScene **this)
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
    if ( m_pCamControl->m_Role[0].sModel[v2 + 5] )
    {
      v5 = *(_DWORD *)(m_pCamControl->InitUI(a2) + 540);
      if ( v5 )
      {
        SkillNum = PAL_GDB::GDB_GetSkillNum(&g_GDB, v5);
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
              (Logger *->FormatException()ArgList, aCNewFailed, aDProjectPal3Co_1, 330),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          sprintf(v11, "item\\%s\\%s.pol", (const char *)(SkillNum + 36), (const char *)(SkillNum + 36));
          if ( !gbGeomNode::LoadFromFile(*v3, v11, 0, 0) )
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
          gbGeomNode::ReplaceTexture(*v3, v11);
          v1 = this;
        }
      }
    }
    v2 += 892;
    ++v3;
    ++a2;
  }
  while ( v2 < 9812 );
}

// 0x005107C0
int CCBStageScene::Init(int _this)
{
  double v1; // st7
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
  double v26; // st7
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
  float v51; // [esp+Ch] [ebp-10h]
  float v52; // [esp+10h] [ebp-Ch]
  float v53; // [esp+10h] [ebp-Ch]
  float v54; // [esp+14h] [ebp-8h]
  float v55; // [esp+18h] [ebp-4h]
  float v56; // [esp+18h] [ebp-4h]

  v1 = *(float *)(this + 912);
  v52 = *(float *)(this + 888);
  v51 = *(float *)(this + 896);
  v47 = sin(*(float *)(this + 920));
  v3 = cos(*(float *)(this + 920));
  *(_DWORD *)(this + 756) = 0;
  v49 = v3;
  v54 = v1 * 0.5;
  v4 = v52 - v54;
  *(float *)(this + 752) = v4;
  v5 = v51 - v54;
  *(float *)(this + 760) = v5;
  *(_DWORD *)(this + 768) = 0;
  v55 = v54 + v52;
  *(float *)(this + 764) = v55;
  *(float *)(this + 772) = v5;
  *(float *)(this + 776) = v55;
  *(_DWORD *)(this + 780) = 0;
  v56 = v54 + v51;
  *(float *)(this + 784) = v56;
  *(_DWORD *)(this + 792) = 0;
  *(float *)(this + 788) = v4;
  *(float *)(this + 796) = v56;
  *(_DWORD *)(this + 688) = 0;
  *(float *)(this + 684) = -v1;
  *(float *)(this + 692) = -v1;
  *(_DWORD *)(this + 700) = 0;
  *(float *)(this + 696) = v1;
  *(float *)(this + 704) = -v1;
  *(_DWORD *)(this + 712) = 0;
  *(float *)(this + 708) = v1;
  *(float *)(this + 716) = v1;
  *(_DWORD *)(this + 724) = 0;
  *(float *)(this + 720) = -v1;
  *(float *)(this + 728) = v1;
  v6 = v49 * *(float *)(this + 692) - v47 * *(float *)(this + 684);
  v7 = v47 * *(float *)(this + 692);
  v8 = v49 * *(float *)(this + 684);
  *(_DWORD *)(this + 688) = 0;
  *(float *)(this + 684) = v7 + v8;
  *(float *)(this + 692) = v6;
  v9 = v49 * *(float *)(this + 704) - v47 * *(float *)(this + 696);
  v10 = v47 * *(float *)(this + 704);
  v11 = v49 * *(float *)(this + 696);
  *(_DWORD *)(this + 700) = 0;
  *(float *)(this + 696) = v10 + v11;
  *(float *)(this + 704) = v9;
  v12 = v49 * *(float *)(this + 716) - v47 * *(float *)(this + 708);
  v13 = v49 * *(float *)(this + 708);
  v14 = v47 * *(float *)(this + 716);
  *(_DWORD *)(this + 712) = 0;
  *(float *)(this + 708) = v13 + v14;
  *(float *)(this + 716) = v12;
  v15 = v49 * *(float *)(this + 728) - v47 * *(float *)(this + 720);
  v16 = v47 * *(float *)(this + 728);
  v17 = v49 * *(float *)(this + 720);
  *(_DWORD *)(this + 724) = 0;
  *(float *)(this + 720) = v16 + v17;
  *(float *)(this + 728) = v15;
  v18 = v51 + *(float *)(this + 692);
  v19 = v52 + *(float *)(this + 684);
  *(_DWORD *)(this + 688) = 1056964608;
  *(float *)(this + 684) = v19;
  *(float *)(this + 692) = v18;
  v20 = v51 + *(float *)(this + 704);
  v21 = v52 + *(float *)(this + 696);
  *(_DWORD *)(this + 700) = 1056964608;
  *(float *)(this + 696) = v21;
  *(float *)(this + 704) = v20;
  v22 = v51 + *(float *)(this + 716);
  v23 = v52 + *(float *)(this + 708);
  *(_DWORD *)(this + 712) = 1056964608;
  *(float *)(this + 708) = v23;
  *(float *)(this + 716) = v22;
  v24 = v51 + *(float *)(this + 728);
  v25 = v52 + *(float *)(this + 720);
  *(_DWORD *)(this + 724) = 1056964608;
  *(float *)(this + 720) = v25;
  *(float *)(this + 728) = v24;
  v26 = *(float *)(this + 940);
  v48 = sin(*(float *)(this + 944));
  v50 = cos(*(float *)(this + 944));
  v53 = *(float *)(this + 928);
  v27 = *(float *)(this + 936);
  *(float *)(this + 820) = -v26;
  *(float *)(this + 828) = -v26;
  *(_DWORD *)(this + 824) = 0;
  *(_DWORD *)(this + 836) = 0;
  *(float *)(this + 832) = v26;
  *(float *)(this + 840) = -v26;
  *(_DWORD *)(this + 848) = 0;
  *(float *)(this + 844) = v26;
  *(float *)(this + 852) = v26;
  *(_DWORD *)(this + 860) = 0;
  *(float *)(this + 856) = -v26;
  *(float *)(this + 864) = v26;
  v28 = v50 * *(float *)(this + 828) - v48 * *(float *)(this + 820);
  v29 = v50 * *(float *)(this + 820);
  v30 = v48 * *(float *)(this + 828);
  *(_DWORD *)(this + 824) = 0;
  *(float *)(this + 820) = v29 + v30;
  *(float *)(this + 828) = v28;
  v31 = v50 * *(float *)(this + 840) - v48 * *(float *)(this + 832);
  v32 = v48 * *(float *)(this + 840);
  v33 = v50 * *(float *)(this + 832);
  *(_DWORD *)(this + 836) = 0;
  *(float *)(this + 832) = v32 + v33;
  *(float *)(this + 840) = v31;
  v34 = v50 * *(float *)(this + 852) - v48 * *(float *)(this + 844);
  v35 = v50 * *(float *)(this + 844);
  v36 = v48 * *(float *)(this + 852);
  *(_DWORD *)(this + 848) = 0;
  *(float *)(this + 844) = v35 + v36;
  *(float *)(this + 852) = v34;
  v37 = v50 * *(float *)(this + 864) - v48 * *(float *)(this + 856);
  v38 = v48 * *(float *)(this + 864);
  v39 = v50 * *(float *)(this + 856);
  *(_DWORD *)(this + 860) = 0;
  *(float *)(this + 856) = v38 + v39;
  *(float *)(this + 864) = v37;
  v40 = v27 + *(float *)(this + 828);
  *(float *)(this + 820) = v53 + *(float *)(this + 820);
  *(_DWORD *)(this + 824) = 1056964608;
  *(float *)(this + 828) = v40;
  v41 = v27 + *(float *)(this + 840);
  v42 = v53 + *(float *)(this + 832);
  *(_DWORD *)(this + 836) = 1056964608;
  *(float *)(this + 832) = v42;
  *(float *)(this + 840) = v41;
  v43 = v27 + *(float *)(this + 852);
  v44 = v53 + *(float *)(this + 844);
  *(_DWORD *)(this + 848) = 1056964608;
  *(float *)(this + 844) = v44;
  *(float *)(this + 852) = v43;
  v45 = v27 + *(float *)(this + 864);
  v46 = v53 + *(float *)(this + 856);
  *(_DWORD *)(this + 860) = 1056964608;
  *(float *)(this + 856) = v46;
  *(float *)(this + 864) = v45;
  return 0;
}

// 0x00510C80
int CCBStageScene::SetBattleFieldAttr()
{
  int result; // eax
  gbGeomNode *m_pPointer; // ecx

  result = CCBStageScene::Init((int)this);
  m_pPointer = (gbGeomNode *)this->m_pPointer;
  if ( m_pPointer )
    return ((int (*)(gbGeomNode *))m_pPointer->next[5].next)(m_pPointer);
  return result;
}

// 0x00510CA0
void CCBStageScene::GetBattleFieldSubdueAttr(gbMatrixStack *a2)
{
  int v3; // ebp
  int v4; // ecx
  int v5; // ecx
  char *v7; // ebx
  long double v8; // st7
  float v9; // [esp+18h] [ebp-24h]
  float v10; // [esp+18h] [ebp-24h]
  float v11; // [esp+30h] [ebp-Ch]
  float v12; // [esp+34h] [ebp-8h]
  float v13; // [esp+38h] [ebp-4h]
  gbMatrixStack *a2a; // [esp+40h] [ebp+4h]

  v3 = 0;
  v4 = *(_DWORD *)&this->m_pStage[604];
  if ( v4 && this->m_pStage[344] )
  {
    (*(void (**)(int, _DWORD))(*(_DWORD *)v4 + 16))(v4, 0);
    v5 = *(_DWORD *)&this->m_pStage[612];
    if ( v5 )
      (*(void (**)(int, _DWORD))(*(_DWORD *)v5 + 16))(v5, 0);
    if ( this->m_pStage[960] && *(_DWORD *)&this->m_pStage[616] )
    {
      a2->Push();
      v9 = sin(*(float *)(**(_DWORD **)this->m_pStage + 80) * 10.0) * 5.0 + *(float *)&this->m_pStage[952] + 6.0;
      a2->Translate(*(float *)&this->m_pStage[948], v9, *(float *)&this->m_pStage[956]);
      (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)&this->m_pStage[616] + 16))(
        *(_DWORD *)&this->m_pStage[616],
        0);
      a2->Pop();
    }
    a2a = 0;
    v12 = *(float *)&this->m_pStage[892];
    v7 = (char *)&this->m_pStage[620];
    do
    {
      if ( v3 >= 5 )
      {
        if ( *(_DWORD *)v7 )
        {
          v8 = (double)(int)a2a * 0.017453292;
          v11 = sin(v8) * 20.0 + *(float *)&this->m_pStage[888];
          v13 = cos(v8) * 20.0 + *(float *)&this->m_pStage[896];
          a2->Push();
          v10 = v12 + 2.0;
          a2->Translate(v11, v10, v13);
          (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)v7 + 16))(*(_DWORD *)v7, 0);
          a2->Pop();
          a2a = (gbMatrixStack *)((char *)a2a + 60);
        }
      }
      ++v3;
      v7 += 4;
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
    v1 = (struct gbRenderEffect *)gbEffectMgr::NewTrivalEffect(*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200), 3);
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
    DynVertBuf = (struct gbDynVertBuf *)gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_Input.KeyInfo[177].Data + 196), 5u);
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
    gbColorQuad::gbColorQuad(&v8, &v9);
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
    gbColorQuad::gbColorQuad(&v8, &v9);
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
    gbColorQuad::gbColorQuad(&v8, &v9);
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
  char *v7; // [esp+Ch] [ebp-Ch]
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
      v7 = (char *)&m_pRoleState->m_Role[0].sModel[5];
      do
      {
        result = (char)v7;
        if ( *v7 )
        {
          inited = m_pRoleState->InitUI(v3);
          sprintf(byte_17ABF00, "%d(%s)", v3, (const char *)(inited + 8));
          (gbCamera *->PointWorldToScr()&this->m_pStage->m_pCam->OrthoSize,
            (struct gbVec3D *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + v4))->m_Thread[42].bExecuted,
            &v9,
            &v8);
          result = sub_4DFB70((char *)this->m_pStage->m_TempStorageNGH, byte_17ABF00, v9, v8, 16.0);
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
void CCBStageScene::LoadPointer(int _this, char a2)
{
  struct gbTextureArray *v3; // ecx
  struct gbRenderEffect *v4; // edx

  gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x15u);
  v3 = (struct gbTextureArray *)*(struct gbTextureArray **)(this + 672);
  v4 = (struct gbRenderEffect *)*(struct gbRenderEffect **)(this + 664);
  *(_BYTE *)(this + 750) = -1;
  *(_BYTE *)(this + 749) = -1;
  *(_BYTE *)(this + 748) = -1;
  *(_BYTE *)(this + 751) = a2;
  *(_BYTE *)(this + 819) = a2;
  (struct gbGeomQuad *->RenderGeomQuad()(this + 684), 1, v4, v3);
  (struct gbGeomQuad *->RenderGeomQuad()(this + 752),
    1,
    *(struct gbRenderEffect **)(this + 664),
    *(struct gbTextureArray **)(this + 680));
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
  gbVec3D::gbVec3D(&v15, 0.0, 0.0, 0.0);
  m_pStage = (CCBStage *)this->m_pStage;
  pPos = (Actor *)this->m_pStage->m_WPXVariance;
  LODWORD(v10.x) = m_pStage->m_pDisplayChain;
  v14 = *(gbRay *)(CameraCtrl *->GetViewTarget()m_pStage->m_pCam, pTarget, (float *)&pPos);
  v3 = gbRay::IntersectPlane(&v14, &v12, &v11);
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
  return gbVec3D::Length(&v10) < 30.0;
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
  CIniFile::CIniFile(&v5);
  v3 = 0;
  v6 = 0;
  CIniFile::OpenFileWrite(&v5, aDatascriptComb_1);
  CIniFile::WriteSection(&v5, aRolepos);
  for ( i = 24; i < 68; i += 4 )
  {
    sprintf(byte_17ABE00, "Role%d-x", v3);
    CIniFile::WriteLine(
      &v5,
      byte_17ABE00,
      *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[42].bExecuted);
    sprintf(byte_17ABE00, "Role%d-z", v3);
    CIniFile::WriteLine(
      &v5,
      byte_17ABE00,
      *(float *)&(*(CCBSystem **)((char *)&this->m_pStage->m_pCBSystem + i))->m_Thread[42].cmd.dwCmdID);
    ++v3;
  }
  v6 = -1;
  CIniFile::~CIniFile(&v5);
  return 1;
}

// 0x00511790
char CCBStageScene::Render(int _this)
{
  int v2; // ebp
  int v3; // edi
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // eax
  double v10; // st7
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  CIniFile v16; // [esp+2Ch] [ebp-20h] BYREF
  float v17; // [esp+34h] [ebp-18h] BYREF
  int v18; // [esp+38h] [ebp-14h]
  int v19; // [esp+3Ch] [ebp-10h] BYREF
  int v20; // [esp+48h] [ebp-4h]

  v17 = 0.0;
  v18 = 0;
  v19 = 0;
  v2 = 0;
  v3 = 0;
  CIniFile::CIniFile(&v16);
  v20 = 0;
  CIniFile::OpenFileRead(&v16, aDatascriptComb_1);
  do
  {
    CIniFile::ReadStart(&v16);
    CIniFile::ReadSection(&v16, aRolepos);
    sprintf(byte_17ABD00, "Role%d-x", v2);
    CIniFile::ReadLine(&v16, byte_17ABD00, &v17);
    v18 = 0;
    sprintf(byte_17ABD00, "Role%d-z", v2);
    CIniFile::ReadLine(&v16, byte_17ABD00, (float *)&v19);
    if ( ++v3 >= 6 )
      v4 = this + 12 * v3 + 200;
    else
      v4 = this + 12 * v3 + 92;
    v5 = v18;
    *(float *)v4 = v17;
    v6 = v19;
    *(_DWORD *)(v4 + 4) = v5;
    *(_DWORD *)(v4 + 8) = v6;
    if ( v3 == 6 )
    {
      CIniFile::ReadStart(&v16);
      CIniFile::ReadSection(&v16, aFivelineup);
      CIniFile::ReadLine(&v16, asc_5D8B80, &v17);
      CIniFile::ReadLine(&v16, "z", (float *)&v19);
      v7 = v18;
      v8 = v19;
      *(float *)(this + 164) = v17;
      *(_DWORD *)(this + 168) = v7;
      *(_DWORD *)(this + 172) = v8;
    }
    ++v2;
  }
  while ( v2 < 11 );
  v9 = *(_DWORD *)(this + 128);
  v10 = *(float *)(this + 140);
  v11 = *(_DWORD *)(this + 148);
  v18 = *(_DWORD *)(this + 144);
  v17 = v10;
  *(_DWORD *)(this + 140) = v9;
  v12 = *(_DWORD *)(this + 132);
  v13 = v18;
  v19 = v11;
  *(_DWORD *)(this + 144) = v12;
  v14 = v19;
  *(_DWORD *)(this + 148) = *(_DWORD *)(this + 136);
  *(float *)(this + 128) = v10;
  *(_DWORD *)(this + 136) = v14;
  *(_DWORD *)(this + 132) = v13;
  v20 = -1;
  CIniFile::~CIniFile(&v16);
  return 1;
}

// 0x00511970
char CCBStageScene::ShowAxis(int _this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  CIniFile v6; // [esp+5Ch] [ebp-14h] BYREF
  int v7; // [esp+6Ch] [ebp-4h]

  CIniFile::CIniFile(&v6);
  v7 = 0;
  CIniFile::OpenFileRead(&v6, aDatascriptComb_1);
  CIniFile::ReadSection(&v6, aFivelineup);
  CIniFile::ReadLine(&v6, asc_5D8B80, (float *)(this + 900));
  CIniFile::ReadLine(&v6, "y", (float *)(this + 904));
  CIniFile::ReadLine(&v6, "z", (float *)(this + 908));
  CIniFile::ReadLine(&v6, aRadius, (float *)(this + 916));
  *(_DWORD *)(this + 912) = *(_DWORD *)(this + 916);
  CIniFile::ReadLine(&v6, aRoll, (float *)(this + 924));
  v2 = *(_DWORD *)(this + 900);
  *(_DWORD *)(this + 920) = *(_DWORD *)(this + 924);
  v3 = *(_DWORD *)(this + 904);
  *(_DWORD *)(this + 888) = v2;
  v4 = *(_DWORD *)(this + 908);
  *(_DWORD *)(this + 892) = v3;
  *(_DWORD *)(this + 896) = v4;
  CIniFile::ReadSection(&v6, aEnemyfivelineu);
  CIniFile::ReadLine(&v6, asc_5D8B80, (float *)(this + 928));
  CIniFile::ReadLine(&v6, "y", (float *)(this + 932));
  CIniFile::ReadLine(&v6, "z", (float *)(this + 936));
  CIniFile::ReadLine(&v6, aRadius, (float *)(this + 940));
  CIniFile::ReadLine(&v6, aRoll, (float *)(this + 944));
  v7 = -1;
  CIniFile::~CIniFile(&v6);
  return 1;
}

// 0x00511AE0
char CCBStageScene::ShowRoleIndex()
{
  CIniFile v3; // [esp+30h] [ebp-14h] BYREF
  int v4; // [esp+40h] [ebp-4h]

  if ( (g_nGameFlags & 2) == 0 )
  {
    CIniFile::CIniFile(&v3);
    v4 = 0;
    CIniFile::OpenFileWrite(&v3, aDatascriptComb_1);
    CIniFile::WriteSection(&v3, aFivelineup);
    CIniFile::WriteLine(&v3, asc_5D8B80, *(float *)&this->m_FiveLineupCenterQuad.color.Color);
    CIniFile::WriteLine(&v3, "y", this->m_EnemyFiveLineupQuad.vec[0].x);
    CIniFile::WriteLine(&v3, "z", this->m_EnemyFiveLineupQuad.vec[0].y);
    CIniFile::WriteLine(&v3, aRadius, this->m_EnemyFiveLineupQuad.vec[1].z);
    CIniFile::WriteLine(&v3, aRoll, this->m_EnemyFiveLineupQuad.vec[2].y);
    v4 = -1;
    CIniFile::~CIniFile(&v3);
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
