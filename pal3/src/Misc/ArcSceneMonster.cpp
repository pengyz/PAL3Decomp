#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ArcSceneMonster.h"

// Forward declarations for unnamed functions
void * sub_446010(void *a2); // from annotations

// 0x00441E30
int ArcSceneMonster::HitTest(unsigned int *pPoint)
{
  LONG *v3; // ebx
  POINT v4; // rax
  int result; // eax
  POINT v6; // rax
  LONG m_nMonsterLevel; // ebp
  unsigned int v8; // ecx
  int m_nMonsterGold; // eax
  unsigned int v10; // edx
  POINT v11; // rax
  LONG m_nSkillCount; // ecx
  LONG v13; // eax
  LONG v14; // ecx
  LONG v15; // edx
  LONG m_nDropRate; // eax
  unsigned int v17; // ecx
  unsigned int v18; // edx
  bool v19; // zf
  POINT v20; // [esp-0x8] [ebp-0x28]
  RECT rc; // [esp+0x10] [ebp-0x10] BYREF

  v20.y = pPoint[1];
  v3 = (LONG *)(&this->m_pMonsterData + 3);
  v20.x = *pPoint;
  if ( !PtInRect((const RECT *)(&this->m_pMonsterData + 3), v20) )
    return 5;
  rc.left = (LONG)this->m_pSkillList;
  rc.top = *((_DWORD *)&this->m_pSkillList + 1);
  rc.right = *((_DWORD *)&this->m_pSkillList + 2);
  v4 = *(POINT *)pPoint;
  rc.bottom = this->m_nSkillCount;
  if ( PtInRect(&rc, v4) )
    return 0;
  rc.left = (LONG)this->m_pDropItems;
  rc.top = this->m_nDropRate;
  rc.right = *(&this->m_nDropRate + 1);
  v6 = *(POINT *)pPoint;
  rc.bottom = *(&this->m_nDropRate + 2);
  if ( PtInRect(&rc, v6) )
    return 1;
  if ( this->m_nMonsterMP - this->m_nMonsterHP <= 0 )
    return 5;
  m_nMonsterLevel = this->m_nMonsterLevel;
  rc.left = *v3;
  rc.top = m_nMonsterLevel;
  rc.right = *((_DWORD *)&this->m_pMonsterData + 5);
  v8 = pPoint[1];
  m_nMonsterGold = this->m_nMonsterGold;
  rc.bottom = *((_DWORD *)&this->m_pMonsterData + 6);
  v10 = *pPoint;
  rc.bottom = m_nMonsterLevel + m_nMonsterGold;
  if ( PtInRect(&rc, (POINT)__PAIR64__(v8, v10)) )
    return 2;
  rc.left = *v3;
  rc.top = *((_DWORD *)&this->m_pMonsterData + 4);
  rc.right = *((_DWORD *)&this->m_pMonsterData + 5);
  v11.y = pPoint[1];
  m_nSkillCount = this->m_nSkillCount;
  rc.bottom = *((_DWORD *)&this->m_pMonsterData + 6);
  v11.x = *pPoint;
  rc.top = m_nSkillCount;
  rc.bottom = m_nMonsterLevel;
  if ( PtInRect(&rc, v11) )
    return 3;
  v13 = *((_DWORD *)&this->m_pMonsterData + 4);
  v14 = *((_DWORD *)&this->m_pMonsterData + 5);
  rc.left = *v3;
  v15 = *((_DWORD *)&this->m_pMonsterData + 6);
  rc.top = v13;
  m_nDropRate = this->m_nDropRate;
  rc.right = v14;
  v17 = pPoint[1];
  rc.bottom = v15;
  v18 = *pPoint;
  rc.bottom = m_nDropRate;
  rc.top = m_nMonsterLevel;
  v19 = !PtInRect(&rc, (POINT)__PAIR64__(v17, v18));
  result = 4;
  if ( v19 )
    return 5;
  return result;
}

