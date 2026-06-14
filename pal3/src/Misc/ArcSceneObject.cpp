#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ArcSceneObject.h"

// Unnamed globals (extern)
extern char byte_1010101;
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DD9E3C[256];
extern CHAR byte_DD9F3C[256];
extern CHAR byte_DDA03C[256];
extern CHAR byte_DDA13C[256];
extern CHAR byte_DDA23C[256];
extern CHAR byte_DDA33C[256];
extern CHAR byte_DDA43C[256];
extern CHAR byte_DDA53C[256];
extern CHAR byte_DDA63C[256];
extern CHAR byte_DDA73C[512];
extern int dword_DC413C;
extern int dword_DC423C;
extern int dword_DC433C;
extern int dword_DD533C;
extern int dword_DD543C;

// 0x00458A20
CHAR * ArcSceneObject::FormatDescription(int nVal)
{
  __int16 v2; // ax
  __int16 v3; // ax
  __int16 v4; // ax
  __int16 v5; // ax
  __int16 v6; // ax
  __int16 v7; // ax
  __int16 v8; // ax
  __int16 v9; // ax
  __int16 v10; // ax
  __int16 v11; // ax
  __int16 v12; // ax
  __int16 v13; // si
  int v14; // esi
  char *v15; // edi
  int v16; // esi
  CHAR *v17; // edi
  char *v18; // [esp+0x8] [ebp-0x168]
  unsigned __int8 v19; // [esp+0xC] [ebp-0x164]
  char *v20; // [esp+0x10] [ebp-0x160]
  char *v21; // [esp+0x14] [ebp-0x15C]
  char *v22; // [esp+0x18] [ebp-0x158]
  CHAR String2[240]; // [esp+0x1C] [ebp-0x154] BYREF
  char Buffer[100]; // [esp+0x10C] [ebp-0x64] BYREF

  if ( !nVal )
    return 0;
  memset(String2, 0, sizeof(String2));
  memset(Buffer, 0, sizeof(Buffer));
  v20 = byte_1010101;
  v21 = byte_1010101;
  v22 = byte_1010101;
  v18 = byte_1010101;
  v19 = (unsigned __int8)byte_1010101;
  memset(&String1, 0, 0x100u);
  if ( *(int *)(nVal + 8) <= 0 )
    LOBYTE(v18) = 0;
  else
    sprintf(Buffer, "%s ", (const char *)g_bSlotFlag);
  if ( *(int *)(nVal + 12) <= 0 )
    BYTE1(v18) = 0;
  else
    sprintf(&Buffer[20], "%s ", (const char *)&g_bSlotFlag[256]);
  if ( *(int *)(nVal + 16) <= 0 )
    BYTE2(v18) = 0;
  else
    sprintf(&Buffer[40], "%s ", (const char *)&g_bSlotFlag[512]);
  if ( *(int *)(nVal + 20) <= 0 )
    HIBYTE(v18) = 0;
  else
    sprintf(&Buffer[60], "%s ", byte_DC3F3C);
  if ( *(int *)(nVal + 24) <= 0 )
    v19 = 0;
  else
    sprintf(&Buffer[80], "%s ", byte_DC403C);
  v2 = *(_WORD *)(nVal + 606);
  if ( v2 <= 0 )
  {
    if ( v2 >= 0 )
      HIBYTE(v21) = 0;
    else
      sprintf(&String2[140], "%s%d ", (const char *)g_bSlotFlag, v2);
  }
  else
  {
    sprintf(&String2[140], "%s+%d ", (const char *)g_bSlotFlag, v2);
  }
  v3 = *(_WORD *)(nVal + 608);
  if ( v3 <= 0 )
  {
    if ( v3 >= 0 )
      LOBYTE(v22) = 0;
    else
      sprintf(&String2[160], "%s%d ", (const char *)&g_bSlotFlag[256], v3);
  }
  else
  {
    sprintf(&String2[160], "%s+%d ", (const char *)&g_bSlotFlag[256], v3);
  }
  v4 = *(_WORD *)(nVal + 610);
  if ( v4 <= 0 )
  {
    if ( v4 >= 0 )
      BYTE1(v22) = 0;
    else
      sprintf(&String2[180], "%s%d ", (const char *)&g_bSlotFlag[512], v4);
  }
  else
  {
    sprintf(&String2[180], "%s+%d ", (const char *)&g_bSlotFlag[512], v4);
  }
  v5 = *(_WORD *)(nVal + 612);
  if ( v5 <= 0 )
  {
    if ( v5 >= 0 )
      BYTE2(v22) = 0;
    else
      sprintf(&String2[200], "%s%d ", byte_DC3F3C, v5);
  }
  else
  {
    sprintf(&String2[200], "%s+%d ", byte_DC3F3C, v5);
  }
  v6 = *(_WORD *)(nVal + 614);
  if ( v6 <= 0 )
  {
    if ( v6 >= 0 )
      HIBYTE(v22) = 0;
    else
      sprintf(&String2[220], "%s%d ", byte_DC403C, v6);
  }
  else
  {
    sprintf(&String2[220], "%s+%d ", byte_DC403C, v6);
  }
  v7 = *(_WORD *)(nVal + 592);
  if ( v7 <= 0 )
  {
    if ( v7 >= 0 )
      LOBYTE(v20) = 0;
    else
      sprintf(String2, "%s%s ", (const char *)dword_DC413C, (const char *)dword_DD543C);
  }
  else
  {
    sprintf(String2, "%s%s ", (const char *)dword_DC413C, (const char *)dword_DD533C);
  }
  v8 = *(_WORD *)(nVal + 594);
  if ( v8 <= 0 )
  {
    if ( v8 >= 0 )
      BYTE1(v20) = 0;
    else
      sprintf(&String2[20], "%s%s ", (const char *)dword_DC423C, (const char *)dword_DD543C);
  }
  else
  {
    sprintf(&String2[20], "%s%s ", (const char *)dword_DC423C, (const char *)dword_DD533C);
  }
  v9 = *(_WORD *)(nVal + 596);
  if ( v9 <= 0 )
  {
    if ( v9 >= 0 )
      BYTE2(v20) = 0;
    else
      sprintf(&String2[40], "%s%s ", (const char *)dword_DC433C, (const char *)dword_DD543C);
  }
  else
  {
    sprintf(&String2[40], "%s%s ", (const char *)dword_DC433C, (const char *)dword_DD533C);
  }
  v10 = *(_WORD *)(nVal + 598);
  if ( v10 <= 0 )
  {
    if ( v10 >= 0 )
      HIBYTE(v20) = 0;
    else
      sprintf(&String2[60], "%s%s ", (const char *)&g_szRoleName0, (const char *)dword_DD543C);
  }
  else
  {
    sprintf(&String2[60], "%s%s ", (const char *)&g_szRoleName0, (const char *)dword_DD533C);
  }
  v11 = *(_WORD *)(nVal + 600);
  if ( v11 <= 0 )
  {
    if ( v11 >= 0 )
      LOBYTE(v21) = 0;
    else
      sprintf(&String2[80], "%s%s ", (const char *)&g_szRoleName1, (const char *)dword_DD543C);
  }
  else
  {
    sprintf(&String2[80], "%s%s ", (const char *)&g_szRoleName1, (const char *)dword_DD533C);
  }
  v12 = *(_WORD *)(nVal + 602);
  if ( v12 <= 0 )
  {
    if ( v12 >= 0 )
      BYTE1(v21) = 0;
    else
      sprintf(&String2[100], "%s%s ", (const char *)&g_szRoleName2, (const char *)dword_DD543C);
  }
  else
  {
    sprintf(&String2[100], "%s%s ", (const char *)&g_szRoleName2, (const char *)dword_DD533C);
  }
  v13 = *(_WORD *)(nVal + 604);
  if ( v13 <= 0 )
  {
    if ( v13 >= 0 )
      BYTE2(v21) = 0;
    else
      sprintf(&String2[120], "%s%s ", (const char *)&g_szRoleName3, (const char *)dword_DD543C);
  }
  else
  {
    sprintf(&String2[120], "%s%s ", (const char *)&g_szRoleName3, (const char *)dword_DD533C);
  }
  lstrcpyA(&String1, g_szSceneUIText);
  v14 = 0;
  v15 = Buffer;
  do
  {
    if ( *((_BYTE *)&v18 + v14) )
      lstrcatA(&String1, v15);
    ++v14;
    v15 += 20;
  }
  while ( v14 < 5 );
  v16 = 0;
  v17 = String2;
  do
  {
    if ( *((_BYTE *)&v20 + v16) )
      lstrcatA(&String1, v17);
    ++v16;
    v17 += 20;
  }
  while ( v16 < 12 );
  return &String1;
}

