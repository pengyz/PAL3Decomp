#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/DealData.h"

int * ctor_0x431870(int *_this); // from annotations

// Unnamed globals (extern)
extern CHAR asc_5B1E74[2];
extern const char * off_58B448;
extern const char * off_592DA4;

// 0x00457260
DealData::DealData()
{
  ctor_0x431870((int *)this->m_LoadTxt.m_token);
  ((PAL_GDB *)&this->m_LoadGDB)->ResetAllData();
  ctor_0x431870((int *)&this->m_LoadGDB.m_ItemData[507].fightstate[14]);
  this->m_LoadGDB.m_ItemData[508].fightstate[5] = 0;
  *((_DWORD *)&this->m_ManagerData + 1064) = 0;
  *((_DWORD *)&this->m_ManagerData + 1065) = 0;
  memset((char *)&this->m_ManagerData + 4264, 0, 0x640u);
  memset((char *)&this->m_ManagerData + 7464, 0, 0x190u);
  memset((char *)&this->m_ManagerData + 5864, 0, 0x640u);
  *(_DWORD *)&this->m_LoadGDB.m_ItemData[508].fightstate[4] = 0;
  *((_DWORD *)&this->m_ManagerData + 1064) = 0;
  *((_DWORD *)&this->m_ManagerData + 1065) = 0;
  memset((char *)&this->m_ManagerData + 4264, 0, 0x320u);
  this->m_isHarshRfus = 0;
  LOBYTE(this->m_LoadGDB.m_ItemData[507].fightstate[12]) = 0;
  memset(&this->m_LoadGDB.m_ItemData[508].desc[356], 0, 0x100u);
  g_bListNeedsRefresh = 0;
  (int *)this;
}

// 0x004573C0
int DealData::CompareString(LPCSTR lpString1, LPCSTR lpString2)
{
  int i; // ebx

  for ( i = 0; ; ++i )
  {
    if ( !lstrcmpA(lpString1, (LPCSTR)&off_592DA4) )
      return -1;
    if ( !lstrcmpA(lpString1, lpString2) )
      break;
    lpString1 += 30;
  }
  return i;
}

