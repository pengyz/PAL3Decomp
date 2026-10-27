#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIBigMap.h"
#include "Role/Actor.h"
#include "Misc/Array.h"
#include "Misc/BINK.h"
#include "Combat/CCBControlWindow.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffgbParticle.h"
#include "Render/CScreenMode.h"
#include "Scene/Camera.h"
#include "Scene/CameraCtrl.h"
#include "UI/EquipUI.h"
#include "Misc/GeomNode.h"
#include "UI/MagicUI.h"
#include "Misc/MainEquipUI.h"
#include "Misc/MainPropUI.h"
#include "Role/NPC.h"
#include "Misc/NameSys.h"
#include "Role/Object3D.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Misc/OpenSceneFile.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PathObj.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneMgr.h"
#include "Scene/SceneObj.h"
#include "Misc/ScriptSystemData.h"
#include "UI/StateUI.h"
#include "Misc/UIButton.h"
#include "Misc/UIButtonEX.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "UI/UINote.h"
#include "Misc/UIParticle.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4947E0(...);
int sub_494880(...);

// Unnamed globals (extern)
extern CHAR byte_DC6A3C[256];
extern CHAR byte_DC773C[256];
void __cdecl nullsub_10(void);
void __cdecl nullsub_7(void);
void __cdecl nullsub_8(void);
void __cdecl nullsub_9(void);

// 0x00414E50
int UIBigMap::UpdateActions(int *deltatime, int haveinput)
{
  int v4; // eax
  float v5; // st7
  float v6; // st7
  float v7; // st6
  float v9; // [esp+0x8] [ebp-0x18]
  float v10; // [esp+0xC] [ebp-0x14]
  float v11; // [esp+0x10] [ebp-0x10]
  float v12; // [esp+0x10] [ebp-0x10]
  gbVec3D v13; // [esp+0x14] [ebp-0xC] BYREF

  (((RoleSystem *)this))->RoleSystem::Notify() /* [ROWTABLE] */;
  *(_DWORD *)&this->m_Element[1].m_btn.m_caption[112] = 11;
  *(_DWORD *)&this->m_Element[1].m_btn.m_caption[116] = haveinput;
  v4 = *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 5);
  if ( v4 != 4 )
    *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 4) = v4;
  *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 5) = 4;
  this->m_Element[2].m_btn.m_childs.m_needscriptdel = *(_DWORD *)&this->buf[56];
  this->m_Element[2].m_btn.m_bcreateok = *(_DWORD *)&this->buf[60];
  this->m_Element[2].m_btn.m_bvisible = *(_DWORD *)&this->buf[64];
  *(_DWORD *)&this->m_Element[1].m_btn.m_caption[124] = (unsigned long)*deltatime;
  *(_DWORD *)&this->m_Element[1].m_btn.m_benable_snd = (unsigned long)deltatime[1];
  *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 1) = (unsigned long)deltatime[2];
  *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 2) = 1056964608;
  *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 3) = 0;
  v9 = *(float *)&this->buf[56] - *(float *)&this->m_Element[1].m_btn.m_caption[124];
  v5 = *(float *)&this->buf[60] - *(float *)&this->m_Element[1].m_btn.m_benable_snd;
  v13.x = v9;
  v10 = v5;
  v6 = *(float *)&this->buf[64] - *((float *)&this->m_Element[1].m_btn.m_benable_snd + 1);
  v13.y = v10;
  v11 = v6;
  v13.z = v11;
  (((gbVec3D *)&v13))->gbVec3D::Normalize();
  v7 = 0.0f - v13.z;
  v12 = v13.x - 0.0f;
  *(_DWORD *)&this->m_Element[1].m_isBtnCreate = 0;
  *(float *)&this->m_Element[1].m_btn.m_surecolor.Color = v7;
  *(float *)&this->m_Element[2].m_bShow = v12;
  (((gbVec3D *)&this->m_Element[1].m_btn.m_surecolor))->gbVec3D::Normalize();
  return (((Actor *)&this->m_Element[0].m_btn.m_texarray.m_ptex[13]))->Actor::CompareActionName(18, 0);
}

// 0x00418260
int UIBigMap::UpdateTransform(int deltatime, float *haveinput)
{
  float v3; // ebx
  int v6; // ecx
  int v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float v12; // edx
  float v13; // eax
  gbVec3D *v14; // edi
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float v18; // edx
  float v19; // eax
  float v20; // st7
  float *v21; // eax
  float *v22; // eax
  float *v23; // eax
  float v24; // edx
  float v25; // eax
  float v26; // st7
  float *v27; // eax
  float *v28; // eax
  float *v29; // eax
  float *v30; // eax
  float v31; // edx
  float v32; // eax
  float *v33; // eax
  float *v34; // eax
  float *v35; // eax
  float *v36; // eax
  float v37; // edx
  float v38; // eax
  float v39; // st7
  float *v40; // eax
  const gbVec3D *v41; // eax
  RoleSystem *v42; // ecx
  float *v43; // eax
  RoleSystem *v44; // ecx
  const gbVec3D *v45; // eax
  gbVec3D *v46; // eax
  RoleSystem *v47; // ecx
  float *v48; // eax
  const gbVec3D *v49; // eax
  float *p_m_nSize; // esi
  int v51; // esi
  float v52; // [esp+0x94] [ebp-0x68]
  float v53; // [esp+0x98] [ebp-0x64]
  float v54; // [esp+0x98] [ebp-0x64]
  float v55; // [esp+0x98] [ebp-0x64]
  float v56; // [esp+0x98] [ebp-0x64]
  float v57; // [esp+0x98] [ebp-0x64]
  float v58; // [esp+0x9C] [ebp-0x60]
  float v59; // [esp+0x9C] [ebp-0x60]
  float v60; // [esp+0x9C] [ebp-0x60]
  float v61; // [esp+0x9C] [ebp-0x60]
  float v62; // [esp+0x9C] [ebp-0x60]
  float v63; // [esp+0x9C] [ebp-0x60]
  float v64; // [esp+A0h] [ebp-0x5C]
  float v65; // [esp+A0h] [ebp-0x5C]
  float v66; // [esp+A0h] [ebp-0x5C]
  float v67; // [esp+A0h] [ebp-0x5C]
  float v68; // [esp+A0h] [ebp-0x5C]
  float v69; // [esp+A0h] [ebp-0x5C]
  float v70; // [esp+A0h] [ebp-0x5C]
  float v71; // [esp+A0h] [ebp-0x5C]
  float v72; // [esp+A0h] [ebp-0x5C]
  float v73; // [esp+A0h] [ebp-0x5C]
  float v74; // [esp+A0h] [ebp-0x5C]
  float v75; // [esp+A0h] [ebp-0x5C]
  float v76; // [esp+A0h] [ebp-0x5C]
  float v77; // [esp+A0h] [ebp-0x5C]
  float v78; // [esp+A0h] [ebp-0x5C]
  float v79; // [esp+A0h] [ebp-0x5C]
  float v80; // [esp+A0h] [ebp-0x5C]
  float v81; // [esp+A0h] [ebp-0x5C]
  float v82; // [esp+A4h] [ebp-0x58]
  float v83; // [esp+A4h] [ebp-0x58]
  float v84; // [esp+A4h] [ebp-0x58]
  float v85; // [esp+A4h] [ebp-0x58]
  float v86; // [esp+A4h] [ebp-0x58]
  float v87; // [esp+A4h] [ebp-0x58]
  float v88; // [esp+A4h] [ebp-0x58]
  float v89; // [esp+A4h] [ebp-0x58]
  float v90; // [esp+A4h] [ebp-0x58]
  float v91; // [esp+A4h] [ebp-0x58]
  float v92; // [esp+A4h] [ebp-0x58]
  float v93; // [esp+A4h] [ebp-0x58]
  float v94; // [esp+A4h] [ebp-0x58]
  float v95; // [esp+A4h] [ebp-0x58]
  float v96; // [esp+A4h] [ebp-0x58]
  float v97; // [esp+A8h] [ebp-0x54]
  float v98; // [esp+A8h] [ebp-0x54]
  float v99; // [esp+A8h] [ebp-0x54]
  float v100; // [esp+A8h] [ebp-0x54]
  float v101; // [esp+A8h] [ebp-0x54]
  float v102; // [esp+A8h] [ebp-0x54]
  float v103; // [esp+A8h] [ebp-0x54]
  float v104; // [esp+A8h] [ebp-0x54]
  float v105; // [esp+A8h] [ebp-0x54]
  float v106; // [esp+A8h] [ebp-0x54]
  float v107; // [esp+A8h] [ebp-0x54]
  float v108; // [esp+A8h] [ebp-0x54]
  float v109; // [esp+A8h] [ebp-0x54]
  float fLerpFactor; // [esp+B4h] [ebp-0x48]
  float pSrc; // [esp+B8h] [ebp-0x44] BYREF
  float v112; // [esp+BCh] [ebp-0x40]
  struct gbVec3D v113; // [esp+C0h] [ebp-0x3C] BYREF
  gbVec3D v114; // [esp+CCh] [ebp-0x30] BYREF
  float v115; // [esp+D8h] [ebp-0x24] BYREF
  gbVec3D nVal; // [esp+DCh] [ebp-0x20] BYREF
  float pOut[2]; // [esp+E8h] [ebp-0x14] BYREF
  gbVec3D v118; // [esp+F0h] [ebp-0xC] BYREF

  if ( !this->m_Element[0].m_btn.m_texarray.m_ptex[1] )
    return 0;
  if ( !*(_DWORD *)&this->buf[40] )
    return 0;
  if ( *(_DWORD *)&this->buf[156] == 3 )
    return 0;
  v6 = *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 5);
  if ( v6 == 4 )
  {
    v7 = *(_DWORD *)&this->m_Element[1].m_btn.m_caption[112];
    if ( v7 == 7 || v7 == 8 )
    {
      if ( *(_DWORD *)&this->m_Element[1].m_btn.m_caption[116] )
        return 0;
    }
  }
  if ( v6 != 4 || *(_DWORD *)&this->m_Element[1].m_btn.m_caption[112] )
  {
    v59 = -*(float *)&this->m_childs.capacity;
    v53 = -*(float *)&this->m_childs.m_pData;
    v52 = -*(float *)&this->m_pfather;
    pSrc = *v33;
    v112 = v33[1];
    v113.x = v33[2];
    v78 = v113.x - *(float *)&this->m_rect.bottom;
    v60 = v112 - *(float *)&this->m_rect.right;
    v54 = pSrc - *(float *)&this->m_rect.top;
    ((gbVec3D *)pOut)->gbVec3D::gbVec3D(v54, v60, v78);
    pSrc = *v34;
    v112 = v34[1];
    v113.x = v34[2];
    v79 = v113.x * fLerpFactor;
    v61 = v112 * fLerpFactor;
    v55 = pSrc * fLerpFactor;
    pSrc = *v35;
    v112 = v35[1];
    v113.x = v35[2];
    v80 = v113.x + *(float *)&this->buf[64];
    v62 = v112 + *(float *)&this->buf[60];
    v56 = pSrc + *(float *)&this->buf[56];
    ((gbVec3D *)&v114.y)->gbVec3D::gbVec3D(v56, v62, v80);
    pSrc = *v36;
    v37 = v36[1];
    v38 = v36[2];
    v14 = (gbVec3D *)haveinput;
    v112 = v37;
    *haveinput = pSrc;
    haveinput[1] = v37;
    haveinput[2] = v38;
    v39 = *(float *)&this->m_childs.capacity - *(float *)&this->m_rect.bottom;
    v113.x = v38;
    v81 = v39;
    v63 = *(float *)&this->m_childs.m_pData - *(float *)&this->m_rect.right;
    v57 = *(float *)&this->m_pfather - *(float *)&this->m_rect.top;
    ((gbVec3D *)&v118.y)->gbVec3D::gbVec3D(v57, v63, v81);
    pSrc = *v40;
    v112 = v40[1];
    v113.x = v40[2];
    Vec3Lerp(pOut, &pSrc, fLerpFactor, v3);
    (((RoleSystem *)&nVal))->RoleSystem::AddVec3ToTarget((int)&nVal, (int)&this->buf[56]);
    ((gbVec3D *)((gbVec3D *)haveinput + 1))->gbVec3D::operator=(*(v41));
    (((RoleSystem *)v42))->RoleSystem::AddVec3ToTarget((int)&v118.y, (int)&this->m_pfather);
    Vec3Lerp(pOut, v43, fLerpFactor, v96);
    (((RoleSystem *)v44))->RoleSystem::AddVec3ToTarget((int)&nVal, (int)&this->buf[56]);
    ((gbVec3D *)((gbVec3D *)haveinput + 2))->gbVec3D::operator=(*(v45));
    v46 = ((gbVec3D *( *)(gbVec3D *__return_ptr __struct_ptr, gbVec3D *))gbVec3D::operator-)(
            (gbVec3D *)&this->m_pfather,
            *((gbVec3D *)&v118.y));
    (((RoleSystem *)v47))->RoleSystem::AddVec3ToTarget((int)&nVal.z, (int)v46);
    Vec3Lerp(&v115, v48, _pal3_coerce_f32((UIBigMap *)&this->m_rect.top), fLerpFactor);
    (((RoleSystem *)&v114))->RoleSystem::AddVec3ToTarget((int)&v114, (int)&this->buf[56]);
    ((gbVec3D *)((gbVec3D *)haveinput + 3))->gbVec3D::operator=(*(v49));
  }
  else
  {
    v82 = -*(float *)&this->m_childs.capacity;
    v64 = -*(float *)&this->m_childs.m_pData;
    v58 = -*(float *)&this->m_pfather;
    pSrc = *v8;
    v112 = v8[1];
    v113.x = v8[2];
    v97 = v113.x - *(float *)&this->m_rect.bottom;
    v83 = v112 - *(float *)&this->m_rect.right;
    v65 = pSrc - *(float *)&this->m_rect.top;
    pSrc = *v9;
    v112 = v9[1];
    v113.x = v9[2];
    v98 = v113.x * fLerpFactor;
    v84 = v112 * fLerpFactor;
    v66 = pSrc * fLerpFactor;
    ((gbVec3D *)pOut)->gbVec3D::gbVec3D(v66, v84, v98);
    pSrc = *v10;
    v112 = v10[1];
    v113.x = v10[2];
    v99 = v113.x + *(float *)&this->buf[52];
    v85 = v112 + *(float *)&this->buf[48];
    v67 = pSrc + *(float *)&this->buf[44];
    ((gbVec3D *)&v118.y)->gbVec3D::gbVec3D(v67, v85, v99);
    pSrc = *v11;
    v12 = v11[1];
    v13 = v11[2];
    v112 = v12;
    v113.x = v13;
    v14 = (gbVec3D *)haveinput;
    *haveinput = pSrc;
    haveinput[1] = v12;
    haveinput[2] = v13;
    v100 = *(float *)&this->m_childs.capacity - *(float *)&this->m_rect.bottom;
    v86 = *(float *)&this->m_childs.m_pData - *(float *)&this->m_rect.right;
    v68 = *(float *)&this->m_pfather - *(float *)&this->m_rect.top;
    ((gbVec3D *)&v118.y)->gbVec3D::gbVec3D(v68, v86, v100);
    pSrc = *v15;
    v112 = v15[1];
    v113.x = v15[2];
    v101 = v113.x * fLerpFactor;
    v87 = v112 * fLerpFactor;
    v69 = pSrc * fLerpFactor;
    ((gbVec3D *)pOut)->gbVec3D::gbVec3D(v69, v87, v101);
    pSrc = *v16;
    v112 = v16[1];
    v113.x = v16[2];
    v102 = v113.x + *(float *)&this->buf[52];
    v88 = v112 + *(float *)&this->buf[48];
    v70 = pSrc + *(float *)&this->buf[44];
    pSrc = *v17;
    v112 = v17[1];
    v18 = v112;
    v19 = v17[2];
    haveinput[3] = pSrc;
    haveinput[4] = v18;
    haveinput[5] = v19;
    v20 = *(float *)&this->m_childs.capacity + *(float *)&this->m_rect.bottom;
    v113.x = v19;
    v103 = v20;
    v89 = *(float *)&this->m_childs.m_pData + *(float *)&this->m_rect.right;
    v71 = *(float *)&this->m_rect.top + *(float *)&this->m_pfather;
    ((gbVec3D *)&v118.y)->gbVec3D::gbVec3D(v71, v89, v103);
    pSrc = *v21;
    v112 = v21[1];
    v113.x = v21[2];
    v104 = v113.x * fLerpFactor;
    v90 = v112 * fLerpFactor;
    v72 = pSrc * fLerpFactor;
    ((gbVec3D *)pOut)->gbVec3D::gbVec3D(v72, v90, v104);
    pSrc = *v22;
    v112 = v22[1];
    v113.x = v22[2];
    v105 = v113.x + *(float *)&this->buf[52];
    v91 = v112 + *(float *)&this->buf[48];
    v73 = pSrc + *(float *)&this->buf[44];
    pSrc = *v23;
    v112 = v23[1];
    v24 = v112;
    v25 = v23[2];
    haveinput[6] = pSrc;
    haveinput[7] = v24;
    haveinput[8] = v25;
    v106 = -*(float *)&this->m_childs.capacity;
    v26 = *(float *)&this->m_childs.m_pData;
    v113.x = v25;
    v92 = -v26;
    v74 = -*(float *)&this->m_pfather;
    ((gbVec3D *)&v118.y)->gbVec3D::gbVec3D(v74, v92, v106);
    pSrc = *v27;
    v112 = v27[1];
    v113.x = v27[2];
    v107 = v113.x + *(float *)&this->m_rect.bottom;
    v93 = v112 + *(float *)&this->m_rect.right;
    v75 = pSrc + *(float *)&this->m_rect.top;
    ((gbVec3D *)pOut)->gbVec3D::gbVec3D(v75, v93, v107);
    pSrc = *v28;
    v112 = v28[1];
    v113.x = v28[2];
    v108 = v113.x * fLerpFactor;
    v94 = v112 * fLerpFactor;
    v76 = pSrc * fLerpFactor;
    pSrc = *v29;
    v112 = v29[1];
    v113.x = v29[2];
    v109 = v113.x + *(float *)&this->buf[52];
    v95 = v112 + *(float *)&this->buf[48];
    v77 = pSrc + *(float *)&this->buf[44];
    ((gbVec3D *)&v114.y)->gbVec3D::gbVec3D(v77, v95, v109);
    pSrc = *v30;
    v112 = v30[1];
    v31 = v112;
    v32 = v30[2];
    haveinput[9] = pSrc;
    v113.x = v32;
    haveinput[10] = v31;
    haveinput[11] = v32;
  }
  p_m_nSize = (float *)&this->m_childs.m_nSize;
  v113.y = *p_m_nSize;
  v113.z = p_m_nSize[1];
  v114.x = p_m_nSize[2];
  (((gbVec3D *)&v113.y))->gbVec3D::operator*=(1.0);
  v51 = 4;
  do
  {
    (((gbVec3D *)v14++))->gbVec3D::operator+=(*(&v113));
    --v51;
  }
  while ( v51 );
  return 1;
}

