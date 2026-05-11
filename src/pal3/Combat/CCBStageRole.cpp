#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageRole.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/C3DSpark.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/CCBSystem.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/CEffSParticle.h"
#include "pal3/gen/CEffect.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/SceneObj.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_40EE00(...);
int sub_4DFC40(...);
int sub_4F6A20(...);
int sub_4F6A80(...);
int sub_4F6AB0(...);
int sub_4F6BB0(...);
int sub_509230(...);
int sub_50B430(...);
int sub_50B4C0(...);
int sub_50B4F0(...);
int sub_53DF80(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Co_8[];
extern char aFlydown[];
extern char aFlyup[];
extern char aNghOpenObjD[];
extern char aOver[];
extern char aPause[];
extern char aStore[];
extern char aTagWeapon1[];
extern char aTagWeapon2[];
extern char aWe011[];
extern char aWe011b[];
extern char aWe012[];
extern char aWe013[];
extern char aWe014[];
extern char aWork[];
extern char aWork1[];
extern unsigned char byte_17AB714;
extern unsigned char byte_17AB734;
extern unsigned char byte_17AB764;
extern unsigned char byte_17AB794;
extern unsigned char byte_17AB7D4;
extern unsigned char byte_17AB804;
extern unsigned char byte_17AB818;
extern unsigned char byte_17AB874;
extern unsigned char byte_17AB884;
extern unsigned char byte_17AB8B4;
extern unsigned char byte_17AB8B8;
extern unsigned char byte_17AB9C4;
extern unsigned char byte_1895558;
extern int dword_17AB6E8;
extern int dword_17AB6EC;
extern int dword_17AB6F0;
extern int dword_17AB6F8;
extern int dword_17AB6FC;
extern int dword_17AB700;
extern int dword_17AB708;
extern int dword_17AB70C;
extern int dword_17AB710;
extern int dword_17AB718;
extern int dword_17AB71C;
extern int dword_17AB720;
extern int dword_17AB728;
extern int dword_17AB72C;
extern int dword_17AB730;
extern int dword_17AB738;
extern int dword_17AB73C;
extern int dword_17AB740;
extern int dword_17AB748;
extern int dword_17AB74C;
extern int dword_17AB750;
extern int dword_17AB758;
extern int dword_17AB75C;
extern int dword_17AB760;
extern int dword_17AB768;
extern int dword_17AB76C;
extern int dword_17AB770;
extern int dword_17AB778;
extern int dword_17AB77C;
extern int dword_17AB780;
extern int dword_17AB788;
extern int dword_17AB78C;
extern int dword_17AB790;
extern int dword_17AB7A8;
extern int dword_17AB7AC;
extern int dword_17AB7B0;
extern int dword_17AB7B8;
extern int dword_17AB7BC;
extern int dword_17AB7C0;
extern int dword_17AB7C8;
extern int dword_17AB7CC;
extern int dword_17AB7D0;
extern int dword_17AB7D8;
extern int dword_17AB7DC;
extern int dword_17AB7E0;
extern int dword_17AB7E8;
extern int dword_17AB7EC;
extern int dword_17AB7F0;
extern int dword_17AB7F8;
extern int dword_17AB7FC;
extern int dword_17AB800;
extern int dword_17AB878;
extern int dword_17AB87C;
extern int dword_17AB880;
extern int dword_17AB888;
extern int dword_17AB88C;
extern int dword_17AB890;
extern int dword_17AB898;
extern int dword_17AB89C;
extern int dword_17AB8A0;
extern int dword_17AB8A8;
extern int dword_17AB8AC;
extern int dword_17AB8B0;
extern int dword_17AB9B8;
extern int dword_17AB9BC;
extern int dword_17AB9C0;
extern int dword_17AB9C8;
extern int dword_17AB9CC;
extern int dword_17AB9D8;
extern int dword_17AB9DC;
extern int dword_17ABC7C;
extern int dword_17ABC80;
extern int dword_17ABC84;
extern int dword_17ABC88;
extern int dword_17ABC8C;
extern int dword_17ABC90;
extern int dword_17ABC94;
extern int dword_17ABC98;
extern int dword_17ABC9C;
extern int dword_17ABCA0;
extern int dword_17ABCA4;
extern int dword_17ABCA8;
extern int dword_17ABCAC;
extern int dword_17ABCB0;
extern int dword_17ABCB4;
extern int dword_17ABCB8;
extern int dword_56FE98;
extern int dword_58618C;
extern int dword_586190;
extern int dword_586198;
extern int dword_58619C;
extern float flt_17ABCCC;
extern float flt_17ABCD0;
extern float flt_17ABCD4;
extern float flt_17ABCD8;
extern int nullsub_1;
extern int nullsub_32;
extern int nullsub_33;
extern int nullsub_34;
extern int nullsub_35;
extern int nullsub_36;
extern int nullsub_37;
extern int nullsub_38;
extern int nullsub_39;
extern int nullsub_40;
extern int nullsub_41;
extern int nullsub_42;
extern int nullsub_43;
extern int nullsub_44;
extern int nullsub_45;
extern int nullsub_46;
extern int nullsub_47;
extern int nullsub_48;
extern int nullsub_49;
extern int nullsub_50;
extern int nullsub_51;
extern int nullsub_52;
extern int nullsub_53;
extern int nullsub_54;
extern int stru_17AB828;
extern int unk_5888C4;
extern int unk_5888C8;
extern int unk_5888D0;

// 0x004ED040
char CCBStageRole::IsActive(int index)
{
  return *((_BYTE *)&this->m_OBBox.ylen + 892 * index + 3);
}

// 0x00508930
CCBStageRole::~CCBStageRole()
{
  int v5; // edx
  char *v6; // esi
  int v7; // ecx
  int v8; // eax
  int v9; // edi
  int v10; // edi
  bool v11; // al
  bool v12; // cc
  int v13; // edx
  double v14; // st7
  char v16; // dl
  float *v17; // eax
  float v18; // ecx
  char v19; // cl
  int v20; // eax
  float *v21; // eax
  float v22; // edi
  char v23; // dl
  float *v24; // eax
  float v25; // ecx
  char v26; // cl
  int v27; // eax
  float *v28; // eax
  float v29; // edi
  float v30; // [esp+10h] [ebp-3Ch]
  int v31; // [esp+14h] [ebp-38h]
  int a5; // [esp+18h] [ebp-34h]
  int v33; // [esp+20h] [ebp-2Ch]
  int v34; // [esp+24h] [ebp-28h]
  float v35; // [esp+28h] [ebp-24h]
  int v36; // [esp+2Ch] [ebp-20h]
  int v37; // [esp+30h] [ebp-1Ch]
  float v38; // [esp+34h] [ebp-18h]
  int v39; // [esp+38h] [ebp-14h]
  int v40; // [esp+3Ch] [ebp-10h]
  float v41; // [esp+40h] [ebp-Ch]
  int v42; // [esp+44h] [ebp-8h]
  int v43; // [esp+48h] [ebp-4h]

  v5 = *(_DWORD *)&this->m_Task[18].eMode[60 * a2];
  v6 = (char *)this + 60 * a2;
  if ( v5 != a4[1] )
    v5 = a4[1];
  v7 = *(_DWORD *)this->m_sLastRole;
  v30 = 0.0;
  v31 = 0;
  a5 = 0;
  v35 = *(float *)(*(_DWORD *)(v7 + 20) + 900);
  v36 = *(_DWORD *)(*(_DWORD *)(v7 + 20) + 904);
  v37 = *(_DWORD *)(*(_DWORD *)(v7 + 20) + 908);
  v38 = *(float *)(*(_DWORD *)(v7 + 64) + 6596);
  v39 = *(_DWORD *)(*(_DWORD *)(v7 + 64) + 6600);
  v40 = *(_DWORD *)(*(_DWORD *)(v7 + 64) + 6604);
  v8 = a4[2];
  if ( (unsigned int)v8 > 4 )
  {
    v41 = *(float *)(*(_DWORD *)(v7 + 64) + 6596);
    v42 = *(_DWORD *)(*(_DWORD *)(v7 + 64) + 6600);
    v9 = *(_DWORD *)(*(_DWORD *)(v7 + 64) + 6604);
  }
  else
  {
    v41 = *(float *)(*(_DWORD *)(v7 + 20) + 900);
    v42 = *(_DWORD *)(*(_DWORD *)(v7 + 20) + 904);
    v9 = *(_DWORD *)(*(_DWORD *)(v7 + 20) + 908);
  }
  v43 = v9;
  v10 = a4[3];
  if ( v10 == -1 )
  {
    switch ( *a4 )
    {
      case 0x104:
      case 0x10D:
        v11 = sub_4F6A80(v5);
        goto LABEL_12;
      case 0x105:
        v11 = sub_4F6A20(v5);
        goto LABEL_12;
      case 0x106:
        v11 = sub_4F6BB0(v5);
        goto LABEL_12;
      case 0x10E:
        v11 = sub_4F6AB0(v5);
LABEL_12:
        if ( v11 )
          goto LABEL_13;
        v8 = a4[2];
        if ( v8 < 0 )
          goto LABEL_21;
        v12 = v8 < 5;
        break;
      default:
LABEL_13:
        v8 = a4[2];
        if ( (unsigned int)v8 > 4 )
          goto LABEL_20;
        goto LABEL_21;
    }
  }
  else
  {
    if ( v10 < 0 )
      goto LABEL_21;
    v12 = v10 < 5;
  }
  if ( v12 )
  {
LABEL_20:
    v13 = v37;
    v14 = v35;
    v33 = v36;
    goto LABEL_22;
  }
LABEL_21:
  v13 = v40;
  v14 = v38;
  v33 = v39;
LABEL_22:
  v34 = v13;
  if ( a3 == 1 )
  {
    if ( *((_DWORD *)v6 + 612) == -1 )
    {
  0;
    }
    else
    {
      if ( v6[2452] )
      {
        v30 = v41;
        v31 = v42;
        a5 = v43;
      }
      if ( v6[2453] )
      {
        v30 = v14;
        v31 = v33;
        a5 = v13;
      }
      v16 = v6[2454];
      if ( v16 )
      {
        v17 = (float *)*(float **)(*(_DWORD *)this->m_sLastRole + 4 * v8 + 24);
        v18 = v17[1649];
        v17 += 1649;
        v30 = v18;
        v31 = *((_DWORD *)v17 + 1);
        a5 = *((_DWORD *)v17 + 2);
      }
      v19 = v6[2455];
      if ( v19 )
      {
        v20 = a4[3];
        if ( v20 == -1 )
        {
          v30 = v14;
          v31 = v33;
          a5 = v34;
        }
        else
        {
          v21 = (float *)*(float **)(*(_DWORD *)this->m_sLastRole + 4 * v20 + 24);
          v22 = v21[1649];
          v21 += 1649;
          v30 = v22;
          v31 = *((_DWORD *)v21 + 1);
          a5 = *((_DWORD *)v21 + 2);
        }
      }
      if ( !v6[2452] && !v6[2453] && !v16 && !v19 )
      {
        v30 = *((float *)v6 + 614);
        v31 = *((_DWORD *)v6 + 615);
        a5 = *((_DWORD *)v6 + 616);
      }
      if ( *a4 == 269 )
        ((CEffect *)*(CEffect **)(**(_DWORD **)this->m_sLastRole + 48))->Render(*((_DWORD *)v6 + 612));
      if ( *a4 == 270 )
        ((CEffect *)*(CEffect **)(**(_DWORD **)this->m_sLastRole + 44))->Render(*((_DWORD *)v6 + 612));
      if ( *a4 == 269 )
        return ((CEffMgr *)*(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 48))->Init(*((_DWORD *)v6 + 612), SLODWORD(v30), v31, a5, 0);
      else
        return ((CEffMgr *)*(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 44))->Init(*((_DWORD *)v6 + 612), SLODWORD(v30), v31, a5, 0);
    }
  }
  else if ( *((_DWORD *)v6 + 619) == -1 )
  {
  0;
  }
  else
  {
    if ( v6[2480] )
    {
      v30 = v41;
      v31 = v42;
      a5 = v43;
    }
    if ( v6[2481] )
    {
      v30 = v14;
      v31 = v33;
      a5 = v13;
    }
    v23 = v6[2482];
    if ( v23 )
    {
      v24 = (float *)*(float **)(*(_DWORD *)this->m_sLastRole + 4 * v8 + 24);
      v25 = v24[1649];
      v24 += 1649;
      v30 = v25;
      v31 = *((_DWORD *)v24 + 1);
      a5 = *((_DWORD *)v24 + 2);
    }
    v26 = v6[2483];
    if ( v26 )
    {
      v27 = a4[3];
      if ( v27 == -1 )
      {
        v30 = v14;
        v31 = v33;
        a5 = v34;
      }
      else
      {
        v28 = (float *)*(float **)(*(_DWORD *)this->m_sLastRole + 4 * v27 + 24);
        v29 = v28[1649];
        v28 += 1649;
        v30 = v29;
        v31 = *((_DWORD *)v28 + 1);
        a5 = *((_DWORD *)v28 + 2);
      }
    }
    if ( !v6[2480] && !v6[2481] && !v23 && !v26 )
    {
      v30 = *((float *)v6 + 621);
      v31 = *((_DWORD *)v6 + 622);
      a5 = *((_DWORD *)v6 + 623);
    }
    if ( *a4 == 269 )
      ((CEffect *)*(CEffect **)(**(_DWORD **)this->m_sLastRole + 48))->Render(*((_DWORD *)v6 + 619));
    if ( *a4 == 270 )
      ((CEffect *)*(CEffect **)(**(_DWORD **)this->m_sLastRole + 44))->Render(*((_DWORD *)v6 + 619));
    if ( *a4 == 269 )
      return ((CEffMgr *)*(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 48))->Init(*((_DWORD *)v6 + 619), SLODWORD(v30), v31, a5, 0);
    else
      return ((CEffMgr *)*(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 44))->Init(*((_DWORD *)v6 + 619), SLODWORD(v30), v31, a5, 0);
  }
}

// 0x005090F0
int CCBStageRole::Proceed()
{
  dword_17ABC7C = 519;
  dword_17ABC80 = 519;
  dword_17ABC84 = 519;
  dword_17ABC88 = 519;
  return 519;
}

// 0x00509130
// attributes: thunk
int CCBStageRole::SetAlive()
{
  return CCBStageRole::SetMaxBlend();
}

// 0x00509140
int CCBStageRole::SetMaxBlend()
{
  dword_17ABC8C = 128;
  dword_17ABC90 = 323;
  dword_17ABC94 = 519;
  dword_17ABC98 = 716;
  return 716;
}

// 0x00509180
// attributes: thunk
int CCBStageRole::SetVisible()
{
  return CCBStageRole::SetPause();
}

// 0x00509190
int CCBStageRole::SetPause()
{
  dword_17ABC9C = 545;
  dword_17ABCA0 = 545;
  dword_17ABCA4 = 545;
  dword_17ABCA8 = 545;
  return 545;
}

// 0x005091D0
// attributes: thunk
int CCBStageRole::OnChangeAction()
{
  return CCBStageRole::CheckAction();
}

// 0x005091E0
int CCBStageRole::CheckAction()
{
  dword_17ABCAC = 121;
  dword_17ABCB0 = 316;
  dword_17ABCB4 = 512;
  dword_17ABCB8 = 709;
  return 709;
}

// 0x00509220
// attributes: thunk
int CCBStageRole::OnPlayAction()
{
  return sub_509230();
}

// 0x00509270
// attributes: thunk
int CCBStageRole::IsUnderMouse()
{
  return CCBStageRole::IsCollideRay();
}

// 0x00509280
int CCBStageRole::IsCollideRay()
{
  dword_17AB9DC = 12;
  return 12;
}

// 0x00509290
// attributes: thunk
int CCBStageRole::GetRoleRadius()
{
  return CCBStageRole::GetRoleHeight();
}

// 0x005092A0
int CCBStageRole::GetRoleHeight()
{
  dword_17AB9D8 = 508;
  return 508;
}

// 0x005092B0
char * CCBStageRole::GetOBBox(int a2)
{
  gbOBBox *p_m_OBBox; // ebp
  gbOBBox *v4; // edi
  CCBRoleState *v5; // ecx
  int v7; // [esp+10h] [ebp-4h]

  ((gbMatrix4 *)&this->m_dwID)->gbMatrix4();
  p_m_OBBox = (gbOBBox *)&this->m_OBBox;
  v7 = 64;
  do
  {
    ((gbVec3D *)&p_m_OBBox[-1].xlen)->gbVec3D(0.0, 0.0, 0.0);
    v4 = p_m_OBBox;
    p_m_OBBox = (gbOBBox *)((char *)p_m_OBBox + 96);
    memset(v4, 0, 0x2Cu);
    --v7;
  }
  while ( v7 );
  *(_DWORD *)this->m_Task[61].eMode = 0;
  *(_DWORD *)&this->m_Task[61].bValid = 0;
  this->m_Task[62].fp = 0;
  *(_DWORD *)this->m_Task[62]._pad_0004 = 0;
  *(_DWORD *)&this->m_Task[62]._pad_0004[4] = 0;
  *(_DWORD *)&this->m_Task[62]._pad_0004[8] = 0;
  this->m_Task[62].vec1.x = 0.0;
  this->m_Task[62].vec1.y = 0.0;
  this->m_Task[62].vec1.z = 0.0;
  this->m_Task[62].cmd.dwCmdKind = 0;
  this->m_Task[62].cmd.dwCmdID = 0;
  this->m_Task[62].cmd.dwItemID = 0;
  this->m_Task[62].cmd.nSrcRole = 0;
  this->m_Task[62].cmd.nDestRole = 0;
  *(_DWORD *)&this->m_Task[62].cmd.bMultiSrcRole = 0;
  memset(this, 0, 0x1A18u);
  this->m_pStage = (CCBStage *)a2;
  v5 = (CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)a2 + 16);
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 0;
  this->m_pRoleState = v5;
  *(_DWORD *)&this->m_Task[62].cmd.bDestRole[3] = gbCrc32Compute(aOver);
  *(_DWORD *)&this->m_Task[62].cmd.bDestRole[7] = gbCrc32Compute(aWork);
  *(_DWORD *)&this->m_Task[62].cmd.bValid = gbCrc32Compute(aWork1);
  LODWORD(this->m_Task[62].fTemp) = gbCrc32Compute(aPause);
  LODWORD(this->m_Task[62].fTemp2) = gbCrc32Compute(aStore);
  this->m_Task[62].dwID = gbCrc32Compute(aFlyup);
  *(_DWORD *)this->m_Task[62].eMode = gbCrc32Compute(aFlydown);
  *(_DWORD *)&this->m_Task[62].bValid = 0;
  strcpy(this->m_sLastRole, "???");
  return (char *)this;
}

