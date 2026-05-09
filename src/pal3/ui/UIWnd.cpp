#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIWnd.h"

// 0x0043F560
int sub_43F560(int *this)
{
  int v1; // edx

  if ( *(this + 108) <= 0 )
    return -1;
  v1 = *(this + 280);
  if ( v1 == -1 )
    return -1;
  else
    return v1 + *(this + 279);
}

// 0x0043FA00
void sub_43FA00(gbRefObject **this, LPCSTR lpString, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  bool v6; // zf
  int v7; // ebp
  int v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString;
  if ( lpString )
  {
    v5 = *(this + 43);
    if ( v5 )
      v5->Release();
    OpenBaseFile::OpenBaseFile(&lpString);
    v6 = a3 == 0;
    *(this + 44) = 0;
    if ( v6 )
    {
      *(this + 43) = (gbRefObject *)(*(int (__thiscall **)(int, const CHAR *))(*(_DWORD *)g_pGfxManager + 8))(
                                      g_pGfxManager,
                                      v3);
    }
    else
    {
      v7 = *(_DWORD *)g_pGfxManager;
      v8 = v3->_CalculateUV();
      *(this + 43) = (gbRefObject *)(*(int (__thiscall **)(int, int))(v7 + 8))(g_pGfxManager, v8);
      *(this + 44) = (gbRefObject *)v3->Parent_Data();
    }
    v9 = (gbTexture *)*(this + 43);
    if ( v9 )
      v9->LoadTexture(1);
    (struct gbVFileSystem **->OpenNULLFile()&lpString);
  }
}

// 0x0043FAE0
void sub_43FAE0(gbRefObject **this, LPCSTR lpString, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  bool v6; // zf
  int v7; // ebp
  int v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString;
  if ( lpString )
  {
    v5 = *(this + 45);
    if ( v5 )
      v5->Release();
    OpenBaseFile::OpenBaseFile(&lpString);
    v6 = a3 == 0;
    *(this + 46) = 0;
    if ( v6 )
    {
      *(this + 45) = (gbRefObject *)(*(int (__thiscall **)(int, const CHAR *))(*(_DWORD *)g_pGfxManager + 8))(
                                      g_pGfxManager,
                                      v3);
    }
    else
    {
      v7 = *(_DWORD *)g_pGfxManager;
      v8 = v3->_CalculateUV();
      *(this + 45) = (gbRefObject *)(*(int (__thiscall **)(int, int))(v7 + 8))(g_pGfxManager, v8);
      *(this + 46) = (gbRefObject *)v3->Parent_Data();
    }
    v9 = (gbTexture *)*(this + 45);
    if ( v9 )
      v9->LoadTexture(1);
    (struct gbVFileSystem **->OpenNULLFile()&lpString);
  }
}

// 0x0043FCA0
void sub_43FCA0(int this, float a2)
{
  int v2; // eax
  double v3; // st7
  double v4; // st6

  *(float *)(this + 124) = a2;
  if ( a2 >= 0.0 )
  {
    v2 = *(_DWORD *)(this + 68);
    if ( v2 )
    {
      if ( v2 != 1 )
      {
LABEL_7:
        *(float *)(this + 128) = *(float *)(this + 120) / a2;
        *(float *)(this + 152) = a2 / *(float *)(this + 120);
        return;
      }
      v3 = (double)*(int *)(this + 28) - *(float *)(this + 148) - *(float *)(this + 132);
      v4 = (double)*(int *)(this + 20) + *(float *)(this + 144);
    }
    else
    {
      v3 = (double)*(int *)(this + 24) - *(float *)(this + 140) - *(float *)(this + 132);
      v4 = (double)*(int *)(this + 16) + *(float *)(this + 136);
    }
    *(float *)(this + 120) = v3 - (v4 + *(float *)(this + 132));
    goto LABEL_7;
  }
}

// 0x0043FDB0
void sub_43FDB0(float *this, int a2)
{
  *(this + 34) = (float)a2;
}

// 0x0043FDC0
void sub_43FDC0(float *this, int a2)
{
  *(this + 35) = (float)a2;
}

// 0x0043FDD0
void sub_43FDD0(float *this, int a2)
{
  *(this + 36) = (float)a2;
}

// 0x0043FDE0
void sub_43FDE0(float *this, int a2)
{
  *(this + 37) = (float)a2;
}

