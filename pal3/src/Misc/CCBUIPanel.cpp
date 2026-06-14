#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CCBUIPanel.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations

int * ctor_0x431870(int *_this); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];
extern char byte_598C14[4];
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern int dword_56AEE8;
extern int dword_56B220[];
extern int dword_DD2A3C;
extern int dword_DD2B3C;
extern int dword_DD2C3C;
extern int dword_DD2D3C;
extern int dword_DD2E3C;
extern int dword_DD2F3C;
extern int dword_DD303C;
extern int dword_DD313C;
extern int dword_DD323C;
extern int dword_DD333C;
extern int dword_DD343C;
extern int dword_DD953C;
extern int dword_DD963C;
extern int dword_DDB03C;
extern int dword_DDB13C;
extern int off_599594;
extern const char * off_59959C;
extern const char * off_5995A0;
extern const char * off_5995A4;
extern const char * off_5995A8;
extern void * off_5ABBE0;
extern vtbl_0056AF80 stru_56AF80;
extern vtbl_0056B22C stru_56B22C;

// 0x004460D0
int * CCBUIPanel::ctor_60D0()
{
// [VFTABLE] ((UIListBox *)&this->__vftable)->UIListBox();
  ((UIFrameWnd *)&this->m_scrollbar.m_texarrayInfo[5])->InitSharedPanel();
  *(_DWORD *)&this->m_Slots[30].m_Widget[140] = 38;
  ((ARC_PlayerAtt *)&this->m_Slots[30].m_Widget[144])->Refresh();
  ((ARC_PlayerAtt *)&this->m_Slots[33].m_Widget[84])->Refresh();
  ctor_0x431870((int *)&this->m_Data[20]);
  *(_DWORD *)&this->m_hasKeyCtrl = 0;
  this->m_showGrayBk = 0;
// [VFTABLE] this->m_scrollbar.__vftable = (vtbl_0056AE2C *)800;
  this->m_scrollbar.m_fontcolor.Color = 600;
  return (int *)this;
}

// 0x00446200
void CCBUIPanel::ctor_6200()
{
  UIListBox **v2; // [esp+0x0] [ebp-0x14]

  this->Destroy(v2, (int)this);
  ((PalScript *)&this->m_Data[20])->Cleanup();
  ((UIRoleDialog *)&this->m_Slots[33].m_Widget[84])->_UIRoleDialog();
  ((UIRoleDialog *)&this->m_Slots[30].m_Widget[144])->_UIRoleDialog();
  ((PalScript *)&this->m_Slots[30].m_nEdgeB)->ctor();
  ((UIFrameWnd *)&this->m_scrollbar.m_texarrayInfo[5])->_UIFrameWnd_ovl();
// [VFTABLE] ((UIListBox *)&this->__vftable)->_UIListBox();
}

// 0x004462C0
void CCBUIPanel::InitPanel()
{
  int *p_m_showGrayBk; // ebp
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int m_nPosX; // ecx
  int m_nMarginX; // edx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int m_nDimH; // ecx
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  void *vftable; // edx
  int v26; // eax
  int v27; // edx
  unsigned int Color; // ecx
  int v29; // ecx
  int v30; // edx
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // ecx
  int v37; // edx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // ecx
  int v44; // edx
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // ecx
  int v51; // edx
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // eax
  int v57; // ecx
  int v58; // edx
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // eax
  int v64; // ecx
  int v65; // edx
  int v66; // eax
  int v67; // eax
  int v68; // eax
  int v69; // eax
  int v70; // eax
  int v71; // ecx
  int v72; // edx
  int v73; // eax
  int v74; // eax
  int v75; // eax
  int v76; // eax
  int v77; // eax
  int v78; // ecx
  int v79; // edx
  int v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // ecx
  int v86; // edx
  int v87; // eax
  int v88; // eax
  int v89; // eax
  int v90; // eax
  int v91; // eax
  int v92; // ecx
  int v93; // edx
  int v94; // eax
  int v95; // eax
  int v96; // eax
  int v97; // eax
  int v98; // eax
  int v99; // ecx
  int v100; // edx
  int v101; // eax
  int v102; // eax
  int v103; // eax
  int v104; // eax
  int v105; // eax
  int v106; // ecx
  int v107; // edx
  int v108; // eax
  int v109; // eax
  int v110; // eax
  int v111; // eax
  int v112; // eax
  _PlugInfo *m_disablepicInfo; // ecx
  int m_bcreateok; // edx
  char *v115; // eax
  char *v116; // eax
  LONG v117; // eax
  char *v118; // eax
  UIWnd *v119; // eax
  int capacity; // ecx
  int width; // edx
  int v122; // eax
  int v123; // eax
  unsigned int v124; // eax
  int v125; // eax
  char *v126; // eax
  int v127; // ecx
  int v128; // edx
  int v129; // eax
  int v130; // eax
  int v131; // eax
  int v132; // eax
  int v133; // eax
  int m_nPanelX; // ecx
  int m_nItemNum; // edx
  int v136; // eax
  int v137; // eax
  int v138; // eax
  int v139; // eax
  int v140; // eax
  int v141; // ecx
  int v142; // edx
  int v143; // eax
  int v144; // eax
  int v145; // eax
  int v146; // eax
  int v147; // eax
  int v148; // ecx
  int v149; // edx
  char *v150; // eax
  int v151; // eax
  unsigned int v152; // eax
  int v153; // eax
  unsigned int v154; // eax
  int v155; // ecx
  int v156; // edx
  int v157; // eax
  int v158; // eax
  int v159; // eax
  int v160; // eax
  int v161; // eax
  int v162; // ecx
  int v163; // edx
  int v164; // eax
  int v165; // eax
  int v166; // eax
  int v167; // eax
  int v168; // eax
  int v169; // ecx
  int v170; // edx
  int v171; // eax
  int v172; // eax
  int v173; // eax
  int v174; // eax
  int v175; // eax
  int v176; // ecx
  int v177; // edx
  int v178; // eax
  int v179; // eax
  int v180; // eax
  int v181; // eax
  int v182; // eax
  int v183; // ecx
  int v184; // edx
  int v185; // eax
  int v186; // eax
  int v187; // eax
  int v188; // eax
  int v189; // eax
  int v190; // ecx
  int v191; // edx
  int v192; // eax
  int v193; // eax
  int v194; // eax
  int v195; // eax
  int v196; // eax
  int v197; // ecx
  int v198; // edx
  int v199; // eax
  int v200; // eax
  int v201; // eax
  int v202; // eax
  int v203; // eax
  int v204; // ecx
  int v205; // edx
  int v206; // eax
  int v207; // eax
  int v208; // eax
  int v209; // eax
  int v210; // eax
  int v211; // ecx
  int m_hScrollBar; // edx
  char *v213; // eax
  Parent_Data *v214; // eax
  gbTexture *v215; // eax
  int v216; // eax
  unsigned int v217; // eax
  void *v218; // ecx
  float m_fScaleY; // edx
  void *v220; // eax
  char *v221; // eax
  int v222; // eax
  int v223; // eax
  int v224; // eax
  int v225; // ecx
  int v226; // edx
  int v227; // eax
  float v228; // eax
  Parent_Data *v229; // eax
  gbTexture *v230; // eax
  Parent_Data *v231; // eax
  int v232; // ecx
  int v233; // edx
  int v234; // eax
  int v235; // eax
  unsigned int v236; // eax
  int v237; // eax
  unsigned int v238; // eax
  int v239; // ecx
  int v240; // edx
  int v241; // eax
  int v242; // eax
  int v243; // eax
  int v244; // eax
  int v245; // eax
  int v246; // ecx
  int v247; // edx
  int v248; // eax
  int v249; // eax
  int v250; // eax
  int v251; // eax
  int v252; // eax
  int v253; // ecx
  int v254; // edx
  int v255; // eax
  int v256; // eax
  int v257; // eax
  int v258; // eax
  int v259; // eax
  int v260; // ecx
  int v261; // edx
  int v262; // eax
  int v263; // eax
  int v264; // eax
  int v265; // eax
  int v266; // eax
  int v267; // ecx
  int v268; // edx
  int v269; // ecx
  UICursor *v270; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v273; // esi
  CScreenMode *v274; // eax
  gbColorQuad v275; // [esp+0x61C] [ebp-0x14] BYREF
  int nVal[4]; // [esp+0x620] [ebp-0x10] BYREF

  p_m_showGrayBk = &this->m_showGrayBk;
// [VFTABLE] ((UIListBox *)&this->__vftable)->SetSelTexture(240, this->m_showGrayBk, *(_DWORD *)&this->m_hasKeyCtrl, (int)this->m_scrollbar.__vftable, this->m_scrollbar.m_fontcolor.Color, 0);
  (*(void ( **)(_PlugInfo **, int, int, int, int, int, int, int, int, CCBUIPanel *))&this->m_scrollbar.m_texarrayInfo[5]->name[24])(
    &this->m_scrollbar.m_texarrayInfo[5],
    240,
    1536,
    1024,
    *p_m_showGrayBk,
    p_m_showGrayBk[1],
    p_m_showGrayBk[2],
    p_m_showGrayBk[3],
    off_599594,
    this);
  this->m_Slots[27].m_nPosX = 146;
  this->m_Slots[27].m_nPosY = 105;
  this->m_Slots[27].m_nDimH = 125;
  this->m_Slots[27].m_nDimH2 = 125;
  this->m_Slots[27].m_fDimH = 125.0;
  this->m_Slots[27].m_nMarginX = 18;
  this->m_Slots[27].m_nMarginX2 = 18;
  this->m_Slots[27].m_fMarginX = 18.0;
  v3 = this->m_Slots[27].m_nMarginX + this->m_Slots[27].m_nPosX;
  this->m_Slots[27].m_nEdgeR = v3;
  this->m_Slots[27].m_nEdgeR2 = v3;
  v4 = this->m_Slots[27].m_nDimH + this->m_Slots[27].m_nPosY;
  this->m_Slots[27].m_nEdgeB = v4;
  this->m_Slots[27].m_nEdgeB2 = v4;
  v5 = this->m_Slots[27].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[27].m_nClipL = v5;
  this->m_Slots[27].m_nClipL2 = v5;
// [VFTABLE] v6 = this->m_Slots[27].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[27].m_nClipT = v6;
  this->m_Slots[27].m_nClipT2 = v6;
  v7 = this->m_Slots[27].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[27].m_nClipR = v7;
  this->m_Slots[27].m_nClipR2 = v7;
  v8 = this->m_Slots[27].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[27].m_nClipB = v8;
  this->m_Slots[27].m_nClipB2 = v8;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "xuelingzhen.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[27].m_Widget
                                                                                    + 32))(
    this->m_Slots[27].m_Widget,
    294,
    &this->m_Slots[27],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[27].m_Widget)->SetUserData();
  this->m_Slots[27].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[27].m_Widget)(this->m_Slots[27].m_Widget, 0);
  this->m_Slots[27].m_Widget[377] = 0;
  this->m_Slots[1].m_nPosX = 104;
  this->m_Slots[1].m_nPosY = 80;
  this->m_Slots[1].m_nDimH = 173;
  this->m_Slots[1].m_nDimH2 = 173;
  this->m_Slots[1].m_fDimH = 173.0;
  this->m_Slots[1].m_nMarginX = 204;
  this->m_Slots[1].m_nMarginX2 = 204;
  this->m_Slots[1].m_fMarginX = 204.0;
  v9 = this->m_Slots[1].m_nMarginX + this->m_Slots[1].m_nPosX;
  this->m_Slots[1].m_nEdgeR = v9;
  this->m_Slots[1].m_nEdgeR2 = v9;
  v10 = this->m_Slots[1].m_nDimH + this->m_Slots[1].m_nPosY;
  this->m_Slots[1].m_nEdgeB = v10;
  this->m_Slots[1].m_nEdgeB2 = v10;
  v11 = this->m_Slots[1].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[1].m_nClipL = v11;
  this->m_Slots[1].m_nClipL2 = v11;
// [VFTABLE] v12 = this->m_Slots[1].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[1].m_nClipT = v12;
  this->m_Slots[1].m_nClipT2 = v12;
  v13 = this->m_Slots[1].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[1].m_nClipR = v13;
  this->m_Slots[1].m_nClipR2 = v13;
  v14 = this->m_Slots[1].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[1].m_nClipB = v14;
  this->m_Slots[1].m_nClipB2 = v14;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "deyang.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[1].m_Widget
                                                                                    + 32))(
    this->m_Slots[1].m_Widget,
    256,
    &this->m_Slots[1],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[1].m_Widget)->SetUserData();
  this->m_Slots[1].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[1].m_Widget)(this->m_Slots[1].m_Widget, 0);
  this->m_Slots[1].m_Widget[377] = 0;
  this->m_Slots[20].m_nPosX = 142;
  this->m_Slots[20].m_nPosY = 189;
  this->m_Slots[20].m_nDimH = 170;
  this->m_Slots[20].m_nDimH2 = 170;
  this->m_Slots[20].m_fDimH = 170.0;
  this->m_Slots[20].m_nMarginX = 406;
  this->m_Slots[20].m_nMarginX2 = 406;
  this->m_Slots[20].m_fMarginX = 406.0;
  m_nPosX = this->m_Slots[20].m_nPosX;
  m_nMarginX = this->m_Slots[20].m_nMarginX;
  this->m_Slots[20].m_nEdgeR = m_nPosX + m_nMarginX;
  this->m_Slots[20].m_nEdgeR2 = m_nPosX + m_nMarginX;
  v17 = this->m_Slots[20].m_nPosY + this->m_Slots[20].m_nDimH;
  this->m_Slots[20].m_nEdgeB = v17;
  this->m_Slots[20].m_nEdgeB2 = v17;
  v18 = this->m_Slots[20].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[20].m_nClipL = v18;
  this->m_Slots[20].m_nClipL2 = v18;