// 0x00509410
int CCBStageRole::GetRotAngle()
{
  unsigned int *p_dwCmdID; // ebp
  char *eMode; // ecx

  p_dwCmdID = (unsigned int *)&this->m_ThrowCmdData.dwCmdID;
  this->m_ThrowCmdData.dwCmdID = 0;
  this->m_ThrowCmdData.dwItemID = 0;
  eMode = (char *)this->m_Task[61].eMode;
  this->m_bValid = 0;
  this->m_bVisible = 0;
  p_dwCmdID[2] = 0;
  this->m_bPaused = 0;
  this->m_bAbsTime = 0;
  this->m_fTimeScale = 1.0;
  this->m_bAlive = 0;
  this->m_bRun = 0;
  this->m_bShowWeapon = 0;
  this->m_bFlash = 0;
  this->m_bForceFinishThrowingWeapon = 0;
  this->m_fMaxThrowSpeed = 0.0;
  this->m_fThrowSpeed = 0.0;
  this->m_fBlend = 0.0;
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[2] = 0;
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[6] = 0;
  LODWORD(this->m_Task[61].fTemp2) = 2;
  this->m_Task[61].dwID = 32;
  this->m_fThrowLen = 0.0;
  this->m_ThrowCmdData.dwCmdKind = -1;
  p_dwCmdID[3] = -1;
  this->m_bCatching = 0;
  *(&this->m_bCatching + 1) = 0;
  this->m_iState = 0;
  LODWORD(this->m_Task[61].fTemp) = 1;
  *(_DWORD *)eMode = 0;
  *((_DWORD *)eMode + 1) = 0;
  *((_DWORD *)eMode + 2) = 0;
  *(_DWORD *)this->m_Task[62]._pad_0004 = 0;
  *(_DWORD *)&this->m_Task[62]._pad_0004[4] = 0;
  *(_DWORD *)&this->m_Task[62]._pad_0004[8] = 0;
  this->m_Task[62].vec1.x = 0.0;
  this->m_Task[62].vec1.y = 0.0;
  this->m_Task[62].vec1.z = 0.0;
  this->m_Task[62].cmd.dwCmdKind = 0;
  this->m_Task[62].cmd.dwCmdID = 0;
  this->m_Task[62].cmd.dwItemID = 0;
  this->m_Task[62].cmd.nSrcRole = 0;
  this->m_Task[62].cmd.nDestRole = 0;
  *(_DWORD *)&this->m_Task[62].cmd.bMultiSrcRole = 0;
  memset(&this->m_ThrowCmdData.bMultiSrcRole, 0, 0x1800u);
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[10] = 0;
  return 0;
}

// 0x00509540
char CCBStageRole::IsIdle(unsigned int a2)
{
  _DWORD *v3; // eax
  int v4; // eax
  char Buffer[260]; // [esp+8h] [ebp-910h] BYREF
  char pExceptionObject[1024]; // [esp+10Ch] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+50Ch] [ebp-40Ch] BYREF
  int v9; // [esp+914h] [ebp-4h]

  v3 = (_DWORD *)operator new(0x224u);
  v9 = 0;
  if ( v3 )
    v4 = ((Actor *)v3)->FastInit();
  else
    v4 = 0;
  v9 = -1;
  this->m_nIndex = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_8, 120),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( a2 <= 4 )
  {
    switch ( a2 )
    {
      case 0u:
        sprintf(Buffer, dword_58619C);
        break;
      case 1u:
        sprintf(Buffer, dword_586198);
        break;
      case 2u:
        sprintf(Buffer, a106);
        break;
      case 3u:
        sprintf(Buffer, (const char *const)&dword_586190);
        break;
      case 4u:
        sprintf(Buffer, dword_58618C);
        break;
    }
    ((Actor *)this->m_nIndex)->LoadModel();
    this->ProcCatchED();
  }
  this->m_bFlash = 0;
  return 1;
}

// 0x00509690
char CCBStageRole::IsAtInitPos()
{
  Actor *m_nIndex; // ecx
  void *v3; // edi

  m_nIndex = (Actor *)this->m_nIndex;
  if ( !m_nIndex )
    return 1;
  m_nIndex->UpdateAllActions();
  v3 = (void *)this->m_nIndex;
  if ( v3 )
  {
    sub_40EE00(this->m_nIndex);
    operator delete(v3);
  }
  this->m_nIndex = 0;
  return 1;
}

// 0x005096D0
char CCBStageRole::IsAtProtectPos(int a2, int a3, int a4)
{
  int inited; // eax
  float m_fBlend; // eax
  unsigned int v7; // eax
  char *v8; // edi
  char *v9; // esi
  char v10; // cl
  const char *v11; // edi
  unsigned int v12; // edx
  const char *v13; // edi
  CCBStage *m_pStage; // eax
  CCBRoleState *m_pRoleState; // ecx
  CCBStageScene *m_pScene; // esi
  float *v17; // eax
  CCBStage *v18; // eax
  CCBRoleState *v19; // ecx
  CCBStageScene *v20; // esi
  int m_fBlend_low; // eax
  unsigned __int8 v22; // dl
  float v23; // eax
  const char *v25; // [esp-8h] [ebp-11Ch]
  float v26; // [esp+Ch] [ebp-108h]
  char Buffer[260]; // [esp+10h] [ebp-104h] BYREF

  this->GetRotAngle();
  LODWORD(this->m_fBlend) = a2;
  *(_DWORD *)&this->m_bBeSelected = a3;
  this->m_bValid = 1;
  this->m_bVisible = 1;
  this->m_bAlive = 1;
  *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[2] = 0;
  if ( a2 >= 5 && a2 < 11 )
  {
    if ( strcmp((const char *)(((CCBRoleState *)this->m_pRoleState)->InitUI(a2) + 8), this->m_sLastRole) )
    {
      v25 = (const char *)(((CCBRoleState *)this->m_pRoleState)->InitUI(a2) + 8);
      inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(a2);
      sprintf(Buffer, "role\\%s\\%s.ini", (const char *)(inited + 8), v25);
      m_fBlend = this->m_fBlend;
      if ( SLODWORD(m_fBlend) < 5
        || SLODWORD(m_fBlend) >= 11
        || (int)g_pVFileSys->FileExistNum(Buffer) > 0 )
      {
        ((CCBRoleState *)this->m_pRoleState)->InitUI(a2);
        ((Actor *)this->m_nIndex)->LoadModel();
        v11 = (const char *)(((CCBRoleState *)this->m_pRoleState)->InitUI(a2) + 8);
        v12 = strlen(v11) + 1;
        v13 = (const char *)&v11[v12];
        qmemcpy(this->m_sLastRole, &v13[-v12], 4 * (v12 >> 2));
        v9 = (char *)&v13[4 * (v12 >> 2) - v12];
        v8 = (char *)&this->m_sLastRole[4 * (v12 >> 2)];
        v10 = v12;
      }
      else
      {
        ((Actor *)this->m_nIndex)->LoadModel();
        v7 = strlen(a203) + 1;
        qmemcpy(this->m_sLastRole, a203, 4 * (v7 >> 2));
        v9 = (char *)&a203[4 * (v7 >> 2)];
        v8 = (char *)&this->m_sLastRole[4 * (v7 >> 2)];
        v10 = v7;
      }
      qmemcpy(v8, v9, v10 & 3);
    }
    this->ProcCatchED();
  }
  if ( ((CCBStageRole *)this->m_pRoleState)->IsActive(a2) )
    this->m_Task[61].dwID = 32;
  else
    this->m_Task[61].dwID = 50;
  this->IsGrabedBy();
  if ( ((CCBStageRole *)this->m_pRoleState)->IsActive(a2) == 1 )
  {
    m_pStage = (CCBStage *)this->m_pStage;
    m_pRoleState = (CCBRoleState *)this->m_pRoleState;
    *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[6] = 1110704128;
    m_pScene = (CCBStageScene *)m_pStage->m_pScene;
    v17 = (float *)&m_pScene->_pad_000[12 * m_pRoleState->IsAllWeDead(a2) + 8];
  }
  else
  {
    v18 = (CCBStage *)this->m_pStage;
    v19 = (CCBRoleState *)this->m_pRoleState;
    *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[6] = -1022951424;
    v20 = (CCBStageScene *)v18->m_pScene;
    v17 = (float *)&v20->_pad_0B0[12 * v19->IsAllWeDead(a2)];
  }
  this->m_Task[62].vec1.x = *v17;
  this->m_Task[62].vec1.y = v17[1];
  this->m_Task[62].vec1.z = v17[2];
  *(float *)this->m_Task[62]._pad_0004 = this->m_Task[62].vec1.x;
  *(float *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].vec1.y;
  *(float *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].vec1.z;
  v26 = *(float *)&this->m_Task[62].cmd.bSrcRole[6];
  m_fBlend_low = LODWORD(this->m_fBlend);
  *(float *)&this->m_Task[62].cmd.bSrcRole[2] = v26;
  if ( m_fBlend_low >= 5 && m_fBlend_low < 11 )
  {
    if ( !this->m_pRoleState->m_bWeSneakAttackEnemy )
      goto LABEL_24;
    goto LABEL_23;
  }
  if ( (unsigned int)m_fBlend_low <= 4 && this->m_pRoleState->m_bEnemySneakAttackUs )
LABEL_23:
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = v26 + 180.0;
LABEL_24:
  this->ClearAniMsg(0, 1.0);
  v22 = *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 878);
  v23 = this->m_fBlend;
  this->m_bShowWeaponModel = v22;
  if ( LODWORD(v23) <= 4 )
    this->m_bShowWeaponModel = 0;
  return 1;
}

