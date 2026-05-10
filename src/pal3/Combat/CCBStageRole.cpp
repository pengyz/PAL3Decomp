#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageRole.h"

// 0x004ED040
char CCBStageRole::IsActive(int index)
{
  return this->m_pStage[892 * index + 579];
}

// 0x00508930
int sub_508930(int a2, int a3, _DWORD *a4)
{
  int v5; // edx
  _DWORD *v6; // esi
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
  int v32; // [esp+18h] [ebp-34h]
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

  v5 = *(this + 15 * a2 + 611);
  v6 = this + 15 * a2;
  if ( v5 != a4[1] )
    v5 = a4[1];
  v7 = *(this + 2);
  v30 = 0.0;
  v31 = 0;
  v32 = 0;
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
    if ( v6[612] == -1 )
    {
      return 0;
    }
    else
    {
      if ( *((_BYTE *)v6 + 2452) )
      {
        v30 = v41;
        v31 = v42;
        v32 = v43;
      }
      if ( *((_BYTE *)v6 + 2453) )
      {
        v30 = v14;
        v31 = v33;
        v32 = v13;
      }
      v16 = *((_BYTE *)v6 + 2454);
      if ( v16 )
      {
        v17 = *(float **)(*(this + 2) + 4 * v8 + 24);
        v18 = v17[1649];
        v17 += 1649;
        v30 = v18;
        v31 = *((_DWORD *)v17 + 1);
        v32 = *((_DWORD *)v17 + 2);
      }
      v19 = *((_BYTE *)v6 + 2455);
      if ( v19 )
      {
        v20 = a4[3];
        if ( v20 == -1 )
        {
          v30 = v14;
          v31 = v33;
          v32 = v34;
        }
        else
        {
          v21 = *(float **)(*(this + 2) + 4 * v20 + 24);
          v22 = v21[1649];
          v21 += 1649;
          v30 = v22;
          v31 = *((_DWORD *)v21 + 1);
          v32 = *((_DWORD *)v21 + 2);
        }
      }
      if ( !*((_BYTE *)v6 + 2452) && !*((_BYTE *)v6 + 2453) && !v16 && !v19 )
      {
        v30 = *((float *)v6 + 614);
        v31 = v6[615];
        v32 = v6[616];
      }
      if ( *a4 == 269 )
        CEffect::Render(*(int **)(*(_DWORD *)*(this + 2) + 48), v6[612]);
      if ( *a4 == 270 )
        CEffect::Render(*(int **)(*(_DWORD *)*(this + 2) + 44), v6[612]);
      if ( *a4 == 269 )
        return CEffMgr::Init(*(int **)(*(_DWORD *)*(this + 2) + 48), v6[612], SLODWORD(v30), v31, v32, 0);
      else
        return CEffMgr::Init(*(int **)(*(_DWORD *)*(this + 2) + 44), v6[612], SLODWORD(v30), v31, v32, 0);
    }
  }
  else if ( v6[619] == -1 )
  {
    return 0;
  }
  else
  {
    if ( *((_BYTE *)v6 + 2480) )
    {
      v30 = v41;
      v31 = v42;
      v32 = v43;
    }
    if ( *((_BYTE *)v6 + 2481) )
    {
      v30 = v14;
      v31 = v33;
      v32 = v13;
    }
    v23 = *((_BYTE *)v6 + 2482);
    if ( v23 )
    {
      v24 = *(float **)(*(this + 2) + 4 * v8 + 24);
      v25 = v24[1649];
      v24 += 1649;
      v30 = v25;
      v31 = *((_DWORD *)v24 + 1);
      v32 = *((_DWORD *)v24 + 2);
    }
    v26 = *((_BYTE *)v6 + 2483);
    if ( v26 )
    {
      v27 = a4[3];
      if ( v27 == -1 )
      {
        v30 = v14;
        v31 = v33;
        v32 = v34;
      }
      else
      {
        v28 = *(float **)(*(this + 2) + 4 * v27 + 24);
        v29 = v28[1649];
        v28 += 1649;
        v30 = v29;
        v31 = *((_DWORD *)v28 + 1);
        v32 = *((_DWORD *)v28 + 2);
      }
    }
    if ( !*((_BYTE *)v6 + 2480) && !*((_BYTE *)v6 + 2481) && !v23 && !v26 )
    {
      v30 = *((float *)v6 + 621);
      v31 = v6[622];
      v32 = v6[623];
    }
    if ( *a4 == 269 )
      CEffect::Render(*(int **)(*(_DWORD *)*(this + 2) + 48), v6[619]);
    if ( *a4 == 270 )
      CEffect::Render(*(int **)(*(_DWORD *)*(this + 2) + 44), v6[619]);
    if ( *a4 == 269 )
      return CEffMgr::Init(*(int **)(*(_DWORD *)*(this + 2) + 48), v6[619], SLODWORD(v30), v31, v32, 0);
    else
      return CEffMgr::Init(*(int **)(*(_DWORD *)*(this + 2) + 44), v6[619], SLODWORD(v30), v31, v32, 0);
  }
}

// 0x005090F0
int sub_5090F0()
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
int sub_509140()
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
int sub_509190()
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
int sub_5091E0()
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
int sub_509280()
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
int sub_5092A0()
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
  v3 = &this->m_pStage[444];
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
int sub_509410(int this)
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
char sub_509540(int this, unsigned int a2)
{
  void *v3; // eax
  int v4; // eax
  char Buffer[260]; // [esp+8h] [ebp-910h] BYREF
  char pExceptionObject[1024]; // [esp+10Ch] [ebp-80Ch] BYREF
  char ArgList; // [esp+50Ch] [ebp-40Ch] BYREF
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
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_8, 120),
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
    Buffer->LoadModel(0);
    this->ProcCatchED();
  }
  *(_BYTE *)(this + 274) = 0;
  return 1;
}

// 0x00509690
char sub_509690()
{
  void *v2; // edi

  if ( !*(this + 73) )
    return 1;
  Actor::UpdateAllActions();
  v2 = (void *)*(this + 73);
  if ( v2 )
  {
    sub_40EE00(*(this + 73));
    operator delete(v2);
  }
  *(this + 73) = 0;
  return 1;
}

