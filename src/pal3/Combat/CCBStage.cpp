#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStage.h"

// Forward declarations for unnamed functions
int sub_4C5C20(...);
int sub_4DF6B0(...);
int sub_4DF700(...);
int sub_4DF710(...);
int sub_4DFA10(...);
int sub_4DFF90(...);
int sub_4DFFF0(...);
int sub_4EED60(...);
int sub_4F06C0(...);
int sub_4F6CD0(...);
int sub_4FB9A0(...);
int sub_4FB9F0(...);
int sub_4FBA70(...);
int sub_4FBE50(...);
int sub_4FBF90(...);
int sub_4FC150(...);
int sub_4FC700(...);
int sub_4FC7D0(...);
int sub_4FC9A0(...);
int sub_4FCD00(...);
int sub_4FCD50(...);
int sub_4FCDE0(...);
int sub_4FCE00(...);
int sub_4FCFB0(...);
int sub_4FD290(...);
int sub_4FD3D0(...);
int sub_4FD880(...);
int sub_4FDA10(...);
int sub_4FDFC0(...);
int sub_4FE290(...);
int sub_4FE540(...);
int sub_4FE550(...);
int sub_4FE600(...);
int sub_4FECE0(...);
int sub_4FEE60(...);
int sub_4FEFB0(...);
int sub_4FF1B0(...);
int sub_4FF3D0(...);
int sub_4FF5C0(...);
int sub_4FF740(...);
int sub_500840(...);
int sub_5009C0(...);
int sub_500AD0(...);
int sub_503680(...);
int sub_503AE0(...);
int sub_503FA0(...);
int sub_504510(...);
int sub_504540(...);
int sub_5049F0(...);
int sub_504A80(...);
int sub_508460(...);
int sub_50A4B0(...);
int sub_50E160(...);
int sub_50E360(...);
int sub_50E550(...);
int sub_50EB00(...);
int sub_50FD00(...);
int sub_511E20(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aCamFovF[];
extern char aCamXFYFZF[];
extern char aCamYawFPitchFR[];
extern char aDProjectPal3Co_5[];
extern char aEnemysneakatta[];
extern char aMoney[];
extern char aNewFailedAtCre[];
extern char aOver[];
extern char aWe013[];
extern char aWesneakattacke[];
extern char aWitch[];
extern unsigned char byte_17A9927;
extern unsigned char byte_17AA89C;
extern unsigned char byte_17AA91C;
extern unsigned char byte_17AA920;
extern unsigned char byte_17AAA2C;
extern unsigned char byte_17AB6E4;
extern int dword_17A990C;
extern int dword_17AA870;
extern int dword_17AA874;
extern int dword_17AA878;
extern int dword_17AA880;
extern int dword_17AA884;
extern int dword_17AA888;
extern int dword_17AA890;
extern int dword_17AA894;
extern int dword_17AA898;
extern int dword_17AA910;
extern int dword_17AA914;
extern int dword_17AA918;
extern int dword_17AAA20;
extern int dword_17AAA24;
extern int dword_17AAA28;
extern int dword_17AAD3C;
extern int dword_17AB6B8;
extern int dword_17AB6BC;
extern int dword_17AB6C0;
extern int dword_17AB6C8;
extern int dword_17AB6CC;
extern int dword_17AB6D0;
extern int dword_17AB6D8;
extern int dword_17AB6DC;
extern int dword_17AB6E0;
extern float flt_17ABCDC;
extern float flt_56A610;
extern float flt_56A64C;
extern float flt_56A77C;
extern int unk_5DB6C4;

// 0x004DFAA0
int CCBStage::InitRound()
{
  int result; // eax
  const char *v2; // [esp+10h] [ebp+4h]
  float v3; // [esp+14h] [ebp+8h]
  float v4; // [esp+18h] [ebp+Ch]
  int v5; // [esp+1Ch] [ebp+10h]

  strcpy(&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 24], v2);
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 284] = v3;
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 288] = v4;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 20] = 1;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 296] = 1103101952;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 280] = v5;
  result = *(_DWORD *)&this->m_pCBSystem[16] + 1;
  *(_DWORD *)&this->m_pCBSystem[16] = result;
  return result;
}

// 0x004DFED0
int CCBStage::EndRound()
{
  int result; // eax
  float v2; // [esp+4h] [ebp+4h]
  float v3; // [esp+8h] [ebp+8h]
  float v4; // [esp+Ch] [ebp+Ch]
  float v5; // [esp+10h] [ebp+10h]
  char v6; // [esp+14h] [ebp+14h]

  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 284] = v2;
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 288] = v3;
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 292] = v4;
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 296] = v5;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 20] = 5;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 280] = *(_DWORD *)&this->m_pCBSystem[8];
  this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 283] = v6;
  result = *(_DWORD *)&this->m_pCBSystem[16] + 1;
  *(_DWORD *)&this->m_pCBSystem[16] = result;
  return result;
}

// 0x004FB9A0
_DWORD * sub_4FB9A0(int a2)
{
  _DWORD *v2; // edx
  int v3; // esi
  void *v4; // edi

  v2 = this + 688;
  v3 = 256;
  do
  {
    v4 = v2;
    v2 += 658;
    --v3;
    memset(v4, 0, 0x2Cu);
  }
  while ( v3 );
  memset(this, 0, 0xA48B0u);
  *this = a2;
  *((_DWORD *)this + 1) = *(_DWORD *)(a2 + 16);
  return this;
}

// 0x004FB9F0
unsigned int sub_4FB9F0(int this)
{
  _DWORD *v2; // ecx
  unsigned int result; // eax

  v2 = (_DWORD *)(this + 80);
  *v2 = 0;
  v2[1] = 0;
  *(_BYTE *)(this + 152) = 0;
  *(_DWORD *)(this + 156) = 0;
  memset((void *)(this + 168), 0, 0xA4800u);
  *(_DWORD *)(this + 160) = -1;
  *(_DWORD *)(this + 164) = -1;
  *(_DWORD *)(this + 88) = -1;
  *(_DWORD *)(this + 92) = 0;
  *(_DWORD *)(this + 96) = 0;
  *(_WORD *)(this + 100) = 0;
  *(_BYTE *)(this + 102) = 0;
  memset((void *)(this + 104), 0, 0x2Cu);
  *(_DWORD *)(this + 148) = 0;
  result = gbCrc32Compute(aOver);
  *(_DWORD *)(this + 673960) = result;
  return result;
}

