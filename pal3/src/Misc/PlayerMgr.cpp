#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PlayerMgr.h"

// Forward declarations for unnamed functions
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
CHAR * sub_458F70(LPCSTR lpString, int a2, LPSTR lpString1); // from annotations

// Unnamed globals (extern)
extern CHAR asc_5B74B4[2];
extern char asc_5B74B8[];
extern char byte_5967B0[3];
extern CHAR byte_DCEB3C[256];
extern int dword_56B3C8[];
extern int dword_56B4DC[];
extern int dword_56B4F0[];
extern int dword_56B540[];
extern int dword_56B554[];
extern int dword_56B568[];
extern int dword_56B57C[];
extern int dword_56B590[];
extern int dword_56B5A4[];
extern int dword_56B5B8[];
extern int dword_DC353C;
extern int dword_DC363C;
extern int dword_DC373C;
extern int dword_DD4A3C;
extern int dword_DDA93C;
extern int dword_DDAA3C;
extern const char * off_56B504;
extern const char * off_56B518;
extern const char * off_56B52C;
extern RoleSystem stru_C059A0;

// 0x0045AE60
void PlayerMgr::ctor()
{
  void *v2; // eax
  UIListBox *v3; // [esp+0x0] [ebp-0x20]
  int v4; // [esp+0x4] [ebp-0x1C]

  v2 = (void *)*((_DWORD *)&this->pNGHVarianceParticle + 1266);
  if ( v2 )
  {
    operator delete(v2);
    *((_DWORD *)&this->pNGHVarianceParticle + 1266) = 0;
  }
  if ( *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) )
  {
    operator delete(*((void **)&(&this->pNGHVarianceParticle)[23] + 9));
    *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) = 0;
  }
  if ( *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[232] )
  {
    operator delete(*(void **)&this->m_RoleTask.m_taskFile.m_token[232]);
    *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[232] = 0;
  }
  if ( *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 10) )
  {
    operator delete(*((void **)&(&this->pNGHVarianceParticle)[23] + 10));
    *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 10) = 0;
  }
  this->m_RoleTask.m_taskFile.m_token[260] = 0;
  *((_BYTE *)&(&this->pNGHVarianceParticle)[78] + 28) = 0;
  ((CCBRoleState *)this)->Destroy(v3, v4);
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 4197))->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)(&this->pNGHVarianceParticle + 4103))->Destroy2();
  ((UICaption *)(&this->pNGHVarianceParticle + 4017))->Destroy2();
  ((UICaption *)(&(&this->pNGHVarianceParticle)[70] + 11))->Destroy2();
  ((UICaption *)(&this->pNGHVarianceParticle + 3845))->Destroy2();
  ((UICaption *)(&(&this->pNGHVarianceParticle)[67] + 7))->Destroy2();
  ((UICaption *)(&this->pNGHVarianceParticle + 3669))->Destroy2();
  ((UICaption *)(&this->pNGHVarianceParticle + 3579))->Destroy2();
  ((UICaption *)(&this->pNGHVarianceParticle + 3489))->Destroy2();
  ((UICaption *)(&this->pNGHVarianceParticle + 3398))->Destroy2();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 3356))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&(&this->pNGHVarianceParticle)[59] + 10))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 3272))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 3230))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&(&this->pNGHVarianceParticle)[57])->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)(&this->pNGHVarianceParticle + 3099))->Destroy2();
  ((UICaption *)(&this->pNGHVarianceParticle + 3013))->Destroy2();
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->DeleteRow();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 2661))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 2623))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 2091))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 2049))->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)(&(&this->pNGHVarianceParticle)[35] + 3))->Destroy2();
  ((UICaption *)(&this->pNGHVarianceParticle + 1877))->Destroy2();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 1835))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&(&this->pNGHVarianceParticle)[32] + 5))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 1759))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->pNGHVarianceParticle + 1721))->UIFrameWnd::_UIFrameWnd();
  ((UIRoleDialog *)(&this->pNGHVarianceParticle + 1379))->_UIRoleDialog();
  ((PalScript *)(&this->pNGHVarianceParticle + 1302))->PalScript_Init();
  ((PalScript *)(&this->dwWeaponWU + 6028))->ctor();
  ((UIFrameWnd *)(&this->dwWeaponWU + 5990))->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)(&this->dwWeaponWU + 5969))->ctor();
  ((UIFrameWnd *)(&this->dwWeaponWU + 5931))->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0045B7A0
