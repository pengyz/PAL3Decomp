#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/EquipUI.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
CHAR * sub_458F70(LPCSTR lpString, int a2, LPSTR lpString1); // from annotations
int sub_47F590(int parent, int a2); // from annotations
int sub_496190(...);
int sub_4A3360(CHAR *_this, int a2, int *a3); // from annotations

// Unnamed globals (extern)
extern char asc_5B74B8[];
extern char byte_5967B0[3];
extern char byte_A00110;
extern char byte_A00427;
extern char byte_A00517;
extern char byte_A00518;
extern char byte_A00519;
extern char byte_A00520;
extern char byte_A00521;
extern char byte_A00522;
extern char byte_A00523;
extern char byte_A00524;
extern char byte_A00525;
extern char byte_A00526;
extern char byte_A00539;
extern char byte_A00540;
extern char byte_A00541;
extern char byte_A00542;
extern char byte_A00543;
extern char byte_A00544;
extern char byte_A00545;
extern char byte_A00546;
extern char byte_A00547;
extern char byte_A00548;
extern char byte_A00549;
extern char byte_A00550;
extern char byte_A00551;
extern char byte_A00564;
extern char byte_A00565;
extern char byte_A00566;
extern char byte_A00567;
extern char byte_A00568;
extern char byte_A00569;
extern char byte_A00570;
extern char byte_A00571;
extern char byte_ABC001;
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
extern CHAR byte_DE5F74[3];
extern CHAR byte_DE5F77[3];
extern CHAR byte_DE5F7A[3];
extern CHAR byte_DE5F7D[3];
extern CHAR byte_DE5F80[3];
extern CHAR byte_DE5F83[3];
extern CHAR byte_DE5F86[3];
extern CHAR byte_DE5F89[3];
extern CHAR byte_DE5F8C[3];
extern CHAR byte_DE5F8F[3];
extern int dword_56E148[];
extern int dword_A00500;
extern int dword_A00510;
extern const char * off_56E130;
extern void * off_5CADC4;
extern void *off_5CADC8;
extern void * off_5CADD0;
extern RoleSystem stru_C059A0;
extern int word_A00572;
extern int word_ABC002;

// 0x00484D20
int EquipUI::ShowPage()
{
  char *v2; // ecx

  if ( g_bRoleFlag1 )
  {
    v2 = (char *)&this->m_EquipData + 2280;
  }
  else
  {
    ((PalScript *)((char *)&this->m_EquipData + 2280))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    v2 = (char *)&this->m_EquipData + 2280;
  }
  sub_445E50((int)v2);
  if ( !g_bRoleFlag2 )
    ((PalScript *)((char *)&this->m_EquipData + 2624))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)&this->m_EquipData + 2624);
  ((PalScript *)((char *)&this->m_EquipData + 2968))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnBattle_Array.tga", g_bDebugMode);
  sub_445E50((int)&this->m_EquipData + 2968);
  sub_445E50((int)&this->m_EquipData + 904);
  sub_445E50((int)&this->m_EquipData + 1248);
  sub_445E50((int)&this->m_EquipData + 1592);
  sub_445E50((int)&this->m_EquipData + 1936);
  sub_445E50((int)&this->m_EquipData + 3312);
  return sub_445E50((int)&this->m_EquipData + 3656);
}

// 0x00484E70
int EquipUI::SelectTab0(unsigned __int8 nTab)
{
  BYTE1(this->j) = nTab;
  return ((LineupComp *)this)->DispatchSlotMethod(0, nTab);
}

// 0x0048A2F0
int EquipUI::SetSubTab(unsigned __int8 nTab)
{
  *((_BYTE *)&this->m_EquipData + 501) = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState(0, nTab);
}

// 0x00494040
void EquipUI::UpdateSlot(int nSlotIdx, int nItemID, int nCount)
{
  CHAR *v5; // esi
  CHAR *v6; // edi
  RoleAtt *v7; // ecx
  LPCSTR v8; // eax
  CHAR String1[253]; // [esp+0x10] [ebp-0x100] BYREF
  __int16 v10; // [esp+0x10D] [ebp-0x3]
  char v11; // [esp+0x10F] [ebp-0x1]

  v5 = &this->buf[24];
  sprintf(&this->buf[24], g_szSceneUIText);
  memset(String1, 0, sizeof(String1));
  v10 = 0;
  v11 = 0;
  v6 = sub_458F70((LPCSTR)(nCount + 96), (int)asc_5B74B8, String1);
  if ( lstrlenA(v6) <= 0 )
  {
    ((RoleAtt *)v7)->FormatAttributeText();
    lstrcatA(v5, v8);
  }
  else
  {
    lstrcpyA(v5, v6);
  }
  ((UICaption *)((char *)this + 204880))->SetEnable((int)v5, 0);
  ((UICaption *)((char *)this + 204728))->SetEnable((int)String1, 0);
}

// 0x004945C0
int EquipUI::SelectBigMapTab0(char nTab)
{
  BYTE1(this->j) = nTab;
  return ((UIBigMap *)this)->SetEntryVisible(0, nTab);
}

// 0x00494D70
void EquipUI::HandleInput(int nInputID, int nParam)
{
  char *v4; // edi
  unsigned int v5; // edi
  const char *v6; // ebp
  const char *v7; // edx
  char *v8; // edi
  int v9; // edi
  char *v10; // edi
  const char *v11; // edx
  const char *v12; // ebx
  char *v13; // edi
  int v14; // edi
  char *v15; // edi
  unsigned int v16; // edi
  char *v17; // edi
  unsigned int v18; // edi
  const char *v19; // edi
  int v20; // ebp
  signed int Child; // edi
  _DWORD *v22; // eax
  int v23; // ebx
  int v24; // ebp
  int v25; // ebp
  int ItemData; // eax
  int *v27; // eax
  int v28; // ebx
  const char *v29; // ebp
  UICursor *v30; // ecx
  const char *v31; // [esp-0x18] [ebp-0x150]
  int v32; // [esp+0x10] [ebp-0x128]
  int nIndex; // [esp+0x14] [ebp-0x124]
  int v34; // [esp+0x1C] [ebp-0x11C]
  int v35; // [esp+0x20] [ebp-0x118]
  gbColorQuad v36; // [esp+0x28] [ebp-0x110] BYREF
  char pOut[12]; // [esp+0x2C] [ebp-0x10C] BYREF
  char Buffer; // [esp+0x38] [ebp-0x100] BYREF
  _BYTE v39[252]; // [esp+0x39] [ebp-FFh] BYREF
  __int16 v40; // [esp+0x135] [ebp-0x3]
  char v41; // [esp+0x137] [ebp-0x1]

  if ( nInputID <= 5 )
  {
    switch ( nParam )
    {
      case 0:
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(7);
        *(_DWORD *)&this->m_EquipData.m_Type = 7;
        v4 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v4 + 162424));
        sub_445E50((int)(v4 + 163112));
        sub_445E50((int)(v4 + 162768));
        sub_445E50((int)(v4 + 163456));
        sub_445E50((int)(v4 + 163800));
        sub_445E50((int)(v4 + 164144));
        if ( !::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8] )
          goto LABEL_42;
        this->UpdateSlot(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 6], ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 7], ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8]);
        ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(228.0);
        ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 262, 600);
        if ( !strcmp((const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8] + 36), g_szSceneUIText) )
          sprintf(&this->buf[24], byte_5967B0, "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8] + 36),
            (const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8] + 36));
        ((PalScript *)((char *)this + 219748))->LoadModel(&this->buf[24], 0);
        v5 = ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 8];
        v6 = (const char *)(v5 + 36);
        v7 = (const char *)(v5 + 66);
        if ( !strcmp((const char *)(v5 + 36), g_szSceneUIText) )
          goto LABEL_38;
        goto LABEL_39;
      case 1:
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(11);
        *(_DWORD *)&this->m_EquipData.m_Type = 11;
        v8 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v8 + 162424));
        sub_445E50((int)(v8 + 163112));
        sub_445E50((int)(v8 + 162768));
        sub_445E50((int)(v8 + 163456));
        sub_445E50((int)(v8 + 163800));
        sub_445E50((int)(v8 + 164144));
        if ( !*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 3) )
          goto LABEL_42;
        this->UpdateSlot(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 1), *((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 2), *((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 3));
        ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(180.0);
        ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 258, 600);
        if ( !strcmp(
                (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 3) + 36),
                g_szSceneUIText) )
          sprintf(&this->buf[24], byte_5967B0, "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 3) + 36),
            (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 3) + 36));
        ((PalScript *)((char *)this + 219748))->LoadModel(&this->buf[24], 0);
        v9 = *((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 3);
        v6 = (const char *)(v9 + 36);
        v7 = (const char *)(v9 + 66);
        if ( strcmp((const char *)(v9 + 36), g_szSceneUIText) )
          goto LABEL_39;
        goto LABEL_38;
      case 2:
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(12);
        *(_DWORD *)&this->m_EquipData.m_Type = 12;
        v10 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v10 + 162424));
        sub_445E50((int)(v10 + 163112));
        sub_445E50((int)(v10 + 162768));
        sub_445E50((int)(v10 + 163456));
        sub_445E50((int)(v10 + 163800));
        sub_445E50((int)(v10 + 164144));
        if ( !*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID) )
          goto LABEL_42;
        this->UpdateSlot(*((_DWORD *)&::Buffer.m_partyActor.m_nAnimFrame + 352 * nInputID + 1), *((_DWORD *)&::Buffer.m_partyActor.m_nAnimFrame + 352 * nInputID + 2), *((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID));
        ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(180.0);
        ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 258, 600);
        if ( !strcmp(
                (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID) + 36),
                g_szSceneUIText) )
          sprintf(&this->buf[24], byte_5967B0, "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID) + 36),
            (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID) + 36));
        ((PalScript *)((char *)this + 219748))->LoadModel(&this->buf[24], 0);
        v11 = (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * *((_DWORD *)this + 53799)) + 66);
        v12 = (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID) + 36);
        if ( !strcmp(v12, g_szSceneUIText) )
          goto LABEL_38;
        Buffer = 0;
        memset(v39, 0, sizeof(v39));
        v40 = 0;
        v41 = 0;
        sprintf(&Buffer, "%s%s", v12, v11);
        v31 = v12;
        goto LABEL_40;
      case 3:
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(13);
        *(_DWORD *)&this->m_EquipData.m_Type = 13;
        v13 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v13 + 162424));
        sub_445E50((int)(v13 + 163112));
        sub_445E50((int)(v13 + 162768));
        sub_445E50((int)(v13 + 163456));
        sub_445E50((int)(v13 + 163800));
        sub_445E50((int)(v13 + 164144));
        if ( !*((_DWORD *)&::Buffer.m_partyActor.m_fAnimDelta + 352 * nInputID) )
          goto LABEL_42;
        this->UpdateSlot(*((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 4), *((_DWORD *)&::Buffer.m_partyActor.m_pParticleData + 352 * nInputID + 5), *((_DWORD *)&::Buffer.m_partyActor.m_fAnimDelta + 352 * nInputID));
        ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(180.0);
        ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 258, 600);
        if ( !strcmp(
                (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_fAnimDelta + 352 * nInputID) + 36),
                g_szSceneUIText) )
          sprintf(&this->buf[24], byte_5967B0, "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_fAnimDelta + 352 * nInputID) + 36),
            (const char *)(*((_DWORD *)&::Buffer.m_partyActor.m_fAnimDelta + 352 * nInputID) + 36));
        ((PalScript *)((char *)this + 219748))->LoadModel(&this->buf[24], 0);
        v14 = *((_DWORD *)&::Buffer.m_partyActor.m_fAnimDelta + 352 * nInputID);
        v6 = (const char *)(v14 + 36);
        v7 = (const char *)(v14 + 66);
        if ( strcmp((const char *)(v14 + 36), g_szSceneUIText) )
          goto LABEL_39;
        goto LABEL_38;
      case 4:
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(9);
        *(_DWORD *)&this->m_EquipData.m_Type = 9;
        v15 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v15 + 162424));
        sub_445E50((int)(v15 + 163112));
        sub_445E50((int)(v15 + 162768));
        sub_445E50((int)(v15 + 163456));
        sub_445E50((int)(v15 + 163800));
        sub_445E50((int)(v15 + 164144));
        if ( !::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2] )
          goto LABEL_42;
        this->UpdateSlot(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID], ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 1], ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2]);
        ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(180.0);
        ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 258, 600);
        if ( !strcmp((const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2] + 36), g_szSceneUIText) )
          sprintf(&this->buf[24], byte_5967B0, "NONE");
        else
          sprintf(
            &this->buf[24],
            "Item\\%s\\%s.pol",
            (const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2] + 36),
            (const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2] + 36));
        ((PalScript *)((char *)this + 219748))->LoadModel(&this->buf[24], 0);
        v16 = ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 2];
        v6 = (const char *)(v16 + 36);
        v7 = (const char *)(v16 + 66);
        if ( strcmp((const char *)(v16 + 36), g_szSceneUIText) )
          goto LABEL_39;
        goto LABEL_38;
      case 5:
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(9);
        *(_DWORD *)&this->m_EquipData.m_Type = 9;
        v17 = (char *)this + 9980 * nInputID;
        sub_445E50((int)(v17 + 162424));
        sub_445E50((int)(v17 + 163112));
        sub_445E50((int)(v17 + 162768));
        sub_445E50((int)(v17 + 163456));
        sub_445E50((int)(v17 + 163800));
        sub_445E50((int)(v17 + 164144));
        if ( ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5] )
        {
          this->UpdateSlot(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 3], ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 4], ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5]);
          ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(180.0);
          ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 258, 600);
          if ( !strcmp((const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5] + 36), g_szSceneUIText) )
            sprintf(&this->buf[24], byte_5967B0, "NONE");
          else
            sprintf(
              &this->buf[24],
              "Item\\%s\\%s.pol",
              (const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5] + 36),
              (const char *)(::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5] + 36));
          ((PalScript *)((char *)this + 219748))->LoadModel(&this->buf[24], 0);
          v18 = ::Buffer.m_partyActor.m_dwMatMsg[352 * nInputID + 5];
          v6 = (const char *)(v18 + 36);
          v7 = (const char *)(v18 + 66);
          if ( !strcmp((const char *)(v18 + 36), g_szSceneUIText) )
          {
LABEL_38:
            v19 = &this->buf[24];
            sprintf(&this->buf[24], byte_5967B0, "NONE");
          }
          else
          {
LABEL_39:
            Buffer = 0;
            memset(v39, 0, sizeof(v39));
            v40 = 0;
            v41 = 0;
            sprintf(&Buffer, "%s%s", v6, v7);
            v31 = v6;
LABEL_40:
            v19 = &this->buf[24];
            sprintf(&this->buf[24], "Item\\%s\\%s.tga", v31, &Buffer);
          }
          ((gbGeomNode *)*((gbGeomNode **)this + 54941))->ReplaceTexture(v19);
          *((_DWORD *)this + 54938) = 1;
        }
        else
        {
LABEL_42:
          ((UICaption *)((char *)this + 204728))->SetEnable((int)g_szSceneUIText, 0);
          ((UICaption *)((char *)this + 204880))->SetEnable((int)g_szSceneUIText, 0);
          *((_DWORD *)this + 54938) = 0;
        }
