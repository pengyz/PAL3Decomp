#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UICoverFrm.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations

int * ctor_0x431870(int *_this); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];
extern char byte_80AC01;
extern char * off_5EFF78;
extern const char * off_5F2488;
extern RoleSystem stru_C059A0;

// 0x0044C840
int UICoverFrm::SetDefaultValues()
{
  char *v2; // edi
  int result; // eax

  v2 = (char *)&this->m_test + 1932;
  *((_DWORD *)&this->m_test + 481) = 1102409892;
  *((_DWORD *)&this->m_test + 482) = 1140948992;
  *((_DWORD *)&this->m_test + 478) = 518;
  *((_DWORD *)&this->m_test + 480) = 1542;
  sub_445FA0((char *)&this->m_test + 1932);
  result = (**(int ( ***)(char *, int))v2)(v2, 1);
  *((_BYTE *)&this->m_test + 2084) = 1;
  return result;
}

// 0x0044C8A0
char UICoverFrm::UpdateAnimation(float fVal)
{
  double v3; // st7
  char *v4; // edi

  v3 = *((float *)&this->m_test + 482) - fVal * *((float *)&this->m_test + 481);
  *((float *)&this->m_test + 482) = v3;
  *((_DWORD *)&this->m_test + 478) = (__int64)v3;
  *((_DWORD *)&this->m_test + 480) = (__int64)v3 + 1024;
  v4 = (char *)&this->m_test + 1932;
  sub_445FA0((char *)&this->m_test + 1932);
  if ( *((int *)&this->m_test + 480) > 36 )
    return 0;
  (**(void ( ***)(char *, _DWORD))v4)((char *)&this->m_test + 1932, 0);
  *((_BYTE *)&this->m_test + 2084) = 0;
  this->m_LKYX.m_caption[32] = 1;
  return 1;
}

// 0x0044DB50
int UICoverFrm::SetCoverTexture(int nTexPtr)
{
  *((_BYTE *)&this->m_test + 1748) = 1;
  *((_DWORD *)&this->m_test + 438) = nTexPtr;
  return nTexPtr;
}

// 0x0044FF20
int * UICoverFrm::FindActiveSlot()
{
  int v1; // eax
  UIStatic *i; // edx

  v1 = 0;
// [VFTABLE] for ( i = (UIStatic *)((char *)&this->m_test + 2452); i->__vftable; i = (UIStatic *)((char *)i + 2272) )
  {
    if ( ++v1 >= 6 )
      return (int *)((char *)&this->m_test + 2396);
  }
  return (int *)((char *)&this->m_test + 2272 * v1 + 2396);
}

// 0x00527230
int UICoverFrm::UpdateClouds(int nVal, int nVal2)
{
  float m_ratioh; // eax
  int result; // eax
  int v6; // eax
  char *v7; // ebp
  int v8; // [esp-0x10] [ebp-0x14]
  int v9; // [esp-0x10] [ebp-0x14]

  m_ratioh = this->m_smlCloud[0]._cloud.m_ratioh;
  LOBYTE(this->m_smlCloud[2]._cloud.m_pbk2) = 0;
  (*(void ( **)(float *, _DWORD))LODWORD(m_ratioh))(&this->m_smlCloud[0]._cloud.m_ratioh, 0);
  result = *((_DWORD *)this + 3755);
  if ( result > 0 )
  {
    v6 = nVal;
    *((_BYTE *)this + 15018) = 1;
    if ( nVal >= 0 )
    {
      if ( nVal > 1 )
        v6 = 1;
    }
    else
    {
      v6 = 0;
    }
    if ( v6 )
    {
      if ( v6 == 1 )
      {
        v8 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(&this->m_testCloud[1]._cloud.m_bcreateok + 402 * nVal2))
           + 36;
        sprintf(&this->buf[8], "%s%s.pol", "SubGame\\Appraise\\Exhibit\\Data\\", v8);
      }
    }
    else
    {
      v9 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(&this->m_testCloud[1]._cloud.m_childs.m_needscriptdel + 402 * nVal2))
         + 36;
      sprintf(&this->buf[8], "%s%s.pol", "SubGame\\Appraise\\Exhibit\\Data\\", v9);
    }
    v7 = (char *)this + 32 * nVal2;
    ((PalScript *)(v7 + 4692))->LoadModel(&this->buf[8], 0);
    *((_DWORD *)v7 + 1174) = 1;
