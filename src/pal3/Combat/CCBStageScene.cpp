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
  this->_f3B4 = 0.0;
  this->_f3B8 = 0.0;
  this->_f3BC = 0.0;
  this->_pad_3C0[1] = 1;
  this->_pad_3C0[2] = 1;
  this->_pad_3C0[3] = 1;
  this->_d3C8 = 0;
  this->_pad_3C0[0] = 0;
  this->_pad_3C0[4] = 0;
  this->_d2DC = 0;
  this->_d2E0 = 0;
  this->_d2E4 = 1065353216;
  this->_d2E8 = 1065353216;
  this->_d364 = 0;
  this->_d368 = 0;
  this->_d36C = 1065353216;
  this->_d370 = 1065353216;
  this->_d320 = 0;
  this->_d324 = 0;
  this->_d328 = 1065353216;
  this->_d32C = 1065353216;
  return 0;
}

// 0x0050FEE0
CCBStageScene::CCBStageScene()
{
  gbTexture *v2; // eax
  _DWORD *v3; // eax
  int d29C; // ecx
  gbTexture *v5; // eax
  _DWORD *v6; // eax
  int d2A4; // ecx
  char pExceptionObject[1024]; // [esp+18h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+418h] [ebp-400h] BYREF

  this->Update();
  this->_d014 = -1025769472;
  this->_d018 = 0;
  this->_d01C = -1023279104;
  this->_d020 = 1106247680;
  this->_d028 = -1025769472;
  this->_d024 = 0;
  this->_d02C = -1025769472;
  this->_d030 = 0;
  this->_d034 = 1106247680;
  this->_d038 = 1106247680;
  this->_d03C = 0;
  this->_d040 = 1092616192;
  this->_d044 = -1021968384;
  this->_d048 = 0;
  this->_d04C = -1035468800;
  this->_d050 = -1035468800;
  this->_d058 = -1035468800;
  this->_d054 = 0;
  this->_d0BC = 1124859904;
  this->_d0C0 = 0;
  this->_d0C4 = 1123024896;
  this->_d0C8 = 1133248512;
  this->_d0CC = 0;
  this->_d0D0 = 1124859904;
  this->_d0D4 = 1124859904;
  this->_d0D8 = 0;
  this->_d0DC = 1133248512;
  this->_d0E0 = 1133248512;
  this->_d0E4 = 0;
  this->_d0E8 = 1132593152;
  this->_d0EC = 1120403456;
  this->_d0F0 = 0;
  this->_d0F4 = 1128792064;
  this->_d0F8 = 1128792064;
  this->_d0FC = 0;
  this->_d100 = 1128792064;
  this->Render();
  this->ShowAxis();
  this->_p298 = ((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptAddit_1, 0);
  v2 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                      g_pGfxMgr,
                      aCbsceneFivelin);
  this->_d29C = (int)v2;
  v2->LoadTexture(1);
  v3 = (_DWORD *)operator new(0x44u);
  if ( v3 )
  {
    d29C = this->_d29C;
    v3[16] = 1;
    *v3 = d29C;
  }
  else
  {
    v3 = 0;
  }
  this->_d2A0 = (int)v3;
  v5 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                      g_pGfxMgr,
                      aCbsceneFivelin_0);
  this->_d2A4 = (int)v5;
  v5->LoadTexture(1);
  v6 = (_DWORD *)operator new(0x44u);
  if ( v6 )
  {
    d2A4 = this->_d2A4;
    v6[16] = 1;
    *v6 = d2A4;
  }
  else
  {
    v6 = 0;
  }
  this->_d2A8 = (int)v6;
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
  void (***d268)(_DWORD, int); // ecx
  void (***d25C)(_DWORD, int); // ecx
  void (***d260)(_DWORD, int); // ecx
  char *pad_26C; // esi
  int v6; // edi

  sub_511630(this);
  ((gbRefObject *)this->_d29C)->Release();
  ((gbRefObject *)this->_p298)->Release();
  if ( this->_d2A0 )
  {
    operator delete((void *)this->_d2A0);
    this->_d2A0 = 0;
  }
  d268 = (void (***)(_DWORD, int))this->_d268;
  if ( d268 )
  {
    (**d268)(d268, 1);
    this->_d268 = 0;
  }
  d25C = (void (***)(_DWORD, int))this->_d25C;
  if ( d25C )
  {
    (**d25C)(d25C, 1);
    this->_d25C = 0;
  }
  d260 = (void (***)(_DWORD, int))this->_d260;
  if ( d260 )
  {
    (**d260)(d260, 1);
    this->_d260 = 0;
  }
  pad_26C = (char *)this->_pad_26C;
  v6 = 11;
  do
  {
    if ( *(_DWORD *)pad_26C )
    {
      (***(void (****)(_DWORD, int))pad_26C)(*(_DWORD *)pad_26C, 1);
      *(_DWORD *)pad_26C = 0;
    }
    pad_26C += 4;
    --v6;
  }
  while ( v6 );
  1;
}