// 0x005099A0
char CCBStageRole::IsTaskFinished@<al>(_DWORD *this@<ecx>, int a2@<edi>)
{
  char result; // al
  Actor *v4; // ecx
  int v5; // eax
  int inited; // eax
  int v7; // eax
  int v8; // ecx
  char *Instance; // eax
  char *v10; // eax
  int v11; // [esp-8h] [ebp-14h]
  float scale; // [esp+4h] [ebp-8h]
  float v13; // [esp+8h] [ebp-4h]

  result = *((_BYTE *)this + 264);
  if ( result )
  {
    v4 = (Actor *)*((_DWORD *)this + 73);
    if ( v4 )
    {
      scale = 1.3;
      if ( !*((_BYTE *)this + 380) )
      {
        v5 = *((_DWORD *)this + 1642);
        if ( v5 == 32 || v5 == 50 )
          scale = 0.64999998;
      }
      v13 = scale;
      if ( *((_BYTE *)this + 267) )
      {
        v4->SetTimeScale(scale);
      }
      else if ( *((_BYTE *)this + 266) )
      {
        v13 = 0.0;
      }
      else
      {
        v13 = scale * *((float *)this + 67);
      }
      v11 = a2;
      ((Actor *)*((_DWORD *)this + 73))->SetTimeScale(v13);
      if ( *(_DWORD *)(((CCBRoleState *)*((_DWORD *)this + 1))->InitUI(*((_DWORD *)this + 71)) + 848) )
      {
        inited = ((CCBRoleState *)*((_DWORD *)this + 1))->InitUI(*((_DWORD *)this + 71));
        ((gbGeomNode *)*(gbGeomNode **)(inited + 848))->SetBladeTimeScale(v13);
      }
      if ( *(_DWORD *)(((CCBRoleState *)*((_DWORD *)this + 1))->InitUI(*((_DWORD *)this + 71)) + 860) )
      {
        v7 = ((CCBRoleState *)*((_DWORD *)this + 1))->InitUI(*((_DWORD *)this + 71));
        ((gbGeomNode *)*(gbGeomNode **)(v7 + 860))->SetBladeTimeScale(v13);
      }
      if ( ((CCBStageRole *)this)->ForceDelTaskByPFN() && !*((_BYTE *)this + 380) )
      {
        ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
        if ( !((CCBRoleState *)*(CCBRoleState **)(*(_DWORD *)*this + 16))->IsRoleAlive(*((_DWORD *)this + 71)) )
          *((_BYTE *)this + 272) = 0;
      }
      v8 = *((_DWORD *)this + 73);
      *((_DWORD *)this + 1660) = 0;
      if ( ((gbVisNode *)*(gbVisNode **)(v8 + 16))->PopMessage((struct gbNodeMsgObj *)&dword_17AB9C8) == 1
        && dword_17AB9C8 == 1 )
      {
        *((_DWORD *)this + 1660) = dword_17AB9CC;
      }
      if ( !*((_BYTE *)this + 380) )
        ((CCBStageRole *)this)->Grab(*((_DWORD *)this + 1660));
      if ( !*((_DWORD *)this + 71) && *((_DWORD *)this + 1642) != 31 )
      {
        Instance = (char *)CScreenMode::GetInstance();
        ((CCBStageRole *)Instance)->PlaySound(aWe011, a2);
      }
      if ( *((_DWORD *)this + 71) == 4 && *((_DWORD *)this + 1642) != 31 )
      {
        v10 = (char *)CScreenMode::GetInstance();
        ((CCBStageRole *)v10)->PlaySound(aWe011b, v11);
      }
      return ((Actor *)*((_DWORD *)this + 73))->QueryState();
    }
  }
  return result;
}

// 0x00509B90
void CCBStageRole::IsDoTask(gbMatrixStack *a2)
{
  float m_fBlend; // eax
  int m_fBlend_low; // eax
  int v5; // esi
  int v6; // edi
  char RoleType; // al
  unsigned int v8; // edi
  char *v9; // esi
  int v10; // ebx
  unsigned int dwID; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int *LastBladePos; // ecx
  double v16; // st7
  int inited; // eax
  CCBStage *m_pStage; // eax
  unsigned __int8 m_bShowWeaponModel; // cl
  __int16 v20; // [esp+2Ch] [ebp-6Ah]
  float v21; // [esp+32h] [ebp-64h] BYREF
  float v22; // [esp+36h] [ebp-60h] BYREF
  struct gbVec3D v23; // [esp+3Ah] [ebp-5Ch] BYREF
  float v24[4]; // [esp+46h] [ebp-50h] BYREF
  _BYTE v25[64]; // [esp+56h] [ebp-40h] BYREF

  if ( (byte_17AB9C4 & 1) == 0 )
  {
    dword_17AB9B8 = 0;
    byte_17AB9C4 |= 1u;
    dword_17AB9BC = 1065353216;
    dword_17AB9C0 = 0;
    atexit(nullsub_32);
  }
  ((gbMatrix4 *)v25)->gbMatrix4();
  m_fBlend = this->m_fBlend;
  memset(&v23, 0, sizeof(v23));
  v20 = 0;
  if ( SLODWORD(m_fBlend) >= 5 && SLODWORD(m_fBlend) < 11 )
    this->ProcPursueRole(0, 0, 0);
  if ( this->m_bShowWeapon )
  {
    this->DoTask(&v23.x);
    m_fBlend_low = LODWORD(this->m_fBlend);
    v23.y = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 10.0 + (double)m_fBlend_low) * 5.0 + v23.y + 6.0;
    if ( (unsigned int)m_fBlend_low <= 4
      || m_fBlend_low >= 5 && m_fBlend_low < 11 && this->ForceEndTaskByPFN() )
    {
      ((gbCamera *)&this->m_pStage->m_pCam->_base[4])->PointWorldToScr(&v23, &v21, &v22);
      v5 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(LODWORD(this->m_fBlend), 0);
      v6 = ((CCBRoleState *)this->m_pRoleState)->SetRoleField(LODWORD(this->m_fBlend), 1);
      RoleType = ((CCBRoleState *)this->m_pRoleState)->GetRoleType(LODWORD(this->m_fBlend));
      if ( LODWORD(this->m_fBlend) == 10 && this->m_pRoleState->m_bMustFail || RoleType && v5 > v6 / 4 )
        strcpy(byte_17AB8B8, *(const char **)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 888));
      else
        sprintf(byte_17AB8B8, "%d/%d", v5, v6);
      v8 = 10 * strlen(byte_17AB8B8);
      v9 = (char *)(__int64)((v21 + 1.0) * (double)(int)g_pGameTime * 0.5);
      v10 = (__int64)((1.0 - v22) * (double)(int)g_pAbsTime * 0.5);
      if ( (int)v9 >= 0 )
      {
        if ( (int)v9 > (int)((char *)g_pGameTime - v8) )
          v9 = (char *)g_pGameTime - v8;
      }
      else
      {
        v9 = 0;
      }
      if ( v10 >= 20 )
      {
        if ( v10 > (int)g_pAbsTime )
          v10 = (int)g_pAbsTime;
      }
      else
      {
        v10 = 20;
      }
      sub_4DFC40((char *)this->m_pStage->m_TempStorageNGH, byte_17AB8B8, (int)v9, v10, -1);
      if ( LODWORD(this->m_fBlend) > 4 )
        this->ProcPursueRole((int)v9, v10, 1);
    }
  }
  if ( BYTE1(this->m_pStage->m_pCBSystem->m_nTimesOfCombat) && g_nCombatMode == 1
    || this->m_bVisible && (this->m_bAlive || SLODWORD(this->m_fBlend) < 5) )
  {
    a2->Push();
    a2->Translate((struct gbVec3D *)this->m_Task[62]._pad_0004);
    a2->Rotate(*(float *)&this->m_Task[62].cmd.bSrcRole[2], (struct gbVec3D *)&dword_17AB9B8);
    dwID = this->m_Task[61].dwID;
    switch ( dword_56FE98[dwID] )
    {
      case 1:
        v20 = 1;
        break;
      case 2:
        v20 = 256;
        break;
      case 3:
        v20 = 0;
        break;
    }
    v12 = LODWORD(this->m_fBlend);
    if ( !v12 && (dwID == 39 || dwID == 49) )
      v20 = 0;
    if ( v12 == 3 )
      v20 = 257;
    if ( v12 == 1 )
      v20 = 257;
    if ( (v12 == 2 || v12 == 4) && dwID == 46 )
      v20 = 256;
    if ( this->m_bForceFinishThrowingWeapon )
    {
      if ( this->m_fMaxThrowSpeed > 0.0 || (LOBYTE(v20) = 0, this->m_fMaxThrowSpeed >= 0.0) )
        LOBYTE(v20) = 1;
      if ( this->m_fThrowSpeed <= 0.0 && this->m_fThrowSpeed < 0.0 )
        goto LABEL_64;
    }
    else if ( !HIBYTE(v20) )
    {
LABEL_64:
      if ( (_BYTE)v20 && *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 848) )
      {
        a2->Push();
        ((gbActor *)*(gbActor **)(this->m_nIndex + 16))->GetTagNodeTM((struct gbMatrix4 *)v25, aTagWeapon2);
        a2->MultMatrix((struct gbMatrix4 *)v25);
        inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
        (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)(inited + 848) + 16))(*(_DWORD *)(inited + 848), 0);
        a2->Pop();
      }
      if ( this->m_bFlash )
      {
        m_pStage = (CCBStage *)this->m_pStage;
        m_bShowWeaponModel = this->m_bShowWeaponModel;
        v24[0] = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 7.8000002) * 0.34999999 + 0.64999998;
        v24[1] = v24[0];
        v24[2] = v24[0];
        if ( m_bShowWeaponModel )
        {
          ((gbRenderEffect *)*(gbRenderEffect **)&m_pStage->m_TempStorageWPX[4].m_name[36])->SetVariant(PARAM_HANDLE_SPECULAR, v24);
          ((Actor *)this->m_nIndex)->DispatchAction(*(_DWORD *)&this->m_pStage->m_TempStorageWPX[4].m_name[36]);
        }
        else
        {
          ((gbRenderEffect *)*(gbRenderEffect **)&m_pStage->m_TempStorageWPX[4].m_name[32])->SetVariant(PARAM_HANDLE_SPECULAR, v24);
          ((Actor *)this->m_nIndex)->DispatchAction(*(_DWORD *)&this->m_pStage->m_TempStorageWPX[4].m_name[32]);
        }
      }
      else
      {
        ((Actor *)this->m_nIndex)->DispatchAction(0);
      }
      a2->Pop();
      return;
    }
    if ( *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v12) + 860) )
    {
      a2->Push();
      ((gbActor *)*(gbActor **)(this->m_nIndex + 16))->GetTagNodeTM((struct gbMatrix4 *)v25, aTagWeapon1);
      a2->MultMatrix((struct gbMatrix4 *)v25);
      v13 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)(v13 + 860) + 16))(*(_DWORD *)(v13 + 860), 0);
      a2->Pop();
      if ( LODWORD(this->m_fBlend) == 3 && *(_BYTE *)(g_SceneMgr.m_slot[3]._d108 + 613) == 3 )
      {
        v14 = ((CCBRoleState *)this->m_pRoleState)->InitUI(3);
        LastBladePos = (int *)((gbGeomNode *)*(gbGeomNode **)(v14 + 860))->GetLastBladePos(0);
        if ( LastBladePos )
        {
          v16 = this->m_pStage->m_pCBSystem->m_DeltaTime + flt_17ABCCC;
          flt_17ABCCC = v16;
          if ( v16 >= 0.050000001 )
          {
            ((C3DSpark *)this->m_pStage->m_pCBSystem->m_p3DSpark)->CreateOne(*LastBladePos, LastBladePos[1], LastBladePos[2]);
            flt_17ABCCC = flt_17ABCCC - 0.050000001;
          }
        }
      }
    }
    goto LABEL_64;
  }
}

// 0x0050A180
int CCBStageRole::Grab(int a2)
{
  sub_50B430((char *)this, a2);
  sub_50B4C0(this);
  return sub_50B4F0(this);
}

// 0x0050A1A0
char CCBStageRole::Release(char a2)
{
  this->m_bAlive = a2;
  return a2;
}

// 0x0050A1B0
void CCBStageRole::TryRelease()
{
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 23) )
    this->ClearAniMsg(1, 0.44);
  else
    this->ClearAniMsg(0, 1.0);
}

// 0x0050A1F0
char CCBStageRole::ForceRelease(char a2)
{
  this->m_bVisible = a2;
  return a2;
}

// 0x0050A200
char CCBStageRole::DangerForceRelease(char a2)
{
  this->m_bPaused = a2;
  return a2;
}

// 0x0050A210
int CCBStageRole::IsGrabedBy()
{
  Actor *m_nIndex; // ecx
  int result; // eax

  m_nIndex = (Actor *)this->m_nIndex;
  if ( m_nIndex )
  {
    m_nIndex->EnableTransition(*(&bVisible + this->m_Task[61].dwID), this->m_bShowWeaponModel != 0);
    return ((Actor *)this->m_nIndex)->CompareAction(this->m_Task[61].dwID, 0);
  }
  return result;
}

// 0x0050A260
void CCBStageRole::GetPointerPos()
{
  Actor *m_nIndex; // ecx

  m_nIndex = (Actor *)this->m_nIndex;
  if ( m_nIndex )
  {
    m_nIndex->EnableTransition(*(&bVisible + this->m_Task[61].dwID), this->m_bShowWeaponModel != 0);
    ((Actor *)this->m_nIndex)->SetVisible(*(&bVisible + this->m_Task[61].dwID));
  }
}

