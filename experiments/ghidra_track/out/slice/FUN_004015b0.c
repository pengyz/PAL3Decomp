
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

