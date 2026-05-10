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
extern int dword_BFDA64;
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

  if ( this->m_name[196] )
  {
    v3 = rand();
    ((Actor *)*(Actor **)&this->m_name[204])->SetAction(-83 - v3 % 34);
    this->m_name[197] = 1;
  }
  ((gbGeomNode *)this->m_actarray)->GetTotalOBBox((struct gbOBBox *)&this->_pad_0004[8]);
  sub_535FD0(
    (float *)this,
    v7,
    *(float *)&this->m_name[148],
    *(float *)&this->m_name[152],
    *(float *)&this->m_name[156]);
  result = (*(int (**)(void *))(*(_DWORD *)this->m_actarray + 20))(this->m_actarray);
  v5 = *(_DWORD *)this->_pad_0004;
  if ( v5 )
    result = (*(int (**)(int))(*(_DWORD *)v5 + 20))(v5);
  v6 = *(_DWORD *)&this->_pad_0004[4];
  if ( v6 )
    return (*(int (**)(int))(*(_DWORD *)v6 + 20))(v6);
  return result;
}

// 0x00536220
// attributes: thunk
int Actor::GetDefaultFOV_thunk()
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
int Actor::GetDefaultDist_thunk()
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
  *(_DWORD *)&this->m_szTexture[60] = 0;
  this->m_szTexture[52] = 0;
  this->m_szTexture[53] = 0;
  return 0;
}

// 0x005363C0
int Actor::Cleanup()
{
  if ( *(_DWORD *)&this->m_szTexture[60] )
    operator delete(*(void **)&this->m_szTexture[60]);
  return this->ResetState();
}

