#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Render/TextureLib.h"

// Forward declarations for unnamed functions
int sub_53F5C0(...);

// Unnamed globals (extern)
extern CHAR asc_5D41EC[];
extern TextureLibDataBase stru_1894B78;

// 0x004A6930
char TextureLib::LoadTexture(char *pszPath)
{
  char *m_Image; // esi

  m_Image = this->m_Image;
  ((gbImage2D *)this->m_Image)->Release();
  ((gbImage2D *)m_Image)->LoadImageFile(pszPath, 0);
  return 1;
}

// 0x004A6960
gbTexture * TextureLib::CreateFromFile()
{
  TextureLib *v1; // ebx
  int m_nStride; // ecx
  int m_nDataSize; // esi
  int m_nBPP; // eax
  _BYTE *v6; // eax
  int v7; // edi
  int v8; // edx
  int v9; // ebp
  int v10; // ebp
  int v11; // esi
  int v12; // ebx
  int v13; // ecx
  bool v14; // zf
  int m_nTexWidth; // edi
  float m_fTexParam; // esi
  int v17; // edx
  int v18; // ebp
  int v19; // esi
  int v20; // ecx
  gbTexture *m_pResultTex; // ecx
  gbTexture *v22; // ebx
  char *m_nDataEnd; // [esp-0x18] [ebp-0x6C]
  int v24; // [esp+0x4] [ebp-0x50]
  int v25; // [esp+0x4] [ebp-0x50]
  _BYTE *Block; // [esp+0x8] [ebp-0x4C]
  int v27; // [esp+0xC] [ebp-0x48]
  int v28; // [esp+0xC] [ebp-0x48]
  int m_nDataOffset; // [esp+0x14] [ebp-0x40]
  int v31; // [esp+0x14] [ebp-0x40]
  int v32; // [esp+0x18] [ebp-0x3C]
  int v33; // [esp+0x18] [ebp-0x3C]
  int v34; // [esp+0x1C] [ebp-0x38]
  int m_nTexHeight; // [esp+0x1C] [ebp-0x38]
  int p_DWORD; // [esp+0x20] [ebp-0x34] BYREF
  _BYTE v37[4]; // [esp+0x24] [ebp-0x30]
  _BYTE v38[8]; // [esp+0x28] [ebp-0x2C]
  int nVal; // [esp+0x30] [ebp-0x24] BYREF
  char v40; // [esp+0x34] [ebp-0x20]
  Array v41; // [esp+0x38] [ebp-0x1C] BYREF
  int v42; // [esp+0x50] [ebp-0x4]
  int v43; // [esp+0x58] [ebp+0x4]
  int v44; // [esp+0x5C] [ebp+0x8]
  int v45; // [esp+0x60] [ebp+0xC]
  int v46; // [esp+0x64] [ebp+0x10]
  int v47; // [esp+0x68] [ebp+0x14]
  int v48; // [esp+0x68] [ebp+0x14]
  int v49; // [esp+0x6C] [ebp+0x18]
  int v50; // [esp+0x70] [ebp+0x1C]
  int v51; // [esp+0x74] [ebp+0x20]
  char v52; // [esp+0x78] [ebp+0x24]
  int v53; // [esp+0x78] [ebp+0x24]
  int v54; // [esp+0x78] [ebp+0x24]
if ( v52 )
    return this->m_pResultTex;
  m_nStride = this->m_nStride;
  m_nDataSize = this->m_nDataSize;
  LOBYTE(v41.m_pDataStart) = 0;
  memset(&v41.m_nSize, 0, 12);
  v40 = 0;
  m_nBPP = this->m_nBPP;
  v42 = 0;
  nVal = 0;
  v6 = operator new(m_nStride * m_nDataSize * (m_nBPP / 8));
  v7 = this->m_nBPP;
  v8 = this->m_nStride;
  m_nDataOffset = this->m_nDataOffset;
  Block = v6;
  v53 = 0;
  v32 = v7;
  if ( v49 < v51 )
  {
    v9 = v8 * v7;
    v34 = v8 * v7;
    v24 = v7 * (v47 + v8 * v49);
    v27 = v51 - v49;
    do
    {
      if ( v47 < v50 )
      {
        v10 = v24;
        v11 = v7 / 8;
        v12 = v50 - v47;
        do
        {
          v13 = 0;
          if ( v11 > 0 )
          {
            do
            {
              v6[v53 + v13] = *(_BYTE *)(m_nDataOffset + v10 / 8 + v13);
              ++v13;
            }
            while ( v13 < v11 );
            v7 = v32;
          }
          v10 += v7;
          --v12;
          v53 += v11;
        }
        while ( v12 );
        v9 = v34;
}
      v14 = v27 == 1;
      v24 += v9;
      --v27;
    }
    while ( !v14 );
  }
  m_nTexWidth = this->m_nTexWidth;
  m_fTexParam = this->m_fTexParam;
  v54 = 0;
  m_nTexHeight = this->m_nTexHeight;
  v33 = m_nTexWidth;
  if ( v44 < v46 )
  {
    v17 = LODWORD(m_fTexParam) * m_nTexWidth;
    v31 = LODWORD(m_fTexParam) * m_nTexWidth;
    v48 = m_nTexWidth * (v43 + LODWORD(m_fTexParam) * v44);
    v25 = v46 - v44;
    do
    {
      if ( v43 < v45 )
      {
        v18 = v48;
        v19 = m_nTexWidth / 8;
        v28 = v45 - v43;
        do
        {
          v37[0] = 0;
          v38[0] = 0;
          v38[4] = 0;
          ++nVal;
          v20 = 0;
          p_DWORD = v18 / 8;
          if ( v19 > 0 )
          {
            do
            {
              v38[v20] = *(_BYTE *)(m_nTexHeight + v18 / 8 + v20);
              v37[v20] = Block[v54 + v20];
              ++v20;
            }
            while ( v20 < v19 );
m_nTexWidth = v33;
          }
          ((Array *)&v41)->InsertBlocks(v41.m_pData, 1u, &p_DWORD);
          v18 += m_nTexWidth;
          v14 = v28 == 1;
          v54 += v19;
          --v28;
        }
        while ( !v14 );
        v17 = v31;
      }
      v14 = v25 == 1;
      v48 += v17;
      --v25;
    }
    while ( !v14 );
  }
  operator delete(Block);
  m_nDataEnd = (char *)this->m_nDataEnd;
  v40 = 0;
  ((UITitle_YXXX *)&this->m_pPalette)->CreateTitle(m_nDataEnd, 1u, (int)&nVal);
  m_pResultTex = this->m_pResultTex;
  this->m_bLoaded = 1;
  ((gbTexture *)m_pResultTex)->UpdateTexture((gbImage2D *)(&this->m_pResultTex + 1));
  v22 = this->m_pResultTex;
  operator delete((void *)v41.m_nSize);
  return v22;
}