// 0x0043FDF0
void sub_43FDF0(int this, float a2)
{
  double v2; // st7
  double v3; // st6

  if ( *(float *)(this + 124) > 0.0 )
  {
    v2 = a2;
    if ( a2 < 0.0 )
      v2 = 0.0;
    if ( v2 > *(float *)(this + 124) )
      v2 = *(float *)(this + 124);
    v3 = v2 * *(float *)(this + 128);
    *(float *)(this + 116) = v3;
    if ( v3 >= *(float *)(this + 120) )
      *(_DWORD *)(this + 116) = *(_DWORD *)(this + 120);
    *(float *)(this + 156) = *(float *)(this + 152) * *(float *)(this + 108);
    if ( v2 > (double)*(int *)(this + 240) )
    {
      *(_BYTE *)(this + 238) = 1;
    }
    else
    {
      *(_BYTE *)(this + 237) = 1;
      *(_BYTE *)(this + 238) = 0;
    }
    *(_BYTE *)(this + 160) = 0;
  }
}

// 0x0043FEC0
int sub_43FEC0(_DWORD *this, _DWORD *a2)
{
  _DWORD *v2; // edx
  _DWORD *v3; // ecx
  int result; // eax

  v2 = this + 19;
  v3 = this + 4;
  *v2 = *a2;
  v2[1] = a2[1];
  v2[2] = a2[2];
  v2[3] = a2[3];
  *v3 = *a2;
  v3[1] = a2[1];
  v3[2] = a2[2];
  result = a2[3];
  v3[3] = result;
  return result;
}

// 0x004426B0
void sub_4426B0(gbRefObject **this, LPCSTR lpString1, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  char v6; // al
  int v7; // ebx
  int v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString1;
  if ( lpString1 )
  {
    v5 = *(this + 28);
    if ( v5 )
      v5->Release();
    OpenBaseFile::OpenBaseFile(&lpString1);
    lstrcmpA(v3, String2);
    v6 = a3;
    *(this + 29) = 0;
    if ( v6 )
    {
      v7 = *(_DWORD *)g_pGfxManager;
      v8 = v3->_CalculateUV();
      *(this + 28) = (gbRefObject *)(*(int (__thiscall **)(int, int))(v7 + 8))(g_pGfxManager, v8);
      *(this + 29) = (gbRefObject *)v3->Parent_Data();
    }
    else
    {
      *(this + 28) = (gbRefObject *)(*(int (__thiscall **)(int, const CHAR *))(*(_DWORD *)g_pGfxManager + 8))(
                                      g_pGfxManager,
                                      v3);
    }
    v9 = (gbTexture *)*(this + 28);
    if ( v9 )
      v9->LoadTexture(1);
    if ( !lstrcmpA(v3, String2) )
      MEMORY[0xD90D3C] = (int)*(this + 28);
    (struct gbVFileSystem **->OpenNULLFile()&lpString1);
  }
}

// 0x004427A0
int sub_4427A0(_DWORD *this, int a2)
{
  int result; // eax

  result = a2;
  if ( a2 )
    *(this + 23) = 2;
  else
    *(this + 23) = 1;
  return result;
}

// 0x004427C0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __thiscall sub_4427C0(_DWORD *this, const char *a2, int a3)
{
  int v3; // ebp
  unsigned int v4; // kr04_4
  unsigned int v5; // ebx
  int v6; // ecx
  char v7; // al
  unsigned int v8; // eax
  int v9; // ecx

  if ( a2 )
  {
    v3 = (int)(this + 24);
    v4 = strlen(a2) + 1;
    v5 = v4 - 1;
    if ( v4 - 1 > 0xFFFFFFFD )
      std::_Xlen();
    v6 = *(_DWORD *)(v3 + 4);
    if ( v6 && (v7 = *(_BYTE *)(v6 - 1)) != 0 && v7 != -1 )
    {
      if ( v4 == 1 )
      {
        *(_BYTE *)(v6 - 1) = v7 - 1;
        *(_DWORD *)(v3 + 4) = 0;
        *(_DWORD *)(v3 + 8) = 0;
        *(_DWORD *)(v3 + 12) = 0;
        goto LABEL_16;
      }
    }
    else
    {
      if ( v4 == 1 )
      {
        std::(_DWORD *->_Tidy()v3, 1);
        goto LABEL_16;
      }
      v8 = *(_DWORD *)(v3 + 12);
      if ( v8 <= 0x1F && v8 >= v5 )
      {
LABEL_15:
        qmemcpy(*(void **)(v3 + 4), a2, v5);
        v9 = *(_DWORD *)(v3 + 4);
        *(_DWORD *)(v3 + 8) = v5;
        *(_BYTE *)(v9 + v5) = 0;
LABEL_16:
        if ( a3 )
          *(this + 18) = 1;
        else
          *(this + 18) = 0;
        return;
      }
      std::(_DWORD *->_Tidy()v3, 1);
    }
    v3->GetKeyState(v5);
    goto LABEL_15;
  }
}

