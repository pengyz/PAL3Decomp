
void __fastcall FUN_00402080(int *param_1)

{
  if (*param_1 != 0) {
    if (param_1[1] != 0) {
      EnumJoystick();
      (**(code **)(*(int *)param_1[1] + 8))((int *)param_1[1]);
      param_1[1] = 0;
    }
    if (param_1[2] != 0) {
      FUN_00402360();
      (**(code **)(*(int *)param_1[2] + 8))((int *)param_1[2]);
      param_1[2] = 0;
    }
    (**(code **)(*(int *)*param_1 + 8))((int *)*param_1);
    *param_1 = 0;
  }
  return;
}

