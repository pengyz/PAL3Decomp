#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Object3D.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/PalScript.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIItem.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UINote.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_40EE00(...);
int sub_43AFA0(...);
int sub_444F60(...);
int sub_537060(...);

// Unnamed globals (extern)
extern char aOver[];
extern char aSubgameHocksho_0[];
extern char aSubgameHocksho_1[];
extern char aUiFlexNote[];
extern unsigned char byte_DC733C;
extern int dword_BFD6D0;
extern int dword_BFD6D4;
extern int dword_BFDA60;
extern int dword_DE4C94;
extern void *off_56A66C;
extern void *off_56A9C0;
extern void *off_56B898;
extern void *off_56B8A4;
extern void *off_596420;
extern void *off_596424;
extern int unk_56B884;
extern int unk_ABE000;

// 0x0047CB70
Object3D::Object3D()
{
  this->LoadSubObject();
  *(_DWORD *)&this->m_visible = 0;
}

// 0x0047CB90
struct gbVFileSystem * Object3D::_Object3D(const char *a2, int a3)
{
  gbGeomNode *v4; // eax
  gbGeomNode *v5; // edi
  gbGeomNode *v6; // ecx
  _DWORD *v7; // eax
  gbGeomNode *v8; // eax
  char Destination[4]; // [esp+10h] [ebp-60h] BYREF
  OpenBaseFile v11; // [esp+14h] [ebp-5Ch] BYREF
  _BYTE v12[68]; // [esp+18h] [ebp-58h] BYREF
  float v13; // [esp+5Ch] [ebp-14h]
  int v14; // [esp+6Ch] [ebp-4h]

  this->LoadSubObject();
  *(_DWORD *)Destination = 0;
  strncpy(Destination, &a2[strlen(a2) - 3], 3u);
  ((OpenBaseFile *)&v11)->OpenBaseFile();
  v14 = 0;
  ((gbMatrix4 *)v12)->gbMatrix4();
  if ( !_strcmpi(Destination, off_596424) )
  {
    this->m_type = 1;
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = v4;
    LOBYTE(v14) = 1;
    if ( !v4 )
    {
      v6 = 0;
      goto LABEL_5;
    }
LABEL_3:
    v4->gbGeomNode();
    *(_DWORD *)v5->_pad_0000 = &off_56A66C;
    v6 = v5;
LABEL_5:
    LOBYTE(v14) = 0;
    this->m_pol = v6;
    v6->LoadFromFile(a2, 0, 0);
    ((gbGeomNode *)this->m_pol)->GetOBBox((struct gbOBBox *)v12);
    goto LABEL_13;
  }
  if ( !_strcmpi(Destination, off_596420) )
  {
    this->m_type = 3;
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = v4;
    LOBYTE(v14) = 2;
    if ( !v4 )
    {
      v6 = 0;
      goto LABEL_5;
    }
    goto LABEL_3;
  }
  this->m_type = 2;
  v7 = (_DWORD *)operator new(0x224u);
  LOBYTE(v14) = 3;
  if ( v7 )
    v8 = (gbGeomNode *)((Actor *)v7)->FastInit();
  else
    v8 = 0;
  LOBYTE(v14) = 0;
  this->m_pol = v8;
  ((Actor *)v8)->LoadModel();
  ((Actor *)this->m_pol)->CompareAction(a3, 0);
  (*(void (**)(_DWORD, _BYTE *, _DWORD))(**(_DWORD **)(*(_DWORD *)&this->m_pol->_pad_0000[16] + 88) + 28))(
    *(_DWORD *)(*(_DWORD *)&this->m_pol->_pad_0000[16] + 88),
    v12,
    *(_DWORD *)&this->m_pol->_pad_0000[16]);
LABEL_13:
  this->m_subObjHeight = v13;
  this->m_isLoadObj = 1;
  LOBYTE(this->m_dropz) = 1;
  this->m_rotDstMode = a3;
  v14 = -1;
  return ((OpenNULLFile *)&v11)->OpenNULLFile();
}

