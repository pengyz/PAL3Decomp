#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageScene.h"

// Forward declarations for unnamed functions
int sub_4DFB70(...);
int sub_50FEE0(...);
int sub_5100D0(...);
int sub_510180(...);
int sub_510540(...);
int sub_510610(...);
int sub_5107C0(...);
int sub_510C80(...);
int sub_510E00(...);
int sub_510F50(...);
int sub_511030(...);
int sub_511110(...);
int sub_5112B0(...);
int sub_5112F0(...);
int sub_511340(...);
int sub_511630(...);
int sub_511690(...);
int sub_511790(...);
int sub_511970(...);
int sub_511AE0(...);
int sub_511C10(...);
int sub_511C30(...);
int sub_511C50(...);
int sub_511CA0(...);
int sub_511CF0(...);

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
char sub_50FEE0()
{
  gbTexture *v2; // eax
  _DWORD *v3; // eax
  int v4; // ecx
  gbTexture *v5; // eax
  _DWORD *v6; // eax
  int v7; // ecx
  char pExceptionObject[1024]; // [esp+18h] [ebp-800h] BYREF
  char ArgList; // [esp+418h] [ebp-400h] BYREF

  CCBStageScene::Update((int)this);
  *((_DWORD *)this + 5) = -1025769472;
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 7) = -1023279104;
  *((_DWORD *)this + 8) = 1106247680;
  *((_DWORD *)this + 10) = -1025769472;
  *((_DWORD *)this + 9) = 0;
  *((_DWORD *)this + 11) = -1025769472;
  *((_DWORD *)this + 12) = 0;
  *((_DWORD *)this + 13) = 1106247680;
  *((_DWORD *)this + 14) = 1106247680;
  *((_DWORD *)this + 15) = 0;
  *((_DWORD *)this + 16) = 1092616192;
  *((_DWORD *)this + 17) = -1021968384;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 19) = -1035468800;
  *((_DWORD *)this + 20) = -1035468800;
  *((_DWORD *)this + 22) = -1035468800;
  *((_DWORD *)this + 21) = 0;
  *((_DWORD *)this + 47) = 1124859904;
  *((_DWORD *)this + 48) = 0;
  *((_DWORD *)this + 49) = 1123024896;
  *((_DWORD *)this + 50) = 1133248512;
  *((_DWORD *)this + 51) = 0;
  *((_DWORD *)this + 52) = 1124859904;
  *((_DWORD *)this + 53) = 1124859904;
  *((_DWORD *)this + 54) = 0;
  *((_DWORD *)this + 55) = 1133248512;
  *((_DWORD *)this + 56) = 1133248512;
  *((_DWORD *)this + 57) = 0;
  *((_DWORD *)this + 58) = 1132593152;
  *((_DWORD *)this + 59) = 1120403456;
  *((_DWORD *)this + 60) = 0;
  *((_DWORD *)this + 61) = 1128792064;
  *((_DWORD *)this + 62) = 1128792064;
  *((_DWORD *)this + 63) = 0;
  *((_DWORD *)this + 64) = 1128792064;
  this->Render();
  this->ShowAxis();
  *((_DWORD *)this + 166) = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)(g_pGfxManager + 200), aGfxscriptAddit_1, 0);
  v2 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      aCbsceneFivelin);
  *((_DWORD *)this + 167) = v2;
  v2->LoadTexture(1);
  v3 = operator new(0x44u);
  if ( v3 )
  {
    v4 = *((_DWORD *)this + 167);
    v3[16] = 1;
    *v3 = v4;
  }
  else
  {
    v3 = 0;
  }
  *((_DWORD *)this + 168) = v3;
  v5 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      aCbsceneFivelin_0);
  *((_DWORD *)this + 169) = v5;
  v5->LoadTexture(1);
  v6 = operator new(0x44u);
  if ( v6 )
  {
    v7 = *((_DWORD *)this + 169);
    v6[16] = 1;
    *v6 = v7;
  }
  else
  {
    v6 = 0;
  }
  *((_DWORD *)this + 170) = v6;
  if ( !v6 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCouldnTCreateT, (int)aDProjectPal3Co_1, 135),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->Create();
  return 1;
}

