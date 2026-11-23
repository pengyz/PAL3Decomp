#include "types.h"
#include "ghidra_isms.h"

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ArraySort(void)

{
  int iVar1;
  int in_stack_0000000c;
  code *in_stack_00000010;
  
  iVar1 = in_stack_0000000c + -1;
  if (-1 < iVar1) {
    do {
      iVar1 = (*in_stack_00000010)();
      in_stack_0000000c = in_stack_0000000c + -1;
    } while (in_stack_0000000c != 0);
  }
  return iVar1;
}


undefined4 * __fastcall FUN_00401000(undefined4 *param_1)

{
  undefined4 uVar1;
  
  *param_1 = &PTR_FUN_0056a600;
  uVar1 = FUN_00552ed8(1,8);
  param_1[4] = uVar1;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  return param_1;
}


undefined4 __thiscall FUN_00401030(undefined4 param_1,byte param_2)

{
  FUN_00401050();
  if ((param_2 & 1) != 0) {
    FUN_00541d10(param_1);
  }
  return param_1;
}


void __fastcall FUN_00401050(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0056a600;
  FUN_004017a0();
  FUN_00552f55(param_1[4]);
  return;
}


undefined4 __thiscall
FUN_00401070(int *param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  float fVar1;
  byte bVar2;
  int iVar3;
  float *pfVar4;
  undefined4 unaff_EBX;
  int unaff_EBP;
  float unaff_retaddr;
  
  FUN_004017a0();
  iVar3 = FUN_00552ed8(1,0x40);
  param_1[1] = iVar3;
  iVar3 = FUN_00552ed8(1,0x40);
  param_1[2] = iVar3;
  pfVar4 = (float *)FUN_00552ed8(1,0x40);
  *(undefined4 *)(param_1[1] + 0x3c) = 0;
  *(undefined4 *)(param_1[2] + 0x3c) = 0;
  pfVar4[2] = 0.0;
  bVar2 = (**(code **)(*param_1 + 8))(param_4,param_5);
  fVar1 = SQRT((float)(param_3 * param_3 + (param_2 - param_4) * (param_2 - param_4))) *
          *(float *)(&g_fHeuristicScale + (uint)bVar2 * 4);
  pfVar4[3] = 0.0;
  pfVar4[1] = fVar1;
  pfVar4[4] = unaff_retaddr;
  pfVar4[0xf] = 0.0;
  *pfVar4 = fVar1 + pfVar4[2];
  pfVar4[5] = (float)((int)unaff_retaddr * 0x200);
  *(float **)(param_1[1] + 0x3c) = pfVar4;
  param_1[5] = 1;
  iVar3 = FUN_004014b0();
  while ((iVar3 != 0 && (param_1[5] < 0x12d))) {
    if (*(int *)(iVar3 + 0x14) == unaff_EBP) {
      param_1[3] = iVar3;
      goto LAB_00401247;
    }
    if ((param_1[3] == 0) || (*(float *)(iVar3 + 4) < *(float *)(param_1[3] + 4))) {
      param_1[3] = iVar3;
    }
    FUN_004012a0(iVar3,*(undefined4 *)(iVar3 + 0xc),*(int *)(iVar3 + 0x10) + -1,param_2,param_5);
    FUN_004012a0(iVar3,*(undefined4 *)(iVar3 + 0xc),*(int *)(iVar3 + 0x10) + 1,param_2,param_5);
    FUN_004012a0(iVar3,*(int *)(iVar3 + 0xc) + -1,*(undefined4 *)(iVar3 + 0x10),param_2,param_5);
    FUN_004012a0(iVar3,*(int *)(iVar3 + 0xc) + 1,*(undefined4 *)(iVar3 + 0x10),param_2,param_5);
    FUN_004012a0(iVar3,*(int *)(iVar3 + 0xc) + -1,*(int *)(iVar3 + 0x10) + -1,param_2,param_5);
    FUN_004012a0(iVar3,*(int *)(iVar3 + 0xc) + 1,*(int *)(iVar3 + 0x10) + 1,param_2,param_5);
    FUN_004012a0(iVar3,*(int *)(iVar3 + 0xc) + 1,*(int *)(iVar3 + 0x10) + -1,param_2,param_5);
    FUN_004012a0(iVar3,*(int *)(iVar3 + 0xc) + -1,*(int *)(iVar3 + 0x10) + 1,param_2,param_5);
    param_1[5] = param_1[5] + 1;
    iVar3 = FUN_004014b0();
  }
  unaff_EBX = 1;
LAB_00401247:
  if (param_1[3] != 0) {
    *(undefined4 *)(param_1[3] + 0x1c) = 0;
    for (iVar3 = *(int *)(param_1[3] + 0x18); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x18)) {
      *(int *)(*(int *)(param_1[3] + 0x18) + 0x1c) = param_1[3];
      iVar3 = *(int *)(param_1[3] + 0x18);
      param_1[3] = iVar3;
    }
    return unaff_EBX;
  }
  return 0xffffffff;
}