// 0x004FBA70
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char __thiscall sub_4FBA70(_DWORD *this)
{
  int v2; // edi
  int v3; // eax
  char result; // al
  _DWORD *i; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD *v9; // eax
  std::codecvt_base *v10; // eax
  int v11; // eax
  void *v12; // eax
  int v13; // eax
  char pExceptionObject[1024]; // [esp+10h] [ebp-100Ch] BYREF
  char ArgList[1024]; // [esp+410h] [ebp-C0Ch] BYREF
  char v16[1024]; // [esp+810h] [ebp-80Ch] BYREF
  char v17; // [esp+C10h] [ebp-40Ch] BYREF
  int v18; // [esp+1018h] [ebp-4h]

  v2 = 0;
  v18 = 0;
  if ( operator new(0x3CCu) )
    v3 = sub_50FD00(this);
  else
    v3 = 0;
  v18 = -1;
  *((_DWORD *)this + 5) = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_5, 6003),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( (unsigned __int8)v3->CCBStageScene() )
  {
    for ( i = this + 6; ; ++i )
    {
      v18 = 1;
      if ( operator new(0x1A18u) )
        v6 = this->GetOBBox();
      else
        v6 = 0;
      v18 = -1;
      *i = v6;
      if ( !v6 )
      {
        qmemcpy(
          pExceptionObject,
          (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_5, 109),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      if ( !(unsigned __int8)v2->IsIdle() )
        break;
      if ( ++v2 >= 11 )
      {
        v18 = 2;
        if ( operator new(0x17E8u) )
          v7 = sub_503FA0(this, g_pGfxManager);
        else
          v7 = 0;
        *((_DWORD *)this + 3) = v7;
        v18 = -1;
        if ( !v7 )
        {
          qmemcpy(
            pExceptionObject,
            (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_5, 124),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        result = sub_504510(v7);
        if ( result )
        {
          v18 = 3;
          if ( operator new(0x690B0u) )
            v8 = this->SetCamPos(*((_DWORD *)this + 3));
          else
            v8 = 0;
          v18 = -1;
          *((_DWORD *)this + 4) = v8;
          if ( !v8 )
          {
            qmemcpy(
              pExceptionObject,
              (const void *)Logger::FormatException((char)ArgList, (int)aNewFailedAtCre, (int)aDProjectPal3Co_5, 135),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          result = v8->Destroy();
          if ( result )
          {
            v9 = operator new(0x4618u);
            v18 = 4;
            if ( v9 )
              v10 = (std::codecvt_base *)sub_4DF6B0(v9, (int)this);
            else
              v10 = 0;
            v18 = -1;
            *((_DWORD *)this + 17) = v10;
            if ( !v10 )
            {
              qmemcpy(
                pExceptionObject,
                (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_5, 6003),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            result = std::v10->do_always_noconv();
            if ( result )
            {
              v18 = 5;
              if ( operator new(0x614u) )
                v11 = sub_511E20(this);
              else
                v11 = 0;
              v18 = -1;
              *((_DWORD *)this + 18) = v11;
              if ( !v11 )
              {
                qmemcpy(
                  pExceptionObject,
                  (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Co_5, 6003),
                  sizeof(pExceptionObject));
                _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              result = v11->CCBStageShadow();
              if ( result )
              {
                v12 = operator new(0x6390u);
                v18 = 6;
                if ( v12 )
                  v13 = v12->SetCircle((int)this);
                else
                  v13 = 0;
                v18 = -1;
                *((_DWORD *)this + 19) = v13;
                if ( !v13 )
                {
                  qmemcpy(
                    v16,
                    (const void *)Logger::FormatException((char)&v17, (int)aCNewFailed, (int)aDProjectPal3Co_5, 6003),
                    sizeof(v16));
                  _CxxThrowException(v16, (_ThrowInfo *)&_TI1_AV_Exception__);
                }
                return (unsigned __int8)v13->IsPointerUnderMouse() != 0;
              }
            }
          }
        }
        return result;
      }
    }
  }
  return 0;
}

// 0x004FBE50
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char __thiscall sub_4FBE50(int this)
{
  int v2; // ebp
  void *v3; // edi
  void **i; // edi
  void *v5; // ebx
  std::codecvt_base *v6; // ecx
  void (__thiscall ***v7)(_DWORD, int); // ecx
  void *v8; // edi
  std::codecvt_base *v9; // ecx
  void *v10; // edi
  void *v11; // edi
  void *v12; // edi

  v2 = 0;
  if ( *(_DWORD *)(this + 20) )
  {
    CCBStageScene::~CCBStageScene();
    v3 = *(void **)(this + 20);
    if ( v3 )
    {
      nullsub_3(*(void **)(this + 20));
      operator delete(v3);
    }
    *(_DWORD *)(this + 20) = 0;
    for ( i = (void **)(this + 24); *i; ++i )
    {
      CCBStageRole::IsAtInitPos();
      v5 = *i;
      if ( *i )
      {
        nullsub_3(*i);
        operator delete(v5);
      }
      *i = 0;
      if ( ++v2 >= 11 )
      {
        v6 = *(std::codecvt_base **)(this + 12);
        if ( v6 )
        {
          std::v6->do_always_noconv();
          v7 = *(void (__thiscall ****)(_DWORD, int))(this + 12);
          if ( v7 )
            (**v7)(v7, 1);
          *(_DWORD *)(this + 12) = 0;
          if ( *(_DWORD *)(this + 16) )
          {
            CCBStageCam::Init();
            v8 = *(void **)(this + 16);
            if ( v8 )
            {
              j_std::codecvt_base::do_always_noconv(*(std::codecvt_base **)(this + 16));
              operator delete(v8);
            }
            *(_DWORD *)(this + 16) = 0;
            v9 = *(std::codecvt_base **)(this + 68);
            if ( v9 )
            {
              std::v9->do_always_noconv();
              v10 = *(void **)(this + 68);
              if ( v10 )
              {
                nullsub_3(*(void **)(this + 68));
                operator delete(v10);
              }
              *(_DWORD *)(this + 68) = 0;
              if ( *(_DWORD *)(this + 72) )
              {
                CCBStageShadow::~CCBStageShadow();
                v11 = *(void **)(this + 72);
                if ( v11 )
                {
                  nullsub_3(*(void **)(this + 72));
                  operator delete(v11);
                }
                *(_DWORD *)(this + 72) = 0;
                if ( *(_DWORD *)(this + 76) )
                {
                  CCBCamControl::DoList();
                  v12 = *(void **)(this + 76);
                  if ( v12 )
                  {
                    sub_508460(*(_DWORD *)(this + 76));
                    operator delete(v12);
                  }
                  *(_DWORD *)(this + 76) = 0;
                  return 1;
                }
              }
            }
          }
        }
        return 0;
      }
    }
  }
  return 0;
}

// 0x004FBF90
char sub_4FBF90()
{
  int v3; // ebx
  int v4; // edi
  _DWORD *v5; // esi
  int v6; // ecx
  void *v7; // ecx

  CCBStage::~CCBStage((int)this);
  *((_DWORD *)this + 2) = *(_DWORD *)(*this + 28);
  if ( !*((_DWORD *)this + 5) || !(unsigned __int8)CCBStageScene::Reset() )
    return 0;
  v3 = 0;
  v4 = 0;
  v5 = this + 6;
  do
  {
    if ( !*v5 )
      return 0;
    CCBStageRole::GetRotAngle();
    if ( *(_BYTE *)(*((_DWORD *)this + 1) + v4 + 577) )
    {
      if ( !(unsigned __int8)v3->IsAtProtectPos(0, 0) )
        return 0;
    }
    else if ( !(unsigned __int8)v3->IsAtProtectPos(0, 0) )
    {
      return 0;
    }
    v4 += 892;
    ++v3;
    ++v5;
  }
  while ( v4 < 9812 );
  if ( !*((_DWORD *)this + 3) || !(unsigned __int8)sub_504540() )
    return 0;
  if ( !*((_DWORD *)this + 4) || !(unsigned __int8)CCBStageCam::Update() )
    return 0;
  v6 = *((_DWORD *)this + 18);
  if ( !v6 || !(unsigned __int8)v6->Reset() )
    return 0;
  if ( !*((_DWORD *)this + 19) || !(unsigned __int8)CCBCamControl::ResetListFlag() )
    return 0;
  v7 = (void *)*((_DWORD *)this + 17);
  if ( !v7 || !sub_4DF700(v7) )
    return 0;
  sub_4DFFF0(*((_DWORD *)this + 17), 0.0, 0);
  return 1;
}

// 0x004FC0A0
int CCBStage::Update()
{
  void **v2; // esi
  int v3; // ebx
  float *v4; // eax
  int result; // eax
  float v6; // [esp+0h] [ebp-10h]

  if ( this->m_pCBSystem[152] != 1 )
  {
    GRPinput::GetCursorPos((LPPOINT)&this->m_pCBSystem[80]);
    CCBStageScene::SetBattleFieldAttr(*(_DWORD **)&this->m_pCBSystem[20]);
    if ( dword_17A990C == 1 )
      this->Update();
    else
      this->Render();
    v2 = (void **)&this->m_pCBSystem[24];
    v3 = 11;
    do
    {
      if ( *((_BYTE *)*v2 + 264) )
        CCBStageRole::IsTaskFinished(*v2);
      ++v2;
      --v3;
    }
    while ( v3 );
    CCBStage::ProcessTurn(*(CCBStage **)&this->m_pCBSystem[12]);
    CCBStageCam::DoTask(*(_DWORD *)&this->m_pCBSystem[16]);
    nullsub_3(*(void **)&this->m_pCBSystem[68]);
    nullsub_3(*(void **)&this->m_pCBSystem[72]);
    this->UpdatePhysics();
    v6 = *(double *)(*(_DWORD *)this->m_pCBSystem + 64);
    v4 = (float *)CEffectSystem::DestroyAllEffect();
    v4->SetVisible(v6);
  }
  return result;
}

// 0x004FC150
int sub_4FC150()
{
  float v2; // ecx
  char *v3; // ecx
  char *v4; // edi
  double v5; // st7
  gbVec3D *v6; // eax
  int v7; // eax
  int v8; // eax
  float *v9; // eax
  int result; // eax
  float v11; // ecx
  int v12; // edx
  float v13; // [esp+1Ch] [ebp-7Ch]
  float v14; // [esp+20h] [ebp-78h]
  float v15; // [esp+24h] [ebp-74h]
  int v16; // [esp+30h] [ebp-68h] BYREF
  int v17; // [esp+34h] [ebp-64h] BYREF
  float v18; // [esp+38h] [ebp-60h] BYREF
  float v19; // [esp+3Ch] [ebp-5Ch]
  int v20; // [esp+40h] [ebp-58h]
  float v21; // [esp+44h] [ebp-54h] BYREF
  float v22; // [esp+48h] [ebp-50h]
  int v23; // [esp+4Ch] [ebp-4Ch]
  _DWORD v24[3]; // [esp+50h] [ebp-48h] BYREF
  _DWORD v25[3]; // [esp+5Ch] [ebp-3Ch] BYREF
  float v26[6]; // [esp+68h] [ebp-30h] BYREF
  float v27; // [esp+80h] [ebp-18h] BYREF
  float v28; // [esp+84h] [ebp-14h]
  float v29; // [esp+88h] [ebp-10h]
  float v30[3]; // [esp+8Ch] [ebp-Ch] BYREF

  v25[1] = 1065353216;
  v19 = 0.0;
  v25[0] = 0;
  v25[2] = 0;
  v18 = 1.0;
  v20 = 1065353216;
  v24[1] = 0;
  v21 = 0.0;
  v22 = 0.0;
  v23 = 0;
  v24[0] = 1065353216;
  v24[2] = 1065353216;
  v27 = 0.0;
  v28 = 0.0;
  v29 = 0.0;
  (gbVec3D *->gbVec3D()v30, 0.0, 0.0, 0.0);
  v2 = *((float *)this + 21);
  v18 = *((float *)this + 20);
  v19 = v2;
  v3 = (char *)*((_DWORD *)this + 3);
  v16 = 0;
  v17 = 0;
  v4 = (char *)v3->GetViewTarget(v26, (int *)&v18);
  gbVec3D::operator=(&v27, v4);
  gbVec3D::operator=(v30, v4 + 12);
  v5 = (gbRay *->IntersectPlane()&v27, (struct gbVec3D *)v25, (struct gbVec3D *)v24);
  v18 = v30[0] * v5;
  v19 = v30[1] * v5;
  v15 = v29 + v5 * v30[2];
  v14 = v28 + v19;
  v13 = v18 + v27;
  v6 = (gbVec3D *->gbVec3D()v26, v13, v14, v15);
  v18 = *(float *)v6;
  v19 = *((float *)v6 + 1);
  v7 = *((_DWORD *)v6 + 2);
  v21 = v18;
  v20 = v7;
  v23 = v7;
  v8 = *((_DWORD *)this + 22);
  v22 = v19;
  if ( v8 != -1 )
  {
    gbVec3D::operator=(*(this + v8 + 6) + 6596, &v21);
    v9 = (float *)*(this + *((_DWORD *)this + 22) + 6);
    v9[1646] = v21;
    v9 += 1646;
    v9[1] = v22;
    *((_DWORD *)v9 + 2) = v23;
  }
  result = *((_DWORD *)this + 5);
  if ( *(_BYTE *)(result + 964) )
  {
    if ( (MEMORY[0xBFC6D8] & 0xF) == 1 )
    {
      v18 = v21;
      v19 = v22;
      v20 = v23;
      v11 = v22;
      *(float *)(result + 888) = v21;
      v12 = v20;
      *(float *)(result + 892) = v11;
      *(_DWORD *)(result + 896) = v12;
    }
    else
    {
      GRPinput::GetMousePos(&g_Input, &v16, &v17);
      result = *((_DWORD *)this + 5);
      *(float *)(result + 912) = (double)v16 + *(float *)(result + 912);
      *(float *)(*((_DWORD *)this + 5) + 920) = (double)v17 * 0.016666668 + *(float *)(*((_DWORD *)this + 5) + 920);
    }
  }
  return result;
}

// 0x004FC3A0
int CCBStage::EditorUpdate()
{
  int v2; // ebp
  CCBStageCam *v3; // eax
  int v4; // eax
  void *v5; // eax
  CCBStageCam *v6; // eax
  gbSceneGraph *pSceneGraph; // ebx
  struct gbCamera *v8; // eax
  gbMatrixStack *v9; // edi
  int v10; // eax
  char *v11; // eax
  int v12; // ecx
  long double v13; // st7
  bool v14; // cc
  CCBStageCam *v15; // eax
  struct gbCamera *v16; // eax
  int v17; // ecx
  int v18; // ecx
  void *v19; // eax
  int v21; // [esp+18h] [ebp-3Ch]
  float v22; // [esp+20h] [ebp-34h]
  CCBStageRole **v23; // [esp+38h] [ebp-1Ch]
  int v24; // [esp+38h] [ebp-1Ch]
  float v25; // [esp+3Ch] [ebp-18h]
  char *v26; // [esp+40h] [ebp-14h]
  float v27; // [esp+48h] [ebp-Ch] BYREF
  float v28; // [esp+4Ch] [ebp-8h]
  float v29; // [esp+50h] [ebp-4h]

  v2 = 0;
  *(_DWORD *)&g_pGfxManager[444] = 0;
  v3 = this->m_pCam;
  if ( v3 )
    v4 = (int)&v3->OrthoSize;
  else
    v4 = 0;
  v21 = v4;
  v5 = CEffectSystem::DestroyAllEffect();
  CEffectSystem::HandleViewMove((int)v5, v21);
  v6 = this->m_pCam;
  pSceneGraph = *(gbSceneGraph **)&g_pGfxManager[448];
  if ( v6 )
    v8 = (CCBStageCam *)&v6->OrthoSize;
  else
    v8 = 0;
  pSceneGraph->Begin(v8);
  LOBYTE(pSceneGraph->?[9].m[0]) = 0;
  v9 = *(gbMatrixStack **)&g_pGfxManager[216];
  (CameraCtrl *->SetAsCurrent()this->m_pCam, 3);
  v9->Push();
  (*(void (__thiscall **)(int, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_TempStorageWPX + 16) + 16))(
    *(_DWORD *)this->m_TempStorageWPX + 16,
    0);
  if ( !HIBYTE(this->m_pShadow[3]) )
  {
    this->m_pScene->GetBattleFieldSubdueAttr(v9);
    v23 = (CCBStageRole **)&this->m_pRole;
    do
    {
      if ( dword_17A990C == 1
        || (v10 = (int)&this->m_pRoleState->m_sCombatDialog[v2], *(_BYTE *)(v10 + 577)) && !*(_BYTE *)(v10 + 1432) )
      {
        CCBStageRole::IsDoTask(*v23, v9);
      }
      v2 += 892;
      ++v23;
    }
    while ( v2 < 9812 );
    v11 = (char *)&this->m_pRole;
    v24 = 0;
    v26 = (char *)&this->m_pRole;
    do
    {
      v12 = *(_DWORD *)v11;
      if ( *(_BYTE *)(*(_DWORD *)v11 + 280) )
      {
        v27 = 0.0;
        v28 = 0.0;
        v29 = 0.0;
        v12->DoTask(&v27);
        v13 = sin(this->m_pCBSystem->m_fTimeFund * 10.0 + (double)v24);
        v25 = v13;
        v28 = v13 * 5.0 + v28 + 6.0;
        v9->Push();
        v9->Translate(v27, v28, v29);
        v22 = v25 * 0.2 + 1.0;
        v9->Scale(1.0, v22, 1.0);
        ((void (__thiscall *)(gbGeomNode *, _DWORD))this->m_pScene->m_pPointer->next[4].next)(
          this->m_pScene->m_pPointer,
          0);
        v9->Pop();
      }
      v11 = v26 + 4;
      v14 = ++v24 < 5;
      v26 += 4;
    }
    while ( v14 );
  }
  (SceneMgr *->RenderUpdate()this->m_pCBSystem->m_pEffMgr);
  (SceneMgr *->RenderUpdate()this->m_pCBSystem->m_pATSEffMgr);
  v9->Pop();
  pSceneGraph->End();
  (CCBStageShadow *->Create()this->m_NGHVariance);
  v15 = this->m_pCam;
  if ( v15 )
    v16 = (CCBStageCam *)&v15->OrthoSize;
  else
    v16 = 0;
  pSceneGraph->Begin(v16);
  LOBYTE(pSceneGraph->?[9].m[0]) = 0;
  (*(void (__thiscall **)(int, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_TempStorageWPX + 16) + 16))(
    *(_DWORD *)this->m_TempStorageWPX + 16,
    0);
  ((void (__thiscall *)(gbVisNode *, _DWORD))this->m_pScene->m_pLights->next[4].next)(this->m_pScene->m_pLights, 0);
  (SceneMgr *->RenderAll()this->m_pCBSystem->m_pEffMgr);
  (SceneMgr *->RenderAll()this->m_pCBSystem->m_pATSEffMgr);
  C3DSpark::Render((int)this->m_pCBSystem->m_p3DSpark->m_Spark, (struct gbVec3D *)gbSceneGraph::End);
  pSceneGraph->End();
  if ( byte_17A9927 )
  {
    this->m_pScene->IsSameBattleFieldAttr();
    this->m_pScene->GetBFASubdueFM();
  }
  if ( BYTE1(this->m_pCBSystem->m_bFiveNimbus) )
  {
    if ( dword_17A990C == 1 )
    {
      v17 = (int)this->m_pScene;
      if ( !*(_BYTE *)(v17 + 963) )
        goto LABEL_31;
      v17->LoadPointer(60);
    }
    if ( dword_17A990C == 4 )
    {
      v18 = (int)this->m_pScene;
      if ( *(_BYTE *)(v18 + 963) )
        v18->LoadPointer(60);
      CCCTData::~CCCTData((int)this->m_pCamControl);
    }
  }
LABEL_31:
  sub_4DFA10((int *)this->?.y);
  v19 = CEffectSystem::DestroyAllEffect();
  CEffectSystem::Update((int)v19);
  sub_4C5C20((int *)g_pSceneMgr);
  PushMatrixStacks();
  v29 = 0.0;
  (CGameData *->Render()&g_GameData);
  sub_4DF710(this->?.y);
  if ( !g_pPalScript )
    (Logger *->Render()g_Logger);
  v29 = NAN;
  return (int)PopMatrixStacks();
}

// 0x004FC6F0
// attributes: thunk
void __thiscall CCBStage::Render(_DWORD *this)
{
  this->GetTask();
}

// 0x004FC700
int sub_4FC700(int a2, const void *a3, char a4)
{
  int v5; // ebp
  _BYTE *i; // eax
  _DWORD *v8; // edi

  if ( (int)*((_DWORD *)this + 39) >= 246 )
    CCBSystem::CreateObj(&unk_5DB6C4, 0, 48);
  v5 = 0;
  for ( i = this + 699; *i; i += 2632 )
  {
    if ( ++v5 >= 256 )
      return -1;
  }
  v8 = this + 658 * v5;
  v8[43] = 2;
  *((_BYTE *)v8 + 2796) = 1;
  *((_BYTE *)v8 + 2797) = a4;
  v8[686] = CCBSystem::ProcProtect(*this);
  v8[44] = 0;
  v8[42] = a2;
  v8[687] = 0;
  if ( a3 )
    qmemcpy(v8 + 688, a3, 0x2Cu);
  else
    v8[690] = -1;
  ++*((_DWORD *)this + 39);
  return v5;
}

// 0x004FC7D0
int sub_4FC7D0(int a2, int a3, int a4, int a5, int a6, _DWORD *a7, int a8, int a9)
{
  int v9; // ebp
  int v10; // ebx
  _BYTE *i; // eax
  _DWORD *v13; // esi
  _DWORD *v14; // esi

  v9 = 0;
  v10 = 2632 * a2;
  for ( i = this + 658 * a2 + 56; *i; i += 80 )
  {
    if ( ++v9 >= 32 )
      return -1;
  }
  v13 = (_DWORD *)((char *)this + 80 * v9 + v10 + 184);
  memset(v13, 0, 0x50u);
  *((_BYTE *)this + 80 * v9 + v10 + 225) = 0;
  *((_BYTE *)this + 80 * v9 + v10 + 224) = 1;
  *(_DWORD *)((char *)this + 80 * v9 + v10 + 200) = 2;
  *v13 = a3;
  *(_DWORD *)((char *)this + 80 * v9 + v10 + 188) = a4;
  *(_DWORD *)((char *)this + 80 * v9 + v10 + 192) = a5;
  *(_DWORD *)((char *)this + 80 * v9 + v10 + 196) = a6;
  v13[5] = CCBSystem::ProcProtect(*this);
  v13[7] = a8;
  v13[6] = 0;
  v13[8] = a9;
  if ( a7 )
  {
    v14 = v13 + 11;
    *v14 = *a7;
    v14[1] = a7[1];
    v14[2] = a7[2];
  }
  ++*(_DWORD *)((char *)this + v10 + 176);
  return v9;
}

// 0x004FC8B0
char CCBStage::Procced(int a2)
{
  char *v2; // edx
  int v3; // ecx
  _BYTE *v4; // eax

  v2 = &this->m_pCBSystem[2632 * a2];
  v3 = 32;
  v4 = v2 + 227;
  do
  {
    if ( *(v4 - 3) )
      *v4 = 1;
    v4 += 80;
    --v3;
  }
  while ( v3 );
  v2[2797] = 1;
  return 1;
}

// 0x004FC980
int CCBStage::IsDoTask(int a2)
{
  return (int)&this->m_pCBSystem[2632 * a2 + 168];
}

// 0x004FC9A0
int sub_4FC9A0(int a2)
{
  return *(this + 658 * a2 + 686);
}

// 0x004FC9C0
char * CCBStage::DelTask(int a2, _BYTE *a3, _DWORD *a4)
{
  char *result; // eax

  *a3 = 0;
  *a4 = 0;
  result = &this->m_pCBSystem[2632 * a2];
  if ( *((_DWORD *)result + 43) == 4 )
  {
    *a3 = 1;
    *a4 = *((_DWORD *)result + 687);
  }
  return result;
}

// 0x004FCA00
char CCBStage::ForceDelTask(int a2)
{
  char *v2; // eax
  int v3; // edx

  v2 = &this->m_pCBSystem[168];
  v3 = 0;
  while ( !v2[2628] || a2 != *(_DWORD *)v2 || *((_DWORD *)v2 + 1) == 4 )
  {
    ++v3;
    v2 += 2632;
    if ( v3 >= 256 )
      return 0;
  }
  return 1;
}

// 0x004FCA80
void CCBStage::GetTask()
{
  int v2; // ebx
  char *v3; // edi
  int v4; // ebp
  char *v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int (__thiscall *v9)(_DWORD *, int); // ecx
  char *v10; // [esp+10h] [ebp-4h]

  v2 = 0;
  v3 = &this->m_pUtil[2796];
  v10 = &this->m_pUtil[2796];
  do
  {
    if ( *v3 == 1 && *((_DWORD *)v3 - 656) == 3 )
    {
      v4 = 0;
      v5 = v3 - 2676;
      do
      {
        if ( !v5[104] || v4 > 0 && *(_DWORD *)v5 == 2 )
          break;
        if ( *((_DWORD *)v5 + 20) == 2 )
        {
          if ( v4 > 0 )
          {
            if ( *((float *)v5 + 23) >= 0.0 )
            {
              if ( *(float *)(*(_DWORD *)this->m_pUtil + 80) - *((float *)v5 + 2) > *((float *)v5 + 23) )
              {
LABEL_25:
                (CCBStage *->GetTaskID()this, v2, v4);
LABEL_26:
                *(_DWORD *)&this->m_pUtil[160] = v2;
                *(_DWORD *)&this->m_pUtil[164] = v4;
                (*((void (__thiscall **)(char *, _DWORD))v5 + 16))(&this->m_pUtil[*((_DWORD *)v5 + 17)], 0);
              }
            }
            else if ( *(_DWORD *)v5 == 4 )
            {
              goto LABEL_25;
            }
          }
        }
        else
        {
          if ( *((_DWORD *)v5 + 20) == 3 )
            goto LABEL_26;
          if ( *((_DWORD *)v5 + 20) == 4 && (CCBStage *->GetTaskState()this, v2) == 1 )
          {
            v6 = *((_DWORD *)v10 - 655);
            *((_DWORD *)v10 - 656) = 4;
            v6 *= 80;
            v7 = *(_DWORD *)&v10[v6 - 2656];
            v8 = (int)&v10[v6 - 2628];
            *((_DWORD *)v10 - 12) = v7;
            v9 = *(int (__thiscall **)(_DWORD *, int))(v8 - 64);
            if ( v9 == CCBStage::ProcFiveLienupFadeOut
              && (!v9 || !*(_DWORD *)(v8 - 60) && !*(_DWORD *)(v8 - 56) && !*(_DWORD *)(v8 - 52)) )
            {
              *((_DWORD *)v10 - 12) = *(_DWORD *)(v8 - 108);
            }
            if ( v10[1] == 1 )
            {
              this->GetStageRole(v2);
              break;
            }
          }
        }
        ++v4;
        v5 += 80;
      }
      while ( v4 < 32 );
    }
    ++v2;
    v3 = v10 + 2632;
    v10 += 2632;
  }
  while ( v2 < 256 );
}

// 0x004FCBD0
char CCBStage::GetTaskID(int a2, int a3)
{
  char *v3; // eax

  v3 = &this->m_pCBSystem[2632 * a2 + 80 * a3];
  *((_DWORD *)v3 + 50) = 3;
  *((float *)v3 + 52) = *(float *)(*(_DWORD *)this->m_pCBSystem + 80);
  return 1;
}

// 0x004FCC10
char CCBStage::GetTaskState(int a2)
{
  int v2; // edx
  char *v3; // ecx
  int v4; // eax
  _DWORD *i; // ecx

  v2 = 0;
  v3 = &this->m_pCBSystem[2632 * a2];
  v4 = *((_DWORD *)v3 + 44);
  if ( v4 <= 0 )
    return 1;
  for ( i = v3 + 200; *i == 4; i += 20 )
  {
    if ( ++v2 >= v4 )
      return 1;
  }
  return 0;
}

// 0x004FCC50
char CCBStage::GetTaskState(int a2)
{
  int v2; // ebx
  char *i; // edx
  int v4; // eax
  int v5; // esi
  char *v6; // eax
  int v7; // ecx

  v2 = 0;
  for ( i = &this->m_pCBSystem[2796]; ; i += 2632 )
  {
    if ( *i )
    {
      if ( *((_DWORD *)i - 656) != 4 && *((_DWORD *)i - 657) == 11 )
      {
        v4 = *((_DWORD *)i - 9);
        if ( v4 >= 5 && v4 < 11 )
          break;
      }
    }
LABEL_18:
    if ( ++v2 >= 256 )
      return 0;
  }
  v5 = 0;
  v6 = i - 2612;
  while ( 1 )
  {
    if ( *(int (__thiscall **)(_DWORD *, int))v6 == CCBStage::HandleKeyCtrl
      && (!*(_DWORD *)v6 || !*((_DWORD *)v6 + 1) && !*((_DWORD *)v6 + 2) && !*((_DWORD *)v6 + 3)) )
    {
      if ( *((_DWORD *)v6 + 4) == 4 )
        goto LABEL_18;
      v7 = *((_DWORD *)i - 8);
      if ( v7 == a2 || v7 == -1 && i[a2 - 15] )
        return 1;
    }
    ++v5;
    v6 += 80;
    if ( v5 >= 32 )
      goto LABEL_18;
  }
}

// 0x004FCD00
int sub_4FCD00(int a2)
{
  int result; // eax
  _DWORD *v4; // edx
  int v5; // ebx

  result = CCBStageRole::GetState(*(this + a2 + 6));
  v4 = this + 690;
  v5 = 256;
  do
  {
    LOBYTE(result) = *((_BYTE *)v4 + 36);
    if ( (_BYTE)result )
    {
      if ( *v4 == a2 )
      {
        result = 0;
        memset(v4 - 648, 0, 0xA48u);
        --*((_DWORD *)this + 39);
      }
    }
    v4 += 658;
    --v5;
  }
  while ( v5 );
  return result;
}

// 0x004FCD50
_BYTE *__userpurge sub_4FCD50@<eax>(_BYTE *result@<eax>, int a2@<ecx>, int a3)
{
  int v3; // edx
  int v4; // esi
  int v5; // ecx

  v3 = a2 + 2760;
  v4 = 256;
  do
  {
    LOBYTE(result) = *(_BYTE *)(v3 + 36);
    if ( (_BYTE)result && *(_DWORD *)v3 == a3 )
    {
      result = (_BYTE *)(v3 - 2533);
      v5 = 32;
      do
      {
        if ( *(result - 3) )
          *result = 1;
        result += 80;
        --v5;
      }
      while ( v5 );
    }
    v3 += 2632;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x004FCDA0
int CCBStage::IsTaskExist(int a2)
{
  int result; // eax
  char *v3; // ecx
  int v4; // edx

  result = 0;
  v3 = &this->m_pCBSystem[2760];
  v4 = 256;
  do
  {
    if ( v3[36] && *(_DWORD *)v3 == a2 && *((_DWORD *)v3 - 648) != 29 )
      ++result;
    v3 += 2632;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x004FCDE0
int sub_4FCDE0(int a2)
{
  int result; // eax

  result = a2;
  if ( a2 == -1 )
    *((_DWORD *)this + 22) = -1;
  else
    *((_DWORD *)this + 22) = a2;
  return result;
}

// 0x004FCE00
int sub_4FCE00(int a2)
{
  int v2; // eax
  int v3; // esi

  v2 = 80 * *((_DWORD *)this + 41);
  v3 = (int)this + 2632 * *((_DWORD *)this + 40) + v2 + 184;
  if ( *((_BYTE *)this + 2632 * *((_DWORD *)this + 40) + v2 + 225) )
  {
    if ( *((_BYTE *)this + 2632 * *((_DWORD *)this + 40) + v2 + 227) == 1
      || *(float *)(*this + 80) - *(float *)(v3 + 24) >= *(float *)(v3 + 32)
      || (char *->SetJoystickAbs()&g_Input) )
    {
      *(_DWORD *)(v3 + 16) = 4;
    }
    return 0;
  }
  else
  {
    *((_BYTE *)this + 2632 * *((_DWORD *)this + 40) + v2 + 225) = 1;
    return 0;
  }
}

// 0x004FCE70
int CCBStage::IsSubTaskFinished(int a2)
{
  int v3; // ecx
  char *v4; // eax
  double v5; // st7
  int v6; // esi
  double v7; // st7
  unsigned int v8; // eax
  unsigned int v9; // ecx
  float v11; // [esp+1Ch] [ebp-8h]
  float v12; // [esp+1Ch] [ebp-8h]
  float v13; // [esp+20h] [ebp-4h]
  float v14; // [esp+20h] [ebp-4h]

  v3 = 329 * *(_DWORD *)&this->m_pCBSystem[160];
  v4 = &this->m_pCBSystem[80 * *(_DWORD *)&this->m_pCBSystem[164]];
  v5 = *(float *)&v4[8 * v3 + 216] * 0.25;
  v6 = (int)&v4[8 * v3 + 184];
  v11 = v5;
  v13 = v5 * 3.0;
  if ( !v4[8 * v3 + 225] )
  {
    *(_DWORD *)&v4[8 * v3 + 248] = 0;
    v4[8 * v3 + 225] = 1;
  }
  CCBStage::EndRound(*(CCBStage **)&this->m_pCBSystem[68]);
  v7 = *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *(float *)(v6 + 24);
  if ( v7 >= v13 )
  {
    v12 = (1.0 - (v7 - v13) / v11) * 255.0;
    v9 = (int)v12;
    *(_DWORD *)(v6 + 64) = v9;
    v8 = v9 <= 0xFF ? v9 : 0;
  }
  else
  {
    v14 = v7 / v13 * 255.0;
    v8 = (int)v14;
    *(_DWORD *)(v6 + 64) = v8;
    if ( v8 > 0xFF )
      v8 = 255;
  }
  *(_DWORD *)(v6 + 64) = v8;
  if ( *(_BYTE *)(v6 + 43) == 1
    || *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *(float *)(v6 + 24) >= *(float *)(v6 + 32) )
  {
    *(_DWORD *)(v6 + 16) = 4;
  }
  return 0;
}

// 0x004FCFB0
int sub_4FCFB0(int a2)
{
  int v3; // ecx
  int v4; // edx
  double v5; // st7
  int v6; // esi
  double v7; // st7
  unsigned int v8; // eax
  unsigned int v9; // ecx
  float v11; // [esp+8h] [ebp-8h]
  float v12; // [esp+8h] [ebp-8h]
  float v13; // [esp+Ch] [ebp-4h]
  float v14; // [esp+Ch] [ebp-4h]

  v3 = 329 * *((_DWORD *)this + 40);
  v4 = 80 * *((_DWORD *)this + 41);
  v5 = *(float *)((char *)this + 8 * v3 + v4 + 216) * 0.25;
  v6 = (int)this + 8 * v3 + v4 + 184;
  v11 = v5;
  v13 = v5 * 3.0;
  if ( !*((_BYTE *)this + 8 * v3 + v4 + 225) )
  {
    *(_DWORD *)((char *)this + 8 * v3 + v4 + 248) = 0;
    *((_BYTE *)this + 8 * v3 + v4 + 225) = 1;
  }
  sub_4DFF90((_DWORD *)*((_DWORD *)this + 17), *((_BYTE *)this + 8 * v3 + v4 + 248));
  v7 = *(float *)(*this + 80) - *(float *)(v6 + 24);
  if ( v7 >= v13 )
  {
    v12 = (1.0 - (v7 - v13) / v11) * 255.0;
    v9 = (int)v12;
    *(_DWORD *)(v6 + 64) = v9;
    v8 = v9 <= 0xFF ? v9 : 0;
  }
  else
  {
    v14 = v7 / v13 * 255.0;
    v8 = (int)v14;
    *(_DWORD *)(v6 + 64) = v8;
    if ( v8 > 0xFF )
      v8 = 255;
  }
  *(_DWORD *)(v6 + 64) = v8;
  if ( *(_BYTE *)(v6 + 43) == 1 || *(float *)(*this + 80) - *(float *)(v6 + 24) >= *(float *)(v6 + 32) )
    *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FD0B0
int CCBStage::IsTaskValid(int a2)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  double v6; // st7
  unsigned int v7; // eax
  float v9; // [esp+20h] [ebp-4h]
  float v10; // [esp+20h] [ebp-4h]

  v3 = 329 * *(_DWORD *)&this->m_pCBSystem[160];
  v4 = 80 * *(_DWORD *)&this->m_pCBSystem[164];
  v5 = &this->m_pCBSystem[8 * v3 + 184 + v4];
  v9 = *(float *)&this->m_pCBSystem[8 * v3 + 216 + v4];
  if ( !this->m_pCBSystem[8 * v3 + 225 + v4] )
  {
    *(_DWORD *)&this->m_pCBSystem[8 * v3 + 248 + v4] = 0;
    this->m_pCBSystem[8 * v3 + 225 + v4] = 1;
  }
  CCBStage::EndRound(*(CCBStage **)&this->m_pCBSystem[68]);
  v6 = *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v5 + 6);
  if ( v6 >= v9 )
  {
    *((_DWORD *)v5 + 16) = 255;
    *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    v10 = v6 / v9 * 255.0;
    v7 = (int)v10;
    *((_DWORD *)v5 + 16) = v7;
    if ( v7 > 0xFF )
      v7 = 255;
    *((_DWORD *)v5 + 16) = v7;
  }
  if ( v5[43] == 1 )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FD1A0
int CCBStage::IsSubTaskValid(int a2)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  double v6; // st7
  unsigned int v7; // ecx
  float v9; // [esp+20h] [ebp-4h]
  float v10; // [esp+20h] [ebp-4h]

  v3 = 329 * *(_DWORD *)&this->m_pCBSystem[160];
  v4 = 80 * *(_DWORD *)&this->m_pCBSystem[164];
  v5 = &this->m_pCBSystem[8 * v3 + 184 + v4];
  v9 = *(float *)&this->m_pCBSystem[8 * v3 + 216 + v4];
  if ( !this->m_pCBSystem[8 * v3 + 225 + v4] )
  {
    *(_DWORD *)&this->m_pCBSystem[8 * v3 + 248 + v4] = 255;
    this->m_pCBSystem[8 * v3 + 225 + v4] = 1;
  }
  CCBStage::EndRound(*(CCBStage **)&this->m_pCBSystem[68]);
  v6 = *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v5 + 6);
  if ( v6 >= v9 )
  {
    *((_DWORD *)v5 + 16) = 0;
    *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    v10 = (1.0 - v6 / v9) * 255.0;
    v7 = (int)v10;
    *((_DWORD *)v5 + 16) = v7;
    *((_DWORD *)v5 + 16) = v7 <= 0xFF ? v7 : 0;
  }
  if ( v5[43] == 1 )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FD290
int sub_4FD290(int a2)
{
  int v3; // ecx
  _DWORD *v4; // eax
  int v5; // edi
  int v7; // ebp
  char *v8; // eax
  void (__thiscall ***v9)(_DWORD, int); // ecx
  char *v10; // eax
  int v11; // ecx

  v3 = 329 * *((_DWORD *)this + 40);
  v4 = this + 20 * *((_DWORD *)this + 41);
  v5 = (int)&v4[2 * v3 + 46];
  if ( !BYTE1(v4[2 * v3 + 56]) )
  {
    if ( *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    v7 = *(_DWORD *)(*this + 4);
    if ( *(_BYTE *)(*((_DWORD *)this + 1) + 536) )
    {
      v8 = PalScript::SetAppName(&MEMORY[0x8ACD30], aWesneakattacke);
      UIWnd::SetEnable(*(_DWORD **)(v7 + 1072), v8, 1);
      v9 = *(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(*this + 4) + 1072);
    }
    else
    {
      v10 = PalScript::SetAppName(&MEMORY[0x8ACD30], aEnemysneakatta);
      UIWnd::SetEnable(*(_DWORD **)(v7 + 1076), v10, 1);
      v9 = *(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(*this + 4) + 1076);
    }
    (**v9)(v9, 1);
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || *(float *)(*this + 80) - *(float *)(v5 + 24) > *(float *)(v5 + 32)
    || *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) )
  {
    v11 = *(_DWORD *)(*this + 4);
    if ( *(_BYTE *)(*((_DWORD *)this + 1) + 536) )
    {
      (***(void (__thiscall ****)(_DWORD, _DWORD))(v11 + 1072))(*(_DWORD *)(v11 + 1072), 0);
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    (***(void (__thiscall ****)(_DWORD, _DWORD))(v11 + 1076))(*(_DWORD *)(v11 + 1076), 0);
    *(_DWORD *)(v5 + 16) = 4;
  }
  return 0;
}

// 0x004FD3D0
int sub_4FD3D0(int this, int a2)
{
  int v3; // ebp
  int v4; // ecx
  int v5; // ebx
  int v6; // eax
  int v8; // edi
  signed int i; // edi
  int v10; // edi
  int v11; // ebx
  _BYTE *v12; // ecx
  int j; // edi
  int v14; // ecx
  int v15; // edx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  char v19; // dl
  int k; // eax
  int v21; // ebp
  int v22; // eax
  int v23; // ecx
  int v24; // eax
  int v25; // ecx
  unsigned int *v26; // [esp+10h] [ebp-10h]
  _DWORD *v27; // [esp+14h] [ebp-Ch]
  _DWORD *v28; // [esp+14h] [ebp-Ch]
  int v29; // [esp+18h] [ebp-8h]
  int v30; // [esp+18h] [ebp-8h]
  int v31; // [esp+1Ch] [ebp-4h]

  if ( (byte_17AAA2C & 1) == 0 )
  {
    dword_17AAA20 = 0;
    byte_17AAA2C |= 1u;
    dword_17AAA24 = 0;
    dword_17AAA28 = 0;
    atexit(nullsub_20);
  }
  v3 = 2632 * *(_DWORD *)(this + 160);
  v31 = *(_DWORD *)(this + v3 + 2760);
  v4 = v3 + 80 * *(_DWORD *)(this + 164);
  v5 = v4 + this + 184;
  v29 = v5;
  if ( !*(_BYTE *)(v4 + this + 225) )
  {
    *(_DWORD *)(this + 92) = 0;
    *(_DWORD *)(this + 96) = 0;
    *(_WORD *)(this + 100) = 0;
    *(_BYTE *)(this + 102) = 0;
    v6 = sub_503680(*(_DWORD *)(v4 + this + 228), this + v3 + 2752);
    dword_17AAD3C = v6;
    if ( v6 == -1 )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 36) = -1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    sub_503AE0(v6, *(_DWORD *)(v5 + 44), *(_DWORD *)(this + v3 + 2756));
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( (*(_BYTE *)(v5 + 44) & 1) != 0 )
  {
    v8 = 0;
    v26 = (unsigned int *)(this + v3 + 2752);
    v27 = (_DWORD *)(this + 24);
    do
    {
      if ( CCBRoleState::CancelVariance(*(char **)(this + 4), v26, v8)
        && !CCBStageRole::IsActive(*(_BYTE **)(this + 4), v8)
        && (unsigned __int8)sub_50A4B0(*v27) == 1 )
      {
        dword_17AAD3C = v8;
        sub_503AE0(v8, *(_DWORD *)(v5 + 44), *(_DWORD *)(this + v3 + 2756));
      }
      ++v8;
      ++v27;
    }
    while ( v8 < 11 );
    sub_503AE0(dword_17AAD3C, *(_DWORD *)(v5 + 44), *(_DWORD *)(this + v3 + 2756));
    for ( i = 0; i < 11; ++i )
    {
      if ( *(_BYTE *)(this + i + 92) && !CCBRoleState::CancelVariance(*(char **)(this + 4), v26, i) )
        *(_BYTE *)(this + i + 92) = 0;
    }
    if ( (unsigned int)dword_17AAD3C <= 0xA && CCBRoleState::GetRoleAttr(*(_DWORD **)(this + 4), v31) < 4 )
      dword_17AAD3C->SetBladeTime();
  }
  else
  {
    v10 = 0;
    v11 = 0;
    v28 = (_DWORD *)(this + 24);
    do
    {
      v12 = *(_BYTE **)(this + 4);
      if ( v12[v11 + 577] && v12->IsActive(v10) == 1 && (unsigned __int8)sub_50A4B0(*v28) == 1 )
      {
        dword_17AAD3C = v10;
        sub_503AE0(v10, *(_DWORD *)(v29 + 44), *(_DWORD *)(this + v3 + 2756));
      }
      v11 += 892;
      ++v10;
      ++v28;
    }
    while ( v11 < 9812 );
    v26 = (unsigned int *)(this + v3 + 2752);
    if ( !sub_4F6CD0(v26) )
    {
      for ( j = 0; j < 11; ++j )
      {
        if ( *(_BYTE *)(this + j + 92) && !CCBRoleState::IsRoleAlive(*(_BYTE **)(this + 4), j) )
          *(_BYTE *)(this + j + 92) = 0;
      }
    }
    v5 = v29;
  }
  v14 = 0;
  v15 = 0;
  v30 = 0;
  v16 = this + 24;
  do
  {
    if ( *(_BYTE *)(v14 + *(_DWORD *)(this + 4) + 577) )
    {
      if ( *(_BYTE *)(v15 + this + 92) )
      {
        ++v30;
        *(_BYTE *)(*(_DWORD *)v16 + 280) = 1;
        *(_BYTE *)(*(_DWORD *)v16 + 274) = 1;
      }
      else
      {
        *(_BYTE *)(*(_DWORD *)v16 + 280) = 0;
        *(_BYTE *)(*(_DWORD *)v16 + 274) = 0;
      }
    }
    v14 += 892;
    ++v15;
    v16 += 4;
  }
  while ( v14 < 9812 );
  if ( v30 <= 0 )
    *(_BYTE *)(v5 + 41) = 0;
  if ( MEMORY[0xBFC5F4] == 1 && ((v17 = MEMORY[0xBFC5E8][0] & 0xF, v17 == 1) || v17 == 2) )
  {
    if ( (*(_BYTE *)(v5 + 44) & 0x10) != 0 )
    {
      *(_BYTE *)(this + v3 + 2769) = 0;
      *(_BYTE *)(this + v3 + 2768) = 0;
      *(_DWORD *)(this + v3 + 2764) = dword_17AAD3C;
      if ( dword_17AAD3C == -1 )
        return 0;
    }
    else
    {
      *(_BYTE *)(this + v3 + 2768) = 0;
      *(_BYTE *)(this + v3 + 2769) = 1;
      v18 = this + v3 + 2781;
      *(_DWORD *)v18 = *(_DWORD *)(this + 92);
      *(_DWORD *)(v18 + 4) = *(_DWORD *)(this + 96);
      *(_WORD *)(v18 + 8) = *(_WORD *)(this + 100);
      *(_BYTE *)(v18 + 10) = *(_BYTE *)(this + 102);
      v19 = 0;
      for ( k = 0; k < 11; ++k )
      {
        if ( *(_BYTE *)(this + 92 + k) )
          v19 = 1;
      }
      if ( !v19 )
        return 0;
    }
    v21 = v31;
    *(_DWORD *)(v5 + 36) = dword_17AAD3C;
    *(_DWORD *)(v5 + 16) = 4;
    v22 = 0;
    *(_BYTE *)(*(_DWORD *)(this + 4 * v31 + 24) + 274) = 0;
    v23 = this + 24;
    do
    {
      if ( *(_BYTE *)(v22 + *(_DWORD *)(this + 4) + 577) )
      {
        *(_BYTE *)(*(_DWORD *)v23 + 280) = 0;
        *(_BYTE *)(*(_DWORD *)v23 + 274) = 0;
      }
      v22 += 892;
      v23 += 4;
    }
    while ( v22 < 9812 );
  }
  else
  {
    v21 = v31;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || MEMORY[0xBFC604] == 1 && (MEMORY[0xBFC5F8] & 0xF) == 1
    || MEMORY[0xBFC704] == 1
    || *v26 == 262 && CCBRoleState::GetRoleField(*(_BYTE **)(this + 4), v21, 16)
    || *v26 == 261 && CCBRoleState::GetRoleField(*(_BYTE **)(this + 4), v21, 15) )
  {
    *(_DWORD *)(v5 + 36) = -1;
    *(_DWORD *)(v5 + 16) = 4;
    v24 = 0;
    v25 = this + 24;
    do
    {
      if ( *(_BYTE *)(v24 + *(_DWORD *)(this + 4) + 577) )
      {
        *(_BYTE *)(*(_DWORD *)v25 + 280) = 0;
        *(_BYTE *)(*(_DWORD *)v25 + 274) = 0;
      }
      v24 += 892;
      v25 += 4;
    }
    while ( v24 < 9812 );
  }
  return 0;
}

// 0x004FD880
int sub_4FD880(int a2)
{
  int v3; // edi
  int v4; // eax
  int v5; // ebp
  const char *v7; // eax
  int v8; // eax
  void (__thiscall ***v9)(_DWORD, int); // ecx
  void (__thiscall ***v10)(_DWORD, _DWORD); // ecx
  int v11; // [esp-4h] [ebp-10h]

  v3 = 2632 * *((_DWORD *)this + 40);
  v4 = v3 + 80 * *((_DWORD *)this + 41);
  v5 = (int)this + v4 + 184;
  if ( !*((_BYTE *)this + v4 + 225) )
  {
    if ( *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    if ( *(_DWORD *)((char *)this + v3 + 2756) )
    {
      v11 = *(_DWORD *)((char *)this + v3 + 2756);
      if ( *(_DWORD *)((char *)this + v3 + 2752) == 270 )
      {
        v7 = (const char *)g_GDB->GDB_GetItemNum(v11);
        if ( *(_DWORD *)((char *)this + v3 + 2760) > 4u )
          UIWnd::SetEnable(*(_DWORD **)(*(_DWORD *)(*this + 4) + 1076), v7, 1);
        else
          UIWnd::SetEnable(*(_DWORD **)(*(_DWORD *)(*this + 4) + 1072), v7, 1);
      }
      else
      {
        v8 = g_GDB->GDB_GetRoleNum(v11);
        if ( *(_DWORD *)((char *)this + v3 + 2760) > 4u )
          UIWnd::SetEnable(*(_DWORD **)(*(_DWORD *)(*this + 4) + 1076), (const char *)(v8 + 28), 1);
        else
          UIWnd::SetEnable(*(_DWORD **)(*(_DWORD *)(*this + 4) + 1072), (const char *)(v8 + 28), 1);
      }
    }
    if ( *(_DWORD *)((char *)this + v3 + 2760) > 4u )
      v9 = *(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(*this + 4) + 1076);
    else
      v9 = *(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(*this + 4) + 1072);
    (**v9)(v9, 1);
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || *(float *)(*this + 80) - *(float *)(v5 + 24) > *(float *)(v5 + 32)
    || *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) )
  {
    if ( *(_DWORD *)((char *)this + v3 + 2760) > 4u )
      v10 = *(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)(*this + 4) + 1076);
    else
      v10 = *(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)(*this + 4) + 1072);
    (**v10)(v10, 0);
    *(_DWORD *)(v5 + 16) = 4;
  }
  return 0;
}

// 0x004FDA10
int sub_4FDA10(int a2)
{
  int v3; // edi
  int v4; // eax
  int v5; // ebp
  int v6; // eax
  void (__thiscall ***v7)(_DWORD, int); // ecx
  void (__thiscall ***v8)(_DWORD, _DWORD); // ecx

  v3 = 2632 * *((_DWORD *)this + 40);
  v4 = v3 + 80 * *((_DWORD *)this + 41);
  v5 = (int)this + v4 + 184;
  if ( !*((_BYTE *)this + v4 + 225) )
  {
    v6 = g_GDB->GDB_GetSkillNum(*(_DWORD *)((char *)this + v4 + 228));
    if ( *(_DWORD *)((char *)this + v3 + 2760) > 4u )
    {
      UIWnd::SetEnable(*(_DWORD **)(*(_DWORD *)(*this + 4) + 1076), (const char *)(v6 + 4), 1);
      v7 = *(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(*this + 4) + 1076);
    }
    else
    {
      UIWnd::SetEnable(*(_DWORD **)(*(_DWORD *)(*this + 4) + 1072), (const char *)(v6 + 4), 1);
      v7 = *(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(*this + 4) + 1072);
    }
    (**v7)(v7, 1);
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1 || *(float *)(*this + 80) - *(float *)(v5 + 24) > *(float *)(v5 + 32) )
  {
    if ( *(_DWORD *)((char *)this + v3 + 2760) > 4u )
      v8 = *(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)(*this + 4) + 1076);
    else
      v8 = *(void (__thiscall ****)(_DWORD, _DWORD))(*(_DWORD *)(*this + 4) + 1072);
    (**v8)(v8, 0);
    *(_DWORD *)(v5 + 16) = 4;
  }
  return 0;
}

// 0x004FDB10
int CCBStage::GetRoleTaskNum(int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  char *v6; // esi
  char *v7; // ecx
  int *v8; // eax
  int v9; // ecx
  double v10; // st7
  double v11; // st7
  double v12; // st7
  int v13; // eax
  char v14; // dl
  int v16; // [esp+8h] [ebp-20h] BYREF
  int v17; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  int v19; // [esp+14h] [ebp-14h]
  int v20; // [esp+18h] [ebp-10h]
  int v21; // [esp+1Ch] [ebp-Ch]
  float v22; // [esp+20h] [ebp-8h] BYREF
  float v23; // [esp+24h] [ebp-4h] BYREF

  v22 = 0.0;
  v23 = 0.0;
  v16 = 0;
  v3 = *(_DWORD *)&this->m_pCBSystem[160];
  v17 = 0;
  v18 = 0;
  v4 = 2632 * v3;
  v5 = v4 + 80 * *(_DWORD *)&this->m_pCBSystem[164];
  v6 = &this->m_pCBSystem[v5 + 184];
  if ( !this->m_pCBSystem[v5 + 225] )
  {
    v7 = &this->m_pCBSystem[v4 + 2760];
    *(float *)&this->m_pCBSystem[4 * *(_DWORD *)v7 + 104] = *(float *)&this->m_pCBSystem[4 * *(_DWORD *)v7 + 104] + 10.0;
    v8 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)v7 + 24] + 6584);
    v16 = *v8;
    v17 = v8[1];
    v18 = v8[2];
    *((_DWORD *)v6 + 16) = v16;
    *((_DWORD *)v6 + 17) = v18;
    v20 = *(int *)&this->m_pCBSystem[4 * *(_DWORD *)v7 + 104];
    v21 = (int)*(float *)&v20;
    *((float *)v6 + 18) = *(float *)&v21;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *((_DWORD *)v6 + 19) = (g_RandSeed >> 16) & 0x1F;
    v6[41] = 1;
  }
  v16 = *((_DWORD *)v6 + 16);
  v18 = *((_DWORD *)v6 + 17);
  v9 = *(_DWORD *)&this->m_pCBSystem[12];
  v17 = 1112014848;
  (gbCamera *->PointWorldToScr()(v9 + 4), (struct gbVec3D *)&v16, &v22, &v23);
  sprintf(byte_17AA920, "%d", *((_DWORD *)v6 + 11));
  v10 = (*(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6)) / *((float *)v6 + 8);
  if ( v10 > 1.0 )
    v10 = 1.0;
  *(float *)&v21 = (1.0 - v10) * 255.0;
  v20 = (int)*(float *)&v21;
  *(float *)&v21 = (*(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6)) * 30.0;
  v19 = (int)*(float *)&v21;
  v11 = (double)MEMORY[0xBFD6D4];
  v19 = *((_DWORD *)v6 + 18) - (__int64)((1.0 - v23) * v11 * -0.5) - v19;
  v23 = 1.0 - ((double)v19 + (double)v19) / v11;
  v12 = (double)MEMORY[0xBFD6D0];
  v19 = *((_DWORD *)v6 + 19) - (__int64)((v22 + 1.0) * v12 * -0.5) - 16;
  v22 = ((double)v19 + (double)v19) / v12 - 1.0;
  v13 = *((_DWORD *)v6 + 13);
  if ( v13 )
  {
    v14 = v6[52];
    BYTE1(v21) = BYTE1(*((_DWORD *)v6 + 13));
    BYTE2(v21) = BYTE2(v13);
    LOBYTE(v21) = v14;
  }
  else
  {
    *(_WORD *)((char *)&v21 + 1) = 12850;
    LOBYTE(v21) = -1;
  }
  HIBYTE(v21) = v20;
  CCBStage::InitRound(*(CCBStage **)&this->m_pCBSystem[68]);
  if ( *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6) > *((float *)v6 + 8) )
    *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FDD90
int CCBStage::SelectRole(int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  char *v6; // esi
  int v7; // eax
  double v8; // st7
  double v9; // st7
  double v10; // st7
  float v11; // edx
  int v13; // [esp+8h] [ebp-20h] BYREF
  float v14; // [esp+Ch] [ebp-1Ch]
  int v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  int v17; // [esp+18h] [ebp-10h]
  int v18; // [esp+1Ch] [ebp-Ch]
  float v19; // [esp+20h] [ebp-8h] BYREF
  float v20; // [esp+24h] [ebp-4h] BYREF

  v19 = 0.0;
  v20 = 0.0;
  v13 = 0;
  v3 = *(_DWORD *)&this->m_pCBSystem[160];
  v14 = 0.0;
  v15 = 0;
  v4 = 2632 * v3;
  v5 = v4 + 80 * *(_DWORD *)&this->m_pCBSystem[164];
  v6 = &this->m_pCBSystem[v5 + 184];
  if ( !this->m_pCBSystem[v5 + 225] )
  {
    v7 = *(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)&this->m_pCBSystem[v4 + 2760] + 24] + 6596;
    v13 = *(_DWORD *)v7;
    v14 = *(float *)(v7 + 4);
    v15 = *(_DWORD *)(v7 + 8);
    v14 = v14 + 80.0;
    *(_DWORD *)&this->m_pCBSystem[v5 + 248] = v13;
    *(float *)&this->m_pCBSystem[v5 + 252] = v14;
    *(_DWORD *)&this->m_pCBSystem[v5 + 256] = v15;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *(_DWORD *)&this->m_pCBSystem[v5 + 260] = (g_RandSeed >> 16) & 0x1F;
    this->m_pCBSystem[v5 + 225] = 1;
  }
  v13 = *(_DWORD *)&this->m_pCBSystem[v5 + 248];
  v14 = *(float *)&this->m_pCBSystem[v5 + 252];
  v15 = *(_DWORD *)&this->m_pCBSystem[v5 + 256];
  (gbCamera *->PointWorldToScr()(*(_DWORD *)&this->m_pCBSystem[12] + 4), (struct gbVec3D *)&v13, &v19, &v20);
  v8 = (*(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6)) / *((float *)v6 + 8);
  *(float *)&v18 = v8;
  if ( v8 > 1.0 )
    *(float *)&v18 = 1.0;
  *(float *)&v17 = (1.0 - *(float *)&v18) * 255.0;
  v16 = (int)*(float *)&v17;
  *(float *)&v17 = *(float *)&v18 * 32.0;
  v18 = (int)*(float *)&v17;
  v9 = (double)MEMORY[0xBFD6D4];
  v17 = 16 - (__int64)((1.0 - v20) * v9 * -0.5) - v18;
  v20 = 1.0 - ((double)v17 + (double)v17) / v9;
  v10 = (double)MEMORY[0xBFD6D0];
  LODWORD(v11) = *((_DWORD *)v6 + 19) - (__int64)((v19 + 1.0) * v10 * -0.5) - 16;
  *(_WORD *)((char *)&v18 + 1) = 13055;
  *(float *)&v17 = v11;
  LOBYTE(v18) = -1;
  HIBYTE(v18) = v16;
  v19 = ((double)v17 + (double)v17) / v10 - 1.0;
  CCBStage::InitRound(*(CCBStage **)&this->m_pCBSystem[68]);
  if ( *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6) > *((float *)v6 + 8) )
    *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FDFC0
int sub_4FDFC0(int a2)
{
  _DWORD *v2; // esi
  int v3; // eax
  int v4; // ecx
  _DWORD *v5; // eax
  int v6; // ebx
  int *v7; // eax
  int v8; // eax
  gbCamera *v9; // ecx
  double v10; // st7
  double v11; // st7
  double v12; // st7
  int v13; // edx
  char *v15; // [esp-8h] [ebp-B8h]
  char *v16; // [esp-4h] [ebp-B4h]
  int v17; // [esp-4h] [ebp-B4h]
  char Buffer[128]; // [esp+Ch] [ebp-A4h] BYREF
  int v19; // [esp+8Ch] [ebp-24h]
  _DWORD *v20; // [esp+90h] [ebp-20h]
  int v21; // [esp+94h] [ebp-1Ch] BYREF
  int v22; // [esp+98h] [ebp-18h]
  int v23; // [esp+9Ch] [ebp-14h]
  int v24; // [esp+A0h] [ebp-10h]
  float v25; // [esp+A4h] [ebp-Ch]
  float v26; // [esp+A8h] [ebp-8h] BYREF
  float v27; // [esp+ACh] [ebp-4h] BYREF

  v2 = this;
  v26 = 0.0;
  v27 = 0.0;
  v21 = 0;
  v3 = *((_DWORD *)this + 40);
  v22 = 0;
  v23 = 0;
  v20 = this;
  v4 = 329 * v3;
  v5 = &v20[20 * v20[41]];
  v6 = (int)&v5[2 * v4 + 46];
  if ( !BYTE1(v5[2 * v4 + 56]) )
  {
    *(float *)&v2[v5[2 * v4 + 58] + 26] = *(float *)&v2[v5[2 * v4 + 58] + 26] + 10.0;
    v7 = (int *)(v2[v5[2 * v4 + 58] + 6] + 6596);
    v21 = *v7;
    v22 = v7[1];
    v23 = v7[2];
    v8 = *(_DWORD *)(v6 + 48);
    *(_DWORD *)(v6 + 64) = v21;
    *(_DWORD *)(v6 + 68) = v23;
    v24 = v2[v8 + 26];
    LODWORD(v25) = (int)*(float *)&v24;
    *(float *)(v6 + 72) = v25;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *(_DWORD *)(v6 + 76) = (g_RandSeed >> 16) & 0x1F;
    *(_BYTE *)(v6 + 41) = 1;
  }
  v21 = *(_DWORD *)(v6 + 64);
  v23 = *(_DWORD *)(v6 + 68);
  v9 = (gbCamera *)(v2[3] + 4);
  v22 = 1112014848;
  v9->PointWorldToScr((struct gbVec3D *)&v21, &v26, &v27);
  v10 = (*(float *)(*v2 + 80) - *(float *)(v6 + 24)) / *(float *)(v6 + 32);
  if ( v10 > 1.0 )
    v10 = 1.0;
  v25 = (1.0 - v10) * 255.0;
  v19 = (int)v25;
  v25 = (*(float *)(*v2 + 80) - *(float *)(v6 + 24)) * 30.0;
  v24 = (int)v25;
  v11 = (double)MEMORY[0xBFD6D4];
  LODWORD(v25) = *(_DWORD *)(v6 + 72) - (__int64)((1.0 - v27) * v11 * -0.5) - v24;
  v27 = 1.0 - ((double)SLODWORD(v25) + (double)SLODWORD(v25)) / v11;
  v12 = (double)MEMORY[0xBFD6D0];
  v13 = *(_DWORD *)(v6 + 76) - (__int64)((v26 + 1.0) * v12 * -0.5);
  *(_WORD *)((char *)&v24 + 1) = 13055;
  LODWORD(v25) = v13 - 32;
  LOBYTE(v24) = -1;
  HIBYTE(v24) = v19;
  v26 = ((double)SLODWORD(v25) + (double)SLODWORD(v25)) / v12 - 1.0;
  if ( *(_DWORD *)(v6 + 44) == 1 )
  {
    v17 = *(_DWORD *)(v6 + 52);
    v15 = PalScript::SetAppName(&MEMORY[0x8ACD30], aWitch);
    sprintf(Buffer, "%s -%d", v15, v17);
  }
  else if ( *(_DWORD *)(v6 + 44) == 2 )
  {
    v16 = PalScript::SetAppName(&MEMORY[0x8ACD30], aMoney);
    sprintf(Buffer, "%d%s", *(_DWORD *)(v6 + 52), v16);
  }
  else
  {
    strcpy(Buffer, MEMORY[0xC10D38]);
    v2 = v20;
  }
  (char *->InitRound()v2[17], Buffer, v26, v27, v24);
  if ( *(float *)(*v2 + 80) - *(float *)(v6 + 24) > *(float *)(v6 + 32) )
    *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FE290
int sub_4FE290(const char **this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  double v8; // st7
  double v9; // st7
  double v10; // st7
  __int64 v11; // rax
  float v12; // ebx
  int v13; // eax
  int v15; // [esp-4h] [ebp-34h]
  const char *v16; // [esp+Ch] [ebp-24h] BYREF
  float v17; // [esp+10h] [ebp-20h]
  const char *v18; // [esp+14h] [ebp-1Ch]
  int v19; // [esp+18h] [ebp-18h]
  float v20; // [esp+1Ch] [ebp-14h]
  int v21; // [esp+20h] [ebp-10h]
  float v22; // [esp+24h] [ebp-Ch] BYREF
  float v23; // [esp+28h] [ebp-8h] BYREF
  int v24; // [esp+2Ch] [ebp-4h] BYREF

  v22 = 0.0;
  v23 = 0.0;
  v3 = (int)*((_DWORD *)this + 40);
  v16 = 0;
  v17 = 0.0;
  v18 = 0;
  v4 = 2632 * v3;
  v5 = v4 + 80 * (_DWORD)*((_DWORD *)this + 41);
  v6 = (int)this + v5 + 184;
  if ( !*((_BYTE *)this + v5 + 225) )
  {
    v7 = (int)(*(this + *(_DWORD *)((char *)this + v4 + 2760) + 6) + 6584);
    v16 = *(const char **)v7;
    v17 = *(float *)(v7 + 4);
    v18 = *(const char **)(v7 + 8);
    v17 = v17 + 80.0;
    *(const char **)((char *)this + v5 + 248) = v16;
    *(float *)((char *)this + v5 + 252) = v17;
    *(const char **)((char *)this + v5 + 256) = v18;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *(const char **)((char *)this + v5 + 260) = (const char *)((g_RandSeed >> 16) & 0x1F);
    *((_BYTE *)this + v5 + 225) = 1;
  }
  v16 = *(const char **)((char *)this + v5 + 248);
  v17 = *(float *)((char *)this + v5 + 252);
  v18 = *(const char **)((char *)this + v5 + 256);
  (gbCamera *->PointWorldToScr()(*((_DWORD *)this + 3) + 4), (struct gbVec3D *)&v16, &v22, &v23);
  v8 = (*((float *)*this + 20) - *(float *)(v6 + 24)) / *(float *)(v6 + 32);
  *(float *)&v21 = v8;
  if ( v8 > 1.0 )
    *(float *)&v21 = 1.0;
  v20 = (1.0 - *(float *)&v21) * 255.0;
  v19 = (int)v20;
  v20 = *(float *)&v21 * 32.0;
  v9 = (double)MEMORY[0xBFD6D4];
  v21 = 16 - (__int64)((1.0 - v23) * v9 * -0.5);
  v23 = 1.0 - ((double)v21 + (double)v21) / v9;
  v10 = (double)MEMORY[0xBFD6D0];
  v11 = (__int64)((v22 + 1.0) * v10 * -0.5);
  HIDWORD(v11) = *this;
  LODWORD(v12) = *(_DWORD *)(v6 + 76) - v11 - 16;
  v20 = v12;
  HIBYTE(v24) = v19;
  *(_WORD *)((char *)&v24 + 1) = 13055;
  LOBYTE(v24) = -1;
  v22 = ((double)SLODWORD(v12) + (double)SLODWORD(v12)) / v10 - 1.0;
  (***(void (__thiscall ****)(_DWORD, int))(*(_DWORD *)(HIDWORD(v11) + 4) + 1080))(
    *(_DWORD *)(*(_DWORD *)(HIDWORD(v11) + 4) + 1080),
    1);
  UIWnd::SetEnable(*(_DWORD **)(*((_DWORD *)*this + 1) + 1080), *((_DWORD *)this + 1), 0);
  v15 = v24;
  v13 = CCBStage::ProcShowEnemyFiveLineup(*this);
  NPC::UpdateAnim(*(_DWORD **)(v13 + 1080), v15);
  UIWnd::GetChild(*(_DWORD **)(*((_DWORD *)*this + 1) + 1080), &v24);
  UIWnd::ScreenToClient(*(_DWORD **)(*((_DWORD *)*this + 1) + 1080), LODWORD(v12) - 168, v21 - 128);
  UIWnd::SetShow(*(_DWORD **)(*((_DWORD *)*this + 1) + 1080), 0);
  if ( *(_BYTE *)(v6 + 43) == 1 || *((float *)*this + 20) - *(float *)(v6 + 24) > *(float *)(v6 + 32) )
  {
    (***(void (__thiscall ****)(_DWORD, _DWORD))(*((_DWORD *)*this + 1) + 1080))(
      *(_DWORD *)(*((_DWORD *)*this + 1) + 1080),
      0);
    *(_DWORD *)(v6 + 16) = 4;
  }
  return 0;
}

// 0x004FE540
int sub_4FE540()
{
  return *((_DWORD *)this + 1);
}

// 0x004FE550
int sub_4FE550(int a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // edi
  int v6; // ecx

  v3 = 2632 * *((_DWORD *)this + 40);
  v4 = v3 + 80 * *((_DWORD *)this + 41);
  v5 = (int)this + v4 + 184;
  if ( !*((_BYTE *)this + v4 + 225) )
  {
    v6 = *(this + *(_DWORD *)((char *)this + v3 + 2760) + 6);
    if ( !*(_BYTE *)(v6 + 373) || !*(_BYTE *)(v6 + 374) )
    {
      if ( *(_BYTE *)(v6 + 373) == 1 )
        CCBStageRole::GetCurrentTaskIndex();
      CCBStageRole::DelAllTask(*(this + 658 * *((_DWORD *)this + 40) + 686), 1);
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
    }
  }
  return 0;
}

// 0x004FE600
int sub_4FE600(int a2)
{
  int v2; // eax
  int v3; // edx
  int v4; // esi

  v2 = 2632 * *((_DWORD *)this + 40);
  v3 = v2 + 80 * *((_DWORD *)this + 41);
  v4 = (int)this + v3 + 184;
  if ( !*((_BYTE *)this + v3 + 225) )
  {
    CCBStageRole::GetCurrentTask(*(_DWORD *)((char *)this + v2 + 2744));
    *(_BYTE *)(v4 + 41) = 1;
    *(_DWORD *)(v4 + 16) = 4;
  }
  return 0;
}

// 0x004FE660
int CCBStage::ProcShowSneakAttackState(int this, int a2)
{
  int v3; // eax
  int v4; // ebp
  int v5; // edi
  unsigned int v7; // eax
  _DWORD *v8; // ecx
  _DWORD *v9; // ecx
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  double v13; // st7
  int v14; // eax
  _DWORD *inited; // eax
  int i; // ebx
  int v17; // eax
  _BYTE *v18; // ecx
  int v19; // eax
  int v20; // ebx
  float *v21; // ecx
  float *v22; // eax
  double v23; // st7
  double v24; // st7
  int RoleIndex; // edi
  char v26; // [esp+13h] [ebp-5Dh]
  int v27; // [esp+14h] [ebp-5Ch]
  unsigned int v28; // [esp+18h] [ebp-58h] BYREF
  float v29; // [esp+1Ch] [ebp-54h] BYREF
  float v30[3]; // [esp+20h] [ebp-50h] BYREF
  float v31; // [esp+2Ch] [ebp-44h] BYREF
  float v32; // [esp+30h] [ebp-40h]
  float v33; // [esp+34h] [ebp-3Ch]
  _DWORD v34[3]; // [esp+38h] [ebp-38h] BYREF
  _DWORD v35[11]; // [esp+44h] [ebp-2Ch] BYREF

  memset(v30, 0, sizeof(v30));
  v3 = 2632 * *(_DWORD *)(this + 160);
  v4 = v3 + this + 2752;
  v5 = v3 + 80 * *(_DWORD *)(this + 164) + this + 184;
  v27 = v5;
  if ( !CCBStageRole::IsReady(
          *(CCBStageRole **)(this + 4 * *(_DWORD *)(v3 + this + 2760) + 24),
          *(_DWORD *)(v3 + this + 2744)) )
  {
    *(_DWORD *)(v5 + 16) = 4;
    return 0;
  }
  if ( !*(_BYTE *)(v5 + 41) && CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)(this + 4 * *(_DWORD *)(v4 + 8) + 24)) )
  {
    (CCBStage *->ResetAll()this);
    v7 = *(_DWORD *)(v4 + 8);
    if ( v7 <= 4 && *(_BYTE *)(*(_DWORD *)&g_SceneMgr.m_info[1408 * v7 + 936] + 613) == 5
      || *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(v4 + 8)) == 7366 )
    {
      v28 = *(_DWORD *)(v4 + 12);
      if ( v28 <= 0xA )
      {
        v8 = sub_50E160;
        v30[0] = (float)(int)v28;
LABEL_25:
        CCBStageRole::GetProperCurAction(
          *(CCBStageRole **)(this + 4 * *(_DWORD *)(v4 + 8) + 24),
          v8,
          0,
          0,
          0,
          *(_DWORD **)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
          (int *)v30,
          (const void *)v4,
          (_DWORD *)1);
        goto LABEL_26;
      }
      v9 = *(_DWORD **)(this + 4);
      v29 = NAN;
      v28 = -1;
      if ( (unsigned int)v9->WriteBackRoleData(v4, &v29, (int *)&v28) <= 0xA )
      {
        v8 = sub_50E160;
        v30[0] = (float)*(int *)(v4 + 12);
        goto LABEL_25;
      }
    }
    else
    {
      v10 = *(_DWORD *)(v4 + 8);
      if ( v10 > 4 )
      {
        if ( *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(v4 + 8)) == 720 )
        {
          v8 = CCBStageRole::ProcMagic;
        }
        else if ( *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(v4 + 8)) == 738
               || (inited = (_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *(_DWORD *)(v4 + 8)),
                   v8 = CCBStageRole::ProcTurnToRole,
                   *inited == 739) )
        {
          v8 = CCBStageRole::ProcBlock;
        }
        goto LABEL_25;
      }
      v11 = v10 - 1;
      if ( v11 )
      {
        v12 = v11 - 1;
        if ( v12 )
        {
          if ( v12 == 1 )
          {
            v13 = (float *->AddTask()*(_DWORD *)(this + 36), v30);
            v14 = *(_DWORD *)(this + 160);
            v29 = v13;
            CCBStageRole::GetProperCurAction(
              *(CCBStageRole **)(this + 4 * *(_DWORD *)(v4 + 8) + 24),
              sub_50E360,
              0,
              0,
              0,
              *(_DWORD **)(this + 2632 * v14 + 2744),
              (int *)v30,
              (const void *)v4,
              (_DWORD *)1);
            CCBStageRole::GetProperCurAction(
              *(CCBStageRole **)(this + 4 * *(_DWORD *)(v4 + 8) + 24),
              CCBStage::CheckAllDone,
              0,
              0,
              0,
              *(_DWORD **)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
              (int *)v30,
              (const void *)v4,
              (_DWORD *)1);
            v8 = CCBStage::ProcessCommand;
            v30[0] = v29;
            goto LABEL_25;
          }
        }
        else
        {
          CCBStageRole::GetProperCurAction(
            *(CCBStageRole **)(this + 32),
            CCBStageRole::ProcMagic,
            0,
            0,
            0,
            *(_DWORD **)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
            (int *)v30,
            (const void *)v4,
            (_DWORD *)1);
        }
        v8 = CCBStageRole::ProcTurnToRole;
        goto LABEL_25;
      }
      CCBStageRole::GetProperCurAction(
        *(CCBStageRole **)(this + 28),
        CCBStageRole::ProcUseRecoverItem,
        0,
        0,
        0,
        *(_DWORD **)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
        (int *)v30,
        (const void *)v4,
        (_DWORD *)1);
    }
LABEL_26:
    *(_DWORD *)(v5 + 64) = 1;
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( CCBStageRole::IsActive(*(CCBStageRole **)(this + 4), *(_DWORD *)(v4 + 8)) )
  {
    v26 = 1;
    if ( *(_BYTE *)(v4 + 17) )
    {
      for ( i = 0; i < 11; ++i )
      {
        if ( *(_BYTE *)(i + v4 + 29) && CCBRoleState::IsRoleAlive(*(CCBRoleState **)(this + 4), i) )
          v26 = 0;
      }
      if ( v26 )
        goto LABEL_35;
    }
    else if ( !CCBRoleState::IsRoleAlive(*(CCBRoleState **)(this + 4), *(_DWORD *)(v4 + 12)) )
    {
LABEL_35:
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
  }
  if ( *(_DWORD *)(v5 + 64) == 1 )
  {
    v17 = *(_DWORD *)(v4 + 8);
    if ( v17 >= 5 && v17 < 11 )
    {
      v18 = *(_BYTE **)(this + 4);
      if ( v18[577] )
      {
        if ( *(int *)(v18->InitUI(0) + 84) >= 0
          && *(int *)(CCBRoleState::InitUI(*(void **)(this + 4), 0) + 84) < 11 )
        {
          v19 = CCBRoleState::InitUI(*(void **)(this + 4), 0);
          if ( sub_4F06C0(v4, *(_DWORD *)(v19 + 84)) )
          {
            v20 = *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), 0) + 84);
            v21 = (float *)(*(_DWORD *)(this + 4 * v20 + 24) + 6584);
            v22 = (float *)(*(_DWORD *)(this + 4 * *(_DWORD *)(v4 + 8) + 24) + 6584);
            v31 = *v21 - *v22;
            v32 = v21[1] - v22[1];
            v23 = v21[2] - v22[2];
            *(float *)&v34[1] = v32;
            v33 = v23;
            *(float *)v34 = v31;
            *(float *)&v34[2] = v33;
            v24 = (gbVec3D *->Length()v34);
            if ( v24 < 120.0 && v24 > 50.0 )
            {
              if ( sub_4EED60(*(_DWORD *)(this + 4), v20) )
              {
                memset(v35, 0, sizeof(v35));
                v35[2] = 0;
                v35[1] = 0;
                v35[3] = v20;
                RoleIndex = (_DWORD *->GetRoleIndex()this, 18, v35, 1);
                if ( RoleIndex != -1 )
                {
                  v31 = *(float *)(v4 + 8);
                  v32 = *(float *)&v35[2];
                  v33 = *(float *)&v35[3];
                  (_DWORD *->GetRoleName()this,
                    RoleIndex,
                    (int)CCBStage::ProcFiveLienupFadeIn,
                    0,
                    0,
                    0,
                    &v31,
                    -1082130432,
                    0);
                  (_DWORD *->GetRoleName()this, RoleIndex, (int)sub_500840, 0, 0, 0, &v31, -1082130432, 0);
                  (_DWORD *->GetRoleName()this, RoleIndex, (int)sub_5009C0, 0, 0, 0, &v31, -1082130432, 0);
                  (_DWORD *->GetRoleName()this, RoleIndex, (int)sub_500AD0, 0, 0, 0, &v31, -1082130432, 0);
                  (_DWORD *->GetRoleName()this,
                    RoleIndex,
                    (int)CCBStage::ProcFiveLienupFadeOut,
                    0,
                    0,
                    0,
                    &v31,
                    -1082130432,
                    0);
                  *(_DWORD *)(v27 + 64) = 0;
                  (CCBSystem *->GetStageRoleByIdx()this, RoleIndex);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)(this + 4 * *(_DWORD *)(v4 + 8) + 24)) || *(_BYTE *)(v27 + 43) == 1 )
    *(_DWORD *)(v27 + 16) = 4;
  return 0;
}

// 0x004FECE0
int sub_4FECE0(int a2)
{
  int v3; // edi
  int *v4; // ebp
  int v5; // ebx

  if ( (byte_17AA91C & 1) == 0 )
  {
    dword_17AA910 = 0;
    byte_17AA91C |= 1u;
    dword_17AA914 = 0;
    dword_17AA918 = 0;
    atexit(nullsub_21);
  }
  v3 = 2632 * *((_DWORD *)this + 40);
  v4 = (_DWORD *)((char *)this + v3 + 2760);
  v5 = (int)this + 80 * *((_DWORD *)this + 41) + v3 + 184;
  if ( (unsigned __int8)CCBStageRole::IsReady(*(_DWORD *)((char *)this + v3 + 2744)) )
  {
    if ( !*(_BYTE *)(v5 + 41) && (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(this + *v4 + 6)) == 1 )
    {
      *(float *)&dword_17AA910 = (float)*v4;
      *(float *)&dword_17AA914 = (float)*(int *)((char *)this + v3 + 2764);
      sub_50E550->GetProperCurAction(0, 0, 0, *(this + 658 * *((_DWORD *)this + 40) + 686),
        &dword_17AA910,
        this + 658 * *((_DWORD *)this + 40) + 688,
        1);
      *(_BYTE *)(v5 + 41) = 1;
    }
    if ( (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(this + *v4 + 6)) == 1 )
      *(_DWORD *)(v5 + 16) = 4;
    if ( *(_BYTE *)(v5 + 43) == 1 )
      *(_DWORD *)(v5 + 16) = 4;
    return 0;
  }
  else
  {
    *(_DWORD *)(v5 + 16) = 4;
    return 0;
  }
}

// 0x004FEE60
int sub_4FEE60(int a2)
{
  int v2; // edx
  int v3; // esi

  v2 = 2632 * *((_DWORD *)this + 40) + 80 * *((_DWORD *)this + 41);
  v3 = (int)this + v2 + 184;
  if ( !*((_BYTE *)this + v2 + 225) )
  {
    sub_50EB00->ProcTransportRun(0, 0, 0, 0, 0, 3);
    *(_BYTE *)(v3 + 41) = 1;
    *(_DWORD *)(v3 + 16) = 4;
  }
  if ( *(_BYTE *)(v3 + 43) == 1 )
    *(_DWORD *)(v3 + 16) = 4;
  return 0;
}

// 0x004FEFB0
int sub_4FEFB0(int this, int a2)
{
  int v3; // eax
  int *v4; // edi
  int v5; // ebx
  int v7; // eax
  int v8; // ecx
  int (__stdcall *v9)(int); // edx
  double v10; // st7
  int v11; // eax
  float v12[3]; // [esp+14h] [ebp-Ch] BYREF

  v3 = 2632 * *(_DWORD *)(this + 160);
  v4 = (int *)(v3 + this + 2760);
  v5 = v3 + 80 * *(_DWORD *)(this + 164) + this + 184;
  if ( !(unsigned __int8)CCBStageRole::IsReady(*(_DWORD *)(v3 + this + 2744)) )
  {
    *(_DWORD *)(v5 + 16) = 4;
    return 0;
  }
  if ( !*(_BYTE *)(v5 + 41) && (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(_DWORD *)(this + 4 * *v4 + 24)) == 1 )
  {
    v7 = *v4;
    if ( *v4 >= 0 && v7 < 5 )
    {
      switch ( v7 )
      {
        case 1:
          v8 = *(_DWORD *)(this + 28);
          v9 = (int (__stdcall *)(int))CCBStageRole::ProcUseRecoverItem;
          break;
        case 2:
          v8 = *(_DWORD *)(this + 32);
          v9 = CCBStageRole::ProcMagic;
          break;
        case 3:
          v8 = *(_DWORD *)(this + 36);
          v9 = (int (__stdcall *)(int))CCBStage::CheckAllDone;
          break;
        default:
          v8 = *(_DWORD *)(this + 4 * v7 + 24);
          v9 = CCBStageRole::ProcTurnToRole;
          break;
      }
      goto LABEL_22;
    }
    if ( *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *v4) == 720 )
    {
      v9 = CCBStageRole::ProcMagic;
    }
    else
    {
      if ( *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *v4) != 738
        && *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *v4) != 739 )
      {
        v9 = CCBStageRole::ProcTurnToRole;
        v8 = *(_DWORD *)(this + 4 * *v4 + 24);
LABEL_22:
        v9->GetProperCurAction(0, 0, 0, *(_DWORD *)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
          v8 + 6596,
          0,
          1);
        v10 = *(float *)(*(_DWORD *)(this + 4 * *v4 + 24) + 6636);
        v12[1] = 0.0;
        v11 = *(_DWORD *)(this + 160);
        v12[0] = v10;
        v12[2] = 0.0;
        CCBStageRole::GetProperCurAction(
          CCBStage::ProcessCommand,
          0,
          0,
          0,
          *(_DWORD *)(this + 2632 * v11 + 2744),
          v12,
          0,
          1);
        *(_BYTE *)(v5 + 41) = 1;
        goto LABEL_23;
      }
      v9 = CCBStageRole::ProcBlock;
    }
    v8 = *(_DWORD *)(this + 4 * *v4 + 24);
    goto LABEL_22;
  }
LABEL_23:
  if ( (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(_DWORD *)(this + 4 * *v4 + 24)) == 1 )
    *(_DWORD *)(v5 + 16) = 4;
  if ( *(_BYTE *)(v5 + 43) == 1 && !*(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), *v4) + 36) )
    *(_DWORD *)(v5 + 16) = 4;
  return 0;
}