// 0x004A6CA0
gbTexture * TextureLib::CreateFromMemory(_BYTE *pData, int nSize, char nFormat)
{
  TextureLib *v4; // edi
  int m_nDataStart; // eax
  int v6; // edx
  int m_nTexHeight; // esi
  int v9; // ebp
  int v10; // ebp
  int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // edi
  int v15; // ecx
  int v16; // edi
  int v17; // ecx
  int v18; // edi
  int v19; // ecx
  int v20; // edi
  bool v21; // cc
  bool v22; // zf
  int v25; // [esp+0x8] [ebp-0x14]
  int v26; // [esp+0xC] [ebp-0x10]
  int v27; // [esp+0x10] [ebp-0xC]
  int v28; // [esp+0x14] [ebp-0x8]
  int m_nTexWidth; // [esp+0x18] [ebp-0x4]
  _BYTE *pDataa; // [esp+0x20] [ebp+0x4]
  int nSizea; // [esp+0x24] [ebp+0x8]
m_nDataStart = this->m_nDataStart;
  if ( !m_nDataStart )
    return this->m_pResultTex;
  v6 = (this->m_nDataEnd - m_nDataStart) / 24;
  if ( v6 <= 0 )
    return this->m_pResultTex;
  *pData = this->m_bLoaded;
  if ( !this->m_bLoaded )
    return this->m_pResultTex;
  m_nTexHeight = this->m_nTexHeight;
  m_nTexWidth = this->m_nTexWidth;
  v25 = v6;
  v9 = 0;
  v27 = 0;
  v28 = v6;
  do
  {
    v10 = this->m_nDataStart + v9;
    if ( *(_BYTE *)(v10 + 4) )
    {
      --v25;
      goto LABEL_52;
    }
    v26 = 0;
    pDataa = (_BYTE *)(*(_DWORD *)v10 - 1);
    if ( *(int *)v10 > 0 )
    {
      nSizea = 0;
      while ( 1 )
      {
        v11 = *(_DWORD *)(v10 + 12) + nSizea;
        if ( !*(_BYTE *)(v11 + 12) )
          break;
        --pDataa;
LABEL_50:
        v21 = ++v26 < *(_DWORD *)v10;
        nSizea += 16;
        if ( !v21 )
          goto LABEL_51;
      }
      v12 = *(_DWORD *)v11;
      if ( nFormat )
      {
        *(_BYTE *)(v12 + m_nTexHeight) = *(_BYTE *)(v11 + 4);
        *(_BYTE *)(v12 + m_nTexHeight + 1) = *(_BYTE *)(v11 + 5);
        LOBYTE(v13) = *(_BYTE *)(v11 + 6);
        goto LABEL_31;
      }
      v14 = *(unsigned __int8 *)(v11 + 4);
      v15 = *(unsigned __int8 *)(v12 + m_nTexHeight);
      if ( v15 <= v14 )
      {
        if ( v15 >= v14 || (v15 += nSize, v15 < v14) )
        {
LABEL_19:
          *(_BYTE *)(v12 + m_nTexHeight) = v15;
          v16 = *(unsigned __int8 *)(v11 + 5);
          v17 = *(unsigned __int8 *)(v12 + m_nTexHeight + 1);
          if ( v17 <= v16 )
          {
            if ( v17 >= v16 || (v17 += nSize, v17 < v16) )
            {
LABEL_25:
              *(_BYTE *)(v12 + m_nTexHeight + 1) = v17;
              v18 = *(unsigned __int8 *)(v11 + 6);
              v13 = *(unsigned __int8 *)(v12 + m_nTexHeight + 2);
              if ( v13 <= v18 )
              {
                if ( v13 >= v18 || (v13 += nSize, v13 < v18) )
                {
LABEL_31:
                  *(_BYTE *)(v12 + m_nTexHeight + 2) = v13;
                  if ( m_nTexWidth != 32 )
                  {
                    if ( *(_BYTE *)(v12 + m_nTexHeight) != *(_BYTE *)(v11 + 4)
                      || *(_BYTE *)(v12 + m_nTexHeight + 1) != *(_BYTE *)(v11 + 5)
                      || *(_BYTE *)(v12 + m_nTexHeight + 2) != *(_BYTE *)(v11 + 6) )
                    {
                      goto LABEL_49;
                    }
LABEL_48:
                    --pDataa;
                    *(_BYTE *)(*(_DWORD *)(v10 + 12) + nSizea + 12) = 1;
LABEL_49:
goto LABEL_50;
                  }
                  if ( nFormat )
                  {
                    LOBYTE(v19) = *(_BYTE *)(v11 + 7);
                    goto LABEL_40;
                  }
                  v20 = *(unsigned __int8 *)(v11 + 7);
                  v19 = *(unsigned __int8 *)(v12 + m_nTexHeight + 3);
                  if ( v19 <= v20 )
                  {
                    if ( v19 >= v20 || (v19 += nSize, v19 < v20) )
                    {
LABEL_40:
                      *(_BYTE *)(v12 + m_nTexHeight + 3) = v19;
                      if ( *(_BYTE *)(v12 + m_nTexHeight) != *(_BYTE *)(v11 + 4)
                        || *(_BYTE *)(v12 + m_nTexHeight + 1) != *(_BYTE *)(v11 + 5)
                        || *(_BYTE *)(v12 + m_nTexHeight + 2) != *(_BYTE *)(v11 + 6)
                        || *(_BYTE *)(v12 + m_nTexHeight + 3) != *(_BYTE *)(v11 + 7) )
                      {
                        goto LABEL_49;
                      }
                      goto LABEL_48;
                    }
                  }
                  else
                  {
                    v19 -= nSize;
                    if ( v19 > v20 )
                      goto LABEL_40;
                  }
                  LOBYTE(v19) = *(_BYTE *)(v11 + 7);
                  goto LABEL_40;
                }
              }
              else
              {
                v13 -= nSize;
                if ( v13 > v18 )
                  goto LABEL_31;
              }
              LOBYTE(v13) = *(_BYTE *)(v11 + 6);
              goto LABEL_31;
            }
          }
          else
          {
            v17 -= nSize;
            if ( v17 > v16 )
              goto LABEL_25;
          }
          LOBYTE(v17) = *(_BYTE *)(v11 + 5);
          goto LABEL_25;
        }
      }
      else
      {
        v15 -= nSize;
        if ( v15 > v14 )
          goto LABEL_19;
      }
      LOBYTE(v15) = *(_BYTE *)(v11 + 4);
      goto LABEL_19;
    }
LABEL_51:
    *(_BYTE *)(v10 + 4) = (int)pDataa <= 0;
LABEL_52:
    v9 = v27 + 24;
    v22 = v28 == 1;
    v27 += 24;
    --v28;
  }
  while ( !v22 );
  ((gbTexture *)this->m_pResultTex)->UpdateTexture((gbImage2D *)(&this->m_pResultTex + 1));
  if ( v25 <= 0 )
    this->m_bLoaded = 0;
  return this->m_pResultTex;
}

