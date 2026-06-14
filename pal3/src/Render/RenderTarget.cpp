#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/RenderTarget.h"

// Forward declarations for unnamed functions
int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
CHAR * sub_458F70(LPCSTR lpString, int a2, LPSTR lpString1); // from annotations
int sub_5427A5(...);
int sub_543C42(...);

int crt_sub_00540070(void); // from annotations

// Unnamed globals (extern)
extern char asc_5B74B8[];
extern char byte_5967B0[3];
extern int dword_DC8D3C;
extern const char * off_56C548;
extern void * off_5C775C;
extern void *off_5C7760;
extern int unk_5D3C68;
extern int unk_5D3C6C;

// 0x0047A400
int RenderTarget::InitParticleRenders()
{
  RenderTarget *v2; // esi
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  int v15; // [esp+0x18] [ebp-0xC]
  int v16; // [esp+0x1C] [ebp-0x8]
  int v17; // [esp+0x20] [ebp-0x4]

  v15 = 60;
  v2 = (RenderTarget *)((char *)this + 173948);
  do
  {
    v3 = *((_DWORD *)this + 52247);
    v4 = *((_DWORD *)this + 52249) - v3;
    v5 = rand();
    v16 = *((_DWORD *)this + 52248);
    v17 = v3 + v5 % (v4 / 2);
    v6 = *((_DWORD *)this + 52250) - v16;
    ((RenderTarget *)v2)->LoadTexture(szFilename);
    ((RenderTarget *)v2)->SetSize(32);
    fY = rand() % 10 + 252;
    fX = rand() % 10 + 36;
    v7 = rand();
    ((RenderTarget *)v2)->SetColor(v7 % 10 - 37, fX, fY);
    v8 = rand();
    ((RenderTarget *)v2)->SetAlpha(v8 % 135 + 120);
    ((RenderTarget *)v2)->SetField084();
    ((RenderTarget *)v2)->SetState();
    fYa = (float)v16;
    fXa = (float)v17;
    ((RenderTarget *)v2)->UpdateTransform(fXa, fYa);
    ((RenderTarget *)v2)->CalcRenderDimensions(v4, v6);
    ((RenderTarget *)v2)->SetOffset(1092616192);
    rand();
    *(float *)&fXb = (float)(rand() % 8 + 2);
    ((RenderTarget *)v2)->SetScale(fXb);
    ((RenderTarget *)v2)->SetVisible(1);
    v2 = (RenderTarget *)((char *)v2 + 584);
    result = --v15;
  }
  while ( v15 );
  return result;
}

// 0x004867F0
int RenderTarget::InitChildPanels()
{
  char *v2; // edi
  int v3; // ebp

  this->m_szPath = 800;
  this->m_nDefaultH = 600;
  *((_DWORD *)this + 218) = 0;
  *((_BYTE *)this + 876) = 0;
  *((_BYTE *)this + 889) = 0;
  *((_DWORD *)this + 223) = 0;
  *((_DWORD *)this + 224) = 0;
  *((_DWORD *)this + 225) = 0;
  *((_DWORD *)this + 226) = -1;
  *((_BYTE *)this + 908) = 0;
  *((_BYTE *)this + 910) = 0;
  *((_BYTE *)this + 911) = 0;
  *((_BYTE *)this + 912) = 0;
  *((_DWORD *)this + 229) = 0;
  *((_DWORD *)this + 830) = 0;
  *((_BYTE *)this + 3336) = 0;
  *((_BYTE *)this + 3337) = 0;
  *((_BYTE *)this + 3348) = 0;
  *((_DWORD *)this + 836) = 0;
  *((_DWORD *)this + 835) = 0;
  v2 = (char *)this + 3356;
  v3 = 40;
  do
  {
    ArraySort((int)v2, 12, 99, 0 /* TODO: (int)RenderTarget::Init */);
    v2 += 1192;
    --v3;
  }
  while ( v3 );
  *((_DWORD *)this + 12758) = 0;
  sub_4422E0((char *)this + 51036);
  sub_4422E0((char *)this + 51188);
  sub_4422E0((char *)this + 51340);
  sub_4422E0((char *)this + 51492);
  sub_4422E0((char *)this + 51644);
  sub_4422E0((char *)this + 51796);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0((char *)this + 55044);
  sub_4422E0((char *)this + 55836);
  sub_4422E0((char *)this + 55988);
  *((_DWORD *)this + 51446) = 0;
  ((ARC_PlayerAtt *)((char *)this + 205788))->Refresh();
  ((ARC_PlayerAtt *)((char *)this + 207156))->Refresh();
  ((ARC_PlayerAtt *)((char *)this + 208524))->Refresh();
  ((UI3DCtrl *)((char *)this + 210236))->ctor_D830();
  sub_4422E0((char *)this + 210320);
  sub_4422E0((char *)this + 211840);
  sub_4422E0((char *)this + 211992);
  sub_4422E0((char *)this + 212144);
  sub_4422E0((char *)this + 212296);
  sub_4422E0((char *)this + 212448);
  ((UIListBox *)((char *)this + 239812))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 241020))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 242228))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 243436))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 244644))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 245852))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 247060))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 248268))->UpdateKeyCtrl();
  ((UIProgressBar *)((char *)this + 249476))->ctor();
  *((_BYTE *)this + 881) = 0;
  *((_BYTE *)this + 880) = 0;
  *((_BYTE *)this + 878) = 0;
  *((_BYTE *)this + 877) = 0;
  *((_BYTE *)this + 879) = 0;
  *((_DWORD *)this + 833) = 0;
  *((_DWORD *)this + 832) = 0;
  *((_DWORD *)this + 831) = 0;
  *((_DWORD *)this + 76758) = 0;
  *((_DWORD *)this + 76759) = 0;
  *((_DWORD *)this + 51443) = 0;
  *((_DWORD *)this + 51444) = 0;
  *((_DWORD *)this + 51445) = 0;
  return (int)this;
}

// 0x00486CE0
int * RenderTarget::Init()
{
  this->m_iMode = 0;
  this->m_Texture = 0;
  this->m_nRenderX = 0;
  this->m_iMode = 0xFFFF;
  return &this->m_iMode;
}

// 0x004870C0
void RenderTarget::InitNPCPanel()
{
  ((PalScript *)((char *)this + 249476))->PalScript_Init();
  ((UIListBox *)((char *)this + 248268))->DeleteRow();
  ((UIListBox *)((char *)this + 247060))->DeleteRow();
  ((UIListBox *)((char *)this + 245852))->DeleteRow();
  ((UIListBox *)((char *)this + 244644))->DeleteRow();
  ((UIListBox *)((char *)this + 243436))->DeleteRow();
  ((UIListBox *)((char *)this + 242228))->DeleteRow();
  ((UIListBox *)((char *)this + 241020))->DeleteRow();
  ((UIListBox *)((char *)this + 239812))->DeleteRow();
  ((UIFrameWnd *)((char *)this + 212448))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212296))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212144))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 211992))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 211840))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 210320))->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)((char *)this + 210236))->ctor();
  ((UIRoleDialog *)((char *)this + 208524))->_UIRoleDialog();
  ((UIRoleDialog *)((char *)this + 207156))->_UIRoleDialog();
  ((UIRoleDialog *)((char *)this + 205788))->_UIRoleDialog();
  ((UIFrameWnd *)((char *)this + 55988))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 55836))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 55044))->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)((char *)this + 54700))->Destroy2();
  ((UICaption *)((char *)this + 54356))->Destroy2();
  ((UICaption *)((char *)this + 54012))->Destroy2();
  ((UICaption *)((char *)this + 53668))->Destroy2();
  ((UICaption *)((char *)this + 53324))->Destroy2();
  ((UICaption *)((char *)this + 52980))->Destroy2();
  ((UICaption *)((char *)this + 52636))->Destroy2();
  ((UICaption *)((char *)this + 52292))->Destroy2();
  ((UICaption *)((char *)this + 51948))->Destroy2();
  ((UIFrameWnd *)((char *)this + 51796))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51644))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51492))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51340))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51188))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51036))->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0048F3A0
