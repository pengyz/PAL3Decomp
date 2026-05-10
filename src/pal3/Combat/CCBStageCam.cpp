#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageCam.h"
#include "pal3/gen/CCCTData.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"

// Forward declarations for unnamed functions
int sub_504DD0(...);

// Unnamed globals (extern)
extern char aBasedataCbdata_0[];
extern char aCbdataFlexcamD[];
extern char aCouldnTOpenCbC[];
extern char aDProjectPal3Co_6[];
extern int dword_17A990C;

// 0x00504E70
CCBStageCam::CCBStageCam(CCBStageCam *Buffer)
{
  FILE *v2; // esi
  char *v3; // eax
  int v4; // ecx
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  v2 = (FILE *)fopen(aBasedataCbdata_0, Mode);
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCouldnTOpenCbC, aDProjectPal3Co_6, 702),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v3 = (char *)&Buffer->_pad_0000[176];
  v4 = 2000;
  do
  {
    *((_DWORD *)v3 + 1) = 1112014848;
    *(_DWORD *)v3 = 1112014848;
    v3 += 204;
    --v4;
  }
  while ( v4 );
  fseek(v2, 0, 0);
  fwrite(Buffer, 0x639C0u, 1u, v2);
  fwrite((char *)Buffer + 408000, 0x7D0u, 1u, v2);
  fwrite((char *)Buffer + 410000, 0x4E20u, 1u, v2);
  fclose(v2);
  1;
}

// 0x00504F40
CCBStageCam::~CCBStageCam()
{
  struct gbVFile *v2; // esi
  OpenBaseFile v4; // [esp+3Ch] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+40h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+440h] [ebp-40Ch] BYREF
  int v7; // [esp+848h] [ebp-4h]

  ((OpenBaseFile *)&v4)->OpenBaseFile();
  v7 = 0;
  v2 = (struct gbVFile *)g_pVFileSys->OpenFile(aCbdataFlexcamD, 0x201u);
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCouldnTOpenCbC, aDProjectPal3Co_6, 734),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  g_pVFileSys->Seek(v2, 0, 1);
  g_pVFileSys->Read(this, 0x639C0u, v2);
  g_pVFileSys->Read((char *)this + 408000, 0x7D0u, v2);
  g_pVFileSys->Read((char *)this + 410000, 0x4E20u, v2);
  g_pVFileSys->CloseFile(v2);
  v7 = -1;
  ((OpenNULLFile *)&v4)->OpenNULLFile();
  1;
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
char CCBStageCam::LoadEditorCam(int a2, int a3, const void *a4)
{
  int IsEditorCamValid; // eax
  int IsCamValid; // eax
  _DWORD *v8; // edx
  int v9; // ecx

  IsEditorCamValid = this->IsEditorCamValid(a2);
  if ( a3 >= IsEditorCamValid )
    return this->Reset(a2, a4);
  if ( IsEditorCamValid >= 50 )
    return 0;
  IsCamValid = this->IsCamValid();
  if ( IsCamValid == -1 )
    return 0;
  if ( a3 < 49 )
  {
    v8 = (_DWORD *)((char *)this + 200 * a2 + 410196);
    v9 = 49 - a3;
    do
    {
      * v8 = (*)*(v8 - 1);
      --v8;
      --v9;
    }
    while ( v9 );
  }
  *((_DWORD *)this + 50 * a2 + a3 + 102500) = IsCamValid;
  *((_BYTE *)this + IsCamValid + 408000) = 1;
  qmemcpy((char *)this + 204 * IsCamValid, a4, 0xCCu);
  return 1;
}

// 0x00505180
char CCBStageCam::SaveEditorCam(int a2, int a3, int a4)
{
  int IsEditorCamValid; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  char *v9; // eax

  IsEditorCamValid = this->IsEditorCamValid(a2);
  if ( a3 >= IsEditorCamValid || a4 >= IsEditorCamValid || a3 == a4 )
    return 0;
  v6 = 10 * (5 * a2 + 10250);
  v7 = v6 + a3;
  v8 = *(_DWORD *)&this->_pad_0000[4 * v6 + 4 * a3];
  v9 = (char *)&this->_pad_0000[4 * a4 + 4 * v6];
  *(_DWORD *)&this->_pad_0000[4 * v7] = *(_DWORD *)v9;
  *(_DWORD *)v9 = v8;
  return 1;
}

