#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Data/PAL_GDB.h"

// Forward declarations for unnamed functions
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations

LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];
extern char byte_5D8A18[4];
extern char byte_5D8A1C[4];
extern char byte_5D8A20[4];
extern char byte_5D8A24[4];
extern char byte_5D8A28[4];
extern char byte_5D8A2C[4];
extern char byte_5D8A30[8];
extern int dword_D8BBEC;
extern int dword_DC393C;
extern int dword_DC9F3C;
extern int dword_DD4B3C;
extern const char * off_58B448;
extern RoleSystem stru_C059A0;
extern char unk_5D89B0;
extern CHAR unk_5D8A00;
extern char unk_5D8A38[];
extern const char * unk_5D8A3C;
extern unsigned int unk_5DFDEC;

// 0x00457410
char PAL_GDB::LoadLanguage(char *path)
{
  PalScript *v3; // esi
  char *v4; // edi

  v3 = (PalScript *)&this->m_ItemData[508].desc[360];
  ((PalScript *)&this->m_ItemData[508].desc[360])->LoadFromFile(path);
  ((PalScript *)v3)->SetDirectory("sec1");
  if ( ((PalScript *)v3)->HasNext() )
  {
    v4 = Destination;
    do
    {
      if ( !_strcmpi((const char *)&off_58B448, (const char *)v3) )
        break;
      ((PalScript *)v3)->LoadNext();
      strncpy(v4, (const char *)v3, 0x100u);
      v4 += 256;
    }
    while ( ((PalScript *)v3)->HasNext() );
  }
  this->m_ItemData[508].desc[356] = 1;
  return 1;
}

// 0x00457F00
void PAL_GDB::RefreshSkillNumbers()
{
  int v2; // ebx
  int *v3; // edi
  int v4; // ebx
  int *v5; // edi

  if ( this->m_head.str[0] && (unsigned __int8)((PAL_GDB *)&this->m_RoleData[0].Remark[362])->PAL_GDB() )
  {
    v2 = 0;
    if ( *((int *)this + 205023) > 0 )
    {
      v3 = (int *)((char *)this + 821700);
      do
      {
        *v3 = ((PAL_GDB *)&this->m_RoleData[0].Remark[362])->GDB_GetSkillNum(*(v3 - 400));
        ++v2;
        ++v3;
      }
      while ( v2 < *((_DWORD *)this + 205023) );
    }
    v4 = 0;
    if ( *((int *)this + 205024) > 0 )
    {
      v5 = (int *)((char *)this + 822500);
      do
      {
        *v5 = ((PAL_GDB *)&this->m_RoleData[0].Remark[362])->GDB_GetSkillNum(*(v5 - 400));
        ++v4;
        ++v5;
      }
      while ( v4 < *((_DWORD *)this + 205024) );
    }
  }
}