// 0x00487F80
int * ArcSceneMonster::CreateInfoPanel(
        
        int nVal,
        int nVal2,
        int id,
        int *pnVal,
        int nVal3)
{
  int v6; // ebp
  char *v8; // ebp
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  int v19; // edx
  int v20; // eax
  int v21; // edx
  int v22; // edx
  int v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // eax
  int *result; // eax
  int v28; // [esp+0x8C] [ebp-0x50]
  int v29; // [esp+0x9C] [ebp-0x40] BYREF
  int v30; // [esp+A0h] [ebp-0x3C]
  _DWORD v31[2]; // [esp+A4h] [ebp-0x38] BYREF
  int v32; // [esp+ACh] [ebp-0x30]
  int v33; // [esp+B4h] [ebp-0x28] BYREF
  int v34; // [esp+B8h] [ebp-0x24]
  int v35; // [esp+BCh] [ebp-0x20]
  int v36; // [esp+C0h] [ebp-0x1C]
  int v37; // [esp+C4h] [ebp-0x18] BYREF
  int v38; // [esp+C8h] [ebp-0x14]
  int v39; // [esp+CCh] [ebp-0x10]
  int v40; // [esp+D0h] [ebp-0xC]
  _DWORD v41[2]; // [esp+D4h] [ebp-0x8] BYREF
  _UNKNOWN *retaddr; // [esp+DCh] [ebp+0x0]

  if ( nVal <= 5 )
  {
    v28 = v6;
    v29 = *(_DWORD *)nVal2;
    v30 = *(_DWORD *)(nVal2 + 4);
    v31[0] = v29 + 29;
    v31[1] = v30 + 119;
    v8 = &this->id + 4892 * nVal;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *, int))(*((_DWORD *)v8 + 53723) + 16))(
      v8 + 214892,
      *(&g_ArcSceneMonsterTable + nVal),
      &v29,
      this,
      v28);
    ((UIStatic *)(v8 + 214892))->CreateFromTemplate();
    v31[0] = v32;
    v9 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v32 += 240;
    (*(void ( **)(char *, int, _DWORD *, ArcSceneMonster *))(*((_DWORD *)v8 + 53761) + 16))(
      v8 + 215044,
      v9,
      v31,
      this);
    ((UIStatic *)(v8 + 215044))->CreateFromTemplate();
    v10 = *((_DWORD *)v8 + 53799);
    v31[0] = v32;
    v32 += 14;
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(v10 + 16))(
      v8 + 215196,
      *(&g_ArcSceneMonsterTable + nVal),
      v31,
      this);
    ((UIStatic *)(v8 + 215196))->CreateFromTemplate();
    v31[0] = v32;
    v11 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v32 += 256;
    (*(void ( **)(char *, int, _DWORD *, ArcSceneMonster *))(*((_DWORD *)v8 + 53837) + 16))(
      v8 + 215348,
      v11,
      v31,
      this);
    ((UIStatic *)(v8 + 215348))->CreateFromTemplate();
    v12 = *((_DWORD *)v8 + 53875);
    v31[0] = v32;
    v32 += 32;
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(v12 + 16))(
      v8 + 215500,
      *(&g_ArcSceneMonsterTable + nVal),
      v31,
      this);
    ((UIStatic *)(v8 + 215500))->CreateFromTemplate();
    v13 = *(_DWORD *)(nVal2 + 4) + 16;
    v41[0] = *(_DWORD *)nVal2 + 44;
    v41[1] = v13;
    retaddr = (_UNKNOWN *)(v41[0] + 64);
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(*((_DWORD *)v8 + 53913) + 16))(
      v8 + 215652,
      *(&g_ArcSceneMonsterTable + nVal),
      v41,
      this);
    ((UIStatic *)(v8 + 215652))->CreateFromTemplate();
    (**((void ( ***)(int, _DWORD))v8 + 53913))((int)(v8 + 215652), 0);
    v14 = *(_DWORD *)nVal2;
    v34 = *(_DWORD *)(nVal2 + 4);
    v33 = v14 + 106;
    v36 = v34 + 32;
    v15 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v35 = v14 + 234;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 53989) + 16))(
      v8 + 215956,
      v15,
      &v33,
      this);
    ((UIScene *)(v8 + 215956))->SetShow(0);
    sub_446010(v8 + 215956);
    v16 = *((_DWORD *)v8 + 53951);
    v34 = *(_DWORD *)(nVal2 + 4) + 22;
    v36 = v34 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v16 + 16))(
      v8 + 215804,
      *(&g_ArcSceneMonsterTable + nVal),
      &v33,
      this);
    ((UIScene *)(v8 + 215804))->SetShow(0);
    sub_446010(v8 + 215804);
    v34 = *(_DWORD *)(nVal2 + 4) + 42;
    v17 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v36 = v34 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 54027) + 16))(
      v8 + 216108,
      v17,
      &v33,
      this);
    ((UIScene *)(v8 + 216108))->SetShow(0);
    sub_446010(v8 + 216108);
    v18 = *((_DWORD *)v8 + 54065);
    v34 = *(_DWORD *)(nVal2 + 4) + 66;
    v36 = v34 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v18 + 16))(
      v8 + 216260,
      *(&g_ArcSceneMonsterTable + nVal),
      &v33,
      this);
    ((UIScene *)(v8 + 216260))->SetShow(0);
    sub_446010(v8 + 216260);
    v34 = *(_DWORD *)(nVal2 + 4) + 88;
    v19 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v36 = v34 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 54103) + 16))(
      v8 + 216412,
      v19,
      &v33,
      this);
    (**((void ( ***)(int, _DWORD))v8 + 54103))((int)(v8 + 216412), 0);
    sub_446010(v8 + 216412);
    v20 = *(_DWORD *)nVal2;
    v38 = *(_DWORD *)(nVal2 + 4);
    v37 = v20 + 230;
    v40 = v38 + 32;
    v21 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v39 = v20 + 340;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 54141) + 16))(
      v8 + 216564,
      v21,
      &v37,
      this);
    ((UIScene *)(v8 + 216564))->SetShow(0);
    sub_446010(v8 + 216564);
    v22 = *((_DWORD *)v8 + 54179);
    v38 = *(_DWORD *)(nVal2 + 4) + 22;
    v40 = v38 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v22 + 16))(
      v8 + 216716,
      *(&g_ArcSceneMonsterTable + nVal),
      &v37,
      this);
    ((UIScene *)(v8 + 216716))->SetShow(0);
    sub_446010(v8 + 216716);
    v38 = *(_DWORD *)(nVal2 + 4) + 42;
    v23 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v40 = v38 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 54217) + 16))(
      v8 + 216868,
      v23,
      &v37,
      this);
    ((UIScene *)(v8 + 216868))->SetShow(0);
    sub_446010(v8 + 216868);
    v24 = *((_DWORD *)v8 + 54255);
    v38 = *(_DWORD *)(nVal2 + 4) + 66;
    v40 = v38 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v24 + 16))(
      v8 + 217020,
      *(&g_ArcSceneMonsterTable + nVal),
      &v37,
      this);
    ((UIScene *)(v8 + 217020))->SetShow(0);
    sub_446010(v8 + 217020);
    v25 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v26 = *((_DWORD *)v8 + 54293);
    v8 += 217172;
    v38 = *(_DWORD *)(nVal2 + 4) + 88;
    v40 = v38 + 32;
    (*(void ( **)(char *, int))(v26 + 16))(v8, v25);
    ((UIScene *)v8)->SetShow(0);
    return (int *)sub_446010(v8);
  }
  return result;
}