unsigned __int8 PlayerMgr::LoadState(const void *arg0)
{
  char *v3; // ebx
  void *v4; // edi
  unsigned int v5; // edx
  int v6; // eax
  int **v7; // edi
  int v8; // ebx
  int *v9; // eax
  int v10; // ecx
  int *v11; // eax
  unsigned __int8 result; // al
  int v13; // [esp+0x10] [ebp-0x10]
  int p_DWORD; // [esp+0x14] [ebp-0xC] BYREF
  int v15; // [esp+0x18] [ebp-0x8]
  int *v16; // [esp+0x1C] [ebp-0x4]
  const void *arg0a; // [esp+0x24] [ebp+0x4]

  v3 = &this->m_RoleTask.m_taskFile.m_token[268];
  memset(&this->m_RoleTask.m_taskFile.m_token[268], 0, 0x4460u);
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->ClearAll();
  qmemcpy(v3, arg0, 0x4460u);
  if ( *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 10) )
  {
    operator delete(*((void **)&(&this->pNGHVarianceParticle)[23] + 10));
    *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 10) = 0;
  }
  v4 = operator new(4 * *(&this->dwWeaponWU + 3264));
  v5 = 4 * *(&this->dwWeaponWU + 3264);
  *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 10) = v4;
  memset(v4, 0, v5);
  v13 = 0;
  v6 = *(&this->dwWeaponWU + 3264);
  p_DWORD = 0xFFFF;
  v15 = 0;
  v16 = 0;
  if ( v6 > 0 )
  {
    v7 = (int **)(&this->dwWeaponWU + 3666);
    arg0a = (const void *)(-15880 - (_DWORD)this);
    do
    {
      sprintf(&this->m_RoleTask.m_TaskData[4], byte_5967B0, *v7 + 1);
      v8 = ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->SetItemOffset(&this->m_RoleTask.m_TaskData[4], 0);
      sprintf(&this->m_RoleTask.m_TaskData[4], &dir[20], (*v7)[152]);
      ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->SetMouseMoveSel(1, v8, &this->m_RoleTask.m_TaskData[4], 0);
      sprintf(&this->m_RoleTask.m_TaskData[4], &dir[20], 0);
      ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->SetMouseMoveSel(2, v8, &this->m_RoleTask.m_TaskData[4], 0);
      v9 = *v7;
      v10 = **v7;
      v15 = 1;
      p_DWORD = v10;
      v16 = v9;
      v11 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD);
      if ( v11 )
        *(int **)((char *)v7 + (_DWORD)arg0a + *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 10)) = (int *)(99 - v11[1]);
      else
        *(int **)((char *)v7 + (_DWORD)arg0a + *((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 10)) = (int *)99;
      ++v7;
      ++v13;
    }
    while ( v13 < *(&this->dwWeaponWU + 3264) );
  }
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->GetItem();
  result = this->m_RoleTask.m_taskFile.m_token[269];
  if ( !result )
  {
    sub_445E50((int)(&this->pNGHVarianceParticle + 3489));
    result = (unsigned __int8)((PalScript *)(&this->pNGHVarianceParticle + 3489))->OpenScript("UI\\Assistant\\Communal\\UnDicker.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  }
  *((_BYTE *)&(&this->pNGHVarianceParticle)[78] + 28) = 1;
  return result;
}

// 0x0045B990
int PlayerMgr::InitCombatUI(int nVal)
{
  int *v3; // edi
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // edx
  char *v18; // ebp
  int v19; // ecx
  int v20; // eax
  char *v21; // ebp
  CParticleEffect *v22; // eax
  int v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // edx
  int v27; // eax
  int v28; // ecx
  int v29; // ecx
  int v30; // eax
  int v31; // eax
  int *v32; // ecx
  int *v33; // ecx
  int *v34; // ecx
  int *v35; // ecx
  int v36; // eax
  int v37; // edx
  int v38; // edx
  int v39; // edx
  CParticleEffect **v40; // ebp
  int v41; // eax
  int v42; // edx
  int v43; // ecx
  int v44; // edx
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // edx
  int v49; // edx
  int v50; // ecx
  int v51; // eax
  int v52; // ecx
  char *v53; // eax
  unsigned __int8 v54; // dl
  bool v55; // cf
  int v56; // eax
  int v57; // eax
  int v58; // eax
  int v59; // edx
  int v60; // eax
  int v61; // eax
  int v62; // edx
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // eax
  int v67; // edx
  int v68; // eax
  int v69; // edx
  int v70; // eax
  int v71; // eax
  int v72; // eax
  int result; // eax
  char *v74; // [esp+0x552] [ebp-0x100]
  char *v75; // [esp+0x552] [ebp-0x100]
  float v76; // [esp+0x556] [ebp-FCh]
  _DWORD v77[4]; // [esp+0x566] [ebp-ECh] BYREF
  unsigned __int8 v78; // [esp+0x579] [ebp-D9h]
  char *v79; // [esp+0x57A] [ebp-D8h]
  int v80; // [esp+0x57E] [ebp-D4h] BYREF
  int v81; // [esp+0x582] [ebp-D0h]
  int v82; // [esp+0x586] [ebp-CCh]
  int v83; // [esp+0x58A] [ebp-C8h]
  _DWORD v84[2]; // [esp+0x58E] [ebp-C4h] BYREF
  int v85; // [esp+0x596] [ebp-BCh]
  int v86; // [esp+0x59A] [ebp-B8h]
  char *v87; // [esp+0x59E] [ebp-B4h]
  int v88; // [esp+0x5A2] [ebp-B0h] BYREF
  int v89; // [esp+0x5A6] [ebp-ACh]
  int v90; // [esp+0x5AA] [ebp-A8h]
  int v91; // [esp+0x5AE] [ebp-A4h]
  _DWORD v92[4]; // [esp+0x5B2] [ebp-A0h] BYREF
  gbVec3D pDir; // [esp+0x5C2] [ebp-0x90] BYREF
  int v94; // [esp+0x5CE] [ebp-0x84]
  _DWORD v95[4]; // [esp+0x5D2] [ebp-0x80] BYREF
  gbVec3D pPos; // [esp+0x5E2] [ebp-0x70] BYREF
  int v97; // [esp+0x5EE] [ebp-0x64]
  _DWORD v98[4]; // [esp+0x5F2] [ebp-0x60] BYREF
  _DWORD v99[4]; // [esp+0x602] [ebp-0x50] BYREF
  _DWORD v100[4]; // [esp+0x612] [ebp-0x40] BYREF
  _DWORD v101[4]; // [esp+0x622] [ebp-0x30] BYREF
  _DWORD v102[4]; // [esp+0x632] [ebp-0x20] BYREF
  int v103[4]; // [esp+0x642] [ebp-0x10] BYREF

  v3 = &this->dwWeaponWU + 5927;
  *(&this->dwWeaponWU + 5928) = 0;
  *(&this->dwWeaponWU + 5927) = 0;
  *(&this->dwWeaponWU + 5929) = 800;
  *(&this->dwWeaponWU + 5930) = 600;
  ((UIListBox *)this)->SetSelTexture(-1, *(&this->dwWeaponWU + 5927), *(&this->dwWeaponWU + 5928), *(&this->dwWeaponWU + 5929), *(&this->dwWeaponWU + 5930), 0);
  *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) = nVal;
  *(&this->dwWeaponWU + 5928) = 0;
  *v3 = 0;
  v4 = *(_DWORD *)this->m_RoleTask.m_TaskData;
  v5 = *(&this->dwWeaponWU + 5928);
  v95[1] = 22;
  v95[0] = 266;
  *(&this->dwWeaponWU + 5930) = v5 + v4;
  *(&this->dwWeaponWU + 5929) = *v3 + *(&this->m_nHuaYingMode + 12);
  v6 = *(&this->dwWeaponWU + 5990);
  v95[2] = 482;
  v95[3] = 150;
  (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(v6 + 16))(
    &this->dwWeaponWU + 5990,
    257,
    v95,
    this);
  ((UIStatic *)(&this->dwWeaponWU + 5990))->CreateFromTemplate();
  v7 = *(&this->dwWeaponWU + 5969);
  v92[1] = 564;
  v92[0] = 0;
  v92[2] = 800;
  v92[3] = 599;
  (*(void ( **)(int *, int, _DWORD *, char *, _DWORD, PlayerMgr *))(v7 + 28))(
    &this->dwWeaponWU + 5969,
    257,
    v92,
    "UI\\Flex\\framebar.tga",
    0,
    this);
  ((CScreenMode *)(&this->dwWeaponWU + 5969))->SetPosition(30,   35);
  v100[1] = 0;
  v100[0] = 0;
  v100[2] = 206;
  v100[3] = 600;
  (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU + 5931) + 16))(
    &this->dwWeaponWU + 5931,
    257,
    v100,
    this);
  ((UIStatic *)(&this->dwWeaponWU + 5931))->CreateFromTemplate();
  v8 = *((_DWORD *)&this->pNGHVarianceParticle + 2091);
  v98[1] = 32;
  v98[0] = 454;
  v98[2] = 790;
  v98[3] = 425;
  (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(v8 + 16))(
    &this->pNGHVarianceParticle + 2091,
    257,
    v98,
    this);
  ((UIStatic *)(&this->pNGHVarianceParticle + 2091))->CreateFromTemplate();
  v9 = *((_DWORD *)&this->pNGHVarianceParticle + 2661);
  v102[1] = 50;
  v102[0] = 476;
  v102[2] = 782;
  v102[3] = 82;
  (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(v9 + 16))(
    &this->pNGHVarianceParticle + 2661,
    294,
    v102,
    this);
  ((UIScene *)(&this->pNGHVarianceParticle + 2661))->SetShow(0);
  sprintf(
    &this->m_RoleTask.m_TaskData[4],
    "%s                %s   %s",
    (const char *)dword_DC353C,
    (const char *)dword_DC363C,
    (const char *)dword_DC373C);
  ((UICaption *)(&this->pNGHVarianceParticle + 2661))->SetEnable((int)&this->m_RoleTask.m_TaskData[4], 0);
  *((_DWORD *)&this->pNGHVarianceParticle + 3002) = 79;
  *((_DWORD *)&this->pNGHVarianceParticle + 3001) = 476;
  *((_DWORD *)&this->pNGHVarianceParticle + 3003) = 769;
  *((_DWORD *)&this->pNGHVarianceParticle + 3004) = *((_DWORD *)&this->pNGHVarianceParticle + 3002) + 306;
  v10 = *((_DWORD *)&this->pNGHVarianceParticle + 3003);
  LODWORD(pPos.y) = *((_DWORD *)&this->pNGHVarianceParticle + 3002) + 15;
  LODWORD(pPos.x) = v10 - 31;
  v97 = LODWORD(pPos.y) + 26;
  LODWORD(pPos.z) = v10 - 31 + 22;
  LODWORD(pDir.y) = LODWORD(pPos.y) + 253;
  LODWORD(pDir.x) = v10 - 31;
  v11 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  v12 = LODWORD(pPos.y) + 279;
  pDir.z = pPos.z;
  v13 = *((_DWORD *)&(&this->pNGHVarianceParticle)[48] + 11);
  v94 = LODWORD(pPos.y) + 279;
  LOBYTE(v12) = *(_BYTE *)(v11 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, _DWORD, int, int))(v13 + 28))(
    &(&this->pNGHVarianceParticle)[48] + 11,
    259,
    &this->pNGHVarianceParticle + 3001,
    this,
    0,
    1,
    v12);
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->SetLockSel();
  *((_DWORD *)&this->pNGHVarianceParticle + 2989) = -4;
  *((_DWORD *)&this->pNGHVarianceParticle + 2990) = -6;
  *((_DWORD *)&this->pNGHVarianceParticle + 2991) = 10;
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->pNGHVarianceParticle + 3001, 38, 27, 0);
  ((CCBUI *)(&this->pNGHVarianceParticle + 2719))->ShowEffect(*((_DWORD *)&this->pNGHVarianceParticle + 3002) + 1, *((_DWORD *)&this->pNGHVarianceParticle + 3003) - 38, *((_DWORD *)&this->pNGHVarianceParticle + 3003));
  ((CCBUI *)(&this->pNGHVarianceParticle + 2719))->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)(&this->pNGHVarianceParticle + 2719))->SetSelection(27);
  ((CCBUI *)(&this->pNGHVarianceParticle + 2719))->SetCurPlayer(5);
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->SetFirstShow((int)"Name", 168);
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->SetFirstShow((int)"Price", 51);
  ((UIListBox *)(&(&this->pNGHVarianceParticle)[48] + 11))->SetFirstShow((int)"Num1", 38);
  ((CCBUI *)(&this->pNGHVarianceParticle + 2719))->VirtualCall();
  v14 = *((_DWORD *)&this->pNGHVarianceParticle + 3002) + 2;
  v88 = *((_DWORD *)&this->pNGHVarianceParticle + 3001);
  v89 = v14;
  v90 = v88 + 256;
  v91 = v14 + 23;
  *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = 0;
  do
  {
    (*(void ( **)(CParticleEffect **, int, int *, PlayerMgr *))(*((_DWORD *)&(&this->pNGHVarianceParticle)[38]
                                                                          + 38
                                                                          * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                          + 1)
                                                                        + 16))(
      &(&this->pNGHVarianceParticle)[38] + 38 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 1,
      257,
      &v88,
      this);
    ((UIStatic *)(&(&this->pNGHVarianceParticle)[38]
                                            + 38 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 1))->CreateFromTemplate();
    v15 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
    v89 = v91;
    v91 += 23;
    *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = v15 + 1;
  }
  while ( v15 + 1 < 13 );
  *((_DWORD *)&this->pNGHVarianceParticle + 4194) = 0;
  *((_DWORD *)&this->pNGHVarianceParticle + 4193) = 0;
  *((_DWORD *)&this->pNGHVarianceParticle + 4195) = 90;
  *((_DWORD *)&this->pNGHVarianceParticle + 4196) = *((_DWORD *)&this->pNGHVarianceParticle + 4194) + 32;
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                                     + 4197)
                                                                                   + 16))(
    &this->pNGHVarianceParticle + 4197,
    513,
    &this->pNGHVarianceParticle + 4193,
    this);
  ((UIScene *)(&this->pNGHVarianceParticle + 4197))->SetShow(0);
  (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle + 4197))(
    &this->pNGHVarianceParticle + 4197,
    0);
  v16 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  v87 = "UI\\Assistant\\Communal\\Add";
  LOBYTE(v79) = *(_BYTE *)(v16 + 3284);
  v17 = *((_DWORD *)&this->pNGHVarianceParticle + 3013);
  v18 = v79;
  v74 = v79;
  *((_DWORD *)&this->pNGHVarianceParticle + 3185) = 24;
  *((_DWORD *)&this->pNGHVarianceParticle + 3186) = 40;
  *((_DWORD *)&this->pNGHVarianceParticle + 3006) = 158;
  *((_DWORD *)&this->pNGHVarianceParticle + 3005) = 476;
  *((_DWORD *)&this->pNGHVarianceParticle + 3007) = 500;
  *((_DWORD *)&this->pNGHVarianceParticle + 3008) = 198;
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, char *))(v17 + 28))(
    &this->pNGHVarianceParticle + 3013,
    405,
    &this->pNGHVarianceParticle + 3005,
    this,
    "UI\\Assistant\\Communal\\Sub",
    0,
    v74);
  v19 = *((_DWORD *)&this->pNGHVarianceParticle + 3005);
  v20 = *((_DWORD *)&this->pNGHVarianceParticle + 3008);
  *((_DWORD *)&this->pNGHVarianceParticle + 3010) = v20;
  v75 = v18;
  v21 = v87;
  *((_DWORD *)&this->pNGHVarianceParticle + 3009) = v19;
  *((_DWORD *)&this->pNGHVarianceParticle + 3011) = *((_DWORD *)&this->pNGHVarianceParticle + 3007);
  *((_DWORD *)&this->pNGHVarianceParticle + 3012) = *((_DWORD *)&this->pNGHVarianceParticle + 3186) + v20;
  (*(void ( **)(int, CParticleEffect **, PlayerMgr *, char *, _DWORD, char *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                                        + 3099)
                                                                                      + 28))(
    406,
    &this->pNGHVarianceParticle + 3009,
    this,
    v21,
    0,
    v75);
  *((_BYTE *)&this->pNGHVarianceParticle + 12756) = (_BYTE)v79;
  *((_DWORD *)&this->pNGHVarianceParticle + 3187) = 1;
  ((PalScript *)(&this->pNGHVarianceParticle + 3013))->OpenScript("UI\\Assistant\\Communal\\UnSub.tga", *((_BYTE *)&this->pNGHVarianceParticle + 12756));
  ((PalScript *)(&this->pNGHVarianceParticle + 3099))->OpenScript("UI\\Assistant\\Communal\\UnAdd.tga", *((_BYTE *)&this->pNGHVarianceParticle + 12756));
  *((_DWORD *)&this->pNGHVarianceParticle + 3188) = 20;
  (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle + 3013))(
    &this->pNGHVarianceParticle + 3013,
    0);
  (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle + 3099))(
    &this->pNGHVarianceParticle + 3099,
    0);
  v22 = (&this->pNGHVarianceParticle)[57];
  v81 = 142;
  v80 = 218;
  v82 = 450;
  v83 = 556;
  (*(void ( **)(CParticleEffect **, int, int *, PlayerMgr *))v22->_ParticleSystems)(
    &(&this->pNGHVarianceParticle)[57],
    161,
    &v80,
    this);
  ((UIStatic *)&(&this->pNGHVarianceParticle)[57])->CreateFromTemplate();
  v23 = *((_DWORD *)&this->pNGHVarianceParticle + 3230);
  v81 = 388;
  v80 = 232;
  v82 = 444;
  v83 = 556;
  (*(void ( **)(CParticleEffect **, int, int *, PlayerMgr *))(v23 + 16))(
    &this->pNGHVarianceParticle + 3230,
    161,
    &v80,
    this);
  ((UIScene *)(&this->pNGHVarianceParticle + 3230))->SetShow(0);
  v24 = *((_DWORD *)&this->pNGHVarianceParticle + 3272);
  v81 = 520;
  v80 = 232;
  v82 = 444;
  v83 = 552;
  (*(void ( **)(CParticleEffect **, int, int *, PlayerMgr *))(v24 + 16))(
    &this->pNGHVarianceParticle + 3272,
    161,
    &v80,
    this);
  ((UIScene *)(&this->pNGHVarianceParticle + 3272))->SetShow(0);
  v25 = *((_DWORD *)&this->pNGHVarianceParticle + 2623);
  v99[1] = 158;
  v99[0] = 404;
  v99[2] = 420;
  v99[3] = 190;
  (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(v25 + 16))(
    &this->pNGHVarianceParticle + 2623,
    257,
    v99,
    this);
  ((UIStatic *)(&this->pNGHVarianceParticle + 2623))->CreateFromTemplate();
  *((_DWORD *)&this->pNGHVarianceParticle + 3353) = 392;
  *((_DWORD *)&this->pNGHVarianceParticle + 3352) = 478;
  *((_DWORD *)&this->pNGHVarianceParticle + 3354) = 624;
  *((_DWORD *)&this->pNGHVarianceParticle + 3355) = *((_DWORD *)&this->pNGHVarianceParticle + 3353) + 32;
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *))(*((_DWORD *)&(&this->pNGHVarianceParticle)[59]
                                                                                     + 10)
                                                                                   + 16))(
    &(&this->pNGHVarianceParticle)[59] + 10,
    272,
    &this->pNGHVarianceParticle + 3352,
    this);
  ((UIScene *)(&(&this->pNGHVarianceParticle)[59] + 10))->SetShow(0);
  sprintf(
    &this->m_RoleTask.m_TaskData[4],
    "%s %d",
    (const char *)&g_bSaveFlag,
    ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)(&(&this->pNGHVarianceParticle)[59] + 10))->SetEnable((int)&this->m_RoleTask.m_TaskData[4], 0);
  *((_DWORD *)&this->pNGHVarianceParticle + 3395) = 392;
  *((_DWORD *)&this->pNGHVarianceParticle + 3394) = 638;
  *((_DWORD *)&this->pNGHVarianceParticle + 3396) = 764;
  *((_DWORD *)&this->pNGHVarianceParticle + 3397) = *((_DWORD *)&this->pNGHVarianceParticle + 3395) + 32;
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                                     + 3356)
                                                                                   + 16))(
    &this->pNGHVarianceParticle + 3356,
    261,
    &this->pNGHVarianceParticle + 3394,
    this);
  ((UIScene *)(&this->pNGHVarianceParticle + 3356))->SetShow(0);
  sprintf(
    &this->m_RoleTask.m_TaskData[4],
    "%s %d",
    g_szCombatFieldName,
    *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[244]);
  ((UICaption *)(&this->pNGHVarianceParticle + 3356))->SetEnable((int)&this->m_RoleTask.m_TaskData[4], 0);
  *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = 0;
  do
  {
    v26 = *(&this->dwWeaponWU + 6281);
    v27 = *(&this->dwWeaponWU + 6280);
    v77[0] = *(&this->dwWeaponWU + 6279);
    v28 = *(&this->dwWeaponWU + 6282);
    v77[1] = v27;
    v29 = v27 + v28;
    v30 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
    v77[2] = v77[0] + v26;
    v77[3] = v29;
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU + 38 * v30 + 6069) + 16))(
      &this->dwWeaponWU + 38 * v30 + 6069,
      dword_56B3C8[v30],
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 38 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6069))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 38 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6069))(
      &this->dwWeaponWU + 38 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6069,
      0);
    v31 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 1;
    *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = v31;
  }
  while ( v31 < 5 );
  *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = 0;
  do
  {
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->m_bWPXS
                                                                           + 270
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 5399)
                                                                         + 16))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5399,
      dword_56B4DC[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->m_bWPXS
                                            + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 5399))->CreateFromTemplate();
    *((float *)&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5441) = *(float *)&this->m_RoleTask.m_taskFile.m_token[264];
    *(&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5443) = 1;
    (**((void ( ***)(int *, _DWORD))&this->m_bWPXS
      + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 5399))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5399,
      0);
    (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(*((_DWORD *)&(&this->pNGHVarianceParticle)[2]
                                                                             + 228
                                                                             * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                             + 6)
                                                                           + 16))(
      &(&this->pNGHVarianceParticle)[2] + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6,
      dword_56B554[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&(&this->pNGHVarianceParticle)[2]
                                            + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6))->CreateFromTemplate();
    (**((void ( ***)(CParticleEffect **, _DWORD))&(&this->pNGHVarianceParticle)[2]
      + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6))(
      &(&this->pNGHVarianceParticle)[2] + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->m_bWPXS
                                                                           + 270
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 5444)
                                                                         + 16))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5444,
      dword_56B540[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->m_bWPXS
                                            + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 5444))->CreateFromTemplate();
    *((float *)&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5486) = *(float *)&this->m_RoleTask.m_taskFile.m_token[264];
    *(&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5488) = 1;
    (**((void ( ***)(int *, _DWORD))&this->m_bWPXS
      + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 5444))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5444,
      0);
    (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                             + 228
                                                                             * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                             + 156)
                                                                           + 16))(
      &this->pNGHVarianceParticle + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 156,
      dword_56B5B8[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->pNGHVarianceParticle
                                            + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 156))->CreateFromTemplate();
    (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle
      + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 156))(
      &this->pNGHVarianceParticle + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 156,
      0);
    (*(void ( **)(int *, const char *, _DWORD *, PlayerMgr *))(*(&this->m_bWPXS
                                                                                    + 270
                                                                                    * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                                    + 5489)
                                                                                  + 16))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5489,
      (&off_56B518)[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->m_bWPXS
                                            + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 5489))->CreateFromTemplate();
    *((float *)&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5531) = *(float *)&this->m_RoleTask.m_taskFile.m_token[264];
    *(&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5533) = 1;
    (**((void ( ***)(int *, _DWORD))&this->m_bWPXS
      + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 5489))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5489,
      0);
    (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                             + 228
                                                                             * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                             + 194)
                                                                           + 16))(
      &this->pNGHVarianceParticle + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 194,
      dword_56B590[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->pNGHVarianceParticle
                                            + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 194))->CreateFromTemplate();
    (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle
      + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 194))(
      &this->pNGHVarianceParticle + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 194,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->m_bWPXS
                                                                           + 270
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 5534)
                                                                         + 16))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5534,
      dword_56B4F0[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->m_bWPXS
                                            + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 5534))->CreateFromTemplate();
    *((float *)&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5576) = *(float *)&this->m_RoleTask.m_taskFile.m_token[264];
    *(&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5578) = 1;
    (**((void ( ***)(int *, _DWORD))&this->m_bWPXS
      + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 5534))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5534,
      0);
    (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(*((_DWORD *)&(&this->pNGHVarianceParticle)[4]
                                                                             + 228
                                                                             * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                             + 8)
                                                                           + 16))(
      &(&this->pNGHVarianceParticle)[4] + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 8,
      dword_56B568[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&(&this->pNGHVarianceParticle)[4]
                                            + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 8))->CreateFromTemplate();
    (**((void ( ***)(CParticleEffect **, _DWORD))&(&this->pNGHVarianceParticle)[4]
      + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 8))(
      &(&this->pNGHVarianceParticle)[4] + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 8,
      0);
    (*(void ( **)(int *, const char *, _DWORD *, PlayerMgr *))(*(&this->m_bWPXS
                                                                                    + 270
                                                                                    * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                                    + 5579)
                                                                                  + 16))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5579,
      (&off_56B504)[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->m_bWPXS
                                            + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 5579))->CreateFromTemplate();
    *((float *)&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5621) = *(float *)&this->m_RoleTask.m_taskFile.m_token[264];
    *(&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5623) = 1;
    (**((void ( ***)(int *, _DWORD))&this->m_bWPXS
      + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 5579))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5579,
      0);
    (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                             + 228
                                                                             * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                             + 270)
                                                                           + 16))(
      &this->pNGHVarianceParticle + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 270,
      dword_56B57C[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->pNGHVarianceParticle
                                            + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 270))->CreateFromTemplate();
    (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle
      + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 270))(
      &this->pNGHVarianceParticle + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 270,
      0);
    (*(void ( **)(int *, const char *, _DWORD *, PlayerMgr *))(*(&this->m_bWPXS
                                                                                    + 270
                                                                                    * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                                    + 5624)
                                                                                  + 16))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5624,
      (&off_56B52C)[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->m_bWPXS
                                            + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 5624))->CreateFromTemplate();
    *((float *)&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5666) = *(float *)&this->m_RoleTask.m_taskFile.m_token[264];
    *(&this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5668) = 1;
    (**((void ( ***)(int *, _DWORD))&this->m_bWPXS
      + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 5624))(
      &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5624,
      0);
    (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                             + 228
                                                                             * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                             + 308)
                                                                           + 16))(
      &this->pNGHVarianceParticle + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 308,
      dword_56B5A4[*(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]],
      v77,
      this);
    ((UIStatic *)(&this->pNGHVarianceParticle
                                            + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 308))->CreateFromTemplate();
    (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle
      + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 308))(
      &this->pNGHVarianceParticle + 228 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 308,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6285)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6285,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6285))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6285))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6285,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6323)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6323,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6323))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6323))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6323,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6361)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6361,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6361))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6361))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6361,
      0);
    v32 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6399;
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*v32 + 16))(v32, 295, v77, this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6399))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6399))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6399,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6589)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6589,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6589))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6589))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6589,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6627)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6627,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6627))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6627))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6627,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6665)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6665,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6665))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6665))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6665,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6703)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6703,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6703))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6703))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6703,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6893)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6893,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6893))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6893))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6893,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6931)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6931,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6931))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6931))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6931,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6969)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6969,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6969))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6969))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6969,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7007)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7007,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7007))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7007))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7007,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7197)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7197,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7197))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7197))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7197,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7235)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7235,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7235))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7235))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7235,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7273)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7273,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7273))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7273))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7273,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7311)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7311,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7311))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7311))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7311,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7501)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7501,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7501))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7501))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7501,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7539)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7539,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7539))->CreateFromTemplate();
    v33 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7539;
    (*(void ( **)(int *, _DWORD))*v33)(v33, 0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7577)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7577,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7577))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7577))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7577,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7615)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7615,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7615))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7615))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7615,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7805)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7805,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7805))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7805))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7805,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7843)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7843,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7843))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7843))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7843,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7881)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7881,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7881))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7881))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7881,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7919)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7919,
      295,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7919))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7919))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7919,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6437)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6437,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6437))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6437))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6437,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6475)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6475,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6475))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6475))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6475,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6513)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6513,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6513))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6513))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6513,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6551)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6551,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6551))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6551))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6551,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6741)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6741,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6741))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6741))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6741,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6779)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6779,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6779))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6779))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6779,
      0);
    v34 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6817;
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*v34 + 16))(v34, 296, v77, this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6817))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6817))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6817,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 6855)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6855,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 6855))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 6855))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6855,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7045)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7045,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7045))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7045))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7045,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7083)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7083,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7083))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7083))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7083,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7121)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7121,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7121))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7121))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7121,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7159)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7159,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7159))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7159))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7159,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7349)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7349,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7349))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7349))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7349,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7387)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7387,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7387))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7387))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7387,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7425)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7425,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7425))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7425))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7425,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7463)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7463,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7463))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7463))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7463,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7653)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7653,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7653))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7653))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7653,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7691)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7691,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7691))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7691))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7691,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7729)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7729,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7729))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7729))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7729,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7767)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7767,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7767))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7767))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7767,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7957)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7957,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7957))->CreateFromTemplate();
    v35 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7957;
    (*(void ( **)(int *, _DWORD))*v35)(v35, 0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 7995)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7995,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 7995))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 7995))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7995,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 8033)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 8033,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 8033))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 8033))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 8033,
      0);
    (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU
                                                                           + 1824
                                                                           * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                                           + 8071)
                                                                         + 16))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 8071,
      296,
      v77,
      this);
    ((UIStatic *)(&this->dwWeaponWU
                                            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                            + 8071))->CreateFromTemplate();
    (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
      + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 8071))(
      &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 8071,
      0);
    v36 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 1;
    *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = v36;
  }
  while ( v36 < 5 );
  v37 = *((_DWORD *)&this->pNGHVarianceParticle + 1721);
  v84[1] = 436;
  v84[0] = 456;
  v85 = 486;
  v86 = 555;
  (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(v37 + 16))(
    &this->pNGHVarianceParticle + 1721,
    257,
    v84,
    this);
  ((UIStatic *)(&this->pNGHVarianceParticle + 1721))->CreateFromTemplate();
  v38 = *((_DWORD *)&this->pNGHVarianceParticle + 1759);
  v84[0] = v85;
  v85 += 256;
  (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(v38 + 16))(
    &this->pNGHVarianceParticle + 1759,
    257,
    v84,
    this);
  ((UIStatic *)(&this->pNGHVarianceParticle + 1759))->CreateFromTemplate();
  v39 = *((_DWORD *)&(&this->pNGHVarianceParticle)[32] + 5);
  v84[0] = v85;
  v85 += 32;
  (*(void ( **)(CParticleEffect **, int, _DWORD *, PlayerMgr *))(v39 + 16))(
    &(&this->pNGHVarianceParticle)[32] + 5,
    257,
    v84,
    this);
  ((UIStatic *)(&(&this->pNGHVarianceParticle)[32] + 5))->CreateFromTemplate();
  *((_DWORD *)&this->pNGHVarianceParticle + 1874) = 447;
  *((_DWORD *)&this->pNGHVarianceParticle + 1873) = 489;
  *((_DWORD *)&this->pNGHVarianceParticle + 1875) = 745;
  *((_DWORD *)&this->pNGHVarianceParticle + 1876) = *((_DWORD *)&this->pNGHVarianceParticle + 1874) + 100;
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                                     + 1835)
                                                                                   + 16))(
    &this->pNGHVarianceParticle + 1835,
    265,
    &this->pNGHVarianceParticle + 1873,
    this);
  ((UIScene *)(&this->pNGHVarianceParticle + 1835))->SetShow(0);
  (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle + 1835))(
    &this->pNGHVarianceParticle + 1835,
    0);
  v40 = &this->pNGHVarianceParticle + 2087;
  *((_DWORD *)&this->pNGHVarianceParticle + 2088) = *((_DWORD *)&this->pNGHVarianceParticle + 1874);
  *((_DWORD *)&this->pNGHVarianceParticle + 2087) = *((_DWORD *)&this->pNGHVarianceParticle + 1873);
  *((_DWORD *)&this->pNGHVarianceParticle + 2089) = *((_DWORD *)&this->pNGHVarianceParticle + 1875);
  *((_DWORD *)&this->pNGHVarianceParticle + 2090) = *((_DWORD *)&this->pNGHVarianceParticle + 1876);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *))(*((_DWORD *)&this->pNGHVarianceParticle
                                                                                     + 2049)
                                                                                   + 16))(
    &this->pNGHVarianceParticle + 2049,
    305,
    &this->pNGHVarianceParticle + 2087,
    this);
  ((UIScene *)(&this->pNGHVarianceParticle + 2049))->SetShow(0);
  v41 = *((_DWORD *)&this->pNGHVarianceParticle + 1876) - 36;
  v101[0] = *((_DWORD *)&this->pNGHVarianceParticle + 1875) - 36;
  v101[1] = v41;
  v101[2] = v101[0] + 24;
  v101[3] = v41 + 32;
  (*(void ( **)(int *, int, _DWORD *, PlayerMgr *))(*(&this->dwWeaponWU + 6028) + 16))(
    &this->dwWeaponWU + 6028,
    2,
    v101,
    this);
  ((UIScene *)(&this->dwWeaponWU + 6028))->LoadResource("ui\\scene\\page");
  ((UIScene *)(&this->dwWeaponWU + 6028))->SetController(0x40000000);
  (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU + 6028))(&this->dwWeaponWU + 6028, 0);
  *((_DWORD *)&(&this->pNGHVarianceParticle)[62] + 13) = 569;
  v42 = *((_DWORD *)&this->pNGHVarianceParticle + 3398);
  *((_DWORD *)&(&this->pNGHVarianceParticle)[62] + 12) = 300;
  *((_DWORD *)&this->pNGHVarianceParticle + 3486) = 390;
  *((_DWORD *)&this->pNGHVarianceParticle + 3487) = *((_DWORD *)&(&this->pNGHVarianceParticle)[62] + 13) + 25;
  v43 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  LOBYTE(v43) = *(_BYTE *)(v43 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(v42 + 28))(
    &this->pNGHVarianceParticle + 3398,
    262,
    &(&this->pNGHVarianceParticle)[62] + 12,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v43);
  ((PalScript *)(&this->pNGHVarianceParticle + 3398))->OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnYes.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  v44 = *((_DWORD *)&(&this->pNGHVarianceParticle)[62] + 13);
  *((_DWORD *)&this->pNGHVarianceParticle + 3578) = *((_DWORD *)&this->pNGHVarianceParticle + 3487);
  v45 = *((_DWORD *)&this->pNGHVarianceParticle + 3486) + 66;
  *((_DWORD *)&this->pNGHVarianceParticle + 3576) = v44;
  *((_DWORD *)&this->pNGHVarianceParticle + 3575) = v45;
  *((_DWORD *)&this->pNGHVarianceParticle + 3577) = v45 + 90;
  v46 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  LOBYTE(v46) = *(_BYTE *)(v46 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(*((_DWORD *)&this->pNGHVarianceParticle + 3489) + 28))(
    &this->pNGHVarianceParticle + 3489,
    263,
    &this->pNGHVarianceParticle + 3575,
    this,
    "UI\\Assistant\\Communal\\bDicker",
    0,
    v46);
  sub_445E50((int)(&this->pNGHVarianceParticle + 3489));
  ((PalScript *)(&this->pNGHVarianceParticle + 3489))->OpenScript("UI\\Assistant\\Communal\\UnDicker.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  v47 = *((_DWORD *)&this->pNGHVarianceParticle + 3577);
  v48 = *((_DWORD *)&this->pNGHVarianceParticle + 3578);
  *((_DWORD *)&this->pNGHVarianceParticle + 3666) = *((_DWORD *)&this->pNGHVarianceParticle + 3576);
  v47 += 66;
  *((_DWORD *)&this->pNGHVarianceParticle + 3668) = v48;
  v49 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  *((_DWORD *)&this->pNGHVarianceParticle + 3665) = v47;
  *((_DWORD *)&this->pNGHVarianceParticle + 3667) = v47 + 90;
  LOBYTE(v49) = *(_BYTE *)(v49 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(*((_DWORD *)&this->pNGHVarianceParticle + 3579) + 28))(
    &this->pNGHVarianceParticle + 3579,
    264,
    &this->pNGHVarianceParticle + 3665,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    v49);
  ((PalScript *)(&this->pNGHVarianceParticle + 3579))->OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnNo.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  v50 = *(&this->dwWeaponWU + 5929) - 38;
  v51 = *(&this->dwWeaponWU + 5930) - 50;
  *((_DWORD *)&(&this->pNGHVarianceParticle)[67] + 3) = v50;
  *((_DWORD *)&(&this->pNGHVarianceParticle)[67] + 4) = v51;
  *((_DWORD *)&(&this->pNGHVarianceParticle)[67] + 5) = v50 + 38;
  v52 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  *((_DWORD *)&(&this->pNGHVarianceParticle)[67] + 6) = v51 + 48;
  LOBYTE(v52) = *(_BYTE *)(v52 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(*((_DWORD *)&this->pNGHVarianceParticle + 3669) + 28))(
    &this->pNGHVarianceParticle + 3669,
    258,
    &(&this->pNGHVarianceParticle)[67] + 3,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    0,
    v52);
  ((PalScript *)(&this->pNGHVarianceParticle + 3669))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnExit.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  ((CCBFiveNimbusWindow *)(&this->pNGHVarianceParticle + 1302))->CreateScriptAndCamera(404, (int)this);
  v79 = g_szSceneUIText;
  v53 = "D16";
  while ( 1 )
  {
    v54 = *v53;
    v78 = v54;
    v55 = v54 < (unsigned __int8)*v79;
    if ( v54 != *v79 )
      break;
    if ( !v54 )
      goto LABEL_12;
    v78 = v53[1];
    v55 = v78 < (unsigned __int8)v79[1];
    if ( v78 != v79[1] )
      break;
    v53 += 2;
    v79 += 2;
    if ( !v78 )
    {
LABEL_12:
      v56 = 0;
      goto LABEL_14;
    }
  }
  v56 = -v55 - (v55 - 1);
LABEL_14:
  if ( v56 )
    sprintf(&this->m_RoleTask.m_TaskData[4], "Item\\%s\\%s.pol", "D16", "D16");
  else
    sprintf(&this->m_RoleTask.m_TaskData[4], byte_5967B0, "NONE");
  ((PalScript *)(&this->pNGHVarianceParticle + 1320))->LoadModel(&this->m_RoleTask.m_TaskData[4], 0);
  *((_DWORD *)&this->pNGHVarianceParticle + 1321) = 0;
  *((_DWORD *)&this->pNGHVarianceParticle + 1319) = 1;
  ((CCBFiveNimbusWindow *)(&this->pNGHVarianceParticle + 1302))->SetFloatParam(120.0);
  ((Camera *)(&this->pNGHVarianceParticle + 1302))->UpdateCameraLookAt(330, 258, 600);
  ((UIPushButton *)(&this->pNGHVarianceParticle + 1302))->SetAnimOffset(1, 0, v76);
  v57 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  *((_DWORD *)&this->pNGHVarianceParticle + 4190) = 439;
  *((_DWORD *)&this->pNGHVarianceParticle + 4191) = 576;
  *((_DWORD *)&this->pNGHVarianceParticle + 4189) = 492;
  *((_DWORD *)&this->pNGHVarianceParticle + 4192) = 489;
  LOBYTE(v57) = *(_BYTE *)(v57 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(*((_DWORD *)&(&this->pNGHVarianceParticle)[67] + 7) + 28))(
    &(&this->pNGHVarianceParticle)[67] + 7,
    273,
    &this->pNGHVarianceParticle + 4189,
    this,
    "UI\\Assistant\\Equip\\bDK5",
    0,
    v57);
  ((PalScript *)(&(&this->pNGHVarianceParticle)[67] + 7))->OpenScript("UI\\Assistant\\Equip\\UnDK5.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  v58 = *((_DWORD *)&this->pNGHVarianceParticle + 4191);
  v59 = *((_DWORD *)&this->pNGHVarianceParticle + 3845);
  *((_DWORD *)&this->pNGHVarianceParticle + 4189) = v58;
  *((_DWORD *)&this->pNGHVarianceParticle + 4191) = v58 + 84;
  v60 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  LOBYTE(v60) = *(_BYTE *)(v60 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(v59 + 28))(
    &this->pNGHVarianceParticle + 3845,
    274,
    &this->pNGHVarianceParticle + 4189,
    this,
    "UI\\Assistant\\Equip\\bDK6",
    0,
    v60);
  ((PalScript *)(&this->pNGHVarianceParticle + 3845))->OpenScript("UI\\Assistant\\Equip\\UnDK6.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  v61 = *((_DWORD *)&this->pNGHVarianceParticle + 4191);
  v62 = *((_DWORD *)&(&this->pNGHVarianceParticle)[70] + 11);
  *((_DWORD *)&this->pNGHVarianceParticle + 4189) = v61;
  *((_DWORD *)&this->pNGHVarianceParticle + 4191) = v61 + 84;
  v63 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  LOBYTE(v63) = *(_BYTE *)(v63 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(v62 + 28))(
    &(&this->pNGHVarianceParticle)[70] + 11,
    275,
    &this->pNGHVarianceParticle + 4189,
    this,
    "UI\\Assistant\\Equip\\bDK7",
    0,
    v63);
  ((PalScript *)(&(&this->pNGHVarianceParticle)[70] + 11))->OpenScript("UI\\Assistant\\Equip\\UnDK7.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  v64 = *((_DWORD *)&this->pNGHVarianceParticle + 4192);
  *((_DWORD *)&this->pNGHVarianceParticle + 4189) = 492;
  v64 += 2;
  *((_DWORD *)&this->pNGHVarianceParticle + 4191) = 576;
  *((_DWORD *)&this->pNGHVarianceParticle + 4190) = v64;
  *((_DWORD *)&this->pNGHVarianceParticle + 4192) = v64 + 50;
  v65 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  LOBYTE(v65) = *(_BYTE *)(v65 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(*((_DWORD *)&this->pNGHVarianceParticle + 4017) + 28))(
    &this->pNGHVarianceParticle + 4017,
    276,
    &this->pNGHVarianceParticle + 4189,
    this,
    "UI\\Assistant\\Equip\\bDK8",
    0,
    v65);
  ((PalScript *)(&this->pNGHVarianceParticle + 4017))->OpenScript("UI\\Assistant\\Equip\\UnDK8.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  v66 = *((_DWORD *)&this->pNGHVarianceParticle + 4191);
  v67 = *((_DWORD *)&this->pNGHVarianceParticle + 4103);
  *((_DWORD *)&this->pNGHVarianceParticle + 4189) = v66;
  *((_DWORD *)&this->pNGHVarianceParticle + 4191) = v66 + 84;
  v68 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  LOBYTE(v68) = *(_BYTE *)(v68 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(v67 + 28))(
    &this->pNGHVarianceParticle + 4103,
    277,
    &this->pNGHVarianceParticle + 4189,
    this,
    "UI\\Assistant\\Equip\\bDK9",
    0,
    v68);
  ((PalScript *)(&this->pNGHVarianceParticle + 4103))->OpenScript("UI\\Assistant\\Equip\\UnDK9.tga", *(_BYTE *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6) + 3284));
  *((_DWORD *)&this->pNGHVarianceParticle + 2088) = 492;
  *v40 = (CParticleEffect *)511;
  *((_DWORD *)&this->pNGHVarianceParticle + 2089) = 595;
  v69 = *((_DWORD *)&this->pNGHVarianceParticle + 1877);
  *((_DWORD *)&this->pNGHVarianceParticle + 2090) = *((_DWORD *)&this->pNGHVarianceParticle + 2088) + 50;
  v70 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  LOBYTE(v70) = *(_BYTE *)(v70 + 3284);
  (*(void ( **)(CParticleEffect **, int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(v69 + 28))(
    &this->pNGHVarianceParticle + 1877,
    297,
    &this->pNGHVarianceParticle + 2087,
    this,
    "UI\\Assistant\\Equip\\bEquipYes",
    0,
    v70);
  v71 = *((_DWORD *)&this->pNGHVarianceParticle + 2089) + 40;
  *v40 = (CParticleEffect *)v71;
  *((_DWORD *)&this->pNGHVarianceParticle + 2089) = v71 + 84;
  v72 = *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
  LOBYTE(v72) = *(_BYTE *)(v72 + 3284);
  (*(void ( **)(int, CParticleEffect **, PlayerMgr *, char *, _DWORD, int))(*((_DWORD *)&(&this->pNGHVarianceParticle)[35]
                                                                                     + 3)
                                                                                   + 28))(
    304,
    &this->pNGHVarianceParticle + 2087,
    this,
    "UI\\Assistant\\Equip\\bEquipNo",
    0,
    v72);
  ((PAL3 *)this)->GetValue(0);
  v103[1] = 200;
  v103[0] = 300;
  v103[2] = 500;
  v103[3] = 300;
  ((ARC_PlayerAtt *)(&this->pNGHVarianceParticle + 1379))->Create((int)&g_PlayerAttBuffer2.skill[2], (int)v103);
  ((UIItem *)(&this->pNGHVarianceParticle + 1379))->SetData(31);
  result = ((PAL3 *)this)->SetValue(0);
  this->m_RoleTask.m_taskFile.m_token[260] = 1;
  return result;
}

// 0x00461C50
void PlayerMgr::InitMode(int nVal)
{
  UICaption *v3; // edi
  LONG v5; // edx
  int v6; // ecx
  double v7; // st7
  double v8; // st7
  int v9; // ecx
  CParticleEffect *v10; // edx
  float fProb; // [esp+0xC] [ebp-0x4]
  int nVala; // [esp+0x14] [ebp+0x4]

  v3 = (UICaption *)(&this->pNGHVarianceParticle + 1835);
  (**((void ( ***)(CParticleEffect **, int))&this->pNGHVarianceParticle + 1835))(
    &this->pNGHVarianceParticle + 1835,
    1);
  switch ( nVal )
  {
    case 0:
      v5 = 5 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[244] / 10;
      goto LABEL_8;
    case 1:
      v6 = 6 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[244];
      goto LABEL_7;
    case 2:
      if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom < 7 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[244] / 10 )
        goto LABEL_11;
      goto LABEL_12;
    case 3:
      v6 = 8 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[244];
LABEL_7:
      v5 = v6 / 10;
LABEL_8:
      if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom < v5 )
        goto LABEL_11;
      goto LABEL_12;
    case 4:
      if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom >= 9 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[244] / 10 )
        goto LABEL_12;
LABEL_11:
      ((UICaption *)v3)->SetEnable((int)(&this->dwWeaponWU + 177), 0);
      (**((void ( ***)(int *, int))&this->dwWeaponWU + 6028))(&this->dwWeaponWU + 6028, 1);
      ((PAL3 *)this)->SetValue(0);
      ((PAL3 *)this)->SetPanelStates(1u);
      ((PAL3 *)this)->SetRange(0);
      sub_445E50((int)(&(&this->pNGHVarianceParticle)[48] + 11));
      sprintf(
        &this->m_RoleTask.m_TaskData[4],
        "%s %d",
        g_szCombatFieldName,
        *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[244]);
      ((UICaption *)(&this->pNGHVarianceParticle + 3356))->SetEnable((int)&this->m_RoleTask.m_TaskData[4], 0);
      *((_DWORD *)&this->pNGHVarianceParticle + 4366) = 1;
      *((_BYTE *)&this->pNGHVarianceParticle + 16941) = 0;
      break;
    default:
LABEL_12:
      *((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 1) = nVal;
      if ( *((float *)&this->dwWeaponWU + nVal + 369) >= 0.0 )
        v7 = *((float *)&this->dwWeaponWU + nVal + 369);
      else
        v7 = (double)(rand() % 100) * 0.0099999998;
      *(float *)&nVala = v7;
      if ( *((float *)&this->dwWeaponWU + nVal + 1014) >= 0.0 )
        v8 = *((float *)&this->dwWeaponWU + nVal + 1014);
      else
        v8 = (double)(rand() % 100) * 0.0099999998;
      if ( ((CCBUI *)this)->RollProbability(*(float *)&nVala) )
      {
        *((_DWORD *)&this->pNGHVarianceParticle + 4366) = 1;
        ((PAL_GDB *)this)->UpdateSkillPanel();
      }
      else
      {
        fProb = v8;
        if ( ((CCBUI *)this)->RollProbability(fProb) )
        {
          v9 = *(_DWORD *)&this->m_RoleTask._TaskPicFolder[8];
          v10 = (CParticleEffect *)((char *)&(&this->pNGHVarianceParticle)[78]->_bPlay + 1);
          *((_DWORD *)&this->pNGHVarianceParticle + 4366) = 0;
          (&this->pNGHVarianceParticle)[78] = v10;
          if ( (int)v10 < v9 )
          {
            switch ( nVal )
            {
              case 1:
                sub_445E50((int)(&(&this->pNGHVarianceParticle)[67] + 7));
                ((PAL_GDB *)this)->UpdateSkillPanel();
                break;
              case 2:
                sub_445E50((int)(&(&this->pNGHVarianceParticle)[67] + 7));
                sub_445E50((int)(&this->pNGHVarianceParticle + 3845));
                ((PAL_GDB *)this)->UpdateSkillPanel();
                break;
              case 3:
                sub_445E50((int)(&(&this->pNGHVarianceParticle)[67] + 7));
                sub_445E50((int)(&this->pNGHVarianceParticle + 3845));
                sub_445E50((int)(&(&this->pNGHVarianceParticle)[70] + 11));
                ((PAL_GDB *)this)->UpdateSkillPanel();
                break;
              case 4:
                sub_445E50((int)(&(&this->pNGHVarianceParticle)[67] + 7));
                sub_445E50((int)(&this->pNGHVarianceParticle + 3845));
                sub_445E50((int)(&(&this->pNGHVarianceParticle)[70] + 11));
                sub_445E50((int)(&this->pNGHVarianceParticle + 4017));
                ((PAL_GDB *)this)->UpdateSkillPanel();
                break;
              default:
                goto LABEL_29;
            }
          }
          else
          {
            *((_DWORD *)&this->pNGHVarianceParticle + 4366) = 2;
            ((PAL_GDB *)this)->UpdateSkillPanel();
          }
        }
        else
        {
          *((_DWORD *)&this->pNGHVarianceParticle + 4366) = 3;
LABEL_29:
          ((PAL_GDB *)this)->UpdateSkillPanel();
        }
      }
      break;
  }
}

// 0x004620E0
int PlayerMgr::SendInputToRole(unsigned __int8 pData)
{
  (**((void ( ***)(CParticleEffect **, _DWORD))&this->pNGHVarianceParticle + 1835))(
    &this->pNGHVarianceParticle + 1835,
    pData);
  return (**((int ( ***)(int *, _DWORD))&this->dwWeaponWU + 6028))(&this->dwWeaponWU + 6028, pData);
}

// 0x00462120
int PlayerMgr::SetSelectionFlags(int nFlags)
{
  int v3; // edi
  int v4; // edx
  int v5; // eax
  int result; // eax

  v3 = 0;
  v4 = 0;
  *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = 0;
  do
  {
    v5 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
    if ( *((_BYTE *)&this->dwWeaponWU + v5 + 25132) && *(_BYTE *)(*(&this->dwWeaponWU + nFlags + 3666) + v5 + 614) )
    {
      ++v3;
      v4 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
    }
    result = v5 + 1;
    *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = result;
  }
  while ( result < 5 );
  if ( v3 )
  {
    if ( v3 == 1 )
    {
      result = *(unsigned __int8 *)(*(&this->dwWeaponWU + nFlags + 3666) + 612) - 7;
      switch ( *(_BYTE *)(*(&this->dwWeaponWU + nFlags + 3666) + 612) )
      {
        case 7:
          result = this->HandleInput(v4, 0, nFlags);
          break;
        case 8:
          result = this->HandleInput(v4, 3, nFlags);
          break;
        case 9:
          result = this->HandleInput(v4, 4, nFlags);
          break;
        case 0xB:
          result = this->HandleInput(v4, 1, nFlags);
          break;
        default:
          return result;
      }
    }
  }
  else
  {
    sprintf(&this->m_RoleTask.m_TaskData[4], "\\n    %s", (const char *)dword_DD4A3C);
    ((UICaption *)(&this->pNGHVarianceParticle + 1493))->SetEnable((int)&this->m_RoleTask.m_TaskData[4], 0);
    return ((UIRoleSelect *)(&this->pNGHVarianceParticle + 1379))->SetByte(1);
  }
  return result;
}

// 0x004623A0
int PlayerMgr::CreatePanelElements(CCBUIPanel *arg0)
{
  _WORD *v3; // ebp
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int i; // edi
  __int16 v8; // ax
  bool v9; // sf
  bool v10; // cc
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // edi
  int *v16; // eax
  _DWORD *v17; // ecx
  int v18; // edx
  _DWORD *v19; // eax
  int v20; // edx
  int v21; // ecx
  int v22; // eax
  int v23; // edx
  int v24; // ecx
  int v25; // edi
  __int16 v26; // ax
  bool v27; // sf
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int v32; // ecx
  int v33; // edi
  int *v34; // eax
  _DWORD *v35; // ecx
  int v36; // edx
  int v37; // eax
  int v38; // edx
  int v39; // ecx
  int v40; // edi
  _DWORD *v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // edx
  int v46; // ecx
  int v47; // edi
  int *v48; // eax
  _DWORD *v49; // ecx
  int v50; // edx
  int v51; // eax
  int v52; // edx
  int v53; // ecx
  int v54; // edi
  _DWORD *v55; // eax
  __int16 v56; // ax
  bool v57; // sf
  int v58; // eax
  int v59; // eax
  int v60; // edx
  int v61; // ecx
  int v62; // edi
  int *v63; // eax
  _DWORD *v64; // ecx
  int v65; // edx
  _DWORD *v66; // eax
  int v67; // edx
  int v68; // ecx
  int v69; // eax
  int v70; // edx
  int v71; // ecx
  int v72; // edi
  __int16 v73; // ax
  bool v74; // sf
  int v75; // eax
  int v76; // eax
  int v77; // eax
  int v78; // edx
  int v79; // ecx
  int v80; // edi
  int *v81; // eax
  _DWORD *v82; // ecx
  int v83; // edx
  int v84; // eax
  int v85; // edx
  int v86; // ecx
  int v87; // edi
  _DWORD *v88; // eax
  int v89; // eax
  int v90; // eax
  int v91; // eax
  int v92; // edx
  int v93; // ecx
  int v94; // edi
  int *v95; // eax
  _DWORD *v96; // ecx
  int v97; // edx
  int v98; // eax
  int v99; // edx
  int v100; // ecx
  int v101; // edi
  _DWORD *v102; // eax
  int v103; // eax
  __int16 v104; // cx
  __int16 v105; // dx
  int v106; // eax
  int v107; // edx
  int v108; // ecx
  int v109; // edi
  int *v110; // eax
  _DWORD *v111; // ecx
  int v112; // edx
  int v113; // eax
  int v114; // edx
  int v115; // ecx
  int v116; // edi
  _DWORD *v117; // eax
  int v118; // eax
  __int16 v119; // cx
  __int16 v120; // dx
  int v121; // eax
  int v122; // eax
  int v123; // edx
  int v124; // ecx
  int v125; // edi
  int *v126; // eax
  _DWORD *v127; // ecx
  int v128; // edx
  int v129; // eax
  int v130; // edx
  int v131; // ecx
  int v132; // edi
  _DWORD *v133; // eax
  int *v134; // ecx
  int v135; // eax
  int v136; // eax
  int v137; // edx
  int v138; // ecx
  int v139; // edi
  int *v140; // eax
  _DWORD *v141; // ecx
  int v142; // edx
  int v143; // eax
  int v144; // edx
  int v145; // ecx
  int v146; // edi
  _DWORD *v147; // eax
  int v148; // eax
  __int16 v149; // cx
  __int16 v150; // dx
  int v151; // eax
  int v152; // edx
  int v153; // ecx
  int v154; // edi
  int *v155; // eax
  _DWORD *v156; // ecx
  int v157; // edx
  int v158; // eax
  int v159; // edx
  int v160; // ecx
  int v161; // edi
  _DWORD *v162; // eax
  int v163; // eax
  __int16 v164; // cx
  __int16 v165; // dx
  int v166; // eax
  int v167; // eax
  int v168; // edx
  int v169; // ecx
  int v170; // edi
  int v171; // eax
  int v172; // edx
  int v173; // ecx
  int v174; // edi
  int v175; // eax
  int v176; // eax
  int v177; // edx
  int v178; // ecx
  int v179; // edi
  int *v180; // eax
  _DWORD *v181; // ecx
  int v182; // edx
  int v183; // eax
  int v184; // edx
  int v185; // ecx
  int v186; // edi
  _DWORD *v187; // eax
  int v188; // ecx
  int j; // edi
  __int16 v190; // ax
  bool v191; // sf
  int v192; // eax
  int v193; // eax
  int v194; // edx
  int v195; // ecx
  int v196; // edi
  int *v197; // eax
  _DWORD *v198; // ecx
  int v199; // edx
  _DWORD *v200; // eax
  int v201; // edx
  int v202; // ecx
  int v203; // eax
  int v204; // edx
  int v205; // ecx
  int v206; // edi
  __int16 v207; // ax
  bool v208; // sf
  int v209; // eax
  int v210; // eax
  int v211; // eax
  int v212; // edx
  int v213; // ecx
  int v214; // edi
  int *v215; // eax
  _DWORD *v216; // ecx
  int v217; // edx
  int v218; // eax
  int v219; // edx
  int v220; // ecx
  int v221; // edi
  _DWORD *v222; // eax
  int v223; // eax
  int v224; // eax
  int v225; // eax
  int v226; // edx
  int v227; // ecx
  int v228; // edi
  int *v229; // eax
  _DWORD *v230; // ecx
  int v231; // edx
  int v232; // eax
  int v233; // edx
  int v234; // ecx
  int v235; // edi
  _DWORD *v236; // eax
  __int16 v237; // ax
  bool v238; // sf
  int v239; // eax
  int v240; // eax
  int v241; // edx
  int v242; // ecx
  int v243; // edi
  int *v244; // eax
  _DWORD *v245; // ecx
  int v246; // edx
  _DWORD *v247; // eax
  int v248; // edx
  int v249; // ecx
  int v250; // eax
  int v251; // edx
  int v252; // ecx
  int v253; // edi
  __int16 v254; // ax
  bool v255; // sf
  int v256; // eax
  int v257; // eax
  int v258; // eax
  int v259; // edx
  int v260; // ecx
  int v261; // edi
  int *v262; // eax
  _DWORD *v263; // ecx
  int v264; // edx
  int v265; // eax
  int v266; // edx
  int v267; // ecx
  int v268; // edi
  _DWORD *v269; // eax
  int v270; // eax
  int v271; // eax
  int v272; // eax
  int v273; // edx
  int v274; // ecx
  int v275; // edi
  int *v276; // eax
  _DWORD *v277; // ecx
  int v278; // edx
  int v279; // eax
  int v280; // edx
  int v281; // ecx
  int v282; // edi
  _DWORD *v283; // eax
  int v284; // eax
  __int16 v285; // cx
  __int16 v286; // dx
  int v287; // eax
  int v288; // edx
  int v289; // ecx
  int v290; // edi
  int *v291; // eax
  _DWORD *v292; // ecx
  int v293; // edx
  int v294; // eax
  int v295; // edx
  int v296; // ecx
  int v297; // edi
  _DWORD *v298; // eax
  int v299; // eax
  __int16 v300; // cx
  __int16 v301; // dx
  int v302; // eax
  int v303; // eax
  int v304; // edx
  int v305; // ecx
  int v306; // edi
  int *v307; // eax
  _DWORD *v308; // ecx
  int v309; // edx
  int v310; // eax
  int v311; // edx
  int v312; // ecx
  int v313; // edi
  _DWORD *v314; // eax
  int *v315; // ecx
  int v316; // eax
  int v317; // eax
  int v318; // edx
  int v319; // ecx
  int v320; // edi
  int *v321; // eax
  _DWORD *v322; // ecx
  int v323; // edx
  int v324; // eax
  int v325; // edx
  int v326; // ecx
  int v327; // edi
  _DWORD *v328; // eax
  int v329; // eax
  __int16 v330; // cx
  __int16 v331; // dx
  int v332; // eax
  int v333; // edx
  int v334; // ecx
  int v335; // edi
  int *v336; // eax
  _DWORD *v337; // ecx
  int v338; // edx
  int v339; // eax
  int v340; // edx
  int v341; // ecx
  int v342; // edi
  _DWORD *v343; // eax
  int v344; // eax
  __int16 v345; // cx
  __int16 v346; // dx
  int v347; // eax
  int v348; // eax
  int v349; // edx
  int v350; // ecx
  int v351; // edi
  int v352; // eax
  int v353; // edx
  int v354; // ecx
  int v355; // edi
  int v356; // eax
  int v357; // eax
  int v358; // edx
  int v359; // ecx
  int v360; // edi
  int *v361; // eax
  _DWORD *v362; // ecx
  int v363; // edx
  int v364; // eax
  int v365; // edx
  int v366; // ecx
  int v367; // edi
  _DWORD *v368; // eax
  int v369; // ecx
  int k; // edi
  __int16 v371; // ax
  bool v372; // sf
  int v373; // eax
  int v374; // eax
  int v375; // edx
  int v376; // ecx
  int v377; // edi
  int *v378; // eax
  _DWORD *v379; // ecx
  int v380; // edx
  _DWORD *v381; // eax
  int v382; // edx
  int v383; // ecx
  int v384; // eax
  int v385; // edx
  int v386; // ecx
  int v387; // edi
  __int16 v388; // ax
  bool v389; // sf
  int v390; // eax
  int v391; // eax
  int v392; // eax
  int v393; // edx
  int v394; // ecx
  int v395; // edi
  int *v396; // eax
  _DWORD *v397; // ecx
  int v398; // edx
  int v399; // eax
  int v400; // edx
  int v401; // ecx
  int v402; // edi
  _DWORD *v403; // eax
  int v404; // eax
  int v405; // eax
  int v406; // eax
  int v407; // edx
  int v408; // ecx
  int v409; // edi
  int *v410; // eax
  _DWORD *v411; // ecx
  int v412; // edx
  int v413; // eax
  int v414; // edx
  int v415; // ecx
  int v416; // edi
  _DWORD *v417; // eax
  __int16 v418; // ax
  bool v419; // sf
  int v420; // eax
  int v421; // eax
  int v422; // edx
  int v423; // ecx
  int v424; // edi
  int *v425; // eax
  _DWORD *v426; // ecx
  int v427; // edx
  _DWORD *v428; // eax
  int v429; // edx
  int v430; // ecx
  int v431; // eax
  int v432; // edx
  int v433; // ecx
  int v434; // edi
  __int16 v435; // ax
  bool v436; // sf
  int v437; // eax
  int v438; // eax
  int v439; // eax
  int v440; // edx
  int v441; // ecx
  int v442; // edi
  int *v443; // eax
  _DWORD *v444; // ecx
  int v445; // edx
  int v446; // eax
  int v447; // edx
  int v448; // ecx
  int v449; // edi
  _DWORD *v450; // eax
  int v451; // eax
  int v452; // eax
  int v453; // eax
  int v454; // edx
  int v455; // ecx
  int v456; // edi
  int *v457; // eax
  _DWORD *v458; // ecx
  int v459; // edx
  int v460; // eax
  int v461; // edx
  int v462; // ecx
  int v463; // edi
  _DWORD *v464; // eax
  int v465; // eax
  __int16 v466; // cx
  __int16 v467; // dx
  int v468; // eax
  int v469; // edx
  int v470; // ecx
  int v471; // edi
  int *v472; // eax
  _DWORD *v473; // ecx
  int v474; // edx
  int v475; // eax
  int v476; // edx
  int v477; // ecx
  int v478; // edi
  _DWORD *v479; // eax
  int v480; // eax
  __int16 v481; // cx
  __int16 v482; // dx
  int v483; // eax
  int v484; // eax
  int v485; // edx
  int v486; // ecx
  int v487; // edi
  int *v488; // eax
  _DWORD *v489; // ecx
  int v490; // edx
  int v491; // eax
  int v492; // edx
  int v493; // ecx
  int v494; // edi
  _DWORD *v495; // eax
  int *v496; // ecx
  int v497; // eax
  int v498; // eax
  int v499; // edx
  int v500; // ecx
  int v501; // edi
  int *v502; // eax
  _DWORD *v503; // ecx
  int v504; // edx
  int v505; // eax
  int v506; // edx
  int v507; // ecx
  int v508; // edi
  _DWORD *v509; // eax
  int v510; // eax
  __int16 v511; // cx
  __int16 v512; // dx
  int v513; // eax
  int v514; // edx
  int v515; // ecx
  int v516; // edi
  int *v517; // eax
  _DWORD *v518; // ecx
  int v519; // edx
  int v520; // eax
  int v521; // edx
  int v522; // ecx
  int v523; // edi
  _DWORD *v524; // eax
  int v525; // eax
  __int16 v526; // cx
  __int16 v527; // dx
  int v528; // eax
  int v529; // eax
  int v530; // edx
  int v531; // ecx
  int v532; // edi
  int v533; // eax
  int v534; // edx
  int v535; // ecx
  int v536; // edi
  int v537; // eax
  int v538; // eax
  int v539; // edx
  int v540; // ecx
  int v541; // edi
  int *v542; // eax
  _DWORD *v543; // ecx
  int v544; // edx
  int v545; // eax
  int v546; // edx
  int v547; // ecx
  int v548; // edi
  _DWORD *v549; // eax
  int v550; // ecx
  int m; // edi
  __int16 v552; // ax
  bool v553; // sf
  int v554; // eax
  int v555; // eax
  int v556; // edx
  int v557; // ecx
  int v558; // edi
  int *v559; // eax
  _DWORD *v560; // ecx
  int v561; // edx
  _DWORD *v562; // eax
  int v563; // eax
  int v564; // edx
  int v565; // ecx
  int v566; // edi
  __int16 v567; // ax
  bool v568; // sf
  int v569; // eax
  int v570; // eax
  int v571; // eax
  int v572; // edx
  int v573; // ecx
  int v574; // edi
  int *v575; // eax
  _DWORD *v576; // ecx
  int v577; // edx
  int v578; // eax
  int v579; // edx
  int v580; // ecx
  int v581; // edi
  _DWORD *v582; // eax
  int v583; // eax
  int v584; // eax
  int v585; // eax
  int v586; // edx
  int v587; // ecx
  int v588; // edi
  int *v589; // eax
  _DWORD *v590; // ecx
  int v591; // edx
  int v592; // eax
  int v593; // edx
  int v594; // ecx
  int v595; // edi
  _DWORD *v596; // eax
  __int16 v597; // ax
  bool v598; // sf
  int v599; // eax
  int v600; // eax
  int v601; // edx
  int v602; // ecx
  int v603; // edi
  int *v604; // eax
  _DWORD *v605; // ecx
  int v606; // edx
  _DWORD *v607; // eax
  int v608; // eax
  int v609; // edx
  int v610; // ecx
  int v611; // edi
  __int16 v612; // ax
  bool v613; // sf
  int v614; // eax
  int v615; // eax
  int v616; // eax
  int v617; // edx
  int v618; // ecx
  int v619; // edi
  int *v620; // eax
  _DWORD *v621; // ecx
  int v622; // edx
  int v623; // eax
  int v624; // edx
  int v625; // ecx
  int v626; // edi
  _DWORD *v627; // eax
  int v628; // eax
  int v629; // eax
  int v630; // eax
  int v631; // edx
  int v632; // ecx
  int v633; // edi
  int *v634; // eax
  _DWORD *v635; // ecx
  int v636; // edx
  int v637; // eax
  int v638; // edx
  int v639; // ecx
  int v640; // edi
  _DWORD *v641; // eax
  int v642; // eax
  __int16 v643; // cx
  __int16 v644; // dx
  int v645; // eax
  int v646; // edx
  int v647; // ecx
  int v648; // edi
  int *v649; // eax
  _DWORD *v650; // ecx
  int v651; // edx
  int v652; // eax
  int v653; // edx
  int v654; // ecx
  int v655; // edi
  _DWORD *v656; // eax
  int v657; // eax
  __int16 v658; // cx
  __int16 v659; // dx
  int v660; // eax
  int v661; // eax
  int v662; // edx
  int v663; // ecx
  int v664; // edi
  int *v665; // eax
  _DWORD *v666; // ecx
  int v667; // edx
  int v668; // eax
  int v669; // edx
  int v670; // ecx
  int v671; // edi
  _DWORD *v672; // eax
  int *v673; // ecx
  int v674; // eax
  int v675; // eax
  int v676; // edx
  int v677; // ecx
  int v678; // edi
  int *v679; // eax
  _DWORD *v680; // ecx
  int v681; // edx
  int v682; // eax
  int v683; // edx
  int v684; // ecx
  int v685; // edi
  _DWORD *v686; // eax
  int v687; // eax
  __int16 v688; // cx
  __int16 v689; // dx
  int v690; // eax
  int v691; // edx
  int v692; // ecx
  int v693; // edi
  int *v694; // eax
  _DWORD *v695; // ecx
  int v696; // edx
  int v697; // eax
  int v698; // edx
  int v699; // ecx
  int v700; // edi
  _DWORD *v701; // eax
  int v702; // eax
  __int16 v703; // cx
  __int16 v704; // dx
  int v705; // eax
  int v706; // eax
  int v707; // edx
  int v708; // ecx
  int v709; // edi
  int v710; // eax
  int v711; // edx
  int v712; // ecx
  int v713; // edi
  int v714; // eax
  int v715; // eax
  int v716; // edx
  int v717; // ecx
  int v718; // edi
  int *v719; // eax
  _DWORD *v720; // ecx
  int v721; // edx
  int v722; // eax
  int v723; // edx
  int v724; // ecx
  int v725; // edi
  _DWORD *v726; // eax
  int v727; // ecx
  int n; // edi
  __int16 v729; // ax
  bool v730; // sf
  int v731; // eax
  int v732; // eax
  int v733; // edx
  int v734; // ecx
  int v735; // edi
  int *v736; // eax
  _DWORD *v737; // ecx
  int v738; // edx
  _DWORD *v739; // eax
  int v740; // eax
  int v741; // edx
  int v742; // ecx
  int v743; // edi
  __int16 v744; // ax
  bool v745; // sf
  int v746; // eax
  int v747; // eax
  int v748; // eax
  int v749; // edx
  int v750; // ecx
  int v751; // edi
  int *v752; // eax
  _DWORD *v753; // ecx
  int v754; // edx
  int v755; // eax
  int v756; // edx
  int v757; // ecx
  int v758; // edi
  _DWORD *v759; // eax
  int v760; // eax
  int v761; // eax
  int v762; // eax
  int v763; // edx
  int v764; // ecx
  int v765; // edi
  int *v766; // eax
  _DWORD *v767; // ecx
  int v768; // edx
  int v769; // eax
  int v770; // edx
  int v771; // ecx
  int v772; // edi
  _DWORD *v773; // eax
  __int16 v774; // ax
  bool v775; // sf
  int v776; // eax
  int v777; // eax
  int v778; // edx
  int v779; // ecx
  int v780; // edi
  int *v781; // eax
  _DWORD *v782; // ecx
  int v783; // edx
  _DWORD *v784; // eax
  int v785; // eax
  int v786; // edx
  int v787; // ecx
  int v788; // edi
  __int16 v789; // ax
  int v790; // eax
  int v791; // eax
  int v792; // edx
  int v793; // ecx
  int v794; // edi
  int *v795; // eax
  _DWORD *v796; // ecx
  int v797; // edx
  int v798; // eax
  int v799; // edx
  int v800; // ecx
  int v801; // edi
  _DWORD *v802; // eax
  int v803; // eax
  int v804; // eax
  int v805; // edx
  int v806; // ecx
  int v807; // edi
  int *v808; // eax
  _DWORD *v809; // ecx
  int v810; // edx
  int v811; // eax
  int v812; // edx
  int v813; // ecx
  int v814; // edi
  _DWORD *v815; // eax
  int v816; // eax
  __int16 v817; // cx
  __int16 v818; // dx
  int v819; // eax
  int v820; // edx
  int v821; // ecx
  int v822; // edi
  int *v823; // eax
  _DWORD *v824; // ecx
  int v825; // edx
  int v826; // eax
  int v827; // edx
  int v828; // ecx
  int v829; // edi
  _DWORD *v830; // eax
  int v831; // eax
  __int16 v832; // cx
  __int16 v833; // dx
  int v834; // eax
  int v835; // eax
  int v836; // edx
  int v837; // ecx
  int v838; // edi
  int *v839; // eax
  _DWORD *v840; // ecx
  int v841; // edx
  int v842; // eax
  int v843; // edx
  int v844; // ecx
  int v845; // edi
  _DWORD *v846; // eax
  int *v847; // ecx
  int v848; // eax
  int v849; // eax
  int v850; // edx
  int v851; // ecx
  int v852; // edi
  int *v853; // eax
  _DWORD *v854; // ecx
  int v855; // edx
  int v856; // eax
  int v857; // edx
  int v858; // ecx
  int v859; // edi
  _DWORD *v860; // eax
  int v861; // eax
  __int16 v862; // cx
  __int16 v863; // dx
  int v864; // eax
  int v865; // edx
  int v866; // ecx
  int v867; // edi
  int *v868; // eax
  _DWORD *v869; // ecx
  int v870; // edx
  int v871; // eax
  int v872; // edx
  int v873; // ecx
  int v874; // edi
  _DWORD *v875; // eax
  int v876; // eax
  __int16 v877; // cx
  __int16 v878; // dx
  int v879; // eax
  int v880; // eax
  int v881; // edx
  int v882; // ecx
  int v883; // edi
  int v884; // eax
  int v885; // eax
  int v886; // eax
  int *v887; // edx
  int v888; // eax
  CCBUI *v889; // ecx
  int ii; // edi
  int v891; // eax
  int v892; // eax
  int v893; // eax
  int v894; // eax
  int *v895; // edx
  int v896; // eax
  int v897; // eax
  int v898; // eax
  int v899; // eax
  int *v900; // edx
  int v901; // eax
  __int16 v902; // cx
  __int16 v903; // dx
  int v904; // eax
  int v905; // eax
  int v906; // eax
  __int16 v907; // cx
  __int16 v908; // dx
  int v909; // eax
  int v910; // eax
  int *v911; // edx
  int *v912; // ecx
  int v913; // eax
  int v914; // eax
  int *v915; // edx
  int v916; // eax
  __int16 v917; // cx
  __int16 v918; // dx
  int v919; // eax
  int v920; // eax
  int v921; // eax
  __int16 v922; // cx
  __int16 v923; // dx
  int v924; // eax
  int v925; // eax
  int *v926; // edx
  int v927; // eax
  int v928; // eax
  int *v929; // edx
  int result; // eax
  _WORD *v931; // [esp+0x24] [ebp-D3Ch]
  int v932; // [esp+0x52C] [ebp-0x834]
  int v933; // [esp+0x53C] [ebp-0x824]
  int v934; // [esp+0x54C] [ebp-0x814]
  int v935; // [esp+0x55C] [ebp-0x804]
  int v936; // [esp+0x56C] [ebp-0x7F4]
  int v937; // [esp+0x57C] [ebp-0x7E4]
  int v938; // [esp+0x58C] [ebp-0x7D4]
  int v939; // [esp+0x59C] [ebp-0x7C4]
  int v940; // [esp+0x5AC] [ebp-0x7B4]
  int v941; // [esp+0x5BC] [ebp-0x7A4]
  int v942; // [esp+0x5CC] [ebp-0x794]
  int v943; // [esp+0x5DC] [ebp-0x784]
  int v944; // [esp+0x5EC] [ebp-0x774]
  int v945; // [esp+0x5FC] [ebp-0x764]
  int v946; // [esp+0x60C] [ebp-0x754]
  int v947; // [esp+0x61C] [ebp-0x744]
  int v948; // [esp+0x62C] [ebp-0x734]
  int v949; // [esp+0x63C] [ebp-0x724]
  int v950; // [esp+0x64C] [ebp-0x714]
  int v951; // [esp+0x65C] [ebp-0x704]
  int v952; // [esp+0x66C] [ebp-0x6F4]
  int v953; // [esp+0x67C] [ebp-0x6E4]
  int v954; // [esp+0x68C] [ebp-0x6D4]
  int v955; // [esp+0x69C] [ebp-0x6C4]
  int v956; // [esp+0x6AC] [ebp-0x6B4]
  int v957; // [esp+0x6BC] [ebp-0x6A4]
  int v958; // [esp+0x6CC] [ebp-0x694]
  int v959; // [esp+0x6DC] [ebp-0x684]
  int v960; // [esp+0x6EC] [ebp-0x674]
  int v961; // [esp+0x6FC] [ebp-0x664]
  int v962; // [esp+0x70C] [ebp-0x654]
  int v963; // [esp+0x71C] [ebp-0x644]
  int v964; // [esp+0x72C] [ebp-0x634]
  int v965; // [esp+0x73C] [ebp-0x624]
  int v966; // [esp+0x74C] [ebp-0x614]
  int v967; // [esp+0x75C] [ebp-0x604]
  int v968; // [esp+0x76C] [ebp-0x5F4]
  int v969; // [esp+0x77C] [ebp-0x5E4]
  int v970; // [esp+0x78C] [ebp-0x5D4]
  int v971; // [esp+0x79C] [ebp-0x5C4]
  int v972; // [esp+0x7AC] [ebp-0x5B4]
  int v973; // [esp+0x7BC] [ebp-0x5A4]
  int v974; // [esp+0x7CC] [ebp-0x594]
  int v975; // [esp+0x7DC] [ebp-0x584]
  int v976; // [esp+0x7EC] [ebp-0x574]
  int v977; // [esp+0x7FC] [ebp-0x564]
  int v978; // [esp+0x80C] [ebp-0x554]
  int v979; // [esp+0x81C] [ebp-0x544]
  int v980; // [esp+0x82C] [ebp-0x534]
  int v981; // [esp+0x83C] [ebp-0x524]
  int v982; // [esp+0x84C] [ebp-0x514]
  int v983; // [esp+0x85C] [ebp-0x504]
  int v984; // [esp+0x86C] [ebp-0x4F4]
  int v985; // [esp+0x87C] [ebp-0x4E4]
  int v986; // [esp+0x88C] [ebp-0x4D4]
  int v987; // [esp+0x89C] [ebp-0x4C4]
  int v988; // [esp+0x8AC] [ebp-0x4B4]
  int v989; // [esp+0x8BC] [ebp-0x4A4]
  int v990; // [esp+0x8CC] [ebp-0x494]
  int v991; // [esp+0x8DC] [ebp-0x484]
  int v992; // [esp+0x8EC] [ebp-0x474]
  int v993; // [esp+0x8FC] [ebp-0x464]
  int v994; // [esp+0x90C] [ebp-0x454]
  int v995; // [esp+0x91C] [ebp-0x444]
  int v996; // [esp+0x92C] [ebp-0x434]
  int v997; // [esp+0x93C] [ebp-0x424]
  int v998; // [esp+0x94C] [ebp-0x414]
  int v999; // [esp+0x95C] [ebp-0x404]
  int v1000; // [esp+0x96C] [ebp-0x3F4]
  int v1001; // [esp+0x97C] [ebp-0x3E4]
  int v1002; // [esp+0x98C] [ebp-0x3D4]
  int v1003; // [esp+0x99C] [ebp-0x3C4]
  int v1004; // [esp+0x9AC] [ebp-0x3B4]
  int v1005; // [esp+0x9BC] [ebp-0x3A4]
  int v1006; // [esp+0x9CC] [ebp-0x394]
  int v1007; // [esp+0x9DC] [ebp-0x384]
  int v1008; // [esp+0x9EC] [ebp-0x374]
  int v1009; // [esp+0x9FC] [ebp-0x364]
  int v1010; // [esp+A0Ch] [ebp-0x354]
  int v1011; // [esp+A1Ch] [ebp-0x344]
  int v1012; // [esp+A2Ch] [ebp-0x334]
  int v1013; // [esp+A3Ch] [ebp-0x324]
  int v1014; // [esp+A4Ch] [ebp-0x314]
  int v1015; // [esp+A5Ch] [ebp-0x304]
  int v1016; // [esp+A6Ch] [ebp-0x2F4]
  int v1017; // [esp+A7Ch] [ebp-0x2E4]
  int v1018; // [esp+A8Ch] [ebp-0x2D4]
  int v1019; // [esp+A9Ch] [ebp-0x2C4]
  int v1020; // [esp+AACh] [ebp-0x2B4]
  int v1021; // [esp+ABCh] [ebp-0x2A4]
  int v1022; // [esp+ACCh] [ebp-0x294]
  int v1023; // [esp+ADCh] [ebp-0x284]
  int v1024; // [esp+AECh] [ebp-0x274]
  int v1025; // [esp+AFCh] [ebp-0x264]
  int v1026; // [esp+B0Ch] [ebp-0x254]
  int v1027; // [esp+B1Ch] [ebp-0x244]
  int v1028; // [esp+B2Ch] [ebp-0x234]
  int v1029; // [esp+B3Ch] [ebp-0x224]
  int v1030; // [esp+B4Ch] [ebp-0x214]
  int v1031; // [esp+B5Ch] [ebp-0x204]
  int v1032; // [esp+B6Ch] [ebp-0x1F4]
  int v1033; // [esp+B7Ch] [ebp-0x1E4]
  int v1034; // [esp+B8Ch] [ebp-0x1D4]
  int v1035; // [esp+B9Ch] [ebp-0x1C4]
  int v1036; // [esp+BACh] [ebp-0x1B4]
  int v1037; // [esp+BBCh] [ebp-0x1A4]
  int v1038; // [esp+BCCh] [ebp-0x194]
  int v1039; // [esp+BDCh] [ebp-0x184]
  int v1040; // [esp+BECh] [ebp-0x174]
  int v1041; // [esp+BFCh] [ebp-0x164]
  int v1042; // [esp+C0Ch] [ebp-0x154]
  int v1043; // [esp+C1Ch] [ebp-0x144]
  int v1044; // [esp+C2Ch] [ebp-0x134]
  int v1045; // [esp+C3Ch] [ebp-0x124]
  int v1046; // [esp+C4Ch] [ebp-0x114]
  int v1047; // [esp+C5Ch] [ebp-0x104]
  int v1048; // [esp+C6Ch] [ebp-F4h]
  char pData[16]; // [esp+C70h] [ebp-F0h] BYREF
  char v1050[16]; // [esp+C80h] [ebp-E0h] BYREF
  int v1051[4]; // [esp+C90h] [ebp-D0h] BYREF
  int nCol[4]; // [esp+CA0h] [ebp-C0h] BYREF
  char v1053[16]; // [esp+CB0h] [ebp-B0h] BYREF
  int v1054[4]; // [esp+CC0h] [ebp-A0h] BYREF
  int v1055[4]; // [esp+CD0h] [ebp-0x90] BYREF
  int v1056[4]; // [esp+CE0h] [ebp-0x80] BYREF
  char v1057[16]; // [esp+CF0h] [ebp-0x70] BYREF
  char v1058[16]; // [esp+D00h] [ebp-0x60] BYREF
  int v1059[4]; // [esp+D10h] [ebp-0x50] BYREF
  char v1060[16]; // [esp+D20h] [ebp-0x40] BYREF
  char v1061[16]; // [esp+D30h] [ebp-0x30] BYREF
  char v1062[16]; // [esp+D40h] [ebp-0x20] BYREF
  int v1063[4]; // [esp+D50h] [ebp-0x10] BYREF

  v3 = (_WORD *)*(&this->dwWeaponWU + (_DWORD)arg0 + 3666);
  v931 = v3;
  if ( *((CCBUIPanel **)&this->m_bWPXS + 1258) != arg0 )
  {
    memset(&this->m_bWPXS + 1198, 0, 0xF0u);
    memset(&this->m_bWPXS + 1259, 0, 0xF0u);
    *(&this->m_bWPXS + 1258) = (int)arg0;
  }
  *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = 0;
  while ( 2 )
  {
    if ( !*((_BYTE *)&this->dwWeaponWU + *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 25132) )
      goto LABEL_406;
    *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[252] = 0;
    do
    {
      (**((void ( ***)(int *, _DWORD))&this->m_bWPXS
        + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
        + 45 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[252]
        + 5399))(
        &this->m_bWPXS
      + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
      + 45 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[252]
      + 5399,
        0);
      *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[256] = 0;
      do
      {
        (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
          + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
          + 304 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[252]
          + 38 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[256]
          + 6285))(
          &this->dwWeaponWU
        + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
        + 304 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[252]
        + 38 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[256]
        + 6285,
          0);
        v4 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[256] + 1;
        *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[256] = v4;
      }
      while ( v4 < 8 );
      v5 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[252] + 1;
      *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[252] = v5;
    }
    while ( v5 < 6 );
    switch ( *((_BYTE *)v3 + 612) )
    {
      case 7:
        v6 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        if ( !*((_BYTE *)v3 + v6 + 614) )
          goto LABEL_406;
        if ( !*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v6 + 3) )
        {
          ((UIStatic *)(&this->m_bWPXS + 270 * v6 + 5399))->CreateFromTemplate();
          for ( i = 0; i < 8; ++i )
            (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 38 * i
              + 6285))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 38 * i + 6285,
              0);
          v8 = v3[325];
          v9 = v8 < 0;
          v10 = v8 <= 0;
          v11 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( v10 )
          {
            if ( !v9 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v11 + 5036) = 0;
LABEL_20:
              v26 = v931[327];
              v27 = v26 < 0;
              v10 = v26 <= 0;
              v28 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                v42 = 3 * v28;
                if ( v27 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v42 + 5041) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5037) = 0;
                  v43 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v43 + 4796) )
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v43 + 6475);
                    v44 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v45 = *(&this->m_bWPXS + 192 * v44 + 262);
                    v46 = *(&this->m_bWPXS + 192 * v44 + 263);
                    v47 = *(&this->m_bWPXS + 192 * v44 + 264);
                    v1000 = *(&this->m_bWPXS + 192 * v44 + 265);
                    v48 = &this->m_bWPXS + 624 * v44 + 2344;
                    v48[2] = v46;
                    v49 = v48 + 1;
                    v48[3] = v47;
                    v48[1] = v45;
                    v50 = v1000;
                  }
                  else
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v43 + 6475);
                    v51 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v52 = *(&this->m_bWPXS + 192 * v51 + 254);
                    v53 = *(&this->m_bWPXS + 192 * v51 + 255);
                    v54 = *(&this->m_bWPXS + 192 * v51 + 256);
                    v938 = *(&this->m_bWPXS + 192 * v51 + 257);
                    v48 = &this->m_bWPXS + 624 * v51 + 2344;
                    v48[2] = v53;
                    v49 = v48 + 1;
                    v48[3] = v54;
                    v48[1] = v52;
                    v50 = v938;
                  }
                  v48[4] = v50;
                  v55 = v48 + 5;
                  *v55 = *v49;
                  v55[1] = v49[1];
                  v55[2] = v49[2];
                  v55[3] = v49[3];
                  (**((void ( ***)(int *, int))&this->dwWeaponWU
                    + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                    + 6475))(
                    &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6475,
                    1);
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v42 + 5037) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v28 + 5037) = 1;
                v29 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v29 + 4792) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v29 + 6323);
                  v30 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v31 = *(&this->m_bWPXS + 192 * v30 + 246);
                  v32 = *(&this->m_bWPXS + 192 * v30 + 247);
                  v33 = *(&this->m_bWPXS + 192 * v30 + 248);
                  v1044 = *(&this->m_bWPXS + 192 * v30 + 249);
                  v34 = &this->m_bWPXS + 624 * v30 + 2292;
                  v34[2] = v32;
                  v35 = v34 + 1;
                  v34[3] = v33;
                  v34[1] = v31;
                  v36 = v1044;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v29 + 6323);
                  v37 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v38 = *(&this->m_bWPXS + 192 * v37 + 238);
                  v39 = *(&this->m_bWPXS + 192 * v37 + 239);
                  v40 = *(&this->m_bWPXS + 192 * v37 + 240);
                  v936 = *(&this->m_bWPXS + 192 * v37 + 241);
                  v34 = &this->m_bWPXS + 624 * v37 + 2292;
                  v34[2] = v39;
                  v35 = v34 + 1;
                  v34[3] = v40;
                  v34[1] = v38;
                  v36 = v936;
                }
                v34[4] = v36;
                v41 = v34 + 5;
                *v41 = *v35;
                v41[1] = v35[1];
                v41[2] = v35[2];
                v41[3] = v35[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 6323))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6323,
                  1);
              }
              v56 = v931[326];
              v57 = v56 < 0;
              v10 = v56 <= 0;
              v58 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                if ( !v57 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v58 + 5038) = 0;
                  goto LABEL_37;
                }
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v58 + 6513))(
                  &this->dwWeaponWU + 1824 * v58 + 6513,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4798) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5042) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5038) = 0;
                v69 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v70 = *(&this->m_bWPXS + 192 * v69 + 262);
                v71 = *(&this->m_bWPXS + 192 * v69 + 263);
                v72 = *(&this->m_bWPXS + 192 * v69 + 264);
                v940 = *(&this->m_bWPXS + 192 * v69 + 265);
                v63 = &this->m_bWPXS + 624 * v69 + 2357;
                v63[2] = v71;
                v64 = v63 + 1;
                v63[3] = v72;
                v63[1] = v70;
                v65 = v940;
              }
              else
              {
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v58 + 6361))(
                  &this->dwWeaponWU + 1824 * v58 + 6361,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4794) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5038) = 1;
                v59 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v60 = *(&this->m_bWPXS + 192 * v59 + 246);
                v61 = *(&this->m_bWPXS + 192 * v59 + 247);
                v62 = *(&this->m_bWPXS + 192 * v59 + 248);
                v1032 = *(&this->m_bWPXS + 192 * v59 + 249);
                v63 = &this->m_bWPXS + 624 * v59 + 2305;
                v63[2] = v61;
                v64 = v63 + 1;
                v63[3] = v62;
                v63[1] = v60;
                v65 = v1032;
              }
              v63[4] = v65;
              v66 = v63 + 5;
              *v66 = *v64;
              v66[1] = v64[1];
              v67 = v64[2];
              v68 = v64[3];
              v66[2] = v67;
              v66[3] = v68;