// 0x005363E0
void Actor::SetAction(int actionId)
{
  int v3; // eax
  int v4; // eax
  float v5; // [esp+8h] [ebp-Ch]
  float v6; // [esp+8h] [ebp-Ch]

  if ( this->m_szTexture[64] )
  {
    v3 = *(_DWORD *)&this->m_szTexture[68];
    if ( v3 )
    {
      v4 = actionId + v3;
      this->m_szTexture[64] = 0;
      *(_DWORD *)&this->m_szTexture[68] = v4;
      if ( v4 <= 0 )
      {
        (**((void (***)(char *, _DWORD))this + 774))((char *)this + 3096, 0);
        (**((void (***)(char *, _DWORD))this + 835))((char *)this + 3340, 0);
        sprintf(&this->m_name[52], "       %s\\n       %s", byte_DD893C, byte_DD8B3C);
        ((UIWnd *)((char *)this + 816))->SetEnable(&this->m_name[52], 0);
        sub_4A1530((int)&this->m_szTexture[80], 1);
        *(_DWORD *)&this->m_szTexture[68] = 0;
      }
      v5 = (float)*(int *)&this->m_szTexture[72];
      ((UIWnd *)((char *)this + 3096))->FindChild(v5);
      v6 = (float)*(int *)&this->m_szTexture[68];
      ((UIWnd *)((char *)this + 3096))->FindChildByName(v6);
      this->m_szTexture[52] = 1;
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

  this->m_szTexture[65] = 0;
  ((UIWnd *)(UIWnd *)this + 26)->SetEnable(byte_DDAD3C, 0);
  sub_4A1530((int)this + 1728, 1);
  *(_DWORD *)&this->m_szTexture[68] = 1000;
  *(_DWORD *)&this->m_szTexture[72] = 1000;
  sub_43FE90((int)this + 3096);
  v5 = (float)*(int *)&this->m_szTexture[72];
  ((UIWnd *)((char *)this + 3096))->FindChild(v5);
  v6 = (float)*(int *)&this->m_szTexture[68];
  ((UIWnd *)((char *)this + 3096))->FindChildByName(v6);
  v2 = *(_DWORD *)&this->m_szTexture[68];
  v3 = (void (**)(char *, bool))*((_DWORD *)this + 774);
  this->m_szTexture[76] = v2 <= 0;
  (*v3)((char *)this + 3096, v2 > 0);
  return (**((int (***)(char *, bool))this + 835))(
           (char *)this + 3340,
           *(_DWORD *)&this->m_szTexture[68] > 0);
}

// 0x00536560
char Actor::ProcessFrame()
{
  _DWORD *v2; // eax
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

  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, 800, 600, 0);
  v2 = (_DWORD *)operator new(0xCu);
  if ( v2 )
  {
    *((_BYTE *)v2 + 8) = 0;
    v2[1] = 0;
    *v2 = 0;
  }
  else
  {
    v2 = 0;
  }
  *(_DWORD *)&this->m_szTexture[60] = v2;
  *(_DWORD *)&this->m_szTexture[68] = 1000;
  *(_DWORD *)&this->m_szTexture[72] = 1000;
  v3 = *((_DWORD *)this + 774);
  this->m_szTexture[58] = -58;
  this->m_szTexture[57] = 116;
  this->m_szTexture[56] = 36;
  v19 = 310;
  v18 = 350;
  v20 = 440;
  v21 = 322;
  (*(void (**)(char *, int, int *, Actor *))(v3 + 16))((char *)this + 3096, -5570049, &v18, this);
  ((UIWnd *)(UIWnd **)this + 774)->GetChildCount(aPal3Timenotefi_96_0, *((_BYTE *)this + 3492));
  ((UIWnd *)(UIWnd **)this + 774)->GetChildAt(off_60154C, *((_BYTE *)this + 3492));
  sub_43FD90((float *)this + 774, 2);
  ((UIWnd *)((char *)this + 3096))->GetWidth(2);
  ((UIWnd *)((char *)this + 3096))->SetFrameRate(2);
  ((UIWnd *)((char *)this + 3096))->GetHeight(2);
  ((UIWnd *)((char *)this + 3096))->GetPosition(1);
  *((_DWORD *)this + 827) = 1;
  v13 = (float)*(int *)&this->m_szTexture[72];
  ((UIWnd *)((char *)this + 3096))->FindChild(v13);
  v14 = (float)*(int *)&this->m_szTexture[68];
  ((UIWnd *)((char *)this + 3096))->FindChildByName(v14);
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
  ((UIWnd *)((char *)this + 3340))->SetShow(0);
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
  ((UIWnd *)((char *)this + 3340))->GetChild((int)&id);
  a3[1] = 250;
  a3[0] = 300;
  a3[2] = 500;
  a3[3] = 370;
  ((UIItem *)&this->m_szTexture[80])->Create(-5569793, (int)a3);
  v6 = *(_DWORD *)&this->m_szTexture[164] + 22;
  *(_DWORD *)&this->m_szTexture[176] = *(_DWORD *)&this->m_szTexture[160] + 6;
  v7 = *(_DWORD *)&this->m_szTexture[172];
  *(_DWORD *)&this->m_szTexture[180] = v6;
  v8 = *(_DWORD *)&this->m_szTexture[168] - 6;
  *(_DWORD *)&this->m_szTexture[188] = v7 - 38;
  *((_DWORD *)this + 426) = 0;
  *((_DWORD *)this + 427) = 16;
  *(_DWORD *)&this->m_szTexture[184] = v8;
  ((UIWnd *)((char *)this + 816))->GetRect(&this->m_szTexture[176]);
  ((UIItem *)&this->m_szTexture[80])->SetData(31);
  this->m_szTexture[76] = 0;
  this->m_szTexture[64] = 1;
  this->m_szTexture[65] = 0;
  v24[1] = 200;
  v24[0] = 250;
  v24[2] = 550;
  v24[3] = 328;
  ((UIItem *)(UIItem *)this + 1728)->Create(-5520641, (int)v24);
  ((UIItem *)(UIItem *)this + 1728)->SetData(31);
  v9 = *((_DWORD *)this + 452);
  v10 = *((_DWORD *)this + 454);
  *((_DWORD *)this + 457) = *((_DWORD *)this + 453) + 26;
  *((_DWORD *)this + 456) = v9 + 6;
  v11 = *((_DWORD *)this + 455) - 38;
  *((_DWORD *)this + 768) = 0;
  *((_DWORD *)this + 769) = 20;
  *((_DWORD *)this + 458) = v10 - 6;
  *((_DWORD *)this + 459) = v11;
  ((UIWnd *)(UIWnd *)this + 26)->GetRect((_DWORD *)this + 456);
  ((UIWnd *)(UIWnd *)this + 26)->SetEnable(byte_DDAD3C, 0);
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

  if ( this->m_szTexture[76] )
    return ((UIWnd *)this)->HitTest(a2, a3);
  if ( !this->m_szTexture[65] && sub_4A1CF0((_DWORD *)this + 432) == 2 )
    this->m_szTexture[65] = 1;
  sprintf(&this->m_name[52], "%d/%d", (int)*((float *)this + 813), *(_DWORD *)&this->m_szTexture[72]);
  ((UIWnd *)((char *)this + 3340))->SetEnable(&this->m_name[52], 1);
  if ( this->m_szTexture[52] )
  {
    v5 = *(_DWORD *)&this->m_szTexture[60];
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
      v9 = this->m_szTexture[53];
      this->m_szTexture[64] = 0;
      if ( v9 )
      {
        v10 = this->m_szTexture[59] + 20;
        this->m_szTexture[59] = v10;
        if ( v10 == -1 )
        {
          this->m_szTexture[59] = -1;
          this->m_szTexture[53] = 0;
        }
      }
      else
      {
        v11 = this->m_szTexture[59];
        this->m_szTexture[59] = v11 - 20;
        if ( v11 == 20 )
        {
          this->m_szTexture[59] = 0;
          this->m_szTexture[53] = 1;
        }
      }
    }
    else
    {
      *(_DWORD *)(v5 + 4) = v7;
      *(_BYTE *)(v5 + 8) = 0;
      this->m_szTexture[52] = 0;
      this->m_szTexture[64] = 1;
      this->m_szTexture[59] = -1;
    }
  }
  this->m_szTexture[76] = sub_4A1CF0(&this->m_szTexture[80]) == 2;
  return ((UIWnd *)this)->HitTest(a2, a3);
}

