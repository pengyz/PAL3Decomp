#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ArcLocaleRole.h"
#include "GameBase/GRPinput.h"
#include "Script/PalScript.h"
#include "Misc/PtrArray.h"
#include "Misc/RoleAtt.h"
#include "UI/UICursor.h"
#include "Misc/UISceneFrm.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x0047F930
int ArcLocaleRole::HandleKeyInput()
{
  int result; // eax

  result = 1;
  if ( g_Input.KeyInfo[2].PressTime == 1 )
    return (*(int ( **)(ArcLocaleRole *, int, int *, _DWORD))(*(_DWORD *)&this->active + 24))(
             this,
             1001,
             &byte_A00604,
             0);
  if ( g_Input.KeyInfo[3].PressTime == 1 )
    return (*(int ( **)(ArcLocaleRole *, int, int *, _DWORD))(*(_DWORD *)&this->active + 24))(
             this,
             1001,
             &byte_A00605,
             0);
  return result;
}

// 0x004A6C70
int ArcLocaleRole::Release()
{
  int result; // eax

  operator delete((void *)LODWORD(this->pos.z));
  result = 0;
  this->pos.z = 0.0f;
  *(_DWORD *)&this->layer = 0;
  this->rotate = 0.0f;
  return result;
}

// 0x004AF410
int ArcLocaleRole::IterateColors()
{
  float y; // ebx
  float i; // esi
  int result; // eax

  y = this->pos.y;
  for ( i = this->pos.x; LODWORD(i) != LODWORD(y); LODWORD(i) += 24 )
    (((ArcLocaleRole *)LODWORD(i)))->ArcLocaleRole::Release();
  operator delete((void *)LODWORD(this->pos.x));
  result = 0;
  this->pos.x = 0.0f;
  this->pos.y = 0.0f;
  this->pos.z = 0.0f;
  return result;
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
    v3 = (unsigned long)p_DWORD[1];
    if ( v3 )
      v4 = (p_DWORD[2] - v3) >> 4;
    else
      v4 = 0;
    x = this->pos.x;
    if ( x == 0.0f )
      v6 = 0;
    else
      v6 = (LODWORD(this->pos.y) - LODWORD(x)) >> 4;
    if ( v4 <= v6 )
    {
      v7 = (unsigned long)p_DWORD[2];
      v8 = (unsigned long)p_DWORD[1];
      if ( v3 != v7 )
      {
        do
        {
          v9 = (_DWORD *)v8;
          v10 = x;
          v8 += 16;
          LODWORD(x) += 16;
          *(_DWORD *)LODWORD(v10) = (unsigned long)*v9;
          *(_DWORD *)(LODWORD(v10) + 4) = (unsigned long)v9[1];
          *(_DWORD *)(LODWORD(v10) + 8) = (unsigned long)v9[2];
          *(_DWORD *)(LODWORD(v10) + 12) = (unsigned long)v9[3];
        }
        while ( v8 != v7 );
}
      v11 = (unsigned long)p_DWORD[1];
      if ( !v11 )
      {
        this->pos.y = this->pos.x;
        return (int *)this;
      }
LABEL_33:
      LODWORD(this->pos.y) = LODWORD(this->pos.x) + 16 * ((p_DWORD[2] - v11) >> 4);
      return (int *)this;
    }
    if ( v3 )
      v13 = (p_DWORD[2] - v3) >> 4;
    else
      v13 = 0;
    if ( x == 0.0f )
      v14 = 0;
    else
      v14 = (LODWORD(this->pos.z) - LODWORD(x)) >> 4;
    if ( v13 <= v14 )
    {
      if ( x == 0.0f )
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
          *(_DWORD *)LODWORD(v18) = (unsigned long)*v17;
          *(_DWORD *)(LODWORD(v18) + 4) = (unsigned long)v17[1];
          *(_DWORD *)(LODWORD(v18) + 8) = (unsigned long)v17[2];
          *(_DWORD *)(LODWORD(v18) + 12) = (unsigned long)v17[3];
        }
        while ( (_DWORD *)v3 != v16 );
}
      v19 = (unsigned long)p_DWORD[2];
      for ( i = this->pos.y; v16 != (_DWORD *)v19; LODWORD(i) += 16 )
      {
        if ( i != 0.0f )
        {
          *(_DWORD *)LODWORD(i) = (unsigned long)*v16;
          *(_DWORD *)(LODWORD(i) + 4) = (unsigned long)v16[1];
          *(_DWORD *)(LODWORD(i) + 8) = (unsigned long)v16[2];
          *(_DWORD *)(LODWORD(i) + 12) = (unsigned long)v16[3];
}
        v16 += 4;
      }
      v11 = (unsigned long)p_DWORD[1];
      if ( !v11 )
      {
        this->pos.y = this->pos.x;
        return (int *)this;
      }
      goto LABEL_33;
    }
    operator delete((void *)LODWORD(this->pos.x));
    v21 = (unsigned long)p_DWORD[1];
    if ( v21 )
      v22 = (p_DWORD[2] - v21) >> 4;
    else
      v22 = 0;
    if ( v22 < 0 )
      v22 = 0;
    v23 = (_DWORD *)operator new(16 * v22);
    LODWORD(this->pos.x) = (unsigned long)v23;
    v24 = (unsigned long)p_DWORD[2];
    v25 = (_DWORD *)v23;
    for ( j = (_DWORD *)p_DWORD[1]; j != (_DWORD *)v24; v25 += 4 )
    {
      if ( v25 )
      {
        *v25 = *j;
        v25[1] = (unsigned long)j[1];
        v25[2] = (unsigned long)j[2];
        v25[3] = (unsigned long)j[3];
      }
      j += 4;
    }
    LODWORD(this->pos.y) = (unsigned long)v25;
    LODWORD(this->pos.z) = (unsigned long)v25;
  }
  return (int *)this;
}