LABEL_37:
              v73 = v931[328];
              v74 = v73 < 0;
              v10 = v73 <= 0;
              v75 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( !v10 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v75 + 5039) = 1;
                v76 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v76 + 4794) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v76 + 6399);
                  v77 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v78 = *(&this->m_bWPXS + 192 * v77 + 238);
                  v79 = *(&this->m_bWPXS + 192 * v77 + 239);
                  v80 = *(&this->m_bWPXS + 192 * v77 + 240);
                  v1002 = *(&this->m_bWPXS + 192 * v77 + 241);
                  v81 = &this->m_bWPXS + 624 * v77 + 2318;
                  v81[2] = v79;
                  v82 = v81 + 1;
                  v81[3] = v80;
                  v81[1] = v78;
                  v83 = v1002;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v76 + 6399);
                  v84 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v85 = *(&this->m_bWPXS + 192 * v84 + 250);
                  v86 = *(&this->m_bWPXS + 192 * v84 + 251);
                  v87 = *(&this->m_bWPXS + 192 * v84 + 252);
                  v942 = *(&this->m_bWPXS + 192 * v84 + 253);
                  v81 = &this->m_bWPXS + 624 * v84 + 2318;
                  v81[2] = v86;
                  v82 = v81 + 1;
                  v81[3] = v87;
                  v81[1] = v85;
                  v83 = v942;
                }
                v81[4] = v83;
                v88 = v81 + 5;
                *v88 = *v82;
                v88[1] = v82[1];
                v88[2] = v82[2];
                v88[3] = v82[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 6399))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6399,
                  1);
                goto LABEL_78;
              }
              v89 = 3 * v75;
              if ( !v74 )
              {
                *((_BYTE *)&this->m_bWPXS + 16 * v89 + 5039) = 0;
                goto LABEL_78;
              }
              *((_BYTE *)&this->m_bWPXS + 16 * v89 + 5043) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5039) = 0;
              v90 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v90 + 4798) )
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v90 + 6551);
                v91 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v92 = *(&this->m_bWPXS + 192 * v91 + 254);
                v93 = *(&this->m_bWPXS + 192 * v91 + 255);
                v94 = *(&this->m_bWPXS + 192 * v91 + 256);
                v1046 = *(&this->m_bWPXS + 192 * v91 + 257);
                v95 = &this->m_bWPXS + 624 * v91 + 2370;
                v95[2] = v93;
                v96 = v95 + 1;
                v95[3] = v94;
                v95[1] = v92;
                v97 = v1046;
              }
              else
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v90 + 6551);
                v98 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v99 = *(&this->m_bWPXS + 192 * v98 + 266);
                v100 = *(&this->m_bWPXS + 192 * v98 + 267);
                v101 = *(&this->m_bWPXS + 192 * v98 + 268);
                v944 = *(&this->m_bWPXS + 192 * v98 + 269);
                v95 = &this->m_bWPXS + 624 * v98 + 2370;
                v95[2] = v100;
                v96 = v95 + 1;
                v95[3] = v101;
                v95[1] = v99;
                v97 = v944;
              }
