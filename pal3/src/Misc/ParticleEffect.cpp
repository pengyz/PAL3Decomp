#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ParticleEffect.h"

// Forward declarations for unnamed functions
int sub_4BA150(...);
int sub_4BA270(...);
int sub_4BA3D0(...);
int sub_4BA770(...);
int sub_4BACA0(...);
void sub_4BAE60(int _this, gbVFile *pFile); // from annotations

// Unnamed globals (extern)
extern int dword_5D41AC;

// 0x004BA510
int ParticleEffect::LoadSceneFile(const char *pszName, const char *pszName2)
{
  gbVFile *v4; // ebx
  int result; // eax
  int v6; // edi
  int v7; // esi
  sg_emitter *emitter; // edi
  int v9; // esi
  RenderTarget *econtrol; // edi
  char v11[8]; // [esp+0x6C] [ebp-0x8] BYREF
  sg_particle *pszNamea; // [esp+0x78] [ebp+0x4]

  v4 = ((gbVFileSystem *)g_pVFileSys)->OpenFile(pszName, 0x201u);
  if ( v4 )
  {
    sub_4BA3D0(this);
    strcpy(this->name, pszName);
    ((gbVFileSystem *)g_pVFileSys)->Read(v11, 6u, v4);
    if ( strcmp(v11, "sgpar") )
      ((gbVFileSystem *)g_pVFileSys)->CloseFile(v4);
    ((gbVFileSystem *)g_pVFileSys)->Read(&g_nFileVersion, 4u, v4);
    if ( g_nFileVersion == dword_5D41AC )
    {
      ((gbVFileSystem *)g_pVFileSys)->Read(&this->maxparticle, 4u, v4);
      ((gbVFileSystem *)g_pVFileSys)->Read(&this->emittedto, 4u, v4);
      ((gbVFileSystem *)g_pVFileSys)->Read(&this->npwmr, 4u, v4);
      if ( g_nFileVersion > 0x10000 )
        ((gbVFileSystem *)g_pVFileSys)->Read(&this->m_fMultisize, 4u, v4);
      ((gbVFileSystem *)g_pVFileSys)->Read(&this->particle_num, 4u, v4);
      ((gbVFileSystem *)g_pVFileSys)->Read(&this->emitter_num, 4u, v4);
      ((gbVFileSystem *)g_pVFileSys)->Read(&this->emission_controlnum, 4u, v4);
      v6 = 0;
      if ( this->particle_num > 0 )
      {
        pszNamea = this->particle;
        do
        {
          sub_4BACA0(v4);
          ++v6;
          ++pszNamea;
        }
        while ( v6 < this->particle_num );
      }
      v7 = 0;
      if ( this->emitter_num > 0 )
      {
        emitter = this->emitter;
        do
        {
          sub_4BAE60(v4);
          ++v7;
          ++emitter;
        }
        while ( v7 < this->emitter_num );
      }
      v9 = 0;
      if ( this->emission_controlnum > 0 )
      {
        econtrol = (RenderTarget *)this->econtrol;
        do
        {
          ((RenderTarget *)econtrol)->ReadVFile(v4);
          ++v9;
          econtrol = (RenderTarget *)((char *)econtrol + 36952);
        }
        while ( v9 < this->emission_controlnum );
      }
      ((gbVFileSystem *)g_pVFileSys)->CloseFile(v4);
      result = ((CEffect *)this)->SetRenderParam(LODWORD(this->m_fMultisize));
      LOBYTE(result) = 1;
    }
    else
    {
      ((gbVFileSystem *)g_pVFileSys)->CloseFile(v4);
      result = MessageBoxA(0, "Not supported file version", "Info", 0);
      LOBYTE(result) = 0;
    }
  }
  else
  {
    result = MessageBoxA(hWnd, Text, Caption, 0);
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004BC760
ParticleEffect * ParticleEffect::Reset()
{
  sub_4BA270(&this->name[4]);
  this->m_pTexture[0] = 0;
  this->m_pTexture[1] = 0;
  this->m_pTexture[2] = 0;
  this->m_pTexture[3] = 0;
  this->deltatime = 0.0;
  return this;
}

// 0x004BC7E0
int ParticleEffect::SetDeltaTime(int nVal)
{
  LODWORD(this->deltatime) = nVal;
  return nVal;
}

// 0x004BC7F0
int ParticleEffect::UpdateParticles(float fVal, int nVal, int nVal2, int nVal3)
{
  int npwmr; // eax
  int result; // eax
  int v8; // esi
  char *v9; // edi
  int v10; // [esp+0x8] [ebp-0xC] BYREF
  int v11; // [esp+0xC] [ebp-0x8]
  int v12; // [esp+0x10] [ebp-0x4]
  float fVala; // [esp+0x18] [ebp+0x4]

  v10 = nVal;
  npwmr = this->npwmr;
  v11 = nVal2;
  v12 = nVal3;
  if ( npwmr == 1 )
  {
    v10 = 0;
    v11 = 0;
    v12 = 0;
  }
  result = this->particle_num;
  v8 = 0;
  fVala = fVal * *(float *)&this->maxfps;
  if ( result > 0 )
  {
    v9 = &this->econtrol[0].name[4];
    do
    {
      sub_4BA150(fVala, (int)&v10);
      result = this->particle_num;
      ++v8;
      v9 += 36952;
    }
    while ( v8 < result );
  }
  return result;
}

// 0x004BD520
char ParticleEffect::LoadTextures(const char *pszName, const char *pszName2)
{
  int v4; // ebp
  int v6; // edi
  float *p_elapsetime; // esi
  gbTexture_D3D **m_pTexture; // esi
  const char *v9; // edi
  gbTexture *v10; // eax
  const char *v11; // [esp+0x0] [ebp-0x124]
  OpenBaseFile v12; // [esp+0x10] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x14] [ebp-0x110] BYREF
  int v14; // [esp+0x120] [ebp-0x4]

  v4 = 0;
  v14 = 0;
  strcpy(g_szParticleTexName, pszName);
  sprintf(Buffer, "%s\\%s", g_szParticleTexName, pszName2);
  if ( (unsigned __int8)((ParticleEffect *)&this->name[4])->LoadSceneFile(Buffer, v11) )
  {
    v6 = 0;
    if ( this->particle_num > 0 )
    {
      p_elapsetime = &this->econtrol[0].elapsetime;
      do
      {
        sub_4BA770(
          &this->particle[*((_DWORD *)p_elapsetime - 1)].particle_name[4],
          &this->emitter[*(_DWORD *)p_elapsetime].name[4]);
        ++v6;
        p_elapsetime += 9238;
      }
      while ( v6 < this->particle_num );
    }
    if ( this->emitter_num > 0 )
    {
      m_pTexture = this->m_pTexture;
      v9 = &this->particle[0].filename[4];
      do
      {
        if ( v4 < 4 )
        {
          sprintf(Buffer, "%s\\%s", g_szParticleTexName, v9);
          v10 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, Buffer);
          *m_pTexture = (gbTexture_D3D *)v10;
          ((gbTexture *)v10)->LoadTexture(1);
        }
        ++v4;
        ++m_pTexture;
        v9 += 21572;
      }
      while ( v4 < this->emitter_num );
    }
    v14 = -1;
    return 1;
  }
  else
  {
    v14 = -1;
    return 0;
  }
}

// 0x004BD7C0
int ParticleEffect::SetTimeParam(int nVal)
{
  CEffect *v3; // edi
  int result; // eax
  int v5; // [esp+0x0] [ebp-0xC]

  v3 = (CEffect *)&this->name[4];
  *(float *)&v5 = 1.0 / *((float *)this + 90708);
  ((CEffect *)&this->name[4])->SetRenderParam(v5);
  result = ((CEffect *)v3)->SetRenderParam(nVal);
  *((_DWORD *)this + 90708) = nVal;
  return result;
}

// 0x0053F960
bool ParticleEffect::LoadFromFile(char *filename)
{
  gbVFile *v2; // eax
  gbVFile *v3; // ebp
  size_t FileSize; // esi
  char *v5; // eax
  unsigned int v6; // ecx
  const void *v7; // esi
  TextureLib *v8; // edi
  int v9; // eax
  int v10; // esi
  char *v11; // eax
  char *v12; // ecx
  char *v13; // eax
  char *v14; // esi
  size_t v16; // eax
  size_t v17; // esi
  char *v18; // edi
  TextureLib *v19; // edi
  int v20; // eax
  int v21; // esi
  char *v22; // eax
  char *v23; // ecx
  char *v24; // eax
  char *v25; // esi
  char *v26; // [esp+0x8] [ebp-0x28]
  CHAR String2[4]; // [esp+0x20] [ebp-0x10] BYREF
  TextureLib *v28; // [esp+0x24] [ebp-0xC]
  char *String; // [esp+0x28] [ebp-0x8]
  size_t v30; // [esp+0x2C] [ebp-0x4]
  void *Block; // [esp+0x34] [ebp+0x4]
  char *Blocka; // [esp+0x34] [ebp+0x4]

  v28 = (TextureLib *)this;
  memset(String2, 0, sizeof(String2));
  strncpy(String2, &filename[strlen(filename) - 3], 3u);
  if ( lstrcmpA(lpString1, String2) )
    return 0;
  v2 = ((gbVFileSystem *)g_pVFileSys)->OpenFile(filename, 0x201u);
  v3 = v2;
  if ( !v2 )
    return 0;
  if ( *(_DWORD *)&v2[304] )
  {
    FileSize = ((gbVFileSystem *)g_pVFileSys)->GetFileSize(v2);
    v30 = FileSize;
    Block = malloc(FileSize);
    v5 = (char *)malloc(FileSize);
    v6 = FileSize;
    v7 = *(const void **)&v3[304];
    g_ScriptSystemData.m_String = v5;
    qmemcpy(Block, v7, v6);
    qmemcpy(v5, *(const void **)&v3[304], v6);
    ((gbVFileSystem *)g_pVFileSys)->CloseFile(v3);
    v8 = v28;
    v9 = ((TextureLib *)v28)->ParseConfigFile(g_ScriptSystemData.m_String);
    v10 = v9;
    if ( v9 )
    {
      v11 = (char *)operator new(1088 * v9);
      if ( v11 )
      {
        if ( v10 - 1 >= 0 )
        {
          v12 = v11 + 1060;
          do
          {
            *((_DWORD *)v12 - 3) = 0;
            *((_DWORD *)v12 - 2) = 0;
            *((_DWORD *)v12 - 1) = 0;
            *(_DWORD *)v12 = 0;
            *((_DWORD *)v12 + 1) = 0;
            *((_DWORD *)v12 + 2) = 0;
            *((_DWORD *)v12 + 3) = 0;
            *((_DWORD *)v12 + 4) = 0;
            *(v12 - 1060) = 0;
            *(v12 - 548) = 0;
            *((_DWORD *)v12 - 8) = 256;
            *((_DWORD *)v12 - 9) = 256;
            *((_DWORD *)v12 - 6) = 0;
            *((_DWORD *)v12 - 7) = 0;
            *((_DWORD *)v12 - 5) = 256;
            *((_DWORD *)v12 + 5) = 0;
            v12[24] = 0;
            v12 += 1088;
            --v10;
          }
          while ( v10 );
        }
      }
      else
      {
        v11 = 0;
      }
      v8->m_pTexture = v11;
      v13 = strtok((char *)Block, Delimiter);
      if ( lstrcmpA(v13, "#endfile") )
      {
        do
        {
          v14 = strtok(0, Delimiter);
          ((void ( *)(TextureLib *, char *, char *))*((_DWORD *)v8->m_pResultTex))(v8, v14, Delimiter);
        }
        while ( lstrcmpA(v14, "#endfile") );
      }
      free(Block);
      free(g_ScriptSystemData.m_String);
      LOBYTE(v8[1].m_pResultTex) = 1;
      return 1;
    }
    return 0;
  }
  v16 = ((gbVFileSystem *)g_pVFileSys)->GetFileSize(v2);
  v17 = v16;
  if ( v16 == -1 || !v16 )
  {
    ((gbVFileSystem *)g_pVFileSys)->CloseFile(v3);
    return 0;
  }
  v18 = (char *)operator new(v16);
  g_ScriptSystemData.m_String = v18;
  Blocka = (char *)operator new(v17);
  ((gbVFileSystem *)g_pVFileSys)->Read(v18, v17, v3);
  ((gbVFileSystem *)g_pVFileSys)->CloseFile(v3);
  qmemcpy(Blocka, v18, v17);
  v19 = v28;
  v20 = ((TextureLib *)v28)->ParseConfigFile(Blocka);
  v21 = v20;
  if ( !v20 )
    return 0;
  v22 = (char *)operator new(1088 * v20);
  if ( v22 )
  {
    if ( v21 - 1 >= 0 )
    {
      v23 = v22 + 1060;
      do
      {
        *((_DWORD *)v23 - 3) = 0;
        *((_DWORD *)v23 - 2) = 0;
        *((_DWORD *)v23 - 1) = 0;
        *(_DWORD *)v23 = 0;
        *((_DWORD *)v23 + 1) = 0;
        *((_DWORD *)v23 + 2) = 0;
        *((_DWORD *)v23 + 3) = 0;
        *((_DWORD *)v23 + 4) = 0;
        *(v23 - 1060) = 0;
        *(v23 - 548) = 0;
        *((_DWORD *)v23 - 8) = 256;
        *((_DWORD *)v23 - 9) = 256;
        *((_DWORD *)v23 - 6) = 0;
        *((_DWORD *)v23 - 7) = 0;
        *((_DWORD *)v23 - 5) = 256;
        *((_DWORD *)v23 + 5) = 0;
        v23[24] = 0;
        v23 += 1088;
        --v21;
      }
      while ( v21 );
    }
  }
  else
  {
    v22 = 0;
  }
  v26 = g_ScriptSystemData.m_String;
  v19->m_pTexture = v22;
  v24 = strtok(v26, Delimiter);
  if ( lstrcmpA(v24, "#endfile") )
  {
    do
    {
      v25 = strtok(0, Delimiter);
      ((void ( *)(TextureLib *, char *, char *))*((_DWORD *)v19->m_pResultTex))(v19, v25, Delimiter);
    }
    while ( lstrcmpA(v25, "#endfile") );
  }
  operator delete(String);
  operator delete(Blocka);
  LOBYTE(v28[1].m_pResultTex) = 1;
  return 1;
}
