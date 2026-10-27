#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_JDHY.h"
#include "Role/Actor.h"
#include "Misc/ArcPastScene.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Misc/ChoseCompose.h"
#include "Misc/MainEquipUI.h"
#include "GameBase/PAL3.h"
#include "Script/PalScript.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "UI/StateUI.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameWnd.h"
#include "Misc/UIParticle.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UISceneMap.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern CHAR byte_DC6A3C[256];

// 0x0045E9F0
void UITitle_JDHY::LayoutCalcRects()
{
  unsigned int m_id; // eax
  int v3; // ecx
  unsigned int v4; // edx
  unsigned int v5; // eax
  char *v6; // ecx
  int v7; // ecx
  _DWORD *v8; // eax
  _DWORD *v9; // edx
  _DWORD *v10; // eax
  _DWORD *v11; // edx
  _DWORD *v12; // eax
  _DWORD *v13; // ecx
  _DWORD *v14; // eax
  _DWORD *v15; // edx
  _DWORD *v16; // eax
  _DWORD *v17; // edx
  _DWORD *v18; // eax
  _DWORD *v19; // edx
  _DWORD *v20; // eax
  _DWORD *v21; // edx
  _DWORD *v22; // eax
  _DWORD *v23; // edx
  _DWORD *v24; // eax
  _DWORD *v25; // edx
  _DWORD *v26; // eax
  _DWORD *v27; // edx
  _DWORD *v28; // eax
  _DWORD *v29; // edx
  _DWORD *v30; // eax
  _DWORD *v31; // edx
  _DWORD *v32; // eax
  _DWORD *v33; // edx
  _DWORD *v34; // eax
  _DWORD *v35; // edx
  _DWORD *v36; // eax
  _DWORD *v37; // edx
  _DWORD *v38; // eax
  _DWORD *v39; // edx
  _DWORD *v40; // eax
  _DWORD *v41; // edx
  _DWORD *v42; // eax
  _DWORD *v43; // edx
  _DWORD *v44; // eax
  _DWORD *v45; // edx
  _DWORD *v46; // eax
  _DWORD *v47; // edx
  _DWORD *v48; // eax
  _DWORD *v49; // edx
  _DWORD *v50; // eax
  _DWORD *v51; // edx
  _DWORD *v52; // eax
  _DWORD *v53; // edx
  _DWORD *v54; // eax
  _DWORD *v55; // edx
  unsigned int v56; // edx
  unsigned int v57; // ecx
  unsigned int v58; // edx
  unsigned int v59; // ecx
  unsigned int v60; // edx
  unsigned int v61; // ecx
  unsigned int v62; // edx
  unsigned int v63; // ecx
  unsigned int v64; // edx
  unsigned int v65; // ecx
  unsigned int v66; // edx
  unsigned int v67; // ecx
  unsigned int v68; // edx
  unsigned int v69; // ecx
  unsigned int v70; // edx
  unsigned int v71; // ecx
  LONG v72; // eax
  unsigned int v73; // edx
  unsigned int v74; // ecx
  unsigned int v75; // edx
  unsigned int v76; // ecx
  unsigned int v77; // edx
  unsigned int v78; // ecx
  unsigned int v79; // edx
  unsigned int v80; // ecx
  unsigned int v81; // edx
  unsigned int v82; // ecx
  unsigned int v83; // edx
  unsigned int v84; // ecx
  unsigned int v85; // edx
  unsigned int v86; // ecx
  unsigned int v87; // edx
  unsigned int v88; // ecx
  LONG v89; // eax
  int v90; // eax
  int v91; // [esp+0x8] [ebp-0x20] BYREF
  int v92; // [esp+0xC] [ebp-0x1C]
  int v93; // [esp+0x10] [ebp-0x18]
  int v94; // [esp+0x14] [ebp-0x14]
  int a2; // [esp+0x18] [ebp-0x10] BYREF
  int v96; // [esp+0x1C] [ebp-0xC]
  int v97; // [esp+0x20] [ebp-0x8]
  int v98; // [esp+0x24] [ebp-0x4]

  this->m_OutFrameT.m_id = 0;
  do
  {
    m_id = this->m_OutFrameT.m_id;
    if ( *((_BYTE *)&this->m_NoteItem[6].m_NotePic.m_FVF + m_id) )
    {
      v3 = *(&this->m_NoteItem[6].m_NotePic.m_bcreateok + 4 * m_id);
      v96 = v3 + 36;
      a2 = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * m_id) - 24;
      v97 = a2 + 24;
      v98 = v3 + 66;
      (((UIWnd *)(&this->m_NoteItem[23].m_ItemRc.bottom + 270 * m_id)))->UIWnd::sub_445FA0(&a2);
      (((UIWnd *)&this->m_NoteItem[23].m_NoteItemBk.m_texarrayInfo[270 * this->m_OutFrameT.m_id + 3]))->UIWnd::sub_445FA0(&a2);
      (((UIWnd *)(&this->m_NoteItem[23].m_NoteID.m_id + 270 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&a2);
      v4 = this->m_OutFrameT.m_id;
      v96 = *(&this->m_NoteItem[6].m_NotePic.m_bcreateok + 4 * v4) + 36;
      a2 = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * v4) + 18;
      v97 = a2 + 22;
      v98 = v96 + 30;
      (((UIWnd *)(&this->m_NoteItem[23].m_NoteState.m_childs.capacity + 270 * v4)))->UIWnd::sub_445FA0(&a2);
      (((UIWnd *)(&this->m_NoteItem[23].m_HeadShot_NO_SEL[0].pDebugTex + 270 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&a2);
      (((UIWnd *)&this->m_NoteItem[23].m_HeadShot_NO_SEL[1].m_text[1080 * this->m_OutFrameT.m_id]))->UIWnd::sub_445FA0(&a2);
      v5 = this->m_OutFrameT.m_id;
      v6 = (char *)this + 16 * v5;
      v92 = *((_DWORD *)v6 + 6566);
      v7 = *((_DWORD *)v6 + 6563) - 6;
      v94 = v92 + 22;
      v91 = v7;
      v93 = v7 + 14;
      (((UIWnd *)&this->m_NoteItem[24].m_HeadShot[6 * v5 + 2].m_ppicInfo))->UIWnd::sub_445FA0(&v91);
      v91 = v93 + 4;
      v93 += 18;
      (((UIWnd *)(&this->m_NoteItem[24].m_NoteTime.m_pbkInfo + 228 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&v91);
      v91 = v93 + 4;
      v93 += 18;
      (((UIWnd *)(&this->m_NoteItem[24].m_NoteMoney.m_pbkInfo + 228 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&v91);
      v91 = v93 + 4;
      v93 += 18;
      (((UIWnd *)&this->m_NoteItem[24].m_HeadShot[6 * this->m_OutFrameT.m_id + 3].m_ppicInfo))->UIWnd::sub_445FA0(&v91);
      v91 = v93 + 4;
      v93 += 18;
      (((UIWnd *)&this->m_NoteItem[24].m_HeadShot[6 * this->m_OutFrameT.m_id + 4].m_ppicInfo))->UIWnd::sub_445FA0(&v91);
      v91 = v93 + 4;
      v93 += 18;
      (((UIWnd *)&this->m_NoteItem[24].m_NoteLv[6 * this->m_OutFrameT.m_id].m_pbkInfo))->UIWnd::sub_445FA0(&v91);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].pDebugTex + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bcreateok + 4 * this->m_OutFrameT.m_id) + 12;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_bfocus + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel
                                                                                              + 4
                                                                                              * this->m_OutFrameT.m_id)
                                                                                            - 30;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_align + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_bfocus
                                                                                             + 192
                                                                                             * this->m_OutFrameT.m_id)
                                                                                           + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ratiow + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].pDebugTex + 192 * this->m_OutFrameT.m_id) + 38;
      ((UIWnd *)(&this->m_NoteItem[6].m_NotePicName + 48 * this->m_OutFrameT.m_id))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_bfocus + 192 * this->m_OutFrameT.m_id);
      v8 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v9 = (_DWORD *)(v8 + 15709);
      v8 += 15713;
      *v8 = *v9;
      v8[1] = (unsigned long)v9[1];
      v8[2] = (unsigned long)v9[2];
      v8[3] = (unsigned long)v9[3];
      (((UIWnd *)((char *)&this->m_NoteItem[7] + 7296 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ratioh + 192 * this->m_OutFrameT.m_id);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * this->m_OutFrameT.m_id + 4] = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].pDebugTex + 192 * this->m_OutFrameT.m_id);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * this->m_OutFrameT.m_id] = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_align + 192 * this->m_OutFrameT.m_id)
                                                                                                 + 2;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * this->m_OutFrameT.m_id + 8] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * this->m_OutFrameT.m_id] + 26;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * this->m_OutFrameT.m_id + 12] = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ratiow + 192 * this->m_OutFrameT.m_id);
      (((UIWnd *)&this->m_NoteItem[7].m_NoteItemBk.m_texarray.m_ptex[1824 * this->m_OutFrameT.m_id + 10]))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * this->m_OutFrameT.m_id]);
      v10 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v11 = (_DWORD *)(v10 + 15717);
      v10 += 15721;
      *v10 = *v11;
      v10[1] = (unsigned long)v11[1];
      v10[2] = (unsigned long)v11[2];
      v10[3] = (unsigned long)v11[3];
      (((UIWnd *)&this->m_NoteItem[7].m_NoteItemBk.m_caption[7296 * this->m_OutFrameT.m_id + 96]))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * this->m_OutFrameT.m_id + 16]);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_nSize + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bcreateok + 4 * this->m_OutFrameT.m_id) + 12;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.capacity + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * this->m_OutFrameT.m_id) - 30;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_needscriptdel + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.capacity + 192 * this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)((UIWnd *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1]) + 192 * this->m_OutFrameT.m_id + 13) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_nSize + 192 * this->m_OutFrameT.m_id) + 38;
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id + 2].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.capacity + 192 * this->m_OutFrameT.m_id);
      v12 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v13 = (_DWORD *)(v12 + 15741);
      v12 += 15745;
      *v12 = *v13;
      v12[1] = (unsigned long)v13[1];
      v12[2] = (unsigned long)v13[2];
      v12[3] = (unsigned long)v13[3];
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id + 3].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_bvisible + 192 * this->m_OutFrameT.m_id);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_ratiow + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_nSize + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_align + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_needscriptdel
                                                                                             + 192
                                                                                             * this->m_OutFrameT.m_id)
                                                                                           + 2;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_ratioh + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_align + 192 * this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_textx + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)((UIWnd *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1]) + 192 * this->m_OutFrameT.m_id + 13);
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id + 4].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_align + 192 * this->m_OutFrameT.m_id);
      v14 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v15 = (_DWORD *)(v14 + 15749);
      v14 += 15753;
      *v14 = *v15;
      v14[1] = (unsigned long)v15[1];
      v14[2] = (unsigned long)v15[2];
      v14[3] = (unsigned long)v15[3];
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot[48 * this->m_OutFrameT.m_id].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_texty + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.top + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bcreateok
                                                                                                + 4
                                                                                                * this->m_OutFrameT.m_id)
                                                                                              + 12;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.left + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel
                                                                                                 + 4
                                                                                                 * this->m_OutFrameT.m_id)
                                                                                               - 30;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.right + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.left
                                                                                                  + 192 * this->m_OutFrameT.m_id)
                                                                                                + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.bottom + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.top + 192 * this->m_OutFrameT.m_id)
                                                                                                 + 38;
      (((UIWnd *)(&this->m_NoteItem[7].m_NoteTime.m_texty + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect + 48 * this->m_OutFrameT.m_id);
      v16 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v17 = (_DWORD *)(v16 + 15773);
      v16 += 15777;
      *v16 = *v17;
      v16[1] = (unsigned long)v17[1];
      v16[2] = (unsigned long)v17[2];
      v16[3] = (unsigned long)v17[3];
      (((UIWnd *)(&this->m_NoteItem[7].m_NoteMoney.m_texty + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_pfather + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_bcreateok + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.top
                                                                                                 + 192
                                                                                                 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_childs.m_needscriptdel + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.right + 192 * this->m_OutFrameT.m_id) + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_bvisible + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_childs.m_needscriptdel
                                                                                                + 192
                                                                                                * this->m_OutFrameT.m_id)
                                                                                              + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_benable + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.bottom
                                                                                               + 192
                                                                                               * this->m_OutFrameT.m_id);
      (((UIWnd *)&this->m_NoteItem[7].m_NoteLv[48 * this->m_OutFrameT.m_id].m_texty))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_childs.m_needscriptdel + 192 * this->m_OutFrameT.m_id);
      v18 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v19 = (_DWORD *)(v18 + 15781);
      v18 += 15785;
      *v18 = *v19;
      v18[1] = (unsigned long)v19[1];
      v18[2] = (unsigned long)v19[2];
      v18[3] = (unsigned long)v19[3];
      (((UIWnd *)&this->m_NoteItem[7].m_NoteLv[48 * this->m_OutFrameT.m_id + 1].m_texty))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_bfocus + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_nTextW + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bcreateok
                                                                                              + 4
                                                                                              * this->m_OutFrameT.m_id)
                                                                                            + 12;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_FVF + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible
                                                                                           + 4 * this->m_OutFrameT.m_id)
                                                                                         + 4;
      *((_DWORD *)((UIWnd *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3]) + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_FVF + 192 * this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_fontcolor.Color + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_nTextW + 192 * this->m_OutFrameT.m_id) + 38;
      (((UIWnd *)(&this->m_NoteItem[7].m_NotePicName.m_texty + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_FVF + 192 * this->m_OutFrameT.m_id);
      v20 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v21 = (_DWORD *)(v20 + 15805);
      v20 += 15809;
      *v20 = *v21;
      v20[1] = (unsigned long)v21[1];
      v20[2] = (unsigned long)v21[2];
      v20[3] = (unsigned long)v21[3];
      (((UIWnd *)(&this->m_NoteItem[8].m_NoteItemBk.m_ratiow + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_wndcolor + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_rect.bottom + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_nTextW + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_rect.right + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)((UIWnd *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3])
                                                                                                  + 192 * this->m_OutFrameT.m_id)
                                                                                                + 2;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_pfather + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_rect.right + 192 * this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_childs.m_pData + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_fontcolor.Color + 192 * this->m_OutFrameT.m_id);
      (((UIWnd *)&this->m_NoteItem[8].m_NoteItemBk.m_caption[7296 * this->m_OutFrameT.m_id + 32]))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_rect.right + 192 * this->m_OutFrameT.m_id);
      v22 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v23 = (_DWORD *)(v22 + 15813);
      v22 += 15817;
      *v22 = *v23;
      v22[1] = (unsigned long)v23[1];
      v22[2] = (unsigned long)v23[2];
      v22[3] = (unsigned long)v23[3];
      (((UIWnd *)(&this->m_NoteItem[8].m_NoteID.m_pfather + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_childs.capacity + 192 * this->m_OutFrameT.m_id);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppicInfo + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bcreateok + 4 * this->m_OutFrameT.m_id) + 12;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppic + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * this->m_OutFrameT.m_id) + 4;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_disablepic + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppic + 192 * this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_disablepicInfo + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppicInfo + 192 * this->m_OutFrameT.m_id) + 38;
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id + 3].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppic + 192 * this->m_OutFrameT.m_id);
      v24 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v25 = (_DWORD *)(v24 + 15837);
      v24 += 15841;
      *v24 = *v25;
      v24[1] = (unsigned long)v25[1];
      v24[2] = (unsigned long)v25[2];
      v24[3] = (unsigned long)v25[3];
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id + 4].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_pbk2 + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_fontcolor.Color + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppicInfo + 192 * this->m_OutFrameT.m_id);
      *((_DWORD *)((UIWnd *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4]) + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_disablepic + 192 * this->m_OutFrameT.m_id) + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_wndcolor.Color + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)((UIWnd *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4]) + 192 * this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_id + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_disablepicInfo
                                                                                          + 192 * this->m_OutFrameT.m_id);
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot[48 * this->m_OutFrameT.m_id].m_pfather))->UIWnd::sub_445FA0((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4] + 768 * this->m_OutFrameT.m_id);
      v26 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v27 = (_DWORD *)(v26 + 15845);
      v26 += 15849;
      *v26 = *v27;
      v26[1] = (unsigned long)v27[1];
      v26[2] = (unsigned long)v27[2];
      v26[3] = (unsigned long)v27[3];
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot[48 * this->m_OutFrameT.m_id + 1].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_rect + 48 * this->m_OutFrameT.m_id);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id + 4] = *(&this->m_NoteItem[6].m_NotePic.m_bcreateok + 4 * this->m_OutFrameT.m_id) + 12;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id] = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * this->m_OutFrameT.m_id)
                                                                                                 + 4;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id + 8] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id] + 26;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id + 12] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id + 4] + 38;
      (((UIWnd *)(&this->m_NoteItem[8].m_NoteMoney.m_rect.right + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id]);
      v28 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v29 = (_DWORD *)(v28 + 15869);
      v28 += 15873;
      *v28 = *v29;
      v28[1] = (unsigned long)v29[1];
      v28[2] = (unsigned long)v29[2];
      v28[3] = (unsigned long)v29[3];
      (((UIWnd *)&this->m_NoteItem[8].m_NoteLv[48 * this->m_OutFrameT.m_id].m_rect.right))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id + 16]);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_disablepicInfo + 192 * this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id + 4];
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_disablepic + 192 * this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id + 8] + 2;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_pbk2 + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_disablepic + 192 * this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_mouseoff + 192 * this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * this->m_OutFrameT.m_id + 12];
      (((UIWnd *)&this->m_NoteItem[8].m_NoteLv[48 * this->m_OutFrameT.m_id + 1].m_rect.right))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_disablepic + 192 * this->m_OutFrameT.m_id);
      v30 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v31 = (_DWORD *)(v30 + 15877);
      v30 += 15881;
      *v30 = *v31;
      v30[1] = (unsigned long)v31[1];
      v30[2] = (unsigned long)v31[2];
      v30[3] = (unsigned long)v31[3];
      (((UIWnd *)&this->m_NoteItem[8].m_NoteLv[48 * this->m_OutFrameT.m_id + 2].m_rect.right))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_FVF + 192 * this->m_OutFrameT.m_id);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepicInfo + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable + 4 * this->m_OutFrameT.m_id) - 38;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepic + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * this->m_OutFrameT.m_id) - 30;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_pbk2 + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepic + 192 * this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_mouseoff + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepicInfo + 192 * this->m_OutFrameT.m_id) + 38;
      (((UIWnd *)&this->m_NoteItem[7].m_NoteID.m_text[7296 * this->m_OutFrameT.m_id]))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepic + 192 * this->m_OutFrameT.m_id);
      v32 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v33 = (_DWORD *)(v32 + 15725);
      v32 += 15729;
      *v32 = *v33;
      v32[1] = (unsigned long)v33[1];
      v32[2] = (unsigned long)v33[2];
      v32[3] = (unsigned long)v33[3];
      (((UIWnd *)&this->m_NoteItem[7].m_NoteState.m_text[7296 * this->m_OutFrameT.m_id]))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_FVF + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_id + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepicInfo
                                                                                          + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_wndcolor.Color + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_pbk2 + 192 * this->m_OutFrameT.m_id) + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.left + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_wndcolor.Color
                                                                                                 + 192
                                                                                                 * this->m_OutFrameT.m_id)
                                                                                               + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.top + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_mouseoff
                                                                                                + 192
                                                                                                * this->m_OutFrameT.m_id);
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_wndcolor + 192 * this->m_OutFrameT.m_id);
      v34 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v35 = (_DWORD *)(v34 + 15733);
      v34 += 15737;
      *v34 = *v35;
      v34[1] = (unsigned long)v35[1];
      v34[2] = (unsigned long)v35[2];
      v34[3] = (unsigned long)v35[3];
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id + 1].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.right + 192 * this->m_OutFrameT.m_id);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * this->m_OutFrameT.m_id + 12] = *(&this->m_NoteItem[6].m_NotePic.m_benable + 4 * this->m_OutFrameT.m_id) - 38;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * this->m_OutFrameT.m_id + 8] = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * this->m_OutFrameT.m_id) - 30;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * this->m_OutFrameT.m_id + 16] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * this->m_OutFrameT.m_id + 8] + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbkInfo + 192 * this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * this->m_OutFrameT.m_id + 12] + 38;
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot[48 * this->m_OutFrameT.m_id + 1].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * this->m_OutFrameT.m_id + 8]);
      v36 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v37 = (_DWORD *)(v36 + 15757);
      v36 += 15761;
      *v36 = *v37;
      v36[1] = (unsigned long)v37[1];
      v36[2] = (unsigned long)v37[2];
      v36[3] = (unsigned long)v37[3];
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot[48 * this->m_OutFrameT.m_id + 2].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_ppic + 192 * this->m_OutFrameT.m_id);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_mouseoff + 192 * this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * this->m_OutFrameT.m_id + 12];
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbk2 + 192 * this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * this->m_OutFrameT.m_id + 16] + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_FVF + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbk2
                                                                                           + 192
                                                                                           * this->m_OutFrameT.m_id)
                                                                                         + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_nTextW + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbkInfo
                                                                                              + 192
                                                                                              * this->m_OutFrameT.m_id);
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot[48 * this->m_OutFrameT.m_id + 3].m_text))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbk2 + 192 * this->m_OutFrameT.m_id);
      v38 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v39 = (_DWORD *)(v38 + 15765);
      v38 += 15769;
      *v38 = *v39;
      v38[1] = (unsigned long)v39[1];
      v38[2] = (unsigned long)v39[2];
      v38[3] = (unsigned long)v39[3];
      (((UIWnd *)this->m_NoteItem[7].m_HeadShot[48 * this->m_OutFrameT.m_id + 4].m_text))->UIWnd::sub_445FA0((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2] + 768 * this->m_OutFrameT.m_id);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_textx + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable + 4 * this->m_OutFrameT.m_id) - 38;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ratioh + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * this->m_OutFrameT.m_id) - 30;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_texty + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ratioh + 192 * this->m_OutFrameT.m_id) + 26;
      (&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_fonttype)[192 * this->m_OutFrameT.m_id] = (Parent_Data *)(*((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_textx + 192 * this->m_OutFrameT.m_id) + 38);
      (((UIWnd *)&this->m_NoteItem[7].m_NoteLv[48 * this->m_OutFrameT.m_id + 2].m_texty))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ratioh + 192 * this->m_OutFrameT.m_id);
      v40 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v41 = (_DWORD *)(v40 + 15789);
      v40 += 15793;
      *v40 = *v41;
      v40[1] = (unsigned long)v41[1];
      v40[2] = (unsigned long)v41[2];
      v40[3] = (unsigned long)v41[3];
      (((UIWnd *)&this->m_NoteItem[7].m_NoteLv[48 * this->m_OutFrameT.m_id + 3].m_texty))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_text[768 * this->m_OutFrameT.m_id]);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_pbkInfo + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_textx + 192 * this->m_OutFrameT.m_id);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_text[768 * this->m_OutFrameT.m_id + 16] = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_texty + 192 * this->m_OutFrameT.m_id) + 2;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ppic + 192 * this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_text[768 * this->m_OutFrameT.m_id + 16] + 26;
      // [overlay-fix 2026-10-27] C2440: Parent_Data* 赋给 _DWORD 解引用位（垃圾形）——待语义修复
      // *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ppicInfo + 192 * this->m_OutFrameT.m_id) = (&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_fonttype)[192 * this->m_OutFrameT.m_id];
      (((UIWnd *)&this->m_NoteItem[7].m_NoteLv[48 * this->m_OutFrameT.m_id + 4].m_texty))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_text[768 * this->m_OutFrameT.m_id + 16]);
      v42 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v43 = (_DWORD *)(v42 + 15797);
      v42 += 15801;
      *v42 = *v43;
      v42[1] = (unsigned long)v43[1];
      v42[2] = (unsigned long)v43[2];
      v42[3] = (unsigned long)v43[3];
      (((UIWnd *)(&this->m_NoteItem[7].m_NotePic.m_texty + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_disablepic + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_benable + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable
                                                                                               + 4
                                                                                               * this->m_OutFrameT.m_id)
                                                                                             - 38;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bvisible + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible
                                                                                                + 4
                                                                                                * this->m_OutFrameT.m_id)
                                                                                              + 4;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bfocus + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bvisible
                                                                                              + 192
                                                                                              * this->m_OutFrameT.m_id)
                                                                                            + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].pDebugTex + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_benable + 192 * this->m_OutFrameT.m_id) + 38;
      (((UIWnd *)(&this->m_NoteItem[8].m_NoteState.m_pfather + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bvisible + 192 * this->m_OutFrameT.m_id);
      v44 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v45 = (_DWORD *)(v44 + 15821);
      v44 += 15825;
      *v44 = *v45;
      v44[1] = (unsigned long)v45[1];
      v44[2] = (unsigned long)v45[2];
      v44[3] = (unsigned long)v45[3];
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_align + 192 * this->m_OutFrameT.m_id);
      (&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_fonttype)[192 * this->m_OutFrameT.m_id] = (Parent_Data *)*(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_benable + 192 * this->m_OutFrameT.m_id);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_texty + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bfocus + 192 * this->m_OutFrameT.m_id) + 2;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_text[768 * this->m_OutFrameT.m_id] = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_texty + 192 * this->m_OutFrameT.m_id)
                                                                                                 + 26;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_text[768 * this->m_OutFrameT.m_id + 4] = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].pDebugTex + 192 * this->m_OutFrameT.m_id);
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id + 1].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_texty + 192 * this->m_OutFrameT.m_id);
      v46 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v47 = (_DWORD *)(v46 + 15829);
      v46 += 15833;
      *v46 = *v47;
      v46[1] = (unsigned long)v47[1];
      v46[2] = (unsigned long)v47[2];
      v46[3] = (unsigned long)v47[3];
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * this->m_OutFrameT.m_id + 2].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_text[768 * this->m_OutFrameT.m_id + 8]);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_pData + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable + 4 * this->m_OutFrameT.m_id) - 38;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_pfather + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * this->m_OutFrameT.m_id) + 4;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.capacity + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_pfather + 192 * this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_nSize + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_pData + 192 * this->m_OutFrameT.m_id) + 38;
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot[48 * this->m_OutFrameT.m_id + 2].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_pfather + 192 * this->m_OutFrameT.m_id);
      v48 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v49 = (_DWORD *)(v48 + 15853);
      v48 += 15857;
      *v48 = *v49;
      v48[1] = (unsigned long)v49[1];
      v48[2] = (unsigned long)v49[2];
      v48[3] = (unsigned long)v49[3];
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot[48 * this->m_OutFrameT.m_id + 3].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_needscriptdel + 192 * this->m_OutFrameT.m_id);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].pDebugTex + 192 * this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_pData + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_bfocus + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.capacity
                                                                                              + 192
                                                                                              * this->m_OutFrameT.m_id)
                                                                                            + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_align + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_bfocus
                                                                                             + 192
                                                                                             * this->m_OutFrameT.m_id)
                                                                                           + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_ratiow + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_nSize + 192 * this->m_OutFrameT.m_id);
      (((UIWnd *)&this->m_NoteItem[8].m_HeadShot[48 * this->m_OutFrameT.m_id + 4].m_pfather))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_bfocus + 192 * this->m_OutFrameT.m_id);
      v50 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v51 = (_DWORD *)(v50 + 15861);
      v50 += 15865;
      *v50 = *v51;
      v50[1] = (unsigned long)v51[1];
      v50[2] = (unsigned long)v51[2];
      v50[3] = (unsigned long)v51[3];
      (((UIWnd *)(&this->m_NoteItem[8].m_NoteTime.m_rect.right + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_ratioh + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot[0].m_id + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable
                                                                                   + 4 * this->m_OutFrameT.m_id)
                                                                                 - 38;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_wndcolor.Color + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible
                                                                                               + 4
                                                                                               * this->m_OutFrameT.m_id)
                                                                                             + 4;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_rect.left + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_wndcolor.Color
                                                                                          + 192 * this->m_OutFrameT.m_id)
                                                                                        + 26;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_rect.top + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_id
                                                                                         + 192 * this->m_OutFrameT.m_id)
                                                                                       + 38;
      (((UIWnd *)&this->m_NoteItem[8].m_NoteLv[48 * this->m_OutFrameT.m_id + 3].m_rect.right))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot[0].m_wndcolor + 192 * this->m_OutFrameT.m_id);
      v52 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v53 = (_DWORD *)(v52 + 15885);
      v52 += 15889;
      *v52 = *v53;
      v52[1] = (unsigned long)v53[1];
      v52[2] = (unsigned long)v53[2];
      v52[3] = (unsigned long)v53[3];
      (((UIWnd *)&this->m_NoteItem[8].m_NoteLv[48 * this->m_OutFrameT.m_id + 4].m_rect.right))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot[0].m_rect.right + 192 * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot[0].m_childs.m_nSize + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_id
                                                                                               + 192
                                                                                               * this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot[0].m_childs.capacity + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_rect.left
                                                                                                + 192
                                                                                                * this->m_OutFrameT.m_id)
                                                                                              + 2;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_childs.m_needscriptdel + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_childs.capacity + 192 * this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_bcreateok + 192 * this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_rect.top
                                                                                          + 192 * this->m_OutFrameT.m_id);
      (((UIWnd *)(&this->m_NoteItem[8].m_NotePic.m_rect.right + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot[0].m_childs.capacity + 192 * this->m_OutFrameT.m_id);
      v54 = (_DWORD *)((char *)this + 768 * this->m_OutFrameT.m_id);
      v55 = (_DWORD *)(v54 + 15893);
      v54 += 15897;
      *v54 = *v55;
      v54[1] = (unsigned long)v55[1];
      v54[2] = (unsigned long)v55[2];
      v54[3] = (unsigned long)v55[3];
      (((UIWnd *)(&this->m_NoteItem[8].m_NotePicName.m_rect.right + 1824 * this->m_OutFrameT.m_id)))->UIWnd::sub_445FA0(&this->m_NoteItem[17].m_HeadShot[0].m_childs.capacity + 192 * this->m_OutFrameT.m_id);
      this->m_OutFrameT.m_rect.left = 0;
      do
      {
        v56 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_align + v56) = (int)&(*(gbTexture **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].pDebugTex + v56))[-1].InFmt.b_shift;
        v57 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].pDebugTex + v57) = *(gbTexture **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_bfocus + v57);
        v58 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ratiow + v58) = *(int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_align + v58);
        v59 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ratioh + v59) = *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_align + v59)
                                                                                + 38;
        v60 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(void **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_texty + v60) = *(char **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_textx
                                                                                         + v60)
                                                                              - 12;
        v61 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(void **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_textx + v61) = *(void **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ratioh
                                                                                         + v61);
        v62 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(Parent_Data **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_fonttype + v62) = *(Parent_Data **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_texty + v62);
        v63 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v63] = (unsigned long)*(char **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_texty
                                                                              + v63)
                                                                   + 38;
        v64 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v64 + 8] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[v64 + 4]
                                                                       - 12;
        v65 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v65 + 4] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[v65];
        v66 = this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[128 * v66 + 12] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[128 * v66 + 8];
        v67 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v67 + 16] = *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v67 + 8]
                                                                        + 38;
        v68 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ppic + v68) = (gbTexture *)&(*(_PlugInfo **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_pbkInfo + v68))[-1]._tex_uvRB.v;
        v69 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_PlugInfo **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_pbkInfo + v69) = *(_PlugInfo **)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[v69 + 16];
        v70 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_PlugInfo **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ppicInfo + v70) = *(_PlugInfo **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ppic + v70);
        v71 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_disablepic + v71) = (gbTexture *)((char *)&(*(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ppic + v71))->InFmt.Type + 2);
        v72 = this->m_OutFrameT.m_rect.left + 1;
        this->m_OutFrameT.m_rect.left = v72;
      }
      while ( v72 < 6 );
      this->m_OutFrameT.m_rect.left = 0;
      do
      {
        v73 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_pbk2 + v73) = (gbTexture *)&(*(_PlugInfo **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepicInfo + v73))[-1]._tex_uvRB.v;
        v74 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_PlugInfo **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_disablepicInfo + v74) = *(_PlugInfo **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepic + v74);
        v75 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)(&this->m_NoteItem[18].m_HeadShot[0].m_mouseoff + v75) = (unsigned long)*(gbTexture **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_pbk2
                                                                                          + v75);
        v76 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_FVF + v76) = (int)&(*(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_pbk2 + v76))->InFmt.Type
                                                                                     + 2;
        v77 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)((char *)((UIWnd *)&this->m_NoteItem[18].m_HeadShot[1]) + v77) = *(int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_nTextW
                                                                                                 + v77)
                                                                             - 12;
        v78 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_nTextW + v78) = *(int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_FVF + v78);
        v79 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(unsigned int *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_fontcolor.Color + v79) = *(_DWORD *)((char *)((UIWnd *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1]) + v79);
        v80 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(unsigned int *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_wndcolor.Color + v80) = *(_DWORD *)((char *)((UIWnd *)&this->m_NoteItem[18].m_HeadShot[1]) + v80) + 38;
        v81 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.left + v81) = *(unsigned int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_id + v81)
                                                                                 - 12;
        v82 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(unsigned int *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_id + v82) = *(unsigned int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_wndcolor.Color + v82);
        v83 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.top + v83) = *(LONG *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.left
                                                                                          + v83);
        v84 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.right + v84) = *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.left
                                                                                            + v84)
                                                                                  + 38;
        v85 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(UIWnd **)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_pfather + v85) = (UIWnd *)(*(LONG *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.bottom + v85)
                                                                                           - 12);
        v86 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.bottom + v86) = *(LONG *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.right
                                                                                             + v86);
        v87 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(char **)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_childs.m_pData + v87) = *(char **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pfather
                                                                                                  + v87);
        v88 = (this->m_OutFrameT.m_rect.left + 6 * this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_childs.capacity + v88) = (int)&(*(UIWnd **)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_pfather + v88))->m_childs.m_pData
                                                                                                 + 2;
        v89 = this->m_OutFrameT.m_rect.left + 1;
        this->m_OutFrameT.m_rect.left = v89;
      }
      while ( v89 < 6 );
    }
    v90 = this->m_OutFrameT.m_id + 1;
    this->m_OutFrameT.m_id = v90;
  }
  while ( v90 < 5 );
}