// 0x0047CD70
unsigned __int8 Object3D::LoadObject(const char *a2, int a3)
{
  unsigned __int8 result; // al
  Actor *m_actor; // ecx
  Actor *v6; // eax
  Actor *v7; // edi
  Actor *v8; // ecx
  Actor *v9; // eax
  Actor *v10; // edi
  Actor *v11; // ecx
  int Destination; // [esp+10h] [ebp-14h] BYREF
  OpenBaseFile v13; // [esp+14h] [ebp-10h] BYREF
  int v14; // [esp+20h] [ebp-4h]

  result = this->m_isLoadObj;
  LOBYTE(this->m_subType) = 0;
  BYTE1(this->m_subType) = 0;
  if ( result )
  {
    m_actor = (Actor *)this->m_actor;
    if ( m_actor )
    {
      (*(void (**)(Actor *, int))m_actor->m_actarray)(m_actor, 1);
      this->m_actor = 0;
    }
    Destination = 0;
    strncpy((char *)&Destination, &a2[strlen(a2) - 3], 3u);
    ((OpenBaseFile *)&v13)->OpenBaseFile();
    v14 = 0;
    if ( _strcmpi((const char *)&Destination, off_596424) )
    {
      if ( _strcmpi((const char *)&Destination, off_596420) )
      {
LABEL_15:
        v14 = -1;
        return (unsigned __int8)((OpenNULLFile *)&v13)->OpenNULLFile();
      }
      this->m_subObj = (gbGeomNode *)3;
      v9 = (Actor *)operator new(0x118u);
      v10 = v9;
      LOBYTE(v14) = 2;
      if ( v9 )
      {
        v9->gbGeomNode();
        v10->m_actarray = &off_56A66C;
        v11 = v10;
      }
      else
      {
        v11 = 0;
      }
      LOBYTE(v14) = 0;
      this->m_actor = v11;
      ((gbGeomNode *)v11)->LoadFromFile(a2, 0, 0);
      ((gbVisNode *)this->m_actor)->SetTimeScale(1.0);
    }
    else
    {
      this->m_subObj = (gbGeomNode *)1;
      v6 = (Actor *)operator new(0x118u);
      v7 = v6;
      LOBYTE(v14) = 1;
      if ( v6 )
      {
        v6->gbGeomNode();
        v7->m_actarray = &off_56A66C;
        v8 = v7;
      }
      else
      {
        v8 = 0;
      }
      LOBYTE(v14) = 0;
      this->m_actor = v8;
      ((gbGeomNode *)v8)->LoadFromFile(a2, 0, 0);
    }
    LOBYTE(this->m_subType) = 1;
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
      (**(void (***)(gbGeomNode *, int))m_pol->_pad_0000)(m_pol, 1);
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
  v2 = (gbGeomNode *)this->m_pol;
  if ( v2 )
  {
    sub_40EE00((int)this->m_pol->_pad_0000);
    operator delete(v2);
    this->m_pol = 0;
    this->m_isLoadObj = 0;
    return;
  }
LABEL_9:
  this->m_isLoadObj = 0;
}

// 0x0047CF40
char Object3D::Destroy()
{
  unsigned int v2; // eax
  struct gbNodeMsgObj v4; // [esp+Ch] [ebp-10h] BYREF

  if ( this->m_type != 3 || !((gbVisNode *)this->m_pol)->PopMessage(&v4) )
    return 0;
  while ( 1 )
  {
    if ( v4.msgid == 1 )
    {
      v2 = gbCrc32Compute(aOver);
      if ( v4.param[0] == v2 )
        break;
    }
    if ( !((gbVisNode *)this->m_pol)->PopMessage(&v4) )
      return 0;
  }
  return 1;
}

// 0x0047CFB0
long double Object3D::IsOverCVD(float a1, float a2, float a3, float a4, float a5, float a6)
{
  return acos((a6 * a3 + a5 * a2 + a4 * a1) / (sqrt(a6 * a6 + a5 * a5 + a4 * a4) * sqrt(a3 * a3 + a2 * a2 + a1 * a1)))
       * 57.295776;
}

// 0x0047D030
void Object3D::VecAngle(float a2, float a3, float a4)
{
  float v4; // edx
  float v6; // ecx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st6
  gbVec3D v11; // [esp+10h] [ebp-18h] BYREF
  float v12; // [esp+20h] [ebp-8h]
  float v13; // [esp+24h] [ebp-4h]

  v4 = a4;
  v6 = a3;
  this->m_height = a2;
  this->m_position.x = v6;
  this->m_position.y = v4;
  a2 = this->m_position.z - this->m_height;
  v7 = this->RelativePos.x - this->m_position.x;
  v11.x = a2;
  a3 = v7;
  v8 = this->RelativePos.y - this->m_position.y;
  v11.y = a3;
  a4 = v8;
  v11.z = a4;
  this->m_roll = ((gbVec3D *)&v11)->Length();
  v9 = this->m_height - this->m_position.z;
  v12 = this->m_position.x - this->RelativePos.x;
  v10 = this->m_position.y - this->RelativePos.y;
  a3 = v12;
  v13 = v10;
  a2 = v9;
  a4 = v13;
  ((gbVec3D *)&a2)->Normalize();
  this->m_forward.z = a2->IsOverCVD(a3, a4, 0.0, 0.0, 1.0);
}

// 0x0047D130
void Object3D::SetObjectPosition(float a2, float a3, float a4)
{
  float v4; // edx
  float v6; // ecx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st6
  gbVec3D v11; // [esp+10h] [ebp-18h] BYREF
  float v12; // [esp+20h] [ebp-8h]
  float v13; // [esp+24h] [ebp-4h]

  v4 = a4;
  v6 = a3;
  this->m_position.z = a2;
  this->RelativePos.x = v6;
  this->RelativePos.y = v4;
  a2 = this->m_position.z - this->m_height;
  v7 = this->RelativePos.x - this->m_position.x;
  v11.x = a2;
  a3 = v7;
  v8 = this->RelativePos.y - this->m_position.y;
  v11.y = a3;
  a4 = v8;
  v11.z = a4;
  this->m_roll = ((gbVec3D *)&v11)->Length();
  v9 = this->m_height - this->m_position.z;
  v12 = this->m_position.x - this->RelativePos.x;
  v10 = this->m_position.y - this->RelativePos.y;
  a3 = v12;
  v13 = v10;
  a2 = v9;
  a4 = v13;
  ((gbVec3D *)&a2)->Normalize();
  this->m_forward.z = a2->IsOverCVD(a3, a4, 0.0, 0.0, 1.0);
}

// 0x0047D230
long double Object3D::SetCentrePos()
{
  double v2; // st7
  double v3; // st6
  double v4; // st6
  gbVec3D v6; // [esp+4h] [ebp-24h] BYREF
  float v7; // [esp+10h] [ebp-18h]
  float v8; // [esp+14h] [ebp-14h]
  float v9; // [esp+18h] [ebp-10h]
  float v10; // [esp+20h] [ebp-8h]
  float v11; // [esp+24h] [ebp-4h]

  v7 = 0.0;
  v8 = 0.0;
  v2 = this->m_height - this->m_position.z;
  v3 = this->m_position.x - this->RelativePos.x;
  v9 = 1.0;
  v10 = v3;
  v4 = this->m_position.y - this->RelativePos.y;
  v6.y = v10;
  v11 = v4;
  v6.x = v2;
  v6.z = v11;
  ((gbVec3D *)&v6)->Normalize();
  if ( this->m_height >= (double)this->m_position.z )
    return ((Object3D *)v6.x)->IsOverCVD(v6.y, v6.z, v7, v8, v9);
  else
    return 360.0 - ((Object3D *)v6.x)->IsOverCVD(v6.y, v6.z, v7, v8, v9);
}

// 0x0047D320
void Object3D::GetScreenDegree()
{
  long double v2; // st7
  long double v3; // st6
  double m_roll; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st5
  float v9; // eax
  float v10; // ecx
  double v11; // st7
  double v12; // st6
  float v13; // [esp+4h] [ebp-28h]
  gbVec3D v14; // [esp+8h] [ebp-24h] BYREF
  float v15; // [esp+14h] [ebp-18h]
  float v16; // [esp+18h] [ebp-14h]
  float v17; // [esp+1Ch] [ebp-10h]
  float v18; // [esp+24h] [ebp-8h]
  float v19; // [esp+28h] [ebp-4h]

  v2 = *(float *)&this->m_pCamera * 0.017453292;
  v3 = this->m_yaw * 0.017453292;
  v13 = cos(v3);
  this->m_dist = sin(v2) * v13;
  this->m_forward.x = sin(v3);
  this->m_forward.y = -(cos(v2) * v13);
  m_roll = this->m_roll;
  v15 = m_roll * this->m_dist;
  v16 = m_roll * this->m_forward.x;
  v5 = m_roll * this->m_forward.y;
  v6 = this->m_position.z - v15;
  v7 = this->RelativePos.x - v16;
  v15 = 0.0;
  v16 = v7;
  v8 = this->RelativePos.y - v5;
  v9 = v16;
  v16 = 0.0;
  this->m_position.x = v9;
  v17 = v8;
  v10 = v17;
  v17 = 1.0;
  this->m_height = v6;
  this->m_position.y = v10;
  v11 = this->m_height - this->m_position.z;
  v18 = this->m_position.x - this->RelativePos.x;
  v12 = this->m_position.y - this->RelativePos.y;
  v14.y = v18;
  v19 = v12;
  v14.x = v11;
  v14.z = v19;
  ((gbVec3D *)&v14)->Normalize();
  this->m_forward.z = ((Object3D *)v14.x)->IsOverCVD(v14.y, v14.z, v15, v16, v17);
}

// 0x0047D440
void Object3D::GetScreenDegree(int a1@<ecx>, int a2, int a3, int a4, gbMatrixStack *a5)
{
  struct gbCamera **v6; // eax
  float v7; // edi
  gbMatrixStack *v8; // edi
  double v10; // st7
  unsigned __int8 v11; // c0
  unsigned __int8 v12; // c3
  float v13; // [esp+38h] [ebp-28h]
  float v14; // [esp+38h] [ebp-28h]
  float v15; // [esp+40h] [ebp-20h]
  gbSceneGraph *v16; // [esp+50h] [ebp-10h]
  struct gbVec3D v17; // [esp+54h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+60h] [ebp+0h] BYREF
  float v19; // [esp+70h] [ebp+10h]

  v6 = *(struct gbCamera ***)(a1 + 84);
  if ( !v6 || !*(_BYTE *)a1 || !*(_BYTE *)(a1 + 80) )
    return;
  v7 = dword_BFDA60->InvViewMatrix.m[1][3];
  v16 = (gbSceneGraph *)LODWORD(v7);
  ((gbSceneGraph *)LODWORD(v7))->Begin(*v6);
  *(_BYTE *)(LODWORD(v7) + 19244) = 0;
  v8 = a5;
  if ( !a5 )
    v8 = (gbMatrixStack *)dword_BFDA60->pMatrixStack[1];
  ((gbCamera *)**(gbCamera ***)(a1 + 84))->SetAsCurrent(3);
  v8->Push();
  v8->Translate((struct gbVec3D *)(a1 + 32));
  v8->Rotate(*(float *)(a1 + 60), (struct gbVec3D *)&retaddr);
  retaddr = 0;
  v8->Rotate(*(float *)(a1 + 56), (struct gbVec3D *)&retaddr);
  if ( !*(_DWORD *)(a1 + 144) && *(_BYTE *)(a1 + 120) )
  {
    v10 = 360.0 - *(float *)(a1 + 116);
    if ( !(v11 | v12) )
      v10 = -v10;
    v19 = v10;
    retaddr = 0;
    v8->Rotate(v19, (struct gbVec3D *)&retaddr);
  }
  v8->Rotate(*(float *)(a1 + 64), (struct gbVec3D *)&retaddr);
  v15 = *(float *)(a1 + 68);
  v17.z = 1.0;
  retaddr = 0;
  v8->Rotate(v15, (struct gbVec3D *)&v17.z);
  v13 = *(float *)(a1 + 72);
  v17.x = 0.0;
  v17.y = 1.0;
  v17.z = 0.0;
  v8->Rotate(v13, &v17);
  v14 = *(float *)(a1 + 76);
  v17.x = 0.0;
  v17.y = 0.0;
  v17.z = 1.0;
  v8->Rotate(v14, &v17);
  switch ( *(_DWORD *)(a1 + 4) )
  {
    case 1:
      goto LABEL_16;
    case 2:
      ((Actor *)*(Actor **)(a1 + 8))->DispatchAction(0);
      break;
    case 3:
LABEL_16:
      (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)(a1 + 8) + 16))(*(_DWORD *)(a1 + 8), 0);
      break;
  }
  v8->Pop();
  if ( *(_BYTE *)(a1 + 21) && *(_BYTE *)(a1 + 20) )
  {
    v8->Push();
    v17.x = *(float *)(a1 + 32);
    v17.y = *(float *)(a1 + 36) + *(float *)(a1 + 24);
    v17.z = *(float *)(a1 + 40);
    v8->Translate(&v17);
    if ( *(_DWORD *)(a1 + 16) == 1 || *(_DWORD *)(a1 + 16) == 3 )
      (*(void (**)(_DWORD, _DWORD))(**(_DWORD **)(a1 + 12) + 16))(*(_DWORD *)(a1 + 12), 0);
    v8->Pop();
  }
  v16->End();
}