// 0x00491F20
int * ArcSceneMonster::CreateMonsterUI(
        
        int nVal,
        int nVal2,
        int id,
        int *pnVal,
        int nVal3)
{
  int v6; // ebp
  char *v8; // ebp
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  int v19; // edx
  int v20; // edx
  int v21; // eax
  int v22; // edx
  int v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // edx
  int v27; // eax
  int *result; // eax
  int v29; // [esp+0x198] [ebp-0x50]
  int v30; // [esp+0x1A8] [ebp-0x40] BYREF
  int v31; // [esp+0x1B0] [ebp-0x38] BYREF
  int v32; // [esp+0x1B4] [ebp-0x34]
  int v33; // [esp+0x1B8] [ebp-0x30] BYREF
  int v34; // [esp+0x1BC] [ebp-0x2C]
  _DWORD v35[2]; // [esp+0x1C0] [ebp-0x28] BYREF
  int v36; // [esp+0x1C8] [ebp-0x20] BYREF
  int v37; // [esp+0x1D0] [ebp-0x18] BYREF
  int v38; // [esp+0x1D4] [ebp-0x14]
  int v39; // [esp+0x1D8] [ebp-0x10]
  int v40; // [esp+0x1DC] [ebp-0xC]
  _DWORD v41[2]; // [esp+0x1E0] [ebp-0x8] BYREF
  _UNKNOWN *retaddr; // [esp+0x1E8] [ebp+0x0]

  if ( nVal <= 5 )
  {
    v29 = v6;
    v33 = *(_DWORD *)nVal2;
    v34 = *(_DWORD *)(nVal2 + 4);
    v35[0] = v33 + 29;
    v35[1] = v34 + 119;
    v8 = &this->id + 9980 * nVal;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *, int))(*((_DWORD *)v8 + 39200) + 16))(
      v8 + 156800,
      *(&g_pfnCallback + nVal),
      &v33,
      this,
      v29);
    ((UIStatic *)(v8 + 156800))->CreateFromTemplate();
    v9 = *((_DWORD *)v8 + 39238);
    v35[0] = v36;
    v36 += 240;
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(v9 + 16))(
      v8 + 156952,
      *(&g_pfnCallback + nVal),
      v35,
      this);
    ((UIStatic *)(v8 + 156952))->CreateFromTemplate();
    v35[0] = v36;
    v10 = (int)*(&g_pfnCallback + nVal);
    v36 += 14;
    (*(void ( **)(char *, int, _DWORD *, ArcSceneMonster *))(*((_DWORD *)v8 + 39276) + 16))(
      v8 + 157104,
      v10,
      v35,
      this);
    ((UIStatic *)(v8 + 157104))->CreateFromTemplate();
    v11 = *((_DWORD *)v8 + 39314);
    v35[0] = v36;
    v36 += 256;
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(v11 + 16))(
      v8 + 157256,
      *(&g_pfnCallback + nVal),
      v35,
      this);
    ((UIStatic *)(v8 + 157256))->CreateFromTemplate();
    v35[0] = v36;
    v12 = (int)*(&g_pfnCallback + nVal);
    v36 += 32;
    (*(void ( **)(char *, int, _DWORD *, ArcSceneMonster *))(*((_DWORD *)v8 + 39352) + 16))(
      v8 + 157408,
      v12,
      v35,
      this);
    ((UIStatic *)(v8 + 157408))->CreateFromTemplate();
    v13 = *(_DWORD *)nVal2 + 44;
    v41[1] = *(_DWORD *)(nVal2 + 4) + 16;
    v14 = *((_DWORD *)v8 + 39390);
    v41[0] = v13;
    retaddr = (_UNKNOWN *)(v13 + 64);
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(v14 + 16))(
      v8 + 157560,
      *(&g_pfnCallback + nVal),
      v41,
      this);
    ((UIStatic *)(v8 + 157560))->CreateFromTemplate();
    (**((void ( ***)(int, _DWORD))v8 + 39390))((int)(v8 + 157560), 0);
    v15 = *(_DWORD *)(nVal2 + 4);
    v16 = *((_DWORD *)v8 + 39466);
    v31 = *(_DWORD *)nVal2 + 106;
    v32 = v15;
    v33 = v31 + 138;
    v34 = v15 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v16 + 16))(
      v8 + 157864,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39846) + 16))(
      v8 + 159384,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40226) + 16))(
      v8 + 160904,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(v8 + 157864))->SetShow(0);
    sub_446010(v8 + 157864);
    v32 = *(_DWORD *)(nVal2 + 4) + 22;
    v17 = (int)*(&g_pfnCallback + nVal);
    v34 = v32 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39428) + 16))(
      v8 + 157712,
      v17,
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39808) + 16))(
      v8 + 159232,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40188) + 16))(
      v8 + 160752,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(v8 + 157712))->SetShow(0);
    sub_446010(v8 + 157712);
    v18 = *((_DWORD *)v8 + 39504);
    v32 = *(_DWORD *)(nVal2 + 4) + 42;
    v34 = v32 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v18 + 16))(
      v8 + 158016,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39884) + 16))(
      v8 + 159536,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40264) + 16))(
      v8 + 161056,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(v8 + 158016))->SetShow(0);
    sub_446010(v8 + 158016);
    v32 = *(_DWORD *)(nVal2 + 4) + 66;
    v19 = (int)*(&g_pfnCallback + nVal);
    v34 = v32 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39542) + 16))(
      v8 + 158168,
      v19,
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39922) + 16))(
      v8 + 159688,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40302) + 16))(
      v8 + 161208,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(v8 + 158168))->SetShow(0);
    sub_446010(v8 + 158168);
    v20 = *((_DWORD *)v8 + 39580);
    v32 = *(_DWORD *)(nVal2 + 4) + 88;
    v34 = v32 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v20 + 16))(
      v8 + 158320,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39960) + 16))(
      v8 + 159840,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40340) + 16))(
      v8 + 161360,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(v8 + 158320))->SetShow(0);
    sub_446010(v8 + 158320);
    v21 = *(_DWORD *)nVal2;
    v38 = *(_DWORD *)(nVal2 + 4);
    v37 = v21 + 230;
    v40 = v38 + 32;
    v22 = (int)*(&g_pfnCallback + nVal);
    v39 = v21 + 340;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39618) + 16))(
      v8 + 158472,
      v22,
      &v37,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39998) + 16))(
      v8 + 159992,
      *(&g_pfnCallback + nVal),
      &v37,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40378) + 16))(
      v8 + 161512,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(v8 + 158472))->SetShow(0);
    sub_446010(v8 + 158472);
    v23 = *((_DWORD *)v8 + 39656);
    v38 = *(_DWORD *)(nVal2 + 4) + 22;
    v40 = v38 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v23 + 16))(
      v8 + 158624,
      *(&g_pfnCallback + nVal),
      &v37,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40036) + 16))(
      v8 + 160144,
      *(&g_pfnCallback + nVal),
      &v37,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40416) + 16))(
      v8 + 161664,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(v8 + 158624))->SetShow(0);
    sub_446010(v8 + 158624);
    v38 = *(_DWORD *)(nVal2 + 4) + 42;
    v24 = (int)*(&g_pfnCallback + nVal);
    v40 = v38 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39694) + 16))(
      v8 + 158776,
      v24,
      &v37,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40074) + 16))(
      v8 + 160296,
      *(&g_pfnCallback + nVal),
      &v37,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40454) + 16))(
      v8 + 161816,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(v8 + 158776))->SetShow(0);
    sub_446010(v8 + 158776);
    v25 = *((_DWORD *)v8 + 39732);
    v38 = *(_DWORD *)(nVal2 + 4) + 66;
    v40 = v38 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v25 + 16))(
      v8 + 158928,
      *(&g_pfnCallback + nVal),
      &v37,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40112) + 16))(
      v8 + 160448,
      *(&g_pfnCallback + nVal),
      &v37,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40492) + 16))(
      v8 + 161968,
      *(&g_pfnCallback + nVal),
      &v31,
      this);
    ((UIScene *)(UIScene *)v8 + 462)->SetShow(0);
    sub_446010(v8 + 158928);
    v26 = (int)*(&g_pfnCallback + nVal);
    v27 = *((_DWORD *)v8 + 39770);
    v38 = *(_DWORD *)(nVal2 + 4) + 88;
    v40 = v38 + 32;
    (*(void ( **)(char *, int))(v27 + 16))(v8 + 159080, v26);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40150) + 16))(
      v8 + 160600,
      *(&g_pfnCallback + nVal),
      &v36,
      this);
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40530) + 16))(
      v8 + 162120,
      *(&g_pfnCallback + nVal),
      &v30,
      this);
    ((UIScene *)(v8 + 159080))->SetShow(0);
    return (int *)sub_446010(v8 + 159080);
  }
  return result;
}

