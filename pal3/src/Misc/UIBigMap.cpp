#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIBigMap.h"

// Forward declarations for unnamed functions
int sub_43FD90(float *_this, int a2); // from annotations
void sub_43FDB0(float *_this, int a2); // from annotations
int sub_43FEC0(void *a2); // from annotations
int sub_442000(void); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445ED0(int a2, int a3); // from annotations
int sub_445FA0(void *a2); // from annotations
int sub_4947E0(...);
int sub_494880(...);
int sub_496DD0(int a2); // from annotations

void ActVec_Insert_char(Actor *_this, char *pszBuf, unsigned int dwVal, char *pszBuf2); // from annotations
_WORD * ActVec_Insert_word(Actor *_this, _WORD *p_WORD, unsigned int dwVal, _WORD *p_WORD2); // from annotations
struct gbVFileSystem * LoadScene(double sceneNames, char *arg8, char *pszBuf, char pData, char pData2); // from annotations
float * Vec3D_Lerp(float *pOut, float *pSrc, float fLerpFactor); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];
extern char byte_A00110;
extern unsigned __int8 byte_D8BC2C;
extern CHAR byte_DC6A3C[256];
extern CHAR byte_DC773C[256];
extern int dword_56D5F0[];
extern int dword_D8BC38;
extern RoleSystem * dword_D8BEEC;
extern int dword_DC743C;
extern int dword_DC753C;
extern int dword_DC763C;
extern int dword_DDAB3C;
extern int dword_DDAC3C;
void __cdecl nullsub_10(void);
void __cdecl nullsub_7(void);
void __cdecl nullsub_8(void);
void __cdecl nullsub_9(void);
extern const char * off_56D5D8;
extern void * off_5C936C;
extern _SPropValue * off_5C9378;
extern RoleSystem stru_C059A0;
extern gbVec3D stru_D8BC20;

// 0x00414E50
int UIBigMap::Update(int *deltatime, int haveinput)
{
  int v4; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st6
  float v9; // [esp+0x8] [ebp-0x18]
  float v10; // [esp+0xC] [ebp-0x14]
  float v11; // [esp+0x10] [ebp-0x10]
  float v12; // [esp+0x10] [ebp-0x10]
  gbVec3D v13; // [esp+0x14] [ebp-0xC] BYREF

  ((RoleSystem *)this)->Notify();
  *(_DWORD *)&this->m_Element[1].m_btn.m_caption[112] = 11;
  *(_DWORD *)&this->m_Element[1].m_btn.m_caption[116] = haveinput;
  v4 = *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 5);
  if ( v4 != 4 )
    *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 4) = v4;
  *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 5) = 4;
  this->m_Element[2].m_btn.m_childs.m_needscriptdel = *(_DWORD *)&this->buf[56];
  this->m_Element[2].m_btn.m_bcreateok = *(_DWORD *)&this->buf[60];
  this->m_Element[2].m_btn.m_bvisible = *(_DWORD *)&this->buf[64];
  *(_DWORD *)&this->m_Element[1].m_btn.m_caption[124] = *deltatime;
  *(_DWORD *)&this->m_Element[1].m_btn.m_benable_snd = deltatime[1];
  *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 1) = deltatime[2];
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
  ((gbVec3D *)&v13)->Normalize();
  v7 = 0.0 - v13.z;
  v12 = v13.x - 0.0;
  *(_DWORD *)&this->m_Element[1].m_isBtnCreate = 0;
  *(float *)&this->m_Element[1].m_btn.m_surecolor.Color = v7;
  *(float *)&this->m_Element[2].m_bShow = v12;
  ((gbVec3D *)&this->m_Element[1].m_btn.m_surecolor)->Normalize();
  return ((Actor *)&this->m_Element[0].m_btn.m_texarray.m_ptex[13])->CompareActionName(18, 0);
}