// 0x00445920
int UIWnd::Reset()
{
  return (gbRefObject **->MoveWindow()this + 26);
}

// 0x00445930
int UIWnd::SetState(int state)
{
  int result; // eax

  result = state;
  *((_DWORD *)this + 47) = state;
  if ( state )
  {
    *((_DWORD *)this + 43) = 2;
    *((_DWORD *)this + 22) = *(_DWORD *)&this->m_fontcolor[16];
    *((_DWORD *)this + 23) = *(_DWORD *)&this->m_fontcolor[20];
    *((_DWORD *)this + 24) = *(_DWORD *)&this->m_fontcolor[24];
    result = *(_DWORD *)&this->m_fontcolor[28];
    *((_DWORD *)this + 25) = result;
  }
  return result;
}

// 0x00445AA0
_DWORD * sub_445AA0(_DWORD *this)
{
  int v3; // [esp+4h] [ebp-4h]

  PtrArray::Clear(this + 9);
  *this = &off_56AEC8;
  *(this + 3) = -1;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(v3) = 0;
    LOWORD(v3) = 1285;
  }
  else
  {
    LOBYTE(v3) = 0;
    *(_WORD *)((char *)&v3 + 1) = 1285;
  }
  HIBYTE(v3) = -1;
  *(this + 1) = v3;
  *(this + 2) = -1;
  return this;
}

// 0x00445B40
void std::ios_base::~ios_base(std::ios_base *this)
{
  *(_DWORD *)this->_data = &off_56AEC8;
  this->UpdateChildren();
  sub_432680((void **)&this->_data[36]);
}

// 0x00445B90
int UIWnd::Create(int id, void *pRect, int parent)
{
  *(_DWORD *)&this->m_fontcolor[12] = id;
  *(_DWORD *)&this->m_fontcolor[16] = *(_DWORD *)pRect;
  *(_DWORD *)&this->m_fontcolor[20] = *((_DWORD *)pRect + 1);
  *(_DWORD *)&this->m_fontcolor[24] = *((_DWORD *)pRect + 2);
  *(_DWORD *)&this->m_fontcolor[28] = *((_DWORD *)pRect + 3);
  *(_DWORD *)&this->m_fontcolor[32] = parent;
  if ( parent )
  {
    sub_445BF0((int *)parent, (int)this);
    sub_445E10(*(_DWORD **)&this->m_fontcolor[32], &this->m_fontcolor[16]);
  }
  *(_DWORD *)&this->m_fontcolor[52] = 1;
  *(_DWORD *)&this->m_fontcolor[56] = 1;
  *(_DWORD *)&this->m_fontcolor[60] = 1;
  return 1;
}

// 0x00445C10
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __thiscall sub_445C10(_DWORD *this)
{
  int v2; // edi
  int v3; // ecx

  v2 = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  for ( *(this + 15) = 0; v2 < *(this + 10); ++v2 )
  {
    v3 = *(_DWORD *)(*(this + 9) + 4 * v2);
    (*(void (__thiscall **)(int))(*(_DWORD *)v3 + 12))(v3);
  }
  sub_4326A0((int)(this + 9), 0, -1);
}

// 0x00445C60
BOOL sub_445C60(_DWORD *this, int a2, int a3)
{
  int v5; // edi
  int v6; // esi
  int v7; // ecx

  if ( !*(this + 14) )
    return 0;
  if ( !*(this + 15) )
    return 0;
  v5 = *(this + 10) - 1;
  if ( v5 < 0 )
    return a3 == 0;
  v6 = a3;
  do
  {
    v7 = *(_DWORD *)(*(this + 9) + 4 * v5);
    if ( (*(int (__thiscall **)(int, int, int))(*(_DWORD *)v7 + 8))(v7, a2, v6) )
      v6 = 0;
    --v5;
  }
  while ( v5 >= 0 );
  return v6 == 0;
}