LABEL_43:
        v20 = *((_DWORD *)this + 54416);
        v32 = v20;
        Child = ((NPC *)((char *)this + 217412))->CreateChild();
        if ( Child < 0 )
        {
          v20 = 0;
          v32 = 0;
        }
        if ( *((int *)this + 54918) >= 0 )
          ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(*((void **)this + 54918));
        ((UIListBox *)((char *)this + 217412))->ClearAll();
        nIndex = 0;
        if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
        {
          do
          {
            v22 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, nIndex);
            v34 = v22[1];
            v23 = v22[2];
            sprintf(&this->buf[24], byte_5967B0, v23 + 4);
            v24 = ((UIListBox *)((char *)this + 217412))->SetItemOffset(&this->buf[24], 0);
            sprintf(&this->buf[24], &dir[20], v34);
            ((UIListBox *)((char *)this + 217412))->SetMouseMoveSel(1, v24, &this->buf[24], 0);
            if ( *(_BYTE *)(nInputID + v23 + 614) )
            {
              if ( v24 < 0 || v24 >= *((_DWORD *)this + 54479) )
                v25 = 0;
              else
                v25 = *(_DWORD *)(*((_DWORD *)this + 54478) + 4 * v24);
              *(_DWORD *)(v25 + 68) = *((_DWORD *)this + 54354);
            }
            else
            {
              ((UITabCtrl *)(UITabCtrl *)this + 1469)->SetItemParam(v24);
            }
            ++nIndex;
          }
          while ( nIndex < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
          v20 = v32;
        }
        ((UIListBox *)((char *)this + 217412))->SetSel(v20);
        ItemData = ((UIListBox *)((char *)this + 217412))->GetItemData();
        if ( ItemData <= Child )
          Child = ItemData - 1;
        ((UIListBox *)((char *)this + 217412))->GetItem();
        if ( Child >= 0 )
        {
          v27 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, Child);
          v28 = v27[2];
          this->UpdateSlot(*v27, v27[1], v28);
          if ( *(_BYTE *)(v28 + 612) == 11 )
          {
            ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(228.0);
            ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 262, 600);
          }
          else
          {
            ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(180.0);
            ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 258, 600);
          }
          v35 = *((_DWORD *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, Child) + 2);
          v29 = (const char *)(v35 + 36);
          if ( !strcmp((const char *)(v35 + 36), g_szSceneUIText) )
            sprintf(&this->buf[24], byte_5967B0, "NONE");
          else
            sprintf(&this->buf[24], "Item\\%s\\%s.pol", (const char *)(v35 + 36), (const char *)(v35 + 36));
          ((PalScript *)((char *)this + 219748))->LoadModel(&this->buf[24], 0);
          if ( !strcmp((const char *)(v35 + 36), g_szSceneUIText) )
          {
            sprintf(&this->buf[24], byte_5967B0, "NONE");
          }
          else
          {
            Buffer = 0;
            memset(v39, 0, sizeof(v39));
            v40 = 0;
            v41 = 0;
            sprintf(&Buffer, "%s%s", v29, (const char *)(v35 + 66));
            sprintf(&this->buf[24], "Item\\%s\\%s.tga", v29, &Buffer);
          }
          ((gbGeomNode *)*((gbGeomNode **)this + 54941))->ReplaceTexture(&this->buf[24]);
          v20 = v32;
          *((_DWORD *)this + 54938) = 1;
        }
        if ( v20 >= *((_DWORD *)this + 54415) )
          v20 = *((_DWORD *)this + 54415);
        ((UIListBox *)((char *)this + 217412))->SetSel(v20);
        if ( *(_DWORD *)&this->_isCreatable >= ((UIListBox *)((char *)this + 217412))->GetItemData() )
          *(_DWORD *)&this->_isCreatable = ((UIListBox *)((char *)this + 217412))->GetItemData() - 1;
        if ( *(int *)&this->_isCreatable < 0 )
          *(_DWORD *)&this->_isCreatable = -1;
        ((UIListBox *)((char *)this + 217412))->GetItem();
        LODWORD(this->_flashSpeed) = nParam;
        ((MainPropUI *)this)->ShowSubPanels(nInputID);
        ((UIScene *)this)->LoadRoleSkillData(nInputID);
        ((MainEquipUI *)this)->UpdateTooltip(nInputID);
        ((UICursor *)v30)->IRender();
        break;
      default:
        goto LABEL_43;
    }
  }
}

// 0x00498820
int EquipUI::ctor()
{
  *(_DWORD *)&this->buf[8] = 800;
  *(_DWORD *)&this->buf[12] = 600;
  *(_DWORD *)&this->buf[24] = 0;
  *((_BYTE *)&this->m_EquipData + 244) = 0;
  *((_DWORD *)&this->m_EquipData + 63) = 0;
  *((_BYTE *)&this->m_EquipData + 257) = 0;
  *((_DWORD *)&this->m_EquipData + 65) = 0;
  *((_DWORD *)&this->m_EquipData + 66) = 0;
  *((_DWORD *)&this->m_EquipData + 67) = 0;
  *((_DWORD *)&this->m_EquipData + 68) = 0;
  *((_BYTE *)&this->m_EquipData + 277) = 0;
  *((_BYTE *)&this->m_EquipData + 278) = 0;
  *((_BYTE *)&this->m_EquipData + 279) = 0;
  *((_DWORD *)&this->m_EquipData + 70) = 0;
  sub_4422E0((char *)&this->m_EquipData + 284);
  sub_4422E0((char *)&this->m_EquipData + 436);
  sub_4422E0((char *)&this->m_EquipData + 588);
  sub_4422E0((char *)&this->m_EquipData + 740);
  sub_4422E0((char *)&this->m_EquipData + 892);
  sub_4422E0((char *)&this->m_EquipData + 1044);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0((char *)&this->m_EquipData + 4292);
  sub_4422E0((char *)&this->m_EquipData + 4460);
  sub_4422E0((char *)&this->m_EquipData + 4612);
  ((ARC_PlayerAtt *)((char *)this + 154784))->Refresh();
  sub_4422E0((char *)this + 180612);
  sub_4422E0((char *)this + 180764);
  sub_4422E0((char *)this + 180916);
  sub_4422E0((char *)this + 181084);
  sub_4422E0((char *)this + 181236);
  sub_4422E0((char *)this + 184940);
  ((UI3DCtrl *)((char *)this + 185092))->ctor_D830();
  sub_4422E0((char *)this + 185176);
  ((UIListBox *)((char *)this + 187152))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 188360))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 189568))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 190776))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 191984))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 193192))->UpdateKeyCtrl();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  *((_DWORD *)this + 48947) = -1;
  ((UIProgressBar *)((char *)this + 195792))->ctor();
  *((_BYTE *)&this->m_EquipData + 249) = 0;
  *((_BYTE *)&this->m_EquipData + 248) = 0;
  *((_BYTE *)&this->m_EquipData + 246) = 0;
  *((_BYTE *)&this->m_EquipData + 245) = 0;
  *((_BYTE *)&this->m_EquipData + 247) = 0;
  *((_DWORD *)this + 38693) = 0;
  *((_DWORD *)this + 38694) = 0;
  *((_DWORD *)this + 38695) = 0;
  return (int)this;
}

// 0x00499030
void EquipUI::ctor_9030()
{
  ((PalScript *)((char *)this + 195792))->PalScript_Init();
  ((UICaption *)((char *)this + 195444))->Destroy2();
  ((UICaption *)((char *)this + 195100))->Destroy2();
  ((UICaption *)((char *)this + 194756))->Destroy2();
  ((UIListBox *)((char *)this + 193192))->DeleteRow();
  ((UIListBox *)((char *)this + 191984))->DeleteRow();
  ((UIListBox *)((char *)this + 190776))->DeleteRow();
  ((UIListBox *)((char *)this + 189568))->DeleteRow();
  ((UIListBox *)((char *)this + 188360))->DeleteRow();
  ((UIListBox *)((char *)this + 187152))->DeleteRow();
  ((UIFrameWnd *)((char *)this + 185176))->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)((char *)this + 185092))->ctor();
  ((UIFrameWnd *)((char *)this + 184940))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 181236))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 181084))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 180916))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 180764))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 180612))->UIFrameWnd::_UIFrameWnd();
  ((UIRoleDialog *)((char *)this + 154784))->_UIRoleDialog();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 4612))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 4460))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 4292))->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)((char *)&this->m_EquipData + 3948))->Destroy2();
  ((UICaption *)((char *)&this->m_EquipData + 3604))->Destroy2();
  ((UICaption *)((char *)&this->m_EquipData + 3260))->Destroy2();
  ((UICaption *)((char *)&this->m_EquipData + 2916))->Destroy2();
  ((UICaption *)((char *)&this->m_EquipData + 2572))->Destroy2();
  ((UICaption *)((char *)&this->m_EquipData + 2228))->Destroy2();
  ((UICaption *)((char *)&this->m_EquipData + 1884))->Destroy2();
  ((UICaption *)((char *)&this->m_EquipData + 1540))->Destroy2();
  ((UICaption *)((char *)&this->m_EquipData + 1196))->Destroy2();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 1044))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 892))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 740))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 588))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 436))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)&this->m_EquipData + 284))->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0049E840
int EquipUI::SetSubTab2(unsigned __int8 nTab)
{
  *((_BYTE *)&this->m_EquipData + 245) = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState2(0, nTab);
}

// 0x0049F9B0
int EquipUI::SetGroupVisible(unsigned __int8 bVisible)
{
  sub_445E50((int)this + 187152);
  sub_445E50((int)this + 188360);
  sub_445E50((int)this + 189568);
  sub_445E50((int)this + 190776);
  sub_445E50((int)this + 191984);
  return sub_445E50((int)this + 193192);
}

// 0x0049FA10
int EquipUI::InitParticleEffects(int nVal)
{
  void **v4; // esi
  int *v5; // ebx
  int v6; // edi
  RenderTarget *v7; // ebp
  int v8; // eax
  int v9; // eax
  int *p_m_nScaleX; // edi
  RenderTarget *v11; // esi
  bool v12; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  void **v19; // [esp+0x18] [ebp-0xC]
  int v20; // [esp+0x1C] [ebp-0x8]
  int nVala; // [esp+0x28] [ebp+0x4]

  *((_DWORD *)this + 38693) = 0;
  *((_DWORD *)this + 38694) = 0;
  nVala = 16;
  *((_BYTE *)this + nVal + 154772) = 1;
// [VFTABLE] v4 = &this->__vftable + 4 * nVal;
  v19 = v4;
  v5 = (int *)(v4 + 38661);
  v6 = (char *)v4[38663] - (char *)v4[38661];
  v20 = v6;
  v7 = (RenderTarget *)((char *)&this->m_EquipData + 9344 * nVal + 4764);
  while ( 1 )
  {
    ((RenderTarget *)v7)->LoadTexture(szFilename);
    ((RenderTarget *)v7)->SetSize(32);
    fY = rand() % 10 + 98;
    fX = rand() % 10 + 168;
    v8 = rand();
    ((RenderTarget *)v7)->SetColor(v8 % 10 + 68, fX, fY);
    v9 = rand();
    ((RenderTarget *)v7)->SetAlpha(v9 % 55 - 56);
    *((_BYTE *)&v7->m_ScreenPlane + 4) = 1;
    ((RenderTarget *)v7)->SetField084();
    ((RenderTarget *)v7)->SetState();
    fYa = (float)(int)v4[38662];
    fXa = (float)(*v5 + rand() % v6);
    ((RenderTarget *)v7)->UpdateTransform(fXa, fYa);
    ((RenderTarget *)v7)->Render(*v5, v5[1], v5[2]);
    rand();
    *(float *)&fXb = (float)(rand() % 2 + 1);
    ((RenderTarget *)v7)->SetOffset(fXb);
    ((RenderTarget *)v7)->SetScale(0);
    ((RenderTarget *)v7)->SetVisible(1);
    p_m_nScaleX = &v7[373].m_nScaleX;
    v11 = v7;
    v7 = (RenderTarget *)((char *)v7 + 584);
    result = nVala - 1;
    v12 = nVala == 1;
    qmemcpy(p_m_nScaleX, v11, 0x248u);
    --nVala;
    if ( v12 )
      break;
    v4 = v19;
    v6 = v20;
  }
  return result;
}