// [VFTABLE] ((void ( *)(UIWnd **, int))this->m_Star[10].m_pfather->__vftable)(&this->m_Star[10].m_pfather, 1);
    ((UICaption *)&this->m_Star[11].m_benable)->SetEnable((int)(&this->m_testCloud[1]._cloud.m_benable + 402 * nVal2), 1);
    (*(void ( **)(int *, int))this->m_Star[11].m_benable)(&this->m_Star[11].m_benable, 1);
    *((_DWORD *)v7 + 1020) = 0;
    *((_DWORD *)v7 + 1097) = 0;
    result = *((_DWORD *)this + 3755) - 1;
    *((_DWORD *)this + 3755) = result;
  }
  return result;
}

// 0x00527370
int UICoverFrm::ResetStarFrames(int nVal)
{
  void **v3; // edi

// [VFTABLE] v3 = &this->__vftable + 8 * nVal;
  v3[1174] = 0;
// [VFTABLE] ((void ( *)(UIWnd **, _DWORD))this->m_Star[10].m_pfather->__vftable)(&this->m_Star[10].m_pfather, 0);
  (*(void ( **)(int *, _DWORD))this->m_Star[11].m_benable)(&this->m_Star[11].m_benable, 0);
  v3[1020] = (void *)1;
  v3[1097] = (void *)1;
  *((_BYTE *)this + 15018) = 0;
  return 1;
}

// 0x0052BA10
int UICoverFrm::ctor()
{
  *(_DWORD *)this->buf = 800;
  *(_DWORD *)&this->buf[4] = 600;
  ctor_0x431870((int *)&this->m_background.m_wndcolor);
  this->m_Star[5].m_wndcolor.Color = 418;
  this->m_Star[5].m_id = (void *)418;
  this->m_Star[5].m_rect.left = 48;
  this->m_Star[5].m_rect.top = 192;
  this->m_Star[5].m_rect.right = 78;
  this->m_Star[5].m_rect.bottom = 78;
  LOBYTE(this->m_Star[5].m_pfather) = 0;
  BYTE1(this->m_Star[5].m_pfather) = 0;
  HIBYTE(this->m_Star[5].m_pfather) = 0;
  sub_4422E0(&this->m_Star[5].m_childs);
  ((CCBResultWindow *)&this->m_Star[6].m_bfocus)->ctor();
  sub_4422E0(&this->m_Meteor.m_fontcolor);
  sub_4422E0(&this->m_Meteor.m_TailPt[8]);
  this->m_QCYM.m_offsety = 0.0;
  this->m_QCYM.m_bBigFont = 1;
  this->m_QCYM.m_texarray.m_ptex[0] = 0;
  this->m_QCYM.m_texarray.m_ptex[1] = (gbTexture *)1092616192;
  LOBYTE(this->m_QCYM.m_texarray.m_ptex[2]) = 0;
  BYTE2(this->m_QCYM.m_texarray.m_ptex[3]) = 0;
  ((ARC_PlayerAtt *)&this->m_QCYM.m_texarray.m_ptex[4])->Refresh();
  ((ARC_PlayerAtt *)&this->m_YXXX.m_caption[112])->Refresh();
  *(&this->m_Star[12].m_nFrame + 3) = -1;
  *(&this->m_Star[12].m_nFrame + 4) = -1;
  *(&this->m_Star[12].m_nFrame + 5) = -1;
// [VFTABLE] this->m_Meteor.__vftable = (vtbl_0056AE2C *)-1;
  *(gbTexture **)((char *)&this->m_QCYM.m_texarray.m_ptex[2] + 1) = 0;
  BYTE1(this->m_QCYM.m_texarray.m_ptex[3]) = 0;
  *((_BYTE *)&this->m_test + 805) = 1;
  return (int)this;
}