// 0x005100D0
char sub_5100D0(int _this)
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
char sub_510180()
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  _DWORD *v6; // esi
  int v7; // edi

  CCBStageScene::Update((int)this);
  this->SetFlingRotX();
  this->SetFlingRotY();
  v2 = *(_DWORD *)(*(_DWORD *)*this + 112);
  v3 = *(_DWORD *)(v2 + 64);
  *((_DWORD *)this + 242) = v3;
  switch ( v3 )
  {
    case 1:
      *((_DWORD *)this + 204) = 2134481581;
      break;
    case 2:
      *((_DWORD *)this + 204) = 2145285425;
      break;
    case 3:
      *((_DWORD *)this + 204) = 2136127083;
      break;
    case 4:
      *((_DWORD *)this + 204) = 2145285565;
      break;
    case 5:
      *((_DWORD *)this + 204) = 2144775770;
      break;
    default:
      break;
  }
  v4 = CCBRoleState::CheckDeath(*((_DWORD *)this + 242));
  *((_DWORD *)this + 20) = *((_DWORD *)this + 41);
  *((_DWORD *)this + 21) = *((_DWORD *)this + 42);
  *((_DWORD *)this + 22) = *((_DWORD *)this + 43);
  switch ( v4 )
  {
    case 1:
      *((float *)this + 230) = *((float *)this + 230) + 1.256636;
      *((_DWORD *)this + 5) = *((_DWORD *)this + 38);
      *((_DWORD *)this + 6) = *((_DWORD *)this + 39);
      *((_DWORD *)this + 7) = *((_DWORD *)this + 40);
      *((_DWORD *)this + 17) = *((_DWORD *)this + 32);
      *((_DWORD *)this + 18) = *((_DWORD *)this + 33);
      *((_DWORD *)this + 19) = *((_DWORD *)this + 34);
      *((_DWORD *)this + 11) = *((_DWORD *)this + 35);
      *((_DWORD *)this + 12) = *((_DWORD *)this + 36);
      *((_DWORD *)this + 13) = *((_DWORD *)this + 37);
      *((_DWORD *)this + 14) = *((_DWORD *)this + 29);
      *((_DWORD *)this + 15) = *((_DWORD *)this + 30);
      *((_DWORD *)this + 16) = *((_DWORD *)this + 31);
      *((_DWORD *)this + 8) = *((_DWORD *)this + 26);
      *((_DWORD *)this + 9) = *((_DWORD *)this + 27);
      v5 = *((_DWORD *)this + 28);
      goto LABEL_13;
    case 2:
      *((float *)this + 230) = *((float *)this + 230) + 2.513272;
      *((_DWORD *)this + 5) = *((_DWORD *)this + 32);
      *((_DWORD *)this + 6) = *((_DWORD *)this + 33);
      *((_DWORD *)this + 7) = *((_DWORD *)this + 34);
      *((_DWORD *)this + 17) = *((_DWORD *)this + 35);
      *((_DWORD *)this + 18) = *((_DWORD *)this + 36);
      *((_DWORD *)this + 19) = *((_DWORD *)this + 37);
      *((_DWORD *)this + 11) = *((_DWORD *)this + 29);
      *((_DWORD *)this + 12) = *((_DWORD *)this + 30);
      *((_DWORD *)this + 13) = *((_DWORD *)this + 31);
      *((_DWORD *)this + 14) = *((_DWORD *)this + 26);
      *((_DWORD *)this + 15) = *((_DWORD *)this + 27);
      *((_DWORD *)this + 16) = *((_DWORD *)this + 28);
      *((_DWORD *)this + 8) = *((_DWORD *)this + 38);
      *((_DWORD *)this + 9) = *((_DWORD *)this + 39);
      v5 = *((_DWORD *)this + 40);
      goto LABEL_13;
    case 3:
      *((float *)this + 230) = *((float *)this + 230) + 5.0265441;
      *((_DWORD *)this + 5) = *((_DWORD *)this + 29);
      *((_DWORD *)this + 6) = *((_DWORD *)this + 30);
      *((_DWORD *)this + 7) = *((_DWORD *)this + 31);
      *((_DWORD *)this + 17) = *((_DWORD *)this + 26);
      *((_DWORD *)this + 18) = *((_DWORD *)this + 27);
      *((_DWORD *)this + 19) = *((_DWORD *)this + 28);
      *((_DWORD *)this + 11) = *((_DWORD *)this + 38);
      *((_DWORD *)this + 12) = *((_DWORD *)this + 39);
      *((_DWORD *)this + 13) = *((_DWORD *)this + 40);
      *((_DWORD *)this + 14) = *((_DWORD *)this + 32);
      *((_DWORD *)this + 15) = *((_DWORD *)this + 33);
      *((_DWORD *)this + 16) = *((_DWORD *)this + 34);
      *((_DWORD *)this + 8) = *((_DWORD *)this + 35);
      *((_DWORD *)this + 9) = *((_DWORD *)this + 36);
      v5 = *((_DWORD *)this + 37);
      goto LABEL_13;
    case 4:
      *((float *)this + 230) = *((float *)this + 230) + 3.769908;
      *((_DWORD *)this + 5) = *((_DWORD *)this + 35);
      *((_DWORD *)this + 6) = *((_DWORD *)this + 36);
      *((_DWORD *)this + 7) = *((_DWORD *)this + 37);
      *((_DWORD *)this + 17) = *((_DWORD *)this + 29);
      *((_DWORD *)this + 18) = *((_DWORD *)this + 30);
      *((_DWORD *)this + 19) = *((_DWORD *)this + 31);
      *((_DWORD *)this + 11) = *((_DWORD *)this + 26);
      *((_DWORD *)this + 12) = *((_DWORD *)this + 27);
      *((_DWORD *)this + 13) = *((_DWORD *)this + 28);
      *((_DWORD *)this + 14) = *((_DWORD *)this + 38);
      *((_DWORD *)this + 15) = *((_DWORD *)this + 39);
      *((_DWORD *)this + 16) = *((_DWORD *)this + 40);
      *((_DWORD *)this + 8) = *((_DWORD *)this + 32);
      *((_DWORD *)this + 9) = *((_DWORD *)this + 33);
      v5 = *((_DWORD *)this + 34);
      goto LABEL_13;
    case 5:
      *((_DWORD *)this + 5) = *((_DWORD *)this + 26);
      *((_DWORD *)this + 6) = *((_DWORD *)this + 27);
      *((_DWORD *)this + 7) = *((_DWORD *)this + 28);
      *((_DWORD *)this + 17) = *((_DWORD *)this + 38);
      *((_DWORD *)this + 18) = *((_DWORD *)this + 39);
      *((_DWORD *)this + 19) = *((_DWORD *)this + 40);
      *((_DWORD *)this + 11) = *((_DWORD *)this + 32);
      *((_DWORD *)this + 12) = *((_DWORD *)this + 33);
      *((_DWORD *)this + 13) = *((_DWORD *)this + 34);
      *((_DWORD *)this + 14) = *((_DWORD *)this + 35);
      *((_DWORD *)this + 15) = *((_DWORD *)this + 36);
      *((_DWORD *)this + 16) = *((_DWORD *)this + 37);
      *((_DWORD *)this + 8) = *((_DWORD *)this + 29);
      *((_DWORD *)this + 9) = *((_DWORD *)this + 30);
      v5 = *((_DWORD *)this + 31);
LABEL_13:
      *((_DWORD *)this + 10) = v5;
      break;
    default:
      break;
  }
  if ( strlen((const char *)(v2 + 32)) )
    sub_511340(v2 + 32);
  else
    sub_511340(aZ27);
  v6 = this + 155;
  v7 = 11;
  do
  {
    if ( *v6 )
    {
      (**(void (***)(_DWORD, int))*v6)(*v6, 1);
      *v6 = 0;
    }
    ++v6;
    --v7;
  }
  while ( v7 );
  return 1;
}

