#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ARC_PlayerAtt.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];

// 0x004A12F0
int ARC_PlayerAtt::Refresh()
{
  ((UITextArea *)&this->Remark[106])->InitAfterClear();
  sub_4422E0(&this->Remark[298]);
  sub_4422E0(&this->Remark[450]);
  *(_DWORD *)&this->name[8] = 90;
  *(_DWORD *)&this->name[12] = 26;
  UIScene::GetSys();
  UIScene::GetSys();
  *(_DWORD *)&this->byMagicUseTime[2][4] = 0;
  *(_DWORD *)&this->byMagicUseTime[4][0] = -1;
  *(_DWORD *)&this->byMagicUseTime[4][4] = 208;
  *(_DWORD *)&this->byMagicUseTime[5][2] = 103;
  this->byMagicUseTime[6][0] = 0;
  this->byMagicUseTime[6][1] = 0;
  this->byMagicLevel[1][2] = 0;
  *(_DWORD *)&this->byMagicLevel[0][4] = 0;
  *(_DWORD *)&this->byMagicLevel[0][0] = 0;
  *(_DWORD *)&this->Remark[62] = 0;
  return (int)this;
}

// 0x004A16C0
int ARC_PlayerAtt::Create(int id, int nVal)
{
  int v4; // edx
  char *v5; // edi
  int v6; // edx
  char *v7; // ebp
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // ebp
  int v15; // ecx
  int v16; // edx
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ebx
  int v24; // kr04_4
  int v25; // eax
  int v26; // edx
  int lv; // eax
  int v28; // edx
  int v29; // eax
  char Buffer[253]; // [esp+0x34] [ebp-0x300] BYREF
  __int16 v32; // [esp+0x131] [ebp-0x203]
  char v33; // [esp+0x133] [ebp-0x201]
  char v34[253]; // [esp+0x134] [ebp-0x200] BYREF
  __int16 v35; // [esp+0x231] [ebp-0x103]
  char v36; // [esp+0x233] [ebp-0x101]
  char v37[253]; // [esp+0x234] [ebp-0x100] BYREF
  __int16 v38; // [esp+0x331] [ebp-0x3]
  char v39; // [esp+0x333] [ebp-0x1]
  int parent; // [esp+0x340] [ebp+0xC]
  int v41; // [esp+0x344] [ebp+0x10]
  int v42; // [esp+0x348] [ebp+0x14]

  ((PalScript *)this)->Create(id, (tagRECT *)nVal, parent);
  *(_DWORD *)&this->Remark[66] = parent;
  *(_DWORD *)&this->byMagicUseTime[3][2] = v41;
  memset(Buffer, 0, sizeof(Buffer));
  memset(v34, 0, sizeof(v34));
  v32 = 0;
  v33 = 0;
  v37[0] = 0;
  v35 = 0;
  v36 = 0;
  *(_DWORD *)&this->Remark[70] = id;
  memset(&v37[1], 0, 0xFCu);
  v38 = 0;
  v4 = *(_DWORD *)nVal;
  v39 = 0;
  v5 = &this->Remark[74];
  *(_DWORD *)&this->Remark[74] = v4;
  *(_DWORD *)&this->Remark[78] = *(_DWORD *)(nVal + 4);
  *(_DWORD *)&this->Remark[82] = *(_DWORD *)(nVal + 8);
  *(_DWORD *)&this->Remark[86] = *(_DWORD *)(nVal + 12);
  sprintf(Buffer, byte_5967B0, "UI\\GameMainUI\\MUIDialog\\Normal\\DlgBackground.tga");
  sprintf(v34, byte_5967B0, "UI\\GameMainUI\\MUIDialog\\Normal\\Yes");
  sprintf(v37, byte_5967B0, "UI\\GameMainUI\\MUIDialog\\Normal\\No");
  v6 = *(_DWORD *)&this->Remark[78];
  v7 = &this->Remark[90];
  *(_DWORD *)&this->Remark[94] = v6 + 6;
  v8 = *(_DWORD *)&this->Remark[74];
  *(_DWORD *)&this->Remark[90] = v8 + 6;
  v9 = *(_DWORD *)&this->byMagicUseTime[3][2];
  if ( !v9 )
  {
    *(_DWORD *)&this->Remark[82] = v8 + 308;
    *(_DWORD *)&this->Remark[86] = v6 + 109;
    (*(void ( **)(char *, int, char *, ARC_PlayerAtt *))(*(_DWORD *)&this->Remark[298] + 16))(
      &this->Remark[298],
      655360,
      &this->Remark[74],
      this);
    ((UIStatic *)&this->Remark[298])->CreateFromTemplate();
    (**(void ( ***)(char *, _DWORD))&this->Remark[298])(&this->Remark[298], 0);
    sub_445FA0(&this->Remark[298]);
    v22 = *(_DWORD *)&this->name[12];
    v23 = *(_DWORD *)&this->Remark[86] - v22 - 6;
    v24 = *(_DWORD *)&this->name[8];
    *(_DWORD *)&this->name[20] = v23;
    v25 = *(_DWORD *)v5 + 154 - v24 / 2;
    v26 = *(_DWORD *)&this->name[8];
    *(_DWORD *)&this->name[16] = v25;
    *(_DWORD *)&this->name[24] = v26 + v25;
    lv = this->lv;
    *(_DWORD *)&this->name[28] = v22 + v23;
    (*(void ( **)(int *, int, char *, ARC_PlayerAtt *, char *, _DWORD, int))(lv + 28))(
      &this->lv,
      655362,
      &this->name[16],
      this,
      v34,
      0,
      v42);
    sub_445FA0(&this->lv);
    (*(void ( **)(int *, _DWORD))this->lv)(&this->lv, 0);
    LOBYTE(this->haogan[2]) = 0;
    v28 = *(_DWORD *)&this->Remark[86] - 38;
    *(_DWORD *)&this->Remark[98] = *(_DWORD *)&this->Remark[82] - 6;
    *(_DWORD *)&this->Remark[102] = v28;
    goto LABEL_7;
  }
  v10 = v9 - 2;
  if ( !v10 )
  {
    *(_DWORD *)&this->Remark[86] = v6 + 109;
    v12 = *(_DWORD *)&this->Remark[298];
    *(_DWORD *)&this->Remark[82] = v8 + 308;
    (*(void ( **)(char *, int, char *, ARC_PlayerAtt *))(v12 + 16))(
      &this->Remark[298],
      655360,
      &this->Remark[74],
      this);
    ((UIStatic *)&this->Remark[298])->CreateFromTemplate();
    (**(void ( ***)(char *, _DWORD))&this->Remark[298])(&this->Remark[298], 0);
    sub_445FA0(&this->Remark[298]);
    v13 = *(_DWORD *)&this->name[12];
    v14 = *(_DWORD *)&this->name[8];
    v15 = *(_DWORD *)&this->Remark[86] - v13 - 6;
    v16 = *(_DWORD *)v5 + 26;
    *(_DWORD *)&this->name[20] = v15;
    *(_DWORD *)&this->name[24] = v16 + v14;
    *(_DWORD *)&this->name[16] = v16;
    v17 = this->lv;
    *(_DWORD *)&this->name[28] = v13 + v15;
    (*(void ( **)(int *, int, char *, ARC_PlayerAtt *, char *, _DWORD, int))(v17 + 28))(
      &this->lv,
      655362,
      &this->name[16],
      this,
      v34,
      0,
      v42);
    sub_445FA0(&this->lv);
    (*(void ( **)(int *, _DWORD))this->lv)(&this->lv, 0);
    LOBYTE(this->haogan[2]) = 0;
    v18 = *(_DWORD *)&this->name[8];
    v19 = this->currolevalue[1];
    v20 = *(_DWORD *)&this->Remark[82] - v18 - 26;
    *(_DWORD *)&this->name[16] = v20;
    *(_DWORD *)&this->name[24] = v18 + v20;
    (*(void ( **)(int *, int, char *, ARC_PlayerAtt *, char *, _DWORD, int))(v19 + 28))(
      &this->currolevalue[1],
      655363,
      &this->name[16],
      this,
      v37,
      0,
      v42);
    sub_445FA0(&this->currolevalue[1]);
    (*(void ( **)(int *, _DWORD))this->currolevalue[1])(&this->currolevalue[1], 0);
    LOBYTE(this->dwMagicID[0][3]) = 0;
    v21 = *(_DWORD *)&this->Remark[86] - 38;
    *(_DWORD *)&this->Remark[98] = *(_DWORD *)&this->Remark[82] - 6;
    *(_DWORD *)&this->Remark[102] = v21;
LABEL_7:
    v7 = &this->Remark[90];
    goto LABEL_8;
  }
  if ( v10 == 1 )
  {
    ((UINote *)&this->Remark[106])->Create(655360, (int)&this->Remark[74], (int)this, "UI\\Flex\\Note");
    (**(void ( ***)(char *, _DWORD))&this->Remark[106])(&this->Remark[106], 0);
    sub_445FA0(&this->Remark[106]);
    v11 = *(_DWORD *)&this->Remark[86] - 6;
    *(_DWORD *)&this->Remark[98] = *(_DWORD *)&this->Remark[82] - 6;
    *(_DWORD *)&this->Remark[102] = v11;
  }
LABEL_8:
  v29 = *(_DWORD *)&this->Remark[450];
  *(_DWORD *)&this->byMagicUseTime[6][4] = 0;
  *(_DWORD *)&this->byMagicUseTime[7][2] = 0;
  this->byMagicLevel[2][1] = 1;
  (*(void ( **)(char *, int, char *, ARC_PlayerAtt *))(v29 + 16))(&this->Remark[450], 655360, v7, this);
  sub_445FA0(&this->Remark[450]);
  ((UIScene *)&this->Remark[450])->SetShow(0);
  return (**(int ( ***)(char *, _DWORD))&this->Remark[450])(&this->Remark[450], 0);
}
