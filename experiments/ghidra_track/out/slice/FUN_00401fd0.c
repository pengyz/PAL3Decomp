
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

