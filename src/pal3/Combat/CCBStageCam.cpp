#include "pal3/gen/CCBStageCam.h"

// 0x00504E70
char sub_504E70(char *Buffer)
{
  FILE *v2; // esi
  _DWORD *v3; // eax
  int v4; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList; // [esp+408h] [ebp-400h] BYREF

  v2 = fopen(aBasedataCbdata_0, Mode);
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCouldnTOpenCbC, (int)aDProjectPal3Co_6, 702),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v3 = Buffer + 176;
  v4 = 2000;
  do
  {
    v3[1] = 1112014848;
    *v3 = 1112014848;
    v3 += 51;
    --v4;
  }
  while ( v4 );
  fseek(v2, 0, 0);
  fwrite(Buffer, 0x639C0u, 1u, v2);
  fwrite(Buffer + 408000, 0x7D0u, 1u, v2);
  fwrite(Buffer + 410000, 0x4E20u, 1u, v2);
  fclose(v2);
  return 1;
}

// 0x00504F40
char sub_504F40(int this)
{
  struct gbVFile *v2; // esi
  struct gbVFileSystem *v4; // [esp+3Ch] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+40h] [ebp-80Ch] BYREF
  char ArgList; // [esp+440h] [ebp-40Ch] BYREF
  int v7; // [esp+848h] [ebp-4h]

  OpenBaseFile::OpenBaseFile(&v4);
  v7 = 0;
  v2 = g_pVFileSys->OpenFile(aCbdataFlexcamD, 0x201u);
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCouldnTOpenCbC, (int)aDProjectPal3Co_6, 734),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Read((void *)this, 0x639C0u, v2);
  g_pVFileSys->Read((void *)(this + 408000), 0x7D0u, v2);
  g_pVFileSys->Read((void *)(this + 410000), 0x4E20u, v2);
  g_pVFileSys->CloseFile(v2);
  v7 = -1;
  OpenNULLFile::OpenNULLFile(&v4);
  return 1;
}

// 0x00505060
char CCBStageCam::Reset(int a2, const void *a3)
{
  int IsCamValid; // esi
  int IsEditorCamValid; // eax

  IsCamValid = this->IsCamValid();
  IsEditorCamValid = this->IsEditorCamValid(a2);
  if ( IsCamValid == -1 )
    return 0;
  if ( IsEditorCamValid >= 50 )
    return 0;
  *((_DWORD *)this + 50 * a2 + IsEditorCamValid + 102500) = IsCamValid;
  *((_BYTE *)this + IsCamValid + 408000) = 1;
  qmemcpy((char *)this + 204 * IsCamValid, a3, 0xCCu);
  return 1;
}

// 0x005050D0
char sub_5050D0(_DWORD *this, int a2, int a3, const void *a4)
{
  int v5; // eax
  int v7; // eax
  _DWORD *v8; // edx
  int v9; // ecx

  v5 = a2->IsEditorCamValid();
  if ( a3 >= v5 )
    return this->Reset(a2, a4);
  if ( v5 >= 50 )
    return 0;
  v7 = this->IsCamValid();
  if ( v7 == -1 )
    return 0;
  if ( a3 < 49 )
  {
    v8 = this + 50 * a2 + 102549;
    v9 = 49 - a3;
    do
    {
      *v8 = *(v8 - 1);
      --v8;
      --v9;
    }
    while ( v9 );
  }
  *(this + 50 * a2 + a3 + 102500) = v7;
  *((_BYTE *)this + v7 + 408000) = 1;
  qmemcpy(this + 51 * v7, a4, 0xCCu);
  return 1;
}

// 0x00505180
char sub_505180(_DWORD *this, int a2, int a3, int a4)
{
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  _DWORD *v9; // eax

  v5 = a2->IsEditorCamValid();
  if ( a3 >= v5 || a4 >= v5 || a3 == a4 )
    return 0;
  v6 = 10 * (5 * a2 + 10250);
  v7 = v6 + a3;
  v8 = *(this + v6 + a3);
  v9 = this + a4 + v6;
  *(this + v7) = *v9;
  *v9 = v8;
  return 1;
}

