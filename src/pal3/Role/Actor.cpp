#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/UIItem.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_43FD90(...);
int sub_43FE90(...);
int sub_4A1530(...);
int sub_4A1CF0(...);
int sub_535FD0(...);
int sub_5370E0(...);
int sub_5372B0(...);
int sub_5372D0(...);
int sub_5374E0(...);
int sub_537510(...);

// Unnamed globals (extern)
extern char aPal3Timenotefi_96_0[];
extern unsigned char byte_DD893C;
extern unsigned char byte_DD8B3C;
extern unsigned char byte_DDAD3C;
extern int dword_17B129C;
extern int dword_17B154C;
extern float flt_17B1298;
extern float flt_17B1548;
extern void *off_570904;
extern void *off_60154C;

// 0x00536160
int Actor::SetParam(int a2)
{
  int v3; // eax
  int result; // eax
  int v5; // ecx
  int v6; // ecx
  float v7[17]; // [esp+4h] [ebp-44h] BYREF

  if ( this->m_actarray[216] )
  {
    v3 = rand();
    Actor::SetAction(*(Actor **)&this->m_actarray[224], -83 - v3 % 34);
    this->m_actarray[217] = 1;
  }
  gbGeomNode::GetTotalOBBox(*(gbGeomNode **)this->m_actarray, (struct gbOBBox *)&this->m_actarray[12]);
  sub_535FD0(
    (float *)this->m_actarray,
    v7,
    *(float *)&this->m_actarray[168],
    *(float *)&this->m_actarray[172],
    *(float *)&this->m_actarray[176]);
  result = (*(int (**)(_DWORD))(**(_DWORD **)this->m_actarray + 20))(*(_DWORD *)this->m_actarray);
  v5 = *(_DWORD *)&this->m_actarray[4];
  if ( v5 )
    result = (*(int (**)(int))(*(_DWORD *)v5 + 20))(v5);
  v6 = *(_DWORD *)&this->m_actarray[8];
  if ( v6 )
    return (*(int (**)(int))(*(_DWORD *)v6 + 20))(v6);
  return result;
}

// 0x00536220
// attributes: thunk
int __cdecl Actor::GetDefaultFOV_thunk()
{
  return Actor::SetDefaultFOV();
}

// 0x00536230
int Actor::SetDefaultFOV()
{
  dword_17B129C = 1094713344;
  return 1094713344;
}

// 0x00536240
// attributes: thunk
int __cdecl Actor::GetDefaultDist_thunk()
{
  int result; // eax

  Actor::SetDefaultDist();
  return result;
}

// 0x00536250
void Actor::SetDefaultDist()
{
  flt_17B1298 = 12.0 + 12.0;
}

// 0x005363A0
int Actor::ResetState()
{
  *(_DWORD *)&this->m_actarray[340] = 0;
  this->m_actarray[332] = 0;
  this->m_actarray[333] = 0;
  return 0;
}

// 0x005363C0
int Actor::Cleanup()
{
  if ( *(_DWORD *)&this->m_actarray[340] )
    operator delete(*(void **)&this->m_actarray[340]);
  return this->ResetState();
}

// 0x005363E0
void Actor::SetAction(int actionId)
{
  int v3; // eax
  int v4; // eax
  float v5; // [esp+8h] [ebp-Ch]
  float v6; // [esp+8h] [ebp-Ch]

  if ( this->m_actarray[344] )
  {
    v3 = *(_DWORD *)&this->m_actarray[348];
    if ( v3 )
    {
      v4 = actionId + v3;
      this->m_actarray[344] = 0;
      *(_DWORD *)&this->m_actarray[348] = v4;
      if ( v4 <= 0 )
      {
        (**((void (***)(char *, _DWORD))this + 774))((char *)this + 3096, 0);
        (**((void (***)(char *, _DWORD))this + 835))((char *)this + 3340, 0);
        sprintf(&this->m_actarray[72], "       %s\\n       %s", byte_DD893C, byte_DD8B3C);
        (_DWORD *->SetEnable()this + 204, &this->m_actarray[72], 0);
        sub_4A1530((int)&this->m_actarray[360], 1);
        *(_DWORD *)&this->m_actarray[348] = 0;
      }
      v5 = (float)*(int *)&this->m_actarray[352];
      UIWnd::FindChild((int)this + 3096, v5);
      v6 = (float)*(int *)&this->m_actarray[348];
      UIWnd::FindChildByName((int)this + 3096, v6);
      this->m_actarray[332] = 1;
    }
  }
}