int RenderTarget::OnRender()
{
  int i; // edi
  int result; // eax
  const char *v4; // ebp
  int v5; // ecx
  int *v6; // eax
  const char **v7; // eax
  int v8; // ebx
  CScreenMode *v9; // eax
  char *v10; // edi
  int v11; // ebp
  int v12; // ebp
  char *v13; // edi
  char v14; // al
  char v15; // al
  int v16; // edi
  char *v17; // ebp
  char v18; // al
  char *v19; // edi
  int v20; // ebx
  CScreenMode *v21; // eax
  int v22; // ecx
  int *v23; // eax
  char v24; // al
  char *v25; // esi
  int v26; // edi
  int v27; // ebx
  int v28; // eax
  int v29; // eax
  int v30; // ecx
  char *v31; // edx
  int v32; // ebp
  char *v33; // edi
  char v34; // al
  char *v35; // esi
  int v36; // edi
  int v37; // edi
  int *v38; // edx
  int v39; // edi
  int *v40; // eax
  int v41; // edi
  int v42; // edi
  int v43; // edi
  int v44; // edi
  int v45; // edi
  CHAR *v46; // ebx
  LPCSTR v47; // eax
  const char *v48; // ebx
  int Child; // eax
  int v50; // eax
  int v51; // eax
  int v52; // ecx
  int v53; // eax
  const char *v54; // eax
  int v55; // edx
  int v56; // eax
  int v57; // eax
  int v58; // eax
  int v59; // ecx
  int v60; // eax
  int v61; // edx
  int v62; // eax
  int v63; // eax
  int v64; // eax
  CHAR *v65; // ebx
  RoleAtt *v66; // ecx
  LPCSTR v67; // eax
  const char *v68; // ebx
  CScreenMode *Instance; // eax
  const void *v70; // [esp-0x8] [ebp-0x120]
  const char *v71; // [esp-0x8] [ebp-0x120]
  const void *v72; // [esp-0x8] [ebp-0x120]
  int v73; // [esp+0x10] [ebp-0x108]
  RoleAtt *SkillNum; // [esp+0x10] [ebp-0x108]
  RoleAtt *v75; // [esp+0x10] [ebp-0x108]
  const char **nVal; // [esp+0x14] [ebp-0x104]
  char *nVala; // [esp+0x14] [ebp-0x104]
  char Buffer; // [esp+0x18] [ebp-0x100] BYREF
  _BYTE v79[252]; // [esp+0x19] [ebp-FFh] BYREF
  __int16 v80; // [esp+0x115] [ebp-0x3]
  char v81; // [esp+0x117] [ebp-0x1]
  int v82; // [esp+0x11C] [ebp+0x4]
  int nMsg; // [esp+0x120] [ebp+0x8]
  int wParam; // [esp+0x124] [ebp+0xC]

  switch ( v82 )
  {
    case 1000:
      if ( nMsg )
      {
        for ( i = 0; i < 8; ++i )
          ((CEffect *)this)->CreateFromTemplate(i);
        ((MagicUI *)this)->RefreshAndLayout();
        ((PalScript *)this)->InitMainUIScripts();
        g_nSceneState = 1;
        *((_BYTE *)this + 888) = 1;
        *((_DWORD *)this + 51443) = 0;
        *((_DWORD *)this + 51444) = 0;
        *((_BYTE *)this + 909) = 0;
        ((UICursor *)((char *)this + 205772))->IRender();
        return 1;
      }
      else
      {
        *((_BYTE *)this + 888) = 0;
        return 1;
      }
    case 1001:
      if ( *((_BYTE *)this + 3336) )
        return 1;
      v4 = (const char *)nMsg;
      v5 = 0;
      v6 = g_MonsterEntryTable;
      break;
    case 1002:
      if ( *((_BYTE *)this + 3336) )
        return 1;
      *(&this->m_nDefaultH + 1) = 0;
      v27 = 5;
      while ( 1 )
      {
        v28 = *(&this->m_nDefaultH + 1);
        if ( *((_BYTE *)this + v28 + 877) )
        {
          if ( nMsg == g_MonsterEntryTable[v28] )
            break;
        }
        v29 = v28 + 1;
        *(&this->m_nDefaultH + 1) = v29;
        if ( v29 >= 5 )
        {
          switch ( nMsg )
          {
            case 10486018:
              *((_DWORD *)this + 51445) = 0;
              if ( *((_BYTE *)this + 205772) )
                goto LABEL_93;
              ((CEffect *)this)->CreateFromTemplate(0);
              result = 1;
              break;
            case 10486019:
              *((_DWORD *)this + 51445) = 1;
              if ( *((_BYTE *)this + 205773) )
                goto LABEL_93;
              ((CEffect *)this)->CreateFromTemplate(1);
              result = 1;
              break;
            case 10486020:
              *((_DWORD *)this + 51445) = 2;
              if ( *((_BYTE *)this + 205774) )
                goto LABEL_93;
              ((CEffect *)this)->CreateFromTemplate(2);
              result = 1;
              break;
            case 10486021:
              *((_DWORD *)this + 51445) = 3;
              if ( *((_BYTE *)this + 205775) )
                goto LABEL_93;
              ((CEffect *)this)->CreateFromTemplate(3);
              result = 1;
              break;
            case 10486022:
              *((_DWORD *)this + 51445) = 5;
              if ( *((_BYTE *)this + 205777) )
                goto LABEL_93;
              ((CEffect *)this)->CreateFromTemplate(5);
              result = 1;
              break;
            case 10486023:
              *((_DWORD *)this + 51445) = 6;
              if ( *((_BYTE *)this + 205778) )
                goto LABEL_93;
              ((CEffect *)this)->CreateFromTemplate(6);
              result = 1;
              break;
            case 10486024:
              *((_DWORD *)this + 51445) = 4;
              if ( *((_BYTE *)this + 205776) )
                goto LABEL_93;
              ((CEffect *)this)->CreateFromTemplate(4);
              result = 1;
              break;
            case 10486025:
              *((_DWORD *)this + 51445) = 7;
              if ( !*((_BYTE *)this + 205779) )
                ((CEffect *)this)->CreateFromTemplate(7);
              goto LABEL_93;
            default:
LABEL_93:
              result = 1;
              break;
          }
          return result;
        }
      }
      if ( *((_BYTE *)this + 910) && *((_BYTE *)this + 909) )
      {
        v30 = *((_DWORD *)this + 224);
        if ( v30 < 0 )
          return 1;
        v31 = (char *)this + 12 * v30;
        v32 = (int)&v31[9536 * *((_DWORD *)this + 226) + 3356 + 1192 * *((_DWORD *)this + 225)];
        if ( *(_BYTE *)(*(_DWORD *)&v31[9536 * *((_DWORD *)this + 226) + 3364 + 1192 * *((_DWORD *)this + 225)] + 577) == 1 )
        {
          v33 = (char *)this + 217324;
          do
          {
            (**(void ( ***)(char *, _DWORD))v33)(v33, 0);
            v33 += 4892;
            --v27;
          }
          while ( v27 );
          ((CameraCtrl *)this)->CalcStatPower(v32);
          if ( v34 )
          {
            (**((void ( ***)(char *, int))this + 1223 * *(&this->m_nDefaultH + 1) + 54331))(
              (char *)this + 4892 * *(&this->m_nDefaultH + 1) + 217324,
              1);
            return 1;
          }
          ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), *((_DWORD *)this + 225));
        }
      }
      return 1;
    case 1003:
      switch ( nMsg )
      {
        case 10486018:
          *((_DWORD *)this + 51445) = 0;
          *((_BYTE *)this + 205772) = 0;
          result = 1;
          break;
        case 10486019:
          *((_DWORD *)this + 51445) = 1;
          *((_BYTE *)this + 205773) = 0;
          result = 1;
          break;
        case 10486020:
          *((_DWORD *)this + 51445) = 2;
          *((_BYTE *)this + 205774) = 0;
          result = 1;
          break;
        case 10486021:
          *((_DWORD *)this + 51445) = 3;
          *((_BYTE *)this + 205775) = 0;
          result = 1;
          break;
        case 10486022:
          *((_DWORD *)this + 51445) = 5;
          *((_BYTE *)this + 205777) = 0;
          result = 1;
          break;
        case 10486023:
          *((_DWORD *)this + 51445) = 6;
          *((_BYTE *)this + 205778) = 0;
          result = 1;
          break;
        case 10486024:
          *((_DWORD *)this + 51445) = 4;
          *((_BYTE *)this + 205776) = 0;
          result = 1;
          break;
        case 10486025:
          *((_DWORD *)this + 51445) = 7;
          *((_BYTE *)this + 205779) = 0;
          goto LABEL_103;
        default:
LABEL_103:
          result = 1;
          break;
      }
      return result;
    case 1007:
      if ( *((_BYTE *)this + 3336) )
        return 1;
      *((_DWORD *)this + 224) = wParam;
      if ( wParam >= 0 )
      {
        switch ( nMsg )
        {
          case 10486295:
            v37 = *((_DWORD *)this + 224);
            if ( v37 >= ((UIListBox *)((char *)this + 239812))->GetItemData() )
              goto LABEL_141;
            v38 = (int *)((char *)this + 9536 * *((_DWORD *)this + 51446) + 12 * v37 + 3356);
            ((MainPropUI *)this)->SetCaption(*v38, v38[1], v38[2]);
            return 1;
          case 10486296:
            v39 = *((_DWORD *)this + 224);
            if ( v39 >= ((UIListBox *)((char *)this + 241020))->GetItemData() )
              goto LABEL_141;
            v40 = (int *)((char *)this + 9536 * *((_DWORD *)this + 51446) + 12 * v39 + 8124);
            goto LABEL_129;
          case 10486297:
            v41 = *((_DWORD *)this + 224);
            if ( v41 >= ((UIListBox *)((char *)this + 242228))->GetItemData() )
              goto LABEL_141;
            v40 = (int *)((char *)this + 9536 * *((_DWORD *)this + 51446) + 12 * v41 + 6932);
            goto LABEL_129;
          case 10486304:
            v42 = *((_DWORD *)this + 224);
            if ( v42 >= ((UIListBox *)((char *)this + 243436))->GetItemData() )
              goto LABEL_141;
            v40 = (int *)((char *)this + 9536 * *((_DWORD *)this + 51446) + 12 * v42 + 4548);
            goto LABEL_129;
          case 10486305:
            v43 = *((_DWORD *)this + 224);
            if ( v43 >= ((UIListBox *)((char *)this + 244644))->GetItemData() )
              goto LABEL_141;
            v40 = (int *)((char *)this + 9536 * *((_DWORD *)this + 51446) + 12 * v43 + 5740);
            goto LABEL_129;
          case 10486306:
            v44 = *((_DWORD *)this + 224);
            if ( v44 >= ((UIListBox *)((char *)this + 245852))->GetItemData() )
              goto LABEL_141;
            v40 = (int *)((char *)this + 9536 * *((_DWORD *)this + 51446) + 12 * v44 + 9316);
            goto LABEL_129;
          case 10486307:
            v45 = *((_DWORD *)this + 224);
            if ( v45 >= ((UIListBox *)((char *)this + 247060))->GetItemData() )
              goto LABEL_141;
            v40 = (int *)((char *)this + 9536 * *((_DWORD *)this + 51446) + 12 * v45 + 10508);
LABEL_129:
            ((MainPropUI *)this)->SetCaption(*v40, v40[1], v40[2]);
            result = 1;
            break;
          case 10486308:
            *((_DWORD *)this + 224) = ((UIListBox *)((char *)this + 248268))->GetLockedSel();
            if ( *((_DWORD *)this + 224) < ((UIListBox *)((char *)this + 248268))->GetItemData() )
            {
              ((MainPropUI *)this)->FindValidSaveSlot();
              SkillNum = (RoleAtt *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*((_DWORD *)this
                                      + 75 * *((unsigned __int8 *)this + *((_DWORD *)this + 224) + 307032)
                                      + 232));
              sprintf((char *const)&this->m_ScreenPlane + 4, g_szSceneUIText);
              v46 = sub_458F70(&SkillNum->Remark[90], (int)asc_5B74B8, (LPSTR)this + 360);
              if ( lstrlenA(v46) <= 0 )
              {
                ((RoleAtt *)SkillNum)->FormatAttributeText();
                lstrcpyA((LPSTR)&this->m_ScreenPlane + 4, v47);
              }
              else
              {
                lstrcpyA((LPSTR)&this->m_ScreenPlane + 4, v46);
              }
              ((UICaption *)((char *)this + 212144))->SetEnable((int)(&this->m_ScreenPlane + 1), 0);
              ((UICaption *)((char *)this + 211992))->SetEnable((int)this + 360, 0);
              ((UICaption *)(UICaption *)this + 2213)->SetEnable((int)this + 300 * *((unsigned __int8 *)this + *((_DWORD *)this + 224) + 307032) + 932, 1);
              v48 = &SkillNum->Remark[30];
              if ( !strcmp(&SkillNum->Remark[30], g_szSceneUIText) )
                sprintf((char *const)&this->m_ScreenPlane + 4, byte_5967B0, "NONE");
              else
                sprintf(
                  (char *const)&this->m_ScreenPlane + 4,
                  "Item\\%s\\%s.pol",
                  &SkillNum->Remark[30],
                  &SkillNum->Remark[30]);
              ((PalScript *)((char *)this + 249548))->LoadModel((const char *)&this->m_ScreenPlane + 4, 0);
              if ( !strcmp(&SkillNum->Remark[30], g_szSceneUIText) )
              {
                sprintf((char *const)&this->m_ScreenPlane + 4, byte_5967B0, "NONE");
              }
              else
              {
                Buffer = 0;
                memset(v79, 0, sizeof(v79));
                v80 = 0;
                v81 = 0;
                sprintf(&Buffer, "%s%s", v48, &SkillNum->Remark[60]);
                sprintf((char *const)&this->m_ScreenPlane + 4, "Item\\%s\\%s.tga", v48, &Buffer);
              }
              ((gbGeomNode *)*((gbGeomNode **)this + 62391))->ReplaceTexture((const char *)&this->m_ScreenPlane + 4);
              *((_DWORD *)this + 62388) = 1;
            }
            goto LABEL_141;
          default:
LABEL_141:
            result = 1;
            break;
        }
      }
      else
      {
        ((UICaption *)((char *)this + 211992))->SetEnable((int)g_szSceneUIText, 0);
        ((UICaption *)((char *)this + 212144))->SetEnable((int)g_szSceneUIText, 0);
        return 1;
      }
      return result;
    case 1008:
      if ( *((_BYTE *)this + 3336) )
        return 1;
      switch ( nMsg )
      {
        case 10486295:
          Child = ((NPC *)((char *)this + 239812))->CreateChild();
          *((_DWORD *)this + 224) = Child;
          if ( Child >= 0 )
          {
            if ( ((CameraCtrl *)this)->HandleCameraEvent(Child, 0) )
            {
              ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), 0);
              ((MainPropUI *)this)->SetPage(0);
              v50 = *((_DWORD *)this + 51446);
              *((_BYTE *)this + 908) = 1;
              *((_DWORD *)this + 226) = v50;
              *((_BYTE *)this + 910) = 1;
              *((_BYTE *)this + 909) = 1;
            }
            else
            {
              *((_BYTE *)this + 910) = 0;
            }
            *((_DWORD *)this + 225) = 0;
            v71 = off_5C7760[0];
          }
          else
          {
            v71 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486296:
          v51 = ((NPC *)((char *)this + 241020))->CreateChild();
          *((_DWORD *)this + 224) = v51;
          if ( v51 >= 0 )
          {
            if ( ((CameraCtrl *)this)->HandleCameraEvent(v51, 4) )
            {
              ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), 4);
              ((MainPropUI *)this)->SetPage(0);
              v52 = *((_DWORD *)this + 51446);
              *((_BYTE *)this + 908) = 1;
              *((_DWORD *)this + 226) = v52;
              *((_BYTE *)this + 910) = 1;
              *((_BYTE *)this + 909) = 1;
            }
            else
            {
              *((_BYTE *)this + 910) = 0;
            }
            *((_DWORD *)this + 225) = 4;
            v71 = off_5C7760[0];
          }
          else
          {
            v71 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486297:
          v53 = ((NPC *)((char *)this + 242228))->CreateChild();
          *((_DWORD *)this + 224) = v53;
          if ( v53 < 0 )
          {
            v54 = g_pCScreenMode_5C7768;
            goto LABEL_201;
          }
          if ( ((CameraCtrl *)this)->HandleCameraEvent(v53, 3) )
          {
            ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), 3);
            ((MainPropUI *)this)->SetPage(0);
            v55 = *((_DWORD *)this + 51446);
            *((_BYTE *)this + 908) = 1;
            *((_DWORD *)this + 226) = v55;
            *((_BYTE *)this + 910) = 1;
            *((_BYTE *)this + 909) = 1;
          }
          else
          {
            *((_BYTE *)this + 910) = 0;
          }
          *((_DWORD *)this + 225) = 3;
          goto LABEL_200;
        case 10486304:
          v56 = ((NPC *)((char *)this + 243436))->CreateChild();
          *((_DWORD *)this + 224) = v56;
          if ( v56 >= 0 )
          {
            if ( ((CameraCtrl *)this)->HandleCameraEvent(v56, 1) )
            {
              ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), 1);
              ((MainPropUI *)this)->SetPage(0);
              v57 = *((_DWORD *)this + 51446);
              *((_BYTE *)this + 908) = 1;
              *((_DWORD *)this + 226) = v57;
              *((_BYTE *)this + 910) = 1;
              *((_BYTE *)this + 909) = 1;
            }
            else
            {
              *((_BYTE *)this + 910) = 0;
            }
            *((_DWORD *)this + 225) = 1;
            v71 = off_5C7760[0];
          }
          else
          {
            v71 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486305:
          v58 = ((NPC *)((char *)this + 244644))->CreateChild();
          *((_DWORD *)this + 224) = v58;
          if ( v58 >= 0 )
          {
            if ( ((CameraCtrl *)this)->HandleCameraEvent(v58, 2) )
            {
              ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), 2);
              ((MainPropUI *)this)->SetPage(0);
              v59 = *((_DWORD *)this + 51446);
              *((_BYTE *)this + 908) = 1;
              *((_DWORD *)this + 226) = v59;
              *((_BYTE *)this + 910) = 1;
              *((_BYTE *)this + 909) = 1;
            }
            else
            {
              *((_BYTE *)this + 910) = 0;
            }
            *((_DWORD *)this + 225) = 2;
            v71 = off_5C7760[0];
          }
          else
          {
            v71 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486306:
          v60 = ((NPC *)((char *)this + 245852))->CreateChild();
          *((_DWORD *)this + 224) = v60;
          if ( v60 < 0 )
          {
            v54 = g_pCScreenMode_5C7768;
            goto LABEL_201;
          }
          if ( ((CameraCtrl *)this)->HandleCameraEvent(v60, 5) )
          {
            ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), 5);
            ((MainPropUI *)this)->SetPage(0);
            v61 = *((_DWORD *)this + 51446);
            *((_BYTE *)this + 908) = 1;
            *((_DWORD *)this + 226) = v61;
            *((_BYTE *)this + 910) = 1;
            *((_BYTE *)this + 909) = 1;
          }
          else
          {
            *((_BYTE *)this + 910) = 0;
          }
          *((_DWORD *)this + 225) = 5;
          goto LABEL_200;
        case 10486307:
          v62 = ((NPC *)((char *)this + 247060))->CreateChild();
          *((_DWORD *)this + 224) = v62;
          if ( v62 >= 0 )
          {
            if ( ((CameraCtrl *)this)->HandleCameraEvent(v62, 6) )
            {
              ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), 6);
              ((MainPropUI *)this)->SetPage(0);
              v63 = *((_DWORD *)this + 51446);
              *((_BYTE *)this + 908) = 1;
              *((_DWORD *)this + 226) = v63;
              *((_BYTE *)this + 910) = 1;
              *((_BYTE *)this + 909) = 1;
            }
            else
            {
              *((_BYTE *)this + 910) = 0;
            }
            *((_DWORD *)this + 225) = 6;
            v71 = off_5C7760[0];
          }
          else
          {
            v71 = g_pCScreenMode_5C7768;
          }
          break;
        case 10486308:
          v64 = ((NPC *)((char *)this + 248268))->CreateChild();
          *((_DWORD *)this + 224) = v64;
          if ( v64 < 0 )
          {
            v71 = g_pCScreenMode_5C7768;
            break;
          }
          if ( !((CameraCtrl *)this)->InitBlendState(v64, 7) )
            return 1;
          ((MainPropUI *)this)->FindValidSaveSlot();
          v75 = (RoleAtt *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*((_DWORD *)this + 75 * *((unsigned __int8 *)this + *((_DWORD *)this + 224) + 307032) + 232));
          sprintf((char *const)&this->m_ScreenPlane + 4, g_szSceneUIText);
          v65 = sub_458F70(&v75->Remark[90], (int)asc_5B74B8, (LPSTR)this + 360);
          if ( lstrlenA(v65) <= 0 )
          {
            ((RoleAtt *)v66)->FormatAttributeText();
            lstrcpyA((LPSTR)&this->m_ScreenPlane + 4, v67);
          }
          else
          {
            lstrcpyA((LPSTR)&this->m_ScreenPlane + 4, v65);
          }
          ((UICaption *)((char *)this + 212144))->SetEnable((int)(&this->m_ScreenPlane + 1), 0);
          ((UICaption *)((char *)this + 211992))->SetEnable((int)this + 360, 0);
          ((UICaption *)(UICaption *)this + 2213)->SetEnable((int)this + 300 * *((unsigned __int8 *)this + *((_DWORD *)this + 224) + 307032) + 932, 1);
          v68 = &v75->Remark[30];
          if ( !strcmp(&v75->Remark[30], g_szSceneUIText) )
            sprintf((char *const)&this->m_ScreenPlane + 4, byte_5967B0, "NONE");
          else
            sprintf((char *const)&this->m_ScreenPlane + 4, "Item\\%s\\%s.pol", &v75->Remark[30], &v75->Remark[30]);
          ((PalScript *)((char *)this + 249548))->LoadModel((const char *)&this->m_ScreenPlane + 4, 0);
          if ( !strcmp(&v75->Remark[30], g_szSceneUIText) )
          {
            sprintf((char *const)&this->m_ScreenPlane + 4, byte_5967B0, "NONE");
          }
          else
          {
            Buffer = 0;
            memset(v79, 0, sizeof(v79));
            v80 = 0;
            v81 = 0;
            sprintf(&Buffer, "%s%s", v68, &v75->Remark[60]);
            sprintf((char *const)&this->m_ScreenPlane + 4, "Item\\%s\\%s.tga", v68, &Buffer);
          }
          ((gbGeomNode *)*((gbGeomNode **)this + 62391))->ReplaceTexture((const char *)&this->m_ScreenPlane + 4);
          *((_DWORD *)this + 62388) = 1;
          *((_DWORD *)this + 225) = 7;
          sprintf((char *const)&this->m_ScreenPlane + 4, "\\n            %s", (const char *)dword_DC8D3C);
          ((UICaption *)((char *)this + 208980))->SetEnable((int)(&this->m_ScreenPlane + 1), 0);
          ((UIRoleSelect *)((char *)this + 208524))->SetByte(1);
          ((MainPropUI *)this)->SetPage(0);