// 0x00418260
int UIBigMap::Update(int deltatime, float *haveinput)
{
  int v5; // ecx
  int v6; // eax
  gbVec3D *v7; // eax
  float v8; // edx
  float v9; // eax
  float *v10; // edi
  gbVec3D *v11; // eax
  float v12; // edx
  float v13; // eax
  double v14; // st7
  gbVec3D *v15; // eax
  float v16; // edx
  float v17; // eax
  double v18; // st7
  gbVec3D *v19; // eax
  float v20; // edx
  float v21; // eax
  gbVec3D *v22; // eax
  float y; // edx
  float z; // eax
  double v25; // st7
  int v26; // eax
  RoleSystem *v27; // ecx
  float *v28; // eax
  RoleSystem *v29; // ecx
  int v30; // eax
  int v31; // eax
  RoleSystem *v32; // ecx
  float *v33; // eax
  int v34; // eax
  int *p_m_nSize; // esi
  int v36; // esi
  float v37; // [esp+0x94] [ebp-0x68]
  float v38; // [esp+0x98] [ebp-0x64]
  float v39; // [esp+0x98] [ebp-0x64]
  float v40; // [esp+0x98] [ebp-0x64]
  float v41; // [esp+0x98] [ebp-0x64]
  float v42; // [esp+0x98] [ebp-0x64]
  float v43; // [esp+0x9C] [ebp-0x60]
  float v44; // [esp+0x9C] [ebp-0x60]
  float v45; // [esp+0x9C] [ebp-0x60]
  float v46; // [esp+0x9C] [ebp-0x60]
  float v47; // [esp+0x9C] [ebp-0x60]
  float v48; // [esp+0x9C] [ebp-0x60]
  float v49; // [esp+A0h] [ebp-0x5C]
  float v50; // [esp+A0h] [ebp-0x5C]
  float v51; // [esp+A0h] [ebp-0x5C]
  float v52; // [esp+A0h] [ebp-0x5C]
  float v53; // [esp+A0h] [ebp-0x5C]
  float v54; // [esp+A0h] [ebp-0x5C]
  float v55; // [esp+A0h] [ebp-0x5C]
  float v56; // [esp+A0h] [ebp-0x5C]
  float v57; // [esp+A0h] [ebp-0x5C]
  float v58; // [esp+A0h] [ebp-0x5C]
  float v59; // [esp+A0h] [ebp-0x5C]
  float v60; // [esp+A0h] [ebp-0x5C]
  float v61; // [esp+A0h] [ebp-0x5C]
  float v62; // [esp+A0h] [ebp-0x5C]
  float v63; // [esp+A0h] [ebp-0x5C]
  float v64; // [esp+A0h] [ebp-0x5C]
  float v65; // [esp+A0h] [ebp-0x5C]
  float v66; // [esp+A0h] [ebp-0x5C]
  float v67; // [esp+A4h] [ebp-0x58]
  float v68; // [esp+A4h] [ebp-0x58]
  float v69; // [esp+A4h] [ebp-0x58]
  float v70; // [esp+A4h] [ebp-0x58]
  float v71; // [esp+A4h] [ebp-0x58]
  float v72; // [esp+A4h] [ebp-0x58]
  float v73; // [esp+A4h] [ebp-0x58]
  float v74; // [esp+A4h] [ebp-0x58]
  float v75; // [esp+A4h] [ebp-0x58]
  float v76; // [esp+A4h] [ebp-0x58]
  float v77; // [esp+A4h] [ebp-0x58]
  float v78; // [esp+A4h] [ebp-0x58]
  float v79; // [esp+A4h] [ebp-0x58]
  float v80; // [esp+A4h] [ebp-0x58]
  float v81; // [esp+A8h] [ebp-0x54]
  float v82; // [esp+A8h] [ebp-0x54]
  float v83; // [esp+A8h] [ebp-0x54]
  float v84; // [esp+A8h] [ebp-0x54]
  float v85; // [esp+A8h] [ebp-0x54]
  float v86; // [esp+A8h] [ebp-0x54]
  float v87; // [esp+A8h] [ebp-0x54]
  float v88; // [esp+A8h] [ebp-0x54]
  float v89; // [esp+A8h] [ebp-0x54]
  float v90; // [esp+A8h] [ebp-0x54]
  float v91; // [esp+A8h] [ebp-0x54]
  float v92; // [esp+A8h] [ebp-0x54]
  float v93; // [esp+A8h] [ebp-0x54]
  float fLerpFactor; // [esp+B4h] [ebp-0x48]
  gbVec3D pSrc; // [esp+B8h] [ebp-0x44] BYREF
  _DWORD v96[2]; // [esp+C4h] [ebp-0x38] BYREF
  gbVec3D v97; // [esp+CCh] [ebp-0x30] BYREF
  float v98; // [esp+D8h] [ebp-0x24] BYREF
  gbVec3D nVal; // [esp+DCh] [ebp-0x20] BYREF
  gbVec3D pOut; // [esp+E8h] [ebp-0x14] BYREF
  __int64 v101; // [esp+F4h] [ebp-0x8] BYREF

  if ( !this->m_Element[0].m_btn.m_texarray.m_ptex[1] )
    return 0;
  if ( !*(_DWORD *)&this->buf[40] )
    return 0;
  if ( *(_DWORD *)&this->buf[156] == 3 )
    return 0;
  v5 = *((_DWORD *)&this->m_Element[1].m_btn.m_benable_snd + 5);
  if ( v5 == 4 )
  {
    v6 = *(_DWORD *)&this->m_Element[1].m_btn.m_caption[112];
    if ( v6 == 7 || v6 == 8 )
    {
      if ( *(_DWORD *)&this->m_Element[1].m_btn.m_caption[116] )
        return 0;
    }
  }
  if ( v5 != 4 || *(_DWORD *)&this->m_Element[1].m_btn.m_caption[112] )
  {
    v44 = -*(float *)&this->m_childs.capacity;
    v38 = -*(float *)&this->m_childs.m_pData;
    v37 = -*(float *)&this->m_pfather;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&pOut.z)->gbVec3D(v37, v38, v44);
    v63 = pSrc.z - *(float *)&this->m_rect.bottom;
    v45 = pSrc.y - *(float *)&this->m_rect.right;
    v39 = pSrc.x - *(float *)&this->m_rect.top;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&pOut)->gbVec3D(v39, v45, v63);
    v64 = pSrc.z * fLerpFactor;
    v46 = pSrc.y * fLerpFactor;
    v40 = pSrc.x * fLerpFactor;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&nVal)->gbVec3D(v40, v46, v64);
    v65 = pSrc.z + *(float *)&this->buf[64];
    v47 = pSrc.y + *(float *)&this->buf[60];
    v41 = pSrc.x + *(float *)&this->buf[56];
    // [AUTO-COMMENTED] v22 = ((gbVec3D *)&v97.y)->gbVec3D(v41, v47, v65);
    pSrc.x = v22->x;
    y = v22->y;
    z = v22->z;
    v10 = haveinput;
    pSrc.y = y;
    *haveinput = pSrc.x;
    haveinput[1] = y;
    haveinput[2] = z;
    v25 = *(float *)&this->m_childs.capacity - *(float *)&this->m_rect.bottom;
    pSrc.z = z;
    v66 = v25;
    v48 = *(float *)&this->m_childs.m_pData - *(float *)&this->m_rect.right;
    v42 = *(float *)&this->m_pfather - *(float *)&this->m_rect.top;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&v101)->gbVec3D(v42, v48, v66);
    Vec3D_Lerp(&pOut.x, &pSrc.x, fLerpFactor);
    ((RoleSystem *)&nVal)->AddVec3ToTarget((int)&nVal, (int)&this->buf[56]);
    ((gbVec3D *)haveinput + 3)->operator=(v26);
    ((RoleSystem *)v27)->AddVec3ToTarget((int)&v101, (int)&this->m_pfather);
    Vec3D_Lerp(&pOut.x, v28, fLerpFactor);
    ((RoleSystem *)v29)->AddVec3ToTarget((int)&nVal, (int)&this->buf[56]);
    ((gbVec3D *)haveinput + 6)->operator=(v30);
    v31 = ((gbVec3D *)&this->m_pfather)->operator-(&v101);
    ((RoleSystem *)v32)->AddVec3ToTarget((int)&nVal.z, v31);
    Vec3D_Lerp(&v98, v33, COERCE_FLOAT((UIBigMap *)&this->m_rect.top));
    ((RoleSystem *)&v97)->AddVec3ToTarget((int)&v97, (int)&this->buf[56]);
    ((gbVec3D *)haveinput + 9)->operator=(v34);
  }
  else
  {
    v67 = -*(float *)&this->m_childs.capacity;
    v49 = -*(float *)&this->m_childs.m_pData;
    v43 = -*(float *)&this->m_pfather;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&v97)->gbVec3D(v43, v49, v67);
    v81 = pSrc.z - *(float *)&this->m_rect.bottom;
    v68 = pSrc.y - *(float *)&this->m_rect.right;
    v50 = pSrc.x - *(float *)&this->m_rect.top;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&nVal)->gbVec3D(v50, v68, v81);
    v82 = pSrc.z * fLerpFactor;
    v69 = pSrc.y * fLerpFactor;
    v51 = pSrc.x * fLerpFactor;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&pOut)->gbVec3D(v51, v69, v82);
    v83 = pSrc.z + *(float *)&this->buf[52];
    v70 = pSrc.y + *(float *)&this->buf[48];
    v52 = pSrc.x + *(float *)&this->buf[44];
    // [AUTO-COMMENTED] v7 = ((gbVec3D *)&v101)->gbVec3D(v52, v70, v83);
    pSrc.x = v7->x;
    v8 = v7->y;
    v9 = v7->z;
    pSrc.y = v8;
    pSrc.z = v9;
    v10 = haveinput;
    *haveinput = pSrc.x;
    haveinput[1] = v8;
    haveinput[2] = v9;
    v84 = *(float *)&this->m_childs.capacity - *(float *)&this->m_rect.bottom;
    v71 = *(float *)&this->m_childs.m_pData - *(float *)&this->m_rect.right;
    v53 = *(float *)&this->m_pfather - *(float *)&this->m_rect.top;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&v101)->gbVec3D(v53, v71, v84);
    v85 = pSrc.z * fLerpFactor;
    v72 = pSrc.y * fLerpFactor;
    v54 = pSrc.x * fLerpFactor;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&pOut)->gbVec3D(v54, v72, v85);
    v86 = pSrc.z + *(float *)&this->buf[52];
    v73 = pSrc.y + *(float *)&this->buf[48];
    v55 = pSrc.x + *(float *)&this->buf[44];
    // [AUTO-COMMENTED] v11 = ((gbVec3D *)&nVal)->gbVec3D(v55, v73, v86);
    pSrc.x = v11->x;
    pSrc.y = v11->y;
    v12 = pSrc.y;
    v13 = v11->z;
    haveinput[3] = pSrc.x;
    haveinput[4] = v12;
    haveinput[5] = v13;
    v14 = *(float *)&this->m_childs.capacity + *(float *)&this->m_rect.bottom;
    pSrc.z = v13;
    v87 = v14;
    v74 = *(float *)&this->m_childs.m_pData + *(float *)&this->m_rect.right;
    v56 = *(float *)&this->m_rect.top + *(float *)&this->m_pfather;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&v101)->gbVec3D(v56, v74, v87);
    v88 = pSrc.z * fLerpFactor;
    v75 = pSrc.y * fLerpFactor;
    v57 = pSrc.x * fLerpFactor;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&pOut)->gbVec3D(v57, v75, v88);
    v89 = pSrc.z + *(float *)&this->buf[52];
    v76 = pSrc.y + *(float *)&this->buf[48];
    v58 = pSrc.x + *(float *)&this->buf[44];
    // [AUTO-COMMENTED] v15 = ((gbVec3D *)&nVal)->gbVec3D(v58, v76, v89);
    pSrc.x = v15->x;
    pSrc.y = v15->y;
    v16 = pSrc.y;
    v17 = v15->z;
    haveinput[6] = pSrc.x;
    haveinput[7] = v16;
    haveinput[8] = v17;
    v90 = -*(float *)&this->m_childs.capacity;
    v18 = *(float *)&this->m_childs.m_pData;
    pSrc.z = v17;
    v77 = -v18;
    v59 = -*(float *)&this->m_pfather;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&v101)->gbVec3D(v59, v77, v90);
    v91 = pSrc.z + *(float *)&this->m_rect.bottom;
    v78 = pSrc.y + *(float *)&this->m_rect.right;
    v60 = pSrc.x + *(float *)&this->m_rect.top;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&pOut)->gbVec3D(v60, v78, v91);
    v92 = pSrc.z * fLerpFactor;
    v79 = pSrc.y * fLerpFactor;
    v61 = pSrc.x * fLerpFactor;
    // [AUTO-COMMENTED] pSrc = *((gbVec3D *)&nVal)->gbVec3D(v61, v79, v92);
    v93 = pSrc.z + *(float *)&this->buf[52];
    v80 = pSrc.y + *(float *)&this->buf[48];
    v62 = pSrc.x + *(float *)&this->buf[44];
    // [AUTO-COMMENTED] v19 = ((gbVec3D *)&v97.y)->gbVec3D(v62, v80, v93);
    pSrc.x = v19->x;
    pSrc.y = v19->y;
    v20 = pSrc.y;
    v21 = v19->z;
    haveinput[9] = pSrc.x;
    pSrc.z = v21;
    haveinput[10] = v20;
    haveinput[11] = v21;
  }
  p_m_nSize = &this->m_childs.m_nSize;
  v96[0] = *p_m_nSize;
  v96[1] = p_m_nSize[1];
  LODWORD(v97.x) = p_m_nSize[2];
  ((gbVec3D *)v96)->operator*=(1065353216);
  v36 = 4;
  do
  {
    ((gbVec3D *)v10)->operator+=(&pSrc.z);
    v10 += 3;
    --v36;
  }
  while ( v36 );
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
  gbSound3DNode *v17; // eax
  _BYTE *v18; // esi
  int *v19; // eax
  _BYTE *pData; // ebp
  const char *v21; // esi
  PalScript *p_bkWndX; // ebx
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
  char *v46; // [esp+0x28] [ebp-0x16C]
  int p_DWORD[3]; // [esp+0x2C] [ebp-0x168] BYREF
  gbMatrix4 pMatrix; // [esp+0x38] [ebp-0x15C] BYREF
  float v49[2]; // [esp+0x78] [ebp-0x11C]
  float v50; // [esp+0x80] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x84] [ebp-0x110] BYREF
  int v52; // [esp+0x190] [ebp-0x4]

  ((BINK *)this)->Destroy();
  v4 = &this->buf[68];
  v5 = element - (_DWORD)&this->buf[68];
  *(_DWORD *)&this->buf[68] = *(_DWORD *)element;
  v6 = &this->buf[72];
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
  v7 = &this->buf[144];
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
  v9 = &this->buf[179];
  do
  {
    *v9 = v9[v5];
    ++v9;
  }
  while ( (unsigned int)&v9[-111 - (_DWORD)v4] < 0x10 );
  *(_DWORD *)&this->buf[196] = *(_DWORD *)(element + 128);
  *(_DWORD *)&this->buf[200] = *(_DWORD *)(element + 132);
  v46 = &this->buf[204];
  v44 = (OpenSceneFile)(element - (_DWORD)v4);
  v45 = 16;
  do
  {
    ((gbVec3D *)v46)->operator=(&v46[*(_DWORD *)&v44]);
    v10 = v45 == 1;
    v46 += 12;
    --v45;
  }
  while ( !v10 );
  v11 = &this->ms_BigMap.m_mouseoff + 2;
  *(_WORD *)&this->ms_BigMap.m_mouseoff = *(_WORD *)(element + 328);
  do
  {
    *v11 = v11[v5];
    ++v11;
  }
  while ( (unsigned int)&v11[-330 - (_DWORD)v4] < 0x20 );