// 0x0047C1C0
int UITitle_JDHY::HandleDeviceLostA()
{
  PAL3 *Instance_db10; // eax
  float m_snaph; // ecx
  int v4; // eax
  PAL3 *v5; // eax
  int result; // eax
  PAL3 *v7; // ecx
  unsigned __int8 v8; // bl
  PAL3 *v9; // eax
  PAL3 *v10; // eax

  Instance_db10 = (PAL3 *)PAL3::GetInstance_db10();
  (((RenderTarget *)Instance_db10))->RenderTarget::OnDeviceLost(1);
  m_snaph = PAL3::GetInstance_db10()->m_snaph;
  v4 = 1061158912;
  if ( m_snaph != 0.0f )
    v4 = 1065353216;
  this->m_NoteItem[0].m_NoteMoney.m_bfocus = v4;
  this->m_NoteItem[0].m_NoteMoney.m_benable = v4;
  v5 = (PAL3 *)PAL3::GetInstance_db10();
  LOBYTE(result) = (((RenderTarget *)v5))->RenderTarget::OnResetDevice(1);
  if ( (_BYTE)result )
  {
    v8 = g_bGameFlag2;
    g_bGameFlag2 = 0;
    (((PAL3 *)v7))->PAL3::Render();
    g_bGameFlag2 = v8;
    v9 = (PAL3 *)PAL3::GetInstance_db10();
    (((RenderTarget *)v9))->RenderTarget::RenderToScreen();
    this->m_NoteItem[0].m_NoteMoney.m_bvisible = 0;
    v10 = (PAL3 *)PAL3::GetInstance_db10();
    result = (int)(((RenderTarget *)v10))->RenderTarget::GetActiveTexture();
    if ( result )
    {
      if ( *(_DWORD *)(result + 84) )
        this->m_NoteItem[0].m_NoteMoney.m_bvisible = result;
    }
  }
  else
  {
    this->m_NoteItem[0].m_NoteMoney.m_bvisible = 0;
  }
  return result;
}