// 0x005364B0
int Actor::InitComponents()
{
  int v2; // eax
  void (**v3)(char *, bool); // edx
  float v5; // [esp+0h] [ebp-Ch]
  float v6; // [esp+0h] [ebp-Ch]

  this->m_actarray[345] = 0;
  (_DWORD *->SetEnable()this + 546, byte_DDAD3C, 0);
  sub_4A1530((int)this + 1728, 1);
  *(_DWORD *)&this->m_actarray[348] = 1000;
  *(_DWORD *)&this->m_actarray[352] = 1000;
  sub_43FE90((int)this + 3096);
  v5 = (float)*(int *)&this->m_actarray[352];
  UIWnd::FindChild((int)this + 3096, v5);
  v6 = (float)*(int *)&this->m_actarray[348];
  UIWnd::FindChildByName((int)this + 3096, v6);
  v2 = *(_DWORD *)&this->m_actarray[348];
  v3 = (void (**)(char *, bool))*((_DWORD *)this + 774);
  this->m_actarray[356] = v2 <= 0;
  (*v3)((char *)this + 3096, v2 > 0);
  return (**((int (***)(char *, bool))this + 835))(
           (char *)this + 3340,
           *(_DWORD *)&this->m_actarray[348] > 0);
}

// 0x00536560
char Actor::ProcessFrame()
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  float v13; // [esp+Ch] [ebp-58h]
  float v14; // [esp+Ch] [ebp-58h]
  char id; // [esp+20h] [ebp-44h] BYREF
  __int16 id_1; // [esp+21h] [ebp-43h]
  char id_3; // [esp+23h] [ebp-41h]
  int v18; // [esp+24h] [ebp-40h] BYREF
  int v19; // [esp+28h] [ebp-3Ch]
  int v20; // [esp+2Ch] [ebp-38h]
  int v21; // [esp+30h] [ebp-34h]
  _DWORD v22[4]; // [esp+34h] [ebp-30h] BYREF
  int a3[4]; // [esp+44h] [ebp-20h] BYREF
  int v24[4]; // [esp+54h] [ebp-10h] BYREF

  (UIListBox *->SetSelTexture()this, -1, 0, 0, 800, 600, 0);
  v2 = operator new(0xCu);
  if ( v2 )
  {
    *(_BYTE *)(v2 + 8) = 0;
    *(_DWORD *)(v2 + 4) = 0;
    *(_DWORD *)v2 = 0;
  }
  else
  {
    v2 = 0;
  }
  *(_DWORD *)&this->m_szTexture[72] = v2;
  *(_DWORD *)&this->m_szTexture[80] = 1000;
  *(_DWORD *)&this->m_szTexture[84] = 1000;
  v3 = *((_DWORD *)this + 774);
  this->m_szTexture[70] = -58;
  this->m_szTexture[69] = 116;
  this->m_szTexture[68] = 36;
  v19 = 310;
  v18 = 350;
  v20 = 440;
  v21 = 322;
  (*(void (**)(char *, int, int *, Actor *))(v3 + 16))((char *)this + 3096, -5570049, &v18, this);
  (UIWnd **->GetChildCount()this + 774, aPal3Timenotefi_96_0, *((_BYTE *)this + 3492));
  (UIWnd **->GetChildAt()this + 774, off_60154C, *((_BYTE *)this + 3492));
  sub_43FD90((float *)this + 774, 2);
  (UIWnd *->GetWidth()((char *)this + 3096), 2);
  (UIWnd *->SetFrameRate()((char *)this + 3096), 2);
  (UIWnd *->GetHeight()((char *)this + 3096), 2);
  (UIWnd *->GetPosition()((char *)this + 3096), 1);
  *((_DWORD *)this + 827) = 1;
  v13 = (float)*(int *)&this->m_szTexture[84];
  UIWnd::FindChild((int)this + 3096, v13);
  v14 = (float)*(int *)&this->m_szTexture[80];
  UIWnd::FindChildByName((int)this + 3096, v14);
  v4 = v20;
  v22[0] = v18;
  v5 = v19;
  *((_DWORD *)this + 834) = 400;
  v22[1] = v5 - 26;
  v22[2] = v4;
  *((_DWORD *)this + 832) = 1101004800;
  *((_DWORD *)this + 829) = 255;
  v22[3] = v5 - 26 + 32;
  (*(void (**)(char *, int, _DWORD *, Actor *))(*((_DWORD *)this + 835) + 16))(
    (char *)this + 3340,
    -5570049,
    v22,
    this);
  (UIWnd *->SetShow()((char *)this + 3340), 0);
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
  (UIWnd *->GetChild()((char *)this + 3340), (int)&id);
  a3[1] = 250;
  a3[0] = 300;
  a3[2] = 500;
  a3[3] = 370;
  (UIItem *->Create()&this->m_szTexture[92], -5569793, (int)a3);
  v6 = *(_DWORD *)&this->m_szTexture[176] + 22;
  *(_DWORD *)&this->m_szTexture[188] = *(_DWORD *)&this->m_szTexture[172] + 6;
  v7 = *(_DWORD *)&this->m_szTexture[184];
  *(_DWORD *)&this->m_szTexture[192] = v6;
  v8 = *(_DWORD *)&this->m_szTexture[180] - 6;
  *(_DWORD *)&this->m_szTexture[200] = v7 - 38;
  *((_DWORD *)this + 426) = 0;
  *((_DWORD *)this + 427) = 16;
  *(_DWORD *)&this->m_szTexture[196] = v8;
  (UIWnd *->GetRect()((char *)this + 816), &this->m_szTexture[188]);
  (UIItem *->SetData()&this->m_szTexture[92], 31);
  this->m_szTexture[88] = 0;
  this->m_szTexture[76] = 1;
  this->m_szTexture[77] = 0;
  v24[1] = 200;
  v24[0] = 250;
  v24[2] = 550;
  v24[3] = 328;
  (UIItem *->Create()this + 1728, -5520641, (int)v24);
  (UIItem *->SetData()this + 1728, 31);
  v9 = *((_DWORD *)this + 452);
  v10 = *((_DWORD *)this + 454);
  *((_DWORD *)this + 457) = *((_DWORD *)this + 453) + 26;
  *((_DWORD *)this + 456) = v9 + 6;
  v11 = *((_DWORD *)this + 455) - 38;
  *((_DWORD *)this + 768) = 0;
  *((_DWORD *)this + 769) = 20;
  *((_DWORD *)this + 458) = v10 - 6;
  *((_DWORD *)this + 459) = v11;
  (UIWnd *->GetRect()this + 21, (_DWORD *)this + 456);
  (UIWnd *->SetEnable()this + 21, byte_DDAD3C, 0);
  sub_4A1530((int)this + 1728, 1);
  return 1;
}