// 0x00460A90
int PAL_GDB::UpdateSkillPanel()
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // ebp
  int v7; // ecx
  int v8; // eax
  LONG v9; // edi
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  char *v17; // eax
  _DWORD *v18; // ecx
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // ecx
  int v25; // eax
  int v26; // edx
  unsigned int v27; // eax
  char *v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // edx
  unsigned int v32; // eax
  char *v33; // eax
  int v34; // eax
  int v35; // edx
  unsigned int v36; // eax
  char *v37; // eax
  int v38; // eax
  unsigned int v39; // edx
  unsigned int v40; // eax
  char *v41; // eax
  int v42; // eax
  unsigned int v43; // edx
  unsigned int v44; // eax
  char *v45; // eax
  int v46; // eax
  unsigned int v47; // edx
  unsigned int v48; // eax
  char *v49; // eax
  int v50; // eax
  int v51; // ecx
  int v52; // eax
  int v53; // ecx
  int **v54; // eax
  int v55; // ecx
  int *v56; // eax
  int v57; // ecx
  int v58; // eax
  LONG v59; // eax
  int v60; // eax
  int v61; // edi
  char *v62; // eax
  _DWORD *v63; // ecx
  int v64; // edx
  int v65; // eax
  int v66; // ecx
  int v67; // edx
  int v68; // eax
  int v69; // ecx
  int v70; // eax
  int result; // eax
  int v72; // eax
  int *v73; // [esp+0x0] [ebp-0x28]
  int p_DWORD; // [esp+0x10] [ebp-0x18] BYREF
  int v75; // [esp+0x14] [ebp-0x14]
  unsigned int v76; // [esp+0x18] [ebp-0x10]
  int v77; // [esp+0x1C] [ebp-0xC] BYREF
  int v78; // [esp+0x20] [ebp-0x8]
  int *v79; // [esp+0x24] [ebp-0x4]
  int v80; // [esp+0x2C] [ebp+0x4]
  char v81; // [esp+0x30] [ebp+0x8]

  if ( *(_DWORD *)&this->m_RoleData[124].Remark[74] )
  {
    operator delete(*(void **)&this->m_RoleData[124].Remark[74]);
    *(_DWORD *)&this->m_RoleData[124].Remark[74] = 0;
  }
  *(_DWORD *)&this->m_RoleData[124].Remark[74] = operator new(4 * *(_DWORD *)&this->m_RoleData[124].Remark[78]);
  v2 = *(_DWORD *)&this->m_RoleData[16].Remark[474];
  *(_DWORD *)&this->m_RoleData[124].Remark[82] = 0;
  *(_DWORD *)&this->m_RoleData[0].Remark[190] = 0;
  if ( v2 > 0 )
  {
    do
    {
      v3 = *(_DWORD *)&this->m_RoleData[0].Remark[190];
      v4 = *(_DWORD *)&this->m_RoleData[0].Remark[174];
      *(_DWORD *)&this->m_RoleData[0].Remark[194] = 0;
      if ( *(int *)(v4 + 4 * v3) > 0 )
      {
        do
        {
          *(_DWORD *)(*(_DWORD *)&this->m_RoleData[124].Remark[74] + 4 * *(_DWORD *)&this->m_RoleData[124].Remark[82]) = **(_DWORD **)&this->m_RoleData[18].Remark[4 * v3 + 378];
          v5 = *(_DWORD *)&this->m_RoleData[0].Remark[174];
          v6 = *(_DWORD *)&this->m_RoleData[0].Remark[194] + 1;
          ++*(_DWORD *)&this->m_RoleData[124].Remark[82];
          v3 = *(_DWORD *)&this->m_RoleData[0].Remark[190];
          *(_DWORD *)&this->m_RoleData[0].Remark[194] = v6;
        }
        while ( v6 < *(_DWORD *)(v5 + 4 * v3) );
      }
      if ( *(_DWORD *)&this->m_RoleData[124].Remark[82] >= *(_DWORD *)&this->m_RoleData[124].Remark[78] )
        break;
      v7 = *(_DWORD *)&this->m_RoleData[16].Remark[474];
      v8 = *(_DWORD *)&this->m_RoleData[0].Remark[190] + 1;
      *(_DWORD *)&this->m_RoleData[0].Remark[190] = v8;
    }
    while ( v8 < v7 );
  }
  v9 = *(_DWORD *)&this->m_RoleData[0].Remark[186];
  if ( v81 )
  {
    switch ( v80 )
    {
      case 0:
        v10 = 5 * v9;
        goto LABEL_16;
      case 1:
        v11 = 6 * v9;
        goto LABEL_14;
      case 2:
        v10 = 7 * v9;
        goto LABEL_16;
      case 3:
        v11 = 8 * v9;
LABEL_14:
        v12 = v11 / 10;
        goto LABEL_17;
      case 4:
        v10 = 9 * v9;
LABEL_16:
        v12 = v10 / 10;
LABEL_17:
        v9 = v12;
        break;
      default:
        break;
    }
  }
  (**(void ( ***)(char *, int))&this->m_RoleData[112].Remark[158])(&this->m_RoleData[112].Remark[158], 1);
  (**(void ( ***)(char *, int))&this->m_RoleData[29].Remark[454])(&this->m_RoleData[29].Remark[454], 1);
  v13 = *(_DWORD *)&this->m_RoleData[124].Remark[58];
  *(_DWORD *)&this->m_RoleData[124].Remark[50] = 0;
  switch ( v13 )
  {
    case 0:
      v14 = rand() % 2;
      ((UICaption *)&this->m_RoleData[112].Remark[158])->SetEnable((int)&this->m_RoleData[6].Remark[512 * v80 + 14 + 256 * v14], 0);
      this->m_RoleData[123].Remark[387] = 0;
      ((PAL3 *)this)->SetValue(0);
      goto LABEL_89;
    case 1:
      if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom < v9 || v9 <= 0 )
      {
        if ( *(int *)&this->m_RoleData[0].Remark[186] <= 0 )
        {
          ((UICaption *)&this->m_RoleData[112].Remark[158])->SetEnable((int)dword_DC393C, 0);
          this->m_RoleData[123].Remark[387] = 0;
          goto LABEL_89;
        }
        if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom >= v9 )
        {
          if ( v81 )
          {
            ((PAL3 *)this)->SetValue(1u);
            ((PAL3 *)this)->SetRange(0);
            sub_445E50((int)&this->m_RoleData[116].Remark[206]);
            *(_DWORD *)&this->m_RoleData[124].Remark[58] = 0;
            this->m_RoleData[123].Remark[387] = 0;
            goto LABEL_89;
          }
          ((PAL3 *)this)->SetValue(0);
          ((PAL3 *)this)->SetRange(1u);
        }
        else
        {
          ((UICaption *)&this->m_RoleData[112].Remark[158])->SetEnable((int)&this->m_RoleData[2].Remark[54], 0);
          ((PAL3 *)this)->SetValue(0);
          ((PAL3 *)this)->SetPanelStates(1u);
          ((PAL3 *)this)->SetRange(0);
        }
        sub_445E50((int)&this->m_RoleData[116].Remark[206]);
        this->m_RoleData[123].Remark[387] = 0;
      }
      else
      {
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom -= v9;
        if ( v81 )
        {
          v15 = rand() % 2;
          ((UICaption *)&this->m_RoleData[112].Remark[158])->SetEnable((int)(&this->m_RoleData[2].stealnum + 256 * v80 + 128 * v15), 0);
        }
        else
        {
          ((UICaption *)&this->m_RoleData[112].Remark[158])->SetEnable((int)&this->m_RoleData[1].Remark[394], 0);
        }
        if ( this->m_RoleData[20].rolevalue[11] )
        {
          operator delete((void *)this->m_RoleData[20].rolevalue[11]);
          this->m_RoleData[20].rolevalue[11] = 0;
        }
        v16 = *(_DWORD *)&this->m_RoleData[124].Remark[78];
        v17 = (char *)operator new(12 * v16);
        if ( v17 )
        {
          if ( v16 - 1 >= 0 )
          {
            v18 = v17 + 8;
            v19 = v16;
            do
            {
              *(v18 - 2) = 0xFFFF;
              *(v18 - 1) = 0;
              *v18 = 0;
              v18 += 3;
              --v19;
            }
            while ( v19 );
          }
        }
        else
        {
          v17 = 0;
        }
        this->m_RoleData[20].rolevalue[11] = (int)v17;
        v20 = *(_DWORD *)&this->m_RoleData[124].Remark[78];
        *(_DWORD *)&this->m_RoleData[0].Remark[190] = 0;
        if ( v20 > 0 )
        {
          do
          {
            *(_DWORD *)(this->m_RoleData[20].rolevalue[11] + 12 * *(_DWORD *)&this->m_RoleData[0].Remark[190]) = *(_DWORD *)(*(_DWORD *)&this->m_RoleData[124].Remark[74] + 4 * *(_DWORD *)&this->m_RoleData[0].Remark[190]);
            *(_DWORD *)(this->m_RoleData[20].rolevalue[11] + 12 * *(_DWORD *)&this->m_RoleData[0].Remark[190] + 4) = 1;
            *(_DWORD *)(this->m_RoleData[20].rolevalue[11] + 12 * *(_DWORD *)&this->m_RoleData[0].Remark[190] + 8) = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(_DWORD *)(*(_DWORD *)&this->m_RoleData[124].Remark[74] + 4 * *(_DWORD *)&this->m_RoleData[0].Remark[190]));
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive(this->m_RoleData[20].rolevalue[11] + 12 * *(_DWORD *)&this->m_RoleData[0].Remark[190], v73);
            v21 = *(_DWORD *)&this->m_RoleData[124].Remark[78];
            v22 = *(_DWORD *)&this->m_RoleData[0].Remark[190] + 1;
            *(_DWORD *)&this->m_RoleData[0].Remark[190] = v22;
          }
          while ( v22 < v21 );
        }
        p_DWORD = 0xFFFF;
        v75 = 0;
        v76 = 0;
        *(_DWORD *)&this->m_RoleData[0].Remark[190] = 0;
        do
        {
          if ( this->m_RoleData[30].name[*(_DWORD *)&this->m_RoleData[0].Remark[190] + 28] )
          {
            *(_DWORD *)&this->m_RoleData[0].Remark[194] = 0;
            do
            {
              v23 = *(_DWORD *)&this->m_RoleData[0].Remark[190];
              v24 = *(_DWORD *)&this->m_RoleData[0].Remark[194];
              if ( this->m_RoleData[109].Remark[6 * v23 + 407 + v24] )
              {
                switch ( v24 )
                {
                  case 0:
                    v75 = 1;
                    v25 = 1408 * v23;
                    v26 = *(int *)((char *)&Buffer.m_partyActor.m_pParticleData + v25 + 4);
                    v27 = *(unsigned int *)((char *)&Buffer.m_partyActor.m_pParticleData + v25 + 12);
                    p_DWORD = v26;
                    v76 = v27;
                    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
                    v28 = &this->m_head.str[1408 * *(_DWORD *)&this->m_RoleData[0].Remark[190]];
                    if ( *((_DWORD *)v28 + 4689) )
                    {
                      v29 = (int)(v28 + 18748);
                      goto LABEL_52;
                    }
                    break;
                  case 1:
                    v75 = 1;
                    v46 = 352 * v23;
                    v47 = Buffer.m_partyActor.m_dwMatMsg[v46 + 6];
                    v48 = Buffer.m_partyActor.m_dwMatMsg[v46 + 8];
                    p_DWORD = v47;
                    v76 = v48;
                    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
                    v49 = &this->m_head.str[1408 * *(_DWORD *)&this->m_RoleData[0].Remark[190]];
                    if ( *((_DWORD *)v49 + 4701) )
                    {
                      v29 = (int)(v49 + 18796);
                      goto LABEL_52;
                    }
                    break;
                  case 2:
                    v75 = 1;
                    v38 = 352 * v23;
                    v39 = Buffer.m_partyActor.m_dwMatMsg[v38];
                    v40 = Buffer.m_partyActor.m_dwMatMsg[v38 + 2];
                    p_DWORD = v39;
                    v76 = v40;
                    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
                    v41 = &this->m_head.str[1408 * *(_DWORD *)&this->m_RoleData[0].Remark[190]];
                    if ( *((_DWORD *)v41 + 4695) )
                    {
                      v29 = (int)(v41 + 18772);
                      goto LABEL_52;
                    }
                    break;
                  case 3:
                    v75 = 1;
                    v30 = 1408 * v23;
                    v31 = *(_DWORD *)((char *)&Buffer.m_partyActor.m_nAnimFrame + v30 + 4);
                    v32 = *(unsigned int *)((char *)&Buffer.m_partyActor.m_pParticleData + v30);
                    p_DWORD = v31;
                    v76 = v32;
                    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
                    v33 = &this->m_head.str[1408 * *(_DWORD *)&this->m_RoleData[0].Remark[190]];
                    if ( *((_DWORD *)v33 + 4686) )
                    {
                      v29 = (int)(v33 + 18736);
                      goto LABEL_52;
                    }
                    break;
                  case 4:
                    v75 = 1;
                    v34 = 1408 * v23;
                    v35 = *(int *)((char *)&Buffer.m_partyActor.m_pParticleData + v34 + 16);
                    v36 = *(_DWORD *)((char *)&Buffer.m_partyActor.m_fAnimDelta + v34);
                    p_DWORD = v35;
                    v76 = v36;
                    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
                    v37 = &this->m_head.str[1408 * *(_DWORD *)&this->m_RoleData[0].Remark[190]];
                    if ( *((_DWORD *)v37 + 4692) )
                    {
                      v29 = (int)(v37 + 18760);
                      goto LABEL_52;
                    }
                    break;
                  case 5:
                    v75 = 1;
                    v42 = 352 * v23;
                    v43 = Buffer.m_partyActor.m_dwMatMsg[v42 + 3];
                    v44 = Buffer.m_partyActor.m_dwMatMsg[v42 + 5];
                    p_DWORD = v43;
                    v76 = v44;
                    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
                    v45 = &this->m_head.str[1408 * *(_DWORD *)&this->m_RoleData[0].Remark[190]];
                    if ( *((_DWORD *)v45 + 4698) )
                    {
                      v29 = (int)(v45 + 18784);
LABEL_52:
                      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive(v29, v73);
                    }
                    break;
                  default:
                    break;
                }
              }
              v50 = *(_DWORD *)&this->m_RoleData[0].Remark[194] + 1;
              *(_DWORD *)&this->m_RoleData[0].Remark[194] = v50;
            }
            while ( v50 < 6 );
          }
          v51 = *(_DWORD *)&this->m_RoleData[0].Remark[190] + 1;
          *(_DWORD *)&this->m_RoleData[0].Remark[190] = v51;
        }
        while ( v51 < 5 );
        if ( this->m_RoleData[20].rolevalue[11] )
        {
          operator delete((void *)this->m_RoleData[20].rolevalue[11]);
          this->m_RoleData[20].rolevalue[11] = 0;
        }
        *(_DWORD *)&this->m_RoleData[124].Remark[66] = 0;
        *(_DWORD *)&this->m_RoleData[124].Remark[78] = 0;
        *(_DWORD *)&this->m_RoleData[0].Remark[186] = 0;
        sprintf(&this->m_head.str[80], "%s %d", g_szCombatFieldName, 0);
        ((UICaption *)&this->m_RoleData[119].Remark[278])->SetEnable((int)&this->m_head.str[80], 0);
        ((UICaption *)&this->m_RoleData[118].lv)->SetEnable((int)g_szSceneUIText, 0);
        v52 = *(_DWORD *)&this->m_RoleData[16].Remark[474];
        this->m_RoleData[109].rolevalue[7] = 0;
        *(_DWORD *)&this->m_RoleData[0].Remark[190] = 0;
        if ( v52 > 0 )
        {
          do
          {
            *(_DWORD *)(*(_DWORD *)&this->m_RoleData[0].Remark[174] + 4 * *(_DWORD *)&this->m_RoleData[0].Remark[190]) = 0;
            sprintf(
              &this->m_head.str[80],
              &dir[20],
              *(_DWORD *)(*(_DWORD *)&this->m_RoleData[0].Remark[174] + 4 * *(_DWORD *)&this->m_RoleData[0].Remark[190]));
            ((UIListBox *)&this->m_RoleData[116].Remark[206])->SetMouseMoveSel(2, *(_DWORD *)&this->m_RoleData[0].Remark[190], &this->m_head.str[80], 0);
            v53 = *(_DWORD *)&this->m_RoleData[0].Remark[190];
            v78 = 0;
            v79 = 0;
            v54 = (int **)&this->m_RoleData[18].Remark[4 * v53 + 378];
            v77 = 0xFFFF;
            v55 = **v54;
            v78 = 1;
            v77 = v55;
            v79 = *v54;
            v56 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&v77);
            if ( v56 )
              *(_DWORD *)(*(_DWORD *)&this->m_RoleData[109].ImageID[24] + 4
                                                                        * *(_DWORD *)&this->m_RoleData[0].Remark[190]) = 99 - v56[1];
            else
              *(_DWORD *)(*(_DWORD *)&this->m_RoleData[109].ImageID[24] + 4
                                                                        * *(_DWORD *)&this->m_RoleData[0].Remark[190]) = 99;
            v57 = *(_DWORD *)&this->m_RoleData[16].Remark[474];
            v58 = *(_DWORD *)&this->m_RoleData[0].Remark[190] + 1;
            *(_DWORD *)&this->m_RoleData[0].Remark[190] = v58;
          }
          while ( v58 < v57 );
        }
        ((PAL3 *)this)->SetValue(0);
        sub_445E50((int)&this->m_RoleData[116].Remark[206]);
        ((PAL3 *)this)->SetRange(0);
        this->m_RoleData[123].Remark[387] = 1;
      }
      goto LABEL_89;
    case 2:
      v59 = *(_DWORD *)&this->m_RoleData[0].Remark[186];
      if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom < v59 )
      {
        ((UICaption *)&this->m_RoleData[112].Remark[158])->SetEnable((int)&this->m_RoleData[2].Remark[54], 0);
        *(_DWORD *)&this->m_RoleData[124].Remark[58] = 0;
        this->m_RoleData[123].Remark[387] = 0;
      }
      else
      {
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom -= v59;
        *(_DWORD *)&this->m_RoleData[124].Remark[50] = 0;
        v60 = rand() % 2;
        ((UICaption *)&this->m_RoleData[112].Remark[158])->SetEnable((int)&this->m_RoleData[12].Remark[512 * v80 + 42 + 256 * v60], 0);
        if ( this->m_RoleData[20].rolevalue[11] )
        {
          operator delete((void *)this->m_RoleData[20].rolevalue[11]);
          this->m_RoleData[20].rolevalue[11] = 0;
        }
        v61 = *(_DWORD *)&this->m_RoleData[124].Remark[78];
        v62 = (char *)operator new(12 * v61);
        if ( v62 )
        {
          if ( v61 - 1 >= 0 )
          {
            v63 = v62 + 8;
            v64 = v61;
            do
            {
              *(v63 - 2) = 0xFFFF;
              *(v63 - 1) = 0;
              *v63 = 0;
              v63 += 3;
              --v64;
            }
            while ( v64 );
          }
        }
        else
        {
          v62 = 0;
        }
        this->m_RoleData[20].rolevalue[11] = (int)v62;
        v65 = *(_DWORD *)&this->m_RoleData[124].Remark[78];
        *(_DWORD *)&this->m_RoleData[0].Remark[190] = 0;
        if ( v65 > 0 )
        {
          do
          {
            *(_DWORD *)(this->m_RoleData[20].rolevalue[11] + 12 * *(_DWORD *)&this->m_RoleData[0].Remark[190]) = *(_DWORD *)(*(_DWORD *)&this->m_RoleData[124].Remark[74] + 4 * *(_DWORD *)&this->m_RoleData[0].Remark[190]);
            *(_DWORD *)(this->m_RoleData[20].rolevalue[11] + 12 * *(_DWORD *)&this->m_RoleData[0].Remark[190] + 4) = 1;
            *(_DWORD *)(this->m_RoleData[20].rolevalue[11] + 12 * *(_DWORD *)&this->m_RoleData[0].Remark[190] + 8) = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(_DWORD *)(*(_DWORD *)&this->m_RoleData[124].Remark[74] + 4 * *(_DWORD *)&this->m_RoleData[0].Remark[190]));
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive(this->m_RoleData[20].rolevalue[11] + 12 * *(_DWORD *)&this->m_RoleData[0].Remark[190], v73);
            v66 = *(_DWORD *)&this->m_RoleData[124].Remark[78];
            v67 = *(_DWORD *)&this->m_RoleData[0].Remark[190] + 1;
            *(_DWORD *)&this->m_RoleData[0].Remark[190] = v67;
          }
          while ( v67 < v66 );
        }
        if ( this->m_RoleData[20].rolevalue[11] )
        {
          operator delete((void *)this->m_RoleData[20].rolevalue[11]);
          this->m_RoleData[20].rolevalue[11] = 0;
        }
        *(_DWORD *)&this->m_RoleData[124].Remark[66] = 0;
        *(_DWORD *)&this->m_RoleData[124].Remark[78] = 0;
        *(_DWORD *)&this->m_RoleData[0].Remark[186] = 0;
        sprintf(&this->m_head.str[80], "%s %d", g_szCombatFieldName, 0);
        ((UICaption *)&this->m_RoleData[119].Remark[278])->SetEnable((int)&this->m_head.str[80], 0);
        ((UICaption *)&this->m_RoleData[118].lv)->SetEnable((int)g_szSceneUIText, 0);
        v68 = *(_DWORD *)&this->m_RoleData[16].Remark[474];
        this->m_RoleData[109].rolevalue[7] = 0;
        *(_DWORD *)&this->m_RoleData[0].Remark[190] = 0;
        if ( v68 > 0 )
        {
          do
          {
            *(_DWORD *)(*(_DWORD *)&this->m_RoleData[0].Remark[174] + 4 * *(_DWORD *)&this->m_RoleData[0].Remark[190]) = 0;
            sprintf(
              &this->m_head.str[80],
              &dir[20],
              *(_DWORD *)(*(_DWORD *)&this->m_RoleData[0].Remark[174] + 4 * *(_DWORD *)&this->m_RoleData[0].Remark[190]));
            ((UIListBox *)&this->m_RoleData[116].Remark[206])->SetMouseMoveSel(2, *(_DWORD *)&this->m_RoleData[0].Remark[190], &this->m_head.str[80], 0);
            v69 = *(_DWORD *)&this->m_RoleData[16].Remark[474];
            v70 = *(_DWORD *)&this->m_RoleData[0].Remark[190] + 1;
            *(_DWORD *)&this->m_RoleData[0].Remark[190] = v70;
          }
          while ( v70 < v69 );
        }
        this->m_RoleData[123].Remark[387] = 1;
        ((PAL3 *)this)->SetValue(0);
