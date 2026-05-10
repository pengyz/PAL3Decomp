#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PalScript.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/PalScriptMgr.h"
#include "pal3/gen/Parent_Data.h"
#include "pal3/gen/PtrArray.h"
#include "pal3/gen/SceneObj.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_430670(...);
int sub_4307D0(...);
int sub_4309D0(...);
int sub_431040(...);
int sub_431780(...);
int sub_4318A0(...);
int sub_4319C0(...);
int sub_432990(...);

// Unnamed globals (extern)
extern char aBegin[];
extern char aBigmapScriptLo[];
extern char aDProjectPal3Sc[];
extern char aInitSce[];
extern char aInitScs[];
extern char aLangNull[];
extern char aPal3lang[];
extern char aScriptSysInitF[];
extern char aSystemScriptLo[];
extern char aUiBigmapBigmap[];
extern unsigned char byte_56A634;
extern int dword_1894B78;
extern int dword_BFDA60;
extern void *off_58B448;
extern int stru_D8C2B8;
extern int unknown_libname_339;
extern int unknown_libname_340;

// 0x00430290
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int PalScript::LoadScript(int pathAddr)
{
  unsigned int v2; // kr04_4
  unsigned int v3; // ebp
  unsigned int v4; // kr08_4
  unsigned int v5; // ebp
  _BYTE *v6; // ecx
  char v7; // al
  _BYTE *v8; // ecx
  char v9; // al
  int result; // eax
  char v11; // [esp+13h] [ebp-265h]
  SceneObj v12[2]; // [esp+14h] [ebp-264h] BYREF
  int v13; // [esp+274h] [ebp-4h]

  *(_DWORD *)&v12[0]._tail[16] = this;
  ctor_0x431870(&v12[0]._tail[60]);
  v13 = 0;
  ((PalScript *)&v12[0]._tail[60])->LoadFromFile((char *)pathAddr);
  ((PalScript *)&v12[0]._tail[60])->SetDirectory(aPal3lang);
  LOBYTE(v12[0]._p000) = v11;
  v12->string::_Tidy(0);
  for ( LOBYTE(v13) = 1; ((PalScript *)&v12[0]._tail[60])->HasNext(); *(_DWORD *)&v12[0]._tail[12] = 0 )
  {
    if ( !_strcmpi(&v12[0]._tail[60], off_58B448) )
      break;
    v2 = strlen(&v12[0]._tail[60]) + 1;
    v3 = v2 - 1;
    if ( v12->Update(v2 - 1) )
    {
      qmemcpy((void *)v12[0]._d004, &v12[0]._tail[60], v3);
      v12[0]._d008 = v2 - 1;
      *(_BYTE *)(v12[0]._d004 + v3) = 0;
    }
    ((PalScript *)&v12[0]._tail[60])->LoadNext();
    v12[0]._tail[0] = v11;
    ((std *)v12[0]._tail)->string::_Tidy(0);
    v4 = strlen(&v12[0]._tail[60]) + 1;
    v5 = v4 - 1;
    if ( ((SceneObj *)v12[0]._tail)->Update(v4 - 1) )
    {
      qmemcpy(*(void **)&v12[0]._tail[4], &v12[0]._tail[60], v5);
      *(_DWORD *)&v12[0]._tail[8] = v4 - 1;
      *(_BYTE *)(*(_DWORD *)&v12[0]._tail[4] + v5) = 0;
    }
    LOBYTE(v13) = 2;
    v12[0]._tail[20] = (char)v12[0]._p000;
    ((std *)&v12[0]._tail[20])->string::_Tidy(0);
    sub_4307D0((int)&v12[0]._tail[20], v12, 0, 0xFFFFFFFF);
    LOBYTE(v13) = 3;
    sub_430670((int)&v12[0]._tail[36], (int)v12[0]._tail);
    LOBYTE(v13) = 4;
    sub_4309D0(*(int *)&v12[0]._tail[16], &v12[0]._tail[52], &v12[0]._tail[20]);
    LOBYTE(v13) = 5;
    ((std *)&v12[0]._tail[36])->string::_Tidy(1);
    LOBYTE(v13) = 2;
    ((std *)&v12[0]._tail[20])->string::_Tidy(1);
    LOBYTE(v13) = 1;
    if ( *(_DWORD *)&v12[0]._tail[4] )
    {
      v6 = (_BYTE *)(*(_DWORD *)&v12[0]._tail[4] - 1);
      v7 = *(_BYTE *)(*(_DWORD *)&v12[0]._tail[4] - 1);
      if ( !v7 || v7 == -1 )
        operator delete(v6);
      else
        * v6 = (*)v7 - 1;
    }
    *(_DWORD *)&v12[0]._tail[4] = 0;
    *(_DWORD *)&v12[0]._tail[8] = 0;
  }
  if ( v12[0]._d004 )
  {
    v8 = (_BYTE *)(v12[0]._d004 - 1);
    v9 = *(_BYTE *)(v12[0]._d004 - 1);
    if ( !v9 || v9 == -1 )
      operator delete(v8);
    else
      * v8 = (*)v9 - 1;
  }
  v12[0]._d004 = 0;
  v12[0]._d008 = 0;
  v12[0]._d00C = 0;
  v13 = -1;
  sub_4318A0((int)&v12[0]._tail[60]);
  return result;
}

