
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

