#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBCamControl.h"
#include "pal3/gen/CCBStageEffect.h"
#include "pal3/gen/CEffect.h"

// Unnamed globals (extern)
extern char aGfxscriptGeomD[];
extern char aGfxscriptGeomD_0[];
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
  *((_QWORD *)&g_bSceneLoaded + 184) = 0x13A00000077LL;
  *((_QWORD *)&g_bSceneLoaded + 185) = 0x2C3000001FELL;
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
  *((_QWORD *)&g_bSceneLoaded + 186) = 0x20700000207LL;
  *((_QWORD *)&g_bSceneLoaded + 187) = 0x20700000207LL;
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
  *((_QWORD *)&g_bSceneLoaded + 188) = 0x14300000080LL;
  *((_QWORD *)&g_bSceneLoaded + 189) = 0x2CC00000207LL;
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
  *((_QWORD *)&g_bSceneLoaded + 190) = 0x22100000221LL;
  *((_QWORD *)&g_bSceneLoaded + 191) = 0x22100000221LL;
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
  *((_QWORD *)&g_bSceneLoaded + 192) = 0x13C00000079LL;
  *((_QWORD *)&g_bSceneLoaded + 193) = 0x2C500000200LL;
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
  *((_QWORD *)&g_bSceneLoaded + 194) = 0x23D0000023DLL;
  *((_QWORD *)&g_bSceneLoaded + 195) = 0x23D0000023DLL;
  return 573;
}

// 0x005083B0
char * CCBCamControl::SetCircle(int a2)
{
  char *v3; // eax
  int v4; // ecx

  ((gbVolModNode *)&this->m_CCT._data[16])->gbVolModNode();
  `eh vector constructor iterator'(
    &this->m_CCT._data[236],
    0xDCu,
    10,
    gbVolModNode::gbVolModNode,
    gbVolModNode::~gbVolModNode);
  v3 = (char *)&this->m_CCT._data[2464];
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
  *(_DWORD *)&this->m_CCT._data[2436] = 0;
  *(_DWORD *)&this->m_CCT._data[2440] = 0;
  *(_DWORD *)&this->m_CCT._data[8] = a2;
  return this->m_CCT._data;
}

// 0x005084C0
char CCBCamControl::IsPointerUnderMouse()
{
  _DWORD *v2; // esi

  ((CCBStageEffect *)this)->CCBStageEffect();
  v2 = (_DWORD *)operator new(0xD8u);
  if ( v2 )
  {
    v2[1] = 1;
    * v2 = (*)gbRefObject::`vftable';
    * v2 = (*)gbVolumeModifier::`vftable';
    v2[24] = 0;
    v2[25] = 0;
    v2[26] = 0;
    ((CCBCamControl *)(v2 + 27))->LoadPointer();
    * v2 = (*)&off_56A694;
  }
  else
  {
    v2 = 0;
  }
  v2->Init(0);
  v2[7] = 1008981770;
  v2[8] = 1008981770;
  v2[9] = 1008981770;
  v2[10] = 1065353216;
  v2[17] = 1;
  v2[18] = 1133903872;
  v2[21] = 1056964608;
  v2[3] = 1008981770;
  v2[11] = 1;
  v2[12] = 1;
  v2[4] = 1008981770;
  v2[13] = 0;
  v2[14] = 0;
  v2[5] = 1008981770;
  v2[15] = 0x40000000;
  v2[16] = 1133903872;
  v2[6] = 1065353216;
  ((gbVolModNode *)&this->m_CCT._data[16])->SetVolModObj((struct gbVolumeModifier *)v2);
  ((gbRefObject *)v2)->Release();
  *(_DWORD *)&this->m_CCT._data[2436] = ((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptGeomD, 0x401u);
  *(_DWORD *)&this->m_CCT._data[2440] = ((gbEffectMgr *)g_pGfxMgr->pEffectMgr)->NewRenderEffect(aGfxscriptGeomD_0, 0x441u);
  return 1;
}

// 0x00508660
_DWORD * CCBCamControl::LoadPointer()
{
  *(_DWORD *)&this->m_CCT._data[52] = 0;
  *(_DWORD *)&this->m_CCT._data[56] = 0;
  *(_DWORD *)&this->m_CCT._data[60] = 0;
  *(_DWORD *)&this->m_CCT._data[64] = 0;
  *(_DWORD *)&this->m_CCT._data[68] = 0;
  *(_DWORD *)&this->m_CCT._data[72] = 0;
  return this->m_CCT._data;
}

// 0x00508680
char CCBCamControl::DoList()
{
  ((gbRefObject *)*((_DWORD *)this + 609))->Release();
  return 1;
}

// 0x00508690
int CCBCamControl::ResetListFlag()
{
  _DWORD *v2; // esi
  _DWORD *v3; // edx
  _DWORD *v4; // edx

  v2 = (_DWORD *)operator new(0xD8u);
  if ( v2 )
  {
    v2[1] = 1;
    * v2 = (*)gbRefObject::`vftable';
    * v2 = (*)gbVolumeModifier::`vftable';
    ((gbVec3D *)(gbVec3D *)v2 + 8)->gbVec3D(0.0, 0.0, 0.0);
    ((CCBCamControl *)(v2 + 27))->LoadPointer();
    * v2 = (*)&off_56A694;
  }
  else
  {
    v2 = 0;
  }
  v2->Init(0);
  v2[7] = 0;
  v2[8] = 0;
  v2[9] = 0;
  v2[10] = 1065353216;
  v2[17] = 1;
  v2[18] = 1133903872;
  v2[21] = 1056964608;
  v2[3] = 0;
  v2[11] = 1;
  v2[12] = 1;
  v2[4] = 0;
  v2[13] = 0;
  v2[14] = 0;
  v2[5] = 0;
  v2[15] = 0x40000000;
  v2[16] = 1133903872;
  v2[6] = 1065353216;
  ((gbVolModNode *)&this->m_CCT._data[236])->SetVolModObj((struct gbVolumeModifier *)v2);
  ((gbRefObject *)v2)->Release();
  v3 = (_DWORD *)(*(_DWORD *)&this->m_CCT._data[232] + 28);
  *v3 = -1098907648;
  v3[1] = -1098907648;
  v3[2] = -1098907648;
  v3[3] = 1065353216;
  v4 = (_DWORD *)(*(_DWORD *)&this->m_CCT._data[452] + 28);
  *v4 = -1098907648;
  v4[1] = -1098907648;
  v4[2] = -1098907648;
  v4[3] = 1065353216;
  return -1098907647;
}

// 0x00508880
int CCBCamControl::KeepCurCam(int a2)
{
  char *v2; // edx
  int result; // eax
  char *i; // esi

  v2 = (char *)&this->m_CCT._data[2444];
  result = 0;
  for ( i = &this->m_CCT._data[2444]; *(_DWORD *)i != a2; i += 60 )
  {
    if ( ++result >= 384 )
    {
      result = 0;
      while ( *(_DWORD *)v2 )
      {
        ++result;
        v2 += 60;
        if ( result >= 384 )
          return 0;
      }
      *(_DWORD *)&this->m_CCT._data[60 * result + 2444] = a2;
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
      result = ((CEffect *)*(CEffect **)(*(_DWORD *)(*((_DWORD *)this + 2))->m_CCT._data + 44))->Render((int)v4[612]);
    v5 = (int)v4[619];
    if ( v5 != -1 )
      return ((CEffect *)*(CEffect **)(*(_DWORD *)(*((_DWORD *)this + 2))->m_CCT._data + 44))->Render(v5);
  }
  return result;
}
