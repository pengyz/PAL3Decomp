
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