// [VFTABLE] BYTE2(this->m_Element[0].m_btn.__vftable) = *(_BYTE *)(element + 362);
  ((gbVec3D *)&this->m_Element[0].m_btn.m_fontcolor)->operator=(element + 364);
  ((gbVec3D *)&this->m_Element[0].m_btn.m_rect)->operator=(element + 376);
  this->m_Element[0].m_btn.m_rect.bottom = *(_DWORD *)(element + 388);
  p_m_pfather = &this->m_Element[0].m_btn.m_pfather;
  do
  {
    *(_BYTE *)p_m_pfather = *((_BYTE *)p_m_pfather + v5);
    p_m_pfather = (UIWnd **)((char *)p_m_pfather + 1);
  }
  while ( (unsigned int)p_m_pfather - 392 - (unsigned int)v4 < 8 );
  this->m_Element[0].m_btn.m_childs.capacity = *(_DWORD *)(element + 400);
  this->m_Element[0].m_btn.m_childs.m_nSize = *(_DWORD *)(element + 404);
  this->m_Element[0].m_btn.m_childs.m_needscriptdel = *(_DWORD *)(element + 408);
  p_m_bcreateok = &this->m_Element[0].m_btn.m_bcreateok;
  v14 = 52;
  do
  {
    *p_m_bcreateok = *(int *)((char *)p_m_bcreateok + v5);
    ++p_m_bcreateok;
    --v14;
  }
  while ( v14 );
  this->buf[104] = ((RoleSystem *)element)->SetAnimBlend();
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
          // [AUTO-COMMENTED] v17 = ((gbSound3DNode *)v16)->gbSound3DNode();
        else
          v17 = 0;
        this->m_Element[0].m_btn.m_optData.pData = v17;
        v52 = -1;
        sprintf(Buffer, "snd\\%s.wav", &this->buf[72]);
        if ( ((gbSound3DNode *)this->m_Element[0].m_btn.m_optData.pData)->LoadFromFile(Buffer) )
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
            operator delete(v18);
          }
          this->m_Element[0].m_btn.m_optData.pData = 0;
        }
      }
    }
    else
    {
      if ( v15 == 23 && *(_DWORD *)&this->buf[152] == 1 )
        LOBYTE(dword_D8BC38) = this->buf[71] == 0;
      v21 = (const char *)(element + 4);
      if ( strlen((const char *)(element + 4)) )
      {
        if ( *v21 == 95 )
        {
          sprintf(Buffer, "%s%s", "scene\\", visible);
          v52 = 1;
          sprintf(Buffer, "%s\\%s", visible + 64, v21);
          p_bkWndX = (PalScript *)&this->bkWndX;
          ((GeomNode *)&this->bkWndX)->InitFromFile((const gbGeomNode *)Buffer, 0);
          v23 = this->buf[140];
          if ( v23 == 3 || v23 == 13 )
          {
            strcpy(&Buffer[strlen(Buffer) - 4], "A.pol");
            v24 = (gbGeomNode *)operator new(0x118u);
            v25 = v24;
            v45 = (int)v24;
            LOBYTE(v52) = 2;
            if ( v24 )
            {
              v26 = v25;
            }
            else
            {
              v26 = 0;
            }
            LOBYTE(v52) = 1;
            this->m_bcreateok = (int)v26;
            ((gbGeomNode *)v26)->LoadFromFile(Buffer, 0, 0);
          }
          v52 = -1;
          ((OpenSceneFile *)&v44)->_OpenSceneFile();
        }
        else
        {
          if ( *v21 == 43 )
          {
            p_bkWndX = (PalScript *)&this->bkWndX;
            capacity = this->m_Element[0].m_btn.m_childs.capacity;
            v52 = 3;
            ((GeomNode *)&this->bkWndX)->InitFromFile((const gbGeomNode *)v21, capacity);
            v52 = -1;
          }
          else if ( strchr(v21, 46) )
          {
            v52 = 5;
            sprintf(Buffer, "object\\%s", v21);
            p_bkWndX = (PalScript *)&this->bkWndX;
            ((GeomNode *)&this->bkWndX)->InitFromFile((const gbGeomNode *)Buffer, 0);
            v27 = this->buf[140];
            if ( v27 == 3 || v27 == 13 )
            {
              strcpy(&Buffer[strlen(Buffer) - 4], "A.pol");
              v28 = (gbGeomNode *)operator new(0x118u);
              v29 = v28;
              v45 = (int)v28;
              LOBYTE(v52) = 6;
              if ( v28 )
              {
                v30 = v29;
              }
              else
              {
                v30 = 0;
              }
              LOBYTE(v52) = 5;
              this->m_bcreateok = (int)v30;
              ((gbGeomNode *)v30)->LoadFromFile(Buffer, 0, 0);
            }
            v52 = -1;
          }
          else
          {
            v52 = 4;
            sprintf(Buffer, "item\\%s\\%s.pol", v21, v21);
            p_bkWndX = (PalScript *)&this->bkWndX;
            ((GeomNode *)&this->bkWndX)->InitFromFile((const gbGeomNode *)Buffer, 0);
            v52 = -1;
          }
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
            if ( p_bkWndX->m_bLoadSceneScript == 3 )
            {
              ((gbVisNode *)this->bkWndY)->SetTimeScale(0.0);
              (*(void ( **)(int, _DWORD))(*(_DWORD *)this->bkWndY + 24))(this->bkWndY, 0);
              ((PalScript *)p_bkWndX)->GetCount(0);
            }
            break;
          case 4:
          case 6:
          case 0xE:
            ((gbVisNode *)this->bkWndY)->SetTimeScale(0.0);
            (*(void ( **)(int, _DWORD))(*(_DWORD *)this->bkWndY + 24))(this->bkWndY, 0);
            break;
          case 5:
            v33 = operator new(0x1C28u);
            v34 = v33;
            v44 = (OpenSceneFile)v33;
            v52 = 7;
            if ( v33 )
            {
              v35 = v33;
              v36 = 256;
              do
              {
                v35 += 3;
                --v36;
              }
              while ( v36 );
              v37 = v34 + 1026;
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
            *(_DWORD *)&this->m_Element[0].m_btn.m_caption[68] = v34;
            v34[768] = v39;
            v40 = *(_DWORD **)&this->m_Element[0].m_btn.m_caption[68];
            v52 = -1;
            qmemcpy(v40, &this->buf[204], 12 * v40[768]);
            ((PathObj *)*(PathObj **)&this->m_Element[0].m_btn.m_caption[68])->CalcLength();
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
            if ( *(_DWORD *)&this->buf[148] && p_bkWndX->m_bLoadSceneScript == 3 )
            {
              ((gbVisNode *)this->bkWndY)->SetTimeScale(0.0);
              (*(void ( **)(int, _DWORD))(*(_DWORD *)this->bkWndY + 24))(this->bkWndY, 0);
              ((PalScript *)p_bkWndX)->GetCount(0);
            }
            v31 = rand();
            this->m_pbktex = 0;
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
        if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(p_DWORD) )
          this->buf[69] = 0;
      }
      bkWndX = this->bkWndX;
      if ( bkWndX == 2 || bkWndX == 3 )
      {
        ((PalScriptMgr *)this)->BuildCmdTransform(&pMatrix);
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
          ((gbGeomNode *)this->bkWndY)->SetAnimLoop(1);
        }
      }
      if ( this->buf[69] && this->bkWndX == 4 && !_strcmpi(&this->buf[72], a4_0) )
        ((CEffMgr *)this->bkWndY)->SetEffectClass(*(_DWORD *)&this->buf[108], *(_DWORD *)&this->buf[112], *(_DWORD *)&this->buf[116]);
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
  double v7; // st6
  double v8; // st5
  double v9; // st5
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
    if ( this->buf[140] == 27 && dword_D8BEEC )
      ((RoleSystem *)dword_D8BEEC)->RenderRole(pStack, 0);
    if ( this->bkWndX )
    {
      if ( (byte_D8BC2C & 1) == 0 )
      {
        ((gbVec3D *)&stru_D8BC20)->x = 0.0;
        byte_D8BC2C |= 1u;
        ((gbVec3D *)&stru_D8BC20)->y = 1.0;
        ((gbVec3D *)&stru_D8BC20)->z = 0.0;
        atexit(nullsub_10);
      }
      if ( (byte_D8BC2C & 2) == 0 )
      {
        g_ScriptSystemData = 1065353216;
        byte_D8BC2C |= 2u;
        g_ScriptSystemData = 0;
        g_ScriptSystemData = 0;
        atexit(nullsub_9);
      }
      if ( (byte_D8BC2C & 4) == 0 )
      {
        g_ScriptSystemData = 0;
        byte_D8BC2C |= 4u;
        g_ScriptSystemData = 0;
        g_ScriptSystemData = 1065353216;
        atexit(nullsub_8);
      }
      v4 = 0;
      switch ( this->buf[140] )
      {
        case 3:
          ((gbMatrixStack *)pStack)->Push();
          ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->buf[108]);
          ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->buf[120], stru_D8BC20);
          ((PalScript *)&this->bkWndX)->SetIndex(visible);
          ((gbMatrixStack *)pStack)->Pop();
          if ( LOBYTE(this->screenrect.right) == 1 && this->m_bcreateok )
          {
            ((gbMatrixStack *)pStack)->Push();
            ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_bvisible);
            ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->buf[120], stru_D8BC20);
            (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_bcreateok + 16))(this->m_bcreateok, 0);
            goto LABEL_32;
          }
          goto LABEL_33;
        case 4:
          if ( LOBYTE(this->screenrect.right) )
          {
            ((gbMatrixStack *)pStack)->Push();
            ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_childs.capacity);
            ((PalScript *)&this->bkWndX)->SetIndex(visible);
            goto LABEL_32;
          }
          goto LABEL_33;
        case 0xD:
          ((gbMatrixStack *)pStack)->Push();
          ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->buf[108]);
          ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->buf[120], stru_D8BC20);
          ((PalScript *)&this->bkWndX)->SetIndex(visible);
          ((gbMatrixStack *)pStack)->Pop();
          if ( this->m_bcreateok )
          {
            ((gbMatrixStack *)pStack)->Push();
            ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_bvisible);
            ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->buf[120], stru_D8BC20);
            (*(void ( **)(int, int))(*(_DWORD *)this->m_bcreateok + 16))(
              this->m_bcreateok,
              visible);
            goto LABEL_32;
          }
          goto LABEL_33;
        case 0x15:
          ((gbMatrixStack *)pStack)->Push();
          ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_childs.capacity);
          v5 = g_pRoleSystem;
          v16 = g_pRoleSystem;
          if ( g_pRoleSystem )
          {
            if ( (byte_D8BC2C & 8) == 0 )
            {
              byte_D8BC2C |= 8u;
              g_ScriptSystemData = 0;
              g_ScriptSystemData = 0;
              g_ScriptSystemData = 1065353216;
              atexit(nullsub_7);
              v5 = v16;
            }
            p_m_fPosX = &v5->m_fPosX;
            v18.x = *p_m_fPosX;
            v18.y = p_m_fPosX[1];
            v7 = *(float *)&this->m_childs.capacity - v18.x;
            v8 = *(float *)&this->m_childs.m_nSize - (v18.y + 60.0);
            v18.z = p_m_fPosX[2];
            v20.x = v8;
            v9 = *(float *)&this->m_childs.m_needscriptdel - v18.z;
            v18.y = v20.x;
            v20.y = v9;
            v18.x = v7;
            v18.z = v20.y;
            ((gbVec3D *)&v18)->Normalize();
            v22 = 0.0;
            v21 = 0.0;
            v20.z = 0.0;
            v23 = 1.0;
            ((gbQuaternion *)&v20.z)->SetTwoVector((gbVec3D *)&g_ScriptSystemData, &v18);
            ((gbMatrixStack *)pStack)->Rotate((gbQuaternion *)&v20.z);
          }
          goto LABEL_31;
        case 0x18:
          if ( *(_DWORD *)&this->buf[148] == 1 )
            goto LABEL_33;
          ((gbMatrixStack *)pStack)->Push();
          ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_childs.capacity);
          ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->buf[120], stru_D8BC20);
          ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->m_Element[0].m_btn.m_rect.bottom, (gbVec3D *)&g_ScriptSystemData);
          ((PalScript *)&this->bkWndX)->SetIndex(visible);