LABEL_46:
              v95[4] = v97;
              v102 = v95 + 5;
              *v102 = *v96;
              v102[1] = v96[1];
              v102[2] = v96[2];
              v102[3] = v96[3];
              (**((void ( ***)(int *, int))&this->dwWeaponWU
                + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                + 6551))(
                &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6551,
                1);
LABEL_78:
              (**((void ( ***)(int *, int))&this->m_bWPXS
                + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                + 5399))(
                &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5399,
                1);
              v3 = v931;
              goto LABEL_406;
            }
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v11 + 6437))(
              &this->dwWeaponWU + 1824 * v11 + 6437,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4796) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5040) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5036) = 0;
            v22 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v23 = *(&this->m_bWPXS + 192 * v22 + 254);
            v24 = *(&this->m_bWPXS + 192 * v22 + 255);
            v25 = *(&this->m_bWPXS + 192 * v22 + 256);
            v934 = *(&this->m_bWPXS + 192 * v22 + 257);
            v16 = &this->m_bWPXS + 624 * v22 + 2331;
            v16[2] = v24;
            v17 = v16 + 1;
            v16[3] = v25;
            v16[1] = v23;
            v18 = v934;
          }
          else
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v11 + 6285))(
              &this->dwWeaponWU + 1824 * v11 + 6285,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4792) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5036) = 1;
            v12 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v13 = *(&this->m_bWPXS + 192 * v12 + 238);
            v14 = *(&this->m_bWPXS + 192 * v12 + 239);
            v15 = *(&this->m_bWPXS + 192 * v12 + 240);
            v954 = *(&this->m_bWPXS + 192 * v12 + 241);
            v16 = &this->m_bWPXS + 624 * v12 + 2279;
            v16[2] = v14;
            v17 = v16 + 1;
            v16[3] = v15;
            v16[1] = v13;
            v18 = v954;
          }
          v16[4] = v18;
          v19 = v16 + 5;
          *v19 = *v17;
          v19[1] = v17[1];
          v20 = v17[2];
          v21 = v17[3];
          v19[2] = v20;
          v19[3] = v21;
          goto LABEL_20;
        }
        ((UIStatic *)(&this->m_bWPXS + 270 * v6 + 5399))->CreateFromTemplate();
        v103 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v104 = v3[325];
        v105 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v103 + 3) + 650);
        if ( v104 >= v105 )
        {
          if ( v104 <= v105 )
            goto LABEL_53;
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v103 + 6285))(
            &this->dwWeaponWU + 1824 * v103 + 6285,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4792) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5036) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5040) = 0;
          v113 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v114 = *(&this->m_bWPXS + 192 * v113 + 238);
          v115 = *(&this->m_bWPXS + 192 * v113 + 239);
          v116 = *(&this->m_bWPXS + 192 * v113 + 240);
          v946 = *(&this->m_bWPXS + 192 * v113 + 241);
          v110 = &this->m_bWPXS + 624 * v113 + 2279;
          v110[2] = v115;
          v111 = v110 + 1;
          v110[3] = v116;
          v110[1] = v114;
          v112 = v946;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v103 + 6437))(
            &this->dwWeaponWU + 1824 * v103 + 6437,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4796) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5040) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5036) = 0;
          v106 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v107 = *(&this->m_bWPXS + 192 * v106 + 254);
          v108 = *(&this->m_bWPXS + 192 * v106 + 255);
          v109 = *(&this->m_bWPXS + 192 * v106 + 256);
          v1004 = *(&this->m_bWPXS + 192 * v106 + 257);
          v110 = &this->m_bWPXS + 624 * v106 + 2331;
          v110[2] = v108;
          v111 = v110 + 1;
          v110[3] = v109;
          v110[1] = v107;
          v112 = v1004;
        }
        v110[4] = v112;
        v117 = v110 + 5;
        *v117 = *v111;
        v117[1] = v111[1];
        v117[2] = v111[2];
        v117[3] = v111[3];
LABEL_53:
        v118 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v119 = v931[327];
        v120 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v118 + 3) + 654);
        if ( v119 >= v120 )
        {
          if ( v119 <= v120 )
            goto LABEL_64;
          *((_BYTE *)&this->m_bWPXS + 48 * v118 + 5037) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5041) = 0;
          v135 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v135 + 4792) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v135 + 6323);
            v136 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v137 = *(&this->m_bWPXS + 192 * v136 + 246);
            v138 = *(&this->m_bWPXS + 192 * v136 + 247);
            v139 = *(&this->m_bWPXS + 192 * v136 + 248);
            v1006 = *(&this->m_bWPXS + 192 * v136 + 249);
            v140 = &this->m_bWPXS + 624 * v136 + 2292;
            v140[2] = v138;
            v141 = v140 + 1;
            v140[3] = v139;
            v140[1] = v137;
            v142 = v1006;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v135 + 6323);
            v143 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v144 = *(&this->m_bWPXS + 192 * v143 + 238);
            v145 = *(&this->m_bWPXS + 192 * v143 + 239);
            v146 = *(&this->m_bWPXS + 192 * v143 + 240);
            v950 = *(&this->m_bWPXS + 192 * v143 + 241);
            v140 = &this->m_bWPXS + 624 * v143 + 2292;
            v140[2] = v145;
            v141 = v140 + 1;
            v140[3] = v146;
            v140[1] = v144;
            v142 = v950;
          }
          v140[4] = v142;
          v147 = v140 + 5;
          *v147 = *v141;
          v147[1] = v141[1];
          v147[2] = v141[2];
          v147[3] = v141[3];
          v134 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6323;
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v118 + 5041) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5037) = 0;
          v121 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v121 + 4796) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v121 + 6475);
            v122 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v123 = *(&this->m_bWPXS + 192 * v122 + 262);
            v124 = *(&this->m_bWPXS + 192 * v122 + 263);
            v125 = *(&this->m_bWPXS + 192 * v122 + 264);
            v1034 = *(&this->m_bWPXS + 192 * v122 + 265);
            v126 = &this->m_bWPXS + 624 * v122 + 2344;
            v126[2] = v124;
            v127 = v126 + 1;
            v126[3] = v125;
            v126[1] = v123;
            v128 = v1034;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v121 + 6475);
            v129 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v130 = *(&this->m_bWPXS + 192 * v129 + 254);
            v131 = *(&this->m_bWPXS + 192 * v129 + 255);
            v132 = *(&this->m_bWPXS + 192 * v129 + 256);
            v948 = *(&this->m_bWPXS + 192 * v129 + 257);
            v126 = &this->m_bWPXS + 624 * v129 + 2344;
            v126[2] = v131;
            v127 = v126 + 1;
            v126[3] = v132;
            v126[1] = v130;
            v128 = v948;
          }
          v126[4] = v128;
          v133 = v126 + 5;
          *v133 = *v127;
          v133[1] = v127[1];
          v133[2] = v127[2];
          v133[3] = v127[3];
          v134 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6475;
        }
        (*(void ( **)(int *, int))*v134)(v134, 1);
LABEL_64:
        v148 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v149 = v931[326];
        v150 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v148 + 3) + 652);
        if ( v149 >= v150 )
        {
          if ( v149 <= v150 )
          {
LABEL_69:
            v163 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v164 = v931[328];
            v165 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v163 + 3) + 656);
            if ( v164 >= v165 )
            {
              if ( v164 > v165 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v163 + 5039) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5043) = 0;
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 6399))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6399,
                  1);
                v175 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v175 + 4794) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v175 + 6399);
                  v176 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v177 = *(&this->m_bWPXS + 192 * v176 + 238);
                  v178 = *(&this->m_bWPXS + 192 * v176 + 239);
                  v179 = *(&this->m_bWPXS + 192 * v176 + 240);
                  v1045 = *(&this->m_bWPXS + 192 * v176 + 241);
                  v180 = &this->m_bWPXS + 624 * v176 + 2318;
                  v180[2] = v178;
                  v181 = v180 + 1;
                  v180[3] = v179;
                  v180[1] = v177;
                  v182 = v1045;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v175 + 6399);
                  v183 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v184 = *(&this->m_bWPXS + 192 * v183 + 250);
                  v185 = *(&this->m_bWPXS + 192 * v183 + 251);
                  v186 = *(&this->m_bWPXS + 192 * v183 + 252);
                  v956 = *(&this->m_bWPXS + 192 * v183 + 253);
                  v180 = &this->m_bWPXS + 624 * v183 + 2318;
                  v180[2] = v185;
                  v181 = v180 + 1;
                  v180[3] = v186;
                  v180[1] = v184;
                  v182 = v956;
                }
                v180[4] = v182;
                v187 = v180 + 5;
                *v187 = *v181;
                v187[1] = v181[1];
                v187[2] = v181[2];
                v187[3] = v181[3];
              }
              goto LABEL_78;
            }
            *((_BYTE *)&this->m_bWPXS + 48 * v163 + 5043) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5039) = 0;
            v166 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v166 + 4798) )
            {
              sub_445FA0(&this->dwWeaponWU + 1824 * v166 + 6551);
              v167 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v168 = *(&this->m_bWPXS + 192 * v167 + 254);
              v169 = *(&this->m_bWPXS + 192 * v167 + 255);
              v170 = *(&this->m_bWPXS + 192 * v167 + 256);
              v1008 = *(&this->m_bWPXS + 192 * v167 + 257);
              v95 = &this->m_bWPXS + 624 * v167 + 2370;
              v95[2] = v169;
              v96 = v95 + 1;
              v95[3] = v170;
              v95[1] = v168;
              v97 = v1008;
            }
            else
            {
              sub_445FA0(&this->dwWeaponWU + 1824 * v166 + 6551);
              v171 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v172 = *(&this->m_bWPXS + 192 * v171 + 266);
              v173 = *(&this->m_bWPXS + 192 * v171 + 267);
              v174 = *(&this->m_bWPXS + 192 * v171 + 268);
              v932 = *(&this->m_bWPXS + 192 * v171 + 269);
              v95 = &this->m_bWPXS + 624 * v171 + 2370;
              v95[2] = v173;
              v96 = v95 + 1;
              v95[3] = v174;
              v95[1] = v172;
              v97 = v932;
            }
            goto LABEL_46;
          }
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v148 + 6361))(
            &this->dwWeaponWU + 1824 * v148 + 6361,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4794) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5038) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5042) = 0;
          v158 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v159 = *(&this->m_bWPXS + 192 * v158 + 246);
          v160 = *(&this->m_bWPXS + 192 * v158 + 247);
          v161 = *(&this->m_bWPXS + 192 * v158 + 248);
          v952 = *(&this->m_bWPXS + 192 * v158 + 249);
          v155 = &this->m_bWPXS + 624 * v158 + 2305;
          v155[2] = v160;
          v156 = v155 + 1;
          v155[3] = v161;
          v155[1] = v159;
          v157 = v952;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v148 + 6513))(
            &this->dwWeaponWU + 1824 * v148 + 6513,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4798) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5042) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5038) = 0;
          v151 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v152 = *(&this->m_bWPXS + 192 * v151 + 262);
          v153 = *(&this->m_bWPXS + 192 * v151 + 263);
          v154 = *(&this->m_bWPXS + 192 * v151 + 264);
          v1048 = *(&this->m_bWPXS + 192 * v151 + 265);
          v155 = &this->m_bWPXS + 624 * v151 + 2357;
          v155[2] = v153;
          v156 = v155 + 1;
          v155[3] = v154;
          v155[1] = v152;
          v157 = v1048;
        }
        v155[4] = v157;
        v162 = v155 + 5;
        *v162 = *v156;
        v162[1] = v156[1];
        v162[2] = v156[2];
        v162[3] = v156[3];
        goto LABEL_69;
      case 8:
        v188 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        if ( !*((_BYTE *)v3 + v188 + 614) )
          goto LABEL_406;
        if ( !*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v188) )
        {
          ((UIStatic *)(&this->m_bWPXS + 270 * v188 + 5534))->CreateFromTemplate();
          for ( j = 0; j < 8; ++j )
            (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 38 * j
              + 7197))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 38 * j + 7197,
              0);
          v190 = v3[325];
          v191 = v190 < 0;
          v10 = v190 <= 0;
          v192 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( v10 )
          {
            if ( !v191 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v192 + 5060) = 0;
LABEL_89:
              v207 = v931[327];
              v208 = v207 < 0;
              v10 = v207 <= 0;
              v209 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                v223 = 3 * v209;
                if ( v208 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v223 + 5065) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5061) = 0;
                  v224 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v224 + 4820) )
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v224 + 7387);
                    v225 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v226 = *(&this->m_bWPXS + 192 * v225 + 358);
                    v227 = *(&this->m_bWPXS + 192 * v225 + 359);
                    v228 = *(&this->m_bWPXS + 192 * v225 + 360);
                    v1012 = *(&this->m_bWPXS + 192 * v225 + 361);
                    v229 = &this->m_bWPXS + 624 * v225 + 2656;
                    v229[2] = v227;
                    v230 = v229 + 1;
                    v229[3] = v228;
                    v229[1] = v226;
                    v231 = v1012;
                  }
                  else
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v224 + 7387);
                    v232 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v233 = *(&this->m_bWPXS + 192 * v232 + 350);
                    v234 = *(&this->m_bWPXS + 192 * v232 + 351);
                    v235 = *(&this->m_bWPXS + 192 * v232 + 352);
                    v962 = *(&this->m_bWPXS + 192 * v232 + 353);
                    v229 = &this->m_bWPXS + 624 * v232 + 2656;
                    v229[2] = v234;
                    v230 = v229 + 1;
                    v229[3] = v235;
                    v229[1] = v233;
                    v231 = v962;
                  }
                  v229[4] = v231;
                  v236 = v229 + 5;
                  *v236 = *v230;
                  v236[1] = v230[1];
                  v236[2] = v230[2];
                  v236[3] = v230[3];
                  (**((void ( ***)(int *, int))&this->dwWeaponWU
                    + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                    + 7387))(
                    &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7387,
                    1);
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v223 + 5061) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v209 + 5061) = 1;
                v210 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v210 + 4816) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v210 + 7235);
                  v211 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v212 = *(&this->m_bWPXS + 192 * v211 + 342);
                  v213 = *(&this->m_bWPXS + 192 * v211 + 343);
                  v214 = *(&this->m_bWPXS + 192 * v211 + 344);
                  v1037 = *(&this->m_bWPXS + 192 * v211 + 345);
                  v215 = &this->m_bWPXS + 624 * v211 + 2604;
                  v215[2] = v213;
                  v216 = v215 + 1;
                  v215[3] = v214;
                  v215[1] = v212;
                  v217 = v1037;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v210 + 7235);
                  v218 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v219 = *(&this->m_bWPXS + 192 * v218 + 334);
                  v220 = *(&this->m_bWPXS + 192 * v218 + 335);
                  v221 = *(&this->m_bWPXS + 192 * v218 + 336);
                  v960 = *(&this->m_bWPXS + 192 * v218 + 337);
                  v215 = &this->m_bWPXS + 624 * v218 + 2604;
                  v215[2] = v220;
                  v216 = v215 + 1;
                  v215[3] = v221;
                  v215[1] = v219;
                  v217 = v960;
                }
                v215[4] = v217;
                v222 = v215 + 5;
                *v222 = *v216;
                v222[1] = v216[1];
                v222[2] = v216[2];
                v222[3] = v216[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7235))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7235,
                  1);
              }
              v237 = v931[326];
              v238 = v237 < 0;
              v10 = v237 <= 0;
              v239 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                if ( !v238 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v239 + 5062) = 0;
                  goto LABEL_106;
                }
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v239 + 7425))(
                  &this->dwWeaponWU + 1824 * v239 + 7425,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4822) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5066) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5062) = 0;
                v250 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v251 = *(&this->m_bWPXS + 192 * v250 + 358);
                v252 = *(&this->m_bWPXS + 192 * v250 + 359);
                v253 = *(&this->m_bWPXS + 192 * v250 + 360);
                v964 = *(&this->m_bWPXS + 192 * v250 + 361);
                v244 = &this->m_bWPXS + 624 * v250 + 2669;
                v244[2] = v252;
                v245 = v244 + 1;
                v244[3] = v253;
                v244[1] = v251;
                v246 = v964;
              }
              else
              {
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v239 + 7273))(
                  &this->dwWeaponWU + 1824 * v239 + 7273,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4818) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5062) = 1;
                v240 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v241 = *(&this->m_bWPXS + 192 * v240 + 342);
                v242 = *(&this->m_bWPXS + 192 * v240 + 343);
                v243 = *(&this->m_bWPXS + 192 * v240 + 344);
                v1043 = *(&this->m_bWPXS + 192 * v240 + 345);
                v244 = &this->m_bWPXS + 624 * v240 + 2617;
                v244[2] = v242;
                v245 = v244 + 1;
                v244[3] = v243;
                v244[1] = v241;
                v246 = v1043;
              }
              v244[4] = v246;
              v247 = v244 + 5;
              *v247 = *v245;
              v247[1] = v245[1];
              v248 = v245[2];
              v249 = v245[3];
              v247[2] = v248;
              v247[3] = v249;