// 0x005051E0
char sub_5051E0(_BYTE *this, int a2, int a3)
{
  int v5; // eax
  _DWORD *v6; // eax
  int v7; // edx

  if ( a3 >= a2->IsEditorCamValid() )
    return 0;
  v5 = 10 * (5 * a2 + 10250);
  *(this + *((_DWORD *)this + v5 + a3) + 408000) = 0;
  if ( a3 == 49 )
  {
    *((_DWORD *)this + 50 * a2 + 102549) = -1;
    return 1;
  }
  else
  {
    if ( a3 < 49 )
    {
      v6 = this + 4 * v5 + 4 * a3;
      v7 = 49 - a3;
      do
      {
        *v6 = v6[1];
        ++v6;
        --v7;
      }
      while ( v7 );
    }
    return 1;
  }
}

// 0x00505250
char sub_505250(_BYTE *this, int a2)
{
  int v2; // edx
  int *v3; // eax
  int v4; // esi

  v2 = 50;
  v3 = (int *)(this + 200 * a2 + 410000);
  do
  {
    v4 = *v3++;
    --v2;
    *(this + v4 + 408000) = 0;
    *(v3 - 1) = -1;
  }
  while ( v2 );
  return 1;
}

// 0x00505290
int CCBStageCam::IsEditorCamValid(int a2)
{
  int result; // eax
  int v3; // edx
  _DWORD *v4; // ecx

  result = 0;
  v3 = 0;
  v4 = (_DWORD *)((char *)this + 200 * a2 + 410000);
  do
  {
    if ( *v4 == -1 )
      break;
    ++result;
    ++v3;
    ++v4;
  }
  while ( v3 < 50 );
  return result;
}

// 0x005052C0
int sub_5052C0(_BYTE *this)
{
  int result; // eax

  result = 0;
  while ( *(this + result + 408000) )
  {
    if ( ++result >= 2000 )
      return -1;
  }
  return result;
}

// 0x005052E0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_DWORD *__thiscall sub_5052E0(_DWORD *this, int **a2, int a3)
{
  int v4; // eax

  sub_504DD0(this);
  *(this + 107512) = 0;
  *(this + 107513) = 0;
  *(this + 107514) = 0;
  *(this + 107515) = 0;
  *(this + 107516) = 0;
  *(this + 107517) = 0;
  *(this + 107522) = 0;
  *(this + 107523) = 0;
  *(this + 107524) = 0;
  *(this + 107525) = 0;
  *(this + 107526) = 0;
  *(this + 107527) = 0;
  *(this + 107528) = 0;
  *(this + 107529) = 0;
  *(this + 107530) = 0;
  *(this + 107531) = 0;
  *(this + 107532) = 0;
  *(this + 107533) = 0;
  *(this + 107534) = 0;
  *(this + 107535) = 0;
  *(this + 107536) = 0;
  (gbMatrix4 *->gbMatrix4()(this + 107537));
  *(this + 107557) = 0;
  *(this + 107558) = 0;
  *(this + 107559) = 0;
  *(this + 107560) = 0;
  *(this + 107561) = 0;
  *(this + 107562) = 0;
  *(this + 107500) = a2;
  *(this + 107501) = a3;
  v4 = **a2;
  *(this + 107509) = -1;
  *(this + 107502) = v4;
  return this;
}

// 0x00505410
int sub_505410(int this)
{
  *(_DWORD *)(this + 430016) = 0;
  *(_DWORD *)(this + 430020) = 0;
  *(_BYTE *)(this + 430012) = 0;
  *(_DWORD *)(this + 430076) = 0;
  *(_DWORD *)(this + 430024) = 0;
  *(_DWORD *)(this + 430228) = 0;
  *(_DWORD *)(this + 430236) = 0;
  *(_DWORD *)(this + 430028) = -1;
  *(_DWORD *)(this + 430032) = -1;
  *(_DWORD *)(this + 430036) = -1;
  *(_DWORD *)(this + 430080) = 1065353216;
  *(_DWORD *)(this + 430084) = 1117782016;
  *(_DWORD *)(this + 430232) = 1112014848;
  *(_DWORD *)(this + 430240) = 1120403456;
  *(_DWORD *)(this + 430244) = 1120403456;
  *(_DWORD *)(this + 430248) = 1120403456;
  return 1120403456;
}

