#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBProtectWindow.h"

// Forward declarations for unnamed functions
int sub_445E50(int a2); // from annotations
int sub_519180(...);
int sub_525080(...);
int sub_525090(void *_this); // from annotations

// Unnamed globals (extern)
extern CHAR byte_DC6A3C[256];
extern int dword_17AD59C;
extern int dword_17AD5C8[];
extern int dword_17AD5CC[];
extern int dword_DC783C;
extern char dword_DCDA3C[];
extern char dword_DCDB3C[];
extern char dword_DCDC3C[];
extern char dword_DCDD3C[];
extern char dword_DCDE3C[];
extern char dword_DCDF3C[];
extern char dword_DCE03C[];
extern char dword_DCE13C[];
extern char dword_DCE23C[];
extern char dword_DCE33C[];
extern char dword_DCE43C[];
extern char dword_DCE53C[];
extern char dword_DCE63C[];
extern char dword_DCE73C[];
extern int dword_DCF53C;
extern int dword_DD373C;
extern int dword_DDB23C;
extern int dword_DDB33C;
extern int dword_DDB43C;
extern int dword_DDB53C;
extern int dword_DDB63C;
extern float flt_17AD598;
extern RoleSystem stru_C059A0;
extern const char * unk_5DFF88;
extern const char * unk_5DFF90;
extern const char * unk_5DFF94;

// 0x0043D7A0
int CCBProtectWindow::ForwardOnMessage(int nVal, int nMsg, int wParam)
{
  return ((PalScript *)this)->OnMessage(nVal, nMsg, wParam);
}

// 0x00449BE0
char CCBProtectWindow::ValidateSlot(unsigned int dwVal)
{
  char result; // al

  result = dwVal;
  if ( dwVal <= 0x25 )
    return ((SceneInfo *)((char *)this + 360))->ProcessCollision(*((_DWORD *)this + 119 * dwVal + 131), *((_DWORD *)this + 119 * dwVal + 132));
  return result;
}