LABEL_32:
          ((gbMatrixStack *)pStack)->Pop();
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
          SoundList = (CScreenMode *)((CScreenMode *)v4)->GetSoundList();
          if ( !((CScreenMode *)SoundList)->IsAudioReady() || !v17 )
            return;
          ((Object3D *)this)->SetTransform((gbMatrix4 *)&pMatrix);
          v20.z = 0.0;
          v21 = 0.0;
          v22 = 0.0;
          v23 = 0.0;
          v24 = 0.0;
          v25 = 0.0;
          ((gbOBBox *)&pMatrix)->GetAABBox((gbAABBox *)&v20.z);
          v12 = this->buf[140];
          if ( v12 == 15 )
          {
            p_capacity = &this->m_childs.capacity;
            v19 = *(float *)p_capacity;
            LODWORD(v20.x) = p_capacity[1];
            v14 = *((float *)p_capacity + 2);
            v20.x = v24;
            v20.y = v14;
            ((gbMatrixStack *)pStack)->Push();
            ((gbMatrixStack *)pStack)->Translate(v20);
            ((gbMatrixStack *)pStack)->Scale(1.0,   -1.0,   1.0);
            x = v18.x;
            (*(void ( **)(_DWORD, _DWORD))(*(_DWORD *)LODWORD(v18.x) + 16))(LODWORD(v18.x), 0);
            ((gbMatrixStack *)pStack)->Pop();
            v20.y = v22;
            ((gbMatrixStack *)pStack)->Push();
            ((gbMatrixStack *)pStack)->Translate(v20);
            (*(void ( **)(_DWORD))(*(_DWORD *)LODWORD(x) + 16))(0);
          }
          else
          {
            if ( v12 != 23 )
              return;
            v19 = v23 + v20.z;
            v20.x = v21 + v24;
            v20.y = v22 + v25;
            v18.x = v19 * 0.5;
            v18.z = v20.y * 0.5;
            v18.y = v24 + 2.0;
            ((gbMatrixStack *)pStack)->Push();
            ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&v18.y);
            (*(void ( **)(_DWORD))(*(_DWORD *)LODWORD(v18.x) + 16))(0);
          }
          ((gbMatrixStack *)pStack)->Pop();
          break;
        case 0x1C:
          if ( *(_DWORD *)&this->buf[144] )
          {
            ((gbMatrixStack *)pStack)->Push();
            ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_childs.capacity);
            ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->buf[120], stru_D8BC20);
          }
          else
          {
            ((gbMatrixStack *)pStack)->Push();
            ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_childs.capacity);
            ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->buf[120], stru_D8BC20);
            ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->m_bvisible, (gbVec3D *)&g_ScriptSystemData);
          }
          ((PalScript *)&this->bkWndX)->SetIndex(visible);
          goto LABEL_32;
        default:
          ((gbMatrixStack *)pStack)->Push();
          ((gbMatrixStack *)pStack)->Translate((gbVec3D *)&this->m_childs.capacity);
          ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->buf[120], stru_D8BC20);
          ((gbMatrixStack *)pStack)->Rotate(*(float *)&this->m_Element[0].m_btn.m_rect.bottom, (gbVec3D *)&g_ScriptSystemData);
LABEL_31:
          ((PalScript *)&this->bkWndX)->SetIndex(visible);
          goto LABEL_32;
      }
    }
  }
}

// 0x0043BF90
int UIBigMap::Update(int deltatime, int haveinput)
{
  int v4; // eax
  int result; // eax
  int v6; // eax
  __int64 v7; // rax
  int v8; // ecx
  int v9; // ebp
  double v10; // st7
  __int64 v11; // rax
  int v12; // ecx
  int v13; // ecx
  int v14; // eax
  double v15; // st7
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
    v10 = (double)(v8 + (int)v7) - *(float *)&this->buf[132];
  }
  else
  {
    v14 = *(_DWORD *)&this->buf[164];
    if ( v14 )
    {
      result = v14 - 1;
      if ( result )
        return result;
      v15 = (double)*(int *)&this->buf[40] - *(float *)&this->buf[132];
      v9 = *(_DWORD *)&this->buf[36] - *(_DWORD *)&this->buf[140] - haveinput;
      *(_DWORD *)&this->buf[20] = v9;
      v10 = v15 - (double)(deltatime / 2);
    }
    else
    {
      v9 = *(_DWORD *)&this->buf[36] - *(_DWORD *)&this->buf[140] - haveinput;
      v16 = *(_DWORD *)&this->buf[32] - deltatime / 2;
      *(_DWORD *)&this->buf[20] = v9;
      v10 = (double)v16 + *(float *)&this->buf[132];
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
  result = sub_442000();
  *(_DWORD *)&this->buf[76] = result;
  *(_DWORD *)&this->buf[72] = result;
  return result;
}

// 0x004431E0
int UIBigMap::SetViewParams(int deltatime, int haveinput)
{
  *(_DWORD *)&this->buf[80] = deltatime;
  *(_DWORD *)&this->buf[84] = haveinput;
  return deltatime;
}

// 0x00451360
int UIBigMap::LayoutBinkVideo(LPCSTR lpString1, int haveinput)
{
  int v5; // edi
  int v6; // ebp
  char pData[4]; // [esp+0x10] [ebp-0x10] BYREF
  LONG top; // [esp+0x14] [ebp-0xC]
  int width; // [esp+0x18] [ebp-0x8]
  int height; // [esp+0x1C] [ebp-0x4]

  if ( lpString1 )
  {
    (*(void ( **)(float *, int))LODWORD(this->ms_BigMap.m_ratiow))(&this->ms_BigMap.m_ratiow, 1);
    ((UIStatic *)&this->ms_BigMap.m_ratiow)->CreateFromTemplate();
    if ( haveinput )
    {
      width = g_DrvInfo.width;
      *(_DWORD *)pData = g_DrvInfo.width - 256;
      height = g_DrvInfo.height;
      top = g_DrvInfo.height - 512;
      sub_445FA0(&this->ms_BigMap.m_ratiow);
      this->m_Element[0].m_btn.m_bvisible = 1;
      ((BINK *)this)->SetVideoRect((char)pData);
      sub_445FA0(&this->buf[168]);
      v5 = width - *(_DWORD *)pData;
      top = this->m_rect.top + 16;
      height = top + 120;
      *(_DWORD *)pData += 4;
      width = width + 484 - v5;
      sub_445FA0(&this->m_Element[0].m_btn.m_benable);
      v6 = width;
      ((BINK *)this)->SetVideoRect((char)pData);
      *(_DWORD *)pData = v6 + 4;
      width = v6 + 4 + v5;
      return sub_445FA0(&this->buf[168]);
    }
    else
    {
      height = g_DrvInfo.height;
      *(_DWORD *)pData = 0;
      width = 256;
      top = g_DrvInfo.height - 512;
      sub_445FA0(&this->ms_BigMap.m_ratiow);
      this->m_Element[0].m_btn.m_bvisible = 0;
      ((BINK *)this)->SetVideoRect((char)pData);
      sub_445FA0(&this->buf[168]);
      width = *(_DWORD *)pData - 4;
      *(_DWORD *)pData -= 484;
      top = this->m_rect.top + 16;
      height = top + 120;
      return sub_445FA0(&this->m_Element[0].m_btn.m_benable);
    }
  }
  else
  {
    (*(void ( **)(float *, _DWORD))LODWORD(this->ms_BigMap.m_ratiow))(&this->ms_BigMap.m_ratiow, 0);
    *(_DWORD *)pData = this->m_rect.left;
    top = this->m_rect.top;
    width = this->m_rect.right;
    height = g_DrvInfo.height - 2;
    top = g_DrvInfo.height - 138;
    ((BINK *)this)->SetVideoRect((char)pData);
    sub_445FA0(&this->buf[168]);
    width = *(_DWORD *)pData - 4;
    *(_DWORD *)pData -= 724;
    top = this->m_rect.top + 16;
    height = top + 120;
    return sub_445FA0(&this->m_Element[0].m_btn.m_benable);
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
  sub_445ED0((int)"ui\\scene\\role.tga", 1);
  ((PalScript *)this)->Create(id, &pRect, parent);
  pRect.bottom = (2 * g_DrvInfo.height - 74) / 2;
  pRect.left = 36;
  pRect.right = 218;
  pRect.top = pRect.bottom - 182;
  ((UINote *)&this->m_Element[0].m_btn.m_caption[24])->Create(10, (int)&pRect, 0, "ui\\flex\\map");
  sub_445FA0(&this->m_Element[0].m_btn.m_caption[24]);
  ((UIScene *)&this->m_Element[0].m_btn.m_caption[24])->SetState();
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
  sub_445FA0(&this->ms_BigMap.m_bcreateok);
  ((UIStatic *)&this->ms_BigMap.m_bcreateok)->CreateFromTemplate();
  pRect.left = 4;
  pRect.right = 65;
  pRect.bottom = g_DrvInfo.height - 5;
  pRect.top = g_DrvInfo.height - 66;
  ((void ( *)(UIWnd **, int, tagRECT *, UIBigMap *))this->m_Element[0].m_btn.m_pfather->m_rect.left)(
    &this->m_Element[0].m_btn.m_pfather,
    1,
    &pRect,
    this);
  sub_445FA0(&this->m_Element[0].m_btn.m_pfather);
  ((UIStatic *)&this->m_Element[0].m_btn.m_pfather)->CreateFromTemplate();
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
  return sub_445FA0(&this->m_pbktex);
}

// 0x00489BA0
void UIBigMap::UpdateElement(int element, int visible)
{
  int v3; // edi
  UIBigMap *v4; // esi
  int v5; // eax
  int v6; // edi
  CHAR *buf; // ebp
  int v8; // ecx
  int v9; // edx
  _BYTE *v10; // esi
  int v11; // eax
  _DWORD *v12; // ecx
  unsigned int v13; // esi
  int v14; // ecx
  int v15; // ebp
  int v16; // edi
  int v17; // eax
  const CHAR *v18; // [esp-0xC] [ebp-0x1A4]
  int v19; // [esp-0x8] [ebp-0x1A0]
  int v21; // [esp+0xC] [ebp-0x18C]
  int RoleNum; // [esp+0x14] [ebp-0x184]
  CHAR String1[125]; // [esp+0x18] [ebp-0x180] BYREF
  __int16 v24; // [esp+0x95] [ebp-0x103]
  char v25; // [esp+0x97] [ebp-0x101]
  char Buffer[253]; // [esp+0x98] [ebp-0x100] BYREF
  __int16 v27; // [esp+0x195] [ebp-0x3]
  char v28; // [esp+0x197] [ebp-0x1]
if ( this->m_Element[0].m_btn.m_enablecolor.Color )
  {
    v5 = *(unsigned __int16 *)(element + 4);
    if ( v5 + 1 > 3 )
      v5 = 2;
    if ( *(_WORD *)(element + 4) < 3u
      && (unsigned int)*(_WORD *)(element + 6) >= *(unsigned __int8 *)(*(_DWORD *)(element + 8) + v5 + 710) )
    {
      v19 = v3;
      memset(String1, 0, sizeof(String1));
      v24 = 0;
      v25 = 0;
      v6 = visible;
      switch ( visible )
      {
        case 0:
          lstrcpyA(String1, g_szRoleNameTable);
          break;
        case 1:
          v18 = (const CHAR *)dword_DC743C;
          goto LABEL_12;
        case 2:
          lstrcpyA(String1, (LPCSTR)dword_DC753C);
          break;
        case 3:
          lstrcpyA(String1, (LPCSTR)dword_DC763C);
          break;
        case 4:
          v18 = byte_DC773C;
LABEL_12:
          lstrcpyA(String1, v18);
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
          (const char *)dword_DDAB3C,
          *(unsigned __int16 *)(element + 4) + 1,
          byte_DC6A3C);
      if ( *(_WORD *)(element + 4) >= 3u )
      {
        *(_WORD *)(element + 4) = 3;
        v8 = *(_DWORD *)(element + 8);
        if ( *(_DWORD *)&::Buffer.m_partyActor.m_szTexture[1408 * visible + 4] >= (int)*(unsigned __int8 *)(v8 + 713)
          && *(_BYTE *)(v8 + 714) <= 3u )
        {
          v9 = 0;
          v21 = *(_DWORD *)(v8 + 716);
          if ( v21 )
          {
            v10 = &::Buffer.m_partyActor.m_bDirFlag + 1408 * visible + 32;
LABEL_20:
            v11 = 0;
            v12 = v10;
            while ( v21 != *v12 )
            {
              ++v11;
              ++v12;
              if ( v11 >= 8 )
              {
                ++v9;
                v10 += 32;
                if ( v9 < 6 )
                  goto LABEL_20;
                goto LABEL_26;
              }
            }
            if ( *((_BYTE *)&::Buffer.m_FrameA.m_rect.left + 1408 * visible + 8 * v9 + v11) )
              goto LABEL_27;
LABEL_26:
            RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v21);
            ((RoleSystem *)*((_DWORD *)&g_SceneMgrPrefix.m_pData + 4 * visible))->CheckVisible();
            memset(Buffer, 0, sizeof(Buffer));
            v27 = 0;
            v28 = 0;
            sprintf(Buffer, "    %s%s %s\\n", String1, (const char *)dword_DDAC3C, (const char *)(RoleNum + 28));
            lstrcatA(buf, Buffer);
          }
        }
LABEL_27:
        v6 = visible;
}
      ((UICaption *)&v4[20].m_Element[1].m_btn.m_EnableMode)->SetEnable((int)buf, 0);
      ((UIRoleSelect *)&v4[20].m_Element[0].m_btn.m_caption[104])->SetByte(1);
      v13 = 0;
      v14 = 16 * v6;
      v15 = 0;
      v16 = *(&g_SceneMgrPrefix.m_nSize + 4 * v6);
      while ( v16 && v13 < (int)&(*(char **)((char *)&g_SceneMgrPrefix.m_pData + v14))[-v16] / 12 )
      {
        if ( *(_DWORD *)(*(int *)((char *)&g_SceneMgrPrefix.m_nSize + v14) + v15) == *(_DWORD *)element )
        {
          v17 = 12 * v13;
          *(_WORD *)(*(int *)((char *)&g_SceneMgrPrefix.m_nSize + v14) + v17 + 6) = *(_WORD *)(element + 6);
          *(_WORD *)(*(int *)((char *)&g_SceneMgrPrefix.m_nSize + v14) + v17 + 4) = *(_WORD *)(element + 4);
          break;
        }
        ++v13;
        v15 += 12;
      }
      ((NPC *)v19)->InitAll();
      *(&this->m_Element[0].m_show + 2) = 0;
      *(&this->m_Element[0].m_show + 1) = 0;
      ((MainPropUI *)this)->SetPage(1u);
      this->m_Element[0].m_show = 0;
      ((CameraCtrl *)this)->BuildRenderLists();
      ((MagicUI *)this)->UpdateViewListItems();
    }
  }
}

// 0x00490E90
UIBigMap::UIBigMap()
{
  sub_4422E0(this);
  UIScene::GetSys();
  sub_4422E0(&this->ms_BigMap.m_pbk2);
  sub_4422E0(&this->m_Element[0].m_btn.m_texarray.m_ptex[5]);
  ((UIButton *)&this->m_Element[0].m_btn.m_caption[76])->ctor_17();
  sub_4422E0(&this->m_Element[1].m_btn.m_texarray.m_ptex[6]);
  sub_4422E0(&this->m_Element[1].m_btn.m_caption[80]);
  ((UIButton *)&this->m_Element[2].m_btn.m_pfather)->ctor_17();
  sub_4422E0(&this->m_Element[2].m_btn.m_caption[84]);
  sub_4422E0(&this->m_Element[3].m_btn.m_childs);
  ((UIButton *)&this->m_Element[3].m_btn.m_alignmode)->ctor_17();
  sub_4422E0(&this->m_Element[4].m_btn.m_childs.capacity);
  sub_4422E0(this->m_Element[4].m_btn.m_caption);
  sub_4422E0(&this->m_Element[4].m_btn.m_optData);
  sub_4422E0(&this->m_Element[5].m_btn.m_texarray.m_ptex[2]);
  sub_4422E0(&this->m_Element[5].m_btn.m_caption[64]);
  sub_4422E0(&this->m_Element[6].m_btn.m_rect);
  sub_4422E0(&this->m_Element[6].m_btn.m_texarrayInfo[1]);
  sub_4422E0((char *)&this->m_Answer.m_btRc + 100);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
}

// 0x004910B0
void UIBigMap::_UIBigMap()
{
  ((UICaption *)((char *)&this->m_Answer + 2604))->Destroy2();
  ((UICaption *)((char *)&this->m_Answer + 2260))->Destroy2();
  ((UICaption *)((char *)&this->m_Answer + 1916))->Destroy2();
  ((UICaption *)((char *)&this->m_Answer + 1572))->Destroy2();
  ((UICaption *)((char *)&this->m_Answer.m_btRc + 596))->Destroy2();
  ((UICaption *)((char *)&this->m_Answer.m_btRc + 252))->Destroy2();
  ((UIFrameWnd *)((char *)&this->m_Answer.m_btRc + 100))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Element[6].m_btn.m_texarrayInfo[1])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Element[6].m_btn.m_rect)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Element[5].m_btn.m_caption[64])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Element[5].m_btn.m_texarray.m_ptex[2])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Element[4].m_btn.m_optData)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)this->m_Element[4].m_btn.m_caption)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Element[4].m_btn.m_childs.capacity)->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_Element[3].m_btn.m_alignmode)->_UIButton();
  ((UIFrameWnd *)&this->m_Element[3].m_btn.m_childs)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Element[2].m_btn.m_caption[84])->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_Element[2].m_btn.m_pfather)->_UIButton();
  ((UIFrameWnd *)&this->m_Element[1].m_btn.m_caption[80])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Element[1].m_btn.m_texarray.m_ptex[6])->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_Element[0].m_btn.m_caption[76])->_UIButton();
  ((UIFrameWnd *)&this->m_Element[0].m_btn.m_texarray.m_ptex[5])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->ms_BigMap.m_pbk2)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->buf[48])->Destroy2();
