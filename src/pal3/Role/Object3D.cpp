#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Object3D.h"

// 0x0047CB70
void sub_47CB70(_DWORD *this)
{
  Object3D::LoadSubObject();
  *(this + 21) = 0;
}

// 0x0047CB90
struct gbVFileSystem * Object3D::_Object3D(const char *a2, int a3)
{
  gbGeomNode *v4; // eax
  gbGeomNode *v5; // edi
  gbGeomNode *v6; // ecx
  int v7; // eax
  gbGeomNode *v8; // eax
  char Destination[4]; // [esp+10h] [ebp-60h] BYREF
  struct gbVFileSystem *v11; // [esp+14h] [ebp-5Ch] BYREF
  _BYTE v12[88]; // [esp+18h] [ebp-58h] BYREF

  this->LoadSubObject();
  *(_DWORD *)Destination = 0;
  strncpy(Destination, &a2[strlen(a2) - 3], 3u);
  OpenBaseFile::OpenBaseFile(&v11);
  *(_DWORD *)&v12[84] = 0;
  (gbMatrix4 *->gbMatrix4()v12);
  if ( !_strcmpi(Destination, off_596424) )
  {
    this->m_type = 1;
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = v4;
    v12[84] = 1;
    if ( !v4 )
    {
      v6 = 0;
      goto LABEL_5;
    }
LABEL_3:
    v4->gbGeomNode();
    v5->next = (gbChain1DNode *)&off_56A66C;
    v6 = v5;
LABEL_5:
    v12[84] = 0;
    this->m_pol = v6;
    v6->LoadFromFile(a2, 0, 0);
    this->m_pol->GetOBBox((struct gbOBBox *)v12);
    goto LABEL_13;
  }
  if ( !_strcmpi(Destination, off_596420) )
  {
    this->m_type = 3;
    v4 = (gbGeomNode *)operator new(0x118u);
    v5 = v4;
    v12[84] = 2;
    if ( !v4 )
    {
      v6 = 0;
      goto LABEL_5;
    }
    goto LABEL_3;
  }
  this->m_type = 2;
  v7 = operator new(0x224u);
  v12[84] = 3;
  if ( v7 )
    v8 = (gbGeomNode *)v7->FastInit();
  else
    v8 = 0;
  v12[84] = 0;
  this->m_pol = v8;
  (Actor *->LoadModel()v8);
  (Actor *->CompareAction()this->m_pol, a3, 0);
  (*(void (__thiscall **)(_DWORD, _BYTE *, int))(**(_DWORD **)(this->m_pol->Children.m_numNode + 88) + 28))(
    *(_DWORD *)(this->m_pol->Children.m_numNode + 88),
    v12,
    this->m_pol->Children.m_numNode);
LABEL_13:
  this->m_showSubObj = *(float *)&v12[68];
  this->m_isLoadObj = 1;
  LOBYTE(this->m_dropy) = 1;
  this->m_rotDstSpeed = a3;
  *(_DWORD *)&v12[84] = -1;
  return OpenNULLFile::OpenNULLFile(&v11);
}

