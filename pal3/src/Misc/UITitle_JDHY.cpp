#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_JDHY.h"

// Forward declarations for unnamed functions
void * GetSaveDataManager(void); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
int sub_4B43E0(_DWORD *_this, int a2); // from annotations

BOOL ReadRegistryString(const char *szSubKey, const char *szValueName, char *szOutBuf); // from annotations

// Unnamed globals (extern)
extern char byte_A00110;
extern char byte_A00700;
extern char byte_A00701;
extern char byte_A00702;
extern char byte_A00703;
extern char byte_A00704;
extern char byte_A00705;
extern char byte_A00708;
extern char byte_A00709;
extern char byte_ABC00B;
extern CHAR byte_DC6A3C[256];
extern int dword_A00710;
extern int dword_D8BBEC;
extern int dword_DC633C;
extern int dword_DC643C;
extern int dword_DD383C;
extern int dword_DD4E3C;
extern int dword_DD4F3C;
extern int dword_DD513C;
extern int dword_DD523C;
extern int dword_DD8A3C;
extern int dword_DD933C;
extern int dword_DDB73C;
extern int dword_DDB83C;
extern int dword_DDC13C;
extern void * off_5D11B8;
extern void * off_5D11C0;
extern void * off_5D11C4;
extern void * off_5D11E0;
extern void * off_5D11F8;
extern void * off_5D11FC;
extern RoleSystem stru_C059A0;

// 0x0045E9F0
void UITitle_JDHY::LayoutCalcRects()
{
  void *m_id; // eax
  void **v3; // eax
  void **v4; // edx
  void **v5; // eax
  void **v6; // edx
  void **v7; // eax
  void **v8; // ecx
  void **v9; // eax
  void **v10; // edx
  void **v11; // eax
  void **v12; // edx
  void **v13; // eax
  void **v14; // edx
  void **v15; // eax
  void **v16; // edx
  void **v17; // eax
  void **v18; // edx
  void **v19; // eax
  void **v20; // edx
  void **v21; // eax
  void **v22; // edx
  void **v23; // eax
  void **v24; // edx
  void **v25; // eax
  void **v26; // edx
  void **v27; // eax
  void **v28; // edx
  void **v29; // eax
  void **v30; // edx
  void **v31; // eax
  void **v32; // edx
  void **v33; // eax
  void **v34; // edx
  void **v35; // eax
  void **v36; // edx
  void **v37; // eax
  void **v38; // edx
  void **v39; // eax
  void **v40; // edx
  void **v41; // eax
  void **v42; // edx
  void **v43; // eax
  void **v44; // edx
  void **v45; // eax
  void **v46; // edx
  void **v47; // eax
  void **v48; // edx
  void **v49; // eax
  void **v50; // edx
  int v51; // edx
  int v52; // ecx
  int v53; // edx
  int v54; // ecx
  int v55; // edx
  int v56; // ecx
  int v57; // edx
  int v58; // ecx
  int v59; // edx
  int v60; // ecx
  int v61; // edx
  int v62; // ecx
  int v63; // edx
  int v64; // ecx
  int v65; // edx
  int v66; // ecx
  LONG v67; // eax
  int v68; // edx
  int v69; // ecx
  int v70; // edx
  int v71; // ecx
  int v72; // edx
  int v73; // ecx
  int v74; // edx
  int v75; // ecx
  int v76; // edx
  int v77; // ecx
  int v78; // edx
  int v79; // ecx
  int v80; // edx
  int v81; // ecx
  int v82; // edx
  int v83; // ecx
  LONG v84; // eax
  int v85; // eax

  this->m_OutFrameT.m_id = 0;
  do
  {
    m_id = this->m_OutFrameT.m_id;
    if ( *((_BYTE *)&this->m_NoteItem[6].m_NotePic.m_FVF + (_DWORD)m_id) )
    {
      sub_445FA0(&this->m_NoteItem[23].m_ItemRc.bottom + 270 * (_DWORD)m_id);
      sub_445FA0(&this->m_NoteItem[23].m_NoteItemBk.m_texarrayInfo[270 * (int)this->m_OutFrameT.m_id + 3]);
      sub_445FA0(&this->m_NoteItem[23].m_NoteID.m_id + 270 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[23].m_NoteState.m_childs.capacity + 270 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[23].m_HeadShot_NO_SEL[0].pDebugTex + 270 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[23].m_HeadShot_NO_SEL[1].m_text[1080 * (int)this->m_OutFrameT.m_id]);
      sub_445FA0(&this->m_NoteItem[24].m_HeadShot[6 * (int)this->m_OutFrameT.m_id + 2].m_ppicInfo);
      sub_445FA0(&this->m_NoteItem[24].m_NoteTime.m_pbkInfo + 228 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[24].m_NoteMoney.m_pbkInfo + 228 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[24].m_HeadShot[6 * (int)this->m_OutFrameT.m_id + 3].m_ppicInfo);
      sub_445FA0(&this->m_NoteItem[24].m_HeadShot[6 * (int)this->m_OutFrameT.m_id + 4].m_ppicInfo);
      sub_445FA0(&this->m_NoteItem[24].m_NoteLv[6 * (int)this->m_OutFrameT.m_id].m_pbkInfo);
// [VFTABLE] *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].pDebugTex + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->__vftable + 4 * ((int)this->m_OutFrameT.m_id + 1641)) + 12;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_bfocus + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * (int)this->m_OutFrameT.m_id)
                                                                                                 - 30;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_align + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_bfocus
                                                                                                  + 192 * (int)this->m_OutFrameT.m_id)
                                                                                                + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ratiow + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].pDebugTex + 192 * (int)this->m_OutFrameT.m_id) + 38;
      sub_445FA0(&this->m_NoteItem[6].m_NotePicName + 48 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] v3 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v4 = v3 + 15709;
      v3 += 15713;
      *v3 = *v4;
      v3[1] = v4[1];
      v3[2] = v4[2];
      v3[3] = v4[3];
      sub_445FA0((char *)&this->m_NoteItem[7] + 7296 * (int)this->m_OutFrameT.m_id);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * (int)this->m_OutFrameT.m_id + 4] = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].pDebugTex + 192 * (int)this->m_OutFrameT.m_id);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * (int)this->m_OutFrameT.m_id] = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_align + 192 * (int)this->m_OutFrameT.m_id) + 2;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * (int)this->m_OutFrameT.m_id + 8] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * (int)this->m_OutFrameT.m_id] + 26;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[768 * (int)this->m_OutFrameT.m_id + 12] = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ratiow + 192 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[7].m_NoteItemBk.m_texarray.m_ptex[1824 * (int)this->m_OutFrameT.m_id + 10]);
// [VFTABLE] v5 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v6 = v5 + 15717;
      v5 += 15721;
      *v5 = *v6;
      v5[1] = v6[1];
      v5[2] = v6[2];
      v5[3] = v6[3];
      sub_445FA0(&this->m_NoteItem[7].m_NoteItemBk.m_caption[7296 * (int)this->m_OutFrameT.m_id + 96]);
// [VFTABLE] *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_nSize + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->__vftable + 4 * ((int)this->m_OutFrameT.m_id + 1641)) + 12;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.capacity + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * (int)this->m_OutFrameT.m_id) - 30;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_needscriptdel + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.capacity + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1] + 192 * (int)this->m_OutFrameT.m_id + 13) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_nSize + 192 * (int)this->m_OutFrameT.m_id) + 38;
      sub_445FA0(this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id + 2].m_text);
// [VFTABLE] v7 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v8 = v7 + 15741;
      v7 += 15745;
      *v7 = *v8;
      v7[1] = v8[1];
      v7[2] = v8[2];
      v7[3] = v8[3];
      sub_445FA0(this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id + 3].m_text);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_ratiow + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_nSize + 192 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_align + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_childs.m_needscriptdel
                                                                                                  + 192 * (int)this->m_OutFrameT.m_id)
                                                                                                + 2;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_ratioh + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_align + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_textx + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1]
                                                                                                  + 192 * (int)this->m_OutFrameT.m_id
                                                                                                  + 13);
      sub_445FA0(this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id + 4].m_text);
// [VFTABLE] v9 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v10 = v9 + 15749;
      v9 += 15753;
      *v9 = *v10;
      v9[1] = v10[1];
      v9[2] = v10[2];
      v9[3] = v10[3];
      sub_445FA0(this->m_NoteItem[7].m_HeadShot[48 * (int)this->m_OutFrameT.m_id].m_text);
// [VFTABLE] *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.top + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->__vftable + 4 * ((int)this->m_OutFrameT.m_id + 1641)) + 12;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.left + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * (int)this->m_OutFrameT.m_id) - 30;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.right + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.left + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.bottom + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.top + 192 * (int)this->m_OutFrameT.m_id) + 38;
      sub_445FA0(&this->m_NoteItem[7].m_NoteTime.m_texty + 1824 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] v11 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v12 = v11 + 15773;
      v11 += 15777;
      *v11 = *v12;
      v11[1] = v12[1];
      v11[2] = v12[2];
      v11[3] = v12[3];
      sub_445FA0(&this->m_NoteItem[7].m_NoteMoney.m_texty + 1824 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_bcreateok + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.top + 192 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_childs.m_needscriptdel + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.right + 192 * (int)this->m_OutFrameT.m_id) + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_bvisible + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_childs.m_needscriptdel + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_benable + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_rect.bottom + 192 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[7].m_NoteLv[48 * (int)this->m_OutFrameT.m_id].m_texty);
// [VFTABLE] v13 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v14 = v13 + 15781;
      v13 += 15785;
      *v13 = *v14;
      v13[1] = v14[1];
      v13[2] = v14[2];
      v13[3] = v14[3];
      sub_445FA0(&this->m_NoteItem[7].m_NoteLv[48 * (int)this->m_OutFrameT.m_id + 1].m_texty);
// [VFTABLE] *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_nTextW + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->__vftable + 4 * ((int)this->m_OutFrameT.m_id + 1641))
                                                                                                 + 12;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_FVF + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible
                                                                                                + 4
                                                                                                * (int)this->m_OutFrameT.m_id)
                                                                                              + 4;
// [VFTABLE] *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].__vftable + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_FVF + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_fontcolor.Color + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_nTextW + 192 * (int)this->m_OutFrameT.m_id) + 38;
      sub_445FA0(&this->m_NoteItem[7].m_NotePicName.m_texty + 1824 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] v15 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v16 = v15 + 15805;
      v15 += 15809;
      *v15 = *v16;
      v15[1] = v16[1];
      v15[2] = v16[2];
      v15[3] = v16[3];
      sub_445FA0(&this->m_NoteItem[8].m_NoteItemBk.m_ratiow + 1824 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_rect.bottom + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_nTextW + 192 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_rect.right + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].__vftable + 192 * (int)this->m_OutFrameT.m_id) + 2;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_pfather + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_rect.right + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_childs.m_pData + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_fontcolor.Color + 192 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[8].m_NoteItemBk.m_caption[7296 * (int)this->m_OutFrameT.m_id + 32]);
// [VFTABLE] v17 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v18 = v17 + 15813;
      v17 += 15817;
      *v17 = *v18;
      v17[1] = v18[1];
      v17[2] = v18[2];
      v17[3] = v18[3];
      sub_445FA0(&this->m_NoteItem[8].m_NoteID.m_pfather + 1824 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppicInfo + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->__vftable + 4 * ((int)this->m_OutFrameT.m_id + 1641)) + 12;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppic + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * (int)this->m_OutFrameT.m_id) + 4;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_disablepic + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppic + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_disablepicInfo + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppicInfo + 192 * (int)this->m_OutFrameT.m_id) + 38;
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id + 3].m_pfather);
// [VFTABLE] v19 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v20 = v19 + 15837;
      v19 += 15841;
      *v19 = *v20;
      v19[1] = v20[1];
      v19[2] = v20[2];
      v19[3] = v20[3];
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id + 4].m_pfather);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_fontcolor.Color + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_ppicInfo + 192 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].__vftable + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_disablepic + 192 * (int)this->m_OutFrameT.m_id) + 2;
// [VFTABLE] *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_wndcolor.Color + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].__vftable + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_id + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_disablepicInfo + 192 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot[48 * (int)this->m_OutFrameT.m_id].m_pfather);
// [VFTABLE] v21 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v22 = v21 + 15845;
      v21 += 15849;
      *v21 = *v22;
      v21[1] = v22[1];
      v21[2] = v22[2];
      v21[3] = v22[3];
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot[48 * (int)this->m_OutFrameT.m_id + 1].m_pfather);
// [VFTABLE] *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id + 4] = *((_DWORD *)&this->__vftable + 4 * ((int)this->m_OutFrameT.m_id + 1641)) + 12;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id] = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * (int)this->m_OutFrameT.m_id) + 4;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id + 8] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id] + 26;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id + 12] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id + 4] + 38;
      sub_445FA0(&this->m_NoteItem[8].m_NoteMoney.m_rect.right + 1824 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] v23 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v24 = v23 + 15869;
      v23 += 15873;
      *v23 = *v24;
      v23[1] = v24[1];
      v23[2] = v24[2];
      v23[3] = v24[3];
      sub_445FA0(&this->m_NoteItem[8].m_NoteLv[48 * (int)this->m_OutFrameT.m_id].m_rect.right);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_disablepicInfo + 192 * (int)this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id + 4];
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_disablepic + 192 * (int)this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id + 8] + 2;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_pbk2 + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_disablepic + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_mouseoff + 192 * (int)this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_text[768 * (int)this->m_OutFrameT.m_id + 12];
      sub_445FA0(&this->m_NoteItem[8].m_NoteLv[48 * (int)this->m_OutFrameT.m_id + 1].m_rect.right);
// [VFTABLE] v25 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v26 = v25 + 15877;
      v25 += 15881;
      *v25 = *v26;
      v25[1] = v26[1];
      v25[2] = v26[2];
      v25[3] = v26[3];
      sub_445FA0(&this->m_NoteItem[8].m_NoteLv[48 * (int)this->m_OutFrameT.m_id + 2].m_rect.right);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepicInfo + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable + 4 * (int)this->m_OutFrameT.m_id) - 38;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepic + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * (int)this->m_OutFrameT.m_id) - 30;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_pbk2 + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepic + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_mouseoff + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepicInfo + 192 * (int)this->m_OutFrameT.m_id) + 38;
      sub_445FA0(&this->m_NoteItem[7].m_NoteID.m_text[7296 * (int)this->m_OutFrameT.m_id]);
// [VFTABLE] v27 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v28 = v27 + 15725;
      v27 += 15729;
      *v27 = *v28;
      v27[1] = v28[1];
      v27[2] = v28[2];
      v27[3] = v28[3];
      sub_445FA0(&this->m_NoteItem[7].m_NoteState.m_text[7296 * (int)this->m_OutFrameT.m_id]);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_id + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepicInfo + 192 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_wndcolor.Color + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_pbk2 + 192 * (int)this->m_OutFrameT.m_id) + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.left + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_wndcolor.Color + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.top + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_mouseoff + 192 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id].m_text);
// [VFTABLE] v29 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v30 = v29 + 15733;
      v29 += 15737;
      *v29 = *v30;
      v29[1] = v30[1];
      v29[2] = v30[2];
      v29[3] = v30[3];
      sub_445FA0(this->m_NoteItem[7].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id + 1].m_text);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * (int)this->m_OutFrameT.m_id + 12] = *(&this->m_NoteItem[6].m_NotePic.m_benable + 4 * (int)this->m_OutFrameT.m_id) - 38;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * (int)this->m_OutFrameT.m_id + 8] = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * (int)this->m_OutFrameT.m_id) - 30;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * (int)this->m_OutFrameT.m_id + 16] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * (int)this->m_OutFrameT.m_id + 8] + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbkInfo + 192 * (int)this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * (int)this->m_OutFrameT.m_id + 12] + 38;
      sub_445FA0(this->m_NoteItem[7].m_HeadShot[48 * (int)this->m_OutFrameT.m_id + 1].m_text);