// 0x004B15F0
int UITitle_JDHY::InitNoteItems()
{
  gbTexture *m_ppic; // eax
  _PlugInfo *m_pbkInfo; // ecx
  int result; // eax
  LONG *p_top; // esi
  _DWORD *v6; // edi
  int v7; // [esp+ACh] [ebp-0x1C]
  int v8; // [esp+B0h] [ebp-0x18]
  int v9; // [esp+B4h] [ebp-0x14]
  _DWORD v10[4]; // [esp+B8h] [ebp-0x10] BYREF

  v10[1] = 42;
  m_ppic = (gbTexture *)this->m_NoteItem[79].m_NotePicName.m_ppic;
  m_pbkInfo = (_PlugInfo *)this->m_NoteItem[79].m_NotePicName.m_pbkInfo;
  result = (int)&m_ppic->NameCrc32;
  v10[0] = 12;
  v10[2] = result;
  v10[3] = (unsigned long)&m_pbkInfo->name[38];
  v7 = 0;
  p_top = (LONG *)&this->m_NoteItem[43].m_HeadShot[4].m_rect.top;
  do
  {
    LOBYTE(result) = g_bDebugMode;
    (*(void ( **)(LONG *, int *, _DWORD *, UITitle_JDHY *, char *, int, int))(*(p_top - 86) + 28))(
      p_top - 86,
      &byte_A00703,
      (_DWORD *)(v10),
      this,
      "UI\\GameMainUI\\System\\Note",
      1,
      result);
    (((PalScript *)(p_top - 86)))->PalScript::OpenScript("UI\\GameMainUI\\System\\Note2.tga", g_bDebugMode);
    *((_BYTE *)p_top - 4) = 0;
    (*(void ( **)(LONG *, _DWORD))*(p_top - 86))(p_top - 86, 0);
    (*(void ( **)(LONG *, int *, _DWORD *, UITitle_JDHY *))(*p_top + 16))(p_top, &byte_A00703, (_DWORD *)(v10), this);
    (((UIScene *)p_top))->UIScene::SetShow(0);
    v9 = v7 + 1;
    sprintf(&this->buf[16], (const char *)&dir[20], v7 + 1);
    (((UICaption *)p_top))->UICaption::SetEnable();
    (*(void ( **)(LONG *, _DWORD))*p_top)(p_top, 0);
    (*(void ( **)(LONG *, int *, _DWORD *, UITitle_JDHY *))(p_top[38] + 16))(
      p_top + 38,
      &byte_A00703,
      (_DWORD *)(v10),
      this);
    (*(void ( **)(LONG *, _DWORD))p_top[38])(p_top + 38, 0);
    v6 = (_DWORD *)(p_top + 76);
    v8 = 5;
    do
    {
      (*(void ( **)(_DWORD *, int *, _DWORD *, UITitle_JDHY *))(v6[190] + 16))(
        v6 + 190,
        &byte_A00703,
        (_DWORD *)(v10),
        this);
      (*(void ( **)(_DWORD *, _DWORD))v6[190])(v6 + 190, 0);
      (*(void ( **)(_DWORD *, int *, _DWORD *, UITitle_JDHY *))(*v6 + 16))(v6, &byte_A00703, (_DWORD *)(v10), this);
      (*(void ( **)(_DWORD *, _DWORD))*v6)(v6, 0);
      (*(void ( **)(_DWORD *, int *, _DWORD *, UITitle_JDHY *))(v6[458] + 16))(
        v6 + 458,
        &byte_A00703,
        (_DWORD *)(v10),
        this);
      AllocObject(v6 + 458);
      (*(void ( **)(_DWORD *, _DWORD))v6[458])(v6 + 458, 0);
      v6 += 38;
      --v8;
    }
    while ( v8 );
    (*(void ( **)(LONG *, int *, _DWORD *, UITitle_JDHY *))(p_top[458] + 16))(
      p_top + 458,
      &byte_A00703,
      (_DWORD *)(v10),
      this);
    AllocObject(p_top + 458);
    (*(void ( **)(LONG *, _DWORD))p_top[458])(p_top + 458, 0);
    (*(void ( **)(LONG *, int *, _DWORD *, UITitle_JDHY *))(p_top[496] + 16))(
      p_top + 496,
      &byte_A00703,
      (_DWORD *)(v10),
      this);
    AllocObject(p_top + 496);
    (*(void ( **)(LONG *, _DWORD))p_top[496])(p_top + 496, 0);
    (*(void ( **)(LONG *, int *, _DWORD *, UITitle_JDHY *))(p_top[724] + 16))(
      p_top + 724,
      &byte_A00703,
      (_DWORD *)(v10),
      this);
    (*(void ( **)(LONG *, _DWORD))p_top[724])(p_top + 724, 0);
    (*(void ( **)(LONG *, int *, _DWORD *, UITitle_JDHY *))(p_top[762] + 16))(
      p_top + 762,
      &byte_A00703,
      (_DWORD *)(v10),
      this);
    AllocObject(p_top + 762);
    (*(void ( **)(LONG *, _DWORD))p_top[762])(p_top + 762, 0);
    p_top += 890;
    *((_BYTE *)&this->m_NoteItem[43].m_HeadShot[1].m_ratioh + v7) = 0;
    result = ++v7;
  }
  while ( v9 < 36 );
  return result;
}

