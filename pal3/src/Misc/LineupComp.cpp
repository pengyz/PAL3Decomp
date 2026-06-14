#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/LineupComp.h"

// Forward declarations for unnamed functions
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations

int * ctor_0x431870(int *_this); // from annotations

// Unnamed globals (extern)
extern const char * off_56BA1C;

// 0x0044B850
LineupComp::LineupComp(int thisa)
{
  ctor_0x431870((int *)this);
  LOWORD(this->m_3DRole[3].RelativePos.z) = 0;
  BYTE2(this->m_3DRole[3].RelativePos.z) = 0;
  *(_DWORD *)&this->m_3DNone[0].m_isLoadObj = 0;
  LOBYTE(this->m_3DNone[0].m_type) = 0;
  LOBYTE(this->m_3DNone[1].m_forward.y) = 0;
  LOBYTE(this->m_3DNone[3].m_rotx) = 0;
  LOBYTE(this->m_3DNone[5].m_subObj) = 0;
  LOBYTE(this->m_3DRole[1].m_dist) = 0;
  (int)this;
}

// 0x004543C0
int LineupComp::SetVisible(int thisa, unsigned __int8 pData)
{
  float *p_m_yaw; // edi
  int v5; // ebp

  (*(void ( **)(float *, _DWORD))LODWORD(this->m_3DRole[0].m_yaw))(
    &this->m_3DRole[0].m_yaw,
    (unsigned __int8)thisa);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_3DRole[1].m_yaw))(
    &this->m_3DRole[1].m_yaw,
    (unsigned __int8)thisa);
  p_m_yaw = &this->m_3DRole[2].m_yaw;
  v5 = 3;
  do
  {
    (**(void ( ***)(float *, _DWORD))p_m_yaw)(p_m_yaw, (unsigned __int8)thisa);
    p_m_yaw += 94;
    --v5;
  }
  while ( v5 );
  return (*(int ( **)(int *, _DWORD))this->m_3DNone[4].m_rotDstMode)(
           &this->m_3DNone[4].m_rotDstMode,
           (unsigned __int8)thisa);
}

// 0x00483FA0
int LineupComp::ShowById(int id)
{
  char *v4; // esi
  void (***v5)(_DWORD, _DWORD); // edi
  int v6; // edx
  char *v7; // edi
  int v8; // ecx
  int v9; // esi
  UIStatic *v11; // [esp+0x44] [ebp-0x18]
  char *v12; // [esp+0x48] [ebp-0x14]
  _BYTE v13[16]; // [esp+0x4C] [ebp-0x10] BYREF
  _DWORD *ida; // [esp+0x60] [ebp+0x4]

  v4 = (char *)this + 1944 * id;
  v5 = (void ( ***)(_DWORD, _DWORD))(v4 + 161520);
  v12 = v4;
  (*(void ( **)(char *, const char *, _BYTE *, LineupComp *))(*((_DWORD *)v4 + 40380) + 16))(
    v4 + 161520,
    (&off_56BA1C)[id],
    v13,
    this);
  ((UIStatic *)(v4 + 161520))->CreateFromTemplate();
  v11 = (UIStatic *)(v4 + 161824);
  (*(void ( **)(const char *, _BYTE *, LineupComp *))(*((_DWORD *)v4 + 40456) + 16))(
    (&off_56BA1C)[id],
    v13,
    this);
  ((UIStatic *)(v4 + 161824))->CreateFromTemplate();
  v6 = *((_DWORD *)v4 + 40418);
  v4 += 161672;
  (*(void ( **)(char *, const char *, _BYTE *, LineupComp *))(v6 + 16))(v4, (&off_56BA1C)[id], v13, this);
  ((UIScene *)v4)->SetShow(0);
  sub_446010(v4);
  (**v5)(v5, 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v11->__vftable->ShowWindow)(v11, 0);
  (**(void ( ***)(char *, _DWORD))v4)(v4, 0);
  v7 = "UI\\GameMainUI\\Lineup\\Lineup0";
  v8 = 24 * id + 5683600;
  v9 = (int)(v12 + 161976);
  ida = (_DWORD *)v8;
  do
  {
    LOBYTE(v8) = g_bDebugMode;
    (*(void ( **)(int, _DWORD, _BYTE *, LineupComp *, char *, int))(*(_DWORD *)v9 + 28))(
      v9,
      *ida,
      v13,
      this,
      v7,
      v8);
    sub_445E50(v9);
    (**(void ( ***)(int, _DWORD))v9)(v9, 0);
    v7 += 256;
    v9 += 248;
    ++ida;
  }
  while ( (int)v7 < (int)"UI\\GameMainUI\\Lineup\\zhenlie.tga" );
  this->GetSlotWidget(id, 0);
  return sub_445E50((int)(v12 + 163216));
}

// 0x00484140
int LineupComp::CallSlotMethod(int nIndex, unsigned int dwParam)
{
  char *v3; // edi
  int (***v4)(_DWORD, _DWORD); // edi
  int v5; // ebx
  int result; // eax

  v3 = (char *)this + 1944 * nIndex;
  (**((void ( ***)(int, _DWORD))v3 + 40380))((int)(v3 + 161520), (unsigned __int8)dwParam);
  (**((void ( ***)(int, _DWORD))v3 + 40456))((int)(v3 + 161824), (unsigned __int8)dwParam);
  (**((void ( ***)(int, _DWORD))v3 + 40418))((int)(v3 + 161672), (unsigned __int8)dwParam);
  v4 = (int ( ***)(_DWORD, _DWORD))(v3 + 161976);
  v5 = 6;
  do
  {
    result = (**v4)(v4, (unsigned __int8)dwParam);
    v4 += 62;
    --v5;
  }
  while ( v5 );
  return result;
}

// 0x004841B0
int LineupComp::PositionAt(int arg0, int nVal, int nVal2)
{
  char *v4; // esi

  v4 = (char *)this + 1944 * arg0;
  sub_445FA0(v4 + 161520);
  sub_445FA0(v4 + 161672);
  ((UICaption *)(v4 + 161672))->SetEnable((int)&g_szRoleNameTable[256 * arg0], 0);
  sub_445FA0(v4 + 161976);
  sub_445FA0(v4 + 162224);
  sub_445FA0(v4 + 162968);
  sub_445FA0(v4 + 162720);
  sub_445FA0(v4 + 162472);
  sub_445FA0(v4 + 163216);
  return sub_445FA0(v4 + 161824);
}

// 0x00484E10
int LineupComp::DispatchSlotMethod(int nIndex, unsigned int dwParam)
{
  return this->CallSlotMethod(nIndex, dwParam);
}

// 0x00484E30
int LineupComp::GetSlotWidget(int nIndex, unsigned int dwParam)
{
  int v3; // ebx
  char *v4; // esi
  int result; // eax

  v3 = 6;
  v4 = (char *)this + 1944 * nIndex + 161976;
  do
  {
    result = sub_445E50((int)v4);
    v4 += 248;
    --v3;
  }
  while ( v3 );
  return result;
}