// 0x00536A40
// attributes: thunk
int Actor::GetDefaultFOV2_thunk()
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
int Actor::GetDefaultDist2_thunk()
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
  unsigned int *m_dwMatMsg; // ebx
  char *v5; // edi
  unsigned int v6; // kr04_4
  int v7; // eax
  unsigned int v8; // esi
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  gbActor *v13; // ecx
  char *m_szTexture; // esi
  gbActor *v15; // ebp
  gbActor *m_pact; // [esp-4h] [ebp-30h]
  struct gbNodeMsgObj v17; // [esp+10h] [ebp-1Ch] BYREF
  int v18; // [esp+28h] [ebp-4h]

  m_dwMatMsg = (unsigned int *)this->m_dwMatMsg;
  if ( !strcmp(name, (const char *)this->m_dwMatMsg) )
    return 1;
  v6 = strlen(name) + 1;
  v5 = (char *)&name[v6];
  qmemcpy(m_dwMatMsg, name, 4 * (v6 >> 2));
  qmemcpy(&m_dwMatMsg[v6 >> 2], &v5[4 * (v6 >> 2) - v6], v6 & 3);
  _strlwr((char *)m_dwMatMsg);
  v7 = *(_DWORD *)this->_pad_0004;
  v8 = 0;
  if ( v7 && (unsigned int)((*(_DWORD *)&this->_pad_0004[4] - v7) >> 2) > 1 )
  {
    this->m_pact = 0;
    v9 = gbCrc32Compute((const char *)m_dwMatMsg);
    while ( 1 )
    {
      v10 = *(_DWORD *)this->_pad_0004;
      if ( !v10 || v8 >= (*(_DWORD *)&this->_pad_0004[4] - v10) >> 2 )
        break;
      if ( sub_5370E0(v9, *(_DWORD *)(v10 + 4 * v8)) )
      {
        this->m_pact = *(gbActor **)(*(_DWORD *)this->_pad_0004 + 4 * v8);
        break;
      }
      ++v8;
    }
  }
  m_pact = (gbActor *)this->m_pact;
  v11 = gbCrc32Compute((const char *)m_dwMatMsg);
  v12 = sub_5370E0(v11, (int)m_pact);
  v13 = (gbActor *)this->m_pact;
  if ( !v13 || !v12 )
    return 0;
  v13->GotoAction((char *)m_dwMatMsg, 0);
  while ( ((gbVisNode *)this->m_pact)->PopMessage(&v17) )
    ;
  m_szTexture = (char *)this->m_szTexture;
  if ( this->m_szTexture[0] )
  {
    ((OpenBaseFile *)&name)->OpenBaseFile();
    v15 = (gbActor *)this->m_pact;
    v18 = 0;
    (*(void (**)(gbActorDef *, char *))(*(_DWORD *)v15->pBody + 60))(v15->pBody, m_szTexture);
    v18 = -1;
    ((OpenNULLFile *)&name)->OpenNULLFile();
  }
  return 1;
}