// [VFTABLE] v19 = this->m_Slots[20].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[20].m_nClipT = v19;
  m_nDimH = this->m_Slots[20].m_nDimH;
  v21 = *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[20].m_nClipT2 = v19;
  this->m_Slots[20].m_nClipR = m_nDimH - v21;
  this->m_Slots[20].m_nClipR2 = m_nDimH - v21;
  v22 = m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[20].m_nClipB = v22;
  this->m_Slots[20].m_nClipB2 = v22;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "shushan.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[20].m_Widget
                                                                                    + 32))(
    this->m_Slots[20].m_Widget,
    281,
    &this->m_Slots[20],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[20].m_Widget)->SetUserData();
  this->m_Slots[20].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[20].m_Widget)(this->m_Slots[20].m_Widget, 0);
  this->m_Slots[20].m_Widget[377] = 0;
  v23 = *p_m_showGrayBk;
  this->m_Slots[22].m_nEdgeR = 653;
  this->m_Slots[22].m_nEdgeR2 = 653;
  this->m_Slots[22].m_nEdgeB = 327;
  this->m_Slots[22].m_nEdgeB2 = 327;
  this->m_Slots[22].m_nDimH = 151;
  v24 = 518 - v23;
// [VFTABLE] vftable = this->m_scrollbar.__vftable;
  this->m_Slots[22].m_nClipL = v24;
  this->m_Slots[22].m_nClipL2 = v24;
  this->m_Slots[22].m_nDimH2 = 151;
  v26 = 518 - (_DWORD)vftable;
  v27 = *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[22].m_nClipT = v26;
  this->m_Slots[22].m_nClipT2 = v26;
  this->m_Slots[22].m_nPosX = 135;
  this->m_Slots[22].m_nPosY = 176;
  this->m_Slots[22].m_nClipR = 151 - v27;
  this->m_Slots[22].m_nClipR2 = 151 - v27;
  Color = this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[22].m_fDimH = 151.0;
  this->m_Slots[22].m_nMarginX = 518;
  this->m_Slots[22].m_nMarginX2 = 518;
  this->m_Slots[22].m_fMarginX = 518.0;
  this->m_Slots[22].m_nClipB = 151 - Color;
  this->m_Slots[22].m_nClipB2 = 151 - Color;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "suoyaota.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[22].m_Widget
                                                                                    + 32))(
    this->m_Slots[22].m_Widget,
    289,
    &this->m_Slots[22],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[22].m_Widget)->SetUserData();
  this->m_Slots[22].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[22].m_Widget)(this->m_Slots[22].m_Widget, 0);
  this->m_Slots[22].m_Widget[377] = 0;
  this->m_Slots[25].m_nPosX = 141;
  this->m_Slots[25].m_nPosY = 144;
  this->m_Slots[25].m_nDimH = 46;
  this->m_Slots[25].m_nDimH2 = 46;
  this->m_Slots[25].m_fDimH = 46.0;
  this->m_Slots[25].m_nMarginX = 656;
  this->m_Slots[25].m_nMarginX2 = 656;
  this->m_Slots[25].m_fMarginX = 656.0;
  v29 = this->m_Slots[25].m_nMarginX;
  v30 = this->m_Slots[25].m_nPosX;
  this->m_Slots[25].m_nEdgeR = v29 + v30;
  this->m_Slots[25].m_nEdgeR2 = v29 + v30;
  v31 = this->m_Slots[25].m_nDimH + this->m_Slots[25].m_nPosY;
  this->m_Slots[25].m_nEdgeB = v31;
  this->m_Slots[25].m_nEdgeB2 = v31;
  v32 = this->m_Slots[25].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[25].m_nClipL = v32;
  this->m_Slots[25].m_nClipL2 = v32;
// [VFTABLE] v33 = this->m_Slots[25].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[25].m_nClipT = v33;
  this->m_Slots[25].m_nClipT2 = v33;
  v34 = this->m_Slots[25].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[25].m_nClipR = v34;
  this->m_Slots[25].m_nClipR2 = v34;
  v35 = this->m_Slots[25].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[25].m_nClipB = v35;
  this->m_Slots[25].m_nClipB2 = v35;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "xinxianjie.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[25].m_Widget
                                                                                    + 32))(
    this->m_Slots[25].m_Widget,
    292,
    &this->m_Slots[25],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[25].m_Widget)->SetUserData();
  this->m_Slots[25].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[25].m_Widget)(this->m_Slots[25].m_Widget, 0);
  this->m_Slots[25].m_Widget[377] = 0;
  this->m_Slots[7].m_nPosX = 120;
  this->m_Slots[7].m_nPosY = 110;
  this->m_Slots[7].m_nDimH = 0;
  this->m_Slots[7].m_nDimH2 = 0;
  this->m_Slots[7].m_fDimH = 0.0;
  this->m_Slots[7].m_nMarginX = 903;
  this->m_Slots[7].m_nMarginX2 = 903;
  this->m_Slots[7].m_fMarginX = 903.0;
  v36 = this->m_Slots[7].m_nPosX;
  v37 = this->m_Slots[7].m_nMarginX;
  this->m_Slots[7].m_nEdgeR = v36 + v37;
  this->m_Slots[7].m_nEdgeR2 = v36 + v37;
  v38 = this->m_Slots[7].m_nPosY + this->m_Slots[7].m_nDimH;
  this->m_Slots[7].m_nEdgeB = v38;
  this->m_Slots[7].m_nEdgeB2 = v38;
  v39 = this->m_Slots[7].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[7].m_nClipL = v39;
  this->m_Slots[7].m_nClipL2 = v39;
// [VFTABLE] v40 = this->m_Slots[7].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[7].m_nClipT = v40;
  this->m_Slots[7].m_nClipT2 = v40;
  v41 = this->m_Slots[7].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[7].m_nClipR = v41;
  this->m_Slots[7].m_nClipR2 = v41;
  v42 = this->m_Slots[7].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[7].m_nClipB = v42;
  this->m_Slots[7].m_nClipB2 = v42;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "rongyandiyu.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[7].m_Widget
                                                                                    + 32))(
    this->m_Slots[7].m_Widget,
    262,
    &this->m_Slots[7],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[7].m_Widget)->SetUserData();
  this->m_Slots[7].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[7].m_Widget)(this->m_Slots[7].m_Widget, 0);
  this->m_Slots[7].m_Widget[377] = 0;
  this->m_Slots[17].m_nPosX = 209;
  this->m_Slots[17].m_nPosY = 61;
  this->m_Slots[17].m_nDimH = 100;
  this->m_Slots[17].m_nDimH2 = 100;
  this->m_Slots[17].m_fDimH = 100.0;
  this->m_Slots[17].m_nMarginX = 1007;
  this->m_Slots[17].m_nMarginX2 = 1007;
  this->m_Slots[17].m_fMarginX = 1007.0;
  v43 = this->m_Slots[17].m_nPosX;
  v44 = this->m_Slots[17].m_nMarginX;
  this->m_Slots[17].m_nEdgeR = v43 + v44;
  this->m_Slots[17].m_nEdgeR2 = v43 + v44;
  v45 = this->m_Slots[17].m_nPosY + this->m_Slots[17].m_nDimH;
  this->m_Slots[17].m_nEdgeB = v45;
  this->m_Slots[17].m_nEdgeB2 = v45;
  v46 = this->m_Slots[17].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[17].m_nClipL = v46;
  this->m_Slots[17].m_nClipL2 = v46;
// [VFTABLE] v47 = this->m_Slots[17].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[17].m_nClipT = v47;
  this->m_Slots[17].m_nClipT2 = v47;
  v48 = this->m_Slots[17].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[17].m_nClipR = v48;
  this->m_Slots[17].m_nClipR2 = v48;
  v49 = this->m_Slots[17].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[17].m_nClipB = v49;
  this->m_Slots[17].m_nClipB2 = v49;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "huangquanlu.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[17].m_Widget
                                                                                    + 32))(
    this->m_Slots[17].m_Widget,
    278,
    &this->m_Slots[17],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[17].m_Widget)->SetUserData();
  this->m_Slots[17].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[17].m_Widget)(this->m_Slots[17].m_Widget, 0);
  this->m_Slots[17].m_Widget[377] = 0;
  this->m_Slots[5].m_nPosX = 112;
  this->m_Slots[5].m_nPosY = 107;
  this->m_Slots[5].m_nDimH = 18;
  this->m_Slots[5].m_nDimH2 = 18;
  this->m_Slots[5].m_fDimH = 18.0;
  this->m_Slots[5].m_nMarginX = 1089;
  this->m_Slots[5].m_nMarginX2 = 1089;
  this->m_Slots[5].m_fMarginX = 1089.0;
  v50 = this->m_Slots[5].m_nMarginX;
  v51 = this->m_Slots[5].m_nPosX;
  this->m_Slots[5].m_nEdgeR = v50 + v51;
  this->m_Slots[5].m_nEdgeR2 = v50 + v51;
  v52 = this->m_Slots[5].m_nDimH + this->m_Slots[5].m_nPosY;
  this->m_Slots[5].m_nEdgeB = v52;
  this->m_Slots[5].m_nEdgeB2 = v52;
  v53 = this->m_Slots[5].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[5].m_nClipL = v53;
  this->m_Slots[5].m_nClipL2 = v53;
// [VFTABLE] v54 = this->m_Slots[5].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[5].m_nClipT = v54;
  this->m_Slots[5].m_nClipT2 = v54;
  v55 = this->m_Slots[5].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[5].m_nClipR = v55;
  this->m_Slots[5].m_nClipR2 = v55;
  v56 = this->m_Slots[5].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[5].m_nClipB = v56;
  this->m_Slots[5].m_nClipB2 = v56;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "guijiewaiwei.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[5].m_Widget
                                                                                    + 32))(
    this->m_Slots[5].m_Widget,
    260,
    &this->m_Slots[5],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[5].m_Widget)->SetUserData();
  this->m_Slots[5].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[5].m_Widget)(this->m_Slots[5].m_Widget, 0);
  this->m_Slots[5].m_Widget[377] = 0;
  this->m_Slots[14].m_nPosX = 100;
  this->m_Slots[14].m_nPosY = 94;
  this->m_Slots[14].m_nDimH = 20;
  this->m_Slots[14].m_nDimH2 = 20;
  this->m_Slots[14].m_fDimH = 20.0;
  this->m_Slots[14].m_nMarginX = 1336;
  this->m_Slots[14].m_nMarginX2 = 1336;
  this->m_Slots[14].m_fMarginX = 1336.0;
  v57 = this->m_Slots[14].m_nMarginX;
  v58 = this->m_Slots[14].m_nPosX;
  this->m_Slots[14].m_nEdgeR = v57 + v58;
  this->m_Slots[14].m_nEdgeR2 = v57 + v58;
  v59 = this->m_Slots[14].m_nDimH + this->m_Slots[14].m_nPosY;
  this->m_Slots[14].m_nEdgeB = v59;
  this->m_Slots[14].m_nEdgeB2 = v59;
  v60 = this->m_Slots[14].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[14].m_nClipL = v60;
  this->m_Slots[14].m_nClipL2 = v60;
// [VFTABLE] v61 = this->m_Slots[14].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[14].m_nClipT = v61;
  this->m_Slots[14].m_nClipT2 = v61;
  v62 = this->m_Slots[14].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[14].m_nClipR = v62;
  this->m_Slots[14].m_nClipR2 = v62;
  v63 = this->m_Slots[14].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[14].m_nClipB = v63;
  this->m_Slots[14].m_nClipB2 = v63;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "penglai.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[14].m_Widget
                                                                                    + 32))(
    this->m_Slots[14].m_Widget,
    275,
    &this->m_Slots[14],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[14].m_Widget)->SetUserData();
  this->m_Slots[14].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[14].m_Widget)(this->m_Slots[14].m_Widget, 0);
  this->m_Slots[14].m_Widget[377] = 0;
  this->m_Slots[16].m_nPosX = 75;
  this->m_Slots[16].m_nPosY = 69;
  this->m_Slots[16].m_nDimH = 243;
  this->m_Slots[16].m_nDimH2 = 243;
  this->m_Slots[16].m_fDimH = 243.0;
  this->m_Slots[16].m_nMarginX = 170;
  this->m_Slots[16].m_nMarginX2 = 170;
  this->m_Slots[16].m_fMarginX = 170.0;
  v64 = this->m_Slots[16].m_nPosX;
  v65 = this->m_Slots[16].m_nMarginX;
  this->m_Slots[16].m_nEdgeR = v64 + v65;
  this->m_Slots[16].m_nEdgeR2 = v64 + v65;
  v66 = this->m_Slots[16].m_nPosY + this->m_Slots[16].m_nDimH;
  this->m_Slots[16].m_nEdgeB = v66;
  this->m_Slots[16].m_nEdgeB2 = v66;
  v67 = this->m_Slots[16].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[16].m_nClipL = v67;
  this->m_Slots[16].m_nClipL2 = v67;
// [VFTABLE] v68 = this->m_Slots[16].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[16].m_nClipT = v68;
  this->m_Slots[16].m_nClipT2 = v68;
  v69 = this->m_Slots[16].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[16].m_nClipR = v69;
  this->m_Slots[16].m_nClipR2 = v69;
  v70 = this->m_Slots[16].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[16].m_nClipB = v70;
  this->m_Slots[16].m_nClipB2 = v70;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "pilitang.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[16].m_Widget
                                                                                    + 32))(
    this->m_Slots[16].m_Widget,
    277,
    &this->m_Slots[16],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[16].m_Widget)->SetUserData();
  this->m_Slots[16].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[16].m_Widget)(this->m_Slots[16].m_Widget, 0);
  this->m_Slots[16].m_Widget[377] = 0;
  this->m_Slots[21].m_nPosX = 204;
  this->m_Slots[21].m_nPosY = 256;
  this->m_Slots[21].m_nDimH = 273;
  this->m_Slots[21].m_nDimH2 = 273;
  this->m_Slots[21].m_fDimH = 273.0;
  this->m_Slots[21].m_nMarginX = 304;
  this->m_Slots[21].m_nMarginX2 = 304;
  this->m_Slots[21].m_fMarginX = 304.0;
  v71 = this->m_Slots[21].m_nPosX;
  v72 = this->m_Slots[21].m_nMarginX;
  this->m_Slots[21].m_nEdgeR = v71 + v72;
  this->m_Slots[21].m_nEdgeR2 = v71 + v72;
  v73 = this->m_Slots[21].m_nPosY + this->m_Slots[21].m_nDimH;
  this->m_Slots[21].m_nEdgeB = v73;
  this->m_Slots[21].m_nEdgeB2 = v73;
  v74 = this->m_Slots[21].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[21].m_nClipL = v74;
  this->m_Slots[21].m_nClipL2 = v74;