// 0x005368A0
BOOL Actor::HandleEvent(int a2, int a3)
{
  int v5; // edi
  DWORD TickCount; // eax
  DWORD v7; // eax
  unsigned int v8; // edx
  char v9; // al
  char v10; // al
  char v11; // al

  if ( this->m_szTexture[88] )
    return (UIWnd *->HitTest()this, a2, a3);
  if ( !this->m_szTexture[77] && sub_4A1CF0((_DWORD *)this + 432) == 2 )
    this->m_szTexture[77] = 1;
  sprintf(&this->m_name[64], "%d/%d", (int)*((float *)this + 813), *(_DWORD *)&this->m_szTexture[84]);
  (UIWnd *->SetEnable()((char *)this + 3340), &this->m_name[64], 1);
  if ( this->m_szTexture[64] )
  {
    v5 = *(_DWORD *)&this->m_szTexture[72];
    if ( !*(_BYTE *)(v5 + 8) )
    {
      TickCount = GetTickCount();
      *(_DWORD *)v5 = TickCount;
      *(_DWORD *)(v5 + 4) = TickCount;
      *(_BYTE *)(v5 + 8) = 1;
    }
    v7 = GetTickCount();
    v8 = v7 - *(_DWORD *)(v5 + 4);
    *(_DWORD *)v5 = v7;
    if ( v8 <= 0x7D0 )
    {
      v9 = this->m_szTexture[65];
      this->m_szTexture[76] = 0;
      if ( v9 )
      {
        v10 = this->m_szTexture[71] + 20;
        this->m_szTexture[71] = v10;
        if ( v10 == -1 )
        {
          this->m_szTexture[71] = -1;
          this->m_szTexture[65] = 0;
        }
      }
      else
      {
        v11 = this->m_szTexture[71];
        this->m_szTexture[71] = v11 - 20;
        if ( v11 == 20 )
        {
          this->m_szTexture[71] = 0;
          this->m_szTexture[65] = 1;
        }
      }
    }
    else
    {
      *(_DWORD *)(v5 + 4) = v7;
      *(_BYTE *)(v5 + 8) = 0;
      this->m_szTexture[64] = 0;
      this->m_szTexture[76] = 1;
      this->m_szTexture[71] = -1;
    }
  }
  this->m_szTexture[88] = sub_4A1CF0(&this->m_szTexture[92]) == 2;
  return (UIWnd *->HitTest()this, a2, a3);
}