// 0x0047CD70
unsigned __int8 Object3D::LoadObject(const char *a2, int a3)
{
  unsigned __int8 result; // al
  void (__thiscall ***v5)(_DWORD, int); // ecx
  gbGeomNode *v6; // eax
  gbGeomNode *v7; // edi
  gbGeomNode *v8; // ecx
  gbGeomNode *v9; // eax
  gbGeomNode *v10; // edi
  gbGeomNode *v11; // ecx
  int Destination; // [esp+10h] [ebp-14h] BYREF
  struct gbVFileSystem *v13; // [esp+14h] [ebp-10h] BYREF
  int v14; // [esp+20h] [ebp-4h]

  result = this->m_isLoadObj[0];
  this->m_isLoadObj[20] = 0;
  this->m_isLoadObj[21] = 0;
  if ( result )
  {
    v5 = *(void (__thiscall ****)(_DWORD, int))&this->m_isLoadObj[12];
    if ( v5 )
    {
      (**v5)(v5, 1);
      *(_DWORD *)&this->m_isLoadObj[12] = 0;
    }
    Destination = 0;
    strncpy((char *)&Destination, &a2[strlen(a2) - 3], 3u);
    OpenBaseFile::OpenBaseFile(&v13);
    v14 = 0;
    if ( _strcmpi((const char *)&Destination, off_596424) )
    {
      if ( _strcmpi((const char *)&Destination, off_596420) )
      {
LABEL_15:
        v14 = -1;
        return (unsigned __int8)OpenNULLFile::OpenNULLFile(&v13);
      }
      *(_DWORD *)&this->m_isLoadObj[16] = 3;
      v9 = (gbGeomNode *)operator new(0x118u);
      v10 = v9;
      LOBYTE(v14) = 2;
      if ( v9 )
      {
        v9->gbGeomNode();
        *(_DWORD *)v10->gbVisNode = &off_56A66C;
        v11 = v10;
      }
      else
      {
        v11 = 0;
      }
      LOBYTE(v14) = 0;
      *(_DWORD *)&this->m_isLoadObj[12] = v11;
      v11->LoadFromFile(a2, 0, 0);
      gbVisNode::SetTimeScale(*(gbVisNode **)&this->m_isLoadObj[12], 1.0);
    }
    else
    {
      *(_DWORD *)&this->m_isLoadObj[16] = 1;
      v6 = (gbGeomNode *)operator new(0x118u);
      v7 = v6;
      LOBYTE(v14) = 1;
      if ( v6 )
      {
        v6->gbGeomNode();
        *(_DWORD *)v7->gbVisNode = &off_56A66C;
        v8 = v7;
      }
      else
      {
        v8 = 0;
      }
      LOBYTE(v14) = 0;
      *(_DWORD *)&this->m_isLoadObj[12] = v8;
      v8->LoadFromFile(a2, 0, 0);
    }
    this->m_isLoadObj[20] = 1;
    goto LABEL_15;
  }
  return result;
}

// 0x0047CEE0
void sub_47CEE0(_DWORD *this)
{
  void *v2; // edi
  void (__thiscall ***v3)(_DWORD, int); // ecx

  if ( *(this + 1) == 1 )
  {
LABEL_7:
    v3 = (void (__thiscall ***)(_DWORD, int))*(this + 2);
    if ( v3 )
    {
      (**v3)(v3, 1);
      *(this + 2) = 0;
    }
    goto LABEL_9;
  }
  if ( *(this + 1) != 2 )
  {
    if ( *(this + 1) != 3 )
    {
      *(_BYTE *)this = 0;
      return;
    }
    goto LABEL_7;
  }
  v2 = (void *)*(this + 2);
  if ( v2 )
  {
    sub_40EE00(*(this + 2));
    operator delete(v2);
    *(this + 2) = 0;
    *(_BYTE *)this = 0;
    return;
  }
LABEL_9:
  *(_BYTE *)this = 0;
}

// 0x0047CF40
char sub_47CF40(int this)
{
  unsigned int v2; // eax
  _DWORD v4[4]; // [esp+Ch] [ebp-10h] BYREF

  if ( *(_DWORD *)(this + 4) != 3 || !gbVisNode::PopMessage(*(gbVisNode **)(this + 8), (struct gbNodeMsgObj *)v4) )
    return 0;
  while ( 1 )
  {
    if ( v4[0] == 1 )
    {
      v2 = gbCrc32Compute(aOver);
      if ( v4[1] == v2 )
        break;
    }
    if ( !gbVisNode::PopMessage(*(gbVisNode **)(this + 8), (struct gbNodeMsgObj *)v4) )
      return 0;
  }
  return 1;
}