LABEL_106:
              v254 = v931[328];
              v255 = v254 < 0;
              v10 = v254 <= 0;
              v256 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( !v10 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v256 + 5063) = 1;
                v257 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v257 + 4818) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v257 + 7311);
                  v258 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v259 = *(&this->m_bWPXS + 192 * v258 + 334);
                  v260 = *(&this->m_bWPXS + 192 * v258 + 335);
                  v261 = *(&this->m_bWPXS + 192 * v258 + 336);
                  v1014 = *(&this->m_bWPXS + 192 * v258 + 337);
                  v262 = &this->m_bWPXS + 624 * v258 + 2630;
                  v262[2] = v260;
                  v263 = v262 + 1;
                  v262[3] = v261;
                  v262[1] = v259;
                  v264 = v1014;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v257 + 7311);
                  v265 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v266 = *(&this->m_bWPXS + 192 * v265 + 346);
                  v267 = *(&this->m_bWPXS + 192 * v265 + 347);
                  v268 = *(&this->m_bWPXS + 192 * v265 + 348);
                  v966 = *(&this->m_bWPXS + 192 * v265 + 349);
                  v262 = &this->m_bWPXS + 624 * v265 + 2630;
                  v262[2] = v267;
                  v263 = v262 + 1;
                  v262[3] = v268;
                  v262[1] = v266;
                  v264 = v966;
                }
                v262[4] = v264;
                v269 = v262 + 5;
                *v269 = *v263;
                v269[1] = v263[1];
                v269[2] = v263[2];
                v269[3] = v263[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7311))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7311,
                  1);
                goto LABEL_147;
              }
              v270 = 3 * v256;
              if ( !v255 )
              {
                *((_BYTE *)&this->m_bWPXS + 16 * v270 + 5063) = 0;
LABEL_147:
                (**((void ( ***)(int *, int))&this->m_bWPXS
                  + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 5534))(
                  &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5534,
                  1);
                v3 = v931;
                goto LABEL_406;
              }
              *((_BYTE *)&this->m_bWPXS + 16 * v270 + 5067) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5063) = 0;
              v271 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v271 + 4822) )
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v271 + 7463);
                v272 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v273 = *(&this->m_bWPXS + 192 * v272 + 350);
                v274 = *(&this->m_bWPXS + 192 * v272 + 351);
                v275 = *(&this->m_bWPXS + 192 * v272 + 352);
                v1039 = *(&this->m_bWPXS + 192 * v272 + 353);
                v276 = &this->m_bWPXS + 624 * v272 + 2682;
                v276[2] = v274;
                v277 = v276 + 1;
                v276[3] = v275;
                v276[1] = v273;
                v278 = v1039;
              }
              else
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v271 + 7463);
                v279 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v280 = *(&this->m_bWPXS + 192 * v279 + 362);
                v281 = *(&this->m_bWPXS + 192 * v279 + 363);
                v282 = *(&this->m_bWPXS + 192 * v279 + 364);
                v968 = *(&this->m_bWPXS + 192 * v279 + 365);
                v276 = &this->m_bWPXS + 624 * v279 + 2682;
                v276[2] = v281;
                v277 = v276 + 1;
                v276[3] = v282;
                v276[1] = v280;
                v278 = v968;
              }
LABEL_115:
              v276[4] = v278;
              v283 = v276 + 5;
              *v283 = *v277;
              v283[1] = v277[1];
              v283[2] = v277[2];
              v283[3] = v277[3];
              (**((void ( ***)(int *, int))&this->dwWeaponWU
                + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                + 7463))(
                &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7463,
                1);
              goto LABEL_147;
            }
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v192 + 7349))(
              &this->dwWeaponWU + 1824 * v192 + 7349,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4820) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5064) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5060) = 0;
            v203 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v204 = *(&this->m_bWPXS + 192 * v203 + 350);
            v205 = *(&this->m_bWPXS + 192 * v203 + 351);
            v206 = *(&this->m_bWPXS + 192 * v203 + 352);
            v958 = *(&this->m_bWPXS + 192 * v203 + 353);
            v197 = &this->m_bWPXS + 624 * v203 + 2643;
            v197[2] = v205;
            v198 = v197 + 1;
            v197[3] = v206;
            v197[1] = v204;
            v199 = v958;
          }
          else
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v192 + 7197))(
              &this->dwWeaponWU + 1824 * v192 + 7197,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4816) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5060) = 1;
            v193 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v194 = *(&this->m_bWPXS + 192 * v193 + 334);
            v195 = *(&this->m_bWPXS + 192 * v193 + 335);
            v196 = *(&this->m_bWPXS + 192 * v193 + 336);
            v1010 = *(&this->m_bWPXS + 192 * v193 + 337);
            v197 = &this->m_bWPXS + 624 * v193 + 2591;
            v197[2] = v195;
            v198 = v197 + 1;
            v197[3] = v196;
            v197[1] = v194;
            v199 = v1010;
          }
          v197[4] = v199;
          v200 = v197 + 5;
          *v200 = *v198;
          v200[1] = v198[1];
          v201 = v198[2];
          v202 = v198[3];
          v200[2] = v201;
          v200[3] = v202;
          goto LABEL_89;
        }
        ((UIStatic *)(&this->m_bWPXS + 270 * v188 + 5534))->CreateFromTemplate();
        v284 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v285 = v3[325];
        v286 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v284) + 650);
        if ( v285 >= v286 )
        {
          if ( v285 <= v286 )
            goto LABEL_122;
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v284 + 7197))(
            &this->dwWeaponWU + 1824 * v284 + 7197,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4816) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5060) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5064) = 0;
          v294 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v295 = *(&this->m_bWPXS + 192 * v294 + 334);
          v296 = *(&this->m_bWPXS + 192 * v294 + 335);
          v297 = *(&this->m_bWPXS + 192 * v294 + 336);
          v970 = *(&this->m_bWPXS + 192 * v294 + 337);
          v291 = &this->m_bWPXS + 624 * v294 + 2591;
          v291[2] = v296;
          v292 = v291 + 1;
          v291[3] = v297;
          v291[1] = v295;
          v293 = v970;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v284 + 7349))(
            &this->dwWeaponWU + 1824 * v284 + 7349,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4820) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5064) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5060) = 0;
          v287 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v288 = *(&this->m_bWPXS + 192 * v287 + 350);
          v289 = *(&this->m_bWPXS + 192 * v287 + 351);
          v290 = *(&this->m_bWPXS + 192 * v287 + 352);
          v1016 = *(&this->m_bWPXS + 192 * v287 + 353);
          v291 = &this->m_bWPXS + 624 * v287 + 2643;
          v291[2] = v289;
          v292 = v291 + 1;
          v291[3] = v290;
          v291[1] = v288;
          v293 = v1016;
        }
        v291[4] = v293;
        v298 = v291 + 5;
        *v298 = *v292;
        v298[1] = v292[1];
        v298[2] = v292[2];
        v298[3] = v292[3];
LABEL_122:
        v299 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v300 = v931[327];
        v301 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v299) + 654);
        if ( v300 >= v301 )
        {
          if ( v300 <= v301 )
            goto LABEL_133;
          *((_BYTE *)&this->m_bWPXS + 48 * v299 + 5061) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5065) = 0;
          v316 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v316 + 4816) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v316 + 7235);
            v317 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v318 = *(&this->m_bWPXS + 192 * v317 + 342);
            v319 = *(&this->m_bWPXS + 192 * v317 + 343);
            v320 = *(&this->m_bWPXS + 192 * v317 + 344);
            v1018 = *(&this->m_bWPXS + 192 * v317 + 345);
            v321 = &this->m_bWPXS + 624 * v317 + 2604;
            v321[2] = v319;
            v322 = v321 + 1;
            v321[3] = v320;
            v321[1] = v318;
            v323 = v1018;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v316 + 7235);
            v324 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v325 = *(&this->m_bWPXS + 192 * v324 + 334);
            v326 = *(&this->m_bWPXS + 192 * v324 + 335);
            v327 = *(&this->m_bWPXS + 192 * v324 + 336);
            v974 = *(&this->m_bWPXS + 192 * v324 + 337);
            v321 = &this->m_bWPXS + 624 * v324 + 2604;
            v321[2] = v326;
            v322 = v321 + 1;
            v321[3] = v327;
            v321[1] = v325;
            v323 = v974;
          }
          v321[4] = v323;
          v328 = v321 + 5;
          *v328 = *v322;
          v328[1] = v322[1];
          v328[2] = v322[2];
          v328[3] = v322[3];
          v315 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7235;
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v299 + 5065) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5061) = 0;
          v302 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v302 + 4820) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v302 + 7387);
            v303 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v304 = *(&this->m_bWPXS + 192 * v303 + 358);
            v305 = *(&this->m_bWPXS + 192 * v303 + 359);
            v306 = *(&this->m_bWPXS + 192 * v303 + 360);
            v1047 = *(&this->m_bWPXS + 192 * v303 + 361);
            v307 = &this->m_bWPXS + 624 * v303 + 2656;
            v307[2] = v305;
            v308 = v307 + 1;
            v307[3] = v306;
            v307[1] = v304;
            v309 = v1047;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v302 + 7387);
            v310 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v311 = *(&this->m_bWPXS + 192 * v310 + 350);
            v312 = *(&this->m_bWPXS + 192 * v310 + 351);
            v313 = *(&this->m_bWPXS + 192 * v310 + 352);
            v972 = *(&this->m_bWPXS + 192 * v310 + 353);
            v307 = &this->m_bWPXS + 624 * v310 + 2656;
            v307[2] = v312;
            v308 = v307 + 1;
            v307[3] = v313;
            v307[1] = v311;
            v309 = v972;
          }
          v307[4] = v309;
          v314 = v307 + 5;
          *v314 = *v308;
          v314[1] = v308[1];
          v314[2] = v308[2];
          v314[3] = v308[3];
          v315 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7387;
        }
        (*(void ( **)(int *, int))*v315)(v315, 1);
LABEL_133:
        v329 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v330 = v931[326];
        v331 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v329) + 652);
        if ( v330 >= v331 )
        {
          if ( v330 <= v331 )
          {
LABEL_138:
            v344 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v345 = v931[328];
            v346 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * v344) + 656);
            if ( v345 >= v346 )
            {
              if ( v345 > v346 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v344 + 5063) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5067) = 0;
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7311))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7311,
                  1);
                v356 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v356 + 4818) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v356 + 7311);
                  v357 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v358 = *(&this->m_bWPXS + 192 * v357 + 334);
                  v359 = *(&this->m_bWPXS + 192 * v357 + 335);
                  v360 = *(&this->m_bWPXS + 192 * v357 + 336);
                  v1035 = *(&this->m_bWPXS + 192 * v357 + 337);
                  v361 = &this->m_bWPXS + 624 * v357 + 2630;
                  v361[2] = v359;
                  v362 = v361 + 1;
                  v361[3] = v360;
                  v361[1] = v358;
                  v363 = v1035;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v356 + 7311);
                  v364 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v365 = *(&this->m_bWPXS + 192 * v364 + 346);
                  v366 = *(&this->m_bWPXS + 192 * v364 + 347);
                  v367 = *(&this->m_bWPXS + 192 * v364 + 348);
                  v980 = *(&this->m_bWPXS + 192 * v364 + 349);
                  v361 = &this->m_bWPXS + 624 * v364 + 2630;
                  v361[2] = v366;
                  v362 = v361 + 1;
                  v361[3] = v367;
                  v361[1] = v365;
                  v363 = v980;
                }
                v361[4] = v363;
                v368 = v361 + 5;
                *v368 = *v362;
                v368[1] = v362[1];
                v368[2] = v362[2];
                v368[3] = v362[3];
              }
              goto LABEL_147;
            }
            *((_BYTE *)&this->m_bWPXS + 48 * v344 + 5067) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5063) = 0;
            v347 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v347 + 4822) )
            {
              sub_445FA0(&this->dwWeaponWU + 1824 * v347 + 7463);
              v348 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v349 = *(&this->m_bWPXS + 192 * v348 + 350);
              v350 = *(&this->m_bWPXS + 192 * v348 + 351);
              v351 = *(&this->m_bWPXS + 192 * v348 + 352);
              v1020 = *(&this->m_bWPXS + 192 * v348 + 353);
              v276 = &this->m_bWPXS + 624 * v348 + 2682;
              v276[2] = v350;
              v277 = v276 + 1;
              v276[3] = v351;
              v276[1] = v349;
              v278 = v1020;
            }
            else
            {
              sub_445FA0(&this->dwWeaponWU + 1824 * v347 + 7463);
              v352 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v353 = *(&this->m_bWPXS + 192 * v352 + 362);
              v354 = *(&this->m_bWPXS + 192 * v352 + 363);
              v355 = *(&this->m_bWPXS + 192 * v352 + 364);
              v978 = *(&this->m_bWPXS + 192 * v352 + 365);
              v276 = &this->m_bWPXS + 624 * v352 + 2682;
              v276[2] = v354;
              v277 = v276 + 1;
              v276[3] = v355;
              v276[1] = v353;
              v278 = v978;
            }
            goto LABEL_115;
          }
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v329 + 7273))(
            &this->dwWeaponWU + 1824 * v329 + 7273,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4818) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5062) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5066) = 0;
          v339 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v340 = *(&this->m_bWPXS + 192 * v339 + 342);
          v341 = *(&this->m_bWPXS + 192 * v339 + 343);
          v342 = *(&this->m_bWPXS + 192 * v339 + 344);
          v976 = *(&this->m_bWPXS + 192 * v339 + 345);
          v336 = &this->m_bWPXS + 624 * v339 + 2617;
          v336[2] = v341;
          v337 = v336 + 1;
          v336[3] = v342;
          v336[1] = v340;
          v338 = v976;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v329 + 7425))(
            &this->dwWeaponWU + 1824 * v329 + 7425,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4822) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5066) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5062) = 0;
          v332 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v333 = *(&this->m_bWPXS + 192 * v332 + 358);
          v334 = *(&this->m_bWPXS + 192 * v332 + 359);
          v335 = *(&this->m_bWPXS + 192 * v332 + 360);
          v1041 = *(&this->m_bWPXS + 192 * v332 + 361);
          v336 = &this->m_bWPXS + 624 * v332 + 2669;
          v336[2] = v334;
          v337 = v336 + 1;
          v336[3] = v335;
          v336[1] = v333;
          v338 = v1041;
        }
        v336[4] = v338;
        v343 = v336 + 5;
        *v343 = *v337;
        v343[1] = v337[1];
        v343[2] = v337[2];
        v343[3] = v337[3];
        goto LABEL_138;
      case 9:
        v369 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        if ( !*((_BYTE *)v3 + v369 + 614) )
          goto LABEL_406;
        if ( !*((_DWORD *)&Buffer.m_partyActor.m_fAnimDelta + 352 * v369) )
        {
          ((UIStatic *)(&this->m_bWPXS + 270 * v369 + 5579))->CreateFromTemplate();
          for ( k = 0; k < 8; ++k )
            (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 38 * k
              + 7501))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 38 * k + 7501,
              0);
          v371 = v3[325];
          v372 = v371 < 0;
          v10 = v371 <= 0;
          v373 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( v10 )
          {
            if ( !v372 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v373 + 5068) = 0;
LABEL_158:
              v388 = v931[327];
              v389 = v388 < 0;
              v10 = v388 <= 0;
              v390 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                v404 = 3 * v390;
                if ( v389 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v404 + 5073) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5069) = 0;
                  v405 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v405 + 4828) )
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v405 + 7691);
                    v406 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v407 = *(&this->m_bWPXS + 192 * v406 + 390);
                    v408 = *(&this->m_bWPXS + 192 * v406 + 391);
                    v409 = *(&this->m_bWPXS + 192 * v406 + 392);
                    v1024 = *(&this->m_bWPXS + 192 * v406 + 393);
                    v410 = &this->m_bWPXS + 624 * v406 + 2760;
                    v410[2] = v408;
                    v411 = v410 + 1;
                    v410[3] = v409;
                    v410[1] = v407;
                    v412 = v1024;
                  }
                  else
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v405 + 7691);
                    v413 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v414 = *(&this->m_bWPXS + 192 * v413 + 382);
                    v415 = *(&this->m_bWPXS + 192 * v413 + 383);
                    v416 = *(&this->m_bWPXS + 192 * v413 + 384);
                    v986 = *(&this->m_bWPXS + 192 * v413 + 385);
                    v410 = &this->m_bWPXS + 624 * v413 + 2760;
                    v410[2] = v415;
                    v411 = v410 + 1;
                    v410[3] = v416;
                    v410[1] = v414;
                    v412 = v986;
                  }
                  v410[4] = v412;
                  v417 = v410 + 5;
                  *v417 = *v411;
                  v417[1] = v411[1];
                  v417[2] = v411[2];
                  v417[3] = v411[3];
                  (**((void ( ***)(int *, int))&this->dwWeaponWU
                    + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                    + 7691))(
                    &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7691,
                    1);
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v404 + 5069) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v390 + 5069) = 1;
                v391 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v391 + 4824) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v391 + 7539);
                  v392 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v393 = *(&this->m_bWPXS + 192 * v392 + 374);
                  v394 = *(&this->m_bWPXS + 192 * v392 + 375);
                  v395 = *(&this->m_bWPXS + 192 * v392 + 376);
                  v1036 = *(&this->m_bWPXS + 192 * v392 + 377);
                  v396 = &this->m_bWPXS + 624 * v392 + 2708;
                  v396[2] = v394;
                  v397 = v396 + 1;
                  v396[3] = v395;
                  v396[1] = v393;
                  v398 = v1036;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v391 + 7539);
                  v399 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v400 = *(&this->m_bWPXS + 192 * v399 + 366);
                  v401 = *(&this->m_bWPXS + 192 * v399 + 367);
                  v402 = *(&this->m_bWPXS + 192 * v399 + 368);
                  v984 = *(&this->m_bWPXS + 192 * v399 + 369);
                  v396 = &this->m_bWPXS + 624 * v399 + 2708;
                  v396[2] = v401;
                  v397 = v396 + 1;
                  v396[3] = v402;
                  v396[1] = v400;
                  v398 = v984;
                }
                v396[4] = v398;
                v403 = v396 + 5;
                *v403 = *v397;
                v403[1] = v397[1];
                v403[2] = v397[2];
                v403[3] = v397[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7539))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7539,
                  1);
              }
              v418 = v931[326];
              v419 = v418 < 0;
              v10 = v418 <= 0;
              v420 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                if ( !v419 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v420 + 5070) = 0;
                  goto LABEL_175;
                }
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v420 + 7729))(
                  &this->dwWeaponWU + 1824 * v420 + 7729,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4830) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5074) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5070) = 0;
                v431 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v432 = *(&this->m_bWPXS + 192 * v431 + 390);
                v433 = *(&this->m_bWPXS + 192 * v431 + 391);
                v434 = *(&this->m_bWPXS + 192 * v431 + 392);
                v988 = *(&this->m_bWPXS + 192 * v431 + 393);
                v425 = &this->m_bWPXS + 624 * v431 + 2773;
                v425[2] = v433;
                v426 = v425 + 1;
                v425[3] = v434;
                v425[1] = v432;
                v427 = v988;
              }
              else
              {
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v420 + 7577))(
                  &this->dwWeaponWU + 1824 * v420 + 7577,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4826) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5070) = 1;
                v421 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v422 = *(&this->m_bWPXS + 192 * v421 + 374);
                v423 = *(&this->m_bWPXS + 192 * v421 + 375);
                v424 = *(&this->m_bWPXS + 192 * v421 + 376);
                v1038 = *(&this->m_bWPXS + 192 * v421 + 377);
                v425 = &this->m_bWPXS + 624 * v421 + 2721;
                v425[2] = v423;
                v426 = v425 + 1;
                v425[3] = v424;
                v425[1] = v422;
                v427 = v1038;
              }
              v425[4] = v427;
              v428 = v425 + 5;
              *v428 = *v426;
              v428[1] = v426[1];
              v429 = v426[2];
              v430 = v426[3];
              v428[2] = v429;
              v428[3] = v430;
LABEL_175:
              v435 = v931[328];
              v436 = v435 < 0;
              v10 = v435 <= 0;
              v437 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( !v10 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v437 + 5071) = 1;
                v438 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v438 + 4826) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v438 + 7615);
                  v439 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v440 = *(&this->m_bWPXS + 192 * v439 + 366);
                  v441 = *(&this->m_bWPXS + 192 * v439 + 367);
                  v442 = *(&this->m_bWPXS + 192 * v439 + 368);
                  v1026 = *(&this->m_bWPXS + 192 * v439 + 369);
                  v443 = &this->m_bWPXS + 624 * v439 + 2734;
                  v443[2] = v441;
                  v444 = v443 + 1;
                  v443[3] = v442;
                  v443[1] = v440;
                  v445 = v1026;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v438 + 7615);
                  v446 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v447 = *(&this->m_bWPXS + 192 * v446 + 378);
                  v448 = *(&this->m_bWPXS + 192 * v446 + 379);
                  v449 = *(&this->m_bWPXS + 192 * v446 + 380);
                  v990 = *(&this->m_bWPXS + 192 * v446 + 381);
                  v443 = &this->m_bWPXS + 624 * v446 + 2734;
                  v443[2] = v448;
                  v444 = v443 + 1;
                  v443[3] = v449;
                  v443[1] = v447;
                  v445 = v990;
                }
                v443[4] = v445;
                v450 = v443 + 5;
                *v450 = *v444;
                v450[1] = v444[1];
                v450[2] = v444[2];
                v450[3] = v444[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7615))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7615,
                  1);
                goto LABEL_216;
              }
              v451 = 3 * v437;
              if ( !v436 )
              {
                *((_BYTE *)&this->m_bWPXS + 16 * v451 + 5071) = 0;
LABEL_216:
                (**((void ( ***)(int *, int))&this->m_bWPXS
                  + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 5579))(
                  &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5579,
                  1);
                v3 = v931;
                goto LABEL_406;
              }
              *((_BYTE *)&this->m_bWPXS + 16 * v451 + 5075) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5071) = 0;
              v452 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v452 + 4830) )
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v452 + 7767);
                v453 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v454 = *(&this->m_bWPXS + 192 * v453 + 382);
                v455 = *(&this->m_bWPXS + 192 * v453 + 383);
                v456 = *(&this->m_bWPXS + 192 * v453 + 384);
                v1040 = *(&this->m_bWPXS + 192 * v453 + 385);
                v457 = &this->m_bWPXS + 624 * v453 + 2786;
                v457[2] = v455;
                v458 = v457 + 1;
                v457[3] = v456;
                v457[1] = v454;
                v459 = v1040;
              }
              else
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v452 + 7767);
                v460 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v461 = *(&this->m_bWPXS + 192 * v460 + 394);
                v462 = *(&this->m_bWPXS + 192 * v460 + 395);
                v463 = *(&this->m_bWPXS + 192 * v460 + 396);
                v992 = *(&this->m_bWPXS + 192 * v460 + 397);
                v457 = &this->m_bWPXS + 624 * v460 + 2786;
                v457[2] = v462;
                v458 = v457 + 1;
                v457[3] = v463;
                v457[1] = v461;
                v459 = v992;
              }
LABEL_184:
              v457[4] = v459;
              v464 = v457 + 5;
              *v464 = *v458;
              v464[1] = v458[1];
              v464[2] = v458[2];
              v464[3] = v458[3];
              (**((void ( ***)(int *, int))&this->dwWeaponWU
                + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                + 7767))(
                &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7767,
                1);
              goto LABEL_216;
            }
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v373 + 7653))(
              &this->dwWeaponWU + 1824 * v373 + 7653,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4828) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5072) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5068) = 0;
            v384 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v385 = *(&this->m_bWPXS + 192 * v384 + 382);
            v386 = *(&this->m_bWPXS + 192 * v384 + 383);
            v387 = *(&this->m_bWPXS + 192 * v384 + 384);
            v982 = *(&this->m_bWPXS + 192 * v384 + 385);
            v378 = &this->m_bWPXS + 624 * v384 + 2747;
            v378[2] = v386;
            v379 = v378 + 1;
            v378[3] = v387;
            v378[1] = v385;
            v380 = v982;
          }
          else
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v373 + 7501))(
              &this->dwWeaponWU + 1824 * v373 + 7501,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4824) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5068) = 1;
            v374 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v375 = *(&this->m_bWPXS + 192 * v374 + 366);
            v376 = *(&this->m_bWPXS + 192 * v374 + 367);
            v377 = *(&this->m_bWPXS + 192 * v374 + 368);
            v1022 = *(&this->m_bWPXS + 192 * v374 + 369);
            v378 = &this->m_bWPXS + 624 * v374 + 2695;
            v378[2] = v376;
            v379 = v378 + 1;
            v378[3] = v377;
            v378[1] = v375;
            v380 = v1022;
          }
          v378[4] = v380;
          v381 = v378 + 5;
          *v381 = *v379;
          v381[1] = v379[1];
          v382 = v379[2];
          v383 = v379[3];
          v381[2] = v382;
          v381[3] = v383;
          goto LABEL_158;
        }
        ((UIStatic *)(&this->m_bWPXS + 270 * v369 + 5579))->CreateFromTemplate();
        v465 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v466 = v3[325];
        v467 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_fAnimDelta + 352 * v465) + 650);
        if ( v466 >= v467 )
        {
          if ( v466 <= v467 )
            goto LABEL_191;
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v465 + 7501))(
            &this->dwWeaponWU + 1824 * v465 + 7501,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4824) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5068) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5072) = 0;
          v475 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v476 = *(&this->m_bWPXS + 192 * v475 + 366);
          v477 = *(&this->m_bWPXS + 192 * v475 + 367);
          v478 = *(&this->m_bWPXS + 192 * v475 + 368);
          v994 = *(&this->m_bWPXS + 192 * v475 + 369);
          v472 = &this->m_bWPXS + 624 * v475 + 2695;
          v472[2] = v477;
          v473 = v472 + 1;
          v472[3] = v478;
          v472[1] = v476;
          v474 = v994;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v465 + 7653))(
            &this->dwWeaponWU + 1824 * v465 + 7653,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4828) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5072) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5068) = 0;
          v468 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v469 = *(&this->m_bWPXS + 192 * v468 + 382);
          v470 = *(&this->m_bWPXS + 192 * v468 + 383);
          v471 = *(&this->m_bWPXS + 192 * v468 + 384);
          v1028 = *(&this->m_bWPXS + 192 * v468 + 385);
          v472 = &this->m_bWPXS + 624 * v468 + 2747;
          v472[2] = v470;
          v473 = v472 + 1;
          v472[3] = v471;
          v472[1] = v469;
          v474 = v1028;
        }
        v472[4] = v474;
        v479 = v472 + 5;
        *v479 = *v473;
        v479[1] = v473[1];
        v479[2] = v473[2];
        v479[3] = v473[3];
LABEL_191:
        v480 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v481 = v931[327];
        v482 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_fAnimDelta + 352 * v480) + 654);
        if ( v481 >= v482 )
        {
          if ( v481 <= v482 )
            goto LABEL_202;
          *((_BYTE *)&this->m_bWPXS + 48 * v480 + 5069) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5073) = 0;
          v497 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v497 + 4824) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v497 + 7539);
            v498 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v499 = *(&this->m_bWPXS + 192 * v498 + 374);
            v500 = *(&this->m_bWPXS + 192 * v498 + 375);
            v501 = *(&this->m_bWPXS + 192 * v498 + 376);
            v1030 = *(&this->m_bWPXS + 192 * v498 + 377);
            v502 = &this->m_bWPXS + 624 * v498 + 2708;
            v502[2] = v500;
            v503 = v502 + 1;
            v502[3] = v501;
            v502[1] = v499;
            v504 = v1030;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v497 + 7539);
            v505 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v506 = *(&this->m_bWPXS + 192 * v505 + 366);
            v507 = *(&this->m_bWPXS + 192 * v505 + 367);
            v508 = *(&this->m_bWPXS + 192 * v505 + 368);
            v998 = *(&this->m_bWPXS + 192 * v505 + 369);
            v502 = &this->m_bWPXS + 624 * v505 + 2708;
            v502[2] = v507;
            v503 = v502 + 1;
            v502[3] = v508;
            v502[1] = v506;
            v504 = v998;
          }
          v502[4] = v504;
          v509 = v502 + 5;
          *v509 = *v503;
          v509[1] = v503[1];
          v509[2] = v503[2];
          v509[3] = v503[3];
          v496 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7539;
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v480 + 5073) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5069) = 0;
          v483 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v483 + 4828) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v483 + 7691);
            v484 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v485 = *(&this->m_bWPXS + 192 * v484 + 390);
            v486 = *(&this->m_bWPXS + 192 * v484 + 391);
            v487 = *(&this->m_bWPXS + 192 * v484 + 392);
            v1042 = *(&this->m_bWPXS + 192 * v484 + 393);
            v488 = &this->m_bWPXS + 624 * v484 + 2760;
            v488[2] = v486;
            v489 = v488 + 1;
            v488[3] = v487;
            v488[1] = v485;
            v490 = v1042;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v483 + 7691);
            v491 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v492 = *(&this->m_bWPXS + 192 * v491 + 382);
            v493 = *(&this->m_bWPXS + 192 * v491 + 383);
            v494 = *(&this->m_bWPXS + 192 * v491 + 384);
            v996 = *(&this->m_bWPXS + 192 * v491 + 385);
            v488 = &this->m_bWPXS + 624 * v491 + 2760;
            v488[2] = v493;
            v489 = v488 + 1;
            v488[3] = v494;
            v488[1] = v492;
            v490 = v996;
          }
          v488[4] = v490;
          v495 = v488 + 5;
          *v495 = *v489;
          v495[1] = v489[1];
          v495[2] = v489[2];
          v495[3] = v489[3];
          v496 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7691;
        }
        (*(void ( **)(int *, int))*v496)(v496, 1);