// 0x004FF1B0
int sub_4FF1B0(int a2)
{
  int v3; // eax
  _DWORD *v4; // ebp
  int v5; // edi
  int (__stdcall *v6)(int); // edx
  double v7; // st7
  int v8; // eax
  float v10[3]; // [esp+18h] [ebp-Ch] BYREF

  v3 = 2632 * *((_DWORD *)this + 40);
  v4 = (_DWORD *)((char *)this + v3 + 2760);
  v5 = (int)this + 80 * *((_DWORD *)this + 41) + v3 + 184;
  if ( !(unsigned __int8)CCBStageRole::IsReady(*(_DWORD *)((char *)this + v3 + 2744)) )
    goto LABEL_13;
  if ( *(_BYTE *)(v5 + 41) || (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(this + *v4 + 6)) != 1 )
    goto LABEL_12;
  if ( *v4 == 1 )
    goto LABEL_9;
  if ( *v4 != 2 )
  {
    if ( *v4 != 3 )
    {
      v6 = CCBStageRole::ProcTurnToRole;
LABEL_10:
      v6->GetProperCurAction(0, 0, 0, *(this + 658 * *((_DWORD *)this + 40) + 686), *(this + *v4 + 6) + 6596, 0, 1);
      goto LABEL_11;
    }
LABEL_9:
    v6 = (int (__stdcall *)(int))CCBStageRole::ProcUseRecoverItem;
    goto LABEL_10;
  }
  CCBStageRole::GetProperCurAction(
    CCBStageRole::ProcMagic,
    0,
    0,
    0,
    *(this + 658 * *((_DWORD *)this + 40) + 686),
    *((_DWORD *)this + 8) + 6596,
    0,
    1);
LABEL_11:
  v7 = *(float *)(*(this + *v4 + 6) + 6636);
  v10[1] = 0.0;
  v8 = *((_DWORD *)this + 40);
  v10[0] = v7;
  v10[2] = 0.0;
  CCBStageRole::GetProperCurAction(CCBStage::ProcessCommand, 0, 0, 0, *(this + 658 * v8 + 686), v10, 0, 1);
  *(_BYTE *)(v5 + 41) = 1;
LABEL_12:
  if ( (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(this + *v4 + 6)) == 1 )
LABEL_13:
    *(_DWORD *)(v5 + 16) = 4;
  return 0;
}