LABEL_200:
          v54 = off_5C7760[0];
LABEL_201:
          v71 = v54;
          break;
        default:
          return 1;
      }
LABEL_202:
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v71, 1);
      return 1;
    case 1009:
      return 1;
    case 1010:
      if ( *((_BYTE *)this + 3336) )
        return 1;
      if ( *((int *)this + 226) >= 0 )
      {
        *((_BYTE *)this + 909) = 0;
        *((_BYTE *)this + 911) = 0;
        *((_BYTE *)this + 910) = 0;
        *((_BYTE *)this + 908) = 0;
        *((_DWORD *)this + 225) = -1;
        *((_DWORD *)this + 226) = -1;
        ((MainPropUI *)this)->SetPage(1u);
        v35 = (char *)this + 217324;
        v36 = 5;
        do
        {
          (**(void ( ***)(char *, _DWORD))v35)(v35, 0);
          v35 += 4892;
          --v36;
        }
        while ( v36 );
      }
      return 1;
    case 1020:
      if ( *((_BYTE *)this + 3336) )
        return 1;
      v22 = 0;
      v23 = g_MonsterEntryTable;
      while ( nMsg != *v23 )
      {
        ++v23;
        ++v22;
        if ( (int)v23 >= (int)&g_ArcSceneMonsterTable )
          return 1;
      }
      if ( *((int *)this + 224) >= 0 && *((_BYTE *)this + 908) )
      {
        if ( ((ScriptSystem *)this)->ProcessScriptEvent(*((_DWORD *)this + 226), v22, *((_DWORD *)this + 224)) )
        {
          LineupUI::LoadRoleData();
          ((MainPropUI *)this)->SetPage(1u);
        }
        if ( !*((_BYTE *)this + 909) )
        {
          *((_BYTE *)this + 908) = 0;
          *((_DWORD *)this + 226) = -1;
          *((_BYTE *)this + 911) = 0;
          *((_BYTE *)this + 910) = 0;
        }
        return 1;
      }
      else
      {
        v24 = *((_BYTE *)this + 909);
        *((_DWORD *)this + 51446) = v22;
        if ( !v24 )
        {
          ((MagicUI *)this)->UpdateViewListItems();
          ((MainPropUI *)this)->DisplayCaption(*((_DWORD *)this + 51446));
          v25 = (char *)this + 217324;
          v26 = 5;
          do
          {
            (**(void ( ***)(char *, _DWORD))v25)(v25, 0);
            v25 += 4892;
            --v26;
          }
          while ( v26 );
        }
        return 1;
      }
    default:
      return ((PalScript *)this)->OnMessage(v82, nMsg, wParam);
  }
  do
  {
    if ( nMsg == *v6 )
    {
      v73 = v5;
      if ( *((_BYTE *)this + 910) )
      {
        if ( !*((_BYTE *)this + 909) )
          goto LABEL_35;
        v12 = 5;
        v13 = (char *)this + 217324;
        nVala = (char *)this
              + 9536 * *((_DWORD *)this + 226)
              + 1192 * *((_DWORD *)this + 225)
              + 12 * *((_DWORD *)this + 224)
              + 3356;
        do
        {
          (**(void ( ***)(char *, _DWORD))v13)(v13, 0);
          v13 += 4892;
          --v12;
        }
        while ( v12 );
        v14 = *(_BYTE *)(*((_DWORD *)nVala + 2) + 577);
        if ( v14 == 1 )
        {
          ((CameraCtrl *)this)->CalcStatPower((int)nVala);
          if ( v15 )
            (**((void ( ***)(char *, int))this + 1223 * v73 + 54331))((char *)this + 4892 * v73 + 217324, 1);
          else
            ((CameraCtrl *)this)->ProcessCameraTask(*((_DWORD *)this + 224), *((_DWORD *)this + 225));
        }
        else if ( v14 == 2 )
        {
          v16 = 0;
          v17 = (char *)this + 217324;
          do
          {
            if ( *((_BYTE *)this + v16 + 877) )
            {
              ((CameraCtrl *)this)->CalcStatPower((int)nVala);
              if ( v18 )
                (**(void ( ***)(char *, int))v17)(v17, 1);
              else
                (**(void ( ***)(char *, _DWORD))v17)(v17, 0);
            }
            ++v16;
            v17 += 4892;
          }
          while ( v16 < 5 );
        }
      }
      if ( *((_BYTE *)this + 909) )
      {
LABEL_36:
        v71 = (const char *)off_5C775C;
        goto LABEL_202;
      }
LABEL_35:
      *((_DWORD *)this + 51446) = v73;
      ((MagicUI *)this)->UpdateViewListItems();
      ((MainPropUI *)this)->DisplayCaption(v73);
      goto LABEL_36;
    }
    ++v6;
    ++v5;
  }
  while ( (int)v6 < (int)&g_ArcSceneMonsterTable );
  v7 = &off_56C548;
  v8 = 0;
  nVal = &off_56C548;
  while ( v4 != *v7 )
  {
LABEL_17:
    ++v7;
    ++v8;
    nVal = v7;
    if ( (int)v7 >= (int)g_MonsterEntryTable )
      goto LABEL_39;
  }
  if ( !*((_BYTE *)this + 3336) )
  {
    ((MagicUI *)this)->InitUILayout();
    v70 = off_5C775C;
    v9 = CScreenMode::GetInstance();
    ((CScreenMode *)v9)->AudioSetPosition(v70, 1);
    *((_DWORD *)this + 224) = -1;
    *((_BYTE *)this + 909) = 0;
    *((_BYTE *)this + 911) = 0;
    *((_BYTE *)this + 910) = 0;
    ((MainPropUI *)this)->SetPage(1u);
    v10 = (char *)this + 217324;
    v11 = 5;
    do
    {
      (**(void ( ***)(char *, _DWORD))v10)(v10, 0);
      v10 += 4892;
      --v11;
    }
    while ( v11 );
    v7 = nVal;
    v4 = (const char *)nMsg;
    goto LABEL_17;
  }
  v19 = (char *)this + 237060;
  v20 = 8;
  do
  {
    sub_445E50((int)v19);
    v19 += 344;
    --v20;
  }
  while ( v20 );