// 0x004B1C00
int UITitle_JDHY::ResetNoteState()
{
  gbTexture *m_pbk2; // eax
  int result; // eax

  m_pbk2 = (gbTexture *)this->m_NoteItem[79].m_NotePicName.m_pbk2;
  if ( m_pbk2 )
  {
    result = (int)&m_pbk2[-1].nLevels + 3;
    if ( !result )
    {
      result = 1;
      *(_DWORD *)this->m_NoteItem[43].m_NoteID.m_text = 1;
      LOBYTE(this->m_NoteItem[43].m_NoteID.m_textx) = 1;
      *(_DWORD *)this->m_NoteItem[43].m_NoteItemBk.m_caption = 0;
      LOBYTE(this->m_NoteItem[43].m_NoteItemBk.m_disablepicInfo) = 0;
    }
  }
  else
  {
    result = 1;
    *(_DWORD *)this->m_NoteItem[43].m_NoteID.m_text = 0;
    LOBYTE(this->m_NoteItem[43].m_NoteID.m_textx) = 0;
    *(_DWORD *)this->m_NoteItem[43].m_NoteItemBk.m_caption = 1;
    LOBYTE(this->m_NoteItem[43].m_NoteItemBk.m_disablepicInfo) = 1;
  }
  return result;
}

