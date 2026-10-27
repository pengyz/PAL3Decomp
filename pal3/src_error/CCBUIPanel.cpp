#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CCBUIPanel.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Misc/CCBPanelSlot.h"
#include "Combat/CCBProtectWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBUI.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Misc/ChoseCompose.h"
#include "Misc/LineupComp.h"
#include "Misc/NameSys.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Misc/RoleShadow.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/SoundMgr.h"
#include "Misc/TxtFile.h"
#include "Misc/UICaption.h"
#include "Misc/UICoverFrm.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UISceneMap.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];

// 0x004460D0
CCBUIPanel::CCBUIPanel()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  ((UIFrameWnd *)((UIFrameWnd *)((UIWnd *)this) + 5))->UIFrameWnd::InitSharedPanel();
  ((PalScript *)&this->m_EmbedPalScript)->PalScript::PalScript();
  this->m_nTodo_4994 = 38;
  ((UIRoleDialog *)&this->m_EmbedPlayerAtt)->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)&this->m_nPlayerAttOverlay)->UIRoleDialog::UIRoleDialog();
  ((TxtFile *)&this->m_Data[20])->TxtFile::TxtFile();
  *((_DWORD *)((UIWnd *)this) + 19) = 0;
  *((_DWORD *)((UIWnd *)this) + 18) = 0;
  *((_DWORD *)((UIWnd *)this) + 20) = 800;
  *((_DWORD *)((UIWnd *)this) + 21) = 600;
}

// 0x00446200
CCBUIPanel::~CCBUIPanel()
{
  UIListBox **v2; // [esp+0x0] [ebp-0x14]

  this->CCBUIPanel::Destroy(v2, (int)this);
  (((PalScript *)&this->m_Data[20]))->PalScript::Cleanup();
  (((UIRoleDialog *)&this->m_nPlayerAttOverlay))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)&this->m_EmbedPlayerAtt))->UIRoleDialog::~UIRoleDialog();
  (((PalScript *)&this->m_EmbedPalScript))->PalScript::ctor();
  ((UIFrameWnd *)((UIFrameWnd *)((UIWnd *)this) + 5))->UIFrameWnd::_UIFrameWnd_ovl_00443550();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x004462C0
