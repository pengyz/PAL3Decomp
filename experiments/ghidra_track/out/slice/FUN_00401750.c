
void __thiscall FUN_00401750(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00552ed8(1,8);
  *puVar1 = param_2;
  puVar1[1] = *(undefined4 *)(*(int *)(param_1 + 0x10) + 4);
  *(undefined4 **)(*(int *)(param_1 + 0x10) + 4) = puVar1;
  return;
}