// 0x005096D0
char CCBStageRole::IsAtProtectPos(int a2, int a3, int a4)
{
  int inited; // eax
  int v6; // eax
  unsigned int v7; // eax
  char *v8; // edi
  char *v9; // esi
  char v10; // cl
  const char *v11; // edi
  unsigned int v12; // edx
  const char *v13; // edi
  int v14; // eax
  _DWORD *v15; // ecx
  int v16; // esi
  _DWORD *v17; // eax
  int v18; // eax
  _DWORD *v19; // ecx
  int v20; // esi
  int v21; // eax
  char v22; // dl
  unsigned int v23; // eax
  const char *v25; // [esp-8h] [ebp-11Ch]
  float v26; // [esp+Ch] [ebp-108h]
  char Buffer[260]; // [esp+10h] [ebp-104h] BYREF

  CCBStageRole::GetRotAngle((int)this);
  *(_DWORD *)&this->m_pStage[284] = a2;
  *(_DWORD *)&this->m_pStage[288] = a3;
  this->m_pStage[264] = 1;
  this->m_pStage[265] = 1;
  this->m_pStage[272] = 1;
  *(_DWORD *)&this->m_pStage[6632] = 0;
  if ( a2 >= 5 && a2 < 11 )
  {
    if ( strcmp((const char *)(CCBRoleState::InitUI(*(CCBRoleState **)&this->m_pStage[4], a2) + 8), &this->m_pStage[8]) )
    {
      v25 = (const char *)(CCBRoleState::InitUI(*(CCBRoleState **)&this->m_pStage[4], a2) + 8);
      inited = CCBRoleState::InitUI(*(CCBRoleState **)&this->m_pStage[4], a2);
      sprintf(Buffer, "role\\%s\\%s.ini", (const char *)(inited + 8), v25);
      v6 = *(_DWORD *)&this->m_pStage[284];
      if ( v6 < 5 || v6 >= 11 || (int)g_pVFileSys->FileExistNum(Buffer) > 0 )
      {
        CCBRoleState::InitUI(*(CCBRoleState **)&this->m_pStage[4], a2);
        Actor::LoadModel(*(Actor **)&this->m_pStage[292]);
        v11 = (const char *)(CCBRoleState::InitUI(*(CCBRoleState **)&this->m_pStage[4], a2) + 8);
        v12 = strlen(v11) + 1;
        v13 = &v11[v12];
        qmemcpy(&this->m_pStage[8], &v13[-v12], 4 * (v12 >> 2));
        v9 = (char *)&v13[4 * (v12 >> 2) - v12];
        v8 = &this->m_pStage[4 * (v12 >> 2) + 8];
        v10 = v12;
      }
      else
      {
        Actor::LoadModel(*(Actor **)&this->m_pStage[292]);
        v7 = strlen(a203) + 1;
        qmemcpy(&this->m_pStage[8], a203, 4 * (v7 >> 2));
        v9 = &a203[4 * (v7 >> 2)];
        v8 = &this->m_pStage[4 * (v7 >> 2) + 8];
        v10 = v7;
      }
      qmemcpy(v8, v9, v10 & 3);
    }
    (int *->ProcCatchED()this->m_pStage);
  }
  if ( CCBStageRole::IsActive(*(CCBStageRole **)&this->m_pStage[4], a2) )
    *(_DWORD *)&this->m_pStage[6568] = 32;
  else
    *(_DWORD *)&this->m_pStage[6568] = 50;
  CCBStageRole::IsGrabedBy((int)this);
  if ( CCBStageRole::IsActive(*(CCBStageRole **)&this->m_pStage[4], a2) == 1 )
  {
    v14 = *(_DWORD *)this->m_pStage;
    v15 = *(_DWORD **)&this->m_pStage[4];
    *(_DWORD *)&this->m_pStage[6636] = 1110704128;
    v16 = *(_DWORD *)(v14 + 20);
    v17 = (_DWORD *)(v16 + 12 * v15->IsAllWeDead(a2) + 8);
  }
  else
  {
    v18 = *(_DWORD *)this->m_pStage;
    v19 = *(_DWORD **)&this->m_pStage[4];
    *(_DWORD *)&this->m_pStage[6636] = -1022951424;
    v20 = *(_DWORD *)(v18 + 20);
    v17 = (_DWORD *)(v20 + 12 * v19->IsAllWeDead(a2) + 176);
  }
  *(_DWORD *)&this->m_pStage[6596] = *v17;
  *(_DWORD *)&this->m_pStage[6600] = v17[1];
  *(_DWORD *)&this->m_pStage[6604] = v17[2];
  *(_DWORD *)&this->m_pStage[6584] = *(_DWORD *)&this->m_pStage[6596];
  *(_DWORD *)&this->m_pStage[6588] = *(_DWORD *)&this->m_pStage[6600];
  *(_DWORD *)&this->m_pStage[6592] = *(_DWORD *)&this->m_pStage[6604];
  v26 = *(float *)&this->m_pStage[6636];
  v21 = *(_DWORD *)&this->m_pStage[284];
  *(float *)&this->m_pStage[6632] = v26;
  if ( v21 >= 5 && v21 < 11 )
  {
    if ( !*(_BYTE *)(*(_DWORD *)&this->m_pStage[4] + 536) )
      goto LABEL_24;
    goto LABEL_23;
  }
  if ( (unsigned int)v21 <= 4 && *(_BYTE *)(*(_DWORD *)&this->m_pStage[4] + 537) )
LABEL_23:
    *(float *)&this->m_pStage[6632] = v26 + 180.0;
LABEL_24:
  CCBStageRole::ClearAniMsg((int)this, 0, 1.0);
  v22 = *(_BYTE *)(CCBRoleState::InitUI(*(CCBRoleState **)&this->m_pStage[4], *(_DWORD *)&this->m_pStage[284]) + 878);
  v23 = *(_DWORD *)&this->m_pStage[284];
  this->m_pStage[372] = v22;
  if ( v23 <= 4 )
    this->m_pStage[372] = 0;
  return 1;
}