// 0x00423A70
void UIBigMap::LoadScene(int element, const char *visible)
{
  char *v4; // esi
  int v5; // ebx
  char *v6; // eax
  char *v7; // eax
  int v8; // ecx
  char *v9; // eax
  bool v10; // zf
  _BYTE *v11; // eax
  UIWnd **p_m_pfather; // eax
  int *p_m_bcreateok; // esi
  int v14; // eax
  char v15; // al
  gbSound3DNode *v16; // eax
  _BYTE *v17; // eax
  _BYTE *v18; // esi
  int *v19; // eax
  _BYTE *pData; // ebp
  const char *v21; // esi
  int *p_bkWndX; // ebx
  char v23; // al
  gbGeomNode *v24; // eax
  gbGeomNode *v25; // esi
  gbGeomNode *v26; // ecx
  char v27; // al
  gbGeomNode *v28; // eax
  gbGeomNode *v29; // esi
  gbGeomNode *v30; // ecx
  int v31; // eax
  long double v32; // st7
  _DWORD *v33; // eax
  _DWORD *v34; // esi
  _DWORD *v35; // ebx
  int v36; // edi
  _DWORD *v37; // ebx
  int v38; // edi
  int v39; // eax
  _DWORD *v40; // edi
  int bkWndX; // eax
  char v42; // al
  int capacity; // [esp+0xC] [ebp-0x188]
  OpenSceneFile v44; // [esp+0x20] [ebp-0x174] BYREF
  int v45; // [esp+0x24] [ebp-0x170]
  gbVec3D *v46; // [esp+0x28] [ebp-0x16C]
  int p_DWORD[3]; // [esp+0x2C] [ebp-0x168] BYREF
  gbMatrix4 pMatrix; // [esp+0x38] [ebp-0x15C] BYREF
  float v49[2]; // [esp+0x78] [ebp-0x11C]
  float v50; // [esp+0x80] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x84] [ebp-0x110] BYREF
  int v52; // [esp+0x190] [ebp-0x4]

  (((BINK *)this))->BINK::Destroy();
  v4 = (char *)&this->buf[68];
  v5 = element - (_DWORD)&this->buf[68];
  *(_DWORD *)&this->buf[68] = *(_DWORD *)element;
  v6 = (char *)&this->buf[72];
  do
  {
    *v6 = v6[v5];
    ++v6;
  }
  while ( (unsigned int)&v6[-4 - (_DWORD)&this->buf[68]] < 0x20 );
  this->buf[104] = *(_BYTE *)(element + 36);
  this->buf[105] = *(_BYTE *)(element + 37);
  *(_DWORD *)&this->buf[108] = *(_DWORD *)(element + 40);
  *(_DWORD *)&this->buf[112] = *(_DWORD *)(element + 44);
  *(_DWORD *)&this->buf[116] = *(_DWORD *)(element + 48);
  *(_DWORD *)&this->buf[120] = *(_DWORD *)(element + 52);
  *(_DWORD *)&this->buf[124] = *(_DWORD *)(element + 56);
  *(_DWORD *)&this->buf[128] = *(_DWORD *)(element + 60);
  *(_DWORD *)&this->buf[132] = *(_DWORD *)(element + 64);
  *(_DWORD *)&this->buf[136] = *(_DWORD *)(element + 68);
  this->buf[140] = *(_BYTE *)(element + 72);
  this->buf[141] = *(_BYTE *)(element + 73);
  this->buf[142] = *(_BYTE *)(element + 74);
  this->buf[143] = *(_BYTE *)(element + 75);
  v7 = (char *)&this->buf[144];
  v8 = 6;
  do
  {
    *(_DWORD *)v7 = *(_DWORD *)&v7[v5];
    v7 += 4;
    --v8;
  }
  while ( v8 );
  this->buf[168] = *(_BYTE *)(element + 100);
  *(_WORD *)&this->buf[170] = *(_WORD *)(element + 102);
  *(_WORD *)&this->buf[172] = *(_WORD *)(element + 104);
  *(_WORD *)&this->buf[174] = *(_WORD *)(element + 106);
  *(_WORD *)&this->buf[176] = *(_WORD *)(element + 108);
  this->buf[178] = *(_BYTE *)(element + 110);
  v9 = (char *)&this->buf[179];
  do
  {
    *v9 = v9[v5];
    ++v9;
  }
  while ( (unsigned int)&v9[-111 - (_DWORD)v4] < 0x10 );
  *(_DWORD *)&this->buf[196] = *(_DWORD *)(element + 128);
  *(_DWORD *)&this->buf[200] = *(_DWORD *)(element + 132);
  v46 = (gbVec3D *)&this->buf[204];
  v44 = (OpenSceneFile)(element - (_DWORD)v4);
  v45 = 16;
  do
  {
    (((gbVec3D *)v46))->gbVec3D::operator=(*((gbVec3D *)((char *)v46 + *(_DWORD *)&v44)));
    v10 = v45 == 1;
    ++v46;
    --v45;
  }
  while ( !v10 );
  v11 = (_BYTE *)(&this->ms_BigMap.m_mouseoff + 2);
  *(_WORD *)&this->ms_BigMap.m_mouseoff = *(_WORD *)(element + 328);
  do
  {
    *v11 = v11[v5];
    ++v11;
  }
  while ( (unsigned int)&v11[-330 - (_DWORD)v4] < 0x20 );
  *((_BYTE *)((UIWnd *)&this->m_Element[0].m_btn) + 2) = *(_BYTE *)(element + 362);
  (((gbVec3D *)&this->m_Element[0].m_btn.m_fontcolor))->gbVec3D::operator=(*((const gbVec3D *)(element + 364)));
  (((gbVec3D *)&this->m_Element[0].m_btn.m_rect))->gbVec3D::operator=(*((const gbVec3D *)(element + 376)));
  this->m_Element[0].m_btn.m_rect.bottom = *(_DWORD *)(element + 388);
  p_m_pfather = (UIWnd **)&this->m_Element[0].m_btn.m_pfather;
  do
  {
    *(_BYTE *)p_m_pfather = *((_BYTE *)p_m_pfather + v5);
    p_m_pfather = (UIWnd **)((char *)p_m_pfather + 1);
  }
  while ( (unsigned int)p_m_pfather - 392 - (unsigned int)v4 < 8 );
  this->m_Element[0].m_btn.m_childs.capacity = *(_DWORD *)(element + 400);
  this->m_Element[0].m_btn.m_childs.m_nSize = *(_DWORD *)(element + 404);
  this->m_Element[0].m_btn.m_childs.m_needscriptdel = *(_DWORD *)(element + 408);
  p_m_bcreateok = (int *)&this->m_Element[0].m_btn.m_bcreateok;
  v14 = 52;
  do
  {
    *p_m_bcreateok = *(int *)((char *)p_m_bcreateok + v5);
    ++p_m_bcreateok;
    --v14;
  }
  while ( v14 );
  this->buf[104] = RoleSystem::SetAnimBlend(element);
  this->m_childs.capacity = *(_DWORD *)&this->buf[108];
  this->m_childs.m_nSize = *(_DWORD *)&this->buf[112];
  this->m_childs.m_needscriptdel = *(_DWORD *)&this->buf[116];
  v15 = this->buf[140];
  if ( v15 != 37 )
  {
    if ( v15 == 43 )
    {
      if ( (g_dwGameFlags & 1) != 0 )
      {
        v16 = (gbSound3DNode *)operator new(0x40u);
        v44 = (OpenSceneFile)v16;
        v52 = 0;
        if ( v16 )
          v16->gbSound3DNode::gbSound3DNode();
        else
          v17 = 0;
        this->m_Element[0].m_btn.m_optData.pData = v17;
        v52 = -1;
        sprintf(Buffer, "snd\\%s.wav", &this->buf[72]);
        if ( (((gbSound3DNode *)this->m_Element[0].m_btn.m_optData.pData))->gbSound3DNode::LoadFromFile(Buffer) )
        {
          *((_DWORD *)this->m_Element[0].m_btn.m_optData.pData + 13) = 0;
          v19 = (int *)(this->m_Element[0].m_btn.m_optData.pData + 8);
          *v19 = this->m_childs.capacity;
          v19[1] = this->m_childs.m_nSize;
          v19[2] = this->m_childs.m_needscriptdel;
          pData = this->m_Element[0].m_btn.m_optData.pData;
          *((_DWORD *)pData + 14) = 1116471296;
          *((_DWORD *)pData + 15) = 1153138688;
        }
        else
        {
          v18 = this->m_Element[0].m_btn.m_optData.pData;
          if ( v18 )
          {
            (((gbSound3DNode *)this->m_Element[0].m_btn.m_optData.pData))->gbSound3DNode::~gbSound3DNode();
            operator delete(v18);
          }
          this->m_Element[0].m_btn.m_optData.pData = 0;
        }
      }
    }
    else
    {
      if ( v15 == 23 && *(_DWORD *)&this->buf[152] == 1 )
        LOBYTE(g_ScriptSystemData.m_nScriptFlag) = this->buf[71] == 0;
      v21 = (const char *)(element + 4);
      if ( strlen((const char *)(element + 4)) )
      {
        if ( *v21 == 95 )
        {
          sprintf(Buffer, "%s%s", "scene\\", visible);
          v52 = 1;
          sprintf(Buffer, "%s\\%s", visible + 64, v21);
          p_bkWndX = (int *)&this->bkWndX;
          (((GeomNode *)&this->bkWndX))->GeomNode::InitFromFile((const gbGeomNode *)Buffer, 0);
          v23 = this->buf[140];
          if ( v23 == 3 || v23 == 13 )
          {
            strcpy((char *)&Buffer[strlen((const char *)Buffer) - 4], "A.pol");
            v24 = (gbGeomNode *)operator new(0x118u);
            v25 = (gbGeomNode *)v24;
            v45 = (int)v24;
            LOBYTE(v52) = 2;
            if ( v24 )
            {
              v24->gbGeomNode::gbGeomNode();
              v26 = (gbGeomNode *)v25;
            }
            else
            {
              v26 = 0;
            }
            LOBYTE(v52) = 1;
            this->m_bcreateok = (int)v26;
            (((gbGeomNode *)v26))->gbGeomNode::LoadFromFile(Buffer, 0, 0);
          }
          v52 = -1;
          (((OpenSceneFile *)&v44))->OpenSceneFile::~OpenSceneFile();
        }
        else
        {
          if ( *v21 == 43 )
          {
            ((OpenBaseFile *)&v44)->OpenBaseFile::OpenBaseFile();
            p_bkWndX = (int *)&this->bkWndX;
            capacity = this->m_Element[0].m_btn.m_childs.capacity;
            v52 = 3;
            (((GeomNode *)&this->bkWndX))->GeomNode::InitFromFile((const gbGeomNode *)v21, capacity);
            v52 = -1;
          }
          else if ( strchr(v21, 46) )
          {
            ((OpenBaseFile *)&v44)->OpenBaseFile::OpenBaseFile();
            v52 = 5;
            sprintf(Buffer, "object\\%s", v21);
            p_bkWndX = (int *)&this->bkWndX;
            (((GeomNode *)&this->bkWndX))->GeomNode::InitFromFile((const gbGeomNode *)Buffer, 0);
            v27 = this->buf[140];
            if ( v27 == 3 || v27 == 13 )
            {
              strcpy((char *)&Buffer[strlen((const char *)Buffer) - 4], "A.pol");
              v28 = (gbGeomNode *)operator new(0x118u);
              v29 = (gbGeomNode *)v28;
              v45 = (int)v28;
              LOBYTE(v52) = 6;
              if ( v28 )
              {
                v28->gbGeomNode::gbGeomNode();
                v30 = (gbGeomNode *)v29;
              }
              else
              {
                v30 = 0;
              }
              LOBYTE(v52) = 5;
              this->m_bcreateok = (int)v30;
              (((gbGeomNode *)v30))->gbGeomNode::LoadFromFile(Buffer, 0, 0);
            }
            v52 = -1;
          }
          else
          {
            ((OpenBaseFile *)&v44)->OpenBaseFile::OpenBaseFile();
            v52 = 4;
            sprintf(Buffer, "item\\%s\\%s.pol", v21, v21);
            p_bkWndX = (int *)&this->bkWndX;
            (((GeomNode *)&this->bkWndX))->GeomNode::InitFromFile((const gbGeomNode *)Buffer, 0);
            v52 = -1;
          }
          ((OpenNULLFile *)&v44)->OpenNULLFile::OpenNULLFile();
        }
        switch ( this->buf[140] )
        {
          case 1:
          case 2:
          case 0xC:
          case 0x13:
          case 0x17:
          case 0x1A:
          case 0x1D:
          case 0x20:
          case 0x29:
            if ( *p_bkWndX == 3 )
            {
              (((gbVisNode *)this->bkWndY))->gbVisNode::SetTimeScale(0.0);
              (*(void ( **)(int, _DWORD))(*(_DWORD *)this->bkWndY + 24))(this->bkWndY, 0);
              (((PalScript *)p_bkWndX))->PalScript::GetCount(0);
            }
            break;
          case 4:
          case 6:
          case 0xE:
            (((gbVisNode *)this->bkWndY))->gbVisNode::SetTimeScale(0.0);
            (*(void ( **)(int, _DWORD))(*(_DWORD *)this->bkWndY + 24))(this->bkWndY, 0);
            break;
          case 5:
            v33 = (_DWORD *)operator new(0x1C28u);
            v34 = (_DWORD *)v33;
            v44 = (OpenSceneFile)v33;
            v52 = 7;
            if ( v33 )
            {
              v35 = (_DWORD *)v33;
              v36 = 256;
              do
              {
                v35 += 3;
                --v36;
              }
              while ( v36 );
              v37 = (_DWORD *)(v34 + 1026);
              v38 = 256;
              do
              {
                v37 += 3;
                --v38;
              }
              while ( v38 );
              v34[1796] = 0;
              v34[1797] = 0;
              v34[1798] = 0;
              v34[1799] = 0;
              v34[1800] = 0;
              v34[1801] = 0;
              v34[768] = 0;
            }
            else
            {
              v34 = 0;
            }
            v39 = *(_DWORD *)&this->buf[200];
            *(_DWORD *)&this->m_Element[0].m_btn.m_caption[68] = (_DWORD)v34;
            v34[768] = v39;
            v40 = (_DWORD *)(*(_DWORD **)&this->m_Element[0].m_btn.m_caption[68]);
            v52 = -1;
            qmemcpy(v40, &this->buf[204], 12 * v40[768]);
            (((PathObj *)*(PathObj **)&this->m_Element[0].m_btn.m_caption[68]))->PathObj::CalcLength();
            LOBYTE(this->screenrect.right) = 0;
            break;
          case 0xD:
            this->m_bvisible = *(_DWORD *)&this->buf[108];
            this->m_benable = *(_DWORD *)&this->buf[112];
            this->m_bfocus = *(_DWORD *)&this->buf[116];
            this->screenrect.left = 0;
            v32 = *(float *)&this->buf[120] * 0.017453292;
            *(float *)&this->m_pbktex = sin(v32);
            *(float *)&this->screenrect.top = cos(v32);
            *(float *)&this->m_pbktex = *(float *)&this->m_pbktex * 200.0;
            *(float *)&this->screenrect.left = *(float *)&this->screenrect.left * 200.0;
            *(float *)&this->screenrect.top = *(float *)&this->screenrect.top * 200.0;
            LOBYTE(this->screenrect.right) = 0;
            v44 = (OpenSceneFile)(rand() % 300);
            *(float *)&this->screenrect.bottom = (double)*(int *)&v44 * 0.0099999998;
            break;
          case 0x11:
            if ( *(_DWORD *)&this->buf[148] && *p_bkWndX == 3 )
            {
              (((gbVisNode *)this->bkWndY))->gbVisNode::SetTimeScale(0.0);
              (*(void ( **)(int, _DWORD))(*(_DWORD *)this->bkWndY + 24))(this->bkWndY, 0);
              (((PalScript *)p_bkWndX))->PalScript::GetCount(0);
            }
            v31 = rand();
            this->m_pbktex = ((gbTexture *)0);
            v44 = (OpenSceneFile)(v31 % 10);
            *(float *)&this->screenrect.left = (float)(v31 % 10);
            break;
          default:
            break;
        }
      }
      if ( this->buf[140] == 24 && *(_DWORD *)&this->buf[148] == 1 )
      {
        p_DWORD[1] = 0;
        p_DWORD[2] = 0;
        p_DWORD[0] = *(_DWORD *)&this->buf[144];
        if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(p_DWORD) )
          this->buf[69] = 0;
      }
      bkWndX = this->bkWndX;
      if ( bkWndX == 2 || bkWndX == 3 )
      {
        (((PalScriptMgr *)this))->PalScriptMgr::BuildCmdTransform(&pMatrix);
        *(float *)&this->m_Element[0].m_btn.m_optData.width = sqrt(v50 * v50 + v49[0] * v49[0]) * 0.5;
      }
      if ( this->bkWndX == 3 )
      {
        v42 = this->buf[140];
        if ( v42 == 4
          || v42 == 6
          || v42 == 12
          || v42 == 14
          || v42 == 16
          || v42 == 19
          || v42 == 23
          || v42 == 26
          || v42 == 32
          || v42 == 41 )
        {
          (((gbGeomNode *)this->bkWndY))->gbGeomNode::SetAnimLoop(1);
        }
      }
      if ( this->buf[69] && this->bkWndX == 4 && !_strcmpi(&this->buf[72], a4_0) )
        (((CEffMgr *)this->bkWndY))->CEffMgr::SetEffectClass(*(_DWORD *)&this->buf[108], *(_DWORD *)&this->buf[112], *(_DWORD *)&this->buf[116]);
      this->m_Element[0].m_btn.m_optData.bpp = *(_DWORD *)&this->buf[120];
    }
  }
}