LABEL_89:
        if ( *(_DWORD *)&this->m_RoleData[124].Remark[74] )
        {
          operator delete(*(void **)&this->m_RoleData[124].Remark[74]);
          *(_DWORD *)&this->m_RoleData[124].Remark[74] = 0;
        }
        sprintf(&this->m_head.str[80], "%s %d", (const char *)&g_bSaveFlag, ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
        ((UICaption *)&this->m_RoleData[119].Remark[110])->SetEnable((int)&this->m_head.str[80], 0);
        (**(void ( ***)(char *, _DWORD))&this->m_RoleData[117].name[16])(&this->m_RoleData[117].name[16], 0);
        (**(void ( ***)(char *, _DWORD))&this->m_RoleData[118].Remark[102])(
          &this->m_RoleData[118].Remark[102],
          0);
        return (**(int ( ***)(char *, _DWORD))&this->m_RoleData[123].Remark[234])(
                 &this->m_RoleData[123].Remark[234],
                 0);
      }
      return result;
    case 3:
      ((PAL3 *)this)->SetValue(0);
      v72 = rand() % 2;
      ((UICaption *)&this->m_RoleData[112].Remark[158])->SetEnable((int)&this->m_RoleData[9].Remark[512 * v80 + 38 + 256 * v72], 0);
      g_bListNeedsRefresh = 1;
      goto LABEL_89;
    default:
      goto LABEL_89;
  }
}

// 0x00478C00
MainEquipUI * PAL_GDB::ResetAllData()
{
  RoleAtt *m_RoleData; // ebx
  char *Remark; // ebp
  FightSkill *m_SkillData; // ebx
  char *desc; // ebp
  FightItem *m_ItemData; // ebx
  char *ModelID; // ebp
  CHAR *v7; // ebx
  char *v8; // ebp
  int v11; // [esp+0x14] [ebp-0x4]
  int v12; // [esp+0x14] [ebp-0x4]
  int v13; // [esp+0x14] [ebp-0x4]
  int v14; // [esp+0x14] [ebp-0x4]

  m_RoleData = this->m_RoleData;
  Remark = this->m_RoleData[0].Remark;
  v11 = 200;
  do
  {
    m_RoleData->id = 0;
    *((_WORD *)Remark - 1) = 0;
    lstrcpyA(Remark, g_szSceneUIText);
    lstrcpyA(Remark + 512, g_szSceneUIText);
    lstrcpyA(Remark + 542, g_szSceneUIText);
    lstrcpyA(Remark + 594, g_szSceneUIText);
    ++m_RoleData;
    memset(Remark + 630, 0, 0x30u);
    *(_DWORD *)(Remark + 774) = 0;
    Remark += 852;
    --v11;
  }
  while ( v11 );
  v12 = 300;
  m_SkillData = this->m_SkillData;
  desc = this->m_SkillData[0].desc;
  do
  {
    m_SkillData->id = 0;
    lstrcpyA(desc - 32, g_szSceneUIText);
    lstrcpyA(desc, g_szSceneUIText);
    ++m_SkillData;
    memset(desc + 532, 0, 0x18u);
    desc += 760;
    --v12;
  }
  while ( v12 );
  v13 = 500;
  m_ItemData = this->m_ItemData;
  ModelID = this->m_ItemData[0].ModelID;
  do
  {
    m_ItemData->id = 0;
    lstrcpyA(ModelID - 32, g_szSceneUIText);
    lstrcpyA(ModelID, g_szSceneUIText);
    lstrcpyA(ModelID + 30, g_szSceneUIText);
    lstrcpyA(ModelID + 60, g_szSceneUIText);
    ModelID[576] = 0;
    memset(ModelID + 608, 0, 0x18u);
    ++m_ItemData;
    ModelID += 800;
    --v13;
  }
  while ( v13 );
  v14 = 10;
  v7 = (CHAR *)&this->m_ItemData[500];
  v8 = &this->m_ItemData[500].ImageID[14];
  do
  {
    *((_DWORD *)v8 - 12) = 0;
    lstrcpyA(v7, g_szSceneUIText);
    lstrcpyA(v8, g_szSceneUIText);
    v7 += 632;
    memset(v8 + 526, 0, 0x18u);
    v8 += 632;
    --v14;
  }
  while ( v14 );
  *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
  memset(&this->m_ItemData[500], 0, 0x18B0u);
  memset(this, 0, 0xA0u);
  memset(this->m_ItemData, 0, 0x61A80u);
  memset(this->m_RoleData, 0, sizeof(this->m_RoleData));
  memset(this->m_SkillData, 0, sizeof(this->m_SkillData));
  return (MainEquipUI *)this;
}

// 0x00478E00
PAL_GDB::PAL_GDB()
{
  gbVFile *v2; // eax
  gbVFile *v3; // edi
  PAL_GDB *result; // eax
  OpenBaseFile v5; // [esp+0x84] [ebp-0x810] BYREF
  char pExceptionObject[1024]; // [esp+0x88] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x488] [ebp-0x40C] BYREF
  int v8; // [esp+0x890] [ebp-0x4]

  v8 = 0;
  v2 = ((gbVFileSystem *)g_pVFileSys)->OpenFile("cbdata\\pal3_softstar.gdb", 0x201u);
  v3 = v2;
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("Combat data couldn't found", "D:\\Project\\PAL3\\Fight\\LoadData.cpp", 38),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  ((gbVFileSystem *)g_pVFileSys)->Seek(v2, 0, 1);
  ((gbVFileSystem *)g_pVFileSys)->Read(this, 0xA0u, v3);
  ((gbVFileSystem *)g_pVFileSys)->Seek(v3, this->m_head.RolePos, 1);
  ((gbVFileSystem *)g_pVFileSys)->Read(this->m_RoleData, 852 * this->m_head.RoleNum, v3);
  ((gbVFileSystem *)g_pVFileSys)->Seek(v3, this->m_head.SkillPos, 1);
  ((gbVFileSystem *)g_pVFileSys)->Read(this->m_SkillData, 760 * this->m_head.SkillNum, v3);
  ((gbVFileSystem *)g_pVFileSys)->Seek(v3, this->m_head.ItemPos, 1);
  ((gbVFileSystem *)g_pVFileSys)->Read(this->m_ItemData, 800 * this->m_head.ItemNum, v3);
  ((gbVFileSystem *)g_pVFileSys)->Seek(v3, this->m_head.ComboPos, 1);
  ((gbVFileSystem *)g_pVFileSys)->Read(&this->m_ItemData[500], 632 * this->m_head.ComboNum, v3);
  ((gbVFileSystem *)g_pVFileSys)->CloseFile(v3);
  v8 = -1;
  LOBYTE(result) = 1;
  result;
}

// 0x00478FD0
void PAL_GDB::_PAL_GDB(int nVal)
{
  int RoleNum; // esi
  int v3; // edx

  if ( nVal )
  {
    RoleNum = this->m_head.RoleNum;
    *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
    if ( RoleNum > 0 )
    {
      do
      {
        v3 = *(_DWORD *)&this->m_ItemData[507].fightstate[10];
        if ( nVal == this->m_RoleData[v3].id )
          break;
        *(_DWORD *)&this->m_ItemData[507].fightstate[10] = v3 + 1;
      }
      while ( v3 + 1 < RoleNum );
    }
  }
}

// 0x00479040
bool PAL_GDB::GDB_LoadFile()
{
  return this->m_head.RoleNum;
}

// 0x00479050
int PAL_GDB::GDB_GetRole(unsigned int ID)
{
  if ( ID > 0xC8 )
    return 0;
  else
    return this->m_RoleData[ID].id;
}

// 0x00479080
int PAL_GDB::GDB_GetRoleNum(int nVal)
{
  int SkillNum; // edx
  int v3; // eax
  int v4; // eax

  if ( !nVal )
    return 0;
  SkillNum = this->m_head.SkillNum;
  *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
  if ( SkillNum <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *(_DWORD *)&this->m_ItemData[507].fightstate[10];
    if ( nVal == this->m_SkillData[v3].id )
      break;
    v4 = v3 + 1;
    *(_DWORD *)&this->m_ItemData[507].fightstate[10] = v4;
    if ( v4 >= SkillNum )
      return 0;
  }
  return (int)&this->m_SkillData[*(_DWORD *)&this->m_ItemData[507].fightstate[10]];
}

// 0x00479130
int PAL_GDB::GDB_GetSkillNum(int nVal)
{
  int ItemNum; // esi
  int v3; // eax
  int v4; // eax

  if ( !nVal )
    return 0;
  ItemNum = this->m_head.ItemNum;
  *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
  if ( ItemNum <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *(_DWORD *)&this->m_ItemData[507].fightstate[10];
    if ( nVal == this->m_ItemData[v3].id )
      break;
    v4 = v3 + 1;
    *(_DWORD *)&this->m_ItemData[507].fightstate[10] = v4;
    if ( v4 >= ItemNum )
      return 0;
  }
  return (int)&this->m_ItemData[*(_DWORD *)&this->m_ItemData[507].fightstate[10]];
}

// 0x004791A0
unsigned int PAL_GDB::GDB_GetSkillID()
{
  return this->m_head.ItemNum;
}

// 0x004791B0
int PAL_GDB::GetItemID(unsigned int index)
{
  if ( index > 0x1F4 )
    return 0;
  else
    return this->m_ItemData[index].id;
}

// 0x004791E0
int PAL_GDB::GDB_GetItemNum(int nVal)
{
  int ComboNum; // edx
  int v3; // eax
  int v4; // eax

  if ( !nVal )
    return 0;
  ComboNum = this->m_head.ComboNum;
  *(_DWORD *)&this->m_ItemData[507].fightstate[10] = 0;
  if ( ComboNum <= 0 )
    return 0;
  while ( 1 )
  {
    v3 = *(_DWORD *)&this->m_ItemData[507].fightstate[10];
    if ( nVal == *(_DWORD *)&this->m_ItemData[500].name[632 * v3 + 28] )
      break;
    v4 = v3 + 1;
    *(_DWORD *)&this->m_ItemData[507].fightstate[10] = v4;
    if ( v4 >= ComboNum )
      return 0;
  }
  return (int)&this->m_ItemData[500] + 632 * *(_DWORD *)&this->m_ItemData[507].fightstate[10];
}

// 0x004792C0
// attributes: thunk
unsigned int PAL_GDB::GDB_GetComboID()
{
  return accessor_004792D0(this);
}