// 0x00510180
char CCBStageScene::Reset()
{
  int v2; // ecx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int d070; // ecx
  char *pad_26C; // esi
  int v8; // edi

  this->Update();
  this->SetFlingRotX();
  this->SetFlingRotY();
  v2 = *(_DWORD *)this->_pad_000;
  v3 = *(_DWORD *)(**(_DWORD **)this->_pad_000 + 112);
  v4 = *(_DWORD *)(v3 + 64);
  this->_d3C8 = v4;
  switch ( v4 )
  {
    case 1:
      this->_d330 = 2134481581;
      break;
    case 2:
      this->_d330 = 2145285425;
      break;
    case 3:
      this->_d330 = 2136127083;
      break;
    case 4:
      this->_d330 = 2145285565;
      break;
    case 5:
      this->_d330 = 2144775770;
      break;
    default:
      break;
  }
  v5 = ((CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)v2 + 16))->CheckDeath(this->_d3C8);
  this->_d050 = this->_d0A4;
  this->_d054 = this->_d0A8;
  this->_d058 = this->_d0AC;
  switch ( v5 )
  {
    case 1:
      *(float *)&this->_d398 = *(float *)&this->_d398 + 1.256636;
      this->_d014 = this->_d098;
      this->_d018 = this->_d09C;
      this->_d01C = this->_d0A0;
      this->_d044 = this->_d080;
      this->_d048 = this->_d084;
      this->_d04C = this->_d088;
      this->_d02C = this->_d08C;
      this->_d030 = this->_d090;
      this->_d034 = this->_d094;
      this->_d038 = this->_d074;
      this->_d03C = this->_d078;
      this->_d040 = this->_d07C;
      this->_d020 = this->_d068;
      this->_d024 = this->_d06C;
      d070 = this->_d070;
      goto LABEL_13;
    case 2:
      *(float *)&this->_d398 = *(float *)&this->_d398 + 2.513272;
      this->_d014 = this->_d080;
      this->_d018 = this->_d084;
      this->_d01C = this->_d088;
      this->_d044 = this->_d08C;
      this->_d048 = this->_d090;
      this->_d04C = this->_d094;
      this->_d02C = this->_d074;
      this->_d030 = this->_d078;
      this->_d034 = this->_d07C;
      this->_d038 = this->_d068;
      this->_d03C = this->_d06C;
      this->_d040 = this->_d070;
      this->_d020 = this->_d098;
      this->_d024 = this->_d09C;
      d070 = this->_d0A0;
      goto LABEL_13;
    case 3:
      *(float *)&this->_d398 = *(float *)&this->_d398 + 5.0265441;
      this->_d014 = this->_d074;
      this->_d018 = this->_d078;
      this->_d01C = this->_d07C;
      this->_d044 = this->_d068;
      this->_d048 = this->_d06C;
      this->_d04C = this->_d070;
      this->_d02C = this->_d098;
      this->_d030 = this->_d09C;
      this->_d034 = this->_d0A0;
      this->_d038 = this->_d080;
      this->_d03C = this->_d084;
      this->_d040 = this->_d088;
      this->_d020 = this->_d08C;
      this->_d024 = this->_d090;
      d070 = this->_d094;
      goto LABEL_13;
    case 4:
      *(float *)&this->_d398 = *(float *)&this->_d398 + 3.769908;
      this->_d014 = this->_d08C;
      this->_d018 = this->_d090;
      this->_d01C = this->_d094;
      this->_d044 = this->_d074;
      this->_d048 = this->_d078;
      this->_d04C = this->_d07C;
      this->_d02C = this->_d068;
      this->_d030 = this->_d06C;
      this->_d034 = this->_d070;
      this->_d038 = this->_d098;
      this->_d03C = this->_d09C;
      this->_d040 = this->_d0A0;
      this->_d020 = this->_d080;
      this->_d024 = this->_d084;
      d070 = this->_d088;
      goto LABEL_13;
    case 5:
      this->_d014 = this->_d068;
      this->_d018 = this->_d06C;
      this->_d01C = this->_d070;
      this->_d044 = this->_d098;
      this->_d048 = this->_d09C;
      this->_d04C = this->_d0A0;
      this->_d02C = this->_d080;
      this->_d030 = this->_d084;
      this->_d034 = this->_d088;
      this->_d038 = this->_d08C;
      this->_d03C = this->_d090;
      this->_d040 = this->_d094;
      this->_d020 = this->_d074;
      this->_d024 = this->_d078;
      d070 = this->_d07C;
LABEL_13:
      this->_d028 = d070;
      break;
    default:
      break;
  }
  if ( strlen((const char *)(v3 + 32)) )
    sub_511340((int)this, (const char *)(v3 + 32));
  else
    sub_511340((int)this, aZ27);
  pad_26C = (char *)this->_pad_26C;
  v8 = 11;
  do
  {
    if ( *(_DWORD *)pad_26C )
    {
      (***(void (****)(_DWORD, int))pad_26C)(*(_DWORD *)pad_26C, 1);
      *(_DWORD *)pad_26C = 0;
    }
    pad_26C += 4;
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
    *(_DWORD *)v3->_base = &off_56A66C;
    v4 = v3;
  }
  else
  {
    v4 = 0;
  }
  v8 = -1;
  this->_d268 = (int)v4;
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
  CCBRoleState *v4; // ecx
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
      (**(void (***)(gbGeomNode *, int))(*v3)->_base)(*v3, 1);
      *v3 = 0;
    }
    v4 = (CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)(*v1)->_pad_000 + 16);
    if ( *(&v4->m_Role[0].bValid + v2) )
    {
      v5 = *(_DWORD *)(v4->InitUI(a2) + 540);
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
            *(_DWORD *)v8->_base = &off_56A66C;
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
              (**(void (***)(gbGeomNode *, int))(*v3)->_base)(*v3, 1);
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
    v2 += 892;
    ++v3;
    ++a2;
  }
  while ( v2 < 9812 );
}