// 0x00516100
CCBProtectWindow * CCBProtectWindow::_sdtor_19(CCBProtectWindow *Block, char a2)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00518E30
BOOL CCBProtectWindow::ShowAndNotify(int nVal, int nVal2)
{
  sub_519180();
  ((CCBUI *)this)->ShowDialogWindow();
  ((CCBUI *)this)->HideAll();
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x0051D6E0
CCBProtectWindow::CCBProtectWindow()
{
  dword_17AD59C = 1094713344;
}

// 0x0051D6F0
// attributes: thunk
void CCBProtectWindow::_CCBProtectWindow()
{

}

// 0x0051D700
void CCBProtectWindow::Reset()
{
  flt_17AD598 = 12.0 + 12.0;
}

// 0x0051DD80
void CCBProtectWindow::Destroy()
{
  char v2; // [esp+0x8] [ebp+0x4]

  ((CCBStage *)this)->ShowWindow();
  if ( (v2 & 1) != 0 )
    operator delete(this);
}

// 0x0051F1B0
int CCBProtectWindow::OnMessage(int nVal, int nVal2, int nVal3)
{
  CScreenMode *Instance; // eax
  int v7; // eax
  int v8; // esi
  char *v9; // ecx
  int v10; // edi
  int v11; // edi
  char *v12; // ecx
  void *v13; // edx
  CCBProtectWindow *v14; // ecx
  _BYTE *v15; // eax
  int *v16; // edi
  bool v17; // zf
  CUtil *v18; // ecx
  CScreenMode *v19; // eax
  void ( ***v20)(char *, int); // esi
  char *v21; // edi
  CScreenMode *v22; // eax
  CScreenMode *v23; // eax
  PalScriptMgr *v24; // ecx
  CScreenMode *v25; // eax
  int v26; // eax
  const void *v27; // esi
  int v28; // eax
  int v29; // edx
  int v30; // ecx
  char *v31; // edx
  unsigned int v32; // eax
  char *v33; // edi
  char *v34; // esi
  char v35; // cl
  int v36; // eax
  int v37; // eax
  const void *v38; // esi
  int v39; // eax
  int v40; // edx
  int v41; // ecx
  char *v42; // edx
  unsigned int v43; // eax
  char *v44; // edi
  char *v45; // esi
  char v46; // cl
  int v47; // eax
  CScreenMode *v48; // eax
  char *v49; // ecx
  char *v50; // ecx
  CScreenMode *v51; // eax
  char *v52; // ecx
  void ( **v53)(int); // eax
  UIButton **v54; // esi
  UIButton **v55; // esi
  UIButton **v56; // esi
  CScreenMode *v57; // eax
  CScreenMode *v58; // eax
  int v59; // eax
  int v60; // esi
  int v61; // eax
  int v62; // ecx
  DWORD Time; // eax
  int v64; // esi
  int v65; // eax
  signed int v66; // esi
  void *v67; // eax
  int ItemID; // eax
  int v69; // eax
  int v70; // eax
  int v71; // edx
  CCBProtectWindow *v72; // ecx
  int SkillNum; // esi
  int v74; // ecx
  unsigned int v75; // edx
  void *v76; // ecx
  signed int v77; // edi
  int v78; // eax
  int v79; // esi
  int v80; // esi
  signed int v81; // edi
  int v82; // eax
  int v83; // eax
  int v84; // edx
  CCBProtectWindow *v85; // ecx
  int v86; // eax
  int v87; // ecx
  char v88; // al
  int v89; // ecx
  int v90; // eax
  unsigned int v91; // edx
  int Size; // esi
  void *v93; // eax
  signed int v94; // edi
  int v95; // ecx
  _DWORD *v96; // eax
  int v97; // eax
  signed int v98; // esi
  int v99; // eax
  int v100; // eax
  int v101; // eax
  int v102; // ecx
  _DWORD *v103; // edx
  int v104; // esi
  CCBProtectWindow *v105; // ecx
  _BYTE *v106; // eax
  char v107; // cl
  int v108; // ecx
  int v109; // eax
  unsigned int v110; // edx
  UIButton **v111; // esi
  int v112; // esi
  int v113; // esi
  int v114; // esi
  const char *v115; // [esp-0x8] [ebp-0x38]
  const char *v116; // [esp-0x8] [ebp-0x38]
  const char *v117; // [esp-0x8] [ebp-0x38]
  const char *v118; // [esp-0x8] [ebp-0x38]
  const char *v119; // [esp-0x8] [ebp-0x38]
  const char *v120; // [esp-0x8] [ebp-0x38]
  const char *v121; // [esp-0x8] [ebp-0x38]
  const char *v122; // [esp-0x8] [ebp-0x38]
  const char *v123; // [esp-0x8] [ebp-0x38]
  int v124; // [esp-0x4] [ebp-0x34]
  char pOut[12]; // [esp+0xC] [ebp-0x24] BYREF
  int v126; // [esp+0x18] [ebp-0x18]
  void *Block; // [esp+0x1C] [ebp-0x14]
  unsigned int v128; // [esp+0x20] [ebp-0x10]
  _DWORD *v129; // [esp+0x24] [ebp-0xC]
  const void *v130; // [esp+0x28] [ebp-0x8]
  signed int i; // [esp+0x2C] [ebp-0x4]
  int nVala; // [esp+0x38] [ebp+0x8]
  CCBProtectWindow *nValb; // [esp+0x38] [ebp+0x8]
  char *nValc; // [esp+0x38] [ebp+0x8]
  char *nVald; // [esp+0x38] [ebp+0x8]
  char *nVale; // [esp+0x38] [ebp+0x8]
  int nValf; // [esp+0x38] [ebp+0x8]
  int nValg; // [esp+0x38] [ebp+0x8]
  int nVal2a; // [esp+0x3C] [ebp+0xC]
  CCBProtectWindow *nVal2b; // [esp+0x3C] [ebp+0xC]
  char *nVal2c; // [esp+0x3C] [ebp+0xC]
  char *nVal2d; // [esp+0x3C] [ebp+0xC]
  int nVal2f; // [esp+0x3C] [ebp+0xC]
  float nVal2g; // [esp+0x3C] [ebp+0xC]
  signed int nVal2e; // [esp+0x3C] [ebp+0xC]
  int nVal3a; // [esp+0x40] [ebp+0x10]
  int nVal3b; // [esp+0x40] [ebp+0x10]
  int nVal3c; // [esp+0x40] [ebp+0x10]
  int nVal3d; // [esp+0x40] [ebp+0x10]

  if ( nVal == 1000 )
  {
    if ( nVal2 )
    {
      v59 = sub_525080(*((UIWnd **)this + 2003));
      *((_DWORD *)this + 2011) = v59;
      *((_DWORD *)this + 86395) = v59;
      v60 = *((_DWORD *)this + 2011);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      switch ( v60 )
      {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
          sub_445E50((int)this + 1744);
          sub_445E50((int)this + 2088);
          sub_445E50((int)this + 2432);
          sub_445E50((int)this + 2680);
          break;
        default:
          break;
      }
      *((_DWORD *)this + 2012) = sub_525090(*((void **)this + 2003));
      nVal2f = *(_DWORD *)(*((_DWORD *)this + 2003) + 5256);
      *((_DWORD *)this + 82005) = nVal2f;
      nVal2g = (double)nVal2f * *(float *)(*((_DWORD *)this + 2012) + 216);
      *((_DWORD *)this + 82006) = (int)nVal2g;
      *((_DWORD *)this + 86395) = *((_DWORD *)this + 2011);
      *((_DWORD *)this + 86393) = *((_DWORD *)this + 82005);
      qmemcpy((char *)this + 345584, *((const void **)this + 2012), 0xDCu);
      v61 = *((_DWORD *)this + 2003);
      v62 = *(unsigned __int8 *)(v61 + 3868);
      *(_BYTE *)(v61 + 3868) = 0;
      if ( (_BYTE)v62 )
      {
        nVal3d = 0;
        while ( 1 )
        {
          Time = timeGetTime();
          CRT_set_new_handler(Time);
          memset(g_CCBProtectData, 0, 0x30u);
          v64 = 0;
          nVal2e = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillID();
          v65 = *((_DWORD *)this + 2012);
          if ( *(int *)(v65 + 12) > 0 )
            break;
LABEL_126:
          v66 = 0;
          v67 = 0;
          nValg = 0;
          Block = 0;
          if ( nVal2e > 0 )
          {
            do
            {
              ItemID = ((PAL_GDB *)&g_pGDB)->GetItemID(v66);
              if ( *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(ItemID) + 612) == 1 )
                Block = (char *)Block + 1;
              ++v66;
            }
            while ( v66 < nVal2e );
            v67 = Block;
          }
          v128 = 12 * nVal3d;
          if ( (int)v67 < *(_DWORD *)&g_CCBProtectData[12 * nVal3d] )
            *(_DWORD *)&g_CCBProtectData[12 * nVal3d] = v67;
          for ( i = 0; i < nVal2e; ++i )
          {
            v69 = rand();
            v70 = ((PAL_GDB *)&g_pGDB)->GetItemID(v69 % nVal2e);
            v71 = 0;
            if ( nValg <= 0 )
            {
LABEL_138:
              SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v70);
              v130 = (const void *)SkillNum;
              if ( *(int *)(SkillNum + 608) > 0 && *(_BYTE *)(SkillNum + 612) == 1 )
              {
                qmemcpy(
                  (char *)this + 53328 * nVal3d + 26664 * nVal3d + 808 * nValg + 8052,
                  (const void *)SkillNum,
                  0x320u);
                v74 = nValg + 50 * nVal3d;
                ++nValg;
                v75 = v128;
                qmemcpy((char *)this + 808 * v74 + 507668, v130, 0x320u);
                if ( nValg >= *(_DWORD *)&g_CCBProtectData[v75] )
                  break;
              }
            }
            else
            {
              v72 = (CCBProtectWindow *)((char *)this + 79992 * nVal3d + 8052);
// [VFTABLE] while ( (vtbl_0056AE2C *)v70 != v72->__vftable )
              {
                ++v71;
                v72 = (CCBProtectWindow *)((char *)v72 + 808);
                if ( v71 >= nValg )
                  goto LABEL_138;
              }
            }
          }
          v76 = 0;
          v77 = 0;
          Block = 0;
          if ( nVal2e > 0 )
          {
            do
            {
              v78 = ((PAL_GDB *)&g_pGDB)->GetItemID(v77);
              v79 = v78;
              if ( v78 != 6119
                && v78 != 6120
                && v78 != 6121
                && v78 != 6122
                && v78 != 6123
                && v78 != 6124
                && v78 != 6125
                && v78 != 6427
                && v78 != 6408
                && v78 != 6409
                && v78 != 6410
                && v78 != 6411
                && v78 != 6412
                && v78 != 6413
                && (*(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v78) + 612) == 2
                 || *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v79) + 612) == 3) )
              {
                Block = (char *)Block + 1;
              }
              ++v77;
            }
            while ( v77 < nVal2e );
            v76 = Block;
          }
          if ( (int)v76 < dword_17AD5C8[v128 / 4] )
            dword_17AD5C8[v128 / 4] = (int)v76;
          v129 = 0;
          i = 0;
          if ( nVal2e > 0 )
          {
            v80 = nVal3d;
            v81 = nVal2e;
            do
            {
              v82 = rand();
              v83 = ((PAL_GDB *)&g_pGDB)->GetItemID(v82 % v81);
              if ( v83 != 6119
                && v83 != 6120
                && v83 != 6121
                && v83 != 6122
                && v83 != 6123
                && v83 != 6124
                && v83 != 6125
                && v83 != 6427
                && v83 != 6408
                && v83 != 6409
                && v83 != 6410
                && v83 != 6411
                && v83 != 6412
                && v83 != 6413 )
              {
                v84 = 0;
                if ( nValg <= 0 )
                {
LABEL_184:
                  v86 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v83);
                  v87 = *(_DWORD *)(v86 + 608);
                  v130 = (const void *)v86;
                  if ( v87 > 0 )
                  {
                    v88 = *(_BYTE *)(v86 + 612);
                    if ( v88 == 2 || v88 == 3 )
                    {
                      qmemcpy((char *)this + 53328 * nVal3d + 26664 * nVal3d + 808 * nValg + 8052, v130, 0x320u);
                      v89 = nValg + 50 * nVal3d;
                      ++nValg;
                      v129 = (_DWORD *)((char *)v129 + 1);
                      v90 = (int)v129;
                      v91 = v128;
                      qmemcpy((char *)this + 808 * v89 + 507668, v130, 0x320u);
                      if ( v90 >= *(int *)((char *)dword_17AD5C8 + v91) )
                        break;
                      v81 = nVal2e;
                      v80 = nVal3d;
                    }
                  }
                }
                else
                {
                  v85 = (CCBProtectWindow *)((char *)this + 79992 * v80 + 8052);
// [VFTABLE] while ( (vtbl_0056AE2C *)v83 != v85->__vftable )
                  {
                    ++v84;
                    v85 = (CCBProtectWindow *)((char *)v85 + 808);
                    if ( v84 >= nValg )
                      goto LABEL_184;
                  }
                }
              }
              ++i;
            }
            while ( i < v81 );
          }
          ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(4);
          Size = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize();
          v126 = Size;
          v93 = operator new(4 * Size);
          v94 = 0;
          Block = v93;
          if ( Size > 0 )
          {
            v129 = v93;
            do
            {
              v95 = *(_DWORD *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, v94);
              v96 = v129;
              ++v94;
              *v129 = v95;
              v129 = v96 + 1;
            }
            while ( v94 < Size );
          }
          v97 = 0;
          v98 = 0;
          v129 = 0;
          if ( nVal2e > 0 )
          {
            do
            {
              v99 = ((PAL_GDB *)&g_pGDB)->GetItemID(v98);
              if ( *((_DWORD *)Block + v94) != v99
                && v99 != 6001
                && v99 != 6023
                && v99 != 6021
                && v99 != 6025
                && v99 != 6026
                && v99 != 6010
                && *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v99) + 612) == 4 )
              {
                v129 = (_DWORD *)((char *)v129 + 1);
              }
              ++v98;
            }
            while ( v98 < nVal2e );
            v97 = (int)v129;
          }
          if ( v97 < dword_17AD5CC[v128 / 4] )
            dword_17AD5CC[v128 / 4] = v97;
          v129 = 0;
          for ( i = 0; i < nVal2e; ++i )
          {
            v100 = rand();
            v101 = ((PAL_GDB *)&g_pGDB)->GetItemID(v100 % nVal2e);
            v102 = 0;
            if ( v126 <= 0 )
            {
LABEL_212:
              if ( v101 != 6001 && v101 != 6023 && v101 != 6021 && v101 != 6025 && v101 != 6026 && v101 != 6010 )
              {
                v104 = 0;
                if ( nValg <= 0 )
                {
LABEL_222:
                  v106 = (_BYTE *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v101);
                  v107 = v106[612];
                  v130 = v106;
                  if ( v107 == 4 )
                  {
                    qmemcpy((char *)this + 53328 * nVal3d + 26664 * nVal3d + 808 * nValg + 8052, v130, 0x320u);
                    v108 = nValg + 50 * nVal3d;
                    ++nValg;
                    v129 = (_DWORD *)((char *)v129 + 1);
                    v109 = (int)v129;
                    v110 = v128;
                    qmemcpy((char *)this + 808 * v108 + 507668, v130, 0x320u);
                    if ( v109 >= *(int *)((char *)dword_17AD5CC + v110) )
                      break;
                  }
                }
                else
                {
                  v105 = (CCBProtectWindow *)((char *)this + 79992 * nVal3d + 8052);
// [VFTABLE] while ( (vtbl_0056AE2C *)v101 != v105->__vftable )
                  {
                    ++v104;
                    v105 = (CCBProtectWindow *)((char *)v105 + 808);
                    if ( v104 >= nValg )
                      goto LABEL_222;
                  }
                }
              }
            }
            else
            {
              v103 = Block;
              while ( v101 != *v103 )
              {
                ++v102;
                ++v103;
                if ( v102 >= v126 )
                  goto LABEL_212;
              }
            }
          }
          if ( Block )
            operator delete(Block);
          *((_DWORD *)this + nVal3d + 2007) = nValg;
          *((_DWORD *)this + nVal3d + 167317) = nValg;
          *((_DWORD *)this + 86389) = 0;
          ++nVal3d;
          *((_DWORD *)this + 86390) = 0;
          *((_DWORD *)this + 86391) = 0;
          *((_DWORD *)this + 86392) = 0;
          if ( nVal3d >= 4 )
          {
            *((_BYTE *)this + 8025) = 0;
            switch ( *((_DWORD *)this + 2011) )
            {
              case 0:
                v111 = &this->m_pOk + 3;
                sprintf(
                  (char *const)&this->m_pOk + 12,
                  "\\n    %s%s%s",
                  (const char *)dword_DCF53C,
                  (const char *)dword_DDB63C,
                  byte_DC6A3C);
                goto LABEL_234;
              case 1:
                v111 = &this->m_pOk + 3;
                sprintf(
                  (char *const)&this->m_pOk + 12,
                  "\\n    %s%s%s",
                  (const char *)dword_DCF53C,
                  (const char *)dword_DDB53C,
                  byte_DC6A3C);
                goto LABEL_234;
              case 2:
                v111 = &this->m_pOk + 3;
                sprintf(
                  (char *const)&this->m_pOk + 12,
                  "\\n    %s%s%s",
                  (const char *)dword_DCF53C,
                  (const char *)dword_DDB43C,
                  byte_DC6A3C);
                goto LABEL_234;
              case 3:
                v111 = &this->m_pOk + 3;
                sprintf(
                  (char *const)&this->m_pOk + 12,
                  "\\n    %s%s%s",
                  (const char *)dword_DCF53C,
                  (const char *)dword_DDB33C,
                  byte_DC6A3C);
                goto LABEL_234;
              case 4:
                v111 = &this->m_pOk + 3;
                sprintf(
                  (char *const)&this->m_pOk + 12,
                  "\\n    %s%s%s",
                  (const char *)dword_DCF53C,
                  (const char *)dword_DDB23C,
                  byte_DC6A3C);
LABEL_234:
                ((UICaption *)((char *)this + 669760))->SetEnable((int)v111, 0);
                ((UIRoleSelect *)((char *)this + 669304))->SetByte(1);
                break;
              default:
                goto LABEL_235;
            }
            goto LABEL_235;
          }
        }
        nValf = 48 * nVal3d;
        while ( !((CCBStageRole *)(__int64)(*(float *)(v65 + nValf + 24) * 100.0))->CheckActionValid() )
        {
          if ( ((CCBStageRole *)(__int64)(*(float *)(nValf + *((_DWORD *)this + 2012) + 28) * 100.0))->CheckActionValid() )
          {
            ++dword_17AD5C8[3 * nVal3d];
            goto LABEL_124;
          }
          if ( ((CCBStageRole *)(__int64)(*(float *)(nValf + *((_DWORD *)this + 2012) + 32) * 100.0))->CheckActionValid() )
          {
            ++dword_17AD5CC[3 * nVal3d];
            goto LABEL_124;
          }
LABEL_125:
          v65 = *((_DWORD *)this + 2012);
          if ( v64 >= *(_DWORD *)(v65 + 12) )
            goto LABEL_126;
        }
        ++*(_DWORD *)&g_CCBProtectData[12 * nVal3d];
