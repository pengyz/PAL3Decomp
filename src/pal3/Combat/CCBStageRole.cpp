#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageRole.h"

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
extern int dword_17A990C;
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
  return this->m_pStage[892 * index + 579];
}

// 0x00508930
CCBStageRole::~CCBStageRole(int a2, int a3, _DWORD *a4)
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

  v5 = this->m_Task[10].cmd.bSrcRole[15 * a2 + 8];
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
      return 0;
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
        CEffect::Render(*(CEffect **)(**(_DWORD **)this->m_sLastRole + 48), *((_DWORD *)v6 + 612));
      if ( *a4 == 270 )
        CEffect::Render(*(CEffect **)(**(_DWORD **)this->m_sLastRole + 44), *((_DWORD *)v6 + 612));
      if ( *a4 == 269 )
        return CEffMgr::Init(
                 *(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 48),
                 *((_DWORD *)v6 + 612),
                 SLODWORD(v30),
                 v31,
                 a5,
                 0);
      else
        return CEffMgr::Init(
                 *(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 44),
                 *((_DWORD *)v6 + 612),
                 SLODWORD(v30),
                 v31,
                 a5,
                 0);
    }
  }
  else if ( *((_DWORD *)v6 + 619) == -1 )
  {
    return 0;
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
      CEffect::Render(*(CEffect **)(**(_DWORD **)this->m_sLastRole + 48), *((_DWORD *)v6 + 619));
    if ( *a4 == 270 )
      CEffect::Render(*(CEffect **)(**(_DWORD **)this->m_sLastRole + 44), *((_DWORD *)v6 + 619));
    if ( *a4 == 269 )
      return CEffMgr::Init(
               *(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 48),
               *((_DWORD *)v6 + 619),
               SLODWORD(v30),
               v31,
               a5,
               0);
    else
      return CEffMgr::Init(
               *(CEffMgr **)(**(_DWORD **)this->m_sLastRole + 44),
               *((_DWORD *)v6 + 619),
               SLODWORD(v30),
               v31,
               a5,
               0);
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
  char *v3; // ebp
  char *v4; // edi
  int v5; // ecx
  int v7; // [esp+10h] [ebp-4h]

  (gbMatrix4 *->gbMatrix4()&this->m_pStage[296]);
  v3 = (char *)&this->m_pStage[444];
  v7 = 64;
  do
  {
    (gbVec3D *->gbVec3D()(v3 - 12), 0.0, 0.0, 0.0);
    v4 = v3;
    v3 += 96;
    memset(v4, 0, 0x2Cu);
    --v7;
  }
  while ( v7 );
  *(_DWORD *)&this->m_pStage[6572] = 0;
  *(_DWORD *)&this->m_pStage[6576] = 0;
  *(_DWORD *)&this->m_pStage[6580] = 0;
  *(_DWORD *)&this->m_pStage[6584] = 0;
  *(_DWORD *)&this->m_pStage[6588] = 0;
  *(_DWORD *)&this->m_pStage[6592] = 0;
  *(_DWORD *)&this->m_pStage[6596] = 0;
  *(_DWORD *)&this->m_pStage[6600] = 0;
  *(_DWORD *)&this->m_pStage[6604] = 0;
  *(_DWORD *)&this->m_pStage[6608] = 0;
  *(_DWORD *)&this->m_pStage[6612] = 0;
  *(_DWORD *)&this->m_pStage[6616] = 0;
  *(_DWORD *)&this->m_pStage[6620] = 0;
  *(_DWORD *)&this->m_pStage[6624] = 0;
  *(_DWORD *)&this->m_pStage[6628] = 0;
  memset(this, 0, 0x1A18u);
  *(_DWORD *)this->m_pStage = a2;
  v5 = *(_DWORD *)(*(_DWORD *)a2 + 16);
  *(_DWORD *)&this->m_pStage[6640] = 0;
  *(_DWORD *)&this->m_pStage[4] = v5;
  *(_DWORD *)&this->m_pStage[6644] = gbCrc32Compute(aOver);
  *(_DWORD *)&this->m_pStage[6648] = gbCrc32Compute(aWork);
  *(_DWORD *)&this->m_pStage[6652] = gbCrc32Compute(aWork1);
  *(_DWORD *)&this->m_pStage[6656] = gbCrc32Compute(aPause);
  *(_DWORD *)&this->m_pStage[6660] = gbCrc32Compute(aStore);
  *(_DWORD *)&this->m_pStage[6664] = gbCrc32Compute(aFlyup);
  *(_DWORD *)&this->m_pStage[6668] = gbCrc32Compute(aFlydown);
  *(_DWORD *)&this->m_pStage[6672] = 0;
  strcpy(&this->m_pStage[8], "???");
  return this->m_pStage;
}

// 0x00509410
int CCBStageRole::GetRotAngle(int _this)
{
  int v3; // ebp
  _DWORD *v4; // ecx

  v3 = this + 400;
  *(_DWORD *)(this + 400) = 0;
  *(_DWORD *)(this + 404) = 0;
  v4 = (_DWORD *)(this + 6572);
  *(_BYTE *)(this + 264) = 0;
  *(_BYTE *)(this + 265) = 0;
  *(_DWORD *)(v3 + 8) = 0;
  *(_BYTE *)(this + 266) = 0;
  *(_BYTE *)(this + 267) = 0;
  *(_DWORD *)(this + 268) = 1065353216;
  *(_BYTE *)(this + 272) = 0;
  *(_BYTE *)(this + 273) = 0;
  *(_BYTE *)(this + 280) = 0;
  *(_BYTE *)(this + 274) = 0;
  *(_BYTE *)(this + 380) = 0;
  *(_DWORD *)(this + 384) = 0;
  *(_DWORD *)(this + 388) = 0;
  *(_DWORD *)(this + 284) = 0;
  *(_DWORD *)(this + 6632) = 0;
  *(_DWORD *)(this + 6636) = 0;
  *(_DWORD *)(this + 6564) = 2;
  *(_DWORD *)(this + 6568) = 32;
  *(_DWORD *)(this + 392) = 0;
  *(_DWORD *)(this + 396) = -1;
  *(_DWORD *)(v3 + 12) = -1;
  *(_BYTE *)(this + 373) = 0;
  *(_BYTE *)(this + 374) = 0;
  *(_DWORD *)(this + 376) = 0;
  *(_DWORD *)(this + 6560) = 1;
  *v4 = 0;
  v4[1] = 0;
  v4[2] = 0;
  *(_DWORD *)(this + 6584) = 0;
  *(_DWORD *)(this + 6588) = 0;
  *(_DWORD *)(this + 6592) = 0;
  *(_DWORD *)(this + 6596) = 0;
  *(_DWORD *)(this + 6600) = 0;
  *(_DWORD *)(this + 6604) = 0;
  *(_DWORD *)(this + 6608) = 0;
  *(_DWORD *)(this + 6612) = 0;
  *(_DWORD *)(this + 6616) = 0;
  *(_DWORD *)(this + 6620) = 0;
  *(_DWORD *)(this + 6624) = 0;
  *(_DWORD *)(this + 6628) = 0;
  memset((void *)(this + 416), 0, 0x1800u);
  *(_DWORD *)(this + 6640) = 0;
  return 0;
}

// 0x00509540
char CCBStageRole::IsIdle(int _this, unsigned int a2)
{
  int v3; // eax
  int v4; // eax
  char Buffer[260]; // [esp+8h] [ebp-910h] BYREF
  char pExceptionObject[1024]; // [esp+10Ch] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+50Ch] [ebp-40Ch] BYREF
  int v9; // [esp+914h] [ebp-4h]

  v3 = operator new(0x224u);
  v9 = 0;
  if ( v3 )
    v4 = v3->FastInit();
  else
    v4 = 0;
  v9 = -1;
  *(_DWORD *)(this + 292) = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      (Logger *->FormatException()ArgList, aCNewFailed_0, aDProjectPal3Co_8, 120),
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
    Actor::LoadModel(*(Actor **)(this + 292));
    (CCBStageRole *->ProcCatchED()this);
  }
  *(_BYTE *)(this + 274) = 0;
  return 1;
}

// 0x00509690
char CCBStageRole::IsAtInitPos()
{
  Actor *m_bFlash; // ecx
  void *v3; // edi

  m_bFlash = (Actor *)this->m_bFlash;
  if ( !m_bFlash )
    return 1;
  m_bFlash->UpdateAllActions();
  v3 = (void *)this->m_bFlash;
  if ( v3 )
  {
    sub_40EE00(this->m_bFlash);
    operator delete(v3);
  }
  this->m_bFlash = 0;
  return 1;
}

