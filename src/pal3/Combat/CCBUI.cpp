#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/CCBStageScene.h"
#include "pal3/gen/CCBSystem.h"

// Forward declarations for unnamed functions
int sub_4DC650(...);
int sub_4DF2F0(...);
int sub_4E2C50(...);
int sub_4E30E0(...);
int sub_4E3780(...);
int sub_4E3A20(...);
int sub_4E3D90(...);
int sub_4E40B0(...);
int sub_4E4570(...);
int sub_4E4A80(...);
int sub_4E4D50(...);
int sub_4E4D70(...);
int sub_4E4F00(...);
int sub_4E50B0(...);
int sub_4E5110(...);
int sub_4E5170(...);
int sub_4E5B20(...);
int sub_4E5E00(...);
int sub_504240(...);

// Unnamed globals (extern)
extern char aStopped[];
extern unsigned char byte_17A94E4;
extern unsigned char byte_17A9924;
extern unsigned char byte_17A9925;
extern unsigned char byte_17A9926;
extern unsigned char byte_17A9930;
extern unsigned char byte_17A9931;
extern unsigned char byte_17A9932;
extern unsigned char byte_17A9933;
extern unsigned char byte_17A9934;
extern unsigned char byte_17A9935;
extern unsigned char byte_17A9936;
extern unsigned char byte_17A9937;
extern unsigned char byte_17A9938;
extern unsigned char byte_17A9944;
extern unsigned char byte_17A9945;
extern unsigned char byte_17A9946;
extern unsigned char byte_17A9947;
extern unsigned char byte_17A9948;
extern unsigned char byte_17A9949;
extern unsigned char byte_17A994A;
extern unsigned char byte_17A994B;
extern unsigned char byte_17A994C;
extern unsigned char byte_17A994D;
extern unsigned char byte_17A994E;
extern unsigned char byte_5D87F0;
extern unsigned char byte_5D8808;
extern unsigned char byte_5D8848;
extern unsigned char byte_5D8864;
extern unsigned char byte_5D8884;
extern int dword_17A990C;
extern float flt_17A95F8;

// 0x004DC560
int CCBUI::GetState()
{
  int result; // eax

  LOBYTE(result) = BYTE1(this->m_wndcolor.Red);
  if ( !(_BYTE)result )
  {
    BYTE1(this->m_wndcolor.Red) = 1;
    return sub_4DC650((CCBSystem **)this, (CCBSystem *)sub_4DF2F0, 0, 0, 0, 0, 0, 0, (CCBSystem *)0xFFFFFFFF, 0, 0);
  }
  return result;
}

// 0x004DC5C0
int CCBUI::SetParam(int a2, int a3)
{
  int result; // eax
  __int32 v4; // [esp+10h] [ebp+Ch]

  result = a2;
  this->m_wndcolor.Color = a3;
  LOBYTE(this->m_rect.left) = 1;
  this->m_wndcolor.Alpha = a2;
  this->m_id = v4;
  switch ( a2 )
  {
    case 259:
    case 260:
    case 261:
    case 262:
    case 265:
    case 267:
      this->m_wndcolor.Alpha = a2;
      break;
    default:
      return result;
  }
  return result;
}

// 0x004E04C0
int CCBUI::Update()
{
  int result; // eax

  ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->ProcAI(flt_17A95F8);
  if ( *(_BYTE *)(this->m_fontcolor.ColorQuadFmt + 132) != byte_17A9924 )
    ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->SetRenderFlag(byte_17A9924);
  *(_BYTE *)(this->m_fontcolor.ColorQuadFmt + 134) = byte_5D87F0;
  if ( byte_17A9926 )
  {
    CCBSystem::GetRenderFlag();
    byte_17A9926 = 0;
  }
  this->UpdateInput();
  this->UpdateDisplay();
  this->UpdateAnimation();
  LOBYTE(result) = this->UpdateState();
  return result;
}

// 0x004E0690
char CCBUI::UpdateInput()
{
  char result; // al
  int v3; // eax
  char Buffer[128]; // [esp+8h] [ebp-80h] BYREF

  result = byte_17A9930;
  if ( byte_17A9930 )
  {
    ((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(this->m_fontcolor.ColorQuadFmt + 20) + 20))->Update();
    ((CCBStageScene *)*(CCBStageScene **)(*(_DWORD *)(this->m_fontcolor.ColorQuadFmt + 20) + 20))->ShowRoleIndex();
    result = ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->CreateObj(byte_5D8864, 0, 0x40u);
    byte_17A9930 = 0;
  }
  if ( byte_17A9932 )
    byte_17A9932 = 0;
  if ( byte_17A9931 )
    byte_17A9931 = 0;
  if ( byte_17A9933 )
  {
    v3 = sub_504240(*(float **)(*(_DWORD *)(this->m_fontcolor.ColorQuadFmt + 20) + 12));
    sprintf(Buffer, &byte_5D8848, v3);
    result = ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->CreateObj(Buffer, 0, 0x40u);
    byte_17A9933 = 0;
  }
  return result;
}

