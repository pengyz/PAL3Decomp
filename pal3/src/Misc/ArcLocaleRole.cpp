#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ArcLocaleRole.h"

// Forward declarations for unnamed functions
bool sub_4AB560(_DWORD *_this, int a2, int a3); // from annotations
int todo_408BD0(...);

// Unnamed globals (extern)
extern char byte_A00604;
extern char byte_A00605;

// 0x0047F930
int ArcLocaleRole::HandleKeyInput()
{
  int result; // eax

  result = 1;
  if ( g_Input.KeyInfo[2].PressTime == 1 )
    return (*(int ( **)(ArcLocaleRole *, int, char *, _DWORD))(*(_DWORD *)&this->active + 24))(
             this,
             1001,
             &byte_A00604,
             0);
  if ( g_Input.KeyInfo[3].PressTime == 1 )
    return (*(int ( **)(ArcLocaleRole *, int, char *, _DWORD))(*(_DWORD *)&this->active + 24))(
             this,
             1001,
             &byte_A00605,
             0);
  return result;
}

// 0x004A6C70
int ArcLocaleRole::Release()
{
  operator delete((void *)LODWORD(this->pos.z));
  this->pos.z = 0.0;
  *(_DWORD *)&this->layer = 0;
  this->rotate = 0.0;
  return 0;
}

// 0x004AF410
int ArcLocaleRole::IterateColors()
{
  float y; // ebx
  float i; // esi

  y = this->pos.y;
  for ( i = this->pos.x; LODWORD(i) != LODWORD(y); LODWORD(i) += 24 )
    ((ArcLocaleRole *)LODWORD(i))->Release();
  operator delete((void *)LODWORD(this->pos.x));
  this->pos.x = 0.0;
  this->pos.y = 0.0;
  this->pos.z = 0.0;
  return 0;
}

// 0x004AFB60
int * ArcLocaleRole::CalcPosition(int *p_DWORD)
{
  ArcLocaleRole *v2; // ebx
  int v3; // ecx
  unsigned int v4; // esi
  float x; // edx
  unsigned int v6; // eax
  int v7; // esi
  int v8; // eax
  _DWORD *v9; // ecx
  float v10; // ebx
  int v11; // ecx
  unsigned int v13; // esi
  unsigned int v14; // eax
  int v15; // eax
  _DWORD *v16; // eax
  _DWORD *v17; // esi
  float v18; // ebx
  int v19; // edx
  float i; // ecx
  int v21; // ecx
  int v22; // eax
  _DWORD *v23; // eax
  int v24; // edx
  _DWORD *v25; // ecx
  _DWORD *j; // eax
if ( this != (ArcLocaleRole *)p_DWORD )
  {
    v3 = p_DWORD[1];
    if ( v3 )
      v4 = (p_DWORD[2] - v3) >> 4;
    else
      v4 = 0;
    x = this->pos.x;
    if ( x == 0.0 )
      v6 = 0;
    else
      v6 = (LODWORD(this->pos.y) - LODWORD(x)) >> 4;
    if ( v4 <= v6 )
    {
      v7 = p_DWORD[2];
      v8 = p_DWORD[1];
      if ( v3 != v7 )
      {
        do
        {
          v9 = (_DWORD *)v8;
          v10 = x;
          v8 += 16;
          LODWORD(x) += 16;
          *(_DWORD *)LODWORD(v10) = *v9;
          *(_DWORD *)(LODWORD(v10) + 4) = v9[1];
          *(_DWORD *)(LODWORD(v10) + 8) = v9[2];
          *(_DWORD *)(LODWORD(v10) + 12) = v9[3];
        }
        while ( v8 != v7 );
}
      v11 = p_DWORD[1];
      if ( !v11 )
      {
        this->pos.y = this->pos.x;
        return (int *)v2;
      }
LABEL_33:
      LODWORD(this->pos.y) = LODWORD(this->pos.x) + 16 * ((p_DWORD[2] - v11) >> 4);
      return (int *)v2;
    }
    if ( v3 )
      v13 = (p_DWORD[2] - v3) >> 4;
    else
      v13 = 0;
    if ( x == 0.0 )
      v14 = 0;
    else
      v14 = (LODWORD(this->pos.z) - LODWORD(x)) >> 4;
    if ( v13 <= v14 )
    {
      if ( x == 0.0 )
        v15 = 0;
      else
        v15 = (LODWORD(this->pos.y) - LODWORD(x)) >> 4;
      v16 = (_DWORD *)(v3 + 16 * v15);
      if ( (_DWORD *)v3 != v16 )
      {
        do
        {
          v17 = (_DWORD *)v3;
          v18 = x;
          v3 += 16;
          LODWORD(x) += 16;
          *(_DWORD *)LODWORD(v18) = *v17;
          *(_DWORD *)(LODWORD(v18) + 4) = v17[1];
          *(_DWORD *)(LODWORD(v18) + 8) = v17[2];
          *(_DWORD *)(LODWORD(v18) + 12) = v17[3];
        }
        while ( (_DWORD *)v3 != v16 );
}
      v19 = p_DWORD[2];
      for ( i = this->pos.y; v16 != (_DWORD *)v19; LODWORD(i) += 16 )
      {
        if ( i != 0.0 )
        {
          *(_DWORD *)LODWORD(i) = *v16;
          *(_DWORD *)(LODWORD(i) + 4) = v16[1];
          *(_DWORD *)(LODWORD(i) + 8) = v16[2];
          *(_DWORD *)(LODWORD(i) + 12) = v16[3];
}
        v16 += 4;
      }
      v11 = p_DWORD[1];
      if ( !v11 )
      {
        this->pos.y = this->pos.x;
        return (int *)v2;
      }
      goto LABEL_33;
    }
    operator delete((void *)LODWORD(this->pos.x));
    v21 = p_DWORD[1];
    if ( v21 )
      v22 = (p_DWORD[2] - v21) >> 4;
    else
      v22 = 0;
    if ( v22 < 0 )
      v22 = 0;
    v23 = operator new(16 * v22);
    LODWORD(this->pos.x) = v23;
    v24 = p_DWORD[2];
    v25 = v23;
    for ( j = (_DWORD *)p_DWORD[1]; j != (_DWORD *)v24; v25 += 4 )
    {
      if ( v25 )
      {
        *v25 = *j;
        v25[1] = j[1];
        v25[2] = j[2];
        v25[3] = j[3];
      }
      j += 4;
    }
    LODWORD(this->pos.y) = v25;
    LODWORD(this->pos.z) = v25;
  }
  return (int *)v2;
}