// [VFTABLE] ((UIFrameWnd *)&this->__vftable)->_UIFrameWnd();
}

// 0x00491C30
int UIBigMap::GetChildCount(int nVal, int nVal2)
{
  int v4; // ecx
  char *v5; // esi
  int v6; // edx
  int v7; // eax
  int result; // eax
  int v10; // [esp+0x18] [ebp-0x10] BYREF
  int v11; // [esp+0x1C] [ebp-0xC]
  int v12; // [esp+0x20] [ebp-0x8]
  int v13; // [esp+0x24] [ebp-0x4]

  if ( nVal <= 5 )
  {
    v4 = *(_DWORD *)nVal2;
    v11 = *(_DWORD *)(nVal2 + 4);
    v13 = v11 + 12;
    v10 = v4;
    v12 = v4 + 85;
    v5 = (char *)this + 9980 * nVal;
    (*(void ( **)(char *, _DWORD, int *, UIBigMap *))(*((_DWORD *)v5 + 38827) + 16))(
      v5 + 155308,
      *(&g_pfnCallback + nVal),
      &v10,
      this);
    ((UIScene *)(v5 + 155308))->GetChildCount();
    ((UIScene *)(v5 + 155308))->GetChildAt();
    *((_DWORD *)v5 + 38845) = 1;
    v5[155478] = -30;
    v5[155477] = -51;
    v5[155476] = 58;
    v5[155479] = -1;
    sub_43FD90((float *)v5 + 38827, 4);
    ((UIWnd *)(v5 + 155308))->GetWidth(-4);
    sub_43FDB0((float *)v5 + 38827, 1);
    ((UIWnd *)(v5 + 155308))->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UIBigMap *))(*((_DWORD *)v5 + 39101) + 16))(
      v5 + 156404,
      *(&g_pfnCallback + nVal),
      &v10,
      this);
    ((UIScene *)(v5 + 156404))->GetChildCount();
    ((UIScene *)(v5 + 156404))->GetChildAt();
    *((_DWORD *)v5 + 39119) = 1;
    v5[156574] = -30;
    v5[156573] = -51;
    v5[156572] = 58;
    v5[156575] = -1;
    sub_43FD90((float *)v5 + 39101, 4);
    ((UIWnd *)(v5 + 156404))->GetWidth(-4);
    sub_43FDB0((float *)v5 + 39101, 1);
    ((UIWnd *)(v5 + 156404))->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UIBigMap *))(*((_DWORD *)v5 + 38964) + 16))(
      v5 + 155856,
      *(&g_pfnCallback + nVal),
      &v10,
      this);
    ((UIScene *)(v5 + 155856))->GetChildCount();
    ((UIScene *)(v5 + 155856))->GetChildAt();
    *((_DWORD *)v5 + 38982) = 1;
    v5[156026] = -30;
    v5[156025] = -51;
    v5[156024] = 58;
    v5[156027] = -1;
    sub_43FD90((float *)v5 + 38964, 4);
    ((UIWnd *)(UIWnd *)v5 + 2292)->GetWidth(-4);
    sub_43FDB0((float *)v5 + 38964, 1);
    ((UIWnd *)(UIWnd *)v5 + 2292)->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(*((_DWORD *)v5 + 38888) + 16))(
      v5 + 155552,
      *(&g_pfnCallback + nVal),
      nVal2,
      this);
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(*((_DWORD *)v5 + 39162) + 16))(
      v5 + 156648,
      *(&g_pfnCallback + nVal),
      nVal2,
      this);
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(*((_DWORD *)v5 + 39025) + 16))(
      v5 + 156100,
      *(&g_pfnCallback + nVal),
      nVal2,
      this);
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(*((_DWORD *)v5 + 38627) + 16))(
      v5 + 154508,
      *(&g_pfnCallback + nVal),
      nVal2,
      this);
    ((UIStatic *)(v5 + 154508))->CreateFromTemplate();
    LOBYTE(v6) = g_bDebugMode;
    (*(void ( **)(char *, int, int, UIBigMap *, char *, int, int))(*((_DWORD *)v5 + 38665) + 28))(
      v5 + 154660,
      dword_56D5F0[nVal],
      nVal2,
      this,
      &"UI\\GameMainUI\\Communal\\RoleHead0"[256 * nVal],
      1,
      v6);
    v7 = *((_DWORD *)v5 + 38751);
    v5 += 155004;
    (*(void ( **)(char *, _DWORD, int, UIBigMap *))(v7 + 16))(v5, *(&g_pfnCallback + nVal), nVal2, this);
    ((UIStatic *)v5)->CreateFromTemplate();
    return ((UIScene *)v5)->SetShow(0);
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
  int a2; // [esp+0x0] [ebp-0x40] BYREF
  int v13; // [esp+0x4] [ebp-0x3C]
  int v14; // [esp+0x8] [ebp-0x38]
  int v15; // [esp+0xC] [ebp-0x34]
  int v16; // [esp+0x10] [ebp-0x30]
  int v17; // [esp+0x14] [ebp-0x2C]
  int v18; // [esp+0x18] [ebp-0x28]
  int v19; // [esp+0x1C] [ebp-0x24]
  int v20; // [esp+0x20] [ebp-0x20]
  int v21; // [esp+0x24] [ebp-0x1C]
  int v22; // [esp+0x28] [ebp-0x18]
  int v23; // [esp+0x2C] [ebp-0x14]
  int v24; // [esp+0x30] [ebp-0x10]
  int v25; // [esp+0x34] [ebp-0xC]
  int v26; // [esp+0x38] [ebp-0x8]
  int v27; // [esp+0x3C] [ebp-0x4]

  result = arg0;
  if ( arg0 <= 5 )
  {
    v4 = (char *)this + 9980 * arg0;
    sub_445FA0(v4 + 154508);
    v5 = p_DWORD[1] + 10;
    v20 = *p_DWORD + 25;
    v22 = v20 + 65;
    v21 = v5;
    v23 = v5 + 86;
    sub_445FA0(v4 + 154660);
    v6 = p_DWORD[1] + 36;
    v24 = p_DWORD[2] - 27;
    v25 = v6;
    v26 = v24 + 32;
    v27 = v6 + 128;
    sub_445FA0(v4 + 155004);
    v7 = *p_DWORD - 72;
    v13 = p_DWORD[1] + 21;
    a2 = v7;
    v15 = v13 + 12;
    v14 = v7 + 85;
    sub_43FEC0(&a2);
    v8 = *p_DWORD - 80;
    v13 = v15 + 16;
    a2 = v8;
    v15 += 28;
    v14 = v8 + 85;
    sub_43FEC0(&a2);
    v9 = *p_DWORD - 70;
    v13 = v15 + 16;
    a2 = v9;
    v14 = v9 + 85;
    v15 += 28;
    sub_43FEC0(&a2);
    v10 = p_DWORD[1];
    v16 = a2;
    v17 = v10;
    v18 = a2 + 100;
    v19 = v10 + 32;
    sub_445FA0(v4 + 155552);
    v11 = p_DWORD[1] + 28;
    v16 = a2;
    v17 = v11;
    v19 = v11 + 32;
    v18 = a2 + 100;
    sub_445FA0(v4 + 156648);
    v17 = p_DWORD[1] + 56;
    v16 = a2;
    v18 = a2 + 100;
    v19 = v17 + 32;
    return sub_445FA0(v4 + 156100);
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
    (**((void ( ***)(int, _DWORD))v4 + 38627))((int)(v4 + 154508), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 38665))((int)(v4 + 154660), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 38751))((int)(v4 + 155004), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 38827))((int)(v4 + 155308), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 38888))((int)(v4 + 155552), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39101))((int)(v4 + 156404), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39162))((int)(v4 + 156648), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 38964))((int)(v4 + 155856), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39025))((int)(v4 + 156100), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39200))((int)(v4 + 156800), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39238))((int)(v4 + 156952), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39276))((int)(v4 + 157104), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39314))((int)(v4 + 157256), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39352))((int)(v4 + 157408), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39390))((int)(v4 + 157560), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39428))((int)(v4 + 157712), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39808))((int)(v4 + 159232), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40188))((int)(v4 + 160752), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39466))((int)(v4 + 157864), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39846))((int)(v4 + 159384), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40226))((int)(v4 + 160904), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39504))((int)(v4 + 158016), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39884))((int)(v4 + 159536), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40264))((int)(v4 + 161056), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39542))((int)(v4 + 158168), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39922))((int)(v4 + 159688), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40302))((int)(v4 + 161208), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39580))((int)(v4 + 158320), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39960))((int)(v4 + 159840), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40340))((int)(v4 + 161360), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39618))((int)(v4 + 158472), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39998))((int)(v4 + 159992), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40378))((int)(v4 + 161512), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39656))((int)(v4 + 158624), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40036))((int)(v4 + 160144), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40416))((int)(v4 + 161664), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39694))((int)(v4 + 158776), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40074))((int)(v4 + 160296), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40454))((int)(v4 + 161816), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39732))((int)(v4 + 158928), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40112))((int)(v4 + 160448), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40492))((int)(v4 + 161968), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 39770))((int)(v4 + 159080), bParam);
    (**((void ( ***)(int, _DWORD))v4 + 40150))((int)(v4 + 160600), bParam);
    return (**((int ( ***)(int, _DWORD))v4 + 40530))((int)(v4 + 162120), bParam);
  }
  return result;
}