// 0x0049C2C0
char PAL_GDB::LoadByType(unsigned int dwVal, char pData)
{
  int v4; // ebp
  char v5; // al
  int *v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // ebp
  int i; // edi
  char v11; // al
  int j; // edi
  int v13; // ecx
  char v14; // cl
  char *v15; // edi
  char *v16; // edi
  char v18; // al
  int k; // edi
  int v20; // [esp+0x10] [ebp-0x1C]
  int nItemID; // [esp+0x14] [ebp-0x18] BYREF
  int v22; // [esp+0x18] [ebp-0x14]
  int v23; // [esp+0x1C] [ebp-0x10]
  char pOut[12]; // [esp+0x20] [ebp-0xC] BYREF

  v4 = 0;
  v5 = this->m_RoleData[0].Remark[486];
  nItemID = 0xFFFF;
  v22 = 0;
  v23 = 0;
  v20 = 0;
  if ( !v5 )
  {
    if ( pData )
      this->m_RoleData[0].Remark[488] = 1;
    else
      this->m_RoleData[0].Remark[488] = 0;
  }
  v6 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, dwVal);
  v7 = *v6;
  nItemID = *v6;
  v22 = v6[1];
  v8 = v6[2];
  v23 = v8;
  if ( !v8 )
    return 0;
  switch ( *(_DWORD *)&this->m_RoleData[0].Remark[474] )
  {
    case 0:
      if ( pData )
      {
        v9 = 0;
        for ( i = 0; i < 5; ++i )
        {
          if ( this->m_RoleData[0].Remark[i + 455] )
          {
            if ( this->IsValidItem((int)&nItemID) )
              ++v9;
            v8 = v23;
          }
        }
        if ( v9 <= 0 )
          goto LABEL_74;
      }
      v11 = *(_BYTE *)(v8 + 629);
      if ( v11 != 1 && v11 != 2 )
      {
        if ( !pData )
          goto LABEL_76;
        goto LABEL_74;
      }
      for ( j = 0; j < 5; ++j )
      {
        if ( this->m_RoleData[0].Remark[j + 455] && this->IsValidItem((int)&nItemID) )
          ++v20;
      }
      if ( v20 > 0 )
        return 1;
      if ( !pData )
        goto LABEL_71;
      goto LABEL_69;
    case 1:
      if ( v7 == 6408 )
      {
        if ( !pData )
          goto LABEL_76;
LABEL_74:
        v16 = &this->m_head.str[108];
        sprintf(&this->m_head.str[108], "\\n      %s", dword_DC9F3C);
LABEL_75:
        ((UICaption *)&this->m_RoleData[182].Remark[10])->SetEnable((int)v16, 0);
        ((UIRoleSelect *)&this->m_RoleData[181].Remark[406])->SetByte(1);
LABEL_76:
        if ( !this->m_RoleData[0].Remark[486] )
          this->m_RoleData[0].Remark[488] = 0;
        return 0;
      }
      v13 = *(_DWORD *)v8;
      if ( *(_DWORD *)v8 == 6427 )
      {
        if ( ((UIScene *)"M22")->ProcessInput(0) )
        {
          if ( !pData )
            goto LABEL_76;
          goto LABEL_74;
        }
      }
      else if ( v13 != 6401 && v13 != 6405 )
      {
        v14 = *(_BYTE *)(v8 + 628);
        if ( v14 != 7 && v14 != 8 )
        {
          if ( v14 == 9 )
          {
            if ( !this->IsValidItem((int)&nItemID) )
            {
              if ( !pData )
                goto LABEL_76;
              v16 = &this->m_head.str[108];
              sprintf(&this->m_head.str[108], "\\n   %s", dword_DD4B3C);
              goto LABEL_75;
            }
            this->m_RoleData[0].Remark[488] = 1;
            this->m_RoleData[0].Remark[486] = 1;
            return 1;
          }
          if ( v14 != 10 && v14 != 11 )
          {
            if ( v14 != 15
              && !*(_WORD *)(v8 + 754)
              && !*(_WORD *)(v8 + 756)
              && !*(_WORD *)(v8 + 758)
              && !*(_WORD *)(v8 + 760) )
            {
              v18 = *(_BYTE *)(v8 + 629);
              if ( v18 != 1 && v18 != 2 )
              {
                if ( !pData )
                  goto LABEL_76;
                goto LABEL_74;
              }
              for ( k = 0; k < 5; ++k )
              {
                if ( this->m_RoleData[0].Remark[k + 455] && this->IsValidItem((int)&nItemID) )
                  ++v4;
              }
              if ( v4 <= 0 )
              {
                if ( !this->m_RoleData[0].Remark[486] )
                {
                  this->m_RoleData[0].Remark[488] = 0;
                  return 0;
                }
                return 0;
              }
            }
            return 1;
          }
        }
        if ( this->IsValidItem((int)&nItemID) )
          return 1;
        if ( pData )
        {
          v15 = &this->m_head.str[108];
          sprintf(&this->m_head.str[108], "\\n   %s", dword_DD4B3C);
LABEL_70:
          ((UICaption *)&this->m_RoleData[182].Remark[10])->SetEnable((int)v15, 0);
          ((UIRoleSelect *)&this->m_RoleData[181].Remark[406])->SetByte(1);
          goto LABEL_71;
        }
        goto LABEL_71;
      }
      if ( dword_D8BBEC == 2 )
        return 1;
      if ( pData )
      {
LABEL_69:
        v15 = &this->m_head.str[108];
        sprintf(&this->m_head.str[108], "\\n      %s", dword_DC9F3C);
        goto LABEL_70;
      }
LABEL_71:
      if ( !this->m_RoleData[0].Remark[486] )
      {
        this->m_RoleData[0].Remark[488] = 0;
        return 0;
      }
      return 0;
    case 2:
    case 3:
    case 4:
    case 5:
      if ( pData )
        goto LABEL_74;
      goto LABEL_76;
    default:
      return 1;
  }
}

// 0x0049C660
int PAL_GDB::SelectBestTarget(int nVal)
{
  PAL_GDB *v3; // ebx
  int *v4; // eax
  int v5; // edx
  char *v7; // esi
  int v8; // edi
  char *v9; // eax
  unsigned __int8 *p_m_bActionActive; // edi
  int v11; // edx
  int v12; // ebx
  _DWORD *v13; // eax
  int *v14; // esi
  __int16 v15; // bp
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  char *v21; // esi
  int v22; // edi
  int v23; // esi
  int v24; // eax
  int *v25; // ecx
  int v26; // eax
  int *v27; // edx
  int v28; // eax
  char v29; // al
  int v30; // esi
  char *v31; // edi
  int v32; // [esp+0x10] [ebp-0x60]
  __int16 *v33; // [esp+0x14] [ebp-0x5C]
  int v34; // [esp+0x18] [ebp-0x58]
  int v35; // [esp+0x1C] [ebp-0x54]
  char *v36; // [esp+0x20] [ebp-0x50]
  __int16 v37; // [esp+0x24] [ebp-0x4C]
  __int16 v38; // [esp+0x28] [ebp-0x48]
  __int16 v39; // [esp+0x2C] [ebp-0x44]
  __int16 v40; // [esp+0x30] [ebp-0x40]
  __int16 v41; // [esp+0x34] [ebp-0x3C]
  int nItemID[2]; // [esp+0x3C] [ebp-0x34] BYREF
  int v44; // [esp+0x44] [ebp-0x2C]
  _DWORD pOut[5]; // [esp+0x48] [ebp-0x28] BYREF
  _DWORD v46[5]; // [esp+0x5C] [ebp-0x14] BYREF
  char nVala; // [esp+0x74] [ebp+0x4]
v4 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, nVal);
  nItemID[0] = *v4;
  v5 = v4[1];
  memset(v46, 0, sizeof(v46));
  nItemID[1] = v5;
  v44 = v4[2];
  memset(pOut, 0, sizeof(pOut));
  v32 = 0;
  v35 = 0;
  nVala = 1;
  this->m_RoleData[0].Remark[488] = 1;
  if ( nVal < 0 )
    return -1;
  v7 = &this->m_RoleData[188].ModelID[22];
  v8 = 5;
  do
  {
    (**(void ( ***)(char *, _DWORD))v7)(v7, 0);
    v7 += 4892;
    --v8;
  }
  while ( v8 );
  v9 = &this->m_RoleData[0].Remark[455];
  v34 = 0;
  v36 = &this->m_RoleData[0].Remark[455];
  p_m_bActionActive = &Buffer.m_partyActor.m_bActionActive;
  v11 = 0;
  do
  {
    if ( *v9 )
    {
      v12 = 0;
      v37 = *(_WORD *)(v44 + 704);
      v38 = *(_WORD *)(v44 + 706);
      v39 = *(_WORD *)(v44 + 700);
      v40 = *(_WORD *)(v44 + 702);
      v41 = *(_WORD *)(v44 + 708);
      v13 = &v46[v11];
      v14 = &v46[v11];
      v33 = (__int16 *)(v44 + 644);
      do
      {
        v15 = *v33;
        if ( *v33 > 0 )
        {
          v14 = &v46[v11];
          pOut[v11] += Buffer.m_partyActor.m_dwMatMsg[v12 + 9 + v34]
                     - *(_DWORD *)&Buffer.m_partyActor.m_curact[4 * v12 + 39 + 4 * v34];
          *v13 += v15;
        }
        if ( v37 )
        {
          v14 = &v46[v11];
          v16 = *(p_m_bActionActive - 1);
          *v13 += v37;
          pOut[v11] += v16;
        }
        if ( v38 )
        {
          v14 = &v46[v11];
          v17 = *p_m_bActionActive;
          *v13 += v38;
          pOut[v11] += v17;
        }
        if ( v39 )
        {
          v14 = &v46[v11];
          v18 = *(p_m_bActionActive - 3);
          *v13 += v39;
          pOut[v11] += v18;
        }
        if ( v40 )
        {
          v14 = &v46[v11];
          v19 = *(p_m_bActionActive - 2);
          *v13 += v40;
          pOut[v11] += v19;
        }
        if ( v41 )
        {
          v14 = &v46[v11];
          v20 = p_m_bActionActive[1];
          *v13 += v41;
          pOut[v11] += v20;
        }
        if ( *v14 > 0 )
          nVala = 0;
        ++v12;
        ++v33;
      }
      while ( v12 < 12 );
}
    p_m_bActionActive += 1408;
    v9 = v36 + 1;
    ++v11;
    ++v36;
    v34 += 352;
  }
  while ( (int)p_m_bActionActive < (int)((unsigned __int8 *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[148] + 3) );
  if ( nVala )
  {
    v21 = &this->m_RoleData[188].ModelID[22];
    v22 = 5;
    do
    {
      (**(void ( ***)(char *, _DWORD))v21)(v21, 0);
      v21 += 4892;
      --v22;
    }
    while ( v22 );
    this->m_RoleData[0].Remark[488] = 0;
    return -2;
  }
  else
  {
    v23 = 0;
    v24 = 0;
    v25 = pOut;
    while ( !this->m_RoleData[0].Remark[v24 + 455] || *v25 <= 0 )
    {
      ++v24;
      ++v25;
      if ( v24 >= 5 )
        goto LABEL_35;
    }
    v23 = v24;
    v35 = pOut[v24];
LABEL_35:
    v26 = 0;
    v27 = pOut;
    do
    {
      if ( this->m_RoleData[0].Remark[v26 + 455] && *v27 >= v35 )
      {
        v35 = *v27;
        v32 = v26;
      }
      ++v26;
      ++v27;
    }
    while ( v26 < 5 );
    v28 = pOut[v32];
    if ( v28 )
    {
      if ( v28 == pOut[v23] )
        v32 = v23;
    }
    else
    {
      v32 = 0;
    }
    v29 = *(_BYTE *)(v44 + 629);
    if ( v29 == 1 )
    {
      if ( ((PAL_GDB *)v3)->IsValidItem((int)nItemID) )
        (**(void ( ***)(int, int))&this->m_RoleData[188].ModelID[4892 * v32 + 22])(
          (int)&this->m_RoleData[188].ModelID[4892 * v32 + 22],
          1);
      this->m_RoleData[0].Remark[489] = 0;
      return v32;
    }
    else if ( v29 == 2 )
    {
      v30 = 0;
      v31 = &this->m_RoleData[188].ModelID[22];
      do
      {
        if ( this->m_RoleData[0].Remark[v30 + 455] && ((PAL_GDB *)v3)->IsValidItem((int)nItemID) )
          (**(void ( ***)(char *, int))v31)(v31, 1);
        ++v30;
        v31 += 4892;
      }
      while ( v30 < 5 );
      this->m_RoleData[0].Remark[489] = 1;
      return -1;
    }
    else
    {
      return -3;
    }
  }
}