// 0x0047CFB0
long double sub_47CFB0(float a1, float a2, float a3, float a4, float a5, float a6)
{
  return acos((a6 * a3 + a5 * a2 + a4 * a1) / (sqrt(a6 * a6 + a5 * a5 + a4 * a4) * sqrt(a3 * a3 + a2 * a2 + a1 * a1)))
       * 57.295776;
}

// 0x0047D030
void sub_47D030(float *this, float a2, float a3, float a4)
{
  float v4; // edx
  float v6; // ecx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st6
  _DWORD v11[4]; // [esp+10h] [ebp-18h] BYREF
  float v12; // [esp+20h] [ebp-8h]
  float v13; // [esp+24h] [ebp-4h]

  v4 = a4;
  v6 = a3;
  *(this + 8) = a2;
  *(this + 9) = v6;
  *(this + 10) = v4;
  a2 = *(this + 11) - *(this + 8);
  v7 = *(this + 12) - *(this + 9);
  *(float *)v11 = a2;
  a3 = v7;
  v8 = *(this + 13) - *(this + 10);
  *(float *)&v11[1] = a3;
  a4 = v8;
  *(float *)&v11[2] = a4;
  *(this + 25) = (gbVec3D *->Length()v11);
  v9 = *(this + 8) - *(this + 11);
  v12 = *(this + 9) - *(this + 12);
  v10 = *(this + 10) - *(this + 13);
  a3 = v12;
  v13 = v10;
  a2 = v9;
  a4 = v13;
  (gbVec3D *->Normalize()&a2);
  *(this + 29) = a2->IsOverCVD(a3, a4, 0.0, 0.0, 1.0);
}

// 0x0047D130
void sub_47D130(float *this, float a2, float a3, float a4)
{
  float v4; // edx
  float v6; // ecx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st6
  _DWORD v11[4]; // [esp+10h] [ebp-18h] BYREF
  float v12; // [esp+20h] [ebp-8h]
  float v13; // [esp+24h] [ebp-4h]

  v4 = a4;
  v6 = a3;
  *(this + 11) = a2;
  *(this + 12) = v6;
  *(this + 13) = v4;
  a2 = *(this + 11) - *(this + 8);
  v7 = *(this + 12) - *(this + 9);
  *(float *)v11 = a2;
  a3 = v7;
  v8 = *(this + 13) - *(this + 10);
  *(float *)&v11[1] = a3;
  a4 = v8;
  *(float *)&v11[2] = a4;
  *(this + 25) = (gbVec3D *->Length()v11);
  v9 = *(this + 8) - *(this + 11);
  v12 = *(this + 9) - *(this + 12);
  v10 = *(this + 10) - *(this + 13);
  a3 = v12;
  v13 = v10;
  a2 = v9;
  a4 = v13;
  (gbVec3D *->Normalize()&a2);
  *(this + 29) = a2->IsOverCVD(a3, a4, 0.0, 0.0, 1.0);
}

// 0x0047D230
long double sub_47D230(float *this)
{
  double v2; // st7
  double v3; // st6
  double v4; // st6
  float v6; // [esp+4h] [ebp-24h] BYREF
  float v7; // [esp+8h] [ebp-20h]
  float v8; // [esp+Ch] [ebp-1Ch]
  float v9; // [esp+10h] [ebp-18h]
  float v10; // [esp+14h] [ebp-14h]
  float v11; // [esp+18h] [ebp-10h]
  float v12; // [esp+20h] [ebp-8h]
  float v13; // [esp+24h] [ebp-4h]

  v9 = 0.0;
  v10 = 0.0;
  v2 = *(this + 8) - *(this + 11);
  v3 = *(this + 9) - *(this + 12);
  v11 = 1.0;
  v12 = v3;
  v4 = *(this + 10) - *(this + 13);
  v7 = v12;
  v13 = v4;
  v6 = v2;
  v8 = v13;
  (gbVec3D *->Normalize()&v6);
  if ( *(this + 8) >= (double)*(this + 11) )
    return v6->IsOverCVD(v7, v8, v9, v10, v11);
  else
    return 360.0 - v6->IsOverCVD(v7, v8, v9, v10, v11);
}