// 0x00430570
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char * PalScript::SetAppName(char *name)
{
  char *v3; // esi
  unsigned int v4; // kr04_4
  unsigned int v5; // ebx
  char *v6; // eax
  int d004; // ecx
  char **p_name; // eax
  char *v9; // esi
  char *v10; // esi
  char *result; // eax
  int v12; // [esp+10h] [ebp-24h] BYREF
  char v13[4]; // [esp+14h] [ebp-20h] BYREF
  int v14; // [esp+18h] [ebp-1Ch] BYREF
  char *v15; // [esp+1Ch] [ebp-18h]
  unsigned int v16; // [esp+20h] [ebp-14h]
  int v17; // [esp+30h] [ebp-4h]

  LOBYTE(v14) = (_BYTE)name;
  ((std *)&v14)->string::_Tidy(0);
  v3 = name;
  v4 = strlen(name) + 1;
  v5 = v4 - 1;
  if ( ((SceneObj *)&v14)->Update(v4 - 1) )
  {
    qmemcpy(v15, v3, v5);
    v16 = v4 - 1;
    v15[v5] = 0;
  }
  v17 = 0;
  v6 = (char *)*sub_431040(this, v13, (int)&v14);
  d004 = this->_d004;
  name = v6;
  if ( v6 == (char *)d004 || sub_431780((int)&v14, (int)(v6 + 12)) < 0 )
  {
    v12 = this->_d004;
    p_name = (char **)&v12;
  }
  else
  {
    p_name = &name;
  }
  v9 = (char *)*p_name;
  v17 = -1;
  ((std *)&v14)->string::_Tidy(1);
  if ( v9 == (char *)this->_d004 )
    return aLangNull;
  v10 = (char *)*((_DWORD *)v9 + 8);
  result = byte_56A634;
  if ( v10 )
    return v10;
  return result;
}

// 0x004318B0
void * PalScript::LoadFromFile(char *filename)
{
  struct gbVFile *v3; // eax
  struct gbVFile *v4; // esi
  unsigned int v5; // ebp
  void *v6; // edi
  OpenBaseFile v8; // [esp+34h] [ebp-10h] BYREF
  int v9; // [esp+40h] [ebp-4h]

  sub_4319C0((int)this);
  ((OpenBaseFile *)&v8)->OpenBaseFile();
  v9 = 0;
  v3 = (struct gbVFile *)g_pVFileSys->OpenFile(filename, 0x201u);
  v4 = v3;
  if ( v3 )
  {
    g_pVFileSys->Seek(v3, 0, 3);
    v5 = g_pVFileSys->TellPos(v4);
    g_pVFileSys->Seek(v4, 0, 1);
    v6 = (void *)malloc(v5 + 1);
    *((_DWORD *)this + 128) = v6;
    if ( v6 )
    {
      memset(v6, 0, v5 + 1);
      g_pVFileSys->Read(*((void **)this + 128), v5, v4);
      *((_DWORD *)this + 129) = *((_DWORD *)this + 128);
      g_pVFileSys->CloseFile(v4);
    }
  }
  v9 = -1;
  return ((OpenNULLFile *)&v8)->OpenNULLFile();
}

