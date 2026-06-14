#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffGrid.h"

// Forward declarations for unnamed functions
int sub_4C9550(...);
int sub_4CAB30(...);
int sub_4CABE0(...);
int sub_4CAC70(...);
int sub_4CB130(...);
void __cdecl todo_401800(void);

// Unnamed globals (extern)
extern char byte_FFFFFF;
extern int dword_5D4DAC;
extern int dword_5D4DB8;
extern int dword_5D4DC4;
extern int dword_5D4DCC;
extern int dword_5D4DD4;
extern int dword_5D4E00;
extern int dword_5D4E24;
extern int dword_5D4E30;
extern int dword_5D4E38;
extern int dword_5D4E40;
extern int dword_5D4FFC;
extern int dword_5D5008;
extern int dword_5D5014;
extern int dword_5D5038;
extern int dword_5D5040;
extern int dword_5D5048;
extern int dword_5D5050;
extern int dword_5D51B0;
extern int dword_5D51F8;
extern int dword_5D5204;
extern int dword_5D5210;
extern int dword_5D5278;
extern int dword_5D5284;
extern int dword_5D5290;
extern int dword_5D529C;
extern int dword_5D52A8;
void __cdecl nullsub_83(void);
void __cdecl nullsub_84(void);
void __cdecl nullsub_85(void);

// 0x004C9610
CEffGrid::CEffGrid()
{
  void *v1; // eax

  v1 = operator new(0x10B8u);
  if ( v1 )
    sub_4C9550(v1);
}

// 0x004C9650
void CEffGrid::_CEffGrid()
{
  CEffObj *v2; // edi
  gbGeomQuad *m_pGeomQuad; // eax
  int v4; // ebp
  gbRefObject *m_pTexture; // ecx
  CEffObj *v6; // esi
  CEffMgr *m_pEM; // eax
  bool v8; // cc
  int v9; // edi

  v2 = this + 1;
  m_pGeomQuad = this->m_pGeomQuad;
  v4 = 0;
  if ( m_pGeomQuad )
    operator delete(m_pGeomQuad);
  if ( this->m_pMesh )
    operator delete(this->m_pMesh);
  if ( this->m_pMesh2 )
    operator delete(this->m_pMesh2);
  m_pTexture = (gbRefObject *)this->m_pTexture;
  if ( m_pTexture )
    ((gbRefObject *)m_pTexture)->Release();
  if ( this->m_pTextureArray )
    operator delete(this->m_pTextureArray);
  v6 = this != 0 ? v2 : 0;
  m_pEM = v6[2].m_pEM;
  v8 = (int)m_pEM <= 0;
  if ( !m_pEM )
  {
    if ( !*(this != 0 ? (_DWORD *)&v2[2].m_bIdle : (_DWORD *)32) )
      return;
    v8 = 1;
  }
  if ( !v8 )
  {
    v9 = 0;
    do
    {
// [VFTABLE] operator delete(*(void **)((char *)v6[1].__vftable + v9));
      ++v4;
// [VFTABLE] *(_DWORD *)((char *)v6[1].__vftable + v9) = 0;
      v9 += 152;
    }
    while ( v4 < (int)v6[2].m_pEM );
  }
// [VFTABLE] operator delete(v6[1].__vftable);
// [VFTABLE] v6[1].__vftable = 0;
  v6[2].m_pEM = 0;
  *(_DWORD *)&v6[2].m_bIdle = 0;
}