// 0x00536A40
// attributes: thunk
int __cdecl Actor::GetDefaultFOV2_thunk()
{
  return Actor::SetDefaultFOV2();
}

// 0x00536A50
int Actor::SetDefaultFOV2()
{
  dword_17B154C = 1094713344;
  return 1094713344;
}

// 0x00536A60
// attributes: thunk
int __cdecl Actor::GetDefaultDist2_thunk()
{
  int result; // eax

  Actor::SetDefaultDist2();
  return result;
}

// 0x00536A70
void Actor::SetDefaultDist2()
{
  flt_17B1548 = 12.0 + 12.0;
}

// 0x00536A80
int Actor::FastInit(int a1)
{
  *(_BYTE *)a1 = HIBYTE(a1);
  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 12) = 0;
  *(_DWORD *)(a1 + 540) = 0;
  *(_DWORD *)(a1 + 544) = 0;
  memset((void *)(a1 + 20), 0, 0x104u);
  memset((void *)(a1 + 280), 0, 0x104u);
  return a1;
}

// 0x00536AC0
int Actor::LoadAction(char *name)
{
  char *v3; // ebx
  char *v5; // edi
  unsigned int v6; // kr04_4
  int v7; // eax
  unsigned int v8; // esi
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  gbActor *v13; // ecx
  char *v14; // esi
  int v15; // ebp
  int v16; // [esp-4h] [ebp-30h]
  _BYTE v17[16]; // [esp+10h] [ebp-1Ch] BYREF
  int v18; // [esp+28h] [ebp-4h]

  v3 = (char *)&this->m_actarray[540];
  if ( !strcmp(name, &this->m_actarray[540]) )
    return 1;
  v6 = strlen(name) + 1;
  v5 = (char *)&name[v6];
  qmemcpy(v3, name, 4 * (v6 >> 2));
  qmemcpy(&v3[4 * (v6 >> 2)], &v5[4 * (v6 >> 2) - v6], v6 & 3);
  _strlwr(v3);
  v7 = *(_DWORD *)&this->m_actarray[4];
  v8 = 0;
  if ( v7 && (unsigned int)((*(_DWORD *)&this->m_actarray[8] - v7) >> 2) > 1 )
  {
    *(_DWORD *)&this->m_actarray[16] = 0;
    v9 = gbCrc32Compute(v3);
    while ( 1 )
    {
      v10 = *(_DWORD *)&this->m_actarray[4];
      if ( !v10 || v8 >= (*(_DWORD *)&this->m_actarray[8] - v10) >> 2 )
        break;
      if ( sub_5370E0(v9, *(_DWORD *)(v10 + 4 * v8)) )
      {
        *(_DWORD *)&this->m_actarray[16] = *(_DWORD *)(*(_DWORD *)&this->m_actarray[4] + 4 * v8);
        break;
      }
      ++v8;
    }
  }
  v16 = *(_DWORD *)&this->m_actarray[16];
  v11 = gbCrc32Compute(v3);
  v12 = sub_5370E0(v11, v16);
  v13 = (gbActor *)*(gbActor **)&this->m_actarray[16];
  if ( !v13 || !v12 )
    return 0;
  v13->GotoAction(v3, 0);
  while ( gbVisNode::PopMessage(*(gbVisNode **)&this->m_actarray[16], (struct gbNodeMsgObj *)v17) )
    ;
  v14 = (char *)&this->m_actarray[280];
  if ( this->m_actarray[280] )
  {
    OpenBaseFile::OpenBaseFile(&name);
    v15 = *(_DWORD *)&this->m_actarray[16];
    v18 = 0;
    (*(void (**)(_DWORD, char *))(**(_DWORD **)(v15 + 88) + 60))(*(_DWORD *)(v15 + 88), v14);
    v18 = -1;
    (struct gbVFileSystem **->OpenNULLFile()&name);
  }
  return 1;
}