// 0x00499CC0
int * ArcSceneMonster::CreateStatusPanel(
        
        int nVal,
        int nVal2,
        int id,
        int *pnVal,
        int nVal3)
{
  int v6; // ebp
  char *v8; // ebp
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // edx
  int v23; // edx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  int *result; // eax
  int v28; // [esp+0x8C] [ebp-0x50]
  int v29; // [esp+0x9C] [ebp-0x40] BYREF
  int v30; // [esp+A0h] [ebp-0x3C]
  _DWORD v31[2]; // [esp+A4h] [ebp-0x38] BYREF
  int v32; // [esp+ACh] [ebp-0x30]
  int v33; // [esp+B4h] [ebp-0x28] BYREF
  int v34; // [esp+B8h] [ebp-0x24]
  int v35; // [esp+BCh] [ebp-0x20]
  int v36; // [esp+C0h] [ebp-0x1C]
  int v37; // [esp+C4h] [ebp-0x18] BYREF
  int v38; // [esp+C8h] [ebp-0x14]
  int v39; // [esp+CCh] [ebp-0x10]
  int v40; // [esp+D0h] [ebp-0xC]
  _DWORD v41[2]; // [esp+D4h] [ebp-0x8] BYREF
  _UNKNOWN *retaddr; // [esp+DCh] [ebp+0x0]

  if ( nVal <= 5 )
  {
    v28 = v6;
    v29 = *(_DWORD *)nVal2;
    v30 = *(_DWORD *)(nVal2 + 4);
    v31[0] = v29 + 29;
    v31[1] = v30 + 119;
    v8 = &this->id + 4892 * nVal;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *, int))(*((_DWORD *)v8 + 39611) + 16))(
      v8 + 158444,
      *(&g_ArcSceneMonsterTable2 + nVal),
      &v29,
      this,
      v28);
    ((UIStatic *)(v8 + 158444))->CreateFromTemplate();
    v31[0] = v32;
    v9 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v32 += 240;
    (*(void ( **)(char *, int, _DWORD *, ArcSceneMonster *))(*((_DWORD *)v8 + 39649) + 16))(
      v8 + 158596,
      v9,
      v31,
      this);
    ((UIStatic *)(v8 + 158596))->CreateFromTemplate();
    v10 = *((_DWORD *)v8 + 39687);
    v31[0] = v32;
    v32 += 14;
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(v10 + 16))(
      v8 + 158748,
      *(&g_ArcSceneMonsterTable2 + nVal),
      v31,
      this);
    ((UIStatic *)(v8 + 158748))->CreateFromTemplate();
    v31[0] = v32;
    v11 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v32 += 256;
    (*(void ( **)(char *, int, _DWORD *, ArcSceneMonster *))(*((_DWORD *)v8 + 39725) + 16))(
      v8 + 158900,
      v11,
      v31,
      this);
    ((UIStatic *)(v8 + 158900))->CreateFromTemplate();
    v12 = *((_DWORD *)v8 + 39763);
    v31[0] = v32;
    v32 += 32;
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(v12 + 16))(
      v8 + 159052,
      *(&g_ArcSceneMonsterTable2 + nVal),
      v31,
      this);
    ((UIStatic *)(v8 + 159052))->CreateFromTemplate();
    v13 = *(_DWORD *)(nVal2 + 4) + 16;
    v41[0] = *(_DWORD *)nVal2 + 44;
    v41[1] = v13;
    retaddr = (_UNKNOWN *)(v41[0] + 64);
    (*(void ( **)(char *, _DWORD, _DWORD *, ArcSceneMonster *))(*((_DWORD *)v8 + 39801) + 16))(
      v8 + 159204,
      *(&g_ArcSceneMonsterTable2 + nVal),
      v41,
      this);
    ((UIStatic *)(v8 + 159204))->CreateFromTemplate();
    (**((void ( ***)(int, _DWORD))v8 + 39801))((int)(v8 + 159204), 0);
    v14 = *(_DWORD *)nVal2;
    v34 = *(_DWORD *)(nVal2 + 4);
    v33 = v14 + 106;
    v36 = v34 + 32;
    v15 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v35 = v14 + 234;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39877) + 16))(
      v8 + 159508,
      v15,
      &v33,
      this);
    ((UIScene *)(v8 + 159508))->SetShow(0);
    sub_446010(v8 + 159508);
    v16 = *((_DWORD *)v8 + 39839);
    v34 = *(_DWORD *)(nVal2 + 4) + 22;
    v36 = v34 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v16 + 16))(
      v8 + 159356,
      *(&g_ArcSceneMonsterTable2 + nVal),
      &v33,
      this);
    ((UIScene *)(v8 + 159356))->SetShow(0);
    sub_446010(v8 + 159356);
    v34 = *(_DWORD *)(nVal2 + 4) + 42;
    v17 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v36 = v34 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39915) + 16))(
      v8 + 159660,
      v17,
      &v33,
      this);
    ((UIScene *)(v8 + 159660))->SetShow(0);
    sub_446010(v8 + 159660);
    v18 = *((_DWORD *)v8 + 39953);
    v34 = *(_DWORD *)(nVal2 + 4) + 66;
    v36 = v34 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v18 + 16))(
      v8 + 159812,
      *(&g_ArcSceneMonsterTable2 + nVal),
      &v33,
      this);
    ((UIScene *)(v8 + 159812))->SetShow(0);
    sub_446010(v8 + 159812);
    v34 = *(_DWORD *)(nVal2 + 4) + 88;
    v19 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v36 = v34 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 39991) + 16))(
      v8 + 159964,
      v19,
      &v33,
      this);
    (**((void ( ***)(int, _DWORD))v8 + 39991))((int)(v8 + 159964), 0);
    v20 = *(_DWORD *)(nVal2 + 4);
    v21 = *((_DWORD *)v8 + 40029);
    v37 = *(_DWORD *)nVal2 + 230;
    v38 = v20;
    v39 = v37 + 110;
    v40 = v20 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v21 + 16))(
      v8 + 160116,
      *(&g_ArcSceneMonsterTable2 + nVal),
      &v37,
      this);
    ((UIScene *)(v8 + 160116))->SetShow(0);
    sub_446010(v8 + 160116);
    v38 = *(_DWORD *)(nVal2 + 4) + 22;
    v22 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v40 = v38 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40067) + 16))(
      v8 + 160268,
      v22,
      &v37,
      this);
    ((UIScene *)(v8 + 160268))->SetShow(0);
    sub_446010(v8 + 160268);
    v23 = *((_DWORD *)v8 + 40105);
    v38 = *(_DWORD *)(nVal2 + 4) + 42;
    v40 = v38 + 32;
    (*(void ( **)(char *, _DWORD, int *, ArcSceneMonster *))(v23 + 16))(
      v8 + 160420,
      *(&g_ArcSceneMonsterTable2 + nVal),
      &v37,
      this);
    ((UIScene *)(v8 + 160420))->SetShow(0);
    sub_446010(v8 + 160420);
    v38 = *(_DWORD *)(nVal2 + 4) + 66;
    v24 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v40 = v38 + 32;
    (*(void ( **)(char *, int, int *, ArcSceneMonster *))(*((_DWORD *)v8 + 40143) + 16))(
      v8 + 160572,
      v24,
      &v37,
      this);
    ((UIScene *)(v8 + 160572))->SetShow(0);
    sub_446010(v8 + 160572);
    v25 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v26 = *((_DWORD *)v8 + 40181);
    v8 += 160724;
    v38 = *(_DWORD *)(nVal2 + 4) + 88;
    v40 = v38 + 32;
    (*(void ( **)(char *, int))(v26 + 16))(v8, v25);
    ((UIScene *)v8)->SetShow(0);
    return (int *)sub_446010(v8);
  }
  return result;
}