void CCBUIPanel::InitPanel()
{
  _DWORD *v2; // ebp
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int *v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int *v16; // eax
  int m_nPosX; // ecx
  int v18; // edx
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int m_nDimH; // ecx
  int v23; // edx
  int v24; // eax
  int *v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // ecx
  int *v32; // eax
  int v33; // ecx
  int v34; // edx
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int *v40; // eax
  int v41; // ecx
  int v42; // edx
  int v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int *v48; // eax
  int v49; // ecx
  int v50; // edx
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int *v56; // eax
  int v57; // ecx
  int v58; // edx
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // eax
  int *v64; // eax
  int v65; // ecx
  int v66; // edx
  int v67; // eax
  int v68; // eax
  int v69; // eax
  int v70; // eax
  int v71; // eax
  int *v72; // eax
  int v73; // ecx
  int v74; // edx
  int v75; // eax
  int v76; // eax
  int v77; // eax
  int v78; // eax
  int v79; // eax
  int *v80; // eax
  int v81; // ecx
  int v82; // edx
  int v83; // eax
  int v84; // eax
  int v85; // eax
  int v86; // eax
  int v87; // eax
  int *v88; // eax
  int v89; // ecx
  int v90; // edx
  int v91; // eax
  int v92; // eax
  int v93; // eax
  int v94; // eax
  int v95; // eax
  int *v96; // eax
  int v97; // ecx
  int v98; // edx
  int v99; // eax
  int v100; // eax
  int v101; // eax
  int v102; // eax
  int v103; // eax
  int *v104; // eax
  int v105; // ecx
  int v106; // edx
  int v107; // eax
  int v108; // eax
  int v109; // eax
  int v110; // eax
  int v111; // eax
  int *v112; // eax
  int v113; // ecx
  int v114; // edx
  int v115; // eax
  int v116; // eax
  int v117; // eax
  int v118; // eax
  int v119; // eax
  int *v120; // eax
  int v121; // ecx
  int v122; // edx
  int v123; // eax
  int v124; // eax
  int v125; // eax
  int v126; // eax
  int v127; // eax
  int *v128; // eax
  _PlugInfo *m_disablepicInfo; // ecx
  int m_bcreateok; // edx
  char *v131; // eax
  char *v132; // eax
  char *v133; // eax
  char *v134; // eax
  UIWnd *v135; // eax
  int *v136; // eax
  int v137; // ecx
  int v138; // edx
  int v139; // eax
  int v140; // eax
  int v141; // eax
  int v142; // eax
  int v143; // eax
  int *v144; // eax
  int v145; // ecx
  int v146; // edx
  int v147; // eax
  int v148; // eax
  int v149; // eax
  int v150; // eax
  int v151; // eax
  int *v152; // eax
  int m_nPanelX; // ecx
  int m_nItemNum; // edx
  int v155; // eax
  int v156; // eax
  int v157; // eax
  int v158; // eax
  int v159; // eax
  int *v160; // eax
  int v161; // ecx
  int v162; // edx
  int v163; // eax
  int v164; // eax
  int v165; // eax
  int v166; // eax
  int v167; // eax
  int *v168; // eax
  int v169; // ecx
  int v170; // edx
  int v171; // eax
  int v172; // eax
  int v173; // eax
  int v174; // eax
  int v175; // eax
  int *v176; // eax
  int v177; // ecx
  int v178; // edx
  int v179; // eax
  int v180; // eax
  int v181; // eax
  int v182; // eax
  int v183; // eax
  int *v184; // eax
  int v185; // ecx
  int v186; // edx
  int v187; // eax
  int v188; // eax
  int v189; // eax
  int v190; // eax
  int v191; // eax
  int *v192; // eax
  int v193; // ecx
  int v194; // edx
  int v195; // eax
  int v196; // eax
  int v197; // eax
  int v198; // eax
  int v199; // eax
  int *v200; // eax
  int v201; // ecx
  int v202; // edx
  int v203; // eax
  int v204; // eax
  int v205; // eax
  int v206; // eax
  int v207; // eax
  int *v208; // eax
  int v209; // ecx
  int v210; // edx
  int v211; // eax
  int v212; // eax
  int v213; // eax
  int v214; // eax
  int v215; // eax
  int *v216; // eax
  int v217; // ecx
  int v218; // edx
  int v219; // eax
  int v220; // eax
  int v221; // eax
  int v222; // eax
  int v223; // eax
  int *v224; // eax
  int v225; // ecx
  int v226; // edx
  int v227; // eax
  int v228; // eax
  int v229; // eax
  int v230; // eax
  int v231; // eax
  int *v232; // eax
  int v233; // ecx
  int v234; // edx
  int v235; // eax
  int v236; // eax
  int v237; // eax
  int v238; // eax
  int v239; // eax
  int *v240; // eax
  int v241; // ecx
  int m_hScrollBar; // edx
  char *v243; // eax
  Parent_Data *v244; // eax
  gbTexture *v245; // eax
  int v246; // eax
  int v247; // eax
  int *v248; // eax
  int v249; // ecx
  float m_fScaleY; // edx
  unsigned int v251; // eax
  int v252; // eax
  int v253; // eax
  int v254; // eax
  int v255; // eax
  int *v256; // eax
  int v257; // ecx
  int v258; // edx
  int v259; // eax
  float v260; // eax
  Parent_Data *v261; // eax
  gbTexture *v262; // eax
  Parent_Data *v263; // eax
  int *v264; // eax
  int v265; // ecx
  int v266; // edx
  int v267; // eax
  int v268; // eax
  int v269; // eax
  int v270; // eax
  int v271; // eax
  int *v272; // eax
  int v273; // ecx
  int v274; // edx
  int v275; // eax
  int v276; // eax
  int v277; // eax
  int v278; // eax
  int v279; // eax
  int *v280; // eax
  int v281; // ecx
  int v282; // edx
  int v283; // eax
  int v284; // eax
  int v285; // eax
  int v286; // eax
  int v287; // eax
  int *v288; // eax
  int v289; // ecx
  int v290; // edx
  int v291; // eax
  int v292; // eax
  int v293; // eax
  int v294; // eax
  int v295; // eax
  int *v296; // eax
  int v297; // ecx
  int v298; // edx
  int v299; // eax
  int v300; // eax
  int v301; // eax
  int v302; // eax
  int v303; // eax
  int *v304; // eax
  int v305; // ecx
  int v306; // edx
  int v307; // ecx
  UICursor *v308; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v311; // esi
  CScreenMode *v312; // eax
  gbColorQuad v313; // [esp+0x61C] [ebp-0x14] BYREF
  int v314; // [esp+0x620] [ebp-0x10]
  int v315; // [esp+0x624] [ebp-0xC]
  int v316; // [esp+0x628] [ebp-0x8]
  int v317; // [esp+0x62C] [ebp-0x4]

  v2 = (_DWORD *)((char *)((UIWnd *)this) + 72);
  (((UIListBox *)this))->UIListBox::SetSelTexture(240, *((_DWORD *)((UIWnd *)this) + 18), *((_DWORD *)((UIWnd *)this) + 19), *((_DWORD *)((UIWnd *)this) + 20), *((_DWORD *)((UIWnd *)this) + 21)) /* [ROWTABLE] */;
  (*(void ( **)(char *, int, int, int, _DWORD, _DWORD, _DWORD, _DWORD, int, CCBUIPanel *))(*((_DWORD *)((UIWnd *)this) + 90) + 28))(
    (char *)((UIWnd *)this) + 360,
    240,
    1536,
    1024,
    *v2,
    v2[1],
    v2[2],
    v2[3],
    off_599594,
    this);
  this->m_Slots[27].m_nPosX = 146;
  this->m_Slots[27].m_nPosY = 105;
  this->m_Slots[27].m_nDimH = 125;
  this->m_Slots[27].m_nDimH2 = 125;
  this->m_Slots[27].m_fDimH = 125.0f;
  *(_DWORD *)&this->m_Slots[27] = 18;
  this->m_Slots[27].m_nMarginX2 = 18;
  this->m_Slots[27].m_fMarginX = 18.0f;
  v3 = *(_DWORD *)&this->m_Slots[27] + this->m_Slots[27].m_nPosX;
  this->m_Slots[27].m_nEdgeR = v3;
  this->m_Slots[27].m_nEdgeR2 = v3;
  v4 = this->m_Slots[27].m_nDimH + this->m_Slots[27].m_nPosY;
  this->m_Slots[27].m_nEdgeB = v4;
  this->m_Slots[27].m_nEdgeB2 = v4;
  v5 = *(_DWORD *)&this->m_Slots[27] - *v2;
  this->m_Slots[27].m_nClipL = v5;
  this->m_Slots[27].m_nClipL2 = v5;
  v6 = *(_DWORD *)&this->m_Slots[27] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[27].m_nClipT = v6;
  this->m_Slots[27].m_nClipT2 = v6;
  v7 = this->m_Slots[27].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[27].m_nClipR = v7;
  this->m_Slots[27].m_nClipR2 = v7;
  v8 = this->m_Slots[27].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[27].m_nClipB = v8;
  this->m_Slots[27].m_nClipB2 = v8;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "xuelingzhen.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[27].m_Widget
                                                                                    + 32))(
    this->m_Slots[27].m_Widget,
    294,
    &this->m_Slots[27],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v9);
  this->m_Slots[27].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[27].m_Widget)((char *)(this->m_Slots[27].m_Widget), (_DWORD)(0));
  this->m_Slots[27].m_Widget[377] = 0;
  this->m_Slots[1].m_nPosX = 104;
  this->m_Slots[1].m_nPosY = 80;
  this->m_Slots[1].m_nDimH = 173;
  this->m_Slots[1].m_nDimH2 = 173;
  this->m_Slots[1].m_fDimH = 173.0f;
  *(_DWORD *)&this->m_Slots[1] = 204;
  this->m_Slots[1].m_nMarginX2 = 204;
  this->m_Slots[1].m_fMarginX = 204.0f;
  v10 = *(_DWORD *)&this->m_Slots[1] + this->m_Slots[1].m_nPosX;
  this->m_Slots[1].m_nEdgeR = v10;
  this->m_Slots[1].m_nEdgeR2 = v10;
  v11 = this->m_Slots[1].m_nDimH + this->m_Slots[1].m_nPosY;
  this->m_Slots[1].m_nEdgeB = v11;
  this->m_Slots[1].m_nEdgeB2 = v11;
  v12 = *(_DWORD *)&this->m_Slots[1] - *v2;
  this->m_Slots[1].m_nClipL = v12;
  this->m_Slots[1].m_nClipL2 = v12;
  v13 = *(_DWORD *)&this->m_Slots[1] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[1].m_nClipT = v13;
  this->m_Slots[1].m_nClipT2 = v13;
  v14 = this->m_Slots[1].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[1].m_nClipR = v14;
  this->m_Slots[1].m_nClipR2 = v14;
  v15 = this->m_Slots[1].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[1].m_nClipB = v15;
  this->m_Slots[1].m_nClipB2 = v15;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "deyang.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[1].m_Widget
                                                                                    + 32))(
    this->m_Slots[1].m_Widget,
    256,
    &this->m_Slots[1],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v16);
  this->m_Slots[1].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[1].m_Widget)((char *)(this->m_Slots[1].m_Widget), (_DWORD)(0));
  this->m_Slots[1].m_Widget[377] = 0;
  this->m_Slots[20].m_nPosX = 142;
  this->m_Slots[20].m_nPosY = 189;
  this->m_Slots[20].m_nDimH = 170;
  this->m_Slots[20].m_nDimH2 = 170;
  this->m_Slots[20].m_fDimH = 170.0f;
  *(_DWORD *)&this->m_Slots[20] = 406;
  this->m_Slots[20].m_nMarginX2 = 406;
  this->m_Slots[20].m_fMarginX = 406.0f;
  m_nPosX = this->m_Slots[20].m_nPosX;
  v18 = (int)this->m_Slots[20];
  this->m_Slots[20].m_nEdgeR = m_nPosX + v18;
  this->m_Slots[20].m_nEdgeR2 = m_nPosX + v18;
  v19 = this->m_Slots[20].m_nPosY + this->m_Slots[20].m_nDimH;
  this->m_Slots[20].m_nEdgeB = v19;
  this->m_Slots[20].m_nEdgeB2 = v19;
  v20 = *(_DWORD *)&this->m_Slots[20] - *v2;
  this->m_Slots[20].m_nClipL = v20;
  this->m_Slots[20].m_nClipL2 = v20;
  v21 = *(_DWORD *)&this->m_Slots[20] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[20].m_nClipT = v21;
  m_nDimH = this->m_Slots[20].m_nDimH;
  v23 = *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[20].m_nClipT2 = v21;
  this->m_Slots[20].m_nClipR = m_nDimH - v23;
  this->m_Slots[20].m_nClipR2 = m_nDimH - v23;
  v24 = m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[20].m_nClipB = v24;
  this->m_Slots[20].m_nClipB2 = v24;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "shushan.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[20].m_Widget
                                                                                    + 32))(
    this->m_Slots[20].m_Widget,
    281,
    &this->m_Slots[20],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v25);
  this->m_Slots[20].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[20].m_Widget)((char *)(this->m_Slots[20].m_Widget), (_DWORD)(0));
  this->m_Slots[20].m_Widget[377] = 0;
  v26 = (unsigned long)*v2;
  this->m_Slots[22].m_nEdgeR = 653;
  this->m_Slots[22].m_nEdgeR2 = 653;
  this->m_Slots[22].m_nEdgeB = 327;
  this->m_Slots[22].m_nEdgeB2 = 327;
  this->m_Slots[22].m_nDimH = 151;
  v27 = 518 - v26;
  v28 = *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[22].m_nClipL = v27;
  this->m_Slots[22].m_nClipL2 = v27;
  this->m_Slots[22].m_nDimH2 = 151;
  v29 = 518 - v28;
  v30 = *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[22].m_nClipT = v29;
  this->m_Slots[22].m_nClipT2 = v29;
  this->m_Slots[22].m_nPosX = 135;
  this->m_Slots[22].m_nPosY = 176;
  this->m_Slots[22].m_nClipR = 151 - v30;
  this->m_Slots[22].m_nClipR2 = 151 - v30;
  v31 = *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[22].m_fDimH = 151.0f;
  *(_DWORD *)&this->m_Slots[22] = 518;
  this->m_Slots[22].m_nMarginX2 = 518;
  this->m_Slots[22].m_fMarginX = 518.0f;
  this->m_Slots[22].m_nClipB = 151 - v31;
  this->m_Slots[22].m_nClipB2 = 151 - v31;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "suoyaota.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[22].m_Widget
                                                                                    + 32))(
    this->m_Slots[22].m_Widget,
    289,
    &this->m_Slots[22],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v32);
  this->m_Slots[22].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[22].m_Widget)((char *)(this->m_Slots[22].m_Widget), (_DWORD)(0));
  this->m_Slots[22].m_Widget[377] = 0;
  this->m_Slots[25].m_nPosX = 141;
  this->m_Slots[25].m_nPosY = 144;
  this->m_Slots[25].m_nDimH = 46;
  this->m_Slots[25].m_nDimH2 = 46;
  this->m_Slots[25].m_fDimH = 46.0f;
  *(_DWORD *)&this->m_Slots[25] = 656;
  this->m_Slots[25].m_nMarginX2 = 656;
  this->m_Slots[25].m_fMarginX = 656.0f;
  v33 = (int)this->m_Slots[25];
  v34 = this->m_Slots[25].m_nPosX;
  this->m_Slots[25].m_nEdgeR = v33 + v34;
  this->m_Slots[25].m_nEdgeR2 = v33 + v34;
  v35 = this->m_Slots[25].m_nDimH + this->m_Slots[25].m_nPosY;
  this->m_Slots[25].m_nEdgeB = v35;
  this->m_Slots[25].m_nEdgeB2 = v35;
  v36 = *(_DWORD *)&this->m_Slots[25] - *v2;
  this->m_Slots[25].m_nClipL = v36;
  this->m_Slots[25].m_nClipL2 = v36;
  v37 = *(_DWORD *)&this->m_Slots[25] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[25].m_nClipT = v37;
  this->m_Slots[25].m_nClipT2 = v37;
  v38 = this->m_Slots[25].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[25].m_nClipR = v38;
  this->m_Slots[25].m_nClipR2 = v38;
  v39 = this->m_Slots[25].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[25].m_nClipB = v39;
  this->m_Slots[25].m_nClipB2 = v39;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "xinxianjie.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[25].m_Widget
                                                                                    + 32))(
    this->m_Slots[25].m_Widget,
    292,
    &this->m_Slots[25],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v40);
  this->m_Slots[25].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[25].m_Widget)((char *)(this->m_Slots[25].m_Widget), (_DWORD)(0));
  this->m_Slots[25].m_Widget[377] = 0;
  this->m_Slots[7].m_nPosX = 120;
  this->m_Slots[7].m_nPosY = 110;
  this->m_Slots[7].m_nDimH = 0;
  this->m_Slots[7].m_nDimH2 = 0;
  this->m_Slots[7].m_fDimH = 0.0f;
  *(_DWORD *)&this->m_Slots[7] = 903;
  this->m_Slots[7].m_nMarginX2 = 903;
  this->m_Slots[7].m_fMarginX = 903.0f;
  v41 = this->m_Slots[7].m_nPosX;
  v42 = (int)this->m_Slots[7];
  this->m_Slots[7].m_nEdgeR = v41 + v42;
  this->m_Slots[7].m_nEdgeR2 = v41 + v42;
  v43 = this->m_Slots[7].m_nPosY + this->m_Slots[7].m_nDimH;
  this->m_Slots[7].m_nEdgeB = v43;
  this->m_Slots[7].m_nEdgeB2 = v43;
  v44 = *(_DWORD *)&this->m_Slots[7] - *v2;
  this->m_Slots[7].m_nClipL = v44;
  this->m_Slots[7].m_nClipL2 = v44;
  v45 = *(_DWORD *)&this->m_Slots[7] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[7].m_nClipT = v45;
  this->m_Slots[7].m_nClipT2 = v45;
  v46 = this->m_Slots[7].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[7].m_nClipR = v46;
  this->m_Slots[7].m_nClipR2 = v46;
  v47 = this->m_Slots[7].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[7].m_nClipB = v47;
  this->m_Slots[7].m_nClipB2 = v47;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "rongyandiyu.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[7].m_Widget
                                                                                    + 32))(
    this->m_Slots[7].m_Widget,
    262,
    &this->m_Slots[7],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v48);
  this->m_Slots[7].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[7].m_Widget)((char *)(this->m_Slots[7].m_Widget), (_DWORD)(0));
  this->m_Slots[7].m_Widget[377] = 0;
  this->m_Slots[17].m_nPosX = 209;
  this->m_Slots[17].m_nPosY = 61;
  this->m_Slots[17].m_nDimH = 100;
  this->m_Slots[17].m_nDimH2 = 100;
  this->m_Slots[17].m_fDimH = 100.0f;
  *(_DWORD *)&this->m_Slots[17] = 1007;
  this->m_Slots[17].m_nMarginX2 = 1007;
  this->m_Slots[17].m_fMarginX = 1007.0f;
  v49 = this->m_Slots[17].m_nPosX;
  v50 = (int)this->m_Slots[17];
  this->m_Slots[17].m_nEdgeR = v49 + v50;
  this->m_Slots[17].m_nEdgeR2 = v49 + v50;
  v51 = this->m_Slots[17].m_nPosY + this->m_Slots[17].m_nDimH;
  this->m_Slots[17].m_nEdgeB = v51;
  this->m_Slots[17].m_nEdgeB2 = v51;
  v52 = *(_DWORD *)&this->m_Slots[17] - *v2;
  this->m_Slots[17].m_nClipL = v52;
  this->m_Slots[17].m_nClipL2 = v52;
  v53 = *(_DWORD *)&this->m_Slots[17] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[17].m_nClipT = v53;
  this->m_Slots[17].m_nClipT2 = v53;
  v54 = this->m_Slots[17].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[17].m_nClipR = v54;
  this->m_Slots[17].m_nClipR2 = v54;
  v55 = this->m_Slots[17].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[17].m_nClipB = v55;
  this->m_Slots[17].m_nClipB2 = v55;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "huangquanlu.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[17].m_Widget
                                                                                    + 32))(
    this->m_Slots[17].m_Widget,
    278,
    &this->m_Slots[17],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v56);
  this->m_Slots[17].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[17].m_Widget)((char *)(this->m_Slots[17].m_Widget), (_DWORD)(0));
  this->m_Slots[17].m_Widget[377] = 0;
  this->m_Slots[5].m_nPosX = 112;
  this->m_Slots[5].m_nPosY = 107;
  this->m_Slots[5].m_nDimH = 18;
  this->m_Slots[5].m_nDimH2 = 18;
  this->m_Slots[5].m_fDimH = 18.0f;
  *(_DWORD *)&this->m_Slots[5] = 1089;
  this->m_Slots[5].m_nMarginX2 = 1089;
  this->m_Slots[5].m_fMarginX = 1089.0f;
  v57 = (int)this->m_Slots[5];
  v58 = this->m_Slots[5].m_nPosX;
  this->m_Slots[5].m_nEdgeR = v57 + v58;
  this->m_Slots[5].m_nEdgeR2 = v57 + v58;
  v59 = this->m_Slots[5].m_nDimH + this->m_Slots[5].m_nPosY;
  this->m_Slots[5].m_nEdgeB = v59;
  this->m_Slots[5].m_nEdgeB2 = v59;
  v60 = *(_DWORD *)&this->m_Slots[5] - *v2;
  this->m_Slots[5].m_nClipL = v60;
  this->m_Slots[5].m_nClipL2 = v60;
  v61 = *(_DWORD *)&this->m_Slots[5] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[5].m_nClipT = v61;
  this->m_Slots[5].m_nClipT2 = v61;
  v62 = this->m_Slots[5].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[5].m_nClipR = v62;
  this->m_Slots[5].m_nClipR2 = v62;
  v63 = this->m_Slots[5].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[5].m_nClipB = v63;
  this->m_Slots[5].m_nClipB2 = v63;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "guijiewaiwei.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[5].m_Widget
                                                                                    + 32))(
    this->m_Slots[5].m_Widget,
    260,
    &this->m_Slots[5],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v64);
  this->m_Slots[5].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[5].m_Widget)((char *)(this->m_Slots[5].m_Widget), (_DWORD)(0));
  this->m_Slots[5].m_Widget[377] = 0;
  this->m_Slots[14].m_nPosX = 100;
  this->m_Slots[14].m_nPosY = 94;
  this->m_Slots[14].m_nDimH = 20;
  this->m_Slots[14].m_nDimH2 = 20;
  this->m_Slots[14].m_fDimH = 20.0f;
  *(_DWORD *)&this->m_Slots[14] = 1336;
  this->m_Slots[14].m_nMarginX2 = 1336;
  this->m_Slots[14].m_fMarginX = 1336.0f;
  v65 = (int)this->m_Slots[14];
  v66 = this->m_Slots[14].m_nPosX;
  this->m_Slots[14].m_nEdgeR = v65 + v66;
  this->m_Slots[14].m_nEdgeR2 = v65 + v66;
  v67 = this->m_Slots[14].m_nDimH + this->m_Slots[14].m_nPosY;
  this->m_Slots[14].m_nEdgeB = v67;
  this->m_Slots[14].m_nEdgeB2 = v67;
  v68 = *(_DWORD *)&this->m_Slots[14] - *v2;
  this->m_Slots[14].m_nClipL = v68;
  this->m_Slots[14].m_nClipL2 = v68;
  v69 = *(_DWORD *)&this->m_Slots[14] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[14].m_nClipT = v69;
  this->m_Slots[14].m_nClipT2 = v69;
  v70 = this->m_Slots[14].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[14].m_nClipR = v70;
  this->m_Slots[14].m_nClipR2 = v70;
  v71 = this->m_Slots[14].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[14].m_nClipB = v71;
  this->m_Slots[14].m_nClipB2 = v71;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "penglai.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[14].m_Widget
                                                                                    + 32))(
    this->m_Slots[14].m_Widget,
    275,
    &this->m_Slots[14],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v72);
  this->m_Slots[14].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[14].m_Widget)((char *)(this->m_Slots[14].m_Widget), (_DWORD)(0));
  this->m_Slots[14].m_Widget[377] = 0;
  this->m_Slots[16].m_nPosX = 75;
  this->m_Slots[16].m_nPosY = 69;
  this->m_Slots[16].m_nDimH = 243;
  this->m_Slots[16].m_nDimH2 = 243;
  this->m_Slots[16].m_fDimH = 243.0f;
  *(_DWORD *)&this->m_Slots[16] = 170;
  this->m_Slots[16].m_nMarginX2 = 170;
  this->m_Slots[16].m_fMarginX = 170.0f;
  v73 = this->m_Slots[16].m_nPosX;
  v74 = (int)this->m_Slots[16];
  this->m_Slots[16].m_nEdgeR = v73 + v74;
  this->m_Slots[16].m_nEdgeR2 = v73 + v74;
  v75 = this->m_Slots[16].m_nPosY + this->m_Slots[16].m_nDimH;
  this->m_Slots[16].m_nEdgeB = v75;
  this->m_Slots[16].m_nEdgeB2 = v75;
  v76 = *(_DWORD *)&this->m_Slots[16] - *v2;
  this->m_Slots[16].m_nClipL = v76;
  this->m_Slots[16].m_nClipL2 = v76;
  v77 = *(_DWORD *)&this->m_Slots[16] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[16].m_nClipT = v77;
  this->m_Slots[16].m_nClipT2 = v77;
  v78 = this->m_Slots[16].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[16].m_nClipR = v78;
  this->m_Slots[16].m_nClipR2 = v78;
  v79 = this->m_Slots[16].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[16].m_nClipB = v79;
  this->m_Slots[16].m_nClipB2 = v79;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "pilitang.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[16].m_Widget
                                                                                    + 32))(
    this->m_Slots[16].m_Widget,
    277,
    &this->m_Slots[16],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v80);
  this->m_Slots[16].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[16].m_Widget)((char *)(this->m_Slots[16].m_Widget), (_DWORD)(0));
  this->m_Slots[16].m_Widget[377] = 0;
  this->m_Slots[21].m_nPosX = 204;
  this->m_Slots[21].m_nPosY = 256;
  this->m_Slots[21].m_nDimH = 273;
  this->m_Slots[21].m_nDimH2 = 273;
  this->m_Slots[21].m_fDimH = 273.0f;
  *(_DWORD *)&this->m_Slots[21] = 304;
  this->m_Slots[21].m_nMarginX2 = 304;
  this->m_Slots[21].m_fMarginX = 304.0f;
  v81 = this->m_Slots[21].m_nPosX;
  v82 = (int)this->m_Slots[21];
  this->m_Slots[21].m_nEdgeR = v81 + v82;
  this->m_Slots[21].m_nEdgeR2 = v81 + v82;
  v83 = this->m_Slots[21].m_nPosY + this->m_Slots[21].m_nDimH;
  this->m_Slots[21].m_nEdgeB = v83;
  this->m_Slots[21].m_nEdgeB2 = v83;
  v84 = *(_DWORD *)&this->m_Slots[21] - *v2;
  this->m_Slots[21].m_nClipL = v84;
  this->m_Slots[21].m_nClipL2 = v84;
  v85 = *(_DWORD *)&this->m_Slots[21] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[21].m_nClipT = v85;
  this->m_Slots[21].m_nClipT2 = v85;
  v86 = this->m_Slots[21].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[21].m_nClipR = v86;
  this->m_Slots[21].m_nClipR2 = v86;
  v87 = this->m_Slots[21].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[21].m_nClipB = v87;
  this->m_Slots[21].m_nClipB2 = v87;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "shushangudao.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[21].m_Widget
                                                                                    + 32))(
    this->m_Slots[21].m_Widget,
    288,
    &this->m_Slots[21],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v88);
  this->m_Slots[21].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[21].m_Widget)((char *)(this->m_Slots[21].m_Widget), (_DWORD)(0));
  this->m_Slots[21].m_Widget[377] = 0;
  this->m_Slots[26].m_nPosX = 41;
  this->m_Slots[26].m_nPosY = 35;
  this->m_Slots[26].m_nDimH = 409;
  this->m_Slots[26].m_nDimH2 = 409;
  this->m_Slots[26].m_fDimH = 409.0f;
  *(_DWORD *)&this->m_Slots[26] = 585;
  this->m_Slots[26].m_nMarginX2 = 585;
  this->m_Slots[26].m_fMarginX = 585.0f;
  v89 = (int)this->m_Slots[26];
  v90 = this->m_Slots[26].m_nPosX;
  this->m_Slots[26].m_nEdgeR = v89 + v90;
  this->m_Slots[26].m_nEdgeR2 = v89 + v90;
  v91 = this->m_Slots[26].m_nDimH + this->m_Slots[26].m_nPosY;
  this->m_Slots[26].m_nEdgeB = v91;
  this->m_Slots[26].m_nEdgeB2 = v91;
  v92 = *(_DWORD *)&this->m_Slots[26] - *v2;
  this->m_Slots[26].m_nClipL = v92;
  this->m_Slots[26].m_nClipL2 = v92;
  v93 = *(_DWORD *)&this->m_Slots[26] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[26].m_nClipT = v93;
  this->m_Slots[26].m_nClipT2 = v93;
  v94 = this->m_Slots[26].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[26].m_nClipR = v94;
  this->m_Slots[26].m_nClipR2 = v94;
  v95 = this->m_Slots[26].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[26].m_nClipB = v95;
  this->m_Slots[26].m_nClipB2 = v95;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "xingsen.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[26].m_Widget
                                                                                    + 32))(
    this->m_Slots[26].m_Widget,
    293,
    &this->m_Slots[26],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v96);
  this->m_Slots[26].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[26].m_Widget)((char *)(this->m_Slots[26].m_Widget), (_DWORD)(0));
  this->m_Slots[26].m_Widget[377] = 0;
  this->m_Slots[28].m_nPosX = 188;
  this->m_Slots[28].m_nPosY = 120;
  this->m_Slots[28].m_nDimH = 298;
  this->m_Slots[28].m_nDimH2 = 298;
  this->m_Slots[28].m_fDimH = 298.0f;
  *(_DWORD *)&this->m_Slots[28] = 771;
  this->m_Slots[28].m_nMarginX2 = 771;
  this->m_Slots[28].m_fMarginX = 771.0f;
  v97 = (int)this->m_Slots[28];
  v98 = this->m_Slots[28].m_nPosX;
  this->m_Slots[28].m_nEdgeR = v97 + v98;
  this->m_Slots[28].m_nEdgeR2 = v97 + v98;
  v99 = this->m_Slots[28].m_nDimH + this->m_Slots[28].m_nPosY;
  this->m_Slots[28].m_nEdgeB = v99;
  this->m_Slots[28].m_nEdgeB2 = v99;
  v100 = *(_DWORD *)&this->m_Slots[28] - *v2;
  this->m_Slots[28].m_nClipL = v100;
  this->m_Slots[28].m_nClipL2 = v100;
  v101 = *(_DWORD *)&this->m_Slots[28] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[28].m_nClipT = v101;
  this->m_Slots[28].m_nClipT2 = v101;
  v102 = this->m_Slots[28].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[28].m_nClipR = v102;
  this->m_Slots[28].m_nClipR2 = v102;
  v103 = this->m_Slots[28].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[28].m_nClipB = v103;
  this->m_Slots[28].m_nClipB2 = v103;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "yuzhou.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[28].m_Widget
                                                                                    + 32))(
    this->m_Slots[28].m_Widget,
    295,
    &this->m_Slots[28],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v104);
  this->m_Slots[28].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[28].m_Widget)((char *)(this->m_Slots[28].m_Widget), (_DWORD)(0));
  this->m_Slots[28].m_Widget[377] = 0;
  this->m_Slots[2].m_nPosX = 139;
  this->m_Slots[2].m_nPosY = 101;
  this->m_Slots[2].m_nDimH = 155;
  this->m_Slots[2].m_nDimH2 = 155;
  this->m_Slots[2].m_fDimH = 155.0f;
  *(_DWORD *)&this->m_Slots[2] = 1006;
  this->m_Slots[2].m_nMarginX2 = 1006;
  this->m_Slots[2].m_fMarginX = 1006.0f;
  v105 = this->m_Slots[2].m_nPosX;
  v106 = (int)this->m_Slots[2];
  this->m_Slots[2].m_nEdgeR = v105 + v106;
  this->m_Slots[2].m_nEdgeR2 = v105 + v106;
  v107 = this->m_Slots[2].m_nPosY + this->m_Slots[2].m_nDimH;
  this->m_Slots[2].m_nEdgeB = v107;
  this->m_Slots[2].m_nEdgeB2 = v107;
  v108 = *(_DWORD *)&this->m_Slots[2] - *v2;
  this->m_Slots[2].m_nClipL = v108;
  this->m_Slots[2].m_nClipL2 = v108;
  v109 = *(_DWORD *)&this->m_Slots[2] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[2].m_nClipT = v109;
  this->m_Slots[2].m_nClipT2 = v109;
  v110 = this->m_Slots[2].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[2].m_nClipR = v110;
  this->m_Slots[2].m_nClipR2 = v110;
  v111 = this->m_Slots[2].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[2].m_nClipB = v111;
  this->m_Slots[2].m_nClipB2 = v111;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "fengdu.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[2].m_Widget
                                                                                    + 32))(
    this->m_Slots[2].m_Widget,
    257,
    &this->m_Slots[2],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v112);
  this->m_Slots[2].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[2].m_Widget)((char *)(this->m_Slots[2].m_Widget), (_DWORD)(0));
  this->m_Slots[2].m_Widget[377] = 0;
  this->m_Slots[29].m_nPosX = 138;
  this->m_Slots[29].m_nPosY = 113;
  this->m_Slots[29].m_nDimH = 200;
  this->m_Slots[29].m_nDimH2 = 200;
  this->m_Slots[29].m_fDimH = 200.0f;
  *(_DWORD *)&this->m_Slots[29] = 1248;
  this->m_Slots[29].m_nMarginX2 = 1248;
  this->m_Slots[29].m_fMarginX = 1248.0f;
  v113 = this->m_Slots[29].m_nPosX;
  v114 = (int)this->m_Slots[29];
  this->m_Slots[29].m_nEdgeR = v113 + v114;
  this->m_Slots[29].m_nEdgeR2 = v113 + v114;
  v115 = this->m_Slots[29].m_nPosY + this->m_Slots[29].m_nDimH;
  this->m_Slots[29].m_nEdgeB = v115;
  this->m_Slots[29].m_nEdgeB2 = v115;
  v116 = *(_DWORD *)&this->m_Slots[29] - *v2;
  this->m_Slots[29].m_nClipL = v116;
  this->m_Slots[29].m_nClipL2 = v116;
  v117 = *(_DWORD *)&this->m_Slots[29] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[29].m_nClipT = v117;
  this->m_Slots[29].m_nClipT2 = v117;
  v118 = this->m_Slots[29].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[29].m_nClipR = v118;
  this->m_Slots[29].m_nClipR2 = v118;
  v119 = this->m_Slots[29].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[29].m_nClipB = v119;
  this->m_Slots[29].m_nClipB2 = v119;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "zhenjiang.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[29].m_Widget
                                                                                    + 32))(
    this->m_Slots[29].m_Widget,
    296,
    &this->m_Slots[29],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v120);
  this->m_Slots[29].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[29].m_Widget)((char *)(this->m_Slots[29].m_Widget), (_DWORD)(0));
  this->m_Slots[29].m_Widget[377] = 0;
  this->m_Slots[15].m_nPosX = 65;
  this->m_Slots[15].m_nPosY = 112;
  this->m_Slots[15].m_nDimH = 40;
  this->m_Slots[15].m_nDimH2 = 40;
  this->m_Slots[15].m_fDimH = 40.0f;
  *(_DWORD *)&this->m_Slots[15] = 1426;
  this->m_Slots[15].m_nMarginX2 = 1426;
  this->m_Slots[15].m_fMarginX = 1426.0f;
  v121 = (int)this->m_Slots[15];
  v122 = this->m_Slots[15].m_nPosX;
  this->m_Slots[15].m_nEdgeR = v121 + v122;
  this->m_Slots[15].m_nEdgeR2 = v121 + v122;
  v123 = this->m_Slots[15].m_nDimH + this->m_Slots[15].m_nPosY;
  this->m_Slots[15].m_nEdgeB = v123;
  this->m_Slots[15].m_nEdgeB2 = v123;
  v124 = *(_DWORD *)&this->m_Slots[15] - *v2;
  this->m_Slots[15].m_nClipL = v124;
  this->m_Slots[15].m_nClipL2 = v124;
  v125 = *(_DWORD *)&this->m_Slots[15] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[15].m_nClipT = v125;
  this->m_Slots[15].m_nClipT2 = v125;
  v126 = this->m_Slots[15].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[15].m_nClipR = v126;
  this->m_Slots[15].m_nClipR2 = v126;
  v127 = this->m_Slots[15].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[15].m_nClipB = v127;
  this->m_Slots[15].m_nClipB2 = v127;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "penglaimigong.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[15].m_Widget
                                                                                    + 32))(
    this->m_Slots[15].m_Widget,
    276,
    &this->m_Slots[15],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v128);
  this->m_Slots[15].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[15].m_Widget)((char *)(this->m_Slots[15].m_Widget), (_DWORD)(0));
  this->m_Slots[15].m_Widget[377] = 0;
  this->m_Static_2440.m_bcreateok = 112;
  this->m_Static_2440.m_bvisible = 113;
  this->m_Static_2288.m_pbk2 = ((gbTexture *)((gbTexture *)214));
  *(_DWORD *)((UIWnd *)&this->m_Static_2440) = 214;
  this->m_Static_2440.m_rect.left = 1129709568;
  this->m_Static_2288.m_disablepicInfo = ((_PlugInfo *)((_PlugInfo *)6));
  this->m_Static_2288.m_nTextW = 6;
  this->m_Static_2440.m_id = 1086324736;
  m_disablepicInfo = (_PlugInfo *)this->m_Static_2288.m_disablepicInfo;
  m_bcreateok = this->m_Static_2440.m_bcreateok;
  *(_DWORD *)&this->m_Static_2288.m_mouseoff = (unsigned long)((char *)m_disablepicInfo + m_bcreateok);
  this->m_Static_2440.m_fontcolor.Color = (unsigned int)m_disablepicInfo + m_bcreateok;
  v131 = (char *)this->m_Static_2288.m_pbk2 + this->m_Static_2440.m_bvisible;
  this->m_Static_2288.m_FVF = (int)v131;
  this->m_Static_2440.m_wndcolor.Color = (unsigned int)v131;
  v132 = (char *)this->m_Static_2288.m_disablepicInfo - *v2;
  this->m_Static_2440.m_rect.top = (LONG)v132;
  this->m_Static_2440.m_childs.m_pData = ((char *)(v132));
  v133 = (char *)this->m_Static_2288.m_disablepicInfo - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Static_2440.m_rect.right = (LONG)v133;
  this->m_Static_2440.m_childs.capacity = (int)v133;
  v134 = (char *)this->m_Static_2288.m_pbk2 - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Static_2440.m_rect.bottom = (LONG)v134;
  this->m_Static_2440.m_childs.m_nSize = (int)v134;
  v135 = (UIWnd *)((char *)this->m_Static_2288.m_pbk2 - *((_DWORD *)((UIWnd *)this) + 21));
  this->m_Static_2440.m_pfather = ((UIWnd *)(v135));
  this->m_Static_2440.m_childs.m_needscriptdel = (int)v135;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "bingfenggu.tga");
  (*(void ( **)(int *, int, _PlugInfo **, CCBUIPanel *, char *, _DWORD))(this->m_Static_2440.m_align
                                                                                            + 32))(
    &this->m_Static_2440.m_align,
    245,
    &this->m_Static_2288.m_disablepicInfo,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v136);
  LOBYTE(this->m_Static_2744.m_FVF) = 1;
  (*(void ( **)(int *, _DWORD))this->m_Static_2440.m_align)(&this->m_Static_2440.m_align, 0);
  BYTE1(this->m_Static_2744.m_FVF) = 0;
  *((_DWORD *)((UIWnd *)this) + 147) = 116;
  *((_DWORD *)((UIWnd *)this) + 148) = 73;
  *((_DWORD *)((UIWnd *)this) + 130) = 472;
  *((_DWORD *)((UIWnd *)this) + 134) = 472;
  *((_DWORD *)((UIWnd *)this) + 138) = 1139539968;
  *((_DWORD *)((UIWnd *)this) + 129) = 122;
  *((_DWORD *)((UIWnd *)this) + 133) = 122;
  *((_DWORD *)((UIWnd *)this) + 137) = 1123287040;
  v137 = *((_DWORD *)((UIWnd *)this) + 147);
  v138 = *((_DWORD *)((UIWnd *)this) + 129);
  *((_DWORD *)((UIWnd *)this) + 131) = v137 + v138;
  *((_DWORD *)((UIWnd *)this) + 135) = v137 + v138;
  v139 = *((_DWORD *)((UIWnd *)this) + 148) + *((_DWORD *)((UIWnd *)this) + 130);
  *((_DWORD *)((UIWnd *)this) + 132) = v139;
  *((_DWORD *)((UIWnd *)this) + 136) = v139;
  v140 = *((_DWORD *)((UIWnd *)this) + 129) - *v2;
  *((_DWORD *)((UIWnd *)this) + 139) = v140;
  *((_DWORD *)((UIWnd *)this) + 143) = v140;
  v141 = *((_DWORD *)((UIWnd *)this) + 129) - *((_DWORD *)((UIWnd *)this) + 20);
  *((_DWORD *)((UIWnd *)this) + 140) = v141;
  *((_DWORD *)((UIWnd *)this) + 144) = v141;
  v142 = *((_DWORD *)((UIWnd *)this) + 130) - *((_DWORD *)((UIWnd *)this) + 19);
  *((_DWORD *)((UIWnd *)this) + 141) = v142;
  *((_DWORD *)((UIWnd *)this) + 145) = v142;
  v143 = *((_DWORD *)((UIWnd *)this) + 130) - *((_DWORD *)((UIWnd *)this) + 21);
  *((_DWORD *)((UIWnd *)this) + 142) = v143;
  *((_DWORD *)((UIWnd *)this) + 146) = v143;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "anningchun.tga");
  (*(void ( **)(char *, int, char *, CCBUIPanel *, char *, _DWORD))(*((_DWORD *)((UIWnd *)this) + 152) + 32))(
    (char *)((UIWnd *)this) + 608,
    241,
    (char *)((UIWnd *)this) + 516,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v144);
  *((_BYTE *)((UIWnd *)this) + 984) = 1;
  (**((void ( ***)(char *, _DWORD))((UIWnd *)this) + 152))((char *)((char *)((UIWnd *)this) + 608), (_DWORD)(0));
  *((_BYTE *)((UIWnd *)this) + 985) = 0;
  this->m_Slots[23].m_nPosX = 124;
  this->m_Slots[23].m_nPosY = 96;
  this->m_Slots[23].m_nDimH = 504;
  this->m_Slots[23].m_nDimH2 = 504;
  this->m_Slots[23].m_fDimH = 504.0f;
  *(_DWORD *)&this->m_Slots[23] = 588;
  this->m_Slots[23].m_nMarginX2 = 588;
  this->m_Slots[23].m_fMarginX = 588.0f;
  v145 = this->m_Slots[23].m_nPosX;
  v146 = (int)this->m_Slots[23];
  this->m_Slots[23].m_nEdgeR = v145 + v146;
  this->m_Slots[23].m_nEdgeR2 = v145 + v146;
  v147 = this->m_Slots[23].m_nPosY + this->m_Slots[23].m_nDimH;
  this->m_Slots[23].m_nEdgeB = v147;
  this->m_Slots[23].m_nEdgeB2 = v147;
  v148 = *(_DWORD *)&this->m_Slots[23] - *v2;
  this->m_Slots[23].m_nClipL = v148;
  this->m_Slots[23].m_nClipL2 = v148;
  v149 = *(_DWORD *)&this->m_Slots[23] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[23].m_nClipT = v149;
  this->m_Slots[23].m_nClipT2 = v149;
  v150 = this->m_Slots[23].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[23].m_nClipR = v150;
  this->m_Slots[23].m_nClipR2 = v150;
  v151 = this->m_Slots[23].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[23].m_nClipB = v151;
  this->m_Slots[23].m_nClipB2 = v151;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "tangjiabao.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[23].m_Widget
                                                                                    + 32))(
    this->m_Slots[23].m_Widget,
    290,
    &this->m_Slots[23],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v152);
  this->m_Slots[23].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[23].m_Widget)((char *)(this->m_Slots[23].m_Widget), (_DWORD)(0));
  this->m_Slots[23].m_Widget[377] = 0;
  this->m_nItemNum = 174;
  this->m_nMaxItemNum = 126;
  this->m_nPanelY = 569;
  this->m_nChildH = 569;
  this->m_fPanelH = 569.0f;
  this->m_nPanelX = 852;
  this->m_nChildW = 852;
  this->m_fPanelW = 852.0f;
  m_nPanelX = this->m_nPanelX;
  m_nItemNum = this->m_nItemNum;
  this->m_nChildX = m_nPanelX + m_nItemNum;
  this->m_nBorderL = m_nPanelX + m_nItemNum;
  v155 = this->m_nPanelY + this->m_nMaxItemNum;
  this->m_nChildY = v155;
  this->m_nBorderR = v155;
  v156 = this->m_nPanelX - *v2;
  this->m_nGridX = v156;
  this->m_nItemW = v156;
  v157 = this->m_nPanelX - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_nGridY = v157;
  this->m_nItemH = v157;
  v158 = this->m_nPanelY - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_nGridW = v158;
  this->m_nSpacingX = v158;
  v159 = this->m_nPanelY - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_nGridH = v159;
  this->m_nSpacingY = v159;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "binhua.tga");
  ((void ( *)(void **, int, int *, CCBUIPanel *, char *, _DWORD))this->m_pVfTable[1].RenderIfUnlocked)(
    &this->m_pVfTable,
    243,
    &this->m_nPanelX,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v160);
  LOBYTE(this->m_nTodo_1792.m_nNotifyRender) = 1;
  ((void ( *)(void **, _DWORD))this->m_pVfTable->ShowClipped)(&this->m_pVfTable, 0);
  BYTE1(this->m_nTodo_1792.m_nNotifyRender) = 0;
  this->m_Slots[8].m_nPosX = 90;
  this->m_Slots[8].m_nPosY = 140;
  this->m_Slots[8].m_nDimH = 329;
  this->m_Slots[8].m_nDimH2 = 329;
  this->m_Slots[8].m_fDimH = 329.0f;
  *(_DWORD *)&this->m_Slots[8] = 1121;
  this->m_Slots[8].m_nMarginX2 = 1121;
  this->m_Slots[8].m_fMarginX = 1121.0f;
  v161 = (int)this->m_Slots[8];
  v162 = this->m_Slots[8].m_nPosX;
  this->m_Slots[8].m_nEdgeR = v161 + v162;
  this->m_Slots[8].m_nEdgeR2 = v161 + v162;
  v163 = this->m_Slots[8].m_nDimH + this->m_Slots[8].m_nPosY;
  this->m_Slots[8].m_nEdgeB = v163;
  this->m_Slots[8].m_nEdgeB2 = v163;
  v164 = *(_DWORD *)&this->m_Slots[8] - *v2;
  this->m_Slots[8].m_nClipL = v164;
  this->m_Slots[8].m_nClipL2 = v164;
  v165 = *(_DWORD *)&this->m_Slots[8] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[8].m_nClipT = v165;
  this->m_Slots[8].m_nClipT2 = v165;
  v166 = this->m_Slots[8].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[8].m_nClipR = v166;
  this->m_Slots[8].m_nClipR2 = v166;
  v167 = this->m_Slots[8].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[8].m_nClipB = v167;
  this->m_Slots[8].m_nClipB2 = v167;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "jianzhong.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[8].m_Widget
                                                                                    + 32))(
    this->m_Slots[8].m_Widget,
    263,
    &this->m_Slots[8],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v168);
  this->m_Slots[8].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[8].m_Widget)((char *)(this->m_Slots[8].m_Widget), (_DWORD)(0));
  this->m_Slots[8].m_Widget[377] = 0;
  *((_DWORD *)((UIWnd *)this) + 266) = 128;
  *((_DWORD *)((UIWnd *)this) + 267) = 113;
  *((_DWORD *)((UIWnd *)this) + 249) = 566;
  *((_DWORD *)((UIWnd *)this) + 253) = 566;
  *((_DWORD *)((UIWnd *)this) + 257) = 1141735424;
  *((_DWORD *)((UIWnd *)this) + 248) = 1230;
  *((_DWORD *)((UIWnd *)this) + 252) = 1230;
  *((_DWORD *)((UIWnd *)this) + 256) = 1150926848;
  v169 = *((_DWORD *)((UIWnd *)this) + 266);
  v170 = *((_DWORD *)((UIWnd *)this) + 248);
  *((_DWORD *)((UIWnd *)this) + 250) = v169 + v170;
  *((_DWORD *)((UIWnd *)this) + 254) = v169 + v170;
  v171 = *((_DWORD *)((UIWnd *)this) + 267) + *((_DWORD *)((UIWnd *)this) + 249);
  *((_DWORD *)((UIWnd *)this) + 251) = v171;
  *((_DWORD *)((UIWnd *)this) + 255) = v171;
  v172 = *((_DWORD *)((UIWnd *)this) + 248) - *v2;
  *((_DWORD *)((UIWnd *)this) + 258) = v172;
  *((_DWORD *)((UIWnd *)this) + 262) = v172;
  v173 = *((_DWORD *)((UIWnd *)this) + 248) - *((_DWORD *)((UIWnd *)this) + 20);
  *((_DWORD *)((UIWnd *)this) + 259) = v173;
  *((_DWORD *)((UIWnd *)this) + 263) = v173;
  v174 = *((_DWORD *)((UIWnd *)this) + 249) - *((_DWORD *)((UIWnd *)this) + 19);
  *((_DWORD *)((UIWnd *)this) + 260) = v174;
  *((_DWORD *)((UIWnd *)this) + 264) = v174;
  v175 = *((_DWORD *)((UIWnd *)this) + 249) - *((_DWORD *)((UIWnd *)this) + 21);
  *((_DWORD *)((UIWnd *)this) + 261) = v175;
  *((_DWORD *)((UIWnd *)this) + 265) = v175;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "anxi.tga");
  (*(void ( **)(char *, int, char *, CCBUIPanel *, char *, _DWORD))(*((_DWORD *)((UIWnd *)this) + 271) + 32))(
    (char *)((UIWnd *)this) + 1084,
    242,
    (char *)((UIWnd *)this) + 992,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v176);
  *((_BYTE *)&this->m_nPanelOffsetY + 112) = 1;
  (**((void ( ***)(char *, _DWORD))((UIWnd *)this) + 271))((char *)((char *)((UIWnd *)this) + 1084), (_DWORD)(0));
  *((_BYTE *)&this->m_nPanelOffsetY + 113) = 0;
  this->m_Slots[6].m_nPosX = 85;
  this->m_Slots[6].m_nPosY = 155;
  this->m_Slots[6].m_nDimH = 625;
  this->m_Slots[6].m_nDimH2 = 625;
  this->m_Slots[6].m_fDimH = 625.0f;
  *(_DWORD *)&this->m_Slots[6] = 1386;
  this->m_Slots[6].m_nMarginX2 = 1386;
  this->m_Slots[6].m_fMarginX = 1386.0f;
  v177 = this->m_Slots[6].m_nPosX;
  v178 = (int)this->m_Slots[6];
  this->m_Slots[6].m_nEdgeR = v177 + v178;
  this->m_Slots[6].m_nEdgeR2 = v177 + v178;
  v179 = this->m_Slots[6].m_nPosY + this->m_Slots[6].m_nDimH;
  this->m_Slots[6].m_nEdgeB = v179;
  this->m_Slots[6].m_nEdgeB2 = v179;
  v180 = *(_DWORD *)&this->m_Slots[6] - *v2;
  this->m_Slots[6].m_nClipL = v180;
  this->m_Slots[6].m_nClipL2 = v180;
  v181 = *(_DWORD *)&this->m_Slots[6] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[6].m_nClipT = v181;
  this->m_Slots[6].m_nClipT2 = v181;
  v182 = this->m_Slots[6].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[6].m_nClipR = v182;
  this->m_Slots[6].m_nClipR2 = v182;
  v183 = this->m_Slots[6].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[6].m_nClipB = v183;
  this->m_Slots[6].m_nClipB2 = v183;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "haidicheng.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[6].m_Widget
                                                                                    + 32))(
    this->m_Slots[6].m_Widget,
    261,
    &this->m_Slots[6],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v184);
  this->m_Slots[6].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[6].m_Widget)((char *)(this->m_Slots[6].m_Widget), (_DWORD)(0));
  this->m_Slots[6].m_Widget[377] = 0;
  this->m_Slots[11].m_nPosX = 155;
  this->m_Slots[11].m_nPosY = 139;
  this->m_Slots[11].m_nDimH = 784;
  this->m_Slots[11].m_nDimH2 = 784;
  this->m_Slots[11].m_fDimH = 784.0f;
  *(_DWORD *)&this->m_Slots[11] = 907;
  this->m_Slots[11].m_nMarginX2 = 907;
  this->m_Slots[11].m_fMarginX = 907.0f;
  v185 = (int)this->m_Slots[11];
  v186 = this->m_Slots[11].m_nPosX;
  this->m_Slots[11].m_nEdgeR = v185 + v186;
  this->m_Slots[11].m_nEdgeR2 = v185 + v186;
  v187 = this->m_Slots[11].m_nDimH + this->m_Slots[11].m_nPosY;
  this->m_Slots[11].m_nEdgeB = v187;
  this->m_Slots[11].m_nEdgeB2 = v187;
  v188 = *(_DWORD *)&this->m_Slots[11] - *v2;
  this->m_Slots[11].m_nClipL = v188;
  this->m_Slots[11].m_nClipL2 = v188;
  v189 = *(_DWORD *)&this->m_Slots[11] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[11].m_nClipT = v189;
  this->m_Slots[11].m_nClipT2 = v189;
  v190 = this->m_Slots[11].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[11].m_nClipR = v190;
  this->m_Slots[11].m_nClipR2 = v190;
  v191 = this->m_Slots[11].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[11].m_nClipB = v191;
  this->m_Slots[11].m_nClipB2 = v191;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "leizhou.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[11].m_Widget
                                                                                    + 32))(
    this->m_Slots[11].m_Widget,
    272,
    &this->m_Slots[11],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v192);
  this->m_Slots[11].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[11].m_Widget)((char *)(this->m_Slots[11].m_Widget), (_DWORD)(0));
  this->m_Slots[11].m_Widget[377] = 0;
  this->m_Slots[19].m_nPosX = 100;
  this->m_Slots[19].m_nPosY = 96;
  this->m_Slots[19].m_nDimH = 918;
  this->m_Slots[19].m_nDimH2 = 918;
  this->m_Slots[19].m_fDimH = 918.0f;
  *(_DWORD *)&this->m_Slots[19] = 748;
  this->m_Slots[19].m_nMarginX2 = 748;
  this->m_Slots[19].m_fMarginX = 748.0f;
  v193 = (int)this->m_Slots[19];
  v194 = this->m_Slots[19].m_nPosX;
  this->m_Slots[19].m_nEdgeR = v193 + v194;
  this->m_Slots[19].m_nEdgeR2 = v193 + v194;
  v195 = this->m_Slots[19].m_nDimH + this->m_Slots[19].m_nPosY;
  this->m_Slots[19].m_nEdgeB = v195;
  this->m_Slots[19].m_nEdgeB2 = v195;
  v196 = *(_DWORD *)&this->m_Slots[19] - *v2;
  this->m_Slots[19].m_nClipL = v196;
  this->m_Slots[19].m_nClipL2 = v196;
  v197 = *(_DWORD *)&this->m_Slots[19] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[19].m_nClipT = v197;
  this->m_Slots[19].m_nClipT2 = v197;
  v198 = this->m_Slots[19].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[19].m_nClipR = v198;
  this->m_Slots[19].m_nClipR2 = v198;
  v199 = this->m_Slots[19].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[19].m_nClipB = v199;
  this->m_Slots[19].m_nClipB2 = v199;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "shenshu.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[19].m_Widget
                                                                                    + 32))(
    this->m_Slots[19].m_Widget,
    280,
    &this->m_Slots[19],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v200);
  this->m_Slots[19].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[19].m_Widget)((char *)(this->m_Slots[19].m_Widget), (_DWORD)(0));
  this->m_Slots[19].m_Widget[377] = 0;
  this->m_Slots[18].m_nPosX = 232;
  this->m_Slots[18].m_nPosY = 166;
  this->m_Slots[18].m_nDimH = 858;
  this->m_Slots[18].m_nDimH2 = 858;
  this->m_Slots[18].m_fDimH = 858.0f;
  *(_DWORD *)&this->m_Slots[18] = 438;
  this->m_Slots[18].m_nMarginX2 = 438;
  this->m_Slots[18].m_fMarginX = 438.0f;
  v201 = this->m_Slots[18].m_nPosX;
  v202 = (int)this->m_Slots[18];
  this->m_Slots[18].m_nEdgeR = v201 + v202;
  this->m_Slots[18].m_nEdgeR2 = v201 + v202;
  v203 = this->m_Slots[18].m_nPosY + this->m_Slots[18].m_nDimH;
  this->m_Slots[18].m_nEdgeB = v203;
  this->m_Slots[18].m_nEdgeB2 = v203;
  v204 = *(_DWORD *)&this->m_Slots[18] - *v2;
  this->m_Slots[18].m_nClipL = v204;
  this->m_Slots[18].m_nClipL2 = v204;
  v205 = *(_DWORD *)&this->m_Slots[18] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[18].m_nClipT = v205;
  this->m_Slots[18].m_nClipT2 = v205;
  v206 = this->m_Slots[18].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[18].m_nClipR = v206;
  this->m_Slots[18].m_nClipR2 = v206;
  v207 = this->m_Slots[18].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[18].m_nClipB = v207;
  this->m_Slots[18].m_nClipB2 = v207;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "shenjietianmen.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[18].m_Widget
                                                                                    + 32))(
    this->m_Slots[18].m_Widget,
    279,
    &this->m_Slots[18],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v208);
  this->m_Slots[18].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[18].m_Widget)((char *)(this->m_Slots[18].m_Widget), (_DWORD)(0));
  this->m_Slots[18].m_Widget[377] = 0;
  this->m_Slots[12].m_nPosX = 174;
  this->m_Slots[12].m_nPosY = 132;
  this->m_Slots[12].m_nDimH = 778;
  this->m_Slots[12].m_nDimH2 = 778;
  this->m_Slots[12].m_fDimH = 778.0f;
  *(_DWORD *)&this->m_Slots[12] = 311;
  this->m_Slots[12].m_nMarginX2 = 311;
  this->m_Slots[12].m_fMarginX = 311.0f;
  v209 = this->m_Slots[12].m_nPosX;
  v210 = (int)this->m_Slots[12];
  this->m_Slots[12].m_nEdgeR = v209 + v210;
  this->m_Slots[12].m_nEdgeR2 = v209 + v210;
  v211 = this->m_Slots[12].m_nPosY + this->m_Slots[12].m_nDimH;
  this->m_Slots[12].m_nEdgeB = v211;
  this->m_Slots[12].m_nEdgeB2 = v211;
  v212 = *(_DWORD *)&this->m_Slots[12] - *v2;
  this->m_Slots[12].m_nClipL = v212;
  this->m_Slots[12].m_nClipL2 = v212;
  v213 = *(_DWORD *)&this->m_Slots[12] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[12].m_nClipT = v213;
  this->m_Slots[12].m_nClipT2 = v213;
  v214 = this->m_Slots[12].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[12].m_nClipR = v214;
  this->m_Slots[12].m_nClipR2 = v214;
  v215 = this->m_Slots[12].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[12].m_nClipB = v215;
  this->m_Slots[12].m_nClipB2 = v215;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "manzhou.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[12].m_Widget
                                                                                    + 32))(
    this->m_Slots[12].m_Widget,
    273,
    &this->m_Slots[12],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v216);
  this->m_Slots[12].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[12].m_Widget)((char *)(this->m_Slots[12].m_Widget), (_DWORD)(0));
  this->m_Slots[12].m_Widget[377] = 0;
  this->m_Slots[13].m_nPosX = 141;
  this->m_Slots[13].m_nPosY = 145;
  this->m_Slots[13].m_nDimH = 880;
  this->m_Slots[13].m_nDimH2 = 880;
  this->m_Slots[13].m_fDimH = 880.0f;
  *(_DWORD *)&this->m_Slots[13] = 226;
  this->m_Slots[13].m_nMarginX2 = 226;
  this->m_Slots[13].m_fMarginX = 226.0f;
  v217 = (int)this->m_Slots[13];
  v218 = this->m_Slots[13].m_nPosX;
  this->m_Slots[13].m_nEdgeR = v217 + v218;
  this->m_Slots[13].m_nEdgeR2 = v217 + v218;
  v219 = this->m_Slots[13].m_nDimH + this->m_Slots[13].m_nPosY;
  this->m_Slots[13].m_nEdgeB = v219;
  this->m_Slots[13].m_nEdgeB2 = v219;
  v220 = *(_DWORD *)&this->m_Slots[13] - *v2;
  this->m_Slots[13].m_nClipL = v220;
  this->m_Slots[13].m_nClipL2 = v220;
  v221 = *(_DWORD *)&this->m_Slots[13] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[13].m_nClipT = v221;
  this->m_Slots[13].m_nClipT2 = v221;
  v222 = this->m_Slots[13].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[13].m_nClipR = v222;
  this->m_Slots[13].m_nClipR2 = v222;
  v223 = this->m_Slots[13].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[13].m_nClipB = v223;
  this->m_Slots[13].m_nClipB2 = v223;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "mohuankongjian.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[13].m_Widget
                                                                                    + 32))(
    this->m_Slots[13].m_Widget,
    274,
    &this->m_Slots[13],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v224);
  this->m_Slots[13].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[13].m_Widget)((char *)(this->m_Slots[13].m_Widget), (_DWORD)(0));
  this->m_Slots[13].m_Widget[377] = 0;
  this->m_Slots[24].m_nPosX = 161;
  this->m_Slots[24].m_nPosY = 92;
  this->m_Slots[24].m_nDimH = 716;
  this->m_Slots[24].m_nDimH2 = 716;
  this->m_Slots[24].m_fDimH = 716.0f;
  *(_DWORD *)&this->m_Slots[24] = 164;
  this->m_Slots[24].m_nMarginX2 = 164;
  this->m_Slots[24].m_fMarginX = 164.0f;
  v225 = (int)this->m_Slots[24];
  v226 = this->m_Slots[24].m_nPosX;
  this->m_Slots[24].m_nEdgeR = v225 + v226;
  this->m_Slots[24].m_nEdgeR2 = v225 + v226;
  v227 = this->m_Slots[24].m_nDimH + this->m_Slots[24].m_nPosY;
  this->m_Slots[24].m_nEdgeB = v227;
  this->m_Slots[24].m_nEdgeB2 = v227;
  v228 = *(_DWORD *)&this->m_Slots[24] - *v2;
  this->m_Slots[24].m_nClipL = v228;
  this->m_Slots[24].m_nClipL2 = v228;
  v229 = *(_DWORD *)&this->m_Slots[24] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[24].m_nClipT = v229;
  this->m_Slots[24].m_nClipT2 = v229;
  v230 = this->m_Slots[24].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[24].m_nClipR = v230;
  this->m_Slots[24].m_nClipR2 = v230;
  v231 = this->m_Slots[24].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[24].m_nClipB = v231;
  this->m_Slots[24].m_nClipB2 = v231;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "xianrendong.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[24].m_Widget
                                                                                    + 32))(
    this->m_Slots[24].m_Widget,
    291,
    &this->m_Slots[24],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v232);
  this->m_Slots[24].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[24].m_Widget)((char *)(this->m_Slots[24].m_Widget), (_DWORD)(0));
  this->m_Slots[24].m_Widget[377] = 0;
  this->m_Slots[3].m_nPosX = 134;
  this->m_Slots[3].m_nPosY = 108;
  this->m_Slots[3].m_nDimH = 832;
  this->m_Slots[3].m_nDimH2 = 832;
  this->m_Slots[3].m_fDimH = 832.0f;
  *(_DWORD *)&this->m_Slots[3] = 81;
  this->m_Slots[3].m_nMarginX2 = 81;
  this->m_Slots[3].m_fMarginX = 81.0f;
  v233 = this->m_Slots[3].m_nPosX;
  v234 = (int)this->m_Slots[3];
  this->m_Slots[3].m_nEdgeR = v233 + v234;
  this->m_Slots[3].m_nEdgeR2 = v233 + v234;
  v235 = this->m_Slots[3].m_nPosY + this->m_Slots[3].m_nDimH;
  this->m_Slots[3].m_nEdgeB = v235;
  this->m_Slots[3].m_nEdgeB2 = v235;
  v236 = *(_DWORD *)&this->m_Slots[3] - *v2;
  this->m_Slots[3].m_nClipL = v236;
  this->m_Slots[3].m_nClipL2 = v236;
  v237 = *(_DWORD *)&this->m_Slots[3] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[3].m_nClipT = v237;
  this->m_Slots[3].m_nClipT2 = v237;
  v238 = this->m_Slots[3].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[3].m_nClipR = v238;
  this->m_Slots[3].m_nClipR2 = v238;
  v239 = this->m_Slots[3].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[3].m_nClipB = v239;
  this->m_Slots[3].m_nClipB2 = v239;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "guchengzhen.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[3].m_Widget
                                                                                    + 32))(
    this->m_Slots[3].m_Widget,
    258,
    &this->m_Slots[3],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v240);
  this->m_Slots[3].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[3].m_Widget)((char *)(this->m_Slots[3].m_Widget), (_DWORD)(0));
  this->m_Slots[3].m_Widget[377] = 0;
  *(&this->m_nTodo_1792.m_hTexture + 4) = 142;
  *(&this->m_nTodo_1792.m_hTexture + 5) = 106;
  this->m_nTodo_1792.m_nColors = 419;
  LODWORD(this->m_nTodo_1792.m_fCameraOffset) = 419;
  this->m_nTodo_1792.m_hFont = 1137803264;
  this->m_nTodo_1792.m_hScrollBar = 671;
  LODWORD(this->m_nTodo_1792.m_fAngle) = 671;
  this->m_nTodo_1792.m_bVisible = ((Parent_Data *)((Parent_Data *)1143455744));
  v241 = *(&this->m_nTodo_1792.m_hTexture + 4);
  m_hScrollBar = this->m_nTodo_1792.m_hScrollBar;
  this->m_nTodo_1792.m_bLoadState = v241 + m_hScrollBar;
  this->m_nTodo_1792.m_bFieldCC = ((Parent_Data *)((Parent_Data *)(v241 + m_hScrollBar)));
  v243 = (char *)(*(&this->m_nTodo_1792.m_hTexture + 5) + this->m_nTodo_1792.m_nColors);
  this->m_nTodo_1792.m_pChildData = ((char *)(v243));
  this->m_nTodo_1792.m_nFieldD0 = (int)v243;
  v244 = (Parent_Data *)(this->m_nTodo_1792.m_hScrollBar - *v2);
  this->m_nTodo_1792.m_bEnabled = ((Parent_Data *)(v244));
  this->m_nTodo_1792.m_hTexture = (int)v244;
  v245 = (gbTexture *)(this->m_nTodo_1792.m_hScrollBar - *((_DWORD *)((UIWnd *)this) + 20));
  this->m_nTodo_1792.m_pTexture = ((gbTexture *)(v245));
  *(&this->m_nTodo_1792.m_hTexture + 1) = (int)v245;
  v246 = this->m_nTodo_1792.m_nColors - *((_DWORD *)((UIWnd *)this) + 19);
  *(_DWORD *)&this->m_nTodo_1792.m_bOverlayRender = v246;
  *(&this->m_nTodo_1792.m_hTexture + 2) = v246;
  v247 = this->m_nTodo_1792.m_nColors - *((_DWORD *)((UIWnd *)this) + 21);
  *(_DWORD *)&this->m_nTodo_1792.m_bCursorLeft = v247;
  *(&this->m_nTodo_1792.m_hTexture + 3) = v247;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "bishan.tga");
  (*(void ( **)(int *, int, int *, CCBUIPanel *, char *, _DWORD))(*(&this->m_nTodo_1792.m_hTexture
                                                                                                  + 9)
                                                                                                + 32))(
    &this->m_nTodo_1792.m_hTexture + 9,
    244,
    &this->m_nTodo_1792.m_hScrollBar,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v248);
  LOBYTE(this->m_Static_2288.m_ppicInfo) = 1;
  (**((void ( ***)(int *, _DWORD))&this->m_nTodo_1792.m_hTexture + 9))((int *)(&this->m_nTodo_1792.m_hTexture + 9), (_DWORD)(0));
  BYTE1(this->m_Static_2288.m_ppicInfo) = 0;
  LODWORD(this->m_nTodo_2896.m_fScaleY) = 110;
  LODWORD(this->m_nTodo_2896.m_fScaleX) = 103;
  this->m_nTodo_2896.m_fontcolor.Color = 675;
  this->m_nTodo_2896.m_rect.top = 675;
  this->m_nTodo_2896.m_childs.m_pData = ((char *)((char *)1143521280));
  *(_DWORD *)((UIWnd *)&this->m_nTodo_2896) = 440;
  this->m_nTodo_2896.m_rect.left = 440;
  this->m_nTodo_2896.m_pfather = ((UIWnd *)((UIWnd *)1138491392));
  v249 = (int)((UIWnd *)&this->m_nTodo_2896);
  m_fScaleY = this->m_nTodo_2896.m_fScaleY;
  this->m_nTodo_2896.m_wndcolor.Color = v249 + LODWORD(m_fScaleY);
  this->m_nTodo_2896.m_rect.right = v249 + LODWORD(m_fScaleY);
  v251 = this->m_nTodo_2896.m_fontcolor.Color + LODWORD(this->m_nTodo_2896.m_fScaleX);
  this->m_nTodo_2896.m_id = v251;
  this->m_nTodo_2896.m_rect.bottom = v251;
  v252 = *(_DWORD *)((UIWnd *)&this->m_nTodo_2896) - *v2;
  this->m_nTodo_2896.m_childs.capacity = v252;
  this->m_nTodo_2896.m_bvisible = v252;
  v253 = *(_DWORD *)((UIWnd *)&this->m_nTodo_2896) - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_nTodo_2896.m_childs.m_nSize = v253;
  this->m_nTodo_2896.m_benable = v253;
  v254 = this->m_nTodo_2896.m_fontcolor.Color - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_nTodo_2896.m_childs.m_needscriptdel = v254;
  this->m_nTodo_2896.m_bfocus = v254;
  v255 = this->m_nTodo_2896.m_fontcolor.Color - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_nTodo_2896.m_bcreateok = v255;
  this->m_nTodo_2896.m_nViewW = v255;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "chaohai.tga");
  (*(void ( **)(int *, int, UIScene *, CCBUIPanel *, char *, _DWORD))(this->m_nTodo_2896.m_nShowState
                                                                                         + 32))(
    &this->m_nTodo_2896.m_nShowState,
    246,
    &this->m_nTodo_2896,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v256);
  LOBYTE(this->m_nTodo_3240.m_nRectW) = 1;
  (*(void ( **)(int *, _DWORD))this->m_nTodo_2896.m_nShowState)(
    &this->m_nTodo_2896.m_nShowState,
    0);
  BYTE1(this->m_nTodo_3240.m_nRectW) = 0;
  *(_DWORD *)&this->m_nTodo_3240.m_bCursorLeft = 97;
  this->m_nTodo_3240.m_hTexture = 85;
  this->m_nTodo_3240.m_nPosY = 195;
  this->m_nTodo_3240.m_hScrollBar = 195;
  this->m_nTodo_3240.m_fAngle = 195.0f;
  this->m_nTodo_3240.m_nPosX = 1113;
  this->m_nTodo_3240.m_dwColor = 1113;
  this->m_nTodo_3240.m_pChildData = ((char *)((char *)1149968384));
  v257 = this->m_nTodo_3240.m_nPosX;
  v258 = *(_DWORD *)&this->m_nTodo_3240.m_bCursorLeft;
  this->m_nTodo_3240.m_nLoadResource = v257 + v258;
  this->m_nTodo_3240.m_nColors = v257 + v258;
  v259 = this->m_nTodo_3240.m_nPosY + this->m_nTodo_3240.m_hTexture;
  this->m_nTodo_3240.m_nNotifyRender = v259;
  this->m_nTodo_3240.m_bLoadState = v259;
  LODWORD(v260) = this->m_nTodo_3240.m_nPosX - *v2;
  this->m_nTodo_3240.m_fCameraOffset = v260;
  *(float *)&this->m_nTodo_3240.m_hFont = v260;
  v261 = (Parent_Data *)(this->m_nTodo_3240.m_nPosX - *((_DWORD *)((UIWnd *)this) + 20));
  this->m_nTodo_3240.m_bFieldCC = ((Parent_Data *)(v261));
  this->m_nTodo_3240.m_bEnabled = ((Parent_Data *)(v261));
  v262 = (gbTexture *)(this->m_nTodo_3240.m_nPosY - *((_DWORD *)((UIWnd *)this) + 19));
  this->m_nTodo_3240.m_nFieldD0 = (int)v262;
  this->m_nTodo_3240.m_pTexture = ((gbTexture *)(v262));
  v263 = (Parent_Data *)(this->m_nTodo_3240.m_nPosY - *((_DWORD *)((UIWnd *)this) + 21));
  this->m_nTodo_3240.m_bVisible = ((Parent_Data *)(v263));
  *(_DWORD *)&this->m_nTodo_3240.m_bOverlayRender = (_DWORD)v263;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "chuanchangjiang.tga");
  (*(void ( **)(int *, int, int *, CCBUIPanel *, char *, _DWORD))(*(&this->m_nTodo_3240.m_hTexture
                                                                                                  + 4)
                                                                                                + 32))(
    &this->m_nTodo_3240.m_hTexture + 4,
    247,
    &this->m_nTodo_3240.m_nPosX,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v264);
  *((_BYTE *)&this->m_nTodo_3584.m_hTexture + 48) = 1;
  (**((void ( ***)(int *, _DWORD))&this->m_nTodo_3240.m_hTexture + 4))((int *)(&this->m_nTodo_3240.m_hTexture + 4), (_DWORD)(0));
  *((_BYTE *)&this->m_nTodo_3584.m_hTexture + 49) = 0;
  *(&this->m_nTodo_3584.m_hTexture + 32) = 113;
  *(&this->m_nTodo_3584.m_hTexture + 33) = 83;
  *(&this->m_nTodo_3584.m_hTexture + 15) = 138;
  *(&this->m_nTodo_3584.m_hTexture + 19) = 138;
  *(&this->m_nTodo_3584.m_hTexture + 23) = 1124728832;
  *(&this->m_nTodo_3584.m_hTexture + 14) = 1405;
  *(&this->m_nTodo_3584.m_hTexture + 18) = 1405;
  *(&this->m_nTodo_3584.m_hTexture + 22) = 1152360448;
  v265 = *(&this->m_nTodo_3584.m_hTexture + 32);
  v266 = *(&this->m_nTodo_3584.m_hTexture + 14);
  *(&this->m_nTodo_3584.m_hTexture + 16) = v265 + v266;
  *(&this->m_nTodo_3584.m_hTexture + 20) = v265 + v266;
  v267 = *(&this->m_nTodo_3584.m_hTexture + 33) + *(&this->m_nTodo_3584.m_hTexture + 15);
  *(&this->m_nTodo_3584.m_hTexture + 17) = v267;
  *(&this->m_nTodo_3584.m_hTexture + 21) = v267;
  v268 = *(&this->m_nTodo_3584.m_hTexture + 14) - *v2;
  *(&this->m_nTodo_3584.m_hTexture + 24) = v268;
  *(&this->m_nTodo_3584.m_hTexture + 28) = v268;
  v269 = *(&this->m_nTodo_3584.m_hTexture + 14) - *((_DWORD *)((UIWnd *)this) + 20);
  *(&this->m_nTodo_3584.m_hTexture + 25) = v269;
  *(&this->m_nTodo_3584.m_hTexture + 29) = v269;
  v270 = *(&this->m_nTodo_3584.m_hTexture + 15) - *((_DWORD *)((UIWnd *)this) + 19);
  *(&this->m_nTodo_3584.m_hTexture + 26) = v270;
  *(&this->m_nTodo_3584.m_hTexture + 30) = v270;
  v271 = *(&this->m_nTodo_3584.m_hTexture + 15) - *((_DWORD *)((UIWnd *)this) + 21);
  *(&this->m_nTodo_3584.m_hTexture + 27) = v271;
  *(&this->m_nTodo_3584.m_hTexture + 31) = v271;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "chuanhai.tga");
  (*(void ( **)(unsigned int *, int, int *, CCBUIPanel *, char *, _DWORD))(this->m_nTodo_3928.m_id
                                                                                                  + 32))(
    &this->m_nTodo_3928.m_id,
    248,
    &this->m_nTodo_3584.m_hTexture + 14,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v272);
  this->m_bActive = 1;
  (*(void ( **)(unsigned int *, _DWORD))this->m_nTodo_3928.m_id)(&this->m_nTodo_3928.m_id, 0);
  *(&this->m_bActive + 1) = 0;
  this->m_Slots[0].m_nPosX = 214;
  this->m_Slots[0].m_nPosY = 149;
  this->m_Slots[0].m_nDimH = 417;
  this->m_Slots[0].m_nDimH2 = 417;
  this->m_Slots[0].m_fDimH = 417.0f;
  *(_DWORD *)this->m_Slots = 923;
  this->m_Slots[0].m_nMarginX2 = 923;
  this->m_Slots[0].m_fMarginX = 923.0f;
  v273 = this->m_Slots[0].m_nPosX;
  v274 = (int)this->m_Slots[0];
  this->m_Slots[0].m_nEdgeR = v273 + v274;
  this->m_Slots[0].m_nEdgeR2 = v273 + v274;
  v275 = this->m_Slots[0].m_nPosY + this->m_Slots[0].m_nDimH;
  this->m_Slots[0].m_nEdgeB = v275;
  this->m_Slots[0].m_nEdgeB2 = v275;
  v276 = *(_DWORD *)this->m_Slots - *v2;
  this->m_Slots[0].m_nClipL = v276;
  this->m_Slots[0].m_nClipL2 = v276;
  v277 = *(_DWORD *)this->m_Slots - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[0].m_nClipT = v277;
  this->m_Slots[0].m_nClipT2 = v277;
  v278 = this->m_Slots[0].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[0].m_nClipR = v278;
  this->m_Slots[0].m_nClipR2 = v278;
  v279 = this->m_Slots[0].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[0].m_nClipB = v279;
  this->m_Slots[0].m_nClipB2 = v279;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "dadukou.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[0].m_Widget
                                                                                    + 32))(
    this->m_Slots[0].m_Widget,
    249,
    this->m_Slots,
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v280);
  this->m_Slots[0].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[0].m_Widget)((char *)(this->m_Slots[0].m_Widget), (_DWORD)(0));
  this->m_Slots[0].m_Widget[377] = 0;
  this->m_Slots[4].m_nPosX = 182;
  this->m_Slots[4].m_nPosY = 136;
  this->m_Slots[4].m_nDimH = 590;
  this->m_Slots[4].m_nDimH2 = 590;
  this->m_Slots[4].m_fDimH = 590.0f;
  *(_DWORD *)&this->m_Slots[4] = 94;
  this->m_Slots[4].m_nMarginX2 = 94;
  this->m_Slots[4].m_fMarginX = 94.0f;
  v281 = (int)this->m_Slots[4];
  v282 = this->m_Slots[4].m_nPosX;
  this->m_Slots[4].m_nEdgeR = v281 + v282;
  this->m_Slots[4].m_nEdgeR2 = v281 + v282;
  v283 = this->m_Slots[4].m_nDimH + this->m_Slots[4].m_nPosY;
  this->m_Slots[4].m_nEdgeB = v283;
  this->m_Slots[4].m_nEdgeB2 = v283;
  v284 = *(_DWORD *)&this->m_Slots[4] - *v2;
  this->m_Slots[4].m_nClipL = v284;
  this->m_Slots[4].m_nClipL2 = v284;
  v285 = *(_DWORD *)&this->m_Slots[4] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[4].m_nClipT = v285;
  this->m_Slots[4].m_nClipT2 = v285;
  v286 = this->m_Slots[4].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[4].m_nClipR = v286;
  this->m_Slots[4].m_nClipR2 = v286;
  v287 = this->m_Slots[4].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[4].m_nClipB = v287;
  this->m_Slots[4].m_nClipB2 = v287;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "gutenglin.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[4].m_Widget
                                                                                    + 32))(
    this->m_Slots[4].m_Widget,
    259,
    &this->m_Slots[4],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v288);
  this->m_Slots[4].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[4].m_Widget)((char *)(this->m_Slots[4].m_Widget), (_DWORD)(0));
  this->m_Slots[4].m_Widget[377] = 0;
  this->m_Slots[9].m_nPosX = 143;
  this->m_Slots[9].m_nPosY = 117;
  this->m_Slots[9].m_nDimH = 47;
  this->m_Slots[9].m_nDimH2 = 47;
  this->m_Slots[9].m_fDimH = 47.0f;
  *(_DWORD *)&this->m_Slots[9] = 357;
  this->m_Slots[9].m_nMarginX2 = 357;
  this->m_Slots[9].m_fMarginX = 357.0f;
  v289 = (int)this->m_Slots[9];
  v290 = this->m_Slots[9].m_nPosX;
  this->m_Slots[9].m_nEdgeR = v289 + v290;
  this->m_Slots[9].m_nEdgeR2 = v289 + v290;
  v291 = this->m_Slots[9].m_nDimH + this->m_Slots[9].m_nPosY;
  this->m_Slots[9].m_nEdgeB = v291;
  this->m_Slots[9].m_nEdgeB2 = v291;
  v292 = *(_DWORD *)&this->m_Slots[9] - *v2;
  this->m_Slots[9].m_nClipL = v292;
  this->m_Slots[9].m_nClipL2 = v292;
  v293 = *(_DWORD *)&this->m_Slots[9] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[9].m_nClipT = v293;
  this->m_Slots[9].m_nClipT2 = v293;
  v294 = this->m_Slots[9].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[9].m_nClipR = v294;
  this->m_Slots[9].m_nClipR2 = v294;
  v295 = this->m_Slots[9].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[9].m_nClipB = v295;
  this->m_Slots[9].m_nClipB2 = v295;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "jiudingshan.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[9].m_Widget
                                                                                    + 32))(
    this->m_Slots[9].m_Widget,
    264,
    &this->m_Slots[9],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v296);
  this->m_Slots[9].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[9].m_Widget)((char *)(this->m_Slots[9].m_Widget), (_DWORD)(0));
  this->m_Slots[9].m_Widget[377] = 0;
  this->m_Slots[10].m_nPosX = 120;
  this->m_Slots[10].m_nPosY = 111;
  this->m_Slots[10].m_nDimH = 555;
  this->m_Slots[10].m_nDimH2 = 555;
  this->m_Slots[10].m_fDimH = 555.0f;
  *(_DWORD *)&this->m_Slots[10] = 728;
  this->m_Slots[10].m_nMarginX2 = 728;
  this->m_Slots[10].m_fMarginX = 728.0f;
  v297 = this->m_Slots[10].m_nPosX;
  v298 = (int)this->m_Slots[10];
  this->m_Slots[10].m_nEdgeR = v297 + v298;
  this->m_Slots[10].m_nEdgeR2 = v297 + v298;
  v299 = this->m_Slots[10].m_nPosY + this->m_Slots[10].m_nDimH;
  this->m_Slots[10].m_nEdgeB = v299;
  this->m_Slots[10].m_nEdgeB2 = v299;
  v300 = *(_DWORD *)&this->m_Slots[10] - *v2;
  this->m_Slots[10].m_nClipL = v300;
  this->m_Slots[10].m_nClipL2 = v300;
  v301 = *(_DWORD *)&this->m_Slots[10] - *((_DWORD *)((UIWnd *)this) + 20);
  this->m_Slots[10].m_nClipT = v301;
  this->m_Slots[10].m_nClipT2 = v301;
  v302 = this->m_Slots[10].m_nDimH - *((_DWORD *)((UIWnd *)this) + 19);
  this->m_Slots[10].m_nClipR = v302;
  this->m_Slots[10].m_nClipR2 = v302;
  v303 = this->m_Slots[10].m_nDimH - *((_DWORD *)((UIWnd *)this) + 21);
  this->m_Slots[10].m_nClipB = v303;
  this->m_Slots[10].m_nClipB2 = v303;
  sprintf((char *const)((UIWnd *)this) + 104, "%s%s", g_szDataPath, "jiulongpo.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, char *, _DWORD))(*(_DWORD *)this->m_Slots[10].m_Widget
                                                                                    + 32))(
    this->m_Slots[10].m_Widget,
    265,
    &this->m_Slots[10],
    this,
    (char *)((UIWnd *)this) + 104,
    0);
  CCBUIPanel_SetUserData(*v304);
  this->m_Slots[10].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[10].m_Widget)((char *)(this->m_Slots[10].m_Widget), (_DWORD)(0));
  this->m_Slots[10].m_Widget[377] = 0;
  this->m_nTodo_48AC = 0;
  *(_DWORD *)&this->m_Slots[29].m_Widget[380] = 0;
  this->m_nTodo_48B0 = 64;
  this->m_nTodo_48B4 = this->m_nTodo_48AC + 64;
  (*(void ( **)(int *, int, char *, CCBUIPanel *))(this->m_EmbedPalScript + 16))(
    &this->m_EmbedPalScript,
    240,
    &this->m_Slots[29].m_Widget[380],
    this);
  (((UIScene *)&this->m_EmbedPalScript))->UIScene::LoadResource((void *)off_59959C);
  UIScene_SetController(1084227584);
  *(float *)&this->m_nTodo_495C = (float)*(int *)&this->m_Slots[29].m_Widget[380];
  *(float *)&this->m_nTodo_4960 = (float)this->m_nTodo_48AC;
  this->m_nTodo_4964 = (__int64)*(float *)&this->m_nTodo_495C;
  this->m_nTodo_4968 = (__int64)*(float *)&this->m_nTodo_4960;
  this->m_nTodo_498C = 1123024896;
  v315 = 200;
  v314 = 250;
  v316 = 550;
  v317 = 300;
  Create__ovl_1((ARC_PlayerAtt *)&this->m_EmbedPlayerAtt);
  (((UIItem *)&this->m_EmbedPlayerAtt))->UIItem::SetData(31);
  Create__ovl_1((ARC_PlayerAtt *)&this->m_nPlayerAttOverlay);
  (((UIItem *)&this->m_nPlayerAttOverlay))->UIItem::SetData(31);
  v305 = *(&this->m_nPlayerAttOverlay + 20);
  v306 = *(&this->m_nPlayerAttOverlay + 22);
  *(&this->m_nPlayerAttOverlay + 25) = *(&this->m_nPlayerAttOverlay + 21) + 26;
  *(&this->m_nPlayerAttOverlay + 24) = v305 + 6;
  v307 = *(&this->m_nPlayerAttOverlay + 23) - 38;
  *((_DWORD *)&this->m_EmbedCaption + 222) = 0;
  *(_DWORD *)this->m_Data = 20;
  *(&this->m_nPlayerAttOverlay + 26) = v306 - 6;
  *(&this->m_nPlayerAttOverlay + 27) = v307;
  (((UIWnd *)&this->m_EmbedCaption))->UIWnd::sub_445FA0(&this->m_nPlayerAttOverlay + 24);
  (((PalScript *)&this->m_Data[20]))->PalScript::LoadFromFile("datascript\\SceneName.txt");
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    v311 = (gbAudioManager *)AudioManager;
    if ( AudioManager )
    {
      (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
      (((gbAudioManager *)v311))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v311))->gbAudioManager::StopSoundStream(2);
      v312 = (CScreenMode *)CScreenMode::GetInstance();
      (((SoundMgr *)v312))->SoundMgr::PlayCPKStream(1);
    }
  }
  (((UICursor *)v308))->UICursor::_todo_541CC0();
}