// 0x00536C50
int Actor::CompareAction(int actionIdx, int a3)
{
  if ( !strcmp((&off_570904)[actionIdx], &this->m_actarray[540]) )
    return 1;
  else
    return this->LoadAction((&off_570904)[actionIdx]);
}

// 0x00536CC0
unsigned int Actor::GetAnimDuration(int animId)
{
  return gbActor::GetActionDuration(*(gbActor **)&this->m_actarray[16], (char *)animId);
}

// 0x00536CE0
void Actor::EnableTransition(int a2, int a3)
{
  gbActor::EnableActionTransMtl(*(gbActor **)&this->m_actarray[16], (char *)a2, a3);
}

// 0x00536D00
void Actor::SetTimeScale(float scale)
{
  gbVisNode::SetTimeScale(*(gbVisNode **)&this->m_actarray[16], scale);
}

// 0x00536D20
void * Actor::LoadModel()
{
  int v2; // esi
  struct gbActor *ActorFile; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // esi
  int v6; // edx
  unsigned int v7; // ecx
  int v8; // eax
  int v9; // eax
  _DWORD *v10; // edi
  _DWORD *v11; // ebp
  int v12; // eax
  _DWORD *v13; // ecx
  _DWORD *i; // eax
  int v16; // [esp+10h] [ebp-11Ch] BYREF
  struct gbVFileSystem *v17; // [esp+14h] [ebp-118h] BYREF
  void *v18; // [esp+18h] [ebp-114h]
  char Buffer[260]; // [esp+1Ch] [ebp-110h] BYREF
  int v20; // [esp+128h] [ebp-4h]
  const char *v21; // [esp+130h] [ebp+4h]

  this->UpdateAllActions();
  strcpy(&this->m_actarray[20], v21);
  OpenBaseFile::OpenBaseFile(&v17);
  v2 = 0;
  v20 = 0;
  sprintf(Buffer, "role\\%s\\%s.ini", &this->m_actarray[20], &this->m_actarray[20]);
  if ( (int)g_pVFileSys->FileExistNum(Buffer) > 0 )
  {
    ActorFile = (gbActorMgr *->LoadActorFile()g_pActorMgr, Buffer);
    *(_DWORD *)&this->m_actarray[16] = ActorFile;
    if ( ActorFile )
    {
      v4 = (_DWORD *)*(_DWORD **)&this->m_actarray[8];
      v5 = v4;
      if ( (*(_DWORD *)&this->m_actarray[12] - (int)v4) >> 2 )
      {
        sub_5374E0(v4, v4, v4 + 1);
        sub_537510(
          *(_DWORD **)&this->m_actarray[8],
          (_DWORD *)(1 - ((*(_DWORD *)&this->m_actarray[8] - (int)v5) >> 2)),
          &this->m_actarray[16]);
        v13 = (_DWORD *)*(_DWORD **)&this->m_actarray[8];
        for ( i = v5; i != v13; ++i )
          * i = (*)*(_DWORD *)&this->m_actarray[16];
        *(_DWORD *)&this->m_actarray[8] += 4;
      }
      else
      {
        v6 = *(_DWORD *)&this->m_actarray[4];
        if ( !v6 || (v7 = ((int)v4 - v6) >> 2, v7 <= 1) )
          v7 = 1;
        if ( v6 )
          v8 = ((int)v4 - v6) >> 2;
        else
          v8 = 0;
        v9 = v7 + v8;
        v16 = v9;
        if ( v9 < 0 )
          v9 = 0;
        v10 = (_DWORD *)operator new(4 * v9);
        v11 = (_DWORD *)sub_5374E0(*(_DWORD **)&this->m_actarray[4], v5, v10);
        sub_537510(v11, (_DWORD *)1, &this->m_actarray[16]);
        sub_5374E0(v5, *(_DWORD **)&this->m_actarray[8], v11 + 1);
        v18 = (void *)*(void **)&this->m_actarray[4];
        operator delete(v18);
        *(_DWORD *)&this->m_actarray[12] = &v10[v16];
        v12 = sub_5372B0(this);
        *(_DWORD *)&this->m_actarray[4] = v10;
        *(_DWORD *)&this->m_actarray[8] = &v10[v12 + 1];
      }
    }
  }
  else
  {
    do
    {
      sprintf(Buffer, "role\\%s\\%02d.ini", &this->m_actarray[20], v2);
      v16 = 0;
      if ( g_pVFileSys->FileExistNum(Buffer) )
      {
        v16 = (int)(gbActorMgr *->LoadActorFile()g_pActorMgr, Buffer);
        if ( !v16 )
          goto LABEL_21;
        sub_5372D0((int)this, *(_DWORD **)&this->m_actarray[8], 1u, &v16);
      }
      ++v2;
    }
    while ( v2 < 10 );
    *(_DWORD *)&this->m_actarray[16] = **(_DWORD **)&this->m_actarray[4];
  }
LABEL_21:
  v20 = -1;
  return OpenNULLFile::OpenNULLFile(&v17);
}