undefined4 __thiscall FUN_004012a0(int *param_1,undefined4 param_2,float param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  float fVar5;
  int *piVar6;
  float unaff_EBX;
  float fVar7;
  int unaff_ESI;
  float unaff_EDI;
  float fVar8;
  float fVar9;
  undefined4 uStack_8;
  int iStack_4;
  
  fVar5 = param_3;
  iVar2 = (**(code **)(*param_1 + 4))(param_3,param_4);
  if (iVar2 == 0) {
    return 0;
  }
  (**(code **)(*param_1 + 8))();
  fVar9 = (float)((iRam00000010 - param_4) * (iRam00000010 - param_4) +
                 (iRam0000000c - (int)param_3) * (iRam0000000c - (int)param_3));
  uVar3 = (**(code **)(*param_1 + 8))(param_3,param_4);
  fVar8 = SQRT(unaff_EBX) * *(float *)(&g_fHeuristicScale + (uVar3 & 0xff) * 4) + fRam00000008;
  fVar7 = (float)(param_4 * 0x200 + (int)param_3);
  pfVar4 = (float *)FUN_00401500(fVar7);
  if (pfVar4 == (float *)0x0) {
    pfVar4 = (float *)FUN_00401530(fVar7);
    if (pfVar4 == (float *)0x0) {
      pfVar4 = (float *)FUN_00552ed8(1,0x40);
      pfVar4[6] = unaff_EDI;
      pfVar4[2] = fVar8;
      bVar1 = (**(code **)(*param_1 + 8))(uStack_8,iStack_4);
      fVar8 = SQRT((float)((param_4 - iStack_4) * (param_4 - iStack_4) + unaff_ESI * unaff_ESI)) *
              *(float *)(&g_fHeuristicScale + (uint)bVar1 * 4);
      pfVar4[1] = fVar8;
      pfVar4[3] = fVar9;
      pfVar4[4] = unaff_EDI;
      pfVar4[5] = fVar7;
      *pfVar4 = fVar8 + param_3;
      FUN_00401560(pfVar4);
      piVar6 = (int *)((int)fVar5 + 0x1c);
      do {
        if (*piVar6 == 0) break;
        param_4 = param_4 + 1;
        piVar6 = piVar6 + 1;
      } while (param_4 < 8);
      *(float **)((int)fVar5 + 0x1c + param_4 * 4) = pfVar4;
    }
    else {
      piVar6 = (int *)((int)unaff_EDI + 0x1c);
      do {
        if (*piVar6 == 0) break;
        piVar6 = piVar6 + 1;
        fVar5 = (float)((int)fVar5 + 1);
      } while ((int)fVar5 < 8);
      *(float **)((int)unaff_EDI + 0x1c + (int)fVar5 * 4) = pfVar4;
      if (fVar8 < pfVar4[2]) {
        pfVar4[6] = unaff_EDI;
        pfVar4[2] = fVar8;
        *pfVar4 = fVar8 + pfVar4[1];
        FUN_004015b0(pfVar4);
        return 1;
      }
    }
  }
  else {
    piVar6 = (int *)((int)unaff_EDI + 0x1c);
    do {
      if (*piVar6 == 0) break;
      piVar6 = piVar6 + 1;
      fVar5 = (float)((int)fVar5 + 1);
    } while ((int)fVar5 < 8);
    *(float **)((int)unaff_EDI + 0x1c + (int)fVar5 * 4) = pfVar4;
    if (fVar8 < pfVar4[2]) {
      pfVar4[6] = unaff_EDI;
      pfVar4[2] = fVar8;
      *pfVar4 = fVar8 + pfVar4[1];
      return 1;
    }
  }
  return 1;
}