// 0x0049CA70
BOOL PAL_GDB::IsValidItem(int nItemID)
{
  BOOL result; // eax
  int v3; // ebp
  int v4; // esi
  char v5; // al
  int v6; // esi
  _BYTE *v7; // edi
  _DWORD *v8; // edx
  int v9; // esi
  _BYTE *v10; // edi
  _DWORD *v11; // edx
  int v12; // esi
  _BYTE *v13; // edi
  _DWORD *v14; // edx
  int v15; // esi
  _BYTE *v16; // edi
  _DWORD *v17; // edx
  int v18; // esi
  _BYTE *v19; // edi
  _DWORD *v20; // edx
  int v21; // edx
  _BYTE *v22; // ebx
  __int16 *v23; // edi
  int v24; // [esp+0x10] [ebp-0x4]
  int v25; // [esp+0x1C] [ebp+0x8]

  result = nItemID;
  v3 = 0;
  v24 = 0;
  if ( *(_DWORD *)nItemID == 6408 )
  {
LABEL_2:
    LOBYTE(result) = 0;
    return result;
  }
  v4 = *(_DWORD *)(nItemID + 8);
  result = *(_DWORD *)v4;
  if ( *(_DWORD *)v4 == 6427 )
  {
    result = ((UIScene *)"M22")->ProcessInput(0);
    if ( result )
    {
      LOBYTE(result) = 0;
      return result;
    }
    goto LABEL_84;
  }
  if ( result == 6401 || result == 6405 )
  {
LABEL_84:
    result = dword_D8BBEC;
    LOBYTE(result) = dword_D8BBEC == 2;
    return result;
  }
  v5 = *(_BYTE *)(v4 + 628);
  switch ( v5 )
  {
    case 5:
LABEL_7:
      LOBYTE(result) = 1;
      return result;
    case 7:
      result = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(306);
      if ( *(_BYTE *)(result + v25 + 572) )
      {
        v6 = 0;
        v7 = &Buffer.m_partyActor.m_bDirFlag + 1408 * v25 + 32;
LABEL_12:
        result = 0;
        v8 = v7;
        while ( *v8 != 306 || !*((_BYTE *)&Buffer.m_FrameA.m_rect.left + 1408 * v25 + 8 * v6 + result) )
        {
          ++result;
          ++v8;
          if ( result >= 8 )
          {
            ++v6;
            v7 += 32;
            if ( v6 < 6 )
              goto LABEL_12;
            LOBYTE(result) = 1;
            return result;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 8:
      result = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(311);
      if ( *(_BYTE *)(result + v25 + 572) )
      {
        v9 = 0;
        v10 = &Buffer.m_partyActor.m_bDirFlag + 1408 * v25 + 32;
LABEL_22:
        result = 0;
        v11 = v10;
        while ( *v11 != 311 || !*((_BYTE *)&Buffer.m_FrameA.m_rect.left + 1408 * v25 + 8 * v9 + result) )
        {
          ++result;
          ++v11;
          if ( result >= 8 )
          {
            ++v9;
            v10 += 32;
            if ( v9 < 6 )
              goto LABEL_22;
            LOBYTE(result) = 1;
            return result;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 9:
      result = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(301);
      if ( *(_BYTE *)(result + v25 + 572) )
      {
        v12 = 0;
        v13 = &Buffer.m_partyActor.m_bDirFlag + 1408 * v25 + 32;
LABEL_32:
        result = 0;
        v14 = v13;
        while ( *v14 != 301 || !*((_BYTE *)&Buffer.m_FrameA.m_rect.left + 1408 * v25 + 8 * v12 + result) )
        {
          ++result;
          ++v14;
          if ( result >= 8 )
          {
            ++v12;
            v13 += 32;
            if ( v12 < 6 )
              goto LABEL_32;
            LOBYTE(result) = 1;
            return result;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 10:
      result = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(316);
      if ( *(_BYTE *)(result + v25 + 572) )
      {
        v15 = 0;
        v16 = &Buffer.m_partyActor.m_bDirFlag + 1408 * v25 + 32;
LABEL_42:
        result = 0;
        v17 = v16;
        while ( *v17 != 316 || !*((_BYTE *)&Buffer.m_FrameA.m_rect.left + 1408 * v25 + 8 * v15 + result) )
        {
          ++result;
          ++v17;
          if ( result >= 8 )
          {
            ++v15;
            v16 += 32;
            if ( v15 < 6 )
              goto LABEL_42;
            LOBYTE(result) = 1;
            return result;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 11:
      result = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(321);
      if ( *(_BYTE *)(result + v25 + 572) )
      {
        v18 = 0;
        v19 = &Buffer.m_partyActor.m_bDirFlag + 1408 * v25 + 32;
LABEL_52:
        result = 0;
        v20 = v19;
        while ( *v20 != 321 || !*((_BYTE *)&Buffer.m_FrameA.m_rect.left + 1408 * v25 + 8 * v18 + result) )
        {
          ++result;
          ++v20;
          if ( result >= 8 )
          {
            ++v18;
            v19 += 32;
            if ( v18 < 6 )
              goto LABEL_52;
            LOBYTE(result) = 1;
            return result;
          }
        }
        goto LABEL_2;
      }
      LOBYTE(result) = 0;
      break;
    case 15:
      LOBYTE(result) = 1;
      break;
    default:
      if ( *(_WORD *)(v4 + 754) || *(_WORD *)(v4 + 756) || *(_WORD *)(v4 + 758) || *(_WORD *)(v4 + 760) )
        goto LABEL_7;
      v21 = 0;
      v22 = (_BYTE *)(v4 + 631);
      v23 = (__int16 *)(v4 + 644);
      do
      {
        if ( *v22 == 3 )
          v24 = ++v3;
        if ( *v23 > 0 )
        {
          v3 = Buffer.m_partyActor.m_dwMatMsg[352 * v25 + 9 + v21]
             - *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * v25 + 39 + 4 * v21]
             + v24;
          v24 = v3;
        }
        ++v21;
        ++v23;
        ++v22;
      }
      while ( v21 < 12 );
      if ( *(_WORD *)(v4 + 704) )
        v3 += *(&Buffer.m_partyActor.m_bActionFlag3 + 1408 * v25);
      if ( *(_WORD *)(v4 + 706) )
        v3 += *(&Buffer.m_partyActor.m_bActionActive + 1408 * v25);
      if ( *(_WORD *)(v4 + 700) )
        v3 += *(&Buffer.m_partyActor.m_nActionParam + 1408 * v25);
      if ( *(_WORD *)(v4 + 702) )
        v3 += *(&Buffer.m_partyActor.m_bActionFlag2 + 1408 * v25);
      if ( *(_WORD *)(v4 + 708) )
        v3 += *((unsigned __int8 *)&Buffer.m_partyActor.m_nActionState + 1408 * v25);
      return v3 > 0;
  }
  return result;
}

// 0x004E50B0
char * PAL_GDB::SetupSkillConfig()
{
  char *result; // eax
  int *v2; // [esp+0x0] [ebp-0x10]
  int v3[3]; // [esp+0x4] [ebp-0xC] BYREF

  v3[0] = ((PAL_GDB *)&g_pGDB)->GetItemID(index);
  v3[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v3[0]);
  v3[1] = 1;
  result = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)v3, v2);
  BYTE2(g_RoleSystemCombat.m_configData[2]) = 1;
  return result;
}

// 0x004E5500
int PAL_GDB::LoadConfigFromINI()
{
  int result; // eax
  int v3; // ebp
  int v4; // ebx
  char *v5; // edi
  CHAR ReturnedString[256]; // [esp+0x10] [ebp-0x300] BYREF
  CHAR KeyName[256]; // [esp+0x110] [ebp-0x200] BYREF
  CHAR v8[256]; // [esp+0x210] [ebp-0x100] BYREF

  GetPrivateProfileStringA("Item", "NewItem", Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
  result = atoi(ReturnedString);
  v3 = result;
  v4 = 0;
  if ( result > 0 )
  {
    v5 = &this->m_head.str[12];
    do
    {
      sprintf(KeyName, &dir[20], v4);
      GetPrivateProfileStringA("Item", KeyName, Default, v8, 0xFFu, "datascript\\combatBE.ini");
      sprintf(KeyName, "%sID", v8);
      GetPrivateProfileStringA("Item", KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
      *((_DWORD *)v5 - 1) = atoi(ReturnedString);
      sprintf(KeyName, "%sHP", v8);
      GetPrivateProfileStringA("Item", KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
      *(_DWORD *)v5 = atoi(ReturnedString);
      sprintf(KeyName, "%sGP", v8);
      GetPrivateProfileStringA("Item", KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
      *((_DWORD *)v5 + 1) = atoi(ReturnedString);
      sprintf(KeyName, "%sMP", v8);
      GetPrivateProfileStringA("Item", KeyName, Default, ReturnedString, 0xFFu, "datascript\\combatBE.ini");
      result = atoi(ReturnedString);
      *((_DWORD *)v5 + 2) = result;
      ++v4;
      v5 += 16;
    }
    while ( v4 < v3 );
  }
  return result;
}

// 0x004E56E0
char PAL_GDB::FindItemByID(int nVal, int *p_DWORD)
{
  int v3; // eax
  char *i; // ecx

  v3 = 0;
  for ( i = &this->m_head.str[8]; *(_DWORD *)i != nVal; i += 16 )
  {
    if ( ++v3 >= 500 )
      return 0;
  }
  *p_DWORD = v3;
  return 1;
}

// 0x004E5710
int PAL_GDB::GetItemPrice(int nVal)
{
  int p_DWORD; // [esp+0x8] [ebp-0x4] BYREF

  p_DWORD = -1;
  if ( this->FindItemByID(nVal, &p_DWORD) == 1 )
    return *(_DWORD *)&this->m_head.str[16 * p_DWORD + 12];
  else
    return *(__int16 *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal) + 644);
}

// 0x004E5760
int PAL_GDB::GetItemWeight(int nVal)
{
  int p_DWORD; // [esp+0x8] [ebp-0x4] BYREF

  p_DWORD = -1;
  if ( this->FindItemByID(nVal, &p_DWORD) == 1 )
    return *(_DWORD *)&this->m_head.str[16 * p_DWORD + 16];
  else
    return *(__int16 *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal) + 646);
}

// 0x004E57B0
int PAL_GDB::GetItemData(int nVal)
{
  int p_DWORD; // [esp+0x8] [ebp-0x4] BYREF

  p_DWORD = -1;
  if ( this->FindItemByID(nVal, &p_DWORD) == 1 )
    return *(_DWORD *)&this->m_head.str[16 * p_DWORD + 20];
  else
    return *(__int16 *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal) + 648);
}

// 0x004E5800
int PAL_GDB::PartySetupDialogProc(HWND hDlg, UINT pData, WPARAM a4, LPARAM a5)
{
  HWND DlgItem; // ebp
  HWND v6; // ebx
  char v8; // bl
  int *v9; // eax
  unsigned int v10; // ecx
  LRESULT v11; // eax
  LRESULT v12; // eax
  int v13; // eax
  int Role; // eax
  int v15; // edx
  int *v16; // ecx
  int v17; // eax
  int v18; // eax
  LPARAM lParam[8]; // [esp+0x10] [ebp-0x20] BYREF

  DlgItem = GetDlgItem(hDlg, 1156);
  v6 = GetDlgItem(hDlg, 1155);
  if ( pData == 78 )
  {
    if ( a4 == 1155 )
    {
      if ( *(_DWORD *)(a5 + 8) != -3 )
        return 0;
      v18 = *(_DWORD *)(a5 + 12);
      if ( v18 == -1 )
        return 0;
      if ( v18 < 5 )
      {
        if ( SceneMgr::GetValidPartyCount() > 1 )
        {
          *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + *(_DWORD *)(a5 + 12)) = 0;
          BYTE2(g_RoleSystemCombat.m_configData[4]) = 1;
          return 0;
        }
        return 0;
      }
      if ( !*(&g_pRoleSystem + v18) )
        goto LABEL_34;
      *(&g_pRoleSystem + v18) = 0;
      v17 = g_nPartyCount - 1;
    }
    else
    {
      if ( a4 != 1156 )
        return 0;
      if ( *(_DWORD *)(a5 + 8) != -3 )
        return 0;
      v13 = *(_DWORD *)(a5 + 12);
      if ( v13 == -1 )
        return 0;
      if ( v13 < 5 )
      {
        if ( SceneMgr::GetValidPartyCount() < 4 )
        {
          *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + *(_DWORD *)(a5 + 12)) = 1;
          BYTE2(Buffer.m_fMoveTargetX) = 3;
          BYTE2(Buffer.m_StaticSlotArray.m_bfocus) = 5;
          *((_BYTE *)&Buffer.m_partyUI3._todo_05C + 45) = 1;
          g_SceneMgr = 2;
          BYTE2(((RoleSystem *)&stru_C059A0)->m_fMoveTargetX) = 4;
          BYTE2(g_RoleSystemCombat.m_configData[4]) = 1;
          return 0;
        }
        return 0;
      }
      Role = ((PAL_GDB *)&g_pGDB)->GDB_GetRole(*(_DWORD *)(a5 + 12));
      v15 = 0;
      v16 = g_nPartyRoles;
      while ( *v16 )
      {
        ++v16;
        ++v15;
        if ( (int)v16 >= (int)&g_nPartyCount )
          return 0;
      }
      g_nPartyRoles[v15] = Role;
      v17 = g_nPartyCount + 1;
    }
    g_nPartyCount = v17;
LABEL_34:
    BYTE2(g_RoleSystemCombat.m_configData[4]) = 1;
    return 0;
  }
  if ( pData == 272 )
  {
    v11 = SendMessageA(v6, 0x1037u, 0, 0);
    LOBYTE(v11) = v11 | 0x21;
    SendMessageA(v6, 0x1036u, 0, v11);
    v12 = SendMessageA(DlgItem, 0x1037u, 0, 0);
    LOBYTE(v12) = v12 | 0x21;
    SendMessageA(DlgItem, 0x1036u, 0, v12);
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 7;
    lParam[1] = 0;
    lParam[2] = 150;
    lParam[3] = (LPARAM)"Name";
    SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParam);
    lParam[1] = 1;
    lParam[2] = 50;
    lParam[3] = (LPARAM)&g_EffMgr;
    SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParam);
    lParam[1] = 1;
    lParam[2] = 60;
    lParam[3] = (LPARAM)&g_EffMgr;
    SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)lParam);
    memset(lParam, 0, sizeof(lParam));
    lParam[0] = 7;
    lParam[1] = 0;
    lParam[2] = 165;
    lParam[3] = (LPARAM)"Name";
    SendMessageA(v6, 0x101Bu, 0, (LPARAM)lParam);
    lParam[1] = 1;
    lParam[2] = 50;
    lParam[3] = (LPARAM)&g_EffMgr;
    SendMessageA(v6, 0x101Bu, 1u, (LPARAM)lParam);
    BYTE1(g_RoleSystemCombat.m_configData[4]) = 1;
    return 0;
  }
  if ( pData != 273 || (unsigned __int16)a4 != 1 )
    return 0;
  if ( g_nPartyCount )
  {
    do
    {
      v8 = 0;
      v9 = &g_nPartyRoles[1];
      do
      {
        v10 = *(v9 - 1);
        if ( v10 < *v9 )
        {
          *(v9 - 1) = *v9;
          *v9 = v10;
          v8 = 1;
        }
        ++v9;
      }
      while ( (int)v9 < (int)&g_nPartyCount );
    }
    while ( v8 );
    EndDialog(hDlg, 1);
    g_RoleSystemCombat.g_hCBStageCamDlg = 0;
    return 0;
  }
  else
  {
    MessageBoxA(hWnd, &unk_5D8A00, 0, 0);
    return 0;
  }
}

// 0x004E5B20
LRESULT PAL_GDB::RefreshPartyDialog()
{
  HWND DlgItem; // ebp
  HWND v3; // ebx
  int v4; // eax
  signed int v5; // esi
  int Role; // eax
  int v7; // eax
  int v8; // ebx
  char v9; // al
  int v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // esi
  LRESULT result; // eax
  int v15; // [esp+0x10] [ebp-0x34]
  int *v16; // [esp+0x10] [ebp-0x34]
  HWND v17; // [esp+0x14] [ebp-0x30]
  int v18; // [esp+0x14] [ebp-0x30]
  LPARAM lParam[10]; // [esp+0x1C] [ebp-0x28] BYREF

  DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCBStageCamDlg, 1156);
  v3 = GetDlgItem(g_RoleSystemCombat.g_hCBStageCamDlg, 1155);
  memset(lParam, 0, sizeof(lParam));
  v17 = v3;
  SendMessageA(v3, 0x1009u, 0, 0);
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  LOBYTE(v4) = ((PAL_GDB *)&g_pGDB)->GDB_LoadFile();
  v15 = v4;

  v5 = 0;
  if ( v15 > 0 )
  {
    do
    {
      lParam[0] = 1;
      lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
      Role = ((PAL_GDB *)&g_pGDB)->GDB_GetRole(v5);
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(Role);
      v8 = v7;
      lParam[1] = v5;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, v7 + 600);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      v9 = *(_BYTE *)(v8 + 518);
      if ( v9 == 98 || v9 == 66 )
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &unk_5D8A3C);
      else
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, unk_5D8A38);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 2;
      switch ( *(_WORD *)(v8 + 4) )
      {
        case 0:
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%d%s", v5, byte_5D8A30);
          break;
        case 1:
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%d%s", v5, byte_5D8A2C);
          break;
        case 2:
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%d%s", v5, byte_5D8A28);
          break;
        case 3:
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%d%s", v5, byte_5D8A24);
          break;
        case 4:
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%d%s", v5, byte_5D8A20);
          break;
        case 5:
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%d%s", v5, byte_5D8A1C);
          break;
        case 6:
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%d%s", v5, byte_5D8A18);
          break;
        default:
          break;
      }
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v5;
    }
    while ( v5 < v15 );
    v3 = v17;
  }
  v10 = 0;
  v18 = 0;
  v16 = (int *)&this->m_RoleData[9].Remark[174];
  do
  {
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    v11 = *v16;
    lParam[1] = v10;
    if ( v11 )
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(v11);
      v13 = v12;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, v12 + 600);
      SendMessageA(v3, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      if ( *(_DWORD *)(v13 + 772) )
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &unk_5D8A3C);
      else
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, unk_5D8A38);
      result = SendMessageA(v3, 0x1006u, 0, (LPARAM)lParam);
      v10 = v18;
    }
    else
    {
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &unk_5D89B0);
      SendMessageA(v3, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], g_szSceneUIText);
      result = SendMessageA(v3, 0x1006u, 0, (LPARAM)lParam);
    }
    v18 = ++v10;
    ++v16;
  }
  while ( v10 < 11 );
  return result;
}

