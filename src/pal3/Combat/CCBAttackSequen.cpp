#include "pal3/gen/CCBAttackSequen.h"

// 0x004DB5C0
int CCBAttackSequen::Update()
{
  char *v2; // eax
  int v3; // ecx
  char *v4; // eax
  int v5; // ecx

  if ( this->m_pCBSystem[453] || !this->m_pCBSystem[452] )
  {
    v4 = &this->m_pCBSystem[16];
    v5 = 11;
    do
    {
      *((_DWORD *)v4 - 1) = 0;
      v4 += 40;
      --v5;
      *((float *)v4 - 10) = *(float *)(*(_DWORD *)this->m_pCBSystem + 80);
    }
    while ( v5 );
  }
  else
  {
    v2 = &this->m_pCBSystem[16];
    v3 = 11;
    do
    {
      if ( v2[31] )
        *((_DWORD *)v2 - 1) = 0;
      else
        *((float *)v2 - 1) = *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *(float *)v2;
      v2 += 40;
      --v3;
      *((float *)v2 - 10) = *(float *)(*(_DWORD *)this->m_pCBSystem + 80);
    }
    while ( v3 );
  }
  this->ProcessQueue();
  this->CheckComplete();
  return this->AdvanceStep();
}

// 0x004DBA60
char CCBAttackSequen::ProcessQueue()
{
  int v2; // ebx
  char *v3; // esi
  __int64 v4; // rax
  int v5; // edi

  v2 = 0;
  v3 = &this->m_pCBSystem[36];
  do
  {
    LOBYTE(v4) = v3[12];
    if ( (_BYTE)v4 )
    {
      LOBYTE(v4) = CCBRoleState::IsRoleAlive(*(_BYTE **)(*(_DWORD *)this->m_pCBSystem + 16), v2);
      if ( (_BYTE)v4 )
      {
        if ( v3[10] )
        {
          v4 = (__int64)((double)(unsigned __int8)v3[9] * (*((float *)v3 - 6) * 50.0) + (double)*(int *)v3);
          *(_DWORD *)v3 = v4;
          if ( (int)v4 > 11500 )
            *(_DWORD *)v3 = 11500;
        }
        else
        {
          v5 = *((_DWORD *)v3 - 1);
          v4 = (__int64)(*((float *)v3 - 6) * 50.0 * (double)(unsigned __int8)v3[8] + (double)v5);
          *((_DWORD *)v3 - 1) = v4;
          if ( (int)v4 >= 11500 )
          {
            if ( v5 < 11500 )
              ++*((_DWORD *)v3 + 1);
            *((_DWORD *)v3 - 1) = 11500;
          }
        }
      }
    }
    ++v2;
    v3 += 40;
  }
  while ( v2 < 11 );
  return v4;
}

// 0x004DBB20
char CCBAttackSequen::CheckComplete()
{
  int v2; // edi
  char *v3; // esi
  char result; // al
  double v5; // st7

  v2 = 76;
  v3 = &this->m_pCBSystem[46];
  do
  {
    result = v3[2];
    if ( result )
    {
      if ( *v3 )
        v5 = (double)*(int *)(v3 - 10) * 0.0078260871 + 659.0;
      else
        v5 = (double)*(int *)(v3 - 14) * 0.017130435 + 460.0;
      result = UIWnd::ScreenToClient(*(_DWORD **)(*(_DWORD *)&this->m_pCBSystem[4] + v2), (__int64)v5, 8);
    }
    v2 += 4;
    v3 += 40;
  }
  while ( v2 < 120 );
  return result;
}

// 0x004DBD40
int CCBAttackSequen::AdvanceStep()
{
  int v1; // ebx
  int v3; // esi
  _BYTE *v4; // ecx
  int v5; // eax
  long double v6; // st7
  char v7; // al
  int result; // eax
  int v9; // [esp+Ch] [ebp-18h]
  float v10; // [esp+14h] [ebp-10h]
  float v11; // [esp+14h] [ebp-10h]
  float v12; // [esp+18h] [ebp-Ch]
  int v13; // [esp+1Ch] [ebp-8h]
  int v14; // [esp+20h] [ebp-4h]

  v1 = 0;
  v13 = 0;
  v3 = 76;
  do
  {
    v4 = *(_BYTE **)&this->m_pCBSystem[8];
    if ( v4[v1 + 577] )
    {
      if ( !v4->IsRoleAlive(v13) || *(_BYTE *)(v1 + *(_DWORD *)&this->m_pCBSystem[8] + 1432) == 1 )
      {
        (***(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)&this->m_pCBSystem[4] + v3))(
          *(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[4] + v3),
          0);
      }
      else
      {
        v5 = *(_DWORD *)&this->m_pCBSystem[4];
        if ( *(_DWORD *)(*(_DWORD *)(v5 + 72) + 56) == 1 )
          (***(void (__thiscall ****)(_DWORD, int))(v3 + v5))(*(_DWORD *)(v3 + v5), 1);
        v14 = -1;
        if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)this->m_pCBSystem + 20) + v3 - 52) + 280) )
        {
          v6 = sin(*(float *)(*(_DWORD *)this->m_pCBSystem + 80) * 16.0);
          v10 = v6;
          v11 = v10 * 50.0;
          v9 = (int)v11;
          if ( v3 < 96 )
          {
            v7 = v9 - 56;
            BYTE2(v14) = v9 - 56;
          }
          else
          {
            v12 = v6 * 125.0;
            v7 = (int)v12 + 126;
          }
          BYTE1(v14) = v7;
          LOBYTE(v14) = v7;
          sub_446030(*(_DWORD **)(*(_DWORD *)&this->m_pCBSystem[4] + v3));
        }
        v14->UpdateAnim();
      }
    }
    v3 += 4;
    result = v13 + 1;
    v1 += 892;
    ++v13;
  }
  while ( v3 < 120 );
  return result;
}
