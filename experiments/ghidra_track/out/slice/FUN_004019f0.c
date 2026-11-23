
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004019f0(gbTextureArray *param_1)

{
  gbMatrixStack *this;
  gbMatrix4 *this_00;
  gbDynVertBuf *this_01;
  int iVar1;
  gbVec3D *this_02;
  float local_50;
  float local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  undefined1 local_3;
  undefined1 local_2;
  undefined1 local_1;
  
  this_02 = (gbVec3D *)&local_44;
  iVar1 = 4;
  do {
    gbVec3D::_default_constructor_closure_(this_02);
    this_02 = this_02 + 0xc;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  this = *(gbMatrixStack **)(DAT_00bfda60 + 0xd8);
  this_00 = gbMatrixStack::GetTop(this);
  local_50 = 0.0;
  local_4c = 0.0;
  local_48 = 0;
  gbMatrix4::Transform(this_00,(gbVec3D *)(param_1 + 0x4c),(gbVec3D *)&local_50);
  local_18 = local_48;
  local_40 = local_4c;
  local_44 = local_50 - *(float *)(&DAT_00580a58 + *(int *)(param_1 + 0x48) * 8) * _DAT_0056a610;
  local_1 = 0xff;
  local_4 = 0xff;
  local_3 = 0xff;
  local_2 = 0xff;
  local_28 = local_4c + *(float *)(&DAT_00580a5c + *(int *)(param_1 + 0x48) * 8);
  local_34 = local_4c;
  local_3c = local_48;
  local_24 = local_48;
  local_14 = 0;
  local_38 = *(float *)(&DAT_00580a58 + *(int *)(param_1 + 0x48) * 8) * _DAT_0056a610 + local_50;
  local_10 = 0;
  local_c = 0x3f800000;
  local_8 = 0x3f800000;
  local_30 = local_48;
  local_2c = local_38;
  local_20 = local_44;
  local_1c = local_28;
  gbMatrixStack::Push(this);
  gbMatrixStack::LoadIdentity(this);
  this_01 = gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)(DAT_00bfda60 + 0xc4),0x15);
  gbDynVertBuf::RenderGeomQuad
            (this_01,(gbGeomQuad *)&local_44,1,*(gbRenderEffect **)(param_1 + 0x58),param_1);
  gbMatrixStack::Pop(this);
  return;
}

