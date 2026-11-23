
/* Derived::update(int) */

int __thiscall Derived::update(Derived *this,int param_1)

{
  int iVar1;
  
  iVar1 = Base::update((Base *)this,param_1);
  return iVar1 + *(int *)(this + 0x38);
}