// 0x00536C50
int Actor::CompareAction(int actionIdx, int a3)
{
  if ( !strcmp((&off_570904)[actionIdx], (const char *)this->m_dwMatMsg) )
    return 1;
  else
    return this->LoadAction((&off_570904)[actionIdx]);
}

// 0x00536CC0
unsigned int Actor::GetAnimDuration(int animId)
{
  return ((gbActor *)this->m_pact)->GetActionDuration((char *)animId);
}

// 0x00536CE0
void Actor::EnableTransition(int a2, int a3)
{
  ((gbActor *)this->m_pact)->EnableActionTransMtl((char *)a2, a3);
}

// 0x00536D00
void Actor::SetTimeScale(float scale)
{
  ((gbVisNode *)this->m_pact)->SetTimeScale(scale);
}

// 0x00536D20
void * Actor::LoadModel()
{
  int v2; // esi
  gbActor *ActorFile; // eax
  gbActor **v4; // eax
  gbActor **v5; // esi
  int v6; // edx
  unsigned int v7; // ecx
  int v8; // eax
  int v9; // eax
  _DWORD *v10; // edi
  _DWORD *v11; // ebp
  int v12; // eax
  gbActor **v13; // ecx
  gbActor **i; // eax
  int v16; // [esp+10h] [ebp-11Ch] BYREF
  OpenBaseFile v17; // [esp+14h] [ebp-118h] BYREF
  void *v18; // [esp+18h] [ebp-114h]
  char Buffer[260]; // [esp+1Ch] [ebp-110h] BYREF
  int v20; // [esp+128h] [ebp-4h]
  const char *v21; // [esp+130h] [ebp+4h]

  this->UpdateAllActions();
  strcpy(this->m_name, v21);
  ((OpenBaseFile *)&v17)->OpenBaseFile();
  v2 = 0;
  v20 = 0;
  sprintf(Buffer, "role\\%s\\%s.ini", this->m_name, this->m_name);
  if ( (int)g_pVFileSys->FileExistNum(Buffer) > 0 )
  {
    ActorFile = (gbActor *)dword_BFDA64->LoadActorFile(Buffer);
    this->m_pact = ActorFile;
    if ( ActorFile )
    {
      v4 = *(gbActor ***)&this->_pad_0004[4];
      v5 = v4;
      if ( (*(_DWORD *)&this->_pad_0004[8] - (int)v4) >> 2 )
      {
        sub_5374E0(v4, v4, v4 + 1);
        sub_537510(
          *(_DWORD **)&this->_pad_0004[4],
          (_DWORD *)(1 - ((*(_DWORD *)&this->_pad_0004[4] - (int)v5) >> 2)),
          &this->m_pact);
        v13 = *(gbActor ***)&this->_pad_0004[4];
        for ( i = v5; i != v13; ++i )
          *i = this->m_pact;
        *(_DWORD *)&this->_pad_0004[4] += 4;
      }
      else
      {
        v6 = *(_DWORD *)this->_pad_0004;
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
        v11 = (_DWORD *)sub_5374E0(*(_DWORD **)this->_pad_0004, v5, v10);
        sub_537510(v11, (_DWORD *)1, &this->m_pact);
        sub_5374E0(v5, *(_DWORD **)&this->_pad_0004[4], v11 + 1);
        v18 = (void *)*(void **)this->_pad_0004;
        operator delete(v18);
        *(_DWORD *)&this->_pad_0004[8] = &v10[v16];
        v12 = sub_5372B0(this);
        *(_DWORD *)this->_pad_0004 = v10;
        *(_DWORD *)&this->_pad_0004[4] = &v10[v12 + 1];
      }
    }
  }
  else
  {
    do
    {
      sprintf(Buffer, "role\\%s\\%02d.ini", this->m_name, v2);
      v16 = 0;
      if ( g_pVFileSys->FileExistNum(Buffer) )
      {
        v16 = (int)dword_BFDA64->LoadActorFile(Buffer);
        if ( !v16 )
          goto LABEL_21;
        sub_5372D0((int)this, *(_DWORD **)&this->_pad_0004[4], 1u, &v16);
      }
      ++v2;
    }
    while ( v2 < 10 );
    this->m_pact = **(gbActor ***)this->_pad_0004;
  }
LABEL_21:
  v20 = -1;
  return ((OpenNULLFile *)&v17)->OpenNULLFile();
}

