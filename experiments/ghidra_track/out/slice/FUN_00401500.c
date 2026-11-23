
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

