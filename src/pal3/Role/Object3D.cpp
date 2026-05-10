#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Object3D.h"
#include "pal3/gen/Actor.h"
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
int sub_43AFA0(...);
int sub_444F60(...);

// Unnamed globals (extern)
extern char aSubgameHocksho_0[];
extern char aSubgameHocksho_1[];
extern char aUiFlexNote[];
extern unsigned char byte_DC733C;
extern void *off_56A66C;
extern void *off_56A9C0;
extern void *off_56B898;
extern void *off_56B8A4;
extern void *off_596420;
extern void *off_596424;
extern int unk_56B884;
extern int unk_ABE000;

// 0x0047CB90
struct gbVFileSystem * Object3D::_Object3D(const char *a2, int a3)
{
  gbGeomNode *v4; // eax
  gbGeomNode *v5; // edi
  gbGeomNode *v6; // ecx
  int v7; // eax
  gbGeomNode *v8; // eax
  char Destination[4]; // [esp+10h] [ebp-60h] BYREF
  OpenBaseFile v11; // [esp+14h] [ebp-5Ch] BYREF
  _BYTE v12[68]; // [esp+18h] [ebp-58h] BYREF
  __int32 v13; // [esp+5Ch] [ebp-14h]
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
    v4 = (gbGeomNode *)((operator *)0x118u)->new();
    v5 = v4;
    LOBYTE(v14) = 1;
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
    LOBYTE(v14) = 0;
    this->m_pol = v6;
    v6->LoadFromFile(a2, 0, 0);
    ((gbGeomNode *)this->m_pol)->GetOBBox((struct gbOBBox *)v12);
    goto LABEL_13;
  }
  if ( !_strcmpi(Destination, off_596420) )
  {
    this->m_type = 3;
    v4 = (gbGeomNode *)((operator *)0x118u)->new();
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
  v7 = ((operator *)0x224u)->new();
  LOBYTE(v14) = 3;
  if ( v7 )
    v8 = (gbGeomNode *)v7->FastInit();
  else
    v8 = 0;
  LOBYTE(v14) = 0;
  this->m_pol = v8;
  ((Actor *)v8)->LoadModel();
  ((Actor *)this->m_pol)->CompareAction(a3, 0);
  (*(void (**)(_DWORD, _BYTE *, int))(**(_DWORD **)(this->m_pol->Children.m_numNode + 88) + 28))(
    *(_DWORD *)(this->m_pol->Children.m_numNode + 88),
    v12,
    this->m_pol->Children.m_numNode);
LABEL_13:
  this->m_showSubObj = v13;
  LOBYTE(this->m_isLoadObj) = 1;
  LOBYTE(this->m_dropy) = 1;
  LODWORD(this->m_rotDstSpeed) = a3;
  v14 = -1;
  return ((OpenNULLFile **)&v11)->OpenNULLFile();
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
        return (unsigned __int8)((OpenNULLFile **)&v13)->OpenNULLFile();
      }
      this->m_subObj = (gbGeomNode *)3;
      v9 = (Actor *)((operator *)0x118u)->new();
      v10 = v9;
      LOBYTE(v14) = 2;
      if ( v9 )
      {
        v9->gbGeomNode();
        v10->m_actarray = (__int32)&off_56A66C;
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
      v6 = (Actor *)((operator *)0x118u)->new();
      v7 = v6;
      LOBYTE(v14) = 1;
      if ( v6 )
      {
        v6->gbGeomNode();
        v7->m_actarray = (__int32)&off_56A66C;
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

// 0x0047D9D0
void * Object3D::SetupCamera()
{
  float v2; // [esp+0h] [ebp-2Ch]
  float v3; // [esp+4h] [ebp-28h]
  struct gbRay v4; // [esp+14h] [ebp-18h] BYREF
  struct gbRay *v5; // [esp+30h] [ebp+4h]
  int *v6; // [esp+34h] [ebp+8h]

  memset(&v4, 0, sizeof(v4));
  v3 = 1.0 - ((double)v6[1] + (double)v6[1]) / (double)g_Input.KeyInfo[120].HoldTime;
  v2 = ((double)*v6 + (double)*v6) / (double)g_Input.KeyInfo[120].Data - 1.0;
  ((gbCamera *)*(gbCamera **)LODWORD(this->m_dropz))->GetRayToScreen(v2, v3, &v4);
  qmemcpy(v5, &v4, sizeof(struct gbRay));
  return v5;
}

// 0x0047DCA0
int Object3D::Create()
{
  ((UIListBox *)this)->UIListBox();
  LODWORD(this->m_rotz) = &off_56A9C0;
  this->m_dropx = 0.0;
  LODWORD(this->m_yaw) = 800;
  LODWORD(this->m_pitch) = 600;
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
  this->m_isLoadObj = (__int32)&off_56B8A4;
  LODWORD(this->m_rotz) = &off_56B898;
  return (int)this;
}

// 0x0047DE40
void Object3D::Init()
{
  __int32 m_yaw_low; // eax
  float m_pitch; // ecx
  int v4; // eax
  char *v5; // ebx
  _DWORD *v6; // ebp
  PalScript **v7; // esi
  char id; // [esp+1Ch] [ebp-24h] BYREF
  __int16 id_1; // [esp+1Dh] [ebp-23h]
  char id_3; // [esp+1Fh] [ebp-21h]
  _DWORD v11[4]; // [esp+20h] [ebp-20h] BYREF
  int a3[4]; // [esp+30h] [ebp-10h] BYREF

  m_yaw_low = LODWORD(this->m_yaw);
  m_pitch = this->m_pitch;
  this->m_visible = m_yaw_low;
  *(float *)&this->m_pCamera = m_pitch;
  this->m_dropz = 0.0;
  this->m_dropy = 0.0;
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, this->m_visible, (int)this->m_pCamera, 0);
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
    ((void (*)(PalScript **, _DWORD))(*v7)->m_bLoadSceneScript)(v7, 0);
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