// 0x004319F0
int PalScript::SetDirectory(char *dir)
{
  BOOL v3; // edi
  int result; // eax

  v3 = 0;
  *((_DWORD *)this + 130) = *((_DWORD *)this + 128);
  for ( result = this->HasNext(); result; result = this->HasNext() )
  {
    if ( v3 )
    {
      result = _strcmpi(this->_pad_000, dir);
      if ( !result )
      {
        *((_DWORD *)this + 129) = *((_DWORD *)this + 130);
        return result;
      }
      v3 = 0;
    }
    else
    {
      v3 = _strcmpi(this->_pad_000, aBegin) == 0;
    }
  }
  return result;
}

// 0x00431A60
int PalScript::HasNext()
{
  int v2; // ecx
  PalScript *v3; // esi
  char v4; // al
  char v5; // al
  _BYTE *v6; // eax

  memset(this, 0, 0x200u);
  v2 = 0;
  if ( **((_BYTE **)this + 130) )
  {
    v3 = this;
    do
    {
      if ( v2 > 2 )
      {
        if ( v2 != 3 )
          return 1;
        if ( **((_BYTE **)this + 130) == 38 )
          goto LABEL_30;
      }
      else
      {
        if ( v2 == 2 )
        {
          v5 = **((_BYTE **)this + 130);
          if ( v5 == 59 )
          {
            v2 = 1;
          }
          else if ( v5 == 10 || v5 == 32 || v5 == 9 || v5 == 44 )
          {
            v2 = 255;
          }
          else if ( v5 != 13 )
          {
            v3->_pad_000[0] = v5;
            v3 = (PalScript *)((char *)v3 + 1);
          }
          goto LABEL_31;
        }
        if ( !v2 )
        {
          v4 = **((_BYTE **)this + 130);
          if ( v4 == 36 )
          {
            v2 = 3;
          }
          else if ( v4 == 59 )
          {
            v2 = 1;
          }
          else if ( v4 != 32 && v4 != 9 && v4 != 44 && v4 != 13 && v4 != 10 )
          {
            v3->_pad_000[0] = v4;
            v3 = (PalScript *)((char *)v3 + 1);
            v2 = 2;
          }
          goto LABEL_31;
        }
        if ( **((_BYTE **)this + 130) == 10 )
LABEL_30:
          v2 = 0;
      }
LABEL_31:
      v6 = (_BYTE *)(*((_DWORD *)this + 130) + 1);
      *((_DWORD *)this + 130) = v6;
    }
    while ( *v6 );
  }
  return 0;
}

// 0x00431B60
int PalScript::LoadNext()
{
  int result; // eax
  PalScript *v3; // esi
  char v4; // cl
  char v5; // cl
  _BYTE *v6; // ecx

  result = 0;
  memset(this, 0, 0x200u);
  if ( **((_BYTE **)this + 130) )
  {
    v3 = this;
    do
    {
      if ( result > 2 )
        break;
      if ( result == 2 )
      {
        v5 = **((_BYTE **)this + 130);
        if ( v5 == 38 )
        {
          result = 255;
        }
        else
        {
          v3->_pad_000[0] = v5;
          v3 = (PalScript *)((char *)v3 + 1);
        }
      }
      else if ( result )
      {
        result = **((_BYTE **)this + 130) != 10;
      }
      else
      {
        v4 = **((_BYTE **)this + 130);
        if ( v4 == 59 )
        {
          result = 1;
        }
        else if ( v4 == 36 )
        {
          result = 2;
        }
      }
      v6 = (_BYTE *)(*((_DWORD *)this + 130) + 1);
      *((_DWORD *)this + 130) = v6;
    }
    while ( *v6 );
  }
  return result;
}

// 0x00431D80
PalScript::PalScript()
{
  unknown_libname_339();
  atexit(unknown_libname_340);
}

// 0x00431F00
int PalScript::AddWaitObj()
{
  ((PalScript *)this)->AddCamObj();
  return atexit(PalScript::ClearAllCamObj);
}

// 0x00431F10
int PalScript::AddCamObj(int a1)
{
  LOBYTE(stru_D8C2B8.m_lpDI) = HIBYTE(a1);
  stru_D8C2B8.m_lpDIDKeyboard = 0;
  stru_D8C2B8.m_lpDIDMouse = 0;
  stru_D8C2B8.m_mouseSensitivity = 0.0;
  return 0;
}

