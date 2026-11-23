
void __fastcall thunk_FUN_004019b0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = param_1;
  if ((int)param_1[0x10] < 1) {
    param_1[0x10] = 0;
    return;
  }
  do {
    gbRefObject::Release((gbRefObject *)*puVar1);
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar2 < (int)param_1[0x10]);
  param_1[0x10] = 0;
  return;
}

