#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SoundMgr.h"

// 0x0053C340
char SoundMgr::InitCPK(int nVal, int nVal2)
{
  char result; // al
  CPK *v5; // esi
  CPK *p_dwFatherCRC; // edi
  char Buffer[320]; // [esp+0x14] [ebp-0x140] BYREF

  if ( nVal2 )
    result = BinkSetSoundSystem(BinkOpenDirectSound, nVal);
  else
    result = BinkSetSoundSystem(BinkOpenMiles, nVal);
  if ( (g_dwGameFlags & 2) != 0 )
  {
    v5 = (CPK *)&this->m_szScriptMusic[8];
    ((CPK *)&this->m_szScriptMusic[8])->SetOpenMode(1);
    p_dwFatherCRC = (CPK *)&this->m_Cpk.m_CPKTable[32749].dwFatherCRC;
    ((CPK *)p_dwFatherCRC)->SetOpenMode(1);
    if ( ((CPK *)v5)->IsValidCPK("movie\\movie.cpk") )
    {
      ((CPK *)v5)->Load("movie\\movie.cpk");
    }
    else
    {
      sprintf(Buffer, "%s%s", (const char *)&Data, "movie\\movie.cpk");
      if ( ((CPK *)v5)->IsValidCPK(Buffer) )
        ((CPK *)v5)->Load(Buffer);
    }
    result = ((CPK *)p_dwFatherCRC)->IsValidCPK("movie\\movie_end.cpk");
    if ( result )
      return ((CPK *)p_dwFatherCRC)->Load("movie\\movie_end.cpk");
  }
  return result;
}

// 0x0053EA80
int SoundMgr::PlayCPKStream()
{
  int result; // eax
  CPKFile *v3; // esi
  char Buffer[260]; // [esp+0x10] [ebp-0x104] BYREF
  int v5; // [esp+0x118] [ebp+0x4]
  char *v6; // [esp+0x11C] [ebp+0x8]
  int v7; // [esp+0x120] [ebp+0xC]

  if ( LOBYTE(this->m_Cpk.m_pCPKFile[4]) )
  {
    result = (int)((CPK *)&this->m_cbbuf[4])->Open(v6);
    v3 = (CPKFile *)result;
    if ( result )
    {
      sprintf(Buffer, "\\\\\\\\%lu,%lu.mp3", this->m_Cpk.m_pCPKFile[5], *(_DWORD *)(result + 36));
      ((CPK *)&this->m_cbbuf[4])->Seek(v3, 0, 0);
      ((gbAudioManager *)this->m_audiodrv)->PlaySoundStream(v5, Buffer, v7);
      return ((CPK *)&this->m_cbbuf[4])->Close(v3);
    }
  }
  else
  {
    ((gbAudioManager *)this->m_audiodrv)->PlaySoundStream(v5, v6, v7);
  }
  return result;
}