// 0x004C9750
int CEffGrid::Init(float *pfVal, float fVal, float fVal2, float fVal3)
{
  int m_dwStartColor_low; // ecx
  int result; // eax

  this->m_bIdle = 0;
  this->m_bVisible = 0;
  this->m_vecPos.x = fVal + pfVal[46];
  this->m_vecPos.y = fVal2 + pfVal[47];
  this->m_vecPos.z = fVal3 + pfVal[48];
  this->m_vecRot.x = pfVal[54];
  this->m_vecRot.y = pfVal[49];
  this->m_vecRot.z = pfVal[55];
  this->m_vecOffsetPos.z = 0.0;
  this->m_vecOffsetPos.y = 0.0;
  this->m_vecOffsetPos.x = 0.0;
  this->m_dwStartColor = (unsigned int)pfVal[51];
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_fAlpha = (float)HIBYTE(this->m_dwStartColor);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_fRed = (float)(unsigned __int8)BYTE2(this->m_dwStartColor);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_fGreen = (float)(unsigned __int8)BYTE1(this->m_dwStartColor);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  this->m_fCurFrame = 0.0;
  m_dwStartColor_low = LOBYTE(this->m_dwStartColor);
  this->m_nLoops = 0;
  this->m_fBlue = (float)m_dwStartColor_low;
  this->m_fXSize = pfVal[50];
  result = *((_DWORD *)pfVal + 50);
  LODWORD(this->m_fZSize) = result;
  return result;
}

// 0x004C98F0
char CEffGrid::Create(tagEffObjType *pType)
{
// [IDA_MISID]   _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v3; // esp
  void *v5; // eax
  int v6; // ebx
  int v7; // edi
  int v8; // edi
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  __int64 fSacleZ; // rax
  float fSacleY; // ecx
  int m_nQuad; // ebx
  gbGeomQuad *v15; // eax
  int v16; // ebx
  int v17; // ebp
  int v18; // ebx
  int v19; // edi
  int v20; // ebp
  gbVec3D *v21; // eax
  int v22; // ebp
  gbVec3D *v23; // ebx
  int v24; // ebp
  int v25; // ebp
  gbVec3D *v26; // eax
  int v27; // ebp
  gbVec3D *v28; // ebx
  int v29; // ebp
  gbVec3D *m_pMesh; // ecx
  gbGeomQuad *v32; // [esp+0x0] [ebp-0x1010]
  gbVec3D *v33; // [esp+0x0] [ebp-0x1010]
  gbVec3D *v34; // [esp+0x0] [ebp-0x1010]
  _BYTE v35[1024]; // [esp+0x4] [ebp-0x100C] BYREF
  char pExceptionObject[1024]; // [esp+0x404] [ebp-C0Ch] BYREF
  char ArgList; // [esp+0x804] [ebp-0x80C] BYREF
  char v38; // [esp+C04h] [ebp-0x40C] BYREF
  _EXCEPTION_REGISTRATION_RECORD *v39; // [esp+0x1004] [ebp-0xC]
  void *v40; // [esp+0x1008] [ebp-0x8]
  int v41; // [esp+0x100C] [ebp-0x4]

  v41 = -1;
// [IDA_MISID]   ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v40 = ((void*)0);
// [IDA_MISID]   v39 = ExceptionList;
  v3 = alloca(4100);
  v5 = operator new(0x4C0u);
  *((_DWORD *)this + 6) = v5;
  if ( v5 )
  {
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      *(_DWORD *)(v7 + *((_DWORD *)this + 6)) = operator new(0x2D0u);
      if ( !*(_DWORD *)(v7 + *((_DWORD *)this + 6)) )
        break;
      v7 += 152;
      ++v6;
      if ( v7 >= 1216 )
      {
        v8 = 0;
        *((_DWORD *)this + 10) = 8;
        *((_DWORD *)this + 11) = 10;
        v9 = 0;
        do
        {
          *(_BYTE *)(v9 + *((_DWORD *)this + 6) + 148) = 0;
          v10 = 0;
          if ( *((int *)this + 11) > 0 )
          {
            v11 = 0;
            do
            {
              ++v10;
              v11 += 72;
              *(_BYTE *)(*(_DWORD *)(v9 + *((_DWORD *)this + 6)) + v11 - 8) = 0;
            }
            while ( v10 < *((_DWORD *)this + 11) );
          }
          ++v8;
          v9 += 152;
        }
        while ( v8 < *((_DWORD *)this + 10) );
        goto LABEL_10;
      }
    }
    if ( v6 > 0 && v6 - 1 >= 0 )
    {
      v19 = 152 * (v6 - 1);
      do
      {
        operator delete(*(void **)(v19 + *((_DWORD *)this + 6)));
        v19 -= 152;
        --v6;
      }
      while ( v6 );
    }
    operator delete(*((void **)this + 6));
  }
