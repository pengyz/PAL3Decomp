
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