// 0x00496FA0
void UIBigMap::Render()
{
  int i; // edi
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v3);
  if ( *((_BYTE *)this + *((_DWORD *)this + 38626) + 154496) )
  {
    for ( i = 0; i < 16; ++i )
    {
// [IDA_MISID]       if ( ((Concurrency *)(&this->m_Element[11].m_btn.m_rect.top + 2336 * *((_DWORD *)this + 38626) + 146 * i))->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)(&this->m_Element[11].m_btn.m_rect.top
                                           + 2336 * *((_DWORD *)this + 38626)
                                           + 146 * i))->Apply();
// [IDA_MISID]       if ( ((Concurrency *)((char *)this + 9344 * *((_DWORD *)this + 38626) + 584 * i + 79616))->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)((char *)this + 9344 * *((_DWORD *)this + 38626) + 584 * i + 79616))->Apply();
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
  ((UICaption *)&this->m_Element[10].m_btn.m_texarray.m_ptex[3])->SetEnable((int)this->buf, 0);
  sprintf(this->buf, &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)&this->m_Element[10].m_btn.m_caption[68])->SetEnable((int)this->buf, 0);
  if ( BYTE2(this->ms_BigMap.m_fontcolor.Color) )
  {
    ((MainPropUI *)this)->HandleKeyInput();
    this->i = 0;
    do
    {
      i = this->i;
// [VFTABLE] if ( *((_BYTE *)&this->ms_BigMap.__vftable + i + 1) )
      {
        v7 = *((_BYTE *)this + 9980 * i + 155468);
        v8 = (float *)((char *)this + 9980 * i);
        if ( !v7 )
        {
          sprintf(this->buf, "%d/%d", (int)v8[38866], Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 9]);
          ((UICaption *)((char *)this + 9980 * this->i + 155552))->SetEnable((int)this->buf, 0);
        }
        if ( !*((_BYTE *)this + 9980 * this->i + 156564) )
        {
          sprintf(
            this->buf,
            "%d/%d",
            (int)*((float *)this + 2495 * this->i + 39140),
            Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 10]);
          ((UICaption *)((char *)this + 9980 * this->i + 156648))->SetEnable((int)this->buf, 0);
        }
        if ( !*((_BYTE *)this + 9980 * this->i + 156016) )
        {
          sprintf(
            this->buf,
            "%d/%d",
            (int)*((float *)this + 2495 * this->i + 39003),
            Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 11]);
          ((UICaption *)((char *)this + 9980 * this->i + 156100))->SetEnable((int)this->buf, 0);
        }
      }
      v9 = this->i + 1;
      this->i = v9;
    }
    while ( v9 < 5 );
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x00497450
int UIBigMap::UpdateNPCAnimations(int nVal, int nVal2)
{
  char *v3; // esi
  int result; // eax

  v3 = (char *)this + 9980 * nVal;
  ((NPC *)(v3 + 154660))->NPC::UpdateAnim();
  ((NPC *)(v3 + 157560))->NPC::UpdateAnim();
  return result;
}

// 0x004974A0
int UIBigMap::OnMessage(int nVal, char *pszBuf, int nItemID)
{
  int i; // edi
  UIBigMap *v6; // esi
  UICursor *v7; // ecx
  int result; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  CScreenMode *Instance; // eax
  void *m_id; // eax
  void *v15; // eax
  void *v16; // eax
  _SPropValue *v17; // eax
  int v18; // eax
  int *v19; // edi
  char *v20; // ecx
  int v21; // edi
  const char *v22; // ebp
  const char *v23; // edx
  int v24; // eax
  int *v25; // edi
  char *v26; // ecx
  int v27; // edi
  int v28; // eax
  int *v29; // edi
  char *v30; // ecx
  int v31; // edi
  int v32; // eax
  int *v33; // edi
  char *v34; // ecx
  int v35; // edi
  int v36; // eax
  int *v37; // edi
  char *v38; // ecx
  int v39; // edi
  int v40; // eax
  int *v41; // edi
  char *v42; // ecx
  int v43; // edi
  char *buf; // edi
  int *v45; // eax
  int v46; // edi
  const char *v47; // ebp
  CScreenMode *v48; // eax
  const void *v49; // [esp-0x8] [ebp-0x130]
  _SPropValue *v50; // [esp-0x8] [ebp-0x130]
  int v51; // [esp+0x18] [ebp-0x110]
  char Buffer; // [esp+0x1C] [ebp-0x10C] BYREF
  _BYTE v53[252]; // [esp+0x1D] [ebp-0x10B] BYREF
  __int16 v54; // [esp+0x119] [ebp-0xF]
  char v55; // [esp+0x11B] [ebp-0xD]
  _BYTE pOut[12]; // [esp+0x11C] [ebp-0xC] BYREF

  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        for ( i = 0; i < 8; ++i )
          sub_496DD0(i);
        ((MagicUI *)this)->ProcessInput();
        ((MainPropUI *)this)->ShowPage();
        g_nSceneState = 1;
        BYTE2(this->ms_BigMap.m_fontcolor.Color) = 1;
        v6 = (UIBigMap *)((char *)this + 154496);
// [VFTABLE] v6->__vftable = 0;
        v6->m_fontcolor.Color = 0;
        ((UICursor *)v7)->IRender();
        result = 1;
      }
      else
      {
        BYTE2(this->ms_BigMap.m_fontcolor.Color) = 0;
        ((CScreenMode *)this)->ResetProgressList();
        result = 1;
      }
      break;
    case 1001:
      this->i = 0;
      do
      {
        v9 = this->i;
// [VFTABLE] if ( *((_BYTE *)&this->ms_BigMap.__vftable + v9 + 1) && pszBuf == (char *)dword_56D5F0[v9] )
        {
          *((_DWORD *)this + 53799) = this->i;
          this->ms_BigMap.m_wndcolor.Color = -1;
          ((UIListBox *)((char *)this + 217412))->GetItem();
          ((SceneMgr *)this)->FormatStatusCaption(*((_DWORD *)this + 53799));
          ((StateUI *)this)->UpdateRoleTooltip(*((_DWORD *)this + 53799));
          ((MainPropUI *)this)->ShowSubPanels(*((_DWORD *)this + 53799));
          ((MainEquipUI *)this)->UpdateTooltip(*((_DWORD *)this + 53799));
          ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), (int)this->ms_BigMap.m_id);