// 0x004E5E00
int PAL_GDB::PopulateAvailableRoles()
{
  HWND DlgItem; // ebx
  int *v3; // esi
  int v4; // eax
  bool v5; // zf
  int v6; // eax
  int v7; // esi
  int result; // eax
  bool v9; // cc
  LPARAM v10; // [esp+0x10] [ebp-0x30]
  int *v11; // [esp+0x14] [ebp-0x2C]
  LPARAM lParam[10]; // [esp+0x18] [ebp-0x28] BYREF

  DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCBStageCamDlg, 1155);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);

  v3 = (int *)&this->m_RoleData[9].Remark[174];
  v10 = 0;
  v11 = v3;
  do
  {
    v4 = *v3;
    v5 = *v3 == 0;
    lParam[0] = 1;
    lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
    lParam[1] = v10;
    if ( v5 )
    {
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &unk_5D89B0);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], g_szSceneUIText);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
    else
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(v4);
      v7 = v6;
      lParam[2] = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, v6 + 600);
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      if ( *(_DWORD *)(v7 + 772) )
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &unk_5D8A3C);
      else
        sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, unk_5D8A38);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
    result = v10 + 1;
    v3 = v11 + 1;
    v9 = ++v10 < 11;
    ++v11;
  }
  while ( v9 );
  return result;
}

// 0x004E5F60
int * PAL_GDB::UpdateInventorySlots()
{
  int *result; // eax
  char *v2; // ecx
  int v3; // edx

  memset(&this->m_RoleData[9].Remark[174], 0, 0x2Cu);
  if ( LOBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather) )
    *(_DWORD *)&this->m_RoleData[9].Remark[174] = 101;
  if ( BYTE1(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather) )
    *(_DWORD *)&this->m_RoleData[9].Remark[178] = 104;
  if ( BYTE2(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather) )
    *(_DWORD *)&this->m_RoleData[9].Remark[182] = 106;
  if ( HIBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather) )
    *(_DWORD *)&this->m_RoleData[9].Remark[186] = 107;
  if ( LOBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.m_pData) )
    *(_DWORD *)&this->m_RoleData[9].Remark[190] = 102;
  result = g_nPartyRoles;
  v2 = &this->m_RoleData[9].Remark[194];
  do
  {
    v3 = *result++;
    *(_DWORD *)v2 = v3;
    v2 += 4;
  }
  while ( (int)result < (int)&g_nPartyCount );
  return result;
}

// 0x004E5FF0
int PAL_GDB::DlgProcCamera(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  return ((CCBStageCam *)g_RoleSystemCombat.m_teamSlots[263])->UpdateEditorState();
}

// 0x004EC1F0
LRESULT PAL_GDB::ShowDetailPanel(HWND hDlg)
{
  LRESULT result; // eax
  HWND v4; // ebp
  int v5; // esi
  int ItemNum; // ebx
  int RoleNum; // edi
  int SkillNum; // eax
  HWND hWnd; // [esp+0x10] [ebp-0x1C]
  HWND v10; // [esp+0x14] [ebp-0x18]
  HWND DlgItem; // [esp+0x18] [ebp-0x14]
  HWND v12; // [esp+0x1C] [ebp-0x10]
  HWND v13; // [esp+0x20] [ebp-0xC]
  HWND v14; // [esp+0x24] [ebp-0x8]
  HWND v15; // [esp+0x28] [ebp-0x4]
  char hDlga; // [esp+0x30] [ebp+0x4]

  result = *(_DWORD *)&this->m_RoleData[11].Remark[82];
  if ( result != -1 )
  {
    GetDlgItem(hDlg, 1208);
    GetDlgItem(hDlg, 1279);
    DlgItem = GetDlgItem(hDlg, 1281);
    v12 = GetDlgItem(hDlg, 1280);
    hWnd = GetDlgItem(hDlg, 1283);
    v10 = GetDlgItem(hDlg, 1282);
    GetDlgItem(hDlg, 1209);
    GetDlgItem(hDlg, 1214);
    GetDlgItem(hDlg, 1215);
    GetDlgItem(hDlg, 1216);
    GetDlgItem(hDlg, 1218);
    GetDlgItem(hDlg, 1217);
    v14 = GetDlgItem(hDlg, 1285);
    v15 = GetDlgItem(hDlg, 1284);
    v13 = GetDlgItem(hDlg, 1287);
    v4 = GetDlgItem(hDlg, 1286);
    GetDlgItem(hDlg, 1219);
    GetDlgItem(hDlg, 1220);
    GetDlgItem(hDlg, 1221);
    GetDlgItem(hDlg, 1222);
    v5 = *(_DWORD *)&this->m_RoleData[9].Remark[4 * *(_DWORD *)&this->m_RoleData[11].Remark[82] + 246];
    ItemNum = 0;
    RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v5);
    if ( RoleNum || (ItemNum = ((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(v5)) != 0 )
      SkillNum = 0;
    else
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v5);
    hDlga = 0;
    if ( RoleNum )
    {
      hDlga = *(_BYTE *)(RoleNum + 577);
    }
    else if ( ItemNum )
    {
      hDlga = *(_BYTE *)(ItemNum + 592);
    }
    else if ( SkillNum )
    {
      hDlga = *(_BYTE *)(SkillNum + 629);
    }
    EditBox_SetReadOnly(hWnd, 1);
    EditBox_SetReadOnly(v10, 0);
    EditBox_SetReadOnly(DlgItem, 0);
    EditBox_SetReadOnly(v12, 0);
    EditBox_SetReadOnly(v13, 0);
    EditBox_SetReadOnly(v4, 0);
    EditBox_SetReadOnly(v14, 0);
    EditBox_SetReadOnly(v15, 0);
    switch ( hDlga )
    {
      case 1:
        result = EditBox_SetReadOnly(v13, 1);
        break;
      case 2:
        result = EditBox_SetReadOnly(v14, 1);
        break;
      case 4:
        result = EditBox_SetReadOnly(v15, 1);
        break;
      default:
        result = EditBox_SetReadOnly(v4, 1);
        break;
    }
  }
  return result;
}

// 0x004ED8C0
int PAL_GDB::LoadSkillData()
{
  PAL_GDB *v1; // edx
  int v2; // esi
  char *v3; // eax
  int v4; // ecx
  int v5; // ecx
  int i; // edi
  int SkillNum; // eax
  char *v8; // eax
  int result; // eax
  char *v10; // ebx
  unsigned int v11; // edx
  char *v12; // edi
  void **v13; // edi
  char *v14; // edi
  char *v15; // esi
  char v16; // cl
  int v17; // eax
  unsigned int v18; // eax
  char *v19; // edi
  int v21; // [esp+0x1C] [ebp-0x4]
v2 = 0;
  v3 = &this->m_RoleData[0].Remark[474];
  do
  {
    if ( v2 >= 5 )
    {
      v3[749] = 1;
      v3[744] = 1;
      v3[745] = 1;
      v3[748] = 1;
      v3[746] = 1;
      v3[747] = 1;
      v3[11] = 0;
      v3[10] = 0;
      v3[9] = 0;
      v4 = *(_DWORD *)v3;
      if ( *(_DWORD *)v3 == 916 || v4 == 917 || v4 == 921 || v4 == 922 || v4 == 926 || v4 == 927 )
        v3[9] = 1;
      v5 = *(_DWORD *)v3;
      if ( *(_DWORD *)v3 == 918 || v5 == 919 || v5 == 920 || v5 == 923 || v5 == 928 )
        v3[10] = 1;
    }
    ++v2;
    v3 += 892;
  }
  while ( v2 < 11 );
  for ( i = 0; i < 5; ++i )
  {
    if ( !Buffer.m_partyActor.m_dwMatMsg[352 * i + 8] )
    {
      Buffer.m_partyActor.m_dwMatMsg[352 * i + 6] = 6603;
      Buffer.m_partyActor.m_dwMatMsg[352 * i + 7] = 1;
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(Buffer.m_partyActor.m_dwMatMsg[352 * i + 6]);
Buffer.m_partyActor.m_dwMatMsg[352 * i + 8] = SkillNum;
    }
    v8 = &this->m_head.str[892 * i];
    v8[648] = *(_BYTE *)(Buffer.m_partyActor.m_dwMatMsg[352 * i + 8] + 613);
    v8[651] = 0;
    v8[650] = 0;
    v8[649] = 0;
    switch ( v8[648] )
    {
      case 0:
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)307.19998 )
          goto LABEL_22;
        ++*(_DWORD *)&g_TempBuffer1024[912];
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
        goto LABEL_24;
      case 1:
      case 3:
LABEL_24:
        v8[650] = 1;
        break;
      case 4:
      case 7:
LABEL_22:
        v8[649] = 1;
        break;
      default:
        break;
    }
    v8[652] = 0;
    if ( !i )
    {
      if ( *(_DWORD *)Buffer.m_partyActor.m_dwMatMsg[8] == 6603 )
      {
        this->m_RoleData[0].Remark[486] = 1;
        *(_DWORD *)&this->m_RoleData[1].Remark[62] = *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 3);
        *(float *)&this->m_RoleData[1].Remark[66] = Buffer.m_partyActor.m_fAngleDeg;
        *(_DWORD *)&this->m_RoleData[1].Remark[70] = *((_DWORD *)&Buffer.m_partyActor.m_fAngleDeg + 1);
      }
      else
      {
        this->m_RoleData[0].Remark[486] = 0;
      }
      this->m_RoleData[0].Remark[484] = 1;
      this->m_RoleData[0].Remark[483] = 0;
    }
  }
  result = -4;
  v10 = &this->m_RoleData[0].Remark[394];
  v21 = -4;
  do
  {
    if ( result > 0 && result < 7 )
      *((_DWORD *)v10 + 144) = result;
    if ( v10[17] )
    {
      switch ( *((_DWORD *)v10 - 2) )
      {
        case 'e':
          v11 = strlen((const char *)&g_pfnUpdateFuncs[4]) + 1;
          v12 = (char *)&g_pfnUpdateFuncs[4] + v11;
          goto LABEL_42;
        case 'f':
          v11 = strlen((const char *)g_pfnUpdateFuncs) + 1;
          v12 = (char *)g_pfnUpdateFuncs + v11;
          goto LABEL_42;
        case 'h':
          v13 = &g_pfnUpdateFuncs[3];
          goto LABEL_45;
        case 'j':
          v11 = strlen(a106) + 1;
          v12 = &a106[v11];
LABEL_42:
          qmemcpy(v10, &v12[-v11], 4 * (v11 >> 2));
          v15 = &v12[4 * (v11 >> 2) - v11];
          v14 = &v10[4 * (v11 >> 2)];
          v16 = v11;
          goto LABEL_46;
        case 'k':
          v13 = &g_pfnUpdateFuncs[1];
          goto LABEL_45;
        default:
          ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)v10 - 2));
          if ( !v17 )
            break;
          v13 = (void **)(v17 + 518);