// 0x00424570
void UIBigMap::RenderRole(gbMatrixStack *pStack, int visible)
{
  CScreenMode *v4; // ecx
  RoleSystem *v5; // eax
  float *p_m_fPosX; // eax
  float v7; // st6
  float v8; // st5
  float v9; // st5
  char v10; // al
  CScreenMode *SoundList; // eax
  char v12; // al
  int *p_capacity; // edi
  float v14; // edx
  float x; // edi
  RoleSystem *v16; // [esp+0x28] [ebp-0x80]
  int v17; // [esp+0x28] [ebp-0x80]
  gbVec3D v18; // [esp+0x2C] [ebp-0x7C] BYREF
  float v19; // [esp+0x38] [ebp-0x70]
  struct gbVec3D v20; // [esp+0x3C] [ebp-0x6C] BYREF
  float v21; // [esp+0x48] [ebp-0x60]
  float v22; // [esp+0x4C] [ebp-0x5C]
  float v23; // [esp+0x50] [ebp-0x58]
  float v24; // [esp+0x54] [ebp-0x54]
  float v25; // [esp+0x58] [ebp-0x50]
  gbOBBox pMatrix; // [esp+0x5C] [ebp-0x4C] BYREF

  if ( this->buf[69] )
  {
    if ( this->buf[140] == 27 && g_ScriptSystemData.m_nTodo_D8BEEC )
      (((RoleSystem *)g_ScriptSystemData.m_nTodo_D8BEEC))->RoleSystem::RenderRole(pStack, 0);
    if ( this->bkWndX )
    {
      if ( (g_ScriptSystemData.m_bMapRenderFlags & 1) == 0 )
      {
        g_vRotateAxis.x = 0.0;
        g_ScriptSystemData.m_bMapRenderFlags |= 1u;
        g_vRotateAxis.y = 1.0;
        g_vRotateAxis.z = 0.0;
        atexit(nullsub_10);
      }
      if ( (g_ScriptSystemData.m_bMapRenderFlags & 2) == 0 )
      {
        g_ScriptSystemData.m_nTodo_8F8.x = 1.0;
        g_ScriptSystemData.m_bMapRenderFlags |= 2u;
        g_ScriptSystemData.m_nTodo_8FC = 0;
        g_ScriptSystemData.m_nTodo_900 = 0;
        atexit(nullsub_9);
      }
      if ( (g_ScriptSystemData.m_bMapRenderFlags & 4) == 0 )
      {
        g_ScriptSystemData.m_nTodo_8E8.x = 0.0;
        g_ScriptSystemData.m_bMapRenderFlags |= 4u;
        g_ScriptSystemData.m_nTodo_8EC = 0;
        g_ScriptSystemData.m_nTodo_8F0 = 1065353216;
        atexit(nullsub_8);
      }
      v4 = 0;
      switch ( this->buf[140] )
      {
        case 3:
          (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
          (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->buf[108]);
          (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->buf[120],  g_vRotateAxis);
          (((PalScript *)&this->bkWndX))->PalScript::SetIndex(visible);
          (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
          if ( LOBYTE(this->screenrect.right) == 1 && this->m_bcreateok )
          {
            (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
            (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_bvisible);
            (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->buf[120],  g_vRotateAxis);
            (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_bcreateok + 16))(this->m_bcreateok, 0);
            goto LABEL_32;
          }
          goto LABEL_33;
        case 4:
          if ( LOBYTE(this->screenrect.right) )
          {
            (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
            (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_childs.capacity);
            (((PalScript *)&this->bkWndX))->PalScript::SetIndex(visible);
            goto LABEL_32;
          }
          goto LABEL_33;
        case 0xD:
          (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
          (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->buf[108]);
          (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->buf[120],  g_vRotateAxis);
          (((PalScript *)&this->bkWndX))->PalScript::SetIndex(visible);
          (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
          if ( this->m_bcreateok )
          {
            (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
            (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_bvisible);
            (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->buf[120],  g_vRotateAxis);
            (*(void ( **)(int, int))(*(_DWORD *)this->m_bcreateok + 16))(
              this->m_bcreateok,
              visible);
            goto LABEL_32;
          }
          goto LABEL_33;
        case 0x15:
          (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
          (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_childs.capacity);
          v5 = g_pRoleSystem;
          v16 = g_pRoleSystem;
          if ( g_pRoleSystem )
          {
            if ( (g_ScriptSystemData.m_bMapRenderFlags & 8) == 0 )
            {
              g_ScriptSystemData.m_bMapRenderFlags |= 8u;
              g_ScriptSystemData.m_nTodo_8D8.x = 0.0;
              g_ScriptSystemData.m_nTodo_8DC = 0;
              g_ScriptSystemData.m_nTodo_8E0 = 1065353216;
              atexit(nullsub_7);
              v5 = (RoleSystem *)v16;
            }
            p_m_fPosX = (float *)&v5->m_fPosX;
            v18.x = *p_m_fPosX;
            v18.y = p_m_fPosX[1];
            v7 = *(float *)&this->m_childs.capacity - v18.x;
            v8 = *(float *)&this->m_childs.m_nSize - (v18.y + 60.0f);
            v18.z = p_m_fPosX[2];
            v20.x = v8;
            v9 = *(float *)&this->m_childs.m_needscriptdel - v18.z;
            v18.y = v20.x;
            v20.y = v9;
            v18.x = v7;
            v18.z = v20.y;
            (((gbVec3D *)&v18))->gbVec3D::Normalize();
            v22 = 0.0f;
            v21 = 0.0f;
            v20.z = 0.0;
            v23 = 1.0f;
            (((gbQuaternion *)&v20.z))->gbQuaternion::SetTwoVector(&g_ScriptSystemData.m_nTodo_8D8, &v18);
            (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(gbQuaternion *)&v20.z);
          }
          goto LABEL_31;
        case 0x18:
          if ( *(_DWORD *)&this->buf[148] == 1 )
            goto LABEL_33;
          (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
          (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_childs.capacity);
          (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->buf[120],  g_vRotateAxis);
          (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->m_Element[0].m_btn.m_rect.bottom,  g_ScriptSystemData.m_nTodo_8F8);
          (((PalScript *)&this->bkWndX))->PalScript::SetIndex(visible);
LABEL_32:
          (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
LABEL_33:
          v10 = this->buf[140];
          v17 = 0;
          if ( v10 == 15 )
          {
            v4 = (CScreenMode *)g_nRenderFlags;
            v17 = g_nRenderFlags;
          }
          else if ( v10 == 23 && this->buf[70] && *(_DWORD *)&this->buf[148] != 1 )
          {
            v17 = g_nRenderMode;
          }
          SoundList = (CScreenMode *)(((CScreenMode *)v4))->CScreenMode::GetSoundList();
          if ( !(((CScreenMode *)SoundList))->CScreenMode::IsAudioReady() || !v17 )
            return;
          (((Object3D *)this))->Object3D::SetTransform(&pMatrix.trans);
          v20.z = 0.0;
          v21 = 0.0f;
          v22 = 0.0f;
          v23 = 0.0f;
          v24 = 0.0f;
          v25 = 0.0f;
          (((gbOBBox *)&pMatrix))->gbOBBox::GetAABBox(*(gbAABBox *)&v20.z);
          v12 = this->buf[140];
          if ( v12 == 15 )
          {
            p_capacity = (int *)&this->m_childs.capacity;
            v19 = *(float *)p_capacity;
            LODWORD(v20.x) = (unsigned long)p_capacity[1];
            v14 = *((float *)p_capacity + 2);
            v20.x = v24;
            v20.y = v14;
            (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
            (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(v20);
            (((gbMatrixStack *)pStack))->gbMatrixStack::Scale(1.0,   -1.0,   1.0);
            x = v18.x;
            (*(void ( **)(_DWORD, _DWORD))(*(_DWORD *)LODWORD(v18.x) + 16))(LODWORD(v18.x), 0);
            (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
            v20.y = v22;
            (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
            (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(v20);
            (*(void ( **)(_DWORD))(*(_DWORD *)LODWORD(x) + 16))(0);
          }
          else
          {
            if ( v12 != 23 )
              return;
            v19 = v23 + v20.z;
            v20.x = v21 + v24;
            v20.y = v22 + v25;
            v18.x = v19 * 0.5f;
            v18.z = v20.y * 0.5f;
            v18.y = v24 + 2.0f;
            (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
            (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&v18.y);
            (*(void ( **)(_DWORD))(*(_DWORD *)LODWORD(v18.x) + 16))(0);
          }
          (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
          break;
        case 0x1C:
          if ( *(_DWORD *)&this->buf[144] )
          {
            (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
            (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_childs.capacity);
            (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->buf[120],  g_vRotateAxis);
          }
          else
          {
            (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
            (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_childs.capacity);
            (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->buf[120],  g_vRotateAxis);
            (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->m_bvisible,  g_ScriptSystemData.m_nTodo_8E8);
          }
          (((PalScript *)&this->bkWndX))->PalScript::SetIndex(visible);
          goto LABEL_32;
        default:
          (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
          (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this->m_childs.capacity);
          (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->buf[120],  g_vRotateAxis);
          (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(*(float *)&this->m_Element[0].m_btn.m_rect.bottom,  g_ScriptSystemData.m_nTodo_8F8);
LABEL_31:
          (((PalScript *)&this->bkWndX))->PalScript::SetIndex(visible);
          goto LABEL_32;
      }
    }
  }
}

// 0x0043BF90
int UIBigMap::UpdateWindowPos(int deltatime, int haveinput)
{
  int v4; // eax
  int result; // eax
  int v6; // eax
  __int64 v7; // rax
  int v8; // ecx
  int v9; // ebp
  float v10; // st7
  __int64 v11; // rax
  int v12; // ecx
  int v13; // ecx
  int v14; // eax
  float v15; // st7
  int v16; // edx

  v4 = *(_DWORD *)&this->buf[160];
  this->bkWndY = deltatime;
  this->i = haveinput;
  if ( v4 )
  {
    result = v4 - 1;
    if ( result )
      return result;
    v6 = *(_DWORD *)&this->buf[164];
    if ( !v6 )
    {
      v11 = (__int64)((double)(*(_DWORD *)&this->buf[36] - haveinput / 2) + *(float *)&this->buf[132]);
      v12 = *(_DWORD *)&this->buf[32] - *(_DWORD *)&this->buf[140];
      *(_DWORD *)&this->buf[20] = v11;
      v13 = v12 - deltatime;
      *(_DWORD *)&this->buf[16] = v13;
      result = haveinput + v11;
      *(_DWORD *)&this->buf[24] = deltatime + v13;
      *(_DWORD *)&this->buf[28] = result;
      return result;
    }
    result = v6 - 1;
    if ( result )
      return result;
    v7 = (__int64)((double)*(int *)&this->buf[44] - *(float *)&this->buf[132] - (double)(haveinput / 2));
    v8 = *(_DWORD *)&this->buf[40];
    v9 = v7;
    LODWORD(v7) = *(_DWORD *)&this->buf[140];
    *(_DWORD *)&this->buf[20] = v9;
    v10 = (float)(v8 + (int)v7) - *(float *)&this->buf[132];
  }
  else
  {
    v14 = *(_DWORD *)&this->buf[164];
    if ( v14 )
    {
      result = v14 - 1;
      if ( result )
        return result;
      v15 = (float)*(int *)&this->buf[40] - *(float *)&this->buf[132];
      v9 = *(_DWORD *)&this->buf[36] - *(_DWORD *)&this->buf[140] - haveinput;
      *(_DWORD *)&this->buf[20] = v9;
      v10 = v15 - (float)(deltatime / 2);
    }
    else
    {
      v9 = *(_DWORD *)&this->buf[36] - *(_DWORD *)&this->buf[140] - haveinput;
      v16 = *(_DWORD *)&this->buf[32] - deltatime / 2;
      *(_DWORD *)&this->buf[20] = v9;
      v10 = (float)v16 + *(float *)&this->buf[132];
    }
  }
  *(_DWORD *)&this->buf[16] = (__int64)v10;
  result = deltatime + (__int64)v10;
  *(_DWORD *)&this->buf[24] = result;
  *(_DWORD *)&this->buf[28] = haveinput + v9;
  return result;
}

// 0x00441240
int UIBigMap::SetScrollRange(int nMin, int nMax)
{
  int v4; // ecx
  int v5; // edx
  int result; // eax

  *(_DWORD *)&this->buf[64] = nMax;
  v4 = nMax - nMin;
  *(_DWORD *)&this->buf[60] = nMin;
  if ( nMax - nMin <= 0 )
  {
    *(_DWORD *)&this->buf[84] = 0;
    *(_DWORD *)&this->buf[68] = 0;
  }
  else
  {
    v5 = v4 / 10;
    if ( v4 / 10 < 2 )
      v5 = 2;
    *(_DWORD *)&this->buf[84] = v5;
    *(_DWORD *)&this->buf[68] = nMin;
  }
  *(_DWORD *)&this->buf[84] = 1;
  result = CalcWeightedOffset();
  *(_DWORD *)&this->buf[76] = result;
  *(_DWORD *)&this->buf[72] = result;
  return result;
}

// 0x004431E0
int UIBigMap::SetViewParams(int deltatime, int haveinput)
{
  int result; // eax

  result = deltatime;
  *(_DWORD *)&this->buf[80] = deltatime;
  *(_DWORD *)&this->buf[84] = haveinput;
  return result;
}

// 0x00451360
int UIBigMap::LayoutBinkVideo(LPCSTR lpString1, int haveinput)
{
  int v5; // edi
  int v6; // ebp
  LONG a2; // [esp+0x10] [ebp-0x10] BYREF
  LONG top; // [esp+0x14] [ebp-0xC]
  int width; // [esp+0x18] [ebp-0x8]
  int height; // [esp+0x1C] [ebp-0x4]

  if ( lpString1 )
  {
    (*(void ( **)(float *, int))LODWORD(this->ms_BigMap.m_ratiow))(&this->ms_BigMap.m_ratiow, 1);
    (((UIPushButton *)&this->ms_BigMap.m_ratiow))->UIPushButton::CreateFromTemplate((void *)lpString1, 0);
    if ( haveinput )
    {
      width = g_DrvInfo.width;
      a2 = g_DrvInfo.width - 256;
      height = g_DrvInfo.height;
      top = g_DrvInfo.height - 512;
      (((UIWnd *)&this->ms_BigMap.m_ratiow))->UIWnd::sub_445FA0(&a2);
      this->m_Element[0].m_btn.m_bvisible = 1;
      SetVideoRect((BINK *)this);
      (((UIWnd *)&this->buf[168]))->UIWnd::sub_445FA0(&a2);
      v5 = width - a2;
      top = this->m_rect.top + 16;
      height = top + 120;
      a2 += 4;
      width = width + 484 - v5;
      (((UIWnd *)&this->m_Element[0].m_btn.m_benable))->UIWnd::sub_445FA0(&a2);
      v6 = width;
      SetVideoRect((BINK *)this);
      a2 = v6 + 4;
      width = v6 + 4 + v5;
      return (((UIWnd *)&this->buf[168]))->UIWnd::sub_445FA0(&a2);
    }
    else
    {
      height = g_DrvInfo.height;
      a2 = 0;
      width = 256;
      top = g_DrvInfo.height - 512;
      (((UIWnd *)&this->ms_BigMap.m_ratiow))->UIWnd::sub_445FA0(&a2);
      this->m_Element[0].m_btn.m_bvisible = 0;
      SetVideoRect((BINK *)this);
      (((UIWnd *)&this->buf[168]))->UIWnd::sub_445FA0(&a2);
      width = a2 - 4;
      a2 -= 484;
      top = this->m_rect.top + 16;
      height = top + 120;
      return (((UIWnd *)&this->m_Element[0].m_btn.m_benable))->UIWnd::sub_445FA0(&a2);
    }
  }
  else
  {
    (*(void ( **)(float *, _DWORD))LODWORD(this->ms_BigMap.m_ratiow))(&this->ms_BigMap.m_ratiow, 0);
    a2 = this->m_rect.left;
    top = this->m_rect.top;
    width = this->m_rect.right;
    height = g_DrvInfo.height - 2;
    top = g_DrvInfo.height - 138;
    SetVideoRect((BINK *)this);
    (((UIWnd *)&this->buf[168]))->UIWnd::sub_445FA0(&a2);
    width = a2 - 4;
    a2 -= 724;
    top = this->m_rect.top + 16;
    height = top + 120;
    return (((UIWnd *)&this->m_Element[0].m_btn.m_benable))->UIWnd::sub_445FA0(&a2);
  }
}

// 0x004528F0
int UIBigMap::InitUI(int id, int parent)
{
  int m_bcreateok; // edx
  gbTexture *m_pbktex; // edx
  tagRECT pRect; // [esp+0x30] [ebp-0x10] BYREF

  pRect.bottom = g_DrvInfo.height;
  pRect.left = 0;
  pRect.top = 0;
  pRect.right = g_DrvInfo.width;
  LoadUISceneTexture((int)"ui\\scene\\role.tga", 1);
  this->UIWnd::Create(id, &pRect, parent);
  pRect.bottom = (2 * g_DrvInfo.height - 74) / 2;
  pRect.left = 36;
  pRect.right = 218;
  pRect.top = pRect.bottom - 182;
  (((UINote *)&this->m_Element[0].m_btn.m_caption[24]))->UINote::Create(10, (int)&pRect, 0, "ui\\flex\\map");
  (((UIWnd *)&this->m_Element[0].m_btn.m_caption[24]))->UIWnd::sub_445FA0(&pRect);
  (((UIScene *)&this->m_Element[0].m_btn.m_caption[24]))->UIScene::SetState(1);
  *(_DWORD *)&this->m_Element[0].m_btn.m_caption[92] = 1066611507;
  m_bcreateok = this->ms_BigMap.m_bcreateok;
  pRect.bottom = g_DrvInfo.height;
  pRect.top = g_DrvInfo.height - 23;
  pRect.left = 0;
  pRect.right = 68;
  (*(void ( **)(int *, _DWORD, tagRECT *, UIBigMap *))(m_bcreateok + 16))(
    &this->ms_BigMap.m_bcreateok,
    0,
    &pRect,
    this);
  (((UIWnd *)&this->ms_BigMap.m_bcreateok))->UIWnd::sub_445FA0(&pRect);
  (((UIPushButton *)&this->ms_BigMap.m_bcreateok))->UIPushButton::CreateFromTemplate("ui\\scene\\map\\base.tga", 0);
  pRect.left = 4;
  pRect.right = 65;
  pRect.bottom = g_DrvInfo.height - 5;
  pRect.top = g_DrvInfo.height - 66;
  ((void ( *)(UIWnd **, int, tagRECT *, UIBigMap *))this->m_Element[0].m_btn.m_pfather->m_rect.left)(
    &this->m_Element[0].m_btn.m_pfather,
    1,
    &pRect,
    this);
  (((UIWnd *)&this->m_Element[0].m_btn.m_pfather))->UIWnd::sub_445FA0(&pRect);
  (((UIPushButton *)&this->m_Element[0].m_btn.m_pfather))->UIPushButton::CreateFromTemplate("ui\\scene\\map\\compass.tga", 0);
  this->m_Element[0].m_btn.m_alignmode = 0;
  m_pbktex = this->m_pbktex;
  pRect.bottom = g_DrvInfo.height - 5;
  pRect.top = g_DrvInfo.height - 69;
  pRect.left = 4;
  pRect.right = 68;
  ((void ( *)(gbTexture **, int, tagRECT *, UIBigMap *, char *, int, _DWORD))m_pbktex->Height)(
    &this->m_pbktex,
    1,
    &pRect,
    this,
    "ui\\scene\\map\\probe",
    1,
    0);
  return (((UIWnd *)&this->m_pbktex))->UIWnd::sub_445FA0(&pRect);
}

// 0x00489BA0
void UIBigMap::UpdateElement(int element, int visible)
{
  UIBigMap *v3; // esi
  int v4; // eax
  int v5; // edi
  CHAR *buf; // ebp
  int v7; // ecx
  int v8; // edx
  float *v9; // esi
  int v10; // eax
  float *v11; // ecx
  unsigned int v12; // esi
  int v13; // ecx
  int v14; // ebp
  int v15; // edi
  int v16; // eax
  int v18; // [esp+0xC] [ebp-0x18C]
  int RoleNum; // [esp+0x14] [ebp-0x184]
  CHAR String1[125]; // [esp+0x18] [ebp-0x180] BYREF
  __int16 v21; // [esp+0x95] [ebp-0x103]
  char v22; // [esp+0x97] [ebp-0x101]
  char Buffer[253]; // [esp+0x98] [ebp-0x100] BYREF
  __int16 v24; // [esp+0x195] [ebp-0x3]
  char v25; // [esp+0x197] [ebp-0x1]

  v3 = this;
  if ( this->m_Element[0].m_btn.m_enablecolor.Color )
  {
    v4 = *(unsigned __int16 *)(element + 4);
    if ( v4 + 1 > 3 )
      v4 = 2;
    if ( *(_WORD *)(element + 4) < 3u
      && (unsigned int)*(_WORD *)(element + 6) >= *(unsigned __int8 *)(*(_DWORD *)(element + 8) + v4 + 710) )
    {
      memset(String1, 0, sizeof(String1));
      v21 = 0;
      v22 = 0;
      v5 = visible;
      switch ( visible )
      {
        case 0:
          lstrcpyA(String1, g_szRoleNameTable);
          break;
        case 1:
          lstrcpyA(String1, (LPCSTR)&dword_DC743C);
          break;
        case 2:
          lstrcpyA(String1, (LPCSTR)&dword_DC753C);
          break;
        case 3:
          lstrcpyA(String1, (LPCSTR)&dword_DC763C);
          break;
        case 4:
          lstrcpyA(String1, byte_DC773C);
          break;
        default:
          break;
      }
      ++*(_WORD *)(element + 4);
      buf = this->buf;
      this->buf[0] = 0;
      if ( *(_WORD *)(element + 4) <= 3u )
        sprintf(
          this->buf,
          "\\n\\n    %s %s %s%d%s\\n",
          String1,
          (const char *)(*(_DWORD *)(element + 8) + 28),
          (const char *)&dword_DDAB3C,
          *(unsigned __int16 *)(element + 4) + 1,
          byte_DC6A3C);
      if ( *(_WORD *)(element + 4) >= 3u )
      {
        *(_WORD *)(element + 4) = 3;
        v7 = *(_DWORD *)(element + 8);
        if ( *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * visible) >= *(unsigned __int8 *)(v7 + 713)
          && *(_BYTE *)(v7 + 714) <= 3u )
        {
          v8 = 0;
          v18 = *(_DWORD *)(v7 + 716);
          if ( v18 )
          {
            v9 = (float *)(&g_RoleSlotBuf.m_partyActor.m_fDirZ + 352 * visible);
LABEL_19:
            v10 = 0;
            v11 = (float *)v9;
            while ( v18 != *(_DWORD *)v11 )
            {
              ++v10;
              ++v11;
              if ( v10 >= 8 )
              {
                ++v8;
                v9 += 8;
                if ( v8 < 6 )
                  goto LABEL_19;
                goto LABEL_25;
              }
            }
            if ( *((_BYTE *)&g_RoleSlotBuf.m_fPathSpeed + 1408 * visible + 8 * v8 + v10) )
              goto LABEL_26;
LABEL_25:
            RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(v18);
            RoleSystem::CheckVisible();
            memset(Buffer, 0, sizeof(Buffer));
            v24 = 0;
            v25 = 0;
            sprintf(Buffer, "    %s%s %s\\n", String1, (const char *)&dword_DDAC3C, (const char *)(RoleNum + 28));
            lstrcatA((char *)buf, Buffer);
          }
        }
LABEL_26:
        v5 = visible;
        v3 = this;
      }
      SetEnable((UICaption *)&v3[20].m_Element[1].m_btn.m_EnableMode);
      (((UIRoleSelect *)&v3[20].m_Element[0].m_btn.m_caption[104]))->UIRoleSelect::SetByte(1);
      v12 = 0;
      v13 = 16 * v5;
      v14 = 0;
      v15 = *(&g_SceneMgrPrefix.m_nSize + 4 * v5);
      while ( v15 && v12 < (int)&(*(char **)((char *)&g_SceneMgrPrefix.m_pData + v13))[-v15] / 12 )
      {
        if ( *(_DWORD *)(*(int *)((char *)&g_SceneMgrPrefix.m_nSize + v13) + v14) == *(_DWORD *)element )
        {
          v16 = 12 * v12;
          *(_WORD *)(*(int *)((char *)&g_SceneMgrPrefix.m_nSize + v13) + v16 + 6) = *(_WORD *)(element + 6);
          *(_WORD *)(*(int *)((char *)&g_SceneMgrPrefix.m_nSize + v13) + v16 + 4) = *(_WORD *)(element + 4);
          break;
        }
        ++v12;
        v14 += 12;
      }
      NPC::InitAll();
      *(&this->m_Element[0].m_show + 2) = 0;
      *(&this->m_Element[0].m_show + 1) = 0;
      (((MainPropUI *)this))->MainPropUI::SetPage(1u) /* [ROWTABLE] */;
      this->m_Element[0].m_show = 0;
      (((CameraCtrl *)this))->CameraCtrl::BuildRenderLists();
      MagicUI_UpdateViewListItems(visible);
    }
  }
}

// 0x00490E90
UIBigMap::UIBigMap()
{
  (((UIFrameContainer *)this))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  (((UIFrameContainer *)&this->ms_BigMap.m_pbk2))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Element[0].m_btn.m_texarray.m_ptex[5]))->UIFrameContainer::ResetContainerState();
  ctor_17((UIButton *)&this->m_Element[0].m_btn.m_caption[76]);
  (((UIFrameContainer *)&this->m_Element[1].m_btn.m_texarray.m_ptex[6]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Element[1].m_btn.m_caption[80]))->UIFrameContainer::ResetContainerState();
  ctor_17((UIButton *)&this->m_Element[2].m_btn.m_pfather);
  (((UIFrameContainer *)&this->m_Element[2].m_btn.m_caption[84]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Element[3].m_btn.m_childs))->UIFrameContainer::ResetContainerState();
  ctor_17((UIButton *)&this->m_Element[3].m_btn.m_alignmode);
  (((UIFrameContainer *)&this->m_Element[4].m_btn.m_childs.capacity))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)this->m_Element[4].m_btn.m_caption))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Element[4].m_btn.m_optData))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Element[5].m_btn.m_texarray.m_ptex[2]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Element[5].m_btn.m_caption[64]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Element[6].m_btn.m_rect))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_Element[6].m_btn.m_texarrayInfo[1]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)((char *)&this->m_Answer.m_btRc + 100)))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
}

// 0x004910B0
UIBigMap::~UIBigMap()
{
  (((UICaption *)((char *)&this->m_Answer + 2604)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_Answer + 2260)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_Answer + 1916)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_Answer + 1572)))->UICaption::Destroy2();
  (((UICaption *)(&this->m_Answer.pCallbackVtable2 + 63)))->UICaption::Destroy2();
  (((UICaption *)((char *)&this->m_Answer.m_btRc + 252)))->UICaption::Destroy2();
  (((UIFrameContainer *)((char *)&this->m_Answer.m_btRc + 100)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Element[6].m_btn.m_texarrayInfo[1]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Element[6].m_btn.m_rect))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Element[5].m_btn.m_caption[64]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Element[5].m_btn.m_texarray.m_ptex[2]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Element[4].m_btn.m_optData))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)this->m_Element[4].m_btn.m_caption))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Element[4].m_btn.m_childs.capacity))->UIFrameContainer::~UIFrameContainer();
  (((UIButton *)&this->m_Element[3].m_btn.m_alignmode))->UIButton::~UIButton();
  (((UIFrameContainer *)&this->m_Element[3].m_btn.m_childs))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Element[2].m_btn.m_caption[84]))->UIFrameContainer::~UIFrameContainer();
  (((UIButton *)&this->m_Element[2].m_btn.m_pfather))->UIButton::~UIButton();
  (((UIFrameContainer *)&this->m_Element[1].m_btn.m_caption[80]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_Element[1].m_btn.m_texarray.m_ptex[6]))->UIFrameContainer::~UIFrameContainer();
  (((UIButton *)&this->m_Element[0].m_btn.m_caption[76]))->UIButton::~UIButton();
  (((UIFrameContainer *)&this->m_Element[0].m_btn.m_texarray.m_ptex[5]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->ms_BigMap.m_pbk2))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)&this->buf[48]))->UICaption::Destroy2();
  (((UIFrameContainer *)this))->UIFrameContainer::~UIFrameContainer();
}

