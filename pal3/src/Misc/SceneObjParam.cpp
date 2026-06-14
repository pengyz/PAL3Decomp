#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SceneObjParam.h"

// 0x00533CB0
int SceneObjParam::UpdateCameraAndRole(gbGfxManager *p)
{
  this->mInfo.reserve[14] = 0;
  this->mInfo.reserve[15] = 0;
  this->mInfo.reserve[16] = 0;
  this->mInfo.reserve[17] = 0;
  this->mInfo.reserve[18] = 0;
  this->mInfo.reserve[19] = 0;
  this->mInfo.reserve[27] = 0;
  this->mInfo.reserve[28] = 0;
  this->mInfo.reserve[29] = 0;
  this->mInfo.reserve[30] = 0;
  this->mInfo.reserve[31] = 0;
  this->mInfo.reserve[32] = 0;
  this->mInfo.reserve[33] = 0;
  this->mInfo.reserve[34] = 0;
  this->mInfo.reserve[35] = 0;
  this->mInfo.reserve[36] = 0;
  this->mInfo.reserve[37] = 0;
  this->mInfo.reserve[38] = 0;
  this->mInfo.reserve[39] = 0;
  this->mInfo.reserve[40] = 0;
  this->mInfo.reserve[41] = 0;
  ((RoleAtt *)this)->ResetNameField();
  return (int)this;
}

// 0x00533DA0
int SceneObjParam::FlushCommands()
{
  return ((RoleSystem *)this)->FlushCommandQueue();
}