// 0x00510540
int sub_510540()
{
  gbGeomNode *v2; // eax
  gbGeomNode *v3; // esi
  gbGeomNode *v4; // ecx
  char pExceptionObject[1024]; // [esp+Ch] [ebp-80Ch] BYREF
  char ArgList; // [esp+40Ch] [ebp-40Ch] BYREF
  int v8; // [esp+814h] [ebp-4h]

  v2 = (gbGeomNode *)operator new(0x118u);
  v3 = v2;
  v8 = 0;
  if ( v2 )
  {
    v2->gbGeomNode();
    *(_DWORD *)v3->gbVisNode = &off_56A66C;
    v4 = v3;
  }
  else
  {
    v4 = 0;
  }
  v8 = -1;
  *((_DWORD *)this + 154) = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_1, 293),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return v4->LoadFromFile(aUiCombatPointe, 0, 0);
}

// 0x00510610
void sub_510610(gbGeomNode **this)
{
  gbGeomNode **v1; // esi
  int v2; // ebx
  gbGeomNode **v3; // edi
  void *v4; // ecx
  int v5; // eax
  int v6; // ebp
  gbGeomNode *v7; // eax
  gbGeomNode *v8; // esi
  int v9; // [esp+18h] [ebp-918h]
  char v11[256]; // [esp+24h] [ebp-90Ch] BYREF
  char pExceptionObject[1024]; // [esp+124h] [ebp-80Ch] BYREF
  char ArgList; // [esp+524h] [ebp-40Ch] BYREF
  int v14; // [esp+92Ch] [ebp-4h]

  v1 = this;
  v2 = 0;
  v9 = 0;
  v3 = this + 155;
  do
  {
    if ( *v3 )
    {
      (**(void (***)(gbGeomNode *, int))(*v3)->gbVisNode)(*v3, 1);
      *v3 = 0;
    }
    v4 = *(void **)(*(_DWORD *)(*v1)->gbVisNode + 16);
    if ( *((_BYTE *)v4 + v2 + 577) )
    {
      v5 = *(_DWORD *)(v4->InitUI(v9) + 540);
      if ( v5 )
      {
        v6 = g_GDB->GDB_GetSkillNum(v5);
        if ( v6 )
        {
          v7 = (gbGeomNode *)operator new(0x118u);
          v8 = v7;
          v14 = 0;
          if ( v7 )
          {
            v7->gbGeomNode();
            *(_DWORD *)v8->gbVisNode = &off_56A66C;
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
              (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_1, 330),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          sprintf(v11, "item\\%s\\%s.pol", (const char *)(v6 + 36), (const char *)(v6 + 36));
          if ( !gbGeomNode::LoadFromFile(*v3, v11, 0, 0) )
          {
            if ( *v3 )
            {
              (**(void (***)(gbGeomNode *, int))(*v3)->gbVisNode)(*v3, 1);
              *v3 = 0;
            }
          }
          sprintf(v11, "item\\%s\\%s%s.tga", (const char *)(v6 + 36), (const char *)(v6 + 36), (const char *)(v6 + 66));
          gbGeomNode::ReplaceTexture(*v3, v11);
          v1 = this;
        }
      }
    }
    v2 += 892;
    ++v3;
    ++v9;
  }
  while ( v2 < 9812 );
}

// 0x005107C0
int sub_5107C0(int _this)
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
int sub_510C80()
{
  int result; // eax
  int v3; // ecx

  result = CCBStageScene::Init((int)this);
  v3 = *((_DWORD *)this + 154);
  if ( v3 )
    return (*(int (**)(int))(*(_DWORD *)v3 + 20))(v3);
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
    v7 = &this->m_pStage[620];
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
void sub_510E00()
{
  gbRefObject *v1; // esi
  gbVec3D *v2; // edi
  int v3; // ebp
  struct gbDynVertBuf *DynVertBuf; // eax
  struct gbDynVertBuf *v5; // edi
  _DWORD *v6; // ecx
  _DWORD *v7; // ecx
  _DWORD *v8; // [esp+10h] [ebp-3Ch] BYREF
  _DWORD *v9; // [esp+14h] [ebp-38h]
  int v10; // [esp+18h] [ebp-34h]
  gbRefObject *v11; // [esp+1Ch] [ebp-30h]
  _BYTE v12[3]; // [esp+30h] [ebp-1Ch] BYREF
  char v13; // [esp+33h] [ebp-19h]
  _DWORD v14[3]; // [esp+34h] [ebp-18h] BYREF
  int v15; // [esp+40h] [ebp-Ch]
  int v16; // [esp+44h] [ebp-8h]
  int v17; // [esp+48h] [ebp-4h]

  if ( g_pGfxManager && *((_DWORD *)this + 961) )
  {
    v1 = (gbRefObject *)gbEffectMgr::NewTrivalEffect(*(gbEffectMgr **)(g_pGfxManager + 200), 3);
    v13 = 80;
    v2 = (gbVec3D *)v14;
    v3 = 2;
    do
    {
      gbVec3D::`default constructor closure'(v2);
      v2 = (gbVec3D *)((char *)v2 + 12);
      --v3;
    }
    while ( v3 );
    memset(v14, 0, sizeof(v14));
    DynVertBuf = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 5u);
    v11 = v1;
    v10 = 2;
    v9 = v14;
    v8 = v14;
    v5 = DynVertBuf;
    *(_WORD *)v12 = 255;
    v12[2] = 0;
    v16 = 0;
    v15 = 0;
    v17 = 1176256512;
    (gbColorQuad *->gbColorQuad()&v8, (struct gbColorQuad *)v12);
    v5->RenderLineStrip();
    v11 = v1;
    v10 = 2;
    v9 = v14;
    v8 = v6;
    v12[0] = 0;
    *(_WORD *)&v12[1] = -256;
    v17 = 0;
    v16 = 0;
    v15 = 1176256512;
    (gbColorQuad *->gbColorQuad()&v8, (struct gbColorQuad *)v12);
    v5->RenderLineStrip();
    v11 = v1;
    v10 = 2;
    v9 = v14;
    v8 = v7;
    *(_WORD *)v12 = -256;
    v12[2] = 0;
    v17 = 0;
    v15 = 0;
    v16 = 1176256512;
    (gbColorQuad *->gbColorQuad()&v8, (struct gbColorQuad *)v12);
    v5->RenderLineStrip();
    v1->Release();
  }
}

// 0x00510F50
char sub_510F50()
{
  char result; // al
  int v3; // esi
  int v4; // edi
  char *v5; // ebp
  int v6; // eax
  _BYTE *v7; // [esp+Ch] [ebp-Ch]
  float v8; // [esp+10h] [ebp-8h] BYREF
  float v9; // [esp+14h] [ebp-4h] BYREF

  result = g_pGfxManager;
  v9 = 0.0;
  v8 = 0.0;
  if ( g_pGfxManager )
  {
    result = *((_DWORD *)this + 962);
    if ( result )
    {
      v3 = 0;
      v4 = 24;
      v5 = *(char **)(**(_DWORD **)this + 16);
      v7 = v5 + 577;
      do
      {
        result = (char)v7;
        if ( *v7 )
        {
          v6 = v5->InitUI(v3);
          sprintf(byte_17ABF00, "%d(%s)", v3, (const char *)(v6 + 8));
          (gbCamera *->PointWorldToScr()(*(_DWORD *)(*(_DWORD *)this + 12) + 4),
            (struct gbVec3D *)(*(_DWORD *)(v4 + *(_DWORD *)this) + 6584),
            &v9,
            &v8);
          result = sub_4DFB70(*(char **)(*(_DWORD *)this + 68), byte_17ABF00, v9, v8, 16.0);
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
void sub_511030(int _this, char a2)
{
  struct gbTextureArray *v3; // ecx
  struct gbRenderEffect *v4; // edx

  gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(g_pGfxManager + 196), 0x15u);
  v3 = *(struct gbTextureArray **)(this + 672);
  v4 = *(struct gbRenderEffect **)(this + 664);
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
bool sub_511110()
{
  int v2; // eax
  float *v3; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5
  float v8; // [esp+0h] [ebp-74h]
  float v9; // [esp+4h] [ebp-70h]
  int v10; // [esp+8h] [ebp-6Ch] BYREF
  float v11[5]; // [esp+Ch] [ebp-68h] BYREF
  _DWORD v12[3]; // [esp+20h] [ebp-54h] BYREF
  int v13; // [esp+2Ch] [ebp-48h] BYREF
  float v14; // [esp+30h] [ebp-44h]
  float v15; // [esp+34h] [ebp-40h]
  float v16[6]; // [esp+38h] [ebp-3Ch] BYREF
  float v17; // [esp+50h] [ebp-24h] BYREF
  float v18; // [esp+54h] [ebp-20h]
  float v19; // [esp+58h] [ebp-1Ch]
  float v20; // [esp+5Ch] [ebp-18h]
  int v21; // [esp+60h] [ebp-14h]
  int v22; // [esp+64h] [ebp-10h]
  _BYTE v23[12]; // [esp+68h] [ebp-Ch] BYREF

  v16[1] = 1.0;
  v16[0] = 0.0;
  v16[2] = 0.0;
  v14 = 0.0;
  v13 = 1065353216;
  v15 = 1.0;
  memset(v12, 0, sizeof(v12));
  v20 = 0.0;
  v21 = 0;
  v22 = 0;
  (gbVec3D *->gbVec3D()v23, 0.0, 0.0, 0.0);
  v2 = *(_DWORD *)this;
  v10 = *(_DWORD *)(*(_DWORD *)this + 80);
  v11[0] = *(float *)(v2 + 84);
  v3 = (float *)CameraCtrl::GetViewTarget(*(char **)(v2 + 12), v16, &v10);
  v17 = *v3;
  v18 = v3[1];
  v19 = v3[2];
  v20 = v3[3];
  v21 = *((_DWORD *)v3 + 4);
  v22 = *((_DWORD *)v3 + 5);
  v4 = (gbRay *->IntersectPlane()&v17, (struct gbVec3D *)&v13, (struct gbVec3D *)v12);
  v8 = v18 * v4;
  v9 = v19 * v4;
  v14 = v8 + v16[4];
  v15 = v16[5] + v9;
  v5 = *((_DWORD *)this + 222) - v14;
  v15 = *((_DWORD *)this + 223) - v15;
  v6 = *((_DWORD *)this + 224) - (v4 * v20 + v17);
  v11[1] = v15;
  v16[0] = v6;
  v11[0] = v5;
  v11[2] = v16[0];
  return (gbVec3D *->Length()v11) < 30.0;
}

// 0x005112B0
int sub_5112B0()
{
  int v1; // edx
  _DWORD *v2; // eax
  _DWORD *v3; // ecx
  int result; // eax

  v1 = *((_DWORD *)this + 231);
  *((_DWORD *)this + 228) = *((_DWORD *)this + 229);
  v2 = this + 225;
  *((_DWORD *)this + 230) = v1;
  v3 = this + 222;
  *v3 = *v2;
  v3[1] = v2[1];
  result = v2[2];
  v3[2] = result;
  return result;
}

// 0x005112F0
_DWORD * sub_5112F0()
{
  _DWORD *result; // eax
  int v2; // ecx

  result = this + 3;
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

// 0x00511690
char sub_511690()
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
    CIniFile::WriteLine(&v5, byte_17ABE00, *(float *)(*(_DWORD *)(i + *this) + 6584));
    sprintf(byte_17ABE00, "Role%d-z", v3);
    CIniFile::WriteLine(&v5, byte_17ABE00, *(float *)(*(_DWORD *)(i + *this) + 6592));
    ++v3;
  }
  v6 = -1;
  CIniFile::~CIniFile(&v5);
  return 1;
}

// 0x00511790
char sub_511790(int _this)
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
char sub_511970(int _this)
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
char sub_511AE0()
{
  CIniFile v3; // [esp+30h] [ebp-14h] BYREF
  int v4; // [esp+40h] [ebp-4h]

  if ( (g_nGameFlags & 2) == 0 )
  {
    CIniFile::CIniFile(&v3);
    v4 = 0;
    CIniFile::OpenFileWrite(&v3, aDatascriptComb_1);
    CIniFile::WriteSection(&v3, aFivelineup);
    CIniFile::WriteLine(&v3, asc_5D8B80, *((_DWORD *)this + 222));
    CIniFile::WriteLine(&v3, "y", *((_DWORD *)this + 223));
    CIniFile::WriteLine(&v3, "z", *((_DWORD *)this + 224));
    CIniFile::WriteLine(&v3, aRadius, *((_DWORD *)this + 228));
    CIniFile::WriteLine(&v3, aRoll, *((_DWORD *)this + 230));
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
int sub_511C10()
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
void sub_511C30()
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
int sub_511C50()
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
int sub_511CF0()
{
  *(_DWORD *)&byte_17ABF00[1684] = 128;
  *(_DWORD *)&byte_17ABF00[1688] = 323;
  *(_DWORD *)&byte_17ABF00[1692] = 519;
  *(_DWORD *)&byte_17ABF00[1696] = 716;
  return 716;
}
