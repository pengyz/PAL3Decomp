#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIEmote.h"

// Forward declarations for unnamed functions
int sub_445AA0(void); // from annotations
void * sub_446010(void *a2); // from annotations

// Unnamed globals (extern)
extern char byte_80AB19;
extern char byte_80AB20;
extern char byte_80AB21;
extern int dword_DD263C;
extern const char * off_570748;
extern const char * off_570754;

// 0x0044D0B0
int UIEmote::InitParticleSlots()
{
  int v2; // ebx
  char *v3; // edi

  v2 = 10;
  v3 = (char *)this + 8568;
  do
  {
    v3 += 208;
    --v2;
    *((_DWORD *)v3 - 51) = rand() % 100 + 298;
    *((_DWORD *)v3 - 52) = 758;
    *((_DWORD *)v3 - 48) = 1144881152;
  }
  while ( v2 );
  *((_DWORD *)this + 2147) = 128;
  *((_DWORD *)this + 2148) = 64;
  *((_DWORD *)this + 2199) = 128;
  *((_DWORD *)this + 2200) = 64;
  *((_DWORD *)this + 2251) = 128;
  *((_DWORD *)this + 2252) = 128;
  *((_DWORD *)this + 2303) = 256;
  *((_DWORD *)this + 2304) = 256;
  *((_DWORD *)this + 2355) = 256;
  *((_DWORD *)this + 2356) = 64;
  *((_DWORD *)this + 2407) = 64;
  *((_DWORD *)this + 2408) = 32;
  *((_DWORD *)this + 2459) = 256;
  *((_DWORD *)this + 2460) = 128;
  *((_DWORD *)this + 2511) = 512;
  *((_DWORD *)this + 2512) = 128;
  return 128;
}

// 0x0044E530
UIEmote::UIEmote()
{
  sub_445AA0();
  this->m_needscriptdel = 0;
  this->m_role = 0;
  this->m_cur = 0;
  this->m_loopcount = 2;
}

// 0x00529870
void UIEmote::Render()
{
  void *m_id; // edx
  UIStatic *v3; // edi
  float *v4; // ebx
  int capacity; // ebp
  __int64 v6; // rax
  __int64 v7; // rax
  void *vftable; // edx
  UIAnimateCtrl *v9; // edi
  LONG top; // eax
  char *m_pData; // edx
  int m_bvisible; // eax
  UIQuadManager *Instance; // eax
  const char **v14; // [esp+0x30] [ebp-0x38]
  int nVal[4]; // [esp+0x38] [ebp-0x30] BYREF
  _DWORD v16[4]; // [esp+0x48] [ebp-0x20] BYREF
  _DWORD v17[4]; // [esp+0x58] [ebp-0x10] BYREF

  m_id = this->m_ani[0].m_id;
// [VFTABLE] this->m_ani[0].__vftable = (vtbl_0056AE2C *)this->m_ani[0].m_wndcolor.Color;
  this->m_cur = 0;
  this->m_needscriptdel = 0;
  this->m_ani[0].m_fontcolor.Color = (unsigned int)m_id;
// [VFTABLE] ((UIListBox *)this)->SetSelTexture(-1, (int)this->m_needscriptdel, this->m_cur, (int)this->m_ani[0].__vftable, this->m_ani[0].m_fontcolor.Color, 0);
  v14 = &off_570748;
  v3 = (UIStatic *)&this->m_ani[2].m_texarray.m_ptex[7];
  v4 = (float *)&this->m_ani[9].m_texarray.m_ptex[2];
  do
  {
    capacity = this->m_ani[7].m_childs.capacity;
    this->m_cur = (__int64)(v4[1] - (double)(capacity / 2));
    v6 = (__int64)(*v4 - (double)((int)this->m_ani[7].m_childs.m_pData / 2));
    HIDWORD(v6) = this->m_ani[7].m_childs.m_pData;
    this->m_needscriptdel = (gbImage2D *)v6;
    LODWORD(v6) = HIDWORD(v6) + v6;
    HIDWORD(v6) = this->m_cur;
// [VFTABLE] this->m_ani[0].__vftable = (vtbl_0056AE2C *)v6;
    this->m_ani[0].m_fontcolor.Color = HIDWORD(v6) + capacity;
// [VFTABLE] ((void ( *)(UIStatic *, const char *, gbImage2D **, UIEmote *))v3->__vftable->Create)(
// [VFTABLE]   v3,
// [VFTABLE]   *v14,
// [VFTABLE]   &this->m_needscriptdel,
// [VFTABLE]   this);
    ((UIStatic *)v3)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v3->__vftable->ShowWindow)(v3, 0);
    v4 += 2;
    v3 = (UIStatic *)((char *)v3 + 184);
    ++v14;
  }
  while ( (int)v14 < (int)&off_570754 );
  if ( *(int *)&Buffer.m_partyActor.m_curact[39] > 0 )
  {
    v7 = (__int64)((double)*(int *)&Buffer.m_partyActor.m_curact[39] * 0.0099999998);
    this->m_ani[7].m_rect.top = v7;
    if ( (int)v7 <= 0 )
      this->m_ani[7].m_rect.top = 1;
  }
  else
  {
    this->m_ani[7].m_rect.top = 0;
  }