// 0x0052BD50
void UICoverFrm::ctor_BD50()
{
  ((UIRoleDialog *)&this->m_YXXX.m_caption[112])->_UIRoleDialog();
  ((UIRoleDialog *)&this->m_QCYM.m_texarray.m_ptex[4])->_UIRoleDialog();
  ((UIFrameWnd *)&this->m_Meteor.m_TailPt[8])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Meteor.m_fontcolor)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Star[6].m_bfocus)->ctor();
  ((UIFrameWnd *)&this->m_Star[5].m_childs)->UIFrameWnd::_UIFrameWnd();
  ((PalScript *)&this->m_background.m_wndcolor)->Cleanup();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0052C450
void UICoverFrm::Render()
{
  ScreenEffect *Instance; // eax
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  if ( !*((_DWORD *)&this->m_test + 200) )
  {
    Instance = ((ScreenEffectMgr *)this)->GetInstance();
    *((_DWORD *)&this->m_test + 200) = ((ScreenEffectMgr *)Instance)->ProcessEffect();
  }
  ((CCBControlWindow *)this)->Render(v3);
}

// 0x0052C480
double UICoverFrm::UpdateStarAnimation(int edi0, double result, int result_4, int nVal)
{
  int v5; // edi
  double v6; // st7
  char *m_pData; // eax
  CScreenMode *Instance; // eax
  double v10; // st7
  double v11; // st7
  double v12; // st7
  CCBStageRole *v13; // eax
  _BYTE *p_m_bChangedMat; // eax
  gbTexture **p_pDebugTex; // edi
  CScreenMode *v16; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v18; // esi
  CScreenMode *v19; // eax
  CScreenMode *v20; // eax
  void ( ***v21)(_DWORD, int); // eax
  char *v22; // [esp-0x10] [ebp-0x28]
  char *v23; // [esp-0xC] [ebp-0x24]
  float v24; // [esp+0x10] [ebp-0x8]
  int *v25; // [esp+0x10] [ebp-0x8]
  float v26; // [esp+0x14] [ebp-0x4]
  int v27; // [esp+0x14] [ebp-0x4]

  v6 = *(float *)&edi0 * 36.599998;
  v24 = v6;
  if ( !*((_BYTE *)&this->m_test + 796) && ((UIParabolaCtrl *)&this->m_YXXX.m_caption[112])->GetState() == 2 )
  {
    m_pData = this->m_Star[5].m_childs.m_pData;
    LOBYTE(this->m_Star[5].m_pfather) = 1;
    (*(void ( **)(PtrArray *, int))m_pData)(&this->m_Star[5].m_childs, 1);
    (*(void ( **)(int *, int))this->m_Star[6].m_bfocus)(&this->m_Star[6].m_bfocus, 1);
    this->m_Star[7].m_IsNextTimeRand = 2;
    v6 = *(float *)this->m_QCYM.m_texarray.m_ptex;
    if ( v6 > 0.0 )
    {
      *((float *)&this->m_Star[7].m_nFrame + 1) = *(float *)this->m_QCYM.m_texarray.m_ptex;
      *((float *)&this->m_Star[7].m_nFrame + 5) = v6;
      *((_BYTE *)&this->m_Star[7].m_nFrame + 12) = 0;
    }
    else
    {
      *(&this->m_Star[7].m_nFrame + 1) = 0;
      *((_BYTE *)&this->m_Star[7].m_nFrame + 12) = 1;
    }
    *(&this->m_Star[7].m_nFrame + 2) = 1;
    v22 = off_5EFF78;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v22, 0);
    *((_BYTE *)&this->m_test + 796) = 1;
  }
  if ( !LOBYTE(this->m_Star[5].m_pfather) )
    goto LABEL_52;
  v10 = v24 * 0.079999998;
  if ( this->m_QCYM.m_bBigFont )
  {
    v11 = v10 + *(float *)this->m_QCYM.m_texarray.m_ptex;
    *(float *)this->m_QCYM.m_texarray.m_ptex = v11;
    if ( v11 >= *(float *)&this->m_QCYM.m_texarray.m_ptex[1] )
      this->m_QCYM.m_texarray.m_ptex[0] = this->m_QCYM.m_texarray.m_ptex[1];
  }
  else
  {
    v12 = *(float *)this->m_QCYM.m_texarray.m_ptex - v10;
    *(float *)this->m_QCYM.m_texarray.m_ptex = v12;
    if ( v12 <= 0.0 )
      this->m_QCYM.m_texarray.m_ptex[0] = 0;
  }
  v6 = *(float *)this->m_QCYM.m_texarray.m_ptex;
  if ( v6 > 0.0 )
  {
    *((float *)&this->m_Star[7].m_nFrame + 1) = *(float *)this->m_QCYM.m_texarray.m_ptex;
    *((float *)&this->m_Star[7].m_nFrame + 5) = v6;
    *((_BYTE *)&this->m_Star[7].m_nFrame + 12) = 0;
  }
  else
  {
    *(&this->m_Star[7].m_nFrame + 1) = 0;
    *((_BYTE *)&this->m_Star[7].m_nFrame + 12) = 1;
  }
  if ( *((_BYTE *)&this->m_Star[7].m_nFrame + 12) )
  {
    v6 = 360.0 - *(float *)&this->m_Star[7].m_nNextTime;
    v26 = v6;
    if ( v6 > 180.0 )
    {
      v6 = v26;
      if ( v26 > 270.0 )
      {
        v6 = v26;
        if ( v26 > 318.60001 )
        {
          v6 = v26;
          if ( v26 > 354.20001 )
          {
            v6 = v26;
            if ( v26 <= 359.0 )
              this->m_QCYM.m_offsety = 100.0;
          }
          else
          {
            this->m_QCYM.m_offsety = 75.0;
          }
        }
        else
        {
          this->m_QCYM.m_offsety = 50.0;
        }
      }
      else
      {
        this->m_QCYM.m_offsety = 30.0;
      }
    }
    else
    {
      this->m_QCYM.m_offsety = 0.0;
    }
    LOBYTE(this->m_Star[5].m_pfather) = 0;
    LOBYTE(this->m_QCYM.m_texarray.m_ptex[2]) = 1;
    BYTE2(this->m_QCYM.m_texarray.m_ptex[3]) = 1;
  }
  else
  {
    LOBYTE(this->m_Star[5].m_pfather) = 1;
    LOBYTE(this->m_QCYM.m_texarray.m_ptex[2]) = 0;
  }

  if ( !LOBYTE(this->m_Star[5].m_pfather) )
  {
LABEL_52:
    if ( BYTE2(this->m_QCYM.m_texarray.m_ptex[3]) )
    {
      v23 = off_5EFF78;
      v13 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v13)->PlaySound(v23, v5);

      ((CScreenMode *)this)->InitPlayerData();
      BYTE2(this->m_QCYM.m_texarray.m_ptex[3]) = 0;
    }
  }
  if ( !((UIParabolaCtrl *)&this->m_QCYM.m_texarray.m_ptex[4])->GetState() )
    ((UISceneFace *)this)->UpdateFacePosition();
  if ( BYTE1(this->m_Star[5].m_pfather) )
  {
    p_m_bChangedMat = &Buffer.m_partyActor.m_bChangedMat;
    v27 = 0;
    v25 = (int *)&Buffer.m_partyActor.m_bChangedMat;
    p_pDebugTex = &this->m_cloud[4]._cloud.pDebugTex;
    do
    {
      if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v27) )
      {
        sprintf(&this->buf[8], "%d/%d", (int)*((float *)p_pDebugTex - 22), *((_DWORD *)p_m_bChangedMat - 2));
        ((UICaption *)p_pDebugTex)->SetEnable((int)&this->buf[8], 0);
        v6 = *((float *)p_pDebugTex + 115);
        sprintf(&this->buf[8], "%d/%d", (int)v6, *v25);
        ((UICaption *)(p_pDebugTex + 137))->SetEnable((int)&this->buf[8], 0);
        if ( BYTE2(this->m_Star[5].m_pfather) )
        {
          if ( *((_BYTE *)p_pDebugTex - 84) )
            BYTE2(this->m_Star[5].m_pfather) = 0;
        }
      }
      p_pDebugTex += 388;
      ++v27;
      p_m_bChangedMat = v25 + 352;
      v25 += 352;
    }
    while ( (int)v25 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[210] );
  }
  if ( HIBYTE(this->m_Star[5].m_pfather) )
  {
    if ( (g_dwGameFlags & 4) != 0 )
    {
      v16 = CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)((CScreenMode *)v16)->GetAudioManager();
      v18 = AudioManager;
      if ( AudioManager )
      {
        ((gbAudioManager *)AudioManager)->StopSoundStream(1);
        ((gbAudioManager *)v18)->StopSoundStream(2);
      }
      if ( CScreenMode::GetInstance()->m_bRenderAlt )
      {
        v19 = CScreenMode::GetInstance();
        ((CScreenMode *)v19)->AudioFadeOut();
      }
      else
      {
        v20 = CScreenMode::GetInstance();
        ((CScreenMode *)v20)->AudioStopAll();
      }
    }
    v21 = (void ( ***)(_DWORD, int))((CGameData *)&g_gamefrm)->SetMode(0);
    (**v21)(v21, 1);
    ((CGameData *)&g_gamefrm)->Load(0);
    g_nSceneState = 2;
  }
  else
  {
    ((UIListBox *)this)->Update(edi0, SLODWORD(result));
  }
  return v6;
}