// 0x0049FBE0
BOOL EquipUI::UpdateDisplay(int nPage, int nSlot)
{
  BOOL result; // eax
  int v5; // ebx
  int v6; // ebp
  int v7; // edi
  int v8; // edi
  double v9; // st7
  RenderTarget *v10; // ebx
  int v11; // eax
  int v12; // eax
  _BYTE *p_field_028; // edi
  RenderTarget *v14; // esi
  bool v15; // zf
  int nOffY; // [esp+0x0] [ebp-0x30]
  int nOffYa; // [esp+0x0] [ebp-0x30]
  int nOffYb; // [esp+0x0] [ebp-0x30]
  int v19; // [esp+0x4] [ebp-0x2C]
  float fX; // [esp+0x18] [ebp-0x18]
  int v21; // [esp+0x1C] [ebp-0x14]
  float fY; // [esp+0x28] [ebp-0x8]
  int nPageb; // [esp+0x34] [ebp+0x4]
  int nPagea; // [esp+0x34] [ebp+0x4]

  LOBYTE(result) = *((_BYTE *)&this->m_EquipData + nPage + 245);
  if ( result )
  {
    v5 = *((_DWORD *)this + 4 * nPage + 66545);
    v6 = *((_DWORD *)this + 4 * nPage + 66547) - v5;
    v7 = *((_DWORD *)this + 4 * nPage + 66548);
    nPageb = *((_DWORD *)this + 4 * nPage + 66546);
    v8 = v7 - nPageb;
    v21 = v8;
    v9 = (double)nPageb;
    nPagea = 12;
    fX = (float)(v5 + v6 / 2);
    v10 = (RenderTarget *)((char *)this + 7008 * nPage + 196100);
    while ( 1 )
    {
      ((RenderTarget *)v10)->LoadTexture(szFilename);
      ((RenderTarget *)v10)->SetSize(32);
      v19 = (unsigned __int8)nSlot + rand() % 10;
      nOffY = BYTE1(nSlot) + rand() % 10;
      v11 = rand();
      ((RenderTarget *)v10)->SetColor(BYTE2(nSlot) + v11 % 10, nOffY, v19);
      v12 = rand();
      ((RenderTarget *)v10)->SetAlpha(v12 % 135 + 120);
      ((RenderTarget *)v10)->SetField084();
      ((RenderTarget *)v10)->SetState();
      fY = v9;
      ((RenderTarget *)v10)->UpdateTransform(fX, fY);
      ((RenderTarget *)v10)->CalcRenderDimensions(v6, v8);
      rand();
      *(float *)&nOffYa = (float)(rand() % 2 + 1);
      ((RenderTarget *)v10)->SetOffset(nOffYa);
      rand();
      *(float *)&nOffYb = (float)(rand() % 2 + 2);
      ((RenderTarget *)v10)->SetScale(nOffYb);
      ((RenderTarget *)v10)->SetVisible(1);
      p_field_028 = &v10[175]._field_028;
      v14 = v10;
      v10 = (RenderTarget *)((char *)v10 + 584);
      result = nPagea - 1;
      v15 = nPagea == 1;
      qmemcpy(p_field_028, v14, 0x248u);
      --nPagea;
      if ( v15 )
        break;
      v8 = v21;
    }
  }
  return result;
}

// 0x0049FE00
void EquipUI::RenderEffects()
{
  int v2; // eax
  ScreenEffect *v3; // edi
  int v4; // ebp
  int i; // edi
  CCBMagicWindow *v6; // [esp+0x0] [ebp-0x18]
  int v7; // [esp+0x10] [ebp-0x8]
  ScreenEffect *v8; // [esp+0x14] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v6);
  v2 = 0;
  v3 = (ScreenEffect *)((char *)this + 231140);
  v7 = 0;
  v8 = (ScreenEffect *)((char *)this + 231140);
  do
  {
    if ( *((_BYTE *)&this->m_EquipData + v2 + 245) )
    {
      v4 = 12;
      do
      {
// [IDA_MISID]         if ( ((Concurrency *)&v3[-1460])->details::VirtualProcessor::IsThrottled() )
          ((ScreenEffect *)v3 - 1460)->Apply();
// [IDA_MISID]         if ( ((Concurrency *)v3)->details::VirtualProcessor::IsThrottled() )
          ((ScreenEffect *)v3)->Apply();
        v3 = (ScreenEffect *)((char *)v3 + 584);
        --v4;
      }
      while ( v4 );
      v2 = v7;
    }
    ++v2;
    v3 = v8 + 292;
    v7 = v2;
    v8 += 292;
  }
  while ( v2 < 5 );
  if ( *((_BYTE *)this + *((_DWORD *)this + 38695) + 154772) )
  {
    for ( i = 0; i < 16; ++i )
    {
// [IDA_MISID]       if ( ((Concurrency *)((char *)&this->m_EquipData + 9344 * *((_DWORD *)this + 38695) + 584 * i + 4764))->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)((char *)&this->m_EquipData
                                           + 9344 * *((_DWORD *)this + 38695)
                                           + 584 * i
                                           + 4764))->Apply();
// [IDA_MISID]       if ( ((Concurrency *)(&this->m_ArrowRc[2][1][584 * *((_DWORD *)this + 38695) + 1].top + 146 * i))->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)(&this->m_ArrowRc[2][1][584 * *((_DWORD *)this + 38695) + 1].top + 146 * i))->Apply();
    }
  }
}

// 0x0049FF30
int EquipUI::FindNextSlot(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  ++*pCounter;
  while ( 1 )
  {
    v2 = *pCounter;
    if ( *((_BYTE *)&this->m_EquipData + *pCounter + 245) )
    {
      if ( v2 <= 4 )
        break;
    }
    v3 = v2 + 1;
    *pCounter = v3;
    if ( v3 > 4 )
      *pCounter = 0;
  }
  return *pCounter;
}

// 0x0049FF60
int EquipUI::FindPrevSlot(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  --*pCounter;
  while ( 1 )
  {
    v2 = *pCounter;
    if ( *((_BYTE *)&this->m_EquipData + *pCounter + 245) )
    {
      if ( v2 >= 0 )
        break;
    }
    v3 = v2 - 1;
    *pCounter = v3;
    if ( v3 < 0 )
      *pCounter = 4;
  }
  return *pCounter;
}

// 0x0049FF90
char EquipUI::HandleInput()
{
  char result; // al
  int *v3; // edi
  int PrevSlot; // eax
  void *vftable; // edx
  int v6; // eax
  int v7; // eax

  result = *((_BYTE *)this + 156125);
  if ( !result )
  {
    result = 1;
    if ( *((_BYTE *)&this->m_EquipData + 277) )
    {
      if ( g_Input.KeyInfo[10].PressTime == 1 )
      {
        v3 = (int *)((char *)&this->m_EquipData + 252);
        PrevSlot = this->FindPrevSlot((int *)&this->m_EquipData + 63);
LABEL_7:
// [VFTABLE] vftable = this->__vftable;
        *v3 = PrevSlot;
        return ((char ( *)(EquipUI *, int, int, _DWORD))vftable->OnMessage)(
                 this,
                 1001,
                 dword_56E148[PrevSlot],
                 0);
      }
      if ( g_Input.KeyInfo[9].PressTime == 1 )
      {
        v3 = (int *)((char *)&this->m_EquipData + 252);
        PrevSlot = this->FindNextSlot((int *)&this->m_EquipData + 63);
        goto LABEL_7;
      }
      if ( g_Input.KeyInfo[8].PressTime == 1 )
      {
        return this->OnMessage(1010, 0, 0);
      }
      else if ( g_Input.KeyInfo[6].PressTime == 1 )
      {
        return this->OnMessage(1020,
                 dword_56E148[*((_DWORD *)&this->m_EquipData + 63)],
                 0);
      }
    }
    else
    {
      if ( g_Input.KeyInfo[2].PressTime == 1 )
      {
        v6 = *((_DWORD *)&this->m_EquipData + 65) - 1;
        *((_DWORD *)&this->m_EquipData + 65) = v6;
        if ( v6 < 0 )
          *((_DWORD *)&this->m_EquipData + 65) = 0;
      }
      else
      {
        if ( g_Input.KeyInfo[3].PressTime != 1 )
          return result;
        v7 = *((_DWORD *)&this->m_EquipData + 65) + 1;
        *((_DWORD *)&this->m_EquipData + 65) = v7;
        if ( v7 >= 5 )
          *((_DWORD *)&this->m_EquipData + 65) = 5;
      }
      return this->OnMessage(1001,
               (&off_56E130)[*((_DWORD *)&this->m_EquipData + 65)],
               0);
    }
  }
  return result;
}