// 0x00491C30
int UIBigMap::GetChildCount(int nVal, int nVal2)
{
  int v4; // ecx
  char *v5; // esi
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int result; // eax
  int v12; // [esp+0x18] [ebp-0x10] BYREF
  int v13; // [esp+0x1C] [ebp-0xC]
  int v14; // [esp+0x20] [ebp-0x8]
  int v15; // [esp+0x24] [ebp-0x4]

  if ( nVal <= 5 )
  {
    v4 = *(_DWORD *)nVal2;
    v13 = *(_DWORD *)(nVal2 + 4);
    v15 = v13 + 12;
    v12 = v4;
    v14 = v4 + 85;
    v5 = (char *)this + 9980 * nVal;
    (*(void ( **)(char *, _DWORD, int *, UIBigMap *))(*((_DWORD *)v5 + 38827) + 16))(
      v5 + 155308,
      (_DWORD)(*(&g_pfnCallback + nVal)),
      &v12,
      this);
    (((UIScene *)(v5 + 155308)))->UIScene::GetChildCount();
    (((UIScene *)(v5 + 155308)))->UIScene::GetChildAt();
    *((_DWORD *)v5 + 38845) = 1;
    v5[155478] = -30;
    v5[155477] = -51;
    v5[155476] = 58;
    v5[155479] = -1;
    sub_43FD90((float *)v5 + 38827, 4);
    (((UIProgressBar *)(v5 + 155308)))->UIProgressBar::GetWidth(-4);
    sub_43FDB0((float *)v5 + 38827, 1);
    (((UIProgressBar *)(v5 + 155308)))->UIProgressBar::GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UIBigMap *))(*((_DWORD *)v5 + 39101) + 16))(
      v5 + 156404,
      (_DWORD)(*(&g_pfnCallback + nVal)),
      &v12,
      this);
    (((UIScene *)(v5 + 156404)))->UIScene::GetChildCount();
    (((UIScene *)(v5 + 156404)))->UIScene::GetChildAt();
    *((_DWORD *)v5 + 39119) = 1;
    v5[156574] = -30;
    v5[156573] = -51;
    v5[156572] = 58;
    v5[156575] = -1;
    sub_43FD90((float *)v5 + 39101, 4);
    ((UIProgressBar *)((UIProgressBar *)v5 + 641))->UIProgressBar::GetWidth(-4);
    sub_43FDB0((float *)v5 + 39101, 1);
    ((UIProgressBar *)((UIProgressBar *)v5 + 641))->UIProgressBar::GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UIBigMap *))(*((_DWORD *)v5 + 38964) + 16))(
      v5 + 155856,
      (_DWORD)(*(&g_pfnCallback + nVal)),
      &v12,
      this);
    (((UIScene *)(v5 + 155856)))->UIScene::GetChildCount();
    (((UIScene *)(v5 + 155856)))->UIScene::GetChildAt();
    *((_DWORD *)v5 + 38982) = 1;
    v5[156026] = -30;
    v5[156025] = -51;
    v5[156024] = 58;
    v5[156027] = -1;
    sub_43FD90((float *)v5 + 38964, 4);
    (((UIProgressBar *)(v5 + 155856)))->UIProgressBar::GetWidth(-4);
    sub_43FDB0((float *)v5 + 38964, 1);
    (((UIProgressBar *)(v5 + 155856)))->UIProgressBar::GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(*((_DWORD *)v5 + 38888) + 16))(
      v5 + 155552,
      (_DWORD)(*(&g_pfnCallback + nVal)),
      nVal2,
      this);
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(*((_DWORD *)v5 + 39162) + 16))(
      v5 + 156648,
      (_DWORD)(*(&g_pfnCallback + nVal)),
      nVal2,
      this);
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(*((_DWORD *)v5 + 39025) + 16))(
      v5 + 156100,
      (_DWORD)(*(&g_pfnCallback + nVal)),
      nVal2,
      this);
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(*((_DWORD *)v5 + 38627) + 16))(
      v5 + 154508,
      (_DWORD)(*(&g_pfnCallback + nVal)),
      nVal2,
      this);
    LOBYTE(v6) = g_bDebugMode;
    (((UIPushButton *)(v5 + 154508)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\HeadBk.tga", v6);
    LOBYTE(v7) = g_bDebugMode;
    (*(void ( **)(char *, _DWORD, int, UIBigMap *, char *, int, int))(*((_DWORD *)v5 + 38665) + 28))(
      v5 + 154660,
      *(&dword_56D5F0 + nVal),
      nVal2,
      this,
      &"UI\\GameMainUI\\Communal\\RoleHead0"[256 * nVal],
      1,
      v7);
    v8 = *((_DWORD *)v5 + 38751);
    v5 += 155004;
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(v8 + 16))(v5, (_DWORD)(*(&g_pfnCallback + nVal)), nVal2, this);
    LOBYTE(v9) = g_bDebugMode;
    (((UIPushButton *)v5))->UIPushButton::CreateFromTemplate((void *)(0x56D5B0)[nVal], v9);
    return (((UIScene *)v5))->UIScene::SetShow(0);
  }
  return result;
}