// 0x00536FB0
int Actor::QueryState()
{
  return (*(int (**)(_DWORD))(**(_DWORD **)&this->m_actarray[16] + 20))(*(_DWORD *)&this->m_actarray[16]);
}

// 0x00536FC0
int Actor::DispatchAction(int actionId)
{
  return (*(int (**)(_DWORD, int))(**(_DWORD **)&this->m_actarray[16] + 16))(
           *(_DWORD *)&this->m_actarray[16],
           actionId);
}

// 0x00536FD0
int Actor::PlayAction(int actionId)
{
  return (*(int (**)(_DWORD, int, _DWORD))(**(_DWORD **)(*(_DWORD *)&this->m_actarray[16] + 88) + 28))(
           *(_DWORD *)(*(_DWORD *)&this->m_actarray[16] + 88),
           actionId,
           *(_DWORD *)&this->m_actarray[16]);
}

// 0x00536FF0
int Actor::UpdateAllActions()
{
  unsigned int i; // edi
  int v3; // eax
  int result; // eax
  char *v5; // esi

  for ( i = 0; ; ++i )
  {
    v3 = *(_DWORD *)&this->m_actarray[4];
    if ( !v3 || i >= (*(_DWORD *)&this->m_actarray[8] - v3) >> 2 )
      break;
    (gbActorMgr *->DestroyActor()g_pActorMgr, *(struct gbActor **)(v3 + 4 * i));
  }
  result = *(_DWORD *)&this->m_actarray[8];
  *(_DWORD *)&this->m_actarray[8] = *(_DWORD *)&this->m_actarray[4];
  *(_DWORD *)&this->m_actarray[16] = 0;
  v5 = (char *)&this->m_actarray[540];
  *(_DWORD *)v5 = 0;
  *((_DWORD *)v5 + 1) = 0;
  return result;
}

// 0x005371B0
void Actor::SetVisible(int bVisible)
{
  int v3; // eax
  int v4; // eax
  gbActor *v5; // ecx
  char *v6; // esi
  int v7; // ebx
  int v8; // [esp+0h] [ebp-2Ch]
  _DWORD v9[4]; // [esp+10h] [ebp-1Ch] BYREF
  int v10; // [esp+28h] [ebp-4h]
  char *v11; // [esp+34h] [ebp+8h]
  char *v12; // [esp+38h] [ebp+Ch]

  if ( bVisible )
  {
    strcpy(&this->m_actarray[540], (const char *)bVisible);
    _strlwr(&this->m_actarray[540]);
  }
  v8 = *(_DWORD *)&this->m_actarray[16];
  v3 = gbCrc32Compute(&this->m_actarray[540]);
  v4 = sub_5370E0(v3, v8);
  v5 = (gbActor *)*(gbActor **)&this->m_actarray[16];
  if ( v5 && v4 )
  {
    v5->GotoAction(&this->m_actarray[540], v11, v12);
    while ( gbVisNode::PopMessage(*(gbVisNode **)&this->m_actarray[16], (struct gbNodeMsgObj *)v9) )
      ;
    v6 = (char *)&this->m_actarray[280];
    if ( this->m_actarray[280] )
    {
      OpenBaseFile::OpenBaseFile(&bVisible);
      v7 = *(_DWORD *)&this->m_actarray[16];
      v10 = 0;
      (*(void (**)(_DWORD, char *))(**(_DWORD **)(v7 + 88) + 60))(*(_DWORD *)(v7 + 88), v6);
      v10 = -1;
      (struct gbVFileSystem **->OpenNULLFile()&bVisible);
    }
  }
}