// 0x0052DC40
int ArcSceneMonster::CheckDistance(float fVal)
{
  unsigned int v2; // esi
  int v3; // edx
  char *m_pMonsterData; // edi
  float *i; // ecx

  if ( fVal < 0.0 )
    return 0;
  if ( fVal > (double)*((float *)&this->m_pMonsterData + 1) )
    return 0;
  v2 = *(_DWORD *)&this->id;
  v3 = 0;
  if ( !*(_DWORD *)&this->id )
    return 0;
  m_pMonsterData = (char *)this->m_pMonsterData;
  for ( i = (float *)(m_pMonsterData + 12); fVal > (double)*i; i += 8 )
  {
    if ( ++v3 >= v2 )
      return 0;
  }
  return (int)&m_pMonsterData[32 * v3];
}

// 0x0052DCA0
int ArcSceneMonster::ValidateRange(float fVal)
{
  unsigned int v2; // esi
  int v3; // edx
  float *i; // ecx

  if ( fVal < 0.0 )
    return 0;
  if ( fVal > (double)*((float *)&this->m_pMonsterData + 1) )
    return 0;
  v2 = *(_DWORD *)&this->id;
  v3 = 0;
  if ( !*(_DWORD *)&this->id )
    return 0;
  for ( i = (float *)((char *)this->m_pMonsterData + 12); fVal > (double)*i; i += 8 )
  {
    if ( ++v3 >= v2 )
      return 0;
  }
  return v3;
}