// 0x004A00B0
BOOL EquipUI::Update(int nVal, int nVal2)
{
  __int64 v4; // rax
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  char v8; // cl
  float *v9; // eax
  int v10; // eax
  char v11; // cl
  float *v12; // eax
  float *v13; // eax
  int v14; // eax
  int v16; // [esp-0x4] [ebp-0x28]
  int v17; // [esp+0x20] [ebp-0x4]

  v4 = (__int64)g_fGameTimer;
  v5 = (int)v4 / 3600;
  v17 = (int)v4 / 60 % 60;
  v16 = (int)v4 % 60;
  if ( (int)v4 / 3600 < 100 )
    sprintf(&this->buf[28], "%02d:%02d:%02d", v5, v17, v16);
  else
    sprintf(&this->buf[28], "%03d:%02d:%02d", v5, v17, v16);
  ((UICaption *)((char *)&this->m_EquipData + 4460))->SetEnable((int)&this->buf[28], 0);
  sprintf(&this->buf[28], &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)((char *)&this->m_EquipData + 4612))->SetEnable((int)&this->buf[28], 0);
  if ( *((_BYTE *)&this->m_EquipData + 256) )
  {

    *(_DWORD *)&this->buf[16] = 0;
    do
    {
      v6 = *(_DWORD *)&this->buf[16];
      if ( *((_BYTE *)&this->m_EquipData + v6 + 245) )
      {
        v7 = 4892 * v6;
        v8 = *((_BYTE *)this + v7 + 157112);
        v9 = (float *)((char *)this + v7);
        if ( !v8 )
        {
          sprintf(
            &this->buf[28],
            "%d/%d",
            (int)v9[39277],
            Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)&this->buf[16] + 9]);
          ((UICaption *)((char *)this + 4892 * *(_DWORD *)&this->buf[16] + 157196))->SetEnable((int)&this->buf[28], 0);
        }
        v10 = 4892 * *(_DWORD *)&this->buf[16];
        v11 = *((_BYTE *)this + v10 + 158208);
        v12 = (float *)((char *)this + v10);
        if ( !v11 )
        {
          sprintf(
            &this->buf[28],
            "%d/%d",
            (int)v12[39551],
            Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)&this->buf[16] + 10]);
          ((UICaption *)((char *)this + 4892 * *(_DWORD *)&this->buf[16] + 158292))->SetEnable((int)&this->buf[28], 0);
        }
        v13 = (float *)((char *)this + 4892 * *(_DWORD *)&this->buf[16]);
        if ( !*((_BYTE *)v13 + 157660) )
        {
          sprintf(
            &this->buf[28],
            "%d/%d",
            (int)v13[39414],
            Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)&this->buf[16] + 11]);
          ((UICaption *)((char *)this + 4892 * *(_DWORD *)&this->buf[16] + 157744))->SetEnable((int)&this->buf[28], 0);
        }
        ((UIFrameWnd *)((char *)this + 52 * *(_DWORD *)&this->buf[16] + 194400))->ProcessTimer(1, 1, 2, *((_DWORD *)this + 4 * *(_DWORD *)&this->buf[16] + 48665));
      }
      v14 = *(_DWORD *)&this->buf[16] + 1;
      *(_DWORD *)&this->buf[16] = v14;
    }
    while ( v14 < 5 );
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x004A0370
void EquipUI::HandleEquipEvent(int nVal, char *pszBuf, int nVal2)
{
  int i; // edi
  UICursor *v6; // ecx
  int v7; // edx
  char **v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ebp
  char *v12; // edi
  int *v13; // eax
  int v14; // ecx
  int v15; // eax
  char v16; // al
  int v17; // edi
  int v18; // ebp
  char *v19; // edi
  char *v20; // edi
  int v21; // ebp
  char v22; // al
  CScreenMode *Instance; // eax
  char *v24; // eax
  int v25; // eax
  int v26; // eax
  signed int v27; // eax
  int v28; // eax
  int v29; // eax
  int *v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // edi
  char *v34; // ebp
  int v35; // edi
  char *v36; // ebp
  char *v37; // esi
  int v38; // edi
  char *v39; // edi
  int v40; // ebp
  int *v41; // eax
  int v42; // ecx
  char v43; // al
  CCBFiveNimbusWindow *v44; // edi
  const char *v45; // ebp
  CScreenMode *v46; // eax
  UIListBox *v47; // edi
  int *v48; // eax
  int v49; // edi
  char *v50; // ebp
  CScreenMode *v51; // eax
  char *v52; // [esp-0x8] [ebp-0x158]
  const void *v53; // [esp-0x8] [ebp-0x158]
  const void *v54; // [esp-0x8] [ebp-0x158]
  float v55; // [esp-0x4] [ebp-0x154]
  int v56; // [esp+0x10] [ebp-0x140]
  int nItemID; // [esp+0x14] [ebp-0x13C] BYREF
  int v58; // [esp+0x18] [ebp-0x138]
  int v59; // [esp+0x1C] [ebp-0x134]
  _BYTE v60[12]; // [esp+0x20] [ebp-0x130] BYREF
  int v61[3]; // [esp+0x2C] [ebp-0x124] BYREF
  _BYTE v62[12]; // [esp+0x38] [ebp-0x118] BYREF
  _BYTE pOut[12]; // [esp+0x44] [ebp-0x10C] BYREF
  char Buffer[253]; // [esp+0x50] [ebp-0x100] BYREF
  __int16 v65; // [esp+0x14D] [ebp-0x3]
  char v66; // [esp+0x14F] [ebp-0x1]

  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        for ( i = 0; i < 8; ++i )
          this->InitParticleEffects(i);
        ((ArcSceneObject *)this)->ResetEquipControls();
        ((StateUI *)this)->ShowPage();
        g_nSceneState = 1;
        *((_BYTE *)&this->m_EquipData + 256) = 1;
        *((_DWORD *)this + 38693) = 0;
        *((_DWORD *)this + 38694) = 0;
        *((_BYTE *)&this->m_EquipData + 276) = 0;
        ((UICursor *)v6)->IRender();
      }
      else
      {
        *((_BYTE *)&this->m_EquipData + 256) = 0;
      }
      return;
    case 1001:
      v7 = 0;
      v8 = (char **)dword_56E148;
      while ( pszBuf != *v8 )
      {
        ++v8;
        ++v7;
        if ( (int)v8 >= (int)&g_ArcSceneMonsterTable2 )
        {
          *(_DWORD *)&this->buf[16] = 0;
          do
          {
            v9 = *(_DWORD *)&this->buf[16];
            if ( (&off_56E130)[v9] == pszBuf )
            {
              ((MainEquipUI *)this)->ShowWithCursor(*(_DWORD *)&this->buf[16]);
              v52 = (char *)off_5CADC4;
              goto LABEL_170;
            }
            v10 = v9 + 1;
            *(_DWORD *)&this->buf[16] = v10;
          }
          while ( v10 < 6 );
          if ( pszBuf <= byte_A00110 )
          {
            if ( pszBuf == byte_A00110 )
            {
LABEL_48:
              v53 = off_5CADC4;
              Instance = CScreenMode::GetInstance();
              ((CScreenMode *)Instance)->AudioSetPosition(v53, 1);
              ((MainEquipUI *)*((MainEquipUI **)&this->m_EquipData + 70))->HandleMessage();
            }
            else
            {
              switch ( (unsigned int)pszBuf )
              {
                case 0xA00102u:
                case 0xA00103u:
                case 0xA00104u:
                case 0xA00106u:
                case 0xA00107u:
                case 0xA00108u:
                case 0xA00109u:
                  goto LABEL_48;
                default:
                  return;
              }
            }
            return;
          }
          if ( pszBuf == &byte_A00427 )
          {
            if ( *((_BYTE *)&this->m_EquipData + 278) )
            {
              v52 = (char *)off_5CADD0;
              goto LABEL_170;
            }
            *((_DWORD *)this + 48947) = -1;
          }
          else if ( pszBuf - &byte_A00427 == 1 )
          {
            if ( *((_BYTE *)&this->m_EquipData + 278) )
            {
              v52 = (char *)off_5CADD0;
              goto LABEL_170;
            }
            *((_DWORD *)this + 48947) = 0;
          }
          else
          {
            if ( pszBuf - &byte_A00427 != 2 )
              return;
            if ( *((_BYTE *)&this->m_EquipData + 278) )
            {
              v52 = (char *)off_5CADD0;
              goto LABEL_170;
            }
            *((_DWORD *)this + 48947) = 3;
          }
          ((MainEquipUI *)this)->SetupRoleList(*((_DWORD *)&this->m_EquipData + 65), 0);
          v24 = (char *)off_5CADC4;
          goto LABEL_169;
        }
      }
      v56 = v7;
      if ( *((int *)&this->m_EquipData + 67) >= 0 && *((_BYTE *)&this->m_EquipData + 277) )
      {
        v11 = 0;
        v12 = (char *)this + 160876;
        do
        {
          if ( *((_BYTE *)&this->m_EquipData + v11 + 245) )
            (**(void ( ***)(char *, _DWORD))v12)(v12, 0);
          ++v11;
          v12 += 4892;
        }
        while ( v11 < 5 );
        v13 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, *((_DWORD *)&this->m_EquipData + 67));
        nItemID = *v13;
        v14 = v13[1];
        v58 = v14;
        v15 = v13[2];
        v59 = v15;
        if ( !v15 || v14 <= 0 )
        {
          *((_BYTE *)&this->m_EquipData + 276) = 0;
          v20 = (char *)this + 160876;
          v21 = 5;
          do
          {
            (**(void ( ***)(char *, _DWORD))v20)(v20, 0);
            v20 += 4892;
            --v21;
          }
          while ( v21 );
          *((_BYTE *)&this->m_EquipData + 278) = 0;
          *((_BYTE *)&this->m_EquipData + 277) = 0;
          this->SetGroupVisible(1u);
          return;
        }
        if ( *((_DWORD *)&this->m_EquipData + 65) )
        {
          v17 = v56;
          if ( ((PAL_GDB *)this)->IsValidItem((int)&nItemID) )
            goto LABEL_25;
          goto LABEL_40;
        }
        v16 = *(_BYTE *)(v15 + 629);
        if ( v16 == 1 )
        {
          v17 = v56;
          if ( ((PAL_GDB *)this)->IsValidItem((int)&nItemID) )
          {
LABEL_25:
            (**((void ( ***)(char *, int))this + 1223 * v17 + 40219))((char *)this + 4892 * v17 + 160876, 1);
            goto LABEL_40;
          }
          ((PAL_GDB *)this)->SelectBestTarget(*((_DWORD *)&this->m_EquipData + 67));
LABEL_40:
          v22 = *((_BYTE *)&this->m_EquipData + 276);
          *((_DWORD *)&this->m_EquipData + 63) = v17;
          if ( !v22 )
          {
            ((StateUI *)this)->DisplayCaption(v17);
            if ( !*((_BYTE *)&this->m_EquipData + 277) )
              ((MainEquipUI *)this)->SetupRoleList(*((_DWORD *)&this->m_EquipData + 65), 1);
          }
          v52 = (char *)off_5CADC4;
          goto LABEL_170;
        }
        if ( v16 == 2 )
        {
          v18 = 0;
          v19 = (char *)this + 160876;
          do
          {
            if ( ((PAL_GDB *)this)->IsValidItem((int)&nItemID) )
              (**(void ( ***)(char *, int))v19)(v19, 1);
            ++v18;
            v19 += 4892;
          }
          while ( v18 < 5 );
        }
      }
      else
      {
        *((_BYTE *)&this->m_EquipData + 276) = 0;
      }
      v17 = v56;
      goto LABEL_40;
    case 1002:
      *(_DWORD *)&this->buf[16] = 0;
      while ( 1 )
      {
        v28 = *(_DWORD *)&this->buf[16];
        if ( *((_BYTE *)&this->m_EquipData + v28 + 245) )
        {
          if ( pszBuf == (char *)dword_56E148[v28] )
            break;
        }
        v29 = v28 + 1;
        *(_DWORD *)&this->buf[16] = v29;
        if ( v29 >= 5 )
        {
          switch ( (unsigned int)pszBuf )
          {
            case 0xA00102u:
              *((_DWORD *)this + 38695) = 0;
              if ( !*((_BYTE *)this + 154772) )
                this->InitParticleEffects(0);
              break;
            case 0xA00103u:
              *((_DWORD *)this + 38695) = 1;
              if ( !*((_BYTE *)this + 154773) )
                this->InitParticleEffects(1);
              break;
            case 0xA00104u:
              *((_DWORD *)this + 38695) = 2;
              if ( !*((_BYTE *)this + 154774) )
                this->InitParticleEffects(2);
              break;
            case 0xA00105u:
              *((_DWORD *)this + 38695) = 3;
              if ( !*((_BYTE *)this + 154775) )
                this->InitParticleEffects(3);
              break;
            case 0xA00106u:
              *((_DWORD *)this + 38695) = 5;
              if ( !*((_BYTE *)this + 154777) )
                this->InitParticleEffects(5);
              break;
            case 0xA00107u:
              *((_DWORD *)this + 38695) = 6;
              if ( !*((_BYTE *)this + 154778) )
                this->InitParticleEffects(6);
              break;
            case 0xA00108u:
              *((_DWORD *)this + 38695) = 4;
              if ( !*((_BYTE *)this + 154776) )
                this->InitParticleEffects(4);
              break;
            case 0xA00109u:
              *((_DWORD *)this + 38695) = 7;
              if ( !*((_BYTE *)this + 154779) )
                this->InitParticleEffects(7);
              break;
            default:
              return;
          }
          return;
        }
      }
      if ( *((int *)&this->m_EquipData + 67) < 0 || !*((_BYTE *)&this->m_EquipData + 277) )
        return;
      v30 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v60, *((_DWORD *)&this->m_EquipData + 67));
      nItemID = *v30;
      v58 = v30[1];
      v31 = *((_DWORD *)&this->m_EquipData + 65);
      v32 = v30[2];
      v59 = v32;
      if ( !v31 )
      {
        if ( *(_BYTE *)(v32 + 629) != 1 )
          return;
        v33 = 0;
        v34 = (char *)this + 160876;
        do
        {
          if ( *((_BYTE *)&this->m_EquipData + v33 + 245) )
            (**(void ( ***)(char *, _DWORD))v34)(v34, 0);
          ++v33;
          v34 += 4892;
        }
        while ( v33 < 5 );
        if ( !((PAL_GDB *)this)->IsValidItem((int)&nItemID) )
        {
          ((PAL_GDB *)this)->SelectBestTarget(*((_DWORD *)&this->m_EquipData + 67));
          return;
        }
        goto LABEL_97;
      }
      v35 = 0;
      v36 = (char *)this + 160876;
      do
      {
        if ( *((_BYTE *)&this->m_EquipData + v35 + 245) )
          (**(void ( ***)(char *, _DWORD))v36)(v36, 0);
        ++v35;
        v36 += 4892;
      }
      while ( v35 < 5 );
      if ( ((PAL_GDB *)this)->IsValidItem((int)&nItemID) )
      {
LABEL_97:
        (**((void ( ***)(char *, int))this + 1223 * *(_DWORD *)&this->buf[16] + 40219))(
          (char *)this + 4892 * *(_DWORD *)&this->buf[16] + 160876,
          1);
        return;
      }
      return;
    case 1003:
      switch ( (unsigned int)pszBuf )
      {
        case 0xA00102u:
          *((_DWORD *)this + 38695) = 0;
          *((_BYTE *)this + 154772) = 0;
          break;
        case 0xA00103u:
          *((_DWORD *)this + 38695) = 1;
          *((_BYTE *)this + 154773) = 0;
          break;
        case 0xA00104u:
          *((_DWORD *)this + 38695) = 2;
          *((_BYTE *)this + 154774) = 0;
          break;
        case 0xA00105u:
          *((_DWORD *)this + 38695) = 3;
          *((_BYTE *)this + 154775) = 0;
          break;
        case 0xA00106u:
          *((_DWORD *)this + 38695) = 5;
          *((_BYTE *)this + 154777) = 0;
          break;
        case 0xA00107u:
          *((_DWORD *)this + 38695) = 6;
          *((_BYTE *)this + 154778) = 0;
          break;
        case 0xA00108u:
          *((_DWORD *)this + 38695) = 4;
          *((_BYTE *)this + 154776) = 0;
          break;
        case 0xA00109u:
          *((_DWORD *)this + 38695) = 7;
          *((_BYTE *)this + 154779) = 0;
          break;
        default:
          return;
      }
      return;
    case 1007:
      *((_DWORD *)&this->m_EquipData + 67) = nVal2;
      if ( nVal2 < 0 )
      {
        ((UICaption *)((char *)this + 180764))->SetEnable((int)g_szSceneUIText, 0);
        ((UICaption *)((char *)this + 180916))->SetEnable((int)g_szSceneUIText, 0);
        *((_DWORD *)this + 48967) = 0;
        v39 = (char *)this + 160876;
        v40 = 5;
        do
        {
          (**(void ( ***)(char *, _DWORD))v39)(v39, 0);
          v39 += 4892;
          --v40;
        }
        while ( v40 );
        goto LABEL_129;
      }
      v41 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v61, nVal2);
      nItemID = *v41;
      v58 = v41[1];
      v42 = *v41;
      v59 = v41[2];
      ((MainEquipUI *)this)->SetSlotLabel(v42, v41[1], v41[2]);
      v43 = *(_BYTE *)(v59 + 612);
      if ( v43 == 11 )
      {
        ((CCBFiveNimbusWindow *)((char *)this + 195792))->SetFloatParam(228.0);
        ((Camera *)((char *)this + 195792))->UpdateCameraLookAt(128, 262, 600);
        goto LABEL_135;
      }
      if ( v43 == 6 )
      {
        v44 = (CCBFiveNimbusWindow *)((char *)this + 195792);
        v55 = 200.0;
LABEL_134:
        ((CCBFiveNimbusWindow *)v44)->SetFloatParam(v55);
        ((Camera *)v44)->UpdateCameraLookAt(128, 258, 600);
        goto LABEL_135;
      }
      v44 = (CCBFiveNimbusWindow *)((char *)this + 195792);
      v55 = 160.0;
      if ( *(_DWORD *)v59 != 6421 )
        goto LABEL_134;
      ((CCBFiveNimbusWindow *)((char *)this + 195792))->SetFloatParam(160.0);
      ((Camera *)v44)->UpdateCameraLookAt(128, 276, 600);
