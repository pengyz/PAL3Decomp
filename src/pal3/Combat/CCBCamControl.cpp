#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBCamControl.h"
#include "pal3/gen/CCBStageEffect.h"
#include "pal3/gen/CEffect.h"

// Unnamed globals (extern)
extern char aGfxscriptGeomD[];
extern char aGfxscriptGeomD_0[];
extern unsigned char byte_17AAF64;
extern int nullsub_3;
extern void *off_56A694;

// 0x005081D0
// attributes: thunk
CCBCamControl::CCBCamControl()
{
  CCBCamControl::~CCBCamControl();
}

// 0x005081E0
CCBCamControl::~CCBCamControl()
{
  *(_DWORD *)&byte_17AAF64[1472] = 119;
  *(_DWORD *)&byte_17AAF64[1476] = 314;
  *(_DWORD *)&byte_17AAF64[1480] = 510;
  *(_DWORD *)&byte_17AAF64[1484] = 707;
  707;
}

// 0x00508220
// attributes: thunk
int CCBCamControl::Reset()
{
  return CCBCamControl::Create();
}

// 0x00508230
int CCBCamControl::Create()
{
  *(_DWORD *)&byte_17AAF64[1488] = 519;
  *(_DWORD *)&byte_17AAF64[1492] = 519;
  *(_DWORD *)&byte_17AAF64[1496] = 519;
  *(_DWORD *)&byte_17AAF64[1500] = 519;
  return 519;
}

// 0x00508270
// attributes: thunk
int CCBCamControl::Destroy()
{
  return CCBCamControl::Init();
}

// 0x00508280
int CCBCamControl::Init()
{
  *(_DWORD *)&byte_17AAF64[1504] = 128;
  *(_DWORD *)&byte_17AAF64[1508] = 323;
  *(_DWORD *)&byte_17AAF64[1512] = 519;
  *(_DWORD *)&byte_17AAF64[1516] = 716;
  return 716;
}

// 0x005082C0
// attributes: thunk
int CCBCamControl::Update()
{
  return CCBCamControl::StartList();
}

// 0x005082D0
int CCBCamControl::StartList()
{
  *(_DWORD *)&byte_17AAF64[1520] = 545;
  *(_DWORD *)&byte_17AAF64[1524] = 545;
  *(_DWORD *)&byte_17AAF64[1528] = 545;
  *(_DWORD *)&byte_17AAF64[1532] = 545;
  return 545;
}

// 0x00508310
// attributes: thunk
int CCBCamControl::StartList()
{
  return CCBCamControl::StopList();
}

// 0x00508320
int CCBCamControl::StopList()
{
  *(_DWORD *)&byte_17AAF64[1536] = 121;
  *(_DWORD *)&byte_17AAF64[1540] = 316;
  *(_DWORD *)&byte_17AAF64[1544] = 512;
  *(_DWORD *)&byte_17AAF64[1548] = 709;
  return 709;
}

// 0x00508360
// attributes: thunk
int CCBCamControl::HandleInput()
{
  return CCBCamControl::UpdateCircleSet();
}

// 0x00508370
int CCBCamControl::UpdateCircleSet()
{
  *(_DWORD *)&byte_17AAF64[1552] = 573;
  *(_DWORD *)&byte_17AAF64[1556] = 573;
  *(_DWORD *)&byte_17AAF64[1560] = 573;
  *(_DWORD *)&byte_17AAF64[1564] = 573;
  return 573;
}

