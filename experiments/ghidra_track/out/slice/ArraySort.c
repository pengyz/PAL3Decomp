
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ArraySort(void)

{
  int iVar1;
  int in_stack_0000000c;
  code *in_stack_00000010;
  
  iVar1 = in_stack_0000000c + -1;
  if (-1 < iVar1) {
    do {
      iVar1 = (*in_stack_00000010)();
      in_stack_0000000c = in_stack_0000000c + -1;
    } while (in_stack_0000000c != 0);
  }
  return iVar1;
}