// 0x0047D690
void Object3D::CaculateRelative(float a2)
{
  unsigned int v3; // eax
  int m_rotDstDir; // eax
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
  double v21; // st7
  unsigned __int8 v22; // c0
  unsigned __int8 v23; // c3
  double v24; // st7
  struct gbNodeMsgObj v25; // [esp+Ch] [ebp-10h] BYREF

  if ( !this->m_isLoadObj )
    return;
  if ( LOBYTE(this->m_dropz) )
  {
    switch ( this->m_type )
    {
      case 1u:
LABEL_10:
        (*(void (**)(gbGeomNode *))(*(_DWORD *)this->m_pol + 20))(this->m_pol);
        break;
      case 2u:
        if ( sub_537060((gbVisNode **)this->m_pol) )
          ((Actor *)this->m_pol)->CompareAction(0, 0);
        ((Actor *)this->m_pol)->QueryState();
        break;
      case 3u:
        goto LABEL_10;
    }
  }
  if ( BYTE1(this->m_subType) && LOBYTE(this->m_subType) )
  {
    if ( this->m_subObj == (gbGeomNode *)1 )
    {
      (*((void (**)(Actor *))this->m_actor->m_actarray + 5))(this->m_actor);
    }
    else if ( this->m_subObj == (gbGeomNode *)3 )
    {
      (*((void (**)(Actor *))this->m_actor->m_actarray + 5))(this->m_actor);
      while ( ((gbVisNode *)this->m_actor)->PopMessage(&v25) )
      {
        if ( v25.msgid == 1 )
        {
          v3 = gbCrc32Compute(aOver);
          if ( v25.param[0] == v3 )
          {
            (*((void (**)(Actor *, _DWORD))this->m_actor->m_actarray + 6))(this->m_actor, 0);
            ((gbVisNode *)this->m_actor)->SetTimeScale(1.0);
          }
        }
      }
    }
  }
  if ( BYTE1(this->m_degreeToScreen) )
  {
    m_rotDstDir = this->m_rotDstDir;
    if ( m_rotDstDir )
    {
      if ( m_rotDstDir == 1 )
      {
        if ( this->m_rotRelative >= (double)this->m_rotDegree )
        {
          if ( this->m_rotRelative <= (double)this->m_rotDegree )
          {
            if ( this->m_rotRelative > 360.0 )
              this->m_rotRelative = this->m_rotRelative - 360.0;
            if ( this->m_rotRelative < 0.0 )
              this->m_rotRelative = this->m_rotRelative + 360.0;
            BYTE1(this->m_degreeToScreen) = 0;
          }
          else
          {
            v11 = a2 * 50.0 * this->m_rotDstDegree;
            v12 = this->m_rotRelative - v11;
            this->m_rotRelative = v12;
            if ( v12 <= this->m_rotDegree )
              this->m_rotRelative = this->m_rotDegree;
            v13 = this->RelativePos.z - v11;
            this->RelativePos.z = v13;
            if ( v15 )
              this->RelativePos.z = v13 + 360.0;
          }
        }
        else
        {
          v5 = a2 * 50.0 * this->m_rotDstDegree;
          v6 = v5 + this->m_rotRelative;
          this->m_rotRelative = v6;
          if ( v6 >= this->m_rotDegree )
            this->m_rotRelative = this->m_rotDegree;
          v7 = v5 + this->RelativePos.z;
          this->RelativePos.z = v7;
          if ( !(v9 | v10) )
            this->RelativePos.z = v7 - 360.0;
        }
      }
      return;
    }
    if ( this->m_rotRelative >= (double)this->m_rotDegree )
    {
      if ( this->m_rotRelative <= (double)this->m_rotDegree )
      {
        BYTE1(this->m_degreeToScreen) = 0;
      }
      else
      {
        v18 = a2 * 50.0 * this->m_rotDstDegree;
        v19 = this->m_rotRelative - v18;
        this->m_rotRelative = v19;
        *(float *)&this->m_isActionRelativeRot = *(float *)&this->m_isActionRelativeRot - v18;
        if ( v19 <= this->m_rotDegree )
          this->m_rotRelative = this->m_rotDegree;
      }
    }
    else
    {
      v16 = a2 * 50.0 * this->m_rotDstDegree;
      v17 = v16 + this->m_rotRelative;
      this->m_rotRelative = v17;
      *(float *)&this->m_isActionRelativeRot = v16 + *(float *)&this->m_isActionRelativeRot;
      if ( v17 >= this->m_rotDegree )
        this->m_rotRelative = this->m_rotDegree;
    }
    v21 = *(float *)&this->m_isActionRelativeRot;
    if ( v22 | v23 )
    {
      if ( v21 >= 0.0 )
      {
LABEL_52:
        this->m_pCamera = *(ObjectCamera **)&this->m_isActionRelativeRot;
        this->GetScreenDegree();
        return;
      }
      v24 = *(float *)&this->m_isActionRelativeRot + 360.0;
    }
    else
    {
      v24 = v21 - 360.0;
    }
    *(float *)&this->m_isActionRelativeRot = v24;
    goto LABEL_52;
  }
}