LABEL_135:
      v45 = (const char *)(v59 + 36);
      if ( !strcmp((const char *)(v59 + 36), g_szSceneUIText) )
        sprintf(&this->buf[28], byte_5967B0, "NONE");
      else
        sprintf(&this->buf[28], "Item\\%s\\%s.pol", (const char *)(v59 + 36), (const char *)(v59 + 36));
      ((PalScript *)((char *)this + 195864))->LoadModel(&this->buf[28], 0);
      if ( !strcmp((const char *)(v59 + 36), g_szSceneUIText) )
      {
        sprintf(&this->buf[28], byte_5967B0, "NONE");
      }
      else
      {
        memset(Buffer, 0, sizeof(Buffer));
        v65 = 0;
        v66 = 0;
        sprintf(Buffer, "%s%s", v45, (const char *)(v59 + 66));
        sprintf(&this->buf[28], "Item\\%s\\%s.tga", v45, Buffer);
      }
      ((gbGeomNode *)*((gbGeomNode **)this + 48970))->ReplaceTexture(&this->buf[28]);
      *((_DWORD *)this + 48967) = 1;
      return;
    case 1008:
      if ( *((int *)&this->m_EquipData + 67) >= 0 )
      {
        switch ( *((_DWORD *)&this->m_EquipData + 65) )
        {
          case 0:
            v47 = (UIListBox *)((char *)this + 187152);
            goto LABEL_153;
          case 1:
            v47 = (UIListBox *)((char *)this + 188360);
            goto LABEL_153;
          case 2:
            v47 = (UIListBox *)((char *)this + 189568);
            goto LABEL_153;
          case 3:
            v47 = (UIListBox *)((char *)this + 190776);
            goto LABEL_153;
          case 4:
            v47 = (UIListBox *)((char *)this + 191984);
LABEL_153:
            if ( *((_DWORD *)&this->m_EquipData + 67) >= ((UIListBox *)v47)->GetItemData() )
              return;
            goto LABEL_156;
          case 5:
            v47 = (UIListBox *)((char *)this + 193192);
            if ( *((_DWORD *)&this->m_EquipData + 67) >= ((UIListBox *)((char *)this + 193192))->GetItemData() )
              return;
LABEL_156:
            *((_DWORD *)&this->m_EquipData + 67) = ((NPC *)v47)->CreateChild();
LABEL_157:
            if ( ((PAL_GDB *)this)->LoadByType(*((_DWORD *)&this->m_EquipData + 67), 1) )
            {
              if ( *((_DWORD *)&this->m_EquipData + 65) == 1 )
              {
                v48 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v62, *((_DWORD *)&this->m_EquipData + 67));
                v49 = 0;
                nItemID = *v48;
                v50 = (char *)this + 160876;
                v58 = v48[1];
                v59 = v48[2];
                while ( 1 )
                {
                  if ( *((_BYTE *)&this->m_EquipData + v49 + 245) )
                  {
                    if ( ((PAL_GDB *)this)->IsValidItem((int)&nItemID) )
                    {
                      (**((void ( ***)(char *, int))this + 1223 * v49 + 40219))(
                        (char *)this + 4892 * v49 + 160876,
                        1);
LABEL_167:
                      this->SetGroupVisible(0);
                      *((_BYTE *)&this->m_EquipData + 277) = 1;
                      *((_BYTE *)&this->m_EquipData + 276) = 1;
                      v52 = off_5CADC8[0];
                      goto LABEL_170;
                    }
                    (**(void ( ***)(char *, _DWORD))v50)(v50, 0);
                  }
                  ++v49;
                  v50 += 4892;
                  if ( v49 >= 5 )
                    goto LABEL_167;
                }
              }
              ((PAL_GDB *)this)->SelectBestTarget(*((_DWORD *)&this->m_EquipData + 67));
              goto LABEL_167;
            }
            *((_BYTE *)&this->m_EquipData + 277) = 0;
            v24 = (char *)off_5CADD0;
LABEL_169:
            v52 = v24;
LABEL_170:
            v51 = CScreenMode::GetInstance();
            ((CScreenMode *)v51)->AudioSetPosition(v52, 1);
            break;
          default:
            goto LABEL_157;
        }
      }
      else
      {
        v54 = off_5CADD0;
        v46 = CScreenMode::GetInstance();
        ((CScreenMode *)v46)->AudioSetPosition(v54, 1);
LABEL_129:
        ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nVal2);
      }
      return;
    case 1009:
      return;
    case 1010:
      *((_BYTE *)&this->m_EquipData + 276) = 0;
      *((_BYTE *)&this->m_EquipData + 278) = 0;
      *((_BYTE *)&this->m_EquipData + 277) = 0;
      this->SetGroupVisible(1u);
      v37 = (char *)this + 160876;
      v38 = 5;
      do
      {
        (**(void ( ***)(char *, _DWORD))v37)(v37, 0);
        v37 += 4892;
        --v38;
      }
      while ( v38 );
      return;
    case 1020:
      *(_DWORD *)&this->buf[16] = 0;
      while ( 1 )
      {
        v25 = *(_DWORD *)&this->buf[16];
        if ( *((_BYTE *)&this->m_EquipData + v25 + 245) )
        {
          if ( pszBuf == (char *)dword_56E148[v25] )
            break;
        }
        v26 = v25 + 1;
        *(_DWORD *)&this->buf[16] = v26;
        if ( v26 >= 5 )
          return;
      }
      v27 = *((_DWORD *)&this->m_EquipData + 67);
      *((_DWORD *)&this->m_EquipData + 63) = *(_DWORD *)&this->buf[16];
      if ( v27 < 0 || !((PAL_GDB *)this)->LoadByType(v27, 1) )
        goto LABEL_72;
      ((Array *)this)->HandleItemPage(*(_DWORD *)&this->buf[16], *(_DWORD *)&this->buf[16]);
      ((StateUI *)this)->UpdateScrollValues();
      if ( !*((_BYTE *)&this->m_EquipData + 276) )
      {
        this->SetGroupVisible(1u);
LABEL_72:
        if ( !*((_BYTE *)&this->m_EquipData + 276) )
          ((StateUI *)this)->DisplayCaption(*((_DWORD *)&this->m_EquipData + 63));
      }
      *((_BYTE *)&this->m_EquipData + 244) = 1;
      return;
    default:
      goto LABEL_129;
  }
}

// 0x004A1E40
int EquipUI::InitUI()
{
  *(_DWORD *)&this->buf[8] = 800;
  *(_DWORD *)&this->buf[12] = 600;
  *(_DWORD *)&this->buf[16] = 0;
  *(_DWORD *)&this->buf[20] = 0;
  LOBYTE(this->j) = 0;
  *(_DWORD *)&this->_isCreatable = 0;
  LOBYTE(this->_flashSpeed) = 0;
  BYTE1(this->_flashSpeed) = 0;
  sub_4422E0(&this->m_EquipData);
  sub_4422E0(&this->m_EquipData.m_Dicker + 151);
  sub_4422E0((char *)&this->m_EquipData + 304);
  sub_4422E0((char *)&this->m_EquipData + 456);
  sub_4422E0((char *)&this->m_EquipData + 608);
  sub_4422E0((char *)&this->m_EquipData + 760);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0((char *)&this->m_EquipData + 4008);
  sub_4422E0((char *)&this->m_EquipData + 4176);
  sub_4422E0((char *)&this->m_EquipData + 4328);
  sub_4422E0((char *)this + 154516);
  sub_4422E0((char *)this + 154668);
  sub_4422E0((char *)this + 154820);
  sub_4422E0((char *)this + 154972);
  sub_4422E0((char *)this + 174688);
  UIScene::GetSys();
  *((_DWORD *)this + 44014) = 0;
  *((_DWORD *)this + 44015) = 0;
  *((_DWORD *)this + 44016) = 0;
  *((_DWORD *)this + 44017) = 0;
  *((_DWORD *)this + 44018) = 0;
  *((_DWORD *)this + 44019) = 0;
  *((_DWORD *)this + 44020) = 0;
  *((_DWORD *)this + 44021) = 0;
  sub_4422E0((char *)this + 176092);
  BYTE1(this->k) = 0;
  LOBYTE(this->k) = 0;
  BYTE2(this->j) = 0;
  BYTE1(this->j) = 0;
  HIBYTE(this->j) = 0;
  *((_DWORD *)this + 38622) = 0;
  *((_DWORD *)this + 38623) = 0;
  *((_DWORD *)this + 38624) = 0;
  *((_DWORD *)this + 44061) = 0;
  return (int)this;
}

