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
int sub_431870(...);
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
extern unsigned char byte_D8C2B8;
extern unsigned char byte_D8C324;
extern int dword_1894B78;
extern int dword_D8C2BC;
extern int dword_D8C2C0;
extern int dword_D8C2C4;
extern int dword_D8C2C8;
extern int dword_D8C2E8;
extern int dword_D8C360;
extern void *off_58B448;
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
  char *v6; // ecx
  char v7; // al
  char *v8; // ecx
  char v9; // al
  char v11; // [esp+13h] [ebp-265h]
  int v12; // [esp+14h] [ebp-264h] BYREF
  char *v13; // [esp+18h] [ebp-260h]
  unsigned int v14; // [esp+1Ch] [ebp-25Ch]
  int v15; // [esp+20h] [ebp-258h]
  int v16; // [esp+24h] [ebp-254h] BYREF
  char *v17; // [esp+28h] [ebp-250h]
  unsigned int v18; // [esp+2Ch] [ebp-24Ch]
  int v19; // [esp+30h] [ebp-248h]
  PalScript *v20; // [esp+34h] [ebp-244h]
  _DWORD v21[4]; // [esp+38h] [ebp-240h] BYREF
  _DWORD v22[4]; // [esp+48h] [ebp-230h] BYREF
  _DWORD v23[2]; // [esp+58h] [ebp-220h] BYREF
  PalScript String1[13]; // [esp+60h] [ebp-218h] BYREF
  int v25; // [esp+274h] [ebp-4h]

  v20 = this;
  sub_431870(String1);
  v25 = 0;
  String1->LoadFromFile((char *)pathAddr);
  String1->SetDirectory(aPal3lang);
  LOBYTE(v12) = v11;
  ((std *)&v12)->string::_Tidy(0);
  for ( LOBYTE(v25) = 1; String1->HasNext(); v19 = 0 )
  {
    if ( !_strcmpi((const char *)String1, off_58B448) )
      break;
    v2 = strlen((const char *)String1) + 1;
    v3 = v2 - 1;
    if ( ((SceneObj *)&v12)->Update(v2 - 1) )
    {
      qmemcpy(v13, String1, v3);
      v14 = v2 - 1;
      v13[v3] = 0;
    }
    String1->LoadNext();
    LOBYTE(v16) = v11;
    ((std *)&v16)->string::_Tidy(0);
    v4 = strlen((const char *)String1) + 1;
    v5 = v4 - 1;
    if ( ((SceneObj *)&v16)->Update(v4 - 1) )
    {
      qmemcpy(v17, String1, v5);
      v18 = v4 - 1;
      v17[v5] = 0;
    }
    LOBYTE(v25) = 2;
    LOBYTE(v21[0]) = v12;
    v21->string::_Tidy(0);
    sub_4307D0((int)v21, &v12, 0, 0xFFFFFFFF);
    LOBYTE(v25) = 3;
    sub_430670((int)v22, (int)&v16);
    LOBYTE(v25) = 4;
    sub_4309D0((int)v20, v23, (int)v21);
    LOBYTE(v25) = 5;
    v22->string::_Tidy(1);
    LOBYTE(v25) = 2;
    v21->string::_Tidy(1);
    LOBYTE(v25) = 1;
    if ( v17 )
    {
      v6 = (char *)v17 - 1;
      v7 = *(v17 - 1);
      if ( !v7 || v7 == -1 )
        operator delete(v6);
      else
        * v6 = (*)v7 - 1;
    }
    v17 = 0;
    v18 = 0;
  }
  if ( v13 )
  {
    v8 = (char *)v13 - 1;
    v9 = *(v13 - 1);
    if ( !v9 || v9 == -1 )
      operator delete(v8);
    else
      * v8 = (*)v9 - 1;
  }
  v13 = 0;
  v14 = 0;
  v15 = 0;
  v25 = -1;
  return sub_4318A0(String1);
}

