
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