// 0x0047D320
void sub_47D320(float *this)
{
  long double v2; // st7
  long double v3; // st6
  double v4; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st5
  float v9; // eax
  float v10; // ecx
  double v11; // st7
  double v12; // st6
  float v13; // [esp+4h] [ebp-28h]
  float v14; // [esp+8h] [ebp-24h] BYREF
  float v15; // [esp+Ch] [ebp-20h]
  float v16; // [esp+10h] [ebp-1Ch]
  float v17; // [esp+14h] [ebp-18h]
  float v18; // [esp+18h] [ebp-14h]
  float v19; // [esp+1Ch] [ebp-10h]
  float v20; // [esp+24h] [ebp-8h]
  float v21; // [esp+28h] [ebp-4h]

  v2 = *(this + 22) * 0.017453292;
  v3 = *(this + 23) * 0.017453292;
  v13 = cos(v3);
  *(this + 26) = sin(v2) * v13;
  *(this + 27) = sin(v3);
  *(this + 28) = -(cos(v2) * v13);
  v4 = *(this + 25);
  v17 = v4 * *(this + 26);
  v18 = v4 * *(this + 27);
  v5 = v4 * *(this + 28);
  v6 = *(this + 11) - v17;
  v7 = *(this + 12) - v18;
  v17 = 0.0;
  v18 = v7;
  v8 = *(this + 13) - v5;
  v9 = v18;
  v18 = 0.0;
  *(this + 9) = v9;
  v19 = v8;
  v10 = v19;
  v19 = 1.0;
  *(this + 8) = v6;
  *(this + 10) = v10;
  v11 = *(this + 8) - *(this + 11);
  v20 = *(this + 9) - *(this + 12);
  v12 = *(this + 10) - *(this + 13);
  v15 = v20;
  v21 = v12;
  v14 = v11;
  v16 = v21;
  (gbVec3D *->Normalize()&v14);
  *(this + 29) = v14->IsOverCVD(v15, v16, v17, v18, v19);
}

// 0x0047D440
void __userpurge sub_47D440(int a1@<ecx>, int a2, int a3, int a4, gbMatrixStack *a5)
{
  struct gbCamera **v6; // eax
  gbSceneGraph *v7; // edi
  gbMatrixStack *v8; // edi
  double v10; // st7
  unsigned __int8 v11; // c0
  unsigned __int8 v12; // c3
  float v13; // [esp+38h] [ebp-28h]
  float v14; // [esp+38h] [ebp-28h]
  float v15; // [esp+40h] [ebp-20h]
  gbSceneGraph *v16; // [esp+50h] [ebp-10h]
  float v17; // [esp+54h] [ebp-Ch] BYREF
  float v18; // [esp+58h] [ebp-8h]
  float v19; // [esp+5Ch] [ebp-4h] BYREF
  _UNKNOWN *retaddr; // [esp+60h] [ebp+0h] BYREF
  float v21; // [esp+70h] [ebp+10h]

  v6 = *(struct gbCamera ***)(a1 + 84);
  if ( !v6 || !*(_BYTE *)a1 || !*(_BYTE *)(a1 + 80) )
    return;
  v7 = *(gbSceneGraph **)(g_pGfxManager + 448);
  v16 = v7;
  v7->Begin(*v6);
  v7->pAllRObj[19244] = 0;
  v8 = a5;
  if ( !a5 )
    v8 = *(gbMatrixStack **)(g_pGfxManager + 216);
  gbCamera::SetAsCurrent(**(gbCamera ***)(a1 + 84), 3);
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
    v21 = v10;
    retaddr = 0;
    v8->Rotate(v21, (struct gbVec3D *)&retaddr);
  }
  v8->Rotate(*(float *)(a1 + 64), (struct gbVec3D *)&retaddr);
  v15 = *(float *)(a1 + 68);
  v19 = 1.0;
  retaddr = 0;
  v8->Rotate(v15, (struct gbVec3D *)&v19);
  v13 = *(float *)(a1 + 72);
  v17 = 0.0;
  v18 = 1.0;
  v19 = 0.0;
  v8->Rotate(v13, (struct gbVec3D *)&v17);
  v14 = *(float *)(a1 + 76);
  v17 = 0.0;
  v18 = 0.0;
  v19 = 1.0;
  v8->Rotate(v14, (struct gbVec3D *)&v17);
  switch ( *(_DWORD *)(a1 + 4) )
  {
    case 1:
      goto LABEL_16;
    case 2:
      Actor::DispatchAction(0);
      break;
    case 3:
LABEL_16:
      (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(a1 + 8) + 16))(*(_DWORD *)(a1 + 8), 0);
      break;
  }
  v8->Pop();
  if ( *(_BYTE *)(a1 + 21) && *(_BYTE *)(a1 + 20) )
  {
    v8->Push();
    v17 = *(float *)(a1 + 32);
    v18 = *(float *)(a1 + 36) + *(float *)(a1 + 24);
    v19 = *(float *)(a1 + 40);
    v8->Translate((struct gbVec3D *)&v17);
    if ( *(_DWORD *)(a1 + 16) == 1 || *(_DWORD *)(a1 + 16) == 3 )
      (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(a1 + 12) + 16))(*(_DWORD *)(a1 + 12), 0);
    v8->Pop();
  }
  v16->End();
}