// 0x00536FB0
int Actor::QueryState()
{
  return (*(int (**)(gbActor *))(*(_DWORD *)this->m_pact + 20))(this->m_pact);
}

// 0x00536FC0
int Actor::DispatchAction(int actionId)
{
  return (*(int (**)(gbActor *, int))(*(_DWORD *)this->m_pact + 16))(this->m_pact, actionId);
}

// 0x00536FD0
int Actor::PlayAction(int actionId)
{
  return (*(int (**)(gbActorDef *, int, gbActor *))(*(_DWORD *)this->m_pact->pBody + 28))(
           this->m_pact->pBody,
           actionId,
           this->m_pact);
}

// 0x00536FF0
int Actor::UpdateAllActions()
{
  unsigned int i; // edi
  int v3; // eax
  int result; // eax
  unsigned int *m_dwMatMsg; // esi

  for ( i = 0; ; ++i )
  {
    v3 = *(_DWORD *)this->_pad_0004;
    if ( !v3 || i >= (*(_DWORD *)&this->_pad_0004[4] - v3) >> 2 )
      break;
    dword_BFDA64->DestroyActor(*(struct gbActor **)(v3 + 4 * i));
  }
  result = *(_DWORD *)&this->_pad_0004[4];
  *(_DWORD *)&this->_pad_0004[4] = *(_DWORD *)this->_pad_0004;
  this->m_pact = 0;
  m_dwMatMsg = (unsigned int *)this->m_dwMatMsg;
  *m_dwMatMsg = 0;
  m_dwMatMsg[1] = 0;
  return result;
}

// 0x005371B0
void Actor::SetVisible(int bVisible)
{
  int v3; // eax
  int v4; // eax
  gbActor *v5; // ecx
  char *m_szTexture; // esi
  gbActor *v7; // ebx
  gbActor *m_pact; // [esp+0h] [ebp-2Ch]
  struct gbNodeMsgObj v9; // [esp+10h] [ebp-1Ch] BYREF
  int v10; // [esp+28h] [ebp-4h]
  char *v11; // [esp+34h] [ebp+8h]
  char *v12; // [esp+38h] [ebp+Ch]

  if ( bVisible )
  {
    strcpy((char *)this->m_dwMatMsg, (const char *)bVisible);
    _strlwr((char *)this->m_dwMatMsg);
  }
  m_pact = (gbActor *)this->m_pact;
  v3 = gbCrc32Compute((const char *)this->m_dwMatMsg);
  v4 = sub_5370E0(v3, (int)m_pact);
  v5 = (gbActor *)this->m_pact;
  if ( v5 && v4 )
  {
    v5->GotoAction((char *)this->m_dwMatMsg, v11, v12);
    while ( ((gbVisNode *)this->m_pact)->PopMessage(&v9) )
      ;
    m_szTexture = (char *)this->m_szTexture;
    if ( this->m_szTexture[0] )
    {
      ((OpenBaseFile *)&bVisible)->OpenBaseFile();
      v7 = (gbActor *)this->m_pact;
      v10 = 0;
      (*(void (**)(gbActorDef *, char *))(*(_DWORD *)v7->pBody + 60))(v7->pBody, m_szTexture);
      v10 = -1;
      ((OpenNULLFile *)&bVisible)->OpenNULLFile();
    }
  }
}
