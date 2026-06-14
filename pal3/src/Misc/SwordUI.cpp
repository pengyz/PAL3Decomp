#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SwordUI.h"

// Forward declarations for unnamed functions
void * sub_446010(void *a2); // from annotations
unsigned int sub_4A8230(unsigned int a2, int a3); // from annotations

// Unnamed globals (extern)
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DCF43C[256];
extern int dword_C10CC4;

// 0x004AAD90
gbTexture * SwordUI::RenderSword()
{
  gbTexture *result; // eax
  int v3; // ecx
  int v4; // edi
  _BYTE *p_type; // eax
  float v6; // edx
  const CHAR *v7; // edi
  int m_purgeEquipNum; // eax
  int v9; // ebx
  int v10; // edi
  int v11; // ecx
  int m_purgeWeaponNum; // eax
  int m_avgAdornFANG; // ecx
  int m_avgAdornWU; // eax
  int m_avgWeaponWU; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  CHAR v19[125]; // [esp+0xC] [ebp-D4h] BYREF
  __int16 v20; // [esp+0x89] [ebp-0x57]
  char v21; // [esp+0x8B] [ebp-0x55]
  CHAR String1[64]; // [esp+0x8C] [ebp-0x54] BYREF
  char v23; // [esp+CCh] [ebp-0x14]
  char v24; // [esp+CDh] [ebp-0x13]
  char v25; // [esp+CEh] [ebp-0x12]
  char v26; // [esp+CFh] [ebp-0x11]
  char v27; // [esp+D0h] [ebp-0x10]
  char v28; // [esp+D1h] [ebp-0xF]
  char v29; // [esp+D2h] [ebp-0xE]
  char v30; // [esp+D3h] [ebp-0xD]
  unsigned int a2; // [esp+D4h] [ebp-0xC]
  int m_avgDefFANG; // [esp+D8h] [ebp-0x8]
  float v33; // [esp+DCh] [ebp-0x4]

  result = (gbTexture *)this->m_Distribute[98].m_Index;
  if ( (int)result > 0 )
  {
    switch ( g_nFiveNimbusCount )
    {
      case 0:
        ((UIStatic *)&this->m_parSword[16].m_viewRect.bottom)->CreateFromTemplate();
        lstrcpyA(String1, (LPCSTR)g_bSlotFlag);
        if ( gbColorQuad::ColorQuadFmt )
        {
          v25 = -7;
          v24 = -34;
          v23 = -102;
        }
        else
        {
          v25 = -102;
          v24 = -34;
          v23 = -7;
        }
        v26 = -1;
        goto LABEL_23;
      case 1:
        ((UIStatic *)&this->m_parSword[16].m_viewRect.bottom)->CreateFromTemplate();
        lstrcpyA(String1, (LPCSTR)&g_bSlotFlag[256]);
        if ( gbColorQuad::ColorQuadFmt )
        {
          v29 = -72;
          v28 = -71;
          v27 = -1;
        }
        else
        {
          v29 = -1;
          v28 = -71;
          v27 = -72;
        }
        v30 = -1;
        goto LABEL_23;
      case 2:
        ((UIStatic *)&this->m_parSword[16].m_viewRect.bottom)->CreateFromTemplate();
        lstrcpyA(String1, byte_DC3F3C);
        if ( gbColorQuad::ColorQuadFmt )
        {
          *(_WORD *)((char *)&m_avgDefFANG + 1) = -73;
          LOBYTE(m_avgDefFANG) = -54;
        }
        else
        {
          *(_WORD *)((char *)&m_avgDefFANG + 1) = -13641;
          LOBYTE(m_avgDefFANG) = -1;
        }
        HIBYTE(m_avgDefFANG) = -1;
        goto LABEL_23;
      case 3:
        ((UIStatic *)&this->m_parSword[16].m_viewRect.bottom)->CreateFromTemplate();
        lstrcpyA(String1, (LPCSTR)&g_bSlotFlag[512]);
        if ( gbColorQuad::ColorQuadFmt )
        {
          *(_WORD *)((char *)&a2 + 1) = -12033;
          LOBYTE(a2) = -73;
        }
        else
        {
          *(_WORD *)((char *)&a2 + 1) = -18433;
          LOBYTE(a2) = -48;
        }
        HIBYTE(a2) = -1;
        goto LABEL_23;
      case 4:
        ((UIStatic *)&this->m_parSword[16].m_viewRect.bottom)->CreateFromTemplate();
        lstrcpyA(String1, byte_DC403C);
        if ( gbColorQuad::ColorQuadFmt )
        {
          *(_WORD *)((char *)&v33 + 1) = -18452;
          LOBYTE(v33) = -1;
        }
        else
        {
          *(_WORD *)((char *)&v33 + 1) = -20;
          LOBYTE(v33) = -73;
        }
        HIBYTE(v33) = -1;
LABEL_23:
        sub_446010(&this->m_parSword[15]._element.m_rect.right);
        break;
      default:
        break;
    }
    memset(v19, 0, sizeof(v19));
    v20 = 0;
    this->buf[0] = 0;
    v21 = 0;
    *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 3) = 2224;
    ((UICaption *)&this->m_parSword[15]._element.m_rect.right)->SetEnable((int)byte_DCF43C, 0);
    lstrcpyA(v19, byte_DCF43C);
    v3 = *(_DWORD *)&this->m_WSkill[27].helvself[1];
    v4 = 0;
    if ( v3 > 0 )
    {
      p_type = &this->m_WSkill[0].type;
      LODWORD(v6) = (unsigned __int8)g_nActorState;
      LODWORD(v33) = (unsigned __int8)g_nActorState;
      while ( *(_QWORD *)(p_type - 4) != __PAIR64__(BYTE1(g_nActorState), LODWORD(v6))
           || *(_QWORD *)(p_type + 4) != __PAIR64__(BYTE2(g_nActorState), HIBYTE(g_nActorState))
           || *((_DWORD *)p_type + 3) != (unsigned __int8)g_nActor_DE5F9C )
      {
        ++v4;
        p_type += 760;
        if ( v4 >= v3 )
          goto LABEL_33;
        v6 = v33;
      }
      *((_DWORD *)&Buffer.m_partyActor.m_fSpeed + 3) = *(&this->m_adornNum + 190 * v4);
      v7 = (const CHAR *)&this->m_WSkill[v4].att[3];
      lstrcpyA(v19, v7);
      ((UICaption *)&this->m_parSword[15]._element.m_rect.right)->SetEnable((int)v7, 0);
    }
LABEL_33:
    m_purgeEquipNum = this->m_purgeEquipNum;
    v9 = 0;
    v10 = 0;
    a2 = 0;
    v33 = 0.0;
    if ( m_purgeEquipNum > 0 )
    {
      v11 = *((_DWORD *)&this->m_ljsNumber + 39);
      if ( v11 > 0 )
        a2 = m_purgeEquipNum / v11;
    }
    m_purgeWeaponNum = this->m_purgeWeaponNum;
    if ( m_purgeWeaponNum > 0 )
    {
      m_avgAdornFANG = this->m_avgAdornFANG;
      if ( m_avgAdornFANG > 0 )
        v9 = m_purgeWeaponNum / m_avgAdornFANG;
    }
    m_avgAdornWU = this->m_avgAdornWU;
    if ( m_avgAdornWU > 0 )
    {
      m_avgDefFANG = this->m_avgDefFANG;
      if ( m_avgDefFANG > 0 )
        v33 = ((double)m_avgDefFANG * 0.0099999998 + 0.89999998) * (double)(m_avgAdornWU / m_avgDefFANG) * 0.2;
    }
    m_avgWeaponWU = this->m_avgWeaponWU;
    if ( m_avgWeaponWU > 0 )
    {
      v16 = this->m_avgAdornFANG;
      if ( v16 > 0 )
        v10 = m_avgWeaponWU / v16;
    }
    v17 = *((_DWORD *)&this->m_ljsNumber + 38);
    m_avgDefFANG = *((_DWORD *)&this->m_ljsNumber + 39) / 2;
    v18 = LODWORD(Buffer.m_partyActor.m_fAngleDeg) + v17 / 5 - m_avgDefFANG;
    if ( v18 > 0 )
    {
      if ( v18 > 20 )
        v18 = 20;
    }
    else
    {
      v18 = 1;
    }
    LODWORD(Buffer.m_partyActor.m_fAngleDeg) = v18;
    m_avgDefFANG = (int)v33;
    v33 = ((double)dword_C10CC4 * 0.02 + 1.0) * (double)(int)(a2 + v9 + v10 + m_avgDefFANG);
    a2 = (int)v33;
    g_nUpdateInterval = a2;
    g_nUpdateInterval = sub_4A8230(a2, dword_C10CC4);
    ((RoleSystem *)&Buffer)->RecalcAggregatedStats(0);
    return ((TextureLib *)&this->m_StuffList.m_column[3].head[48])->CreateFromFile();
  }
  return result;
}