// 0x005096D0
char CCBStageRole::IsAtProtectPos(int a2, int a3, int a4)
{
  int inited; // eax
  __int32 m_bAlive; // eax
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
  int v17; // eax
  CCBStage *v18; // eax
  CCBRoleState *v19; // ecx
  CCBStageScene *v20; // esi
  __int32 v21; // eax
  char v22; // dl
  unsigned __int32 v23; // eax
  const char *v25; // [esp-8h] [ebp-11Ch]
  float x; // [esp+Ch] [ebp-108h]
  char Buffer[260]; // [esp+10h] [ebp-104h] BYREF

  CCBStageRole::GetRotAngle((int)this);
  this->m_bAlive = a2;
  this->m_bRun = a3;
  LOBYTE(this->m_bValid) = 1;
  BYTE1(this->m_bValid) = 1;
  LOBYTE(this->m_bPaused) = 1;
  this->m_Task[36].fp = 0;
  if ( a2 >= 5 && a2 < 11 )
  {
    if ( strcmp((const char *)(this->m_pRoleState->InitUI(a2) + 8), this->m_sLastRole) )
    {
      v25 = (const char *)(this->m_pRoleState->InitUI(a2) + 8);
      inited = this->m_pRoleState->InitUI(a2);
      sprintf(Buffer, "role\\%s\\%s.ini", (const char *)(inited + 8), v25);
      m_bAlive = this->m_bAlive;
      if ( m_bAlive < 5 || m_bAlive >= 11 || (int)g_pVFileSys->FileExistNum(Buffer) > 0 )
      {
        this->m_pRoleState->InitUI(a2);
        (Actor *->LoadModel()this->m_bFlash);
        v11 = (const char *)(this->m_pRoleState->InitUI(a2) + 8);
        v12 = strlen(v11) + 1;
        v13 = (const char *)&v11[v12];
        qmemcpy(this->m_sLastRole, &v13[-v12], 4 * (v12 >> 2));
        v9 = (char *)&v13[4 * (v12 >> 2) - v12];
        v8 = (char *)&this->m_sLastRole[4 * (v12 >> 2)];
        v10 = v12;
      }
      else
      {
        (Actor *->LoadModel()this->m_bFlash);
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
  if ( (CCBStageRole *->IsActive()this->m_pRoleState, a2) )
    this->m_Task[35].cmd.bDestRole[3] = 32;
  else
    this->m_Task[35].cmd.bDestRole[3] = 50;
  CCBStageRole::IsGrabedBy((int)this);
  if ( (CCBStageRole *->IsActive()this->m_pRoleState, a2) == 1 )
  {
    m_pStage = (CCBStage *)this->m_pStage;
    m_pRoleState = (CCBRoleState *)this->m_pRoleState;
    this->m_Task[36].vec1.x = 45.0;
    m_pScene = (CCBStageScene *)m_pStage->m_pScene;
    v17 = (int)&m_pScene->m_vecFiveLineup[m_pRoleState->IsAllWeDead(a2)];
  }
  else
  {
    v18 = (CCBStage *)this->m_pStage;
    v19 = (CCBRoleState *)this->m_pRoleState;
    this->m_Task[36].vec1.x = -135.0;
    v20 = (CCBStageScene *)v18->m_pScene;
    v17 = (int)&v20->m_vecEnemyLineup[v19->IsAllWeDead(a2)];
  }
  this->m_Task[35].cmd.bDestRole[10] = *(_DWORD *)v17;
  this->m_Task[35].cmd.bValid = *(_DWORD *)(v17 + 4);
  this->m_Task[35].fTemp = *(float *)(v17 + 8);
  this->m_Task[35].cmd.bDestRole[7] = this->m_Task[35].cmd.bDestRole[10];
  this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].cmd.bValid;
  this->m_Task[35].cmd.bDestRole[9] = LODWORD(this->m_Task[35].fTemp);
  x = this->m_Task[36].vec1.x;
  v21 = this->m_bAlive;
  *(float *)&this->m_Task[36].fp = x;
  if ( v21 >= 5 && v21 < 11 )
  {
    if ( !LOBYTE(this->m_pRoleState->m_bWeSneakAttackEnemy) )
      goto LABEL_24;
    goto LABEL_23;
  }
  if ( (unsigned int)v21 <= 4 && BYTE1(this->m_pRoleState->m_bWeSneakAttackEnemy) )
LABEL_23:
    *(float *)&this->m_Task[36].fp = x + 180.0;
LABEL_24:
  CCBStageRole::ClearAniMsg((int)this, 0, 1.0);
  v22 = *(_BYTE *)(this->m_pRoleState->InitUI(this->m_bAlive) + 878);
  v23 = this->m_bAlive;
  LOBYTE(this->m_vThrowVec.x) = v22;
  if ( v23 <= 4 )
    LOBYTE(this->m_vThrowVec.x) = 0;
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
      (Actor *->SetTimeScale()*((_DWORD *)this + 73), v13);
      if ( *(_DWORD *)((CCBRoleState *->InitUI()*((_DWORD *)this + 1), *((_DWORD *)this + 71)) + 848) )
      {
        inited = (CCBRoleState *->InitUI()*((_DWORD *)this + 1), *((_DWORD *)this + 71));
        gbGeomNode::SetBladeTimeScale(*(gbGeomNode **)(inited + 848), v13);
      }
      if ( *(_DWORD *)((CCBRoleState *->InitUI()*((_DWORD *)this + 1), *((_DWORD *)this + 71)) + 860) )
      {
        v7 = (CCBRoleState *->InitUI()*((_DWORD *)this + 1), *((_DWORD *)this + 71));
        gbGeomNode::SetBladeTimeScale(*(gbGeomNode **)(v7 + 860), v13);
      }
      if ( (CCBStageRole *->ForceDelTaskByPFN()this) && !*((_BYTE *)this + 380) )
      {
        CCBStageRole::ClearBadPushTask((int)this, 0.0099999998);
        if ( !CCBRoleState::IsRoleAlive(*(CCBRoleState **)(*(_DWORD *)*this + 16), *((_DWORD *)this + 71)) )
          *((_BYTE *)this + 272) = 0;
      }
      v8 = *((_DWORD *)this + 73);
      *((_DWORD *)this + 1660) = 0;
      if ( gbVisNode::PopMessage(*(gbVisNode **)(v8 + 16), (struct gbNodeMsgObj *)&dword_17AB9C8) == 1
        && dword_17AB9C8 == 1 )
      {
        *((_DWORD *)this + 1660) = dword_17AB9CC;
      }
      if ( !*((_BYTE *)this + 380) )
        (CCBStageRole *->Grab()this, *((_DWORD *)this + 1660));
      if ( !*((_DWORD *)this + 71) && *((_DWORD *)this + 1642) != 31 )
      {
        Instance = (char *)CScreenMode::GetInstance();
        (CCBStageRole *->PlaySound()Instance, aWe011, a2);
      }
      if ( *((_DWORD *)this + 71) == 4 && *((_DWORD *)this + 1642) != 31 )
      {
        v10 = (char *)CScreenMode::GetInstance();
        (CCBStageRole *->PlaySound()v10, aWe011b, v11);
      }
      return (Actor *->QueryState()*((_DWORD *)this + 73));
    }
  }
  return result;
}