// 0x0050A2B0
void CCBStageRole::SetBladeTime(int a2)
{
  int *pad_0004; // eax
  double v4; // st7
  double v5; // st6
  long double v6; // st7
  int v7; // [esp+8h] [ebp-8h]
  int v8; // [esp+Ch] [ebp-4h]

  if ( (byte_17AB8B4 & 1) == 0 )
  {
    dword_17AB8A8 = 0;
    byte_17AB8B4 |= 1u;
    dword_17AB8AC = 0;
    dword_17AB8B0 = 0;
    atexit(nullsub_35);
  }
  if ( (byte_17AB8B4 & 2) == 0 )
  {
    dword_17AB898 = 0;
    byte_17AB8B4 |= 2u;
    dword_17AB89C = 0;
    dword_17AB8A0 = 0;
    atexit(nullsub_34);
  }
  if ( (byte_17AB8B4 & 4) == 0 )
  {
    byte_17AB8B4 |= 4u;
    dword_17AB888 = 0;
    dword_17AB88C = 0;
    dword_17AB890 = 1065353216;
    atexit(nullsub_33);
  }
  pad_0004 = (int *)this->m_pStage->m_pRole[a2]->m_Task[62]._pad_0004;
  dword_17AB898 = *pad_0004;
  dword_17AB89C = pad_0004[1];
  dword_17AB8A0 = pad_0004[2];
  v4 = *(float *)&dword_17AB898 - *(float *)this->m_Task[62]._pad_0004;
  *(float *)&v7 = *(float *)&dword_17AB89C - *(float *)&this->m_Task[62]._pad_0004[4];
  v5 = *(float *)&dword_17AB8A0 - *(float *)&this->m_Task[62]._pad_0004[8];
  dword_17AB8AC = v7;
  *(float *)&v8 = v5;
  *(float *)&dword_17AB8A8 = v4;
  dword_17AB8B0 = v8;
  ((gbVec3D *)&dword_17AB8A8)->Normalize();
  v6 = acos(
         *(float *)&dword_17AB890 * *(float *)&dword_17AB8B0
       + *(float *)&dword_17AB88C * *(float *)&dword_17AB8AC
       + *(float *)&dword_17AB888 * *(float *)&dword_17AB8A8);
  *(float *)&this->m_Task[62].cmd.bSrcRole[2] = v6;
  if ( *(float *)&dword_17AB8A8 < 0.0 )
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = 6.2831855 - v6;
  *(float *)&this->m_Task[62].cmd.bSrcRole[2] = *(float *)&this->m_Task[62].cmd.bSrcRole[2] * 57.29578;
}

// 0x0050A500
bool CCBStageRole::LoadAction(gbRay a2)
{
  struct gbOBBox *WorldPos; // eax

  WorldPos = (struct gbOBBox *)this->GetWorldPos();
  return ((gbRay *)&a2)->IsColOBB(WorldPos) == 1;
}

// 0x0050A520
int CCBStageRole::GetStatus(int index)
{
  ((Actor *)this->m_nIndex)->PlayAction((int)&this->m_dwID);
  return LODWORD(this->m_fBlend);
}

// 0x0050A560
float * CCBStageRole::GetWorldPos()
{
  _BYTE v3[64]; // [esp+8h] [ebp-40h] BYREF

  ((gbMatrix4 *)v3)->gbMatrix4();
  ((Actor *)this->m_nIndex)->PlayAction((int)&this->m_dwID);
  ((gbMatrix4 *)v3)->LoadIdentity();
  ((gbMatrix4 *)v3)->SetAxisAngle(GB_AXIS_Y, *(float *)&this->m_Task[62].cmd.bSrcRole[2]);
  ((gbMatrix4 *)&this->m_dwID)->RightMultiply((const struct gbMatrix4 *)v3);
  ((gbMatrix4 *)&this->m_dwID)->RightTranslate((struct gbVec3D *)this->m_Task[62]._pad_0004);
  return (float *)&this->m_dwID;
}

// 0x0050A5D0
double CCBStageRole::AddTask(float *a2)
{
  double v3; // st7
  double v4; // st6
  double v6; // st7
  gbVec3D v7; // [esp+4h] [ebp-18h] BYREF
  float v8; // [esp+14h] [ebp-8h]
  float v9; // [esp+18h] [ebp-4h]

  if ( (byte_17AB884 & 1) == 0 )
  {
    v7.x = 0.0;
    byte_17AB884 |= 1u;
    v7.y = 0.0;
    v7.z = 1.0;
    dword_17AB878 = 0;
    dword_17AB87C = 0;
    dword_17AB880 = 1065353216;
    atexit(nullsub_36);
  }
  v3 = *a2 - *(float *)this->m_Task[62]._pad_0004;
  v8 = a2[1] - *(float *)&this->m_Task[62]._pad_0004[4];
  v4 = a2[2] - *(float *)&this->m_Task[62]._pad_0004[8];
  v7.y = v8;
  v9 = v4;
  v7.x = v3;
  v7.z = v9;
  if ( ((gbVec3D *)&v7)->Length() <= 0.0 )
    return 0.0;
  ((gbVec3D *)&v7)->Normalize();
  v6 = acos(v7.y * *(float *)&dword_17AB87C + v7.z * *(float *)&dword_17AB880 + *(float *)&dword_17AB878 * v7.x);
  if ( v7.x < 0.0 )
    v6 = 6.2831855 - v6;
  return v6 * 57.29578;
}

// 0x0050A6F0
bool CCBStageRole::ForceDelTaskByPFN()
{
  return LODWORD(this->m_fThrowLen) == 0;
}

// 0x0050A700
bool CCBStageRole::ForceEndTaskByPFN()
{
  double v1; // st7
  double v2; // st6
  float v4; // [esp+4h] [ebp-14h]
  float v5; // [esp+8h] [ebp-10h]
  gbVec3D v6; // [esp+Ch] [ebp-Ch] BYREF

  v1 = *(float *)this->m_Task[62]._pad_0004 - this->m_Task[62].vec1.x;
  v4 = *(float *)&this->m_Task[62]._pad_0004[4] - this->m_Task[62].vec1.y;
  v2 = *(float *)&this->m_Task[62]._pad_0004[8] - this->m_Task[62].vec1.z;
  v6.y = v4;
  v5 = v2;
  v6.x = v1;
  v6.z = v5;
  return ((gbVec3D *)&v6)->Length() <= 13.0;
}

// 0x0050A770
bool CCBStageRole::EndTask(int a2, int a3)
{
  float m_fBlend; // eax
  CCBStage *m_pStage; // ecx
  float *v6; // eax
  float *p_x; // ecx
  double v8; // st7
  double v9; // st6
  CCBStage *v10; // edx
  float *v11; // eax
  double v12; // st7
  double v13; // st7
  double v14; // st6
  gbVec3D v16; // [esp+4h] [ebp-30h] BYREF
  gbVec3D v17; // [esp+10h] [ebp-24h] BYREF
  float v18; // [esp+20h] [ebp-14h]
  float v19; // [esp+24h] [ebp-10h]
  float v20; // [esp+2Ch] [ebp-8h]
  float v21; // [esp+30h] [ebp-4h]

  memset(&v16, 0, sizeof(v16));
  m_fBlend = this->m_fBlend;
  memset(&v17, 0, sizeof(v17));
  if ( m_fBlend != 0.0 )
    return 0;
  m_pStage = (CCBStage *)this->m_pStage;
  v6 = (float *)m_pStage->m_pRole[a2];
  p_x = (float *)&m_pStage->m_pRole[a3]->m_Task[62].vec1.x;
  v6 += 1649;
  v8 = *p_x - *v6;
  v18 = p_x[1] - v6[1];
  v9 = p_x[2] - v6[2];
  v16.y = v18;
  v19 = v9;
  v16.x = v8;
  v16.z = v19;
  ((gbVec3D *)&v16)->Normalize();
  v10 = (CCBStage *)this->m_pStage;
  v16.x = v16.x * 40.0;
  v16.y = v16.y * 40.0;
  v16.z = v16.z * 40.0;
  v11 = (float *)v10->m_pRole[a2];
  v12 = v16.x + v11[1649];
  v18 = v16.y + v11[1650];
  v19 = v16.z + v11[1651];
  v16.x = v12;
  v16.z = v19;
  v16.y = v18;
  v13 = *(float *)this->m_Task[62]._pad_0004 - v12;
  v20 = *(float *)&this->m_Task[62]._pad_0004[4] - v18;
  v14 = *(float *)&this->m_Task[62]._pad_0004[8] - v19;
  v17.y = v20;
  v21 = v14;
  v17.x = v13;
  v17.z = v21;
  return ((gbVec3D *)&v17)->Length() <= 20.0;
}

// 0x0050A8E0
char CCBStageRole::DelTask(int a2)
{
  LODWORD(this->m_Task[61].fTemp2) = a2;
  return 1;
}

// 0x0050A8F0
char CCBStageRole::DelAllTask(int a2, char a3)
{
  char result; // al

  result = 1;
  if ( this->m_bCatching == 1 )
    return 0;
  this->m_bCatching = 1;
  *(&this->m_bCatching + 1) = a3;
  this->m_iState = a2;
  return result;
}

// 0x0050A920
char CCBStageRole::GetCurrentTask(int a2)
{
  char result; // al

  if ( a2 != 0x7FFFFFFF || (result = this->m_bCatching) != 0 )
  {
    result = this->GetState();
    this->m_bCatching = 0;
    *(&this->m_bCatching + 1) = 0;
    this->m_iState = 0;
  }
  return result;
}

// 0x0050A960
int CCBStageRole::GetCurrentTaskIndex()
{
  this->GetState();
  this->m_bCatching = 0;
  *(&this->m_bCatching + 1) = 0;
  this->m_iState = 0;
  return 0;
}

// 0x0050A980
bool CCBStageRole::IsReady(int idx)
{
  return this->m_bCatching && this->m_iState == idx;
}

// 0x0050A9B0
_DWORD * CCBStageRole::DoTask(float *a2)
{
  float *WorldPos; // eax
  float *Center; // eax
  _DWORD *result; // eax
  char v6[12]; // [esp+8h] [ebp-Ch] BYREF

  if ( (byte_17AB874 & 1) == 0 )
  {
    byte_17AB874 |= 1u;
    ((gbMatrix4 *)&stru_17AB828)->gbMatrix4();
    atexit(nullsub_37);
  }
  WorldPos = (float *)this->GetWorldPos();
  Center = (float *)WorldPos->GetCenter(v6);
  * a2 = (*)*Center;
  a2[1] = Center[1];
  a2[2] = Center[2];
  a2[1] = this->m_vecLen.y * 0.5 + a2[1] + 10.0;
  result = (_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
  if ( *result == 707 )
    a2[1] = a2[1] - 80.0;
  return result;
}

// 0x0050AA60
void CCBStageRole::ClearBadPushTask(float a2)
{
  unsigned int m_fBlend_low; // eax
  int inited; // eax
  int v5; // eax

  m_fBlend_low = LODWORD(this->m_fBlend);
  if ( m_fBlend_low <= 4 )
  {
    if ( *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(m_fBlend_low) + 848) )
    {
      inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbGeomNode *)*(gbGeomNode **)(inited + 848))->SetBladeTime(a2);
    }
    if ( *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 860) )
    {
      v5 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbGeomNode *)*(gbGeomNode **)(v5 + 860))->SetBladeTime(a2);
    }
  }
}

// 0x0050AAE0
double CCBStageRole::PushBackAllTask()
{
  int m_nIndex; // eax
  float v3; // [esp+4h] [ebp-4h] BYREF

  m_nIndex = this->m_nIndex;
  v3 = 0.0;
  if ( ((gbVisNode *)*(gbVisNode **)(m_nIndex + 16))->GetBlend(&v3) )
    return v3;
  else
    return 1.0;
}

// 0x0050AB10
void CCBStageRole::ClearAniMsg(char a2, float a3)
{
  int inited; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax

  if ( a3 <= 0.98000002 && a2 )
  {
    ((gbVisNode *)*(gbVisNode **)(this->m_nIndex + 16))->SetBlend(BLEND_ALPHA, a3);
    if ( *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 860) )
    {
      inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbVisNode *)*(gbVisNode **)(inited + 860))->SetBlend(BLEND_ALPHA, a3);
    }
    if ( *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 848) )
    {
      v5 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbVisNode *)*(gbVisNode **)(v5 + 848))->SetBlend(BLEND_ALPHA, a3);
    }
  }
  else
  {
    ((gbVisNode *)*(gbVisNode **)(this->m_nIndex + 16))->SetBlend(BLEND_NONE, 1.0);
    if ( *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 860) )
    {
      v6 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbVisNode *)*(gbVisNode **)(v6 + 860))->SetBlend(BLEND_NONE, 1.0);
    }
    if ( *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 848) )
    {
      v7 = ((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend));
      ((gbVisNode *)*(gbVisNode **)(v7 + 848))->SetBlend(BLEND_NONE, 1.0);
    }
  }
}