// 0x004B2750
FILE * UITitle_JDHY::SaveData(double Data, int nVal)
{
  Actor *SaveDataManager; // eax
  FILE *v5; // edi
  void *v7; // esi
  double v8; // [esp-0x4] [ebp-0x94]
  int v9; // [esp+0x4] [ebp-0x8C]
  char Buffer[125]; // [esp+0x10] [ebp-0x80] BYREF
  __int16 v11; // [esp+0x8D] [ebp-0x3]
  char v12; // [esp+0x8F] [ebp-0x1]

  (((CGameData *)&g_gamefrm))->CGameData::Load(0);
  LODWORD(v8) = LODWORD(Data);
  SaveDataManager = (Actor *)GetSaveDataManager();
  v5 = (((Actor *)SaveDataManager))->Actor::DoSceneTransition(v8, v9);
  if ( v5 )
  {
    v7 = g_pMiniGame3;
    if ( g_pMiniGame3 )
    {
      (((ArcPastScene *)g_pMiniGame3))->ArcPastScene::FreeChildList();
      operator delete(v7);
      g_pMiniGame3 = 0;
      g_bSceneLoaded_0 = 0;
      g_nMiniGameParam = 1;
      g_nMiniGameState = 0;
    }
    PAL3::WriteRegistry("SOFTWARE\\SOFTSTAR\\PAL3_SAVE", (DWORD)"SEEK", LODWORD(Data));
    return v5;
  }
  else
  {
    memset(Buffer, 0, sizeof(Buffer));
    v11 = 0;
    v12 = 0;
    sprintf(Buffer, "\\n            %s", (const char *)&dword_DDB83C);
    (((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype))->UICaption::SetEnable();
    (((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype))->UIRoleSelect::SetByte(1);
    return 0;
  }
}

// 0x004B2920
char UITitle_JDHY::LoadData(int Data)
{
  Actor *SaveDataManager; // eax
  char *v5; // ebx
  Actor *v6; // eax
  __int64 v7; // rax
  int v8; // esi
  int v9; // edi
  int v10; // edi
  char *v11; // esi
  int v12; // eax
  int v13; // edx
  int v14; // [esp+0x0] [ebp-0x2F8]
  int *p_m_pRoleObj; // [esp+0x14] [ebp-0x2E4]
  char *v16; // [esp+0x18] [ebp-0x2E0]
  float v18; // [esp+0x20] [ebp-0x2D8]
  char v19[5]; // [esp+0x24] [ebp-0x2D4]
  char v20[67]; // [esp+0x29] [ebp-0x2CF] BYREF
  int v21; // [esp+0x6C] [ebp-0x28C]
  char v22[257]; // [esp+0x70] [ebp-0x288] BYREF
  __int16 v23; // [esp+0x171] [ebp-0x187]
  char v24; // [esp+0x173] [ebp-0x185]
  char Buffer[125]; // [esp+0x174] [ebp-0x184] BYREF
  __int16 v26; // [esp+0x1F1] [ebp-0x107]
  char v27; // [esp+0x1F3] [ebp-0x105]
  char v28[257]; // [esp+0x1F4] [ebp-0x104] BYREF
  __int16 v29; // [esp+0x2F5] [ebp-0x3]
  char v30; // [esp+0x2F7] [ebp-0x1]

  memset(v28, 0, sizeof(v28));
  v29 = 0;
  v30 = 0;
  SaveDataManager = (Actor *)GetSaveDataManager();
  if ( (((Actor *)SaveDataManager))->Actor::LoadActorModel(Data) )
  {
    sprintf(v28, "Save\\PAL3_%04d.JPG", Data);
    (((gbImage2D *)&g_PAL3_Instance.m_Image2D))->gbImage2D::WriteJpegImage(v28, 100);
    v5 = (char *)this + 3560 * Data;
    v16 = (char *)v5;
    (((UIFrameWnd *)(v5 + 159616)))->UIFrameWnd::SetTextureByID((int)v28);
    (**((void ( ***)(int, int))v5 + 39904))((int)((int)(v5 + 159616)), (int)(1));
    memset(v22, 0, sizeof(v22));
    v23 = 0;
    v24 = 0;
    v6 = (Actor *)GetSaveDataManager();
    (((Actor *)v6))->Actor::LoadSaveData((char *)Data);
    v7 = (__int64)v18;
    v8 = (int)v7 / 3600;
    v9 = (int)v7 / 60 % 60;
    v14 = (int)v7 % 60;
    if ( (int)v7 / 3600 < 100 )
      sprintf(v22, "%s %02d:%02d:%02d", &dword_DC643C, v8, v9, v14);
    else
      sprintf(v22, "%s %03d:%02d:%02d", &dword_DC643C, v8, v9, v14);
    (((UICaption *)(v5 + 158552)))->UICaption::SetEnable();
    sprintf(v22, "%s %d", (const char *)&dword_DC633C, v21);
    (((UICaption *)(v5 + 158704)))->UICaption::SetEnable();
    sprintf(v22, "%s %s", (const char *)&dword_DD933C, v20);
    (((UICaption *)(v5 + 159768)))->UICaption::SetEnable();
    v10 = 0;
    p_m_pRoleObj = (int *)&g_RoleSlotBuf.m_partyActor.m_pRoleObj;
    v11 = (char *)(v5 + 157784);
    do
    {
      if ( v19[v10] )
      {
        v5[v10 + 158544] = 1;
        v12 = (**(int ( ***)(char *, int))v11)((char *)(v11), (int)(1));
        LOBYTE(v12) = g_bDebugMode;
        (((UIPushButton *)v11))->UIPushButton::CreateFromTemplate((void *)off_56F314[v10], v12);
        LOBYTE(v13) = g_bDebugMode;
        (((UIPushButton *)(v11 - 760)))->UIPushButton::CreateFromTemplate((void *)off_56F328[v10], v13);
        (**((void ( ***)(int, _DWORD))v11 - 190))((int)((int)(v11 - 760)), (_DWORD)(0));
        sprintf(v22, "%d %s", *p_m_pRoleObj, byte_DC6A3C);
        (((UICaption *)(v11 + 1072)))->UICaption::SetEnable();
        v5 = (char *)v16;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))v11)((char *)(v11), (_DWORD)(0));
        (**((void ( ***)(int, _DWORD))v11 - 190))((int)((int)(v11 - 760)), (_DWORD)(0));
        v5[v10 + 158544] = 0;
      }
      ++v10;
      v11 += 152;
      p_m_pRoleObj += 352;
    }
    while ( (int)p_m_pRoleObj < (int)&unk_C06198 );
    (((ChoseCompose *)this))->ChoseCompose::LayoutItem(Data, *((_DWORD *)v5 + 39090), *((_DWORD *)v5 + 39091), *((_DWORD *)v5 + 39092), *((_DWORD *)v5 + 39093));
    return PAL3::WriteRegistry("SOFTWARE\\SOFTSTAR\\PAL3_SAVE", (DWORD)"SEEK", Data);
  }
  else
  {
    memset(Buffer, 0, sizeof(Buffer));
    v26 = 0;
    v27 = 0;
    sprintf(Buffer, "\\n            %s", (const char *)&dword_DDB73C);
    (((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype))->UICaption::SetEnable();
    (((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype))->UIRoleSelect::SetByte(1);
    return ((int ( *)(_PlugInfo **, _DWORD))this->m_NoteItem[Data + 44].m_HeadShot_NO_SEL[4].m_pbkInfo->filepos)(
             &this->m_NoteItem[Data + 44].m_HeadShot_NO_SEL[4].m_pbkInfo,
             0);
  }
}

// 0x004B2C70
void UITitle_JDHY::RenderSlotEffects()
{
  int i; // edi
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  (((CCBControlWindow *)this))->CCBControlWindow::Render(v3) /* [ROWTABLE] */;
  if ( *((_BYTE *)&this->m_NoteItem[42].m_NotePic.m_pbkInfo + (unsigned int)this->m_NoteItem[42].m_NotePic.m_ppicInfo) )
  {
    for ( i = 0; i < 16; ++i )
    {
      if ( IsVisible((RenderTarget *)(&this->m_NoteItem[0].m_NotePic.m_fontcolor
                                    + 2336 * (int)this->m_NoteItem[42].m_NotePic.m_ppicInfo
                                    + 146 * i)) )
        ((UIParticle *)((UIParticle *)&this->m_NoteItem[0].m_NotePic.m_fontcolor
        + 16 * (int)this->m_NoteItem[42].m_NotePic.m_ppicInfo
        + i))->UIParticle::Apply(11);
      if ( IsVisible((RenderTarget *)(&this->m_NoteItem[21].m_NoteLv[4].m_nTextW
                                    + 2336 * (int)this->m_NoteItem[42].m_NotePic.m_ppicInfo
                                    + 146 * i)) )
        ((UIParticle *)((UIParticle *)&this->m_NoteItem[21].m_NoteLv[4].m_nTextW
        + 16 * (int)this->m_NoteItem[42].m_NotePic.m_ppicInfo
        + i))->UIParticle::Apply(10);
    }
  }
}

// 0x004B3100
int UITitle_JDHY::UITitle_JDHY_ForwardHitTest(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // esi
  __int64 v5; // rax
  int v6; // ebx
  int v7; // ebp
  int v8; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v10; // eax
  int v11; // [esp-0x10] [ebp-0x14]
  int v12; // [esp-0xC] [ebp-0x10]
  int v13; // [esp-0xC] [ebp-0x10]
  const void *v14; // [esp-0x8] [ebp-0xC]
  const void *v15; // [esp-0x8] [ebp-0xC]
  int v16; // [esp+0x0] [ebp-0x4]
  int a3; // [esp+0xC] [ebp+0x8]

  v3 = v1;
  if ( *(_DWORD *)(v1 + 286376) )
    return 1;
  v5 = (__int64)g_fGameTimer;
  v6 = (int)v5 / 3600;
  v7 = (int)v5 / 60 % 60;
  v11 = (int)v5 % 60;
  if ( (int)v5 / 3600 < 100 )
    sprintf((char *const)(v1 + 104), "%02d:%02d:%02d", v6, v7, v11);
  else
    sprintf((char *const)(v1 + 104), "%03d:%02d:%02d", v6, v7, v11);
  (((UICaption *)(v3 + 4544)))->UICaption::SetEnable();
  sprintf((char *const)(v3 + 104), (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
  (((UICaption *)(v3 + 4696)))->UICaption::SetEnable();
  UITitle_JDHY_HandleNavigation(v2);
  (((CScreenMode *)v3))->CScreenMode::GetMouseDelta();
  UITitle_JDHY_HandleInput(v12);
  if ( !UIParabolaCtrl_GetState(v13) )
  {
    v8 = *(_DWORD *)(v3 + 286372);
    if ( v8 )
    {
      if ( v8 == 1 )
      {
        *(_DWORD *)(v3 + 286376) = 1;
        v14 = (const void *)off_5D11FC;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v14, 1);
        return 1;
      }
    }
    else
    {
      (((UITitle_JDHY *)v3))->UITitle_JDHY::LoadData(*(_DWORD *)(v3 + 286364));
      v15 = (const void *)off_5D11F8;
      v10 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v10))->CScreenMode::AudioSetPosition(v15, 1);
    }
  }
  if ( !UIParabolaCtrl_GetState(v16) )
    (((MainEquipUI *)*(MainEquipUI **)(v3 + 364)))->MainEquipUI::HandleMessage(10);
  return (((SceneObj *)v3))->SceneObj::Update(nVal, a3);
}