// 0x004FF3D0
int sub_4FF3D0(int this, int a2)
{
  int v3; // ebp
  int v4; // eax
  char v5; // cl
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // ecx
  _DWORD *v10; // eax
  _DWORD *v11; // ecx
  int v12; // eax
  int v13; // eax
  _DWORD *v14; // ebp
  _BYTE *v15; // ecx
  int v16; // eax
  _DWORD *v17; // eax
  _DWORD *v18; // esi
  int v20; // [esp+8h] [ebp-4h]

  v3 = 2632 * *(_DWORD *)(this + 160);
  v4 = v3 + 80 * *(_DWORD *)(this + 164);
  v5 = *(_BYTE *)(v4 + this + 225);
  v6 = v4 + this + 184;
  v20 = v6;
  if ( !v5 )
  {
    v7 = 0;
    v8 = this + 24;
    do
    {
      if ( *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 4), v7) + 25)
        && *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 4), v7) + 26) )
      {
        v9 = 3 * *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), v7) + 584);
        v10 = (_DWORD *)(*(_DWORD *)v8 + 6584);
        v11 = (_DWORD *)(*(_DWORD *)(this + 20) + 4 * v9 + 92);
        *v10 = *v11;
        v10[1] = v11[1];
        v10[2] = v11[2];
        *(_DWORD *)(*(_DWORD *)v8 + 6632) = *(_DWORD *)(*(_DWORD *)v8 + 6636);
      }
      ++v7;
      v8 += 4;
    }
    while ( v7 < 5 );
    v12 = g_GDB->GDB_GetItemNum(*(_DWORD *)(this + v3 + 2756));
    if ( v12 )
    {
      if ( *(_BYTE *)(v12 + 592) == 2 )
      {
        v13 = *(_DWORD *)(this + v3 + 2764);
        v14 = (_DWORD *)(this + v3 + 2764);
        if ( v13 != -1 && v13 != 10 )
        {
          v15 = *(_BYTE **)(this + 4);
          if ( v15[9497] )
          {
            if ( !*(_BYTE *)(v15->InitUI(10) + 880) )
            {
              v16 = *(_DWORD *)(this + 64);
              if ( *(_BYTE *)(v16 + 272) )
              {
                *(_DWORD *)(v16 + 6584) = *(_DWORD *)(v16 + 6596);
                *(_DWORD *)(v16 + 6588) = *(_DWORD *)(v16 + 6600);
                *(_DWORD *)(v16 + 6592) = *(_DWORD *)(v16 + 6604);
                CCBStageRole::ForceRelease(0);
              }
            }
          }
          v17 = (_DWORD *)(*(_DWORD *)(this + 64) + 6596);
          v18 = (_DWORD *)(*(_DWORD *)(this + 4 * *v14 + 24) + 6584);
          *v18 = *v17;
          v18[1] = v17[1];
          v18[2] = v17[2];
        }
      }
    }
    v6 = v20;
    *(_BYTE *)(v20 + 41) = 1;
  }
  *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FF5C0