// 0x005083B0
char * CCBCamControl::SetCircle(int a2)
{
  float *p_fFromZ; // eax
  int v4; // ecx

  ((gbVolModNode *)&this->m_CCT.m_Pool[0].bFinished)->gbVolModNode();
  `eh vector constructor iterator'(
    (char *)&this->m_CCT.m_Pool[0].fCircleCentreY,
    0xDCu,
    10,
    gbVolModNode::gbVolModNode,
    gbVolModNode::~gbVolModNode);
  p_fFromZ = (float *)&this->m_CCT.m_Pool[8].EndPos.fFromZ;
  v4 = 384;
  do
  {
    *(p_fFromZ - 2) = 0.0;
    *(p_fFromZ - 1) = 0.0;
    *p_fFromZ = 0.0;
    p_fFromZ[5] = 0.0;
    p_fFromZ[6] = 0.0;
    p_fFromZ[7] = 0.0;
    p_fFromZ += 15;
    --v4;
  }
  while ( v4 );
  nullsub_3(this);
  this->m_CCT.m_Pool[8].StartPos.pit = 0.0;
  this->m_CCT.m_Pool[8].StartPos.fRoll = 0.0;
  this->m_CCT.m_Pool[0].bValid = a2;
  return (char *)this;
}

// 0x005084C0
char CCBCamControl::IsPointerUnderMouse(int _this)
{
  int v2; // esi

  this->CCBStageEffect();
  v2 = ((operator *)0xD8u)->new();
  if ( v2 )
  {
    *(_DWORD *)(v2 + 4) = 1;
    *(_DWORD *)v2 = gbRefObject::`vftable';
    *(_DWORD *)v2 = gbVolumeModifier::`vftable';
    *(_DWORD *)(v2 + 96) = 0;
    *(_DWORD *)(v2 + 100) = 0;
    *(_DWORD *)(v2 + 104) = 0;
    ((CCBCamControl *)(v2 + 108))->LoadPointer();
    *(_DWORD *)v2 = &off_56A694;
  }
  else
  {
    v2 = 0;
  }
  v2->Init(0);
  *(_DWORD *)(v2 + 28) = 1008981770;
  *(_DWORD *)(v2 + 32) = 1008981770;
  *(_DWORD *)(v2 + 36) = 1008981770;
  *(_DWORD *)(v2 + 40) = 1065353216;
  *(_DWORD *)(v2 + 68) = 1;
  *(_DWORD *)(v2 + 72) = 1133903872;
  *(_DWORD *)(v2 + 84) = 1056964608;
  *(_DWORD *)(v2 + 12) = 1008981770;
  *(_DWORD *)(v2 + 44) = 1;
  *(_DWORD *)(v2 + 48) = 1;
  *(_DWORD *)(v2 + 16) = 1008981770;
  *(_DWORD *)(v2 + 52) = 0;
  *(_DWORD *)(v2 + 56) = 0;
  *(_DWORD *)(v2 + 20) = 1008981770;
  *(_DWORD *)(v2 + 60) = 0x40000000;
  *(_DWORD *)(v2 + 64) = 1133903872;
  *(_DWORD *)(v2 + 24) = 1065353216;
  ((gbVolModNode *)(this + 16))->SetVolModObj((struct gbVolumeModifier *)v2);
  ((gbRefObject *)v2)->Release();
  *(_DWORD *)(this + 2436) = ((gbEffectMgr *)*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200))->NewRenderEffect(aGfxscriptGeomD, 0x401u);
  *(_DWORD *)(this + 2440) = ((gbEffectMgr *)*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200))->NewRenderEffect(aGfxscriptGeomD_0, 0x441u);
  return 1;
}

// 0x00508660
_DWORD * CCBCamControl::LoadPointer()
{
  this->m_CCT.m_Pool[0].StartPos.z = 0.0;
  this->m_CCT.m_Pool[0].StartPos.fYaw = 0.0;
  this->m_CCT.m_Pool[0].StartPos.yaw = 0.0;
  this->m_CCT.m_Pool[0].StartPos.fPitch = 0.0;
  this->m_CCT.m_Pool[0].StartPos.pit = 0.0;
  this->m_CCT.m_Pool[0].StartPos.fRoll = 0.0;
  return this;
}

// 0x00508680
char CCBCamControl::DoList()
{
  ((gbRefObject *)*((_DWORD *)this + 609))->Release();
  return 1;
}

// 0x00508690
int CCBCamControl::ResetListFlag(int _this)
{
  int v2; // esi
  _DWORD *v3; // edx
  _DWORD *v4; // edx

  v2 = ((operator *)0xD8u)->new();
  if ( v2 )
  {
    *(_DWORD *)(v2 + 4) = 1;
    *(_DWORD *)v2 = gbRefObject::`vftable';
    *(_DWORD *)v2 = gbVolumeModifier::`vftable';
    ((gbVec3D *)(v2 + 96))->gbVec3D(0.0, 0.0, 0.0);
    ((CCBCamControl *)(v2 + 108))->LoadPointer();
    *(_DWORD *)v2 = &off_56A694;
  }
  else
  {
    v2 = 0;
  }
  v2->Init(0);
  *(_DWORD *)(v2 + 28) = 0;
  *(_DWORD *)(v2 + 32) = 0;
  *(_DWORD *)(v2 + 36) = 0;
  *(_DWORD *)(v2 + 40) = 1065353216;
  *(_DWORD *)(v2 + 68) = 1;
  *(_DWORD *)(v2 + 72) = 1133903872;
  *(_DWORD *)(v2 + 84) = 1056964608;
  *(_DWORD *)(v2 + 12) = 0;
  *(_DWORD *)(v2 + 44) = 1;
  *(_DWORD *)(v2 + 48) = 1;
  *(_DWORD *)(v2 + 16) = 0;
  *(_DWORD *)(v2 + 52) = 0;
  *(_DWORD *)(v2 + 56) = 0;
  *(_DWORD *)(v2 + 20) = 0;
  *(_DWORD *)(v2 + 60) = 0x40000000;
  *(_DWORD *)(v2 + 64) = 1133903872;
  *(_DWORD *)(v2 + 24) = 1065353216;
  ((gbVolModNode *)(this + 236))->SetVolModObj((struct gbVolumeModifier *)v2);
  ((gbRefObject *)v2)->Release();
  v3 = (_DWORD *)(*(_DWORD *)(this + 232) + 28);
  *v3 = -1098907648;
  v3[1] = -1098907648;
  v3[2] = -1098907648;
  v3[3] = 1065353216;
  v4 = (_DWORD *)(*(_DWORD *)(this + 452) + 28);
  *v4 = -1098907648;
  v4[1] = -1098907648;
  v4[2] = -1098907648;
  v4[3] = 1065353216;
  return -1098907647;
}

// 0x00508880
int CCBCamControl::KeepCurCam(int a2)
{
  float *p_rol; // edx
  int result; // eax
  float *i; // esi

  p_rol = (float *)&this->m_CCT.m_Pool[8].StartPos.rol;
  result = 0;
  for ( i = &this->m_CCT.m_Pool[8].StartPos.rol; *(_DWORD *)i != a2; i += 15 )
  {
    if ( ++result >= 384 )
    {
      result = 0;
      while ( *(_DWORD *)p_rol )
      {
        ++result;
        p_rol += 15;
        if ( result >= 384 )
          return 0;
      }
      *((_DWORD *)&this->m_CCT.m_Pool[8].StartPos.rol + 15 * result) = a2;
      return result;
    }
  }
  return result;
}

// 0x005088D0
int CCBCamControl::DoLineMove(unsigned int a2)
{
  int result; // eax
  CCBCamControl **v4; // esi
  int v5; // esi

  result = a2;
  if ( a2 < 0x180 )
  {
    v4 = this + 15 * a2;
    result = (int)v4[612];
    if ( result != -1 )
      result = ((CEffect *)*((CEffect **)(*((_DWORD *)this + 2))->m_CCT.m_Pool[0].fp + 11))->Render((int)v4[612]);
    v5 = (int)v4[619];
    if ( v5 != -1 )
      return ((CEffect *)*((CEffect **)(*((_DWORD *)this + 2))->m_CCT.m_Pool[0].fp + 11))->Render(v5);
  }
  return result;
}