// 0x004B3470
int UITitle_JDHY::UITitle_JDHY_OnMessage(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int i; // edi
  CScreenMode *Instance; // eax
  int AudioManager; // eax
  int v6; // edi
  _DWORD *v7; // esi
  int result; // eax
  CScreenMode *v9; // eax
  CScreenMode *v10; // eax
  CScreenMode *v11; // eax
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  CScreenMode *v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // edx
  int v21; // edx
  CScreenMode *v22; // eax
  int v23; // eax
  float v24; // st7
  CScreenMode *v25; // eax
  gbAudioManager *v26; // eax
  float fProgressa; // [esp+0x0] [ebp-0x14]
  float fProgressb; // [esp+0x0] [ebp-0x14]
  float fProgressc; // [esp+0x0] [ebp-0x14]
  const void *fProgress; // [esp+0x0] [ebp-0x14]
  const void *fProgressd; // [esp+0x0] [ebp-0x14]
  const void *fProgresse; // [esp+0x0] [ebp-0x14]
  const void *fProgressf; // [esp+0x0] [ebp-0x14]
  const void *fProgressg; // [esp+0x0] [ebp-0x14]
  const void *fProgressh; // [esp+0x0] [ebp-0x14]
  const void *fProgressi; // [esp+0x0] [ebp-0x14]
  const void *fProgressj; // [esp+0x0] [ebp-0x14]
  const void *fProgressk; // [esp+0x0] [ebp-0x14]
  float v39; // [esp+0x4] [ebp-0x10]
  int *nMsg; // [esp+0x1C] [ebp+0x8]
  int nMsga; // [esp+0x1C] [ebp+0x8]
  int nMsgb; // [esp+0x1C] [ebp+0x8]
  int wParam; // [esp+0x20] [ebp+0xC]

  v2 = v1;
  switch ( nVal )
  {
    case 1000:
      if ( nMsg )
      {
        for ( i = 0; i < 8; ++i )
          (((UITitle_JDHY *)v2))->UITitle_JDHY::InitPageState(i);
        (((UISceneMap *)v2))->UISceneMap::ShowPage();
        (((StateUI *)v2))->StateUI::SaveData();
        if ( g_bRoleSystem_5CEFA9 )
        {
          sub_445E50(v2 + 154796);
          *(_DWORD *)(v2 + 286372) = 0;
        }
        else
        {
          sub_445E50(v2 + 154796);
          *(_DWORD *)(v2 + 286372) = 1;
        }
        UITitle_JDHY_ResetAndRefresh(*(_DWORD *)(v2 + 286372));
        *(_DWORD *)(v2 + 286376) = 0;
        if ( (g_dwGameFlags & 4) != 0 )
        {
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          AudioManager = (((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
          v6 = AudioManager;
          if ( AudioManager )
          {
            fProgressa = *(float *)(AudioManager + 212) * 100.0f;
            (((CScreenMode *)(v2 + 285504)))->CScreenMode::SetProgress(fProgressa);
            fProgressb = *(float *)(v6 + 208) * 100.0f;
            (((CScreenMode *)(v2 + 285776)))->CScreenMode::SetProgress(fProgressb);
            fProgressc = *(float *)(v6 + 204) * 100.0f;
            (((CScreenMode *)(v2 + 285776)))->CScreenMode::SetProgress(fProgressc);
          }
        }
        else
        {
          (((CScreenMode *)(v2 + 285504)))->CScreenMode::SetProgress(0.0);
          (((CScreenMode *)(v2 + 285776)))->CScreenMode::SetProgress(0.0);
          (((CScreenMode *)(v2 + 285776)))->CScreenMode::SetProgress(0.0);
        }
        v7 = (_DWORD *)(v2 + 154480);
        *v7 = 0;
        v7[1] = 0;
        (((UICursor *)0))->UICursor::_todo_541CC0();
        result = 1;
      }
      else
      {
        UITitle_JDHY_ResetAndRefresh(0);
        result = 1;
      }
      break;
    case 1001:
      if ( *(_BYTE *)(v1 + 290461) || *(_BYTE *)(v1 + 287725) )
      {
LABEL_86:
        result = 1;
      }
      else if ( nMsg > &byte_A00110 )
      {
        switch ( (unsigned int)nMsg )
        {
          case 0xA00701u:
            UITitle_JDHY_ScrollDown(1);
            result = 1;
            break;
          case 0xA00702u:
            UITitle_JDHY_ScrollUp(1);
            result = 1;
            break;
          case 0xA00704u:
            if ( *(_DWORD *)(v1 + 286372) )
            {
              *(_DWORD *)(v1 + 286372) = 0;
              UITitle_JDHY_ResetAndRefresh(0);
              (((UITitle_JDHY *)v2))->UITitle_JDHY::ResetNoteState();
              *(_DWORD *)(v2 + 154876) = 1;
              *(_BYTE *)(v2 + 154864) = 1;
              *(_DWORD *)(v2 + 155124) = 0;
              *(_BYTE *)(v2 + 155112) = 0;
            }
            else
            {
              *(_DWORD *)(v1 + 154876) = 1;
              *(_BYTE *)(v1 + 154864) = 1;
            }
            fProgress = (const void *)off_5D11E0;
            goto LABEL_41;
          case 0xA00705u:
            if ( *(_DWORD *)(v1 + 286372) == 1 )
            {
              *(_DWORD *)(v1 + 155124) = 1;
              *(_BYTE *)(v1 + 155112) = 1;
            }
            else
            {
              *(_DWORD *)(v1 + 286372) = 1;
              UITitle_JDHY_ResetAndRefresh(1);
              (((UITitle_JDHY *)v2))->UITitle_JDHY::ResetNoteState();
              *(_DWORD *)(v2 + 155124) = 1;
              *(_BYTE *)(v2 + 155112) = 1;
              *(_DWORD *)(v2 + 154876) = 0;
              *(_BYTE *)(v2 + 154864) = 0;
            }
            fProgress = (const void *)off_5D11E0;
            goto LABEL_41;
          case 0xA00708u:
            *(_BYTE *)(v1 + 286380) = 1;
            sprintf((char *const)(v1 + 104), "\\n        %s", (const char *)&dword_DD383C);
            (((UICaption *)(v2 + 289576)))->UICaption::SetEnable();
            (((UIRoleSelect *)(v2 + 289120)))->UIRoleSelect::SetByte(1);
            fProgress = (const void *)off_5D11C0;
            goto LABEL_41;
          default:
            goto LABEL_42;
        }
      }
      else if ( nMsg == &byte_A00110 )
      {
        fProgressk = (const void *)off_5D11B8;
        v16 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v16))->CScreenMode::AudioSetPosition(fProgressk, 1);
        (((MainEquipUI *)*(MainEquipUI **)(v2 + 364)))->MainEquipUI::HandleMessage(9);
        result = 1;
      }
      else
      {
        switch ( (unsigned int)nMsg )
        {
          case 0xA00102u:
            fProgressd = (const void *)off_5D11B8;
            v9 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v9))->CScreenMode::AudioSetPosition(fProgressd, 1);
            (((MainEquipUI *)*(MainEquipUI **)(v2 + 364)))->MainEquipUI::HandleMessage(0);
            result = 1;
            break;
          case 0xA00103u:
            fProgresse = (const void *)off_5D11B8;
            v10 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v10))->CScreenMode::AudioSetPosition(fProgresse, 1);
            (((MainEquipUI *)*(MainEquipUI **)(v2 + 364)))->MainEquipUI::HandleMessage(3);
            result = 1;
            break;
          case 0xA00104u:
            fProgressf = (const void *)off_5D11B8;
            v11 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v11))->CScreenMode::AudioSetPosition(fProgressf, 1);
            (((MainEquipUI *)*(MainEquipUI **)(v2 + 364)))->MainEquipUI::HandleMessage(2);
            result = 1;
            break;
          case 0xA00105u:
            fProgressg = (const void *)off_5D11B8;
            v12 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v12))->CScreenMode::AudioSetPosition(fProgressg, 1);
            (((MainEquipUI *)*(MainEquipUI **)(v2 + 364)))->MainEquipUI::HandleMessage(1);
            result = 1;
            break;
          case 0xA00106u:
            fProgressh = (const void *)off_5D11B8;
            v13 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v13))->CScreenMode::AudioSetPosition(fProgressh, 1);
            (((MainEquipUI *)*(MainEquipUI **)(v2 + 364)))->MainEquipUI::HandleMessage(5);
            result = 1;
            break;
          case 0xA00107u:
            fProgressi = (const void *)off_5D11B8;
            v14 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v14))->CScreenMode::AudioSetPosition(fProgressi, 1);
            (((MainEquipUI *)*(MainEquipUI **)(v2 + 364)))->MainEquipUI::HandleMessage(6);
            result = 1;
            break;
          case 0xA00108u:
            fProgressj = (const void *)off_5D11B8;
            v15 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v15))->CScreenMode::AudioSetPosition(fProgressj, 1);
            (((MainEquipUI *)*(MainEquipUI **)(v2 + 364)))->MainEquipUI::HandleMessage(4);
            result = 1;
            break;
          default:
            goto LABEL_42;
        }
      }
      break;
    case 1002:
      switch ( (unsigned int)nMsg )
      {
        case 0xA00102u:
          *(_DWORD *)(v1 + 154488) = 0;
          if ( *(_BYTE *)(v1 + 154480) )
            goto LABEL_76;
          (((UITitle_JDHY *)v1))->UITitle_JDHY::InitPageState(0);
          result = 1;
          break;
        case 0xA00103u:
          *(_DWORD *)(v1 + 154488) = 1;
          if ( *(_BYTE *)(v1 + 154481) )
            goto LABEL_76;
          (((UITitle_JDHY *)v1))->UITitle_JDHY::InitPageState(1);
          result = 1;
          break;
        case 0xA00104u:
          *(_DWORD *)(v1 + 154488) = 2;
          if ( *(_BYTE *)(v1 + 154482) )
            goto LABEL_76;
          (((UITitle_JDHY *)v1))->UITitle_JDHY::InitPageState(2);
          result = 1;
          break;
        case 0xA00105u:
          *(_DWORD *)(v1 + 154488) = 3;
          if ( *(_BYTE *)(v1 + 154483) )
            goto LABEL_76;
          (((UITitle_JDHY *)v1))->UITitle_JDHY::InitPageState(3);
          result = 1;
          break;
        case 0xA00106u:
          *(_DWORD *)(v1 + 154488) = 5;
          if ( *(_BYTE *)(v1 + 154485) )
            goto LABEL_76;
          (((UITitle_JDHY *)v1))->UITitle_JDHY::InitPageState(5);
          result = 1;
          break;
        case 0xA00107u:
          *(_DWORD *)(v1 + 154488) = 6;
          if ( *(_BYTE *)(v1 + 154486) )
            goto LABEL_76;
          (((UITitle_JDHY *)v1))->UITitle_JDHY::InitPageState(6);
          result = 1;
          break;
        case 0xA00108u:
          *(_DWORD *)(v1 + 154488) = 4;
          if ( *(_BYTE *)(v1 + 154484) )
            goto LABEL_76;
          (((UITitle_JDHY *)v1))->UITitle_JDHY::InitPageState(4);
          result = 1;
          break;
        case 0xA00109u:
          *(_DWORD *)(v1 + 154488) = 7;
          if ( !*(_BYTE *)(v1 + 154487) )
            (((UITitle_JDHY *)v1))->UITitle_JDHY::InitPageState(7);
          goto LABEL_76;
        default:
LABEL_76:
          result = 1;
          break;
      }
      break;
    case 1003:
      switch ( (unsigned int)nMsg )
      {
        case 0xA00102u:
          *(_DWORD *)(v1 + 154488) = 0;
          *(_BYTE *)(v1 + 154480) = 0;
          result = 1;
          break;
        case 0xA00103u:
          *(_DWORD *)(v1 + 154488) = 1;
          *(_BYTE *)(v1 + 154481) = 0;
          result = 1;
          break;
        case 0xA00104u:
          *(_DWORD *)(v1 + 154488) = 2;
          *(_BYTE *)(v1 + 154482) = 0;
          result = 1;
          break;
        case 0xA00105u:
          *(_DWORD *)(v1 + 154488) = 3;
          *(_BYTE *)(v1 + 154483) = 0;
          result = 1;
          break;
        case 0xA00106u:
          *(_DWORD *)(v1 + 154488) = 5;
          *(_BYTE *)(v1 + 154485) = 0;
          result = 1;
          break;
        case 0xA00107u:
          *(_DWORD *)(v1 + 154488) = 6;
          *(_BYTE *)(v1 + 154486) = 0;
          result = 1;
          break;
        case 0xA00108u:
          *(_DWORD *)(v1 + 154488) = 4;
          *(_BYTE *)(v1 + 154484) = 0;
          result = 1;
          break;
        case 0xA00109u:
          *(_DWORD *)(v1 + 154488) = 7;
          *(_BYTE *)(v1 + 154487) = 0;
          goto LABEL_86;
        default:
          goto LABEL_86;
      }
      break;
    case 1019:
      if ( nMsg == &byte_A00709 )
      {
        nMsgb = *(int *)(v1 + 285736);
        v25 = (CScreenMode *)CScreenMode::GetInstance();
        v26 = (gbAudioManager *)(((CScreenMode *)v25))->CScreenMode::GetAudioManager();
        if ( v26 )
        {
          v39 = *(float *)&nMsgb * 0.009999999776482582f;
          (((gbAudioManager *)v26))->gbAudioManager::SetMusicMasterVolume(v39);
        }
      }
      else if ( (char *)nMsg - (char *)&byte_A00709 == 7 )
      {
        nMsga = *(int *)(v1 + 286008);
        v22 = (CScreenMode *)CScreenMode::GetInstance();
        v23 = (((CScreenMode *)v22))->CScreenMode::GetAudioManager();
        if ( v23 )
        {
          v24 = *(float *)&nMsga * 0.009999999776482582f;
          *(float *)(v23 + 208) = v24;
          *(float *)(v23 + 204) = v24;
          return 1;
        }
      }
      else if ( (char *)nMsg - (char *)&byte_A00709 == 771575 )
      {
        v18 = (__int64)*(float *)(v1 + 285456);
        v19 = *(_DWORD *)(v1 + 285496);
        if ( v18 <= v19 )
        {
          if ( v18 < v19 && v18 <= *(_DWORD *)(v1 + 286352) * (*(_DWORD *)(v1 + 285500) - 1) )
          {
            UITitle_JDHY_ScrollUp(0);
            result = 1;
            v21 = *(_DWORD *)(v2 + 285500) - 1;
            *(_DWORD *)(v2 + 285496) = v18;
            *(_DWORD *)(v2 + 285500) = v21;
            if ( v21 <= 1 )
            {
              *(_DWORD *)(v2 + 285500) = 1;
              return result;
            }
          }
        }
        else if ( v18 >= *(_DWORD *)(v1 + 285500) * *(_DWORD *)(v1 + 286352) )
        {
          UITitle_JDHY_ScrollDown(0);
          v20 = *(_DWORD *)(v2 + 285500);
          *(_DWORD *)(v2 + 285496) = v18;
          *(_DWORD *)(v2 + 285500) = v20 + 1;
          if ( v20 + 1 > 36 )
          {
            *(_DWORD *)(v2 + 285500) = 36;
            return 1;
          }
        }
      }
      result = 1;
      break;
    case 1021:
      if ( nMsg == &byte_A00704 )
      {
        sprintf((char *const)(v1 + 104), "\\n        %s", (const char *)&dword_DD8A3C);
        (((UICaption *)(v2 + 288208)))->UICaption::SetEnable();
        (((UIRoleSelect *)(v2 + 287752)))->UIRoleSelect::SetByte(1);
        fProgress = (const void *)off_5D11C0;
LABEL_41:
        v17 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v17))->CScreenMode::AudioSetPosition(fProgress, 1);
      }
