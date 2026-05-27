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