// 0x0047D9D0
void * Object3D::SetupCamera()
{
  float v2; // [esp+0h] [ebp-2Ch]
  float v3; // [esp+4h] [ebp-28h]
  struct gbRay v4; // [esp+14h] [ebp-18h] BYREF
  struct gbRay *v5; // [esp+30h] [ebp+4h]
  int *v6; // [esp+34h] [ebp+8h]

  memset(&v4, 0, sizeof(v4));
  v3 = 1.0 - ((double)v6[1] + (double)v6[1]) / (double)dword_BFD6D4;
  v2 = ((double)*v6 + (double)*v6) / (double)dword_BFD6D0 - 1.0;
  ((gbCamera *)**(gbCamera ***)&this->m_visible)->GetRayToScreen(v2, v3, &v4);
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
  struct tagPOINT Point; // [esp+4h] [ebp-84h] BYREF
  _BYTE actionId[124]; // [esp+Ch] [ebp-7Ch] BYREF

  if ( !LOBYTE(this->m_dropz) || BYTE1(this->m_degreeToScreen) || g_Input.KeyInfo[0].PressTime != 1 )
    return 0;
  ((gbMatrix4 *)actionId)->gbMatrix4();
  ((GRPinput *)&Point)->GetCursorPos();
  v2 = (void *)this->SetupCamera();
  m_type = this->m_type;
  qmemcpy(&actionId[76], v2, 0x18u);
  v4 = m_type - 1;
  if ( v4 )
  {
    v5 = v4 - 1;
    if ( v5 )
    {
      if ( v5 != 1 )
        return ((gbRay *)&actionId[76])->IsColOBB((struct gbOBBox *)actionId) != 0;
      ((gbGeomNode *)this->m_pol)->GetTotalOBBox((struct gbOBBox *)actionId);
    }
    else
    {
      ((Actor *)this->m_pol)->PlayAction((int)actionId);
    }
  }
  else
  {
    ((gbGeomNode *)this->m_pol)->GetOBBox((struct gbOBBox *)actionId);
  }
  ((gbMatrix4 *)actionId)->RightTranslate((struct gbVec3D *)&this->m_height);
  return ((gbRay *)&actionId[76])->IsColOBB((struct gbOBBox *)actionId) != 0;
}