int sub_4FF5C0(int a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // ebp
  int v6; // esi
  int v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // ebx

  v3 = 2632 * *((_DWORD *)this + 40);
  v4 = v3 + 80 * *((_DWORD *)this + 41);
  v5 = (int)this + v3 + 2752;
  v6 = (int)this + v4 + 184;
  if ( !*((_BYTE *)this + v4 + 225) )
  {
    v7 = *(this + *(_DWORD *)((char *)this + v3 + 2760) + 6);
    *(_DWORD *)(v7 + 6632) = *(_DWORD *)(v7 + 6636);
    *((_BYTE *)this + v4 + 225) = 1;
    *(_DWORD *)((char *)this + v4 + 240) = CCBCamControl::KeepCurCam(*(_DWORD *)(v5 + 4));
    *(_BYTE *)(v6 + 62) = 0;
    *(_BYTE *)(v6 + 61) = 0;
    *(_BYTE *)(v6 + 60) = 0;
    *(_DWORD *)(v6 + 68) = 0;
    *(_DWORD *)(v6 + 64) = 0;
  }
  v8 = *(_DWORD *)(v6 + 56);
  v9 = *((_DWORD *)this + 19);
  v10 = v9 + 60 * v8 + 2444;
  if ( !*(_BYTE *)(v6 + 60) && *(float *)(*this + 80) - *(float *)(v6 + 24) >= *(float *)(v9 + 60 * v8 + 2468) )
  {
    *(_DWORD *)(v6 + 64) = CCBStageRole::~CCBStageRole(v8, 1, v5);
    *(_BYTE *)(v6 + 60) = 1;
  }
  if ( !*(_BYTE *)(v6 + 61) && *(float *)(*this + 80) - *(float *)(v6 + 24) >= *(float *)(v10 + 52) )
  {
    *(_DWORD *)(v6 + 68) = CCBStageRole::~CCBStageRole(*(_DWORD *)(v6 + 56), 2, v5);
    *(_BYTE *)(v6 + 61) = 1;
  }
  if ( !*(_BYTE *)(v6 + 62)
    && *(float *)(*this + 80) - *(float *)(v6 + 24) >= *(float *)(*((_DWORD *)this + 19) + 60 * *(_DWORD *)(v6 + 56) + 2472) )
  {
    CCBRoleState::RandSetEnemyPos(this + 658 * *((_DWORD *)this + 40) + 688);
    *(_BYTE *)(v6 + 62) = 1;
  }
  if ( (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(this + *(_DWORD *)(v5 + 8) + 6)) == 1
    && *(_BYTE *)(v6 + 62)
    && !CEffMgr::Render(*(char **)(*this + 44), *(_DWORD *)(v6 + 64))
    && !CEffMgr::Render(*(char **)(*this + 44), *(_DWORD *)(v6 + 68)) )
  {
    *(_DWORD *)(v6 + 16) = 4;
  }
  return 0;
}