// [VFTABLE] v75 = this->m_Slots[21].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[21].m_nClipT = v75;
  this->m_Slots[21].m_nClipT2 = v75;
  v76 = this->m_Slots[21].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[21].m_nClipR = v76;
  this->m_Slots[21].m_nClipR2 = v76;
  v77 = this->m_Slots[21].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[21].m_nClipB = v77;
  this->m_Slots[21].m_nClipB2 = v77;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "shushangudao.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[21].m_Widget
                                                                                    + 32))(
    this->m_Slots[21].m_Widget,
    288,
    &this->m_Slots[21],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[21].m_Widget)->SetUserData();
  this->m_Slots[21].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[21].m_Widget)(this->m_Slots[21].m_Widget, 0);
  this->m_Slots[21].m_Widget[377] = 0;
  this->m_Slots[26].m_nPosX = 41;
  this->m_Slots[26].m_nPosY = 35;
  this->m_Slots[26].m_nDimH = 409;
  this->m_Slots[26].m_nDimH2 = 409;
  this->m_Slots[26].m_fDimH = 409.0;
  this->m_Slots[26].m_nMarginX = 585;
  this->m_Slots[26].m_nMarginX2 = 585;
  this->m_Slots[26].m_fMarginX = 585.0;
  v78 = this->m_Slots[26].m_nMarginX;
  v79 = this->m_Slots[26].m_nPosX;
  this->m_Slots[26].m_nEdgeR = v78 + v79;
  this->m_Slots[26].m_nEdgeR2 = v78 + v79;
  v80 = this->m_Slots[26].m_nDimH + this->m_Slots[26].m_nPosY;
  this->m_Slots[26].m_nEdgeB = v80;
  this->m_Slots[26].m_nEdgeB2 = v80;
  v81 = this->m_Slots[26].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[26].m_nClipL = v81;
  this->m_Slots[26].m_nClipL2 = v81;
// [VFTABLE] v82 = this->m_Slots[26].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[26].m_nClipT = v82;
  this->m_Slots[26].m_nClipT2 = v82;
  v83 = this->m_Slots[26].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[26].m_nClipR = v83;
  this->m_Slots[26].m_nClipR2 = v83;
  v84 = this->m_Slots[26].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[26].m_nClipB = v84;
  this->m_Slots[26].m_nClipB2 = v84;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "xingsen.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[26].m_Widget
                                                                                    + 32))(
    this->m_Slots[26].m_Widget,
    293,
    &this->m_Slots[26],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[26].m_Widget)->SetUserData();
  this->m_Slots[26].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[26].m_Widget)(this->m_Slots[26].m_Widget, 0);
  this->m_Slots[26].m_Widget[377] = 0;
  this->m_Slots[28].m_nPosX = 188;
  this->m_Slots[28].m_nPosY = 120;
  this->m_Slots[28].m_nDimH = 298;
  this->m_Slots[28].m_nDimH2 = 298;
  this->m_Slots[28].m_fDimH = 298.0;
  this->m_Slots[28].m_nMarginX = 771;
  this->m_Slots[28].m_nMarginX2 = 771;
  this->m_Slots[28].m_fMarginX = 771.0;
  v85 = this->m_Slots[28].m_nMarginX;
  v86 = this->m_Slots[28].m_nPosX;
  this->m_Slots[28].m_nEdgeR = v85 + v86;
  this->m_Slots[28].m_nEdgeR2 = v85 + v86;
  v87 = this->m_Slots[28].m_nDimH + this->m_Slots[28].m_nPosY;
  this->m_Slots[28].m_nEdgeB = v87;
  this->m_Slots[28].m_nEdgeB2 = v87;
  v88 = this->m_Slots[28].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[28].m_nClipL = v88;
  this->m_Slots[28].m_nClipL2 = v88;
// [VFTABLE] v89 = this->m_Slots[28].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[28].m_nClipT = v89;
  this->m_Slots[28].m_nClipT2 = v89;
  v90 = this->m_Slots[28].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[28].m_nClipR = v90;
  this->m_Slots[28].m_nClipR2 = v90;
  v91 = this->m_Slots[28].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[28].m_nClipB = v91;
  this->m_Slots[28].m_nClipB2 = v91;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "yuzhou.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[28].m_Widget
                                                                                    + 32))(
    this->m_Slots[28].m_Widget,
    295,
    &this->m_Slots[28],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[28].m_Widget)->SetUserData();
  this->m_Slots[28].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[28].m_Widget)(this->m_Slots[28].m_Widget, 0);
  this->m_Slots[28].m_Widget[377] = 0;
  this->m_Slots[2].m_nPosX = 139;
  this->m_Slots[2].m_nPosY = 101;
  this->m_Slots[2].m_nDimH = 155;
  this->m_Slots[2].m_nDimH2 = 155;
  this->m_Slots[2].m_fDimH = 155.0;
  this->m_Slots[2].m_nMarginX = 1006;
  this->m_Slots[2].m_nMarginX2 = 1006;
  this->m_Slots[2].m_fMarginX = 1006.0;
  v92 = this->m_Slots[2].m_nPosX;
  v93 = this->m_Slots[2].m_nMarginX;
  this->m_Slots[2].m_nEdgeR = v92 + v93;
  this->m_Slots[2].m_nEdgeR2 = v92 + v93;
  v94 = this->m_Slots[2].m_nPosY + this->m_Slots[2].m_nDimH;
  this->m_Slots[2].m_nEdgeB = v94;
  this->m_Slots[2].m_nEdgeB2 = v94;
  v95 = this->m_Slots[2].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[2].m_nClipL = v95;
  this->m_Slots[2].m_nClipL2 = v95;
// [VFTABLE] v96 = this->m_Slots[2].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[2].m_nClipT = v96;
  this->m_Slots[2].m_nClipT2 = v96;
  v97 = this->m_Slots[2].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[2].m_nClipR = v97;
  this->m_Slots[2].m_nClipR2 = v97;
  v98 = this->m_Slots[2].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[2].m_nClipB = v98;
  this->m_Slots[2].m_nClipB2 = v98;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "fengdu.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[2].m_Widget
                                                                                    + 32))(
    this->m_Slots[2].m_Widget,
    257,
    &this->m_Slots[2],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[2].m_Widget)->SetUserData();
  this->m_Slots[2].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[2].m_Widget)(this->m_Slots[2].m_Widget, 0);
  this->m_Slots[2].m_Widget[377] = 0;
  this->m_Slots[29].m_nPosX = 138;
  this->m_Slots[29].m_nPosY = 113;
  this->m_Slots[29].m_nDimH = 200;
  this->m_Slots[29].m_nDimH2 = 200;
  this->m_Slots[29].m_fDimH = 200.0;
  this->m_Slots[29].m_nMarginX = 1248;
  this->m_Slots[29].m_nMarginX2 = 1248;
  this->m_Slots[29].m_fMarginX = 1248.0;
  v99 = this->m_Slots[29].m_nPosX;
  v100 = this->m_Slots[29].m_nMarginX;
  this->m_Slots[29].m_nEdgeR = v99 + v100;
  this->m_Slots[29].m_nEdgeR2 = v99 + v100;
  v101 = this->m_Slots[29].m_nPosY + this->m_Slots[29].m_nDimH;
  this->m_Slots[29].m_nEdgeB = v101;
  this->m_Slots[29].m_nEdgeB2 = v101;
  v102 = this->m_Slots[29].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[29].m_nClipL = v102;
  this->m_Slots[29].m_nClipL2 = v102;
// [VFTABLE] v103 = this->m_Slots[29].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[29].m_nClipT = v103;
  this->m_Slots[29].m_nClipT2 = v103;
  v104 = this->m_Slots[29].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[29].m_nClipR = v104;
  this->m_Slots[29].m_nClipR2 = v104;
  v105 = this->m_Slots[29].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[29].m_nClipB = v105;
  this->m_Slots[29].m_nClipB2 = v105;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "zhenjiang.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[29].m_Widget
                                                                                    + 32))(
    this->m_Slots[29].m_Widget,
    296,
    &this->m_Slots[29],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[29].m_Widget)->SetUserData();
  this->m_Slots[29].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[29].m_Widget)(this->m_Slots[29].m_Widget, 0);
  this->m_Slots[29].m_Widget[377] = 0;
  this->m_Slots[15].m_nPosX = 65;
  this->m_Slots[15].m_nPosY = 112;
  this->m_Slots[15].m_nDimH = 40;
  this->m_Slots[15].m_nDimH2 = 40;
  this->m_Slots[15].m_fDimH = 40.0;
  this->m_Slots[15].m_nMarginX = 1426;
  this->m_Slots[15].m_nMarginX2 = 1426;
  this->m_Slots[15].m_fMarginX = 1426.0;
  v106 = this->m_Slots[15].m_nMarginX;
  v107 = this->m_Slots[15].m_nPosX;
  this->m_Slots[15].m_nEdgeR = v106 + v107;
  this->m_Slots[15].m_nEdgeR2 = v106 + v107;
  v108 = this->m_Slots[15].m_nDimH + this->m_Slots[15].m_nPosY;
  this->m_Slots[15].m_nEdgeB = v108;
  this->m_Slots[15].m_nEdgeB2 = v108;
  v109 = this->m_Slots[15].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[15].m_nClipL = v109;
  this->m_Slots[15].m_nClipL2 = v109;
// [VFTABLE] v110 = this->m_Slots[15].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[15].m_nClipT = v110;
  this->m_Slots[15].m_nClipT2 = v110;
  v111 = this->m_Slots[15].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[15].m_nClipR = v111;
  this->m_Slots[15].m_nClipR2 = v111;
  v112 = this->m_Slots[15].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[15].m_nClipB = v112;
  this->m_Slots[15].m_nClipB2 = v112;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "penglaimigong.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[15].m_Widget
                                                                                    + 32))(
    this->m_Slots[15].m_Widget,
    276,
    &this->m_Slots[15],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[15].m_Widget)->SetUserData();
  this->m_Slots[15].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[15].m_Widget)(this->m_Slots[15].m_Widget, 0);
  this->m_Slots[15].m_Widget[377] = 0;
  this->m_Static_2440.m_bcreateok = 112;
  this->m_Static_2440.m_bvisible = 113;
  this->m_Static_2288.m_pbk2 = (gbTexture *)214;
// [VFTABLE] this->m_Static_2440.__vftable = (vtbl_0056AE2C *)214;
  this->m_Static_2440.m_rect.left = 1129709568;
  this->m_Static_2288.m_disablepicInfo = (_PlugInfo *)6;
  this->m_Static_2288.m_nTextW = 6;
  this->m_Static_2440.m_id = (void *)1086324736;
  m_disablepicInfo = this->m_Static_2288.m_disablepicInfo;
  m_bcreateok = this->m_Static_2440.m_bcreateok;
  *(_DWORD *)&this->m_Static_2288.m_mouseoff = (char *)m_disablepicInfo + m_bcreateok;
  this->m_Static_2440.m_fontcolor.Color = (unsigned int)m_disablepicInfo + m_bcreateok;
  v115 = (char *)this->m_Static_2288.m_pbk2 + this->m_Static_2440.m_bvisible;
  this->m_Static_2288.m_FVF = (int)v115;
  this->m_Static_2440.m_wndcolor.Color = (unsigned int)v115;
  v116 = (char *)this->m_Static_2288.m_disablepicInfo - *p_m_showGrayBk;
  this->m_Static_2440.m_rect.top = (LONG)v116;
  this->m_Static_2440.m_childs.m_pData = v116;
// [VFTABLE] v117 = (char *)this->m_Static_2288.m_disablepicInfo - (char *)this->m_scrollbar.__vftable;
  this->m_Static_2440.m_rect.right = v117;
  this->m_Static_2440.m_childs.capacity = v117;
  v118 = (char *)this->m_Static_2288.m_pbk2 - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Static_2440.m_rect.bottom = (LONG)v118;
  this->m_Static_2440.m_childs.m_nSize = (int)v118;
  v119 = (UIWnd *)((char *)this->m_Static_2288.m_pbk2 - this->m_scrollbar.m_fontcolor.Color);
  this->m_Static_2440.m_pfather = v119;
  this->m_Static_2440.m_childs.m_needscriptdel = (int)v119;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "bingfenggu.tga");
  (*(void ( **)(int *, int, _PlugInfo **, CCBUIPanel *, LONG *, _DWORD))(this->m_Static_2440.m_align
                                                                                            + 32))(
    &this->m_Static_2440.m_align,
    245,
    &this->m_Static_2288.m_disablepicInfo,
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)&this->m_Static_2440.m_align)->SetUserData();
  LOBYTE(this->m_Static_2744.m_FVF) = 1;
  (*(void ( **)(int *, _DWORD))this->m_Static_2440.m_align)(&this->m_Static_2440.m_align, 0);
  BYTE1(this->m_Static_2744.m_FVF) = 0;
  this->m_column[1].items.capacity = 116;
  this->m_column[1].items.m_nSize = 73;
  *(_DWORD *)this->m_column[1].head = 472;
  *(_DWORD *)&this->m_column[1].head[16] = 472;
  *(_DWORD *)&this->m_column[1].head[32] = 1139539968;
  this->m_column[0].width = 122;
  *(_DWORD *)&this->m_column[1].head[12] = 122;
  *(_DWORD *)&this->m_column[1].head[28] = 1123287040;
  capacity = this->m_column[1].items.capacity;
  width = this->m_column[0].width;
  *(_DWORD *)&this->m_column[1].head[4] = capacity + width;
  *(_DWORD *)&this->m_column[1].head[20] = capacity + width;
  v122 = this->m_column[1].items.m_nSize + *(_DWORD *)this->m_column[1].head;
  *(_DWORD *)&this->m_column[1].head[8] = v122;
  *(_DWORD *)&this->m_column[1].head[24] = v122;
  v123 = this->m_column[0].width - *p_m_showGrayBk;
  *(_DWORD *)&this->m_column[1].head[36] = v123;
  *(_DWORD *)&this->m_column[1].head[52] = v123;