// [VFTABLE] v31 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v32 = v31 + 15757;
      v31 += 15761;
      *v31 = *v32;
      v31[1] = v32[1];
      v31[2] = v32[2];
      v31[3] = v32[3];
      sub_445FA0(this->m_NoteItem[7].m_HeadShot[48 * (int)this->m_OutFrameT.m_id + 2].m_text);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_mouseoff + 192 * (int)this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * (int)this->m_OutFrameT.m_id + 12];
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbk2 + 192 * (int)this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_text[768 * (int)this->m_OutFrameT.m_id + 16] + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_FVF + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbk2
                                                                                                + 192
                                                                                                * (int)this->m_OutFrameT.m_id)
                                                                                              + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_nTextW + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pbkInfo + 192 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(this->m_NoteItem[7].m_HeadShot[48 * (int)this->m_OutFrameT.m_id + 3].m_text);
// [VFTABLE] v33 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v34 = v33 + 15765;
      v33 += 15769;
      *v33 = *v34;
      v33[1] = v34[1];
      v33[2] = v34[2];
      v33[3] = v34[3];
      sub_445FA0(this->m_NoteItem[7].m_HeadShot[48 * (int)this->m_OutFrameT.m_id + 4].m_text);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_textx + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable
                                                                                                  + 4 * (int)this->m_OutFrameT.m_id)
                                                                                                - 38;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ratioh + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_childs.m_needscriptdel + 4 * (int)this->m_OutFrameT.m_id) - 30;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_texty + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ratioh
                                                                                                  + 192 * (int)this->m_OutFrameT.m_id)
                                                                                                + 26;
      (&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_fonttype)[192 * (int)this->m_OutFrameT.m_id] = (Parent_Data *)(*(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_textx + 192 * (int)this->m_OutFrameT.m_id) + 38);
      sub_445FA0(&this->m_NoteItem[7].m_NoteLv[48 * (int)this->m_OutFrameT.m_id + 2].m_texty);
// [VFTABLE] v35 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v36 = v35 + 15789;
      v35 += 15793;
      *v35 = *v36;
      v35[1] = v36[1];
      v35[2] = v36[2];
      v35[3] = v36[3];
      sub_445FA0(&this->m_NoteItem[7].m_NoteLv[48 * (int)this->m_OutFrameT.m_id + 3].m_texty);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_pbkInfo + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_textx + 192 * (int)this->m_OutFrameT.m_id);
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_text[768 * (int)this->m_OutFrameT.m_id + 16] = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_texty + 192 * (int)this->m_OutFrameT.m_id) + 2;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ppic + 192 * (int)this->m_OutFrameT.m_id) = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_text[768 * (int)this->m_OutFrameT.m_id + 16] + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_ppicInfo + 192 * (int)this->m_OutFrameT.m_id) = (&this->m_NoteItem[17].m_HeadShot_NO_SEL[2].m_fonttype)[192 * (int)this->m_OutFrameT.m_id];
      sub_445FA0(&this->m_NoteItem[7].m_NoteLv[48 * (int)this->m_OutFrameT.m_id + 4].m_texty);
// [VFTABLE] v37 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v38 = v37 + 15797;
      v37 += 15801;
      *v37 = *v38;
      v37[1] = v38[1];
      v37[2] = v38[2];
      v37[3] = v38[3];
      sub_445FA0(&this->m_NoteItem[7].m_NotePic.m_texty + 1824 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_benable + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable + 4 * (int)this->m_OutFrameT.m_id) - 38;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bvisible + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * (int)this->m_OutFrameT.m_id) + 4;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bfocus + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bvisible + 192 * (int)this->m_OutFrameT.m_id)
                                                                                                 + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].pDebugTex + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_benable + 192 * (int)this->m_OutFrameT.m_id) + 38;
      sub_445FA0(&this->m_NoteItem[8].m_NoteState.m_pfather + 1824 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] v39 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v40 = v39 + 15821;
      v39 += 15825;
      *v39 = *v40;
      v39[1] = v40[1];
      v39[2] = v40[2];
      v39[3] = v40[3];
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id].m_pfather);
      (&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_fonttype)[192 * (int)this->m_OutFrameT.m_id] = (Parent_Data *)*(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_benable + 192 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_texty + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_bfocus
                                                                                                  + 192 * (int)this->m_OutFrameT.m_id)
                                                                                                + 2;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_text[768 * (int)this->m_OutFrameT.m_id] = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_texty + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].m_text[768 * (int)this->m_OutFrameT.m_id + 4] = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[3].pDebugTex + 192 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id + 1].m_pfather);
// [VFTABLE] v41 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v42 = v41 + 15829;
      v41 += 15833;
      *v41 = *v42;
      v41[1] = v42[1];
      v41[2] = v42[2];
      v41[3] = v42[3];
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot_NO_SEL[48 * (int)this->m_OutFrameT.m_id + 2].m_pfather);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_pData + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable + 4 * (int)this->m_OutFrameT.m_id) - 38;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_pfather + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * (int)this->m_OutFrameT.m_id) + 4;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.capacity + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_pfather + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_nSize + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_pData + 192 * (int)this->m_OutFrameT.m_id) + 38;
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot[48 * (int)this->m_OutFrameT.m_id + 2].m_pfather);
// [VFTABLE] v43 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v44 = v43 + 15853;
      v43 += 15857;
      *v43 = *v44;
      v43[1] = v44[1];
      v43[2] = v44[2];
      v43[3] = v44[3];
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot[48 * (int)this->m_OutFrameT.m_id + 3].m_pfather);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].pDebugTex + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_pData + 192 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_bfocus + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.capacity + 192 * (int)this->m_OutFrameT.m_id)
                                                                                                 + 2;
      *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_align + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_bfocus
                                                                                                  + 192 * (int)this->m_OutFrameT.m_id)
                                                                                                + 26;
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_ratiow + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot_NO_SEL[4].m_childs.m_nSize + 192 * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[8].m_HeadShot[48 * (int)this->m_OutFrameT.m_id + 4].m_pfather);
// [VFTABLE] v45 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v46 = v45 + 15861;
      v45 += 15865;
      *v45 = *v46;
      v45[1] = v46[1];
      v45[2] = v46[2];
      v45[3] = v46[3];
      sub_445FA0(&this->m_NoteItem[8].m_NoteTime.m_rect.right + 1824 * (int)this->m_OutFrameT.m_id);
      *((_DWORD *)&this->m_NoteItem[17].m_HeadShot[0].m_id + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_benable
                                                                                                  + 4 * (int)this->m_OutFrameT.m_id)
                                                                                                - 38;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_wndcolor.Color + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[6].m_NotePic.m_bvisible + 4 * (int)this->m_OutFrameT.m_id) + 4;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_rect.left + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_wndcolor.Color
                                                                                               + 192
                                                                                               * (int)this->m_OutFrameT.m_id)
                                                                                             + 26;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_rect.top + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot[0].m_id
                                                                                              + 192
                                                                                              * (int)this->m_OutFrameT.m_id)
                                                                                            + 38;
      sub_445FA0(&this->m_NoteItem[8].m_NoteLv[48 * (int)this->m_OutFrameT.m_id + 3].m_rect.right);
// [VFTABLE] v47 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v48 = v47 + 15885;
      v47 += 15889;
      *v47 = *v48;
      v47[1] = v48[1];
      v47[2] = v48[2];
      v47[3] = v48[3];
      sub_445FA0(&this->m_NoteItem[8].m_NoteLv[48 * (int)this->m_OutFrameT.m_id + 4].m_rect.right);
      *(&this->m_NoteItem[17].m_HeadShot[0].m_childs.m_nSize + 192 * (int)this->m_OutFrameT.m_id) = *((_DWORD *)&this->m_NoteItem[17].m_HeadShot[0].m_id + 192 * (int)this->m_OutFrameT.m_id);
      *(&this->m_NoteItem[17].m_HeadShot[0].m_childs.capacity + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_rect.left + 192 * (int)this->m_OutFrameT.m_id) + 2;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_childs.m_needscriptdel + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_childs.capacity + 192 * (int)this->m_OutFrameT.m_id) + 26;
      *(&this->m_NoteItem[17].m_HeadShot[0].m_bcreateok + 192 * (int)this->m_OutFrameT.m_id) = *(&this->m_NoteItem[17].m_HeadShot[0].m_rect.top
                                                                                               + 192
                                                                                               * (int)this->m_OutFrameT.m_id);
      sub_445FA0(&this->m_NoteItem[8].m_NotePic.m_rect.right + 1824 * (int)this->m_OutFrameT.m_id);
// [VFTABLE] v49 = &this->__vftable + 192 * (int)this->m_OutFrameT.m_id;
      v50 = v49 + 15893;
      v49 += 15897;
      *v49 = *v50;
      v49[1] = v50[1];
      v49[2] = v50[2];
      v49[3] = v50[3];
      sub_445FA0(&this->m_NoteItem[8].m_NotePicName.m_rect.right + 1824 * (int)this->m_OutFrameT.m_id);
      this->m_OutFrameT.m_rect.left = 0;
      do
      {
        v51 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_align + v51) = (int)&(*(gbTexture **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].pDebugTex + v51))[-1].InFmt.b_shift;
        v52 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].pDebugTex + v52) = *(gbTexture **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_bfocus + v52);
        v53 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ratiow + v53) = *(int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_align + v53);
        v54 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ratioh + v54) = *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_align + v54)
                                                                                + 38;
        v55 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_texty + v55) = *(int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_textx + v55)
                                                                                       - 12;
        v56 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_textx + v56) = *(_DWORD *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ratioh + v56);
        v57 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(Parent_Data **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_fonttype + v57) = *(Parent_Data **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_texty + v57);
        v58 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v58] = *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_texty
                                                                                       + v58)
                                                                   + 38;
        v59 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v59 + 8] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[v59 + 4]
                                                                       - 12;
        v60 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v60 + 4] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[v60];
        v61 = this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[128 * v61 + 12] = *(_DWORD *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[128 * v61 + 8];
        v62 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v62 + 16] = *(_DWORD *)&this->m_NoteItem[18].m_HeadShot[0].m_text[v62 + 8]
                                                                        + 38;
        v63 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ppic + v63) = (gbTexture *)&(*(_PlugInfo **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_pbkInfo + v63))[-1]._tex_uvRB.v;
        v64 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_PlugInfo **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_pbkInfo + v64) = *(_PlugInfo **)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_text[v64 + 16];
        v65 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_PlugInfo **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ppicInfo + v65) = *(_PlugInfo **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_ppic + v65);
        v66 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_disablepic + v66) = (gbTexture *)(&(*(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_ppic + v66))->InFmt.Type + 2);
        v67 = this->m_OutFrameT.m_rect.left + 1;
        this->m_OutFrameT.m_rect.left = v67;
      }
      while ( v67 < 6 );
      this->m_OutFrameT.m_rect.left = 0;
      do
      {
        v68 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_pbk2 + v68) = (gbTexture *)&(*(_PlugInfo **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepicInfo + v68))[-1]._tex_uvRB.v;
        v69 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_PlugInfo **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_disablepicInfo + v69) = *(_PlugInfo **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_disablepic + v69);
        v70 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(_DWORD *)(&this->m_NoteItem[18].m_HeadShot[0].m_mouseoff + v70) = *(gbTexture **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_pbk2
                                                                                          + v70);
        v71 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_FVF + v71) = (int)(&(*(gbTexture **)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_pbk2 + v71))->InFmt.Type + 2);
        v72 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
// [VFTABLE] *(vtbl_0056AE2C **)((char *)&this->m_NoteItem[18].m_HeadShot[1].__vftable + v72) = (vtbl_0056AE2C *)(*(int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_nTextW + v72) - 12);
        v73 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[0].m_nTextW + v73) = *(int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[0].m_FVF + v73);
        v74 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
// [VFTABLE] *(unsigned int *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_fontcolor.Color + v74) = *(unsigned int *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].__vftable + v74);
        v75 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
// [VFTABLE] *(unsigned int *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_wndcolor.Color + v75) = (unsigned int)&(*(vtbl_0056AE2C **)((char *)&this->m_NoteItem[18].m_HeadShot[1].__vftable + v75))[1].Update_2ff0 + 2;
        v76 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.left + v76) = *(LONG *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_id
                                                                                           + v76)
                                                                                 - 12;
        v77 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(void **)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_id + v77) = *(void **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_wndcolor.Color
                                                                                      + v77);
        v78 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.top + v78) = *(LONG *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.left
                                                                                          + v78);
        v79 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.right + v79) = *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.left
                                                                                            + v79)
                                                                                  + 38;
        v80 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(UIWnd **)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_pfather + v80) = (UIWnd *)(*(LONG *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.bottom + v80)
                                                                                           - 12);
        v81 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(LONG *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_rect.bottom + v81) = *(LONG *)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_rect.right
                                                                                             + v81);
        v82 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(char **)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_childs.m_pData + v82) = *(char **)((char *)&this->m_NoteItem[17].m_HeadShot_NO_SEL[1].m_pfather
                                                                                                  + v82);
        v83 = (this->m_OutFrameT.m_rect.left + 6 * (int)this->m_OutFrameT.m_id) << 7;
        *(int *)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_childs.capacity + v83) = (int)&(*(UIWnd **)((char *)&this->m_NoteItem[18].m_HeadShot[1].m_pfather + v83))->m_childs.m_pData
                                                                                                 + 2;
        v84 = this->m_OutFrameT.m_rect.left + 1;
        this->m_OutFrameT.m_rect.left = v84;
      }
      while ( v84 < 6 );
    }
    v85 = (int)this->m_OutFrameT.m_id + 1;
    this->m_OutFrameT.m_id = (void *)v85;
  }
  while ( v85 < 5 );
}

// 0x0047C1C0
int UITitle_JDHY::HandleDeviceLostA()
{
  PAL3 *Instance_db10; // eax
  PAL3 *v3; // ecx
  float m_snaph; // ecx
  int v5; // eax
  PAL3 *v6; // eax
  int result; // eax
  PAL3 *v8; // ecx
  unsigned __int8 v9; // bl
  PAL3 *v10; // ecx
  PAL3 *v11; // eax
  PAL3 *v12; // ecx
  PAL3 *v13; // eax

  Instance_db10 = ((PAL3 *)this)->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->OnDeviceLost(1);
  m_snaph = ((PAL3 *)v3)->GetInstance_db10()->m_snaph;
  v5 = 1061158912;
  if ( m_snaph != 0.0 )
    v5 = 1065353216;
  this->m_NoteItem[0].m_NoteMoney.m_bfocus = v5;
  this->m_NoteItem[0].m_NoteMoney.m_benable = v5;
  v6 = ((PAL3 *)LODWORD(m_snaph))->GetInstance_db10();
  LOBYTE(result) = ((RenderTarget *)v6)->OnResetDevice(1);
  if ( (_BYTE)result )
  {
    v9 = g_bGameFlag2;
    g_bGameFlag2 = 0;
    ((PAL3 *)v8)->Render();
    g_bGameFlag2 = v9;
    v11 = ((PAL3 *)v10)->GetInstance_db10();
    ((RenderTarget *)v11)->RenderToScreen();
    this->m_NoteItem[0].m_NoteMoney.m_bvisible = 0;
    v13 = ((PAL3 *)v12)->GetInstance_db10();
    result = (int)((RenderTarget *)v13)->GetActiveTexture();
    if ( result )
    {
      if ( *(_DWORD *)(result + 84) )
        this->m_NoteItem[0].m_NoteMoney.m_bvisible = result;
    }
  }
  else
  {
    this->m_NoteItem[0].m_NoteMoney.m_bvisible = 0;
  }
  return result;
}

