#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIGameFrm.h"

// Forward declarations for unnamed functions
int sub_4A5760(int a2); // from annotations

// Unnamed globals (extern)
extern void * off_5CC7AC;

// 0x004A6120
int UIGameFrm::OnMessage(int nVal, int nVal2, int nVal3)
{
  int i; // edi
  int j; // edi
  UICursor *v7; // ecx
  UIGameFrm *v8; // esi
  int result; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v11; // eax
  const void *v12; // [esp-0x8] [ebp-0xC]
  const void *v13; // [esp-0x8] [ebp-0xC]

  switch ( nVal )
  {
    case 1000:
      if ( nVal2 )
      {
        for ( i = 0; i < 8; ++i )
          sub_4A5760(i);
        ((EquipUI *)this)->Create();
        ((MainEquipUI *)this)->ShowPage();
        for ( j = 0; j < 5; ++j )
          ((Comp_DonateUI *)this)->ProcessInput();
        g_nSceneState = 1;
        LOBYTE(this->m_note.m_rect.left) = 1;
        v8 = (UIGameFrm *)((char *)this + 154488);
// [VFTABLE] v8->__vftable = 0;
        v8->m_fontcolor.Color = 0;
        ((UICursor *)v7)->IRender();
        result = 1;
      }
      else
      {
        LOBYTE(this->m_note.m_rect.left) = 0;
        result = 1;
      }
      break;
    case 1001:
      switch ( nVal2 )
      {
        case 10486019:
        case 10486020:
        case 10486021:
        case 10486022:
        case 10486023:
        case 10486024:
        case 10486025:
          v12 = off_5CC7AC;
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v12, 1);
          ((MainEquipUI *)this)->HandleMessage();
          result = 1;
          break;
        case 10486032:
          v13 = off_5CC7AC;
          v11 = CScreenMode::GetInstance();
          ((CScreenMode *)v11)->AudioSetPosition(v13, 1);
          ((MainEquipUI *)this)->HandleMessage();
          goto LABEL_12;
        default:
LABEL_12:
          result = 1;
          break;
      }
      break;
    case 1002:
      switch ( nVal2 )
      {
        case 10486018:
          *((_DWORD *)this + 38624) = 0;
          if ( *((_BYTE *)this + 154488) )
            goto LABEL_30;
          sub_4A5760(0);
          result = 1;
          break;
        case 10486019:
          *((_DWORD *)this + 38624) = 1;
          if ( *((_BYTE *)this + 154489) )
            goto LABEL_30;
          sub_4A5760(1);
          result = 1;
          break;
        case 10486020:
          *((_DWORD *)this + 38624) = 2;
          if ( *((_BYTE *)this + 154490) )
            goto LABEL_30;
          sub_4A5760(2);
          result = 1;
          break;
        case 10486021:
          *((_DWORD *)this + 38624) = 3;
          if ( *((_BYTE *)this + 154491) )
            goto LABEL_30;
          sub_4A5760(3);
          result = 1;
          break;
        case 10486022:
          *((_DWORD *)this + 38624) = 5;
          if ( *((_BYTE *)this + 154493) )
            goto LABEL_30;
          sub_4A5760(5);
          result = 1;
          break;
        case 10486023:
          *((_DWORD *)this + 38624) = 6;
          if ( *((_BYTE *)this + 154494) )
            goto LABEL_30;
          sub_4A5760(6);
          result = 1;
          break;
        case 10486024:
          *((_DWORD *)this + 38624) = 4;
          if ( *((_BYTE *)this + 154492) )
            goto LABEL_30;
          sub_4A5760(4);
          result = 1;
          break;
        case 10486025:
          *((_DWORD *)this + 38624) = 7;
          if ( !*((_BYTE *)this + 154495) )
            sub_4A5760(7);
          goto LABEL_30;
        default:
LABEL_30:
          result = 1;
          break;
      }
      break;
    case 1003:
      switch ( nVal2 )
      {
        case 10486018:
          *((_DWORD *)this + 38624) = 0;
          *((_BYTE *)this + 154488) = 0;
          result = 1;
          break;
        case 10486019:
          *((_DWORD *)this + 38624) = 1;
          *((_BYTE *)this + 154489) = 0;
          result = 1;
          break;
        case 10486020:
          *((_DWORD *)this + 38624) = 2;
          *((_BYTE *)this + 154490) = 0;
          result = 1;
          break;
        case 10486021:
          *((_DWORD *)this + 38624) = 3;
          *((_BYTE *)this + 154491) = 0;
          result = 1;
          break;
        case 10486022:
          *((_DWORD *)this + 38624) = 5;
          *((_BYTE *)this + 154493) = 0;
          result = 1;
          break;
        case 10486023:
          *((_DWORD *)this + 38624) = 6;
          *((_BYTE *)this + 154494) = 0;
          result = 1;
          break;
        case 10486024:
          *((_DWORD *)this + 38624) = 4;
          *((_BYTE *)this + 154492) = 0;
          result = 1;
          break;
        case 10486025:
          *((_DWORD *)this + 38624) = 7;
          *((_BYTE *)this + 154495) = 0;
          goto LABEL_40;
        default:
          goto LABEL_40;
      }
      break;
    case 1009:
LABEL_40:
      result = 1;
      break;
    default:
      result = ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
      break;
  }
  return result;
}

// 0x004A6600
int UIGameFrm::Destroy()
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  UIListBox *v10; // [esp+0x0] [ebp-0x8]
  int v11; // [esp+0x4] [ebp-0x4]

  ((CCBRoleState *)this)->Destroy(v10, v11);
  result = (*(int ( **)(_DWORD))(**((_DWORD **)this + 44014) + 12))(*((_DWORD *)this + 44014));
  v3 = *((_DWORD *)this + 44014);
  if ( v3 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
  v4 = *((_DWORD *)this + 44015);
  if ( v4 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
  v5 = *((_DWORD *)this + 44016);
  if ( v5 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
  v6 = *((_DWORD *)this + 44017);
  if ( v6 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
  v7 = *((_DWORD *)this + 44018);
  if ( v7 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
  v8 = *((_DWORD *)this + 44019);
  if ( v8 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
  v9 = *((_DWORD *)this + 44020);
  if ( v9 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
  *((_DWORD *)this + 44014) = 0;
  *((_DWORD *)this + 44015) = 0;
  *((_DWORD *)this + 44016) = 0;
  *((_DWORD *)this + 44017) = 0;
  *((_DWORD *)this + 44018) = 0;
  *((_DWORD *)this + 44019) = 0;
  *((_DWORD *)this + 44020) = 0;
  return result;
}
