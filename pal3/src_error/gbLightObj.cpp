#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/Object3D.h"
#include "Misc/ScriptVM.h"
#include "Misc/UIBigMap.h"

// 0x00423860
gbLightObj::~gbLightObj()
{
  char v2; // [esp+0x8] [ebp+0x4]

  (((ScriptVM *)this))->ScriptVM::ProcessFrame();
  if ( (v2 & 1) != 0 )
    operator delete(this);
}

// 0x0042BEE0
BOOL gbLightObj::IsIdle()
{
  return LOBYTE(this->m_HotSize) == 0;
}

// 0x0042C6A0
void gbLightObj::GetAABBox(gbAABBox *p)
{
  gbOBBox pMatrix; // [esp+0x4] [ebp-0x4C] BYREF

  (((Object3D *)&this[-1].m_SysLight.phi))->Object3D::SetTransform(&pMatrix.trans);
  (((gbOBBox *)&pMatrix))->gbOBBox::GetAABBox(*p);
}

// 0x0042C6E0
gbGfxManager * gbLightObj::GetGfxManager(int nVal1)
{
  gbGfxManager *result; // eax

  (((UIBigMap *)&this[-1].m_SysLight.phi))->UIBigMap::RenderRole(gfxMgr->pMatrixStack[1], nVal1);
  return result;
}

// 0x0042C8D0
int gbLightObj::GetCGEntry(char a2)
{
  int result; // eax

  (((gbLightObj *)((char *)this - 8)))->gbLightObj::~gbLightObj();
  return result;
}