// 0x0053F500
int TextureLib::CheckEndKey(LPCSTR lpString1, LPCSTR lpString2)
{
  int i; // ebx

  for ( i = 0; ; ++i )
  {
    if ( !lstrcmpA(lpString1, "End_Key") )
      return -1;
    if ( !lstrcmpA(lpString1, lpString2) )
      break;
    lpString1 += 32;
  }
  return i;
}

// 0x0053F550
void TextureLib::ClearAndJump()
{

  JUMPOUT(0x53F570);
}

// 0x0053F560
int * TextureLib::ClearGlobalVars()
{
  nearby_53f4c0(&stru_1894B78);
  ((TextureLibDataBase *)&stru_1894B78)->_realNum = 0;
  ((TextureLibDataBase *)&stru_1894B78)->_isLoadTLI = 0;
  ((TextureLibDataBase *)&stru_1894B78)->_libfolder[0] = 0;
  ((TextureLibDataBase *)&stru_1894B78)->m_pData = 0;
  return (int *)&stru_1894B78;
}

// 0x0053F5C0
int TextureLib::sub_53F5C0(void *Block, char a3)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return (int)this;
}

// 0x0053F5E0
void TextureLib::FreeTexture()
{
  if ( this->m_pTexture )
  {
    operator delete(this->m_pTexture);
    this->m_pTexture = 0;
  }
  nearby_53f4f0(this);
}

