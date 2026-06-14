#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/ScreenEffect.h"

// Forward declarations for unnamed functions
__int64 sub_4B5570(int _this, char *pszName, int a3, TextureLibDataBase *a4, int a5); // from annotations
__int64 sub_4B5830(float *_this, char *pszName, int a3, TextureLibDataBase *a4, int a5); // from annotations
__int64 sub_4B59B0(char *_this, char *pszName, TextureLibDataBase *a3, int a4, int a5); // from annotations
__int64 sub_4B5BB0(float *_this, char *pszName, int a3, TextureLibDataBase *a4, int a5); // from annotations

// 0x004B4DC0
void ScreenEffect::Apply()
{
  double v1; // st7
  double v2; // st6
  TextureLibDataBase *v3; // edi
  char *v4; // ebx
  double v5; // st7
  TextureLibDataBase *v6; // ebp
  __int64 v7; // rax
  int v8; // [esp+0x14] [ebp+0x4]

  if ( *((_BYTE *)this + 128) )
  {
    v1 = (double)*((int *)this + 7);
    v2 = (double)*((int *)this + 6);
    v3 = (TextureLibDataBase *)(__int64)(*((float *)this + 35) - v1);
    v4 = (char *)(__int64)(*((float *)this + 34) - v2);
    v5 = v1 + *((float *)this + 35);
    v6 = (TextureLibDataBase *)(__int64)(v2 + *((float *)this + 34));
    v7 = (__int64)v5;
    switch ( v8 )
    {
      case 1:
        ((TextureLibDataBase *)this)->AutoScrollParticles(v4, (int)v3, v6, v7);
        break;
      case 2:
        ((TextureLibDataBase *)this)->AutoScrollParticlesEx(v4, v3, (int)v6, (__int64)v5);
        break;
      case 3:
        ((TextureLibDataBase *)this)->UpdateCircularMotion(v4, (int)v3, v6, v7);
        break;
      case 4:
        ((TextureLibDataBase *)this)->UpdateOrbitalMotion(v4, (int)v3, v6, (__int64)v5);
        break;
      case 5:
        sub_4B5570(v4, v3, v6, v7);
        break;
      case 6:
        ((TextureLibDataBase *)this)->UpdateLinearMotion(v4, (int)v3, v6, (__int64)v5);
        break;
      case 7:
        sub_4B5830(v4, v3, v6, v7);
        break;
      case 8:
        sub_4B5BB0(v4, v3, v6, v7);
        break;
      case 9:
        sub_4B59B0(v4, v3, v6, (__int64)v5);
        break;
      case 10:
        ((TextureLibDataBase *)this)->LoadLibrary(v4, (int)v3, v6, v7);
        break;
      case 11:
        ((TextureLibDataBase *)this)->UpdateByMode(v4, (int)v3, v6, (__int64)v5);
        break;
      case 12:
        ((TextureLibDataBase *)this)->RenderFrame((int)v4, (int)v3, (int)v6, (__int64)v5);
        break;
      case 13:
        ((TextureLibDataBase *)this)->GetTextureByName(v4, (int)v3, v6, v7);
        break;
      default:
        return;
    }
  }
}

// 0x004BDFB0
ScreenEffect::ScreenEffect()
{
  char v3; // [esp+0xB] [ebp-0x11]

  ((RenderTarget *)&this->m_needscriptdel)->ResetHorizontal();
  ((RenderTarget *)((char *)this + 32))->ResetVertical();
  ((RenderTarget *)((char *)this + 56))->ResetVertical2();
  ((RenderTarget *)((char *)this + 80))->ResetBase();
  *((_BYTE *)this + 104) = v3;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 30) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 32) = 0;
  *((_DWORD *)this + 33) = 0;
  *((_DWORD *)this + 34) = 0;
  *((_DWORD *)this + 35) = 0;
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 37) = 0;
  this;
}

// 0x004BE830
void ScreenEffect::CopyParams(int *pParams)
{
  gbImage2D *v2; // edx
  void **v3; // [esp+0x8] [ebp+0x8]

// [VFTABLE] this->__vftable = *v3;
  v2 = (gbImage2D *)((char *)*v3 + 4096);
  this->m_life = (int)v3;
  this->m_needscriptdel = v2;
  this->m_nType = (int)pParams;
}