LABEL_10:
  this->m_nXDivision = (__int64)pType->fSacleX;
  fSacleZ = (__int64)pType->fSacleZ;
  this->m_nZDivision = fSacleZ;
  fSacleY = pType->fSacleY;
  this->m_nQuad = this->m_nXDivision * fSacleZ;
  this->m_fGridSize = fSacleY;
  this->m_fFramePerSec = pType->fFramePerSec;
  this->m_vecPos.x = pType->fX;
  this->m_vecPos.y = pType->fY;
  this->m_vecPos.z = pType->fZ;
  this->m_vecRot.x = pType->fStartXRot;
  this->m_vecRot.y = pType->fStartYRot;
  this->m_vecRot.z = pType->fStartZRot;
  this->m_bAdditiveBlend = pType->bAdditiveBlend;
  this->m_bNoZTest = pType->bNoZTest;
  this->m_byMaxFrame = pType->nFrame;
  this->m_nRequireLoops = (int)&byte_FFFFFF;
  this->m_dwStartColor = pType->dwColor;
  this->m_fWavePower = pType->fTopRadius;
  this->m_fWaveSpeed = pType->fBottomRadius;
  this->m_fFlapPower = pType->fTextureRepeat;
  this->m_fFlapSpeed = pType->fTopRadiusIncSpeed;
  sub_4CAB30(pType->nFramePerRow, pType->nFramePerCol);
  m_nQuad = this->m_nQuad;
  v15 = (gbGeomQuad *)operator new(68 * m_nQuad);
  v32 = v15;
  v41 = 0;
  if ( v15 )
  {
    v16 = m_nQuad - 1;
    v17 = (int)v15;
    if ( v16 >= 0 )
    {
      v18 = v16 + 1;
      do
      {
        v17 += 68;
        --v18;
      }
      while ( v18 );
      v15 = v32;
    }
  }
  else
  {
    v15 = 0;
  }
  v41 = -1;
  this->m_pGeomQuad = v15;
  if ( !v15 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("new fail in CEffGrid::Create", "D:\\Project\\PAL3\\combat\\EffGrid.cpp", 115),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v20 = (this->m_nXDivision + 1) * (this->m_nZDivision + 1);
  v21 = (gbVec3D *)operator new(12 * v20);
  v33 = v21;
  v41 = 1;
  if ( v21 )
  {
    v22 = v20 - 1;
    v23 = v21;
    if ( v22 >= 0 )
    {
      v24 = v22 + 1;
      do
      {
        --v24;
      }
      while ( v24 );
      v21 = v33;
    }
  }
  else
  {
    v21 = 0;
  }
  v25 = (this->m_nXDivision + 1) * (this->m_nZDivision + 1);
  this->m_pMesh = v21;
  v26 = (gbVec3D *)operator new(12 * v25);
  v34 = v26;
  v41 = 2;
  if ( v26 )
  {
    v27 = v25 - 1;
    v28 = v26;
    if ( v27 >= 0 )
    {
      v29 = v27 + 1;
      do
      {
        --v29;
      }
      while ( v29 );
      v26 = v34;
    }
  }
  else
  {
    v26 = 0;
  }
  m_pMesh = this->m_pMesh;
  v41 = -1;
  this->m_pMesh2 = v26;
  if ( !m_pMesh || !v26 )
  {
    qmemcpy(v35, ((Logger *)&v38)->FormatException("new fail in CEffGrid::Create", "D:\\Project\\PAL3\\combat\\EffGrid.cpp", 124), sizeof(v35));
    _CxxThrowException(v35, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  sub_4CABE0(pType->szTexture);
  sub_4CAC70(this);
  return 1;
}

// 0x004C9CA0
int CEffGrid::slot_6(int a2, int a3)
{
  int result; // eax
  char m_bAdditiveBlend; // al
  bool v6; // zf
  CEffMgr *m_pEM; // eax
  gbRenderEffect *m_pAlphaBlendNoZ; // ebp
  gbMatrixStack *v9; // edi
  float v10; // [esp+0x3C] [ebp-0xC]
  float retaddr; // [esp+0x48] [ebp+0x0] BYREF

  if ( (*(_BYTE *)(&g_PAL3.m_nCEffCylinderCount + 13) & 1) == 0 )
  {
    *(&g_PAL3.m_nCEffCylinderCount + 10) = 1065353216;
    *((_BYTE *)&g_PAL3.m_nCEffCylinderCount + 52) |= 1u;
    *(&g_PAL3.m_nCEffCylinderCount + 11) = 0;
    *(&g_PAL3.m_nCEffCylinderCount + 12) = 0;
    result = atexit(nullsub_85);
  }
  if ( (*(_BYTE *)(&g_PAL3.m_nCEffCylinderCount + 13) & 2) == 0 )
  {
    *(&g_PAL3.m_nCEffCylinderCount + 6) = 0;
    *((_BYTE *)&g_PAL3.m_nCEffCylinderCount + 52) |= 2u;
    *(&g_PAL3.m_nCEffCylinderCount + 7) = 1065353216;
    *(&g_PAL3.m_nCEffCylinderCount + 8) = 0;
    result = atexit(nullsub_84);
  }
  if ( (*(_BYTE *)(&g_PAL3.m_nCEffCylinderCount + 13) & 4) == 0 )
  {
    *(&g_PAL3.m_nCEffCylinderCount + 2) = 0;
    *((_BYTE *)&g_PAL3.m_nCEffCylinderCount + 52) |= 4u;
    *(&g_PAL3.m_nCEffCylinderCount + 3) = 0;
    *(&g_PAL3.m_nCEffCylinderCount + 4) = 1065353216;
    result = atexit(nullsub_83);
  }
  LOBYTE(result) = this->m_bIdle;
  if ( !(_BYTE)result )
  {
    LOBYTE(result) = this->m_bVisible;
    if ( (_BYTE)result )
    {
      ((gbVertPoolMgr *)this->m_pEM->m_pDisplay->pVertPoolMgr)->GetDynVertBuf(0x15u);
      m_bAdditiveBlend = this->m_bAdditiveBlend;
      if ( this->m_bNoZTest )
      {
        v6 = m_bAdditiveBlend == 0;
        m_pEM = this->m_pEM;
        if ( v6 )
          m_pAlphaBlendNoZ = m_pEM->m_pAlphaBlendNoZ;
        else
          m_pAlphaBlendNoZ = m_pEM->m_pAdditiveBlendNoZ;
      }
      else
      {
        v6 = m_bAdditiveBlend == 0;
        m_pEM = this->m_pEM;
        if ( v6 )
          m_pAlphaBlendNoZ = m_pEM->m_pAlphaBlend;
        else
          m_pAlphaBlendNoZ = m_pEM->m_pAdditiveBlend;
      }
      v9 = m_pEM->m_pDisplay->pMatrixStack[1];
      ((gbMatrixStack *)v9)->Push();
      v10 = this->m_vecOffsetPos.x + this->m_vecPos.x;
      retaddr = v10;
      ((gbMatrixStack *)v9)->Translate((gbVec3D *)&retaddr);
      ((gbMatrixStack *)v9)->Scale(this->m_fXSize,   1.0,   this->m_fZSize);
      ((gbMatrixStack *)v9)->Rotate(this->m_vecRot.x, (gbVec3D *)(&g_PAL3.m_nCEffCylinderCount + 10));
      ((gbMatrixStack *)v9)->Rotate(this->m_vecRot.y, (gbVec3D *)&g_PAL3.m_nCEffCylinderCount + 2);
      ((gbMatrixStack *)v9)->Rotate(this->m_vecRot.z, (gbVec3D *)(&g_PAL3.m_nCEffCylinderCount + 2));
      ((gbDynVertBuf *)this->m_pGeomQuad)->RenderGeomQuad(this->m_nQuad, m_pAlphaBlendNoZ, this->m_pTextureArray);
      ((gbMatrixStack *)v9)->Pop();
    }
  }
  return result;
}

// 0x004C9ED0
int CEffGrid::slot_5(int a2)
{
  CEffGrid *v2; // edi
  double v3; // st7
  CEffObj *v4; // esi
  __int16 v5; // fps
  double v6; // st7
  bool v7; // c0
  char v8; // c2
  bool v9; // c3
  int result; // eax
  char *v11; // ebx
  int v12; // edx
  int v13; // edi
  int v14; // ecx
  int v15; // eax
  int v16; // edx
  bool v17; // cc
  int v18; // esi
  int v19; // edx
  int m_nXDivision; // ecx
  double eu; // st7
  int m_nZDivision; // edx
  double v23; // st7
  int v24; // edx
  int v25; // eax
  int v26; // [esp+0x0] [ebp-0x14]
  float v27; // [esp+0x4] [ebp-0x10]
  float v29; // [esp+0x8] [ebp-0xC]
  int v30; // [esp+0xC] [ebp-0x8]
  float v31; // [esp+0xC] [ebp-0x8]
  int v32; // [esp+0x10] [ebp-0x4]
  float v33; // [esp+0x10] [ebp-0x4]
  int a2a; // [esp+0x1C] [ebp+0x8]
  int a2b; // [esp+0x1C] [ebp+0x8]
HIWORD(result) = HIWORD(a2);
  v3 = *(float *)&a2 - *((float *)this + 4);
  v4 = this + 1;
  *((float *)this + 4) = *(float *)&a2;
  *((float *)this + 5) = v3;
  v6 = *((float *)this + 5);
  v7 = v6 < 0.0;
  v8 = 0;
  v9 = v6 == 0.0;
  LOWORD(result) = v5;
  if ( v6 > 0.0 )
  {
    a2a = 0;
    if ( *((int *)this + 10) > 0 )
    {
      v32 = 0;
      while ( 1 )
      {
// [VFTABLE] v11 = (char *)v4[1].__vftable + v32;
        if ( v11[148] )
        {
          if ( *((_DWORD *)v11 + 3) == 3 )
          {
            v12 = 0;
            v30 = 0;
            if ( *(int *)&v4[2].m_bIdle > 0 )
              break;
          }
        }
LABEL_29:
        v17 = ++a2a < (int)v4[2].m_pEM;
        v32 += 152;
        if ( !v17 )
          goto LABEL_30;
      }
      v13 = 0;
      while ( 1 )
      {
        v14 = v13 + *(_DWORD *)v11;
        if ( !*(_BYTE *)(v14 + 64) || v13 > 0 && *(_DWORD *)(v14 - 64) == 2 )
        {
LABEL_28:
goto LABEL_29;
        }
        switch ( *(_DWORD *)(v14 + 8) )
        {
          case 2:
            if ( v13 > 0 )
            {
              if ( *(float *)(v14 + 20) >= 0.0 )
              {
                if ( *(float *)&v4->m_pEM - *(float *)(v14 - 56) > *(float *)(v14 + 20) )
                {
                  ((CCBStage *)v4)->GetTaskParam(a2a, v12);
                  v4[1].m_pEM = (CEffMgr *)a2a;
                  *(_DWORD *)&v4[1].m_bIdle = v30;
                  goto LABEL_24;
                }
              }
              else if ( *(_DWORD *)(v14 - 64) == 4 )
              {
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v4[1].__vftable + v32) + v13 + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v4[1].__vftable + v32) + v13 + 16) = v4->m_pEM;
LABEL_21:
                *(_DWORD *)&v4[1].m_bIdle = v12;
                v4[1].m_pEM = (CEffMgr *)a2a;
LABEL_24:
// [VFTABLE] (*((void ( **)(CEffObj *, _DWORD, _DWORD, _DWORD))v4->__vftable + 1))(
// [VFTABLE]   v4,
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v11 + v13),
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v11 + v13 + 4),
// [VFTABLE]   0);
              }
            }
            break;
          case 3:
            goto LABEL_21;
          case 4:
            if ( ((CCBStage *)v4)->SetTaskState(a2a) )
            {
              v15 = *((_DWORD *)v11 + 1);
              *((_DWORD *)v11 + 3) = 4;
              v16 = 9 * v15;
              LOBYTE(v15) = v11[149];
              *((_DWORD *)v11 + 5) = *(_DWORD *)(*(_DWORD *)v11 + 8 * v16 - 12);
              if ( (_BYTE)v15 == 1 )
              {
                ((CEffgbParticle *)v4)->Init(a2a);
                goto LABEL_28;
              }
            }
            break;
        }
        v12 = v30 + 1;
        v13 += 72;
        if ( ++v30 >= *(_DWORD *)&v4[2].m_bIdle )
          goto LABEL_28;
      }
    }