// 0x0049AAF0
void ArcSceneObject::ResetEquipControls()
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  float v6; // eax
  int v7; // eax
  int pnVal; // [esp+0x8] [ebp-0x10] BYREF
  int v9; // [esp+0xC] [ebp-0xC]
  int v10; // [esp+0x10] [ebp-0x8]
  int v11; // [esp+0x14] [ebp-0x4]

  ((MainEquipUI *)this)->ResetControls();
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1349, byte_DD9E3C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1352, byte_DD9F3C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1355, byte_DDA03C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1358, byte_DDA13C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1361, byte_DDA23C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1364, byte_DDA33C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1367, byte_DDA43C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1370, byte_DDA53C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1373, byte_DDA63C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 1376, byte_DDA73C);
  v2 = 0;
  while ( !*((_BYTE *)&this->subobj + v2 + 5) )
  {
    if ( ++v2 >= 5 )
      goto LABEL_6;
  }
  ((StateUI *)this)->DisplayCaption(v2);
LABEL_6:
  v9 = 62;
  pnVal = 686;
  v10 = 796;
  v11 = 157;
  this->info.param[5] = 0.0;
  v3 = 60;
  do
  {
    v4 = LODWORD(this->info.param[5]);
    if ( *((_BYTE *)&this->subobj + v4 + 5) )
    {
      ((UITitle_XJTM *)this)->Layout_49a6e0(v4, &pnVal);
      ((UITitle_XJTM *)this)->SetMonsterState2(LODWORD(this->info.param[5]), 1u);
      v3 += 122;
      v9 = v3;
      v11 = v3 + 95;
    }
    else
    {
      ((UITitle_XJTM *)this)->SetMonsterState2(v4, 0);
    }
    v5 = LODWORD(this->info.param[5]) + 1;
    LODWORD(this->info.param[5]) = v5;
  }
  while ( v5 < 5 );
  ((StateUI *)this)->UpdateScrollValues();
  this->info.param[5] = 0.0;
  while ( 1 )
  {
    v6 = this->info.param[5];
    if ( *((_BYTE *)&this->subobj + LODWORD(v6) + 5) )
      break;
    v7 = LODWORD(v6) + 1;
    LODWORD(this->info.param[5]) = v7;
    if ( v7 >= 5 )
      return;
  }
  *(&this->subobj + 3) = LODWORD(this->info.param[5]);
  ((MainEquipUI *)this)->ShowWithCursor(0);
  ((StateUI *)this)->DisplayCaption(LODWORD(this->info.param[5]));
}

// 0x005254C0
ArcSceneObject * ArcSceneObject::InitFromConfig()
{
  this->info = 0;
  lstrcpyA(this->info.name, g_szSceneUIText);
  lstrcpyA(&this->info.ctype, g_szSceneUIText);
  lstrcpyA((LPSTR)&this->info.rect.right + 2, g_szSceneUIText);
  lstrcpyA((LPSTR)&this->info.param[5], g_szSceneUIText);
  this->task.m_bCVDOver = 0;
  memset(&this->subobj + 7, 0, 0x18u);
  return this;
}

// 0x00533F50
void ArcSceneObject::UpdateOscillation(float fDelta)
{
  long double v2; // st7

  v2 = fDelta + *((float *)&this->subobj + 1);
  *((float *)&this->subobj + 1) = v2;
  if ( *(float *)&this->subobj <= fabs(v2) )
  {
    *((_BYTE *)&this->subobj + 20) = v2 <= 0.0;
    *((float *)&this->subobj + 2) = v2;
    *(&this->subobj + 1) = 0;
    this->task.m_bCVDOver = 1;
    this->info.reserve[43] = this->info.reserve[40];
    this->task.mTouchCounter = this->info.reserve[41];
    this->task.m_iState = this->info.reserve[42];
  }
}