// 0x00509B90
void CCBStageRole::IsDoTask(gbMatrixStack *a2)
{
  __int32 m_bAlive; // eax
  __int32 v4; // eax
  int v5; // esi
  int v6; // edi
  char RoleType; // al
  unsigned int v8; // edi
  int v9; // esi
  int HoldTime; // ebx
  __int32 v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int *LastBladePos; // ecx
  double v16; // st7
  int inited; // eax
  CCBStage *m_pStage; // eax
  char x_low; // cl
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
  (gbMatrix4 *->gbMatrix4()v25);
  m_bAlive = this->m_bAlive;
  memset(&v23, 0, sizeof(v23));
  v20 = 0;
  if ( m_bAlive >= 5 && m_bAlive < 11 )
    this->ProcPursueRole(0, 0, 0);
  if ( LOBYTE(this->m_fTimeScale) )
  {
    CCBStageRole::DoTask((int)this, &v23.x);
    v4 = this->m_bAlive;
    v23.y = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 10.0 + (double)v4) * 5.0 + v23.y + 6.0;
    if ( (unsigned int)v4 <= 4 || v4 >= 5 && v4 < 11 && this->ForceEndTaskByPFN() )
    {
      (gbCamera *->PointWorldToScr()&this->m_pStage->m_pCam->OrthoSize, &v23, &v21, &v22);
      v5 = this->m_pRoleState->SetRoleField(this->m_bAlive, 0);
      v6 = this->m_pRoleState->SetRoleField(this->m_bAlive, 1);
      RoleType = this->m_pRoleState->GetRoleType(this->m_bAlive);
      if ( this->m_bAlive == 10 && LOBYTE(this->m_pRoleState->m_nBossRound) || RoleType && v5 > v6 / 4 )
        strcpy(byte_17AB8B8, *(const char **)(this->m_pRoleState->InitUI(this->m_bAlive) + 888));
      else
        sprintf(byte_17AB8B8, "%d/%d", v5, v6);
      v8 = 10 * strlen(byte_17AB8B8);
      v9 = (__int64)((v21 + 1.0) * (double)g_Input.KeyInfo[120].Data * 0.5);
      HoldTime = (__int64)((1.0 - v22) * (double)g_Input.KeyInfo[120].HoldTime * 0.5);
      if ( v9 >= 0 )
      {
        if ( v9 > (int)(g_Input.KeyInfo[120].Data - v8) )
          v9 = g_Input.KeyInfo[120].Data - v8;
      }
      else
      {
        v9 = 0;
      }
      if ( HoldTime >= 20 )
      {
        if ( HoldTime > g_Input.KeyInfo[120].HoldTime )
          HoldTime = g_Input.KeyInfo[120].HoldTime;
      }
      else
      {
        HoldTime = 20;
      }
      sub_4DFC40((char *)this->m_pStage->m_TempStorageNGH, byte_17AB8B8, v9, HoldTime, -1);
      if ( this->m_bAlive > 4u )
        this->ProcPursueRole(v9, HoldTime, 1);
    }
  }
  if ( BYTE1(this->m_pStage->m_pCBSystem->m_bFiveNimbus) && dword_17A990C == 1
    || BYTE1(this->m_bValid) && (LOBYTE(this->m_bPaused) || this->m_bAlive < 5) )
  {
    a2->Push();
    a2->Translate((struct gbVec3D *)&this->m_Task[35].cmd.bDestRole[7]);
    a2->Rotate(*(float *)&this->m_Task[36].fp, (struct gbVec3D *)&dword_17AB9B8);
    v11 = this->m_Task[35].cmd.bDestRole[3];
    switch ( dword_56FE98[v11] )
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
    v12 = this->m_bAlive;
    if ( !v12 && (v11 == 39 || v11 == 49) )
      v20 = 0;
    if ( v12 == 3 )
      v20 = 257;
    if ( v12 == 1 )
      v20 = 257;
    if ( (v12 == 2 || v12 == 4) && v11 == 46 )
      v20 = 256;
    if ( LOBYTE(this->m_vThrowVec.z) )
    {
      if ( this->m_vecLen.x > 0.0 || (LOBYTE(v20) = 0, this->m_vecLen.x >= 0.0) )
        LOBYTE(v20) = 1;
      if ( this->m_vecLen.y <= 0.0 && this->m_vecLen.y < 0.0 )
        goto LABEL_64;
    }
    else if ( !HIBYTE(v20) )
    {
LABEL_64:
      if ( (_BYTE)v20 && *(_DWORD *)(this->m_pRoleState->InitUI(this->m_bAlive) + 848) )
      {
        a2->Push();
        gbActor::GetTagNodeTM(*(gbActor **)(this->m_bFlash + 16), (struct gbMatrix4 *)v25, aTagWeapon2);
        a2->MultMatrix((struct gbMatrix4 *)v25);
        inited = this->m_pRoleState->InitUI(this->m_bAlive);
        (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)(inited + 848) + 16))(*(_DWORD *)(inited + 848), 0);
        a2->Pop();
      }
      if ( BYTE2(this->m_bPaused) )
      {
        m_pStage = (CCBStage *)this->m_pStage;
        x_low = LOBYTE(this->m_vThrowVec.x);
        v24[0] = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 7.8000002) * 0.34999999 + 0.64999998;
        v24[1] = v24[0];
        v24[2] = v24[0];
        if ( x_low )
        {
          gbRenderEffect::SetVariant(
            *(gbRenderEffect **)&m_pStage->m_TempStorageWPX[4].m_name[96],
            PARAM_HANDLE_SPECULAR,
            v24);
          (Actor *->DispatchAction()this->m_bFlash, *(_DWORD *)&this->m_pStage->m_TempStorageWPX[4].m_name[96]);
        }
        else
        {
          gbRenderEffect::SetVariant(
            *(gbRenderEffect **)&m_pStage->m_TempStorageWPX[4].m_name[92],
            PARAM_HANDLE_SPECULAR,
            v24);
          (Actor *->DispatchAction()this->m_bFlash, *(_DWORD *)&this->m_pStage->m_TempStorageWPX[4].m_name[92]);
        }
      }
      else
      {
        (Actor *->DispatchAction()this->m_bFlash, 0);
      }
      a2->Pop();
      return;
    }
    if ( *(_DWORD *)(this->m_pRoleState->InitUI(v12) + 860) )
    {
      a2->Push();
      gbActor::GetTagNodeTM(*(gbActor **)(this->m_bFlash + 16), (struct gbMatrix4 *)v25, aTagWeapon1);
      a2->MultMatrix((struct gbMatrix4 *)v25);
      v13 = this->m_pRoleState->InitUI(this->m_bAlive);
      (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)(v13 + 860) + 16))(*(_DWORD *)(v13 + 860), 0);
      a2->Pop();
      if ( this->m_bAlive == 3 && *(_BYTE *)(LODWORD(g_SceneMgr.m_npc[0].m_path.length[16]) + 613) == 3 )
      {
        v14 = this->m_pRoleState->InitUI(3);
        LastBladePos = (int *)gbGeomNode::GetLastBladePos(*(gbGeomNode **)(v14 + 860), 0);
        if ( LastBladePos )
        {
          v16 = this->m_pStage->m_pCBSystem->m_DeltaTime + flt_17ABCCC;
          flt_17ABCCC = v16;
          if ( v16 >= 0.050000001 )
          {
            this->m_pStage->m_pCBSystem->m_p3DSpark->CreateOne(*LastBladePos, LastBladePos[1], LastBladePos[2]);
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
  sub_50B430(this->m_pStage, a2);
  sub_50B4C0(this);
  return sub_50B4F0((int *)this->m_pStage);
}

// 0x0050A1A0
char CCBStageRole::Release(char a2)
{
  LOBYTE(this->m_bPaused) = a2;
  return a2;
}

// 0x0050A1B0
int CCBStageRole::TryRelease(int _this)
{
  if ( CCBRoleState::GetRoleField(*(_BYTE **)(this + 4), *(_DWORD *)(this + 284), 23) )
    return CCBStageRole::ClearAniMsg(1, 0.44);
  else
    return CCBStageRole::ClearAniMsg(0, 1.0);
}

// 0x0050A1F0
char CCBStageRole::ForceRelease(char a2)
{
  BYTE1(this->m_bValid) = a2;
  return a2;
}

// 0x0050A200
char CCBStageRole::DangerForceRelease(char a2)
{
  BYTE2(this->m_bValid) = a2;
  return a2;
}

// 0x0050A210
int CCBStageRole::IsGrabedBy(int _this)
{
  int result; // eax

  if ( *(_DWORD *)(this + 292) )
  {
    Actor::EnableTransition(bVisible[*(_DWORD *)(this + 6568)], *(_BYTE *)(this + 372) != 0);
    return Actor::CompareAction(*(_DWORD *)(this + 6568), 0);
  }
  return result;
}

// 0x0050A260
int CCBStageRole::GetPointerPos(int _this)
{
  int result; // eax

  if ( *(_DWORD *)(this + 292) )
  {
    Actor::EnableTransition(bVisible[*(_DWORD *)(this + 6568)], *(_BYTE *)(this + 372) != 0);
    return Actor::SetVisible(bVisible[*(_DWORD *)(this + 6568)], 0, 0);
  }
  return result;
}

// 0x0050A2B0
void CCBStageRole::SetBladeTime(int a2)
{
  __int32 *v3; // eax
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
  v3 = (__int32 *)&this->m_pStage->m_pRole[a2]->m_Task[35].cmd.bDestRole[7];
  dword_17AB898 = *v3;
  dword_17AB89C = v3[1];
  dword_17AB8A0 = v3[2];
  v4 = *(float *)&dword_17AB898 - *(float *)&this->m_Task[35].cmd.bDestRole[7];
  *(float *)&v7 = *(float *)&dword_17AB89C - *(float *)&this->m_Task[35].cmd.bDestRole[8];
  v5 = *(float *)&dword_17AB8A0 - *(float *)&this->m_Task[35].cmd.bDestRole[9];
  dword_17AB8AC = v7;
  *(float *)&v8 = v5;
  *(float *)&dword_17AB8A8 = v4;
  dword_17AB8B0 = v8;
  (gbVec3D *->Normalize()&dword_17AB8A8);
  v6 = acos(
         *(float *)&dword_17AB890 * *(float *)&dword_17AB8B0
       + *(float *)&dword_17AB88C * *(float *)&dword_17AB8AC
       + *(float *)&dword_17AB888 * *(float *)&dword_17AB8A8);
  *(float *)&this->m_Task[36].fp = v6;
  if ( *(float *)&dword_17AB8A8 < 0.0 )
    *(float *)&this->m_Task[36].fp = 6.2831855 - v6;
  *(float *)&this->m_Task[36].fp = *(float *)&this->m_Task[36].fp * 57.29578;
}

// 0x0050A500
bool CCBStageRole::LoadAction(char a1, int a2, int a3, int a4, int a5, int a6)
{
  struct gbOBBox *v6; // eax

  v6 = (struct gbOBBox *)CCBStageRole::GetWorldPos();
  return (gbRay *->IsColOBB()&a1, v6) == 1;
}

// 0x0050A520
int CCBStageRole::GetStatus(int index)
{
  Actor::PlayAction(*(_DWORD **)&this->m_pStage[292], (int)&this->m_pStage[296]);
  return *(_DWORD *)&this->m_pStage[284];
}

// 0x0050A560
float * CCBStageRole::GetWorldPos()
{
  _BYTE v3[64]; // [esp+8h] [ebp-40h] BYREF

  (gbMatrix4 *->gbMatrix4()v3);
  (Actor *->PlayAction()this->m_bFlash, (int)&this->m_bFlashCounter);
  (gbMatrix4 *->LoadIdentity()v3);
  (gbMatrix4 *->SetAxisAngle()v3, GB_AXIS_Y, *(float *)this->?[36].cmd.bDestRole);
  (gbMatrix4 *->RightMultiply()&this->m_bFlashCounter, (const struct gbMatrix4 *)v3);
  (gbMatrix4 *->RightTranslate()&this->m_bFlashCounter, (struct gbVec3D *)&this->?[36].cmd.bMultiDestRole);
  return (float *)&this->m_bFlashCounter;
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
  v3 = *a2 - *(float *)&this->m_Task[35].cmd.bDestRole[7];
  v8 = a2[1] - *(float *)&this->m_Task[35].cmd.bDestRole[8];
  v4 = a2[2] - *(float *)&this->m_Task[35].cmd.bDestRole[9];
  v7.y = v8;
  v9 = v4;
  v7.x = v3;
  v7.z = v9;
  if ( gbVec3D::Length(&v7) <= 0.0 )
    return 0.0;
  gbVec3D::Normalize(&v7);
  v6 = acos(v7.y * *(float *)&dword_17AB87C + v7.z * *(float *)&dword_17AB880 + *(float *)&dword_17AB878 * v7.x);
  if ( v7.x < 0.0 )
    v6 = 6.2831855 - v6;
  return v6 * 57.29578;
}

// 0x0050A6F0
bool CCBStageRole::ForceDelTaskByPFN()
{
  return LODWORD(this->m_vecLen.z) == 0;
}

// 0x0050A700
bool CCBStageRole::ForceEndTaskByPFN()
{
  double v1; // st7
  double v2; // st6
  float v4; // [esp+4h] [ebp-14h]
  float v5; // [esp+8h] [ebp-10h]
  gbVec3D v6; // [esp+Ch] [ebp-Ch] BYREF

  v1 = *(float *)&this->m_Task[35].cmd.bDestRole[7] - *(float *)&this->m_Task[35].cmd.bDestRole[10];
  v4 = *(float *)&this->m_Task[35].cmd.bDestRole[8] - *(float *)&this->m_Task[35].cmd.bValid;
  v2 = *(float *)&this->m_Task[35].cmd.bDestRole[9] - this->m_Task[35].fTemp;
  v6.y = v4;
  v5 = v2;
  v6.x = v1;
  v6.z = v5;
  return gbVec3D::Length(&v6) <= 13.0;
}

// 0x0050A770
bool CCBStageRole::EndTask(int a2, int a3)
{
  __int32 m_bAlive; // eax
  CCBStage *m_pStage; // ecx
  float *v6; // eax
  float *v7; // ecx
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
  m_bAlive = this->m_bAlive;
  memset(&v17, 0, sizeof(v17));
  if ( m_bAlive )
    return 0;
  m_pStage = (CCBStage *)this->m_pStage;
  v6 = (float *)m_pStage->m_pRole[a2];
  v7 = (float *)&m_pStage->m_pRole[a3]->m_Task[35].cmd.bDestRole[10];
  v6 += 1649;
  v8 = *v7 - *v6;
  v18 = v7[1] - v6[1];
  v9 = v7[2] - v6[2];
  v16.y = v18;
  v19 = v9;
  v16.x = v8;
  v16.z = v19;
  gbVec3D::Normalize(&v16);
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
  v13 = *(float *)&this->m_Task[35].cmd.bDestRole[7] - v12;
  v20 = *(float *)&this->m_Task[35].cmd.bDestRole[8] - v18;
  v14 = *(float *)&this->m_Task[35].cmd.bDestRole[9] - v19;
  v17.y = v20;
  v21 = v14;
  v17.x = v13;
  v17.z = v21;
  return gbVec3D::Length(&v17) <= 20.0;
}

// 0x0050A8E0
char CCBStageRole::DelTask(int a2)
{
  this->m_Task[35].cmd.bDestRole[2] = a2;
  return 1;
}

// 0x0050A8F0
char CCBStageRole::DelAllTask(int _this, int a2, char a3)
{
  char result; // al

  result = 1;
  if ( *(_BYTE *)(this + 373) == 1 )
    return 0;
  *(_BYTE *)(this + 373) = 1;
  *(_BYTE *)(this + 374) = a3;
  *(_DWORD *)(this + 376) = a2;
  return result;
}

// 0x0050A920
char CCBStageRole::GetCurrentTask(int _this, int a2)
{
  char result; // al

  if ( a2 != 0x7FFFFFFF || (result = *(_BYTE *)(this + 373)) != 0 )
  {
    result = (CCBStageRole *->GetState()this);
    *(_BYTE *)(this + 373) = 0;
    *(_BYTE *)(this + 374) = 0;
    *(_DWORD *)(this + 376) = 0;
  }
  return result;
}

// 0x0050A960
int CCBStageRole::GetCurrentTaskIndex(int _this)
{
  this->GetState();
  *(_BYTE *)(this + 373) = 0;
  *(_BYTE *)(this + 374) = 0;
  *(_DWORD *)(this + 376) = 0;
  return 0;
}

// 0x0050A980
bool CCBStageRole::IsReady(int idx)
{
  return this->m_pStage[373] && *(_DWORD *)&this->m_pStage[376] == idx;
}

// 0x0050A9B0
_DWORD * CCBStageRole::DoTask(int _this, float *a2)
{
  float *WorldPos; // eax
  float *Center; // eax
  _DWORD *result; // eax
  char v6[12]; // [esp+8h] [ebp-Ch] BYREF

  if ( (byte_17AB874 & 1) == 0 )
  {
    byte_17AB874 |= 1u;
    gbMatrix4::gbMatrix4(&stru_17AB828);
    atexit(nullsub_37);
  }
  WorldPos = (CCBStageRole *->GetWorldPos()this);
  Center = (float *)WorldPos->GetCenter(v6);
  * a2 = (*)*Center;
  a2[1] = Center[1];
  a2[2] = Center[2];
  a2[1] = *(float *)(this + 364) * 0.5 + a2[1] + 10.0;
  result = (_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284));
  if ( *result == 707 )
    a2[1] = a2[1] - 80.0;
  return result;
}

// 0x0050AA60
void CCBStageRole::ClearBadPushTask(int _this, float a2)
{
  unsigned int v3; // eax
  int v4; // eax
  int v5; // eax

  v3 = *(_DWORD *)(this + 284);
  if ( v3 <= 4 )
  {
    if ( *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), v3) + 848) )
    {
      v4 = CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284));
      gbGeomNode::SetBladeTime(*(gbGeomNode **)(v4 + 848), a2);
    }
    if ( *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284)) + 860) )
    {
      v5 = CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284));
      gbGeomNode::SetBladeTime(*(gbGeomNode **)(v5 + 860), a2);
    }
  }
}