// 0x004AFD80
unsigned int ArcLocaleRole::ParseLocaleData(char *pszBuf2, int nVal)
{
  char *v3; // ebx
  char *v4; // ebp
  unsigned int result; // eax
  int v6; // edx
  char *v7; // ebx
  int v8; // edi
  int v9; // esi
  char *v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // esi
  BOOL v15; // eax
  int v16; // ecx
  bool v17; // sf
  bool v18; // of
  int v19; // eax
  bool v20; // al
  int *v21; // edx
  bool v22; // al
  int v23; // eax
  int v24; // ecx
  int v25; // edx
  char *v26; // edi
  char *v27; // esi
  bool v28; // al
  int v29; // eax
  int v30; // ecx
  int *v31; // edx
  _DWORD *v32; // ebx
  int v33; // eax
  int v34; // ecx
  int v35; // eax
  int v36; // [esp+0x8] [ebp-0x44] BYREF
  int v37; // [esp+0xC] [ebp-0x40] BYREF
  int v38; // [esp+0x10] [ebp-0x3C] BYREF
  int v39; // [esp+0x14] [ebp-0x38]
  int v40; // [esp+0x18] [ebp-0x34]
  _DWORD v41[3]; // [esp+0x1C] [ebp-0x30] BYREF
  int v42; // [esp+0x28] [ebp-0x24] BYREF
  int v43; // [esp+0x2C] [ebp-0x20]
  int v44; // [esp+0x30] [ebp-0x1C]
  _DWORD v45[5]; // [esp+0x34] [ebp-0x18] BYREF
  int v46; // [esp+0x48] [ebp-0x4]

  v3 = pszBuf2;
  v4 = pszBuf;
  result = (unsigned int)((unsigned __int64)(715827883LL * (pszBuf2 - pszBuf)) >> 32) >> 31;
  v6 = (pszBuf2 - pszBuf) / 12;
  if ( v6 <= 16 )
    return result;
  do
  {
    v7 = v3 - 12;
    v41[0] = *(_DWORD *)v4;
    v8 = *((_DWORD *)v4 + 1);
    v9 = *((_DWORD *)v4 + 2);
    v41[1] = v8;
    v41[2] = v9;
    v10 = &v4[12 * (v6 / 2)];
    v45[0] = *(_DWORD *)v10;
    v11 = *((_DWORD *)v10 + 1);
    v45[1] = v11;
    v12 = *((_DWORD *)v10 + 2);
    v38 = *(_DWORD *)v7;
    v45[2] = v12;
    v39 = *((_DWORD *)v7 + 1);
    v40 = *((_DWORD *)v7 + 2);
    v36 = nVal;
    if ( !nVal )
    {
      v13 = *(_DWORD *)(v9 + 608);
      v14 = *(_DWORD *)(v12 + 608);
      goto LABEL_8;
    }
    if ( nVal == 1 )
    {
      v13 = *(_DWORD *)(v9 + 624);
      v14 = *(_DWORD *)(v12 + 624);
LABEL_8:
      LOBYTE(v13) = v13 < v14;
      goto LABEL_9;
    }
    if ( nVal != 2 )
      goto LABEL_19;
    v13 = v8 > v11;
LABEL_9:
    if ( (_BYTE)v13 )
    {
      if ( nVal )
      {
        if ( nVal != 1 )
        {
          v15 = v11 > v39;
          goto LABEL_16;
        }
        v16 = *(_DWORD *)(v12 + 624);
        v18 = __OFSUB__(v16, *(_DWORD *)(v40 + 624));
        v17 = v16 - *(_DWORD *)(v40 + 624) < 0;
      }
      else
      {
        v19 = *(_DWORD *)(v12 + 608);
        v18 = __OFSUB__(v19, *(_DWORD *)(v40 + 608));
        v17 = v19 - *(_DWORD *)(v40 + 608) < 0;
      }
      LOBYTE(v15) = v17 ^ v18;
LABEL_16:
      if ( !v15 )
      {
        v20 = sub_4AB560(&v36, (int)v41, (int)&v38);
        v21 = &v38;
        if ( !v20 )
          v21 = v41;
        goto LABEL_23;
      }
LABEL_22:
      v21 = v45;
      goto LABEL_23;
    }
LABEL_19:
    if ( sub_4AB560(&v36, (int)v41, (int)&v38) )
    {
      v21 = v41;
    }
    else
    {
      v22 = sub_4AB560(&v36, (int)v45, (int)&v38);
      v21 = &v38;
      if ( !v22 )
        goto LABEL_22;
    }
LABEL_23:
    v23 = *v21;
    v24 = v21[1];
    v25 = v21[2];
    v37 = nVal;
    v3 = pszBuf2;
    v42 = v23;
    v43 = v24;
    v44 = v25;
    v26 = pszBuf2;
    v27 = v4;
    while ( 1 )
    {
      while ( 1 )
      {
        if ( !v37 )
        {
          v29 = *(_DWORD *)(*((_DWORD *)v27 + 2) + 608);
          v30 = *(_DWORD *)(v25 + 608);
          goto LABEL_30;
        }
        if ( v37 == 1 )
        {
          v29 = *(_DWORD *)(*((_DWORD *)v27 + 2) + 624);
          v30 = *(_DWORD *)(v25 + 624);
LABEL_30:
          v28 = v29 < v30;
          goto LABEL_31;
        }
        if ( v37 != 2 )
          break;
        v28 = *((_DWORD *)v27 + 1) > v43;
LABEL_31:
        if ( !v28 )
          break;
        v27 += 12;
      }
      for ( v26 -= 12; sub_4AB560(&v37, (int)&v42, (int)v26); v26 -= 12 )
        ;
      if ( v26 <= v27 )
        break;
      v31 = (int *)v27;
      v32 = v27;
      v27 += 12;
      v33 = *v31;
      v34 = v31[1];
      v46 = v31[2];
      *v32 = *(_DWORD *)v26;
      v32[1] = *((_DWORD *)v26 + 1);
      v4 = pszBuf;
      v32[2] = *((_DWORD *)v26 + 2);
      v3 = pszBuf2;
      *(_DWORD *)v26 = v33;
      v35 = v46;
      *((_DWORD *)v26 + 1) = v34;
      *((_DWORD *)v26 + 2) = v35;
      v25 = v44;
    }
    if ( (v3 - v27) / 12 > (v27 - v4) / 12 )
    {
      ((ArcLocaleRole *)v4)->ParseLocaleData(v27, nVal);
      v4 = v27;
      pszBuf = v27;
    }
    else
    {
      ((ArcLocaleRole *)v27)->ParseLocaleData(v3, nVal);
      v3 = v27;
      pszBuf2 = v27;
    }
    result = (unsigned int)((unsigned __int64)(715827883LL * (v3 - v4)) >> 32) >> 31;
    v6 = (v3 - v4) / 12;
  }
  while ( v6 > 16 );
  return result;
}