// 0x004E0740
char CCBUI::UpdateDisplay()
{
  int ColorQuadFmt; // eax
  int v3; // edi
  int i; // esi
  CCBRoleState *v5; // ecx
  int v6; // edi
  int v7; // esi
  CCBRoleState *v8; // ecx
  HWND DlgItem; // eax

  LOBYTE(ColorQuadFmt) = byte_17A9925;
  if ( byte_17A9925 )
  {
    v3 = 0;
    for ( i = 0; i < 5; ++i )
    {
      ColorQuadFmt = this->m_fontcolor.ColorQuadFmt;
      v5 = (CCBRoleState *)*(CCBRoleState **)(this->m_fontcolor.ColorQuadFmt + 16);
      if ( v5->m_Role[i].bValid )
      {
        ColorQuadFmt = v5->InitUI(v3);
        *(_BYTE *)(ColorQuadFmt + 837) = 0;
      }
      ++v3;
    }
    byte_17A9924 = 0;
    byte_17A9925 = 0;
  }
  else
  {
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      v8 = (CCBRoleState *)*(CCBRoleState **)(this->m_fontcolor.ColorQuadFmt + 16);
      if ( v8->m_Role[v7].bValid )
      {
        ColorQuadFmt = v8->InitUI(v6);
        if ( !*(_BYTE *)(ColorQuadFmt + 837) )
          break;
      }
      ++v7;
      ++v6;
      if ( v7 >= 5 )
      {
        if ( !byte_17A9924 )
        {
          byte_17A9924 = 1;
          sprintf(byte_17A94E4, "%s", byte_5D8884);
          DlgItem = GetDlgItem((HWND)g_Input.KeyInfo[176].Data, 1004);
          SendMessageA(DlgItem, 0xCu, 0, (LPARAM)byte_17A94E4);
          LOBYTE(ColorQuadFmt) = ((CCBSystem *)this->m_fontcolor.ColorQuadFmt)->ProcFlee(byte_17A9924);
        }
        return ColorQuadFmt;
      }
    }
  }
  return ColorQuadFmt;
}

// 0x004E0820
char CCBUI::UpdateAnimation()
{
  char result; // al

  result = byte_17A9934;
  if ( byte_17A9934 )
  {
    byte_17A9934 = 0;
    result = sub_4E2C50(this);
  }
  if ( byte_17A9935 )
  {
    byte_17A9935 = 0;
    result = sub_4E30E0(&this->m_fontcolor.ColorQuadFmt);
  }
  if ( byte_17A9936 )
  {
    byte_17A9936 = 0;
    result = sub_4E3780(this);
  }
  if ( byte_17A9938 )
  {
    byte_17A9938 = 0;
    result = sub_4E3D90((CCBRoleState **)this);
  }
  if ( byte_17A9937 )
  {
    byte_17A9937 = 0;
    result = sub_4E3A20((CCBRoleState **)this);
  }
  if ( byte_17A9944 )
  {
    byte_17A9944 = 0;
    result = sub_4E40B0((CCBRoleState **)this);
  }
  if ( byte_17A9945 )
  {
    byte_17A9945 = 0;
    result = sub_4E4570(this);
  }
  if ( byte_17A9946 )
  {
    byte_17A9946 = 0;
    result = sub_4E4A80(this);
  }
  if ( byte_17A9948 )
  {
    byte_17A9948 = 0;
    result = sub_4E4D70(this);
  }
  if ( byte_17A9947 )
  {
    byte_17A9947 = 0;
    result = sub_4E4D50(this);
  }
  if ( byte_17A994A )
  {
    byte_17A994A = 0;
    result = (unsigned __int8)sub_4E50B0();
  }
  if ( byte_17A9949 )
  {
    byte_17A9949 = 0;
    result = sub_4E4F00(this);
  }
  if ( byte_17A994B )
  {
    byte_17A994B = 0;
    result = sub_4E5170();
  }
  if ( byte_17A994C )
  {
    byte_17A994C = 0;
    result = sub_4E5110();
  }
  if ( byte_17A994D )
  {
    byte_17A994D = 0;
    result = sub_4E5B20(&this->m_fontcolor.ColorQuadFmt);
  }
  if ( byte_17A994E )
  {
    byte_17A994E = 0;
    return sub_4E5E00(&this->m_fontcolor.ColorQuadFmt);
  }
  return result;
}

// 0x004E0980
char CCBUI::UpdateState()
{
  char result; // al
  int v2; // esi
  HWND DlgItem; // edi

  result = dword_17A990C;
  v2 = *(_DWORD *)(*(_DWORD *)(this->m_fontcolor.ColorQuadFmt + 20) + 16);
  if ( dword_17A990C == 4 )
  {
    DlgItem = GetDlgItem((HWND)g_Input.KeyInfo[176].HoldTime, 1201);
    result = *(_BYTE *)(v2 + 430012);
    if ( result )
    {
      byte_5D8808 = 1;
      sprintf(byte_17A94E4, "%03d-%03d", *(_DWORD *)(v2 + 430032), *(_DWORD *)(v2 + 430036));
      return SendMessageA(DlgItem, 0xCu, 0, (LPARAM)byte_17A94E4);
    }
    else if ( byte_5D8808 == 1 )
    {
      byte_5D8808 = 0;
      sprintf(byte_17A94E4, aStopped);
      return SendMessageA(DlgItem, 0xCu, 0, (LPARAM)byte_17A94E4);
    }
  }
  return result;
}

// 0x00519200
int CCBUI::ShowDialogWindow()
{
  int v2; // esi
  _BYTE *v3; // edi
  int result; // eax

  v2 = 0;
  v3 = (char *)&this->m_pItemWindow + 2;
  do
  {
    if ( *(v3 - 2) == 1 && *v3 == 1 )
      LOBYTE(result) = this->ShowAIWindow(v2);
    ++v2;
    v3 += 72;
  }
  while ( v2 < 20 );
  return result;
}