// 0x00445CD0
int sub_445CD0(_DWORD *this)
{
  int result; // eax
  int i; // esi
  _DWORD *v4; // ecx

  result = *(this + 14);
  if ( result )
  {
    result = *(this + 10);
    for ( i = 0; i < result; ++i )
    {
      v4 = *(_DWORD **)(*(this + 9) + 4 * i);
      if ( v4[14] )
        (*(void (__thiscall **)(_DWORD *))(*v4 + 4))(v4);
      result = *(this + 10);
    }
  }
  return result;
}

// 0x00445D10
int sub_445D10(int a1, int a2, int a3)
{
  return 0;
}

// 0x00445D20
int sub_445D20(_DWORD *this, int a2, int a3)
{
  return UIWnd::ClientToScreen(a2 - *(this + 4), a3 - *(this + 5));
}

// 0x00445D40
int sub_445D40(_DWORD *this, int a2, int a3)
{
  int v4; // ebp
  int v5; // edi
  int v6; // edx
  int v7; // ecx
  int result; // eax
  int i; // edi

  v4 = *(this + 4);
  v5 = *(this + 6);
  v6 = *(this + 5);
  v7 = *(this + 7);
  *(this + 4) = a2 + v4;
  *(this + 6) = a2 + v5;
  *(this + 5) = a3 + v6;
  *(this + 7) = a3 + v7;
  if ( this )
    (*(void (__thiscall **)(_DWORD *, int, _DWORD, _DWORD))(*this + 24))(this, 1022, 0, 0);
  result = *(this + 10);
  for ( i = 0; i < result; ++i )
  {
    a2->ClientToScreen(a3);
    result = *(this + 10);
  }
  return result;
}

// 0x00445DB0
int UIWnd::SetVisible(int bVisible)
{
  int v2; // ebx
  int v3; // edx
  int v4; // esi
  int v5; // edi

  if ( bVisible )
  {
    v4 = *(_DWORD *)(bVisible + 16);
    v5 = *(_DWORD *)(bVisible + 20);
    v2 = *(_DWORD *)(bVisible + 24);
    v3 = *(_DWORD *)(bVisible + 28);
  }
  else
  {
    v2 = MEMORY[0xBFD6D0];
    v3 = MEMORY[0xBFD6D4];
    v4 = 0;
    v5 = 0;
  }
  return this->ScreenToClient(v4 + (v2 + *(_DWORD *)&this->m_fontcolor[16] - *(_DWORD *)&this->m_fontcolor[24] - v4) / 2,
           v5 + (v3 + *(_DWORD *)&this->m_fontcolor[20] - *(_DWORD *)&this->m_fontcolor[28] - v5) / 2);
}

// 0x00445E70
int sub_445E70(int *this, int a2)
{
  int result; // eax
  int v3; // edx

  result = *(this + 13);
  if ( result )
  {
    result = a2;
    if ( *(this + 14) != a2 )
    {
      v3 = *this;
      *(this + 14) = a2;
      return (*(int (__stdcall **)(int, int, _DWORD))(v3 + 24))(1000, a2, 0);
    }
  }
  return result;
}

// 0x00445EA0
void * sub_445EA0()
{
  memset(this, 0, 0x44u);
  return this;
}

// 0x00445F20
int sub_445F20(gbRefObject **this)
{
  int v2; // esi
  gbRefObject **v3; // ebx

  v2 = 0;
  if ( (int)*(this + 16) > 0 )
  {
    v3 = this;
    do
    {
      gbRefObject::Release(*v3);
      ++v2;
      ++v3;
    }
    while ( v2 < (int)*(this + 16) );
  }
  memset(this, 0, 0x44u);
  return 0;
}

// 0x00445FA0
int sub_445FA0(_DWORD *this, _DWORD *a2)
{
  int result; // eax

  result = (int)(this + 4);
  *(this + 4) = *a2;
  *(this + 5) = a2[1];
  *(this + 6) = a2[2];
  *(this + 7) = a2[3];
  if ( this )
    return (*(int (__thiscall **)(_DWORD *, int, _DWORD, _DWORD))(*this + 24))(this, 1022, 0, 0);
  return result;
}

// 0x00445FE0
_DWORD * sub_445FE0(_DWORD *this, _DWORD *a2)
{
  _DWORD *v3; // ecx

  v3 = this + 4;
  *a2 = *v3;
  a2[1] = v3[1];
  a2[2] = v3[2];
  a2[3] = v3[3];
  return a2;
}

// 0x00446010
int UIWnd::GetChild(int id)
{
  *(_DWORD *)&this->m_fontcolor[4] = *(_DWORD *)id;
  return id;
}
