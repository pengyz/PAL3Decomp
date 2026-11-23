
/* WARNING: Unknown calling convention: cdecl -- yet parameter storage is locked */

byte cdecl FileSysDestory(void)

{
  code *pcVar1;
  
  if (DAT_007cc178 != 0) {
    gbVFileSystem::Release((gbVFileSystem *)&DAT_007cc178);
  }
  if (DAT_006ebfa0 != 0) {
    gbVFileSystem::Release((gbVFileSystem *)&DAT_006ebfa0);
    pcVar1 = g_pVFileSys_exref;
    *(undefined4 *)g_pVFileSys_exref = 0;
    return (byte)pcVar1;
  }
  *(undefined4 *)g_pVFileSys_exref = 0;
  return 0;
}

