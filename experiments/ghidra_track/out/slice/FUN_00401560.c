
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

