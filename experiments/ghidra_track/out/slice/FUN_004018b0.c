
void __thiscall FUN_004018b0(undefined4 *param_1,undefined4 param_2,undefined4 *param_3)

{
  gbRenderEffect *pgVar1;
  int iVar2;
  gbTexture *this;
  undefined4 *puVar3;
  int iVar4;
  char local_110 [260];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0055f02b;
  pvStack_c = ExceptionList;
  iVar4 = 0;
  ExceptionList = &pvStack_c;
  pgVar1 = gbEffectMgr::NewRenderEffect
                     ((gbEffectMgr *)DAT_00bfda60[0x32],s_gfxscript_sprite_gbf_00580aa0,0);
  param_1[0x16] = pgVar1;
  param_1[0x12] = param_2;
  param_1[0x13] = *param_3;
  param_1[0x14] = param_3[1];
  param_1[0x15] = param_3[2];
  param_1[0x11] = 0;
  FUN_00401f50();
  local_4 = 0;
  puVar3 = param_1;
  do {
    FUN_00553082(local_110,s_HBobject_BB_02d__02d_tga_00580a86 + 2,param_1[0x12],iVar4);
    iVar2 = gbVFileSystem::FileExistNum(*(gbVFileSystem **)g_pVFileSys_exref,local_110);
    if (iVar2 == 0) break;
    this = (gbTexture *)(**(code **)(*DAT_00bfda60 + 8))(local_110);
    *puVar3 = this;
    gbTexture::LoadTexture(this,1);
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 0x10);
  param_1[0x10] = iVar4;
  local_4 = 0xffffffff;
  FUN_00401f90();
  ExceptionList = pvStack_c;
  return;
}