LABEL_39:
  switch ( (unsigned int)v4 )
  {
    case 0xA00102u:
    case 0xA00104u:
    case 0xA00105u:
    case 0xA00106u:
    case 0xA00107u:
    case 0xA00108u:
    case 0xA00109u:
    case 0xA00110u:
      v72 = off_5C775C;
      v21 = CScreenMode::GetInstance();
      ((CScreenMode *)v21)->AudioSetPosition(v72, 1);
      ((MainEquipUI *)*((MainEquipUI **)this + 12758))->HandleMessage();
      break;
    default:
      return 1;
  }
  return 1;
}

// 0x004B4820
void RenderTarget::SetVisible(BOOL bVisible)
{
  LOBYTE(this->m_bVisible) = bVisible;
}

// 0x004B4840
void RenderTarget::SetField084()
{
  float v1; // [esp+0x4] [ebp+0x4]

  this->m_fRenderIntensity = v1;
}

// 0x004B4850
void RenderTarget::SetColor(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b)
{
  int v5; // edi

  BYTE2(this->m_nAlpha) = r;
  BYTE1(this->m_nAlpha) = g;
  LOBYTE(this->m_nAlpha) = b;
  v5 = 16 * (rand() % 12);
  BYTE2(this->m_nColor) = (__int64)*(float *)((char *)&unk_5D3C68 + v5);
  BYTE1(this->m_nColor) = (__int64)*(float *)(v5 + 6110308);
  LOBYTE(this->m_nColor) = (__int64)*(float *)(v5 + 6110304);
}

// 0x004B48B0
void RenderTarget::SetAlpha(unsigned __int8 nAlpha)
{
  HIBYTE(this->m_nAlpha) = nAlpha;
  HIBYTE(this->m_nColor) = (__int64)*((float *)&unk_5D3C6C + 4 * (rand() % 12));
}

// 0x004B48E0
void RenderTarget::SetSize(int nHeight)
{
  int v2; // [esp+0xC] [ebp+0x8]

  *((_DWORD *)this + 143) = nHeight;
  *((_DWORD *)this + 144) = v2;
  this->m_nHalfWidth = nHeight / 2;
  this->m_nHalfHeight = v2 / 2;
}

// 0x004B4910
void RenderTarget::SetState()
{
  int v1; // [esp+0x4] [ebp+0x4]

  *((_DWORD *)this + 145) = v1;
}