LABEL_45:
          v18 = strlen((const char *)v13) + 1;
          v19 = (char *)v13 + v18;
          qmemcpy(v10, &v19[-v18], 4 * (v18 >> 2));
          v15 = &v19[4 * (v18 >> 2) - v18];
          v14 = &v10[4 * (v18 >> 2)];
          v16 = v18;
LABEL_46:
          qmemcpy(v14, v15, v16 & 3);
          break;
      }
    }
    v10 += 892;
    result = v21 + 1;
    v21 = result;
  }
  while ( result + 4 < 11 );
  return result;
}

// 0x004F69F0
bool PAL_GDB::IsItemConsumable(int nItemId)
{
  char v2; // al

  v2 = *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nItemId) + 4);
  return v2 == 3 || v2 == 2 || v2 == 1;
}

// 0x004F6A20
bool PAL_GDB::IsItemEquipment(int nItemId)
{
  return *(_BYTE *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nItemId) + 4) == 2;
}

// 0x004F6A40
bool PAL_GDB::IsRoleAlive(int nRoleId)
{
  return *(_WORD *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nRoleId) + 592) > 0;
}

// 0x004F6A60
bool PAL_GDB::IsRoleDead(int nRoleId)
{
  return *(__int16 *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nRoleId) + 592) < 0;
}

// 0x004F6A80
bool PAL_GDB::IsRoleAlive2(int nVal)
{
  int RoleNum; // eax

  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nVal);
  return !RoleNum || *(_BYTE *)(RoleNum + 577) > 2u;
}

// 0x004F6AB0
bool PAL_GDB::IsItemConsumed(int nItemId)
{
  return *(__int16 *)(((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(nItemId) + 606) < 0;
}

// 0x004F6AD0
bool PAL_GDB::GetSkillLevel(int nVal)
{
  int SkillNum; // eax
  unsigned __int8 v3; // cl

  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal);
  if ( SkillNum && *(_BYTE *)(SkillNum + 612) == 1 )
  {
    v3 = *(_BYTE *)(SkillNum + 631);
    if ( v3 <= 1u )
      return *(_WORD *)(SkillNum + 644) > 0;
    if ( v3 == 2 )
      return 1;
  }
  return 0;
}

// 0x004F6B20
bool PAL_GDB::GetSkillType(int nVal)
{
  int SkillNum; // eax
  unsigned __int8 v3; // cl

  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal);
  if ( SkillNum && *(_BYTE *)(SkillNum + 612) == 1 )
  {
    v3 = *(_BYTE *)(SkillNum + 633);
    if ( v3 <= 1u )
      return *(_WORD *)(SkillNum + 648) > 0;
    if ( v3 == 2 )
      return 1;
  }
  return 0;
}

// 0x004F6B70
bool PAL_GDB::IsSkillUsable(int nVal)
{
  int SkillNum; // eax

  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal);
  return *(_BYTE *)(SkillNum + 612) == 2 && *(_BYTE *)(SkillNum + 631) <= 1u && *(__int16 *)(SkillNum + 644) < 0;
}

// 0x004F6BB0
bool PAL_GDB::IsSkillEmpty(int nVal)
{
  int SkillNum; // eax

  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal);
  return !SkillNum || *(_BYTE *)(SkillNum + 612) == 2;
}

// 0x004F6BE0
char PAL_GDB::SearchAllItems(int nVal, int *p_DWORD, int *pnVal, int *p_DWORD2)
{
  int v5; // edi
  int v6; // ebx
  int v7; // esi
  int v8; // eax
  int *v9; // edx
  int v11; // [esp+0x10] [ebp-0x4]

  v5 = 0;
  v11 = 0;
LABEL_2:
  v6 = 0;
  v7 = 0;
LABEL_3:
  v8 = 0;
  v9 = &this->m_RoleData[0].att[v5 + 1 + v7];
  while ( *v9 != nVal )
  {
    ++v8;
    ++v9;
    if ( v8 >= 8 )
    {
      v7 += 8;
      ++v6;
      if ( v7 < 48 )
        goto LABEL_3;
      v5 += 223;
      ++v11;
      if ( v5 >= 1115 )
        return 0;
      goto LABEL_2;
    }
  }
  *p_DWORD = v6;
  *pnVal = v8;
  *p_DWORD2 = v11;
  return 1;
}

// 0x004F6C60
char PAL_GDB::SearchItemLoop(int nVal, int nVal2, int *p_DWORD, int *pnVal)
{
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int *v8; // edx

  v5 = 0;
  v6 = 0;
  while ( 2 )
  {
    v7 = 0;
    v8 = &this->m_RoleData[0].att[223 * nVal + 1 + v6];
    do
    {
      if ( *v8 == nVal2 )
      {
        *p_DWORD = v5;
        *pnVal = v7;
        return 1;
      }
      ++v7;
      ++v8;
    }
    while ( v7 < 8 );
    v6 += 8;
    ++v5;
    if ( v6 < 48 )
      continue;
    break;
  }
  return 0;
}

// 0x004F6D30
char PAL_GDB::IsRoleSkillValid(unsigned int *pdwVal, int nVal)
{
  unsigned int v3; // eax

  v3 = *pdwVal;
  if ( *pdwVal >= 0x104 )
  {
    if ( v3 <= 0x105 )
    {
      if ( *(_WORD *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pdwVal[1]) + 2 * nVal + 616) == 2 )
        return 1;
    }
    else if ( v3 == 262 && *(_WORD *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(pdwVal[1]) + 2 * nVal + 698) == 2 )
    {
      return 1;
    }
  }
  return 0;
}

// 0x004F6E80
char PAL_GDB::IterateInventory(int *p_DWORD)
{
  unsigned int v3; // edx
  int v4; // esi
  int v5; // eax
  char *j; // edx
  int v7; // eax
  int v8; // ebx
  int v9; // esi
  int *v10; // edi
  int v11; // ecx
  int v12; // eax
  _DWORD *i; // eax
  int *p_DWORDa; // [esp+0x18] [ebp+0x4]

  if ( *p_DWORD != 262 )
  {
    v3 = p_DWORD[2];
    v4 = 0;
    if ( v3 > 4 )
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(_DWORD *)&this->m_RoleData[0].Remark[892 * v3 + 386]);
      v11 = 0;
      for ( i = (_DWORD *)(v12 + 760); *i != p_DWORD[1]; ++i )
      {
        if ( ++v11 >= 4 )
          return 0;
      }
    }
    else if ( *p_DWORD == 260 )
    {
      v5 = 892 * v3;
      for ( j = &this->m_RoleData[0].ImageID[892 * v3 + 4];
            *(_DWORD *)j != p_DWORD[1] || !this->m_RoleData[0].ImageID[v5 + 28 + v4];
            j += 4 )
      {
        if ( ++v4 >= 6 )
          return 0;
      }
    }
    else
    {
      v7 = p_DWORD[1];
      p_DWORDa = 0;
      v8 = 936;
LABEL_11:
      v9 = 0;
      v10 = (int *)((char *)&p_DWORDa[223 * v3 + 186] + (_DWORD)this);
      while ( *v10 != v7 || !this->m_head.str[892 * v3 + v9 + v8] )
      {
        ++v9;
        ++v10;
        if ( v9 >= 8 )
        {
          v8 += 8;
          p_DWORDa += 8;
          if ( v8 < 984 )
            goto LABEL_11;
          return 0;
        }
      }
    }
  }
  return 1;
}

// 0x004F6FB0
char PAL_GDB::BuildItemArray(int nVal)
{
  int v3; // eax
  int SlotCount; // ebx
  int v5; // esi
  _BYTE pOut[12]; // [esp+0x10] [ebp-0x18] BYREF
  _BYTE v8[12]; // [esp+0x1C] [ebp-0xC] BYREF

  v3 = *(_DWORD *)(nVal + 8);
  if ( v3 >= 5 && v3 < 11 )
    return 0;
  SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
  v5 = 0;
  if ( SlotCount <= 0 )
    return 0;
  while ( *(_DWORD *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut) != *(_DWORD *)(nVal + 4)
       || *((int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v8) + 1) <= 0
       || ((CCBSystem *)this)->IsMagicSlotMsg(nVal) && !((CCBSystem *)this)->HandleMagicCommand(nVal) )
  {
    if ( ++v5 >= SlotCount )
      return 0;
  }
  return 1;
}

// 0x00526300
gbGeomNode * PAL_GDB::RefreshPartyStats()
{
  char *v1; // esi
  int *p_shikuaisucc; // edi
  float *v3; // ebx
  int v4; // ebp
  int SkillNum; // eax
  int v6; // eax
  int v7; // eax
  gbGeomNode *result; // eax

  v1 = &this->m_head.str[96];
  p_shikuaisucc = (int *)&this->m_RoleData[7].shikuaisucc;
  v3 = &this->m_RoleData[4].append[8];
  v4 = 5;
  do
  {
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*p_shikuaisucc);
    sprintf(v1, "SubGame\\Appraise\\Exhibit\\Data\\%s.pol", (const char *)(SkillNum + 36));
    ((PalScript *)(v3 - 77))->LoadModel(v1, 0);
    v6 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(p_shikuaisucc[1]);
    sprintf(v1, "SubGame\\Appraise\\Exhibit\\Data\\%s.pol", (const char *)(v6 + 36));
    ((PalScript *)v3)->LoadModel(v1, 0);
    v7 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*p_shikuaisucc);
    sprintf(v1, "SubGame\\Appraise\\Exhibit\\Data\\%s.pol", (const char *)(v7 + 36));
    result = ((PalScript *)(v3 + 77))->LoadModel(v1, 0);
    p_shikuaisucc += 402;
    v3 += 8;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x00528650