// [VFTABLE] v124 = this->m_column[0].width - (unsigned int)this->m_scrollbar.__vftable;
  *(_DWORD *)&this->m_column[1].head[40] = v124;
  *(_DWORD *)&this->m_column[1].head[56] = v124;
  v125 = *(_DWORD *)this->m_column[1].head - *(_DWORD *)&this->m_hasKeyCtrl;
  *(_DWORD *)&this->m_column[1].head[44] = v125;
  *(_DWORD *)&this->m_column[1].head[60] = v125;
  v126 = (char *)(*(_DWORD *)this->m_column[1].head - this->m_scrollbar.m_fontcolor.Color);
  *(_DWORD *)&this->m_column[1].head[48] = v126;
  this->m_column[1].items.m_pData = v126;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "anningchun.tga");
  (*(void ( **)(char *, int, int *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)&this->m_column[2].head[4]
                                                                                      + 32))(
    &this->m_column[2].head[4],
    241,
    &this->m_column[0].width,
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)&this->m_column[2].head[4])->SetUserData();
  this->m_column[6].head[44] = 1;
  (**(void ( ***)(char *, _DWORD))&this->m_column[2].head[4])(&this->m_column[2].head[4], 0);
  this->m_column[6].head[45] = 0;
  this->m_Slots[23].m_nPosX = 124;
  this->m_Slots[23].m_nPosY = 96;
  this->m_Slots[23].m_nDimH = 504;
  this->m_Slots[23].m_nDimH2 = 504;
  this->m_Slots[23].m_fDimH = 504.0;
  this->m_Slots[23].m_nMarginX = 588;
  this->m_Slots[23].m_nMarginX2 = 588;
  this->m_Slots[23].m_fMarginX = 588.0;
  v127 = this->m_Slots[23].m_nPosX;
  v128 = this->m_Slots[23].m_nMarginX;
  this->m_Slots[23].m_nEdgeR = v127 + v128;
  this->m_Slots[23].m_nEdgeR2 = v127 + v128;
  v129 = this->m_Slots[23].m_nPosY + this->m_Slots[23].m_nDimH;
  this->m_Slots[23].m_nEdgeB = v129;
  this->m_Slots[23].m_nEdgeB2 = v129;
  v130 = this->m_Slots[23].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[23].m_nClipL = v130;
  this->m_Slots[23].m_nClipL2 = v130;
// [VFTABLE] v131 = this->m_Slots[23].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[23].m_nClipT = v131;
  this->m_Slots[23].m_nClipT2 = v131;
  v132 = this->m_Slots[23].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[23].m_nClipR = v132;
  this->m_Slots[23].m_nClipR2 = v132;
  v133 = this->m_Slots[23].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[23].m_nClipB = v133;
  this->m_Slots[23].m_nClipB2 = v133;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "tangjiabao.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[23].m_Widget
                                                                                    + 32))(
    this->m_Slots[23].m_Widget,
    290,
    &this->m_Slots[23],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[23].m_Widget)->SetUserData();
  this->m_Slots[23].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[23].m_Widget)(this->m_Slots[23].m_Widget, 0);
  this->m_Slots[23].m_Widget[377] = 0;
  this->m_nItemNum = 174;
  this->m_nMaxItemNum = 126;
  this->m_nPanelY = 569;
  this->m_nChildH = 569;
  this->m_fPanelH = 569.0;
  this->m_nPanelX = 852;
  this->m_nChildW = 852;
  this->m_fPanelW = 852.0;
  m_nPanelX = this->m_nPanelX;
  m_nItemNum = this->m_nItemNum;
  this->m_nChildX = m_nPanelX + m_nItemNum;
  this->m_nBorderL = m_nPanelX + m_nItemNum;
  v136 = this->m_nPanelY + this->m_nMaxItemNum;
  this->m_nChildY = v136;
  this->m_nBorderR = v136;
  v137 = this->m_nPanelX - *p_m_showGrayBk;
  this->m_nGridX = v137;
  this->m_nItemW = v137;
// [VFTABLE] v138 = this->m_nPanelX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_nGridY = v138;
  this->m_nItemH = v138;
  v139 = this->m_nPanelY - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_nGridW = v139;
  this->m_nSpacingX = v139;
  v140 = this->m_nPanelY - this->m_scrollbar.m_fontcolor.Color;
  this->m_nGridH = v140;
  this->m_nSpacingY = v140;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "binhua.tga");
  ((void ( *)(void **, int, int *, CCBUIPanel *, LONG *, _DWORD))this->m_pVfTable[1].RenderIfUnlocked)(
    &this->m_pVfTable,
    243,
    &this->m_nPanelX,
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)&this->m_pVfTable)->SetUserData();
  LOBYTE(this->m_Scene_1792.m_nNotifyRender) = 1;
  ((void ( *)(void **, _DWORD))this->m_pVfTable->ShowWindow)(&this->m_pVfTable, 0);
  BYTE1(this->m_Scene_1792.m_nNotifyRender) = 0;
  this->m_Slots[8].m_nPosX = 90;
  this->m_Slots[8].m_nPosY = 140;
  this->m_Slots[8].m_nDimH = 329;
  this->m_Slots[8].m_nDimH2 = 329;
  this->m_Slots[8].m_fDimH = 329.0;
  this->m_Slots[8].m_nMarginX = 1121;
  this->m_Slots[8].m_nMarginX2 = 1121;
  this->m_Slots[8].m_fMarginX = 1121.0;
  v141 = this->m_Slots[8].m_nMarginX;
  v142 = this->m_Slots[8].m_nPosX;
  this->m_Slots[8].m_nEdgeR = v141 + v142;
  this->m_Slots[8].m_nEdgeR2 = v141 + v142;
  v143 = this->m_Slots[8].m_nDimH + this->m_Slots[8].m_nPosY;
  this->m_Slots[8].m_nEdgeB = v143;
  this->m_Slots[8].m_nEdgeB2 = v143;
  v144 = this->m_Slots[8].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[8].m_nClipL = v144;
  this->m_Slots[8].m_nClipL2 = v144;
// [VFTABLE] v145 = this->m_Slots[8].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[8].m_nClipT = v145;
  this->m_Slots[8].m_nClipT2 = v145;
  v146 = this->m_Slots[8].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[8].m_nClipR = v146;
  this->m_Slots[8].m_nClipR2 = v146;
  v147 = this->m_Slots[8].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[8].m_nClipB = v147;
  this->m_Slots[8].m_nClipB2 = v147;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "jianzhong.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[8].m_Widget
                                                                                    + 32))(
    this->m_Slots[8].m_Widget,
    263,
    &this->m_Slots[8],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[8].m_Widget)->SetUserData();
  this->m_Slots[8].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[8].m_Widget)(this->m_Slots[8].m_Widget, 0);
  this->m_Slots[8].m_Widget[377] = 0;
  *(_DWORD *)&this->m_column[7].head[40] = 128;
  *(_DWORD *)&this->m_column[7].head[44] = 113;
  *(_DWORD *)&this->m_column[6].head[56] = 566;
  this->m_column[6].items.m_nSize = 566;
  *(_DWORD *)&this->m_column[7].head[4] = 1141735424;
  *(_DWORD *)&this->m_column[6].head[52] = 1230;
  this->m_column[6].items.capacity = 1230;
  *(_DWORD *)this->m_column[7].head = 1150926848;
  v148 = *(_DWORD *)&this->m_column[7].head[40];
  v149 = *(_DWORD *)&this->m_column[6].head[52];
  *(_DWORD *)&this->m_column[6].head[60] = v148 + v149;
  this->m_column[6].items.m_needscriptdel = v148 + v149;
  v150 = (char *)(*(_DWORD *)&this->m_column[7].head[44] + *(_DWORD *)&this->m_column[6].head[56]);
  this->m_column[6].items.m_pData = v150;
  this->m_column[6].width = (int)v150;
  v151 = *(_DWORD *)&this->m_column[6].head[52] - *p_m_showGrayBk;
  *(_DWORD *)&this->m_column[7].head[8] = v151;
  *(_DWORD *)&this->m_column[7].head[24] = v151;
// [VFTABLE] v152 = *(_DWORD *)&this->m_column[6].head[52] - (unsigned int)this->m_scrollbar.__vftable;
  *(_DWORD *)&this->m_column[7].head[12] = v152;
  *(_DWORD *)&this->m_column[7].head[28] = v152;
  v153 = *(_DWORD *)&this->m_column[6].head[56] - *(_DWORD *)&this->m_hasKeyCtrl;
  *(_DWORD *)&this->m_column[7].head[16] = v153;
  *(_DWORD *)&this->m_column[7].head[32] = v153;
  v154 = *(_DWORD *)&this->m_column[6].head[56] - this->m_scrollbar.m_fontcolor.Color;
  *(_DWORD *)&this->m_column[7].head[20] = v154;
  *(_DWORD *)&this->m_column[7].head[36] = v154;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "anxi.tga");
  (*(void ( **)(char *, int, char *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)&this->m_column[7].head[60] + 32))(
    &this->m_column[7].head[60],
    242,
    &this->m_column[6].head[52],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)&this->m_column[7].head[60])->SetUserData();
  LOBYTE(this->_todo_5B4) = 1;
  (**(void ( ***)(char *, _DWORD))&this->m_column[7].head[60])(&this->m_column[7].head[60], 0);
  BYTE1(this->_todo_5B4) = 0;
  this->m_Slots[6].m_nPosX = 85;
  this->m_Slots[6].m_nPosY = 155;
  this->m_Slots[6].m_nDimH = 625;
  this->m_Slots[6].m_nDimH2 = 625;
  this->m_Slots[6].m_fDimH = 625.0;
  this->m_Slots[6].m_nMarginX = 1386;
  this->m_Slots[6].m_nMarginX2 = 1386;
  this->m_Slots[6].m_fMarginX = 1386.0;
  v155 = this->m_Slots[6].m_nPosX;
  v156 = this->m_Slots[6].m_nMarginX;
  this->m_Slots[6].m_nEdgeR = v155 + v156;
  this->m_Slots[6].m_nEdgeR2 = v155 + v156;
  v157 = this->m_Slots[6].m_nPosY + this->m_Slots[6].m_nDimH;
  this->m_Slots[6].m_nEdgeB = v157;
  this->m_Slots[6].m_nEdgeB2 = v157;
  v158 = this->m_Slots[6].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[6].m_nClipL = v158;
  this->m_Slots[6].m_nClipL2 = v158;
// [VFTABLE] v159 = this->m_Slots[6].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[6].m_nClipT = v159;
  this->m_Slots[6].m_nClipT2 = v159;
  v160 = this->m_Slots[6].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[6].m_nClipR = v160;
  this->m_Slots[6].m_nClipR2 = v160;
  v161 = this->m_Slots[6].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[6].m_nClipB = v161;
  this->m_Slots[6].m_nClipB2 = v161;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "haidicheng.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[6].m_Widget
                                                                                    + 32))(
    this->m_Slots[6].m_Widget,
    261,
    &this->m_Slots[6],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[6].m_Widget)->SetUserData();
  this->m_Slots[6].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[6].m_Widget)(this->m_Slots[6].m_Widget, 0);
  this->m_Slots[6].m_Widget[377] = 0;
  this->m_Slots[11].m_nPosX = 155;
  this->m_Slots[11].m_nPosY = 139;
  this->m_Slots[11].m_nDimH = 784;
  this->m_Slots[11].m_nDimH2 = 784;
  this->m_Slots[11].m_fDimH = 784.0;
  this->m_Slots[11].m_nMarginX = 907;
  this->m_Slots[11].m_nMarginX2 = 907;
  this->m_Slots[11].m_fMarginX = 907.0;
  v162 = this->m_Slots[11].m_nMarginX;
  v163 = this->m_Slots[11].m_nPosX;
  this->m_Slots[11].m_nEdgeR = v162 + v163;
  this->m_Slots[11].m_nEdgeR2 = v162 + v163;
  v164 = this->m_Slots[11].m_nDimH + this->m_Slots[11].m_nPosY;
  this->m_Slots[11].m_nEdgeB = v164;
  this->m_Slots[11].m_nEdgeB2 = v164;
  v165 = this->m_Slots[11].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[11].m_nClipL = v165;
  this->m_Slots[11].m_nClipL2 = v165;
// [VFTABLE] v166 = this->m_Slots[11].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[11].m_nClipT = v166;
  this->m_Slots[11].m_nClipT2 = v166;
  v167 = this->m_Slots[11].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[11].m_nClipR = v167;
  this->m_Slots[11].m_nClipR2 = v167;
  v168 = this->m_Slots[11].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[11].m_nClipB = v168;
  this->m_Slots[11].m_nClipB2 = v168;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "leizhou.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[11].m_Widget
                                                                                    + 32))(
    this->m_Slots[11].m_Widget,
    272,
    &this->m_Slots[11],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[11].m_Widget)->SetUserData();
  this->m_Slots[11].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[11].m_Widget)(this->m_Slots[11].m_Widget, 0);
  this->m_Slots[11].m_Widget[377] = 0;
  this->m_Slots[19].m_nPosX = 100;
  this->m_Slots[19].m_nPosY = 96;
  this->m_Slots[19].m_nDimH = 918;
  this->m_Slots[19].m_nDimH2 = 918;
  this->m_Slots[19].m_fDimH = 918.0;
  this->m_Slots[19].m_nMarginX = 748;
  this->m_Slots[19].m_nMarginX2 = 748;
  this->m_Slots[19].m_fMarginX = 748.0;
  v169 = this->m_Slots[19].m_nMarginX;
  v170 = this->m_Slots[19].m_nPosX;
  this->m_Slots[19].m_nEdgeR = v169 + v170;
  this->m_Slots[19].m_nEdgeR2 = v169 + v170;
  v171 = this->m_Slots[19].m_nDimH + this->m_Slots[19].m_nPosY;
  this->m_Slots[19].m_nEdgeB = v171;
  this->m_Slots[19].m_nEdgeB2 = v171;
  v172 = this->m_Slots[19].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[19].m_nClipL = v172;
  this->m_Slots[19].m_nClipL2 = v172;