// 0x0050AC50
int CCBStageRole::SetParam(int a2, char a3)
{
  int result; // eax
  Actor *m_nIndex; // ecx

  result = a2;
  if ( a2 > 0 )
  {
    sprintf(byte_17AB818, "z%02d", a2);
    if ( (byte_1895558 & 1) == 0 )
    {
      byte_1895558 |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    result = ((CEffSParticle *)&g_nCursorState)->GetEditorTaskDescription((unsigned __int8 *)byte_17AB818);
    if ( a3 || result != *(_DWORD *)&this->m_Task[62].bValid )
    {
      m_nIndex = (Actor *)this->m_nIndex;
      *(_DWORD *)&this->m_Task[62].bValid = result;
      m_nIndex->SetVisible((int)byte_17AB818);
      return (*(int (**)(_DWORD, _DWORD))(**(_DWORD **)(this->m_nIndex + 16) + 24))(
               *(_DWORD *)(this->m_nIndex + 16),
               0);
    }
  }
  return result;
}

// 0x0050AD30
char CCBStageRole::GetProperCurAction(
        CCBStageRole *this,
        _DWORD *a2,
        _DWORD *a3,
        _DWORD *a4,
        _DWORD *a5,
        _DWORD *a6,
        int *a7,
        const void *a8,
        _DWORD *a9)
{
  int *v11; // eax
  unsigned __int8 *v12; // eax
  unsigned __int8 *v13; // eax
  _DWORD v14[3]; // [esp+4h] [ebp-Ch] BYREF

  if ( (byte_17AB804 & 1) == 0 )
  {
    dword_17AB7F8 = 0;
    byte_17AB804 |= 1u;
    dword_17AB7FC = 0;
    dword_17AB800 = 0;
    atexit(nullsub_40);
  }
  if ( (byte_17AB804 & 2) == 0 )
  {
    dword_17AB7E8 = 0;
    byte_17AB804 |= 2u;
    dword_17AB7EC = 0;
    dword_17AB7F0 = 0;
    atexit(nullsub_39);
  }
  if ( (byte_17AB804 & 4) == 0 )
  {
    dword_17AB7D8 = 0;
    byte_17AB804 |= 4u;
    dword_17AB7DC = 0;
    dword_17AB7E0 = 0;
    atexit(nullsub_38);
  }
  if ( (_DWORD *)this->m_iState != a6 )
    return 0;
  v11 = a7;
  if ( !a7 )
  {
    memset(v14, 0, sizeof(v14));
    v11 = v14;
  }
  dword_17AB7F8 = *v11;
  dword_17AB7FC = v11[1];
  dword_17AB800 = v11[2];
  if ( a9 == (_DWORD *)2 )
  {
    this->GetState();
    goto LABEL_15;
  }
  if ( a9 != (_DWORD *)3 )
  {
LABEL_15:
    v12 = (unsigned __int8 *)&this->m_ThrowCmdData.bMultiSrcRole + 96 * LODWORD(this->m_fThrowLen);
    *(_DWORD *)v12 = a2;
    *((_DWORD *)v12 + 1) = a3;
    *((_DWORD *)v12 + 2) = a4;
    *((_DWORD *)v12 + 3) = a5;
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * LODWORD(this->m_fThrowLen)) = 1;
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * LODWORD(this->m_fThrowLen) + 2) = 0;
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * LODWORD(this->m_fThrowLen) + 1) = 0;
    *((_DWORD *)&this->m_OBBox.trans.ty + 24 * LODWORD(this->m_fThrowLen)) = ((CCBSystem *)this->m_pStage->m_pCBSystem)->ProcProtect();
    v13 = (unsigned __int8 *)&this->m_ThrowCmdData.bDestRole[96 * LODWORD(this->m_fThrowLen) + 3];
    *(_DWORD *)v13 = dword_17AB7F8;
    *((_DWORD *)v13 + 1) = dword_17AB7FC;
    *((_DWORD *)v13 + 2) = dword_17AB800;
    *((_DWORD *)&this->m_OBBox.trans.tz + 24 * LODWORD(this->m_fThrowLen)) = a9;
    if ( a8 )
      qmemcpy((char *)&this->m_OBBox + 96 * LODWORD(this->m_fThrowLen), a8, 0x2Cu);
    else
      memset((char *)&this->m_OBBox + 96 * LODWORD(this->m_fThrowLen), 0, 0x2Cu);
    goto LABEL_23;
  }
  this->GetTaskState();
  LOBYTE(this->m_OBBox.trans.tw) = 1;
  BYTE2(this->m_OBBox.trans.tw) = 0;
  BYTE1(this->m_OBBox.trans.tw) = 0;
  *(_DWORD *)&this->m_ThrowCmdData.bMultiSrcRole = a2;
  *(_DWORD *)&this->m_ThrowCmdData.bSrcRole[2] = a3;
  *(_DWORD *)&this->m_ThrowCmdData.bSrcRole[6] = a4;
  *(_DWORD *)&this->m_ThrowCmdData.bSrcRole[10] = a5;
  LODWORD(this->m_OBBox.trans.ty) = ((CCBSystem *)this->m_pStage->m_pCBSystem)->ProcProtect();
  *(_DWORD *)&this->m_ThrowCmdData.bDestRole[3] = dword_17AB7F8;
  *(_DWORD *)&this->m_ThrowCmdData.bDestRole[7] = dword_17AB7FC;
  *(_DWORD *)&this->m_ThrowCmdData.bValid = dword_17AB800;
  LODWORD(this->m_OBBox.trans.tz) = 3;
  if ( a8 )
    qmemcpy(&this->m_OBBox, a8, 0x2Cu);
  else
    memset(&this->m_OBBox, 0, 0x2Cu);
  BYTE2(this->m_fRightWeapon) = 0;
LABEL_23:
  ++LODWORD(this->m_fThrowLen);
  return 1;
}

// 0x0050B070
char CCBStageRole::ProcTransportRun(
        CCBStageRole *this,
        float a2,
        float a3,
        int a4,
        int a5,
        int *a6,
        const void *a7,
        float a8)
{
  int *v9; // eax
  float v11; // eax
  _DWORD v12[3]; // [esp+8h] [ebp-Ch] BYREF

  if ( (byte_17AB7D4 & 1) == 0 )
  {
    dword_17AB7C8 = 0;
    byte_17AB7D4 |= 1u;
    dword_17AB7CC = 0;
    dword_17AB7D0 = 0;
    atexit(nullsub_43);
  }
  if ( (byte_17AB7D4 & 2) == 0 )
  {
    dword_17AB7B8 = 0;
    byte_17AB7D4 |= 2u;
    dword_17AB7BC = 0;
    dword_17AB7C0 = 0;
    atexit(nullsub_42);
  }
  if ( (byte_17AB7D4 & 4) == 0 )
  {
    dword_17AB7A8 = 0;
    byte_17AB7D4 |= 4u;
    dword_17AB7AC = 0;
    dword_17AB7B0 = 0;
    atexit(nullsub_41);
  }
  v9 = a6;
  if ( !a6 )
  {
    memset(v12, 0, sizeof(v12));
    v9 = v12;
  }
  dword_17AB7C8 = *v9;
  dword_17AB7CC = v9[1];
  dword_17AB7D0 = v9[2];
  switch ( LODWORD(a8) )
  {
    case 2:
      this->GetState();
      break;
    case 3:
      this->GetTaskState();
      break;
    case 4:
      if ( SLODWORD(this->m_fThrowLen) > 0 )
        return 0;
      break;
    default:
      return 0;
  }
  LOBYTE(this->m_OBBox.trans.tw) = 1;
  BYTE2(this->m_OBBox.trans.tw) = 0;
  BYTE1(this->m_OBBox.trans.tw) = 0;
  *(float *)&this->m_ThrowCmdData.bMultiSrcRole = a2;
  *(float *)&this->m_ThrowCmdData.bSrcRole[2] = a3;
  *(_DWORD *)&this->m_ThrowCmdData.bSrcRole[6] = a4;
  *(_DWORD *)&this->m_ThrowCmdData.bSrcRole[10] = a5;
  LODWORD(this->m_OBBox.trans.ty) = ((CCBSystem *)this->m_pStage->m_pCBSystem)->ProcProtect();
  *(_DWORD *)&this->m_ThrowCmdData.bDestRole[3] = dword_17AB7C8;
  *(_DWORD *)&this->m_ThrowCmdData.bDestRole[7] = dword_17AB7CC;
  *(_DWORD *)&this->m_ThrowCmdData.bValid = dword_17AB7D0;
  this->m_OBBox.trans.tz = a8;
  if ( a7 )
    qmemcpy(&this->m_OBBox, a7, 0x2Cu);
  else
    memset(&this->m_OBBox, 0, 0x2Cu);
  LODWORD(v11) = LODWORD(this->m_fThrowLen) + 1;
  BYTE2(this->m_fRightWeapon) = 0;
  this->m_fThrowLen = v11;
  return 1;
}

// 0x0050B290
char CCBStageRole::SetForceFinishThrowingWeapon(int a2)
{
  int v2; // ebx
  unsigned __int8 *v4; // eax

  v2 = a2;
  if ( a2 == 63 )
  {
    memset(&this->m_Task[60].fTemp, 0, 0x60u);
    --LODWORD(this->m_fThrowLen);
    return 1;
  }
  else
  {
    if ( a2 < SLODWORD(this->m_fThrowLen) )
    {
      v4 = (unsigned __int8 *)&this->m_ThrowCmdData.bMultiSrcRole + 96 * a2;
      do
      {
        ++v2;
        qmemcpy(v4, v4 + 96, 0x60u);
        v4 += 96;
      }
      while ( v2 < SLODWORD(this->m_fThrowLen) );
    }
    memset(&this->m_ThrowCmdData.bMultiSrcRole + 96 * LODWORD(this->m_fThrowLen)--, 0, 0x60u);
    return 1;
  }
}

// 0x0050B330
char CCBStageRole::GetState()
{
  float *p_ty; // eax
  int v2; // edx

  p_ty = (float *)&this->m_OBBox.trans.ty;
  v2 = 64;
  do
  {
    *((_BYTE *)p_ty + 8) = 0;
    *p_ty = 0.0;
    p_ty += 24;
    --v2;
  }
  while ( v2 );
  this->m_fThrowLen = 0.0;
  return 1;
}

// 0x0050B360
int CCBStageRole::ProcCatchED()
{
  int result; // eax

  if ( SLODWORD(this->m_fBlend) < 5 )
  {
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)aZ01);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)aZ09);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)aZ06);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)aZ03);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)aZ04);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)aZ05);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)&unk_5888D0);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)&unk_5888C8);
    ((Actor *)this->m_nIndex)->GetAnimDuration((int)&unk_5888C4);
    return ((Actor *)this->m_nIndex)->GetAnimDuration((int)&aNghOpenObjD);
  }
  return result;
}

// 0x0050B530
int CCBStageRole::GetTaskState()
{
  int result; // eax
  float m_fThrowLen; // edx
  unsigned __int8 *v3; // edi

  result = LODWORD(this->m_fThrowLen);
  if ( result )
  {
    if ( result > 0 )
    {
      m_fThrowLen = this->m_fThrowLen;
      v3 = (unsigned __int8 *)&this->m_ThrowCmdData.bMultiSrcRole + 96 * result;
      do
      {
        --LODWORD(m_fThrowLen);
        qmemcpy(v3, v3 - 96, 0x60u);
        v3 -= 96;
      }
      while ( m_fThrowLen != 0.0 );
    }
    memset(&this->m_ThrowCmdData.bMultiSrcRole, 0, 0x60u);
    return 0;
  }
  return result;
}