// 0x004A4220
void EquipUI::Init()
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // edx
  const CHAR *v6; // ebp
  UIStatic *v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // edx
  LineupUI *v11; // eax
  int v12; // eax
  RenderTarget *v13; // eax
  int inited; // eax
  MainPropUI *v15; // eax
  int v16; // eax
  EquipUI *v17; // eax
  int v18; // eax
  CCCTData *v19; // eax
  int v20; // eax
  LineupUI *v21; // eax
  int v22; // eax
  UITitle_JDHY *v23; // eax
  int v24; // eax
  LineupUI *v25; // ecx
  int v26; // [esp+0x3C] [ebp-0x64]
  int v27; // [esp+0x54] [ebp-0x4C] BYREF
  int v28; // [esp+0x58] [ebp-0x48]
  int v29; // [esp+0x5C] [ebp-0x44]
  int v30; // [esp+0x60] [ebp-0x40]
  int v31; // [esp+0x64] [ebp-0x3C]
  int v32; // [esp+0x68] [ebp-0x38]
  int v33; // [esp+0x6C] [ebp-0x34]
  int v34; // [esp+0x70] [ebp-0x30]
  int v35; // [esp+0x74] [ebp-0x2C] BYREF
  int v36; // [esp+0x78] [ebp-0x28]
  int v37; // [esp+0x7C] [ebp-0x24]
  int v38; // [esp+0x80] [ebp-0x20]
  _DWORD v39[4]; // [esp+0x84] [ebp-0x1C] BYREF
  int v40; // [esp+0x9C] [ebp-0x4]

  v2 = *(_DWORD *)&this->buf[8];
  v3 = *(_DWORD *)&this->buf[12];
  *(_DWORD *)this->buf = v2;
  this->bkWndY = 0;
  this->bkWndX = 0;
  *(_DWORD *)&this->buf[4] = v3;
  ((UIListBox *)this)->SetSelTexture(-1, this->bkWndX, this->bkWndY, *(_DWORD *)this->buf, *(_DWORD *)&this->buf[4], 0);
  v4 = this->bkWndY + 18;
  v35 = this->bkWndX + 592;
  v36 = v4;
  v37 = v35 + 192;
  v38 = v4 + 526;
  (*(void ( **)(st_Manager *, int, int *, EquipUI *))(*(_DWORD *)&this->m_EquipData.m_Type + 16))(
    &this->m_EquipData,
    161,
    &v35,
    this);
  ((UIStatic *)&this->m_EquipData)->CreateFromTemplate();
  v5 = *(_DWORD *)(&this->m_EquipData.m_Dicker + 151);
  v36 += 26;
  v35 = v37;
  v38 = v36 + 526;
  v37 += 17;
  (*(void ( **)(_BYTE *, int, int *, EquipUI *))(v5 + 16))(
    &this->m_EquipData.m_Dicker + 151,
    161,
    &v35,
    this);
  ((UIStatic *)(&this->m_EquipData.m_Dicker + 151))->CreateFromTemplate();
  v39[1] = 14;
  v39[0] = 626;
  v39[2] = 674;
  v39[3] = 68;
  v6 = "UI\\GameMainUI\\State\\State0.tga";
  v7 = (UIStatic *)((char *)this + 174080);
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, int, _DWORD *, EquipUI *))v7->__vftable->Create)(v7, 161, v39, this);
    ((UIStatic *)v7)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v7->__vftable->ShowWindow)(v7, 0);
    v6 += 256;
    ++v7;
  }
  while ( (int)v6 < (int)"UI\\GameMainUI\\State\\Portrait0.tga" );
  v8 = *((_DWORD *)&this->m_EquipData + 76);
  v27 = v37 - 205;
  v29 = v37 - 205 + 203;
  v28 = 0;
  v30 = 64;
  (*(void ( **)(char *, int, int *, EquipUI *))(v8 + 16))((char *)&this->m_EquipData + 304, 161, &v27, this);
  ((UIStatic *)(UIStatic *)&this->m_EquipData + 2)->CreateFromTemplate();
  v9 = *((_DWORD *)&this->m_EquipData + 1082);
  v28 = -4;
  v27 = 618;
  v29 = 738;
  v30 = 28;
  (*(void ( **)(char *, int, int *, EquipUI *))(v9 + 16))((char *)&this->m_EquipData + 4328, 161, &v27, this);
  ((UIScene *)((char *)&this->m_EquipData + 4328))->SetShow(0);
  sub_446010((char *)&this->m_EquipData + 4328);
  v10 = *((_DWORD *)&this->m_EquipData + 1044);
  v28 = 16;
  v27 = 668;
  v29 = 748;
  v30 = 48;
  (*(void ( **)(char *, int, int *, EquipUI *))(v10 + 16))((char *)&this->m_EquipData + 4176, 161, &v27, this);
  ((UIScene *)((char *)&this->m_EquipData + 4176))->SetShow(0);
  sub_446010((char *)&this->m_EquipData + 4176);
  ((LineupUI *)this)->RebuildFontPage();
  v32 = 0;
  v31 = 0;
  v33 = 0;
  v34 = 32;
  ((StateUI *)this)->GetChildPtr(0);
  ((StateUI *)this)->GetChildPtr(1);
  ((StateUI *)this)->GetChildPtr(2);
  ((StateUI *)this)->GetChildPtr(3);
  ((StateUI *)this)->GetChildPtr(4);
  ((StateUI *)this)->FindChild(0);
  ((StateUI *)this)->FindChild(1);
  ((StateUI *)this)->FindChild(2);
  ((StateUI *)this)->FindChild(3);
  ((StateUI *)this)->FindChild(4);
  *((_BYTE *)this + 176089) = 0;
  *((_BYTE *)this + 176088) = g_bRoleSystem_5CEFA9;
  v11 = (LineupUI *)operator new(0x29CECu);
  v40 = 0;
  if ( v11 )
    v12 = ((LineupUI *)v11)->Save();
  else
    v12 = 0;
  v40 = -1;
  *((_DWORD *)this + 44014) = v12;
  v13 = (RenderTarget *)operator new(0x56630u);
  v40 = 1;
  if ( v13 )
    inited = ((RenderTarget *)v13)->InitChildPanels();
  else
    inited = 0;
  v40 = -1;
  *((_DWORD *)this + 44015) = inited;
  v15 = (MainPropUI *)operator new(0x35B50u);
  v40 = 2;
  if ( v15 )
    v16 = ((MainPropUI *)v15)->_MainPropUI();
  else
    v16 = 0;
  v40 = -1;
  *((_DWORD *)this + 44016) = v16;
  v17 = (EquipUI *)operator new(0x41014u);
  v40 = 3;
  if ( v17 )
    v18 = ((EquipUI *)v17)->ctor();
  else
    v18 = 0;
  v40 = -1;
  *((_DWORD *)this + 44017) = v18;
  v19 = (CCCTData *)operator new(0x62588u);
  v40 = 4;
  if ( v19 )
    // [AUTO-COMMENTED] v20 = ((CCCTData *)v19)->CCCTData();
  else
    v20 = 0;
  v40 = -1;
  *((_DWORD *)this + 44018) = v20;
  v21 = (LineupUI *)operator new(0x27BD4u);
  v40 = 5;
  if ( v21 )
    v22 = ((LineupUI *)v21)->ctor_E5C0();
  else
    v22 = 0;
  v40 = -1;
  *((_DWORD *)this + 44019) = v22;
  v23 = (UITitle_JDHY *)operator new(0x46EB8u);
  v40 = 6;
  if ( v23 )
    v24 = ((UITitle_JDHY *)v23)->DestroyPages();
  else
    v24 = 0;
  v25 = (LineupUI *)*((_DWORD *)this + 44014);
  v40 = -1;
  *((_DWORD *)this + 44020) = v24;
  ((LineupUI *)v25)->CreatePreviewScene((int)this);
  ((CameraCtrl *)*((CameraCtrl **)this + 44015))->CreateCameraUI((int)this);
  sub_496190(*((_DWORD *)this + 44016), this);
  ((MainEquipUI *)*((MainEquipUI **)this + 44017))->CreateListPanel((int)this, v26);
  ((EquipUI *)*((EquipUI **)this + 44018))->InitEquipUI((int)this);
  sub_47F590(*((_DWORD *)this + 44019), (int)this);
  ((UITitle_JDHY *)*((UITitle_JDHY **)this + 44020))->PopulateContent();
  g_bRoleFlag1 = 0;
  g_bRoleFlag2 = 0;
  BYTE1(this->_flashSpeed) = 1;
}

// 0x004A4890
int EquipUI::GetSelected()
{
  int result; // eax
  int v2; // edx
  int v3; // edx

  result = 0;
  *(_DWORD *)&this->buf[16] = 0;
  do
  {
    v2 = *(_DWORD *)&this->buf[16];
    if ( *((_BYTE *)&this->j + v2 + 1) )
      ++result;
    v3 = v2 + 1;
    *(_DWORD *)&this->buf[16] = v3;
  }
  while ( v3 < 5 );
  return result;
}

// 0x004A48B0
void EquipUI::InitSlots()
{
  unsigned int data; // [esp+0x8] [ebp+0x4]

  if ( this->GetSelected() < 5 )
  {
    BYTE1(this->j) = data;
    ((UIBase *)this)->SetItemData(0, data);
    ((EquipUI *)*((EquipUI **)this + 44015))->SetSubTab(data);
    ((EquipUI *)*((EquipUI **)this + 44016))->SelectBigMapTab0(data);
    ((EquipUI *)*((EquipUI **)this + 44017))->SetSubTab2(data);
    ((EquipUI *)*((EquipUI **)this + 44014))->SelectTab0(data);
  }
  else
  {
    BYTE1(this->j) = 0;
    ((UIBase *)this)->SetItemData(0, 0);
    ((EquipUI *)*((EquipUI **)this + 44015))->SetSubTab(0);
    ((EquipUI *)*((EquipUI **)this + 44016))->SelectBigMapTab0(0);
    ((EquipUI *)*((EquipUI **)this + 44017))->SetSubTab2(0);
    ((EquipUI *)*((EquipUI **)this + 44014))->SelectTab0(0);
  }
}

// 0x004A4C20
int EquipUI::Create()
{
  RoleSystem *v2; // edi
  int v3; // ebp
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v10; // [esp+0x18] [ebp-0x28]
  int a3[2]; // [esp+0x20] [ebp-0x20] BYREF
  int v12; // [esp+0x28] [ebp-0x18]
  int v13; // [esp+0x2C] [ebp-0x14]
  int p_DWORD; // [esp+0x30] [ebp-0x10] BYREF
  int v15; // [esp+0x34] [ebp-0xC]
  int v16; // [esp+0x38] [ebp-0x8]
  int v17; // [esp+0x3C] [ebp-0x4]

  gfxMgr->fSelfIllum = 1.0;
  lstrcpyA(byte_DE5F74, byte_DD9E3C);
  lstrcpyA(byte_DE5F77, byte_DD9F3C);
  lstrcpyA(byte_DE5F7A, byte_DDA03C);
  lstrcpyA(byte_DE5F7D, byte_DDA13C);
  lstrcpyA(byte_DE5F80, byte_DDA23C);
  lstrcpyA(byte_DE5F83, byte_DDA33C);
  lstrcpyA(byte_DE5F86, byte_DDA43C);
  lstrcpyA(byte_DE5F89, byte_DDA53C);
  lstrcpyA(byte_DE5F8C, byte_DDA63C);
  lstrcpyA(byte_DE5F8F, byte_DDA73C);
  ((CCBUIPanel *)this)->InitScrollState();

  ((StateUI *)this)->InitLayout();
  ((StateUI *)this)->CreateWidgets();
  ((MagicUI *)this)->SetSelectedData();
  ((MagicUI *)this)->Init();
  v2 = &Buffer;
  do
  {
    ((RoleSystem *)v2)->RecalcAggregatedStats(0);
    v2 = (RoleSystem *)((char *)v2 + 1408);
  }
  while ( (int)v2 < (int)&((RoleSystem *)&stru_C059A0)->m_fMoveTargetY );
  v15 = 62;
  p_DWORD = 686;
  v16 = 796;
  v17 = 157;
  a3[1] = 0;
  a3[0] = 0;
  v12 = 148;
  v13 = 530;
  v10 = 147;
  v3 = 0;
  *(_DWORD *)&this->buf[16] = 0;
  v4 = 60;
  do
  {
    v5 = *(_DWORD *)&this->buf[16];
    if ( *((_BYTE *)&this->j + v5 + 1) )
    {
      if ( ++v3 <= 4 )
      {
        ((ComposeUI *)this)->ProcessChildItem(v5, &p_DWORD);
        sub_4A3360((CHAR *)this, *(_DWORD *)&this->buf[16], a3);
        ((UIBase *)this)->SetItemData(*(_DWORD *)&this->buf[16], 1u);
        v4 += 122;
        a3[0] = v12;
        v12 += 148;
        v15 = v4;
        v17 = v4 + 95;
        v10 += 148;
      }
    }
    v6 = *(_DWORD *)&this->buf[16] + 1;
    *(_DWORD *)&this->buf[16] = v6;
  }
  while ( v6 < 5 );
  *(_DWORD *)&this->buf[16] = 0;
  do
  {
    v7 = *(_DWORD *)&this->buf[16];
    if ( !*((_BYTE *)&this->j + v7 + 1) )
    {
      ((UIBase *)this)->SetItemData(v7, 0);
      if ( v3 < 4 )
      {
        sub_445FA0((char *)this + 3788 * *(_DWORD *)&this->buf[16] + 157240);
        ((UIStatic *)((char *)this + 3788 * *(_DWORD *)&this->buf[16] + 157240))->CreateFromTemplate();
        (**((void ( ***)(char *, int))this + 947 * *(_DWORD *)&this->buf[16] + 39310))(
          (char *)this + 3788 * *(_DWORD *)&this->buf[16] + 157240,
          1);
        v10 += 148;
        ++v3;
      }
    }
    v8 = *(_DWORD *)&this->buf[16] + 1;
    *(_DWORD *)&this->buf[16] = v8;
  }
  while ( v8 < 5 );
  return ((s_RoleState *)this)->LoadAndSetupRole();
}

