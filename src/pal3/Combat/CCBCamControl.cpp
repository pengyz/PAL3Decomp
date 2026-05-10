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
int CCBCamControl::CCBCamControl()
{
  return CCBCamControl::~CCBCamControl();
}

// 0x005081E0
CCBCamControl::~CCBCamControl()
{
  *(_DWORD *)&byte_17AAF64[1472] = 119;
  *(_DWORD *)&byte_17AAF64[1476] = 314;
  *(_DWORD *)&byte_17AAF64[1480] = 510;
  *(_DWORD *)&byte_17AAF64[1484] = 707;
  return 707;
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
  char *v3; // eax
  int v4; // ecx

  ((gbVolModNode *)&this->m_CCT[16])->gbVolModNode();
  `eh vector constructor iterator'(
    &this->m_CCT[236],
    0xDCu,
    10,
    gbVolModNode::gbVolModNode,
    gbVolModNode::~gbVolModNode);
  v3 = (char *)&this->m_CCT[2464];
  v4 = 384;
  do
  {
    *((_DWORD *)v3 - 2) = 0;
    *((_DWORD *)v3 - 1) = 0;
    *(_DWORD *)v3 = 0;
    *((_DWORD *)v3 + 5) = 0;
    *((_DWORD *)v3 + 6) = 0;
    *((_DWORD *)v3 + 7) = 0;
    v3 += 60;
    --v4;
  }
  while ( v4 );
  nullsub_3(this);
  *(_DWORD *)&this->m_CCT[2436] = 0;
  *(_DWORD *)&this->m_CCT[2440] = 0;
  *(_DWORD *)&this->m_CCT[8] = a2;
  return this->m_CCT;
}

// 0x005084C0
char CCBCamControl::IsPointerUnderMouse(int _this)
{
  gbRefObject *v2; // esi

  this->CCBStageEffect();
  v2 = (gbRefObject *)((operator *)0xD8u)->new();
  if ( v2 )
  {
    v2[1].RefCount = 1;
    v2->RefCount = (int)gbRefObject::`vftable';
    v2->RefCount = (int)gbVolumeModifier::`vftable';
    v2[24].RefCount = 0;
    v2[25].RefCount = 0;
    v2[26].RefCount = 0;
    ((CCBCamControl *)&v2[27])->LoadPointer();
    v2->RefCount = (int)&off_56A694;
  }
  else
  {
    v2 = 0;
  }
  v2->Init(0);
  v2[7].RefCount = 1008981770;
  v2[8].RefCount = 1008981770;
  v2[9].RefCount = 1008981770;
  v2[10].RefCount = 1065353216;
  v2[17].RefCount = 1;
  v2[18].RefCount = 1133903872;
  v2[21].RefCount = 1056964608;
  v2[3].RefCount = 1008981770;
  v2[11].RefCount = 1;
  v2[12].RefCount = 1;
  v2[4].RefCount = 1008981770;
  v2[13].RefCount = 0;
  v2[14].RefCount = 0;
  v2[5].RefCount = 1008981770;
  v2[15].RefCount = 0x40000000;
  v2[16].RefCount = 1133903872;
  v2[6].RefCount = 1065353216;
  ((gbVolModNode *)(this + 16))->SetVolModObj((struct gbVolumeModifier *)v2);
  v2->Release();
  *(_DWORD *)(this + 2436) = ((gbEffectMgr *)*(gbEffectMgr **)(g_pGfxManager + 200))->NewRenderEffect(aGfxscriptGeomD, 0x401u);
  *(_DWORD *)(this + 2440) = ((gbEffectMgr *)*(gbEffectMgr **)(g_pGfxManager + 200))->NewRenderEffect(aGfxscriptGeomD_0, 0x441u);
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
  gbRefObject *v2; // esi
  _DWORD *v3; // edx
  _DWORD *v4; // edx

  v2 = (gbRefObject *)((operator *)0xD8u)->new();
  if ( v2 )
  {
    v2[1].RefCount = 1;
    v2->RefCount = (int)gbRefObject::`vftable';
    v2->RefCount = (int)gbVolumeModifier::`vftable';
    ((gbVec3D *)&v2[24])->gbVec3D(0.0, 0.0, 0.0);
    ((CCBCamControl *)&v2[27].RefCount)->LoadPointer();
    v2->RefCount = (int)&off_56A694;
  }
  else
  {
    v2 = 0;
  }
  v2->Init(0);
  v2[7].RefCount = 0;
  v2[8].RefCount = 0;
  v2[9].RefCount = 0;
  v2[10].RefCount = 1065353216;
  v2[17].RefCount = 1;
  v2[18].RefCount = 1133903872;
  v2[21].RefCount = 1056964608;
  v2[3].RefCount = 0;
  v2[11].RefCount = 1;
  v2[12].RefCount = 1;
  v2[4].RefCount = 0;
  v2[13].RefCount = 0;
  v2[14].RefCount = 0;
  v2[5].RefCount = 0;
  v2[15].RefCount = 0x40000000;
  v2[16].RefCount = 1133903872;
  v2[6].RefCount = 1065353216;
  ((gbVolModNode *)(this + 236))->SetVolModObj((struct gbVolumeModifier *)v2);
  v2->Release();
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
