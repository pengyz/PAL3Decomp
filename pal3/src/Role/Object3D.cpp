#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/Object3D.h"

// Forward declarations for unnamed functions
int sub_445FA0(void *a2); // from annotations
int sub_4B7020(...);
void sub_536D20(Actor *_this, const char *a2, int a3); // from annotations

// Unnamed globals (extern)
extern int dword_DE4C94;
extern const char * off_596420;
extern const char * off_596424;

// 0x00429EE0
void Object3D::SetTransform(gbMatrix4 *pMatrix)
{
  gbMatrix4 v3; // [esp+0x20] [ebp-0x40] BYREF

  ((PalScriptMgr *)this)->BuildCmdTransform(pMatrix);
  ((gbMatrix4 *)&v3)->LoadIdentity();
  if ( *((_BYTE *)this + 244) == 28 && !*((_DWORD *)this + 62) )
  {
    ((gbMatrix4 *)&v3)->SetAxisAngle(2, LODWORD(this->m_roty));
    ((gbMatrix4 *)pMatrix)->RightMultiply(&v3);
  }
  ((gbMatrix4 *)&v3)->SetAxisAngle(0, *((_DWORD *)this + 140));
  ((gbMatrix4 *)pMatrix)->RightMultiply(&v3);
  ((gbMatrix4 *)&v3)->SetAxisAngle(1, *((_DWORD *)this + 56));
  ((gbMatrix4 *)pMatrix)->RightMultiply(&v3);
  ((gbMatrix4 *)pMatrix)->RightTranslate((gbVec3D *)&this->m_position.z);
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
      if ( !((gbVisNode *)this->m_type)->PopMessage(v5) )
        return 0;
      while ( 1 )
      {
        if ( v5.msgid == 1 )
        {
          v4 = gbCrc32Compute("over");
          if ( v5.param[0] == v4 )
            break;
        }
        if ( !((gbVisNode *)this->m_type)->PopMessage(v5) )
          return 0;
      }
      return 1;
    case 3:
      if ( !((gbVisNode *)this->m_type)->PopMessage(v5) )
        return *(_DWORD *)(this->m_type + 256) >= 1;
      while ( 1 )
      {
        if ( v5.msgid == 1 )
        {
          v3 = gbCrc32Compute("over");
          if ( v5.param[0] == v3 )
            break;
        }
        if ( !((gbVisNode *)this->m_type)->PopMessage(v5) )
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

  ((gbGeomNode *)LODWORD(this->RelativePos.z))->GetOBBox(pOBBox);
  ((gbMatrix4 *)&v3)->LoadIdentity();
  ((gbMatrix4 *)&v3)->SetAxisAngle(1, *((_DWORD *)this + 56));
  ((gbMatrix4 *)pOBBox)->RightMultiply(&v3);
  ((gbMatrix4 *)pOBBox)->RightTranslate((gbVec3D *)&this->m_roty);
}

// 0x0047CB70
Object3D::Object3D()
{

  this->m_pCamera = 0;
}

// 0x0047CB90
OpenNULLFile * Object3D::_Object3D(const char *pszName, int actionIdx)
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

  *(_DWORD *)Destination = 0;
  strncpy(Destination, &pszName[strlen(pszName) - 3], 3u);
  v13 = 0;
  if ( !_strcmpi(Destination, (const char *)&off_596424) )
  {
    this->m_type = 1;
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = v4;
    LOBYTE(v13) = 1;
    if ( !v4 )
    {
      v6 = 0;
      goto LABEL_5;
    }
LABEL_3:
    v6 = v5;
LABEL_5:
    LOBYTE(v13) = 0;
    this->m_pol = v6;
    ((gbGeomNode *)v6)->LoadFromFile(pszName, 0, 0);
    ((gbGeomNode *)this->m_pol)->GetOBBox(&v12);
    goto LABEL_13;
  }
  if ( !_strcmpi(Destination, (const char *)&off_596420) )
  {
    this->m_type = 3;
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = v4;
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
    ((Actor *)v7)->FastInit();
  else
    v8 = 0;
  LOBYTE(v13) = 0;
  this->m_pol = v8;
  sub_536D20((Actor *)v8, pszName, 0);
  ((Actor *)this->m_pol)->CompareActionName(actionIdx, 0);
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
    m_subObj = this->m_subObj;
    if ( m_subObj )
    {
      (**(void ( ***)(gbGeomNode *, int))m_subObj)(m_subObj, 1);
      this->m_subObj = 0;
    }
    Destination = 0;
    strncpy((char *)&Destination, &filename[strlen(filename) - 3], 3u);
    v14 = 0;
    if ( _strcmpi((const char *)&Destination, (const char *)&off_596424) )
    {
      if ( _strcmpi((const char *)&Destination, (const char *)&off_596420) )
      {
LABEL_15:
        v14 = -1;
        return result;
      }
      this->m_subType = 3;
      v9 = (gbGeomNode *)operator new(0x118u);
      v10 = v9;
      LOBYTE(v14) = 2;
      if ( v9 )
      {
        v11 = v10;
      }
      else
      {
        v11 = 0;
      }
      LOBYTE(v14) = 0;
      this->m_subObj = v11;
      ((gbGeomNode *)v11)->LoadFromFile(filename, 0, 0);
      ((gbVisNode *)this->m_subObj)->SetTimeScale(1.0);
    }
    else
    {
      this->m_subType = 1;
      v6 = (gbGeomNode *)operator new(0x118u);
      v7 = v6;
      LOBYTE(v14) = 1;
      if ( v6 )
      {
        v8 = v7;
      }
      else
      {
        v8 = 0;
      }
      LOBYTE(v14) = 0;
      this->m_subObj = v8;
      ((gbGeomNode *)v8)->LoadFromFile(filename, 0, 0);
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
    m_pol = this->m_pol;
    if ( m_pol )
    {
      (**(void ( ***)(gbGeomNode *, int))m_pol)(m_pol, 1);
      this->m_pol = 0;
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
  v2 = this->m_pol;
  if ( v2 )
  {
    ((NPC *)this->m_pol)->FreeBuffer();
    operator delete(v2);
    this->m_pol = 0;
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

  if ( this->m_type == 3 && ((gbVisNode *)this->m_pol)->PopMessage(v3) )
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
    while ( ((gbVisNode *)this->m_pol)->PopMessage(v3) );
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
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st6
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
  this->m_dist = ((gbVec3D *)&v11)->Length();
  v9 = this->m_position.x - this->RelativePos.x;
  v12 = this->m_position.y - this->RelativePos.y;
  v10 = this->m_position.z - this->RelativePos.z;
  fVal2 = v12;
  v13 = v10;
  fVal = v9;
  fVal3 = v13;
  ((gbVec3D *)&fVal)->Normalize();
  this->m_degreeToScreen = this->IsOverCVD(fVal, fVal2, fVal3, 0.0, 0.0, 1.0);
}

// 0x0047D130
void Object3D::SetObjectPosition(float position, float fVal, float fVal2)
{
  float v4; // edx
  float v6; // ecx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st6
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
  this->m_dist = ((gbVec3D *)&v11)->Length();
  v9 = this->m_position.x - this->RelativePos.x;
  v12 = this->m_position.y - this->RelativePos.y;
  v10 = this->m_position.z - this->RelativePos.z;
  fVal = v12;
  v13 = v10;
  position = v9;
  fVal2 = v13;
  ((gbVec3D *)&position)->Normalize();
  this->m_degreeToScreen = this->IsOverCVD(position, fVal, fVal2, 0.0, 0.0, 1.0);
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

  v7 = 0.0;
  v8 = 0.0;
  v2 = this->m_position.x - this->RelativePos.x;
  v3 = this->m_position.y - this->RelativePos.y;
  v9 = 1.0;
  v10 = v3;
  v4 = this->m_position.z - this->RelativePos.z;
  v6.y = v10;
  v11 = v4;
  v6.x = v2;
  v6.z = v11;
  ((gbVec3D *)&v6)->Normalize();
  if ( this->m_position.x >= (double)this->RelativePos.x )
    return this->IsOverCVD(v6.x, v6.y, v6.z, v7, v8, v9);
  else
    return 360.0 - this->IsOverCVD(v6.x, v6.y, v6.z, v7, v8, v9);
}

// 0x0047D320
void Object3D::GetScreenDegree()
{
  long double v2; // st7
  long double v3; // st6
  double m_dist; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st5
  float v9; // eax
  float v10; // ecx
  double v11; // st7
  double v12; // st6
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
  v15 = 0.0;
  v16 = v7;
  v8 = this->RelativePos.z - v5;
  v9 = v16;
  v16 = 0.0;
  this->m_position.y = v9;
  v17 = v8;
  v10 = v17;
  v17 = 1.0;
  this->m_position.x = v6;
  this->m_position.z = v10;
  v11 = this->m_position.x - this->RelativePos.x;
  v18 = this->m_position.y - this->RelativePos.y;
  v12 = this->m_position.z - this->RelativePos.z;
  v14.y = v18;
  v19 = v12;
  v14.x = v11;
  v14.z = v19;
  ((gbVec3D *)&v14)->Normalize();
  this->m_degreeToScreen = this->IsOverCVD(v14.x, v14.y, v14.z, v15, v16, v17);
}

// 0x0047D440
void Object3D::GetScreenDegree(int a2, int a3, int a4, gbMatrixStack *a5)
{
  ObjectCamera *m_pCamera; // eax
  gbSceneGraph *pSceneGraph; // edi
  gbMatrixStack *v8; // edi
  double v10; // st7
  unsigned __int8 v11; // c0
  unsigned __int8 v12; // c3
  float m_dropy; // [esp+0x38] [ebp-0x28]
  float m_dropz; // [esp+0x38] [ebp-0x28]
  float m_dropx; // [esp+0x40] [ebp-0x20]
  gbSceneGraph *v16; // [esp+0x50] [ebp-0x10]
  struct gbVec3D v17; // [esp+0x54] [ebp-0xC] BYREF
  _UNKNOWN *retaddr; // [esp+0x60] [ebp+0x0] BYREF
  float v19; // [esp+0x70] [ebp+0x10]

  m_pCamera = this->m_pCamera;
  if ( !m_pCamera || !this->m_isLoadObj || !this->m_visible )
    return;
  pSceneGraph = gfxMgr->pSceneGraph;
  v16 = pSceneGraph;
  ((gbSceneGraph *)pSceneGraph)->Begin(m_pCamera->m_pCamera);
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  v8 = a5;
  if ( !a5 )
    v8 = gfxMgr->pMatrixStack[1];
  ((gbCamera *)this->m_pCamera->m_pCamera)->SetAsCurrent(3);
  ((gbMatrixStack *)v8)->Push();
  ((gbMatrixStack *)v8)->Translate(this->m_position);
  ((gbMatrixStack *)v8)->Rotate(this->m_rotx, (gbVec3D *)&retaddr);
  retaddr = 0;
  ((gbMatrixStack *)v8)->Rotate(this->m_roty, (gbVec3D *)&retaddr);
  if ( !this->m_rotDstMode && this->m_isActionRelativeRot )
  {
    v10 = 360.0 - this->m_degreeToScreen;
    if ( !(v11 | v12) )
      v10 = -v10;
    v19 = v10;
    retaddr = 0;
    ((gbMatrixStack *)v8)->Rotate(v19, (gbVec3D *)&retaddr);
  }
  ((gbMatrixStack *)v8)->Rotate(this->m_rotz, (gbVec3D *)&retaddr);
  m_dropx = this->m_dropx;
  v17.z = 1.0;
  retaddr = 0;
  ((gbMatrixStack *)v8)->Rotate(m_dropx, (gbVec3D *)&v17.z);
  m_dropy = this->m_dropy;
  v17.x = 0.0;
  v17.y = 1.0;
  v17.z = 0.0;
  ((gbMatrixStack *)v8)->Rotate(m_dropy, v17);
  m_dropz = this->m_dropz;
  v17.x = 0.0;
  v17.y = 0.0;
  v17.z = 1.0;
  ((gbMatrixStack *)v8)->Rotate(m_dropz, v17);
  switch ( this->m_type )
  {
    case 1u:
      goto LABEL_16;
    case 2u:
      ((Actor *)this->m_pol)->DispatchAction(0);
      break;
    case 3u:
LABEL_16:
      (*(void (**)(gbGeomNode *, _DWORD))(*(_DWORD *)this->m_pol + 16))(this->m_pol, 0);
      break;
  }
  ((gbMatrixStack *)v8)->Pop();
  if ( this->m_showSubObj && this->m_isLoadSubObj )
  {
    ((gbMatrixStack *)v8)->Push();
    v17.x = this->m_position.x;
    v17.y = this->m_position.y + this->m_subObjHeight;
    v17.z = this->m_position.z;
    ((gbMatrixStack *)v8)->Translate(v17);
    if ( this->m_subType == 1 || this->m_subType == 3 )
      (*(void (**)(gbGeomNode *, _DWORD))(*(_DWORD *)this->m_subObj + 16))(this->m_subObj, 0);
    ((gbMatrixStack *)v8)->Pop();
  }
  ((gbSceneGraph *)v16)->End();
}

// 0x0047D690
void Object3D::CaculateRelative(float fVal)
{
  unsigned int v3; // eax
  int m_rotDstMode; // eax
  double v5; // st7
  double v6; // st6
  double v7; // st7
  unsigned __int8 v9; // c0
  unsigned __int8 v10; // c3
  double v11; // st7
  double v12; // st6
  double v13; // st7
  char v15; // c0
  double v16; // st7
  double v17; // st6
  double v18; // st7
  double v19; // st6
  double m_rotRelative; // st7
  unsigned __int8 v22; // c0
  unsigned __int8 v23; // c3
  double v24; // st7
  struct gbNodeMsgObj v25; // [esp+0xC] [ebp-0x10] BYREF

  if ( !this->m_isLoadObj )
    return;
  if ( this->m_visible )
  {
    switch ( this->m_type )
    {
      case 1u:
LABEL_10:
        (*(void ( **)(gbGeomNode *))(*(_DWORD *)this->m_pol + 20))(this->m_pol);
        break;
      case 2u:
        if ( ((Object3D *)this->m_pol)->GetVisNode() )
          ((Actor *)this->m_pol)->CompareActionName(0, 0);
        ((Actor *)this->m_pol)->QueryState();
        break;
      case 3u:
        goto LABEL_10;
    }
  }
  if ( this->m_showSubObj && this->m_isLoadSubObj )
  {
    if ( this->m_subType == 1 )
    {
      (*(void ( **)(gbGeomNode *))(*(_DWORD *)this->m_subObj + 20))(this->m_subObj);
    }
    else if ( this->m_subType == 3 )
    {
      (*(void ( **)(gbGeomNode *))(*(_DWORD *)this->m_subObj + 20))(this->m_subObj);
      while ( ((gbVisNode *)this->m_subObj)->PopMessage(v25) )
      {
        if ( v25.msgid == 1 )
        {
          v3 = gbCrc32Compute("over");
          if ( v25.param[0] == v3 )
          {
            (*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)this->m_subObj + 24))(this->m_subObj, 0);
            ((gbVisNode *)this->m_subObj)->SetTimeScale(1.0);
          }
        }
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
            if ( this->m_rotDegree > 360.0 )
              this->m_rotDegree = this->m_rotDegree - 360.0;
            if ( this->m_rotDegree < 0.0 )
              this->m_rotDegree = this->m_rotDegree + 360.0;
            this->m_bRotDstDegree = 0;
          }
          else
          {
            v11 = fVal * 50.0 * this->m_rotDstSpeed;
            v12 = this->m_rotDegree - v11;
            this->m_rotDegree = v12;
            if ( v12 <= this->m_rotDstDegree )
              this->m_rotDegree = this->m_rotDstDegree;
            v13 = this->m_roty - v11;
            this->m_roty = v13;
            if ( v15 )
              this->m_roty = v13 + 360.0;
          }
        }
        else
        {
          v5 = fVal * 50.0 * this->m_rotDstSpeed;
          v6 = v5 + this->m_rotDegree;
          this->m_rotDegree = v6;
          if ( v6 >= this->m_rotDstDegree )
            this->m_rotDegree = this->m_rotDstDegree;
          v7 = v5 + this->m_roty;
          this->m_roty = v7;
          if ( !(v9 | v10) )
            this->m_roty = v7 - 360.0;
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
        v18 = fVal * 50.0 * this->m_rotDstSpeed;
        v19 = this->m_rotDegree - v18;
        this->m_rotDegree = v19;
        this->m_rotRelative = this->m_rotRelative - v18;
        if ( v19 <= this->m_rotDstDegree )
          this->m_rotDegree = this->m_rotDstDegree;
      }
    }
    else
    {
      v16 = fVal * 50.0 * this->m_rotDstSpeed;
      v17 = v16 + this->m_rotDegree;
      this->m_rotDegree = v17;
      this->m_rotRelative = v16 + this->m_rotRelative;
      if ( v17 >= this->m_rotDstDegree )
        this->m_rotDegree = this->m_rotDstDegree;
    }
    m_rotRelative = this->m_rotRelative;
    if ( v22 | v23 )
    {
      if ( m_rotRelative >= 0.0 )
      {
LABEL_52:
        this->m_yaw = this->m_rotRelative;

        return;
      }
      v24 = this->m_rotRelative + 360.0;
    }
    else
    {
      v24 = m_rotRelative - 360.0;
    }
    this->m_rotRelative = v24;
    goto LABEL_52;
  }
}

// 0x0047D9D0
void * Object3D::SetupCamera()
{
  float v2; // [esp+0x0] [ebp-0x2C]
  float v3; // [esp+0x4] [ebp-0x28]
  struct gbRay v4; // [esp+0x14] [ebp-0x18] BYREF
  gbRay *v5; // [esp+0x30] [ebp+0x4]
  int *v6; // [esp+0x34] [ebp+0x8]

  memset(&v4, 0, sizeof(v4));
  v3 = 1.0 - ((double)v6[1] + (double)v6[1]) / (double)g_DrvInfo.height;
  v2 = ((double)*v6 + (double)*v6) / (double)g_DrvInfo.width - 1.0;
  ((gbCamera *)this->m_pCamera->m_pCamera)->GetRayToScreen(v2, v3, &v4);
  qmemcpy(v5, &v4, sizeof(struct gbRay));
  return v5;
}

// 0x0047DA60
bool Object3D::Update()
{
  void *v2; // esi
  unsigned int m_type; // eax
  unsigned int v4; // eax
  unsigned int v5; // eax
  struct gbOBBox actionId; // [esp+0xC] [ebp-0x7C] BYREF
  gbRay v8; // [esp+0x58] [ebp-0x30] BYREF

  if ( !this->m_visible || this->m_bRotDstDegree || g_Input.KeyInfo[0].PressTime != 1 )
    return 0;
  ((GRPinput *)&g_Input)->GetCursorPos();
  v2 = this->SetupCamera();
  m_type = this->m_type;
  qmemcpy(&v8, v2, sizeof(v8));
  v4 = m_type - 1;
  if ( v4 )
  {
    v5 = v4 - 1;
    if ( v5 )
    {
      if ( v5 != 1 )
        return ((gbRay *)&v8)->IsColOBB(actionId) != 0;
      ((gbGeomNode *)this->m_pol)->GetTotalOBBox(&actionId);
    }
    else
    {
      ((Actor *)this->m_pol)->PlayAction((int)&actionId);
    }
  }
  else
  {
    ((gbGeomNode *)this->m_pol)->GetOBBox(&actionId);
  }
  ((gbMatrix4 *)&actionId)->RightTranslate(this->m_position);
  return ((gbRay *)&v8)->IsColOBB(actionId) != 0;
}

// 0x0047DB40
bool Object3D::GetMouseRay@<al>(Object3D *this@<ecx>, int a3)
{
  void *v4; // esi
  unsigned int m_type; // eax
  unsigned int v6; // eax
  unsigned int v7; // eax
  struct gbOBBox actionId; // [esp+0xC] [ebp-0x7C] BYREF
  gbRay v10; // [esp+0x58] [ebp-0x30] BYREF

  if ( !this->m_visible || this->m_bRotDstDegree || (g_Input.KeyInfo[(_DWORD)a2].Data & 0xF) != 1 )
    return 0;
  ((GRPinput *)&g_Input)->GetCursorPos();
  v4 = this->SetupCamera();
  m_type = this->m_type;
  qmemcpy(&v10, v4, sizeof(v10));
  v6 = m_type - 1;
  if ( v6 )
  {
    v7 = v6 - 1;
    if ( v7 )
    {
      if ( v7 != 1 )
        return ((gbRay *)&v10)->IsColOBB(actionId) != 0;
      ((gbGeomNode *)this->m_pol)->GetTotalOBBox(&actionId);
    }
    else
    {
      ((Actor *)this->m_pol)->PlayAction((int)&actionId);
    }
  }
  else
  {
    ((gbGeomNode *)this->m_pol)->GetOBBox(&actionId);
  }
  ((gbMatrix4 *)&actionId)->RightTranslate(this->m_position);
  return ((gbRay *)&v10)->IsColOBB(actionId) != 0;
}

// 0x0047DC60
// attributes: thunk
bool Object3D::CheckMouseLPressed()
{
  return this->CheckMousePressed();
}

// 0x0047DC70
bool Object3D::CheckMousePressed()
{
  dword_DE4C94 = 1094713344;
  return 0;
}

// 0x0047DD60
int Object3D::fn_47DD60(unsigned __int8 *thisa)
{
  return *((unsigned __int8 *)this + 3757);
}

// 0x0047FD90
void * Object3D::LoadActorModel(int nParam)
{
  int v2; // edi
  CCBParabolaWindow *v4; // ebx
  void *result; // eax
  CCBParabolaWindow *v6; // ebx
  CCBParabolaWindow *v7; // ebx
  CCBParabolaWindow *v8; // ebx
  CCBParabolaWindow *v9; // ebx
  CCBParabolaWindow *v10; // ebx
  int v11; // [esp+0x14] [ebp+0x8]

  v2 = v11;
  if ( v11 >= 0 )
  {
    if ( v11 > 1 )
      v2 = 1;
  }
  else
  {
    v2 = 0;
  }
  if ( *((_DWORD *)this + nParam + 40681) != v2 )
  {
    switch ( nParam )
    {
      case 0:
        v4 = (CCBParabolaWindow *)((char *)this + 158596);
        if ( v2 )
        {
          sub_445FA0((char *)this + 158596);
          result = ((CCBParabolaWindow *)v4)->LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Gods", g_bDebugMode);
          goto LABEL_25;
        }
        sub_445FA0((char *)this + 158596);
        ((UIStatic *)((char *)this + 158596))->LoadResource("UI\\GameMainUI\\JusticeBook\\PassGods0.tga", g_bDebugMode);
        ((UIStatic *)((char *)this + 158596))->LoadTexture();
        *((_DWORD *)this + nParam + 40681) = 0;
        break;
      case 1:
        v6 = (CCBParabolaWindow *)((char *)this + 158844);
        if ( v2 )
        {
          sub_445FA0((char *)this + 158844);
          result = ((CCBParabolaWindow *)v6)->LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Immortal", g_bDebugMode);
          goto LABEL_25;
        }
        sub_445FA0((char *)this + 158844);
        ((UIStatic *)((char *)this + 158844))->LoadResource("UI\\GameMainUI\\JusticeBook\\PassImmortal0.tga", g_bDebugMode);
        ((UIStatic *)((char *)this + 158844))->LoadTexture();
        *((_DWORD *)this + nParam + 40681) = 0;
        break;
      case 2:
        v7 = (CCBParabolaWindow *)((char *)this + 159092);
        if ( v2 )
        {
          sub_445FA0((char *)this + 159092);
          result = ((CCBParabolaWindow *)v7)->LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Ghost", g_bDebugMode);
          goto LABEL_25;
        }
        sub_445FA0((char *)this + 159092);
        ((UIStatic *)((char *)this + 159092))->LoadResource("UI\\GameMainUI\\JusticeBook\\PassGhost0.tga", g_bDebugMode);
        ((UIStatic *)((char *)this + 159092))->LoadTexture();
        *((_DWORD *)this + nParam + 40681) = 0;
        break;
      case 3:
        v8 = (CCBParabolaWindow *)((char *)this + 159340);
        if ( v2 )
        {
          sub_445FA0((char *)this + 159340);
          result = ((CCBParabolaWindow *)v8)->LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Demon", g_bDebugMode);
          goto LABEL_25;
        }
        sub_445FA0((char *)this + 159340);
        ((UIStatic *)((char *)this + 159340))->LoadResource("UI\\GameMainUI\\JusticeBook\\PassDemon0.tga", g_bDebugMode);
        ((UIStatic *)((char *)this + 159340))->LoadTexture();
        *((_DWORD *)this + nParam + 40681) = 0;
        break;
      case 4:
        v9 = (CCBParabolaWindow *)((char *)this + 159588);
        if ( v2 )
        {
          sub_445FA0((char *)this + 159588);
          result = ((CCBParabolaWindow *)v9)->LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Human", g_bDebugMode);
          goto LABEL_25;
        }
        sub_445FA0((char *)this + 159588);
        ((UIStatic *)((char *)this + 159588))->LoadResource("UI\\GameMainUI\\JusticeBook\\PassHuman0.tga", g_bDebugMode);
        ((UIStatic *)((char *)this + 159588))->LoadTexture();
        *((_DWORD *)this + nParam + 40681) = 0;
        break;
      case 5:
        v10 = (CCBParabolaWindow *)((char *)this + 159836);
        if ( v2 )
        {
          sub_445FA0((char *)this + 159836);
          result = ((CCBParabolaWindow *)v10)->LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Magic", g_bDebugMode);
          goto LABEL_25;
        }
        sub_445FA0((char *)this + 159836);
        ((UIStatic *)((char *)this + 159836))->LoadResource("UI\\GameMainUI\\JusticeBook\\PassMagic0.tga", g_bDebugMode);
        ((UIStatic *)((char *)this + 159836))->LoadTexture();
        *((_DWORD *)this + nParam + 40681) = 0;
        break;
      default:
LABEL_25:
        *((_DWORD *)this + nParam + 40681) = v2;
        break;
    }
  }
  return result;
}

// 0x004B7F80
int Object3D::RenderTransformed(int nLOD)
{
  gbMatrixStack *v3; // esi
  double v4; // st7
  float v6; // [esp+0xC] [ebp-0x1C]
  float v7; // [esp+0xC] [ebp-0x1C]
  struct gbVec3D v8; // [esp+0x1C] [ebp-0xC] BYREF

  if ( *((_DWORD *)this + 264) )
  {
    v3 = gfxMgr->pMatrixStack[1];
    ((gbMatrixStack *)v3)->Push();
    v6 = sin(this->m_pitch * 3.0) * 8.0 + 25.0;
    ((gbMatrixStack *)v3)->Translate(0.0,   v6,   0.0);
    v4 = this->m_pitch * 3.0;
    v8.x = 0.0;
    v8.y = 1.0;
    v7 = v4;
    v8.z = 0.0;
    ((gbMatrixStack *)v3)->Rotate(v7, v8);
    (*(void ( **)(_DWORD, _DWORD))(**((_DWORD **)this + 264) + 16))(*((_DWORD *)this + 264), 0);
    ((gbMatrixStack *)v3)->Pop();
  }
  (*(void ( **)(Object3D *, _DWORD))(*(_DWORD *)&this->m_isLoadObj + 12))(this, 0);
  return 1;
}

// 0x00537060
gbVisNode * Object3D::GetVisNode()
{
  return (gbVisNode *)this->CheckMessage("over");
}

// 0x00537070
int Object3D::CheckMessage(const char *pszMsgName)
{
  unsigned int v3; // eax
  struct gbNodeMsgObj v5; // [esp+0x10] [ebp-0x10] BYREF

  if ( !((gbVisNode *)this->m_subType)->PopMessage(v5) )
    return 0;
  while ( 1 )
  {
    if ( v5.msgid == 1 )
    {
      v3 = gbCrc32Compute(pszMsgName);
      if ( v5.param[0] == v3 )
        break;
    }
    if ( !((gbVisNode *)this->m_subType)->PopMessage(v5) )
      return 0;
  }
  return 1;
}