// 0x004AB6B0
int EquipUI::InitEquipUI(int nVal)
{
  int *p_bkWndX; // edi
  int v4; // eax
  unsigned int v5; // edx
  void *vftable; // eax
  int m_FVF; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // eax
  int v20; // edx
  int v21; // edx
  int v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // edx
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // eax
  int v32; // edx
  int v33; // eax
  int v34; // edx
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int v38; // eax
  int v39; // edx
  int v40; // edx
  int v41; // edx
  int v42; // edx
  int v43; // ecx
  int v44; // eax
  int v45; // ecx
  signed int ExecutionResourceId; // edi
  signed int v47; // esi
  int PropertyByIndex; // eax
  _BYTE *RoleNum; // eax
  int k; // eax
  int result; // eax
  float v52; // [esp+0x2B4] [ebp-E8h]
  float v53; // [esp+0x2B4] [ebp-E8h]
  int v54; // [esp+0x2B4] [ebp-E8h]
  int v55; // [esp+0x2B8] [ebp-E4h]
  char v56; // [esp+0x2BC] [ebp-E0h]
  int v57; // [esp+0x2C0] [ebp-DCh]
  int nVal5; // [esp+0x2C4] [ebp-D8h]
  int nVal5a; // [esp+0x2C4] [ebp-D8h]
  unsigned __int8 a8[4]; // [esp+0x2C8] [ebp-D4h] BYREF
  int v61; // [esp+0x2CC] [ebp-D0h]
  int v62; // [esp+0x2D0] [ebp-CCh]
  int v63; // [esp+0x2D4] [ebp-C8h]
  int v64; // [esp+0x2D8] [ebp-C4h] BYREF
  int v65; // [esp+0x2DC] [ebp-C0h]
  int v66; // [esp+0x2E0] [ebp-BCh]
  int v67; // [esp+0x2E4] [ebp-B8h]
  int v68; // [esp+0x2E8] [ebp-B4h] BYREF
  int v69; // [esp+0x2EC] [ebp-B0h]
  int v70; // [esp+0x2F0] [ebp-ACh]
  int v71; // [esp+0x2F4] [ebp-A8h]
  int v72; // [esp+0x2F8] [ebp-A4h] BYREF
  int v73; // [esp+0x2FC] [ebp-A0h]
  int v74; // [esp+0x300] [ebp-0x9C]
  int v75; // [esp+0x304] [ebp-0x98]
  int v76; // [esp+0x308] [ebp-0x94] BYREF
  int v77; // [esp+0x30C] [ebp-0x90]
  int v78; // [esp+0x310] [ebp-0x8C]
  int v79; // [esp+0x314] [ebp-0x88]
  int v80; // [esp+0x318] [ebp-0x84] BYREF
  int v81; // [esp+0x31C] [ebp-0x80]
  int v82; // [esp+0x320] [ebp-0x7C]
  int v83; // [esp+0x324] [ebp-0x78]
  signed int v84; // [esp+0x328] [ebp-0x74]
  _DWORD v85[2]; // [esp+0x32C] [ebp-0x70] BYREF
  int v86; // [esp+0x334] [ebp-0x68]
  int v87; // [esp+0x338] [ebp-0x64]
  _DWORD v88[4]; // [esp+0x33C] [ebp-0x60] BYREF
  _DWORD v89[4]; // [esp+0x34C] [ebp-0x50] BYREF
  int v90; // [esp+0x35C] [ebp-0x40] BYREF
  int v91; // [esp+0x360] [ebp-0x3C]
  int v92; // [esp+0x364] [ebp-0x38]
  int v93; // [esp+0x368] [ebp-0x34]
  _DWORD v94[4]; // [esp+0x36C] [ebp-0x30] BYREF
  _DWORD v95[4]; // [esp+0x37C] [ebp-0x20] BYREF
  _DWORD v96[4]; // [esp+0x38C] [ebp-0x10] BYREF

  p_bkWndX = &this->bkWndX;
  this->bkWndY = 0;
  this->bkWndX = 0;
  *(_DWORD *)this->buf = *(_DWORD *)&this->buf[8];
  *(_DWORD *)&this->buf[4] = *(_DWORD *)&this->buf[12];
  ((UIListBox *)this)->SetSelTexture(-1, this->bkWndX, this->bkWndY, *(_DWORD *)this->buf, *(_DWORD *)&this->buf[4], 0);
  v4 = this->bkWndY + 44;
  v85[0] = *p_bkWndX + 784;
  v85[1] = v4;
  v86 = v85[0] + 17;
  v87 = v4 + 526;
  (*(void ( **)(int *, int, _DWORD *, EquipUI *))(this->m_TempData[3].currolevalue[7] + 16))(
    &this->m_TempData[3].currolevalue[7],
    161,
    v85,
    this);
  ((UIStatic *)&this->m_TempData[3].currolevalue[7])->CreateFromTemplate();
  v5 = this->m_TempData[3].dwMagicID[2][5];
  v72 = v86 - 205;
  v74 = v86 - 205 + 203;
  v73 = 0;
  v75 = 64;
  (*(void ( **)(unsigned int *, int, int *, EquipUI *))(v5 + 16))(
    &this->m_TempData[3].dwMagicID[2][5],
    161,
    &v72,
    this);
  ((UIStatic *)&this->m_TempData[3].dwMagicID[2][5])->CreateFromTemplate();
// [VFTABLE] vftable = this->m_Arrow[0][0][0].__vftable;
  v73 = -4;
  v72 = 618;
  v74 = 738;
  v75 = 28;
  ((void ( *)(UIStatic *, int, int *, EquipUI *))vftable->Create)(this->m_Arrow[0][0], 161, &v72, this);
  ((UIScene *)this->m_Arrow)->SetShow(0);
  sub_446010(this->m_Arrow);
  m_FVF = this->m_Role[4].m_FVF;
  v73 = 16;
  v72 = 668;
  v74 = 748;
  v75 = 48;
  (*(void ( **)(int *, int, int *, EquipUI *))(m_FVF + 16))(
    &this->m_Role[4].m_FVF,
    161,
    &v72,
    this);
  ((UIScene *)&this->m_Role[4].m_FVF)->SetShow(0);
  sub_446010(&this->m_Role[4].m_FVF);
  ((SystemUI *)this)->LayoutWidgets();
  v9 = this->bkWndY + 2;
  v89[0] = *p_bkWndX + 260;
  v8 = v89[0];
  *((_WORD *)this + 89750) = 58;
  v89[2] = v8 + 256;
  v8 += 4;
  v89[1] = v9;
  *((_DWORD *)this + 44868) = v9;
  *((_DWORD *)this + 44867) = v8;
  *((_WORD *)this + 89751) = v8;
  v10 = *((_DWORD *)this + 44867);
  v89[3] = v9 + 534;
  *((_DWORD *)this + 44869) = v10 + 218;
  *((_DWORD *)this + 44870) = *((_DWORD *)this + 44868) + 356;
  *((_DWORD *)this + 44871) = *((_DWORD *)this + 44867);
  *((_DWORD *)this + 44872) = *((_DWORD *)this + 44868);
  *((_DWORD *)this + 44873) = *((_DWORD *)this + 44869);
  *((_DWORD *)this + 44874) = *((_DWORD *)this + 44870);
  (*(void ( **)(char *, int *, char *, EquipUI *))(*((_DWORD *)this + 44701) + 16))(
    (char *)this + 178804,
    dword_A00500,
    (char *)this + 179468,
    this);
  ((UIStatic *)((char *)this + 178804))->CreateFromTemplate();
  *((_DWORD *)this + 44864) = *((_DWORD *)this + 44868) + 36;
  v11 = *((_DWORD *)this + 44867) + 16;
  *((_DWORD *)this + 44863) = v11;
  *((_DWORD *)this + 44865) = v11 + 196;
  *((_DWORD *)this + 44866) = *((_DWORD *)this + 44864) + 326;
  (*(void ( **)(char *, int *, char *, EquipUI *))(*((_DWORD *)this + 44739) + 16))(
    (char *)this + 178956,
    dword_A00500,
    (char *)this + 179452,
    this);
  ((UIScene *)((char *)this + 178956))->SetShow(0);
  sub_446010((char *)this + 178956);
  ((UICaption *)((char *)this + 178956))->SetEnable((int)g_szSceneUIText, 0);
  (*(void ( **)(char *, int *, _DWORD *, EquipUI *))(*((_DWORD *)this + 44663) + 16))(
    (char *)this + 178652,
    dword_A00500,
    v89,
    this);
  ((UIStatic *)((char *)this + 178652))->CreateFromTemplate();
  v12 = *((_DWORD *)this + 44395);
  v95[1] = 10;
  v95[0] = 470;
  v95[2] = 502;
  v95[3] = 42;
  (*(void ( **)(char *, int *, _DWORD *, EquipUI *))(v12 + 16))(
    (char *)this + 177580,
    &dword_A00510,
    v95,
    this);
  ((UIStatic *)((char *)this + 177580))->CreateFromTemplate();
  v13 = *p_bkWndX;
  v14 = *((_DWORD *)this + 44357);
  v91 = this->bkWndY + 16;
  v93 = v91 + 32;
  v90 = v13 + 342;
  v92 = v13 + 470;
  (*(void ( **)(char *, __int16 *, int *, EquipUI *))(v14 + 16))(
    (char *)this + 177428,
    &word_A00572,
    &v90,
    this);
  ((UIScene *)((char *)this + 177428))->SetShow(0);
  sub_446010((char *)this + 177428);
  v15 = *((_DWORD *)this + 44433);
  v81 = 48;
  v80 = 672;
  v82 = 784;
  v83 = 160;
  (*(void ( **)(char *, char *, int *, EquipUI *))(v15 + 16))((char *)this + 177732, &byte_A00541, &v80, this);
  ((UIScene *)((char *)this + 177732))->SetShow(0);
  ((UIStatic *)((char *)this + 177732))->CreateFromTemplate();
  LOBYTE(v16) = g_bDebugMode;
  v17 = *((_DWORD *)this + 44777);
  v94[1] = 28;
  v94[0] = 506;
  v94[2] = 619;
  v94[3] = 100;
  (*(void ( **)(char *, char *, _DWORD *, EquipUI *, char *, int, int))(v17 + 28))(
    (char *)this + 179108,
    &byte_A00571,
    v94,
    this,
    "UI\\GameMainUI\\Sword\\yjfx",
    1,
    v16);
  g_bUIWnd_DE625A = 0;
  (**((void ( ***)(char *, _DWORD))this + 44777))((char *)this + 179108, 0);
  ((SaleUI *)this)->InitColumnWidths();
  v18 = *((_DWORD *)this + 44471);
  v96[1] = 131;
  v96[0] = 690;
  v96[2] = 795;
  v96[3] = 519;
  (*(void ( **)(char *, int *, _DWORD *, EquipUI *))(v18 + 16))(
    (char *)this + 177884,
    dword_A00500,
    v96,
    this);
  ((UIScene *)((char *)this + 177884))->SetShow(0);
  ((UIStatic *)((char *)this + 177884))->CreateFromTemplate();
  LOBYTE(v19) = g_bDebugMode;
  v20 = *((_DWORD *)this + 45497);
  v61 = 146;
  *(_DWORD *)a8 = 694;
  v62 = 737;
  v63 = 197;
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *, char *, _DWORD, int))(v20 + 28))(
    (char *)this + 181988,
    &byte_A00542,
    a8,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\shui_lunar",
    0,
    v19);
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *))(*((_DWORD *)this + 45927) + 16))(
    (char *)this + 183708,
    &byte_A00517,
    a8,
    this);
  ((UIStatic *)((char *)this + 183708))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 45927))((char *)this + 183708, 0);
  v21 = *((_DWORD *)this + 44877);
  *(_DWORD *)a8 = v62 - 7;
  v64 = v62 - 7;
  v62 = v62 - 7 + 43;
  v66 = v62;
  v65 = v61 + 1;
  v22 = v61 + 52;
  v67 = v61 + 52;
  LOBYTE(v22) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, EquipUI *, char *, _DWORD, int))(v21 + 28))(
    (char *)this + 179508,
    &byte_A00547,
    &v64,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\shui_Positive",
    0,
    v22);
  (*(void ( **)(char *, char *, int *, EquipUI *))(*((_DWORD *)this + 45307) + 16))(
    (char *)this + 181228,
    &byte_A00522,
    &v64,
    this);
  ((UIStatic *)((char *)this + 181228))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 45307))((char *)this + 181228, 0);
  *(_DWORD *)a8 = 694;
  v62 = 737;
  v61 = v63 + 22;
  v63 += 73;
  v23 = v63;
  LOBYTE(v23) = g_bDebugMode;
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *, char *, _DWORD, int))(*((_DWORD *)this + 45583)
                                                                                            + 28))(
    (char *)this + 182332,
    &byte_A00543,
    a8,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\huo_lunar",
    0,
    v23);
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *))(*((_DWORD *)this + 45965) + 16))(
    (char *)this + 183860,
    &byte_A00518,
    a8,
    this);
  ((UIStatic *)((char *)this + 183860))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 45965))((char *)this + 183860, 0);
  v24 = *((_DWORD *)this + 44963);
  *(_DWORD *)a8 = v62 - 7;
  v64 = v62 - 7;
  v62 = v62 - 7 + 43;
  v66 = v62;
  v65 = v61 + 1;
  v25 = v61 + 52;
  v67 = v61 + 52;
  LOBYTE(v25) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, EquipUI *, char *, _DWORD, int))(v24 + 28))(
    (char *)this + 179852,
    &byte_A00548,
    &v64,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\huo_Positive",
    0,
    v25);
  (*(void ( **)(char *, char *, int *, EquipUI *))(*((_DWORD *)this + 45345) + 16))(
    (char *)this + 181380,
    &byte_A00523,
    &v64,
    this);
  ((UIStatic *)((char *)this + 181380))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 45345))((char *)this + 181380, 0);
  v61 = v63 + 23;
  v63 += 74;
  v26 = v63;
  LOBYTE(v26) = g_bDebugMode;
  v27 = *((_DWORD *)this + 45669);
  *(_DWORD *)a8 = 694;
  v62 = 737;
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *, char *, _DWORD, int))(v27 + 28))(
    (char *)this + 182676,
    &byte_A00544,
    a8,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\lei_lunar",
    0,
    v26);
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *))(*((_DWORD *)this + 46003) + 16))(
    (char *)this + 184012,
    byte_A00519,
    a8,
    this);
  ((UIStatic *)((char *)this + 184012))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 46003))((char *)this + 184012, 0);
  v28 = *((_DWORD *)this + 45049);
  *(_DWORD *)a8 = v62 - 7;
  v64 = v62 - 7;
  v62 = v62 - 7 + 43;
  v66 = v62;
  v65 = v61 + 1;
  v29 = v61 + 52;
  v67 = v61 + 52;
  LOBYTE(v29) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, EquipUI *, char *, _DWORD, int))(v28 + 28))(
    (char *)this + 180196,
    byte_A00549,
    &v64,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\lei_Positive",
    0,
    v29);
  (*(void ( **)(char *, char *, int *, EquipUI *))(*((_DWORD *)this + 45383) + 16))(
    (char *)this + 181532,
    &byte_A00524,
    &v64,
    this);
  ((UIStatic *)((char *)this + 181532))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 45383))((char *)this + 181532, 0);
  v30 = *((_DWORD *)this + 45755);
  v61 = v63 + 23;
  v63 += 74;
  v31 = v63;
  LOBYTE(v31) = g_bDebugMode;
  *(_DWORD *)a8 = 694;
  v62 = 737;
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *, char *, _DWORD, int))(v30 + 28))(
    (char *)this + 183020,
    &byte_A00545,
    a8,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\feng_lunar",
    0,
    v31);
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *))(*((_DWORD *)this + 46041) + 16))(
    (char *)this + 184164,
    &byte_A00520,
    a8,
    this);
  ((UIStatic *)((char *)this + 184164))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 46041))((char *)this + 184164, 0);
  v32 = *((_DWORD *)this + 45135);
  *(_DWORD *)a8 = v62 - 7;
  v64 = v62 - 7;
  v62 = v62 - 7 + 43;
  v66 = v62;
  v65 = v61 + 1;
  v33 = v61 + 52;
  v67 = v61 + 52;
  LOBYTE(v33) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, EquipUI *, char *, _DWORD, int))(v32 + 28))(
    (char *)this + 180540,
    &byte_A00550,
    &v64,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\feng_Positive",
    0,
    v33);
  (*(void ( **)(char *, char *, int *, EquipUI *))(*((_DWORD *)this + 45421) + 16))(
    (char *)this + 181684,
    &byte_A00525,
    &v64,
    this);
  ((UIStatic *)((char *)this + 181684))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 45421))((char *)this + 181684, 0);
  v34 = *((_DWORD *)this + 45841);
  v61 = v63 + 24;
  v63 += 75;
  v35 = v63;
  LOBYTE(v35) = g_bDebugMode;
  *(_DWORD *)a8 = 694;
  v62 = 737;
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *, char *, _DWORD, int))(v34 + 28))(
    (char *)this + 183364,
    &byte_A00546,
    a8,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\tu_lunar",
    0,
    v35);
  (*(void ( **)(char *, char *, unsigned __int8 *, EquipUI *))(*((_DWORD *)this + 46079) + 16))(
    (char *)this + 184316,
    &byte_A00521,
    a8,
    this);
  ((UIStatic *)((char *)this + 184316))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 46079))((char *)this + 184316, 0);
  v36 = *((_DWORD *)this + 45221);
  *(_DWORD *)a8 = v62 - 7;
  v64 = v62 - 7;
  v62 = v62 - 7 + 43;
  v66 = v62;
  v65 = v61 + 1;
  v37 = v61 + 52;
  v67 = v61 + 52;
  LOBYTE(v37) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, EquipUI *, char *, _DWORD, int))(v36 + 28))(
    (char *)this + 180884,
    &byte_A00551,
    &v64,
    this,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\tu_Positive",
    0,
    v37);
  (*(void ( **)(char *, char *, int *, EquipUI *))(*((_DWORD *)this + 45459) + 16))(
    (char *)this + 181836,
    &byte_A00526,
    &v64,
    this);
  ((UIStatic *)((char *)this + 181836))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 45459))((char *)this + 181836, 0);
  v38 = *((_DWORD *)this + 46117);
  v69 = 132;
  v68 = 691;
  v70 = 779;
  v71 = 196;
  (*(void ( **)(char *, char *, int *, EquipUI *))(v38 + 16))((char *)this + 184468, &byte_A00566, &v68, this);
  ((UIStatic *)((char *)this + 184468))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 46117))((char *)this + 184468, 0);
  v39 = *((_DWORD *)this + 46155);
  v69 = v71 + 10;
  v71 += 74;
  (*(void ( **)(char *, char *, int *, EquipUI *))(v39 + 16))((char *)this + 184620, &byte_A00567, &v68, this);
  ((UIStatic *)((char *)this + 184620))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 46155))((char *)this + 184620, 0);
  v40 = *((_DWORD *)this + 46193);
  v69 = v71 + 9;
  v71 += 73;
  (*(void ( **)(char *, char *, int *, EquipUI *))(v40 + 16))((char *)this + 184772, &byte_A00568, &v68, this);
  ((UIStatic *)((char *)this + 184772))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 46193))((char *)this + 184772, 0);
  v41 = *((_DWORD *)this + 46231);
  v69 = v71 + 10;
  --v68;
  v71 += 74;
  v70 = v68 + 88;
  (*(void ( **)(char *, char *, int *, EquipUI *))(v41 + 16))((char *)this + 184924, byte_A00569, &v68, this);
  ((UIStatic *)((char *)this + 184924))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 46231))((char *)this + 184924, 0);
  v42 = *((_DWORD *)this + 46269);
  v69 = v71 + 11;
  v71 += 75;
  (*(void ( **)(char *, char *, int *, EquipUI *))(v42 + 16))((char *)this + 185076, &byte_A00570, &v68, this);
  ((UIStatic *)((char *)this + 185076))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 46269))((char *)this + 185076, 0);
  LOBYTE(v43) = g_bDebugMode;
  v44 = *((_DWORD *)this + 95454);
  v88[1] = 466;
  v88[0] = 291;
  v88[2] = 491;
  v88[3] = 526;
  (*(void ( **)(char *, char *, _DWORD *, EquipUI *, char *, int, int))(v44 + 28))(
    (char *)this + 381816,
    &byte_A00564,
    v88,
    this,
    "UI\\GameMainUI\\Sword\\Positive",
    1,
    v43);
  (**((void ( ***)(char *, _DWORD))this + 95454))((char *)this + 381816, 0);
  LOBYTE(v45) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, EquipUI *, char *, int, int))(*((_DWORD *)this + 95540) + 28))(
    (char *)this + 382160,
    &byte_A00565,
    v88,
    this,
    "UI\\GameMainUI\\Sword\\Lunar",
    1,
    v45);
  (**((void ( ***)(char *, int))this + 95540))((char *)this + 382160, 1);
  ((CCBFiveNimbusWindow *)((char *)this + 178036))->CreateScriptAndCamera((int)byte_A00539, (int)this);
  ((PalScript *)((char *)this + 178108))->LoadModel("UI\\GameMainUI\\SWORD\\Data\\Sword.pol", 0);
  *((_DWORD *)this + 44528) = 1;
  *((_DWORD *)this + 44526) = 1;
  ((CCBFiveNimbusWindow *)((char *)this + 178036))->SetFloatParam(100.0);
  ((Camera *)((char *)this + 178036))->UpdateCameraLookAt(392, 400);
  ((UIPushButton *)((char *)this + 178036))->SetAnimOffset(2, (int)this->m_TempData[2].weapon.item, v52);
  *((_DWORD *)this + 70923) = 62;
  *((_DWORD *)this + 70922) = 370;
  *((_DWORD *)this + 70924) = 450;
  *((_DWORD *)this + 70925) = 430;
  ((CCBFiveNimbusWindow *)((char *)this + 178344))->CreateScriptAndCamera((int)&byte_A00540, (int)this);
  ((PalScript *)((char *)this + 178416))->LoadModel("UI\\GameMainUI\\SWORD\\Data\\ljs.pol", 0);
  *((_DWORD *)this + 44605) = 1;
  *((_DWORD *)this + 44603) = 1;
  ((CCBFiveNimbusWindow *)((char *)this + 178344))->SetFloatParam(460.0);
  ((Camera *)((char *)this + 178344))->UpdateCameraLookAt(730, 152);
  ((UIPushButton *)((char *)this + 178344))->SetAnimOffset(1, 0, v53);
  ((PalScriptWaitObj *)(PalScriptWaitObj *)this + 47843)->ReleaseObject("UI\\GameMainUI\\Sword\\Data\\J131Src.tga");
  ((TextureLib *)((char *)this + 382744))->LoadTexture(pszPath);
  *((_DWORD *)this + 95626) = 69;
  *((_DWORD *)this + 95627) = 102;
  *((_DWORD *)this + 95628) = 179;
  *((_DWORD *)this + 95629) = 137;
  *((_DWORD *)this + 95630) = 69;
  *((_DWORD *)this + 95631) = 137;
  *((_DWORD *)this + 95632) = 179;
  *((_DWORD *)this + 95633) = 162;
  *((_DWORD *)this + 95634) = 69;
  *((_DWORD *)this + 95635) = 162;
  *((_DWORD *)this + 95636) = 179;
  *((_DWORD *)this + 95637) = 188;
  *((_DWORD *)this + 95638) = 69;
  *((_DWORD *)this + 95639) = 188;
  *((_DWORD *)this + 95640) = 179;
  *((_DWORD *)this + 95641) = 213;
  *((_DWORD *)this + 95642) = 69;
  *((_DWORD *)this + 95644) = 179;
  *((_DWORD *)this + 95643) = 213;
  *((_DWORD *)this + 95645) = 237;
  *((_DWORD *)this + 95646) = 326;
  *((_DWORD *)this + 95647) = 102;
  *((_DWORD *)this + 95648) = 436;
  *((_DWORD *)this + 95649) = 137;
  *((_DWORD *)this + 95650) = 326;
  *((_DWORD *)this + 95651) = 137;
  *((_DWORD *)this + 95652) = 436;
  *((_DWORD *)this + 95653) = 162;
  *((_DWORD *)this + 95654) = 326;
  *((_DWORD *)this + 95655) = 162;
  *((_DWORD *)this + 95656) = 436;
  *((_DWORD *)this + 95657) = 188;
  *((_DWORD *)this + 95658) = 326;
  *((_DWORD *)this + 95659) = 188;
  *((_DWORD *)this + 95660) = 436;
  *((_DWORD *)this + 95661) = 213;
  *((_DWORD *)this + 95662) = 326;
  *((_DWORD *)this + 95664) = 436;
  *((_DWORD *)this + 95663) = 213;
  *((_DWORD *)this + 95665) = 237;
  *((_DWORD *)this + 95666) = 0;
  *((_DWORD *)this + 95667) = 0;
  *((_DWORD *)this + 95668) = 110;
  *((_DWORD *)this + 95669) = 35;
  *((_DWORD *)this + 95671) = 35;
  *((_DWORD *)this + 95670) = 0;
  *((_DWORD *)this + 95672) = 110;
  *((_DWORD *)this + 95673) = 60;
  *((_DWORD *)this + 95675) = 60;
  *((_DWORD *)this + 95674) = 0;
  *((_DWORD *)this + 95676) = 110;
  *((_DWORD *)this + 95677) = 86;
  *((_DWORD *)this + 95679) = 86;
  *((_DWORD *)this + 95678) = 0;
  *((_DWORD *)this + 95680) = 110;
  *((_DWORD *)this + 95681) = 111;
  *((_DWORD *)this + 95683) = 111;
  *((_DWORD *)this + 95682) = 0;
  *((_DWORD *)this + 95684) = 110;
  *((_DWORD *)this + 95685) = 135;
  this->m_TempData[2].wear[0].item = 0;