// 0x0050B580
char CCBStageRole::ProcPursueRole(int a2, int a3, char a4)
{
  CCBUI *m_pUI; // edi
  void (***v6)(_DWORD, int); // ecx
  int v7; // ebx
  void (***v8)(_DWORD, int); // ecx
  void (***v9)(_DWORD, int); // ecx
  void (***v10)(_DWORD, int); // ecx
  void (***v11)(_DWORD, int); // ecx
  void (***v12)(_DWORD, int); // ecx
  void (***v13)(_DWORD, int); // ecx
  void (***v14)(_DWORD, int); // ecx
  void (***v15)(_DWORD, int); // ecx
  void (***v16)(_DWORD, int); // ecx
  void (***v17)(_DWORD, int); // ecx
  void (***v18)(_DWORD, int); // ecx
  void (***v19)(_DWORD, int); // ecx
  void (***v20)(_DWORD, int); // ecx
  void (***v21)(_DWORD, int); // ecx
  void (***v22)(_DWORD, int); // ecx
  void (***v23)(_DWORD, int); // ecx
  void (***v24)(_DWORD, int); // ecx
  char result; // al
  void (***v26)(_DWORD, int); // ecx
  void (***v27)(_DWORD, _DWORD); // ecx
  void (***v28)(_DWORD, _DWORD); // ecx
  void (***v29)(_DWORD, _DWORD); // ecx
  void (***v30)(_DWORD, _DWORD); // ecx
  void (***v31)(_DWORD, _DWORD); // ecx
  void (***v32)(_DWORD, _DWORD); // ecx
  void (***v33)(_DWORD, _DWORD); // ecx
  void (***v34)(_DWORD, _DWORD); // ecx
  void (***v35)(_DWORD, _DWORD); // ecx
  void (***v36)(_DWORD, _DWORD); // ecx
  void (***v37)(_DWORD, _DWORD); // ecx
  void (***v38)(_DWORD, _DWORD); // ecx
  void (***v39)(_DWORD, _DWORD); // ecx
  void (***v40)(_DWORD, _DWORD); // ecx
  void (***v41)(_DWORD, _DWORD); // ecx
  void (***v42)(_DWORD, _DWORD); // ecx
  void (***v43)(_DWORD, _DWORD); // ecx
  void (***v44)(_DWORD, _DWORD); // ecx
  char (***v45)(_DWORD, _DWORD); // ecx

  m_pUI = (CCBUI *)this->m_pStage->m_pCBSystem->m_pUI;
  if ( a4 )
  {
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 6) )
    {
      v6 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateFace[LODWORD(this->m_fBlend) + 3];
      (**v6)(v6, 1);
      ((UIWnd *)m_pUI->m_pRoleStateFace[LODWORD(this->m_fBlend) + 3])->ScreenToClient(a2, a3);
      v7 = a2 + 24;
    }
    else
    {
      v7 = a2;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 7) )
    {
      v8 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_fBlend) + 4];
      (**v8)(v8, 1);
      ((UIWnd *)m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 8) )
    {
      v9 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_fBlend) + 4];
      (**v9)(v9, 1);
      ((UIWnd *)m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 9) )
    {
      v10 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_fBlend) + 4];
      (**v10)(v10, 1);
      ((UIWnd *)m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 12) )
    {
      v11 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_fBlend) + 4];
      (**v11)(v11, 1);
      ((UIWnd *)m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 13) )
    {
      v12 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_fBlend) + 4];
      (**v12)(v12, 1);
      ((UIWnd *)m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 10) )
    {
      v13 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_fBlend) + 4];
      (**v13)(v13, 1);
      ((UIWnd *)m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 11) )
    {
      v14 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_fBlend) + 4];
      (**v14)(v14, 1);
      ((UIWnd *)m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 14) )
    {
      v15 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_fBlend) + 4];
      (**v15)(v15, 1);
      ((UIWnd *)m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 15) )
    {
      v16 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateStable[LODWORD(this->m_fBlend) + 4];
      (**v16)(v16, 1);
      ((UIWnd *)m_pUI->m_pRoleStateStable[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 16) )
    {
      v17 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateBlank[LODWORD(this->m_fBlend) + 4];
      (**v17)(v17, 1);
      ((UIWnd *)m_pUI->m_pRoleStateBlank[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 17) )
    {
      v18 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateForbid[LODWORD(this->m_fBlend) + 4];
      (**v18)(v18, 1);
      ((UIWnd *)m_pUI->m_pRoleStateForbid[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 18) )
    {
      v19 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateSleep[LODWORD(this->m_fBlend) + 4];
      (**v19)(v19, 1);
      ((UIWnd *)m_pUI->m_pRoleStateSleep[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 19) )
    {
      v20 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateChaos[LODWORD(this->m_fBlend) + 4];
      (**v20)(v20, 1);
      ((UIWnd *)m_pUI->m_pRoleStateChaos[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 20) )
    {
      v21 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateMad[LODWORD(this->m_fBlend) + 4];
      (**v21)(v21, 1);
      ((UIWnd *)m_pUI->m_pRoleStateMad[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 21) )
    {
      v22 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateMirror[LODWORD(this->m_fBlend) + 4];
      (**v22)(v22, 1);
      ((UIWnd *)m_pUI->m_pRoleStateMirror[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 22) )
    {
      v23 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateWall[LODWORD(this->m_fBlend) + 4];
      (**v23)(v23, 1);
      ((UIWnd *)m_pUI->m_pRoleStateWall[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 23) )
    {
      v24 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateBound[LODWORD(this->m_fBlend) + 4];
      (**v24)(v24, 1);
      ((UIWnd *)m_pUI->m_pRoleStateBound[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
      v7 += 20;
    }
    result = ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 26);
    if ( result )
    {
      v26 = (void (***)(_DWORD, int))m_pUI->m_pRoleStateHermit[LODWORD(this->m_fBlend) + 4];
      (**v26)(v26, 1);
      return ((UIWnd *)m_pUI->m_pRoleStateHermit[LODWORD(this->m_fBlend) + 4])->ScreenToClient(v7, a3);
    }
  }
  else
  {
    v27 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateFace[LODWORD(this->m_fBlend) + 3];
    (**v27)(v27, 0);
    v28 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateAttackInc[LODWORD(this->m_fBlend) + 4];
    (**v28)(v28, 0);
    v29 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateAttackDec[LODWORD(this->m_fBlend) + 4];
    (**v29)(v29, 0);
    v30 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateDefenceInc[LODWORD(this->m_fBlend) + 4];
    (**v30)(v30, 0);
    v31 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateDefenceDec[LODWORD(this->m_fBlend) + 4];
    (**v31)(v31, 0);
    v32 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateLuckInc[LODWORD(this->m_fBlend) + 4];
    (**v32)(v32, 0);
    v33 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateLuckDec[LODWORD(this->m_fBlend) + 4];
    (**v33)(v33, 0);
    v34 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateSpeedInc[LODWORD(this->m_fBlend) + 4];
    (**v34)(v34, 0);
    v35 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateSpeedDec[LODWORD(this->m_fBlend) + 4];
    (**v35)(v35, 0);
    v36 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateStable[LODWORD(this->m_fBlend) + 4];
    (**v36)(v36, 0);
    v37 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateBlank[LODWORD(this->m_fBlend) + 4];
    (**v37)(v37, 0);
    v38 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateForbid[LODWORD(this->m_fBlend) + 4];
    (**v38)(v38, 0);
    v39 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateSleep[LODWORD(this->m_fBlend) + 4];
    (**v39)(v39, 0);
    v40 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateChaos[LODWORD(this->m_fBlend) + 4];
    (**v40)(v40, 0);
    v41 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateMad[LODWORD(this->m_fBlend) + 4];
    (**v41)(v41, 0);
    v42 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateMirror[LODWORD(this->m_fBlend) + 4];
    (**v42)(v42, 0);
    v43 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateWall[LODWORD(this->m_fBlend) + 4];
    (**v43)(v43, 0);
    v44 = (void (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateBound[LODWORD(this->m_fBlend) + 4];
    (**v44)(v44, 0);
    v45 = (char (***)(_DWORD, _DWORD))m_pUI->m_pRoleStateHermit[LODWORD(this->m_fBlend) + 4];
    return (**v45)(v45, 0);
  }
  return result;
}

// 0x0050BBD0
int CCBStageRole::ProcTurn()
{
  unsigned int m_fBlend_low; // eax
  CCBRoleState *m_pRoleState; // ecx
  int v5; // eax

  m_fBlend_low = LODWORD(this->m_fBlend);
  m_pRoleState = (CCBRoleState *)this->m_pRoleState;
  if ( !*(&m_pRoleState->m_Role[0].bValid + 892 * m_fBlend_low) )
  {
    if ( m_fBlend_low <= 4 )
      return 32;
    return 50;
  }
  if ( !((CCBStageRole *)m_pRoleState)->IsActive(m_fBlend_low) )
    return 50;
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleAttr(LODWORD(this->m_fBlend)) == 5 )
    return 47;
  if ( LODWORD(this->m_Task[61].fTemp2) == 4 )
    return 34;
  if ( *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_fBlend)) + 588) )
  {
    this->ClearBadPushTask(0.25);
    return 42;
  }
  else if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 17)
         || ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 14) )
  {
    return 45;
  }
  else
  {
    v5 = ((CCBRoleState *)this->m_pRoleState)->GetRoleAttr(LODWORD(this->m_fBlend)) - 4;
    if ( v5 )
    {
      if ( v5 == 1 )
        return 47;
      return 32;
    }
    else
    {
      return 46;
    }
  }
}

// 0x0050BCD0
int CCBStageRole::ProcTurnToRole(int a2)
{
  char *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  unsigned int dwCmdKind; // eax
  float *v9; // ecx
  char *v10; // eax
  char *Instance; // eax
  char *v12; // eax
  char *pad_0004; // edi
  double m_DeltaTime; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st6
  char *v19; // eax
  char *v20; // eax
  double v21; // st7
  double v22; // st7
  char *v23; // eax
  char *v24; // eax
  char *v25; // eax
  int v26; // [esp-4h] [ebp-28h]
  int v27; // [esp+0h] [ebp-24h]
  int v28; // [esp+10h] [ebp-14h]
  float v29; // [esp+10h] [ebp-14h]
  int v30; // [esp+14h] [ebp-10h]
  float v31; // [esp+14h] [ebp-10h]
  float v32; // [esp+18h] [ebp-Ch]
  float v33; // [esp+1Ch] [ebp-8h]
  int v34; // [esp+1Ch] [ebp-8h]
  int v35; // [esp+20h] [ebp-4h]

  if ( (byte_17AB794 & 1) == 0 )
  {
    byte_17AB794 |= 1u;
    dword_17AB788 = 0;
    dword_17AB78C = 0;
    dword_17AB790 = 0;
    atexit(nullsub_46);
  }
  if ( (byte_17AB794 & 2) == 0 )
  {
    byte_17AB794 |= 2u;
    dword_17AB778 = 0;
    dword_17AB77C = 0;
    dword_17AB780 = 1065353216;
    atexit(nullsub_45);
  }
  if ( (byte_17AB794 & 4) == 0 )
  {
    byte_17AB794 |= 4u;
    dword_17AB768 = 0;
    dword_17AB76C = 0;
    dword_17AB770 = 0;
    atexit(nullsub_44);
  }
  v3 = (char *)this + 96 * this->m_ThrowCmdData.dwCmdKind;
  if ( !v3[506] )
  {
    this->m_Task[62].cmd.dwCmdKind = *((_DWORD *)v3 + 108);
    this->m_Task[62].cmd.dwCmdID = *((_DWORD *)v3 + 109);
    this->m_Task[62].cmd.dwItemID = *((_DWORD *)v3 + 110);
    v4 = *(float *)&this->m_Task[62].cmd.dwCmdKind - *(float *)this->m_Task[62]._pad_0004;
    *(float *)&v28 = *(float *)&this->m_Task[62].cmd.dwCmdID - *(float *)&this->m_Task[62]._pad_0004[4];
    v5 = *(float *)&this->m_Task[62].cmd.dwItemID - *(float *)&this->m_Task[62]._pad_0004[8];
    dword_17AB78C = v28;
    *(float *)&v30 = v5;
    *(float *)&dword_17AB788 = v4;
    dword_17AB790 = v30;
    if ( ((gbVec3D *)&dword_17AB788)->Length() < 2.0 )
    {
      *(_DWORD *)this->m_Task[62]._pad_0004 = this->m_Task[62].cmd.dwCmdKind;
      *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
      *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
      *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
      return 0;
    }
    ((gbVec3D *)&dword_17AB788)->Normalize();
    v7 = acos(
           *(float *)&dword_17AB780 * *(float *)&dword_17AB790
         + *(float *)&dword_17AB77C * *(float *)&dword_17AB78C
         + *(float *)&dword_17AB778 * *(float *)&dword_17AB788);
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = v7;
    if ( *(float *)&dword_17AB788 < 0.0 )
      *(float *)&this->m_Task[62].cmd.bSrcRole[2] = 6.2831855 - v7;
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = *(float *)&this->m_Task[62].cmd.bSrcRole[2] * 57.29578;
    this->m_Task[62].cmd.nSrcRole = dword_17AB788;
    this->m_Task[62].cmd.nDestRole = dword_17AB78C;
    *(_DWORD *)&this->m_Task[62].cmd.bMultiSrcRole = dword_17AB790;
    *(float *)&this->m_Task[62].cmd.nSrcRole = *(float *)&this->m_Task[62].cmd.nSrcRole * 380.0;
    *(float *)&this->m_Task[62].cmd.nDestRole = *(float *)&this->m_Task[62].cmd.nDestRole * 380.0;
    *(float *)&this->m_Task[62].cmd.bMultiSrcRole = *(float *)&this->m_Task[62].cmd.bMultiSrcRole * 380.0;
    if ( ((CCBStageRole *)this->m_pRoleState)->IsActive(LODWORD(this->m_fBlend)) )
      this->m_Task[61].dwID = 31;
    else
      this->m_Task[61].dwID = 52;
    this->IsGrabedBy();
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 2) = 1;
    this->ClearBadPushTask(0.0099999998);
    dwCmdKind = this->m_ThrowCmdData.dwCmdKind;
    this->m_bRun = 1;
    v9 = (float *)((char *)this + 96 * dwCmdKind);
    if ( v9[108] >= -700.0 || v9[110] >= -700.0 )
    {
      if ( !LODWORD(this->m_fBlend) )
      {
        Instance = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(aWe011, 0);
      }
      if ( LODWORD(this->m_fBlend) == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !LODWORD(this->m_fBlend) )
      {
        v10 = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)v10)->AudioSetPosition(aWe011, 1);
      }
      if ( LODWORD(this->m_fBlend) == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)v12)->AudioSetPosition(aWe011b, v26);
      }
    }
  }
  pad_0004 = (char *)this->m_Task[62]._pad_0004;
  m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
  v32 = *(float *)&this->m_Task[62].cmd.nSrcRole * m_DeltaTime;
  v33 = *(float *)&this->m_Task[62].cmd.nDestRole * m_DeltaTime;
  v15 = v32 + *(float *)this->m_Task[62]._pad_0004;
  v29 = *(float *)&this->m_Task[62]._pad_0004[4] + v33;
  v16 = *(float *)&this->m_Task[62]._pad_0004[8] + m_DeltaTime * *(float *)&this->m_Task[62].cmd.bMultiSrcRole;
  *(float *)&this->m_Task[62]._pad_0004[4] = v29;
  v31 = v16;
  *(float *)this->m_Task[62]._pad_0004 = v15;
  *(float *)&this->m_Task[62]._pad_0004[8] = v31;
  v17 = *(float *)&this->m_Task[62].cmd.dwCmdKind - *(float *)this->m_Task[62]._pad_0004;
  *(float *)&v34 = *(float *)&this->m_Task[62].cmd.dwCmdID - *(float *)&this->m_Task[62]._pad_0004[4];
  v18 = *(float *)&this->m_Task[62].cmd.dwItemID - *(float *)&this->m_Task[62]._pad_0004[8];
  dword_17AB78C = v34;
  *(float *)&v35 = v18;
  *(float *)&dword_17AB788 = v17;
  dword_17AB790 = v35;
  if ( ((gbVec3D *)&dword_17AB788)->Length() >= 2.0 )
  {
    ((gbVec3D *)&dword_17AB788)->Normalize();
    v21 = acos(
            *(float *)&dword_17AB780 * *(float *)&dword_17AB790
          + *(float *)&dword_17AB77C * *(float *)&dword_17AB78C
          + *(float *)&dword_17AB778 * *(float *)&dword_17AB788);
    if ( *(float *)&dword_17AB788 < 0.0 )
      v21 = 6.2831855 - v21;
    v22 = v21 * 57.29578;
    flt_17ABCD0 = v22;
    if ( fabs(v22 - *(float *)&this->m_Task[62].cmd.bSrcRole[2]) < 1.570796370506287 )
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
        return 0;
      *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
      if ( !LODWORD(this->m_fBlend) )
      {
        v24 = (char *)CScreenMode::GetInstance();
        ((CCBStageRole *)v24)->PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_fBlend) != 4 )
      {
LABEL_43:
        this->m_bRun = 0;
        return 0;
      }
    }
    else
    {
      *(_DWORD *)pad_0004 = this->m_Task[62].cmd.dwCmdKind;
      *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
      *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
      *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
      if ( !LODWORD(this->m_fBlend) )
      {
        v23 = (char *)CScreenMode::GetInstance();
        ((CCBStageRole *)v23)->PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_fBlend) != 4 )
        goto LABEL_43;
    }
    v25 = (char *)CScreenMode::GetInstance();
    ((CCBStageRole *)v25)->PlaySound(aWe011b, v27);
    goto LABEL_43;
  }
  *(_DWORD *)pad_0004 = this->m_Task[62].cmd.dwCmdKind;
  *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
  *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
  *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
  if ( !LODWORD(this->m_fBlend) )
  {
    v19 = (char *)CScreenMode::GetInstance();
    ((CCBStageRole *)v19)->PlaySound(aWe011, v27);
  }
  if ( LODWORD(this->m_fBlend) == 4 )
  {
    v20 = (char *)CScreenMode::GetInstance();
    ((CCBStageRole *)v20)->PlaySound(aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C320
int CCBStageRole::ProcBlock(int a2)
{
  char *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  unsigned int dwCmdKind; // eax
  float *v9; // ecx
  char *v10; // eax
  char *Instance; // eax
  char *v12; // eax
  char *pad_0004; // edi
  double m_DeltaTime; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st6
  char *v19; // eax
  char *v20; // eax
  double v21; // st7
  double v22; // st7
  char *v23; // eax
  char *v24; // eax
  char *v25; // eax
  int v26; // [esp-4h] [ebp-28h]
  int v27; // [esp+0h] [ebp-24h]
  int v28; // [esp+10h] [ebp-14h]
  float v29; // [esp+10h] [ebp-14h]
  int v30; // [esp+14h] [ebp-10h]
  float v31; // [esp+14h] [ebp-10h]
  float v32; // [esp+18h] [ebp-Ch]
  float v33; // [esp+1Ch] [ebp-8h]
  int v34; // [esp+1Ch] [ebp-8h]
  int v35; // [esp+20h] [ebp-4h]

  if ( (byte_17AB764 & 1) == 0 )
  {
    byte_17AB764 |= 1u;
    dword_17AB758 = 0;
    dword_17AB75C = 0;
    dword_17AB760 = 0;
    atexit(nullsub_49);
  }
  if ( (byte_17AB764 & 2) == 0 )
  {
    byte_17AB764 |= 2u;
    dword_17AB748 = 0;
    dword_17AB74C = 0;
    dword_17AB750 = 1065353216;
    atexit(nullsub_48);
  }
  if ( (byte_17AB764 & 4) == 0 )
  {
    byte_17AB764 |= 4u;
    dword_17AB738 = 0;
    dword_17AB73C = 0;
    dword_17AB740 = 0;
    atexit(nullsub_47);
  }
  v3 = (char *)this + 96 * this->m_ThrowCmdData.dwCmdKind;
  if ( !v3[506] )
  {
    this->m_Task[62].cmd.dwCmdKind = *((_DWORD *)v3 + 108);
    this->m_Task[62].cmd.dwCmdID = *((_DWORD *)v3 + 109);
    this->m_Task[62].cmd.dwItemID = *((_DWORD *)v3 + 110);
    v4 = *(float *)&this->m_Task[62].cmd.dwCmdKind - *(float *)this->m_Task[62]._pad_0004;
    *(float *)&v28 = *(float *)&this->m_Task[62].cmd.dwCmdID - *(float *)&this->m_Task[62]._pad_0004[4];
    v5 = *(float *)&this->m_Task[62].cmd.dwItemID - *(float *)&this->m_Task[62]._pad_0004[8];
    dword_17AB75C = v28;
    *(float *)&v30 = v5;
    *(float *)&dword_17AB758 = v4;
    dword_17AB760 = v30;
    if ( ((gbVec3D *)&dword_17AB758)->Length() < 2.0 )
    {
      *(_DWORD *)this->m_Task[62]._pad_0004 = this->m_Task[62].cmd.dwCmdKind;
      *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
      *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
      *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
      return 0;
    }
    ((gbVec3D *)&dword_17AB758)->Normalize();
    v7 = acos(
           *(float *)&dword_17AB750 * *(float *)&dword_17AB760
         + *(float *)&dword_17AB74C * *(float *)&dword_17AB75C
         + *(float *)&dword_17AB748 * *(float *)&dword_17AB758);
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = v7;
    if ( *(float *)&dword_17AB758 < 0.0 )
      *(float *)&this->m_Task[62].cmd.bSrcRole[2] = 6.2831855 - v7;
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = *(float *)&this->m_Task[62].cmd.bSrcRole[2] * 57.29578;
    this->m_Task[62].cmd.nSrcRole = dword_17AB758;
    this->m_Task[62].cmd.nDestRole = dword_17AB75C;
    *(_DWORD *)&this->m_Task[62].cmd.bMultiSrcRole = dword_17AB760;
    *(float *)&this->m_Task[62].cmd.nSrcRole = *(float *)&this->m_Task[62].cmd.nSrcRole * 570.0;
    *(float *)&this->m_Task[62].cmd.nDestRole = *(float *)&this->m_Task[62].cmd.nDestRole * 570.0;
    *(float *)&this->m_Task[62].cmd.bMultiSrcRole = *(float *)&this->m_Task[62].cmd.bMultiSrcRole * 570.0;
    if ( ((CCBStageRole *)this->m_pRoleState)->IsActive(LODWORD(this->m_fBlend)) )
      this->m_Task[61].dwID = 31;
    else
      this->m_Task[61].dwID = 52;
    this->IsGrabedBy();
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 2) = 1;
    this->ClearBadPushTask(0.0099999998);
    dwCmdKind = this->m_ThrowCmdData.dwCmdKind;
    this->m_bRun = 1;
    v9 = (float *)((char *)this + 96 * dwCmdKind);
    if ( v9[108] >= -700.0 || v9[110] >= -700.0 )
    {
      if ( !LODWORD(this->m_fBlend) )
      {
        Instance = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(aWe011, 0);
      }
      if ( LODWORD(this->m_fBlend) == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !LODWORD(this->m_fBlend) )
      {
        v10 = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)v10)->AudioSetPosition(aWe011, 1);
      }
      if ( LODWORD(this->m_fBlend) == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = (char *)CScreenMode::GetInstance();
        ((CScreenMode *)v12)->AudioSetPosition(aWe011b, v26);
      }
    }
  }
  pad_0004 = (char *)this->m_Task[62]._pad_0004;
  m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
  v32 = *(float *)&this->m_Task[62].cmd.nSrcRole * m_DeltaTime;
  v33 = *(float *)&this->m_Task[62].cmd.nDestRole * m_DeltaTime;
  v15 = v32 + *(float *)this->m_Task[62]._pad_0004;
  v29 = *(float *)&this->m_Task[62]._pad_0004[4] + v33;
  v16 = *(float *)&this->m_Task[62]._pad_0004[8] + m_DeltaTime * *(float *)&this->m_Task[62].cmd.bMultiSrcRole;
  *(float *)&this->m_Task[62]._pad_0004[4] = v29;
  v31 = v16;
  *(float *)this->m_Task[62]._pad_0004 = v15;
  *(float *)&this->m_Task[62]._pad_0004[8] = v31;
  v17 = *(float *)&this->m_Task[62].cmd.dwCmdKind - *(float *)this->m_Task[62]._pad_0004;
  *(float *)&v34 = *(float *)&this->m_Task[62].cmd.dwCmdID - *(float *)&this->m_Task[62]._pad_0004[4];
  v18 = *(float *)&this->m_Task[62].cmd.dwItemID - *(float *)&this->m_Task[62]._pad_0004[8];
  dword_17AB75C = v34;
  *(float *)&v35 = v18;
  *(float *)&dword_17AB758 = v17;
  dword_17AB760 = v35;
  if ( ((gbVec3D *)&dword_17AB758)->Length() >= 2.0 )
  {
    ((gbVec3D *)&dword_17AB758)->Normalize();
    v21 = acos(
            *(float *)&dword_17AB750 * *(float *)&dword_17AB760
          + *(float *)&dword_17AB74C * *(float *)&dword_17AB75C
          + *(float *)&dword_17AB748 * *(float *)&dword_17AB758);
    if ( *(float *)&dword_17AB758 < 0.0 )
      v21 = 6.2831855 - v21;
    v22 = v21 * 57.29578;
    flt_17ABCD4 = v22;
    if ( fabs(v22 - *(float *)&this->m_Task[62].cmd.bSrcRole[2]) < 1.570796370506287 )
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
        return 0;
      *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
      if ( !LODWORD(this->m_fBlend) )
      {
        v24 = (char *)CScreenMode::GetInstance();
        ((CCBStageRole *)v24)->PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_fBlend) != 4 )
      {
LABEL_43:
        this->m_bRun = 0;
        return 0;
      }
    }
    else
    {
      *(_DWORD *)pad_0004 = this->m_Task[62].cmd.dwCmdKind;
      *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
      *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
      *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
      if ( !LODWORD(this->m_fBlend) )
      {
        v23 = (char *)CScreenMode::GetInstance();
        ((CCBStageRole *)v23)->PlaySound(aWe011, v27);
      }
      if ( LODWORD(this->m_fBlend) != 4 )
        goto LABEL_43;
    }
    v25 = (char *)CScreenMode::GetInstance();
    ((CCBStageRole *)v25)->PlaySound(aWe011b, v27);
    goto LABEL_43;
  }
  *(_DWORD *)pad_0004 = this->m_Task[62].cmd.dwCmdKind;
  *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
  *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
  *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
  if ( !LODWORD(this->m_fBlend) )
  {
    v19 = (char *)CScreenMode::GetInstance();
    ((CCBStageRole *)v19)->PlaySound(aWe011, v27);
  }
  if ( LODWORD(this->m_fBlend) == 4 )
  {
    v20 = (char *)CScreenMode::GetInstance();
    ((CCBStageRole *)v20)->PlaySound(aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C970
int CCBStageRole::ProcMagic(int a2)
{
  char *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  unsigned int v8; // ecx
  char *Instance; // eax
  double v10; // st7
  char *v11; // ecx
  double v12; // st7
  double v13; // st7
  char *v14; // eax
  char *v15; // eax
  int a4; // [esp+0h] [ebp-28h]
  int v17; // [esp+Ch] [ebp-1Ch]
  float v18; // [esp+14h] [ebp-14h]
  float v19; // [esp+18h] [ebp-10h]
  int v20; // [esp+20h] [ebp-8h]
  int v21; // [esp+24h] [ebp-4h]

  if ( (byte_17AB734 & 1) == 0 )
  {
    byte_17AB734 |= 1u;
    dword_17AB728 = 0;
    dword_17AB72C = 0;
    dword_17AB730 = 0;
    atexit(nullsub_51);
  }
  if ( (byte_17AB734 & 2) == 0 )
  {
    byte_17AB734 |= 2u;
    dword_17AB718 = 0;
    dword_17AB71C = 0;
    dword_17AB720 = 1065353216;
    atexit(nullsub_50);
  }
  v19 = 1.0;
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_fBlend), 23) )
    v19 = 0.44;
  v3 = (char *)this + 96 * this->m_ThrowCmdData.dwCmdKind;
  if ( !v3[506] )
  {
    this->m_Task[62].cmd.dwCmdKind = *((_DWORD *)v3 + 108);
    this->m_Task[62].cmd.dwCmdID = *((_DWORD *)v3 + 109);
    this->m_Task[62].cmd.dwItemID = *((_DWORD *)v3 + 110);
    v4 = *(float *)&this->m_Task[62].cmd.dwCmdKind - *(float *)this->m_Task[62]._pad_0004;
    *(float *)&v20 = *(float *)&this->m_Task[62].cmd.dwCmdID - *(float *)&this->m_Task[62]._pad_0004[4];
    v5 = *(float *)&this->m_Task[62].cmd.dwItemID - *(float *)&this->m_Task[62]._pad_0004[8];
    dword_17AB72C = v20;
    *(float *)&v21 = v5;
    *(float *)&dword_17AB728 = v4;
    dword_17AB730 = v21;
    if ( ((gbVec3D *)&dword_17AB728)->Length() < 2.0 )
    {
      this->ClearAniMsg(0, 1.0);
      *(_DWORD *)this->m_Task[62]._pad_0004 = this->m_Task[62].cmd.dwCmdKind;
      *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
      *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
      *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
      return 0;
    }
    ((gbVec3D *)&dword_17AB728)->Normalize();
    v7 = acos(
           *(float *)&dword_17AB720 * *(float *)&dword_17AB730
         + *(float *)&dword_17AB71C * *(float *)&dword_17AB72C
         + *(float *)&dword_17AB718 * *(float *)&dword_17AB728);
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = v7;
    if ( *(float *)&dword_17AB728 < 0.0 )
      *(float *)&this->m_Task[62].cmd.bSrcRole[2] = 6.2831855 - v7;
    v8 = 96 * this->m_ThrowCmdData.dwCmdKind;
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = *(float *)&this->m_Task[62].cmd.bSrcRole[2] * 57.29578;
    *((_BYTE *)&this->m_OBBox.trans.tw + v8 + 2) = 1;
    *((_DWORD *)&this->m_OBBox.trans.zw + 24 * this->m_ThrowCmdData.dwCmdKind) = 1065353216;
    this->m_Task[61].dwID = 32;
    this->IsGrabedBy();
    *(float *)&a4 = *(float *)&this->m_Task[62]._pad_0004[4] - 20.0;
    if ( LODWORD(this->m_fBlend) )
      ((CEffMgr *)this->m_pStage->m_pCBSystem->m_pEffMgr)->Init(221, *(_DWORD *)this->m_Task[62]._pad_0004, a4, *(_DWORD *)&this->m_Task[62]._pad_0004[8], 0);
    else
      ((CEffMgr *)this->m_pStage->m_pCBSystem->m_pEffMgr)->Init(222, *(_DWORD *)this->m_Task[62]._pad_0004, a4, *(_DWORD *)&this->m_Task[62]._pad_0004[8], 0);
    this->ClearBadPushTask(0.0099999998);
    Instance = (char *)CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(aWe014, 1);
  }
  v10 = this->PushBackAllTask();
  v11 = (char *)this + 96 * this->m_ThrowCmdData.dwCmdKind;
  if ( *((float *)v11 + 122) <= 0.0 )
  {
    v13 = this->m_pStage->m_pCBSystem->m_DeltaTime * 2.5 + v10;
    v18 = v13;
    if ( v13 >= v19 )
    {
      v18 = v19;
      v11[505] = 1;
      v14 = (char *)CScreenMode::GetInstance();
      ((CCBStageRole *)v14)->PlaySound(aWe014, v17);
    }
  }
  else
  {
    v12 = v10 - this->m_pStage->m_pCBSystem->m_DeltaTime * 2.5;
    v18 = v12;
    if ( v12 < 0.0 )
    {
      *((_DWORD *)v11 + 122) = -1054867456;
      *(_DWORD *)this->m_Task[62]._pad_0004 = this->m_Task[62].cmd.dwCmdKind;
      *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
      *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
      *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[2] = *(_DWORD *)&this->m_Task[62].cmd.bSrcRole[6];
    }
  }
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
  {
    v18 = v19;
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
    v15 = (char *)CScreenMode::GetInstance();
    ((CCBStageRole *)v15)->PlaySound(aWe014, v17);
  }
  if ( v18 < 1.0 )
    this->ClearAniMsg(1, v18);
  else
    this->ClearAniMsg(0, 1.0);
  return 0;
}