// 0x00505490
char CCBStageCam::Destroy()
{
  CCBStageCam::Create((int)this);
  CCBStageCam::~CCBStageCam((int)this);
  this->Destroy();
  return 1;
}

// 0x005054B0
char sub_5054B0(_DWORD *this)
{
  void (__thiscall ***v2)(_DWORD, int); // ecx

  v2 = (void (__thiscall ***)(_DWORD, int))*(this + 107556);
  if ( v2 )
  {
    (**v2)(v2, 1);
    *(this + 107556) = 0;
  }
  return 1;
}

// 0x005054E0
char CCBStageCam::Update()
{
  CCBStageCam::Create((int)this);
  return 1;
}

// 0x005054F0
void sub_5054F0(int this)
{
  int v2; // eax
  void *v3; // ecx
  double v4; // st7
  int v5; // eax
  char *v6; // ecx
  float *v7; // eax
  float v8; // edx
  double v9; // st7
  char v10; // al
  double v11; // st7
  double v12; // st6
  float v13; // eax
  double v14; // st6
  float v15; // edx
  int v16; // [esp+Ch] [ebp-54h] BYREF
  int v17; // [esp+10h] [ebp-50h]
  int v18; // [esp+14h] [ebp-4Ch]
  float v19[3]; // [esp+18h] [ebp-48h] BYREF
  float v20[2]; // [esp+24h] [ebp-3Ch] BYREF
  float v21; // [esp+2Ch] [ebp-34h]
  float v22; // [esp+30h] [ebp-30h] BYREF
  int v23; // [esp+34h] [ebp-2Ch]
  float v24; // [esp+38h] [ebp-28h]
  float v25[3]; // [esp+3Ch] [ebp-24h] BYREF
  _BYTE v26[24]; // [esp+48h] [ebp-18h] BYREF

  *(_DWORD *)(*(_DWORD *)(this + 430004) + 448) = 0;
  if ( *(_BYTE *)(this + 430012) )
    CCCTData::Init();
  if ( *(float *)(this + 430076) <= 0.0 )
  {
    *(_DWORD *)(this + 430076) = 0;
  }
  else
  {
    v2 = *(_DWORD *)(this + 430000);
    v16 = *(_DWORD *)(this + 430116);
    v3 = *(void **)(this + 430004);
    v4 = *(float *)(this + 430076) - *(double *)(*(_DWORD *)v2 + 64) * *(float *)(this + 430080);
    *(float *)(this + 430076) = v4;
    *(float *)(this + 430116) = sin(*(float *)(*(_DWORD *)v2 + 80) * *(float *)(this + 430084)) * v4
                              + *(float *)(this + 430116);
    v3->UpdateCamera((int *)(this + 430112));
    CameraCtrl::SetAsCurrent(*(_DWORD *)(this + 430004), 3);
    *(_DWORD *)(this + 430116) = v16;
  }
  if ( dword_17A990C == 4 )
  {
    this->SwitchEditorCamPos();
    this->ProcCamMove();
    v20[1] = 1.0;
    v17 = 0;
    v20[0] = 0.0;
    v21 = 0.0;
    v16 = 1065353216;
    v18 = 1065353216;
    v19[1] = 0.0;
    v19[0] = 1.0;
    v19[2] = 1.0;
    v22 = 0.0;
    v23 = 0;
    v24 = 0.0;
    (gbVec3D *->gbVec3D()v25, 0.0, 0.0, 0.0);
    v5 = *(_DWORD *)(this + 430000);
    v16 = *(_DWORD *)(v5 + 80);
    v6 = *(char **)(this + 430004);
    v17 = *(_DWORD *)(v5 + 84);
    v7 = (float *)v6->GetViewTarget(v26, &v16);
    v8 = *v7;
    v7 += 3;
    v22 = v8;
    v23 = *((_DWORD *)v7 - 2);
    v24 = *(v7 - 1);
    gbVec3D::operator=(v25, v7);
    v9 = (gbRay *->IntersectPlane()&v22, (struct gbVec3D *)v20, (struct gbVec3D *)v19);
    v10 = *(_BYTE *)(this + 430253);
    v20[0] = v25[0] * v9;
    v19[0] = v20[0] + v22;
    v11 = v9 * v25[2] + v24;
    if ( v10 )
    {
      v12 = (double)MEMORY[0xBFC1A8] * 0.1 + *(float *)(this + 430232);
      *(float *)(this + 430232) = v12;
      v20[0] = v19[0];
      v21 = v11;
      v13 = v21;
      *(float *)(this + 430228) = v19[0];
      *(float *)(this + 430232) = v12;
      *(float *)(this + 430236) = v13;
    }
    if ( *(_BYTE *)(this + 430254) )
    {
      v14 = (double)MEMORY[0xBFC1A8] * 0.1 + *(float *)(this + 430244);
      *(float *)(this + 430244) = v14;
      v21 = v11;
      v15 = v21;
      *(float *)(this + 430240) = v19[0];
      *(float *)(this + 430244) = v14;
      *(float *)(this + 430248) = v15;
    }
  }
}