// [IDA_MISID]   ExecutionResourceId = ((Concurrency *)&g_pGDB)->details::VirtualProcessor::GetExecutionResourceId();
  v47 = 0;
  v84 = ExecutionResourceId;
  for ( nVal5 = 0; v47 < ExecutionResourceId; nVal5 = v47 )
  {
    PropertyByIndex = ((NPC *)&g_pGDB)->GetPropertyByIndex(v47);
    RoleNum = (_BYTE *)((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(PropertyByIndex);
    if ( RoleNum[4] == 4 )
    {
      qmemcpy(&this->m_EquipData.m_Dicker + 760 * (int)this->m_TempData[2].wear[0].item + 171, RoleNum, 0x2F8u);
      ExecutionResourceId = v84;
      v47 = nVal5;
      ++this->m_TempData[2].wear[0].item;
    }
    ++v47;
  }
  k = this->k;
  v81 = 48;
  v80 = 688;
  v82 = 784;
  v83 = 80;
  (*(void ( **)(int *, char *, int *, EquipUI *))(k + 16))(&this->k, &byte_A00541, &v80, this);
  ((UIScene *)&this->k)->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&nVal5a + 1) = -5;
    LOBYTE(nVal5a) = 31;
  }
  else
  {
    *(_WORD *)((char *)&nVal5a + 1) = 8187;
    LOBYTE(nVal5a) = -1;
  }
  HIBYTE(nVal5a) = -1;
  sub_446010(&this->k);
  ((CCCTData *)this)->CreateUI();
  memset(&this->m_TempData[2].maxrolevalue[1], 0, 0x630u);
  v77 = 200;
  v76 = 288;
  v78 = 488;
  v79 = 312;
  ((ARC_PlayerAtt *)((char *)this + 400080))->Create((int)&byte_ABC001, (int)&v76);
  ((UIItem *)((char *)this + 400080))->SetData(31);
  v77 = 200;
  v76 = 241;
  v78 = 421;
  v79 = 460;
  ((ARC_PlayerAtt *)((char *)this + 401448))->Create((int)&word_ABC002, (int)&v76);
  ((UIItem *)((char *)this + 401448))->SetData(31);
  LOBYTE(result) = ((SystemUI *)this)->CreateNoteEntry(0, v54, v55, v56, v57, nVal5a, a8[0]);
  this->m_TempData[3].currolevalue[6] = nVal;
  BYTE1(this->m_TempData[2].wear[1].item) = 1;
  return result;
}