// 0x0050AAE0
double CCBStageRole::PushBackAllTask()
{
  __int32 m_bFlash; // eax
  float v3; // [esp+4h] [ebp-4h] BYREF

  m_bFlash = this->m_bFlash;
  v3 = 0.0;
  if ( gbVisNode::GetBlend(*(gbVisNode **)(m_bFlash + 16), &v3) )
    return v3;
  else
    return 1.0;
}

// 0x0050AB10
void CCBStageRole::ClearAniMsg(int _this, char a2, float a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax

  if ( a3 <= 0.98000002 && a2 )
  {
    gbVisNode::SetBlend(*(gbVisNode **)(*(_DWORD *)(this + 292) + 16), BLEND_ALPHA, a3);
    if ( *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284)) + 860) )
    {
      v4 = CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284));
      gbVisNode::SetBlend(*(gbVisNode **)(v4 + 860), BLEND_ALPHA, a3);
    }
    if ( *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284)) + 848) )
    {
      v5 = CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284));
      gbVisNode::SetBlend(*(gbVisNode **)(v5 + 848), BLEND_ALPHA, a3);
    }
  }
  else
  {
    gbVisNode::SetBlend(*(gbVisNode **)(*(_DWORD *)(this + 292) + 16), BLEND_NONE, 1.0);
    if ( *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284)) + 860) )
    {
      v6 = CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284));
      gbVisNode::SetBlend(*(gbVisNode **)(v6 + 860), BLEND_NONE, 1.0);
    }
    if ( *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284)) + 848) )
    {
      v7 = CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284));
      gbVisNode::SetBlend(*(gbVisNode **)(v7 + 848), BLEND_NONE, 1.0);
    }
  }
}

// 0x0050AC50
int CCBStageRole::SetParam(int a2, char a3)
{
  int result; // eax
  Actor *m_bFlash; // ecx

  result = a2;
  if ( a2 > 0 )
  {
    sprintf(byte_17AB818, "z%02d", a2);
    if ( (byte_1895558 & 1) == 0 )
    {
      byte_1895558 |= 1u;
      (CEffMgr *->Reset()&g_nCursorState);
      atexit(nullsub_1);
    }
    result = (CEffSParticle *->GetEditorTaskDescription()&g_nCursorState, (unsigned __int8 *)byte_17AB818);
    if ( a3 || result != this->m_Task[36].cmd.bMultiDestRole )
    {
      m_bFlash = (Actor *)this->m_bFlash;
      this->m_Task[36].cmd.bMultiDestRole = result;
      m_bFlash->SetVisible((int)byte_17AB818);
      return (*(int (**)(_DWORD, _DWORD))(**(_DWORD **)(this->m_bFlash + 16) + 24))(
               *(_DWORD *)(this->m_bFlash + 16),
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
  char *v12; // eax
  char *v13; // eax
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
  if ( *(_DWORD **)&this->m_pStage[376] != a6 )
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
    v12 = (char *)&this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 416];
    *(_DWORD *)v12 = a2;
    *((_DWORD *)v12 + 1) = a3;
    *((_DWORD *)v12 + 2) = a4;
    *((_DWORD *)v12 + 3) = a5;
    this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 504] = 1;
    this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 506] = 0;
    this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 505] = 0;
    *(_DWORD *)&this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 496] = CCBSystem::ProcProtect(**(_DWORD ***)this->m_pStage);
    v13 = (char *)&this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 432];
    *(_DWORD *)v13 = dword_17AB7F8;
    *((_DWORD *)v13 + 1) = dword_17AB7FC;
    *((_DWORD *)v13 + 2) = dword_17AB800;
    *(_DWORD *)&this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 500] = a9;
    if ( a8 )
      qmemcpy(&this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 444], a8, 0x2Cu);
    else
      memset(&this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 444], 0, 0x2Cu);
    goto LABEL_23;
  }
  this->GetTaskState();
  this->m_pStage[504] = 1;
  this->m_pStage[506] = 0;
  this->m_pStage[505] = 0;
  *(_DWORD *)&this->m_pStage[416] = a2;
  *(_DWORD *)&this->m_pStage[420] = a3;
  *(_DWORD *)&this->m_pStage[424] = a4;
  *(_DWORD *)&this->m_pStage[428] = a5;
  *(_DWORD *)&this->m_pStage[496] = CCBSystem::ProcProtect(**(_DWORD ***)this->m_pStage);
  *(_DWORD *)&this->m_pStage[432] = dword_17AB7F8;
  *(_DWORD *)&this->m_pStage[436] = dword_17AB7FC;
  *(_DWORD *)&this->m_pStage[440] = dword_17AB800;
  *(_DWORD *)&this->m_pStage[500] = 3;
  if ( a8 )
    qmemcpy(&this->m_pStage[444], a8, 0x2Cu);
  else
    memset(&this->m_pStage[444], 0, 0x2Cu);
  this->m_pStage[602] = 0;
LABEL_23:
  ++*(_DWORD *)&this->m_pStage[392];
  return 1;
}

// 0x0050B070
char CCBStageRole::ProcTransportRun(
        CCBStageRole *this,
        int a2,
        int a3,
        int a4,
        int a5,
        int *a6,
        const void *a7,
        int a8)
{
  int *v9; // eax
  int v11; // eax
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
  switch ( a8 )
  {
    case 2:
      this->GetState();
      break;
    case 3:
      this->GetTaskState();
      break;
    case 4:
      if ( *(int *)&this->m_pStage[392] > 0 )
        return 0;
      break;
    default:
      return 0;
  }
  this->m_pStage[504] = 1;
  this->m_pStage[506] = 0;
  this->m_pStage[505] = 0;
  *(_DWORD *)&this->m_pStage[416] = a2;
  *(_DWORD *)&this->m_pStage[420] = a3;
  *(_DWORD *)&this->m_pStage[424] = a4;
  *(_DWORD *)&this->m_pStage[428] = a5;
  *(_DWORD *)&this->m_pStage[496] = CCBSystem::ProcProtect(**(_DWORD ***)this->m_pStage);
  *(_DWORD *)&this->m_pStage[432] = dword_17AB7C8;
  *(_DWORD *)&this->m_pStage[436] = dword_17AB7CC;
  *(_DWORD *)&this->m_pStage[440] = dword_17AB7D0;
  *(_DWORD *)&this->m_pStage[500] = a8;
  if ( a7 )
    qmemcpy(&this->m_pStage[444], a7, 0x2Cu);
  else
    memset(&this->m_pStage[444], 0, 0x2Cu);
  v11 = *(_DWORD *)&this->m_pStage[392] + 1;
  this->m_pStage[602] = 0;
  *(_DWORD *)&this->m_pStage[392] = v11;
  return 1;
}

// 0x0050B290
char CCBStageRole::SetForceFinishThrowingWeapon(int a2)
{
  int v2; // ebx
  float *v4; // eax

  v2 = a2;
  if ( a2 == 63 )
  {
    memset(&this->m_Task[34].bExecuted, 0, 0x60u);
    --LODWORD(this->m_vecLen.z);
    return 1;
  }
  else
  {
    if ( a2 < SLODWORD(this->m_vecLen.z) )
    {
      v4 = (float *)&this->m_fThrowSpeed + 24 * a2;
      do
      {
        ++v2;
        qmemcpy(v4, v4 + 24, 0x60u);
        v4 += 24;
      }
      while ( v2 < SLODWORD(this->m_vecLen.z) );
    }
    memset(&this->m_fThrowSpeed + 24 * LODWORD(this->m_vecLen.z)--, 0, 0x60u);
    return 1;
  }
}

// 0x0050B330
char CCBStageRole::GetCurrentState()
{
  char *v1; // eax
  int v2; // edx

  v1 = (char *)&this->m_pStage[496];
  v2 = 64;
  do
  {
    v1[8] = 0;
    *(_DWORD *)v1 = 0;
    v1 += 96;
    --v2;
  }
  while ( v2 );
  *(_DWORD *)&this->m_pStage[392] = 0;
  return 1;
}