// 0x004FF740
int sub_4FF740(int a2)
{
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // ebp
  int v7; // esi
  _DWORD *v8; // ebx
  _BYTE *v9; // ecx
  _DWORD *v10; // eax
  _BYTE *v11; // ecx
  int v13; // [esp+4h] [ebp-4h]

  v3 = 329 * *((_DWORD *)this + 40);
  v4 = 80 * *((_DWORD *)this + 41);
  v5 = (int)this + 8 * v3 + v4 + 184;
  v13 = v5;
  if ( !*((_BYTE *)this + 8 * v3 + v4 + 225) )
  {
    v6 = 0;
    v7 = 0;
    v8 = this + 6;
    do
    {
      v9 = (_BYTE *)*((_DWORD *)this + 1);
      if ( v9[v7 + 577] && !*(_BYTE *)(v9->InitUI(v6) + 880) )
      {
        v10 = (_DWORD *)*v8;
        v10[1646] = *(_DWORD *)(*v8 + 6596);
        v10[1647] = v10[1650];
        v10[1648] = v10[1651];
        *(_DWORD *)(*v8 + 6632) = *(_DWORD *)(*v8 + 6636);
      }
      v7 += 892;
      ++v6;
      ++v8;
    }
    while ( v7 < 9812 );
    v11 = (_BYTE *)*((_DWORD *)this + 1);
    if ( v11[9497] && !*(_BYTE *)(v11->InitUI(10) + 880) && *(_BYTE *)(*((_DWORD *)this + 16) + 272) )
      CCBStageRole::ForceRelease(1);
    v5 = v13;
    *(_BYTE *)(v13 + 41) = 1;
  }
  *(_DWORD *)(v5 + 16) = 4;
  return 0;
}

