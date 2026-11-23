
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