LABEL_30:
    result = *((_DWORD *)v2 + 9);
    if ( result <= 0 )
      this->m_bIdle = 1;
    LOBYTE(result) = this->m_bIdle;
    if ( !(_BYTE)result )
    {
      this->m_fCurFrame = this->m_fFramePerSec * *((float *)v2 + 5) + this->m_fCurFrame;
      if ( (g_bEffSystemFlags & 1) == 0 )
      {
        g_bEffSystemFlags |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      v18 = 0;
      v19 = (int)abs32((int)this->m_fCurFrame) % (unsigned __int8)this->m_byMaxFrame;
      m_nXDivision = this->m_nXDivision;
      eu = this->m_DefaultUVSet[v19].eu;
      result = (int)v2 + 16 * v19;
      m_nZDivision = this->m_nZDivision;
      v26 = result;
      v33 = (eu - *(float *)(result + 184)) * (1.0 / (double)m_nXDivision);
      a2b = 0;
      v29 = (*(float *)(result + 196) - *(float *)(result + 188)) * (1.0 / (double)m_nZDivision);
      if ( m_nZDivision > 0 )
      {
        do
        {
          v23 = *(float *)(result + 184);
          v24 = 0;
          v31 = (double)a2b * v29 + *(float *)(result + 188);
          if ( m_nXDivision > 0 )
          {
            v25 = v18;
            do
            {
              ++v18;
              this->m_pGeomQuad[v25].su = v23;
              v23 = v23 + v33;
              ++v25;
              ++v24;
              this->m_pGeomQuad[v25 - 1].eu = v23;
              this->m_pGeomQuad[v25 - 1].sv = v31;
              v27 = v29 + v31;
              this->m_pGeomQuad[v25 - 1].ev = v27;
              this->m_pGeomQuad[v25 - 1].color = this->m_dwStartColor;
              m_nXDivision = this->m_nXDivision;
            }
            while ( v24 < m_nXDivision );
            result = v26;
          }
          ++a2b;
        }
        while ( a2b < this->m_nZDivision );
      }
    }
  }
  return result;
}

