
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* __static_initialization_and_destruction_0() */

void __static_initialization_and_destruction_0(void)

{
  Derived::Derived((Derived *)g_root);
  __cxa_atexit(Derived::~Derived,g_root,&__dso_handle);
  return;
}