// 0x004AFD80
unsigned int ArcLocaleRole::ParseLocaleData(char *pszBuf, char *pszBuf2, int nVal)
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

  v3 = (char *)pszBuf2;
  v4 = (char *)pszBuf;
  result = (unsigned int)((unsigned __int64)(715827883i64 * (pszBuf2 - pszBuf)) >> 32) >> 31;
  v6 = (pszBuf2 - pszBuf) / 12;
  if ( v6 <= 16 )
    return result;
  do
  {
    v7 = (char *)(v3 - 12);
    v41[0] = *(_DWORD *)v4;
    v8 = *((_DWORD *)v4 + 1);
    v9 = *((_DWORD *)v4 + 2);
    v41[1] = v8;
    v41[2] = v9;
    v10 = (char *)&v4[12 * (v6 / 2)];
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
        v21 = (int *)&v38;
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
      v21 = (int *)&v38;
      if ( !v22 )
        goto LABEL_22;
    }
LABEL_23:
    v23 = (unsigned long)*v21;
    v24 = (unsigned long)v21[1];
    v25 = (unsigned long)v21[2];
    v37 = nVal;
    v3 = (char *)pszBuf2;
    v42 = v23;
    v43 = v24;
    v44 = v25;
    v26 = (char *)pszBuf2;
    v27 = (char *)v4;
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
      v32 = (_DWORD *)v27;
      v27 += 12;
      v33 = (unsigned long)*v31;
      v34 = (unsigned long)v31[1];
      v46 = (unsigned long)v31[2];
      *v32 = *(_DWORD *)v26;
      v32[1] = *((_DWORD *)v26 + 1);
      v4 = (char *)pszBuf;
      v32[2] = *((_DWORD *)v26 + 2);
      v3 = (char *)pszBuf2;
      *(_DWORD *)v26 = v33;
      v35 = v46;
      *((_DWORD *)v26 + 1) = v34;
      *((_DWORD *)v26 + 2) = v35;
      v25 = v44;
    }
    if ( (v3 - v27) / 12 > (v27 - v4) / 12 )
    {
      ArcLocaleRole::ParseLocaleData(v4, v27, nVal);
      v4 = (char *)v27;
      pszBuf = v27;
    }
    else
    {
      ArcLocaleRole::ParseLocaleData(v27, v3, nVal);
      v3 = (char *)v27;
      pszBuf2 = v27;
    }
    result = (unsigned int)((unsigned __int64)(715827883i64 * (v3 - v4)) >> 32) >> 31;
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

  v2 = (void *)(*(void **)&this->active);
  if ( *(_DWORD *)&this->active )
  {
    NullCallback(v9);
    operator delete(v2);
  }
  x = this->pos.x;
  if ( x != 0.0f )
  {
    UISceneFrm_ShowAndRelease((int)v9);
    operator delete((void *)LODWORD(x));
  }
  y = this->pos.y;
  if ( y != 0.0f )
  {
    NullCallback(v9);
    operator delete((void *)LODWORD(y));
  }
  z = this->pos.z;
  if ( z != 0.0f )
    (**(void ( ***)(float, int))LODWORD(z))((float)(_pal3_coerce_f32(LODWORD(z))), (int)(1));
  v6 = (void *)(*(void **)&this->layer);
  if ( v6 )
  {
    NullCallback(v9);
    operator delete(v6);
  }
  rotate = this->rotate;
  if ( rotate != 0.0f )
    (*(void ( **)(float, int))(*(_DWORD *)LODWORD(rotate) + 20))(_pal3_coerce_f32(LODWORD(rotate)), 1);
  return (((PalScript *)this))->PalScript::ResetAll();
}

// 0x005350C0
void ArcLocaleRole::GetScreenLeft(double thisa)
{
  int v3; // eax
  float x; // ecx
  int v5; // [esp+0x0] [ebp-0x8]

  v3 = *(_DWORD *)&this->layer;
  LOBYTE(this[1].pos.y) = 0;
  BYTE1(this[1].pos.y) = 0;
  if ( v3 )
  {
    if ( *(_BYTE *)(v3 + 135) )
    {
      x = this->pos.x;
      if ( x != 0.0f )
      {
        LoadOverlayTexture((UISceneFrm *)LODWORD(x));
        Actor_InitActorComponents(v5);
      }
    }
    UITabCtrl_Render(v5);
    (((RoleAtt *)LODWORD(this->pos.z)))->RoleAtt::ResetFightState();
    LOBYTE(this[1].pos.y) = 0;
    BYTE1(this[1].pos.y) = 0;
  }
  (((UICursor *)this))->UICursor::_todo_541CC0();
}