// 0x005107C0
int CCBStageScene::Init()
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
  double f3AC; // st7
  float f3A8; // esi
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
  float f380; // [esp+Ch] [ebp-10h]
  float f378; // [esp+10h] [ebp-Ch]
  float f3A0; // [esp+10h] [ebp-Ch]
  float v54; // [esp+14h] [ebp-8h]
  float v55; // [esp+18h] [ebp-4h]
  float v56; // [esp+18h] [ebp-4h]

  v1 = *(float *)&this->_d390;
  f378 = this->_f378;
  f380 = this->_f380;
  v47 = sin(*(float *)&this->_d398);
  v3 = cos(*(float *)&this->_d398);
  this->_d2F4 = 0;
  v49 = v3;
  v54 = v1 * 0.5;
  v4 = f378 - v54;
  this->_f2F0 = v4;
  v5 = f380 - v54;
  this->_f2F8 = v5;
  this->_d300 = 0;
  v55 = v54 + f378;
  this->_f2FC = v55;
  this->_f304 = v5;
  this->_f308 = v55;
  this->_d30C = 0;
  v56 = v54 + f380;
  this->_f310 = v56;
  this->_d318 = 0;
  this->_f314 = v4;
  this->_f31C = v56;
  this->_d2B0 = 0;
  this->_f2AC = -v1;
  this->_f2B4 = -v1;
  this->_d2BC = 0;
  this->_f2B8 = v1;
  this->_f2C0 = -v1;
  this->_d2C8 = 0;
  this->_f2C4 = v1;
  this->_f2CC = v1;
  this->_d2D4 = 0;
  this->_f2D0 = -v1;
  this->_f2D8 = v1;
  v6 = v49 * this->_f2B4 - v47 * this->_f2AC;
  v7 = v47 * this->_f2B4;
  v8 = v49 * this->_f2AC;
  this->_d2B0 = 0;
  this->_f2AC = v7 + v8;
  this->_f2B4 = v6;
  v9 = v49 * this->_f2C0 - v47 * this->_f2B8;
  v10 = v47 * this->_f2C0;
  v11 = v49 * this->_f2B8;
  this->_d2BC = 0;
  this->_f2B8 = v10 + v11;
  this->_f2C0 = v9;
  v12 = v49 * this->_f2CC - v47 * this->_f2C4;
  v13 = v49 * this->_f2C4;
  v14 = v47 * this->_f2CC;
  this->_d2C8 = 0;
  this->_f2C4 = v13 + v14;
  this->_f2CC = v12;
  v15 = v49 * this->_f2D8 - v47 * this->_f2D0;
  v16 = v47 * this->_f2D8;
  v17 = v49 * this->_f2D0;
  this->_d2D4 = 0;
  this->_f2D0 = v16 + v17;
  this->_f2D8 = v15;
  v18 = f380 + this->_f2B4;
  v19 = f378 + this->_f2AC;
  this->_d2B0 = 1056964608;
  this->_f2AC = v19;
  this->_f2B4 = v18;
  v20 = f380 + this->_f2C0;
  v21 = f378 + this->_f2B8;
  this->_d2BC = 1056964608;
  this->_f2B8 = v21;
  this->_f2C0 = v20;
  v22 = f380 + this->_f2CC;
  v23 = f378 + this->_f2C4;
  this->_d2C8 = 1056964608;
  this->_f2C4 = v23;
  this->_f2CC = v22;
  v24 = f380 + this->_f2D8;
  v25 = f378 + this->_f2D0;
  this->_d2D4 = 1056964608;
  this->_f2D0 = v25;
  this->_f2D8 = v24;
  f3AC = this->_f3AC;
  v48 = sin(this->_f3B0);
  v50 = cos(this->_f3B0);
  f3A0 = this->_f3A0;
  f3A8 = this->_f3A8;
  this->_f334 = -f3AC;
  this->_f33C = -f3AC;
  this->_d338 = 0;
  this->_d344 = 0;
  this->_f340 = f3AC;
  this->_f348 = -f3AC;
  this->_d350 = 0;
  this->_f34C = f3AC;
  this->_f354 = f3AC;
  this->_d35C = 0;
  this->_f358 = -f3AC;
  this->_f360 = f3AC;
  v28 = v50 * this->_f33C - v48 * this->_f334;
  v29 = v50 * this->_f334;
  v30 = v48 * this->_f33C;
  this->_d338 = 0;
  this->_f334 = v29 + v30;
  this->_f33C = v28;
  v31 = v50 * this->_f348 - v48 * this->_f340;
  v32 = v48 * this->_f348;
  v33 = v50 * this->_f340;
  this->_d344 = 0;
  this->_f340 = v32 + v33;
  this->_f348 = v31;
  v34 = v50 * this->_f354 - v48 * this->_f34C;
  v35 = v50 * this->_f34C;
  v36 = v48 * this->_f354;
  this->_d350 = 0;
  this->_f34C = v35 + v36;
  this->_f354 = v34;
  v37 = v50 * this->_f360 - v48 * this->_f358;
  v38 = v48 * this->_f360;
  v39 = v50 * this->_f358;
  this->_d35C = 0;
  this->_f358 = v38 + v39;
  this->_f360 = v37;
  v40 = f3A8 + this->_f33C;
  this->_f334 = f3A0 + this->_f334;
  this->_d338 = 1056964608;
  this->_f33C = v40;
  v41 = f3A8 + this->_f348;
  v42 = f3A0 + this->_f340;
  this->_d344 = 1056964608;
  this->_f340 = v42;
  this->_f348 = v41;
  v43 = f3A8 + this->_f354;
  v44 = f3A0 + this->_f34C;
  this->_d350 = 1056964608;
  this->_f34C = v44;
  this->_f354 = v43;
  v45 = f3A8 + this->_f360;
  v46 = f3A0 + this->_f358;
  this->_d35C = 1056964608;
  this->_f358 = v46;
  this->_f360 = v45;
  return 0;
}