// 0x0047D690
void Object3D::CaculateRelative(int this, float a2)
{
  unsigned int v3; // eax
  int v4; // eax
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
  _DWORD v25[4]; // [esp+Ch] [ebp-10h] BYREF

  if ( !*(_BYTE *)this )
    return;
  if ( *(_BYTE *)(this + 80) )
  {
    switch ( *(_DWORD *)(this + 4) )
    {
      case 1:
LABEL_10:
        (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(this + 8) + 20))(*(_DWORD *)(this + 8));
        break;
      case 2:
        if ( sub_537060() )
          Actor::CompareAction(*(void **)(this + 8), 0, 0);
        Actor::QueryState(*(void **)(this + 8));
        break;
      case 3:
        goto LABEL_10;
    }
  }
  if ( *(_BYTE *)(this + 21) && *(_BYTE *)(this + 20) )
  {
    if ( *(_DWORD *)(this + 16) == 1 )
    {
      (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(this + 12) + 20))(*(_DWORD *)(this + 12));
    }
    else if ( *(_DWORD *)(this + 16) == 3 )
    {
      (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(this + 12) + 20))(*(_DWORD *)(this + 12));
      while ( gbVisNode::PopMessage(*(gbVisNode **)(this + 12), (struct gbNodeMsgObj *)v25) )
      {
        if ( v25[0] == 1 )
        {
          v3 = gbCrc32Compute(aOver);
          if ( v25[1] == v3 )
          {
            (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(this + 12) + 24))(*(_DWORD *)(this + 12), 0);
            gbVisNode::SetTimeScale(*(gbVisNode **)(this + 12), 1.0);
          }
        }
      }
    }
  }
  if ( *(_BYTE *)(this + 121) )
  {
    v4 = *(_DWORD *)(this + 144);
    if ( v4 )
    {
      if ( v4 == 1 )
      {
        if ( *(float *)(this + 128) >= (double)*(float *)(this + 132) )
        {
          if ( *(float *)(this + 128) <= (double)*(float *)(this + 132) )
          {
            if ( *(float *)(this + 128) > 360.0 )
              *(float *)(this + 128) = *(float *)(this + 128) - 360.0;
            if ( *(float *)(this + 128) < 0.0 )
              *(float *)(this + 128) = *(float *)(this + 128) + 360.0;
            *(_BYTE *)(this + 121) = 0;
          }
          else
          {
            v11 = a2 * 50.0 * *(float *)(this + 136);
            v12 = *(float *)(this + 128) - v11;
            *(float *)(this + 128) = v12;
            if ( v12 <= *(float *)(this + 132) )
              *(_DWORD *)(this + 128) = *(_DWORD *)(this + 132);
            v13 = *(float *)(this + 56) - v11;
            *(float *)(this + 56) = v13;
            if ( v15 )
              *(float *)(this + 56) = v13 + 360.0;
          }
        }
        else
        {
          v5 = a2 * 50.0 * *(float *)(this + 136);
          v6 = v5 + *(float *)(this + 128);
          *(float *)(this + 128) = v6;
          if ( v6 >= *(float *)(this + 132) )
            *(_DWORD *)(this + 128) = *(_DWORD *)(this + 132);
          v7 = v5 + *(float *)(this + 56);
          *(float *)(this + 56) = v7;
          if ( !(v9 | v10) )
            *(float *)(this + 56) = v7 - 360.0;
        }
      }
      return;
    }
    if ( *(float *)(this + 128) >= (double)*(float *)(this + 132) )
    {
      if ( *(float *)(this + 128) <= (double)*(float *)(this + 132) )
      {
        *(_BYTE *)(this + 121) = 0;
      }
      else
      {
        v18 = a2 * 50.0 * *(float *)(this + 136);
        v19 = *(float *)(this + 128) - v18;
        *(float *)(this + 128) = v19;
        *(float *)(this + 124) = *(float *)(this + 124) - v18;
        if ( v19 <= *(float *)(this + 132) )
          *(_DWORD *)(this + 128) = *(_DWORD *)(this + 132);
      }
    }
    else
    {
      v16 = a2 * 50.0 * *(float *)(this + 136);
      v17 = v16 + *(float *)(this + 128);
      *(float *)(this + 128) = v17;
      *(float *)(this + 124) = v16 + *(float *)(this + 124);
      if ( v17 >= *(float *)(this + 132) )
        *(_DWORD *)(this + 128) = *(_DWORD *)(this + 132);
    }
    v21 = *(float *)(this + 124);
    if ( v22 | v23 )
    {
      if ( v21 >= 0.0 )
      {
LABEL_52:
        *(float *)(this + 88) = *(float *)(this + 124);
        (float *->GetScreenDegree()this);
        return;
      }
      v24 = *(float *)(this + 124) + 360.0;
    }
    else
    {
      v24 = v21 - 360.0;
    }
    *(float *)(this + 124) = v24;
    goto LABEL_52;
  }
}