void __fastcall FUN_004014b0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 4) + 0x3c);
  if (iVar1 == 0) {
    return;
  }
  *(undefined4 *)(*(int *)(param_1 + 4) + 0x3c) = *(undefined4 *)(iVar1 + 0x3c);
  *(undefined4 *)(iVar1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 8) + 0x3c);
  *(int *)(*(int *)(param_1 + 8) + 0x3c) = iVar1;
  return;
}


undefined1 FUN_004014f0(void)

{
  return 0;
}


undefined4 __thiscall FUN_00401500(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 4);
  for (iVar2 = *(int *)(*(int *)(param_1 + 4) + 0x3c);
      (iVar2 != 0 && (*(int *)(iVar2 + 0x14) != param_2)); iVar2 = *(int *)(iVar2 + 0x3c)) {
    iVar1 = iVar2;
  }
  return *(undefined4 *)(iVar1 + 0x3c);
}


undefined4 __thiscall FUN_00401530(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  for (iVar2 = *(int *)(*(int *)(param_1 + 8) + 0x3c);
      (iVar2 != 0 && (*(int *)(iVar2 + 0x14) != param_2)); iVar2 = *(int *)(iVar2 + 0x3c)) {
    iVar1 = iVar2;
  }
  return *(undefined4 *)(iVar1 + 0x3c);
}


void __thiscall FUN_00401560(int param_1,float *param_2)

{
  float *pfVar1;
  float *pfVar2;
  
  pfVar1 = *(float **)(param_1 + 4);
  for (pfVar2 = (float *)(*(float **)(param_1 + 4))[0xf];
      (pfVar2 != (float *)0x0 && (*pfVar2 < *param_2)); pfVar2 = (float *)pfVar2[0xf]) {
    pfVar1 = pfVar2;
  }
  param_2[0xf] = pfVar1[0xf];
  pfVar1[0xf] = (float)param_2;
  return;
}


void FUN_00401590(int param_1)

{
  int iVar1;
  
  while (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 0x3c);
    FUN_00552f55(param_1);
    param_1 = iVar1;
  }
  return;
}


void __thiscall FUN_004015b0(int *param_1,int *param_2)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  int iVar6;
  int local_10;
  int *local_c;
  
  fVar5 = *(float *)((int)param_2 + 8);
  local_c = (int *)((int)param_2 + 0x1c);
  local_10 = 0;
  do {
    pfVar1 = (float *)*local_c;
    if (pfVar1 == (float *)0x0) break;
    iVar6 = *(int *)((int)param_2 + 0xc) - (int)pfVar1[3];
    iVar3 = *(int *)((int)param_2 + 0x10) - (int)pfVar1[4];
    uVar4 = (**(code **)(*param_1 + 8))(pfVar1[3],pfVar1[4]);
    fVar2 = SQRT((float)(iVar6 * iVar6 + iVar3 * iVar3)) *
            *(float *)(&g_fHeuristicScale + (uVar4 & 0xff) * 4) + fVar5;
    if (fVar2 < pfVar1[2]) {
      pfVar1[2] = fVar2;
      pfVar1[6] = (float)param_2;
      *pfVar1 = fVar2 + pfVar1[1];
      FUN_00401750(pfVar1);
    }
    local_10 = local_10 + 1;
    local_c = local_c + 1;
  } while (local_10 < 8);
  iVar3 = *(int *)(param_1[4] + 4);
  do {
    if (iVar3 == 0) {
      return;
    }
    fVar5 = (float)FUN_00401780();
    local_10 = 0;
    param_2 = (int *)((int)fVar5 + 0x1c);
    do {
      pfVar1 = (float *)*param_2;
      if (pfVar1 == (float *)0x0) break;
      iVar6 = *(int *)((int)fVar5 + 0xc) - (int)pfVar1[3];
      iVar3 = *(int *)((int)fVar5 + 0x10) - (int)pfVar1[4];
      uVar4 = (**(code **)(*param_1 + 8))(pfVar1[3],pfVar1[4]);
      fVar2 = SQRT((float)(iVar6 * iVar6 + iVar3 * iVar3)) *
              *(float *)(&g_fHeuristicScale + (uVar4 & 0xff) * 4) + *(float *)((int)fVar5 + 8);
      if (fVar2 < pfVar1[2]) {
        pfVar1[2] = fVar2;
        pfVar1[6] = fVar5;
        *pfVar1 = fVar2 + pfVar1[1];
        FUN_00401750(pfVar1);
      }
      local_10 = local_10 + 1;
      param_2 = param_2 + 1;
    } while (local_10 < 8);
    iVar3 = *(int *)(param_1[4] + 4);
  } while( true );
}