// [VFTABLE] v173 = this->m_Slots[19].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[19].m_nClipT = v173;
  this->m_Slots[19].m_nClipT2 = v173;
  v174 = this->m_Slots[19].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[19].m_nClipR = v174;
  this->m_Slots[19].m_nClipR2 = v174;
  v175 = this->m_Slots[19].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[19].m_nClipB = v175;
  this->m_Slots[19].m_nClipB2 = v175;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "shenshu.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[19].m_Widget
                                                                                    + 32))(
    this->m_Slots[19].m_Widget,
    280,
    &this->m_Slots[19],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[19].m_Widget)->SetUserData();
  this->m_Slots[19].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[19].m_Widget)(this->m_Slots[19].m_Widget, 0);
  this->m_Slots[19].m_Widget[377] = 0;
  this->m_Slots[18].m_nPosX = 232;
  this->m_Slots[18].m_nPosY = 166;
  this->m_Slots[18].m_nDimH = 858;
  this->m_Slots[18].m_nDimH2 = 858;
  this->m_Slots[18].m_fDimH = 858.0;
  this->m_Slots[18].m_nMarginX = 438;
  this->m_Slots[18].m_nMarginX2 = 438;
  this->m_Slots[18].m_fMarginX = 438.0;
  v176 = this->m_Slots[18].m_nPosX;
  v177 = this->m_Slots[18].m_nMarginX;
  this->m_Slots[18].m_nEdgeR = v176 + v177;
  this->m_Slots[18].m_nEdgeR2 = v176 + v177;
  v178 = this->m_Slots[18].m_nPosY + this->m_Slots[18].m_nDimH;
  this->m_Slots[18].m_nEdgeB = v178;
  this->m_Slots[18].m_nEdgeB2 = v178;
  v179 = this->m_Slots[18].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[18].m_nClipL = v179;
  this->m_Slots[18].m_nClipL2 = v179;
// [VFTABLE] v180 = this->m_Slots[18].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[18].m_nClipT = v180;
  this->m_Slots[18].m_nClipT2 = v180;
  v181 = this->m_Slots[18].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[18].m_nClipR = v181;
  this->m_Slots[18].m_nClipR2 = v181;
  v182 = this->m_Slots[18].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[18].m_nClipB = v182;
  this->m_Slots[18].m_nClipB2 = v182;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "shenjietianmen.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[18].m_Widget
                                                                                    + 32))(
    this->m_Slots[18].m_Widget,
    279,
    &this->m_Slots[18],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[18].m_Widget)->SetUserData();
  this->m_Slots[18].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[18].m_Widget)(this->m_Slots[18].m_Widget, 0);
  this->m_Slots[18].m_Widget[377] = 0;
  this->m_Slots[12].m_nPosX = 174;
  this->m_Slots[12].m_nPosY = 132;
  this->m_Slots[12].m_nDimH = 778;
  this->m_Slots[12].m_nDimH2 = 778;
  this->m_Slots[12].m_fDimH = 778.0;
  this->m_Slots[12].m_nMarginX = 311;
  this->m_Slots[12].m_nMarginX2 = 311;
  this->m_Slots[12].m_fMarginX = 311.0;
  v183 = this->m_Slots[12].m_nPosX;
  v184 = this->m_Slots[12].m_nMarginX;
  this->m_Slots[12].m_nEdgeR = v183 + v184;
  this->m_Slots[12].m_nEdgeR2 = v183 + v184;
  v185 = this->m_Slots[12].m_nPosY + this->m_Slots[12].m_nDimH;
  this->m_Slots[12].m_nEdgeB = v185;
  this->m_Slots[12].m_nEdgeB2 = v185;
  v186 = this->m_Slots[12].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[12].m_nClipL = v186;
  this->m_Slots[12].m_nClipL2 = v186;
// [VFTABLE] v187 = this->m_Slots[12].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[12].m_nClipT = v187;
  this->m_Slots[12].m_nClipT2 = v187;
  v188 = this->m_Slots[12].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[12].m_nClipR = v188;
  this->m_Slots[12].m_nClipR2 = v188;
  v189 = this->m_Slots[12].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[12].m_nClipB = v189;
  this->m_Slots[12].m_nClipB2 = v189;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "manzhou.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[12].m_Widget
                                                                                    + 32))(
    this->m_Slots[12].m_Widget,
    273,
    &this->m_Slots[12],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[12].m_Widget)->SetUserData();
  this->m_Slots[12].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[12].m_Widget)(this->m_Slots[12].m_Widget, 0);
  this->m_Slots[12].m_Widget[377] = 0;
  this->m_Slots[13].m_nPosX = 141;
  this->m_Slots[13].m_nPosY = 145;
  this->m_Slots[13].m_nDimH = 880;
  this->m_Slots[13].m_nDimH2 = 880;
  this->m_Slots[13].m_fDimH = 880.0;
  this->m_Slots[13].m_nMarginX = 226;
  this->m_Slots[13].m_nMarginX2 = 226;
  this->m_Slots[13].m_fMarginX = 226.0;
  v190 = this->m_Slots[13].m_nMarginX;
  v191 = this->m_Slots[13].m_nPosX;
  this->m_Slots[13].m_nEdgeR = v190 + v191;
  this->m_Slots[13].m_nEdgeR2 = v190 + v191;
  v192 = this->m_Slots[13].m_nDimH + this->m_Slots[13].m_nPosY;
  this->m_Slots[13].m_nEdgeB = v192;
  this->m_Slots[13].m_nEdgeB2 = v192;
  v193 = this->m_Slots[13].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[13].m_nClipL = v193;
  this->m_Slots[13].m_nClipL2 = v193;
// [VFTABLE] v194 = this->m_Slots[13].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[13].m_nClipT = v194;
  this->m_Slots[13].m_nClipT2 = v194;
  v195 = this->m_Slots[13].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[13].m_nClipR = v195;
  this->m_Slots[13].m_nClipR2 = v195;
  v196 = this->m_Slots[13].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[13].m_nClipB = v196;
  this->m_Slots[13].m_nClipB2 = v196;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "mohuankongjian.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[13].m_Widget
                                                                                    + 32))(
    this->m_Slots[13].m_Widget,
    274,
    &this->m_Slots[13],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[13].m_Widget)->SetUserData();
  this->m_Slots[13].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[13].m_Widget)(this->m_Slots[13].m_Widget, 0);
  this->m_Slots[13].m_Widget[377] = 0;
  this->m_Slots[24].m_nPosX = 161;
  this->m_Slots[24].m_nPosY = 92;
  this->m_Slots[24].m_nDimH = 716;
  this->m_Slots[24].m_nDimH2 = 716;
  this->m_Slots[24].m_fDimH = 716.0;
  this->m_Slots[24].m_nMarginX = 164;
  this->m_Slots[24].m_nMarginX2 = 164;
  this->m_Slots[24].m_fMarginX = 164.0;
  v197 = this->m_Slots[24].m_nMarginX;
  v198 = this->m_Slots[24].m_nPosX;
  this->m_Slots[24].m_nEdgeR = v197 + v198;
  this->m_Slots[24].m_nEdgeR2 = v197 + v198;
  v199 = this->m_Slots[24].m_nDimH + this->m_Slots[24].m_nPosY;
  this->m_Slots[24].m_nEdgeB = v199;
  this->m_Slots[24].m_nEdgeB2 = v199;
  v200 = this->m_Slots[24].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[24].m_nClipL = v200;
  this->m_Slots[24].m_nClipL2 = v200;
// [VFTABLE] v201 = this->m_Slots[24].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[24].m_nClipT = v201;
  this->m_Slots[24].m_nClipT2 = v201;
  v202 = this->m_Slots[24].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[24].m_nClipR = v202;
  this->m_Slots[24].m_nClipR2 = v202;
  v203 = this->m_Slots[24].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[24].m_nClipB = v203;
  this->m_Slots[24].m_nClipB2 = v203;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "xianrendong.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[24].m_Widget
                                                                                    + 32))(
    this->m_Slots[24].m_Widget,
    291,
    &this->m_Slots[24],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[24].m_Widget)->SetUserData();
  this->m_Slots[24].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[24].m_Widget)(this->m_Slots[24].m_Widget, 0);
  this->m_Slots[24].m_Widget[377] = 0;
  this->m_Slots[3].m_nPosX = 134;
  this->m_Slots[3].m_nPosY = 108;
  this->m_Slots[3].m_nDimH = 832;
  this->m_Slots[3].m_nDimH2 = 832;
  this->m_Slots[3].m_fDimH = 832.0;
  this->m_Slots[3].m_nMarginX = 81;
  this->m_Slots[3].m_nMarginX2 = 81;
  this->m_Slots[3].m_fMarginX = 81.0;
  v204 = this->m_Slots[3].m_nPosX;
  v205 = this->m_Slots[3].m_nMarginX;
  this->m_Slots[3].m_nEdgeR = v204 + v205;
  this->m_Slots[3].m_nEdgeR2 = v204 + v205;
  v206 = this->m_Slots[3].m_nPosY + this->m_Slots[3].m_nDimH;
  this->m_Slots[3].m_nEdgeB = v206;
  this->m_Slots[3].m_nEdgeB2 = v206;
  v207 = this->m_Slots[3].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[3].m_nClipL = v207;
  this->m_Slots[3].m_nClipL2 = v207;
// [VFTABLE] v208 = this->m_Slots[3].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[3].m_nClipT = v208;
  this->m_Slots[3].m_nClipT2 = v208;
  v209 = this->m_Slots[3].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[3].m_nClipR = v209;
  this->m_Slots[3].m_nClipR2 = v209;
  v210 = this->m_Slots[3].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[3].m_nClipB = v210;
  this->m_Slots[3].m_nClipB2 = v210;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "guchengzhen.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[3].m_Widget
                                                                                    + 32))(
    this->m_Slots[3].m_Widget,
    258,
    &this->m_Slots[3],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[3].m_Widget)->SetUserData();
  this->m_Slots[3].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[3].m_Widget)(this->m_Slots[3].m_Widget, 0);
  this->m_Slots[3].m_Widget[377] = 0;
  *(&this->m_Scene_1792.m_hTexture + 4) = 142;
  *(&this->m_Scene_1792.m_hTexture + 5) = 106;
  this->m_Scene_1792.m_nColors = 419;
  LODWORD(this->m_Scene_1792.m_fCameraOffset) = 419;
  this->m_Scene_1792.m_hFont = 1137803264;
  this->m_Scene_1792.m_hScrollBar = 671;
  LODWORD(this->m_Scene_1792.m_fAngle) = 671;
  this->m_Scene_1792.m_bVisible = (Parent_Data *)1143455744;
  v211 = *(&this->m_Scene_1792.m_hTexture + 4);
  m_hScrollBar = this->m_Scene_1792.m_hScrollBar;
  this->m_Scene_1792.m_bLoadState = v211 + m_hScrollBar;
  this->m_Scene_1792.m_bFieldCC = (Parent_Data *)(v211 + m_hScrollBar);
  v213 = (char *)(*(&this->m_Scene_1792.m_hTexture + 5) + this->m_Scene_1792.m_nColors);
  this->m_Scene_1792.m_pChildData = v213;
  this->m_Scene_1792.m_nFieldD0 = (int)v213;
  v214 = (Parent_Data *)(this->m_Scene_1792.m_hScrollBar - *p_m_showGrayBk);
  this->m_Scene_1792.m_bEnabled = v214;
  this->m_Scene_1792.m_hTexture = (int)v214;
// [VFTABLE] v215 = (gbTexture *)(this->m_Scene_1792.m_hScrollBar - (unsigned int)this->m_scrollbar.__vftable);
  this->m_Scene_1792.m_pTexture = v215;
  *(&this->m_Scene_1792.m_hTexture + 1) = (int)v215;
  v216 = this->m_Scene_1792.m_nColors - *(_DWORD *)&this->m_hasKeyCtrl;
  *(_DWORD *)&this->m_Scene_1792.m_bOverlayRender = v216;
  *(&this->m_Scene_1792.m_hTexture + 2) = v216;
  v217 = this->m_Scene_1792.m_nColors - this->m_scrollbar.m_fontcolor.Color;
  *(_DWORD *)&this->m_Scene_1792.m_bCursorLeft = v217;
  *(&this->m_Scene_1792.m_hTexture + 3) = v217;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "bishan.tga");
  (*(void ( **)(int *, int, int *, CCBUIPanel *, LONG *, _DWORD))(*(&this->m_Scene_1792.m_hTexture
                                                                                                  + 9)
                                                                                                + 32))(
    &this->m_Scene_1792.m_hTexture + 9,
    244,
    &this->m_Scene_1792.m_hScrollBar,
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)(&this->m_Scene_1792.m_hTexture + 9))->SetUserData();
  LOBYTE(this->m_Static_2288.m_ppicInfo) = 1;
  (**((void ( ***)(int *, _DWORD))&this->m_Scene_1792.m_hTexture + 9))(
    &this->m_Scene_1792.m_hTexture + 9,
    0);
  BYTE1(this->m_Static_2288.m_ppicInfo) = 0;
  LODWORD(this->m_Scene_2896.m_fScaleY) = 110;
  LODWORD(this->m_Scene_2896.m_fScaleX) = 103;
  this->m_Scene_2896.m_fontcolor.Color = 675;
  this->m_Scene_2896.m_rect.top = 675;
  this->m_Scene_2896.m_childs.m_pData = (char *)1143521280;
// [VFTABLE] this->m_Scene_2896.__vftable = (vtbl_0056AE2C *)440;
  this->m_Scene_2896.m_rect.left = 440;
  this->m_Scene_2896.m_pfather = (UIWnd *)1138491392;
// [VFTABLE] v218 = this->m_Scene_2896.__vftable;
  m_fScaleY = this->m_Scene_2896.m_fScaleY;
  this->m_Scene_2896.m_wndcolor.Color = (unsigned int)v218 + LODWORD(m_fScaleY);
  this->m_Scene_2896.m_rect.right = (LONG)v218 + LODWORD(m_fScaleY);
  v220 = (void *)(this->m_Scene_2896.m_fontcolor.Color + LODWORD(this->m_Scene_2896.m_fScaleX));
  this->m_Scene_2896.m_id = v220;
  this->m_Scene_2896.m_rect.bottom = (LONG)v220;
// [VFTABLE] v221 = (char *)this->m_Scene_2896.__vftable - *p_m_showGrayBk;
  this->m_Scene_2896.m_childs.capacity = (int)v221;
  this->m_Scene_2896.m_bvisible = (int)v221;