// 0x00430570
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char * PalScript::SetAppName(char *name)
{
  char *v3; // esi
  unsigned int v4; // kr04_4
  unsigned int v5; // ebx
  char *v6; // eax
  scScriptInstance *m_pinst; // ecx
  char **p_name; // eax
  char *v9; // esi
  char *v10; // esi
  char *result; // eax
  scScriptInstance *v12; // [esp+10h] [ebp-24h] BYREF
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
  v6 = (char *)*sub_431040(v13, (int)&v14);
  m_pinst = (scScriptInstance *)this->m_pinst;
  name = v6;
  if ( v6 == (char *)m_pinst || sub_431780((int)&v14, (int)(v6 + 12)) < 0 )
  {
    v12 = (scScriptInstance *)this->m_pinst;
    p_name = (char **)&v12;
  }
  else
  {
    p_name = &name;
  }
  v9 = (char *)*p_name;
  v17 = -1;
  ((std *)&v14)->string::_Tidy(1);
  if ( v9 == (char *)this->m_pinst )
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
  return ((OpenNULLFile **)&v8)->OpenNULLFile();
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
      result = _strcmpi((const char *)this, dir);
      if ( !result )
      {
        *((_DWORD *)this + 129) = *((_DWORD *)this + 130);
        return result;
      }
      v3 = 0;
    }
    else
    {
      v3 = _strcmpi((const char *)this, aBegin) == 0;
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
            LOBYTE(v3->m_bLoadSceneScript) = v5;
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
            LOBYTE(v3->m_bLoadSceneScript) = v4;
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
          LOBYTE(v3->m_bLoadSceneScript) = v5;
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
  return atexit(unknown_libname_340);
}

// 0x00431F00
int PalScript::AddWaitObj()
{
  ((int)this)->AddCamObj();
  return atexit(PalScript::ClearAllCamObj);
}

// 0x00431F10
int PalScript::AddCamObj(int a1)
{
  byte_D8C2B8 = HIBYTE(a1);
  dword_D8C2BC = 0;
  dword_D8C2C0 = 0;
  dword_D8C2C4 = 0;
  return 0;
}

// 0x00431F40
void PalScript::ClearAllCamObj()
{
  char v0; // al

  if ( (byte_D8C324 & 0x10) == 0 )
  {
    byte_D8C324 |= 0x10u;
    if ( dword_D8C2BC )
    {
      v0 = *(_BYTE *)(dword_D8C2BC - 1);
      if ( !v0 || v0 == -1 )
        operator delete((void *)(dword_D8C2BC - 1));
      else
        *(_BYTE *)(dword_D8C2BC - 1) = v0 - 1;
    }
    dword_D8C2BC = 0;
    dword_D8C2C0 = 0;
    dword_D8C2C4 = 0;
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
  if ( !sub_432990((int)aInitScs) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aScriptSysInitF, aDProjectPal3Sc, 71),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( !((int)dword_D8C2E8)->InsertAt(aInitSce) )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aSystemScriptLo, aDProjectPal3Sc, 73),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = (int)((int)dword_D8C2C8)->InsertAt(aUiBigmapBigmap);
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

  if ( dword_D8C360 < 0 )
  {
    result = 0;
  }
  else
  {
    --dword_D8C360;
    result = (char *)(8 * dword_D8C360 + 14205804);
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
  CHAR *v6; // eax
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
    v5 = *(_DWORD *)g_Input.KeyInfo[177].Data;
    v6 = ((int)dword_1894B78)->_CalculateUV(Buffer);
    *((_DWORD *)this + 49) = (PalScript *)(*(int (**)(int, CHAR *))(v5 + 8))(g_Input.KeyInfo[177].Data, v6);
    *((_DWORD *)this + 50) = (PalScript *)((int)dword_1894B78)->Parent_Data(Buffer);
  }
  else
  {
    *((_DWORD *)this + 49) = (PalScript *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                                  g_Input.KeyInfo[177].Data,
                                  Buffer);
  }
  v7 = (gbTexture *)*((_DWORD *)this + 49);
  if ( v7 )
    v7->LoadTexture(1);
  v11 = -1;
  return ((OpenNULLFile **)&v9)->OpenNULLFile();
}