// 0x004CA1D0
int CEffGrid::RenderEffectPass(int a2)
{
  int result; // eax
  CEffObj *v3; // ebx
  int v4; // ecx
  int v5; // edx
  char *vftable; // esi
  int v7; // ebp
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v3 = this + 1;
  v4 = *((_DWORD *)this + 10);
  v5 = 0;
  if ( v4 > 0 )
  {
// [VFTABLE] vftable = (char *)v3[1].__vftable;
    result = (int)(vftable + 148);
    while ( *(_BYTE *)result )
    {
      ++v5;
      result += 152;
      if ( v5 >= v4 )
        return result;
    }
    v7 = 152 * v5;
    *(_DWORD *)&vftable[v7 + 12] = 2;
// [VFTABLE] *((_BYTE *)v3[1].__vftable + v7 + 148) = 1;
// [VFTABLE] *((_BYTE *)v3[1].__vftable + v7 + 149) = 1;
    v8 = ++*(&g_PAL3.m_nCEffCylinderCount + 14);
    if ( !*(&g_PAL3.m_nCEffCylinderCount + 14) || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      *(&g_PAL3.m_nCEffCylinderCount + 14) = 1;
    }
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 16) = v8;
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 4) = 0;
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 8) = 0;
// [VFTABLE] result = (int)v3[1].__vftable;
    *(_DWORD *)(result + v7 + 20) = 0;
    if ( a2 )
    {
// [VFTABLE] qmemcpy((char *)v3[1].__vftable + v7 + 24, (const void *)a2, 0x7Cu);
    }
    else
    {
      result = 0;
// [VFTABLE] memset((char *)v3[1].__vftable + v7 + 24, 0, 0x7Cu);
    }