// 0x005051E0
char CCBStageCam::AddCurCamToEditor(int a2, int a3)
{
  int v5; // eax
  char *v6; // eax
  int v7; // edx

  if ( a3 >= this->IsEditorCamValid(a2) )
    return 0;
  v5 = 10 * (5 * a2 + 10250);
  *((_BYTE *)this + *(_DWORD *)&this->_pad_0000[4 * v5 + 4 * a3] + 408000) = 0;
  if ( a3 == 49 )
  {
    *((_DWORD *)this + 50 * a2 + 102549) = -1;
    return 1;
  }
  else
  {
    if ( a3 < 49 )
    {
      v6 = (char *)&this->_pad_0000[4 * v5 + 4 * a3];
      v7 = 49 - a3;
      do
      {
        *(_DWORD *)v6 = *((_DWORD *)v6 + 1);
        v6 += 4;
        --v7;
      }
      while ( v7 );
    }
    return 1;
  }
}

// 0x00505250
char CCBStageCam::DelEditorCam(int a2)
{
  int v2; // edx
  int *v3; // eax
  int v4; // esi

  v2 = 50;
  v3 = (int *)((char *)this + 200 * a2 + 410000);
  do
  {
    v4 = *v3++;
    --v2;
    *((_BYTE *)this + v4 + 408000) = 0;
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
int CCBStageCam::IsCamValid()
{
  int result; // eax

  result = 0;
  while ( *((_BYTE *)this + result + 408000) )
  {
    if ( ++result >= 2000 )
      return -1;
  }
  return result;
}

// 0x005052E0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_DWORD * CCBStageCam::SetCamPos(int **a2, int a3)
{
  int v4; // eax

  sub_504DD0(this);
  *((_DWORD *)this + 107512) = 0;
  *((_DWORD *)this + 107513) = 0;
  *((_DWORD *)this + 107514) = 0;
  *((_DWORD *)this + 107515) = 0;
  *((_DWORD *)this + 107516) = 0;
  *((_DWORD *)this + 107517) = 0;
  *((_DWORD *)this + 107522) = 0;
  *((_DWORD *)this + 107523) = 0;
  *((_DWORD *)this + 107524) = 0;
  *((_DWORD *)this + 107525) = 0;
  *((_DWORD *)this + 107526) = 0;
  *((_DWORD *)this + 107527) = 0;
  *((_DWORD *)this + 107528) = 0;
  *((_DWORD *)this + 107529) = 0;
  *((_DWORD *)this + 107530) = 0;
  *((_DWORD *)this + 107531) = 0;
  *((_DWORD *)this + 107532) = 0;
  *((_DWORD *)this + 107533) = 0;
  *((_DWORD *)this + 107534) = 0;
  *((_DWORD *)this + 107535) = 0;
  *((_DWORD *)this + 107536) = 0;
  ((gbMatrix4 *)((char *)this + 430148))->gbMatrix4();
  *((_DWORD *)this + 107557) = 0;
  *((_DWORD *)this + 107558) = 0;
  *((_DWORD *)this + 107559) = 0;
  *((_DWORD *)this + 107560) = 0;
  *((_DWORD *)this + 107561) = 0;
  *((_DWORD *)this + 107562) = 0;
  *((_DWORD *)this + 107500) = a2;
  *((_DWORD *)this + 107501) = a3;
  v4 = **a2;
  *((_DWORD *)this + 107509) = -1;
  *((_DWORD *)this + 107502) = v4;
  return this->_pad_0000;
}

// 0x00505410
int CCBStageCam::Create()
{
  *((_DWORD *)this + 107504) = 0;
  *((_DWORD *)this + 107505) = 0;
  *((_BYTE *)this + 430012) = 0;
  *((_DWORD *)this + 107519) = 0;
  *((_DWORD *)this + 107506) = 0;
  *((_DWORD *)this + 107557) = 0;
  *((_DWORD *)this + 107559) = 0;
  *((_DWORD *)this + 107507) = -1;
  *((_DWORD *)this + 107508) = -1;
  *((_DWORD *)this + 107509) = -1;
  *((_DWORD *)this + 107520) = 1065353216;
  *((_DWORD *)this + 107521) = 1117782016;
  *((_DWORD *)this + 107558) = 1112014848;
  *((_DWORD *)this + 107560) = 1120403456;
  *((_DWORD *)this + 107561) = 1120403456;
  *((_DWORD *)this + 107562) = 1120403456;
  return 1120403456;
}

// 0x00505490
char CCBStageCam::Destroy()
{
  this->Create();
  this->~CCBStageCam();
  ((CCCTData *)this)->Destroy();
  return 1;
}

// 0x005054B0
char CCBStageCam::Init()
{
  void (***v2)(_DWORD, int); // ecx

  v2 = (void (***)(_DWORD, int))*((_DWORD *)this + 107556);
  if ( v2 )
  {
    (**v2)(v2, 1);
    *((_DWORD *)this + 107556) = 0;
  }
  return 1;
}

// 0x005054E0
char CCBStageCam::Update()
{
  this->Create();
  return 1;
}

// 0x005054F0
void CCBStageCam::DoTask()
{
  int v2; // eax
  CCCTData *v3; // ecx
  double v4; // st7
  int v5; // eax
  CameraCtrl *v6; // ecx
  float *ViewTarget; // eax
  float v8; // edx
  double v9; // st7
  char v10; // al
  double v11; // st7
  double v12; // st6
  float z; // eax
  double v14; // st6
  float v15; // edx
  float pPos; // [esp+Ch] [ebp-54h] BYREF
  int v17; // [esp+10h] [ebp-50h]
  int v18; // [esp+14h] [ebp-4Ch]
  struct gbVec3D v19; // [esp+18h] [ebp-48h] BYREF
  struct gbVec3D v20; // [esp+24h] [ebp-3Ch] BYREF
  gbRay v21; // [esp+30h] [ebp-30h] BYREF
  _BYTE pTarget[24]; // [esp+48h] [ebp-18h] BYREF

  *(_DWORD *)(*((_DWORD *)this + 107501) + 448) = 0;
  if ( *((_BYTE *)this + 430012) )
    ((CCCTData *)this)->Init();
  if ( *((float *)this + 107519) <= 0.0 )
  {
    *((_DWORD *)this + 107519) = 0;
  }
  else
  {
    v2 = *((_DWORD *)this + 107500);
    pPos = *((float *)this + 107529);
    v3 = (CCCTData *)*((_DWORD *)this + 107501);
    v4 = *((float *)this + 107519) - *(double *)(*(_DWORD *)v2 + 64) * *((float *)this + 107520);
    *((float *)this + 107519) = v4;
    *((float *)this + 107529) = sin(*(float *)(*(_DWORD *)v2 + 80) * *((float *)this + 107521)) * v4
                              + *((float *)this + 107529);
    v3->UpdateCamera((int)this + 430112);
    ((CameraCtrl *)*((CameraCtrl **)this + 107501))->SetAsCurrent(3);
    *((float *)this + 107529) = pPos;
  }
  if ( dword_17A990C == 4 )
  {
    ((CCBStageCam *)this)->SwitchEditorCamPos();
    this->ProcCamMove();
    v20.y = 1.0;
    v17 = 0;
    v20.x = 0.0;
    v20.z = 0.0;
    pPos = 1.0;
    v18 = 1065353216;
    v19.y = 0.0;
    v19.x = 1.0;
    v19.z = 1.0;
    memset(&v21, 0, 12);
    ((gbVec3D *)&v21.Direction)->gbVec3D(0.0, 0.0, 0.0);
    v5 = *((_DWORD *)this + 107500);
    pPos = *(float *)(v5 + 80);
    v6 = (CameraCtrl *)*((_DWORD *)this + 107501);
    v17 = *(_DWORD *)(v5 + 84);
    ViewTarget = (float *)v6->GetViewTarget(pTarget, &pPos);
    v8 = *ViewTarget;
    ViewTarget += 3;
    v21.Origin.x = v8;
    v21.Origin.y = *(ViewTarget - 2);
    v21.Origin.z = *(ViewTarget - 1);
    ((gbVec3D *)&v21.Direction)->operator=(ViewTarget);
    v9 = ((gbRay *)&v21)->IntersectPlane(&v20, &v19);
    v10 = *((_BYTE *)this + 430253);
    v20.x = v21.Direction.x * v9;
    v19.x = v20.x + v21.Origin.x;
    v11 = v9 * v21.Direction.z + v21.Origin.z;
    if ( v10 )
    {
      v12 = (double)*(int *)&g_Input.MouseState[8] * 0.1 + *((float *)this + 107558);
      *((float *)this + 107558) = v12;
      v20.x = v19.x;
      v20.z = v11;
      z = v20.z;
      *((_DWORD *)this + 107557) = LODWORD(v19.x);
      *((float *)this + 107558) = v12;
      *((float *)this + 107559) = z;
    }
    if ( *((_BYTE *)this + 430254) )
    {
      v14 = (double)*(int *)&g_Input.MouseState[8] * 0.1 + *((float *)this + 107561);
      *((float *)this + 107561) = v14;
      v20.z = v11;
      v15 = v20.z;
      *((_DWORD *)this + 107560) = LODWORD(v19.x);
      *((float *)this + 107561) = v14;
      *((float *)this + 107562) = v15;
    }
  }
}

// 0x00505770
char CCBStageCam::ClearFinishedTask(int a2)
{
  if ( !this->IsEditorCamValid(a2) )
    return 0;
  *((_BYTE *)this + 430012) = 1;
  ((CCCTData *)this)->Save(a2);
  *((_DWORD *)this + 107508) = a2;
  *((_DWORD *)this + 107509) = 0;
  return 1;
}

// 0x00505800
int CCBStageCam::AddTask()
{
  *((_BYTE *)this + 430012) = 0;
  *((_DWORD *)this + 107508) = -1;
  *((_DWORD *)this + 107509) = -1;
  return -1;
}

// 0x00505820
char CCBStageCam::ProcCamMove()
{
  char *v2; // eax
  char *v3; // ecx
  int v4; // eax
  char result; // al
  float v6; // [esp+4h] [ebp-18h] BYREF
  int v7; // [esp+8h] [ebp-14h]
  int v8; // [esp+Ch] [ebp-10h]
  float v9; // [esp+10h] [ebp-Ch] BYREF
  int v10; // [esp+14h] [ebp-8h]
  int v11; // [esp+18h] [ebp-4h]

  v2 = (char *)this + 430228;
  v6 = *((float *)this + 107557);
  v3 = (char *)this + 430240;
  v7 = *((_DWORD *)v2 + 1);
  v4 = *((_DWORD *)v2 + 2);
  v9 = *(float *)v3;
  v8 = v4;
  v10 = *((_DWORD *)v3 + 1);
  result = g_Input.KeyInfo[15].PressTime;
  v11 = *((_DWORD *)v3 + 2);
  v7 = 0;
  v10 = 0;
  if ( g_Input.KeyInfo[15].PressTime == 1 )
  {
    result = ((CCCTData *)this)->Create(&v6);
    if ( result )
    {
      *((_BYTE *)this + 430253) = 1;
    }
    else
    {
      result = ((CCCTData *)this)->Create(&v9);
      if ( result )
      {
        *((_BYTE *)this + 430254) = 1;
      }
      else
      {
        *((_BYTE *)this + 430253) = 0;
        *((_BYTE *)this + 430254) = 0;
      }
    }
  }
  if ( (g_Input.KeyInfo[15].Data & 0xF) != 1 )
  {
    *((_BYTE *)this + 430253) = 0;
    *((_BYTE *)this + 430254) = 0;
  }
  return result;
}

// 0x005058E0
int CCBStageCam::SwitchEditorCamPos()
{
  return (*(int (**)(_DWORD))(*(_DWORD *)(*((_DWORD *)this + 107556))->_pad_0000 + 20))(*((_DWORD *)this + 107556));
}