// 0x0047DB40
bool Object3D::GetMouseRay(int a2)
{
  void *v3; // esi
  unsigned int m_type; // eax
  unsigned int v5; // eax
  unsigned int v6; // eax
  struct tagPOINT Point; // [esp+4h] [ebp-84h] BYREF
  _BYTE actionId[124]; // [esp+Ch] [ebp-7Ch] BYREF

  if ( !LOBYTE(this->m_dropz) || BYTE1(this->m_degreeToScreen) || (g_Input.KeyInfo[a2].Data & 0xF) != 1 )
    return 0;
  ((gbMatrix4 *)actionId)->gbMatrix4();
  ((GRPinput *)&Point)->GetCursorPos();
  v3 = (void *)this->SetupCamera();
  m_type = this->m_type;
  qmemcpy(&actionId[76], v3, 0x18u);
  v5 = m_type - 1;
  if ( v5 )
  {
    v6 = v5 - 1;
    if ( v6 )
    {
      if ( v6 != 1 )
        return ((gbRay *)&actionId[76])->IsColOBB((struct gbOBBox *)actionId) != 0;
      ((gbGeomNode *)this->m_pol)->GetTotalOBBox((struct gbOBBox *)actionId);
    }
    else
    {
      ((Actor *)this->m_pol)->PlayAction((int)actionId);
    }
  }
  else
  {
    ((gbGeomNode *)this->m_pol)->GetOBBox((struct gbOBBox *)actionId);
  }
  ((gbMatrix4 *)actionId)->RightTranslate((struct gbVec3D *)&this->m_height);
  return ((gbRay *)&actionId[76])->IsColOBB((struct gbOBBox *)actionId) != 0;
}