// 0x005303C0
int ArcLocaleRole::DispatchActive(int nVal)
{
  return (*(int ( **)(_DWORD))(**(_DWORD **)&this->active + 20))(*(_DWORD *)&this->active);
}

// 0x00535030
int ArcLocaleRole::Destroy()
{
  void *v2; // edi
  float x; // edi
  float y; // edi
  float z; // ecx
  void *v6; // edi
  float rotate; // ecx
  void *v9; // [esp+0x0] [ebp-0x8]

  v2 = *(void **)&this->active;
  if ( *(_DWORD *)&this->active )
  {
    todo_408BD0(v9);
    operator delete(v2);
  }
  x = this->pos.x;
  if ( x != 0.0 )
  {
    ((UISceneFrm *)LODWORD(this->pos.x))->ShowAndRelease();
    operator delete((void *)LODWORD(x));
  }
  y = this->pos.y;
  if ( y != 0.0 )
  {
    todo_408BD0(v9);
    operator delete((void *)LODWORD(y));
  }
  z = this->pos.z;
  if ( z != 0.0 )
    (**(void ( ***)(float, int))LODWORD(z))(COERCE_FLOAT(LODWORD(z)), 1);
  v6 = *(void **)&this->layer;
  if ( v6 )
  {
    todo_408BD0(v9);
    operator delete(v6);
  }
  rotate = this->rotate;
  if ( rotate != 0.0 )
    (*(void ( **)(float, int))(*(_DWORD *)LODWORD(rotate) + 20))(COERCE_FLOAT(LODWORD(rotate)), 1);
  return ((PalScript *)this)->ResetAll();
}