// 0x0050CDE0
int CCBStageRole::ProcUseRecoverItem(float a2)
{
  char *v3; // eax
  unsigned int v4; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  long double v9; // st7
  double v10; // st7
  float v11; // edi
  float m_fBlend; // eax
  char *Instance; // eax
  char *v14; // eax
  double v15; // st7
  double v16; // st6
  double m_DeltaTime; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  float v21; // eax
  char *v22; // eax
  char *v23; // eax
  float v24; // eax
  char *v25; // eax
  char *v26; // eax
  int v27; // [esp+0h] [ebp-18h]
  float v28; // [esp+Ch] [ebp-Ch]
  int v29; // [esp+10h] [ebp-8h]
  int v30; // [esp+10h] [ebp-8h]
  float v31; // [esp+10h] [ebp-8h]
  int v32; // [esp+14h] [ebp-4h]
  int v33; // [esp+14h] [ebp-4h]
  float a2a; // [esp+1Ch] [ebp+4h]

  if ( (byte_17AB714 & 1) == 0 )
  {
    byte_17AB714 |= 1u;
    dword_17AB708 = 0;
    dword_17AB70C = 0;
    dword_17AB710 = 0;
    atexit(nullsub_54);
  }
  if ( (byte_17AB714 & 2) == 0 )
  {
    byte_17AB714 |= 2u;
    dword_17AB6F8 = 0;
    dword_17AB6FC = 0;
    dword_17AB700 = 1065353216;
    atexit(nullsub_53);
  }
  if ( (byte_17AB714 & 4) == 0 )
  {
    byte_17AB714 |= 4u;
    dword_17AB6E8 = 0;
    dword_17AB6EC = 0;
    dword_17AB6F0 = 0;
    atexit(nullsub_52);
  }
  v3 = (char *)this + 96 * this->m_ThrowCmdData.dwCmdKind;
  if ( v3[506] )
  {
    v11 = a2;
  }
  else
  {
    *((_DWORD *)v3 + 122) = -1054867456;
    v4 = 96 * this->m_ThrowCmdData.dwCmdKind;
    this->m_Task[62].cmd.dwCmdKind = *(_DWORD *)&this->m_ThrowCmdData.bDestRole[v4 + 3];
    this->m_Task[62].cmd.dwCmdID = *(_DWORD *)&this->m_ThrowCmdData.bDestRole[v4 + 7];
    this->m_Task[62].cmd.dwItemID = *(_DWORD *)&this->m_ThrowCmdData.bDestRole[v4 + 11];
    v5 = *(float *)&this->m_Task[62].cmd.dwCmdKind - *(float *)this->m_Task[62]._pad_0004;
    *(float *)&v29 = *(float *)&this->m_Task[62].cmd.dwCmdID - *(float *)&this->m_Task[62]._pad_0004[4];
    v6 = *(float *)&this->m_Task[62].cmd.dwItemID - *(float *)&this->m_Task[62]._pad_0004[8];
    dword_17AB70C = v29;
    *(float *)&v32 = v6;
    *(float *)&dword_17AB708 = v5;
    dword_17AB710 = v32;
    v7 = ((gbVec3D *)&dword_17AB708)->Length();
    a2a = v7;
    if ( v7 < 2.0 )
    {
      *(_DWORD *)this->m_Task[62]._pad_0004 = this->m_Task[62].cmd.dwCmdKind;
      *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
      *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
      *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
      return 0;
    }
    ((gbVec3D *)&dword_17AB708)->Normalize();
    v9 = acos(
           *(float *)&dword_17AB700 * *(float *)&dword_17AB710
         + *(float *)&dword_17AB6FC * *(float *)&dword_17AB70C
         + *(float *)&dword_17AB6F8 * *(float *)&dword_17AB708);
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = v9;
    if ( *(float *)&dword_17AB708 < 0.0 )
      *(float *)&this->m_Task[62].cmd.bSrcRole[2] = 6.2831855 - v9;
    *(float *)&this->m_Task[62].cmd.bSrcRole[2] = *(float *)&this->m_Task[62].cmd.bSrcRole[2] * 57.29578;
    this->m_Task[62].cmd.nSrcRole = dword_17AB708;
    v10 = a2a + a2a;
    this->m_Task[62].cmd.nDestRole = dword_17AB70C;
    *(_DWORD *)&this->m_Task[62].cmd.bMultiSrcRole = dword_17AB710;
    *(float *)&this->m_Task[62].cmd.nSrcRole = v10 * *(float *)&this->m_Task[62].cmd.nSrcRole;
    *(float *)&this->m_Task[62].cmd.nDestRole = v10 * *(float *)&this->m_Task[62].cmd.nDestRole;
    *(float *)&this->m_Task[62].cmd.bMultiSrcRole = v10 * *(float *)&this->m_Task[62].cmd.bMultiSrcRole;
    if ( ((CCBStageRole *)this->m_pRoleState)->IsActive(LODWORD(this->m_fBlend)) )
      this->m_Task[61].dwID = 31;
    else
      this->m_Task[61].dwID = 52;
    this->IsGrabedBy();
    v11 = 0.0;
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 2) = 1;
    this->ClearBadPushTask(0.0099999998);
    m_fBlend = this->m_fBlend;
    this->m_bRun = 1;
    if ( LODWORD(m_fBlend) == 1 )
    {
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(aWe012, 1);
    }
    if ( LODWORD(this->m_fBlend) == 3 )
    {
      v14 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v14)->AudioSetPosition(aWe013, 1);
    }
  }
  v15 = *(float *)&this->m_Task[62].cmd.dwCmdKind - *(float *)this->m_Task[62]._pad_0004;
  *(float *)&v30 = *(float *)&this->m_Task[62].cmd.dwCmdID - *(float *)&this->m_Task[62]._pad_0004[4];
  v16 = *(float *)&this->m_Task[62].cmd.dwItemID - *(float *)&this->m_Task[62]._pad_0004[8];
  dword_17AB70C = v30;
  *(float *)&v33 = v16;
  *(float *)&dword_17AB708 = v15;
  dword_17AB710 = v33;
  if ( LODWORD(v11) == this->m_Task[62].dwID )
    *((_DWORD *)&this->m_OBBox.trans.zw + 24 * this->m_ThrowCmdData.dwCmdKind) = 1120403456;
  if ( *(&this->m_OBBox.trans.zw + 24 * this->m_ThrowCmdData.dwCmdKind) > 0.0
    && ((gbVec3D *)&dword_17AB708)->Length() > 2.0 )
  {
    m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
    v28 = *(float *)&this->m_Task[62].cmd.nSrcRole * m_DeltaTime;
    v31 = *(float *)&this->m_Task[62].cmd.nDestRole * m_DeltaTime;
    v18 = m_DeltaTime * *(float *)&this->m_Task[62].cmd.bMultiSrcRole;
    *(float *)this->m_Task[62]._pad_0004 = v28 + *(float *)this->m_Task[62]._pad_0004;
    *(float *)&this->m_Task[62]._pad_0004[4] = v31 + *(float *)&this->m_Task[62]._pad_0004[4];
    *(float *)&this->m_Task[62]._pad_0004[8] = v18 + *(float *)&this->m_Task[62]._pad_0004[8];
  }
  if ( LODWORD(v11) == *(_DWORD *)this->m_Task[62].eMode && ((gbVec3D *)&dword_17AB708)->Length() <= 2.0 )
    *((_DWORD *)&this->m_OBBox.trans.zw + 24 * this->m_ThrowCmdData.dwCmdKind) = -1054867456;
  ((gbVec3D *)&dword_17AB708)->Normalize();
  v19 = acos(
          *(float *)&dword_17AB700 * *(float *)&dword_17AB710
        + *(float *)&dword_17AB6FC * *(float *)&dword_17AB70C
        + *(float *)&dword_17AB6F8 * *(float *)&dword_17AB708);
  if ( *(float *)&dword_17AB708 < 0.0 )
    v19 = 6.2831855 - v19;
  v20 = v19 * 57.29578;
  flt_17ABCD8 = v20;
  if ( fabs(v20 - *(float *)&this->m_Task[62].cmd.bSrcRole[2]) >= 1.570796370506287 )
  {
    *(_DWORD *)this->m_Task[62]._pad_0004 = this->m_Task[62].cmd.dwCmdKind;
    *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
    *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
    *((_DWORD *)&this->m_OBBox.trans.zw + 24 * this->m_ThrowCmdData.dwCmdKind) = -1054867456;
  }
  if ( LODWORD(v11) == *(_DWORD *)&this->m_Task[62].cmd.bDestRole[3] )
  {
    *(_DWORD *)this->m_Task[62]._pad_0004 = this->m_Task[62].cmd.dwCmdKind;
    *(_DWORD *)&this->m_Task[62]._pad_0004[4] = this->m_Task[62].cmd.dwCmdID;
    *(_DWORD *)&this->m_Task[62]._pad_0004[8] = this->m_Task[62].cmd.dwItemID;
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
    v21 = this->m_fBlend;
    this->m_bRun = 0;
    if ( LODWORD(v21) == 1 )
    {
      v22 = (char *)CScreenMode::GetInstance();
      ((CCBStageRole *)v22)->PlaySound(aWe012, v27);
    }
    if ( LODWORD(this->m_fBlend) == 3 )
    {
      v23 = (char *)CScreenMode::GetInstance();
      ((CCBStageRole *)v23)->PlaySound(aWe013, v27);
    }
  }
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_fBlend)) )
  {
    *((_BYTE *)&this->m_OBBox.trans.tw + 96 * this->m_ThrowCmdData.dwCmdKind + 1) = 1;
    v24 = this->m_fBlend;
    this->m_bRun = 0;
    if ( LODWORD(v24) == 1 )
    {
      v25 = (char *)CScreenMode::GetInstance();
      ((CCBStageRole *)v25)->PlaySound(aWe012, v27);
    }
    if ( LODWORD(this->m_fBlend) == 3 )
    {
      v26 = (char *)CScreenMode::GetInstance();
      ((CCBStageRole *)v26)->PlaySound(aWe013, v27);
    }
  }
  return 0;
}

