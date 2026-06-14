#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "GameBase/SoundContext.h"

// 0x00527A80
void SoundContext::CreateSubPanels(int nMode)
{
  int v3; // eax
  int v4; // ecx
  JusticeBookUI *v5; // eax
  PAL_GDB *v6; // eax
  SaleUI *v7; // eax
  CCBUI *inited; // eax
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v11; // esi
  int nVal[4]; // [esp+0x10] [ebp-0x1C] BYREF
  int v13; // [esp+0x28] [ebp-0x4]

  v3 = *((_DWORD *)this + 22);
  v4 = *((_DWORD *)this + 23);
  *((_DWORD *)this + 20) = v3;
  *((_DWORD *)this + 21) = v4;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, *((_DWORD *)this + 20), *((_DWORD *)this + 21), 0);
  nVal[1] = 200;
  nVal[0] = 250;
  nVal[2] = 550;
  nVal[3] = 300;
  ((ARC_PlayerAtt *)(this + 89))->Create((int)&g_PlayerAttBuffer, (int)nVal);
  ((UIItem *)(this + 89))->SetData(31);
  v5 = (JusticeBookUI *)operator new(0xDB80u);
  v13 = 0;
  if ( v5 )
    v6 = (PAL_GDB *)((JusticeBookUI *)v5)->ctor();
  else
    v6 = 0;
  v13 = -1;
  *((_DWORD *)this + 431) = v6;
  ((PAL_GDB *)v6)->InitSkillDisplay((int)this);
  v7 = (SaleUI *)operator new(0x18E34u);
  v13 = 1;
  if ( v7 )
    inited = (CCBUI *)((SaleUI *)v7)->InitUI();
  else
    inited = 0;
  v13 = -1;
  *((_DWORD *)this + 432) = inited;
  ((CCBUI *)inited)->InitSkillUI((int)this);
  *(SoundContext *)(*((_DWORD *)this + 431) + 12748) = *(this + 432);
  *((_BYTE *)this + 1740) = 0;
  *((_DWORD *)this + 434) = nMode;
  if ( !nMode )
  {
    ((PAL3 *)this)->HandleDeviceLost();
    *((_BYTE *)this + 1740) = 1;
  }
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
    v11 = AudioManager;
    if ( AudioManager )
    {
      ((gbAudioManager *)AudioManager)->DetachAll3D();
      ((gbAudioManager *)v11)->StopSoundStream(0);
      ((gbAudioManager *)v11)->StopSoundStream(2);
      ((gbAudioManager *)v11)->StopSoundStream(1);
    }
  }
}