// 0x005350C0
void ArcLocaleRole::GetScreenLeft(double thisa)
{
  int v3; // eax
  float x; // ecx
  double v5; // [esp-0x4] [ebp-0xC]
  int v6; // [esp+0x4] [ebp-0x4]

  v3 = *(_DWORD *)&this->layer;
  *((_BYTE *)this + 36) = 0;
  *((_BYTE *)this + 37) = 0;
  if ( v3 )
  {
    if ( *(_BYTE *)(v3 + 135) )
    {
      x = this->pos.x;
      if ( x != 0.0 )
      {
        LODWORD(v5) = g_nMiniGameParam;
        ((UISceneMap *)LODWORD(x))->LoadOverlayTexture(v5, v6);
        ((Actor *)LODWORD(this->rotate))->InitActorComponents();
      }
    }
    ((UITabCtrl *)*(UITabCtrl **)&this->layer)->Render();
    ((RoleAtt *)LODWORD(this->pos.z))->ResetFightState();
    *((_BYTE *)this + 36) = 0;
    *((_BYTE *)this + 37) = 0;
  }
  ((UICursor *)this)->IRender();
}

// 0x00535FD0
float * ArcLocaleRole::TransformPoint(float *a2, float a3, float a4, float a5)
{
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  float v10; // [esp+0xC] [ebp-0x14]
  float v11; // [esp+0xC] [ebp-0x14]
  float v12; // [esp+0xC] [ebp-0x14]
  float v13; // [esp+0xC] [ebp-0x14]
  float v14; // [esp+0x10] [ebp-0x10]
  float v15; // [esp+0x10] [ebp-0x10]
  float v16; // [esp+0x10] [ebp-0x10]
  float v17; // [esp+0x10] [ebp-0x10]
  float v18; // [esp+0x18] [ebp-0x8]
  float v19; // [esp+0x18] [ebp-0x8]
  float v20; // [esp+0x18] [ebp-0x8]
  float v21; // [esp+0x18] [ebp-0x8]
  float v22; // [esp+0x1C] [ebp-0x4]
  float v23; // [esp+0x1C] [ebp-0x4]
  float v24; // [esp+0x1C] [ebp-0x4]
  float v25; // [esp+0x1C] [ebp-0x4]

  v10 = *(this + 20) * -0.5;
  v14 = *(this + 21) * -0.5;
  v5 = *(this + 19) * -0.5 + a3;
  v18 = a4 + v10;
  *(this + 23) = v18;
  v22 = a5 + v14;
  *(this + 22) = v5;
  *(this + 24) = v22;
  v19 = *(this + 20) * -0.5;
  v23 = *(this + 21) * -0.5;
  v6 = *(this + 19) * 0.5 + a3;
  v11 = v19 + a4;
  *(this + 26) = v11;
  v15 = v23 + a5;
  *(this + 25) = v6;
  *(this + 27) = v15;
  v20 = *(this + 20) * -0.5;
  v24 = *(this + 21) * 0.5;
  v7 = *(this + 19) * 0.5 + a3;
  v12 = v20 + a4;
  *(this + 29) = v12;
  v16 = v24 + a5;
  *(this + 28) = v7;
  *(this + 30) = v16;
  v21 = *(this + 20) * -0.5;
  v25 = *(this + 21) * 0.5;
  v8 = *(this + 19) * -0.5 + a3;
  v13 = v21 + a4;
  *(this + 32) = v13;
  v17 = v25 + a5;
  *(this + 31) = v8;
  *(this + 33) = v17;
  qmemcpy(a2, this + 22, 0x44u);
  return a2;
}