// [VFTABLE] v222 = (char *)this->m_Scene_2896.__vftable - (char *)this->m_scrollbar.__vftable;
  this->m_Scene_2896.m_childs.m_nSize = v222;
  this->m_Scene_2896.m_benable = v222;
  v223 = this->m_Scene_2896.m_fontcolor.Color - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Scene_2896.m_childs.m_needscriptdel = v223;
  this->m_Scene_2896.m_bfocus = v223;
  v224 = this->m_Scene_2896.m_fontcolor.Color - this->m_scrollbar.m_fontcolor.Color;
  this->m_Scene_2896.m_bcreateok = v224;
  this->m_Scene_2896.m_nViewW = v224;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "chaohai.tga");
  (*(void ( **)(int *, int, UIScene *, CCBUIPanel *, LONG *, _DWORD))(this->m_Scene_2896.m_nShowState
                                                                                         + 32))(
    &this->m_Scene_2896.m_nShowState,
    246,
    &this->m_Scene_2896,
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)&this->m_Scene_2896.m_nShowState)->SetUserData();
  LOBYTE(this->m_Scene_3240.m_nRectW) = 1;
  (*(void ( **)(int *, _DWORD))this->m_Scene_2896.m_nShowState)(
    &this->m_Scene_2896.m_nShowState,
    0);
  BYTE1(this->m_Scene_3240.m_nRectW) = 0;
  *(_DWORD *)&this->m_Scene_3240.m_bCursorLeft = 97;
  this->m_Scene_3240.m_hTexture = 85;
  this->m_Scene_3240.m_nPosY = 195;
  this->m_Scene_3240.m_hScrollBar = 195;
  this->m_Scene_3240.m_fAngle = 195.0;
  this->m_Scene_3240.m_nPosX = 1113;
  this->m_Scene_3240.m_dwColor = 1113;
  this->m_Scene_3240.m_pChildData = (char *)1149968384;
  v225 = this->m_Scene_3240.m_nPosX;
  v226 = *(_DWORD *)&this->m_Scene_3240.m_bCursorLeft;
  this->m_Scene_3240.m_nLoadResource = v225 + v226;
  this->m_Scene_3240.m_nColors = v225 + v226;
  v227 = this->m_Scene_3240.m_nPosY + this->m_Scene_3240.m_hTexture;
  this->m_Scene_3240.m_nNotifyRender = v227;
  this->m_Scene_3240.m_bLoadState = v227;
  LODWORD(v228) = this->m_Scene_3240.m_nPosX - *p_m_showGrayBk;
  this->m_Scene_3240.m_fCameraOffset = v228;
  *(float *)&this->m_Scene_3240.m_hFont = v228;
// [VFTABLE] v229 = (Parent_Data *)(this->m_Scene_3240.m_nPosX - (unsigned int)this->m_scrollbar.__vftable);
  this->m_Scene_3240.m_bFieldCC = v229;
  this->m_Scene_3240.m_bEnabled = v229;
  v230 = (gbTexture *)(this->m_Scene_3240.m_nPosY - *(_DWORD *)&this->m_hasKeyCtrl);
  this->m_Scene_3240.m_nFieldD0 = (int)v230;
  this->m_Scene_3240.m_pTexture = v230;
  v231 = (Parent_Data *)(this->m_Scene_3240.m_nPosY - this->m_scrollbar.m_fontcolor.Color);
  this->m_Scene_3240.m_bVisible = v231;
  *(_DWORD *)&this->m_Scene_3240.m_bOverlayRender = v231;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "chuanchangjiang.tga");
  (*(void ( **)(int *, int, int *, CCBUIPanel *, LONG *, _DWORD))(*(&this->m_Scene_3240.m_hTexture
                                                                                                  + 4)
                                                                                                + 32))(
    &this->m_Scene_3240.m_hTexture + 4,
    247,
    &this->m_Scene_3240.m_nPosX,
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)(&this->m_Scene_3240.m_hTexture + 4))->SetUserData();
  *((_BYTE *)&this->m_Scene_3584.m_hTexture + 48) = 1;
  (**((void ( ***)(int *, _DWORD))&this->m_Scene_3240.m_hTexture + 4))(
    &this->m_Scene_3240.m_hTexture + 4,
    0);
  *((_BYTE *)&this->m_Scene_3584.m_hTexture + 49) = 0;
  *(&this->m_Scene_3584.m_hTexture + 32) = 113;
  *(&this->m_Scene_3584.m_hTexture + 33) = 83;
  *(&this->m_Scene_3584.m_hTexture + 15) = 138;
  *(&this->m_Scene_3584.m_hTexture + 19) = 138;
  *(&this->m_Scene_3584.m_hTexture + 23) = 1124728832;
  *(&this->m_Scene_3584.m_hTexture + 14) = 1405;
  *(&this->m_Scene_3584.m_hTexture + 18) = 1405;
  *(&this->m_Scene_3584.m_hTexture + 22) = 1152360448;
  v232 = *(&this->m_Scene_3584.m_hTexture + 32);
  v233 = *(&this->m_Scene_3584.m_hTexture + 14);
  *(&this->m_Scene_3584.m_hTexture + 16) = v232 + v233;
  *(&this->m_Scene_3584.m_hTexture + 20) = v232 + v233;
  v234 = *(&this->m_Scene_3584.m_hTexture + 33) + *(&this->m_Scene_3584.m_hTexture + 15);
  *(&this->m_Scene_3584.m_hTexture + 17) = v234;
  *(&this->m_Scene_3584.m_hTexture + 21) = v234;
  v235 = *(&this->m_Scene_3584.m_hTexture + 14) - *p_m_showGrayBk;
  *(&this->m_Scene_3584.m_hTexture + 24) = v235;
  *(&this->m_Scene_3584.m_hTexture + 28) = v235;
// [VFTABLE] v236 = *(&this->m_Scene_3584.m_hTexture + 14) - (unsigned int)this->m_scrollbar.__vftable;
  *(&this->m_Scene_3584.m_hTexture + 25) = v236;
  *(&this->m_Scene_3584.m_hTexture + 29) = v236;
  v237 = *(&this->m_Scene_3584.m_hTexture + 15) - *(_DWORD *)&this->m_hasKeyCtrl;
  *(&this->m_Scene_3584.m_hTexture + 26) = v237;
  *(&this->m_Scene_3584.m_hTexture + 30) = v237;
  v238 = *(&this->m_Scene_3584.m_hTexture + 15) - this->m_scrollbar.m_fontcolor.Color;
  *(&this->m_Scene_3584.m_hTexture + 27) = v238;
  *(&this->m_Scene_3584.m_hTexture + 31) = v238;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "chuanhai.tga");
  (*((void ( **)(void **, int, int *, CCBUIPanel *, LONG *, _DWORD))this->m_Item_3928.m_id + 8))(
    &this->m_Item_3928.m_id,
    248,
    &this->m_Scene_3584.m_hTexture + 14,
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)&this->m_Item_3928.m_id)->SetUserData();
  this->m_bActive = 1;
  (*(void ( **)(void **, _DWORD))this->m_Item_3928.m_id)(&this->m_Item_3928.m_id, 0);
  *(&this->m_bActive + 1) = 0;
  this->m_Slots[0].m_nPosX = 214;
  this->m_Slots[0].m_nPosY = 149;
  this->m_Slots[0].m_nDimH = 417;
  this->m_Slots[0].m_nDimH2 = 417;
  this->m_Slots[0].m_fDimH = 417.0;
  this->m_Slots[0].m_nMarginX = 923;
  this->m_Slots[0].m_nMarginX2 = 923;
  this->m_Slots[0].m_fMarginX = 923.0;
  v239 = this->m_Slots[0].m_nPosX;
  v240 = this->m_Slots[0].m_nMarginX;
  this->m_Slots[0].m_nEdgeR = v239 + v240;
  this->m_Slots[0].m_nEdgeR2 = v239 + v240;
  v241 = this->m_Slots[0].m_nPosY + this->m_Slots[0].m_nDimH;
  this->m_Slots[0].m_nEdgeB = v241;
  this->m_Slots[0].m_nEdgeB2 = v241;
  v242 = this->m_Slots[0].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[0].m_nClipL = v242;
  this->m_Slots[0].m_nClipL2 = v242;
// [VFTABLE] v243 = this->m_Slots[0].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[0].m_nClipT = v243;
  this->m_Slots[0].m_nClipT2 = v243;
  v244 = this->m_Slots[0].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[0].m_nClipR = v244;
  this->m_Slots[0].m_nClipR2 = v244;
  v245 = this->m_Slots[0].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[0].m_nClipB = v245;
  this->m_Slots[0].m_nClipB2 = v245;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "dadukou.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[0].m_Widget
                                                                                    + 32))(
    this->m_Slots[0].m_Widget,
    249,
    this->m_Slots,
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[0].m_Widget)->SetUserData();
  this->m_Slots[0].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[0].m_Widget)(this->m_Slots[0].m_Widget, 0);
  this->m_Slots[0].m_Widget[377] = 0;
  this->m_Slots[4].m_nPosX = 182;
  this->m_Slots[4].m_nPosY = 136;
  this->m_Slots[4].m_nDimH = 590;
  this->m_Slots[4].m_nDimH2 = 590;
  this->m_Slots[4].m_fDimH = 590.0;
  this->m_Slots[4].m_nMarginX = 94;
  this->m_Slots[4].m_nMarginX2 = 94;
  this->m_Slots[4].m_fMarginX = 94.0;
  v246 = this->m_Slots[4].m_nMarginX;
  v247 = this->m_Slots[4].m_nPosX;
  this->m_Slots[4].m_nEdgeR = v246 + v247;
  this->m_Slots[4].m_nEdgeR2 = v246 + v247;
  v248 = this->m_Slots[4].m_nDimH + this->m_Slots[4].m_nPosY;
  this->m_Slots[4].m_nEdgeB = v248;
  this->m_Slots[4].m_nEdgeB2 = v248;
  v249 = this->m_Slots[4].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[4].m_nClipL = v249;
  this->m_Slots[4].m_nClipL2 = v249;
// [VFTABLE] v250 = this->m_Slots[4].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[4].m_nClipT = v250;
  this->m_Slots[4].m_nClipT2 = v250;
  v251 = this->m_Slots[4].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[4].m_nClipR = v251;
  this->m_Slots[4].m_nClipR2 = v251;
  v252 = this->m_Slots[4].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[4].m_nClipB = v252;
  this->m_Slots[4].m_nClipB2 = v252;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "gutenglin.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[4].m_Widget
                                                                                    + 32))(
    this->m_Slots[4].m_Widget,
    259,
    &this->m_Slots[4],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[4].m_Widget)->SetUserData();
  this->m_Slots[4].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[4].m_Widget)(this->m_Slots[4].m_Widget, 0);
  this->m_Slots[4].m_Widget[377] = 0;
  this->m_Slots[9].m_nPosX = 143;
  this->m_Slots[9].m_nPosY = 117;
  this->m_Slots[9].m_nDimH = 47;
  this->m_Slots[9].m_nDimH2 = 47;
  this->m_Slots[9].m_fDimH = 47.0;
  this->m_Slots[9].m_nMarginX = 357;
  this->m_Slots[9].m_nMarginX2 = 357;
  this->m_Slots[9].m_fMarginX = 357.0;
  v253 = this->m_Slots[9].m_nMarginX;
  v254 = this->m_Slots[9].m_nPosX;
  this->m_Slots[9].m_nEdgeR = v253 + v254;
  this->m_Slots[9].m_nEdgeR2 = v253 + v254;
  v255 = this->m_Slots[9].m_nDimH + this->m_Slots[9].m_nPosY;
  this->m_Slots[9].m_nEdgeB = v255;
  this->m_Slots[9].m_nEdgeB2 = v255;
  v256 = this->m_Slots[9].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[9].m_nClipL = v256;
  this->m_Slots[9].m_nClipL2 = v256;
// [VFTABLE] v257 = this->m_Slots[9].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[9].m_nClipT = v257;
  this->m_Slots[9].m_nClipT2 = v257;
  v258 = this->m_Slots[9].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[9].m_nClipR = v258;
  this->m_Slots[9].m_nClipR2 = v258;
  v259 = this->m_Slots[9].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[9].m_nClipB = v259;
  this->m_Slots[9].m_nClipB2 = v259;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "jiudingshan.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[9].m_Widget
                                                                                    + 32))(
    this->m_Slots[9].m_Widget,
    264,
    &this->m_Slots[9],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[9].m_Widget)->SetUserData();
  this->m_Slots[9].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[9].m_Widget)(this->m_Slots[9].m_Widget, 0);
  this->m_Slots[9].m_Widget[377] = 0;
  this->m_Slots[10].m_nPosX = 120;
  this->m_Slots[10].m_nPosY = 111;
  this->m_Slots[10].m_nDimH = 555;
  this->m_Slots[10].m_nDimH2 = 555;
  this->m_Slots[10].m_fDimH = 555.0;
  this->m_Slots[10].m_nMarginX = 728;
  this->m_Slots[10].m_nMarginX2 = 728;
  this->m_Slots[10].m_fMarginX = 728.0;
  v260 = this->m_Slots[10].m_nPosX;
  v261 = this->m_Slots[10].m_nMarginX;
  this->m_Slots[10].m_nEdgeR = v260 + v261;
  this->m_Slots[10].m_nEdgeR2 = v260 + v261;
  v262 = this->m_Slots[10].m_nPosY + this->m_Slots[10].m_nDimH;
  this->m_Slots[10].m_nEdgeB = v262;
  this->m_Slots[10].m_nEdgeB2 = v262;
  v263 = this->m_Slots[10].m_nMarginX - *p_m_showGrayBk;
  this->m_Slots[10].m_nClipL = v263;
  this->m_Slots[10].m_nClipL2 = v263;