LABEL_124:
        ++v64;
        goto LABEL_125;
      }
LABEL_235:
      if ( ((PropUI *)*((PropUI **)this + 2005))->CheckMode(1u) )
      {
        *((_DWORD *)&this->m_pOk + 1) = 0;
        if ( *((int *)this + *((_DWORD *)this + 82012) + 86389) > 0 )
        {
          do
          {
            v112 = 99 * *((_DWORD *)this + 82012);
            *((_BYTE *)this
            + 808 * v112
            + 808 * *((_DWORD *)this + 202 * *((_DWORD *)&this->m_pOk + 1) + 202 * v112 + 2214)
            + 8852) = ((UIScenePanel *)*((UIScenePanel **)this + 2005))->ValidateIndex(*((_DWORD *)&this->m_pOk + 1));
            v113 = *((_DWORD *)this + 82012);
            *((_BYTE *)this
            + 40400 * v113
            + 808 * *((_DWORD *)this + 19998 * v113 + 202 * *((_DWORD *)&this->m_pOk + 1) + 2214)
            + 508468) = ((UIScenePanel *)*((UIScenePanel **)this + 2005))->ValidateIndex(*((_DWORD *)&this->m_pOk + 1));
            *((_DWORD *)this + 19998 * *((_DWORD *)this + 82012) + 202 * *((_DWORD *)&this->m_pOk + 1) + 2214) = -1;
            v114 = *((_DWORD *)&this->m_pOk + 1) + 1;
            *((_DWORD *)&this->m_pOk + 1) = v114;
          }
          while ( v114 < *((_DWORD *)this + *((_DWORD *)this + 82012) + 86389) );
        }
      }
      *((_BYTE *)this + 8026) = 0;
    }
    return 1;
  }
  if ( nVal != 1001 )
    return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
  switch ( nVal2 )
  {
    case 10492673:
      if ( *((_BYTE *)this + 2500) )
      {
        v115 = unk_5DFF94;
      }
      else
      {
        *((_DWORD *)this + 628) = 0;
        *((_BYTE *)this + 2500) = 0;
        (**((void ( ***)(char *, _DWORD))this + 932))((char *)this + 3728, 0);
        (**((void ( ***)(char *, _DWORD))this + 994))((char *)this + 3976, 0);
        (**((void ( ***)(CCBProtectWindow *, _DWORD))this + 1056))(this + 24, 0);
        (**((void ( ***)(char *, _DWORD))this + 1118))((char *)this + 4472, 0);
        (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
        (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
        (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
        (**((void ( ***)(char *, _DWORD))this + 1374))((char *)this + 5496, 0);
        (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
        (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
        (**((void ( ***)(char *, _DWORD))this + 1564))((char *)this + 6256, 0);
        (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
        (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
        (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, 0);
        (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
        (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
        (**((void ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, 0);
        *((_DWORD *)this + 952) = 0;
        *((_BYTE *)this + 3796) = 0;
        *((_DWORD *)this + 1014) = 0;
        *((_BYTE *)this + 4044) = 0;
        *((_DWORD *)this + 1076) = 0;
        *((_BYTE *)this + 4292) = 0;
        *((_DWORD *)this + 1138) = 0;
        *((_BYTE *)this + 4540) = 0;
        ((CUtil *)*((CUtil **)this + 2002))->Update(3.0f);
        v115 = unk_5DFF88;
      }
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v115, 1);
      return 1;
    case 10492674:
      if ( *((_BYTE *)this + 2500) )
        goto LABEL_46;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      (**((void ( ***)(char *, _DWORD))this + 932))((char *)this + 3728, 0);
      (**((void ( ***)(char *, _DWORD))this + 994))((char *)this + 3976, 0);
      (**((void ( ***)(CCBProtectWindow *, _DWORD))this + 1056))(this + 24, 0);
      (**((void ( ***)(char *, _DWORD))this + 1118))((char *)this + 4472, 0);
      (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
      (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
      (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
      (**((void ( ***)(char *, _DWORD))this + 1374))((char *)this + 5496, 0);
      (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
      (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
      (**((void ( ***)(char *, _DWORD))this + 1564))((char *)this + 6256, 0);
      (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
      (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
      (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, 0);
      (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
      (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
      (**((void ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, 0);
      v7 = 0;
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      v8 = *((_DWORD *)this + 82011);
      nVal2a = 0;
      nVala = 0;
      *((_DWORD *)this + v8 + 86389) = 0;
      if ( *((int *)this + v8 + 2007) > 0 )
      {
        v9 = (char *)this + 79992 * v8 + 8852;
        do
        {
          v9[1] = 0;
          if ( !*v9 )
            ++nVala;
          ++v7;
          v9 += 808;
        }
        while ( v7 < *((_DWORD *)this + v8 + 2007) );
      }
      v10 = *((_DWORD *)this + 2012);
      nVal3a = 0;
      Block = *(void **)(v10 + 16);
      Block = (char *)Block + rand() % (*(_DWORD *)(v10 + 20) - (int)Block);
      if ( (int)Block <= 0 )
        goto LABEL_32;
      break;
    case 10492675:
      v20 = (void ( ***)(char *, int))((char *)this + 3728);
      if ( *((_BYTE *)this + 2500) )
      {
        (**v20)((char *)this + 3728, 1);
        v21 = (char *)this + 3976;
        (**((void ( ***)(char *, int))this + 994))((char *)this + 3976, 1);
        nVal2b = this + 24;
        (**((void ( ***)(int))this + 1056))(1);
        nValc = (char *)this + 4472;
        (**((void ( ***)(int))this + 1118))(1);
      }
      else
      {
        (**v20)((char *)this + 3728, 0);
        v21 = (char *)this + 3976;
        (**((void ( ***)(char *, _DWORD))this + 994))((char *)this + 3976, 0);
        nVal2b = this + 24;
        (**((void ( ***)(_DWORD))this + 1056))(0);
        nValc = (char *)this + 4472;
        (**((void ( ***)(_DWORD))this + 1118))(0);
        (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
        (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
        (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
        (**((void ( ***)(char *, _DWORD))this + 1374))((char *)this + 5496, 0);
        (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
        (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
        (**((void ( ***)(char *, _DWORD))this + 1564))((char *)this + 6256, 0);
        (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
        (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
        (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, 0);
        (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
        (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
        (**((void ( ***)(_DWORD))this + 1940))(0);
      }
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)v21 + 20) = 0;
      v21[68] = 0;
      nVal2b->m_pWPXFace = 0;
      LOBYTE(nVal2b->m_pbktex) = 0;
      *((_DWORD *)nValc + 20) = 0;
      nValc[68] = 0;
      goto LABEL_59;
    case 10492676:
      if ( *((_BYTE *)this + 2500) )
        goto LABEL_46;
      if ( *((int *)this + 2011) >= 4 || ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom <= 0 )
      {
        sprintf(
          (char *const)&this->m_pOk + 12,
          "\\n        %s: %d, %s",
          (const char *)dword_DC783C,
          ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom,
          (const char *)dword_DD373C);
        ((UICaption *)((char *)this + 671128))->SetEnable((int)(&this->m_pOk + 3), 0);
        ((UIRoleSelect *)((char *)this + 670672))->SetByte(1);
        v117 = unk_5DFF90;
        v22 = CScreenMode::GetInstance();
        ((CScreenMode *)v22)->AudioSetPosition(v117, 1);
        return 1;
      }
      else
      {
        *((_BYTE *)this + 8026) = 1;
        *((_DWORD *)this + 628) = 0;
        *((_BYTE *)this + 2500) = 0;
        (**((void ( ***)(char *, _DWORD))this + 932))((char *)this + 3728, 0);
        (**((void ( ***)(char *, _DWORD))this + 994))((char *)this + 3976, 0);
        (**((void ( ***)(CCBProtectWindow *, _DWORD))this + 1056))(this + 24, 0);
        (**((void ( ***)(char *, _DWORD))this + 1118))((char *)this + 4472, 0);
        (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
        (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
        (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
        (**((void ( ***)(char *, _DWORD))this + 1374))((char *)this + 5496, 0);
        (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
        (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
        (**((void ( ***)(char *, _DWORD))this + 1564))((char *)this + 6256, 0);
        (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
        (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
        (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, 0);
        (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
        (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
        (**((void ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, 0);
        *((_DWORD *)this + 952) = 0;
        *((_BYTE *)this + 3796) = 0;
        *((_DWORD *)this + 1014) = 0;
        *((_BYTE *)this + 4044) = 0;
        *((_DWORD *)this + 1076) = 0;
        *((_BYTE *)this + 4292) = 0;
        *((_DWORD *)this + 1138) = 0;
        *((_BYTE *)this + 4540) = 0;
        ((CUtil *)*((CUtil **)this + 2002))->Update(1.0f);
LABEL_59:
        v121 = unk_5DFF88;
        v51 = CScreenMode::GetInstance();
        ((CScreenMode *)v51)->AudioSetPosition(v121, 1);
        return 1;
      }
    case 10492677:
      if ( *((_BYTE *)this + 2500) )
      {
LABEL_46:
        v118 = unk_5DFF94;
        v23 = CScreenMode::GetInstance();
        ((CScreenMode *)v23)->AudioSetPosition(v118, 1);
        return 1;
      }
      else
      {
        ((CUtil *)*((CUtil **)this + 2002))->Update(5.0f);
        ((PalScriptMgr *)v24)->Destroy();
        v119 = unk_5DFF88;
        v25 = CScreenMode::GetInstance();
        ((CScreenMode *)v25)->AudioSetPosition(v119, 1);
        v26 = *((_DWORD *)this + 82005);
        v27 = (const void *)*((_DWORD *)this + 2012);
        *((_DWORD *)this + 126861) = *((_DWORD *)this + 2011);
        *((_DWORD *)this + 126859) = v26;
        v28 = *((_DWORD *)this + 82009);
        v29 = *((_DWORD *)this + 82008);
        nVal3b = 4;
        qmemcpy((char *)this + 507448, v27, 0xDCu);
        v30 = *((_DWORD *)this + 82011);
        *((_DWORD *)this + 167322) = v28;
        *((_DWORD *)this + 167324) = v30;
        *((_DWORD *)this + 167323) = *((_DWORD *)this + 82010);
        *((_DWORD *)this + 167321) = v29;
        v31 = (char *)this + 669268;
        nVald = (char *)this + 507668;
        nVal2c = (char *)this + 8052;
        do
        {
          v31 += 4;
          v32 = 808 * *(_DWORD *)(*((_DWORD *)this + 2012) + 12);
          qmemcpy(nVald, nVal2c, 4 * (v32 >> 2));
          v34 = &nVal2c[4 * (v32 >> 2)];
          v33 = &nVald[4 * (v32 >> 2)];
          v35 = v32;
          v36 = nVal3b;
          qmemcpy(v33, v34, v35 & 3);
          *((_DWORD *)v31 - 1) = *((_DWORD *)v31 - 165311);
          nVal2c += 79992;
          nVald += 40400;
          --nVal3b;
        }
        while ( v36 != 1 );
        return 1;
      }
    case 10492680:
      if ( !*((_DWORD *)this + 2012) )
        return 1;
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      v37 = *((_DWORD *)this + 82005);
      v38 = (const void *)*((_DWORD *)this + 2012);
      *((_DWORD *)this + 126861) = *((_DWORD *)this + 2011);
      *((_DWORD *)this + 126859) = v37;
      v39 = *((_DWORD *)this + 82009);
      v40 = *((_DWORD *)this + 82008);
      qmemcpy((char *)this + 507448, v38, 0xDCu);
      v41 = *((_DWORD *)this + 82011);
      *((_DWORD *)this + 167322) = v39;
      *((_DWORD *)this + 167324) = v41;
      *((_DWORD *)this + 167323) = *((_DWORD *)this + 82010);
      *((_DWORD *)this + 167321) = v40;
      v42 = (char *)this + 669268;
      nVale = (char *)this + 507668;
      nVal2d = (char *)this + 8052;
      nVal3c = 4;
      do
      {
        v42 += 4;
        v43 = 808 * *(_DWORD *)(*((_DWORD *)this + 2012) + 12);
        qmemcpy(nVale, nVal2d, 4 * (v43 >> 2));
        v45 = &nVal2d[4 * (v43 >> 2)];
        v44 = &nVale[4 * (v43 >> 2)];
        v46 = v43;
        v47 = nVal3c;
        qmemcpy(v44, v45, v46 & 3);
        *((_DWORD *)v42 - 1) = *((_DWORD *)v42 - 165311);
        nVal2d += 79992;
        nVale += 40400;
        --nVal3c;
      }
      while ( v47 != 1 );
      ((CUtil *)*((CUtil **)this + 2002))->Update(5.0f);
      v120 = unk_5DFF88;
      v48 = CScreenMode::GetInstance();
      ((CScreenMode *)v48)->AudioSetPosition(v120, 1);
      return 1;
    case 10492681:
      (**((void ( ***)(char *, _DWORD))this + 1374))((char *)this + 5496, 0);
      (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
      (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
      (**((void ( ***)(char *, _DWORD))this + 1564))((char *)this + 6256, 0);
      (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
      (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
      (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, 0);
      (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
      (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
      (**((void ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, 0);
      v49 = (char *)this + 4736;
      if ( *((_BYTE *)this + 3796) )
      {
        (**(void ( ***)(char *, int))v49)(v49, 1);
        (**((void ( ***)(char *, int))this + 1246))((char *)this + 4984, 1);
        (**((void ( ***)(char *, int))this + 1308))((char *)this + 5232, 1);
        *((_DWORD *)this + 1014) = 0;
        *((_BYTE *)this + 4044) = 0;
        *((_DWORD *)this + 1076) = 0;
        *((_BYTE *)this + 4292) = 0;
        *((_DWORD *)this + 1138) = 0;
        *((_BYTE *)this + 4540) = 0;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))v49)(v49, 0);
        (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
        (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
      }
      goto LABEL_59;
    case 10492688:
      (**((void ( ***)(char *, _DWORD))this + 1564))((char *)this + 6256, 0);
      (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
      (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
      (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
      (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
      (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
      (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, 0);
      (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
      (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
      (**((void ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, 0);
      v50 = (char *)this + 5496;
      if ( *((_BYTE *)this + 4044) )
      {
        (**(void ( ***)(char *, int))v50)(v50, 1);
        (**((void ( ***)(char *, int))this + 1436))((char *)this + 5744, 1);
        (**((void ( ***)(char *, int))this + 1498))((char *)this + 5992, 1);
        *((_DWORD *)this + 952) = 0;
        *((_BYTE *)this + 3796) = 0;
        *((_DWORD *)this + 1076) = 0;
        *((_BYTE *)this + 4292) = 0;
        *((_DWORD *)this + 1138) = 0;
        *((_BYTE *)this + 4540) = 0;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))v50)(v50, 0);
        (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
        (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
      }
      goto LABEL_59;
    case 10492689:
      (**((void ( ***)(char *, _DWORD))this + 1374))((char *)this + 5496, 0);
      (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
      (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
      (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
      (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
      (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
      (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, 0);
      (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
      (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
      (**((void ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, 0);
      v52 = (char *)this + 6256;
      if ( *((_BYTE *)this + 4292) )
      {
        (**(void ( ***)(char *, int))v52)(v52, 1);
        (**((void ( ***)(char *, int))this + 1626))((char *)this + 6504, 1);
        (**((void ( ***)(char *, int))this + 1688))((char *)this + 6752, 1);
        *((_DWORD *)this + 952) = 0;
        *((_BYTE *)this + 3796) = 0;
        *((_DWORD *)this + 1014) = 0;
        *((_BYTE *)this + 4044) = 0;
        *((_DWORD *)this + 1138) = 0;
        *((_BYTE *)this + 4540) = 0;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))v52)(v52, 0);
        (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
        (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
      }
      goto LABEL_59;
    case 10492690:
      (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
      (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
      (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
      (**((void ( ***)(char *, _DWORD))this + 1374))((char *)this + 5496, 0);
      (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
      (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
      (**((void ( ***)(char *, _DWORD))this + 1564))((char *)this + 6256, 0);
      (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
      (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
      v53 = (void ( **)(int))*((_DWORD *)this + 1754);
      if ( *((_BYTE *)this + 4540) )
      {
        (*v53)(1);
        (**((void ( ***)(char *, int))this + 1816))((char *)this + 7264, 1);
        (**((void ( ***)(char *, int))this + 1878))((char *)this + 7512, 1);
        (**((void ( ***)(char *, int))this + 1940))((char *)this + 7760, 1);
        *((_DWORD *)this + 952) = 0;
        *((_BYTE *)this + 3796) = 0;
        *((_DWORD *)this + 1014) = 0;
        *((_BYTE *)this + 4044) = 0;
        *((_DWORD *)this + 1076) = 0;
        *((_BYTE *)this + 4292) = 0;
      }
      else
      {
        (*v53)(0);
        (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
        (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
        (**((void ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, 0);
      }
      goto LABEL_59;
    case 10492691:
      *((_BYTE *)this + 5052) = 0;
      *((_DWORD *)this + 1266) = 0;
      *((_DWORD *)this + 1328) = 0;
      *((_BYTE *)this + 5300) = 0;
      *((_DWORD *)this + 82008) = 0;
      if ( !*((_BYTE *)this + 4804) )
      {
        *((_DWORD *)this + 82008) = 1;
        *((_DWORD *)this + 1266) = 1;
        *((_BYTE *)this + 5052) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      v54 = &this->m_pOk + 3;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDA3C, dword_DCDE3C);
      goto LABEL_104;
    case 10492692:
      *((_BYTE *)this + 4804) = 0;
      *((_DWORD *)this + 1204) = 0;
      *((_DWORD *)this + 1328) = 0;
      *((_BYTE *)this + 5300) = 0;
      *((_DWORD *)this + 82008) = 1;
      if ( !*((_BYTE *)this + 5052) )
      {
        *((_DWORD *)this + 82008) = 1;
        *((_DWORD *)this + 1266) = 1;
        *((_BYTE *)this + 5052) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      v55 = &this->m_pOk + 3;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDA3C, dword_DCDF3C);
      goto LABEL_91;
    case 10492693:
      *((_BYTE *)this + 4804) = 0;
      *((_DWORD *)this + 1204) = 0;
      *((_DWORD *)this + 1266) = 0;
      *((_BYTE *)this + 5052) = 0;
      *((_DWORD *)this + 82008) = 2;
      if ( !*((_BYTE *)this + 5300) )
      {
        *((_DWORD *)this + 82008) = 1;
        *((_DWORD *)this + 1266) = 1;
        *((_BYTE *)this + 5052) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      v56 = &this->m_pOk + 3;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDA3C, dword_DCE03C);
      goto LABEL_109;
    case 10492694:
      *((_BYTE *)this + 5812) = 0;
      *((_DWORD *)this + 1456) = 0;
      *((_DWORD *)this + 1518) = 0;
      *((_BYTE *)this + 6060) = 0;
      *((_DWORD *)this + 82009) = 0;
      if ( !*((_BYTE *)this + 5564) )
      {
        *((_DWORD *)this + 82009) = 1;
        *((_DWORD *)this + 1456) = 1;
        *((_BYTE *)this + 5812) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      v54 = &this->m_pOk + 3;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDB3C, dword_DCE13C);
      goto LABEL_104;
    case 10492695:
      *((_BYTE *)this + 5564) = 0;
      *((_DWORD *)this + 1394) = 0;
      *((_DWORD *)this + 1518) = 0;
      *((_BYTE *)this + 6060) = 0;
      *((_DWORD *)this + 82009) = 1;
      if ( !*((_BYTE *)this + 5812) )
      {
        *((_DWORD *)this + 82009) = 1;
        *((_DWORD *)this + 1456) = 1;
        *((_BYTE *)this + 5812) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      v55 = &this->m_pOk + 3;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDB3C, dword_DCE23C);
      goto LABEL_91;
    case 10492696:
      *((_BYTE *)this + 5564) = 0;
      *((_DWORD *)this + 1394) = 0;
      *((_DWORD *)this + 1456) = 0;
      *((_BYTE *)this + 5812) = 0;
      *((_DWORD *)this + 82009) = 2;
      if ( !*((_BYTE *)this + 6060) )
      {
        *((_DWORD *)this + 82009) = 1;
        *((_DWORD *)this + 1456) = 1;
        *((_BYTE *)this + 5812) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      v56 = &this->m_pOk + 3;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDB3C, dword_DCE33C);
      goto LABEL_109;
    case 10492697:
      *((_BYTE *)this + 6572) = 0;
      *((_DWORD *)this + 1646) = 0;
      *((_DWORD *)this + 1708) = 0;
      *((_BYTE *)this + 6820) = 0;
      *((_DWORD *)this + 82010) = 0;
      if ( !*((_BYTE *)this + 6324) )
      {
        *((_DWORD *)this + 82010) = 1;
        *((_DWORD *)this + 1646) = 1;
        *((_BYTE *)this + 6572) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      v54 = &this->m_pOk + 3;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDC3C, dword_DCE13C);
      goto LABEL_104;
    case 10492704:
      *((_BYTE *)this + 6324) = 0;
      *((_DWORD *)this + 1584) = 0;
      *((_DWORD *)this + 1708) = 0;
      *((_BYTE *)this + 6820) = 0;
      *((_DWORD *)this + 82010) = 1;
      if ( !*((_BYTE *)this + 6572) )
      {
        *((_DWORD *)this + 82010) = 1;
        *((_DWORD *)this + 1646) = 1;
        *((_BYTE *)this + 6572) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      v55 = &this->m_pOk + 3;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDC3C, dword_DCE23C);
LABEL_91:
      ((UICaption *)((char *)this + 671128))->SetEnable((int)v55, 0);
      ((UIRoleSelect *)((char *)this + 670672))->SetByte(1);
      v122 = unk_5DFF88;
      v57 = CScreenMode::GetInstance();
      ((CScreenMode *)v57)->AudioSetPosition(v122, 1);
      return 1;
    case 10492705:
      *((_BYTE *)this + 6324) = 0;
      *((_DWORD *)this + 1584) = 0;
      *((_DWORD *)this + 1646) = 0;
      *((_BYTE *)this + 6572) = 0;
      *((_DWORD *)this + 82010) = 2;
      if ( !*((_BYTE *)this + 6820) )
      {
        *((_DWORD *)this + 82010) = 1;
        *((_DWORD *)this + 1646) = 1;
        *((_BYTE *)this + 6572) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      v56 = &this->m_pOk + 3;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n            %s: %s", dword_DCDC3C, dword_DCE33C);
      goto LABEL_109;
    case 10492706:
      *((_BYTE *)this + 7332) = 0;
      *((_DWORD *)this + 1836) = 0;
      *((_DWORD *)this + 1898) = 0;
      *((_BYTE *)this + 7580) = 0;
      *((_DWORD *)this + 1960) = 0;
      *((_BYTE *)this + 7828) = 0;
      *((_DWORD *)this + 82011) = 1;
      if ( !*((_BYTE *)this + 7084) )
      {
        *((_DWORD *)this + 82011) = 0;
        *((_DWORD *)this + 1960) = 1;
        *((_BYTE *)this + 7828) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n        %s: %s", dword_DCDD3C, dword_DCE43C);
      ((UICaption *)((char *)this + 671128))->SetEnable((int)(&this->m_pOk + 3), 0);
      goto LABEL_105;
    case 10492707:
      *((_BYTE *)this + 7084) = 0;
      *((_DWORD *)this + 1774) = 0;
      *((_DWORD *)this + 1898) = 0;
      *((_BYTE *)this + 7580) = 0;
      *((_DWORD *)this + 1960) = 0;
      *((_BYTE *)this + 7828) = 0;
      *((_DWORD *)this + 82011) = 2;
      if ( !*((_BYTE *)this + 7332) )
      {
        *((_DWORD *)this + 82011) = 0;
        *((_DWORD *)this + 1960) = 1;
        *((_BYTE *)this + 7828) = 1;
      }
      ((CCBStageRole *)this)->DispatchUpdate(0);
      (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
      (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
      (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n        %s: %s", dword_DCDD3C, dword_DCE53C);
      ((UICaption *)((char *)this + 671128))->SetEnable((int)(&this->m_pOk + 3), 0);
      goto LABEL_110;
    case 10492708:
      *((_DWORD *)this + 1774) = 0;
      *((_BYTE *)this + 7084) = 0;
      *((_DWORD *)this + 1836) = 0;
      *((_BYTE *)this + 7332) = 0;
      *((_DWORD *)this + 1960) = 0;
      *((_BYTE *)this + 7828) = 0;
      *((_DWORD *)this + 82011) = 3;
      if ( !*((_BYTE *)this + 7580) )
      {
        *((_DWORD *)this + 82011) = 0;
        *((_DWORD *)this + 1960) = 1;
        *((_BYTE *)this + 7828) = 1;
      }
      (**((void ( ***)(char *, _DWORD))this + 932))((char *)this + 3728, 0);
      (**((void ( ***)(char *, _DWORD))this + 994))((char *)this + 3976, 0);
      (**((void ( ***)(CCBProtectWindow *, _DWORD))this + 1056))(this + 24, 0);
      (**((void ( ***)(char *, _DWORD))this + 1118))((char *)this + 4472, 0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      ((CCBStageRole *)this)->DispatchUpdateAll(0);
      ((CCBStageRole *)this)->DispatchUpdate(0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      v54 = &this->m_pOk + 3;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      sprintf((char *const)&this->m_pOk + 12, "\\n        %s: %s", dword_DCDD3C, dword_DCE63C);
LABEL_104:
      ((UICaption *)((char *)this + 671128))->SetEnable((int)v54, 0);
LABEL_105:
      ((UIRoleSelect *)((char *)this + 670672))->SetByte(1);
      v123 = unk_5DFF88;
      v58 = CScreenMode::GetInstance();
      ((CScreenMode *)v58)->AudioSetPosition(v123, 1);
      return 1;
    case 10492709:
      *((_DWORD *)this + 1774) = 0;
      *((_BYTE *)this + 7084) = 0;
      *((_DWORD *)this + 1836) = 0;
      *((_BYTE *)this + 7332) = 0;
      *((_DWORD *)this + 1898) = 0;
      *((_BYTE *)this + 7580) = 0;
      *((_DWORD *)this + 82011) = 0;
      if ( !*((_BYTE *)this + 7828) )
      {
        *((_DWORD *)this + 82011) = 0;
        *((_DWORD *)this + 1960) = 1;
        *((_BYTE *)this + 7828) = 1;
      }
      (**((void ( ***)(char *, _DWORD))this + 932))((char *)this + 3728, 0);
      (**((void ( ***)(char *, _DWORD))this + 994))((char *)this + 3976, 0);
      (**((void ( ***)(CCBProtectWindow *, _DWORD))this + 1056))(this + 24, 0);
      (**((void ( ***)(char *, _DWORD))this + 1118))((char *)this + 4472, 0);
      (**((void ( ***)(char *, _DWORD))this + 1184))((char *)this + 4736, 0);
      (**((void ( ***)(char *, _DWORD))this + 1246))((char *)this + 4984, 0);
      (**((void ( ***)(char *, _DWORD))this + 1308))((char *)this + 5232, 0);
      (**((void ( ***)(char *, _DWORD))this + 1374))((char *)this + 5496, 0);
      (**((void ( ***)(char *, _DWORD))this + 1436))((char *)this + 5744, 0);
      (**((void ( ***)(char *, _DWORD))this + 1498))((char *)this + 5992, 0);
      (**((void ( ***)(char *, _DWORD))this + 1564))((char *)this + 6256, 0);
      (**((void ( ***)(char *, _DWORD))this + 1626))((char *)this + 6504, 0);
      (**((void ( ***)(char *, _DWORD))this + 1688))((char *)this + 6752, 0);
      (**((void ( ***)(char *, _DWORD))this + 1754))((char *)this + 7016, 0);
      (**((void ( ***)(char *, _DWORD))this + 1816))((char *)this + 7264, 0);
      (**((void ( ***)(char *, _DWORD))this + 1878))((char *)this + 7512, 0);
      (**((void ( ***)(char *, _DWORD))this + 1940))((char *)this + 7760, 0);
      *((_DWORD *)this + 952) = 0;
      *((_BYTE *)this + 3796) = 0;
      *((_DWORD *)this + 1014) = 0;
      *((_BYTE *)this + 4044) = 0;
      *((_DWORD *)this + 1076) = 0;
      *((_BYTE *)this + 4292) = 0;
      *((_DWORD *)this + 1138) = 0;
      *((_BYTE *)this + 4540) = 0;
      *((_DWORD *)this + 628) = 0;
      *((_BYTE *)this + 2500) = 0;
      v56 = &this->m_pOk + 3;
      sprintf((char *const)&this->m_pOk + 12, "\\n        %s: %s", dword_DCDD3C, dword_DCE73C);
LABEL_109:
      ((UICaption *)((char *)this + 671128))->SetEnable((int)v56, 0);
LABEL_110:
      ((UIRoleSelect *)((char *)this + 670672))->SetByte(1);
      goto LABEL_59;
    default:
      return 1;
  }
  while ( nVala > 0 )
  {
    v11 = rand() % *((_DWORD *)this + v8 + 2007);
    if ( nVala <= (int)Block )
    {
      v13 = 0;
      if ( *((int *)this + v8 + 2007) > 0 )
      {
        v14 = (CCBProtectWindow *)((char *)this + 53328 * v8 + 26664 * v8 + 808 * nVal2a + 8856);
        v15 = (char *)this + 79992 * v8 + 8853;
        do
        {
          if ( !*(v15 - 1) && !*v15 && *(_DWORD *)(v15 - 801) )
          {
            *v15 = 1;
// [VFTABLE] v14->__vftable = v13;
            ++nVal2a;
            v14 = (CCBProtectWindow *)((char *)v14 + 808);
            ++*((_DWORD *)this + v8 + 86389);
          }
          v13 = (void *)((char *)v13 + 1);
          v15 += 808;
        }
        while ( (int)v13 < *((_DWORD *)this + v8 + 2007) );
      }
      break;
    }
    v12 = (char *)this + 79992 * v8 + 808 * v11;
    if ( !v12[8852] && !v12[8853] && *((_DWORD *)v12 + 2013) )
    {
      v12[8853] = 1;
      *((_DWORD *)this + 19998 * v8 + 202 * nVal2a++ + 2214) = v11;
      ++nVal3a;
      ++*((_DWORD *)this + v8 + 86389);
    }
    if ( nVal3a >= (int)Block )
      break;
  }
LABEL_32:
  *((_DWORD *)this + 85488) = nVal2a;
  if ( nVal2a > 0 )
  {
    v16 = (int *)((char *)this + 344356);
    nValb = (CCBProtectWindow *)((char *)this + 79992 * v8 + 8856);
    do
    {
// [VFTABLE] v124 = *((_DWORD *)this + 202 * ((int)nValb->__vftable + 99 * v8) + 2013);
      *(v16 - 400) = v124;
      *v16++ = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v124);
      v17 = nVal2a == 1;
      nValb = (CCBProtectWindow *)((char *)nValb + 808);
      --nVal2a;
    }
    while ( !v17 );
  }
  ((PropUI *)*((PropUI **)this + 2005))->SetPendingMessage(1, 1, *(_DWORD *)(*((_DWORD *)this + 2012) + 8));
  ((PropUI *)*((PropUI **)this + 2005))->UpdateItemList((char *)this + 328052);
  v18 = (CUtil *)*((_DWORD *)this + 2002);
  *((_DWORD *)this + 82012) = v8;
  ((CUtil *)v18)->Update(4.0f);
  v116 = unk_5DFF88;
  v19 = CScreenMode::GetInstance();
  ((CScreenMode *)v19)->AudioSetPosition(v116, 1);
  return 1;
}