// 0x0053E310
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void CCBStageRole::PlaySound(char *name, int a3)
{
  unsigned int v4; // ebp
  unsigned int v5; // kr08_4
  unsigned int v6; // ebp
  gbSound2DNode **i; // esi
  gbSound2DNode **j; // edi
  char v9; // al
  int v10; // [esp+4h] [ebp-20h] BYREF
  char *v11; // [esp+8h] [ebp-1Ch]
  unsigned int v12; // [esp+Ch] [ebp-18h]
  int v13; // [esp+14h] [ebp-10h]
  int v14; // [esp+20h] [ebp-4h]

  if ( (g_nGameFlags & 1) != 0 )
  {
    LOBYTE(v10) = (_BYTE)name;
    ((std *)&v10)->string::_Tidy(0);
    v14 = 0;
    v4 = strlen(&g_SceneMgr._gap_c93c[76]);
    if ( ((SceneObj *)&v10)->Update(v4) )
    {
      qmemcpy(v11, &g_SceneMgr._gap_c93c[76], v4);
      ((std *)&v10)->string::_Eos(v4);
    }
    v13 = 0;
    v5 = strlen(name) + 1;
    v6 = v5 - 1;
    v14 = 1;
    if ( ((SceneObj *)&v10)->Update(v5 - 1) )
    {
      qmemcpy(v11, name, v6);
      v12 = v5 - 1;
      v11[v6] = 0;
    }
    for ( i = *(gbSound2DNode ***)&this->m_Task[1].bValid; i != this->m_Task[2].fp; i += 5 )
    {
      for ( j = (gbSound2DNode **)this->m_Task[2].fp; i != j; i += 5 )
      {
        if ( sub_53DF80((int)i, (int)&v10) )
          break;
      }
      if ( i == this->m_Task[2].fp )
        break;
      if ( ((gbSound2DNode *)i[4])->IsPlaying() )
      {
        ((gbSound2DNode *)i[4])->Stop();
        break;
      }
    }
    if ( v11 )
    {
      v9 = *(v11 - 1);
      if ( !v9 || v9 == -1 )
        operator delete(v11 - 1);
      else
        *(v11 - 1) = v9 - 1;
    }
  }
}
