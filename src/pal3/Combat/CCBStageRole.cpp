#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageRole.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/SceneObj.h"

// Forward declarations for unnamed functions
int sub_50B430(...);
int sub_50B4C0(...);
int sub_50B4F0(...);
int sub_53DF80(...);

// 0x004ED040
char CCBStageRole::IsActive(int index)
{
  return *((_BYTE *)&this->m_OBBox.trans.zx + 892 * index + 3);
}

// 0x0050A180
int CCBStageRole::Grab(int a2)
{
  sub_50B430((char *)this, a2);
  sub_50B4C0(this);
  return sub_50B4F0(this);
}

// 0x0050A520
int CCBStageRole::GetStatus(int index)
{
  ((Actor *)this->m_bFlash)->PlayAction((int)&this->m_bFlashCounter);
  return this->m_bAlive;
}

// 0x0050A560
float * CCBStageRole::GetWorldPos()
{
  _BYTE v3[64]; // [esp+8h] [ebp-40h] BYREF

  ((gbMatrix4 *)v3)->gbMatrix4();
  ((Actor *)this->m_bFlash)->PlayAction((int)&this->m_bFlashCounter);
  ((gbMatrix4 *)v3)->LoadIdentity();
  ((gbMatrix4 *)v3)->SetAxisAngle(GB_AXIS_Y, *(float *)&this->m_Task[36].fp);
  ((gbMatrix4 *)&this->m_bFlashCounter)->RightMultiply((const struct gbMatrix4 *)v3);
  ((gbMatrix4 *)&this->m_bFlashCounter)->RightTranslate((struct gbVec3D *)&this->m_Task[35].cmd.bDestRole[7]);
  return (float *)&this->m_bFlashCounter;
}

// 0x0050A980
bool CCBStageRole::IsReady(int idx)
{
  return BYTE1(this->m_vThrowVec.x) && LODWORD(this->m_vThrowVec.y) == idx;
}

// 0x0050B330
char CCBStageRole::GetState()
{
  __int32 *bDestRole; // eax
  int v2; // edx

  bDestRole = (__int32 *)this->m_ThrowCmdData.bDestRole;
  v2 = 64;
  do
  {
    *((_BYTE *)bDestRole + 8) = 0;
    *bDestRole = 0;
    bDestRole += 24;
    --v2;
  }
  while ( v2 );
  this->m_vecLen.z = 0.0;
  return 1;
}

// 0x0050B530
int CCBStageRole::GetTaskState()
{
  int result; // eax
  float z; // edx
  float *v3; // edi

  result = LODWORD(this->m_vecLen.z);
  if ( result )
  {
    if ( result > 0 )
    {
      z = this->m_vecLen.z;
      v3 = (float *)&this->m_fThrowSpeed + 24 * result;
      do
      {
        --LODWORD(z);
        qmemcpy(v3, v3 - 24, 0x60u);
        v3 -= 24;
      }
      while ( z != 0.0 );
    }
    memset(&this->m_fThrowSpeed, 0, 0x60u);
    return 0;
  }
  return result;
}

// 0x0053E310
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void CCBStageRole::PlaySound(char *name, int a3)
{
  unsigned int v4; // ebp
  unsigned int v5; // kr08_4
  unsigned int v6; // ebp
  int i; // esi
  __int32 j; // edi
  char v9; // al
  int v10; // [esp+4h] [ebp-20h] BYREF
  char *v11; // [esp+8h] [ebp-1Ch]
  unsigned int v12; // [esp+Ch] [ebp-18h]
  int v13; // [esp+14h] [ebp-10h]
  int v14; // [esp+20h] [ebp-4h]

  if ( (g_nGameFlags & 1) != 0 )
  {
    LOBYTE(v10) = (_BYTE)name;
    ((std *)&v10)->string::_Tidy(0);
    v14 = 0;
    v4 = strlen((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    if ( ((SceneObj *)&v10)->Update(v4) )
    {
      qmemcpy(v11, &g_SceneMgr.m_npc[5].m_path.normal[140].y, v4);
      ((std *)&v10)->string::_Eos(v4);
    }
    v13 = 0;
    v5 = strlen(name) + 1;
    v6 = v5 - 1;
    v14 = 1;
    if ( ((SceneObj *)&v10)->Update(v5 - 1) )
    {
      qmemcpy(v11, name, v6);
      v12 = v5 - 1;
      v11[v6] = 0;
    }
    for ( i = this->m_Task[0].cmd.bDestRole[0]; i != this->m_Task[0].cmd.bDestRole[1]; i += 20 )
    {
      for ( j = this->m_Task[0].cmd.bDestRole[1]; i != j; i += 20 )
      {
        if ( sub_53DF80(i, (int)&v10) )
          break;
      }
      if ( i == this->m_Task[0].cmd.bDestRole[1] )
        break;
      if ( ((gbSound2DNode *)*(gbSound2DNode **)(i + 16))->IsPlaying() )
      {
        ((gbSound2DNode *)*(gbSound2DNode **)(i + 16))->Stop();
        break;
      }
    }
    if ( v11 )
    {
      v9 = *(v11 - 1);
      if ( !v9 || v9 == -1 )
        operator delete(v11 - 1);
      else
        *(v11 - 1) = v9 - 1;
    }
  }
}