// [VFTABLE] v264 = this->m_Slots[10].m_nMarginX - (unsigned int)this->m_scrollbar.__vftable;
  this->m_Slots[10].m_nClipT = v264;
  this->m_Slots[10].m_nClipT2 = v264;
  v265 = this->m_Slots[10].m_nDimH - *(_DWORD *)&this->m_hasKeyCtrl;
  this->m_Slots[10].m_nClipR = v265;
  this->m_Slots[10].m_nClipR2 = v265;
  v266 = this->m_Slots[10].m_nDimH - this->m_scrollbar.m_fontcolor.Color;
  this->m_Slots[10].m_nClipB = v266;
  this->m_Slots[10].m_nClipB2 = v266;
  sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s%s", g_szDataPath, "jiulongpo.tga");
  (*(void ( **)(char *, int, CCBPanelSlot *, CCBUIPanel *, LONG *, _DWORD))(*(_DWORD *)this->m_Slots[10].m_Widget
                                                                                    + 32))(
    this->m_Slots[10].m_Widget,
    265,
    &this->m_Slots[10],
    this,
    &this->m_scrollbar.m_rect.right,
    0);
  ((CCBUIPanel *)this->m_Slots[10].m_Widget)->SetUserData();
  this->m_Slots[10].m_Widget[376] = 1;
  (**(void ( ***)(char *, _DWORD))this->m_Slots[10].m_Widget)(this->m_Slots[10].m_Widget, 0);
  this->m_Slots[10].m_Widget[377] = 0;
  this->m_Slots[30].m_nMarginX = 0;
  *(_DWORD *)&this->m_Slots[29].m_Widget[380] = 0;
  this->m_Slots[30].m_nDimH = 64;
  this->m_Slots[30].m_nEdgeR = this->m_Slots[30].m_nMarginX + 64;
  (*(void ( **)(int *, int, char *, CCBUIPanel *))(this->m_Slots[30].m_nEdgeB + 16))(
    &this->m_Slots[30].m_nEdgeB,
    240,
    &this->m_Slots[29].m_Widget[380],
    this);
  ((UIScene *)&this->m_Slots[30].m_nEdgeB)->LoadResource((void *)off_59959C);
  ((UIScene *)&this->m_Slots[30].m_nEdgeB)->SetController(1084227584);
  *(float *)&this->m_Slots[30].m_Widget[84] = (float)*(int *)&this->m_Slots[29].m_Widget[380];
  *(float *)&this->m_Slots[30].m_Widget[88] = (float)this->m_Slots[30].m_nMarginX;
  *(_DWORD *)&this->m_Slots[30].m_Widget[92] = (__int64)*(float *)&this->m_Slots[30].m_Widget[84];
  *(_DWORD *)&this->m_Slots[30].m_Widget[96] = (__int64)*(float *)&this->m_Slots[30].m_Widget[88];
  *(_DWORD *)&this->m_Slots[30].m_Widget[132] = 1123024896;
  nVal[1] = 200;
  nVal[0] = 250;
  nVal[2] = 550;
  nVal[3] = 300;
  ((ARC_PlayerAtt *)&this->m_Slots[30].m_Widget[144])->Create((int)&g_PlayerAttBuffer, (int)nVal);
  ((UIItem *)&this->m_Slots[30].m_Widget[144])->SetData(31);
  ((ARC_PlayerAtt *)&this->m_Slots[33].m_Widget[84])->Create((int)&g_PlayerAttBuffer.id + 1, (int)nVal);
  ((UIItem *)&this->m_Slots[33].m_Widget[84])->SetData(31);
  v267 = *(_DWORD *)&this->m_Slots[33].m_Widget[164];
  v268 = *(_DWORD *)&this->m_Slots[33].m_Widget[172];
  *(_DWORD *)&this->m_Slots[33].m_Widget[184] = *(_DWORD *)&this->m_Slots[33].m_Widget[168] + 26;
  *(_DWORD *)&this->m_Slots[33].m_Widget[180] = v267 + 6;
  v269 = *(_DWORD *)&this->m_Slots[33].m_Widget[176] - 38;
  *((_DWORD *)&this->_todo_50B8 + 222) = 0;
  *(_DWORD *)this->m_Data = 20;
  *(_DWORD *)&this->m_Slots[33].m_Widget[188] = v268 - 6;
  *(_DWORD *)&this->m_Slots[33].m_Widget[192] = v269;
  sub_445FA0(&this->_todo_50B8);
  ((PalScript *)&this->m_Data[20])->LoadFromFile("datascript\\SceneName.txt");
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    v273 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->DetachAll3D();
      ((gbAudioManager *)v273)->StopSoundStream(0);
      ((gbAudioManager *)v273)->StopSoundStream(2);
      v274 = CScreenMode::GetInstance();
      ((SoundMgr *)v274)->PlayCPKStream();
    }
  }
  ((UICursor *)v270)->IRender();
}

// 0x00449980
void CCBUIPanel::SetUserData()
{
  _PlugInfo *v1; // [esp+0x4] [ebp+0x4]

  this->m_scrollbar.m_texarrayInfo[6] = v1;
}

// 0x00449990
// attributes: thunk
void CCBUIPanel::Destroy(UIListBox **thisa, int a3)
{
  ((CCBRoleState *)this)->Destroy((UIListBox *)thisa, a3);
}

// 0x00449AB0
int CCBUIPanel::CenterSlot(unsigned int nSlotIdx)
{
  int result; // eax
  int *v4; // ecx
  int v5; // edx
  int v6; // edi
  double v7; // st7
  int v8; // edi
  __int64 v9; // rax
  float nSlotIdxa; // [esp+0x10] [ebp+0x4]

  result = nSlotIdx;
  if ( nSlotIdx <= 0x25 )
  {
    v4 = &this->m_column[0].items.m_needscriptdel + 119 * nSlotIdx;
    v5 = *(_DWORD *)&this->m_column[1].head[476 * nSlotIdx];
    v4[22] = *(_DWORD *)&this->m_column[1].head[476 * nSlotIdx + 4]
           - (*(_DWORD *)&this->m_column[1].head[476 * nSlotIdx + 4] - *(&this->m_column[0].width + 119 * nSlotIdx)) / 2;
    v6 = *(_DWORD *)&this->m_column[1].head[476 * nSlotIdx + 8]
       - (*(_DWORD *)&this->m_column[1].head[476 * nSlotIdx + 8] - v5) / 2;
    v4[23] = v6;
    v7 = (double)*(&this->m_column[1].width + 119 * nSlotIdx) + *(float *)&this->m_Slots[30].m_Widget[84];
    *(float *)&this->m_Slots[30].m_Widget[84] = v7;
    nSlotIdxa = (double)v6 + *(float *)&this->m_Slots[30].m_Widget[88];
    *(float *)&this->m_Slots[30].m_Widget[88] = nSlotIdxa;
    v8 = (__int64)v7;
    *(_DWORD *)&this->m_Slots[30].m_Widget[92] = v8;
    v9 = (__int64)nSlotIdxa;
    *(_DWORD *)&this->m_Slots[30].m_Widget[96] = v9;
    this->m_Slots[30].m_nMarginX = v9;
    *(_DWORD *)&this->m_Slots[29].m_Widget[380] = v8;
    this->m_Slots[30].m_nDimH = v8 + 64;
    this->m_Slots[30].m_nEdgeR = v9 + 64;
    return sub_445FA0(&this->m_Slots[30].m_nEdgeB);
  }
  return result;
}

// 0x00449B90
char CCBUIPanel::FocusCurrentRole()
{
  unsigned int v2; // edi
  char *v3; // esi
  int v4; // eax

  v2 = 0;
  v3 = byte_598C14;
  while ( 1 )
  {
    v4 = _strcmpi(v3, (const char *)&g_RoleSystemInstance);
    if ( !v4 )
      break;
    v3 += 64;
    ++v2;
    if ( (int)v3 >= (int)&off_599594 )
      return v4;
  }
  this->CenterSlot(v2);
  LOBYTE(v4) = ((CCBProtectWindow *)this)->ValidateSlot(v2);
  return v4;
}

// 0x00449C50
int CCBUIPanel::UpdateSlotClipping()
{
  int v2; // ebp
  char *v3; // esi
  int v4; // eax
  int v5; // eax
  int v7; // [esp+0xC] [ebp-0x4]

  v7 = 0;
  v2 = 38;
  v3 = &this->m_column[2].head[4];
  do
  {
    if ( *(v3 - 96) )
    {
      v4 = *((_DWORD *)v3 - 13);
// [VFTABLE] if ( v4 >= (int)this->m_scrollbar.__vftable - this->m_showGrayBk
// [VFTABLE]   || v4 <= -*((_DWORD *)v3 - 5)
// [VFTABLE]   || (v5 = *((_DWORD *)v3 - 11),
// [VFTABLE]   v5 >= (int)(this->m_scrollbar.m_fontcolor.Color - *(_DWORD *)&this->m_hasKeyCtrl))
// [VFTABLE]   || v5 <= -*((_DWORD *)v3 - 4) )
      {
        if ( v3[376] )
        {
          (**(void ( ***)(char *, _DWORD))v3)(v3, 0);
          v3[377] = 0;
        }
      }
      else
      {
        if ( v3[376] )
        {
          (**(void ( ***)(char *, int))v3)(v3, 1);
          v3[377] = 1;
        }
        ++v7;
      }
    }
    v3 += 476;
    --v2;
  }
  while ( v2 );
  return v7;
}

// 0x00449CF0
char CCBUIPanel::UpdateSlotPositions(int nVal)
{
  int v3; // ebp
  char *v4; // esi
  char *v5; // ebx
  double v6; // st7
  int v7; // esi
  __int64 v8; // rax
  double v9; // st7

  v3 = 38;
  v4 = &this->m_column[1].head[32];
  do
  {
    v5 = v4 - 36;
    *((float *)v4 - 1) = *(float *)&this->m_column[0].head[48] + *((float *)v4 - 1);
    *(float *)v4 = *(float *)&this->m_column[0].head[52] + *(float *)v4;
    *(_DWORD *)v5 = (__int64)*((float *)v4 - 1);
    *((_DWORD *)v4 - 8) = (__int64)*(float *)v4;
    *((_DWORD *)v4 - 7) = *((_DWORD *)v4 - 9) + *((_DWORD *)v4 + 9);
    *((_DWORD *)v4 - 6) = *((_DWORD *)v4 - 8) + *((_DWORD *)v4 + 10);
    sub_445FA0(v4 + 56);
    *((_DWORD *)v4 + 1) = *((_DWORD *)v4 - 9) - this->m_showGrayBk;
    v4 += 476;
// [VFTABLE] *((_DWORD *)v4 - 117) = *(_DWORD *)v5 - (unsigned int)this->m_scrollbar.__vftable;
    *((_DWORD *)v4 - 116) = *((_DWORD *)v4 - 127) - *(_DWORD *)&this->m_hasKeyCtrl;
    --v3;
    *((_DWORD *)v4 - 115) = *((_DWORD *)v4 - 127) - this->m_scrollbar.m_fontcolor.Color;
  }
  while ( v3 );
  *(float *)&this->m_Slots[30].m_Widget[84] = *(float *)&this->m_column[0].head[48]
                                            + *(float *)&this->m_Slots[30].m_Widget[84];
  *(float *)&this->m_Slots[30].m_Widget[88] = *(float *)&this->m_column[0].head[52]
                                            + *(float *)&this->m_Slots[30].m_Widget[88];
  v6 = *(float *)&this->m_Slots[30].m_Widget[88];
  v7 = (__int64)*(float *)&this->m_Slots[30].m_Widget[84];
  *(_DWORD *)&this->m_Slots[30].m_Widget[92] = v7;
  *(_DWORD *)&this->m_Slots[30].m_Widget[96] = (__int64)v6;
  this->m_Slots[30].m_nMarginX = (__int64)v6;
  *(_DWORD *)&this->m_Slots[29].m_Widget[380] = v7;
  this->m_Slots[30].m_nDimH = v7 + 64;
  this->m_Slots[30].m_nEdgeR = (__int64)v6 + 64;
  sub_445FA0(&this->m_Slots[30].m_nEdgeB);
  LOBYTE(v8) = this->m_Slots[30].m_Widget[128];
  if ( (_BYTE)v8 )
  {
    *(float *)&this->m_Slots[30].m_Widget[108] = *(float *)&this->m_column[0].head[48]
                                               + *(float *)&this->m_Slots[30].m_Widget[108];
    *(float *)&this->m_Slots[30].m_Widget[112] = *(float *)&this->m_column[0].head[52]
                                               + *(float *)&this->m_Slots[30].m_Widget[112];
    v9 = *(float *)&this->m_Slots[30].m_Widget[112];
    *(_DWORD *)&this->m_Slots[30].m_Widget[100] = (__int64)*(float *)&this->m_Slots[30].m_Widget[108];
    v8 = (__int64)v9;
    *(_DWORD *)&this->m_Slots[30].m_Widget[104] = (__int64)v9;
  }
  return v8;
}

// 0x00449E60
void CCBUIPanel::EnsureSize(int nVal, int nVal2)
{
  int v4; // eax
  int v5; // eax

  v4 = *(_DWORD *)&this->m_Slots[30].m_Widget[92];
  if ( nVal > v4 && nVal2 > *(_DWORD *)&this->m_Slots[30].m_Widget[96] )
  {
    ((UIScene *)&this->m_Slots[30].m_nEdgeB)->LoadResource((void *)off_5995A8);
LABEL_7:
    *(_DWORD *)&this->m_Slots[30].m_Widget[136] = 1;
    goto LABEL_8;
  }
  if ( nVal > v4 && nVal2 <= *(_DWORD *)&this->m_Slots[30].m_Widget[96] )
  {
    ((UIScene *)&this->m_Slots[30].m_nEdgeB)->LoadResource((void *)off_5995A0);
    goto LABEL_7;
  }
LABEL_8:
  v5 = *(_DWORD *)&this->m_Slots[30].m_Widget[92];
  if ( nVal >= v5 )
    return;
  if ( nVal2 > *(_DWORD *)&this->m_Slots[30].m_Widget[96] )
  {
    ((UIScene *)&this->m_Slots[30].m_nEdgeB)->LoadResource((void *)off_5995A4);
LABEL_14:
    *(_DWORD *)&this->m_Slots[30].m_Widget[136] = 0;
    return;
  }
  if ( nVal < v5 && nVal2 <= *(_DWORD *)&this->m_Slots[30].m_Widget[96] )
  {
    ((UIScene *)&this->m_Slots[30].m_nEdgeB)->LoadResource((void *)off_59959C);
    goto LABEL_14;
  }
}

// 0x0044A180
int CCBUIPanel::SetAllSlotsVisible(unsigned __int8 bVisible)
{
  char *v2; // esi
  int v3; // ebx
  int result; // eax

  v2 = &this->m_column[2].head[4];
  v3 = 38;
  do
  {
    result = sub_445E50((int)v2);
    v2 += 476;
    --v3;
  }
  while ( v3 );
  return result;
}