// 0x0047D9D0
void * Object3D::SetupCamera()
{
  float v2; // [esp+0h] [ebp-2Ch]
  float v3; // [esp+4h] [ebp-28h]
  _DWORD v4[6]; // [esp+14h] [ebp-18h] BYREF
  void *v5; // [esp+30h] [ebp+4h]
  int *v6; // [esp+34h] [ebp+8h]

  memset(v4, 0, sizeof(v4));
  v3 = 1.0 - ((double)v6[1] + (double)v6[1]) / (double)MEMORY[0xBFD6D4];
  v2 = ((double)*v6 + (double)*v6) / (double)MEMORY[0xBFD6D0] - 1.0;
  gbCamera::GetRayToScreen(**(gbCamera ***)&this->m_isLoadObj[84], v2, v3, (struct gbRay *)v4);
  qmemcpy(v5, v4, 0x18u);
  return v5;
}

// 0x0047DA60
bool Object3D::Update(int this)
{
  void *v2; // esi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  struct tagPOINT Point; // [esp+4h] [ebp-84h] BYREF
  _BYTE actionId[100]; // [esp+Ch] [ebp-7Ch] BYREF

  if ( !*(_BYTE *)(this + 80) || *(_BYTE *)(this + 121) || g_Input.? != 1 )
    return 0;
  (gbMatrix4 *->gbMatrix4()actionId);
  GRPinput::GetCursorPos(&Point);
  v2 = (Object3D *->SetupCamera()this);
  v3 = *(_DWORD *)(this + 4);
  qmemcpy(&actionId[76], v2, 0x18u);
  v4 = v3 - 1;
  if ( v4 )
  {
    v5 = v4 - 1;
    if ( v5 )
    {
      if ( v5 != 1 )
        return (gbRay *->IsColOBB()&actionId[76], (struct gbOBBox *)actionId) != 0;
      gbGeomNode::GetTotalOBBox(*(gbGeomNode **)(this + 8), (struct gbOBBox *)actionId);
    }
    else
    {
      Actor::PlayAction(*(Actor **)(this + 8), (int)actionId);
    }
  }
  else
  {
    gbGeomNode::GetOBBox(*(gbGeomNode **)(this + 8), (struct gbOBBox *)actionId);
  }
  (gbMatrix4 *->RightTranslate()actionId, (struct gbVec3D *)(this + 32));
  return (gbRay *->IsColOBB()&actionId[76], (struct gbOBBox *)actionId) != 0;
}