// 0x004929E0
int UIBigMap::ProcessChildItem(int arg0, int *p_DWORD)
{
  int result; // eax
  char *v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // [esp+0x0] [ebp-0x40] BYREF
  int v13; // [esp+0x4] [ebp-0x3C]
  int v14; // [esp+0x8] [ebp-0x38]
  int v15; // [esp+0xC] [ebp-0x34]
  int v16; // [esp+0x10] [ebp-0x30] BYREF
  int v17; // [esp+0x14] [ebp-0x2C]
  int v18; // [esp+0x18] [ebp-0x28]
  int v19; // [esp+0x1C] [ebp-0x24]
  _DWORD a2[4]; // [esp+0x20] [ebp-0x20] BYREF
  _DWORD v21[4]; // [esp+0x30] [ebp-0x10] BYREF

  result = arg0;
  if ( arg0 <= 5 )
  {
    v4 = (char *)this + 9980 * arg0;
    (((UIWnd *)(v4 + 154508)))->UIWnd::sub_445FA0(p_DWORD);
    v5 = (unsigned long)(p_DWORD[1] + 10);
    a2[0] = (unsigned long)(*p_DWORD + 25);
    a2[2] = a2[0] + 65;
    a2[1] = v5;
    a2[3] = v5 + 86;
    (((UIWnd *)(v4 + 154660)))->UIWnd::sub_445FA0(a2);
    v6 = (unsigned long)(p_DWORD[1] + 36);
    v21[0] = (unsigned long)(p_DWORD[2] - 27);
    v21[1] = v6;
    v21[2] = v21[0] + 32;
    v21[3] = v6 + 128;
    (((UIWnd *)(v4 + 155004)))->UIWnd::sub_445FA0(v21);
    v7 = (unsigned long)(*p_DWORD - 72);
    v13 = (unsigned long)(p_DWORD[1] + 21);
    v12 = v7;
    v15 = v13 + 12;
    v14 = v7 + 85;
    sub_43FEC0(&v12);
    v8 = (unsigned long)(*p_DWORD - 80);
    v13 = v15 + 16;
    v12 = v8;
    v15 += 28;
    v14 = v8 + 85;
    sub_43FEC0(&v12);
    v9 = (unsigned long)(*p_DWORD - 70);
    v13 = v15 + 16;
    v12 = v9;
    v14 = v9 + 85;
    v15 += 28;
    sub_43FEC0(&v12);
    v10 = (unsigned long)p_DWORD[1];
    v16 = v12;
    v17 = v10;
    v18 = v12 + 100;
    v19 = v10 + 32;
    (((UIWnd *)(v4 + 155552)))->UIWnd::sub_445FA0(&v16);
    v11 = (unsigned long)(p_DWORD[1] + 28);
    v16 = v12;
    v17 = v11;
    v19 = v11 + 32;
    v18 = v12 + 100;
    (((UIWnd *)(v4 + 156648)))->UIWnd::sub_445FA0(&v16);
    v17 = (unsigned long)(p_DWORD[1] + 56);
    v16 = v12;
    v18 = v12 + 100;
    v19 = v17 + 32;
    return (((UIWnd *)(v4 + 156100)))->UIWnd::sub_445FA0(&v16);
  }
  return result;
}