// [VFTABLE] ++v3[2].__vftable;
    if ( v5 != -1 )
    {
      v9 = *(_DWORD *)&v3[2].m_bIdle;
      v10 = 0;
      if ( v9 > 0 )
      {
// [VFTABLE] v11 = *((_DWORD *)v3[1].__vftable + 38 * v5);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++*(&g_PAL3.m_nCEffCylinderCount + 14);
        if ( !*(&g_PAL3.m_nCEffCylinderCount + 14) || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          *(&g_PAL3.m_nCEffCylinderCount + 14) = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v3[1].__vftable + v7 + 4);
      }
LABEL_22:
      v15 = *(_DWORD *)&v3[2].m_bIdle;
      v16 = 0;
      if ( v15 > 0 )
      {
// [VFTABLE] v17 = *((_DWORD *)v3[1].__vftable + 38 * v5);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++*(&g_PAL3.m_nCEffCylinderCount + 14);
        if ( !*(&g_PAL3.m_nCEffCylinderCount + 14) || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          *(&g_PAL3.m_nCEffCylinderCount + 14) = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v3[1].__vftable + v7 + 4);
      }
LABEL_31:
      sub_4CB130(v5, CEffCylinder::UpdateGeometry, 0, 0, *(_DWORD *)(a2 + 72), *(_DWORD *)(a2 + 76));
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 12) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v3[1].__vftable + v7) + 8) = 3;
// [VFTABLE] result = *(_DWORD *)((char *)v3[1].__vftable + v7);
      *(_DWORD *)(result + 16) = v3->m_pEM;
    }
  }
  return result;
}

