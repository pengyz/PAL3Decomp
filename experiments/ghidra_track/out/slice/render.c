
/* Derived::render(Complex*) */

void __thiscall Derived::render(Derived *this,Complex *param_1)

{
  *(float *)(param_1 + 4) = (float)*(int *)param_1;
  *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(this + 0x38);
  strcpy((char *)(param_1 + 0x14),g_message);
  return;
}