// 0x00510C80
int CCBStageScene::SetBattleFieldAttr()
{
  int result; // eax
  int d268; // ecx

  result = this->Init();
  d268 = this->_d268;
  if ( d268 )
    return (*(int (**)(int))(*(_DWORD *)d268 + 20))(d268);
  return result;
}

// 0x00510CA0
void CCBStageScene::GetBattleFieldSubdueAttr(gbMatrixStack *a2)
{
  int v3; // ebp
  int d25C; // ecx
  int d264; // ecx
  char *pad_26C; // ebx
  long double v8; // st7
  float v9; // [esp+18h] [ebp-24h]
  float v10; // [esp+18h] [ebp-24h]
  float v11; // [esp+30h] [ebp-Ch]
  float f37C; // [esp+34h] [ebp-8h]
  float v13; // [esp+38h] [ebp-4h]
  gbMatrixStack *a2a; // [esp+40h] [ebp+4h]

  v3 = 0;
  d25C = this->_d25C;
  if ( d25C && this->_pad_104[84] )
  {
    (*(void (**)(int, _DWORD))(*(_DWORD *)d25C + 16))(d25C, 0);
    d264 = this->_d264;
    if ( d264 )
      (*(void (**)(int, _DWORD))(*(_DWORD *)d264 + 16))(d264, 0);
    if ( this->_pad_3C0[0] && this->_d268 )
    {
      a2->Push();
      v9 = sin(*(float *)(**(_DWORD **)this->_pad_000 + 80) * 10.0) * 5.0 + this->_f3B8 + 6.0;
      a2->Translate(this->_f3B4, v9, this->_f3BC);
      (*(void (**)(int, _DWORD))(*(_DWORD *)this->_d268 + 16))(this->_d268, 0);
      a2->Pop();
    }
    a2a = 0;
    f37C = this->_f37C;
    pad_26C = (char *)this->_pad_26C;
    do
    {
      if ( v3 >= 5 )
      {
        if ( *(_DWORD *)pad_26C )
        {
          v8 = (double)(int)a2a * 0.017453292;
          v11 = sin(v8) * 20.0 + this->_f378;
          v13 = cos(v8) * 20.0 + this->_f380;
          a2->Push();
          v10 = f37C + 2.0;
          a2->Translate(v11, v10, v13);
          (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)pad_26C + 16))(*(_DWORD *)pad_26C, 0);
          a2->Pop();
          a2a = (gbMatrixStack *)((char *)a2a + 60);
        }
      }
      ++v3;
      pad_26C += 4;
    }
    while ( v3 < 11 );
  }
}

