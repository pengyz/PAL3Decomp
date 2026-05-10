#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffExplosive.h"
#include "pal3/gen/CEffCallBack.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_4C7E60(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Co_13[];
extern char aNewFailInCeffe[];
extern unsigned char byte_DE99AC;
extern int dword_DE9980;
extern int dword_DE9984;
extern int dword_DE9988;
extern int dword_DE9990;
extern int dword_DE9994;
extern int dword_DE9998;
extern int dword_DE99A0;
extern int dword_DE99A4;
extern int dword_DE99A8;
extern int nullsub_1;
extern int nullsub_80;
extern int nullsub_81;
extern int nullsub_82;
extern int unk_5D4D3C;
extern int unk_5D4D7C;
extern int unk_5D4DAC;
extern int unk_5D4DB8;
extern int unk_5D4DC4;
extern int unk_5D4DCC;
extern int unk_5D4DD4;
extern int unk_5D4DF4;
extern int unk_5D4E00;
extern int unk_5D4E24;
extern int unk_5D4E30;
extern int unk_5D4E38;
extern int unk_5D4E40;
extern int unk_5D5038;
extern int unk_5D5040;
extern int unk_5D5048;
extern int unk_5D5050;
extern int unk_5D51A4;
extern int unk_5D51B0;
extern int unk_5D51BC;
extern int unk_5D51C8;
extern int unk_5D51D0;
extern int unk_5D51D8;
extern int unk_5D51EC;
extern int unk_5D51F8;
extern int unk_5D5204;
extern int unk_5D5210;
extern int unk_5D521C;
extern int unk_FFFFFF;

// 0x004C6C10
char CEffExplosive::Create(int a2)
{
  _DWORD *v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int m_nQuad; // ebx
  gbGeomQuad *v12; // eax
  int v13; // ebx
  int v14; // ebp
  int v15; // ebx
  int v16; // edi
  int v17; // ebx
  tagExplosive *v18; // eax
  _DWORD *p_z; // ecx
  int v20; // edx
  gbGeomQuad *m_pGeomQuad; // ecx
  gbGeomQuad *v23; // [esp+10h] [ebp-810h]
  char pExceptionObject[1024]; // [esp+14h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+414h] [ebp-40Ch] BYREF
  int v26; // [esp+81Ch] [ebp-4h]

  v3 = (_DWORD *)operator new(0x4C0u);
  *(_DWORD *)&this->_pad_0000[24] = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v5 + *(_DWORD *)&this->_pad_0000[24]) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v5 + *(_DWORD *)&this->_pad_0000[24]) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *(_DWORD *)&this->_pad_0000[40] = 8;
        *(_DWORD *)&this->_pad_0000[44] = 10;
        v7 = 0;
        do
        {
          *(_BYTE *)(v7 + *(_DWORD *)&this->_pad_0000[24] + 148) = 0;
          v8 = 0;
          if ( *(int *)&this->_pad_0000[44] > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(*(_DWORD *)(v7 + *(_DWORD *)&this->_pad_0000[24]) + v9 - 8) = 0;
            }
            while ( v8 < *(_DWORD *)&this->_pad_0000[44] );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *(_DWORD *)&this->_pad_0000[40] );
        goto LABEL_10;
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v16 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(v16 + *(_DWORD *)&this->_pad_0000[24]));
        v16 -= 152;
        --v4;
      }
      while ( v4 );
    }
    operator delete(*(void **)&this->_pad_0000[24]);
  }