// 0x00449990
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void CCBUIPanel::Destroy(UIListBox **thisa)
{
  Destroy__ovl_03((int)this);
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00449B90
char CCBUIPanel::FocusCurrentRole()
{
  unsigned int v2; // edi
  int *v3; // esi
  int v4; // eax

  v2 = 0;
  v3 = (int *)"Q07";
  while ( 1 )
  {
    v4 = _strcmpi((const char *)v3, (const char *)&g_RoleSystemInstance);
    if ( !v4 )
      break;
    v3 += 16;
    ++v2;
    if ( (int)v3 >= (int)&off_599594 )
      return v4;
  }
  CCBUIPanel_CenterSlot(v2);
  return (((CCBProtectWindow *)this))->CCBProtectWindow::ValidateSlot(v2) /* [ROWTABLE] */;
}

// 0x00449C20
void CCBUIPanel::sub_449C20()
{
  char *v2; // esi
  int v3; // edi
  CCBMagicWindow *v4; // [esp+0x0] [ebp-0xC]

  v2 = (char *)((UIWnd *)this) + 608;
  v3 = 38;
  do
  {
    (*(void ( **)(char *))(*(_DWORD *)v2 + 4))(v2);
    v2 += 476;
    --v3;
  }
  while ( v3 );
  (((CCBControlWindow *)this))->CCBControlWindow::Render(v4) /* [ROWTABLE] */;
}

// 0x0044A1B0
BOOL CCBUIPanel::ProcessInput(double st7_0)
{
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  int m_nTodo_4990; // eax
  int v7; // [esp+0x0] [ebp-0x8]
  int v8; // [esp+0x0] [ebp-0x8]

  if ( *((_BYTE *)&this->m_nTodo_4B60 + 885) )
    return (((SceneObj *)this))->SceneObj::Update(SLODWORD(st7_0), SHIDWORD(st7_0)) /* [ROWTABLE] */;
  if ( g_nSceneState != 2 && (g_dwGameFlags & 1) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
  }
  if ( LOBYTE(this->m_nTodo_4988) )
    *((_BYTE *)((UIWnd *)this) + 508) = 1;
  CCBUIPanel_UpdateSlotClipping(v7);
  (((CCBRoleState *)this))->CCBRoleState::UpdateFadeAlpha();
  if ( !UIParabolaCtrl_GetState(v8) )
  {
    CCBUIPanel_SetAllSlotsVisible(0);
    (((UISceneMap *)this))->UISceneMap::ValidateInput(this->m_nTodo_4994) /* [ROWTABLE] */;
  }
  if ( LOBYTE(this->m_nTodo_4988) )
    (((CCBRoleState *)this))->CCBRoleState::UpdateSpringAnim(*(float *)&st7_0);
  if ( !BYTE1(this->m_nTodo_4988) || !LOBYTE(this->m_nTodo_4988) )
    goto LABEL_20;
  m_nTodo_4990 = this->m_nTodo_4990;
  LOBYTE(this->m_nTodo_4988) = 0;
  if ( m_nTodo_4990 )
  {
    if ( m_nTodo_4990 == 1 )
      (((UIScene *)&this->m_EmbedPalScript))->UIScene::LoadResource((void *)off_5995A0);
  }
  else
  {
    (((UIScene *)&this->m_EmbedPalScript))->UIScene::LoadResource((void *)off_59959C);
  }
  if ( this->m_nTodo_4994 <= 0x25u )
  {
    this->CCBUIPanel::ActivateSlot(this->m_nTodo_4994);
    return 1;
  }
  else
  {
LABEL_20:
    StopSceneScripts((const char *)LODWORD(st7_0));
    return (((SceneObj *)this))->SceneObj::Update(SLODWORD(st7_0), SHIDWORD(st7_0)) /* [ROWTABLE] */;
  }
}

// 0x0044A4F0
void CCBUIPanel::ActivateSlot(unsigned int nSlotIdx)
{
  PalScriptMgr *v3; // ecx

  if ( nSlotIdx <= 0x25 )
  {
    LOBYTE(v3) = (unsigned long)CScreenMode::GetInstance()->m_bRenderAlt;
    if ( (_BYTE)v3 )
      CScreenMode::GetInstance()->m_bRenderAlt = 0;
    (((PalScriptMgr *)v3))->PalScriptMgr::Destroy();
    this->m_nTodo_4994 = -1;
    (((CGameData *)&g_gamefrm))->CGameData::Load(0);
  }
}

// 0x0044A540
int CCBUIPanel::OnMessage_a540(int nVal, int nVal2, int nVal3)
{
  int v4; // edi
  int v7; // esi
  int *v8; // eax
  char Destination[253]; // [esp+0x4] [ebp-0x200] BYREF
  __int16 v10; // [esp+0x101] [ebp-0x103]
  char v11; // [esp+0x103] [ebp-0x101]
  char Buffer[253]; // [esp+0x104] [ebp-0x100] BYREF
  __int16 v13; // [esp+0x201] [ebp-0x3]
  char v14; // [esp+0x203] [ebp-0x1]

  if ( nVal == 1000 )
  {
    if ( nVal2 )
    {
      this->m_nTodo_4994 = -1;
      (((CCBRoleState *)this))->CCBRoleState::InitFadeAndSpring();
    }
    return 1;
  }
  else
  {
    if ( nVal != 1001 )
      return this->UIWnd::OnMessage(nVal, nVal2, nVal3);
    v7 = 0;
    v8 = (int *)&dword_56AEE8;
    while ( nVal2 != *v8 )
    {
      ++v8;
      ++v7;
      if ( (int)v8 >= (int)0x56AF80 )
        return 1;
    }
    if ( !LOBYTE(this->m_nTodo_4988) )
    {
      memset(Destination, 0, sizeof(Destination));
      v10 = 0;
      v11 = 0;
      (((PalScript *)&this->m_Data[20]))->PalScript::SetDirectory((char *)&"Q07"[16 * v7]);
      (((PalScript *)&this->m_Data[20]))->PalScript::FindSaveStateString((PalScript *)&dir[12], Destination, (char *)0x100, v4);
      if ( !*((_BYTE *)((UIWnd *)this) + 476 * v7 + 596) )
      {
        sprintf(
          (char *const)((UIWnd *)this) + 104,
          "%s%s%s",
          (const char *)&dword_DDB03C,
          Destination,
          (const char *)&dword_DDB13C);
        SetEnable((UICaption *)&this->m_EmbedCaption);
        (((UIRoleSelect *)&this->m_nPlayerAttOverlay))->UIRoleSelect::SetByte(1);
        return 1;
      }
      sprintf(
        (char *const)((UIWnd *)this) + 104,
        "%s%s%s",
        (const char *)&dword_DD953C,
        Destination,
        (const char *)&dword_DD963C);
      memset(Buffer, 0, sizeof(Buffer));
      v13 = 0;
      v14 = 0;
      sprintf(Buffer, "%s", (char *)((UIWnd *)this) + 104);
      SetEnable((UICaption *)&this->m_nTodo_4B60);
      (((UIRoleSelect *)&this->m_EmbedPlayerAtt))->UIRoleSelect::SetByte(1);
      this->m_nTodo_4994 = v7;
    }
    return 1;
  }
}

// 0x00453D10
void CCBUIPanel::_todo_453D10()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  (((UIFrameContainer *)((char *)((UIWnd *)this) + 360)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)((UIWnd *)this) + 512)))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  (((UIFrameContainer *)&this->m_Static_2136))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_2288))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_2440))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_2592))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Static_2744))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  ((UIRoleDialog *)&this->m_nTodo_3928)->UIRoleDialog::UIRoleDialog();
  this->m_Slots[2].m_fDimH = 0.0f;
  *((_DWORD *)((UIWnd *)this) + 19) = 0;
  *((_DWORD *)((UIWnd *)this) + 18) = 0;
  *((_DWORD *)((UIWnd *)this) + 20) = 800;
  *((_DWORD *)((UIWnd *)this) + 21) = 600;
}