// 0x005099A0
char __usercall CCBStageRole::IsTaskFinished@<al>(_DWORD *this@<ecx>, int a2@<edi>)
{
  char result; // al
  Actor *v4; // ecx
  int v5; // eax
  int inited; // eax
  int v7; // eax
  int v8; // ecx
  CCBStageRole *Instance; // eax
  CCBStageRole *v10; // eax
  int v11; // [esp-8h] [ebp-14h]
  float scale; // [esp+4h] [ebp-8h]
  float v13; // [esp+8h] [ebp-4h]

  result = *((_BYTE *)this + 264);
  if ( result )
  {
    v4 = (Actor *)*(this + 73);
    if ( v4 )
    {
      scale = 1.3;
      if ( !*((_BYTE *)this + 380) )
      {
        v5 = *(this + 1642);
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
      (Actor *->SetTimeScale()*(this + 73), v13);
      if ( *(_DWORD *)((CCBRoleState *->InitUI()*(this + 1), *(this + 71)) + 848) )
      {
        inited = (CCBRoleState *->InitUI()*(this + 1), *(this + 71));
        gbGeomNode::SetBladeTimeScale(*(gbGeomNode **)(inited + 848), v13);
      }
      if ( *(_DWORD *)((CCBRoleState *->InitUI()*(this + 1), *(this + 71)) + 860) )
      {
        v7 = (CCBRoleState *->InitUI()*(this + 1), *(this + 71));
        gbGeomNode::SetBladeTimeScale(*(gbGeomNode **)(v7 + 860), v13);
      }
      if ( this->ForceDelTaskByPFN() && !*((_BYTE *)this + 380) )
      {
        CCBStageRole::ClearBadPushTask((int)this, 0.0099999998);
        if ( !CCBRoleState::IsRoleAlive(*(CCBRoleState **)(*(_DWORD *)*this + 16), *(this + 71)) )
          *((_BYTE *)this + 272) = 0;
      }
      v8 = *(this + 73);
      *(this + 1660) = 0;
      if ( gbVisNode::PopMessage(*(gbVisNode **)(v8 + 16), (struct gbNodeMsgObj *)&dword_17AB9C8) == 1
        && dword_17AB9C8 == 1 )
      {
        *(this + 1660) = dword_17AB9CC;
      }
      if ( !*((_BYTE *)this + 380) )
        (CCBStageRole *->Grab()this, *(this + 1660));
      if ( !*(this + 71) && *(this + 1642) != 31 )
      {
        Instance = (CCBStageRole *)CScreenMode::GetInstance();
        Instance->PlaySound(aWe011, a2);
      }
      if ( *(this + 71) == 4 && *(this + 1642) != 31 )
      {
        v10 = (CCBStageRole *)CScreenMode::GetInstance();
        v10->PlaySound(aWe011b, v11);
      }
      return (Actor *->QueryState()*(this + 73));
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
  int v9; // esi
  int v10; // ebx
  int dwItemID; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  struct gbVec3D *LastBladePos; // ecx
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
  (gbMatrix4 *->gbMatrix4()v25);
  m_fBlend = this->m_bAlive;
  memset(&v23, 0, sizeof(v23));
  v20 = 0;
  if ( SLODWORD(m_fBlend) >= 5 && SLODWORD(m_fBlend) < 11 )
    (int *->ProcPursueRole()this, 0, 0, 0);
  if ( this->m_fTimeScale )
  {
    CCBStageRole::DoTask((int)this, (float *)&v23.x);
    m_fBlend_low = LODWORD(this->m_bAlive);
    *(float *)&v23.y = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 10.0 + (double)m_fBlend_low) * 5.0
                     + *(float *)&v23.y
                     + 6.0;
    if ( (unsigned int)m_fBlend_low <= 4
      || m_fBlend_low >= 5 && m_fBlend_low < 11 && (float *->ForceEndTaskByPFN()this) )
    {
      (gbCamera *->PointWorldToScr()&this->m_pStage->m_pCam->OrthoSize, &v23, &v21, &v22);
      v5 = this->m_pRoleState->SetRoleField(LODWORD(this->m_bAlive), 0);
      v6 = this->m_pRoleState->SetRoleField(LODWORD(this->m_bAlive), 1);
      RoleType = this->m_pRoleState->GetRoleType(LODWORD(this->m_bAlive));
      if ( LODWORD(this->m_bAlive) == 10 && this->m_pRoleState->m_nBossRound || RoleType && v5 > v6 / 4 )
        strcpy(byte_17AB8B8, *(const char **)(this->m_pRoleState->InitUI(LODWORD(this->m_bAlive)) + 888));
      else
        sprintf(byte_17AB8B8, "%d/%d", v5, v6);
      v8 = 10 * strlen(byte_17AB8B8);
      v9 = (__int64)((v21 + 1.0) * (double)MEMORY[0xBFD6D0] * 0.5);
      v10 = (__int64)((1.0 - v22) * (double)MEMORY[0xBFD6D4] * 0.5);
      if ( v9 >= 0 )
      {
        if ( v9 > (int)(MEMORY[0xBFD6D0] - v8) )
          v9 = MEMORY[0xBFD6D0] - v8;
      }
      else
      {
        v9 = 0;
      }
      if ( v10 >= 20 )
      {
        if ( v10 > MEMORY[0xBFD6D4] )
          v10 = MEMORY[0xBFD6D4];
      }
      else
      {
        v10 = 20;
      }
      sub_4DFC40((char *)this->m_pStage->?.y, byte_17AB8B8, v9, v10, -1);
      if ( LODWORD(this->m_bAlive) > 4 )
        (int *->ProcPursueRole()this, v9, v10, 1);
    }
  }
  if ( BYTE1(this->m_pStage->m_pCBSystem->m_bFiveNimbus) && dword_17A990C == 1
    || this->? && (this->m_bPaused || SLODWORD(this->m_bAlive) < 5) )
  {
    a2->Push();
    a2->Translate((struct gbVec3D *)&this->?[36].cmd.bMultiDestRole);
    a2->Rotate(*(float *)this->?[36].cmd.bDestRole, (struct gbVec3D *)&dword_17AB9B8);
    dwItemID = this->?[36].cmd.dwItemID;
    switch ( dword_56FE98[dwItemID] )
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
    v12 = LODWORD(this->m_bAlive);
    if ( !v12 && (dwItemID == 39 || dwItemID == 49) )
      v20 = 0;
    if ( v12 == 3 )
      v20 = 257;
    if ( v12 == 1 )
      v20 = 257;
    if ( (v12 == 2 || v12 == 4) && dwItemID == 46 )
      v20 = 256;
    if ( this->? )
    {
      if ( this->m_vecLen > 0.0 || (LOBYTE(v20) = 0, this->m_vecLen >= 0.0) )
        LOBYTE(v20) = 1;
      if ( this->? <= 0.0 && this->? < 0.0 )
        goto LABEL_64;
    }
    else if ( !HIBYTE(v20) )
    {
LABEL_64:
      if ( (_BYTE)v20 && *(_DWORD *)(this->m_pRoleState->InitUI(LODWORD(this->m_bAlive)) + 848) )
      {
        a2->Push();
        gbActor::GetTagNodeTM(*(gbActor **)(this->m_bFlash + 16), (struct gbMatrix4 *)v25, aTagWeapon2);
        a2->MultMatrix((struct gbMatrix4 *)v25);
        inited = this->m_pRoleState->InitUI(LODWORD(this->m_bAlive));
        (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(inited + 848) + 16))(*(_DWORD *)(inited + 848), 0);
        a2->Pop();
      }
      if ( this->? )
      {
        m_pStage = this->m_pStage;
        m_bShowWeaponModel = this->m_vThrowVec;
        v24[0] = sin(this->m_pStage->m_pCBSystem->m_fTimeFund * 7.8000002) * 0.34999999 + 0.64999998;
        v24[1] = v24[0];
        v24[2] = v24[0];
        if ( m_bShowWeaponModel )
        {
          gbRenderEffect::SetVariant(
            *(gbRenderEffect **)(*(_DWORD *)m_pStage->m_TempStorageWPX + 2440),
            PARAM_HANDLE_SPECULAR,
            v24);
          (Actor *->DispatchAction()this->m_bFlash,
            *(_DWORD *)(*(_DWORD *)this->m_pStage->m_TempStorageWPX + 2440));
        }
        else
        {
          gbRenderEffect::SetVariant(
            *(gbRenderEffect **)(*(_DWORD *)m_pStage->m_TempStorageWPX + 2436),
            PARAM_HANDLE_SPECULAR,
            v24);
          (Actor *->DispatchAction()this->m_bFlash,
            *(_DWORD *)(*(_DWORD *)this->m_pStage->m_TempStorageWPX + 2436));
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
      v13 = this->m_pRoleState->InitUI(LODWORD(this->m_bAlive));
      (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(v13 + 860) + 16))(*(_DWORD *)(v13 + 860), 0);
      a2->Pop();
      if ( LODWORD(this->m_bAlive) == 3 && *(_BYTE *)(g_SceneMgr.?[0].?.points[219].y + 613) == 3 )
      {
        v14 = this->m_pRoleState->InitUI(3);
        LastBladePos = gbGeomNode::GetLastBladePos(*(gbGeomNode **)(v14 + 860), 0);
        if ( LastBladePos )
        {
          v16 = this->m_pStage->m_pCBSystem->m_DeltaTime + flt_17ABCCC;
          flt_17ABCCC = v16;
          if ( v16 >= 0.050000001 )
          {
            this->m_pStage->m_pCBSystem->m_p3DSpark->m_Spark->CreateOne(LastBladePos->x, LastBladePos->y, LastBladePos->z);
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
char sub_50A1A0(char a2)
{
  *(this + 272) = a2;
  return a2;
}

// 0x0050A1B0
int sub_50A1B0(int this)
{
  if ( CCBRoleState::GetRoleField(*(_BYTE **)(this + 4), *(_DWORD *)(this + 284), 23) )
    return CCBStageRole::ClearAniMsg(1, 0.44);
  else
    return CCBStageRole::ClearAniMsg(0, 1.0);
}

// 0x0050A1F0
char sub_50A1F0(char a2)
{
  *(this + 265) = a2;
  return a2;
}

// 0x0050A200
char sub_50A200(char a2)
{
  *(this + 266) = a2;
  return a2;
}

// 0x0050A210
int sub_50A210(int this)
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
int sub_50A260(int this)
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
void sub_50A2B0(int a2)
{
  int *v3; // eax
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
  v3 = (int *)(*(_DWORD *)(*(_DWORD *)this + 4 * a2 + 24) + 6584);
  dword_17AB898 = *v3;
  dword_17AB89C = v3[1];
  dword_17AB8A0 = v3[2];
  v4 = *(float *)&dword_17AB898 - *(this + 1646);
  *(float *)&v7 = *(float *)&dword_17AB89C - *(this + 1647);
  v5 = *(float *)&dword_17AB8A0 - *(this + 1648);
  dword_17AB8AC = v7;
  *(float *)&v8 = v5;
  *(float *)&dword_17AB8A8 = v4;
  dword_17AB8B0 = v8;
  (gbVec3D *->Normalize()&dword_17AB8A8);
  v6 = acos(
         *(float *)&dword_17AB890 * *(float *)&dword_17AB8B0
       + *(float *)&dword_17AB88C * *(float *)&dword_17AB8AC
       + *(float *)&dword_17AB888 * *(float *)&dword_17AB8A8);
  *(this + 1658) = v6;
  if ( *(float *)&dword_17AB8A8 < 0.0 )
    *(this + 1658) = 6.2831855 - v6;
  *(this + 1658) = *(this + 1658) * 57.29578;
}

// 0x0050A500
bool sub_50A500(char a1, int a2, int a3, int a4, int a5, int a6)
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
double sub_50A5D0(float *a2)
{
  double v3; // st7
  double v4; // st6
  double v6; // st7
  float v7; // [esp+4h] [ebp-18h] BYREF
  float v8; // [esp+8h] [ebp-14h]
  float v9; // [esp+Ch] [ebp-10h]
  float v10; // [esp+14h] [ebp-8h]
  float v11; // [esp+18h] [ebp-4h]

  if ( (byte_17AB884 & 1) == 0 )
  {
    v7 = 0.0;
    byte_17AB884 |= 1u;
    v8 = 0.0;
    v9 = 1.0;
    dword_17AB878 = 0;
    dword_17AB87C = 0;
    dword_17AB880 = 1065353216;
    atexit(nullsub_36);
  }
  v3 = *a2 - *(this + 1646);
  v10 = a2[1] - *(this + 1647);
  v4 = a2[2] - *(this + 1648);
  v8 = v10;
  v11 = v4;
  v7 = v3;
  v9 = v11;
  if ( (gbVec3D *->Length()&v7) <= 0.0 )
    return 0.0;
  (gbVec3D *->Normalize()&v7);
  v6 = acos(v8 * *(float *)&dword_17AB87C + v9 * *(float *)&dword_17AB880 + *(float *)&dword_17AB878 * v7);
  if ( v7 < 0.0 )
    v6 = 6.2831855 - v6;
  return v6 * 57.29578;
}

// 0x0050A6F0
bool sub_50A6F0()
{
  return *(this + 98) == 0;
}

// 0x0050A700
bool sub_50A700()
{
  double v1; // st7
  double v2; // st6
  float v4; // [esp+4h] [ebp-14h]
  float v5; // [esp+8h] [ebp-10h]
  float v6[3]; // [esp+Ch] [ebp-Ch] BYREF

  v1 = *(this + 1646) - *(this + 1649);
  v4 = *(this + 1647) - *(this + 1650);
  v2 = *(this + 1648) - *(this + 1651);
  v6[1] = v4;
  v5 = v2;
  v6[0] = v1;
  v6[2] = v5;
  return (gbVec3D *->Length()v6) <= 13.0;
}

// 0x0050A770
bool sub_50A770(int a2, int a3)
{
  int v4; // eax
  float v5; // ecx
  float *v6; // eax
  float *v7; // ecx
  double v8; // st7
  double v9; // st6
  int v10; // edx
  float *v11; // eax
  double v12; // st7
  double v13; // st7
  double v14; // st6
  float v16; // [esp+4h] [ebp-30h] BYREF
  float v17; // [esp+8h] [ebp-2Ch]
  float v18; // [esp+Ch] [ebp-28h]
  float v19; // [esp+10h] [ebp-24h] BYREF
  float v20; // [esp+14h] [ebp-20h]
  float v21; // [esp+18h] [ebp-1Ch]
  float v22; // [esp+20h] [ebp-14h]
  float v23; // [esp+24h] [ebp-10h]
  float v24; // [esp+2Ch] [ebp-8h]
  float v25; // [esp+30h] [ebp-4h]

  v16 = 0.0;
  v17 = 0.0;
  v4 = *((_DWORD *)this + 71);
  v18 = 0.0;
  v19 = 0.0;
  v20 = 0.0;
  v21 = 0.0;
  if ( v4 )
    return 0;
  v5 = *this;
  v6 = *(float **)(LODWORD(v5) + 4 * a2 + 24);
  v7 = (float *)(*(_DWORD *)(LODWORD(v5) + 4 * a3 + 24) + 6596);
  v6 += 1649;
  v8 = *v7 - *v6;
  v22 = v7[1] - v6[1];
  v9 = v7[2] - v6[2];
  v17 = v22;
  v23 = v9;
  v16 = v8;
  v18 = v23;
  (gbVec3D *->Normalize()&v16);
  v10 = *(_DWORD *)this;
  v16 = v16 * 40.0;
  v17 = v17 * 40.0;
  v18 = v18 * 40.0;
  v11 = *(float **)(v10 + 4 * a2 + 24);
  v12 = v16 + v11[1649];
  v22 = v17 + v11[1650];
  v23 = v18 + v11[1651];
  v16 = v12;
  v18 = v23;
  v17 = v22;
  v13 = *(this + 1646) - v12;
  v24 = *(this + 1647) - v22;
  v14 = *(this + 1648) - v23;
  v20 = v24;
  v25 = v14;
  v19 = v13;
  v21 = v25;
  return (gbVec3D *->Length()&v19) <= 20.0;
}

// 0x0050A8E0
char sub_50A8E0(int a2)
{
  *(this + 1641) = a2;
  return 1;
}

// 0x0050A8F0
char sub_50A8F0(int this, int a2, char a3)
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
char CCBStageRole::GetCurrentTask(int this, int a2)
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
int sub_50A960(int this)
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
_DWORD * CCBStageRole::DoTask(int this, float *a2)
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
  *a2 = *Center;
  a2[1] = Center[1];
  a2[2] = Center[2];
  a2[1] = *(float *)(this + 364) * 0.5 + a2[1] + 10.0;
  result = (_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(this + 284));
  if ( *result == 707 )
    a2[1] = a2[1] - 80.0;
  return result;
}

// 0x0050AA60
void sub_50AA60(int this, float a2)
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
double sub_50AAE0()
{
  int v1; // eax
  float v3; // [esp+4h] [ebp-4h] BYREF

  v1 = *(this + 73);
  v3 = 0.0;
  if ( gbVisNode::GetBlend(*(gbVisNode **)(v1 + 16), &v3) )
    return v3;
  else
    return 1.0;
}

// 0x0050AB10
void sub_50AB10(int this, char a2, float a3)
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
int sub_50AC50(int a2, char a3)
{
  int result; // eax

  result = a2;
  if ( a2 > 0 )
  {
    sprintf(byte_17AB818, "z%02d", a2);
    if ( (byte_1895558 & 1) == 0 )
    {
      byte_1895558 |= 1u;
      g_nCursorState->Reset();
      atexit(nullsub_1);
    }
    result = g_nCursorState->GetEditorTaskDescription((unsigned __int8 *)byte_17AB818);
    if ( a3 || result != *(this + 1668) )
    {
      *(this + 1668) = result;
      byte_17AB818->SetVisible(0, 0);
      return (*(int (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(*(this + 73) + 16) + 24))(
               *(_DWORD *)(*(this + 73) + 16),
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
    v12 = &this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 416];
    *(_DWORD *)v12 = a2;
    *((_DWORD *)v12 + 1) = a3;
    *((_DWORD *)v12 + 2) = a4;
    *((_DWORD *)v12 + 3) = a5;
    this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 504] = 1;
    this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 506] = 0;
    this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 505] = 0;
    *(_DWORD *)&this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 496] = CCBSystem::ProcProtect(**(_DWORD ***)this->m_pStage);
    v13 = &this->m_pStage[96 * *(_DWORD *)&this->m_pStage[392] + 432];
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
char sub_50B290(int a2)
{
  int v2; // ebx
  int v4; // eax

  v2 = a2;
  if ( a2 == 63 )
  {
    memset(this + 1616, 0, 0x60u);
    --*(this + 98);
    return 1;
  }
  else
  {
    if ( a2 < *(this + 98) )
    {
      v4 = (int)(this + 24 * a2 + 104);
      do
      {
        ++v2;
        qmemcpy((void *)v4, (const void *)(v4 + 96), 0x60u);
        v4 += 96;
      }
      while ( v2 < *(this + 98) );
    }
    memset(this + 24 * (*(this + 98))-- + 104, 0, 0x60u);
    return 1;
  }
}

// 0x0050B330
char CCBStageRole::GetCurrentState()
{
  char *v1; // eax
  int v2; // edx

  v1 = &this->m_pStage[496];
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
int sub_50B360()
{
  int result; // eax

  if ( *(this + 71) < 5 )
  {
    aZ01->GetAnimDuration();
    aZ09->GetAnimDuration();
    aZ06->GetAnimDuration();
    aZ03->GetAnimDuration();
    aZ04->GetAnimDuration();
    aZ05->GetAnimDuration();
    Actor::GetAnimDuration(&unk_5888D0);
    Actor::GetAnimDuration(&unk_5888C8);
    Actor::GetAnimDuration(&unk_5888C4);
    return Actor::GetAnimDuration(&aNghOpenObjD);
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
      v3 = &this->m_pStage[96 * result + 416];
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
char sub_50B580(int a2, int a3, char a4)
{
  int v5; // edi
  void (__thiscall ***v6)(_DWORD, int); // ecx
  int v7; // ebx
  void (__thiscall ***v8)(_DWORD, int); // ecx
  void (__thiscall ***v9)(_DWORD, int); // ecx
  void (__thiscall ***v10)(_DWORD, int); // ecx
  void (__thiscall ***v11)(_DWORD, int); // ecx
  void (__thiscall ***v12)(_DWORD, int); // ecx
  void (__thiscall ***v13)(_DWORD, int); // ecx
  void (__thiscall ***v14)(_DWORD, int); // ecx
  void (__thiscall ***v15)(_DWORD, int); // ecx
  void (__thiscall ***v16)(_DWORD, int); // ecx
  void (__thiscall ***v17)(_DWORD, int); // ecx
  void (__thiscall ***v18)(_DWORD, int); // ecx
  void (__thiscall ***v19)(_DWORD, int); // ecx
  void (__thiscall ***v20)(_DWORD, int); // ecx
  void (__thiscall ***v21)(_DWORD, int); // ecx
  void (__thiscall ***v22)(_DWORD, int); // ecx
  void (__thiscall ***v23)(_DWORD, int); // ecx
  void (__thiscall ***v24)(_DWORD, int); // ecx
  char result; // al
  void (__thiscall ***v26)(_DWORD, int); // ecx
  void (__thiscall ***v27)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v28)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v29)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v30)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v31)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v32)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v33)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v34)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v35)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v36)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v37)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v38)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v39)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v40)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v41)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v42)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v43)(_DWORD, _DWORD); // ecx
  void (__thiscall ***v44)(_DWORD, _DWORD); // ecx
  int (__thiscall ***v45)(_DWORD, _DWORD); // ecx

  v5 = *(_DWORD *)(*(_DWORD *)*this + 4);
  if ( a4 )
  {
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 6) )
    {
      v6 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 176);
      (**v6)(v6, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 176), a2, a3);
      v7 = a2 + 24;
    }
    else
    {
      v7 = a2;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 7) )
    {
      v8 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 220);
      (**v8)(v8, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 220), v7, a3);
      v7 += 24;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 8) )
    {
      v9 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 264);
      (**v9)(v9, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 264), v7, a3);
      v7 += 24;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 9) )
    {
      v10 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 308);
      (**v10)(v10, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 308), v7, a3);
      v7 += 24;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 12) )
    {
      v11 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 440);
      (**v11)(v11, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 440), v7, a3);
      v7 += 24;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 13) )
    {
      v12 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 484);
      (**v12)(v12, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 484), v7, a3);
      v7 += 24;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 10) )
    {
      v13 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 352);
      (**v13)(v13, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 352), v7, a3);
      v7 += 24;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 11) )
    {
      v14 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 396);
      (**v14)(v14, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 396), v7, a3);
      v7 += 24;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 14) )
    {
      v15 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 528);
      (**v15)(v15, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 528), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 15) )
    {
      v16 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 572);
      (**v16)(v16, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 572), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 16) )
    {
      v17 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 616);
      (**v17)(v17, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 616), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 17) )
    {
      v18 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 660);
      (**v18)(v18, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 660), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 18) )
    {
      v19 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 704);
      (**v19)(v19, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 704), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 19) )
    {
      v20 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 748);
      (**v20)(v20, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 748), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 20) )
    {
      v21 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 792);
      (**v21)(v21, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 792), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 21) )
    {
      v22 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 836);
      (**v22)(v22, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 836), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 22) )
    {
      v23 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 880);
      (**v23)(v23, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 880), v7, a3);
      v7 += 20;
    }
    if ( (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 23) )
    {
      v24 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 924);
      (**v24)(v24, 1);
      UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 924), v7, a3);
      v7 += 20;
    }
    result = (_BYTE *->GetRoleField()*(this + 1), *(this + 71), 26);
    if ( result )
    {
      v26 = *(void (__thiscall ****)(_DWORD, int))(v5 + 4 * *(this + 71) + 968);
      (**v26)(v26, 1);
      return UIWnd::ScreenToClient(*(_DWORD **)(v5 + 4 * *(this + 71) + 968), v7, a3);
    }
  }
  else
  {
    v27 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 176);
    (**v27)(v27, 0);
    v28 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 220);
    (**v28)(v28, 0);
    v29 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 264);
    (**v29)(v29, 0);
    v30 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 308);
    (**v30)(v30, 0);
    v31 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 352);
    (**v31)(v31, 0);
    v32 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 396);
    (**v32)(v32, 0);
    v33 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 440);
    (**v33)(v33, 0);
    v34 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 484);
    (**v34)(v34, 0);
    v35 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 528);
    (**v35)(v35, 0);
    v36 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 572);
    (**v36)(v36, 0);
    v37 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 616);
    (**v37)(v37, 0);
    v38 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 660);
    (**v38)(v38, 0);
    v39 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 704);
    (**v39)(v39, 0);
    v40 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 748);
    (**v40)(v40, 0);
    v41 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 792);
    (**v41)(v41, 0);
    v42 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 836);
    (**v42)(v42, 0);
    v43 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 880);
    (**v43)(v43, 0);
    v44 = *(void (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 924);
    (**v44)(v44, 0);
    v45 = *(int (__thiscall ****)(_DWORD, _DWORD))(v5 + 4 * *(this + 71) + 968);
    return (**v45)(v45, 0);
  }
  return result;
}