// 0x00457490
LPSTR DealData::LoadStoreConfig(CHAR *lpString2)
{
  LPSTR result; // eax
  unsigned __int8 v4; // al
  CHAR *v5; // edx
  CHAR *v6; // edx
  CHAR *v7; // edx
  CHAR *v8; // edx
  CHAR *v9; // edx
  TxtFile *p_m_LoadTxt; // [esp-0xC] [ebp-0x18]
  TxtFile *v11; // [esp-0xC] [ebp-0x18]
  TxtFile *v12; // [esp-0xC] [ebp-0x18]
  TxtFile *v13; // [esp-0xC] [ebp-0x18]
  TxtFile *v14; // [esp-0xC] [ebp-0x18]
  CHAR *lpString1; // [esp+0x8] [ebp-0x4]

  lpString1 = &this->m_LoadGDB.m_ItemData[508].desc[356];
  result = (LPSTR)lstrcmpA(&this->m_LoadGDB.m_ItemData[508].desc[356], lpString2);
  if ( result )
  {
    this->m_LoadGDB.m_ItemData[508].fightstate[5] = 0;
    *((_DWORD *)&this->m_ManagerData + 1064) = 0;
    *((_DWORD *)&this->m_ManagerData + 1065) = 0;
    memset((char *)&this->m_ManagerData + 4264, 0, 0x640u);
    memset((char *)&this->m_ManagerData + 7464, 0, 0x190u);
    memset((char *)&this->m_ManagerData + 5864, 0, 0x640u);
    *(_DWORD *)&this->m_LoadGDB.m_ItemData[508].fightstate[4] = 0;
    g_bListNeedsRefresh = 0;
    ((PalScript *)&this->m_LoadTxt)->LoadFromFile(lpString2);
    ((PalScript *)&this->m_LoadTxt)->SetDirectory("sec1");
    while ( ((PalScript *)&this->m_LoadTxt)->HasNext() )
    {
      if ( !_strcmpi((const char *)&off_58B448, this->m_LoadTxt.m_token) )
        break;
      switch ( this->CompareString("ST", this->m_LoadTxt.m_token) )
      {
        case 0:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          LOBYTE(this->m_LoadGDB.m_ItemData[508].fightstate[4]) = atoi(this->m_LoadTxt.m_token);
          break;
        case 1:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          v4 = atoi(this->m_LoadTxt.m_token);
          HIBYTE(this->m_LoadGDB.m_ItemData[508].fightstate[4]) = v4;
          if ( v4 > 1u )
            HIBYTE(this->m_LoadGDB.m_ItemData[508].fightstate[4]) = 1;
          break;
        case 2:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          this->m_LoadGDB.m_ItemData[508].fightstate[5] = atoi(this->m_LoadTxt.m_token);
          break;
        case 3:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA((LPSTR)&this->m_LoadGDB.m_ItemData[508].fightstate[6], this->m_LoadTxt.m_token);
          break;
        case 4:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          this->m_LoadGDB.m_ItemData[509].desc[72] = atoi(this->m_LoadTxt.m_token);
          break;
        case 5:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          *(_DWORD *)&this->m_LoadGDB.m_ItemData[509].desc[76] = atoi(this->m_LoadTxt.m_token);
          break;
        case 6:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA(&this->m_LoadGDB.m_ItemData[509].desc[80], this->m_LoadTxt.m_token);
          break;
        case 7:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA(&this->m_LoadGDB.m_ItemData[509].desc[336], this->m_LoadTxt.m_token);
          break;
        case 8:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA(&this->m_LoadGDB.m_ItemData[509].fstype[20], this->m_LoadTxt.m_token);
          break;
        case 9:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA(&this->m_LoadGDB.m_ItemData[510].desc[48], this->m_LoadTxt.m_token);
          break;
        case 10:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA(&this->m_LoadGDB.m_ItemData[510].desc[304], this->m_LoadTxt.m_token);
          break;
        case 11:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA((LPSTR)&this->m_LoadGDB.m_ItemData[510].rolevalue[6], this->m_LoadTxt.m_token);
          break;
        case 12:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA(&this->m_LoadGDB.m_ItemData[511].desc[16], this->m_LoadTxt.m_token);
          break;
        case 13:
          ((PalScript *)&this->m_LoadTxt)->LoadNext();
          lstrcpyA(&this->m_LoadGDB.m_ItemData[511].desc[272], this->m_LoadTxt.m_token);
          break;
        case 14:
          while ( lstrcmpA(this->m_LoadTxt.m_token, asc_5B1E74) )
          {
            ((PalScript *)&this->m_LoadTxt)->HasNext();
            switch ( this->CompareString("AcptQuantum", this->m_LoadTxt.m_token) )
            {
              case 0:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ItemData[511].gu = atof(this->m_LoadTxt.m_token);
                break;
              case 1:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)this->m_LoadGDB.m_ItemData[511].rolevalue, this->m_LoadTxt.m_token);
                break;
              case 2:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[0].Remark[20], this->m_LoadTxt.m_token);
                break;
              case 3:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[3].Remark[416] = atof(this->m_LoadTxt.m_token);
                break;
              case 4:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                p_m_LoadTxt = &this->m_LoadTxt;
                v5 = &this->m_LoadGDB.m_ComboData[3].Remark[436];
                goto LABEL_34;
              case 5:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[4].Remark[56], this->m_LoadTxt.m_token);
                break;
              case 6:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[7].Remark[452] = atof(this->m_LoadTxt.m_token);
                break;
              case 7:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[7].Remark[472], this->m_LoadTxt.m_token);
                break;
              case 8:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                p_m_LoadTxt = &this->m_LoadTxt;
                v5 = &this->m_LoadGDB.m_ComboData[8].Remark[92];
                goto LABEL_34;
              case 9:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 416, this->m_LoadTxt.m_token);
                break;
              case 10:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 672, this->m_LoadTxt.m_token);
                break;
              case 11:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                p_m_LoadTxt = &this->m_LoadTxt;
                v5 = (char *)&this->m_ManagerData + 2976;
