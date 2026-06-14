#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/MUIDialog.h"

// 0x0049CEC0
int MUIDialog::GetPlayerAttField(int nVal, int nVal2)
{
  int v3; // esi
  _BYTE *v4; // edx
  int v5; // eax
  _DWORD *v6; // ecx

  v3 = 0;
  v4 = &Buffer.m_partyActor.m_bDirFlag + 1408 * nVal + 32;
  while ( 2 )
  {
    v5 = 0;
    v6 = v4;
    do
    {
      if ( nVal2 == *v6 )
        return *((unsigned __int8 *)&Buffer.m_fMoveRadius + 1408 * nVal + 8 * v3 + v5);
      ++v5;
      ++v6;
    }
    while ( v5 < 8 );
    ++v3;
    v4 += 32;
    if ( v3 < 6 )
      continue;
    break;
  }
  return 0;
}

// 0x004A1620
char MUIDialog::InvokeCallback()
{
  char result; // al
  int v3; // eax
  int v4; // eax

  result = *((_BYTE *)this + 1364);
  if ( result )
  {
    (**((void ( ***)(UIStatic *, _DWORD))&this->m_static + 38))(&this->m_static + 1, 0);
    v3 = *((_DWORD *)this + 331);
    if ( v3 )
    {
      v4 = v3 - 2;
      if ( v4 )
      {
        if ( v4 == 1 )
          (*(void ( **)(PtrArray *, _DWORD))this->m_childs.m_pData)(&this->m_childs, 0);
      }
      else
      {
        (*(void ( **)(tagRECT *, _DWORD))this->m_btRc.left)(&this->m_btRc, 0);
        (**((void ( ***)(char *, _DWORD))&this->m_btRc + 86))((char *)&this->m_btRc + 344, 0);
      }
    }
    else
    {
      (*(void ( **)(tagRECT *, _DWORD))this->m_btRc.left)(&this->m_btRc, 0);
    }
    --g_nUILayoutFlags;
    this->m_bmodal = 0;
    *((_BYTE *)this + 1341) = 0;
    *((_BYTE *)this + 1340) = 0;
    return ((PalScript *)this)->ShowWindow(0);
  }
  return result;
}

// 0x00527130
void MUIDialog::SetSlotCaption(int a2)
{
  DWORD TickCount; // eax
  int v4; // eax
  MUIDialog *v5; // ecx
  void **v6; // eax
  void *v7; // ecx
  MUIDialog *v8; // ecx
  int v9; // edx

  TickCount = GetTickCount();
  CRT_set_new_handler(TickCount);
  v4 = rand() % 2;
  v5 = (MUIDialog *)((char *)this + 32 * a2 + 4096);
// [VFTABLE] v5->__vftable = (vtbl_0056AE2C *)*((_DWORD *)this + 3 * v4 + 1232);
  v5->m_fontcolor.Color = *((_DWORD *)this + 3 * v4 + 1233);
  v5->m_wndcolor.Color = *((_DWORD *)this + 3 * v4 + 1234);
  *((_DWORD *)this + 3758) = v4;
  if ( v4 )
  {
// [VFTABLE] v6 = &this->__vftable + 8 * a2;
    v6[1101] = (void *)*((_DWORD *)this + 1232);
    v6[1102] = (void *)*((_DWORD *)this + 1233);
    v7 = (void *)*((_DWORD *)this + 1234);
  }
  else
  {
// [VFTABLE] v6 = &this->__vftable + 8 * a2;
    v6[1101] = (void *)*((_DWORD *)this + 1235);
    v6[1102] = (void *)*((_DWORD *)this + 1236);
    v7 = (void *)*((_DWORD *)this + 1237);
  }
  v6[1103] = v7;
  v8 = (MUIDialog *)((char *)this + 4388);
  v9 = 5;
  do
  {
    *((_DWORD *)&v8[-1].m_btRc + 87) = 0;
// [VFTABLE] v8->__vftable = 0;
    v8 = (MUIDialog *)((char *)v8 + 32);
    --v9;
  }
  while ( v9 );
  v6[1020] = (void *)1;
  v6[1097] = (void *)1;
  ((UICaption *)((char *)this + 5256))->SetEnable((int)this + 1608 * a2 + 6976, 1);
}
