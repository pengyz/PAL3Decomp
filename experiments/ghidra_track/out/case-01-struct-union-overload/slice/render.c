
/* Derived::render(Complex*) */

void __thiscall Derived::render(Derived *this,Complex *param_1)

{
  (param_1->pos).x = (float)(float)(int)param_1->id;
  param_1->fval = *(UNION_Complex_16 *)(this + 0x38);
  strcpy((char *)&param_1->name,g_message);
  return;
}