LABEL_34:
                lstrcpyA(v5, p_m_LoadTxt->m_token);
                break;
              default:
                break;
            }
          }
          break;
        case 15:
          while ( lstrcmpA(this->m_LoadTxt.m_token, asc_5B1E74) )
          {
            ((PalScript *)&this->m_LoadTxt)->HasNext();
            switch ( this->CompareString("AcptQuantum", this->m_LoadTxt.m_token) )
            {
              case 0:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ItemData[511].special = atof(this->m_LoadTxt.m_token);
                break;
              case 1:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[0].Remark[276], this->m_LoadTxt.m_token);
                break;
              case 2:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_LoadGDB.m_ComboData[0].rolevalue[3], this->m_LoadTxt.m_token);
                break;
              case 3:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[3].Remark[420] = atof(this->m_LoadTxt.m_token);
                break;
              case 4:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v11 = &this->m_LoadTxt;
                v6 = &this->m_LoadGDB.m_ComboData[4].Remark[312];
                goto LABEL_51;
              case 5:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[5].name[12], this->m_LoadTxt.m_token);
                break;
              case 6:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[7].Remark[456] = atof(this->m_LoadTxt.m_token);
                break;
              case 7:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[8].Remark[348], this->m_LoadTxt.m_token);
                break;
              case 8:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v11 = &this->m_LoadTxt;
                v6 = (CHAR *)&this->m_LoadGDB.m_ComboData[9].man[3];
                goto LABEL_51;
              case 9:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 928, this->m_LoadTxt.m_token);
                break;
              case 10:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 1184, this->m_LoadTxt.m_token);
                break;
              case 11:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v11 = &this->m_LoadTxt;
                v6 = (char *)&this->m_ManagerData + 3232;
LABEL_51:
                lstrcpyA(v6, v11->m_token);
                break;
              default:
                break;
            }
          }
          break;
        case 16:
          while ( lstrcmpA(this->m_LoadTxt.m_token, asc_5B1E74) )
          {
            ((PalScript *)&this->m_LoadTxt)->HasNext();
            switch ( this->CompareString("AcptQuantum", this->m_LoadTxt.m_token) )
            {
              case 0:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ItemData[511].rvtype[1] = atof(this->m_LoadTxt.m_token);
                break;
              case 1:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[1].Remark[152], this->m_LoadTxt.m_token);
                break;
              case 2:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[1].Remark[408], this->m_LoadTxt.m_token);
                break;
              case 3:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[3].Remark[424] = atof(this->m_LoadTxt.m_token);
                break;
              case 4:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v12 = &this->m_LoadTxt;
                v7 = &this->m_LoadGDB.m_ComboData[5].Remark[188];
                goto LABEL_68;
              case 5:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[5].Remark[444], this->m_LoadTxt.m_token);
                break;
              case 6:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[7].Remark[460] = atof(this->m_LoadTxt.m_token);
                break;
              case 7:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[9].Remark[224], this->m_LoadTxt.m_token);
                break;
              case 8:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v12 = &this->m_LoadTxt;
                v7 = &this->m_LoadGDB.m_ComboData[9].Remark[480];
                goto LABEL_68;
              case 9:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 1440, this->m_LoadTxt.m_token);
                break;
              case 10:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 1696, this->m_LoadTxt.m_token);
                break;
              case 11:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v12 = &this->m_LoadTxt;
                v7 = (char *)&this->m_ManagerData + 3488;
LABEL_68:
                lstrcpyA(v7, v12->m_token);
                break;
              default:
                break;
            }
          }
          break;
        case 17:
          while ( lstrcmpA(this->m_LoadTxt.m_token, asc_5B1E74) )
          {
            ((PalScript *)&this->m_LoadTxt)->HasNext();
            switch ( this->CompareString("AcptQuantum", this->m_LoadTxt.m_token) )
            {
              case 0:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ItemData[511].rvtype[5] = atof(this->m_LoadTxt.m_token);
                break;
              case 1:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[2].Remark[28], this->m_LoadTxt.m_token);
                break;
              case 2:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[2].Remark[284], this->m_LoadTxt.m_token);
                break;
              case 3:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[3].Remark[428] = atof(this->m_LoadTxt.m_token);
                break;
              case 4:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v13 = &this->m_LoadTxt;
                v8 = &this->m_LoadGDB.m_ComboData[6].Remark[64];
                goto LABEL_85;
              case 5:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[6].Remark[320], this->m_LoadTxt.m_token);
                break;
              case 6:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[7].Remark[464] = atof(this->m_LoadTxt.m_token);
                break;
              case 7:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadLang.m_token[172], this->m_LoadTxt.m_token);
                break;
              case 8:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v13 = &this->m_LoadTxt;
                v8 = &this->m_LoadLang.m_token[428];
                goto LABEL_85;
              case 9:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 1952, this->m_LoadTxt.m_token);
                break;
              case 10:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 2208, this->m_LoadTxt.m_token);
                break;
              case 11:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v13 = &this->m_LoadTxt;
                v8 = (char *)&this->m_ManagerData + 3744;