// 0x0053F610
int TextureLib::ParseConfigFile(char *String)
{
  int v2; // ebx
  char *v3; // eax
  char *v4; // esi

  v2 = 0;
  v3 = strtok(g_ScriptSystemData.m_String, Delimiter);
  if ( !lstrcmpA(v3, "#endfile") )
    return 0;
  do
  {
    v4 = strtok(0, Delimiter);
    if ( !lstrcmpA(v4, "#End") )
      ++v2;
  }
  while ( lstrcmpA(v4, "#endfile") );
  return v2;
}

// 0x0053F680
char TextureLib::AddEntryFromConfig(char *lpString2, char *Delimiter)
{
  int v5; // eax
  char *v6; // eax
  char *v7; // ebx
  char *v8; // eax
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  char *v12; // eax
  char *v13; // eax
  char *v14; // eax
  int *v16; // [esp+0x0] [ebp-0x10]

  do
  {
    v5 = this->CheckEndKey("t_name", lpString2);
    if ( v5 == -1 )
      return 0;
    switch ( v5 )
    {
      case 0:
        v6 = strtok(0, Delimiter);
        lstrcpyA(&this->m_pTexture[1088 * this->m_szText], v6);
        break;
      case 1:
        v7 = strtok(0, Delimiter);
        lstrcpyA(&this->m_pTexture[1088 * this->m_szText + 512], (LPCSTR)&this->m_szPathBuf);
        lstrcatA(&this->m_pTexture[1088 * this->m_szText + 512], v7);
        break;
      case 2:
        v8 = strtok(0, Delimiter);
        *(_DWORD *)&this->m_pTexture[1088 * this->m_szText + 1024] = atoi(v8);
        break;
      case 3:
        v9 = strtok(0, Delimiter);
        *(_DWORD *)&this->m_pTexture[1088 * this->m_szText + 1028] = atoi(v9);
        break;
      case 4:
        v10 = strtok(0, Delimiter);
        *(_DWORD *)&this->m_pTexture[1088 * this->m_szText + 1032] = atoi(v10);
        break;
      case 5:
        v11 = strtok(0, Delimiter);
        *(_DWORD *)&this->m_pTexture[1088 * this->m_szText + 1036] = atoi(v11);
        break;
      case 6:
        v12 = strtok(0, Delimiter);
        *(_DWORD *)&this->m_pTexture[1088 * this->m_szText + 1040] = atoi(v12);
        break;
      case 7:
        v13 = strtok(0, Delimiter);
        *(_DWORD *)&this->m_pTexture[1088 * this->m_szText + 1044] = atoi(v13);
        break;
      case 8:
        v14 = strtok(0, Delimiter);
        *(_DWORD *)&this->m_pTexture[1088 * this->m_szText + 1080] = atoi(v14);
        break;
      default:
        break;
    }
    lpString2 = strtok(0, Delimiter);
  }
  while ( lstrcmpA(lpString2, "#End") );
  ((CScreenMode *)&this->m_pTexture[1088 * this->m_szText])->UpdateRenderState(v16);
  ++this->m_szText;
  return 1;
}

// 0x0053F920
char * TextureLib::SetPath(char *path)
{
  char *result; // eax

  result = (char *)lstrlenA(path);
  if ( (int)result > 0 )
  {
    lstrcpyA((LPSTR)&this->m_szPathBuf, path);
    result = (char *)lstrlenA((LPCSTR)&this->m_szPathBuf);
    if ( *((_BYTE *)&this->m_pResultTex + (_DWORD)result + 11) != 92 )
      return lstrcatA((LPSTR)&this->m_szPathBuf, asc_5D41EC);
  }
  return result;
}