// 0x00431F40
void PalScript::ClearAllCamObj()
{
  IDirectInputDevice8A v0; // al

  if ( (stru_D8C2B8.m_keyStates[4] & 0x10) == 0 )
  {
    stru_D8C2B8.m_keyStates[4] |= 0x10u;
    if ( stru_D8C2B8.m_lpDIDKeyboard )
    {
      v0 = stru_D8C2B8.m_lpDIDKeyboard[-1];
      if ( !*(_BYTE *)&v0 || v0 == 0xFF )
        operator delete(&stru_D8C2B8.m_lpDIDKeyboard[-1]);
      else
        stru_D8C2B8.m_lpDIDKeyboard[-1] = (IDirectInputDevice8A)(*(_BYTE *)&v0 - 1);
    }
    stru_D8C2B8.m_lpDIDKeyboard = 0;
    stru_D8C2B8.m_lpDIDMouse = 0;
    stru_D8C2B8.m_mouseSensitivity = 0.0;
  }
}

// 0x00431FA0
// attributes: thunk
int PalScript::ClearAllWaitObj()
{
  return PalScriptMgr::_CON_ReLoadScript();
}

// 0x00431FB0
int PalScript::Update()
{
  int result; // eax
  char pExceptionObject[1024]; // [esp+8h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+408h] [ebp-400h] BYREF

  PalScriptMgr::_CON_ReLoadScript();
  if ( !sub_432990(aInitScs) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aScriptSysInitF, aDProjectPal3Sc, 71),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( !((PtrArray *)&stru_D8C2B8.m_mousept)->InsertAt(aInitSce) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aSystemScriptLo, aDProjectPal3Sc, 73),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = (int)((PtrArray *)&stru_D8C2B8.m_mouseMinX)->InsertAt(aUiBigmapBigmap);
  if ( !result )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aBigmapScriptLo, aDProjectPal3Sc, 75),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x00434C00
char *PalScript::GetString()
{
  char *result; // eax

  if ( *(int *)&stru_D8C2B8.m_keyStates[64] < 0 )
  {
    result = 0;
  }
  else
  {
    --*(_DWORD *)&stru_D8C2B8.m_keyStates[64];
    result = (char *)(8 * *(_DWORD *)&stru_D8C2B8.m_keyStates[64] + 14205804);
  }
  if ( result )
  {
    if ( *result == 5 )
      return ((PtrArray *)*((_WORD *)result + 2))->SetAtGrow(0);
  }
  return result;
}

// 0x0043A250
int PalScript::Reset()
{
  int result; // eax

  ((UIWnd *)(UIWnd **)this + 19)->MoveWindow();
  ((UIWnd *)this)->UpdateChildren();
  return result;
}

// 0x0043AA00
struct gbVFileSystem * PalScript::OpenScript(const char *a2, char a3)
{
  gbRefObject *v4; // ecx
  int v5; // edi
  Scene *v6; // eax
  gbTexture *v7; // ecx
  OpenBaseFile v9; // [esp+8h] [ebp-110h] BYREF
  char Buffer[256]; // [esp+Ch] [ebp-10Ch] BYREF
  int v11; // [esp+114h] [ebp-4h]

  ((OpenBaseFile *)&v9)->OpenBaseFile();
  v11 = 0;
  sprintf(Buffer, "%s", a2);
  v4 = (gbRefObject *)*((_DWORD *)this + 49);
  if ( v4 )
    v4->Release();
  if ( a3 )
  {
    v5 = *(_DWORD *)dword_BFDA60->_pad_0000;
    v6 = ((_Texture_Info *)dword_1894B78)->_CalculateUV(Buffer);
    *((_DWORD *)this + 49) = (PalScript *)(*(int (**)(gbGfxManager *, Scene *))(v5 + 8))(dword_BFDA60, v6);
    *((_DWORD *)this + 50) = (PalScript *)((Parent_Data *)dword_1894B78)->Parent_Data(Buffer);
  }
  else
  {
    *((_DWORD *)this + 49) = (PalScript *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)dword_BFDA60->_pad_0000 + 8))(
                                  dword_BFDA60,
                                  Buffer);
  }
  v7 = (gbTexture *)*((_DWORD *)this + 49);
  if ( v7 )
    v7->LoadTexture(1);
  v11 = -1;
  return ((OpenNULLFile *)&v9)->OpenNULLFile();
}