LABEL_202:
        v510 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v511 = v931[326];
        v512 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_fAnimDelta + 352 * v510) + 652);
        if ( v511 >= v512 )
        {
          if ( v511 <= v512 )
          {
LABEL_207:
            v525 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v526 = v931[328];
            v527 = *(_WORD *)(*((_DWORD *)&Buffer.m_partyActor.m_fAnimDelta + 352 * v525) + 656);
            if ( v526 >= v527 )
            {
              if ( v526 > v527 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v525 + 5071) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5075) = 0;
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7615))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7615,
                  1);
                v537 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v537 + 4826) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v537 + 7615);
                  v538 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v539 = *(&this->m_bWPXS + 192 * v538 + 366);
                  v540 = *(&this->m_bWPXS + 192 * v538 + 367);
                  v541 = *(&this->m_bWPXS + 192 * v538 + 368);
                  v941 = *(&this->m_bWPXS + 192 * v538 + 369);
                  v542 = &this->m_bWPXS + 624 * v538 + 2734;
                  v542[2] = v540;
                  v543 = v542 + 1;
                  v542[1] = v539;
                  v542[3] = v541;
                  v544 = v941;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v537 + 7615);
                  v545 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v546 = *(&this->m_bWPXS + 192 * v545 + 378);
                  v547 = *(&this->m_bWPXS + 192 * v545 + 379);
                  v548 = *(&this->m_bWPXS + 192 * v545 + 380);
                  v943 = *(&this->m_bWPXS + 192 * v545 + 381);
                  v542 = &this->m_bWPXS + 624 * v545 + 2734;
                  v542[2] = v547;
                  v543 = v542 + 1;
                  v542[1] = v546;
                  v542[3] = v548;
                  v544 = v943;
                }
                v542[4] = v544;
                v549 = v542 + 5;
                *v549 = *v543;
                v549[1] = v543[1];
                v549[2] = v543[2];
                v549[3] = v543[3];
              }
              goto LABEL_216;
            }
            *((_BYTE *)&this->m_bWPXS + 48 * v525 + 5075) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5071) = 0;
            v528 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v528 + 4830) )
            {
              sub_445FA0(&this->dwWeaponWU + 1824 * v528 + 7767);
              v529 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v530 = *(&this->m_bWPXS + 192 * v529 + 382);
              v531 = *(&this->m_bWPXS + 192 * v529 + 383);
              v532 = *(&this->m_bWPXS + 192 * v529 + 384);
              v937 = *(&this->m_bWPXS + 192 * v529 + 385);
              v457 = &this->m_bWPXS + 624 * v529 + 2786;
              v457[2] = v531;
              v458 = v457 + 1;
              v457[3] = v532;
              v457[1] = v530;
              v459 = v937;
            }
            else
            {
              sub_445FA0(&this->dwWeaponWU + 1824 * v528 + 7767);
              v533 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v534 = *(&this->m_bWPXS + 192 * v533 + 394);
              v535 = *(&this->m_bWPXS + 192 * v533 + 395);
              v536 = *(&this->m_bWPXS + 192 * v533 + 396);
              v939 = *(&this->m_bWPXS + 192 * v533 + 397);
              v457 = &this->m_bWPXS + 624 * v533 + 2786;
              v457[2] = v535;
              v458 = v457 + 1;
              v457[3] = v536;
              v457[1] = v534;
              v459 = v939;
            }
            goto LABEL_184;
          }
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v510 + 7577))(
            &this->dwWeaponWU + 1824 * v510 + 7577,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4826) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5070) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5074) = 0;
          v520 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v521 = *(&this->m_bWPXS + 192 * v520 + 374);
          v522 = *(&this->m_bWPXS + 192 * v520 + 375);
          v523 = *(&this->m_bWPXS + 192 * v520 + 376);
          v935 = *(&this->m_bWPXS + 192 * v520 + 377);
          v517 = &this->m_bWPXS + 624 * v520 + 2721;
          v517[2] = v522;
          v518 = v517 + 1;
          v517[3] = v523;
          v517[1] = v521;
          v519 = v935;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v510 + 7729))(
            &this->dwWeaponWU + 1824 * v510 + 7729,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4830) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5074) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5070) = 0;
          v513 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v514 = *(&this->m_bWPXS + 192 * v513 + 390);
          v515 = *(&this->m_bWPXS + 192 * v513 + 391);
          v516 = *(&this->m_bWPXS + 192 * v513 + 392);
          v933 = *(&this->m_bWPXS + 192 * v513 + 393);
          v517 = &this->m_bWPXS + 624 * v513 + 2773;
          v517[2] = v515;
          v518 = v517 + 1;
          v517[3] = v516;
          v517[1] = v514;
          v519 = v933;
        }
        v517[4] = v519;
        v524 = v517 + 5;
        *v524 = *v518;
        v524[1] = v518[1];
        v524[2] = v518[2];
        v524[3] = v518[3];
        goto LABEL_207;
      case 0xA:
        v550 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        if ( !*((_BYTE *)v3 + v550 + 614) )
          goto LABEL_406;
        if ( !Buffer.m_partyActor.m_dwMatMsg[352 * v550 + 2] )
        {
          ((UIStatic *)(&this->m_bWPXS + 270 * v550 + 5489))->CreateFromTemplate();
          for ( m = 0; m < 8; ++m )
            (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 38 * m
              + 6893))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 38 * m + 6893,
              0);
          v552 = v3[325];
          v553 = v552 < 0;
          v10 = v552 <= 0;
          v554 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( v10 )
          {
            if ( !v553 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v554 + 5052) = 0;
LABEL_227:
              v567 = v931[327];
              v568 = v567 < 0;
              v10 = v567 <= 0;
              v569 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                v583 = 3 * v569;
                if ( v568 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v583 + 5057) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5053) = 0;
                  v584 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v584 + 4812) )
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v584 + 7083);
                    v585 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v586 = *(&this->m_bWPXS + 192 * v585 + 326);
                    v587 = *(&this->m_bWPXS + 192 * v585 + 327);
                    v588 = *(&this->m_bWPXS + 192 * v585 + 328);
                    v953 = *(&this->m_bWPXS + 192 * v585 + 329);
                    v589 = &this->m_bWPXS + 624 * v585 + 2552;
                    v589[2] = v587;
                    v590 = v589 + 1;
                    v589[1] = v586;
                    v589[3] = v588;
                    v591 = v953;
                  }
                  else
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v584 + 7083);
                    v592 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v593 = *(&this->m_bWPXS + 192 * v592 + 318);
                    v594 = *(&this->m_bWPXS + 192 * v592 + 319);
                    v595 = *(&this->m_bWPXS + 192 * v592 + 320);
                    v955 = *(&this->m_bWPXS + 192 * v592 + 321);
                    v589 = &this->m_bWPXS + 624 * v592 + 2552;
                    v589[2] = v594;
                    v590 = v589 + 1;
                    v589[1] = v593;
                    v589[3] = v595;
                    v591 = v955;
                  }
                  v589[4] = v591;
                  v596 = v589 + 5;
                  *v596 = *v590;
                  v596[1] = v590[1];
                  v596[2] = v590[2];
                  v596[3] = v590[3];
                  (**((void ( ***)(int *, int))&this->dwWeaponWU
                    + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                    + 7083))(
                    &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7083,
                    1);
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v583 + 5053) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v569 + 5053) = 1;
                v570 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v570 + 4808) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v570 + 6931);
                  v571 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v572 = *(&this->m_bWPXS + 192 * v571 + 310);
                  v573 = *(&this->m_bWPXS + 192 * v571 + 311);
                  v574 = *(&this->m_bWPXS + 192 * v571 + 312);
                  v949 = *(&this->m_bWPXS + 192 * v571 + 313);
                  v575 = &this->m_bWPXS + 624 * v571 + 2500;
                  v575[2] = v573;
                  v576 = v575 + 1;
                  v575[1] = v572;
                  v575[3] = v574;
                  v577 = v949;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v570 + 6931);
                  v578 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v579 = *(&this->m_bWPXS + 192 * v578 + 302);
                  v580 = *(&this->m_bWPXS + 192 * v578 + 303);
                  v581 = *(&this->m_bWPXS + 192 * v578 + 304);
                  v951 = *(&this->m_bWPXS + 192 * v578 + 305);
                  v575 = &this->m_bWPXS + 624 * v578 + 2500;
                  v575[2] = v580;
                  v576 = v575 + 1;
                  v575[1] = v579;
                  v575[3] = v581;
                  v577 = v951;
                }
                v575[4] = v577;
                v582 = v575 + 5;
                *v582 = *v576;
                v582[1] = v576[1];
                v582[2] = v576[2];
                v582[3] = v576[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 6931))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6931,
                  1);
              }
              v597 = v931[326];
              v598 = v597 < 0;
              v10 = v597 <= 0;
              v599 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                if ( !v598 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v599 + 5054) = 0;
                  goto LABEL_244;
                }
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v599 + 7121))(
                  &this->dwWeaponWU + 1824 * v599 + 7121,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4814) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5058) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5054) = 0;
                v608 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v609 = *(&this->m_bWPXS + 192 * v608 + 326);
                v610 = *(&this->m_bWPXS + 192 * v608 + 327);
                v611 = *(&this->m_bWPXS + 192 * v608 + 328);
                v959 = *(&this->m_bWPXS + 192 * v608 + 329);
                v604 = &this->m_bWPXS + 624 * v608 + 2565;
                v604[2] = v610;
                v605 = v604 + 1;
                v604[1] = v609;
                v604[3] = v611;
                v606 = v959;
              }
              else
              {
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v599 + 6969))(
                  &this->dwWeaponWU + 1824 * v599 + 6969,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4810) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5054) = 1;
                v600 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v601 = *(&this->m_bWPXS + 192 * v600 + 310);
                v602 = *(&this->m_bWPXS + 192 * v600 + 311);
                v603 = *(&this->m_bWPXS + 192 * v600 + 312);
                v957 = *(&this->m_bWPXS + 192 * v600 + 313);
                v604 = &this->m_bWPXS + 624 * v600 + 2513;
                v604[2] = v602;
                v605 = v604 + 1;
                v604[1] = v601;
                v604[3] = v603;
                v606 = v957;
              }
              v604[4] = v606;
              v607 = v604 + 5;
              *v607 = *v605;
              v607[1] = v605[1];
              v607[2] = v605[2];
              v607[3] = v605[3];
LABEL_244:
              v612 = v931[328];
              v613 = v612 < 0;
              v10 = v612 <= 0;
              v614 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( !v10 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v614 + 5055) = 1;
                v615 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v615 + 4810) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v615 + 7007);
                  v616 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v617 = *(&this->m_bWPXS + 192 * v616 + 302);
                  v618 = *(&this->m_bWPXS + 192 * v616 + 303);
                  v619 = *(&this->m_bWPXS + 192 * v616 + 304);
                  v961 = *(&this->m_bWPXS + 192 * v616 + 305);
                  v620 = &this->m_bWPXS + 624 * v616 + 2526;
                  v620[2] = v618;
                  v621 = v620 + 1;
                  v620[1] = v617;
                  v620[3] = v619;
                  v622 = v961;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v615 + 7007);
                  v623 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v624 = *(&this->m_bWPXS + 192 * v623 + 314);
                  v625 = *(&this->m_bWPXS + 192 * v623 + 315);
                  v626 = *(&this->m_bWPXS + 192 * v623 + 316);
                  v963 = *(&this->m_bWPXS + 192 * v623 + 317);
                  v620 = &this->m_bWPXS + 624 * v623 + 2526;
                  v620[2] = v625;
                  v621 = v620 + 1;
                  v620[1] = v624;
                  v620[3] = v626;
                  v622 = v963;
                }
                v620[4] = v622;
                v627 = v620 + 5;
                *v627 = *v621;
                v627[1] = v621[1];
                v627[2] = v621[2];
                v627[3] = v621[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7007))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7007,
                  1);
                goto LABEL_285;
              }
              v628 = 3 * v614;
              if ( !v613 )
              {
                *((_BYTE *)&this->m_bWPXS + 16 * v628 + 5055) = 0;
                goto LABEL_285;
              }
              *((_BYTE *)&this->m_bWPXS + 16 * v628 + 5059) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5055) = 0;
              v629 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v629 + 4814) )
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v629 + 7159);
                v630 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v631 = *(&this->m_bWPXS + 192 * v630 + 318);
                v632 = *(&this->m_bWPXS + 192 * v630 + 319);
                v633 = *(&this->m_bWPXS + 192 * v630 + 320);
                v965 = *(&this->m_bWPXS + 192 * v630 + 321);
                v634 = &this->m_bWPXS + 624 * v630 + 2578;
                v634[2] = v632;
                v635 = v634 + 1;
                v634[1] = v631;
                v634[3] = v633;
                v636 = v965;
              }
              else
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v629 + 7159);
                v637 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v638 = *(&this->m_bWPXS + 192 * v637 + 330);
                v639 = *(&this->m_bWPXS + 192 * v637 + 331);
                v640 = *(&this->m_bWPXS + 192 * v637 + 332);
                v967 = *(&this->m_bWPXS + 192 * v637 + 333);
                v634 = &this->m_bWPXS + 624 * v637 + 2578;
                v634[2] = v639;
                v635 = v634 + 1;
                v634[1] = v638;
                v634[3] = v640;
                v636 = v967;
              }
LABEL_253:
              v634[4] = v636;
              v641 = v634 + 5;
              *v641 = *v635;
              v641[1] = v635[1];
              v641[2] = v635[2];
              v641[3] = v635[3];
              (**((void ( ***)(int *, int))&this->dwWeaponWU
                + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                + 7159))(
                &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7159,
                1);
              goto LABEL_285;
            }
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v554 + 7045))(
              &this->dwWeaponWU + 1824 * v554 + 7045,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4812) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5056) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5052) = 0;
            v563 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v564 = *(&this->m_bWPXS + 192 * v563 + 318);
            v565 = *(&this->m_bWPXS + 192 * v563 + 319);
            v566 = *(&this->m_bWPXS + 192 * v563 + 320);
            v947 = *(&this->m_bWPXS + 192 * v563 + 321);
            v559 = &this->m_bWPXS + 624 * v563 + 2539;
            v559[2] = v565;
            v560 = v559 + 1;
            v559[1] = v564;
            v559[3] = v566;
            v561 = v947;
          }
          else
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v554 + 6893))(
              &this->dwWeaponWU + 1824 * v554 + 6893,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4808) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5052) = 1;
            v555 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v556 = *(&this->m_bWPXS + 192 * v555 + 302);
            v557 = *(&this->m_bWPXS + 192 * v555 + 303);
            v558 = *(&this->m_bWPXS + 192 * v555 + 304);
            v945 = *(&this->m_bWPXS + 192 * v555 + 305);
            v559 = &this->m_bWPXS + 624 * v555 + 2487;
            v559[2] = v557;
            v560 = v559 + 1;
            v559[1] = v556;
            v559[3] = v558;
            v561 = v945;
          }
          v559[4] = v561;
          v562 = v559 + 5;
          *v562 = *v560;
          v562[1] = v560[1];
          v562[2] = v560[2];
          v562[3] = v560[3];
          goto LABEL_227;
        }
        ((UIStatic *)(&this->m_bWPXS + 270 * v550 + 5489))->CreateFromTemplate();
        v642 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v643 = v3[325];
        v644 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v642 + 2] + 650);
        if ( v643 >= v644 )
        {
          if ( v643 <= v644 )
            goto LABEL_260;
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v642 + 6893))(
            &this->dwWeaponWU + 1824 * v642 + 6893,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4808) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5052) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5056) = 0;
          v652 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v653 = *(&this->m_bWPXS + 192 * v652 + 302);
          v654 = *(&this->m_bWPXS + 192 * v652 + 303);
          v655 = *(&this->m_bWPXS + 192 * v652 + 304);
          v971 = *(&this->m_bWPXS + 192 * v652 + 305);
          v649 = &this->m_bWPXS + 624 * v652 + 2487;
          v649[2] = v654;
          v650 = v649 + 1;
          v649[1] = v653;
          v649[3] = v655;
          v651 = v971;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v642 + 7045))(
            &this->dwWeaponWU + 1824 * v642 + 7045,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4812) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5056) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5052) = 0;
          v645 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v646 = *(&this->m_bWPXS + 192 * v645 + 318);
          v647 = *(&this->m_bWPXS + 192 * v645 + 319);
          v648 = *(&this->m_bWPXS + 192 * v645 + 320);
          v969 = *(&this->m_bWPXS + 192 * v645 + 321);
          v649 = &this->m_bWPXS + 624 * v645 + 2539;
          v649[2] = v647;
          v650 = v649 + 1;
          v649[1] = v646;
          v649[3] = v648;
          v651 = v969;
        }
        v649[4] = v651;
        v656 = v649 + 5;
        *v656 = *v650;
        v656[1] = v650[1];
        v656[2] = v650[2];
        v656[3] = v650[3];
LABEL_260:
        v657 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v658 = v931[327];
        v659 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v657 + 2] + 654);
        if ( v658 >= v659 )
        {
          if ( v658 <= v659 )
            goto LABEL_271;
          *((_BYTE *)&this->m_bWPXS + 48 * v657 + 5053) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5057) = 0;
          v674 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v674 + 4808) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v674 + 6931);
            v675 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v676 = *(&this->m_bWPXS + 192 * v675 + 310);
            v677 = *(&this->m_bWPXS + 192 * v675 + 311);
            v678 = *(&this->m_bWPXS + 192 * v675 + 312);
            v977 = *(&this->m_bWPXS + 192 * v675 + 313);
            v679 = &this->m_bWPXS + 624 * v675 + 2500;
            v679[2] = v677;
            v680 = v679 + 1;
            v679[1] = v676;
            v679[3] = v678;
            v681 = v977;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v674 + 6931);
            v682 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v683 = *(&this->m_bWPXS + 192 * v682 + 302);
            v684 = *(&this->m_bWPXS + 192 * v682 + 303);
            v685 = *(&this->m_bWPXS + 192 * v682 + 304);
            v979 = *(&this->m_bWPXS + 192 * v682 + 305);
            v679 = &this->m_bWPXS + 624 * v682 + 2500;
            v679[2] = v684;
            v680 = v679 + 1;
            v679[1] = v683;
            v679[3] = v685;
            v681 = v979;
          }
          v679[4] = v681;
          v686 = v679 + 5;
          *v686 = *v680;
          v686[1] = v680[1];
          v686[2] = v680[2];
          v686[3] = v680[3];
          v673 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6931;
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v657 + 5057) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5053) = 0;
          v660 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v660 + 4812) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v660 + 7083);
            v661 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v662 = *(&this->m_bWPXS + 192 * v661 + 326);
            v663 = *(&this->m_bWPXS + 192 * v661 + 327);
            v664 = *(&this->m_bWPXS + 192 * v661 + 328);
            v973 = *(&this->m_bWPXS + 192 * v661 + 329);
            v665 = &this->m_bWPXS + 624 * v661 + 2552;
            v665[2] = v663;
            v666 = v665 + 1;
            v665[1] = v662;
            v665[3] = v664;
            v667 = v973;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v660 + 7083);
            v668 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v669 = *(&this->m_bWPXS + 192 * v668 + 318);
            v670 = *(&this->m_bWPXS + 192 * v668 + 319);
            v671 = *(&this->m_bWPXS + 192 * v668 + 320);
            v975 = *(&this->m_bWPXS + 192 * v668 + 321);
            v665 = &this->m_bWPXS + 624 * v668 + 2552;
            v665[2] = v670;
            v666 = v665 + 1;
            v665[1] = v669;
            v665[3] = v671;
            v667 = v975;
          }
          v665[4] = v667;
          v672 = v665 + 5;
          *v672 = *v666;
          v672[1] = v666[1];
          v672[2] = v666[2];
          v672[3] = v666[3];
          v673 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7083;
        }
        (*(void ( **)(int *, int))*v673)(v673, 1);
LABEL_271:
        v687 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v688 = v931[326];
        v689 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v687 + 2] + 652);
        if ( v688 >= v689 )
        {
          if ( v688 <= v689 )
            goto LABEL_276;
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v687 + 6969))(
            &this->dwWeaponWU + 1824 * v687 + 6969,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4810) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5054) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5058) = 0;
          v697 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v698 = *(&this->m_bWPXS + 192 * v697 + 310);
          v699 = *(&this->m_bWPXS + 192 * v697 + 311);
          v700 = *(&this->m_bWPXS + 192 * v697 + 312);
          v983 = *(&this->m_bWPXS + 192 * v697 + 313);
          v694 = &this->m_bWPXS + 624 * v697 + 2513;
          v694[2] = v699;
          v695 = v694 + 1;
          v694[1] = v698;
          v694[3] = v700;
          v696 = v983;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v687 + 7121))(
            &this->dwWeaponWU + 1824 * v687 + 7121,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4814) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5058) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5054) = 0;
          v690 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v691 = *(&this->m_bWPXS + 192 * v690 + 326);
          v692 = *(&this->m_bWPXS + 192 * v690 + 327);
          v693 = *(&this->m_bWPXS + 192 * v690 + 328);
          v981 = *(&this->m_bWPXS + 192 * v690 + 329);
          v694 = &this->m_bWPXS + 624 * v690 + 2565;
          v694[2] = v692;
          v695 = v694 + 1;
          v694[1] = v691;
          v694[3] = v693;
          v696 = v981;
        }
        v694[4] = v696;
        v701 = v694 + 5;
        *v701 = *v695;
        v701[1] = v695[1];
        v701[2] = v695[2];
        v701[3] = v695[3];
LABEL_276:
        v702 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v703 = v931[328];
        v704 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v702 + 2] + 656);
        if ( v703 < v704 )
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v702 + 5059) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5055) = 0;
          v705 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v705 + 4814) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v705 + 7159);
            v706 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v707 = *(&this->m_bWPXS + 192 * v706 + 318);
            v708 = *(&this->m_bWPXS + 192 * v706 + 319);
            v709 = *(&this->m_bWPXS + 192 * v706 + 320);
            v985 = *(&this->m_bWPXS + 192 * v706 + 321);
            v634 = &this->m_bWPXS + 624 * v706 + 2578;
            v634[2] = v708;
            v635 = v634 + 1;
            v634[1] = v707;
            v634[3] = v709;
            v636 = v985;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v705 + 7159);
            v710 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v711 = *(&this->m_bWPXS + 192 * v710 + 330);
            v712 = *(&this->m_bWPXS + 192 * v710 + 331);
            v713 = *(&this->m_bWPXS + 192 * v710 + 332);
            v987 = *(&this->m_bWPXS + 192 * v710 + 333);
            v634 = &this->m_bWPXS + 624 * v710 + 2578;
            v634[2] = v712;
            v635 = v634 + 1;
            v634[1] = v711;
            v634[3] = v713;
            v636 = v987;
          }
          goto LABEL_253;
        }
        if ( v703 > v704 )
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v702 + 5055) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5059) = 0;
          (**((void ( ***)(int *, int))&this->dwWeaponWU
            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
            + 7007))(
            &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7007,
            1);
          v714 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v714 + 4810) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v714 + 7007);
            v715 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v716 = *(&this->m_bWPXS + 192 * v715 + 302);
            v717 = *(&this->m_bWPXS + 192 * v715 + 303);
            v718 = *(&this->m_bWPXS + 192 * v715 + 304);
            v989 = *(&this->m_bWPXS + 192 * v715 + 305);
            v719 = &this->m_bWPXS + 624 * v715 + 2526;
            v719[2] = v717;
            v720 = v719 + 1;
            v719[1] = v716;
            v719[3] = v718;
            v721 = v989;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v714 + 7007);
            v722 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v723 = *(&this->m_bWPXS + 192 * v722 + 314);
            v724 = *(&this->m_bWPXS + 192 * v722 + 315);
            v725 = *(&this->m_bWPXS + 192 * v722 + 316);
            v991 = *(&this->m_bWPXS + 192 * v722 + 317);
            v719 = &this->m_bWPXS + 624 * v722 + 2526;
            v719[2] = v724;
            v720 = v719 + 1;
            v719[1] = v723;
            v719[3] = v725;
            v721 = v991;
          }
          v719[4] = v721;
          v726 = v719 + 5;
          *v726 = *v720;
          v726[1] = v720[1];
          v726[2] = v720[2];
          v726[3] = v720[3];
        }
LABEL_285:
        v727 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        if ( !Buffer.m_partyActor.m_dwMatMsg[352 * v727 + 5] )
        {
          ((UIStatic *)(&this->m_bWPXS + 270 * v727 + 5624))->CreateFromTemplate();
          for ( n = 0; n < 8; ++n )
            (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 38 * n
              + 7805))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 38 * n + 7805,
              0);
          v729 = v931[325];
          v730 = v729 < 0;
          v10 = v729 <= 0;
          v731 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( v10 )
          {
            if ( !v730 )
            {
              *((_BYTE *)&this->m_bWPXS + 48 * v731 + 5076) = 0;
LABEL_294:
              v744 = v931[327];
              v745 = v744 < 0;
              v10 = v744 <= 0;
              v746 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                v760 = 3 * v746;
                if ( v745 )
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v760 + 5081) = 1;
                  *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5077) = 0;
                  v761 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  if ( *((_BYTE *)&this->m_bWPXS + 48 * v761 + 4836) )
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v761 + 7995);
                    v762 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v763 = *(&this->m_bWPXS + 192 * v762 + 422);
                    v764 = *(&this->m_bWPXS + 192 * v762 + 423);
                    v765 = *(&this->m_bWPXS + 192 * v762 + 424);
                    v1001 = *(&this->m_bWPXS + 192 * v762 + 425);
                    v766 = &this->m_bWPXS + 624 * v762 + 2864;
                    v766[2] = v764;
                    v767 = v766 + 1;
                    v766[1] = v763;
                    v766[3] = v765;
                    v768 = v1001;
                  }
                  else
                  {
                    sub_445FA0(&this->dwWeaponWU + 1824 * v761 + 7995);
                    v769 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                    v770 = *(&this->m_bWPXS + 192 * v769 + 414);
                    v771 = *(&this->m_bWPXS + 192 * v769 + 415);
                    v772 = *(&this->m_bWPXS + 192 * v769 + 416);
                    v1003 = *(&this->m_bWPXS + 192 * v769 + 417);
                    v766 = &this->m_bWPXS + 624 * v769 + 2864;
                    v766[2] = v771;
                    v767 = v766 + 1;
                    v766[1] = v770;
                    v766[3] = v772;
                    v768 = v1003;
                  }
                  v766[4] = v768;
                  v773 = v766 + 5;
                  *v773 = *v767;
                  v773[1] = v767[1];
                  v773[2] = v767[2];
                  v773[3] = v767[3];
                  (**((void ( ***)(int *, int))&this->dwWeaponWU
                    + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                    + 7995))(
                    &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7995,
                    1);
                }
                else
                {
                  *((_BYTE *)&this->m_bWPXS + 16 * v760 + 5077) = 0;
                }
              }
              else
              {
                *((_BYTE *)&this->m_bWPXS + 48 * v746 + 5077) = 1;
                v747 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v747 + 4832) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v747 + 7843);
                  v748 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v749 = *(&this->m_bWPXS + 192 * v748 + 406);
                  v750 = *(&this->m_bWPXS + 192 * v748 + 407);
                  v751 = *(&this->m_bWPXS + 192 * v748 + 408);
                  v997 = *(&this->m_bWPXS + 192 * v748 + 409);
                  v752 = &this->m_bWPXS + 624 * v748 + 2812;
                  v752[2] = v750;
                  v753 = v752 + 1;
                  v752[1] = v749;
                  v752[3] = v751;
                  v754 = v997;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v747 + 7843);
                  v755 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v756 = *(&this->m_bWPXS + 192 * v755 + 398);
                  v757 = *(&this->m_bWPXS + 192 * v755 + 399);
                  v758 = *(&this->m_bWPXS + 192 * v755 + 400);
                  v999 = *(&this->m_bWPXS + 192 * v755 + 401);
                  v752 = &this->m_bWPXS + 624 * v755 + 2812;
                  v752[2] = v757;
                  v753 = v752 + 1;
                  v752[1] = v756;
                  v752[3] = v758;
                  v754 = v999;
                }
                v752[4] = v754;
                v759 = v752 + 5;
                *v759 = *v753;
                v759[1] = v753[1];
                v759[2] = v753[2];
                v759[3] = v753[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7843))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7843,
                  1);
              }
              v774 = v931[326];
              v775 = v774 < 0;
              v10 = v774 <= 0;
              v776 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( v10 )
              {
                if ( !v775 )
                {
                  *((_BYTE *)&this->m_bWPXS + 48 * v776 + 5078) = 0;
                  goto LABEL_311;
                }
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v776 + 8033))(
                  &this->dwWeaponWU + 1824 * v776 + 8033,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4838) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5082) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5078) = 0;
                v785 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v786 = *(&this->m_bWPXS + 192 * v785 + 422);
                v787 = *(&this->m_bWPXS + 192 * v785 + 423);
                v788 = *(&this->m_bWPXS + 192 * v785 + 424);
                v1007 = *(&this->m_bWPXS + 192 * v785 + 425);
                v781 = &this->m_bWPXS + 624 * v785 + 2877;
                v781[2] = v787;
                v782 = v781 + 1;
                v781[1] = v786;
                v781[3] = v788;
                v783 = v1007;
              }
              else
              {
                (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v776 + 7881))(
                  &this->dwWeaponWU + 1824 * v776 + 7881,
                  1);
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4834) = 1;
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5078) = 1;
                v777 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v778 = *(&this->m_bWPXS + 192 * v777 + 406);
                v779 = *(&this->m_bWPXS + 192 * v777 + 407);
                v780 = *(&this->m_bWPXS + 192 * v777 + 408);
                v1005 = *(&this->m_bWPXS + 192 * v777 + 409);
                v781 = &this->m_bWPXS + 624 * v777 + 2825;
                v781[2] = v779;
                v782 = v781 + 1;
                v781[1] = v778;
                v781[3] = v780;
                v783 = v1005;
              }
              v781[4] = v783;
              v784 = v781 + 5;
              *v784 = *v782;
              v784[1] = v782[1];
              v784[2] = v782[2];
              v784[3] = v782[3];