void __thiscall FUN_00401750(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00552ed8(1,8);
  *puVar1 = param_2;
  puVar1[1] = *(undefined4 *)(*(int *)(param_1 + 0x10) + 4);
  *(undefined4 **)(*(int *)(param_1 + 0x10) + 4) = puVar1;
  return;
}


undefined4 __fastcall FUN_00401780(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = *(undefined4 **)(*(int *)(param_1 + 0x10) + 4);
  uVar2 = *puVar1;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 4) = puVar1[1];
  FUN_00552f55(puVar1);
  return uVar2;
}


void __fastcall FUN_004017a0(int param_1)

{
  FUN_00401590(*(undefined4 *)(param_1 + 4));
  FUN_00401590(*(undefined4 *)(param_1 + 8));
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}


void FUN_00401800(void)

{
  return;
}


void __fastcall FUN_00401880(int param_1)

{
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  return;
}


void __thiscall FUN_004018b0(undefined4 *param_1,undefined4 param_2,undefined4 *param_3)

{
  gbRenderEffect *pgVar1;
  int iVar2;
  gbTexture *this;
  undefined4 *puVar3;
  int iVar4;
  char local_110 [260];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0055f02b;
  pvStack_c = ExceptionList;
  iVar4 = 0;
  ExceptionList = &pvStack_c;
  pgVar1 = gbEffectMgr::NewRenderEffect
                     ((gbEffectMgr *)DAT_00bfda60[0x32],s_gfxscript_sprite_gbf_00580aa0,0);
  param_1[0x16] = pgVar1;
  param_1[0x12] = param_2;
  param_1[0x13] = *param_3;
  param_1[0x14] = param_3[1];
  param_1[0x15] = param_3[2];
  param_1[0x11] = 0;
  FUN_00401f50();
  local_4 = 0;
  puVar3 = param_1;
  do {
    FUN_00553082(local_110,s_HBobject_BB_02d__02d_tga_00580a86 + 2,param_1[0x12],iVar4);
    iVar2 = gbVFileSystem::FileExistNum(*(gbVFileSystem **)g_pVFileSys_exref,local_110);
    if (iVar2 == 0) break;
    this = (gbTexture *)(**(code **)(*DAT_00bfda60 + 8))(local_110);
    *puVar3 = this;
    gbTexture::LoadTexture(this,1);
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 0x10);
  param_1[0x10] = iVar4;
  local_4 = 0xffffffff;
  FUN_00401f90();
  ExceptionList = pvStack_c;
  return;
}


void __fastcall FUN_004019b0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = param_1;
  if ((int)param_1[0x10] < 1) {
    param_1[0x10] = 0;
    return;
  }
  do {
    gbRefObject::Release((gbRefObject *)*puVar1);
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar2 < (int)param_1[0x10]);
  param_1[0x10] = 0;
  return;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004019f0(gbTextureArray *param_1)