// 0x0050B360
int CCBStageRole::ProcCatchED()
{
  int result; // eax

  if ( this->m_bAlive < 5 )
  {
    (Actor *->GetAnimDuration()this->m_bFlash, (int)aZ01);
    (Actor *->GetAnimDuration()this->m_bFlash, (int)aZ09);
    (Actor *->GetAnimDuration()this->m_bFlash, (int)aZ06);
    (Actor *->GetAnimDuration()this->m_bFlash, (int)aZ03);
    (Actor *->GetAnimDuration()this->m_bFlash, (int)aZ04);
    (Actor *->GetAnimDuration()this->m_bFlash, (int)aZ05);
    (Actor *->GetAnimDuration()this->m_bFlash, (int)&unk_5888D0);
    (Actor *->GetAnimDuration()this->m_bFlash, (int)&unk_5888C8);
    (Actor *->GetAnimDuration()this->m_bFlash, (int)&unk_5888C4);
    return (Actor *->GetAnimDuration()this->m_bFlash, (int)&aNghOpenObjD);
  }
  return result;
}

// 0x0050B530
int CCBStageRole::GetTaskState()
{
  int result; // eax
  int v2; // edx
  char *v3; // edi

  result = *(_DWORD *)&this->m_pStage[392];
  if ( result )
  {
    if ( result > 0 )
    {
      v2 = *(_DWORD *)&this->m_pStage[392];
      v3 = (char *)&this->m_pStage[96 * result + 416];
      do
      {
        --v2;
        qmemcpy(v3, v3 - 96, 0x60u);
        v3 -= 96;
      }
      while ( v2 );
    }
    memset(&this->m_pStage[416], 0, 0x60u);
    return 0;
  }
  return result;
}

// 0x0050B580
char CCBStageRole::ProcPursueRole(int a2, int a3, char a4)
{
  CCBUI *m_pUI; // edi
  UIStatic *v6; // ecx
  int v7; // ebx
  UIStatic *v8; // ecx
  UIStatic *v9; // ecx
  UIStatic *v10; // ecx
  UIStatic *v11; // ecx
  UIStatic *v12; // ecx
  UIStatic *v13; // ecx
  UIStatic *v14; // ecx
  UIStatic *v15; // ecx
  UIStatic *v16; // ecx
  UIStatic *v17; // ecx
  UIStatic *v18; // ecx
  UIStatic *v19; // ecx
  UIStatic *v20; // ecx
  UIStatic *v21; // ecx
  UIStatic *v22; // ecx
  UIStatic *v23; // ecx
  UIStatic *v24; // ecx
  char result; // al
  UIStatic *v26; // ecx
  UIStatic *v27; // ecx
  UIStatic *v28; // ecx
  UIStatic *v29; // ecx
  UIStatic *v30; // ecx
  UIStatic *v31; // ecx
  UIStatic *v32; // ecx
  UIStatic *v33; // ecx
  UIStatic *v34; // ecx
  UIStatic *v35; // ecx
  UIStatic *v36; // ecx
  UIStatic *v37; // ecx
  UIStatic *v38; // ecx
  UIStatic *v39; // ecx
  UIStatic *v40; // ecx
  UIStatic *v41; // ecx
  UIStatic *v42; // ecx
  UIStatic *v43; // ecx
  UIStatic *v44; // ecx
  UIStatic *v45; // ecx

  m_pUI = (CCBUI *)this->m_pStage->m_pCBSystem->m_pUI;
  if ( a4 )
  {
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 6) )
    {
      v6 = (UIStatic *)m_pUI->m_pAttackSequenFace[this->m_bAlive + 9];
      (*(void (**)(UIStatic *, int))v6->m_fontcolor.ColorQuadFmt)(v6, 1);
      m_pUI->m_pAttackSequenFace[this->m_bAlive + 9]->ScreenToClient(a2, a3);
      v7 = a2 + 24;
    }
    else
    {
      v7 = a2;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 7) )
    {
      v8 = (UIStatic *)m_pUI->m_pRoleStateFaceName[this->m_bAlive];
      (*(void (**)(UIStatic *, int))v8->m_fontcolor.ColorQuadFmt)(v8, 1);
      m_pUI->m_pRoleStateFaceName[this->m_bAlive]->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 8) )
    {
      v9 = (UIStatic *)m_pUI->m_pRoleStateAttackInc[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v9->m_fontcolor.ColorQuadFmt)(v9, 1);
      m_pUI->m_pRoleStateAttackInc[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 9) )
    {
      v10 = (UIStatic *)m_pUI->m_pRoleStateAttackDec[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v10->m_fontcolor.ColorQuadFmt)(v10, 1);
      m_pUI->m_pRoleStateAttackDec[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 12) )
    {
      v11 = (UIStatic *)m_pUI->m_pRoleStateLuckInc[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v11->m_fontcolor.ColorQuadFmt)(v11, 1);
      m_pUI->m_pRoleStateLuckInc[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 13) )
    {
      v12 = (UIStatic *)m_pUI->m_pRoleStateLuckDec[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v12->m_fontcolor.ColorQuadFmt)(v12, 1);
      m_pUI->m_pRoleStateLuckDec[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 10) )
    {
      v13 = (UIStatic *)m_pUI->m_pRoleStateDefenceInc[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v13->m_fontcolor.ColorQuadFmt)(v13, 1);
      m_pUI->m_pRoleStateDefenceInc[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 11) )
    {
      v14 = (UIStatic *)m_pUI->m_pRoleStateDefenceDec[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v14->m_fontcolor.ColorQuadFmt)(v14, 1);
      m_pUI->m_pRoleStateDefenceDec[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 24;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 14) )
    {
      v15 = (UIStatic *)m_pUI->m_pRoleStateSpeedInc[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v15->m_fontcolor.ColorQuadFmt)(v15, 1);
      m_pUI->m_pRoleStateSpeedInc[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 15) )
    {
      v16 = (UIStatic *)m_pUI->m_pRoleStateSpeedDec[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v16->m_fontcolor.ColorQuadFmt)(v16, 1);
      m_pUI->m_pRoleStateSpeedDec[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 16) )
    {
      v17 = (UIStatic *)m_pUI->m_pRoleStateStable[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v17->m_fontcolor.ColorQuadFmt)(v17, 1);
      m_pUI->m_pRoleStateStable[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 17) )
    {
      v18 = (UIStatic *)m_pUI->m_pRoleStateBlank[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v18->m_fontcolor.ColorQuadFmt)(v18, 1);
      m_pUI->m_pRoleStateBlank[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 18) )
    {
      v19 = (UIStatic *)m_pUI->m_pRoleStateForbid[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v19->m_fontcolor.ColorQuadFmt)(v19, 1);
      m_pUI->m_pRoleStateForbid[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 19) )
    {
      v20 = (UIStatic *)m_pUI->m_pRoleStateSleep[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v20->m_fontcolor.ColorQuadFmt)(v20, 1);
      m_pUI->m_pRoleStateSleep[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 20) )
    {
      v21 = (UIStatic *)m_pUI->m_pRoleStateChaos[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v21->m_fontcolor.ColorQuadFmt)(v21, 1);
      m_pUI->m_pRoleStateChaos[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 21) )
    {
      v22 = (UIStatic *)m_pUI->m_pRoleStateMad[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v22->m_fontcolor.ColorQuadFmt)(v22, 1);
      m_pUI->m_pRoleStateMad[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 22) )
    {
      v23 = (UIStatic *)m_pUI->m_pRoleStateMirror[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v23->m_fontcolor.ColorQuadFmt)(v23, 1);
      m_pUI->m_pRoleStateMirror[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    if ( this->m_pRoleState->GetRoleField(this->m_bAlive, 23) )
    {
      v24 = (UIStatic *)m_pUI->m_pRoleStateWall[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v24->m_fontcolor.ColorQuadFmt)(v24, 1);
      m_pUI->m_pRoleStateWall[this->m_bAlive + 6]->ScreenToClient(v7, a3);
      v7 += 20;
    }
    result = this->m_pRoleState->GetRoleField(this->m_bAlive, 26);
    if ( result )
    {
      v26 = (UIStatic *)m_pUI->m_pRoleStateBound[this->m_bAlive + 6];
      (*(void (**)(UIStatic *, int))v26->m_fontcolor.ColorQuadFmt)(v26, 1);
      return m_pUI->m_pRoleStateBound[this->m_bAlive + 6]->ScreenToClient(v7, a3);
    }
  }
  else
  {
    v27 = (UIStatic *)m_pUI->m_pAttackSequenFace[this->m_bAlive + 9];
    (*(void (**)(UIStatic *, _DWORD))v27->m_fontcolor.ColorQuadFmt)(v27, 0);
    v28 = (UIStatic *)m_pUI->m_pRoleStateFaceName[this->m_bAlive];
    (*(void (**)(UIStatic *, _DWORD))v28->m_fontcolor.ColorQuadFmt)(v28, 0);
    v29 = (UIStatic *)m_pUI->m_pRoleStateAttackInc[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v29->m_fontcolor.ColorQuadFmt)(v29, 0);
    v30 = (UIStatic *)m_pUI->m_pRoleStateAttackDec[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v30->m_fontcolor.ColorQuadFmt)(v30, 0);
    v31 = (UIStatic *)m_pUI->m_pRoleStateDefenceInc[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v31->m_fontcolor.ColorQuadFmt)(v31, 0);
    v32 = (UIStatic *)m_pUI->m_pRoleStateDefenceDec[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v32->m_fontcolor.ColorQuadFmt)(v32, 0);
    v33 = (UIStatic *)m_pUI->m_pRoleStateLuckInc[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v33->m_fontcolor.ColorQuadFmt)(v33, 0);
    v34 = (UIStatic *)m_pUI->m_pRoleStateLuckDec[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v34->m_fontcolor.ColorQuadFmt)(v34, 0);
    v35 = (UIStatic *)m_pUI->m_pRoleStateSpeedInc[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v35->m_fontcolor.ColorQuadFmt)(v35, 0);
    v36 = (UIStatic *)m_pUI->m_pRoleStateSpeedDec[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v36->m_fontcolor.ColorQuadFmt)(v36, 0);
    v37 = (UIStatic *)m_pUI->m_pRoleStateStable[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v37->m_fontcolor.ColorQuadFmt)(v37, 0);
    v38 = (UIStatic *)m_pUI->m_pRoleStateBlank[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v38->m_fontcolor.ColorQuadFmt)(v38, 0);
    v39 = (UIStatic *)m_pUI->m_pRoleStateForbid[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v39->m_fontcolor.ColorQuadFmt)(v39, 0);
    v40 = (UIStatic *)m_pUI->m_pRoleStateSleep[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v40->m_fontcolor.ColorQuadFmt)(v40, 0);
    v41 = (UIStatic *)m_pUI->m_pRoleStateChaos[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v41->m_fontcolor.ColorQuadFmt)(v41, 0);
    v42 = (UIStatic *)m_pUI->m_pRoleStateMad[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v42->m_fontcolor.ColorQuadFmt)(v42, 0);
    v43 = (UIStatic *)m_pUI->m_pRoleStateMirror[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v43->m_fontcolor.ColorQuadFmt)(v43, 0);
    v44 = (UIStatic *)m_pUI->m_pRoleStateWall[this->m_bAlive + 6];
    (*(void (**)(UIStatic *, _DWORD))v44->m_fontcolor.ColorQuadFmt)(v44, 0);
    v45 = (UIStatic *)m_pUI->m_pRoleStateBound[this->m_bAlive + 6];
    return (*(char (**)(UIStatic *, _DWORD))v45->m_fontcolor.ColorQuadFmt)(v45, 0);
  }
  return result;
}

