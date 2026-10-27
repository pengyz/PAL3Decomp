#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/Object3D.h"
#include "Role/Actor.h"
#include "GameBase/GRPinput.h"
#include "Role/NPC.h"
#include "Role/ObjectCamera.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Script/PalScriptMgr.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4B7020(...);

// 0x00429EE0
void Object3D::SetTransform(gbMatrix4 *pMatrix)
{
  gbMatrix4 v3; // [esp+0x20] [ebp-0x40] BYREF

  (((PalScriptMgr *)this))->PalScriptMgr::BuildCmdTransform(pMatrix);
  (((gbMatrix4 *)&v3))->gbMatrix4::LoadIdentity();
  if ( LOBYTE(this[1].m_pitch) == 28 && !LODWORD(this[1].m_roll) )
  {
    (((gbMatrix4 *)&v3))->gbMatrix4::SetAxisAngle(GB_AXIS_Z, this->m_roty);
    // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
    // (((gbMatrix4 *)pMatrix))->gbMatrix4::RightMultiply(&v3);
  }
  (((gbMatrix4 *)&v3))->gbMatrix4::SetAxisAngle(GB_AXIS_X, this[3].m_forward.x);
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // (((gbMatrix4 *)pMatrix))->gbMatrix4::RightMultiply(&v3);
  (((gbMatrix4 *)&v3))->gbMatrix4::SetAxisAngle(GB_AXIS_Y, this[1].m_dropy);
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // (((gbMatrix4 *)pMatrix))->gbMatrix4::RightMultiply(&v3);
  (((gbMatrix4 *)pMatrix))->gbMatrix4::RightTranslate(*(gbVec3D *)&this->m_position.z);
}

// 0x0042B1F0
BOOL Object3D::IsVisible()
{
  unsigned int v3; // eax
  unsigned int v4; // eax
  struct gbNodeMsgObj v5; // [esp+0x10] [ebp-0x10] BYREF

  switch ( *(_DWORD *)&this->m_isLoadObj )
  {
    case 1:
      if ( !(((gbVisNode *)this->m_type))->gbVisNode::PopMessage(v5) )
        return 0;
      while ( 1 )
      {
        if ( v5.msgid == 1 )
        {
          v4 = gbCrc32Compute("over");
          if ( v5.param[0] == v4 )
            break;
        }
        if ( !(((gbVisNode *)this->m_type))->gbVisNode::PopMessage(v5) )
          return 0;
      }
      return 1;
    case 3:
      if ( !(((gbVisNode *)this->m_type))->gbVisNode::PopMessage(v5) )
        return *(_DWORD *)(this->m_type + 256) >= 1;
      while ( 1 )
      {
        if ( v5.msgid == 1 )
        {
          v3 = gbCrc32Compute("over");
          if ( v5.param[0] == v3 )
            break;
        }
        if ( !(((gbVisNode *)this->m_type))->gbVisNode::PopMessage(v5) )
          return *(_DWORD *)(this->m_type + 256) >= 1;
      }
      return 1;
    case 4:
      return sub_4B7020(this->m_type) == -1;
    default:
      return 1;
  }
}

// 0x0042B2F0
void Object3D::GetOrientedOBBox(gbOBBox *pOBBox)
{
  gbMatrix4 v3; // [esp+0xC] [ebp-0x40] BYREF

  (((gbGeomNode *)LODWORD(this->RelativePos.z)))->gbGeomNode::GetOBBox(pOBBox);
  (((gbMatrix4 *)&v3))->gbMatrix4::LoadIdentity();
  (((gbMatrix4 *)&v3))->gbMatrix4::SetAxisAngle(GB_AXIS_Y, this[1].m_dropy);
  // [overlay-fix 2026-10-27] 垃圾形/类型错——待语义修复
  // (((gbMatrix4 *)&pOBBox->trans))->gbMatrix4::RightMultiply(&v3);
  (((gbMatrix4 *)&pOBBox->trans))->gbMatrix4::RightTranslate(*(gbVec3D *)&this->m_roty);
}

// 0x0047CB70
Object3D::Object3D()
{
  this->Object3D::LoadSubObject();
  this->m_pCamera = ((ObjectCamera *)0);
}