// 0x0044A1B0
BOOL CCBUIPanel::ProcessInput(double st7_0)
{
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  PalScriptMgr *v6; // ecx
  int v7; // eax

  if ( this->m_Slots[33].m_Widget[57] )
// [VFTABLE] return ((UIListBox *)&this->__vftable)->Update(SLODWORD(st7_0), SHIDWORD(st7_0));
  if ( g_nSceneState != 2 && (g_dwGameFlags & 1) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    ((gbAudioManager *)AudioManager)->DetachAll3D();
  }
  if ( this->m_Slots[30].m_Widget[128] )
    LOBYTE(this->m_column[0].items.m_nSize) = 1;

  ((CCBRoleState *)this)->UpdateFadeAlpha();
  if ( !((UIParabolaCtrl *)&this->m_Slots[30].m_Widget[144])->GetState() )
  {
    this->SetAllSlotsVisible(0);
    ((UISceneMap *)this)->ValidateInput(*(_DWORD *)&this->m_Slots[30].m_Widget[140]);
  }
  if ( this->m_Slots[30].m_Widget[128] )
    ((CCBRoleState *)this)->UpdateSpringAnim(*(float *)&st7_0);
  if ( !this->m_Slots[30].m_Widget[129] || !this->m_Slots[30].m_Widget[128] )
    goto LABEL_20;
  v7 = *(_DWORD *)&this->m_Slots[30].m_Widget[136];
  this->m_Slots[30].m_Widget[128] = 0;
  if ( v7 )
  {
    if ( v7 == 1 )
      ((UIScene *)&this->m_Slots[30].m_nEdgeB)->LoadResource((void *)off_5995A0);
  }
  else
  {
    ((UIScene *)&this->m_Slots[30].m_nEdgeB)->LoadResource((void *)off_59959C);
  }
  if ( *(_DWORD *)&this->m_Slots[30].m_Widget[140] <= 0x25u )
  {
    this->ActivateSlot(*(_DWORD *)&this->m_Slots[30].m_Widget[140]);
    return 1;
  }
  else
  {
LABEL_20:
    ((PalScriptMgr *)v6)->RunSceneScript((const char *)LODWORD(st7_0));
// [VFTABLE] return ((UIListBox *)&this->__vftable)->Update(SLODWORD(st7_0), SHIDWORD(st7_0));
  }
}

// 0x0044A4F0
void CCBUIPanel::ActivateSlot(unsigned int nSlotIdx)
{
  PalScriptMgr *v3; // ecx

  if ( nSlotIdx <= 0x25 )
  {
    LOBYTE(v3) = CScreenMode::GetInstance()->m_bRenderAlt;
    if ( (_BYTE)v3 )
      CScreenMode::GetInstance()->m_bRenderAlt = 0;
    ((PalScriptMgr *)v3)->Destroy();
    *(_DWORD *)&this->m_Slots[30].m_Widget[140] = -1;
    ((CGameData *)&g_gamefrm)->Load(0);
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
      *(_DWORD *)&this->m_Slots[30].m_Widget[140] = -1;
      ((CCBRoleState *)this)->InitFadeAndSpring();
    }
    return 1;
  }
  else
  {
    if ( nVal != 1001 )
      return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
    v7 = 0;
    v8 = &dword_56AEE8;
    while ( nVal2 != *v8 )
    {
      ++v8;
      ++v7;
      if ( (int)v8 >= (int)&stru_56AF80 )
        return 1;
    }
    if ( !this->m_Slots[30].m_Widget[128] )
    {
      memset(Destination, 0, sizeof(Destination));
      v10 = 0;
      v11 = 0;
      ((PalScript *)&this->m_Data[20])->SetDirectory(&byte_598C14[64 * v7]);
      ((PalScript *)&this->m_Data[20])->FindSaveStateString((PalScript *)&dir[12], Destination, (char *)0x100, v4);
      if ( !*((_BYTE *)&this->m_column[1].items.m_needscriptdel + 476 * v7) )
      {
        sprintf(
          (char *const)&this->m_scrollbar.m_rect.right,
          "%s%s%s",
          (const char *)dword_DDB03C,
          Destination,
          (const char *)dword_DDB13C);
        ((UICaption *)&this->_todo_50B8)->SetEnable((int)&this->m_scrollbar.m_rect.right, 1);
        ((UIRoleSelect *)&this->m_Slots[33].m_Widget[84])->SetByte(1);
        return 1;
      }
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "%s%s%s",
        (const char *)dword_DD953C,
        Destination,
        (const char *)dword_DD963C);
      memset(Buffer, 0, sizeof(Buffer));
      v13 = 0;
      v14 = 0;
      sprintf(Buffer, byte_5967B0, &this->m_scrollbar.m_rect.right);
      ((UICaption *)&this->m_Slots[31].m_Widget[124])->SetEnable((int)Buffer, 1);
      ((UIRoleSelect *)&this->m_Slots[30].m_Widget[144])->SetByte(1);
      *(_DWORD *)&this->m_Slots[30].m_Widget[140] = v7;
    }
    return 1;
  }
}

// 0x00453D10
int CCBUIPanel::ctor_3D10()
{
// [VFTABLE] ((UIListBox *)&this->__vftable)->UIListBox();
  sub_4422E0(&this->m_scrollbar.m_texarrayInfo[5]);
  sub_4422E0(&this->m_column[0].items.m_needscriptdel);
  UIScene::GetSys();
  sub_4422E0(&this->m_Static_2136);
  sub_4422E0(&this->m_Static_2288);
  sub_4422E0(&this->m_Static_2440);
  sub_4422E0(&this->m_Static_2592);
  sub_4422E0(&this->m_Static_2744);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  ((ARC_PlayerAtt *)&this->m_Item_3928)->Refresh();
  this->m_Slots[2].m_fDimH = 0.0;
  *(_DWORD *)&this->m_hasKeyCtrl = 0;
  this->m_showGrayBk = 0;
// [VFTABLE] this->m_scrollbar.__vftable = (vtbl_0056AE2C *)800;
  this->m_scrollbar.m_fontcolor.Color = 600;
  return (int)this;
}

// 0x00453E70
void CCBUIPanel::ctor()
{
  ((UIRoleDialog *)&this->m_Item_3928)->_UIRoleDialog();
  ((UICaption *)&this->m_Scene_3584)->Destroy2();
  ((UICaption *)&this->m_Scene_3240)->Destroy2();
  ((UICaption *)&this->m_Scene_2896)->Destroy2();
  ((UIFrameWnd *)&this->m_Static_2744)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_2592)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_2440)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_2288)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Static_2136)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_Scene_1792)->Destroy2();
  ((UIFrameWnd *)&this->m_column[0].items.m_needscriptdel)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_scrollbar.m_texarrayInfo[5])->UIFrameWnd::_UIFrameWnd();
// [VFTABLE] ((UIListBox *)&this->__vftable)->_UIListBox();
}

// 0x004544F0
int CCBUIPanel::UpdateButtonVisibility()
{
  sub_445E50((int)&this->m_column[2].head[60]);
  sub_445E50((int)&this->m_column[7].head[16]);
  return sub_445E50((int)(&this->m_nPanelOffsetY + 17));
}

// 0x00454550
char CCBUIPanel::RenderIfUnlocked()
{
  char result; // al
  CCBMagicWindow *v2; // [esp+0x4] [ebp+0x4]

  result = LOBYTE(this->m_Slots[2].m_fMarginX);
  if ( !result )
    ((CCBControlWindow *)this)->Render(v2);
  return result;
}

// 0x00454560
BOOL CCBUIPanel::ProcessInputIfUnlocked(int nVal, int nVal2)
{
  if ( LOBYTE(this->m_Slots[2].m_fMarginX) )
    return 1;
  else
// [VFTABLE] return ((UIListBox *)&this->__vftable)->Update(nVal, nVal2);
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
  unsigned __int8 v18; // [esp+0x0] [ebp-0x8]

  switch ( nVal )
  {
    case 1000:
      if ( nVal2 )
      {

        LOBYTE(this->m_Slots[2].m_fMarginX) = 0;
      }
      return 1;
    case 1001:
      v6 = 0;
      v7 = dword_56B220;
      do
      {
        if ( nVal2 == *v7 )
        {
          this->m_Slots[2].m_nEdgeB2 = v6 + 1;
          v15 = off_5ABBE0;
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v15, 1);
          ((RoleShadow *)this)->CreateFromTemplate(1u);
          ((LineupComp *)this)->SetVisible(0, v18);
          return 1;
        }
        ++v7;
        ++v6;
      }
      while ( (int)v7 < (int)&stru_56B22C );
      switch ( nVal2 )
      {
        case 193:
          ((ChoseCompose *)LODWORD(this->m_Slots[2].m_fDimH))->Init(0);
          break;
        case -1431699013:
          m_fDimH = this->m_Slots[2].m_fDimH;
          m_nEdgeB2 = this->m_Slots[2].m_nEdgeB2;
          LOBYTE(this->m_Slots[2].m_fMarginX) = 1;
          ((UICoverFrm *)LODWORD(m_fDimH))->SetCoverTexture(m_nEdgeB2);
          v16 = off_5ABBE0;
LABEL_16:
          v10 = CScreenMode::GetInstance();
          ((CScreenMode *)v10)->AudioSetPosition(v16, 1);
          return 1;
        case -1431698501:
          ((RoleShadow *)this)->CreateFromTemplate(0);
          ((LineupComp *)this)->SetVisible(1, v18);
          break;
        default:
          return 1;
      }
      v16 = off_5ABBE0;
      goto LABEL_16;
    case 1002:
      v11 = 0;
      v12 = dword_56B220;
      while ( nVal2 != *v12 )
      {
        ++v12;
        ++v11;
        if ( (int)v12 >= (int)&stru_56B22C )
          return 1;
      }
      if ( v11 )
      {
        v13 = v11 - 1;
        if ( v13 )
        {
          if ( v13 == 1 )
            sprintf(
              (char *const)&this->m_scrollbar.m_rect.right,
              "%s\\n%s\\n%s\\n%s",
              (const char *)dword_DD313C,
              (const char *)dword_DD323C,
              (const char *)dword_DD333C,
              (const char *)dword_DD343C);
        }
        else
        {
          sprintf(
            (char *const)&this->m_scrollbar.m_rect.right,
            "%s\\n%s\\n%s\\n%s",
            (const char *)dword_DD2D3C,
            (const char *)dword_DD2E3C,
            (const char *)dword_DD2F3C,
            (const char *)dword_DD303C);
        }
      }
      else
      {
        sprintf(
          (char *const)&this->m_scrollbar.m_rect.right,
          "%s\\n%s\\n%s",
          (const char *)dword_DD2A3C,
          (const char *)dword_DD2B3C,
          (const char *)dword_DD2C3C);
      }
      ((UICaption *)&this->m_column[0].items.m_needscriptdel)->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      return 1;
    case 1003:
      v14 = dword_56B220;
      do
      {
        if ( nVal2 == *v14 )
          ((UICaption *)&this->m_column[0].items.m_needscriptdel)->SetEnable((int)g_szSceneUIText, 0);
        ++v14;
      }
      while ( (int)v14 < (int)&stru_56B22C );
      return 1;
    default:
      return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
  }
}

// 0x0048A170
int CCBUIPanel::InitSlots()
{
  LONG left; // eax
  int result; // eax

  this->m_scrollbar.m_rect.left = 0;
  do
  {
    left = this->m_scrollbar.m_rect.left;
    if ( this->m_column[5].head[left + 21] )
    {
      ((UIListBox *)((char *)this + 4892 * left + 213400))->GetCurSel();
      ((UIListBox *)((char *)this + 4892 * this->m_scrollbar.m_rect.left + 214496))->GetCurSel();
      ((UIListBox *)((char *)this + 4892 * this->m_scrollbar.m_rect.left + 213948))->GetCurSel();
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "%d/%d",
        (int)*((float *)this + 1223 * this->m_scrollbar.m_rect.left + 53389),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_scrollbar.m_rect.left + 9]);
      ((UICaption *)((char *)this + 4892 * this->m_scrollbar.m_rect.left + 213644))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "%d/%d",
        (int)*((float *)this + 1223 * this->m_scrollbar.m_rect.left + 53663),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_scrollbar.m_rect.left + 10]);
      ((UICaption *)((char *)this + 4892 * this->m_scrollbar.m_rect.left + 214740))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "%d/%d",
        (int)*((float *)this + 1223 * this->m_scrollbar.m_rect.left + 53526),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_scrollbar.m_rect.left + 11]);
      ((UICaption *)((char *)this + 4892 * this->m_scrollbar.m_rect.left + 214192))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
    }
    result = this->m_scrollbar.m_rect.left + 1;
    this->m_scrollbar.m_rect.left = result;
  }
  while ( result < 5 );
  return result;
}

// 0x004A3EC0
int CCBUIPanel::InitScrollState()
{
  LONG left; // eax
  int result; // eax

  this->m_scrollbar.m_rect.left = 0;
  do
  {
    left = this->m_scrollbar.m_rect.left;
    if ( *((_BYTE *)&this->m_scrollbar.m_texarrayInfo[5] + left + 1) )
    {
      ((UIListBox *)((char *)this + 3788 * left + 155748))->GetCurSel();
      ((UIListBox *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 156844))->GetCurSel();
      ((UIListBox *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 156296))->GetCurSel();
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "%d/%d",
        (int)*((float *)this + 947 * this->m_scrollbar.m_rect.left + 38976),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_scrollbar.m_rect.left + 9]);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 155992))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "%d/%d",
        (int)*((float *)this + 947 * this->m_scrollbar.m_rect.left + 39250),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_scrollbar.m_rect.left + 10]);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 157088))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "%d/%d",
        (int)*((float *)this + 947 * this->m_scrollbar.m_rect.left + 39113),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->m_scrollbar.m_rect.left + 11]);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 156540))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s %d", (const char *)g_bSlotFlag, 0);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 158000))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s %d", (const char *)&g_bSlotFlag[256], 0);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 158152))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s %d", (const char *)&g_bSlotFlag[512], 0);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 158304))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s %d", byte_DC3F3C, 0);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 158456))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf((char *const)&this->m_scrollbar.m_rect.right, "%s %d", byte_DC403C, 0);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 158608))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
      sprintf(
        (char *const)&this->m_scrollbar.m_rect.right,
        "%s %d %s %d %s %d %s %d",
        (const char *)&g_szRoleName1,
        0,
        (const char *)&g_szRoleName0,
        0,
        (const char *)&g_szRoleName2,
        0,
        (const char *)&g_szRoleName3,
        0);
      ((UICaption *)((char *)this + 3788 * this->m_scrollbar.m_rect.left + 158760))->SetEnable((int)&this->m_scrollbar.m_rect.right, 0);
    }
    result = this->m_scrollbar.m_rect.left + 1;
    this->m_scrollbar.m_rect.left = result;
  }
  while ( result < 5 );
  return result;
}
