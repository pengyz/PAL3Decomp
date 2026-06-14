#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CJ_FindFile.h"

// Forward declarations for unnamed functions
void sub_43FDB0(float *_this, int a2); // from annotations
int sub_43FEC0(void *a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations

// 0x00450F90
int CJ_FindFile::Create(int id, void *pRect, int parent, char *tex)
{
  int v6; // eax
  int v7; // ebx
  int v8; // edx
  int v9; // eax
  int v10; // ebx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  char pData[4]; // [esp+0x3C] [ebp-0x10] BYREF
  int v16; // [esp+0x40] [ebp-0xC]
  int v17; // [esp+0x44] [ebp-0x8]
  int v18; // [esp+0x48] [ebp-0x4]

  *(_DWORD *)pRect = 0;
  *(_DWORD *)&this->m_strRoot[20] = 458;
  *((_DWORD *)pRect + 2) = 800;
  *((_DWORD *)pRect + 3) = 594;
  ((PalScript *)this)->Create(id, (tagRECT *)pRect, parent);
  ((UINote *)&this->m_strRoot[80])->Create(0, (int)pRect, 0, "ui\\flex\\dlg");
  *(_DWORD *)&this->m_strRoot[148] = 1048576000;
  v18 = g_DrvInfo.height - 8;
  v16 = g_DrvInfo.height - 520;
  v6 = *(_DWORD *)&this->m_fileName[100];
  *(_DWORD *)pData = 8;
  v17 = 264;
  (*(void ( **)(char *, int, char *, CJ_FindFile *))(v6 + 16))(&this->m_fileName[100], 2, pData, this);
  v7 = *(_DWORD *)&this->m_strRoot[24];
  v8 = *(_DWORD *)&this->m_strRoot[16];
  v9 = *(_DWORD *)&this->m_fileName[256];
  v16 = 8;
  v10 = v7 - v8;
  *(_DWORD *)pData = 256;
  v17 = 600;
  v18 = 144;
  (*(void ( **)(char *, int, char *, CJ_FindFile *))(v9 + 16))(&this->m_fileName[256], 1, pData, this);
  sub_446010(&this->m_fileName[256]);
  (*(void ( **)(char *, int, char *, CJ_FindFile *))(*(_DWORD *)&this->m_strRoot[272] + 16))(
    &this->m_strRoot[272],
    2,
    pData,
    this);
  ((UIScene *)&this->m_strRoot[272])->LoadResource("ui\\scene\\page");
  ((UIScene *)&this->m_strRoot[272])->SetController(0x40000000);
  ((BINK *)this)->SetVideoRect((char)pData);
  sub_445FA0(&this->m_strRoot[272]);
  v11 = (v10 - 134) / 2;
  *(_DWORD *)pData = v11;
  v17 = v11 + 134;
  v12 = *(_DWORD *)&this->m_strbuf[36];
  v18 = 600;
  v16 = 580;
  (*(void ( **)(char *, _DWORD, char *, CJ_FindFile *))(v12 + 16))(&this->m_strbuf[36], 0, pData, this);
  sub_445FA0(&this->m_strbuf[36]);
  ((UIStatic *)&this->m_strbuf[36])->CreateFromTemplate();
  v13 = *(_DWORD *)&this->m_strbuf[188];
  *(_DWORD *)pData = v11;
  v17 = v11 + 134;
  v18 = 600;
  v16 = 568;
  (*(void ( **)(char *, _DWORD, char *, CJ_FindFile *))(v13 + 16))(&this->m_strbuf[188], 0, pData, this);
  sub_43FEC0(pData);
  ((UIScene *)&this->m_strbuf[188])->GetChildCount();
  ((UIScene *)&this->m_strbuf[188])->GetChildAt();
  ((UIScrollBar *)&this->m_strbuf[188])->SetRange(4.0);
  ((UIProgressBar *)&this->m_strbuf[188])->FindChildByName(0.0);
  *(_DWORD *)&this->m_strbuf[300] = 1120403456;
  sub_43FDB0((float *)&this->m_strbuf[188], 4);
  ((UIWnd *)&this->m_strbuf[188])->GetHeight(9);
  ((UIWnd *)&this->m_strbuf[188])->GetWidth(4);
  ((UIWnd *)&this->m_strbuf[188])->GetPosition(9);
  return (**(int ( ***)(char *, _DWORD))&this->m_strbuf[188])(&this->m_strbuf[188], 0);
}
