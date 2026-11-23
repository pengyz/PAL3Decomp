
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