{
  gbMatrixStack *this;
  gbMatrix4 *this_00;
  gbDynVertBuf *this_01;
  int iVar1;
  gbVec3D *this_02;
  float local_50;
  float local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  undefined1 local_3;
  undefined1 local_2;
  undefined1 local_1;
  
  this_02 = (gbVec3D *)&local_44;
  iVar1 = 4;
  do {
    gbVec3D::_default_constructor_closure_(this_02);
    this_02 = this_02 + 0xc;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  this = *(gbMatrixStack **)(DAT_00bfda60 + 0xd8);
  this_00 = gbMatrixStack::GetTop(this);
  local_50 = 0.0;
  local_4c = 0.0;
  local_48 = 0;
  gbMatrix4::Transform(this_00,(gbVec3D *)(param_1 + 0x4c),(gbVec3D *)&local_50);
  local_18 = local_48;
  local_40 = local_4c;
  local_44 = local_50 - *(float *)(&DAT_00580a58 + *(int *)(param_1 + 0x48) * 8) * _DAT_0056a610;
  local_1 = 0xff;
  local_4 = 0xff;
  local_3 = 0xff;
  local_2 = 0xff;
  local_28 = local_4c + *(float *)(&DAT_00580a5c + *(int *)(param_1 + 0x48) * 8);
  local_34 = local_4c;
  local_3c = local_48;
  local_24 = local_48;
  local_14 = 0;
  local_38 = *(float *)(&DAT_00580a58 + *(int *)(param_1 + 0x48) * 8) * _DAT_0056a610 + local_50;
  local_10 = 0;
  local_c = 0x3f800000;
  local_8 = 0x3f800000;
  local_30 = local_48;
  local_2c = local_38;
  local_20 = local_44;
  local_1c = local_28;
  gbMatrixStack::Push(this);
  gbMatrixStack::LoadIdentity(this);
  this_01 = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(DAT_00bfda60 + 0xc4),0x15);
  gbDynVertBuf::RenderGeomQuad
            (this_01,(gbGeomQuad *)&local_44,1,*(gbRenderEffect **)(param_1 + 0x58),param_1);
  gbMatrixStack::Pop(this);
  return;
}


void FUN_00401bc0(void)