// 0x00492E10
int UIBigMap::SetEntryVisible(int nIndex, unsigned __int8 bParam)
{
  int result; // eax
  char *v4; // esi

  result = nIndex;
  if ( nIndex <= 5 )
  {
    v4 = (char *)this + 9980 * nIndex;
    (**((void ( ***)(int, _DWORD))v4 + 38627))((int)((int)(v4 + 154508)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 38665))((int)((int)(v4 + 154660)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 38751))((int)((int)(v4 + 155004)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 38827))((int)((int)(v4 + 155308)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 38888))((int)((int)(v4 + 155552)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39101))((int)((int)(v4 + 156404)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39162))((int)((int)(v4 + 156648)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 38964))((int)((int)(v4 + 155856)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39025))((int)((int)(v4 + 156100)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39200))((int)((int)(v4 + 156800)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39238))((int)((int)(v4 + 156952)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39276))((int)((int)(v4 + 157104)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39314))((int)((int)(v4 + 157256)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39352))((int)((int)(v4 + 157408)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39390))((int)((int)(v4 + 157560)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39428))((int)((int)(v4 + 157712)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39808))((int)((int)(v4 + 159232)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40188))((int)((int)(v4 + 160752)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39466))((int)((int)(v4 + 157864)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39846))((int)((int)(v4 + 159384)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40226))((int)((int)(v4 + 160904)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39504))((int)((int)(v4 + 158016)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39884))((int)((int)(v4 + 159536)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40264))((int)((int)(v4 + 161056)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39542))((int)((int)(v4 + 158168)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39922))((int)((int)(v4 + 159688)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40302))((int)((int)(v4 + 161208)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39580))((int)((int)(v4 + 158320)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39960))((int)((int)(v4 + 159840)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40340))((int)((int)(v4 + 161360)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39618))((int)((int)(v4 + 158472)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39998))((int)((int)(v4 + 159992)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40378))((int)((int)(v4 + 161512)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39656))((int)((int)(v4 + 158624)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40036))((int)((int)(v4 + 160144)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40416))((int)((int)(v4 + 161664)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39694))((int)((int)(v4 + 158776)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40074))((int)((int)(v4 + 160296)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40454))((int)((int)(v4 + 161816)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39732))((int)((int)(v4 + 158928)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40112))((int)((int)(v4 + 160448)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40492))((int)((int)(v4 + 161968)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 39770))((int)((int)(v4 + 159080)), (_DWORD)(bParam));
    (**((void ( ***)(int, _DWORD))v4 + 40150))((int)((int)(v4 + 160600)), (_DWORD)(bParam));
    return (**((int ( ***)(int, _DWORD))v4 + 40530))((int)((int)(v4 + 162120)), (_DWORD)(bParam));
  }
  return result;
}

// 0x00496FA0
void UIBigMap::Render()
{
  int i; // edi
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  (((CCBControlWindow *)this))->CCBControlWindow::Render(v3) /* [ROWTABLE] */;
  if ( this[15].m_Element[0].m_btn.m_caption[*(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] + 52] )
  {
    for ( i = 0; i < 16; ++i )
    {
      if ( IsVisible((RenderTarget *)(&this->m_Element[11].m_btn.m_rect.top
                                    + 2336 * *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60]
                                    + 146 * i)) )
        ((UIParticle *)((UIParticle *)&this->m_Element[11].m_btn.m_rect.top
        + 16 * *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60]
        + i))->UIParticle::Apply(11);
      if ( IsVisible((RenderTarget *)((char *)&this[7].m_Answer.m_btRc
                                    + 9344 * *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60]
                                    + 584 * i
                                    + 216)) )
        (((UIParticle *)((char *)&this[7].m_Answer.m_btRc
                       + 9344 * *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60]
                       + 584 * i
                       + 216)))->UIParticle::Apply(10);
    }
  }
}

// 0x004971E0
BOOL UIBigMap::ProcessInput(int nVal, int nVal2)
{
  __int64 v4; // rax
  int v5; // ebx
  int i; // eax
  char v7; // cl
  float *v8; // eax
  int v9; // eax
  int v11; // [esp-0x4] [ebp-0x28]
  int v12; // [esp+0x20] [ebp-0x4]

  v4 = (__int64)g_fGameTimer;
  v5 = (int)v4 / 3600;
  v12 = (int)v4 / 60 % 60;
  v11 = (int)v4 % 60;
  if ( (int)v4 / 3600 < 100 )
    sprintf(this->buf, "%02d:%02d:%02d", v5, v12, v11);
  else
    sprintf(this->buf, "%03d:%02d:%02d", v5, v12, v11);
  SetEnable((UICaption *)&this->m_Element[10].m_btn.m_texarray.m_ptex[3]);
  sprintf(this->buf, (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)&this->m_Element[10].m_btn.m_caption[68]);
  if ( BYTE2(this->ms_BigMap.m_fontcolor.Color) )
  {
    (((MainPropUI *)this))->MainPropUI::HandleKeyInput() /* [ROWTABLE] */;
    this->i = 0;
    do
    {
      i = this->i;
      if ( *((_BYTE *)((UIWnd *)&this->ms_BigMap) + i + 1) )
      {
        v7 = *((_BYTE *)&this[15].m_Element[3].m_btn.m_childs.capacity + 9980 * i);
        v8 = (float *)((char *)this + 9980 * i);
        if ( !v7 )
        {
          sprintf(
            this->buf,
            "%d/%d",
            (int)v8[38866],
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->i));
          SetEnable((UICaption *)&this[15].m_Element[3].m_btn.m_texarray.m_ptex[2495 * this->i + 7]);
        }
        if ( !*((_BYTE *)&this[15].m_Element[5].m_btn.m_optData.height + 9980 * this->i) )
        {
          sprintf(
            this->buf,
            "%d/%d",
            (int)*((float *)&this[15].m_Element[5].m_btn.m_optData.width + 2495 * this->i),
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->i + 1));
          SetEnable((UICaption *)(&this[15].m_Element[6].m_btn.m_childs.m_nSize + 2495 * this->i));
        }
        if ( !this[15].m_Element[4].m_btn.m_caption[9980 * this->i + 4] )
        {
          sprintf(
            this->buf,
            "%d/%d",
            (int)*(float *)&this[15].m_Element[4].m_btn.m_caption[9980 * this->i],
            *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * this->i + 2));
          SetEnable((UICaption *)&this[15].m_Element[4].m_btn.m_caption[9980 * this->i + 88]);
        }
      }
      v9 = this->i + 1;
      this->i = v9;
    }
    while ( v9 < 5 );
  }
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x00497450
int UIBigMap::UpdateNPCAnimations(int nVal, int nVal2)
{
  char *v3; // esi
  int result; // eax

  v3 = (char *)this + 9980 * nVal;
  (((NPC *)(v3 + 154660)))->NPC::UpdateAnim(nVal2);
  (((NPC *)(v3 + 157560)))->NPC::UpdateAnim(nVal2);
  return result;
}