// 0x0050BBD0
int CCBStageRole::ProcTurn(int _this)
{
  unsigned int v2; // eax
  _BYTE *v3; // ecx
  int v5; // eax

  v2 = *(_DWORD *)(this + 284);
  v3 = (_BYTE *)*(_BYTE **)(this + 4);
  if ( !v3[892 * v2 + 577] )
  {
    if ( v2 <= 4 )
      return 32;
    return 50;
  }
  if ( !v3->IsActive(v2) )
    return 50;
  if ( CCBRoleState::GetRoleAttr(*(_DWORD **)(this + 4), *(_DWORD *)(this + 284)) == 5 )
    return 47;
  if ( *(_DWORD *)(this + 6564) == 4 )
    return 34;
  if ( *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284)) + 588) )
  {
    this->ClearBadPushTask(0.25);
    return 42;
  }
  else if ( CCBRoleState::GetRoleField(*(_BYTE **)(this + 4), *(_DWORD *)(this + 284), 17)
         || CCBRoleState::GetRoleField(*(_BYTE **)(this + 4), *(_DWORD *)(this + 284), 14) )
  {
    return 45;
  }
  else
  {
    v5 = CCBRoleState::GetRoleAttr(*(_DWORD **)(this + 4), *(_DWORD *)(this + 284)) - 4;
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
  __int32 m_bShowWeaponModel; // eax
  float *v9; // ecx
  char *v10; // eax
  char *Instance; // eax
  char *v12; // eax
  float *v13; // edi
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
  __int32 v29; // [esp+10h] [ebp-14h]
  int v30; // [esp+14h] [ebp-10h]
  __int32 v31; // [esp+14h] [ebp-10h]
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
  v3 = (char *)this + 96 * this->m_bShowWeaponModel;
  if ( !v3[506] )
  {
    this->m_Task[35].fTemp2 = *((float *)v3 + 108);
    this->m_Task[35].dwID = *((_DWORD *)v3 + 109);
    this->m_Task[35].eMode = *((_DWORD *)v3 + 110);
    v4 = this->m_Task[35].fTemp2 - *(float *)&this->m_Task[35].cmd.bDestRole[7];
    *(float *)&v28 = *(float *)&this->m_Task[35].dwID - *(float *)&this->m_Task[35].cmd.bDestRole[8];
    v5 = *(float *)&this->m_Task[35].eMode - *(float *)&this->m_Task[35].cmd.bDestRole[9];
    dword_17AB78C = v28;
    *(float *)&v30 = v5;
    *(float *)&dword_17AB788 = v4;
    dword_17AB790 = v30;
    if ( (gbVec3D *->Length()&dword_17AB788) < 2.0 )
    {
      this->m_Task[35].cmd.bDestRole[7] = LODWORD(this->m_Task[35].fTemp2);
      this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
      this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
      BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
      return 0;
    }
    (gbVec3D *->Normalize()&dword_17AB788);
    v7 = acos(
           *(float *)&dword_17AB780 * *(float *)&dword_17AB790
         + *(float *)&dword_17AB77C * *(float *)&dword_17AB78C
         + *(float *)&dword_17AB778 * *(float *)&dword_17AB788);
    *(float *)&this->m_Task[36].fp = v7;
    if ( *(float *)&dword_17AB788 < 0.0 )
      *(float *)&this->m_Task[36].fp = 6.2831855 - v7;
    *(float *)&this->m_Task[36].fp = *(float *)&this->m_Task[36].fp * 57.29578;
    this->m_Task[35].bValid = dword_17AB788;
    this->m_Task[35].bFinished = dword_17AB78C;
    this->m_Task[35].bExecuted = dword_17AB790;
    *(float *)&this->m_Task[35].bValid = *(float *)&this->m_Task[35].bValid * 380.0;
    *(float *)&this->m_Task[35].bFinished = *(float *)&this->m_Task[35].bFinished * 380.0;
    *(float *)&this->m_Task[35].bExecuted = *(float *)&this->m_Task[35].bExecuted * 380.0;
    if ( (CCBStageRole *->IsActive()this->m_pRoleState, this->m_bAlive) )
      this->m_Task[35].cmd.bDestRole[3] = 31;
    else
      this->m_Task[35].cmd.bDestRole[3] = 52;
    CCBStageRole::IsGrabedBy((int)this);
    BYTE2(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
    CCBStageRole::ClearBadPushTask((int)this, 0.0099999998);
    m_bShowWeaponModel = this->m_bShowWeaponModel;
    BYTE1(this->m_bPaused) = 1;
    v9 = (float *)((char *)this + 96 * m_bShowWeaponModel);
    if ( v9[108] >= -700.0 || v9[110] >= -700.0 )
    {
      if ( !this->m_bAlive )
      {
        Instance = (char *)CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()Instance, aWe011, 0);
      }
      if ( this->m_bAlive == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !this->m_bAlive )
      {
        v10 = (char *)CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v10, aWe011, 1);
      }
      if ( this->m_bAlive == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = (char *)CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v12, aWe011b, v26);
      }
    }
  }
  v13 = (float *)&this->m_Task[35].cmd.bDestRole[7];
  m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
  v32 = *(float *)&this->m_Task[35].bValid * m_DeltaTime;
  v33 = *(float *)&this->m_Task[35].bFinished * m_DeltaTime;
  v15 = v32 + *(float *)&this->m_Task[35].cmd.bDestRole[7];
  *(float *)&v29 = *(float *)&this->m_Task[35].cmd.bDestRole[8] + v33;
  v16 = *(float *)&this->m_Task[35].cmd.bDestRole[9] + m_DeltaTime * *(float *)&this->m_Task[35].bExecuted;
  this->m_Task[35].cmd.bDestRole[8] = v29;
  *(float *)&v31 = v16;
  *(float *)&this->m_Task[35].cmd.bDestRole[7] = v15;
  this->m_Task[35].cmd.bDestRole[9] = v31;
  v17 = this->m_Task[35].fTemp2 - *(float *)&this->m_Task[35].cmd.bDestRole[7];
  *(float *)&v34 = *(float *)&this->m_Task[35].dwID - *(float *)&this->m_Task[35].cmd.bDestRole[8];
  v18 = *(float *)&this->m_Task[35].eMode - *(float *)&this->m_Task[35].cmd.bDestRole[9];
  dword_17AB78C = v34;
  *(float *)&v35 = v18;
  *(float *)&dword_17AB788 = v17;
  dword_17AB790 = v35;
  if ( (gbVec3D *->Length()&dword_17AB788) >= 2.0 )
  {
    (gbVec3D *->Normalize()&dword_17AB788);
    v21 = acos(
            *(float *)&dword_17AB780 * *(float *)&dword_17AB790
          + *(float *)&dword_17AB77C * *(float *)&dword_17AB78C
          + *(float *)&dword_17AB778 * *(float *)&dword_17AB788);
    if ( *(float *)&dword_17AB788 < 0.0 )
      v21 = 6.2831855 - v21;
    v22 = v21 * 57.29578;
    flt_17ABCD0 = v22;
    if ( fabs(v22 - *(float *)&this->m_Task[36].fp) < 1.570796370506287 )
    {
      if ( this->m_pRoleState->IsRoleAlive(this->m_bAlive) )
        return 0;
      BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
      if ( !this->m_bAlive )
      {
        v24 = (char *)CScreenMode::GetInstance();
        (CCBStageRole *->PlaySound()v24, aWe011, v27);
      }
      if ( this->m_bAlive != 4 )
      {
LABEL_43:
        BYTE1(this->m_bPaused) = 0;
        return 0;
      }
    }
    else
    {
      * v13 = (*)this->m_Task[35].fTemp2;
      this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
      this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
      BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
      if ( !this->m_bAlive )
      {
        v23 = (char *)CScreenMode::GetInstance();
        (CCBStageRole *->PlaySound()v23, aWe011, v27);
      }
      if ( this->m_bAlive != 4 )
        goto LABEL_43;
    }
    v25 = (char *)CScreenMode::GetInstance();
    (CCBStageRole *->PlaySound()v25, aWe011b, v27);
    goto LABEL_43;
  }
  * v13 = (*)this->m_Task[35].fTemp2;
  this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
  this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
  BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
  if ( !this->m_bAlive )
  {
    v19 = (char *)CScreenMode::GetInstance();
    (CCBStageRole *->PlaySound()v19, aWe011, v27);
  }
  if ( this->m_bAlive == 4 )
  {
    v20 = (char *)CScreenMode::GetInstance();
    (CCBStageRole *->PlaySound()v20, aWe011b, v27);
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
  __int32 m_bShowWeaponModel; // eax
  float *v9; // ecx
  char *v10; // eax
  char *Instance; // eax
  char *v12; // eax
  float *v13; // edi
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
  __int32 v29; // [esp+10h] [ebp-14h]
  int v30; // [esp+14h] [ebp-10h]
  __int32 v31; // [esp+14h] [ebp-10h]
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
  v3 = (char *)this + 96 * this->m_bShowWeaponModel;
  if ( !v3[506] )
  {
    this->m_Task[35].fTemp2 = *((float *)v3 + 108);
    this->m_Task[35].dwID = *((_DWORD *)v3 + 109);
    this->m_Task[35].eMode = *((_DWORD *)v3 + 110);
    v4 = this->m_Task[35].fTemp2 - *(float *)&this->m_Task[35].cmd.bDestRole[7];
    *(float *)&v28 = *(float *)&this->m_Task[35].dwID - *(float *)&this->m_Task[35].cmd.bDestRole[8];
    v5 = *(float *)&this->m_Task[35].eMode - *(float *)&this->m_Task[35].cmd.bDestRole[9];
    dword_17AB75C = v28;
    *(float *)&v30 = v5;
    *(float *)&dword_17AB758 = v4;
    dword_17AB760 = v30;
    if ( (gbVec3D *->Length()&dword_17AB758) < 2.0 )
    {
      this->m_Task[35].cmd.bDestRole[7] = LODWORD(this->m_Task[35].fTemp2);
      this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
      this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
      BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
      return 0;
    }
    (gbVec3D *->Normalize()&dword_17AB758);
    v7 = acos(
           *(float *)&dword_17AB750 * *(float *)&dword_17AB760
         + *(float *)&dword_17AB74C * *(float *)&dword_17AB75C
         + *(float *)&dword_17AB748 * *(float *)&dword_17AB758);
    *(float *)&this->m_Task[36].fp = v7;
    if ( *(float *)&dword_17AB758 < 0.0 )
      *(float *)&this->m_Task[36].fp = 6.2831855 - v7;
    *(float *)&this->m_Task[36].fp = *(float *)&this->m_Task[36].fp * 57.29578;
    this->m_Task[35].bValid = dword_17AB758;
    this->m_Task[35].bFinished = dword_17AB75C;
    this->m_Task[35].bExecuted = dword_17AB760;
    *(float *)&this->m_Task[35].bValid = *(float *)&this->m_Task[35].bValid * 570.0;
    *(float *)&this->m_Task[35].bFinished = *(float *)&this->m_Task[35].bFinished * 570.0;
    *(float *)&this->m_Task[35].bExecuted = *(float *)&this->m_Task[35].bExecuted * 570.0;
    if ( (CCBStageRole *->IsActive()this->m_pRoleState, this->m_bAlive) )
      this->m_Task[35].cmd.bDestRole[3] = 31;
    else
      this->m_Task[35].cmd.bDestRole[3] = 52;
    CCBStageRole::IsGrabedBy((int)this);
    BYTE2(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
    CCBStageRole::ClearBadPushTask((int)this, 0.0099999998);
    m_bShowWeaponModel = this->m_bShowWeaponModel;
    BYTE1(this->m_bPaused) = 1;
    v9 = (float *)((char *)this + 96 * m_bShowWeaponModel);
    if ( v9[108] >= -700.0 || v9[110] >= -700.0 )
    {
      if ( !this->m_bAlive )
      {
        Instance = (char *)CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()Instance, aWe011, 0);
      }
      if ( this->m_bAlive == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !this->m_bAlive )
      {
        v10 = (char *)CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v10, aWe011, 1);
      }
      if ( this->m_bAlive == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = (char *)CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v12, aWe011b, v26);
      }
    }
  }
  v13 = (float *)&this->m_Task[35].cmd.bDestRole[7];
  m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
  v32 = *(float *)&this->m_Task[35].bValid * m_DeltaTime;
  v33 = *(float *)&this->m_Task[35].bFinished * m_DeltaTime;
  v15 = v32 + *(float *)&this->m_Task[35].cmd.bDestRole[7];
  *(float *)&v29 = *(float *)&this->m_Task[35].cmd.bDestRole[8] + v33;
  v16 = *(float *)&this->m_Task[35].cmd.bDestRole[9] + m_DeltaTime * *(float *)&this->m_Task[35].bExecuted;
  this->m_Task[35].cmd.bDestRole[8] = v29;
  *(float *)&v31 = v16;
  *(float *)&this->m_Task[35].cmd.bDestRole[7] = v15;
  this->m_Task[35].cmd.bDestRole[9] = v31;
  v17 = this->m_Task[35].fTemp2 - *(float *)&this->m_Task[35].cmd.bDestRole[7];
  *(float *)&v34 = *(float *)&this->m_Task[35].dwID - *(float *)&this->m_Task[35].cmd.bDestRole[8];
  v18 = *(float *)&this->m_Task[35].eMode - *(float *)&this->m_Task[35].cmd.bDestRole[9];
  dword_17AB75C = v34;
  *(float *)&v35 = v18;
  *(float *)&dword_17AB758 = v17;
  dword_17AB760 = v35;
  if ( (gbVec3D *->Length()&dword_17AB758) >= 2.0 )
  {
    (gbVec3D *->Normalize()&dword_17AB758);
    v21 = acos(
            *(float *)&dword_17AB750 * *(float *)&dword_17AB760
          + *(float *)&dword_17AB74C * *(float *)&dword_17AB75C
          + *(float *)&dword_17AB748 * *(float *)&dword_17AB758);
    if ( *(float *)&dword_17AB758 < 0.0 )
      v21 = 6.2831855 - v21;
    v22 = v21 * 57.29578;
    flt_17ABCD4 = v22;
    if ( fabs(v22 - *(float *)&this->m_Task[36].fp) < 1.570796370506287 )
    {
      if ( this->m_pRoleState->IsRoleAlive(this->m_bAlive) )
        return 0;
      BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
      if ( !this->m_bAlive )
      {
        v24 = (char *)CScreenMode::GetInstance();
        (CCBStageRole *->PlaySound()v24, aWe011, v27);
      }
      if ( this->m_bAlive != 4 )
      {
LABEL_43:
        BYTE1(this->m_bPaused) = 0;
        return 0;
      }
    }
    else
    {
      * v13 = (*)this->m_Task[35].fTemp2;
      this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
      this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
      BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
      if ( !this->m_bAlive )
      {
        v23 = (char *)CScreenMode::GetInstance();
        (CCBStageRole *->PlaySound()v23, aWe011, v27);
      }
      if ( this->m_bAlive != 4 )
        goto LABEL_43;
    }
    v25 = (char *)CScreenMode::GetInstance();
    (CCBStageRole *->PlaySound()v25, aWe011b, v27);
    goto LABEL_43;
  }
  * v13 = (*)this->m_Task[35].fTemp2;
  this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
  this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
  BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
  if ( !this->m_bAlive )
  {
    v19 = (char *)CScreenMode::GetInstance();
    (CCBStageRole *->PlaySound()v19, aWe011, v27);
  }
  if ( this->m_bAlive == 4 )
  {
    v20 = (char *)CScreenMode::GetInstance();
    (CCBStageRole *->PlaySound()v20, aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C970
int CCBStageRole::ProcMagic(int _this, int a2)
{
  int v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  int v8; // ecx
  char *Instance; // eax
  double v10; // st7
  int v11; // ecx
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
  if ( CCBRoleState::GetRoleField(*(CCBRoleState **)(this + 4), *(_DWORD *)(this + 284), 23) )
    v19 = 0.44;
  v3 = 96 * *(_DWORD *)(this + 396) + this;
  if ( !*(_BYTE *)(v3 + 506) )
  {
    *(_DWORD *)(this + 6608) = *(_DWORD *)(v3 + 432);
    *(_DWORD *)(this + 6612) = *(_DWORD *)(v3 + 436);
    *(_DWORD *)(this + 6616) = *(_DWORD *)(v3 + 440);
    v4 = *(float *)(this + 6608) - *(float *)(this + 6584);
    *(float *)&v20 = *(float *)(this + 6612) - *(float *)(this + 6588);
    v5 = *(float *)(this + 6616) - *(float *)(this + 6592);
    dword_17AB72C = v20;
    *(float *)&v21 = v5;
    *(float *)&dword_17AB728 = v4;
    dword_17AB730 = v21;
    if ( (gbVec3D *->Length()&dword_17AB728) < 2.0 )
    {
      this->ClearAniMsg(0, 1.0);
      *(_DWORD *)(this + 6584) = *(_DWORD *)(this + 6608);
      *(_DWORD *)(this + 6588) = *(_DWORD *)(this + 6612);
      *(_DWORD *)(this + 6592) = *(_DWORD *)(this + 6616);
      *(_BYTE *)(96 * *(_DWORD *)(this + 396) + this + 505) = 1;
      return 0;
    }
    (gbVec3D *->Normalize()&dword_17AB728);
    v7 = acos(
           *(float *)&dword_17AB720 * *(float *)&dword_17AB730
         + *(float *)&dword_17AB71C * *(float *)&dword_17AB72C
         + *(float *)&dword_17AB718 * *(float *)&dword_17AB728);
    *(float *)(this + 6632) = v7;
    if ( *(float *)&dword_17AB728 < 0.0 )
      *(float *)(this + 6632) = 6.2831855 - v7;
    v8 = 96 * *(_DWORD *)(this + 396);
    *(float *)(this + 6632) = *(float *)(this + 6632) * 57.29578;
    *(_BYTE *)(v8 + this + 506) = 1;
    *(_DWORD *)(96 * *(_DWORD *)(this + 396) + this + 488) = 1065353216;
    *(_DWORD *)(this + 6568) = 32;
    this->IsGrabedBy();
    *(float *)&a4 = *(float *)(this + 6588) - 20.0;
    if ( *(_DWORD *)(this + 284) )
      CEffMgr::Init(
        *(CEffMgr **)(**(_DWORD **)this + 44),
        221,
        *(_DWORD *)(this + 6584),
        a4,
        *(_DWORD *)(this + 6592),
        0);
    else
      CEffMgr::Init(
        *(CEffMgr **)(**(_DWORD **)this + 44),
        222,
        *(_DWORD *)(this + 6584),
        a4,
        *(_DWORD *)(this + 6592),
        0);
    this->ClearBadPushTask(0.0099999998);
    Instance = (char *)CScreenMode::GetInstance();
    (CScreenMode *->AudioSetPosition()Instance, aWe014, 1);
  }
  v10 = (CCBStageRole *->PushBackAllTask()this);
  v11 = 96 * *(_DWORD *)(this + 396) + this;
  if ( *(float *)(v11 + 488) <= 0.0 )
  {
    v13 = *(double *)(**(_DWORD **)this + 64) * 2.5 + v10;
    v18 = v13;
    if ( v13 >= v19 )
    {
      v18 = v19;
      *(_BYTE *)(v11 + 505) = 1;
      v14 = (char *)CScreenMode::GetInstance();
      (CCBStageRole *->PlaySound()v14, aWe014, v17);
    }
  }
  else
  {
    v12 = v10 - *(double *)(**(_DWORD **)this + 64) * 2.5;
    v18 = v12;
    if ( v12 < 0.0 )
    {
      *(_DWORD *)(v11 + 488) = -1054867456;
      *(_DWORD *)(this + 6584) = *(_DWORD *)(this + 6608);
      *(_DWORD *)(this + 6588) = *(_DWORD *)(this + 6612);
      *(_DWORD *)(this + 6592) = *(_DWORD *)(this + 6616);
      *(_DWORD *)(this + 6632) = *(_DWORD *)(this + 6636);
    }
  }
  if ( !CCBRoleState::IsRoleAlive(*(CCBRoleState **)(this + 4), *(_DWORD *)(this + 284)) )
  {
    v18 = v19;
    *(_BYTE *)(96 * *(_DWORD *)(this + 396) + this + 505) = 1;
    v15 = (char *)CScreenMode::GetInstance();
    (CCBStageRole *->PlaySound()v15, aWe014, v17);
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
  __int32 v4; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  long double v9; // st7
  double v10; // st7
  float v11; // edi
  __int32 m_bAlive; // eax
  char *Instance; // eax
  char *v14; // eax
  double v15; // st7
  double v16; // st6
  double m_DeltaTime; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  __int32 v21; // eax
  char *v22; // eax
  char *v23; // eax
  __int32 v24; // eax
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
  v3 = (char *)this + 96 * this->m_bShowWeaponModel;
  if ( v3[506] )
  {
    v11 = a2;
  }
  else
  {
    *((_DWORD *)v3 + 122) = -1054867456;
    v4 = 96 * this->m_bShowWeaponModel;
    LODWORD(this->m_Task[35].fTemp2) = *(__int32 *)((char *)&this->m_ThrowCmdData.dwItemID + v4);
    this->m_Task[35].dwID = *(int *)((char *)&this->m_ThrowCmdData.nSrcRole + v4);
    this->m_Task[35].eMode = *(int *)((char *)&this->m_ThrowCmdData.nDestRole + v4);
    v5 = this->m_Task[35].fTemp2 - *(float *)&this->m_Task[35].cmd.bDestRole[7];
    *(float *)&v29 = *(float *)&this->m_Task[35].dwID - *(float *)&this->m_Task[35].cmd.bDestRole[8];
    v6 = *(float *)&this->m_Task[35].eMode - *(float *)&this->m_Task[35].cmd.bDestRole[9];
    dword_17AB70C = v29;
    *(float *)&v32 = v6;
    *(float *)&dword_17AB708 = v5;
    dword_17AB710 = v32;
    v7 = (gbVec3D *->Length()&dword_17AB708);
    a2a = v7;
    if ( v7 < 2.0 )
    {
      this->m_Task[35].cmd.bDestRole[7] = LODWORD(this->m_Task[35].fTemp2);
      this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
      this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
      BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
      return 0;
    }
    (gbVec3D *->Normalize()&dword_17AB708);
    v9 = acos(
           *(float *)&dword_17AB700 * *(float *)&dword_17AB710
         + *(float *)&dword_17AB6FC * *(float *)&dword_17AB70C
         + *(float *)&dword_17AB6F8 * *(float *)&dword_17AB708);
    *(float *)&this->m_Task[36].fp = v9;
    if ( *(float *)&dword_17AB708 < 0.0 )
      *(float *)&this->m_Task[36].fp = 6.2831855 - v9;
    *(float *)&this->m_Task[36].fp = *(float *)&this->m_Task[36].fp * 57.29578;
    this->m_Task[35].bValid = dword_17AB708;
    v10 = a2a + a2a;
    this->m_Task[35].bFinished = dword_17AB70C;
    this->m_Task[35].bExecuted = dword_17AB710;
    *(float *)&this->m_Task[35].bValid = v10 * *(float *)&this->m_Task[35].bValid;
    *(float *)&this->m_Task[35].bFinished = v10 * *(float *)&this->m_Task[35].bFinished;
    *(float *)&this->m_Task[35].bExecuted = v10 * *(float *)&this->m_Task[35].bExecuted;
    if ( (CCBStageRole *->IsActive()this->m_pRoleState, this->m_bAlive) )
      this->m_Task[35].cmd.bDestRole[3] = 31;
    else
      this->m_Task[35].cmd.bDestRole[3] = 52;
    CCBStageRole::IsGrabedBy((int)this);
    v11 = 0.0;
    BYTE2(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
    CCBStageRole::ClearBadPushTask((int)this, 0.0099999998);
    m_bAlive = this->m_bAlive;
    BYTE1(this->m_bPaused) = 1;
    if ( m_bAlive == 1 )
    {
      Instance = (char *)CScreenMode::GetInstance();
      (CScreenMode *->AudioSetPosition()Instance, aWe012, 1);
    }
    if ( this->m_bAlive == 3 )
    {
      v14 = (char *)CScreenMode::GetInstance();
      (CScreenMode *->AudioSetPosition()v14, aWe013, 1);
    }
  }
  v15 = this->m_Task[35].fTemp2 - *(float *)&this->m_Task[35].cmd.bDestRole[7];
  *(float *)&v30 = *(float *)&this->m_Task[35].dwID - *(float *)&this->m_Task[35].cmd.bDestRole[8];
  v16 = *(float *)&this->m_Task[35].eMode - *(float *)&this->m_Task[35].cmd.bDestRole[9];
  dword_17AB70C = v30;
  *(float *)&v33 = v16;
  *(float *)&dword_17AB708 = v15;
  dword_17AB710 = v33;
  if ( LODWORD(v11) == this->m_Task[36].cmd.nDestRole )
    this->m_ThrowCmdData.bSrcRole[24 * this->m_bShowWeaponModel + 9] = 1120403456;
  if ( *(float *)&this->m_ThrowCmdData.bSrcRole[24 * this->m_bShowWeaponModel + 9] > 0.0
    && (gbVec3D *->Length()&dword_17AB708) > 2.0 )
  {
    m_DeltaTime = this->m_pStage->m_pCBSystem->m_DeltaTime;
    v28 = *(float *)&this->m_Task[35].bValid * m_DeltaTime;
    v31 = *(float *)&this->m_Task[35].bFinished * m_DeltaTime;
    v18 = m_DeltaTime * *(float *)&this->m_Task[35].bExecuted;
    *(float *)&this->m_Task[35].cmd.bDestRole[7] = v28 + *(float *)&this->m_Task[35].cmd.bDestRole[7];
    *(float *)&this->m_Task[35].cmd.bDestRole[8] = v31 + *(float *)&this->m_Task[35].cmd.bDestRole[8];
    *(float *)&this->m_Task[35].cmd.bDestRole[9] = v18 + *(float *)&this->m_Task[35].cmd.bDestRole[9];
  }
  if ( LODWORD(v11) == this->m_Task[36].cmd.bMultiSrcRole && (gbVec3D *->Length()&dword_17AB708) <= 2.0 )
    this->m_ThrowCmdData.bSrcRole[24 * this->m_bShowWeaponModel + 9] = -1054867456;
  (gbVec3D *->Normalize()&dword_17AB708);
  v19 = acos(
          *(float *)&dword_17AB700 * *(float *)&dword_17AB710
        + *(float *)&dword_17AB6FC * *(float *)&dword_17AB70C
        + *(float *)&dword_17AB6F8 * *(float *)&dword_17AB708);
  if ( *(float *)&dword_17AB708 < 0.0 )
    v19 = 6.2831855 - v19;
  v20 = v19 * 57.29578;
  flt_17ABCD8 = v20;
  if ( fabs(v20 - *(float *)&this->m_Task[36].fp) >= 1.570796370506287 )
  {
    this->m_Task[35].cmd.bDestRole[7] = LODWORD(this->m_Task[35].fTemp2);
    this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
    this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
    this->m_ThrowCmdData.bSrcRole[24 * this->m_bShowWeaponModel + 9] = -1054867456;
  }
  if ( LODWORD(v11) == LODWORD(this->m_Task[36].vec1.z) )
  {
    this->m_Task[35].cmd.bDestRole[7] = LODWORD(this->m_Task[35].fTemp2);
    this->m_Task[35].cmd.bDestRole[8] = this->m_Task[35].dwID;
    this->m_Task[35].cmd.bDestRole[9] = this->m_Task[35].eMode;
    BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
    v21 = this->m_bAlive;
    BYTE1(this->m_bPaused) = 0;
    if ( v21 == 1 )
    {
      v22 = (char *)CScreenMode::GetInstance();
      (CCBStageRole *->PlaySound()v22, aWe012, v27);
    }
    if ( this->m_bAlive == 3 )
    {
      v23 = (char *)CScreenMode::GetInstance();
      (CCBStageRole *->PlaySound()v23, aWe013, v27);
    }
  }
  if ( !this->m_pRoleState->IsRoleAlive(this->m_bAlive) )
  {
    BYTE1(this->m_ThrowCmdData.bDestRole[24 * this->m_bShowWeaponModel + 2]) = 1;
    v24 = this->m_bAlive;
    BYTE1(this->m_bPaused) = 0;
    if ( v24 == 1 )
    {
      v25 = (char *)CScreenMode::GetInstance();
      (CCBStageRole *->PlaySound()v25, aWe012, v27);
    }
    if ( this->m_bAlive == 3 )
    {
      v26 = (char *)CScreenMode::GetInstance();
      (CCBStageRole *->PlaySound()v26, aWe013, v27);
    }
  }
  return 0;
}

// 0x0053E310
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void CCBStageRole::PlaySound(CCBStageRole *this, char *name, int a3)
{
  unsigned int v4; // ebp
  unsigned int v5; // kr08_4
  unsigned int v6; // ebp
  int i; // esi
  int j; // edi
  char v9; // al
  unsigned int v10; // [esp+4h] [ebp-20h] BYREF
  char *v11; // [esp+8h] [ebp-1Ch]
  unsigned int v12; // [esp+Ch] [ebp-18h]
  int v13; // [esp+14h] [ebp-10h]
  int v14; // [esp+20h] [ebp-4h]

  if ( (g_nGameFlags & 1) != 0 )
  {
    LOBYTE(v10) = (_BYTE)name;
    std::string::_Tidy(&v10, 0);
    v14 = 0;
    v4 = strlen(&g_SceneMgr.m_info[51624]);
    if ( SceneObj::Update(&v10, v4, 1) )
    {
      qmemcpy(v11, &g_SceneMgr.m_info[51624], v4);
      std::string::_Eos(&v10, v4);
    }
    v13 = 0;
    v5 = strlen(name) + 1;
    v6 = v5 - 1;
    v14 = 1;
    if ( SceneObj::Update(&v10, v5 - 1, 1) )
    {
      qmemcpy(v11, name, v6);
      v12 = v5 - 1;
      v11[v6] = 0;
    }
    for ( i = *(_DWORD *)&this->m_pStage[816]; i != *(_DWORD *)&this->m_pStage[820]; i += 20 )
    {
      for ( j = *(_DWORD *)&this->m_pStage[820]; i != j; i += 20 )
      {
        if ( sub_53DF80(i, (int)&v10) )
          break;
      }
      if ( i == *(_DWORD *)&this->m_pStage[820] )
        break;
      if ( gbSound2DNode::IsPlaying(*(gbSound2DNode **)(i + 16)) )
      {
        gbSound2DNode::Stop(*(gbSound2DNode **)(i + 16));
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