// 0x0050BBD0
int sub_50BBD0(int this)
{
  unsigned int v2; // eax
  _BYTE *v3; // ecx
  int v5; // eax

  v2 = *(_DWORD *)(this + 284);
  v3 = *(_BYTE **)(this + 4);
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
  _DWORD *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  int v8; // eax
  float *v9; // ecx
  char *v10; // eax
  char *Instance; // eax
  char *v12; // eax
  _DWORD *v13; // edi
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st6
  CCBStageRole *v19; // eax
  CCBStageRole *v20; // eax
  double v21; // st7
  double v22; // st7
  CCBStageRole *v23; // eax
  CCBStageRole *v24; // eax
  CCBStageRole *v25; // eax
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
  v3 = this + 24 * *(this + 99);
  if ( !*((_BYTE *)v3 + 506) )
  {
    *(this + 1652) = v3[108];
    *(this + 1653) = v3[109];
    *(this + 1654) = v3[110];
    v4 = *((float *)this + 1652) - *((float *)this + 1646);
    *(float *)&v28 = *((float *)this + 1653) - *((float *)this + 1647);
    v5 = *((float *)this + 1654) - *((float *)this + 1648);
    dword_17AB78C = v28;
    *(float *)&v30 = v5;
    *(float *)&dword_17AB788 = v4;
    dword_17AB790 = v30;
    if ( (gbVec3D *->Length()&dword_17AB788) < 2.0 )
    {
      *(this + 1646) = *(this + 1652);
      *(this + 1647) = *(this + 1653);
      *(this + 1648) = *(this + 1654);
      *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
      return 0;
    }
    (gbVec3D *->Normalize()&dword_17AB788);
    v7 = acos(
           *(float *)&dword_17AB780 * *(float *)&dword_17AB790
         + *(float *)&dword_17AB77C * *(float *)&dword_17AB78C
         + *(float *)&dword_17AB778 * *(float *)&dword_17AB788);
    *((float *)this + 1658) = v7;
    if ( *(float *)&dword_17AB788 < 0.0 )
      *((float *)this + 1658) = 6.2831855 - v7;
    *((float *)this + 1658) = *((float *)this + 1658) * 57.29578;
    *(this + 1655) = dword_17AB788;
    *(this + 1656) = dword_17AB78C;
    *(this + 1657) = dword_17AB790;
    *((float *)this + 1655) = *((float *)this + 1655) * 380.0;
    *((float *)this + 1656) = *((float *)this + 1656) * 380.0;
    *((float *)this + 1657) = *((float *)this + 1657) * 380.0;
    if ( (CCBStageRole *->IsActive()*(this + 1), *(this + 71)) )
      *(this + 1642) = 31;
    else
      *(this + 1642) = 52;
    CCBStageRole::IsGrabedBy((int)this);
    *((_BYTE *)this + 96 * *(this + 99) + 506) = 1;
    CCBStageRole::ClearBadPushTask((int)this, 0.0099999998);
    v8 = *(this + 99);
    *((_BYTE *)this + 273) = 1;
    v9 = (float *)(this + 24 * v8);
    if ( v9[108] >= -700.0 || v9[110] >= -700.0 )
    {
      if ( !*(this + 71) )
      {
        Instance = CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()Instance, aWe011, 0);
      }
      if ( *(this + 71) == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !*(this + 71) )
      {
        v10 = CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v10, aWe011, 1);
      }
      if ( *(this + 71) == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v12, aWe011b, v26);
      }
    }
  }
  v13 = this + 1646;
  v14 = *(double *)(*(_DWORD *)*this + 64);
  v32 = *((float *)this + 1655) * v14;
  v33 = *((float *)this + 1656) * v14;
  v15 = v32 + *((float *)this + 1646);
  v29 = *((float *)this + 1647) + v33;
  v16 = *((float *)this + 1648) + v14 * *((float *)this + 1657);
  *((float *)this + 1647) = v29;
  v31 = v16;
  *((float *)this + 1646) = v15;
  *((float *)this + 1648) = v31;
  v17 = *((float *)this + 1652) - *((float *)this + 1646);
  *(float *)&v34 = *((float *)this + 1653) - *((float *)this + 1647);
  v18 = *((float *)this + 1654) - *((float *)this + 1648);
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
    if ( fabs(v22 - *((float *)this + 1658)) < 1.570796370506287 )
    {
      if ( (CCBRoleState *->IsRoleAlive()*(this + 1), *(this + 71)) )
        return 0;
      *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
      if ( !*(this + 71) )
      {
        v24 = (CCBStageRole *)CScreenMode::GetInstance();
        v24->PlaySound(aWe011, v27);
      }
      if ( *(this + 71) != 4 )
      {
LABEL_43:
        *((_BYTE *)this + 273) = 0;
        return 0;
      }
    }
    else
    {
      *v13 = *(this + 1652);
      *(this + 1647) = *(this + 1653);
      *(this + 1648) = *(this + 1654);
      *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
      if ( !*(this + 71) )
      {
        v23 = (CCBStageRole *)CScreenMode::GetInstance();
        v23->PlaySound(aWe011, v27);
      }
      if ( *(this + 71) != 4 )
        goto LABEL_43;
    }
    v25 = (CCBStageRole *)CScreenMode::GetInstance();
    v25->PlaySound(aWe011b, v27);
    goto LABEL_43;
  }
  *v13 = *(this + 1652);
  *(this + 1647) = *(this + 1653);
  *(this + 1648) = *(this + 1654);
  *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
  if ( !*(this + 71) )
  {
    v19 = (CCBStageRole *)CScreenMode::GetInstance();
    v19->PlaySound(aWe011, v27);
  }
  if ( *(this + 71) == 4 )
  {
    v20 = (CCBStageRole *)CScreenMode::GetInstance();
    v20->PlaySound(aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C320
int CCBStageRole::ProcBlock(int a2)
{
  _DWORD *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v7; // st7
  int v8; // eax
  float *v9; // ecx
  char *v10; // eax
  char *Instance; // eax
  char *v12; // eax
  _DWORD *v13; // edi
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st6
  CCBStageRole *v19; // eax
  CCBStageRole *v20; // eax
  double v21; // st7
  double v22; // st7
  CCBStageRole *v23; // eax
  CCBStageRole *v24; // eax
  CCBStageRole *v25; // eax
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
  v3 = this + 24 * *(this + 99);
  if ( !*((_BYTE *)v3 + 506) )
  {
    *(this + 1652) = v3[108];
    *(this + 1653) = v3[109];
    *(this + 1654) = v3[110];
    v4 = *((float *)this + 1652) - *((float *)this + 1646);
    *(float *)&v28 = *((float *)this + 1653) - *((float *)this + 1647);
    v5 = *((float *)this + 1654) - *((float *)this + 1648);
    dword_17AB75C = v28;
    *(float *)&v30 = v5;
    *(float *)&dword_17AB758 = v4;
    dword_17AB760 = v30;
    if ( (gbVec3D *->Length()&dword_17AB758) < 2.0 )
    {
      *(this + 1646) = *(this + 1652);
      *(this + 1647) = *(this + 1653);
      *(this + 1648) = *(this + 1654);
      *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
      return 0;
    }
    (gbVec3D *->Normalize()&dword_17AB758);
    v7 = acos(
           *(float *)&dword_17AB750 * *(float *)&dword_17AB760
         + *(float *)&dword_17AB74C * *(float *)&dword_17AB75C
         + *(float *)&dword_17AB748 * *(float *)&dword_17AB758);
    *((float *)this + 1658) = v7;
    if ( *(float *)&dword_17AB758 < 0.0 )
      *((float *)this + 1658) = 6.2831855 - v7;
    *((float *)this + 1658) = *((float *)this + 1658) * 57.29578;
    *(this + 1655) = dword_17AB758;
    *(this + 1656) = dword_17AB75C;
    *(this + 1657) = dword_17AB760;
    *((float *)this + 1655) = *((float *)this + 1655) * 570.0;
    *((float *)this + 1656) = *((float *)this + 1656) * 570.0;
    *((float *)this + 1657) = *((float *)this + 1657) * 570.0;
    if ( (CCBStageRole *->IsActive()*(this + 1), *(this + 71)) )
      *(this + 1642) = 31;
    else
      *(this + 1642) = 52;
    CCBStageRole::IsGrabedBy((int)this);
    *((_BYTE *)this + 96 * *(this + 99) + 506) = 1;
    CCBStageRole::ClearBadPushTask((int)this, 0.0099999998);
    v8 = *(this + 99);
    *((_BYTE *)this + 273) = 1;
    v9 = (float *)(this + 24 * v8);
    if ( v9[108] >= -700.0 || v9[110] >= -700.0 )
    {
      if ( !*(this + 71) )
      {
        Instance = CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()Instance, aWe011, 0);
      }
      if ( *(this + 71) == 4 )
      {
        v26 = 0;
        goto LABEL_25;
      }
    }
    else
    {
      if ( !*(this + 71) )
      {
        v10 = CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v10, aWe011, 1);
      }
      if ( *(this + 71) == 4 )
      {
        v26 = 1;
LABEL_25:
        v12 = CScreenMode::GetInstance();
        (CScreenMode *->AudioSetPosition()v12, aWe011b, v26);
      }
    }
  }
  v13 = this + 1646;
  v14 = *(double *)(*(_DWORD *)*this + 64);
  v32 = *((float *)this + 1655) * v14;
  v33 = *((float *)this + 1656) * v14;
  v15 = v32 + *((float *)this + 1646);
  v29 = *((float *)this + 1647) + v33;
  v16 = *((float *)this + 1648) + v14 * *((float *)this + 1657);
  *((float *)this + 1647) = v29;
  v31 = v16;
  *((float *)this + 1646) = v15;
  *((float *)this + 1648) = v31;
  v17 = *((float *)this + 1652) - *((float *)this + 1646);
  *(float *)&v34 = *((float *)this + 1653) - *((float *)this + 1647);
  v18 = *((float *)this + 1654) - *((float *)this + 1648);
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
    if ( fabs(v22 - *((float *)this + 1658)) < 1.570796370506287 )
    {
      if ( (CCBRoleState *->IsRoleAlive()*(this + 1), *(this + 71)) )
        return 0;
      *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
      if ( !*(this + 71) )
      {
        v24 = (CCBStageRole *)CScreenMode::GetInstance();
        v24->PlaySound(aWe011, v27);
      }
      if ( *(this + 71) != 4 )
      {
LABEL_43:
        *((_BYTE *)this + 273) = 0;
        return 0;
      }
    }
    else
    {
      *v13 = *(this + 1652);
      *(this + 1647) = *(this + 1653);
      *(this + 1648) = *(this + 1654);
      *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
      if ( !*(this + 71) )
      {
        v23 = (CCBStageRole *)CScreenMode::GetInstance();
        v23->PlaySound(aWe011, v27);
      }
      if ( *(this + 71) != 4 )
        goto LABEL_43;
    }
    v25 = (CCBStageRole *)CScreenMode::GetInstance();
    v25->PlaySound(aWe011b, v27);
    goto LABEL_43;
  }
  *v13 = *(this + 1652);
  *(this + 1647) = *(this + 1653);
  *(this + 1648) = *(this + 1654);
  *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
  if ( !*(this + 71) )
  {
    v19 = (CCBStageRole *)CScreenMode::GetInstance();
    v19->PlaySound(aWe011, v27);
  }
  if ( *(this + 71) == 4 )
  {
    v20 = (CCBStageRole *)CScreenMode::GetInstance();
    v20->PlaySound(aWe011b, v27);
    return 0;
  }
  return 0;
}