// 0x004FF840
int CCBStage::ProcGrabStageRole(int a2)
{
  int v3; // eax
  char *v4; // edi
  char *v5; // ebp
  int v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v13[6]; // [esp+14h] [ebp-1Ch] BYREF
  int v14; // [esp+2Ch] [ebp-4h]

  memset(v13, 0, 12);
  v3 = 2632 * *(_DWORD *)&this->m_pCBSystem[160];
  v4 = &this->m_pCBSystem[v3 + 2752];
  v5 = &this->m_pCBSystem[80 * *(_DWORD *)&this->m_pCBSystem[164] + 184 + v3];
  if ( !CCBStageRole::IsReady(
          *(CCBStageRole **)&this->m_pCBSystem[4 * *(_DWORD *)&this->m_pCBSystem[v3 + 2760] + 24],
          *(_DWORD *)&this->m_pCBSystem[v3 + 2744]) )
    goto LABEL_17;
  if ( !v5[41] )
  {
    if ( !CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24]) )
      return 0;
    CCBStageRole::GetState(*(CCBStageRole **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24]);
    v6 = *(_DWORD *)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24];
    *(_DWORD *)(v6 + 6632) = *(_DWORD *)(v6 + 6636);
    v7 = *((_DWORD *)v4 + 1);
    if ( v7 > 0x10D0 )
    {
      if ( v7 == 4505 )
      {
        this->ResetAll();
        v11 = *(_DWORD *)&this->m_pCBSystem[160];
        v14 = 0;
        CCBStageRole::GetProperCurAction(
          *(CCBStageRole **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24],
          CCBStageRole::ProcTurnToRole,
          0,
          0,
          0,
          *(_DWORD **)&this->m_pCBSystem[2632 * v11 + 2744],
          v13,
          v4,
          (_DWORD *)1);
      }
    }
    else if ( v7 == 4304 || (v8 = v7 - 4101) == 0 )
    {
      this->ResetAll();
      v10 = *(_DWORD *)&this->m_pCBSystem[160];
      v14 = 0;
      CCBStageRole::GetProperCurAction(
        *(CCBStageRole **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24],
        CCBStageRole::ProcMagic,
        0,
        0,
        0,
        *(_DWORD **)&this->m_pCBSystem[2632 * v10 + 2744],
        v13,
        v4,
        (_DWORD *)1);
    }
    else if ( v8 == 104 )
    {
      this->ResetAll();
      v9 = *(_DWORD *)&this->m_pCBSystem[160];
      v14 = 0;
      CCBStageRole::GetProperCurAction(
        *(CCBStageRole **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24],
        CCBStageRole::ProcUseRecoverItem,
        0,
        0,
        0,
        *(_DWORD **)&this->m_pCBSystem[2632 * v9 + 2744],
        v13,
        v4,
        (_DWORD *)1);
    }
    v5[41] = 1;
  }
  if ( CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24]) || v5[43] == 1 )
  {
    CCBStageRole::TryRelease(*(_DWORD *)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24]);
LABEL_17:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00503020
int CCBStage::ResetAll()
{
  int v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int *v7; // eax
  int v8; // ecx
  int *v9; // eax
  gbVec3D *v10; // eax
  int v11; // eax
  int *v12; // esi
  gbVec3D *v13; // eax
  gbVec3D *v14; // eax
  int v15; // edx
  int result; // eax
  int *v17; // eax
  int *v18; // eax
  gbVec3D *v19; // eax
  int v20; // eax
  int v21; // ebx
  gbVec3D *v22; // eax
  int v23; // ecx
  int v24; // edx
  int *v26; // eax
  int *v27; // eax
  gbVec3D *v28; // eax
  int v29; // eax
  gbVec3D *v30; // eax
  float v31; // [esp+18h] [ebp-38h]
  float v32; // [esp+18h] [ebp-38h]
  float v33; // [esp+18h] [ebp-38h]
  float v34; // [esp+18h] [ebp-38h]
  float v35; // [esp+18h] [ebp-38h]
  float v36; // [esp+18h] [ebp-38h]
  float v37; // [esp+18h] [ebp-38h]
  float v38; // [esp+1Ch] [ebp-34h]
  float v39; // [esp+1Ch] [ebp-34h]
  float v40; // [esp+1Ch] [ebp-34h]
  float v41; // [esp+1Ch] [ebp-34h]
  float v42; // [esp+1Ch] [ebp-34h]
  float v43; // [esp+1Ch] [ebp-34h]
  float v44; // [esp+1Ch] [ebp-34h]
  float v45; // [esp+20h] [ebp-30h]
  float v46; // [esp+20h] [ebp-30h]
  float v47; // [esp+20h] [ebp-30h]
  float v48; // [esp+20h] [ebp-30h]
  float v49; // [esp+20h] [ebp-30h]
  float v50; // [esp+20h] [ebp-30h]
  float v51; // [esp+20h] [ebp-30h]
  int v52; // [esp+24h] [ebp-2Ch]
  int v53; // [esp+24h] [ebp-2Ch]
  int v54; // [esp+24h] [ebp-2Ch]
  int v55; // [esp+24h] [ebp-2Ch]
  int v56; // [esp+30h] [ebp-20h] BYREF
  int v57; // [esp+34h] [ebp-1Ch] BYREF
  int v58; // [esp+38h] [ebp-18h] BYREF
  int v59; // [esp+3Ch] [ebp-14h]
  int v60; // [esp+40h] [ebp-10h]
  _BYTE v61[12]; // [esp+44h] [ebp-Ch] BYREF
  int *v62; // [esp+54h] [ebp+4h]
  int v63; // [esp+58h] [ebp+8h]

  if ( (byte_17AA89C & 1) == 0 )
  {
    dword_17AA890 = 0;
    byte_17AA89C |= 1u;
    dword_17AA894 = 0;
    dword_17AA898 = 0;
    atexit(nullsub_30);
  }
  if ( (byte_17AA89C & 2) == 0 )
  {
    dword_17AA880 = 0;
    byte_17AA89C |= 2u;
    dword_17AA884 = 0;
    dword_17AA888 = 0;
    atexit(nullsub_29);
  }
  if ( (byte_17AA89C & 4) == 0 )
  {
    dword_17AA870 = 0;
    byte_17AA89C |= 4u;
    dword_17AA874 = 0;
    dword_17AA878 = 0;
    atexit(nullsub_28);
  }
  v2 = v63;
  v56 = -1;
  v57 = -1;
  v3 = *(_DWORD *)(v63 + 12);
  if ( v3 == -1 )
  {
    v4 = CCBRoleState::WriteBackRoleData(*(_DWORD **)&this->m_pCBSystem[4], v63, &v56, &v57);
    v5 = v4;
    if ( v4 <= 11 )
    {
      v17 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * v4 + 24] + 6596);
      dword_17AA880 = *v17;
      dword_17AA884 = v17[1];
      dword_17AA888 = v17[2];
      v18 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)(v63 + 8) + 24] + 6584);
      dword_17AA890 = *v18;
      dword_17AA894 = v18[1];
      dword_17AA898 = v18[2];
      __asm
      {
        fld     dword_17AA898
        fsub    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword_17AA894
        fsub    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA890
        fsub    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v19 = (gbVec3D *->gbVec3D()v61, v34, v41, v48);
      v58 = *(_DWORD *)v19;
      v59 = *((_DWORD *)v19 + 1);
      v20 = *((_DWORD *)v19 + 2);
      dword_17AA870 = v58;
      v60 = v20;
      dword_17AA874 = v59;
      dword_17AA878 = v20;
      (gbVec3D *->Normalize()&dword_17AA870);
      v21 = *(_DWORD *)(v63 + 8);
      if ( v21 == 4 && *(_BYTE *)(*(_DWORD *)&g_SceneMgr.m_info[6568] + 613) == 1 )
      {
        CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[40], v52);
        __asm { fstp    [esp+2Ch+arg_4] }
        CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * v5 + 24], v53);
        __asm
        {
          fadd    [esp+2Ch+arg_4]
          fadd    ds:flt_56A77C
        }
      }
      else
      {
        CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * v21 + 24], v52);
        __asm { fstp    [esp+2Ch+arg_4] }
        CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * v5 + 24], v54);
        __asm { fadd    [esp+2Ch+arg_4] }
      }
      __asm
      {
        fld     dword_17AA870
        fmul    st, st(1)
      }
      __asm
      {
        fstp    dword_17AA870
        fld     dword_17AA874
        fmul    st, st(1)
        fstp    dword_17AA874
        fld     dword_17AA878
        fmul    st, st(1)
        fstp    dword_17AA878
        fstp    st
        fld     dword_17AA878
        fadd    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword_17AA874
        fadd    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA870
        fadd    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v22 = (gbVec3D *->gbVec3D()v61, v35, v42, v49);
      v58 = *(_DWORD *)v22;
      v23 = *((_DWORD *)v22 + 1);
      __asm { fld     [esp+20h+var_18] }
      v24 = *((_DWORD *)v22 + 2);
      result = (int)v62;
      v59 = v23;
      v60 = v24;
      __asm { fstp    dword ptr [eax] }
      *(float *)result = _ET1;
      v62[1] = v23;
      v62[2] = v24;
    }
    else
    {
      _EDI = v62;
      v7 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * v56 + 24] + 6596);
      *v62 = *v7;
      v8 = v57;
      v62[1] = v7[1];
      v62[2] = v7[2];
      v9 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * v8 + 24] + 6596);
      dword_17AA890 = *v9;
      dword_17AA894 = v9[1];
      dword_17AA898 = v9[2];
      __asm
      {
        fld     dword_17AA898
        fadd    dword ptr [edi+8]
        fstp    [esp+30h+var_30]
        fld     dword_17AA894
        fadd    dword ptr [edi+4]
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA890
        fadd    dword ptr [edi]
      }
      __asm { fstp    [esp+38h+var_38] }
      v10 = (gbVec3D *->gbVec3D()v61, v31, v38, v45);
      v58 = *(_DWORD *)v10;
      __asm
      {
        fld     [esp+2Ch+var_18]
        fmul    ds:flt_56A610
      }
      v59 = *((_DWORD *)v10 + 1);
      v11 = *((_DWORD *)v10 + 2);
      __asm
      {
        fstp    dword_17AA880
        fld     [esp+2Ch+var_14]
        fmul    ds:flt_56A610
      }
      v60 = v11;
      __asm
      {
        fstp    dword_17AA884
        fld     [esp+2Ch+var_10]
        fmul    ds:flt_56A610
        fstp    dword_17AA888
      }
      v12 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)(v63 + 8) + 24] + 6584);
      dword_17AA890 = *v12;
      dword_17AA894 = v12[1];
      dword_17AA898 = v12[2];
      __asm
      {
        fld     dword_17AA898
        fsub    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword_17AA894
        fsub    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA890
        fsub    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v13 = (gbVec3D *->gbVec3D()v61, v32, v39, v46);
      v58 = *(_DWORD *)v13;
      v59 = *((_DWORD *)v13 + 1);
      v60 = *((_DWORD *)v13 + 2);
      dword_17AA870 = v58;
      dword_17AA874 = v59;
      dword_17AA878 = v60;
      (gbVec3D *->Normalize()&dword_17AA870);
      __asm
      {
        fld     dword_17AA870
        fmul    ds:flt_56A64C
      }
      __asm
      {
        fstp    dword_17AA870
        fld     dword_17AA874
        fmul    ds:flt_56A64C
        fstp    dword_17AA874
        fld     dword_17AA878
        fmul    ds:flt_56A64C
        fst     dword_17AA878
        fadd    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword_17AA874
        fadd    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA870
        fadd    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v14 = (gbVec3D *->gbVec3D()v61, v33, v40, v47);
      v58 = *(_DWORD *)v14;
      v59 = *((_DWORD *)v14 + 1);
      v15 = v59;
      result = *((_DWORD *)v14 + 2);
      *v62 = v58;
      v62[1] = v15;
      v62[2] = result;
      v60 = result;
    }
  }
  else
  {
    v26 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * v3 + 24] + 6596);
    dword_17AA880 = *v26;
    dword_17AA884 = v26[1];
    dword_17AA888 = v26[2];
    v27 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)(v63 + 8) + 24] + 6584);
    dword_17AA890 = *v27;
    dword_17AA894 = v27[1];
    dword_17AA898 = v27[2];
    __asm
    {
      fld     dword_17AA898
      fsub    dword_17AA888
      fstp    [esp+30h+var_30]
      fld     dword_17AA894
      fsub    dword_17AA884
    }
    __asm
    {
      fstp    [esp+34h+var_34]
      fld     dword_17AA890
      fsub    dword_17AA880
    }
    __asm { fstp    [esp+38h+var_38] }
    v28 = (gbVec3D *->gbVec3D()v61, v36, v43, v50);
    v58 = *(_DWORD *)v28;
    v59 = *((_DWORD *)v28 + 1);
    v29 = *((_DWORD *)v28 + 2);
    dword_17AA870 = v58;
    v60 = v29;
    dword_17AA874 = v59;
    dword_17AA878 = v29;
    (gbVec3D *->Normalize()&dword_17AA870);
    CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * *(_DWORD *)(v63 + 12) + 24], v52);
    __asm { fstp    [esp+2Ch+arg_4] }
    CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * *(_DWORD *)(v2 + 8) + 24], v55);
    __asm
    {
      fadd    [esp+2Ch+arg_4]
      fld     dword_17AA870
      fmul    st, st(1)
      fstp    dword_17AA870
      fld     dword_17AA874
      fmul    st, st(1)
      fstp    dword_17AA874
      fld     dword_17AA878
      fmul    st, st(1)
      fstp    dword_17AA878
    }
    __asm { fstp    st }
    if ( *(_DWORD *)CCBRoleState::InitUI(*(void **)&this->m_pCBSystem[4], *(_DWORD *)(v2 + 8)) == 7364
      || *(_DWORD *)CCBRoleState::InitUI(*(void **)&this->m_pCBSystem[4], *(_DWORD *)(v2 + 8)) == 7381 )
    {
      __asm
      {
        fld     dword_17AA870
        fadd    st, st
        fstp    dword_17AA870
        fld     dword_17AA874
        fadd    st, st
        fstp    dword_17AA874
        fld     dword_17AA878
        fadd    st, st
        fstp    dword_17AA878
      }
    }
    __asm
    {
      fld     dword_17AA878
      fadd    dword_17AA888
    }
    __asm
    {
      fstp    [esp+30h+var_30]
      fld     dword_17AA874
      fadd    dword_17AA884
    }
    __asm
    {
      fstp    [esp+34h+var_34]
      fld     dword_17AA870
      fadd    dword_17AA880
    }
    __asm { fstp    [esp+38h+var_38] }
    v30 = (gbVec3D *->gbVec3D()v61, v37, v44, v51);
    v58 = *(_DWORD *)v30;
    v59 = *((_DWORD *)v30 + 1);
    v60 = *((_DWORD *)v30 + 2);
    return gbVec3D::operator=(v62, &v58);
  }
  return result;
}

// 0x00503CF0
int CCBStage::UpdatePhysics()
{
  int result; // eax
  float *v2; // ecx
  int v3; // edx
  double v4; // st7
  __int16 v5; // fps
  double v6; // st6
  bool v7; // c0
  char v8; // c2
  bool v9; // c3

  result = *(_DWORD *)this->m_pCBSystem;
  v2 = (float *)&this->m_pCBSystem[104];
  v3 = 11;
  v4 = *(double *)(result + 64) * 30.0;
  do
  {
    if ( *v2 > 0.0 )
    {
      if ( *v2 <= 160.0 )
        *v2 = *v2 - v4;
      else
        *v2 = 160.0;
    }
    v6 = *v2;
    v7 = v6 < 0.0;
    v8 = 0;
    v9 = v6 == 0.0;
    LOWORD(result) = v5;
    if ( v6 < 0.0 )
      *v2 = 0.0;
    ++v2;
    --v3;
  }
  while ( v3 );
  return result;
}