// 0x00454550
char CCBUIPanel::RenderIfUnlocked()
{
  char result; // al
  CCBMagicWindow *v2; // [esp+0x4] [ebp+0x4]

  result = LOBYTE(this->m_Slots[2].m_fMarginX);
  if ( !result )
    (((CCBControlWindow *)this))->CCBControlWindow::Render(v2) /* [ROWTABLE] */;
  return result;
}

// 0x00454560
BOOL CCBUIPanel::ProcessInputIfUnlocked(int nVal, int nVal2)
{
  if ( LOBYTE(this->m_Slots[2].m_fMarginX) )
    return 1;
  else
    return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x00454590
int CCBUIPanel::OnMessage(int nVal, int nVal2, int nVal3)
{
  int v6; // ecx
  int *v7; // eax
  CScreenMode *Instance; // eax
  float m_fDimH; // ecx
  CScreenMode *v10; // eax
  int v11; // ecx
  int *v12; // eax
  int v13; // ecx
  int *v14; // edi
  const void *v15; // [esp-0x8] [ebp-0x10]
  const void *v16; // [esp-0x8] [ebp-0x10]
  int m_nEdgeB2; // [esp-0x4] [ebp-0xC]
  int v18; // [esp+0x0] [ebp-0x8]

  switch ( nVal )
  {
    case 1000:
      if ( nVal2 )
      {
        CCBUIPanel_UpdateButtonVisibility(v18);
        LOBYTE(this->m_Slots[2].m_fMarginX) = 0;
      }
      return 1;
    case 1001:
      v6 = 0;
      v7 = (int *)&dword_56B220;
      do
      {
        if ( nVal2 == *v7 )
        {
          this->m_Slots[2].m_nEdgeB2 = v6 + 1;
          v15 = (const void *)off_5ABBE0;
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v15, 1);
          (((RoleShadow *)this))->RoleShadow::CreateFromTemplate(1u);
          (((LineupComp *)this))->LineupComp::SetVisible(0);
          return 1;
        }
        ++v7;
        ++v6;
      }
      while ( (int)v7 < (int)0x56B22C );
      switch ( nVal2 )
      {
        case 193:
          (((ChoseCompose *)LODWORD(this->m_Slots[2].m_fDimH)))->ChoseCompose::Init(0);
          break;
        case -1431699013:
          m_fDimH = this->m_Slots[2].m_fDimH;
          m_nEdgeB2 = this->m_Slots[2].m_nEdgeB2;
          LOBYTE(this->m_Slots[2].m_fMarginX) = 1;
          (((UICoverFrm *)LODWORD(m_fDimH)))->UICoverFrm::SetCoverTexture(m_nEdgeB2);
          v16 = (const void *)off_5ABBE0;
LABEL_16:
          v10 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v10))->CScreenMode::AudioSetPosition(v16, 1);
          return 1;
        case -1431698501:
          (((RoleShadow *)this))->RoleShadow::CreateFromTemplate(0);
          (((LineupComp *)this))->LineupComp::SetVisible(1u);
          break;
        default:
          return 1;
      }
      v16 = (const void *)off_5ABBE0;
      goto LABEL_16;
    case 1002:
      v11 = 0;
      v12 = (int *)&dword_56B220;
      while ( nVal2 != *v12 )
      {
        ++v12;
        ++v11;
        if ( (int)v12 >= (int)0x56B22C )
          return 1;
      }
      if ( v11 )
      {
        v13 = v11 - 1;
        if ( v13 )
        {
          if ( v13 == 1 )
            sprintf(
              (char *const)((UIWnd *)this) + 104,
              "%s\\n%s\\n%s\\n%s",
              (const char *)&dword_DD313C,
              (const char *)&dword_DD323C,
              (const char *)&dword_DD333C,
              (const char *)&dword_DD343C);
        }
        else
        {
          sprintf(
            (char *const)((UIWnd *)this) + 104,
            "%s\\n%s\\n%s\\n%s",
            (const char *)&dword_DD2D3C,
            (const char *)&dword_DD2E3C,
            (const char *)&dword_DD2F3C,
            (const char *)&dword_DD303C);
        }
      }
      else
      {
        sprintf(
          (char *const)((UIWnd *)this) + 104,
          "%s\\n%s\\n%s",
          (const char *)&dword_DD2A3C,
          (const char *)&dword_DD2B3C,
          (const char *)&dword_DD2C3C);
      }
      SetEnable((UICaption *)((char *)((UIWnd *)this) + 512));
      return 1;
    case 1003:
      v14 = (int *)&dword_56B220;
      do
      {
        if ( nVal2 == *v14 )
          SetEnable((UICaption *)((char *)((UIWnd *)this) + 512));
        ++v14;
      }
      while ( (int)v14 < (int)0x56B22C );
      return 1;
    default:
      return this->UIWnd::OnMessage(nVal, nVal2, nVal3);
  }
}