// 0x0047CB90
OpenNULLFile * Object3D::_todo_0047CB90(const char *pszName, int actionIdx)
{
  gbGeomNode *v4; // eax
  gbGeomNode *v5; // edi
  gbGeomNode *v6; // ecx
  Actor *v7; // eax
  gbGeomNode *v8; // eax
  OpenNULLFile *result; // eax
  char Destination[4]; // [esp+0x10] [ebp-0x60] BYREF
  OpenBaseFile v11; // [esp+0x14] [ebp-0x5C] BYREF
  struct gbOBBox v12; // [esp+0x18] [ebp-0x58] BYREF
  int v13; // [esp+0x6C] [ebp-0x4]

  this->Object3D::LoadSubObject();
  *(_DWORD *)Destination = 0;
  strncpy(Destination, &pszName[strlen(pszName) - 3], 3u);
  v13 = 0;
  if ( !_strcmpi(Destination, byte_596424) )
  {
    this->m_type = 1;
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = (gbGeomNode *)v4;
    LOBYTE(v13) = 1;
    if ( !v4 )
    {
      v6 = 0;
      goto LABEL_5;
    }
LABEL_3:
    v4->gbGeomNode::gbGeomNode();
    v6 = (gbGeomNode *)v5;
LABEL_5:
    LOBYTE(v13) = 0;
    this->m_pol = ((gbGeomNode *)(v6));
    (((gbGeomNode *)v6))->gbGeomNode::LoadFromFile(pszName, 0, 0);
    (((gbGeomNode *)this->m_pol))->gbGeomNode::GetOBBox(&v12);
    goto LABEL_13;
  }
  if ( !_strcmpi(Destination, byte_596420) )
  {
    this->m_type = 3;
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = (gbGeomNode *)v4;
    LOBYTE(v13) = 2;
    if ( !v4 )
    {
      v6 = 0;
      goto LABEL_5;
    }
    goto LABEL_3;
  }
  this->m_type = 2;
  v7 = (Actor *)operator new(0x224u);
  LOBYTE(v13) = 3;
  if ( v7 )
    (((Actor *)v7))->Actor::FastInit();
  else
    v8 = 0;
  LOBYTE(v13) = 0;
  this->m_pol = ((gbGeomNode *)(v8));
  (((Actor *)v8))->Actor::LoadActionSequences(pszName, 0);
  (((Actor *)this->m_pol))->Actor::CompareActionName(actionIdx, 0);
  (*(void ( **)(_DWORD, gbOBBox *, gbChain1DNode *))(**(_DWORD **)&this->m_pol->children.m_Tail[11] + 28))(
    *(_DWORD *)&this->m_pol->children.m_Tail[11],
    &v12,
    this->m_pol->children.m_Tail);
LABEL_13:
  this->m_height = v12.ylen;
  this->m_isLoadObj = 1;
  this->m_visible = 1;
  this->m_action = actionIdx;
  v13 = -1;
  ((OpenNULLFile *)&v11)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x0047CD70
unsigned __int8 Object3D::LoadObject(const char *filename, int act)
{
  unsigned __int8 result; // al
  gbGeomNode *m_subObj; // ecx
  gbGeomNode *v6; // eax
  gbGeomNode *v7; // edi
  gbGeomNode *v8; // ecx
  gbGeomNode *v9; // eax
  gbGeomNode *v10; // edi
  gbGeomNode *v11; // ecx
  int Destination; // [esp+0x10] [ebp-0x14] BYREF
  OpenBaseFile v13; // [esp+0x14] [ebp-0x10] BYREF
  int v14; // [esp+0x20] [ebp-0x4]

  result = this->m_isLoadObj;
  this->m_isLoadSubObj = 0;
  this->m_showSubObj = 0;
  if ( result )
  {
    m_subObj = (gbGeomNode *)this->m_subObj;
    if ( m_subObj )
    {
      (**(void ( ***)(gbGeomNode *, int))((gbChain1DNode *)m_subObj))((gbGeomNode *)(m_subObj), (int)(1));
      this->m_subObj = ((gbGeomNode *)0);
    }
    Destination = 0;
    strncpy((char *)&Destination, &filename[strlen(filename) - 3], 3u);
    v14 = 0;
    if ( _strcmpi((const char *)&Destination, byte_596424) )
    {
      if ( _strcmpi((const char *)&Destination, byte_596420) )
      {
LABEL_15:
        v14 = -1;
        ((OpenNULLFile *)&v13)->OpenNULLFile::OpenNULLFile();
        return result;
      }
      this->m_subType = 3;
      v9 = (gbGeomNode *)operator new(0x118u);
      v10 = (gbGeomNode *)v9;
      LOBYTE(v14) = 2;
      if ( v9 )
      {
        v9->gbGeomNode::gbGeomNode();
        v11 = (gbGeomNode *)v10;
      }
      else
      {
        v11 = 0;
      }
      LOBYTE(v14) = 0;
      this->m_subObj = ((gbGeomNode *)(v11));
      (((gbGeomNode *)v11))->gbGeomNode::LoadFromFile(filename, 0, 0);
      (((gbVisNode *)this->m_subObj))->gbVisNode::SetTimeScale(1.0);
    }
    else
    {
      this->m_subType = 1;
      v6 = (gbGeomNode *)operator new(0x118u);
      v7 = (gbGeomNode *)v6;
      LOBYTE(v14) = 1;
      if ( v6 )
      {
        v6->gbGeomNode::gbGeomNode();
        v8 = (gbGeomNode *)v7;
      }
      else
      {
        v8 = 0;
      }
      LOBYTE(v14) = 0;
      this->m_subObj = ((gbGeomNode *)(v8));
      (((gbGeomNode *)v8))->gbGeomNode::LoadFromFile(filename, 0, 0);
    }
    this->m_isLoadSubObj = 1;
    goto LABEL_15;
  }
  return result;
}

// 0x0047CEE0
void Object3D::LoadSubObject()
{
  gbGeomNode *v2; // edi
  gbGeomNode *m_pol; // ecx

  if ( this->m_type == 1 )
  {
LABEL_7:
    m_pol = (gbGeomNode *)this->m_pol;
    if ( m_pol )
    {
      (**(void ( ***)(gbGeomNode *, int))((gbChain1DNode *)m_pol))((gbGeomNode *)(m_pol), (int)(1));
      this->m_pol = ((gbGeomNode *)0);
    }
    goto LABEL_9;
  }
  if ( this->m_type != 2 )
  {
    if ( this->m_type != 3 )
    {
      this->m_isLoadObj = 0;
      return;
    }
    goto LABEL_7;
  }
  v2 = (gbGeomNode *)this->m_pol;
  if ( v2 )
  {
    (((NPC *)this->m_pol))->NPC::FreeBuffer();
    operator delete(v2);
    this->m_pol = ((gbGeomNode *)0);
    this->m_isLoadObj = 0;
    return;
  }
LABEL_9:
  this->m_isLoadObj = 0;
}

// 0x0047CF40
void Object3D::Destroy()
{
  unsigned int v2; // eax
  struct gbNodeMsgObj v3; // [esp+0xC] [ebp-0x10] BYREF

  if ( this->m_type == 3 && (((gbVisNode *)this->m_pol))->gbVisNode::PopMessage(v3) )
  {
    do
    {
      if ( v3.msgid == 1 )
      {
        v2 = gbCrc32Compute("over");
        if ( v3.param[0] == v2 )
          break;
      }
    }
    while ( (((gbVisNode *)this->m_pol))->gbVisNode::PopMessage(v3) );
  }
}

// 0x0047CFB0
long double Object3D::IsOverCVD(
        
        float fVal,
        float fVal2,
        float fVal3,
        float fVal4,
        float fVal5,
        float fVal6)
{
  return acos(
           (fVal6 * fVal3 + fVal5 * fVal2 + fVal4 * fVal)
         / (sqrt(fVal6 * fVal6 + fVal5 * fVal5 + fVal4 * fVal4)
          * sqrt(fVal3 * fVal3 + fVal2 * fVal2 + fVal * fVal)))
       * 57.295776;
}

// 0x0047D030
void Object3D::VecAngle(float fVal, float fVal2, float fVal3)
{
  float v4; // edx
  float v6; // ecx
  float v7; // st7
  float v8; // st7
  float v9; // st7
  float v10; // st6
  gbVec3D v11; // [esp+0x10] [ebp-0x18] BYREF
  float v12; // [esp+0x20] [ebp-0x8]
  float v13; // [esp+0x24] [ebp-0x4]

  v4 = fVal3;
  v6 = fVal2;
  this->m_position.x = fVal;
  this->m_position.y = v6;
  this->m_position.z = v4;
  fVal = this->RelativePos.x - this->m_position.x;
  v7 = this->RelativePos.y - this->m_position.y;
  v11.x = fVal;
  fVal2 = v7;
  v8 = this->RelativePos.z - this->m_position.z;
  v11.y = fVal2;
  fVal3 = v8;
  v11.z = fVal3;
  this->m_dist = (((gbVec3D *)&v11))->gbVec3D::Length();
  v9 = this->m_position.x - this->RelativePos.x;
  v12 = this->m_position.y - this->RelativePos.y;
  v10 = this->m_position.z - this->RelativePos.z;
  fVal2 = v12;
  v13 = v10;
  fVal = v9;
  fVal3 = v13;
  (((gbVec3D *)&fVal))->gbVec3D::Normalize();
  this->m_degreeToScreen = this->Object3D::IsOverCVD(fVal, fVal2, fVal3, 0.0f, 0.0f, 1.0f);
}

// 0x0047D130
void Object3D::SetObjectPosition(float position, float fVal, float fVal2)
{
  float v4; // edx
  float v6; // ecx
  float v7; // st7
  float v8; // st7
  float v9; // st7
  float v10; // st6
  gbVec3D v11; // [esp+0x10] [ebp-0x18] BYREF
  float v12; // [esp+0x20] [ebp-0x8]
  float v13; // [esp+0x24] [ebp-0x4]

  v4 = fVal2;
  v6 = fVal;
  this->RelativePos.x = position;
  this->RelativePos.y = v6;
  this->RelativePos.z = v4;
  position = this->RelativePos.x - this->m_position.x;
  v7 = this->RelativePos.y - this->m_position.y;
  v11.x = position;
  fVal = v7;
  v8 = this->RelativePos.z - this->m_position.z;
  v11.y = fVal;
  fVal2 = v8;
  v11.z = fVal2;
  this->m_dist = (((gbVec3D *)&v11))->gbVec3D::Length();
  v9 = this->m_position.x - this->RelativePos.x;
  v12 = this->m_position.y - this->RelativePos.y;
  v10 = this->m_position.z - this->RelativePos.z;
  fVal = v12;
  v13 = v10;
  position = v9;
  fVal2 = v13;
  (((gbVec3D *)&position))->gbVec3D::Normalize();
  this->m_degreeToScreen = this->Object3D::IsOverCVD(position, fVal, fVal2, 0.0f, 0.0f, 1.0f);
}

// 0x0047D230
long double Object3D::SetCentrePos()
{
  double v2; // st7
  double v3; // st6
  double v4; // st6
  gbVec3D v6; // [esp+0x4] [ebp-0x24] BYREF
  float v7; // [esp+0x10] [ebp-0x18]
  float v8; // [esp+0x14] [ebp-0x14]
  float v9; // [esp+0x18] [ebp-0x10]
  float v10; // [esp+0x20] [ebp-0x8]
  float v11; // [esp+0x24] [ebp-0x4]

  v7 = 0.0f;
  v8 = 0.0f;
  v2 = this->m_position.x - this->RelativePos.x;
  v3 = this->m_position.y - this->RelativePos.y;
  v9 = 1.0f;
  v10 = v3;
  v4 = this->m_position.z - this->RelativePos.z;
  v6.y = v10;
  v11 = v4;
  v6.x = v2;
  v6.z = v11;
  (((gbVec3D *)&v6))->gbVec3D::Normalize();
  if ( this->m_position.x >= (double)this->RelativePos.x )
    return this->Object3D::IsOverCVD(v6.x, v6.y, v6.z, v7, v8, v9);
  else
    return 360.0 - this->Object3D::IsOverCVD(v6.x, v6.y, v6.z, v7, v8, v9);
}

// 0x0047D320
void Object3D::GetScreenDegree()
{
  long double v2; // st7
  long double v3; // st6
  float m_dist; // st7
  float v5; // st7
  float v6; // st6
  float v7; // st5
  float v8; // st5
  float v9; // eax
  float v10; // ecx
  float v11; // st7
  float v12; // st6
  float v13; // [esp+0x4] [ebp-0x28]
  gbVec3D v14; // [esp+0x8] [ebp-0x24] BYREF
  float v15; // [esp+0x14] [ebp-0x18]
  float v16; // [esp+0x18] [ebp-0x14]
  float v17; // [esp+0x1C] [ebp-0x10]
  float v18; // [esp+0x24] [ebp-0x8]
  float v19; // [esp+0x28] [ebp-0x4]

  v2 = this->m_yaw * 0.017453292;
  v3 = this->m_pitch * 0.017453292;
  v13 = cos(v3);
  this->m_forward.x = sin(v2) * v13;
  this->m_forward.y = sin(v3);
  this->m_forward.z = -(cos(v2) * v13);
  m_dist = this->m_dist;
  v15 = m_dist * this->m_forward.x;
  v16 = m_dist * this->m_forward.y;
  v5 = m_dist * this->m_forward.z;
  v6 = this->RelativePos.x - v15;
  v7 = this->RelativePos.y - v16;
  v15 = 0.0f;
  v16 = v7;
  v8 = this->RelativePos.z - v5;
  v9 = v16;
  v16 = 0.0f;
  this->m_position.y = v9;
  v17 = v8;
  v10 = v17;
  v17 = 1.0f;
  this->m_position.x = v6;
  this->m_position.z = v10;
  v11 = this->m_position.x - this->RelativePos.x;
  v18 = this->m_position.y - this->RelativePos.y;
  v12 = this->m_position.z - this->RelativePos.z;
  v14.y = v18;
  v19 = v12;
  v14.x = v11;
  v14.z = v19;
  (((gbVec3D *)&v14))->gbVec3D::Normalize();
  this->m_degreeToScreen = this->Object3D::IsOverCVD(v14.x, v14.y, v14.z, v15, v16, v17);
}

// 0x0047D440
void Object3D::RenderObjectScene(gbVec3D scrVec, gbMatrixStack *pMatrixStack)
{
  int v2; // ecx
  int v3; // esi
  gbCamera **v4; // eax
  gbSceneGraph *pSceneGraph; // edi
  gbMatrixStack *v6; // edi
  float v8; // st7
  unsigned __int8 v9; // c0
  unsigned __int8 v10; // c3
  float v11; // [esp+0x38] [ebp-0x28]
  float v12; // [esp+0x38] [ebp-0x28]
  float v13; // [esp+0x40] [ebp-0x20]
  gbSceneGraph *v14; // [esp+0x50] [ebp-0x10]
  struct gbVec3D v15; // [esp+0x54] [ebp-0xC] BYREF
  _UNKNOWN *retaddr; // [esp+0x60] [ebp+0x0] BYREF
  float pMatrixStacka; // [esp+0x70] [ebp+0x10]

  v3 = v2;
  v4 = (gbCamera **)*(gbCamera ***)(v2 + 84);
  if ( !v4 || !*(_BYTE *)v2 || !*(_BYTE *)(v2 + 80) )
    return;
  pSceneGraph = gfxMgr->pSceneGraph;
  v14 = (gbSceneGraph *)pSceneGraph;
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(*v4);
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  v6 = pMatrixStack;
  if ( !pMatrixStack )
    v6 = gfxMgr->pMatrixStack[1];
  (((gbCamera *)**(gbCamera ***)(v3 + 84)))->gbCamera::SetAsCurrent(3);
  (((gbMatrixStack *)v6))->gbMatrixStack::Push();
  (((gbMatrixStack *)v6))->gbMatrixStack::Translate(*(gbVec3D *)(v3 + 32));
  (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(*(float *)(v3 + 60), * (gbVec3D *)&retaddr);
  retaddr = 0;
  (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(*(float *)(v3 + 56), * (gbVec3D *)&retaddr);
  if ( !*(_DWORD *)(v3 + 144) && *(_BYTE *)(v3 + 120) )
  {
    v8 = 360.0f - *(float *)(v3 + 116);
    if ( !(v9 | v10) )
      v8 = -v8;
    pMatrixStacka = v8;
    retaddr = 0;
    (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(pMatrixStacka, * (gbVec3D *)&retaddr);
  }
  (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(*(float *)(v3 + 64), * (gbVec3D *)&retaddr);
  v13 = *(float *)(v3 + 68);
  v15.z = 1.0;
  retaddr = 0;
  (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(v13, * (gbVec3D *)&v15.z);
  v11 = *(float *)(v3 + 72);
  v15.x = 0.0;
  v15.y = 1.0;
  v15.z = 0.0;
  (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(v11,  v15);
  v12 = *(float *)(v3 + 76);
  v15.x = 0.0;
  v15.y = 0.0;
  v15.z = 1.0;
  (((gbMatrixStack *)v6))->gbMatrixStack::Rotate(v12,  v15);
  switch ( *(_DWORD *)(v3 + 4) )
  {
    case 1:
      goto LABEL_16;
    case 2:
      (((Actor *)*(Actor **)(v3 + 8)))->Actor::DispatchAction(0);
      break;
    case 3:
LABEL_16:
      (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(v3 + 8) + 16))(*(_DWORD *)(v3 + 8), 0);
      break;
  }
  (((gbMatrixStack *)v6))->gbMatrixStack::Pop();
  if ( *(_BYTE *)(v3 + 21) && *(_BYTE *)(v3 + 20) )
  {
    (((gbMatrixStack *)v6))->gbMatrixStack::Push();
    v15.x = *(float *)(v3 + 32);
    v15.y = *(float *)(v3 + 36) + *(float *)(v3 + 24);
    v15.z = *(float *)(v3 + 40);
    (((gbMatrixStack *)v6))->gbMatrixStack::Translate(v15);
    if ( *(_DWORD *)(v3 + 16) == 1 || *(_DWORD *)(v3 + 16) == 3 )
      (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(v3 + 12) + 16))(*(_DWORD *)(v3 + 12), 0);
    (((gbMatrixStack *)v6))->gbMatrixStack::Pop();
  }
  (((gbSceneGraph *)v14))->gbSceneGraph::End();
}

// 0x0047D690
// bad sp value at call has been detected, the output may be wrong!
void Object3D::CaculateRelative(float fVal)
{
  int v2; // ebx
  unsigned int v3; // ebp
  int v4; // edi
  char m_showSubObj; // al
  float v7; // eax
  int m_rotDstMode; // eax
  double v9; // st7
  double v10; // st6
  float v11; // st7
  float v13; // c0
  unsigned __int8 v14; // c3
  double v15; // st7
  float v16; // st6
  float v17; // st7
  float v19; // c0
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st6
  float m_rotRelative; // st7
  unsigned __int8 v26; // c0
  unsigned __int8 v27; // c3
  double v28; // st7
  int v29; // [esp-0x8] [ebp-0x24]
  int v30; // [esp-0x4] [ebp-0x20]
  struct gbNodeMsgObj v31; // [esp+0x0] [ebp-0x1C] BYREF
  float v32; // [esp+0x10] [ebp-0xC]

  if ( !this->m_isLoadObj )
    return;
  if ( this->m_visible )
  {
    switch ( this->m_type )
    {
      case 1u:
LABEL_10:
        (*(void ( **)(gbGeomNode *))(*(_DWORD *)((gbChain1DNode *)this->m_pol) + 20))(this->m_pol);
        break;
      case 2u:
        if ( (((Object3D *)this->m_pol))->Object3D::GetVisNode() )
          (((Actor *)this->m_pol))->Actor::CompareActionName(0, 0);
        (((Actor *)this->m_pol))->Actor::QueryState(v31.param[1]);
        break;
      case 3u:
        goto LABEL_10;
    }
  }
  m_showSubObj = this->m_showSubObj;
  v31.param[0] = v3;
  if ( m_showSubObj && this->m_isLoadSubObj )
  {
    if ( this->m_subType == 1 )
    {
      (*(void ( **)(gbGeomNode *, unsigned int))(*(_DWORD *)((gbChain1DNode *)this->m_subObj) + 20))(
        this->m_subObj,
        v31.param[0]);
    }
    else if ( this->m_subType == 3 )
    {
      (*(void ( **)(gbGeomNode *, unsigned int))(*(_DWORD *)((gbChain1DNode *)this->m_subObj) + 20))(
        this->m_subObj,
        v31.param[0]);
      // [overlay-fix 2026-10-27] 垃圾形条件（成员缺失/类型非法）——待语义修复
      // if ( (((gbVisNode *)this->m_subObj))->gbVisNode::PopMessage(*(gbNodeMsgObj *)&v31.pfrom) )
      if ( 0 )
      {
        v30 = v2;
        v29 = v4;
        do
        {
          if ( v31.param[1] == 1 )
          {
            // [overlay-fix 2026-10-27] 垃圾形表达式——待语义修复
            // v7 = (gbVisNode *)gbCrc32Compute("over");
            v7 = 0;
            // [overlay-fix 2026-10-27] 垃圾形条件（成员缺失/类型非法）——待语义修复
            // if ( v31.pfrom == v7 )
            if ( 0 )
            {
              (*(void ( **)(gbGeomNode *, _DWORD, int, int))(*(_DWORD *)((gbChain1DNode *)this->m_subObj) + 24))(
                this->m_subObj,
                0,
                v29,
                v30);
              (((gbVisNode *)this->m_subObj))->gbVisNode::SetTimeScale(1.0);
            }
          }
        }
        while ( (((gbVisNode *)this->m_subObj))->gbVisNode::PopMessage(v31) );
      }
    }
  }
  if ( this->m_bRotDstDegree )
  {
    m_rotDstMode = this->m_rotDstMode;
    if ( m_rotDstMode )
    {
      if ( m_rotDstMode == 1 )
      {
        if ( this->m_rotDegree >= (double)this->m_rotDstDegree )
        {
          if ( this->m_rotDegree <= (double)this->m_rotDstDegree )
          {
            if ( this->m_rotDegree > 360.0f )
              this->m_rotDegree = this->m_rotDegree - 360.0f;
            if ( this->m_rotDegree < 0.0f )
              this->m_rotDegree = this->m_rotDegree + 360.0f;
            this->m_bRotDstDegree = 0;
          }
          else
          {
            v15 = v32 * 50.0 * this->m_rotDstSpeed;
            v16 = this->m_rotDegree - v15;
            this->m_rotDegree = v16;
            if ( v16 <= this->m_rotDstDegree )
              this->m_rotDegree = this->m_rotDstDegree;
            v17 = this->m_roty - v15;
            this->m_roty = v17;
            if ( v19 )
              this->m_roty = v17 + 360.0f;
          }
        }
        else
        {
          v9 = v32 * 50.0 * this->m_rotDstSpeed;
          v10 = v9 + this->m_rotDegree;
          this->m_rotDegree = v10;
          if ( v10 >= this->m_rotDstDegree )
            this->m_rotDegree = this->m_rotDstDegree;
          v11 = v9 + this->m_roty;
          this->m_roty = v11;
          // [overlay-fix 2026-10-27] 垃圾形条件（成员缺失/类型非法）——待语义修复
          // if ( !(v13 | v14) )
          if ( 0 )
            this->m_roty = v11 - 360.0f;
        }
      }
      return;
    }
    if ( this->m_rotDegree >= (double)this->m_rotDstDegree )
    {
      if ( this->m_rotDegree <= (double)this->m_rotDstDegree )
      {
        this->m_bRotDstDegree = 0;
      }
      else
      {
        v22 = v32 * 50.0 * this->m_rotDstSpeed;
        v23 = this->m_rotDegree - v22;
        this->m_rotDegree = v23;
        this->m_rotRelative = this->m_rotRelative - v22;
        if ( v23 <= this->m_rotDstDegree )
          this->m_rotDegree = this->m_rotDstDegree;
      }
    }
    else
    {
      v20 = v32 * 50.0 * this->m_rotDstSpeed;
      v21 = v20 + this->m_rotDegree;
      this->m_rotDegree = v21;
      this->m_rotRelative = v20 + this->m_rotRelative;
      if ( v21 >= this->m_rotDstDegree )
        this->m_rotDegree = this->m_rotDstDegree;
    }
    m_rotRelative = this->m_rotRelative;
    if ( v26 | v27 )
    {
      if ( m_rotRelative >= 0.0f )
      {
LABEL_53:
        this->m_yaw = this->m_rotRelative;
        this->Object3D::GetScreenDegree();
        return;
      }
      v28 = this->m_rotRelative + 360.0;
    }
    else
    {
      v28 = m_rotRelative - 360.0;
    }
    this->m_rotRelative = v28;
    goto LABEL_53;
  }
}

// 0x0047D9D0
void * Object3D::SetupCamera(int nVal1)
{
  void *result; // eax
  float v3; // [esp+0x0] [ebp-0x2C]
  float v4; // [esp+0x4] [ebp-0x28]
  struct gbRay v5; // [esp+0x14] [ebp-0x18] BYREF
  int *v6; // [esp+0x34] [ebp+0x8]

  memset(&v5, 0, sizeof(v5));
  v4 = 1.0f - ((float)v6[1] + (float)v6[1]) / (float)g_DrvInfo.height;
  v3 = ((float)*v6 + (float)*v6) / (float)g_DrvInfo.width - 1.0f;
  (((gbCamera *)this->m_pCamera->m_pCamera))->gbCamera::GetRayToScreen(v3, v4, &v5);
  result = (void *)nVal1;
  qmemcpy((void *)nVal1, &v5, 0x18u);
  return result;
}

// 0x0047DA60
bool Object3D::Update()
{
  void *v2; // esi
  unsigned int m_type; // eax
  unsigned int v4; // eax
  unsigned int v5; // eax
  struct tagPOINT Point; // [esp+0x4] [ebp-0x84] BYREF
  struct gbOBBox actionId; // [esp+0xC] [ebp-0x7C] BYREF
  gbRay v9; // [esp+0x58] [ebp-0x30] BYREF
  int nVal1[6]; // [esp+0x70] [ebp-0x18] BYREF

  if ( !this->m_visible || this->m_bRotDstDegree || g_Input.KeyInfo[0].PressTime != 1 )
    return 0;
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&Point);
  v2 = (void *)this->Object3D::SetupCamera((int)nVal1);
  m_type = this->m_type;
  qmemcpy(&v9, v2, sizeof(v9));
  v4 = m_type - 1;
  if ( v4 )
  {
    v5 = v4 - 1;
    if ( v5 )
    {
      if ( v5 != 1 )
        return (((gbRay *)&v9))->gbRay::IsColOBB(actionId) != 0;
      (((gbGeomNode *)this->m_pol))->gbGeomNode::GetTotalOBBox(&actionId);
    }
    else
    {
      (((Actor *)this->m_pol))->Actor::PlayAction((int)&actionId);
    }
  }
  else
  {
    (((gbGeomNode *)this->m_pol))->gbGeomNode::GetOBBox(&actionId);
  }
  (((gbMatrix4 *)&actionId.trans))->gbMatrix4::RightTranslate(this->m_position);
  return (((gbRay *)&v9))->gbRay::IsColOBB(actionId) != 0;
}

// 0x0047DB40
bool Object3D::GetMouseRay(gbRay *retstr, tagPOINT *pPOINT)
{
  Object3D *v2; // ecx
  Object3D *v3; // ebx
  void *v4; // esi
  unsigned int m_type; // eax
  unsigned int v6; // eax
  unsigned int v7; // eax
  struct tagPOINT Point; // [esp+0x4] [ebp-0x84] BYREF
  struct gbOBBox actionId; // [esp+0xC] [ebp-0x7C] BYREF
  gbRay v11; // [esp+0x58] [ebp-0x30] BYREF
  int nVal1[6]; // [esp+0x70] [ebp-0x18] BYREF

  v3 = (Object3D *)v2;
  if ( !v2->m_visible || v2->m_bRotDstDegree || (g_Input.KeyInfo[(_DWORD)retstr].Data & 0xF) != 1 )
    return 0;
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&Point);
  v4 = (((Object3D *)v3))->Object3D::SetupCamera((int)nVal1);
  m_type = v3->m_type;
  qmemcpy(&v11, v4, sizeof(v11));
  v6 = m_type - 1;
  if ( v6 )
  {
    v7 = v6 - 1;
    if ( v7 )
    {
      if ( v7 != 1 )
        return (((gbRay *)&v11))->gbRay::IsColOBB(actionId) != 0;
      (((gbGeomNode *)v3->m_pol))->gbGeomNode::GetTotalOBBox(&actionId);
    }
    else
    {
      (((Actor *)v3->m_pol))->Actor::PlayAction((int)&actionId);
    }
  }
  else
  {
    (((gbGeomNode *)v3->m_pol))->gbGeomNode::GetOBBox(&actionId);
  }
  (((gbMatrix4 *)&actionId.trans))->gbMatrix4::RightTranslate(v3->m_position);
  return (((gbRay *)&v11))->gbRay::IsColOBB(actionId) != 0;
}

// 0x0047DC60
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
bool Object3D::CheckMouseLPressed()
{
  return this->Object3D::CheckMousePressed();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x0047DC70
bool Object3D::CheckMousePressed()
{
  bool result; // al

  result = 0;
  dword_DE4C94 = 1094713344;
  return result;
}

// 0x0047DD60
int Object3D::SetBlendMode(unsigned __int8 *thisa)
{
  return BYTE1(this[24].m_forward.y);
}

// 0x00537060
gbVisNode * Object3D::GetVisNode()
{
  return (gbVisNode *)this->Object3D::CheckMessage("over");
}

// 0x00537070
int Object3D::CheckMessage(const char *pszMsgName)
{
  unsigned int v3; // eax
  struct gbNodeMsgObj v5; // [esp+0x10] [ebp-0x10] BYREF

  if ( !(((gbVisNode *)this->m_subType))->gbVisNode::PopMessage(v5) )
    return 0;
  while ( 1 )
  {
    if ( v5.msgid == 1 )
    {
      v3 = gbCrc32Compute(pszMsgName);
      if ( v5.param[0] == v3 )
        break;
    }
    if ( !(((gbVisNode *)this->m_subType))->gbVisNode::PopMessage(v5) )
      return 0;
  }
  return 1;
}