{
                    /* WARNING: Could not recover jumptable at 0x00401bc5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  gbVFileSystem::gbVFileSystem((gbVFileSystem *)&DAT_007cc178);
  return;
}


void FUN_00401bd0(void)

{
  FUN_00553041(&LAB_00401be0);
  return;
}


void FUN_00401c00(void)

{
                    /* WARNING: Could not recover jumptable at 0x00401c05. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  gbVFileSystem::gbVFileSystem((gbVFileSystem *)&DAT_006ebfa0);
  return;
}


void FUN_00401c10(void)

{
  FUN_00553041(&LAB_00401c20);
  return;
}


void FUN_00401c40(void)

{
                    /* WARNING: Could not recover jumptable at 0x00401c45. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  gbVFileSystem::gbVFileSystem((gbVFileSystem *)&DAT_0060bdc8);
  return;
}


void FUN_00401c50(void)

{
  FUN_00553041(&LAB_00401c60);
  return;
}


undefined4 __thiscall FUN_00401df0(undefined4 param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  bool bVar8;
  char local_248 [260];
  undefined1 local_144 [324];
  
  iVar2 = __strcmpi(param_2,(char *)&DAT_008ac5d8);
  if (iVar2 == 0) {
    *(int **)g_pVFileSys_exref = &DAT_006ebfa0;
    return param_1;
  }
  uVar3 = 0xffffffff;
  pcVar5 = param_2;
  do {
    pcVar7 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar7 + -uVar3;
  pcVar7 = (char *)&DAT_008ac5d8;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  bVar8 = DAT_006ebfa0 != 0;
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  if (bVar8) {
    gbVFileSystem::Release((gbVFileSystem *)&DAT_006ebfa0);
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = param_2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = param_2 + 1;
    cVar1 = *param_2;
    param_2 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  pcVar7 = local_248;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  if ((g_dwGameFlags & 2) != 0) {
    uVar3 = 0xffffffff;
    pcVar5 = &DAT_00580b5c;
    do {
      pcVar7 = pcVar5;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar7 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar7;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    iVar2 = -1;
    pcVar5 = local_248;
    do {
      pcVar6 = pcVar5;
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pcVar6 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar6;
    } while (cVar1 != '\0');
    pcVar5 = pcVar7 + -uVar3;
    pcVar7 = pcVar6 + -1;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  iVar2 = gbVFileSystem::Init((gbVFileSystem *)&DAT_006ebfa0,local_248);
  if (iVar2 == 0) {
    FUN_00553082(local_144,&DAT_00580b54,&DAT_01894970,local_248);
    gbVFileSystem::Init((gbVFileSystem *)&DAT_006ebfa0,local_248);
    *(int **)g_pVFileSys_exref = &DAT_006ebfa0;
    return param_1;
  }
  *(int **)g_pVFileSys_exref = &DAT_006ebfa0;
  return param_1;
}


void FUN_00401f40(void)

{
  *(undefined4 **)g_pVFileSys_exref = &DAT_007cc178;
  return;
}


void __fastcall FUN_00401f50(undefined4 *param_1)

{
  *param_1 = *(undefined4 *)g_pVFileSys_exref;
  *(undefined4 **)g_pVFileSys_exref = &DAT_007cc178;
  return;
}


void __fastcall FUN_00401f70(undefined4 *param_1)

{
  *param_1 = *(undefined4 *)g_pVFileSys_exref;
  *(undefined **)g_pVFileSys_exref = &DAT_0060bdc8;
  return;
}


void __fastcall FUN_00401f90(undefined4 *param_1)

{
  *(undefined4 *)g_pVFileSys_exref = *param_1;
  return;
}


undefined4 * __fastcall FUN_00401fd0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  param_1[6] = 0x7fffffff;
  param_1[7] = 0x7fffffff;
  param_1[10] = 0x7fffffff;
  param_1[0xb] = 0x7fffffff;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[0x61b] = 0;
  param_1[0x61c] = 0;
  param_1[0x61d] = 0;
  param_1[3] = 0x3f800000;
  param_1[4] = 0x80000000;
  param_1[5] = 0x80000000;
  param_1[8] = 0x80000000;
  param_1[9] = 0x80000000;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  puVar2 = param_1 + 0x1a;
  for (iVar1 = 0x43; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  puVar2 = (undefined4 *)((int)param_1 + 0x176);
  for (iVar1 = 0x43; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  puVar2 = param_1 + 0x9e;
  for (iVar1 = 0x10e; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_1 + 0x1ac;
  for (iVar1 = 0x21c; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return param_1;
}


void __fastcall FUN_00402080(int *param_1)

{
  if (*param_1 != 0) {
    if (param_1[1] != 0) {
      EnumJoystick();
      (**(code **)(*(int *)param_1[1] + 8))((int *)param_1[1]);
      param_1[1] = 0;
    }
    if (param_1[2] != 0) {
      FUN_00402360();
      (**(code **)(*(int *)param_1[2] + 8))((int *)param_1[2]);
      param_1[2] = 0;
    }
    (**(code **)(*(int *)*param_1 + 8))((int *)*param_1);
    *param_1 = 0;
  }
  return;
}


void __thiscall FUN_004021e0(int param_1,int param_2,int param_3)

{
  *(int *)(param_1 + 0x186c) = param_2;
  if (param_2 == 0) {
    FUN_00402360();
  }
  else {
    FUN_00402310();
  }
  *(int *)(param_1 + 0x1870) = param_3;
  if (param_3 != 0) {
    FUN_00402380();
    return;
  }
  EnumJoystick();
  return;
}


void __fastcall FUN_00402220(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_1 + 0x68);
  for (iVar1 = 0x43; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  puVar2 = (undefined4 *)(param_1 + 0x176);
  for (iVar1 = 0x43; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  puVar2 = (undefined4 *)(param_1 + 0x278);
  for (iVar1 = 0x10e; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_1 + 0x6b0);
  for (iVar1 = 0x21c; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_1 + 0x1878);
  for (iVar1 = 0x438; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}


void FUN_00402290(int param_1,int param_2)

{
  SetCursorPos(param_1,param_2);
  return;
}


undefined1 __thiscall FUN_004022c0(int param_1,uint param_2)

{
  return *(undefined1 *)((param_2 & 0xffff) + 0x68 + param_1);
}


/* WARNING: Unknown calling convention: cdecl -- yet parameter storage is locked */

byte cdecl FileSysDestory(void)

{
  code *pcVar1;
  
  if (DAT_007cc178 != 0) {
    gbVFileSystem::Release((gbVFileSystem *)&DAT_007cc178);
  }
  if (DAT_006ebfa0 != 0) {
    gbVFileSystem::Release((gbVFileSystem *)&DAT_006ebfa0);
    pcVar1 = g_pVFileSys_exref;
    *(undefined4 *)g_pVFileSys_exref = 0;
    return (byte)pcVar1;
  }
  *(undefined4 *)g_pVFileSys_exref = 0;
  return 0;
}


void __fastcall thunk_FUN_004019b0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = param_1;
  if ((int)param_1[0x10] < 1) {
    param_1[0x10] = 0;
    return;
  }
  do {
    gbRefObject::Release((gbRefObject *)*puVar1);
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar2 < (int)param_1[0x10]);
  param_1[0x10] = 0;
  return;
}

