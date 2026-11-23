
void __thiscall FUN_004021e0(int param_1,int param_2,int param_3)

{
  *(int *)(param_1 + 0x186c) = param_2;
  if (param_2 == 0) {
    FUN_00402360();
  }
  else {
    FUN_00402310();
  }
  *(int *)(param_1 + 0x1870) = param_3;
  if (param_3 != 0) {
    FUN_00402380();
    return;
  }
  EnumJoystick();
  return;
}