// 0x004B4920
gbVFileSystem * RenderTarget::LoadTexture(const char *szFilename)
{
  char *m_szTexPath; // edi
  gbVFileSystem *result; // eax
  gbRefObject *v5; // ecx
  gbTexture *v6; // eax

  m_szTexPath = this->m_szTexPath;
  result = (gbVFileSystem *)lstrcpyA(this->m_szTexPath, szFilename);
  if ( m_szTexPath )
  {
    v5 = (gbRefObject *)*((_DWORD *)this + 104);
    if ( v5 )
    {
      ((gbRefObject *)v5)->Release();
      *((_DWORD *)this + 104) = 0;
    }
    v6 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, m_szTexPath);
    *((_DWORD *)this + 104) = v6;
    if ( v6 )
      ((gbTexture *)v6)->LoadTexture(1);
  }
  return result;
}

// 0x004B49C0
void RenderTarget::UpdateTransform(float fX, float fY)
{
  double v4; // st7
  __int64 v5; // rax
  double m_nHeight; // st7
  int v7; // eax
  gbTexture_D3D *m_Texture; // ebx
  int v9; // edi
  int v10; // eax
  int m_nHalfWidth; // ecx
  double v12; // st7
  double v13; // st6
  double v14; // st6
  int m_nHalfHeight; // ecx
  double v16; // st7
  int fXb; // [esp+0xC] [ebp+0x4]
  float fXa; // [esp+0xC] [ebp+0x4]

  this->m_fOffsetParam = fX;
  this->m_fRender = fY;
  this->m_fX = fX;
  this->m_fY = fY;
  this->m_Texture = (gbTexture_D3D *)(__int64)fY;
  v4 = (double)(this->m_nWidth / 2);
  this->m_iMode = (__int64)(fX - v4);
  v5 = (__int64)(v4 + fX);
  m_nHeight = (double)this->m_nHeight;
  this->m_nRenderX = v5;
  this->m_nRenderY = (__int64)(m_nHeight + fY);
  v7 = rand();
  m_Texture = this->m_Texture;
  v9 = this->m_nHeight;
  this->m_fRenderX = (float)(this->m_iMode + v7 % this->m_nWidth);
  v10 = rand();
  m_nHalfWidth = this->m_nHalfWidth;
  v12 = (double)((int)m_Texture + v10 % v9);
  fXb = this->m_nRenderX - m_nHalfWidth;
  this->m_fRenderY = v12;
  v13 = (double)fXb;
  if ( v13 < this->m_fRenderX )
    this->m_fRenderX = v13;
  v14 = (double)(this->m_iMode + m_nHalfWidth);
  if ( v14 > this->m_fRenderX )
    this->m_fRenderX = v14;
  m_nHalfHeight = this->m_nHalfHeight;
  fXa = (float)(this->m_nRenderY - m_nHalfHeight);
  if ( v12 > fXa )
    this->m_fRenderY = fXa;
  v16 = (double)((int)m_Texture + m_nHalfHeight);
  if ( v16 > this->m_fRenderY )
    this->m_fRenderY = v16;
  *(float *)&this->m_nDefaultH = (double)v9 + this->m_fRender;
}

// 0x004B4B10
void RenderTarget::CalcRenderDimensions(int nVal, int nVal2)
{
  double m_fRender; // st7
  __int64 v5; // rax
  double v6; // st7
  double m_fOffsetParam; // st6
  __int64 v8; // rax
  double v9; // st7
  int v10; // eax
  int m_nHeight; // edi
  gbTexture_D3D *m_Texture; // ebx
  int v13; // eax
  int m_nHalfWidth; // ecx
  double v15; // st7
  double v16; // st6
  double v17; // st6
  int m_nHalfHeight; // ecx
  double v19; // st7
  int nVala; // [esp+0x10] [ebp+0x4]
  int nVal2b; // [esp+0x14] [ebp+0x8]
  float nVal2a; // [esp+0x14] [ebp+0x8]

  this->m_nWidth = nVal;
  this->m_nHeight = nVal2;
  m_fRender = this->m_fRender;
  nVala = nVal / 2;
  this->m_nHalfW = nVala;
  *(_DWORD *)&this->m_nHalfH = nVal2 / 2;
  v5 = (__int64)m_fRender;
  v6 = (double)nVala;
  m_fOffsetParam = this->m_fOffsetParam;
  this->m_Texture = (gbTexture_D3D *)v5;
  v8 = (__int64)(m_fOffsetParam - v6);
  v9 = v6 + this->m_fOffsetParam;
  this->m_iMode = v8;
  this->m_nRenderX = (__int64)v9;
  this->m_nRenderY = (__int64)((double)nVal2 + this->m_fRender);
  v10 = rand();
  m_nHeight = this->m_nHeight;
  m_Texture = this->m_Texture;
  this->m_fRenderX = (float)(this->m_iMode + v10 % this->m_nWidth);
  v13 = rand();
  m_nHalfWidth = this->m_nHalfWidth;
  v15 = (double)((int)m_Texture + v13 % m_nHeight);
  nVal2b = this->m_nRenderX - m_nHalfWidth;
  this->m_fRenderY = v15;
  v16 = (double)nVal2b;
  if ( v16 < this->m_fRenderX )
    this->m_fRenderX = v16;
  v17 = (double)(this->m_iMode + m_nHalfWidth);
  if ( v17 > this->m_fRenderX )
    this->m_fRenderX = v17;
  m_nHalfHeight = this->m_nHalfHeight;
  nVal2a = (float)(this->m_nRenderY - m_nHalfHeight);
  if ( v15 > nVal2a )
    this->m_fRenderY = nVal2a;
  v19 = (double)((int)m_Texture + m_nHalfHeight);
  if ( v19 > this->m_fRenderY )
    this->m_fRenderY = v19;
  *(float *)&this->m_nDefaultH = (double)m_nHeight + this->m_fRender;
}

// 0x004B4C60
void RenderTarget::Render(int nY, int nWidth, int nHeight)
{
  int v5; // eax
  gbTexture_D3D *m_Texture; // ebx
  int m_nHeight; // edi
  int v8; // eax
  int m_nHalfWidth; // ecx
  double v10; // st7
  double v11; // st6
  double v12; // st6
  int m_nHalfHeight; // ecx
  double v14; // st7
  int nYb; // [esp+0x18] [ebp+0x4]
  float nYa; // [esp+0x18] [ebp+0x4]
  int v17; // [esp+0x24] [ebp+0x10]

  this->m_nWidth = nHeight - nY;
  this->m_nHeight = v17 - nWidth;
  this->m_nHalfW = (nHeight - nY) / 2;
  *(_DWORD *)&this->m_nHalfH = (v17 - nWidth) / 2;
  this->m_iMode = nY;
  this->m_Texture = (gbTexture_D3D *)nWidth;
  this->m_nRenderX = nHeight;
  this->m_nRenderY = v17;
  v5 = rand();
  m_Texture = this->m_Texture;
  m_nHeight = this->m_nHeight;
  this->m_fRenderX = (float)(this->m_iMode + v5 % this->m_nWidth);
  v8 = rand();
  m_nHalfWidth = this->m_nHalfWidth;
  v10 = (double)((int)m_Texture + v8 % m_nHeight);
  nYb = this->m_nRenderX - m_nHalfWidth;
  this->m_fRenderY = v10;
  v11 = (double)nYb;
  if ( v11 < this->m_fRenderX )
    this->m_fRenderX = v11;
  v12 = (double)(this->m_iMode + m_nHalfWidth);
  if ( v12 > this->m_fRenderX )
    this->m_fRenderX = v12;
  m_nHalfHeight = this->m_nHalfHeight;
  nYa = (float)(this->m_nRenderY - m_nHalfHeight);
  if ( v10 > nYa )
    this->m_fRenderY = nYa;
  v14 = (double)((int)m_Texture + m_nHalfHeight);
  if ( v14 > this->m_fRenderY )
    this->m_fRenderY = v14;
  *(float *)&this->m_nDefaultH = (double)m_nHeight + this->m_fRender;
}

// 0x004B4D80
void RenderTarget::SetOffset(int nOffY)
{
  int v2; // [esp+0x8] [ebp+0x8]

  this->m_nOffsetX = nOffY;
  this->m_nOffsetY = v2;
}

// 0x004B4DA0
void RenderTarget::SetScale(int nScaleY)
{
  int v2; // [esp+0x8] [ebp+0x8]

  this->m_nScaleX = nScaleY;
  this->m_nScaleY = v2;
}

