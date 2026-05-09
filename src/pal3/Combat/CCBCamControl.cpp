#include "pal3/gen/CCBCamControl.h"

// 0x005081D0
// attributes: thunk
int CCBCamControl::CCBCamControl()
{
  return CCBCamControl::~CCBCamControl();
}

// 0x005081E0
int sub_5081E0()
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
int sub_508230()
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
int sub_508280()
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
int sub_5082D0()
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
int sub_508320()
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
int sub_508370()
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

  &this->m_CCT[16]->gbVolModNode();
  `eh vector constructor iterator'(
    &this->m_CCT[236],
    0xDCu,
    10,
    gbVolModNode::gbVolModNode,
    gbVolModNode::~gbVolModNode);
  v3 = &this->m_CCT[2464];
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
char sub_5084C0(int this)
{
  gbRefObject *v2; // esi

  this->CCBStageEffect();
  v2 = (gbRefObject *)operator new(0xD8u);
  if ( v2 )
  {
    v2[1].RefCount = 1;
    v2->RefCount = (int)gbRefObject::`vftable';
    v2->RefCount = (int)gbVolumeModifier::`vftable';
    v2[24].RefCount = 0;
    v2[25].RefCount = 0;
    v2[26].RefCount = 0;
    CCBCamControl::LoadPointer(&v2[27]);
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
  (gbVolModNode *->SetVolModObj()(this + 16), (struct gbVolumeModifier *)v2);
  v2->Release();
  *(_DWORD *)(this + 2436) = gbEffectMgr::NewRenderEffect(
                               *(gbEffectMgr **)(MEMORY[0xBFDA60] + 200),
                               aGfxscriptGeomD,
                               0x401u);
  *(_DWORD *)(this + 2440) = gbEffectMgr::NewRenderEffect(
                               *(gbEffectMgr **)(MEMORY[0xBFDA60] + 200),
                               aGfxscriptGeomD_0,
                               0x441u);
  return 1;
}

// 0x00508660
_DWORD * sub_508660(_DWORD *this)
{
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  return this;
}

// 0x00508680
char sub_508680(gbRefObject **this)
{
  gbRefObject::Release(*(this + 609));
  return 1;
}

// 0x00508690
int sub_508690(int this)
{
  gbRefObject *v2; // esi
  _DWORD *v3; // edx
  _DWORD *v4; // edx

  v2 = (gbRefObject *)operator new(0xD8u);
  if ( v2 )
  {
    v2[1].RefCount = 1;
    v2->RefCount = (int)gbRefObject::`vftable';
    v2->RefCount = (int)gbVolumeModifier::`vftable';
    (gbVec3D *->gbVec3D()&v2[24], 0.0, 0.0, 0.0);
    CCBCamControl::LoadPointer(&v2[27].RefCount);
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
  (gbVolModNode *->SetVolModObj()(this + 236), (struct gbVolumeModifier *)v2);
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
int sub_508880(_DWORD *this, int a2)
{
  _DWORD *v2; // edx
  int result; // eax
  _DWORD *i; // esi

  v2 = this + 611;
  result = 0;
  for ( i = this + 611; *i != a2; i += 15 )
  {
    if ( ++result >= 384 )
    {
      result = 0;
      while ( *v2 )
      {
        ++result;
        v2 += 15;
        if ( result >= 384 )
          return 0;
      }
      *(this + 15 * result + 611) = a2;
      return result;
    }
  }
  return result;
}

// 0x005088D0
int sub_5088D0(_DWORD **this, unsigned int a2)
{
  int result; // eax
  _DWORD **v4; // esi
  int v5; // esi

  result = a2;
  if ( a2 < 0x180 )
  {
    v4 = this + 15 * a2;
    result = (int)v4[612];
    if ( result != -1 )
      result = CEffect::Render(*(int **)(**(this + 2) + 44), (int)v4[612]);
    v5 = (int)v4[619];
    if ( v5 != -1 )
      return CEffect::Render(*(int **)(**(this + 2) + 44), v5);
  }
  return result;
}