// 0x0047DB40
bool Object3D::GetMouseRay(int this, int a2)
{
  void *v3; // esi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  struct tagPOINT Point; // [esp+4h] [ebp-84h] BYREF
  _BYTE actionId[100]; // [esp+Ch] [ebp-7Ch] BYREF

  if ( !*(_BYTE *)(this + 80) || *(_BYTE *)(this + 121) || (g_Input.?[4 * a2 + 7] & 0xF) != 1 )
    return 0;
  (gbMatrix4 *->gbMatrix4()actionId);
  GRPinput::GetCursorPos(&Point);
  v3 = (Object3D *->SetupCamera()this);
  v4 = *(_DWORD *)(this + 4);
  qmemcpy(&actionId[76], v3, 0x18u);
  v5 = v4 - 1;
  if ( v5 )
  {
    v6 = v5 - 1;
    if ( v6 )
    {
      if ( v6 != 1 )
        return (gbRay *->IsColOBB()&actionId[76], (struct gbOBBox *)actionId) != 0;
      gbGeomNode::GetTotalOBBox(*(gbGeomNode **)(this + 8), (struct gbOBBox *)actionId);
    }
    else
    {
      Actor::PlayAction(*(Actor **)(this + 8), (int)actionId);
    }
  }
  else
  {
    gbGeomNode::GetOBBox(*(gbGeomNode **)(this + 8), (struct gbOBBox *)actionId);
  }
  (gbMatrix4 *->RightTranslate()actionId, (struct gbVec3D *)(this + 32));
  return (gbRay *->IsColOBB()&actionId[76], (struct gbOBBox *)actionId) != 0;
}

// 0x0047DC60
// attributes: thunk
int Object3D::CheckMouseLPressed()
{
  return Object3D::CheckMousePressed();
}

// 0x0047DC70
int sub_47DC70()
{
  dword_DE4C94 = 1094713344;
  return 1094713344;
}