// 0x0050C970
int CCBStageRole::ProcMagic(int this, int a2)
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
  CCBStageRole *v14; // eax
  CCBStageRole *v15; // eax
  int v16; // [esp+0h] [ebp-28h]
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
    *(float *)&v16 = *(float *)(this + 6588) - 20.0;
    if ( *(_DWORD *)(this + 284) )
      CEffMgr::Init(*(int **)(**(_DWORD **)this + 44), 221, *(_DWORD *)(this + 6584), v16, *(_DWORD *)(this + 6592), 0);
    else
      CEffMgr::Init(*(int **)(**(_DWORD **)this + 44), 222, *(_DWORD *)(this + 6584), v16, *(_DWORD *)(this + 6592), 0);
    this->ClearBadPushTask(0.0099999998);
    Instance = CScreenMode::GetInstance();
    (CScreenMode *->AudioSetPosition()Instance, aWe014, 1);
  }
  v10 = (_DWORD *->PushBackAllTask()this);
  v11 = 96 * *(_DWORD *)(this + 396) + this;
  if ( *(float *)(v11 + 488) <= 0.0 )
  {
    v13 = *(double *)(**(_DWORD **)this + 64) * 2.5 + v10;
    v18 = v13;
    if ( v13 >= v19 )
    {
      v18 = v19;
      *(_BYTE *)(v11 + 505) = 1;
      v14 = (CCBStageRole *)CScreenMode::GetInstance();
      v14->PlaySound(aWe014, v17);
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
    v15 = (CCBStageRole *)CScreenMode::GetInstance();
    v15->PlaySound(aWe014, v17);
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
  _DWORD *v3; // eax
  int v4; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  long double v9; // st7
  double v10; // st7
  float v11; // edi
  int v12; // eax
  char *Instance; // eax
  char *v14; // eax
  double v15; // st7
  double v16; // st6
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  int v21; // eax
  CCBStageRole *v22; // eax
  CCBStageRole *v23; // eax
  int v24; // eax
  CCBStageRole *v25; // eax
  CCBStageRole *v26; // eax
  int v27; // [esp+0h] [ebp-18h]
  float v28; // [esp+Ch] [ebp-Ch]
  int v29; // [esp+10h] [ebp-8h]
  int v30; // [esp+10h] [ebp-8h]
  float v31; // [esp+10h] [ebp-8h]
  int v32; // [esp+14h] [ebp-4h]
  int v33; // [esp+14h] [ebp-4h]
  float v34; // [esp+1Ch] [ebp+4h]

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
  v3 = this + 24 * *(this + 99);
  if ( *((_BYTE *)v3 + 506) )
  {
    v11 = a2;
  }
  else
  {
    v3[122] = -1054867456;
    v4 = 96 * *(this + 99);
    *(this + 1652) = *(_DWORD *)((char *)this + v4 + 432);
    *(this + 1653) = *(_DWORD *)((char *)this + v4 + 436);
    *(this + 1654) = *(_DWORD *)((char *)this + v4 + 440);
    v5 = *((float *)this + 1652) - *((float *)this + 1646);
    *(float *)&v29 = *((float *)this + 1653) - *((float *)this + 1647);
    v6 = *((float *)this + 1654) - *((float *)this + 1648);
    dword_17AB70C = v29;
    *(float *)&v32 = v6;
    *(float *)&dword_17AB708 = v5;
    dword_17AB710 = v32;
    v7 = (gbVec3D *->Length()&dword_17AB708);
    v34 = v7;
    if ( v7 < 2.0 )
    {
      *(this + 1646) = *(this + 1652);
      *(this + 1647) = *(this + 1653);
      *(this + 1648) = *(this + 1654);
      *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
      return 0;
    }
    (gbVec3D *->Normalize()&dword_17AB708);
    v9 = acos(
           *(float *)&dword_17AB700 * *(float *)&dword_17AB710
         + *(float *)&dword_17AB6FC * *(float *)&dword_17AB70C
         + *(float *)&dword_17AB6F8 * *(float *)&dword_17AB708);
    *((float *)this + 1658) = v9;
    if ( *(float *)&dword_17AB708 < 0.0 )
      *((float *)this + 1658) = 6.2831855 - v9;
    *((float *)this + 1658) = *((float *)this + 1658) * 57.29578;
    *(this + 1655) = dword_17AB708;
    v10 = v34 + v34;
    *(this + 1656) = dword_17AB70C;
    *(this + 1657) = dword_17AB710;
    *((float *)this + 1655) = v10 * *((float *)this + 1655);
    *((float *)this + 1656) = v10 * *((float *)this + 1656);
    *((float *)this + 1657) = v10 * *((float *)this + 1657);
    if ( (CCBStageRole *->IsActive()*(this + 1), *(this + 71)) )
      *(this + 1642) = 31;
    else
      *(this + 1642) = 52;
    CCBStageRole::IsGrabedBy((int)this);
    v11 = 0.0;
    *((_BYTE *)this + 96 * *(this + 99) + 506) = 1;
    CCBStageRole::ClearBadPushTask((int)this, 0.0099999998);
    v12 = *(this + 71);
    *((_BYTE *)this + 273) = 1;
    if ( v12 == 1 )
    {
      Instance = CScreenMode::GetInstance();
      (CScreenMode *->AudioSetPosition()Instance, aWe012, 1);
    }
    if ( *(this + 71) == 3 )
    {
      v14 = CScreenMode::GetInstance();
      (CScreenMode *->AudioSetPosition()v14, aWe013, 1);
    }
  }
  v15 = *((float *)this + 1652) - *((float *)this + 1646);
  *(float *)&v30 = *((float *)this + 1653) - *((float *)this + 1647);
  v16 = *((float *)this + 1654) - *((float *)this + 1648);
  dword_17AB70C = v30;
  *(float *)&v33 = v16;
  *(float *)&dword_17AB708 = v15;
  dword_17AB710 = v33;
  if ( LODWORD(v11) == *(this + 1666) )
    *(this + 24 * *(this + 99) + 122) = 1120403456;
  if ( *((float *)this + 24 * *(this + 99) + 122) > 0.0 && (gbVec3D *->Length()&dword_17AB708) > 2.0 )
  {
    v17 = *(double *)(*(_DWORD *)*this + 64);
    v28 = *((float *)this + 1655) * v17;
    v31 = *((float *)this + 1656) * v17;
    v18 = v17 * *((float *)this + 1657);
    *((float *)this + 1646) = v28 + *((float *)this + 1646);
    *((float *)this + 1647) = v31 + *((float *)this + 1647);
    *((float *)this + 1648) = v18 + *((float *)this + 1648);
  }
  if ( LODWORD(v11) == *(this + 1667) && (gbVec3D *->Length()&dword_17AB708) <= 2.0 )
    *(this + 24 * *(this + 99) + 122) = -1054867456;
  (gbVec3D *->Normalize()&dword_17AB708);
  v19 = acos(
          *(float *)&dword_17AB700 * *(float *)&dword_17AB710
        + *(float *)&dword_17AB6FC * *(float *)&dword_17AB70C
        + *(float *)&dword_17AB6F8 * *(float *)&dword_17AB708);
  if ( *(float *)&dword_17AB708 < 0.0 )
    v19 = 6.2831855 - v19;
  v20 = v19 * 57.29578;
  flt_17ABCD8 = v20;
  if ( fabs(v20 - *((float *)this + 1658)) >= 1.570796370506287 )
  {
    *(this + 1646) = *(this + 1652);
    *(this + 1647) = *(this + 1653);
    *(this + 1648) = *(this + 1654);
    *(this + 24 * *(this + 99) + 122) = -1054867456;
  }
  if ( LODWORD(v11) == *(this + 1661) )
  {
    *(this + 1646) = *(this + 1652);
    *(this + 1647) = *(this + 1653);
    *(this + 1648) = *(this + 1654);
    *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
    v21 = *(this + 71);
    *((_BYTE *)this + 273) = 0;
    if ( v21 == 1 )
    {
      v22 = (CCBStageRole *)CScreenMode::GetInstance();
      v22->PlaySound(aWe012, v27);
    }
    if ( *(this + 71) == 3 )
    {
      v23 = (CCBStageRole *)CScreenMode::GetInstance();
      v23->PlaySound(aWe013, v27);
    }
  }
  if ( !(CCBRoleState *->IsRoleAlive()*(this + 1), *(this + 71)) )
  {
    *((_BYTE *)this + 96 * *(this + 99) + 505) = 1;
    v24 = *(this + 71);
    *((_BYTE *)this + 273) = 0;
    if ( v24 == 1 )
    {
      v25 = (CCBStageRole *)CScreenMode::GetInstance();
      v25->PlaySound(aWe012, v27);
    }
    if ( *(this + 71) == 3 )
    {
      v26 = (CCBStageRole *)CScreenMode::GetInstance();
      v26->PlaySound(aWe013, v27);
    }
  }
  return 0;
}

// 0x0053E310
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __thiscall CCBStageRole::PlaySound(CCBStageRole *this, char *name, int a3)
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
