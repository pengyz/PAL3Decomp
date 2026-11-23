#include "types.h"
#include "ghidra_isms.h"

/* WARNING: Control flow encountered bad instruction data */

void __stack_chk_fail(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __stack_chk_fail@GLIBC_2.4 */
  halt_baddata();
}


/* Base::~Base() */

void Base::_GLOBAL__sub_I__Base(void)

{
  __static_initialization_and_destruction_0();
  return;
}


/* WARNING: Removing unreachable block (ram,0x0040111d) */
/* WARNING: Removing unreachable block (ram,0x00401127) */

void deregister_tm_clones(void)

{
  return;
}


/* Derived::calc(double) */

double __thiscall Derived::calc(Derived *this,double param_1)

{
  return (double)(int)(param_1 + param_1);
}


/* Derived::render(Complex*) */

void __thiscall Derived::render(Derived *this,Complex *param_1)

{
  (param_1->pos).x = (float)(float)(int)param_1->id;
  param_1->fval = *(UNION_Complex_16 *)(this + 0x38);
  strcpy((char *)&param_1->name,g_message);
  return;
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* printf@GLIBC_2.2.5 */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strcpy(char *__dest,char *__src)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* strcpy@GLIBC_2.2.5 */
  halt_baddata();
}


/* Derived::Derived() */

void __thiscall Derived::Derived(Derived *this)

{
  Base::Base((Base *)this);
  *(undefined ***)this = &PTR__Derived_00403da0;
  return;
}


undefined8 main(void)

{
  uint uVar1;
  long in_FS_OFFSET;
  Complex local_38;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  fixture_init();
  local_38.id = (int)0x3;
  local_38.fval.fval = 0.0;
  Derived::render((Derived *)g_root,&local_38);
  fixture_tick(3);
  uVar1 = fixture_get();
  printf("%s counter=%d name=%s\n",g_message,(ulong)uVar1,&local_38.name);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}


void FUN_00401020(void)

{
  (*(code *)PTR_00404010)();
  return;
}


/* WARNING: Control flow encountered bad instruction data */

void __cxa_atexit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __cxa_atexit@GLIBC_2.2.5 */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __libc_start_main@GLIBC_2.34 */
  halt_baddata();
}


/* Derived::update(int) */

int __thiscall Derived::update(Derived *this,int param_1)

{
  int iVar1;
  
  iVar1 = Base::update((Base *)this,param_1);
  return iVar1 + *(int *)(this + 0x38);
}


/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* __static_initialization_and_destruction_0() */

void __static_initialization_and_destruction_0(void)

{
  Derived::Derived((Derived *)g_root);
  __cxa_atexit(Derived::~Derived,g_root,&__dso_handle);
  return;
}


/* WARNING: Unknown calling convention: __cdecl -- yet parameter storage is locked */
/* fixture_init() */

void __cdecl fixture_init(void)

{
  g_root._8_4_ = 0;
  g_root._56_4_ = 7;
  g_root._48_8_ = 0;
  return;
}


int _init(EVP_PKEY_CTX *ctx)

{
  int iVar1;
  
  iVar1 = 0;
  if (PTR___gmon_start___00403ff8 != (undefined *)0x0) {
    iVar1 = (*(code *)PTR___gmon_start___00403ff8)();
  }
  return iVar1;
}


/* WARNING: Unknown calling convention: __cdecl -- yet parameter storage is locked */
/* fixture_tick(int) */

void __cdecl fixture_tick(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  int local_14;
  
  for (local_14 = 0; local_14 < param_1; local_14 = local_14 + 1) {
    iVar1 = Derived::update((Derived *)g_root,1);
    iVar2 = Derived::calc((Derived *)g_root,local_14,2);
    dVar3 = Derived::calc((Derived *)g_root,DAT_00402038);
    g_counter = g_counter + iVar1 + iVar2 + (int)dVar3;
  }
  return;
}


/* Derived::~Derived() */

void __thiscall Derived::~Derived(Derived *this)

{
  ~Derived(this);
  operator_delete(this);
  return;
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void operator_delete(void *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* _ZdlPv@GLIBCXX_3.4 */
  halt_baddata();
}


/* Base::~Base() */

void __thiscall Base::~Base(Base *this)

{
  ~Base(this);
  operator_delete(this);
  return;
}


void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined1 auStack_8 [8];
  
  (*(code *)PTR___libc_start_main_00403ff0)(main,param_2,&stack0x00000008,0,0,param_1,auStack_8);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* WARNING: Unknown calling convention: __cdecl -- yet parameter storage is locked */
/* fixture_get() */

int __cdecl fixture_get(void)

{
  return g_counter;
}


void _dl_relocate_static_pie(void)

{
  return;
}


/* Base::Base() */

void __thiscall Base::Base(Base *this)

{
  *(undefined ***)this = &PTR__Base_00403dd0;
  return;
}


void frame_dummy(void)

{
  register_tm_clones();
  return;
}


void __do_global_dtors_aux(void)

{
  if (completed_0 == '\0') {
    deregister_tm_clones();
    completed_0 = 1;
    return;
  }
  return;
}


/* WARNING: Removing unreachable block (ram,0x0040115f) */
/* WARNING: Removing unreachable block (ram,0x00401169) */

void register_tm_clones(void)

{
  return;
}


void _fini(void)

{
  return;
}