// 0x00510E00
void CCBStageScene::GetBFASubdueFM()
{
  gbRefObject *v1; // esi
  unsigned __int8 *p_Blue; // edi
  int v3; // ebp
  struct gbDynVertBuf *DynVertBuf; // eax
  struct gbDynVertBuf *v5; // edi
  int v6; // ecx
  int v7; // ecx
  gbColorQuad v8; // [esp+10h] [ebp-3Ch] BYREF
  gbRefObject *v9; // [esp+1Ch] [ebp-30h]
  struct gbColorQuad v10; // [esp+30h] [ebp-1Ch] BYREF
  int v11; // [esp+3Ch] [ebp-10h]
  int v12; // [esp+40h] [ebp-Ch]
  int v13; // [esp+44h] [ebp-8h]
  int v14; // [esp+48h] [ebp-4h]

  if ( g_pGfxMgr && this->_pad_3C0[1] )
  {
    v1 = (gbRefObject *)((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewTrivalEffect(3);
    HIBYTE(v10.ColorQuadFmt) = 80;
    p_Blue = (unsigned __int8 *)&v10.Blue;
    v3 = 2;
    do
    {
      ((void (*)(unsigned __int8 *))gbVec3D::`default constructor closure')(p_Blue);
      p_Blue += 12;
      --v3;
    }
    while ( v3 );
    *(_DWORD *)&v10.Blue = 0;
    v10.Color = 0;
    v11 = 0;
    DynVertBuf = ((gbVertPoolMgr *)g_pGfxMgr->pVertPoolMgr)->GetDynVertBuf(5u);
    v9 = v1;
    v8.Color = 2;
    *(_DWORD *)&v8.Blue = &v10.Blue;
    v8.ColorQuadFmt = (int)&v10.Blue;
    v5 = DynVertBuf;
    LOWORD(v10.ColorQuadFmt) = 255;
    BYTE2(v10.ColorQuadFmt) = 0;
    v13 = 0;
    v12 = 0;
    v14 = 1176256512;
    ((gbColorQuad *)&v8)->gbColorQuad(&v10);
    v5->RenderLineStrip();
    v9 = v1;
    v8.Color = 2;
    *(_DWORD *)&v8.Blue = &v10.Blue;
    v8.ColorQuadFmt = v6;
    LOBYTE(v10.ColorQuadFmt) = 0;
    *(_WORD *)((char *)&v10.ColorQuadFmt + 1) = -256;
    v14 = 0;
    v13 = 0;
    v12 = 1176256512;
    ((gbColorQuad *)&v8)->gbColorQuad(&v10);
    v5->RenderLineStrip();
    v9 = v1;
    v8.Color = 2;
    *(_DWORD *)&v8.Blue = &v10.Blue;
    v8.ColorQuadFmt = v7;
    LOWORD(v10.ColorQuadFmt) = -256;
    BYTE2(v10.ColorQuadFmt) = 0;
    v14 = 0;
    v12 = 0;
    v13 = 1176256512;
    ((gbColorQuad *)&v8)->gbColorQuad(&v10);
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
  CCBRoleState *v5; // ebp
  int inited; // eax
  unsigned __int8 *p_bValid; // [esp+Ch] [ebp-Ch]
  float v8; // [esp+10h] [ebp-8h] BYREF
  float v9; // [esp+14h] [ebp-4h] BYREF

  result = (char)g_pGfxMgr;
  v9 = 0.0;
  v8 = 0.0;
  if ( g_pGfxMgr )
  {
    result = this->_pad_3C0[2];
    if ( result )
    {
      v3 = 0;
      v4 = 24;
      v5 = (CCBRoleState *)*(CCBRoleState **)(**(_DWORD **)this->_pad_000 + 16);
      p_bValid = (unsigned __int8 *)&v5->m_Role[0].bValid;
      do
      {
        result = (char)p_bValid;
        if ( *p_bValid )
        {
          inited = v5->InitUI(v3);
          sprintf(byte_17ABF00, "%d(%s)", v3, (const char *)(inited + 8));
          ((gbCamera *)(*(_DWORD *)(*(_DWORD *)this->_pad_000 + 12) + 4))->PointWorldToScr((struct gbVec3D *)(*(_DWORD *)(v4 + *(_DWORD *)this->_pad_000) + 6584), &v9, &v8);
          result = sub_4DFB70(*(char **)(*(_DWORD *)this->_pad_000 + 68), byte_17ABF00, v9, v8, 16.0);
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
  struct gbTextureArray *d2A0; // ecx
  struct gbRenderEffect *p298; // edx

  ((gbVertPoolMgr *)g_pGfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
  d2A0 = (struct gbTextureArray *)this->_d2A0;
  p298 = (struct gbRenderEffect *)this->_p298;
  this->_pad_2EC[2] = -1;
  this->_pad_2EC[1] = -1;
  this->_pad_2EC[0] = -1;
  this->_pad_2EC[3] = a2;
  HIBYTE(this->_d330) = a2;
  ((gbDynVertBuf *)&this->_f2AC)->RenderGeomQuad(1, p298, d2A0);
  ((gbDynVertBuf *)&this->_f2F0)->RenderGeomQuad(1, (struct gbRenderEffect *)this->_p298, (struct gbTextureArray *)this->_d2A8);
}

// 0x00511110
bool CCBStageScene::LoadFlingNode()
{
  int v2; // eax
  double v3; // st7
  double v4; // st6
  double v5; // st5
  float v7; // [esp+0h] [ebp-74h]
  float v8; // [esp+4h] [ebp-70h]
  float pPos; // [esp+8h] [ebp-6Ch] BYREF
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
  v2 = *(_DWORD *)this->_pad_000;
  pPos = *(float *)(*(_DWORD *)this->_pad_000 + 80);
  v10.x = *(float *)(v2 + 84);
  v14 = *(gbRay *)((CameraCtrl *)*(CameraCtrl **)(v2 + 12))->GetViewTarget(pTarget, &pPos);
  v3 = ((gbRay *)&v14)->IntersectPlane(&v12, &v11);
  v7 = v14.Origin.y * v3;
  v8 = v14.Origin.z * v3;
  v12.y = v7 + pTarget[4];
  v12.z = pTarget[5] + v8;
  v4 = this->_f378 - v12.y;
  v12.z = this->_f37C - v12.z;
  v5 = this->_f380 - (v3 * v14.Direction.x + v14.Origin.x);
  v10.y = v12.z;
  pTarget[0] = v5;
  v10.x = v4;
  v10.z = pTarget[0];
  return ((gbVec3D *)&v10)->Length() < 30.0;
}

// 0x005112B0
int CCBStageScene::SetFlingRotX()
{
  int d39C; // edx
  char *pad_384; // eax
  float *p_f378; // ecx
  int result; // eax

  d39C = this->_d39C;
  this->_d390 = this->_d394;
  pad_384 = (char *)this->_pad_384;
  this->_d398 = d39C;
  p_f378 = (float *)&this->_f378;
  * p_f378 = (*)*(float *)pad_384;
  p_f378[1] = *((float *)pad_384 + 1);
  result = *((_DWORD *)pad_384 + 2);
  *((_DWORD *)p_f378 + 2) = result;
  return result;
}

// 0x005112F0
_DWORD * CCBStageScene::SetFlingRotY()
{
  _DWORD *result; // eax
  int v2; // ecx

  result = (_DWORD *)&this->_pad_000[12];
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
    ((CIniFile *)&v5)->WriteLine(byte_17ABE00, *(float *)(*(_DWORD *)(i + *(_DWORD *)this->_pad_000) + 6584));
    sprintf(byte_17ABE00, "Role%d-z", v3);
    ((CIniFile *)&v5)->WriteLine(byte_17ABE00, *(float *)(*(_DWORD *)(i + *(_DWORD *)this->_pad_000) + 6592));
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
  int *v4; // eax
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int d080; // eax
  double v10; // st7
  int d094; // edx
  int d084; // ecx
  int v13; // eax
  int v14; // ecx
  CIniFile v16; // [esp+2Ch] [ebp-20h] BYREF
  float v17; // [esp+34h] [ebp-18h] BYREF
  int d090; // [esp+38h] [ebp-14h]
  int v19; // [esp+3Ch] [ebp-10h] BYREF
  int v20; // [esp+48h] [ebp-4h]

  v17 = 0.0;
  d090 = 0;
  v19 = 0;
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
    d090 = 0;
    sprintf(byte_17ABD00, "Role%d-z", v2);
    ((CIniFile *)&v16)->ReadLine(byte_17ABD00, (float *)&v19);
    if ( ++v3 >= 6 )
      v4 = (int *)&this->_d0C8 + 3 * v3;
    else
      v4 = (int *)&this->_pad_05C[12 * v3];
    v5 = d090;
    *(float *)v4 = v17;
    v6 = v19;
    v4[1] = v5;
    v4[2] = v6;
    if ( v3 == 6 )
    {
      ((CIniFile *)&v16)->ReadStart();
      ((CIniFile *)&v16)->ReadSection(aFivelineup);
      ((CIniFile *)&v16)->ReadLine(asc_5D8B80, &v17);
      ((CIniFile *)&v16)->ReadLine("z", (float *)&v19);
      v7 = d090;
      v8 = v19;
      *(float *)&this->_d0A4 = v17;
      this->_d0A8 = v7;
      this->_d0AC = v8;
    }
    ++v2;
  }
  while ( v2 < 11 );
  d080 = this->_d080;
  v10 = *(float *)&this->_d08C;
  d094 = this->_d094;
  d090 = this->_d090;
  v17 = v10;
  this->_d08C = d080;
  d084 = this->_d084;
  v13 = d090;
  v19 = d094;
  this->_d090 = d084;
  v14 = v19;
  this->_d094 = this->_d088;
  *(float *)&this->_d080 = v10;
  this->_d088 = v14;
  this->_d084 = v13;
  v20 = -1;
  ((CIniFile *)&v16)->~CIniFile();
  return 1;
}

// 0x00511970
char CCBStageScene::ShowAxis()
{
  float v2; // eax
  float v3; // ecx
  float v4; // eax
  CIniFile v6; // [esp+5Ch] [ebp-14h] BYREF
  int v7; // [esp+6Ch] [ebp-4h]

  ((CIniFile *)&v6)->CIniFile();
  v7 = 0;
  ((CIniFile *)&v6)->OpenFileRead(aDatascriptComb_1);
  ((CIniFile *)&v6)->ReadSection(aFivelineup);
  ((CIniFile *)&v6)->ReadLine(asc_5D8B80, (float *)this->_pad_384);
  ((CIniFile *)&v6)->ReadLine("y", (float *)&this->_pad_384[4]);
  ((CIniFile *)&v6)->ReadLine("z", (float *)&this->_pad_384[8]);
  ((CIniFile *)&v6)->ReadLine(aRadius, (float *)&this->_d394);
  this->_d390 = this->_d394;
  ((CIniFile *)&v6)->ReadLine(aRoll, (float *)&this->_d39C);
  v2 = *(float *)this->_pad_384;
  this->_d398 = this->_d39C;
  v3 = *(float *)&this->_pad_384[4];
  this->_f378 = v2;
  v4 = *(float *)&this->_pad_384[8];
  this->_f37C = v3;
  this->_f380 = v4;
  ((CIniFile *)&v6)->ReadSection(aEnemyfivelineu);
  ((CIniFile *)&v6)->ReadLine(asc_5D8B80, &this->_f3A0);
  ((CIniFile *)&v6)->ReadLine("y", (float *)this->_pad_3A4);
  ((CIniFile *)&v6)->ReadLine("z", &this->_f3A8);
  ((CIniFile *)&v6)->ReadLine(aRadius, &this->_f3AC);
  ((CIniFile *)&v6)->ReadLine(aRoll, &this->_f3B0);
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
    ((CIniFile *)&v3)->WriteLine(asc_5D8B80, this->_f378);
    ((CIniFile *)&v3)->WriteLine("y", this->_f37C);
    ((CIniFile *)&v3)->WriteLine("z", this->_f380);
    ((CIniFile *)&v3)->WriteLine(aRadius, *(float *)&this->_d390);
    ((CIniFile *)&v3)->WriteLine(aRoll, *(float *)&this->_d398);
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