// 0x0048A170
int CCBUIPanel::InitSlots()
{
  int v2; // eax
  int result; // eax

  *((_DWORD *)((UIWnd *)this) + 24) = 0;
  do
  {
    v2 = *((_DWORD *)((UIWnd *)this) + 24);
    if ( *((_BYTE *)((UIWnd *)this) + v2 + 877) )
    {
      (((UIListBox *)(&this[9].m_Slots[21].m_nPosX + 1223 * v2)))->UIListBox::GetCurSel();
      (((UIListBox *)&this[9].m_Slots[23].m_Widget[4892 * *((_DWORD *)((UIWnd *)this) + 24) + 124]))->UIListBox::GetCurSel();
      (((UIListBox *)&this[9].m_Slots[22].m_Widget[4892 * *((_DWORD *)((UIWnd *)this) + 24) + 52]))->UIListBox::GetCurSel();
      sprintf(
        (char *const)((UIWnd *)this) + 104,
        "%d/%d",
        (int)*(float *)&this[9].m_Slots[21].m_Widget[4892 * *((_DWORD *)((UIWnd *)this) + 24) + 136],
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)((UIWnd *)this) + 24)));
      SetEnable((UICaption *)&this[9].m_Slots[21].m_Widget[4892 * *((_DWORD *)((UIWnd *)this) + 24) + 224]);
      sprintf(
        (char *const)((UIWnd *)this) + 104,
        "%d/%d",
        (int)*(float *)&this[9].m_Slots[23].m_Widget[4892 * *((_DWORD *)((UIWnd *)this) + 24) + 280],
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)((UIWnd *)this) + 24) + 1));
      SetEnable((UICaption *)&this[9].m_Slots[23].m_Widget[4892 * *((_DWORD *)((UIWnd *)this) + 24) + 368]);
      sprintf(
        (char *const)((UIWnd *)this) + 104,
        "%d/%d",
        (int)*(float *)&this[9].m_Slots[22].m_Widget[4892 * *((_DWORD *)((UIWnd *)this) + 24) + 208],
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)((UIWnd *)this) + 24) + 2));
      SetEnable((UICaption *)&this[9].m_Slots[22].m_Widget[4892 * *((_DWORD *)((UIWnd *)this) + 24) + 296]);
    }
    result = *((_DWORD *)((UIWnd *)this) + 24) + 1;
    *((_DWORD *)((UIWnd *)this) + 24) = result;
  }
  while ( result < 5 );
  return result;
}