// 0x0047DCA0
int Object3D::Create()
{
  this->UIListBox();
  *(_DWORD *)&this->m_isLoadObj[72] = &off_56A9C0;
  *(_DWORD *)&this->m_isLoadObj[76] = 0;
  *(_DWORD *)&this->m_isLoadObj[96] = 800;
  *(_DWORD *)&this->m_isLoadObj[100] = 600;
  *((_DWORD *)this + 96) = 0;
  *((_BYTE *)this + 388) = 0;
  sub_444F60((_BYTE *)this + 392);
  (_BYTE *->UIFrameWnd()this + 584);
  `eh vector constructor iterator'(
    (char *)this + 736,
    0x158u,
    5,
    (void (__thiscall *)(void *))UIScene::_UIScene,
    (void (__thiscall *)(void *))UIScene::Destroy2);
  UIItem::Refresh((int)this + 2456);
  *(_DWORD *)this->m_isLoadObj = &off_56B8A4;
  *(_DWORD *)&this->m_isLoadObj[72] = &off_56B898;
  return (int)this->m_isLoadObj;
}

// 0x0047DE40
void Object3D::Init()
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  char *v5; // ebx
  _DWORD *v6; // ebp
  gbRefObject **v7; // esi
  int v8; // [esp+1Ch] [ebp-24h] BYREF
  _DWORD v9[4]; // [esp+20h] [ebp-20h] BYREF
  int v10[4]; // [esp+30h] [ebp-10h] BYREF

  v2 = *(_DWORD *)&this->m_isLoadObj[96];
  v3 = *(_DWORD *)&this->m_isLoadObj[100];
  *(_DWORD *)&this->m_isLoadObj[88] = v2;
  *(_DWORD *)&this->m_isLoadObj[92] = v3;
  *(_DWORD *)&this->m_isLoadObj[84] = 0;
  *(_DWORD *)&this->m_isLoadObj[80] = 0;
  (UIWnd *->SetSelTexture()this,
    -1,
    0,
    0,
    *(_DWORD *)&this->m_isLoadObj[88],
    *(_DWORD *)&this->m_isLoadObj[92],
    0);
  *((_DWORD *)this + 93) = 170;
  *((_DWORD *)this + 92) = 310;
  *((_DWORD *)this + 94) = 468;
  *((_DWORD *)this + 95) = 430;
  (UINote *->Create()this + 2, -1430519792, (int)this + 368, (int)this, aUiFlexNote);
  (**((void (__thiscall ***)(char *, _DWORD))this + 98))((char *)this + 392, 0);
  v4 = *((_DWORD *)this + 93) + 10;
  v9[0] = *((_DWORD *)this + 92) + 10;
  v9[1] = v4;
  v9[2] = v9[0] + 136;
  v9[3] = v4 + 128;
  (*(void (__thiscall **)(char *, int, _DWORD *, Object3D *))(*((_DWORD *)this + 146) + 16))(
    (char *)this + 584,
    -1430519792,
    v9,
    this);
  (_DWORD *->SetShow()this + 146, 0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v8 + 1) = -5;
    LOBYTE(v8) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v8 + 1) = 8187;
    LOBYTE(v8) = -1;
  }
  HIBYTE(v8) = -1;
  (_DWORD *->GetChild()this + 146, &v8);
  (**((void (__thiscall ***)(char *, _DWORD))this + 146))((char *)this + 584, 0);
  v5 = byte_DC733C;
  v6 = &unk_56B884;
  v7 = (gbRefObject **)((char *)this + 736);
  do
  {
    ((void (__thiscall *)(gbRefObject **, _DWORD, _DWORD *, Object3D *, char *, _DWORD, int))(*v7)[7].RefCount)(
      v7,
      *v6,
      v9,
      this,
      aSubgameHocksho_0,
      0,
      1);
    v7->OpenScript(aSubgameHocksho_1, 1);
    sub_43AFA0((char *)v7, v5);
    v7[27] = (gbRefObject *)3;
    v7[26] = (gbRefObject *)1;
    v7[52] = (gbRefObject *)1;
    ((void (__thiscall *)(gbRefObject **, _DWORD))(*v7)->RefCount)(v7, 0);
    ++v6;
    v5 += 256;
    v7 += 86;
  }
  while ( (int)v6 < (int)&off_56B898 );
  v10[1] = 200;
  v10[0] = 300;
  v10[2] = 500;
  v10[3] = 300;
  UIItem::Create((int)this + 2456, (int)&unk_ABE000, v10, (int)this, 3, 0);
  (_DWORD *->SetData()this + 614, 18, 255, 28, 200);
  *((_BYTE *)this + 3829) = 0;
  *((_BYTE *)this + 3830) = 0;
}