LABEL_311:
              v3 = v931;
              v789 = v931[328];
              if ( v789 > 0 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5079) = 1;
                v790 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                if ( *((_BYTE *)&this->m_bWPXS + 48 * v790 + 4834) )
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v790 + 7919);
                  v791 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v792 = *(&this->m_bWPXS + 192 * v791 + 398);
                  v793 = *(&this->m_bWPXS + 192 * v791 + 399);
                  v794 = *(&this->m_bWPXS + 192 * v791 + 400);
                  v1009 = *(&this->m_bWPXS + 192 * v791 + 401);
                  v795 = &this->m_bWPXS + 624 * v791 + 2838;
                  v795[2] = v793;
                  v796 = v795 + 1;
                  v795[1] = v792;
                  v795[3] = v794;
                  v797 = v1009;
                }
                else
                {
                  sub_445FA0(&this->dwWeaponWU + 1824 * v790 + 7919);
                  v798 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                  v799 = *(&this->m_bWPXS + 192 * v798 + 410);
                  v800 = *(&this->m_bWPXS + 192 * v798 + 411);
                  v801 = *(&this->m_bWPXS + 192 * v798 + 412);
                  v1011 = *(&this->m_bWPXS + 192 * v798 + 413);
                  v795 = &this->m_bWPXS + 624 * v798 + 2838;
                  v795[2] = v800;
                  v796 = v795 + 1;
                  v795[1] = v799;
                  v795[3] = v801;
                  v797 = v1011;
                }
                v795[4] = v797;
                v802 = v795 + 5;
                *v802 = *v796;
                v802[1] = v796[1];
                v802[2] = v796[2];
                v802[3] = v796[3];
                (**((void ( ***)(int *, int))&this->dwWeaponWU
                  + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                  + 7919))(
                  &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7919,
                  1);
                v3 = v931;
                goto LABEL_353;
              }
              if ( v789 >= 0 )
              {
                *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5079) = 0;
                goto LABEL_353;
              }
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5083) = 1;
              *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5079) = 0;
              v803 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              if ( *((_BYTE *)&this->m_bWPXS + 48 * v803 + 4838) )
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v803 + 8071);
                v804 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v805 = *(&this->m_bWPXS + 192 * v804 + 414);
                v806 = *(&this->m_bWPXS + 192 * v804 + 415);
                v807 = *(&this->m_bWPXS + 192 * v804 + 416);
                v1013 = *(&this->m_bWPXS + 192 * v804 + 417);
                v808 = &this->m_bWPXS + 624 * v804 + 2890;
                v808[2] = v806;
                v809 = v808 + 1;
                v808[1] = v805;
                v808[3] = v807;
                v810 = v1013;
              }
              else
              {
                sub_445FA0(&this->dwWeaponWU + 1824 * v803 + 8071);
                v811 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
                v812 = *(&this->m_bWPXS + 192 * v811 + 426);
                v813 = *(&this->m_bWPXS + 192 * v811 + 427);
                v814 = *(&this->m_bWPXS + 192 * v811 + 428);
                v1015 = *(&this->m_bWPXS + 192 * v811 + 429);
                v808 = &this->m_bWPXS + 624 * v811 + 2890;
                v808[2] = v813;
                v809 = v808 + 1;
                v808[1] = v812;
                v808[3] = v814;
                v810 = v1015;
              }
              goto LABEL_320;
            }
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v731 + 7957))(
              &this->dwWeaponWU + 1824 * v731 + 7957,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4836) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5080) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5076) = 0;
            v740 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v741 = *(&this->m_bWPXS + 192 * v740 + 414);
            v742 = *(&this->m_bWPXS + 192 * v740 + 415);
            v743 = *(&this->m_bWPXS + 192 * v740 + 416);
            v995 = *(&this->m_bWPXS + 192 * v740 + 417);
            v736 = &this->m_bWPXS + 624 * v740 + 2851;
            v736[2] = v742;
            v737 = v736 + 1;
            v736[1] = v741;
            v736[3] = v743;
            v738 = v995;
          }
          else
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v731 + 7805))(
              &this->dwWeaponWU + 1824 * v731 + 7805,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4832) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5076) = 1;
            v732 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v733 = *(&this->m_bWPXS + 192 * v732 + 398);
            v734 = *(&this->m_bWPXS + 192 * v732 + 399);
            v735 = *(&this->m_bWPXS + 192 * v732 + 400);
            v993 = *(&this->m_bWPXS + 192 * v732 + 401);
            v736 = &this->m_bWPXS + 624 * v732 + 2799;
            v736[2] = v734;
            v737 = v736 + 1;
            v736[1] = v733;
            v736[3] = v735;
            v738 = v993;
          }
          v736[4] = v738;
          v739 = v736 + 5;
          *v739 = *v737;
          v739[1] = v737[1];
          v739[2] = v737[2];
          v739[3] = v737[3];
          goto LABEL_294;
        }
        ((UIStatic *)(&this->m_bWPXS + 270 * v727 + 5624))->CreateFromTemplate();
        v816 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v817 = v931[325];
        v818 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v816 + 5] + 650);
        if ( v817 >= v818 )
        {
          if ( v817 <= v818 )
            goto LABEL_328;
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v816 + 7805))(
            &this->dwWeaponWU + 1824 * v816 + 7805,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4832) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5076) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5080) = 0;
          v826 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v827 = *(&this->m_bWPXS + 192 * v826 + 398);
          v828 = *(&this->m_bWPXS + 192 * v826 + 399);
          v829 = *(&this->m_bWPXS + 192 * v826 + 400);
          v1019 = *(&this->m_bWPXS + 192 * v826 + 401);
          v823 = &this->m_bWPXS + 624 * v826 + 2799;
          v823[2] = v828;
          v824 = v823 + 1;
          v823[1] = v827;
          v823[3] = v829;
          v825 = v1019;
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v816 + 7957))(
            &this->dwWeaponWU + 1824 * v816 + 7957,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4836) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5080) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5076) = 0;
          v819 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v820 = *(&this->m_bWPXS + 192 * v819 + 414);
          v821 = *(&this->m_bWPXS + 192 * v819 + 415);
          v822 = *(&this->m_bWPXS + 192 * v819 + 416);
          v1017 = *(&this->m_bWPXS + 192 * v819 + 417);
          v823 = &this->m_bWPXS + 624 * v819 + 2851;
          v823[2] = v821;
          v824 = v823 + 1;
          v823[1] = v820;
          v823[3] = v822;
          v825 = v1017;
        }
        v823[4] = v825;
        v830 = v823 + 5;
        *v830 = *v824;
        v830[1] = v824[1];
        v830[2] = v824[2];
        v830[3] = v824[3];
LABEL_328:
        v831 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v832 = v931[327];
        v833 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v831 + 5] + 654);
        if ( v832 >= v833 )
        {
          if ( v832 <= v833 )
            goto LABEL_339;
          *((_BYTE *)&this->m_bWPXS + 48 * v831 + 5077) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5081) = 0;
          v848 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v848 + 4832) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v848 + 7843);
            v849 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v850 = *(&this->m_bWPXS + 192 * v849 + 406);
            v851 = *(&this->m_bWPXS + 192 * v849 + 407);
            v852 = *(&this->m_bWPXS + 192 * v849 + 408);
            v1025 = *(&this->m_bWPXS + 192 * v849 + 409);
            v853 = &this->m_bWPXS + 624 * v849 + 2812;
            v853[2] = v851;
            v854 = v853 + 1;
            v853[1] = v850;
            v853[3] = v852;
            v855 = v1025;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v848 + 7843);
            v856 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v857 = *(&this->m_bWPXS + 192 * v856 + 398);
            v858 = *(&this->m_bWPXS + 192 * v856 + 399);
            v859 = *(&this->m_bWPXS + 192 * v856 + 400);
            v1027 = *(&this->m_bWPXS + 192 * v856 + 401);
            v853 = &this->m_bWPXS + 624 * v856 + 2812;
            v853[2] = v858;
            v854 = v853 + 1;
            v853[1] = v857;
            v853[3] = v859;
            v855 = v1027;
          }
          v853[4] = v855;
          v860 = v853 + 5;
          *v860 = *v854;
          v860[1] = v854[1];
          v860[2] = v854[2];
          v860[3] = v854[3];
          v847 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7843;
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v831 + 5081) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5077) = 0;
          v834 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v834 + 4836) )
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v834 + 7995);
            v835 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v836 = *(&this->m_bWPXS + 192 * v835 + 422);
            v837 = *(&this->m_bWPXS + 192 * v835 + 423);
            v838 = *(&this->m_bWPXS + 192 * v835 + 424);
            v1021 = *(&this->m_bWPXS + 192 * v835 + 425);
            v839 = &this->m_bWPXS + 624 * v835 + 2864;
            v839[2] = v837;
            v840 = v839 + 1;
            v839[1] = v836;
            v839[3] = v838;
            v841 = v1021;
          }
          else
          {
            sub_445FA0(&this->dwWeaponWU + 1824 * v834 + 7995);
            v842 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v843 = *(&this->m_bWPXS + 192 * v842 + 414);
            v844 = *(&this->m_bWPXS + 192 * v842 + 415);
            v845 = *(&this->m_bWPXS + 192 * v842 + 416);
            v1023 = *(&this->m_bWPXS + 192 * v842 + 417);
            v839 = &this->m_bWPXS + 624 * v842 + 2864;
            v839[2] = v844;
            v840 = v839 + 1;
            v839[1] = v843;
            v839[3] = v845;
            v841 = v1023;
          }
          v839[4] = v841;
          v846 = v839 + 5;
          *v846 = *v840;
          v846[1] = v840[1];
          v846[2] = v840[2];
          v846[3] = v840[3];
          v847 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7995;
        }
        (*(void ( **)(int *, int))*v847)(v847, 1);
LABEL_339:
        v861 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v862 = v931[326];
        v863 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v861 + 5] + 652);
        if ( v862 < v863 )
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v861 + 8033))(
            &this->dwWeaponWU + 1824 * v861 + 8033,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4838) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5082) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5078) = 0;
          v864 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v865 = *(&this->m_bWPXS + 192 * v864 + 422);
          v866 = *(&this->m_bWPXS + 192 * v864 + 423);
          v867 = *(&this->m_bWPXS + 192 * v864 + 424);
          v1029 = *(&this->m_bWPXS + 192 * v864 + 425);
          v868 = &this->m_bWPXS + 624 * v864 + 2877;
          v868[2] = v866;
          v869 = v868 + 1;
          v868[1] = v865;
          v868[3] = v867;
          v870 = v1029;
LABEL_343:
          v868[4] = v870;
          v875 = v868 + 5;
          *v875 = *v869;
          v875[1] = v869[1];
          v875[2] = v869[2];
          v875[3] = v869[3];
          goto LABEL_344;
        }
        if ( v862 > v863 )
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v861 + 7881))(
            &this->dwWeaponWU + 1824 * v861 + 7881,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4834) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5078) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5082) = 0;
          v871 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          v872 = *(&this->m_bWPXS + 192 * v871 + 406);
          v873 = *(&this->m_bWPXS + 192 * v871 + 407);
          v874 = *(&this->m_bWPXS + 192 * v871 + 408);
          v1031 = *(&this->m_bWPXS + 192 * v871 + 409);
          v868 = &this->m_bWPXS + 624 * v871 + 2825;
          v868[2] = v873;
          v869 = v868 + 1;
          v868[1] = v872;
          v868[3] = v874;
          v870 = v1031;
          goto LABEL_343;
        }
LABEL_344:
        v876 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v3 = v931;
        v877 = v931[328];
        v878 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v876 + 5] + 656);
        if ( v877 >= v878 )
        {
          if ( v877 > v878 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * v876 + 5079) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5083) = 0;
            (**((void ( ***)(int *, int))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 7919))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7919,
              1);
            v885 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v885 + 4834) )
            {
              ((CCBUI *)this)->AddItem(v1060, v885, 5, 0);
              sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7919);
              v886 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v887 = &this->m_bWPXS + 192 * v886 + 398;
            }
            else
            {
              ((CCBUI *)this)->AddItem(nCol, v885, 5, 3);
              sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 7919);
              v886 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v887 = &this->m_bWPXS + 192 * v886 + 410;
            }
            ((CCBUI *)(&this->m_bWPXS + 624 * v886 + 2838))->SetItemData(*v887, v887[1], v887[2], v887[3]);
          }
          goto LABEL_353;
        }
        *((_BYTE *)&this->m_bWPXS + 48 * v876 + 5083) = 1;
        *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5079) = 0;
        v879 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        if ( !*((_BYTE *)&this->m_bWPXS + 48 * v879 + 4838) )
        {
          ((CCBUI *)this)->AddItem(pData, v879, 5, 7);
          sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 8071);
          v884 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          ((CCBUI *)(&this->m_bWPXS + 624 * v884 + 2890))->SetItemData(*(&this->m_bWPXS + 192 * v884 + 426), *(&this->m_bWPXS + 192 * v884 + 427), *(&this->m_bWPXS + 192 * v884 + 428), *(&this->m_bWPXS + 192 * v884 + 429));
          goto LABEL_321;
        }
        sub_445FA0(&this->dwWeaponWU + 1824 * v879 + 8071);
        v880 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v881 = *(&this->m_bWPXS + 192 * v880 + 414);
        v882 = *(&this->m_bWPXS + 192 * v880 + 415);
        v883 = *(&this->m_bWPXS + 192 * v880 + 416);
        v1033 = *(&this->m_bWPXS + 192 * v880 + 417);
        v808 = &this->m_bWPXS + 624 * v880 + 2890;
        v808[2] = v882;
        v809 = v808 + 1;
        v808[1] = v881;
        v808[3] = v883;
        v810 = v1033;
LABEL_320:
        v808[4] = v810;
        v815 = v808 + 5;
        *v815 = *v809;
        v815[1] = v809[1];
        v815[2] = v809[2];
        v815[3] = v809[3];
LABEL_321:
        (**((void ( ***)(int *, int))&this->dwWeaponWU
          + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
          + 8071))(
          &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 8071,
          1);
        v3 = v931;
LABEL_353:
        (**((void ( ***)(int *, int))&this->m_bWPXS
          + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
          + 5489))(
          &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5489,
          1);
        (**((void ( ***)(int *, int))&this->m_bWPXS
          + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
          + 5624))(
          &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5624,
          1);
LABEL_406:
        result = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 1;
        *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] = result;
        if ( result < 5 )
          continue;
        return result;
      case 0xB:
        v888 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        if ( !*((_BYTE *)v3 + v888 + 614) )
          goto LABEL_406;
        v889 = (CCBUI *)*((_DWORD *)&(&this->pNGHVarianceParticle)[78] + 6);
        if ( !Buffer.m_partyActor.m_dwMatMsg[352 * v888 + 8] )
        {
          ((CCBUI *)v889)->fn_469D40();
          ((UIStatic *)(&this->m_bWPXS
                                                  + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                  + 5444))->CreateFromTemplate();
          for ( ii = 0; ii < 8; ++ii )
            (**((void ( ***)(int *, _DWORD))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 38 * ii
              + 6589))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 38 * ii + 6589,
              0);
          v891 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( (__int16)v3[325] <= 0 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * v891 + 5044) = 0;
          }
          else
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v891 + 6589))(
              &this->dwWeaponWU + 1824 * v891 + 6589,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4800) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5044) = 1;
            v892 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            ((CCBUI *)(&this->m_bWPXS + 624 * v892 + 2383))->SetItemData(*(&this->m_bWPXS + 192 * v892 + 270), *(&this->m_bWPXS + 192 * v892 + 271), *(&this->m_bWPXS + 192 * v892 + 272), *(&this->m_bWPXS + 192 * v892 + 273));
          }
          if ( (__int16)v3[327] <= 0 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5045) = 0;
          }
          else
          {
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5045) = 1;
            v893 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v893 + 4800) )
            {
              ((CCBUI *)this)->AddItem(v1058, v893, 1, 2);
              sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6627);
              v894 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v895 = &this->m_bWPXS + 192 * v894 + 278;
            }
            else
            {
              ((CCBUI *)this)->AddItem(v1054, v893, 1, 0);
              sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6627);
              v894 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v895 = &this->m_bWPXS + 192 * v894 + 270;
            }
            ((CCBUI *)(&this->m_bWPXS + 624 * v894 + 2396))->SetItemData(*v895, v895[1], v895[2], v895[3]);
            (**((void ( ***)(int *, int))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 6627))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6627,
              1);
          }
          v896 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( (__int16)v3[326] <= 0 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * v896 + 5046) = 0;
          }
          else
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v896 + 6665))(
              &this->dwWeaponWU + 1824 * v896 + 6665,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4802) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5046) = 1;
            v897 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            ((CCBUI *)(&this->m_bWPXS + 624 * v897 + 2409))->SetItemData(*(&this->m_bWPXS + 192 * v897 + 278), *(&this->m_bWPXS + 192 * v897 + 279), *(&this->m_bWPXS + 192 * v897 + 280), *(&this->m_bWPXS + 192 * v897 + 281));
          }
          if ( (__int16)v3[328] <= 0 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5047) = 0;
          }
          else
          {
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5047) = 1;
            v898 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v898 + 4802) )
            {
              ((CCBUI *)this)->AddItem(v1062, v898, 1, 0);
              sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6703);
              v899 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v900 = &this->m_bWPXS + 192 * v899 + 270;
            }
            else
            {
              ((CCBUI *)this)->AddItem(v1056, v898, 1, 3);
              sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6703);
              v899 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v900 = &this->m_bWPXS + 192 * v899 + 282;
            }
            ((CCBUI *)(&this->m_bWPXS + 624 * v899 + 2422))->SetItemData(*v900, v900[1], v900[2], v900[3]);
            (**((void ( ***)(int *, int))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 6703))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6703,
              1);
          }
          goto LABEL_405;
        }
        ((CCBUI *)v889)->fn_469D40();
        ((UIStatic *)(&this->m_bWPXS
                                                + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
                                                + 5444))->CreateFromTemplate();
        v901 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v902 = v3[325];
        v903 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v901 + 8] + 650);
        if ( v902 >= v903 )
        {
          if ( v902 > v903 )
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v901 + 6589))(
              &this->dwWeaponWU + 1824 * v901 + 6589,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4800) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5044) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5048) = 0;
            v905 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            ((CCBUI *)(&this->m_bWPXS + 624 * v905 + 2383))->SetItemData(*(&this->m_bWPXS + 192 * v905 + 270), *(&this->m_bWPXS + 192 * v905 + 271), *(&this->m_bWPXS + 192 * v905 + 272), *(&this->m_bWPXS + 192 * v905 + 273));
          }
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v901 + 6741))(
            &this->dwWeaponWU + 1824 * v901 + 6741,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4804) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5048) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5044) = 0;
          v904 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          ((CCBUI *)(&this->m_bWPXS + 624 * v904 + 2435))->SetItemData(*(&this->m_bWPXS + 192 * v904 + 286), *(&this->m_bWPXS + 192 * v904 + 287), *(&this->m_bWPXS + 192 * v904 + 288), *(&this->m_bWPXS + 192 * v904 + 289));
        }
        v906 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v907 = v3[327];
        v908 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v906 + 8] + 654);
        if ( v907 >= v908 )
        {
          if ( v907 <= v908 )
            goto LABEL_391;
          *((_BYTE *)&this->m_bWPXS + 48 * v906 + 5045) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5049) = 0;
          v913 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v913 + 4800) )
          {
            ((CCBUI *)this)->AddItem(v1053, v913, 1, 2);
            sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6627);
            v914 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v915 = &this->m_bWPXS + 192 * v914 + 278;
          }
          else
          {
            ((CCBUI *)this)->AddItem(v1055, v913, 1, 0);
            sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6627);
            v914 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v915 = &this->m_bWPXS + 192 * v914 + 270;
          }
          ((CCBUI *)(&this->m_bWPXS + 624 * v914 + 2396))->SetItemData(*v915, v915[1], v915[2], v915[3]);
          v912 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6627;
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v906 + 5049) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5045) = 0;
          v909 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v909 + 4804) )
          {
            ((CCBUI *)this)->AddItem(v1050, v909, 1, 6);
            sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6779);
            v910 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v911 = &this->m_bWPXS + 192 * v910 + 294;
          }
          else
          {
            ((CCBUI *)this)->AddItem(v1051, v909, 1, 4);
            sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6779);
            v910 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v911 = &this->m_bWPXS + 192 * v910 + 286;
          }
          ((CCBUI *)(&this->m_bWPXS + 624 * v910 + 2448))->SetItemData(*v911, v911[1], v911[2], v911[3]);
          v912 = &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6779;
        }
        (*(void ( **)(int *, int))*v912)(v912, 1);
LABEL_391:
        v916 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v917 = v3[326];
        v918 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v916 + 8] + 652);
        if ( v917 >= v918 )
        {
          if ( v917 > v918 )
          {
            (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v916 + 6665))(
              &this->dwWeaponWU + 1824 * v916 + 6665,
              1);
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4802) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5046) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5050) = 0;
            v920 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            ((CCBUI *)(&this->m_bWPXS + 624 * v920 + 2409))->SetItemData(*(&this->m_bWPXS + 192 * v920 + 278), *(&this->m_bWPXS + 192 * v920 + 279), *(&this->m_bWPXS + 192 * v920 + 280), *(&this->m_bWPXS + 192 * v920 + 281));
          }
        }
        else
        {
          (**((void ( ***)(int *, int))&this->dwWeaponWU + 1824 * v916 + 6817))(
            &this->dwWeaponWU + 1824 * v916 + 6817,
            1);
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 4806) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5050) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5046) = 0;
          v919 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          ((CCBUI *)(&this->m_bWPXS + 624 * v919 + 2461))->SetItemData(*(&this->m_bWPXS + 192 * v919 + 294), *(&this->m_bWPXS + 192 * v919 + 295), *(&this->m_bWPXS + 192 * v919 + 296), *(&this->m_bWPXS + 192 * v919 + 297));
        }
        v921 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
        v922 = v3[328];
        v923 = *(_WORD *)(Buffer.m_partyActor.m_dwMatMsg[352 * v921 + 8] + 656);
        if ( v922 >= v923 )
        {
          if ( v922 > v923 )
          {
            *((_BYTE *)&this->m_bWPXS + 48 * v921 + 5047) = 1;
            *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5051) = 0;
            (**((void ( ***)(int *, int))&this->dwWeaponWU
              + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
              + 6703))(
              &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6703,
              1);
            v927 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            if ( *((_BYTE *)&this->m_bWPXS + 48 * v927 + 4802) )
            {
              ((CCBUI *)this)->AddItem(v1061, v927, 1, 0);
              sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6703);
              v928 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v929 = &this->m_bWPXS + 192 * v928 + 270;
            }
            else
            {
              ((CCBUI *)this)->AddItem(v1063, v927, 1, 3);
              sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6703);
              v928 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
              v929 = &this->m_bWPXS + 192 * v928 + 282;
            }
            ((CCBUI *)(&this->m_bWPXS + 624 * v928 + 2422))->SetItemData(*v929, v929[1], v929[2], v929[3]);
          }
        }
        else
        {
          *((_BYTE *)&this->m_bWPXS + 48 * v921 + 5051) = 1;
          *((_BYTE *)&this->m_bWPXS + 48 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5047) = 0;
          v924 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
          if ( *((_BYTE *)&this->m_bWPXS + 48 * v924 + 4806) )
          {
            ((CCBUI *)this)->AddItem(v1057, v924, 1, 4);
            sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6855);
            v925 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v926 = &this->m_bWPXS + 192 * v925 + 286;
          }
          else
          {
            ((CCBUI *)this)->AddItem(v1059, v924, 1, 7);
            sub_445FA0(&this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6855);
            v925 = *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248];
            v926 = &this->m_bWPXS + 192 * v925 + 298;
          }
          ((CCBUI *)(&this->m_bWPXS + 624 * v925 + 2474))->SetItemData(*v926, v926[1], v926[2], v926[3]);
          (**((void ( ***)(int *, int))&this->dwWeaponWU
            + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
            + 6855))(
            &this->dwWeaponWU + 1824 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 6855,
            1);
        }
LABEL_405:
        (**((void ( ***)(int *, int))&this->m_bWPXS
          + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248]
          + 5444))(
          &this->m_bWPXS + 270 * *(_DWORD *)&this->m_RoleTask.m_taskFile.m_token[248] + 5444,
          1);
        goto LABEL_406;
      default:
        goto LABEL_406;
    }
  }
}

// 0x00469D90
void PlayerMgr::SetupPlayerDisplay(int nVal)
{
  CHAR *v3; // ebx
  CHAR *v4; // ebp
  RoleAtt *v5; // ecx
  void (__stdcall *v6)(LPSTR, LPCSTR); // ebp
  LPCSTR v7; // eax
  CHAR String1[253]; // [esp+0x10] [ebp-0x100] BYREF
  __int16 v9; // [esp+0x10D] [ebp-0x3]
  char v10; // [esp+0x10F] [ebp-0x1]

  v3 = &this->m_RoleTask.m_TaskData[4];
  sprintf(&this->m_RoleTask.m_TaskData[4], g_szSceneUIText);
  memset(String1, 0, sizeof(String1));
  v9 = 0;
  v10 = 0;
  v4 = sub_458F70((LPCSTR)(*(&this->dwWeaponWU + nVal + 3666) + 96), (int)asc_5B74B8, String1);
  if ( lstrlenA(v4) <= 0 )
  {
    ((RoleAtt *)v5)->FormatAttributeText();
    v6 = (void ( *)(LPSTR, LPCSTR))lstrcatA;
    lstrcatA(v3, v7);
  }
  else
  {
    lstrcpyA(v3, v4);
    v6 = (void ( *)(LPSTR, LPCSTR))lstrcatA;
  }
  ((UICaption *)(&this->pNGHVarianceParticle + 3230))->SetEnable((int)String1, 0);
  switch ( *(_BYTE *)(*(&this->dwWeaponWU + nVal + 3666) + 613) )
  {
    case 1:
    case 3:
      v6(v3, asc_5B74B4);
      v6(v3, (LPCSTR)dword_DDAA3C);
      break;
    case 2:
    case 5:
    case 6:
      v6(v3, asc_5B74B4);
      v6(v3, byte_DCEB3C);
      break;
    case 4:
    case 7:
      v6(v3, asc_5B74B4);
      v6(v3, (LPCSTR)dword_DDA93C);
      break;
    default:
      break;
  }
  ((UICaption *)(&this->pNGHVarianceParticle + 3272))->SetEnable((int)v3, 0);
}

