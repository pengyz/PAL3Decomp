#pragma once
// Auto-generated: PAL_GDB

#include "ComboAttack.h"
#include "FightItem.h"
#include "FightSkill.h"
#include "OutFile.h"
#include "RoleAtt.h"
#include "gbengine/gbGeomNode.h"

class MainEquipUI;

class PAL_GDB {
public:
    OutFile m_head; // +0x0
    char _gap_004[156]; // +0x4
    RoleAtt m_RoleData[200]; // +0xA0
    char _gap_3C0[169600]; // +0x3C0
    FightSkill m_SkillData[300]; // +0x29A40
    char _gap_29EF0[226800]; // +0x29EF0
    FightItem m_ItemData[512]; // +0x614E0
    char _gap_61CE0[407552]; // +0x61CE0
    ComboAttack m_ComboData[10]; // +0xC54E0
    char _gap_C5508[6320]; // +0xC5508
    int i; // +0xC6DB8
    // total size: 0xC6DBC (814524)

    char LoadLanguage(char *path); // 0x00457410
    void RefreshSkillNumbers(); // 0x00457F00
    int UpdateSkillPanel(); // 0x00460A90
    MainEquipUI * ResetAllData(); // 0x00478C00
    PAL_GDB(); // 0x00478E00
    void _PAL_GDB(int nVal); // 0x00478FD0
    bool GDB_LoadFile(); // 0x00479040
    int GDB_GetRole(unsigned int ID); // 0x00479050
    int GDB_GetRoleNum(int nVal); // 0x00479080
    int GDB_GetSkillNum(int nVal); // 0x00479130
    unsigned int GDB_GetSkillID(); // 0x004791A0
    int GetItemID(unsigned int index); // 0x004791B0
    int GDB_GetItemNum(int nVal); // 0x004791E0
    unsigned int GDB_GetComboID(); // 0x004792C0
    char LoadByType(unsigned int dwVal, char pData); // 0x0049C2C0
    int SelectBestTarget(int nVal); // 0x0049C660
    BOOL IsValidItem(int nItemID); // 0x0049CA70
    char * SetupSkillConfig(); // 0x004E50B0
    int LoadConfigFromINI(); // 0x004E5500
    char FindItemByID(int nVal, int *p_DWORD); // 0x004E56E0
    int GetItemPrice(int nVal); // 0x004E5710
    int GetItemWeight(int nVal); // 0x004E5760
    int GetItemData(int nVal); // 0x004E57B0
    int PartySetupDialogProc(HWND hDlg, UINT pData, WPARAM a4, LPARAM a5); // 0x004E5800
    LRESULT RefreshPartyDialog(); // 0x004E5B20
    int PopulateAvailableRoles(); // 0x004E5E00
    int * UpdateInventorySlots(); // 0x004E5F60
    int DlgProcCamera(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam); // 0x004E5FF0
    LRESULT ShowDetailPanel(HWND hDlg); // 0x004EC1F0
    int LoadSkillData(); // 0x004ED8C0
    bool IsItemConsumable(int nItemId); // 0x004F69F0
    bool IsItemEquipment(int nItemId); // 0x004F6A20
    bool IsRoleAlive(int nRoleId); // 0x004F6A40
    bool IsRoleDead(int nRoleId); // 0x004F6A60
    bool IsRoleAlive2(int nVal); // 0x004F6A80
    bool IsItemConsumed(int nItemId); // 0x004F6AB0
    bool GetSkillLevel(int nVal); // 0x004F6AD0
    bool GetSkillType(int nVal); // 0x004F6B20
    bool IsSkillUsable(int nVal); // 0x004F6B70
    bool IsSkillEmpty(int nVal); // 0x004F6BB0
    char SearchAllItems(int nVal, int *p_DWORD, int *pnVal, int *p_DWORD2); // 0x004F6BE0
    char SearchItemLoop(int nVal, int nVal2, int *p_DWORD, int *pnVal); // 0x004F6C60
    char IsRoleSkillValid(unsigned int *pdwVal, int nVal); // 0x004F6D30
    char IterateInventory(int *p_DWORD); // 0x004F6E80
    char BuildItemArray(int nVal); // 0x004F6FB0
    gbGeomNode * RefreshPartyStats(); // 0x00526300
    int InitSkillDisplay(int nVal); // 0x00528650
    char * SetDefaultEquipment(); // 0x005294C0
    BOOL SetupSkillData(int nVal); // 0x0052ECE0
};