LABEL_85:
                lstrcpyA(v8, v13->m_token);
                break;
              default:
                break;
            }
          }
          break;
        case 18:
          while ( lstrcmpA(this->m_LoadTxt.m_token, asc_5B1E74) )
          {
            ((PalScript *)&this->m_LoadTxt)->HasNext();
            switch ( this->CompareString("AcptQuantum", this->m_LoadTxt.m_token) )
            {
              case 0:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ItemData[511].rvtype[9] = atof(this->m_LoadTxt.m_token);
                break;
              case 1:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_LoadGDB.m_ComboData[2].rolevalue[7], this->m_LoadTxt.m_token);
                break;
              case 2:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[3].Remark[160], this->m_LoadTxt.m_token);
                break;
              case 3:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[3].Remark[432] = atof(this->m_LoadTxt.m_token);
                break;
              case 4:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v14 = &this->m_LoadTxt;
                v9 = &this->m_LoadGDB.m_ComboData[7].name[20];
                goto LABEL_102;
              case 5:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_LoadGDB.m_ComboData[7].Remark[196], this->m_LoadTxt.m_token);
                break;
              case 6:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                *(float *)&this->m_LoadGDB.m_ComboData[7].Remark[468] = atof(this->m_LoadTxt.m_token);
                break;
              case 7:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA(&this->m_lastFile[160], this->m_LoadTxt.m_token);
                break;
              case 8:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v14 = &this->m_LoadTxt;
                v9 = &this->m_ManagerData.m_Dicker + 159;
                goto LABEL_102;
              case 9:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 2464, this->m_LoadTxt.m_token);
                break;
              case 10:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                lstrcpyA((LPSTR)&this->m_ManagerData + 2720, this->m_LoadTxt.m_token);
                break;
              case 11:
                ((PalScript *)&this->m_LoadTxt)->LoadNext();
                v14 = &this->m_LoadTxt;
                v9 = (char *)&this->m_ManagerData + 4000;
LABEL_102:
                lstrcpyA(v9, v14->m_token);
                break;
              default:
                break;
            }
          }
          break;
        case 19:
          while ( lstrcmpA(this->m_LoadTxt.m_token, asc_5B1E74) )
          {
            if ( *((int *)&this->m_ManagerData + 1064) > 200 )
              break;
            ((PalScript *)&this->m_LoadTxt)->HasNext();
            if ( !lstrcmpA(this->m_LoadTxt.m_token, "Item_ID") )
            {
              ((PalScript *)&this->m_LoadTxt)->LoadNext();
              *((_DWORD *)&this->m_ManagerData + (*((_DWORD *)&this->m_ManagerData + 1064))++ + 1066) = atoi(this->m_LoadTxt.m_token);
            }
          }
          break;
        case 20:
          while ( lstrcmpA(this->m_LoadTxt.m_token, asc_5B1E74) )
          {
            if ( *((int *)&this->m_ManagerData + 1065) > 200 )
              break;
            ((PalScript *)&this->m_LoadTxt)->HasNext();
            if ( !lstrcmpA(this->m_LoadTxt.m_token, "Item_ID") )
            {
              ((PalScript *)&this->m_LoadTxt)->LoadNext();
              *((_DWORD *)&this->m_ManagerData + (*((_DWORD *)&this->m_ManagerData + 1065))++ + 1266) = atoi(this->m_LoadTxt.m_token);
            }
          }
          break;
        default:
          break;
      }
    }
    this->m_isHarshRfus = 1;
    return lstrcpyA(lpString1, lpString2);
  }
  return result;
}