int PAL_GDB::InitSkillDisplay(int nVal)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  float Escape; // edx
  int v8; // edx
  char *v9; // ebp
  int SkillNum; // eax
  bool v11; // zf
  int v12; // edx
  unsigned int NormalAtkID; // eax
  char *v14; // ebx
  int *v15; // ebp
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // ecx
  float v22; // ecx
  int v23; // edx
  int result; // eax
  float v25; // [esp+0x54] [ebp-0x88]
  int *v26; // [esp+0x64] [ebp-0x78]
  int v27; // [esp+0x68] [ebp-0x74]
  int v28; // [esp+0x68] [ebp-0x74]
  int v29; // [esp+0x6C] [ebp-0x70] BYREF
  int v30; // [esp+0x70] [ebp-0x6C]
  int v31; // [esp+0x74] [ebp-0x68]
  int v32; // [esp+0x78] [ebp-0x64]
  int v33; // [esp+0x7C] [ebp-0x60] BYREF
  int v34; // [esp+0x80] [ebp-0x5C]
  int v35; // [esp+0x84] [ebp-0x58]
  int v36; // [esp+0x88] [ebp-0x54]
  int v37; // [esp+0x8C] [ebp-0x50] BYREF
  int v38; // [esp+0x90] [ebp-0x4C]
  int v39; // [esp+0x94] [ebp-0x48]
  int v40; // [esp+0x98] [ebp-0x44]
  _DWORD v41[2]; // [esp+0x9C] [ebp-0x40] BYREF
  int v42; // [esp+A4h] [ebp-0x38]
  int v43; // [esp+A8h] [ebp-0x34]
  _DWORD v44[4]; // [esp+ACh] [ebp-0x30] BYREF
  _DWORD v45[4]; // [esp+BCh] [ebp-0x20] BYREF
  int v46[4]; // [esp+CCh] [ebp-0x10] BYREF

  this->m_RoleData[14].rolevalue[5] = nVal;
  ((PalScript *)this)->LoadResource("SubGame\\Appraise\\Exhibit\\Appraise.dft");

  *(_DWORD *)&this->m_head.str[76] = 0;
  *(_DWORD *)&this->m_head.str[72] = 0;
  *(_DWORD *)&this->m_head.str[80] = *(_DWORD *)&this->m_head.str[88];
  *(_DWORD *)&this->m_head.str[84] = *(_DWORD *)&this->m_head.str[76] + *(_DWORD *)&this->m_head.str[92];
  ((UIListBox *)this)->SetSelTexture(-1, *(_DWORD *)&this->m_head.str[72], *(_DWORD *)&this->m_head.str[76], *(_DWORD *)&this->m_head.str[80], *(_DWORD *)&this->m_head.str[84], 0);
  v3 = *(_DWORD *)&this->m_RoleData[1].Remark[286];
  v30 = 34;
  v29 = 165;
  v31 = 633;
  v32 = 138;
  (*(void ( **)(char *, ARC_PlayerAtt *, int *, PAL_GDB *))(v3 + 16))(
    &this->m_RoleData[1].Remark[286],
    &g_PlayerAttBuffer,
    &v29,
    this);
  ((UIStatic *)&this->m_RoleData[1].Remark[286])->CreateFromTemplate();
  v4 = *(_DWORD *)&this->m_RoleData[1].Remark[438];
  v30 += 6;
  v29 += 22;
  v32 = v30 + 158;
  v31 = v29 + 428;
  (*(void ( **)(char *, ARC_PlayerAtt *, int *, PAL_GDB *))(v4 + 16))(
    &this->m_RoleData[1].Remark[438],
    &g_PlayerAttBuffer,
    &v29,
    this);
  ((UIScene *)&this->m_RoleData[1].Remark[438])->SetShow(0);
  sub_446010(&this->m_RoleData[1].Remark[438]);
  v5 = *(_DWORD *)&this->m_RoleData[1].Remark[134];
  v44[1] = 10;
  v44[0] = 32;
  v44[2] = 160;
  v44[3] = 138;
  (*(void ( **)(char *, ARC_PlayerAtt *, _DWORD *, PAL_GDB *))(v5 + 16))(
    &this->m_RoleData[1].Remark[134],
    &g_PlayerAttBuffer,
    v44,
    this);
  ((UIStatic *)&this->m_RoleData[1].Remark[134])->CreateFromTemplate();
  v6 = *(_DWORD *)&this->m_RoleData[0].ModelID[18];
  v45[1] = 138;
  v45[0] = 86;
  v45[2] = 712;
  v45[3] = 606;
  (*(void ( **)(char *, ARC_PlayerAtt *, _DWORD *, PAL_GDB *))(v6 + 16))(
    &this->m_RoleData[0].ModelID[18],
    &g_PlayerAttBuffer,
    v45,
    this);
  ((UIStatic *)&this->m_RoleData[0].ModelID[18])->CreateFromTemplate();
  Escape = this->m_RoleData[2].Escape;
  v41[1] = 0;
  v41[0] = 0;
  v42 = 14;
  v43 = 600;
  (*(void ( **)(float *, ARC_PlayerAtt *, _DWORD *, PAL_GDB *))(LODWORD(Escape) + 16))(
    &this->m_RoleData[2].Escape,
    &g_PlayerAttBuffer,
    v41,
    this);
  ((UIStatic *)&this->m_RoleData[2].Escape)->CreateFromTemplate();
  v8 = *(_DWORD *)&this->m_RoleData[3].Remark[18];
  v41[0] = 786;
  v42 = 800;
  (*(void ( **)(char *, ARC_PlayerAtt *, _DWORD *, PAL_GDB *))(v8 + 16))(
    &this->m_RoleData[3].Remark[18],
    &g_PlayerAttBuffer,
    v41,
    this);
  ((UIStatic *)&this->m_RoleData[3].Remark[18])->CreateFromTemplate();
  ((CCBFiveNimbusWindow *)&this->m_RoleData[2].Remark[42])->CreateScriptAndCamera((int)&g_PlayerAttBuffer.Remark[2], (int)this);
  ((CCBFiveNimbusWindow *)&this->m_RoleData[2].Remark[42])->SetFloatParam(1180.0);
  ((Camera *)&this->m_RoleData[2].Remark[42])->UpdateCameraLookAt(400, 300);
  v9 = &this->m_RoleData[2].Remark[118];
  v26 = (int *)&this->m_RoleData[5].Remark[278];
  v27 = 5;
  do
  {
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*v26);
    sprintf(&this->m_head.str[96], "%s%s.pol", "SubGame\\Appraise\\Exhibit\\Data\\", (const char *)(SkillNum + 36));
    ((PalScript *)(v9 - 4))->LoadModel(&this->m_head.str[96], 0);
    *(_DWORD *)v9 = 1;
    ((UIPushButton *)&this->m_RoleData[2].Remark[42])->SetAnimOffset(1, 1127481344, v25);
    *(_DWORD *)&this->m_RoleData[2].Remark[286] = 58;
    v9 += 32;
    ++*(_DWORD *)&this->m_RoleData[2].Remark[110];
    v11 = v27 == 1;
    v26 += 402;
    --v27;
  }
  while ( !v11 );
  v12 = this->m_RoleData[1].att[4];
  *(_DWORD *)&this->m_RoleData[2].Remark[354] = 1124597760;
  *(_DWORD *)&this->m_RoleData[2].Remark[366] = 1124597760;
  *(_DWORD *)&this->m_RoleData[2].Remark[378] = -1006501888;
  *(_DWORD *)&this->m_RoleData[2].Remark[390] = -1006501888;
  *(_DWORD *)&this->m_RoleData[2].Remark[402] = -1006501888;
  *(_DWORD *)&this->m_RoleData[2].Remark[350] = -1010958336;
  *(_DWORD *)&this->m_RoleData[2].Remark[358] = 0;
  *(_DWORD *)&this->m_RoleData[2].Remark[362] = 1136525312;
  *(_DWORD *)&this->m_RoleData[2].Remark[370] = 0;
  *(_DWORD *)&this->m_RoleData[2].Remark[374] = -1004863488;
  *(_DWORD *)&this->m_RoleData[2].Remark[382] = 0;
  *(_DWORD *)&this->m_RoleData[2].Remark[386] = 0;
  *(_DWORD *)&this->m_RoleData[2].Remark[394] = 0;
  *(_DWORD *)&this->m_RoleData[2].Remark[398] = 1142620160;
  *(_DWORD *)&this->m_RoleData[2].Remark[406] = 0;
  v34 = 136;
  v33 = 86;
  v35 = 714;
  v36 = 605;
  (*(void ( **)(int *, ARC_PlayerAtt *, int *, PAL_GDB *))(v12 + 16))(
    &this->m_RoleData[1].att[4],
    &g_PlayerAttBuffer,
    &v33,
    this);
  ((UIStatic *)&this->m_RoleData[1].att[4])->CreateFromTemplate();
  (*(void ( **)(int *, _DWORD))this->m_RoleData[1].att[4])(&this->m_RoleData[1].att[4], 0);
  NormalAtkID = this->m_RoleData[1].NormalAtkID;
  v34 = 164;
  v33 = 325;
  v35 = 481;
  v36 = 196;
  (*(void ( **)(unsigned int *, ARC_PlayerAtt *, int *, PAL_GDB *))(NormalAtkID + 16))(
    &this->m_RoleData[1].NormalAtkID,
    &g_PlayerAttBuffer,
    &v33,
    this);
  ((UIScene *)&this->m_RoleData[1].NormalAtkID)->SetShow(0);
  sub_446010(&this->m_RoleData[1].NormalAtkID);
  (*(void ( **)(unsigned int *, _DWORD))this->m_RoleData[1].NormalAtkID)(
    &this->m_RoleData[1].NormalAtkID,
    0);
  ((CCBFiveNimbusWindow *)&this->m_RoleData[2].Remark[410])->CreateScriptAndCamera((int)&g_PlayerAttBuffer.Remark[3], (int)this);
  ((CCBFiveNimbusWindow *)&this->m_RoleData[2].Remark[410])->SetFloatParam(560.0);
  ((Camera *)&this->m_RoleData[2].Remark[410])->UpdateCameraLookAt(400, 360);
  v14 = &this->m_RoleData[2].Remark[486];
  v15 = (int *)&this->m_RoleData[5].Remark[278];
  v28 = 5;
  do
  {
    v16 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*v15);
    sprintf(&this->m_head.str[96], "%s%s.pol", "SubGame\\Appraise\\Exhibit\\Data\\", (const char *)(v16 + 36));
    ((PalScript *)(v14 - 4))->LoadModel(&this->m_head.str[96], 0);
    *(_DWORD *)v14 = 0;
    v15 += 402;
    ++*(_DWORD *)&this->m_RoleData[2].Remark[478];
    v14 += 32;
    --v28;
  }
  while ( v28 );
  v46[1] = 200;
  v46[0] = 250;
  v46[2] = 550;
  v46[3] = 328;
  ((ARC_PlayerAtt *)&this->m_RoleData[14].rolevalue[7])->Create(180146190, (int)v46);
  ((UIItem *)&this->m_RoleData[14].rolevalue[7])->SetData(31);
  v17 = *(_DWORD *)&this->m_RoleData[14].gold;
  v18 = *(_DWORD *)&this->m_RoleData[14].height;
  this->m_RoleData[14].skill[1] = this->m_RoleData[14].NormalAtkID + 26;
  this->m_RoleData[14].skill[0] = v17 + 6;
  this->m_RoleData[14].skill[3] = *(_DWORD *)&this->m_RoleData[14].speed2 - 38;
  *(_DWORD *)&this->m_RoleData[16].Remark[298] = 0;
  *(_DWORD *)&this->m_RoleData[16].Remark[302] = 20;
  this->m_RoleData[14].skill[2] = v18 - 6;
  sub_445FA0(&this->m_RoleData[15].Remark[262]);
  v19 = this->m_RoleData[14].rolevalue[5];
  v20 = *(_DWORD *)&this->m_RoleData[0].Remark[186];
  v38 = 556;
  v37 = 338;
  v39 = 454;
  v40 = 582;
  LOBYTE(v21) = *(_BYTE *)(v19 + 1756);
  (*(void ( **)(char *, char *, int *, PAL_GDB *, char *, _DWORD, int))(v20 + 28))(
    &this->m_RoleData[0].Remark[186],
    (char *)&g_PlayerAttBuffer.id + 1,
    &v37,
    this,
    "SubGame\\Appraise\\Exhibit\\Do",
    0,
    v21);
  (**(void ( ***)(char *, _DWORD))&this->m_RoleData[0].Remark[186])(&this->m_RoleData[0].Remark[186], 0);
  v22 = *(float *)&v37;
  v23 = v39;
  this->m_RoleData[65].rolevalue[0] = v38;
  result = v40;
  this->m_RoleData[65].lv = v22;
  this->m_RoleData[65].rolevalue[1] = v23;
  this->m_RoleData[65].rolevalue[2] = result;
  this->m_RoleData[3].Remark[170] = 0;
  return result;
}

// 0x005294C0
char * PAL_GDB::SetDefaultEquipment()
{
  char *v1; // ebx
  int v2; // ebp
  char *result; // eax
  char *v4; // edi

  *(_DWORD *)&this->m_RoleData[5].Remark[278] = 6025;
  *(_DWORD *)&this->m_RoleData[7].Remark[182] = 6021;
  *(_DWORD *)&this->m_RoleData[9].Remark[86] = 6023;
  *(_DWORD *)&this->m_RoleData[10].stealnum = 6010;
  *(_DWORD *)&this->m_RoleData[12].height = 6001;
  *(_DWORD *)&this->m_RoleData[5].Remark[282] = 6301;
  *(_DWORD *)&this->m_RoleData[7].Remark[186] = 6302;
  *(_DWORD *)&this->m_RoleData[9].Remark[90] = 6303;
  this->m_RoleData[11].id = 6304;
  *(_DWORD *)&this->m_RoleData[12].speed2 = 6305;
  v1 = &this->m_RoleData[5].Remark[286];
  v2 = 5;
  do
  {
    qmemcpy(v1, (const void *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*((_DWORD *)v1 - 2)), 0x320u);
    result = (char *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*((_DWORD *)v1 - 1));
    v4 = v1 + 800;
    v1 += 1608;
    --v2;
    qmemcpy(v4, result, 0x320u);
  }
  while ( v2 );
  return result;
}

// 0x0052ECE0
BOOL PAL_GDB::SetupSkillData(int nVal)
{
  int p_DWORD[3]; // [esp+0x0] [ebp-0xC] BYREF

  p_DWORD[0] = nVal;
  p_DWORD[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(nVal);
  p_DWORD[1] = 1;
  return ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(p_DWORD) != 0;
}