// 0x0052CA10
int UICoverFrm::OnMessage(int nVal, char *pszBuf, int nVal2)
{
  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        *((_DWORD *)&this->m_test + 200) = 0;
        ((UIBigMap *)this)->DestroyFrames();
      }
      break;
    case 1009:
      if ( pszBuf == &byte_80AC01 )
      {
        if ( BYTE1(this->m_Star[5].m_pfather) )
        {
          if ( !BYTE2(this->m_Star[5].m_pfather) )
            HIBYTE(this->m_Star[5].m_pfather) = 1;
        }
        if ( !LOBYTE(this->m_QCYM.m_texarray.m_ptex[2]) )
        {
          this->m_QCYM.m_bBigFont = 0;
          LOBYTE(this->m_Star[5].m_pfather) = 1;
          return 1;
        }
      }
      else if ( pszBuf - &byte_80AC01 == 6 )
      {
        (*(void ( **)(gbColorQuad *, _DWORD))this->m_Meteor.m_fontcolor.Color)(&this->m_Meteor.m_fontcolor, 0);
        (*(void ( **)(tagPOINT *, _DWORD))this->m_Meteor.m_TailPt[8].x)(&this->m_Meteor.m_TailPt[8], 0);
        ((UIRoleSelect *)&this->m_YXXX.m_caption[112])->SetByte(1);
        return 1;
      }
      break;
    case 1010:
      break;
    default:
      return ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nVal2);
  }
  return 1;
}