// [VFTABLE] vftable = this->m_ani[6].__vftable;
  v9 = &this->m_ani[6];
  v17[1] = 158;
  v17[0] = 300;
  v17[2] = 468;
  v17[3] = 190;
  ((void ( *)(UIAnimateCtrl *, char *, _DWORD *, UIEmote *))vftable->Create)(
    &this->m_ani[6],
    byte_80AB21,
    v17,
    this);
  ((UIScene *)&this->m_ani[6])->SetShow(0);
  sprintf((char *const)&this->m_ani[0].m_rect, "%s%d%", dword_DD263C, this->m_ani[7].m_rect.top);
  ((UICaption *)&this->m_ani[6])->SetEnable((int)&this->m_ani[0].m_rect, 0);
  sub_446010(&this->m_ani[6]);
  this->m_ani[7].m_fontcolor.Color = 1087583027;
  ((CCBResultWindow *)&this->m_ani[6])->StartAnim();
  top = this->m_ani[7].m_rect.top;
  LOBYTE(this->m_ani[7].m_rect.left) = 0;
  if ( top > 0 )
// [VFTABLE] ((void ( *)(UIAnimateCtrl *, int))v9->__vftable->ShowWindow)(&this->m_ani[6], 1);
  else
// [VFTABLE] ((void ( *)(UIAnimateCtrl *, _DWORD))v9->__vftable->ShowWindow)(&this->m_ani[6], 0);
  nVal[1] = 158;
  nVal[0] = 300;
  nVal[2] = 432;
  nVal[3] = 290;
  ((UINote *)&this->m_ani[11].m_texarray.m_ptex[8])->Create((int)&byte_80AB20, (int)nVal, (int)this, "UI\\Flex\\Note");
  // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->m_ani[11].m_texarray.m_ptex[8]->0)(
    // [VTBL_DISPATCH]   &this->m_ani[11].m_texarray.m_ptex[8],
    // [VTBL_DISPATCH]   0);
  // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, char *, int *, UIEmote *))&this->m_ani[10].m_texarray.m_ptex[11]->0 + 4))(
    // [VTBL_DISPATCH]   &this->m_ani[10].m_texarray.m_ptex[11],
    // [VTBL_DISPATCH]   &byte_80AB20,
    // [VTBL_DISPATCH]   nVal,
    // [VTBL_DISPATCH]   this);
  ((UIScene *)&this->m_ani[10].m_texarray.m_ptex[11])->SetShow(0);
  sub_446010(&this->m_ani[10].m_texarray.m_ptex[11]);
  // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->m_ani[10].m_texarray.m_ptex[11]->0)(
    // [VTBL_DISPATCH]   &this->m_ani[10].m_texarray.m_ptex[11],
    // [VTBL_DISPATCH]   0);
  m_pData = this->m_ani[9].m_childs.m_pData;
  m_bvisible = this->m_ani[7].m_bvisible;
  v16[2] = this->m_ani[9].m_pfather;
  v16[1] = 0;
  v16[0] = 0;
  v16[3] = m_pData;
  (*(void ( **)(int *, char *, _DWORD *, UIEmote *))(m_bvisible + 16))(
    &this->m_ani[7].m_bvisible,
    byte_80AB19,
    v16,
    this);
  ((UIStatic *)&this->m_ani[7].m_bvisible)->CreateFromTemplate();
  (*(void ( **)(int *, _DWORD))this->m_ani[7].m_bvisible)(&this->m_ani[7].m_bvisible, 0);
  (*(void ( **)(int *, char *, _DWORD *, UIEmote *))(this->m_ani[8].m_childs.m_nSize + 16))(
    &this->m_ani[8].m_childs.m_nSize,
    byte_80AB19,
    v16,
    this);
  ((UIStatic *)&this->m_ani[8].m_childs.m_nSize)->CreateFromTemplate();
  (*(void ( **)(int *, _DWORD))this->m_ani[8].m_childs.m_nSize)(
    &this->m_ani[8].m_childs.m_nSize,
    0);
  LOBYTE(this->m_ani[12].m_texarray.m_ptex[15]) = 1;
  Instance = UIQuadManager::GetInstance();
  ((UIRenderObj *)Instance)->_UIRenderObj();
  ((UITitle_QCYM *)this)->HandleDeviceLostC();
}
