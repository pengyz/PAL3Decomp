#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/BINK.h"

gbActorMgr * GetActorMgr(void); // from annotations

// 0x004236D0
void BINK::Reset()
{
  bool v2; // zf
  char v3; // [esp+0x13] [ebp-0x19]
  unsigned int *p_BytesRead; // [esp+0x14] [ebp-0x18]
  int v5; // [esp+0x18] [ebp-0x14]

  this->Height = 0;
  ((RenderTarget3 *)&this->Frames)->ClearEffects();
  this->Size = 0;
  this->FrameSize = 0;
  this->SndSize = 0;
  this->FrameRects[0].Top = 0;
  this->FrameRects[0].Width = 0;
  this->FrameRects[0].Height = 0;
  this->FrameRects[1].Left = 0;
  this->FrameRects[1].Top = 0;
  this->FrameRects[1].Width = 0;
  ((PalScriptMgr *)&this->FrameRects[2].Top)->InitControlBlock();
  v5 = 16;
  this->UVWidth = 0;
  this->UVHeight = 0;
  this->MaskPlane = 0;
  p_BytesRead = &this->bio.BytesRead;
  do
  {
    v2 = v5 == 1;
    p_BytesRead += 3;
    --v5;
  }
  while ( !v2 );
  this->twoframestime = 0;
  this->entireframetime = 0;
  this->slowestframetime = 0;
  this->slowestframe = 0;
  this->slowest2frametime = 0;
  this->slowest2frame = 0;
  this->bsnd.snddata[84] = v3;
  *(_DWORD *)&this->bsnd.snddata[88] = 0;
  *(_DWORD *)&this->bsnd.snddata[92] = 0;
  *(_DWORD *)&this->bsnd.snddata[96] = 0;
  *(_DWORD *)&this->bsnd.snddata[100] = 0;
  *(_DWORD *)&this->bsnd.snddata[104] = 0;
  *(_DWORD *)&this->bsnd.snddata[108] = 0;
  *(_DWORD *)&this->bsnd.snddata[112] = 0;
  *(_DWORD *)&this->bsnd.snddata[116] = 0;
  *(_DWORD *)&this->bsnd.snddata[120] = 0;
  *(_DWORD *)&this->bsnd.snddata[124] = 0;
  this->skippedlastblit = 0;
  memset(&this->FrameRects[7].Width, 0, 0x26Cu);
  memset(this->FrameRects, 0, 0x24u);
  *(_DWORD *)&this->bsnd.snddata[48] = 0;
  *(_DWORD *)&this->bsnd.snddata[52] = 0;
  this->bsnd.snddata[56] = -1;
  *(_DWORD *)&this->bsnd.snddata[64] = 0;
  *(_DWORD *)&this->bsnd.snddata[68] = 0;
  *(_DWORD *)&this->bsnd.snddata[72] = 0;
  *(_DWORD *)&this->bsnd.snddata[76] = 0;
  *(_DWORD *)&this->bsnd.snddata[80] = 0;
  this->sndendframe = 0;
  this->soundskips = 0;
  this->sndprime = 0;
}

// 0x004243E0
void BINK::Destroy()
{
  void ( ***Left)(_DWORD, int); // ecx
  BINKRECT *FrameRects; // edi
  int v4; // edx
  unsigned int v5; // ecx
  void **v6; // eax
  int *v7; // eax
  int v8; // ecx
  void *skippedblits; // edi
  void *v10; // [esp-0x8] [ebp-0x14]

  Left = (void ( ***)(_DWORD, int))this->FrameRects[0].Left;
  FrameRects = this->FrameRects;
  if ( Left )
  {
    (**Left)(Left, 1);
    FrameRects->Left = 0;
  }
  memset(FrameRects, 0, 0x24u);
  GetActorMgr();
  memset(&this->FrameRects[7].Width, 0, 0x26Cu);
  if ( *(_DWORD *)&this->bsnd.snddata[48] )
  {
    operator delete(*(void **)&this->bsnd.snddata[48]);
    *(_DWORD *)&this->bsnd.snddata[48] = 0;
  }
  *(_DWORD *)&this->bsnd.snddata[52] = 0;
  this->bsnd.snddata[56] = -1;
  *(_DWORD *)&this->bsnd.snddata[60] = 0;
  *(_DWORD *)&this->bsnd.snddata[64] = 0;
  *(_DWORD *)&this->bsnd.snddata[68] = 0;
  *(_DWORD *)&this->bsnd.snddata[72] = 0;
  *(_DWORD *)&this->bsnd.snddata[76] = 0;
  *(_DWORD *)&this->bsnd.snddata[80] = 0;
  while ( this->skippedlastblit )
  {
    v4 = *(_DWORD *)&this->bsnd.snddata[96] + 76;
    v5 = this->skippedlastblit - 1;
    *(_DWORD *)&this->bsnd.snddata[96] = v4;
    this->skippedlastblit = v5;
    if ( !v5 || v4 == *(_DWORD *)&this->bsnd.snddata[92] )
    {
      v6 = *(void ***)&this->bsnd.snddata[100];
      *(_DWORD *)&this->bsnd.snddata[100] = v6 + 1;
      operator delete(*v6);
      if ( this->skippedlastblit )
      {
        v7 = *(int **)&this->bsnd.snddata[100];
        v8 = *v7;
        *(_DWORD *)&this->bsnd.snddata[88] = *v7;
        *(_DWORD *)&this->bsnd.snddata[92] = v8 + 4028;
        *(_DWORD *)&this->bsnd.snddata[96] = v8;
        *(_DWORD *)&this->bsnd.snddata[100] = v7;
      }
      else
      {
        *(_DWORD *)&this->bsnd.snddata[88] = 0;
        *(_DWORD *)&this->bsnd.snddata[92] = 0;
        *(_DWORD *)&this->bsnd.snddata[96] = 0;
        *(_DWORD *)&this->bsnd.snddata[100] = 0;
        *(_DWORD *)&this->bsnd.snddata[104] = 0;
        v10 = *(void **)&this->bsnd.snddata[120];
        *(_DWORD *)&this->bsnd.snddata[108] = 0;
        *(_DWORD *)&this->bsnd.snddata[112] = 0;
        *(_DWORD *)&this->bsnd.snddata[116] = 0;
        operator delete(v10);
      }
    }
  }
  skippedblits = (void *)this->skippedblits;
  if ( skippedblits )
  {
    operator delete(skippedblits);
    this->skippedblits = 0;
  }
  this->soundskips = 1065353216;
  this->sndendframe = 0;
  this->sndprime = 0;
}

// 0x004517A0
int BINK::SetVideoRect(char pData)
{
  char v3; // [esp+0x8] [ebp+0x8]

  *(_DWORD *)(pData + 4) = 552;
  *(_DWORD *)(pData + 12) = 584;
  *(_DWORD *)pData = v3 != 0 ? 760 : 18;
  *(_DWORD *)(pData + 8) = v3 != 0 ? 792 : 50;
  return pData;
}