LABEL_32:
          v17 = (_SPropValue *)off_5C936C;
          goto LABEL_126;
        }
        v10 = v9 + 1;
        this->i = v10;
      }
      while ( v10 < 5 );
      this->i = 0;
      do
      {
        v11 = this->i;
        if ( (&off_56D5D8)[v11] == pszBuf )
        {
          ((StateUI *)this)->UpdateRoleTooltip(*((_DWORD *)this + 53799));
          ((MainPropUI *)this)->ShowSubPanels(*((_DWORD *)this + 53799));
          ((MainEquipUI *)this)->UpdateTooltip(*((_DWORD *)this + 53799));
          this->ms_BigMap.m_wndcolor.Color = -1;
          ((UIListBox *)((char *)this + 217412))->GetItem();
          ((SceneMgr *)this)->FormatStatusCaption(*((_DWORD *)this + 53799));
          ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), this->i);
LABEL_34:
          v50 = (_SPropValue *)off_5C936C;
          goto LABEL_127;
        }
        v12 = v11 + 1;
        this->i = v12;
      }
      while ( v12 < 5 );
      if ( pszBuf > byte_A00110 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00319u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            ((UIListBox *)((char *)this + 217412))->GetItem();
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), 0);
            goto LABEL_30;
          case 0xA00320u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            ((UIListBox *)((char *)this + 217412))->GetItem();
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), 2);
            goto LABEL_32;
          case 0xA00321u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            ((UIListBox *)((char *)this + 217412))->GetItem();
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), 1);
            goto LABEL_34;
          case 0xA00322u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            ((UIListBox *)((char *)this + 217412))->GetItem();
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), 3);
LABEL_30:
            v50 = (_SPropValue *)off_5C936C;
            goto LABEL_127;
          case 0xA00323u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            ((UIListBox *)((char *)this + 217412))->GetItem();
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), 4);
            goto LABEL_32;
          case 0xA00324u:
            this->ms_BigMap.m_wndcolor.Color = -1;
            ((UIListBox *)((char *)this + 217412))->GetItem();
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), 5);
            goto LABEL_34;
          case 0xA00333u:
            m_id = this->ms_BigMap.m_id;
            *((_DWORD *)this + 54918) = -1;
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), (int)m_id);
            goto LABEL_34;
          case 0xA00334u:
            v15 = this->ms_BigMap.m_id;
            *((_DWORD *)this + 54918) = 0;
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), (int)v15);
            goto LABEL_34;
          case 0xA00335u:
            v16 = this->ms_BigMap.m_id;
            *((_DWORD *)this + 54918) = 3;
            ((EquipUI *)this)->HandleInput(*((_DWORD *)this + 53799), (int)v16);
            goto LABEL_34;
          default:
            goto LABEL_128;
        }
      }
      if ( pszBuf != byte_A00110 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00102u:
          case 0xA00103u:
          case 0xA00105u:
          case 0xA00106u:
          case 0xA00107u:
          case 0xA00108u:
          case 0xA00109u:
            break;
          default:
            goto LABEL_128;
        }
      }
      v49 = off_5C936C;
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v49, 1);
      ((MainEquipUI *)this->ms_BigMap.m_rect.top)->HandleMessage();
      result = 1;
      break;
    case 1002:
      switch ( (unsigned int)pszBuf )
      {
        case 0xA00102u:
          *((_DWORD *)this + 38626) = 0;
          if ( *((_BYTE *)this + 154496) )
            goto LABEL_91;
          sub_496DD0(0);
          result = 1;
          break;
        case 0xA00103u:
          *((_DWORD *)this + 38626) = 1;
          if ( *((_BYTE *)this + 154497) )
            goto LABEL_91;
          sub_496DD0(1);
          result = 1;
          break;
        case 0xA00104u:
          *((_DWORD *)this + 38626) = 2;
          if ( *((_BYTE *)this + 154498) )
            goto LABEL_91;
          sub_496DD0(2);
          result = 1;
          break;
        case 0xA00105u:
          *((_DWORD *)this + 38626) = 3;
          if ( *((_BYTE *)this + 154499) )
            goto LABEL_91;
          sub_496DD0(3);
          result = 1;
          break;
        case 0xA00106u:
          *((_DWORD *)this + 38626) = 5;
          if ( *((_BYTE *)this + 154501) )
            goto LABEL_91;
          sub_496DD0(5);
          result = 1;
          break;
        case 0xA00107u:
          *((_DWORD *)this + 38626) = 6;
          if ( *((_BYTE *)this + 154502) )
            goto LABEL_91;
          sub_496DD0(6);
          result = 1;
          break;
        case 0xA00108u:
          *((_DWORD *)this + 38626) = 4;
          if ( *((_BYTE *)this + 154500) )
            goto LABEL_91;
          sub_496DD0(4);
          result = 1;
          break;
        case 0xA00109u:
          *((_DWORD *)this + 38626) = 7;
          if ( !*((_BYTE *)this + 154503) )
            sub_496DD0(7);
          goto LABEL_91;
        default:
LABEL_91:
          result = 1;
          break;
      }
      break;
    case 1003:
      switch ( (unsigned int)pszBuf )
      {
        case 0xA00102u:
          *((_DWORD *)this + 38626) = 0;
          *((_BYTE *)this + 154496) = 0;
          result = 1;
          break;
        case 0xA00103u:
          *((_DWORD *)this + 38626) = 1;
          *((_BYTE *)this + 154497) = 0;
          result = 1;
          break;
        case 0xA00104u:
          *((_DWORD *)this + 38626) = 2;
          *((_BYTE *)this + 154498) = 0;
          result = 1;
          break;
        case 0xA00105u:
          *((_DWORD *)this + 38626) = 3;
          *((_BYTE *)this + 154499) = 0;
          result = 1;
          break;
        case 0xA00106u:
          *((_DWORD *)this + 38626) = 5;
          *((_BYTE *)this + 154501) = 0;
          result = 1;
          break;
        case 0xA00107u:
          *((_DWORD *)this + 38626) = 6;
          *((_BYTE *)this + 154502) = 0;
          result = 1;
          break;
        case 0xA00108u:
          *((_DWORD *)this + 38626) = 4;
          *((_BYTE *)this + 154500) = 0;
          result = 1;
          break;
        case 0xA00109u:
          *((_DWORD *)this + 38626) = 7;
          *((_BYTE *)this + 154503) = 0;
          goto LABEL_101;
        default:
LABEL_101:
          result = 1;
          break;
      }
      break;
    case 1007:
      this->ms_BigMap.m_wndcolor.Color = nItemID;
      if ( nItemID >= 0 )
      {
        if ( (unsigned __int8)sub_4947E0(nItemID, *((_DWORD *)this + 53799), 0) )
          ((UIScene *)this)->LoadRoleSkillData(*((_DWORD *)this + 53799));
        else
          ((SceneMgr *)this)->FormatStatusCaption(*((_DWORD *)this + 53799));
        v45 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, this->ms_BigMap.m_wndcolor.Color);
        v46 = v45[2];
        v51 = v46;
        ((EquipUI *)this)->UpdateSlot(*v45, v45[1], v46);
        if ( *(_BYTE *)(v46 + 613) == 5 )
        {
          ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(228.0);
          ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 270, 600);
        }
        else if ( *(_BYTE *)(v46 + 612) == 11 )
        {
          ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(228.0);
          ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 262, 600);
        }
        else if ( *(_DWORD *)v46 == 8114 || *(_DWORD *)v46 == 8132 )
        {
          ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(180.0);
          ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 242, 600);
        }
        else
        {
          ((CCBFiveNimbusWindow *)((char *)this + 219676))->SetFloatParam(180.0);
          ((Camera *)((char *)this + 219676))->UpdateCameraLookAt(128, 258, 600);
        }
        v47 = (const char *)(v46 + 36);
        if ( !strcmp((const char *)(v46 + 36), g_szSceneUIText) )
          sprintf(this->buf, byte_5967B0, "NONE");
        else
          sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v51 + 36), (const char *)(v51 + 36));
        ((PalScript *)((char *)this + 219748))->LoadModel(this->buf, 0);
        if ( !strcmp((const char *)(v51 + 36), g_szSceneUIText) )
        {
          sprintf(this->buf, byte_5967B0, "NONE");
        }
        else
        {
          Buffer = 0;
          memset(v53, 0, sizeof(v53));
          v54 = 0;
          v55 = 0;
          sprintf(&Buffer, "%s%s", v47, (const char *)(v51 + 66));
          sprintf(this->buf, "Item\\%s\\%s.tga", v47, &Buffer);
        }
        ((gbGeomNode *)*((gbGeomNode **)this + 54941))->ReplaceTexture(this->buf);
        *((_DWORD *)this + 54938) = 1;
      }
      result = 1;
      break;
    case 1008:
      this->ms_BigMap.m_wndcolor.Color = nItemID;
      if ( nItemID < 0 )
        goto LABEL_129;
      if ( !(unsigned __int8)sub_4947E0(nItemID, *((_DWORD *)this + 53799), 1) )
      {
        v17 = off_5C9378;
LABEL_126:
        v50 = v17;
LABEL_127:
        v48 = CScreenMode::GetInstance();
        ((CScreenMode *)v48)->AudioSetPosition(v50, 1);
        goto LABEL_128;
      }
      sub_494880(this, *((_DWORD *)this + 53799));
      result = 1;
      break;
    case 1009:
      goto LABEL_128;
    case 1021:
      switch ( (unsigned int)pszBuf )
      {
        case 0xA00319u:
          v18 = *((_DWORD *)this + 53799);
          v19 = (int *)&::Buffer.m_partyActor.m_dwMatMsg[352 * v18 + 6];
          v20 = (char *)v19[2];
          if ( v20 )
          {
            ((StateUI *)this)->UpdateAttributeDisplay(v18, v20, 0.0);
            ((EquipUI *)this)->UpdateSlot(*v19, v19[1], v19[2]);
            if ( !strcmp((const char *)(v19[2] + 36), g_szSceneUIText) )
              sprintf(this->buf, byte_5967B0, "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v19[2] + 36), (const char *)(v19[2] + 36));
            ((PalScript *)((char *)this + 219748))->LoadModel(this->buf, 0);
            v21 = v19[2];
            v22 = (const char *)(v21 + 36);
            v23 = (const char *)(v21 + 66);
            if ( !strcmp((const char *)(v21 + 36), g_szSceneUIText) )
              goto LABEL_71;
            goto LABEL_72;
          }
          break;
        case 0xA00320u:
          v24 = *((_DWORD *)this + 53799);
          v25 = (int *)(&::Buffer.m_partyActor.m_nAnimFrame + 704 * v24 + 2);
          v26 = (char *)v25[2];
          if ( v26 )
          {
            ((StateUI *)this)->UpdateAttributeDisplay(v24, v26, 2.0f);
            ((EquipUI *)this)->UpdateSlot(*v25, v25[1], v25[2]);
            if ( !strcmp((const char *)(v25[2] + 36), g_szSceneUIText) )
              sprintf(this->buf, byte_5967B0, "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v25[2] + 36), (const char *)(v25[2] + 36));
            ((PalScript *)((char *)this + 219748))->LoadModel(this->buf, 0);
            v27 = v25[2];
            v22 = (const char *)(v27 + 36);
            v23 = (const char *)(v27 + 66);
            if ( !strcmp((const char *)(v27 + 36), g_szSceneUIText) )
              goto LABEL_71;
            goto LABEL_72;
          }
          break;
        case 0xA00321u:
          v28 = *((_DWORD *)this + 53799);
          v29 = (int *)(&::Buffer.m_partyActor.m_pParticleData + 352 * v28 + 1);
          v30 = (char *)v29[2];
          if ( v30 )
          {
            ((StateUI *)this)->UpdateAttributeDisplay(v28, v30, 1.0f);
            ((EquipUI *)this)->UpdateSlot(*v29, v29[1], v29[2]);
            if ( !strcmp((const char *)(v29[2] + 36), g_szSceneUIText) )
              sprintf(this->buf, byte_5967B0, "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v29[2] + 36), (const char *)(v29[2] + 36));
            ((PalScript *)((char *)this + 219748))->LoadModel(this->buf, 0);
            v31 = v29[2];
            v22 = (const char *)(v31 + 36);
            v23 = (const char *)(v31 + 66);
            if ( !strcmp((const char *)(v31 + 36), g_szSceneUIText) )
              goto LABEL_71;
            goto LABEL_72;
          }
          break;
        case 0xA00322u:
          v32 = *((_DWORD *)this + 53799);
          v33 = (int *)(&::Buffer.m_partyActor.m_pParticleData + 352 * v32 + 4);
          v34 = (char *)v33[2];
          if ( v34 )
          {
            ((StateUI *)this)->UpdateAttributeDisplay(v32, v34, 3.0f);
            ((EquipUI *)this)->UpdateSlot(*v33, v33[1], v33[2]);
            if ( !strcmp((const char *)(v33[2] + 36), g_szSceneUIText) )
              sprintf(this->buf, byte_5967B0, "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v33[2] + 36), (const char *)(v33[2] + 36));
            ((PalScript *)((char *)this + 219748))->LoadModel(this->buf, 0);
            v35 = v33[2];
            v22 = (const char *)(v35 + 36);
            v23 = (const char *)(v35 + 66);
            if ( !strcmp((const char *)(v35 + 36), g_szSceneUIText) )
              goto LABEL_71;
            goto LABEL_72;
          }
          break;
        case 0xA00323u:
          v36 = *((_DWORD *)this + 53799);
          v37 = (int *)&::Buffer.m_partyActor.m_dwMatMsg[352 * v36];
          v38 = (char *)v37[2];
          if ( v38 )
          {
            ((StateUI *)this)->UpdateAttributeDisplay(v36, v38, 4.0f);
            ((EquipUI *)this)->UpdateSlot(*v37, v37[1], v37[2]);
            if ( !strcmp((const char *)(v37[2] + 36), g_szSceneUIText) )
              sprintf(this->buf, byte_5967B0, "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v37[2] + 36), (const char *)(v37[2] + 36));
            ((PalScript *)((char *)this + 219748))->LoadModel(this->buf, 0);
            v39 = v37[2];
            v22 = (const char *)(v39 + 36);
            v23 = (const char *)(v39 + 66);
            if ( !strcmp((const char *)(v39 + 36), g_szSceneUIText) )
              goto LABEL_71;
            goto LABEL_72;
          }
          break;
        case 0xA00324u:
          v40 = *((_DWORD *)this + 53799);
          v41 = (int *)&::Buffer.m_partyActor.m_dwMatMsg[352 * v40 + 3];
          v42 = (char *)v41[2];
          if ( v42 )
          {
            ((StateUI *)this)->UpdateAttributeDisplay(v40, v42, 5.0f);
            ((EquipUI *)this)->UpdateSlot(*v41, v41[1], v41[2]);
            if ( !strcmp((const char *)(v41[2] + 36), g_szSceneUIText) )
              sprintf(this->buf, byte_5967B0, "NONE");
            else
              sprintf(this->buf, "Item\\%s\\%s.pol", (const char *)(v41[2] + 36), (const char *)(v41[2] + 36));
            ((PalScript *)((char *)this + 219748))->LoadModel(this->buf, 0);
            v43 = v41[2];
            v22 = (const char *)(v43 + 36);
            v23 = (const char *)(v43 + 66);
            if ( !strcmp((const char *)(v43 + 36), g_szSceneUIText) )
            {
LABEL_71:
              buf = this->buf;
              sprintf(this->buf, byte_5967B0, "NONE");
            }
            else
            {
LABEL_72:
              Buffer = 0;
              memset(v53, 0, sizeof(v53));
              v54 = 0;
              v55 = 0;
              sprintf(&Buffer, "%s%s", v22, v23);
              buf = this->buf;
              sprintf(this->buf, "Item\\%s\\%s.tga", v22, &Buffer);
            }
            ((gbGeomNode *)*((gbGeomNode **)this + 54941))->ReplaceTexture(buf);
            *((_DWORD *)this + 54938) = 1;
            v50 = (_SPropValue *)off_5C936C;
            goto LABEL_127;
          }
          break;
        default:
          break;
      }
LABEL_128:
      result = 1;
      break;
    default:
LABEL_129:
      result = ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nItemID);
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

  p_m_fontcolor = &this->m_Element[4].m_btn.m_fontcolor;
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
  (**(void ( ***)(char *, _DWORD))&this->m_Element[1].m_btn.m_caption[44])(
    &this->m_Element[1].m_btn.m_caption[44],
    0);
  (*(void ( **)(LONG *, _DWORD))this->m_Element[2].m_screenPt.y)(&this->m_Element[2].m_screenPt.y, 0);
  this->m_Element[2].m_btn.m_texarray.m_ptex[14] = 0;
  this->m_Element[2].m_btn.m_texarray.m_ptex[15] = 0;
  LOBYTE(this->m_Element[2].m_btn.m_texarrayInfo[1]) = 0;
  p_m_offsetx = &this->m_Element[5].m_btn.m_offsetx;
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
  p_m_disablepicInfo = &this->m_Element[2].m_btn.m_disablepicInfo;
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
  this->m_pbktex = (gbTexture *)msg;
  this->m_bvisible = wparam;
  this->screenrect.left = wparam;
  this->m_benable = lparam;
  this->screenrect.top = lparam;
  return ((UIScene *)this)->CalcViewTransform(1);
}

// 0x00539810
void UIBigMap::SetElementVisible(FILE *Buffer, FILE *Stream)
{
  int v4; // ecx
  char *v5; // esi
  int i; // edi
  char *v7; // esi
  int v8; // ecx
  int j; // edi
  int v10; // [esp+0x18] [ebp-0x2A4] BYREF
  int Buffera; // [esp+0x1C] [ebp-0x2A0] BYREF
  __int16 p_WORD2; // [esp+0x22] [ebp-0x29A] BYREF
  UIBigMap *v13; // [esp+0x24] [ebp-0x298]
  int v14; // [esp+0x28] [ebp-0x294]
  char pszBuf2[40]; // [esp+0x2C] [ebp-0x290] BYREF
  int v16; // [esp+0x54] [ebp-0x268]
  int v17; // [esp+0x58] [ebp-0x264]
  int v18; // [esp+0x5C] [ebp-0x260]
  int base[57]; // [esp+B4h] [ebp-0x208] BYREF
  gbAABBox v20[10]; // [esp+0x198] [ebp-0x124] BYREF
  gbVec3D v21; // [esp+0x29C] [ebp-0x20] BYREF
  gbVec3D v22; // [esp+0x2A8] [ebp-0x14] BYREF
if ( Buffer )
  {
    fread(this, 0x84u, 1u, Buffer);
    Buffera = 0;
    fread(&Buffera, 4u, 1u, Buffer);
    v4 = *(_DWORD *)&this->buf[32];
    v5 = &this->buf[28];
    v14 = *((_DWORD *)v5 + 2);
    *((_DWORD *)v5 + 2) = v4;
    v16 = 0;
    v17 = 0;
    v18 = 0;
    for ( i = 0; i < Buffera; ++i )
    {
      fread(pszBuf2, 0x290u, 1u, Buffer);
      ActVec_Insert_char((Actor *)v5, *((char **)v5 + 2), 1u, pszBuf2);
    }
    v7 = &this->buf[44];
    v8 = *(_DWORD *)&this->buf[48];
    v14 = *(_DWORD *)&this->buf[52];
    *(_DWORD *)&this->buf[52] = v8;
    v10 = 0;
    fread(&v10, 4u, 1u, Buffer);
    for ( j = 0; j < v10; ++j )
    {
      fread(&p_WORD2, 2u, 1u, Buffer);
      ActVec_Insert_word((Actor *)v7, *((_WORD **)v7 + 2), 1u, &p_WORD2);
    }
  }
}