// 0x004A3EC0
int CCBUIPanel::InitScrollState()
{
  int v2; // eax
  int result; // eax

  *((_DWORD *)((UIWnd *)this) + 24) = 0;
  do
  {
    v2 = *((_DWORD *)((UIWnd *)this) + 24);
    if ( *((_BYTE *)((UIWnd *)this) + v2 + 361) )
    {
      (((UIListBox *)((char *)((UIWnd *)&this[7]) + 3788 * v2 + 964)))->UIListBox::GetCurSel();
      (((UIListBox *)(&this[7].m_nTodo_1792.m_hTexture + 947 * *((_DWORD *)((UIWnd *)this) + 24) + 15)))->UIListBox::GetCurSel();
      (((UIListBox *)(&this[7].m_nGridY + 947 * *((_DWORD *)((UIWnd *)this) + 24))))->UIListBox::GetCurSel();
      sprintf(
        (char *const)((UIWnd *)this) + 104,
        "%d/%d",
        (int)*((float *)((UIWnd *)&this[7]) + 947 * *((_DWORD *)((UIWnd *)this) + 24) + 280),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)((UIWnd *)this) + 24)));
      SetEnable((UICaption *)((char *)((UIWnd *)&this[7]) + 3788 * *((_DWORD *)((UIWnd *)this) + 24) + 1208));
      sprintf(
        (char *const)((UIWnd *)this) + 104,
        "%d/%d",
        (int)*(&this[7].m_Static_2136.m_ratioh + 947 * *((_DWORD *)((UIWnd *)this) + 24)),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)((UIWnd *)this) + 24) + 1));
      SetEnable((UICaption *)((char *)&this[7].m_Static_2288.m_rect + 3788 * *((_DWORD *)((UIWnd *)this) + 24)));
      sprintf(
        (char *const)((UIWnd *)this) + 104,
        "%d/%d",
        (int)*((float *)&this[7].m_pVfTable + 947 * *((_DWORD *)((UIWnd *)this) + 24) + 27),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *((_DWORD *)((UIWnd *)this) + 24) + 2));
      SetEnable((UICaption *)(&this[7].m_pVfTable + 947 * *((_DWORD *)((UIWnd *)this) + 24) + 49));
      sprintf((char *const)((UIWnd *)this) + 104, "%s %d", (const char *)g_bSlotFlag, 0);
      SetEnable((UICaption *)(&this[7].m_nTodo_2896.m_hTexture + 947 * *((_DWORD *)((UIWnd *)this) + 24) + 28));
      sprintf((char *const)((UIWnd *)this) + 104, "%s %d", (const char *)&g_bSlotFlag[256], 0);
      SetEnable((UICaption *)(&this[7].m_nTodo_3240.m_nScrollWidget + 947 * *((_DWORD *)((UIWnd *)this) + 24)));
      sprintf((char *const)((UIWnd *)this) + 104, "%s %d", (const char *)&g_bSlotFlag[512], 0);
      SetEnable((UICaption *)(&this[7].m_nTodo_3240.m_hTexture + 947 * *((_DWORD *)((UIWnd *)this) + 24) + 18));
      sprintf((char *const)((UIWnd *)this) + 104, "%s %d", byte_DC3F3C, 0);
      SetEnable((UICaption *)(&this[7].m_nTodo_3584.m_nScrollIdx + 947 * *((_DWORD *)((UIWnd *)this) + 24)));
      sprintf((char *const)((UIWnd *)this) + 104, "%s %d", byte_DC403C, 0);
      SetEnable((UICaption *)(&this[7].m_nTodo_3584.m_hTexture + 947 * *((_DWORD *)((UIWnd *)this) + 24) + 8));
      sprintf(
        (char *const)((UIWnd *)this) + 104,
        "%s %d %s %d %s %d %s %d",
        (const char *)&g_szRoleName1,
        0,
        (const char *)&g_szRoleName0,
        0,
        (const char *)&g_szRoleName2,
        0,
        (const char *)&g_szRoleName3,
        0);
      SetEnable((UICaption *)(&this[7].m_nTodo_3928.m_childs.m_needscriptdel + 947 * *((_DWORD *)((UIWnd *)this) + 24)));
    }
    result = *((_DWORD *)((UIWnd *)this) + 24) + 1;
    *((_DWORD *)((UIWnd *)this) + 24) = result;
  }
  while ( result < 5 );
  return result;
}