// 0x00505770
char CCBStageCam::ClearFinishedTask(int this, int a2)
{
  if ( !(CCBStageCam *->IsEditorCamValid()this, a2) )
    return 0;
  *(_BYTE *)(this + 430012) = 1;
  (CCCTData *->Save()this, a2);
  *(_DWORD *)(this + 430032) = a2;
  *(_DWORD *)(this + 430036) = 0;
  return 1;
}

// 0x00505800
int sub_505800(int this)
{
  *(_BYTE *)(this + 430012) = 0;
  *(_DWORD *)(this + 430032) = -1;
  *(_DWORD *)(this + 430036) = -1;
  return -1;
}

// 0x00505820
int sub_505820(int this)
{
  int v2; // eax
  int *v3; // ecx
  int v4; // eax
  int result; // eax
  int v6; // [esp+4h] [ebp-18h] BYREF
  int v7; // [esp+8h] [ebp-14h]
  int v8; // [esp+Ch] [ebp-10h]
  int v9; // [esp+10h] [ebp-Ch] BYREF
  int v10; // [esp+14h] [ebp-8h]
  int v11; // [esp+18h] [ebp-4h]

  v2 = this + 430228;
  v6 = *(_DWORD *)(this + 430228);
  v3 = (int *)(this + 430240);
  v7 = *(_DWORD *)(v2 + 4);
  v4 = *(_DWORD *)(v2 + 8);
  v9 = *v3;
  v8 = v4;
  v10 = v3[1];
  result = MEMORY[0xBFC6E4];
  v11 = v3[2];
  v7 = 0;
  v10 = 0;
  if ( MEMORY[0xBFC6E4] == 1 )
  {
    result = CCCTData::Create(&v6);
    if ( (_BYTE)result )
    {
      *(_BYTE *)(this + 430253) = 1;
    }
    else
    {
      result = CCCTData::Create(&v9);
      if ( (_BYTE)result )
      {
        *(_BYTE *)(this + 430254) = 1;
      }
      else
      {
        *(_BYTE *)(this + 430253) = 0;
        *(_BYTE *)(this + 430254) = 0;
      }
    }
  }
  if ( (MEMORY[0xBFC6D8] & 0xF) != 1 )
  {
    *(_BYTE *)(this + 430253) = 0;
    *(_BYTE *)(this + 430254) = 0;
  }
  return result;
}

// 0x005058E0
int sub_5058E0(_DWORD **this)
{
  return (*(int (__thiscall **)(_DWORD))(**(this + 107556) + 20))(*(this + 107556));
}