// 0x0047DC60
// attributes: thunk
int Object3D::CheckMouseLPressed()
{
  return Object3D::CheckMousePressed();
}

// 0x0047DC70
int Object3D::CheckMousePressed()
{
  dword_DE4C94 = 1094713344;
  return 1094713344;
}

// 0x0047DCA0
int Object3D::Create()
{
  ((UIListBox *)this)->UIListBox();
  LODWORD(this->m_dropx) = &off_56A9C0;
  this->m_dropy = 0.0;
  LODWORD(this->m_pitch) = 800;
  LODWORD(this->m_roll) = 600;
  *((_DWORD *)this + 96) = 0;
  *((_BYTE *)this + 388) = 0;
  sub_444F60((UIWnd *)((char *)this + 392));
  ((UIFrameWnd *)((char *)this + 584))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 736,
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIItem *)(UIItem *)this + 2456)->Refresh();
  *(_DWORD *)&this->m_isLoadObj = &off_56B8A4;
  LODWORD(this->m_dropx) = &off_56B898;
  return (int)this;
}

// 0x0047DE40
void Object3D::Init()
{
  float m_pitch; // eax
  float m_roll; // ecx
  int v4; // eax
  char *v5; // ebx
  _DWORD *v6; // ebp
  PalScript **v7; // esi
  char id; // [esp+1Ch] [ebp-24h] BYREF
  __int16 id_1; // [esp+1Dh] [ebp-23h]
  char id_3; // [esp+1Fh] [ebp-21h]
  _DWORD v11[4]; // [esp+20h] [ebp-20h] BYREF
  int a3[4]; // [esp+30h] [ebp-10h] BYREF

  m_pitch = this->m_pitch;
  m_roll = this->m_roll;
  *(float *)&this->m_pCamera = m_pitch;
  this->m_yaw = m_roll;
  *(_DWORD *)&this->m_visible = 0;
  this->m_dropz = 0.0;
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, (int)this->m_pCamera, LODWORD(this->m_yaw), 0);
  *((_DWORD *)this + 93) = 170;
  *((_DWORD *)this + 92) = 310;
  *((_DWORD *)this + 94) = 468;
  *((_DWORD *)this + 95) = 430;
  ((UINote *)((char *)this + 392))->Create(-1430519792, (int)this + 368, (int)this, aUiFlexNote);
  (**((void (***)(char *, _DWORD))this + 98))((char *)this + 392, 0);
  v4 = *((_DWORD *)this + 93) + 10;
  v11[0] = *((_DWORD *)this + 92) + 10;
  v11[1] = v4;
  v11[2] = v11[0] + 136;
  v11[3] = v4 + 128;
  (*(void (**)(char *, int, _DWORD *, Object3D *))(*((_DWORD *)this + 146) + 16))(
    (char *)this + 584,
    -1430519792,
    v11,
    this);
  ((UIWnd *)((char *)this + 584))->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    id_1 = -5;
    id = 31;
  }
  else
  {
    id_1 = 8187;
    id = -1;
  }
  id_3 = -1;
  ((UIWnd *)((char *)this + 584))->GetChild((int)&id);
  (**((void (***)(char *, _DWORD))this + 146))((char *)this + 584, 0);
  v5 = byte_DC733C;
  v6 = (_DWORD *)&unk_56B884;
  v7 = (PalScript **)((char *)this + 736);
  do
  {
    ((void (*)(PalScript **, _DWORD, _DWORD *, Object3D *, char *, _DWORD, int))(*v7)->m_CamObj.m_nSize)(
      v7,
      *v6,
      v11,
      this,
      aSubgameHocksho_0,
      0,
      1);
    v7->OpenScript(aSubgameHocksho_1, 1);
    sub_43AFA0((char *)v7, v5);
    v7[27] = (PalScript *)3;
    v7[26] = (PalScript *)1;
    v7[52] = (PalScript *)1;
    (*(void (**)(PalScript **, _DWORD))&(*v7)->m_bLoadSceneScript)(v7, 0);
    ++v6;
    v5 += 256;
    v7 += 86;
  }
  while ( (int)v6 < (int)&off_56B898 );
  a3[1] = 200;
  a3[0] = 300;
  a3[2] = 500;
  a3[3] = 300;
  ((UIItem *)(UIItem *)this + 2456)->Create((int)&unk_ABE000, (int)a3);
  ((UIItem *)(UIItem *)this + 2456)->SetData(18);
  *((_BYTE *)this + 3829) = 0;
  *((_BYTE *)this + 3830) = 0;
}