// 0x004CA9A0
const char * CEffGrid::GetEditorObjDescription(int nIndex)
{
  const char *result; // eax

  switch ( nIndex )
  {
    case 0:
      result = (const char *)dword_5D5050;
      break;
    case 1:
      result = (const char *)dword_5D4E40;
      break;
    case 2:
      result = (const char *)dword_5D4E38;
      break;
    case 3:
      result = (const char *)dword_5D4E30;
      break;
    case 4:
      result = (const char *)dword_5D4E24;
      break;
    case 5:
      result = (const char *)dword_5D5048;
      break;
    case 6:
      result = (const char *)dword_5D5040;
      break;
    case 7:
      result = (const char *)dword_5D5038;
      break;
    case 8:
      result = (const char *)dword_5D4E00;
      break;
    case 9:
      result = (const char *)&g_EffEditorState;
      break;
    case 10:
      result = (const char *)dword_5D51B0;
      break;
    case 12:
      result = (const char *)dword_5D4DD4;
      break;
    case 13:
      result = (const char *)dword_5D4DCC;
      break;
    case 14:
      result = (const char *)dword_5D4DC4;
      break;
    case 15:
      result = (const char *)dword_5D4DB8;
      break;
    case 16:
      result = (const char *)dword_5D4DAC;
      break;
    case 17:
      result = (const char *)dword_5D5014;
      break;
    case 18:
      result = (const char *)dword_5D5008;
      break;
    case 19:
      result = (const char *)dword_5D4FFC;
      break;
    case 20:
      result = (const char *)&g_pszEditorDesc;
      break;
    default:
      result = (const char *)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004CAAB0
int CEffGrid::DispatchByType(int a2)
{
  int result; // eax

  switch ( a2 )
  {
    case 0:
      result = (int)dword_5D52A8;
      break;
    case 1:
      result = (int)dword_5D5210;
      break;
    case 2:
      result = (int)dword_5D5204;
      break;
    case 3:
      result = (int)dword_5D51F8;
      break;
    case 4:
      result = (int)dword_5D529C;
      break;
    case 5:
      result = (int)dword_5D5290;
      break;
    case 6:
      result = (int)dword_5D5284;
      break;
    case 7:
      result = (int)dword_5D5278;
      break;
    default:
      result = (int)&g_EffCylinderEditorData;
      break;
  }
  return result;
}