// 0x0052D5B0
int UICoverFrm::AnimateElements()
{
  DWORD Time; // eax
  int i; // ebx
  int j; // ebp
  int k; // edi
  int m; // edx
  UIPar_Star *v7; // esi
  int v8; // edi
  int result; // eax

  Time = timeGetTime();
  CRT_set_new_handler(Time);
  for ( i = rand() % 5; !*((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + i); i = rand() % 5 )
    ;
  for ( j = rand() % 5; !*((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + j); j = rand() % 5 )
    ;
  for ( k = rand() % 5; !*((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + k); k = rand() % 5 )
    ;
  for ( m = rand() % 5; !*((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + m); m = rand() % 5 )
    ;
// [VFTABLE] this->m_Meteor.__vftable = (vtbl_0056AE2C *)m;
  *(&this->m_Star[12].m_nFrame + 3) = i;
  *(&this->m_Star[12].m_nFrame + 4) = j;
  *(&this->m_Star[12].m_nFrame + 5) = k;
  ((UIStatic *)&this->m_Star[8])->CreateFromTemplate();
  ((UIStatic *)&this->m_Star[9].m_rect.bottom)->CreateFromTemplate();
  ((UIStatic *)&this->m_Star[10].m_bvisible)->CreateFromTemplate();
  ((UIStatic *)&this->m_Star[11].m_IsHighPoint)->CreateFromTemplate();
  v7 = &this->m_Star[8];
  v8 = 4;
  do
  {
// [VFTABLE] result = ((int ( *)(UIPar_Star *, int))v7->__vftable->ShowWindow)(v7, 1);
    v7 = (UIPar_Star *)((char *)v7 + 152);
    --v8;
  }
  while ( v8 );
  return result;
}

// 0x0052D7C0
char UICoverFrm::LoadFromFile(char *pszFileName)
{
  FILE *v4; // ebp
  void *vftable; // esi
  char *v6; // eax
  _DWORD *v7; // ecx
  void *v8; // edx
  unsigned int Color; // edx
  int v10; // ecx
  float *v11; // eax
  unsigned int v12; // eax
  double v13; // st7
  float *v14; // edx
  gbVec3D *v15; // ecx
  float v16; // esi
  double v17; // st7
  double y; // st6
  float v19; // edx
  double v20; // st6
  float v21; // edx
  int v22; // [esp+0x10] [ebp-0x234] BYREF
  float v23; // [esp+0x14] [ebp-0x230]
  float v24; // [esp+0x18] [ebp-0x22C]
  float v25; // [esp+0x1C] [ebp-0x228]
  float v26; // [esp+0x20] [ebp-0x224]
  float v27; // [esp+0x24] [ebp-0x220]
  float v28; // [esp+0x28] [ebp-0x21C]
  float v29; // [esp+0x2C] [ebp-0x218]
  float v30; // [esp+0x30] [ebp-0x214]
  float v31; // [esp+0x34] [ebp-0x210]
  float v32; // [esp+0x3C] [ebp-0x208]
  float v33; // [esp+0x40] [ebp-0x204]
  char Buffer[256]; // [esp+0x44] [ebp-0x200] BYREF
  char v35[256]; // [esp+0x144] [ebp-0x100] BYREF

  if ( !pszFileName )
    return 0;
  v4 = fopen(pszFileName, aR);
  if ( (v4->_flag & 0x10) != 0 )
    goto LABEL_12;
  while ( 1 )
  {
    fscanf(v4, "%s %s", Buffer, v35);
    if ( strcmp(Buffer, "*NODE_NAME") )
    {
      fgets(Buffer, 150, v4);
      goto LABEL_11;
    }
    if ( !strcmp(v35, off_5F2488) )
      break;
LABEL_11:
    if ( (v4->_flag & 0x10) != 0 )
      goto LABEL_12;
  }
  if ( (v4->_flag & 0x10) == 0 )
  {
    while ( 1 )
    {
      fscanf(v4, "%s %ud", Buffer, this);
      if ( !strcmp(Buffer, "*MESH_NUMVERTEX") )
        break;
      fgets(Buffer, 150, v4);
      if ( (v4->_flag & 0x10) != 0 )
        goto LABEL_11;
    }
  }
LABEL_12:
// [VFTABLE] if ( !this->__vftable )
    return 0;
  fseek(v4, 0, 0);
// [VFTABLE] vftable = this->__vftable;
// [VFTABLE] v6 = (char *)operator new(32 * (int)this->__vftable);
  if ( v6 )
  {
    if ( (int)&vftable[-1].OnMessage + 3 >= 0 )
    {
      v7 = v6 + 28;
      v8 = vftable;
      do
      {
        *(v7 - 7) = 0;
        *(v7 - 6) = 0;
        *(v7 - 5) = 0;
        *(v7 - 4) = 0;
        *(v7 - 3) = 0;
        *(v7 - 2) = 0;
        *(v7 - 1) = 0;
        *v7 = 0;
        v7 += 8;
        v8 = (void *)((char *)v8 - 1);
      }
      while ( v8 );
    }
  }
  else
  {
    v6 = 0;
  }
  this->m_fontcolor.Color = (unsigned int)v6;
  if ( !v6 )
    return 0;
  v22 = 0;
  while ( (v4->_flag & 0x10) == 0 )
  {
    fscanf(v4, "%s %s", Buffer, v35);
    if ( !strcmp(Buffer, "*NODE_NAME") )
    {
      if ( !strcmp(v35, off_5F2488) )
      {
        if ( (v4->_flag & 0x10) != 0 )
          break;
        do
        {
          fscanf(v4, byte_5967B0, Buffer);
          if ( !strcmp(Buffer, "*MESH_VERTEX") )
          {
            fscanf(v4, &dir[20], &v22);
            fscanf(
              v4,
              "%f %f %f",
              32 * v22 + this->m_fontcolor.Color,
              32 * v22 + this->m_fontcolor.Color + 8,
              32 * v22 + this->m_fontcolor.Color + 4);
            *(float *)(32 * v22 + this->m_fontcolor.Color + 8) = -*(float *)(32 * v22 + this->m_fontcolor.Color + 8);
            if ( v22 <= 0 )
            {
              *(_DWORD *)(this->m_fontcolor.Color + 12) = 0;
              *(_DWORD *)(this->m_fontcolor.Color + 16) = 0;
            }
            else
            {
              Color = this->m_fontcolor.Color;
              v10 = 32 * (v22 - 1);
              v11 = (float *)(Color + 32 * v22);
              v26 = *(float *)(v10 + Color);
              v27 = *(float *)(v10 + Color + 4);
              v28 = *(float *)(v10 + Color + 8);
              v29 = *v11;
              v30 = v11[1];
              v31 = v11[2];
              v11[4] = sqrt((v29 - v26) * (v29 - v26) + (v30 - v27) * (v30 - v27) + (v31 - v28) * (v31 - v28));
              *(float *)(this->m_fontcolor.Color + 32 * v22 + 12) = *(float *)(v10 + this->m_fontcolor.Color + 12)
                                                                  + *(float *)(32 * v22 + this->m_fontcolor.Color + 16);
              v12 = this->m_fontcolor.Color;
              v13 = *(float *)(v10 + v12 + 20);
              v14 = (float *)(v12 + 32 * v22);
              v15 = (gbVec3D *)(v10 + v12 + 20);
              v23 = *v14;
              v16 = v14[1];
              v17 = v13 - v23;
              y = v15->y;
              v19 = v14[2];
              v24 = v16;
              v25 = v19;
              v32 = y - v16;
              v20 = v15->z - v19;
              v15->y = v32;
              v33 = v20;
              v21 = v33;
              v15->x = v17;
              v15->z = v21;
              ((gbVec3D *)v15)->Normalize();
            }
          }
          else
          {
            fgets(Buffer, 150, v4);
          }
        }
        while ( (v4->_flag & 0x10) == 0 );
      }
    }
    else
    {
      fgets(Buffer, 150, v4);
    }
  }
// [VFTABLE] this->m_wndcolor.Color = *(_DWORD *)(32 * (int)this->__vftable + this->m_fontcolor.Color - 20);
  fclose(v4);
  return 1;
}
