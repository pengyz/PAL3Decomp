
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