LABEL_42:
      result = 1;
      break;
    default:
      result = (((UIWnd *)v1))->UIWnd::OnMessage(nVal, (int)nMsg, wParam);
      break;
  }
  return result;
}

// 0x004B43E0
int UITitle_JDHY::InitPageState(int nPage)
{
  int *v3; // ebx
  char *v4; // edi
  int v5; // esi
  gbColorQuad *v6; // ebp
  int v7; // eax
  int v8; // eax
  gbColorQuad *v9; // edi
  gbColorQuad *v10; // esi
  bool v11; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  float fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  float fYb; // [esp+0x4] [ebp-0x20]
  char *v19; // [esp+0x18] [ebp-0xC]
  int v20; // [esp+0x1C] [ebp-0x8]
  int nPagea; // [esp+0x28] [ebp+0x4]

  this->m_NoteItem[42].m_NotePic.m_pbkInfo = ((_PlugInfo *)0);
  this->m_NoteItem[42].m_NotePic.m_ppic = ((gbTexture *)0);
  nPagea = 16;
  *((_BYTE *)&this->m_NoteItem[42].m_NotePic.m_pbkInfo + nPage) = 1;
  v3 = (int *)(&this->m_NoteItem[42].m_NoteLv[4].m_mouseoff + 16 * nPage);
  v4 = (char *)this + 16 * nPage;
  v5 = *((_DWORD *)v4 + 38590) - *v3;
  v19 = (char *)v4;
  v20 = v5;
  v6 = (gbColorQuad *)(&this->m_NoteItem[0].m_NotePic.m_fontcolor + 2336 * nPage);
  while ( 1 )
  {
    (((RenderTarget *)v6))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v6))->RenderTarget::SetSize(32);
    fY = rand() % 10 + 58;
    fX = rand() % 10 + 66;
    v7 = rand();
    (((RenderTarget *)v6))->RenderTarget::SetColor(v7 % 10 - 6, fX, fY);
    v8 = rand();
    (((RenderTarget *)v6))->RenderTarget::SetAlpha(v8 % 55 - 56);
    LOBYTE(v6[26].Color) = 1;
    (((RenderTarget *)v6))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v6))->RenderTarget::SetState(1067030938);
    fYa = (float)*((int *)v4 + 38589);
    fXa = (float)(*v3 + rand() % v5);
    (((RenderTarget *)v6))->RenderTarget::UpdateTransform(fXa, fYa);
    (((RenderTarget *)v6))->RenderTarget::Render(*v3, v3[1], v3[2]);
    fYb = (float)(rand() % 2 + 1);
    fXb = (float)(rand() % 2 + 1);
    (((RenderTarget *)v6))->RenderTarget::SetOffset(fXb, fYb);
    (((RenderTarget *)v6))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v6))->RenderTarget::SetVisible(1);
    v9 = (gbColorQuad *)(v6 + 18688);
    v10 = (gbColorQuad *)v6;
    v6 += 146;
    result = nPagea - 1;
    v11 = nPagea == 1;
    qmemcpy(v9, v10, 0x248u);
    --nPagea;
    if ( v11 )
      break;
    v4 = (char *)v19;
    v5 = v20;
  }
  return result;
}