LABEL_10:
  this->m_nXDivision = (__int64)*(float *)(a2 + 224);
  this->m_nZDivision = (__int64)*(float *)(a2 + 232);
  this->m_fGridSize = *(float *)(a2 + 228);
  this->m_fMaxExplosivePower = *(float *)(a2 + 244);
  this->m_fMinExplosivePower = *(float *)(a2 + 248);
  this->m_vecExplosiveDir.x = *(float *)(a2 + 252);
  this->m_vecExplosiveDir.y = *(float *)(a2 + 256);
  v10 = this->m_nXDivision * this->m_nZDivision;
  this->m_vecExplosiveDir.z = *(float *)(a2 + 268);
  this->m_fPowerDec = *(float *)(a2 + 260);
  this->m_nQuad = v10;
  this->m_fFramePerSec = *(float *)(a2 + 180);
  this->m_vecPos.x = *(float *)(a2 + 184);
  this->m_vecPos.y = *(float *)(a2 + 188);
  this->m_vecPos.z = *(float *)(a2 + 192);
  this->m_vecRot.x = *(float *)(a2 + 216);
  this->m_vecRot.y = *(float *)(a2 + 196);
  this->m_vecRot.z = *(float *)(a2 + 220);
  this->m_bAdditiveBlend = *(_BYTE *)(a2 + 213);
  this->m_bNoZTest = *(_BYTE *)(a2 + 215);
  this->m_byMaxFrame = *(_BYTE *)(a2 + 176);
  this->m_nRequireLoops = (int)&unk_FFFFFF;
  this->m_dwStartColor = *(_DWORD *)(a2 + 204);
  this->InitDefaultUVSet(*(_DWORD *)(a2 + 168), *(_DWORD *)(a2 + 172));
  m_nQuad = this->m_nQuad;
  v12 = (gbGeomQuad *)operator new(68 * m_nQuad);
  v23 = v12;
  v26 = 0;
  if ( v12 )
  {
    v13 = m_nQuad - 1;
    v14 = (int)v12;
    if ( v13 >= 0 )
    {
      v15 = v13 + 1;
      do
      {
        ArraySort(v14, 12, 4, gbVec3D::`default constructor closure');
        v14 += 68;
        --v15;
      }
      while ( v15 );
      v12 = v23;
    }
  }
  else
  {
    v12 = 0;
  }
  v17 = this->m_nQuad;
  this->m_pGeomQuad = v12;
  v26 = -1;
  v18 = (tagExplosive *)operator new(24 * v17);
  if ( v18 )
  {
    if ( v17 - 1 >= 0 )
    {
      p_z = (_DWORD *)&v18->vecRot.z;
      v20 = v17;
      do
      {
        *(p_z - 5) = 0;
        *(p_z - 4) = 0;
        *(p_z - 3) = 0;
        *(p_z - 2) = 0;
        *(p_z - 1) = 0;
        *p_z = 0;
        p_z += 6;
        --v20;
      }
      while ( v20 );
    }
  }
  else
  {
    v18 = 0;
  }
  m_pGeomQuad = (gbGeomQuad *)this->m_pGeomQuad;
  this->m_pExplosive = v18;
  if ( !m_pGeomQuad || !v18 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aNewFailInCeffe, aDProjectPal3Co_13, 121),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  this->LoadTexture(a2 + 40);
  return 1;
}

// 0x004C6F20
void CEffExplosive::Destroy()
{
  unsigned __int8 m_bAdditiveBlend; // al
  bool v3; // zf
  _DWORD *v4; // eax
  struct gbRenderEffect *v5; // ebp
  gbMatrixStack *v6; // edi
  float v7; // [esp+3Ch] [ebp-Ch]
  float retaddr; // [esp+48h] [ebp+0h] BYREF

  if ( (byte_DE99AC & 1) == 0 )
  {
    dword_DE99A0 = 1065353216;
    byte_DE99AC |= 1u;
    dword_DE99A4 = 0;
    dword_DE99A8 = 0;
    atexit(nullsub_82);
  }
  if ( (byte_DE99AC & 2) == 0 )
  {
    dword_DE9990 = 0;
    byte_DE99AC |= 2u;
    dword_DE9994 = 1065353216;
    dword_DE9998 = 0;
    atexit(nullsub_81);
  }
  if ( (byte_DE99AC & 4) == 0 )
  {
    dword_DE9980 = 0;
    byte_DE99AC |= 4u;
    dword_DE9984 = 0;
    dword_DE9988 = 1065353216;
    atexit(nullsub_80);
  }
  if ( !this->_pad_0000[8] && this->m_bVisible )
  {
    ((gbVertPoolMgr *)*(gbVertPoolMgr **)(**(_DWORD **)&this->_pad_0000[4] + 196))->GetDynVertBuf(0x15u);
    m_bAdditiveBlend = this->m_bAdditiveBlend;
    if ( this->m_bNoZTest )
    {
      v3 = m_bAdditiveBlend == 0;
      v4 = (_DWORD *)*(_DWORD **)&this->_pad_0000[4];
      if ( v3 )
        v5 = (struct gbRenderEffect *)v4[3];
      else
        v5 = (struct gbRenderEffect *)v4[2];
    }
    else
    {
      v3 = m_bAdditiveBlend == 0;
      v4 = (_DWORD *)*(_DWORD **)&this->_pad_0000[4];
      if ( v3 )
        v5 = (struct gbRenderEffect *)v4[5];
      else
        v5 = (struct gbRenderEffect *)v4[4];
    }
    v6 = (gbMatrixStack *)*(gbMatrixStack **)(*v4 + 216);
    v6->Push();
    v7 = this->m_vecOffsetPos.x + this->m_vecPos.x;
    retaddr = v7;
    v6->Translate((struct gbVec3D *)&retaddr);
    v6->Scale(this->m_fXSize, 1.0, this->m_fZSize);
    v6->Rotate(this->m_vecRot.x, (struct gbVec3D *)&dword_DE99A0);
    v6->Rotate(this->m_vecRot.y, (struct gbVec3D *)&dword_DE9990);
    v6->Rotate(this->m_vecRot.z, (struct gbVec3D *)&dword_DE9980);
    ((gbDynVertBuf *)this->m_pGeomQuad)->RenderGeomQuad(this->m_nQuad, v5, this->m_pTextureArray);
    v6->Pop();
  }
}

// 0x004C7680
int CEffExplosive::ProcCommonTask(int _94)
{
  double v3; // st7
  int v4; // edi
  int v5; // ecx
  double v6; // st7
  int v7; // ebp
  double m_fAlpha; // st7
  unsigned __int16 v9; // cx
  float a3; // [esp+10h] [ebp-80h]
  int a3a; // [esp+10h] [ebp-80h]
  float a2; // [esp+24h] [ebp-6Ch]
  float v14; // [esp+28h] [ebp-68h]
  float v15; // [esp+2Ch] [ebp-64h]
  float v16; // [esp+30h] [ebp-60h]
  float v17; // [esp+34h] [ebp-5Ch]
  gbVec3D v18; // [esp+38h] [ebp-58h] BYREF
  struct gbVec3D v19; // [esp+44h] [ebp-4Ch] BYREF
  _BYTE v20[64]; // [esp+50h] [ebp-40h] BYREF

  v3 = *(float *)&this->_pad_0000[16];
  v4 = *(_DWORD *)&this->_pad_0000[24] + 152 * *(_DWORD *)&this->_pad_0000[28];
  v5 = 9 * *(_DWORD *)&this->_pad_0000[32];
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  a2 = *(float *)&this->_pad_0000[20];
  if ( v6 > *(float *)(v7 + 24) )
    a2 = a2 - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    *(_DWORD *)(v7 + 44) = 0;
    this->m_bVisible = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  if ( *(float *)&this->_pad_0000[16] - *(float *)(v7 + 16) > *(float *)(v4 + 84) && !*(_DWORD *)(v7 + 44) )
  {
    sub_4C7E60((int)this);
    *(_DWORD *)(v7 + 44) = 1;
  }
  this->m_vecRot.x = a2 * *(float *)(v4 + 64) + this->m_vecRot.x;
  this->m_vecRot.y = a2 * *(float *)(v4 + 68) + this->m_vecRot.y;
  this->m_vecRot.z = a2 * *(float *)(v4 + 72) + this->m_vecRot.z;
  this->m_vecPos.x = a2 * *(float *)(v4 + 28) + this->m_vecPos.x;
  this->m_vecPos.y = a2 * *(float *)(v4 + 32) + this->m_vecPos.y;
  this->m_vecPos.z = a2 * *(float *)(v4 + 36) + this->m_vecPos.z;
  ((gbMatrix4 *)v20)->gbMatrix4();
  memset(&v18, 0, sizeof(v18));
  memset(&v19, 0, sizeof(v19));
  ((gbMatrix4 *)v20)->LoadIdentity();
  v18 = *(gbVec3D *)(v4 + 44);
  ((gbVec3D *)&v18)->Normalize();
  a3 = (*(float *)&this->_pad_0000[16] - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  ((gbMatrix4 *)v20)->SetAxisAngle(&v18, a3);
  v19.z = *(float *)(v4 + 56);
  v19.x = 0.0;
  v19.y = 0.0;
  ((gbMatrix4 *)v20)->Rotate(&v19, &this->m_vecOffsetPos);
  if ( *(float *)(v4 + 80) != 0.0
    || *(float *)(v4 + 84) != 0.0
    || *(float *)(v4 + 92) != 0.0
    || *(float *)(v4 + 88) != 0.0 )
  {
    this->m_fAlpha = a2 * *(float *)(v4 + 80) + this->m_fAlpha;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    if ( this->m_fAlpha <= 255.0 )
    {
      if ( this->m_fAlpha >= 0.0 )
        m_fAlpha = this->m_fAlpha;
      else
        m_fAlpha = 0.0;
    }
    else
    {
      m_fAlpha = 255.0;
    }
    this->m_fAlpha = m_fAlpha;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v14 = this->m_fAlpha + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v15 = this->m_fRed + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v16 = this->m_fGreen + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    v17 = this->m_fBlue + 12582912.0;
    if ( (g_bCursorVisible & 1) == 0 )
    {
      g_bCursorVisible |= 1u;
      ((CEffMgr *)&g_nCursorState)->Reset();
      atexit(nullsub_1);
    }
    HIBYTE(v9) = LOBYTE(v14);
    LOBYTE(v9) = LOBYTE(v15);
    this->m_dwStartColor = LOBYTE(v17) | ((LOBYTE(v16) | (v9 << 8)) << 8);
  }
  this->m_fXSize = a2 * *(float *)(v4 + 24) + this->m_fXSize;
  this->m_fZSize = a2 * *(float *)(v4 + 108) + this->m_fZSize;
  if ( *(_DWORD *)(v7 + 44) == 1 )
  {
    *(float *)&a3a = *(float *)&this->_pad_0000[16] - *(float *)(v7 + 16);
    this->UpdateExplosive(a2, a3a);
  }
  if ( *(_BYTE *)(v7 + 66) == 1 || *(float *)&this->_pad_0000[16] - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
    *(_DWORD *)(v7 + 8) = 4;
  return 0;
}

// 0x004C7A70
void * CEffExplosive::GetEditorTaskDescription(int a1)
{
  void *result; // eax

  switch ( a1 )
  {
    case 0:
      result = (void *)&unk_5D5050;
      break;
    case 1:
      result = (void *)&unk_5D4E40;
      break;
    case 2:
      result = (void *)&unk_5D4E38;
      break;
    case 3:
      result = (void *)&unk_5D4E30;
      break;
    case 4:
      result = (void *)&unk_5D4E24;
      break;
    case 5:
      result = (void *)&unk_5D5048;
      break;
    case 6:
      result = (void *)&unk_5D5040;
      break;
    case 7:
      result = (void *)&unk_5D5038;
      break;
    case 8:
      result = (void *)&unk_5D4E00;
      break;
    case 9:
      result = (void *)&unk_5D4DF4;
      break;
    case 10:
      result = (void *)&unk_5D51B0;
      break;
    case 12:
      result = (void *)&unk_5D4DD4;
      break;
    case 13:
      result = (void *)&unk_5D4DCC;
      break;
    case 14:
      result = (void *)&unk_5D4DC4;
      break;
    case 15:
      result = (void *)&unk_5D4DB8;
      break;
    case 16:
      result = (void *)&unk_5D4DAC;
      break;
    case 17:
      result = (void *)&unk_5D51A4;
      break;
    case 20:
      result = (void *)&unk_5D4D7C;
      break;
    default:
      result = (void *)&unk_5D4D3C;
      break;
  }
  return result;
}

// 0x004C7B70
void * CEffExplosive::GetEditorObjDescription(int a1)
{
  void *result; // eax

  switch ( a1 )
  {
    case 0:
      result = (void *)&unk_5D521C;
      break;
    case 1:
      result = (void *)&unk_5D5210;
      break;
    case 2:
      result = (void *)&unk_5D5204;
      break;
    case 3:
      result = (void *)&unk_5D51F8;
      break;
    case 4:
      result = (void *)&unk_5D51EC;
      break;
    case 5:
      result = (void *)&CTaskTpl<tagEffTaskParam,unsigned long (CEffCallBack::*)(unsigned long)>::DelTask;
      break;
    case 6:
      result = (void *)&unk_5D51D8;
      break;
    case 7:
      result = (void *)&unk_5D51D0;
      break;
    case 8:
      result = (void *)&unk_5D51C8;
      break;
    case 9:
      result = (void *)&unk_5D51BC;
      break;
    default:
      result = (void *)&unk_5D4D3C;
      break;
  }
  return result;
}

// 0x004C7C00
void CEffExplosive::InitDefaultUVSet(int a2, int a3)
{
  int v3; // ebx
  float *p_eu; // edi
  int v5; // ecx
  double v6; // st7
  float *v7; // eax
  double v8; // st5
  double v9; // st5
  double v10; // st3
  double v11; // st3
  int v12; // [esp+8h] [ebp-8h]
  float v13; // [esp+8h] [ebp-8h]
  int v14; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v12 = 0;
  if ( a3 > 0 )
  {
    p_eu = (float *)&this->m_DefaultUVSet[0].eu;
    do
    {
      v5 = 0;
      v14 = 0;
      if ( a2 > 0 )
      {
        v6 = (double)a2;
        v7 = p_eu;
        p_eu += 4 * a2;
        v8 = (double)a3;
        v13 = (double)v12 / v8;
        v9 = 1.0 - (1.0 / v8 + v13);
        do
        {
          v10 = (double)v14;
          v7 += 4;
          v14 = ++v5;
          v11 = v10 / v6;
          *(v7 - 6) = v11;
          *(v7 - 4) = 1.0 / v6 + v11;
          *(v7 - 5) = v9;
          *(v7 - 3) = 1.0 - v13;
        }
        while ( v5 < a2 );
      }
      v12 = ++v3;
    }
    while ( v3 < a3 );
  }
}

// 0x004C7CB0
_DWORD * CEffExplosive::LoadTexture(int a2)
{
  gbTexture *v3; // eax
  _DWORD *result; // eax
  gbTexture *m_pTexture; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  v3 = (gbTexture *)(*(int (**)(_DWORD, int))(***(_DWORD ***)&this->_pad_0000[4] + 8))(
                      **(_DWORD **)&this->_pad_0000[4],
                      a2);
  this->m_pTexture = v3;
  v3->LoadTexture(1);
  result = (_DWORD *)operator new(0x44u);
  if ( result )
  {
    m_pTexture = (gbTexture *)this->m_pTexture;
    result[16] = 1;
    *result = m_pTexture;
  }
  else
  {
    result = 0;
  }
  this->m_pTextureArray = (gbTextureArray *)result;
  if ( !result )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_13, 499),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004C7D40
int CEffExplosive::CreateGeom()
{
  int m_nXDivision; // edx
  int result; // eax
  int v3; // ebx
  int v4; // ebp
  double i; // st7
  double v6; // st6
  int v7; // esi
  int v8; // eax
  gbGeomQuad *m_pGeomQuad; // edx
  gbGeomQuad *v10; // edx
  gbGeomQuad *v11; // edx
  gbGeomQuad *v12; // edx
  gbGeomQuad *v13; // edx
  double v14; // st5
  float *v15; // edx
  float v16; // [esp+8h] [ebp-4h]

  m_nXDivision = this->m_nXDivision;
  result = this->m_nZDivision;
  v3 = 0;
  v4 = 0;
  v16 = (double)m_nXDivision * this->m_fGridSize * -0.5;
  for ( i = (double)result * this->m_fGridSize * 0.5; v4 < result; i = i - this->m_fGridSize )
  {
    v6 = v16;
    v7 = 0;
    if ( m_nXDivision > 0 )
    {
      v8 = 68 * v3;
      do
      {
        m_pGeomQuad = (gbGeomQuad *)this->m_pGeomQuad;
        *(float *)((char *)&m_pGeomQuad->vec[0].y + v8) = 0.0;
        *(float *)((char *)&m_pGeomQuad->vec[0].x + v8) = v6;
        ++v3;
        *(float *)((char *)&m_pGeomQuad->vec[0].z + v8) = i;
        v10 = (gbGeomQuad *)this->m_pGeomQuad;
        *(float *)((char *)&v10->vec[1].y + v8) = 0.0;
        *(float *)((char *)&v10->vec[1].x + v8) = v6;
        *(float *)((char *)&v10->vec[1].z + v8) = i;
        *(float *)((char *)&this->m_pGeomQuad->vec[1].x + v8) = *(float *)((char *)&this->m_pGeomQuad->vec[1].x + v8)
                                                              + this->m_fGridSize;
        v11 = (gbGeomQuad *)this->m_pGeomQuad;
        *(float *)((char *)&v11->vec[2].y + v8) = 0.0;
        *(float *)((char *)&v11->vec[2].x + v8) = v6;
        *(float *)((char *)&v11->vec[2].z + v8) = i;
        *(float *)((char *)&this->m_pGeomQuad->vec[2].x + v8) = *(float *)((char *)&this->m_pGeomQuad->vec[2].x + v8)
                                                              + this->m_fGridSize;
        *(float *)((char *)&this->m_pGeomQuad->vec[2].z + v8) = *(float *)((char *)&this->m_pGeomQuad->vec[2].z + v8)
                                                              - this->m_fGridSize;
        v12 = (gbGeomQuad *)this->m_pGeomQuad;
        *(float *)((char *)&v12->vec[3].y + v8) = 0.0;
        *(float *)((char *)&v12->vec[3].x + v8) = v6;
        *(float *)((char *)&v12->vec[3].z + v8) = i;
        v13 = (gbGeomQuad *)this->m_pGeomQuad;
        v14 = *(float *)((char *)&v13->vec[3].z + v8) - this->m_fGridSize;
        v15 = (float *)((char *)&v13->vec[3].z + v8);
        v8 += 68;
        ++v7;
        *v15 = v14;
        m_nXDivision = this->m_nXDivision;
        v6 = v6 + this->m_fGridSize;
      }
      while ( v7 < m_nXDivision );
    }
    result = this->m_nZDivision;
    ++v4;
  }
  return result;
}

// 0x004C8370
int CEffExplosive::UpdateExplosive(float a2, int a3)
{
  int result; // eax
  int v5; // ebp
  int v6; // edi
  int v7; // ebp
  float *v8; // eax
  double v9; // st7
  gbGeomQuad *m_pGeomQuad; // ecx
  float *v11; // eax
  gbGeomQuad *v12; // edx
  float *v13; // eax
  gbGeomQuad *v14; // eax
  double v15; // st6
  float *v16; // eax
  tagExplosive *m_pExplosive; // ecx
  gbGeomQuad *v18; // eax
  double v19; // st7
  float *v20; // eax
  gbGeomQuad *v21; // ecx
  float *v22; // eax
  gbGeomQuad *v23; // edx
  float *v24; // eax
  gbGeomQuad *v25; // eax
  double v26; // st7
  float *v27; // eax
  int v28; // edx
  bool v29; // cc
  float v30; // [esp+4h] [ebp-90h]
  float v31; // [esp+8h] [ebp-8Ch]
  float v32; // [esp+Ch] [ebp-88h]
  int v33; // [esp+20h] [ebp-74h]
  int v34; // [esp+24h] [ebp-70h]
  int v35; // [esp+28h] [ebp-6Ch]
  float v36; // [esp+2Ch] [ebp-68h]
  float v37; // [esp+30h] [ebp-64h]
  float v38; // [esp+30h] [ebp-64h]
  float v39; // [esp+34h] [ebp-60h]
  float v40; // [esp+34h] [ebp-60h]
  float v41; // [esp+3Ch] [ebp-58h]
  float v42; // [esp+40h] [ebp-54h]
  gbQuaternion v43; // [esp+44h] [ebp-50h] BYREF
  _BYTE v44[64]; // [esp+54h] [ebp-40h] BYREF

  memset(&v43, 0, 12);
  v43.w = 1.0;
  ((gbMatrix4 *)v44)->gbMatrix4();
  result = this->m_nXDivision;
  v5 = 0;
  v33 = 0;
  v35 = 0;
  if ( result > 0 )
  {
    do
    {
      v34 = 0;
      if ( this->m_nZDivision > 0 )
      {
        v6 = 68 * v5;
        v7 = v5;
        do
        {
          v8 = (float *)((char *)this->m_pGeomQuad + v6);
          v9 = (v8[9] + v8[6] + v8[3] + *v8) * 0.25;
          v37 = (v8[10] + v8[7] + v8[4] + v8[1]) * 0.25;
          v39 = (v8[11] + v8[8] + v8[5] + v8[2]) * 0.25;
          * v8 = (*)*v8 - v9;
          v8[1] = v8[1] - v37;
          v8[2] = v8[2] - v39;
          m_pGeomQuad = (gbGeomQuad *)this->m_pGeomQuad;
          v11 = (float *)((char *)&m_pGeomQuad->vec[1].x + v6);
          * v11 = (*)*v11 - v9;
          v11[1] = *(float *)((char *)&m_pGeomQuad->vec[1].y + v6) - v37;
          v11[2] = *(float *)((char *)&m_pGeomQuad->vec[1].z + v6) - v39;
          v12 = (gbGeomQuad *)this->m_pGeomQuad;
          v13 = (float *)((char *)&v12->vec[2].x + v6);
          * v13 = (*)*v13 - v9;
          v13[1] = *(float *)((char *)&v12->vec[2].y + v6) - v37;
          v13[2] = *(float *)((char *)&v12->vec[2].z + v6) - v39;
          v14 = (gbGeomQuad *)this->m_pGeomQuad;
          v15 = *(float *)((char *)&v14->vec[3].x + v6);
          v16 = (float *)((char *)&v14->vec[3].x + v6);
          * v16 = (*)v15 - v9;
          v16[1] = v16[1] - v37;
          v16[2] = v16[2] - v39;
          m_pExplosive = (tagExplosive *)this->m_pExplosive;
          v41 = a2 * m_pExplosive[v7].vecSpeed.y;
          v42 = a2 * m_pExplosive[v7].vecSpeed.z;
          v36 = a2 * m_pExplosive[v7].vecSpeed.x + v9;
          v38 = v41 + v37;
          v40 = v42 + v39;
          v32 = a2 * m_pExplosive[v7].vecRot.z;
          v31 = a2 * m_pExplosive[v7].vecRot.y;
          v30 = a2 * m_pExplosive[v7].vecRot.x;
          ((gbQuaternion *)&v43)->SetYawPitchRoll(v30, v31, v32);
          ((gbQuaternion *)&v43)->GetMatrix((struct gbMatrix4 *)v44);
          ((gbMatrix4 *)v44)->RotateIn((struct gbVec3D *)((char *)this->m_pGeomQuad->vec + v6));
          ((gbMatrix4 *)v44)->RotateIn((struct gbVec3D *)((char *)&this->m_pGeomQuad->vec[1] + v6));
          ((gbMatrix4 *)v44)->RotateIn((struct gbVec3D *)((char *)&this->m_pGeomQuad->vec[2] + v6));
          ((gbMatrix4 *)v44)->RotateIn((struct gbVec3D *)((char *)&this->m_pGeomQuad->vec[3] + v6));
          v18 = (gbGeomQuad *)this->m_pGeomQuad;
          v19 = v36 + *(float *)((char *)&v18->vec[0].x + v6);
          v20 = (float *)((char *)v18 + v6);
          *v20 = v19;
          v20[1] = v38 + v20[1];
          v20[2] = v40 + v20[2];
          v21 = (gbGeomQuad *)this->m_pGeomQuad;
          v22 = (float *)((char *)&v21->vec[1].x + v6);
          * v22 = (*)v36 + *v22;
          v22[1] = v38 + *(float *)((char *)&v21->vec[1].y + v6);
          v22[2] = v40 + *(float *)((char *)&v21->vec[1].z + v6);
          v23 = (gbGeomQuad *)this->m_pGeomQuad;
          v24 = (float *)((char *)&v23->vec[2].x + v6);
          * v24 = (*)v36 + *v24;
          v24[1] = v38 + *(float *)((char *)&v23->vec[2].y + v6);
          v24[2] = v40 + *(float *)((char *)&v23->vec[2].z + v6);
          v25 = (gbGeomQuad *)this->m_pGeomQuad;
          v26 = v36 + *(float *)((char *)&v25->vec[3].x + v6);
          v27 = (float *)((char *)&v25->vec[3].x + v6);
          *v27 = v26;
          ++v7;
          v6 += 68;
          v27[1] = v38 + v27[1];
          v27[2] = v40 + v27[2];
          v28 = v33 + 1;
          v29 = ++v34 < this->m_nZDivision;
          ++v33;
        }
        while ( v29 );
        v5 = v28;
      }
      result = ++v35;
    }
    while ( v35 < this->m_nXDivision );
  }
  return result;
}