// 0x004974A0
int UIBigMap::OnMessage(int nVal, char *pszBuf, int nItemID)
{
  int i; // edi
  char *v6; // esi
  UICursor *v7; // ecx
  int result; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  CScreenMode *v17; // eax
  CScreenMode *v18; // eax
  CScreenMode *v19; // eax
  CScreenMode *Instance; // eax
  unsigned int m_id; // eax
  unsigned int v22; // eax
  unsigned int v23; // eax
  char *v24; // eax
  int v25; // eax
  int *v26; // edi
  char *v27; // ecx
  int v28; // edi
  const char *v29; // ebp
  const char *v30; // edx
  int v31; // eax
  int *v32; // edi
  char *v33; // ecx
  int v34; // edi
  int v35; // eax
  int *v36; // edi
  char *v37; // ecx
  int v38; // edi
  int v39; // eax
  int *v40; // edi
  char *v41; // ecx
  int v42; // edi
  int v43; // eax
  int *v44; // edi
  char *v45; // ecx
  int v46; // edi
  int v47; // eax
  int *v48; // edi
  char *v49; // ecx
  int v50; // edi
  char *buf; // edi
  int *v52; // eax
  int v53; // edi
  const char *v54; // ebp
  CScreenMode *v55; // eax
  const void *v56; // [esp-0x8] [ebp-0x130]
  const void *v57; // [esp-0x8] [ebp-0x130]
  const void *v58; // [esp-0x8] [ebp-0x130]
  const void *v59; // [esp-0x8] [ebp-0x130]
  const void *v60; // [esp-0x8] [ebp-0x130]
  const void *v61; // [esp-0x8] [ebp-0x130]
  const void *v62; // [esp-0x8] [ebp-0x130]
  const void *v63; // [esp-0x8] [ebp-0x130]
  char *v64; // [esp-0x8] [ebp-0x130]
  int v65; // [esp+0x0] [ebp-0x128]
  int v66; // [esp+0x18] [ebp-0x110]
  char Buffer; // [esp+0x1C] [ebp-0x10C] BYREF
  _BYTE v68[252]; // [esp+0x1D] [ebp-0x10B] BYREF
  __int16 v69; // [esp+0x119] [ebp-0xF]
  char v70; // [esp+0x11B] [ebp-0xD]
  _BYTE pOut[12]; // [esp+0x11C] [ebp-0xC] BYREF

  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        for ( i = 0; i < 8; ++i )
          LoadBigMapRenderTarget(i);
        MagicUI_ProcessInput(v65);
        (((MainPropUI *)this))->MainPropUI::ShowPage() /* [ROWTABLE] */;
        g_nSceneState = 1;
        BYTE2(this->ms_BigMap.m_fontcolor.Color) = 1;
        v6 = (char *)&this[15].m_Element[0].m_btn.m_caption[52];
        *(_DWORD *)v6 = 0;
        *((_DWORD *)v6 + 1) = 0;
        (((UICursor *)v7))->UICursor::_todo_541CC0();
        result = 1;
      }
      else
      {
        BYTE2(this->ms_BigMap.m_fontcolor.Color) = 0;
        (((CScreenMode *)this))->CScreenMode::ResetProgressList() /* [ROWTABLE] */;
        result = 1;
      }
      break;
    case 1001:
      this->i = 0;
      do
      {
        v9 = this->i;
        if ( *((_BYTE *)((UIWnd *)&this->ms_BigMap) + v9 + 1) && pszBuf == (char *)*(&dword_56D5F0 + v9) )
        {
          *((_DWORD *)&this[20].m_Answer + 801) = this->i;
          this->ms_BigMap.m_wndcolor.Color = -1;
          (((UIListBox *)&this[21].m_Element[4].m_btn.m_texarray.m_ptex[2]))->UIListBox::GetItem();
          SceneMgr_FormatStatusCaption(*((_DWORD *)&this[20].m_Answer + 801));
          (((StateUI *)this))->StateUI::UpdateRoleTooltip(*((_DWORD *)&this[20].m_Answer + 801)) /* [ROWTABLE] */;
          MainPropUI_ShowSubPanels(*((_DWORD *)&this[20].m_Answer + 801));
          (((MainEquipUI *)this))->MainEquipUI::UpdateTooltip(*((_DWORD *)&this[20].m_Answer + 801)) /* [ROWTABLE] */;
          (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), this->ms_BigMap.m_id) /* [ROWTABLE] */;
LABEL_38:
          v24 = (char *)off_5C936C;
          goto LABEL_132;
        }
        v10 = v9 + 1;
        this->i = v10;
      }
      while ( v10 < 5 );
      this->i = 0;
      do
      {
        v11 = this->i;
        if ( g_pPropUINameStrs[v11] == pszBuf )
        {
          (((StateUI *)this))->StateUI::UpdateRoleTooltip(*((_DWORD *)&this[20].m_Answer + 801)) /* [ROWTABLE] */;
          MainPropUI_ShowSubPanels(*((_DWORD *)&this[20].m_Answer + 801));
          (((MainEquipUI *)this))->MainEquipUI::UpdateTooltip(*((_DWORD *)&this[20].m_Answer + 801)) /* [ROWTABLE] */;
          this->ms_BigMap.m_wndcolor.Color = -1;
          (((UIListBox *)&this[21].m_Element[4].m_btn.m_texarray.m_ptex[2]))->UIListBox::GetItem();
          SceneMgr_FormatStatusCaption(*((_DWORD *)&this[20].m_Answer + 801));
          (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), this->i) /* [ROWTABLE] */;
LABEL_40:
          v64 = (char *)off_5C936C;
          goto LABEL_133;
        }
        v12 = v11 + 1;
        this->i = v12;
      }
      while ( v12 < 5 );
      if ( pszBuf > (char *)&byte_A00110 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00319u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            (((UIListBox *)&this[21].m_Element[4].m_btn.m_texarray.m_ptex[2]))->UIListBox::GetItem();
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), 0) /* [ROWTABLE] */;
            goto LABEL_36;
          case 0xA00320u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            (((UIListBox *)&this[21].m_Element[4].m_btn.m_texarray.m_ptex[2]))->UIListBox::GetItem();
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), 2) /* [ROWTABLE] */;
            goto LABEL_38;
          case 0xA00321u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            (((UIListBox *)&this[21].m_Element[4].m_btn.m_texarray.m_ptex[2]))->UIListBox::GetItem();
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), 1) /* [ROWTABLE] */;
            goto LABEL_40;
          case 0xA00322u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            (((UIListBox *)&this[21].m_Element[4].m_btn.m_texarray.m_ptex[2]))->UIListBox::GetItem();
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), 3) /* [ROWTABLE] */;
LABEL_36:
            v64 = (char *)off_5C936C;
            goto LABEL_133;
          case 0xA00323u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            (((UIListBox *)&this[21].m_Element[4].m_btn.m_texarray.m_ptex[2]))->UIListBox::GetItem();
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), 4) /* [ROWTABLE] */;
            goto LABEL_38;
          case 0xA00324u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            (((UIListBox *)&this[21].m_Element[4].m_btn.m_texarray.m_ptex[2]))->UIListBox::GetItem();
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), 5) /* [ROWTABLE] */;
            goto LABEL_40;
          case 0xA00333u:
            m_id = this->ms_BigMap.m_id;
            this[21].m_Element[10].m_btn.m_id = -1;
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), m_id) /* [ROWTABLE] */;
            goto LABEL_40;
          case 0xA00334u:
            v22 = this->ms_BigMap.m_id;
            this[21].m_Element[10].m_btn.m_id = 0;
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), v22) /* [ROWTABLE] */;
            goto LABEL_40;
          case 0xA00335u:
            v23 = this->ms_BigMap.m_id;
            this[21].m_Element[10].m_btn.m_id = 3;
            (((EquipUI *)this))->EquipUI::HandleInput(*((_DWORD *)&this[20].m_Answer + 801), v23) /* [ROWTABLE] */;
            goto LABEL_40;
          default:
            goto LABEL_134;
        }
      }
      if ( pszBuf == (char *)&byte_A00110 )
      {
        v63 = (const void *)off_5C936C;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v63, 1);
        (((MainEquipUI *)this->ms_BigMap.m_rect.top))->MainEquipUI::HandleMessage(9);
        result = 1;
      }
      else
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00102u:
            v56 = (const void *)off_5C936C;
            v13 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v13))->CScreenMode::AudioSetPosition(v56, 1);
            (((MainEquipUI *)this->ms_BigMap.m_rect.top))->MainEquipUI::HandleMessage(0);
            result = 1;
            break;
          case 0xA00103u:
            v57 = (const void *)off_5C936C;
            v14 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v14))->CScreenMode::AudioSetPosition(v57, 1);
            (((MainEquipUI *)this->ms_BigMap.m_rect.top))->MainEquipUI::HandleMessage(3);
            result = 1;
            break;
          case 0xA00105u:
            v58 = (const void *)off_5C936C;
            v15 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v15))->CScreenMode::AudioSetPosition(v58, 1);
            (((MainEquipUI *)this->ms_BigMap.m_rect.top))->MainEquipUI::HandleMessage(1);
            result = 1;
            break;
          case 0xA00106u:
            v59 = (const void *)off_5C936C;
            v16 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v16))->CScreenMode::AudioSetPosition(v59, 1);
            (((MainEquipUI *)this->ms_BigMap.m_rect.top))->MainEquipUI::HandleMessage(5);
            result = 1;
            break;
          case 0xA00107u:
            v60 = (const void *)off_5C936C;
            v17 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v17))->CScreenMode::AudioSetPosition(v60, 1);
            (((MainEquipUI *)this->ms_BigMap.m_rect.top))->MainEquipUI::HandleMessage(6);
            result = 1;
            break;
          case 0xA00108u:
            v61 = (const void *)off_5C936C;
            v18 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v18))->CScreenMode::AudioSetPosition(v61, 1);
            (((MainEquipUI *)this->ms_BigMap.m_rect.top))->MainEquipUI::HandleMessage(4);
            result = 1;
            break;
          case 0xA00109u:
            v62 = (const void *)off_5C936C;
            v19 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v19))->CScreenMode::AudioSetPosition(v62, 1);
            (((MainEquipUI *)this->ms_BigMap.m_rect.top))->MainEquipUI::HandleMessage(7);
            result = 1;
            break;
          default:
            goto LABEL_134;
        }
      }
      break;
    case 1002:
      switch ( (unsigned int)pszBuf )
      {
        case 0xA00102u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 0;
          if ( this[15].m_Element[0].m_btn.m_caption[52] )
            goto LABEL_97;
          LoadBigMapRenderTarget(0);
          result = 1;
          break;
        case 0xA00103u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 1;
          if ( this[15].m_Element[0].m_btn.m_caption[53] )
            goto LABEL_97;
          LoadBigMapRenderTarget(1);
          result = 1;
          break;
        case 0xA00104u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 2;
          if ( this[15].m_Element[0].m_btn.m_caption[54] )
            goto LABEL_97;
          LoadBigMapRenderTarget(2);
          result = 1;
          break;
        case 0xA00105u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 3;
          if ( this[15].m_Element[0].m_btn.m_caption[55] )
            goto LABEL_97;
          LoadBigMapRenderTarget(3);
          result = 1;
          break;
        case 0xA00106u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 5;
          if ( this[15].m_Element[0].m_btn.m_caption[57] )
            goto LABEL_97;
          LoadBigMapRenderTarget(5);
          result = 1;
          break;
        case 0xA00107u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 6;
          if ( this[15].m_Element[0].m_btn.m_caption[58] )
            goto LABEL_97;
          LoadBigMapRenderTarget(6);
          result = 1;
          break;
        case 0xA00108u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 4;
          if ( this[15].m_Element[0].m_btn.m_caption[56] )
            goto LABEL_97;
          LoadBigMapRenderTarget(4);
          result = 1;
          break;
        case 0xA00109u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 7;
          if ( !this[15].m_Element[0].m_btn.m_caption[59] )
            LoadBigMapRenderTarget(7);
          goto LABEL_97;
        default:
LABEL_97:
          result = 1;
          break;
      }
      break;
    case 1003:
      switch ( (unsigned int)pszBuf )
      {
        case 0xA00102u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 0;
          this[15].m_Element[0].m_btn.m_caption[52] = 0;
          result = 1;
          break;
        case 0xA00103u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 1;
          this[15].m_Element[0].m_btn.m_caption[53] = 0;
          result = 1;
          break;
        case 0xA00104u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 2;
          this[15].m_Element[0].m_btn.m_caption[54] = 0;
          result = 1;
          break;
        case 0xA00105u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 3;
          this[15].m_Element[0].m_btn.m_caption[55] = 0;
          result = 1;
          break;
        case 0xA00106u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 5;
          this[15].m_Element[0].m_btn.m_caption[57] = 0;
          result = 1;
          break;
        case 0xA00107u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 6;
          this[15].m_Element[0].m_btn.m_caption[58] = 0;
          result = 1;
          break;
        case 0xA00108u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 4;
          this[15].m_Element[0].m_btn.m_caption[56] = 0;
          result = 1;
          break;
        case 0xA00109u:
          *(_DWORD *)&this[15].m_Element[0].m_btn.m_caption[60] = 7;
          this[15].m_Element[0].m_btn.m_caption[59] = 0;
          goto LABEL_107;
        default:
LABEL_107:
          result = 1;
          break;
      }
      break;
    case 1007:
      this->ms_BigMap.m_wndcolor.Color = nItemID;
      if ( nItemID >= 0 )
      {
        if ( (unsigned __int8)sub_4947E0(nItemID, *((_DWORD *)&this[20].m_Answer + 801), 0) )
          UIScene_LoadRoleSkillData(*((_DWORD *)&this[20].m_Answer + 801));
        else
          SceneMgr_FormatStatusCaption(*((_DWORD *)&this[20].m_Answer + 801));
        v52 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, this->ms_BigMap.m_wndcolor.Color);
        v53 = (unsigned long)v52[2];
        v66 = v53;
        (((EquipUI *)this))->EquipUI::UpdateSlot(*v52, v52[1], v53) /* [ROWTABLE] */;
        if ( *(_BYTE *)(v53 + 613) == 5 )
        {
          (((CCBFiveNimbusWindow *)&this[21].m_Element[10].m_btn.m_rect))->CCBFiveNimbusWindow::SetFloatParam(228.0);
          (((Camera *)&this[21].m_Element[10].m_btn.m_rect))->Camera::UpdateCameraLookAt(128, 270, 600);
        }
        else if ( *(_BYTE *)(v53 + 612) == 11 )
        {
          (((CCBFiveNimbusWindow *)&this[21].m_Element[10].m_btn.m_rect))->CCBFiveNimbusWindow::SetFloatParam(228.0);
          (((Camera *)&this[21].m_Element[10].m_btn.m_rect))->Camera::UpdateCameraLookAt(128, 262, 600);
        }
        else if ( *(_DWORD *)v53 == 8114 || *(_DWORD *)v53 == 8132 )
        {
          (((CCBFiveNimbusWindow *)&this[21].m_Element[10].m_btn.m_rect))->CCBFiveNimbusWindow::SetFloatParam(180.0);
          (((Camera *)&this[21].m_Element[10].m_btn.m_rect))->Camera::UpdateCameraLookAt(128, 242, 600);
        }
        else
        {
          (((CCBFiveNimbusWindow *)&this[21].m_Element[10].m_btn.m_rect))->CCBFiveNimbusWindow::SetFloatParam(180.0);
          (((Camera *)&this[21].m_Element[10].m_btn.m_rect))->Camera::UpdateCameraLookAt(128, 258, 600);
        }
        v54 = (const char *)(v53 + 36);
        if ( !strcmp((const char *)(v53 + 36), unk_C10D38) )
          sprintf(this->buf, "%s", "NONE");
        else
          sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v66 + 36), (const char *)(v66 + 36));
        (((PalScript *)&this[21].m_Element[10].m_btn.m_offsety))->PalScript::LoadModel(this->buf, 0);
        if ( !strcmp((const char *)(v66 + 36), unk_C10D38) )
        {
          sprintf(this->buf, "%s", "NONE");
        }
        else
        {
          Buffer = 0;
          memset(v68, 0, sizeof(v68));
          v69 = 0;
          v70 = 0;
          sprintf(&Buffer, "%s%s", v54, (const char *)(v66 + 66));
          sprintf(this->buf, "Item\\%s\\%s.tga", v54, &Buffer);
        }
        (((gbGeomNode *)this[21].m_Element[10].m_btn.m_texarray.m_ptex[2]))->gbGeomNode::ReplaceTexture(this->buf);
        *(_DWORD *)&this[21].m_Element[10].m_btn.m_bBigFont = 1;
      }
      result = 1;
      break;
    case 1008:
      this->ms_BigMap.m_wndcolor.Color = nItemID;
      if ( nItemID < 0 )
        goto LABEL_135;
      if ( !(unsigned __int8)sub_4947E0(nItemID, *((_DWORD *)&this[20].m_Answer + 801), 1) )
      {
        v24 = off_5C9378[0];
LABEL_132:
        v64 = (char *)v24;
LABEL_133:
        v55 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v55))->CScreenMode::AudioSetPosition(v64, 1);
        goto LABEL_134;
      }
      sub_494880(*((_DWORD *)&this[20].m_Answer + 801));
      result = 1;
      break;
    case 1009:
      goto LABEL_134;
    case 1021:
      switch ( (unsigned int)pszBuf )
      {
        case 0xA00319u:
          v25 = *((_DWORD *)&this[20].m_Answer + 801);
          v26 = (int *)(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * v25);
          v27 = (char *)v26[2];
          if ( v27 )
          {
            (((StateUI *)this))->StateUI::UpdateAttributeDisplay(v25, v27, 0.0) /* [ROWTABLE] */;
            (((EquipUI *)this))->EquipUI::UpdateSlot(*v26, v26[1], v26[2]) /* [ROWTABLE] */;
            if ( !strcmp((const char *)(v26[2] + 36), unk_C10D38) )
              sprintf(this->buf, "%s", "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v26[2] + 36), (const char *)(v26[2] + 36));
            (((PalScript *)&this[21].m_Element[10].m_btn.m_offsety))->PalScript::LoadModel(this->buf, 0);
            v28 = (unsigned long)v26[2];
            v29 = (const char *)(v28 + 36);
            v30 = (const char *)(v28 + 66);
            if ( !strcmp((const char *)(v28 + 36), unk_C10D38) )
              goto LABEL_77;
            goto LABEL_78;
          }
          break;
        case 0xA00320u:
          v31 = *((_DWORD *)&this[20].m_Answer + 801);
          v32 = (int *)(&g_RoleSlotBuf.m_partyActor.m_nModelParamB + 352 * v31);
          v33 = (char *)v32[2];
          if ( v33 )
          {
            (((StateUI *)this))->StateUI::UpdateAttributeDisplay(v31, v33, _pal3_coerce_f32(2)) /* [ROWTABLE] */;
            (((EquipUI *)this))->EquipUI::UpdateSlot(*v32, v32[1], v32[2]) /* [ROWTABLE] */;
            if ( !strcmp((const char *)(v32[2] + 36), unk_C10D38) )
              sprintf(this->buf, "%s", "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v32[2] + 36), (const char *)(v32[2] + 36));
            (((PalScript *)&this[21].m_Element[10].m_btn.m_offsety))->PalScript::LoadModel(this->buf, 0);
            v34 = (unsigned long)v32[2];
            v29 = (const char *)(v34 + 36);
            v30 = (const char *)(v34 + 66);
            if ( !strcmp((const char *)(v34 + 36), unk_C10D38) )
              goto LABEL_77;
            goto LABEL_78;
          }
          break;
        case 0xA00321u:
          v35 = *((_DWORD *)&this[20].m_Answer + 801);
          v36 = (int *)(&g_RoleSlotBuf.m_partyActor.m_nAnimFrames + 352 * v35);
          v37 = (char *)v36[2];
          if ( v37 )
          {
            (((StateUI *)this))->StateUI::UpdateAttributeDisplay(v35, v37, _pal3_coerce_f32(1)) /* [ROWTABLE] */;
            (((EquipUI *)this))->EquipUI::UpdateSlot(*v36, v36[1], v36[2]) /* [ROWTABLE] */;
            if ( !strcmp((const char *)(v36[2] + 36), unk_C10D38) )
              sprintf(this->buf, "%s", "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v36[2] + 36), (const char *)(v36[2] + 36));
            (((PalScript *)&this[21].m_Element[10].m_btn.m_offsety))->PalScript::LoadModel(this->buf, 0);
            v38 = (unsigned long)v36[2];
            v29 = (const char *)(v38 + 36);
            v30 = (const char *)(v38 + 66);
            if ( !strcmp((const char *)(v38 + 36), unk_C10D38) )
              goto LABEL_77;
            goto LABEL_78;
          }
          break;
        case 0xA00322u:
          v39 = *((_DWORD *)&this[20].m_Answer + 801);
          v40 = (int *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * v39 + 1];
          v41 = (char *)v40[2];
          if ( v41 )
          {
            (((StateUI *)this))->StateUI::UpdateAttributeDisplay(v39, v41, _pal3_coerce_f32(3)) /* [ROWTABLE] */;
            (((EquipUI *)this))->EquipUI::UpdateSlot(*v40, v40[1], v40[2]) /* [ROWTABLE] */;
            if ( !strcmp((const char *)(v40[2] + 36), unk_C10D38) )
              sprintf(this->buf, "%s", "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v40[2] + 36), (const char *)(v40[2] + 36));
            (((PalScript *)&this[21].m_Element[10].m_btn.m_offsety))->PalScript::LoadModel(this->buf, 0);
            v42 = (unsigned long)v40[2];
            v29 = (const char *)(v42 + 36);
            v30 = (const char *)(v42 + 66);
            if ( !strcmp((const char *)(v42 + 36), unk_C10D38) )
              goto LABEL_77;
            goto LABEL_78;
          }
          break;
        case 0xA00323u:
          v43 = *((_DWORD *)&this[20].m_Answer + 801);
          v44 = (int *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v43 + 1];
          v45 = (char *)v44[2];
          if ( v45 )
          {
            (((StateUI *)this))->StateUI::UpdateAttributeDisplay(v43, v45, _pal3_coerce_f32(4)) /* [ROWTABLE] */;
            (((EquipUI *)this))->EquipUI::UpdateSlot(*v44, v44[1], v44[2]) /* [ROWTABLE] */;
            if ( !strcmp((const char *)(v44[2] + 36), unk_C10D38) )
              sprintf(this->buf, "%s", "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v44[2] + 36), (const char *)(v44[2] + 36));
            (((PalScript *)&this[21].m_Element[10].m_btn.m_offsety))->PalScript::LoadModel(this->buf, 0);
            v46 = (unsigned long)v44[2];
            v29 = (const char *)(v46 + 36);
            v30 = (const char *)(v46 + 66);
            if ( !strcmp((const char *)(v46 + 36), unk_C10D38) )
              goto LABEL_77;
            goto LABEL_78;
          }
          break;
        case 0xA00324u:
          v47 = *((_DWORD *)&this[20].m_Answer + 801);
          v48 = (int *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * v47 + 4];
          v49 = (char *)v48[2];
          if ( v49 )
          {
            (((StateUI *)this))->StateUI::UpdateAttributeDisplay(v47, v49, _pal3_coerce_f32(5)) /* [ROWTABLE] */;
            (((EquipUI *)this))->EquipUI::UpdateSlot(*v48, v48[1], v48[2]) /* [ROWTABLE] */;
            if ( !strcmp((const char *)(v48[2] + 36), unk_C10D38) )
              sprintf(this->buf, "%s", "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v48[2] + 36), (const char *)(v48[2] + 36));
            (((PalScript *)&this[21].m_Element[10].m_btn.m_offsety))->PalScript::LoadModel(this->buf, 0);
            v50 = (unsigned long)v48[2];
            v29 = (const char *)(v50 + 36);
            v30 = (const char *)(v50 + 66);
            if ( !strcmp((const char *)(v50 + 36), unk_C10D38) )
            {
LABEL_77:
              buf = this->buf;
              sprintf(this->buf, "%s", "NONE");
            }
            else
            {
LABEL_78:
              Buffer = 0;
              memset(v68, 0, sizeof(v68));
              v69 = 0;
              v70 = 0;
              sprintf(&Buffer, "%s%s", v29, v30);
              buf = this->buf;
              sprintf(this->buf, "Item\\%s\\%s.tga", v29, &Buffer);
            }
            (((gbGeomNode *)this[21].m_Element[10].m_btn.m_texarray.m_ptex[2]))->gbGeomNode::ReplaceTexture(buf);
            *(_DWORD *)&this[21].m_Element[10].m_btn.m_bBigFont = 1;
            v64 = (char *)off_5C936C;
            goto LABEL_133;
          }
          break;
        default:
          break;
      }
LABEL_134:
      result = 1;
      break;
    default:
LABEL_135:
      result = this->UIWnd::OnMessage(nVal, (int)pszBuf, nItemID);
      break;
  }
  return result;
}

// 0x0052C8A0
void UIBigMap::DestroyFrames()
{
  gbColorQuad *p_m_fontcolor; // ecx
  int *p_m_offsetx; // esi
  int v4; // ebp
  _PlugInfo **p_m_disablepicInfo; // esi
  int v6; // edi

  p_m_fontcolor = (gbColorQuad *)&this->m_Element[4].m_btn.m_fontcolor;
  *((_DWORD *)&this->m_Answer + 788) = 0;
  *((_BYTE *)&this->m_Answer + 3156) = 1;
  *((_DWORD *)&this->m_Answer + 790) = 0;
  *((_DWORD *)&this->m_Answer + 791) = 1084227584;
  *((_BYTE *)&this->m_Answer + 3168) = 0;
  this->m_Element[1].m_btn.m_caption[40] = 0;
  *((_BYTE *)&this->m_Answer + 3174) = 0;
  this->m_Element[1].m_btn.m_caption[41] = 0;
  this->m_Element[1].m_btn.m_caption[43] = 0;
  p_m_fontcolor->Color = -1;
  p_m_fontcolor[1].Color = -1;
  p_m_fontcolor[2].Color = -1;
  p_m_fontcolor[3].Color = -1;
  *(_DWORD *)((char *)&this->m_Answer + 3169) = 0;
  *((_BYTE *)&this->m_Answer + 3173) = 0;
  (*(void ( **)(LONG *, int))this->m_Element[4].m_btn.m_rect.top)(&this->m_Element[4].m_btn.m_rect.top, 1);
  ((void ( *)(_PlugInfo **, int))this->m_Element[4].m_btn.m_texarrayInfo[2]->filepos)(
    &this->m_Element[4].m_btn.m_texarrayInfo[2],
    1);
  (**(void ( ***)(char *, _DWORD))&this->m_Element[1].m_btn.m_caption[44])((char *)(&this->m_Element[1].m_btn.m_caption[44]), (_DWORD)(0));
  (*(void ( **)(int *, _DWORD))this->m_Element[2].m_screenPt.y)(
    &this->m_Element[2].m_screenPt.y,
    0);
  this->m_Element[2].m_btn.m_texarray.m_ptex[14] = 0;
  this->m_Element[2].m_btn.m_texarray.m_ptex[15] = 0;
  LOBYTE(this->m_Element[2].m_btn.m_texarrayInfo[1]) = 0;
  p_m_offsetx = (int *)&this->m_Element[5].m_btn.m_offsetx;
  v4 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*(p_m_offsetx - 38))(p_m_offsetx - 38, 0);
    (*(void ( **)(int *, _DWORD))*p_m_offsetx)(p_m_offsetx, 0);
    (*(void ( **)(int *, _DWORD))p_m_offsetx[38])(p_m_offsetx + 38, 0);
    (*(void ( **)(int *, _DWORD))p_m_offsetx[76])(p_m_offsetx + 76, 0);
    (*(void ( **)(int *, _DWORD))p_m_offsetx[114])(p_m_offsetx + 114, 0);
    (*(void ( **)(int *, _DWORD))p_m_offsetx[175])(p_m_offsetx + 175, 0);
    (*(void ( **)(int *, _DWORD))p_m_offsetx[213])(p_m_offsetx + 213, 0);
    (*(void ( **)(int *, _DWORD))p_m_offsetx[251])(p_m_offsetx + 251, 0);
    (*(void ( **)(int *, _DWORD))p_m_offsetx[312])(p_m_offsetx + 312, 0);
    p_m_offsetx += 388;
    --v4;
  }
  while ( v4 );
  p_m_disablepicInfo = (_PlugInfo **)&this->m_Element[2].m_btn.m_disablepicInfo;
  v6 = 4;
  do
  {
    ((void ( *)(_PlugInfo **, _DWORD))(*p_m_disablepicInfo)->filepos)(p_m_disablepicInfo, 0);
    p_m_disablepicInfo += 38;
    --v6;
  }
  while ( v6 );
}

// 0x0052E0F0
int UIBigMap::SetBounds(int msg, int wparam, int lparam)
{
  this->m_bcreateok = msg;
  this->m_pbktex = ((gbTexture *)((gbTexture *)msg));
  this->m_bvisible = wparam;
  this->screenrect.left = wparam;
  this->m_benable = lparam;
  this->screenrect.top = lparam;
  return (((UIScene *)this))->UIScene::CalcViewTransform(1) /* [ROWTABLE] */;
}

// 0x00539810
void UIBigMap::SetElementVisible(FILE *Buffer, FILE *Stream)
{
  Actor *v4; // ecx
  Actor *v5; // esi
  int i; // edi
  char *v7; // esi
  int v8; // ecx
  int j; // edi
  int v10; // [esp+0x18] [ebp-0x2A4] BYREF
  int Buffera; // [esp+0x1C] [ebp-0x2A0] BYREF
  __int16 v12; // [esp+0x22] [ebp-0x29A] BYREF
  UIBigMap *v13; // [esp+0x24] [ebp-0x298]
  Actor *m_actarray_end; // [esp+0x28] [ebp-0x294]
  char pVal[40]; // [esp+0x2C] [ebp-0x290] BYREF
  int v16; // [esp+0x54] [ebp-0x268]
  int v17; // [esp+0x58] [ebp-0x264]
  int v18; // [esp+0x5C] [ebp-0x260]
  int base[57]; // [esp+B4h] [ebp-0x208] BYREF
  gbAABBox v20; // [esp+0x198] [ebp-0x124] BYREF
  gbVec3D v21; // [esp+0x29C] [ebp-0x20] BYREF
  gbVec3D v22; // [esp+0x2A8] [ebp-0x14] BYREF
if ( Buffer )
  {
    fread(this, 0x84u, 1u, Buffer);
    Buffera = 0;
    fread(&Buffera, 4u, 1u, Buffer);
    v4 = (Actor *)(*(Actor **)&this->buf[32]);
    v5 = (Actor *)&this->buf[28];
    m_actarray_end = (Actor *)v5->m_actarray_end;
    v5->m_actarray_end = v4;
    v16 = 0;
    v17 = 0;
    v18 = 0;
    for ( i = 0; i < Buffera; ++i )
    {
      fread(pVal, 0x290u, 1u, Buffer);
      PtrVec_InsertN(v5, &v5->m_actarray_end->m_actarray_type, 1u, pVal);
    }
    v7 = (char *)&this->buf[44];
    v8 = *(_DWORD *)&this->buf[48];
    m_actarray_end = (Actor *)(*(Actor **)&this->buf[52]);
    *(_DWORD *)&this->buf[52] = v8;
    v10 = 0;
    fread(&v10, 4u, 1u, Buffer);
    for ( j = 0; j < v10; ++j )
    {
      fread(&v12, 2u, 1u, Buffer);
      PtrVec_Insert_word((Actor *)v7, *((_WORD **)v7 + 2), 1u, &v12);
    }
  }
}