// 0x005045B0
char CCBStage::ProcessTurn()
{
  double x; // st7
  double y; // st6
  double v4; // st6
  int v5; // eax
  double v6; // st7
  double v7; // st7
  double v8; // st6
  double v9; // st6
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  float v15; // [esp+2Ch] [ebp-44h]
  float v16; // [esp+30h] [ebp-40h]
  float v17; // [esp+34h] [ebp-3Ch]
  struct tagPOINT Point; // [esp+38h] [ebp-38h] BYREF
  float v19; // [esp+40h] [ebp-30h] BYREF
  int v20; // [esp+44h] [ebp-2Ch]
  float v21; // [esp+48h] [ebp-28h]
  float v22; // [esp+4Ch] [ebp-24h] BYREF
  float v23; // [esp+50h] [ebp-20h]
  float v24; // [esp+54h] [ebp-1Ch]
  float v25; // [esp+58h] [ebp-18h]
  float v26; // [esp+60h] [ebp-10h]
  _DWORD v27[3]; // [esp+64h] [ebp-Ch] BYREF

  *(_DWORD *)&this->m_pCBSystem[448] = 0;
  sub_5049F0(this);
  sub_504A80(this->m_pCBSystem);
  GRPinput::GetCursorPos(&Point);
  if ( GRPinput::GetKeyState(&g_Input, 0x100u) || GRPinput::GetKeyState(&g_Input, 0x101u) )
  {
    x = (double)Point.x;
    v15 = x - *(float *)&this->m_pCBSystem[552];
    y = (double)Point.y;
    v17 = y;
    v4 = y - *(float *)&this->m_pCBSystem[556];
    *(float *)&this->m_pCBSystem[556] = v17;
    v16 = v4;
    *(float *)&this->m_pCBSystem[552] = x;
  }
  else
  {
    v16 = 0.0;
    v15 = 0.0;
    *(float *)&this->m_pCBSystem[552] = (float)Point.x;
    *(float *)&this->m_pCBSystem[556] = (float)Point.y;
  }
  if ( !*(_BYTE *)(**(_DWORD **)&this->m_pCBSystem[544] + 134) )
  {
    if ( GRPinput::GetKeyState(&g_Input, 0x100u) )
    {
      v5 = *(_DWORD *)&this->m_pCBSystem[544];
      if ( *(_DWORD *)(v5 + 88) == -1 && !*(_BYTE *)(*(_DWORD *)(v5 + 20) + 964) )
      {
        v22 = *(float *)&this->m_pCBSystem[504];
        v23 = *(float *)&this->m_pCBSystem[508];
        v24 = *(float *)&this->m_pCBSystem[512];
        (gbVec3D *->Normalize()&v22);
        v27[0] = *(_DWORD *)&this->m_pCBSystem[516];
        v27[1] = *(_DWORD *)&this->m_pCBSystem[520];
        v27[2] = *(_DWORD *)&this->m_pCBSystem[524];
        (gbVec3D *->Normalize()v27);
        v19 = 0.0;
        v20 = 0;
        v21 = 0.0;
        (gbVec3D *->CrossProduct()v27, (const struct gbVec3D *)&v22, (struct gbVec3D *)&v19);
        (gbVec3D *->Normalize()&v19);
        v6 = v16 + v16;
        if ( (g_Input.m_mousept[6712] & 0xF) == 1 )
        {
          v22 = 0.0;
          v23 = v6;
          v7 = (float)0.0;
          v24 = 0.0;
          v8 = v15 + v15;
          v19 = v19 * v8;
        }
        else
        {
          v23 = 0.0;
          v22 = v6 * v22;
          v7 = v6 * v24;
          v24 = v7;
          v8 = v15 + v15;
          v19 = v8 * v19;
        }
        v21 = v21 * v8;
        v9 = v7;
        v10 = v23;
        v26 = v9;
        v20 = 0;
        v25 = v19 + v22;
        v26 = v26 + v21;
        *(float *)&this->m_pCBSystem[480] = v25 + *(float *)&this->m_pCBSystem[480];
        *(float *)&this->m_pCBSystem[484] = v10 + *(float *)&this->m_pCBSystem[484];
        *(float *)&this->m_pCBSystem[488] = v26 + *(float *)&this->m_pCBSystem[488];
        InputSystem::ProcessKeyboard(1);
        InputSystem::ProcessKeyboard(0);
      }
    }
    v11 = (double)*(int *)&g_Input.m_mousept[5128] * 0.25;
    if ( (g_Input.m_mousept[6712] & 0xF) == 1 )
    {
      *(float *)&this->m_pCBSystem[464] = v11 * 0.001 + *(float *)&this->m_pCBSystem[464];
      InputSystem::ProcessKeyboard(0);
    }
    else if ( (g_Input.m_mousept[6728] & 0xF) == 1 )
    {
      v12 = v11 * 0.001 + *(float *)&this->m_pCBSystem[4];
      *(_DWORD *)&this->m_pCBSystem[8] = 0;
      *(float *)&this->m_pCBSystem[4] = v12;
    }
    else
    {
      *(float *)&this->m_pCBSystem[468] = v11 + *(float *)&this->m_pCBSystem[468];
      InputSystem::ProcessKeyboard(1);
    }
    if ( GRPinput::GetKeyState(&g_Input, 0x101u)
      && !*(_BYTE *)(*(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[544] + 20) + 964) )
    {
      v13 = v15 * 0.0043633231 + *(float *)&this->m_pCBSystem[456];
      *(float *)&this->m_pCBSystem[456] = v13;
      *(float *)&this->m_pCBSystem[452] = *(float *)&this->m_pCBSystem[452] - v16 * 0.0043633231;
      if ( v13 <= 3.1415927 )
      {
        if ( v13 <= -3.1415927 )
          v13 = v13 + 6.2831855;
      }
      else
      {
        v13 = v13 - 6.2831855;
      }
      *(float *)&this->m_pCBSystem[456] = v13;
      InputSystem::ProcessKeyboard(0);
    }
  }
  *(_DWORD *)&this->m_pCBSystem[468] = 1120403456;
  InputSystem::ProcessKeyboard(0);
  (CameraCtrl *->SetAsCurrent()this, 3);
  Combat::LogMessage(*(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[544] + 68), 5, 135, aCamXFYFZF);
  Combat::LogMessage(*(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[544] + 68), 5, 150, aCamYawFPitchFR);
  return Combat::LogMessage(*(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[544] + 68), 5, 165, aCamFovF);
}

// 0x0050D440
int CCBStage::CheckAllDone()
{
  char *v2; // eax
  int v3; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st7
  double v8; // st7
  int v9; // edi
  int v10; // eax
  char *Instance; // eax
  double v12; // st7
  double v13; // st6
  double v14; // st7
  double v15; // st7
  int v16; // eax
  CCBStageRole *v17; // eax
  int v18; // eax
  CCBStageRole *v19; // eax
  int v20; // [esp+0h] [ebp-14h]
  float v21; // [esp+8h] [ebp-Ch]
  int v22; // [esp+Ch] [ebp-8h]
  int v23; // [esp+Ch] [ebp-8h]
  float v24; // [esp+Ch] [ebp-8h]
  int v25; // [esp+10h] [ebp-4h]
  int v26; // [esp+10h] [ebp-4h]
  int v27; // [esp+18h] [ebp+4h]
  float v28; // [esp+18h] [ebp+4h]

  if ( (byte_17AB6E4 & 1) == 0 )
  {
    byte_17AB6E4 |= 1u;
    dword_17AB6D8 = 0;
    dword_17AB6DC = 0;
    dword_17AB6E0 = 0;
    atexit(nullsub_57);
  }
  if ( (byte_17AB6E4 & 2) == 0 )
  {
    byte_17AB6E4 |= 2u;
    dword_17AB6C8 = 0;
    dword_17AB6CC = 0;
    dword_17AB6D0 = 1065353216;
    atexit(nullsub_56);
  }
  if ( (byte_17AB6E4 & 4) == 0 )
  {
    byte_17AB6E4 |= 4u;
    dword_17AB6B8 = 0;
    dword_17AB6BC = 0;
    dword_17AB6C0 = 0;
    atexit(nullsub_55);
  }
  v2 = &this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396]];
  if ( v2[506] )
  {
    v9 = v27;
  }
  else
  {
    *((_DWORD *)v2 + 122) = -1054867456;
    v3 = 96 * *(_DWORD *)&this->m_pCBSystem[396];
    *(_DWORD *)&this->m_pCBSystem[6608] = *(_DWORD *)&this->m_pCBSystem[v3 + 432];
    *(_DWORD *)&this->m_pCBSystem[6612] = *(_DWORD *)&this->m_pCBSystem[v3 + 436];
    *(_DWORD *)&this->m_pCBSystem[6616] = *(_DWORD *)&this->m_pCBSystem[v3 + 440];
    v4 = *(float *)&this->m_pCBSystem[6608] - *(float *)&this->m_pCBSystem[6584];
    *(float *)&v22 = *(float *)&this->m_pCBSystem[6612] - *(float *)&this->m_pCBSystem[6588];
    v5 = *(float *)&this->m_pCBSystem[6616] - *(float *)&this->m_pCBSystem[6592];
    dword_17AB6DC = v22;
    *(float *)&v25 = v5;
    *(float *)&dword_17AB6D8 = v4;
    dword_17AB6E0 = v25;
    v6 = (gbVec3D *->Length()&dword_17AB6D8);
    if ( v6 < 2.0 )
    {
      *(_DWORD *)&this->m_pCBSystem[6584] = *(_DWORD *)&this->m_pCBSystem[6608];
      *(_DWORD *)&this->m_pCBSystem[6588] = *(_DWORD *)&this->m_pCBSystem[6612];
      *(_DWORD *)&this->m_pCBSystem[6592] = *(_DWORD *)&this->m_pCBSystem[6616];
      this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 505] = 1;
      return 0;
    }
    (gbVec3D *->Normalize()&dword_17AB6D8);
    flt_17ABCDC = acos(
                    *(float *)&dword_17AB6D0 * *(float *)&dword_17AB6E0
                  + *(float *)&dword_17AB6CC * *(float *)&dword_17AB6DC
                  + *(float *)&dword_17AB6C8 * *(float *)&dword_17AB6D8);
    if ( *(float *)&dword_17AB6D8 < 0.0 )
      flt_17ABCDC = 6.2831855 - flt_17ABCDC;
    *(float *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 492] = flt_17ABCDC * 57.29578;
    *(_DWORD *)&this->m_pCBSystem[6620] = dword_17AB6D8;
    v28 = v6;
    v8 = v28 + v28;
    *(_DWORD *)&this->m_pCBSystem[6624] = dword_17AB6DC;
    *(_DWORD *)&this->m_pCBSystem[6628] = dword_17AB6E0;
    *(float *)&this->m_pCBSystem[6620] = v8 * *(float *)&this->m_pCBSystem[6620];
    *(float *)&this->m_pCBSystem[6624] = v8 * *(float *)&this->m_pCBSystem[6624];
    *(float *)&this->m_pCBSystem[6628] = v8 * *(float *)&this->m_pCBSystem[6628];
    if ( CCBStageRole::IsActive(*(CCBStageRole **)&this->m_pCBSystem[4], *(_DWORD *)&this->m_pCBSystem[284]) )
      *(_DWORD *)&this->m_pCBSystem[6568] = 31;
    else
      *(_DWORD *)&this->m_pCBSystem[6568] = 52;
    CCBStageRole::IsGrabedBy((int)this);
    v9 = 0;
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 506] = 1;
    CCBStageRole::ClearBadPushTask((int)this, 0.40000001);
    v10 = *(_DWORD *)&this->m_pCBSystem[284];
    this->m_pCBSystem[273] = 1;
    if ( v10 == 3 )
    {
      Instance = CScreenMode::GetInstance();
      (CScreenMode *->AudioSetPosition()Instance, aWe013, 1);
    }
  }
  v12 = *(float *)&this->m_pCBSystem[6608] - *(float *)&this->m_pCBSystem[6584];
  *(float *)&v23 = *(float *)&this->m_pCBSystem[6612] - *(float *)&this->m_pCBSystem[6588];
  v13 = *(float *)&this->m_pCBSystem[6616] - *(float *)&this->m_pCBSystem[6592];
  dword_17AB6DC = v23;
  *(float *)&v26 = v13;
  *(float *)&dword_17AB6D8 = v12;
  dword_17AB6E0 = v26;
  if ( v9 == *(_DWORD *)&this->m_pCBSystem[6664] )
    *(_DWORD *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 488] = 1120403456;
  if ( *(float *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 488] > 0.0
    && (gbVec3D *->Length()&dword_17AB6D8) > 2.0 )
  {
    v14 = *(double *)(**(_DWORD **)this->m_pCBSystem + 64);
    v21 = *(float *)&this->m_pCBSystem[6620] * v14;
    v24 = *(float *)&this->m_pCBSystem[6624] * v14;
    v15 = v14 * *(float *)&this->m_pCBSystem[6628];
    *(float *)&this->m_pCBSystem[6584] = v21 + *(float *)&this->m_pCBSystem[6584];
    *(float *)&this->m_pCBSystem[6588] = v24 + *(float *)&this->m_pCBSystem[6588];
    *(float *)&this->m_pCBSystem[6592] = v15 + *(float *)&this->m_pCBSystem[6592];
    *(float *)&this->m_pCBSystem[6632] = *(double *)(**(_DWORD **)this->m_pCBSystem + 64) * 720.0
                                       + *(float *)&this->m_pCBSystem[6632];
  }
  if ( v9 == *(_DWORD *)&this->m_pCBSystem[6668] && (gbVec3D *->Length()&dword_17AB6D8) <= 2.0 )
    *(_DWORD *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 488] = -1054867456;
  (gbVec3D *->Normalize()&dword_17AB6D8);
  flt_17ABCDC = acos(
                  *(float *)&dword_17AB6D0 * *(float *)&dword_17AB6E0
                + *(float *)&dword_17AB6CC * *(float *)&dword_17AB6DC
                + *(float *)&dword_17AB6C8 * *(float *)&dword_17AB6D8);
  if ( *(float *)&dword_17AB6D8 < 0.0 )
    flt_17ABCDC = 6.2831855 - flt_17ABCDC;
  if ( fabs(flt_17ABCDC * 57.29578 - *(float *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 492]) >= 1.570796370506287 )
  {
    *(_DWORD *)&this->m_pCBSystem[6584] = *(_DWORD *)&this->m_pCBSystem[6608];
    *(_DWORD *)&this->m_pCBSystem[6588] = *(_DWORD *)&this->m_pCBSystem[6612];
    *(_DWORD *)&this->m_pCBSystem[6592] = *(_DWORD *)&this->m_pCBSystem[6616];
    *(_DWORD *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 488] = -1054867456;
  }
  if ( v9 == *(_DWORD *)&this->m_pCBSystem[6644] )
  {
    *(_DWORD *)&this->m_pCBSystem[6584] = *(_DWORD *)&this->m_pCBSystem[6608];
    *(_DWORD *)&this->m_pCBSystem[6588] = *(_DWORD *)&this->m_pCBSystem[6612];
    *(_DWORD *)&this->m_pCBSystem[6592] = *(_DWORD *)&this->m_pCBSystem[6616];
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 505] = 1;
    v16 = *(_DWORD *)&this->m_pCBSystem[284];
    this->m_pCBSystem[273] = 0;
    if ( v16 == 3 )
    {
      v17 = (CCBStageRole *)CScreenMode::GetInstance();
      v17->PlaySound(aWe013, v20);
    }
  }
  if ( !CCBRoleState::IsRoleAlive(*(CCBRoleState **)&this->m_pCBSystem[4], *(_DWORD *)&this->m_pCBSystem[284]) )
  {
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 505] = 1;
    v18 = *(_DWORD *)&this->m_pCBSystem[284];
    this->m_pCBSystem[273] = 0;
    if ( v18 == 3 )
    {
      v19 = (CCBStageRole *)CScreenMode::GetInstance();
      v19->PlaySound(aWe013, v20);
    }
  }
  return 0;
}

// 0x0050E0D0
int CCBStage::ProcessCommand()
{
  char *v2; // eax
  int v3; // edx

  v2 = &this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396]];
  if ( !v2[506] )
  {
    v3 = *(_DWORD *)&this->m_pCBSystem[284];
    *(_DWORD *)&this->m_pCBSystem[6632] = *((_DWORD *)v2 + 108);
    if ( CCBStageRole::IsActive(*(CCBStageRole **)&this->m_pCBSystem[4], v3) )
      *(_DWORD *)&this->m_pCBSystem[6568] = 32;
    else
      *(_DWORD *)&this->m_pCBSystem[6568] = 50;
    CCBStageRole::IsGrabedBy((int)this);
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 506] = 1;
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 505] = 1;
  }
  return 0;
}
