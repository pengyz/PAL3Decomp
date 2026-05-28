#pragma once
// Game constants with confirmed semantic meaning from binary analysis
// Only add entries when the semantic is clearly understood

// === Role IDs (GDB角色编号) ===
const int ROLEID_JINGTIAN  = 301;  // 景天 (protagonist)
const int ROLEID_XUEJIAN   = 302;  // 雪见
const int ROLEID_LONGKUI   = 303;  // 龙葵
const int ROLEID_ZIXUAN    = 304;  // 紫萱
const int ROLEID_CHANGQING = 305;  // 长卿
const int ROLEID_HUAYING   = 306;  // 花楹
const int ROLEID_CHONGLOU  = 311;  // 重楼

// === Config Constants ===
const int DEFAULT_FRAME_RATE      = 35;  // FPS cap
const int INITIAL_EVENT_ID        = 31;  // g_nCurrentEventId start value
const int DEFAULT_ROLE_INIT_LEVEL = 20;  // all roles start at level 20
const int MAX_NPC_COUNT           = 20;  // NPC::InitAll parameter
const int TEAM_TRIPLE_STRIDE      = 12;  // team array entry = {roleID, subgroup, count}

// === Magic Constants ===
const int MAGIC_SLOT_INIT    = 0x03030303;  // 4 slots × 3 magic types
const int SUBGROUP_FLAG_MASK = 0x2D0003;    // encoded subgroup+flag value
const int SUBGROUP_FLAG_ALT  = 0x0F0003;    // alternate encoded subgroup+flag

// === TeamConfigSlot layout ===
// _todo_694 and _todo_C00 arrays contain 6 TeamConfigSlots, stride=52 ints each
const int TCS_STRIDE     = 52;  // ints per slot (208 bytes)
const int TCS_NUM_SLOTS  = 6;
const int TCS_SKILL_ID   = 3;   // skill triplet: {resourceID=82xxx, enable=1, gdbNum}
const int TCS_SKILL_EN   = 4;
const int TCS_SKILL_NUM  = 5;
const int TCS_SKILL_RID  = 6;   // skill resource ID (CScreenMode::InitPlayerData)
const int TCS_POS_X      = 10;  // default position X
const int TCS_POS_Y      = 11;  // default position Y
const int TCS_TEAM_SIZE  = 37;  // team member count
const int TCS_CHAR_BASE  = 38;  // 5 char init values [38..42]
const int TCS_FORM_BASE  = 43;  // 7 formation flags [43..49]

// === _todo_UI5908_ext layout ===
// Low indices: team 4 config (FullInit only)
const int UI5_TEAM_SIZE  = 36;  // team member count (13)
const int UI5_CHAR_BASE  = 37;  // 5 char init values [37..41]
const int UI5_FORM_BASE  = 42;  // 7 formation flags [42..48]
const int UI5_MONSTER_ID = 63;  // monster/config ID (4341)
const int UI5_SKILL_ID   = 106; // skill triplet: {82001, 1, gdbNum}
const int UI5_SKILL_EN   = 107;
const int UI5_SKILL_NUM  = 108;
const int UI5_EXT_FORM   = 126; // 7 extra formation flags [126..132]

// === _todo_UI4540_ext layout ===
const int UI3_TEAM_SIZE  = 26;  // team member count (10)
const int UI3_CHAR_BASE  = 27;  // 5 char init values [27..31]
const int UI3_FORM_BASE  = 32;  // 7 formation flags [32..38]
const int UI3_MISC_ID    = 53;  // misc resource ID (1943)

// === FightItem struct field constants (GDB item/skill data) ===
const int FIGHTITEM_TYPE_LEARN_SKILL = 11;  // FightItem.type == 11: item teaches skill on use
const int FIGHTITEM_LEARN_SLOT_0     = 0;   // user[0] = protagonist (景天)
const int FIGHTITEM_ID_SPECIAL_A     = 6602; // item type ID: special/plot item type A
const int FIGHTITEM_ID_SPECIAL_B     = 6603; // item type ID: special/plot item type B

// === GDB Item/Skill IDs used in PalScript opcode handlers ===
// PalScript::Op_CameraFocusPoint handles "getitem" - item acquisition that teaches skills.
// case values = item type ID, paired skill IDs learned when item is used:
const int GDB_ITEMTYPE_LEARN_SKILL_0 = 6119;  // teaches GDB skill 8146
const int GDB_ITEMTYPE_LEARN_SKILL_1 = 6120;  // teaches GDB skill 8147
const int GDB_ITEMTYPE_LEARN_SKILL_3 = 6122;  // teaches GDB skill 8149
const int GDB_ITEMTYPE_LEARN_SKILL_4 = 6123;  // teaches GDB skill 8150 + 6427
const int GDB_ITEMTYPE_LEARN_SKILL_5 = 6124;  // teaches GDB skill 8151
const int GDB_ITEMTYPE_LEARN_SKILL_6 = 6125;  // teaches GDB skill 8152

const int GDB_SKILLID_LEARN_0  = 8146;  // learned from item type 6119
const int GDB_SKILLID_LEARN_1  = 8147;  // learned from item type 6120
const int GDB_SKILLID_LEARN_3  = 8149;  // learned from item type 6122
const int GDB_SKILLID_LEARN_4A = 8150;  // learned from item type 6123 (primary)
const int GDB_SKILLID_LEARN_4B = 6427;  // learned from item type 6123 (secondary)
const int GDB_SKILLID_LEARN_5  = 8151;  // learned from item type 6124
const int GDB_SKILLID_LEARN_6  = 8152;  // learned from item type 6125

// === _todo_C00 layout (TeamConfigSlot array) ===
const int TC1_TEAM_SIZE  = 94;  // slot 1 + 42
const int TC1_CHAR_BASE  = 95;  // [95..99]
const int TC1_FORM_BASE  = 100; // [100..106]
const int TC1_SKILL_ID   = 164; // slot 3 + 8
const int TC1_SKILL_EN   = 165;
const int TC1_SKILL_NUM  = 166;