// 0x004BB050
void RenderTarget::ReadVFile(gbVFile *pFile)
{
  ((gbVFileSystem *)g_pVFileSys)->Read(this, 0x40u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read(&this->m_fileHeader, 4u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read(&this->m_fRenderX, 4u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read(&this->m_fFileParam, 4u, pFile);
}

// 0x004BB0B0
int RenderTarget::ClearTexture()
{
  this->m_iMode = 0;
  this->m_Texture = 0;
  this->m_nRenderX = 0;
  this->m_fRenderX = 0.0;
  this->m_fileHeader = 0.0;
  this->_field_03C = 0;
  this->_field_038 = 0;
  this->m_fX = 0.0;
  this->_field_02C = 0.0;
  *(_DWORD *)&this->_field_028 = 0;
  this->m_nHeight = 0;
  this->m_nHalfHeight = 0;
  this->m_nHalfWidth = 0;
  *(_DWORD *)&this->m_nHalfH = 0;
  this->m_nHalfW = 0;
  this->m_fRenderY = 1.0;
  this->m_fY = 1.0;
  this->m_nWidth = 1065353216;
  this->m_nRenderY = 1065353216;
  return 1065353216;
}

// 0x004BB0F0
int RenderTarget::ApplyScale(float fVal)
{
  double v2; // st7
  double v4; // st7

  v2 = 1.0 / this->m_fInvScale;
  this->m_fileData = v2 * this->m_fileData;
  this->m_fFileParam = v2 * this->m_fFileParam;
  *(float *)&this->m_nColor = v2 * *(float *)&this->m_nColor;
  v4 = 1.0 / this->m_fInvScale;
  this->m_fileHeader = v4 * this->m_fileHeader;
  this->m_fRenderX = v4 * this->m_fRenderX;
  this->m_fRenderY = v4 * this->m_fRenderY;
  this->m_fileData = fVal * this->m_fileData;
  this->m_fFileParam = fVal * this->m_fFileParam;
  *(float *)&this->m_nColor = fVal * *(float *)&this->m_nColor;
  this->m_fileHeader = fVal * this->m_fileHeader;
  this->m_fRenderX = fVal * this->m_fRenderX;
  this->m_fRenderY = fVal * this->m_fRenderY;
  this->m_fInvScale = fVal;
  return LODWORD(fVal);
}

// 0x004BB180
int RenderTarget::fn_4BB180(int nVal)
{
  *((_DWORD *)this + 89) = nVal;
  return nVal;
}

// 0x004BB200
void RenderTarget::ScreenToLocal(float *pOutX, float *pInX, float *pInY)
{
  double v4; // st7

  v4 = (g_fRenderHeight - pOutX[1]) / g_fRenderWidth * (*((float *)this + 54) - *((float *)this + 51))
     + *((float *)this + 51);
  *pInX = (*pOutX - *(float *)&g_nTextureDefault) / g_fConst400 * (*((float *)this + 53) - *((float *)this + 50))
        + *((float *)this + 50);
  pInX[1] = v4;
}

// 0x004BB260
void RenderTarget::LoadFromFile(gbVFile *pFile)
{
  ((gbVFileSystem *)g_pVFileSys)->Read(this, 4u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read(&this->m_Texture, 4u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read(&this->m_nRenderX, 0x40u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read(&this->m_fRenderY, 0x80u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read((char *)this + 212, 0xCu, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read(this + 1, 0xCu, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read((char *)this + 224, 0x2D0u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read((char *)this + 944, 0x2D0u, pFile);
  ((gbVFileSystem *)g_pVFileSys)->Read((char *)this + 1664, 0xE34u, pFile);
}

// 0x004BC7B0
void RenderTarget::UpdateTimeStep()
{
  ;
}

// 0x004BC8A0
int RenderTarget::RenderToTexture()
{
  ParticleEffect *v1; // ebp
  float xy; // ebx
  int v3; // edi
  int particle_num; // eax
  sg_emitter *pemitter; // eax
  gbTexture_D3D *v6; // edx
  double v7; // st7
  int v8; // eax
  int emittedto; // eax
  float *p_a; // esi
  double v11; // st7
  double v12; // st7
  int v13; // ebp
  int v14; // edi
  __int64 v15; // rax
  double v16; // st7
  int v17; // ebp
  int v18; // edi
  __int64 v19; // rax
  double v20; // st7
  double v21; // st6
  int v22; // ebp
  int v23; // edi
  __int64 v24; // rax
  double v25; // st7
  double v26; // st6
  int v27; // ebp
  int v28; // edi
  __int64 v29; // rax
  int v30; // ecx
  int v31; // eax
  IDirect3DBaseTexture9 *pTex; // [esp+C8h] [ebp-0x224]
  float v34; // [esp+C8h] [ebp-0x224]
  float v35; // [esp+DCh] [ebp-0x210]
  float v36; // [esp+E0h] [ebp-0x20C]
  float v37; // [esp+E4h] [ebp-0x208]
  float v38; // [esp+E8h] [ebp-0x204]
  int v39; // [esp+ECh] [ebp-0x200]
  int v40; // [esp+ECh] [ebp-0x200]
  int v41; // [esp+ECh] [ebp-0x200]
  float v42; // [esp+F0h] [ebp-0x1FC]
  int v43; // [esp+F0h] [ebp-0x1FC]
  float v44; // [esp+F4h] [ebp-0x1F8]
  float v45; // [esp+F8h] [ebp-0x1F4] BYREF
  float v46; // [esp+FCh] [ebp-0x1F0]
  float v47[2]; // [esp+0x100] [ebp-0x1EC]
  float v48; // [esp+0x108] [ebp-0x1E4]
  int v49; // [esp+0x10C] [ebp-0x1E0]
  int v50; // [esp+0x110] [ebp-0x1DC]
  float v51; // [esp+0x114] [ebp-0x1D8]
  float v52; // [esp+0x118] [ebp-0x1D4] BYREF
  float v53; // [esp+0x11C] [ebp-0x1D0]
  float v54; // [esp+0x120] [ebp-0x1CC]
  char *v55; // [esp+0x128] [ebp-0x1C4]
  float v56; // [esp+0x12C] [ebp-0x1C0]
  RenderTarget *v57; // [esp+0x130] [ebp-0x1BC]
  int v58; // [esp+0x134] [ebp-0x1B8]
  gbMatrixStack *v59; // [esp+0x138] [ebp-0x1B4]
  float v60[2]; // [esp+0x13C] [ebp-0x1B0]
  int v61; // [esp+0x144] [ebp-0x1A8]
  float v62[2]; // [esp+0x148] [ebp-0x1A4]
  float v63; // [esp+0x150] [ebp-0x19C]
  float v64; // [esp+0x154] [ebp-0x198]
  int v65[7]; // [esp+0x158] [ebp-0x194] BYREF
  float v66; // [esp+0x174] [ebp-0x178]
  float v67; // [esp+0x178] [ebp-0x174]
  float v68; // [esp+0x180] [ebp-0x16C]
  float v69; // [esp+0x184] [ebp-0x168]
  float v70; // [esp+0x18C] [ebp-0x160]
  float v71; // [esp+0x190] [ebp-0x15C]
  float v72; // [esp+0x198] [ebp-0x154]
  float v73; // [esp+0x19C] [ebp-0x150]
  float v74; // [esp+0x1A4] [ebp-0x148]
  float v75; // [esp+0x1A8] [ebp-0x144]
  float v76; // [esp+0x1B0] [ebp-0x13C]
  float v77; // [esp+0x1B4] [ebp-0x138]
  float v78; // [esp+0x1BC] [ebp-0x130]
  float v79; // [esp+0x1C0] [ebp-0x12C]
  _DWORD v80[4]; // [esp+0x1C4] [ebp-0x128] BYREF
  float v81; // [esp+0x1D4] [ebp-0x118]
  float v82; // [esp+0x1D8] [ebp-0x114]
  _DWORD v83[4]; // [esp+0x1DC] [ebp-0x110] BYREF
  float v84; // [esp+0x1EC] [ebp-0x100]
  float v85; // [esp+0x1F0] [ebp-FCh]
  float v86; // [esp+0x1F8] [ebp-F4h]
  float v87; // [esp+0x1FC] [ebp-F0h]
  float v88; // [esp+0x204] [ebp-E8h]
  float v89; // [esp+0x208] [ebp-E4h]
  int v90[16]; // [esp+0x20C] [ebp-E0h] BYREF
  float v91[16]; // [esp+0x24C] [ebp-A0h] BYREF
  float v92[24]; // [esp+0x28C] [ebp-0x60] BYREF

  v1 = (ParticleEffect *)this;
qmemcpy(v91, ((gbGfxManager *)gfxMgr)->GetWorldMatrix(), sizeof(v91));
  ((ParticleEffect *)v1)->UpdateParticles(v1->deltatime, SLODWORD(v91[12]), SLODWORD(v91[13]), SLODWORD(v91[14]));
  xy = gfxMgr[1].InvViewMatrix.xy;
  v59 = gfxMgr->pMatrixStack[1];
  ((gbMatrixStack *)v59)->Push();
  if ( v1->npwmr != 1 )
    ((gbGfxManager *)gfxMgr)->IdentityWorldMatrix();
  (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 60))(gfxMgr);
  qmemcpy(v91, ((gbGfxManager *)gfxMgr)->GetViewMatrix(), sizeof(v91));
  *(float *)&v90[12] = v91[12];
  *(float *)&v90[13] = v91[13];
  *(float *)&v90[14] = v91[14];
  *(float *)v80 = v91[0];
  *(float *)&v80[1] = v91[4];
  *(float *)&v80[2] = v91[8];
  *(float *)v83 = v91[1];
  *(float *)&v83[1] = v91[5];
  *(float *)&v83[2] = v91[9];
  v3 = 0;
  v90[11] = 0;
  memset(&v90[6], 0, 16);
  memset(&v90[1], 0, 16);
  v90[15] = 1065353216;
  v90[10] = 1065353216;
  v90[5] = 1065353216;
  v90[0] = 1065353216;
  *(float *)v65 = v91[2];
  *(float *)&v65[1] = v91[6];
  *(float *)&v65[2] = v91[10];
  (*(void ( **)(float, _DWORD))(*(_DWORD *)LODWORD(xy) + 368))(COERCE_FLOAT(LODWORD(xy)), 0);
  (*(void ( **)(float, int))(*(_DWORD *)LODWORD(xy) + 356))(COERCE_FLOAT(LODWORD(xy)), 322);
  (*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(COERCE_FLOAT(LODWORD(xy)), 7, 1);
  (*(void ( **)(float, int, _DWORD))(*(_DWORD *)LODWORD(xy) + 228))(COERCE_FLOAT(LODWORD(xy)), 14, 0);
  (*(void ( **)(float, int, _DWORD))(*(_DWORD *)LODWORD(xy) + 228))(COERCE_FLOAT(LODWORD(xy)), 137, 0);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 268))(COERCE_FLOAT(LODWORD(xy)), 0, 1, 4);
  (*(void ( **)(float, _DWORD, int, _DWORD))(*(_DWORD *)LODWORD(xy) + 268))(COERCE_FLOAT(LODWORD(xy)), 0, 2, 0);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 268))(COERCE_FLOAT(LODWORD(xy)), 0, 3, 2);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 276))(COERCE_FLOAT(LODWORD(xy)), 0, 6, 2);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 276))(COERCE_FLOAT(LODWORD(xy)), 0, 5, 2);
  (*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(COERCE_FLOAT(LODWORD(xy)), 27, 1);
  (*(void ( **)(float, _DWORD, int, int))(*(_DWORD *)LODWORD(xy) + 268))(COERCE_FLOAT(LODWORD(xy)), 0, 4, 7);
  (*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(COERCE_FLOAT(LODWORD(xy)), 19, 2);
  (*(void ( **)(float, int, int))(*(_DWORD *)LODWORD(xy) + 228))(COERCE_FLOAT(LODWORD(xy)), 20, 2);
  particle_num = v1->particle_num;
  v1->active_parnum = 0;
  v49 = 0;
  if ( particle_num > 0 )
  {
    do
    {
      if ( v1->ecenable[v3 + 1] )
      {
        pemitter = v1->econtrol[v3].pemitter;
        v6 = v1->m_pTexture[v1->econtrol[v3].emitter_pointer];
        v55 = &v1->name[36952 * v3];
        pTex = v6->pTex;
// [VFTABLE] v51 = 1.0 / (double)*((int *)&pemitter->direction_graph.__vftable + 46);
// [VFTABLE] v7 = (double)*((int *)&pemitter->direction_graph.__vftable + 45);
        v8 = *(_DWORD *)LODWORD(xy);
        v48 = 1.0 / v7;
        (*(void ( **)(float, _DWORD, IDirect3DBaseTexture9 *))(v8 + 260))(COERCE_FLOAT(LODWORD(xy)), 0, pTex);
        emittedto = v1->emittedto;
        v50 = 0;
        if ( emittedto > 0 )
        {
          p_a = &v1->econtrol[v3].particle_array[0].currgbcolor.a;
          do
          {
            if ( *((_DWORD *)p_a - 19) )
            {
              ++v1->active_parnum;
              v36 = *(p_a - 7);
              v37 = *(p_a - 6);
              v38 = *(p_a - 5);
              v44 = (double)*((int *)p_a - 15) * v51;
              v42 = (double)*((int *)p_a - 14) * v48;
              v34 = p_a[2] * 0.01745329222222222;
              sub_543C42((int)v90, (int)v65, v34);
              sub_5427A5(&v52, v80, v90);
              sub_5427A5(&v45, v83, v90);
              v35 = *(p_a - 4) * 0.5 * *(float *)(*((_DWORD *)v55 + 9306) + 356);
              v11 = -v52;
              v56 = v11;
              *(float *)&v58 = -v53;
              v61 = v58;
              v60[0] = -v54;
              v62[0] = v60[0];
              v88 = *(float *)&v58 - v46;
              v89 = v60[0] - v47[0];
              v66 = v88 * v35;
              v67 = v89 * v35;
              v81 = v66 + v37;
              v92[1] = v81;
              v82 = v67 + v38;
              v92[0] = (v11 - v45) * v35 + v36;
              v12 = *(p_a - 2);
              v92[2] = v82;
              if ( v12 < 1.0 )
              {
                if ( *(p_a - 2) > 0.0 )
                  v39 = (__int64)(*(p_a - 2) * 255.0 + 0.5);
                else
                  v39 = 0;
              }
              else
              {
                v39 = 255;
              }
              if ( *(p_a - 1) < 1.0 )
              {
                if ( *(p_a - 1) > 0.0 )
                  v13 = (__int64)(*(p_a - 1) * 255.0 + 0.5);
                else
                  v13 = 0;
              }
              else
              {
                v13 = 255;
              }
              if ( *p_a < 1.0 )
              {
                if ( *p_a > 0.0 )
                  v14 = (__int64)(*p_a * 255.0 + 0.5);
                else
                  v14 = 0;
              }
              else
              {
                v14 = 255;
              }
              if ( p_a[1] < 1.0 )
              {
                if ( p_a[1] > 0.0 )
                  v15 = (__int64)(p_a[1] * 255.0 + 0.5);
                else
                  LODWORD(v15) = 0;
              }
              else
              {
                LODWORD(v15) = 255;
              }
              v70 = v53 - v46;
              v92[4] = v44;
              v71 = v54 - v47[0];
              v86 = v70 * v35;
              LODWORD(v92[3]) = v14 | ((v13 | ((v39 | ((_DWORD)v15 << 8)) << 8)) << 8);
              v92[5] = v42;
              v87 = v71 * v35;
              v74 = v86 + v37;
              v92[7] = v74;
              v75 = v87 + v38;
              v92[6] = (v52 - v45) * v35 + v36;
              v16 = *(p_a - 2);
              v92[8] = v75;
              if ( v16 < 1.0 )
              {
                if ( *(p_a - 2) > 0.0 )
                  v40 = (__int64)(*(p_a - 2) * 255.0 + 0.5);
                else
                  v40 = 0;
              }
              else
              {
                v40 = 255;
              }
              if ( *(p_a - 1) < 1.0 )
              {
                if ( *(p_a - 1) > 0.0 )
                  v17 = (__int64)(*(p_a - 1) * 255.0 + 0.5);
                else
                  v17 = 0;
              }
              else
              {
                v17 = 255;
              }
              if ( *p_a < 1.0 )
              {
                if ( *p_a > 0.0 )
                  v18 = (__int64)(*p_a * 255.0 + 0.5);
                else
                  v18 = 0;
              }
              else
              {
                v18 = 255;
              }
              if ( p_a[1] < 1.0 )
              {
                if ( p_a[1] > 0.0 )
                  v19 = (__int64)(p_a[1] * 255.0 + 0.5);
                else
                  LODWORD(v19) = 0;
              }
              else
              {
                LODWORD(v19) = 255;
              }
              v20 = v44 + v51;
              v92[10] = v20;
              v84 = v46 + v53;
              v85 = v47[0] + v54;
              LODWORD(v92[9]) = v18 | ((v17 | ((v40 | ((_DWORD)v19 << 8)) << 8)) << 8);
              v92[11] = v42;
              v78 = v84 * v35;
              v79 = v85 * v35;
              v63 = v78 + v37;
              v92[13] = v63;
              v64 = v79 + v38;
              v92[12] = (v45 + v52) * v35 + v36;
              v21 = *(p_a - 2);
              v92[14] = v64;
              if ( v21 < 1.0 )
              {
                if ( *(p_a - 2) > 0.0 )
                  v41 = (__int64)(*(p_a - 2) * 255.0 + 0.5);
                else
                  v41 = 0;
              }
              else
              {
                v41 = 255;
              }
              if ( *(p_a - 1) < 1.0 )
              {
                if ( *(p_a - 1) > 0.0 )
                  v22 = (__int64)(*(p_a - 1) * 255.0 + 0.5);
                else
                  v22 = 0;
              }
              else
              {
                v22 = 255;
              }
              if ( *p_a < 1.0 )
              {
                if ( *p_a > 0.0 )
                  v23 = (__int64)(*p_a * 255.0 + 0.5);
                else
                  v23 = 0;
              }
              else
              {
                v23 = 255;
              }
              if ( p_a[1] < 1.0 )
              {
                if ( p_a[1] > 0.0 )
                  v24 = (__int64)(p_a[1] * 255.0 + 0.5);
                else
                  LODWORD(v24) = 0;
              }
              else
              {
                LODWORD(v24) = 255;
              }
              v92[16] = v20;
              v25 = v42 + v48;
              v92[17] = v25;
              *(float *)&v65[5] = v60[0];
              LODWORD(v92[15]) = v23 | ((v22 | ((v41 | ((_DWORD)v24 << 8)) << 8)) << 8);
              v65[4] = v58;
              v68 = *(float *)&v58 + v46;
              v69 = v60[0] + v47[0];
              v72 = v68 * v35;
              v73 = v69 * v35;
              v76 = v72 + v37;
              v92[19] = v76;
              v77 = v73 + v38;
              v92[18] = (v56 + v45) * v35 + v36;
              v26 = *(p_a - 2);
              v92[20] = v77;
              if ( v26 < 1.0 )
              {
                if ( *(p_a - 2) > 0.0 )
                  v43 = (__int64)(*(p_a - 2) * 255.0 + 0.5);
                else
                  v43 = 0;
              }
              else
              {
                v43 = 255;
              }
              if ( *(p_a - 1) < 1.0 )
              {
                if ( *(p_a - 1) > 0.0 )
                  v27 = (__int64)(*(p_a - 1) * 255.0 + 0.5);
                else
                  v27 = 0;
              }
              else
              {
                v27 = 255;
              }
              if ( *p_a < 1.0 )
              {
                if ( *p_a > 0.0 )
                  v28 = (__int64)(*p_a * 255.0 + 0.5);
                else
                  v28 = 0;
              }
              else
              {
                v28 = 255;
              }
              if ( p_a[1] < 1.0 )
              {
                if ( p_a[1] > 0.0 )
                  v29 = (__int64)(p_a[1] * 255.0 + 0.5);
                else
                  LODWORD(v29) = 0;
              }
              else
              {
                LODWORD(v29) = 255;
              }
              v92[22] = v44;
              v92[23] = v25;
              LODWORD(v92[21]) = v28 | ((v27 | ((v43 | ((_DWORD)v29 << 8)) << 8)) << 8);
              (*(void ( **)(float, int, int, float *, int))(*(_DWORD *)LODWORD(xy) + 332))(
                COERCE_FLOAT(LODWORD(xy)),
                6,
                2,
                v92,
                24);
              v3 = v49;
              v1 = (ParticleEffect *)v57;
            }
            v30 = v1->emittedto;
            p_a += 23;
            ++v50;
          }
          while ( v50 < v30 );
        }
      }
      v31 = v1->particle_num;
      v49 = ++v3;
    }
    while ( v3 < v31 );
  }
  ((gbMatrixStack *)v59)->Pop();
  gfxMgr[1].AllLight[1].attenuation1 = 0.0;
  ((gbGfxManager_D3D *)gfxMgr)->SetTexture(0);
  ((gbRenderEffect *)gfxMgr->pEffectMgr->m_pDefEffect)->Apply();
  return v1->active_parnum;
}

// 0x004BD6C0
char RenderTarget::LoadParticleTextures(const char *pszName)
{
  char *v4; // eax
  char Str[260]; // [esp+0xC] [ebp-0x208] BYREF
  char pszName2[260]; // [esp+0x110] [ebp-0x104] BYREF

  if ( !pszName )
    return 0;
  strcpy(Str, pszName);
  v4 = strrchr(Str, 92);
  if ( !v4 )
    return 0;
  strcpy(pszName2, v4 + 1);
  strcpy(v4, g_szSceneUIText);
  return ((ParticleEffect *)this)->LoadTextures(Str, pszName2);
}

// 0x004BD870
void RenderTarget::GetManagedTexture()
{
  ((gbChain1DNode *)this)->Process();
}

// 0x004BD880
gbParticleEffect * RenderTarget::CreateParticleEffect(int nVal)
{
  gbParticleEffect *v3; // eax
  gbParticleEffect *v4; // esi
  gbParticleEffect *v5; // ecx
  gbParticleEffect *result; // eax

  v3 = (gbParticleEffect *)operator new(0x160u);
  v4 = v3;
  v5 = 0;
  if ( v3 )
  {
    v5 = v4;
  }
  this->m_nDefaultH = (int)v5;
  ((gbParticleEffect *)v5)->LoadFromFile("effect\\gbParticle\\poisonfog.par");
  result = (gbParticleEffect *)this->m_nDefaultH;
  result->SpaceScale = 32.0;
  return result;
}

// 0x004BD900
gbParticleGroup * RenderTarget::UpdateParticleEffect(int nVal)
{
  int m_szPath; // eax
  gbParticleGroup *result; // eax

  m_szPath = this->m_szPath;
  if ( !m_szPath )
    return (*(gbParticleGroup *( **)(int))(*(_DWORD *)this->m_nDefaultH + 20))(this->m_nDefaultH);
  result = (gbParticleGroup *)(m_szPath - 1);
  if ( !result )
  {
    (*(void ( **)(int))(*(_DWORD *)this->m_nDefaultH + 20))(this->m_nDefaultH);
    result = ((gbParticleEffect *)this->m_nDefaultH)->GetParticleGroup(0);
    if ( result->nAlivePart <= 0 )
      this->m_szPath = -1;
  }
  return result;
}

// 0x004BD950
int RenderTarget::Stop(int nVal)
{
  if ( this->m_szPath == -1 )
    return 0;
  (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_nDefaultH + 16))(this->m_nDefaultH, 0);
  return 1;
}

// 0x004BD970
int RenderTarget::ReleaseDefault()
{
  int ( ***m_nDefaultH)(_DWORD, int); // ecx
  int result; // eax

  m_nDefaultH = (int ( ***)(_DWORD, int))this->m_nDefaultH;
  if ( m_nDefaultH )
  {
    result = (**m_nDefaultH)(m_nDefaultH, 1);
    this->m_nDefaultH = 0;
  }
  return result;
}

// 0x004BD990
void RenderTarget::SetPathMode(int nVal)
{
  gbPartEmitter *Emitter; // eax

  if ( nVal == 1 )
  {
    this->m_szPath = 1;
    Emitter = ((gbParticleEffect *)this->m_nDefaultH)->GetEmitter(0);
    ((gbPartEmitter *)Emitter)->SetLoopEmit(0);
  }
}

// 0x004BD9C0
int RenderTarget::SetDefaultParams(int nVal)
{
  ((gbMatrix4 *)nVal)->LoadIdentity();
  *(_DWORD *)(nVal + 52) = 1109393408;
  *(_DWORD *)(nVal + 72) = 1111490560;
  *(_DWORD *)(nVal + 68) = 1111490560;
  *(_DWORD *)(nVal + 64) = 1114636288;
  return 1111490560;
}

// 0x004BDAC0
RenderTarget::RenderTarget()
{
}

// 0x004BDB60
void RenderTarget::Create()
{
  int v2; // [esp+0xC] [ebp-0x814] BYREF
  int v3; // [esp+0x14] [ebp-0x80C]
  char pExceptionObject[1024]; // [esp+0x20] [ebp-0x800] BYREF
  char ArgList; // [esp+0x420] [ebp-0x400] BYREF

  if ( !(*(int ( **)(gbGfxManager *, int *, int))(*(_DWORD *)gfxMgr + 84))(gfxMgr, &v2, 1) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("Lock Back Buffer failed.", "D:\\Project\\PAL3\\effect\\RenderTarget.cpp", 39),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 88))(gfxMgr);
  (*((void ( **)(gbTexture_D3D **, int, int, int))this->m_ScreenPlane + 3))(
    &this->m_ScreenPlane,
    g_DrvInfo.width,
    g_DrvInfo.height,
    v3);
  (*((void ( **)(gbTexture_D3D **, int, int, int))this->m_Texture + 3))(&this->m_Texture, 512, 512, v3);
  this->m_iMode = 0;
  this->m_nState = 0;
}

// 0x004BDC10
void RenderTarget::OnDeviceLost(int nVal)
{
  int v2; // eax

  if ( this->m_nState != 1 )
  {
    v2 = nVal;
    if ( (nVal == 1 || nVal == 2) && !this->m_nDeviceLost )
      v2 = 0;
    this->m_iMode = v2;
  }
}

// 0x004BDC40
bool RenderTarget::OnResetDevice(int nVal)
{
  BOOL v3; // eax
  int m_iMode; // ecx
  int v5; // esi
  RenderTarget *v7; // [esp+0x28] [ebp-0x10] BYREF
  int v8; // [esp+0x34] [ebp-0x4]
if ( this->m_nState != 1 )
  {
    this->m_nState = 1;
    m_iMode = this->m_iMode;
    v5 = 0;
    if ( this->m_iMode )
    {
      if ( m_iMode <= 0 || m_iMode > 2 )
        return v5 != 0;
      v5 = (*(int ( **)(gbGfxManager *, gbTexture_D3D **))(*(_DWORD *)gfxMgr + 92))(
             gfxMgr,
             &this->m_ScreenPlane);
    }
    else
    {
      v5 = (*(int ( **)(gbGfxManager *, gbTexture_D3D **))(*(_DWORD *)gfxMgr + 92))(gfxMgr, &this->m_Texture);
      ((gbCamera *)&g_pCameraCtrl->m_fMinDist)->SetDimention(512, 384);
      ((CameraCtrl *)&g_pCameraCtrl)->SetAsCurrent(3);
    }
    if ( v5 && (_BYTE)nVal )
    {
      (*(void ( **)(_DWORD, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)LODWORD(gfxMgr[1].InvViewMatrix.xy)
                                                                           + 172))(
        LODWORD(gfxMgr[1].InvViewMatrix.xy),
        0,
        0,
        3,
        -16777216,
        1065353216,
        0);
      (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 48))(gfxMgr);
      PushMatrixStacks(&v7);
      v8 = 0;
      crt_sub_00540070();
      (*(void ( **)(gbGfxManager *))(*(_DWORD *)gfxMgr + 52))(gfxMgr);
      v8 = -1;
      PopMatrixStacks(&v7);
    }
    return v5 != 0;
  }
  LOBYTE(v3) = 0;
  return v3;
}

// 0x004BDD90
int RenderTarget::RenderToScreen()
{
  int result; // eax
  gbGfxManager *v3; // ebx
  int v4; // [esp+0x34] [ebp-0x48] BYREF
  int v5; // [esp+0x38] [ebp-0x44] BYREF
  _DWORD v6[4]; // [esp+0x3C] [ebp-0x40] BYREF
  _DWORD v7[4]; // [esp+0x4C] [ebp-0x30] BYREF
  _BYTE v8[24]; // [esp+0x5C] [ebp-0x20] BYREF
  int v9; // [esp+0x74] [ebp-0x8]
  int v10; // [esp+0x78] [ebp-0x4]

  ((gbCamera *)&g_pCameraCtrl->m_fMinDist)->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  ((CameraCtrl *)&g_pCameraCtrl)->SetAsCurrent(3);
  (*(void ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr + 92))(gfxMgr, 0);
  result = this->m_iMode - 2;
  if ( this->m_iMode == 2 )
  {
    result = this->m_nDeviceLost;
    v3 = gfxMgr;
    if ( result )
    {
      v5 = 0;
      result = (*(int ( **)(int, _DWORD, int *))(*(_DWORD *)result + 72))(result, 0, &v5);
      if ( v5 )
      {
        result = this->m_szPath;
        if ( result )
        {
          v4 = 0;
          result = (*(int ( **)(int, _DWORD, int *))(*(_DWORD *)result + 72))(result, 0, &v4);
          if ( v4 )
          {
            v6[1] = 0;
            v7[1] = 0;
            v6[0] = 0;
            v7[0] = 0;
            (*(void ( **)(int, _BYTE *))(*(_DWORD *)v5 + 48))(v5, v8);
            v7[2] = v9;
            v7[3] = v10;
            (*(void ( **)(int, _BYTE *))(*(_DWORD *)v4 + 48))(v4, v8);
            v6[2] = v9;
            v6[3] = v10;
            result = (*(int ( **)(_DWORD, int, _DWORD *, int, _DWORD *, _DWORD))(*(_DWORD *)LODWORD(v3[1].InvViewMatrix.xy)
                                                                                        + 136))(
                       LODWORD(v3[1].InvViewMatrix.xy),
                       v5,
                       v7,
                       v4,
                       v6,
                       0);
          }
        }
      }
    }
  }
  this->m_nState = 0;
  return result;
}

// 0x004BDEB0
gbTexture * RenderTarget::GetActiveTexture()
{
  if ( this->m_iMode )
  {
    if ( this->m_iMode == 1 )
      return (gbTexture *)&this->m_ScreenPlane;
    if ( this->m_iMode != 2 )
      return 0;
  }
  return (gbTexture *)&this->m_Texture;
}

// 0x004BDF10
int * RenderTarget::Destroy()
{
  this->m_Texture = 0;
  this->m_nRenderX = 1;
  this->m_nHalfW = 0;
  this->m_nRenderY = 0;
  this->m_nHalfH = 0;
  return &this->m_iMode;
}

// 0x004BE8D0
int RenderTarget::ResetHorizontal()
{

  this->m_nRenderY = 1075838976;
  this->m_nHalfWidth = 1;
  return (int)this;
}

// 0x004BEA60
RenderTarget * RenderTarget::ResetVertical()
{

  this->m_nRenderY = 1075838976;
  this->m_nHalfH = 1;
  return this;
}

// 0x004BEBB0
RenderTarget * RenderTarget::ResetVertical2()
{

  this->m_nRenderY = 1075838976;
  this->m_nHalfH = 1;
  return this;
}

// 0x004BED00
RenderTarget * RenderTarget::ResetBase()
{

  this->m_nRenderY = 1075838976;
  return this;
}