// 0x00469EB0
BOOL PlayerMgr::HandleInput(int nInputID, int nParam, int nFlags)
{
  BOOL result; // eax
  int v7; // eax
  int v8; // ecx
  int v10; // edx
  int v11; // ebx
  int *v12; // ecx
  void **v13; // edx
  _DWORD *v14; // eax
  _DWORD *v15; // eax
  int *v16; // edx
  int *v17; // ecx
  int v18; // edx
  int v19; // edx
  char v20; // bl
  _BYTE *v21; // edx
  int *v22; // ecx
  signed __int16 *v23; // eax
  _DWORD *v24; // eax
  _DWORD *v25; // eax
  int *v26; // edx
  int v27; // ebx
  int *v28; // ecx
  void **v29; // eax
  _DWORD *v30; // eax
  _DWORD *v31; // eax
  int *v32; // edx
  int v33; // ebx
  int *v34; // ecx
  unsigned int *v35; // eax
  _DWORD *v36; // eax
  _DWORD *v37; // eax
  int *v38; // edx
  int v39; // ebx
  int *v40; // ecx
  unsigned int *v41; // eax
  _DWORD *v42; // eax
  _DWORD *v43; // eax
  int *v44; // edx
  int v45; // ebx
  int *v46; // ecx
  unsigned int *v47; // eax
  _DWORD *v48; // eax
  _DWORD *v49; // eax
  int *v50; // edx
  RoleSystem *v51; // esi
  int *v52; // eax
  int v53; // esi
  int v54; // edx
  int nInputIDa; // [esp+0x14] [ebp+0x4]
  CParticleEffect **nParama; // [esp+0x18] [ebp+0x8]
  CParticleEffect **nParamb; // [esp+0x18] [ebp+0x8]
  CParticleEffect **nParamc; // [esp+0x18] [ebp+0x8]
  CParticleEffect **nParamd; // [esp+0x18] [ebp+0x8]
  CParticleEffect **nParame; // [esp+0x18] [ebp+0x8]
  CParticleEffect **nParamf; // [esp+0x18] [ebp+0x8]
  int nFlagsa; // [esp+0x1C] [ebp+0xC]

  if ( *((_BYTE *)&(&this->pNGHVarianceParticle)[78] + 20) )
  {
    LOBYTE(result) = 0;
  }
  else if ( nFlags >= 0 )
  {
    v7 = *((_DWORD *)&this->pNGHVarianceParticle + 1266);
    v8 = *(_DWORD *)(v7 + 4 * nFlags);
    result = v7 + 4 * nFlags;
    if ( v8 > 0 )
    {
      if ( *((_BYTE *)&this->pNGHVarianceParticle + 5032) )
      {
        v10 = 6 * nInputID;
        nFlagsa = 6 * nInputID;
        nInputIDa = 6 * nInputID + nParam;
        if ( *((_DWORD *)&this->pNGHVarianceParticle + nInputIDa + 1267) == nFlags )
        {
          LOBYTE(result) = 0;
        }
        else
        {
          switch ( nParam )
          {
            case 0:
              v11 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v11 + 612) == 7 && *(_BYTE *)(v11 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5033) )
                {
                  nParama = &this->pNGHVarianceParticle + 6 * nInputID + 1267;
                  if ( *nParama != (CParticleEffect *)nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                    v12 = &this->dwWeaponWU + 352 * nInputID + 4383;
                    v13 = &Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 1;
                    *v13 = (void *)*v12;
                    v13[1] = (void *)*(&this->dwWeaponWU + 352 * nInputID + 4384);
                    v13[2] = (void *)*(&this->dwWeaponWU + 352 * nInputID + 4385);
                    *v12 = 0;
                    v12[1] = 0;
                    v12[2] = 0;
                    v14 = (_DWORD *)(*((_DWORD *)&this->pNGHVarianceParticle + 1266) + 4 * (_DWORD)*nParama);
                    ++*v14;
                    v10 = nFlagsa;
                    v15 = (_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * (_DWORD)*nParama);
                    --*v15;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                }
                *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5033) = 1;
                (**((void ( ***)(CParticleEffect **, int))&(&this->pNGHVarianceParticle)[2]
                  + 228 * nInputID
                  + 6))(
                  &(&this->pNGHVarianceParticle)[2] + 228 * nInputID + 6,
                  1);
                *((_DWORD *)&this->pNGHVarianceParticle + 6 * nInputID + 1267) = nFlags;
                if ( *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 3) )
                {
                  *(&this->dwWeaponWU + 352 * nInputID + 4383) = *((_DWORD *)&Buffer.m_partyActor.m_pParticleData
                                                                 + 352 * nInputID
                                                                 + 1);
                  *(&this->dwWeaponWU + 352 * nInputID + 4384) = *((_DWORD *)&Buffer.m_partyActor.m_pParticleData
                                                                 + 352 * nInputID
                                                                 + 2);
                  *(&this->dwWeaponWU + 352 * nInputID + 4385) = *((_DWORD *)&Buffer.m_partyActor.m_pParticleData
                                                                 + 352 * nInputID
                                                                 + 3);
                }
                else
                {
                  v16 = &this->dwWeaponWU + 352 * nInputID + 4383;
                  *v16 = 0;
                  v16[1] = 0;
                  v16[2] = 0;
                }
                *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 1) = **((_DWORD **)&this->dwWeaponWU
                                                                                          + nFlags
                                                                                          + 3666);
                *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 2) = 1;
                *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 3) = *(&this->dwWeaponWU
                                                                                         + nFlags
                                                                                         + 3666);
                v17 = &this->m_bWPXS + 270 * nInputID + 5399;
                goto LABEL_72;
              }
              break;
            case 1:
              v45 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v45 + 612) == 11 && *(_BYTE *)(v45 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5034) )
                {
                  nParamf = &this->pNGHVarianceParticle + 6 * nInputID + 1268;
                  if ( *nParamf != (CParticleEffect *)nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                    v46 = &this->dwWeaponWU + 352 * nInputID + 4395;
                    v47 = &Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 6];
                    *v47 = *v46;
                    v47[1] = *(&this->dwWeaponWU + 352 * nInputID + 4396);
                    v47[2] = *(&this->dwWeaponWU + 352 * nInputID + 4397);
                    *v46 = 0;
                    v46[1] = 0;
                    v46[2] = 0;
                    v48 = (_DWORD *)(*((_DWORD *)&this->pNGHVarianceParticle + 1266) + 4 * (_DWORD)*nParamf);
                    ++*v48;
                    v49 = (_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * (_DWORD)*nParamf);
                    v10 = nFlagsa;
                    --*v49;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                }
                *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5034) = 1;
                (**((void ( ***)(CParticleEffect **, int))&this->pNGHVarianceParticle + 228 * nInputID + 156))(
                  &this->pNGHVarianceParticle + 228 * nInputID + 156,
                  1);
                *((_DWORD *)&this->pNGHVarianceParticle + 6 * nInputID + 1268) = nFlags;
                if ( Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8] )
                {
                  *(&this->dwWeaponWU + 352 * nInputID + 4395) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 6];
                  *(&this->dwWeaponWU + 352 * nInputID + 4396) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 7];
                  *(&this->dwWeaponWU + 352 * nInputID + 4397) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8];
                }
                else
                {
                  v50 = &this->dwWeaponWU + 352 * nInputID + 4395;
                  *v50 = 0;
                  v50[1] = 0;
                  v50[2] = 0;
                }
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 6] = **((_DWORD **)&this->dwWeaponWU + nFlags + 3666);
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 7] = 1;
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8] = *(&this->dwWeaponWU + nFlags + 3666);
                v17 = &this->m_bWPXS + 270 * nInputID + 5444;
                goto LABEL_72;
              }
              break;
            case 2:
              v33 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v33 + 612) == 10 && *(_BYTE *)(v33 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5035) )
                {
                  nParamd = &this->pNGHVarianceParticle + 6 * nInputID + 1269;
                  if ( *nParamd != (CParticleEffect *)nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                    v34 = &this->dwWeaponWU + 352 * nInputID + 4389;
                    v35 = &Buffer.m_partyActor.m_dwMatMsg[352 * nInputID];
                    *v35 = *v34;
                    v35[1] = *(&this->dwWeaponWU + 352 * nInputID + 4390);
                    v35[2] = *(&this->dwWeaponWU + 352 * nInputID + 4391);
                    *v34 = 0;
                    v34[1] = 0;
                    v34[2] = 0;
                    v36 = (_DWORD *)(*((_DWORD *)&this->pNGHVarianceParticle + 1266) + 4 * (_DWORD)*nParamd);
                    ++*v36;
                    v37 = (_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * (_DWORD)*nParamd);
                    v10 = nFlagsa;
                    --*v37;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                }
                *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5035) = 1;
                (**((void ( ***)(CParticleEffect **, int))&this->pNGHVarianceParticle + 228 * nInputID + 194))(
                  &this->pNGHVarianceParticle + 228 * nInputID + 194,
                  1);
                *((_DWORD *)&this->pNGHVarianceParticle + 6 * nInputID + 1269) = nFlags;
                *((_BYTE *)&(&this->pNGHVarianceParticle)[23] + 2 * nInputID + 44) = 1;
                if ( Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2] )
                {
                  *(&this->dwWeaponWU + 352 * nInputID + 4389) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID];
                  *(&this->dwWeaponWU + 352 * nInputID + 4390) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 1];
                  *(&this->dwWeaponWU + 352 * nInputID + 4391) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2];
                }
                else
                {
                  v38 = &this->dwWeaponWU + 352 * nInputID + 4389;
                  *v38 = 0;
                  v38[1] = 0;
                  v38[2] = 0;
                }
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID] = **((_DWORD **)&this->dwWeaponWU + nFlags + 3666);
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 1] = 1;
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2] = *(&this->dwWeaponWU + nFlags + 3666);
                v17 = &this->m_bWPXS + 270 * nInputID + 5489;
                goto LABEL_72;
              }
              break;
            case 3:
              v18 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v18 + 612) == 8 && *(_BYTE *)(v18 + nInputID + 614) )
              {
                v19 = 3 * nInputID + 46722;
                v20 = *((_BYTE *)&this->m_pMsgBuffer.m_pData + 2 * v19);
                v21 = (char *)this + 2 * v19;
                if ( v20 )
                {
                  nParamb = &this->pNGHVarianceParticle + 6 * nInputID + 1270;
                  if ( *nParamb != (CParticleEffect *)nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                    v22 = &this->dwWeaponWU + 352 * nInputID + 4380;
                    v23 = &Buffer.m_partyActor.m_nAnimFrame + 704 * nInputID + 2;
                    *(_DWORD *)v23 = *v22;
                    *((_DWORD *)v23 + 1) = *(&this->dwWeaponWU + 352 * nInputID + 4381);
                    *((_DWORD *)v23 + 2) = *(&this->dwWeaponWU + 352 * nInputID + 4382);
                    *v22 = 0;
                    v22[1] = 0;
                    v22[2] = 0;
                    v24 = (_DWORD *)(*((_DWORD *)&this->pNGHVarianceParticle + 1266) + 4 * (_DWORD)*nParamb);
                    ++*v24;
                    v25 = (_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * (_DWORD)*nParamb);
                    --*v25;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                }
                *v21 = 1;
                (**((void ( ***)(CParticleEffect **, int))&(&this->pNGHVarianceParticle)[4]
                  + 228 * nInputID
                  + 8))(
                  &(&this->pNGHVarianceParticle)[4] + 228 * nInputID + 8,
                  1);
                *((_DWORD *)&this->pNGHVarianceParticle + 6 * nInputID + 1270) = nFlags;
                if ( *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * nInputID) )
                {
                  *(&this->dwWeaponWU + 352 * nInputID + 4380) = *((_DWORD *)&Buffer.m_partyActor.m_nAnimFrame
                                                                 + 352 * nInputID
                                                                 + 1);
                  *(&this->dwWeaponWU + 352 * nInputID + 4381) = *((_DWORD *)&Buffer.m_partyActor.m_nAnimFrame
                                                                 + 352 * nInputID
                                                                 + 2);
                  *(&this->dwWeaponWU + 352 * nInputID + 4382) = *((_DWORD *)&Buffer.m_partyActor.m_pParticleData
                                                                 + 352 * nInputID);
                }
                else
                {
                  v26 = &this->dwWeaponWU + 352 * nInputID + 4380;
                  *v26 = 0;
                  v26[1] = 0;
                  v26[2] = 0;
                }
                *((_DWORD *)&Buffer.m_partyActor.m_nAnimFrame + 352 * nInputID + 1) = **((_DWORD **)&this->dwWeaponWU
                                                                                       + nFlags
                                                                                       + 3666);
                *((_DWORD *)&Buffer.m_partyActor.m_nAnimFrame + 352 * nInputID + 2) = 1;
                *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * nInputID) = *(&this->dwWeaponWU + nFlags + 3666);
                v17 = &this->m_bWPXS + 270 * nInputID + 5534;
                goto LABEL_72;
              }
              break;
            case 4:
              v27 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v27 + 612) == 9 && *(_BYTE *)(v27 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5037) )
                {
                  nParamc = &this->pNGHVarianceParticle + 6 * nInputID + 1271;
                  if ( *nParamc != (CParticleEffect *)nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                    v28 = &this->dwWeaponWU + 352 * nInputID + 4386;
                    v29 = &Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 4;
                    *v29 = (void *)*v28;
                    v29[1] = (void *)*(&this->dwWeaponWU + 352 * nInputID + 4387);
                    v29[2] = (void *)*(&this->dwWeaponWU + 352 * nInputID + 4388);
                    *v28 = 0;
                    v28[1] = 0;
                    v28[2] = 0;
                    v30 = (_DWORD *)(*((_DWORD *)&this->pNGHVarianceParticle + 1266) + 4 * (_DWORD)*nParamc);
                    ++*v30;
                    v31 = (_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * (_DWORD)*nParamc);
                    v10 = nFlagsa;
                    --*v31;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                }
                *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5037) = 1;
                (**((void ( ***)(CParticleEffect **, int))&this->pNGHVarianceParticle + 228 * nInputID + 270))(
                  &this->pNGHVarianceParticle + 228 * nInputID + 270,
                  1);
                *((_DWORD *)&this->pNGHVarianceParticle + 6 * nInputID + 1271) = nFlags;
                if ( *((_DWORD *)&Buffer.m_partyActor.m_fAnimDelta + 352 * nInputID) )
                {
                  *(&this->dwWeaponWU + 352 * nInputID + 4386) = *((_DWORD *)&Buffer.m_partyActor.m_pParticleData
                                                                 + 352 * nInputID
                                                                 + 4);
                  *(&this->dwWeaponWU + 352 * nInputID + 4387) = *((_DWORD *)&Buffer.m_partyActor.m_pParticleData
                                                                 + 352 * nInputID
                                                                 + 5);
                  *(&this->dwWeaponWU + 352 * nInputID + 4388) = *((_DWORD *)&Buffer.m_partyActor.m_fAnimDelta
                                                                 + 352 * nInputID);
                }
                else
                {
                  v32 = &this->dwWeaponWU + 352 * nInputID + 4386;
                  *v32 = 0;
                  v32[1] = 0;
                  v32[2] = 0;
                }
                *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 4) = **((_DWORD **)&this->dwWeaponWU
                                                                                          + nFlags
                                                                                          + 3666);
                *((_DWORD *)&Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 5) = 1;
                *((_DWORD *)&Buffer.m_partyActor.m_fAnimDelta + 352 * nInputID) = *(&this->dwWeaponWU + nFlags + 3666);
                v17 = &this->m_bWPXS + 270 * nInputID + 5579;
                goto LABEL_72;
              }
              break;
            case 5:
              v39 = *(&this->dwWeaponWU + nFlags + 3666);
              if ( *(_BYTE *)(v39 + 612) == 10 && *(_BYTE *)(v39 + nInputID + 614) )
              {
                if ( *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5038) )
                {
                  nParame = &this->pNGHVarianceParticle + 6 * nInputID + 1272;
                  if ( *nParame != (CParticleEffect *)nFlags )
                  {
                    *(_DWORD *)result = v8 - 1;
                    ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                    v40 = &this->dwWeaponWU + 352 * nInputID + 4392;
                    v41 = &Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 3];
                    *v41 = *v40;
                    v41[1] = *(&this->dwWeaponWU + 352 * nInputID + 4393);
                    v41[2] = *(&this->dwWeaponWU + 352 * nInputID + 4394);
                    *v40 = 0;
                    v40[1] = 0;
                    v40[2] = 0;
                    v42 = (_DWORD *)(*((_DWORD *)&this->pNGHVarianceParticle + 1266) + 4 * (_DWORD)*nParame);
                    ++*v42;
                    v43 = (_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * (_DWORD)*nParame);
                    v10 = nFlagsa;
                    --*v43;
                  }
                }
                else
                {
                  *(_DWORD *)result = v8 - 1;
                  ++*(_DWORD *)(*((_DWORD *)&(&this->pNGHVarianceParticle)[23] + 9) + 4 * nFlags);
                }
                *((_BYTE *)&this->pNGHVarianceParticle + v10 + 5038) = 1;
                (**((void ( ***)(CParticleEffect **, int))&this->pNGHVarianceParticle + 228 * nInputID + 308))(
                  &this->pNGHVarianceParticle + 228 * nInputID + 308,
                  1);
                *((_DWORD *)&this->pNGHVarianceParticle + 6 * nInputID + 1272) = nFlags;
                *((_BYTE *)&(&this->pNGHVarianceParticle)[23] + 2 * nInputID + 45) = 1;
                if ( Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5] )
                {
                  *(&this->dwWeaponWU + 352 * nInputID + 4392) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 3];
                  *(&this->dwWeaponWU + 352 * nInputID + 4393) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 4];
                  *(&this->dwWeaponWU + 352 * nInputID + 4394) = Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5];
                }
                else
                {
                  v44 = &this->dwWeaponWU + 352 * nInputID + 4392;
                  *v44 = 0;
                  v44[1] = 0;
                  v44[2] = 0;
                }
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 3] = **((_DWORD **)&this->dwWeaponWU + nFlags + 3666);
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 4] = 1;
                Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5] = *(&this->dwWeaponWU + nFlags + 3666);
                v17 = &this->m_bWPXS + 270 * nInputID + 5624;
LABEL_72:
                ((CCBResultWindow *)v17)->SetDirty();
              }
              break;
            default:
              break;
          }
          v51 = (RoleSystem *)((char *)&Buffer + 1408 * nInputID);
          ((RoleSystem *)v51)->RecalcAggregatedStats(0);
          v52 = (int *)&v51->m_partyActor.m_curact[39];
          v53 = 12;
          do
          {
            v54 = *(v52 - 12);
            if ( *v52 < v54 )
            {
              if ( *v52 <= 0 )
                *v52 = 0;
            }
            else
            {
              *v52 = v54;
            }
            ++v52;
            --v53;
          }
          while ( v53 );
          result = this->CreatePanelElements((CCBUIPanel *)nFlags);
          LOBYTE(result) = *((_BYTE *)&this->pNGHVarianceParticle + nInputIDa + 5033);
        }
      }
      else
      {
        LOBYTE(result) = 0;
      }
    }
    else
    {
      LOBYTE(result) = 0;
    }
  }
  else
  {
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x00471220
char PlayerMgr::ToggleSlot0(unsigned __int8 pData)
{
  void ( **v3)(CParticleEffect **, _DWORD); // edx
  CParticleEffect **v4; // edi
  int v5; // ebx
  CParticleEffect **v6; // ebp
  CParticleEffect **v7; // edi
  char result; // al
  CParticleEffect *v9; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  v3 = (void ( **)(CParticleEffect **, _DWORD))*((_DWORD *)&this->pNGHVarianceParticle + 3294);
  v4 = &this->pNGHVarianceParticle + 3294;
  *((_BYTE *)&this->pNGHVarianceParticle + 14032) = pData;
  (*v3)(&this->pNGHVarianceParticle + 3294, pData);
  v5 = 0;
  v6 = v4;
  pDataa = 0;
  v7 = &(&this->pNGHVarianceParticle)[62] + 13;
  do
  {
    result = *((_BYTE *)&this->pNGHVarianceParticle + v5 + 14032);
    if ( result )
    {
      *v7 = (CParticleEffect *)(pDataa * *((_DWORD *)&this->pNGHVarianceParticle + 3505)
                              + (*((_DWORD *)&this->pNGHVarianceParticle + 3505)
                               - *((_DWORD *)&this->pNGHVarianceParticle + 3507))
                              / 2);
      v9 = (CParticleEffect *)*((_DWORD *)&this->pNGHVarianceParticle + 3504);
      *(v7 - 1) = v9;
      v7[1] = (CParticleEffect *)((char *)v9 + *((_DWORD *)&this->pNGHVarianceParticle + 3506));
      v7[2] = (CParticleEffect *)((char *)*v7 + *((_DWORD *)&this->pNGHVarianceParticle + 3507));
      result = sub_445FA0(v6);
      ++pDataa;
    }
    ++v5;
    v7 += 4;
    v6 += 38;
  }
  while ( v5 < 5 );
  return result;
}

// 0x004712D0
char PlayerMgr::ToggleSlot1(unsigned __int8 pData)
{
  void ( **v3)(CParticleEffect **, _DWORD); // edx
  int v4; // ebx
  CParticleEffect **v5; // ebp
  CParticleEffect **v6; // edi
  char result; // al
  CParticleEffect *v8; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  v3 = (void ( **)(CParticleEffect **, _DWORD))*((_DWORD *)&this->pNGHVarianceParticle + 3332);
  *((_BYTE *)&this->pNGHVarianceParticle + 14033) = pData;
  (*v3)(&this->pNGHVarianceParticle + 3332, pData);
  v4 = 0;
  v5 = &this->pNGHVarianceParticle + 3294;
  pDataa = 0;
  v6 = &(&this->pNGHVarianceParticle)[62] + 13;
  do
  {
    result = *((_BYTE *)&this->pNGHVarianceParticle + v4 + 14032);
    if ( result )
    {
      *v6 = (CParticleEffect *)(pDataa * *((_DWORD *)&this->pNGHVarianceParticle + 3505)
                              + (*((_DWORD *)&this->pNGHVarianceParticle + 3505)
                               - *((_DWORD *)&this->pNGHVarianceParticle + 3507))
                              / 2);
      v8 = (CParticleEffect *)*((_DWORD *)&this->pNGHVarianceParticle + 3504);
      *(v6 - 1) = v8;
      v6[1] = (CParticleEffect *)((char *)v8 + *((_DWORD *)&this->pNGHVarianceParticle + 3506));
      v6[2] = (CParticleEffect *)((char *)*v6 + *((_DWORD *)&this->pNGHVarianceParticle + 3507));
      result = sub_445FA0(v5);
      ++pDataa;
    }
    ++v4;
    v6 += 4;
    v5 += 38;
  }
  while ( v4 < 5 );
  return result;
}

// 0x00471380
char PlayerMgr::ToggleSlot2(unsigned __int8 pData)
{
  void ( **v3)(CParticleEffect **, _DWORD); // edx
  int v4; // ebx
  CParticleEffect **v5; // ebp
  CParticleEffect **v6; // edi
  char result; // al
  CParticleEffect *v8; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  v3 = (void ( **)(CParticleEffect **, _DWORD))*((_DWORD *)&(&this->pNGHVarianceParticle)[60] + 10);
  *((_BYTE *)&this->pNGHVarianceParticle + 14034) = pData;
  (*v3)(&(&this->pNGHVarianceParticle)[60] + 10, pData);
  v4 = 0;
  v5 = &this->pNGHVarianceParticle + 3294;
  pDataa = 0;
  v6 = &(&this->pNGHVarianceParticle)[62] + 13;
  do
  {
    result = *((_BYTE *)&this->pNGHVarianceParticle + v4 + 14032);
    if ( result )
    {
      *v6 = (CParticleEffect *)(pDataa * *((_DWORD *)&this->pNGHVarianceParticle + 3505)
                              + (*((_DWORD *)&this->pNGHVarianceParticle + 3505)
                               - *((_DWORD *)&this->pNGHVarianceParticle + 3507))
                              / 2);
      v8 = (CParticleEffect *)*((_DWORD *)&this->pNGHVarianceParticle + 3504);
      *(v6 - 1) = v8;
      v6[1] = (CParticleEffect *)((char *)v8 + *((_DWORD *)&this->pNGHVarianceParticle + 3506));
      v6[2] = (CParticleEffect *)((char *)*v6 + *((_DWORD *)&this->pNGHVarianceParticle + 3507));
      result = sub_445FA0(v5);
      ++pDataa;
    }
    ++v4;
    v6 += 4;
    v5 += 38;
  }
  while ( v4 < 5 );
  return result;
}

// 0x00471430
char PlayerMgr::ToggleSlot3(unsigned __int8 pData)
{
  void ( **v3)(CParticleEffect **, _DWORD); // edx
  int v4; // ebx
  CParticleEffect **v5; // ebp
  CParticleEffect **v6; // edi
  char result; // al
  CParticleEffect *v8; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  v3 = (void ( **)(CParticleEffect **, _DWORD))*((_DWORD *)&this->pNGHVarianceParticle + 3408);
  *((_BYTE *)&this->pNGHVarianceParticle + 14035) = pData;
  (*v3)(&this->pNGHVarianceParticle + 3408, pData);
  v4 = 0;
  v5 = &this->pNGHVarianceParticle + 3294;
  pDataa = 0;
  v6 = &(&this->pNGHVarianceParticle)[62] + 13;
  do
  {
    result = *((_BYTE *)&this->pNGHVarianceParticle + v4 + 14032);
    if ( result )
    {
      *v6 = (CParticleEffect *)(pDataa * *((_DWORD *)&this->pNGHVarianceParticle + 3505)
                              + (*((_DWORD *)&this->pNGHVarianceParticle + 3505)
                               - *((_DWORD *)&this->pNGHVarianceParticle + 3507))
                              / 2);
      v8 = (CParticleEffect *)*((_DWORD *)&this->pNGHVarianceParticle + 3504);
      *(v6 - 1) = v8;
      v6[1] = (CParticleEffect *)((char *)v8 + *((_DWORD *)&this->pNGHVarianceParticle + 3506));
      v6[2] = (CParticleEffect *)((char *)*v6 + *((_DWORD *)&this->pNGHVarianceParticle + 3507));
      result = sub_445FA0(v5);
      ++pDataa;
    }
    ++v4;
    v6 += 4;
    v5 += 38;
  }
  while ( v4 < 5 );
  return result;
}

// 0x004714E0
char PlayerMgr::ToggleSlot4(unsigned __int8 pData)
{
  void ( **v3)(CParticleEffect **, _DWORD); // edx
  int v4; // ebx
  CParticleEffect **v5; // ebp
  CParticleEffect **v6; // edi
  char result; // al
  CParticleEffect *v8; // eax
  int pDataa; // [esp+0x14] [ebp+0x4]

  v3 = (void ( **)(CParticleEffect **, _DWORD))*((_DWORD *)&this->pNGHVarianceParticle + 3446);
  *((_BYTE *)&this->pNGHVarianceParticle + 14036) = pData;
  (*v3)(&this->pNGHVarianceParticle + 3446, pData);
  v4 = 0;
  v5 = &this->pNGHVarianceParticle + 3294;
  pDataa = 0;
  v6 = &(&this->pNGHVarianceParticle)[62] + 13;
  do
  {
    result = *((_BYTE *)&this->pNGHVarianceParticle + v4 + 14032);
    if ( result )
    {
      *v6 = (CParticleEffect *)(pDataa * *((_DWORD *)&this->pNGHVarianceParticle + 3505)
                              + (*((_DWORD *)&this->pNGHVarianceParticle + 3505)
                               - *((_DWORD *)&this->pNGHVarianceParticle + 3507))
                              / 2);
      v8 = (CParticleEffect *)*((_DWORD *)&this->pNGHVarianceParticle + 3504);
      *(v6 - 1) = v8;
      v6[1] = (CParticleEffect *)((char *)v8 + *((_DWORD *)&this->pNGHVarianceParticle + 3506));
      v6[2] = (CParticleEffect *)((char *)*v6 + *((_DWORD *)&this->pNGHVarianceParticle + 3507));
      result = sub_445FA0(v5);
      ++pDataa;
    }
    ++v4;
    v6 += 4;
    v5 += 38;
  }
  while ( v4 < 5 );
  return result;
}