// 0x004B01D0
int UITitle_JDHY::DestroyPages()
{
  *(_DWORD *)this->buf = 800;
  *(_DWORD *)&this->buf[4] = 600;
  LOBYTE(this->m_OutFrameT.m_rect.left) = 0;
  this->m_OutFrameT.m_rect.top = 0;
  sub_4422E0(&this->m_OutFrameT.m_rect.right);
  sub_4422E0(&this->m_OutFrameR.m_rect);
  sub_4422E0(&this->m_OutFrameL.m_wndcolor);
  sub_4422E0(&this->m_OutFrameB);
  sub_4422E0(&this->m_OutFrameB + 1);
  sub_4422E0(&this->m_background.m_FVF);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0(&this->m_NoteItem[0].m_NoteLv[1].m_mouseoff);
  sub_4422E0(&this->m_NoteItem[0].m_NoteLv[3].m_fontcolor);
  sub_4422E0(&this->m_NoteItem[0].m_NoteLv[4].m_fontcolor);
  sub_4422E0(&this->m_NoteItem[42].m_NotePic.m_disablepic);
  sub_4422E0(&this->m_NoteItem[42].m_NotePicName.m_disablepic);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  ((UIScene *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->ctor();
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->ctor();
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->ctor();
  sub_4422E0(&this->m_NoteItem[79].m_NoteLv[4].m_pbkInfo);
  sub_4422E0(&this->m_NoteItem[79].m_NotePic.m_pbkInfo);
  this->m_NoteItem[79].m_NotePicName.m_pbkInfo = (_PlugInfo *)92;
  this->m_NoteItem[79].m_NotePicName.m_ppic = (gbTexture *)610;
  this->m_NoteItem[79].m_NotePicName.m_ppicInfo = 0;
  this->m_NoteItem[79].m_NotePicName.m_disablepic = 0;
  this->m_NoteItem[79].m_NotePicName.m_disablepicInfo = 0;
  this->m_NoteItem[79].m_NotePicName.m_pbk2 = 0;
  ((ARC_PlayerAtt *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->Refresh();
  ((ARC_PlayerAtt *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->Refresh();
  ((ARC_PlayerAtt *)&this->m_NoteItem[80].m_NoteLv[1].m_textx)->Refresh();
  this->m_NoteItem[42].m_NotePic.m_pbkInfo = 0;
  this->m_NoteItem[42].m_NotePic.m_ppic = 0;
  this->m_NoteItem[42].m_NotePic.m_ppicInfo = 0;
  *(_DWORD *)&this->m_NoteItem[79].m_NotePicName.m_mouseoff = 0;
  memset(&this->m_NoteItem[43].m_HeadShot[1].m_ratioh, 0, 0x24u);
  return (int)this;
}

// 0x004B0540
int UITitle_JDHY::_UITitle_JDHY()
{
  int result; // eax

  ((UIRoleDialog *)&this->m_NoteItem[80].m_NoteLv[1].m_textx)->_UIRoleDialog();
  ((UIRoleDialog *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->_UIRoleDialog();
  ((UIRoleDialog *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->_UIRoleDialog();
  ((UIFrameWnd *)&this->m_NoteItem[79].m_NotePic.m_pbkInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[79].m_NoteLv[4].m_pbkInfo)->UIFrameWnd::_UIFrameWnd();
  ((CCBResultWindow *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->_CCBResultWindow();
  ((CCBResultWindow *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->_CCBResultWindow();
  ((CCBResultWindow *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->_CCBResultWindow();
  ((UICaption *)&this->m_NoteItem[79].m_HeadShot[4].m_fontcolor)->Destroy2();
  ((UICaption *)&this->m_NoteItem[79].m_HeadShot[1].m_pbkInfo)->Destroy2();
  ((UICaption *)&this->m_NoteItem[43].m_HeadShot_NO_SEL[4].m_childs.capacity)->Destroy2();
  ((UICaption *)&this->m_NoteItem[43].m_HeadShot_NO_SEL[2])->Destroy2();
  ((UICaption *)&this->m_NoteItem[43].m_NoteState.m_pbk)->Destroy2();
  ((UIStatic *)&this->m_NoteItem[43].m_NoteID.m_rect)->_UIStatic();
  ((UIStatic *)&this->m_NoteItem[43].m_NoteItemBk.m_texarray.m_ptex[4])->_UIStatic();
  ((UIFrameWnd *)&this->m_NoteItem[42].m_NotePicName.m_disablepic)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[42].m_NotePic.m_disablepic)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[0].m_NoteLv[4].m_fontcolor)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[0].m_NoteLv[3].m_fontcolor)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[0].m_NoteLv[1].m_mouseoff)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_NoteItem[0].m_NoteMoney.m_text[4])->Destroy2();
  ((UICaption *)&this->m_NoteItem[0].m_HeadShot[4].pDebugTex)->Destroy2();
  ((UICaption *)&this->m_NoteItem[0].m_HeadShot[2].m_rect.bottom)->Destroy2();
  ((UICaption *)&this->m_NoteItem[0].m_HeadShot_NO_SEL[4].m_mouseoff)->Destroy2();
  ((UICaption *)&this->m_NoteItem[0].m_HeadShot_NO_SEL[2].m_text[4])->Destroy2();
  ((UICaption *)&this->m_NoteItem[0].m_HeadShot_NO_SEL[0].m_benable)->Destroy2();
  ((UICaption *)&this->m_NoteItem[0].m_NoteID.m_rect.top)->Destroy2();
  ((UICaption *)&this->m_NoteItem[0].m_NoteItemBk.m_rect.top)->Destroy2();
  ((UICaption *)&this->m_exit.m_texarray.m_ptex[10])->Destroy2();
  ((UIFrameWnd *)&this->m_background.m_FVF)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->m_OutFrameB + 1))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameB)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameL.m_wndcolor)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameR.m_rect)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameT.m_rect.right)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
  return result;
}

// 0x004B0820
int UITitle_JDHY::PopulateContent()
{
  LONG v2; // eax
  LONG v3; // ecx
  LONG left; // ecx
  LONG right; // edx
  unsigned int Color; // eax
  unsigned int v7; // edx
  unsigned int v8; // eax
  gbTexture *m_disablepic; // edx
  gbTexture *v10; // edx
  int v11; // eax
  gbTexture *v12; // edx
  LONG v13; // edx
  int v14; // eax
  int v15; // edx
  int capacity; // eax
  LONG top; // eax
  int v18; // edx
  LONG v19; // eax
  int v20; // edx
  int m_bcreateok; // edx
  int v22; // ecx
  void *m_id; // eax
  LONG v24; // eax
  int v25; // ebx
  double v26; // st7
  __int64 v27; // rax
  int v28; // ebp
  __int64 v29; // rax
  int v30; // ecx
  int v31; // ebx
  char *v32; // ecx
  LONG v33; // ebp
  int v34; // eax
  double v35; // st7
  int v36; // ecx
  LONG v37; // eax
  int v38; // eax
  double v39; // st7
  int m_nTextW; // ebp
  LONG v41; // ebx
  int m_FVF; // eax
  char *m_pData; // ecx
  __int64 v44; // rax
  int v45; // ecx
  gbColorQuad *v46; // eax
  _PlugInfo *m_pbkInfo; // edx
  _PlugInfo *v48; // edx
  LONG bottom; // edx
  int v50; // eax
  int v51; // eax
  _PlugInfo *v52; // ebx
  double v53; // st7
  void *v54; // ebp
  LONG v55; // eax
  __int64 v56; // rax
  gbTexture *v57; // ecx
  _PlugInfo *m_ppicInfo; // ebp
  _BYTE *v59; // ecx
  void *v60; // ebx
  gbTexture *v61; // eax
  double v62; // st7
  int v63; // eax
  gbTexture *m_ppic; // eax
  double v65; // st7
  gbTexture *v66; // eax
  void *v67; // ecx
  gbTexture *v68; // ecx
  int v69; // edx
  int v70; // eax
  gbTexture *v71; // eax
  Parent_Data *v72; // ebx
  double v73; // st7
  __int64 v74; // rax
  _PlugInfo *v75; // ecx
  Parent_Data *v76; // ebx
  __int64 v77; // rax
  __int64 v78; // rax
  int v79; // ecx
  gbTexture *m_pbk; // eax
  Parent_Data *m_fonttype; // ebx
  double v82; // st7
  double v83; // st7
  double v84; // st7
  int m_texty; // ecx
  float fVal; // [esp+0x108] [ebp-0x8C]
  PlayerItem *v88; // [esp+0x10C] [ebp-0x88]
  PlayerItem *v89; // [esp+0x10C] [ebp-0x88]
  PlayerItem *v90; // [esp+0x10C] [ebp-0x88]
  PlayerItem *v91; // [esp+0x110] [ebp-0x84]
  PlayerItem *v92; // [esp+0x110] [ebp-0x84]
  PlayerItem *v93; // [esp+0x110] [ebp-0x84]
  gbTexture *v94; // [esp+0x11C] [ebp-0x78]
  int v95; // [esp+0x11C] [ebp-0x78]
  gbTexture *v96; // [esp+0x11C] [ebp-0x78]
  gbColorQuad v97; // [esp+0x120] [ebp-0x74] BYREF
  int v98; // [esp+0x124] [ebp-0x70] BYREF
  int v99; // [esp+0x128] [ebp-0x6C]
  int v100; // [esp+0x12C] [ebp-0x68]
  int v101; // [esp+0x130] [ebp-0x64]
  int v102; // [esp+0x134] [ebp-0x60] BYREF
  int v103; // [esp+0x138] [ebp-0x5C]
  int v104; // [esp+0x13C] [ebp-0x58]
  int v105; // [esp+0x140] [ebp-0x54]
  int v106; // [esp+0x144] [ebp-0x50] BYREF
  int v107; // [esp+0x148] [ebp-0x4C]
  int v108; // [esp+0x14C] [ebp-0x48]
  int v109; // [esp+0x150] [ebp-0x44]
  int v110; // [esp+0x154] [ebp-0x40] BYREF
  int v111; // [esp+0x158] [ebp-0x3C]
  int v112; // [esp+0x15C] [ebp-0x38]
  int v113; // [esp+0x160] [ebp-0x34]
  int v114; // [esp+0x164] [ebp-0x30] BYREF
  int v115; // [esp+0x168] [ebp-0x2C]
  int v116; // [esp+0x16C] [ebp-0x28]
  int v117; // [esp+0x170] [ebp-0x24]
  int v118; // [esp+0x174] [ebp-0x20] BYREF
  int v119; // [esp+0x178] [ebp-0x1C]
  int v120; // [esp+0x17C] [ebp-0x18]
  int v121; // [esp+0x180] [ebp-0x14]
  int nVal[4]; // [esp+0x184] [ebp-0x10] BYREF
  LONG v123; // [esp+0x198] [ebp+0x4]

  v2 = *(_DWORD *)this->buf;
  v3 = *(_DWORD *)&this->buf[4];
  this->rc.right = v2;
  this->rc.top = 0;
  this->rc.left = 0;
  this->rc.bottom = v3;
  ((UIListBox *)this)->SetSelTexture(-1, this->rc.left, this->rc.top, this->rc.right, this->rc.bottom, 0);
  left = this->rc.left;
  this->m_OutFrameT.m_rect.top = v123;
  right = this->m_OutFrameT.m_rect.right;
  v111 = this->rc.top + 38;
  v110 = left + 670;
  v113 = v111 + 505;
  v112 = left + 784;
  (*(void ( **)(LONG *, int, int *, UITitle_JDHY *))(right + 16))(
    &this->m_OutFrameT.m_rect.right,
    161,
    &v110,
    this);
  ((UIStatic *)&this->m_OutFrameT.m_rect.right)->CreateFromTemplate();
  v110 = v112;
  v112 += 17;
  v111 += 26;
  v102 = v112 - 205;
  v113 = v111 + 526;
  v104 = v112 - 205 + 203;
  Color = this->m_OutFrameL.m_wndcolor.Color;
  v103 = 0;
  v105 = 64;
  (*(void ( **)(gbColorQuad *, int, int *, UITitle_JDHY *))(Color + 16))(
    &this->m_OutFrameL.m_wndcolor,
    161,
    &v102,
    this);
  ((UIStatic *)&this->m_OutFrameL.m_wndcolor)->CreateFromTemplate();
  v7 = this->m_NoteItem[0].m_NoteLv[4].m_fontcolor.Color;
  v103 = -4;
  v102 = 618;
  v104 = 738;
  v105 = 28;
  (*(void ( **)(gbColorQuad *, int, int *, UITitle_JDHY *))(v7 + 16))(
    &this->m_NoteItem[0].m_NoteLv[4].m_fontcolor,
    161,
    &v102,
    this);
  ((UIScene *)&this->m_NoteItem[0].m_NoteLv[4].m_fontcolor)->SetShow(0);
  sub_446010(&this->m_NoteItem[0].m_NoteLv[4].m_fontcolor);
  v8 = this->m_NoteItem[0].m_NoteLv[3].m_fontcolor.Color;
  v103 = 16;
  v102 = 668;
  v104 = 748;
  v105 = 48;
  (*(void ( **)(gbColorQuad *, int, int *, UITitle_JDHY *))(v8 + 16))(
    &this->m_NoteItem[0].m_NoteLv[3].m_fontcolor,
    161,
    &v102,
    this);
  ((UIScene *)&this->m_NoteItem[0].m_NoteLv[3].m_fontcolor)->SetShow(0);
  sub_446010(&this->m_NoteItem[0].m_NoteLv[3].m_fontcolor);
  ((LineupUI *)this)->RebuildMainPage();
  m_disablepic = this->m_NoteItem[42].m_NotePic.m_disablepic;
  v99 = 23;
  v98 = 40;
  v100 = 624;
  v101 = 43;
  (*((void ( **)(gbTexture **, char *, int *, UITitle_JDHY *))m_disablepic + 4))(
    &this->m_NoteItem[42].m_NotePic.m_disablepic,
    &byte_A00700,
    &v98,
    this);
  ((UIStatic *)&this->m_NoteItem[42].m_NotePic.m_disablepic)->CreateFromTemplate();
  v10 = this->m_NoteItem[42].m_NotePicName.m_disablepic;
  v99 = 500;
  v98 = 41;
  v100 = 625;
  v101 = 537;
  (*((void ( **)(gbTexture **, char *, int *, UITitle_JDHY *))v10 + 4))(
    &this->m_NoteItem[42].m_NotePicName.m_disablepic,
    &byte_A00700,
    &v98,
    this);
  ((UIStatic *)&this->m_NoteItem[42].m_NotePicName.m_disablepic)->CreateFromTemplate();
  LOBYTE(v11) = g_bDebugMode;
  v12 = this->m_NoteItem[43].m_NoteItemBk.m_texarray.m_ptex[4];
  v107 = 5;
  v106 = 146;
  v108 = 264;
  v109 = 37;
  ((void ( *)(gbTexture **, char *, int *, UITitle_JDHY *, char *, int))v12->Height)(
    &this->m_NoteItem[43].m_NoteItemBk.m_texarray.m_ptex[4],
    &byte_A00704,
    &v106,
    this,
    "UI\\GameMainUI\\System\\Save",
    v11);
  ((UIStatic *)&this->m_NoteItem[43].m_NoteItemBk.m_texarray.m_ptex[4])->FormatText();
  v13 = this->m_NoteItem[43].m_NoteID.m_rect.left;
  v106 = v108 + 134;
  v108 += 252;
  v14 = v108;
  LOBYTE(v14) = g_bDebugMode;
  (*(void ( **)(tagRECT *, char *, int *, UITitle_JDHY *, char *, int))(v13 + 28))(
    &this->m_NoteItem[43].m_NoteID.m_rect,
    byte_A00705,
    &v106,
    this,
    "UI\\GameMainUI\\System\\Load",
    v14);
  ((UIStatic *)&this->m_NoteItem[43].m_NoteID.m_rect)->FormatText();
  LOBYTE(v15) = g_bDebugMode;
  capacity = this->m_NoteItem[43].m_HeadShot_NO_SEL[4].m_childs.capacity;
  v107 = 456;
  v106 = 696;
  v108 = 769;
  v109 = 531;
  (*(void ( **)(int *, char *, int *, UITitle_JDHY *, char *, int, int))(capacity + 28))(
    &this->m_NoteItem[43].m_HeadShot_NO_SEL[4].m_childs.capacity,
    &byte_A00708,
    &v106,
    this,
    "UI\\GameMainUI\\System\\ExitGame",
    1,
    v15);

  top = this->rc.top;
  LOBYTE(v18) = g_bDebugMode;
  v114 = this->rc.left + 634;
  v115 = top + 38;
  v116 = v114 + 25;
  v117 = top + 66;
  (*(void ( **)(char *, int *, UITitle_JDHY *, char *, int, int))&this->m_NoteItem[79].m_HeadShot[1].m_pbkInfo->name[24])(
    &byte_A00702,
    &v114,
    this,
    "UI\\GameMainUI\\System\\pgup",
    1,
    v18);
  v19 = this->rc.top;
  LOBYTE(v20) = g_bDebugMode;
  v114 = this->rc.left + 634;
  v115 = v19 + 503;
  v116 = v114 + 25;
  v117 = v19 + 531;
  (*(void ( **)(char *, int *, UITitle_JDHY *, char *, int, int))(this->m_NoteItem[79].m_HeadShot[4].m_fontcolor.Color
                                                                         + 28))(
    &byte_A00701,
    &v114,
    this,
    "UI\\GameMainUI\\System\\pgdw",
    1,
    v20);
  m_bcreateok = this->m_NoteItem[79].m_NoteMoney.m_bcreateok;
  this->m_NoteItem[79].m_NoteMoney.m_childs.capacity = 66;
  this->m_NoteItem[79].m_NoteMoney.m_childs.m_nSize = 654;
  this->m_NoteItem[79].m_NoteMoney.m_childs.m_pData = (char *)640;
  this->m_NoteItem[79].m_NoteMoney.m_childs.m_needscriptdel = 503;
  LOBYTE(v22) = g_bDebugMode;
  (*(void ( **)(int *, ARC_PlayerAtt *, PtrArray *, UITitle_JDHY *, char *, int))(m_bcreateok + 28))(
    &this->m_NoteItem[79].m_NoteMoney.m_bcreateok,
    &g_PlayerAttBuffer2,
    &this->m_NoteItem[79].m_NoteMoney.m_childs,
    this,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    v22);
  ((UIScene *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->SetTexture("UI\\GameMainUI\\System\\hdt.tga", 0);
  ((UIBigMap *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->Update(26, 28);
  fill((PlayerItem *)1, v88, v91);
  this->m_NoteItem[79].m_NoteLv[1].m_fontcolor.Color = 1096810496;
  this->m_NoteItem[79].m_NoteLv[1].m_wndcolor.Color = -1050673152;
  m_id = this->m_NoteItem[79].m_NoteLv[1].m_id;
  this->m_NoteItem[79].m_NoteLv[0].m_FVF = 20;
  if ( !m_id )
  {
    v37 = this->m_NoteItem[79].m_NoteLv[1].m_rect.left;
    if ( !v37 )
    {
      m_nTextW = this->m_NoteItem[79].m_NoteMoney.m_nTextW;
      v41 = (__int64)((double)(this->m_NoteItem[79].m_NoteLv[0].m_childs.capacity - m_nTextW - 20)
                    + *(float *)&this->m_NoteItem[79].m_NoteLv[1].m_fontcolor.Color);
      m_FVF = this->m_NoteItem[79].m_NoteMoney.m_FVF;
      m_pData = this->m_NoteItem[79].m_NoteLv[0].m_childs.m_pData;
      this->m_NoteItem[79].m_NoteLv[0].m_rect.right = v41;
      v44 = (__int64)((double)(int)&m_pData[-(m_FVF / 2)]
                    + *(float *)&this->m_NoteItem[79].m_NoteLv[0].m_nTextW
                    + *(float *)&this->m_NoteItem[79].m_NoteLv[0].m_pbk2);
      v45 = this->m_NoteItem[79].m_NoteMoney.m_FVF;
      this->m_NoteItem[79].m_NoteLv[0].m_rect.top = v44;
      this->m_NoteItem[79].m_NoteLv[0].m_rect.bottom = v45 + v44;
      this->m_NoteItem[79].m_NoteLv[0].m_pfather = (UIWnd *)(m_nTextW + v41);
      goto LABEL_12;
    }
    if ( v37 != 1 )
      goto LABEL_12;
    v31 = this->m_NoteItem[79].m_NoteMoney.m_nTextW;
    v33 = (__int64)((double)(this->m_NoteItem[79].m_NoteLv[0].m_childs.capacity - v31 - 20)
                  + *(float *)&this->m_NoteItem[79].m_NoteLv[1].m_fontcolor.Color);
    v38 = this->m_NoteItem[79].m_NoteMoney.m_FVF;
    v39 = (double)this->m_NoteItem[79].m_NoteLv[0].m_childs.m_nSize - *(float *)&this->m_NoteItem[79].m_NoteLv[0].m_pbk2;
    this->m_NoteItem[79].m_NoteLv[0].m_rect.right = v33;
// [VFTABLE] v35 = v39 - (double)(v38 / 2) - *(float *)&this->m_NoteItem[79].m_NoteLv[1].__vftable;
LABEL_7:
    v36 = this->m_NoteItem[79].m_NoteMoney.m_FVF;
    this->m_NoteItem[79].m_NoteLv[0].m_rect.top = (__int64)v35;
    this->m_NoteItem[79].m_NoteLv[0].m_rect.bottom = v36 + (__int64)v35;
    this->m_NoteItem[79].m_NoteLv[0].m_pfather = (UIWnd *)(v31 + v33);
    goto LABEL_12;
  }
  if ( m_id != (void *)1 )
    goto LABEL_12;
  v24 = this->m_NoteItem[79].m_NoteLv[1].m_rect.left;
  if ( !v24 )
  {
    v31 = this->m_NoteItem[79].m_NoteMoney.m_nTextW;
    v32 = this->m_NoteItem[79].m_NoteLv[0].m_childs.m_pData;
    v33 = (__int64)((double)(this->m_NoteItem[79].m_NoteLv[0].m_childs.capacity - v31 / 2)
                  + *(float *)&this->m_NoteItem[79].m_NoteLv[1].m_fontcolor.Color
                  + *(float *)&this->m_NoteItem[79].m_NoteLv[0].m_pbk2);
    v34 = this->m_NoteItem[79].m_NoteMoney.m_FVF;
    this->m_NoteItem[79].m_NoteLv[0].m_rect.right = v33;
    v35 = (double)(int)&v32[-v34 - 20] + *(float *)&this->m_NoteItem[79].m_NoteLv[0].m_nTextW;
    goto LABEL_7;
  }
  if ( v24 == 1 )
  {
    v25 = this->m_NoteItem[79].m_NoteMoney.m_nTextW;
    v26 = (double)this->m_NoteItem[79].m_NoteLv[0].m_childs.m_needscriptdel
        - *(float *)&this->m_NoteItem[79].m_NoteLv[0].m_pbk2;
    v27 = (__int64)(v26 - (double)(v25 / 2) - *(float *)&this->m_NoteItem[79].m_NoteLv[1].m_wndcolor.Color);
    HIDWORD(v27) = this->m_NoteItem[79].m_NoteLv[0].m_childs.m_nSize;
    v28 = (__int64)(v26 - (double)(v25 / 2) - *(float *)&this->m_NoteItem[79].m_NoteLv[1].m_wndcolor.Color);
    this->m_NoteItem[79].m_NoteLv[0].m_rect.right = v27;
    v29 = (__int64)((double)(HIDWORD(v27) + 20)
                  - *(float *)&this->m_NoteItem[79].m_NoteLv[0].m_pbk2
// [VFTABLE] - *(float *)&this->m_NoteItem[79].m_NoteLv[1].__vftable);
    v30 = this->m_NoteItem[79].m_NoteMoney.m_FVF;
    this->m_NoteItem[79].m_NoteLv[0].m_rect.top = v29;
    this->m_NoteItem[79].m_NoteLv[0].m_rect.bottom = v29 + v30;
    this->m_NoteItem[79].m_NoteLv[0].m_pfather = (UIWnd *)(v25 + v28);
  }
LABEL_12:
  // [AUTO-COMMENTED] v46 = ((gbColorQuad *)&v97)->gbColorQuad(0, 0, 0, 0);
  ((UIScene *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->SetParam(v46->Color);
  fVal = (float)(32 * (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo - 28);
  ((UIScene *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->UpdateLayout(fVal);
  m_pbkInfo = this->m_NoteItem[79].m_NoteLv[4].m_pbkInfo;
  v119 = 368;
  v118 = 684;
  v120 = 740;
  v121 = 392;
  (*(void ( **)(_PlugInfo **, char *, int *, UITitle_JDHY *))&m_pbkInfo->name[12])(
    &this->m_NoteItem[79].m_NoteLv[4].m_pbkInfo,
    &byte_A00700,
    &v118,
    this);
  ((UIStatic *)&this->m_NoteItem[79].m_NoteLv[4].m_pbkInfo)->CreateFromTemplate();
  v48 = this->m_NoteItem[79].m_NotePic.m_pbkInfo;
  v119 = 105;
  v118 = 726;
  v120 = 782;
  v121 = 129;
  (*(void ( **)(_PlugInfo **, char *, int *, UITitle_JDHY *))&v48->name[12])(
    &this->m_NoteItem[79].m_NotePic.m_pbkInfo,
    &byte_A00700,
    &v118,
    this);
  ((UIStatic *)&this->m_NoteItem[79].m_NotePic.m_pbkInfo)->CreateFromTemplate();
  bottom = this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom;
  v99 = 56;
  v98 = 698;
  v100 = 718;
  v101 = 364;
  (*(void ( **)(LONG *, char *, int *, UITitle_JDHY *, char *, _DWORD))(bottom + 28))(
    &this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom,
    byte_A00709,
    &v98,
    this,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    0);
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->SetTexture("UI\\GameMainUI\\System\\MusicBar.tga", g_bDebugMode);
  fill((PlayerItem *)1, v89, v92);
  ((UIBigMap *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->Update(26, 30);
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->SetParam(0);
  this->m_NoteItem[79].m_NoteLv[2].m_disablepicInfo = (_PlugInfo *)1101004800;
  this->m_NoteItem[79].m_NoteLv[2].m_pbk2 = (gbTexture *)-1049624576;
  v50 = *(_DWORD *)&this->m_NoteItem[79].m_NoteLv[2].m_mouseoff;
  this->m_NoteItem[79].m_NoteLv[2].m_ppic = (gbTexture *)23;
  if ( !v50 )
  {
    v63 = this->m_NoteItem[79].m_NoteLv[2].m_FVF;
    if ( v63 )
    {
      if ( v63 != 1 )
        goto LABEL_23;
      m_ppicInfo = this->m_NoteItem[79].m_NoteLv[1].m_ppicInfo;
      v97.Color = this->m_NoteItem[79].m_NoteLv[2].m_rect.left - (_DWORD)m_ppicInfo - 23;
      v60 = (void *)(__int64)((double)(int)v97.Color
                                     + *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_disablepicInfo);
      m_ppic = this->m_NoteItem[79].m_NoteLv[1].m_ppic;
      v65 = (double)this->m_NoteItem[79].m_NoteLv[2].m_rect.top - *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_pbk;
// [VFTABLE] this->m_NoteItem[79].m_NoteLv[2].__vftable = v60;
      v97.Color = (int)m_ppic / 2;
      v62 = v65 - (double)((int)m_ppic / 2) - *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_disablepic;
    }
    else
    {
      m_ppicInfo = this->m_NoteItem[79].m_NoteLv[1].m_ppicInfo;
      v97.Color = this->m_NoteItem[79].m_NoteLv[2].m_rect.left - (_DWORD)m_ppicInfo - 23;
      v60 = (void *)(__int64)((double)(int)v97.Color
                                     + *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_disablepicInfo);
      v66 = this->m_NoteItem[79].m_NoteLv[1].m_ppic;
      v67 = this->m_NoteItem[79].m_NoteLv[2].m_id;
// [VFTABLE] this->m_NoteItem[79].m_NoteLv[2].__vftable = v60;
      v97.Color = (unsigned int)v67 - (int)v66 / 2;
      v62 = (double)(int)v97.Color
          + *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_ppicInfo
          + *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_pbk;
    }
    goto LABEL_22;
  }
  if ( v50 != 1 )
    goto LABEL_23;
  v51 = this->m_NoteItem[79].m_NoteLv[2].m_FVF;
  if ( !v51 )
  {
    m_ppicInfo = this->m_NoteItem[79].m_NoteLv[1].m_ppicInfo;
    v97.Color = this->m_NoteItem[79].m_NoteLv[2].m_rect.left - (int)m_ppicInfo / 2;
    v59 = this->m_NoteItem[79].m_NoteLv[2].m_id;
    v60 = (void *)(__int64)((double)(int)v97.Color
                                   + *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_disablepicInfo
                                   + *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_pbk);
    v61 = this->m_NoteItem[79].m_NoteLv[1].m_ppic;
// [VFTABLE] this->m_NoteItem[79].m_NoteLv[2].__vftable = v60;
    v97.Color = v59 - (_BYTE *)v61 - 23;
    v62 = (double)(int)v97.Color + *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_ppicInfo;
LABEL_22:
    v68 = this->m_NoteItem[79].m_NoteLv[1].m_ppic;
    this->m_NoteItem[79].m_NoteLv[1].m_nTextW = (__int64)v62;
    this->m_NoteItem[79].m_NoteLv[2].m_fontcolor.Color = (unsigned int)v68 + (__int64)v62;
    this->m_NoteItem[79].m_NoteLv[2].m_wndcolor.Color = (unsigned int)v60 + (_DWORD)m_ppicInfo;
    goto LABEL_23;
  }
  if ( v51 == 1 )
  {
    v52 = this->m_NoteItem[79].m_NoteLv[1].m_ppicInfo;
    v53 = (double)this->m_NoteItem[79].m_NoteLv[2].m_rect.right - *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_pbk;
    v97.Color = (int)v52 / 2;
    v54 = (void *)(__int64)(v53 - (double)((int)v52 / 2) - *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_pbk2);
    v55 = this->m_NoteItem[79].m_NoteLv[2].m_rect.top;
// [VFTABLE] this->m_NoteItem[79].m_NoteLv[2].__vftable = v54;
    v97.Color = v55 + 23;
    v56 = (__int64)((double)(v55 + 23)
                  - *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_pbk
                  - *(float *)&this->m_NoteItem[79].m_NoteLv[2].m_disablepic);
    v57 = this->m_NoteItem[79].m_NoteLv[1].m_ppic;
    this->m_NoteItem[79].m_NoteLv[1].m_nTextW = v56;
    this->m_NoteItem[79].m_NoteLv[2].m_fontcolor.Color = (unsigned int)v57 + v56;
    this->m_NoteItem[79].m_NoteLv[2].m_wndcolor.Color = (unsigned int)v54 + (_DWORD)v52;
  }
LABEL_23:
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->UpdateLayout(100.0);
  v69 = this->m_NoteItem[79].m_NoteLv[2].m_nTextW;
  v99 = 136;
  v98 = 744;
  v100 = 764;
  v101 = 444;
  (*(void ( **)(int *, int *, int *, UITitle_JDHY *, char *, _DWORD))(v69 + 28))(
    &this->m_NoteItem[79].m_NoteLv[2].m_nTextW,
    dword_A00710,
    &v98,
    this,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    0);
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->SetTexture("UI\\GameMainUI\\System\\MusicEffect.tga", g_bDebugMode);
  fill((PlayerItem *)1, v90, v93);
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->ResizeContentAlt(1);
  ((UIBigMap *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->Update(26, 30);
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->SetParam(0);
  *(_DWORD *)&this->m_NoteItem[79].m_NoteLv[4].m_text[4] = 1097859072;
  *(_DWORD *)&this->m_NoteItem[79].m_NoteLv[4].m_text[8] = -1046478848;
  v70 = *(_DWORD *)&this->m_NoteItem[79].m_NoteLv[4].m_text[12];
  this->m_NoteItem[79].m_NoteLv[4].m_texty = 2;
  if ( !v70 )
  {
    m_pbk = this->m_NoteItem[79].m_NoteLv[4].m_pbk;
    if ( m_pbk )
    {
      if ( m_pbk != (gbTexture *)1 )
        goto LABEL_34;
      m_fonttype = this->m_NoteItem[79].m_NoteLv[3].m_fonttype;
      v97.Color = (char *)this->m_NoteItem[79].m_NoteLv[3].m_pbk2 - (char *)m_fonttype - 2;
      v82 = (double)*(int *)&this->m_NoteItem[79].m_NoteLv[3].m_mouseoff;
      v96 = (gbTexture *)(__int64)((double)(int)v97.Color + *(float *)&this->m_NoteItem[79].m_NoteLv[4].m_text[4]);
      this->m_NoteItem[79].m_NoteLv[3].m_ppic = v96;
      v83 = v82 - this->m_NoteItem[79].m_NoteLv[4].m_ratioh;
      v97.Color = this->m_NoteItem[79].m_NoteLv[3].m_texty / 2;
      v84 = v83 - (double)(int)v97.Color - *(float *)this->m_NoteItem[79].m_NoteLv[4].m_text;
    }
    else
    {
      m_fonttype = this->m_NoteItem[79].m_NoteLv[3].m_fonttype;
      v97.Color = (char *)this->m_NoteItem[79].m_NoteLv[3].m_pbk2 - (char *)m_fonttype - 2;
      v96 = (gbTexture *)(__int64)((double)(int)v97.Color + *(float *)&this->m_NoteItem[79].m_NoteLv[4].m_text[4]);
      this->m_NoteItem[79].m_NoteLv[3].m_ppic = v96;
      v97.Color = (unsigned int)this->m_NoteItem[79].m_NoteLv[3].m_disablepicInfo
                - this->m_NoteItem[79].m_NoteLv[3].m_texty / 2;
      v84 = (double)(int)v97.Color
          + *(float *)&this->m_NoteItem[79].m_NoteLv[4].m_fonttype
          + this->m_NoteItem[79].m_NoteLv[4].m_ratioh;
    }
    m_texty = this->m_NoteItem[79].m_NoteLv[3].m_texty;
    this->m_NoteItem[79].m_NoteLv[3].m_pbkInfo = (_PlugInfo *)(__int64)v84;
    this->m_NoteItem[79].m_NoteLv[3].m_ppicInfo = (_PlugInfo *)(m_texty + (__int64)v84);
    this->m_NoteItem[79].m_NoteLv[3].m_disablepic = (gbTexture *)((char *)m_fonttype + (_DWORD)v96);
    goto LABEL_34;
  }
  if ( v70 == 1 )
  {
    v71 = this->m_NoteItem[79].m_NoteLv[4].m_pbk;
    if ( v71 )
    {
      if ( v71 == (gbTexture *)1 )
      {
        v72 = this->m_NoteItem[79].m_NoteLv[3].m_fonttype;
        v73 = (double)this->m_NoteItem[79].m_NoteLv[3].m_FVF - this->m_NoteItem[79].m_NoteLv[4].m_ratioh;
        v97.Color = (int)v72 / 2;
        v94 = (gbTexture *)(__int64)(v73 - (double)((int)v72 / 2) - *(float *)&this->m_NoteItem[79].m_NoteLv[4].m_text[8]);
        this->m_NoteItem[79].m_NoteLv[3].m_ppic = v94;
        v97.Color = *(_DWORD *)&this->m_NoteItem[79].m_NoteLv[3].m_mouseoff + 2;
        v74 = (__int64)((double)(int)v97.Color
                      - this->m_NoteItem[79].m_NoteLv[4].m_ratioh
                      - *(float *)this->m_NoteItem[79].m_NoteLv[4].m_text);
        v75 = (_PlugInfo *)(v74 + this->m_NoteItem[79].m_NoteLv[3].m_texty);
        this->m_NoteItem[79].m_NoteLv[3].m_pbkInfo = (_PlugInfo *)v74;
        this->m_NoteItem[79].m_NoteLv[3].m_ppicInfo = v75;
        this->m_NoteItem[79].m_NoteLv[3].m_disablepic = (gbTexture *)((char *)v94 + (_DWORD)v72);
      }
    }
    else
    {
      v76 = this->m_NoteItem[79].m_NoteLv[3].m_fonttype;
      v97.Color = (unsigned int)this->m_NoteItem[79].m_NoteLv[3].m_pbk2 - (int)v76 / 2;
      v77 = (__int64)((double)(int)v97.Color
                    + *(float *)&this->m_NoteItem[79].m_NoteLv[4].m_text[4]
                    + this->m_NoteItem[79].m_NoteLv[4].m_ratioh);
      HIDWORD(v77) = this->m_NoteItem[79].m_NoteLv[3].m_disablepicInfo;
      v95 = (__int64)((double)(int)v97.Color
                    + *(float *)&this->m_NoteItem[79].m_NoteLv[4].m_text[4]
                    + this->m_NoteItem[79].m_NoteLv[4].m_ratioh);
      this->m_NoteItem[79].m_NoteLv[3].m_ppic = (gbTexture *)v77;
      v97.Color = HIDWORD(v77) - this->m_NoteItem[79].m_NoteLv[3].m_texty - 2;
      v78 = (__int64)((double)(int)v97.Color + *(float *)&this->m_NoteItem[79].m_NoteLv[4].m_fonttype);
      v79 = this->m_NoteItem[79].m_NoteLv[3].m_texty;
      this->m_NoteItem[79].m_NoteLv[3].m_pbkInfo = (_PlugInfo *)v78;
      this->m_NoteItem[79].m_NoteLv[3].m_ppicInfo = (_PlugInfo *)(v79 + v78);
      this->m_NoteItem[79].m_NoteLv[3].m_disablepic = (gbTexture *)((char *)v76 + v95);
    }
  }
LABEL_34:
  ((UIScene *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->UpdateLayout(100.0);
  ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->SetProgress(0.0);
  ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->SetProgress(0.0);
  ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->SetProgress(0.0);
  nVal[1] = 200;
  nVal[0] = 250;
  nVal[2] = 550;
  nVal[3] = 300;
  ((ARC_PlayerAtt *)&this->m_NoteItem[80].m_NoteLv[1].m_textx)->Create((int)&byte_ABC00B, (int)nVal);
  ((UIItem *)&this->m_NoteItem[80].m_NoteLv[1].m_textx)->SetData(219);
  ((ARC_PlayerAtt *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->Create((int)&g_PlayerAttBuffer2.Remark[5], (int)nVal);
  ((UIItem *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->SetData(219);
  ((ARC_PlayerAtt *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->Create((int)&g_PlayerAttBuffer2.Remark[6], (int)nVal);
  return (int)((UIItem *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetData(219);
}

// 0x004B1580
int UITitle_JDHY::ResetAndRefresh()
{
  int nVal; // [esp+0xC] [ebp+0x4]

  this->m_NoteItem[79].m_NotePicName.m_ppicInfo = 0;
  this->m_NoteItem[79].m_NoteLv[1].m_rect.top = 0;
  this->m_NoteItem[79].m_NoteLv[1].m_rect.right = 1;
  ((CScreenMode *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->SetProgress(0.0);
  this->m_NoteItem[79].m_NotePicName.m_disablepicInfo = 0;
  this->m_NoteItem[79].m_NotePicName.m_disablepic = 0;
  memset(&this->m_NoteItem[43].m_HeadShot[1].m_ratioh, 0, 0x24u);
  ((LineupUI *)this)->UpdateProtectPanel(nVal);

  return this->UpdateTextPosition();
}

// 0x004B15F0
int UITitle_JDHY::InitNoteItems()
{
  gbTexture *m_ppic; // eax
  _PlugInfo *m_pbkInfo; // ecx
  int result; // eax
  LONG *p_top; // esi
  _DWORD *v6; // edi
  int v7; // [esp+ACh] [ebp-0x1C]
  int v8; // [esp+B0h] [ebp-0x18]
  int v9; // [esp+B4h] [ebp-0x14]
  _DWORD v10[4]; // [esp+B8h] [ebp-0x10] BYREF

  v10[1] = 42;
  m_ppic = this->m_NoteItem[79].m_NotePicName.m_ppic;
  m_pbkInfo = this->m_NoteItem[79].m_NotePicName.m_pbkInfo;
  result = (int)(m_ppic + 3);
  v10[0] = 12;
  v10[2] = result;
  v10[3] = &m_pbkInfo->name[38];
  v7 = 0;
  p_top = &this->m_NoteItem[43].m_HeadShot[4].m_rect.top;
  do
  {
    LOBYTE(result) = g_bDebugMode;
    (*(void ( **)(LONG *, char *, _DWORD *, UITitle_JDHY *, char *, int, int))(*(p_top - 86) + 28))(
      p_top - 86,
      &byte_A00703,
      v10,
      this,
      "UI\\GameMainUI\\System\\Note",
      1,
      result);
    ((PalScript *)(p_top - 86))->OpenScript("UI\\GameMainUI\\System\\Note2.tga", g_bDebugMode);
    *((_BYTE *)p_top - 4) = 0;
    (*(void ( **)(LONG *, _DWORD))*(p_top - 86))(p_top - 86, 0);
    (*(void ( **)(LONG *, char *, _DWORD *, UITitle_JDHY *))(*p_top + 16))(p_top, &byte_A00703, v10, this);
    ((UIScene *)p_top)->SetShow(0);
    v9 = v7 + 1;
    sprintf(&this->buf[16], &dir[20], v7 + 1);
    ((UICaption *)p_top)->SetEnable((int)&this->buf[16], 1);
    (*(void ( **)(LONG *, _DWORD))*p_top)(p_top, 0);
    (*(void ( **)(LONG *, char *, _DWORD *, UITitle_JDHY *))(p_top[38] + 16))(
      p_top + 38,
      &byte_A00703,
      v10,
      this);
    (*(void ( **)(LONG *, _DWORD))p_top[38])(p_top + 38, 0);
    v6 = p_top + 76;
    v8 = 5;
    do
    {
      (*(void ( **)(_DWORD *, char *, _DWORD *, UITitle_JDHY *))(v6[190] + 16))(
        v6 + 190,
        &byte_A00703,
        v10,
        this);
      (*(void ( **)(_DWORD *, _DWORD))v6[190])(v6 + 190, 0);
      (*(void ( **)(_DWORD *, char *, _DWORD *, UITitle_JDHY *))(*v6 + 16))(v6, &byte_A00703, v10, this);
      (*(void ( **)(_DWORD *, _DWORD))*v6)(v6, 0);
      (*(void ( **)(_DWORD *, char *, _DWORD *, UITitle_JDHY *))(v6[458] + 16))(
        v6 + 458,
        &byte_A00703,
        v10,
        this);
      sub_446010(v6 + 458);
      (*(void ( **)(_DWORD *, _DWORD))v6[458])(v6 + 458, 0);
      v6 += 38;
      --v8;
    }
    while ( v8 );
    (*(void ( **)(LONG *, char *, _DWORD *, UITitle_JDHY *))(p_top[458] + 16))(
      p_top + 458,
      &byte_A00703,
      v10,
      this);
    sub_446010(p_top + 458);
    (*(void ( **)(LONG *, _DWORD))p_top[458])(p_top + 458, 0);
    (*(void ( **)(LONG *, char *, _DWORD *, UITitle_JDHY *))(p_top[496] + 16))(
      p_top + 496,
      &byte_A00703,
      v10,
      this);
    sub_446010(p_top + 496);
    (*(void ( **)(LONG *, _DWORD))p_top[496])(p_top + 496, 0);
    (*(void ( **)(LONG *, char *, _DWORD *, UITitle_JDHY *))(p_top[724] + 16))(
      p_top + 724,
      &byte_A00703,
      v10,
      this);
    (*(void ( **)(LONG *, _DWORD))p_top[724])(p_top + 724, 0);
    (*(void ( **)(LONG *, char *, _DWORD *, UITitle_JDHY *))(p_top[762] + 16))(
      p_top + 762,
      &byte_A00703,
      v10,
      this);
    sub_446010(p_top + 762);
    (*(void ( **)(LONG *, _DWORD))p_top[762])(p_top + 762, 0);
    p_top += 890;
    *((_BYTE *)&this->m_NoteItem[43].m_HeadShot[1].m_ratioh + v7) = 0;
    result = ++v7;
  }
  while ( v9 < 36 );
  return result;
}

// 0x004B1C00
int UITitle_JDHY::ResetNoteState()
{
  gbTexture *m_pbk2; // eax
  int result; // eax

  m_pbk2 = this->m_NoteItem[79].m_NotePicName.m_pbk2;
  if ( m_pbk2 )
  {
    result = (int)&m_pbk2[-1].nLevels + 3;
    if ( !result )
    {
      *(_DWORD *)this->m_NoteItem[43].m_NoteID.m_text = 1;
      LOBYTE(this->m_NoteItem[43].m_NoteID.m_textx) = 1;
      *(_DWORD *)this->m_NoteItem[43].m_NoteItemBk.m_caption = 0;
      LOBYTE(this->m_NoteItem[43].m_NoteItemBk.m_disablepicInfo) = 0;
      return 1;
    }
  }
  else
  {
    *(_DWORD *)this->m_NoteItem[43].m_NoteID.m_text = 0;
    LOBYTE(this->m_NoteItem[43].m_NoteID.m_textx) = 0;
    *(_DWORD *)this->m_NoteItem[43].m_NoteItemBk.m_caption = 1;
    LOBYTE(this->m_NoteItem[43].m_NoteItemBk.m_disablepicInfo) = 1;
    return 1;
  }
  return result;
}

// 0x004B1C50
int UITitle_JDHY::UpdateButtonStates()
{
  int v1; // ebp
  LONG *p_top; // esi
  void (***v3)(_DWORD, _DWORD); // edi
  int v4; // ebx
  int result; // eax
  gbTexture *m_ppicInfo; // ecx
  LONG *v7; // edi
  int v8; // ebp
  void ( ***v9)(_DWORD, int); // esi
  void ( ***v10)(_DWORD, int); // ecx
  UITitle_JDHY *v11; // ebp
  gbTexture *v12; // esi
  void ( ***v13)(_DWORD, int); // ecx
  int v14; // ebp
  LONG *v15; // esi
  gbTexture *v17; // [esp+0x58] [ebp-0x4]

  v1 = 0;
  p_top = &this->m_NoteItem[43].m_HeadShot[4].m_rect.top;
  do
  {
    (*(void ( **)(LONG *, _DWORD))*(p_top - 86))(p_top - 86, 0);
    (*(void ( **)(LONG *, _DWORD))*p_top)(p_top, 0);
    (*(void ( **)(LONG *, _DWORD))p_top[38])(p_top + 38, 0);
    v3 = (void ( ***)(_DWORD, _DWORD))(p_top + 76);
    v4 = 5;
    do
    {
      (*v3[190])(v3 + 190, 0);
      (**v3)(v3, 0);
      (*v3[458])(v3 + 458, 0);
      v3 += 38;
      --v4;
    }
    while ( v4 );
    (*(void ( **)(LONG *, _DWORD))p_top[458])(p_top + 458, 0);
    (*(void ( **)(LONG *, _DWORD))p_top[496])(p_top + 496, 0);
    (*(void ( **)(LONG *, _DWORD))p_top[724])(p_top + 724, 0);
    (*(void ( **)(LONG *, _DWORD))p_top[762])(p_top + 762, 0);
    result = (int)this;
    ++v1;
    p_top += 890;
    *((_BYTE *)&this->m_NoteItem[43].m_HeadShot[1].m_ratiow + v1 + 3) = 0;
  }
  while ( v1 < 36 );
  m_ppicInfo = (gbTexture *)this->m_NoteItem[79].m_NotePicName.m_ppicInfo;
  v17 = m_ppicInfo;
  if ( !__OFSUB__(m_ppicInfo, (char *)m_ppicInfo + 5) )
  {
    v7 = &this->m_NoteItem[(int)m_ppicInfo + 43].m_HeadShot[4].m_rect.top;
    do
    {
      (*(void ( **)(LONG *, int))*(v7 - 86))(v7 - 86, 1);
      (*(void ( **)(LONG *, int))*v7)(v7, 1);
      (*(void ( **)(LONG *, int))v7[38])(v7 + 38, 1);
      v8 = 0;
      v9 = (void ( ***)(_DWORD, int))(v7 + 76);
      do
      {
        v10 = v9 + 190;
        if ( *((_BYTE *)v7 + v8 + 1824) )
        {
          (**v10)(v10, 1);
          (**v9)(v9, 1);
          (*v9[458])(v9 + 458, 1);
        }
        else
        {
          (**v10)(v10, 0);
          (**v9)(v9, 0);
          (*v9[458])(v9 + 458, 0);
        }
        ++v8;
        v9 += 38;
      }
      while ( v8 < 5 );
      (*(void ( **)(LONG *, int))v7[458])(v7 + 458, 1);
      (*(void ( **)(LONG *, int))v7[496])(v7 + 496, 1);
v12 = v17;
      v13 = (void ( ***)(_DWORD, int))(v7 + 724);
      if ( this->m_NoteItem[79].m_NotePicName.m_disablepic == v17 )
      {
        (**v13)(v13, 1);
        v14 = 0;
        v15 = v7 + 76;
        do
        {
          (*(void ( **)(bool))v15[190])(*((_BYTE *)v7 + v14 + 1824) != 0);
          (*(void ( **)(LONG *, _DWORD))*v15)(v15, 0);
          ++v14;
          v15 += 38;
        }
        while ( v14 < 5 );
        v12 = v17;
}
      else
      {
        (**v13)(v13, 0);
      }
      result = (*(int ( **)(LONG *, int))v7[762])(v7 + 762, 1);
      *((_BYTE *)&this->m_NoteItem[43].m_HeadShot[1].m_ratioh + (_DWORD)v12) = 1;
      v7 += 890;
      v17 = (gbTexture *)((char *)v12 + 1);
    }
    while ( (int)v12 + 1 < (int)&this->m_NoteItem[79].m_NotePicName.m_ppicInfo->name[1] );
  }
  return result;
}

// 0x004B1EA0
int UITitle_JDHY::ScrollDown()
{
  LONG v2; // eax
  CScreenMode *v3; // eax
  int result; // eax
  int v5; // ebx
  int *p_m_ppic; // esi
  unsigned int v7; // eax
  CScreenMode *Instance; // eax
  const void *v9; // [esp-0x4] [ebp-0x14]
  const void *v10; // [esp-0x4] [ebp-0x14]
  float fProgress; // [esp+0x0] [ebp-0x10]
  char v12; // [esp+0x14] [ebp+0x4]
  LONG v13; // [esp+0x14] [ebp+0x4]

  ++this->m_NoteItem[79].m_NotePicName.m_ppicInfo;
  if ( v12 )
  {
    v2 = this->m_NoteItem[79].m_NoteLv[1].m_rect.right + 1;
    this->m_NoteItem[79].m_NoteLv[1].m_rect.right = v2;
    if ( v2 > 32 )
      this->m_NoteItem[79].m_NoteLv[1].m_rect.right = 32;
    v13 = this->m_NoteItem[79].m_NoteLv[1].m_rect.right * (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo - 28;
    this->m_NoteItem[79].m_NoteLv[1].m_rect.top = v13;
    fProgress = (float)v13;
    ((CScreenMode *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->SetProgress(fProgress);
  }
  if ( (int)this->m_NoteItem[79].m_NotePicName.m_ppicInfo <= 31 )
  {

    v5 = 0;
    p_m_ppic = (int *)&this->m_NoteItem[43].m_HeadShot[1].m_ppic;
    do
    {
      v7 = *p_m_ppic - (unsigned int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo;
      *p_m_ppic = v7;
      p_m_ppic[2] = (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo + v7;
      ((ChoseCompose *)this)->LayoutItem(v5++, *(p_m_ppic - 1), *p_m_ppic, p_m_ppic[1], p_m_ppic[2]);
      p_m_ppic += 890;
    }
    while ( v5 < 36 );
    v10 = off_5D11E0;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v10, 1);
    LOBYTE(result) = 1;
  }
  else
  {
    this->m_NoteItem[79].m_NotePicName.m_ppicInfo = (_PlugInfo *)31;
    v9 = off_5D11C4;
    v3 = CScreenMode::GetInstance();
    ((CScreenMode *)v3)->AudioSetPosition(v9, 1);
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004B1FB0
int UITitle_JDHY::ScrollUp()
{
  int v2; // ebx
  LONG v3; // eax
  LONG v4; // eax
  CScreenMode *v5; // eax
  int result; // eax
  int *p_m_ppic; // edi
  char *v8; // eax
  CScreenMode *Instance; // eax
  const void *v10; // [esp-0x4] [ebp-0x14]
  const void *v11; // [esp-0x4] [ebp-0x14]
  float fProgress; // [esp+0x0] [ebp-0x10]
  char v13; // [esp+0x14] [ebp+0x4]

  v2 = 0;
  --this->m_NoteItem[79].m_NotePicName.m_ppicInfo;
  if ( v13 )
  {
    v3 = this->m_NoteItem[79].m_NoteLv[1].m_rect.right - 1;
    this->m_NoteItem[79].m_NoteLv[1].m_rect.right = v3;
    if ( v3 <= 0 )
      this->m_NoteItem[79].m_NoteLv[1].m_rect.right = 0;
    v4 = this->m_NoteItem[79].m_NoteLv[1].m_rect.right * (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo - 28;
    this->m_NoteItem[79].m_NoteLv[1].m_rect.top = v4;
    if ( v4 < 0 )
      this->m_NoteItem[79].m_NoteLv[1].m_rect.top = 0;
    fProgress = (float)this->m_NoteItem[79].m_NoteLv[1].m_rect.top;
    ((CScreenMode *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->SetProgress(fProgress);
  }
  if ( (int)this->m_NoteItem[79].m_NotePicName.m_ppicInfo >= 0 )
  {

    p_m_ppic = (int *)&this->m_NoteItem[43].m_HeadShot[1].m_ppic;
    do
    {
      v8 = (char *)this->m_NoteItem[79].m_NotePicName.m_pbkInfo + *p_m_ppic;
      *p_m_ppic = (int)v8;
      p_m_ppic[2] = (int)&v8[(unsigned int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo];
      ((ChoseCompose *)this)->LayoutItem(v2++, *(p_m_ppic - 1), *p_m_ppic, p_m_ppic[1], p_m_ppic[2]);
      p_m_ppic += 890;
    }
    while ( v2 < 36 );
    v11 = off_5D11E0;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v11, 1);
    LOBYTE(result) = 1;
  }
  else
  {
    this->m_NoteItem[79].m_NotePicName.m_ppicInfo = 0;
    v10 = off_5D11C4;
    v5 = CScreenMode::GetInstance();
    ((CScreenMode *)v5)->AudioSetPosition(v10, 1);
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004B20C0
int UITitle_JDHY::HandleInput()
{
  int result; // eax
  gbTexture *v3; // ebp
  _PlugInfo **i; // edi
  int v5; // ebx
  int j; // edi
  unsigned int v7; // eax
  _PlugInfo **p_m_pbkInfo; // edi
  int v9; // ebx
  int v10; // ebx
  int k; // edi
  unsigned int v12; // eax
  void *v13; // ecx
  Actor *SaveDataManager; // eax
  int SaveData; // edi
  gbTexture *m_pbk2; // eax
  bool v17; // zf
  char *v18; // edi
  CScreenMode *Instance; // eax
  CScreenMode *v20; // eax
  CScreenMode *v21; // eax
  const void *v22; // [esp-0x8] [ebp-0x70]
  const void *v23; // [esp-0x8] [ebp-0x70]
  const void *v24; // [esp-0x8] [ebp-0x70]
  POINT pt; // [esp+0x10] [ebp-0x58]

  LOBYTE(result) = BYTE1(this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_bfocus);
  if ( !(_BYTE)result )
  {
    LOBYTE(result) = BYTE1(this->m_NoteItem[80].m_NoteLv[1].m_bvisible);
    if ( !(_BYTE)result )
    {
// [VFTABLE] LOBYTE(result) = BYTE1(this->m_NoteItem[81].m_NoteState.__vftable);
      if ( !(_BYTE)result )
      {
        result = ((GRPinput *)&g_Input)->GetCursorPos();
        v3 = 0;
        for ( i = &this->m_NoteItem[43].m_HeadShot[1].m_pbkInfo; ; i += 890 )
        {
          LOBYTE(result) = *((_BYTE *)&v3[1861] + (_DWORD)this);
          if ( (_BYTE)result )
          {
            result = PtInRect((const RECT *)i, pt);
            if ( result )
            {
              if ( g_Input.KeyInfo[0].PressTime == 1 )
              {
                result = g_Input.KeyInfo[0].Data & 0xF;
                if ( result == 1 )
                {
                  if ( *((_BYTE *)&this->m_NoteItem[43].m_HeadShot[1].m_ratioh
                       + (unsigned int)this->m_NoteItem[79].m_NotePicName.m_disablepic) )
                  {
                    v5 = 0;
                    for ( j = 0; j < 5; ++j )
                    {
                      v7 = 3560 * (int)this->m_NoteItem[79].m_NotePicName.m_disablepic;
                      if ( this->m_NoteItem[v7 / 0xDE8 + 44].m_NoteItemBk.m_caption[v5 + 108] )
                      {
                        (**(void ( ***)(char *, int))((char *)&this->m_NoteItem[43].m_NoteMoney.m_id
                                                              + j * 152
                                                              + v7))(
                          (char *)&this->m_NoteItem[43].m_NoteMoney.m_id + j * 152 + v7,
                          1);
                        (*(void ( **)(void **, _DWORD))this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic
                                                                                + 43].m_NoteLv[j + 4].m_id)(
                          &this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 43].m_NoteLv[j + 4].m_id,
                          0);
                      }
                      ++v5;
                    }
                  }
                  this->m_NoteItem[79].m_NotePicName.m_disablepic = v3;
                  p_m_pbkInfo = &this->m_NoteItem[44].m_HeadShot_NO_SEL[4].m_pbkInfo;
                  v9 = 36;
                  do
                  {
                    sub_445E50((int)(p_m_pbkInfo - 810));
                    ((void ( *)(_PlugInfo **, _DWORD))(*p_m_pbkInfo)->filepos)(p_m_pbkInfo, 0);
                    p_m_pbkInfo += 890;
                    --v9;
                  }
                  while ( v9 );
                  sub_445E50((int)&this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 43].m_HeadShot[1].m_disablepicInfo);
                  ((void ( *)(_PlugInfo **, int))this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic
                                                                          + 44].m_HeadShot_NO_SEL[4].m_pbkInfo->filepos)(
                    &this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 44].m_HeadShot_NO_SEL[4].m_pbkInfo,
                    1);
                  v10 = 0;
                  for ( k = 0; k < 5; ++k )
                  {
                    v12 = 3560 * (int)this->m_NoteItem[79].m_NotePicName.m_disablepic;
                    if ( this->m_NoteItem[v12 / 0xDE8 + 44].m_NoteItemBk.m_caption[v10 + 108] )
                    {
                      (**(void ( ***)(char *, _DWORD))((char *)&this->m_NoteItem[43].m_NoteMoney.m_id
                                                               + k * 152
                                                               + v12))(
                        (char *)&this->m_NoteItem[43].m_NoteMoney.m_id + k * 152 + v12,
                        0);
                      (*(void ( **)(void **, int))this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic
                                                                           + 43].m_NoteLv[k + 4].m_id)(
                        &this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 43].m_NoteLv[k + 4].m_id,
                        1);
                    }
                    ++v10;
                  }
                  v13 = off_5D11B8;
                  goto LABEL_37;
                }
                if ( result == 2 )
                  break;
              }
            }
          }
          v3 = (gbTexture *)((char *)v3 + 1);
          if ( (int)v3 >= 36 )
            return result;
        }
        this->m_NoteItem[79].m_NotePicName.m_disablepicInfo = (_PlugInfo *)v3;
        SaveDataManager = (Actor *)GetSaveDataManager();
        SaveData = ((Actor *)SaveDataManager)->LoadSaveData((char *)v3);
        m_pbk2 = this->m_NoteItem[79].m_NotePicName.m_pbk2;
        if ( m_pbk2 )
        {
          result = (int)&m_pbk2[-1].nLevels + 3;
          if ( result )
            return result;
          if ( ((UIScene *)"m04")->ProcessInput(0) || ((UIScene *)"m05")->ProcessInput(0) )
          {
            sprintf(&this->buf[16], "\\n        %s", (const char *)dword_DDC13C);
            ((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype)->SetEnable((int)&this->buf[16], 0);
            ((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetByte(1);
            v22 = off_5D11C0;
            Instance = CScreenMode::GetInstance();
            ((CScreenMode *)Instance)->AudioSetPosition(v22, 1);
            return result;
          }
          v17 = SaveData == 0;
          v18 = &this->buf[16];
          if ( !v17 )
          {
            sprintf(v18, "\\n      %s", (const char *)dword_DD4E3C);
LABEL_34:
            ((UICaption *)&this->m_NoteItem[80].m_NoteID.m_fonttype)->SetEnable((int)v18, 0);
            ((UIRoleSelect *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->SetByte(0);
            ((GRPinput *)&g_Input)->Reset();
            v23 = off_5D11C0;
            v20 = CScreenMode::GetInstance();
            ((CScreenMode *)v20)->AudioSetPosition(v23, 1);
            return result;
          }
          sprintf(&this->buf[16], "\\n %s", (const char *)dword_DD4F3C);
          ((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype)->SetEnable((int)&this->buf[16], 0);
          ((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetByte(1);
        }
        else
        {
          v17 = SaveData == 0;
          v18 = &this->buf[16];
          if ( !v17 )
          {
            sprintf(v18, "\\n      %s", (const char *)dword_DD513C);
            goto LABEL_34;
          }
          sprintf(&this->buf[16], "\\n %s", (const char *)dword_DD523C);
          ((UICaption *)&this->m_NoteItem[80].m_NoteID.m_fonttype)->SetEnable((int)&this->buf[16], 0);
          ((UIRoleSelect *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->SetByte(0);
        }
        ((GRPinput *)&g_Input)->Reset();
        v13 = off_5D11C0;
LABEL_37:
        v24 = v13;
        v21 = CScreenMode::GetInstance();
        ((CScreenMode *)v21)->AudioSetPosition(v24, 1);
      }
    }
  }
  return result;
}

// 0x004B2750
FILE * UITitle_JDHY::SaveData(double Data, int nVal)
{
  Actor *SaveDataManager; // eax
  FILE *v5; // edi
  void *v7; // esi
  double v8; // [esp-0x4] [ebp-0x94]
  int v9; // [esp+0x4] [ebp-0x8C]
  char Buffer[125]; // [esp+0x10] [ebp-0x80] BYREF
  __int16 v11; // [esp+0x8D] [ebp-0x3]
  char v12; // [esp+0x8F] [ebp-0x1]

  ((CGameData *)&g_gamefrm)->Load(0);
  LODWORD(v8) = LODWORD(Data);
  SaveDataManager = (Actor *)GetSaveDataManager();
  v5 = ((Actor *)SaveDataManager)->DoSceneTransition(v8, v9);
  if ( v5 )
  {
    v7 = g_pMiniGame3;
    if ( g_pMiniGame3 )
    {
      ((ArcPastScene *)g_pMiniGame3)->FreeChildList();
      operator delete(v7);
      g_pMiniGame3 = 0;
      g_bSceneLoaded_0 = 0;
      g_nMiniGameParam = 1;
      g_nMiniGameState = 0;
    }
    ((PAL3 *)"SOFTWARE\\SOFTSTAR\\PAL3_SAVE")->WriteRegistry((DWORD)"SEEK", LODWORD(Data));
    return v5;
  }
  else
  {
    memset(Buffer, 0, sizeof(Buffer));
    v11 = 0;
    v12 = 0;
    sprintf(Buffer, "\\n            %s", (const char *)dword_DDB83C);
    ((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype)->SetEnable((int)Buffer, 0);
    ((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetByte(1);
    return 0;
  }
}

// 0x004B2920
char UITitle_JDHY::SaveData(int Data)
{
  Actor *SaveDataManager; // eax
  char *v5; // ebx
  Actor *v6; // eax
  __int64 v7; // rax
  int v8; // esi
  int v9; // edi
  int v10; // edi
  char *v11; // esi
  int v12; // [esp+0x0] [ebp-0x2F8]
  char *v13; // [esp+0x14] [ebp-0x2E4]
  char *v14; // [esp+0x18] [ebp-0x2E0]
  float v16; // [esp+0x20] [ebp-0x2D8]
  _BYTE v17[5]; // [esp+0x24] [ebp-0x2D4]
  char v18[67]; // [esp+0x29] [ebp-0x2CF] BYREF
  int v19; // [esp+0x6C] [ebp-0x28C]
  char v20[257]; // [esp+0x70] [ebp-0x288] BYREF
  __int16 v21; // [esp+0x171] [ebp-0x187]
  char v22; // [esp+0x173] [ebp-0x185]
  char Buffer[125]; // [esp+0x174] [ebp-0x184] BYREF
  __int16 v24; // [esp+0x1F1] [ebp-0x107]
  char v25; // [esp+0x1F3] [ebp-0x105]
  char v26[257]; // [esp+0x1F4] [ebp-0x104] BYREF
  __int16 v27; // [esp+0x2F5] [ebp-0x3]
  char v28; // [esp+0x2F7] [ebp-0x1]

  memset(v26, 0, sizeof(v26));
  v27 = 0;
  v28 = 0;
  SaveDataManager = (Actor *)GetSaveDataManager();
  if ( ((Actor *)SaveDataManager)->LoadActorModel(Data) )
  {
    sprintf(v26, "Save\\PAL3_%04d.JPG", Data);
    ((gbImage2D *)(&g_PAL3_Instance.m_pAdditiveEffect2 + 5))->WriteJpegImage(v26, 100);
    v5 = (char *)this + 3560 * Data;
    v14 = v5;
    ((UIFrameWnd *)(v5 + 159616))->SetTextureByID((int)v26);
    (**((void ( ***)(int, int))v5 + 39904))((int)(v5 + 159616), 1);
    memset(v20, 0, sizeof(v20));
    v21 = 0;
    v22 = 0;
    v6 = (Actor *)GetSaveDataManager();
    ((Actor *)v6)->LoadSaveData((char *)Data);
    v7 = (__int64)v16;
    v8 = (int)v7 / 3600;
    v9 = (int)v7 / 60 % 60;
    v12 = (int)v7 % 60;
    if ( (int)v7 / 3600 < 100 )
      sprintf(v20, "%s %02d:%02d:%02d", dword_DC643C, v8, v9, v12);
    else
      sprintf(v20, "%s %03d:%02d:%02d", dword_DC643C, v8, v9, v12);
    ((UICaption *)(v5 + 158552))->SetEnable((int)v20, 0);
    sprintf(v20, "%s %d", (const char *)dword_DC633C, v19);
    ((UICaption *)(v5 + 158704))->SetEnable((int)v20, 0);
    sprintf(v20, "%s %s", (const char *)dword_DD933C, v18);
    ((UICaption *)(v5 + 159768))->SetEnable((int)v20, 0);
    v10 = 0;
    v13 = &::Buffer.m_partyActor.m_szTexture[4];
    v11 = v5 + 157784;
    do
    {
      if ( v17[v10] )
      {
        v5[v10 + 158544] = 1;
        (**(void ( ***)(char *, int))v11)(v11, 1);
        ((UIStatic *)v11)->CreateFromTemplate();
        ((UIStatic *)(UIStatic *)v11 - 5)->CreateFromTemplate();
        (**((void ( ***)(int, _DWORD))v11 - 190))((int)(v11 - 760), 0);
        sprintf(v20, "%d %s", *(_DWORD *)v13, byte_DC6A3C);
        ((UICaption *)(v11 + 1072))->SetEnable((int)g_szSceneUIText, 1);
        v5 = v14;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))v11)(v11, 0);
        (**((void ( ***)(int, _DWORD))v11 - 190))((int)(v11 - 760), 0);
        v5[v10 + 158544] = 0;
      }
      ++v10;
      v11 += 152;
      v13 += 1408;
    }
    while ( (int)v13 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[135] );
    ((ChoseCompose *)this)->LayoutItem(Data, *((_DWORD *)v5 + 39090), *((_DWORD *)v5 + 39091), *((_DWORD *)v5 + 39092), *((_DWORD *)v5 + 39093));
    return ((PAL3 *)"SOFTWARE\\SOFTSTAR\\PAL3_SAVE")->WriteRegistry((DWORD)"SEEK", Data);
  }
  else
  {
    memset(Buffer, 0, sizeof(Buffer));
    v24 = 0;
    v25 = 0;
    sprintf(Buffer, "\\n            %s", (const char *)dword_DDB73C);
    ((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype)->SetEnable((int)Buffer, 0);
    ((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetByte(1);
    return ((char ( *)(_PlugInfo **, _DWORD))this->m_NoteItem[Data + 44].m_HeadShot_NO_SEL[4].m_pbkInfo->filepos)(
             &this->m_NoteItem[Data + 44].m_HeadShot_NO_SEL[4].m_pbkInfo,
             0);
  }
}

// 0x004B2C70
void UITitle_JDHY::RenderSlotEffects()
{
  int i; // edi
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v3);
  if ( *((_BYTE *)&this->m_NoteItem[42].m_NotePic.m_pbkInfo + (unsigned int)this->m_NoteItem[42].m_NotePic.m_ppicInfo) )
  {
    for ( i = 0; i < 16; ++i )
    {
// [IDA_MISID]       if ( ((Concurrency *)(&this->m_NoteItem[0].m_NotePic.m_fontcolor + 2336 * (int)this->m_NoteItem[42].m_NotePic.m_ppicInfo + 146 * i))->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)(&this->m_NoteItem[0].m_NotePic.m_fontcolor
                                           + 2336 * (int)this->m_NoteItem[42].m_NotePic.m_ppicInfo
                                           + 146 * i))->Apply();
// [IDA_MISID]       if ( ((Concurrency *)(&this->m_NoteItem[21].m_NoteLv[4].m_nTextW + 2336 * (int)this->m_NoteItem[42].m_NotePic.m_ppicInfo + 146 * i))->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)(&this->m_NoteItem[21].m_NoteLv[4].m_nTextW
                                           + 2336 * (int)this->m_NoteItem[42].m_NotePic.m_ppicInfo
                                           + 146 * i))->Apply();
    }
  }
}

// 0x004B2D20
int UITitle_JDHY::HandleNavigation()
{
  int result; // eax
  gbTexture *v3; // eax
  _PlugInfo **p_m_pbkInfo; // edi
  int v5; // ebx
  gbTexture *v6; // eax
  _PlugInfo **v7; // edi
  int v8; // ebx
  Actor *SaveDataManager; // eax
  int SaveData; // edi
  gbTexture *m_pbk2; // eax
  bool v12; // zf
  char *v13; // edi
  CScreenMode *Instance; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  gbTexture *m_disablepic; // [esp-0x8] [ebp-0x68]
  const void *v18; // [esp-0x8] [ebp-0x68]
  const void *v19; // [esp-0x8] [ebp-0x68]
  const void *v20; // [esp-0x8] [ebp-0x68]

  LOBYTE(result) = BYTE1(this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_bfocus);
  if ( !(_BYTE)result )
  {
    LOBYTE(result) = BYTE1(this->m_NoteItem[80].m_NoteLv[1].m_bvisible);
    if ( !(_BYTE)result )
    {
// [VFTABLE] LOBYTE(result) = BYTE1(this->m_NoteItem[81].m_NoteState.__vftable);
      if ( !(_BYTE)result )
      {
        result = g_Input.KeyInfo[5].PressTime;
        if ( g_Input.KeyInfo[5].PressTime == 1 )
        {
          v3 = (gbTexture *)((char *)&this->m_NoteItem[79].m_NotePicName.*((_DWORD *)m_disablepic) + 1);
          this->m_NoteItem[79].m_NotePicName.m_disablepic = v3;
          if ( (int)v3 > 35 )
            this->m_NoteItem[79].m_NotePicName.m_disablepic = (gbTexture *)35;
          p_m_pbkInfo = &this->m_NoteItem[44].m_HeadShot_NO_SEL[4].m_pbkInfo;
          v5 = 36;
          do
          {
            sub_445E50((int)(p_m_pbkInfo - 810));
            ((void ( *)(_PlugInfo **, _DWORD))(*p_m_pbkInfo)->filepos)(p_m_pbkInfo, 0);
            p_m_pbkInfo += 890;
            --v5;
          }
          while ( v5 );
          if ( (int)this->m_NoteItem[79].m_NotePicName.m_disablepic >= (int)&this->m_NoteItem[79].m_NotePicName.m_ppicInfo->name[1] )

LABEL_11:
          sub_445E50((int)&this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 43].m_HeadShot[1].m_disablepicInfo);
          return ((int ( *)(_PlugInfo **, int))this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic
                                                                        + 44].m_HeadShot_NO_SEL[4].m_pbkInfo->filepos)(
                   &this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 44].m_HeadShot_NO_SEL[4].m_pbkInfo,
                   1);
        }
        if ( g_Input.KeyInfo[4].PressTime == 1 )
        {
          v6 = (gbTexture *)((char *)this->m_NoteItem[79].m_NotePicName.m_disablepic - 1);
          this->m_NoteItem[79].m_NotePicName.m_disablepic = v6;
          if ( (int)v6 < 0 )
          {
            ((CScreenMode *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->SetProgress(0.0);
            this->m_NoteItem[79].m_NotePicName.m_disablepic = 0;
          }
          v7 = &this->m_NoteItem[44].m_HeadShot_NO_SEL[4].m_pbkInfo;
          v8 = 36;
          do
          {
            sub_445E50((int)(v7 - 810));
            ((void ( *)(_PlugInfo **, _DWORD))(*v7)->filepos)(v7, 0);
            v7 += 890;
            --v8;
          }
          while ( v8 );
          if ( (int)this->m_NoteItem[79].m_NotePicName.m_disablepic < (int)this->m_NoteItem[79].m_NotePicName.m_ppicInfo )

          goto LABEL_11;
        }
        if ( g_Input.KeyInfo[10].PressTime == 1 )
        {
          if ( dword_D8BBEC != 2 || g_bRoleSystem_5CEFA9 )
            return this->OnMessage(1001,
                     &byte_A00704,
                     0);
          sprintf(&this->buf[16], "\\n        %s", (const char *)dword_DD8A3C);
          ((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype)->SetEnable((int)&this->buf[16], 0);
          ((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetByte(1);
          goto LABEL_40;
        }
        if ( g_Input.KeyInfo[9].PressTime == 1 )
          return this->OnMessage(1001,
                   byte_A00705,
                   0);
        if ( g_Input.KeyInfo[7].PressTime == 1 )
        {
          m_disablepic = this->m_NoteItem[79].m_NotePicName.m_disablepic;
          this->m_NoteItem[79].m_NotePicName.m_disablepicInfo = (_PlugInfo *)m_disablepic;
          SaveDataManager = (Actor *)GetSaveDataManager();
          SaveData = ((Actor *)SaveDataManager)->LoadSaveData((char *)m_disablepic);
          m_pbk2 = this->m_NoteItem[79].m_NotePicName.m_pbk2;
          if ( m_pbk2 )
          {
            result = (int)&m_pbk2[-1].nLevels + 3;
            if ( result )
              return result;
            if ( ((UIScene *)"m04")->ProcessInput(0) || ((UIScene *)"m05")->ProcessInput(0) )
            {
              sprintf(&this->buf[16], "\\n        %s", (const char *)dword_DDC13C);
              ((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype)->SetEnable((int)&this->buf[16], 0);
              ((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetByte(1);
              v18 = off_5D11C0;
              Instance = CScreenMode::GetInstance();
              ((CScreenMode *)Instance)->AudioSetPosition(v18, 1);
              return result;
            }
            v12 = SaveData == 0;
            v13 = &this->buf[16];
            if ( !v12 )
            {
              sprintf(v13, "\\n      %s", (const char *)dword_DD4E3C);
LABEL_37:
              ((UICaption *)&this->m_NoteItem[80].m_NoteID.m_fonttype)->SetEnable((int)v13, 0);
              ((UIRoleSelect *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->SetByte(0);
              ((GRPinput *)&g_Input)->Reset();
              v19 = off_5D11C0;
              v15 = CScreenMode::GetInstance();
              ((CScreenMode *)v15)->AudioSetPosition(v19, 1);
              return result;
            }
            sprintf(&this->buf[16], "\\n %s", (const char *)dword_DD4F3C);
            ((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype)->SetEnable((int)&this->buf[16], 0);
            ((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetByte(1);
          }
          else
          {
            v12 = SaveData == 0;
            v13 = &this->buf[16];
            if ( !v12 )
            {
              sprintf(v13, "\\n      %s", (const char *)dword_DD513C);
              goto LABEL_37;
            }
            sprintf(&this->buf[16], "\\n %s", (const char *)dword_DD523C);
            ((UICaption *)&this->m_NoteItem[80].m_NoteID.m_fonttype)->SetEnable((int)&this->buf[16], 0);
            ((UIRoleSelect *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->SetByte(0);
          }
          ((GRPinput *)&g_Input)->Reset();
LABEL_40:
          v20 = off_5D11C0;
          v16 = CScreenMode::GetInstance();
          ((CScreenMode *)v16)->AudioSetPosition(v20, 1);
        }
      }
    }
  }
  return result;
}

// 0x004B3100
int UITitle_JDHY::ForwardHitTest()
{
  __int64 v3; // rax
  int v4; // ebx
  int v5; // ebp
  gbTexture *m_pbk2; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v8; // eax
  int v9; // [esp-0x10] [ebp-0x14]
  const void *v10; // [esp-0x8] [ebp-0xC]
  const void *v11; // [esp-0x8] [ebp-0xC]
  int a2; // [esp+0x8] [ebp+0x4]
  int a3; // [esp+0xC] [ebp+0x8]

  if ( *(_DWORD *)&this->m_NoteItem[79].m_NotePicName.m_mouseoff )
    return 1;
  v3 = (__int64)g_fGameTimer;
  v4 = (int)v3 / 3600;
  v5 = (int)v3 / 60 % 60;
  v9 = (int)v3 % 60;
  if ( (int)v3 / 3600 < 100 )
    sprintf(&this->buf[16], "%02d:%02d:%02d", v4, v5, v9);
  else
    sprintf(&this->buf[16], "%03d:%02d:%02d", v4, v5, v9);
  ((UICaption *)&this->m_NoteItem[0].m_NoteLv[3].m_fontcolor)->SetEnable((int)&this->buf[16], 0);
  sprintf(&this->buf[16], &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)&this->m_NoteItem[0].m_NoteLv[4].m_fontcolor)->SetEnable((int)&this->buf[16], 0);

  ((CScreenMode *)this)->GetMouseDelta();

  if ( !((UIParabolaCtrl *)&this->m_NoteItem[79].m_NotePicName.m_nTextW)->GetState() )
  {
    m_pbk2 = this->m_NoteItem[79].m_NotePicName.m_pbk2;
    if ( m_pbk2 )
    {
      if ( m_pbk2 == (gbTexture *)1 )
      {
        *(_DWORD *)&this->m_NoteItem[79].m_NotePicName.m_mouseoff = 1;
        v10 = off_5D11FC;
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v10, 1);
        return 1;
      }
    }
    else
    {
      this->SaveData((int)this->m_NoteItem[79].m_NotePicName.m_disablepic);
      v11 = off_5D11F8;
      v8 = CScreenMode::GetInstance();
      ((CScreenMode *)v8)->AudioSetPosition(v11, 1);
    }
  }
  if ( !((UIParabolaCtrl *)&this->m_NoteItem[80].m_NoteLv[1].m_textx)->GetState() )
    ((MainEquipUI *)this->m_OutFrameT.m_rect.top)->HandleMessage();
  return ((UIListBox *)this)->Update(a2, a3);
}

// 0x004B3270
int UITitle_JDHY::UpdateTextPosition()
{
  int v1; // ebx
  unsigned int v3; // eax
  int v4; // ebp
  _PlugInfo *v5; // ecx
  int *p_m_ppic; // edi
  int v7; // eax
  _PlugInfo **p_m_pbkInfo; // edi
  int v9; // ebx
  int v10; // ebx
  int i; // edi
  int result; // eax
  float fProgress; // [esp+0x0] [ebp-0x18]
  BYTE Data[4]; // [esp+0x14] [ebp-0x4] BYREF

  v1 = 0;
  *(_DWORD *)Data = 0;
  ReadRegistryString("SOFTWARE\\SOFTSTAR\\PAL3_SAVE", "SEEK", (char *)Data);
  v3 = *(_DWORD *)Data;
  if ( *(_DWORD *)Data >= 0x24u )
  {
    v3 = 35;
    *(_DWORD *)Data = 35;
  }
  v4 = 0;
  v5 = (_PlugInfo *)v3;
  if ( v3 <= 4 )
  {
    v3 = 0;
    *(_DWORD *)Data = 0;
  }
  else
  {
    v4 = 4;
  }
  this->m_NoteItem[79].m_NotePicName.m_disablepicInfo = v5;
  this->m_NoteItem[79].m_NotePicName.m_ppicInfo = (_PlugInfo *)(v3 - v4);
  this->m_NoteItem[79].m_NotePicName.m_disablepic = (gbTexture *)v5;
  this->m_NoteItem[79].m_NoteLv[1].m_rect.right = (LONG)v5 - v4;
  if ( (int)v5 - v4 < 31 )
  {
    this->m_NoteItem[79].m_NoteLv[1].m_rect.top = ((_DWORD)v5 - v4) * (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo;
  }
  else
  {
    this->m_NoteItem[79].m_NoteLv[1].m_rect.right = 31;
    this->m_NoteItem[79].m_NoteLv[1].m_rect.top = (__int64)*(float *)&this->m_NoteItem[79].m_NoteLv[0].m_disablepic;
  }
  fProgress = (float)this->m_NoteItem[79].m_NoteLv[1].m_rect.top;
  ((CScreenMode *)&this->m_NoteItem[79].m_NoteMoney.m_bcreateok)->SetProgress(fProgress);
  p_m_ppic = (int *)&this->m_NoteItem[43].m_HeadShot[1].m_ppic;
  do
  {
    v7 = *p_m_ppic - (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo * (*(_DWORD *)Data - v4);
    *p_m_ppic = v7;
    p_m_ppic[2] = (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo + v7;
    ((ChoseCompose *)this)->LayoutItem(v1++, *(p_m_ppic - 1), *p_m_ppic, p_m_ppic[1], p_m_ppic[2]);
    p_m_ppic += 890;
  }
  while ( v1 < 36 );

  p_m_pbkInfo = &this->m_NoteItem[44].m_HeadShot_NO_SEL[4].m_pbkInfo;
  v9 = 36;
  do
  {
    sub_445E50((int)(p_m_pbkInfo - 810));
    ((void ( *)(_PlugInfo **, _DWORD))(*p_m_pbkInfo)->filepos)(p_m_pbkInfo, 0);
    p_m_pbkInfo += 890;
    --v9;
  }
  while ( v9 );
  sub_445E50((int)&this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 43].m_HeadShot[1].m_disablepicInfo);
  ((void ( *)(_PlugInfo **, int))this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 44].m_HeadShot_NO_SEL[4].m_pbkInfo->filepos)(
    &this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 44].m_HeadShot_NO_SEL[4].m_pbkInfo,
    1);
  v10 = 0;
  for ( i = 0; i < 5; ++i )
  {
    result = 3560 * (int)this->m_NoteItem[79].m_NotePicName.m_disablepic;
    if ( this->m_NoteItem[44].m_NoteItemBk.m_caption[result + 108 + v10] )
    {
      (**(void ( ***)(char *, _DWORD))((char *)&this->m_NoteItem[43].m_NoteMoney.m_id + i * 152 + result))(
        (char *)&this->m_NoteItem[43].m_NoteMoney.m_id + i * 152 + result,
        0);
      result = (*(int ( **)(void **, int))this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic
                                                                   + 43].m_NoteLv[i + 4].m_id)(
                 &this->m_NoteItem[(int)this->m_NoteItem[79].m_NotePicName.m_disablepic + 43].m_NoteLv[i + 4].m_id,
                 1);
    }
    ++v10;
  }
  return result;
}

// 0x004B3470
int UITitle_JDHY::OnMessage()
{
  int i; // edi
  CScreenMode *Instance; // eax
  int AudioManager; // eax
  int v5; // edi
  _PlugInfo **p_m_pbkInfo; // esi
  int result; // eax
  CScreenMode *v8; // eax
  CScreenMode *v9; // eax
  LONG v10; // edi
  LONG top; // eax
  LONG right; // edx
  LONG v13; // edx
  CScreenMode *v14; // eax
  int v15; // eax
  double v16; // st7
  CScreenMode *v17; // eax
  gbAudioManager *v18; // eax
  float fProgressa; // [esp+0x0] [ebp-0x14]
  float fProgressb; // [esp+0x0] [ebp-0x14]
  float fProgressc; // [esp+0x0] [ebp-0x14]
  const void *fProgress; // [esp+0x0] [ebp-0x14]
  const void *fProgressd; // [esp+0x0] [ebp-0x14]
  float v24; // [esp+0x4] [ebp-0x10]
  int nVal; // [esp+0x18] [ebp+0x4]
  char *nMsg; // [esp+0x1C] [ebp+0x8]
  int nMsga; // [esp+0x1C] [ebp+0x8]
  int nMsgb; // [esp+0x1C] [ebp+0x8]
  int wParam; // [esp+0x20] [ebp+0xC]

  switch ( nVal )
  {
    case 1000:
      if ( nMsg )
      {
        for ( i = 0; i < 8; ++i )
          sub_4B43E0(i);
        ((UISceneMap *)this)->ShowPage();
        ((StateUI *)this)->SaveData();
        if ( g_bRoleSystem_5CEFA9 )
        {
          sub_445E50((int)&this->m_NoteItem[43].m_NoteItemBk.m_texarray.m_ptex[4]);
          this->m_NoteItem[79].m_NotePicName.m_pbk2 = 0;
        }
        else
        {
          sub_445E50((int)&this->m_NoteItem[43].m_NoteItemBk.m_texarray.m_ptex[4]);
          this->m_NoteItem[79].m_NotePicName.m_pbk2 = (gbTexture *)1;
        }

        *(_DWORD *)&this->m_NoteItem[79].m_NotePicName.m_mouseoff = 0;
        if ( (g_dwGameFlags & 4) != 0 )
        {
          Instance = CScreenMode::GetInstance();
          AudioManager = ((CScreenMode *)Instance)->GetAudioManager();
          v5 = AudioManager;
          if ( AudioManager )
          {
            fProgressa = *(float *)(AudioManager + 212) * 100.0;
            ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->SetProgress(fProgressa);
            fProgressb = *(float *)(v5 + 208) * 100.0;
            ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->SetProgress(fProgressb);
            fProgressc = *(float *)(v5 + 204) * 100.0;
            ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->SetProgress(fProgressc);
          }
        }
        else
        {
          ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[1].m_rect.bottom)->SetProgress(0.0);
          ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->SetProgress(0.0);
          ((CScreenMode *)&this->m_NoteItem[79].m_NoteLv[2].m_nTextW)->SetProgress(0.0);
        }
        p_m_pbkInfo = &this->m_NoteItem[42].m_NotePic.m_pbkInfo;
        *p_m_pbkInfo = 0;
        p_m_pbkInfo[1] = 0;
        UICursor::IRender();
        result = 1;
      }
      else
      {

        result = 1;
      }
      break;
    case 1001:
// [VFTABLE] if ( BYTE1(this->m_NoteItem[81].m_NoteState.__vftable)
// [VFTABLE]   || BYTE1(this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_bfocus) )
      {
LABEL_80:
        result = 1;
      }
      else if ( nMsg > byte_A00110 )
      {
        switch ( (unsigned int)nMsg )
        {
          case 0xA00701u:

            result = 1;
            break;
          case 0xA00702u:

            result = 1;
            break;
          case 0xA00704u:
            if ( this->m_NoteItem[79].m_NotePicName.m_pbk2 )
            {
              this->m_NoteItem[79].m_NotePicName.m_pbk2 = 0;


              *(_DWORD *)this->m_NoteItem[43].m_NoteItemBk.m_caption = 1;
              LOBYTE(this->m_NoteItem[43].m_NoteItemBk.m_disablepicInfo) = 1;
              *(_DWORD *)this->m_NoteItem[43].m_NoteID.m_text = 0;
              LOBYTE(this->m_NoteItem[43].m_NoteID.m_textx) = 0;
            }
            else
            {
              *(_DWORD *)this->m_NoteItem[43].m_NoteItemBk.m_caption = 1;
              LOBYTE(this->m_NoteItem[43].m_NoteItemBk.m_disablepicInfo) = 1;
            }
            fProgress = off_5D11E0;
            goto LABEL_35;
          case 0xA00705u:
            if ( this->m_NoteItem[79].m_NotePicName.m_pbk2 == (gbTexture *)1 )
            {
              *(_DWORD *)this->m_NoteItem[43].m_NoteID.m_text = 1;
              LOBYTE(this->m_NoteItem[43].m_NoteID.m_textx) = 1;
            }
            else
            {
              this->m_NoteItem[79].m_NotePicName.m_pbk2 = (gbTexture *)1;


              *(_DWORD *)this->m_NoteItem[43].m_NoteID.m_text = 1;
              LOBYTE(this->m_NoteItem[43].m_NoteID.m_textx) = 1;
              *(_DWORD *)this->m_NoteItem[43].m_NoteItemBk.m_caption = 0;
              LOBYTE(this->m_NoteItem[43].m_NoteItemBk.m_disablepicInfo) = 0;
            }
            fProgress = off_5D11E0;
            goto LABEL_35;
          case 0xA00708u:
            LOBYTE(this->m_NoteItem[79].m_NotePicName.m_FVF) = 1;
            sprintf(&this->buf[16], "\\n        %s", (const char *)dword_DD383C);
            ((UICaption *)&this->m_NoteItem[80].m_NoteLv[4].m_textx)->SetEnable((int)&this->buf[16], 0);
            ((UIRoleSelect *)&this->m_NoteItem[80].m_NoteLv[1].m_textx)->SetByte(1);
            fProgress = off_5D11C0;
            goto LABEL_35;
          default:
            goto LABEL_36;
        }
      }
      else
      {
        if ( nMsg != byte_A00110 )
        {
          switch ( (unsigned int)nMsg )
          {
            case 0xA00102u:
            case 0xA00103u:
            case 0xA00104u:
            case 0xA00105u:
            case 0xA00106u:
            case 0xA00107u:
            case 0xA00108u:
              break;
            default:
              goto LABEL_36;
          }
        }
        fProgressd = off_5D11B8;
        v8 = CScreenMode::GetInstance();
        ((CScreenMode *)v8)->AudioSetPosition(fProgressd, 1);
        ((MainEquipUI *)this->m_OutFrameT.m_rect.top)->HandleMessage();
        result = 1;
      }
      break;
    case 1002:
      switch ( (unsigned int)nMsg )
      {
        case 0xA00102u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = 0;
          if ( LOBYTE(this->m_NoteItem[42].m_NotePic.m_pbkInfo) )
            goto LABEL_70;
          sub_4B43E0(0);
          result = 1;
          break;
        case 0xA00103u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)1;
          if ( BYTE1(this->m_NoteItem[42].m_NotePic.m_pbkInfo) )
            goto LABEL_70;
          sub_4B43E0(1);
          result = 1;
          break;
        case 0xA00104u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)2;
          if ( BYTE2(this->m_NoteItem[42].m_NotePic.m_pbkInfo) )
            goto LABEL_70;
          sub_4B43E0(2);
          result = 1;
          break;
        case 0xA00105u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)3;
          if ( HIBYTE(this->m_NoteItem[42].m_NotePic.m_pbkInfo) )
            goto LABEL_70;
          sub_4B43E0(3);
          result = 1;
          break;
        case 0xA00106u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)5;
          if ( BYTE1(this->m_NoteItem[42].m_NotePic.m_ppic) )
            goto LABEL_70;
          sub_4B43E0(5);
          result = 1;
          break;
        case 0xA00107u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)6;
          if ( BYTE2(this->m_NoteItem[42].m_NotePic.m_ppic) )
            goto LABEL_70;
          sub_4B43E0(6);
          result = 1;
          break;
        case 0xA00108u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)4;
          if ( LOBYTE(this->m_NoteItem[42].m_NotePic.m_ppic) )
            goto LABEL_70;
          sub_4B43E0(4);
          result = 1;
          break;
        case 0xA00109u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)7;
          if ( !HIBYTE(this->m_NoteItem[42].m_NotePic.m_ppic) )
            sub_4B43E0(7);
          goto LABEL_70;
        default:
LABEL_70:
          result = 1;
          break;
      }
      break;
    case 1003:
      switch ( (unsigned int)nMsg )
      {
        case 0xA00102u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = 0;
          LOBYTE(this->m_NoteItem[42].m_NotePic.m_pbkInfo) = 0;
          result = 1;
          break;
        case 0xA00103u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)1;
          BYTE1(this->m_NoteItem[42].m_NotePic.m_pbkInfo) = 0;
          result = 1;
          break;
        case 0xA00104u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)2;
          BYTE2(this->m_NoteItem[42].m_NotePic.m_pbkInfo) = 0;
          result = 1;
          break;
        case 0xA00105u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)3;
          HIBYTE(this->m_NoteItem[42].m_NotePic.m_pbkInfo) = 0;
          result = 1;
          break;
        case 0xA00106u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)5;
          BYTE1(this->m_NoteItem[42].m_NotePic.m_ppic) = 0;
          result = 1;
          break;
        case 0xA00107u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)6;
          BYTE2(this->m_NoteItem[42].m_NotePic.m_ppic) = 0;
          result = 1;
          break;
        case 0xA00108u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)4;
          LOBYTE(this->m_NoteItem[42].m_NotePic.m_ppic) = 0;
          result = 1;
          break;
        case 0xA00109u:
          this->m_NoteItem[42].m_NotePic.m_ppicInfo = (_PlugInfo *)7;
          HIBYTE(this->m_NoteItem[42].m_NotePic.m_ppic) = 0;
          goto LABEL_80;
        default:
          goto LABEL_80;
      }
      break;
    case 1019:
      if ( nMsg == byte_A00709 )
      {
        nMsgb = *(int *)&this->m_NoteItem[79].m_NoteLv[2].m_text[12];
        v17 = CScreenMode::GetInstance();
        v18 = (gbAudioManager *)((CScreenMode *)v17)->GetAudioManager();
        if ( v18 )
        {
          v24 = *(float *)&nMsgb * 0.0099999998;
          ((gbAudioManager *)v18)->SetMusicMasterVolume(v24);
        }
      }
      else if ( nMsg - byte_A00709 == 7 )
      {
        nMsga = SLODWORD(this->m_NoteItem[79].m_NoteLv[4].m_ratiow);
        v14 = CScreenMode::GetInstance();
        v15 = ((CScreenMode *)v14)->GetAudioManager();
        if ( v15 )
        {
          v16 = *(float *)&nMsga * 0.0099999998;
          *(float *)(v15 + 208) = v16;
          *(float *)(v15 + 204) = v16;
          return 1;
        }
      }
      else if ( nMsg - byte_A00709 == 771575 )
      {
        v10 = (__int64)*(float *)&this->m_NoteItem[79].m_NoteLv[0].m_disablepicInfo;
        top = this->m_NoteItem[79].m_NoteLv[1].m_rect.top;
        if ( v10 <= top )
        {
          if ( v10 < top
            && v10 <= (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo
                    * (this->m_NoteItem[79].m_NoteLv[1].m_rect.right - 1) )
          {

            result = 1;
            v13 = this->m_NoteItem[79].m_NoteLv[1].m_rect.right - 1;
            this->m_NoteItem[79].m_NoteLv[1].m_rect.top = v10;
            this->m_NoteItem[79].m_NoteLv[1].m_rect.right = v13;
            if ( v13 <= 1 )
            {
              this->m_NoteItem[79].m_NoteLv[1].m_rect.right = 1;
              return result;
            }
          }
        }
        else if ( v10 >= this->m_NoteItem[79].m_NoteLv[1].m_rect.right
                       * (int)this->m_NoteItem[79].m_NotePicName.m_pbkInfo )
        {

          right = this->m_NoteItem[79].m_NoteLv[1].m_rect.right;
          this->m_NoteItem[79].m_NoteLv[1].m_rect.top = v10;
          this->m_NoteItem[79].m_NoteLv[1].m_rect.right = right + 1;
          if ( right + 1 > 36 )
          {
            this->m_NoteItem[79].m_NoteLv[1].m_rect.right = 36;
            return 1;
          }
        }
      }
      result = 1;
      break;
    case 1021:
      if ( nMsg == &byte_A00704 )
      {
        sprintf(&this->buf[16], "\\n        %s", (const char *)dword_DD8A3C);
        ((UICaption *)&this->m_NoteItem[80].m_HeadShot[2].m_fonttype)->SetEnable((int)&this->buf[16], 0);
        ((UIRoleSelect *)&this->m_NoteItem[80].m_HeadShot_NO_SEL[4].m_fonttype)->SetByte(1);
        fProgress = off_5D11C0;
LABEL_35:
        v9 = CScreenMode::GetInstance();
        ((CScreenMode *)v9)->AudioSetPosition(fProgress, 1);
      }
LABEL_36:
      result = 1;
      break;
    default:
      result = ((PalScript *)this)->OnMessage(nVal, (int)nMsg, wParam);
      break;
  }
  return result;
}
