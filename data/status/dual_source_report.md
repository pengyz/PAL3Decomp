# 双源 diff 报表（只读）

> **口径 = 往返保真**（非「IDA vs 注解」）：`asm/pal3/ida_structs.json` 是 `annotation → apply → IDB → export` 的**下游产物**，两源不并列。本表任何差异只读作**往返保真缺口**（注解未在 apply→export 往返中保真 / export 侧合成成员），不得读成「IDA 反对注解」或「注解错误」。
>
> **位面复用 ≠ 偏移冲突**：`known_members` 的 dict 形态（inline union/struct）、`source:overlap`、同偏移 `_N` 变体键是**同一存储的多解释视图声明**，单列「位面复用」账，不计缺失/冲突（CLAUDE.md 2026-10-16 反向审计定谳）。
>
> **陈旧拒报**：export 时间戳早于注解最新改动 ⇒ 本报表**不生成**（rc=2）。

## 0. 输入与时间戳（陈旧拒报判据）

| 项 | 值 |
|---|---|
| 导出产物 | `asm/pal3/ida_structs.json` |
| 注解目录 | `data/annotations/structs`（926 个 JSON） |
| export 时间戳 | 2026-11-23 17:39:51 +0800（epoch 1795426791.300997） |
| 注解最新改动 | 2026-11-23 17:31:21 +0800（epoch 1795426281.830256） |
| 注解最新改动文件 | `data/annotations/structs/UIWnd.json` |
| 陈旧判定 | FRESH（export 不早于注解最新改动） |

## 1. 量化统计

| 指标 | 值 |
|---|---|
| 结构：双侧共有 / 仅导出 / 仅注解 | 863 / 443 / 63 |
| 成员全同（type 串全同） | 0 |
| 成员拼写归一（语义等价，不计差异） | 0 |
| **类型差异（语义不等）** | **0** |
| **成员缺失（注解有 · 导出缺，真缺口）** | **8946** |
| **成员新增（导出有 · 注解缺）** | **9090** |
| └ 其中 export 合成补尾 `_tail_*` | 102 |
| 位面复用声明（dict / overlap / 同偏移变体） | 161 |
| 已解释·基类区域成员（偏移 < base_size） | 0 |
| 已解释·vptr/base 声明迁移到 vtables/bases | 1 |
| 结构 sizeof 不一致 | 0 |
| `_inline_*` 引用 / 定义 / 引用无定义 / 定义未引用 | 27 / 31 / 0 / 4 |

**多少类不一致？** 855 个结构存在任一差异（成员数/偏移/类型），见 §8；**多少成员缺失？** 真缺口 8946 个，见 §2（另 1 个已解释不计缺口）。

## 2. 成员缺失（注解有 · 导出缺）

往返丢失真缺口（**未**被基类区域 / vptr·base 归位解释的）：

| 类 | 偏移键 | 成员 | 注解 type |
|---|---|---|---|
| ARC_ArcBrief | 0x0 | gametime | `float` |
| ARC_ArcBrief | 0x4 | inteam | `unsigned char[5]` |
| ARC_ArcBrief | 0x4c | money | `int` |
| ARC_ArcBrief | 0x9 | scenename | `char[64]` |
| ARC_ArcHeader | 0x0 | magic | `char[4]` |
| ARC_ArcHeader | 0x4 | ver | `BYTE` |
| ARC_ArcHeader | 0x48 | brief | `ARC_ArcBrief` |
| ARC_ArcHeader | 0x8 | reverse | `unsigned int[16]` |
| ARC_ArcHeader | 0x98 | localeOffset | `DWORD` |
| ARC_ArcHeader | 0x9c | playerOffset | `DWORD` |
| ARC_ArcHeader | 0xa0 | scriptOffset | `DWORD` |
| ARC_ArcHeader | 0xa4 | sceneOffset | `DWORD` |
| ARC_ArcHeader | 0xa8 | soundOffset | `DWORD` |
| ARC_ArcHeader | 0xac | miscOffset | `DWORD` |
| ARC_ArcHeader | 0xb0 | mapOffset | `unsigned int[2]` |
| ARC_ArcHeader | 0xb8 | pastOffset | `DWORD` |
| ARC_ArcHeader | 0xbc | npcOffset | `DWORD` |
| ARC_ArcHeader | 0xc0 | reverseOffset | `unsigned int[7]` |
| ARC_ArcLocaleRole | 0x0 | active | `BYTE` |
| ARC_ArcLocaleRole | 0x1 | offset | `unsigned char[27]` |
| ARC_ArcMsic | 0x0 | byte6forwishPool | `unsigned char[12]` |
| ARC_ArcMsic | 0x124 | m_PurgeNum | `ARC_WuLing` |
| ARC_ArcMsic | 0x128 | byteoffset | `unsigned char[256]` |
| ARC_ArcMsic | 0x16 | m_isAllPurged | `unsigned char[5]` |
| ARC_ArcMsic | 0x1c | m_totalNum | `int` |
| ARC_ArcMsic | 0x20 | m_isyjfx | `BYTE` |
| ARC_ArcMsic | 0x21 | m_ComSkill | `unsigned char[8][5]` |
| ARC_ArcMsic | 0x49 | m_SDTY | `BYTE` |
| ARC_ArcMsic | 0x4a | m_APPR | `BYTE` |
| ARC_ArcMsic | 0x4b | m_SKEE | `BYTE` |
| ARC_ArcMsic | 0x4c | m_isSword | `DWORD` |
| ARC_ArcMsic | 0x50 | m_isJusticeBook | `DWORD` |
| ARC_ArcMsic | 0x54 | g_dwWeaponWU | `int` |
| ARC_ArcMsic | 0x58 | m_bigMapElement | `unsigned char[40]` |
| ARC_ArcMsic | 0x80 | g_nWolfCounter | `DWORD` |
| ARC_ArcMsic | 0x84 | com_quantum | `float[5][8]` |
| ARC_ArcMsic | 0xc | m_isPurged | `unsigned char[5][2]` |
| ARC_ComboAttack | 0x0 | name | `char[32]` |
| ARC_ComboAttack | 0x20 | id | `DWORD` |
| ARC_ComboAttack | 0x24 | man | `unsigned int[4]` |
| ARC_ComboAttack | 0x250 | fanwei | `BYTE` |
| ARC_ComboAttack | 0x251 | rvtype | `unsigned char[12]` |
| ARC_ComboAttack | 0x25e | rolevalue | `short[12]` |
| ARC_ComboAttack | 0x34 | pos | `unsigned char[4]` |
| ARC_ComboAttack | 0x38 | skill | `DWORD` |
| ARC_ComboAttack | 0x3c | WeaponType | `unsigned char[4]` |
| ARC_ComboAttack | 0x40 | Range | `BYTE` |
| ARC_ComboAttack | 0x44 | state | `FightState[3]` |
| ARC_ComboAttack | 0x50 | Remark | `char[512]` |
| ARC_FightItem | 0x0 | id | `DWORD` |
| ARC_FightItem | 0x24 | ModelID | `char[30]` |
| ARC_FightItem | 0x260 | price | `int` |
| ARC_FightItem | 0x264 | type | `BYTE` |
| ARC_FightItem | 0x265 | weapontype | `BYTE` |
| ARC_FightItem | 0x266 | user | `unsigned char[5]` |
| ARC_FightItem | 0x26b | att | `unsigned char[5]` |
| ARC_FightItem | 0x270 | gu | `int` |
| ARC_FightItem | 0x274 | special | `BYTE` |
| ARC_FightItem | 0x275 | fanwei | `BYTE` |
| ARC_FightItem | 0x276 | space | `BYTE` |
| ARC_FightItem | 0x277 | rvtype | `unsigned char[12]` |
| ARC_FightItem | 0x284 | rolevalue | `short[12]` |
| ARC_FightItem | 0x29c | fstype | `unsigned char[31]` |
| ARC_FightItem | 0x2bc | fightstate | `short[31]` |
| ARC_FightItem | 0x2fc | lian | `int` |
| ARC_FightItem | 0x300 | saveqi | `short` |
| ARC_FightItem | 0x302 | saveshen | `short` |
| ARC_FightItem | 0x304 | addbaoji | `short` |
| ARC_FightItem | 0x306 | addteji | `short` |
| ARC_FightItem | 0x308 | stone | `DWORD` |
| ARC_FightItem | 0x30c | make | `DWORD` |
| ARC_FightItem | 0x310 | smeltPrice | `int` |
| ARC_FightItem | 0x314 | hecheng | `unsigned int[2]` |
| ARC_FightItem | 0x31c | make2 | `DWORD` |
| ARC_FightItem | 0x4 | name | `char[32]` |
| ARC_FightItem | 0x42 | ImageID | `char[30]` |
| ARC_FightItem | 0x60 | desc | `char[512]` |
| ARC_FightSkill | 0x0 | id | `DWORD` |
| ARC_FightSkill | 0x1c | name | `char[32]` |
| ARC_FightSkill | 0x23c | user | `unsigned char[5]` |
| ARC_FightSkill | 0x241 | fanwei | `BYTE` |
| ARC_FightSkill | 0x242 | special | `BYTE` |
| ARC_FightSkill | 0x243 | rvtype | `unsigned char[12]` |
| ARC_FightSkill | 0x250 | rolevalue | `short[12]` |
| ARC_FightSkill | 0x268 | succ | `BYTE` |
| ARC_FightSkill | 0x26a | fs | `short[31]` |
| ARC_FightSkill | 0x2a8 | consumervtype | `int[2]` |
| ARC_FightSkill | 0x2b0 | consumetype | `int[3]` |
| ARC_FightSkill | 0x2bc | tutype | `BYTE` |
| ARC_FightSkill | 0x2c0 | tusuval | `int` |
| ARC_FightSkill | 0x2c4 | lv | `BYTE` |
| ARC_FightSkill | 0x2c5 | lvup | `unsigned char[4]` |
| ARC_FightSkill | 0x2c9 | rolelv | `BYTE` |
| ARC_FightSkill | 0x2ca | magiclv | `BYTE` |
| ARC_FightSkill | 0x2cc | nextid | `DWORD` |
| ARC_FightSkill | 0x2d0 | isuseall | `BYTE` |
| ARC_FightSkill | 0x2d4 | hecheng | `unsigned int[3]` |
| ARC_FightSkill | 0x2e0 | heskill | `unsigned int[3]` |
| ARC_FightSkill | 0x2ec | helv | `unsigned char[3]` |
| ARC_FightSkill | 0x2ef | helvself | `unsigned char[3]` |
| ARC_FightSkill | 0x2f2 | manlv | `unsigned char[3]` |
| ARC_FightSkill | 0x2f5 | heji | `BYTE` |
| ARC_FightSkill | 0x3c | desc | `char[512]` |
| ARC_FightSkill | 0x4 | type | `BYTE` |
| ARC_FightSkill | 0x8 | att | `int[5]` |
| ARC_Inventory | 0x0 | m_items | `std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >` |
| ARC_Inventory | 0x10 | m_curtype | `int` |
| ARC_Inventory | 0x14 | m_typeitems | `std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >` |
| ARC_Inventory | 0x24 | m_money | `int` |
| ARC_MonsterStar | 0x0 | needexp | `int` |
| ARC_MonsterStar | 0x4 | active | `int` |
| ARC_MonsterStar | 0x8 | exp | `int` |
| ARC_MonsterStar | 0xc | item | `DWORD` |
| ARC_OutFile | 0x0 | str | `char[128]` |
| ARC_OutFile | 0x80 | RolePos | `DWORD` |
| ARC_OutFile | 0x84 | RoleNum | `int` |
| ARC_OutFile | 0x88 | SkillPos | `DWORD` |
| ARC_OutFile | 0x8c | SkillNum | `int` |
| ARC_OutFile | 0x90 | ItemPos | `DWORD` |
| ARC_OutFile | 0x94 | ItemNum | `int` |
| ARC_OutFile | 0x98 | ComboPos | `DWORD` |
| ARC_OutFile | 0x9c | ComboNum | `int` |
| ARC_PAL_GDB | 0x0 | m_head | `ARC_OutFile` |
| ARC_PAL_GDB | 0x29a40 | m_SkillData | `ARC_FightSkill[300]` |
| ARC_PAL_GDB | 0x614e0 | m_ItemData | `ARC_FightItem[500]` |
| ARC_PAL_GDB | 0xa0 | m_RoleData | `ARC_RoleAtt[200]` |
| ARC_PAL_GDB | 0xc2f60 | m_ComboData | `ARC_ComboAttack[10]` |
| ARC_PAL_GDB | 0xc4810 | i | `int` |
| ARC_PAL_GDB | 0xc4814 | mLoaded | `BYTE` |
| ARC_PlayerAtt | 0x354 | hat | `ARC_PlayerItem *` |
| ARC_PlayerAtt | 0x35c | nScriptSpeed | `int` |
| ARC_PlayerAtt | 0x360 | cloth | `ARC_PlayerItem` |
| ARC_PlayerAtt | 0x36c | shoes | `ARC_PlayerItem` |
| ARC_PlayerAtt | 0x378 | wear | `ARC_PlayerItem[2]` |
| ARC_PlayerAtt | 0x390 | nScriptCounter | `int` |
| ARC_PlayerAtt | 0x394 | weapon | `ARC_PlayerItem` |
| ARC_PlayerAtt | 0x3a0 | maxrolevalue | `int[12]` |
| ARC_PlayerAtt | 0x3d0 | currolevalue | `int[12]` |
| ARC_PlayerAtt | 0x400 | dwWeaponSkillID | `unsigned int` |
| ARC_PlayerAtt | 0x404 | dwCleanCent | `unsigned int` |
| ARC_PlayerAtt | 0x408 | fWeaponSkillMass | `float` |
| ARC_PlayerAtt | 0x40c | dwSkillID | `unsigned int[6]` |
| ARC_PlayerAtt | 0x424 | bSkillMastered | `unsigned char[6]` |
| ARC_PlayerAtt | 0x42c | dwMagicID | `unsigned int[8][6]` |
| ARC_PlayerAtt | 0x4ec | bMagicMastered | `unsigned char[8][6]` |
| ARC_PlayerAtt | 0x51c | byMagicUseTime | `unsigned char[8][6]` |
| ARC_PlayerAtt | 0x54c | byMagicLevel | `unsigned char[8][6]` |
| ARC_PlayerAtt | 0x57c | bAutoCtrl | `unsigned char` |
| ARC_PlayerAtt | 0x57d | bAIAttack | `unsigned char` |
| ARC_PlayerAtt | 0x57e | bAIMagic | `unsigned char` |
| ARC_PlayerAtt | 0x57f | bAISkill | `unsigned char` |
| ARC_PlayerAtt | 0x580 | bAIUseItem | `unsigned char` |
| ARC_PlayerAtt | 0x581 | bAINegative | `unsigned char` |
| ARC_PlayerAtt | 0x582 | byLineup | `unsigned char` |
| ARC_PlayerItem | 0x0 | id | `DWORD` |
| ARC_PlayerItem | 0x4 | num | `int` |
| ARC_PlayerItem | 0x8 | item | `short` |
| ARC_PlayerMgrInfo | 0x0 | m_nHuaYingMode | `int` |
| ARC_PlayerMgrInfo | 0x1bb4 | m_inteam | `unsigned char[5]` |
| ARC_PlayerMgrInfo | 0x1bbc | m_inventory | `ARC_Inventory` |
| ARC_PlayerMgrInfo | 0x1be4 | m_reoccupy | `ARC_Reoccupy` |
| ARC_PlayerMgrInfo | 0x1bf4 | m_starts | `ARC_MonsterStar[10]` |
| ARC_PlayerMgrInfo | 0x1c94 | m_byGemUseTime | `unsigned char[8]` |
| ARC_PlayerMgrInfo | 0x1c9c | reverse | `unsigned int[18]` |
| ARC_PlayerMgrInfo | 0x20 | m_att | `ARC_PlayerAtt[5]` |
| ARC_PlayerMgrInfo | 0x4 | dwWeaponWU | `int` |
| ARC_PlayerMgrInfo | 0x8 | m_favor | `int[6]` |
| ARC_Reoccupy | 0x0 | m_id | `std::vector<unsigned int,std::allocator<unsigned int> >` |
| ARC_RoleAtt | 0x0 | id | `DWORD` |
| ARC_RoleAtt | 0x130 | _todo_130 | `char[152]` |
| ARC_RoleAtt | 0x1c8 | _todo_1c8 | `char[62]` |
| ARC_RoleAtt | 0x206 | ModelID | `char[30]` |
| ARC_RoleAtt | 0x224 | _todo_224 | `char[304]` |
| ARC_RoleAtt | 0x4 | type | `WORD` |
| ARC_RoleAtt | 0x48 | _todo_048 | `int` |
| ARC_RoleAtt | 0x4c | _todo_04c | `int` |
| ARC_RoleAtt | 0x50 | _todo_050 | `char[4]` |
| ARC_RoleAtt | 0x54 | _todo_054 | `int` |
| ARC_RoleAtt | 0x58 | _todo_058 | `int` |
| ARC_RoleAtt | 0x5c | _todo_05c | `int` |
| ARC_RoleAtt | 0x6 | _todo_006 | `char[66]` |
| ARC_RoleAtt | 0x60 | _todo_060 | `int` |
| ARC_RoleAtt | 0x64 | _todo_064 | `int` |
| ARC_RoleAtt | 0x68 | _todo_068 | `int` |
| ARC_RoleAtt | 0x6c | _todo_06c | `int` |
| ARC_RoleAtt | 0x70 | _todo_070 | `int` |
| ARC_RoleAtt | 0x74 | _todo_074 | `char[188]` |
| ASISTAGE | 0x0 | ASI_stream_open | `char *` |
| ASISTAGE | 0x10 | ASI_stream_attribute | `char *` |
| ASISTAGE | 0x14 | ASI_stream_set_preference | `char *` |
| ASISTAGE | 0x18 | INPUT_BIT_RATE | `DWORD` |
| ASISTAGE | 0x1c | INPUT_SAMPLE_RATE | `DWORD` |
| ASISTAGE | 0x20 | INPUT_BITS | `DWORD` |
| ASISTAGE | 0x24 | INPUT_CHANNELS | `DWORD` |
| ASISTAGE | 0x28 | OUTPUT_BIT_RATE | `DWORD` |
| ASISTAGE | 0x2c | OUTPUT_SAMPLE_RATE | `DWORD` |
| ASISTAGE | 0x30 | OUTPUT_BITS | `DWORD` |
| ASISTAGE | 0x34 | OUTPUT_CHANNELS | `DWORD` |
| ASISTAGE | 0x38 | POSITION | `DWORD` |
| ASISTAGE | 0x3c | PERCENT_DONE | `DWORD` |
| ASISTAGE | 0x4 | ASI_stream_process | `char *` |
| ASISTAGE | 0x40 | MIN_INPUT_BLOCK_SIZE | `DWORD` |
| ASISTAGE | 0x44 | RAW_RATE | `DWORD` |
| ASISTAGE | 0x48 | RAW_BITS | `DWORD` |
| ASISTAGE | 0x4c | RAW_CHANNELS | `DWORD` |
| ASISTAGE | 0x50 | REQUESTED_RATE | `DWORD` |
| ASISTAGE | 0x54 | REQUESTED_BITS | `DWORD` |
| ASISTAGE | 0x58 | REQUESTED_CHANS | `DWORD` |
| ASISTAGE | 0x5c | stream | `long` |
| ASISTAGE | 0x8 | ASI_stream_seek | `char *` |
| ASISTAGE | 0xc | ASI_stream_close | `char *` |
| AStarPathFinder | 0x10 | Stack | `AStarPathFinder::STACK *` |
| AStarPathFinder | 0x14 | m_TestTimer | `int` |
| AStarPathFinder | 0x4 | OPEN | `AStarPathFinder::NODE *` |
| AStarPathFinder | 0x8 | CLOSED | `AStarPathFinder::NODE *` |
| AStarPathFinder | 0xc | PATH | `AStarPathFinder::NODE *` |
| Actor | 0x0 | m_actarray_type | `char` |
| Actor | 0x10 | m_pact | `gbActor *` |
| Actor | 0x100 | m_Actor | `int` |
| Actor | 0x108 | m_nCmdParam | `int` |
| Actor | 0x110 | m_pActor | `gbActor *` |
| Actor | 0x118 | m_szTexture | `char[28]` |
| Actor | 0x134 | m_vecLocalPos | `gbVec3D` |
| Actor | 0x14 | m_name | `char[8]` |
| Actor | 0x148 | m_nAnimState | `short` |
| Actor | 0x14c | m_nActionType | `unsigned char` |
| Actor | 0x14d | m_bActionFlag1 | `unsigned char` |
| Actor | 0x150 | m_nActionParam | `unsigned char` |
| Actor | 0x151 | m_bActionFlag2 | `unsigned char` |
| Actor | 0x152 | m_bActionFlag3 | `unsigned char` |
| Actor | 0x153 | m_bActionActive | `unsigned char` |
| Actor | 0x154 | m_nActionState | `int` |
| Actor | 0x158 | m_nActionResult | `unsigned char` |
| Actor | 0x159 | m_bInitialized | `unsigned char` |
| Actor | 0x15c | m_nHP | `int` |
| Actor | 0x160 | m_nMaxHP | `int` |
| Actor | 0x164 | m_bHPVisible | `unsigned char` |
| Actor | 0x168 | m_nHandleEvent | `int` |
| Actor | 0x16c | m_vecPos | `gbVec3D` |
| Actor | 0x178 | m_vecRot | `gbVec3D` |
| Actor | 0x184 | m_nCloneParam | `int` |
| Actor | 0x188 | m_fActionAssignParam | `float` |
| Actor | 0x18c | m_nCloneParamB | `int` |
| Actor | 0x190 | m_nCloneState | `int` |
| Actor | 0x194 | m_nCloneFlag1 | `int` |
| Actor | 0x198 | m_nCloneFlag2 | `int` |
| Actor | 0x19c | m_fFacingAngle | `float` |
| Actor | 0x1a4 | m_nModelParamA | `int` |
| Actor | 0x1ac | m_nModelParamB | `int` |
| Actor | 0x1b0 | m_nRoleState1 | `int` |
| Actor | 0x1b4 | m_pEquipAtt0 | `RoleAtt *` |
| Actor | 0x1b8 | m_nAnimFrames | `int` |
| Actor | 0x1bc | m_nTransitionParam | `int` |
| Actor | 0x1c | m_fMoveSpeed | `float` |
| Actor | 0x1c0 | m_pEquipAtt1 | `RoleAtt *[3]` |
| Actor | 0x1cc | m_pEquipAtt2 | `RoleAtt *[3]` |
| Actor | 0x1e4 | m_fBlendWeight | `float` |
| Actor | 0x1e8 | m_obbox | `int` |
| Actor | 0x1f0 | m_pSelfAtt | `void*` |
| Actor | 0x1f4 | m_nAnimFrame | `short` |
| Actor | 0x20 | m_fMoveRange | `float` |
| Actor | 0x218 | m_fAnimDelta | `float` |
| Actor | 0x21c | m_dwMatMsg | `unsigned int[11]` |
| Actor | 0x24 | m_pAllocBuf | `char *` |
| Actor | 0x248 | m_bChangedMat | `unsigned char` |
| Actor | 0x249 | m_curact | `char[8]` |
| Actor | 0x274 | _overlap_RoleSystem_m_partyActor_m_nState | `int` |
| Actor | 0x278 | m_fDirX | `float` |
| Actor | 0x27c | m_fDirY | `float` |
| Actor | 0x28 | m_fTransitionSpeed | `float` |
| Actor | 0x280 | m_fDirZ | `float` |
| Actor | 0x284 | m_fNormX | `float` |
| Actor | 0x288 | m_fNormY | `float` |
| Actor | 0x28c | m_fNormZ | `float` |
| Actor | 0x290 | m_fDistAccum | `float` |
| Actor | 0x294 | m_fSpeed | `float` |
| Actor | 0x2a4 | m_fAngleDeg | `float` |
| Actor | 0x2ac | m_bDirFlag | `unsigned char` |
| Actor | 0x2c | m_fTransitionPos | `float` |
| Actor | 0x2d4 | m_nAnimCounter | `int` |
| Actor | 0x30 | m_nRoleParam0 | `int` |
| Actor | 0x305 | m_bStateFlag | `unsigned char` |
| Actor | 0x308 | m_pRoleState | `char *` |
| Actor | 0x310 | m_nUpdateMode | `int` |
| Actor | 0x34 | m_fRoleParam1 | `float` |
| Actor | 0x38 | m_fRoleParam | `float` |
| Actor | 0x3c | m_fRoleParam2 | `float` |
| Actor | 0x4 | m_actarray_begin | `Actor *` |
| Actor | 0x40 | m_fRoleParam3 | `float` |
| Actor | 0x44 | m_nRoleParam2 | `int` |
| Actor | 0x48 | m_pRoleParam3 | `char *` |
| Actor | 0x4c | m_nCachedA | `int` |
| Actor | 0x50 | m_nCachedB | `unsigned char` |
| Actor | 0x54 | m_nTransform | `int` |
| Actor | 0x58 | m_nRoleState0 | `int` |
| Actor | 0x5c | m_bUIFlagA | `unsigned char` |
| Actor | 0x5d | m_bUIFlagB | `unsigned char` |
| Actor | 0x60 | m_fAnimParam | `float` |
| Actor | 0x64 | m_szText | `char` |
| Actor | 0x70 | m_pResource | `void *` |
| Actor | 0x74 | m_nModelId | `int` |
| Actor | 0x8 | m_actarray_end | `Actor *` |
| Actor | 0x80 | m_nAnimParam0 | `int` |
| Actor | 0x84 | m_nAnimParam1 | `int` |
| Actor | 0x88 | m_vecBonePos | `gbVec3D` |
| Actor | 0x94 | m_nPathBuffer | `int` |
| Actor | 0x98 | m_nAnimBuffer | `int` |
| Actor | 0x9c | m_nParticleBuffer | `int` |
| Actor | 0xa0 | m_vecTargetPos | `gbVec3D` |
| Actor | 0xac | m_fInterpStart | `float` |
| Actor | 0xb0 | m_fInterpEnd | `float` |
| Actor | 0xb4 | m_nInterpFrames | `int` |
| Actor | 0xb8 | m_fActionSpeed | `float` |
| Actor | 0xbc | m_nInterpCurrent | `int` |
| Actor | 0xc | m_actarray_capacity_end | `Actor *` |
| Actor | 0xc0 | m_nInterpState | `int` |
| Actor | 0xc4 | m_fInterpSpeed | `float` |
| Actor | 0xc8 | m_nModelLoadState | `int` |
| Actor | 0xcc | m_nState | `int` |
| Actor | 0xd0 | m_pRoleObj | `int` |
| Actor | 0xd4 | m_nPathEnabled | `int` |
| Actor | 0xd8 | m_fScale | `unsigned char` |
| Actor | 0xd9 | m_bParamFlag | `unsigned char` |
| Actor | 0xdc | m_fMatrixA | `float` |
| Actor | 0xe0 | m_fMatrixB | `unsigned char` |
| Actor | 0xe4 | m_fMatrixC | `float` |
| Actor | 0xe8 | m_nMatrixParam | `int` |
| Actor | 0xec | m_fMatrixParamA | `float` |
| Actor | 0xf0 | m_fMatrixParamB | `float` |
| Actor | 0xf4 | m_fMatrixE | `float` |
| Actor | 0xf8 | m_fMatrixF | `float` |
| Actor | 0xfc | m_fMatrixParamC | `float` |
| ArcBrief | 0x0 | gametime | `double` |
| ArcBrief | 0x50 | money | `int` |
| ArcBrief | 0x8 | inteam | `unsigned char[5]` |
| ArcBrief | 0xd | scenename | `char[64]` |
| ArcHeader | 0x0 | magic | `char[4]` |
| ArcHeader | 0x4 | ver | `BYTE` |
| ArcHeader | 0x48 | brief | `ArcBrief` |
| ArcHeader | 0x8 | reverse | `unsigned int[16]` |
| ArcHeader | 0xa0 | localeOffset | `DWORD` |
| ArcHeader | 0xa4 | playerOffset | `DWORD` |
| ArcHeader | 0xa8 | scriptOffset | `DWORD` |
| ArcHeader | 0xac | sceneOffset | `DWORD` |
| ArcHeader | 0xb0 | soundOffset | `DWORD` |
| ArcHeader | 0xb4 | miscOffset | `DWORD` |
| ArcHeader | 0xb8 | mapOffset | `unsigned int[2]` |
| ArcHeader | 0xc0 | pastOffset | `DWORD` |
| ArcHeader | 0xc4 | npcOffset | `DWORD` |
| ArcHeader | 0xc8 | reverseOffset | `unsigned char[20]` |
| ArcLocale | 0x0 | scene | `SceneInfo` |
| ArcLocale | 0x12c | underctrl | `BYTE` |
| ArcLocale | 0x12d | px_mdl | `char[32]` |
| ArcLocale | 0x150 | pstate | `PlayerMgr::PoisonState *` |
| ArcLocale | 0x170 | g_bYouDi | `BYTE` |
| ArcLocale | 0x174 | m_fFStime | `float` |
| ArcLocale | 0x178 | music | `ArcLocaleMusic` |
| ArcLocale | 0x18a | grayscale | `BYTE` |
| ArcLocale | 0x18b | underwater | `BYTE` |
| ArcLocale | 0x18c | rain | `BYTE` |
| ArcLocale | 0x18d | snow | `BYTE` |
| ArcLocale | 0x18e | watermagic | `BYTE` |
| ArcLocale | 0x190 | fog | `gbFogParam` |
| ArcLocale | 0x1c4 | reverse | `unsigned char[32]` |
| ArcLocale | 0x84 | camera | `RC_ARG` |
| ArcLocale | 0xa0 | player | `ArcLocaleRole[5]` |
| ArcLocaleMusic | 0x0 | bscript | `BYTE` |
| ArcLocaleMusic | 0x1 | loop | `BYTE` |
| ArcLocaleMusic | 0x2 | name | `char[16]` |
| ArcLocaleRole | 0x0 | active | `BYTE` |
| ArcLocaleRole | 0x10 | layer | `BYTE` |
| ArcLocaleRole | 0x14 | rotate | `float` |
| ArcLocaleRole | 0x18 | script | `DWORD` |
| ArcLocaleRole | 0x4 | pos | `gbVec3D` |
| ArcMsic | 0x0 | m_bigMapElement | `unsigned char[40]` |
| ArcMsic | 0x28 | m_dwCombatTimes | `DWORD` |
| ArcMsic | 0x280 | nImbibeNimbusTimes | `int` |
| ArcMsic | 0x284 | bShowStatuary | `BYTE` |
| ArcMsic | 0x285 | reverse | `unsigned char[99]` |
| ArcMsic | 0x2c | bPXVariance | `BYTE` |
| ArcMsic | 0x2d | bHaveNimbus | `BYTE` |
| ArcMsic | 0x30 | nNimbus | `int[5]` |
| ArcMsic | 0x44 | m_Player | `tagPlayerSet[11]` |
| ArcPastScene | 0x0 | cityname | `char[32]` |
| ArcPastScene | 0x20 | name | `char[32]` |
| ArcPosition | 0x0 | filepath | `char[256]` |
| ArcScene | 0x0 | scene | `SceneInfo` |
| ArcScene | 0x84 | objArray | `std::vector<ArcSceneObject,std::allocator<ArcSceneObject> >` |
| ArcScene | 0x94 | npcArray | `std::vector<ArcSceneMonster,std::allocator<ArcSceneMonster> >` |
| ArcSceneMonster | 0x0 | id | `BYTE` |
| ArcSceneMonster | 0x1 | active | `BYTE` |
| ArcSceneMonster | 0x13c | m_nSkillCount | `int` |
| ArcSceneMonster | 0x144 | m_nDropRate | `int` |
| ArcSceneMonster | 0x15c | m_nMonsterGold | `int` |
| ArcSceneMonster | 0xa4 | m_nMonsterHP | `int` |
| ArcSceneMonster | 0xa8 | m_nMonsterMP | `int` |
| ArcSceneMonster | 0xb4 | m_nMonsterLevel | `int` |
| ArcSceneMonster | 0xec | m_nMonsterExp | `int` |
| ArcSceneObject | 0x0 | info | `ObjectInfo` |
| ArcSceneObject | 0x25c | task | `SaveTask` |
| ArcSceneObject | 0x268 | subobj | `int` |
| Archive | 0x0 | m_scene | `std::vector<ArcScene,std::allocator<ArcScene> >` |
| Archive | 0x10 | m_past | `std::vector<ArcPastScene,std::allocator<ArcPastScene> >` |
| Archive | 0x20 | m_objNotLoad | `std::vector<unsigned int,std::allocator<unsigned int> >` |
| Array | 0x0 | m_pDataStart | `int` |
| Array | 0x4 | m_nSize | `int` |
| Array | 0x8 | m_pData | `char *` |
| Array | 0xc | m_nCapacity | `int` |
| ArraySlots | 0x48 | m_aSlotPtrs | `int[3]` |
| ArraySlots | 0x54 | m_bActive | `int` |
| ArtistPlugIn | 0x0 | pFile | `FILE *` |
| ArtistPlugIn | 0x204 | pInfo | `_PlugInfo *` |
| ArtistPlugIn | 0x208 | m_infoNum | `UINT` |
| ArtistPlugIn | 0x20c | m_alreadyLoad | `BYTE` |
| ArtistPlugIn | 0x210 | m_tRect | `tagRECT` |
| ArtistPlugIn | 0x220 | m_bOptmize | `BYTE` |
| ArtistPlugIn | 0x224 | m_posMaker | `UIPosMaker` |
| ArtistPlugIn | 0x4 | _libfolder | `char[512]` |
| AudioContext | 0x0 | m_nType | `int` |
| AudioContext | 0x10 | m_bPlaying | `int` |
| AudioContext | 0x14 | m_nReserved | `int` |
| AudioContext | 0x18 | m_pAudioMgr | `char *` |
| AudioContext | 0x1c | m_nFadeTarget | `int` |
| AudioContext | 0x4 | m_nState | `int` |
| AudioContext | 0x8 | m_nVolume | `int` |
| AudioContext | 0xc | m_pSoundName | `char *` |
| Average | 0x0 | _size | `UINT` |
| Average | 0x10 | _real | `UINT` |
| Average | 0x14 | _initialize | `BYTE` |
| Average | 0x15 | _invalid | `BYTE` |
| Average | 0x16 | _full | `BYTE` |
| Average | 0x4 | _data | `float *` |
| Average | 0x8 | ret | `float` |
| Average | 0xc | _cur | `UINT` |
| BARRIER | 0x0 | vPos | `gbVec3D` |
| BARRIER | 0x10 | fYLen | `float` |
| BARRIER | 0x14 | fZLen | `float` |
| BARRIER | 0x18 | nFloorX | `int` |
| BARRIER | 0x1c | nFloorZ | `int` |
| BARRIER | 0xc | fXLen | `float` |
| BINK | 0x0 | Width | `DWORD` |
| BINK | 0x10 | LastFrameNum | `DWORD` |
| BINK | 0x100 | BackgroundThread | `DWORD` |
| BINK | 0x104 | compframe | `char *` |
| BINK | 0x108 | preloadptr | `char *` |
| BINK | 0x10c | frameoffsets | `DWORD *` |
| BINK | 0x110 | bio | `BINKIO` |
| BINK | 0x14 | FrameRate | `DWORD` |
| BINK | 0x18 | FrameRateDiv | `DWORD` |
| BINK | 0x1c | ReadError | `DWORD` |
| BINK | 0x1dc | ioptr | `BYTE *` |
| BINK | 0x1e0 | iosize | `DWORD` |
| BINK | 0x1e4 | decompwidth | `DWORD` |
| BINK | 0x1e8 | decompheight | `DWORD` |
| BINK | 0x1ec | trackindex | `long` |
| BINK | 0x1f0 | tracksizes | `DWORD *` |
| BINK | 0x1f4 | tracktypes | `DWORD *` |
| BINK | 0x1f8 | trackIDs | `int *` |
| BINK | 0x1fc | numrects | `DWORD` |
| BINK | 0x20 | OpenFlags | `DWORD` |
| BINK | 0x200 | playedframes | `DWORD` |
| BINK | 0x204 | firstframetime | `DWORD` |
| BINK | 0x208 | startframetime | `DWORD` |
| BINK | 0x20c | startblittime | `DWORD` |
| BINK | 0x210 | startsynctime | `DWORD` |
| BINK | 0x214 | startsyncframe | `DWORD` |
| BINK | 0x218 | twoframestime | `DWORD` |
| BINK | 0x21c | entireframetime | `DWORD` |
| BINK | 0x220 | slowestframetime | `DWORD` |
| BINK | 0x224 | slowestframe | `DWORD` |
| BINK | 0x228 | slowest2frametime | `DWORD` |
| BINK | 0x22c | slowest2frame | `DWORD` |
| BINK | 0x230 | soundon | `DWORD` |
| BINK | 0x234 | videoon | `DWORD` |
| BINK | 0x238 | totalmem | `DWORD` |
| BINK | 0x23c | timevdecomp | `DWORD` |
| BINK | 0x24 | BinkType | `DWORD` |
| BINK | 0x240 | timeadecomp | `DWORD` |
| BINK | 0x244 | timeblit | `DWORD` |
| BINK | 0x248 | timeopen | `DWORD` |
| BINK | 0x24c | fileframerate | `DWORD` |
| BINK | 0x250 | fileframeratediv | `DWORD` |
| BINK | 0x254 | threadcontrol | `DWORD` |
| BINK | 0x258 | runtimeframes | `DWORD` |
| BINK | 0x25c | runtimemoveamt | `DWORD` |
| BINK | 0x260 | rtframetimes | `DWORD *` |
| BINK | 0x264 | rtadecomptimes | `DWORD *` |
| BINK | 0x268 | rtvdecomptimes | `DWORD *` |
| BINK | 0x26c | rtblittimes | `DWORD *` |
| BINK | 0x270 | rtreadtimes | `DWORD *` |
| BINK | 0x274 | rtidlereadtimes | `DWORD *` |
| BINK | 0x278 | rtthreadreadtimes | `DWORD *` |
| BINK | 0x27c | lastblitflags | `DWORD` |
| BINK | 0x28 | Size | `DWORD` |
| BINK | 0x280 | lastdecompframe | `DWORD` |
| BINK | 0x284 | sndbufsize | `DWORD` |
| BINK | 0x288 | sndbuf | `BYTE *` |
| BINK | 0x28c | sndend | `BYTE *` |
| BINK | 0x290 | sndwritepos | `BYTE *` |
| BINK | 0x294 | sndreadpos | `BYTE *` |
| BINK | 0x298 | sndcomp | `DWORD` |
| BINK | 0x29c | sndamt | `DWORD` |
| BINK | 0x2a0 | sndreenter | `DWORD` |
| BINK | 0x2a4 | sndconvert8 | `DWORD` |
| BINK | 0x2a8 | bsnd | `BINKSND` |
| BINK | 0x2c | FrameSize | `DWORD` |
| BINK | 0x30 | SndSize | `DWORD` |
| BINK | 0x34 | FrameRects | `BINKRECT[8]` |
| BINK | 0x368 | skippedlastblit | `DWORD` |
| BINK | 0x36c | skippedblits | `DWORD` |
| BINK | 0x370 | soundskips | `DWORD` |
| BINK | 0x374 | sndendframe | `DWORD` |
| BINK | 0x378 | sndprime | `DWORD` |
| BINK | 0x37c | sndpad | `DWORD` |
| BINK | 0x380 | bunp | `BUNDLEPOINTERS` |
| BINK | 0x4 | Height | `DWORD` |
| BINK | 0x8 | Frames | `DWORD` |
| BINK | 0xb4 | NumRects | `long` |
| BINK | 0xb8 | PlaneNum | `DWORD` |
| BINK | 0xbc | YPlane | `char *[2]` |
| BINK | 0xc | FrameNum | `DWORD` |
| BINK | 0xc4 | APlane | `char *[2]` |
| BINK | 0xcc | YWidth | `DWORD` |
| BINK | 0xd0 | YHeight | `DWORD` |
| BINK | 0xd4 | UVWidth | `DWORD` |
| BINK | 0xd8 | UVHeight | `DWORD` |
| BINK | 0xdc | MaskPlane | `char *` |
| BINK | 0xe0 | MaskPitch | `DWORD` |
| BINK | 0xe4 | MaskLength | `DWORD` |
| BINK | 0xe8 | LargestFrameSize | `DWORD` |
| BINK | 0xec | InternalFrames | `DWORD` |
| BINK | 0xf0 | NumTracks | `long` |
| BINK | 0xf4 | Highest1SecRate | `DWORD` |
| BINK | 0xf8 | Highest1SecFrame | `DWORD` |
| BINK | 0xfc | Paused | `long` |
| BINKIO | 0x0 | ReadHeader | `char *` |
| BINKIO | 0x10 | Idle | `char *` |
| BINKIO | 0x14 | Close | `char *` |
| BINKIO | 0x18 | bink | `BINK *` |
| BINKIO | 0x1c | ReadError | `DWORD` |
| BINKIO | 0x20 | DoingARead | `DWORD` |
| BINKIO | 0x24 | BytesRead | `DWORD` |
| BINKIO | 0x28 | Working | `DWORD` |
| BINKIO | 0x2c | TotalTime | `DWORD` |
| BINKIO | 0x30 | ForegroundTime | `DWORD` |
| BINKIO | 0x34 | IdleTime | `DWORD` |
| BINKIO | 0x38 | ThreadTime | `DWORD` |
| BINKIO | 0x3c | BufSize | `DWORD` |
| BINKIO | 0x4 | ReadFrame | `char *` |
| BINKIO | 0x40 | BufHighUsed | `DWORD` |
| BINKIO | 0x44 | CurBufSize | `DWORD` |
| BINKIO | 0x48 | CurBufUsed | `DWORD` |
| BINKIO | 0x4c | iodata | `unsigned char[128]` |
| BINKIO | 0x8 | GetBufferSize | `char *` |
| BINKIO | 0xc | SetInfo | `char *` |
| BINKRECT | 0x0 | Left | `long` |
| BINKRECT | 0x4 | Top | `long` |
| BINKRECT | 0x8 | Width | `long` |
| BINKRECT | 0xc | Height | `long` |
| BINKSND | 0x0 | Ready | `char *` |
| BINKSND | 0x10 | Pan | `char *` |
| BINKSND | 0x14 | Pause | `char *` |
| BINKSND | 0x18 | SetOnOff | `char *` |
| BINKSND | 0x1c | Close | `char *` |
| BINKSND | 0x20 | BestSizeIn16 | `DWORD` |
| BINKSND | 0x24 | SoundDroppedOut | `DWORD` |
| BINKSND | 0x28 | OnOff | `long` |
| BINKSND | 0x2c | Latency | `DWORD` |
| BINKSND | 0x30 | VideoScale | `DWORD` |
| BINKSND | 0x34 | freq | `DWORD` |
| BINKSND | 0x38 | bits | `long` |
| BINKSND | 0x3c | chans | `long` |
| BINKSND | 0x4 | Lock | `char *` |
| BINKSND | 0x40 | snddata | `unsigned char[128]` |
| BINKSND | 0x8 | Unlock | `char *` |
| BINKSND | 0xc | Volume | `char *` |
| BOSSHURT | 0x0 | AlphaSpeed | `float` |
| BOSSHURT | 0x10 | nHurtState | `int` |
| BOSSHURT | 0x4 | bFlashState | `BYTE` |
| BOSSHURT | 0x5 | bNeedFlash | `BYTE` |
| BOSSHURT | 0x8 | fTimeCounter | `float` |
| BOSSHURT | 0xc | nWaitSecond | `int` |
| BUNDLEPOINTERS | 0x0 | typeptr | `char *` |
| BUNDLEPOINTERS | 0x10 | motionXptr | `char *` |
| BUNDLEPOINTERS | 0x14 | motionYptr | `char *` |
| BUNDLEPOINTERS | 0x18 | dctptr | `char *` |
| BUNDLEPOINTERS | 0x1c | mdctptr | `char *` |
| BUNDLEPOINTERS | 0x20 | patptr | `char *` |
| BUNDLEPOINTERS | 0x4 | type16ptr | `char *` |
| BUNDLEPOINTERS | 0x8 | colorptr | `char *` |
| BUNDLEPOINTERS | 0xc | bits2ptr | `char *` |
| BillBoardFace | 0x0 | m_texarray | `gbTextureArray` |
| BillBoardFace | 0x44 | m_curtex | `int` |
| BillBoardFace | 0x48 | m_id | `int` |
| BillBoardFace | 0x4c | m_pos | `gbVec3D` |
| BillBoardFace | 0x58 | m_effect | `gbRenderEffect *` |
| BtnGroup | 0x0 | upRc | `tagRECT` |
| BtnGroup | 0x10 | dwRc | `tagRECT` |
| BtnGroup | 0x178 | m_btnDw | `UIButton` |
| BtnGroup | 0x20 | m_btnUp | `UIButton` |
| BtnGroup | 0x2d0 | m_sizex | `int` |
| BtnGroup | 0x2d4 | m_sizey | `int` |
| BtnGroup | 0x2d8 | m_mode | `_BGM` |
| BtnGroup | 0x2dc | m_Interval | `int` |
| BtnGroup | 0x2e0 | m_opt | `BYTE` |
| C2DSpark | 0x0 | m_Spark | `C2DSpark_tagSpark[512]` |
| C2DSpark | 0x6000 | m_fDisplayWidth | `float` |
| C2DSpark | 0x6004 | m_fDisplayHeight | `float` |
| C2DSpark | 0x6008 | m_nCurrentSpark | `int` |
| C2DSpark | 0x600c | m_fBigLum | `float` |
| C2DSpark | 0x6010 | m_nBigLumX | `int` |
| C2DSpark | 0x6014 | m_nBigLumY | `int` |
| C2DSpark | 0x6018 | m_bMouseTrack | `BYTE` |
| C2DSpark | 0x601c | m_pAdditiveBlend | `gbRenderEffect *` |
| C2DSpark | 0x6020 | m_pRedBig | `gbTexture *` |
| C2DSpark | 0x6024 | m_pRedBigArray | `gbTextureArray *` |
| C2DSpark | 0x6028 | m_pBlue16 | `gbTexture *` |
| C2DSpark | 0x602c | m_pBlue16Array | `gbTextureArray *` |
| C2DSpark | 0x6030 | m_pGreen16 | `gbTexture *` |
| C2DSpark | 0x6034 | m_pGreen16Array | `gbTextureArray *` |
| C2DSpark | 0x6038 | m_pRed16 | `gbTexture *` |
| C2DSpark | 0x603c | m_pRed16Array | `gbTextureArray *` |
| C2DSpark | 0x6040 | m_pYellow16 | `gbTexture *` |
| C2DSpark | 0x6044 | m_pYellow16Array | `gbTextureArray *` |
| C2DSpark | 0x6048 | m_Quad | `gbUIQuad` |
| C2DSpark_tagSpark | 0x0 | pTexture1 | `gbTexture *` |
| C2DSpark_tagSpark | 0x10 | pTexture3 | `gbTexture *` |
| C2DSpark_tagSpark | 0x14 | pTextureWrap3 | `void *` |
| C2DSpark_tagSpark | 0x18 | pTexture4 | `gbTexture *` |
| C2DSpark_tagSpark | 0x1c | pTextureWrap4 | `int` |
| C2DSpark_tagSpark | 0x20 | pTexture5 | `gbTexture *` |
| C2DSpark_tagSpark | 0x24 | pTextureWrap5 | `void *` |
| C2DSpark_tagSpark | 0x28 | nRenderEffect | `int` |
| C2DSpark_tagSpark | 0x2c | pRenderEffect | `int` |
| C2DSpark_tagSpark | 0x4 | pTextureWrap1 | `void *` |
| C2DSpark_tagSpark | 0x8 | pTexture2 | `int` |
| C2DSpark_tagSpark | 0xc | pTextureWrap2 | `int` |
| C3DSpark | 0x0 | m_Spark | `C3DSpark_tagSpark[128]` |
| C3DSpark | 0x1c00 | m_nCurrentSpark | `int` |
| C3DSpark | 0x1c04 | m_pAdditiveBlend | `gbRenderEffect *` |
| C3DSpark | 0x1c08 | m_pRedBig | `gbTexture *` |
| C3DSpark | 0x1c0c | m_pRedBigArray | `gbTextureArray *` |
| C3DSpark | 0x1c10 | m_pBlue16 | `gbTexture *` |
| C3DSpark | 0x1c14 | m_pBlue16Array | `gbTextureArray *` |
| C3DSpark | 0x1c18 | m_pGreen16 | `gbTexture *` |
| C3DSpark | 0x1c1c | m_pGreen16Array | `gbTextureArray *` |
| C3DSpark | 0x1c20 | m_pRed16 | `gbTexture *` |
| C3DSpark | 0x1c24 | m_pRed16Array | `gbTextureArray *` |
| C3DSpark | 0x1c28 | m_pYellow16 | `gbTexture *` |
| C3DSpark | 0x1c2c | m_pYellow16Array | `gbTextureArray *` |
| C3DSpark | 0x1c30 | m_GeomQuad | `gbGeomQuad[128]` |
| C3DSpark_tagSpark | 0x0 | _tail_000 | `char[56]` |
| CAccelCentripetalPolicy | 0x0 | _tail_000 | `char[4]` |
| CAcceleratedMotionPolicy | 0xc | _vAcceleration | `gbVec3D` |
| CArrayList | 0x0 | m_ArrayListType | `ArrayListType` |
| CArrayList | 0x10 | m_NumEntriesAllocated | `unsigned int` |
| CArrayList | 0x4 | m_pData | `char *` |
| CArrayList | 0x8 | m_BytesPerEntry | `unsigned int` |
| CArrayList | 0xc | m_NumEntries | `unsigned int` |
| CCBAI | 0x0 | m_bNewRole | `unsigned char[11]` |
| CCBAI | 0x10 | m_pRoleState | `CCBRoleState *` |
| CCBAI | 0x14 | m_pUtil | `CUtil *` |
| CCBAI | 0x18 | m_VA | `tagVA` |
| CCBAI | 0x230 | m_VAF | `tagVAF[32]` |
| CCBAI | 0x30 | m_VAO | `tagVAO[32]` |
| CCBAI | 0x630 | m_Demand | `tagDemand[10][11]` |
| CCBAI | 0xc | m_pCBSystem | `CCBSystem *` |
| CCBAI | 0xd60 | m_nDemandThreadTracer | `int` |
| CCBAI | 0xd68 | m_bDemandThreadTracer | `unsigned char` |
| CCBAI | 0xe00 | m_nHandleEnemyWell | `int` |
| CCBAI | 0xe08 | m_nTodo_E08 | `unsigned char` |
| CCBAIWindow | 0x48 | m_pBack | `UIStatic *` |
| CCBAIWindow | 0x4c | m_pName | `UIStatic *[5]` |
| CCBAIWindow | 0x60 | m_pAttack | `UIPushButton *` |
| CCBAIWindow | 0x64 | m_pItem | `UIPushButton *` |
| CCBAIWindow | 0x68 | m_pSkill | `UIPushButton *` |
| CCBAIWindow | 0x6c | m_pMagic | `UIPushButton *` |
| CCBAIWindow | 0x70 | m_pAffirmative | `UIPushButton *` |
| CCBAIWindow | 0x74 | m_pAI | `UIPushButton *` |
| CCBAIWindow | 0x78 | m_pOk | `UIButton *` |
| CCBAIWindow | 0x7c | m_nIndex | `int` |
| CCBAttackSequen | 0x0 | m_pCBSystem | `CCBSystem *` |
| CCBAttackSequen | 0x1c4 | m_bEnable | `unsigned char` |
| CCBAttackSequen | 0x1c5 | m_bPause | `unsigned char` |
| CCBAttackSequen | 0x1c6 | m_bVisible | `unsigned char` |
| CCBAttackSequen | 0x1c7 | m_bLocked | `unsigned char` |
| CCBAttackSequen | 0x4 | m_pUI | `CCBUI *` |
| CCBAttackSequen | 0x8 | m_pRole | `CCBRoleState *` |
| CCBAttackSequen | 0xc | m_Sequen | `tagAttackSequen[11]` |
| CCBCamControl | 0x10 | m_nTodo_010 | `gbVolModNode *` |
| CCBCamControl | 0x2594 | m_nCurCamIdx | `int` |
| CCBCamControl | 0x260 | m_PanelSlots | `CCBPanelSlot` |
| CCBCamControl | 0x34 | m_fCamBlendA | `float` |
| CCBCamControl | 0x38 | m_fCamBlendB | `float` |
| CCBCamControl | 0x3c | m_CamCtrlData | `int` |
| CCBCamControl | 0x3cfb8 | m_RenderQueue | `UIParticle[98]` |
| CCBCamControl | 0x4af48 | m_SelectRect | `int[4]` |
| CCBCamControl | 0x5558 | m_nCurPageTab | `int` |
| CCBCamControl | 0x5d9ec | m_SlotButtons | `UIButton[5]` |
| CCBCamControl | 0x5f360 | m_TabLists | `_BYTE[6040]` |
| CCBCamControl | 0x68fb0 | m_pStage | `CCBStage *` |
| CCBCamControl | 0x68fb4 | m_pCam | `CCBStageCam *` |
| CCBCamControl | 0x68fb8 | m_pUtil | `CUtil *` |
| CCBCamControl | 0x68fbc | m_bRunning | `unsigned char` |
| CCBCamControl | 0x68fc0 | m_fp | `char *` |
| CCBCamControl | 0x68fd0 | m_nCurList | `int` |
| CCBCamControl | 0x68fd4 | m_nCurTask | `int` |
| CCBCamControl | 0x68fd8 | m_fStartSpeed | `float` |
| CCBCamControl | 0x68fdc | m_fNextSpeed | `float` |
| CCBCamControl | 0x68fe0 | m_vecSpeed | `gbVec3D` |
| CCBCamControl | 0x68fec | m_vecNextSpeed | `gbVec3D` |
| CCBCamControl | 0x68ff8 | m_fDistance | `float` |
| CCBCamControl | 0x68ffc | m_fQuake | `float` |
| CCBCamControl | 0x69000 | m_fQuakeDec | `float` |
| CCBCamControl | 0x69004 | m_fQuakeFre | `float` |
| CCBCamControl | 0x69008 | m_StartPos | `tagCam` |
| CCBCamControl | 0x69020 | m_CurPos | `tagCam` |
| CCBCamControl | 0x69038 | m_vecCurPos | `gbVec3D` |
| CCBCamControl | 0x69044 | m_OBBox | `gbOBBox` |
| CCBCamControl | 0x69090 | m_pPointer | `gbGeomNode *` |
| CCBCamControl | 0x69094 | m_vecCircleCenter | `gbVec3D` |
| CCBCamControl | 0x690a0 | m_vecCircleEnd | `gbVec3D` |
| CCBCamControl | 0x690ac | m_bShowCircleSet | `unsigned char` |
| CCBCamControl | 0x690ad | m_bCircleCenterSelected | `unsigned char` |
| CCBCamControl | 0x690ae | m_bCircleEndSelected | `unsigned char` |
| CCBCamControl | 0x8 | m_pvecCenter | `gbVec3D *` |
| CCBCamControl | 0x984 | m_nList | `gbRefObject *` |
| CCBCamControl | 0x988 | m_nPointerUnderMouse | `int` |
| CCBCamControl | 0x98c | m_CamEntries | `int[1794]` |
| CCBCamControl | 0xc | m_nTodo_00C | `float` |
| CCBControl | 0x0 | m_pCBSystem | `CCBSystem *` |
| CCBControl | 0x10 | m_pUI | `CCBUI *` |
| CCBControl | 0x18 | m_DeltaTime | `double` |
| CCBControl | 0x20 | m_nController | `int` |
| CCBControl | 0x24 | m_bActive | `unsigned char` |
| CCBControl | 0x25 | m_bForceRelease | `unsigned char` |
| CCBControl | 0x28 | m_InputData | `tagControlData` |
| CCBControl | 0x38 | m_CmdData | `tagCmdData` |
| CCBControl | 0x4 | m_pAttackSequen | `CCBAttackSequen *` |
| CCBControl | 0x64 | m_bShowRightPanel | `unsigned char` |
| CCBControl | 0x68 | m_nCurThread | `int` |
| CCBControl | 0x6c | m_nThread | `int` |
| CCBControl | 0x70 | m_Thread | `tagControlThread[4]` |
| CCBControl | 0x8 | m_pStage | `CCBStage *` |
| CCBControl | 0xc | m_pRoleState | `CCBRoleState *` |
| CCBControlWindow | 0x48 | m_pBack | `UIStatic *` |
| CCBControlWindow | 0x4c | m_pButtonAttack | `UIButton *` |
| CCBControlWindow | 0x50 | m_pButtonSkill | `UIButton *` |
| CCBControlWindow | 0x54 | m_pButtonMagic | `UIButton *` |
| CCBControlWindow | 0x58 | m_pButtonItem | `UIButton *` |
| CCBControlWindow | 0x5c | m_pButtonDefence | `UIButton *` |
| CCBControlWindow | 0x60 | m_pButtonLineup | `UIButton *` |
| CCBControlWindow | 0x64 | m_pButtonAI | `UIButton *` |
| CCBControlWindow | 0x68 | m_pButtonFlee | `UIButton *` |
| CCBControlWindow | 0x6c | m_pButtonProtect | `UIButton *` |
| CCBControlWindow | 0x70 | m_CurCtrl | `UIWnd *` |
| CCBControlWindow | 0x74 | m_CurCtrl_1 | `UIWnd *` |
| CCBControlWindow | 0x78 | m_CurCtrl_2 | `UIWnd *` |
| CCBDisplayChain | 0x0 | m_pStage | `CCBStage *` |
| CCBDisplayChain | 0x10 | m_nItemNum | `int` |
| CCBDisplayChain | 0x14 | m_ShowItem | `tagShowItem[64]` |
| CCBDisplayChain | 0x4 | m_pScene | `CCBStageScene *` |
| CCBDisplayChain | 0x4614 | m_byScreenQuadAlpha | `unsigned char` |
| CCBDisplayChain | 0x8 | m_DefaultColor | `tagRGBQUAD` |
| CCBDisplayChain | 0xc | m_ScreenQuadColor | `gbColorQuad` |
| CCBEditor | 0x0 | m_fpThis | `CCBEditor *` |
| CCBEditor | 0x1f48 | m_dwSelectFighter | `int[11]` |
| CCBEditor | 0x1f74 | m_nCurCCTList | `int` |
| CCBEditor | 0x1f78 | m_nCurCCT | `int` |
| CCBEditor | 0x1f7c | m_nCurEffClass | `int` |
| CCBEditor | 0x1f80 | m_nCurEffObjType | `int` |
| CCBEditor | 0x1f84 | m_nCurEffGroup | `int` |
| CCBEditor | 0x1f88 | m_nCurEffObjInGroup | `int` |
| CCBEditor | 0x1f8c | m_nCurEffObjTask | `int` |
| CCBEditor | 0x1f90 | m_dwTrickID | `unsigned long[384]` |
| CCBEditor | 0x2590 | m_nCurSelectedEffGroup | `int` |
| CCBEditor | 0x2594 | m_nCurSelectedTrick | `int` |
| CCBEditor | 0x4 | m_pRoleState | `CCBRoleState *` |
| CCBEditor | 0x8 | m_NewItem | `tagNewItem[500]` |
| CCBFiveNimbusWindow | 0x48 | pCtrlButton | `UIButtonEX *[5]` |
| CCBFiveNimbusWindow | 0x5c | pMiddle | `UIButtonEX *` |
| CCBFiveNimbusWindow | 0x60 | m_OpenWindow | `OpenFNWindow` |
| CCBFiveNimbusWindow | 0x6c | m_nimbus | `int[5]` |
| CCBFiveNimbusWindow | 0x80 | m_state | `int[5]` |
| CCBFiveNimbusWindow | 0x94 | m_nimbusStep | `int` |
| CCBFiveNimbusWindow | 0x98 | m_bShow | `unsigned char` |
| CCBFiveNimbusWindow | 0x99 | m_bLock | `unsigned char` |
| CCBFiveNimbusWindow | 0x9c | m_counter | `int` |
| CCBItemWindow | 0x48 | m_pBack | `UIStatic *` |
| CCBItemWindow | 0x4c | m_pDescription | `UIStatic *` |
| CCBItemWindow | 0x50 | m_pItemList | `UIListBox *[3]` |
| CCBItemWindow | 0x5c | m_pButtonRecover | `UIPushButton *` |
| CCBItemWindow | 0x60 | m_pButtonAttack | `UIPushButton *` |
| CCBItemWindow | 0x64 | m_pButtonTreasure | `UIPushButton *` |
| CCBItemWindow | 0x68 | m_nActivePage | `int` |
| CCBLineupWindow | 0x48 | m_nInitRoleFaceLineup | `int[5]` |
| CCBLineupWindow | 0x5c | m_pBack | `UIStatic *` |
| CCBLineupWindow | 0x60 | m_pFace | `UIStatic *[5]` |
| CCBLineupWindow | 0x74 | m_nSelected | `int` |
| CCBLineupWindow | 0x78 | m_pUI | `CCBUI *` |
| CCBMagicWindow | 0x48 | m_pBack | `UIStatic *` |
| CCBMagicWindow | 0x4c | m_pMagicList | `UIListBox *[6]` |
| CCBMagicWindow | 0x64 | m_pButtonWater | `UIPushButton *` |
| CCBMagicWindow | 0x68 | m_pButtonFire | `UIPushButton *` |
| CCBMagicWindow | 0x6c | m_pButtonThunder | `UIPushButton *` |
| CCBMagicWindow | 0x70 | m_pButtonWind | `UIPushButton *` |
| CCBMagicWindow | 0x74 | m_pButtonEarth | `UIPushButton *` |
| CCBMagicWindow | 0x78 | m_pButtonDouble | `UIPushButton *` |
| CCBMagicWindow | 0x7c | m_nActivePage | `int` |
| CCBMagicWindow | 0xb8 | m_nBtnX | `int` |
| CCBMagicWindow | 0xc4 | m_nBtnY | `int` |
| CCBMagicWindow | 0xc8 | m_nBtnState | `int` |
| CCBPanelSlot | 0x10 | m_nMarginX2 | `int` |
| CCBPanelSlot | 0x14 | m_nDimH2 | `int` |
| CCBPanelSlot | 0x18 | m_nEdgeR2 | `int` |
| CCBPanelSlot | 0x1c | m_nEdgeB2 | `int` |
| CCBPanelSlot | 0x20 | m_fMarginX | `float` |
| CCBPanelSlot | 0x24 | m_fDimH | `float` |
| CCBPanelSlot | 0x28 | m_nClipL | `int` |
| CCBPanelSlot | 0x2c | m_nClipT | `int` |
| CCBPanelSlot | 0x30 | m_nClipR | `int` |
| CCBPanelSlot | 0x34 | m_nClipB | `int` |
| CCBPanelSlot | 0x38 | m_nClipL2 | `int` |
| CCBPanelSlot | 0x3c | m_nClipT2 | `int` |
| CCBPanelSlot | 0x4 | m_nDimH | `int` |
| CCBPanelSlot | 0x40 | m_nClipR2 | `int` |
| CCBPanelSlot | 0x44 | m_nClipB2 | `int` |
| CCBPanelSlot | 0x48 | m_nPosX | `int` |
| CCBPanelSlot | 0x4c | m_nPosY | `int` |
| CCBPanelSlot | 0x5c | m_Widget | `char[384]` |
| CCBPanelSlot | 0x8 | m_nEdgeR | `int` |
| CCBPanelSlot | 0xc | m_nEdgeB | `int` |
| CCBParabolaWindow | 0x48 | m_pBack | `UIStatic *` |
| CCBParabolaWindow | 0x4c | m_pDescription | `UIStatic *` |
| CCBParabolaWindow | 0x50 | m_pItemList | `UIListBox *` |
| CCBProtectWindow | 0x48 | m_pBack | `UIStatic *` |
| CCBProtectWindow | 0x4c | m_pWHFace | `UIPushButton *` |
| CCBProtectWindow | 0x50 | m_pWPXFace | `UIPushButton *` |
| CCBProtectWindow | 0x54 | m_pWHLove | `UIProgressBar *` |
| CCBProtectWindow | 0x58 | m_pWPXLove | `UIProgressBar *` |
| CCBProtectWindow | 0x5c | m_pOk | `UIButton *` |
| CCBResultWindow | 0x48 | m_pBack | `UIStatic *` |
| CCBResultWindow | 0x4c | m_pWind | `UIStatic *` |
| CCBResultWindow | 0x50 | m_pThunder | `UIStatic *` |
| CCBResultWindow | 0x54 | m_pWater | `UIStatic *` |
| CCBResultWindow | 0x58 | m_pFire | `UIStatic *` |
| CCBResultWindow | 0x5c | m_pEarth | `UIStatic *` |
| CCBResultWindow | 0x60 | m_pDouble | `UIStatic *` |
| CCBResultWindow | 0x64 | m_pEXP | `UIStatic *` |
| CCBResultWindow | 0x68 | m_pLevel | `UIStatic *` |
| CCBResultWindow | 0x6c | m_pFace | `UIStatic *[11]` |
| CCBResultWindow | 0x98 | m_pHGM | `UIStatic *` |
| CCBResultWindow | 0x9c | m_pHP | `UIProgressBar *` |
| CCBResultWindow | 0xa0 | m_pGP | `UIProgressBar *` |
| CCBResultWindow | 0xa4 | m_pMP | `UIProgressBar *` |
| CCBResultWindow | 0xa8 | m_pUI | `CCBUI *` |
| CCBResultWindow | 0xac | m_nIndex | `int` |
| CCBResultWindow | 0xb0 | m_bClosed | `unsigned char` |
| CCBRoleState | 0x118 | m_nDamageThisRound | `int` |
| CCBRoleState | 0x120 | m_nState3 | `int[18]` |
| CCBRoleState | 0x168 | m_nTodo_168 | `UIFrameWnd` |
| CCBRoleState | 0x1dfc | m_byteFlags | `unsigned char` |
| CCBRoleState | 0x200 | m_fLastDialogTime | `float` |
| CCBRoleState | 0x204 | m_bCombatDialog | `unsigned char` |
| CCBRoleState | 0x208 | m_pCBSystem | `CCBSystem *` |
| CCBRoleState | 0x20c | m_pStage | `CCBStage *` |
| CCBRoleState | 0x210 | m_pUI | `CCBUI *` |
| CCBRoleState | 0x214 | m_pUtil | `CUtil *` |
| CCBRoleState | 0x218 | m_bWeSneakAttackEnemy | `unsigned char` |
| CCBRoleState | 0x219 | m_bEnemySneakAttackUs | `unsigned char` |
| CCBRoleState | 0x21c | m_nMaxRound | `int` |
| CCBRoleState | 0x220 | m_nBossRound | `int` |
| CCBRoleState | 0x224 | m_bMustFail | `unsigned char` |
| CCBRoleState | 0x225 | m_bFleeAlwaysSuccess | `unsigned char` |
| CCBRoleState | 0x226 | m_bCreatedNewRole | `unsigned char` |
| CCBRoleState | 0x228 | m_Role | `tagRoleState[11]` |
| CCBRoleState | 0x2870 | m_nTodo_2870 | `unsigned char` |
| CCBRoleState | 0x287c | m_BufferData | `char[1628]` |
| CCBRoleState | 0x2ed8 | m_RoleXor | `tagRoleState[11]` |
| CCBRoleState | 0x48b8 | m_SlotUIWnd | `UIWnd` |
| CCBRoleState | 0x490c | m_fLerpCurX | `float` |
| CCBRoleState | 0x4910 | m_fLerpCurY | `float` |
| CCBRoleState | 0x4914 | m_nLerpTargetX | `int` |
| CCBRoleState | 0x4918 | m_nLerpTargetY | `int` |
| CCBRoleState | 0x491c | m_nLerpDestX | `int` |
| CCBRoleState | 0x4920 | m_nLerpDestY | `int` |
| CCBRoleState | 0x492c | m_nLerpDir | `int` |
| CCBRoleState | 0x4939 | m_bLerpDone | `unsigned char` |
| CCBRoleState | 0x493c | m_fLerpSpeed | `float` |
| CCBRoleState | 0x495c | m_fSpringPosX | `float` |
| CCBRoleState | 0x4960 | m_fSpringPosY | `float` |
| CCBRoleState | 0x4964 | m_fSpringTargX | `float` |
| CCBRoleState | 0x4968 | m_fSpringTargY | `float` |
| CCBRoleState | 0x496c | m_fSpringPrevX | `float` |
| CCBRoleState | 0x4970 | m_fSpringPrevY | `float` |
| CCBRoleState | 0x4974 | m_nSpringTargetX | `int` |
| CCBRoleState | 0x4978 | m_nSpringTargetY | `int` |
| CCBRoleState | 0x497c | m_nSpringDir | `int` |
| CCBRoleState | 0x4980 | m_fSpringAccelX | `float` |
| CCBRoleState | 0x4984 | m_fSpringAccelY | `float` |
| CCBRoleState | 0x4988 | m_bSpringDoneX | `unsigned char` |
| CCBRoleState | 0x4989 | m_bSpringDoneY | `unsigned char` |
| CCBRoleState | 0x498c | m_fSpringSpeed | `float` |
| CCBRoleState | 0x4a70 | m_SlotWidgets | `UIWnd` |
| CCBRoleState | 0x4c | m_nState_04C | `int` |
| CCBRoleState | 0x4cd0 | m_SlotRects | `int` |
| CCBRoleState | 0x4d74 | m_SlotRightEdge | `int` |
| CCBRoleState | 0x4db8 | m_nSlotStartY | `int` |
| CCBRoleState | 0x4dbc | m_nSlotSpacing | `int` |
| CCBRoleState | 0x4dc0 | m_nSlotHeight | `int` |
| CCBRoleState | 0x4dc4 | m_nSlotWidth | `int` |
| CCBRoleState | 0x4dc8 | m_bySlotVisible | `unsigned char` |
| CCBRoleState | 0x4e60 | m_pScene | `UIScene *` |
| CCBRoleState | 0x4fb8 | m_Static_20408 | `UIStatic` |
| CCBRoleState | 0x5050 | m_bVideoPlayed | `unsigned char` |
| CCBRoleState | 0x5054 | m_nVideoState | `int` |
| CCBRoleState | 0x5060 | m_nCurrentTaskID | `int` |
| CCBRoleState | 0x5064 | m_nEffCurA | `int` |
| CCBRoleState | 0x5068 | m_nEffCurB | `int` |
| CCBRoleState | 0x5070 | m_nEffTarget1 | `int` |
| CCBRoleState | 0x5074 | m_nEffTarget2 | `int` |
| CCBRoleState | 0x5078 | m_nEffTransFrames | `int` |
| CCBRoleState | 0x507c | m_nEffSwapA | `int` |
| CCBRoleState | 0x5080 | m_nEffSwapB | `int` |
| CCBRoleState | 0x5088 | m_nEffCurC | `int` |
| CCBRoleState | 0x508c | m_nEffSwapC | `int` |
| CCBRoleState | 0x5090 | m_nEffCurD | `int` |
| CCBRoleState | 0x5094 | m_nEffTransFrames2 | `int` |
| CCBRoleState | 0x5098 | m_nEffCurE | `int` |
| CCBRoleState | 0x509c | m_nEffSwapE | `int` |
| CCBRoleState | 0x50a0 | m_fTimeFund | `float` |
| CCBRoleState | 0x55c8 | m_bScrollEnableA | `unsigned char` |
| CCBRoleState | 0x55c9 | m_bScrollEnableB | `unsigned char` |
| CCBRoleState | 0x55cc | m_nScrollOffset | `int` |
| CCBRoleState | 0x55d0 | m_nScrollTarget | `int` |
| CCBRoleState | 0x5654 | m_nFadeFlags | `int` |
| CCBRoleState | 0x5658 | m_nFadeAlpha | `int` |
| CCBRoleState | 0x565c | m_nFadeTimer | `int` |
| CCBRoleState | 0x56cc | m_BattleFlags | `int` |
| CCBRoleState | 0x60 | m_nState_060 | `int` |
| CCBRoleState | 0x64 | m_nCombatResult | `int` |
| CCBRoleState | 0x94 | m_nTargetRoleIdx | `int` |
| CCBRoleState | 0x9c | m_nSelectedAction | `int` |
| CCBRoleState | 0xa0 | m_nSelectedTarget | `int` |
| CCBRoleState | 0xa4 | m_nSelectedItem | `int` |
| CCBRoleState | 0xa8 | m_nState2 | `int[26]` |
| CCBRoleStatePanel | 0x0 | m_Headbk | `UIStatic` |
| CCBRoleStatePanel | 0x1014 | m_NeedRc | `tagRECT` |
| CCBRoleStatePanel | 0x1f0 | m_Name | `UIStatic` |
| CCBRoleStatePanel | 0x288 | m_Jing | `UIStatic` |
| CCBRoleStatePanel | 0x320 | m_JingBar | `UIProgressBar` |
| CCBRoleStatePanel | 0x414 | m_JingVal | `UIStatic` |
| CCBRoleStatePanel | 0x4ac | m_Shen | `UIStatic` |
| CCBRoleStatePanel | 0x544 | m_ShenBar | `UIProgressBar` |
| CCBRoleStatePanel | 0x638 | m_ShenVal | `UIStatic` |
| CCBRoleStatePanel | 0x6d0 | m_Qi | `UIStatic` |
| CCBRoleStatePanel | 0x768 | m_QiBar | `UIProgressBar` |
| CCBRoleStatePanel | 0x85c | m_QiVal | `UIStatic` |
| CCBRoleStatePanel | 0x8f4 | m_AttFrameHead | `UIStatic` |
| CCBRoleStatePanel | 0x98 | m_Head | `UIButton` |
| CCBRoleStatePanel | 0x98c | m_F | `UIStatic` |
| CCBRoleStatePanel | 0xa24 | m_W | `UIStatic` |
| CCBRoleStatePanel | 0xabc | m_S | `UIStatic` |
| CCBRoleStatePanel | 0xb54 | m_Y | `UIStatic` |
| CCBRoleStatePanel | 0xbec | m_Exp | `UIStatic` |
| CCBRoleStatePanel | 0xc84 | m_RoleAtt | `UIStatic[5]` |
| CCBRoleStatePanel | 0xf7c | m_NeedArrow | `UIStatic` |
| CCBRoleStatePanelM | 0x0 | m_Headbk | `UIStatic` |
| CCBRoleStatePanelM | 0x1014 | m_NeedRc | `tagRECT` |
| CCBRoleStatePanelM | 0x1f0 | m_Name | `UIStatic` |
| CCBRoleStatePanelM | 0x288 | m_Jing | `UIStatic` |
| CCBRoleStatePanelM | 0x320 | m_JingBar | `UIProgressBar` |
| CCBRoleStatePanelM | 0x414 | m_JingVal | `UIStatic` |
| CCBRoleStatePanelM | 0x4ac | m_Shen | `UIStatic` |
| CCBRoleStatePanelM | 0x544 | m_ShenBar | `UIProgressBar` |
| CCBRoleStatePanelM | 0x638 | m_ShenVal | `UIStatic` |
| CCBRoleStatePanelM | 0x6d0 | m_Qi | `UIStatic` |
| CCBRoleStatePanelM | 0x768 | m_QiBar | `UIProgressBar` |
| CCBRoleStatePanelM | 0x85c | m_QiVal | `UIStatic` |
| CCBRoleStatePanelM | 0x8f4 | m_AttFrameHead | `UIStatic` |
| CCBRoleStatePanelM | 0x98 | m_Head | `UIButton` |
| CCBRoleStatePanelM | 0x98c | m_F | `UIStatic` |
| CCBRoleStatePanelM | 0xa24 | m_W | `UIStatic` |
| CCBRoleStatePanelM | 0xabc | m_S | `UIStatic` |
| CCBRoleStatePanelM | 0xb54 | m_Y | `UIStatic` |
| CCBRoleStatePanelM | 0xbec | m_Exp | `UIStatic` |
| CCBRoleStatePanelM | 0xc84 | m_RoleAtt | `UIStatic[5]` |
| CCBRoleStatePanelM | 0xf7c | m_NeedArrow | `UIStatic` |
| CCBRoleStatePanelS | 0x0 | m_Headbk | `UIStatic` |
| CCBRoleStatePanelS | 0x130 | m_Name | `UIStatic` |
| CCBRoleStatePanelS | 0x1c8 | m_Jing | `UIStatic` |
| CCBRoleStatePanelS | 0x260 | m_JingBar | `UIProgressBar` |
| CCBRoleStatePanelS | 0x354 | m_JingVal | `UIStatic` |
| CCBRoleStatePanelS | 0x3ec | m_Shen | `UIStatic` |
| CCBRoleStatePanelS | 0x484 | m_ShenBar | `UIProgressBar` |
| CCBRoleStatePanelS | 0x578 | m_ShenVal | `UIStatic` |
| CCBRoleStatePanelS | 0x610 | m_Qi | `UIStatic` |
| CCBRoleStatePanelS | 0x6a8 | m_QiBar | `UIProgressBar` |
| CCBRoleStatePanelS | 0x79c | m_QiVal | `UIStatic` |
| CCBRoleStatePanelS | 0x834 | m_Shade | `UIStatic` |
| CCBRoleStatePanelS | 0x8cc | m_Portrait | `UIStatic` |
| CCBRoleStatePanelS | 0x964 | m_Level | `UIStatic` |
| CCBRoleStatePanelS | 0x98 | m_Head | `UIStatic` |
| CCBRoleStatePanelS | 0x9fc | m_ExpVal | `UIStatic` |
| CCBRoleStatePanelS | 0xa94 | m_NextLv | `UIStatic` |
| CCBRoleStatePanelS | 0xb2c | m_WuLing | `UIStatic[5]` |
| CCBRoleStatePanelS | 0xe24 | m_FWSY | `UIStatic` |
| CCBRoleStatePanelS | 0xebc | m_FWSYrc | `tagRECT` |
| CCBSkillWindow | 0x48 | m_pBack | `UIStatic *` |
| CCBSkillWindow | 0x4c | m_pDescription | `UIStatic *` |
| CCBSkillWindow | 0x50 | m_pSkillList | `UIListBox *[1]` |
| CCBStage | 0x58 | m_pShadow | `CCBStageShadow *` |
| CCBStage | 0x5c | m_pEffect | `CCBStageEffect *` |
| CCBStage | 0x60 | m_BFARole | `int` |
| CCBStage | 0x64 | m_BFARound | `int` |
| CCBStage | 0x68 | m_ptMousePos | `tagPOINT` |
| CCBStage | 0x70 | m_nSelectedRole | `int` |
| CCBStage | 0x74 | m_bRoleSelected | `unsigned char[11]` |
| CCBStage | 0x7f | m_bHideSceneAndRole | `unsigned char` |
| CCBStage | 0x94 | m_nTodo_094 | `int` |
| CCBStage | 0x98 | m_nStageStatus | `unsigned char` |
| CCBStage | 0x99 | m_nTodo_99 | `unsigned char` |
| CCBStage | 0x9a | m_nTodo_9A | `unsigned char` |
| CCBStage | 0x9b | m_nTodo_9B | `unsigned char` |
| CCBStage | 0x9c | m_nTaskCount | `int` |
| CCBStage | 0xa0 | m_nClearRoleAllTask | `int` |
| CCBStage | 0xa4 | m_nRoleSlot | `int` |
| CCBStage | 0xa48a8 | m_nTodo_A48A8 | `int` |
| CCBStage | 0xa48c0 | m_dwAniFlagOver | `unsigned int` |
| CCBStage | 0xa8 | m_TaskGroups | `CCBTaskGroup[256]` |
| CCBStageCam | 0x1280 | m_EditorCam | `tagCam[64]` |
| CCBStageCam | 0x2b4 | m_pStage | `CCBStage *` |
| CCBStageCam | 0x2b8 | m_pUtil | `CUtil *` |
| CCBStageCam | 0x2bc | m_fLastMouseX | `float` |
| CCBStageCam | 0x2c0 | m_fLastMouseY | `float` |
| CCBStageCam | 0x2c8 | m_fp | `char *` |
| CCBStageCam | 0x2d8 | m_nTask | `int` |
| CCBStageCam | 0x2dc | m_nCurTask | `int` |
| CCBStageCam | 0x2e0 | m_Task | `tagCamTask[50]` |
| CCBStageEffect | 0x0 | m_DeltaTime | `double` |
| CCBStageEffect | 0x10 | m_EnvLight | `gbVolModNode` |
| CCBStageEffect | 0x8 | m_pStage | `CCBStage *` |
| CCBStageEffect | 0x984 | m_pGeomFlashEffect | `gbRenderEffect *` |
| CCBStageEffect | 0x988 | m_pGeomFlashEffect_t | `gbRenderEffect *` |
| CCBStageEffect | 0x98c | m_Linker | `tagEffLinker[4]` |
| CCBStageEffect | 0xc | m_pCBSystem | `CCBSystem *` |
| CCBStageEffect | 0xec | m_Light | `gbVolModNode[10]` |
| CCBStageRole | 0x0 | m_pStage | `CCBStage *` |
| CCBStageRole | 0x108 | m_bValid | `unsigned char` |
| CCBStageRole | 0x109 | m_bVisible | `unsigned char` |
| CCBStageRole | 0x10a | m_bPaused | `unsigned char` |
| CCBStageRole | 0x10b | m_bAbsTime | `unsigned char` |
| CCBStageRole | 0x10c | m_fTimeScale | `float` |
| CCBStageRole | 0x110 | m_bAlive | `unsigned char` |
| CCBStageRole | 0x111 | m_bRun | `unsigned char` |
| CCBStageRole | 0x112 | m_bFlash | `unsigned char` |
| CCBStageRole | 0x113 | m_bFlashCounter | `unsigned char` |
| CCBStageRole | 0x114 | m_fFlashTimeKey | `float` |
| CCBStageRole | 0x118 | m_bShowWeapon | `unsigned char` |
| CCBStageRole | 0x11c | m_fBlend | `float` |
| CCBStageRole | 0x120 | m_bBeSelected | `unsigned char` |
| CCBStageRole | 0x124 | m_nIndex | `int` |
| CCBStageRole | 0x128 | m_dwID | `unsigned int` |
| CCBStageRole | 0x12c | m_pActor | `Actor *` |
| CCBStageRole | 0x130 | m_pRawActor | `Actor *` |
| CCBStageRole | 0x134 | m_pWeaponModel | `gbGeomNode *` |
| CCBStageRole | 0x138 | m_vecWeapon | `gbVec3D` |
| CCBStageRole | 0x14 | m_sRoleArray | `Array` |
| CCBStageRole | 0x144 | m_rotWeapon | `gbVec3D` |
| CCBStageRole | 0x150 | m_vNoteThrowPos | `gbVec3D` |
| CCBStageRole | 0x15c | m_vThrowVec | `gbVec3D` |
| CCBStageRole | 0x168 | m_vecLen | `float` |
| CCBStageRole | 0x16c | m_fTask | `float` |
| CCBStageRole | 0x170 | m_fStatus | `float` |
| CCBStageRole | 0x174 | m_bShowWeaponModel | `unsigned char` |
| CCBStageRole | 0x175 | m_bCatching | `unsigned char` |
| CCBStageRole | 0x176 | m_bDelAllTask | `unsigned char` |
| CCBStageRole | 0x178 | m_iState | `int` |
| CCBStageRole | 0x17c | m_bForceFinishThrowingWeapon | `unsigned char` |
| CCBStageRole | 0x180 | m_fMaxThrowSpeed | `float` |
| CCBStageRole | 0x184 | m_fThrowSpeed | `float` |
| CCBStageRole | 0x188 | m_fThrowLen | `float` |
| CCBStageRole | 0x18c | m_ThrowCmdData | `tagCmdData *` |
| CCBStageRole | 0x190 | m_nRotAngle | `int` |
| CCBStageRole | 0x194 | m_nCurActionOff | `int` |
| CCBStageRole | 0x198 | m_nCurActionParam | `int` |
| CCBStageRole | 0x19c | m_nTodo_19C | `int` |
| CCBStageRole | 0x1a0 | m_nTransportRun | `int` |
| CCBStageRole | 0x1a30 | m_dwCurWeaponIndex | `unsigned int` |
| CCBStageRole | 0x1a34 | m_eRoleActState | `ERoleActState` |
| CCBStageRole | 0x1a38 | m_eCurAction | `ACTION_KIND` |
| CCBStageRole | 0x1a3c | m_vecSunDir | `gbVec3D` |
| CCBStageRole | 0x1a4 | m_ActionSlot0 | `int` |
| CCBStageRole | 0x1a48 | m_vecPos | `gbVec3D` |
| CCBStageRole | 0x1a54 | m_vecInitPos | `gbVec3D` |
| CCBStageRole | 0x1a60 | m_vecRunTarget | `gbVec3D` |
| CCBStageRole | 0x1a6c | m_vecRunVelocity | `gbVec3D` |
| CCBStageRole | 0x1a78 | m_fFaceDir | `float` |
| CCBStageRole | 0x1a7c | m_fInitFaceDir | `float` |
| CCBStageRole | 0x1a8 | m_ActionSlot1 | `int` |
| CCBStageRole | 0x1a80 | m_dwCurAniFlag | `unsigned int` |
| CCBStageRole | 0x1a84 | m_dwAniFlagOver | `unsigned int` |
| CCBStageRole | 0x1a88 | m_dwAniFlagWork | `unsigned int` |
| CCBStageRole | 0x1a8c | m_dwAniFlagWork1 | `unsigned int` |
| CCBStageRole | 0x1a90 | m_dwAniFlagWork2 | `unsigned int` |
| CCBStageRole | 0x1a94 | m_dwAniFlagWork3 | `unsigned int` |
| CCBStageRole | 0x1a98 | m_dwAniFlagPause | `unsigned int` |
| CCBStageRole | 0x1a9c | m_dwAniFlagStore | `unsigned int` |
| CCBStageRole | 0x1aa0 | m_dwAniFlagFlyup | `unsigned int` |
| CCBStageRole | 0x1aa4 | m_dwAniFlagFlydown | `unsigned int` |
| CCBStageRole | 0x1aa8 | m_dwAniFlagThrowED | `unsigned int` |
| CCBStageRole | 0x1aac | m_dwAniFlagCatchED | `unsigned int` |
| CCBStageRole | 0x1ab0 | m_dwAniFlagSJump | `unsigned int` |
| CCBStageRole | 0x1ab4 | m_dwAniFlagEJump | `unsigned int` |
| CCBStageRole | 0x1ab8 | m_dwLastExternalActionCRC | `unsigned int` |
| CCBStageRole | 0x1ac | m_ActionSlot2 | `int` |
| CCBStageRole | 0x1b0 | m_nUseRecoverItem | `int` |
| CCBStageRole | 0x1b4 | m_nProperAction | `int` |
| CCBStageRole | 0x1b8 | m_OBBox | `gbOBBox *` |
| CCBStageRole | 0x1bc | m_nOBBox | `int` |
| CCBStageRole | 0x1c0 | m_fActionSpeed0 | `int` |
| CCBStageRole | 0x1c4 | m_nTodo_1C4 | `int` |
| CCBStageRole | 0x1d8 | m_nTodo_1D8 | `int` |
| CCBStageRole | 0x1e4 | m_apSlotData | `int` |
| CCBStageRole | 0x1e8 | m_nTodo_1E8 | `float` |
| CCBStageRole | 0x1f0 | m_nCurState | `int` |
| CCBStageRole | 0x1f4 | m_nActionType0 | `int` |
| CCBStageRole | 0x1f8 | m_bProperCurAction | `unsigned char` |
| CCBStageRole | 0x1f9 | m_bSlotActive0 | `unsigned char` |
| CCBStageRole | 0x1fa | m_bSlotBlocked0 | `unsigned char` |
| CCBStageRole | 0x204 | m_bTransMtl | `unsigned char` |
| CCBStageRole | 0x205 | m_bSpecTransport | `unsigned char` |
| CCBStageRole | 0x206 | m_bGrabed | `unsigned char` |
| CCBStageRole | 0x207 | m_bNormalGrab | `unsigned char` |
| CCBStageRole | 0x208 | m_dwStageTaskID | `unsigned int` |
| CCBStageRole | 0x20c | m_bExternalTask | `unsigned char` |
| CCBStageRole | 0x210 | m_fLeftWeapon | `float` |
| CCBStageRole | 0x214 | m_fRightWeapon | `float` |
| CCBStageRole | 0x218 | m_nTask | `int` |
| CCBStageRole | 0x21c | m_nCurTask | `int` |
| CCBStageRole | 0x220 | m_fp | `char *` |
| CCBStageRole | 0x230 | m_Task | `tagRoleTask[64]` |
| CCBStageRole | 0x24 | m_sRoleData | `char[228]` |
| CCBStageRole | 0x4 | m_pRoleState | `CCBRoleState *` |
| CCBStageRole | 0x8 | m_sLastRole | `char[12]` |
| CCBStageScene | 0x0 | m_pStage | `CCBStage *` |
| CCBStageScene | 0x104 | m_vecInitEnemyLineup | `gbVec3D[7]` |
| CCBStageScene | 0x158 | m_bLoaded | `unsigned char` |
| CCBStageScene | 0x159 | m_sLastScene | `char[256]` |
| CCBStageScene | 0x25c | m_pGeomNode | `gbGeomNode *` |
| CCBStageScene | 0x260 | m_pCvd | `gbGeomNode *` |
| CCBStageScene | 0x264 | m_pLights | `gbVisNode *` |
| CCBStageScene | 0x268 | m_pPointer | `gbGeomNode *` |
| CCBStageScene | 0x26c | m_pCorpse | `gbGeomNode *[11]` |
| CCBStageScene | 0x298 | m_pFling | `gbGeomNode *` |
| CCBStageScene | 0x29c | m_vecFling | `float` |
| CCBStageScene | 0x2a0 | m_nLoadPointer | `int` |
| CCBStageScene | 0x2a4 | m_nFlingState | `int` |
| CCBStageScene | 0x2a8 | m_rotFling | `float` |
| CCBStageScene | 0x2ac | m_fDirSinA | `float` |
| CCBStageScene | 0x2b0 | m_fBlendA | `float` |
| CCBStageScene | 0x2b4 | m_bShowFling | `unsigned char` |
| CCBStageScene | 0x2b8 | m_pFiveLineupEffect | `gbRenderEffect *` |
| CCBStageScene | 0x2bc | m_pFiveLineupTexture | `gbTexture *` |
| CCBStageScene | 0x2c0 | m_pFiveLineupTextureArray | `gbTextureArray *` |
| CCBStageScene | 0x2c4 | m_pFiveLineupCenterTexture | `gbTexture *` |
| CCBStageScene | 0x2c8 | m_pFiveLineupCenterTextureArray | `gbTextureArray *` |
| CCBStageScene | 0x2cc | m_FiveLineupQuad | `gbGeomQuad *` |
| CCBStageScene | 0x2d0 | m_fDirSinB | `float` |
| CCBStageScene | 0x2d4 | m_fBlendB | `float` |
| CCBStageScene | 0x2d8 | m_fDirCosB | `float` |
| CCBStageScene | 0x2dc | m_fBlendRectAX | `float` |
| CCBStageScene | 0x2e0 | m_fBlendRectAY | `float` |
| CCBStageScene | 0x2e4 | m_fBlendRectAW | `float` |
| CCBStageScene | 0x2e8 | m_fBlendRectAH | `float` |
| CCBStageScene | 0x2ec | m_bLoadPointer | `unsigned char` |
| CCBStageScene | 0x2ed | m_nPointerIndex1 | `unsigned char` |
| CCBStageScene | 0x2ee | m_nPointerIndex2 | `unsigned char` |
| CCBStageScene | 0x2ef | m_nPointerData | `unsigned char` |
| CCBStageScene | 0x2f0 | m_nInit | `int` |
| CCBStageScene | 0x2f4 | m_nCamState | `int` |
| CCBStageScene | 0x2f8 | m_fCamPosX | `float` |
| CCBStageScene | 0x2fc | m_fCamPosZ | `float` |
| CCBStageScene | 0x300 | m_fInit | `float` |
| CCBStageScene | 0x304 | m_fCamTargX | `float` |
| CCBStageScene | 0x308 | m_fCamTargZ | `float` |
| CCBStageScene | 0x30c | m_fInitBlend | `float` |
| CCBStageScene | 0x310 | m_FiveLineupCenterQuad | `gbGeomQuad *` |
| CCBStageScene | 0x314 | m_fBlendTime | `float` |
| CCBStageScene | 0x318 | m_nBlendState | `int` |
| CCBStageScene | 0x31c | m_fBlendSpeed | `float` |
| CCBStageScene | 0x320 | m_fBlendRectBX | `float` |
| CCBStageScene | 0x324 | m_fBlendRectBY | `float` |
| CCBStageScene | 0x328 | m_fBlendRectBW | `float` |
| CCBStageScene | 0x32c | m_fBlendRectBH | `float` |
| CCBStageScene | 0x330 | m_nReset | `int` |
| CCBStageScene | 0x334 | m_fDirSinC | `float` |
| CCBStageScene | 0x338 | m_fBlendC | `float` |
| CCBStageScene | 0x33c | m_fDirCosC | `float` |
| CCBStageScene | 0x340 | m_fDirSinD | `float` |
| CCBStageScene | 0x344 | m_fBlendD | `float` |
| CCBStageScene | 0x348 | m_fDirCosD | `float` |
| CCBStageScene | 0x34c | m_fDirSinE | `float` |
| CCBStageScene | 0x350 | m_fBlendE | `float` |
| CCBStageScene | 0x354 | m_EnemyFiveLineupQuad | `gbGeomQuad *` |
| CCBStageScene | 0x358 | m_fDirSinF | `float` |
| CCBStageScene | 0x35c | m_fBlendF | `float` |
| CCBStageScene | 0x360 | m_fDirCosF | `float` |
| CCBStageScene | 0x364 | m_fBlendWeight0 | `float` |
| CCBStageScene | 0x368 | m_fBlendWeight1 | `float` |
| CCBStageScene | 0x36c | m_fBlendWeight2 | `float` |
| CCBStageScene | 0x370 | m_fBlendWeight3 | `float` |
| CCBStageScene | 0x378 | m_fCurAxisX | `float` |
| CCBStageScene | 0x37c | m_fCurAxisY | `float` |
| CCBStageScene | 0x380 | m_fCurAxisZ | `float` |
| CCBStageScene | 0x384 | m_fInitAxisX | `float` |
| CCBStageScene | 0x388 | m_fInitAxisY | `float` |
| CCBStageScene | 0x38c | m_fInitAxisZ | `float` |
| CCBStageScene | 0x390 | m_fCurRotParam | `float` |
| CCBStageScene | 0x394 | m_fInitRotParam | `float` |
| CCBStageScene | 0x398 | m_vecFiveLineupPos | `gbVec3D` |
| CCBStageScene | 0x3a4 | m_vecFiveLineupInitPos | `gbVec3D` |
| CCBStageScene | 0x3b0 | m_fFiveLineupRadius | `float` |
| CCBStageScene | 0x3b4 | m_fFiveLineupInitRadius | `float` |
| CCBStageScene | 0x3b8 | m_fFiveLineupRoll | `float` |
| CCBStageScene | 0x3bc | m_fFiveLineupInitRoll | `float` |
| CCBStageScene | 0x3c0 | m_vecEnemyFiveLineupPos | `gbVec3D` |
| CCBStageScene | 0x3cc | m_fEnemyFiveLineupRadius | `float` |
| CCBStageScene | 0x3d0 | m_fEnemyFiveLineupRoll | `float` |
| CCBStageScene | 0x3d4 | m_vecPointerPos | `gbVec3D` |
| CCBStageScene | 0x3e0 | m_bShowPointer | `unsigned char` |
| CCBStageScene | 0x3e1 | m_bShowAxis | `unsigned char` |
| CCBStageScene | 0x3e2 | m_bShowRoleIndex | `unsigned char` |
| CCBStageScene | 0x3e3 | m_bShowFiveLineup | `unsigned char` |
| CCBStageScene | 0x3e4 | m_bFiveLineupSelected | `unsigned char` |
| CCBStageScene | 0x3e8 | m_eSceneFiveMagicAttrib | `ECBFiveMagic` |
| CCBStageScene | 0x3ec | m_eBattleFieldAttr | `ECBBattleFieldAttr` |
| CCBStageScene | 0x3f0 | m_eBFAForce | `ECBForce` |
| CCBStageScene | 0x4 | m_pUtil | `CUtil *` |
| CCBStageScene | 0x8 | m_vecFiveLineup | `gbVec3D[7]` |
| CCBStageScene | 0x80 | m_nRender | `int` |
| CCBStageScene | 0x84 | m_fLineupCamY | `float` |
| CCBStageScene | 0x88 | m_fLineupCamZ | `float` |
| CCBStageScene | 0x8c | m_fRender | `float` |
| CCBStageScene | 0x90 | m_fLineupPrevY | `float` |
| CCBStageScene | 0x94 | m_fLineupPrevZ | `float` |
| CCBStageScene | 0x98 | m_fLineupDefaultX | `float` |
| CCBStageScene | 0x9c | m_fLineupDefaultY | `float` |
| CCBStageScene | 0xa0 | m_fLineupDefaultZ | `float` |
| CCBStageScene | 0xa4 | m_fLineupExtraX | `float` |
| CCBStageScene | 0xa8 | m_fLineupExtraY | `float` |
| CCBStageScene | 0xac | m_fLineupExtraZ | `float` |
| CCBStageScene | 0xb0 | m_vecEnemyLineup | `gbVec3D[7]` |
| CCBStageShadow | 0x0 | m_pStage | `CCBStage *` |
| CCBStageShadow | 0x10 | m_ShadowInitQuad | `gbGeomQuad[11]` |
| CCBStageShadow | 0x2fc | m_ShadowQuad | `gbGeomQuad[11]` |
| CCBStageShadow | 0x4 | m_pTexture | `gbTexture *` |
| CCBStageShadow | 0x5e8 | m_fShadowRadius | `float[11]` |
| CCBStageShadow | 0x8 | m_pEffect | `gbRenderEffect *` |
| CCBStageShadow | 0xc | m_pTextureArray | `gbTextureArray *` |
| CCBSystem | 0x0 | m_pUtil | `CCBSystem *` |
| CCBSystem | 0x10 | m_pRoleState | `CCBRoleState *` |
| CCBSystem | 0x14 | m_pStage | `CCBStage *` |
| CCBSystem | 0x16098 | m_Player | `tagPlayerSet[11]` |
| CCBSystem | 0x18 | m_pAI | `CCBAI *` |
| CCBSystem | 0x1c | m_pEditor | `CCBEditor *` |
| CCBSystem | 0x20 | m_pES | `CEffectSystem *` |
| CCBSystem | 0x24 | m_pEffectSimple | `CEffectSimple *` |
| CCBSystem | 0x28 | m_pConfig | `TxtFile *` |
| CCBSystem | 0x2c | m_pEffMgr | `CEffMgr *` |
| CCBSystem | 0x30 | m_pATSEffMgr | `CEffMgr *` |
| CCBSystem | 0x34 | m_p2DSpark | `C2DSpark *` |
| CCBSystem | 0x38 | m_p3DSpark | `C3DSpark *` |
| CCBSystem | 0x4 | m_pUI | `CCBUI *` |
| CCBSystem | 0x40 | m_DeltaTime | `double` |
| CCBSystem | 0x48 | m_dTimeFund | `double` |
| CCBSystem | 0x50 | m_fTimeFund | `float` |
| CCBSystem | 0x58 | m_AbsDeltaTime | `double` |
| CCBSystem | 0x60 | m_dAbsTimeFund | `double` |
| CCBSystem | 0x68 | m_fAbsTimeFund | `float` |
| CCBSystem | 0x6c | m_fTimeScale | `float` |
| CCBSystem | 0x70 | m_pFightInfo | `FightInfo *` |
| CCBSystem | 0x74 | m_bQuitFlag | `unsigned char` |
| CCBSystem | 0x75 | m_bPause | `unsigned char` |
| CCBSystem | 0x78 | m_eState | `ECBCombatState` |
| CCBSystem | 0x7c | m_eResult | `ECBCombatResult` |
| CCBSystem | 0x8 | m_pControl | `CCBControl *` |
| CCBSystem | 0x80 | m_bFiveNimbus | `unsigned char` |
| CCBSystem | 0x81 | m_bPXVariance | `unsigned char` |
| CCBSystem | 0x84 | m_nTimesOfCombat | `int` |
| CCBSystem | 0x88 | m_bAuto | `unsigned char` |
| CCBSystem | 0x89 | m_bEditor | `unsigned char` |
| CCBSystem | 0x8a | m_bLockCam | `unsigned char` |
| CCBSystem | 0x8b | m_bFirstRender | `unsigned char` |
| CCBSystem | 0x8c | m_dwIDHolder | `unsigned int` |
| CCBSystem | 0x90 | m_nThread | `int` |
| CCBSystem | 0x94 | m_nCurThread | `int` |
| CCBSystem | 0x98 | m_Thread | `tagThread[1024]` |
| CCBSystem | 0xc | m_pAttackSequen | `CCBAttackSequen *` |
| CCBTaskGroup | 0x0 | m_nTaskId | `int` |
| CCBTaskGroup | 0x10 | m_Slots | `CCBTaskSlot[32]` |
| CCBTaskGroup | 0x4 | m_nState | `int` |
| CCBTaskGroup | 0x8 | m_nCurSlot | `int` |
| CCBTaskGroup | 0xa10 | m_nEndFlag | `int` |
| CCBTaskGroup | 0xa14 | m_nDelResult | `int` |
| CCBTaskGroup | 0xa44 | m_bInUse | `unsigned char` |
| CCBTaskSlot | 0x0 | m_nTaskFn | `int` |
| CCBTaskSlot | 0x10 | m_nState | `int` |
| CCBTaskSlot | 0x18 | m_fStartTime | `float` |
| CCBTaskSlot | 0x1c | m_fMaxWait | `float` |
| CCBTaskSlot | 0x20 | m_fDuration | `float` |
| CCBTaskSlot | 0x24 | m_nActionId | `int` |
| CCBTaskSlot | 0x28 | m_bActive | `unsigned char` |
| CCBTaskSlot | 0x29 | m_bRegistered | `unsigned char` |
| CCBTaskSlot | 0x2b | m_bForceDone | `unsigned char` |
| CCBTaskSlot | 0x4 | m_nTaskArg0 | `int` |
| CCBTaskSlot | 0x40 | m_nTurnState | `int` |
| CCBTaskSlot | 0x8 | m_nTaskArg1 | `int` |
| CCBTaskSlot | 0xc | m_nTaskArg2 | `int` |
| CCBTaskSlot208 | 0x14 | m_nSize | `int` |
| CCBTaskSlot208 | 0x18 | m_nId | `int` |
| CCBTaskSlot208 | 0x50 | m_nCounter | `int` |
| CCBTaskSlot208 | 0x60 | m_fVal0 | `float` |
| CCBTaskSlot208 | 0x64 | m_fVal1 | `float` |
| CCBTaskSlot208 | 0x68 | m_fVal2 | `float` |
| CCBTaskSlot208 | 0x6c | m_fVal3 | `float` |
| CCBTaskSlot208 | 0x70 | m_fVal4 | `float` |
| CCBTaskSlot208 | 0x74 | m_fVal5 | `float` |
| CCBTaskSlot208 | 0x90 | m_ptrC | `void *` |
| CCBTaskSlot208 | 0xb8 | _ovl_0B8 | `_BYTE[24]` |
| CCBUI | 0x124 | m_pRoleStateDefenceInc | `UIStatic *[11]` |
| CCBUI | 0x150 | m_pRoleStateDefenceDec | `UIStatic *[11]` |
| CCBUI | 0x17c | m_pRoleStateLuckInc | `UIStatic *[11]` |
| CCBUI | 0x1a8 | m_pRoleStateLuckDec | `UIStatic *[11]` |
| CCBUI | 0x1d4 | m_pRoleStateSpeedInc | `UIStatic *[11]` |
| CCBUI | 0x200 | m_pRoleStateSpeedDec | `UIStatic *[11]` |
| CCBUI | 0x22c | m_pRoleStateStable | `UIStatic *[11]` |
| CCBUI | 0x258 | m_pRoleStateBlank | `UIStatic *[11]` |
| CCBUI | 0x284 | m_pRoleStateForbid | `UIStatic *[11]` |
| CCBUI | 0x2b0 | m_pRoleStateSleep | `UIStatic *[11]` |
| CCBUI | 0x2dc | m_pRoleStateChaos | `UIStatic *[11]` |
| CCBUI | 0x308 | m_pRoleStateMad | `UIStatic *[11]` |
| CCBUI | 0x334 | m_pRoleStateMirror | `UIStatic *[11]` |
| CCBUI | 0x360 | m_pRoleStateWall | `UIStatic *[11]` |
| CCBUI | 0x38c | m_pRoleStateBound | `UIStatic *[11]` |
| CCBUI | 0x3b8 | m_pRoleStateHermit | `UIStatic *[11]` |
| CCBUI | 0x3e4 | m_pRoleStateImmunity | `UIStatic *[11]` |
| CCBUI | 0x410 | m_pWinPanel | `UIStatic *` |
| CCBUI | 0x414 | m_pLosePanel | `UIStatic *` |
| CCBUI | 0x418 | m_pRoleStateHP | `UIProgressBar *[4]` |
| CCBUI | 0x428 | m_pRoleStateGP | `UIProgressBar *[4]` |
| CCBUI | 0x438 | m_pRoleStateMP | `UIProgressBar *[4]` |
| CCBUI | 0x448 | m_pRoleStateSword | `UIProgressBar *` |
| CCBUI | 0x44c | m_pTrickName | `UIStaticCB *` |
| CCBUI | 0x450 | m_pTrickName2 | `UIStaticCB *` |
| CCBUI | 0x454 | m_pDialogBack | `UIStatic *` |
| CCBUI | 0x458 | m_pResultLevelup | `UIStatic *` |
| CCBUI | 0x45c | m_pResultWindLvup | `UIStatic *` |
| CCBUI | 0x460 | m_pResultThunderLvup | `UIStatic *` |
| CCBUI | 0x464 | m_pResultWaterLvup | `UIStatic *` |
| CCBUI | 0x468 | m_pResultFireLvup | `UIStatic *` |
| CCBUI | 0x46c | m_pResultEarthLvup | `UIStatic *` |
| CCBUI | 0x470 | m_pResultDoubleLvup | `UIStatic *` |
| CCBUI | 0x474 | m_pResultGetItem | `UIStatic *` |
| CCBUI | 0x478 | m_pMain | `CCBControlWindow *` |
| CCBUI | 0x47c | m_pItemWindow | `CCBItemWindow *` |
| CCBUI | 0x48 | m_pBack | `UIStatic *` |
| CCBUI | 0x480 | m_pParabolaWindow | `CCBParabolaWindow *` |
| CCBUI | 0x484 | m_pMagicWindow | `CCBMagicWindow *` |
| CCBUI | 0x488 | m_pSkillWindow | `CCBSkillWindow *` |
| CCBUI | 0x48c | m_pAIWindow | `CCBAIWindow *` |
| CCBUI | 0x490 | m_pLineupWindow | `CCBLineupWindow *` |
| CCBUI | 0x494 | m_pProtectWindow | `CCBProtectWindow *` |
| CCBUI | 0x498 | m_pResultWindow | `CCBResultWindow *[4]` |
| CCBUI | 0x4a8 | m_pFiveNimbusWindow | `CCBFiveNimbusWindow *` |
| CCBUI | 0x4ac | m_pCBSystem | `CCBSystem *` |
| CCBUI | 0x4b0 | m_pUtil | `CUtil *` |
| CCBUI | 0x4c | m_pWHFace | `UIPushButton *` |
| CCBUI | 0x50 | m_pWPXFace | `UIPushButton *` |
| CCBUI | 0x54 | m_pWHLove | `UIProgressBar *` |
| CCBUI | 0x58 | m_pWPXLove | `UIProgressBar *` |
| CCBUI | 0x5c | m_pOk | `UIButton *` |
| CCBUI | 0x68 | m_pAttackSequenFace | `UIStatic *[11]` |
| CCBUI | 0x94 | m_pRoleStatePanel | `UIStatic *[4]` |
| CCBUI | 0xa4 | m_pRoleStateFace | `UIStatic *[5]` |
| CCBUI | 0xb8 | m_pRoleStateFaceName | `UIStatic *[5]` |
| CCBUI | 0xcc | m_pRoleStateAttackInc | `UIStatic *[11]` |
| CCBUI | 0xf8 | m_pRoleStateAttackDec | `UIStatic *[11]` |
| CCBUICtrl | 0x48 | _todo_48 | `UIWnd *` |
| CCBUICtrl | 0x4c | _todo_4C | `UIWnd *[10]` |
| CCBUIPanel | 0x10dc | m_bActive | `unsigned char` |
| CCBUIPanel | 0x10e4 | m_Slots | `CCBPanelSlot[30]` |
| CCBUIPanel | 0x48ac | m_nSlotBaseX | `int` |
| CCBUIPanel | 0x48b0 | m_nSlotStepX | `int` |
| CCBUIPanel | 0x48b4 | m_nSlotBaseY | `int` |
| CCBUIPanel | 0x48b8 | m_EmbedPalScript | `int` |
| CCBUIPanel | 0x495c | m_fSlotRefX | `float` |
| CCBUIPanel | 0x4960 | m_fSlotRefY | `float` |
| CCBUIPanel | 0x4964 | m_nSlotCalcA | `int` |
| CCBUIPanel | 0x4968 | m_nSlotCalcB | `int` |
| CCBUIPanel | 0x496c | m_nSlotCalcC | `int` |
| CCBUIPanel | 0x4970 | m_nSlotCalcD | `int` |
| CCBUIPanel | 0x4974 | m_fSlotCalcX2 | `float` |
| CCBUIPanel | 0x4978 | m_fSlotCalcY2 | `float` |
| CCBUIPanel | 0x4988 | m_bSlotFlags | `int` |
| CCBUIPanel | 0x498c | m_fSlotParam | `float` |
| CCBUIPanel | 0x4990 | m_bEnsureSize | `int` |
| CCBUIPanel | 0x4994 | m_nActiveSlot | `int` |
| CCBUIPanel | 0x4998 | m_EmbedPlayerAtt | `int` |
| CCBUIPanel | 0x4b60 | m_SubCaptionGroup | `void *` |
| CCBUIPanel | 0x4ef0 | m_nPlayerAttOverlay | `int` |
| CCBUIPanel | 0x5050 | m_nReserved5050 | `int` |
| CCBUIPanel | 0x5054 | m_nReserved5054 | `int` |
| CCBUIPanel | 0x540 | m_nPanelOffsetX | `int` |
| CCBUIPanel | 0x5434 | m_Data | `char[512]` |
| CCBUIPanel | 0x544 | m_nPanelOffsetY | `int` |
| CCBUIPanel | 0x5bc | m_nPanelX | `int` |
| CCBUIPanel | 0x5c0 | m_nPanelY | `int` |
| CCBUIPanel | 0x5c4 | m_nChildX | `int` |
| CCBUIPanel | 0x5c8 | m_nChildY | `int` |
| CCBUIPanel | 0x5cc | m_nChildW | `int` |
| CCBUIPanel | 0x5d0 | m_nChildH | `int` |
| CCBUIPanel | 0x5d4 | m_nBorderL | `int` |
| CCBUIPanel | 0x5d8 | m_nBorderR | `int` |
| CCBUIPanel | 0x5dc | m_fPanelW | `float` |
| CCBUIPanel | 0x5e0 | m_fPanelH | `float` |
| CCBUIPanel | 0x5e4 | m_nGridX | `int` |
| CCBUIPanel | 0x5e8 | m_nGridY | `int` |
| CCBUIPanel | 0x5ec | m_nGridW | `int` |
| CCBUIPanel | 0x5f0 | m_nGridH | `int` |
| CCBUIPanel | 0x5f4 | m_nItemW | `int` |
| CCBUIPanel | 0x5f8 | m_nItemH | `int` |
| CCBUIPanel | 0x5fc | m_nSpacingX | `int` |
| CCBUIPanel | 0x600 | m_nSpacingY | `int` |
| CCBUIPanel | 0x604 | m_nItemNum | `int` |
| CCBUIPanel | 0x608 | m_nMaxItemNum | `int` |
| CCBUIPanel | 0x618 | m_pVfTable | `char *` |
| CCBUIPanel | 0x700 | m_SubPanel1 | `void *` |
| CCBUIPanel | 0x858 | m_Static_2136 | `UIStatic` |
| CCBUIPanel | 0x8f0 | m_Static_2288 | `UIStatic` |
| CCBUIPanel | 0x988 | m_Static_2440 | `UIStatic` |
| CCBUIPanel | 0xa20 | m_Static_2592 | `UIStatic` |
| CCBUIPanel | 0xab8 | m_Static_2744 | `UIStatic` |
| CCBUIPanel | 0xb50 | m_SubPanel2 | `void *` |
| CCBUIPanel | 0xca8 | m_SubPanel3 | `void *` |
| CCBUIPanel | 0xe00 | m_SubPanel4 | `void *` |
| CCBUIPanel | 0xf58 | m_SubRoleDialog | `void *` |
| CCBUI_funcptr_t | 0x0 | fp | `char *` |
| CCBUI_funcptr_t | 0x4 | fp_data | `DWORD[3]` |
| CCCTData | 0x0 | m_Pool | `tagCCT[2000]` |
| CCCTData | 0x639c0 | m_bPoolInUse | `unsigned char[2000]` |
| CCCTData | 0x64190 | m_nCCTIndex | `int[50][100]` |
| CCentripetalPolicy | 0x0 | _tail_000 | `char[4]` |
| CD3DEnumeration | 0x0 | m_pD3D | `IDirect3D9 *` |
| CD3DEnumeration | 0x10 | AppMinFullscreenHeight | `unsigned int` |
| CD3DEnumeration | 0x14 | AppMinColorChannelBits | `unsigned int` |
| CD3DEnumeration | 0x18 | AppMinAlphaChannelBits | `unsigned int` |
| CD3DEnumeration | 0x1c | AppMinDepthBits | `unsigned int` |
| CD3DEnumeration | 0x20 | AppMinStencilBits | `unsigned int` |
| CD3DEnumeration | 0x24 | AppUsesDepthBuffer | `unsigned char` |
| CD3DEnumeration | 0x25 | AppUsesMixedVP | `unsigned char` |
| CD3DEnumeration | 0x26 | AppRequiresWindowed | `unsigned char` |
| CD3DEnumeration | 0x27 | AppRequiresFullscreen | `unsigned char` |
| CD3DEnumeration | 0x28 | m_pAllowedAdapterFormatList | `CArrayList *` |
| CD3DEnumeration | 0x4 | m_pAdapterInfoList | `CArrayList *` |
| CD3DEnumeration | 0x8 | ConfirmDeviceCallback | `char *` |
| CD3DEnumeration | 0xc | AppMinFullscreenWidth | `unsigned int` |
| CD3DSettings | 0x0 | IsWindowed | `unsigned char` |
| CD3DSettings | 0x10 | Windowed_DisplayMode | `_D3DDISPLAYMODE` |
| CD3DSettings | 0x20 | Windowed_DepthStencilBufferFormat | `_D3DFORMAT` |
| CD3DSettings | 0x24 | Windowed_MultisampleType | `_D3DMULTISAMPLE_TYPE` |
| CD3DSettings | 0x28 | Windowed_MultisampleQuality | `unsigned int` |
| CD3DSettings | 0x2c | Windowed_VertexProcessingType | `VertexProcessingType` |
| CD3DSettings | 0x30 | Windowed_PresentInterval | `unsigned int` |
| CD3DSettings | 0x34 | Windowed_Width | `int` |
| CD3DSettings | 0x38 | Windowed_Height | `int` |
| CD3DSettings | 0x3c | pFullscreen_AdapterInfo | `D3DAdapterInfo *` |
| CD3DSettings | 0x4 | pWindowed_AdapterInfo | `D3DAdapterInfo *` |
| CD3DSettings | 0x40 | pFullscreen_DeviceInfo | `D3DDeviceInfo *` |
| CD3DSettings | 0x44 | pFullscreen_DeviceCombo | `D3DDeviceCombo *` |
| CD3DSettings | 0x48 | Fullscreen_DisplayMode | `_D3DDISPLAYMODE` |
| CD3DSettings | 0x58 | Fullscreen_DepthStencilBufferFormat | `_D3DFORMAT` |
| CD3DSettings | 0x5c | Fullscreen_MultisampleType | `_D3DMULTISAMPLE_TYPE` |
| CD3DSettings | 0x60 | Fullscreen_MultisampleQuality | `unsigned int` |
| CD3DSettings | 0x64 | Fullscreen_VertexProcessingType | `VertexProcessingType` |
| CD3DSettings | 0x68 | Fullscreen_PresentInterval | `unsigned int` |
| CD3DSettings | 0x8 | pWindowed_DeviceInfo | `D3DDeviceInfo *` |
| CD3DSettings | 0xc | pWindowed_DeviceCombo | `D3DDeviceCombo *` |
| CDamplyCentripetalPolicy | 0x0 | _tail_000 | `char[4]` |
| CEffAction | 0x30 | m_nController | `int` |
| CEffAudio | 0x30 | m_szSoundNamePrefix | `char[128]` |
| CEffAudio | 0xb0 | m_szSoundName | `char[128][4]` |
| CEffBase | 0x10 | m_fPrevTime | `float` |
| CEffBase | 0x14 | m_fDeltaTime | `float` |
| CEffBase | 0x18 | m_pSegData | `char *` |
| CEffBase | 0x1c | m_fDuration | `float` |
| CEffBase | 0x20 | m_fTimeScale | `float` |
| CEffBase | 0x24 | m_nMaxTask | `int` |
| CEffBase | 0x28 | m_nSegments | `int` |
| CEffBase | 0x2c | m_nVertPerSeg | `int` |
| CEffBase | 0x4 | m_pEffectSystem | `CEffectSystem *` |
| CEffBase | 0x8 | m_eKind | `int` |
| CEffBase | 0xc | m_nTaskIndex | `int` |
| CEffBink | 0x30 | m_szBinkNamePrefix | `char[128]` |
| CEffBink | 0xb0 | m_szBinkName | `char[128]` |
| CEffCallBack | 0x30 | m_fStartX | `float` |
| CEffCallBack | 0x34 | m_fStartY | `float` |
| CEffCallBack | 0x38 | m_fStartZ | `float` |
| CEffCallBack | 0x3c | m_dwRunningID | `unsigned int` |
| CEffCustomShape | 0x30 | m_bVisible | `unsigned char` |
| CEffCustomShape | 0x34 | m_vecPos | `gbVec3D` |
| CEffCustomShape | 0x40 | m_vecOffsetPos | `gbVec3D` |
| CEffCustomShape | 0x4c | m_vecRot | `gbVec3D` |
| CEffCustomShape | 0x58 | m_fAlpha | `float` |
| CEffCustomShape | 0x5c | m_fRed | `float` |
| CEffCustomShape | 0x60 | m_fGreen | `float` |
| CEffCustomShape | 0x64 | m_fBlue | `float` |
| CEffCustomShape | 0x68 | m_fScaleX | `float` |
| CEffCustomShape | 0x6c | m_fScaleY | `float` |
| CEffCustomShape | 0x70 | m_fScaleZ | `float` |
| CEffCustomShape | 0x74 | m_pModel | `t3DModel *` |
| CEffCustomShape | 0x78 | m_pTexture | `gbTexture *` |
| CEffCustomShape | 0x7c | m_pRenderEffect | `gbRenderEffect *` |
| CEffCustomShape | 0x80 | m_pIndexBubble | `gbIndexBubble *` |
| CEffCustomShape | 0x84 | m_nCurrFrame | `int` |
| CEffCustomShape | 0x88 | m_nFrameNum | `int` |
| CEffCustomShape | 0x8c | m_fFrameU | `float` |
| CEffCustomShape | 0x90 | m_fFrameV | `float` |
| CEffCustomShape | 0x94 | m_fSpeed | `float` |
| CEffCustomShape | 0x98 | m_fTimeCount | `float` |
| CEffCustomShape | 0x9c | m_UVData | `std::vector<gbVec2D,std::allocator<gbVec2D> >` |
| CEffCylinder | 0x30 | m_pGeomQuad | `gbGeomQuad *` |
| CEffCylinder | 0x34 | m_pTexture | `gbTexture *` |
| CEffCylinder | 0x38 | m_pTextureArray | `gbTextureArray *` |
| CEffCylinder | 0x3c | m_bVisible | `unsigned char` |
| CEffCylinder | 0x3d | m_bAdditiveBlend | `unsigned char` |
| CEffCylinder | 0x3e | m_bNoZTest | `unsigned char` |
| CEffCylinder | 0x3f | m_byMaxFrame | `unsigned char` |
| CEffCylinder | 0x40 | m_nRequireLoops | `int` |
| CEffCylinder | 0x44 | m_nLoops | `int` |
| CEffCylinder | 0x48 | m_fCurFrame | `float` |
| CEffCylinder | 0x4c | m_dwStartColor | `unsigned int` |
| CEffCylinder | 0x50 | m_fAlpha | `float` |
| CEffCylinder | 0x54 | m_fRed | `float` |
| CEffCylinder | 0x58 | m_fGreen | `float` |
| CEffCylinder | 0x5c | m_fBlue | `float` |
| CEffCylinder | 0x60 | m_fSize | `float` |
| CEffCylinder | 0x64 | m_fHeight | `float` |
| CEffCylinder | 0x68 | m_fRotAngle | `float` |
| CEffCylinder | 0x6c | m_fWide | `float` |
| CEffCylinder | 0x70 | m_nDivision | `int` |
| CEffCylinder | 0x74 | m_fTopShrink | `float` |
| CEffCylinder | 0x78 | m_fBottomShrink | `float` |
| CEffCylinder | 0x7c | m_fTopRadius | `float` |
| CEffCylinder | 0x80 | m_fBottomRadius | `float` |
| CEffCylinder | 0x84 | m_fTopRadiusIncSpeed | `float` |
| CEffCylinder | 0x88 | m_fBottomRadiusIncSpeed | `float` |
| CEffCylinder | 0x8c | m_fTopRiseSpeed | `float` |
| CEffCylinder | 0x90 | m_fBottomRiseSpeed | `float` |
| CEffCylinder | 0x94 | m_fTextureRepeat | `float` |
| CEffCylinder | 0x98 | m_fFramePerSec | `float` |
| CEffCylinder | 0x9c | m_fCurTextureV | `float` |
| CEffCylinder | 0xa0 | m_vecRot | `gbVec3D` |
| CEffCylinder | 0xac | m_vecPos | `gbVec3D` |
| CEffCylinder | 0xb8 | m_vecOffsetPos | `gbVec3D` |
| CEffCylinder | 0xc4 | m_DefaultUVSet | `tagUV[256]` |
| CEffExplosive | 0x30 | m_pGeomQuad | `gbGeomQuad *` |
| CEffExplosive | 0x34 | m_pExplosive | `tagExplosive *` |
| CEffExplosive | 0x38 | m_pTexture | `gbTexture *` |
| CEffExplosive | 0x3c | m_pTextureArray | `gbTextureArray *` |
| CEffExplosive | 0x40 | m_bVisible | `unsigned char` |
| CEffExplosive | 0x41 | m_bAdditiveBlend | `unsigned char` |
| CEffExplosive | 0x42 | m_bNoZTest | `unsigned char` |
| CEffExplosive | 0x43 | m_byMaxFrame | `unsigned char` |
| CEffExplosive | 0x44 | m_nRequireLoops | `int` |
| CEffExplosive | 0x48 | m_nLoops | `int` |
| CEffExplosive | 0x4c | m_fCurFrame | `float` |
| CEffExplosive | 0x50 | m_dwStartColor | `unsigned int` |
| CEffExplosive | 0x54 | m_fAlpha | `float` |
| CEffExplosive | 0x58 | m_fRed | `float` |
| CEffExplosive | 0x5c | m_fGreen | `float` |
| CEffExplosive | 0x60 | m_fBlue | `float` |
| CEffExplosive | 0x64 | m_fXSize | `float` |
| CEffExplosive | 0x68 | m_fZSize | `float` |
| CEffExplosive | 0x6c | m_nXDivision | `int` |
| CEffExplosive | 0x70 | m_nZDivision | `int` |
| CEffExplosive | 0x74 | m_fGridSize | `float` |
| CEffExplosive | 0x78 | m_nQuad | `int` |
| CEffExplosive | 0x7c | m_fMaxExplosivePower | `float` |
| CEffExplosive | 0x80 | m_fMinExplosivePower | `float` |
| CEffExplosive | 0x84 | m_vecExplosiveDir | `gbVec3D` |
| CEffExplosive | 0x90 | m_fPowerDec | `float` |
| CEffExplosive | 0x94 | m_fFramePerSec | `float` |
| CEffExplosive | 0x98 | m_vecRot | `gbVec3D` |
| CEffExplosive | 0xa4 | m_vecPos | `gbVec3D` |
| CEffExplosive | 0xb0 | m_vecOffsetPos | `gbVec3D` |
| CEffExplosive | 0xbc | m_fResistance | `float` |
| CEffExplosive | 0xc0 | m_DefaultUVSet | `tagUV[256]` |
| CEffGrid | 0x30 | m_pGeomQuad | `gbGeomQuad *` |
| CEffGrid | 0x34 | m_pMesh | `gbVec3D *` |
| CEffGrid | 0x38 | m_pMesh2 | `gbVec3D *` |
| CEffGrid | 0x3c | m_pTexture | `gbTexture *` |
| CEffGrid | 0x40 | m_pTextureArray | `gbTextureArray *` |
| CEffGrid | 0x44 | m_bVisible | `unsigned char` |
| CEffGrid | 0x45 | m_bAdditiveBlend | `unsigned char` |
| CEffGrid | 0x46 | m_bNoZTest | `unsigned char` |
| CEffGrid | 0x47 | m_byMaxFrame | `unsigned char` |
| CEffGrid | 0x48 | m_nRequireLoops | `int` |
| CEffGrid | 0x4c | m_nLoops | `int` |
| CEffGrid | 0x50 | m_fCurFrame | `float` |
| CEffGrid | 0x54 | m_dwStartColor | `unsigned int` |
| CEffGrid | 0x58 | m_fAlpha | `float` |
| CEffGrid | 0x5c | m_fRed | `float` |
| CEffGrid | 0x60 | m_fGreen | `float` |
| CEffGrid | 0x64 | m_fBlue | `float` |
| CEffGrid | 0x68 | m_fXSize | `float` |
| CEffGrid | 0x6c | m_fZSize | `float` |
| CEffGrid | 0x70 | m_nXDivision | `int` |
| CEffGrid | 0x74 | m_nZDivision | `int` |
| CEffGrid | 0x78 | m_fGridSize | `float` |
| CEffGrid | 0x7c | m_nQuad | `int` |
| CEffGrid | 0x80 | m_fWavePower | `float` |
| CEffGrid | 0x84 | m_fWaveSpeed | `float` |
| CEffGrid | 0x88 | m_fFlapPower | `float` |
| CEffGrid | 0x8c | m_fFlapSpeed | `float` |
| CEffGrid | 0x90 | m_fFramePerSec | `float` |
| CEffGrid | 0x94 | m_vecRot | `gbVec3D` |
| CEffGrid | 0xa0 | m_vecPos | `gbVec3D` |
| CEffGrid | 0xac | m_vecOffsetPos | `gbVec3D` |
| CEffGrid | 0xb8 | m_DefaultUVSet | `tagUV[256]` |
| CEffGroupNode | 0x5c | m_nTodo_05C | `int` |
| CEffGroupNode | 0x60 | m_nTodo_060 | `int` |
| CEffGroupNode | 0x64 | m_nTodo_064 | `int` |
| CEffGroupNode | 0x68 | m_nTodo_068 | `int` |
| CEffGroupNode | 0x6c | m_nTodo_06C | `int` |
| CEffGroupNode | 0x70 | m_nTodo_070 | `int` |
| CEffMeteor | 0x30 | m_pGeomQuad | `gbGeomQuad *` |
| CEffMeteor | 0x34 | m_pChain | `CMeteorChain *` |
| CEffMeteor | 0x38 | m_pMeteor | `tagMeteor *` |
| CEffMeteor | 0x3c | m_pTexture | `gbTexture *` |
| CEffMeteor | 0x40 | m_pTextureArray | `gbTextureArray *` |
| CEffMeteor | 0x44 | m_bVisible | `unsigned char` |
| CEffMeteor | 0x45 | m_bAdditiveBlend | `unsigned char` |
| CEffMeteor | 0x46 | m_bNoZTest | `unsigned char` |
| CEffMeteor | 0x47 | m_bHaveHead | `unsigned char` |
| CEffMeteor | 0x48 | m_byMaxFrame | `unsigned char` |
| CEffMeteor | 0x4c | m_nRequireLoops | `int` |
| CEffMeteor | 0x50 | m_nLoops | `int` |
| CEffMeteor | 0x54 | m_fCurFrame | `float` |
| CEffMeteor | 0x58 | m_dwStartColor | `unsigned int` |
| CEffMeteor | 0x5c | m_fAlpha | `float` |
| CEffMeteor | 0x60 | m_fRed | `float` |
| CEffMeteor | 0x64 | m_fGreen | `float` |
| CEffMeteor | 0x68 | m_fBlue | `float` |
| CEffMeteor | 0x6c | m_fXSize | `float` |
| CEffMeteor | 0x70 | m_fZSize | `float` |
| CEffMeteor | 0x74 | m_nMaxChain | `int` |
| CEffMeteor | 0x78 | m_fMeteorWidth | `float` |
| CEffMeteor | 0x7c | m_nMaxTrail | `int` |
| CEffMeteor | 0x80 | m_fLumDecSpeed | `float` |
| CEffMeteor | 0x84 | m_fWidthDecSpeed | `float` |
| CEffMeteor | 0x88 | m_fMaxLum | `float` |
| CEffMeteor | 0x8c | m_fUpdateTimeFund | `float` |
| CEffMeteor | 0x90 | m_fFramePerSec | `float` |
| CEffMeteor | 0x94 | m_vecRot | `gbVec3D` |
| CEffMeteor | 0xa0 | m_vecPos | `gbVec3D` |
| CEffMeteor | 0xac | m_vecOffsetPos | `gbVec3D` |
| CEffMeteor | 0xb8 | m_vecTarget | `gbVec3D` |
| CEffMeteor | 0xc4 | m_vecStartSpeed | `gbVec3D` |
| CEffMeteor | 0xd0 | m_DefaultUVSet | `tagUV[256]` |
| CEffMgr | 0x0 | _tail_000 | `char[43312]` |
| CEffModel | 0x30 | m_pGeomNode | `gbGeomNode *` |
| CEffModel | 0x40 | m_vecOffsetPos | `gbVec3D` |
| CEffModel | 0x4c | m_vecRot | `gbVec3D` |
| CEffModel | 0x58 | m_bVisible | `unsigned char` |
| CEffModel | 0x59 | m_bAdditiveBlend | `unsigned char` |
| CEffModel | 0x5a | m_bNoZTest | `unsigned char` |
| CEffModel | 0x5c | m_fSizeX | `float` |
| CEffModel | 0x60 | m_fSizeY | `float` |
| CEffModel | 0x64 | m_fSizeZ | `float` |
| CEffObj | 0x4 | m_pEM | `CEffMgr *` |
| CEffObj | 0x8 | m_bIdle | `_BYTE` |
| CEffQuad | 0x10a8 | m_pTexture | `gbTexture *` |
| CEffQuad | 0x10ac | m_pTextureArray | `gbTextureArray *` |
| CEffQuad | 0x30 | m_bActive | `unsigned char` |
| CEffQuad | 0x31 | m_bVisible | `unsigned char` |
| CEffQuad | 0x32 | m_bAniFrame | `unsigned char` |
| CEffQuad | 0x33 | m_bBillBoard | `unsigned char` |
| CEffQuad | 0x34 | m_bAdditiveBlend | `unsigned char` |
| CEffQuad | 0x35 | m_bNoZTest | `unsigned char` |
| CEffQuad | 0x36 | m_byMaxFrame | `unsigned char` |
| CEffQuad | 0x38 | m_nRequireLoops | `int` |
| CEffQuad | 0x3c | m_nQuadNum | `int` |
| CEffQuad | 0x40 | m_nGeomQuadNum | `int` |
| CEffQuad | 0x44 | m_nMaxQuad | `int` |
| CEffQuad | 0x48 | m_nLastCreatedQuad | `int` |
| CEffQuad | 0x4c | m_StartQuad | `tagQuad` |
| CEffQuad | 0x9c | m_pQuad | `tagQuad *` |
| CEffQuad | 0xa0 | m_pGeomQuad | `gbGeomQuad *` |
| CEffQuad | 0xa4 | m_pnG2Q | `int *` |
| CEffQuad | 0xa8 | m_DefaultUVSet | `tagUV[256]` |
| CEffSParticle | 0x30 | m_pEffect | `CParticleEffect *` |
| CEffSParticle | 0x34 | m_vecPos | `gbVec3D` |
| CEffSParticle | 0x40 | m_fX | `float` |
| CEffSParticle | 0x44 | m_fY | `float` |
| CEffSParticle | 0x48 | m_fZ | `float` |
| CEffSParticle | 0x4c | m_fPX | `float` |
| CEffSParticle | 0x50 | m_fPY | `float` |
| CEffSParticle | 0x54 | m_fPZ | `float` |
| CEffSParticle | 0x58 | m_fRotX | `float` |
| CEffSParticle | 0x5c | m_fRotY | `float` |
| CEffSParticle | 0x60 | m_fRotZ | `float` |
| CEffShock | 0x1030 | m_pTexture | `gbTexture *` |
| CEffShock | 0x1034 | m_pTextureArray | `gbTextureArray *` |
| CEffShock | 0x1038 | m_nMaxGeomQuad | `int` |
| CEffShock | 0x103c | m_pGeomQuad | `gbGeomQuad *` |
| CEffShock | 0x1040 | m_pShock | `tagShockUnit *` |
| CEffShock | 0x1044 | m_bVisible | `unsigned char` |
| CEffShock | 0x1045 | m_bAdditiveBlend | `unsigned char` |
| CEffShock | 0x1046 | m_bNoZTest | `unsigned char` |
| CEffShock | 0x1048 | m_fFramePerSec | `float` |
| CEffShock | 0x104c | m_byMaxFrame | `unsigned char` |
| CEffShock | 0x1050 | m_nRequireLoops | `int` |
| CEffShock | 0x1054 | m_nLoops | `int` |
| CEffShock | 0x1058 | m_fCurFrame | `float` |
| CEffShock | 0x105c | m_dwStartColor | `unsigned int` |
| CEffShock | 0x1060 | m_fAlpha | `float` |
| CEffShock | 0x1064 | m_fRed | `float` |
| CEffShock | 0x1068 | m_fGreen | `float` |
| CEffShock | 0x106c | m_fBlue | `float` |
| CEffShock | 0x1070 | m_fSize | `float` |
| CEffShock | 0x1074 | m_vecRot | `gbVec3D` |
| CEffShock | 0x1080 | m_vecPos | `gbVec3D` |
| CEffShock | 0x108c | m_vecOffsetPos | `gbVec3D` |
| CEffShock | 0x1098 | m_nNodeOfShock | `int` |
| CEffShock | 0x109c | m_nCascade | `int` |
| CEffShock | 0x10a0 | m_fWidthOfNode | `float` |
| CEffShock | 0x10a4 | m_fHeightOfNode | `float` |
| CEffShock | 0x10a8 | m_fSpeedOfDisappear | `float` |
| CEffShock | 0x10ac | m_fInterleaving | `float` |
| CEffShock | 0x30 | m_DefaultUVSet | `tagUV[256]` |
| CEffTrackCustomShape | 0xac | m_pTrack | `t3DModel *` |
| CEffTrackCustomShape | 0xb0 | m_fTrackSpeed | `float` |
| CEffTrackCustomShape | 0xb4 | m_fTrackDecPart | `float` |
| CEffTrackCustomShape | 0xb8 | m_nCurrTrackPos | `int` |
| CEffTrackCustomShape | 0xbc | m_fx | `float` |
| CEffTrackCustomShape | 0xc0 | m_fy | `float` |
| CEffTrackCustomShape | 0xc4 | m_fz | `float` |
| CEffTrackCylinder | 0x10c4 | m_pTrack | `t3DModel *` |
| CEffTrackCylinder | 0x10c8 | m_fTrackSpeed | `float` |
| CEffTrackCylinder | 0x10cc | m_fTrackDecPart | `float` |
| CEffTrackCylinder | 0x10d0 | m_nCurrTrackPos | `int` |
| CEffTrackCylinder | 0x10d4 | m_fx | `float` |
| CEffTrackCylinder | 0x10d8 | m_fy | `float` |
| CEffTrackCylinder | 0x10dc | m_fz | `float` |
| CEffTrackGrid | 0x10b8 | m_pTrack | `t3DModel *` |
| CEffTrackGrid | 0x10bc | m_fTrackSpeed | `float` |
| CEffTrackGrid | 0x10c0 | m_fTrackDecPart | `float` |
| CEffTrackGrid | 0x10c4 | m_nCurrTrackPos | `int` |
| CEffTrackGrid | 0x10c8 | m_fx | `float` |
| CEffTrackGrid | 0x10cc | m_fy | `float` |
| CEffTrackGrid | 0x10d0 | m_fz | `float` |
| CEffTrackModel | 0x68 | m_pTrack | `t3DModel *` |
| CEffTrackModel | 0x6c | m_fTrackSpeed | `float` |
| CEffTrackModel | 0x70 | m_fTrackDecPart | `float` |
| CEffTrackModel | 0x74 | m_nCurrTrackPos | `int` |
| CEffTrackModel | 0x78 | m_fx | `float` |
| CEffTrackModel | 0x7c | m_fy | `float` |
| CEffTrackModel | 0x80 | m_fz | `float` |
| CEffTrackQuad | 0x10b0 | m_pTrack | `t3DModel *` |
| CEffTrackQuad | 0x10b4 | m_fTrackSpeed | `float` |
| CEffTrackQuad | 0x10b8 | m_fTrackDecPart | `float` |
| CEffTrackQuad | 0x10bc | m_nCurrTrackPos | `int` |
| CEffTrackQuad | 0x10c0 | m_fx | `float` |
| CEffTrackQuad | 0x10c4 | m_fy | `float` |
| CEffTrackQuad | 0x10c8 | m_fz | `float` |
| CEffTrackSParticle | 0x64 | m_pTrack | `t3DModel *` |
| CEffTrackSParticle | 0x68 | m_fTrackSpeed | `float` |
| CEffTrackSParticle | 0x6c | m_fTrackDecPart | `float` |
| CEffTrackSParticle | 0x70 | m_nCurrTrackPos | `int` |
| CEffect | 0x0 | m_pDispatchTable | `void *` |
| CEffect | 0x10 | m_DeltaTime | `double` |
| CEffect | 0x18 | m_nPartical | `int` |
| CEffect | 0x1801c | m_nQuad | `int` |
| CEffect | 0x18020 | m_QuadBuffer | `gbGeomQuad[2048]` |
| CEffect | 0x1c | m_Partical | `tagPartical[2048]` |
| CEffect | 0x3a020 | m_nQ2PIndex | `int[2048]` |
| CEffect | 0x3c020 | m_pTexture | `gbTexture *` |
| CEffect | 0x3c024 | m_pTextureArray | `gbTextureArray *` |
| CEffect | 0x4 | _field_004 | `int` |
| CEffect | 0x8 | m_eKind | `EEffect` |
| CEffect | 0xc | m_bActive | `unsigned char` |
| CEffect | 0xd | m_bVisible | `unsigned char` |
| CEffectBubble | 0x0 | _tail_000 | `char[4]` |
| CEffectSimple | 0x0 | _tail_000 | `char[4]` |
| CEffectSystem | 0x10 | m_pAlphaBlend | `gbRenderEffect *` |
| CEffectSystem | 0x114 | m_bInitialized | `unsigned char` |
| CEffectSystem | 0x118 | m_nEffect | `int` |
| CEffectSystem | 0x11c | m_pEffect | `CEffect *[8]` |
| CEffectSystem | 0x13c | m_dDeltaTime | `double` |
| CEffectSystem | 0x14 | m_DefaultUVSet | `tagUVSet[16]` |
| CEffectSystem | 0x144 | m_dTimeFund | `double` |
| CEffectSystem | 0x14c | m_fTimeFund | `float` |
| CEffectSystem | 0x150 | m_fTimeScale | `int` |
| CEffectSystem | 0x154 | m_fWindDirection | `int` |
| CEffectSystem | 0x158 | m_fWindSpeed | `int` |
| CEffectSystem | 0x4 | m_pDisplay | `gbGfxManager *` |
| CEffectSystem | 0x8 | m_pVertexBuffer | `gbDynVertBuf *` |
| CEffectSystem | 0xc | m_pAdditiveBlend | `gbRenderEffect *` |
| CEffgbParticle | 0x30 | m_pEffect | `ParticleEffect *` |
| CEffgbParticle | 0x34 | m_fSize | `float` |
| CEffgbParticle | 0x38 | m_fX | `float` |
| CEffgbParticle | 0x3c | m_fY | `float` |
| CEffgbParticle | 0x40 | m_fZ | `float` |
| CEffgbParticle | 0x44 | m_fPX | `float` |
| CEffgbParticle | 0x48 | m_fPY | `float` |
| CEffgbParticle | 0x4c | m_fPZ | `float` |
| CEmitter | 0x0 | _attr | `CParticleSystem::EmitterAttribute` |
| CEmitter | 0xdc | _nCurrTrackPos | `int` |
| CEmitter | 0xe0 | _fTrackDecPart | `float` |
| CFadeColorPolicy | 0x18 | _vEndColor | `gbVec3D` |
| CFadeColorPolicy | 0xc | _vBeginColor | `gbVec3D` |
| CFadeInAlphaPolicy | 0x0 | _tail_000 | `char[4]` |
| CFadeOutAlphaPolicy | 0x0 | _tail_000 | `char[4]` |
| CG_Edit | 0x0 | m_pFather | `CG_Entry *` |
| CG_Edit | 0x18 | m_fYaw | `float` |
| CG_Edit | 0x1c | m_fPitch | `float` |
| CG_Edit | 0x20 | m_fDist | `float` |
| CG_Edit | 0x24 | m_fCamX | `float` |
| CG_Edit | 0x28 | m_fCamY | `float` |
| CG_Edit | 0x2c | m_fCamZ | `float` |
| CG_Edit | 0x30 | m_vCamForward | `gbVec3D` |
| CG_Edit | 0x3c | EFT_LINE | `gbRenderEffect *` |
| CG_Edit | 0x4 | m_MousePt | `tagPOINT` |
| CG_Edit | 0x40 | EFT_GEOM_NOTEX | `gbRenderEffect *` |
| CG_Edit | 0x44 | EFT_GEOM_NOTEX_LINE | `gbRenderEffect *` |
| CG_Edit | 0x48 | m_bWaitForEditArea | `BYTE` |
| CG_Edit | 0x4c | m_rTouchArea | `tagRECT` |
| CG_Edit | 0x5c | m_rLastObjArea | `tagRECT` |
| CG_Edit | 0x6c | m_pLastGroundPt | `tagPOINT` |
| CG_Edit | 0x74 | m_nNoteMoney | `int` |
| CG_Edit | 0xc | m_Param | `_FLOORPARAM` |
| CG_Entry | 0x0 | bOpt | `BYTE` |
| CG_Entry | 0x1 | m_bUIActive | `BYTE` |
| CG_Entry | 0x10 | m_LEVELPARAM | `LEVELPARAM[5]` |
| CG_Entry | 0x38 | m_EntryFrame | `PAL3_FRAME` |
| CG_Entry | 0x3c | m_EntryRolePos | `gbVec3D` |
| CG_Entry | 0x4 | m_pScene | `CG_Scene *` |
| CG_Entry | 0x48 | m_EntryCityName | `char[64]` |
| CG_Entry | 0x8 | m_pUI | `CG_UI *` |
| CG_Entry | 0x88 | m_EntryName | `char[64]` |
| CG_Entry | 0xc | m_pEdit | `CG_Edit *` |
| CG_Entry | 0xc8 | b_NoteJumpFree | `BYTE` |
| CG_Scene | 0x0 | m_pBarrier | `BARRIER *` |
| CG_Scene | 0x10 | m_pScene | `Scene *` |
| CG_Scene | 0x14 | m_CameraCtrl | `RoleCameraCtrl` |
| CG_Scene | 0x4 | m_nBarrier | `int` |
| CG_Scene | 0x60 | m_pNPC | `Role *` |
| CG_Scene | 0x64 | m_pRelive | `RELIVEPARAM *` |
| CG_Scene | 0x68 | m_OBJ | `SceneObj[256]` |
| CG_Scene | 0x6f868 | m_ObjHelper | `OBJHELPER[256]` |
| CG_Scene | 0x72868 | m_OBJPARAM | `ObjParam[9]` |
| CG_Scene | 0x7384c | m_GHOSTPARAM | `GhostParam[4]` |
| CG_Scene | 0x7390c | m_pBOSS | `Role *` |
| CG_Scene | 0x73910 | m_BossHurt | `BOSSHURT` |
| CG_Scene | 0x73924 | m_NGHHurt | `NGHHURT` |
| CG_Scene | 0x73938 | m_bEdit | `BYTE` |
| CG_Scene | 0x7393c | m_nLevel | `int` |
| CG_Scene | 0x73940 | m_nNPC | `int` |
| CG_Scene | 0x73944 | m_nOBJ | `int` |
| CG_Scene | 0x73948 | m_nSpecialOBJ | `int` |
| CG_Scene | 0x7394c | m_fEffTime | `float` |
| CG_Scene | 0x73950 | m_bGameOver | `BYTE` |
| CG_Scene | 0x73954 | m_ObjFile | `TxtFile` |
| CG_Scene | 0x73b60 | EFT_LINE | `gbRenderEffect *` |
| CG_Scene | 0x73b64 | EFT_GEOM | `gbRenderEffect *` |
| CG_Scene | 0x73b68 | EFT_GEOM_NOTEX | `gbRenderEffect *` |
| CG_Scene | 0x73b6c | EFT_GEOM_NOTEX_LINE | `gbRenderEffect *` |
| CG_Scene | 0x73b70 | m_pObjFlagTex | `gbTexture *` |
| CG_Scene | 0x73b74 | m_SpecialObjPos | `gbVec3D[16]` |
| CG_Scene | 0x73c34 | m_DoFlingAct | `BYTE` |
| CG_Scene | 0x73c38 | m_propinfo | `CG_PROPINFO` |
| CG_Scene | 0x73c3c | m_propid | `DWORD` |
| CG_Scene | 0x73c40 | m_tmpPos | `gbVec3D` |
| CG_Scene | 0x73c4c | m_PropArray | `char[12]` |
| CG_Scene | 0x8 | m_bShowHelper | `BYTE` |
| CG_Scene | 0xc | m_pFather | `CG_Entry *` |
| CG_Scene_ArrayErase | 0x0 | _tail_000 | `char[4]` |
| CG_UI | 0x11e4 | m_pName | `UIStatic` |
| CG_UI | 0x1284 | m_pPrice | `UIStatic` |
| CG_UI | 0x1324 | m_pHurt | `UIStatic` |
| CG_UI | 0x13c4 | m_pInfo | `UIStatic` |
| CG_UI | 0x1464 | m_pBuy | `UIButton` |
| CG_UI | 0x148 | m_ParentRc | `tagRECT` |
| CG_UI | 0x158 | m_pFather | `CG_Entry *` |
| CG_UI | 0x15bc | m_pRun | `UIButton` |
| CG_UI | 0x15c | m_SelType | `int` |
| CG_UI | 0x160 | m_SelPropType | `int` |
| CG_UI | 0x164 | m_nResultValue | `int` |
| CG_UI | 0x168 | m_nWinState | `int` |
| CG_UI | 0x16c | m_OutFrameT | `UIStatic` |
| CG_UI | 0x1714 | m_pProp | `UIStatic` |
| CG_UI | 0x17b4 | m_pProps | `UIButton[5]` |
| CG_UI | 0x1e6c | m_pPropsNum | `UIStatic[5]` |
| CG_UI | 0x20c | m_OutFrameR | `UIStatic` |
| CG_UI | 0x218c | m_pHP | `UIStatic *` |
| CG_UI | 0x222c | m_pBossHP | `UIProgressBar` |
| CG_UI | 0x2320 | m_pRoleHP | `UIProgressBar` |
| CG_UI | 0x2414 | m_pRoleFace | `UIStatic` |
| CG_UI | 0x24b4 | m_pBossFace | `UIStatic` |
| CG_UI | 0x2554 | m_pTimeBackground | `UIStatic` |
| CG_UI | 0x25f4 | m_pTimeHunDigit | `UIStaticRM` |
| CG_UI | 0x26b0 | m_pTimeTenDigit | `UIStaticRM` |
| CG_UI | 0x276c | m_pTimeSinDigit | `UIStaticRM` |
| CG_UI | 0x2828 | m_pResult | `UIStatic` |
| CG_UI | 0x28c8 | m_pWinAnswer | `MUIDialog` |
| CG_UI | 0x2ac | m_OutFrameL | `UIStatic` |
| CG_UI | 0x2e30 | m_pLoseAnswer | `MUIDialog` |
| CG_UI | 0x3398 | m_pNoMoneyMsg | `MUIDialog` |
| CG_UI | 0x34c | m_OutFrameB | `UIStatic` |
| CG_UI | 0x3900 | m_pSurpassMsg | `MUIDialog` |
| CG_UI | 0x3e68 | m_pAccountMsg | `MUIDialog` |
| CG_UI | 0x3ec | m_pTime | `UIStatic` |
| CG_UI | 0x43d0 | m_pOverGameMsg | `MUIDialog` |
| CG_UI | 0x48 | buf | `char[256]` |
| CG_UI | 0x48c | m_pMoney | `UIStatic` |
| CG_UI | 0x4938 | m_pExitDlg | `MUIDialog` |
| CG_UI | 0x4ea0 | m_ComboBuffer | `PtrArray` |
| CG_UI | 0x4eb0 | m_SceneMap | `UISceneMap` |
| CG_UI | 0x52c | m_pTools | `UIStatic` |
| CG_UI | 0x5368 | m_Exit | `UIButton` |
| CG_UI | 0x54c0 | m_IsExit | `unsigned char` |
| CG_UI | 0x54c4 | m_InvalidRc0 | `tagRECT` |
| CG_UI | 0x54d4 | m_InvalidRc1 | `tagRECT` |
| CG_UI | 0x54e4 | m_InvalidRc2 | `tagRECT` |
| CG_UI | 0x54f4 | m_nTimeSec | `int` |
| CG_UI | 0x54f8 | m_nBossHP | `int` |
| CG_UI | 0x54fc | m_fBossHP | `float` |
| CG_UI | 0x5500 | m_nRoleFullHP | `int` |
| CG_UI | 0x5504 | m_nRoleCurHP | `int` |
| CG_UI | 0x5508 | m_ComboHitLastTime | `float` |
| CG_UI | 0x550c | m_ComboHitTime | `float` |
| CG_UI | 0x5510 | m_nComboHit | `int` |
| CG_UI | 0x5514 | m_nTotalComboHit | `int` |
| CG_UI | 0x5518 | m_pCombo | `UIStatic` |
| CG_UI | 0x55b8 | m_mouseon | `unsigned char[9]` |
| CG_UI | 0x55c4 | m_nPropCost | `int` |
| CG_UI | 0x55c8 | m_nNoteMoney | `int` |
| CG_UI | 0x55cc | m_pBuyUI | `PropUI *` |
| CG_UI | 0x55d0 | m_bRenderBuyUI | `unsigned char` |
| CG_UI | 0x5cc | m_pItems | `UIButton[9]` |
| CIniFile | 0x0 | m_fp | `gbVFile *` |
| CIniFile | 0x4 | m_bRead | `int` |
| CJ_FindFile | 0x0 | m_strRoot | `char[324]` |
| CJ_FindFile | 0x144 | m_pNextInfo | `char *` |
| CJ_FindFile | 0x148 | m_hContext | `char *` |
| CJ_FindFile | 0x14c | m_pFoundInfo | `char *` |
| CJ_FindFile | 0x150 | m_fileName | `char[324]` |
| CJ_FindFile | 0x294 | m_strbuf | `char[324]` |
| CJ_FindFile | 0x3d8 | m_bClosed | `BYTE` |
| CLoad3DS | 0x0 | m_FilePointer | `gbVFile *` |
| CLoad3DS | 0x18 | m_nTodo_018 | `int` |
| CLoad3DS | 0x1c | m_nTodo_01C | `int` |
| CLoad3DS | 0x20 | m_nTodo_020 | `int` |
| CLoad3DS | 0x4 | m_pBuffer | `char[20]` |
| CMeteorChain | 0x0 | m_pEM | `CEffMgr *` |
| CMeteorChain | 0x10 | m_nNumOfNode | `int` |
| CMeteorChain | 0x14 | m_pFirstNode | `tagMeteorNode *` |
| CMeteorChain | 0x18 | m_pLastNode | `tagMeteorNode *` |
| CMeteorChain | 0x1c | m_fCurTime | `float` |
| CMeteorChain | 0x20 | m_fLastTime | `float` |
| CMeteorChain | 0x24 | m_dwColor | `unsigned int` |
| CMeteorChain | 0x28 | m_fMaxLum | `float` |
| CMeteorChain | 0x2c | m_fLumDecSpeed | `float` |
| CMeteorChain | 0x30 | m_fMaxWidth | `float` |
| CMeteorChain | 0x34 | m_fWidthDecSpeed | `float` |
| CMeteorChain | 0x4 | m_pGeomQuad | `gbGeomQuad *` |
| CMeteorChain | 0x8 | m_bHaveTexture | `unsigned char` |
| CMeteorChain | 0xc | m_pTextureArray | `gbTextureArray *` |
| COLLIDE_DATA | 0x0 | v1 | `gbVec3D` |
| COLLIDE_DATA | 0x18 | v3 | `gbVec3D` |
| COLLIDE_DATA | 0x24 | fn | `gbVec3D` |
| COLLIDE_DATA | 0xc | v2 | `gbVec3D` |
| CONTEXT | 0x0 | ContextFlags | `UINT` |
| CONTEXT | 0x10 | Dr3 | `UINT` |
| CONTEXT | 0x14 | Dr6 | `UINT` |
| CONTEXT | 0x18 | Dr7 | `UINT` |
| CONTEXT | 0x4 | Dr0 | `UINT` |
| CONTEXT | 0x8 | Dr1 | `UINT` |
| CONTEXT | 0x8c | SegGs | `UINT` |
| CONTEXT | 0x90 | SegFs | `UINT` |
| CONTEXT | 0x94 | SegEs | `UINT` |
| CONTEXT | 0x98 | SegDs | `UINT` |
| CONTEXT | 0x9c | Edi | `UINT` |
| CONTEXT | 0xa0 | Esi | `UINT` |
| CONTEXT | 0xa4 | Ebx | `UINT` |
| CONTEXT | 0xa8 | Edx | `UINT` |
| CONTEXT | 0xac | Ecx | `UINT` |
| CONTEXT | 0xb0 | Eax | `UINT` |
| CONTEXT | 0xb4 | Ebp | `UINT` |
| CONTEXT | 0xb8 | Eip | `UINT` |
| CONTEXT | 0xbc | SegCs | `UINT` |
| CONTEXT | 0xc | Dr2 | `UINT` |
| CONTEXT | 0xc0 | EFlags | `UINT` |
| CONTEXT | 0xc4 | Esp | `UINT` |
| CONTEXT | 0xc8 | SegSs | `UINT` |
| COnceFramePolicy | 0xc | _fSpeed | `float` |
| CPK | 0x0 | m_dwAllocGranularity | `unsigned int` |
| CPK | 0x4 | m_eMode | `ECPKMode` |
| CPK | 0x8 | m_CPKHeader | `tagCPKHeader` |
| CPK | 0x88 | m_CPKTable | `tagCPKTable[32768]` |
| CPK | 0xe0088 | m_pCPKFile | `gbVFile *[8]` |
| CPK | 0xe00a8 | m_bLoaded | `unsigned char` |
| CPK | 0xe00ac | m_dwCPKHandle | `unsigned int` |
| CPK | 0xe00b0 | m_dwCPKMappingHandle | `unsigned int` |
| CPK | 0xe00b4 | m_szCPKFileName | `char[260]` |
| CPK | 0xe01b8 | m_nOpenedFileNum | `int` |
| CPKFile | 0x0 | bValid | `unsigned char` |
| CPKFile | 0x10 | lpMapAddress | `char *` |
| CPKFile | 0x14 | lpStartAddress | `char *` |
| CPKFile | 0x18 | dwOffset | `unsigned int` |
| CPKFile | 0x1c | bCompressed | `unsigned char` |
| CPKFile | 0x20 | lpRealData | `char *` |
| CPKFile | 0x24 | dwFileSize | `unsigned int` |
| CPKFile | 0x28 | dwPointer | `unsigned int` |
| CPKFile | 0x2c | pTableItem | `tagCPKTable *` |
| CPKFile | 0x4 | dwCRC | `unsigned int` |
| CPKFile | 0x8 | dwFatherCRC | `unsigned int` |
| CPKFile | 0xc | nTableIndex | `int` |
| CPPEH_RECORD | 0x0 | old_esp | `DWORD` |
| CPPEH_RECORD | 0x4 | exc_ptr | `EXCEPTION_POINTERS *` |
| CPPEH_RECORD | 0x8 | registration | `struct _EH3_EXCEPTION_REGISTRATION` |
| CParticleEffect | 0x0 | _bPlay | `int` |
| CParticleEffect | 0x10 | _ParticleSystems | `char[16]` |
| CParticleEffect | 0x20 | _pRenderEffect | `gbRenderEffect *` |
| CParticleEffect | 0x24 | _pGfxMgr | `gbGfxManager *` |
| CParticleEffect | 0x28 | _dwReserved | `unsigned int[4]` |
| CParticleEffect | 0x4 | _fTimeScale | `float` |
| CParticleEffect | 0x8 | _tBlendType | `int` |
| CParticleEffect | 0xc | _fTime | `float` |
| CParticleSystem | 0x0 | _bVisible | `int` |
| CParticleSystem | 0x10 | _strParticleName | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` |
| CParticleSystem | 0x20 | _dwParticleId | `unsigned int` |
| CParticleSystem | 0x24 | _pPositionPolicy | `CPolicy *` |
| CParticleSystem | 0x28 | _pDirectionPolicy | `CPolicy *` |
| CParticleSystem | 0x2c | _pColorPolicy | `CPolicy *` |
| CParticleSystem | 0x30 | _pAlphaPolicy | `CPolicy *` |
| CParticleSystem | 0x34 | _pFramePolicy | `CPolicy *` |
| CParticleSystem | 0x38 | _pEmitterPolicy | `CPolicy *` |
| CParticleSystem | 0x3c | _pParticles | `CParticleSystem_ParticleUnit *` |
| CParticleSystem | 0x4 | _bPlay | `int` |
| CParticleSystem | 0x40 | _pEmitter | `CEmitter *` |
| CParticleSystem | 0x44 | _KeyFrames | `char[16]` |
| CParticleSystem | 0x54 | _nNumOfParticles | `int` |
| CParticleSystem | 0x58 | _nMaxNum | `int` |
| CParticleSystem | 0x5c | _dwNumOfKeyFrames | `unsigned int` |
| CParticleSystem | 0x60 | _dwNumOfUnitFrames | `unsigned int` |
| CParticleSystem | 0x64 | _nCurrFrame | `int` |
| CParticleSystem | 0x68 | _nLastFrame | `int` |
| CParticleSystem | 0x6c | _fTimeCounter | `float` |
| CParticleSystem | 0x70 | _fEmitDecPart | `float` |
| CParticleSystem | 0x74 | _dwVBFlush | `unsigned int` |
| CParticleSystem | 0x78 | _matTransform | `gbMatrix4` |
| CParticleSystem | 0x8 | _bCycle | `int` |
| CParticleSystem | 0xb8 | _fWidthScale | `float` |
| CParticleSystem | 0xbc | _fHeightScale | `float` |
| CParticleSystem | 0xc | _bManual | `int` |
| CParticleSystem | 0xc0 | _TexCoordData | `std::vector<CParticleSystem::TexCoordQuad,std::allocator<CParticleSystem::TexCoordQuad> >` |
| CParticleSystem | 0xd0 | _pTexture | `gbTexture *` |
| CParticleSystem | 0xd4 | _pRenderEffect | `gbRenderEffect *` |
| CParticleSystem | 0xd8 | _pGfxMgr | `gbGfxManager *` |
| CParticleSystem_ParticleAttribute | 0x0 | _tail_000 | `char[4]` |
| CParticleSystem_ParticleUnit | 0x0 | _tail_000 | `char[4]` |
| CPolicy | 0x4 | _pParticleSystem | `CParticleSystem *` |
| CPolicy | 0x8 | _dwPolicyId | `unsigned int` |
| CRandomColorPolicy | 0x0 | _tail_000 | `char[4]` |
| CReBackFramePolicy | 0xc | _fSpeed | `float` |
| CRenderTarget | 0x0 | _tail_000 | `char[4]` |
| CRenderTarget2 | 0x0 | _tail_000 | `char[4]` |
| CResistanceMotionPolicy | 0x18 | _fConstant | `float` |
| CResistanceMotionPolicy | 0xc | _vAcceleration | `gbVec3D` |
| CRotateEmitterPolicy | 0x18 | _fSpeed | `float` |
| CRotateEmitterPolicy | 0x1c | _fAngle | `float` |
| CRotateEmitterPolicy | 0xc | _vAxis | `gbVec3D` |
| CSEHException | 0x0 | m_dwOpts | `DWORD` |
| CSEHException | 0x4 | m_szExceptionString | `char[260]` |
| CScreenMode | 0x100 | m_fBarOffsetW | `float` |
| CScreenMode | 0x104 | m_fAccum | `float` |
| CScreenMode | 0x108 | m_nProgressTimer | `int` |
| CScreenMode | 0x10c | m_nBarParam | `int` |
| CScreenMode | 0x110 | m_nArrayCapacity | `int` |
| CScreenMode | 0x114 | m_pArrayData | `char *` |
| CScreenMode | 0x118 | m_FrameB | `UIStatic` |
| CScreenMode | 0x1b0 | m_StaticArray | `UIStatic` |
| CScreenMode | 0x268 | m_nVolNode0 | `int` |
| CScreenMode | 0x26c | m_nVolNode1 | `int` |
| CScreenMode | 0x270 | m_nVolNode2 | `int` |
| CScreenMode | 0x274 | m_nVolNode3 | `int` |
| CScreenMode | 0x278 | m_nVolNode4 | `int` |
| CScreenMode | 0x328 | m_pAudioMgr | `gbAudioManager *` |
| CScreenMode | 0x32c | m_pSoundStream | `void *` |
| CScreenMode | 0x330 | m_Static_816 | `UIStatic` |
| CScreenMode | 0x48 | m_nPosY | `int` |
| CScreenMode | 0x4c | m_nLayoutParam | `int` |
| CScreenMode | 0x4dc | m_nPageCounter | `UIScene` |
| CScreenMode | 0x50 | m_nUIState | `int` |
| CScreenMode | 0x54 | m_nUIMode | `int` |
| CScreenMode | 0x58 | m_nScreenWidth | `int` |
| CScreenMode | 0x5c | m_nScreenHeight | `int` |
| CScreenMode | 0x60 | m_nProgressBase | `int` |
| CScreenMode | 0x64 | m_nLayoutState | `int` |
| CScreenMode | 0x68 | m_nLayoutOffX | `int` |
| CScreenMode | 0x6c | m_nLayoutOffY | `int` |
| CScreenMode | 0x71 | m_bLoadFlag | `unsigned char` |
| CScreenMode | 0x78 | m_nProgressValA | `int` |
| CScreenMode | 0x7c | m_nProgressValB | `int` |
| CScreenMode | 0x80 | m_nProgressPos | `int` |
| CScreenMode | 0x84 | m_nProgress | `int` |
| CScreenMode | 0x88 | m_nBarWidth | `int` |
| CScreenMode | 0x8c | m_nBarHeight | `int` |
| CScreenMode | 0x8d4 | m_BtnTooltipC | `UIButton` |
| CScreenMode | 0x90 | m_nBarPosX | `int` |
| CScreenMode | 0x94 | m_nBarPosY | `int` |
| CScreenMode | 0x98 | m_bCameraInit | `int` |
| CScreenMode | 0xa0 | m_fVolume | `float` |
| CScreenMode | 0xa3c | m_ScenePanel | `UIScene` |
| CScreenMode | 0xa4 | m_wndAssistA | `float` |
| CScreenMode | 0xa8 | m_nAudioHandle | `int` |
| CScreenMode | 0xac | m_pfnPlayVideo | `int` |
| CScreenMode | 0xb0 | m_nAudioState | `int` |
| CScreenMode | 0xb4 | m_fAudioVolume | `float` |
| CScreenMode | 0xb8 | m_nAudioFileId | `int` |
| CScreenMode | 0xb94 | m_ScenePanelB | `UIScene` |
| CScreenMode | 0xc0 | m_nVideoState | `int` |
| CScreenMode | 0xc4 | m_fSceneVolume | `float` |
| CScreenMode | 0xcc | m_fPan | `float` |
| CScreenMode | 0xcec | m_ScenePanelC | `UIScene` |
| CScreenMode | 0xd0 | m_fProgressD | `float` |
| CScreenMode | 0xd4 | m_szTooltip | `char[8]` |
| CScreenMode | 0xdc | m_fProgressRatio | `float` |
| CScreenMode | 0xe0 | m_fProgressMax | `float` |
| CScreenMode | 0xe4 | m_fProgressCur | `float` |
| CScreenMode | 0xe4c | m_nAssistMode | `int` |
| CScreenMode | 0xe68 | m_SceneBlock | `int` |
| CScreenMode | 0xe8 | m_fProgress | `float` |
| CScreenMode | 0xec | m_fProgressParam | `float` |
| CScreenMode | 0xf0 | m_fProgressNorm | `float` |
| CScreenMode | 0xf1c | m_bActive | `unsigned char` |
| CScreenMode | 0xf20 | m_nScreenActive | `int` |
| CScreenMode | 0xf24 | m_RoleDialog | `UIRoleDialog` |
| CScreenMode | 0xf4 | m_nBarTotalSize | `int` |
| CScreenMode | 0xf8 | m_fBarOffsetX | `float` |
| CScreenMode | 0xfc | m_fBarOffsetY | `float` |
| CSimpleDirPolicy | 0x0 | _tail_000 | `char[4]` |
| CSimplePosPolicy | 0x0 | _tail_000 | `char[4]` |
| CTaskTpl | 0x10 | m_nCurTask | `int` |
| CTaskTpl | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl | 0x18 | m_nTask | `int` |
| CTaskTpl | 0x1c | m_nMaxTask | `int` |
| CTaskTpl | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl | 0x4 | m_fCurTime | `float` |
| CTaskTpl | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffAction | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffBink | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffModel | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffModel | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffModel | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffShock | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffTime | 0xc | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0x10 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0x14 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0x18 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0x1c | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0x20 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0x4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0x8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 0xc | m_pTask | `char *` |
| CTrail | 0x0 | m_fTime | `float` |
| CTrail | 0x34 | m_dwRenderCounter | `DWORD` |
| CTrail | 0x340 | m_eft | `gbRenderEffect *` |
| CTrail | 0x344 | m_OriginSurface | `IDirect3DSurface9 *` |
| CTrail | 0x38 | m_dwRT | `DWORD` |
| CTrail | 0x3c | m_bReady | `BYTE` |
| CTrail | 0x4 | m_bSupport | `BYTE` |
| CTrail | 0x40 | m_texRT | `gbTexture_D3D[8]` |
| CTrail | 0x5 | m_bEnable | `BYTE` |
| CTrail | 0x8 | m_pCam | `gbCamera *` |
| CTrail | 0xc | m_ScreenQuad | `gbUIQuad` |
| CUSTOMSHAPEVERTEX | 0x0 | v | `D3DXVECTOR3` |
| CUSTOMSHAPEVERTEX | 0x10 | tu | `float` |
| CUSTOMSHAPEVERTEX | 0x14 | tv | `float` |
| CUSTOMSHAPEVERTEX | 0xc | color | `DWORD` |
| CUtil | 0x0 | m_bCanWarp | `unsigned char` |
| CUtil | 0x10 | m_sLogFileName | `char *` |
| CUtil | 0x118 | m_pDefaultString | `char *` |
| CUtil | 0x14 | m_szLogPath | `char[260]` |
| CUtil | 0x160 | m_nTodo_160 | `int[2]` |
| CUtil | 0x168 | m_nListIndex | `int` |
| CUtil | 0x16c | m_nUpdateCounter | `int` |
| CUtil | 0x170 | m_uiItemSlot | `UIItem` |
| CUtil | 0x4 | m_nRandHolder | `short` |
| CUtil | 0x540 | m_nTodo_540 | `int` |
| CUtil | 0x544 | m_nTodo_544 | `int` |
| CUtil | 0x6c8 | m_pScreenMode | `CScreenMode *` |
| CUtil | 0x6cc | m_pBattleSystem | `char *` |
| CUtil | 0x6d0 | m_pListView | `char *` |
| CUtil | 0x6d4 | m_pPropUI | `PropUI *` |
| CUtil | 0x6d8 | m_nRenderMode | `int` |
| CUtil | 0x8 | m_nRandCallCount | `int` |
| CUtil | 0xc | m_fLog | `FILE *` |
| Camera | 0x0 | m_pTodo_0 | `void *` |
| Camera | 0x10 | m_nStepRotate | `int` |
| Camera | 0x110 | m_nFollowMode | `int` |
| Camera | 0x124 | m_pCamera | `gbCamera *` |
| Camera | 0x128 | m_vRayDir | `gbVec3D` |
| Camera | 0x14 | m_nCameraAtPosition | `int` |
| Camera | 0x14c | m_pCollisionMesh | `void *` |
| Camera | 0x15c | m_pRayHitPoint | `void *` |
| Camera | 0x17c | m_nCameraTick | `int` |
| Camera | 0x18 | m_nStepDirection | `int` |
| Camera | 0x180 | m_nPrevCameraTick | `int` |
| Camera | 0x184 | m_fCameraTimer | `float` |
| Camera | 0x188 | m_fLerpSpeed | `float` |
| Camera | 0x18c | m_fLerpProgress | `float` |
| Camera | 0x190 | m_bLerpActive | `unsigned char` |
| Camera | 0x194 | m_ScriptResult | `int` |
| Camera | 0x1c | m_fStepDuration | `float` |
| Camera | 0x20 | m_nTransitionState | `int` |
| Camera | 0x24 | m_fTransitionTime | `float` |
| Camera | 0x28 | m_nTodo_28 | `int` |
| Camera | 0x2c | m_nTodo_02C | `int` |
| Camera | 0x30 | m_nTodo_30 | `int` |
| Camera | 0x34 | m_fStepRotate | `float` |
| Camera | 0x38 | m_nTransitionStep | `int` |
| Camera | 0x3c | m_nTransitionFlags | `int` |
| Camera | 0x4 | m_fCameraEyePosition | `float` |
| Camera | 0x40 | m_fLookAtStart | `float` |
| Camera | 0x44 | m_fLookAtEnd | `float` |
| Camera | 0x48 | m_fLookAtProgress | `float` |
| Camera | 0x4c | m_pLookAtData | `char *` |
| Camera | 0x68 | m_fCameraHeight | `float` |
| Camera | 0x74 | m_nTargetRole | `int` |
| Camera | 0x78 | m_bCreate | `unsigned char` |
| Camera | 0x8 | m_fCameraAtPosition | `float` |
| Camera | 0x80 | m_fFov | `float` |
| Camera | 0x84 | m_fZoomTarget | `int` |
| Camera | 0x88 | m_fAspect | `float` |
| Camera | 0x8c | m_nShakeAmplitude | `int` |
| Camera | 0x90 | m_nShakeDuration | `int` |
| Camera | 0x98 | m_nShakeType | `int` |
| Camera | 0xa0 | m_fShakeFrequency | `float` |
| Camera | 0xa4 | m_fZoomSpeed | `float` |
| Camera | 0xa8 | m_fShakeOffset | `float` |
| Camera | 0xc | m_fCameraUpPosition | `float` |
| Camera | 0xdc | m_nPosition | `int` |
| Camera | 0xe8 | m_fFovTan | `float` |
| Camera | 0xf4 | m_nCollisionFlags | `int` |
| CameraCmd | 0x0 | nCmdID | `int` |
| CameraCmd | 0x4 | nValue | `int` |
| CameraCtrl | 0x0 | m_pCamera | `gbCamera *` |
| CameraCtrl | 0x10 | m_fTargetAngle | `float` |
| CameraCtrl | 0x14 | m_fCurAngle | `float` |
| CameraCtrl | 0x16c | m_nBlendWeightIdx | `int` |
| CameraCtrl | 0x17c | m_nInitParams | `int` |
| CameraCtrl | 0x18 | m_nCamState | `int` |
| CameraCtrl | 0x180 | m_nParamState | `int` |
| CameraCtrl | 0x184 | m_nParamA | `int` |
| CameraCtrl | 0x188 | m_nParamB | `int` |
| CameraCtrl | 0x18c | m_nParamC | `int` |
| CameraCtrl | 0x190 | m_lastFrom | `gbVec3D` |
| CameraCtrl | 0x19c | m_fromVec | `gbVec3D` |
| CameraCtrl | 0x1a8 | m_yaw | `float` |
| CameraCtrl | 0x1ac | m_fCtrlYaw | `float` |
| CameraCtrl | 0x1b0 | m_dist | `int` |
| CameraCtrl | 0x1bc | m_nextYAW | `float` |
| CameraCtrl | 0x1c | m_fAngleDest | `float` |
| CameraCtrl | 0x1c4 | m_fAngle | `float` |
| CameraCtrl | 0x1c8 | m_fOrbitAngle | `float` |
| CameraCtrl | 0x1cc | m_mode | `float` |
| CameraCtrl | 0x1d0 | m_nTodo_1D0 | `float` |
| CameraCtrl | 0x1d4 | m_fCamDist | `float` |
| CameraCtrl | 0x1d8 | m_nWidth | `int` |
| CameraCtrl | 0x1dc | m_nHeight | `int` |
| CameraCtrl | 0x1e0 | m_nAsCurrent | `int` |
| CameraCtrl | 0x1ec | m_vecLookAt | `gbVec3D` |
| CameraCtrl | 0x20 | m_fAngleSrc | `float` |
| CameraCtrl | 0x204 | m_vecUpDir | `gbVec3D` |
| CameraCtrl | 0x22c | m_fViewDistance | `float` |
| CameraCtrl | 0x234 | m_fViewPitch | `float` |
| CameraCtrl | 0x238 | m_fViewYaw | `float` |
| CameraCtrl | 0x23c | m_fDefaultPosX | `float` |
| CameraCtrl | 0x24 | m_fFOV | `float` |
| CameraCtrl | 0x240 | m_fDefaultPosY | `float` |
| CameraCtrl | 0x244 | m_fDefaultPosZ | `float` |
| CameraCtrl | 0x248 | m_fDefaultOffset | `float` |
| CameraCtrl | 0x250 | m_pCameraEvent | `int` |
| CameraCtrl | 0x268 | m_szText | `float` |
| CameraCtrl | 0x26c | m_wParamA | `WORD` |
| CameraCtrl | 0x270 | m_wParamB | `WORD` |
| CameraCtrl | 0x28 | m_fFOVLerp | `float` |
| CameraCtrl | 0x2b0 | m_nEventViewX | `int` |
| CameraCtrl | 0x2b4 | m_nEventViewY | `int` |
| CameraCtrl | 0x2b8 | m_nEventHandle | `int` |
| CameraCtrl | 0x2bc | m_nTodo_2BC | `int` |
| CameraCtrl | 0x2c | m_bCamFlag | `int` |
| CameraCtrl | 0x30 | m_fParamF | `float` |
| CameraCtrl | 0x34 | m_fLerpPosX | `float` |
| CameraCtrl | 0x36d | m_bCamEventFlag | `unsigned char` |
| CameraCtrl | 0x378 | m_bPageMode | `unsigned char` |
| CameraCtrl | 0x379 | m_bCamDirty | `unsigned char` |
| CameraCtrl | 0x37c | m_nPageParam | `int` |
| CameraCtrl | 0x38 | m_fLerpPosY | `float` |
| CameraCtrl | 0x380 | m_bBlendUpdate | `unsigned char` |
| CameraCtrl | 0x384 | m_nBlendWeight | `int` |
| CameraCtrl | 0x38e | m_bBlendWeight | `unsigned char` |
| CameraCtrl | 0x38f | m_bHandleEvent | `unsigned char` |
| CameraCtrl | 0x390 | m_bAutoRotate | `unsigned char` |
| CameraCtrl | 0x394 | m_nBlendTimer | `int` |
| CameraCtrl | 0x39c | m_nBlendState | `int` |
| CameraCtrl | 0x3a0 | m_nSlotParam | `int` |
| CameraCtrl | 0x3c | m_fLerpPosZ | `float` |
| CameraCtrl | 0x4 | m_fMinDist | `float` |
| CameraCtrl | 0x40 | m_fLerpTargetX | `float` |
| CameraCtrl | 0x44 | m_fLerpTargetY | `float` |
| CameraCtrl | 0x48 | m_fLerpTargetZ | `float` |
| CameraCtrl | 0x4a4 | m_nBlendWeightA | `int` |
| CameraCtrl | 0x4a8 | m_nBlendWeightB | `int` |
| CameraCtrl | 0x4ac | m_nBlendWeightC | `int` |
| CameraCtrl | 0x4b0 | m_roleParams | `float` |
| CameraCtrl | 0x4c | m_nUIPosX | `int` |
| CameraCtrl | 0x4f0 | m_nViewState | `int` |
| CameraCtrl | 0x50 | m_nUIWidgetW | `int` |
| CameraCtrl | 0x54 | m_nUIWidgetH | `int` |
| CameraCtrl | 0x58 | m_nUIWidgetSavedW | `int` |
| CameraCtrl | 0x5c | m_fUIWidgetSavedH | `float` |
| CameraCtrl | 0x60 | m_nViewMode | `int` |
| CameraCtrl | 0x64 | m_nViewFlags | `int` |
| CameraCtrl | 0x68 | m_szCamPath | `char[260]` |
| CameraCtrl | 0x8 | m_pTarget | `InputSystem *` |
| CameraCtrl | 0xc | m_nFlags | `int` |
| CameraCtrl | 0xd08 | m_bBlendActive | `unsigned char` |
| CameraCtrl | 0xd09 | m_bBlendPause | `unsigned char` |
| CameraCtrl | 0xd0c | m_nTickCount | `int` |
| CameraCtrl | 0xd10 | m_nTickStamp | `int` |
| CameraCtrl | 0xd14 | m_bTickInit | `unsigned char` |
| CameraCtrl | 0xd18 | m_CamBlocks | `int` |
| CameraParam | 0x0 | nID | `int` |
| CameraParam | 0x4 | _reserved | `int` |
| CameraParam | 0x8 | nParam1 | `int` |
| CameraParam | 0xc | nParam2 | `int` |
| CameraSystem | 0x0 | _tail_000 | `char[4]` |
| CatchableType | 0x0 | properties | `UINT` |
| CatchableType | 0x14 | sizeOrOffset | `int` |
| CatchableType | 0x18 | copyFunction | `PMFN` |
| CatchableType | 0x4 | pType | `TypeDescriptor *` |
| CatchableType | 0x8 | thisDisplacement | `PMD` |
| CatchableTypeArray | 0x0 | nCatchableTypes | `int` |
| ChoseCompose | 0x170 | bkRc | `tagRECT` |
| ChoseCompose | 0x180 | m_id | `unsigned int` |
| ChoseCompose | 0x184 | m_isExit | `unsigned char` |
| ChoseCompose | 0x188 | m_bk | `UIStaticFlex` |
| ChoseCompose | 0x248 | m_ComposeInfo | `UIStatic` |
| ChoseCompose | 0x2e8 | m_RoleName | `UIButton[5]` |
| ChoseCompose | 0x50 | rc | `tagRECT` |
| ChoseCompose | 0x60 | bkWndX | `int` |
| ChoseCompose | 0x64 | bkWndY | `int` |
| ChoseCompose | 0x68 | i | `int` |
| ChoseCompose | 0x6c | j | `int` |
| ChoseCompose | 0x70 | buf | `char[256]` |
| ColRet | 0x0 | dist | `float` |
| ColRet | 0x10 | have | `BYTE` |
| ColRet | 0x14 | counter | `int` |
| ColRet | 0x18 | tri | `Triangle` |
| ColRet | 0x4 | pt | `gbVec3D` |
| Collide_Ray | 0x10 | _vector | `char *[3]` |
| Collide_Ray | 0x1c | _normal | `char *[3]` |
| Collide_Ray | 0x28 | _length | `float` |
| Collide_Ray | 0x2c | _D | `float` |
| Collide_Ray | 0x30 | _nCalculated | `unsigned char` |
| Collide_Ray | 0x31 | _lCalculated | `unsigned char` |
| Collide_Ray | 0x32 | _dCalculated | `unsigned char` |
| Collide_Ray | 0x4 | _origin | `char *[3]` |
| Color4ub | 0x0 | B | `BYTE` |
| Color4ub | 0x1 | G | `BYTE` |
| Color4ub | 0x2 | R | `BYTE` |
| Color4ub | 0x3 | A | `BYTE` |
| Combat | 0x0 | _tail_000 | `char[4]` |
| ComboAttack | 0x0 | name | `char[32]` |
| ComboAttack | 0x20 | id | `DWORD` |
| ComboAttack | 0x24 | man | `unsigned int[4]` |
| ComboAttack | 0x250 | fanwei | `BYTE` |
| ComboAttack | 0x251 | rvtype | `unsigned char[12]` |
| ComboAttack | 0x25e | rolevalue | `short[12]` |
| ComboAttack | 0x278 | hj_EffectRate | `int` |
| ComboAttack | 0x34 | pos | `unsigned char[4]` |
| ComboAttack | 0x38 | skill | `DWORD` |
| ComboAttack | 0x3c | WeaponType | `unsigned char[4]` |
| ComboAttack | 0x40 | Range | `BYTE` |
| ComboAttack | 0x44 | state | `FightState[3]` |
| ComboAttack | 0x50 | Remark | `char[512]` |
| Comp_Donate | 0x0 | m_KeyId | `DWORD` |
| Comp_Donate | 0x4 | m_bDonated | `BYTE` |
| Comp_Donate | 0x5 | m_bComposed | `BYTE` |
| Comp_DonateUI | 0x164 | m_keynum | `int` |
| Comp_DonateUI | 0x168 | m_curitem | `int` |
| Comp_DonateUI | 0x16c | m_state | `Comp_DonateUI::CDState[10]` |
| Comp_DonateUI | 0x194 | m_lang | `char[256][16][5]` |
| Comp_DonateUI | 0x48 | m_RoleId | `int` |
| Comp_DonateUI | 0x4c | m_CompDonate | `Comp_Donate_Detail[10]` |
| Comp_DonateUI | 0x5194 | m_OutFrameT | `UIStatic` |
| Comp_DonateUI | 0x5234 | m_OutFrameR | `UIStatic` |
| Comp_DonateUI | 0x52d4 | m_OutFrameL | `UIStatic` |
| Comp_DonateUI | 0x5374 | m_OutFrameB | `UIStatic` |
| Comp_DonateUI | 0x5414 | m_TopFrame | `UIStatic` |
| Comp_DonateUI | 0x54b4 | m_ExitBtn | `UIButton` |
| Comp_DonateUI | 0x560c | m_Btn | `UIButton[10]` |
| Comp_DonateUI | 0x637c | m_BtnStatic | `UIStatic[10]` |
| Comp_DonateUI | 0x69bc | m_mouseon | `int` |
| Comp_DonateUI | 0x69c0 | m_RoleDlg | `UIRoleDialog` |
| Comp_DonateUI | 0x6f18 | m_SelectDlg | `UIRoleSelect` |
| Comp_DonateUI | 0x7538 | m_IfSel | `unsigned char` |
| Comp_DonateUI | 0x7539 | m_IfGetSel | `unsigned char` |
| Comp_DonateUI | 0x753c | m_RoleDlgRc | `tagRECT` |
| Comp_DonateUI | 0x754c | m_AddIntimacyDonate | `int[5]` |
| Comp_DonateUI | 0x7560 | m_AddIntimacyComp | `int[5]` |
| Comp_DonateUI | 0x7574 | m_RoleLang | `char[512][4][5]` |
| Comp_DonateUI | 0x9d74 | m_SelBtn | `int` |
| Comp_DonateUI | 0x9d78 | m_Msg | `MUIDialog` |
| Comp_DonateUI | 0xa2e0 | m_ActiveDlg | `MUIDialog` |
| Comp_DonateUI | 0xa848 | m_ExitDlg | `MUIDialog` |
| Comp_DonateUI | 0xadb0 | m_IsActive | `unsigned char` |
| Comp_DonateUI | 0xadb1 | m_IsOver | `unsigned char` |
| Comp_DonateUI | 0xadb4 | m_LineupComp | `LineupComp` |
| Comp_DonateUI | 0xb590 | m_BK | `UIStatic` |
| Comp_Donate_Detail | 0x0 | m_KeyId | `DWORD` |
| Comp_Donate_Detail | 0x10 | m_Intimacy | `DWORD` |
| Comp_Donate_Detail | 0x14 | m_CompId | `DWORD` |
| Comp_Donate_Detail | 0x18 | m_bComposed | `BYTE` |
| Comp_Donate_Detail | 0x19 | m_bCanRepeat | `BYTE` |
| Comp_Donate_Detail | 0x4 | m_bDonated | `BYTE` |
| Comp_Donate_Detail | 0x5 | m_bHasKey | `BYTE` |
| Comp_Donate_Detail | 0x8 | m_SourceId | `DWORD` |
| Comp_Donate_Detail | 0xc | m_bHasSource | `BYTE` |
| ComposeUI | 0x190 | m_MiddleFrame | `UIStatic[3]` |
| ComposeUI | 0x370 | m_Talk | `UIButton` |
| ComposeUI | 0x48 | m_CurRender | `int` |
| ComposeUI | 0x4c | m_isCreatable | `unsigned char` |
| ComposeUI | 0x4c8 | m_Compose | `UIButton` |
| ComposeUI | 0x50 | m_TopFrame | `UIStatic` |
| ComposeUI | 0x620 | m_Exit | `UIButton` |
| ComposeUI | 0x778 | m_SelBtn | `int` |
| ComposeUI | 0xf0 | m_BottomFrame | `UIStatic` |
| Config | 0x4 | m_ptr_4 | `unsigned char *` |
| ConfigFile | 0x0 | m_pDefaultString | `char *` |
| DICOLORSET | 0x0 | dwSize | `UINT` |
| DICOLORSET | 0x10 | cCalloutHighlight | `UINT` |
| DICOLORSET | 0x14 | cBorder | `UINT` |
| DICOLORSET | 0x18 | cControlFill | `UINT` |
| DICOLORSET | 0x1c | cHighlightFill | `UINT` |
| DICOLORSET | 0x20 | cAreaFill | `UINT` |
| DICOLORSET | 0x4 | cTextFore | `UINT` |
| DICOLORSET | 0x8 | cTextHighlight | `UINT` |
| DICOLORSET | 0xc | cCalloutLine | `UINT` |
| DIDEVCAPS | 0x0 | dwSize | `DWORD` |
| DIDEVCAPS | 0x10 | dwButtons | `DWORD` |
| DIDEVCAPS | 0x14 | dwPOVs | `DWORD` |
| DIDEVCAPS | 0x18 | dwFFSamplePeriod | `DWORD` |
| DIDEVCAPS | 0x1c | dwFFMinTimeResolution | `DWORD` |
| DIDEVCAPS | 0x20 | dwFirmwareRevision | `DWORD` |
| DIDEVCAPS | 0x24 | dwHardwareRevision | `DWORD` |
| DIDEVCAPS | 0x28 | dwFFDriverVersion | `DWORD` |
| DIDEVCAPS | 0x4 | dwFlags | `DWORD` |
| DIDEVCAPS | 0x8 | dwDevType | `DWORD` |
| DIDEVCAPS | 0xc | dwAxes | `DWORD` |
| DIDEVICEINSTANCEA | 0x0 | dwSize | `DWORD` |
| DIDEVICEINSTANCEA | 0x14 | guidProduct | `_GUID` |
| DIDEVICEINSTANCEA | 0x16c | tszProductName | `char[324]` |
| DIDEVICEINSTANCEA | 0x24 | dwDevType | `DWORD` |
| DIDEVICEINSTANCEA | 0x28 | tszInstanceName | `char[324]` |
| DIDEVICEINSTANCEA | 0x2b0 | guidFFDriver | `_GUID` |
| DIDEVICEINSTANCEA | 0x2c0 | wUsagePage | `WORD` |
| DIDEVICEINSTANCEA | 0x2c2 | wUsage | `WORD` |
| DIDEVICEINSTANCEA | 0x4 | guidInstance | `_GUID` |
| DIDEVICEOBJECTDATA | 0x0 | dwOfs | `DWORD` |
| DIDEVICEOBJECTDATA | 0x10 | uAppData | `UINT` |
| DIDEVICEOBJECTDATA | 0x4 | dwData | `DWORD` |
| DIDEVICEOBJECTDATA | 0x8 | dwTimeStamp | `DWORD` |
| DIDEVICEOBJECTDATA | 0xc | dwSequence | `DWORD` |
| DIDEVICEOBJECTINSTANCEA | 0x0 | dwSize | `DWORD` |
| DIDEVICEOBJECTINSTANCEA | 0x14 | dwOfs | `DWORD` |
| DIDEVICEOBJECTINSTANCEA | 0x164 | dwFFMaxForce | `DWORD` |
| DIDEVICEOBJECTINSTANCEA | 0x168 | dwFFForceResolution | `DWORD` |
| DIDEVICEOBJECTINSTANCEA | 0x16c | wCollectionNumber | `WORD` |
| DIDEVICEOBJECTINSTANCEA | 0x16e | wDesignatorIndex | `WORD` |
| DIDEVICEOBJECTINSTANCEA | 0x170 | wUsagePage | `WORD` |
| DIDEVICEOBJECTINSTANCEA | 0x172 | wUsage | `WORD` |
| DIDEVICEOBJECTINSTANCEA | 0x174 | dwDimension | `DWORD` |
| DIDEVICEOBJECTINSTANCEA | 0x178 | wExponent | `WORD` |
| DIDEVICEOBJECTINSTANCEA | 0x17a | wReportId | `WORD` |
| DIDEVICEOBJECTINSTANCEA | 0x18 | dwType | `DWORD` |
| DIDEVICEOBJECTINSTANCEA | 0x1c | dwFlags | `DWORD` |
| DIDEVICEOBJECTINSTANCEA | 0x20 | tszName | `char[324]` |
| DIDEVICEOBJECTINSTANCEA | 0x4 | guidType | `_GUID` |
| DIEFFECT | 0x0 | dwSize | `DWORD` |
| DIEFFECT | 0x10 | dwGain | `DWORD` |
| DIEFFECT | 0x14 | dwTriggerButton | `DWORD` |
| DIEFFECT | 0x18 | dwTriggerRepeatInterval | `DWORD` |
| DIEFFECT | 0x1c | cAxes | `DWORD` |
| DIEFFECT | 0x20 | rgdwAxes | `DWORD *` |
| DIEFFECT | 0x24 | rglDirection | `int *` |
| DIEFFECT | 0x28 | lpEnvelope | `DIENVELOPE *` |
| DIEFFECT | 0x2c | cbTypeSpecificParams | `DWORD` |
| DIEFFECT | 0x30 | lpvTypeSpecificParams | `char *` |
| DIEFFECT | 0x34 | dwStartDelay | `DWORD` |
| DIEFFECT | 0x4 | dwFlags | `DWORD` |
| DIEFFECT | 0x8 | dwDuration | `DWORD` |
| DIEFFECT | 0xc | dwSamplePeriod | `DWORD` |
| DIEFFECTINFOA | 0x0 | dwSize | `DWORD` |
| DIEFFECTINFOA | 0x14 | dwEffType | `DWORD` |
| DIEFFECTINFOA | 0x18 | dwStaticParams | `DWORD` |
| DIEFFECTINFOA | 0x1c | dwDynamicParams | `DWORD` |
| DIEFFECTINFOA | 0x20 | tszName | `char[324]` |
| DIEFFECTINFOA | 0x4 | guid | `_GUID` |
| DIEFFESCAPE | 0x0 | dwSize | `DWORD` |
| DIEFFESCAPE | 0x10 | lpvOutBuffer | `char *` |
| DIEFFESCAPE | 0x14 | cbOutBuffer | `DWORD` |
| DIEFFESCAPE | 0x4 | dwCommand | `DWORD` |
| DIEFFESCAPE | 0x8 | lpvInBuffer | `char *` |
| DIEFFESCAPE | 0xc | cbInBuffer | `DWORD` |
| DIENVELOPE | 0x0 | dwSize | `DWORD` |
| DIENVELOPE | 0x10 | dwFadeTime | `DWORD` |
| DIENVELOPE | 0x4 | dwAttackLevel | `DWORD` |
| DIENVELOPE | 0x8 | dwAttackTime | `DWORD` |
| DIENVELOPE | 0xc | dwFadeLevel | `DWORD` |
| DIFILEEFFECT | 0x0 | dwSize | `DWORD` |
| DIFILEEFFECT | 0x14 | lpDiEffect | `DIEFFECT *` |
| DIFILEEFFECT | 0x18 | szFriendlyName | `char[324]` |
| DIFILEEFFECT | 0x4 | GuidEffect | `_GUID` |
| DIPROPDWORD | 0x0 | diph | `DIPROPHEADER` |
| DIPROPDWORD | 0x10 | dwData | `DWORD` |
| DIPROPHEADER | 0x0 | dwSize | `DWORD` |
| DIPROPHEADER | 0x4 | dwHeaderSize | `DWORD` |
| DIPROPHEADER | 0x8 | dwObj | `DWORD` |
| DIPROPHEADER | 0xc | dwHow | `DWORD` |
| DPINFO | 0x0 | active | `long` |
| DPINFO | 0x4 | provider | `DWORD` |
| DPINFO | 0x8 | TYPE | `DPINFO___unnamed` |
| DPINFO___unnamed | 0x0 | _tail_000 | `char[96]` |
| DataConst | 0x0 | val | `float` |
| DataConst | 0x4 | name | `char[32]` |
| DealData | 0x0 | m_isHarshRfus | `BYTE` |
| DealData | 0x210 | m_LoadGDB | `PAL_GDB` |
| DealData | 0x4 | m_LoadTxt | `TxtFile` |
| DealData | 0xc6fcc | m_IsLang | `BYTE` |
| DealData | 0xc6fd0 | m_LoadLang | `TxtFile` |
| DealData | 0xc71dc | m_lastFile | `char[256]` |
| DealData | 0xc72dc | m_ManagerData | `st_Manager` |
| DealUI | 0x184 | m_FlagM | `UIStatic[5]` |
| DealUI | 0x47c | mb_BuyEquip | `UIButton` |
| DealUI | 0x48 | _isCreatable | `BYTE` |
| DealUI | 0x49 | m_Is | `unsigned char[5]` |
| DealUI | 0x4e | m_ST | `WORD` |
| DealUI | 0x50 | m_ID | `WORD` |
| DealUI | 0x54 | m_FlagT | `UIStatic` |
| DealUI | 0x5d4 | mb_BuyProp | `UIButton` |
| DealUI | 0x72c | mb_Sale | `UIButton` |
| DealUI | 0x884 | mb_Talk | `UIButton` |
| DealUI | 0x9dc | m_IsExit | `BYTE` |
| DealUI | 0x9e0 | mb_Exit | `UIButton` |
| DealUI | 0xb38 | m_TabBtn | `UITabBtn` |
| DealUI | 0xb50 | m_BkWnd | `UIStatic` |
| DealUI | 0xbe8 | m_curRender | `int` |
| DealUI | 0xbec | pEquipUI | `EquipUI *` |
| DealUI | 0xbf0 | pPropUI | `PropUI *` |
| DealUI | 0xbf4 | pSaleUI | `SaleUI *` |
| DealUI | 0xbf8 | pInterceptTex | `gbTexture *` |
| DealUI | 0xbfc | sv | `float` |
| DealUI | 0xc00 | ev | `float` |
| DealUI | 0xc04 | m_opt | `BYTE` |
| DealUI | 0xec | m_FlagB | `UIStatic` |
| DisplayConfig | 0x0 | m_nFlags | `int` |
| DisplayConfig | 0x4 | m_nSettingWidth | `int` |
| DisplayConfig | 0x8 | m_nSettingHeight | `int` |
| DisplayConfig | 0xc | m_pDisplayMode | `char *` |
| ECBRoleSpecState | 0x0 | _tail_000 | `char[4]` |
| EH3_EXCEPTION_REGISTRATION | 0x0 | Next | `struct _EH3_EXCEPTION_REGISTRATION *` |
| EH3_EXCEPTION_REGISTRATION | 0x4 | ExceptionHandler | `PVOID` |
| EH3_EXCEPTION_REGISTRATION | 0x8 | ScopeTable | `PSCOPETABLE_ENTRY` |
| EH3_EXCEPTION_REGISTRATION | 0xc | TryLevel | `DWORD` |
| EffAudioNode | 0x0 | _tail_000 | `char[32]` |
| EffBinkNode | 0x0 | _tail_000 | `char[32]` |
| EffCallBackNode | 0x0 | _tail_000 | `char[32]` |
| EffModeParam | 0x0 | nSide | `int` |
| EffModeParam | 0x4 | ePos | `eSkyEffPos` |
| EffModeParam | 0x8 | bAreaRand | `BYTE` |
| EffMultiPassNode | 0x0 | _tail_000 | `char[32]` |
| EffObjectPool | 0x1c | m_nCount | `int` |
| EffObjectPool | 0x20 | m_nCount2 | `int` |
| EffObjectPool | 0xc | m_pObjects | `void *` |
| EffTargetPool | 0x18 | m_pPool | `void *` |
| EffTargetPool | 0x1c | m_nCount | `int` |
| EffectInfo | 0x0 | _pixelPos | `int` |
| EffectInfo | 0x4 | _dstPixel | `unsigned char[4]` |
| EffectInfo | 0x8 | _srcPixel | `unsigned char[4]` |
| EffectInfo | 0xc | _bbb | `BYTE` |
| EffectItem | 0x0 | _pixelNum | `int` |
| EffectItem | 0x4 | _alpha | `BYTE` |
| EffectItem | 0x8 | _pixelInfo | `std::vector<EffectInfo,std::allocator<EffectInfo> >` |
| EquipUI | 0x101f0 | m_ArrowNum | `UIStatic[8][2][5]` |
| EquipUI | 0x133f0 | m_ArrowRc | `tagRECT[8][6][5]` |
| EquipUI | 0x142f0 | m_IsArrow | `unsigned char[8][6][5]` |
| EquipUI | 0x143e0 | m_OldSelect | `int` |
| EquipUI | 0x143e4 | m_IsMove | `unsigned char[8][6][5]` |
| EquipUI | 0x144d4 | m_AnimateRc | `tagRECT[8][6][5]` |
| EquipUI | 0x150 | m_SelNum | `int` |
| EquipUI | 0x153d4 | m_ArrowMove | `UIAnimate[8][6][5]` |
| EquipUI | 0x154 | m_ListNum | `int *` |
| EquipUI | 0x158 | m_x | `int` |
| EquipUI | 0x15c | m_y | `int` |
| EquipUI | 0x160 | m_Sum | `int` |
| EquipUI | 0x164 | i | `int` |
| EquipUI | 0x168 | j | `int` |
| EquipUI | 0x16c | k | `int` |
| EquipUI | 0x170 | _isCreatable | `unsigned char` |
| EquipUI | 0x174 | _flashSpeed | `float` |
| EquipUI | 0x178 | m_EquipData | `st_Manager` |
| EquipUI | 0x18494 | m_Icon | `UIStaticRM[6][5]` |
| EquipUI | 0x19a9c | m_Select | `UIStatic[6][5]` |
| EquipUI | 0x1ad5c | m_IsControlEquip | `unsigned char` |
| EquipUI | 0x1ad5d | m_IsEquip | `unsigned char[6][5]` |
| EquipUI | 0x1ad7b | m_IsMsg | `unsigned char` |
| EquipUI | 0x1ad7c | m_EquipingNum | `int *` |
| EquipUI | 0x1ad80 | m_Equiping | `int[6][5]` |
| EquipUI | 0x1adf8 | m_UnEquipingNum | `int *` |
| EquipUI | 0x1adfc | m_MaxNum | `int *` |
| EquipUI | 0x1ae00 | m_Adorn | `unsigned char[2][5]` |
| EquipUI | 0x1ae0c | m_3DObj | `UI3DCtrl` |
| EquipUI | 0x1af40 | m_Msg | `MUIDialog` |
| EquipUI | 0x1b4a8 | m_TalkFrame | `UIStatic` |
| EquipUI | 0x1b548 | m_Ready | `UIStatic` |
| EquipUI | 0x1b5e8 | m_ReadyRc | `tagRECT` |
| EquipUI | 0x1b5f8 | mb_EquipYes | `UIButton` |
| EquipUI | 0x1b750 | mb_EquipNo | `UIButton` |
| EquipUI | 0x1b8a8 | m_EquipTalk | `UIStatic` |
| EquipUI | 0x1b948 | m_EquipRc | `tagRECT` |
| EquipUI | 0x1b958 | m_ListFrame | `UIStatic` |
| EquipUI | 0x1b9f8 | m_ListGrid | `UIStatic[14]` |
| EquipUI | 0x1c2b8 | m_ScrollHB | `UIStatic` |
| EquipUI | 0x1c358 | m_EquipFlag | `UIStatic` |
| EquipUI | 0x1c3f8 | m_ListEquipTitle | `UIStatic` |
| EquipUI | 0x1c498 | ml_ListEquip | `UIListBox` |
| EquipUI | 0x1c9a0 | ml_ListEquipRc | `tagRECT` |
| EquipUI | 0x1c9b0 | m_btnGroup | `BtnGroup` |
| EquipUI | 0x1cc94 | m_ctrlTime | `float` |
| EquipUI | 0x1cc98 | m_bCanUpdate1 | `unsigned char` |
| EquipUI | 0x1cc99 | m_bCanUpdate2 | `unsigned char` |
| EquipUI | 0x1cc9c | m_EquipRemarkBk | `UIStatic` |
| EquipUI | 0x1cd3c | m_EquipRemark | `UIStatic` |
| EquipUI | 0x1cddc | m_EquipRemarkRc | `tagRECT` |
| EquipUI | 0x1cdec | m_EquipAtt | `UIStatic` |
| EquipUI | 0x1ce8c | m_EquipAttRc | `tagRECT` |
| EquipUI | 0x1ce9c | m_MoneyRemark | `UIStatic` |
| EquipUI | 0x1cf3c | m_MoneyRc | `tagRECT` |
| EquipUI | 0x1cf4c | m_SumEquip | `UIStatic` |
| EquipUI | 0x1cfec | m_SumRc | `tagRECT` |
| EquipUI | 0x1cffc | mb_OK | `UIButton` |
| EquipUI | 0x1d154 | mb_OKRc | `tagRECT` |
| EquipUI | 0x1d164 | m_IsDicker | `unsigned char` |
| EquipUI | 0x1d168 | mb_Cancel | `UIButton` |
| EquipUI | 0x1d2c0 | mb_CancelRc | `tagRECT` |
| EquipUI | 0x1d2d0 | mb_Exit | `UIButton` |
| EquipUI | 0x1d428 | mb_ExitRc | `tagRECT` |
| EquipUI | 0x1d438 | m_TabBtn | `UITabBtn` |
| EquipUI | 0x1d450 | mb_DKRc | `tagRECT` |
| EquipUI | 0x1d460 | haveRc | `tagRECT` |
| EquipUI | 0x1d470 | m_isCancelTalk | `unsigned char` |
| EquipUI | 0x45d8 | p_DealData | `PlayerItem *` |
| EquipUI | 0x45dc | m_TempData | `PlayerAtt[5]` |
| EquipUI | 0x48 | bkWndX | `int` |
| EquipUI | 0x4c | bkWndY | `int` |
| EquipUI | 0x50 | buf | `char[256]` |
| EquipUI | 0x63a0 | rc | `tagRECT` |
| EquipUI | 0x63b0 | m_Frame | `UIStatic` |
| EquipUI | 0x6450 | m_FrameBar | `UIFlexBar` |
| EquipUI | 0x64a4 | m_Flag | `UIStatic` |
| EquipUI | 0x6544 | m_OutFrameT | `UIStatic` |
| EquipUI | 0x65e4 | m_OutFrameR | `UIStatic` |
| EquipUI | 0x6684 | m_OutFrameL | `UIStatic` |
| EquipUI | 0x6724 | m_OutFrameB | `UIStatic` |
| EquipUI | 0x67c4 | m_ani | `UIAnimateCtrl` |
| EquipUI | 0x6868 | m_Role | `UIStatic[5]` |
| EquipUI | 0x6b88 | m_RoleRc | `tagRECT[5]` |
| EquipUI | 0x6bd8 | RoleX | `int` |
| EquipUI | 0x6bdc | RoleY | `int` |
| EquipUI | 0x6be0 | HeadW | `int` |
| EquipUI | 0x6be4 | HeadH | `int` |
| EquipUI | 0x6be8 | m_Is | `unsigned char[5]` |
| EquipUI | 0x6bf0 | m_Arrow | `UIStatic[8][6][5]` |
| ExternalStatistics | 0x0 | _tail_000 | `char[4]` |
| FILETIME | 0x0 | dwLowDateTime | `int` |
| FILETIME | 0x4 | dwHighDateTime | `int` |
| FLOATING_SAVE_AREA | 0x0 | ControlWord | `UINT` |
| FLOATING_SAVE_AREA | 0x10 | ErrorSelector | `UINT` |
| FLOATING_SAVE_AREA | 0x14 | DataOffset | `UINT` |
| FLOATING_SAVE_AREA | 0x18 | DataSelector | `UINT` |
| FLOATING_SAVE_AREA | 0x4 | StatusWord | `UINT` |
| FLOATING_SAVE_AREA | 0x6c | Cr0NpxState | `UINT` |
| FLOATING_SAVE_AREA | 0x8 | TagWord | `UINT` |
| FLOATING_SAVE_AREA | 0xc | ErrorOffset | `UINT` |
| FLTSTAGE | 0x0 | provider | `_FLTPROVIDER *` |
| FLTSTAGE | 0x4 | sample_state | `long` |
| FightInfo | 0x0 | monsterID | `unsigned int[6]` |
| FightInfo | 0x18 | nAllMonsterNum | `int` |
| FightInfo | 0x1c | nMaxRound | `int` |
| FightInfo | 0x20 | sSceneName | `char[32]` |
| FightInfo | 0x40 | eSceneFiveMagic | `ECBFiveMagic` |
| FightInfo | 0x44 | eMeetType | `ECBMeetEnemy` |
| FightInfo | 0x48 | eBattleFieldAttr | `ECBBattleFieldAttr` |
| FightInfo | 0x4c | bMustFail | `BYTE` |
| FightInfo | 0x50 | nRoleWillNotBeAttack | `int` |
| FightInfo | 0x54 | bScript | `BYTE` |
| FightInfo | 0x55 | bBossMusic | `BYTE` |
| FightInfo | 0x56 | bFiveNimbus | `BYTE` |
| FightInfo | 0x57 | bPXVariance | `BYTE` |
| FightInfo | 0x58 | bFirst | `BYTE` |
| FightInfo | 0x5c | pMosnter | `Role *` |
| FightItem | 0x0 | id | `DWORD` |
| FightItem | 0x24 | ModelID | `char[30]` |
| FightItem | 0x260 | price | `int` |
| FightItem | 0x264 | type | `BYTE` |
| FightItem | 0x265 | weapontype | `BYTE` |
| FightItem | 0x266 | user | `unsigned char[5]` |
| FightItem | 0x26b | att | `unsigned char[5]` |
| FightItem | 0x270 | gu | `int` |
| FightItem | 0x274 | special | `BYTE` |
| FightItem | 0x275 | fanwei | `BYTE` |
| FightItem | 0x276 | space | `BYTE` |
| FightItem | 0x277 | rvtype | `unsigned char[12]` |
| FightItem | 0x284 | rolevalue | `short[12]` |
| FightItem | 0x29c | fstype | `unsigned char[31]` |
| FightItem | 0x2bc | fightstate | `short[31]` |
| FightItem | 0x2fc | tosshurt | `int` |
| FightItem | 0x300 | lian | `int` |
| FightItem | 0x304 | saveqi | `short` |
| FightItem | 0x306 | saveshen | `short` |
| FightItem | 0x308 | addbaoji | `short` |
| FightItem | 0x30a | addteji | `short` |
| FightItem | 0x30c | embracer | `int` |
| FightItem | 0x310 | compose_material | `DWORD` |
| FightItem | 0x314 | compose_type | `int` |
| FightItem | 0x318 | compose_final | `DWORD` |
| FightItem | 0x31c | compose_intimacy | `DWORD` |
| FightItem | 0x4 | name | `char[32]` |
| FightItem | 0x42 | ImageID | `char[30]` |
| FightItemScriptBlock | 0x164 | bLoaded | `char` |
| FightItemScriptBlock | 0x168 | pScriptData | `char[152]` |
| FightSkill | 0x0 | id | `DWORD` |
| FightSkill | 0x1c | name | `char[32]` |
| FightSkill | 0x23c | user | `unsigned char[5]` |
| FightSkill | 0x241 | fanwei | `BYTE` |
| FightSkill | 0x242 | special | `BYTE` |
| FightSkill | 0x243 | rvtype | `unsigned char[12]` |
| FightSkill | 0x250 | rolevalue | `short[12]` |
| FightSkill | 0x268 | succ | `BYTE` |
| FightSkill | 0x26a | fs | `short[31]` |
| FightSkill | 0x2a8 | consumervtype | `int[2]` |
| FightSkill | 0x2b0 | consumetype | `int[3]` |
| FightSkill | 0x2bc | tutype | `BYTE` |
| FightSkill | 0x2c0 | tusuval | `int` |
| FightSkill | 0x2c4 | lv | `BYTE` |
| FightSkill | 0x2c5 | lvup | `unsigned char[4]` |
| FightSkill | 0x2c9 | rolelv | `BYTE` |
| FightSkill | 0x2ca | magiclv | `BYTE` |
| FightSkill | 0x2cc | nextid | `DWORD` |
| FightSkill | 0x2d0 | isuseall | `BYTE` |
| FightSkill | 0x2d4 | hecheng | `unsigned int[3]` |
| FightSkill | 0x2e0 | heskill | `unsigned int[3]` |
| FightSkill | 0x2ec | helv | `unsigned char[3]` |
| FightSkill | 0x2ef | helvself | `unsigned char[3]` |
| FightSkill | 0x2f2 | manlv | `unsigned char[3]` |
| FightSkill | 0x2f5 | heji | `BYTE` |
| FightSkill | 0x3c | desc | `char[512]` |
| FightSkill | 0x4 | type | `BYTE` |
| FightSkill | 0x8 | att | `int[5]` |
| FindArc | 0x0 | mPal3SetUpPath | `char[256]` |
| FindArc | 0x100 | arcPos | `ArcPosition[36]` |
| FindArc | 0x2500 | mRealNum | `int` |
| FontPrint3DInfo | 0x0 | font | `gbFontType` |
| FontPrint3DInfo | 0x10 | strloc | `int` |
| FontPrint3DInfo | 0x14 | strlen | `int` |
| FontPrint3DInfo | 0x18 | scalex | `float` |
| FontPrint3DInfo | 0x1c | scaley | `float` |
| FontPrint3DInfo | 0x20 | color | `gbColorQuad` |
| FontPrint3DInfo | 0x4 | x | `float` |
| FontPrint3DInfo | 0x8 | y | `float` |
| FontPrint3DInfo | 0xc | z | `float` |
| FontPrintInfo | 0x0 | font | `gbFontType` |
| FontPrintInfo | 0x10 | endx | `float` |
| FontPrintInfo | 0x14 | endy | `float` |
| FontPrintInfo | 0x18 | strloc | `int` |
| FontPrintInfo | 0x1c | strlen | `int` |
| FontPrintInfo | 0x20 | scalex | `float` |
| FontPrintInfo | 0x24 | scaley | `float` |
| FontPrintInfo | 0x28 | color | `gbColorQuad` |
| FontPrintInfo | 0x4 | x | `float` |
| FontPrintInfo | 0x8 | y | `float` |
| FontPrintInfo | 0xc | z | `float` |
| FontSortInfoObj | 0x0 | index | `int` |
| FontSortInfoObj | 0x4 | z | `float` |
| FrameTex | 0x0 | m_pTex | `gbTexture *` |
| FuncInfoV1 | 0x0 | magicNumber | `int` |
| FuncInfoV1 | 0x10 | pTryBlockMap | `char *` |
| FuncInfoV1 | 0x14 | nIPMapEntries | `int` |
| FuncInfoV1 | 0x18 | pIPtoStateMap | `char *` |
| FuncInfoV1 | 0x4 | maxState | `int` |
| FuncInfoV1 | 0x8 | pUnwindMap | `char *` |
| FuncInfoV1 | 0xc | nTryBlocks | `int` |
| GRP_KEYREG | 0x0 | Data | `int` |
| GRP_KEYREG | 0x4 | HoldTime | `int` |
| GRP_KEYREG | 0x8 | CountMode | `int` |
| GRP_KEYREG | 0xc | PressTime | `int` |
| GRPinput | 0x0 | m_lpDI | `IDirectInput8 *` |
| GRPinput | 0x10 | m_mouseMinX | `long` |
| GRPinput | 0x1030 | m_DIKToKEY | `ULONG[256]` |
| GRPinput | 0x14 | m_mouseMinY | `long` |
| GRPinput | 0x1430 | MouseState | `char[20]` |
| GRPinput | 0x1444 | charTOscan | `ULONG[256]` |
| GRPinput | 0x178 | m_keyRaw | `BYTE[256]` |
| GRPinput | 0x18 | m_mouseMaxX | `long` |
| GRPinput | 0x1844 | KeyTransformation | `int[10]` |
| GRPinput | 0x186c | m_bMouse | `int` |
| GRPinput | 0x1870 | m_bKeyboard | `int` |
| GRPinput | 0x1874 | m_bJoystick | `int` |
| GRPinput | 0x1878 | KeyInfo | `GRP_KEYREG[270]` |
| GRPinput | 0x1c | m_mouseMaxY | `long` |
| GRPinput | 0x20 | m_joystickMinX | `long` |
| GRPinput | 0x24 | m_joystickMinY | `long` |
| GRPinput | 0x278 | m_keyPressTimes | `ULONG[270]` |
| GRPinput | 0x28 | m_joystickMaxX | `long` |
| GRPinput | 0x2c | m_joystickMaxY | `long` |
| GRPinput | 0x30 | m_mousept | `POINT` |
| GRPinput | 0x38 | m_mouseX | `long` |
| GRPinput | 0x3c | m_mouseY | `long` |
| GRPinput | 0x4 | m_lpDIDKeyboard | `IDirectInputDevice8 *` |
| GRPinput | 0x40 | m_mouseFreeX | `long` |
| GRPinput | 0x44 | m_mouseFreeY | `long` |
| GRPinput | 0x48 | m_mouseDeltaX | `long` |
| GRPinput | 0x4c | m_mouseDeltaY | `long` |
| GRPinput | 0x50 | m_joystickX | `long` |
| GRPinput | 0x54 | m_joystickY | `long` |
| GRPinput | 0x58 | m_joystickFreeX | `long` |
| GRPinput | 0x5c | m_joystickFreeY | `long` |
| GRPinput | 0x60 | m_joystickDeltaX | `long` |
| GRPinput | 0x64 | m_joystickDeltaY | `long` |
| GRPinput | 0x68 | m_keyStates | `BYTE[270]` |
| GRPinput | 0x6b0 | m_keyDragStartPositions | `ULONG[270][2]` |
| GRPinput | 0x8 | m_lpDIDMouse | `IDirectInputDevice8 *` |
| GRPinput | 0xc | m_mouseSensitivity | `float` |
| GRPinput | 0xf20 | m_shiftedKeyStates | `BYTE[270]` |
| GeomNode | 0x0 | pNext | `GeomNode *` |
| GeomNode | 0x100 | m_nTodo_100 | `int` |
| GeomNode | 0x110 | mesh | `int` |
| GeomNode | 0x4 | pParent | `GeomNode *` |
| GeomNode | 0x5c | worldTransform | `Matrix4` |
| GeomNode | 0x8 | children | `char[16]` |
| GeomNode | 0x9c | staticTransform | `Matrix4` |
| GeomNote | 0x0 | scene | `char[4]` |
| GeomNote | 0x4 | area | `char[2]` |
| GeomNote | 0x6 | flag | `BYTE` |
| GhostParam | 0x0 | name | `char[32]` |
| GhostParam | 0x20 | id | `DWORD` |
| GhostParam | 0x24 | Type | `int` |
| GhostParam | 0x28 | HP | `int` |
| GhostParam | 0x2c | ATK | `int` |
| Glow | 0x0 | m_eft | `gbRenderEffect *` |
| Glow | 0x4 | m_pGeomEft | `gbRenderEffect *` |
| Glow | 0x8 | m_nPass | `int` |
| Glow | 0xc | m_pObjArray | `char[16]` |
| GlowObj | 0x10 | m_GeomColor | `gbColorFlt` |
| GlowObj | 0x4 | m_bEnable | `BYTE` |
| GlowObj | 0x8 | m_nStepSize | `int` |
| GlowObj | 0xc | m_nPass | `int` |
| GrayScale | 0x0 | m_bEnable | `BYTE` |
| GrayScale | 0x4 | m_pTex | `gbTexture *` |
| HandlerType | 0x0 | adjectives | `int` |
| HandlerType | 0x4 | pType | `const struct TypeDescriptor *` |
| HandlerType | 0x8 | dispCatchObj | `int` |
| HandlerType | 0xc | addressOfHandler | `char *` |
| HeadMsg | 0x18 | m_fTime | `float` |
| HeadMsg | 0x1c | m_nType | `int` |
| HeadMsg | 0x20 | m_nY | `int` |
| HeadMsg | 0x4 | m_bEnable | `unsigned char` |
| HeadMsg | 0x8 | m_szMsg | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` |
| IMAGE_DATA_DIRECTORY | 0x0 | VirtualAddress | `int` |
| IMAGE_DATA_DIRECTORY | 0x4 | Size | `int` |
| IMAGE_FILE_HEADER | 0x0 | Machine | `int` |
| IMAGE_FILE_HEADER | 0x10 | NumberOfSymbols | `int` |
| IMAGE_FILE_HEADER | 0x14 | SizeOfOptionalHeader | `int` |
| IMAGE_FILE_HEADER | 0x18 | Characteristics | `int` |
| IMAGE_FILE_HEADER | 0x4 | NumberOfSections | `int` |
| IMAGE_FILE_HEADER | 0x8 | TimeDateStamp | `int` |
| IMAGE_FILE_HEADER | 0xc | PointerToSymbolTable | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x0 | Magic | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x10 | SizeOfInitializedData | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x14 | SizeOfUninitializedData | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x18 | AddressOfEntryPoint | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x1c | BaseOfCode | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x20 | BaseOfData | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x24 | ImageBase | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x28 | SectionAlignment | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x2c | FileAlignment | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x30 | MajorOperatingSystemVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x34 | MinorOperatingSystemVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x38 | MajorImageVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x3c | MinorImageVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x4 | MajorLinkerVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x40 | MajorSubsystemVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x44 | MinorSubsystemVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x48 | Win32VersionValue | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x4c | SizeOfImage | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x50 | SizeOfHeaders | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x54 | CheckSum | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x58 | Subsystem | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x5c | DllCharacteristics | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x60 | SizeOfStackReserve | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x64 | SizeOfStackCommit | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x68 | SizeOfHeapReserve | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x6c | SizeOfHeapCommit | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x70 | LoaderFlags | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x74 | NumberOfRvaAndSizes | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0x8 | MinorLinkerVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0xc | SizeOfCode | `int` |
| InputSystem | 0x0 | _tail_000 | `char[36]` |
| Inventory | 0x0 | m_items | `std::vector<PlayerItem,std::allocator<PlayerItem> >` |
| Inventory | 0x10 | m_curtype | `int` |
| Inventory | 0x14 | m_typeitems | `std::vector<PlayerItem,std::allocator<PlayerItem> >` |
| Inventory | 0x24 | m_money | `int` |
| Iostream_init | 0x0 | _tail_000 | `char[4]` |
| JusticeBookUI | 0x106c | m_Sorcery | `UIStatic[4]` |
| JusticeBookUI | 0x12ec | m_SorceryRc | `tagRECT[4]` |
| JusticeBookUI | 0x132c | m_Remark | `UIStatic` |
| JusticeBookUI | 0x13cc | m_Number | `UIStatic` |
| JusticeBookUI | 0x146c | m_PgUp | `UIButton` |
| JusticeBookUI | 0x15c4 | m_PgDw | `UIButton` |
| JusticeBookUI | 0x168 | m_IsMsg | `unsigned char` |
| JusticeBookUI | 0x169 | m_IsActive | `unsigned char` |
| JusticeBookUI | 0x16a | m_IsExit | `unsigned char` |
| JusticeBookUI | 0x16b | m_IsOpen | `unsigned char` |
| JusticeBookUI | 0x16c | m_BK | `UIStatic` |
| JusticeBookUI | 0x171c | m_tpGods | `UIPushButton` |
| JusticeBookUI | 0x1818 | m_tpImmortal | `UIPushButton` |
| JusticeBookUI | 0x1914 | m_tpGhost | `UIPushButton` |
| JusticeBookUI | 0x1a10 | m_tpDemon | `UIPushButton` |
| JusticeBookUI | 0x1b0c | m_tpHuman | `UIPushButton` |
| JusticeBookUI | 0x1c08 | m_tpMagic | `UIPushButton` |
| JusticeBookUI | 0x1d04 | m_tpGods_unopen | `UIPushButton` |
| JusticeBookUI | 0x1e00 | m_tpImmortal_unopen | `UIPushButton` |
| JusticeBookUI | 0x1efc | m_tpGhost_unopen | `UIPushButton` |
| JusticeBookUI | 0x1ff8 | m_tpDemon_unopen | `UIPushButton` |
| JusticeBookUI | 0x20c | m_Exit | `UIButton` |
| JusticeBookUI | 0x20f4 | m_tpHuman_unopen | `UIPushButton` |
| JusticeBookUI | 0x21f0 | m_tpMagic_unopen | `UIPushButton` |
| JusticeBookUI | 0x22ec | m_allMonsters | `unsigned long *` |
| JusticeBookUI | 0x22f0 | m_MonstersNum | `int` |
| JusticeBookUI | 0x22f4 | m_tpNum | `int[6]` |
| JusticeBookUI | 0x230c | m_tpID | `unsigned long[100][6]` |
| JusticeBookUI | 0x2c6c | m_bookMark | `JB_TYPE` |
| JusticeBookUI | 0x2c70 | m_curMark | `JB_TYPE` |
| JusticeBookUI | 0x2c74 | m_Page | `int` |
| JusticeBookUI | 0x31c8 | m_DialogState | `int` |
| JusticeBookUI | 0x31d0 | m_Dialog | `UIRoleDialog` |
| JusticeBookUI | 0x364 | m_OutFrameT | `UIStatic` |
| JusticeBookUI | 0x372c | m_ParticlesA | `UIParticle[36]` |
| JusticeBookUI | 0x404 | m_OutFrameR | `UIStatic` |
| JusticeBookUI | 0x48 | rc | `tagRECT` |
| JusticeBookUI | 0x4a4 | m_OutFrameL | `UIStatic` |
| JusticeBookUI | 0x544 | m_OutFrameB | `UIStatic` |
| JusticeBookUI | 0x58 | bkWndX | `int` |
| JusticeBookUI | 0x5c | bkWndY | `int` |
| JusticeBookUI | 0x5e4 | m_JusticeBook | `UI3DCtrl` |
| JusticeBookUI | 0x60 | i | `int` |
| JusticeBookUI | 0x64 | j | `int` |
| JusticeBookUI | 0x68 | buf | `char[256]` |
| JusticeBookUI | 0x718 | m_Monster | `UI3DCtrl` |
| JusticeBookUI | 0x84c | m_Name | `UIStatic` |
| JusticeBookUI | 0x894c | m_ParticlesB | `UIParticle[36]` |
| JusticeBookUI | 0x8ec | m_H | `UIStatic` |
| JusticeBookUI | 0x98c | m_S | `UIStatic` |
| JusticeBookUI | 0xa2c | m_Wuling | `UIStatic[5]` |
| JusticeBookUI | 0xd4c | m_Att | `UIStatic[5]` |
| JusticeBookUI | 0xdb7c | m_FadeState | `unsigned char[2]` |
| KeyFrame | 0x0 | emitterAttr | `CParticleSystem::EmitterAttribute` |
| KeyFrame | 0xdc | pPositionPolicy | `CPolicy *` |
| KeyFrame | 0xe0 | pDirectionPolicy | `CPolicy *` |
| KeyFrame | 0xe4 | pColorPolicy | `CPolicy *` |
| KeyFrame | 0xe8 | pAlphaPolicy | `CPolicy *` |
| KeyFrame | 0xec | pFramePolicy | `CPolicy *` |
| KeyFrame | 0xf0 | pEmitterPolicy | `CPolicy *` |
| KeyFrame | 0xf4 | fTime | `float` |
| KeyFrame | 0xf8 | dwReserved | `unsigned int[4]` |
| LARGE_INTEGER | 0x0 | LowPart | `int` |
| LARGE_INTEGER | 0x10 | QuadPart | `__int64` |
| LARGE_INTEGER | 0x4 | HighPart | `int` |
| LARGE_INTEGER | 0x8 | u | `int` |
| LEVELPARAM | 0x0 | nMonster | `int` |
| LEVELPARAM | 0x4 | nSecond | `int` |
| LINEUPINFO | 0x0 | Info | `unsigned char[6]` |
| LINEUP_SEQUENCE | 0x0 | Role_Sequence | `unsigned char[5]` |
| LayerNode | 0x0 | m_bound | `gbAABBox` |
| LayerNode | 0x18 | m_lv | `int` |
| LayerNode | 0x1c | m_tri | `std::vector<Triangle,std::allocator<Triangle> >` |
| LayerNode | 0x2c | m_child | `LayerNode *[4]` |
| LineupComp | 0x110 | m_3DRole | `Object3D[5]` |
| LineupComp | 0x408 | m_isRoleIn | `unsigned char[5]` |
| LineupComp | 0x410 | m_3DNone | `Object3D[6]` |
| LineupComp | 0x78 | m_LineupObj | `Object3D` |
| LineupComp | 0x7a0 | m_is3DNoneIn | `unsigned char[6]` |
| LineupComp | 0x7a8 | m_pCamera | `ObjectCamera *` |
| LineupComp | 0x7ac | m_objCamPitch | `float` |
| LineupComp | 0x7b0 | m_objRotSpeed | `float` |
| LineupComp | 0x7b4 | m_pointerHeight | `float` |
| LineupComp | 0x7b8 | m_isRotLineup | `BYTE` |
| LineupComp | 0x7bc | m_RoleId | `int` |
| LineupComp | 0x7c0 | m_nRole | `int` |
| LineupComp | 0x7c4 | m_bClickRole | `BYTE` |
| LineupPlank | 0x0 | m_Up | `UIStatic` |
| LineupPlank | 0x130 | m_Dw | `UIStatic` |
| LineupPlank | 0x1c8 | m_Btn | `char[256]` |
| LineupPlank | 0x98 | m_Name | `UIStatic` |
| LineupUI | 0x102c | stp_Exit | `UIButton` |
| LineupUI | 0x1184 | stp_Effect | `UIStatic` |
| LineupUI | 0x11c7c | m_btnPar2 | `UIParticle[16][7]` |
| LineupUI | 0x1224 | stp_Rect | `tagRECT` |
| LineupUI | 0x1234 | m_GameTime | `UIStatic` |
| LineupUI | 0x12d4 | m_GameMoney | `UIStatic` |
| LineupUI | 0x1374 | m_DlgEx | `MUIDialog` |
| LineupUI | 0x168 | m_IsMsg | `unsigned char` |
| LineupUI | 0x169 | m_Is | `unsigned char[5]` |
| LineupUI | 0x170 | m_Frame | `UIStatic` |
| LineupUI | 0x18dc | m_ZhenLie | `UIStatic` |
| LineupUI | 0x197c | m_btnPar | `UIParticle[16][7]` |
| LineupUI | 0x210 | m_TimeMoney | `UIStatic` |
| LineupUI | 0x21f7c | m_btnParRc | `tagRECT[7]` |
| LineupUI | 0x21fec | _isParBtn | `unsigned char[7]` |
| LineupUI | 0x21ff4 | _curParEffect | `int` |
| LineupUI | 0x21ff8 | m_LineupInfo | `LINEUPINFO[5]` |
| LineupUI | 0x22016 | m_Sequence | `char[4]` |
| LineupUI | 0x2201c | roleRc | `tagRECT` |
| LineupUI | 0x2202c | m_RoleFrame | `UIStatic` |
| LineupUI | 0x220cc | m_RoleBtn | `UIButton[5]` |
| LineupUI | 0x22784 | m_RoleBtnIndex | `int[5]` |
| LineupUI | 0x22798 | m_NoBody | `UIStatic[5]` |
| LineupUI | 0x22ab8 | m_RoleLeader | `UIStatic[5]` |
| LineupUI | 0x22dd8 | m_headRc | `tagRECT[5]` |
| LineupUI | 0x22e28 | m_headRole | `int` |
| LineupUI | 0x22e2c | m_Msg | `MUIDialog` |
| LineupUI | 0x23394 | m_objCamPitch | `float` |
| LineupUI | 0x23398 | m_objRotSpeed | `float` |
| LineupUI | 0x2339c | m_pCamera | `ObjectCamera *` |
| LineupUI | 0x233a0 | m_pointerHeight | `float` |
| LineupUI | 0x233a4 | m_bPeek | `unsigned char` |
| LineupUI | 0x233a8 | m_nPeek | `int` |
| LineupUI | 0x233ac | m_nLastPeek | `int` |
| LineupUI | 0x233b0 | m_isRotLineup | `unsigned char` |
| LineupUI | 0x233b4 | m_ObjPos | `gbVec3D[6]` |
| LineupUI | 0x233fc | m_LineupObj | `Object3D` |
| LineupUI | 0x23494 | m_3DRole | `Object3D[5]` |
| LineupUI | 0x2378c | m_IsRole | `unsigned char[6]` |
| LineupUI | 0x23794 | m_RoleId | `int[6]` |
| LineupUI | 0x237ac | m_3DNone | `Object3D[6]` |
| LineupUI | 0x23b3c | m_CtrlPlank | `LineupPlank[5]` |
| LineupUI | 0x26224 | m_ProtectPanel | `ProtectPanel` |
| LineupUI | 0x2672c | m_ProFlag | `unsigned char` |
| LineupUI | 0x26730 | pStateUI | `StateUI *` |
| LineupUI | 0x2b0 | m_OutFrameT | `UIStatic` |
| LineupUI | 0x350 | m_OutFrameR | `UIStatic` |
| LineupUI | 0x3f0 | m_OutFrameL | `UIStatic` |
| LineupUI | 0x48 | rc | `tagRECT` |
| LineupUI | 0x490 | m_OutFrameB | `UIStatic` |
| LineupUI | 0x530 | stp_BarL | `UIStatic` |
| LineupUI | 0x58 | bkWndX | `int` |
| LineupUI | 0x5c | bkWndY | `int` |
| LineupUI | 0x5d0 | stp_BarM | `UIFlexBar` |
| LineupUI | 0x60 | i | `int` |
| LineupUI | 0x624 | stp_BarR | `UIStatic` |
| LineupUI | 0x64 | j | `int` |
| LineupUI | 0x68 | buf | `char[256]` |
| LineupUI | 0x6c4 | stp_State | `UIButton` |
| LineupUI | 0x81c | stp_Magic | `UIButton` |
| LineupUI | 0x974 | stp_Equip | `UIButton` |
| LineupUI | 0xacc | stp_Prop | `UIButton` |
| LineupUI | 0xc24 | stp_BattleArray | `UIButton` |
| LineupUI | 0xd7c | stp_TaskBook | `UIButton` |
| LineupUI | 0xed4 | stp_System | `UIButton` |
| LinkerVersion | 0x0 | bverMajor | `BYTE` |
| LinkerVersion | 0x1 | bverMinor | `BYTE` |
| Logger | 0x0 | m_nCallbackCount | `int` |
| Logger | 0x1214 | m_nRenderX | `int` |
| Logger | 0x1218 | m_nRenderY | `int` |
| Logger | 0x121c | m_bRenderEnabled | `int` |
| Logger | 0x1220 | m_pRenderTarget | `void *` |
| Logger | 0x1224 | m_nRenderMode | `int` |
| Logger | 0x1228 | m_nRenderCount | `int` |
| Logger | 0x1294 | m_nRenderState | `int` |
| Logger | 0x12f8 | m_nTodo_12F8 | `void *` |
| Logger | 0x4 | m_callbacks | `tagLoggerCallback[34]` |
| MIXSTAGE | 0x0 | MSS_mixer_flush | `char *` |
| MIXSTAGE | 0x4 | MSS_mixer_merge | `char *` |
| MIXSTAGE | 0x8 | MSS_mixer_copy | `char *` |
| MUIDialog | 0x130 | m_static | `UIStatic` |
| MUIDialog | 0x1d0 | m_text | `UIStatic` |
| MUIDialog | 0x270 | m_btnW | `int` |
| MUIDialog | 0x274 | m_btnH | `int` |
| MUIDialog | 0x48 | ptr_Dlg | `UIWnd *` |
| MUIDialog | 0x4c | m_DlgId | `unsigned int` |
| MUIDialog | 0x50 | m_rect | `tagRECT` |
| MUIDialog | 0x60 | m_textRc | `tagRECT` |
| MUIDialog | 0x70 | m_bk | `UIStaticFlex` |
| MUIDialogMgr | 0x0 | refrence_counter | `int` |
| MU_SortFun | 0x0 | m_by | `int` |
| MXCEft | 0x5c | m_dwEffectID | `DWORD` |
| MXCEft | 0x60 | m_hEffect | `DWORD` |
| MXCEft | 0x64 | m_pos | `gbVec3D` |
| MXCEft | 0x70 | m_fTime | `float` |
| MXFire | 0x5c | m_nCurTex | `int` |
| MXFire | 0x60 | m_fTime | `float` |
| MXFire | 0x64 | m_pEffect | `gbRenderEffect *` |
| MXFire | 0x68 | m_pTexs | `gbTexture *[16]` |
| MXFire | 0xa8 | m_ta | `gbTextureArray` |
| MXFire | 0xec | m_pFlare | `gbTexture *` |
| MXFire | 0xf0 | m_candle | `gbGeomNode *` |
| MXFire | 0xf4 | m_type | `DWORD` |
| MXPoisonFog | 0x5c | m_pfog | `gbParticleEffect *` |
| MXSavePoint | 0x420 | m_stone | `gbGeomNode *` |
| MXSavePoint | 0x5c | m_fTime | `float` |
| MXSavePoint | 0x60 | m_aTex | `gbTextureArray` |
| MXSavePoint | 0xa4 | m_pTex | `gbTexture *` |
| MXSavePoint | 0xa8 | m_pEffect | `gbRenderEffect *` |
| MXSavePoint | 0xac | m_trans | `gbGeomQuad` |
| MXSavePoint | 0xf0 | m_quads | `gbGeomQuad[12]` |
| MXTransport | 0x248 | m_quads2 | `gbGeomQuad[6]` |
| MXTransport | 0x3e0 | m_trans | `gbGeomQuad` |
| MXTransport | 0x424 | m_height | `gbVec2D[4]` |
| MXTransport | 0x444 | m_ok | `int[4]` |
| MXTransport | 0x454 | m_test | `ParticleEffect` |
| MXTransport | 0x5c | m_fTime | `float` |
| MXTransport | 0x60 | m_pTransTex | `gbTexture *` |
| MXTransport | 0x64 | m_aTex | `gbTextureArray` |
| MXTransport | 0xa8 | m_pEffect | `gbRenderEffect *` |
| MXTransport | 0xac | m_pEffectA | `gbRenderEffect *` |
| MXTransport | 0xb0 | m_quads | `gbGeomQuad[6]` |
| MagicUI | 0x118 | m_tabRemarkBuf | `char[256]` |
| MagicUI | 0x1c1cc | m_btnPar2 | `UIParticle[16][7]` |
| MagicUI | 0x218 | s_x | `int` |
| MagicUI | 0x21c | m_IsMsg | `BYTE` |
| MagicUI | 0x21d | m_Is | `unsigned char[5]` |
| MagicUI | 0x224 | m_CtrlRole | `int` |
| MagicUI | 0x228 | m_IsActive | `BYTE` |
| MagicUI | 0x229 | m_IsCreateable | `BYTE` |
| MagicUI | 0x22c | curPage | `int` |
| MagicUI | 0x230 | m_SelNum | `int` |
| MagicUI | 0x234 | m_CurType | `int` |
| MagicUI | 0x238 | m_usemagicRole | `int` |
| MagicUI | 0x23c | m_isuseMagic | `BYTE` |
| MagicUI | 0x23d | m_LockUse | `BYTE` |
| MagicUI | 0x23e | m_IsUsed | `BYTE` |
| MagicUI | 0x23f | m_IsCanUse | `BYTE` |
| MagicUI | 0x240 | m_IsAllUse | `BYTE` |
| MagicUI | 0x244 | pt | `tagPOINT` |
| MagicUI | 0x24c | m_RoleSkill | `SkillData[7][5]` |
| MagicUI | 0x2c4cc | m_btnParRc | `tagRECT[7]` |
| MagicUI | 0x2c53c | _isParBtn | `unsigned char[7]` |
| MagicUI | 0x2c544 | _curParEffect | `int` |
| MagicUI | 0x2c548 | m_CurSelRole | `int` |
| MagicUI | 0x2c54c | m_CurNeedRole | `int` |
| MagicUI | 0x2c550 | m_Dlg | `MUIDialog` |
| MagicUI | 0x2cab8 | m_Msg | `MUIDialog` |
| MagicUI | 0x2d020 | m_DlgMsg | `DLG_MSG` |
| MagicUI | 0x2d024 | m_Animate | `UIAnimate[5]` |
| MagicUI | 0x2d128 | m_AnimateRc | `tagRECT[5]` |
| MagicUI | 0x2d178 | m_ListFrame | `UIStatic` |
| MagicUI | 0x2d210 | m_ListGrid | `UIStatic[8]` |
| MagicUI | 0x2d6d0 | m_RemarkBk | `UIStatic` |
| MagicUI | 0x2d768 | m_Remark | `UIStatic` |
| MagicUI | 0x2d800 | m_RemarkVal | `UIStatic` |
| MagicUI | 0x2d898 | m_UnCom | `UIStatic` |
| MagicUI | 0x2d930 | m_Role | `m_RoleState[5]` |
| MagicUI | 0x32d04 | m_Ctrlbtn | `UIButton[7]` |
| MagicUI | 0x3366c | ml_SpeList | `UIListBox` |
| MagicUI | 0x33b74 | ml_FengList | `UIListBox` |
| MagicUI | 0x3407c | ml_LeiList | `UIListBox` |
| MagicUI | 0x34584 | ml_ShuiList | `UIListBox` |
| MagicUI | 0x34a8c | ml_HuoList | `UIListBox` |
| MagicUI | 0x34f94 | ml_TuList | `UIListBox` |
| MagicUI | 0x3549c | ml_SuangList | `UIListBox` |
| MagicUI | 0x359a4 | m_TopFrame | `UIStatic` |
| MagicUI | 0x35a3c | m_TopFrameXS | `UIStatic` |
| MagicUI | 0x35ad4 | m_parRainbow | `UIParticle[8][5]` |
| MagicUI | 0x3b754 | m_parRise | `UIParticle[8][5]` |
| MagicUI | 0x413d4 | m_parRc | `tagRECT[5]` |
| MagicUI | 0x48 | m_ComSkill | `char[208]` |
| MagicUI | 0xa544 | pStateUI | `StateUI *` |
| MagicUI | 0xa548 | m_Frame | `UIStatic` |
| MagicUI | 0xa5e0 | m_TimeMoney | `UIStatic` |
| MagicUI | 0xa678 | m_OutFrameT | `UIStatic` |
| MagicUI | 0xa710 | m_OutFrameR | `UIStatic` |
| MagicUI | 0xa7a8 | m_OutFrameL | `UIStatic` |
| MagicUI | 0xa840 | m_OutFrameB | `UIStatic` |
| MagicUI | 0xa8d8 | stp_BarL | `UIStatic` |
| MagicUI | 0xa970 | stp_BarM | `UIFlexBar` |
| MagicUI | 0xa9c4 | stp_BarR | `UIStatic` |
| MagicUI | 0xaa5c | stp_State | `UIButton` |
| MagicUI | 0xabb4 | stp_Magic | `UIButton` |
| MagicUI | 0xad0c | stp_Equip | `UIButton` |
| MagicUI | 0xae64 | stp_Prop | `UIButton` |
| MagicUI | 0xafbc | stp_BattleArray | `UIButton` |
| MagicUI | 0xb114 | stp_TaskBook | `UIButton` |
| MagicUI | 0xb26c | stp_System | `UIButton` |
| MagicUI | 0xb3c4 | stp_Exit | `UIButton` |
| MagicUI | 0xb51c | stp_Effect | `UIStatic` |
| MagicUI | 0xb5b4 | stp_Rect | `tagRECT` |
| MagicUI | 0xb5c4 | titleRc | `tagRECT` |
| MagicUI | 0xb5d4 | m_title | `UIStatic[4]` |
| MagicUI | 0xb834 | m_GameTime | `UIStatic` |
| MagicUI | 0xb8cc | m_GameMoney | `UIStatic` |
| MagicUI | 0xb964 | m_DlgEx | `MUIDialog` |
| MagicUI | 0xbecc | m_btnPar | `UIParticle[16][7]` |
| MainEquipUI | 0x10c4 | stp_System | `UIButton` |
| MainEquipUI | 0x11dcc | m_btnPar2 | `UIParticle[16][7]` |
| MainEquipUI | 0x121c | stp_Exit | `UIButton` |
| MainEquipUI | 0x1374 | stp_Effect | `UIStatic` |
| MainEquipUI | 0x1414 | stp_Rect | `tagRECT` |
| MainEquipUI | 0x1424 | m_GameTime | `UIStatic` |
| MainEquipUI | 0x14c4 | m_GameMoney | `UIStatic` |
| MainEquipUI | 0x1564 | m_DlgEx | `MUIDialog` |
| MainEquipUI | 0x168 | m_IsMsg | `unsigned char` |
| MainEquipUI | 0x169 | m_Is | `unsigned char[5]` |
| MainEquipUI | 0x16e | m_IsActive | `unsigned char` |
| MainEquipUI | 0x16f | m_IsCreateable | `unsigned char` |
| MainEquipUI | 0x170 | m_SelNum | `int` |
| MainEquipUI | 0x174 | m_PutOnType | `int` |
| MainEquipUI | 0x178 | m_CurType | `PlayerItem_Type` |
| MainEquipUI | 0x17c | pStateUI | `StateUI *` |
| MainEquipUI | 0x180 | m_Frame | `UIStatic` |
| MainEquipUI | 0x1acc | m_btnPar | `UIParticle[16][7]` |
| MainEquipUI | 0x220 | m_TimeMoney | `UIStatic` |
| MainEquipUI | 0x220cc | m_btnParRc | `tagRECT[7]` |
| MainEquipUI | 0x2213c | _isParBtn | `unsigned char[7]` |
| MainEquipUI | 0x22144 | _curParEffect | `int` |
| MainEquipUI | 0x22148 | me_Role | `me_RoleState[5]` |
| MainEquipUI | 0x2c0 | m_TopFrame | `UIStatic` |
| MainEquipUI | 0x2debc | m_WeaponName | `UIStatic` |
| MainEquipUI | 0x2df5c | m_ClothName | `UIStatic` |
| MainEquipUI | 0x2dffc | m_ShoesName | `UIStatic` |
| MainEquipUI | 0x2e09c | m_HatName | `UIStatic` |
| MainEquipUI | 0x2e13c | m_Adorn1Name | `UIStatic` |
| MainEquipUI | 0x2e1dc | m_Adorn2Name | `UIStatic` |
| MainEquipUI | 0x2e27c | m_RemarkBk | `UIStatic` |
| MainEquipUI | 0x2e31c | m_Remark | `UIStatic` |
| MainEquipUI | 0x2e3bc | m_RemarkVal | `UIStatic` |
| MainEquipUI | 0x2e45c | m_typeWord | `UIStatic` |
| MainEquipUI | 0x2e4fc | m_remarkRc | `tagRECT` |
| MainEquipUI | 0x2e50c | m_role | `RoleAtt[5]` |
| MainEquipUI | 0x2f5b0 | m_Dlg | `MUIDialog` |
| MainEquipUI | 0x2fb18 | m_Ctrlbtn | `UIButton[5]` |
| MainEquipUI | 0x301d0 | m_ClothIcon | `UIStatic` |
| MainEquipUI | 0x30270 | m_HatIcon | `UIStatic` |
| MainEquipUI | 0x30310 | m_ShoesIcon | `UIStatic` |
| MainEquipUI | 0x303b0 | m_WeaponIcon | `UIStatic` |
| MainEquipUI | 0x30450 | m_AdornIcon1 | `UIStatic` |
| MainEquipUI | 0x304f0 | m_AdornIcon2 | `UIStatic` |
| MainEquipUI | 0x30590 | m_SelRc | `tagRECT` |
| MainEquipUI | 0x305a0 | m_SelRole | `UIButton[5]` |
| MainEquipUI | 0x30c58 | m_CurSelRole | `int` |
| MainEquipUI | 0x30c5c | m_ListTitle | `UIFlexBar` |
| MainEquipUI | 0x30cb0 | m_ListFrame | `UIStatic` |
| MainEquipUI | 0x30d50 | m_ListGrid | `UIStatic[14]` |
| MainEquipUI | 0x31610 | m_title | `UIStatic` |
| MainEquipUI | 0x316b0 | ml_Equiplist | `UIListBox` |
| MainEquipUI | 0x31bb8 | last_index | `int` |
| MainEquipUI | 0x31bbc | m_SortRc | `tagRECT` |
| MainEquipUI | 0x31bcc | mb_SortDefault | `UIButton` |
| MainEquipUI | 0x360 | m_TopFrameZB | `UIStatic` |
| MainEquipUI | 0x400 | m_ScrollHB | `UIStatic` |
| MainEquipUI | 0x48 | m_rcLayout | `tagRECT` |
| MainEquipUI | 0x4a0 | m_OutFrameT | `UIStatic` |
| MainEquipUI | 0x540 | m_OutFrameR | `UIStatic` |
| MainEquipUI | 0x58 | m_nBkWndX | `int` |
| MainEquipUI | 0x5c | m_nBkWndY | `int` |
| MainEquipUI | 0x5e0 | m_OutFrameL | `UIStatic` |
| MainEquipUI | 0x60 | m_nListIdx | `int` |
| MainEquipUI | 0x64 | m_nListIdx2 | `int` |
| MainEquipUI | 0x68 | m_szListBuf | `char[256]` |
| MainEquipUI | 0x680 | m_OutFrameB | `UIStatic` |
| MainEquipUI | 0x720 | stp_BarL | `UIStatic` |
| MainEquipUI | 0x7c0 | stp_BarM | `UIFlexBar` |
| MainEquipUI | 0x814 | stp_BarR | `UIStatic` |
| MainEquipUI | 0x8b4 | stp_State | `UIButton` |
| MainEquipUI | 0xa0c | stp_Magic | `UIButton` |
| MainEquipUI | 0xb64 | stp_Equip | `UIButton` |
| MainEquipUI | 0xcbc | stp_Prop | `UIButton` |
| MainEquipUI | 0xe14 | stp_BattleArray | `UIButton` |
| MainEquipUI | 0xf6c | stp_TaskBook | `UIButton` |
| MainPropUI | 0x113c | stp_System | `UIButton` |
| MainPropUI | 0x11e44 | m_btnPar2 | `UIParticle[16][7]` |
| MainPropUI | 0x1294 | stp_Exit | `UIButton` |
| MainPropUI | 0x13ec | stp_Effect | `UIStatic` |
| MainPropUI | 0x148c | stp_Rect | `tagRECT` |
| MainPropUI | 0x149c | m_GameTime | `UIStatic` |
| MainPropUI | 0x153c | m_GameMoney | `UIStatic` |
| MainPropUI | 0x15dc | m_DlgEx | `MUIDialog` |
| MainPropUI | 0x16c | m_tabRemarkBuf | `char[256]` |
| MainPropUI | 0x1b44 | m_btnPar | `UIParticle[16][7]` |
| MainPropUI | 0x22144 | m_btnParRc | `tagRECT[7]` |
| MainPropUI | 0x221b4 | _isParBtn | `unsigned char[7]` |
| MainPropUI | 0x221bc | _curParEffect | `int` |
| MainPropUI | 0x221c0 | m_Dlg | `MUIDialog` |
| MainPropUI | 0x22728 | m_Role | `p_RoleState[5]` |
| MainPropUI | 0x26c | m_IsMsg | `unsigned char` |
| MainPropUI | 0x26d | m_Is | `unsigned char[5]` |
| MainPropUI | 0x274 | m_CurSelRole | `int` |
| MainPropUI | 0x278 | m_CurNeedRole | `int` |
| MainPropUI | 0x27afc | m_RemarkBk | `UIStatic` |
| MainPropUI | 0x27b9c | m_Remark | `UIStatic` |
| MainPropUI | 0x27c | m_IsActive | `unsigned char` |
| MainPropUI | 0x27c3c | m_RemarkVal | `UIStatic` |
| MainPropUI | 0x27cdc | m_RemarkRc | `tagRECT` |
| MainPropUI | 0x27cec | m_typeWord | `UIStatic` |
| MainPropUI | 0x27d | m_IsCreateable | `unsigned char` |
| MainPropUI | 0x27d8c | m_PageBk | `UIStatic` |
| MainPropUI | 0x27e2c | m_Ctrlbtn | `UIButton[5]` |
| MainPropUI | 0x280 | curPage | `int` |
| MainPropUI | 0x284 | curList | `int` |
| MainPropUI | 0x284e4 | m_Pushbtn | `UIPushButton[5]` |
| MainPropUI | 0x288 | m_SelNum | `int` |
| MainPropUI | 0x289d0 | m_Title | `UIStatic` |
| MainPropUI | 0x28a70 | m_ListFrame | `UIStatic` |
| MainPropUI | 0x28b10 | m_ListGrid | `UIStatic[14]` |
| MainPropUI | 0x28c | m_UseNum | `int` |
| MainPropUI | 0x290 | m_LockUse | `unsigned char` |
| MainPropUI | 0x291 | m_IsUsed | `unsigned char` |
| MainPropUI | 0x292 | m_IsCanUse | `unsigned char` |
| MainPropUI | 0x293 | m_IsAllUse | `unsigned char` |
| MainPropUI | 0x293d0 | m_ScrollHB | `UIStatic` |
| MainPropUI | 0x294 | pStateUI | `StateUI *` |
| MainPropUI | 0x29470 | ml_Resume | `UIListBox` |
| MainPropUI | 0x298 | m_Frame | `UIStatic` |
| MainPropUI | 0x29978 | ml_Attack | `UIListBox` |
| MainPropUI | 0x29e80 | ml_Treasure | `UIListBox` |
| MainPropUI | 0x2a388 | ml_Smelt | `UIListBox` |
| MainPropUI | 0x2a890 | ml_Special | `UIListBox` |
| MainPropUI | 0x2ad98 | m_Animate | `UIAnimate[5]` |
| MainPropUI | 0x2ae9c | m_AnimateRc | `tagRECT[5]` |
| MainPropUI | 0x2aeec | m_SortRc | `tagRECT` |
| MainPropUI | 0x2aefc | mb_SortDefault | `UIButton` |
| MainPropUI | 0x2b054 | mb_SortPrice | `UIButton` |
| MainPropUI | 0x2b1ac | mb_SortUse | `UIButton` |
| MainPropUI | 0x2b304 | m_SortState | `int` |
| MainPropUI | 0x2b308 | m_3DObj | `UI3DCtrl` |
| MainPropUI | 0x2b43c | m_parSingle | `UIParticle[12][5]` |
| MainPropUI | 0x338 | m_TimeMoney | `UIStatic` |
| MainPropUI | 0x3d8 | m_TopFrame | `UIStatic` |
| MainPropUI | 0x478 | m_TopFrameWP | `UIStatic` |
| MainPropUI | 0x48 | rc | `tagRECT` |
| MainPropUI | 0x518 | m_OutFrameT | `UIStatic` |
| MainPropUI | 0x58 | m_nBkWndX | `int` |
| MainPropUI | 0x5b8 | m_OutFrameR | `UIStatic` |
| MainPropUI | 0x5c | m_nBkWndY | `int` |
| MainPropUI | 0x60 | m_nListIdx | `int` |
| MainPropUI | 0x64 | j | `int` |
| MainPropUI | 0x658 | m_OutFrameL | `UIStatic` |
| MainPropUI | 0x68 | m_szListBuf | `char[256]` |
| MainPropUI | 0x6c | buf | `char[256]` |
| MainPropUI | 0x6f8 | m_OutFrameB | `UIStatic` |
| MainPropUI | 0x798 | stp_BarL | `UIStatic` |
| MainPropUI | 0x838 | stp_BarM | `UIFlexBar` |
| MainPropUI | 0x88c | stp_BarR | `UIStatic` |
| MainPropUI | 0x92c | stp_State | `UIButton` |
| MainPropUI | 0xa84 | stp_Magic | `UIButton` |
| MainPropUI | 0xbdc | stp_Equip | `UIButton` |
| MainPropUI | 0xd34 | stp_Prop | `UIButton` |
| MainPropUI | 0xe8c | stp_BattleArray | `UIButton` |
| MainPropUI | 0xfe4 | stp_TaskBook | `UIButton` |
| Math | 0x0 | _tail_000 | `char[4]` |
| Matrix4 | 0x0 | m | `float[4][4]` |
| MatrixStack | 0x0 | _tail_000 | `char[4]` |
| MeshFx | 0x58 | m_iCurrentState | `int` |
| MeshFxCreator | 0x0 | _tail_000 | `char[4]` |
| MiniGame1 | 0x0 | _tail_000 | `char[4]` |
| MiniGame2Scene | 0x0 | _tail_000 | `char[4]` |
| MiniGame3 | 0x0 | _tail_000 | `char[4]` |
| MonsterStar | 0x0 | needexp | `int` |
| MonsterStar | 0x4 | active | `int` |
| MonsterStar | 0x8 | exp | `int` |
| MonsterStar | 0xc | item | `DWORD` |
| MvcController | 0x0 | _tail_000 | `char[4]` |
| MvcViewport | 0x0 | _tail_000 | `char[4]` |
| MyMdl | 0x0 | m_mdltype | `int` |
| MyMdl | 0x4 | m_fx | `MeshFx *` |
| MyMdl | 0x8 | box | `gbOBBox` |
| NGHHURT | 0x0 | AlphaSpeed | `float` |
| NGHHURT | 0x10 | nHurtState | `int` |
| NGHHURT | 0x4 | bFlashState | `BYTE` |
| NGHHURT | 0x5 | bNeedFlash | `BYTE` |
| NGHHURT | 0x8 | fTimeCounter | `float` |
| NGHHURT | 0xc | nWaitSecond | `int` |
| NMHDR | 0x0 | hwndFrom | `HWND__ *` |
| NMHDR | 0x4 | idFrom | `UINT` |
| NMHDR | 0x8 | code | `UINT` |
| NPC | 0x124 | m_wndHPBar | `UIWnd *` |
| NPC | 0x138 | m_WndContainer | `UIWnd` |
| NPC | 0x218 | m_wndNameLabel | `int` |
| NPC | 0x22c | m_AnimWndA | `UIWnd` |
| NPC | 0x24 | m_nTodo_024 | `int` |
| NPC | 0x2b0 | m_wndDialog | `NPC *` |
| NPC | 0x2c4 | m_AnimWndB | `UIWnd` |
| NPC | 0x30 | m_nTodo_30 | `int` |
| NPC | 0x348 | m_wndTooltip | `NPC *` |
| NPC | 0x35c | m_AnimWndC | `UIWnd` |
| NPC | 0x38 | m_pConditionA | `int` |
| NPC | 0x3c | m_pConditionB | `void*` |
| NPC | 0x4 | m_pBuffer | `char *` |
| NPC | 0x44 | m_wndBase | `UIWnd` |
| NPC | 0x478 | m_fAnimTimer | `float` |
| NPC | 0x47c | m_bAnimActive | `int` |
| NPC | 0x8 | m_nBufStart | `int` |
| NPC | 0xc | m_nBufEnd | `int` |
| NPC | 0xe0 | m_nTodo_0E0 | `int` |
| NPCInfo | 0x0 | id | `BYTE` |
| NPCInfo | 0x1 | kind | `BYTE` |
| NPCInfo | 0x148 | noturn | `DWORD` |
| NPCInfo | 0x14c | loopact | `DWORD` |
| NPCInfo | 0x150 | speed | `DWORD` |
| NPCInfo | 0x154 | reserve | `unsigned int[29]` |
| NPCInfo | 0x2 | name | `char[32]` |
| NPCInfo | 0x22 | mtl | `char[32]` |
| NPCInfo | 0x44 | face | `float` |
| NPCInfo | 0x48 | onlayer | `BYTE` |
| NPCInfo | 0x4c | x | `float` |
| NPCInfo | 0x50 | z | `float` |
| NPCInfo | 0x54 | initactive | `BYTE` |
| NPCInfo | 0x58 | initbeh | `ROLE_BEHAVIOUR` |
| NPCInfo | 0x5c | scriptid | `DWORD` |
| NPCInfo | 0x60 | y | `float` |
| NPCInfo | 0x64 | initact | `char[16]` |
| NPCInfo | 0x74 | mid | `unsigned int[3]` |
| NPCInfo | 0x80 | mnum | `BYTE` |
| NPCInfo | 0x81 | mrepeat | `BYTE` |
| NPCInfo | 0x84 | path | `PolyLine` |
| NameSys | 0x0 | m_Flag | `char[8]` |
| NameSys | 0x114 | m_LastName | `NameSys_NAMEFLAG` |
| NameSys | 0x7c | m_RefMax | `int[28]` |
| NameSys | 0x8 | m_FlagZZCC | `char[4]` |
| NameSys | 0xc | m_Ref | `int[28]` |
| NameSys | 0xec | m_CheckMax | `unsigned int[10]` |
| NameSys_NAMEFLAG | 0x0 | _tail_000 | `char[4]` |
| NavFace | 0x0 | index | `unsigned short[3]` |
| NavFaceLayer | 0x0 | numvert | `WORD` |
| NavFaceLayer | 0x2 | numface | `WORD` |
| NavFaceLayer | 0x4 | vertbuf | `gbVec3D *` |
| NavFaceLayer | 0x8 | face | `NavFace *` |
| NavFaceLayer | 0xc | node | `LayerNode *` |
| NavHeader | 0x0 | magic | `unsigned char[4]` |
| NavHeader | 0x4 | version | `BYTE` |
| NavHeader | 0x5 | numlayer | `BYTE` |
| NavHeader | 0x6 | offsettile | `char[2]` |
| NavHeader | 0xa | offsetface | `char[2]` |
| NavTile | 0x0 | y | `float` |
| NavTile | 0x4 | dist | `BYTE` |
| NavTile | 0x5 | floor | `BYTE` |
| NavTileLayer | 0x0 | portal | `tagRECT[8]` |
| NavTileLayer | 0x80 | min | `gbVec3D` |
| NavTileLayer | 0x8c | max | `gbVec3D` |
| NavTileLayer | 0x98 | width | `int` |
| NavTileLayer | 0x9c | height | `int` |
| NavTileLayer | 0xa0 | tile | `NavTile *` |
| NavTriangle | 0x0 | up | `gbVec3D` |
| NavTriangle | 0x18 | side | `gbVec3D` |
| NavTriangle | 0xc | forward | `gbVec3D` |
| NavigationInfo | 0x0 | m_numlayer | `int` |
| NavigationInfo | 0x14c | m_facelayer | `NavFaceLayer[2]` |
| NavigationInfo | 0x4 | m_tilelayer | `NavTileLayer[2]` |
| Note_Item | 0x0 | m_ItemRc | `tagRECT` |
| Note_Item | 0x10 | m_NoteItemBk | `UIButton` |
| Note_Item | 0x168 | m_NoteID | `UIStatic` |
| Note_Item | 0x200 | m_NoteState | `UIStatic` |
| Note_Item | 0x298 | m_HeadShot_NO_SEL | `UIStatic[5]` |
| Note_Item | 0x590 | m_HeadShot | `UIStatic[5]` |
| Note_Item | 0x888 | m_isHead | `unsigned char[5]` |
| Note_Item | 0x890 | m_NoteTime | `UIStatic` |
| Note_Item | 0x928 | m_NoteMoney | `UIStatic` |
| Note_Item | 0x9c0 | m_NoteLv | `UIStatic[5]` |
| Note_Item | 0xcb8 | m_NotePic | `UIStatic` |
| Note_Item | 0xd50 | m_NotePicName | `UIStatic` |
| OBJHELPER | 0x0 | bValid | `BYTE` |
| OBJHELPER | 0x18 | pGroundPt | `tagPOINT` |
| OBJHELPER | 0x20 | nEffRunID | `int` |
| OBJHELPER | 0x24 | vEffPos | `gbVec3D` |
| OBJHELPER | 0x4 | nType | `int` |
| OBJHELPER | 0x8 | rTouchArea | `tagRECT` |
| ORect | 0x0 | m_pt | `tagPOINT[4]` |
| ORect | 0x20 | m_numpt | `int` |
| ObjLockInput | 0x0 | m_objs | `PtrArray` |
| ObjLockInput | 0x10 | m_scripts | `PtrArray` |
| ObjLockInput | 0x20 | m_scriptabs | `PtrArray` |
| ObjParam | 0x0 | ID | `DWORD` |
| ObjParam | 0x28 | Price | `int` |
| ObjParam | 0x2c | Touch | `int` |
| ObjParam | 0x30 | Radius | `float` |
| ObjParam | 0x34 | Value | `int` |
| ObjParam | 0x38 | Speed | `float` |
| ObjParam | 0x3c | Accelerate | `float` |
| ObjParam | 0x4 | Type | `int` |
| ObjParam | 0x40 | Shelf | `char[64]` |
| ObjParam | 0x8 | name | `char[32]` |
| ObjParam | 0x80 | Model | `char[64]` |
| ObjParam | 0xc0 | EffID | `DWORD` |
| ObjParam | 0xc4 | Remark | `char[256]` |
| Object | 0x10 | radius | `float` |
| Object | 0x14 | forward | `gbVec3D` |
| Object | 0x20 | side | `gbVec3D` |
| Object | 0x2c | up | `gbVec3D` |
| Object | 0x4 | position | `gbVec3D` |
| Object3D | 0x0 | m_isLoadObj | `unsigned char` |
| Object3D | 0x10 | m_subType | `unsigned int` |
| Object3D | 0x14 | m_isLoadSubObj | `unsigned char` |
| Object3D | 0x15 | m_showSubObj | `unsigned char` |
| Object3D | 0x18 | m_subObjHeight | `float` |
| Object3D | 0x1c | m_height | `float` |
| Object3D | 0x20 | m_position | `gbVec3D` |
| Object3D | 0x2c | RelativePos | `gbVec3D` |
| Object3D | 0x38 | m_roty | `float` |
| Object3D | 0x3c | m_rotx | `float` |
| Object3D | 0x4 | m_type | `unsigned int` |
| Object3D | 0x40 | m_rotz | `float` |
| Object3D | 0x44 | m_dropx | `float` |
| Object3D | 0x48 | m_dropy | `float` |
| Object3D | 0x4c | m_dropz | `float` |
| Object3D | 0x50 | m_visible | `unsigned char` |
| Object3D | 0x54 | m_pCamera | `ObjectCamera *` |
| Object3D | 0x58 | m_yaw | `float` |
| Object3D | 0x5c | m_pitch | `float` |
| Object3D | 0x60 | m_roll | `float` |
| Object3D | 0x64 | m_dist | `float` |
| Object3D | 0x68 | m_forward | `gbVec3D` |
| Object3D | 0x74 | m_degreeToScreen | `float` |
| Object3D | 0x78 | m_isActionRelativeRot | `unsigned char` |
| Object3D | 0x79 | m_bRotDstDegree | `unsigned char` |
| Object3D | 0x7c | m_rotRelative | `float` |
| Object3D | 0x8 | m_pol | `gbGeomNode *` |
| Object3D | 0x80 | m_rotDegree | `float` |
| Object3D | 0x84 | m_rotDstDegree | `float` |
| Object3D | 0x88 | m_rotDstSpeed | `float` |
| Object3D | 0x8c | m_rotDstDir | `int` |
| Object3D | 0x90 | m_rotDstMode | `int` |
| Object3D | 0x94 | m_action | `int` |
| Object3D | 0xc | m_subObj | `gbGeomNode *` |
| ObjectCamera | 0x0 | m_pCamera | `gbCamera *` |
| ObjectCamera | 0x10 | m_camTo | `gbVec3D` |
| ObjectCamera | 0x1c | m_camUp | `gbVec3D` |
| ObjectCamera | 0x28 | m_camDirect | `gbVec3D` |
| ObjectCamera | 0x34 | m_yaw | `float` |
| ObjectCamera | 0x38 | m_pitch | `float` |
| ObjectCamera | 0x3c | m_roll | `float` |
| ObjectCamera | 0x4 | m_camFrom | `gbVec3D` |
| ObjectCamera | 0x40 | m_dist | `float` |
| ObjectCamera | 0x44 | m_nyaw | `float` |
| ObjectCamera | 0x48 | m_npitch | `float` |
| ObjectCamera | 0x4c | m_nroll | `float` |
| ObjectCamera | 0x50 | m_forward | `gbVec3D` |
| ObjectCamera | 0x5c | m_side | `gbVec3D` |
| ObjectCamera | 0x68 | m_stepRotSpeed | `float` |
| ObjectCamera | 0x6c | m_stepRot | `int` |
| ObjectCamera | 0x70 | m_stepRotMode | `int` |
| ObjectCamera | 0x74 | m_stepRotAxis | `short` |
| ObjectCamera | 0x78 | m_bStepRot | `BYTE` |
| ObjectInfo | 0x150 | linkobj | `WORD` |
| ObjectInfo | 0x152 | depend_scenename | `char[32]` |
| ObjectInfo | 0x172 | depend_id | `BYTE` |
| ObjectInfo | 0x174 | box | `gbAABBox` |
| ObjectInfo | 0x18c | rotateX | `float` |
| ObjectInfo | 0x190 | rotateZ | `float` |
| ObjectInfo | 0x194 | snd | `unsigned char[8]` |
| ObjectInfo | 0x19c | effect | `DWORD` |
| ObjectInfo | 0x1a0 | bScriptChangeActive | `DWORD` |
| ObjectInfo | 0x1a4 | bScriptMoved | `DWORD` |
| ObjectInfo | 0x1a8 | bCalculateExp | `BYTE` |
| ObjectInfo | 0x1ac | reserve | `unsigned int[44]` |
| ObjectInfo | 0x24 | ctype | `BYTE` |
| ObjectInfo | 0x25 | cango | `BYTE` |
| ObjectInfo | 0x28 | pos | `gbVec3D` |
| ObjectInfo | 0x34 | rotate | `float` |
| ObjectInfo | 0x38 | rect | `tagRECT` |
| ObjectInfo | 0x4 | name | `char[32]` |
| ObjectInfo | 0x48 | type | `BYTE` |
| ObjectInfo | 0x49 | savestate | `BYTE` |
| ObjectInfo | 0x4a | onlayer | `BYTE` |
| ObjectInfo | 0x4b | wuling | `BYTE` |
| ObjectInfo | 0x4c | param | `float[6]` |
| ObjectInfo | 0x64 | needspecalact | `BYTE` |
| ObjectInfo | 0x66 | needitem | `WORD` |
| ObjectInfo | 0x68 | needgold | `WORD` |
| ObjectInfo | 0x6a | needlv | `WORD` |
| ObjectInfo | 0x6c | needwu | `WORD` |
| ObjectInfo | 0x6e | needallopen | `BYTE` |
| ObjectInfo | 0x6f | failed | `char[16]` |
| ObjectInfo | 0x80 | dwNeedItem | `DWORD` |
| ObjectInfo | 0x84 | groupid | `BYTE` |
| ObjectInfo | 0x88 | scriptid | `DWORD` |
| ObjectInfo | 0x8c | path | `PolyLine` |
| ObjectInfoBase | 0x0 | id | `BYTE` |
| ObjectInfoBase | 0x1 | active | `BYTE` |
| ObjectInfoBase | 0x2 | times | `BYTE` |
| ObjectInfoBase | 0x3 | siwtch | `BYTE` |
| OpenBaseFile | 0x0 | m_plastsys | `gbVFileSystem *` |
| OpenFNWindow | 0x0 | fWaitTime | `float` |
| OpenFNWindow | 0x4 | bOpen | `BYTE` |
| OpenFNWindow | 0x8 | nOpenFlag | `int` |
| OpenNULLFile | 0x0 | m_plastsys | `gbVFileSystem *` |
| OpenSceneFile | 0x0 | _tail_000 | `char[4]` |
| OutFile | 0x0 | str | `char[128]` |
| OutFile | 0x80 | RolePos | `DWORD` |
| OutFile | 0x84 | RoleNum | `int` |
| OutFile | 0x88 | SkillPos | `DWORD` |
| OutFile | 0x8c | SkillNum | `int` |
| OutFile | 0x90 | ItemPos | `DWORD` |
| OutFile | 0x94 | ItemNum | `int` |
| OutFile | 0x98 | ComboPos | `DWORD` |
| OutFile | 0x9c | ComboNum | `int` |
| PAL3 | 0x0 | m_snaph | `float` |
| PAL3 | 0x140 | m_nTodo_140 | `_DWORD[4]` |
| PAL3 | 0x150 | m_nTodo_150 | `_DWORD[4]` |
| PAL3 | 0x19c | s_gamestate | `int` |
| PAL3 | 0x1a0 | m_pCmdLine | `char *` |
| PAL3 | 0x1a4 | m_bTestCombat | `int` |
| PAL3 | 0x1a8 | m_bCombatWin | `int` |
| PAL3 | 0x1ac | m_bLoadMainUI | `int` |
| PAL3 | 0x1b0 | m_bShowRenderInfo | `int` |
| PAL3 | 0x1b4 | m_bSoftCursor | `int` |
| PAL3 | 0x1b8 | m_bNGHVariance | `int` |
| PAL3 | 0x1bc | m_bWPXVariance | `int` |
| PAL3 | 0x1c0 | m_gametime | `double` |
| PAL3 | 0x20 | m_Image2D | `gbImage2D` |
| PAL3 | 0x4 | m_pScnFrameTex | `gbTexture *` |
| PAL3 | 0x6a0 | m_nTodo_6A0 | `int` |
| PAL3 | 0x6a8 | m_nTodo_6A8 | `int` |
| PAL3 | 0x6ac | m_nTodo_6AC | `int` |
| PAL3 | 0x6b0 | m_nTodo_6B0 | `int` |
| PAL3 | 0x6c8 | m_nTodo_6C8 | `int` |
| PAL3 | 0x6d0 | m_nTodo_6D0 | `int` |
| PAL3 | 0x6d4 | m_nTodo_6D4 | `int` |
| PAL3 | 0x6d8 | m_nTodo_6D8 | `int` |
| PAL3 | 0x8 | m_pAdditiveEffect | `gbRenderEffect *` |
| PAL3 | 0x864 | m_nTodo_864 | `int` |
| PAL3 | 0x868 | m_nTodo_868 | `int` |
| PAL3 | 0x86c | m_nTodo_86C | `int` |
| PAL3 | 0x88c | m_nTodo_88C | `gbTexture *` |
| PAL3 | 0x890 | m_nTodo_890 | `int` |
| PAL3 | 0x894 | m_nTodo_894 | `int` |
| PAL3 | 0xc | m_pAdditiveEffect2 | `gbRenderEffect *` |
| PAL3 | 0xca0 | m_nTodo_CA0 | `int` |
| PAL3 | 0xca4 | m_nTodo_CA4 | `int` |
| PAL3 | 0xca8 | m_nTodo_CA8 | `int` |
| PAL3 | 0xcc8 | m_pDeviceTex | `gbTexture *` |
| PAL3 | 0xccc | m_nTodo_CCC | `int` |
| PAL3 | 0xcd0 | m_nTodo_CD0 | `int` |
| PAL3 | 0xf6c | m_nTodo_F6C | `int` |
| PAL3 | 0xf70 | m_nTodo_F70 | `int` |
| PAL3 | 0xf74 | m_nTodo_F74 | `int` |
| PAL3 | 0xf94 | m_nTodo_F94 | `gbTexture *` |
| PAL3 | 0xf98 | m_nTodo_F98 | `int` |
| PAL3 | 0xf9c | m_nTodo_F9C | `int` |
| PAL_GDB | 0x0 | m_head | `OutFile` |
| PAL_GDB | 0x29a40 | m_SkillData | `FightSkill[300]` |
| PAL_GDB | 0x614e0 | m_ItemData | `FightItem[512]` |
| PAL_GDB | 0xa0 | m_RoleData | `RoleAtt[200]` |
| PAL_GDB | 0xc54e0 | m_ComboData | `ComboAttack[10]` |
| PAL_GDB | 0xc6db8 | i | `int` |
| PARTICLEVERTEX | 0x0 | FVF | `DWORD` |
| PARTICLEVERTEX | 0x10 | tu | `float` |
| PARTICLEVERTEX | 0x14 | tv | `float` |
| PARTICLEVERTEX | 0xc | color | `DWORD` |
| PMD | 0x0 | mdisp | `int` |
| PMD | 0x4 | pdisp | `int` |
| PMD | 0x8 | vdisp | `int` |
| PMFN | 0x0 | pfn | `int` |
| PalScript | 0x100 | m_nUpdateState | `int` |
| PalScript | 0x114 | m_fRenderScaleX | `float` |
| PalScript | 0x118 | m_fScaleY | `float` |
| PalScript | 0x11c | m_fScaleZ | `float` |
| PalScript | 0x124 | m_fInterval | `float` |
| PalScript | 0x128 | m_fElapsed | `float` |
| PalScript | 0x138 | m_nTodo_138 | `int` |
| PalScript | 0x14c | m_nScriptCount | `int` |
| PalScript | 0x160 | m_EncampConfig | `int` |
| PalScript | 0x170 | m_nRepeatCount | `int` |
| PalScript | 0x174 | m_nMaxRepeats | `int` |
| PalScript | 0x178 | m_nCycleCount | `int` |
| PalScript | 0x17c | m_nMaxCycles | `int` |
| PalScript | 0x44 | m_fTimerLimit | `float` |
| PalScript | 0x48 | m_fTimerAccum | `float` |
| PalScript | 0x4c | m_nTodo_04C | `_BYTE[68]` |
| PalScript | 0x510 | m_nTodo_510 | `int` |
| PalScript | 0x614 | m_szDialog2 | `char[256]` |
| PalScript | 0x714 | m_DialogSub | `unsigned char` |
| PalScript | 0x728 | _todo_730 | `float` |
| PalScript | 0x734 | m_fSceneTileSize | `float` |
| PalScript | 0x764 | _todo_764 | `int` |
| PalScript | 0x768 | _todo_768 | `int` |
| PalScript | 0x94 | m_pTaskPtr | `void*` |
| PalScript | 0x98 | m_nTimerCount | `int` |
| PalScript | 0x9c | m_nWaitTimer | `int` |
| PalScript | 0xa0 | m_nAnimState | `int` |
| PalScript | 0xa4 | m_nSnowParticles | `int` |
| PalScript | 0xa8 | m_nItemCheck | `int` |
| PalScript | 0xb0 | m_RoleEmoteData | `int` |
| PalScript | 0xc4 | m_pTexture | `gbTexture *` |
| PalScript | 0xc8 | m_pTextureInfo | `_PlugInfo *` |
| PalScript | 0xd4 | m_RoleEmoteSub | `int` |
| PalScript | 0xd8 | m_nTodo_0D8 | `int` |
| PalScript | 0xdc | m_nRoleCount | `int` |
| PalScript | 0xec | m_nScriptState | `int` |
| PalScript | 0xf0 | m_bCamActive | `unsigned char` |
| PalScript | 0xf4 | m_bSoundType | `unsigned char` |
| PalScript | 0xf8 | m_fCamScale | `float` |
| PalScript | 0xfc | m_fScaleX | `float` |
| PalScriptAnimTimer | 0x8 | m_fTime | `float` |
| PalScriptAnimTimer | 0xc | m_bDone | `char` |
| PalScriptBlendTimer | 0x8 | m_fElapsed | `float` |
| PalScriptBlendTimer | 0xc | m_fDuration | `float` |
| PalScriptFadeInTimer | 0x10 | m_bDone | `char` |
| PalScriptFadeInTimer | 0x8 | m_fElapsed | `float` |
| PalScriptFadeOutTimer | 0x10 | m_bDone | `char` |
| PalScriptFadeOutTimer | 0x8 | m_fElapsed | `float` |
| PalScriptIdleObj | 0x8 | m_nTodo_008 | `int` |
| PalScriptIdleObj | 0xc | m_passedtime | `float` |
| PalScriptMgr | 0x100 | m_nCmdParam0 | `short` |
| PalScriptMgr | 0x104 | m_nCmdParam1 | `short` |
| PalScriptMgr | 0x108 | m_nCmdParam2 | `int` |
| PalScriptMgr | 0x10c | m_nExecCounter | `int` |
| PalScriptMgr | 0x110 | m_pRoleSystemCache | `RoleSystem *` |
| PalScriptMgr | 0x114 | m_wRoleField114 | `unsigned short` |
| PalScriptMgr | 0x116 | m_wRoleField116 | `unsigned short` |
| PalScriptMgr | 0x118 | m_Actor | `short` |
| PalScriptMgr | 0x11a | m_bRoleField11A | `unsigned char` |
| PalScriptMgr | 0x11c | m_nField_0118 | `short` |
| PalScriptMgr | 0x11cc | m_nTileFlags | `int` |
| PalScriptMgr | 0x11d0 | m_fTileHeight | `float` |
| PalScriptMgr | 0x11e | m_nTodo_11A | `unsigned char` |
| PalScriptMgr | 0x120 | m_nTodo_11C | `int` |
| PalScriptMgr | 0x128 | m_pTodo_128 | `char *` |
| PalScriptMgr | 0x12c | m_nScriptCount | `int` |
| PalScriptMgr | 0x130 | m_pScriptObjAux | `PalScriptMgr *` |
| PalScriptMgr | 0x134 | m_nScriptDepth | `int` |
| PalScriptMgr | 0x138 | m_fPrevPosX | `float` |
| PalScriptMgr | 0x13b0 | m_nField_13AC | `int` |
| PalScriptMgr | 0x13c | m_fPrevPosY | `float` |
| PalScriptMgr | 0x140 | m_nExecuteOpcode | `int` |
| PalScriptMgr | 0x144 | m_fExecuteBlock | `float` |
| PalScriptMgr | 0x146c | m_nField_1468 | `int` |
| PalScriptMgr | 0x148 | m_fCurPosY | `float` |
| PalScriptMgr | 0x1494 | m_nField_1490 | `int` |
| PalScriptMgr | 0x14c | m_fAnimSpeed | `float` |
| PalScriptMgr | 0x1568 | m_nField_1564 | `int` |
| PalScriptMgr | 0x1600 | m_nField_15FC | `int` |
| PalScriptMgr | 0x162c | m_nField_1628 | `int` |
| PalScriptMgr | 0x16c | m_nField_0168 | `int` |
| PalScriptMgr | 0x170 | m_RolePos | `int` |
| PalScriptMgr | 0x17c | m_RoleDir | `int` |
| PalScriptMgr | 0x18 | m_scefile | `scSCEFile *` |
| PalScriptMgr | 0x188 | m_nRoleState | `int` |
| PalScriptMgr | 0x18c | m_RoleSubData | `int` |
| PalScriptMgr | 0x194 | m_nRoleParam1 | `int` |
| PalScriptMgr | 0x198 | m_nRoleParam2 | `int` |
| PalScriptMgr | 0x19c | m_nRoleParam3 | `int` |
| PalScriptMgr | 0x1a0 | m_pRoleScript | `void *` |
| PalScriptMgr | 0x1a8 | m_nField_01A4 | `int` |
| PalScriptMgr | 0x1b14 | m_nField_1B10 | `int` |
| PalScriptMgr | 0x1b64 | m_nField_1B60 | `int` |
| PalScriptMgr | 0x1c | m_fPopA | `float` |
| PalScriptMgr | 0x1c10 | m_nField_1C0C | `int` |
| PalScriptMgr | 0x1c4 | m_pOpResult | `void *` |
| PalScriptMgr | 0x1d8 | m_bTileType | `unsigned char` |
| PalScriptMgr | 0x1d98 | m_nField_1D94 | `int` |
| PalScriptMgr | 0x1f0 | m_fSpeed1 | `float` |
| PalScriptMgr | 0x1f4 | m_fSpeed2 | `float` |
| PalScriptMgr | 0x1f8 | m_nScriptID | `short` |
| PalScriptMgr | 0x20 | m_fPopB | `float` |
| PalScriptMgr | 0x2108 | m_nCost | `int` |
| PalScriptMgr | 0x2110 | m_nCapacity | `int` |
| PalScriptMgr | 0x212 | m_nRoleIndex | `short` |
| PalScriptMgr | 0x214 | m_ScriptRoleState | `int` |
| PalScriptMgr | 0x21a | m_bScriptByte | `unsigned char` |
| PalScriptMgr | 0x21c | m_fPosAX | `float` |
| PalScriptMgr | 0x21f8 | m_fFrameTime | `float` |
| PalScriptMgr | 0x21fc | m_fFrameDelta | `float` |
| PalScriptMgr | 0x220 | m_fPosAY | `float` |
| PalScriptMgr | 0x2200 | m_fFrameTotal | `float` |
| PalScriptMgr | 0x224 | m_fPosAZ | `float` |
| PalScriptMgr | 0x228 | m_fPosBX | `float` |
| PalScriptMgr | 0x22c | m_fPosBY | `float` |
| PalScriptMgr | 0x230 | m_fPosBZ | `float` |
| PalScriptMgr | 0x234 | m_nMatrixData | `int` |
| PalScriptMgr | 0x238 | m_bRunCommand | `unsigned char` |
| PalScriptMgr | 0x23c | m_nRoleField23C | `int` |
| PalScriptMgr | 0x24 | m_pPopScript | `void *` |
| PalScriptMgr | 0x240 | m_bScriptInputBlock | `int` |
| PalScriptMgr | 0x244 | m_bInputBlock | `int` |
| PalScriptMgr | 0x248 | m_bRoleLock | `int` |
| PalScriptMgr | 0x250c | m_pTodo_250C | `char *` |
| PalScriptMgr | 0x2510 | m_pTodo_2510 | `char *` |
| PalScriptMgr | 0x2514 | m_pScriptInstA | `char *` |
| PalScriptMgr | 0x2518 | m_pScriptInstD | `PalScriptMgr *` |
| PalScriptMgr | 0x251c | m_pScriptInstE | `char *` |
| PalScriptMgr | 0x2520 | m_nScriptResultA | `int` |
| PalScriptMgr | 0x2524 | m_nScriptResultB | `int` |
| PalScriptMgr | 0x2528 | m_nScriptResultC | `int` |
| PalScriptMgr | 0x278 | m_pCaseTable | `void *` |
| PalScriptMgr | 0x27c | m_nTodo_278 | `int` |
| PalScriptMgr | 0x28 | m_nTodo_024 | `int` |
| PalScriptMgr | 0x2c | m_fCamX | `float` |
| PalScriptMgr | 0x30 | m_fCamY | `float` |
| PalScriptMgr | 0x318 | m_pTodo_318 | `char *` |
| PalScriptMgr | 0x31c | m_nBlockHandle | `int` |
| PalScriptMgr | 0x320 | m_pSceneMgr | `RoleSystem *` |
| PalScriptMgr | 0x324 | m_bRoleCmd | `unsigned char` |
| PalScriptMgr | 0x328 | m_nExecState | `int` |
| PalScriptMgr | 0x32c | m_pCmdBuffer | `char *` |
| PalScriptMgr | 0x330 | m_nLoopCountA | `int` |
| PalScriptMgr | 0x334 | m_nLoopCountB | `int` |
| PalScriptMgr | 0x338 | m_nLoopCountC | `int` |
| PalScriptMgr | 0x33c | m_nSavedPosX | `int` |
| PalScriptMgr | 0x34 | m_fCamZ | `float` |
| PalScriptMgr | 0x340 | m_pSubScriptB | `PalScriptMgr *` |
| PalScriptMgr | 0x344 | m_nScriptCamX | `int` |
| PalScriptMgr | 0x348 | m_nScriptCamY | `int` |
| PalScriptMgr | 0x34c | m_pScriptBlock | `char *` |
| PalScriptMgr | 0x350 | m_pExecObj | `char *` |
| PalScriptMgr | 0x354 | m_fExecParam | `float` |
| PalScriptMgr | 0x358 | m_fExecPosY | `float` |
| PalScriptMgr | 0x35c | m_fExecPosZ | `float` |
| PalScriptMgr | 0x360 | m_nExecState2 | `int` |
| PalScriptMgr | 0x364 | m_pWaitObj | `char *` |
| PalScriptMgr | 0x36c | m_nWaitCount | `int` |
| PalScriptMgr | 0x370 | m_pTodo_370 | `char *` |
| PalScriptMgr | 0x374 | m_fDirNeg | `float` |
| PalScriptMgr | 0x378 | m_pClearResult | `char *` |
| PalScriptMgr | 0x37c | m_nExecHandle | `int` |
| PalScriptMgr | 0x38 | m_pPauseBackup | `void *` |
| PalScriptMgr | 0x3bc | m_nState | `int` |
| PalScriptMgr | 0x3c | m_nFrameCounter | `int` |
| PalScriptMgr | 0x4 | m_bGetSceneScript | `unsigned char` |
| PalScriptMgr | 0x40 | m_fPauseCamY | `float` |
| PalScriptMgr | 0x420 | m_bDirty | `int` |
| PalScriptMgr | 0x44 | m_pBigMapSce | `scSCEFile *` |
| PalScriptMgr | 0x47c | m_nFrameState | `int` |
| PalScriptMgr | 0x48 | m_wndTextBox | `float` |
| PalScriptMgr | 0x4c | m_fPosZ | `float` |
| PalScriptMgr | 0x4f8 | m_nOpType | `int` |
| PalScriptMgr | 0x50 | m_scepath | `scSCEFile *` |
| PalScriptMgr | 0x508 | m_nCmdData | `int` |
| PalScriptMgr | 0x514 | m_fFramePosX | `int` |
| PalScriptMgr | 0x518 | m_fFramePosY | `int` |
| PalScriptMgr | 0x51c | m_fFramePosZ | `int` |
| PalScriptMgr | 0x520 | m_fFrameScale | `int` |
| PalScriptMgr | 0x524 | m_fFrameRot | `int` |
| PalScriptMgr | 0x528 | m_nFrameParam | `int` |
| PalScriptMgr | 0x54 | m_bBigMapState | `unsigned char` |
| PalScriptMgr | 0x58 | m_scriptAux | `int` |
| PalScriptMgr | 0x5c | m_pScriptObjMain | `gbVisNode *` |
| PalScriptMgr | 0x5cc | m_OpSubObj | `int` |
| PalScriptMgr | 0x5d0 | m_OpParam | `int` |
| PalScriptMgr | 0x5d4 | m_OpData | `int` |
| PalScriptMgr | 0x5e0 | m_OpBuffer | `int` |
| PalScriptMgr | 0x60 | m_pExecSystem | `char *` |
| PalScriptMgr | 0x64 | m_nTodo_060 | `int` |
| PalScriptMgr | 0x68 | m_nTodo_064 | `int` |
| PalScriptMgr | 0x6c | m_nTodo_068 | `short` |
| PalScriptMgr | 0x70 | m_nTodo_06C | `short` |
| PalScriptMgr | 0x74 | m_nTodo_070 | `int` |
| PalScriptMgr | 0x778 | m_nTodo_774 | `int` |
| PalScriptMgr | 0x78 | m_nTodo_074 | `float` |
| PalScriptMgr | 0x780 | m_ctrlParabola | `int` |
| PalScriptMgr | 0x7c | m_nTodo_078 | `int` |
| PalScriptMgr | 0x7d4 | m_nField_07D0 | `int` |
| PalScriptMgr | 0x8 | m_scriptMain | `PtrArray` |
| PalScriptMgr | 0x80 | m_nTodo_07C | `float` |
| PalScriptMgr | 0x84 | m_nExecParam | `int` |
| PalScriptMgr | 0x88 | m_vRolePos | `int` |
| PalScriptMgr | 0x8c | m_fDefaultFOV | `float` |
| PalScriptMgr | 0x940 | m_nTodo_93C | `int` |
| PalScriptMgr | 0x948 | m_wndTextDisplay | `UIWnd *` |
| PalScriptMgr | 0x970 | m_nField_096C | `int` |
| PalScriptMgr | 0x98 | m_nScriptIdx | `int` |
| PalScriptMgr | 0x9c | m_pCurScriptBlock | `void *` |
| PalScriptMgr | 0xa0 | m_nBlockEndAddr | `int` |
| PalScriptMgr | 0xa4 | m_pExecState | `void *` |
| PalScriptMgr | 0xa8 | m_pVarContext | `int` |
| PalScriptMgr | 0xac | m_szScriptFile | `char[6]` |
| PalScriptMgr | 0xb2 | m_bExecuteBlock | `unsigned char` |
| PalScriptMgr | 0xb3 | m_bScriptPause | `unsigned char` |
| PalScriptMgr | 0xb4 | m_RoleAnimData | `int` |
| PalScriptMgr | 0xb40 | m_nField_0B3C | `int` |
| PalScriptMgr | 0xb78 | m_nField_0B74 | `int` |
| PalScriptMgr | 0xbc | m_bRunning | `int` |
| PalScriptMgr | 0xc0 | m_bBlockActive | `int` |
| PalScriptMgr | 0xc08 | m_nField_0C04 | `int` |
| PalScriptMgr | 0xc4 | m_bBlockFlag | `int` |
| PalScriptMgr | 0xc68 | m_nField_0C64 | `int` |
| PalScriptMgr | 0xc74 | m_nField_0C70 | `int` |
| PalScriptMgr | 0xcc | m_nTodo_0C8 | `int` |
| PalScriptMgr | 0xcd0 | m_bDeviceResetFlag | `int` |
| PalScriptMgr | 0xcd4 | m_pTodo_CD4 | `char *` |
| PalScriptMgr | 0xcd8 | m_nField_CD4 | `unsigned char` |
| PalScriptMgr | 0xcdc | m_nScreenEffect | `int` |
| PalScriptMgr | 0xce0 | m_nEffectTick | `int` |
| PalScriptMgr | 0xce4 | m_nTickStamp | `int` |
| PalScriptMgr | 0xce8 | m_bEffectInit | `unsigned char` |
| PalScriptMgr | 0xcec | m_bEffectActive | `unsigned char` |
| PalScriptMgr | 0xced | m_nTodo_CE9 | `unsigned char` |
| PalScriptMgr | 0xd0 | m_nSavedBlockNum | `int` |
| PalScriptMgr | 0xd4 | m_pTodo_84 | `unsigned char` |
| PalScriptMgr | 0xd5 | m_bOpcodeFlag | `unsigned char` |
| PalScriptMgr | 0xd8 | m_nExecuteBlock | `int` |
| PalScriptMgr | 0xdc | m_nSavedDataA | `int` |
| PalScriptMgr | 0xe0 | m_nSavedDataB | `int` |
| PalScriptMgr | 0xe4 | m_fAngle | `float` |
| PalScriptMgr | 0xe74 | m_nField_0E70 | `int` |
| PalScriptMgr | 0xe8 | m_nExecRangeA | `int` |
| PalScriptMgr | 0xec | m_nExecRangeB | `int` |
| PalScriptMgr | 0xf0 | m_nExecRangeC | `int` |
| PalScriptMgr | 0xf4 | m_nExecRangeD | `int` |
| PalScriptMgr | 0xf8 | m_nCmdType | `unsigned char` |
| PalScriptMgr | 0xf9 | m_nTodo_0F5 | `unsigned char` |
| PalScriptMgr | 0xfa | m_bExecuteOpcode | `unsigned char` |
| PalScriptMgr | 0xfb | m_nTodo_0F7 | `unsigned char` |
| PalScriptMgr | 0xfc | m_nCmdValue | `int` |
| PalScriptMgr | 0xfc0 | m_RoleCmdCtx | `int` |
| PalScriptProgressTimer | 0x8 | m_fElapsed | `float` |
| PalScriptProgressTimer | 0xc | m_bDone | `char` |
| PalScriptSlotStateOverlay | 0x1c8 | m_pCurrentScript | `PalScript *` |
| PalScriptSlotStateOverlay | 0x1cc | m_bFormationReady | `_BYTE` |
| PalScriptSlotStateOverlay | 0x1cd | m_nSceneTransitionParam | `_BYTE` |
| PalScriptSlotStateOverlay | 0x1d0 | _todo_35c | `int` |
| PalScriptSlotStateOverlay | 0x1d4 | _todo_360 | `int` |
| PalScriptSlotStateOverlay | 0x1dc | m_fFadeTimer | `float` |
| PalScriptSlotStateOverlay | 0x1e0 | _todo_36c | `int` |
| PalScriptSlotStateOverlay | 0x244 | m_szSceneUIText | `char[256]` |
| PalScriptSlotStateOverlay | 0x35c | _todo_4e8 | `int` |
| PalScriptWaitObj | 0x0 | m_nTodo_000 | `void *` |
| PalScriptWaitObj | 0x4 | m_needscriptdel | `gbImage2D *` |
| PalScriptWaitTimer | 0x8 | m_fElapsed | `float` |
| PalScriptWaitTimer | 0xc | m_bDone | `char` |
| ParabolaCalculator | 0x0 | velocity | `gbVec3D` |
| ParabolaCalculator | 0x18 | B | `gbVec3D` |
| ParabolaCalculator | 0x24 | H | `float` |
| ParabolaCalculator | 0x28 | G | `float` |
| ParabolaCalculator | 0x2c | m_state | `int` |
| ParabolaCalculator | 0xc | A | `gbVec3D` |
| ParabolaCalculator_PRBL_STATE | 0x0 | _tail_000 | `char[4]` |
| Param0 | 0x0 | loc | `localVar0` |
| Param0 | 0x10 | pOut | `DWORD` |
| Param0 | 0x14 | pIn | `DWORD` |
| Param0 | 0x18 | n | `DWORD` |
| Param0 | 0xc | retAddr | `DWORD` |
| Param1 | 0x0 | loc | `localVar1` |
| Param1 | 0x1c | retAddr | `DWORD` |
| Param1 | 0x20 | pOut | `DWORD` |
| Param1 | 0x24 | pIn | `DWORD` |
| Param1 | 0x28 | n | `DWORD` |
| Param2 | 0x0 | loc | `localVar2` |
| Param2 | 0x10c | retAddr | `DWORD` |
| Param2 | 0x110 | pOut | `DWORD` |
| Param2 | 0x114 | OutStride | `DWORD` |
| Param2 | 0x118 | pV | `DWORD` |
| Param2 | 0x11c | VStride | `DWORD` |
| Param2 | 0x120 | pM | `DWORD` |
| Param2 | 0x124 | n | `DWORD` |
| Parent_Data | 0x0 | _tail_000 | `char[4]` |
| ParticleEffect | 0x58954 | active_parnum | `int` |
| ParticleEffect | 0x58958 | m_pTexture | `gbTexture_D3D *[4]` |
| ParticleEffect | 0x58968 | deltatime | `float` |
| ParticleVisNode | 0x0 | _tail_000 | `char[8]` |
| PathFinder | 0x18 | m_curlayer | `NavTileLayer *` |
| PathFinder | 0x1c | m_layer | `int` |
| PathFinder | 0x20 | m_pRole | `Role *` |
| PathObj | 0x0 | points | `gbVec3D[256]` |
| PathObj | 0x1008 | normal | `gbVec3D *` |
| PathObj | 0x100c | m_nCurPathLen | `int` |
| PathObj | 0x1010 | m_nTodo_1010 | `int` |
| PathObj | 0x1014 | m_pPathDir | `gbVec3D *` |
| PathObj | 0x1018 | m_nPathLen | `int` |
| PathObj | 0x101c | m_nTodo_101C | `int` |
| PathObj | 0x1c08 | segmentprojection | `float` |
| PathObj | 0x1c0c | segmentlength | `float` |
| PathObj | 0x1c10 | segmentnormal | `gbVec3D` |
| PathObj | 0x1c1c | chosen | `gbVec3D` |
| PathObj | 0xc00 | numpoint | `int` |
| PathObj | 0xc04 | totallength | `float` |
| PathObj | 0xc08 | length | `float[256]` |
| PlayerAtt | 0x354 | hat | `PlayerItem` |
| PlayerAtt | 0x360 | cloth | `PlayerItem` |
| PlayerAtt | 0x36c | shoes | `PlayerItem` |
| PlayerAtt | 0x378 | wear | `PlayerItem[2]` |
| PlayerAtt | 0x390 | weapon | `PlayerItem` |
| PlayerAtt | 0x39c | maxrolevalue | `int[12]` |
| PlayerAtt | 0x3cc | currolevalue | `int[12]` |
| PlayerAtt | 0x3fc | nProtectRole | `int` |
| PlayerAtt | 0x400 | dwWeaponSkillID | `DWORD` |
| PlayerAtt | 0x404 | dwCleanCent | `DWORD` |
| PlayerAtt | 0x408 | fWeaponSkillMass | `float` |
| PlayerAtt | 0x40c | dwSkillID | `unsigned int[9]` |
| PlayerAtt | 0x430 | bSkillMastered | `unsigned char[9]` |
| PlayerAtt | 0x43c | dwMagicID | `unsigned int[9][6]` |
| PlayerAtt | 0x514 | bMagicMastered | `unsigned char[9][6]` |
| PlayerAtt | 0x54a | byMagicUseTime | `unsigned short[9][6]` |
| PlayerAtt | 0x5b6 | byMagicLevel | `unsigned char[9][6]` |
| PlayerAtt | 0x5ec | bAutoCtrl | `BYTE` |
| PlayerAtt | 0x5ed | bAIAttack | `BYTE` |
| PlayerAtt | 0x5ee | bAIMagic | `BYTE` |
| PlayerAtt | 0x5ef | bAISkill | `BYTE` |
| PlayerAtt | 0x5f0 | bAIUseItem | `BYTE` |
| PlayerAtt | 0x5f1 | bAINegative | `BYTE` |
| PlayerAtt | 0x5f2 | byLineup | `BYTE` |
| PlayerAtts | 0xc0 | m_nTodo_0C0 | `int` |
| PlayerAtts | 0xc4 | m_nTodo_0C4 | `int` |
| PlayerAtts | 0xcc | m_nTodo_0CC | `int` |
| PlayerItem | 0x0 | id | `DWORD` |
| PlayerItem | 0x4 | num | `int` |
| PlayerItem | 0x8 | item | `FightItem *` |
| PlayerItemSortFun | 0x0 | m_by | `int` |
| PlayerSkill | 0x0 | id | `DWORD` |
| PlayerSkill | 0x4 | lv | `WORD` |
| PlayerSkill | 0x6 | usedtime | `WORD` |
| PlayerSkill | 0x8 | skill | `FightSkill *` |
| PolyLine | 0x0 | numpt | `int` |
| PolyLine | 0x4 | pt | `gbVec3D[16]` |
| PropUI | 0x1118 | m_nTodo_1118 | `int` |
| PropUI | 0x164 | m_nListCount | `int` |
| PropUI | 0x168 | m_nListSub | `int` |
| PropUI | 0x178 | m_nTodo_178 | `int` |
| PropUI | 0x190 | m_nTodo_190 | `int` |
| PropUI | 0x1f4 | m_nTodo_1F4 | `int` |
| PropUI | 0x1f8 | m_nTodo_1F8 | `int` |
| PropUI | 0x22c | m_nTodo_22C | `int` |
| PropUI | 0x258 | m_nTodo_258 | `int` |
| PropUI | 0x260 | m_nTodo_260 | `int` |
| PropUI | 0x264 | m_szItemTextA | `char[64]` |
| PropUI | 0x2d0 | m_nTodo_2D0 | `int` |
| PropUI | 0x2d4 | m_nTodo_2D4 | `int` |
| PropUI | 0x2d8 | m_nTodo_2D8 | `int` |
| PropUI | 0x2dc | m_nTodo_2DC | `int` |
| PropUI | 0x2e0 | m_nTodo_2E0 | `int` |
| PropUI | 0x320 | m_nTodo_320 | `int` |
| PropUI | 0x3648 | m_nTodo_3648 | `int` |
| PropUI | 0x3650 | m_nTodo_3650 | `int` |
| PropUI | 0x36a4 | m_nBuyListCap | `int` |
| PropUI | 0x3c90 | m_nTodo_3C90 | `int` |
| PropUI | 0x4008 | m_pBuyListBase | `int` |
| PropUI | 0x42d0 | m_bSelFlags | `int` |
| PropUI | 0x43c | m_SubTitleBBTY | `void *` |
| PropUI | 0x44b8 | p_DealData | `PlayerItem *` |
| PropUI | 0x44bc | buf | `char[256]` |
| PropUI | 0x45bc | remarkbuf | `char[256]` |
| PropUI | 0x46bc | m_SelNum | `int` |
| PropUI | 0x46c0 | m_ListSelNum | `int *` |
| PropUI | 0x46c4 | m_MaxNum | `int *` |
| PropUI | 0x46c8 | m_x | `int` |
| PropUI | 0x46cc | m_y | `int` |
| PropUI | 0x46d0 | m_Sum | `int` |
| PropUI | 0x46d4 | i | `int` |
| PropUI | 0x46d8 | j | `int` |
| PropUI | 0x46dc | _isCreatable | `unsigned char` |
| PropUI | 0x46e0 | m_Frame | `UIStatic` |
| PropUI | 0x4778 | m_EmbedUI3DCtrl | `int` |
| PropUI | 0x4780 | m_FrameBar | `UIFlexBar` |
| PropUI | 0x47d4 | m_Flag | `UIStatic` |
| PropUI | 0x48 | bkWndX | `int` |
| PropUI | 0x486c | m_nTodo_486C | `int` |
| PropUI | 0x4870 | m_nTodo_4870 | `int` |
| PropUI | 0x4874 | m_OutFrameT | `UIStatic` |
| PropUI | 0x48c | m_nTodo_48C | `int` |
| PropUI | 0x490 | m_nTodo_490 | `int` |
| PropUI | 0x4914 | m_OutFrameR | `UIStatic` |
| PropUI | 0x49b4 | m_OutFrameL | `UIStatic` |
| PropUI | 0x4a54 | m_OutFrameB | `UIStatic` |
| PropUI | 0x4af4 | mb_ExitRc | `tagRECT` |
| PropUI | 0x4b04 | mb_Exit | `UIButton` |
| PropUI | 0x4c | bkWndY | `int` |
| PropUI | 0x4c5c | m_ani | `UIAnimateCtrl` |
| PropUI | 0x4d00 | m_Role | `UIStatic[5]` |
| PropUI | 0x50 | m_ListWidth | `int` |
| PropUI | 0x5020 | m_RoleRc | `tagRECT[5]` |
| PropUI | 0x5070 | RoleX | `int` |
| PropUI | 0x5074 | RoleY | `int` |
| PropUI | 0x5078 | HeadW | `int` |
| PropUI | 0x507c | HeadH | `int` |
| PropUI | 0x5080 | m_Is | `unsigned char[5]` |
| PropUI | 0x5088 | m_Msg | `MUIDialog` |
| PropUI | 0x54 | m_ListHeight | `int` |
| PropUI | 0x559c | m_EmbedSubPanel | `int` |
| PropUI | 0x55f0 | m_3DObj | `UI3DCtrl` |
| PropUI | 0x564 | m_szItemTextB | `char[64]` |
| PropUI | 0x5724 | m_Dlg | `UIStatic` |
| PropUI | 0x57c4 | m_DlgRc | `tagRECT` |
| PropUI | 0x57d4 | m_TalkFrame | `UIStatic` |
| PropUI | 0x58 | m_PropData | `st_Manager` |
| PropUI | 0x5874 | m_Ready | `UIStatic` |
| PropUI | 0x5914 | m_ReadyRc | `tagRECT` |
| PropUI | 0x5924 | m_ListFrame | `UIStatic` |
| PropUI | 0x59c4 | m_ListGrid | `UIStatic[14]` |
| PropUI | 0x6284 | m_ScrollHB | `UIStatic` |
| PropUI | 0x6324 | m_EquipFlag | `UIStatic` |
| PropUI | 0x63c4 | m_ListPropTitle | `UIStatic` |
| PropUI | 0x6464 | m_ListPropTitleRc | `tagRECT` |
| PropUI | 0x6474 | ml_ListProp | `UIListBox` |
| PropUI | 0x6950 | m_nCaptionOverlay | `int` |
| PropUI | 0x697c | ml_ListPropRc | `tagRECT` |
| PropUI | 0x698c | m_btnGroup | `BtnGroup` |
| PropUI | 0x6c70 | m_ctrlTime | `float` |
| PropUI | 0x6c74 | m_bCanUpdate1 | `unsigned char` |
| PropUI | 0x6c75 | m_bCanUpdate2 | `unsigned char` |
| PropUI | 0x6c78 | m_PropRemarkBk | `UIStatic` |
| PropUI | 0x6d18 | m_PropRemark | `UIStatic` |
| PropUI | 0x6db8 | m_PropAtt | `UIStatic` |
| PropUI | 0x6e58 | m_MoneyRemark | `UIStatic` |
| PropUI | 0x6ef8 | m_MoneyRc | `tagRECT` |
| PropUI | 0x6f08 | m_SumProp | `UIStatic` |
| PropUI | 0x6fa8 | m_SumRc | `tagRECT` |
| PropUI | 0x6fb8 | mb_OK | `UIButton` |
| PropUI | 0x7110 | mb_OKRc | `tagRECT` |
| PropUI | 0x864 | m_szItemTextC | `char[64]` |
| ProtectPanel | 0x1e4 | m_WPXFace | `UIPushButton` |
| ProtectPanel | 0x48 | m_BK | `UIStatic` |
| ProtectPanel | 0xe8 | m_WHFace | `UIPushButton` |
| PtrArray | 0x0 | m_pData | `char *` |
| PtrArray | 0x4 | capacity | `int` |
| PtrArray | 0x8 | m_nSize | `int` |
| PtrArray | 0xc | m_needscriptdel | `int` |
| PtrVec | 0x0 | m_bInitFlag | `unsigned char` |
| PtrVec | 0x4 | m_begin | `void *` |
| PtrVec | 0x8 | m_end | `void *` |
| PtrVec | 0xc | m_cap | `void *` |
| PurgeEffect | 0x0 | pSrcTex | `gbTexture *` |
| PurgeEffect | 0x194 | m_ItemNum | `int` |
| PurgeEffect | 0x198 | EffItem | `std::vector<EffectItem,std::allocator<EffectItem> >` |
| PurgeEffect | 0x1a8 | m_isUpdateMerge | `unsigned char` |
| PurgeEffect | 0x4 | pSrcImg | `gbImage2D` |
| PurgeEffect | 0xcc | pDstImg | `gbImage2D` |
| RC_ARG | 0x0 | fov | `float` |
| RC_ARG | 0x10 | lookat | `gbVec3D` |
| RC_ARG | 0x4 | yaw | `float` |
| RC_ARG | 0x8 | pitch | `float` |
| RC_ARG | 0xc | dist | `float` |
| RELIVEPARAM | 0x0 | AlphaSpeed | `float` |
| RELIVEPARAM | 0x4 | fTimeCounter | `float` |
| RELIVEPARAM | 0x8 | nWaitSecond | `int` |
| RELIVEPARAM | 0xc | nState | `int` |
| RGNDATAHEADER | 0x0 | dwSize | `UINT` |
| RGNDATAHEADER | 0x10 | rcBound | `tagRECT` |
| RGNDATAHEADER | 0x4 | iType | `UINT` |
| RGNDATAHEADER | 0x8 | nCount | `UINT` |
| RGNDATAHEADER | 0xc | nRgnSize | `UINT` |
| RenderTarget | 0x0 | m_iMode | `int` |
| RenderTarget | 0x10 | m_nHalfW | `int` |
| RenderTarget | 0x14 | m_nHalfH | `unsigned char` |
| RenderTarget | 0x18 | m_nHalfWidth | `int` |
| RenderTarget | 0x1c | m_nHalfHeight | `int` |
| RenderTarget | 0x20 | m_nWidth | `int` |
| RenderTarget | 0x24 | m_nHeight | `int` |
| RenderTarget | 0x28 | m_nTodo_028 | `unsigned char` |
| RenderTarget | 0x2c | m_nTodo_02C | `float` |
| RenderTarget | 0x30 | m_fX | `float` |
| RenderTarget | 0x34 | m_fY | `float` |
| RenderTarget | 0x38 | m_nTodo_038 | `int` |
| RenderTarget | 0x3c | m_nTodo_03C | `int` |
| RenderTarget | 0x4 | m_Texture | `gbTexture_D3D *` |
| RenderTarget | 0x40 | m_fileHeader | `float` |
| RenderTarget | 0x44 | m_fRenderX | `float` |
| RenderTarget | 0x48 | m_fRenderY | `float` |
| RenderTarget | 0x4c | m_fileData | `float` |
| RenderTarget | 0x50 | m_fFileParam | `float` |
| RenderTarget | 0x54 | m_nColor | `int` |
| RenderTarget | 0x58 | m_szPath | `int` |
| RenderTarget | 0x5c | m_nDefaultH | `int` |
| RenderTarget | 0x64 | m_ScreenPlane | `gbTexture_D3D *` |
| RenderTarget | 0x7c | m_nAlpha | `int` |
| RenderTarget | 0x8 | m_nRenderX | `int` |
| RenderTarget | 0x80 | m_bVisible | `int` |
| RenderTarget | 0x84 | m_fRenderIntensity | `float` |
| RenderTarget | 0x88 | m_fOffsetParam | `float` |
| RenderTarget | 0x8c | m_fRender | `float` |
| RenderTarget | 0x90 | m_fOffsetX | `float` |
| RenderTarget | 0x94 | m_fOffsetY | `float` |
| RenderTarget | 0x98 | m_nScaleX | `int` |
| RenderTarget | 0x9c | m_nScaleY | `int` |
| RenderTarget | 0xa0 | m_szTexPath | `char[16]` |
| RenderTarget | 0xb0 | m_fInvScale | `float` |
| RenderTarget | 0xb8 | m_nDeviceLost | `int` |
| RenderTarget | 0xbc | m_nTodo_0BC | `int` |
| RenderTarget | 0xc | m_nRenderY | `int` |
| RenderTarget | 0xc4 | m_nState | `int` |
| RenderTarget2 | 0x0 | _tail_000 | `char[4292]` |
| RenderTarget3 | 0x4 | m_ptr_4 | `gbRenderEffect *` |
| RenderTarget4 | 0x0 | _tail_000 | `char[4]` |
| RenderTargetNode | 0x0 | _tail_000 | `char[96]` |
| Reoccupy | 0x0 | m_id | `std::vector<unsigned int,std::allocator<unsigned int> >` |
| RestScript | 0x0 | m_LoadRest | `TxtFile` |
| RestScript | 0x20c | m_lastFile | `char[256]` |
| RestScript | 0x30c | m_Data | `ScriptData` |
| Role | 0x21f4 | m_wanapos | `gbVec3D` |
| Role | 0x274 | m_onlayer | `int` |
| Role | 0x278 | m_active | `int` |
| Role | 0x27c | bCGMonster | `unsigned char` |
| Role | 0x280 | nCGMonsterID | `int` |
| Role | 0x284 | nCGMonsterType | `int` |
| Role | 0x288 | bRelive | `unsigned char` |
| Role | 0x289 | bInvincible | `unsigned char` |
| Role | 0x28c | fRattrapWait | `float` |
| Role | 0x290 | fMirrorWait | `float` |
| Role | 0x294 | bMirror | `unsigned char` |
| Role | 0x298 | fCGBIXIE | `int` |
| Role | 0x29c | bCGBIXIE | `unsigned char` |
| Role | 0x29d | bCrossAlpha | `unsigned char` |
| Role | 0x2a0 | fCrossAlpha | `int` |
| Role | 0x2a4 | bCGMonsterHitObj | `unsigned char` |
| Role | 0x2a5 | bStill | `unsigned char` |
| Role | 0x2a8 | pCG_SceneProp | `SceneProp *` |
| Role | 0x2ac | m_actor | `Actor` |
| Role | 0x5e0 | m_talkoldact | `ACTION_KIND` |
| Role | 0x5e4 | m_talkoldface | `float` |
| Role | 0x5e8 | m_talkobj | `SceneObj *` |
| Role | 0x5ec | m_mstate | `int` |
| Role | 0x5f0 | m_matt | `RoleAtt *` |
| Role | 0x5f4 | m_mfreedist | `float` |
| Role | 0x5f8 | m_mattackrange | `float` |
| Role | 0x5fc | m_mfindradius | `float` |
| Role | 0x60 | m_cmdqueue | `std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >` |
| Role | 0x600 | m_statetime | `float` |
| Role | 0x604 | m_weapon | `gbGeomNode *` |
| Role | 0x608 | m_bLeftWeapon | `unsigned char` |
| Role | 0x609 | m_bRightWeapon | `unsigned char` |
| Role | 0x60c | m_nRad | `int` |
| Role | 0x610 | m_nRealHeadPos | `int` |
| Role | 0x614 | m_nOverlapState | `int` |
| Role | 0x618 | m_tpos | `tagPOINT` |
| Role | 0x620 | m_vTagHeadPos | `gbVec3D` |
| Role | 0x62c | m_overlap | `int` |
| Role | 0x630 | m_bPathMove | `int` |
| Role | 0x634 | m_pathMoveCounter | `int` |
| Role | 0x638 | m_lastpos | `gbVec3D` |
| Role | 0x644 | m_notePos | `gbVec3D` |
| Role | 0x650 | m_path_region | `char[7076]` |
| Role | 0x90 | m_bInView | `int` |
| Role | 0x94 | m_groundpos | `gbVec3D` |
| Role | 0xa0 | m_renderpos | `gbVec3D` |
| Role | 0xac | m_npcinfo | `NPCInfo` |
| RoleAtt | 0x0 | id | `DWORD` |
| RoleAtt | 0x206 | ModelID | `char[30]` |
| RoleAtt | 0x224 | ImageID | `char[30]` |
| RoleAtt | 0x244 | att | `int[5]` |
| RoleAtt | 0x258 | name | `char[32]` |
| RoleAtt | 0x278 | lv | `float` |
| RoleAtt | 0x27c | rolevalue | `int[12]` |
| RoleAtt | 0x2ac | fightstate | `unsigned char[31]` |
| RoleAtt | 0x2cc | RoundNum | `float` |
| RoleAtt | 0x2d0 | SAID | `unsigned char` |
| RoleAtt | 0x2d4 | Escape | `float` |
| RoleAtt | 0x2d8 | haogan | `unsigned short[5]` |
| RoleAtt | 0x2e4 | exp | `float` |
| RoleAtt | 0x2e8 | gold | `WORD` |
| RoleAtt | 0x2ec | NormalAtkID | `DWORD` |
| RoleAtt | 0x2f0 | height | `BYTE` |
| RoleAtt | 0x2f1 | move | `BYTE` |
| RoleAtt | 0x2f2 | attackrange | `BYTE` |
| RoleAtt | 0x2f3 | speed1 | `BYTE` |
| RoleAtt | 0x2f4 | speed2 | `BYTE` |
| RoleAtt | 0x2f8 | skill | `unsigned int[4]` |
| RoleAtt | 0x308 | skill_lv | `unsigned char[3]` |
| RoleAtt | 0x30c | RoleQiAdd | `int` |
| RoleAtt | 0x310 | append | `float[10]` |
| RoleAtt | 0x338 | normalplunder | `DWORD` |
| RoleAtt | 0x33c | normalplundernum | `short` |
| RoleAtt | 0x340 | shikuai | `DWORD` |
| RoleAtt | 0x344 | shikuaiskill | `DWORD` |
| RoleAtt | 0x348 | shikuaisucc | `short` |
| RoleAtt | 0x34a | stealmoney | `short` |
| RoleAtt | 0x34c | steal | `DWORD` |
| RoleAtt | 0x350 | stealnum | `short` |
| RoleAtt | 0x352 | getmoney | `short` |
| RoleAtt | 0x4 | type | `WORD` |
| RoleCamera | 0x17c | m_ptarget | `Role *` |
| RoleCamera | 0x180 | m_pobj | `SceneObj *` |
| RoleCamera | 0x184 | m_targetpos | `gbVec3D` |
| RoleCamera | 0x190 | m_lastFrom | `gbVec3D` |
| RoleCamera | 0x19c | m_fromVec | `gbVec3D` |
| RoleCamera | 0x1a8 | m_yaw | `float` |
| RoleCamera | 0x1ac | m_fCtrlYaw | `float` |
| RoleCamera | 0x1b0 | m_dist | `int` |
| RoleCamera | 0x1b4 | m_pitch | `float` |
| RoleCamera | 0x1b8 | m_roll | `int` |
| RoleCamera | 0x1bc | m_nextYAW | `float` |
| RoleCamera | 0x1c | m_nStackIdx | `int` |
| RoleCamera | 0x1c0 | m_lastYAW | `float` |
| RoleCamera | 0x1c4 | m_camVelocity | `gbVec3D` |
| RoleCamera | 0x1d4 | m_nTodo_1D4 | `int` |
| RoleCamera | 0x1e0 | m_nTodo_1E0 | `int` |
| RoleCamera | 0x1e4 | m_nTodo_1E4 | `int` |
| RoleCamera | 0x1e8 | m_nTodo_1E8 | `int` |
| RoleCamera | 0x1f4 | m_nTodo_1F4 | `int` |
| RoleCamera | 0x20 | m_nStackSize | `int` |
| RoleCamera | 0x200 | m_bFree | `int` |
| RoleCamera | 0x204 | m_bLockForward | `int` |
| RoleCamera | 0x208 | m_bLockCenter | `int` |
| RoleCamera | 0x20c | m_bProcessCollision | `int` |
| RoleCamera | 0x210 | m_CollideTriangleNum | `int` |
| RoleCamera | 0x214 | polygonList | `char[16]` |
| RoleCamera | 0x224 | polygonListBackup | `char[16]` |
| RoleCamera | 0x234 | m_CollideData | `char[12]` |
| RoleCamera | 0x240 | m_clientwidth | `int` |
| RoleCamera | 0x244 | m_clientheight | `int` |
| RoleCamera | 0x248 | CAMERA_LOCK_HALFRADIUS | `BYTE` |
| RoleCamera | 0x249 | CAMERA_COLLIDE_METHOD | `BYTE` |
| RoleCamera | 0x24c | m_lookat | `gbVec3D` |
| RoleCamera | 0x258 | m_from | `gbVec3D` |
| RoleCamera | 0x264 | m_forward | `gbVec3D` |
| RoleCamera | 0x270 | m_up | `gbVec3D` |
| RoleCamera | 0x27c | m_side | `gbVec3D` |
| RoleCamera | 0x288 | m_LockForward | `gbVec3D` |
| RoleCamera | 0x294 | m_LockCenter | `gbVec3D` |
| RoleCamera | 0x2a0 | m_bCollide | `BYTE` |
| RoleCamera | 0x2a4 | m_roomHeight | `float` |
| RoleCamera | 0x2a8 | m_lastUP | `gbVec3D` |
| RoleCameraCtrl | 0x48 | m_pTextArea | `UITextArea *` |
| RoleCtrl | 0x0 | s_camera | `int` |
| RoleCtrl | 0x14 | s_bUpdateSnd | `int` |
| RoleCtrl | 0x18 | s_prole | `Role *` |
| RoleCtrl | 0x1c | s_enable | `int` |
| RoleCtrl | 0x20 | s_cursorpos | `tagPOINT` |
| RoleCtrl | 0x4 | s_cameraedit | `int` |
| RoleCtrl | 0x8 | s_clickpt | `gbVec3D` |
| RoleFadeIn | 0x10 | end | `BYTE` |
| RoleFadeIn | 0x8 | m_passedtime | `float` |
| RoleFadeIn | 0xc | m_role | `Role *` |
| RoleFadeOut | 0x10 | end | `BYTE` |
| RoleFadeOut | 0x8 | m_passedtime | `float` |
| RoleFadeOut | 0xc | m_role | `Role *` |
| RoleShadow | 0x10 | m_effectFrame | `gbRenderEffect *` |
| RoleShadow | 0x14 | m_quad | `gbGeomQuad[77]` |
| RoleShadow | 0x1488 | m_CtrlRoleQuad | `gbGeomQuad` |
| RoleShadow | 0x14cc | m_pFrameShadow | `FrameTex *` |
| RoleShadow | 0x14d0 | m_nFrameNum | `int` |
| RoleShadow | 0x14d4 | m_nCurFrame | `int` |
| RoleShadow | 0x14d8 | m_nFrameFPS | `int` |
| RoleShadow | 0x14dc | m_bFrameShadow | `BYTE` |
| RoleShadow | 0x4 | m_shadowtex | `gbTexture *` |
| RoleShadow | 0x8 | m_effect | `gbRenderEffect *` |
| RoleShadow | 0xc | m_effectFog | `gbRenderEffect *` |
| RoleStatePanel | 0x169 | m_bSlotFlags | `unsigned char[5]` |
| RoleStatePanel | 0x210 | m_RoleStatics | `UIStatic[5]` |
| RoleStatePanel | 0x25e04 | m_roles | `s_RoleState[5]` |
| RoleStatePanel | 0x2afbc | m_pSubTab1 | `UITitle_XJTM *` |
| RoleStatePanel | 0x2afd4 | m_nEquipSlot | `int` |
| RoleStatePanel | 0x2afd8 | m_nTodo_2afd8 | `unsigned char` |
| RoleStatePanel | 0x2afd9 | m_nTodo_2afd9 | `unsigned char` |
| RoleStatePanel | 0x2b078 | m_nDevLost1 | `int` |
| RoleStatePanel | 0x2b07c | m_nDevLost2 | `int` |
| RoleStatePanel | 0x60 | m_nScanIndex | `int` |
| RoleSystem | 0x100 | m_nActionParam | `unsigned char` |
| RoleSystem | 0x1000 | m_configData | `int[96]` |
| RoleSystem | 0x104 | m_nInitMoveMode | `unsigned char` |
| RoleSystem | 0x108 | m_nSpawnExtra | `int` |
| RoleSystem | 0x10c | m_nSpawnParam2 | `int` |
| RoleSystem | 0x110 | m_szModelPath | `int` |
| RoleSystem | 0x114 | m_pWaypointWnd | `UIWnd *` |
| RoleSystem | 0x1184 | m_nTodo_1184 | `int` |
| RoleSystem | 0x1188 | m_nTodo_1188 | `int` |
| RoleSystem | 0x118c | m_nMoveState1 | `int` |
| RoleSystem | 0x1190 | m_nMoveState2 | `int` |
| RoleSystem | 0x1194 | m_nMoveState3 | `int` |
| RoleSystem | 0x1198 | m_bMoveFlag1 | `unsigned char` |
| RoleSystem | 0x119c | m_nMoveParam1 | `int` |
| RoleSystem | 0x11a0 | m_nMoveParam2 | `int` |
| RoleSystem | 0x11a4 | m_bMoveFlag2 | `unsigned char` |
| RoleSystem | 0x11a8 | m_partyUI3 | `UIItem` |
| RoleSystem | 0x120 | m_nParamArray | `int` |
| RoleSystem | 0x1290 | m_teamData3 | `int[29]` |
| RoleSystem | 0x12c | m_bSpawnByteA | `unsigned char` |
| RoleSystem | 0x12d | m_bSpawnByteB | `unsigned char` |
| RoleSystem | 0x130 | m_nSpawnParam | `int` |
| RoleSystem | 0x134 | m_nActionTimer | `int` |
| RoleSystem | 0x138 | m_vecPosArray | `gbVec3D` |
| RoleSystem | 0x148 | m_nMoveSrc | `int` |
| RoleSystem | 0x14c | m_nMoveDst | `int` |
| RoleSystem | 0x150 | m_nMoveStep | `int` |
| RoleSystem | 0x160 | m_nSavedState | `int` |
| RoleSystem | 0x164 | m_nVisState | `int` |
| RoleSystem | 0x168 | m_bVisFlag | `unsigned char` |
| RoleSystem | 0x169 | _gap_169 | `unsigned char[3]` |
| RoleSystem | 0x16c | m_pWndFrame | `char *` |
| RoleSystem | 0x170 | m_nTodo_170 | `int` |
| RoleSystem | 0x17c | m_nActive | `int` |
| RoleSystem | 0x180 | m_fInactiveTime | `float` |
| RoleSystem | 0x190 | m_pCmdQueue | `void *` |
| RoleSystem | 0x194 | m_pCmdQueueEnd | `void *` |
| RoleSystem | 0x1968 | dword_17AA450 | `int` |
| RoleSystem | 0x198 | m_fCmdInterval | `float` |
| RoleSystem | 0x19c | m_fCmdTimer | `float` |
| RoleSystem | 0x1a0 | m_pPathNodeIter | `char *` |
| RoleSystem | 0x1a4 | m_nCmdQueuePos | `int` |
| RoleSystem | 0x1a8 | m_partyActor | `Actor` |
| RoleSystem | 0x44 | m_pVtable | `char *` |
| RoleSystem | 0x48 | m_fStateX | `float` |
| RoleSystem | 0x4c | m_fStateY | `float` |
| RoleSystem | 0x4dc | m_fPathTargetY | `float` |
| RoleSystem | 0x4e0 | m_fPathTargetZ | `float` |
| RoleSystem | 0x4e4 | m_fPathAngle | `float` |
| RoleSystem | 0x4e8 | m_fPathSpeed | `float` |
| RoleSystem | 0x4ec | m_nPrevMoveMode | `int` |
| RoleSystem | 0x4f0 | m_nMoveMode | `int` |
| RoleSystem | 0x4f4 | m_nMoveSubMode | `int` |
| RoleSystem | 0x4f8 | m_nCollisionState | `int` |
| RoleSystem | 0x4fc | m_nCollisionParam | `int` |
| RoleSystem | 0x50 | m_nStateMode | `unsigned char` |
| RoleSystem | 0x500 | m_bPathActive | `unsigned char` |
| RoleSystem | 0x504 | m_nCoreState | `int` |
| RoleSystem | 0x508 | m_nTransformState | `float` |
| RoleSystem | 0x50c | m_fMovement | `float` |
| RoleSystem | 0x510 | m_fRotAxisX | `float` |
| RoleSystem | 0x514 | m_fRotAxisY | `float` |
| RoleSystem | 0x518 | m_fRotAxisZ | `float` |
| RoleSystem | 0x51c | m_nMovement | `float` |
| RoleSystem | 0x520 | m_fSavedRotX | `float` |
| RoleSystem | 0x54 | m_nTimerDuration | `int` |
| RoleSystem | 0x56c | m_nActiveRole | `int` |
| RoleSystem | 0x570 | m_nRoleCount | `int` |
| RoleSystem | 0x574 | m_nAnimation | `int` |
| RoleSystem | 0x578 | m_nAnimCopy1 | `int` |
| RoleSystem | 0x57c | m_nAnimCopy2 | `int` |
| RoleSystem | 0x58 | m_fDirX | `float` |
| RoleSystem | 0x580 | m_nAnimCopy3 | `int` |
| RoleSystem | 0x584 | m_pLinkedRole | `Object3D *` |
| RoleSystem | 0x588 | m_nTransformMode | `int` |
| RoleSystem | 0x58c | m_pLinkedSystem | `char *` |
| RoleSystem | 0x590 | m_fAnimSpeed | `float` |
| RoleSystem | 0x594 | m_fMoveRadius | `float` |
| RoleSystem | 0x598 | m_fMoveSpeed | `float` |
| RoleSystem | 0x59c | m_nMoveReset | `int` |
| RoleSystem | 0x5a0 | m_pRenderObj | `gbGeomNode *` |
| RoleSystem | 0x5a4 | m_bRenderFlag1 | `int` |
| RoleSystem | 0x5a8 | m_bRenderFlag2 | `char` |
| RoleSystem | 0x5ac | m_nTodo_5AC | `int` |
| RoleSystem | 0x5b0 | m_pCtrlPoint | `char *` |
| RoleSystem | 0x5b4 | m_nMoveRole | `int` |
| RoleSystem | 0x5b8 | m_nRetryCount | `int` |
| RoleSystem | 0x5bc | m_fCachePosX | `float` |
| RoleSystem | 0x5c | m_fDirY | `float` |
| RoleSystem | 0x5c0 | m_fCachePosY | `float` |
| RoleSystem | 0x5c4 | m_fCachePosZ | `float` |
| RoleSystem | 0x5c8 | m_fMoveTargetX | `float` |
| RoleSystem | 0x5cc | m_fMoveTargetY | `int` |
| RoleSystem | 0x5d0 | m_fMoveTargetZ | `float` |
| RoleSystem | 0x5d4 | m_fMoveRole | `float` |
| RoleSystem | 0x5d8 | m_fMoveParamY | `float` |
| RoleSystem | 0x5dc | m_fMoveParamZ | `float` |
| RoleSystem | 0x60 | m_fDirZ | `float` |
| RoleSystem | 0x61c | m_nTodo_61C | `int` |
| RoleSystem | 0x64 | m_pPathPoints | `char *` |
| RoleSystem | 0x68 | m_nPathCount | `int` |
| RoleSystem | 0x68c | m_nTodo_68C | `int` |
| RoleSystem | 0x690 | m_nTodo_690 | `float` |
| RoleSystem | 0x6c | m_pPathCurrent | `char *` |
| RoleSystem | 0x70 | m_pPathNext | `char *` |
| RoleSystem | 0x74 | m_nTodo_074 | `int` |
| RoleSystem | 0x78 | m_nPathFlag | `int` |
| RoleSystem | 0x7c | m_nTodo_7C | `int` |
| RoleSystem | 0x80 | m_fMoveX | `float` |
| RoleSystem | 0x84 | m_nPathState | `int` |
| RoleSystem | 0x88 | m_fMoveZ | `float` |
| RoleSystem | 0x8c | m_pPathListHead | `char *` |
| RoleSystem | 0x90 | m_nActionResult | `int` |
| RoleSystem | 0x94 | m_nDispFontColor | `int` |
| RoleSystem | 0x98 | m_nDispWndColor | `int` |
| RoleSystem | 0x9c | m_nTodo_9C | `int` |
| RoleSystem | 0xa0 | m_fPosX | `float` |
| RoleSystem | 0xa4 | m_fPosY | `float` |
| RoleSystem | 0xa8 | m_fPosZ | `float` |
| RoleSystem | 0xac | m_nFacing | `char` |
| RoleSystem | 0xad | m_nActionState | `char` |
| RoleSystem | 0xb0 | m_szModelName | `int` |
| RoleSystem | 0xb4 | m_mapData | `int` |
| RoleSystem | 0xb8 | m_fScale | `float` |
| RoleSystem | 0xb90 | m_nTodo_B90 | `int` |
| RoleSystem | 0xb98 | m_wndPanel | `int` |
| RoleSystem | 0xbac | m_StaticSlotArray | `UIWnd` |
| RoleSystem | 0xbc | m_nImageIdx | `int` |
| RoleSystem | 0xc0 | m_fMoveSpd | `float` |
| RoleSystem | 0xce | m_byStateArray | `unsigned char` |
| RoleSystem | 0xd0 | m_bFlags | `char` |
| RoleSystem | 0xd1 | m_bActionState | `unsigned char` |
| RoleSystem | 0xd8 | m_fAngle | `float` |
| RoleSystem | 0xdc | m_fTileHeight | `float` |
| RoleSystem | 0xe0 | m_nSpawnData | `int` |
| RoleSystem | 0xe4 | m_nActionType | `int` |
| RoleSystem | 0xe8 | m_nActionStep | `int` |
| RoleSystem | 0xec | m_fActionParam | `float` |
| RoleSystem | 0xf0 | m_nSpawnFlags | `unsigned char` |
| RoleSystem | 0xf4 | m_nRoleAction | `unsigned char` |
| RoleSystem | 0xf6 | m_nRoleSlot | `unsigned char` |
| RoleSystem | 0xf8 | m_fWaypointX | `float` |
| RoleSystem | 0xfbc | m_pScriptBuf | `int` |
| RoleSystem | 0xfc | m_fWaypointZ | `float` |
| RoleSystem | 0xfe4 | m_nField_FE4 | `int` |
| RoleSystem | 0xff8 | m_nTodo_FF8 | `void *` |
| RoleTask | 0x0 | dwNameCrc | `DWORD` |
| RoleTask | 0x188 | bLast | `BYTE` |
| RoleTask | 0x4 | nType | `int` |
| RoleTask | 0x8 | tasktitle | `char[128]` |
| RoleTask | 0x88 | taskRemark | `char[256]` |
| RoleTaskLine | 0x0 | nType | `int` |
| RoleTaskLine | 0x4 | ID | `int` |
| RoleTaskLine | 0x8 | bFinished | `BYTE` |
| RoleTaskLine | 0x9 | taskpic | `char[128]` |
| RoleTaskPool | 0x0 | m_TaskData | `std::vector<RoleTask,std::allocator<RoleTask> >` |
| RoleTaskPool | 0x10 | m_TaskLine | `std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >` |
| RoleTaskPool | 0x20 | m_taskFile | `TxtFile` |
| RoleTaskPool | 0x22c | _TaskPicFolder | `char[128]` |
| Role_SPECIAL_ACTION | 0x0 | _tail_000 | `char[36]` |
| RotateInvObj | 0x10 | m_rotate | `gbVec3D` |
| RotateInvObj | 0x8 | m_passedtime | `float` |
| RotateInvObj | 0xc | end | `BYTE` |
| RotateObj | 0x10 | m_rotate | `gbVec3D` |
| RotateObj | 0x1c | m_rotatetime | `float` |
| RotateObj | 0x20 | m_mode | `BYTE` |
| RotateObj | 0x8 | m_passedtime | `float` |
| RotateObj | 0xc | end | `BYTE` |
| SCNFile | 0x0 | m_info | `SceneInfo` |
| SCNFile | 0x80c8 | m_numobj | `int` |
| SCNFile | 0x80cc | m_obj | `char[256]` |
| SCNFile | 0x84 | m_numnpc | `int` |
| SCNFile | 0x88 | m_npc | `NPCInfo[72]` |
| SCNHeader | 0x0 | magic | `unsigned char[4]` |
| SCNHeader | 0x4 | version | `WORD` |
| SCNHeader | 0x6 | numnpc | `WORD` |
| SCNHeader | 0x8 | offsetnpc | `DWORD` |
| SCNHeader | 0xc | numobj | `WORD` |
| SCNHeader | 0xe | offsetobj | `char[2]` |
| SPECIAL_ACTION | 0x0 | _tail_000 | `char[4]` |
| SSE4xMatrix | 0x0 | _11 | `float` |
| SSE4xMatrix | 0x10 | _12 | `float` |
| SSE4xMatrix | 0x20 | _13 | `float` |
| SSE4xMatrix | 0x30 | _14 | `float` |
| SSE4xMatrix | 0x40 | _21 | `float` |
| SSE4xMatrix | 0x50 | _22 | `float` |
| SSE4xMatrix | 0x60 | _23 | `float` |
| SSE4xMatrix | 0x70 | _24 | `float` |
| SSE4xMatrix | 0x80 | _31 | `float` |
| SSE4xMatrix | 0x90 | _32 | `float` |
| SSE4xMatrix | 0xa0 | _33 | `float` |
| SSE4xMatrix | 0xb0 | _34 | `float` |
| SSE4xMatrix | 0xc0 | _41 | `float` |
| SSE4xMatrix | 0xd0 | _42 | `float` |
| SSE4xMatrix | 0xe0 | _43 | `float` |
| SSE4xMatrix | 0xf0 | _44 | `float` |
| S_Distribute | 0x0 | id | `DWORD` |
| S_Distribute | 0x4 | Num | `int` |
| S_Distribute | 0x8 | m_Type | `int` |
| S_Distribute | 0xc | m_Index | `int` |
| SaleUI | 0x13064 | m_NotesNull | `int[299][5]` |
| SaleUI | 0x147c0 | m_IsEquip | `unsigned char[299][5]` |
| SaleUI | 0x14d97 | m_TempIsEquip | `unsigned char[299][5]` |
| SaleUI | 0x150 | remarkbuf | `char[256]` |
| SaleUI | 0x15370 | x | `int` |
| SaleUI | 0x15374 | rc | `tagRECT` |
| SaleUI | 0x15384 | m_Frame | `UIStatic` |
| SaleUI | 0x15424 | m_FrameBar | `UIFlexBar` |
| SaleUI | 0x15478 | m_Flag | `UIStatic` |
| SaleUI | 0x15518 | m_OutFrameT | `UIStatic` |
| SaleUI | 0x155b8 | m_OutFrameR | `UIStatic` |
| SaleUI | 0x15658 | m_OutFrameL | `UIStatic` |
| SaleUI | 0x156f8 | m_OutFrameB | `UIStatic` |
| SaleUI | 0x15798 | mb_Exit | `UIButton` |
| SaleUI | 0x158f0 | m_ExitRc | `tagRECT` |
| SaleUI | 0x15900 | m_ani | `UIAnimateCtrl` |
| SaleUI | 0x159a4 | m_Role | `UIStatic[5]` |
| SaleUI | 0x15cc4 | m_RoleRc | `tagRECT[5]` |
| SaleUI | 0x15d14 | RoleX | `int` |
| SaleUI | 0x15d18 | RoleY | `int` |
| SaleUI | 0x15d1c | HeadW | `int` |
| SaleUI | 0x15d20 | HeadH | `int` |
| SaleUI | 0x15d24 | m_Is | `unsigned char[5]` |
| SaleUI | 0x15d2c | m_Msg | `MUIDialog` |
| SaleUI | 0x16294 | m_3DObj | `UI3DCtrl` |
| SaleUI | 0x163c8 | m_FlagRc | `tagRECT` |
| SaleUI | 0x163d8 | m_TalkFrame | `UIStatic` |
| SaleUI | 0x16478 | m_Ready | `UIStatic` |
| SaleUI | 0x16518 | m_ReadyRc | `tagRECT` |
| SaleUI | 0x16528 | m_entryTalk | `char[256]` |
| SaleUI | 0x16628 | m_btn | `UIButton[5]` |
| SaleUI | 0x16ce0 | m_TabRc | `tagRECT` |
| SaleUI | 0x16cf0 | m_ListSaleTitle | `UIStatic` |
| SaleUI | 0x16d90 | m_ListEquipTitleRc | `tagRECT` |
| SaleUI | 0x16da0 | m_Icon | `UIStaticRM[5][5]` |
| SaleUI | 0x17ffc | m_ListFrame | `UIStatic` |
| SaleUI | 0x1809c | m_ScrollHB | `UIStatic` |
| SaleUI | 0x1813c | m_ListGrid | `UIStatic[14]` |
| SaleUI | 0x189fc | m_ListRc | `tagRECT` |
| SaleUI | 0x18a0c | ml_ResumeList | `UIListBox` |
| SaleUI | 0x18f14 | ResumeNum | `int` |
| SaleUI | 0x18f18 | ml_TreasureList | `UIListBox` |
| SaleUI | 0x19420 | TreasureNum | `int` |
| SaleUI | 0x19424 | ml_AttackList | `UIListBox` |
| SaleUI | 0x1992c | AttackNum | `int` |
| SaleUI | 0x250 | m_SelNum | `int` |
| SaleUI | 0x254 | m_data | `st_Manager` |
| SaleUI | 0x46b4 | m_sort | `SaleUI_SortData[299][5]` |
| SaleUI | 0x48 | bkWidth | `int` |
| SaleUI | 0x488 | m_inventory | `Inventory` |
| SaleUI | 0x4b0 | m_reoccupy | `Reoccupy` |
| SaleUI | 0x4c | bkHeight | `int` |
| SaleUI | 0x4c0 | dwWeaponWU | `int` |
| SaleUI | 0x50 | buf | `char[256]` |
| SaleUI | 0x756c | m_ListSelNum | `int[299][5]` |
| SaleUI | 0x8cc8 | m_Max | `int[299][5]` |
| SaleUI | 0xa424 | m_Sum | `int[5]` |
| SaleUI | 0xa438 | _isCreatable | `unsigned char` |
| SaleUI | 0xa43c | m_SaleData | `PlayerItem[299][5]` |
| SaleUI | 0xea50 | m_TempData | `PlayerItem[158]` |
| SaleUI | 0xf1b8 | m_bNGHS | `int` |
| SaleUI | 0xf1bc | m_bWPXS | `int` |
| SaleUI_SortData | 0x0 | _tail_000 | `char[4]` |
| SaveTask | 0x0 | mTouchCounter | `int` |
| SaveTask | 0x4 | m_iState | `int` |
| SaveTask | 0x8 | m_bCVDOver | `BYTE` |
| SceHeader | 0x0 | flag | `unsigned char[4]` |
| SceHeader | 0x4 | version | `BYTE` |
| SceHeader | 0x5 | blocknum | `char` |
| SceIndex | 0x0 | id | `DWORD` |
| SceIndex | 0x4 | offset | `DWORD` |
| SceIndex | 0x8 | desc | `char[64]` |
| SceOpcodeEntry | 0x0 | handler | `char *` |
| SceOpcodeEntry | 0x4 | paramTypes | `char[7]` |
| SceOpcodeEntry | 0xb | _pad | `char` |
| SceOpcodeEntry | 0xc | paramCount | `short` |
| SceOpcodeEntry | 0xe | _pad2 | `short` |
| Scene | 0x4 | m_pDataBegin | `char *` |
| Scene | 0x78650 | m_nTodo_78650 | `int` |
| Scene | 0x78654 | m_nTodo_78654 | `int` |
| Scene | 0x78658 | m_nTodo_78658 | `int` |
| Scene | 0x7865c | m_nTodo_7865c | `BYTE` |
| Scene | 0x78660 | m_nTodo_78660 | `int` |
| Scene | 0x8 | m_pDataEnd | `char *` |
| Scene | 0x80 | m_nReset | `int` |
| Scene | 0x84 | m_geomnode | `gbGeomNode *` |
| Scene | 0x88 | m_lights | `gbVisNode *` |
| Scene | 0x8c | m_aabb | `gbAABBox` |
| Scene | 0xa4 | m_bbArray | `PtrArray` |
| Scene | 0xb4 | m_objmap | `SceneMapObj[2]` |
| Scene | 0xc | m_pCapacity | `char *[29]` |
| Scene | 0xdc | m_numobj | `int` |
| Scene | 0xe0 | m_roleSlots | `tagRoleSlot[64]` |
| Scene | 0xe0e0 | m_nTodo_e0e0 | `int` |
| Scene | 0xe0e4 | m_roles | `Role[50]` |
| SceneInfo | 0x0 | cityname | `char[32]` |
| SceneInfo | 0x20 | name | `char[32]` |
| SceneInfo | 0x40 | mdl | `char[32]` |
| SceneInfo | 0x60 | type | `SCENE_TYPE` |
| SceneInfo | 0x64 | lightmap | `DWORD` |
| SceneInfo | 0x68 | skybox | `DWORD` |
| SceneInfo | 0x6c | nCount | `int` |
| SceneInfo | 0x70 | pBuffer | `float *` |
| SceneInfo | 0x74 | fScale | `float` |
| SceneInfo | 0x78 | bFlag | `unsigned char` |
| SceneInfo | 0x7c | fResult | `float` |
| SceneInfo | 0x80 | nFlag | `int` |
| SceneMap | 0x4 | m_width | `int` |
| SceneMap | 0x8 | m_height | `int` |
| SceneMap | 0xc | m_map | `BYTE *` |
| SceneMapObj | 0x10 | m_scene | `Scene *` |
| SceneMapPlayer | 0x10 | m_nLayerIndex | `int` |
| SceneMapPlayer | 0x100 | m_layer | `NavTileLayer *` |
| SceneMapPlayer | 0x104 | m_bBuild | `unsigned char` |
| SceneMapPlayer | 0x105 | m_szName | `char[128]` |
| SceneMapPlayer | 0x14 | m_playerpt | `tagPOINT` |
| SceneMapPlayer | 0x1c | m_playerfov | `tagRECT` |
| SceneMapPlayer | 0x2c | m_maxwidth | `int` |
| SceneMapPlayer | 0x30 | m_maxheight | `int` |
| SceneMapPlayer | 0x34 | m_tex | `gbTexture *` |
| SceneMapPlayer | 0x38 | m_img | `gbImage2D` |
| SceneMgr | 0x0 | m_pGfxMgr | `gbGfxManager *` |
| SceneMgr | 0x14 | m_pAlphaEffect | `gbRenderEffect *` |
| SceneMgr | 0x1428 | m_nTodo_1428 | `int` |
| SceneMgr | 0x142c | m_nTodo_142C | `int` |
| SceneMgr | 0x160e | m_nTodo_160E | `unsigned char` |
| SceneMgr | 0x18 | m_pCamera | `gbCamera *` |
| SceneMgr | 0x1c | m_aSceneSlots | `float` |
| SceneMgr | 0x20 | m_nTodo_020 | `float[12]` |
| SceneMgr | 0x4 | m_pSceneRoot | `gbSceneGraph *` |
| SceneMgr | 0x50 | m_PlayerAtts | `PlayerAtts` |
| SceneMgr | 0x560 | m_RenderBuffer | `int[12]` |
| SceneMgr | 0x8 | m_pAddEffect2 | `gbRenderEffect *` |
| SceneMgr | 0xc | m_pAlphaEffect2 | `gbRenderEffect *` |
| SceneMgr | 0xc5d4 | _unkC5D4 | `char[4]` |
| SceneMgr | 0xc5dc | m_pScriptCtrl | `PalScriptMgr *` |
| SceneMgr | 0xd04c | m_nField_D04C | `int` |
| SceneMgr | 0xd0d4 | m_nCollisionFlags | `int` |
| SceneMgr | 0xe0e0 | m_nRoleCount | `int` |
| SceneMgrCamBlock | 0x0 | _gap_000 | `char[84]` |
| SceneMgrCamBlock | 0x1fc | m_nUnlockDataEndFlag | `int` |
| SceneMgrCamBlock | 0x200 | m_nUnlockDataCount | `int` |
| SceneMgrCamBlock | 0x204 | m_MonsterUnlockTable | `int[60]` |
| SceneMgrCamBlock | 0x2f4 | m_nMonsterUnlockEndFlag | `int` |
| SceneMgrCamBlock | 0x2f8 | m_nCurrentScene | `int` |
| SceneMgrCamBlock | 0x2fc | m_pCameraScript | `PalScript *` |
| SceneMgrCamBlock | 0x54 | m_pScriptArrayEnd | `PalScript *` |
| SceneMgrCamBlock | 0x58 | m_nTodo_058 | `PalScript *` |
| SceneMgrCamBlock | 0x5c | m_pUIScript | `PalScript *` |
| SceneMgrCamBlock | 0x60 | m_pScriptArrayEndSub | `PalScript *` |
| SceneMgrCamBlock | 0x64 | m_nUnlockDataOffset | `int` |
| SceneMgrCamBlock | 0x68 | m_nUnlockDataLen | `int` |
| SceneMgrCamBlock | 0x6c | m_RoleUnlockData | `int[100]` |
| SceneObj | 0x130 | mVelocity | `gbVec3D` |
| SceneObj | 0x13c | mTime | `float` |
| SceneObj | 0x140 | mStorePos | `gbVec3D` |
| SceneObj | 0x14c | mRetrorse | `int` |
| SceneObj | 0x150 | mTouchCounter | `int` |
| SceneObj | 0x154 | m_iState | `int` |
| SceneObj | 0x158 | m_bCVDOver | `unsigned char` |
| SceneObj | 0x15c | mOBBox | `gbOBBox` |
| SceneObj | 0x1a8 | m_pObjMsgBuffer | `char[256]` |
| SceneObj | 0x2a8 | m_pObjMsgBuffer2 | `char[256]` |
| SceneObj | 0x3a8 | m_renderpos | `gbVec3D` |
| SceneObj | 0x3b4 | m_subobj | `int` |
| SceneObj | 0x3d8 | m_mdl | `MyMdl` |
| SceneObj | 0x42c | m_info | `ObjectInfo` |
| SceneObj | 0x44 | m_fTimerLimit | `int` |
| SceneObj | 0x4c | _SaveTaskInfo | `SaveTask` |
| SceneObj | 0x58 | m_fTime | `float` |
| SceneObj | 0x5c | m_fDeltaTime | `float` |
| SceneObj | 0x60 | m_fTimeScale | `float` |
| SceneObj | 0x64 | m_deltatime | `float` |
| SceneObj | 0x68 | m_bLockPropUI | `int` |
| SceneObj | 0x688 | m_path | `PathObj *` |
| SceneObj | 0x68c | m_pmap | `SceneMapObj *` |
| SceneObj | 0x690 | m_mapindex | `unsigned char` |
| SceneObj | 0x694 | m_pushboxdir | `int` |
| SceneObj | 0x698 | m_maprect | `tagRECT` |
| SceneObj | 0x6a8 | m_liftrole | `int` |
| SceneObj | 0x6ac | m_common | `std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >` |
| SceneObj | 0x6c | m_bLockCamera | `unsigned char` |
| SceneObj | 0x6dc | m_snd | `gbSound3DNode *` |
| SceneObj | 0x6e0 | m_radius | `float` |
| SceneObj | 0x6e4 | m_runscript | `PalScript *` |
| SceneObj | 0x6e8 | m_fRotateX | `float` |
| SceneObj | 0x6ec | m_fRotateY | `float` |
| SceneObj | 0x6f0 | m_fRotateZ | `float` |
| SceneObj | 0x6f4 | m_fParam | `float` |
| SceneObj | 0x70 | m_bProcessLinkObj | `int` |
| SceneObj | 0x74 | m_bCallProcessGroupObj | `int` |
| SceneObj | 0x78 | m_bMainGroupObj | `int` |
| SceneObj | 0x7c | dwEffGroupRunningID | `unsigned int` |
| SceneObj | 0x80 | bCGObj | `unsigned char` |
| SceneObj | 0x81 | sCGSHELF | `char[64]` |
| SceneObj | 0xc4 | rCGSelfArea | `tagRECT` |
| SceneObj | 0xd4 | rTouchAreaCG | `tagRECT` |
| SceneObj | 0xe4 | fLastTime | `float` |
| SceneObj | 0xe8 | mParam | `subPARAM` |
| SceneObjParam | 0x0 | tmpVEC | `gbVec3D[8]` |
| SceneObjParam | 0x60 | mLinkObj | `SceneObj *` |
| SceneObjParam | 0x64 | mRole | `Role *` |
| SceneObjParam | 0x68 | mInfo | `ObjectInfo` |
| SceneObjScript | 0x0 | type | `BYTE` |
| SceneObjScript | 0x4 | objscript | `PalScript *` |
| SceneObjScript | 0x8 | obj | `SceneObj *` |
| SceneObj_Common_State | 0x0 | _tail_000 | `char[4]` |
| SceneObj_SubObj | 0x0 | _tail_000 | `char[36]` |
| SceneProp | 0x0 | pGeom | `gbGeomNode *` |
| SceneProp | 0x14 | fCurTime | `float` |
| SceneProp | 0x18 | fValidTime | `float` |
| SceneProp | 0x1c | bCountTime | `BYTE` |
| SceneProp | 0x1d | bPopFling | `BYTE` |
| SceneProp | 0x20 | vecFling | `gbVec3D` |
| SceneProp | 0x2c | lastFling | `gbVec3D` |
| SceneProp | 0x38 | rotFling | `gbVec3D` |
| SceneProp | 0x4 | rect | `tagRECT` |
| SceneProp | 0x44 | bCollide | `BYTE` |
| SceneProp | 0x48 | ID | `DWORD` |
| SceneProp | 0x4c | bNeedParabola | `BYTE` |
| SceneProp | 0x50 | nFlag | `int` |
| SceneProp | 0x54 | bValid | `BYTE` |
| SceneProp | 0x58 | parabola | `ParabolaCalculator` |
| SceneVisNode | 0x0 | _tail_000 | `char[8]` |
| ScreenEffect | 0x10 | m_age | `float` |
| ScreenEffect | 0x14 | m_hold | `BYTE` |
| ScreenEffect | 0x8 | m_nType | `int` |
| ScreenEffect | 0xc | m_life | `int` |
| ScreenEffectMgr | 0x0 | m_pVtable | `void*` |
| ScreenEffectMgr | 0x20 | m_fadeOut | `ScreenFadeOut` |
| ScreenEffectMgr | 0x38 | m_fadeWhite | `ScreenFadeWhite` |
| ScreenEffectMgr | 0x4 | m_fadeIn | `ScreenFadeIn` |
| ScreenEffectMgr | 0x50 | m_fadeWhite2 | `ScreenFadeWhite2` |
| ScreenEffectMgr | 0x68 | m_activeQueue | `char[4]` |
| ScreenEffectMgr | 0x6c | m_pAllocBlock | `void *` |
| ScreenEffectMgr | 0x70 | m_pAllocBlockEnd | `void *` |
| ScreenEffectMgr | 0x74 | m_pAllocPos | `void *` |
| ScreenEffectMgr | 0x78 | m_pAllocSlot | `void *` |
| ScreenEffectMgr | 0x7c | m_pAllocRest | `void *` |
| ScreenEffectMgr | 0x80 | m_nAllocFlag1 | `int` |
| ScreenEffectMgr | 0x84 | m_nAllocFlag2 | `int` |
| ScreenEffectMgr | 0x88 | m_fAllocFactor | `int` |
| ScreenEffectMgr | 0x8c | m_pEffect | `char *` |
| ScreenEffectMgr | 0x94 | m_nEffectCount | `int` |
| ScreenEffectNode | 0xa4 | m_pTexture | `gbTexture *` |
| ScreenEffectNode | 0xa8 | m_pRenderEffect | `gbRenderEffect *` |
| ScreenFadeIn | 0x18 | m_first | `int` |
| ScriptCounter | 0x0 | nMaxCount | `int` |
| ScriptCounter | 0x4 | nState | `int` |
| ScriptCounter | 0x8 | nCurCount | `int` |
| ScriptCounter | 0xc | nResourceID | `int` |
| ScriptData | 0x0 | m_ID | `WORD` |
| ScriptData | 0x104 | m_RestPrice | `int` |
| ScriptData | 0x108 | m_Rest | `char[256]` |
| ScriptData | 0x2 | m_Name | `char[256]` |
| ScriptData | 0x208 | m_Enough | `char[256]` |
| ScriptData | 0x308 | m_NoEnough | `char[256]` |
| ScriptData | 0x408 | m_RestEnd | `char[256]` |
| ScriptHelper | 0x0 | _tail_000 | `char[4]` |
| ScriptObj | 0x0 | _tail_000 | `char[4]` |
| ScriptPoolPage | 0x0 | p_starting_alloc_map | `BYTE *` |
| ScriptPoolPage | 0x100 | alloc_blocks | `char[256]` |
| ScriptPoolPage | 0x4 | free_paras_at_start | `UINT` |
| ScriptPoolPage | 0x8 | alloc_map | `unsigned char[241]` |
| ScriptPoolPage | 0xf9 | reserved | `unsigned char[7]` |
| ScriptSystem | 0x0 | m_nSlotID | `int` |
| ScriptSystem | 0x10c | m_nTodo_10C | `int` |
| ScriptSystem | 0x14 | m_nTodo_014 | `float` |
| ScriptSystem | 0x18 | m_nTodo_018 | `float` |
| ScriptSystem | 0x1c | m_nTodo_01C | `int` |
| ScriptSystem | 0x1c0 | m_nTodo_1C0 | `int` |
| ScriptSystem | 0x20 | m_nTodo_020 | `int` |
| ScriptSystem | 0x21f0 | m_nSaveRot_x | `float` |
| ScriptSystem | 0x21f4 | m_nSaveRot_y | `float` |
| ScriptSystem | 0x21f8 | m_nSaveRot_z | `float` |
| ScriptSystem | 0x21fc | m_nSaveDir | `int` |
| ScriptSystem | 0x24 | m_nSerialFlag | `int` |
| ScriptSystem | 0x274 | m_nActionID | `int` |
| ScriptSystem | 0x278 | m_bActive | `int` |
| ScriptSystem | 0x27c | m_nTodo_27C | `int` |
| ScriptSystem | 0x28 | m_nTodo_28 | `int` |
| ScriptSystem | 0x2a8 | m_Object3D | `int` |
| ScriptSystem | 0x36d | m_nTodo_36D | `unsigned char` |
| ScriptSystem | 0x384 | m_pScriptEvent | `int` |
| ScriptSystem | 0x388 | m_nEventParam | `int` |
| ScriptSystem | 0x38d | m_bOpcodeFlag | `unsigned char` |
| ScriptSystem | 0x38e | m_bExecFlag | `unsigned char` |
| ScriptSystem | 0x38f | m_bBlockFlag | `unsigned char` |
| ScriptSystem | 0x4 | m_vPos_x | `float` |
| ScriptSystem | 0x43c | m_nTodo_43C | `int` |
| ScriptSystem | 0x4f0 | m_nActionState | `int` |
| ScriptSystem | 0x4f4 | m_nMoveMode | `int` |
| ScriptSystem | 0x504 | m_nSceneState | `int` |
| ScriptSystem | 0x510 | m_vSavePos1_x | `float` |
| ScriptSystem | 0x514 | m_vSavePos1_y | `float` |
| ScriptSystem | 0x518 | m_vSavePos1_z | `float` |
| ScriptSystem | 0x51c | m_vSrcPos_x | `float` |
| ScriptSystem | 0x520 | m_vSrcPos_y | `float` |
| ScriptSystem | 0x524 | m_vSrcPos_z | `float` |
| ScriptSystem | 0x528 | m_vMoveDir_x | `float` |
| ScriptSystem | 0x52c | m_vMoveDir_y | `float` |
| ScriptSystem | 0x530 | m_vMoveDir_z | `float` |
| ScriptSystem | 0x540 | m_vTargetPos | `float` |
| ScriptSystem | 0x544 | m_fObjects | `float` |
| ScriptSystem | 0x548 | m_fTargetDir | `float` |
| ScriptSystem | 0x56c | m_nTodo_56C | `int` |
| ScriptSystem | 0x5bc | m_nTodo_5BC | `int` |
| ScriptSystem | 0x5c0 | m_nTodo_5C0 | `int` |
| ScriptSystem | 0x5c4 | m_nTodo_5C4 | `int` |
| ScriptSystem | 0x5c8 | m_nSubObjBase | `int` |
| ScriptSystem | 0x68 | m_szFmtBuf | `char[40]` |
| ScriptSystem | 0x8 | m_vPos_y | `float` |
| ScriptSystem | 0x90 | m_nMoveState | `int` |
| ScriptSystem | 0x94 | m_vRot_x | `float` |
| ScriptSystem | 0x98 | m_vRot_y | `float` |
| ScriptSystem | 0x9c | m_vRot_z | `float` |
| ScriptSystem | 0xa0 | m_vDir_x | `float` |
| ScriptSystem | 0xa4 | m_vDir_y | `float` |
| ScriptSystem | 0xa8 | m_vDir_z | `float` |
| ScriptSystem | 0xb0 | m_nTodo_0B0 | `int` |
| ScriptSystem | 0xc | m_vPos_z | `float` |
| ScriptSystem | 0xc8 | m_nTodo_0C8 | `int` |
| ScriptSystem | 0xd0 | m_nTodo_0D0 | `int` |
| ScriptSystemData | 0x0 | m_mapPlayer | `SceneMapPlayer[4]` |
| ScriptSystemData | 0x1000 | m_nCmdParam23 | `short` |
| ScriptSystemData | 0x1004 | m_nTodo_1004 | `int` |
| ScriptSystemData | 0x1008 | m_nTodo_1008 | `int` |
| ScriptSystemData | 0x100c | m_bScriptFlag | `unsigned char` |
| ScriptSystemData | 0x1010 | m_CmdObjArray0 | `PtrArray` |
| ScriptSystemData | 0x1020 | m_nCmdParam24 | `short` |
| ScriptSystemData | 0x1024 | m_nCmdParam25 | `int` |
| ScriptSystemData | 0x1028 | m_nTodo_1028 | `unsigned char` |
| ScriptSystemData | 0x1029 | m_bCmdFlag6 | `unsigned char` |
| ScriptSystemData | 0x1030 | m_nScriptMode | `int` |
| ScriptSystemData | 0x1034 | m_nTodo_1034 | `int` |
| ScriptSystemData | 0x1038 | m_bCmdFlag7 | `unsigned char` |
| ScriptSystemData | 0x1039 | m_bCmdFlag8 | `unsigned char` |
| ScriptSystemData | 0x103a | m_bCmdFlag9 | `unsigned char` |
| ScriptSystemData | 0x1040 | m_nCmdParam26 | `short` |
| ScriptSystemData | 0x1044 | m_nCmdParam27 | `int` |
| ScriptSystemData | 0x1048 | m_nScriptResult | `int` |
| ScriptSystemData | 0x104c | m_nTodo_104C | `char *` |
| ScriptSystemData | 0x1050 | m_nTodo_1050 | `short` |
| ScriptSystemData | 0x1054 | m_nCmdResult | `int` |
| ScriptSystemData | 0x1058 | m_bCmdSuccess | `unsigned char` |
| ScriptSystemData | 0x1059 | m_bCmdError | `unsigned char` |
| ScriptSystemData | 0x1060 | m_nCmdExtra1 | `short` |
| ScriptSystemData | 0x1064 | m_nCmdExtra2 | `int` |
| ScriptSystemData | 0x1068 | m_bCmdExtraFlag | `unsigned char` |
| ScriptSystemData | 0x1070 | m_nCmdExtra3 | `short` |
| ScriptSystemData | 0x1074 | m_nCmdExtra4 | `int` |
| ScriptSystemData | 0x1078 | m_bCmdExtraFlag2 | `unsigned char` |
| ScriptSystemData | 0x1080 | m_nField_1080 | `short` |
| ScriptSystemData | 0x1084 | m_nField_1084 | `int` |
| ScriptSystemData | 0x1090 | m_nField_1090 | `short` |
| ScriptSystemData | 0x1094 | m_nField_1094 | `int` |
| ScriptSystemData | 0x10a0 | m_nField_10A0 | `short` |
| ScriptSystemData | 0x10a4 | m_nField_10A4 | `int` |
| ScriptSystemData | 0x10a8 | m_nField_10A8 | `int` |
| ScriptSystemData | 0x10b0 | m_nField_10B0 | `short` |
| ScriptSystemData | 0x10b4 | m_nField_10B4 | `int` |
| ScriptSystemData | 0x10b8 | m_nField_10B8 | `unsigned char` |
| ScriptSystemData | 0x10c0 | m_nField_10C0 | `short` |
| ScriptSystemData | 0x10c4 | m_nField_10C4 | `int` |
| ScriptSystemData | 0x10c8 | m_nField_10C8 | `unsigned char` |
| ScriptSystemData | 0x10d0 | m_nField_10D0 | `short` |
| ScriptSystemData | 0x10d4 | m_nField_10D4 | `int` |
| ScriptSystemData | 0x10d8 | m_nField_10D8 | `int` |
| ScriptSystemData | 0x10e0 | m_nField_10E0 | `short` |
| ScriptSystemData | 0x10e4 | m_nField_10E4 | `int` |
| ScriptSystemData | 0x10e8 | m_nField_10E8 | `unsigned char` |
| ScriptSystemData | 0x10e9 | m_nField_10E9 | `unsigned char` |
| ScriptSystemData | 0x10f0 | m_nField_10F0 | `short` |
| ScriptSystemData | 0x10f4 | m_nField_10F4 | `int` |
| ScriptSystemData | 0x10f8 | m_nField_10F8 | `unsigned char` |
| ScriptSystemData | 0x10f9 | m_nField_10F9 | `unsigned char` |
| ScriptSystemData | 0x1100 | m_nField_1100 | `short` |
| ScriptSystemData | 0x1104 | m_nField_1104 | `int` |
| ScriptSystemData | 0x1108 | m_nField_1108 | `unsigned char` |
| ScriptSystemData | 0x1109 | m_nField_1109 | `unsigned char` |
| ScriptSystemData | 0x110a | m_nField_110A | `unsigned char` |
| ScriptSystemData | 0x1110 | m_nField_1110 | `short` |
| ScriptSystemData | 0x1114 | m_nField_1114 | `int` |
| ScriptSystemData | 0x1118 | m_nField_1118 | `unsigned char` |
| ScriptSystemData | 0x1119 | m_nField_1119 | `unsigned char` |
| ScriptSystemData | 0x111a | m_nField_111A | `unsigned char` |
| ScriptSystemData | 0x111b | m_nField_111B | `unsigned char` |
| ScriptSystemData | 0x111c | m_nField_111C | `int` |
| ScriptSystemData | 0x1120 | m_nField_1120 | `short` |
| ScriptSystemData | 0x1124 | m_nField_1124 | `int` |
| ScriptSystemData | 0x1128 | m_nField_1128 | `unsigned char` |
| ScriptSystemData | 0x1129 | m_nField_1129 | `unsigned char` |
| ScriptSystemData | 0x112a | m_nField_112A | `unsigned char` |
| ScriptSystemData | 0x1138 | m_nField_1138 | `unsigned char` |
| ScriptSystemData | 0x1139 | m_nField_1139 | `unsigned char` |
| ScriptSystemData | 0x113a | m_nField_113A | `unsigned char` |
| ScriptSystemData | 0x113b | m_nField_113B | `unsigned char` |
| ScriptSystemData | 0x113c | m_nField_113C | `unsigned char` |
| ScriptSystemData | 0x113d | m_nField_113D | `unsigned char` |
| ScriptSystemData | 0x1140 | m_nField_1140 | `short` |
| ScriptSystemData | 0x1144 | m_nField_1144 | `int` |
| ScriptSystemData | 0x1148 | m_nField_1148 | `int` |
| ScriptSystemData | 0x1150 | m_CmdTable | `int[852]` |
| ScriptSystemData | 0x1ea0 | m_nTodo_D8D1B8 | `int` |
| ScriptSystemData | 0x1ea4 | m_nTodo_D8D1BC | `unsigned char` |
| ScriptSystemData | 0x1ea5 | m_nTodo_D8D1BD | `unsigned char` |
| ScriptSystemData | 0x1ea6 | m_nTodo_D8D1BE | `unsigned char` |
| ScriptSystemData | 0x1ea7 | m_nTodo_D8D1BF | `unsigned char` |
| ScriptSystemData | 0x1eac | m_nTodo_D8D1C4 | `unsigned short` |
| ScriptSystemData | 0x1eb0 | m_nTodo_D8D1C8 | `int` |
| ScriptSystemData | 0x1eb4 | m_nTodo_D8D1CC | `unsigned char` |
| ScriptSystemData | 0x1eb5 | m_nTodo_D8D1CD | `unsigned char` |
| ScriptSystemData | 0x1eb6 | m_nTodo_D8D1CE | `unsigned char` |
| ScriptSystemData | 0x1eb7 | m_nTodo_D8D1CF | `unsigned char` |
| ScriptSystemData | 0x1ebc | m_nTodo_D8D1D4 | `unsigned short` |
| ScriptSystemData | 0x1f20 | m_nTodo_D8D238 | `int` |
| ScriptSystemData | 0x1f24 | m_nTodo_D8D23C | `unsigned char` |
| ScriptSystemData | 0x1f2c | m_nTodo_D8D244 | `unsigned short` |
| ScriptSystemData | 0x20f0 | m_nTodo_D8D408 | `int` |
| ScriptSystemData | 0x20f4 | m_nTodo_D8D40C | `unsigned char` |
| ScriptSystemData | 0x20fc | m_nTodo_D8D414 | `unsigned short` |
| ScriptSystemData | 0x2100 | m_nTodo_D8D418 | `int` |
| ScriptSystemData | 0x2104 | m_nTodo_D8D41C | `unsigned char` |
| ScriptSystemData | 0x210c | m_nTodo_D8D424 | `unsigned short` |
| ScriptSystemData | 0x27d0 | m_nTodo_D8DAE8 | `int` |
| ScriptSystemData | 0x27d4 | m_nTodo_D8DAEC | `unsigned char` |
| ScriptSystemData | 0x27d5 | m_nTodo_D8DAED | `unsigned char` |
| ScriptSystemData | 0x27d6 | m_nTodo_D8DAEE | `unsigned char` |
| ScriptSystemData | 0x27d7 | m_nTodo_D8DAEF | `unsigned char` |
| ScriptSystemData | 0x27d8 | m_nTodo_D8DAF0 | `unsigned char` |
| ScriptSystemData | 0x27d9 | m_nTodo_D8DAF1 | `unsigned char` |
| ScriptSystemData | 0x27da | m_nTodo_D8DAF2 | `unsigned char` |
| ScriptSystemData | 0x27dc | m_nTodo_D8DAF4 | `unsigned short` |
| ScriptSystemData | 0x620 | m_scriptArray | `PtrArray` |
| ScriptSystemData | 0x64c | m_nArrData_2C | `float` |
| ScriptSystemData | 0x650 | m_nArrData_30 | `int` |
| ScriptSystemData | 0x678 | m_nArrData | `int[20]` |
| ScriptSystemData | 0x8d4 | m_nGameMode | `int` |
| ScriptSystemData | 0x8d8 | m_nTodo_8D8 | `float` |
| ScriptSystemData | 0x8dc | m_nTodo_8DC | `float` |
| ScriptSystemData | 0x8e0 | m_nTodo_8E0 | `float` |
| ScriptSystemData | 0x8e4 | m_nTodo_8E4 | `float` |
| ScriptSystemData | 0x8e8 | m_nTodo_8E8 | `float` |
| ScriptSystemData | 0x8ec | m_nTodo_8EC | `float` |
| ScriptSystemData | 0x8f0 | m_nTodo_8F0 | `int` |
| ScriptSystemData | 0x8f4 | m_nTodo_8F4 | `int` |
| ScriptSystemData | 0x8f8 | m_nTodo_8F8 | `int` |
| ScriptSystemData | 0x8fc | m_nTodo_8FC | `int` |
| ScriptSystemData | 0x900 | m_nTodo_900 | `int` |
| ScriptSystemData | 0x94c | m_fScriptTimer1 | `float` |
| ScriptSystemData | 0x950 | m_fScriptTimer2 | `float` |
| ScriptSystemData | 0x978 | m_nScriptDelay | `int` |
| ScriptSystemData | 0x97c | m_fScriptSpeed | `float` |
| ScriptSystemData | 0xbac | m_g_fTimeDelta | `float` |
| ScriptSystemData | 0xbd4 | m_nTodo_D8BEEC | `RoleSystem *` |
| ScriptSystemData | 0xc04 | m_nVarPoolSize | `int` |
| ScriptSystemData | 0xc08 | m_nVarCount | `int` |
| ScriptSystemData | 0xc38 | m_nVarFlags | `int` |
| ScriptSystemData | 0xd38 | m_nArgDef_0 | `int` |
| ScriptSystemData | 0xd3c | m_nArgDef_1 | `int` |
| ScriptSystemData | 0xd44 | m_nArgDef_2 | `int` |
| ScriptSystemData | 0xd48 | m_nArgDef_3 | `int` |
| ScriptSystemData | 0xd4c | m_nArgDef_4 | `int` |
| ScriptSystemData | 0xd50 | m_nArgDef_5 | `int` |
| ScriptSystemData | 0xd54 | m_nArgDef_6 | `int` |
| ScriptSystemData | 0xd58 | m_nArgDef_7 | `int` |
| ScriptSystemData | 0xd5c | m_nArgDef_8 | `int` |
| ScriptSystemData | 0xd60 | m_nArgDef_9 | `int` |
| ScriptSystemData | 0xd64 | m_nArgDef_10 | `int` |
| ScriptSystemData | 0xd68 | m_nField_D68 | `short` |
| ScriptSystemData | 0xd6c | m_nArgDef_11 | `int` |
| ScriptSystemData | 0xd74 | m_nArgDef_12 | `int` |
| ScriptSystemData | 0xd78 | m_nArgDef_13 | `int` |
| ScriptSystemData | 0xd7c | m_nArgDef_14 | `int` |
| ScriptSystemData | 0xd80 | m_nArgDef_15 | `int` |
| ScriptSystemData | 0xd84 | m_nArgDef_16 | `int` |
| ScriptSystemData | 0xd88 | m_nField_D88 | `short` |
| ScriptSystemData | 0xd8c | m_nArgDef_17 | `int` |
| ScriptSystemData | 0xd94 | m_nArgDef_18 | `int` |
| ScriptSystemData | 0xd98 | m_nArgDef_19 | `int` |
| ScriptSystemData | 0xd9c | m_nArgDef_20 | `int` |
| ScriptSystemData | 0xda0 | m_nArgDef_21 | `int` |
| ScriptSystemData | 0xda4 | m_nArgDef_22 | `int` |
| ScriptSystemData | 0xda8 | m_nField_DA8 | `short` |
| ScriptSystemData | 0xdac | m_nArgDef_23 | `int` |
| ScriptSystemData | 0xdb0 | m_nArgDef_24 | `int` |
| ScriptSystemData | 0xdb4 | m_nArgDef_25 | `int` |
| ScriptSystemData | 0xdb8 | m_nArgDef_26 | `int` |
| ScriptSystemData | 0xdc4 | m_nArgDef_27 | `unsigned char` |
| ScriptSystemData | 0xdcc | m_nArgDef_28 | `int` |
| ScriptSystemData | 0xdd4 | m_nArgDef_29 | `int` |
| ScriptSystemData | 0xdd8 | m_nArgDef_30 | `int` |
| ScriptSystemData | 0xde4 | m_nArgDef_31 | `int` |
| ScriptSystemData | 0xdec | m_nArgDef_32 | `int` |
| ScriptSystemData | 0xdf0 | m_nArgDef_33 | `int` |
| ScriptSystemData | 0xe94 | m_String | `char[96]` |
| ScriptSystemData | 0xef4 | m_nCmdParamCount | `int` |
| ScriptSystemData | 0xf04 | m_nCmdIndex | `int` |
| ScriptSystemData | 0xf08 | m_nCmdType | `int` |
| ScriptSystemData | 0xf10 | m_nCmdSubType | `short` |
| ScriptSystemData | 0xf14 | m_nCmdParam1 | `int` |
| ScriptSystemData | 0xf18 | m_nCmdParam2 | `int` |
| ScriptSystemData | 0xf20 | m_nCmdParam3 | `short` |
| ScriptSystemData | 0xf24 | m_nCmdParam4 | `int` |
| ScriptSystemData | 0xf28 | m_nCmdParam5 | `int` |
| ScriptSystemData | 0xf30 | m_nCmdParam6 | `short` |
| ScriptSystemData | 0xf34 | m_nCmdParam7 | `int` |
| ScriptSystemData | 0xf40 | m_nCmdParam8 | `short` |
| ScriptSystemData | 0xf44 | m_nCmdParam9 | `int` |
| ScriptSystemData | 0xf48 | m_nCmdParam10 | `int` |
| ScriptSystemData | 0xf70 | m_nCmdParam11 | `short` |
| ScriptSystemData | 0xf78 | m_bCmdFlag1 | `unsigned char` |
| ScriptSystemData | 0xf80 | m_nCmdParam12 | `short` |
| ScriptSystemData | 0xf84 | m_nCmdParam13 | `int` |
| ScriptSystemData | 0xf88 | m_bCmdFlag2 | `unsigned char` |
| ScriptSystemData | 0xf90 | m_nCmdParam14 | `short` |
| ScriptSystemData | 0xf94 | m_nScriptBlockCount | `int` |
| ScriptSystemData | 0xf98 | m_pCurrentBlock | `PalScript *` |
| ScriptSystemData | 0xfa0 | m_nCmdFA0 | `short` |
| ScriptSystemData | 0xfa4 | m_nScriptState | `int` |
| ScriptSystemData | 0xfa8 | m_nCmdFA8 | `int` |
| ScriptSystemData | 0xfac | m_pScriptData | `char *` |
| ScriptSystemData | 0xfb0 | m_nTodo_FB0 | `char[32]` |
| ScriptSystemData | 0xfd0 | m_nCmdFD0 | `short` |
| ScriptSystemData | 0xfd4 | m_nCmdParam19 | `int` |
| ScriptSystemData | 0xfd8 | m_bCmdFlag4 | `unsigned char` |
| ScriptSystemData | 0xfe0 | m_nCmdParam20 | `short` |
| ScriptSystemData | 0xfe4 | m_nCmdParam21 | `int` |
| ScriptSystemData | 0xfe8 | m_bCmdFlag5 | `unsigned char` |
| ScriptSystemData | 0xff0 | m_pCmdTableFF0 | `char *` |
| ScriptSystemData | 0xff4 | m_nCmdParam22 | `int` |
| ScriptVM | 0x10 | m_bufReadPtr | `int` |
| ScriptVM | 0x100 | m_nPauseState | `int` |
| ScriptVM | 0x14 | m_bufWritePtr | `int` |
| ScriptVM | 0x20 | m_nTodo_20 | `int *` |
| ScriptVM | 0x31c | m_pCmdList | `UIWnd *` |
| ScriptVM | 0x33c | m_nPathMode | `int` |
| ScriptVM | 0x340 | m_fPathStartX | `float` |
| ScriptVM | 0x344 | m_fPathStartY | `float` |
| ScriptVM | 0x348 | m_fPathStartZ | `float` |
| ScriptVM | 0x34c | m_nPathParam | `int` |
| ScriptVM | 0x350 | m_fPathEndX | `float` |
| ScriptVM | 0x354 | m_fPathEndY | `float` |
| ScriptVM | 0x358 | m_nTodo_358 | `char *` |
| ScriptVM | 0x35c | m_pPathCurrent | `char *` |
| ScriptVM | 0x360 | m_pPathKeys | `char *` |
| ScriptVM | 0x364 | m_nPathKeyCount | `int` |
| ScriptVM | 0x368 | m_nPathStep | `int` |
| ScriptVM | 0x4 | m_bufHead | `int` |
| ScriptVM | 0x8 | m_bufTail | `int` |
| ScriptVM | 0xa0 | m_nTodo_0A0 | `int` |
| ScriptVM | 0xa4 | m_nTodo_0A4 | `int` |
| ScriptVM | 0xa8 | m_nTodo_0A8 | `int` |
| ScriptVM | 0xc | m_bufCapacity | `int` |
| ScriptVM | 0xdc | m_nTodo_0DC | `int` |
| ScriptVM | 0xe0 | m_nTodo_0E0 | `void *` |
| ScriptVM | 0xf4 | m_nTodo_0F4 | `unsigned char` |
| ScriptWaitFrm | 0x8 | m_frm | `PAL3_FRAME` |
| SkillData | 0x0 | num | `int` |
| SkillData | 0x4 | m_Data | `char[256]` |
| SkyBox | 0x20 | m_vHalfSize | `gbVec3D` |
| SkyBox | 0x2c | m_pEffect | `gbRenderEffect *` |
| SkyBox | 0x30 | m_pEffectNormal | `gbRenderEffect *` |
| SkyBox | 0x34 | m_bValid | `BYTE` |
| SkyBox | 0x4 | m_fogColor | `gbColorQuad` |
| SkyBox | 0x8 | m_pTexture | `gbTexture *[6]` |
| SkyboxEff | 0x0 | m_pEffectNormal | `gbRenderEffect *` |
| SkyboxEff | 0x10 | m_fValidTime | `float` |
| SkyboxEff | 0x14 | m_fps | `float` |
| SkyboxEff | 0x18 | m_fSizeScale | `float` |
| SkyboxEff | 0x1c | m_nEffWidth | `float` |
| SkyboxEff | 0x20 | m_nEffHeight | `float` |
| SkyboxEff | 0x24 | m_eEffMode | `EffModeParam` |
| SkyboxEff | 0x30 | m_vHalfSize | `gbVec3D` |
| SkyboxEff | 0x3c | m_fTime | `float` |
| SkyboxEff | 0x4 | m_pEffTex | `SkyboxEffTex *` |
| SkyboxEff | 0x40 | m_fPassTime | `float` |
| SkyboxEff | 0x44 | m_nCurFrame | `int` |
| SkyboxEff | 0x48 | m_fWidth | `float` |
| SkyboxEff | 0x4c | m_fHeight | `float` |
| SkyboxEff | 0x50 | m_bIsTime | `BYTE` |
| SkyboxEff | 0x51 | m_bOver | `BYTE` |
| SkyboxEff | 0x52 | m_bValid | `BYTE` |
| SkyboxEff | 0x53 | m_bDelyTime | `BYTE` |
| SkyboxEff | 0x54 | m_fNoteTime | `float` |
| SkyboxEff | 0x58 | m_nameCrc | `DWORD` |
| SkyboxEff | 0x5c | m_pSkyboxEff | `gbRenderEffect *` |
| SkyboxEff | 0x60 | m_vRender | `gbVec3D[4]` |
| SkyboxEff | 0x8 | m_nFrameNum | `int` |
| SkyboxEff | 0xc | m_fWaitTime | `float` |
| SkyboxEffMgr | 0x0 | m_fSkyboxSize | `float` |
| SkyboxEffMgr | 0x4 | m_pEffArray | `char[256]` |
| SkyboxEffTex | 0x0 | m_pTex | `gbTexture *` |
| SoundAttachObj | 0x0 | p2d | `gbSound2DNode *` |
| SoundAttachObj | 0x4 | h2d | `_SAMPLE *` |
| SoundAttachObj | 0x8 | time | `UINT` |
| SoundContext | 0x0 | _tail_000 | `char[4]` |
| SoundItem | 0x0 | dwCRC | `DWORD` |
| SoundItem | 0x4 | node2 | `gbSound2DNode *` |
| SoundMgr | 0x11c | m_MusicTable | `TxtFile` |
| SoundMgr | 0x18 | m_nScriptLoop | `int` |
| SoundMgr | 0x1c | m_szSceneMusic | `char[256]` |
| SoundMgr | 0x328 | m_audiodrv | `gbAudioManager *` |
| SoundMgr | 0x32c | DEF3DMasterVol | `int` |
| SoundMgr | 0x330 | DEF2DMasterVol | `int` |
| SoundMgr | 0x334 | DEFMusicMasterVol | `float` |
| SoundMgr | 0x338 | m_bValidDetectSceneMusic | `BYTE` |
| SoundMgr | 0x33c | m_cbbuf | `std::vector<SoundItem,std::allocator<SoundItem> >` |
| SoundMgr | 0x34c | m_cbcursor | `int` |
| SoundMgr | 0x350 | m_Cpk | `CPK` |
| SoundMgr | 0x4 | m_bScriptMusic | `BYTE` |
| SoundMgr | 0x8 | m_szScriptMusic | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` |
| SoundSystem | 0x0 | _tail_000 | `char[4]` |
| StateUI | 0x10fc | stp_Effect | `UIStatic` |
| StateUI | 0x115d4 | m_par2 | `UIParticle[16][7]` |
| StateUI | 0x118 | m_IsMsg | `unsigned char` |
| StateUI | 0x119 | m_Is | `unsigned char[5]` |
| StateUI | 0x1194 | stp_Rect | `tagRECT` |
| StateUI | 0x11a4 | m_GameTime | `UIStatic` |
| StateUI | 0x120 | m_CtrlRole | `int` |
| StateUI | 0x123c | m_GameMoney | `UIStatic` |
| StateUI | 0x124 | m_IsActive | `unsigned char` |
| StateUI | 0x125 | m_IsCreateable | `unsigned char` |
| StateUI | 0x128 | m_Frame | `UIStatic` |
| StateUI | 0x12d4 | m_par | `UIParticle[16][7]` |
| StateUI | 0x1c0 | m_TimeMoney | `UIStatic` |
| StateUI | 0x218d4 | m_parRc | `tagRECT[7]` |
| StateUI | 0x21944 | _isParBtn | `unsigned char[7]` |
| StateUI | 0x2194c | _curParEffect | `int` |
| StateUI | 0x21950 | m_PortraitRc | `tagRECT` |
| StateUI | 0x21960 | m_Portrait | `UIStatic` |
| StateUI | 0x219f8 | m_TeamState | `UIStatic` |
| StateUI | 0x21a90 | m_Time | `UIStatic` |
| StateUI | 0x21b28 | m_Money | `UIStatic` |
| StateUI | 0x21bc0 | m_TeamStateRc | `tagRECT` |
| StateUI | 0x21bd0 | m_RoleState | `s_RoleState[5]` |
| StateUI | 0x258 | m_OutFrameT | `UIStatic` |
| StateUI | 0x268ec | m_State | `UIStatic[4]` |
| StateUI | 0x26b4c | m_Alignment | `UIStatic` |
| StateUI | 0x26be4 | m_AlignmentRc | `tagRECT` |
| StateUI | 0x26bf4 | m_Head | `UIStatic[5]` |
| StateUI | 0x26eec | m_HeadRc | `tagRECT[5]` |
| StateUI | 0x26f3c | m_TopFrame | `UIStatic` |
| StateUI | 0x26fd4 | m_LeaveHere | `UIButton` |
| StateUI | 0x2712c | m_LeaveRc | `tagRECT` |
| StateUI | 0x2713c | m_3DObj | `UI3DCtrl` |
| StateUI | 0x27270 | m_DlgEx | `MUIDialog` |
| StateUI | 0x277d8 | p_LineupUI | `LineupUI *` |
| StateUI | 0x277dc | p_MagicUI | `MagicUI *` |
| StateUI | 0x277e0 | p_mEquipUI | `MainEquipUI *` |
| StateUI | 0x277e4 | p_mPropUI | `MainPropUI *` |
| StateUI | 0x277e8 | p_SwordUI | `SwordUI *` |
| StateUI | 0x277ec | p_JusticeBookUI | `JusticeBookUI *` |
| StateUI | 0x277f0 | p_TaskBookUI | `TaskBookUI *` |
| StateUI | 0x277f4 | p_SystemUI | `SystemUI *` |
| StateUI | 0x277f8 | m_curRender | `int` |
| StateUI | 0x277fc | m_saveflag_note | `unsigned char` |
| StateUI | 0x277fd | m_isSeekSAVELOAD | `unsigned char` |
| StateUI | 0x27800 | m_test | `UIStatic` |
| StateUI | 0x27898 | pInterceptTex | `gbTexture *` |
| StateUI | 0x2789c | sv | `float` |
| StateUI | 0x278a0 | ev | `float` |
| StateUI | 0x278a4 | m_isExit | `unsigned char` |
| StateUI | 0x278a8 | m_SpecialPropItem | `s_SpecialPropItem[5]` |
| StateUI | 0x2f0 | m_OutFrameR | `UIStatic` |
| StateUI | 0x388 | m_OutFrameL | `UIStatic` |
| StateUI | 0x420 | m_OutFrameB | `UIStatic` |
| StateUI | 0x48 | m_isJusticeBook | `unsigned char` |
| StateUI | 0x4b8 | stp_BarL | `UIStatic` |
| StateUI | 0x550 | stp_BarM | `UIFlexBar` |
| StateUI | 0x5a4 | stp_BarR | `UIStatic` |
| StateUI | 0x63c | stp_State | `UIButton` |
| StateUI | 0x794 | stp_Magic | `UIButton` |
| StateUI | 0x8ec | stp_Equip | `UIButton` |
| StateUI | 0xa44 | stp_Prop | `UIButton` |
| StateUI | 0xb9c | stp_BattleArray | `UIButton` |
| StateUI | 0xcf4 | stp_TaskBook | `UIButton` |
| StateUI | 0xe4c | stp_System | `UIButton` |
| StateUI | 0xfa4 | stp_Exit | `UIButton` |
| String | 0x0 | _tail_000 | `char[4]` |
| StringTable | 0x0 | m_data | `char[16]` |
| SwitchVariable | 0x0 | m_switchlimit | `UINT` |
| SwordUI | 0x168 | m_ljsNum | `int` |
| SwordUI | 0x16c | m_ljsNumber | `UIStatic` |
| SwordUI | 0x16d20 | m_btnPar2 | `UIParticle[16][7]` |
| SwordUI | 0x20c | m_purgeEquipNum | `int` |
| SwordUI | 0x210 | m_purgeWeaponNum | `int` |
| SwordUI | 0x214 | m_avgWeaponWU | `int` |
| SwordUI | 0x218 | m_avgAdornWU | `int` |
| SwordUI | 0x21c | m_avgAdornFANG | `int` |
| SwordUI | 0x220 | m_avgDefFANG | `int` |
| SwordUI | 0x224 | m_adornNum | `int` |
| SwordUI | 0x228 | m_defNum | `int` |
| SwordUI | 0x22c | m_WSkill | `FightSkill[28]` |
| SwordUI | 0x27020 | m_btnParRc | `tagRECT[7]` |
| SwordUI | 0x27090 | _isParBtn | `unsigned char[7]` |
| SwordUI | 0x27098 | _curParEffect | `int` |
| SwordUI | 0x2709c | Sword_Name | `UIStatic` |
| SwordUI | 0x2713c | Sword_Att | `UIStatic` |
| SwordUI | 0x271dc | m_Ljs | `UIStatic` |
| SwordUI | 0x2727c | m_WulingCtrl | `UIStatic` |
| SwordUI | 0x2731c | m_Sword | `UI3DCtrl` |
| SwordUI | 0x27450 | m_ljs3D | `UI3DCtrl` |
| SwordUI | 0x27584 | m_SwordFrame | `UIStatic` |
| SwordUI | 0x27624 | m_SwordRemarkBk | `UIStatic` |
| SwordUI | 0x276c4 | m_SwordRemark | `UIStatic` |
| SwordUI | 0x27764 | m_Yjfx | `UIButton` |
| SwordUI | 0x278bc | m_RemarkRc | `tagRECT` |
| SwordUI | 0x278cc | m_SwordRemarkRc | `tagRECT` |
| SwordUI | 0x278dc | m_NoteSwordRemarkRc | `tagRECT` |
| SwordUI | 0x278ec | m_SwordDstX | `unsigned short` |
| SwordUI | 0x278ee | m_SwordNoteX | `unsigned short` |
| SwordUI | 0x278f0 | m_bSwordRemarkOut | `int` |
| SwordUI | 0x278f4 | mb_Positive | `UIButton[5]` |
| SwordUI | 0x27fac | ms_Positive | `UIStatic[5]` |
| SwordUI | 0x282cc | mb_Lunar | `UIButton[5]` |
| SwordUI | 0x28984 | ms_Lunar | `UIStatic[5]` |
| SwordUI | 0x28ca4 | ms_Perfect | `UIStatic[5]` |
| SwordUI | 0x28fc4 | m_CanCtrlBtn | `unsigned char` |
| SwordUI | 0x28fc8 | mb_Test | `UIButton` |
| SwordUI | 0x29120 | m_parSword | `UIParticle[168]` |
| SwordUI | 0x415a0 | m_parSwordRc | `tagRECT` |
| SwordUI | 0x415b0 | m_parPurge | `UIParticle[168]` |
| SwordUI | 0x48 | m_PurgeNum | `WuLing` |
| SwordUI | 0x554c | m_wskillNum | `int` |
| SwordUI | 0x5550 | m_IsMsg | `unsigned char` |
| SwordUI | 0x5554 | m_CtrlRole | `int` |
| SwordUI | 0x5558 | m_IsActive | `unsigned char` |
| SwordUI | 0x5559 | m_IsCreateable | `unsigned char` |
| SwordUI | 0x555a | m_IsLunar | `unsigned char` |
| SwordUI | 0x555b | m_is3dLunar | `unsigned char` |
| SwordUI | 0x555c | m_SelNum | `int` |
| SwordUI | 0x5560 | m_CurPage | `int` |
| SwordUI | 0x5564 | m_angle | `float` |
| SwordUI | 0x5568 | rot | `float` |
| SwordUI | 0x556c | m_Distribute | `S_Distribute[99]` |
| SwordUI | 0x58 | m_nBkWndX | `int` |
| SwordUI | 0x59a30 | m_PositiveBtn | `UIButton` |
| SwordUI | 0x59b88 | m_LunarBtn | `UIButton` |
| SwordUI | 0x59ce0 | Purge_rectA | `tagRECT[5]` |
| SwordUI | 0x59d30 | Purge_rectB | `tagRECT[5]` |
| SwordUI | 0x59d80 | dstRect | `tagRECT[5]` |
| SwordUI | 0x59dd0 | m_PurgeEffect | `PurgeEffect` |
| SwordUI | 0x59f7c | m_effTime | `TimeCtl` |
| SwordUI | 0x59f88 | m_bSwordMotion | `unsigned char` |
| SwordUI | 0x59f89 | m_bSwordEff | `unsigned char` |
| SwordUI | 0x59f8a | m_bSwordRot | `unsigned char` |
| SwordUI | 0x59f8b | m_bEff | `unsigned char` |
| SwordUI | 0x59f8c | m_curpar | `int` |
| SwordUI | 0x59f90 | m_swdTime | `TimeCtl` |
| SwordUI | 0x59f9c | m_Orthosize | `int` |
| SwordUI | 0x59fa0 | m_FinalOrthosize | `int` |
| SwordUI | 0x59fa4 | m_PURGEINFO | `_PURGE_INFO[11]` |
| SwordUI | 0x59ffc | m_SmallBar | `UIFlexBar` |
| SwordUI | 0x5a050 | m_BigBar | `UIFlexBar` |
| SwordUI | 0x5a0a4 | m_Pushbtn | `UIButton[5]` |
| SwordUI | 0x5a75c | m_equipFlag | `UIStatic` |
| SwordUI | 0x5a7fc | m_purgeFlag | `UIStatic` |
| SwordUI | 0x5a89c | m_ListTitle | `UIFlexBar` |
| SwordUI | 0x5a8f0 | m_EquipTitle | `UIStatic` |
| SwordUI | 0x5a990 | m_PurgeTitle | `UIStatic` |
| SwordUI | 0x5aa30 | m_ListTitlePurge | `UIStatic` |
| SwordUI | 0x5aad0 | m_ListFrame | `UIStatic` |
| SwordUI | 0x5ab70 | m_ListFramePurge | `UIStatic` |
| SwordUI | 0x5ac10 | m_ListGrid | `UIStatic[12]` |
| SwordUI | 0x5b390 | m_ListGridPurge | `UIStatic[12]` |
| SwordUI | 0x5b9c | FetchVal | `int` |
| SwordUI | 0x5ba0 | GuVal | `int` |
| SwordUI | 0x5ba4 | pStateUI | `StateUI *` |
| SwordUI | 0x5ba8 | m_FrameLine | `UIStatic` |
| SwordUI | 0x5bb10 | m_WeaponList | `UIListBox` |
| SwordUI | 0x5c | m_nBkWndY | `int` |
| SwordUI | 0x5c018 | m_ClothList | `UIListBox` |
| SwordUI | 0x5c48 | m_TimeMoney | `UIStatic` |
| SwordUI | 0x5c520 | m_HatList | `UIListBox` |
| SwordUI | 0x5ca28 | m_ShoesList | `UIListBox` |
| SwordUI | 0x5ce8 | stp_BarL | `UIStatic` |
| SwordUI | 0x5cf30 | m_AdornList | `UIListBox` |
| SwordUI | 0x5d438 | m_StuffList | `UIListBox` |
| SwordUI | 0x5d88 | stp_BarM | `UIStatic` |
| SwordUI | 0x5d940 | m_StrRc | `tagRECT` |
| SwordUI | 0x5d950 | m_EquipStr | `UIStatic` |
| SwordUI | 0x5d9f0 | m_StuffStr | `UIStatic` |
| SwordUI | 0x5da90 | m_GuVal | `UIStatic` |
| SwordUI | 0x5db30 | m_MsgRc | `tagRECT` |
| SwordUI | 0x5db40 | m_PurgeMsg | `UIStatic` |
| SwordUI | 0x5dbe0 | m_PurgeBottom | `UIFlexBar` |
| SwordUI | 0x5dc34 | m_BtnRc | `tagRECT` |
| SwordUI | 0x5dc44 | m_OK | `UIButton` |
| SwordUI | 0x5dd9c | m_Cancel | `UIButton` |
| SwordUI | 0x5def4 | m_SortEquipbyPrice | `UIButton` |
| SwordUI | 0x5e04c | m_SortEquipbyGu | `UIButton` |
| SwordUI | 0x5e1a4 | m_SortStuffbyPrice | `UIButton` |
| SwordUI | 0x5e28 | stp_BarR | `UIStatic` |
| SwordUI | 0x5e2fc | m_SortStuffbyGu | `UIButton` |
| SwordUI | 0x5e454 | m_SortState | `int` |
| SwordUI | 0x5e458 | m_ItemArray | `Inventory` |
| SwordUI | 0x5e480 | m_Dlg | `MUIDialog` |
| SwordUI | 0x5e9e8 | m_Msg | `MUIDialog` |
| SwordUI | 0x5ec8 | stp_State | `UIButton` |
| SwordUI | 0x5ef50 | note_purgenum | `WuLing` |
| SwordUI | 0x5ef54 | m_bHasWeapon | `unsigned char` |
| SwordUI | 0x60 | m_nSwordIdx | `int` |
| SwordUI | 0x6020 | stp_Magic | `UIButton` |
| SwordUI | 0x6178 | stp_Equip | `UIButton` |
| SwordUI | 0x62d0 | stp_Prop | `UIButton` |
| SwordUI | 0x64 | m_nSwordIdx2 | `int` |
| SwordUI | 0x6428 | stp_BattleArray | `UIButton` |
| SwordUI | 0x6580 | stp_System | `UIButton` |
| SwordUI | 0x66d8 | stp_Exit | `UIButton` |
| SwordUI | 0x68 | m_szSwordBuf | `char[64]` |
| SwordUI | 0x6830 | stp_Effect | `UIStatic` |
| SwordUI | 0x68d0 | stp_Rect | `tagRECT` |
| SwordUI | 0x68e0 | m_GameTime | `UIStatic` |
| SwordUI | 0x6980 | m_GameMoney | `UIStatic` |
| SwordUI | 0x6a20 | m_btnPar | `UIParticle[16][7]` |
| SystemUI | 0x102c | stp_Exit | `UIButton` |
| SystemUI | 0x11674 | m_par2 | `UIParticle[16][7]` |
| SystemUI | 0x1184 | stp_Effect | `UIStatic` |
| SystemUI | 0x1224 | stp_Rect | `tagRECT` |
| SystemUI | 0x1234 | m_GameTime | `UIStatic` |
| SystemUI | 0x12d4 | m_GameMoney | `UIStatic` |
| SystemUI | 0x1374 | m_par | `UIParticle[16][7]` |
| SystemUI | 0x168 | m_IsMsg | `unsigned char` |
| SystemUI | 0x16c | pStateUI | `StateUI *` |
| SystemUI | 0x170 | m_Frame | `UIStatic` |
| SystemUI | 0x210 | m_TimeMoney | `UIStatic` |
| SystemUI | 0x21974 | m_parRc | `tagRECT[7]` |
| SystemUI | 0x219e4 | _isParBtn | `unsigned char[7]` |
| SystemUI | 0x219ec | _curParEffect | `int` |
| SystemUI | 0x219f0 | m_TopBar | `UIStatic` |
| SystemUI | 0x21a90 | m_BottomBar | `UIStatic` |
| SystemUI | 0x21b30 | m_ExitGame | `UIButton` |
| SystemUI | 0x21c88 | m_SaveBtn | `UIButton` |
| SystemUI | 0x21de0 | m_LoadBtn | `UIButton` |
| SystemUI | 0x21f38 | m_DeleteBtn | `UIButton` |
| SystemUI | 0x22090 | m_pbPage | `UIPushButton[10]` |
| SystemUI | 0x22a68 | m_isItemShow | `unsigned char[99]` |
| SystemUI | 0x22acc | m_NoteItem | `Note_Item[99]` |
| SystemUI | 0x2b0 | m_OutFrameT | `UIStatic` |
| SystemUI | 0x350 | m_OutFrameR | `UIStatic` |
| SystemUI | 0x3f0 | m_OutFrameL | `UIStatic` |
| SystemUI | 0x48 | m_rcLayout | `tagRECT` |
| SystemUI | 0x490 | m_OutFrameB | `UIStatic` |
| SystemUI | 0x530 | stp_BarL | `UIStatic` |
| SystemUI | 0x58 | m_nBkWndX | `int` |
| SystemUI | 0x5c | m_nBkWndY | `int` |
| SystemUI | 0x5d0 | stp_BarM | `UIFlexBar` |
| SystemUI | 0x60 | m_nNoteIdx | `int` |
| SystemUI | 0x624 | stp_BarR | `UIStatic` |
| SystemUI | 0x64 | m_nReserved64 | `int` |
| SystemUI | 0x68 | m_szTimeBuf | `char[64]` |
| SystemUI | 0x6c4 | stp_State | `UIButton` |
| SystemUI | 0x7cc7c | m_Scroll | `UIScrollBar` |
| SystemUI | 0x7cdec | m_CurScrollPos | `int` |
| SystemUI | 0x7cdf0 | m_BackBar | `UIStatic` |
| SystemUI | 0x7ce90 | m_BackBar2 | `UIStatic` |
| SystemUI | 0x7cf30 | m_MusicBar | `UIDragBar` |
| SystemUI | 0x7d040 | m_MusicEffectBar | `UIDragBar` |
| SystemUI | 0x7d150 | m_MusicText | `UIStatic` |
| SystemUI | 0x7d1f0 | m_MusicEffectText | `UIStatic` |
| SystemUI | 0x7d290 | m_ItemH | `int` |
| SystemUI | 0x7d294 | m_ItemW | `int` |
| SystemUI | 0x7d298 | m_firstItem | `int` |
| SystemUI | 0x7d29c | m_selItem | `int` |
| SystemUI | 0x7d2a0 | m_getNote | `int` |
| SystemUI | 0x7d2a4 | m_noteState | `NOTE_STATE` |
| SystemUI | 0x7d2a8 | m_loading | `int` |
| SystemUI | 0x7d2ac | m_passtime | `float` |
| SystemUI | 0x7d2b0 | m_isExit | `unsigned char` |
| SystemUI | 0x7d2b4 | m_MsgBox | `MUIDialog` |
| SystemUI | 0x81c | stp_Magic | `UIButton` |
| SystemUI | 0x974 | stp_Equip | `UIButton` |
| SystemUI | 0xac | m_nFieldAC | `int` |
| SystemUI | 0xacc | stp_Prop | `UIButton` |
| SystemUI | 0xb0 | m_nFieldB0 | `int` |
| SystemUI | 0xb4 | m_NoteArray | `void *` |
| SystemUI | 0xc24 | stp_BattleArray | `UIButton` |
| SystemUI | 0xd7c | stp_TaskBook | `UIButton` |
| SystemUI | 0xed4 | stp_System | `UIButton` |
| TaskBookUI | 0x108 | m_OutFrameR | `UIStatic` |
| TaskBookUI | 0x11854 | m_btnPar2 | `UIParticle[16][7]` |
| TaskBookUI | 0x1554 | m_btnPar | `UIParticle[16][7]` |
| TaskBookUI | 0x1a8 | m_OutFrameL | `UIStatic` |
| TaskBookUI | 0x21b54 | m_btnParRc | `tagRECT[7]` |
| TaskBookUI | 0x21bc4 | _isParBtn | `unsigned char[7]` |
| TaskBookUI | 0x21bcc | _curParEffect | `int` |
| TaskBookUI | 0x21bd0 | m_ListBK | `UIStatic` |
| TaskBookUI | 0x21c70 | m_ListTitle | `UIStatic` |
| TaskBookUI | 0x21d10 | m_ListBtn | `UIButton[9]` |
| TaskBookUI | 0x22928 | m_ListBtnBkL | `UIStatic` |
| TaskBookUI | 0x229c8 | m_ListBtnBkR | `UIStatic` |
| TaskBookUI | 0x22a68 | m_Scroll | `UIScrollBar` |
| TaskBookUI | 0x22bd8 | m_IsScroll | `int` |
| TaskBookUI | 0x22bdc | m_ScrollHB | `UIStatic` |
| TaskBookUI | 0x22c7c | m_TaskBk | `UIStatic` |
| TaskBookUI | 0x22d1c | m_TaskPicBk | `UIStatic` |
| TaskBookUI | 0x22dbc | m_TaskPic | `UIStatic` |
| TaskBookUI | 0x22e5c | m_TaskDesc | `UIStatic` |
| TaskBookUI | 0x22efc | m_TaskTitle | `UIStatic` |
| TaskBookUI | 0x22f9c | m_TaskState | `UIStatic` |
| TaskBookUI | 0x2303c | m_SelItem | `int` |
| TaskBookUI | 0x23040 | m_FirstItem | `int` |
| TaskBookUI | 0x23044 | m_TotalItem | `int` |
| TaskBookUI | 0x248 | m_OutFrameB | `UIStatic` |
| TaskBookUI | 0x2e8 | stp_BarL | `UIStatic` |
| TaskBookUI | 0x388 | stp_BarM | `UIFlexBar` |
| TaskBookUI | 0x3dc | stp_BarR | `UIStatic` |
| TaskBookUI | 0x47c | stp_State | `UIButton` |
| TaskBookUI | 0x48 | rc | `tagRECT` |
| TaskBookUI | 0x58 | bkWndX | `int` |
| TaskBookUI | 0x5c | bkWndY | `int` |
| TaskBookUI | 0x5d4 | stp_Magic | `UIButton` |
| TaskBookUI | 0x60 | m_IsCreateable | `unsigned char` |
| TaskBookUI | 0x61 | m_IsActive | `unsigned char` |
| TaskBookUI | 0x64 | pStateUI | `StateUI *` |
| TaskBookUI | 0x68 | m_OutFrameT | `UIStatic` |
| TaskBookUI | 0x72c | stp_Equip | `UIButton` |
| TaskBookUI | 0x884 | stp_Prop | `UIButton` |
| TaskBookUI | 0x9dc | stp_BattleArray | `UIButton` |
| TaskBookUI | 0xb34 | stp_TaskBook | `UIButton` |
| TaskBookUI | 0xc8c | stp_System | `UIButton` |
| TaskBookUI | 0xde4 | stp_Exit | `UIButton` |
| TaskBookUI | 0xf3c | stp_Effect | `UIStatic` |
| TaskBookUI | 0xfdc | stp_Rect | `tagRECT` |
| TaskBookUI | 0xfec | m_DlgEx | `MUIDialog` |
| TaskMgr | 0x10 | m_nCurTask | `int` |
| TaskMgr | 0x14 | m_nCurSubTask | `int` |
| TaskMgr | 0x18 | m_nTask | `int` |
| TaskMgr | 0x1c | m_nMaxTask | `int` |
| TaskMgr | 0x20 | m_nMaxSubTask | `int` |
| TaskMgr | 0x4 | m_fCurTime | `float` |
| TaskMgr | 0x8 | m_fDeltaTime | `float` |
| TaskMgr | 0xc | m_pTask | `char *` |
| TaskMgr_SceneObjParam_SceneObj | 0x0 | m_nTodo_000 | `void *` |
| TextureLib | 0x0 | m_pResultTex | `gbTexture *` |
| TextureLib | 0x100 | m_nImageSize | `int` |
| TextureLib | 0x130 | m_nColorKey | `int` |
| TextureLib | 0x14c | m_nStride | `int` |
| TextureLib | 0x150 | m_nDataSize | `int` |
| TextureLib | 0x158 | m_nTexFormat | `int` |
| TextureLib | 0x180 | m_nBPP | `int` |
| TextureLib | 0x184 | m_nDataOffset | `int` |
| TextureLib | 0x19c | m_nDataStart | `int` |
| TextureLib | 0x1a0 | m_nDataEnd | `int` |
| TextureLib | 0x1a8 | m_bLoaded | `unsigned char` |
| TextureLib | 0x1cc | m_nPaletteSize | `int` |
| TextureLib | 0x1e8 | m_nTexFlags | `int` |
| TextureLib | 0x20 | m_nTextureId | `int` |
| TextureLib | 0x20c | m_szText | `int` |
| TextureLib | 0x210 | m_pTexture | `char *` |
| TextureLib | 0x24 | m_szPath | `int` |
| TextureLib | 0x30 | m_fTexCoordU | `float` |
| TextureLib | 0x34 | m_fTexCoordV | `float` |
| TextureLib | 0x3c | m_fTexScale | `float` |
| TextureLib | 0x40 | m_bTexFilter | `unsigned char` |
| TextureLib | 0x44 | m_nTexParam1 | `int` |
| TextureLib | 0x48 | m_nTexParam2 | `int` |
| TextureLib | 0x4c | m_nTexParam3 | `int` |
| TextureLib | 0x50 | m_bTexClamp | `unsigned char` |
| TextureLib | 0x7f | m_bMipMap | `unsigned char` |
| TextureLib | 0x80 | m_bAlphaChannel | `unsigned char` |
| TextureLib | 0x84 | m_fTexParam | `float` |
| TextureLib | 0x88 | m_fAngle | `float` |
| TextureLib | 0x8c | m_fColorModR | `float` |
| TextureLib | 0x90 | m_fColorModG | `float` |
| TextureLib | 0x94 | m_fColorModB | `float` |
| TextureLib | 0x98 | m_fColorModA | `float` |
| TextureLib | 0x9c | m_fColorAdd | `float` |
| TextureLib | 0xb8 | m_nTexWidth | `int` |
| TextureLib | 0xbc | m_nTexHeight | `int` |
| TextureLib | 0xc | m_szPathBuf | `int` |
| TextureLib | 0xcc | m_Image | `char[48]` |
| TextureLib | 0xfc | m_nImageOffset | `int` |
| TextureLibDataBase | 0x20c | _realNum | `int` |
| TextureLibDataBase | 0x210 | m_pData | `_Texture_Info *` |
| TextureLibDataBase | 0x214 | _isLoadTLI | `BYTE` |
| TextureLibDataBase | 0x244 | m_fScrollSpeed | `float` |
| TextureLibDataBase | 0x4 | Seps | `char *` |
| TextureLibDataBase | 0x8 | tok | `char *` |
| TextureLibDataBase | 0xc | _libfolder | `char[512]` |
| TextureLib_Data | 0x0 | _tail_000 | `char[1116]` |
| ThrowInfo | 0x0 | attributes | `UINT` |
| ThrowInfo | 0x4 | pmfnUnwind | `PMFN` |
| ThrowInfo | 0xc | pCatchableTypeArray | `CatchableTypeArray *` |
| TileMap | 0x0 | _tail_000 | `char[4]` |
| TimeCtl | 0x0 | newtick | `DWORD` |
| TimeCtl | 0x4 | oldtick | `DWORD` |
| TimeCtl | 0x8 | bNote | `BYTE` |
| Triangle | 0x0 | vert | `gbVec3D[3]` |
| Triangle | 0x24 | normal | `gbVec3D` |
| TryBlockMapEntry | 0x0 | tryLow | `int` |
| TryBlockMapEntry | 0x10 | pHandlerArray | `char *` |
| TryBlockMapEntry | 0x4 | tryHigh | `int` |
| TryBlockMapEntry | 0x8 | catchHigh | `int` |
| TryBlockMapEntry | 0xc | nCatches | `int` |
| TxtFile | 0x0 | m_token | `char[512]` |
| TxtFile | 0x200 | m_buf | `char *` |
| TxtFile | 0x204 | m_sectionstart | `char *` |
| TxtFile | 0x208 | m_curpos | `char *` |
| UI3DCtrl | 0x100 | m_rotx | `float` |
| UI3DCtrl | 0x104 | m_rotz | `float` |
| UI3DCtrl | 0x108 | m_dropx | `float` |
| UI3DCtrl | 0x10c | m_dropy | `float` |
| UI3DCtrl | 0x110 | m_dropz | `float` |
| UI3DCtrl | 0x114 | m_scalex | `float` |
| UI3DCtrl | 0x118 | m_scaley | `float` |
| UI3DCtrl | 0x11c | m_scalez | `float` |
| UI3DCtrl | 0x120 | m_lightobj | `gbLightObj *` |
| UI3DCtrl | 0x124 | m_camera | `gbCamera *` |
| UI3DCtrl | 0x128 | m_raydir | `gbVec3D` |
| UI3DCtrl | 0x44 | m_numobj | `int` |
| UI3DCtrl | 0x48 | m_obj | `UI3DObj[5]` |
| UI3DCtrl | 0xe8 | m_orthosize | `float` |
| UI3DCtrl | 0xec | m_rotatemode | `int` |
| UI3DCtrl | 0xf0 | m_isrotateto | `unsigned char` |
| UI3DCtrl | 0xf4 | m_speed | `int` |
| UI3DCtrl | 0xf8 | m_rotate | `float` |
| UI3DCtrl | 0xfc | m_rotatetarget | `float` |
| UI3DModelNode | 0x5c | m_nTodo_05C | `int` |
| UI3DModelNode | 0x60 | m_nTodo_060 | `int` |
| UI3DModelNode | 0x64 | m_nTodo_064 | `int` |
| UI3DModelNode | 0x68 | m_nTodo_068 | `int[16]` |
| UI3DModelNode | 0xe8 | m_nTodo_0E8 | `int` |
| UI3DModelNode | 0xec | m_nTodo_0EC | `int` |
| UI3DModelNode | 0xf0 | m_nTodo_0F0 | `int` |
| UI3DModelNode | 0xf4 | m_nTodo_0F4 | `int` |
| UI3DObj | 0x0 | m_mouseoff | `BYTE` |
| UI3DObj | 0x10 | m_actor | `Actor *` |
| UI3DObj | 0x14 | m_pos | `gbVec3D` |
| UI3DObj | 0x4 | m_enable | `int` |
| UI3DObj | 0x8 | m_needdel | `int` |
| UI3DObj | 0xc | m_type | `int` |
| UIAnimCtrl | 0x0 | _tail_000 | `char[4]` |
| UIAnimate | 0x0 | m_sec | `DWORD` |
| UIAnimate | 0x14 | m_Rc2 | `tagRECT` |
| UIAnimate | 0x24 | m_IsLoop | `unsigned char[4]` |
| UIAnimate | 0x28 | m_Time | `TimeCtl` |
| UIAnimate | 0x4 | m_Rc | `tagRECT` |
| UIAnimateCtrl | 0x44 | m_FPS | `float` |
| UIAnimateCtrl | 0x48 | m_passtime | `float` |
| UIAnimateCtrl | 0x4c | m_texarray | `UITextureArray` |
| UIAnimateCtrl | 0x90 | m_curframe | `int` |
| UIAnimateCtrl | 0x94 | m_numframe | `int` |
| UIAnimateCtrl | 0x98 | m_looppassed | `int` |
| UIAnimateCtrl | 0x9c | m_nLoop | `int` |
| UIAnimateCtrl | 0xa0 | m_mode | `int` |
| UIAnimateCtrlEX | 0x19c | m_Frame | `UIStatic` |
| UIAnimateCtrlEX | 0x234 | m_ResultWnd | `CCBResultWindow` |
| UIAnimateCtrlEX | 0x2ec | m_TextArea | `UITextArea` |
| UIAnimateCtrlEX | 0x3ac | m_ChildWnd | `UIWnd` |
| UIAnimateCtrlEX | 0x3f0 | m_bAnimFlag | `unsigned char` |
| UIAnimateCtrlEX | 0x44 | m_Scene | `UIScene` |
| UIBase | 0x0 | _tail_000 | `char[4]` |
| UIBigDialog | 0x0 | _tail_000 | `char[4]` |
| UIBigMap | 0x168 | ms_BigMap | `UIStatic` |
| UIBigMap | 0x1a88 | m_spiritRect | `tagRECT` |
| UIBigMap | 0x1a98 | m_spirit | `UIAnimateCtrl` |
| UIBigMap | 0x1b3c | m_spiritPosX | `float` |
| UIBigMap | 0x1b40 | m_spiritPosY | `float` |
| UIBigMap | 0x1b44 | m_spiritPos | `tagPOINT` |
| UIBigMap | 0x1b4c | m_movetopos | `tagPOINT` |
| UIBigMap | 0x1b54 | m_movetoX | `float` |
| UIBigMap | 0x1b58 | m_movetoY | `float` |
| UIBigMap | 0x1b5c | m_spiritspeed | `int` |
| UIBigMap | 0x1b60 | m_speedFX | `float` |
| UIBigMap | 0x1b64 | m_speedFY | `float` |
| UIBigMap | 0x1b68 | m_bSpiritCanMove | `unsigned char` |
| UIBigMap | 0x1b69 | m_isSpiritMoveTo | `unsigned char` |
| UIBigMap | 0x1b6c | m_timescale | `float` |
| UIBigMap | 0x1b70 | m_stopdir | `int` |
| UIBigMap | 0x1b74 | m_curElement | `_BIGMAP_ELEMENT` |
| UIBigMap | 0x1b78 | m_Answer | `MUIDialog` |
| UIBigMap | 0x208 | m_Element | `_MapElement[16]` |
| UIBigMap | 0x48 | screenrect | `tagRECT` |
| UIBigMap | 0x58 | bkWndX | `int` |
| UIBigMap | 0x5c | bkWndY | `int` |
| UIBigMap | 0x60 | i | `int` |
| UIBigMap | 0x64 | j | `int` |
| UIBigMap | 0x68 | buf | `char[256]` |
| UIButton | 0x140 | m_benable_snd | `BYTE` |
| UIButton | 0x44 | m_hasDBclk | `unsigned char` |
| UIButton | 0x48 | m_ratiow | `float` |
| UIButton | 0x4c | m_state | `UIButton_UIBUTTON_STATE` |
| UIButton | 0x50 | m_canctrl | `BYTE` |
| UIButton | 0x51 | m_bLockUpdate | `BYTE` |
| UIButton | 0x54 | m_offsetx | `int` |
| UIButton | 0x58 | m_offsety | `float` |
| UIButton | 0x5c | m_bBigFont | `BYTE` |
| UIButton | 0x60 | m_texarray | `UITextureArray` |
| UIButton | 0xa4 | m_texarrayInfo | `_PlugInfo *[3]` |
| UIButton | 0xb0 | m_disablepic | `gbTexture *` |
| UIButton | 0xb4 | m_disablepicInfo | `_PlugInfo *` |
| UIButton | 0xb8 | m_mouseoff | `BYTE` |
| UIButton | 0xb9 | m_mouseon | `BYTE` |
| UIButton | 0xbc | m_alignmode | `int` |
| UIButton | 0xc0 | m_caption | `char[128]` |
| UIButtonEX | 0x158 | m_optData | `_btnOPTDATA[3]` |
| UIButtonEXA | 0x158 | m_optData | `_btnOPTDATA` |
| UIButtonEXA | 0x168 | m_EnableMode | `int` |
| UIButtonEXA | 0x16c | m_color | `gbColorQuad` |
| UIButtonEXA | 0x170 | m_enablecolor | `gbColorQuad` |
| UIButtonEXA | 0x174 | m_surecolor | `gbColorQuad` |
| UIButton_UIBUTTON_STATE | 0x0 | _tail_000 | `char[4]` |
| UICamera | 0x110 | m_pCameraData | `int` |
| UICamera | 0x1cc | m_nStateFlags | `int` |
| UICamera | 0x1d0 | m_nParam | `int` |
| UICamera | 0x1ec | m_fVecX | `float` |
| UICamera | 0x1f0 | m_fVecY | `float` |
| UICamera | 0x1f4 | m_fVecZ | `float` |
| UICamera | 0x274 | m_hCameraHandle | `int` |
| UICamera | 0x278 | m_nTodo_278 | `int` |
| UICamera | 0x80 | m_nCamState | `int` |
| UICamera | 0x98 | m_nViewMode | `int` |
| UICamera | 0xa0 | m_fCamAngle | `float` |
| UICamera | 0xa4 | m_fCoordU | `float` |
| UICamera | 0xa8 | m_fCoordV | `float` |
| UICamera | 0xdc | m_nBuffer | `int` |
| UICamera | 0xe0 | m_hTarget | `int` |
| UICaption | 0x4c | m_tex | `gbTexture *` |
| UICaption | 0x50 | m_numline | `int` |
| UICaption | 0x54 | m_lineheight | `int` |
| UICaption | 0x58 | m_curline | `int` |
| UICaption | 0x5c | m_linetime | `float` |
| UIChatRest | 0x100 | m_FlagB | `UIStatic` |
| UIChatRest | 0x11f0 | m_enough | `MUIDialog` |
| UIChatRest | 0x171c | m_restover | `MUIDialog` |
| UIChatRest | 0x198 | m_FlagM | `UIStatic[3]` |
| UIChatRest | 0x1c48 | m_status | `UINT` |
| UIChatRest | 0x1c4c | m_isExit | `BYTE` |
| UIChatRest | 0x1c50 | m_RestScript | `RestScript` |
| UIChatRest | 0x2464 | m_CANREST_ID | `int` |
| UIChatRest | 0x2468 | m_CANNOTREST_ID | `int` |
| UIChatRest | 0x246c | m_RESTOVER_ID | `int` |
| UIChatRest | 0x2470 | pRest | `PalScript *` |
| UIChatRest | 0x2474 | pCantRest | `PalScript *` |
| UIChatRest | 0x2478 | pRestOver | `PalScript *` |
| UIChatRest | 0x247c | m_bActive | `BYTE` |
| UIChatRest | 0x2480 | pC_DUI | `Comp_DonateUI *` |
| UIChatRest | 0x2484 | m_bC_DUIOver | `BYTE` |
| UIChatRest | 0x2488 | m_BK | `UIStatic` |
| UIChatRest | 0x2520 | m_FadeOutAlpha | `BYTE` |
| UIChatRest | 0x2524 | m_age | `float` |
| UIChatRest | 0x2528 | m_life | `float` |
| UIChatRest | 0x360 | m_Chat | `UIButton` |
| UIChatRest | 0x44 | m_pt | `int` |
| UIChatRest | 0x48 | bkrc | `tagRECT` |
| UIChatRest | 0x4b8 | m_Rest | `UIButton` |
| UIChatRest | 0x58 | m_startX | `int` |
| UIChatRest | 0x5c | m_startY | `int` |
| UIChatRest | 0x60 | mbWidth | `int` |
| UIChatRest | 0x610 | m_Exit | `UIButton` |
| UIChatRest | 0x64 | mbHeight | `int` |
| UIChatRest | 0x68 | m_FlagT | `UIStatic` |
| UIChatRest | 0x768 | m_TabBtn | `UITabBtn` |
| UIChatRest | 0x780 | m_answerDlg | `MUIDialog` |
| UIChatRest | 0xcac | m_bAnswer | `BYTE` |
| UIChatRest | 0xcb0 | eft | `ScreenEffect *` |
| UIChatRest | 0xcb4 | m_timewait | `TimeCtl` |
| UIChatRest | 0xcc0 | m_isFadeOut | `BYTE` |
| UIChatRest | 0xcc1 | m_isFadeIn | `BYTE` |
| UIChatRest | 0xcc4 | m_noenoughmsg | `MUIDialog` |
| UICoverFrm | 0x11c8 | m_midCloud | `_CLOUD[5]` |
| UICoverFrm | 0x158 | m_background | `UIStatic` |
| UICoverFrm | 0x1600 | m_smlCloud | `_CLOUD[5]` |
| UICoverFrm | 0x1a38 | m_testCloud | `_CLOUD[9]` |
| UICoverFrm | 0x1f8 | m_Star | `UIPar_Star[13]` |
| UICoverFrm | 0x21d0 | m_mountainA | `UIStatic` |
| UICoverFrm | 0x2270 | m_mountainB | `UIStatic` |
| UICoverFrm | 0x2310 | m_frame | `UIStatic` |
| UICoverFrm | 0x23b0 | m_Logo | `UIStatic` |
| UICoverFrm | 0x2450 | m_isAlpha | `unsigned char` |
| UICoverFrm | 0x2454 | m_alpha | `float` |
| UICoverFrm | 0x2458 | m_tjA | `UIStaticEXA` |
| UICoverFrm | 0x2520 | m_tjB | `UIStaticEXA` |
| UICoverFrm | 0x25e8 | m_XDGS | `UIButtonEX` |
| UICoverFrm | 0x2770 | m_QCYM | `UIButtonEX` |
| UICoverFrm | 0x28f8 | m_XJTM | `UIButtonEX` |
| UICoverFrm | 0x2a80 | m_LKYX | `UIButtonEX` |
| UICoverFrm | 0x2c08 | m_YXXX | `UIButtonEX` |
| UICoverFrm | 0x2d90 | m_JDHY | `UIButtonEX` |
| UICoverFrm | 0x2f18 | m_CtrlBtn | `UIButtonEX *[6]` |
| UICoverFrm | 0x2f30 | m_SelBtn | `int` |
| UICoverFrm | 0x2f34 | m_ExitGame | `unsigned char` |
| UICoverFrm | 0x2f38 | pQCYM | `UITitle_QCYM *` |
| UICoverFrm | 0x2f3c | pJDHY | `UITitle_JDHY *` |
| UICoverFrm | 0x2f40 | pYXXX | `UITitle_YXXX *` |
| UICoverFrm | 0x2f44 | pXJTM | `UITitle_XJTM *` |
| UICoverFrm | 0x2f48 | pArcSave | `UITitle_ArcSave *` |
| UICoverFrm | 0x2f4c | pLoadingFrm | `UILoadingFrm *` |
| UICoverFrm | 0x2f50 | m_MenuType | `MENU_TYPE` |
| UICoverFrm | 0x2f54 | m_timeAverage | `Average` |
| UICoverFrm | 0x2f6c | m_gotogame | `unsigned char` |
| UICoverFrm | 0x2f70 | m_flag | `unsigned int` |
| UICoverFrm | 0x2f74 | m_test | `UIStatic` |
| UICoverFrm | 0x3290 | m_bLogoDone | `unsigned char` |
| UICoverFrm | 0x3294 | m_hCoverEffect | `int` |
| UICoverFrm | 0x3299 | m_bAnimFlags | `unsigned char[8]` |
| UICoverFrm | 0x3648 | m_bCoverTexSet | `unsigned char` |
| UICoverFrm | 0x364c | m_pCoverTex | `int` |
| UICoverFrm | 0x36e8 | m_nCoverRectArg | `int` |
| UICoverFrm | 0x36ec | m_nCoverInitX | `int` |
| UICoverFrm | 0x36f4 | m_nCoverTargetX | `int` |
| UICoverFrm | 0x36f8 | m_fCoverStep | `float` |
| UICoverFrm | 0x36fc | m_fCoverCurX | `float` |
| UICoverFrm | 0x3700 | m_CoverWnd | `UIWnd` |
| UICoverFrm | 0x3798 | m_bCoverAnimDone | `unsigned char` |
| UICoverFrm | 0x38d0 | m_ActiveSlotBase | `int` |
| UICoverFrm | 0x3908 | m_ActiveSlotFlags | `int` |
| UICoverFrm | 0x48 | rc | `tagRECT` |
| UICoverFrm | 0x58 | buf | `char[256]` |
| UICoverFrm | 0x844 | m_Meteor | `UIPar_Meteor` |
| UICoverFrm | 0x958 | m_cloud | `_CLOUD[10]` |
| UICursor | 0x0 | m_dwID | `unsigned int[3]` |
| UICursor | 0x10 | m_tex | `gbTexture *[3]` |
| UICursor | 0x1c | m_bShow | `BYTE` |
| UICursor | 0x1d | m_bSoftMode | `BYTE` |
| UICursor | 0x2c | m_pData | `unsigned long` |
| UICursor | 0xc | m_active | `CameraCtrl *` |
| UIDialog | 0x44 | m_bmodal | `int` |
| UIDragBar | 0x44 | p_Wnd | `UIWnd *` |
| UIDragBar | 0x48 | m_SX | `int` |
| UIDragBar | 0x4c | m_SY | `int` |
| UIDragBar | 0x50 | m_xOffSet | `int` |
| UIDragBar | 0x54 | m_bDrag | `BYTE` |
| UIDragBar | 0x55 | m_bClick | `BYTE` |
| UIDragBar | 0x58 | m_DragState | `int` |
| UIDragBar | 0x5c | m_lastPt | `tagPOINT` |
| UIDragBar | 0x64 | m_DragRc | `tagRECT` |
| UIDragBar | 0x74 | m_bkRc | `tagRECT` |
| UIDragBar | 0x84 | m_ProgressRc | `tagRECT` |
| UIDragBar | 0x94 | m_DragColor | `gbColorQuad` |
| UIDragBar | 0x98 | m_bkColor | `gbColorQuad` |
| UIDragBar | 0x9c | m_foColor | `gbColorQuad` |
| UIDragBar | 0xa0 | m_DragTex | `gbTexture *[3]` |
| UIDragBar | 0xac | m_DragTexInfo | `_PlugInfo *[3]` |
| UIDragBar | 0xb8 | m_pbk | `gbTexture *` |
| UIDragBar | 0xbc | m_pbkInfo | `_PlugInfo *` |
| UIDragBar | 0xc0 | m_ppic | `gbTexture *` |
| UIDragBar | 0xc4 | m_ppicInfo | `_PlugInfo *` |
| UIDragBar | 0xc8 | m_progress | `float` |
| UIDragBar | 0xcc | m_Lenth | `float` |
| UIDragBar | 0xd0 | m_MaxVal | `float` |
| UIDragBar | 0xd4 | m_Val | `float` |
| UIDragBar | 0xd8 | m_radius | `float` |
| UIDragBar | 0xdc | m_step | `float` |
| UIDragBar | 0xe0 | m_dragRadius | `int` |
| UIDragBar | 0xe4 | m_lradius | `float` |
| UIDragBar | 0xe8 | m_rradius | `float` |
| UIDragBar | 0xec | m_tradius | `float` |
| UIDragBar | 0xf0 | m_bradius | `float` |
| UIDragBar | 0xf4 | m_mode | `int` |
| UIDragBar | 0xf8 | m_dir | `int` |
| UIEmote | 0x48 | m_sub48 | `int` |
| UIEmote | 0x4c | m_cur | `int` |
| UIEmote | 0x50 | m_ani | `UIAnimateCtrl[13]` |
| UIEmote | 0x8a4 | m_role | `Role *` |
| UIEmote | 0x8a8 | m_loopcount | `int` |
| UIEmote | 0x8ac | m_nLoop | `int[13]` |
| UIFlexBar | 0x44 | m_tilewidth | `int` |
| UIFlexBar | 0x48 | m_tileheight | `int` |
| UIFlexBar | 0x4c | m_tex | `gbTexture *` |
| UIFlexBar | 0x50 | m_style | `int` |
| UIFrameContainer | 0x60 | m_bFlag96 | `char` |
| UIFrameContainer | 0x64 | m_aSlots | `int[6]` |
| UIFrameWnd | 0x44 | m_pbktex | `gbTexture *` |
| UIGameFrm | 0x100 | m_nStartPos | `short` |
| UIGameFrm | 0x104 | m_nInit | `UIWnd *` |
| UIGameFrm | 0x1160 | m_fUIColorR | `float` |
| UIGameFrm | 0x1164 | m_nUIColorMode | `int` |
| UIGameFrm | 0x1394 | m_UITitle | `int` |
| UIGameFrm | 0x13f0 | m_fUITransition | `float` |
| UIGameFrm | 0x148 | m_nField_148 | `int` |
| UIGameFrm | 0x164 | m_nSaveSlot | `int` |
| UIGameFrm | 0x1680 | m_fUIFadeAlpha | `float` |
| UIGameFrm | 0x1684 | m_nUIFadeState | `int` |
| UIGameFrm | 0x1910 | m_fSceneTimer | `float` |
| UIGameFrm | 0x1914 | m_nSceneState | `int` |
| UIGameFrm | 0x198 | m_nSceneTransFlag | `int` |
| UIGameFrm | 0x1e30 | m_fEffectTimer | `float` |
| UIGameFrm | 0x1e34 | m_nEffectState | `int` |
| UIGameFrm | 0x270 | m_nPlayerMoney | `int` |
| UIGameFrm | 0x274 | m_nMoneyAdd | `int` |
| UIGameFrm | 0x278 | m_nMoneySub | `int` |
| UIGameFrm | 0x27c | m_nStorePriceMod | `int` |
| UIGameFrm | 0x280 | m_nTodo_280 | `unsigned char` |
| UIGameFrm | 0x281 | m_nTodo_281 | `unsigned char` |
| UIGameFrm | 0x282 | m_nTodo_282 | `unsigned char` |
| UIGameFrm | 0x284 | m_nReputation | `int` |
| UIGameFrm | 0x2870 | m_fScriptTimer | `float` |
| UIGameFrm | 0x287c | m_nScriptPhase | `int` |
| UIGameFrm | 0x288 | m_nSceneLoadParam | `int` |
| UIGameFrm | 0x28c | m_bSceneLoaded | `char` |
| UIGameFrm | 0x28d | m_bSceneActive | `unsigned char` |
| UIGameFrm | 0x290 | m_nGameMode | `int` |
| UIGameFrm | 0x2b00 | m_fDialogTimer | `float` |
| UIGameFrm | 0x2b04 | m_nDialogState | `int` |
| UIGameFrm | 0x2d8 | m_nBattleResult | `int` |
| UIGameFrm | 0x2e0 | m_nMissionState | `int` |
| UIGameFrm | 0x300 | m_nBattleCount | `int` |
| UIGameFrm | 0x38bc | m_nGameFlags | `int` |
| UIGameFrm | 0x38c0 | m_pDialog | `char *` |
| UIGameFrm | 0x38c4 | m_pSceneObjRef | `SceneObj *` |
| UIGameFrm | 0x38c8 | m_nPrevSceneState | `int` |
| UIGameFrm | 0x38cc | m_nSceneTransition | `int` |
| UIGameFrm | 0x38d0 | m_aItemData | `int` |
| UIGameFrm | 0x400 | m_nWinCount | `int` |
| UIGameFrm | 0x42d0 | m_nPostGame | `int` |
| UIGameFrm | 0x44 | m_nField_044 | `int` |
| UIGameFrm | 0x48 | m_nDataCRC | `int` |
| UIGameFrm | 0x500 | m_nLossCount | `int` |
| UIGameFrm | 0x600 | m_nEscapeCount | `int` |
| UIGameFrm | 0x6d0 | m_fAnimTimer | `float` |
| UIGameFrm | 0x6d4 | m_fAnimSpeed | `float` |
| UIGameFrm | 0x6e10 | m_pGameObj | `char *` |
| UIGameFrm | 0x6e14 | m_nMode | `int` |
| UIGameFrm | 0x6e18 | m_pGameObjB | `char *` |
| UIGameFrm | 0x6fc | m_bAnimPaused | `unsigned char` |
| UIGameFrm | 0x730 | m_bAnimLoop | `unsigned char` |
| UIGameFrm | 0x900 | m_nKeyItemCount | `int` |
| UIGameFrm | 0x9b0 | m_fBGMVolume | `float` |
| UIGameFrm | 0x9b4 | m_nBGMState | `int` |
| UIGameFrm | 0xdc | g_pSceneTransitionEnd | `unchar *` |
| UIGameFrm | 0xed4 | m_nUIDialogId | `int` |
| UIGameFrm | 0xef5 | m_bDialogActive | `unsigned char` |
| UIGameFrm | 0xf4 | m_pStartScene | `UIScene *` |
| UIGameFrm | 0xf40 | m_nRender | `int` |
| UIGameFrm | 0xf88 | m_nUIFlags | `int` |
| UIGameOver | 0x48 | m_pbktex | `gbTexture *` |
| UIGameOver | 0x4c | m_Blood | `UIStatic` |
| UIGameOver | 0xe4 | m_fTime | `float` |
| UIGroupCtrl | 0x0 | m_bkRc | `tagRECT` |
| UIGroupCtrl | 0x10 | m_isCreat | `BYTE` |
| UIGroupCtrl | 0x14 | m_ItemNum | `int` |
| UIGroupCtrl | 0x18 | m_lBTNSel | `int` |
| UIGroupCtrl | 0x1c | m_rBTNSel | `int` |
| UIGroupCtrl | 0x20 | m_ItemW | `int` |
| UIGroupCtrl | 0x24 | m_ItemH | `int` |
| UIGroupCtrl | 0x28 | pRect | `tagRECT *` |
| UIGroupCtrl | 0x2c | pKeepRect | `tagRECT *` |
| UIGroupCtrl | 0x30 | m_color | `gbColorQuad` |
| UIGroupCtrl | 0x34 | rollSpeed | `float` |
| UIGroupCtrl | 0x38 | speedstep | `float` |
| UIGroupCtrl | 0x3c | rollID | `int` |
| UIGroupCtrl | 0x40 | isCtrl | `BYTE` |
| UIGroupCtrl | 0x44 | m_PageState | `int` |
| UIGroupCtrl | 0x48 | m_showNum | `int` |
| UIGroupCtrl | 0x4c | pEnable | `BYTE *` |
| UIGroupCtrl | 0x50 | m_pbk | `gbTexture *` |
| UIGroupCtrl | 0x54 | m_pbkInfo | `_PlugInfo *` |
| UIHeadDialog | 0x48 | baseclass2 | `PalScriptWaitObj` |
| UIHeadDialog | 0x50 | m_role | `Role *` |
| UIHeadDialog | 0x54 | m_width | `int` |
| UIHeadDialog | 0x58 | m_height | `int` |
| UIHeadDialog | 0x5c | m_bktex | `gbTexture *` |
| UIHeadDialog | 0x60 | m_text | `char[256]` |
| UIInventory | 0x0 | _tail_000 | `char[68]` |
| UIItem | 0x44 | m_fTimerLimit | `int` |
| UIItem | 0x48 | m_fTimerAccum | `int` |
| UIItem | 0x4c | m_nTodo_04C | `int` |
| UIItem | 0x50 | m_nTodo_050 | `int` |
| UIItem | 0x54 | m_nTodo_054 | `int` |
| UIItem | 0x58 | m_nTodo_058 | `int` |
| UIItem | 0x5c | m_nTodo_05C | `int` |
| UILBColumn | 0x0 | head | `char[64]` |
| UILBColumn | 0x40 | items | `PtrArray` |
| UILBColumn | 0x50 | width | `int` |
| UILBItem | 0x0 | picon | `gbTexture *` |
| UILBItem | 0x4 | text | `char[64]` |
| UILBItem | 0x44 | itemColor | `gbColorQuad` |
| UIListBox | 0x44 | m_selcolor | `gbColorQuad` |
| UIListView | 0x0 | _tail_000 | `char[4]` |
| UILoadingFrm | 0x13c | m_anitime | `float` |
| UILoadingFrm | 0x140 | m_aniFlag | `int` |
| UILoadingFrm | 0x144 | m_MaxValue | `float` |
| UILoadingFrm | 0x148 | m_isOverProgress | `unsigned char` |
| UILoadingFrm | 0x48 | m_LoadProgress | `UIProgressBar` |
| UIManager | 0x0 | _tail_000 | `char[4]` |
| UIMap | 0x44 | m_mapwidth | `int` |
| UIMap | 0x48 | m_screenWidth | `int` |
| UIMap | 0x4c | m_screenHeight | `int` |
| UIMap | 0x50 | m_xMapNum | `int` |
| UIMap | 0x54 | m_yMapNum | `int` |
| UIMap | 0x58 | m_MapNum | `int` |
| UIMap | 0x5c | m_pSubMap | `_SUBMAP *` |
| UIMap | 0x60 | m_moveSpeed | `float` |
| UIMap | 0x64 | m_isMoving | `BYTE` |
| UIMap | 0x68 | m_offsetx | `float` |
| UIMap | 0x6c | m_offsety | `float` |
| UIMap | 0x70 | m_moveoffsetx | `float` |
| UIMap | 0x74 | m_moveoffsety | `float` |
| UIMap | 0x78 | m_bCreate | `BYTE` |
| UIMap | 0x7c | timescale | `float` |
| UIMap | 0x80 | m_bLock | `BYTE` |
| UINote | 0x108 | time | `float` |
| UINote | 0x48 | m_static | `UIStaticFlex` |
| UIObj | 0x0 | _tail_000 | `char[4]` |
| UIPar_Meteor | 0x44 | m_StartToEnd | `tagRECT` |
| UIPar_Meteor | 0x54 | m_tmpPt | `tagPOINT` |
| UIPar_Meteor | 0x5c | m_TailPt | `tagPOINT[16]` |
| UIPar_Meteor | 0xdc | m_nTailNum | `int` |
| UIPar_Meteor | 0xe0 | m_ntmpTailNum | `int` |
| UIPar_Meteor | 0xe4 | m_nFrameNumBetweenTail | `int` |
| UIPar_Meteor | 0xe8 | m_fVelocityX | `float` |
| UIPar_Meteor | 0xec | m_fVelocityY | `float` |
| UIPar_Meteor | 0xf0 | m_passtime | `float` |
| UIPar_Meteor | 0xf4 | m_IsInMeteor | `int` |
| UIPar_Meteor | 0xf8 | m_nNextTime | `int` |
| UIPar_Meteor | 0xfc | m_nFrame | `int` |
| UIPar_Star | 0x44 | m_IsFadeRand | `int` |
| UIPar_Star | 0x48 | m_IsFadeOut | `int` |
| UIPar_Star | 0x4c | m_nLastTime | `int` |
| UIPar_Star | 0x50 | m_IsLastTimeRand | `int` |
| UIPar_Star | 0x54 | m_IsHighPoint | `int` |
| UIPar_Star | 0x58 | m_IsInFlash | `int` |
| UIPar_Star | 0x5c | m_nNextTime | `int` |
| UIPar_Star | 0x60 | m_IsNextTimeRand | `int` |
| UIPar_Star | 0x64 | m_nFrame | `int` |
| UIPar_TimeCtrl | 0x0 | newtick | `DWORD` |
| UIPar_TimeCtrl | 0x4 | oldtick | `unsigned int` |
| UIPar_TimeCtrl | 0x8 | bNote | `BYTE` |
| UIParabolaCtrl | 0x0 | _tail_000 | `char[4]` |
| UIParticle | 0x0 | m_viewRect | `tagRECT` |
| UIParticle | 0x10 | view_radiusX | `int` |
| UIParticle | 0x14 | view_radiusY | `int` |
| UIParticle | 0x18 | par_radiusX | `int` |
| UIParticle | 0x1a0 | _ptex | `gbTexture *` |
| UIParticle | 0x1a4 | _element | `UIStatic` |
| UIParticle | 0x1c | par_radiusY | `int` |
| UIParticle | 0x20 | _W | `int` |
| UIParticle | 0x23c | _sizeX | `int` |
| UIParticle | 0x24 | _H | `int` |
| UIParticle | 0x240 | _sizeY | `int` |
| UIParticle | 0x244 | _speed | `float` |
| UIParticle | 0x28 | m_bGetBottom | `BYTE` |
| UIParticle | 0x29 | m_bBounceX | `BYTE` |
| UIParticle | 0x2c | m_HelixAngle | `float` |
| UIParticle | 0x30 | m_tempx | `float` |
| UIParticle | 0x34 | m_tempy | `float` |
| UIParticle | 0x38 | m_helix_rx | `float` |
| UIParticle | 0x3c | m_helix_ry | `float` |
| UIParticle | 0x40 | m_isDiffuse | `BYTE` |
| UIParticle | 0x44 | m_posx | `float` |
| UIParticle | 0x48 | m_posy | `float` |
| UIParticle | 0x4c | m_FlareTime | `int` |
| UIParticle | 0x50 | m_isSubA | `BYTE` |
| UIParticle | 0x54 | m_rainbowColor | `gbColorQuad` |
| UIParticle | 0x58 | m_bGetTop | `BYTE` |
| UIParticle | 0x5c | m_riseY | `float` |
| UIParticle | 0x60 | m_xflag | `int` |
| UIParticle | 0x64 | m_state | `int` |
| UIParticle | 0x68 | m_iscolorfade | `BYTE` |
| UIParticle | 0x6c | m_time | `UIPar_TimeCtrl` |
| UIParticle | 0x78 | m_sec | `DWORD` |
| UIParticle | 0x7c | m_color | `gbColorQuad` |
| UIParticle | 0x80 | _isActive | `BYTE` |
| UIParticle | 0x84 | _fade | `float` |
| UIParticle | 0x88 | _x | `float` |
| UIParticle | 0x8c | _y | `float` |
| UIParticle | 0x90 | _xi | `float` |
| UIParticle | 0x94 | _yi | `float` |
| UIParticle | 0x98 | _xg | `float` |
| UIParticle | 0x9c | _yg | `float` |
| UIParticle | 0xa0 | _texName | `char[256]` |
| UIPosMaker | 0x0 | m_bIsLoaded | `BYTE` |
| UIPosMaker | 0x4 | m_pUIPos | `_UIPOS *` |
| UIPosMaker | 0x8 | m_nPosNum | `int` |
| UIProgressBar | 0x44 | m_mode | `int` |
| UIProgressBar | 0x48 | m_decorateRc | `tagRECT` |
| UIProgressBar | 0x58 | m_progress | `int` |
| UIProgressBar | 0x5c | m_speed | `int` |
| UIProgressBar | 0x60 | m_SetProgress | `int` |
| UIProgressBar | 0x64 | m_Lenth | `int` |
| UIProgressBar | 0x68 | m_MaxVal | `float` |
| UIProgressBar | 0x6c | m_stepval | `float` |
| UIProgressBar | 0x70 | m_radius | `int` |
| UIProgressBar | 0x74 | m_lradius | `int` |
| UIProgressBar | 0x78 | m_rradius | `int` |
| UIProgressBar | 0x7c | m_tradius | `float` |
| UIProgressBar | 0x80 | m_bradius | `float` |
| UIProgressBar | 0x84 | m_step | `int` |
| UIProgressBar | 0x88 | m_Val | `float` |
| UIProgressBar | 0x8c | m_IsGetit | `BYTE` |
| UIProgressBar | 0x90 | m_bkColor | `gbColorQuad` |
| UIProgressBar | 0x94 | m_foColor | `gbColorQuad` |
| UIProgressBar | 0x98 | m_pbk | `gbTexture *` |
| UIProgressBar | 0x9c | m_pbkInfo | `_PlugInfo *` |
| UIProgressBar | 0xa0 | m_ppic | `gbTexture *` |
| UIProgressBar | 0xa4 | m_ppicInfo | `_PlugInfo *` |
| UIProgressBar | 0xa8 | m_pdecorate | `gbTexture *` |
| UIProgressBar | 0xac | m_pdecorateInfo | `_PlugInfo *` |
| UIProgressBar | 0xb0 | m_decorateW | `int` |
| UIProgressBar | 0xb4 | m_decorateH | `int` |
| UIProgressBar | 0xb8 | m_decorateOffsetX | `int` |
| UIProgressBar | 0xbc | m_decorateOffsetY | `int` |
| UIProgressBar | 0xc0 | m_pgrmode | `PGR_MODE` |
| UIProgressBar | 0xc4 | m_color | `gbColorQuad` |
| UIProgressBar | 0xc8 | m_dstAlpha | `int` |
| UIProgressBar | 0xcc | m_alpha | `int` |
| UIProgressBar | 0xd0 | m_minAlpha | `int` |
| UIProgressBar | 0xd4 | m_fadespeed | `float` |
| UIProgressBar | 0xd8 | m_isAdd | `BYTE` |
| UIProgressBar | 0xd9 | m_isFlash | `BYTE` |
| UIProgressBar | 0xda | m_stop | `BYTE` |
| UIProgressBar | 0xdc | m_warningval | `int` |
| UIPushButton | 0x44 | m_isDown | `unsigned char` |
| UIPushButton | 0x45 | m_isCtrl | `unsigned char` |
| UIPushButton | 0x46 | m_mouseoff | `unsigned char` |
| UIPushButton | 0x48 | m_fontcolor | `gbColorQuad` |
| UIPushButton | 0x4c | m_fonttype | `gbFontType` |
| UIPushButton | 0x50 | m_state | `UIPUSHBUTTON_STATE` |
| UIPushButton | 0x54 | m_texarray | `gbTexture *[2]` |
| UIPushButton | 0x5c | m_texarrayInfo | `_PlugInfo *[2]` |
| UIPushButton | 0x64 | m_bOn | `unsigned char` |
| UIPushButton | 0x68 | m_pOnpic | `gbTexture *` |
| UIPushButton | 0x6c | m_pOnpicInfo | `_PlugInfo *` |
| UIPushButton | 0x70 | m_pDownpic | `gbTexture *` |
| UIPushButton | 0x74 | m_pDownpicInfo | `_PlugInfo *` |
| UIPushButton | 0x78 | m_caption | `char[128]` |
| UIQuadManager | 0x0 | _tail_000 | `char[4]` |
| UIRenderObj | 0x0 | _tail_000 | `char[32]` |
| UIRoleDialog | 0x130 | _todo_130 | `char[152]` |
| UIRoleDialog | 0x1c8 | _todo_1c8 | `char[176]` |
| UIRoleDialog | 0x278 | _todo_278 | `char[344]` |
| UIRoleDialog | 0x3d0 | _todo_3d0 | `char[328]` |
| UIRoleDialog | 0x50 | _todo_050 | `char[32]` |
| UIRoleDialog | 0x518 | byMagicUseTime | `unsigned char[8][6]` |
| UIRoleDialog | 0x548 | _todo_548 | `int` |
| UIRoleDialog | 0x54c | _todo_54c | `int` |
| UIRoleDialog | 0x550 | _todo_550 | `unsigned char` |
| UIRoleDialog | 0x551 | _gap_551 | `char[4]` |
| UIRoleDialog | 0x555 | _todo_555 | `unsigned char` |
| UIRoleDialog | 0x556 | m_nTodo_556 | `char[2]` |
| UIRoleDialog | 0x70 | m_static | `UITextArea` |
| UIRoleSelect | 0x48 | baseclass2 | `PalScriptWaitObj` |
| UIRoleSelect | 0x50 | m_sel | `int` |
| UIRoleSelect | 0x510 | m_bk | `UIStaticFlex` |
| UIRoleSelect | 0x54 | m_maxlen | `int` |
| UIRoleSelect | 0x58 | m_list | `UIListBox` |
| UIRoleSelectDialog | 0x10c | m_ani | `UIAnimateCtrl` |
| UIRoleSelectDialog | 0x1b0 | m_face | `UIStaticFlip` |
| UIRoleSelectDialog | 0x254 | m_static | `UITextArea` |
| UIRoleSelectDialog | 0x314 | m_texth | `int` |
| UIRoleSelectDialog | 0x318 | m_list | `UIListBox` |
| UIRoleSelectDialog | 0x48 | m_state | `int` |
| UIRoleSelectDialog | 0x4c | m_bk | `UIStaticFlex` |
| UIRoleSelectDialog | 0x820 | m_maxlen | `int` |
| UIRoleSelectDialog | 0x824 | m_last | `float` |
| UIRoleSelectDialog | 0x828 | m_sel | `int` |
| UIRoleSelectDialog | 0x82c | m_mode | `int` |
| UIScene | 0x44 | m_nViewW | `int` |
| UIScene | 0x48 | m_fScaleY | `float` |
| UIScene | 0x4c | m_fScaleX | `float` |
| UIScene | 0x50 | m_nTodo_050 | `unsigned char` |
| UIScene | 0x54 | m_nScrollState | `int` |
| UIScene | 0x58 | m_nScrollIdx | `int` |
| UIScene | 0x5c | m_nShowState | `int` |
| UIScene | 0x60 | m_pChildWnd | `UIWnd *` |
| UIScene | 0x64 | m_nClipX | `int` |
| UIScene | 0x68 | m_nClipY | `int` |
| UIScene | 0x6c | m_nRectX | `int` |
| UIScene | 0x70 | m_nRectY | `int` |
| UIScene | 0x74 | m_nClipW | `int` |
| UIScene | 0x78 | m_nRectH | `int` |
| UIScene | 0x7c | m_nRectW | `int` |
| UIScene | 0x80 | m_nScrollWidget | `int` |
| UIScene | 0x84 | m_fPosX | `float` |
| UIScene | 0x88 | m_fPosY | `float` |
| UIScene | 0x8c | m_nLoadResource | `int` |
| UIScene | 0x90 | m_nNotifyRender | `int` |
| UIScene | 0x94 | m_dwColor | `unsigned int` |
| UIScene | 0x98 | m_hScrollBar | `int` |
| UIScene | 0x9c | m_nColors | `int` |
| UIScene | 0xa0 | m_bLoadState | `int` |
| UIScene | 0xa4 | m_pChildData | `char *` |
| UIScene | 0xa8 | m_fAngle | `float` |
| UIScene | 0xac | m_fCameraOffset | `float` |
| UIScene | 0xb0 | m_bFieldCC | `Parent_Data *` |
| UIScene | 0xb4 | m_nFieldD0 | `int` |
| UIScene | 0xb8 | m_bVisible | `Parent_Data *` |
| UIScene | 0xbc | m_hFont | `int` |
| UIScene | 0xc0 | m_bEnabled | `Parent_Data *` |
| UIScene | 0xc4 | m_pTexture | `gbTexture *` |
| UIScene | 0xc8 | m_bOverlayRender | `unsigned char` |
| UIScene | 0xc9 | m_nTodo_0C9 | `unsigned char` |
| UIScene | 0xcc | m_bCursorLeft | `unsigned char` |
| UIScene | 0xd0 | m_hTexture | `int` |
| UISceneFace | 0x138 | m_mp | `UIProgressBar` |
| UISceneFace | 0x22c | m_face | `UIStatic[3]` |
| UISceneFace | 0x3f4 | m_bk | `UIStatic` |
| UISceneFace | 0x44 | m_hp | `UIProgressBar` |
| UISceneFace | 0x48c | m_clicktime | `float` |
| UISceneFace | 0x490 | m_onclick | `int` |
| UISceneFace | 0x494 | m_state | `UIStatic[4]` |
| UISceneFrm | 0x43c | m_face | `UISceneFace` |
| UISceneFrm | 0x48 | m_map | `UISceneMap` |
| UISceneMap | 0x19c | m_base | `UIStatic` |
| UISceneMap | 0x234 | m_compass | `UIStaticEX` |
| UISceneMap | 0x2ec | m_mapbk | `UIStaticFlex` |
| UISceneMap | 0x3ac | m_icons | `UITextureArray` |
| UISceneMap | 0x3f0 | m_state | `int` |
| UISceneMap | 0x44 | m_probe | `UIButton` |
| UISceneObj | 0x0 | _tail_000 | `char[4]` |
| UIScenePanel | 0x13e0 | m_nTodo_13E0 | `void *` |
| UIScenePanel | 0x158 | m_SlotData | `int` |
| UIScenePanel | 0x15c | m_nTodo_15C | `int` |
| UIScenePanel | 0x160 | m_nTodo_160 | `int` |
| UIScenePanel | 0x164 | m_nCategoryIdx | `int` |
| UIScenePanel | 0x168 | m_Static_360 | `UIStatic` |
| UIScenePanel | 0x200 | m_pSubPanel | `float` |
| UIScenePanel | 0x204 | m_nTodo_204 | `int` |
| UIScenePanel | 0x20e0 | m_nTodo_20E0 | `void *` |
| UIScenePanel | 0x2900 | m_Static_10496 | `UIStatic` |
| UIScenePanel | 0x2998 | m_Static_10648 | `UIStatic` |
| UIScenePanel | 0x2a30 | m_Static_10800 | `UIStatic` |
| UIScenePanel | 0x2ac8 | m_Static_10952 | `UIStatic` |
| UIScenePanel | 0x2b60 | m_nTodo_2B60 | `int` |
| UIScenePanel | 0x2b64 | m_nTodo_2B64 | `int` |
| UIScenePanel | 0x2b6c | m_nTodo_11116 | `UIWnd` |
| UIScenePanel | 0x2c08 | m_nTodo_2C08 | `int` |
| UIScenePanel | 0x2c0c | m_nTodo_2C0C | `int` |
| UIScenePanel | 0x2c10 | m_nTodo_2C10 | `int` |
| UIScenePanel | 0x2c14 | m_nTodo_2C14 | `int` |
| UIScenePanel | 0x2c18 | m_nTodo_2C18 | `int` |
| UIScenePanel | 0x2c1c | m_nTodo_2C1C | `int` |
| UIScenePanel | 0x2c20 | m_nTodo_2C20 | `int` |
| UIScenePanel | 0x2c2c | m_nTodo_11308 | `UIWnd` |
| UIScenePanel | 0x2cc8 | m_nTodo_2CC8 | `int` |
| UIScenePanel | 0x2ccc | m_nTodo_2CCC | `int` |
| UIScenePanel | 0x2cd0 | m_nTodo_2CD0 | `int` |
| UIScenePanel | 0x2cd4 | m_nTodo_2CD4 | `int` |
| UIScenePanel | 0x2cd8 | m_nTodo_2CD8 | `int` |
| UIScenePanel | 0x2cdc | m_nTodo_2CDC | `int` |
| UIScenePanel | 0x2ce0 | m_nTodo_2CE0 | `int` |
| UIScenePanel | 0x2cec | m_SceneA | `UIScene` |
| UIScenePanel | 0x2e74 | m_SceneB | `UIScene` |
| UIScenePanel | 0x2ffc | m_SceneC | `UIScene` |
| UIScenePanel | 0x3184 | m_SceneD | `UIScene` |
| UIScenePanel | 0x330c | m_SceneE | `UIScene` |
| UIScenePanel | 0x3494 | m_SceneF | `UIScene` |
| UIScenePanel | 0x3608 | m_nTodo_3608 | `unsigned char` |
| UIScenePanel | 0x3609 | m_nTodo_3609 | `unsigned char` |
| UIScenePanel | 0x360c | m_nTodo_360C | `int` |
| UIScenePanel | 0x3610 | m_nTodo_3610 | `int` |
| UIScenePanel | 0x3614 | m_nTodo_3614 | `int` |
| UIScenePanel | 0x3618 | m_nObjStore | `int` |
| UIScenePanel | 0x3628 | m_hSettingsUI | `int` |
| UIScenePanel | 0x3630 | m_bPanelFlagA | `unsigned char` |
| UIScenePanel | 0x3631 | m_nTodo_3631 | `unsigned char` |
| UIScenePanel | 0x3632 | m_nTodo_3632 | `unsigned char` |
| UIScenePanel | 0x3634 | m_nPanelState | `int` |
| UIScenePanel | 0x3638 | m_bCoverReady | `int` |
| UIScenePanel | 0x363c | m_nSceneIdx | `int` |
| UIScenePanel | 0x3644 | m_bFlags0 | `unsigned char` |
| UIScenePanel | 0x3645 | m_bFlags1 | `unsigned char` |
| UIScenePanel | 0x364c | m_pCoverTexture | `int` |
| UIScenePanel | 0x3650 | m_Static_13904 | `UIStatic` |
| UIScenePanel | 0x36e8 | m_nCoverLeft | `int` |
| UIScenePanel | 0x36ec | m_nCoverTop | `int` |
| UIScenePanel | 0x36f0 | m_nCoverRight | `int` |
| UIScenePanel | 0x36f4 | m_nCoverBottom | `int` |
| UIScenePanel | 0x36f8 | m_fAnimRate | `int` |
| UIScenePanel | 0x36fc | m_fAnimBase | `int` |
| UIScenePanel | 0x3700 | m_Static_14080 | `UIStatic` |
| UIScenePanel | 0x486 | m_bPanelActive | `unsigned char` |
| UIScenePanel | 0x978 | m_pPanelSlot0 | `int` |
| UIScenePanel | 0xa10 | m_pPanelSlot1 | `int` |
| UIScenePanel | 0xaa8 | m_pPanelSlot2 | `int` |
| UIScenePanel | 0xb40 | m_pPanelSlot3 | `int` |
| UIScenePanel | 0xbd8 | m_pPanelSlot4 | `int` |
| UIScenePanel | 0xccc | m_pPanelSlot5 | `int` |
| UIScenePanel | 0xd64 | m_pPanelSlot6 | `int` |
| UIScenePanel | 0xdfc | m_pPanelSlot7 | `int` |
| UIScenePanel | 0xef0 | m_pPanelSlot8 | `int` |
| UIScrollBar | 0x104 | m_texarrayInfo | `_PlugInfo *[10]` |
| UIScrollBar | 0x12c | m_keytime | `float` |
| UIScrollBar | 0x130 | m_btnrect | `tagRECT[2]` |
| UIScrollBar | 0x150 | m_slideroffset | `int` |
| UIScrollBar | 0x154 | m_slidertboffset | `int` |
| UIScrollBar | 0x158 | m_sliderw | `int` |
| UIScrollBar | 0x15c | m_sliderh | `int` |
| UIScrollBar | 0x44 | m_bPress | `unsigned char` |
| UIScrollBar | 0x45 | m_bPressed | `unsigned char` |
| UIScrollBar | 0x48 | m_bk | `UIFlexBar` |
| UIScrollBar | 0x9c | m_btnH | `int` |
| UIScrollBar | 0xa0 | m_mouseat | `int` |
| UIScrollBar | 0xa4 | m_min | `int` |
| UIScrollBar | 0xa8 | m_max | `int` |
| UIScrollBar | 0xac | m_pos | `int` |
| UIScrollBar | 0xb0 | m_lastpos | `float` |
| UIScrollBar | 0xb4 | m_drawpos | `float` |
| UIScrollBar | 0xb8 | m_step | `float` |
| UIScrollBar | 0xbc | m_pagesize | `int` |
| UIScrollBar | 0xc0 | m_texarray | `UITextureArray` |
| UIScrollBar_SB_AREA | 0x0 | _tail_000 | `char[4]` |
| UISelectDialog | 0x0 | _tail_000 | `char[4]` |
| UISlider | 0x0 | _tail_000 | `char[4]` |
| UIStatic | 0x44 | pDebugTex | `gbTexture *` |
| UIStatic | 0x48 | m_align | `int` |
| UIStatic | 0x4c | m_ratiow | `float` |
| UIStatic | 0x50 | m_ratioh | `float` |
| UIStatic | 0x54 | m_textx | `void *` |
| UIStatic | 0x58 | m_texty | `void *` |
| UIStatic | 0x5c | m_fonttype | `Parent_Data *` |
| UIStatic | 0x60 | m_text | `char[16]` |
| UIStatic | 0x70 | m_pbk | `gbTexture *` |
| UIStatic | 0x74 | m_pbkInfo | `_PlugInfo *` |
| UIStatic | 0x78 | m_ppic | `gbTexture *` |
| UIStatic | 0x7c | m_ppicInfo | `_PlugInfo *` |
| UIStatic | 0x80 | m_disablepic | `gbTexture *` |
| UIStatic | 0x84 | m_disablepicInfo | `_PlugInfo *` |
| UIStatic | 0x88 | m_pbk2 | `gbTexture *` |
| UIStatic | 0x8c | m_mouseoff | `unsigned char` |
| UIStatic | 0x90 | m_FVF | `int` |
| UIStatic | 0x94 | m_nTextW | `int` |
| UIStaticCB | 0x98 | m_showct | `int` |
| UIStaticEX | 0x98 | m_rotate | `float` |
| UIStaticEX | 0x9c | m_rotmode | `int` |
| UIStaticEX | 0xa0 | m_rotdst | `float` |
| UIStaticEX | 0xa4 | m_rotspeed | `float` |
| UIStaticEX | 0xa8 | m_rotdir | `int` |
| UIStaticEX | 0xac | m_isStoped | `unsigned char` |
| UIStaticEX | 0xb0 | m_accelerate | `float` |
| UIStaticEX | 0xb4 | m_notespeed | `float` |
| UIStaticEXA | 0xb8 | center_x | `int` |
| UIStaticEXA | 0xbc | center_y | `int` |
| UIStaticFlex | 0x44 | m_currect | `tagRECT` |
| UIStaticFlex | 0x54 | m_texs | `UITextureArray` |
| UIStaticFlex | 0x98 | m_state | `UIStaticFlex_State` |
| UIStaticFlex | 0x9c | m_statetime | `float` |
| UIStaticFlex | 0xa0 | m_fonttype | `gbFontType` |
| UIStaticFlex | 0xa4 | m_tilesize | `int` |
| UIStaticFlex | 0xa8 | m_openstyle | `int` |
| UIStaticFlex_State | 0x0 | _tail_000 | `char[4]` |
| UIStaticFlip | 0x98 | flipMode | `int` |
| UIStaticRM | 0x98 | m_color | `gbColorQuad` |
| UIStaticRM | 0x9c | m_dstAlpha | `int` |
| UIStaticRM | 0xa0 | m_alpha | `int` |
| UIStaticRM | 0xa4 | m_minAlpha | `int` |
| UIStaticRM | 0xa8 | m_fadespeed | `float` |
| UIStaticRM | 0xac | m_isAdd | `unsigned char` |
| UIStaticRM | 0xad | m_isFlash | `unsigned char` |
| UIStaticRM | 0xae | m_stop | `unsigned char` |
| UIStaticRM | 0xb0 | m_mode | `int` |
| UISystem | 0x0 | _tail_000 | `char[4]` |
| UITabBtn | 0x0 | m_BtnAndID | `std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >` |
| UITabBtn | 0x10 | m_SelBtn | `int` |
| UITabBtn | 0x14 | m_pFather | `UIWnd *` |
| UITabCtrl | 0x44 | m_itemwidth | `int` |
| UITabCtrl | 0x48 | m_texarray | `UITextureArray` |
| UITabCtrl | 0x8c | m_numpage | `int` |
| UITabCtrl | 0x90 | m_onpage | `int` |
| UITextArea | 0x44 | m_fFadeDuration | `float` |
| UITextArea | 0x48 | m_fFadeInit | `float` |
| UITextArea | 0x4c | m_nFadeElapsed | `int` |
| UITextArea | 0x50 | m_bFadeActive | `int` |
| UITextArea | 0x54 | m_nReserved54 | `int` |
| UITextArea | 0x58 | m_nRectLeft | `int` |
| UITextArea | 0x5c | m_nRectTop | `int` |
| UITextArea | 0x60 | m_nRectRight | `int` |
| UITextArea | 0x64 | m_nRectBottom | `int` |
| UITextArea | 0x68 | m_todo_68 | `char[68]` |
| UITextArea | 0xac | m_nRenderMode | `int` |
| UITextArea | 0xb0 | m_fFadeAlpha | `float` |
| UITextArea | 0xb4 | m_nRenderArg | `int` |
| UITextArea | 0xb8 | m_nFadeThreshold | `int` |
| UITextArea | 0xbc | m_bFadeReverse | `int` |
| UITextureArray | 0x0 | m_ptex | `gbTexture *[16]` |
| UITextureArray | 0x40 | m_num | `int` |
| UITitle | 0x114 | m_nInitRoles | `UIWnd *` |
| UITitle | 0x1244 | m_ItemSlotC | `UIItem` |
| UITitle | 0x179c | m_ItemSlotD | `UIItem` |
| UITitle | 0x1ac | m_subObjA | `UIStatic` |
| UITitle | 0x1cf4 | m_nTitleStage | `int` |
| UITitle | 0x1cf8 | m_bScriptActive | `unsigned char` |
| UITitle | 0x210c | m_nTitleScript | `int` |
| UITitle | 0x2510 | m_nScriptHandleA | `int` |
| UITitle | 0x2514 | m_nScriptHandleB | `int` |
| UITitle | 0x2518 | m_nScriptHandleC | `int` |
| UITitle | 0x251c | m_nScriptHandleD | `int` |
| UITitle | 0x2520 | m_nScriptHandleE | `int` |
| UITitle | 0x2524 | m_nScriptHandleF | `int` |
| UITitle | 0x2528 | m_bScriptRunning | `unsigned char` |
| UITitle | 0x374 | m_RoleDataA | `CScreenMode *` |
| UITitle | 0x3dc | m_nTodo_3DC | `int` |
| UITitle | 0x3e0 | m_nTodo_3E0 | `int` |
| UITitle | 0x4c | m_rcWindow | `tagRECT` |
| UITitle | 0x4cc | m_RoleDataB | `CScreenMode *` |
| UITitle | 0x534 | m_nTodo_534 | `int` |
| UITitle | 0x538 | m_nTodo_538 | `int` |
| UITitle | 0x5c | m_rcWidgetRect | `tagRECT` |
| UITitle | 0x624 | m_RoleDataC | `CScreenMode *` |
| UITitle | 0x68c | m_nTodo_68C | `int` |
| UITitle | 0x690 | m_nTodo_690 | `int` |
| UITitle | 0x6c | m_nTodo_06C | `int` |
| UITitle | 0x70 | m_nTodo_070 | `int` |
| UITitle | 0x77c | m_ItemSlotA | `UIItem` |
| UITitle | 0x7c | m_nTodo_07C | `UIWnd *` |
| UITitle | 0xcd4 | m_bInitRoles | `unsigned char` |
| UITitle | 0xcd8 | m_hEffect | `int` |
| UITitle | 0xcdc | m_dwEffectTick | `int` |
| UITitle | 0xce0 | m_dwTimerTick | `int` |
| UITitle | 0xce4 | m_bTimerActive | `unsigned char` |
| UITitle | 0xce8 | m_bTimerDone | `unsigned char` |
| UITitle | 0xce9 | m_bTimerProcessed | `unsigned char` |
| UITitle | 0xcec | m_ItemSlotB | `UIItem` |
| UITitle_ArcSave | 0x48 | m_YesNo | `MUIDialog` |
| UITitle_BBTY | 0x168 | m_background | `UIStatic` |
| UITitle_BBTY | 0x208 | m_remark | `UIStatic` |
| UITitle_BBTY | 0x2a8 | m_btn | `UIButtonEXA[3]` |
| UITitle_BBTY | 0x48 | rc | `tagRECT` |
| UITitle_BBTY | 0x58 | bkWndX | `int` |
| UITitle_BBTY | 0x5c | bkWndY | `int` |
| UITitle_BBTY | 0x60 | i | `int` |
| UITitle_BBTY | 0x64 | j | `int` |
| UITitle_BBTY | 0x68 | buf | `char[256]` |
| UITitle_BBTY | 0x710 | m_exit | `UIButton` |
| UITitle_BBTY | 0x868 | m_Name | `UIStatic` |
| UITitle_BBTY | 0x908 | m_Left | `UIStatic` |
| UITitle_BBTY | 0x9a8 | m_Right | `UIStatic` |
| UITitle_BBTY | 0xa48 | m_FlagT | `UIStatic` |
| UITitle_BBTY | 0xae8 | m_FlagB | `UIStatic` |
| UITitle_BBTY | 0xb88 | m_Start | `UIButton` |
| UITitle_BBTY | 0xce0 | m_Notes | `UIButton` |
| UITitle_JDHY | 0x158 | m_OutFrameT | `UIStatic` |
| UITitle_JDHY | 0x1f8 | m_OutFrameR | `UIStatic` |
| UITitle_JDHY | 0x298 | m_OutFrameL | `UIStatic` |
| UITitle_JDHY | 0x338 | m_OutFrameB | `UIStatic` |
| UITitle_JDHY | 0x3d8 | m_background | `UIStatic` |
| UITitle_JDHY | 0x478 | m_exit | `UIButton` |
| UITitle_JDHY | 0x48 | rc | `tagRECT` |
| UITitle_JDHY | 0x58 | buf | `char[256]` |
| UITitle_JDHY | 0x5a7e4 | m_Title_JDHY | `UIStatic` |
| UITitle_JDHY | 0x5a884 | m_TopBar | `UIStatic` |
| UITitle_JDHY | 0x5a924 | m_BottomBar | `UIStatic` |
| UITitle_JDHY | 0x5a9c4 | m_BackBar | `UIStatic` |
| UITitle_JDHY | 0x5aa64 | m_BackBar2 | `UIStatic` |
| UITitle_JDHY | 0x5ab04 | m_pbPage | `UIPushButton[10]` |
| UITitle_JDHY | 0x5b4dc | m_Scroll | `UIScrollBar` |
| UITitle_JDHY | 0x5b64c | m_CurScrollPos | `int` |
| UITitle_JDHY | 0x5b650 | m_ItemH | `int` |
| UITitle_JDHY | 0x5b654 | m_ItemW | `int` |
| UITitle_JDHY | 0x5b658 | m_firstItem | `int` |
| UITitle_JDHY | 0x5b65c | m_selItem | `int` |
| UITitle_JDHY | 0x5b660 | m_getNote | `int` |
| UITitle_JDHY | 0x5b664 | m_loading | `int` |
| UITitle_JDHY | 0x5b668 | m_passtime | `float` |
| UITitle_JDHY | 0x5b66c | m_LoadBtn | `UIButton` |
| UITitle_JDHY | 0x5b7c4 | m_DeleteBtn | `UIButton` |
| UITitle_JDHY | 0x5b91c | m_noteState | `NOTE_STATE` |
| UITitle_JDHY | 0x5d0 | m_isItemShow | `unsigned char[99]` |
| UITitle_JDHY | 0x634 | m_NoteItem | `Note_Item[99]` |
| UITitle_QCYM | 0x158 | m_OutFrameT | `UIStatic` |
| UITitle_QCYM | 0x1f8 | m_OutFrameR | `UIStatic` |
| UITitle_QCYM | 0x298 | m_OutFrameL | `UIStatic` |
| UITitle_QCYM | 0x338 | m_OutFrameB | `UIStatic` |
| UITitle_QCYM | 0x3d8 | m_background | `UIStatic` |
| UITitle_QCYM | 0x478 | m_title | `UIStatic` |
| UITitle_QCYM | 0x48 | rc | `tagRECT` |
| UITitle_QCYM | 0x518 | m_btn | `UIButtonEXA[30]` |
| UITitle_QCYM | 0x58 | buf | `char[256]` |
| UITitle_XJTM | 0x100 | m_OutFrameR | `UIStatic` |
| UITitle_XJTM | 0x1314 | m_ItemInfo | `UIStatic` |
| UITitle_XJTM | 0x1a0 | m_OutFrameL | `UIStatic` |
| UITitle_XJTM | 0x240 | m_OutFrameB | `UIStatic` |
| UITitle_XJTM | 0x2e0 | m_background | `UIStatic` |
| UITitle_XJTM | 0x380 | m_title | `UIStatic` |
| UITitle_XJTM | 0x420 | m_exit | `UIButton` |
| UITitle_XJTM | 0x48 | rc | `tagRECT` |
| UITitle_XJTM | 0x578 | m_IsActive | `unsigned char` |
| UITitle_XJTM | 0x57c | m_pMgr | `UICoverFrm *` |
| UITitle_XJTM | 0x58 | bkWndX | `int` |
| UITitle_XJTM | 0x580 | m_Item | `_Item` |
| UITitle_XJTM | 0x5b0 | m_SelFirstRow | `int` |
| UITitle_XJTM | 0x5b4 | m_SelSecondRow | `int` |
| UITitle_XJTM | 0x5b8 | m_SelFirstChanged | `unsigned char` |
| UITitle_XJTM | 0x5b9 | m_SelSecondChanged | `unsigned char` |
| UITitle_XJTM | 0x5ba | m_SelZeroChanged | `unsigned char` |
| UITitle_XJTM | 0x5bc | m_WordBk | `UIStatic` |
| UITitle_XJTM | 0x5c | bkWndY | `int` |
| UITitle_XJTM | 0x60 | m_OutFrameT | `UIStatic` |
| UITitle_XJTM | 0x65c | m_BtnBk | `UIStatic` |
| UITitle_XJTM | 0x6fc | m_BtnFirstRow | `UIButton[4]` |
| UITitle_XJTM | 0xc5c | m_BtnSecondRow | `UIButton[5]` |
| UITitle_YXXX | 0x198 | m_OutFrameL | `UIStatic` |
| UITitle_YXXX | 0x238 | m_OutFrameB | `UIStatic` |
| UITitle_YXXX | 0x2d8 | m_background | `UIStatic` |
| UITitle_YXXX | 0x378 | m_title | `UIStatic` |
| UITitle_YXXX | 0x418 | m_exit | `UIButton` |
| UITitle_YXXX | 0x48 | rc | `tagRECT` |
| UITitle_YXXX | 0x570 | m_ZZRY | `UIButton` |
| UITitle_YXXX | 0x58 | m_OutFrameT | `UIStatic` |
| UITitle_YXXX | 0x6c8 | m_XGWZ | `UIButton` |
| UITitle_YXXX | 0x820 | m_WordBk | `UIStatic` |
| UITitle_YXXX | 0xf8 | m_OutFrameR | `UIStatic` |
| UIWnd | 0x10 | m_rect | `tagRECT` |
| UIWnd | 0x20 | m_pfather | `UIWnd *` |
| UIWnd | 0x24 | m_childs | `PtrArray` |
| UIWnd | 0x34 | m_bcreateok | `int` |
| UIWnd | 0x38 | m_bvisible | `int` |
| UIWnd | 0x3c | m_benable | `int` |
| UIWnd | 0x4 | m_fontcolor | `gbColorQuad` |
| UIWnd | 0x40 | m_bfocus | `int` |
| UIWnd | 0x8 | m_wndcolor | `gbColorQuad` |
| UIWnd | 0xc | m_id | `unsigned int` |
| UnderWater | 0x0 | m_bEnable | `BYTE` |
| UnderWater | 0x10 | m_iMode | `int` |
| UnderWater | 0x14 | m_fTime | `float` |
| UnderWater | 0x4 | m_pIB | `IDirect3DIndexBuffer9 *` |
| UnderWater | 0x8 | m_pVB | `IDirect3DVertexBuffer9 *` |
| UnderWater | 0xc | m_pBumpmapTex | `IDirect3DTexture9 *` |
| UnwindMapEntry | 0x0 | toState | `int` |
| UnwindMapEntry | 0x4 | action | `char *` |
| VertPoolMgr | 0x0 | _tail_000 | `char[4]` |
| VideoPlayer | 0x0 | _tail_000 | `char[4]` |
| WAVEFORMAT | 0x0 | wFormatTag | `WORD` |
| WAVEFORMAT | 0x2 | nChannels | `WORD` |
| WAVEFORMAT | 0x4 | nSamplesPerSec | `UINT` |
| WAVEFORMAT | 0x8 | nAvgBytesPerSec | `UINT` |
| WAVEFORMAT | 0xc | nBlockAlign | `WORD` |
| WeatherEffectNode | 0x0 | _tail_000 | `char[8]` |
| WishPool | 0x0 | open | `BYTE` |
| WishPool | 0x4 | money | `int` |
| WishPool | 0x8 | flower | `BYTE` |
| XJ_Pic | 0x8 | m_fElapsed | `float` |
| XJ_Pic | 0xc | m_bEnd | `BYTE` |
| _ADPCMDATATAG | 0x0 | blocksize | `DWORD` |
| _ADPCMDATATAG | 0x10 | savesrc | `DWORD` |
| _ADPCMDATATAG | 0x14 | sample | `DWORD` |
| _ADPCMDATATAG | 0x18 | destend | `DWORD` |
| _ADPCMDATATAG | 0x1c | srcend | `DWORD` |
| _ADPCMDATATAG | 0x20 | samplesL | `DWORD` |
| _ADPCMDATATAG | 0x24 | samplesR | `DWORD` |
| _ADPCMDATATAG | 0x28 | moresamples | `unsigned short[16]` |
| _ADPCMDATATAG | 0x4 | extrasamples | `DWORD` |
| _ADPCMDATATAG | 0x8 | blockleft | `DWORD` |
| _ADPCMDATATAG | 0xc | step | `DWORD` |
| _Btn_BtnID | 0x0 | _pBtn | `UIButton *` |
| _Btn_BtnID | 0x4 | _btnID | `DWORD` |
| _CLOUD | 0x0 | _cloud | `UIStatic` |
| _CLOUD | 0x98 | _cloudRc | `tagRECT` |
| _CLOUD | 0xa8 | _width | `int` |
| _CLOUD | 0xac | _height | `int` |
| _CLOUD | 0xb0 | _cloudSpeed | `float` |
| _CLOUD | 0xb4 | _alpha | `float` |
| _CLOUD | 0xb8 | _fade | `float` |
| _CLOUD | 0xbc | _isfade | `BYTE` |
| _CLOUD | 0xc0 | _up | `int` |
| _CLOUD | 0xc4 | _yPt | `int` |
| _CLOUD | 0xc8 | _fluctuate | `int` |
| _CONTEXT | 0x0 | ContextFlags | `DWORD` |
| _CONTEXT | 0x10 | Dr3 | `DWORD` |
| _CONTEXT | 0x14 | Dr6 | `DWORD` |
| _CONTEXT | 0x18 | Dr7 | `DWORD` |
| _CONTEXT | 0x1c | FloatSave | `_FLOATING_SAVE_AREA` |
| _CONTEXT | 0x4 | Dr0 | `DWORD` |
| _CONTEXT | 0x8 | Dr1 | `DWORD` |
| _CONTEXT | 0x8c | SegGs | `DWORD` |
| _CONTEXT | 0x90 | SegFs | `DWORD` |
| _CONTEXT | 0x94 | SegEs | `DWORD` |
| _CONTEXT | 0x98 | SegDs | `DWORD` |
| _CONTEXT | 0x9c | Edi | `DWORD` |
| _CONTEXT | 0xa0 | Esi | `DWORD` |
| _CONTEXT | 0xa4 | Ebx | `DWORD` |
| _CONTEXT | 0xa8 | Edx | `DWORD` |
| _CONTEXT | 0xac | Ecx | `DWORD` |
| _CONTEXT | 0xb0 | Eax | `DWORD` |
| _CONTEXT | 0xb4 | Ebp | `DWORD` |
| _CONTEXT | 0xb8 | Eip | `DWORD` |
| _CONTEXT | 0xbc | SegCs | `DWORD` |
| _CONTEXT | 0xc | Dr2 | `DWORD` |
| _CONTEXT | 0xc0 | EFlags | `DWORD` |
| _CONTEXT | 0xc4 | Esp | `DWORD` |
| _CONTEXT | 0xc8 | SegSs | `DWORD` |
| _CONTEXT | 0xcc | ExtendedRegisters | `unsigned char[512]` |
| _Collvec | 0x0 | _Hand | `DWORD` |
| _Collvec | 0x4 | _Page | `UINT` |
| _Console | 0x0 | m_numcmd | `int` |
| _Console | 0x2204 | m_rect | `tagRECT` |
| _Console | 0x2214 | m_bactive | `int` |
| _Console | 0x2218 | m_bEnable | `int` |
| _Console | 0x221c | m_color | `gbColorQuad` |
| _Console | 0x2220 | m_inputbuf | `char[100]` |
| _Console | 0x2284 | m_showbuf | `char[100][17]` |
| _Console | 0x2928 | m_fontcolor | `gbColorQuad` |
| _Console | 0x4 | m_cmd | `_Console__ConCmd[64]` |
| _Console__ConCmd | 0x0 | _tail_000 | `char[136]` |
| _Ctypevec | 0x0 | _Hand | `DWORD` |
| _Ctypevec | 0x4 | _Page | `UINT` |
| _Ctypevec | 0x8 | _Table | `short *` |
| _Ctypevec | 0xc | _Delfl | `int` |
| _Cvtvec | 0x0 | _Hand | `DWORD` |
| _Cvtvec | 0x4 | _Page | `UINT` |
| _DIACTIONA | 0x0 | uAppData | `UINT` |
| _DIACTIONA | 0x10 | guidInstance | `_GUID` |
| _DIACTIONA | 0x20 | dwObjID | `DWORD` |
| _DIACTIONA | 0x24 | dwHow | `DWORD` |
| _DIACTIONA | 0x4 | dwSemantic | `DWORD` |
| _DIACTIONA | 0x8 | dwFlags | `DWORD` |
| _DIACTIONA | 0xc | uResIdString | `UINT` |
| _DIACTIONFORMATA | 0x0 | dwSize | `DWORD` |
| _DIACTIONFORMATA | 0x10 | rgoAction | `_DIACTIONA *` |
| _DIACTIONFORMATA | 0x14 | guidActionMap | `_GUID` |
| _DIACTIONFORMATA | 0x24 | dwGenre | `DWORD` |
| _DIACTIONFORMATA | 0x28 | dwBufferSize | `DWORD` |
| _DIACTIONFORMATA | 0x2c | lAxisMin | `long` |
| _DIACTIONFORMATA | 0x30 | lAxisMax | `long` |
| _DIACTIONFORMATA | 0x34 | hInstString | `HINSTANCE__ *` |
| _DIACTIONFORMATA | 0x38 | ftTimeStamp | `_FILETIME` |
| _DIACTIONFORMATA | 0x4 | dwActionSize | `DWORD` |
| _DIACTIONFORMATA | 0x40 | dwCRC | `DWORD` |
| _DIACTIONFORMATA | 0x44 | tszActionMap | `char[324]` |
| _DIACTIONFORMATA | 0x8 | dwDataSize | `DWORD` |
| _DIACTIONFORMATA | 0xc | dwNumActions | `DWORD` |
| _DICOLORSET | 0x0 | dwSize | `DWORD` |
| _DICOLORSET | 0x10 | cCalloutHighlight | `DWORD` |
| _DICOLORSET | 0x14 | cBorder | `DWORD` |
| _DICOLORSET | 0x18 | cControlFill | `DWORD` |
| _DICOLORSET | 0x1c | cHighlightFill | `DWORD` |
| _DICOLORSET | 0x20 | cAreaFill | `DWORD` |
| _DICOLORSET | 0x4 | cTextFore | `DWORD` |
| _DICOLORSET | 0x8 | cTextHighlight | `DWORD` |
| _DICOLORSET | 0xc | cCalloutLine | `DWORD` |
| _DICONFIGUREDEVICESPARAMSA | 0x0 | dwSize | `DWORD` |
| _DICONFIGUREDEVICESPARAMSA | 0x10 | lprgFormats | `_DIACTIONFORMATA *` |
| _DICONFIGUREDEVICESPARAMSA | 0x14 | hwnd | `HWND__ *` |
| _DICONFIGUREDEVICESPARAMSA | 0x18 | dics | `_DICOLORSET` |
| _DICONFIGUREDEVICESPARAMSA | 0x3c | lpUnkDDSTarget | `IUnknown *` |
| _DICONFIGUREDEVICESPARAMSA | 0x4 | dwcUsers | `DWORD` |
| _DICONFIGUREDEVICESPARAMSA | 0x8 | lptszUserNames | `char *` |
| _DICONFIGUREDEVICESPARAMSA | 0xc | dwcFormats | `DWORD` |
| _DIDATAFORMAT | 0x0 | dwSize | `DWORD` |
| _DIDATAFORMAT | 0x10 | dwNumObjs | `DWORD` |
| _DIDATAFORMAT | 0x14 | rgodf | `_DIOBJECTDATAFORMAT *` |
| _DIDATAFORMAT | 0x4 | dwObjSize | `DWORD` |
| _DIDATAFORMAT | 0x8 | dwFlags | `DWORD` |
| _DIDATAFORMAT | 0xc | dwDataSize | `DWORD` |
| _DIDEVICEIMAGEINFOA | 0x0 | tszImagePath | `char[324]` |
| _DIDEVICEIMAGEINFOA | 0x144 | dwFlags | `DWORD` |
| _DIDEVICEIMAGEINFOA | 0x148 | dwViewID | `DWORD` |
| _DIDEVICEIMAGEINFOA | 0x14c | rcOverlay | `tagRECT` |
| _DIDEVICEIMAGEINFOA | 0x15c | dwObjID | `DWORD` |
| _DIDEVICEIMAGEINFOA | 0x160 | dwcValidPts | `DWORD` |
| _DIDEVICEIMAGEINFOA | 0x164 | rgptCalloutLine | `tagPOINT[5]` |
| _DIDEVICEIMAGEINFOA | 0x18c | rcCalloutRect | `tagRECT` |
| _DIDEVICEIMAGEINFOA | 0x19c | dwTextAlign | `DWORD` |
| _DIDEVICEIMAGEINFOHEADERA | 0x0 | dwSize | `DWORD` |
| _DIDEVICEIMAGEINFOHEADERA | 0x10 | dwcAxes | `DWORD` |
| _DIDEVICEIMAGEINFOHEADERA | 0x14 | dwcPOVs | `DWORD` |
| _DIDEVICEIMAGEINFOHEADERA | 0x18 | dwBufferSize | `DWORD` |
| _DIDEVICEIMAGEINFOHEADERA | 0x1c | dwBufferUsed | `DWORD` |
| _DIDEVICEIMAGEINFOHEADERA | 0x20 | lprgImageInfoArray | `_DIDEVICEIMAGEINFOA *` |
| _DIDEVICEIMAGEINFOHEADERA | 0x4 | dwSizeImageInfo | `DWORD` |
| _DIDEVICEIMAGEINFOHEADERA | 0x8 | dwcViews | `DWORD` |
| _DIDEVICEIMAGEINFOHEADERA | 0xc | dwcButtons | `DWORD` |
| _DIG_DRIVER | 0x0 | tag | `char[4]` |
| _DIG_DRIVER | 0x10 | master_volume | `long` |
| _DIG_DRIVER | 0x100 | DS_use_default_format | `long` |
| _DIG_DRIVER | 0x104 | use_MMX | `long` |
| _DIG_DRIVER | 0x108 | decode_buffer | `char *` |
| _DIG_DRIVER | 0x10c | decode_buffer_size | `long` |
| _DIG_DRIVER | 0x110 | us_count | `DWORD` |
| _DIG_DRIVER | 0x114 | ms_count | `DWORD` |
| _DIG_DRIVER | 0x118 | last_ms_polled | `DWORD` |
| _DIG_DRIVER | 0x11c | last_percent | `DWORD` |
| _DIG_DRIVER | 0x120 | pipeline | `DPINFO[4]` |
| _DIG_DRIVER | 0x14 | DMA_rate | `long` |
| _DIG_DRIVER | 0x18 | hw_format | `long` |
| _DIG_DRIVER | 0x1c | hw_mode_flags | `DWORD` |
| _DIG_DRIVER | 0x20 | channels_per_sample | `long` |
| _DIG_DRIVER | 0x24 | bytes_per_channel | `long` |
| _DIG_DRIVER | 0x28 | channels_per_buffer | `long` |
| _DIG_DRIVER | 0x2c | samples_per_buffer | `long` |
| _DIG_DRIVER | 0x2c0 | reverb_buffer | `int *` |
| _DIG_DRIVER | 0x2c4 | reverb_buffer_size | `long` |
| _DIG_DRIVER | 0x2c8 | reverb_buffer_position | `long` |
| _DIG_DRIVER | 0x2cc | no_wom_done | `long` |
| _DIG_DRIVER | 0x2d0 | wom_done_buffers | `DWORD` |
| _DIG_DRIVER | 0x30 | playing | `long` |
| _DIG_DRIVER | 0x34 | samples | `_SAMPLE *` |
| _DIG_DRIVER | 0x38 | n_samples | `long` |
| _DIG_DRIVER | 0x3c | build_size | `long` |
| _DIG_DRIVER | 0x4 | backgroundtimer | `long` |
| _DIG_DRIVER | 0x40 | build_buffer | `int *` |
| _DIG_DRIVER | 0x44 | system_data | `long[8]` |
| _DIG_DRIVER | 0x64 | buffer_size | `long` |
| _DIG_DRIVER | 0x68 | hWaveOut | `HWAVEOUT__ *` |
| _DIG_DRIVER | 0x6c | reset_works | `DWORD` |
| _DIG_DRIVER | 0x70 | request_reset | `DWORD` |
| _DIG_DRIVER | 0x74 | first | `wavehdr_tag *` |
| _DIG_DRIVER | 0x78 | n_buffers | `long` |
| _DIG_DRIVER | 0x7c | return_list | `wavehdr_tag * *` |
| _DIG_DRIVER | 0x8 | quiet | `long` |
| _DIG_DRIVER | 0x80 | return_head | `long` |
| _DIG_DRIVER | 0x84 | return_tail | `long` |
| _DIG_DRIVER | 0x88 | deviceid | `DWORD` |
| _DIG_DRIVER | 0x8c | wformat | `pcmwaveformat_tag` |
| _DIG_DRIVER | 0x9c | guid | `DWORD` |
| _DIG_DRIVER | 0xa0 | pDS | `char *` |
| _DIG_DRIVER | 0xa4 | ds_priority | `DWORD` |
| _DIG_DRIVER | 0xa8 | emulated_ds | `long` |
| _DIG_DRIVER | 0xac | lppdsb | `char *` |
| _DIG_DRIVER | 0xb0 | dsHwnd | `DWORD` |
| _DIG_DRIVER | 0xb4 | lpbufflist | `char *` |
| _DIG_DRIVER | 0xb8 | samp_list | `_SAMPLE * *` |
| _DIG_DRIVER | 0xbc | sec_format | `int *` |
| _DIG_DRIVER | 0xc | n_active_samples | `long` |
| _DIG_DRIVER | 0xc0 | max_buffs | `long` |
| _DIG_DRIVER | 0xc4 | released | `long` |
| _DIG_DRIVER | 0xc8 | foreground_timer | `DWORD` |
| _DIG_DRIVER | 0xcc | next | `_DIG_DRIVER *` |
| _DIG_DRIVER | 0xd0 | callingCT | `long` |
| _DIG_DRIVER | 0xd4 | callingDS | `long` |
| _DIG_DRIVER | 0xd8 | DS_initialized | `long` |
| _DIG_DRIVER | 0xdc | DS_sec_buff | `char *` |
| _DIG_DRIVER | 0xe0 | DS_out_buff | `char *` |
| _DIG_DRIVER | 0xe4 | DS_buffer_size | `long` |
| _DIG_DRIVER | 0xe8 | DS_frag_cnt | `long` |
| _DIG_DRIVER | 0xec | DS_frag_size | `long` |
| _DIG_DRIVER | 0xf0 | DS_last_frag | `long` |
| _DIG_DRIVER | 0xf4 | DS_last_write | `long` |
| _DIG_DRIVER | 0xf8 | DS_last_timer | `long` |
| _DIG_DRIVER | 0xfc | DS_skip_time | `long` |
| _DIOBJECTDATAFORMAT | 0x0 | pguid | `_GUID *` |
| _DIOBJECTDATAFORMAT | 0x4 | dwOfs | `DWORD` |
| _DIOBJECTDATAFORMAT | 0x8 | dwType | `DWORD` |
| _DIOBJECTDATAFORMAT | 0xc | dwFlags | `DWORD` |
| _EH3_EXCEPTION_REGISTRATION | 0x0 | Next | `struct _EH3_EXCEPTION_REGISTRATION *` |
| _EH3_EXCEPTION_REGISTRATION | 0x4 | ExceptionHandler | `PVOID` |
| _EH3_EXCEPTION_REGISTRATION | 0x8 | ScopeTable | `PSCOPETABLE_ENTRY` |
| _EH3_EXCEPTION_REGISTRATION | 0xc | TryLevel | `DWORD` |
| _EXCEPTION_POINTERS | 0x0 | ExceptionRecord | `_EXCEPTION_RECORD *` |
| _EXCEPTION_POINTERS | 0x4 | ContextRecord | `_CONTEXT *` |
| _EXCEPTION_RECORD | 0x0 | ExceptionCode | `unsigned int` |
| _EXCEPTION_RECORD | 0x10 | NumberParameters | `unsigned int` |
| _EXCEPTION_RECORD | 0x14 | ExceptionInformation | `unsigned long[15]` |
| _EXCEPTION_RECORD | 0x4 | ExceptionFlags | `unsigned int` |
| _EXCEPTION_RECORD | 0x8 | ExceptionRecord | `_EXCEPTION_RECORD *` |
| _EXCEPTION_RECORD | 0xc | ExceptionAddress | `char *` |
| _FLOATING_SAVE_AREA | 0x0 | ControlWord | `DWORD` |
| _FLOATING_SAVE_AREA | 0x10 | ErrorSelector | `DWORD` |
| _FLOATING_SAVE_AREA | 0x14 | DataOffset | `DWORD` |
| _FLOATING_SAVE_AREA | 0x18 | DataSelector | `DWORD` |
| _FLOATING_SAVE_AREA | 0x1c | RegisterArea | `unsigned char[80]` |
| _FLOATING_SAVE_AREA | 0x4 | StatusWord | `DWORD` |
| _FLOATING_SAVE_AREA | 0x6c | Cr0NpxState | `DWORD` |
| _FLOATING_SAVE_AREA | 0x8 | TagWord | `DWORD` |
| _FLOATING_SAVE_AREA | 0xc | ErrorOffset | `DWORD` |
| _FLOORPARAM | 0x0 | m_GoundPt | `tagPOINT` |
| _FLOORPARAM | 0x8 | m_Valid | `BYTE` |
| _FLTPROVIDER | 0x0 | PROVIDER_query_attribute | `char *` |
| _FLTPROVIDER | 0x10 | set_provider_preference | `char *` |
| _FLTPROVIDER | 0x14 | open_driver | `char *` |
| _FLTPROVIDER | 0x18 | close_driver | `char *` |
| _FLTPROVIDER | 0x1c | premix_process | `char *` |
| _FLTPROVIDER | 0x20 | postmix_process | `char *` |
| _FLTPROVIDER | 0x24 | open_sample | `char *` |
| _FLTPROVIDER | 0x28 | close_sample | `char *` |
| _FLTPROVIDER | 0x2c | sample_process | `char *` |
| _FLTPROVIDER | 0x30 | sample_attribute | `char *` |
| _FLTPROVIDER | 0x34 | set_sample_preference | `char *` |
| _FLTPROVIDER | 0x38 | dig | `_DIG_DRIVER *` |
| _FLTPROVIDER | 0x3c | provider | `DWORD` |
| _FLTPROVIDER | 0x4 | startup | `char *` |
| _FLTPROVIDER | 0x40 | driver_state | `long` |
| _FLTPROVIDER | 0x44 | next | `_FLTPROVIDER *` |
| _FLTPROVIDER | 0x8 | error | `char *` |
| _FLTPROVIDER | 0xc | shutdown | `char *` |
| _IMAGE_DATA_DIRECTORY | 0x0 | VirtualAddress | `DWORD` |
| _IMAGE_DATA_DIRECTORY | 0x4 | Size | `DWORD` |
| _IMAGE_DOS_HEADER | 0x0 | e_magic | `WORD` |
| _IMAGE_DOS_HEADER | 0x10 | e_sp | `WORD` |
| _IMAGE_DOS_HEADER | 0x12 | e_csum | `WORD` |
| _IMAGE_DOS_HEADER | 0x14 | e_ip | `WORD` |
| _IMAGE_DOS_HEADER | 0x16 | e_cs | `WORD` |
| _IMAGE_DOS_HEADER | 0x18 | e_lfarlc | `WORD` |
| _IMAGE_DOS_HEADER | 0x1a | e_ovno | `WORD` |
| _IMAGE_DOS_HEADER | 0x1c | e_res | `unsigned short[4]` |
| _IMAGE_DOS_HEADER | 0x2 | e_cblp | `WORD` |
| _IMAGE_DOS_HEADER | 0x24 | e_oemid | `WORD` |
| _IMAGE_DOS_HEADER | 0x26 | e_oeminfo | `WORD` |
| _IMAGE_DOS_HEADER | 0x28 | e_res2 | `unsigned short[10]` |
| _IMAGE_DOS_HEADER | 0x3c | e_lfanew | `long` |
| _IMAGE_DOS_HEADER | 0x4 | e_cp | `WORD` |
| _IMAGE_DOS_HEADER | 0x6 | e_crlc | `WORD` |
| _IMAGE_DOS_HEADER | 0x8 | e_cparhdr | `WORD` |
| _IMAGE_DOS_HEADER | 0xa | e_minalloc | `WORD` |
| _IMAGE_DOS_HEADER | 0xc | e_maxalloc | `WORD` |
| _IMAGE_DOS_HEADER | 0xe | e_ss | `WORD` |
| _IMAGE_FILE_HEADER | 0x0 | Machine | `WORD` |
| _IMAGE_FILE_HEADER | 0x10 | SizeOfOptionalHeader | `WORD` |
| _IMAGE_FILE_HEADER | 0x12 | Characteristics | `WORD` |
| _IMAGE_FILE_HEADER | 0x2 | NumberOfSections | `WORD` |
| _IMAGE_FILE_HEADER | 0x4 | TimeDateStamp | `DWORD` |
| _IMAGE_FILE_HEADER | 0x8 | PointerToSymbolTable | `DWORD` |
| _IMAGE_FILE_HEADER | 0xc | NumberOfSymbols | `DWORD` |
| _IMAGE_NT_HEADERS | 0x0 | Signature | `DWORD` |
| _IMAGE_NT_HEADERS | 0x18 | OptionalHeader | `_IMAGE_OPTIONAL_HEADER` |
| _IMAGE_NT_HEADERS | 0x4 | FileHeader | `_IMAGE_FILE_HEADER` |
| _IMAGE_OPTIONAL_HEADER | 0x0 | Magic | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x10 | AddressOfEntryPoint | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x14 | BaseOfCode | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x18 | BaseOfData | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x1c | ImageBase | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x2 | MajorLinkerVersion | `BYTE` |
| _IMAGE_OPTIONAL_HEADER | 0x20 | SectionAlignment | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x24 | FileAlignment | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x28 | MajorOperatingSystemVersion | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x2a | MinorOperatingSystemVersion | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x2c | MajorImageVersion | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x2e | MinorImageVersion | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x3 | MinorLinkerVersion | `BYTE` |
| _IMAGE_OPTIONAL_HEADER | 0x30 | MajorSubsystemVersion | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x32 | MinorSubsystemVersion | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x34 | Win32VersionValue | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x38 | SizeOfImage | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x3c | SizeOfHeaders | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x4 | SizeOfCode | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x40 | CheckSum | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x44 | Subsystem | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x46 | DllCharacteristics | `WORD` |
| _IMAGE_OPTIONAL_HEADER | 0x48 | SizeOfStackReserve | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x4c | SizeOfStackCommit | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x50 | SizeOfHeapReserve | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x54 | SizeOfHeapCommit | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x58 | LoaderFlags | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x5c | NumberOfRvaAndSizes | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0x60 | DataDirectory | `_IMAGE_DATA_DIRECTORY[16]` |
| _IMAGE_OPTIONAL_HEADER | 0x8 | SizeOfInitializedData | `DWORD` |
| _IMAGE_OPTIONAL_HEADER | 0xc | SizeOfUninitializedData | `DWORD` |
| _Item | 0x0 | title | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` |
| _Item | 0x10 | info | `std::basic_string<char,std::char_traits<char>,std::allocator<char> >` |
| _Item | 0x20 | bHasChild | `BYTE` |
| _Item | 0x24 | nChildNum | `int` |
| _Item | 0x28 | bIsPic | `BYTE` |
| _Item | 0x2c | ppChildren | `_Item * *` |
| _Item_List_Info | 0x1110 | ms_Title | `UIStatic` |
| _Item_List_Info | 0x11b0 | ms_Info | `UIStatic` |
| _Item_List_Info | 0x1250 | ms_Pic | `UIStatic` |
| _Item_List_Info | 0x12f0 | mb_Prev | `UIButton` |
| _Item_List_Info | 0x48 | m_background | `UIStatic` |
| _Item_List_Info | 0xe8 | m_IsActive | `unsigned char` |
| _Item_List_Info | 0xec | m_pItem | `_Item *` |
| _Item_List_Info | 0xf0 | m_BtnItem | `UIButton[12]` |
| _LARGE_INTEGER | 0x0 | QuadPart | `int` |
| _LARGE_INTEGER | 0x4 | HighPart | `long` |
| _MapElement | 0x0 | m_bShow | `BYTE` |
| _MapElement | 0x1 | m_cango | `BYTE` |
| _MapElement | 0x184 | m_isBtnCreate | `BYTE` |
| _MapElement | 0x185 | m_show | `BYTE` |
| _MapElement | 0x4 | m_screenPt | `tagPOINT` |
| _MapElement | 0xc | m_btn | `UIButtonEXA` |
| _PMD | 0x0 | mdisp | `int` |
| _PMD | 0x4 | pdisp | `int` |
| _PMD | 0x8 | vdisp | `int` |
| _PURGE_INFO | 0x0 | min_wu | `UINT` |
| _PURGE_INFO | 0x4 | max_wu | `UINT` |
| _PlugInfo | 0x0 | filepos | `long` |
| _PlugInfo | 0x104 | crc | `UINT` |
| _PlugInfo | 0x108 | left | `UINT` |
| _PlugInfo | 0x10c | top | `UINT` |
| _PlugInfo | 0x110 | width | `UINT` |
| _PlugInfo | 0x114 | height | `UINT` |
| _PlugInfo | 0x118 | srcWidth | `UINT` |
| _PlugInfo | 0x11c | srcHeight | `UINT` |
| _PlugInfo | 0x120 | libName | `char[256]` |
| _PlugInfo | 0x220 | libWidth | `UINT` |
| _PlugInfo | 0x224 | libHeight | `UINT` |
| _PlugInfo | 0x228 | _tex_uvLT | `_Texture_uv` |
| _PlugInfo | 0x230 | _tex_uvLB | `_Texture_uv` |
| _PlugInfo | 0x238 | _tex_uvRB | `_Texture_uv` |
| _PlugInfo | 0x240 | _tex_uvRT | `_Texture_uv` |
| _PlugInfo | 0x4 | name | `char[256]` |
| _RGNDATA | 0x0 | rdh | `_RGNDATAHEADER` |
| _RGNDATA | 0x20 | Buffer | `char[1]` |
| _RGNDATAHEADER | 0x0 | dwSize | `DWORD` |
| _RGNDATAHEADER | 0x10 | rcBound | `tagRECT` |
| _RGNDATAHEADER | 0x4 | iType | `DWORD` |
| _RGNDATAHEADER | 0x8 | nCount | `DWORD` |
| _RGNDATAHEADER | 0xc | nRgnSize | `DWORD` |
| _SAMPLE | 0x0 | tag | `char[4]` |
| _SAMPLE | 0x10c | SOB_IsWin32s | `long` |
| _SAMPLE | 0x110 | EOB_IsWin32s | `long` |
| _SAMPLE | 0x114 | EOS_IsWin32s | `long` |
| _SAMPLE | 0x118 | secondary_buffer | `long` |
| _SAMPLE | 0x11c | service_interval | `long` |
| _SAMPLE | 0x120 | service_tick | `long` |
| _SAMPLE | 0x124 | buffer_segment_size | `long` |
| _SAMPLE | 0x128 | prev_segment | `long` |
| _SAMPLE | 0x12c | prev_cursor | `long` |
| _SAMPLE | 0x130 | bytes_remaining | `long` |
| _SAMPLE | 0x134 | direct_control | `long` |
| _SAMPLE | 0x138 | doeob | `long` |
| _SAMPLE | 0x13c | dosob | `long` |
| _SAMPLE | 0x14 | len | `unsigned int[2]` |
| _SAMPLE | 0x140 | doeos | `long` |
| _SAMPLE | 0x144 | pipeline | `DPINFO[3]` |
| _SAMPLE | 0x1c | pos | `unsigned int[2]` |
| _SAMPLE | 0x24 | done | `unsigned int[2]` |
| _SAMPLE | 0x27c | reverb_level | `float` |
| _SAMPLE | 0x280 | reverb_reflect_time | `float` |
| _SAMPLE | 0x284 | reverb_decay_time | `float` |
| _SAMPLE | 0x288 | base_scale | `long` |
| _SAMPLE | 0x2c | reset_ASI | `long[2]` |
| _SAMPLE | 0x34 | src_fract | `DWORD` |
| _SAMPLE | 0x38 | left_val | `long` |
| _SAMPLE | 0x3c | right_val | `long` |
| _SAMPLE | 0x4 | driver | `_DIG_DRIVER *` |
| _SAMPLE | 0x40 | current_buffer | `long` |
| _SAMPLE | 0x44 | last_buffer | `long` |
| _SAMPLE | 0x48 | starved | `long` |
| _SAMPLE | 0x4c | loop_count | `long` |
| _SAMPLE | 0x50 | loop_start | `long` |
| _SAMPLE | 0x54 | loop_end | `long` |
| _SAMPLE | 0x58 | format | `long` |
| _SAMPLE | 0x5c | flags | `DWORD` |
| _SAMPLE | 0x60 | playback_rate | `long` |
| _SAMPLE | 0x64 | volume | `long` |
| _SAMPLE | 0x68 | pan | `long` |
| _SAMPLE | 0x6c | left_scale | `long` |
| _SAMPLE | 0x70 | right_scale | `long` |
| _SAMPLE | 0x74 | service_type | `long` |
| _SAMPLE | 0x78 | SOB | `char *` |
| _SAMPLE | 0x7c | EOB | `char *` |
| _SAMPLE | 0x8 | status | `DWORD` |
| _SAMPLE | 0x80 | EOS | `char *` |
| _SAMPLE | 0x84 | user_data | `long[8]` |
| _SAMPLE | 0xa4 | system_data | `long[8]` |
| _SAMPLE | 0xc | start | `char *[2]` |
| _SAMPLE | 0xc4 | adpcm | `_ADPCMDATATAG` |
| _SCOPETABLE_ENTRY | 0x0 | EnclosingLevel | `int` |
| _SCOPETABLE_ENTRY | 0x4 | FilterFunc | `char *` |
| _SCOPETABLE_ENTRY | 0x8 | HandlerFunc | `char *` |
| _STREAM | 0x0 | block_oriented | `long` |
| _STREAM | 0x10 | fileh | `DWORD` |
| _STREAM | 0x104 | next | `char *` |
| _STREAM | 0x108 | autostreaming | `long` |
| _STREAM | 0x10c | cb_IsWin32s | `long` |
| _STREAM | 0x110 | docallback | `long` |
| _STREAM | 0x14 | bufs | `unsigned char *[3]` |
| _STREAM | 0x20 | bufsizes | `unsigned int[3]` |
| _STREAM | 0x2c | reset_ASI | `long[3]` |
| _STREAM | 0x38 | bufstart | `long[3]` |
| _STREAM | 0x4 | using_ASI | `long` |
| _STREAM | 0x44 | asyncs | `char *[3]` |
| _STREAM | 0x50 | loadedbufstart | `long[2]` |
| _STREAM | 0x58 | loadedorder | `long[2]` |
| _STREAM | 0x60 | loadorder | `long` |
| _STREAM | 0x64 | bufsize | `long` |
| _STREAM | 0x68 | readsize | `long` |
| _STREAM | 0x6c | buf1 | `DWORD` |
| _STREAM | 0x70 | size1 | `long` |
| _STREAM | 0x74 | buf2 | `DWORD` |
| _STREAM | 0x78 | size2 | `long` |
| _STREAM | 0x7c | buf3 | `DWORD` |
| _STREAM | 0x8 | ASI | `ASISTAGE *` |
| _STREAM | 0x80 | size3 | `long` |
| _STREAM | 0x84 | datarate | `DWORD` |
| _STREAM | 0x88 | filerate | `long` |
| _STREAM | 0x8c | filetype | `long` |
| _STREAM | 0x90 | fileflags | `DWORD` |
| _STREAM | 0x94 | totallen | `long` |
| _STREAM | 0x98 | substart | `long` |
| _STREAM | 0x9c | sublen | `long` |
| _STREAM | 0xa0 | subpadding | `long` |
| _STREAM | 0xa4 | blocksize | `DWORD` |
| _STREAM | 0xa8 | padding | `long` |
| _STREAM | 0xac | padded | `long` |
| _STREAM | 0xb0 | loadedsome | `long` |
| _STREAM | 0xb4 | startpos | `DWORD` |
| _STREAM | 0xb8 | totalread | `DWORD` |
| _STREAM | 0xbc | loopsleft | `DWORD` |
| _STREAM | 0xc | samp | `_SAMPLE *` |
| _STREAM | 0xc0 | error | `DWORD` |
| _STREAM | 0xc4 | preload | `long` |
| _STREAM | 0xc8 | preloadpos | `DWORD` |
| _STREAM | 0xcc | noback | `long` |
| _STREAM | 0xd0 | alldone | `long` |
| _STREAM | 0xd4 | primeamount | `long` |
| _STREAM | 0xd8 | readatleast | `long` |
| _STREAM | 0xdc | playcontrol | `long` |
| _STREAM | 0xe0 | callback | `char *` |
| _STREAM | 0xe4 | user_data | `long[8]` |
| _SUBMAP | 0x0 | m_bShow | `BYTE` |
| _SUBMAP | 0x14 | m_notepos | `tagRECT` |
| _SUBMAP | 0x24 | m_fposX | `float` |
| _SUBMAP | 0x28 | m_fposY | `float` |
| _SUBMAP | 0x2c | m_pMap | `gbTexture *` |
| _SUBMAP | 0x30 | m_MapLeftToScreenLeft | `int` |
| _SUBMAP | 0x34 | m_MapLeftToScreenRight | `int` |
| _SUBMAP | 0x38 | m_MapTopToScreenTop | `int` |
| _SUBMAP | 0x3c | m_MapTopToScreenBottom | `int` |
| _SUBMAP | 0x4 | m_pos | `tagRECT` |
| _SUBMAP | 0x40 | m_NoteLeft | `int` |
| _SUBMAP | 0x44 | m_NoteRight | `int` |
| _SUBMAP | 0x48 | m_NoteTop | `int` |
| _SUBMAP | 0x4c | m_NoteBottom | `int` |
| _Tex_uv | 0x0 | u | `float` |
| _Tex_uv | 0x4 | v | `float` |
| _Texture_Info | 0x0 | _tex_name | `char[512]` |
| _Texture_Info | 0x200 | _tex_lib | `char[512]` |
| _Texture_Info | 0x400 | _tex_libw | `UINT` |
| _Texture_Info | 0x404 | _tex_libh | `UINT` |
| _Texture_Info | 0x408 | _tex_origin_x | `UINT` |
| _Texture_Info | 0x40c | _tex_origin_y | `UINT` |
| _Texture_Info | 0x410 | _tex_width | `UINT` |
| _Texture_Info | 0x414 | _tex_height | `UINT` |
| _Texture_Info | 0x418 | _tex_uvLT | `_Tex_uv` |
| _Texture_Info | 0x420 | _tex_uvLB | `_Tex_uv` |
| _Texture_Info | 0x428 | _tex_uvRB | `_Tex_uv` |
| _Texture_Info | 0x430 | _tex_uvRT | `_Tex_uv` |
| _Texture_Info | 0x438 | _tex_mode | `UINT` |
| _Texture_Info | 0x43c | _tex_valid | `BYTE` |
| _Texture_uv | 0x0 | u | `float` |
| _Texture_uv | 0x4 | v | `float` |
| _TimeMgr | 0x0 | newtick | `DWORD` |
| _TimeMgr | 0x4 | oldtick | `DWORD` |
| _TimeMgr | 0x8 | bNote | `BYTE` |
| _TypeDescriptor | 0x0 | pVFTable | `char *` |
| _TypeDescriptor | 0x4 | spare | `char *` |
| _UDACCEL | 0x0 | nSec | `UINT` |
| _UDACCEL | 0x4 | nInc | `UINT` |
| _UIPOS | 0x0 | nameCRC | `UINT` |
| _UIPOS | 0x4 | nXPos | `int` |
| _UIPOS | 0x8 | nYPos | `int` |
| _XCPT_ACTION | 0x0 | XcptNum | `DWORD` |
| _XCPT_ACTION | 0x4 | SigNum | `int` |
| _XCPT_ACTION | 0x8 | XcptAction | `char *` |
| _better_note | 0x0 | best_second | `int` |
| _better_note | 0x4 | best_num | `int` |
| _btnOPTDATA | 0x0 | pData | `BYTE *` |
| _btnOPTDATA | 0x4 | width | `UINT` |
| _btnOPTDATA | 0x8 | height | `UINT` |
| _btnOPTDATA | 0xc | bpp | `UINT` |
| _count_string | 0x0 | Length | `short` |
| _count_string | 0x2 | MaximumLength | `short` |
| _count_string | 0x4 | Buffer | `char *` |
| _cpinfo | 0x0 | MaxCharSize | `unsigned int` |
| _cpinfo | 0x4 | DefaultChar | `unsigned char[2]` |
| _cpinfo | 0x6 | LeadByte | `unsigned char[12]` |
| _s__CatchableType | 0x0 | properties | `UINT` |
| _s__CatchableType | 0x14 | sizeOrOffset | `int` |
| _s__CatchableType | 0x18 | copyFunction | `char *` |
| _s__CatchableType | 0x4 | pType | `_TypeDescriptor *` |
| _s__CatchableType | 0x8 | thisDisplacement | `_PMD` |
| _s__CatchableTypeArray | 0x0 | nCatchableTypes | `int` |
| _strflt | 0x0 | sign | `int` |
| _strflt | 0x4 | decpt | `int` |
| _strflt | 0x8 | flag | `int` |
| _strflt | 0xc | mantissa | `char *` |
| code_page_info | 0x0 | code_page | `int` |
| code_page_info | 0x10 | rgrange | `unsigned char[8][4]` |
| code_page_info | 0x4 | mbulinfo | `unsigned short[6]` |
| collision | 0x0 | _tail_000 | `char[4]` |
| direction_emitter_graph | 0x0 | _tail_000 | `char[5300]` |
| doubleint | 0x0 | twoints | `int[2]` |
| elelife_emitter_graph | 0x0 | _tail_000 | `char[5300]` |
| elerandvec_emitter_graph | 0x0 | _tail_000 | `char[5300]` |
| emissionrate_emitter_graph | 0x0 | _tail_000 | `char[5300]` |
| errentry | 0x0 | oscode | `DWORD` |
| errentry | 0x4 | errnocode | `int` |
| gbAABBox | 0x0 | min | `gbVec3D` |
| gbAABBox | 0xc | max | `gbVec3D` |
| gbActor | 0x58 | pBody | `gbActorDef *` |
| gbActor | 0x5c | curSkin | `int` |
| gbActor | 0x60 | pMixInfo | `gbMixActInfo *` |
| gbActor | 0x64 | NumMixInfo | `int` |
| gbActor | 0x68 | pExpNode | `gbActorExpNode *` |
| gbActor | 0x6c | nExpNode | `int` |
| gbActor | 0x70 | MaxExpNode | `int` |
| gbActorDef | 0x18 | pShadowEffect | `gbRenderEffect *[2]` |
| gbActorDef | 0x58 | m_nFilledSlot | `int` |
| gbActorExpNode | 0x0 | name | `unsigned int` |
| gbActorExpNode | 0x4 | toworld | `gbMatrix4` |
| gbActorExpNode | 0x44 | cache | `gbMatrix4` |
| gbActorMgr | 0x0 | AllActorDef | `gbResManager` |
| gbAnimKey | 0x0 | time | `float` |
| gbAnimKey | 0x4 | flags | `unsigned int` |
| gbAnimScript | 0x0 | BeginPos | `int` |
| gbAnimScript | 0x2c | Var_Int | `int[8]` |
| gbAnimScript | 0x4 | EndPos | `int` |
| gbAnimScript | 0x4c | AnimSpeed | `float` |
| gbAnimScript | 0x50 | Vel | `gbVec3D` |
| gbAnimScript | 0x5c | Accel | `gbVec3D` |
| gbAnimScript | 0x68 | Offset | `gbVec3D` |
| gbAnimScript | 0x74 | IsHide | `int` |
| gbAnimScript | 0x78 | CurTime | `double` |
| gbAnimScript | 0x8 | CurPos | `int` |
| gbAnimScript | 0x80 | NextTime | `double` |
| gbAnimScript | 0xc | Var_Flt | `float[8]` |
| gbAudioManager | 0x0 | hStreamArray | `_STREAM *[3]` |
| gbAudioManager | 0x18 | h2DDriver | `_DIG_DRIVER *` |
| gbAudioManager | 0x1c | h3DProvider | `unsigned int` |
| gbAudioManager | 0x20 | Attach3D | `SoundAttachObj[10]` |
| gbAudioManager | 0x98 | Attach2D | `SoundAttachObj[4]` |
| gbAudioManager | 0xc | StreamStatus | `int[3]` |
| gbAudioManager | 0xc8 | CurTime | `unsigned int` |
| gbAudioManager | 0xcc | S_3DMasterVol | `float` |
| gbAudioManager | 0xd0 | S_2DMasterVol | `float` |
| gbAudioManager | 0xd4 | MusicMasterVol | `float` |
| gbAudioManager | 0xd8 | hListener | `h3DPOBJECT *` |
| gbAudioManager | 0xdc | ListenerPos | `gbVec3D` |
| gbAudioManager | 0xe8 | SndDataMgr | `gbResManager` |
| gbAudioMgrDesc | 0x0 | frequence | `unsigned int` |
| gbAudioMgrDesc | 0x4 | bits | `unsigned int` |
| gbAudioMgrDesc | 0x8 | channels | `unsigned int` |
| gbAudioMgrDesc | 0xc | provider | `char[256]` |
| gbBaseMesh | 0x18 | Effect_RefCount | `int` |
| gbBaseMesh | 0x1c | ObjName | `char[32]` |
| gbBaseMesh | 0x3c | VertFVF | `unsigned int` |
| gbBaseMesh | 0x40 | pSections | `gbMeshSection *` |
| gbBaseMesh | 0x44 | nSection | `int` |
| gbBaseMesh | 0x48 | MemCache | `gbMeshMemCache` |
| gbBaseMesh | 0x58 | BoundBox | `gbAABBox` |
| gbBaseMesh | 0x70 | CurTime | `float` |
| gbBaseMesh | 0x74 | pGfxMgr | `gbGfxManager *` |
| gbBinkVideo | 0x10 | m_Cpk | `CPK` |
| gbBinkVideo | 0x4 | m_pos | `tagPOINT` |
| gbBinkVideo | 0xc | m_hBink | `BINK *` |
| gbBinkVideo | 0xe01cc | m_Cpk2 | `CPK` |
| gbCamControler | 0x10 | CtrlTime | `double` |
| gbCamControler | 0x18 | CtrlAge | `double` |
| gbCamControler | 0x8 | pCamera | `gbCamera *` |
| gbCamera | 0x0 | fov | `float` |
| gbCamera | 0x10 | zNear | `float` |
| gbCamera | 0x114 | pControl | `gbCamControler *[16]` |
| gbCamera | 0x14 | zFar | `float` |
| gbCamera | 0x154 | CurCtrl | `int` |
| gbCamera | 0x158 | pGfxMgr | `gbGfxManager *` |
| gbCamera | 0x15c | eyeLoc | `gbVec3D` |
| gbCamera | 0x168 | eyeDir | `gbQuaternion` |
| gbCamera | 0x18 | Viewport | `gbViewPort` |
| gbCamera | 0x30 | Plane | `float[4][6]` |
| gbCamera | 0x4 | OrthoSize | `float` |
| gbCamera | 0x8 | Wscreen | `float` |
| gbCamera | 0x90 | numPlane | `int` |
| gbCamera | 0x94 | ViewMatrix | `gbMatrix4` |
| gbCamera | 0xc | Hscreen | `float` |
| gbCamera | 0xd4 | InvVMatrix | `gbMatrix4` |
| gbChain1D | 0x0 | m_Head | `gbChain1DNode *` |
| gbChain1D | 0x4 | m_Tail | `gbChain1DNode *` |
| gbChain1D | 0x8 | m_numNode | `int` |
| gbChain1D | 0xc | m_Cur | `gbChain1DNode *` |
| gbChain1DNode | 0x4 | next | `gbChain1DNode *` |
| gbClearParam | 0x0 | color | `unsigned int` |
| gbClearParam | 0x4 | depth | `float` |
| gbClearParam | 0x8 | stencil | `int` |
| gbClearParam | 0xc | clearflag | `unsigned int` |
| gbColorFlt | 0x0 | Red | `float` |
| gbColorFlt | 0x4 | Green | `float` |
| gbColorFlt | 0x8 | Blue | `float` |
| gbColorFlt | 0xc | Alpha | `float` |
| gbColorQuad | 0x0 | Color | `unsigned int` |
| gbColorQuadChannels | 0x0 | Blue | `BYTE` |
| gbColorQuadChannels | 0x1 | Green | `BYTE` |
| gbColorQuadChannels | 0x2 | Red | `BYTE` |
| gbColorQuadChannels | 0x3 | Alpha | `BYTE` |
| gbCursorRes | 0x18 | m_pSurface | `IDirect3DSurface9 *` |
| gbCursorRes | 0x1c | m_OriginX | `int` |
| gbCursorRes | 0x20 | m_OriginY | `int` |
| gbDropDesc | 0x0 | unitsize | `float` |
| gbDropDesc | 0x10 | maxlife | `float` |
| gbDropDesc | 0x14 | minvelocity | `float` |
| gbDropDesc | 0x18 | maxvelocity | `float` |
| gbDropDesc | 0x1c | minheight | `float` |
| gbDropDesc | 0x20 | maxheight | `float` |
| gbDropDesc | 0x4 | range | `float` |
| gbDropDesc | 0x8 | emitrate | `int` |
| gbDropDesc | 0xc | minlife | `float` |
| gbDropGroup | 0x10 | m_UnitSize | `float` |
| gbDropGroup | 0x14 | m_Range | `float` |
| gbDropGroup | 0x18 | m_EmitRate | `int` |
| gbDropGroup | 0x1c | m_MinLife | `float` |
| gbDropGroup | 0x20 | m_MaxLife | `float` |
| gbDropGroup | 0x24 | m_MinEmitVel | `float` |
| gbDropGroup | 0x28 | m_MaxEmitVel | `float` |
| gbDropGroup | 0x2c | m_MinHeight | `float` |
| gbDropGroup | 0x30 | m_MaxHeight | `float` |
| gbDropGroup | 0x38 | m_LastFrameTime | `double` |
| gbDropGroup | 0x40 | m_LeftTimeAccum | `float` |
| gbDropGroup | 0x44 | m_pUnits | `gbDropUnit *` |
| gbDropGroup | 0x48 | m_pTex | `gbTexture *` |
| gbDropGroup | 0x4c | m_pEffect | `gbRenderEffect *` |
| gbDropGroup | 0x8 | m_MaxUnit | `int` |
| gbDropGroup | 0xc | m_nAliveUnit | `int` |
| gbDropUnit | 0x0 | life | `float` |
| gbDropUnit | 0x10 | curpos | `gbVec3D` |
| gbDropUnit | 0x1c | lastpos | `gbVec3D` |
| gbDropUnit | 0x4 | velocity | `gbVec3D` |
| gbDynVertBuf | 0x0 | pGfxMgr | `gbGfxManager *` |
| gbDynVertBuf | 0x10 | Stride | `int` |
| gbDynVertBuf | 0x14 | BaseIndex | `int` |
| gbDynVertBuf | 0x18 | LockVertNum | `int` |
| gbDynVertBuf | 0x1c | pXYZ | `float *` |
| gbDynVertBuf | 0x20 | pNormal | `float *` |
| gbDynVertBuf | 0x24 | pColor1 | `gbColorQuad *` |
| gbDynVertBuf | 0x28 | pColor2 | `gbColorQuad *` |
| gbDynVertBuf | 0x2c | pUV | `float *[4]` |
| gbDynVertBuf | 0x4 | Type | `gbPoolType` |
| gbDynVertBuf | 0x8 | VertNum | `int` |
| gbDynVertBuf | 0xc | VertType | `unsigned int` |
| gbEffectMgr | 0x10 | m_pWhiteTex | `gbTexture *` |
| gbEffectMgr | 0x14 | m_pGrayTex | `gbTexture *` |
| gbEffectMgr | 0x18 | m_pDefEffect | `gbRenderEffect *` |
| gbEffectMgr | 0x1c | m_AllHandle | `int[64]` |
| gbEffectMgr | 0x81c | m_nHandle | `int` |
| gbEffectMgr | 0x820 | pCurEffect | `gbRenderEffect *` |
| gbEffectMgr | 0x824 | bDoPassOutside | `int` |
| gbEffectMgr | 0xc | m_pGfxMgr | `gbGfxManager *` |
| gbEmitterData | 0x0 | curdir | `gbVec3D` |
| gbEmitterData | 0x10 | elerandvel_min | `float` |
| gbEmitterData | 0x14 | emissionrate_max | `float` |
| gbEmitterData | 0x18 | emissionrate_min | `float` |
| gbEmitterData | 0x1c | elelifetime_max | `float` |
| gbEmitterData | 0x20 | elelifetime_min | `float` |
| gbEmitterData | 0x28 | accumulate_part | `double` |
| gbEmitterData | 0xc | elerandvel_max | `float` |
| gbEmitterShape | 0x0 | intervec | `gbVec3D *` |
| gbEmitterShape | 0x4 | disarray | `float *` |
| gbEmitterShape | 0x8 | m_iVecnum | `int` |
| gbEmitterShape | 0xc | curmat | `gbMatrix4` |
| gbEmitterSphere | 0x0 | hotspot | `float` |
| gbEmitterSphere | 0x4 | falloff | `float` |
| gbEmitterSquare | 0x0 | min | `gbVec3D` |
| gbEmitterSquare | 0xc | max | `gbVec3D` |
| gbFileStream | 0x0 | _tail_000 | `char[4]` |
| gbFogParam | 0x0 | type | `int` |
| gbFogParam | 0x14 | mode | `int` |
| gbFogParam | 0x18 | start | `float` |
| gbFogParam | 0x1c | end | `float` |
| gbFogParam | 0x20 | density | `float` |
| gbFogParam | 0x24 | plane | `float[4]` |
| gbFogParam | 0x4 | color | `unsigned int` |
| gbGammaRamp | 0x0 | red | `unsigned short[256]` |
| gbGammaRamp | 0x200 | green | `unsigned short[256]` |
| gbGammaRamp | 0x400 | blue | `unsigned short[256]` |
| gbGeomNode | 0x100 | nLoopPast | `int` |
| gbGeomNode | 0x104 | bBlade | `int` |
| gbGeomNode | 0x108 | pMesh | `gbBaseMesh *` |
| gbGeomNode | 0x10c | pTags | `gbTagNode *` |
| gbGeomNode | 0x110 | nTag | `int` |
| gbGeomNode | 0x114 | nXBlade | `int` |
| gbGeomNode | 0x118 | pXTagBlade | `gbTagXBladeNode *` |
| gbGeomNode | 0x58 | CacheToW | `gbMatrix4` |
| gbGeomNode | 0x98 | OffMat | `gbMatrix4` |
| gbGeomNode | 0xd8 | PosCtrl | `gbKeyControler *` |
| gbGeomNode | 0xdc | ScaleCtrl | `gbKeyControler *` |
| gbGeomNode | 0xe0 | RotCtrl | `gbKeyControler *` |
| gbGeomNode | 0xe4 | DegScale | `float` |
| gbGeomNode | 0xe8 | UseControl | `int` |
| gbGeomNode | 0xec | pScript | `gbAnimScript *` |
| gbGeomNode | 0xf0 | CurTime | `double` |
| gbGeomNode | 0xf8 | AnimMaxTime | `float` |
| gbGeomNode | 0xfc | nLoop | `int` |
| gbGeomQuad | 0x0 | vec | `gbVec3D[4]` |
| gbGeomQuad | 0x30 | su | `float` |
| gbGeomQuad | 0x34 | sv | `float` |
| gbGeomQuad | 0x38 | eu | `float` |
| gbGeomQuad | 0x3c | ev | `float` |
| gbGeomQuad | 0x40 | color | `unsigned int` |
| gbGfxCaps | 0x0 | CanWindow | `int` |
| gbGfxCaps | 0x10 | MaxTexHeight | `int` |
| gbGfxCaps | 0x4 | TexMemSize | `unsigned int` |
| gbGfxCaps | 0x8 | MaxOnePassTex | `int` |
| gbGfxCaps | 0xc | MaxTexWidth | `int` |
| gbGfxDriverInfo | 0x0 | type | `int` |
| gbGfxDriverInfo | 0x10 | colorbits | `int` |
| gbGfxDriverInfo | 0x14 | depthbits | `int` |
| gbGfxDriverInfo | 0x18 | stensilbits | `int` |
| gbGfxDriverInfo | 0x1c | nbackbuf | `int` |
| gbGfxDriverInfo | 0x20 | fullscreen | `int` |
| gbGfxDriverInfo | 0x24 | refreshrate | `int` |
| gbGfxDriverInfo | 0x28 | winname | `char[128]` |
| gbGfxDriverInfo | 0x4 | subtype | `int` |
| gbGfxDriverInfo | 0x8 | width | `int` |
| gbGfxDriverInfo | 0xa8 | hinst | `unsigned int` |
| gbGfxDriverInfo | 0xac | hgfxwnd | `unsigned int` |
| gbGfxDriverInfo | 0xb0 | newwindow | `int` |
| gbGfxDriverInfo | 0xb4 | waitforverticalblank | `int` |
| gbGfxDriverInfo | 0xc | height | `int` |
| gbGfxManager | 0x124 | InvViewMatrix | `gbMatrix4` |
| gbGfxManager | 0x164 | WorldMatrix | `gbMatrix4` |
| gbGfxManager | 0x1a4 | CurZBias | `int` |
| gbGfxManager | 0x1a8 | bWireMode | `int` |
| gbGfxManager | 0x1ac | AmbientLight | `gbColorFlt` |
| gbGfxManager | 0x1bc | fSelfIllum | `float` |
| gbGfxManager | 0x1c0 | pSceneGraph | `gbSceneGraph *` |
| gbGfxManager | 0x1c4 | Viewport | `gbViewPort` |
| gbGfxManager | 0x1dc | ClearParam | `gbClearParam` |
| gbGfxManager | 0x1f0 | LastTime | `double` |
| gbGfxManager | 0x1f8 | CurTime | `double` |
| gbGfxManager | 0x200 | LastTick | `unsigned int` |
| gbGfxManager | 0x204 | CurTick | `unsigned int` |
| gbGfxManager | 0x208 | Stat | `gbGfxStatistic` |
| gbGfxManager | 0x238 | AllLight | `gbLight[8]` |
| gbGfxManager | 0x578 | LightEnable | `int[8]` |
| gbGfxManager | 0x598 | FogParam | `gbFogParam` |
| gbGfxManager | 0x5cc | m_pCurTexture | `gbTexture *[8]` |
| gbGfxManager | 0x8 | hGfxWnd | `unsigned int` |
| gbGfxManager | 0xc | DrvInfo | `gbGfxDriverInfo` |
| gbGfxManager | 0xc4 | pVertPoolMgr | `gbVertPoolMgr *` |
| gbGfxManager | 0xc8 | pEffectMgr | `gbEffectMgr *` |
| gbGfxManager | 0xcc | pTexResMgr | `gbResManager *` |
| gbGfxManager | 0xd0 | pFontMgr | `gbPrintFontMgr *` |
| gbGfxManager | 0xd4 | pMatrixStack | `gbMatrixStack *[4]` |
| gbGfxManager | 0xe4 | ViewMatrix | `gbMatrix4` |
| gbGfxManager_D3D | 0x5f0 | m_d3dEnumeration | `CD3DEnumeration` |
| gbGfxManager_D3D | 0x61c | m_bWindowed | `int` |
| gbGfxManager_D3D | 0x620 | m_rcWindowClient | `tagRECT` |
| gbGfxManager_D3D | 0x630 | m_rcWindowBounds | `tagRECT` |
| gbGfxManager_D3D | 0x640 | m_dwWindowStyle | `unsigned int` |
| gbGfxManager_D3D | 0x644 | m_hWnd | `HWND__ *` |
| gbGfxManager_D3D | 0x648 | m_bMinimized | `unsigned char` |
| gbGfxManager_D3D | 0x649 | m_bMaximized | `unsigned char` |
| gbGfxManager_D3D | 0x64a | m_bClipCursorWhenFullscreen | `unsigned char` |
| gbGfxManager_D3D | 0x64b | m_bShowCursorWhenFullscreen | `unsigned char` |
| gbGfxManager_D3D | 0x64c | m_bActive | `unsigned char` |
| gbGfxManager_D3D | 0x650 | m_dwCreateFlags | `unsigned int` |
| gbGfxManager_D3D | 0x654 | m_DriverBug | `D3DDriverBug` |
| gbGfxManager_D3D | 0x658 | m_CursorMgr | `gbResManager` |
| gbGfxManager_D3D | 0x664 | m_pActiveCursor | `gbCursorRes *` |
| gbGfxManager_D3D | 0x668 | m_bShowCursor | `int` |
| gbGfxManager_D3D | 0x66c | m_bSoftVPMode | `int` |
| gbGfxManager_D3D | 0x670 | m_d3dSettings | `CD3DSettings` |
| gbGfxManager_D3D | 0x6dc | m_d3dpp | `_D3DPRESENT_PARAMETERS_` |
| gbGfxManager_D3D | 0x714 | m_pD3D | `IDirect3D9 *` |
| gbGfxManager_D3D | 0x718 | m_pd3dDevice | `IDirect3DDevice9 *` |
| gbGfxManager_D3D | 0x71c | m_d3dCaps | `_D3DCAPS9` |
| gbGfxManager_D3D | 0x84c | m_d3dsdBackBuffer | `_D3DSURFACE_DESC` |
| gbGfxManager_D3D | 0x86c | m_strDeviceStats | `char[90]` |
| gbGfxManager_D3D | 0x8c8 | m_ErrorCode | `long` |
| gbGfxManager_D3D | 0x8cc | m_bDeviceLost | `int` |
| gbGfxManager_D3D | 0x8d0 | m_pBackBuffer | `IDirect3DSurface9 *` |
| gbGfxManager_D3D | 0x8d4 | m_DXTSupported | `int[5]` |
| gbGfxManager_D3D | 0x8e8 | m_pCacheVB | `IDirect3DVertexBuffer9 *` |
| gbGfxManager_D3D | 0x8ec | m_pCacheIB | `IDirect3DIndexBuffer9 *` |
| gbGfxStatistic | 0x0 | nRFaces | `int` |
| gbGfxStatistic | 0x10 | nSrcVerts | `int` |
| gbGfxStatistic | 0x14 | nSrcIndex | `int` |
| gbGfxStatistic | 0x18 | nTexSwitch | `int` |
| gbGfxStatistic | 0x1c | FPS | `float` |
| gbGfxStatistic | 0x20 | TimeAccum | `double` |
| gbGfxStatistic | 0x28 | Frame | `unsigned int` |
| gbGfxStatistic | 0x2c | PrevFrame | `unsigned int` |
| gbGfxStatistic | 0x4 | nRVerts | `int` |
| gbGfxStatistic | 0x8 | nStaticVerts | `int` |
| gbGfxStatistic | 0xc | nStaticIndex | `int` |
| gbImage2D | 0x0 | ImgInfo | `gbImage2DInfo` |
| gbImage2D | 0x80 | Width | `int` |
| gbImage2D | 0x84 | Height | `int` |
| gbImage2D | 0x88 | PixelFmt | `gbPixelFormat` |
| gbImage2D | 0xb4 | BitCount | `int` |
| gbImage2D | 0xb8 | pBits | `unsigned char *` |
| gbImage2D | 0xbc | pPalette | `gbColorQuad *` |
| gbImage2D | 0xc0 | numPalEntry | `int` |
| gbImage2D | 0xc4 | ColorKey | `gbColorQuad` |
| gbImage2DInfo | 0x0 | isdiskinfo | `int` |
| gbImage2DInfo | 0x2c | wdiv | `int[8]` |
| gbImage2DInfo | 0x4 | goal | `int` |
| gbImage2DInfo | 0x4c | hdiv | `int[8]` |
| gbImage2DInfo | 0x6c | wrap_u | `int` |
| gbImage2DInfo | 0x70 | wrap_v | `int` |
| gbImage2DInfo | 0x74 | mipmap | `int` |
| gbImage2DInfo | 0x78 | minfilter | `int` |
| gbImage2DInfo | 0x7c | magfilter | `int` |
| gbImage2DInfo | 0x8 | ngrade | `int` |
| gbImage2DInfo | 0xc | detail | `int[8]` |
| gbIndexBubble | 0x10 | nIndex | `int` |
| gbIndexBubble | 0x14 | BubSize | `int` |
| gbIndexBubble | 0x18 | Start | `int` |
| gbIndexBubble | 0x1c | StartVert | `int` |
| gbIndexBubble | 0x20 | EndVert | `int` |
| gbIndexBubble | 0x8 | pPool | `gbIndexPool *` |
| gbIndexBubble | 0xc | Type | `gbPrimType` |
| gbIndexPool | 0x10 | pMemBuf | `char *` |
| gbIndexPool | 0x14 | TotalIndex | `int` |
| gbIndexPool | 0x18 | FreeIndexBub | `gbChain1D` |
| gbIndexPool | 0x28 | UsedIndexBub | `gbChain1D` |
| gbIndexPool | 0x8 | Type | `gbPoolType` |
| gbIndexPool | 0xc | EleSize | `int` |
| gbKeyControler | 0x10 | nKey | `int` |
| gbKeyControler | 0x4 | pKeys | `char *` |
| gbKeyControler | 0x8 | KeySize | `int` |
| gbKeyControler | 0xc | KeyType | `gbKeyType` |
| gbLight | 0x0 | type | `int` |
| gbLight | 0x14 | specular | `gbColorFlt` |
| gbLight | 0x24 | ambient | `gbColorFlt` |
| gbLight | 0x34 | position | `gbVec3D` |
| gbLight | 0x4 | diffuse | `gbColorFlt` |
| gbLight | 0x40 | direction | `gbVec3D` |
| gbLight | 0x4c | range | `float` |
| gbLight | 0x50 | falloff | `float` |
| gbLight | 0x54 | attenuation0 | `float` |
| gbLight | 0x58 | attenuation1 | `float` |
| gbLight | 0x5c | attenuation2 | `float` |
| gbLight | 0x60 | theta | `float` |
| gbLight | 0x64 | phi | `float` |
| gbLightObj | 0x1c | m_Ambient | `gbColorFlt` |
| gbLightObj | 0x2c | m_UseDiffuse | `int` |
| gbLightObj | 0x30 | m_UseSpecular | `int` |
| gbLightObj | 0x34 | m_NearStart | `float` |
| gbLightObj | 0x38 | m_NearEnd | `float` |
| gbLightObj | 0x3c | m_FarStart | `float` |
| gbLightObj | 0x40 | m_FarEnd | `float` |
| gbLightObj | 0x44 | m_DecayType | `int` |
| gbLightObj | 0x48 | m_DecayRadius | `float` |
| gbLightObj | 0x4c | m_LightShape | `int` |
| gbLightObj | 0x50 | m_HotSize | `float` |
| gbLightObj | 0x54 | m_Falloff | `float` |
| gbLightObj | 0x58 | m_Aspect | `float` |
| gbLightObj | 0x5c | m_BoundSphere | `gbSphere` |
| gbLightObj | 0x6c | m_SysLight | `gbLight` |
| gbLightObj | 0x8 | m_LightType | `int` |
| gbLightObj | 0xc | m_Color | `gbColorFlt` |
| gbLightObj | 0xd4 | m_BakedLight | `int` |
| gbMaterial | 0x0 | diffuse | `gbColorFlt` |
| gbMaterial | 0x10 | ambient | `gbColorFlt` |
| gbMaterial | 0x20 | specular | `gbColorFlt` |
| gbMaterial | 0x30 | emissive | `gbColorFlt` |
| gbMaterial | 0x40 | power | `float` |
| gbMatrix4 | 0x10 | yx | `float` |
| gbMatrix4 | 0x14 | yy | `float` |
| gbMatrix4 | 0x18 | yz | `float` |
| gbMatrix4 | 0x1c | yw | `float` |
| gbMatrix4 | 0x20 | zx | `float` |
| gbMatrix4 | 0x24 | zy | `float` |
| gbMatrix4 | 0x28 | zz | `float` |
| gbMatrix4 | 0x2c | zw | `float` |
| gbMatrix4 | 0x30 | tx | `float` |
| gbMatrix4 | 0x34 | ty | `float` |
| gbMatrix4 | 0x38 | tz | `float` |
| gbMatrix4 | 0x3c | tw | `float` |
| gbMatrix4 | 0x4 | xy | `float` |
| gbMatrix4 | 0x8 | xz | `float` |
| gbMatrix4 | 0xc | xw | `float` |
| gbMatrix4Flat | 0x0 | xx | `float` |
| gbMatrix4Flat | 0x10 | yx | `float` |
| gbMatrix4Flat | 0x14 | yy | `float` |
| gbMatrix4Flat | 0x18 | yz | `float` |
| gbMatrix4Flat | 0x1c | yw | `float` |
| gbMatrix4Flat | 0x20 | zx | `float` |
| gbMatrix4Flat | 0x24 | zy | `float` |
| gbMatrix4Flat | 0x28 | zz | `float` |
| gbMatrix4Flat | 0x2c | zw | `float` |
| gbMatrix4Flat | 0x30 | tx | `float` |
| gbMatrix4Flat | 0x34 | ty | `float` |
| gbMatrix4Flat | 0x38 | tz | `float` |
| gbMatrix4Flat | 0x3c | tw | `float` |
| gbMatrix4Flat | 0x4 | xy | `float` |
| gbMatrix4Flat | 0x8 | xz | `float` |
| gbMatrix4Flat | 0xc | xw | `float` |
| gbMatrixStack | 0x0 | pMatBuf | `gbMatrix4 *` |
| gbMatrixStack | 0x4 | MaxVol | `int` |
| gbMatrixStack | 0x8 | CurPos | `int` |
| gbMatrixStack | 0xc | ValidFlag | `int` |
| gbMeshData | 0x0 | _tail_000 | `char[4]` |
| gbMeshMemCache | 0x0 | pVerts | `gbVec3D *` |
| gbMeshMemCache | 0x4 | nVert | `int` |
| gbMeshMemCache | 0x8 | pIndices | `unsigned short *` |
| gbMeshMemCache | 0xc | nIndex | `int` |
| gbMeshSection | 0x0 | BlendFlags | `int` |
| gbMeshSection | 0x4 | bBakedLight | `int` |
| gbMeshSection | 0x4c | Material | `gbMaterial` |
| gbMeshSection | 0x8 | TexArray | `gbTextureArray` |
| gbMeshSection | 0x90 | pIndexBub | `gbIndexBubble *` |
| gbMeshSection | 0x94 | VertStart | `unsigned int` |
| gbMeshSection | 0x98 | VertEnd | `unsigned int` |
| gbMeshSection | 0x9c | Point | `gbVec3D` |
| gbMeshSection | 0xa8 | pCustomEffect | `gbRenderEffect *` |
| gbMeshSection | 0xac | TexAnim | `gbTexFlipAnim` |
| gbMixActInfo | 0x0 | state | `int` |
| gbMixActInfo | 0x10 | start | `unsigned int` |
| gbMixActInfo | 0x14 | end | `unsigned int` |
| gbMixActInfo | 0x18 | duration | `unsigned int` |
| gbMixActInfo | 0x1c | allbone | `int` |
| gbMixActInfo | 0x20 | endmsg | `unsigned int` |
| gbMixActInfo | 0x4 | name | `unsigned int` |
| gbMixActInfo | 0x8 | weight | `float` |
| gbMixActInfo | 0xc | time | `unsigned int` |
| gbNBTreeNode | 0x8 | pFather | `gbNBTreeNode *` |
| gbNBTreeNode | 0xc | children | `gbChain1D` |
| gbNodeMsgObj | 0x0 | msgid | `int` |
| gbNodeMsgObj | 0x4 | param | `unsigned int[2]` |
| gbNodeMsgObj | 0xc | pfrom | `gbVisNode *` |
| gbNodeMsgPayload | 0x0 | msgid | `int` |
| gbNodeMsgPayload | 0x4 | param | `unsigned int[2]` |
| gbNodeMsgPayload | 0xc | _pad0C | `int` |
| gbOBBox | 0x0 | trans | `Matrix4` |
| gbOBBox | 0x40 | xlen | `float` |
| gbOBBox | 0x44 | ylen | `float` |
| gbOBBox | 0x48 | zlen | `float` |
| gbPartEmitter | 0x0 | name | `char[64]` |
| gbPartEmitter | 0x118 | m_fSpeedMulti | `float` |
| gbPartEmitter | 0x11c | m_fSizeMulti | `float` |
| gbPartEmitter | 0x120 | DirectionCtrl | `gbPartParamControl` |
| gbPartEmitter | 0x1304 | RandomVelCtrl | `gbPartParamControl` |
| gbPartEmitter | 0x24e8 | EmitRateCtrl | `gbPartParamControl` |
| gbPartEmitter | 0x36cc | UnitLifeCtrl | `gbPartParamControl` |
| gbPartEmitter | 0x40 | relative_position | `gbVec3D` |
| gbPartEmitter | 0x48b0 | UnitScaleCtrl | `gbPartParamControl` |
| gbPartEmitter | 0x4c | emission_scope | `gbVec3D` |
| gbPartEmitter | 0x58 | cs_name | `char[64]` |
| gbPartEmitter | 0x5a94 | UnitRotCtrl | `gbPartParamControl` |
| gbPartEmitter | 0x98 | emitter_shape | `int` |
| gbPartEmitter | 0x9c | cyclelen_start | `float` |
| gbPartEmitter | 0xa0 | cyclelen_end | `float` |
| gbPartEmitter | 0xa4 | cycle_loop | `int` |
| gbPartEmitter | 0xa8 | lighton | `int` |
| gbPartEmitter | 0xac | square | `gbEmitterSquare` |
| gbPartEmitter | 0xc4 | sphere | `gbEmitterSphere` |
| gbPartEmitter | 0xcc | shape | `gbEmitterShape` |
| gbPartGroupParam | 0x0 | particle_name | `char[32]` |
| gbPartGroupParam | 0x134c | RotCtrl | `gbPartParamControl` |
| gbPartGroupParam | 0x138 | particlesize | `int` |
| gbPartGroupParam | 0x13c | animation_type | `int` |
| gbPartGroupParam | 0x140 | animation_fps | `int` |
| gbPartGroupParam | 0x144 | random_1stframe | `int` |
| gbPartGroupParam | 0x148 | random_rotstart | `int` |
| gbPartGroupParam | 0x14c | random_rotend | `int` |
| gbPartGroupParam | 0x150 | random_rotdir | `int` |
| gbPartGroupParam | 0x154 | random_mirroringx | `int` |
| gbPartGroupParam | 0x158 | random_mirroringy | `int` |
| gbPartGroupParam | 0x15c | chainnum | `int` |
| gbPartGroupParam | 0x160 | framenum | `int` |
| gbPartGroupParam | 0x164 | blendmode | `int` |
| gbPartGroupParam | 0x168 | SizeCtrl | `gbPartParamControl` |
| gbPartGroupParam | 0x20 | particle_lighting | `int` |
| gbPartGroupParam | 0x24 | gravity | `float` |
| gbPartGroupParam | 0x2530 | AlphaCtrl | `gbPartParamControl` |
| gbPartGroupParam | 0x28 | noresis | `float` |
| gbPartGroupParam | 0x2c | aresis_velocity | `int` |
| gbPartGroupParam | 0x30 | aresis_size | `int` |
| gbPartGroupParam | 0x34 | aresis_constant | `float` |
| gbPartGroupParam | 0x3714 | RGBCtrl | `gbPartParamControl` |
| gbPartGroupParam | 0x38 | filename | `char[256]` |
| gbPartGroupParam | 0x48f8 | TexArray | `gbTextureArray` |
| gbPartGroupParam | 0x493c | pREffect | `gbRenderEffect *` |
| gbPartParamControl | 0x0 | nCurve | `int` |
| gbPartParamControl | 0x3b0 | Segment | `gbVec3D[101][3]` |
| gbPartParamControl | 0x4 | nCtrlPt | `int` |
| gbPartParamControl | 0x48 | Descript | `char[128]` |
| gbPartParamControl | 0x8 | Name | `char[64]` |
| gbPartParamControl | 0xc8 | MinPt | `gbVec3D` |
| gbPartParamControl | 0xd4 | MaxPt | `gbVec3D` |
| gbPartParamControl | 0xe0 | CtrlPt | `gbVec3D[20][3]` |
| gbParticleEffect | 0x108 | CurTime | `double` |
| gbParticleEffect | 0x110 | ElapseTime | `double` |
| gbParticleEffect | 0x118 | SpaceScale | `float` |
| gbParticleEffect | 0x11c | m_ToWorld | `gbMatrix4` |
| gbParticleEffect | 0x58 | Name | `char[64]` |
| gbParticleEffect | 0x98 | nPartGroup | `int` |
| gbParticleEffect | 0x9c | nGroupParam | `int` |
| gbParticleEffect | 0xa0 | nEmitter | `int` |
| gbParticleEffect | 0xa4 | pPartGroups | `gbParticleGroup *` |
| gbParticleEffect | 0xa8 | pGroupParams | `gbPartGroupParam *` |
| gbParticleEffect | 0xac | pEmitters | `gbPartEmitter *` |
| gbParticleEffect | 0xb0 | maxparticle | `int` |
| gbParticleEffect | 0xb4 | emittedto | `int` |
| gbParticleEffect | 0xb8 | npwmr | `int` |
| gbParticleEffect | 0xbc | pParticles | `gbParticleUnit *` |
| gbParticleEffect | 0xc0 | gravity | `float` |
| gbParticleEffect | 0xc4 | timescale | `float` |
| gbParticleEffect | 0xc8 | maxfps | `int` |
| gbParticleEffect | 0xcc | camerafollow | `int` |
| gbParticleEffect | 0xd0 | camerafollowdis | `float` |
| gbParticleEffect | 0xd4 | gravityeffect | `int` |
| gbParticleEffect | 0xd8 | frontplane | `float` |
| gbParticleEffect | 0xdc | backplane | `float` |
| gbParticleEffect | 0xe0 | objectoffset | `gbVec3D` |
| gbParticleEffect | 0xec | systemoffset | `gbVec3D` |
| gbParticleEffect | 0xf8 | systemvelocity | `gbVec3D` |
| gbParticleGroup | 0x0 | Name | `char[64]` |
| gbParticleGroup | 0x40 | Life | `double` |
| gbParticleGroup | 0x48 | EmitterData | `gbEmitterData` |
| gbParticleGroup | 0x78 | pGroupParam | `gbPartGroupParam *` |
| gbParticleGroup | 0x7c | pEmitter | `gbPartEmitter *` |
| gbParticleGroup | 0x80 | pAllUnits | `gbParticleUnit *` |
| gbParticleGroup | 0x84 | MaxUnits | `int` |
| gbParticleGroup | 0x88 | nAlivePart | `int` |
| gbParticleGroup | 0x8c | pParticleEffect | `gbParticleEffect *` |
| gbParticleUnit | 0x0 | alive | `int` |
| gbParticleUnit | 0x10 | age | `float` |
| gbParticleUnit | 0x14 | looptex | `int` |
| gbParticleUnit | 0x18 | chainindex | `int` |
| gbParticleUnit | 0x1c | velocity | `gbVec3D` |
| gbParticleUnit | 0x28 | resistance | `gbVec3D` |
| gbParticleUnit | 0x34 | curpos | `gbVec3D` |
| gbParticleUnit | 0x40 | cursize | `float` |
| gbParticleUnit | 0x44 | curvertexalpha | `float` |
| gbParticleUnit | 0x48 | currgbcolor | `gbColorQuad` |
| gbParticleUnit | 0x4c | rotation | `float` |
| gbParticleUnit | 0x50 | dir | `int` |
| gbParticleUnit | 0x8 | life | `double` |
| gbPixelFormat | 0x0 | Type | `gbPixelFmtType` |
| gbPixelFormat | 0x10 | g_mask | `unsigned int` |
| gbPixelFormat | 0x14 | b_mask | `unsigned int` |
| gbPixelFormat | 0x18 | a_mask | `unsigned int` |
| gbPixelFormat | 0x1c | r_shift | `unsigned int` |
| gbPixelFormat | 0x20 | g_shift | `unsigned int` |
| gbPixelFormat | 0x24 | b_shift | `unsigned int` |
| gbPixelFormat | 0x28 | a_shift | `unsigned int` |
| gbPixelFormat | 0x4 | Bpp | `int` |
| gbPixelFormat | 0x8 | Pal | `gbColorQuad *` |
| gbPixelFormat | 0xc | r_mask | `unsigned int` |
| gbPrintFont | 0x0 | pGfxMgr | `gbGfxManager *` |
| gbPrintFont | 0x10 | numInfo | `int` |
| gbPrintFont | 0x14 | pt3DInfo | `FontPrint3DInfo *` |
| gbPrintFont | 0x18 | num3DInfo | `int` |
| gbPrintFont | 0x1c | max3DInfo | `int` |
| gbPrintFont | 0x20 | strBuffer | `unsigned char *` |
| gbPrintFont | 0x24 | maxStrBuffer | `int` |
| gbPrintFont | 0x28 | curStrLoc | `int` |
| gbPrintFont | 0x2c | curColor | `gbColorQuad` |
| gbPrintFont | 0x30 | ScaleX | `float` |
| gbPrintFont | 0x34 | ScaleY | `float` |
| gbPrintFont | 0x38 | PitchX | `float` |
| gbPrintFont | 0x3c | PitchY | `float` |
| gbPrintFont | 0x4 | ptInfo | `FontPrintInfo *` |
| gbPrintFont | 0x40 | ZValue | `float` |
| gbPrintFont | 0x44 | pEffect | `gbRenderEffect *[2]` |
| gbPrintFont | 0x8 | pSortInfo | `FontSortInfoObj *` |
| gbPrintFont | 0xc | maxInfo | `int` |
| gbPrintFontMgr | 0x0 | pAllFont | `gbPrintFont *[5]` |
| gbQuaternion | 0x0 | x | `float` |
| gbQuaternion | 0x4 | y | `float` |
| gbQuaternion | 0x8 | z | `float` |
| gbQuaternion | 0xc | w | `float` |
| gbRay | 0x0 | Origin | `gbVec3D` |
| gbRay | 0xc | Direction | `gbVec3D` |
| gbRefObject | 0x4 | RefCount | `int` |
| gbRenderEffect | 0x18 | m_pEffect | `ID3DXEffect *` |
| gbRenderEffect | 0x1c | m_Flags | `unsigned int` |
| gbRenderEffect | 0x20 | m_DeclHandle | `IDirect3DVertexDeclaration9 *` |
| gbRenderEffect | 0x24 | m_ParamHandle | `unsigned int[8]` |
| gbRenderEffect_D3D | 0x0 | _tail_000 | `char[4]` |
| gbRenderInfoObj | 0x0 | pNode | `gbVisNode *` |
| gbRenderInfoObj | 0x10 | pTexArray | `gbTextureArray *` |
| gbRenderInfoObj | 0x14 | Priority | `int` |
| gbRenderInfoObj | 0x18 | Flags | `unsigned int` |
| gbRenderInfoObj | 0x1c | EffectFlag | `unsigned int` |
| gbRenderInfoObj | 0x20 | ViewMat | `gbMatrix4` |
| gbRenderInfoObj | 0x4 | Z | `float` |
| gbRenderInfoObj | 0x60 | pAllLight | `gbVolModNode *[2]` |
| gbRenderInfoObj | 0x68 | pAllFog | `gbVolModNode *[2]` |
| gbRenderInfoObj | 0x8 | Param | `unsigned int` |
| gbRenderInfoObj | 0xc | pEffect | `gbRenderEffect *` |
| gbResManager | 0x0 | AllResPt | `char[12]` |
| gbResource | 0x10 | IsLoaded | `int` |
| gbResource | 0x14 | pMgr | `gbResManager *` |
| gbResource | 0x8 | pName | `char *` |
| gbResource | 0xc | NameCrc32 | `unsigned int` |
| gbSceneGraph | 0x0 | pAllRObj | `gbRenderInfoObj *` |
| gbSceneGraph | 0x1032c | m_nWaterNode | `int` |
| gbSceneGraph | 0x10330 | m_CVDNode | `gbRenderInfoObj[8]` |
| gbSceneGraph | 0x106b0 | m_nCVDNode | `int` |
| gbSceneGraph | 0x106b4 | m_renderOctree | `unsigned char` |
| gbSceneGraph | 0x106b5 | m_renderWater | `unsigned char` |
| gbSceneGraph | 0x106b6 | m_bAttachSceneWater | `unsigned char` |
| gbSceneGraph | 0x4 | index | `int[4096]` |
| gbSceneGraph | 0x4004 | CurRObjPos | `int` |
| gbSceneGraph | 0x4008 | pnodebuf | `gbOctreeNode *[4096]` |
| gbSceneGraph | 0x8008 | pOctree | `gbOctree *` |
| gbSceneGraph | 0x800c | pSceneRoot | `gbVisNode *` |
| gbSceneGraph | 0x8010 | pAllShadowObj | `gbRenderInfoObj[16]` |
| gbSceneGraph | 0x8710 | nShadowObj | `int` |
| gbSceneGraph | 0x8714 | pAllVolMod | `gbVolModNode *[256]` |
| gbSceneGraph | 0x8b14 | VolModXform | `gbMatrix4[256]` |
| gbSceneGraph | 0xcb14 | nVolModNode | `int` |
| gbSceneGraph | 0xcb18 | pGfxMgr | `gbGfxManager *` |
| gbSceneGraph | 0xcb1c | pSkyBox | `gbVisNode *` |
| gbSceneGraph | 0xcb20 | pShadowQuadEffect | `gbRenderEffect *` |
| gbSceneGraph | 0xcb24 | pCamera | `gbCamera *` |
| gbSceneGraph | 0xcb28 | pBladeMgr | `gbBladeMgr *` |
| gbSceneGraph | 0xcb2c | m_WaterNode | `gbRenderInfoObj[128]` |
| gbSceneNode | 0x0 | _tail_000 | `char[4]` |
| gbSingleton_gbGfxManager | 0x0 | _tail_000 | `char[4]` |
| gbSnow | 0x50 | m_VelXZ | `float` |
| gbSound2DNode | 0x0 | pAudioMgr | `gbAudioManager *` |
| gbSound2DNode | 0x4 | hSample | `_SAMPLE *` |
| gbSound2DNode | 0x8 | nLoop | `int` |
| gbSound2DNode | 0xc | Volume | `float` |
| gbSound3DNode | 0x0 | pAudioMgr | `gbAudioManager *` |
| gbSound3DNode | 0x14 | Velocity | `gbVec3D` |
| gbSound3DNode | 0x20 | Orientation | `gbVec3D` |
| gbSound3DNode | 0x2c | EffectType | `int` |
| gbSound3DNode | 0x30 | Volume | `float` |
| gbSound3DNode | 0x34 | nLoop | `int` |
| gbSound3DNode | 0x38 | MinDist | `float` |
| gbSound3DNode | 0x3c | MaxDist | `float` |
| gbSound3DNode | 0x4 | hSample | `h3DPOBJECT *` |
| gbSound3DNode | 0x8 | Position | `gbVec3D` |
| gbSoundData | 0x18 | pimage | `char *` |
| gbSphere | 0x0 | r | `float` |
| gbSphere | 0x4 | center | `gbVec3D` |
| gbSurfaceDesc | 0x0 | width | `int` |
| gbSurfaceDesc | 0x10 | pbits | `char *` |
| gbSurfaceDesc | 0x4 | height | `int` |
| gbSurfaceDesc | 0x8 | format | `gbPixelFmtType` |
| gbSurfaceDesc | 0xc | pitch | `int` |
| gbTagNode | 0x0 | name | `char[32]` |
| gbTagNode | 0x20 | origin | `gbVec3D` |
| gbTagNode | 0x2c | userdata | `unsigned int` |
| gbTagXBladeNode | 0x0 | tagNodeA | `gbTagNode` |
| gbTagXBladeNode | 0x30 | tagNodeB | `gbTagNode` |
| gbTagXBladeNode | 0x60 | pBladeMgr | `gbBladeMgr *` |
| gbTexFlipAnim | 0x0 | ppAllTex | `gbTexture * *` |
| gbTexFlipAnim | 0x4 | AnimIndex | `int` |
| gbTexFlipAnim | 0x8 | nTex | `int` |
| gbTexFlipAnim | 0xc | interval | `int` |
| gbTexture | 0x18 | Width | `int` |
| gbTexture | 0x1c | Height | `int` |
| gbTexture | 0x20 | pTexImage | `gbImage2D *` |
| gbTexture | 0x24 | InFmt | `gbPixelFormat` |
| gbTexture | 0x50 | nLevels | `int` |
| gbTextureArray | 0x0 | pTexPt | `gbTexture *[16]` |
| gbTextureArray | 0x40 | nTex | `int` |
| gbTexture_D3D | 0x54 | pTex | `IDirect3DBaseTexture9 *` |
| gbTexture_D3D | 0x58 | pDS | `IDirect3DSurface9 *` |
| gbTexture_D3D | 0x5c | m_ImgFormat | `unsigned int` |
| gbUIQuad | 0x0 | sx | `float` |
| gbUIQuad | 0x10 | su | `float` |
| gbUIQuad | 0x14 | sv | `float` |
| gbUIQuad | 0x18 | eu | `float` |
| gbUIQuad | 0x1c | ev | `float` |
| gbUIQuad | 0x20 | z | `float` |
| gbUIQuad | 0x24 | color | `unsigned int` |
| gbUIQuad | 0x4 | sy | `float` |
| gbUIQuad | 0x8 | ex | `float` |
| gbUIQuad | 0xc | ey | `float` |
| gbVFile1 | 0x0 | OpenMode | `unsigned int` |
| gbVFile1 | 0x10c | m_NowAddr | `unsigned int` |
| gbVFile1 | 0x4 | EntryAddr | `unsigned int` |
| gbVFile1 | 0x8 | FileSize | `unsigned int` |
| gbVFile1 | 0xc | pFilePath | `char[256]` |
| gbVFileSystem | 0x0 | IsInit | `int` |
| gbVFileSystem | 0x10 | m_pckfp | `_iobuf *` |
| gbVFileSystem | 0x14 | m_itemcount | `unsigned int` |
| gbVFileSystem | 0x18 | m_cpk | `CPK` |
| gbVFileSystem | 0x4 | rtDirectory | `char *` |
| gbVFileSystem | 0x8 | pFileBuffer | `gbVFile *` |
| gbVFileSystem | 0xc | Type | `int` |
| gbVec2D | 0x0 | x | `float` |
| gbVec2D | 0x4 | y | `float` |
| gbVec3D | 0x0 | x | `float` |
| gbVec3D | 0x4 | y | `float` |
| gbVec3D | 0x8 | z | `float` |
| gbVec4D | 0x0 | x | `float` |
| gbVec4D | 0x4 | y | `float` |
| gbVec4D | 0x8 | z | `float` |
| gbVec4D | 0xc | w | `float` |
| gbVertPoolMgr | 0x0 | StaticPool | `gbChain1D[32]` |
| gbVertPoolMgr | 0x200 | StaticPoolFVF | `unsigned int[32]` |
| gbVertPoolMgr | 0x280 | StaticIndex | `gbChain1D` |
| gbVertPoolMgr | 0x290 | pDynPool | `gbDynVertBuf *[32]` |
| gbVertPoolMgr | 0x310 | DynPoolFVF | `unsigned int[32]` |
| gbVertPoolMgr | 0x390 | ReadOnlyPool | `gbChain1D[32]` |
| gbVertPoolMgr | 0x590 | ReadOnlyPoolFVF | `unsigned int[32]` |
| gbVertPoolMgr | 0x610 | VertPoolSize | `int` |
| gbVertPoolMgr | 0x614 | IndexPoolSize | `int` |
| gbVertPoolMgr | 0x618 | DynVertPoolSize | `int` |
| gbVertPoolMgr | 0x61c | ReadOnlyPoolSize | `int` |
| gbVertPoolMgr | 0x620 | pGfxMgr | `gbGfxManager *` |
| gbVertexBubble | 0x10 | BubSize | `int` |
| gbVertexBubble | 0x14 | nVerts | `int` |
| gbVertexBubble | 0x18 | pXYZ | `float *` |
| gbVertexBubble | 0x1c | pNormal | `float *` |
| gbVertexBubble | 0x20 | pColor1 | `gbColorQuad *` |
| gbVertexBubble | 0x24 | pColor2 | `gbColorQuad *` |
| gbVertexBubble | 0x28 | pUV | `float *[4]` |
| gbVertexBubble | 0x8 | pPool | `gbVertexPool *` |
| gbVertexBubble | 0xc | Start | `int` |
| gbVertexElement | 0x0 | stream | `unsigned short` |
| gbVertexElement | 0x2 | offset | `unsigned short` |
| gbVertexElement | 0x4 | type | `unsigned char` |
| gbVertexElement | 0x5 | method | `unsigned char` |
| gbVertexElement | 0x6 | usage | `unsigned char` |
| gbVertexElement | 0x7 | usageindex | `unsigned char` |
| gbVertexPool | 0x10 | VertNum | `int` |
| gbVertexPool | 0x14 | VertType | `unsigned int` |
| gbVertexPool | 0x18 | Stride | `int` |
| gbVertexPool | 0x1c | FreeVertBub | `gbChain1D` |
| gbVertexPool | 0x2c | UsedVertBub | `gbChain1D` |
| gbVertexPool | 0x8 | pGfxMgr | `gbGfxManager *` |
| gbVertexPool | 0xc | pMemBuf | `char *` |
| gbViewPort | 0x0 | x | `int` |
| gbViewPort | 0x10 | minz | `float` |
| gbViewPort | 0x14 | maxz | `float` |
| gbViewPort | 0x4 | y | `int` |
| gbViewPort | 0x8 | width | `int` |
| gbViewPort | 0xc | height | `int` |
| gbVisNode | 0x1c | pSceneGraph | `gbSceneGraph *` |
| gbVisNode | 0x34 | Priority | `int` |
| gbVisNode | 0x38 | TimeScale | `float` |
| gbVisNode | 0x3c | bShow | `int` |
| gbVisNode | 0x40 | bDoShadow | `int` |
| gbVisNode | 0x44 | pCullObj | `gbOctreeNode *` |
| gbVisNode | 0x48 | pCullPrev | `gbVisNode *` |
| gbVisNode | 0x4c | pCullNext | `gbVisNode *` |
| gbVisNode | 0x50 | BlendParam | `float` |
| gbVisNode | 0x54 | BlendFlag | `NodeBlend` |
| gbVolModNode | 0x58 | m_ToWorld | `gbMatrix4` |
| gbVolModNode | 0x98 | m_ToView | `gbMatrix4` |
| gbVolModNode | 0xd8 | m_pModObj | `float *` |
| gbVolumeModifier | 0x0 | _tail_000 | `char[4]` |
| graph | 0x0 | curve_num | `int` |
| graph | 0x3b0 | realdata | `D3DXVECTOR3[20][3]` |
| graph | 0x4 | cp_num | `int` |
| graph | 0x48 | describe | `char[128]` |
| graph | 0x680 | interpolate | `char[256]` |
| graph | 0x8 | graphname | `char[64]` |
| graph | 0xc8 | min | `D3DXVECTOR3` |
| graph | 0xd4 | max | `D3DXVECTOR3` |
| graph | 0xe0 | disdata | `D3DXVECTOR3[20][3]` |
| h3DPOBJECT | 0x0 | junk | `DWORD` |
| ioinfo | 0x0 | osfhnd | `long` |
| ioinfo | 0x4 | osfile | `char` |
| ioinfo | 0x5 | pipech | `char` |
| lconv | 0x0 | decimal_point | `char *` |
| lconv | 0x10 | currency_symbol | `char *` |
| lconv | 0x14 | mon_decimal_point | `char *` |
| lconv | 0x18 | mon_thousands_sep | `char *` |
| lconv | 0x1c | mon_grouping | `char *` |
| lconv | 0x20 | positive_sign | `char *` |
| lconv | 0x24 | negative_sign | `char *` |
| lconv | 0x28 | int_frac_digits | `char` |
| lconv | 0x29 | frac_digits | `char` |
| lconv | 0x2a | p_cs_precedes | `char` |
| lconv | 0x2b | p_sep_by_space | `char` |
| lconv | 0x2c | n_cs_precedes | `char` |
| lconv | 0x2d | n_sep_by_space | `char` |
| lconv | 0x2e | p_sign_posn | `char` |
| lconv | 0x2f | n_sign_posn | `char` |
| lconv | 0x4 | thousands_sep | `char *` |
| lconv | 0x8 | grouping | `char *` |
| lconv | 0xc | int_curr_symbol | `char *` |
| localVar0 | 0x0 | l_ebp | `DWORD` |
| localVar0 | 0x4 | l_esi | `DWORD` |
| localVar0 | 0x8 | l_edi | `DWORD` |
| localVar1 | 0x0 | l_absXY | `__int64` |
| localVar1 | 0x10 | l_ebp | `DWORD` |
| localVar1 | 0x14 | l_esi | `DWORD` |
| localVar1 | 0x18 | l_edi | `DWORD` |
| localVar1 | 0x8 | l_absZW | `__int64` |
| localVar2 | 0x0 | l_Matrix | `SSE4xMatrix` |
| localVar2 | 0x100 | l_ebp | `DWORD` |
| localVar2 | 0x104 | l_esi | `DWORD` |
| localVar2 | 0x108 | l_edi | `DWORD` |
| m_RoleState | 0x0 | m_Headbk | `UIStatic` |
| m_RoleState | 0x1014 | m_NeedRc | `tagRECT` |
| m_RoleState | 0x1f0 | m_Name | `UIStatic` |
| m_RoleState | 0x288 | m_Jing | `UIStatic` |
| m_RoleState | 0x320 | m_JingBar | `UIProgressBar` |
| m_RoleState | 0x414 | m_JingVal | `UIStatic` |
| m_RoleState | 0x4ac | m_Shen | `UIStatic` |
| m_RoleState | 0x544 | m_ShenBar | `UIProgressBar` |
| m_RoleState | 0x638 | m_ShenVal | `UIStatic` |
| m_RoleState | 0x6d0 | m_Qi | `UIStatic` |
| m_RoleState | 0x768 | m_QiBar | `UIProgressBar` |
| m_RoleState | 0x85c | m_QiVal | `UIStatic` |
| m_RoleState | 0x8f4 | m_AttFrameHead | `UIStatic` |
| m_RoleState | 0x98 | m_Head | `UIButton` |
| m_RoleState | 0x98c | m_F | `UIStatic` |
| m_RoleState | 0xa24 | m_W | `UIStatic` |
| m_RoleState | 0xabc | m_S | `UIStatic` |
| m_RoleState | 0xb54 | m_Y | `UIStatic` |
| m_RoleState | 0xbec | m_Exp | `UIStatic` |
| m_RoleState | 0xc84 | m_RoleAtt | `UIStatic[5]` |
| m_RoleState | 0xf7c | m_NeedArrow | `UIStatic` |
| magic_tab | 0x0 | magic_id | `DWORD` |
| magic_tab | 0x4 | min_usetime | `int` |
| magic_tab | 0x8 | max_usetime | `int` |
| magic_tab | 0xc | lv | `int` |
| me_RoleState | 0x0 | m_Headbk | `UIStatic` |
| me_RoleState | 0x1014 | m_RoleAttCng | `UIStatic[10]` |
| me_RoleState | 0x1604 | m_RoleAttEqual | `UIStatic[10]` |
| me_RoleState | 0x1bf4 | m_EquipPic | `UIStatic` |
| me_RoleState | 0x1c8c | m_EquipWeapon | `UIButton` |
| me_RoleState | 0x1de4 | m_EquipHat | `UIButton` |
| me_RoleState | 0x1f0 | m_Name | `UIStatic` |
| me_RoleState | 0x1f3c | m_EquipCloth | `UIButton` |
| me_RoleState | 0x2094 | m_EquipShoes | `UIButton` |
| me_RoleState | 0x21ec | m_EquipAdorn1 | `UIButton` |
| me_RoleState | 0x2344 | m_EquipAdorn2 | `UIButton` |
| me_RoleState | 0x288 | m_Jing | `UIStatic` |
| me_RoleState | 0x320 | m_JingBar | `UIProgressBar` |
| me_RoleState | 0x414 | m_JingVal | `UIStatic` |
| me_RoleState | 0x4ac | m_Shen | `UIStatic` |
| me_RoleState | 0x544 | m_ShenBar | `UIProgressBar` |
| me_RoleState | 0x638 | m_ShenVal | `UIStatic` |
| me_RoleState | 0x6d0 | m_Qi | `UIStatic` |
| me_RoleState | 0x768 | m_QiBar | `UIProgressBar` |
| me_RoleState | 0x85c | m_QiVal | `UIStatic` |
| me_RoleState | 0x8f4 | m_AttFrameHead | `UIStatic` |
| me_RoleState | 0x98 | m_Head | `UIButton` |
| me_RoleState | 0x98c | m_AttFramePose | `UIStatic` |
| me_RoleState | 0xa24 | m_RoleAtt | `UIStatic[10]` |
| p_RoleState | 0x0 | m_Headbk | `UIStatic` |
| p_RoleState | 0x1014 | m_NeedRc | `tagRECT` |
| p_RoleState | 0x1f0 | m_Name | `UIStatic` |
| p_RoleState | 0x288 | m_Jing | `UIStatic` |
| p_RoleState | 0x320 | m_JingBar | `UIProgressBar` |
| p_RoleState | 0x414 | m_JingVal | `UIStatic` |
| p_RoleState | 0x4ac | m_Shen | `UIStatic` |
| p_RoleState | 0x544 | m_ShenBar | `UIProgressBar` |
| p_RoleState | 0x638 | m_ShenVal | `UIStatic` |
| p_RoleState | 0x6d0 | m_Qi | `UIStatic` |
| p_RoleState | 0x768 | m_QiBar | `UIProgressBar` |
| p_RoleState | 0x85c | m_QiVal | `UIStatic` |
| p_RoleState | 0x8f4 | m_AttFrameHead | `UIStatic` |
| p_RoleState | 0x98 | m_Head | `UIButton` |
| p_RoleState | 0x98c | m_F | `UIStatic` |
| p_RoleState | 0xa24 | m_W | `UIStatic` |
| p_RoleState | 0xabc | m_S | `UIStatic` |
| p_RoleState | 0xb54 | m_Y | `UIStatic` |
| p_RoleState | 0xbec | m_Exp | `UIStatic` |
| p_RoleState | 0xc84 | m_RoleAtt | `UIStatic[5]` |
| p_RoleState | 0xf7c | m_NeedArrow | `UIStatic` |
| pcmwaveformat_tag | 0x0 | wf | `waveformat_tag` |
| pcmwaveformat_tag | 0xe | wBitsPerSample | `WORD` |
| primitive | 0x14 | _plane | `char *[13]` |
| primitive | 0x4 | _vertices | `char *[4]` |
| primitive | 0x48 | _userFlags | `uint` |
| rgbcolor_particle_graph | 0x0 | _tail_000 | `char[5300]` |
| rotation_particle_graph | 0x0 | _tail_000 | `char[5300]` |
| rotmulti_emitter_graph | 0x0 | _tail_000 | `char[5300]` |
| rterrmsgs | 0x0 | rterrno | `int` |
| rterrmsgs | 0x4 | rterrtxt | `char *` |
| sCollision | 0x0 | collider | `char[4]` |
| sCollision | 0x38 | collisionDistance | `float` |
| sCollision | 0x3c | collisionType | `CollisionType` |
| sCollision | 0x4 | collisionPlane | `char[52]` |
| s_RoleState | 0x0 | m_Headbk | `UIStatic` |
| s_RoleState | 0x130 | m_Name | `UIStatic` |
| s_RoleState | 0x1c8 | m_Jing | `UIStatic` |
| s_RoleState | 0x260 | m_JingBar | `UIProgressBar` |
| s_RoleState | 0x354 | m_JingVal | `UIStatic` |
| s_RoleState | 0x3ec | m_Shen | `UIStatic` |
| s_RoleState | 0x484 | m_ShenBar | `UIProgressBar` |
| s_RoleState | 0x578 | m_ShenVal | `UIStatic` |
| s_RoleState | 0x610 | m_Qi | `UIStatic` |
| s_RoleState | 0x6a8 | m_QiBar | `UIProgressBar` |
| s_RoleState | 0x79c | m_QiVal | `UIStatic` |
| s_RoleState | 0x834 | m_Shade | `UIStatic` |
| s_RoleState | 0x8cc | m_Portrait | `UIStatic` |
| s_RoleState | 0x964 | m_Level | `UIStatic` |
| s_RoleState | 0x98 | m_Head | `UIStatic` |
| s_RoleState | 0x9fc | m_ExpVal | `UIStatic` |
| s_RoleState | 0xa94 | m_NextLv | `UIStatic` |
| s_RoleState | 0xb2c | m_WuLing | `UIStatic[5]` |
| s_RoleState | 0xe24 | m_FWSY | `UIStatic` |
| s_RoleState | 0xebc | m_FWSYrc | `tagRECT` |
| s_SpecialPropItem | 0x0 | m_ItemId | `DWORD` |
| s_SpecialPropItem | 0x4 | m_CanUse | `BYTE` |
| scAsmDecoder | 0x0 | m_stack | `scVarStack *` |
| scCmdDef | 0x0 | pfun | `char *` |
| scCmdDef | 0x4 | paramlist | `unsigned char[8]` |
| scCmdDef | 0xc | paramnum | `WORD` |
| scGlobalUserVar | 0x8 | name | `char[16]` |
| scSCEFile | 0x0 | m_fp | `gbVFile *` |
| scSCEFile | 0x4 | m_blocks | `char[16]` |
| scScriptBlock | 0x0 | id | `DWORD` |
| scScriptBlock | 0x4 | desc | `unsigned char[64]` |
| scScriptBlock | 0x44 | codesize | `DWORD` |
| scScriptBlock | 0x48 | pcodedata | `BYTE *` |
| scScriptBlock | 0x4c | uservarnum | `WORD` |
| scScriptBlock | 0x50 | uservar | `scUserVarInfo *` |
| scScriptBlock | 0x54 | ref | `int` |
| scUserVarInfo | 0x0 | type | `BYTE` |
| scUserVarInfo | 0x2 | initlen | `WORD` |
| scUserVarInfo | 0x4 | initdata | `BYTE *` |
| scVARIANT | 0x0 | type | `BYTE` |
| scVARIANT | 0x2 | len | `WORD` |
| scVARIANT | 0x4 | data | `scVARIANT_data` |
| scVARIANT_data | 0x0 | as_int | `float` |
| scVARIANT_data | 0x0_1 | as_float | `float` |
| scVarStack | 0x0 | m_counter | `int` |
| scVarStack | 0x4 | m_vararray | `scVARIANT[32]` |
| sg_customshape | 0x0 | intervec | `D3DXVECTOR3 *` |
| sg_customshape | 0x4 | disarray | `float *` |
| sg_customshape | 0x8 | m_iVecnum | `int` |
| sg_customshape | 0xc | curmat | `D3DXMATRIX` |
| sg_emission_control | 0x0 | name | `char[64]` |
| sg_emission_control | 0x40 | particle_pointer | `int` |
| sg_emission_control | 0x44 | emitter_pointer | `int` |
| sg_emission_control | 0x48 | elapsetime | `float` |
| sg_emission_control | 0x4c | total_elatime | `float` |
| sg_emission_control | 0x50 | maxparticle | `int` |
| sg_emission_control | 0x54 | first_time | `int` |
| sg_emission_control | 0x58 | cyclelength | `float` |
| sg_emission_control | 0x5c | replacestyle | `int` |
| sg_emission_control | 0x60 | particle_array | `sg_particle_data[400]` |
| sg_emission_control | 0x9020 | emitter | `sg_emitter_data` |
| sg_emission_control | 0x904c | pparticle | `sg_particle *` |
| sg_emission_control | 0x9050 | pemitter | `sg_emitter *` |
| sg_emission_control | 0x9054 | scene_pointer | `sg_particle_scene *` |
| sg_emitter | 0x0 | name | `char[64]` |
| sg_emitter | 0x1568 | elerandvec_graph | `elerandvec_emitter_graph` |
| sg_emitter | 0x2a1c | emissionrate_graph | `emissionrate_emitter_graph` |
| sg_emitter | 0x3ed0 | elelife_graph | `elelife_emitter_graph` |
| sg_emitter | 0x40 | relative_position | `D3DXVECTOR3` |
| sg_emitter | 0x4c | emission_scope | `D3DXVECTOR3` |
| sg_emitter | 0x5384 | sizemulti_graph | `sizemulti_emitter_graph` |
| sg_emitter | 0x58 | cs_name | `char[64]` |
| sg_emitter | 0x6838 | rotmulti_graph | `rotmulti_emitter_graph` |
| sg_emitter | 0x7cec | square | `sg_emitter_square` |
| sg_emitter | 0x7d04 | sphere | `sg_emitter_sphere` |
| sg_emitter | 0x7d0c | m_pCS | `sg_customshape` |
| sg_emitter | 0x98 | emitter_shape | `int` |
| sg_emitter | 0x9c | cyclelen_start | `float` |
| sg_emitter | 0xa0 | cyclelen_end | `float` |
| sg_emitter | 0xa4 | cycle_loop | `int` |
| sg_emitter | 0xa8 | lighton | `int` |
| sg_emitter | 0xac | m_fSpeedMulti | `float` |
| sg_emitter | 0xb0 | m_fSizeMulti | `float` |
| sg_emitter | 0xb4 | direction_graph | `direction_emitter_graph` |
| sg_emitter_data | 0x0 | alive | `int` |
| sg_emitter_data | 0x14 | elerandvel_max | `float` |
| sg_emitter_data | 0x18 | elerandvel_min | `float` |
| sg_emitter_data | 0x1c | emissionrate_max | `int` |
| sg_emitter_data | 0x20 | emissionrate_min | `int` |
| sg_emitter_data | 0x24 | elelifetime_max | `float` |
| sg_emitter_data | 0x28 | elelifetime_min | `float` |
| sg_emitter_data | 0x4 | tval | `float` |
| sg_emitter_data | 0x8 | curdir | `D3DXVECTOR3` |
| sg_emitter_sphere | 0x0 | hotspot | `float` |
| sg_emitter_sphere | 0x4 | falloff | `float` |
| sg_emitter_square | 0x0 | min | `D3DXVECTOR3` |
| sg_emitter_square | 0xc | max | `D3DXVECTOR3` |
| sg_particle | 0x0 | particle_name | `char[32]` |
| sg_particle | 0x138 | particlesize | `int` |
| sg_particle | 0x13c | framenums | `int` |
| sg_particle | 0x140 | framesets | `int` |
| sg_particle | 0x144 | animation_type | `int` |
| sg_particle | 0x148 | animation_fps | `int` |
| sg_particle | 0x14c | random_1stframe | `int` |
| sg_particle | 0x150 | random_rotstart | `int` |
| sg_particle | 0x154 | random_rotend | `int` |
| sg_particle | 0x158 | random_rotdir | `int` |
| sg_particle | 0x15c | random_mirroringx | `int` |
| sg_particle | 0x160 | random_mirroringy | `int` |
| sg_particle | 0x1628 | rotation_graph | `rotation_particle_graph` |
| sg_particle | 0x164 | m_fSizeMulti | `float` |
| sg_particle | 0x168 | chainnum | `int` |
| sg_particle | 0x16c | framenum | `int` |
| sg_particle | 0x170 | blendmode | `int` |
| sg_particle | 0x174 | size_graph | `size_particle_graph` |
| sg_particle | 0x20 | particle_lighting | `int` |
| sg_particle | 0x24 | gravity | `float` |
| sg_particle | 0x28 | noresis | `float` |
| sg_particle | 0x2adc | vertexalpha_graph | `vertexalpha_particle_graph` |
| sg_particle | 0x2c | aresis_velocity | `int` |
| sg_particle | 0x30 | aresis_size | `int` |
| sg_particle | 0x34 | aresis_constant | `float` |
| sg_particle | 0x38 | filename | `char[256]` |
| sg_particle | 0x3f90 | rgbcolor_graph | `rgbcolor_particle_graph` |
| sg_particle_data | 0x0 | alive | `int` |
| sg_particle_data | 0x10 | looptex | `int` |
| sg_particle_data | 0x14 | chainindex | `int` |
| sg_particle_data | 0x18 | velocity | `D3DXVECTOR3` |
| sg_particle_data | 0x24 | resistance | `D3DXVECTOR3` |
| sg_particle_data | 0x30 | curpos | `D3DXVECTOR3` |
| sg_particle_data | 0x3c | cursize | `float` |
| sg_particle_data | 0x4 | elapsetime | `float` |
| sg_particle_data | 0x40 | curvertexalpha | `float` |
| sg_particle_data | 0x44 | currgbcolor | `D3DXCOLOR` |
| sg_particle_data | 0x54 | rotation | `float` |
| sg_particle_data | 0x58 | dir | `int` |
| sg_particle_data | 0x8 | lifetime | `float` |
| sg_particle_data | 0xc | tval | `float` |
| sg_particle_scene | 0x0 | name | `char[256]` |
| sg_particle_scene | 0x100 | emission_controlnum | `int` |
| sg_particle_scene | 0x104 | particle_num | `int` |
| sg_particle_scene | 0x108 | emitter_num | `int` |
| sg_particle_scene | 0x10c | active_particle | `int` |
| sg_particle_scene | 0x110 | active_emitter | `int` |
| sg_particle_scene | 0x114 | active_emissioncontrol | `int` |
| sg_particle_scene | 0x118 | econtrol | `sg_emission_control[4]` |
| sg_particle_scene | 0x24278 | ecenable | `int[4]` |
| sg_particle_scene | 0x24288 | cur_sel | `int` |
| sg_particle_scene | 0x2428c | particle | `sg_particle[4]` |
| sg_particle_scene | 0x3939c | emitter | `sg_emitter[4]` |
| sg_particle_scene | 0x588fc | maxparticle | `int` |
| sg_particle_scene | 0x58900 | emittedto | `int` |
| sg_particle_scene | 0x58904 | npwmr | `int` |
| sg_particle_scene | 0x58908 | gravity | `float` |
| sg_particle_scene | 0x5890c | timescale | `float` |
| sg_particle_scene | 0x58910 | maxfps | `int` |
| sg_particle_scene | 0x58914 | camerafollow | `int` |
| sg_particle_scene | 0x58918 | camerafollowdis | `float` |
| sg_particle_scene | 0x5891c | gravityeffect | `int` |
| sg_particle_scene | 0x58920 | frontplane | `float` |
| sg_particle_scene | 0x58924 | backplane | `float` |
| sg_particle_scene | 0x58928 | objectoffset | `D3DXVECTOR3` |
| sg_particle_scene | 0x58934 | systemoffset | `D3DXVECTOR3` |
| sg_particle_scene | 0x58940 | systemvelocity | `D3DXVECTOR3` |
| sg_particle_scene | 0x5894c | m_fMultisize | `float` |
| size_particle_graph | 0x0 | _tail_000 | `char[5300]` |
| sizemulti_emitter_graph | 0x0 | _tail_000 | `char[5300]` |
| skill_tab | 0x0 | skill_id | `DWORD` |
| skill_tab | 0x4 | lv | `int` |
| st_Manager | 0x0 | m_Type | `BYTE` |
| st_Manager | 0x1 | m_Dicker | `BYTE` |
| subPARAM | 0x0 | f1 | `float` |
| subPARAM | 0x18 | f3 | `float` |
| subPARAM | 0x24 | f4 | `float` |
| subPARAM | 0x30 | f5 | `float` |
| subPARAM | 0x3c | f6 | `float` |
| subPARAM | 0xc | f2 | `float` |
| t3DModel | 0x0 | numOfObjects | `int` |
| t3DModel | 0x18 | pObject | `std::vector<t3DObject,std::allocator<t3DObject> >` |
| t3DModel | 0x4 | numOfMaterials | `int` |
| t3DModel | 0x8 | pMaterials | `std::vector<tMaterialInfo,std::allocator<tMaterialInfo> >` |
| t3DObject | 0x0 | numOfVerts | `int` |
| t3DObject | 0x10 | bHasTexture | `BYTE` |
| t3DObject | 0x11 | strName | `char[255]` |
| t3DObject | 0x110 | pVerts | `D3DXVECTOR3 *` |
| t3DObject | 0x114 | pNormals | `D3DXVECTOR3 *` |
| t3DObject | 0x118 | pTexVerts | `D3DXVECTOR2 *` |
| t3DObject | 0x11c | pFaces | `tFace *` |
| t3DObject | 0x4 | numOfFaces | `int` |
| t3DObject | 0x8 | numTexVertex | `int` |
| t3DObject | 0xc | materialID | `int` |
| tChunk | 0x0 | ID | `WORD` |
| tChunk | 0x4 | length | `UINT` |
| tChunk | 0x8 | bytesRead | `UINT` |
| tFace | 0x0 | vertIndex | `int[3]` |
| tFace | 0xc | coordIndex | `int[3]` |
| tMaterialInfo | 0x0 | strName | `char[255]` |
| tMaterialInfo | 0x1fe | color | `unsigned char[3]` |
| tMaterialInfo | 0x204 | fColor | `float[3]` |
| tMaterialInfo | 0x210 | texureId | `int` |
| tMaterialInfo | 0x214 | uTile | `int` |
| tMaterialInfo | 0x218 | vTile | `float` |
| tMaterialInfo | 0x21c | uOffset | `float` |
| tMaterialInfo | 0x220 | vOffset | `float` |
| tMaterialInfo | 0xff | strFile | `char[255]` |
| tag4DWORD | 0x0 | f1 | `float` |
| tag4DWORD | 0x4 | f2 | `float` |
| tag4DWORD | 0x8 | f3 | `float` |
| tag4DWORD | 0xc | f4 | `float` |
| tagActionCommand | 0x0 | cmdType | `unsigned char` |
| tagActionCommand | 0x14 | fSpeed | `float` |
| tagActionCommand | 0x18 | nCmdParam | `int` |
| tagActionCommand | 0x4 | pTargetActor | `Actor *` |
| tagActionCommand | 0x8 | targetY | `float` |
| tagActionCommand | 0xc | targetZ | `float` |
| tagAnimStateSplit | 0x0 | _anim0 | `char` |
| tagAnimStateSplit | 0x1 | m_bActionPause | `unsigned char` |
| tagAttackSequen | 0x0 | fDeltaTime | `float` |
| tagAttackSequen | 0x10 | pPic | `UIStatic *` |
| tagAttackSequen | 0x14 | nSlot1 | `int` |
| tagAttackSequen | 0x18 | nSlot2 | `int` |
| tagAttackSequen | 0x1c | nRound | `int` |
| tagAttackSequen | 0x20 | bySpeed1 | `BYTE` |
| tagAttackSequen | 0x21 | bySpeed2 | `BYTE` |
| tagAttackSequen | 0x22 | bSlot2Running | `BYTE` |
| tagAttackSequen | 0x23 | bPaused | `BYTE` |
| tagAttackSequen | 0x24 | bValid | `BYTE` |
| tagAttackSequen | 0x4 | fLastTime | `float` |
| tagAttackSequen | 0x8 | nIndex | `int` |
| tagAttackSequen | 0xc | dwID | `DWORD` |
| tagCCT | 0x0 | fp | `char *[4]` |
| tagCCT | 0x10 | dwID | `DWORD` |
| tagCCT | 0x14 | bValid | `BYTE` |
| tagCCT | 0x15 | bExecuted | `BYTE` |
| tagCCT | 0x16 | bFinished | `BYTE` |
| tagCCT | 0x17 | bSplice | `BYTE` |
| tagCCT | 0x18 | fStartTime | `float` |
| tagCCT | 0x1c | fExpectTime | `float` |
| tagCCT | 0x20 | StartPos | `tagCam` |
| tagCCT | 0x38 | EndPos | `tagCam` |
| tagCCT | 0x50 | nStartCam | `int` |
| tagCCT | 0x54 | nEndCam | `int` |
| tagCCT | 0x58 | bStartCamValid | `BYTE` |
| tagCCT | 0x59 | bEndCamValid | `BYTE` |
| tagCCT | 0x5a | bTimeValid | `BYTE` |
| tagCCT | 0x5b | bSpeedValid | `BYTE` |
| tagCCT | 0x5c | bLineMove | `BYTE` |
| tagCCT | 0x5d | bCircleMove | `BYTE` |
| tagCCT | 0x5e | bMechanicsMove | `BYTE` |
| tagCCT | 0x5f | bTimeRevise | `BYTE` |
| tagCCT | 0x60 | bAbsoluteTime | `BYTE` |
| tagCCT | 0x61 | bCounterYaw | `BYTE` |
| tagCCT | 0x62 | bCounterPitch | `BYTE` |
| tagCCT | 0x63 | bCounterRoll | `BYTE` |
| tagCCT | 0x64 | bRandSwing | `BYTE` |
| tagCCT | 0x65 | bSightTrace | `BYTE` |
| tagCCT | 0x66 | bPosTrace | `BYTE` |
| tagCCT | 0x68 | nTraceRole | `int` |
| tagCCT | 0x6c | fStartSpeed | `float` |
| tagCCT | 0x70 | fInertia | `float` |
| tagCCT | 0x74 | fAccelerationTime1 | `float` |
| tagCCT | 0x78 | fAccelerationTime2 | `float` |
| tagCCT | 0x7c | fAcceleration1 | `float` |
| tagCCT | 0x80 | fAcceleration2 | `float` |
| tagCCT | 0x84 | fCircleAngle | `float` |
| tagCCT | 0x88 | fAngleSpeed | `float` |
| tagCCT | 0x8c | fCircleCentreX | `float` |
| tagCCT | 0x90 | fCircleCentreY | `float` |
| tagCCT | 0x94 | fCircleCentreZ | `float` |
| tagCCT | 0x98 | fCircleEndX | `float` |
| tagCCT | 0x9c | fCircleEndY | `float` |
| tagCCT | 0xa0 | fCircleEndZ | `float` |
| tagCCT | 0xa4 | fSwingFre | `float` |
| tagCCT | 0xa8 | fSwing | `float` |
| tagCCT | 0xac | fTimeExpiate | `float` |
| tagCCT | 0xb0 | fStartFOV | `float` |
| tagCCT | 0xb4 | fEndFOV | `float` |
| tagCCT | 0xb8 | fStartTracePosX | `float` |
| tagCCT | 0xbc | fStartTracePosY | `float` |
| tagCCT | 0xc0 | fStartTracePosZ | `float` |
| tagCCT | 0xc4 | dwReserved | `unsigned int[2]` |
| tagCOPYDATASTRUCT | 0x0 | dwData | `DWORD` |
| tagCOPYDATASTRUCT | 0x4 | cbData | `DWORD` |
| tagCOPYDATASTRUCT | 0x8 | lpData | `char *` |
| tagCPKHeader | 0x0 | dwLable | `DWORD` |
| tagCPKHeader | 0x10 | dwMaxFileNum | `DWORD` |
| tagCPKHeader | 0x14 | dwFileNum | `DWORD` |
| tagCPKHeader | 0x18 | dwIsFormatted | `DWORD` |
| tagCPKHeader | 0x1c | dwSizeOfHeader | `DWORD` |
| tagCPKHeader | 0x20 | dwValidTableNum | `DWORD` |
| tagCPKHeader | 0x24 | dwMaxTableNum | `DWORD` |
| tagCPKHeader | 0x28 | dwFragmentNum | `DWORD` |
| tagCPKHeader | 0x2c | dwPackageSize | `DWORD` |
| tagCPKHeader | 0x30 | dwReserved | `unsigned int[20]` |
| tagCPKHeader | 0x4 | dwVersion | `DWORD` |
| tagCPKHeader | 0x8 | dwTableStart | `DWORD` |
| tagCPKHeader | 0xc | dwDataStart | `DWORD` |
| tagCPKTable | 0x0 | dwCRC | `DWORD` |
| tagCPKTable | 0x10 | dwPackedSize | `DWORD` |
| tagCPKTable | 0x14 | dwOriginSize | `DWORD` |
| tagCPKTable | 0x18 | dwExtraInfoSize | `DWORD` |
| tagCPKTable | 0x4 | dwFlag | `DWORD` |
| tagCPKTable | 0x8 | dwFatherCRC | `DWORD` |
| tagCPKTable | 0xc | dwStartPos | `DWORD` |
| tagCam | 0x0 | x | `float` |
| tagCam | 0x10 | pit | `float` |
| tagCam | 0x14 | rol | `float` |
| tagCam | 0x4 | y | `float` |
| tagCam | 0x8 | z | `float` |
| tagCamTask | 0x0 | fp | `char *[4]` |
| tagCamTask | 0x10 | dwID | `DWORD` |
| tagCamTask | 0x14 | bValid | `BYTE` |
| tagCamTask | 0x15 | bExecuted | `BYTE` |
| tagCamTask | 0x16 | bFinished | `BYTE` |
| tagCamTask | 0x18 | fStartTime | `float` |
| tagCamTask | 0x1c | fExpectTime | `float` |
| tagCamTask | 0x20 | StartPos | `tagCam` |
| tagCamTask | 0x38 | EndPos | `tagCam` |
| tagCmdData | 0x0 | dwCmdKind | `DWORD` |
| tagCmdData | 0x10 | bMultiSrcRole | `BYTE` |
| tagCmdData | 0x11 | bMultiDestRole | `BYTE` |
| tagCmdData | 0x12 | bSrcRole | `unsigned char[11]` |
| tagCmdData | 0x28 | bValid | `BYTE` |
| tagCmdData | 0x4 | dwItemID | `DWORD` |
| tagCmdData | 0x8 | nSrcRole | `int` |
| tagCmdData | 0xc | nDestRole | `int` |
| tagCmdDataDestRoleView | 0x0 | _pad_7 | `_BYTE[7]` |
| tagCmdDataDestRoleView | 0x7 | pDestRoleOverlay | `void *` |
| tagCombatTaskData | 0x10c | _todo_10C | `float` |
| tagCombatTaskData | 0x110 | _todo_110 | `int` |
| tagCombatTaskData | 0x114 | _todo_114 | `int` |
| tagCombatTaskData | 0x118 | _todo_118 | `float` |
| tagCombatTaskData | 0x120 | _todo_120 | `int` |
| tagCombatTaskData | 0x124 | _todo_124 | `float` |
| tagCombatTaskData | 0x12c | _todo_12C | `int` |
| tagCombatTaskData | 0x130 | _todo_130 | `float` |
| tagCombatTaskData | 0x138 | _todo_138 | `int` |
| tagCombatTaskData | 0x150 | _todo_150 | `float` |
| tagCombatTaskData | 0x158 | _todo_158 | `int` |
| tagCombatTaskData | 0x160 | m_fFloatParam | `float` |
| tagCombatTaskData | 0x168 | _todo_168 | `float` |
| tagCombatTaskData | 0x170 | _todo_170 | `int` |
| tagCombatTaskData | 0x178 | _todo_178 | `int` |
| tagCombatTaskData | 0x64 | m_fCombatTime | `float` |
| tagCombatTaskData | 0x6c | _todo_06C | `int` |
| tagCombatTaskData | 0x88 | m_fTargetParam | `float` |
| tagCombatTaskData | 0x90 | _todo_090 | `float` |
| tagCombatTaskData | 0xf4 | _todo_0F4 | `int` |
| tagCombatTimerState | 0x364 | pfVal | `float` |
| tagCombatTimerState | 0x368 | m_CCBStageCamBuffer | `char` |
| tagCombatTimerState | 0x4 | m_fCBTimer | `float` |
| tagCombatTimerState | 0x54 | m_nTodo_6E8 | `float` |
| tagCombatTimerState | 0x58 | m_nTodo_6EC | `float` |
| tagCombatTimerState | 0x5c | m_nTodo_6F0 | `float` |
| tagCombatTimerState | 0x68 | m_nTodo_6FC | `float` |
| tagCombatTimerState | 0x6c | m_nTodo_700 | `float` |
| tagCombatTimerState | 0x70 | m_nTodo_704 | `float` |
| tagCombatTimerState | 0x8 | m_nTodo_69C | `int` |
| tagControlData | 0x0 | dwButtonID | `DWORD` |
| tagControlData | 0x4 | dwParam1 | `char *` |
| tagControlData | 0x8 | dwParam2 | `DWORD` |
| tagControlData | 0xc | bValid | `BYTE` |
| tagControlThread | 0x0 | fp | `char *[4]` |
| tagControlThread | 0x10 | fpCaller | `char *[4]` |
| tagControlThread | 0x20 | dwID | `DWORD` |
| tagControlThread | 0x24 | dwFlag | `DWORD` |
| tagControlThread | 0x28 | dwCmdKind | `DWORD` |
| tagControlThread | 0x2c | dwCmdID | `DWORD` |
| tagControlThread | 0x30 | dwReturn | `DWORD` |
| tagControlThread | 0x34 | nTaskIndex | `int` |
| tagControlThread | 0x38 | dwTaskID | `DWORD` |
| tagControlThread | 0x3c | bValid | `BYTE` |
| tagControlThread | 0x3d | bExecuted | `BYTE` |
| tagDemand | 0x0 | nSatisfy | `int` |
| tagDemand | 0x4 | dwThread | `DWORD` |
| tagDemand | 0x8 | bHandle | `char` |
| tagDemand | 0xc | eSpecState | `ECBRoleSpecState` |
| tagEffClass | 0x0 | _tail_000 | `char[4]` |
| tagEffGroup | 0x0 | nValidObj | `int` |
| tagEffGroup | 0x4 | dwEffObjTypeCRC | `unsigned int[16]` |
| tagEffGroup | 0x44 | Task | `char[256]` |
| tagEffLinker | 0x0 | dwTrickID | `DWORD` |
| tagEffLinker | 0x18 | fWaitTime1 | `float` |
| tagEffLinker | 0x1c | fWorkTime1 | `float` |
| tagEffLinker | 0x20 | nEffGroup2 | `int` |
| tagEffLinker | 0x24 | bSrcForceCenter2 | `BYTE` |
| tagEffLinker | 0x25 | bDestForceCenter2 | `BYTE` |
| tagEffLinker | 0x26 | bSrcRole2 | `BYTE` |
| tagEffLinker | 0x27 | bDestRole2 | `BYTE` |
| tagEffLinker | 0x28 | vecPos2 | `gbVec3D` |
| tagEffLinker | 0x34 | fWaitTime2 | `float` |
| tagEffLinker | 0x38 | fWorkTime2 | `float` |
| tagEffLinker | 0x4 | nEffGroup1 | `int` |
| tagEffLinker | 0x8 | bSrcForceCenter1 | `BYTE` |
| tagEffLinker | 0x9 | bDestForceCenter1 | `BYTE` |
| tagEffLinker | 0xa | bSrcRole1 | `BYTE` |
| tagEffLinker | 0xb | bDestRole1 | `BYTE` |
| tagEffLinker | 0xc | vecPos1 | `gbVec3D` |
| tagEffMgrData | 0x0 | _tail_000 | `char[1500]` |
| tagEffObj | 0x0 | dwClassNameCRC | `unsigned int` |
| tagEffObj | 0x10 | pEffect | `CEffObj *` |
| tagEffObj | 0x4 | dwTypeNameCRC | `unsigned int` |
| tagEffObj | 0x8 | dwRunGroupID | `unsigned int` |
| tagEffObj | 0xc | bValid | `unsigned char` |
| tagEffObj | 0xd | bIdle | `unsigned char` |
| tagEffObj | 0xe | bClassObj | `unsigned char` |
| tagEffObjType | 0x0 | dwClassNameCRC | `DWORD` |
| tagEffObjType | 0x100 | fBottomRadiusIncSpeed | `float` |
| tagEffObjType | 0x104 | fTopRiseSpeed | `float` |
| tagEffObjType | 0x108 | fBottomRiseSpeed | `float` |
| tagEffObjType | 0x10c | fTextureRepeat | `float` |
| tagEffObjType | 0x110 | fParam | `float[2]` |
| tagEffObjType | 0x24 | dwTypeNameCRC | `DWORD` |
| tagEffObjType | 0x28 | szTexture | `char[128]` |
| tagEffObjType | 0x4 | szTypeName | `char[30]` |
| tagEffObjType | 0xa8 | nFramePerRow | `int` |
| tagEffObjType | 0xac | nFramePerCol | `int` |
| tagEffObjType | 0xb0 | nFrame | `int` |
| tagEffObjType | 0xb4 | fFramePerSec | `float` |
| tagEffObjType | 0xb8 | fX | `float` |
| tagEffObjType | 0xbc | fY | `float` |
| tagEffObjType | 0xc0 | fZ | `float` |
| tagEffObjType | 0xc4 | fStartYRot | `float` |
| tagEffObjType | 0xc8 | fSize | `float` |
| tagEffObjType | 0xcc | dwColor | `DWORD` |
| tagEffObjType | 0xd0 | nMaxQuad | `int` |
| tagEffObjType | 0xd4 | bValid | `BYTE` |
| tagEffObjType | 0xd5 | bAdditiveBlend | `BYTE` |
| tagEffObjType | 0xd6 | bBillBoard | `BYTE` |
| tagEffObjType | 0xd7 | bNoZTest | `BYTE` |
| tagEffObjType | 0xd8 | fStartXRot | `float` |
| tagEffObjType | 0xdc | fStartZRot | `float` |
| tagEffObjType | 0xe0 | fSacleX | `float` |
| tagEffObjType | 0xe4 | fSacleY | `float` |
| tagEffObjType | 0xe8 | fSacleZ | `float` |
| tagEffObjType | 0xec | fTopShrink | `float` |
| tagEffObjType | 0xf0 | fBottomShrink | `float` |
| tagEffObjType | 0xf4 | fTopRadius | `float` |
| tagEffObjType | 0xf8 | fBottomRadius | `float` |
| tagEffObjType | 0xfc | fTopRadiusIncSpeed | `float` |
| tagEffSParticleSys | 0x0 | m_nEffCount | `int` |
| tagEffSParticleSys | 0x10 | m_vSpawnOffset | `float[2]` |
| tagEffSParticleSys | 0x18 | m_nSpawnFlags | `int` |
| tagEffSParticleSys | 0x1c | m_nSpawnCount | `int` |
| tagEffSParticleSys | 0x20 | m_fSpawnSize | `float` |
| tagEffSParticleSys | 0x24 | m_nSpawnLife | `int` |
| tagEffSParticleSys | 0x28 | m_fSpawnBright | `float` |
| tagEffSParticleSys | 0x2c | m_nSpawnEffect | `int` |
| tagEffSParticleSys | 0x30 | m_bSpawnActive | `unsigned char` |
| tagEffSParticleSys | 0x320 | m_ptLastSpawn | `int[2]` |
| tagEffSParticleSys | 0x38 | m_vSpawn2Pos | `float[2]` |
| tagEffSParticleSys | 0x40 | m_nSpawn2Flags | `int` |
| tagEffSParticleSys | 0x44 | m_nSpawn2Count | `int` |
| tagEffSParticleSys | 0x48 | m_fSpawn2Size | `float` |
| tagEffSParticleSys | 0x4c | m_nSpawn2Color | `int` |
| tagEffSParticleSys | 0x50 | m_nSpawn2Life | `int` |
| tagEffSParticleSys | 0x54 | m_nSpawn2Bright | `int` |
| tagEffSParticleSys | 0x58 | m_nSpawn2Effect | `int` |
| tagEffSParticleSys | 0x5c | m_nSpawn2Rand | `int` |
| tagEffSParticleSys | 0x60 | m_bSpawn2Active | `unsigned char` |
| tagEffSParticleSys | 0x68 | m_vSpawn3Pos | `float[2]` |
| tagEffSParticleSys | 0x70 | m_vSpawn3Rand | `float[2]` |
| tagEffSParticleSys | 0x78 | m_nSpawn3Flags | `int` |
| tagEffSParticleSys | 0x7c | m_nSpawn3Count | `int` |
| tagEffSParticleSys | 0x8 | m_vSpawnPos | `float[2]` |
| tagEffSParticleSys | 0x80 | m_fSpawn3Size | `float` |
| tagEffSParticleSys | 0x84 | m_nSpawn3Color | `int` |
| tagEffSParticleSys | 0x88 | m_fSpawn3Bright | `float` |
| tagEffSParticleSys | 0x8c | m_nSpawn3Life | `int` |
| tagEffSParticleSys | 0x90 | m_bSpawn3Active | `unsigned char` |
| tagEffTaskParam | 0x0 | fQuake | `float` |
| tagEffTaskParam | 0x10 | fSpeedRot | `float` |
| tagEffTaskParam | 0x14 | fCallBack3 | `float` |
| tagEffTaskParam | 0x18 | fCallBack3PX | `float` |
| tagEffTaskParam | 0x1c | fCallBack3PY | `float` |
| tagEffTaskParam | 0x20 | fSoundIndex3 | `float` |
| tagEffTaskParam | 0x24 | fCallBack3PZ | `float` |
| tagEffTaskParam | 0x28 | fSoundStartTime3 | `float` |
| tagEffTaskParam | 0x2c | fSoundIndex4 | `float` |
| tagEffTaskParam | 0x30 | fSoundStartTime4 | `float` |
| tagEffTaskParam | 0x34 | fRotSpeed | `float` |
| tagEffTaskParam | 0x38 | fCallBack4 | `float` |
| tagEffTaskParam | 0x3c | fExplosionTime | `float` |
| tagEffTaskParam | 0x4 | fTrackSpeed | `float` |
| tagEffTaskParam | 0x40 | fCallBack4PY | `float` |
| tagEffTaskParam | 0x44 | fCallBack4PZ | `float` |
| tagEffTaskParam | 0x48 | fStartTime | `float` |
| tagEffTaskParam | 0x4c | fExpectTime | `float` |
| tagEffTaskParam | 0x50 | nBladeTime | `int` |
| tagEffTaskParam | 0x54 | fZStretchSpeed | `float` |
| tagEffTaskParam | 0x58 | bValid | `BYTE` |
| tagEffTaskParam | 0x59 | bGetBackOldTimeScale | `BYTE` |
| tagEffTaskParam | 0x5a | bModifyStartTimeScale | `BYTE` |
| tagEffTaskParam | 0x5c | fTargetRot | `float` |
| tagEffTaskParam | 0x60 | dwActKey | `DWORD` |
| tagEffTaskParam | 0x64 | dwRoleKey | `DWORD` |
| tagEffTaskParam | 0x68 | fReseved | `float[5]` |
| tagEffTaskParam | 0x8 | fQuakeFre | `float` |
| tagEffTaskParam | 0xc | fSoundStartTime2 | `float` |
| tagEntry | 0x0 | sizeFront | `int` |
| tagEntry | 0x4 | pEntryNext | `tagEntry *` |
| tagEntry | 0x8 | pEntryPrev | `tagEntry *` |
| tagEntryEnd | 0x0 | sizeBack | `int` |
| tagExplosive | 0x0 | vecSpeed | `gbVec3D` |
| tagExplosive | 0xc | vecRot | `gbVec3D` |
| tagFightScriptData | 0x164 | bLoaded | `char` |
| tagFightScriptData | 0x168 | pScriptData | `char[152]` |
| tagFormationSceneState | 0x1c8 | m_pCurrentScript | `PalScript *` |
| tagFormationSceneState | 0x1cc | m_bFormationReady | `_BYTE` |
| tagFormationSceneState | 0x1cd | m_nSceneTransitionParam | `_BYTE` |
| tagFormationSceneState | 0x1d0 | _todo_35c | `int` |
| tagFormationSceneState | 0x1d4 | _todo_360 | `int` |
| tagFormationSceneState | 0x1dc | m_fFadeTimer | `float` |
| tagFormationSceneState | 0x1e0 | _todo_36c | `int` |
| tagFormationSceneState | 0x244 | m_szSceneUIText | `char[256]` |
| tagFormationSceneState | 0x35c | _todo_4e8 | `int` |
| tagGroup | 0x0 | cntEntries | `int` |
| tagGroup | 0x4 | listHead | `tagListHead[64]` |
| tagHeader | 0x0 | bitvEntryHi | `UINT` |
| tagHeader | 0x10 | pRegion | `tagRegion *` |
| tagHeader | 0x4 | bitvEntryLo | `UINT` |
| tagHeader | 0x8 | bitvCommit | `UINT` |
| tagHeader | 0xc | pHeapData | `char *` |
| tagImbibeNimbus | 0x0 | mNimbus | `UIStatic *` |
| tagImbibeNimbus | 0x14 | mPos | `tagPOINT` |
| tagImbibeNimbus | 0x1c | bAlive | `BYTE` |
| tagImbibeNimbus | 0x20 | mAccelerate | `float` |
| tagImbibeNimbus | 0x24 | mFX | `float` |
| tagImbibeNimbus | 0x28 | mFY | `float` |
| tagImbibeNimbus | 0x4 | mNimbustype | `ECBFiveNimbus` |
| tagImbibeNimbus | 0x8 | mVelocity | `gbVec3D` |
| tagKBDLLHOOKSTRUCT | 0x0 | vkCode | `unsigned int` |
| tagKBDLLHOOKSTRUCT | 0x10 | dwExtraInfo | `unsigned int` |
| tagKBDLLHOOKSTRUCT | 0x4 | scanCode | `unsigned int` |
| tagKBDLLHOOKSTRUCT | 0x8 | flags | `unsigned int` |
| tagKBDLLHOOKSTRUCT | 0xc | time | `unsigned int` |
| tagLVCOLUMNA | 0x0 | mask | `unsigned int` |
| tagLVCOLUMNA | 0x10 | cchTextMax | `int` |
| tagLVCOLUMNA | 0x14 | iSubItem | `int` |
| tagLVCOLUMNA | 0x18 | iImage | `int` |
| tagLVCOLUMNA | 0x1c | iOrder | `int` |
| tagLVCOLUMNA | 0x4 | fmt | `int` |
| tagLVCOLUMNA | 0x8 | cx | `int` |
| tagLVCOLUMNA | 0xc | pszText | `char *` |
| tagLVITEMA | 0x0 | mask | `unsigned int` |
| tagLVITEMA | 0x10 | stateMask | `unsigned int` |
| tagLVITEMA | 0x14 | pszText | `char *` |
| tagLVITEMA | 0x18 | cchTextMax | `int` |
| tagLVITEMA | 0x1c | iImage | `int` |
| tagLVITEMA | 0x20 | lParam | `long` |
| tagLVITEMA | 0x24 | iIndent | `int` |
| tagLVITEMA | 0x4 | iItem | `int` |
| tagLVITEMA | 0x8 | iSubItem | `int` |
| tagLVITEMA | 0xc | state | `unsigned int` |
| tagListHead | 0x0 | pEntryNext | `tagEntry *` |
| tagListHead | 0x4 | pEntryPrev | `tagEntry *` |
| tagLoggerCallback | 0x0 | szName | `char[32]` |
| tagLoggerCallback | 0x20 | szDesc | `char[100]` |
| tagLoggerCallback | 0x84 | pfn | `int *` |
| tagMeteor | 0x0 | vecPos | `gbVec3D` |
| tagMeteor | 0x18 | vecASpeed | `gbVec3D` |
| tagMeteor | 0x24 | vecTarget | `gbVec3D` |
| tagMeteor | 0xc | vecSpeed | `gbVec3D` |
| tagMeteorNode | 0x0 | vecPos | `gbVec3D` |
| tagMeteorNode | 0x10 | fWidth | `float` |
| tagMeteorNode | 0x14 | fTime | `float` |
| tagMeteorNode | 0x18 | bVisible | `BYTE` |
| tagMeteorNode | 0x1c | pLast | `tagMeteorNode *` |
| tagMeteorNode | 0x20 | pNext | `tagMeteorNode *` |
| tagMeteorNode | 0xc | fLum | `float` |
| tagNMHDR | 0x0 | hwndFrom | `HWND__ *` |
| tagNMHDR | 0x4 | idFrom | `unsigned int` |
| tagNMHDR | 0x8 | code | `unsigned int` |
| tagNMITEMACTIVATE | 0x0 | hdr | `tagNMHDR` |
| tagNMITEMACTIVATE | 0x10 | iSubItem | `int` |
| tagNMITEMACTIVATE | 0x14 | uNewState | `unsigned int` |
| tagNMITEMACTIVATE | 0x18 | uOldState | `unsigned int` |
| tagNMITEMACTIVATE | 0x1c | uChanged | `unsigned int` |
| tagNMITEMACTIVATE | 0x20 | ptAction | `tagPOINT` |
| tagNMITEMACTIVATE | 0x28 | lParam | `long` |
| tagNMITEMACTIVATE | 0x2c | uKeyFlags | `unsigned int` |
| tagNMITEMACTIVATE | 0xc | iItem | `int` |
| tagNewItem | 0x0 | dwItemID | `DWORD` |
| tagNewItem | 0x4 | fnHP | `int (__thiscall *)(void *, unsigned int)` |
| tagNewItem | 0x8 | fnGP | `int (__thiscall *)(void *, unsigned long)` |
| tagNewItem | 0xc | fnMP | `float` |
| tagPALETTEENTRY | 0x0 | peRed | `unsigned char` |
| tagPALETTEENTRY | 0x1 | peGreen | `unsigned char` |
| tagPALETTEENTRY | 0x2 | peBlue | `unsigned char` |
| tagPALETTEENTRY | 0x3 | peFlags | `unsigned char` |
| tagParam | 0x0 | f1 | `float` |
| tagParam | 0x4 | f2 | `float` |
| tagParam | 0x8 | f3 | `float` |
| tagPartical | 0x0 | pPic | `char *` |
| tagPartical | 0x10 | fFramePerSec | `float` |
| tagPartical | 0x14 | fCurFrame | `float` |
| tagPartical | 0x18 | dwColor | `DWORD` |
| tagPartical | 0x1c | fX | `float` |
| tagPartical | 0x20 | fY | `float` |
| tagPartical | 0x24 | fZ | `float` |
| tagPartical | 0x28 | fSize | `float` |
| tagPartical | 0x2c | byAlpha | `BYTE` |
| tagPartical | 0x4 | nQuadIndex | `int` |
| tagPartical | 0x8 | bValid | `BYTE` |
| tagPartical | 0x9 | bVisible | `BYTE` |
| tagPartical | 0xa | bAniFrame | `BYTE` |
| tagPartical | 0xb | bBillBoard | `BYTE` |
| tagPartical | 0xc | byMaxFrame | `BYTE` |
| tagPartical | 0xd | byFrameIndex | `BYTE` |
| tagPartical | 0xe | byLoops | `BYTE` |
| tagPartical | 0xf | byMaxLoops | `BYTE` |
| tagPartyInitView | 0x0 | _gap_50814 | `_BYTE[2]` |
| tagPartyInitView | 0x2 | m_partyInitData | `int[100]` |
| tagPlayerSet | 0x0 | LastRoleCmd | `tagCmdData` |
| tagPlayerSet | 0x2c | nMagicDefaultPage | `int` |
| tagPlayerSet | 0x30 | nItemDefaultPage | `int` |
| tagQuad | 0x0 | nGeomQuad | `int` |
| tagQuad | 0x10 | fX | `float` |
| tagQuad | 0x14 | fY | `float` |
| tagQuad | 0x18 | fZ | `float` |
| tagQuad | 0x1c | fXSize | `float` |
| tagQuad | 0x20 | fYSize | `float` |
| tagQuad | 0x24 | fPX | `float` |
| tagQuad | 0x28 | fPY | `float` |
| tagQuad | 0x2c | fPZ | `float` |
| tagQuad | 0x30 | fRotation | `float` |
| tagQuad | 0x34 | fRotX | `float` |
| tagQuad | 0x38 | fRotZ | `float` |
| tagQuad | 0x3c | fAlpha | `float` |
| tagQuad | 0x4 | bValid | `BYTE` |
| tagQuad | 0x40 | fRed | `float` |
| tagQuad | 0x44 | fGreen | `float` |
| tagQuad | 0x48 | fBlue | `float` |
| tagQuad | 0x4c | dwColor | `DWORD` |
| tagQuad | 0x5 | bVisible | `BYTE` |
| tagQuad | 0x6 | byFrame | `BYTE` |
| tagQuad | 0x7 | byLoops | `BYTE` |
| tagQuad | 0x8 | fFramePerSec | `float` |
| tagQuad | 0xc | fCurFrame | `float` |
| tagRGBQUAD | 0x0 | rgbBlue | `BYTE` |
| tagRGBQUAD | 0x1 | rgbGreen | `BYTE` |
| tagRGBQUAD | 0x2 | rgbRed | `BYTE` |
| tagRGBQUAD | 0x3 | rgbReserved | `BYTE` |
| tagRegion | 0x0 | indGroupUse | `int` |
| tagRegion | 0x144 | grpHeadList | `char[256]` |
| tagRegion | 0x4 | cntRegionSize | `char[64]` |
| tagRegion | 0x44 | bitvGroupHi | `unsigned int[32]` |
| tagRegion | 0xc4 | bitvGroupLo | `unsigned int[32]` |
| tagRoleActionState | 0x1 | _todo_18D | `_BYTE` |
| tagRoleActionState | 0x180 | m_nDialogData | `short` |
| tagRoleActionState | 0x190 | m_nEmoteParam | `int` |
| tagRoleActionState | 0x194 | m_nScreenWidth | `int` |
| tagRoleActionState | 0x1e0 | m_EncampSound | `int` |
| tagRoleActionState | 0x24 | _todo_1B0 | `int` |
| tagRoleActionState | 0x240 | m_CamFocusData | `int` |
| tagRoleActionState | 0x284 | m_nDialogResult | `int` |
| tagRoleActionState | 0x288 | m_DialogByte | `_BYTE` |
| tagRoleActionState | 0x2dc | _todo_468 | `int` |
| tagRoleActionState | 0x34 | m_bRoleAction | `int` |
| tagRoleActionState | 0x36c | m_nPathState | `int` |
| tagRoleActionState | 0x370 | m_nOverlapId | `int` |
| tagRoleActionState | 0x374 | _todo_500 | `int` |
| tagRoleActionState | 0x37c | _todo_508 | `int` |
| tagRoleActionState | 0x48 | m_RoleActionType | `_BYTE` |
| tagRoleActionState | 0x4c | _todo_1B8 | `float` |
| tagRoleActionState | 0x54 | _todo_01E0 | `float` |
| tagRoleActionState | 0x58 | _todo_1C4 | `float` |
| tagRoleActionState | 0x5c | _todo_1C8 | `float` |
| tagRoleActionState | 0x60 | _todo_1CC | `float` |
| tagRoleActionState | 0x64 | _todo_1D0 | `float` |
| tagRoleActionState | 0x68 | _todo_1F4 | `float` |
| tagRoleActionState | 0x6c | _todo_1F8 | `float` |
| tagRoleActionState | 0x70 | _todo_1FC | `float` |
| tagRoleActionState | 0x74 | m_nLoadFromFile | `int` |
| tagRoleActionState | 0x78 | m_nLoadState | `int` |
| tagRoleActionState | 0x7c | m_nNext | `int` |
| tagRoleActionState | 0x80 | m_DialogTemplate | `int` |
| tagRoleActionState | 0x84 | m_nConfigIndex | `int` |
| tagRoleActionState | 0x88 | m_SceneConfig | `int` |
| tagRoleActionState | 0x8c | m_SceneCfg_flags1 | `int` |
| tagRoleActionState | 0x90 | m_SceneCfg_fParam0 | `float` |
| tagRoleActionState | 0x94 | m_SceneCfg_nParam0 | `int` |
| tagRoleActionState | 0x98 | m_SceneCfg_nParam1 | `int` |
| tagRoleActionState | 0x9c | m_SceneCfg_nParam2 | `int` |
| tagRoleActionState | 0xa0 | m_SceneCfg_data | `int` |
| tagRoleActionState | 0xa4 | m_fSceneCfg | `float[48]` |
| tagRoleSlot | 0x0 | nRoleID | `unsigned short` |
| tagRoleState | 0x0 | dwID | `DWORD` |
| tagRoleState | 0x18 | byUIIndex | `BYTE` |
| tagRoleState | 0x19 | bValid | `BYTE` |
| tagRoleState | 0x1a | bAlive | `BYTE` |
| tagRoleState | 0x1ac | bMagicMastered | `unsigned char[9][6]` |
| tagRoleState | 0x1b | bFriend | `BYTE` |
| tagRoleState | 0x1c | bBoss | `BYTE` |
| tagRoleState | 0x1d | bCanAction | `BYTE` |
| tagRoleState | 0x1e | bWaitForFlee | `BYTE` |
| tagRoleState | 0x1e2 | byMagicUseTime | `unsigned short[9][6]` |
| tagRoleState | 0x1f | bEnemyFriend | `BYTE` |
| tagRoleState | 0x20 | nLevel | `int` |
| tagRoleState | 0x24 | nHP | `int` |
| tagRoleState | 0x28 | nFullHP | `int` |
| tagRoleState | 0x2c | nGP | `int` |
| tagRoleState | 0x30 | pCCBSystem | `CCBSystem *` |
| tagRoleState | 0x34 | nMP | `CCBStage *` |
| tagRoleState | 0x38 | nFullMP | `int` |
| tagRoleState | 0x3c | nAttack | `int` |
| tagRoleState | 0x4 | nIndex | `int` |
| tagRoleState | 0x40 | nDefence | `int` |
| tagRoleState | 0x44 | nSpeed | `int` |
| tagRoleState | 0x48 | nLuck | `int` |
| tagRoleState | 0x4c | nLove | `int` |
| tagRoleState | 0x50 | nMoney | `int` |
| tagRoleState | 0x54 | nProtectRole | `int` |
| tagRoleState | 0x58 | dwAttackMode | `DWORD` |
| tagRoleState | 0x5c | nGPInc | `int` |
| tagRoleState | 0x60 | byWeaponType | `BYTE` |
| tagRoleState | 0x61 | bAttackRow | `BYTE` |
| tagRoleState | 0x62 | bAttackColumn | `BYTE` |
| tagRoleState | 0x63 | bAttackAll | `BYTE` |
| tagRoleState | 0x64 | bMagicSword | `BYTE` |
| tagRoleState | 0x68 | fGPCostDec | `float` |
| tagRoleState | 0x6c | fMPCostDec | `float` |
| tagRoleState | 0x70 | fPunchPowerInc | `float` |
| tagRoleState | 0x74 | fSkillCentInc | `float` |
| tagRoleState | 0x78 | fHPIncPerRound | `float` |
| tagRoleState | 0x7c | fGPIncPerRound | `float` |
| tagRoleState | 0x8 | sModel | `char[16]` |
| tagRoleState | 0x80 | fGPIncPerRoundBak | `float` |
| tagRoleState | 0x84 | fMPIncPerRound | `float` |
| tagRoleState | 0x88 | fEXPIncPerCombat | `float` |
| tagRoleState | 0x8c | fMoneyIncPerCombat | `float` |
| tagRoleState | 0x90 | fRecoverItemPowerInc | `float` |
| tagRoleState | 0x94 | nStealCent | `int` |
| tagRoleState | 0x98 | bLostMoneyGetLife | `BYTE` |
| tagRoleState | 0x99 | bMirror | `BYTE` |
| tagRoleState | 0x9c | nEXP | `int` |
| tagRoleState | 0xa0 | nCombatEXP | `int` |
| tagRoleState | 0xa4 | dwSkillID | `unsigned int[9]` |
| tagRoleState | 0xc8 | bSkillMastered | `unsigned char[9]` |
| tagRoleState | 0xd4 | dwMagicID | `unsigned int[9][6]` |
| tagRoleSystemData | 0x118 | _todo_118 | `float` |
| tagRoleSystemData | 0x168 | _todo_168 | `int` |
| tagRoleSystemData | 0x190 | _todo_190 | `int` |
| tagRoleSystemData | 0x64 | _todo_064 | `int` |
| tagRoleTask | 0x0 | fp | `char *[4]` |
| tagRoleTask | 0x1c | cmd | `tagCmdData` |
| tagRoleTask | 0x48 | fTemp | `float` |
| tagRoleTask | 0x4c | fTemp2 | `float` |
| tagRoleTask | 0x50 | dwID | `DWORD` |
| tagRoleTask | 0x54 | eMode | `ECBRoleTaskMode` |
| tagRoleTask | 0x58 | bValid | `BYTE` |
| tagRoleTask | 0x59 | bFinished | `BYTE` |
| tagRoleTask | 0x5a | bExecuted | `BYTE` |
| tagRoleTaskData | 0x0 | nStatus | `int` |
| tagRoleTaskData | 0x10 | pRoleState | `void *` |
| tagRoleTaskData | 0x18 | _gap_18 | `char[48]` |
| tagRoleTaskData | 0x8 | nActionType | `int` |
| tagRoleTaskSlotsView | 0x0 | pLayout | `CCBRoleState *` |
| tagRoleTaskSlotsView | 0x4 | pToggle | `PlayerMgr *` |
| tagRoleTaskSlotsView | 0x8 | _pad | `float` |
| tagRoleTaskVec3View | 0x0 | x | `float` |
| tagRoleTaskVec3View | 0x4 | y | `float` |
| tagRoleTaskVec3View | 0x8 | z | `float` |
| tagScriptCmd | 0x0 | cmd_id | `short` |
| tagScriptCmd | 0x4 | handler | `int` |
| tagScriptCmd | 0x8 | param | `int` |
| tagScriptCmd | 0xc | flags | `int` |
| tagScriptPtrQuad | 0x8c | pScriptVtable | `void *` |
| tagScriptPtrQuad | 0x94 | pScriptPtrA | `void *` |
| tagScriptPtrQuad | 0x98 | pScriptPtrB | `void *` |
| tagScriptPtrQuad | 0xa0 | pScriptPtrC | `void *` |
| tagShockUnit | 0x0 | fRequireLoops | `float` |
| tagShockUnit | 0x4 | fCurFrame | `float` |
| tagShowItem | 0x0 | eKind | `ECBShowItemKind` |
| tagShowItem | 0x104 | color | `tagRGBQUAD` |
| tagShowItem | 0x108 | fX | `float` |
| tagShowItem | 0x10c | fY | `float` |
| tagShowItem | 0x110 | fZ | `float` |
| tagShowItem | 0x114 | fSize | `float` |
| tagShowItem | 0x4 | sTxt | `char[256]` |
| tagSkillCountBlock | 0x122 | nSkillCount1 | `int` |
| tagSkillCountBlock | 0x126 | nSkillCount2 | `int` |
| tagStageRoleData | 0x1c | m_nLoadLinkerParams | `int[4]` |
| tagStageRoleData | 0x2c | m_nSetAliveParams | `int[4]` |
| tagStageRoleData | 0x3c | m_nSetVisibleParams | `int[4]` |
| tagStageRoleData | 0x4c | m_nOnChangeActionParams | `int[4]` |
| tagStageRoleData | 0x6c | _todo_06C | `float` |
| tagStageRoleData | 0x74 | _todo_074 | `float` |
| tagStageRoleData | 0x88 | m_fRoleTargetParam | `int` |
| tagStageSubTask | 0x0 | fp | `char *[4]` |
| tagStageSubTask | 0x10 | eStats | `ECBStageTaskState` |
| tagStageSubTask | 0x14 | dwID | `DWORD` |
| tagStageSubTask | 0x18 | fStartTime | `float` |
| tagStageSubTask | 0x1c | fWaitTime | `float` |
| tagStageSubTask | 0x20 | fTime | `float` |
| tagStageSubTask | 0x24 | dwReturn | `DWORD` |
| tagStageSubTask | 0x28 | bValid | `BYTE` |
| tagStageSubTask | 0x29 | bExecuted | `BYTE` |
| tagStageSubTask | 0x2a | bAction | `BYTE` |
| tagStageSubTask | 0x2b | bRequireToEnd | `BYTE` |
| tagStageSubTask | 0x2c | param | `tagParam` |
| tagStageSubTask | 0x38 | nEffLinker | `int` |
| tagStageSubTask | 0x3c | bEff1Started | `BYTE` |
| tagStageSubTask | 0x3d | bEff2Started | `BYTE` |
| tagStageSubTask | 0x3e | bEffWorked | `BYTE` |
| tagStageSubTask | 0x40 | fTemp1 | `float` |
| tagStageSubTask | 0x44 | fTemp2 | `float` |
| tagStageSubTask | 0x48 | fTemp3 | `float` |
| tagStageSubTask | 0x4c | fTemp4 | `float` |
| tagStageTask | 0x0 | eTask | `ECBStageTask` |
| tagStageTask | 0x10 | SubTask | `tagStageSubTask[32]` |
| tagStageTask | 0x4 | eStats | `ECBStageTaskState` |
| tagStageTask | 0x8 | nSubTask | `int` |
| tagStageTask | 0xa10 | dwID | `DWORD` |
| tagStageTask | 0xa14 | dwReturn | `DWORD` |
| tagStageTask | 0xa18 | cmd | `tagCmdData` |
| tagStageTask | 0xa44 | bValid | `BYTE` |
| tagStageTask | 0xa45 | bAutoDel | `BYTE` |
| tagStageTask | 0xc | nReserved | `int` |
| tagTCITEMA | 0x0 | mask | `unsigned int` |
| tagTCITEMA | 0x10 | cchTextMax | `int` |
| tagTCITEMA | 0x14 | iImage | `int` |
| tagTCITEMA | 0x18 | lParam | `long` |
| tagTCITEMA | 0x4 | dwState | `unsigned int` |
| tagTCITEMA | 0x8 | dwStateMask | `unsigned int` |
| tagTCITEMA | 0xc | pszText | `char *` |
| tagTaskLayoutPtrs | 0x0 | pLayout | `CCBRoleState *` |
| tagTaskLayoutPtrs | 0x4 | pToggle | `PlayerMgr *` |
| tagTaskLayoutPtrs | 0x8 | _pad | `float` |
| tagTaskSlotHeader | 0x0 | pRoleTaskData | `void *` |
| tagTaskSlotHeader | 0x4 | nTaskCount | `int` |
| tagTaskVecXYZ | 0x0 | x | `float` |
| tagTaskVecXYZ | 0x4 | y | `float` |
| tagTaskVecXYZ | 0x8 | z | `float` |
| tagTeamSlotsBOverlay | 0x224 | m_nCombatViewMode | `int` |
| tagTeamSlotsBOverlay | 0x228 | dwInitParam | `HWND` |
| tagTeamSlotsBOverlay | 0x22c | g_hCombatDlg1 | `HWND` |
| tagTeamSlotsBOverlay | 0x230 | g_hCombatDlg2 | `HWND` |
| tagTeamSlotsBOverlay | 0x234 | m_nActorRenderCount | `int` |
| tagTeamSlotsBOverlay | 0x238 | g_hCBStageCamDlg | `HWND` |
| tagTeamSlotsBOverlay | 0x23e | m_bWPARAM | `unsigned char` |
| tagTeamSlotsBOverlay | 0x254 | m_nCCBUISelectedRole | `int` |
| tagTeamSlotsBOverlay | 0x258 | m_nCCBUIIdx | `int` |
| tagTeamSlotsBOverlay | 0x25e | m_bCommandEdited | `unsigned char` |
| tagThread | 0x0 | fp | `char *[4]` |
| tagThread | 0x10 | dwID | `DWORD` |
| tagThread | 0x14 | nTaskIndex | `int` |
| tagThread | 0x18 | dwTaskID | `DWORD` |
| tagThread | 0x1c | dwReturn | `DWORD` |
| tagThread | 0x20 | nTemp | `int` |
| tagThread | 0x24 | bValid | `BYTE` |
| tagThread | 0x25 | bExecuted | `BYTE` |
| tagThread | 0x28 | cmd | `tagCmdData` |
| tagUIParam | 0x0 | pUI | `UIWnd *` |
| tagUIParam | 0x10 | fEndY | `float` |
| tagUIParam | 0x14 | fSpeed | `float` |
| tagUIParam | 0x18 | fEnergy | `int` |
| tagUIParam | 0x1c | nTimes | `int` |
| tagUIParam | 0x4 | fFromX | `float` |
| tagUIParam | 0x8 | fFromY | `float` |
| tagUIParam | 0xc | fEndX | `float` |
| tagUITask | 0x0 | fp | `char *[4]` |
| tagUITask | 0x10 | bValid | `BYTE` |
| tagUITask | 0x11 | bExecuted | `BYTE` |
| tagUITask | 0x12 | bFinished | `BYTE` |
| tagUITask | 0x14 | dwID | `DWORD` |
| tagUITask | 0x18 | fStartTime | `float` |
| tagUITask | 0x1c | fExpectStartTime | `int` |
| tagUITask | 0x20 | fExpectEndTime | `float` |
| tagUITask | 0x24 | param | `tagUIParam` |
| tagUV | 0x0 | su | `float` |
| tagUV | 0x4 | sv | `float` |
| tagUV | 0x8 | eu | `float` |
| tagUV | 0xc | ev | `float` |
| tagUVSet | 0x0 | su | `float` |
| tagUVSet | 0x4 | sv | `float` |
| tagUVSet | 0x8 | eu | `float` |
| tagUVSet | 0xc | ev | `float` |
| tagVA | 0x0 | eKind | `ECBVAKind` |
| tagVA | 0x10 | nEnd | `int` |
| tagVA | 0x14 | bValid | `BYTE` |
| tagVA | 0x4 | nSrc | `int` |
| tagVA | 0x8 | nDest | `int` |
| tagVA | 0xc | nStart | `int` |
| tagVAF | 0x0 | nIndex | `int` |
| tagVAF | 0x18 | bValid | `BYTE` |
| tagVAF | 0x19 | bDecision | `BYTE` |
| tagVAF | 0x1a | bResult | `BYTE` |
| tagVAF | 0x1c | nAddonScore | `int` |
| tagVAF | 0x8 | fp | `char *[4]` |
| tagVAO | 0x0 | dwDataID | `DWORD` |
| tagVAO | 0x4 | nDataIndex | `int` |
| tagVAO | 0x8 | nScore | `int` |
| tagVAO | 0xc | bValid | `BYTE` |
| util | 0x0 | Crc32Table | `unsigned int[256]` |
| util | 0x400 | m_dwIDHolder | `DWORD` |
| util | 0x404 | m_nRandHolder | `int` |
| util | 0x408 | m_nRandCallCount | `int` |
| util | 0x40c | m_pIniReader | `CIniFile *` |
| util | 0x410 | m_pLoader3DS | `CLoad3DS *` |
| vert | 0x0 | _texture | `char *[2]` |
| vert | 0x14 | _screen | `char *` |
| vert | 0x8 | _world | `char *[3]` |
| vertexalpha_particle_graph | 0x0 | _tail_000 | `char[5300]` |
| waveformat_tag | 0x0 | wFormatTag | `WORD` |
| waveformat_tag | 0x2 | nChannels | `WORD` |
| waveformat_tag | 0x4 | nSamplesPerSec | `DWORD` |
| waveformat_tag | 0x8 | nAvgBytesPerSec | `DWORD` |
| waveformat_tag | 0xc | nBlockAlign | `WORD` |
| wavehdr_tag | 0x0 | lpData | `char *` |
| wavehdr_tag | 0x10 | dwFlags | `DWORD` |
| wavehdr_tag | 0x14 | dwLoops | `DWORD` |
| wavehdr_tag | 0x18 | lpNext | `wavehdr_tag *` |
| wavehdr_tag | 0x1c | reserved | `DWORD` |
| wavehdr_tag | 0x4 | dwBufferLength | `DWORD` |
| wavehdr_tag | 0x8 | dwBytesRecorded | `DWORD` |
| wavehdr_tag | 0xc | dwUser | `DWORD` |

### 已解释（不计缺口）

| 解释类 | 数量 | 说明 |
|---|---|---|
| 基类区域成员 | 0 | 偏移 < base_size：IDB 只在基类声明，派生类不重复 |
| vptr 声明迁移 | 0 | `__vftable`/`_vftable` 归位 IDB `vtables`/`bases` 字段 |
| baseclass 声明迁移 | 1 | `baseclass*` 归位 IDB `bases` 字段 |

### baseclass 声明迁移（1）

| 类 | 偏移键 | 成员 |
|---|---|---|
| UIRoleDialog | 0x48 | baseclass2 |

## 3. 成员新增（导出有 · 注解缺）

export 侧合成补尾 `_tail_*`（102 个，合成填充非注解声明）：

| 类 | 偏移 | 名 | type |
|---|---|---|---|
| C3DSpark_tagSpark | 0 | _tail_000 | `char[56]` |
| CAccelCentripetalPolicy | 0 | _tail_000 | `char[4]` |
| CCentripetalPolicy | 0 | _tail_000 | `char[4]` |
| CDamplyCentripetalPolicy | 0 | _tail_000 | `char[4]` |
| CEffCamera | 0 | _tail_000 | `_BYTE[4]` |
| CEffMgr | 0 | _tail_000 | `char[43312]` |
| CEffTemplate | 0 | _tail_000 | `_BYTE[4]` |
| CEffTime | 0 | _tail_000 | `_BYTE[4]` |
| CEffectBubble | 0 | _tail_000 | `char[4]` |
| CEffectSimple | 0 | _tail_000 | `char[4]` |
| CFadeInAlphaPolicy | 0 | _tail_000 | `char[4]` |
| CFadeOutAlphaPolicy | 0 | _tail_000 | `char[4]` |
| CG_Scene_ArrayErase | 0 | _tail_000 | `char[4]` |
| CParticleSystem_ParticleAttribute | 0 | _tail_000 | `char[4]` |
| CParticleSystem_ParticleUnit | 0 | _tail_000 | `char[4]` |
| CRandomColorPolicy | 0 | _tail_000 | `char[4]` |
| CRenderTarget | 0 | _tail_000 | `char[4]` |
| CRenderTarget2 | 0 | _tail_000 | `char[4]` |
| CSimpleDirPolicy | 0 | _tail_000 | `char[4]` |
| CSimplePosPolicy | 0 | _tail_000 | `char[4]` |
| CameraSystem | 0 | _tail_000 | `char[4]` |
| Combat | 0 | _tail_000 | `char[4]` |
| DPINFO___unnamed | 0 | _tail_000 | `char[96]` |
| ECBRoleSpecState | 0 | _tail_000 | `char[4]` |
| EffAudioNode | 0 | _tail_000 | `char[32]` |
| EffBinkNode | 0 | _tail_000 | `char[32]` |
| EffCallBackNode | 0 | _tail_000 | `char[32]` |
| EffMultiPassNode | 0 | _tail_000 | `char[32]` |
| ExternalStatistics | 0 | _tail_000 | `char[4]` |
| GameObject | 0 | _tail_000 | `_BYTE[4]` |
| InputSystem | 0 | _tail_000 | `char[36]` |
| Iostream_init | 0 | _tail_000 | `char[4]` |
| Math | 0 | _tail_000 | `char[4]` |
| MatrixStack | 0 | _tail_000 | `char[4]` |
| MeshFxCreator | 0 | _tail_000 | `char[4]` |
| MiniGame1 | 0 | _tail_000 | `char[4]` |
| MiniGame2Scene | 0 | _tail_000 | `char[4]` |
| MiniGame3 | 0 | _tail_000 | `char[4]` |
| MvcController | 0 | _tail_000 | `char[4]` |
| MvcViewport | 0 | _tail_000 | `char[4]` |
| NameSys_NAMEFLAG | 0 | _tail_000 | `char[4]` |
| OpenSceneFile | 0 | _tail_000 | `char[4]` |
| ParabolaCalculator_PRBL_STATE | 0 | _tail_000 | `char[4]` |
| Parent_Data | 0 | _tail_000 | `char[4]` |
| ParticleVisNode | 0 | _tail_000 | `char[8]` |
| RenderTarget2 | 0 | _tail_000 | `char[4292]` |
| RenderTarget4 | 0 | _tail_000 | `char[4]` |
| RenderTargetNode | 0 | _tail_000 | `char[96]` |
| Role_SPECIAL_ACTION | 0 | _tail_000 | `char[36]` |
| SPECIAL_ACTION | 0 | _tail_000 | `char[4]` |
| SaleUI_SortData | 0 | _tail_000 | `char[4]` |
| SceneObj_Common_State | 0 | _tail_000 | `char[4]` |
| SceneObj_SubObj | 0 | _tail_000 | `char[36]` |
| SceneVisNode | 0 | _tail_000 | `char[8]` |
| ScriptHelper | 0 | _tail_000 | `char[4]` |
| ScriptObj | 0 | _tail_000 | `char[4]` |
| SoundContext | 0 | _tail_000 | `char[4]` |
| SoundSystem | 0 | _tail_000 | `char[4]` |
| String | 0 | _tail_000 | `char[4]` |
| TextureLib_Data | 0 | _tail_000 | `char[1116]` |
| TileMap | 0 | _tail_000 | `char[4]` |
| UIAnimCtrl | 0 | _tail_000 | `char[4]` |
| UIBase | 0 | _tail_000 | `char[4]` |
| UIBigDialog | 0 | _tail_000 | `char[4]` |
| UIButton_UIBUTTON_STATE | 0 | _tail_000 | `char[4]` |
| UIInventory | 0 | _tail_000 | `char[68]` |
| UIListView | 0 | _tail_000 | `char[4]` |
| UIManager | 0 | _tail_000 | `char[4]` |
| UIObj | 0 | _tail_000 | `char[4]` |
| UIParabolaCtrl | 0 | _tail_000 | `char[4]` |
| UIQuadManager | 0 | _tail_000 | `char[4]` |
| UIRenderObj | 0 | _tail_000 | `char[32]` |
| UISceneObj | 0 | _tail_000 | `char[4]` |
| UIScrollBar_SB_AREA | 0 | _tail_000 | `char[4]` |
| UISelectDialog | 0 | _tail_000 | `char[4]` |
| UISlider | 0 | _tail_000 | `char[4]` |
| UIStaticFlex_State | 0 | _tail_000 | `char[4]` |
| UISystem | 0 | _tail_000 | `char[4]` |
| VertPoolMgr | 0 | _tail_000 | `char[4]` |
| VideoPlayer | 0 | _tail_000 | `char[4]` |
| WeatherEffectNode | 0 | _tail_000 | `char[8]` |
| _Console__ConCmd | 0 | _tail_000 | `char[136]` |
| collision | 0 | _tail_000 | `char[4]` |
| direction_emitter_graph | 0 | _tail_000 | `char[5300]` |
| elelife_emitter_graph | 0 | _tail_000 | `char[5300]` |
| elerandvec_emitter_graph | 0 | _tail_000 | `char[5300]` |
| emissionrate_emitter_graph | 0 | _tail_000 | `char[5300]` |
| gbFileStream | 0 | _tail_000 | `char[4]` |
| gbMeshData | 0 | _tail_000 | `char[4]` |
| gbRenderEffect_D3D | 0 | _tail_000 | `char[4]` |
| gbSceneNode | 0 | _tail_000 | `char[4]` |
| gbSingleton_gbGfxManager | 0 | _tail_000 | `char[4]` |
| gbVolumeModifier | 0 | _tail_000 | `char[4]` |
| rgbcolor_particle_graph | 0 | _tail_000 | `char[5300]` |
| rotation_particle_graph | 0 | _tail_000 | `char[5300]` |
| rotmulti_emitter_graph | 0 | _tail_000 | `char[5300]` |
| scScriptInstance | 0 | _tail_000 | `_BYTE[68]` |
| size_particle_graph | 0 | _tail_000 | `char[5300]` |
| sizemulti_emitter_graph | 0 | _tail_000 | `char[5300]` |
| tagEffClass | 0 | _tail_000 | `char[4]` |
| tagEffMgrData | 0 | _tail_000 | `char[1500]` |
| vertexalpha_particle_graph | 0 | _tail_000 | `char[5300]` |

非合成补尾的新增（8988 个）：

| 类 | 偏移 | 名 | type |
|---|---|---|---|
| ARC_ArcBrief | 0 | gametime | `float` |
| ARC_ArcBrief | 4 | inteam | `_BYTE[5]` |
| ARC_ArcBrief | 9 | scenename | `char[64]` |
| ARC_ArcBrief | 76 | money | `int` |
| ARC_ArcHeader | 0 | magic | `char[4]` |
| ARC_ArcHeader | 4 | ver | `BYTE` |
| ARC_ArcHeader | 8 | reverse | `unsigned int[16]` |
| ARC_ArcHeader | 72 | brief | `ARC_ArcBrief` |
| ARC_ArcHeader | 152 | localeOffset | `unsigned int` |
| ARC_ArcHeader | 156 | playerOffset | `unsigned int` |
| ARC_ArcHeader | 160 | scriptOffset | `unsigned int` |
| ARC_ArcHeader | 164 | sceneOffset | `unsigned int` |
| ARC_ArcHeader | 168 | soundOffset | `unsigned int` |
| ARC_ArcHeader | 172 | miscOffset | `unsigned int` |
| ARC_ArcHeader | 176 | mapOffset | `unsigned int[2]` |
| ARC_ArcHeader | 184 | pastOffset | `unsigned int` |
| ARC_ArcHeader | 188 | npcOffset | `unsigned int` |
| ARC_ArcHeader | 192 | reverseOffset | `unsigned int[7]` |
| ARC_ArcLocaleRole | 0 | active | `BYTE` |
| ARC_ArcLocaleRole | 1 | offset | `_BYTE[27]` |
| ARC_ArcMsic | 0 | byte6forwishPool | `_BYTE[12]` |
| ARC_ArcMsic | 12 | m_isPurged | `_BYTE[5][2]` |
| ARC_ArcMsic | 22 | m_isAllPurged | `_BYTE[5]` |
| ARC_ArcMsic | 28 | m_totalNum | `int` |
| ARC_ArcMsic | 32 | m_isyjfx | `BYTE` |
| ARC_ArcMsic | 33 | m_ComSkill | `_BYTE[8][5]` |
| ARC_ArcMsic | 73 | m_SDTY | `BYTE` |
| ARC_ArcMsic | 74 | m_APPR | `BYTE` |
| ARC_ArcMsic | 75 | m_SKEE | `BYTE` |
| ARC_ArcMsic | 76 | m_isSword | `unsigned int` |
| ARC_ArcMsic | 80 | m_isJusticeBook | `unsigned int` |
| ARC_ArcMsic | 84 | g_dwWeaponWU | `int` |
| ARC_ArcMsic | 88 | m_bigMapElement | `_BYTE[40]` |
| ARC_ArcMsic | 128 | g_nWolfCounter | `unsigned int` |
| ARC_ArcMsic | 132 | com_quantum | `float[5][8]` |
| ARC_ArcMsic | 292 | m_PurgeNum | `ARC_WuLing` |
| ARC_ArcMsic | 296 | byteoffset | `_BYTE[256]` |
| ARC_ComboAttack | 0 | name | `char[32]` |
| ARC_ComboAttack | 32 | id | `unsigned int` |
| ARC_ComboAttack | 36 | man | `unsigned int[4]` |
| ARC_ComboAttack | 52 | pos | `_BYTE[4]` |
| ARC_ComboAttack | 56 | skill | `unsigned int` |
| ARC_ComboAttack | 60 | WeaponType | `_BYTE[4]` |
| ARC_ComboAttack | 64 | Range | `BYTE` |
| ARC_ComboAttack | 68 | state | `FightState[3]` |
| ARC_ComboAttack | 80 | Remark | `char[512]` |
| ARC_ComboAttack | 592 | fanwei | `BYTE` |
| ARC_ComboAttack | 593 | rvtype | `_BYTE[12]` |
| ARC_ComboAttack | 606 | rolevalue | `signed __int16[12]` |
| ARC_FightItem | 0 | id | `unsigned int` |
| ARC_FightItem | 4 | name | `char[32]` |
| ARC_FightItem | 36 | ModelID | `char[30]` |
| ARC_FightItem | 66 | ImageID | `char[30]` |
| ARC_FightItem | 96 | desc | `char[512]` |
| ARC_FightItem | 608 | price | `int` |
| ARC_FightItem | 612 | type | `BYTE` |
| ARC_FightItem | 613 | weapontype | `BYTE` |
| ARC_FightItem | 614 | user | `_BYTE[5]` |
| ARC_FightItem | 619 | att | `_BYTE[5]` |
| ARC_FightItem | 624 | gu | `int` |
| ARC_FightItem | 628 | special | `BYTE` |
| ARC_FightItem | 629 | fanwei | `BYTE` |
| ARC_FightItem | 630 | space | `BYTE` |
| ARC_FightItem | 631 | rvtype | `_BYTE[12]` |
| ARC_FightItem | 644 | rolevalue | `signed __int16[12]` |
| ARC_FightItem | 668 | fstype | `_BYTE[31]` |
| ARC_FightItem | 700 | fightstate | `signed __int16[31]` |
| ARC_FightItem | 764 | lian | `int` |
| ARC_FightItem | 768 | saveqi | `signed __int16` |
| ARC_FightItem | 770 | saveshen | `signed __int16` |
| ARC_FightItem | 772 | addbaoji | `signed __int16` |
| ARC_FightItem | 774 | addteji | `signed __int16` |
| ARC_FightItem | 776 | stone | `unsigned int` |
| ARC_FightItem | 780 | make | `unsigned int` |
| ARC_FightItem | 784 | smeltPrice | `int` |
| ARC_FightItem | 788 | hecheng | `unsigned int[2]` |
| ARC_FightItem | 796 | make2 | `unsigned int` |
| ARC_FightSkill | 0 | id | `unsigned int` |
| ARC_FightSkill | 4 | type | `BYTE` |
| ARC_FightSkill | 8 | att | `int[5]` |
| ARC_FightSkill | 28 | name | `char[32]` |
| ARC_FightSkill | 60 | desc | `char[512]` |
| ARC_FightSkill | 572 | user | `_BYTE[5]` |
| ARC_FightSkill | 577 | fanwei | `BYTE` |
| ARC_FightSkill | 578 | special | `BYTE` |
| ARC_FightSkill | 579 | rvtype | `_BYTE[12]` |
| ARC_FightSkill | 592 | rolevalue | `signed __int16[12]` |
| ARC_FightSkill | 616 | succ | `BYTE` |
| ARC_FightSkill | 618 | fs | `signed __int16[31]` |
| ARC_FightSkill | 680 | consumervtype | `int[2]` |
| ARC_FightSkill | 688 | consumetype | `int[3]` |
| ARC_FightSkill | 700 | tutype | `BYTE` |
| ARC_FightSkill | 704 | tusuval | `int` |
| ARC_FightSkill | 708 | lv | `BYTE` |
| ARC_FightSkill | 709 | lvup | `_BYTE[4]` |
| ARC_FightSkill | 713 | rolelv | `BYTE` |
| ARC_FightSkill | 714 | magiclv | `BYTE` |
| ARC_FightSkill | 716 | nextid | `unsigned int` |
| ARC_FightSkill | 720 | isuseall | `BYTE` |
| ARC_FightSkill | 724 | hecheng | `unsigned int[3]` |
| ARC_FightSkill | 736 | heskill | `unsigned int[3]` |
| ARC_FightSkill | 748 | helv | `_BYTE[3]` |
| ARC_FightSkill | 751 | helvself | `_BYTE[3]` |
| ARC_FightSkill | 754 | manlv | `_BYTE[3]` |
| ARC_FightSkill | 757 | heji | `BYTE` |
| ARC_Inventory | 0 | m_items | `char[16]` |
| ARC_Inventory | 16 | m_curtype | `int` |
| ARC_Inventory | 20 | m_typeitems | `char[16]` |
| ARC_Inventory | 36 | m_money | `int` |
| ARC_MonsterStar | 0 | needexp | `int` |
| ARC_MonsterStar | 4 | active | `int` |
| ARC_MonsterStar | 8 | exp | `int` |
| ARC_MonsterStar | 12 | item | `unsigned int` |
| ARC_OutFile | 0 | str | `char[128]` |
| ARC_OutFile | 128 | RolePos | `unsigned int` |
| ARC_OutFile | 132 | RoleNum | `int` |
| ARC_OutFile | 136 | SkillPos | `unsigned int` |
| ARC_OutFile | 140 | SkillNum | `int` |
| ARC_OutFile | 144 | ItemPos | `unsigned int` |
| ARC_OutFile | 148 | ItemNum | `int` |
| ARC_OutFile | 152 | ComboPos | `unsigned int` |
| ARC_OutFile | 156 | ComboNum | `int` |
| ARC_PAL_GDB | 0 | m_head | `ARC_OutFile` |
| ARC_PAL_GDB | 160 | m_RoleData | `ARC_RoleAtt[200]` |
| ARC_PAL_GDB | 170560 | m_SkillData | `ARC_FightSkill[300]` |
| ARC_PAL_GDB | 398560 | m_ItemData | `ARC_FightItem[500]` |
| ARC_PAL_GDB | 798560 | m_ComboData | `ARC_ComboAttack[10]` |
| ARC_PAL_GDB | 804880 | i | `int` |
| ARC_PAL_GDB | 804884 | mLoaded | `BYTE` |
| ARC_PlayerAtt | 852 | hat | `ARC_PlayerItem *` |
| ARC_PlayerAtt | 860 | nScriptSpeed | `int` |
| ARC_PlayerAtt | 864 | cloth | `ARC_PlayerItem` |
| ARC_PlayerAtt | 876 | shoes | `ARC_PlayerItem` |
| ARC_PlayerAtt | 888 | wear | `ARC_PlayerItem[2]` |
| ARC_PlayerAtt | 912 | nScriptCounter | `int` |
| ARC_PlayerAtt | 916 | weapon | `ARC_PlayerItem` |
| ARC_PlayerAtt | 928 | maxrolevalue | `int[12]` |
| ARC_PlayerAtt | 976 | currolevalue | `int[12]` |
| ARC_PlayerAtt | 1024 | dwWeaponSkillID | `unsigned int` |
| ARC_PlayerAtt | 1028 | dwCleanCent | `unsigned int` |
| ARC_PlayerAtt | 1032 | fWeaponSkillMass | `float` |
| ARC_PlayerAtt | 1036 | dwSkillID | `unsigned int[6]` |
| ARC_PlayerAtt | 1060 | bSkillMastered | `_BYTE[6]` |
| ARC_PlayerAtt | 1068 | dwMagicID | `unsigned int[8][6]` |
| ARC_PlayerAtt | 1260 | bMagicMastered | `_BYTE[8][6]` |
| ARC_PlayerAtt | 1308 | byMagicUseTime | `_BYTE[8][6]` |
| ARC_PlayerAtt | 1356 | byMagicLevel | `_BYTE[8][6]` |
| ARC_PlayerAtt | 1404 | bAutoCtrl | `unsigned char` |
| ARC_PlayerAtt | 1405 | bAIAttack | `unsigned char` |
| ARC_PlayerAtt | 1406 | bAIMagic | `unsigned char` |
| ARC_PlayerAtt | 1407 | bAISkill | `unsigned char` |
| ARC_PlayerAtt | 1408 | bAIUseItem | `unsigned char` |
| ARC_PlayerAtt | 1409 | bAINegative | `unsigned char` |
| ARC_PlayerAtt | 1410 | byLineup | `unsigned char` |
| ARC_PlayerItem | 0 | id | `unsigned int` |
| ARC_PlayerItem | 4 | num | `int` |
| ARC_PlayerItem | 8 | item | `signed __int16` |
| ARC_PlayerMgrInfo | 0 | m_nHuaYingMode | `int` |
| ARC_PlayerMgrInfo | 4 | dwWeaponWU | `int` |
| ARC_PlayerMgrInfo | 8 | m_favor | `int[6]` |
| ARC_PlayerMgrInfo | 32 | m_att | `ARC_PlayerAtt[5]` |
| ARC_PlayerMgrInfo | 7092 | m_inteam | `_BYTE[5]` |
| ARC_PlayerMgrInfo | 7100 | m_inventory | `ARC_Inventory` |
| ARC_PlayerMgrInfo | 7140 | m_reoccupy | `ARC_Reoccupy` |
| ARC_PlayerMgrInfo | 7156 | m_starts | `ARC_MonsterStar[10]` |
| ARC_PlayerMgrInfo | 7316 | m_byGemUseTime | `_BYTE[8]` |
| ARC_PlayerMgrInfo | 7324 | reverse | `unsigned int[18]` |
| ARC_Reoccupy | 0 | m_id | `char[16]` |
| ARC_RoleAtt | 0 | id | `unsigned int` |
| ARC_RoleAtt | 4 | type | `unsigned __int16` |
| ARC_RoleAtt | 6 | _todo_006 | `char[66]` |
| ARC_RoleAtt | 72 | _todo_048 | `int` |
| ARC_RoleAtt | 76 | _todo_04c | `int` |
| ARC_RoleAtt | 80 | _todo_050 | `char[4]` |
| ARC_RoleAtt | 84 | _todo_054 | `int` |
| ARC_RoleAtt | 88 | _todo_058 | `int` |
| ARC_RoleAtt | 92 | _todo_05c | `int` |
| ARC_RoleAtt | 96 | _todo_060 | `int` |
| ARC_RoleAtt | 100 | _todo_064 | `int` |
| ARC_RoleAtt | 104 | _todo_068 | `int` |
| ARC_RoleAtt | 108 | _todo_06c | `int` |
| ARC_RoleAtt | 112 | _todo_070 | `int` |
| ARC_RoleAtt | 116 | _todo_074 | `char[188]` |
| ARC_RoleAtt | 304 | _todo_130 | `char[152]` |
| ARC_RoleAtt | 456 | _todo_1c8 | `char[62]` |
| ARC_RoleAtt | 518 | ModelID | `char[30]` |
| ARC_RoleAtt | 548 | _todo_224 | `char[304]` |
| ASISTAGE | 0 | ASI_stream_open | `char *` |
| ASISTAGE | 4 | ASI_stream_process | `char *` |
| ASISTAGE | 8 | ASI_stream_seek | `char *` |
| ASISTAGE | 12 | ASI_stream_close | `char *` |
| ASISTAGE | 16 | ASI_stream_attribute | `char *` |
| ASISTAGE | 20 | ASI_stream_set_preference | `char *` |
| ASISTAGE | 24 | INPUT_BIT_RATE | `unsigned int` |
| ASISTAGE | 28 | INPUT_SAMPLE_RATE | `unsigned int` |
| ASISTAGE | 32 | INPUT_BITS | `unsigned int` |
| ASISTAGE | 36 | INPUT_CHANNELS | `unsigned int` |
| ASISTAGE | 40 | OUTPUT_BIT_RATE | `unsigned int` |
| ASISTAGE | 44 | OUTPUT_SAMPLE_RATE | `unsigned int` |
| ASISTAGE | 48 | OUTPUT_BITS | `unsigned int` |
| ASISTAGE | 52 | OUTPUT_CHANNELS | `unsigned int` |
| ASISTAGE | 56 | POSITION | `unsigned int` |
| ASISTAGE | 60 | PERCENT_DONE | `unsigned int` |
| ASISTAGE | 64 | MIN_INPUT_BLOCK_SIZE | `unsigned int` |
| ASISTAGE | 68 | RAW_RATE | `unsigned int` |
| ASISTAGE | 72 | RAW_BITS | `unsigned int` |
| ASISTAGE | 76 | RAW_CHANNELS | `unsigned int` |
| ASISTAGE | 80 | REQUESTED_RATE | `unsigned int` |
| ASISTAGE | 84 | REQUESTED_BITS | `unsigned int` |
| ASISTAGE | 88 | REQUESTED_CHANS | `unsigned int` |
| ASISTAGE | 92 | stream | `int` |
| AStarPathFinder | 4 | OPEN | `AStarPathFinder::NODE *` |
| AStarPathFinder | 8 | CLOSED | `AStarPathFinder::NODE *` |
| AStarPathFinder | 12 | PATH | `AStarPathFinder::NODE *` |
| AStarPathFinder | 16 | Stack | `AStarPathFinder::STACK *` |
| AStarPathFinder | 20 | m_TestTimer | `int` |
| Actor | 0 | m_actarray_type | `char` |
| Actor | 4 | m_actarray_begin | `Actor *` |
| Actor | 8 | m_actarray_end | `Actor *` |
| Actor | 12 | m_actarray_capacity_end | `Actor *` |
| Actor | 16 | m_pact | `gbActor *` |
| Actor | 20 | m_name | `char[8]` |
| Actor | 28 | m_fMoveSpeed | `float` |
| Actor | 32 | m_fMoveRange | `float` |
| Actor | 36 | m_pAllocBuf | `char *` |
| Actor | 40 | m_fTransitionSpeed | `float` |
| Actor | 44 | m_fTransitionPos | `float` |
| Actor | 48 | m_nRoleParam0 | `int` |
| Actor | 52 | m_fRoleParam1 | `float` |
| Actor | 56 | m_fRoleParam | `float` |
| Actor | 60 | m_fRoleParam2 | `float` |
| Actor | 64 | m_fRoleParam3 | `float` |
| Actor | 68 | m_nRoleParam2 | `int` |
| Actor | 72 | m_pRoleParam3 | `char *` |
| Actor | 76 | m_nCachedA | `int` |
| Actor | 80 | m_nCachedB | `unsigned char` |
| Actor | 84 | m_nTransform | `int` |
| Actor | 88 | m_nRoleState0 | `int` |
| Actor | 92 | m_bUIFlagA | `unsigned char` |
| Actor | 93 | m_bUIFlagB | `unsigned char` |
| Actor | 96 | m_fAnimParam | `float` |
| Actor | 100 | m_szText | `char` |
| Actor | 112 | m_pResource | `void *` |
| Actor | 116 | m_nModelId | `int` |
| Actor | 128 | m_nAnimParam0 | `int` |
| Actor | 132 | m_nAnimParam1 | `int` |
| Actor | 136 | m_vecBonePos | `gbVec3D` |
| Actor | 148 | m_nPathBuffer | `int` |
| Actor | 152 | m_nAnimBuffer | `int` |
| Actor | 156 | m_nParticleBuffer | `int` |
| Actor | 160 | m_vecTargetPos | `gbVec3D` |
| Actor | 172 | m_fInterpStart | `float` |
| Actor | 176 | m_fInterpEnd | `float` |
| Actor | 180 | m_nInterpFrames | `int` |
| Actor | 184 | m_fActionSpeed | `float` |
| Actor | 188 | m_nInterpCurrent | `int` |
| Actor | 192 | m_nInterpState | `int` |
| Actor | 196 | m_fInterpSpeed | `float` |
| Actor | 200 | m_nModelLoadState | `int` |
| Actor | 204 | m_nState | `int` |
| Actor | 208 | m_pRoleObj | `int` |
| Actor | 212 | m_nPathEnabled | `int` |
| Actor | 216 | m_fScale | `unsigned char` |
| Actor | 217 | m_bParamFlag | `unsigned char` |
| Actor | 220 | m_fMatrixA | `float` |
| Actor | 224 | m_fMatrixB | `unsigned char` |
| Actor | 228 | m_fMatrixC | `float` |
| Actor | 232 | m_nMatrixParam | `int` |
| Actor | 236 | m_fMatrixParamA | `float` |
| Actor | 240 | m_fMatrixParamB | `float` |
| Actor | 244 | m_fMatrixE | `float` |
| Actor | 248 | m_fMatrixF | `float` |
| Actor | 252 | m_fMatrixParamC | `float` |
| Actor | 256 | m_Actor | `int` |
| Actor | 264 | m_nCmdParam | `int` |
| Actor | 272 | m_pActor | `gbActor *` |
| Actor | 280 | m_szTexture | `char[28]` |
| Actor | 308 | m_vecLocalPos | `gbVec3D` |
| Actor | 328 | m_nAnimState | `signed __int16` |
| Actor | 332 | m_nActionType | `unsigned char` |
| Actor | 333 | m_bActionFlag1 | `unsigned char` |
| Actor | 336 | m_nActionParam | `unsigned char` |
| Actor | 337 | m_bActionFlag2 | `unsigned char` |
| Actor | 338 | m_bActionFlag3 | `unsigned char` |
| Actor | 339 | m_bActionActive | `unsigned char` |
| Actor | 340 | m_nActionState | `int` |
| Actor | 344 | m_nActionResult | `unsigned char` |
| Actor | 345 | m_bInitialized | `unsigned char` |
| Actor | 348 | m_nHP | `int` |
| Actor | 352 | m_nMaxHP | `int` |
| Actor | 356 | m_bHPVisible | `unsigned char` |
| Actor | 360 | m_nHandleEvent | `int` |
| Actor | 364 | m_vecPos | `gbVec3D` |
| Actor | 376 | m_vecRot | `gbVec3D` |
| Actor | 388 | m_nCloneParam | `int` |
| Actor | 392 | m_fActionAssignParam | `float` |
| Actor | 396 | m_nCloneParamB | `int` |
| Actor | 400 | m_nCloneState | `int` |
| Actor | 404 | m_nCloneFlag1 | `int` |
| Actor | 408 | m_nCloneFlag2 | `int` |
| Actor | 412 | m_fFacingAngle | `float` |
| Actor | 420 | m_nModelParamA | `int` |
| Actor | 428 | m_nModelParamB | `int` |
| Actor | 432 | m_nRoleState1 | `int` |
| Actor | 436 | m_pEquipAtt0 | `RoleAtt *` |
| Actor | 440 | m_nAnimFrames | `int` |
| Actor | 444 | m_nTransitionParam | `int` |
| Actor | 448 | m_pEquipAtt1 | `RoleAtt *[3]` |
| Actor | 460 | m_pEquipAtt2 | `RoleAtt *[3]` |
| Actor | 484 | m_fBlendWeight | `float` |
| Actor | 488 | m_obbox | `int` |
| Actor | 496 | m_pSelfAtt | `void *` |
| Actor | 500 | m_nAnimFrame | `signed __int16` |
| Actor | 512 | m_pParticleData | `void *` |
| Actor | 536 | m_fAnimDelta | `float` |
| Actor | 540 | m_dwMatMsg | `unsigned int[11]` |
| Actor | 584 | m_bChangedMat | `unsigned char` |
| Actor | 585 | m_curact | `char[8]` |
| Actor | 628 | _overlap_RoleSystem_m_partyActor_m_nState | `int` |
| Actor | 632 | m_fDirX | `float` |
| Actor | 636 | m_fDirY | `float` |
| Actor | 640 | m_fDirZ | `float` |
| Actor | 644 | m_fNormX | `float` |
| Actor | 648 | m_fNormY | `float` |
| Actor | 652 | m_fNormZ | `float` |
| Actor | 656 | m_fDistAccum | `float` |
| Actor | 660 | m_fSpeed | `float` |
| Actor | 676 | m_fAngleDeg | `float` |
| Actor | 680 | m_InnerActor | `void *` |
| Actor | 684 | m_bDirFlag | `unsigned char` |
| Actor | 724 | m_nAnimCounter | `int` |
| Actor | 773 | m_bStateFlag | `unsigned char` |
| Actor | 776 | m_pRoleState | `char *` |
| Actor | 784 | m_nUpdateMode | `int` |
| ArcBrief | 0 | gametime | `double` |
| ArcBrief | 8 | inteam | `_BYTE[5]` |
| ArcBrief | 13 | scenename | `char[64]` |
| ArcBrief | 80 | money | `int` |
| ArcHeader | 0 | magic | `char[4]` |
| ArcHeader | 4 | ver | `BYTE` |
| ArcHeader | 8 | reverse | `unsigned int[16]` |
| ArcHeader | 72 | brief | `ArcBrief` |
| ArcHeader | 160 | localeOffset | `unsigned int` |
| ArcHeader | 164 | playerOffset | `unsigned int` |
| ArcHeader | 168 | scriptOffset | `unsigned int` |
| ArcHeader | 172 | sceneOffset | `unsigned int` |
| ArcHeader | 176 | soundOffset | `unsigned int` |
| ArcHeader | 180 | miscOffset | `unsigned int` |
| ArcHeader | 184 | mapOffset | `unsigned int[2]` |
| ArcHeader | 192 | pastOffset | `unsigned int` |
| ArcHeader | 196 | npcOffset | `unsigned int` |
| ArcHeader | 200 | reverseOffset | `_BYTE[20]` |
| ArcLocale | 0 | scene | `SceneInfo` |
| ArcLocale | 132 | camera | `RC_ARG` |
| ArcLocale | 160 | player | `ArcLocaleRole[5]` |
| ArcLocale | 300 | underctrl | `BYTE` |
| ArcLocale | 301 | px_mdl | `char[32]` |
| ArcLocale | 336 | pstate | `PlayerMgr::PoisonState *` |
| ArcLocale | 368 | g_bYouDi | `BYTE` |
| ArcLocale | 372 | m_fFStime | `float` |
| ArcLocale | 376 | music | `ArcLocaleMusic` |
| ArcLocale | 394 | grayscale | `BYTE` |
| ArcLocale | 395 | underwater | `BYTE` |
| ArcLocale | 396 | rain | `BYTE` |
| ArcLocale | 397 | snow | `BYTE` |
| ArcLocale | 398 | watermagic | `BYTE` |
| ArcLocale | 400 | fog | `gbFogParam` |
| ArcLocale | 452 | reverse | `_BYTE[32]` |
| ArcLocaleMusic | 0 | bscript | `BYTE` |
| ArcLocaleMusic | 1 | loop | `BYTE` |
| ArcLocaleMusic | 2 | name | `char[16]` |
| ArcLocaleRole | 0 | active | `BYTE` |
| ArcLocaleRole | 4 | pos | `gbVec3D` |
| ArcLocaleRole | 16 | layer | `BYTE` |
| ArcLocaleRole | 20 | rotate | `float` |
| ArcLocaleRole | 24 | script | `unsigned int` |
| ArcMsic | 0 | m_bigMapElement | `_BYTE[40]` |
| ArcMsic | 40 | m_dwCombatTimes | `unsigned int` |
| ArcMsic | 44 | bPXVariance | `BYTE` |
| ArcMsic | 45 | bHaveNimbus | `BYTE` |
| ArcMsic | 48 | nNimbus | `int[5]` |
| ArcMsic | 68 | m_Player | `tagPlayerSet[11]` |
| ArcMsic | 640 | nImbibeNimbusTimes | `int` |
| ArcMsic | 644 | bShowStatuary | `BYTE` |
| ArcMsic | 645 | reverse | `_BYTE[99]` |
| ArcPastScene | 0 | cityname | `char[32]` |
| ArcPastScene | 32 | name | `char[32]` |
| ArcPosition | 0 | filepath | `char[256]` |
| ArcScene | 0 | scene | `SceneInfo` |
| ArcScene | 132 | objArray | `char[16]` |
| ArcScene | 148 | npcArray | `char[16]` |
| ArcSceneMonster | 0 | id | `BYTE` |
| ArcSceneMonster | 1 | active | `BYTE` |
| ArcSceneMonster | 4 | m_pMonsterData | `void *` |
| ArcSceneMonster | 164 | m_nMonsterHP | `int` |
| ArcSceneMonster | 168 | m_nMonsterMP | `int` |
| ArcSceneMonster | 180 | m_nMonsterLevel | `int` |
| ArcSceneMonster | 236 | m_nMonsterExp | `int` |
| ArcSceneMonster | 304 | m_pSkillList | `void *` |
| ArcSceneMonster | 316 | m_nSkillCount | `int` |
| ArcSceneMonster | 320 | m_pDropItems | `void *` |
| ArcSceneMonster | 324 | m_nDropRate | `int` |
| ArcSceneMonster | 348 | m_nMonsterGold | `int` |
| ArcSceneObject | 0 | info | `ObjectInfo` |
| ArcSceneObject | 604 | task | `SaveTask` |
| ArcSceneObject | 616 | subobj | `int` |
| Archive | 0 | m_scene | `char[16]` |
| Archive | 16 | m_past | `char[16]` |
| Archive | 32 | m_objNotLoad | `char[16]` |
| Array | 0 | m_pDataStart | `int` |
| Array | 4 | m_nSize | `int` |
| Array | 8 | m_pData | `char *` |
| Array | 12 | m_nCapacity | `int` |
| ArraySlots | 72 | m_aSlotPtrs | `int[3]` |
| ArraySlots | 84 | m_bActive | `int` |
| ArtistPlugIn | 0 | pFile | `FILE *` |
| ArtistPlugIn | 4 | _libfolder | `char[512]` |
| ArtistPlugIn | 516 | pInfo | `_PlugInfo *` |
| ArtistPlugIn | 520 | m_infoNum | `unsigned int` |
| ArtistPlugIn | 524 | m_alreadyLoad | `BYTE` |
| ArtistPlugIn | 528 | m_tRect | `tagRECT` |
| ArtistPlugIn | 544 | m_bOptmize | `BYTE` |
| ArtistPlugIn | 548 | m_posMaker | `UIPosMaker` |
| AudioContext | 0 | m_nType | `int` |
| AudioContext | 4 | m_nState | `int` |
| AudioContext | 8 | m_nVolume | `int` |
| AudioContext | 12 | m_pSoundName | `char *` |
| AudioContext | 16 | m_bPlaying | `int` |
| AudioContext | 20 | m_nReserved | `int` |
| AudioContext | 24 | m_pAudioMgr | `char *` |
| AudioContext | 28 | m_nFadeTarget | `int` |
| Average | 0 | _size | `unsigned int` |
| Average | 4 | _data | `float *` |
| Average | 8 | ret | `float` |
| Average | 12 | _cur | `unsigned int` |
| Average | 16 | _real | `unsigned int` |
| Average | 20 | _initialize | `BYTE` |
| Average | 21 | _invalid | `BYTE` |
| Average | 22 | _full | `BYTE` |
| BARRIER | 0 | vPos | `gbVec3D` |
| BARRIER | 12 | fXLen | `float` |
| BARRIER | 16 | fYLen | `float` |
| BARRIER | 20 | fZLen | `float` |
| BARRIER | 24 | nFloorX | `int` |
| BARRIER | 28 | nFloorZ | `int` |
| BINK | 0 | Width | `unsigned int` |
| BINK | 4 | Height | `unsigned int` |
| BINK | 8 | Frames | `unsigned int` |
| BINK | 12 | FrameNum | `unsigned int` |
| BINK | 16 | LastFrameNum | `unsigned int` |
| BINK | 20 | FrameRate | `unsigned int` |
| BINK | 24 | FrameRateDiv | `unsigned int` |
| BINK | 28 | ReadError | `unsigned int` |
| BINK | 32 | OpenFlags | `unsigned int` |
| BINK | 36 | BinkType | `unsigned int` |
| BINK | 40 | Size | `unsigned int` |
| BINK | 44 | FrameSize | `unsigned int` |
| BINK | 48 | SndSize | `unsigned int` |
| BINK | 52 | FrameRects | `BINKRECT[8]` |
| BINK | 180 | NumRects | `int` |
| BINK | 184 | PlaneNum | `unsigned int` |
| BINK | 188 | YPlane | `char *[2]` |
| BINK | 196 | APlane | `char *[2]` |
| BINK | 204 | YWidth | `unsigned int` |
| BINK | 208 | YHeight | `unsigned int` |
| BINK | 212 | UVWidth | `unsigned int` |
| BINK | 216 | UVHeight | `unsigned int` |
| BINK | 220 | MaskPlane | `char *` |
| BINK | 224 | MaskPitch | `unsigned int` |
| BINK | 228 | MaskLength | `unsigned int` |
| BINK | 232 | LargestFrameSize | `unsigned int` |
| BINK | 236 | InternalFrames | `unsigned int` |
| BINK | 240 | NumTracks | `int` |
| BINK | 244 | Highest1SecRate | `unsigned int` |
| BINK | 248 | Highest1SecFrame | `unsigned int` |
| BINK | 252 | Paused | `int` |
| BINK | 256 | BackgroundThread | `unsigned int` |
| BINK | 260 | compframe | `char *` |
| BINK | 264 | preloadptr | `char *` |
| BINK | 268 | frameoffsets | `unsigned int *` |
| BINK | 272 | bio | `BINKIO` |
| BINK | 476 | ioptr | `_BYTE *` |
| BINK | 480 | iosize | `unsigned int` |
| BINK | 484 | decompwidth | `unsigned int` |
| BINK | 488 | decompheight | `unsigned int` |
| BINK | 492 | trackindex | `int` |
| BINK | 496 | tracksizes | `unsigned int *` |
| BINK | 500 | tracktypes | `unsigned int *` |
| BINK | 504 | trackIDs | `int *` |
| BINK | 508 | numrects | `unsigned int` |
| BINK | 512 | playedframes | `unsigned int` |
| BINK | 516 | firstframetime | `unsigned int` |
| BINK | 520 | startframetime | `unsigned int` |
| BINK | 524 | startblittime | `unsigned int` |
| BINK | 528 | startsynctime | `unsigned int` |
| BINK | 532 | startsyncframe | `unsigned int` |
| BINK | 536 | twoframestime | `unsigned int` |
| BINK | 540 | entireframetime | `unsigned int` |
| BINK | 544 | slowestframetime | `unsigned int` |
| BINK | 548 | slowestframe | `unsigned int` |
| BINK | 552 | slowest2frametime | `unsigned int` |
| BINK | 556 | slowest2frame | `unsigned int` |
| BINK | 560 | soundon | `unsigned int` |
| BINK | 564 | videoon | `unsigned int` |
| BINK | 568 | totalmem | `unsigned int` |
| BINK | 572 | timevdecomp | `unsigned int` |
| BINK | 576 | timeadecomp | `unsigned int` |
| BINK | 580 | timeblit | `unsigned int` |
| BINK | 584 | timeopen | `unsigned int` |
| BINK | 588 | fileframerate | `unsigned int` |
| BINK | 592 | fileframeratediv | `unsigned int` |
| BINK | 596 | threadcontrol | `unsigned int` |
| BINK | 600 | runtimeframes | `unsigned int` |
| BINK | 604 | runtimemoveamt | `unsigned int` |
| BINK | 608 | rtframetimes | `unsigned int *` |
| BINK | 612 | rtadecomptimes | `unsigned int *` |
| BINK | 616 | rtvdecomptimes | `unsigned int *` |
| BINK | 620 | rtblittimes | `unsigned int *` |
| BINK | 624 | rtreadtimes | `unsigned int *` |
| BINK | 628 | rtidlereadtimes | `unsigned int *` |
| BINK | 632 | rtthreadreadtimes | `unsigned int *` |
| BINK | 636 | lastblitflags | `unsigned int` |
| BINK | 640 | lastdecompframe | `unsigned int` |
| BINK | 644 | sndbufsize | `unsigned int` |
| BINK | 648 | sndbuf | `_BYTE *` |
| BINK | 652 | sndend | `_BYTE *` |
| BINK | 656 | sndwritepos | `_BYTE *` |
| BINK | 660 | sndreadpos | `_BYTE *` |
| BINK | 664 | sndcomp | `unsigned int` |
| BINK | 668 | sndamt | `unsigned int` |
| BINK | 672 | sndreenter | `unsigned int` |
| BINK | 676 | sndconvert8 | `unsigned int` |
| BINK | 680 | bsnd | `BINKSND` |
| BINK | 872 | skippedlastblit | `unsigned int` |
| BINK | 876 | skippedblits | `unsigned int` |
| BINK | 880 | soundskips | `unsigned int` |
| BINK | 884 | sndendframe | `unsigned int` |
| BINK | 888 | sndprime | `unsigned int` |
| BINK | 892 | sndpad | `unsigned int` |
| BINK | 896 | bunp | `BUNDLEPOINTERS` |
| BINKIO | 0 | ReadHeader | `char *` |
| BINKIO | 4 | ReadFrame | `char *` |
| BINKIO | 8 | GetBufferSize | `char *` |
| BINKIO | 12 | SetInfo | `char *` |
| BINKIO | 16 | Idle | `char *` |
| BINKIO | 20 | Close | `char *` |
| BINKIO | 24 | bink | `BINK *` |
| BINKIO | 28 | ReadError | `unsigned int` |
| BINKIO | 32 | DoingARead | `unsigned int` |
| BINKIO | 36 | BytesRead | `unsigned int` |
| BINKIO | 40 | Working | `unsigned int` |
| BINKIO | 44 | TotalTime | `unsigned int` |
| BINKIO | 48 | ForegroundTime | `unsigned int` |
| BINKIO | 52 | IdleTime | `unsigned int` |
| BINKIO | 56 | ThreadTime | `unsigned int` |
| BINKIO | 60 | BufSize | `unsigned int` |
| BINKIO | 64 | BufHighUsed | `unsigned int` |
| BINKIO | 68 | CurBufSize | `unsigned int` |
| BINKIO | 72 | CurBufUsed | `unsigned int` |
| BINKIO | 76 | iodata | `_BYTE[128]` |
| BINKRECT | 0 | Left | `int` |
| BINKRECT | 4 | Top | `int` |
| BINKRECT | 8 | Width | `int` |
| BINKRECT | 12 | Height | `int` |
| BINKSND | 0 | Ready | `char *` |
| BINKSND | 4 | Lock | `char *` |
| BINKSND | 8 | Unlock | `char *` |
| BINKSND | 12 | Volume | `char *` |
| BINKSND | 16 | Pan | `char *` |
| BINKSND | 20 | Pause | `char *` |
| BINKSND | 24 | SetOnOff | `char *` |
| BINKSND | 28 | Close | `char *` |
| BINKSND | 32 | BestSizeIn16 | `unsigned int` |
| BINKSND | 36 | SoundDroppedOut | `unsigned int` |
| BINKSND | 40 | OnOff | `int` |
| BINKSND | 44 | Latency | `unsigned int` |
| BINKSND | 48 | VideoScale | `unsigned int` |
| BINKSND | 52 | freq | `unsigned int` |
| BINKSND | 56 | bits | `int` |
| BINKSND | 60 | chans | `int` |
| BINKSND | 64 | snddata | `_BYTE[128]` |
| BOSSHURT | 0 | AlphaSpeed | `float` |
| BOSSHURT | 4 | bFlashState | `BYTE` |
| BOSSHURT | 5 | bNeedFlash | `BYTE` |
| BOSSHURT | 8 | fTimeCounter | `float` |
| BOSSHURT | 12 | nWaitSecond | `int` |
| BOSSHURT | 16 | nHurtState | `int` |
| BUNDLEPOINTERS | 0 | typeptr | `char *` |
| BUNDLEPOINTERS | 4 | type16ptr | `char *` |
| BUNDLEPOINTERS | 8 | colorptr | `char *` |
| BUNDLEPOINTERS | 12 | bits2ptr | `char *` |
| BUNDLEPOINTERS | 16 | motionXptr | `char *` |
| BUNDLEPOINTERS | 20 | motionYptr | `char *` |
| BUNDLEPOINTERS | 24 | dctptr | `char *` |
| BUNDLEPOINTERS | 28 | mdctptr | `char *` |
| BUNDLEPOINTERS | 32 | patptr | `char *` |
| BillBoardFace | 0 | m_texarray | `gbTextureArray` |
| BillBoardFace | 68 | m_curtex | `int` |
| BillBoardFace | 72 | m_id | `int` |
| BillBoardFace | 76 | m_pos | `gbVec3D` |
| BillBoardFace | 88 | m_effect | `gbRenderEffect *` |
| BtnGroup | 0 | upRc | `tagRECT` |
| BtnGroup | 16 | dwRc | `tagRECT` |
| BtnGroup | 32 | m_btnUp | `UIButton` |
| BtnGroup | 376 | m_btnDw | `UIButton` |
| BtnGroup | 720 | m_sizex | `int` |
| BtnGroup | 724 | m_sizey | `int` |
| BtnGroup | 728 | m_mode | `_BGM` |
| BtnGroup | 732 | m_Interval | `int` |
| BtnGroup | 736 | m_opt | `BYTE` |
| C2DSpark | 0 | m_Spark | `C2DSpark_tagSpark[512]` |
| C2DSpark | 24576 | m_fDisplayWidth | `float` |
| C2DSpark | 24580 | m_fDisplayHeight | `float` |
| C2DSpark | 24584 | m_nCurrentSpark | `int` |
| C2DSpark | 24588 | m_fBigLum | `float` |
| C2DSpark | 24592 | m_nBigLumX | `int` |
| C2DSpark | 24596 | m_nBigLumY | `int` |
| C2DSpark | 24600 | m_bMouseTrack | `BYTE` |
| C2DSpark | 24604 | m_pAdditiveBlend | `gbRenderEffect *` |
| C2DSpark | 24608 | m_pRedBig | `gbTexture *` |
| C2DSpark | 24612 | m_pRedBigArray | `gbTextureArray *` |
| C2DSpark | 24616 | m_pBlue16 | `gbTexture *` |
| C2DSpark | 24620 | m_pBlue16Array | `gbTextureArray *` |
| C2DSpark | 24624 | m_pGreen16 | `gbTexture *` |
| C2DSpark | 24628 | m_pGreen16Array | `gbTextureArray *` |
| C2DSpark | 24632 | m_pRed16 | `gbTexture *` |
| C2DSpark | 24636 | m_pRed16Array | `gbTextureArray *` |
| C2DSpark | 24640 | m_pYellow16 | `gbTexture *` |
| C2DSpark | 24644 | m_pYellow16Array | `gbTextureArray *` |
| C2DSpark | 24648 | m_Quad | `gbUIQuad` |
| C2DSpark_tagSpark | 0 | pTexture1 | `gbTexture *` |
| C2DSpark_tagSpark | 4 | pTextureWrap1 | `void *` |
| C2DSpark_tagSpark | 8 | pTexture2 | `int` |
| C2DSpark_tagSpark | 12 | pTextureWrap2 | `int` |
| C2DSpark_tagSpark | 16 | pTexture3 | `gbTexture *` |
| C2DSpark_tagSpark | 20 | pTextureWrap3 | `void *` |
| C2DSpark_tagSpark | 24 | pTexture4 | `gbTexture *` |
| C2DSpark_tagSpark | 28 | pTextureWrap4 | `int` |
| C2DSpark_tagSpark | 32 | pTexture5 | `gbTexture *` |
| C2DSpark_tagSpark | 36 | pTextureWrap5 | `void *` |
| C2DSpark_tagSpark | 40 | nRenderEffect | `int` |
| C2DSpark_tagSpark | 44 | pRenderEffect | `int` |
| C3DSpark | 0 | m_Spark | `C3DSpark_tagSpark[128]` |
| C3DSpark | 7168 | m_nCurrentSpark | `int` |
| C3DSpark | 7172 | m_pAdditiveBlend | `gbRenderEffect *` |
| C3DSpark | 7176 | m_pRedBig | `gbTexture *` |
| C3DSpark | 7180 | m_pRedBigArray | `gbTextureArray *` |
| C3DSpark | 7184 | m_pBlue16 | `gbTexture *` |
| C3DSpark | 7188 | m_pBlue16Array | `gbTextureArray *` |
| C3DSpark | 7192 | m_pGreen16 | `gbTexture *` |
| C3DSpark | 7196 | m_pGreen16Array | `gbTextureArray *` |
| C3DSpark | 7200 | m_pRed16 | `gbTexture *` |
| C3DSpark | 7204 | m_pRed16Array | `gbTextureArray *` |
| C3DSpark | 7208 | m_pYellow16 | `gbTexture *` |
| C3DSpark | 7212 | m_pYellow16Array | `gbTextureArray *` |
| C3DSpark | 7216 | m_GeomQuad | `gbGeomQuad[128]` |
| CAcceleratedMotionPolicy | 12 | _vAcceleration | `gbVec3D` |
| CArrayList | 0 | m_ArrayListType | `ArrayListType` |
| CArrayList | 4 | m_pData | `char *` |
| CArrayList | 8 | m_BytesPerEntry | `unsigned int` |
| CArrayList | 12 | m_NumEntries | `unsigned int` |
| CArrayList | 16 | m_NumEntriesAllocated | `unsigned int` |
| CCBAI | 0 | m_bNewRole | `_BYTE[11]` |
| CCBAI | 12 | m_pCBSystem | `CCBSystem *` |
| CCBAI | 16 | m_pRoleState | `CCBRoleState *` |
| CCBAI | 20 | m_pUtil | `CUtil *` |
| CCBAI | 24 | m_VA | `tagVA` |
| CCBAI | 48 | m_VAO | `tagVAO[32]` |
| CCBAI | 560 | m_VAF | `tagVAF[32]` |
| CCBAI | 1584 | m_Demand | `tagDemand[10][11]` |
| CCBAI | 3344 | m_EnemyDemand | `tagDemand[5]` |
| CCBAI | 3424 | m_nDemandThreadTracer | `int` |
| CCBAI | 3432 | m_bDemandThreadTracer | `unsigned char` |
| CCBAI | 3504 | m_FriendDemand | `tagDemand[5]` |
| CCBAI | 3584 | m_nHandleEnemyWell | `int` |
| CCBAI | 3592 | m_nTodo_E08 | `unsigned char` |
| CCBAIWindow | 72 | m_pBack | `UIStatic *` |
| CCBAIWindow | 76 | m_pName | `UIStatic *[5]` |
| CCBAIWindow | 96 | m_pAttack | `UIPushButton *` |
| CCBAIWindow | 100 | m_pItem | `UIPushButton *` |
| CCBAIWindow | 104 | m_pSkill | `UIPushButton *` |
| CCBAIWindow | 108 | m_pMagic | `UIPushButton *` |
| CCBAIWindow | 112 | m_pAffirmative | `UIPushButton *` |
| CCBAIWindow | 116 | m_pAI | `UIPushButton *` |
| CCBAIWindow | 120 | m_pOk | `UIButton *` |
| CCBAIWindow | 124 | m_nIndex | `int` |
| CCBAttackSequen | 0 | m_pCBSystem | `CCBSystem *` |
| CCBAttackSequen | 4 | m_pUI | `CCBUI *` |
| CCBAttackSequen | 8 | m_pRole | `CCBRoleState *` |
| CCBAttackSequen | 12 | m_Sequen | `tagAttackSequen[11]` |
| CCBAttackSequen | 452 | m_bEnable | `unsigned char` |
| CCBAttackSequen | 453 | m_bPause | `unsigned char` |
| CCBAttackSequen | 454 | m_bVisible | `unsigned char` |
| CCBAttackSequen | 455 | m_bLocked | `unsigned char` |
| CCBCamControl | 8 | m_pvecCenter | `gbVec3D *` |
| CCBCamControl | 12 | m_nTodo_00C | `float` |
| CCBCamControl | 16 | m_nTodo_010 | `gbVolModNode *` |
| CCBCamControl | 52 | m_fCamBlendA | `float` |
| CCBCamControl | 56 | m_fCamBlendB | `float` |
| CCBCamControl | 60 | m_CamCtrlData | `int` |
| CCBCamControl | 236 | m_nTodo_EC | `gbVolModNode` |
| CCBCamControl | 608 | m_PanelSlots | `CCBPanelSlot` |
| CCBCamControl | 2436 | m_nList | `gbRefObject *` |
| CCBCamControl | 2440 | m_nPointerUnderMouse | `int` |
| CCBCamControl | 2444 | m_CamEntries | `int[1794]` |
| CCBCamControl | 9620 | m_nCurCamIdx | `int` |
| CCBCamControl | 21848 | m_nCurPageTab | `int` |
| CCBCamControl | 249784 | m_RenderQueue | `UIParticle[98]` |
| CCBCamControl | 307016 | m_SelectRect | `int[4]` |
| CCBCamControl | 383468 | m_SlotButtons | `UIButton[5]` |
| CCBCamControl | 389984 | m_TabLists | `_BYTE[6040]` |
| CCBCamControl | 430000 | m_pStage | `CCBStage *` |
| CCBCamControl | 430004 | m_pCam | `CCBStageCam *` |
| CCBCamControl | 430008 | m_pUtil | `CUtil *` |
| CCBCamControl | 430012 | m_bRunning | `unsigned char` |
| CCBCamControl | 430016 | m_fp | `char *` |
| CCBCamControl | 430032 | m_nCurList | `int` |
| CCBCamControl | 430036 | m_nCurTask | `int` |
| CCBCamControl | 430040 | m_fStartSpeed | `float` |
| CCBCamControl | 430044 | m_fNextSpeed | `float` |
| CCBCamControl | 430048 | m_vecSpeed | `gbVec3D` |
| CCBCamControl | 430060 | m_vecNextSpeed | `gbVec3D` |
| CCBCamControl | 430072 | m_fDistance | `float` |
| CCBCamControl | 430076 | m_fQuake | `float` |
| CCBCamControl | 430080 | m_fQuakeDec | `float` |
| CCBCamControl | 430084 | m_fQuakeFre | `float` |
| CCBCamControl | 430088 | m_StartPos | `tagCam` |
| CCBCamControl | 430112 | m_CurPos | `tagCam` |
| CCBCamControl | 430136 | m_vecCurPos | `gbVec3D` |
| CCBCamControl | 430148 | m_OBBox | `gbOBBox` |
| CCBCamControl | 430224 | m_pPointer | `gbGeomNode *` |
| CCBCamControl | 430228 | m_vecCircleCenter | `gbVec3D` |
| CCBCamControl | 430240 | m_vecCircleEnd | `gbVec3D` |
| CCBCamControl | 430252 | m_bShowCircleSet | `unsigned char` |
| CCBCamControl | 430253 | m_bCircleCenterSelected | `unsigned char` |
| CCBCamControl | 430254 | m_bCircleEndSelected | `unsigned char` |
| CCBControl | 0 | m_pCBSystem | `CCBSystem *` |
| CCBControl | 4 | m_pAttackSequen | `CCBAttackSequen *` |
| CCBControl | 8 | m_pStage | `CCBStage *` |
| CCBControl | 12 | m_pRoleState | `CCBRoleState *` |
| CCBControl | 16 | m_pUI | `CCBUI *` |
| CCBControl | 24 | m_DeltaTime | `double` |
| CCBControl | 32 | m_nController | `int` |
| CCBControl | 36 | m_bActive | `unsigned char` |
| CCBControl | 37 | m_bForceRelease | `unsigned char` |
| CCBControl | 40 | m_InputData | `tagControlData` |
| CCBControl | 56 | m_CmdData | `tagCmdData` |
| CCBControl | 100 | m_bShowRightPanel | `unsigned char` |
| CCBControl | 104 | m_nCurThread | `int` |
| CCBControl | 108 | m_nThread | `int` |
| CCBControl | 112 | m_Thread | `tagControlThread[4]` |
| CCBControlWindow | 72 | m_pBack | `UIStatic *` |
| CCBControlWindow | 76 | m_pButtonAttack | `UIButton *` |
| CCBControlWindow | 80 | m_pButtonSkill | `UIButton *` |
| CCBControlWindow | 84 | m_pButtonMagic | `UIButton *` |
| CCBControlWindow | 88 | m_pButtonItem | `UIButton *` |
| CCBControlWindow | 92 | m_pButtonDefence | `UIButton *` |
| CCBControlWindow | 96 | m_pButtonLineup | `UIButton *` |
| CCBControlWindow | 100 | m_pButtonAI | `UIButton *` |
| CCBControlWindow | 104 | m_pButtonFlee | `UIButton *` |
| CCBControlWindow | 108 | m_pButtonProtect | `UIButton *` |
| CCBControlWindow | 112 | m_CurCtrl | `UIWnd *` |
| CCBControlWindow | 116 | m_CurCtrl_1 | `UIWnd *` |
| CCBControlWindow | 120 | m_CurCtrl_2 | `UIWnd *` |
| CCBDisplayChain | 0 | m_pStage | `CCBStage *` |
| CCBDisplayChain | 4 | m_pScene | `CCBStageScene *` |
| CCBDisplayChain | 8 | m_DefaultColor | `tagRGBQUAD` |
| CCBDisplayChain | 12 | m_ScreenQuadColor | `gbColorQuad` |
| CCBDisplayChain | 16 | m_nItemNum | `int` |
| CCBDisplayChain | 20 | m_ShowItem | `tagShowItem[64]` |
| CCBDisplayChain | 17940 | m_byScreenQuadAlpha | `unsigned char` |
| CCBEditor | 0 | m_fpThis | `CCBEditor *` |
| CCBEditor | 4 | m_pRoleState | `CCBRoleState *` |
| CCBEditor | 8 | m_NewItem | `tagNewItem[500]` |
| CCBEditor | 8008 | m_dwSelectFighter | `int[11]` |
| CCBEditor | 8052 | m_nCurCCTList | `int` |
| CCBEditor | 8056 | m_nCurCCT | `int` |
| CCBEditor | 8060 | m_nCurEffClass | `int` |
| CCBEditor | 8064 | m_nCurEffObjType | `int` |
| CCBEditor | 8068 | m_nCurEffGroup | `int` |
| CCBEditor | 8072 | m_nCurEffObjInGroup | `int` |
| CCBEditor | 8076 | m_nCurEffObjTask | `int` |
| CCBEditor | 8080 | m_dwTrickID | `unsigned int[384]` |
| CCBEditor | 9616 | m_nCurSelectedEffGroup | `int` |
| CCBEditor | 9620 | m_nCurSelectedTrick | `int` |
| CCBFiveNimbusWindow | 72 | pCtrlButton | `UIButtonEX *[5]` |
| CCBFiveNimbusWindow | 92 | pMiddle | `UIButtonEX *` |
| CCBFiveNimbusWindow | 96 | m_OpenWindow | `OpenFNWindow` |
| CCBFiveNimbusWindow | 108 | m_nimbus | `int[5]` |
| CCBFiveNimbusWindow | 128 | m_state | `int[5]` |
| CCBFiveNimbusWindow | 148 | m_nimbusStep | `int` |
| CCBFiveNimbusWindow | 152 | m_bShow | `unsigned char` |
| CCBFiveNimbusWindow | 153 | m_bLock | `unsigned char` |
| CCBFiveNimbusWindow | 156 | m_counter | `int` |
| CCBItemWindow | 72 | m_pBack | `UIStatic *` |
| CCBItemWindow | 76 | m_pDescription | `UIStatic *` |
| CCBItemWindow | 80 | m_pItemList | `UIListBox *[3]` |
| CCBItemWindow | 92 | m_pButtonRecover | `UIPushButton *` |
| CCBItemWindow | 96 | m_pButtonAttack | `UIPushButton *` |
| CCBItemWindow | 100 | m_pButtonTreasure | `UIPushButton *` |
| CCBItemWindow | 104 | m_nActivePage | `int` |
| CCBLineupWindow | 72 | m_nInitRoleFaceLineup | `int[5]` |
| CCBLineupWindow | 92 | m_pBack | `UIStatic *` |
| CCBLineupWindow | 96 | m_pFace | `UIStatic *[5]` |
| CCBLineupWindow | 116 | m_nSelected | `int` |
| CCBLineupWindow | 120 | m_pUI | `CCBUI *` |
| CCBMagicWindow | 72 | m_pBack | `UIStatic *` |
| CCBMagicWindow | 76 | m_pMagicList | `UIListBox *[6]` |
| CCBMagicWindow | 100 | m_pButtonWater | `UIPushButton *` |
| CCBMagicWindow | 104 | m_pButtonFire | `UIPushButton *` |
| CCBMagicWindow | 108 | m_pButtonThunder | `UIPushButton *` |
| CCBMagicWindow | 112 | m_pButtonWind | `UIPushButton *` |
| CCBMagicWindow | 116 | m_pButtonEarth | `UIPushButton *` |
| CCBMagicWindow | 120 | m_pButtonDouble | `UIPushButton *` |
| CCBMagicWindow | 124 | m_nActivePage | `int` |
| CCBMagicWindow | 184 | m_nBtnX | `int` |
| CCBMagicWindow | 196 | m_nBtnY | `int` |
| CCBMagicWindow | 200 | m_nBtnState | `int` |
| CCBPanelSlot | 4 | m_nDimH | `int` |
| CCBPanelSlot | 8 | m_nEdgeR | `int` |
| CCBPanelSlot | 12 | m_nEdgeB | `int` |
| CCBPanelSlot | 16 | m_nMarginX2 | `int` |
| CCBPanelSlot | 20 | m_nDimH2 | `int` |
| CCBPanelSlot | 24 | m_nEdgeR2 | `int` |
| CCBPanelSlot | 28 | m_nEdgeB2 | `int` |
| CCBPanelSlot | 32 | m_fMarginX | `float` |
| CCBPanelSlot | 36 | m_fDimH | `float` |
| CCBPanelSlot | 40 | m_nClipL | `int` |
| CCBPanelSlot | 44 | m_nClipT | `int` |
| CCBPanelSlot | 48 | m_nClipR | `int` |
| CCBPanelSlot | 52 | m_nClipB | `int` |
| CCBPanelSlot | 56 | m_nClipL2 | `int` |
| CCBPanelSlot | 60 | m_nClipT2 | `int` |
| CCBPanelSlot | 64 | m_nClipR2 | `int` |
| CCBPanelSlot | 68 | m_nClipB2 | `int` |
| CCBPanelSlot | 72 | m_nPosX | `int` |
| CCBPanelSlot | 76 | m_nPosY | `int` |
| CCBPanelSlot | 92 | m_Widget | `char[384]` |
| CCBParabolaWindow | 72 | m_pBack | `UIStatic *` |
| CCBParabolaWindow | 76 | m_pDescription | `UIStatic *` |
| CCBParabolaWindow | 80 | m_pItemList | `UIListBox *` |
| CCBProtectWindow | 72 | m_pBack | `UIStatic *` |
| CCBProtectWindow | 76 | m_pWHFace | `UIPushButton *` |
| CCBProtectWindow | 80 | m_pWPXFace | `UIPushButton *` |
| CCBProtectWindow | 84 | m_pWHLove | `UIProgressBar *` |
| CCBProtectWindow | 88 | m_pWPXLove | `UIProgressBar *` |
| CCBProtectWindow | 92 | m_pOk | `UIButton *` |
| CCBResultWindow | 72 | m_pBack | `UIStatic *` |
| CCBResultWindow | 76 | m_pWind | `UIStatic *` |
| CCBResultWindow | 80 | m_pThunder | `UIStatic *` |
| CCBResultWindow | 84 | m_pWater | `UIStatic *` |
| CCBResultWindow | 88 | m_pFire | `UIStatic *` |
| CCBResultWindow | 92 | m_pEarth | `UIStatic *` |
| CCBResultWindow | 96 | m_pDouble | `UIStatic *` |
| CCBResultWindow | 100 | m_pEXP | `UIStatic *` |
| CCBResultWindow | 104 | m_pLevel | `UIStatic *` |
| CCBResultWindow | 108 | m_pFace | `UIStatic *[11]` |
| CCBResultWindow | 152 | m_pHGM | `UIStatic *` |
| CCBResultWindow | 156 | m_pHP | `UIProgressBar *` |
| CCBResultWindow | 160 | m_pGP | `UIProgressBar *` |
| CCBResultWindow | 164 | m_pMP | `UIProgressBar *` |
| CCBResultWindow | 168 | m_pUI | `CCBUI *` |
| CCBResultWindow | 172 | m_nIndex | `int` |
| CCBResultWindow | 176 | m_bClosed | `unsigned char` |
| CCBRoleState | 76 | m_nState_04C | `int` |
| CCBRoleState | 96 | m_nState_060 | `int` |
| CCBRoleState | 100 | m_nCombatResult | `int` |
| CCBRoleState | 132 | m_nState | `int[4]` |
| CCBRoleState | 148 | m_nTargetRoleIdx | `int` |
| CCBRoleState | 156 | m_nSelectedAction | `int` |
| CCBRoleState | 160 | m_nSelectedTarget | `int` |
| CCBRoleState | 164 | m_nSelectedItem | `int` |
| CCBRoleState | 168 | m_nState2 | `int[26]` |
| CCBRoleState | 280 | m_nDamageThisRound | `int` |
| CCBRoleState | 288 | m_nState3 | `int[18]` |
| CCBRoleState | 360 | m_nTodo_168 | `UIFrameWnd` |
| CCBRoleState | 512 | m_fLastDialogTime | `float` |
| CCBRoleState | 516 | m_bCombatDialog | `unsigned char` |
| CCBRoleState | 520 | m_pCBSystem | `CCBSystem *` |
| CCBRoleState | 524 | m_pStage | `CCBStage *` |
| CCBRoleState | 528 | m_pUI | `CCBUI *` |
| CCBRoleState | 532 | m_pUtil | `CUtil *` |
| CCBRoleState | 536 | m_bWeSneakAttackEnemy | `unsigned char` |
| CCBRoleState | 537 | m_bEnemySneakAttackUs | `unsigned char` |
| CCBRoleState | 540 | m_nMaxRound | `int` |
| CCBRoleState | 544 | m_nBossRound | `int` |
| CCBRoleState | 548 | m_bMustFail | `unsigned char` |
| CCBRoleState | 549 | m_bFleeAlwaysSuccess | `unsigned char` |
| CCBRoleState | 550 | m_bCreatedNewRole | `unsigned char` |
| CCBRoleState | 552 | m_Role | `tagRoleState[11]` |
| CCBRoleState | 7676 | m_byteFlags | `unsigned char` |
| CCBRoleState | 10352 | m_nTodo_2870 | `unsigned char` |
| CCBRoleState | 10364 | m_BufferData | `char[1628]` |
| CCBRoleState | 11992 | m_RoleXor | `tagRoleState[11]` |
| CCBRoleState | 18616 | m_SlotUIWnd | `UIWnd` |
| CCBRoleState | 18700 | m_fLerpCurX | `float` |
| CCBRoleState | 18704 | m_fLerpCurY | `float` |
| CCBRoleState | 18708 | m_nLerpTargetX | `int` |
| CCBRoleState | 18712 | m_nLerpTargetY | `int` |
| CCBRoleState | 18716 | m_nLerpDestX | `int` |
| CCBRoleState | 18720 | m_nLerpDestY | `int` |
| CCBRoleState | 18732 | m_nLerpDir | `int` |
| CCBRoleState | 18745 | m_bLerpDone | `unsigned char` |
| CCBRoleState | 18748 | m_fLerpSpeed | `float` |
| CCBRoleState | 18780 | m_fSpringPosX | `float` |
| CCBRoleState | 18784 | m_fSpringPosY | `float` |
| CCBRoleState | 18788 | m_fSpringTargX | `float` |
| CCBRoleState | 18792 | m_fSpringTargY | `float` |
| CCBRoleState | 18796 | m_fSpringPrevX | `float` |
| CCBRoleState | 18800 | m_fSpringPrevY | `float` |
| CCBRoleState | 18804 | m_nSpringTargetX | `int` |
| CCBRoleState | 18808 | m_nSpringTargetY | `int` |
| CCBRoleState | 18812 | m_nSpringDir | `int` |
| CCBRoleState | 18816 | m_fSpringAccelX | `float` |
| CCBRoleState | 18820 | m_fSpringAccelY | `float` |
| CCBRoleState | 18824 | m_bSpringDoneX | `unsigned char` |
| CCBRoleState | 18825 | m_bSpringDoneY | `unsigned char` |
| CCBRoleState | 18828 | m_fSpringSpeed | `float` |
| CCBRoleState | 19056 | m_SlotWidgets | `UIWnd` |
| CCBRoleState | 19664 | m_SlotRects | `int` |
| CCBRoleState | 19828 | m_SlotRightEdge | `int` |
| CCBRoleState | 19896 | m_nSlotStartY | `int` |
| CCBRoleState | 19900 | m_nSlotSpacing | `int` |
| CCBRoleState | 19904 | m_nSlotHeight | `int` |
| CCBRoleState | 19908 | m_nSlotWidth | `int` |
| CCBRoleState | 19912 | m_bySlotVisible | `unsigned char` |
| CCBRoleState | 20064 | m_pScene | `UIScene *` |
| CCBRoleState | 20408 | m_Static_20408 | `UIStatic` |
| CCBRoleState | 20560 | m_bVideoPlayed | `unsigned char` |
| CCBRoleState | 20564 | m_nVideoState | `int` |
| CCBRoleState | 20576 | m_nCurrentTaskID | `int` |
| CCBRoleState | 20580 | m_nEffCurA | `int` |
| CCBRoleState | 20584 | m_nEffCurB | `int` |
| CCBRoleState | 20592 | m_nEffTarget1 | `int` |
| CCBRoleState | 20596 | m_nEffTarget2 | `int` |
| CCBRoleState | 20600 | m_nEffTransFrames | `int` |
| CCBRoleState | 20604 | m_nEffSwapA | `int` |
| CCBRoleState | 20608 | m_nEffSwapB | `int` |
| CCBRoleState | 20616 | m_nEffCurC | `int` |
| CCBRoleState | 20620 | m_nEffSwapC | `int` |
| CCBRoleState | 20624 | m_nEffCurD | `int` |
| CCBRoleState | 20628 | m_nEffTransFrames2 | `int` |
| CCBRoleState | 20632 | m_nEffCurE | `int` |
| CCBRoleState | 20636 | m_nEffSwapE | `int` |
| CCBRoleState | 20640 | m_fTimeFund | `float` |
| CCBRoleState | 21960 | m_bScrollEnableA | `unsigned char` |
| CCBRoleState | 21961 | m_bScrollEnableB | `unsigned char` |
| CCBRoleState | 21964 | m_nScrollOffset | `int` |
| CCBRoleState | 21968 | m_nScrollTarget | `int` |
| CCBRoleState | 22100 | m_nFadeFlags | `int` |
| CCBRoleState | 22104 | m_nFadeAlpha | `int` |
| CCBRoleState | 22108 | m_nFadeTimer | `int` |
| CCBRoleState | 22220 | m_BattleFlags | `int` |
| CCBRoleStatePanel | 0 | m_Headbk | `UIStatic` |
| CCBRoleStatePanel | 152 | m_Head | `UIButton` |
| CCBRoleStatePanel | 496 | m_Name | `UIStatic` |
| CCBRoleStatePanel | 648 | m_Jing | `UIStatic` |
| CCBRoleStatePanel | 800 | m_JingBar | `UIProgressBar` |
| CCBRoleStatePanel | 1044 | m_JingVal | `UIStatic` |
| CCBRoleStatePanel | 1196 | m_Shen | `UIStatic` |
| CCBRoleStatePanel | 1348 | m_ShenBar | `UIProgressBar` |
| CCBRoleStatePanel | 1592 | m_ShenVal | `UIStatic` |
| CCBRoleStatePanel | 1744 | m_Qi | `UIStatic` |
| CCBRoleStatePanel | 1896 | m_QiBar | `UIProgressBar` |
| CCBRoleStatePanel | 2140 | m_QiVal | `UIStatic` |
| CCBRoleStatePanel | 2292 | m_AttFrameHead | `UIStatic` |
| CCBRoleStatePanel | 2444 | m_F | `UIStatic` |
| CCBRoleStatePanel | 2596 | m_W | `UIStatic` |
| CCBRoleStatePanel | 2748 | m_S | `UIStatic` |
| CCBRoleStatePanel | 2900 | m_Y | `UIStatic` |
| CCBRoleStatePanel | 3052 | m_Exp | `UIStatic` |
| CCBRoleStatePanel | 3204 | m_RoleAtt | `UIStatic[5]` |
| CCBRoleStatePanel | 3964 | m_NeedArrow | `UIStatic` |
| CCBRoleStatePanel | 4116 | m_NeedRc | `tagRECT` |
| CCBRoleStatePanelM | 0 | m_Headbk | `UIStatic` |
| CCBRoleStatePanelM | 152 | m_Head | `UIButton` |
| CCBRoleStatePanelM | 496 | m_Name | `UIStatic` |
| CCBRoleStatePanelM | 648 | m_Jing | `UIStatic` |
| CCBRoleStatePanelM | 800 | m_JingBar | `UIProgressBar` |
| CCBRoleStatePanelM | 1044 | m_JingVal | `UIStatic` |
| CCBRoleStatePanelM | 1196 | m_Shen | `UIStatic` |
| CCBRoleStatePanelM | 1348 | m_ShenBar | `UIProgressBar` |
| CCBRoleStatePanelM | 1592 | m_ShenVal | `UIStatic` |
| CCBRoleStatePanelM | 1744 | m_Qi | `UIStatic` |
| CCBRoleStatePanelM | 1896 | m_QiBar | `UIProgressBar` |
| CCBRoleStatePanelM | 2140 | m_QiVal | `UIStatic` |
| CCBRoleStatePanelM | 2292 | m_AttFrameHead | `UIStatic` |
| CCBRoleStatePanelM | 2444 | m_F | `UIStatic` |
| CCBRoleStatePanelM | 2596 | m_W | `UIStatic` |
| CCBRoleStatePanelM | 2748 | m_S | `UIStatic` |
| CCBRoleStatePanelM | 2900 | m_Y | `UIStatic` |
| CCBRoleStatePanelM | 3052 | m_Exp | `UIStatic` |
| CCBRoleStatePanelM | 3204 | m_RoleAtt | `UIStatic[5]` |
| CCBRoleStatePanelM | 3964 | m_NeedArrow | `UIStatic` |
| CCBRoleStatePanelM | 4116 | m_NeedRc | `tagRECT` |
| CCBRoleStatePanelS | 0 | m_Headbk | `UIStatic` |
| CCBRoleStatePanelS | 152 | m_Head | `UIStatic` |
| CCBRoleStatePanelS | 304 | m_Name | `UIStatic` |
| CCBRoleStatePanelS | 456 | m_Jing | `UIStatic` |
| CCBRoleStatePanelS | 608 | m_JingBar | `UIProgressBar` |
| CCBRoleStatePanelS | 852 | m_JingVal | `UIStatic` |
| CCBRoleStatePanelS | 1004 | m_Shen | `UIStatic` |
| CCBRoleStatePanelS | 1156 | m_ShenBar | `UIProgressBar` |
| CCBRoleStatePanelS | 1400 | m_ShenVal | `UIStatic` |
| CCBRoleStatePanelS | 1552 | m_Qi | `UIStatic` |
| CCBRoleStatePanelS | 1704 | m_QiBar | `UIProgressBar` |
| CCBRoleStatePanelS | 1948 | m_QiVal | `UIStatic` |
| CCBRoleStatePanelS | 2100 | m_Shade | `UIStatic` |
| CCBRoleStatePanelS | 2252 | m_Portrait | `UIStatic` |
| CCBRoleStatePanelS | 2404 | m_Level | `UIStatic` |
| CCBRoleStatePanelS | 2556 | m_ExpVal | `UIStatic` |
| CCBRoleStatePanelS | 2708 | m_NextLv | `UIStatic` |
| CCBRoleStatePanelS | 2860 | m_WuLing | `UIStatic[5]` |
| CCBRoleStatePanelS | 3620 | m_FWSY | `UIStatic` |
| CCBRoleStatePanelS | 3772 | m_FWSYrc | `tagRECT` |
| CCBSkillWindow | 72 | m_pBack | `UIStatic *` |
| CCBSkillWindow | 76 | m_pDescription | `UIStatic *` |
| CCBSkillWindow | 80 | m_pSkillList | `UIListBox *[1]` |
| CCBStage | 88 | m_pShadow | `CCBStageShadow *` |
| CCBStage | 92 | m_pEffect | `CCBStageEffect *` |
| CCBStage | 96 | m_BFARole | `int` |
| CCBStage | 100 | m_BFARound | `int` |
| CCBStage | 104 | m_ptMousePos | `tagPOINT` |
| CCBStage | 112 | m_nSelectedRole | `int` |
| CCBStage | 116 | m_bRoleSelected | `_BYTE[11]` |
| CCBStage | 127 | m_bHideSceneAndRole | `unsigned char` |
| CCBStage | 128 | m_fDamageNumPosY | `float[5]` |
| CCBStage | 148 | m_nTodo_094 | `int` |
| CCBStage | 152 | m_nStageStatus | `unsigned char` |
| CCBStage | 153 | m_nTodo_99 | `unsigned char` |
| CCBStage | 154 | m_nTodo_9A | `unsigned char` |
| CCBStage | 155 | m_nTodo_9B | `unsigned char` |
| CCBStage | 156 | m_nTaskCount | `int` |
| CCBStage | 160 | m_nClearRoleAllTask | `int` |
| CCBStage | 164 | m_nRoleSlot | `int` |
| CCBStage | 168 | m_TaskGroups | `CCBTaskGroup[256]` |
| CCBStage | 673960 | m_nTodo_A48A8 | `int` |
| CCBStage | 673984 | m_dwAniFlagOver | `unsigned int` |
| CCBStageCam | 692 | m_pStage | `CCBStage *` |
| CCBStageCam | 696 | m_pUtil | `CUtil *` |
| CCBStageCam | 700 | m_fLastMouseX | `float` |
| CCBStageCam | 704 | m_fLastMouseY | `float` |
| CCBStageCam | 712 | m_fp | `char *` |
| CCBStageCam | 728 | m_nTask | `int` |
| CCBStageCam | 732 | m_nCurTask | `int` |
| CCBStageCam | 736 | m_Task | `tagCamTask[50]` |
| CCBStageCam | 4736 | m_EditorCam | `tagCam[64]` |
| CCBStageEffect | 0 | m_DeltaTime | `double` |
| CCBStageEffect | 8 | m_pStage | `CCBStage *` |
| CCBStageEffect | 12 | m_pCBSystem | `CCBSystem *` |
| CCBStageEffect | 16 | m_EnvLight | `gbVolModNode` |
| CCBStageEffect | 236 | m_Light | `gbVolModNode[10]` |
| CCBStageEffect | 2436 | m_pGeomFlashEffect | `gbRenderEffect *` |
| CCBStageEffect | 2440 | m_pGeomFlashEffect_t | `gbRenderEffect *` |
| CCBStageEffect | 2444 | m_Linker | `tagEffLinker[4]` |
| CCBStageRole | 0 | m_pStage | `CCBStage *` |
| CCBStageRole | 4 | m_pRoleState | `CCBRoleState *` |
| CCBStageRole | 8 | m_sLastRole | `char[12]` |
| CCBStageRole | 20 | m_sRoleArray | `Array` |
| CCBStageRole | 36 | m_sRoleData | `char[228]` |
| CCBStageRole | 264 | m_bValid | `unsigned char` |
| CCBStageRole | 265 | m_bVisible | `unsigned char` |
| CCBStageRole | 266 | m_bPaused | `unsigned char` |
| CCBStageRole | 267 | m_bAbsTime | `unsigned char` |
| CCBStageRole | 268 | m_fTimeScale | `float` |
| CCBStageRole | 272 | m_bAlive | `unsigned char` |
| CCBStageRole | 273 | m_bRun | `unsigned char` |
| CCBStageRole | 274 | m_bFlash | `unsigned char` |
| CCBStageRole | 275 | m_bFlashCounter | `unsigned char` |
| CCBStageRole | 276 | m_fFlashTimeKey | `float` |
| CCBStageRole | 280 | m_bShowWeapon | `unsigned char` |
| CCBStageRole | 284 | m_fBlend | `float` |
| CCBStageRole | 288 | m_bBeSelected | `unsigned char` |
| CCBStageRole | 292 | m_nIndex | `int` |
| CCBStageRole | 296 | m_dwID | `unsigned int` |
| CCBStageRole | 300 | m_pActor | `Actor *` |
| CCBStageRole | 304 | m_pRawActor | `Actor *` |
| CCBStageRole | 308 | m_pWeaponModel | `gbGeomNode *` |
| CCBStageRole | 312 | m_vecWeapon | `gbVec3D` |
| CCBStageRole | 324 | m_rotWeapon | `gbVec3D` |
| CCBStageRole | 336 | m_vNoteThrowPos | `gbVec3D` |
| CCBStageRole | 348 | m_vThrowVec | `gbVec3D` |
| CCBStageRole | 360 | m_vecLen | `float` |
| CCBStageRole | 364 | m_fTask | `float` |
| CCBStageRole | 368 | m_fStatus | `float` |
| CCBStageRole | 372 | m_bShowWeaponModel | `unsigned char` |
| CCBStageRole | 373 | m_bCatching | `unsigned char` |
| CCBStageRole | 374 | m_bDelAllTask | `unsigned char` |
| CCBStageRole | 376 | m_iState | `int` |
| CCBStageRole | 380 | m_bForceFinishThrowingWeapon | `unsigned char` |
| CCBStageRole | 384 | m_fMaxThrowSpeed | `float` |
| CCBStageRole | 388 | m_fThrowSpeed | `float` |
| CCBStageRole | 392 | m_fThrowLen | `float` |
| CCBStageRole | 396 | m_ThrowCmdData | `tagCmdData *` |
| CCBStageRole | 400 | m_nRotAngle | `int` |
| CCBStageRole | 404 | m_nCurActionOff | `int` |
| CCBStageRole | 408 | m_nCurActionParam | `int` |
| CCBStageRole | 412 | m_nTodo_19C | `int` |
| CCBStageRole | 416 | m_nTransportRun | `int` |
| CCBStageRole | 420 | m_ActionSlot0 | `int` |
| CCBStageRole | 424 | m_ActionSlot1 | `int` |
| CCBStageRole | 428 | m_ActionSlot2 | `int` |
| CCBStageRole | 432 | m_nUseRecoverItem | `int` |
| CCBStageRole | 436 | m_nProperAction | `int` |
| CCBStageRole | 440 | m_OBBox | `gbOBBox *` |
| CCBStageRole | 444 | m_nOBBox | `int` |
| CCBStageRole | 448 | m_fActionSpeed0 | `int` |
| CCBStageRole | 452 | m_nTodo_1C4 | `int` |
| CCBStageRole | 472 | m_nTodo_1D8 | `int` |
| CCBStageRole | 484 | m_apSlotData | `int` |
| CCBStageRole | 488 | m_nTodo_1E8 | `float` |
| CCBStageRole | 496 | m_nCurState | `int` |
| CCBStageRole | 500 | m_nActionType0 | `int` |
| CCBStageRole | 504 | m_bProperCurAction | `unsigned char` |
| CCBStageRole | 505 | m_bSlotActive0 | `unsigned char` |
| CCBStageRole | 506 | m_bSlotBlocked0 | `unsigned char` |
| CCBStageRole | 516 | m_bTransMtl | `unsigned char` |
| CCBStageRole | 517 | m_bSpecTransport | `unsigned char` |
| CCBStageRole | 518 | m_bGrabed | `unsigned char` |
| CCBStageRole | 519 | m_bNormalGrab | `unsigned char` |
| CCBStageRole | 520 | m_dwStageTaskID | `unsigned int` |
| CCBStageRole | 524 | m_bExternalTask | `unsigned char` |
| CCBStageRole | 528 | m_fLeftWeapon | `float` |
| CCBStageRole | 532 | m_fRightWeapon | `float` |
| CCBStageRole | 536 | m_nTask | `int` |
| CCBStageRole | 540 | m_nCurTask | `int` |
| CCBStageRole | 544 | m_fp | `char *` |
| CCBStageRole | 560 | m_Task | `tagRoleTask[64]` |
| CCBStageRole | 6704 | m_dwCurWeaponIndex | `unsigned int` |
| CCBStageRole | 6708 | m_eRoleActState | `ERoleActState` |
| CCBStageRole | 6712 | m_eCurAction | `ACTION_KIND` |
| CCBStageRole | 6716 | m_vecSunDir | `gbVec3D` |
| CCBStageRole | 6728 | m_vecPos | `gbVec3D` |
| CCBStageRole | 6740 | m_vecInitPos | `gbVec3D` |
| CCBStageRole | 6752 | m_vecRunTarget | `gbVec3D` |
| CCBStageRole | 6764 | m_vecRunVelocity | `gbVec3D` |
| CCBStageRole | 6776 | m_fFaceDir | `float` |
| CCBStageRole | 6780 | m_fInitFaceDir | `float` |
| CCBStageRole | 6784 | m_dwCurAniFlag | `unsigned int` |
| CCBStageRole | 6788 | m_dwAniFlagOver | `unsigned int` |
| CCBStageRole | 6792 | m_dwAniFlagWork | `unsigned int` |
| CCBStageRole | 6796 | m_dwAniFlagWork1 | `unsigned int` |
| CCBStageRole | 6800 | m_dwAniFlagWork2 | `unsigned int` |
| CCBStageRole | 6804 | m_dwAniFlagWork3 | `unsigned int` |
| CCBStageRole | 6808 | m_dwAniFlagPause | `unsigned int` |
| CCBStageRole | 6812 | m_dwAniFlagStore | `unsigned int` |
| CCBStageRole | 6816 | m_dwAniFlagFlyup | `unsigned int` |
| CCBStageRole | 6820 | m_dwAniFlagFlydown | `unsigned int` |
| CCBStageRole | 6824 | m_dwAniFlagThrowED | `unsigned int` |
| CCBStageRole | 6828 | m_dwAniFlagCatchED | `unsigned int` |
| CCBStageRole | 6832 | m_dwAniFlagSJump | `unsigned int` |
| CCBStageRole | 6836 | m_dwAniFlagEJump | `unsigned int` |
| CCBStageRole | 6840 | m_dwLastExternalActionCRC | `unsigned int` |
| CCBStageScene | 0 | m_pStage | `CCBStage *` |
| CCBStageScene | 4 | m_pUtil | `CUtil *` |
| CCBStageScene | 8 | m_vecFiveLineup | `gbVec3D[7]` |
| CCBStageScene | 92 | m_vecInitFiveLineup | `gbVec3D[3]` |
| CCBStageScene | 128 | m_nRender | `int` |
| CCBStageScene | 132 | m_fLineupCamY | `float` |
| CCBStageScene | 136 | m_fLineupCamZ | `float` |
| CCBStageScene | 140 | m_fRender | `float` |
| CCBStageScene | 144 | m_fLineupPrevY | `float` |
| CCBStageScene | 148 | m_fLineupPrevZ | `float` |
| CCBStageScene | 152 | m_fLineupDefaultX | `float` |
| CCBStageScene | 156 | m_fLineupDefaultY | `float` |
| CCBStageScene | 160 | m_fLineupDefaultZ | `float` |
| CCBStageScene | 164 | m_fLineupExtraX | `float` |
| CCBStageScene | 168 | m_fLineupExtraY | `float` |
| CCBStageScene | 172 | m_fLineupExtraZ | `float` |
| CCBStageScene | 176 | m_vecEnemyLineup | `gbVec3D[7]` |
| CCBStageScene | 260 | m_vecInitEnemyLineup | `gbVec3D[7]` |
| CCBStageScene | 344 | m_bLoaded | `unsigned char` |
| CCBStageScene | 345 | m_sLastScene | `char[256]` |
| CCBStageScene | 604 | m_pGeomNode | `gbGeomNode *` |
| CCBStageScene | 608 | m_pCvd | `gbGeomNode *` |
| CCBStageScene | 612 | m_pLights | `gbVisNode *` |
| CCBStageScene | 616 | m_pPointer | `gbGeomNode *` |
| CCBStageScene | 620 | m_pCorpse | `gbGeomNode *[11]` |
| CCBStageScene | 664 | m_pFling | `gbGeomNode *` |
| CCBStageScene | 668 | m_vecFling | `float` |
| CCBStageScene | 672 | m_nLoadPointer | `int` |
| CCBStageScene | 676 | m_nFlingState | `int` |
| CCBStageScene | 680 | m_rotFling | `float` |
| CCBStageScene | 684 | m_fDirSinA | `float` |
| CCBStageScene | 688 | m_fBlendA | `float` |
| CCBStageScene | 692 | m_bShowFling | `unsigned char` |
| CCBStageScene | 696 | m_pFiveLineupEffect | `gbRenderEffect *` |
| CCBStageScene | 700 | m_pFiveLineupTexture | `gbTexture *` |
| CCBStageScene | 704 | m_pFiveLineupTextureArray | `gbTextureArray *` |
| CCBStageScene | 708 | m_pFiveLineupCenterTexture | `gbTexture *` |
| CCBStageScene | 712 | m_pFiveLineupCenterTextureArray | `gbTextureArray *` |
| CCBStageScene | 716 | m_FiveLineupQuad | `gbGeomQuad *` |
| CCBStageScene | 720 | m_fDirSinB | `float` |
| CCBStageScene | 724 | m_fBlendB | `float` |
| CCBStageScene | 728 | m_fDirCosB | `float` |
| CCBStageScene | 732 | m_fBlendRectAX | `float` |
| CCBStageScene | 736 | m_fBlendRectAY | `float` |
| CCBStageScene | 740 | m_fBlendRectAW | `float` |
| CCBStageScene | 744 | m_fBlendRectAH | `float` |
| CCBStageScene | 748 | m_bLoadPointer | `unsigned char` |
| CCBStageScene | 749 | m_nPointerIndex1 | `unsigned char` |
| CCBStageScene | 750 | m_nPointerIndex2 | `unsigned char` |
| CCBStageScene | 751 | m_nPointerData | `unsigned char` |
| CCBStageScene | 752 | m_nInit | `int` |
| CCBStageScene | 756 | m_nCamState | `int` |
| CCBStageScene | 760 | m_fCamPosX | `float` |
| CCBStageScene | 764 | m_fCamPosZ | `float` |
| CCBStageScene | 768 | m_fInit | `float` |
| CCBStageScene | 772 | m_fCamTargX | `float` |
| CCBStageScene | 776 | m_fCamTargZ | `float` |
| CCBStageScene | 780 | m_fInitBlend | `float` |
| CCBStageScene | 784 | m_FiveLineupCenterQuad | `gbGeomQuad *` |
| CCBStageScene | 788 | m_fBlendTime | `float` |
| CCBStageScene | 792 | m_nBlendState | `int` |
| CCBStageScene | 796 | m_fBlendSpeed | `float` |
| CCBStageScene | 800 | m_fBlendRectBX | `float` |
| CCBStageScene | 804 | m_fBlendRectBY | `float` |
| CCBStageScene | 808 | m_fBlendRectBW | `float` |
| CCBStageScene | 812 | m_fBlendRectBH | `float` |
| CCBStageScene | 816 | m_nReset | `int` |
| CCBStageScene | 820 | m_fDirSinC | `float` |
| CCBStageScene | 824 | m_fBlendC | `float` |
| CCBStageScene | 828 | m_fDirCosC | `float` |
| CCBStageScene | 832 | m_fDirSinD | `float` |
| CCBStageScene | 836 | m_fBlendD | `float` |
| CCBStageScene | 840 | m_fDirCosD | `float` |
| CCBStageScene | 844 | m_fDirSinE | `float` |
| CCBStageScene | 848 | m_fBlendE | `float` |
| CCBStageScene | 852 | m_EnemyFiveLineupQuad | `gbGeomQuad *` |
| CCBStageScene | 856 | m_fDirSinF | `float` |
| CCBStageScene | 860 | m_fBlendF | `float` |
| CCBStageScene | 864 | m_fDirCosF | `float` |
| CCBStageScene | 868 | m_fBlendWeight0 | `float` |
| CCBStageScene | 872 | m_fBlendWeight1 | `float` |
| CCBStageScene | 876 | m_fBlendWeight2 | `float` |
| CCBStageScene | 880 | m_fBlendWeight3 | `float` |
| CCBStageScene | 888 | m_fCurAxisX | `float` |
| CCBStageScene | 892 | m_fCurAxisY | `float` |
| CCBStageScene | 896 | m_fCurAxisZ | `float` |
| CCBStageScene | 900 | m_fInitAxisX | `float` |
| CCBStageScene | 904 | m_fInitAxisY | `float` |
| CCBStageScene | 908 | m_fInitAxisZ | `float` |
| CCBStageScene | 912 | m_fCurRotParam | `float` |
| CCBStageScene | 916 | m_fInitRotParam | `float` |
| CCBStageScene | 920 | m_vecFiveLineupPos | `gbVec3D` |
| CCBStageScene | 932 | m_vecFiveLineupInitPos | `gbVec3D` |
| CCBStageScene | 944 | m_fFiveLineupRadius | `float` |
| CCBStageScene | 948 | m_fFiveLineupInitRadius | `float` |
| CCBStageScene | 952 | m_fFiveLineupRoll | `float` |
| CCBStageScene | 956 | m_fFiveLineupInitRoll | `float` |
| CCBStageScene | 960 | m_vecEnemyFiveLineupPos | `gbVec3D` |
| CCBStageScene | 972 | m_fEnemyFiveLineupRadius | `float` |
| CCBStageScene | 976 | m_fEnemyFiveLineupRoll | `float` |
| CCBStageScene | 980 | m_vecPointerPos | `gbVec3D` |
| CCBStageScene | 992 | m_bShowPointer | `unsigned char` |
| CCBStageScene | 993 | m_bShowAxis | `unsigned char` |
| CCBStageScene | 994 | m_bShowRoleIndex | `unsigned char` |
| CCBStageScene | 995 | m_bShowFiveLineup | `unsigned char` |
| CCBStageScene | 996 | m_bFiveLineupSelected | `unsigned char` |
| CCBStageScene | 1000 | m_eSceneFiveMagicAttrib | `ECBFiveMagic` |
| CCBStageScene | 1004 | m_eBattleFieldAttr | `ECBBattleFieldAttr` |
| CCBStageScene | 1008 | m_eBFAForce | `ECBForce` |
| CCBStageShadow | 0 | m_pStage | `CCBStage *` |
| CCBStageShadow | 4 | m_pTexture | `gbTexture *` |
| CCBStageShadow | 8 | m_pEffect | `gbRenderEffect *` |
| CCBStageShadow | 12 | m_pTextureArray | `gbTextureArray *` |
| CCBStageShadow | 16 | m_ShadowInitQuad | `gbGeomQuad[11]` |
| CCBStageShadow | 764 | m_ShadowQuad | `gbGeomQuad[11]` |
| CCBStageShadow | 1512 | m_fShadowRadius | `float[11]` |
| CCBSystem | 0 | m_pUtil | `CCBSystem *` |
| CCBSystem | 4 | m_pUI | `CCBUI *` |
| CCBSystem | 8 | m_pControl | `CCBControl *` |
| CCBSystem | 12 | m_pAttackSequen | `CCBAttackSequen *` |
| CCBSystem | 16 | m_pRoleState | `CCBRoleState *` |
| CCBSystem | 20 | m_pStage | `CCBStage *` |
| CCBSystem | 24 | m_pAI | `CCBAI *` |
| CCBSystem | 28 | m_pEditor | `CCBEditor *` |
| CCBSystem | 32 | m_pES | `CEffectSystem *` |
| CCBSystem | 36 | m_pEffectSimple | `CEffectSimple *` |
| CCBSystem | 40 | m_pConfig | `TxtFile *` |
| CCBSystem | 44 | m_pEffMgr | `CEffMgr *` |
| CCBSystem | 48 | m_pATSEffMgr | `CEffMgr *` |
| CCBSystem | 52 | m_p2DSpark | `C2DSpark *` |
| CCBSystem | 56 | m_p3DSpark | `C3DSpark *` |
| CCBSystem | 64 | m_DeltaTime | `double` |
| CCBSystem | 72 | m_dTimeFund | `double` |
| CCBSystem | 80 | m_fTimeFund | `float` |
| CCBSystem | 88 | m_AbsDeltaTime | `double` |
| CCBSystem | 96 | m_dAbsTimeFund | `double` |
| CCBSystem | 104 | m_fAbsTimeFund | `float` |
| CCBSystem | 108 | m_fTimeScale | `float` |
| CCBSystem | 112 | m_pFightInfo | `FightInfo *` |
| CCBSystem | 116 | m_bQuitFlag | `unsigned char` |
| CCBSystem | 117 | m_bPause | `unsigned char` |
| CCBSystem | 120 | m_eState | `ECBCombatState` |
| CCBSystem | 124 | m_eResult | `ECBCombatResult` |
| CCBSystem | 128 | m_bFiveNimbus | `unsigned char` |
| CCBSystem | 129 | m_bPXVariance | `unsigned char` |
| CCBSystem | 132 | m_nTimesOfCombat | `int` |
| CCBSystem | 136 | m_bAuto | `unsigned char` |
| CCBSystem | 137 | m_bEditor | `unsigned char` |
| CCBSystem | 138 | m_bLockCam | `unsigned char` |
| CCBSystem | 139 | m_bFirstRender | `unsigned char` |
| CCBSystem | 140 | m_dwIDHolder | `unsigned int` |
| CCBSystem | 144 | m_nThread | `int` |
| CCBSystem | 148 | m_nCurThread | `int` |
| CCBSystem | 152 | m_Thread | `tagThread[1024]` |
| CCBSystem | 90264 | m_Player | `tagPlayerSet[11]` |
| CCBTaskGroup | 0 | m_nTaskId | `int` |
| CCBTaskGroup | 4 | m_nState | `int` |
| CCBTaskGroup | 8 | m_nCurSlot | `int` |
| CCBTaskGroup | 16 | m_Slots | `CCBTaskSlot[32]` |
| CCBTaskGroup | 2576 | m_nEndFlag | `int` |
| CCBTaskGroup | 2580 | m_nDelResult | `int` |
| CCBTaskGroup | 2628 | m_bInUse | `unsigned char` |
| CCBTaskSlot | 0 | m_nTaskFn | `int` |
| CCBTaskSlot | 4 | m_nTaskArg0 | `int` |
| CCBTaskSlot | 8 | m_nTaskArg1 | `int` |
| CCBTaskSlot | 12 | m_nTaskArg2 | `int` |
| CCBTaskSlot | 16 | m_nState | `int` |
| CCBTaskSlot | 24 | m_fStartTime | `float` |
| CCBTaskSlot | 28 | m_fMaxWait | `float` |
| CCBTaskSlot | 32 | m_fDuration | `float` |
| CCBTaskSlot | 36 | m_nActionId | `int` |
| CCBTaskSlot | 40 | m_bActive | `unsigned char` |
| CCBTaskSlot | 41 | m_bRegistered | `unsigned char` |
| CCBTaskSlot | 43 | m_bForceDone | `unsigned char` |
| CCBTaskSlot | 64 | m_nTurnState | `int` |
| CCBTaskSlot208 | 0 | m_nBase | `int` |
| CCBTaskSlot208 | 20 | m_nSize | `int` |
| CCBTaskSlot208 | 24 | m_nId | `int` |
| CCBTaskSlot208 | 80 | m_nCounter | `int` |
| CCBTaskSlot208 | 96 | m_fVal0 | `float` |
| CCBTaskSlot208 | 100 | m_fVal1 | `float` |
| CCBTaskSlot208 | 104 | m_fVal2 | `float` |
| CCBTaskSlot208 | 108 | m_fVal3 | `float` |
| CCBTaskSlot208 | 112 | m_fVal4 | `float` |
| CCBTaskSlot208 | 116 | m_fVal5 | `float` |
| CCBTaskSlot208 | 144 | m_ptrC | `void *` |
| CCBTaskSlot208 | 184 | _ovl_0B8 | `_BYTE[24]` |
| CCBUI | 72 | m_pBack | `UIStatic *` |
| CCBUI | 76 | m_pWHFace | `UIPushButton *` |
| CCBUI | 80 | m_pWPXFace | `UIPushButton *` |
| CCBUI | 84 | m_pWHLove | `UIProgressBar *` |
| CCBUI | 88 | m_pWPXLove | `UIProgressBar *` |
| CCBUI | 92 | m_pOk | `UIButton *` |
| CCBUI | 104 | m_pAttackSequenFace | `UIStatic *[11]` |
| CCBUI | 148 | m_pRoleStatePanel | `UIStatic *[4]` |
| CCBUI | 164 | m_pRoleStateFace | `UIStatic *[5]` |
| CCBUI | 184 | m_pRoleStateFaceName | `UIStatic *[5]` |
| CCBUI | 204 | m_pRoleStateAttackInc | `UIStatic *[11]` |
| CCBUI | 248 | m_pRoleStateAttackDec | `UIStatic *[11]` |
| CCBUI | 292 | m_pRoleStateDefenceInc | `UIStatic *[11]` |
| CCBUI | 336 | m_pRoleStateDefenceDec | `UIStatic *[11]` |
| CCBUI | 380 | m_pRoleStateLuckInc | `UIStatic *[11]` |
| CCBUI | 424 | m_pRoleStateLuckDec | `UIStatic *[11]` |
| CCBUI | 468 | m_pRoleStateSpeedInc | `UIStatic *[11]` |
| CCBUI | 512 | m_pRoleStateSpeedDec | `UIStatic *[11]` |
| CCBUI | 556 | m_pRoleStateStable | `UIStatic *[11]` |
| CCBUI | 600 | m_pRoleStateBlank | `UIStatic *[11]` |
| CCBUI | 644 | m_pRoleStateForbid | `UIStatic *[11]` |
| CCBUI | 688 | m_pRoleStateSleep | `UIStatic *[11]` |
| CCBUI | 732 | m_pRoleStateChaos | `UIStatic *[11]` |
| CCBUI | 776 | m_pRoleStateMad | `UIStatic *[11]` |
| CCBUI | 820 | m_pRoleStateMirror | `UIStatic *[11]` |
| CCBUI | 864 | m_pRoleStateWall | `UIStatic *[11]` |
| CCBUI | 908 | m_pRoleStateBound | `UIStatic *[11]` |
| CCBUI | 952 | m_pRoleStateHermit | `UIStatic *[11]` |
| CCBUI | 996 | m_pRoleStateImmunity | `UIStatic *[11]` |
| CCBUI | 1040 | m_pWinPanel | `UIStatic *` |
| CCBUI | 1044 | m_pLosePanel | `UIStatic *` |
| CCBUI | 1048 | m_pRoleStateHP | `UIProgressBar *[4]` |
| CCBUI | 1064 | m_pRoleStateGP | `UIProgressBar *[4]` |
| CCBUI | 1080 | m_pRoleStateMP | `UIProgressBar *[4]` |
| CCBUI | 1096 | m_pRoleStateSword | `UIProgressBar *` |
| CCBUI | 1100 | m_pTrickName | `UIStaticCB *` |
| CCBUI | 1104 | m_pTrickName2 | `UIStaticCB *` |
| CCBUI | 1108 | m_pDialogBack | `UIStatic *` |
| CCBUI | 1112 | m_pResultLevelup | `UIStatic *` |
| CCBUI | 1116 | m_pResultWindLvup | `UIStatic *` |
| CCBUI | 1120 | m_pResultThunderLvup | `UIStatic *` |
| CCBUI | 1124 | m_pResultWaterLvup | `UIStatic *` |
| CCBUI | 1128 | m_pResultFireLvup | `UIStatic *` |
| CCBUI | 1132 | m_pResultEarthLvup | `UIStatic *` |
| CCBUI | 1136 | m_pResultDoubleLvup | `UIStatic *` |
| CCBUI | 1140 | m_pResultGetItem | `UIStatic *` |
| CCBUI | 1144 | m_pMain | `CCBControlWindow *` |
| CCBUI | 1148 | m_pItemWindow | `CCBItemWindow *` |
| CCBUI | 1152 | m_pParabolaWindow | `CCBParabolaWindow *` |
| CCBUI | 1156 | m_pMagicWindow | `CCBMagicWindow *` |
| CCBUI | 1160 | m_pSkillWindow | `CCBSkillWindow *` |
| CCBUI | 1164 | m_pAIWindow | `CCBAIWindow *` |
| CCBUI | 1168 | m_pLineupWindow | `CCBLineupWindow *` |
| CCBUI | 1172 | m_pProtectWindow | `CCBProtectWindow *` |
| CCBUI | 1176 | m_pResultWindow | `CCBResultWindow *[4]` |
| CCBUI | 1192 | m_pFiveNimbusWindow | `CCBFiveNimbusWindow *` |
| CCBUI | 1196 | m_pCBSystem | `CCBSystem *` |
| CCBUI | 1200 | m_pUtil | `CUtil *` |
| CCBUI | 1208 | m_Task | `tagUITask[19]` |
| CCBUICtrl | 72 | _todo_48 | `UIWnd *` |
| CCBUICtrl | 76 | _todo_4C | `UIWnd *[10]` |
| CCBUIPanel | 1344 | m_nPanelOffsetX | `int` |
| CCBUIPanel | 1348 | m_nPanelOffsetY | `int` |
| CCBUIPanel | 1468 | m_nPanelX | `int` |
| CCBUIPanel | 1472 | m_nPanelY | `int` |
| CCBUIPanel | 1476 | m_nChildX | `int` |
| CCBUIPanel | 1480 | m_nChildY | `int` |
| CCBUIPanel | 1484 | m_nChildW | `int` |
| CCBUIPanel | 1488 | m_nChildH | `int` |
| CCBUIPanel | 1492 | m_nBorderL | `int` |
| CCBUIPanel | 1496 | m_nBorderR | `int` |
| CCBUIPanel | 1500 | m_fPanelW | `float` |
| CCBUIPanel | 1504 | m_fPanelH | `float` |
| CCBUIPanel | 1508 | m_nGridX | `int` |
| CCBUIPanel | 1512 | m_nGridY | `int` |
| CCBUIPanel | 1516 | m_nGridW | `int` |
| CCBUIPanel | 1520 | m_nGridH | `int` |
| CCBUIPanel | 1524 | m_nItemW | `int` |
| CCBUIPanel | 1528 | m_nItemH | `int` |
| CCBUIPanel | 1532 | m_nSpacingX | `int` |
| CCBUIPanel | 1536 | m_nSpacingY | `int` |
| CCBUIPanel | 1540 | m_nItemNum | `int` |
| CCBUIPanel | 1544 | m_nMaxItemNum | `int` |
| CCBUIPanel | 1560 | m_pVfTable | `char *` |
| CCBUIPanel | 1792 | m_SubPanel1 | `void *` |
| CCBUIPanel | 2136 | m_Static_2136 | `UIStatic` |
| CCBUIPanel | 2288 | m_Static_2288 | `UIStatic` |
| CCBUIPanel | 2440 | m_Static_2440 | `UIStatic` |
| CCBUIPanel | 2592 | m_Static_2592 | `UIStatic` |
| CCBUIPanel | 2744 | m_Static_2744 | `UIStatic` |
| CCBUIPanel | 2896 | m_SubPanel2 | `void *` |
| CCBUIPanel | 3240 | m_SubPanel3 | `void *` |
| CCBUIPanel | 3584 | m_SubPanel4 | `void *` |
| CCBUIPanel | 3928 | m_SubRoleDialog | `void *` |
| CCBUIPanel | 4316 | m_bActive | `unsigned char` |
| CCBUIPanel | 4324 | m_Slots | `CCBPanelSlot[30]` |
| CCBUIPanel | 18604 | m_nSlotBaseX | `int` |
| CCBUIPanel | 18608 | m_nSlotStepX | `int` |
| CCBUIPanel | 18612 | m_nSlotBaseY | `int` |
| CCBUIPanel | 18616 | m_EmbedPalScript | `int` |
| CCBUIPanel | 18780 | m_fSlotRefX | `float` |
| CCBUIPanel | 18784 | m_fSlotRefY | `float` |
| CCBUIPanel | 18788 | m_nSlotCalcA | `int` |
| CCBUIPanel | 18792 | m_nSlotCalcB | `int` |
| CCBUIPanel | 18796 | m_nSlotCalcC | `int` |
| CCBUIPanel | 18800 | m_nSlotCalcD | `int` |
| CCBUIPanel | 18804 | m_fSlotCalcX2 | `float` |
| CCBUIPanel | 18808 | m_fSlotCalcY2 | `float` |
| CCBUIPanel | 18824 | m_bSlotFlags | `int` |
| CCBUIPanel | 18828 | m_fSlotParam | `float` |
| CCBUIPanel | 18832 | m_bEnsureSize | `int` |
| CCBUIPanel | 18836 | m_nActiveSlot | `int` |
| CCBUIPanel | 18840 | m_EmbedPlayerAtt | `int` |
| CCBUIPanel | 19296 | m_SubCaptionGroup | `void *` |
| CCBUIPanel | 20208 | m_nPlayerAttOverlay | `int` |
| CCBUIPanel | 20560 | m_nReserved5050 | `int` |
| CCBUIPanel | 20564 | m_nReserved5054 | `int` |
| CCBUIPanel | 20664 | m_EmbedCaption | `void *` |
| CCBUIPanel | 21556 | m_Data | `char[512]` |
| CCBUI_funcptr_t | 0 | fp | `char *` |
| CCBUI_funcptr_t | 4 | fp_data | `unsigned int[3]` |
| CCCTData | 0 | m_Pool | `tagCCT[2000]` |
| CCCTData | 408000 | m_bPoolInUse | `_BYTE[2000]` |
| CCCTData | 410000 | m_nCCTIndex | `int[50][100]` |
| CD3DEnumeration | 0 | m_pD3D | `IDirect3D9 *` |
| CD3DEnumeration | 4 | m_pAdapterInfoList | `CArrayList *` |
| CD3DEnumeration | 8 | ConfirmDeviceCallback | `char *` |
| CD3DEnumeration | 12 | AppMinFullscreenWidth | `unsigned int` |
| CD3DEnumeration | 16 | AppMinFullscreenHeight | `unsigned int` |
| CD3DEnumeration | 20 | AppMinColorChannelBits | `unsigned int` |
| CD3DEnumeration | 24 | AppMinAlphaChannelBits | `unsigned int` |
| CD3DEnumeration | 28 | AppMinDepthBits | `unsigned int` |
| CD3DEnumeration | 32 | AppMinStencilBits | `unsigned int` |
| CD3DEnumeration | 36 | AppUsesDepthBuffer | `unsigned char` |
| CD3DEnumeration | 37 | AppUsesMixedVP | `unsigned char` |
| CD3DEnumeration | 38 | AppRequiresWindowed | `unsigned char` |
| CD3DEnumeration | 39 | AppRequiresFullscreen | `unsigned char` |
| CD3DEnumeration | 40 | m_pAllowedAdapterFormatList | `CArrayList *` |
| CD3DSettings | 0 | IsWindowed | `unsigned char` |
| CD3DSettings | 4 | pWindowed_AdapterInfo | `D3DAdapterInfo *` |
| CD3DSettings | 8 | pWindowed_DeviceInfo | `D3DDeviceInfo *` |
| CD3DSettings | 12 | pWindowed_DeviceCombo | `D3DDeviceCombo *` |
| CD3DSettings | 16 | Windowed_DisplayMode | `_D3DDISPLAYMODE` |
| CD3DSettings | 32 | Windowed_DepthStencilBufferFormat | `_D3DFORMAT` |
| CD3DSettings | 36 | Windowed_MultisampleType | `_D3DMULTISAMPLE_TYPE` |
| CD3DSettings | 40 | Windowed_MultisampleQuality | `unsigned int` |
| CD3DSettings | 44 | Windowed_VertexProcessingType | `VertexProcessingType` |
| CD3DSettings | 48 | Windowed_PresentInterval | `unsigned int` |
| CD3DSettings | 52 | Windowed_Width | `int` |
| CD3DSettings | 56 | Windowed_Height | `int` |
| CD3DSettings | 60 | pFullscreen_AdapterInfo | `D3DAdapterInfo *` |
| CD3DSettings | 64 | pFullscreen_DeviceInfo | `D3DDeviceInfo *` |
| CD3DSettings | 68 | pFullscreen_DeviceCombo | `D3DDeviceCombo *` |
| CD3DSettings | 72 | Fullscreen_DisplayMode | `_D3DDISPLAYMODE` |
| CD3DSettings | 88 | Fullscreen_DepthStencilBufferFormat | `_D3DFORMAT` |
| CD3DSettings | 92 | Fullscreen_MultisampleType | `_D3DMULTISAMPLE_TYPE` |
| CD3DSettings | 96 | Fullscreen_MultisampleQuality | `unsigned int` |
| CD3DSettings | 100 | Fullscreen_VertexProcessingType | `VertexProcessingType` |
| CD3DSettings | 104 | Fullscreen_PresentInterval | `unsigned int` |
| CEffAction | 48 | m_nController | `int` |
| CEffAudio | 48 | m_szSoundNamePrefix | `char[128]` |
| CEffAudio | 176 | m_szSoundName | `char[128][4]` |
| CEffBase | 4 | m_pEffectSystem | `CEffectSystem *` |
| CEffBase | 8 | m_eKind | `int` |
| CEffBase | 12 | m_nTaskIndex | `int` |
| CEffBase | 16 | m_fPrevTime | `float` |
| CEffBase | 20 | m_fDeltaTime | `float` |
| CEffBase | 24 | m_pSegData | `char *` |
| CEffBase | 28 | m_fDuration | `float` |
| CEffBase | 32 | m_fTimeScale | `float` |
| CEffBase | 36 | m_nMaxTask | `int` |
| CEffBase | 40 | m_nSegments | `int` |
| CEffBase | 44 | m_nVertPerSeg | `int` |
| CEffBink | 48 | m_szBinkNamePrefix | `char[128]` |
| CEffBink | 176 | m_szBinkName | `char[128]` |
| CEffCallBack | 48 | m_fStartX | `float` |
| CEffCallBack | 52 | m_fStartY | `float` |
| CEffCallBack | 56 | m_fStartZ | `float` |
| CEffCallBack | 60 | m_dwRunningID | `unsigned int` |
| CEffCustomShape | 48 | m_bVisible | `unsigned char` |
| CEffCustomShape | 52 | m_vecPos | `gbVec3D` |
| CEffCustomShape | 64 | m_vecOffsetPos | `gbVec3D` |
| CEffCustomShape | 76 | m_vecRot | `gbVec3D` |
| CEffCustomShape | 88 | m_fAlpha | `float` |
| CEffCustomShape | 92 | m_fRed | `float` |
| CEffCustomShape | 96 | m_fGreen | `float` |
| CEffCustomShape | 100 | m_fBlue | `float` |
| CEffCustomShape | 104 | m_fScaleX | `float` |
| CEffCustomShape | 108 | m_fScaleY | `float` |
| CEffCustomShape | 112 | m_fScaleZ | `float` |
| CEffCustomShape | 116 | m_pModel | `t3DModel *` |
| CEffCustomShape | 120 | m_pTexture | `gbTexture *` |
| CEffCustomShape | 124 | m_pRenderEffect | `gbRenderEffect *` |
| CEffCustomShape | 128 | m_pIndexBubble | `gbIndexBubble *` |
| CEffCustomShape | 132 | m_nCurrFrame | `int` |
| CEffCustomShape | 136 | m_nFrameNum | `int` |
| CEffCustomShape | 140 | m_fFrameU | `float` |
| CEffCustomShape | 144 | m_fFrameV | `float` |
| CEffCustomShape | 148 | m_fSpeed | `float` |
| CEffCustomShape | 152 | m_fTimeCount | `float` |
| CEffCustomShape | 156 | m_UVData | `char[16]` |
| CEffCylinder | 48 | m_pGeomQuad | `gbGeomQuad *` |
| CEffCylinder | 52 | m_pTexture | `gbTexture *` |
| CEffCylinder | 56 | m_pTextureArray | `gbTextureArray *` |
| CEffCylinder | 60 | m_bVisible | `unsigned char` |
| CEffCylinder | 61 | m_bAdditiveBlend | `unsigned char` |
| CEffCylinder | 62 | m_bNoZTest | `unsigned char` |
| CEffCylinder | 63 | m_byMaxFrame | `unsigned char` |
| CEffCylinder | 64 | m_nRequireLoops | `int` |
| CEffCylinder | 68 | m_nLoops | `int` |
| CEffCylinder | 72 | m_fCurFrame | `float` |
| CEffCylinder | 76 | m_dwStartColor | `unsigned int` |
| CEffCylinder | 80 | m_fAlpha | `float` |
| CEffCylinder | 84 | m_fRed | `float` |
| CEffCylinder | 88 | m_fGreen | `float` |
| CEffCylinder | 92 | m_fBlue | `float` |
| CEffCylinder | 96 | m_fSize | `float` |
| CEffCylinder | 100 | m_fHeight | `float` |
| CEffCylinder | 104 | m_fRotAngle | `float` |
| CEffCylinder | 108 | m_fWide | `float` |
| CEffCylinder | 112 | m_nDivision | `int` |
| CEffCylinder | 116 | m_fTopShrink | `float` |
| CEffCylinder | 120 | m_fBottomShrink | `float` |
| CEffCylinder | 124 | m_fTopRadius | `float` |
| CEffCylinder | 128 | m_fBottomRadius | `float` |
| CEffCylinder | 132 | m_fTopRadiusIncSpeed | `float` |
| CEffCylinder | 136 | m_fBottomRadiusIncSpeed | `float` |
| CEffCylinder | 140 | m_fTopRiseSpeed | `float` |
| CEffCylinder | 144 | m_fBottomRiseSpeed | `float` |
| CEffCylinder | 148 | m_fTextureRepeat | `float` |
| CEffCylinder | 152 | m_fFramePerSec | `float` |
| CEffCylinder | 156 | m_fCurTextureV | `float` |
| CEffCylinder | 160 | m_vecRot | `gbVec3D` |
| CEffCylinder | 172 | m_vecPos | `gbVec3D` |
| CEffCylinder | 184 | m_vecOffsetPos | `gbVec3D` |
| CEffCylinder | 196 | m_DefaultUVSet | `tagUV[256]` |
| CEffExplosive | 48 | m_pGeomQuad | `gbGeomQuad *` |
| CEffExplosive | 52 | m_pExplosive | `tagExplosive *` |
| CEffExplosive | 56 | m_pTexture | `gbTexture *` |
| CEffExplosive | 60 | m_pTextureArray | `gbTextureArray *` |
| CEffExplosive | 64 | m_bVisible | `unsigned char` |
| CEffExplosive | 65 | m_bAdditiveBlend | `unsigned char` |
| CEffExplosive | 66 | m_bNoZTest | `unsigned char` |
| CEffExplosive | 67 | m_byMaxFrame | `unsigned char` |
| CEffExplosive | 68 | m_nRequireLoops | `int` |
| CEffExplosive | 72 | m_nLoops | `int` |
| CEffExplosive | 76 | m_fCurFrame | `float` |
| CEffExplosive | 80 | m_dwStartColor | `unsigned int` |
| CEffExplosive | 84 | m_fAlpha | `float` |
| CEffExplosive | 88 | m_fRed | `float` |
| CEffExplosive | 92 | m_fGreen | `float` |
| CEffExplosive | 96 | m_fBlue | `float` |
| CEffExplosive | 100 | m_fXSize | `float` |
| CEffExplosive | 104 | m_fZSize | `float` |
| CEffExplosive | 108 | m_nXDivision | `int` |
| CEffExplosive | 112 | m_nZDivision | `int` |
| CEffExplosive | 116 | m_fGridSize | `float` |
| CEffExplosive | 120 | m_nQuad | `int` |
| CEffExplosive | 124 | m_fMaxExplosivePower | `float` |
| CEffExplosive | 128 | m_fMinExplosivePower | `float` |
| CEffExplosive | 132 | m_vecExplosiveDir | `gbVec3D` |
| CEffExplosive | 144 | m_fPowerDec | `float` |
| CEffExplosive | 148 | m_fFramePerSec | `float` |
| CEffExplosive | 152 | m_vecRot | `gbVec3D` |
| CEffExplosive | 164 | m_vecPos | `gbVec3D` |
| CEffExplosive | 176 | m_vecOffsetPos | `gbVec3D` |
| CEffExplosive | 188 | m_fResistance | `float` |
| CEffExplosive | 192 | m_DefaultUVSet | `tagUV[256]` |
| CEffGrid | 48 | m_pGeomQuad | `gbGeomQuad *` |
| CEffGrid | 52 | m_pMesh | `gbVec3D *` |
| CEffGrid | 56 | m_pMesh2 | `gbVec3D *` |
| CEffGrid | 60 | m_pTexture | `gbTexture *` |
| CEffGrid | 64 | m_pTextureArray | `gbTextureArray *` |
| CEffGrid | 68 | m_bVisible | `unsigned char` |
| CEffGrid | 69 | m_bAdditiveBlend | `unsigned char` |
| CEffGrid | 70 | m_bNoZTest | `unsigned char` |
| CEffGrid | 71 | m_byMaxFrame | `unsigned char` |
| CEffGrid | 72 | m_nRequireLoops | `int` |
| CEffGrid | 76 | m_nLoops | `int` |
| CEffGrid | 80 | m_fCurFrame | `float` |
| CEffGrid | 84 | m_dwStartColor | `unsigned int` |
| CEffGrid | 88 | m_fAlpha | `float` |
| CEffGrid | 92 | m_fRed | `float` |
| CEffGrid | 96 | m_fGreen | `float` |
| CEffGrid | 100 | m_fBlue | `float` |
| CEffGrid | 104 | m_fXSize | `float` |
| CEffGrid | 108 | m_fZSize | `float` |
| CEffGrid | 112 | m_nXDivision | `int` |
| CEffGrid | 116 | m_nZDivision | `int` |
| CEffGrid | 120 | m_fGridSize | `float` |
| CEffGrid | 124 | m_nQuad | `int` |
| CEffGrid | 128 | m_fWavePower | `float` |
| CEffGrid | 132 | m_fWaveSpeed | `float` |
| CEffGrid | 136 | m_fFlapPower | `float` |
| CEffGrid | 140 | m_fFlapSpeed | `float` |
| CEffGrid | 144 | m_fFramePerSec | `float` |
| CEffGrid | 148 | m_vecRot | `gbVec3D` |
| CEffGrid | 160 | m_vecPos | `gbVec3D` |
| CEffGrid | 172 | m_vecOffsetPos | `gbVec3D` |
| CEffGrid | 184 | m_DefaultUVSet | `tagUV[256]` |
| CEffGroupNode | 92 | m_nTodo_05C | `int` |
| CEffGroupNode | 96 | m_nTodo_060 | `int` |
| CEffGroupNode | 100 | m_nTodo_064 | `int` |
| CEffGroupNode | 104 | m_nTodo_068 | `int` |
| CEffGroupNode | 108 | m_nTodo_06C | `int` |
| CEffGroupNode | 112 | m_nTodo_070 | `int` |
| CEffMeteor | 48 | m_pGeomQuad | `gbGeomQuad *` |
| CEffMeteor | 52 | m_pChain | `CMeteorChain *` |
| CEffMeteor | 56 | m_pMeteor | `tagMeteor *` |
| CEffMeteor | 60 | m_pTexture | `gbTexture *` |
| CEffMeteor | 64 | m_pTextureArray | `gbTextureArray *` |
| CEffMeteor | 68 | m_bVisible | `unsigned char` |
| CEffMeteor | 69 | m_bAdditiveBlend | `unsigned char` |
| CEffMeteor | 70 | m_bNoZTest | `unsigned char` |
| CEffMeteor | 71 | m_bHaveHead | `unsigned char` |
| CEffMeteor | 72 | m_byMaxFrame | `unsigned char` |
| CEffMeteor | 76 | m_nRequireLoops | `int` |
| CEffMeteor | 80 | m_nLoops | `int` |
| CEffMeteor | 84 | m_fCurFrame | `float` |
| CEffMeteor | 88 | m_dwStartColor | `unsigned int` |
| CEffMeteor | 92 | m_fAlpha | `float` |
| CEffMeteor | 96 | m_fRed | `float` |
| CEffMeteor | 100 | m_fGreen | `float` |
| CEffMeteor | 104 | m_fBlue | `float` |
| CEffMeteor | 108 | m_fXSize | `float` |
| CEffMeteor | 112 | m_fZSize | `float` |
| CEffMeteor | 116 | m_nMaxChain | `int` |
| CEffMeteor | 120 | m_fMeteorWidth | `float` |
| CEffMeteor | 124 | m_nMaxTrail | `int` |
| CEffMeteor | 128 | m_fLumDecSpeed | `float` |
| CEffMeteor | 132 | m_fWidthDecSpeed | `float` |
| CEffMeteor | 136 | m_fMaxLum | `float` |
| CEffMeteor | 140 | m_fUpdateTimeFund | `float` |
| CEffMeteor | 144 | m_fFramePerSec | `float` |
| CEffMeteor | 148 | m_vecRot | `gbVec3D` |
| CEffMeteor | 160 | m_vecPos | `gbVec3D` |
| CEffMeteor | 172 | m_vecOffsetPos | `gbVec3D` |
| CEffMeteor | 184 | m_vecTarget | `gbVec3D` |
| CEffMeteor | 196 | m_vecStartSpeed | `gbVec3D` |
| CEffMeteor | 208 | m_DefaultUVSet | `tagUV[256]` |
| CEffModel | 48 | m_pGeomNode | `gbGeomNode *` |
| CEffModel | 64 | m_vecOffsetPos | `gbVec3D` |
| CEffModel | 76 | m_vecRot | `gbVec3D` |
| CEffModel | 88 | m_bVisible | `unsigned char` |
| CEffModel | 89 | m_bAdditiveBlend | `unsigned char` |
| CEffModel | 90 | m_bNoZTest | `unsigned char` |
| CEffModel | 92 | m_fSizeX | `float` |
| CEffModel | 96 | m_fSizeY | `float` |
| CEffModel | 100 | m_fSizeZ | `float` |
| CEffObj | 4 | m_pEM | `CEffMgr *` |
| CEffObj | 8 | m_bIdle | `_BYTE` |
| CEffQuad | 48 | m_bActive | `unsigned char` |
| CEffQuad | 49 | m_bVisible | `unsigned char` |
| CEffQuad | 50 | m_bAniFrame | `unsigned char` |
| CEffQuad | 51 | m_bBillBoard | `unsigned char` |
| CEffQuad | 52 | m_bAdditiveBlend | `unsigned char` |
| CEffQuad | 53 | m_bNoZTest | `unsigned char` |
| CEffQuad | 54 | m_byMaxFrame | `unsigned char` |
| CEffQuad | 56 | m_nRequireLoops | `int` |
| CEffQuad | 60 | m_nQuadNum | `int` |
| CEffQuad | 64 | m_nGeomQuadNum | `int` |
| CEffQuad | 68 | m_nMaxQuad | `int` |
| CEffQuad | 72 | m_nLastCreatedQuad | `int` |
| CEffQuad | 76 | m_StartQuad | `tagQuad` |
| CEffQuad | 156 | m_pQuad | `tagQuad *` |
| CEffQuad | 160 | m_pGeomQuad | `gbGeomQuad *` |
| CEffQuad | 164 | m_pnG2Q | `int *` |
| CEffQuad | 168 | m_DefaultUVSet | `tagUV[256]` |
| CEffQuad | 4264 | m_pTexture | `gbTexture *` |
| CEffQuad | 4268 | m_pTextureArray | `gbTextureArray *` |
| CEffSParticle | 48 | m_pEffect | `CParticleEffect *` |
| CEffSParticle | 52 | m_vecPos | `gbVec3D` |
| CEffSParticle | 64 | m_fX | `float` |
| CEffSParticle | 68 | m_fY | `float` |
| CEffSParticle | 72 | m_fZ | `float` |
| CEffSParticle | 76 | m_fPX | `float` |
| CEffSParticle | 80 | m_fPY | `float` |
| CEffSParticle | 84 | m_fPZ | `float` |
| CEffSParticle | 88 | m_fRotX | `float` |
| CEffSParticle | 92 | m_fRotY | `float` |
| CEffSParticle | 96 | m_fRotZ | `float` |
| CEffShock | 48 | m_DefaultUVSet | `tagUV[256]` |
| CEffShock | 4144 | m_pTexture | `gbTexture *` |
| CEffShock | 4148 | m_pTextureArray | `gbTextureArray *` |
| CEffShock | 4152 | m_nMaxGeomQuad | `int` |
| CEffShock | 4156 | m_pGeomQuad | `gbGeomQuad *` |
| CEffShock | 4160 | m_pShock | `tagShockUnit *` |
| CEffShock | 4164 | m_bVisible | `unsigned char` |
| CEffShock | 4165 | m_bAdditiveBlend | `unsigned char` |
| CEffShock | 4166 | m_bNoZTest | `unsigned char` |
| CEffShock | 4168 | m_fFramePerSec | `float` |
| CEffShock | 4172 | m_byMaxFrame | `unsigned char` |
| CEffShock | 4176 | m_nRequireLoops | `int` |
| CEffShock | 4180 | m_nLoops | `int` |
| CEffShock | 4184 | m_fCurFrame | `float` |
| CEffShock | 4188 | m_dwStartColor | `unsigned int` |
| CEffShock | 4192 | m_fAlpha | `float` |
| CEffShock | 4196 | m_fRed | `float` |
| CEffShock | 4200 | m_fGreen | `float` |
| CEffShock | 4204 | m_fBlue | `float` |
| CEffShock | 4208 | m_fSize | `float` |
| CEffShock | 4212 | m_vecRot | `gbVec3D` |
| CEffShock | 4224 | m_vecPos | `gbVec3D` |
| CEffShock | 4236 | m_vecOffsetPos | `gbVec3D` |
| CEffShock | 4248 | m_nNodeOfShock | `int` |
| CEffShock | 4252 | m_nCascade | `int` |
| CEffShock | 4256 | m_fWidthOfNode | `float` |
| CEffShock | 4260 | m_fHeightOfNode | `float` |
| CEffShock | 4264 | m_fSpeedOfDisappear | `float` |
| CEffShock | 4268 | m_fInterleaving | `float` |
| CEffTrackCustomShape | 184 | m_nCurrTrackPos | `int` |
| CEffTrackCustomShape | 188 | m_fx | `float` |
| CEffTrackCustomShape | 192 | m_fy | `float` |
| CEffTrackCustomShape | 196 | m_fz | `float` |
| CEffTrackCylinder | 4304 | m_nCurrTrackPos | `int` |
| CEffTrackCylinder | 4308 | m_fx | `float` |
| CEffTrackCylinder | 4312 | m_fy | `float` |
| CEffTrackCylinder | 4316 | m_fz | `float` |
| CEffTrackGrid | 4292 | m_nCurrTrackPos | `int` |
| CEffTrackGrid | 4296 | m_fx | `float` |
| CEffTrackGrid | 4300 | m_fy | `float` |
| CEffTrackGrid | 4304 | m_fz | `float` |
| CEffTrackModel | 116 | m_nCurrTrackPos | `int` |
| CEffTrackModel | 120 | m_fx | `float` |
| CEffTrackModel | 124 | m_fy | `float` |
| CEffTrackModel | 128 | m_fz | `float` |
| CEffTrackQuad | 4284 | m_nCurrTrackPos | `int` |
| CEffTrackQuad | 4288 | m_fx | `float` |
| CEffTrackQuad | 4292 | m_fy | `float` |
| CEffTrackQuad | 4296 | m_fz | `float` |
| CEffTrackSParticle | 112 | m_nCurrTrackPos | `int` |
| CEffect | 0 | m_pDispatchTable | `void *` |
| CEffect | 4 | _field_004 | `int` |
| CEffect | 8 | m_eKind | `EEffect` |
| CEffect | 12 | m_bActive | `unsigned char` |
| CEffect | 13 | m_bVisible | `unsigned char` |
| CEffect | 16 | m_DeltaTime | `double` |
| CEffect | 24 | m_nPartical | `int` |
| CEffect | 28 | m_Partical | `tagPartical[2048]` |
| CEffect | 98332 | m_nQuad | `int` |
| CEffect | 98336 | m_QuadBuffer | `gbGeomQuad[2048]` |
| CEffect | 237600 | m_nQ2PIndex | `int[2048]` |
| CEffect | 245792 | m_pTexture | `gbTexture *` |
| CEffect | 245796 | m_pTextureArray | `gbTextureArray *` |
| CEffectSystem | 4 | m_pDisplay | `gbGfxManager *` |
| CEffectSystem | 8 | m_pVertexBuffer | `gbDynVertBuf *` |
| CEffectSystem | 12 | m_pAdditiveBlend | `gbRenderEffect *` |
| CEffectSystem | 16 | m_pAlphaBlend | `gbRenderEffect *` |
| CEffectSystem | 20 | m_DefaultUVSet | `tagUVSet[16]` |
| CEffectSystem | 276 | m_bInitialized | `unsigned char` |
| CEffectSystem | 280 | m_nEffect | `int` |
| CEffectSystem | 284 | m_pEffect | `CEffect *[8]` |
| CEffectSystem | 316 | m_dDeltaTime | `double` |
| CEffectSystem | 324 | m_dTimeFund | `double` |
| CEffectSystem | 332 | m_fTimeFund | `float` |
| CEffectSystem | 336 | m_fTimeScale | `int` |
| CEffectSystem | 340 | m_fWindDirection | `int` |
| CEffectSystem | 344 | m_fWindSpeed | `int` |
| CEffgbParticle | 48 | m_pEffect | `ParticleEffect *` |
| CEffgbParticle | 52 | m_fSize | `float` |
| CEffgbParticle | 56 | m_fX | `float` |
| CEffgbParticle | 60 | m_fY | `float` |
| CEffgbParticle | 64 | m_fZ | `float` |
| CEffgbParticle | 68 | m_fPX | `float` |
| CEffgbParticle | 72 | m_fPY | `float` |
| CEffgbParticle | 76 | m_fPZ | `float` |
| CEmitter | 0 | _attr | `CParticleSystem::EmitterAttribute` |
| CEmitter | 220 | _nCurrTrackPos | `int` |
| CEmitter | 224 | _fTrackDecPart | `float` |
| CFadeColorPolicy | 12 | _vBeginColor | `gbVec3D` |
| CFadeColorPolicy | 24 | _vEndColor | `gbVec3D` |
| CG_Edit | 0 | m_pFather | `CG_Entry *` |
| CG_Edit | 4 | m_MousePt | `tagPOINT` |
| CG_Edit | 12 | m_Param | `_FLOORPARAM` |
| CG_Edit | 24 | m_fYaw | `float` |
| CG_Edit | 28 | m_fPitch | `float` |
| CG_Edit | 32 | m_fDist | `float` |
| CG_Edit | 36 | m_fCamX | `float` |
| CG_Edit | 40 | m_fCamY | `float` |
| CG_Edit | 44 | m_fCamZ | `float` |
| CG_Edit | 48 | m_vCamForward | `gbVec3D` |
| CG_Edit | 60 | EFT_LINE | `gbRenderEffect *` |
| CG_Edit | 64 | EFT_GEOM_NOTEX | `gbRenderEffect *` |
| CG_Edit | 68 | EFT_GEOM_NOTEX_LINE | `gbRenderEffect *` |
| CG_Edit | 72 | m_bWaitForEditArea | `BYTE` |
| CG_Edit | 76 | m_rTouchArea | `tagRECT` |
| CG_Edit | 92 | m_rLastObjArea | `tagRECT` |
| CG_Edit | 108 | m_pLastGroundPt | `tagPOINT` |
| CG_Edit | 116 | m_nNoteMoney | `int` |
| CG_Entry | 0 | bOpt | `BYTE` |
| CG_Entry | 1 | m_bUIActive | `BYTE` |
| CG_Entry | 4 | m_pScene | `CG_Scene *` |
| CG_Entry | 8 | m_pUI | `CG_UI *` |
| CG_Entry | 12 | m_pEdit | `CG_Edit *` |
| CG_Entry | 16 | m_LEVELPARAM | `LEVELPARAM[5]` |
| CG_Entry | 56 | m_EntryFrame | `PAL3_FRAME` |
| CG_Entry | 60 | m_EntryRolePos | `gbVec3D` |
| CG_Entry | 72 | m_EntryCityName | `char[64]` |
| CG_Entry | 136 | m_EntryName | `char[64]` |
| CG_Entry | 200 | b_NoteJumpFree | `BYTE` |
| CG_Scene | 0 | m_pBarrier | `BARRIER *` |
| CG_Scene | 4 | m_nBarrier | `int` |
| CG_Scene | 8 | m_bShowHelper | `BYTE` |
| CG_Scene | 12 | m_pFather | `CG_Entry *` |
| CG_Scene | 16 | m_pScene | `Scene *` |
| CG_Scene | 20 | m_CameraCtrl | `RoleCameraCtrl` |
| CG_Scene | 96 | m_pNPC | `Role *` |
| CG_Scene | 100 | m_pRelive | `RELIVEPARAM *` |
| CG_Scene | 104 | m_OBJ | `SceneObj[256]` |
| CG_Scene | 456808 | m_ObjHelper | `OBJHELPER[256]` |
| CG_Scene | 469096 | m_OBJPARAM | `ObjParam[9]` |
| CG_Scene | 473164 | m_GHOSTPARAM | `GhostParam[4]` |
| CG_Scene | 473356 | m_pBOSS | `Role *` |
| CG_Scene | 473360 | m_BossHurt | `BOSSHURT` |
| CG_Scene | 473380 | m_NGHHurt | `NGHHURT` |
| CG_Scene | 473400 | m_bEdit | `BYTE` |
| CG_Scene | 473404 | m_nLevel | `int` |
| CG_Scene | 473408 | m_nNPC | `int` |
| CG_Scene | 473412 | m_nOBJ | `int` |
| CG_Scene | 473416 | m_nSpecialOBJ | `int` |
| CG_Scene | 473420 | m_fEffTime | `float` |
| CG_Scene | 473424 | m_bGameOver | `BYTE` |
| CG_Scene | 473428 | m_ObjFile | `TxtFile` |
| CG_Scene | 473952 | EFT_LINE | `gbRenderEffect *` |
| CG_Scene | 473956 | EFT_GEOM | `gbRenderEffect *` |
| CG_Scene | 473960 | EFT_GEOM_NOTEX | `gbRenderEffect *` |
| CG_Scene | 473964 | EFT_GEOM_NOTEX_LINE | `gbRenderEffect *` |
| CG_Scene | 473968 | m_pObjFlagTex | `gbTexture *` |
| CG_Scene | 473972 | m_SpecialObjPos | `gbVec3D[16]` |
| CG_Scene | 474164 | m_DoFlingAct | `BYTE` |
| CG_Scene | 474168 | m_propinfo | `CG_PROPINFO` |
| CG_Scene | 474172 | m_propid | `unsigned int` |
| CG_Scene | 474176 | m_tmpPos | `gbVec3D` |
| CG_Scene | 474188 | m_PropArray | `char[12]` |
| CG_UI | 72 | buf | `char[256]` |
| CG_UI | 328 | m_ParentRc | `tagRECT` |
| CG_UI | 344 | m_pFather | `CG_Entry *` |
| CG_UI | 348 | m_SelType | `int` |
| CG_UI | 352 | m_SelPropType | `int` |
| CG_UI | 356 | m_nResultValue | `int` |
| CG_UI | 360 | m_nWinState | `int` |
| CG_UI | 364 | m_OutFrameT | `UIStatic` |
| CG_UI | 524 | m_OutFrameR | `UIStatic` |
| CG_UI | 684 | m_OutFrameL | `UIStatic` |
| CG_UI | 844 | m_OutFrameB | `UIStatic` |
| CG_UI | 1004 | m_pTime | `UIStatic` |
| CG_UI | 1164 | m_pMoney | `UIStatic` |
| CG_UI | 1324 | m_pTools | `UIStatic` |
| CG_UI | 1484 | m_pItems | `UIButton[9]` |
| CG_UI | 4580 | m_pName | `UIStatic` |
| CG_UI | 4740 | m_pPrice | `UIStatic` |
| CG_UI | 4900 | m_pHurt | `UIStatic` |
| CG_UI | 5060 | m_pInfo | `UIStatic` |
| CG_UI | 5220 | m_pBuy | `UIButton` |
| CG_UI | 5564 | m_pRun | `UIButton` |
| CG_UI | 5908 | m_pProp | `UIStatic` |
| CG_UI | 6068 | m_pProps | `UIButton[5]` |
| CG_UI | 7788 | m_pPropsNum | `UIStatic[5]` |
| CG_UI | 8588 | m_pHP | `UIStatic *` |
| CG_UI | 8748 | m_pBossHP | `UIProgressBar` |
| CG_UI | 8992 | m_pRoleHP | `UIProgressBar` |
| CG_UI | 9236 | m_pRoleFace | `UIStatic` |
| CG_UI | 9396 | m_pBossFace | `UIStatic` |
| CG_UI | 9556 | m_pTimeBackground | `UIStatic` |
| CG_UI | 9716 | m_pTimeHunDigit | `UIStaticRM` |
| CG_UI | 9904 | m_pTimeTenDigit | `UIStaticRM` |
| CG_UI | 10092 | m_pTimeSinDigit | `UIStaticRM` |
| CG_UI | 10280 | m_pResult | `UIStatic` |
| CG_UI | 10440 | m_pWinAnswer | `MUIDialog` |
| CG_UI | 11824 | m_pLoseAnswer | `MUIDialog` |
| CG_UI | 13208 | m_pNoMoneyMsg | `MUIDialog` |
| CG_UI | 14592 | m_pSurpassMsg | `MUIDialog` |
| CG_UI | 15976 | m_pAccountMsg | `MUIDialog` |
| CG_UI | 17360 | m_pOverGameMsg | `MUIDialog` |
| CG_UI | 18744 | m_pExitDlg | `MUIDialog` |
| CG_UI | 20128 | m_ComboBuffer | `PtrArray` |
| CG_UI | 20144 | m_SceneMap | `UISceneMap` |
| CG_UI | 21352 | m_Exit | `UIButton` |
| CG_UI | 21696 | m_IsExit | `unsigned char` |
| CG_UI | 21700 | m_InvalidRc0 | `tagRECT` |
| CG_UI | 21716 | m_InvalidRc1 | `tagRECT` |
| CG_UI | 21732 | m_InvalidRc2 | `tagRECT` |
| CG_UI | 21748 | m_nTimeSec | `int` |
| CG_UI | 21752 | m_nBossHP | `int` |
| CG_UI | 21756 | m_fBossHP | `float` |
| CG_UI | 21760 | m_nRoleFullHP | `int` |
| CG_UI | 21764 | m_nRoleCurHP | `int` |
| CG_UI | 21768 | m_ComboHitLastTime | `float` |
| CG_UI | 21772 | m_ComboHitTime | `float` |
| CG_UI | 21776 | m_nComboHit | `int` |
| CG_UI | 21780 | m_nTotalComboHit | `int` |
| CG_UI | 21784 | m_pCombo | `UIStatic` |
| CG_UI | 21944 | m_mouseon | `_BYTE[9]` |
| CG_UI | 21956 | m_nPropCost | `int` |
| CG_UI | 21960 | m_nNoteMoney | `int` |
| CG_UI | 21964 | m_pBuyUI | `PropUI *` |
| CG_UI | 21968 | m_bRenderBuyUI | `unsigned char` |
| CIniFile | 0 | m_fp | `gbVFile *` |
| CIniFile | 4 | m_bRead | `int` |
| CJ_FindFile | 0 | m_strRoot | `char[324]` |
| CJ_FindFile | 324 | m_pNextInfo | `char *` |
| CJ_FindFile | 328 | m_hContext | `char *` |
| CJ_FindFile | 332 | m_pFoundInfo | `char *` |
| CJ_FindFile | 336 | m_fileName | `char[324]` |
| CJ_FindFile | 660 | m_strbuf | `char[324]` |
| CJ_FindFile | 984 | m_bClosed | `BYTE` |
| CLoad3DS | 0 | m_FilePointer | `gbVFile *` |
| CLoad3DS | 4 | m_pBuffer | `char[20]` |
| CLoad3DS | 24 | m_nTodo_018 | `int` |
| CLoad3DS | 28 | m_nTodo_01C | `int` |
| CLoad3DS | 32 | m_nTodo_020 | `int` |
| CMeteorChain | 0 | m_pEM | `CEffMgr *` |
| CMeteorChain | 4 | m_pGeomQuad | `gbGeomQuad *` |
| CMeteorChain | 8 | m_bHaveTexture | `unsigned char` |
| CMeteorChain | 12 | m_pTextureArray | `gbTextureArray *` |
| CMeteorChain | 16 | m_nNumOfNode | `int` |
| CMeteorChain | 20 | m_pFirstNode | `tagMeteorNode *` |
| CMeteorChain | 24 | m_pLastNode | `tagMeteorNode *` |
| CMeteorChain | 28 | m_fCurTime | `float` |
| CMeteorChain | 32 | m_fLastTime | `float` |
| CMeteorChain | 36 | m_dwColor | `unsigned int` |
| CMeteorChain | 40 | m_fMaxLum | `float` |
| CMeteorChain | 44 | m_fLumDecSpeed | `float` |
| CMeteorChain | 48 | m_fMaxWidth | `float` |
| CMeteorChain | 52 | m_fWidthDecSpeed | `float` |
| COLLIDE_DATA | 0 | v1 | `gbVec3D` |
| COLLIDE_DATA | 12 | v2 | `gbVec3D` |
| COLLIDE_DATA | 24 | v3 | `gbVec3D` |
| COLLIDE_DATA | 36 | fn | `gbVec3D` |
| CONTEXT | 0 | ContextFlags | `unsigned int` |
| CONTEXT | 4 | Dr0 | `unsigned int` |
| CONTEXT | 8 | Dr1 | `unsigned int` |
| CONTEXT | 12 | Dr2 | `unsigned int` |
| CONTEXT | 16 | Dr3 | `unsigned int` |
| CONTEXT | 20 | Dr6 | `unsigned int` |
| CONTEXT | 24 | Dr7 | `unsigned int` |
| CONTEXT | 140 | SegGs | `unsigned int` |
| CONTEXT | 144 | SegFs | `unsigned int` |
| CONTEXT | 148 | SegEs | `unsigned int` |
| CONTEXT | 152 | SegDs | `unsigned int` |
| CONTEXT | 156 | Edi | `unsigned int` |
| CONTEXT | 160 | Esi | `unsigned int` |
| CONTEXT | 164 | Ebx | `unsigned int` |
| CONTEXT | 168 | Edx | `unsigned int` |
| CONTEXT | 172 | Ecx | `unsigned int` |
| CONTEXT | 176 | Eax | `unsigned int` |
| CONTEXT | 180 | Ebp | `unsigned int` |
| CONTEXT | 184 | Eip | `unsigned int` |
| CONTEXT | 188 | SegCs | `unsigned int` |
| CONTEXT | 192 | EFlags | `unsigned int` |
| CONTEXT | 196 | Esp | `unsigned int` |
| CONTEXT | 200 | SegSs | `unsigned int` |
| COnceFramePolicy | 12 | _fSpeed | `float` |
| CPK | 0 | m_dwAllocGranularity | `unsigned int` |
| CPK | 4 | m_eMode | `ECPKMode` |
| CPK | 8 | m_CPKHeader | `tagCPKHeader` |
| CPK | 136 | m_CPKTable | `tagCPKTable[32768]` |
| CPK | 917640 | m_pCPKFile | `gbVFile *[8]` |
| CPK | 917672 | m_bLoaded | `unsigned char` |
| CPK | 917676 | m_dwCPKHandle | `unsigned int` |
| CPK | 917680 | m_dwCPKMappingHandle | `unsigned int` |
| CPK | 917684 | m_szCPKFileName | `char[260]` |
| CPK | 917944 | m_nOpenedFileNum | `int` |
| CPKFile | 0 | bValid | `unsigned char` |
| CPKFile | 4 | dwCRC | `unsigned int` |
| CPKFile | 8 | dwFatherCRC | `unsigned int` |
| CPKFile | 12 | nTableIndex | `int` |
| CPKFile | 16 | lpMapAddress | `char *` |
| CPKFile | 20 | lpStartAddress | `char *` |
| CPKFile | 24 | dwOffset | `unsigned int` |
| CPKFile | 28 | bCompressed | `unsigned char` |
| CPKFile | 32 | lpRealData | `char *` |
| CPKFile | 36 | dwFileSize | `unsigned int` |
| CPKFile | 40 | dwPointer | `unsigned int` |
| CPKFile | 44 | pTableItem | `tagCPKTable *` |
| CPPEH_RECORD | 0 | old_esp | `unsigned int` |
| CPPEH_RECORD | 4 | exc_ptr | `EXCEPTION_POINTERS *` |
| CPPEH_RECORD | 8 | registration | `_EH3_EXCEPTION_REGISTRATION` |
| CParticleEffect | 0 | _bPlay | `int` |
| CParticleEffect | 4 | _fTimeScale | `float` |
| CParticleEffect | 8 | _tBlendType | `int` |
| CParticleEffect | 12 | _fTime | `float` |
| CParticleEffect | 16 | _ParticleSystems | `char[16]` |
| CParticleEffect | 32 | _pRenderEffect | `gbRenderEffect *` |
| CParticleEffect | 36 | _pGfxMgr | `gbGfxManager *` |
| CParticleEffect | 40 | _dwReserved | `unsigned int[4]` |
| CParticleSystem | 0 | _bVisible | `int` |
| CParticleSystem | 4 | _bPlay | `int` |
| CParticleSystem | 8 | _bCycle | `int` |
| CParticleSystem | 12 | _bManual | `int` |
| CParticleSystem | 16 | _strParticleName | `char[16]` |
| CParticleSystem | 32 | _dwParticleId | `unsigned int` |
| CParticleSystem | 36 | _pPositionPolicy | `CPolicy *` |
| CParticleSystem | 40 | _pDirectionPolicy | `CPolicy *` |
| CParticleSystem | 44 | _pColorPolicy | `CPolicy *` |
| CParticleSystem | 48 | _pAlphaPolicy | `CPolicy *` |
| CParticleSystem | 52 | _pFramePolicy | `CPolicy *` |
| CParticleSystem | 56 | _pEmitterPolicy | `CPolicy *` |
| CParticleSystem | 60 | _pParticles | `CParticleSystem_ParticleUnit *` |
| CParticleSystem | 64 | _pEmitter | `CEmitter *` |
| CParticleSystem | 68 | _KeyFrames | `char[16]` |
| CParticleSystem | 84 | _nNumOfParticles | `int` |
| CParticleSystem | 88 | _nMaxNum | `int` |
| CParticleSystem | 92 | _dwNumOfKeyFrames | `unsigned int` |
| CParticleSystem | 96 | _dwNumOfUnitFrames | `unsigned int` |
| CParticleSystem | 100 | _nCurrFrame | `int` |
| CParticleSystem | 104 | _nLastFrame | `int` |
| CParticleSystem | 108 | _fTimeCounter | `float` |
| CParticleSystem | 112 | _fEmitDecPart | `float` |
| CParticleSystem | 116 | _dwVBFlush | `unsigned int` |
| CParticleSystem | 120 | _matTransform | `gbMatrix4` |
| CParticleSystem | 184 | _fWidthScale | `float` |
| CParticleSystem | 188 | _fHeightScale | `float` |
| CParticleSystem | 192 | _TexCoordData | `char[16]` |
| CParticleSystem | 208 | _pTexture | `gbTexture *` |
| CParticleSystem | 212 | _pRenderEffect | `gbRenderEffect *` |
| CParticleSystem | 216 | _pGfxMgr | `gbGfxManager *` |
| CPolicy | 4 | _pParticleSystem | `CParticleSystem *` |
| CPolicy | 8 | _dwPolicyId | `unsigned int` |
| CReBackFramePolicy | 12 | _fSpeed | `float` |
| CResistanceMotionPolicy | 12 | _vAcceleration | `gbVec3D` |
| CResistanceMotionPolicy | 24 | _fConstant | `float` |
| CRotateEmitterPolicy | 12 | _vAxis | `gbVec3D` |
| CRotateEmitterPolicy | 24 | _fSpeed | `float` |
| CRotateEmitterPolicy | 28 | _fAngle | `float` |
| CSEHException | 0 | m_dwOpts | `unsigned int` |
| CSEHException | 4 | m_szExceptionString | `char[260]` |
| CScreenMode | 72 | m_nPosY | `int` |
| CScreenMode | 76 | m_nLayoutParam | `int` |
| CScreenMode | 80 | m_nUIState | `int` |
| CScreenMode | 84 | m_nUIMode | `int` |
| CScreenMode | 88 | m_nScreenWidth | `int` |
| CScreenMode | 92 | m_nScreenHeight | `int` |
| CScreenMode | 96 | m_nProgressBase | `int` |
| CScreenMode | 100 | m_nLayoutState | `int` |
| CScreenMode | 104 | m_nLayoutOffX | `int` |
| CScreenMode | 108 | m_nLayoutOffY | `int` |
| CScreenMode | 113 | m_bLoadFlag | `unsigned char` |
| CScreenMode | 120 | m_nProgressValA | `int` |
| CScreenMode | 124 | m_nProgressValB | `int` |
| CScreenMode | 128 | m_nProgressPos | `int` |
| CScreenMode | 132 | m_nProgress | `int` |
| CScreenMode | 136 | m_nBarWidth | `int` |
| CScreenMode | 140 | m_nBarHeight | `int` |
| CScreenMode | 144 | m_nBarPosX | `int` |
| CScreenMode | 148 | m_nBarPosY | `int` |
| CScreenMode | 152 | m_bCameraInit | `int` |
| CScreenMode | 160 | m_fVolume | `float` |
| CScreenMode | 164 | m_wndAssistA | `float` |
| CScreenMode | 168 | m_nAudioHandle | `int` |
| CScreenMode | 172 | m_pfnPlayVideo | `int` |
| CScreenMode | 176 | m_nAudioState | `int` |
| CScreenMode | 180 | m_fAudioVolume | `float` |
| CScreenMode | 184 | m_nAudioFileId | `int` |
| CScreenMode | 192 | m_nVideoState | `int` |
| CScreenMode | 196 | m_fSceneVolume | `float` |
| CScreenMode | 204 | m_fPan | `float` |
| CScreenMode | 208 | m_fProgressD | `float` |
| CScreenMode | 212 | m_szTooltip | `char[8]` |
| CScreenMode | 220 | m_fProgressRatio | `float` |
| CScreenMode | 224 | m_fProgressMax | `float` |
| CScreenMode | 228 | m_fProgressCur | `float` |
| CScreenMode | 232 | m_fProgress | `float` |
| CScreenMode | 236 | m_fProgressParam | `float` |
| CScreenMode | 240 | m_fProgressNorm | `float` |
| CScreenMode | 244 | m_nBarTotalSize | `int` |
| CScreenMode | 248 | m_fBarOffsetX | `float` |
| CScreenMode | 252 | m_fBarOffsetY | `float` |
| CScreenMode | 256 | m_fBarOffsetW | `float` |
| CScreenMode | 260 | m_fAccum | `float` |
| CScreenMode | 264 | m_nProgressTimer | `int` |
| CScreenMode | 268 | m_nBarParam | `int` |
| CScreenMode | 272 | m_nArrayCapacity | `int` |
| CScreenMode | 276 | m_pArrayData | `char *` |
| CScreenMode | 280 | m_FrameB | `UIStatic` |
| CScreenMode | 432 | m_StaticArray | `UIStatic` |
| CScreenMode | 616 | m_nVolNode0 | `int` |
| CScreenMode | 620 | m_nVolNode1 | `int` |
| CScreenMode | 624 | m_nVolNode2 | `int` |
| CScreenMode | 628 | m_nVolNode3 | `int` |
| CScreenMode | 632 | m_nVolNode4 | `int` |
| CScreenMode | 636 | _embed_UIFrameWnd_816 | `UIFrameWnd` |
| CScreenMode | 728 | _embed_UIFrameWnd_968 | `UIFrameWnd` |
| CScreenMode | 808 | m_pAudioMgr | `gbAudioManager *` |
| CScreenMode | 812 | m_pSoundStream | `void *` |
| CScreenMode | 816 | m_Static_816 | `UIStatic` |
| CScreenMode | 1244 | m_nPageCounter | `UIScene` |
| CScreenMode | 2260 | m_BtnTooltipC | `UIButton` |
| CScreenMode | 2608 | m_pGameUI | `void *` |
| CScreenMode | 2620 | m_ScenePanel | `UIScene` |
| CScreenMode | 2964 | m_ScenePanelB | `UIScene` |
| CScreenMode | 3308 | m_ScenePanelC | `UIScene` |
| CScreenMode | 3660 | m_nAssistMode | `int` |
| CScreenMode | 3688 | m_SceneBlock | `int` |
| CScreenMode | 3868 | m_bActive | `unsigned char` |
| CScreenMode | 3872 | m_nScreenActive | `int` |
| CScreenMode | 3876 | m_RoleDialog | `UIRoleDialog` |
| CTaskTpl | 4 | m_fCurTime | `float` |
| CTaskTpl | 8 | m_fDeltaTime | `float` |
| CTaskTpl | 12 | m_pTask | `char *` |
| CTaskTpl | 16 | m_nCurTask | `int` |
| CTaskTpl | 20 | m_nCurSubTask | `int` |
| CTaskTpl | 24 | m_nTask | `int` |
| CTaskTpl | 28 | m_nMaxTask | `int` |
| CTaskTpl | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffAction | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffAction | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffAction | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAction | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffAudio | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffBink | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffBink | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffBink | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffBink | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCamera | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffGrid | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffModel | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffModel | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffModel | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffModel | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuad | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffQuake | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffShock | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffShock | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffShock | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffShock | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffTime | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffTime | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffTime | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffTime | 32 | m_nMaxSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 4 | m_fCurTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 8 | m_fDeltaTime | `float` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 12 | m_pTask | `char *` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 16 | m_nCurTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 20 | m_nCurSubTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 24 | m_nTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 28 | m_nMaxTask | `int` |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 32 | m_nMaxSubTask | `int` |
| CTrail | 0 | m_fTime | `float` |
| CTrail | 4 | m_bSupport | `BYTE` |
| CTrail | 5 | m_bEnable | `BYTE` |
| CTrail | 8 | m_pCam | `gbCamera *` |
| CTrail | 12 | m_ScreenQuad | `gbUIQuad` |
| CTrail | 52 | m_dwRenderCounter | `unsigned int` |
| CTrail | 56 | m_dwRT | `unsigned int` |
| CTrail | 60 | m_bReady | `BYTE` |
| CTrail | 64 | m_texRT | `gbTexture_D3D[8]` |
| CTrail | 832 | m_eft | `gbRenderEffect *` |
| CTrail | 836 | m_OriginSurface | `IDirect3DSurface9 *` |
| CUSTOMSHAPEVERTEX | 0 | v | `D3DXVECTOR3` |
| CUSTOMSHAPEVERTEX | 12 | color | `unsigned int` |
| CUSTOMSHAPEVERTEX | 16 | tu | `float` |
| CUSTOMSHAPEVERTEX | 20 | tv | `float` |
| CUtil | 0 | m_bCanWarp | `unsigned char` |
| CUtil | 4 | m_nRandHolder | `signed __int16` |
| CUtil | 8 | m_nRandCallCount | `int` |
| CUtil | 12 | m_fLog | `FILE *` |
| CUtil | 16 | m_sLogFileName | `char *` |
| CUtil | 20 | m_szLogPath | `char[260]` |
| CUtil | 280 | m_pDefaultString | `char *` |
| CUtil | 352 | m_nTodo_160 | `int[2]` |
| CUtil | 360 | m_nListIndex | `int` |
| CUtil | 364 | m_nUpdateCounter | `int` |
| CUtil | 368 | m_uiItemSlot | `UIItem` |
| CUtil | 1344 | m_nTodo_540 | `int` |
| CUtil | 1348 | m_nTodo_544 | `int` |
| CUtil | 1736 | m_pScreenMode | `CScreenMode *` |
| CUtil | 1740 | m_pBattleSystem | `char *` |
| CUtil | 1744 | m_pListView | `char *` |
| CUtil | 1748 | m_pPropUI | `PropUI *` |
| CUtil | 1752 | m_nRenderMode | `int` |
| Camera | 0 | m_pTodo_0 | `void *` |
| Camera | 4 | m_fCameraEyePosition | `float` |
| Camera | 8 | m_fCameraAtPosition | `float` |
| Camera | 12 | m_fCameraUpPosition | `float` |
| Camera | 16 | m_nStepRotate | `int` |
| Camera | 20 | m_nCameraAtPosition | `int` |
| Camera | 24 | m_nStepDirection | `int` |
| Camera | 28 | m_fStepDuration | `float` |
| Camera | 32 | m_nTransitionState | `int` |
| Camera | 36 | m_fTransitionTime | `float` |
| Camera | 40 | m_nTodo_28 | `int` |
| Camera | 44 | m_nTodo_02C | `int` |
| Camera | 48 | m_nTodo_30 | `int` |
| Camera | 52 | m_fStepRotate | `float` |
| Camera | 56 | m_nTransitionStep | `int` |
| Camera | 60 | m_nTransitionFlags | `int` |
| Camera | 64 | m_fLookAtStart | `float` |
| Camera | 68 | m_fLookAtEnd | `float` |
| Camera | 72 | m_fLookAtProgress | `float` |
| Camera | 76 | m_pLookAtData | `char *` |
| Camera | 104 | m_fCameraHeight | `float` |
| Camera | 116 | m_nTargetRole | `int` |
| Camera | 120 | m_bCreate | `unsigned char` |
| Camera | 128 | m_fFov | `float` |
| Camera | 132 | m_fZoomTarget | `int` |
| Camera | 136 | m_fAspect | `float` |
| Camera | 140 | m_nShakeAmplitude | `int` |
| Camera | 144 | m_nShakeDuration | `int` |
| Camera | 152 | m_nShakeType | `int` |
| Camera | 160 | m_fShakeFrequency | `float` |
| Camera | 164 | m_fZoomSpeed | `float` |
| Camera | 168 | m_fShakeOffset | `float` |
| Camera | 220 | m_nPosition | `int` |
| Camera | 232 | m_fFovTan | `float` |
| Camera | 244 | m_nCollisionFlags | `int` |
| Camera | 272 | m_nFollowMode | `int` |
| Camera | 292 | m_pCamera | `gbCamera *` |
| Camera | 296 | m_vRayDir | `gbVec3D` |
| Camera | 332 | m_pCollisionMesh | `void *` |
| Camera | 348 | m_pRayHitPoint | `void *` |
| Camera | 380 | m_nCameraTick | `int` |
| Camera | 384 | m_nPrevCameraTick | `int` |
| Camera | 388 | m_fCameraTimer | `float` |
| Camera | 392 | m_fLerpSpeed | `float` |
| Camera | 396 | m_fLerpProgress | `float` |
| Camera | 400 | m_bLerpActive | `unsigned char` |
| Camera | 404 | m_ScriptResult | `int` |
| CameraCmd | 0 | nCmdID | `int` |
| CameraCmd | 4 | nValue | `int` |
| CameraCtrl | 0 | m_pCamera | `gbCamera *` |
| CameraCtrl | 4 | m_fMinDist | `float` |
| CameraCtrl | 8 | m_pTarget | `InputSystem *` |
| CameraCtrl | 12 | m_nFlags | `int` |
| CameraCtrl | 16 | m_fTargetAngle | `float` |
| CameraCtrl | 20 | m_fCurAngle | `float` |
| CameraCtrl | 24 | m_nCamState | `int` |
| CameraCtrl | 28 | m_fAngleDest | `float` |
| CameraCtrl | 32 | m_fAngleSrc | `float` |
| CameraCtrl | 36 | m_fFOV | `float` |
| CameraCtrl | 40 | m_fFOVLerp | `float` |
| CameraCtrl | 44 | m_bCamFlag | `int` |
| CameraCtrl | 48 | m_fParamF | `float` |
| CameraCtrl | 52 | m_fLerpPosX | `float` |
| CameraCtrl | 56 | m_fLerpPosY | `float` |
| CameraCtrl | 60 | m_fLerpPosZ | `float` |
| CameraCtrl | 64 | m_fLerpTargetX | `float` |
| CameraCtrl | 68 | m_fLerpTargetY | `float` |
| CameraCtrl | 72 | m_fLerpTargetZ | `float` |
| CameraCtrl | 76 | m_nUIPosX | `int` |
| CameraCtrl | 80 | m_nUIWidgetW | `int` |
| CameraCtrl | 84 | m_nUIWidgetH | `int` |
| CameraCtrl | 88 | m_nUIWidgetSavedW | `int` |
| CameraCtrl | 92 | m_fUIWidgetSavedH | `float` |
| CameraCtrl | 96 | m_nViewMode | `int` |
| CameraCtrl | 100 | m_nViewFlags | `int` |
| CameraCtrl | 104 | m_szCamPath | `char[260]` |
| CameraCtrl | 364 | m_nBlendWeightIdx | `int` |
| CameraCtrl | 380 | m_nInitParams | `int` |
| CameraCtrl | 384 | m_nParamState | `int` |
| CameraCtrl | 388 | m_nParamA | `int` |
| CameraCtrl | 392 | m_nParamB | `int` |
| CameraCtrl | 396 | m_nParamC | `int` |
| CameraCtrl | 400 | m_lastFrom | `gbVec3D` |
| CameraCtrl | 412 | m_fromVec | `gbVec3D` |
| CameraCtrl | 424 | m_yaw | `float` |
| CameraCtrl | 428 | m_fCtrlYaw | `float` |
| CameraCtrl | 432 | m_dist | `int` |
| CameraCtrl | 444 | m_nextYAW | `float` |
| CameraCtrl | 452 | m_fAngle | `float` |
| CameraCtrl | 456 | m_fOrbitAngle | `float` |
| CameraCtrl | 460 | m_mode | `float` |
| CameraCtrl | 464 | m_nTodo_1D0 | `float` |
| CameraCtrl | 468 | m_fCamDist | `float` |
| CameraCtrl | 472 | m_nWidth | `int` |
| CameraCtrl | 476 | m_nHeight | `int` |
| CameraCtrl | 480 | m_nAsCurrent | `int` |
| CameraCtrl | 492 | m_vecLookAt | `gbVec3D` |
| CameraCtrl | 516 | m_vecUpDir | `gbVec3D` |
| CameraCtrl | 556 | m_fViewDistance | `float` |
| CameraCtrl | 564 | m_fViewPitch | `float` |
| CameraCtrl | 568 | m_fViewYaw | `float` |
| CameraCtrl | 572 | m_fDefaultPosX | `float` |
| CameraCtrl | 576 | m_fDefaultPosY | `float` |
| CameraCtrl | 580 | m_fDefaultPosZ | `float` |
| CameraCtrl | 584 | m_fDefaultOffset | `float` |
| CameraCtrl | 592 | m_pCameraEvent | `int` |
| CameraCtrl | 616 | m_szText | `float` |
| CameraCtrl | 620 | m_wParamA | `unsigned __int16` |
| CameraCtrl | 624 | m_wParamB | `unsigned __int16` |
| CameraCtrl | 688 | m_nEventViewX | `int` |
| CameraCtrl | 692 | m_nEventViewY | `int` |
| CameraCtrl | 696 | m_nEventHandle | `int` |
| CameraCtrl | 700 | m_nTodo_2BC | `int` |
| CameraCtrl | 877 | m_bCamEventFlag | `unsigned char` |
| CameraCtrl | 888 | m_bPageMode | `unsigned char` |
| CameraCtrl | 889 | m_bCamDirty | `unsigned char` |
| CameraCtrl | 892 | m_nPageParam | `int` |
| CameraCtrl | 896 | m_bBlendUpdate | `unsigned char` |
| CameraCtrl | 900 | m_nBlendWeight | `int` |
| CameraCtrl | 910 | m_bBlendWeight | `unsigned char` |
| CameraCtrl | 911 | m_bHandleEvent | `unsigned char` |
| CameraCtrl | 912 | m_bAutoRotate | `unsigned char` |
| CameraCtrl | 916 | m_nBlendTimer | `int` |
| CameraCtrl | 924 | m_nBlendState | `int` |
| CameraCtrl | 928 | m_nSlotParam | `int` |
| CameraCtrl | 1188 | m_nBlendWeightA | `int` |
| CameraCtrl | 1192 | m_nBlendWeightB | `int` |
| CameraCtrl | 1196 | m_nBlendWeightC | `int` |
| CameraCtrl | 1200 | m_roleParams | `float` |
| CameraCtrl | 1264 | m_nViewState | `int` |
| CameraCtrl | 2044 | m_nViewBase | `void *` |
| CameraCtrl | 3336 | m_bBlendActive | `unsigned char` |
| CameraCtrl | 3337 | m_bBlendPause | `unsigned char` |
| CameraCtrl | 3340 | m_nTickCount | `int` |
| CameraCtrl | 3344 | m_nTickStamp | `int` |
| CameraCtrl | 3348 | m_bTickInit | `unsigned char` |
| CameraCtrl | 3352 | m_CamBlocks | `int` |
| CameraParam | 0 | nID | `int` |
| CameraParam | 4 | _reserved | `int` |
| CameraParam | 8 | nParam1 | `int` |
| CameraParam | 12 | nParam2 | `int` |
| CatchableType | 0 | properties | `unsigned int` |
| CatchableType | 4 | pType | `TypeDescriptor *` |
| CatchableType | 8 | thisDisplacement | `PMD` |
| CatchableType | 20 | sizeOrOffset | `int` |
| CatchableType | 24 | copyFunction | `PMFN` |
| CatchableTypeArray | 0 | nCatchableTypes | `int` |
| ChoseCompose | 80 | rc | `tagRECT` |
| ChoseCompose | 96 | bkWndX | `int` |
| ChoseCompose | 100 | bkWndY | `int` |
| ChoseCompose | 104 | i | `int` |
| ChoseCompose | 108 | j | `int` |
| ChoseCompose | 112 | buf | `char[256]` |
| ChoseCompose | 368 | bkRc | `tagRECT` |
| ChoseCompose | 384 | m_id | `unsigned int` |
| ChoseCompose | 388 | m_isExit | `unsigned char` |
| ChoseCompose | 392 | m_bk | `UIStaticFlex` |
| ChoseCompose | 584 | m_ComposeInfo | `UIStatic` |
| ChoseCompose | 744 | m_RoleName | `UIButton[5]` |
| ColRet | 0 | dist | `float` |
| ColRet | 4 | pt | `gbVec3D` |
| ColRet | 16 | have | `BYTE` |
| ColRet | 20 | counter | `int` |
| ColRet | 24 | tri | `Triangle` |
| Collide_Ray | 4 | _origin | `char *[3]` |
| Collide_Ray | 16 | _vector | `char *[3]` |
| Collide_Ray | 28 | _normal | `char *[3]` |
| Collide_Ray | 40 | _length | `float` |
| Collide_Ray | 44 | _D | `float` |
| Collide_Ray | 48 | _nCalculated | `unsigned char` |
| Collide_Ray | 49 | _lCalculated | `unsigned char` |
| Collide_Ray | 50 | _dCalculated | `unsigned char` |
| Color4ub | 0 | B | `BYTE` |
| Color4ub | 1 | G | `BYTE` |
| Color4ub | 2 | R | `BYTE` |
| Color4ub | 3 | A | `BYTE` |
| ComboAttack | 0 | name | `char[32]` |
| ComboAttack | 32 | id | `unsigned int` |
| ComboAttack | 36 | man | `unsigned int[4]` |
| ComboAttack | 52 | pos | `_BYTE[4]` |
| ComboAttack | 56 | skill | `unsigned int` |
| ComboAttack | 60 | WeaponType | `_BYTE[4]` |
| ComboAttack | 64 | Range | `BYTE` |
| ComboAttack | 68 | state | `FightState[3]` |
| ComboAttack | 80 | Remark | `char[512]` |
| ComboAttack | 592 | fanwei | `BYTE` |
| ComboAttack | 593 | rvtype | `_BYTE[12]` |
| ComboAttack | 606 | rolevalue | `signed __int16[12]` |
| ComboAttack | 632 | hj_EffectRate | `int` |
| Comp_Donate | 0 | m_KeyId | `unsigned int` |
| Comp_Donate | 4 | m_bDonated | `BYTE` |
| Comp_Donate | 5 | m_bComposed | `BYTE` |
| Comp_DonateUI | 72 | m_RoleId | `int` |
| Comp_DonateUI | 76 | m_CompDonate | `Comp_Donate_Detail[10]` |
| Comp_DonateUI | 356 | m_keynum | `int` |
| Comp_DonateUI | 360 | m_curitem | `int` |
| Comp_DonateUI | 364 | m_state | `Comp_DonateUI::CDState[10]` |
| Comp_DonateUI | 404 | m_lang | `char[256][16][5]` |
| Comp_DonateUI | 20884 | m_OutFrameT | `UIStatic` |
| Comp_DonateUI | 21044 | m_OutFrameR | `UIStatic` |
| Comp_DonateUI | 21204 | m_OutFrameL | `UIStatic` |
| Comp_DonateUI | 21364 | m_OutFrameB | `UIStatic` |
| Comp_DonateUI | 21524 | m_TopFrame | `UIStatic` |
| Comp_DonateUI | 21684 | m_ExitBtn | `UIButton` |
| Comp_DonateUI | 22028 | m_Btn | `UIButton[10]` |
| Comp_DonateUI | 25468 | m_BtnStatic | `UIStatic[10]` |
| Comp_DonateUI | 27068 | m_mouseon | `int` |
| Comp_DonateUI | 27072 | m_RoleDlg | `UIRoleDialog` |
| Comp_DonateUI | 28440 | m_SelectDlg | `UIRoleSelect` |
| Comp_DonateUI | 30008 | m_IfSel | `unsigned char` |
| Comp_DonateUI | 30009 | m_IfGetSel | `unsigned char` |
| Comp_DonateUI | 30012 | m_RoleDlgRc | `tagRECT` |
| Comp_DonateUI | 30028 | m_AddIntimacyDonate | `int[5]` |
| Comp_DonateUI | 30048 | m_AddIntimacyComp | `int[5]` |
| Comp_DonateUI | 30068 | m_RoleLang | `char[512][4][5]` |
| Comp_DonateUI | 40308 | m_SelBtn | `int` |
| Comp_DonateUI | 40312 | m_Msg | `MUIDialog` |
| Comp_DonateUI | 41696 | m_ActiveDlg | `MUIDialog` |
| Comp_DonateUI | 43080 | m_ExitDlg | `MUIDialog` |
| Comp_DonateUI | 44464 | m_IsActive | `unsigned char` |
| Comp_DonateUI | 44465 | m_IsOver | `unsigned char` |
| Comp_DonateUI | 44468 | m_LineupComp | `LineupComp` |
| Comp_DonateUI | 46480 | m_BK | `UIStatic` |
| Comp_Donate_Detail | 0 | m_KeyId | `unsigned int` |
| Comp_Donate_Detail | 4 | m_bDonated | `BYTE` |
| Comp_Donate_Detail | 5 | m_bHasKey | `BYTE` |
| Comp_Donate_Detail | 8 | m_SourceId | `unsigned int` |
| Comp_Donate_Detail | 12 | m_bHasSource | `BYTE` |
| Comp_Donate_Detail | 16 | m_Intimacy | `unsigned int` |
| Comp_Donate_Detail | 20 | m_CompId | `unsigned int` |
| Comp_Donate_Detail | 24 | m_bComposed | `BYTE` |
| Comp_Donate_Detail | 25 | m_bCanRepeat | `BYTE` |
| ComposeUI | 72 | m_CurRender | `int` |
| ComposeUI | 76 | m_isCreatable | `unsigned char` |
| ComposeUI | 80 | m_TopFrame | `UIStatic` |
| ComposeUI | 240 | m_BottomFrame | `UIStatic` |
| ComposeUI | 400 | m_MiddleFrame | `UIStatic[3]` |
| ComposeUI | 880 | m_Talk | `UIButton` |
| ComposeUI | 1224 | m_Compose | `UIButton` |
| ComposeUI | 1568 | m_Exit | `UIButton` |
| ComposeUI | 1912 | m_SelBtn | `int` |
| Config | 4 | m_ptr_4 | `_BYTE *` |
| ConfigFile | 0 | m_pDefaultString | `char *` |
| DICOLORSET | 0 | dwSize | `unsigned int` |
| DICOLORSET | 4 | cTextFore | `unsigned int` |
| DICOLORSET | 8 | cTextHighlight | `unsigned int` |
| DICOLORSET | 12 | cCalloutLine | `unsigned int` |
| DICOLORSET | 16 | cCalloutHighlight | `unsigned int` |
| DICOLORSET | 20 | cBorder | `unsigned int` |
| DICOLORSET | 24 | cControlFill | `unsigned int` |
| DICOLORSET | 28 | cHighlightFill | `unsigned int` |
| DICOLORSET | 32 | cAreaFill | `unsigned int` |
| DIDEVCAPS | 0 | dwSize | `unsigned int` |
| DIDEVCAPS | 4 | dwFlags | `unsigned int` |
| DIDEVCAPS | 8 | dwDevType | `unsigned int` |
| DIDEVCAPS | 12 | dwAxes | `unsigned int` |
| DIDEVCAPS | 16 | dwButtons | `unsigned int` |
| DIDEVCAPS | 20 | dwPOVs | `unsigned int` |
| DIDEVCAPS | 24 | dwFFSamplePeriod | `unsigned int` |
| DIDEVCAPS | 28 | dwFFMinTimeResolution | `unsigned int` |
| DIDEVCAPS | 32 | dwFirmwareRevision | `unsigned int` |
| DIDEVCAPS | 36 | dwHardwareRevision | `unsigned int` |
| DIDEVCAPS | 40 | dwFFDriverVersion | `unsigned int` |
| DIDEVICEINSTANCEA | 0 | dwSize | `unsigned int` |
| DIDEVICEINSTANCEA | 4 | guidInstance | `_GUID` |
| DIDEVICEINSTANCEA | 20 | guidProduct | `_GUID` |
| DIDEVICEINSTANCEA | 36 | dwDevType | `unsigned int` |
| DIDEVICEINSTANCEA | 40 | tszInstanceName | `char[324]` |
| DIDEVICEINSTANCEA | 364 | tszProductName | `char[324]` |
| DIDEVICEINSTANCEA | 688 | guidFFDriver | `_GUID` |
| DIDEVICEINSTANCEA | 704 | wUsagePage | `unsigned __int16` |
| DIDEVICEINSTANCEA | 706 | wUsage | `unsigned __int16` |
| DIDEVICEOBJECTDATA | 0 | dwOfs | `unsigned int` |
| DIDEVICEOBJECTDATA | 4 | dwData | `unsigned int` |
| DIDEVICEOBJECTDATA | 8 | dwTimeStamp | `unsigned int` |
| DIDEVICEOBJECTDATA | 12 | dwSequence | `unsigned int` |
| DIDEVICEOBJECTDATA | 16 | uAppData | `unsigned int` |
| DIDEVICEOBJECTINSTANCEA | 0 | dwSize | `unsigned int` |
| DIDEVICEOBJECTINSTANCEA | 4 | guidType | `_GUID` |
| DIDEVICEOBJECTINSTANCEA | 20 | dwOfs | `unsigned int` |
| DIDEVICEOBJECTINSTANCEA | 24 | dwType | `unsigned int` |
| DIDEVICEOBJECTINSTANCEA | 28 | dwFlags | `unsigned int` |
| DIDEVICEOBJECTINSTANCEA | 32 | tszName | `char[324]` |
| DIDEVICEOBJECTINSTANCEA | 356 | dwFFMaxForce | `unsigned int` |
| DIDEVICEOBJECTINSTANCEA | 360 | dwFFForceResolution | `unsigned int` |
| DIDEVICEOBJECTINSTANCEA | 364 | wCollectionNumber | `unsigned __int16` |
| DIDEVICEOBJECTINSTANCEA | 366 | wDesignatorIndex | `unsigned __int16` |
| DIDEVICEOBJECTINSTANCEA | 368 | wUsagePage | `unsigned __int16` |
| DIDEVICEOBJECTINSTANCEA | 370 | wUsage | `unsigned __int16` |
| DIDEVICEOBJECTINSTANCEA | 372 | dwDimension | `unsigned int` |
| DIDEVICEOBJECTINSTANCEA | 376 | wExponent | `unsigned __int16` |
| DIDEVICEOBJECTINSTANCEA | 378 | wReportId | `unsigned __int16` |
| DIEFFECT | 0 | dwSize | `unsigned int` |
| DIEFFECT | 4 | dwFlags | `unsigned int` |
| DIEFFECT | 8 | dwDuration | `unsigned int` |
| DIEFFECT | 12 | dwSamplePeriod | `unsigned int` |
| DIEFFECT | 16 | dwGain | `unsigned int` |
| DIEFFECT | 20 | dwTriggerButton | `unsigned int` |
| DIEFFECT | 24 | dwTriggerRepeatInterval | `unsigned int` |
| DIEFFECT | 28 | cAxes | `unsigned int` |
| DIEFFECT | 32 | rgdwAxes | `unsigned int *` |
| DIEFFECT | 36 | rglDirection | `int *` |
| DIEFFECT | 40 | lpEnvelope | `DIENVELOPE *` |
| DIEFFECT | 44 | cbTypeSpecificParams | `unsigned int` |
| DIEFFECT | 48 | lpvTypeSpecificParams | `char *` |
| DIEFFECT | 52 | dwStartDelay | `unsigned int` |
| DIEFFECTINFOA | 0 | dwSize | `unsigned int` |
| DIEFFECTINFOA | 4 | guid | `_GUID` |
| DIEFFECTINFOA | 20 | dwEffType | `unsigned int` |
| DIEFFECTINFOA | 24 | dwStaticParams | `unsigned int` |
| DIEFFECTINFOA | 28 | dwDynamicParams | `unsigned int` |
| DIEFFECTINFOA | 32 | tszName | `char[324]` |
| DIEFFESCAPE | 0 | dwSize | `unsigned int` |
| DIEFFESCAPE | 4 | dwCommand | `unsigned int` |
| DIEFFESCAPE | 8 | lpvInBuffer | `char *` |
| DIEFFESCAPE | 12 | cbInBuffer | `unsigned int` |
| DIEFFESCAPE | 16 | lpvOutBuffer | `char *` |
| DIEFFESCAPE | 20 | cbOutBuffer | `unsigned int` |
| DIENVELOPE | 0 | dwSize | `unsigned int` |
| DIENVELOPE | 4 | dwAttackLevel | `unsigned int` |
| DIENVELOPE | 8 | dwAttackTime | `unsigned int` |
| DIENVELOPE | 12 | dwFadeLevel | `unsigned int` |
| DIENVELOPE | 16 | dwFadeTime | `unsigned int` |
| DIFILEEFFECT | 0 | dwSize | `unsigned int` |
| DIFILEEFFECT | 4 | GuidEffect | `_GUID` |
| DIFILEEFFECT | 20 | lpDiEffect | `DIEFFECT *` |
| DIFILEEFFECT | 24 | szFriendlyName | `char[324]` |
| DIPROPDWORD | 0 | diph | `DIPROPHEADER` |
| DIPROPDWORD | 16 | dwData | `unsigned int` |
| DIPROPHEADER | 0 | dwSize | `unsigned int` |
| DIPROPHEADER | 4 | dwHeaderSize | `unsigned int` |
| DIPROPHEADER | 8 | dwObj | `unsigned int` |
| DIPROPHEADER | 12 | dwHow | `unsigned int` |
| DPINFO | 0 | active | `int` |
| DPINFO | 4 | provider | `unsigned int` |
| DPINFO | 8 | TYPE | `DPINFO___unnamed` |
| DataConst | 0 | val | `float` |
| DataConst | 4 | name | `char[32]` |
| DealData | 0 | m_isHarshRfus | `BYTE` |
| DealData | 4 | m_LoadTxt | `TxtFile` |
| DealData | 528 | m_LoadGDB | `PAL_GDB` |
| DealData | 815052 | m_IsLang | `BYTE` |
| DealData | 815056 | m_LoadLang | `TxtFile` |
| DealData | 815580 | m_lastFile | `char[256]` |
| DealData | 815836 | m_ManagerData | `st_Manager` |
| DealUI | 72 | _isCreatable | `BYTE` |
| DealUI | 73 | m_Is | `_BYTE[5]` |
| DealUI | 78 | m_ST | `unsigned __int16` |
| DealUI | 80 | m_ID | `unsigned __int16` |
| DealUI | 84 | m_FlagT | `UIStatic` |
| DealUI | 236 | m_FlagB | `UIStatic` |
| DealUI | 388 | m_FlagM | `UIStatic[5]` |
| DealUI | 1148 | mb_BuyEquip | `UIButton` |
| DealUI | 1492 | mb_BuyProp | `UIButton` |
| DealUI | 1836 | mb_Sale | `UIButton` |
| DealUI | 2180 | mb_Talk | `UIButton` |
| DealUI | 2524 | m_IsExit | `BYTE` |
| DealUI | 2528 | mb_Exit | `UIButton` |
| DealUI | 2872 | m_TabBtn | `UITabBtn` |
| DealUI | 2896 | m_BkWnd | `UIStatic` |
| DealUI | 3048 | m_curRender | `int` |
| DealUI | 3052 | pEquipUI | `EquipUI *` |
| DealUI | 3056 | pPropUI | `PropUI *` |
| DealUI | 3060 | pSaleUI | `SaleUI *` |
| DealUI | 3064 | pInterceptTex | `gbTexture *` |
| DealUI | 3068 | sv | `float` |
| DealUI | 3072 | ev | `float` |
| DealUI | 3076 | m_opt | `BYTE` |
| DisplayConfig | 0 | m_nFlags | `int` |
| DisplayConfig | 4 | m_nSettingWidth | `int` |
| DisplayConfig | 8 | m_nSettingHeight | `int` |
| DisplayConfig | 12 | m_pDisplayMode | `char *` |
| EH3_EXCEPTION_REGISTRATION | 0 | Next | `_EH3_EXCEPTION_REGISTRATION *` |
| EH3_EXCEPTION_REGISTRATION | 4 | ExceptionHandler | `PVOID` |
| EH3_EXCEPTION_REGISTRATION | 8 | ScopeTable | `PSCOPETABLE_ENTRY` |
| EH3_EXCEPTION_REGISTRATION | 12 | TryLevel | `unsigned int` |
| EffModeParam | 0 | nSide | `int` |
| EffModeParam | 4 | ePos | `eSkyEffPos` |
| EffModeParam | 8 | bAreaRand | `BYTE` |
| EffObjectPool | 12 | m_pObjects | `void *` |
| EffObjectPool | 28 | m_nCount | `int` |
| EffObjectPool | 32 | m_nCount2 | `int` |
| EffTargetPool | 24 | m_pPool | `void *` |
| EffTargetPool | 28 | m_nCount | `int` |
| EffectInfo | 0 | _pixelPos | `int` |
| EffectInfo | 4 | _dstPixel | `_BYTE[4]` |
| EffectInfo | 8 | _srcPixel | `_BYTE[4]` |
| EffectInfo | 12 | _bbb | `BYTE` |
| EffectItem | 0 | _pixelNum | `int` |
| EffectItem | 4 | _alpha | `BYTE` |
| EffectItem | 8 | _pixelInfo | `char[16]` |
| EquipUI | 72 | bkWndX | `int` |
| EquipUI | 76 | bkWndY | `int` |
| EquipUI | 80 | buf | `char[256]` |
| EquipUI | 336 | m_SelNum | `int` |
| EquipUI | 340 | m_ListNum | `int *` |
| EquipUI | 344 | m_x | `int` |
| EquipUI | 348 | m_y | `int` |
| EquipUI | 352 | m_Sum | `int` |
| EquipUI | 356 | i | `int` |
| EquipUI | 360 | j | `int` |
| EquipUI | 364 | k | `int` |
| EquipUI | 368 | _isCreatable | `unsigned char` |
| EquipUI | 372 | _flashSpeed | `float` |
| EquipUI | 376 | m_EquipData | `st_Manager` |
| EquipUI | 17880 | p_DealData | `PlayerItem *` |
| EquipUI | 17884 | m_TempData | `PlayerAtt[5]` |
| EquipUI | 25504 | rc | `tagRECT` |
| EquipUI | 25520 | m_Frame | `UIStatic` |
| EquipUI | 25680 | m_FrameBar | `UIFlexBar` |
| EquipUI | 25764 | m_Flag | `UIStatic` |
| EquipUI | 25924 | m_OutFrameT | `UIStatic` |
| EquipUI | 26084 | m_OutFrameR | `UIStatic` |
| EquipUI | 26244 | m_OutFrameL | `UIStatic` |
| EquipUI | 26404 | m_OutFrameB | `UIStatic` |
| EquipUI | 26564 | m_ani | `UIAnimateCtrl` |
| EquipUI | 26728 | m_Role | `UIStatic[5]` |
| EquipUI | 27528 | m_RoleRc | `tagRECT[5]` |
| EquipUI | 27608 | RoleX | `int` |
| EquipUI | 27612 | RoleY | `int` |
| EquipUI | 27616 | HeadW | `int` |
| EquipUI | 27620 | HeadH | `int` |
| EquipUI | 27624 | m_Is | `_BYTE[5]` |
| EquipUI | 27632 | m_Arrow | `UIStatic[8][6][5]` |
| EquipUI | 66032 | m_ArrowNum | `UIStatic[8][2][5]` |
| EquipUI | 78832 | m_ArrowRc | `tagRECT[8][6][5]` |
| EquipUI | 82672 | m_IsArrow | `_BYTE[8][6][5]` |
| EquipUI | 82912 | m_OldSelect | `int` |
| EquipUI | 82916 | m_IsMove | `_BYTE[8][6][5]` |
| EquipUI | 83156 | m_AnimateRc | `tagRECT[8][6][5]` |
| EquipUI | 86996 | m_ArrowMove | `UIAnimate[8][6][5]` |
| EquipUI | 99476 | m_Icon | `UIStaticRM[6][5]` |
| EquipUI | 105116 | m_Select | `UIStatic[6][5]` |
| EquipUI | 109916 | m_IsControlEquip | `unsigned char` |
| EquipUI | 109917 | m_IsEquip | `_BYTE[6][5]` |
| EquipUI | 109947 | m_IsMsg | `unsigned char` |
| EquipUI | 109948 | m_EquipingNum | `int *` |
| EquipUI | 109952 | m_Equiping | `int[6][5]` |
| EquipUI | 110072 | m_UnEquipingNum | `int *` |
| EquipUI | 110076 | m_MaxNum | `int *` |
| EquipUI | 110080 | m_Adorn | `_BYTE[2][5]` |
| EquipUI | 110092 | m_3DObj | `UI3DCtrl` |
| EquipUI | 110400 | m_Msg | `MUIDialog` |
| EquipUI | 111784 | m_TalkFrame | `UIStatic` |
| EquipUI | 111944 | m_Ready | `UIStatic` |
| EquipUI | 112104 | m_ReadyRc | `tagRECT` |
| EquipUI | 112120 | mb_EquipYes | `UIButton` |
| EquipUI | 112464 | mb_EquipNo | `UIButton` |
| EquipUI | 112808 | m_EquipTalk | `UIStatic` |
| EquipUI | 112968 | m_EquipRc | `tagRECT` |
| EquipUI | 112984 | m_ListFrame | `UIStatic` |
| EquipUI | 113144 | m_ListGrid | `UIStatic[14]` |
| EquipUI | 115384 | m_ScrollHB | `UIStatic` |
| EquipUI | 115544 | m_EquipFlag | `UIStatic` |
| EquipUI | 115704 | m_ListEquipTitle | `UIStatic` |
| EquipUI | 115864 | ml_ListEquip | `UIListBox` |
| EquipUI | 117152 | ml_ListEquipRc | `tagRECT` |
| EquipUI | 117168 | m_btnGroup | `BtnGroup` |
| EquipUI | 117908 | m_ctrlTime | `float` |
| EquipUI | 117912 | m_bCanUpdate1 | `unsigned char` |
| EquipUI | 117913 | m_bCanUpdate2 | `unsigned char` |
| EquipUI | 117916 | m_EquipRemarkBk | `UIStatic` |
| EquipUI | 118076 | m_EquipRemark | `UIStatic` |
| EquipUI | 118236 | m_EquipRemarkRc | `tagRECT` |
| EquipUI | 118252 | m_EquipAtt | `UIStatic` |
| EquipUI | 118412 | m_EquipAttRc | `tagRECT` |
| EquipUI | 118428 | m_MoneyRemark | `UIStatic` |
| EquipUI | 118588 | m_MoneyRc | `tagRECT` |
| EquipUI | 118604 | m_SumEquip | `UIStatic` |
| EquipUI | 118764 | m_SumRc | `tagRECT` |
| EquipUI | 118780 | mb_OK | `UIButton` |
| EquipUI | 119124 | mb_OKRc | `tagRECT` |
| EquipUI | 119140 | m_IsDicker | `unsigned char` |
| EquipUI | 119144 | mb_Cancel | `UIButton` |
| EquipUI | 119488 | mb_CancelRc | `tagRECT` |
| EquipUI | 119504 | mb_Exit | `UIButton` |
| EquipUI | 119848 | mb_ExitRc | `tagRECT` |
| EquipUI | 119864 | m_TabBtn | `UITabBtn` |
| EquipUI | 119888 | mb_DKRc | `tagRECT` |
| EquipUI | 119904 | haveRc | `tagRECT` |
| EquipUI | 119920 | m_isCancelTalk | `unsigned char` |
| FILETIME | 0 | dwLowDateTime | `int` |
| FILETIME | 4 | dwHighDateTime | `int` |
| FLOATING_SAVE_AREA | 0 | ControlWord | `unsigned int` |
| FLOATING_SAVE_AREA | 4 | StatusWord | `unsigned int` |
| FLOATING_SAVE_AREA | 8 | TagWord | `unsigned int` |
| FLOATING_SAVE_AREA | 12 | ErrorOffset | `unsigned int` |
| FLOATING_SAVE_AREA | 16 | ErrorSelector | `unsigned int` |
| FLOATING_SAVE_AREA | 20 | DataOffset | `unsigned int` |
| FLOATING_SAVE_AREA | 24 | DataSelector | `unsigned int` |
| FLOATING_SAVE_AREA | 108 | Cr0NpxState | `unsigned int` |
| FLTSTAGE | 0 | provider | `_FLTPROVIDER *` |
| FLTSTAGE | 4 | sample_state | `int` |
| FightInfo | 0 | monsterID | `unsigned int[6]` |
| FightInfo | 24 | nAllMonsterNum | `int` |
| FightInfo | 28 | nMaxRound | `int` |
| FightInfo | 32 | sSceneName | `char[32]` |
| FightInfo | 64 | eSceneFiveMagic | `ECBFiveMagic` |
| FightInfo | 68 | eMeetType | `ECBMeetEnemy` |
| FightInfo | 72 | eBattleFieldAttr | `ECBBattleFieldAttr` |
| FightInfo | 76 | bMustFail | `BYTE` |
| FightInfo | 80 | nRoleWillNotBeAttack | `int` |
| FightInfo | 84 | bScript | `BYTE` |
| FightInfo | 85 | bBossMusic | `BYTE` |
| FightInfo | 86 | bFiveNimbus | `BYTE` |
| FightInfo | 87 | bPXVariance | `BYTE` |
| FightInfo | 88 | bFirst | `BYTE` |
| FightInfo | 92 | pMosnter | `Role *` |
| FightItem | 0 | id | `unsigned int` |
| FightItem | 4 | name | `char[32]` |
| FightItem | 36 | ModelID | `char[30]` |
| FightItem | 66 | ImageID | `char[30]` |
| FightItem | 96 | desc | `_inline_FightItem_desc` |
| FightItem | 608 | price | `int` |
| FightItem | 612 | type | `BYTE` |
| FightItem | 613 | weapontype | `BYTE` |
| FightItem | 614 | user | `_BYTE[5]` |
| FightItem | 619 | att | `_BYTE[5]` |
| FightItem | 624 | gu | `int` |
| FightItem | 628 | special | `BYTE` |
| FightItem | 629 | fanwei | `BYTE` |
| FightItem | 630 | space | `BYTE` |
| FightItem | 631 | rvtype | `_BYTE[12]` |
| FightItem | 644 | rolevalue | `signed __int16[12]` |
| FightItem | 668 | fstype | `_BYTE[31]` |
| FightItem | 700 | fightstate | `signed __int16[31]` |
| FightItem | 764 | tosshurt | `int` |
| FightItem | 768 | lian | `int` |
| FightItem | 772 | saveqi | `signed __int16` |
| FightItem | 774 | saveshen | `signed __int16` |
| FightItem | 776 | addbaoji | `signed __int16` |
| FightItem | 778 | addteji | `signed __int16` |
| FightItem | 780 | embracer | `int` |
| FightItem | 784 | compose_material | `unsigned int` |
| FightItem | 788 | compose_type | `int` |
| FightItem | 792 | compose_final | `unsigned int` |
| FightItem | 796 | compose_intimacy | `unsigned int` |
| FightItemScriptBlock | 356 | bLoaded | `char` |
| FightItemScriptBlock | 360 | pScriptData | `char[152]` |
| FightSkill | 0 | id | `unsigned int` |
| FightSkill | 4 | type | `BYTE` |
| FightSkill | 8 | att | `int[5]` |
| FightSkill | 28 | name | `char[32]` |
| FightSkill | 60 | desc | `char[512]` |
| FightSkill | 572 | user | `_BYTE[5]` |
| FightSkill | 577 | fanwei | `BYTE` |
| FightSkill | 578 | special | `BYTE` |
| FightSkill | 579 | rvtype | `_BYTE[12]` |
| FightSkill | 592 | rolevalue | `signed __int16[12]` |
| FightSkill | 616 | succ | `BYTE` |
| FightSkill | 618 | fs | `signed __int16[31]` |
| FightSkill | 680 | consumervtype | `int[2]` |
| FightSkill | 688 | consumetype | `int[3]` |
| FightSkill | 700 | tutype | `BYTE` |
| FightSkill | 704 | tusuval | `int` |
| FightSkill | 708 | lv | `BYTE` |
| FightSkill | 709 | lvup | `_BYTE[4]` |
| FightSkill | 713 | rolelv | `BYTE` |
| FightSkill | 714 | magiclv | `BYTE` |
| FightSkill | 716 | nextid | `unsigned int` |
| FightSkill | 720 | isuseall | `BYTE` |
| FightSkill | 724 | hecheng | `unsigned int[3]` |
| FightSkill | 736 | heskill | `unsigned int[3]` |
| FightSkill | 748 | helv | `_BYTE[3]` |
| FightSkill | 751 | helvself | `_BYTE[3]` |
| FightSkill | 754 | manlv | `_BYTE[3]` |
| FightSkill | 757 | heji | `BYTE` |
| FindArc | 0 | mPal3SetUpPath | `char[256]` |
| FindArc | 256 | arcPos | `ArcPosition[36]` |
| FindArc | 9472 | mRealNum | `int` |
| FontPrint3DInfo | 0 | font | `gbFontType` |
| FontPrint3DInfo | 4 | x | `float` |
| FontPrint3DInfo | 8 | y | `float` |
| FontPrint3DInfo | 12 | z | `float` |
| FontPrint3DInfo | 16 | strloc | `int` |
| FontPrint3DInfo | 20 | strlen | `int` |
| FontPrint3DInfo | 24 | scalex | `float` |
| FontPrint3DInfo | 28 | scaley | `float` |
| FontPrint3DInfo | 32 | color | `gbColorQuad` |
| FontPrintInfo | 0 | font | `gbFontType` |
| FontPrintInfo | 4 | x | `float` |
| FontPrintInfo | 8 | y | `float` |
| FontPrintInfo | 12 | z | `float` |
| FontPrintInfo | 16 | endx | `float` |
| FontPrintInfo | 20 | endy | `float` |
| FontPrintInfo | 24 | strloc | `int` |
| FontPrintInfo | 28 | strlen | `int` |
| FontPrintInfo | 32 | scalex | `float` |
| FontPrintInfo | 36 | scaley | `float` |
| FontPrintInfo | 40 | color | `gbColorQuad` |
| FontSortInfoObj | 0 | index | `int` |
| FontSortInfoObj | 4 | z | `float` |
| FrameTex | 0 | m_pTex | `gbTexture *` |
| FuncInfoV1 | 0 | magicNumber | `int` |
| FuncInfoV1 | 4 | maxState | `int` |
| FuncInfoV1 | 8 | pUnwindMap | `char *` |
| FuncInfoV1 | 12 | nTryBlocks | `int` |
| FuncInfoV1 | 16 | pTryBlockMap | `char *` |
| FuncInfoV1 | 20 | nIPMapEntries | `int` |
| FuncInfoV1 | 24 | pIPtoStateMap | `char *` |
| GRP_KEYREG | 0 | Data | `int` |
| GRP_KEYREG | 4 | HoldTime | `int` |
| GRP_KEYREG | 8 | CountMode | `int` |
| GRP_KEYREG | 12 | PressTime | `int` |
| GRPinput | 0 | m_lpDI | `IDirectInput8 *` |
| GRPinput | 4 | m_lpDIDKeyboard | `IDirectInputDevice8 *` |
| GRPinput | 8 | m_lpDIDMouse | `IDirectInputDevice8 *` |
| GRPinput | 12 | m_mouseSensitivity | `float` |
| GRPinput | 16 | m_mouseMinX | `int` |
| GRPinput | 20 | m_mouseMinY | `int` |
| GRPinput | 24 | m_mouseMaxX | `int` |
| GRPinput | 28 | m_mouseMaxY | `int` |
| GRPinput | 32 | m_joystickMinX | `int` |
| GRPinput | 36 | m_joystickMinY | `int` |
| GRPinput | 40 | m_joystickMaxX | `int` |
| GRPinput | 44 | m_joystickMaxY | `int` |
| GRPinput | 48 | m_mousept | `POINT` |
| GRPinput | 56 | m_mouseX | `int` |
| GRPinput | 60 | m_mouseY | `int` |
| GRPinput | 64 | m_mouseFreeX | `int` |
| GRPinput | 68 | m_mouseFreeY | `int` |
| GRPinput | 72 | m_mouseDeltaX | `int` |
| GRPinput | 76 | m_mouseDeltaY | `int` |
| GRPinput | 80 | m_joystickX | `int` |
| GRPinput | 84 | m_joystickY | `int` |
| GRPinput | 88 | m_joystickFreeX | `int` |
| GRPinput | 92 | m_joystickFreeY | `int` |
| GRPinput | 96 | m_joystickDeltaX | `int` |
| GRPinput | 100 | m_joystickDeltaY | `int` |
| GRPinput | 104 | m_keyStates | `_BYTE[270]` |
| GRPinput | 376 | m_keyRaw | `_BYTE[256]` |
| GRPinput | 632 | m_keyPressTimes | `ULONG[270]` |
| GRPinput | 1712 | m_keyDragStartPositions | `ULONG[270][2]` |
| GRPinput | 3872 | m_shiftedKeyStates | `_BYTE[270]` |
| GRPinput | 4144 | m_DIKToKEY | `ULONG[256]` |
| GRPinput | 5168 | MouseState | `char[20]` |
| GRPinput | 5188 | charTOscan | `ULONG[256]` |
| GRPinput | 6212 | KeyTransformation | `int[10]` |
| GRPinput | 6252 | m_bMouse | `int` |
| GRPinput | 6256 | m_bKeyboard | `int` |
| GRPinput | 6260 | m_bJoystick | `int` |
| GRPinput | 6264 | KeyInfo | `GRP_KEYREG[270]` |
| GeomNode | 0 | pNext | `GeomNode *` |
| GeomNode | 4 | pParent | `GeomNode *` |
| GeomNode | 8 | children | `char[16]` |
| GeomNode | 92 | worldTransform | `Matrix4` |
| GeomNode | 156 | staticTransform | `Matrix4` |
| GeomNode | 256 | m_nTodo_100 | `int` |
| GeomNode | 272 | mesh | `int` |
| GeomNote | 0 | scene | `char[4]` |
| GeomNote | 4 | area | `char[2]` |
| GeomNote | 6 | flag | `BYTE` |
| GhostParam | 0 | name | `char[32]` |
| GhostParam | 32 | id | `unsigned int` |
| GhostParam | 36 | Type | `int` |
| GhostParam | 40 | HP | `int` |
| GhostParam | 44 | ATK | `int` |
| Glow | 0 | m_eft | `gbRenderEffect *` |
| Glow | 4 | m_pGeomEft | `gbRenderEffect *` |
| Glow | 8 | m_nPass | `int` |
| Glow | 12 | m_pObjArray | `char[16]` |
| GlowObj | 4 | m_bEnable | `BYTE` |
| GlowObj | 8 | m_nStepSize | `int` |
| GlowObj | 12 | m_nPass | `int` |
| GlowObj | 16 | m_GeomColor | `gbColorFlt` |
| GrayScale | 0 | m_bEnable | `BYTE` |
| GrayScale | 4 | m_pTex | `gbTexture *` |
| HandlerType | 0 | adjectives | `int` |
| HandlerType | 4 | pType | `TypeDescriptor *` |
| HandlerType | 8 | dispCatchObj | `int` |
| HandlerType | 12 | addressOfHandler | `char *` |
| HeadMsg | 4 | m_bEnable | `unsigned char` |
| HeadMsg | 8 | m_szMsg | `char[16]` |
| HeadMsg | 24 | m_fTime | `float` |
| HeadMsg | 28 | m_nType | `int` |
| HeadMsg | 32 | m_nY | `int` |
| IMAGE_DATA_DIRECTORY | 0 | VirtualAddress | `int` |
| IMAGE_DATA_DIRECTORY | 4 | Size | `int` |
| IMAGE_FILE_HEADER | 0 | Machine | `int` |
| IMAGE_FILE_HEADER | 4 | NumberOfSections | `int` |
| IMAGE_FILE_HEADER | 8 | TimeDateStamp | `int` |
| IMAGE_FILE_HEADER | 12 | PointerToSymbolTable | `int` |
| IMAGE_FILE_HEADER | 16 | NumberOfSymbols | `int` |
| IMAGE_FILE_HEADER | 20 | SizeOfOptionalHeader | `int` |
| IMAGE_FILE_HEADER | 24 | Characteristics | `int` |
| IMAGE_OPTIONAL_HEADER32 | 0 | Magic | `int` |
| IMAGE_OPTIONAL_HEADER32 | 4 | MajorLinkerVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 8 | MinorLinkerVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 12 | SizeOfCode | `int` |
| IMAGE_OPTIONAL_HEADER32 | 16 | SizeOfInitializedData | `int` |
| IMAGE_OPTIONAL_HEADER32 | 20 | SizeOfUninitializedData | `int` |
| IMAGE_OPTIONAL_HEADER32 | 24 | AddressOfEntryPoint | `int` |
| IMAGE_OPTIONAL_HEADER32 | 28 | BaseOfCode | `int` |
| IMAGE_OPTIONAL_HEADER32 | 32 | BaseOfData | `int` |
| IMAGE_OPTIONAL_HEADER32 | 36 | ImageBase | `int` |
| IMAGE_OPTIONAL_HEADER32 | 40 | SectionAlignment | `int` |
| IMAGE_OPTIONAL_HEADER32 | 44 | FileAlignment | `int` |
| IMAGE_OPTIONAL_HEADER32 | 48 | MajorOperatingSystemVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 52 | MinorOperatingSystemVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 56 | MajorImageVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 60 | MinorImageVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 64 | MajorSubsystemVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 68 | MinorSubsystemVersion | `int` |
| IMAGE_OPTIONAL_HEADER32 | 72 | Win32VersionValue | `int` |
| IMAGE_OPTIONAL_HEADER32 | 76 | SizeOfImage | `int` |
| IMAGE_OPTIONAL_HEADER32 | 80 | SizeOfHeaders | `int` |
| IMAGE_OPTIONAL_HEADER32 | 84 | CheckSum | `int` |
| IMAGE_OPTIONAL_HEADER32 | 88 | Subsystem | `int` |
| IMAGE_OPTIONAL_HEADER32 | 92 | DllCharacteristics | `int` |
| IMAGE_OPTIONAL_HEADER32 | 96 | SizeOfStackReserve | `int` |
| IMAGE_OPTIONAL_HEADER32 | 100 | SizeOfStackCommit | `int` |
| IMAGE_OPTIONAL_HEADER32 | 104 | SizeOfHeapReserve | `int` |
| IMAGE_OPTIONAL_HEADER32 | 108 | SizeOfHeapCommit | `int` |
| IMAGE_OPTIONAL_HEADER32 | 112 | LoaderFlags | `int` |
| IMAGE_OPTIONAL_HEADER32 | 116 | NumberOfRvaAndSizes | `int` |
| Inventory | 0 | m_items | `char[16]` |
| Inventory | 16 | m_curtype | `int` |
| Inventory | 20 | m_typeitems | `char[16]` |
| Inventory | 36 | m_money | `int` |
| JusticeBookUI | 72 | rc | `tagRECT` |
| JusticeBookUI | 88 | bkWndX | `int` |
| JusticeBookUI | 92 | bkWndY | `int` |
| JusticeBookUI | 96 | i | `int` |
| JusticeBookUI | 100 | j | `int` |
| JusticeBookUI | 104 | buf | `char[256]` |
| JusticeBookUI | 360 | m_IsMsg | `unsigned char` |
| JusticeBookUI | 361 | m_IsActive | `unsigned char` |
| JusticeBookUI | 362 | m_IsExit | `unsigned char` |
| JusticeBookUI | 363 | m_IsOpen | `unsigned char` |
| JusticeBookUI | 364 | m_BK | `UIStatic` |
| JusticeBookUI | 524 | m_Exit | `UIButton` |
| JusticeBookUI | 868 | m_OutFrameT | `UIStatic` |
| JusticeBookUI | 1028 | m_OutFrameR | `UIStatic` |
| JusticeBookUI | 1188 | m_OutFrameL | `UIStatic` |
| JusticeBookUI | 1348 | m_OutFrameB | `UIStatic` |
| JusticeBookUI | 1508 | m_JusticeBook | `UI3DCtrl` |
| JusticeBookUI | 1816 | m_Monster | `UI3DCtrl` |
| JusticeBookUI | 2124 | m_Name | `UIStatic` |
| JusticeBookUI | 2284 | m_H | `UIStatic` |
| JusticeBookUI | 2444 | m_S | `UIStatic` |
| JusticeBookUI | 2604 | m_Wuling | `UIStatic[5]` |
| JusticeBookUI | 3404 | m_Att | `UIStatic[5]` |
| JusticeBookUI | 4204 | m_Sorcery | `UIStatic[4]` |
| JusticeBookUI | 4844 | m_SorceryRc | `tagRECT[4]` |
| JusticeBookUI | 4908 | m_Remark | `UIStatic` |
| JusticeBookUI | 5068 | m_Number | `UIStatic` |
| JusticeBookUI | 5228 | m_PgUp | `UIButton` |
| JusticeBookUI | 5572 | m_PgDw | `UIButton` |
| JusticeBookUI | 5916 | m_tpGods | `UIPushButton` |
| JusticeBookUI | 6168 | m_tpImmortal | `UIPushButton` |
| JusticeBookUI | 6420 | m_tpGhost | `UIPushButton` |
| JusticeBookUI | 6672 | m_tpDemon | `UIPushButton` |
| JusticeBookUI | 6924 | m_tpHuman | `UIPushButton` |
| JusticeBookUI | 7176 | m_tpMagic | `UIPushButton` |
| JusticeBookUI | 7428 | m_tpGods_unopen | `UIPushButton` |
| JusticeBookUI | 7680 | m_tpImmortal_unopen | `UIPushButton` |
| JusticeBookUI | 7932 | m_tpGhost_unopen | `UIPushButton` |
| JusticeBookUI | 8184 | m_tpDemon_unopen | `UIPushButton` |
| JusticeBookUI | 8436 | m_tpHuman_unopen | `UIPushButton` |
| JusticeBookUI | 8688 | m_tpMagic_unopen | `UIPushButton` |
| JusticeBookUI | 8940 | m_allMonsters | `unsigned int *` |
| JusticeBookUI | 8944 | m_MonstersNum | `int` |
| JusticeBookUI | 8948 | m_tpNum | `int[6]` |
| JusticeBookUI | 8972 | m_tpID | `unsigned int[100][6]` |
| JusticeBookUI | 11372 | m_bookMark | `JB_TYPE` |
| JusticeBookUI | 11376 | m_curMark | `JB_TYPE` |
| JusticeBookUI | 11380 | m_Page | `int` |
| JusticeBookUI | 12744 | m_DialogState | `int` |
| JusticeBookUI | 12752 | m_Dialog | `UIRoleDialog` |
| JusticeBookUI | 14124 | m_ParticlesA | `UIParticle[36]` |
| JusticeBookUI | 35148 | m_ParticlesB | `UIParticle[36]` |
| JusticeBookUI | 56188 | m_FadeState | `_BYTE[2]` |
| KeyFrame | 0 | emitterAttr | `CParticleSystem::EmitterAttribute` |
| KeyFrame | 220 | pPositionPolicy | `CPolicy *` |
| KeyFrame | 224 | pDirectionPolicy | `CPolicy *` |
| KeyFrame | 228 | pColorPolicy | `CPolicy *` |
| KeyFrame | 232 | pAlphaPolicy | `CPolicy *` |
| KeyFrame | 236 | pFramePolicy | `CPolicy *` |
| KeyFrame | 240 | pEmitterPolicy | `CPolicy *` |
| KeyFrame | 244 | fTime | `float` |
| KeyFrame | 248 | dwReserved | `unsigned int[4]` |
| LARGE_INTEGER | 0 | LowPart | `int` |
| LARGE_INTEGER | 4 | HighPart | `int` |
| LARGE_INTEGER | 8 | u | `int` |
| LARGE_INTEGER | 16 | QuadPart | `signed __int64` |
| LEVELPARAM | 0 | nMonster | `int` |
| LEVELPARAM | 4 | nSecond | `int` |
| LINEUPINFO | 0 | Info | `_BYTE[6]` |
| LINEUP_SEQUENCE | 0 | Role_Sequence | `_BYTE[5]` |
| LayerNode | 0 | m_bound | `gbAABBox` |
| LayerNode | 24 | m_lv | `int` |
| LayerNode | 28 | m_tri | `char[16]` |
| LayerNode | 44 | m_child | `LayerNode *[4]` |
| LineupComp | 68 | m_ObjPos | `gbVec3D[4]` |
| LineupComp | 120 | m_LineupObj | `Object3D` |
| LineupComp | 272 | m_3DRole | `Object3D[5]` |
| LineupComp | 1032 | m_isRoleIn | `_BYTE[5]` |
| LineupComp | 1040 | m_3DNone | `Object3D[6]` |
| LineupComp | 1952 | m_is3DNoneIn | `_BYTE[6]` |
| LineupComp | 1960 | m_pCamera | `ObjectCamera *` |
| LineupComp | 1964 | m_objCamPitch | `float` |
| LineupComp | 1968 | m_objRotSpeed | `float` |
| LineupComp | 1972 | m_pointerHeight | `float` |
| LineupComp | 1976 | m_isRotLineup | `BYTE` |
| LineupComp | 1980 | m_RoleId | `int` |
| LineupComp | 1984 | m_nRole | `int` |
| LineupComp | 1988 | m_bClickRole | `BYTE` |
| LineupPlank | 0 | m_Up | `UIStatic` |
| LineupPlank | 152 | m_Name | `UIStatic` |
| LineupPlank | 304 | m_Dw | `UIStatic` |
| LineupPlank | 456 | m_Btn | `char[256]` |
| LineupUI | 72 | rc | `tagRECT` |
| LineupUI | 88 | bkWndX | `int` |
| LineupUI | 92 | bkWndY | `int` |
| LineupUI | 96 | i | `int` |
| LineupUI | 100 | j | `int` |
| LineupUI | 104 | buf | `char[256]` |
| LineupUI | 360 | m_IsMsg | `unsigned char` |
| LineupUI | 361 | m_Is | `_BYTE[5]` |
| LineupUI | 368 | m_Frame | `UIStatic` |
| LineupUI | 528 | m_TimeMoney | `UIStatic` |
| LineupUI | 688 | m_OutFrameT | `UIStatic` |
| LineupUI | 848 | m_OutFrameR | `UIStatic` |
| LineupUI | 1008 | m_OutFrameL | `UIStatic` |
| LineupUI | 1168 | m_OutFrameB | `UIStatic` |
| LineupUI | 1328 | stp_BarL | `UIStatic` |
| LineupUI | 1488 | stp_BarM | `UIFlexBar` |
| LineupUI | 1572 | stp_BarR | `UIStatic` |
| LineupUI | 1732 | stp_State | `UIButton` |
| LineupUI | 2076 | stp_Magic | `UIButton` |
| LineupUI | 2420 | stp_Equip | `UIButton` |
| LineupUI | 2764 | stp_Prop | `UIButton` |
| LineupUI | 3108 | stp_BattleArray | `UIButton` |
| LineupUI | 3452 | stp_TaskBook | `UIButton` |
| LineupUI | 3796 | stp_System | `UIButton` |
| LineupUI | 4140 | stp_Exit | `UIButton` |
| LineupUI | 4484 | stp_Effect | `UIStatic` |
| LineupUI | 4644 | stp_Rect | `tagRECT` |
| LineupUI | 4660 | m_GameTime | `UIStatic` |
| LineupUI | 4820 | m_GameMoney | `UIStatic` |
| LineupUI | 4980 | m_DlgEx | `MUIDialog` |
| LineupUI | 6364 | m_ZhenLie | `UIStatic` |
| LineupUI | 6524 | m_btnPar | `UIParticle[16][7]` |
| LineupUI | 72828 | m_btnPar2 | `UIParticle[16][7]` |
| LineupUI | 139132 | m_btnParRc | `tagRECT[7]` |
| LineupUI | 139244 | _isParBtn | `_BYTE[7]` |
| LineupUI | 139252 | _curParEffect | `int` |
| LineupUI | 139256 | m_LineupInfo | `LINEUPINFO[5]` |
| LineupUI | 139286 | m_Sequence | `char[4]` |
| LineupUI | 139292 | roleRc | `tagRECT` |
| LineupUI | 139308 | m_RoleFrame | `UIStatic` |
| LineupUI | 139468 | m_RoleBtn | `UIButton[5]` |
| LineupUI | 141188 | m_RoleBtnIndex | `int[5]` |
| LineupUI | 141208 | m_NoBody | `UIStatic[5]` |
| LineupUI | 142008 | m_RoleLeader | `UIStatic[5]` |
| LineupUI | 142808 | m_headRc | `tagRECT[5]` |
| LineupUI | 142888 | m_headRole | `int` |
| LineupUI | 142892 | m_Msg | `MUIDialog` |
| LineupUI | 144276 | m_objCamPitch | `float` |
| LineupUI | 144280 | m_objRotSpeed | `float` |
| LineupUI | 144284 | m_pCamera | `ObjectCamera *` |
| LineupUI | 144288 | m_pointerHeight | `float` |
| LineupUI | 144292 | m_bPeek | `unsigned char` |
| LineupUI | 144296 | m_nPeek | `int` |
| LineupUI | 144300 | m_nLastPeek | `int` |
| LineupUI | 144304 | m_isRotLineup | `unsigned char` |
| LineupUI | 144308 | m_ObjPos | `gbVec3D[6]` |
| LineupUI | 144380 | m_LineupObj | `Object3D` |
| LineupUI | 144532 | m_3DRole | `Object3D[5]` |
| LineupUI | 145292 | m_IsRole | `_BYTE[6]` |
| LineupUI | 145300 | m_RoleId | `int[6]` |
| LineupUI | 145324 | m_3DNone | `Object3D[6]` |
| LineupUI | 146236 | m_CtrlPlank | `LineupPlank[5]` |
| LineupUI | 156196 | m_ProtectPanel | `ProtectPanel` |
| LineupUI | 157484 | m_ProFlag | `unsigned char` |
| LineupUI | 157488 | pStateUI | `StateUI *` |
| LinkerVersion | 0 | bverMajor | `BYTE` |
| LinkerVersion | 1 | bverMinor | `BYTE` |
| Logger | 0 | m_nCallbackCount | `int` |
| Logger | 4 | m_callbacks | `tagLoggerCallback[34]` |
| Logger | 4628 | m_nRenderX | `int` |
| Logger | 4632 | m_nRenderY | `int` |
| Logger | 4636 | m_bRenderEnabled | `int` |
| Logger | 4640 | m_pRenderTarget | `void *` |
| Logger | 4644 | m_nRenderMode | `int` |
| Logger | 4648 | m_nRenderCount | `int` |
| Logger | 4652 | m_szCmdBuf2 | `char[4]` |
| Logger | 4656 | m_szCmdBuf | `char[100]` |
| Logger | 4756 | m_nRenderState | `int` |
| Logger | 4856 | m_nTodo_12F8 | `void *` |
| MIXSTAGE | 0 | MSS_mixer_flush | `char *` |
| MIXSTAGE | 4 | MSS_mixer_merge | `char *` |
| MIXSTAGE | 8 | MSS_mixer_copy | `char *` |
| MUIDialog | 72 | ptr_Dlg | `UIWnd *` |
| MUIDialog | 76 | m_DlgId | `unsigned int` |
| MUIDialog | 80 | m_rect | `tagRECT` |
| MUIDialog | 96 | m_textRc | `tagRECT` |
| MUIDialog | 112 | m_bk | `UIStaticFlex` |
| MUIDialog | 304 | m_static | `UIStatic` |
| MUIDialog | 464 | m_text | `UIStatic` |
| MUIDialog | 624 | m_btnW | `int` |
| MUIDialog | 628 | m_btnH | `int` |
| MUIDialog | 632 | m_btRc | `_inline_MUIDialog_m_btRc` |
| MUIDialog | 976 | pCallbackVtable2 | `void *` |
| MUIDialogMgr | 0 | refrence_counter | `int` |
| MU_SortFun | 0 | m_by | `int` |
| MXCEft | 92 | m_dwEffectID | `unsigned int` |
| MXCEft | 96 | m_hEffect | `unsigned int` |
| MXCEft | 100 | m_pos | `gbVec3D` |
| MXCEft | 112 | m_fTime | `float` |
| MXFire | 92 | m_nCurTex | `int` |
| MXFire | 96 | m_fTime | `float` |
| MXFire | 100 | m_pEffect | `gbRenderEffect *` |
| MXFire | 104 | m_pTexs | `gbTexture *[16]` |
| MXFire | 168 | m_ta | `gbTextureArray` |
| MXFire | 236 | m_pFlare | `gbTexture *` |
| MXFire | 240 | m_candle | `gbGeomNode *` |
| MXFire | 244 | m_type | `unsigned int` |
| MXPoisonFog | 92 | m_pfog | `gbParticleEffect *` |
| MXSavePoint | 92 | m_fTime | `float` |
| MXSavePoint | 96 | m_aTex | `gbTextureArray` |
| MXSavePoint | 164 | m_pTex | `gbTexture *` |
| MXSavePoint | 168 | m_pEffect | `gbRenderEffect *` |
| MXSavePoint | 172 | m_trans | `gbGeomQuad` |
| MXSavePoint | 240 | m_quads | `gbGeomQuad[12]` |
| MXSavePoint | 1056 | m_stone | `gbGeomNode *` |
| MXTransport | 92 | m_fTime | `float` |
| MXTransport | 96 | m_pTransTex | `gbTexture *` |
| MXTransport | 100 | m_aTex | `gbTextureArray` |
| MXTransport | 168 | m_pEffect | `gbRenderEffect *` |
| MXTransport | 172 | m_pEffectA | `gbRenderEffect *` |
| MXTransport | 176 | m_quads | `gbGeomQuad[6]` |
| MXTransport | 584 | m_quads2 | `gbGeomQuad[6]` |
| MXTransport | 992 | m_trans | `gbGeomQuad` |
| MXTransport | 1060 | m_height | `gbVec2D[4]` |
| MXTransport | 1092 | m_ok | `int[4]` |
| MXTransport | 1108 | m_test | `ParticleEffect` |
| MagicUI | 72 | m_ComSkill | `char[208]` |
| MagicUI | 280 | m_tabRemarkBuf | `char[256]` |
| MagicUI | 536 | s_x | `int` |
| MagicUI | 540 | m_IsMsg | `BYTE` |
| MagicUI | 541 | m_Is | `_BYTE[5]` |
| MagicUI | 548 | m_CtrlRole | `int` |
| MagicUI | 552 | m_IsActive | `BYTE` |
| MagicUI | 553 | m_IsCreateable | `BYTE` |
| MagicUI | 556 | curPage | `int` |
| MagicUI | 560 | m_SelNum | `int` |
| MagicUI | 564 | m_CurType | `int` |
| MagicUI | 568 | m_usemagicRole | `int` |
| MagicUI | 572 | m_isuseMagic | `BYTE` |
| MagicUI | 573 | m_LockUse | `BYTE` |
| MagicUI | 574 | m_IsUsed | `BYTE` |
| MagicUI | 575 | m_IsCanUse | `BYTE` |
| MagicUI | 576 | m_IsAllUse | `BYTE` |
| MagicUI | 580 | pt | `tagPOINT` |
| MagicUI | 588 | m_RoleSkill | `SkillData[7][5]` |
| MagicUI | 42308 | pStateUI | `StateUI *` |
| MagicUI | 42312 | m_Frame | `UIStatic` |
| MagicUI | 42464 | m_TimeMoney | `UIStatic` |
| MagicUI | 42616 | m_OutFrameT | `UIStatic` |
| MagicUI | 42768 | m_OutFrameR | `UIStatic` |
| MagicUI | 42920 | m_OutFrameL | `UIStatic` |
| MagicUI | 43072 | m_OutFrameB | `UIStatic` |
| MagicUI | 43224 | stp_BarL | `UIStatic` |
| MagicUI | 43376 | stp_BarM | `UIFlexBar` |
| MagicUI | 43460 | stp_BarR | `UIStatic` |
| MagicUI | 43612 | stp_State | `UIButton` |
| MagicUI | 43956 | stp_Magic | `UIButton` |
| MagicUI | 44300 | stp_Equip | `UIButton` |
| MagicUI | 44644 | stp_Prop | `UIButton` |
| MagicUI | 44988 | stp_BattleArray | `UIButton` |
| MagicUI | 45332 | stp_TaskBook | `UIButton` |
| MagicUI | 45676 | stp_System | `UIButton` |
| MagicUI | 46020 | stp_Exit | `UIButton` |
| MagicUI | 46364 | stp_Effect | `UIStatic` |
| MagicUI | 46516 | stp_Rect | `tagRECT` |
| MagicUI | 46532 | titleRc | `tagRECT` |
| MagicUI | 46548 | m_title | `UIStatic[4]` |
| MagicUI | 47156 | m_GameTime | `UIStatic` |
| MagicUI | 47308 | m_GameMoney | `UIStatic` |
| MagicUI | 47460 | m_DlgEx | `MUIDialog` |
| MagicUI | 48844 | m_btnPar | `UIParticle[16][7]` |
| MagicUI | 115148 | m_btnPar2 | `UIParticle[16][7]` |
| MagicUI | 181452 | m_btnParRc | `tagRECT[7]` |
| MagicUI | 181564 | _isParBtn | `_BYTE[7]` |
| MagicUI | 181572 | _curParEffect | `int` |
| MagicUI | 181576 | m_CurSelRole | `int` |
| MagicUI | 181580 | m_CurNeedRole | `int` |
| MagicUI | 181584 | m_Dlg | `MUIDialog` |
| MagicUI | 182968 | m_Msg | `MUIDialog` |
| MagicUI | 184352 | m_DlgMsg | `DLG_MSG` |
| MagicUI | 184356 | m_Animate | `UIAnimate[5]` |
| MagicUI | 184616 | m_AnimateRc | `tagRECT[5]` |
| MagicUI | 184696 | m_ListFrame | `UIStatic` |
| MagicUI | 184848 | m_ListGrid | `UIStatic[8]` |
| MagicUI | 186064 | m_RemarkBk | `UIStatic` |
| MagicUI | 186216 | m_Remark | `UIStatic` |
| MagicUI | 186368 | m_RemarkVal | `UIStatic` |
| MagicUI | 186520 | m_UnCom | `UIStatic` |
| MagicUI | 186672 | m_Role | `m_RoleState[5]` |
| MagicUI | 208132 | m_Ctrlbtn | `UIButton[7]` |
| MagicUI | 210540 | ml_SpeList | `UIListBox` |
| MagicUI | 211828 | ml_FengList | `UIListBox` |
| MagicUI | 213116 | ml_LeiList | `UIListBox` |
| MagicUI | 214404 | ml_ShuiList | `UIListBox` |
| MagicUI | 215692 | ml_HuoList | `UIListBox` |
| MagicUI | 216980 | ml_TuList | `UIListBox` |
| MagicUI | 218268 | ml_SuangList | `UIListBox` |
| MagicUI | 219556 | m_TopFrame | `UIStatic` |
| MagicUI | 219708 | m_TopFrameXS | `UIStatic` |
| MagicUI | 219860 | m_parRainbow | `UIParticle[8][5]` |
| MagicUI | 243540 | m_parRise | `UIParticle[8][5]` |
| MagicUI | 267220 | m_parRc | `tagRECT[5]` |
| MainEquipUI | 72 | m_rcLayout | `tagRECT` |
| MainEquipUI | 88 | m_nBkWndX | `int` |
| MainEquipUI | 92 | m_nBkWndY | `int` |
| MainEquipUI | 96 | m_nListIdx | `int` |
| MainEquipUI | 100 | m_nListIdx2 | `int` |
| MainEquipUI | 104 | m_szListBuf | `char[256]` |
| MainEquipUI | 360 | m_IsMsg | `unsigned char` |
| MainEquipUI | 361 | m_Is | `_BYTE[5]` |
| MainEquipUI | 366 | m_IsActive | `unsigned char` |
| MainEquipUI | 367 | m_IsCreateable | `unsigned char` |
| MainEquipUI | 368 | m_SelNum | `int` |
| MainEquipUI | 372 | m_PutOnType | `int` |
| MainEquipUI | 376 | m_CurType | `PlayerItem_Type` |
| MainEquipUI | 380 | pStateUI | `StateUI *` |
| MainEquipUI | 384 | m_Frame | `UIStatic` |
| MainEquipUI | 544 | m_TimeMoney | `UIStatic` |
| MainEquipUI | 704 | m_TopFrame | `UIStatic` |
| MainEquipUI | 864 | m_TopFrameZB | `UIStatic` |
| MainEquipUI | 1024 | m_ScrollHB | `UIStatic` |
| MainEquipUI | 1184 | m_OutFrameT | `UIStatic` |
| MainEquipUI | 1344 | m_OutFrameR | `UIStatic` |
| MainEquipUI | 1504 | m_OutFrameL | `UIStatic` |
| MainEquipUI | 1664 | m_OutFrameB | `UIStatic` |
| MainEquipUI | 1824 | stp_BarL | `UIStatic` |
| MainEquipUI | 1984 | stp_BarM | `UIFlexBar` |
| MainEquipUI | 2068 | stp_BarR | `UIStatic` |
| MainEquipUI | 2228 | stp_State | `UIButton` |
| MainEquipUI | 2572 | stp_Magic | `UIButton` |
| MainEquipUI | 2916 | stp_Equip | `UIButton` |
| MainEquipUI | 3260 | stp_Prop | `UIButton` |
| MainEquipUI | 3604 | stp_BattleArray | `UIButton` |
| MainEquipUI | 3948 | stp_TaskBook | `UIButton` |
| MainEquipUI | 4292 | stp_System | `UIButton` |
| MainEquipUI | 4636 | stp_Exit | `UIButton` |
| MainEquipUI | 4980 | stp_Effect | `UIStatic` |
| MainEquipUI | 5140 | stp_Rect | `tagRECT` |
| MainEquipUI | 5156 | m_GameTime | `UIStatic` |
| MainEquipUI | 5316 | m_GameMoney | `UIStatic` |
| MainEquipUI | 5476 | m_DlgEx | `MUIDialog` |
| MainEquipUI | 6860 | m_btnPar | `UIParticle[16][7]` |
| MainEquipUI | 73164 | m_btnPar2 | `UIParticle[16][7]` |
| MainEquipUI | 139468 | m_btnParRc | `tagRECT[7]` |
| MainEquipUI | 139580 | _isParBtn | `_BYTE[7]` |
| MainEquipUI | 139588 | _curParEffect | `int` |
| MainEquipUI | 139592 | me_Role | `me_RoleState[5]` |
| MainEquipUI | 188092 | m_WeaponName | `UIStatic` |
| MainEquipUI | 188252 | m_ClothName | `UIStatic` |
| MainEquipUI | 188412 | m_ShoesName | `UIStatic` |
| MainEquipUI | 188572 | m_HatName | `UIStatic` |
| MainEquipUI | 188732 | m_Adorn1Name | `UIStatic` |
| MainEquipUI | 188892 | m_Adorn2Name | `UIStatic` |
| MainEquipUI | 189052 | m_RemarkBk | `UIStatic` |
| MainEquipUI | 189212 | m_Remark | `UIStatic` |
| MainEquipUI | 189372 | m_RemarkVal | `UIStatic` |
| MainEquipUI | 189532 | m_typeWord | `UIStatic` |
| MainEquipUI | 189692 | m_remarkRc | `tagRECT` |
| MainEquipUI | 189708 | m_role | `RoleAtt[5]` |
| MainEquipUI | 193968 | m_Dlg | `MUIDialog` |
| MainEquipUI | 195352 | m_Ctrlbtn | `UIButton[5]` |
| MainEquipUI | 197072 | m_ClothIcon | `UIStatic` |
| MainEquipUI | 197232 | m_HatIcon | `UIStatic` |
| MainEquipUI | 197392 | m_ShoesIcon | `UIStatic` |
| MainEquipUI | 197552 | m_WeaponIcon | `UIStatic` |
| MainEquipUI | 197712 | m_AdornIcon1 | `UIStatic` |
| MainEquipUI | 197872 | m_AdornIcon2 | `UIStatic` |
| MainEquipUI | 198032 | m_SelRc | `tagRECT` |
| MainEquipUI | 198048 | m_SelRole | `UIButton[5]` |
| MainEquipUI | 199768 | m_CurSelRole | `int` |
| MainEquipUI | 199772 | m_ListTitle | `UIFlexBar` |
| MainEquipUI | 199856 | m_ListFrame | `UIStatic` |
| MainEquipUI | 200016 | m_ListGrid | `UIStatic[14]` |
| MainEquipUI | 202256 | m_title | `UIStatic` |
| MainEquipUI | 202416 | ml_Equiplist | `UIListBox` |
| MainEquipUI | 203704 | last_index | `int` |
| MainEquipUI | 203708 | m_SortRc | `tagRECT` |
| MainEquipUI | 203724 | mb_SortDefault | `UIButton` |
| MainPropUI | 72 | rc | `tagRECT` |
| MainPropUI | 88 | m_nBkWndX | `int` |
| MainPropUI | 92 | m_nBkWndY | `int` |
| MainPropUI | 96 | m_nListIdx | `int` |
| MainPropUI | 100 | j | `int` |
| MainPropUI | 104 | m_szListBuf | `_DWORD` |
| MainPropUI | 108 | buf | `char[256]` |
| MainPropUI | 364 | m_tabRemarkBuf | `char[256]` |
| MainPropUI | 620 | m_IsMsg | `unsigned char` |
| MainPropUI | 621 | m_Is | `_BYTE[5]` |
| MainPropUI | 628 | m_CurSelRole | `int` |
| MainPropUI | 632 | m_CurNeedRole | `int` |
| MainPropUI | 636 | m_IsActive | `unsigned char` |
| MainPropUI | 637 | m_IsCreateable | `unsigned char` |
| MainPropUI | 640 | curPage | `int` |
| MainPropUI | 644 | curList | `int` |
| MainPropUI | 648 | m_SelNum | `int` |
| MainPropUI | 652 | m_UseNum | `int` |
| MainPropUI | 656 | m_LockUse | `unsigned char` |
| MainPropUI | 657 | m_IsUsed | `unsigned char` |
| MainPropUI | 658 | m_IsCanUse | `unsigned char` |
| MainPropUI | 659 | m_IsAllUse | `unsigned char` |
| MainPropUI | 660 | pStateUI | `StateUI *` |
| MainPropUI | 664 | m_Frame | `UIStatic` |
| MainPropUI | 824 | m_TimeMoney | `UIStatic` |
| MainPropUI | 984 | m_TopFrame | `UIStatic` |
| MainPropUI | 1144 | m_TopFrameWP | `UIStatic` |
| MainPropUI | 1304 | m_OutFrameT | `UIStatic` |
| MainPropUI | 1464 | m_OutFrameR | `UIStatic` |
| MainPropUI | 1624 | m_OutFrameL | `UIStatic` |
| MainPropUI | 1784 | m_OutFrameB | `UIStatic` |
| MainPropUI | 1944 | stp_BarL | `UIStatic` |
| MainPropUI | 2104 | stp_BarM | `UIFlexBar` |
| MainPropUI | 2188 | stp_BarR | `UIStatic` |
| MainPropUI | 2348 | stp_State | `UIButton` |
| MainPropUI | 2692 | stp_Magic | `UIButton` |
| MainPropUI | 3036 | stp_Equip | `UIButton` |
| MainPropUI | 3380 | stp_Prop | `UIButton` |
| MainPropUI | 3724 | stp_BattleArray | `UIButton` |
| MainPropUI | 4068 | stp_TaskBook | `UIButton` |
| MainPropUI | 4412 | stp_System | `UIButton` |
| MainPropUI | 4756 | stp_Exit | `UIButton` |
| MainPropUI | 5100 | stp_Effect | `UIStatic` |
| MainPropUI | 5260 | stp_Rect | `tagRECT` |
| MainPropUI | 5276 | m_GameTime | `UIStatic` |
| MainPropUI | 5436 | m_GameMoney | `UIStatic` |
| MainPropUI | 5596 | m_DlgEx | `MUIDialog` |
| MainPropUI | 6980 | m_btnPar | `UIParticle[16][7]` |
| MainPropUI | 73284 | m_btnPar2 | `UIParticle[16][7]` |
| MainPropUI | 139588 | m_btnParRc | `tagRECT[7]` |
| MainPropUI | 139700 | _isParBtn | `_BYTE[7]` |
| MainPropUI | 139708 | _curParEffect | `int` |
| MainPropUI | 139712 | m_Dlg | `MUIDialog` |
| MainPropUI | 141096 | m_Role | `p_RoleState[5]` |
| MainPropUI | 162556 | m_RemarkBk | `UIStatic` |
| MainPropUI | 162716 | m_Remark | `UIStatic` |
| MainPropUI | 162876 | m_RemarkVal | `UIStatic` |
| MainPropUI | 163036 | m_RemarkRc | `tagRECT` |
| MainPropUI | 163052 | m_typeWord | `UIStatic` |
| MainPropUI | 163212 | m_PageBk | `UIStatic` |
| MainPropUI | 163372 | m_Ctrlbtn | `UIButton[5]` |
| MainPropUI | 165092 | m_Pushbtn | `UIPushButton[5]` |
| MainPropUI | 166352 | m_Title | `UIStatic` |
| MainPropUI | 166512 | m_ListFrame | `UIStatic` |
| MainPropUI | 166672 | m_ListGrid | `UIStatic[14]` |
| MainPropUI | 168912 | m_ScrollHB | `UIStatic` |
| MainPropUI | 169072 | ml_Resume | `UIListBox` |
| MainPropUI | 170360 | ml_Attack | `UIListBox` |
| MainPropUI | 171648 | ml_Treasure | `UIListBox` |
| MainPropUI | 172936 | ml_Smelt | `UIListBox` |
| MainPropUI | 174224 | ml_Special | `UIListBox` |
| MainPropUI | 175512 | m_Animate | `UIAnimate[5]` |
| MainPropUI | 175772 | m_AnimateRc | `tagRECT[5]` |
| MainPropUI | 175852 | m_SortRc | `tagRECT` |
| MainPropUI | 175868 | mb_SortDefault | `UIButton` |
| MainPropUI | 176212 | mb_SortPrice | `UIButton` |
| MainPropUI | 176556 | mb_SortUse | `UIButton` |
| MainPropUI | 176900 | m_SortState | `int` |
| MainPropUI | 176904 | m_3DObj | `UI3DCtrl` |
| MainPropUI | 177212 | m_parSingle | `UIParticle[12][5]` |
| Matrix4 | 0 | m | `float[4][4]` |
| MeshFx | 88 | m_iCurrentState | `int` |
| MonsterStar | 0 | needexp | `int` |
| MonsterStar | 4 | active | `int` |
| MonsterStar | 8 | exp | `int` |
| MonsterStar | 12 | item | `unsigned int` |
| MyMdl | 0 | m_mdltype | `int` |
| MyMdl | 4 | m_fx | `MeshFx *` |
| MyMdl | 8 | box | `gbOBBox` |
| NGHHURT | 0 | AlphaSpeed | `float` |
| NGHHURT | 4 | bFlashState | `BYTE` |
| NGHHURT | 5 | bNeedFlash | `BYTE` |
| NGHHURT | 8 | fTimeCounter | `float` |
| NGHHURT | 12 | nWaitSecond | `int` |
| NGHHURT | 16 | nHurtState | `int` |
| NMHDR | 0 | hwndFrom | `HWND__ *` |
| NMHDR | 4 | idFrom | `unsigned int` |
| NMHDR | 8 | code | `unsigned int` |
| NPC | 4 | m_pBuffer | `char *` |
| NPC | 8 | m_nBufStart | `int` |
| NPC | 12 | m_nBufEnd | `int` |
| NPC | 36 | m_nTodo_024 | `int` |
| NPC | 48 | m_nTodo_30 | `int` |
| NPC | 56 | m_pConditionA | `int` |
| NPC | 60 | m_pConditionB | `void *` |
| NPC | 68 | m_wndBase | `UIWnd` |
| NPC | 224 | m_nTodo_0E0 | `int` |
| NPC | 292 | m_wndHPBar | `UIWnd *` |
| NPC | 312 | m_WndContainer | `UIWnd` |
| NPC | 536 | m_wndNameLabel | `int` |
| NPC | 556 | m_AnimWndA | `UIWnd` |
| NPC | 688 | m_wndDialog | `NPC *` |
| NPC | 708 | m_AnimWndB | `UIWnd` |
| NPC | 840 | m_wndTooltip | `NPC *` |
| NPC | 860 | m_AnimWndC | `UIWnd` |
| NPC | 1144 | m_fAnimTimer | `float` |
| NPC | 1148 | m_bAnimActive | `int` |
| NPCInfo | 0 | id | `BYTE` |
| NPCInfo | 1 | kind | `BYTE` |
| NPCInfo | 2 | name | `char[32]` |
| NPCInfo | 34 | mtl | `char[32]` |
| NPCInfo | 68 | face | `float` |
| NPCInfo | 72 | onlayer | `BYTE` |
| NPCInfo | 76 | x | `float` |
| NPCInfo | 80 | z | `float` |
| NPCInfo | 84 | initactive | `BYTE` |
| NPCInfo | 88 | initbeh | `ROLE_BEHAVIOUR` |
| NPCInfo | 92 | scriptid | `unsigned int` |
| NPCInfo | 96 | y | `float` |
| NPCInfo | 100 | initact | `char[16]` |
| NPCInfo | 116 | mid | `unsigned int[3]` |
| NPCInfo | 128 | mnum | `BYTE` |
| NPCInfo | 129 | mrepeat | `BYTE` |
| NPCInfo | 132 | path | `PolyLine` |
| NPCInfo | 328 | noturn | `unsigned int` |
| NPCInfo | 332 | loopact | `unsigned int` |
| NPCInfo | 336 | speed | `unsigned int` |
| NPCInfo | 340 | reserve | `unsigned int[29]` |
| NameSys | 0 | m_Flag | `char[8]` |
| NameSys | 8 | m_FlagZZCC | `char[4]` |
| NameSys | 12 | m_Ref | `int[28]` |
| NameSys | 124 | m_RefMax | `int[28]` |
| NameSys | 236 | m_CheckMax | `unsigned int[10]` |
| NameSys | 276 | m_LastName | `NameSys_NAMEFLAG` |
| NavFace | 0 | index | `unsigned __int16[3]` |
| NavFaceLayer | 0 | numvert | `unsigned __int16` |
| NavFaceLayer | 2 | numface | `unsigned __int16` |
| NavFaceLayer | 4 | vertbuf | `gbVec3D *` |
| NavFaceLayer | 8 | face | `NavFace *` |
| NavFaceLayer | 12 | node | `LayerNode *` |
| NavHeader | 0 | magic | `_BYTE[4]` |
| NavHeader | 4 | version | `BYTE` |
| NavHeader | 5 | numlayer | `BYTE` |
| NavHeader | 6 | offsettile | `char[2]` |
| NavHeader | 10 | offsetface | `char[2]` |
| NavTile | 0 | y | `float` |
| NavTile | 4 | dist | `BYTE` |
| NavTile | 5 | floor | `BYTE` |
| NavTileLayer | 0 | portal | `tagRECT[8]` |
| NavTileLayer | 128 | min | `gbVec3D` |
| NavTileLayer | 140 | max | `gbVec3D` |
| NavTileLayer | 152 | width | `int` |
| NavTileLayer | 156 | height | `int` |
| NavTileLayer | 160 | tile | `NavTile *` |
| NavTriangle | 0 | up | `gbVec3D` |
| NavTriangle | 12 | forward | `gbVec3D` |
| NavTriangle | 24 | side | `gbVec3D` |
| NavigationInfo | 0 | m_numlayer | `int` |
| NavigationInfo | 4 | m_tilelayer | `NavTileLayer[2]` |
| NavigationInfo | 332 | m_facelayer | `NavFaceLayer[2]` |
| Note_Item | 0 | m_ItemRc | `tagRECT` |
| Note_Item | 16 | m_NoteItemBk | `UIButton` |
| Note_Item | 360 | m_NoteID | `UIStatic` |
| Note_Item | 512 | m_NoteState | `UIStatic` |
| Note_Item | 664 | m_HeadShot_NO_SEL | `UIStatic[5]` |
| Note_Item | 1424 | m_HeadShot | `UIStatic[5]` |
| Note_Item | 2184 | m_isHead | `_BYTE[5]` |
| Note_Item | 2192 | m_NoteTime | `UIStatic` |
| Note_Item | 2344 | m_NoteMoney | `UIStatic` |
| Note_Item | 2496 | m_NoteLv | `UIStatic[5]` |
| Note_Item | 3256 | m_NotePic | `UIStatic` |
| Note_Item | 3408 | m_NotePicName | `UIStatic` |
| OBJHELPER | 0 | bValid | `BYTE` |
| OBJHELPER | 4 | nType | `int` |
| OBJHELPER | 8 | rTouchArea | `tagRECT` |
| OBJHELPER | 24 | pGroundPt | `tagPOINT` |
| OBJHELPER | 32 | nEffRunID | `int` |
| OBJHELPER | 36 | vEffPos | `gbVec3D` |
| ORect | 0 | m_pt | `tagPOINT[4]` |
| ORect | 32 | m_numpt | `int` |
| ObjLockInput | 0 | m_objs | `PtrArray` |
| ObjLockInput | 16 | m_scripts | `PtrArray` |
| ObjLockInput | 32 | m_scriptabs | `PtrArray` |
| ObjParam | 0 | ID | `unsigned int` |
| ObjParam | 4 | Type | `int` |
| ObjParam | 8 | name | `char[32]` |
| ObjParam | 40 | Price | `int` |
| ObjParam | 44 | Touch | `int` |
| ObjParam | 48 | Radius | `float` |
| ObjParam | 52 | Value | `int` |
| ObjParam | 56 | Speed | `float` |
| ObjParam | 60 | Accelerate | `float` |
| ObjParam | 64 | Shelf | `char[64]` |
| ObjParam | 128 | Model | `char[64]` |
| ObjParam | 192 | EffID | `unsigned int` |
| ObjParam | 196 | Remark | `char[256]` |
| Object | 4 | position | `gbVec3D` |
| Object | 16 | radius | `float` |
| Object | 20 | forward | `gbVec3D` |
| Object | 32 | side | `gbVec3D` |
| Object | 44 | up | `gbVec3D` |
| Object3D | 0 | m_isLoadObj | `unsigned char` |
| Object3D | 4 | m_type | `unsigned int` |
| Object3D | 8 | m_pol | `gbGeomNode *` |
| Object3D | 12 | m_subObj | `gbGeomNode *` |
| Object3D | 16 | m_subType | `unsigned int` |
| Object3D | 20 | m_isLoadSubObj | `unsigned char` |
| Object3D | 21 | m_showSubObj | `unsigned char` |
| Object3D | 24 | m_subObjHeight | `float` |
| Object3D | 28 | m_height | `float` |
| Object3D | 32 | m_position | `gbVec3D` |
| Object3D | 44 | RelativePos | `gbVec3D` |
| Object3D | 56 | m_roty | `float` |
| Object3D | 60 | m_rotx | `float` |
| Object3D | 64 | m_rotz | `float` |
| Object3D | 68 | m_dropx | `float` |
| Object3D | 72 | m_dropy | `float` |
| Object3D | 76 | m_dropz | `float` |
| Object3D | 80 | m_visible | `unsigned char` |
| Object3D | 84 | m_pCamera | `ObjectCamera *` |
| Object3D | 88 | m_yaw | `float` |
| Object3D | 92 | m_pitch | `float` |
| Object3D | 96 | m_roll | `float` |
| Object3D | 100 | m_dist | `float` |
| Object3D | 104 | m_forward | `gbVec3D` |
| Object3D | 116 | m_degreeToScreen | `float` |
| Object3D | 120 | m_isActionRelativeRot | `unsigned char` |
| Object3D | 121 | m_bRotDstDegree | `unsigned char` |
| Object3D | 124 | m_rotRelative | `float` |
| Object3D | 128 | m_rotDegree | `float` |
| Object3D | 132 | m_rotDstDegree | `float` |
| Object3D | 136 | m_rotDstSpeed | `float` |
| Object3D | 140 | m_rotDstDir | `int` |
| Object3D | 144 | m_rotDstMode | `int` |
| Object3D | 148 | m_action | `int` |
| ObjectCamera | 0 | m_pCamera | `gbCamera *` |
| ObjectCamera | 4 | m_camFrom | `gbVec3D` |
| ObjectCamera | 16 | m_camTo | `gbVec3D` |
| ObjectCamera | 28 | m_camUp | `gbVec3D` |
| ObjectCamera | 40 | m_camDirect | `gbVec3D` |
| ObjectCamera | 52 | m_yaw | `float` |
| ObjectCamera | 56 | m_pitch | `float` |
| ObjectCamera | 60 | m_roll | `float` |
| ObjectCamera | 64 | m_dist | `float` |
| ObjectCamera | 68 | m_nyaw | `float` |
| ObjectCamera | 72 | m_npitch | `float` |
| ObjectCamera | 76 | m_nroll | `float` |
| ObjectCamera | 80 | m_forward | `gbVec3D` |
| ObjectCamera | 92 | m_side | `gbVec3D` |
| ObjectCamera | 104 | m_stepRotSpeed | `float` |
| ObjectCamera | 108 | m_stepRot | `int` |
| ObjectCamera | 112 | m_stepRotMode | `int` |
| ObjectCamera | 116 | m_stepRotAxis | `signed __int16` |
| ObjectCamera | 120 | m_bStepRot | `BYTE` |
| ObjectInfo | 4 | name | `char[32]` |
| ObjectInfo | 36 | ctype | `BYTE` |
| ObjectInfo | 37 | cango | `BYTE` |
| ObjectInfo | 40 | pos | `gbVec3D` |
| ObjectInfo | 52 | rotate | `float` |
| ObjectInfo | 56 | rect | `tagRECT` |
| ObjectInfo | 72 | type | `BYTE` |
| ObjectInfo | 73 | savestate | `BYTE` |
| ObjectInfo | 74 | onlayer | `BYTE` |
| ObjectInfo | 75 | wuling | `BYTE` |
| ObjectInfo | 76 | param | `float[6]` |
| ObjectInfo | 100 | needspecalact | `BYTE` |
| ObjectInfo | 102 | needitem | `unsigned __int16` |
| ObjectInfo | 104 | needgold | `unsigned __int16` |
| ObjectInfo | 106 | needlv | `unsigned __int16` |
| ObjectInfo | 108 | needwu | `unsigned __int16` |
| ObjectInfo | 110 | needallopen | `BYTE` |
| ObjectInfo | 111 | failed | `char[16]` |
| ObjectInfo | 128 | dwNeedItem | `unsigned int` |
| ObjectInfo | 132 | groupid | `BYTE` |
| ObjectInfo | 136 | scriptid | `unsigned int` |
| ObjectInfo | 140 | path | `PolyLine` |
| ObjectInfo | 336 | linkobj | `unsigned __int16` |
| ObjectInfo | 338 | depend_scenename | `char[32]` |
| ObjectInfo | 370 | depend_id | `BYTE` |
| ObjectInfo | 372 | box | `gbAABBox` |
| ObjectInfo | 396 | rotateX | `float` |
| ObjectInfo | 400 | rotateZ | `float` |
| ObjectInfo | 404 | snd | `_BYTE[8]` |
| ObjectInfo | 412 | effect | `unsigned int` |
| ObjectInfo | 416 | bScriptChangeActive | `unsigned int` |
| ObjectInfo | 420 | bScriptMoved | `unsigned int` |
| ObjectInfo | 424 | bCalculateExp | `BYTE` |
| ObjectInfo | 428 | reserve | `unsigned int[44]` |
| ObjectInfoBase | 0 | id | `BYTE` |
| ObjectInfoBase | 1 | active | `BYTE` |
| ObjectInfoBase | 2 | times | `BYTE` |
| ObjectInfoBase | 3 | siwtch | `BYTE` |
| OpenBaseFile | 0 | m_plastsys | `gbVFileSystem *` |
| OpenFNWindow | 0 | fWaitTime | `float` |
| OpenFNWindow | 4 | bOpen | `BYTE` |
| OpenFNWindow | 8 | nOpenFlag | `int` |
| OpenNULLFile | 0 | m_plastsys | `gbVFileSystem *` |
| OutFile | 0 | str | `char[128]` |
| OutFile | 128 | RolePos | `unsigned int` |
| OutFile | 132 | RoleNum | `int` |
| OutFile | 136 | SkillPos | `unsigned int` |
| OutFile | 140 | SkillNum | `int` |
| OutFile | 144 | ItemPos | `unsigned int` |
| OutFile | 148 | ItemNum | `int` |
| OutFile | 152 | ComboPos | `unsigned int` |
| OutFile | 156 | ComboNum | `int` |
| PAL3 | 0 | m_snaph | `float` |
| PAL3 | 4 | m_pScnFrameTex | `gbTexture *` |
| PAL3 | 8 | m_pAdditiveEffect | `gbRenderEffect *` |
| PAL3 | 12 | m_pAdditiveEffect2 | `gbRenderEffect *` |
| PAL3 | 32 | m_Image2D | `gbImage2D` |
| PAL3 | 320 | m_nTodo_140 | `unsigned int[4]` |
| PAL3 | 336 | m_nTodo_150 | `unsigned int[4]` |
| PAL3 | 412 | s_gamestate | `int` |
| PAL3 | 416 | m_pCmdLine | `char *` |
| PAL3 | 420 | m_bTestCombat | `int` |
| PAL3 | 424 | m_bCombatWin | `int` |
| PAL3 | 428 | m_bLoadMainUI | `int` |
| PAL3 | 432 | m_bShowRenderInfo | `int` |
| PAL3 | 436 | m_bSoftCursor | `int` |
| PAL3 | 440 | m_bNGHVariance | `int` |
| PAL3 | 444 | m_bWPXVariance | `int` |
| PAL3 | 448 | m_gametime | `double` |
| PAL3 | 1696 | m_nTodo_6A0 | `int` |
| PAL3 | 1704 | m_nTodo_6A8 | `int` |
| PAL3 | 1708 | m_nTodo_6AC | `int` |
| PAL3 | 1712 | m_nTodo_6B0 | `int` |
| PAL3 | 1736 | m_nTodo_6C8 | `int` |
| PAL3 | 1744 | m_nTodo_6D0 | `int` |
| PAL3 | 1748 | m_nTodo_6D4 | `int` |
| PAL3 | 1752 | m_nTodo_6D8 | `int` |
| PAL3 | 2148 | m_nTodo_864 | `int` |
| PAL3 | 2152 | m_nTodo_868 | `int` |
| PAL3 | 2156 | m_nTodo_86C | `int` |
| PAL3 | 2188 | m_nTodo_88C | `gbTexture *` |
| PAL3 | 2192 | m_nTodo_890 | `int` |
| PAL3 | 2196 | m_nTodo_894 | `int` |
| PAL3 | 3232 | m_nTodo_CA0 | `int` |
| PAL3 | 3236 | m_nTodo_CA4 | `int` |
| PAL3 | 3240 | m_nTodo_CA8 | `int` |
| PAL3 | 3272 | m_pDeviceTex | `gbTexture *` |
| PAL3 | 3276 | m_nTodo_CCC | `int` |
| PAL3 | 3280 | m_nTodo_CD0 | `int` |
| PAL3 | 3948 | m_nTodo_F6C | `int` |
| PAL3 | 3952 | m_nTodo_F70 | `int` |
| PAL3 | 3956 | m_nTodo_F74 | `int` |
| PAL3 | 3988 | m_nTodo_F94 | `gbTexture *` |
| PAL3 | 3992 | m_nTodo_F98 | `int` |
| PAL3 | 3996 | m_nTodo_F9C | `int` |
| PAL_GDB | 0 | m_head | `OutFile` |
| PAL_GDB | 160 | m_RoleData | `RoleAtt[200]` |
| PAL_GDB | 170560 | m_SkillData | `FightSkill[300]` |
| PAL_GDB | 398560 | m_ItemData | `FightItem[512]` |
| PAL_GDB | 808160 | m_ComboData | `ComboAttack[10]` |
| PAL_GDB | 814520 | i | `int` |
| PARTICLEVERTEX | 0 | FVF | `unsigned int` |
| PARTICLEVERTEX | 12 | color | `unsigned int` |
| PARTICLEVERTEX | 16 | tu | `float` |
| PARTICLEVERTEX | 20 | tv | `float` |
| PMD | 0 | mdisp | `int` |
| PMD | 4 | pdisp | `int` |
| PMD | 8 | vdisp | `int` |
| PMFN | 0 | pfn | `int` |
| PalScript | 68 | m_fTimerLimit | `float` |
| PalScript | 72 | m_fTimerAccum | `float` |
| PalScript | 76 | m_nTodo_04C | `_BYTE[68]` |
| PalScript | 144 | m_pCurrentTask | `_inline_PalScript_m_pCurrentTask` |
| PalScript | 148 | m_pTaskPtr | `void *` |
| PalScript | 152 | m_nTimerCount | `int` |
| PalScript | 156 | m_nWaitTimer | `int` |
| PalScript | 160 | m_nAnimState | `int` |
| PalScript | 164 | m_nSnowParticles | `int` |
| PalScript | 168 | m_nItemCheck | `int` |
| PalScript | 176 | m_RoleEmoteData | `int` |
| PalScript | 196 | m_pTexture | `gbTexture *` |
| PalScript | 200 | m_pTextureInfo | `_PlugInfo *` |
| PalScript | 212 | m_RoleEmoteSub | `int` |
| PalScript | 216 | m_nTodo_0D8 | `int` |
| PalScript | 220 | m_nRoleCount | `int` |
| PalScript | 236 | m_nScriptState | `int` |
| PalScript | 240 | m_bCamActive | `unsigned char` |
| PalScript | 244 | m_bSoundType | `unsigned char` |
| PalScript | 248 | m_fCamScale | `float` |
| PalScript | 252 | m_fScaleX | `float` |
| PalScript | 256 | m_nUpdateState | `int` |
| PalScript | 260 | m_WaitObjList | `PtrArray` |
| PalScript | 276 | m_fRenderScaleX | `float` |
| PalScript | 280 | m_fScaleY | `float` |
| PalScript | 284 | m_fScaleZ | `float` |
| PalScript | 292 | m_fInterval | `float` |
| PalScript | 296 | m_fElapsed | `float` |
| PalScript | 312 | m_nTodo_138 | `int` |
| PalScript | 332 | m_nScriptCount | `int` |
| PalScript | 352 | m_EncampConfig | `int` |
| PalScript | 368 | m_nRepeatCount | `int` |
| PalScript | 372 | m_nMaxRepeats | `int` |
| PalScript | 376 | m_nCycleCount | `int` |
| PalScript | 380 | m_nMaxCycles | `int` |
| PalScript | 396 | m_RoleSlotArray | `_inline_PalScript_m_RoleSlotArray` |
| PalScript | 1296 | m_nTodo_510 | `int` |
| PalScript | 1300 | m_szDialog1 | `_inline_PalScript_m_szDialog1` |
| PalScript | 1556 | m_szDialog2 | `char[256]` |
| PalScript | 1812 | m_DialogSub | `unsigned char` |
| PalScript | 1832 | _todo_730 | `float` |
| PalScript | 1844 | m_fSceneTileSize | `float` |
| PalScript | 1892 | _todo_764 | `int` |
| PalScript | 1896 | _todo_768 | `int` |
| PalScriptAnimTimer | 8 | m_fTime | `float` |
| PalScriptAnimTimer | 12 | m_bDone | `char` |
| PalScriptBlendTimer | 8 | m_fElapsed | `float` |
| PalScriptBlendTimer | 12 | m_fDuration | `float` |
| PalScriptDialogOverlay | 140 | overlay | `_inline_PalScriptDialogOverlay_overlay` |
| PalScriptFadeInTimer | 8 | m_fElapsed | `float` |
| PalScriptFadeInTimer | 16 | m_bDone | `char` |
| PalScriptFadeOutTimer | 8 | m_fElapsed | `float` |
| PalScriptFadeOutTimer | 16 | m_bDone | `char` |
| PalScriptIdleObj | 8 | m_nTodo_008 | `int` |
| PalScriptIdleObj | 12 | m_passedtime | `float` |
| PalScriptMgr | 4 | m_bGetSceneScript | `unsigned char` |
| PalScriptMgr | 8 | m_scriptMain | `PtrArray` |
| PalScriptMgr | 24 | m_scefile | `scSCEFile *` |
| PalScriptMgr | 28 | m_fPopA | `float` |
| PalScriptMgr | 32 | m_fPopB | `float` |
| PalScriptMgr | 36 | m_pPopScript | `void *` |
| PalScriptMgr | 40 | m_nTodo_024 | `int` |
| PalScriptMgr | 44 | m_fCamX | `float` |
| PalScriptMgr | 48 | m_fCamY | `float` |
| PalScriptMgr | 52 | m_fCamZ | `float` |
| PalScriptMgr | 56 | m_pPauseBackup | `void *` |
| PalScriptMgr | 60 | m_nFrameCounter | `int` |
| PalScriptMgr | 64 | m_fPauseCamY | `float` |
| PalScriptMgr | 68 | m_pBigMapSce | `scSCEFile *` |
| PalScriptMgr | 72 | m_wndTextBox | `float` |
| PalScriptMgr | 76 | m_fPosZ | `float` |
| PalScriptMgr | 80 | m_scepath | `scSCEFile *` |
| PalScriptMgr | 84 | m_bBigMapState | `unsigned char` |
| PalScriptMgr | 88 | m_scriptAux | `int` |
| PalScriptMgr | 92 | m_pScriptObjMain | `gbVisNode *` |
| PalScriptMgr | 96 | m_pExecSystem | `char *` |
| PalScriptMgr | 100 | m_nTodo_060 | `int` |
| PalScriptMgr | 104 | m_nTodo_064 | `int` |
| PalScriptMgr | 108 | m_nTodo_068 | `signed __int16` |
| PalScriptMgr | 112 | m_nTodo_06C | `signed __int16` |
| PalScriptMgr | 116 | m_nTodo_070 | `int` |
| PalScriptMgr | 120 | m_nTodo_074 | `float` |
| PalScriptMgr | 124 | m_nTodo_078 | `int` |
| PalScriptMgr | 128 | m_nTodo_07C | `float` |
| PalScriptMgr | 132 | m_nExecParam | `int` |
| PalScriptMgr | 136 | m_vRolePos | `int` |
| PalScriptMgr | 140 | m_fDefaultFOV | `float` |
| PalScriptMgr | 152 | m_nScriptIdx | `int` |
| PalScriptMgr | 156 | m_pCurScriptBlock | `void *` |
| PalScriptMgr | 160 | m_nBlockEndAddr | `int` |
| PalScriptMgr | 164 | m_pExecState | `void *` |
| PalScriptMgr | 168 | m_pVarContext | `int` |
| PalScriptMgr | 172 | m_szScriptFile | `char[6]` |
| PalScriptMgr | 178 | m_bExecuteBlock | `unsigned char` |
| PalScriptMgr | 179 | m_bScriptPause | `unsigned char` |
| PalScriptMgr | 180 | m_RoleAnimData | `int` |
| PalScriptMgr | 188 | m_bRunning | `int` |
| PalScriptMgr | 192 | m_bBlockActive | `int` |
| PalScriptMgr | 196 | m_bBlockFlag | `int` |
| PalScriptMgr | 204 | m_nTodo_0C8 | `int` |
| PalScriptMgr | 208 | m_nSavedBlockNum | `int` |
| PalScriptMgr | 212 | m_pTodo_84 | `unsigned char` |
| PalScriptMgr | 213 | m_bOpcodeFlag | `unsigned char` |
| PalScriptMgr | 216 | m_nExecuteBlock | `int` |
| PalScriptMgr | 220 | m_nSavedDataA | `int` |
| PalScriptMgr | 224 | m_nSavedDataB | `int` |
| PalScriptMgr | 228 | m_fAngle | `float` |
| PalScriptMgr | 232 | m_nExecRangeA | `int` |
| PalScriptMgr | 236 | m_nExecRangeB | `int` |
| PalScriptMgr | 240 | m_nExecRangeC | `int` |
| PalScriptMgr | 244 | m_nExecRangeD | `int` |
| PalScriptMgr | 248 | m_nCmdType | `unsigned char` |
| PalScriptMgr | 249 | m_nTodo_0F5 | `unsigned char` |
| PalScriptMgr | 250 | m_bExecuteOpcode | `unsigned char` |
| PalScriptMgr | 251 | m_nTodo_0F7 | `unsigned char` |
| PalScriptMgr | 252 | m_nCmdValue | `int` |
| PalScriptMgr | 256 | m_nCmdParam0 | `signed __int16` |
| PalScriptMgr | 260 | m_nCmdParam1 | `signed __int16` |
| PalScriptMgr | 264 | m_nCmdParam2 | `int` |
| PalScriptMgr | 268 | m_nExecCounter | `int` |
| PalScriptMgr | 272 | m_pRoleSystemCache | `RoleSystem *` |
| PalScriptMgr | 276 | m_wRoleField114 | `unsigned __int16` |
| PalScriptMgr | 278 | m_wRoleField116 | `unsigned __int16` |
| PalScriptMgr | 280 | m_Actor | `signed __int16` |
| PalScriptMgr | 282 | m_bRoleField11A | `unsigned char` |
| PalScriptMgr | 284 | m_nField_0118 | `signed __int16` |
| PalScriptMgr | 286 | m_nTodo_11A | `unsigned char` |
| PalScriptMgr | 288 | m_nTodo_11C | `int` |
| PalScriptMgr | 296 | m_pTodo_128 | `char *` |
| PalScriptMgr | 300 | m_nScriptCount | `int` |
| PalScriptMgr | 304 | m_pScriptObjAux | `PalScriptMgr *` |
| PalScriptMgr | 308 | m_nScriptDepth | `int` |
| PalScriptMgr | 312 | m_fPrevPosX | `float` |
| PalScriptMgr | 316 | m_fPrevPosY | `float` |
| PalScriptMgr | 320 | m_nExecuteOpcode | `int` |
| PalScriptMgr | 324 | m_fExecuteBlock | `float` |
| PalScriptMgr | 328 | m_fCurPosY | `float` |
| PalScriptMgr | 332 | m_fAnimSpeed | `float` |
| PalScriptMgr | 364 | m_nField_0168 | `int` |
| PalScriptMgr | 368 | m_RolePos | `int` |
| PalScriptMgr | 380 | m_RoleDir | `int` |
| PalScriptMgr | 392 | m_nRoleState | `int` |
| PalScriptMgr | 396 | m_RoleSubData | `int` |
| PalScriptMgr | 404 | m_nRoleParam1 | `int` |
| PalScriptMgr | 408 | m_nRoleParam2 | `int` |
| PalScriptMgr | 412 | m_nRoleParam3 | `int` |
| PalScriptMgr | 416 | m_pRoleScript | `void *` |
| PalScriptMgr | 424 | m_nField_01A4 | `int` |
| PalScriptMgr | 452 | m_pOpResult | `void *` |
| PalScriptMgr | 472 | m_bTileType | `unsigned char` |
| PalScriptMgr | 496 | m_fSpeed1 | `float` |
| PalScriptMgr | 500 | m_fSpeed2 | `float` |
| PalScriptMgr | 504 | m_nScriptID | `signed __int16` |
| PalScriptMgr | 530 | m_nRoleIndex | `signed __int16` |
| PalScriptMgr | 532 | m_ScriptRoleState | `int` |
| PalScriptMgr | 538 | m_bScriptByte | `unsigned char` |
| PalScriptMgr | 540 | m_fPosAX | `float` |
| PalScriptMgr | 544 | m_fPosAY | `float` |
| PalScriptMgr | 548 | m_fPosAZ | `float` |
| PalScriptMgr | 552 | m_fPosBX | `float` |
| PalScriptMgr | 556 | m_fPosBY | `float` |
| PalScriptMgr | 560 | m_fPosBZ | `float` |
| PalScriptMgr | 564 | m_nMatrixData | `int` |
| PalScriptMgr | 568 | m_bRunCommand | `unsigned char` |
| PalScriptMgr | 572 | m_nRoleField23C | `int` |
| PalScriptMgr | 576 | m_bScriptInputBlock | `int` |
| PalScriptMgr | 580 | m_bInputBlock | `int` |
| PalScriptMgr | 584 | m_bRoleLock | `int` |
| PalScriptMgr | 632 | m_pCaseTable | `void *` |
| PalScriptMgr | 636 | m_nTodo_278 | `int` |
| PalScriptMgr | 792 | m_pTodo_318 | `char *` |
| PalScriptMgr | 796 | m_nBlockHandle | `int` |
| PalScriptMgr | 800 | m_pSceneMgr | `RoleSystem *` |
| PalScriptMgr | 804 | m_bRoleCmd | `unsigned char` |
| PalScriptMgr | 808 | m_nExecState | `int` |
| PalScriptMgr | 812 | m_pCmdBuffer | `char *` |
| PalScriptMgr | 816 | m_nLoopCountA | `int` |
| PalScriptMgr | 820 | m_nLoopCountB | `int` |
| PalScriptMgr | 824 | m_nLoopCountC | `int` |
| PalScriptMgr | 828 | m_nSavedPosX | `int` |
| PalScriptMgr | 832 | m_pSubScriptB | `PalScriptMgr *` |
| PalScriptMgr | 836 | m_nScriptCamX | `int` |
| PalScriptMgr | 840 | m_nScriptCamY | `int` |
| PalScriptMgr | 844 | m_pScriptBlock | `char *` |
| PalScriptMgr | 848 | m_pExecObj | `char *` |
| PalScriptMgr | 852 | m_fExecParam | `float` |
| PalScriptMgr | 856 | m_fExecPosY | `float` |
| PalScriptMgr | 860 | m_fExecPosZ | `float` |
| PalScriptMgr | 864 | m_nExecState2 | `int` |
| PalScriptMgr | 868 | m_pWaitObj | `char *` |
| PalScriptMgr | 876 | m_nWaitCount | `int` |
| PalScriptMgr | 880 | m_pTodo_370 | `char *` |
| PalScriptMgr | 884 | m_fDirNeg | `float` |
| PalScriptMgr | 888 | m_pClearResult | `char *` |
| PalScriptMgr | 892 | m_nExecHandle | `int` |
| PalScriptMgr | 956 | m_nState | `int` |
| PalScriptMgr | 1056 | m_bDirty | `int` |
| PalScriptMgr | 1148 | m_nFrameState | `int` |
| PalScriptMgr | 1272 | m_nOpType | `int` |
| PalScriptMgr | 1288 | m_nCmdData | `int` |
| PalScriptMgr | 1300 | m_fFramePosX | `int` |
| PalScriptMgr | 1304 | m_fFramePosY | `int` |
| PalScriptMgr | 1308 | m_fFramePosZ | `int` |
| PalScriptMgr | 1312 | m_fFrameScale | `int` |
| PalScriptMgr | 1316 | m_fFrameRot | `int` |
| PalScriptMgr | 1320 | m_nFrameParam | `int` |
| PalScriptMgr | 1484 | m_OpSubObj | `int` |
| PalScriptMgr | 1488 | m_OpParam | `int` |
| PalScriptMgr | 1492 | m_OpData | `int` |
| PalScriptMgr | 1504 | m_OpBuffer | `int` |
| PalScriptMgr | 1912 | m_nTodo_774 | `int` |
| PalScriptMgr | 1920 | m_ctrlParabola | `int` |
| PalScriptMgr | 2004 | m_nField_07D0 | `int` |
| PalScriptMgr | 2368 | m_nTodo_93C | `int` |
| PalScriptMgr | 2376 | m_wndTextDisplay | `UIWnd *` |
| PalScriptMgr | 2416 | m_nField_096C | `int` |
| PalScriptMgr | 2880 | m_nField_0B3C | `int` |
| PalScriptMgr | 2936 | m_nField_0B74 | `int` |
| PalScriptMgr | 3080 | m_nField_0C04 | `int` |
| PalScriptMgr | 3176 | m_nField_0C64 | `int` |
| PalScriptMgr | 3188 | m_nField_0C70 | `int` |
| PalScriptMgr | 3280 | m_bDeviceResetFlag | `int` |
| PalScriptMgr | 3284 | m_pTodo_CD4 | `char *` |
| PalScriptMgr | 3288 | m_nField_CD4 | `unsigned char` |
| PalScriptMgr | 3292 | m_nScreenEffect | `int` |
| PalScriptMgr | 3296 | m_nEffectTick | `int` |
| PalScriptMgr | 3300 | m_nTickStamp | `int` |
| PalScriptMgr | 3304 | m_bEffectInit | `unsigned char` |
| PalScriptMgr | 3308 | m_bEffectActive | `unsigned char` |
| PalScriptMgr | 3309 | m_nTodo_CE9 | `unsigned char` |
| PalScriptMgr | 3700 | m_nField_0E70 | `int` |
| PalScriptMgr | 4032 | m_RoleCmdCtx | `int` |
| PalScriptMgr | 4556 | m_nTileFlags | `int` |
| PalScriptMgr | 4560 | m_fTileHeight | `float` |
| PalScriptMgr | 5040 | m_nField_13AC | `int` |
| PalScriptMgr | 5228 | m_nField_1468 | `int` |
| PalScriptMgr | 5268 | m_nField_1490 | `int` |
| PalScriptMgr | 5480 | m_nField_1564 | `int` |
| PalScriptMgr | 5632 | m_nField_15FC | `int` |
| PalScriptMgr | 5676 | m_nField_1628 | `int` |
| PalScriptMgr | 6932 | m_nField_1B10 | `int` |
| PalScriptMgr | 7012 | m_nField_1B60 | `int` |
| PalScriptMgr | 7184 | m_nField_1C0C | `int` |
| PalScriptMgr | 7576 | m_nField_1D94 | `int` |
| PalScriptMgr | 8456 | m_nCost | `int` |
| PalScriptMgr | 8464 | m_nCapacity | `int` |
| PalScriptMgr | 8696 | m_fFrameTime | `float` |
| PalScriptMgr | 8700 | m_fFrameDelta | `float` |
| PalScriptMgr | 8704 | m_fFrameTotal | `float` |
| PalScriptMgr | 9484 | m_pTodo_250C | `char *` |
| PalScriptMgr | 9488 | m_pTodo_2510 | `char *` |
| PalScriptMgr | 9492 | m_pScriptInstA | `char *` |
| PalScriptMgr | 9496 | m_pScriptInstD | `PalScriptMgr *` |
| PalScriptMgr | 9500 | m_pScriptInstE | `char *` |
| PalScriptMgr | 9504 | m_nScriptResultA | `int` |
| PalScriptMgr | 9508 | m_nScriptResultB | `int` |
| PalScriptMgr | 9512 | m_nScriptResultC | `int` |
| PalScriptProgressTimer | 8 | m_fElapsed | `float` |
| PalScriptProgressTimer | 12 | m_bDone | `char` |
| PalScriptRoleSlotOverlay | 0 | overlay | `_inline_PalScriptRoleSlotOverlay_overlay` |
| PalScriptSlotStateOverlay | 456 | m_pCurrentScript | `PalScript *` |
| PalScriptSlotStateOverlay | 460 | m_bFormationReady | `_BYTE` |
| PalScriptSlotStateOverlay | 461 | m_nSceneTransitionParam | `_BYTE` |
| PalScriptSlotStateOverlay | 464 | _todo_35c | `int` |
| PalScriptSlotStateOverlay | 468 | _todo_360 | `int` |
| PalScriptSlotStateOverlay | 476 | m_fFadeTimer | `float` |
| PalScriptSlotStateOverlay | 480 | _todo_36c | `int` |
| PalScriptSlotStateOverlay | 580 | m_szSceneUIText | `char[256]` |
| PalScriptSlotStateOverlay | 860 | _todo_4e8 | `int` |
| PalScriptWaitObj | 0 | m_nTodo_000 | `void *` |
| PalScriptWaitObj | 4 | m_needscriptdel | `gbImage2D *` |
| PalScriptWaitTimer | 8 | m_fElapsed | `float` |
| PalScriptWaitTimer | 12 | m_bDone | `char` |
| ParabolaCalculator | 0 | velocity | `gbVec3D` |
| ParabolaCalculator | 12 | A | `gbVec3D` |
| ParabolaCalculator | 24 | B | `gbVec3D` |
| ParabolaCalculator | 36 | H | `float` |
| ParabolaCalculator | 40 | G | `float` |
| ParabolaCalculator | 44 | m_state | `int` |
| Param0 | 0 | loc | `localVar0` |
| Param0 | 12 | retAddr | `unsigned int` |
| Param0 | 16 | pOut | `unsigned int` |
| Param0 | 20 | pIn | `unsigned int` |
| Param0 | 24 | n | `unsigned int` |
| Param1 | 0 | loc | `localVar1` |
| Param1 | 28 | retAddr | `unsigned int` |
| Param1 | 32 | pOut | `unsigned int` |
| Param1 | 36 | pIn | `unsigned int` |
| Param1 | 40 | n | `unsigned int` |
| Param2 | 0 | loc | `localVar2` |
| Param2 | 268 | retAddr | `unsigned int` |
| Param2 | 272 | pOut | `unsigned int` |
| Param2 | 276 | OutStride | `unsigned int` |
| Param2 | 280 | pV | `unsigned int` |
| Param2 | 284 | VStride | `unsigned int` |
| Param2 | 288 | pM | `unsigned int` |
| Param2 | 292 | n | `unsigned int` |
| ParticleEffect | 362836 | active_parnum | `int` |
| ParticleEffect | 362840 | m_pTexture | `gbTexture_D3D *[4]` |
| ParticleEffect | 362856 | deltatime | `float` |
| PathFinder | 24 | m_curlayer | `NavTileLayer *` |
| PathFinder | 28 | m_layer | `int` |
| PathFinder | 32 | m_pRole | `Role *` |
| PathObj | 0 | points | `gbVec3D[256]` |
| PathObj | 3072 | numpoint | `int` |
| PathObj | 3076 | totallength | `float` |
| PathObj | 3080 | length | `float[256]` |
| PathObj | 4104 | normal | `gbVec3D *` |
| PathObj | 4108 | m_nCurPathLen | `int` |
| PathObj | 4112 | m_nTodo_1010 | `int` |
| PathObj | 4116 | m_pPathDir | `gbVec3D *` |
| PathObj | 4120 | m_nPathLen | `int` |
| PathObj | 4124 | m_nTodo_101C | `int` |
| PathObj | 7176 | segmentprojection | `float` |
| PathObj | 7180 | segmentlength | `float` |
| PathObj | 7184 | segmentnormal | `gbVec3D` |
| PathObj | 7196 | chosen | `gbVec3D` |
| PlayerAtt | 852 | hat | `PlayerItem` |
| PlayerAtt | 864 | cloth | `PlayerItem` |
| PlayerAtt | 876 | shoes | `PlayerItem` |
| PlayerAtt | 888 | wear | `PlayerItem[2]` |
| PlayerAtt | 912 | weapon | `PlayerItem` |
| PlayerAtt | 924 | maxrolevalue | `int[12]` |
| PlayerAtt | 972 | currolevalue | `int[12]` |
| PlayerAtt | 1020 | nProtectRole | `int` |
| PlayerAtt | 1024 | dwWeaponSkillID | `unsigned int` |
| PlayerAtt | 1028 | dwCleanCent | `unsigned int` |
| PlayerAtt | 1032 | fWeaponSkillMass | `float` |
| PlayerAtt | 1036 | dwSkillID | `unsigned int[9]` |
| PlayerAtt | 1072 | bSkillMastered | `_BYTE[9]` |
| PlayerAtt | 1084 | dwMagicID | `unsigned int[9][6]` |
| PlayerAtt | 1300 | bMagicMastered | `_BYTE[9][6]` |
| PlayerAtt | 1354 | byMagicUseTime | `unsigned __int16[9][6]` |
| PlayerAtt | 1462 | byMagicLevel | `_BYTE[9][6]` |
| PlayerAtt | 1516 | bAutoCtrl | `BYTE` |
| PlayerAtt | 1517 | bAIAttack | `BYTE` |
| PlayerAtt | 1518 | bAIMagic | `BYTE` |
| PlayerAtt | 1519 | bAISkill | `BYTE` |
| PlayerAtt | 1520 | bAIUseItem | `BYTE` |
| PlayerAtt | 1521 | bAINegative | `BYTE` |
| PlayerAtt | 1522 | byLineup | `BYTE` |
| PlayerAtts | 192 | m_nTodo_0C0 | `int` |
| PlayerAtts | 196 | m_nTodo_0C4 | `int` |
| PlayerAtts | 204 | m_nTodo_0CC | `int` |
| PlayerItem | 0 | id | `unsigned int` |
| PlayerItem | 4 | num | `int` |
| PlayerItem | 8 | item | `FightItem *` |
| PlayerItemSortFun | 0 | m_by | `int` |
| PlayerSkill | 0 | id | `unsigned int` |
| PlayerSkill | 4 | lv | `unsigned __int16` |
| PlayerSkill | 6 | usedtime | `unsigned __int16` |
| PlayerSkill | 8 | skill | `FightSkill *` |
| PolyLine | 0 | numpt | `int` |
| PolyLine | 4 | pt | `gbVec3D[16]` |
| PropUI | 72 | bkWndX | `int` |
| PropUI | 76 | bkWndY | `int` |
| PropUI | 80 | m_ListWidth | `int` |
| PropUI | 84 | m_ListHeight | `int` |
| PropUI | 88 | m_PropData | `st_Manager` |
| PropUI | 356 | m_nListCount | `int` |
| PropUI | 360 | m_nListSub | `int` |
| PropUI | 376 | m_nTodo_178 | `int` |
| PropUI | 400 | m_nTodo_190 | `int` |
| PropUI | 500 | m_nTodo_1F4 | `int` |
| PropUI | 504 | m_nTodo_1F8 | `int` |
| PropUI | 556 | m_nTodo_22C | `int` |
| PropUI | 600 | m_nTodo_258 | `int` |
| PropUI | 608 | m_nTodo_260 | `int` |
| PropUI | 612 | m_szItemTextA | `char[64]` |
| PropUI | 720 | m_nTodo_2D0 | `int` |
| PropUI | 724 | m_nTodo_2D4 | `int` |
| PropUI | 728 | m_nTodo_2D8 | `int` |
| PropUI | 732 | m_nTodo_2DC | `int` |
| PropUI | 736 | m_nTodo_2E0 | `int` |
| PropUI | 800 | m_nTodo_320 | `int` |
| PropUI | 1084 | m_SubTitleBBTY | `void *` |
| PropUI | 1164 | m_nTodo_48C | `int` |
| PropUI | 1168 | m_nTodo_490 | `int` |
| PropUI | 1380 | m_szItemTextB | `char[64]` |
| PropUI | 2148 | m_szItemTextC | `char[64]` |
| PropUI | 4376 | m_nTodo_1118 | `int` |
| PropUI | 13896 | m_nTodo_3648 | `int` |
| PropUI | 13904 | m_nTodo_3650 | `int` |
| PropUI | 13988 | m_nBuyListCap | `int` |
| PropUI | 15504 | m_nTodo_3C90 | `int` |
| PropUI | 16392 | m_pBuyListBase | `int` |
| PropUI | 17104 | m_bSelFlags | `int` |
| PropUI | 17592 | p_DealData | `PlayerItem *` |
| PropUI | 17596 | buf | `char[256]` |
| PropUI | 17852 | remarkbuf | `char[256]` |
| PropUI | 18108 | m_SelNum | `int` |
| PropUI | 18112 | m_ListSelNum | `int *` |
| PropUI | 18116 | m_MaxNum | `int *` |
| PropUI | 18120 | m_x | `int` |
| PropUI | 18124 | m_y | `int` |
| PropUI | 18128 | m_Sum | `int` |
| PropUI | 18132 | i | `int` |
| PropUI | 18136 | j | `int` |
| PropUI | 18140 | _isCreatable | `unsigned char` |
| PropUI | 18144 | m_Frame | `UIStatic` |
| PropUI | 18296 | m_EmbedUI3DCtrl | `int` |
| PropUI | 18304 | m_FrameBar | `UIFlexBar` |
| PropUI | 18388 | m_Flag | `UIStatic` |
| PropUI | 18540 | m_nTodo_486C | `int` |
| PropUI | 18544 | m_nTodo_4870 | `int` |
| PropUI | 18548 | m_OutFrameT | `UIStatic` |
| PropUI | 18708 | m_OutFrameR | `UIStatic` |
| PropUI | 18868 | m_OutFrameL | `UIStatic` |
| PropUI | 19028 | m_OutFrameB | `UIStatic` |
| PropUI | 19188 | mb_ExitRc | `tagRECT` |
| PropUI | 19204 | mb_Exit | `UIButton` |
| PropUI | 19548 | m_ani | `UIAnimateCtrl` |
| PropUI | 19712 | m_Role | `UIStatic[5]` |
| PropUI | 20512 | m_RoleRc | `tagRECT[5]` |
| PropUI | 20592 | RoleX | `int` |
| PropUI | 20596 | RoleY | `int` |
| PropUI | 20600 | HeadW | `int` |
| PropUI | 20604 | HeadH | `int` |
| PropUI | 20608 | m_Is | `_BYTE[5]` |
| PropUI | 20616 | m_Msg | `MUIDialog` |
| PropUI | 21916 | m_EmbedSubPanel | `int` |
| PropUI | 22000 | m_3DObj | `UI3DCtrl` |
| PropUI | 22308 | m_Dlg | `UIStatic` |
| PropUI | 22468 | m_DlgRc | `tagRECT` |
| PropUI | 22484 | m_TalkFrame | `UIStatic` |
| PropUI | 22644 | m_Ready | `UIStatic` |
| PropUI | 22804 | m_ReadyRc | `tagRECT` |
| PropUI | 22820 | m_ListFrame | `UIStatic` |
| PropUI | 22980 | m_ListGrid | `UIStatic[14]` |
| PropUI | 25220 | m_ScrollHB | `UIStatic` |
| PropUI | 25380 | m_EquipFlag | `UIStatic` |
| PropUI | 25540 | m_ListPropTitle | `UIStatic` |
| PropUI | 25700 | m_ListPropTitleRc | `tagRECT` |
| PropUI | 25716 | ml_ListProp | `UIListBox` |
| PropUI | 26960 | m_nCaptionOverlay | `int` |
| PropUI | 27004 | ml_ListPropRc | `tagRECT` |
| PropUI | 27020 | m_btnGroup | `BtnGroup` |
| PropUI | 27760 | m_ctrlTime | `float` |
| PropUI | 27764 | m_bCanUpdate1 | `unsigned char` |
| PropUI | 27765 | m_bCanUpdate2 | `unsigned char` |
| PropUI | 27768 | m_PropRemarkBk | `UIStatic` |
| PropUI | 27928 | m_PropRemark | `UIStatic` |
| PropUI | 28088 | m_PropAtt | `UIStatic` |
| PropUI | 28248 | m_MoneyRemark | `UIStatic` |
| PropUI | 28408 | m_MoneyRc | `tagRECT` |
| PropUI | 28424 | m_SumProp | `UIStatic` |
| PropUI | 28584 | m_SumRc | `tagRECT` |
| PropUI | 28600 | mb_OK | `UIButton` |
| PropUI | 28944 | mb_OKRc | `tagRECT` |
| ProtectPanel | 72 | m_BK | `UIStatic` |
| ProtectPanel | 232 | m_WHFace | `UIPushButton` |
| ProtectPanel | 484 | m_WPXFace | `UIPushButton` |
| PtrArray | 0 | m_pData | `char *` |
| PtrArray | 4 | capacity | `int` |
| PtrArray | 8 | m_nSize | `int` |
| PtrArray | 12 | m_needscriptdel | `int` |
| PtrVec | 0 | m_bInitFlag | `unsigned char` |
| PtrVec | 4 | m_begin | `void *` |
| PtrVec | 8 | m_end | `void *` |
| PtrVec | 12 | m_cap | `void *` |
| PurgeEffect | 0 | pSrcTex | `gbTexture *` |
| PurgeEffect | 4 | pSrcImg | `gbImage2D` |
| PurgeEffect | 204 | pDstImg | `gbImage2D` |
| PurgeEffect | 404 | m_ItemNum | `int` |
| PurgeEffect | 408 | EffItem | `char[16]` |
| PurgeEffect | 424 | m_isUpdateMerge | `unsigned char` |
| RC_ARG | 0 | fov | `float` |
| RC_ARG | 4 | yaw | `float` |
| RC_ARG | 8 | pitch | `float` |
| RC_ARG | 12 | dist | `float` |
| RC_ARG | 16 | lookat | `gbVec3D` |
| RELIVEPARAM | 0 | AlphaSpeed | `float` |
| RELIVEPARAM | 4 | fTimeCounter | `float` |
| RELIVEPARAM | 8 | nWaitSecond | `int` |
| RELIVEPARAM | 12 | nState | `int` |
| RGNDATAHEADER | 0 | dwSize | `unsigned int` |
| RGNDATAHEADER | 4 | iType | `unsigned int` |
| RGNDATAHEADER | 8 | nCount | `unsigned int` |
| RGNDATAHEADER | 12 | nRgnSize | `unsigned int` |
| RGNDATAHEADER | 16 | rcBound | `tagRECT` |
| RenderTarget | 0 | m_iMode | `int` |
| RenderTarget | 4 | m_Texture | `gbTexture_D3D *` |
| RenderTarget | 8 | m_nRenderX | `int` |
| RenderTarget | 12 | m_nRenderY | `int` |
| RenderTarget | 16 | m_nHalfW | `int` |
| RenderTarget | 20 | m_nHalfH | `unsigned char` |
| RenderTarget | 24 | m_nHalfWidth | `int` |
| RenderTarget | 28 | m_nHalfHeight | `int` |
| RenderTarget | 32 | m_nWidth | `int` |
| RenderTarget | 36 | m_nHeight | `int` |
| RenderTarget | 40 | m_nTodo_028 | `unsigned char` |
| RenderTarget | 44 | m_nTodo_02C | `float` |
| RenderTarget | 48 | m_fX | `float` |
| RenderTarget | 52 | m_fY | `float` |
| RenderTarget | 56 | m_nTodo_038 | `int` |
| RenderTarget | 60 | m_nTodo_03C | `int` |
| RenderTarget | 64 | m_fileHeader | `float` |
| RenderTarget | 68 | m_fRenderX | `float` |
| RenderTarget | 72 | m_fRenderY | `float` |
| RenderTarget | 76 | m_fileData | `float` |
| RenderTarget | 80 | m_fFileParam | `float` |
| RenderTarget | 84 | m_nColor | `int` |
| RenderTarget | 88 | m_szPath | `int` |
| RenderTarget | 92 | m_nDefaultH | `int` |
| RenderTarget | 100 | m_ScreenPlane | `gbTexture_D3D *` |
| RenderTarget | 124 | m_nAlpha | `int` |
| RenderTarget | 128 | m_bVisible | `int` |
| RenderTarget | 132 | m_fRenderIntensity | `float` |
| RenderTarget | 136 | m_fOffsetParam | `float` |
| RenderTarget | 140 | m_fRender | `float` |
| RenderTarget | 144 | m_fOffsetX | `float` |
| RenderTarget | 148 | m_fOffsetY | `float` |
| RenderTarget | 152 | m_nScaleX | `int` |
| RenderTarget | 156 | m_nScaleY | `int` |
| RenderTarget | 160 | m_szTexPath | `char[16]` |
| RenderTarget | 176 | m_fInvScale | `float` |
| RenderTarget | 184 | m_nDeviceLost | `int` |
| RenderTarget | 188 | m_nTodo_0BC | `int` |
| RenderTarget | 196 | m_nState | `int` |
| RenderTarget3 | 4 | m_ptr_4 | `gbRenderEffect *` |
| Reoccupy | 0 | m_id | `char[16]` |
| RestScript | 0 | m_LoadRest | `TxtFile` |
| RestScript | 524 | m_lastFile | `char[256]` |
| RestScript | 780 | m_Data | `ScriptData` |
| Role | 96 | m_cmdqueue | `char[48]` |
| Role | 144 | m_bInView | `int` |
| Role | 148 | m_groundpos | `gbVec3D` |
| Role | 160 | m_renderpos | `gbVec3D` |
| Role | 172 | m_npcinfo | `NPCInfo` |
| Role | 628 | m_onlayer | `int` |
| Role | 632 | m_active | `int` |
| Role | 636 | bCGMonster | `unsigned char` |
| Role | 640 | nCGMonsterID | `int` |
| Role | 644 | nCGMonsterType | `int` |
| Role | 648 | bRelive | `unsigned char` |
| Role | 649 | bInvincible | `unsigned char` |
| Role | 652 | fRattrapWait | `float` |
| Role | 656 | fMirrorWait | `float` |
| Role | 660 | bMirror | `unsigned char` |
| Role | 664 | fCGBIXIE | `int` |
| Role | 668 | bCGBIXIE | `unsigned char` |
| Role | 669 | bCrossAlpha | `unsigned char` |
| Role | 672 | fCrossAlpha | `int` |
| Role | 676 | bCGMonsterHitObj | `unsigned char` |
| Role | 677 | bStill | `unsigned char` |
| Role | 680 | pCG_SceneProp | `SceneProp *` |
| Role | 684 | m_actor | `Actor` |
| Role | 1504 | m_talkoldact | `ACTION_KIND` |
| Role | 1508 | m_talkoldface | `float` |
| Role | 1512 | m_talkobj | `SceneObj *` |
| Role | 1516 | m_mstate | `int` |
| Role | 1520 | m_matt | `RoleAtt *` |
| Role | 1524 | m_mfreedist | `float` |
| Role | 1528 | m_mattackrange | `float` |
| Role | 1532 | m_mfindradius | `float` |
| Role | 1536 | m_statetime | `float` |
| Role | 1540 | m_weapon | `gbGeomNode *` |
| Role | 1544 | m_bLeftWeapon | `unsigned char` |
| Role | 1545 | m_bRightWeapon | `unsigned char` |
| Role | 1548 | m_nRad | `int` |
| Role | 1552 | m_nRealHeadPos | `int` |
| Role | 1556 | m_nOverlapState | `int` |
| Role | 1560 | m_tpos | `tagPOINT` |
| Role | 1568 | m_vTagHeadPos | `gbVec3D` |
| Role | 1580 | m_overlap | `int` |
| Role | 1584 | m_bPathMove | `int` |
| Role | 1588 | m_pathMoveCounter | `int` |
| Role | 1592 | m_lastpos | `gbVec3D` |
| Role | 1604 | m_notePos | `gbVec3D` |
| Role | 1616 | m_path_region | `char[7076]` |
| Role | 8692 | m_wanapos | `gbVec3D` |
| RoleAtt | 0 | id | `unsigned int` |
| RoleAtt | 4 | type | `unsigned __int16` |
| RoleAtt | 6 | Remark | `_inline_RoleAtt_Remark` |
| RoleAtt | 518 | ModelID | `char[30]` |
| RoleAtt | 548 | ImageID | `char[30]` |
| RoleAtt | 580 | att | `int[5]` |
| RoleAtt | 600 | name | `char[32]` |
| RoleAtt | 632 | lv | `float` |
| RoleAtt | 636 | rolevalue | `int[12]` |
| RoleAtt | 684 | fightstate | `_BYTE[31]` |
| RoleAtt | 716 | RoundNum | `float` |
| RoleAtt | 720 | SAID | `unsigned char` |
| RoleAtt | 724 | Escape | `float` |
| RoleAtt | 728 | haogan | `unsigned __int16[5]` |
| RoleAtt | 740 | exp | `float` |
| RoleAtt | 744 | gold | `unsigned __int16` |
| RoleAtt | 748 | NormalAtkID | `unsigned int` |
| RoleAtt | 752 | height | `BYTE` |
| RoleAtt | 753 | move | `BYTE` |
| RoleAtt | 754 | attackrange | `BYTE` |
| RoleAtt | 755 | speed1 | `BYTE` |
| RoleAtt | 756 | speed2 | `BYTE` |
| RoleAtt | 760 | skill | `unsigned int[4]` |
| RoleAtt | 776 | skill_lv | `_BYTE[3]` |
| RoleAtt | 780 | RoleQiAdd | `int` |
| RoleAtt | 784 | append | `float[10]` |
| RoleAtt | 824 | normalplunder | `unsigned int` |
| RoleAtt | 828 | normalplundernum | `signed __int16` |
| RoleAtt | 832 | shikuai | `unsigned int` |
| RoleAtt | 836 | shikuaiskill | `unsigned int` |
| RoleAtt | 840 | shikuaisucc | `signed __int16` |
| RoleAtt | 842 | stealmoney | `signed __int16` |
| RoleAtt | 844 | steal | `unsigned int` |
| RoleAtt | 848 | stealnum | `signed __int16` |
| RoleAtt | 850 | getmoney | `signed __int16` |
| RoleAttRemarkSkills | 290 | skillCount | `_inline_RoleAttRemarkSkills_skillCount` |
| RoleCamera | 380 | m_ptarget | `Role *` |
| RoleCamera | 384 | m_pobj | `SceneObj *` |
| RoleCamera | 388 | m_targetpos | `gbVec3D` |
| RoleCamera | 400 | m_lastFrom | `gbVec3D` |
| RoleCamera | 412 | m_fromVec | `gbVec3D` |
| RoleCamera | 424 | m_yaw | `float` |
| RoleCamera | 428 | m_fCtrlYaw | `float` |
| RoleCamera | 432 | m_dist | `int` |
| RoleCamera | 436 | m_pitch | `float` |
| RoleCamera | 440 | m_roll | `int` |
| RoleCamera | 444 | m_nextYAW | `float` |
| RoleCamera | 448 | m_lastYAW | `float` |
| RoleCamera | 452 | m_camVelocity | `gbVec3D` |
| RoleCamera | 468 | m_nTodo_1D4 | `int` |
| RoleCamera | 480 | m_nTodo_1E0 | `int` |
| RoleCamera | 484 | m_nTodo_1E4 | `int` |
| RoleCamera | 488 | m_nTodo_1E8 | `int` |
| RoleCamera | 500 | m_nTodo_1F4 | `int` |
| RoleCamera | 512 | m_bFree | `int` |
| RoleCamera | 516 | m_bLockForward | `int` |
| RoleCamera | 520 | m_bLockCenter | `int` |
| RoleCamera | 524 | m_bProcessCollision | `int` |
| RoleCamera | 528 | m_CollideTriangleNum | `int` |
| RoleCamera | 532 | polygonList | `char[16]` |
| RoleCamera | 548 | polygonListBackup | `char[16]` |
| RoleCamera | 564 | m_CollideData | `char[12]` |
| RoleCamera | 576 | m_clientwidth | `int` |
| RoleCamera | 580 | m_clientheight | `int` |
| RoleCamera | 584 | CAMERA_LOCK_HALFRADIUS | `BYTE` |
| RoleCamera | 585 | CAMERA_COLLIDE_METHOD | `BYTE` |
| RoleCamera | 588 | m_lookat | `gbVec3D` |
| RoleCamera | 600 | m_from | `gbVec3D` |
| RoleCamera | 612 | m_forward | `gbVec3D` |
| RoleCamera | 624 | m_up | `gbVec3D` |
| RoleCamera | 636 | m_side | `gbVec3D` |
| RoleCamera | 648 | m_LockForward | `gbVec3D` |
| RoleCamera | 660 | m_LockCenter | `gbVec3D` |
| RoleCamera | 672 | m_bCollide | `BYTE` |
| RoleCamera | 676 | m_roomHeight | `float` |
| RoleCamera | 680 | m_lastUP | `gbVec3D` |
| RoleCameraCtrl | 72 | m_pTextArea | `UITextArea *` |
| RoleCtrl | 0 | s_camera | `int` |
| RoleCtrl | 4 | s_cameraedit | `int` |
| RoleCtrl | 8 | s_clickpt | `gbVec3D` |
| RoleCtrl | 20 | s_bUpdateSnd | `int` |
| RoleCtrl | 24 | s_prole | `Role *` |
| RoleCtrl | 28 | s_enable | `int` |
| RoleCtrl | 32 | s_cursorpos | `tagPOINT` |
| RoleFadeIn | 8 | m_passedtime | `float` |
| RoleFadeIn | 12 | m_role | `Role *` |
| RoleFadeIn | 16 | end | `BYTE` |
| RoleFadeOut | 8 | m_passedtime | `float` |
| RoleFadeOut | 12 | m_role | `Role *` |
| RoleFadeOut | 16 | end | `BYTE` |
| RoleShadow | 4 | m_shadowtex | `gbTexture *` |
| RoleShadow | 8 | m_effect | `gbRenderEffect *` |
| RoleShadow | 12 | m_effectFog | `gbRenderEffect *` |
| RoleShadow | 16 | m_effectFrame | `gbRenderEffect *` |
| RoleShadow | 20 | m_quad | `gbGeomQuad[77]` |
| RoleShadow | 5256 | m_CtrlRoleQuad | `gbGeomQuad` |
| RoleShadow | 5324 | m_pFrameShadow | `FrameTex *` |
| RoleShadow | 5328 | m_nFrameNum | `int` |
| RoleShadow | 5332 | m_nCurFrame | `int` |
| RoleShadow | 5336 | m_nFrameFPS | `int` |
| RoleShadow | 5340 | m_bFrameShadow | `BYTE` |
| RoleStatePanel | 96 | m_nScanIndex | `int` |
| RoleStatePanel | 361 | m_bSlotFlags | `_BYTE[5]` |
| RoleStatePanel | 528 | m_RoleStatics | `UIStatic[5]` |
| RoleStatePanel | 155140 | m_roles | `s_RoleState[5]` |
| RoleStatePanel | 176060 | m_pSubTab1 | `UITitle_XJTM *` |
| RoleStatePanel | 176064 | m_pSubTab2 | `void *` |
| RoleStatePanel | 176084 | m_nEquipSlot | `int` |
| RoleStatePanel | 176088 | m_nTodo_2afd8 | `unsigned char` |
| RoleStatePanel | 176089 | m_nTodo_2afd9 | `unsigned char` |
| RoleStatePanel | 176248 | m_nDevLost1 | `int` |
| RoleStatePanel | 176252 | m_nDevLost2 | `int` |
| RoleSystem | 68 | m_pVtable | `char *` |
| RoleSystem | 72 | m_fStateX | `float` |
| RoleSystem | 76 | m_fStateY | `float` |
| RoleSystem | 80 | m_nStateMode | `unsigned char` |
| RoleSystem | 84 | m_nTimerDuration | `int` |
| RoleSystem | 88 | m_fDirX | `float` |
| RoleSystem | 92 | m_fDirY | `float` |
| RoleSystem | 96 | m_fDirZ | `float` |
| RoleSystem | 100 | m_pPathPoints | `char *` |
| RoleSystem | 104 | m_nPathCount | `int` |
| RoleSystem | 108 | m_pPathCurrent | `char *` |
| RoleSystem | 112 | m_pPathNext | `char *` |
| RoleSystem | 116 | m_nTodo_074 | `int` |
| RoleSystem | 120 | m_nPathFlag | `int` |
| RoleSystem | 124 | m_nTodo_7C | `int` |
| RoleSystem | 128 | m_fMoveX | `float` |
| RoleSystem | 132 | m_nPathState | `int` |
| RoleSystem | 136 | m_fMoveZ | `float` |
| RoleSystem | 140 | m_pPathListHead | `char *` |
| RoleSystem | 144 | m_nActionResult | `int` |
| RoleSystem | 148 | m_nDispFontColor | `int` |
| RoleSystem | 152 | m_nDispWndColor | `int` |
| RoleSystem | 156 | m_nTodo_9C | `int` |
| RoleSystem | 160 | m_fPosX | `float` |
| RoleSystem | 164 | m_fPosY | `float` |
| RoleSystem | 168 | m_fPosZ | `float` |
| RoleSystem | 172 | m_nFacing | `char` |
| RoleSystem | 173 | m_nActionState | `char` |
| RoleSystem | 174 | m_animStateU | `_inline_RoleSystem_m_animStateU` |
| RoleSystem | 176 | m_szModelName | `int` |
| RoleSystem | 180 | m_mapData | `int` |
| RoleSystem | 184 | m_fScale | `float` |
| RoleSystem | 188 | m_nImageIdx | `int` |
| RoleSystem | 192 | m_fMoveSpd | `float` |
| RoleSystem | 206 | m_byStateArray | `unsigned char` |
| RoleSystem | 208 | m_bFlags | `char` |
| RoleSystem | 209 | m_bActionState | `unsigned char` |
| RoleSystem | 216 | m_fAngle | `float` |
| RoleSystem | 220 | m_fTileHeight | `float` |
| RoleSystem | 224 | m_nSpawnData | `int` |
| RoleSystem | 228 | m_nActionType | `int` |
| RoleSystem | 232 | m_nActionStep | `int` |
| RoleSystem | 236 | m_fActionParam | `float` |
| RoleSystem | 240 | m_nSpawnFlags | `unsigned char` |
| RoleSystem | 244 | m_nRoleAction | `unsigned char` |
| RoleSystem | 246 | m_nRoleSlot | `unsigned char` |
| RoleSystem | 248 | m_fWaypointX | `float` |
| RoleSystem | 252 | m_fWaypointZ | `float` |
| RoleSystem | 256 | m_nActionParam | `unsigned char` |
| RoleSystem | 260 | m_nInitMoveMode | `unsigned char` |
| RoleSystem | 264 | m_nSpawnExtra | `int` |
| RoleSystem | 268 | m_nSpawnParam2 | `int` |
| RoleSystem | 272 | m_szModelPath | `int` |
| RoleSystem | 276 | m_pWaypointWnd | `UIWnd *` |
| RoleSystem | 288 | m_nParamArray | `int` |
| RoleSystem | 300 | m_bSpawnByteA | `unsigned char` |
| RoleSystem | 301 | m_bSpawnByteB | `unsigned char` |
| RoleSystem | 304 | m_nSpawnParam | `int` |
| RoleSystem | 308 | m_nActionTimer | `int` |
| RoleSystem | 312 | m_vecPosArray | `gbVec3D` |
| RoleSystem | 328 | m_nMoveSrc | `int` |
| RoleSystem | 332 | m_nMoveDst | `int` |
| RoleSystem | 336 | m_nMoveStep | `int` |
| RoleSystem | 352 | m_nSavedState | `int` |
| RoleSystem | 356 | m_nVisState | `int` |
| RoleSystem | 360 | m_bVisFlag | `unsigned char` |
| RoleSystem | 361 | _gap_169 | `_BYTE[3]` |
| RoleSystem | 364 | m_pWndFrame | `char *` |
| RoleSystem | 368 | m_nTodo_170 | `int` |
| RoleSystem | 380 | m_nActive | `int` |
| RoleSystem | 384 | m_fInactiveTime | `float` |
| RoleSystem | 400 | m_pCmdQueue | `void *` |
| RoleSystem | 404 | m_pCmdQueueEnd | `void *` |
| RoleSystem | 408 | m_fCmdInterval | `float` |
| RoleSystem | 412 | m_fCmdTimer | `float` |
| RoleSystem | 416 | m_pPathNodeIter | `char *` |
| RoleSystem | 420 | m_nCmdQueuePos | `int` |
| RoleSystem | 424 | m_partyActor | `Actor` |
| RoleSystem | 1244 | m_fPathTargetY | `float` |
| RoleSystem | 1248 | m_fPathTargetZ | `float` |
| RoleSystem | 1252 | m_fPathAngle | `float` |
| RoleSystem | 1256 | m_fPathSpeed | `float` |
| RoleSystem | 1260 | m_nPrevMoveMode | `int` |
| RoleSystem | 1264 | m_nMoveMode | `int` |
| RoleSystem | 1268 | m_nMoveSubMode | `int` |
| RoleSystem | 1272 | m_nCollisionState | `int` |
| RoleSystem | 1276 | m_nCollisionParam | `int` |
| RoleSystem | 1280 | m_bPathActive | `unsigned char` |
| RoleSystem | 1284 | m_nCoreState | `int` |
| RoleSystem | 1288 | m_nTransformState | `float` |
| RoleSystem | 1292 | m_fMovement | `float` |
| RoleSystem | 1296 | m_fRotAxisX | `float` |
| RoleSystem | 1300 | m_fRotAxisY | `float` |
| RoleSystem | 1304 | m_fRotAxisZ | `float` |
| RoleSystem | 1308 | m_nMovement | `float` |
| RoleSystem | 1312 | m_fSavedRotX | `float` |
| RoleSystem | 1316 | m_FrameA | `UIFrameWnd` |
| RoleSystem | 1388 | m_nActiveRole | `int` |
| RoleSystem | 1392 | m_nRoleCount | `int` |
| RoleSystem | 1396 | m_nAnimation | `int` |
| RoleSystem | 1400 | m_nAnimCopy1 | `int` |
| RoleSystem | 1404 | m_nAnimCopy2 | `int` |
| RoleSystem | 1408 | m_nAnimCopy3 | `int` |
| RoleSystem | 1412 | m_pLinkedRole | `Object3D *` |
| RoleSystem | 1416 | m_nTransformMode | `int` |
| RoleSystem | 1420 | m_pLinkedSystem | `char *` |
| RoleSystem | 1424 | m_fAnimSpeed | `float` |
| RoleSystem | 1428 | m_fMoveRadius | `float` |
| RoleSystem | 1432 | m_fMoveSpeed | `float` |
| RoleSystem | 1436 | m_nMoveReset | `int` |
| RoleSystem | 1440 | m_pRenderObj | `gbGeomNode *` |
| RoleSystem | 1444 | m_bRenderFlag1 | `int` |
| RoleSystem | 1448 | m_bRenderFlag2 | `char` |
| RoleSystem | 1452 | m_nTodo_5AC | `int` |
| RoleSystem | 1456 | m_pCtrlPoint | `char *` |
| RoleSystem | 1460 | m_nMoveRole | `int` |
| RoleSystem | 1464 | m_nRetryCount | `int` |
| RoleSystem | 1468 | m_fCachePosX | `float` |
| RoleSystem | 1472 | m_fCachePosY | `float` |
| RoleSystem | 1476 | m_fCachePosZ | `float` |
| RoleSystem | 1480 | m_fMoveTargetX | `float` |
| RoleSystem | 1484 | m_fMoveTargetY | `int` |
| RoleSystem | 1488 | m_fMoveTargetZ | `float` |
| RoleSystem | 1492 | m_fMoveRole | `float` |
| RoleSystem | 1496 | m_fMoveParamY | `float` |
| RoleSystem | 1500 | m_fMoveParamZ | `float` |
| RoleSystem | 1564 | m_nTodo_61C | `int` |
| RoleSystem | 1572 | m_nTodo_624 | `UIWnd` |
| RoleSystem | 1676 | m_nTodo_68C | `int` |
| RoleSystem | 1680 | m_nTodo_690 | `float` |
| RoleSystem | 2960 | m_nTodo_B90 | `int` |
| RoleSystem | 2968 | m_wndPanel | `int` |
| RoleSystem | 2988 | m_StaticSlotArray | `UIWnd` |
| RoleSystem | 3072 | m_teamSlotsB | `_inline_RoleSystem_m_teamSlotsB` |
| RoleSystem | 4028 | m_pScriptBuf | `int` |
| RoleSystem | 4068 | m_nField_FE4 | `int` |
| RoleSystem | 4088 | m_nTodo_FF8 | `void *` |
| RoleSystem | 4096 | m_configData | `int[96]` |
| RoleSystem | 4484 | m_nTodo_1184 | `int` |
| RoleSystem | 4488 | m_nTodo_1188 | `int` |
| RoleSystem | 4492 | m_nMoveState1 | `int` |
| RoleSystem | 4496 | m_nMoveState2 | `int` |
| RoleSystem | 4500 | m_nMoveState3 | `int` |
| RoleSystem | 4504 | m_bMoveFlag1 | `unsigned char` |
| RoleSystem | 4508 | m_nMoveParam1 | `int` |
| RoleSystem | 4512 | m_nMoveParam2 | `int` |
| RoleSystem | 4516 | m_bMoveFlag2 | `unsigned char` |
| RoleSystem | 4520 | m_partyUI3 | `UIItem` |
| RoleSystem | 4752 | m_teamData3 | `int[29]` |
| RoleSystem | 6504 | dword_17AA450 | `int` |
| RoleSystemTeamSlotOverlay | 4 | m_teamSlots | `_inline_RoleSystemTeamSlotOverlay_m_teamSlots` |
| RoleTask | 0 | dwNameCrc | `unsigned int` |
| RoleTask | 4 | nType | `int` |
| RoleTask | 8 | tasktitle | `char[128]` |
| RoleTask | 136 | taskRemark | `char[256]` |
| RoleTask | 392 | bLast | `BYTE` |
| RoleTaskLine | 0 | nType | `int` |
| RoleTaskLine | 4 | ID | `int` |
| RoleTaskLine | 8 | bFinished | `BYTE` |
| RoleTaskLine | 9 | taskpic | `char[128]` |
| RoleTaskPool | 0 | m_TaskData | `char[16]` |
| RoleTaskPool | 16 | m_TaskLine | `char[16]` |
| RoleTaskPool | 32 | m_taskFile | `TxtFile` |
| RoleTaskPool | 556 | _TaskPicFolder | `char[128]` |
| RotateInvObj | 8 | m_passedtime | `float` |
| RotateInvObj | 12 | end | `BYTE` |
| RotateInvObj | 16 | m_rotate | `gbVec3D` |
| RotateObj | 8 | m_passedtime | `float` |
| RotateObj | 12 | end | `BYTE` |
| RotateObj | 16 | m_rotate | `gbVec3D` |
| RotateObj | 28 | m_rotatetime | `float` |
| RotateObj | 32 | m_mode | `BYTE` |
| SCNFile | 0 | m_info | `SceneInfo` |
| SCNFile | 132 | m_numnpc | `int` |
| SCNFile | 136 | m_npc | `NPCInfo[72]` |
| SCNFile | 32968 | m_numobj | `int` |
| SCNFile | 32972 | m_obj | `char[256]` |
| SCNHeader | 0 | magic | `_BYTE[4]` |
| SCNHeader | 4 | version | `unsigned __int16` |
| SCNHeader | 6 | numnpc | `unsigned __int16` |
| SCNHeader | 8 | offsetnpc | `unsigned int` |
| SCNHeader | 12 | numobj | `unsigned __int16` |
| SCNHeader | 14 | offsetobj | `char[2]` |
| SSE4xMatrix | 0 | _11 | `float` |
| SSE4xMatrix | 16 | _12 | `float` |
| SSE4xMatrix | 32 | _13 | `float` |
| SSE4xMatrix | 48 | _14 | `float` |
| SSE4xMatrix | 64 | _21 | `float` |
| SSE4xMatrix | 80 | _22 | `float` |
| SSE4xMatrix | 96 | _23 | `float` |
| SSE4xMatrix | 112 | _24 | `float` |
| SSE4xMatrix | 128 | _31 | `float` |
| SSE4xMatrix | 144 | _32 | `float` |
| SSE4xMatrix | 160 | _33 | `float` |
| SSE4xMatrix | 176 | _34 | `float` |
| SSE4xMatrix | 192 | _41 | `float` |
| SSE4xMatrix | 208 | _42 | `float` |
| SSE4xMatrix | 224 | _43 | `float` |
| SSE4xMatrix | 240 | _44 | `float` |
| S_Distribute | 0 | id | `unsigned int` |
| S_Distribute | 4 | Num | `int` |
| S_Distribute | 8 | m_Type | `int` |
| S_Distribute | 12 | m_Index | `int` |
| SaleUI | 72 | bkWidth | `int` |
| SaleUI | 76 | bkHeight | `int` |
| SaleUI | 80 | buf | `char[256]` |
| SaleUI | 336 | remarkbuf | `char[256]` |
| SaleUI | 592 | m_SelNum | `int` |
| SaleUI | 596 | m_data | `st_Manager` |
| SaleUI | 1160 | m_inventory | `Inventory` |
| SaleUI | 1200 | m_reoccupy | `Reoccupy` |
| SaleUI | 1216 | dwWeaponWU | `int` |
| SaleUI | 18100 | m_sort | `SaleUI_SortData[299][5]` |
| SaleUI | 30060 | m_ListSelNum | `int[299][5]` |
| SaleUI | 36040 | m_Max | `int[299][5]` |
| SaleUI | 42020 | m_Sum | `int[5]` |
| SaleUI | 42040 | _isCreatable | `unsigned char` |
| SaleUI | 42044 | m_SaleData | `PlayerItem[299][5]` |
| SaleUI | 59984 | m_TempData | `PlayerItem[158]` |
| SaleUI | 61880 | m_bNGHS | `int` |
| SaleUI | 61884 | m_bWPXS | `int` |
| SaleUI | 77924 | m_NotesNull | `int[299][5]` |
| SaleUI | 83904 | m_IsEquip | `_BYTE[299][5]` |
| SaleUI | 85399 | m_TempIsEquip | `_BYTE[299][5]` |
| SaleUI | 86896 | x | `int` |
| SaleUI | 86900 | rc | `tagRECT` |
| SaleUI | 86916 | m_Frame | `UIStatic` |
| SaleUI | 87076 | m_FrameBar | `UIFlexBar` |
| SaleUI | 87160 | m_Flag | `UIStatic` |
| SaleUI | 87320 | m_OutFrameT | `UIStatic` |
| SaleUI | 87480 | m_OutFrameR | `UIStatic` |
| SaleUI | 87640 | m_OutFrameL | `UIStatic` |
| SaleUI | 87800 | m_OutFrameB | `UIStatic` |
| SaleUI | 87960 | mb_Exit | `UIButton` |
| SaleUI | 88304 | m_ExitRc | `tagRECT` |
| SaleUI | 88320 | m_ani | `UIAnimateCtrl` |
| SaleUI | 88484 | m_Role | `UIStatic[5]` |
| SaleUI | 89284 | m_RoleRc | `tagRECT[5]` |
| SaleUI | 89364 | RoleX | `int` |
| SaleUI | 89368 | RoleY | `int` |
| SaleUI | 89372 | HeadW | `int` |
| SaleUI | 89376 | HeadH | `int` |
| SaleUI | 89380 | m_Is | `_BYTE[5]` |
| SaleUI | 89388 | m_Msg | `MUIDialog` |
| SaleUI | 90772 | m_3DObj | `UI3DCtrl` |
| SaleUI | 91080 | m_FlagRc | `tagRECT` |
| SaleUI | 91096 | m_TalkFrame | `UIStatic` |
| SaleUI | 91256 | m_Ready | `UIStatic` |
| SaleUI | 91416 | m_ReadyRc | `tagRECT` |
| SaleUI | 91432 | m_entryTalk | `char[256]` |
| SaleUI | 91688 | m_btn | `UIButton[5]` |
| SaleUI | 93408 | m_TabRc | `tagRECT` |
| SaleUI | 93424 | m_ListSaleTitle | `UIStatic` |
| SaleUI | 93584 | m_ListEquipTitleRc | `tagRECT` |
| SaleUI | 93600 | m_Icon | `UIStaticRM[5][5]` |
| SaleUI | 98300 | m_ListFrame | `UIStatic` |
| SaleUI | 98460 | m_ScrollHB | `UIStatic` |
| SaleUI | 98620 | m_ListGrid | `UIStatic[14]` |
| SaleUI | 100860 | m_ListRc | `tagRECT` |
| SaleUI | 100876 | ml_ResumeList | `UIListBox` |
| SaleUI | 102164 | ResumeNum | `int` |
| SaleUI | 102168 | ml_TreasureList | `UIListBox` |
| SaleUI | 103456 | TreasureNum | `int` |
| SaleUI | 103460 | ml_AttackList | `UIListBox` |
| SaleUI | 104748 | AttackNum | `int` |
| SaveTask | 0 | mTouchCounter | `int` |
| SaveTask | 4 | m_iState | `int` |
| SaveTask | 8 | m_bCVDOver | `BYTE` |
| SceHeader | 0 | flag | `_BYTE[4]` |
| SceHeader | 4 | version | `BYTE` |
| SceHeader | 5 | blocknum | `char` |
| SceIndex | 0 | id | `unsigned int` |
| SceIndex | 4 | offset | `unsigned int` |
| SceIndex | 8 | desc | `char[64]` |
| SceOpcodeEntry | 0 | handler | `char *` |
| SceOpcodeEntry | 4 | paramTypes | `char[7]` |
| SceOpcodeEntry | 11 | _pad | `char` |
| SceOpcodeEntry | 12 | paramCount | `signed __int16` |
| SceOpcodeEntry | 14 | _pad2 | `signed __int16` |
| Scene | 4 | m_pDataBegin | `char *` |
| Scene | 8 | m_pDataEnd | `char *` |
| Scene | 12 | m_pCapacity | `char *[29]` |
| Scene | 128 | m_nReset | `int` |
| Scene | 132 | m_geomnode | `gbGeomNode *` |
| Scene | 136 | m_lights | `gbVisNode *` |
| Scene | 140 | m_aabb | `gbAABBox` |
| Scene | 164 | m_bbArray | `PtrArray` |
| Scene | 180 | m_objmap | `SceneMapObj[2]` |
| Scene | 220 | m_numobj | `int` |
| Scene | 224 | m_roleSlots | `tagRoleSlot[64]` |
| Scene | 57568 | m_nTodo_e0e0 | `int` |
| Scene | 57572 | m_roles | `Role[50]` |
| Scene | 493136 | m_nTodo_78650 | `int` |
| Scene | 493140 | m_nTodo_78654 | `int` |
| Scene | 493144 | m_nTodo_78658 | `int` |
| Scene | 493148 | m_nTodo_7865c | `BYTE` |
| Scene | 493152 | m_nTodo_78660 | `int` |
| SceneInfo | 0 | cityname | `char[32]` |
| SceneInfo | 32 | name | `char[32]` |
| SceneInfo | 64 | mdl | `char[32]` |
| SceneInfo | 96 | type | `SCENE_TYPE` |
| SceneInfo | 100 | lightmap | `unsigned int` |
| SceneInfo | 104 | skybox | `unsigned int` |
| SceneInfo | 108 | nCount | `int` |
| SceneInfo | 112 | pBuffer | `float *` |
| SceneInfo | 116 | fScale | `float` |
| SceneInfo | 120 | bFlag | `unsigned char` |
| SceneInfo | 124 | fResult | `float` |
| SceneInfo | 128 | nFlag | `int` |
| SceneMap | 4 | m_width | `int` |
| SceneMap | 8 | m_height | `int` |
| SceneMap | 12 | m_map | `_BYTE *` |
| SceneMapObj | 16 | m_scene | `Scene *` |
| SceneMapPlayer | 16 | m_nLayerIndex | `int` |
| SceneMapPlayer | 20 | m_playerpt | `tagPOINT` |
| SceneMapPlayer | 28 | m_playerfov | `tagRECT` |
| SceneMapPlayer | 44 | m_maxwidth | `int` |
| SceneMapPlayer | 48 | m_maxheight | `int` |
| SceneMapPlayer | 52 | m_tex | `gbTexture *` |
| SceneMapPlayer | 56 | m_img | `gbImage2D` |
| SceneMapPlayer | 256 | m_layer | `NavTileLayer *` |
| SceneMapPlayer | 260 | m_bBuild | `unsigned char` |
| SceneMapPlayer | 261 | m_szName | `char[128]` |
| SceneMgr | 0 | m_pGfxMgr | `gbGfxManager *` |
| SceneMgr | 4 | m_pSceneRoot | `gbSceneGraph *` |
| SceneMgr | 8 | m_pAddEffect2 | `gbRenderEffect *` |
| SceneMgr | 12 | m_pAlphaEffect2 | `gbRenderEffect *` |
| SceneMgr | 20 | m_pAlphaEffect | `gbRenderEffect *` |
| SceneMgr | 24 | m_pCamera | `gbCamera *` |
| SceneMgr | 28 | m_aSceneSlots | `float` |
| SceneMgr | 32 | m_nTodo_020 | `float[12]` |
| SceneMgr | 80 | m_PlayerAtts | `PlayerAtts` |
| SceneMgr | 1376 | m_RenderBuffer | `int[12]` |
| SceneMgr | 5160 | m_nTodo_1428 | `int` |
| SceneMgr | 5164 | m_nTodo_142C | `int` |
| SceneMgr | 5646 | m_nTodo_160E | `unsigned char` |
| SceneMgr | 5648 | m_nTodo_C059A0 | `RoleSystem` |
| SceneMgr | 50644 | _unkC5D4 | `char[4]` |
| SceneMgr | 50652 | m_pScriptCtrl | `PalScriptMgr *` |
| SceneMgr | 50814 |  | `_inline_SceneMgr_` |
| SceneMgr | 53324 | m_nField_D04C | `int` |
| SceneMgr | 53460 | m_nCollisionFlags | `int` |
| SceneMgr | 57568 | m_nRoleCount | `int` |
| SceneMgrCamBlock | 0 | _gap_000 | `char[84]` |
| SceneMgrCamBlock | 84 | m_pScriptArrayEnd | `PalScript *` |
| SceneMgrCamBlock | 88 | m_nTodo_058 | `PalScript *` |
| SceneMgrCamBlock | 92 | m_pUIScript | `PalScript *` |
| SceneMgrCamBlock | 96 | m_pScriptArrayEndSub | `PalScript *` |
| SceneMgrCamBlock | 100 | m_nUnlockDataOffset | `int` |
| SceneMgrCamBlock | 104 | m_nUnlockDataLen | `int` |
| SceneMgrCamBlock | 108 | m_RoleUnlockData | `int[100]` |
| SceneMgrCamBlock | 508 | m_nUnlockDataEndFlag | `int` |
| SceneMgrCamBlock | 512 | m_nUnlockDataCount | `int` |
| SceneMgrCamBlock | 516 | m_MonsterUnlockTable | `int[60]` |
| SceneMgrCamBlock | 756 | m_nMonsterUnlockEndFlag | `int` |
| SceneMgrCamBlock | 760 | m_nCurrentScene | `int` |
| SceneMgrCamBlock | 764 | m_pCameraScript | `PalScript *` |
| SceneObj | 68 | m_fTimerLimit | `int` |
| SceneObj | 76 | _SaveTaskInfo | `SaveTask` |
| SceneObj | 88 | m_fTime | `float` |
| SceneObj | 92 | m_fDeltaTime | `float` |
| SceneObj | 96 | m_fTimeScale | `float` |
| SceneObj | 100 | m_deltatime | `float` |
| SceneObj | 104 | m_bLockPropUI | `int` |
| SceneObj | 108 | m_bLockCamera | `unsigned char` |
| SceneObj | 112 | m_bProcessLinkObj | `int` |
| SceneObj | 116 | m_bCallProcessGroupObj | `int` |
| SceneObj | 120 | m_bMainGroupObj | `int` |
| SceneObj | 124 | dwEffGroupRunningID | `unsigned int` |
| SceneObj | 128 | bCGObj | `unsigned char` |
| SceneObj | 129 | sCGSHELF | `char[64]` |
| SceneObj | 196 | rCGSelfArea | `tagRECT` |
| SceneObj | 212 | rTouchAreaCG | `tagRECT` |
| SceneObj | 228 | fLastTime | `float` |
| SceneObj | 232 | mParam | `subPARAM` |
| SceneObj | 304 | mVelocity | `gbVec3D` |
| SceneObj | 316 | mTime | `float` |
| SceneObj | 320 | mStorePos | `gbVec3D` |
| SceneObj | 332 | mRetrorse | `int` |
| SceneObj | 336 | mTouchCounter | `int` |
| SceneObj | 340 | m_iState | `int` |
| SceneObj | 344 | m_bCVDOver | `unsigned char` |
| SceneObj | 348 | mOBBox | `gbOBBox` |
| SceneObj | 424 | m_pObjMsgBuffer | `char[256]` |
| SceneObj | 680 | m_pObjMsgBuffer2 | `char[256]` |
| SceneObj | 936 | m_renderpos | `gbVec3D` |
| SceneObj | 948 | m_subobj | `int` |
| SceneObj | 984 | m_mdl | `MyMdl` |
| SceneObj | 1068 | m_info | `ObjectInfo` |
| SceneObj | 1672 | m_path | `PathObj *` |
| SceneObj | 1676 | m_pmap | `SceneMapObj *` |
| SceneObj | 1680 | m_mapindex | `unsigned char` |
| SceneObj | 1684 | m_pushboxdir | `int` |
| SceneObj | 1688 | m_maprect | `tagRECT` |
| SceneObj | 1704 | m_liftrole | `int` |
| SceneObj | 1708 | m_common | `char[48]` |
| SceneObj | 1756 | m_snd | `gbSound3DNode *` |
| SceneObj | 1760 | m_radius | `float` |
| SceneObj | 1764 | m_runscript | `PalScript *` |
| SceneObj | 1768 | m_fRotateX | `float` |
| SceneObj | 1772 | m_fRotateY | `float` |
| SceneObj | 1776 | m_fRotateZ | `float` |
| SceneObj | 1780 | m_fParam | `float` |
| SceneObjParam | 0 | tmpVEC | `gbVec3D[8]` |
| SceneObjParam | 96 | mLinkObj | `SceneObj *` |
| SceneObjParam | 100 | mRole | `Role *` |
| SceneObjParam | 104 | mInfo | `ObjectInfo` |
| SceneObjScript | 0 | type | `BYTE` |
| SceneObjScript | 4 | objscript | `PalScript *` |
| SceneObjScript | 8 | obj | `SceneObj *` |
| SceneProp | 0 | pGeom | `gbGeomNode *` |
| SceneProp | 4 | rect | `tagRECT` |
| SceneProp | 20 | fCurTime | `float` |
| SceneProp | 24 | fValidTime | `float` |
| SceneProp | 28 | bCountTime | `BYTE` |
| SceneProp | 29 | bPopFling | `BYTE` |
| SceneProp | 32 | vecFling | `gbVec3D` |
| SceneProp | 44 | lastFling | `gbVec3D` |
| SceneProp | 56 | rotFling | `gbVec3D` |
| SceneProp | 68 | bCollide | `BYTE` |
| SceneProp | 72 | ID | `unsigned int` |
| SceneProp | 76 | bNeedParabola | `BYTE` |
| SceneProp | 80 | nFlag | `int` |
| SceneProp | 84 | bValid | `BYTE` |
| SceneProp | 88 | parabola | `ParabolaCalculator` |
| ScreenEffect | 8 | m_nType | `int` |
| ScreenEffect | 12 | m_life | `int` |
| ScreenEffect | 16 | m_age | `float` |
| ScreenEffect | 20 | m_hold | `BYTE` |
| ScreenEffectMgr | 0 | m_pVtable | `void *` |
| ScreenEffectMgr | 4 | m_fadeIn | `ScreenFadeIn` |
| ScreenEffectMgr | 32 | m_fadeOut | `ScreenFadeOut` |
| ScreenEffectMgr | 56 | m_fadeWhite | `ScreenFadeWhite` |
| ScreenEffectMgr | 80 | m_fadeWhite2 | `ScreenFadeWhite2` |
| ScreenEffectMgr | 104 | m_activeQueue | `char[4]` |
| ScreenEffectMgr | 108 | m_pAllocBlock | `void *` |
| ScreenEffectMgr | 112 | m_pAllocBlockEnd | `void *` |
| ScreenEffectMgr | 116 | m_pAllocPos | `void *` |
| ScreenEffectMgr | 120 | m_pAllocSlot | `void *` |
| ScreenEffectMgr | 124 | m_pAllocRest | `void *` |
| ScreenEffectMgr | 128 | m_nAllocFlag1 | `int` |
| ScreenEffectMgr | 132 | m_nAllocFlag2 | `int` |
| ScreenEffectMgr | 136 | m_fAllocFactor | `int` |
| ScreenEffectMgr | 140 | m_pEffect | `char *` |
| ScreenEffectMgr | 148 | m_nEffectCount | `int` |
| ScreenEffectNode | 164 | m_pTexture | `gbTexture *` |
| ScreenEffectNode | 168 | m_pRenderEffect | `gbRenderEffect *` |
| ScreenFadeIn | 24 | m_first | `int` |
| ScriptCounter | 0 | nMaxCount | `int` |
| ScriptCounter | 4 | nState | `int` |
| ScriptCounter | 8 | nCurCount | `int` |
| ScriptCounter | 12 | nResourceID | `int` |
| ScriptData | 0 | m_ID | `unsigned __int16` |
| ScriptData | 2 | m_Name | `char[256]` |
| ScriptData | 260 | m_RestPrice | `int` |
| ScriptData | 264 | m_Rest | `char[256]` |
| ScriptData | 520 | m_Enough | `char[256]` |
| ScriptData | 776 | m_NoEnough | `char[256]` |
| ScriptData | 1032 | m_RestEnd | `char[256]` |
| ScriptPoolPage | 0 | p_starting_alloc_map | `_BYTE *` |
| ScriptPoolPage | 4 | free_paras_at_start | `unsigned int` |
| ScriptPoolPage | 8 | alloc_map | `_BYTE[241]` |
| ScriptPoolPage | 249 | reserved | `_BYTE[7]` |
| ScriptPoolPage | 256 | alloc_blocks | `char[256]` |
| ScriptSystem | 0 | m_nSlotID | `int` |
| ScriptSystem | 4 | m_vPos_x | `float` |
| ScriptSystem | 8 | m_vPos_y | `float` |
| ScriptSystem | 12 | m_vPos_z | `float` |
| ScriptSystem | 20 | m_nTodo_014 | `float` |
| ScriptSystem | 24 | m_nTodo_018 | `float` |
| ScriptSystem | 28 | m_nTodo_01C | `int` |
| ScriptSystem | 32 | m_nTodo_020 | `int` |
| ScriptSystem | 36 | m_nSerialFlag | `int` |
| ScriptSystem | 40 | m_nTodo_28 | `int` |
| ScriptSystem | 104 | m_szFmtBuf | `char[40]` |
| ScriptSystem | 144 | m_nMoveState | `int` |
| ScriptSystem | 148 | m_vRot_x | `float` |
| ScriptSystem | 152 | m_vRot_y | `float` |
| ScriptSystem | 156 | m_vRot_z | `float` |
| ScriptSystem | 160 | m_vDir_x | `float` |
| ScriptSystem | 164 | m_vDir_y | `float` |
| ScriptSystem | 168 | m_vDir_z | `float` |
| ScriptSystem | 176 | m_nTodo_0B0 | `int` |
| ScriptSystem | 200 | m_nTodo_0C8 | `int` |
| ScriptSystem | 208 | m_nTodo_0D0 | `int` |
| ScriptSystem | 268 | m_nTodo_10C | `int` |
| ScriptSystem | 448 | m_nTodo_1C0 | `int` |
| ScriptSystem | 628 | m_nActionID | `int` |
| ScriptSystem | 632 | m_bActive | `int` |
| ScriptSystem | 636 | m_nTodo_27C | `int` |
| ScriptSystem | 680 | m_Object3D | `int` |
| ScriptSystem | 877 | m_nTodo_36D | `unsigned char` |
| ScriptSystem | 900 | m_pScriptEvent | `int` |
| ScriptSystem | 904 | m_nEventParam | `int` |
| ScriptSystem | 909 | m_bOpcodeFlag | `unsigned char` |
| ScriptSystem | 910 | m_bExecFlag | `unsigned char` |
| ScriptSystem | 911 | m_bBlockFlag | `unsigned char` |
| ScriptSystem | 1084 | m_nTodo_43C | `int` |
| ScriptSystem | 1264 | m_nActionState | `int` |
| ScriptSystem | 1268 | m_nMoveMode | `int` |
| ScriptSystem | 1284 | m_nSceneState | `int` |
| ScriptSystem | 1296 | m_vSavePos1_x | `float` |
| ScriptSystem | 1300 | m_vSavePos1_y | `float` |
| ScriptSystem | 1304 | m_vSavePos1_z | `float` |
| ScriptSystem | 1308 | m_vSrcPos_x | `float` |
| ScriptSystem | 1312 | m_vSrcPos_y | `float` |
| ScriptSystem | 1316 | m_vSrcPos_z | `float` |
| ScriptSystem | 1320 | m_vMoveDir_x | `float` |
| ScriptSystem | 1324 | m_vMoveDir_y | `float` |
| ScriptSystem | 1328 | m_vMoveDir_z | `float` |
| ScriptSystem | 1344 | m_vTargetPos | `float` |
| ScriptSystem | 1348 | m_fObjects | `float` |
| ScriptSystem | 1352 | m_fTargetDir | `float` |
| ScriptSystem | 1388 | m_nTodo_56C | `int` |
| ScriptSystem | 1468 | m_nTodo_5BC | `int` |
| ScriptSystem | 1472 | m_nTodo_5C0 | `int` |
| ScriptSystem | 1476 | m_nTodo_5C4 | `int` |
| ScriptSystem | 1480 | m_nSubObjBase | `int` |
| ScriptSystem | 8688 | m_nSaveRot_x | `float` |
| ScriptSystem | 8692 | m_nSaveRot_y | `float` |
| ScriptSystem | 8696 | m_nSaveRot_z | `float` |
| ScriptSystem | 8700 | m_nSaveDir | `int` |
| ScriptSystemData | 0 | m_mapPlayer | `SceneMapPlayer[4]` |
| ScriptSystemData | 1568 | m_scriptArray | `PtrArray` |
| ScriptSystemData | 1612 | m_nArrData_2C | `float` |
| ScriptSystemData | 1616 | m_nArrData_30 | `int` |
| ScriptSystemData | 1656 | m_nArrData | `int[20]` |
| ScriptSystemData | 2216 | m_fTimerA | `float` |
| ScriptSystemData | 2260 | m_nGameMode | `int` |
| ScriptSystemData | 2264 | m_nTodo_8D8 | `float` |
| ScriptSystemData | 2268 | m_nTodo_8DC | `float` |
| ScriptSystemData | 2272 | m_nTodo_8E0 | `float` |
| ScriptSystemData | 2276 | m_nTodo_8E4 | `float` |
| ScriptSystemData | 2280 | m_nTodo_8E8 | `float` |
| ScriptSystemData | 2284 | m_nTodo_8EC | `float` |
| ScriptSystemData | 2288 | m_nTodo_8F0 | `int` |
| ScriptSystemData | 2292 | m_nTodo_8F4 | `int` |
| ScriptSystemData | 2296 | m_nTodo_8F8 | `int` |
| ScriptSystemData | 2300 | m_nTodo_8FC | `int` |
| ScriptSystemData | 2304 | m_nTodo_900 | `int` |
| ScriptSystemData | 2312 | g_vRotateAxis | `gbVec3D` |
| ScriptSystemData | 2324 | m_bMapRenderFlags | `unsigned char` |
| ScriptSystemData | 2328 | m_nScriptCounter0 | `int` |
| ScriptSystemData | 2332 | m_nScriptCounter1 | `int` |
| ScriptSystemData | 2336 | m_nScriptFlag | `int` |
| ScriptSystemData | 2380 | m_fScriptTimer1 | `float` |
| ScriptSystemData | 2384 | m_fScriptTimer2 | `float` |
| ScriptSystemData | 2424 | m_nScriptDelay | `int` |
| ScriptSystemData | 2428 | m_fScriptSpeed | `float` |
| ScriptSystemData | 2988 | m_g_fTimeDelta | `float` |
| ScriptSystemData | 3028 | m_nTodo_D8BEEC | `RoleSystem *` |
| ScriptSystemData | 3032 | m_fTimerB | `float` |
| ScriptSystemData | 3076 | m_nVarPoolSize | `int` |
| ScriptSystemData | 3080 | m_nVarCount | `int` |
| ScriptSystemData | 3128 | m_nVarFlags | `int` |
| ScriptSystemData | 3384 | m_nArgDef_0 | `int` |
| ScriptSystemData | 3388 | m_nArgDef_1 | `int` |
| ScriptSystemData | 3396 | m_nArgDef_2 | `int` |
| ScriptSystemData | 3400 | m_nArgDef_3 | `int` |
| ScriptSystemData | 3404 | m_nArgDef_4 | `int` |
| ScriptSystemData | 3408 | m_nArgDef_5 | `int` |
| ScriptSystemData | 3412 | m_nArgDef_6 | `int` |
| ScriptSystemData | 3416 | m_nArgDef_7 | `int` |
| ScriptSystemData | 3420 | m_nArgDef_8 | `int` |
| ScriptSystemData | 3424 | m_nArgDef_9 | `int` |
| ScriptSystemData | 3428 | m_nArgDef_10 | `int` |
| ScriptSystemData | 3432 | m_nField_D68 | `signed __int16` |
| ScriptSystemData | 3436 | m_nArgDef_11 | `int` |
| ScriptSystemData | 3444 | m_nArgDef_12 | `int` |
| ScriptSystemData | 3448 | m_nArgDef_13 | `int` |
| ScriptSystemData | 3452 | m_nArgDef_14 | `int` |
| ScriptSystemData | 3456 | m_nArgDef_15 | `int` |
| ScriptSystemData | 3460 | m_nArgDef_16 | `int` |
| ScriptSystemData | 3464 | m_nField_D88 | `signed __int16` |
| ScriptSystemData | 3468 | m_nArgDef_17 | `int` |
| ScriptSystemData | 3476 | m_nArgDef_18 | `int` |
| ScriptSystemData | 3480 | m_nArgDef_19 | `int` |
| ScriptSystemData | 3484 | m_nArgDef_20 | `int` |
| ScriptSystemData | 3488 | m_nArgDef_21 | `int` |
| ScriptSystemData | 3492 | m_nArgDef_22 | `int` |
| ScriptSystemData | 3496 | m_nField_DA8 | `signed __int16` |
| ScriptSystemData | 3500 | m_nArgDef_23 | `int` |
| ScriptSystemData | 3504 | m_nArgDef_24 | `int` |
| ScriptSystemData | 3508 | m_nArgDef_25 | `int` |
| ScriptSystemData | 3512 | m_nArgDef_26 | `int` |
| ScriptSystemData | 3524 | m_nArgDef_27 | `unsigned char` |
| ScriptSystemData | 3532 | m_nArgDef_28 | `int` |
| ScriptSystemData | 3540 | m_nArgDef_29 | `int` |
| ScriptSystemData | 3544 | m_nArgDef_30 | `int` |
| ScriptSystemData | 3556 | m_nArgDef_31 | `int` |
| ScriptSystemData | 3564 | m_nArgDef_32 | `int` |
| ScriptSystemData | 3568 | m_nArgDef_33 | `int` |
| ScriptSystemData | 3684 | m_fScriptTileSize2 | `float` |
| ScriptSystemData | 3732 | m_String | `char[96]` |
| ScriptSystemData | 3828 | m_nCmdParamCount | `int` |
| ScriptSystemData | 3844 | m_nCmdIndex | `int` |
| ScriptSystemData | 3848 | m_nCmdType | `int` |
| ScriptSystemData | 3856 | m_nCmdSubType | `signed __int16` |
| ScriptSystemData | 3860 | m_nCmdParam1 | `int` |
| ScriptSystemData | 3864 | m_nCmdParam2 | `int` |
| ScriptSystemData | 3872 | m_nCmdParam3 | `signed __int16` |
| ScriptSystemData | 3876 | m_nCmdParam4 | `int` |
| ScriptSystemData | 3880 | m_nCmdParam5 | `int` |
| ScriptSystemData | 3888 | m_nCmdParam6 | `signed __int16` |
| ScriptSystemData | 3892 | m_nCmdParam7 | `int` |
| ScriptSystemData | 3904 | m_nCmdParam8 | `signed __int16` |
| ScriptSystemData | 3908 | m_nCmdParam9 | `int` |
| ScriptSystemData | 3912 | m_nCmdParam10 | `int` |
| ScriptSystemData | 3952 | m_nCmdParam11 | `signed __int16` |
| ScriptSystemData | 3960 | m_bCmdFlag1 | `unsigned char` |
| ScriptSystemData | 3968 | m_nCmdParam12 | `signed __int16` |
| ScriptSystemData | 3972 | m_nCmdParam13 | `int` |
| ScriptSystemData | 3976 | m_bCmdFlag2 | `unsigned char` |
| ScriptSystemData | 3984 | m_nCmdParam14 | `signed __int16` |
| ScriptSystemData | 3988 | m_nScriptBlockCount | `int` |
| ScriptSystemData | 3992 | m_pCurrentBlock | `PalScript *` |
| ScriptSystemData | 4000 | m_nCmdFA0 | `signed __int16` |
| ScriptSystemData | 4004 | m_nScriptState | `int` |
| ScriptSystemData | 4008 | m_nCmdFA8 | `int` |
| ScriptSystemData | 4012 | m_pScriptData | `char *` |
| ScriptSystemData | 4016 | m_nTodo_FB0 | `char[32]` |
| ScriptSystemData | 4048 | m_nCmdFD0 | `signed __int16` |
| ScriptSystemData | 4052 | m_nCmdParam19 | `int` |
| ScriptSystemData | 4056 | m_bCmdFlag4 | `unsigned char` |
| ScriptSystemData | 4064 | m_nCmdParam20 | `signed __int16` |
| ScriptSystemData | 4068 | m_nCmdParam21 | `int` |
| ScriptSystemData | 4072 | m_bCmdFlag5 | `unsigned char` |
| ScriptSystemData | 4080 | m_pCmdTableFF0 | `char *` |
| ScriptSystemData | 4084 | m_nCmdParam22 | `int` |
| ScriptSystemData | 4096 | m_nCmdParam23 | `signed __int16` |
| ScriptSystemData | 4100 | m_nTodo_1004 | `int` |
| ScriptSystemData | 4104 | m_nTodo_1008 | `int` |
| ScriptSystemData | 4108 | m_bScriptFlag | `unsigned char` |
| ScriptSystemData | 4112 | m_CmdObjArray0 | `PtrArray` |
| ScriptSystemData | 4128 | m_nCmdParam24 | `signed __int16` |
| ScriptSystemData | 4132 | m_nCmdParam25 | `int` |
| ScriptSystemData | 4136 | m_nTodo_1028 | `unsigned char` |
| ScriptSystemData | 4137 | m_bCmdFlag6 | `unsigned char` |
| ScriptSystemData | 4144 | m_nScriptMode | `int` |
| ScriptSystemData | 4148 | m_nTodo_1034 | `int` |
| ScriptSystemData | 4152 | m_bCmdFlag7 | `unsigned char` |
| ScriptSystemData | 4153 | m_bCmdFlag8 | `unsigned char` |
| ScriptSystemData | 4154 | m_bCmdFlag9 | `unsigned char` |
| ScriptSystemData | 4160 | m_nCmdParam26 | `signed __int16` |
| ScriptSystemData | 4164 | m_nCmdParam27 | `int` |
| ScriptSystemData | 4168 | m_nScriptResult | `int` |
| ScriptSystemData | 4172 | m_nTodo_104C | `char *` |
| ScriptSystemData | 4176 | m_nTodo_1050 | `signed __int16` |
| ScriptSystemData | 4180 | m_nCmdResult | `int` |
| ScriptSystemData | 4184 | m_bCmdSuccess | `unsigned char` |
| ScriptSystemData | 4185 | m_bCmdError | `unsigned char` |
| ScriptSystemData | 4192 | m_nCmdExtra1 | `signed __int16` |
| ScriptSystemData | 4196 | m_nCmdExtra2 | `int` |
| ScriptSystemData | 4200 | m_bCmdExtraFlag | `unsigned char` |
| ScriptSystemData | 4208 | m_nCmdExtra3 | `signed __int16` |
| ScriptSystemData | 4212 | m_nCmdExtra4 | `int` |
| ScriptSystemData | 4216 | m_bCmdExtraFlag2 | `unsigned char` |
| ScriptSystemData | 4224 | m_nField_1080 | `signed __int16` |
| ScriptSystemData | 4228 | m_nField_1084 | `int` |
| ScriptSystemData | 4240 | m_nField_1090 | `signed __int16` |
| ScriptSystemData | 4244 | m_nField_1094 | `int` |
| ScriptSystemData | 4256 | m_nField_10A0 | `signed __int16` |
| ScriptSystemData | 4260 | m_nField_10A4 | `int` |
| ScriptSystemData | 4264 | m_nField_10A8 | `int` |
| ScriptSystemData | 4272 | m_nField_10B0 | `signed __int16` |
| ScriptSystemData | 4276 | m_nField_10B4 | `int` |
| ScriptSystemData | 4280 | m_nField_10B8 | `unsigned char` |
| ScriptSystemData | 4288 | m_nField_10C0 | `signed __int16` |
| ScriptSystemData | 4292 | m_nField_10C4 | `int` |
| ScriptSystemData | 4296 | m_nField_10C8 | `unsigned char` |
| ScriptSystemData | 4304 | m_nField_10D0 | `signed __int16` |
| ScriptSystemData | 4308 | m_nField_10D4 | `int` |
| ScriptSystemData | 4312 | m_nField_10D8 | `int` |
| ScriptSystemData | 4320 | m_nField_10E0 | `signed __int16` |
| ScriptSystemData | 4324 | m_nField_10E4 | `int` |
| ScriptSystemData | 4328 | m_nField_10E8 | `unsigned char` |
| ScriptSystemData | 4329 | m_nField_10E9 | `unsigned char` |
| ScriptSystemData | 4336 | m_nField_10F0 | `signed __int16` |
| ScriptSystemData | 4340 | m_nField_10F4 | `int` |
| ScriptSystemData | 4344 | m_nField_10F8 | `unsigned char` |
| ScriptSystemData | 4345 | m_nField_10F9 | `unsigned char` |
| ScriptSystemData | 4352 | m_nField_1100 | `signed __int16` |
| ScriptSystemData | 4356 | m_nField_1104 | `int` |
| ScriptSystemData | 4360 | m_nField_1108 | `unsigned char` |
| ScriptSystemData | 4361 | m_nField_1109 | `unsigned char` |
| ScriptSystemData | 4362 | m_nField_110A | `unsigned char` |
| ScriptSystemData | 4368 | m_nField_1110 | `signed __int16` |
| ScriptSystemData | 4372 | m_nField_1114 | `int` |
| ScriptSystemData | 4376 | m_nField_1118 | `unsigned char` |
| ScriptSystemData | 4377 | m_nField_1119 | `unsigned char` |
| ScriptSystemData | 4378 | m_nField_111A | `unsigned char` |
| ScriptSystemData | 4379 | m_nField_111B | `unsigned char` |
| ScriptSystemData | 4380 | m_nField_111C | `int` |
| ScriptSystemData | 4384 | m_nField_1120 | `signed __int16` |
| ScriptSystemData | 4388 | m_nField_1124 | `int` |
| ScriptSystemData | 4392 | m_nField_1128 | `unsigned char` |
| ScriptSystemData | 4393 | m_nField_1129 | `unsigned char` |
| ScriptSystemData | 4394 | m_nField_112A | `unsigned char` |
| ScriptSystemData | 4408 | m_nField_1138 | `unsigned char` |
| ScriptSystemData | 4409 | m_nField_1139 | `unsigned char` |
| ScriptSystemData | 4410 | m_nField_113A | `unsigned char` |
| ScriptSystemData | 4411 | m_nField_113B | `unsigned char` |
| ScriptSystemData | 4412 | m_nField_113C | `unsigned char` |
| ScriptSystemData | 4413 | m_nField_113D | `unsigned char` |
| ScriptSystemData | 4416 | m_nField_1140 | `signed __int16` |
| ScriptSystemData | 4420 | m_nField_1144 | `int` |
| ScriptSystemData | 4424 | m_nField_1148 | `int` |
| ScriptSystemData | 4432 | m_CmdTable | `int[852]` |
| ScriptSystemData | 7840 | m_nTodo_D8D1B8 | `int` |
| ScriptSystemData | 7844 | m_nTodo_D8D1BC | `unsigned char` |
| ScriptSystemData | 7845 | m_nTodo_D8D1BD | `unsigned char` |
| ScriptSystemData | 7846 | m_nTodo_D8D1BE | `unsigned char` |
| ScriptSystemData | 7847 | m_nTodo_D8D1BF | `unsigned char` |
| ScriptSystemData | 7852 | m_nTodo_D8D1C4 | `unsigned __int16` |
| ScriptSystemData | 7856 | m_nTodo_D8D1C8 | `int` |
| ScriptSystemData | 7860 | m_nTodo_D8D1CC | `unsigned char` |
| ScriptSystemData | 7861 | m_nTodo_D8D1CD | `unsigned char` |
| ScriptSystemData | 7862 | m_nTodo_D8D1CE | `unsigned char` |
| ScriptSystemData | 7863 | m_nTodo_D8D1CF | `unsigned char` |
| ScriptSystemData | 7868 | m_nTodo_D8D1D4 | `unsigned __int16` |
| ScriptSystemData | 7968 | m_nTodo_D8D238 | `int` |
| ScriptSystemData | 7972 | m_nTodo_D8D23C | `unsigned char` |
| ScriptSystemData | 7980 | m_nTodo_D8D244 | `unsigned __int16` |
| ScriptSystemData | 8432 | m_nTodo_D8D408 | `int` |
| ScriptSystemData | 8436 | m_nTodo_D8D40C | `unsigned char` |
| ScriptSystemData | 8444 | m_nTodo_D8D414 | `unsigned __int16` |
| ScriptSystemData | 8448 | m_nTodo_D8D418 | `int` |
| ScriptSystemData | 8452 | m_nTodo_D8D41C | `unsigned char` |
| ScriptSystemData | 8460 | m_nTodo_D8D424 | `unsigned __int16` |
| ScriptSystemData | 10192 | m_nTodo_D8DAE8 | `int` |
| ScriptSystemData | 10196 | m_nTodo_D8DAEC | `unsigned char` |
| ScriptSystemData | 10197 | m_nTodo_D8DAED | `unsigned char` |
| ScriptSystemData | 10198 | m_nTodo_D8DAEE | `unsigned char` |
| ScriptSystemData | 10199 | m_nTodo_D8DAEF | `unsigned char` |
| ScriptSystemData | 10200 | m_nTodo_D8DAF0 | `unsigned char` |
| ScriptSystemData | 10201 | m_nTodo_D8DAF1 | `unsigned char` |
| ScriptSystemData | 10202 | m_nTodo_D8DAF2 | `unsigned char` |
| ScriptSystemData | 10204 | m_nTodo_D8DAF4 | `unsigned __int16` |
| ScriptVM | 4 | m_bufHead | `int` |
| ScriptVM | 8 | m_bufTail | `int` |
| ScriptVM | 12 | m_bufCapacity | `int` |
| ScriptVM | 16 | m_bufReadPtr | `int` |
| ScriptVM | 20 | m_bufWritePtr | `int` |
| ScriptVM | 32 | m_nTodo_20 | `int *` |
| ScriptVM | 160 | m_nTodo_0A0 | `int` |
| ScriptVM | 164 | m_nTodo_0A4 | `int` |
| ScriptVM | 168 | m_nTodo_0A8 | `int` |
| ScriptVM | 220 | m_nTodo_0DC | `int` |
| ScriptVM | 224 | m_nTodo_0E0 | `void *` |
| ScriptVM | 244 | m_nTodo_0F4 | `unsigned char` |
| ScriptVM | 256 | m_nPauseState | `int` |
| ScriptVM | 796 | m_pCmdList | `UIWnd *` |
| ScriptVM | 828 | m_nPathMode | `int` |
| ScriptVM | 832 | m_fPathStartX | `float` |
| ScriptVM | 836 | m_fPathStartY | `float` |
| ScriptVM | 840 | m_fPathStartZ | `float` |
| ScriptVM | 844 | m_nPathParam | `int` |
| ScriptVM | 848 | m_fPathEndX | `float` |
| ScriptVM | 852 | m_fPathEndY | `float` |
| ScriptVM | 856 | m_nTodo_358 | `char *` |
| ScriptVM | 860 | m_pPathCurrent | `char *` |
| ScriptVM | 864 | m_pPathKeys | `char *` |
| ScriptVM | 868 | m_nPathKeyCount | `int` |
| ScriptVM | 872 | m_nPathStep | `int` |
| ScriptWaitFrm | 8 | m_frm | `PAL3_FRAME` |
| SkillData | 0 | num | `int` |
| SkillData | 4 | m_Data | `char[256]` |
| SkyBox | 4 | m_fogColor | `gbColorQuad` |
| SkyBox | 8 | m_pTexture | `gbTexture *[6]` |
| SkyBox | 32 | m_vHalfSize | `gbVec3D` |
| SkyBox | 44 | m_pEffect | `gbRenderEffect *` |
| SkyBox | 48 | m_pEffectNormal | `gbRenderEffect *` |
| SkyBox | 52 | m_bValid | `BYTE` |
| SkyboxEff | 0 | m_pEffectNormal | `gbRenderEffect *` |
| SkyboxEff | 4 | m_pEffTex | `SkyboxEffTex *` |
| SkyboxEff | 8 | m_nFrameNum | `int` |
| SkyboxEff | 12 | m_fWaitTime | `float` |
| SkyboxEff | 16 | m_fValidTime | `float` |
| SkyboxEff | 20 | m_fps | `float` |
| SkyboxEff | 24 | m_fSizeScale | `float` |
| SkyboxEff | 28 | m_nEffWidth | `float` |
| SkyboxEff | 32 | m_nEffHeight | `float` |
| SkyboxEff | 36 | m_eEffMode | `EffModeParam` |
| SkyboxEff | 48 | m_vHalfSize | `gbVec3D` |
| SkyboxEff | 60 | m_fTime | `float` |
| SkyboxEff | 64 | m_fPassTime | `float` |
| SkyboxEff | 68 | m_nCurFrame | `int` |
| SkyboxEff | 72 | m_fWidth | `float` |
| SkyboxEff | 76 | m_fHeight | `float` |
| SkyboxEff | 80 | m_bIsTime | `BYTE` |
| SkyboxEff | 81 | m_bOver | `BYTE` |
| SkyboxEff | 82 | m_bValid | `BYTE` |
| SkyboxEff | 83 | m_bDelyTime | `BYTE` |
| SkyboxEff | 84 | m_fNoteTime | `float` |
| SkyboxEff | 88 | m_nameCrc | `unsigned int` |
| SkyboxEff | 92 | m_pSkyboxEff | `gbRenderEffect *` |
| SkyboxEff | 96 | m_vRender | `gbVec3D[4]` |
| SkyboxEffMgr | 0 | m_fSkyboxSize | `float` |
| SkyboxEffMgr | 4 | m_pEffArray | `char[256]` |
| SkyboxEffTex | 0 | m_pTex | `gbTexture *` |
| SoundAttachObj | 0 | p2d | `gbSound2DNode *` |
| SoundAttachObj | 4 | h2d | `_SAMPLE *` |
| SoundAttachObj | 8 | time | `unsigned int` |
| SoundItem | 0 | dwCRC | `unsigned int` |
| SoundItem | 4 | node2 | `gbSound2DNode *` |
| SoundMgr | 4 | m_bScriptMusic | `BYTE` |
| SoundMgr | 8 | m_szScriptMusic | `char[16]` |
| SoundMgr | 24 | m_nScriptLoop | `int` |
| SoundMgr | 28 | m_szSceneMusic | `char[256]` |
| SoundMgr | 284 | m_MusicTable | `TxtFile` |
| SoundMgr | 808 | m_audiodrv | `gbAudioManager *` |
| SoundMgr | 812 | DEF3DMasterVol | `int` |
| SoundMgr | 816 | DEF2DMasterVol | `int` |
| SoundMgr | 820 | DEFMusicMasterVol | `float` |
| SoundMgr | 824 | m_bValidDetectSceneMusic | `BYTE` |
| SoundMgr | 828 | m_cbbuf | `char[16]` |
| SoundMgr | 844 | m_cbcursor | `int` |
| SoundMgr | 848 | m_Cpk | `CPK` |
| StateUI | 72 | m_isJusticeBook | `unsigned char` |
| StateUI | 280 | m_IsMsg | `unsigned char` |
| StateUI | 281 | m_Is | `_BYTE[5]` |
| StateUI | 288 | m_CtrlRole | `int` |
| StateUI | 292 | m_IsActive | `unsigned char` |
| StateUI | 293 | m_IsCreateable | `unsigned char` |
| StateUI | 296 | m_Frame | `UIStatic` |
| StateUI | 448 | m_TimeMoney | `UIStatic` |
| StateUI | 600 | m_OutFrameT | `UIStatic` |
| StateUI | 752 | m_OutFrameR | `UIStatic` |
| StateUI | 904 | m_OutFrameL | `UIStatic` |
| StateUI | 1056 | m_OutFrameB | `UIStatic` |
| StateUI | 1208 | stp_BarL | `UIStatic` |
| StateUI | 1360 | stp_BarM | `UIFlexBar` |
| StateUI | 1444 | stp_BarR | `UIStatic` |
| StateUI | 1596 | stp_State | `UIButton` |
| StateUI | 1940 | stp_Magic | `UIButton` |
| StateUI | 2284 | stp_Equip | `UIButton` |
| StateUI | 2628 | stp_Prop | `UIButton` |
| StateUI | 2972 | stp_BattleArray | `UIButton` |
| StateUI | 3316 | stp_TaskBook | `UIButton` |
| StateUI | 3660 | stp_System | `UIButton` |
| StateUI | 4004 | stp_Exit | `UIButton` |
| StateUI | 4348 | stp_Effect | `UIStatic` |
| StateUI | 4500 | stp_Rect | `tagRECT` |
| StateUI | 4516 | m_GameTime | `UIStatic` |
| StateUI | 4668 | m_GameMoney | `UIStatic` |
| StateUI | 4820 | m_par | `UIParticle[16][7]` |
| StateUI | 71124 | m_par2 | `UIParticle[16][7]` |
| StateUI | 137428 | m_parRc | `tagRECT[7]` |
| StateUI | 137540 | _isParBtn | `_BYTE[7]` |
| StateUI | 137548 | _curParEffect | `int` |
| StateUI | 137552 | m_PortraitRc | `tagRECT` |
| StateUI | 137568 | m_Portrait | `UIStatic` |
| StateUI | 137720 | m_TeamState | `UIStatic` |
| StateUI | 137872 | m_Time | `UIStatic` |
| StateUI | 138024 | m_Money | `UIStatic` |
| StateUI | 138176 | m_TeamStateRc | `tagRECT` |
| StateUI | 138192 | m_RoleState | `s_RoleState[5]` |
| StateUI | 157932 | m_State | `UIStatic[4]` |
| StateUI | 158540 | m_Alignment | `UIStatic` |
| StateUI | 158692 | m_AlignmentRc | `tagRECT` |
| StateUI | 158708 | m_Head | `UIStatic[5]` |
| StateUI | 159468 | m_HeadRc | `tagRECT[5]` |
| StateUI | 159548 | m_TopFrame | `UIStatic` |
| StateUI | 159700 | m_LeaveHere | `UIButton` |
| StateUI | 160044 | m_LeaveRc | `tagRECT` |
| StateUI | 160060 | m_3DObj | `UI3DCtrl` |
| StateUI | 160368 | m_DlgEx | `MUIDialog` |
| StateUI | 161752 | p_LineupUI | `LineupUI *` |
| StateUI | 161756 | p_MagicUI | `MagicUI *` |
| StateUI | 161760 | p_mEquipUI | `MainEquipUI *` |
| StateUI | 161764 | p_mPropUI | `MainPropUI *` |
| StateUI | 161768 | p_SwordUI | `SwordUI *` |
| StateUI | 161772 | p_JusticeBookUI | `JusticeBookUI *` |
| StateUI | 161776 | p_TaskBookUI | `TaskBookUI *` |
| StateUI | 161780 | p_SystemUI | `SystemUI *` |
| StateUI | 161784 | m_curRender | `int` |
| StateUI | 161788 | m_saveflag_note | `unsigned char` |
| StateUI | 161789 | m_isSeekSAVELOAD | `unsigned char` |
| StateUI | 161792 | m_test | `UIStatic` |
| StateUI | 161944 | pInterceptTex | `gbTexture *` |
| StateUI | 161948 | sv | `float` |
| StateUI | 161952 | ev | `float` |
| StateUI | 161956 | m_isExit | `unsigned char` |
| StateUI | 161960 | m_SpecialPropItem | `s_SpecialPropItem[5]` |
| StringTable | 0 | m_data | `char[16]` |
| SwitchVariable | 0 | m_switchlimit | `unsigned int` |
| SwordUI | 72 | m_PurgeNum | `WuLing` |
| SwordUI | 88 | m_nBkWndX | `int` |
| SwordUI | 92 | m_nBkWndY | `int` |
| SwordUI | 96 | m_nSwordIdx | `int` |
| SwordUI | 100 | m_nSwordIdx2 | `int` |
| SwordUI | 104 | m_szSwordBuf | `char[64]` |
| SwordUI | 360 | m_ljsNum | `int` |
| SwordUI | 364 | m_ljsNumber | `UIStatic` |
| SwordUI | 524 | m_purgeEquipNum | `int` |
| SwordUI | 528 | m_purgeWeaponNum | `int` |
| SwordUI | 532 | m_avgWeaponWU | `int` |
| SwordUI | 536 | m_avgAdornWU | `int` |
| SwordUI | 540 | m_avgAdornFANG | `int` |
| SwordUI | 544 | m_avgDefFANG | `int` |
| SwordUI | 548 | m_adornNum | `int` |
| SwordUI | 552 | m_defNum | `int` |
| SwordUI | 556 | m_WSkill | `FightSkill[28]` |
| SwordUI | 21836 | m_wskillNum | `int` |
| SwordUI | 21840 | m_IsMsg | `unsigned char` |
| SwordUI | 21844 | m_CtrlRole | `int` |
| SwordUI | 21848 | m_IsActive | `unsigned char` |
| SwordUI | 21849 | m_IsCreateable | `unsigned char` |
| SwordUI | 21850 | m_IsLunar | `unsigned char` |
| SwordUI | 21851 | m_is3dLunar | `unsigned char` |
| SwordUI | 21852 | m_SelNum | `int` |
| SwordUI | 21856 | m_CurPage | `int` |
| SwordUI | 21860 | m_angle | `float` |
| SwordUI | 21864 | rot | `float` |
| SwordUI | 21868 | m_Distribute | `S_Distribute[99]` |
| SwordUI | 23452 | FetchVal | `int` |
| SwordUI | 23456 | GuVal | `int` |
| SwordUI | 23460 | pStateUI | `StateUI *` |
| SwordUI | 23464 | m_FrameLine | `UIStatic` |
| SwordUI | 23624 | m_TimeMoney | `UIStatic` |
| SwordUI | 23784 | stp_BarL | `UIStatic` |
| SwordUI | 23944 | stp_BarM | `UIStatic` |
| SwordUI | 24104 | stp_BarR | `UIStatic` |
| SwordUI | 24264 | stp_State | `UIButton` |
| SwordUI | 24608 | stp_Magic | `UIButton` |
| SwordUI | 24952 | stp_Equip | `UIButton` |
| SwordUI | 25296 | stp_Prop | `UIButton` |
| SwordUI | 25640 | stp_BattleArray | `UIButton` |
| SwordUI | 25984 | stp_System | `UIButton` |
| SwordUI | 26328 | stp_Exit | `UIButton` |
| SwordUI | 26672 | stp_Effect | `UIStatic` |
| SwordUI | 26832 | stp_Rect | `tagRECT` |
| SwordUI | 26848 | m_GameTime | `UIStatic` |
| SwordUI | 27008 | m_GameMoney | `UIStatic` |
| SwordUI | 27168 | m_btnPar | `UIParticle[16][7]` |
| SwordUI | 93472 | m_btnPar2 | `UIParticle[16][7]` |
| SwordUI | 159776 | m_btnParRc | `tagRECT[7]` |
| SwordUI | 159888 | _isParBtn | `_BYTE[7]` |
| SwordUI | 159896 | _curParEffect | `int` |
| SwordUI | 159900 | Sword_Name | `UIStatic` |
| SwordUI | 160060 | Sword_Att | `UIStatic` |
| SwordUI | 160220 | m_Ljs | `UIStatic` |
| SwordUI | 160380 | m_WulingCtrl | `UIStatic` |
| SwordUI | 160540 | m_Sword | `UI3DCtrl` |
| SwordUI | 160848 | m_ljs3D | `UI3DCtrl` |
| SwordUI | 161156 | m_SwordFrame | `UIStatic` |
| SwordUI | 161316 | m_SwordRemarkBk | `UIStatic` |
| SwordUI | 161476 | m_SwordRemark | `UIStatic` |
| SwordUI | 161636 | m_Yjfx | `UIButton` |
| SwordUI | 161980 | m_RemarkRc | `tagRECT` |
| SwordUI | 161996 | m_SwordRemarkRc | `tagRECT` |
| SwordUI | 162012 | m_NoteSwordRemarkRc | `tagRECT` |
| SwordUI | 162028 | m_SwordDstX | `unsigned __int16` |
| SwordUI | 162030 | m_SwordNoteX | `unsigned __int16` |
| SwordUI | 162032 | m_bSwordRemarkOut | `int` |
| SwordUI | 162036 | mb_Positive | `UIButton[5]` |
| SwordUI | 163756 | ms_Positive | `UIStatic[5]` |
| SwordUI | 164556 | mb_Lunar | `UIButton[5]` |
| SwordUI | 166276 | ms_Lunar | `UIStatic[5]` |
| SwordUI | 167076 | ms_Perfect | `UIStatic[5]` |
| SwordUI | 167876 | m_CanCtrlBtn | `unsigned char` |
| SwordUI | 167880 | mb_Test | `UIButton` |
| SwordUI | 168224 | m_parSword | `UIParticle[168]` |
| SwordUI | 267680 | m_parSwordRc | `tagRECT` |
| SwordUI | 267696 | m_parPurge | `UIParticle[168]` |
| SwordUI | 367152 | m_PositiveBtn | `UIButton` |
| SwordUI | 367496 | m_LunarBtn | `UIButton` |
| SwordUI | 367840 | Purge_rectA | `tagRECT[5]` |
| SwordUI | 367920 | Purge_rectB | `tagRECT[5]` |
| SwordUI | 368000 | dstRect | `tagRECT[5]` |
| SwordUI | 368080 | m_PurgeEffect | `PurgeEffect` |
| SwordUI | 368508 | m_effTime | `TimeCtl` |
| SwordUI | 368520 | m_bSwordMotion | `unsigned char` |
| SwordUI | 368521 | m_bSwordEff | `unsigned char` |
| SwordUI | 368522 | m_bSwordRot | `unsigned char` |
| SwordUI | 368523 | m_bEff | `unsigned char` |
| SwordUI | 368524 | m_curpar | `int` |
| SwordUI | 368528 | m_swdTime | `TimeCtl` |
| SwordUI | 368540 | m_Orthosize | `int` |
| SwordUI | 368544 | m_FinalOrthosize | `int` |
| SwordUI | 368548 | m_PURGEINFO | `_PURGE_INFO[11]` |
| SwordUI | 368636 | m_SmallBar | `UIFlexBar` |
| SwordUI | 368720 | m_BigBar | `UIFlexBar` |
| SwordUI | 368804 | m_Pushbtn | `UIButton[5]` |
| SwordUI | 370524 | m_equipFlag | `UIStatic` |
| SwordUI | 370684 | m_purgeFlag | `UIStatic` |
| SwordUI | 370844 | m_ListTitle | `UIFlexBar` |
| SwordUI | 370928 | m_EquipTitle | `UIStatic` |
| SwordUI | 371088 | m_PurgeTitle | `UIStatic` |
| SwordUI | 371248 | m_ListTitlePurge | `UIStatic` |
| SwordUI | 371408 | m_ListFrame | `UIStatic` |
| SwordUI | 371568 | m_ListFramePurge | `UIStatic` |
| SwordUI | 371728 | m_ListGrid | `UIStatic[12]` |
| SwordUI | 373648 | m_ListGridPurge | `UIStatic[12]` |
| SwordUI | 375568 | m_WeaponList | `UIListBox` |
| SwordUI | 376856 | m_ClothList | `UIListBox` |
| SwordUI | 378144 | m_HatList | `UIListBox` |
| SwordUI | 379432 | m_ShoesList | `UIListBox` |
| SwordUI | 380720 | m_AdornList | `UIListBox` |
| SwordUI | 382008 | m_StuffList | `UIListBox` |
| SwordUI | 383296 | m_StrRc | `tagRECT` |
| SwordUI | 383312 | m_EquipStr | `UIStatic` |
| SwordUI | 383472 | m_StuffStr | `UIStatic` |
| SwordUI | 383632 | m_GuVal | `UIStatic` |
| SwordUI | 383792 | m_MsgRc | `tagRECT` |
| SwordUI | 383808 | m_PurgeMsg | `UIStatic` |
| SwordUI | 383968 | m_PurgeBottom | `UIFlexBar` |
| SwordUI | 384052 | m_BtnRc | `tagRECT` |
| SwordUI | 384068 | m_OK | `UIButton` |
| SwordUI | 384412 | m_Cancel | `UIButton` |
| SwordUI | 384756 | m_SortEquipbyPrice | `UIButton` |
| SwordUI | 385100 | m_SortEquipbyGu | `UIButton` |
| SwordUI | 385444 | m_SortStuffbyPrice | `UIButton` |
| SwordUI | 385788 | m_SortStuffbyGu | `UIButton` |
| SwordUI | 386132 | m_SortState | `int` |
| SwordUI | 386136 | m_ItemArray | `Inventory` |
| SwordUI | 386176 | m_Dlg | `MUIDialog` |
| SwordUI | 387560 | m_Msg | `MUIDialog` |
| SwordUI | 388944 | note_purgenum | `WuLing` |
| SwordUI | 388948 | m_bHasWeapon | `unsigned char` |
| SystemUI | 72 | m_rcLayout | `tagRECT` |
| SystemUI | 88 | m_nBkWndX | `int` |
| SystemUI | 92 | m_nBkWndY | `int` |
| SystemUI | 96 | m_nNoteIdx | `int` |
| SystemUI | 100 | m_nReserved64 | `int` |
| SystemUI | 104 | m_szTimeBuf | `char[64]` |
| SystemUI | 172 | m_nFieldAC | `int` |
| SystemUI | 176 | m_nFieldB0 | `int` |
| SystemUI | 180 | m_NoteArray | `void *` |
| SystemUI | 360 | m_IsMsg | `unsigned char` |
| SystemUI | 364 | pStateUI | `StateUI *` |
| SystemUI | 368 | m_Frame | `UIStatic` |
| SystemUI | 528 | m_TimeMoney | `UIStatic` |
| SystemUI | 688 | m_OutFrameT | `UIStatic` |
| SystemUI | 848 | m_OutFrameR | `UIStatic` |
| SystemUI | 1008 | m_OutFrameL | `UIStatic` |
| SystemUI | 1168 | m_OutFrameB | `UIStatic` |
| SystemUI | 1328 | stp_BarL | `UIStatic` |
| SystemUI | 1488 | stp_BarM | `UIFlexBar` |
| SystemUI | 1572 | stp_BarR | `UIStatic` |
| SystemUI | 1732 | stp_State | `UIButton` |
| SystemUI | 2076 | stp_Magic | `UIButton` |
| SystemUI | 2420 | stp_Equip | `UIButton` |
| SystemUI | 2764 | stp_Prop | `UIButton` |
| SystemUI | 3108 | stp_BattleArray | `UIButton` |
| SystemUI | 3452 | stp_TaskBook | `UIButton` |
| SystemUI | 3796 | stp_System | `UIButton` |
| SystemUI | 4140 | stp_Exit | `UIButton` |
| SystemUI | 4484 | stp_Effect | `UIStatic` |
| SystemUI | 4644 | stp_Rect | `tagRECT` |
| SystemUI | 4660 | m_GameTime | `UIStatic` |
| SystemUI | 4820 | m_GameMoney | `UIStatic` |
| SystemUI | 4980 | m_par | `UIParticle[16][7]` |
| SystemUI | 71284 | m_par2 | `UIParticle[16][7]` |
| SystemUI | 137588 | m_parRc | `tagRECT[7]` |
| SystemUI | 137700 | _isParBtn | `_BYTE[7]` |
| SystemUI | 137708 | _curParEffect | `int` |
| SystemUI | 137712 | m_TopBar | `UIStatic` |
| SystemUI | 137872 | m_BottomBar | `UIStatic` |
| SystemUI | 138032 | m_ExitGame | `UIButton` |
| SystemUI | 138376 | m_SaveBtn | `UIButton` |
| SystemUI | 138720 | m_LoadBtn | `UIButton` |
| SystemUI | 139064 | m_DeleteBtn | `UIButton` |
| SystemUI | 139408 | m_pbPage | `UIPushButton[10]` |
| SystemUI | 141928 | m_isItemShow | `_BYTE[99]` |
| SystemUI | 142028 | m_NoteItem | `Note_Item[99]` |
| SystemUI | 511100 | m_Scroll | `UIScrollBar` |
| SystemUI | 511468 | m_CurScrollPos | `int` |
| SystemUI | 511472 | m_BackBar | `UIStatic` |
| SystemUI | 511632 | m_BackBar2 | `UIStatic` |
| SystemUI | 511792 | m_MusicBar | `UIDragBar` |
| SystemUI | 512064 | m_MusicEffectBar | `UIDragBar` |
| SystemUI | 512336 | m_MusicText | `UIStatic` |
| SystemUI | 512496 | m_MusicEffectText | `UIStatic` |
| SystemUI | 512656 | m_ItemH | `int` |
| SystemUI | 512660 | m_ItemW | `int` |
| SystemUI | 512664 | m_firstItem | `int` |
| SystemUI | 512668 | m_selItem | `int` |
| SystemUI | 512672 | m_getNote | `int` |
| SystemUI | 512676 | m_noteState | `NOTE_STATE` |
| SystemUI | 512680 | m_loading | `int` |
| SystemUI | 512684 | m_passtime | `float` |
| SystemUI | 512688 | m_isExit | `unsigned char` |
| SystemUI | 512692 | m_MsgBox | `MUIDialog` |
| TaskBookUI | 72 | rc | `tagRECT` |
| TaskBookUI | 88 | bkWndX | `int` |
| TaskBookUI | 92 | bkWndY | `int` |
| TaskBookUI | 96 | m_IsCreateable | `unsigned char` |
| TaskBookUI | 97 | m_IsActive | `unsigned char` |
| TaskBookUI | 100 | pStateUI | `StateUI *` |
| TaskBookUI | 104 | m_OutFrameT | `UIStatic` |
| TaskBookUI | 264 | m_OutFrameR | `UIStatic` |
| TaskBookUI | 424 | m_OutFrameL | `UIStatic` |
| TaskBookUI | 584 | m_OutFrameB | `UIStatic` |
| TaskBookUI | 744 | stp_BarL | `UIStatic` |
| TaskBookUI | 904 | stp_BarM | `UIFlexBar` |
| TaskBookUI | 988 | stp_BarR | `UIStatic` |
| TaskBookUI | 1148 | stp_State | `UIButton` |
| TaskBookUI | 1492 | stp_Magic | `UIButton` |
| TaskBookUI | 1836 | stp_Equip | `UIButton` |
| TaskBookUI | 2180 | stp_Prop | `UIButton` |
| TaskBookUI | 2524 | stp_BattleArray | `UIButton` |
| TaskBookUI | 2868 | stp_TaskBook | `UIButton` |
| TaskBookUI | 3212 | stp_System | `UIButton` |
| TaskBookUI | 3556 | stp_Exit | `UIButton` |
| TaskBookUI | 3900 | stp_Effect | `UIStatic` |
| TaskBookUI | 4060 | stp_Rect | `tagRECT` |
| TaskBookUI | 4076 | m_DlgEx | `MUIDialog` |
| TaskBookUI | 5460 | m_btnPar | `UIParticle[16][7]` |
| TaskBookUI | 71764 | m_btnPar2 | `UIParticle[16][7]` |
| TaskBookUI | 138068 | m_btnParRc | `tagRECT[7]` |
| TaskBookUI | 138180 | _isParBtn | `_BYTE[7]` |
| TaskBookUI | 138188 | _curParEffect | `int` |
| TaskBookUI | 138192 | m_ListBK | `UIStatic` |
| TaskBookUI | 138352 | m_ListTitle | `UIStatic` |
| TaskBookUI | 138512 | m_ListBtn | `UIButton[9]` |
| TaskBookUI | 141608 | m_ListBtnBkL | `UIStatic` |
| TaskBookUI | 141768 | m_ListBtnBkR | `UIStatic` |
| TaskBookUI | 141928 | m_Scroll | `UIScrollBar` |
| TaskBookUI | 142296 | m_IsScroll | `int` |
| TaskBookUI | 142300 | m_ScrollHB | `UIStatic` |
| TaskBookUI | 142460 | m_TaskBk | `UIStatic` |
| TaskBookUI | 142620 | m_TaskPicBk | `UIStatic` |
| TaskBookUI | 142780 | m_TaskPic | `UIStatic` |
| TaskBookUI | 142940 | m_TaskDesc | `UIStatic` |
| TaskBookUI | 143100 | m_TaskTitle | `UIStatic` |
| TaskBookUI | 143260 | m_TaskState | `UIStatic` |
| TaskBookUI | 143420 | m_SelItem | `int` |
| TaskBookUI | 143424 | m_FirstItem | `int` |
| TaskBookUI | 143428 | m_TotalItem | `int` |
| TaskMgr | 4 | m_fCurTime | `float` |
| TaskMgr | 8 | m_fDeltaTime | `float` |
| TaskMgr | 12 | m_pTask | `char *` |
| TaskMgr | 16 | m_nCurTask | `int` |
| TaskMgr | 20 | m_nCurSubTask | `int` |
| TaskMgr | 24 | m_nTask | `int` |
| TaskMgr | 28 | m_nMaxTask | `int` |
| TaskMgr | 32 | m_nMaxSubTask | `int` |
| TaskMgr_SceneObjParam_SceneObj | 0 | m_nTodo_000 | `void *` |
| TextureLib | 0 | m_pResultTex | `gbTexture *` |
| TextureLib | 12 | m_szPathBuf | `int` |
| TextureLib | 32 | m_nTextureId | `int` |
| TextureLib | 36 | m_szPath | `int` |
| TextureLib | 48 | m_fTexCoordU | `float` |
| TextureLib | 52 | m_fTexCoordV | `float` |
| TextureLib | 60 | m_fTexScale | `float` |
| TextureLib | 64 | m_bTexFilter | `unsigned char` |
| TextureLib | 68 | m_nTexParam1 | `int` |
| TextureLib | 72 | m_nTexParam2 | `int` |
| TextureLib | 76 | m_nTexParam3 | `int` |
| TextureLib | 80 | m_bTexClamp | `unsigned char` |
| TextureLib | 127 | m_bMipMap | `unsigned char` |
| TextureLib | 128 | m_bAlphaChannel | `unsigned char` |
| TextureLib | 132 | m_fTexParam | `float` |
| TextureLib | 136 | m_fAngle | `float` |
| TextureLib | 140 | m_fColorModR | `float` |
| TextureLib | 144 | m_fColorModG | `float` |
| TextureLib | 148 | m_fColorModB | `float` |
| TextureLib | 152 | m_fColorModA | `float` |
| TextureLib | 156 | m_fColorAdd | `float` |
| TextureLib | 184 | m_nTexWidth | `int` |
| TextureLib | 188 | m_nTexHeight | `int` |
| TextureLib | 204 | m_Image | `char[48]` |
| TextureLib | 252 | m_nImageOffset | `int` |
| TextureLib | 256 | m_nImageSize | `int` |
| TextureLib | 304 | m_nColorKey | `int` |
| TextureLib | 332 | m_nStride | `int` |
| TextureLib | 336 | m_nDataSize | `int` |
| TextureLib | 344 | m_nTexFormat | `int` |
| TextureLib | 384 | m_nBPP | `int` |
| TextureLib | 388 | m_nDataOffset | `int` |
| TextureLib | 408 | m_pPalette | `void *` |
| TextureLib | 412 | m_nDataStart | `int` |
| TextureLib | 416 | m_nDataEnd | `int` |
| TextureLib | 424 | m_bLoaded | `unsigned char` |
| TextureLib | 460 | m_nPaletteSize | `int` |
| TextureLib | 488 | m_nTexFlags | `int` |
| TextureLib | 524 | m_szText | `int` |
| TextureLib | 528 | m_pTexture | `char *` |
| TextureLibDataBase | 4 | Seps | `char *` |
| TextureLibDataBase | 8 | tok | `char *` |
| TextureLibDataBase | 12 | _libfolder | `char[512]` |
| TextureLibDataBase | 524 | _realNum | `int` |
| TextureLibDataBase | 528 | m_pData | `_Texture_Info *` |
| TextureLibDataBase | 532 | _isLoadTLI | `BYTE` |
| TextureLibDataBase | 580 | m_fScrollSpeed | `float` |
| ThrowInfo | 0 | attributes | `unsigned int` |
| ThrowInfo | 4 | pmfnUnwind | `PMFN` |
| ThrowInfo | 12 | pCatchableTypeArray | `CatchableTypeArray *` |
| TimeCtl | 0 | newtick | `unsigned int` |
| TimeCtl | 4 | oldtick | `unsigned int` |
| TimeCtl | 8 | bNote | `BYTE` |
| Triangle | 0 | vert | `gbVec3D[3]` |
| Triangle | 36 | normal | `gbVec3D` |
| TryBlockMapEntry | 0 | tryLow | `int` |
| TryBlockMapEntry | 4 | tryHigh | `int` |
| TryBlockMapEntry | 8 | catchHigh | `int` |
| TryBlockMapEntry | 12 | nCatches | `int` |
| TryBlockMapEntry | 16 | pHandlerArray | `char *` |
| TxtFile | 0 | m_token | `char[512]` |
| TxtFile | 512 | m_buf | `char *` |
| TxtFile | 516 | m_sectionstart | `char *` |
| TxtFile | 520 | m_curpos | `char *` |
| UI3DCtrl | 68 | m_numobj | `int` |
| UI3DCtrl | 72 | m_obj | `UI3DObj[5]` |
| UI3DCtrl | 232 | m_orthosize | `float` |
| UI3DCtrl | 236 | m_rotatemode | `int` |
| UI3DCtrl | 240 | m_isrotateto | `unsigned char` |
| UI3DCtrl | 244 | m_speed | `int` |
| UI3DCtrl | 248 | m_rotate | `float` |
| UI3DCtrl | 252 | m_rotatetarget | `float` |
| UI3DCtrl | 256 | m_rotx | `float` |
| UI3DCtrl | 260 | m_rotz | `float` |
| UI3DCtrl | 264 | m_dropx | `float` |
| UI3DCtrl | 268 | m_dropy | `float` |
| UI3DCtrl | 272 | m_dropz | `float` |
| UI3DCtrl | 276 | m_scalex | `float` |
| UI3DCtrl | 280 | m_scaley | `float` |
| UI3DCtrl | 284 | m_scalez | `float` |
| UI3DCtrl | 288 | m_lightobj | `gbLightObj *` |
| UI3DCtrl | 292 | m_camera | `gbCamera *` |
| UI3DCtrl | 296 | m_raydir | `gbVec3D` |
| UI3DModelNode | 92 | m_nTodo_05C | `int` |
| UI3DModelNode | 96 | m_nTodo_060 | `int` |
| UI3DModelNode | 100 | m_nTodo_064 | `int` |
| UI3DModelNode | 104 | m_nTodo_068 | `int[16]` |
| UI3DModelNode | 232 | m_nTodo_0E8 | `int` |
| UI3DModelNode | 236 | m_nTodo_0EC | `int` |
| UI3DModelNode | 240 | m_nTodo_0F0 | `int` |
| UI3DModelNode | 244 | m_nTodo_0F4 | `int` |
| UI3DObj | 0 | m_mouseoff | `BYTE` |
| UI3DObj | 4 | m_enable | `int` |
| UI3DObj | 8 | m_needdel | `int` |
| UI3DObj | 12 | m_type | `int` |
| UI3DObj | 16 | m_actor | `Actor *` |
| UI3DObj | 20 | m_pos | `gbVec3D` |
| UIAnimate | 0 | m_sec | `unsigned int` |
| UIAnimate | 4 | m_Rc | `tagRECT` |
| UIAnimate | 20 | m_Rc2 | `tagRECT` |
| UIAnimate | 36 | m_IsLoop | `_BYTE[4]` |
| UIAnimate | 40 | m_Time | `TimeCtl` |
| UIAnimateCtrl | 68 | m_FPS | `float` |
| UIAnimateCtrl | 72 | m_passtime | `float` |
| UIAnimateCtrl | 76 | m_texarray | `UITextureArray` |
| UIAnimateCtrl | 144 | m_curframe | `int` |
| UIAnimateCtrl | 148 | m_numframe | `int` |
| UIAnimateCtrl | 152 | m_looppassed | `int` |
| UIAnimateCtrl | 156 | m_nLoop | `int` |
| UIAnimateCtrl | 160 | m_mode | `int` |
| UIAnimateCtrlEX | 68 | m_Scene | `UIScene` |
| UIAnimateCtrlEX | 412 | m_Frame | `UIStatic` |
| UIAnimateCtrlEX | 564 | m_ResultWnd | `CCBResultWindow` |
| UIAnimateCtrlEX | 748 | m_TextArea | `UITextArea` |
| UIAnimateCtrlEX | 940 | m_ChildWnd | `UIWnd` |
| UIAnimateCtrlEX | 1008 | m_bAnimFlag | `unsigned char` |
| UIBigMap | 72 | screenrect | `tagRECT` |
| UIBigMap | 88 | bkWndX | `int` |
| UIBigMap | 92 | bkWndY | `int` |
| UIBigMap | 96 | i | `int` |
| UIBigMap | 100 | j | `int` |
| UIBigMap | 104 | buf | `char[256]` |
| UIBigMap | 360 | ms_BigMap | `UIStatic` |
| UIBigMap | 520 | m_Element | `_MapElement[16]` |
| UIBigMap | 6792 | m_spiritRect | `tagRECT` |
| UIBigMap | 6808 | m_spirit | `UIAnimateCtrl` |
| UIBigMap | 6972 | m_spiritPosX | `float` |
| UIBigMap | 6976 | m_spiritPosY | `float` |
| UIBigMap | 6980 | m_spiritPos | `tagPOINT` |
| UIBigMap | 6988 | m_movetopos | `tagPOINT` |
| UIBigMap | 6996 | m_movetoX | `float` |
| UIBigMap | 7000 | m_movetoY | `float` |
| UIBigMap | 7004 | m_spiritspeed | `int` |
| UIBigMap | 7008 | m_speedFX | `float` |
| UIBigMap | 7012 | m_speedFY | `float` |
| UIBigMap | 7016 | m_bSpiritCanMove | `unsigned char` |
| UIBigMap | 7017 | m_isSpiritMoveTo | `unsigned char` |
| UIBigMap | 7020 | m_timescale | `float` |
| UIBigMap | 7024 | m_stopdir | `int` |
| UIBigMap | 7028 | m_curElement | `_BIGMAP_ELEMENT` |
| UIBigMap | 7032 | m_Answer | `MUIDialog` |
| UIButton | 68 | m_hasDBclk | `unsigned char` |
| UIButton | 72 | m_ratiow | `float` |
| UIButton | 76 | m_state | `UIButton_UIBUTTON_STATE` |
| UIButton | 80 | m_canctrl | `BYTE` |
| UIButton | 81 | m_bLockUpdate | `BYTE` |
| UIButton | 84 | m_offsetx | `int` |
| UIButton | 88 | m_offsety | `float` |
| UIButton | 92 | m_bBigFont | `BYTE` |
| UIButton | 96 | m_texarray | `UITextureArray` |
| UIButton | 164 | m_texarrayInfo | `_PlugInfo *[3]` |
| UIButton | 176 | m_disablepic | `gbTexture *` |
| UIButton | 180 | m_disablepicInfo | `_PlugInfo *` |
| UIButton | 184 | m_mouseoff | `BYTE` |
| UIButton | 185 | m_mouseon | `BYTE` |
| UIButton | 188 | m_alignmode | `int` |
| UIButton | 192 | m_caption | `char[128]` |
| UIButton | 320 | m_benable_snd | `BYTE` |
| UIButtonEX | 344 | m_optData | `_btnOPTDATA[3]` |
| UIButtonEXA | 344 | m_optData | `_btnOPTDATA` |
| UIButtonEXA | 360 | m_EnableMode | `int` |
| UIButtonEXA | 364 | m_color | `gbColorQuad` |
| UIButtonEXA | 368 | m_enablecolor | `gbColorQuad` |
| UIButtonEXA | 372 | m_surecolor | `gbColorQuad` |
| UICamera | 128 | m_nCamState | `int` |
| UICamera | 152 | m_nViewMode | `int` |
| UICamera | 160 | m_fCamAngle | `float` |
| UICamera | 164 | m_fCoordU | `float` |
| UICamera | 168 | m_fCoordV | `float` |
| UICamera | 220 | m_nBuffer | `int` |
| UICamera | 224 | m_hTarget | `int` |
| UICamera | 272 | m_pCameraData | `int` |
| UICamera | 460 | m_nStateFlags | `int` |
| UICamera | 464 | m_nParam | `int` |
| UICamera | 492 | m_fVecX | `float` |
| UICamera | 496 | m_fVecY | `float` |
| UICamera | 500 | m_fVecZ | `float` |
| UICamera | 628 | m_hCameraHandle | `int` |
| UICamera | 632 | m_nTodo_278 | `int` |
| UICaption | 76 | m_tex | `gbTexture *` |
| UICaption | 80 | m_numline | `int` |
| UICaption | 84 | m_lineheight | `int` |
| UICaption | 88 | m_curline | `int` |
| UICaption | 92 | m_linetime | `float` |
| UIChatRest | 68 | m_pt | `int` |
| UIChatRest | 72 | bkrc | `tagRECT` |
| UIChatRest | 88 | m_startX | `int` |
| UIChatRest | 92 | m_startY | `int` |
| UIChatRest | 96 | mbWidth | `int` |
| UIChatRest | 100 | mbHeight | `int` |
| UIChatRest | 104 | m_FlagT | `UIStatic` |
| UIChatRest | 256 | m_FlagB | `UIStatic` |
| UIChatRest | 408 | m_FlagM | `UIStatic[3]` |
| UIChatRest | 864 | m_Chat | `UIButton` |
| UIChatRest | 1208 | m_Rest | `UIButton` |
| UIChatRest | 1552 | m_Exit | `UIButton` |
| UIChatRest | 1896 | m_TabBtn | `UITabBtn` |
| UIChatRest | 1920 | m_answerDlg | `MUIDialog` |
| UIChatRest | 3244 | m_bAnswer | `BYTE` |
| UIChatRest | 3248 | eft | `ScreenEffect *` |
| UIChatRest | 3252 | m_timewait | `TimeCtl` |
| UIChatRest | 3264 | m_isFadeOut | `BYTE` |
| UIChatRest | 3265 | m_isFadeIn | `BYTE` |
| UIChatRest | 3268 | m_noenoughmsg | `MUIDialog` |
| UIChatRest | 4592 | m_enough | `MUIDialog` |
| UIChatRest | 5916 | m_restover | `MUIDialog` |
| UIChatRest | 7240 | m_status | `unsigned int` |
| UIChatRest | 7244 | m_isExit | `BYTE` |
| UIChatRest | 7248 | m_RestScript | `RestScript` |
| UIChatRest | 9316 | m_CANREST_ID | `int` |
| UIChatRest | 9320 | m_CANNOTREST_ID | `int` |
| UIChatRest | 9324 | m_RESTOVER_ID | `int` |
| UIChatRest | 9328 | pRest | `PalScript *` |
| UIChatRest | 9332 | pCantRest | `PalScript *` |
| UIChatRest | 9336 | pRestOver | `PalScript *` |
| UIChatRest | 9340 | m_bActive | `BYTE` |
| UIChatRest | 9344 | pC_DUI | `Comp_DonateUI *` |
| UIChatRest | 9348 | m_bC_DUIOver | `BYTE` |
| UIChatRest | 9352 | m_BK | `UIStatic` |
| UIChatRest | 9504 | m_FadeOutAlpha | `BYTE` |
| UIChatRest | 9508 | m_age | `float` |
| UIChatRest | 9512 | m_life | `float` |
| UICoverFrm | 72 | rc | `tagRECT` |
| UICoverFrm | 88 | buf | `char[256]` |
| UICoverFrm | 344 | m_background | `UIStatic` |
| UICoverFrm | 504 | m_Star | `UIPar_Star[13]` |
| UICoverFrm | 2116 | m_Meteor | `UIPar_Meteor` |
| UICoverFrm | 2392 | m_cloud | `_CLOUD[10]` |
| UICoverFrm | 4552 | m_midCloud | `_CLOUD[5]` |
| UICoverFrm | 5632 | m_smlCloud | `_CLOUD[5]` |
| UICoverFrm | 6712 | m_testCloud | `_CLOUD[9]` |
| UICoverFrm | 8656 | m_mountainA | `UIStatic` |
| UICoverFrm | 8816 | m_mountainB | `UIStatic` |
| UICoverFrm | 8976 | m_frame | `UIStatic` |
| UICoverFrm | 9136 | m_Logo | `UIStatic` |
| UICoverFrm | 9296 | m_isAlpha | `unsigned char` |
| UICoverFrm | 9300 | m_alpha | `float` |
| UICoverFrm | 9304 | m_tjA | `UIStaticEXA` |
| UICoverFrm | 9504 | m_tjB | `UIStaticEXA` |
| UICoverFrm | 9704 | m_XDGS | `UIButtonEX` |
| UICoverFrm | 10096 | m_QCYM | `UIButtonEX` |
| UICoverFrm | 10488 | m_XJTM | `UIButtonEX` |
| UICoverFrm | 10880 | m_LKYX | `UIButtonEX` |
| UICoverFrm | 11272 | m_YXXX | `UIButtonEX` |
| UICoverFrm | 11664 | m_JDHY | `UIButtonEX` |
| UICoverFrm | 12056 | m_CtrlBtn | `UIButtonEX *[6]` |
| UICoverFrm | 12080 | m_SelBtn | `int` |
| UICoverFrm | 12084 | m_ExitGame | `unsigned char` |
| UICoverFrm | 12088 | pQCYM | `UITitle_QCYM *` |
| UICoverFrm | 12092 | pJDHY | `UITitle_JDHY *` |
| UICoverFrm | 12096 | pYXXX | `UITitle_YXXX *` |
| UICoverFrm | 12100 | pXJTM | `UITitle_XJTM *` |
| UICoverFrm | 12104 | pArcSave | `UITitle_ArcSave *` |
| UICoverFrm | 12108 | pLoadingFrm | `UILoadingFrm *` |
| UICoverFrm | 12112 | m_MenuType | `MENU_TYPE` |
| UICoverFrm | 12116 | m_timeAverage | `Average` |
| UICoverFrm | 12140 | m_gotogame | `unsigned char` |
| UICoverFrm | 12144 | m_flag | `unsigned int` |
| UICoverFrm | 12148 | m_test | `UIStatic` |
| UICoverFrm | 12944 | m_bLogoDone | `unsigned char` |
| UICoverFrm | 12948 | m_hCoverEffect | `int` |
| UICoverFrm | 12953 | m_bAnimFlags | `_BYTE[8]` |
| UICoverFrm | 13896 | m_bCoverTexSet | `unsigned char` |
| UICoverFrm | 13900 | m_pCoverTex | `int` |
| UICoverFrm | 14056 | m_nCoverRectArg | `int` |
| UICoverFrm | 14060 | m_nCoverInitX | `int` |
| UICoverFrm | 14068 | m_nCoverTargetX | `int` |
| UICoverFrm | 14072 | m_fCoverStep | `float` |
| UICoverFrm | 14076 | m_fCoverCurX | `float` |
| UICoverFrm | 14080 | m_CoverWnd | `UIWnd` |
| UICoverFrm | 14232 | m_bCoverAnimDone | `unsigned char` |
| UICoverFrm | 14544 | m_ActiveSlotBase | `int` |
| UICoverFrm | 14600 | m_ActiveSlotFlags | `int` |
| UICursor | 0 | m_dwID | `unsigned int[3]` |
| UICursor | 12 | m_active | `CameraCtrl *` |
| UICursor | 16 | m_tex | `gbTexture *[3]` |
| UICursor | 28 | m_bShow | `BYTE` |
| UICursor | 29 | m_bSoftMode | `BYTE` |
| UICursor | 44 | m_pData | `unsigned int` |
| UIDialog | 68 | m_bmodal | `int` |
| UIDragBar | 68 | p_Wnd | `UIWnd *` |
| UIDragBar | 72 | m_SX | `int` |
| UIDragBar | 76 | m_SY | `int` |
| UIDragBar | 80 | m_xOffSet | `int` |
| UIDragBar | 84 | m_bDrag | `BYTE` |
| UIDragBar | 85 | m_bClick | `BYTE` |
| UIDragBar | 88 | m_DragState | `int` |
| UIDragBar | 92 | m_lastPt | `tagPOINT` |
| UIDragBar | 100 | m_DragRc | `tagRECT` |
| UIDragBar | 116 | m_bkRc | `tagRECT` |
| UIDragBar | 132 | m_ProgressRc | `tagRECT` |
| UIDragBar | 148 | m_DragColor | `gbColorQuad` |
| UIDragBar | 152 | m_bkColor | `gbColorQuad` |
| UIDragBar | 156 | m_foColor | `gbColorQuad` |
| UIDragBar | 160 | m_DragTex | `gbTexture *[3]` |
| UIDragBar | 172 | m_DragTexInfo | `_PlugInfo *[3]` |
| UIDragBar | 184 | m_pbk | `gbTexture *` |
| UIDragBar | 188 | m_pbkInfo | `_PlugInfo *` |
| UIDragBar | 192 | m_ppic | `gbTexture *` |
| UIDragBar | 196 | m_ppicInfo | `_PlugInfo *` |
| UIDragBar | 200 | m_progress | `float` |
| UIDragBar | 204 | m_Lenth | `float` |
| UIDragBar | 208 | m_MaxVal | `float` |
| UIDragBar | 212 | m_Val | `float` |
| UIDragBar | 216 | m_radius | `float` |
| UIDragBar | 220 | m_step | `float` |
| UIDragBar | 224 | m_dragRadius | `int` |
| UIDragBar | 228 | m_lradius | `float` |
| UIDragBar | 232 | m_rradius | `float` |
| UIDragBar | 236 | m_tradius | `float` |
| UIDragBar | 240 | m_bradius | `float` |
| UIDragBar | 244 | m_mode | `int` |
| UIDragBar | 248 | m_dir | `int` |
| UIEmote | 72 | m_sub48 | `int` |
| UIEmote | 76 | m_cur | `int` |
| UIEmote | 80 | m_ani | `UIAnimateCtrl[13]` |
| UIEmote | 2212 | m_role | `Role *` |
| UIEmote | 2216 | m_loopcount | `int` |
| UIEmote | 2220 | m_nLoop | `int[13]` |
| UIFlexBar | 68 | m_tilewidth | `int` |
| UIFlexBar | 72 | m_tileheight | `int` |
| UIFlexBar | 76 | m_tex | `gbTexture *` |
| UIFlexBar | 80 | m_style | `int` |
| UIFrameContainer | 96 | m_bFlag96 | `char` |
| UIFrameContainer | 100 | m_aSlots | `int[6]` |
| UIFrameWnd | 68 | m_pbktex | `gbTexture *` |
| UIGameFrm | 68 | m_nField_044 | `int` |
| UIGameFrm | 72 | m_nDataCRC | `int` |
| UIGameFrm | 220 | g_pSceneTransitionEnd | `unchar *` |
| UIGameFrm | 244 | m_pStartScene | `UIScene *` |
| UIGameFrm | 256 | m_nStartPos | `signed __int16` |
| UIGameFrm | 260 | m_nInit | `UIWnd *` |
| UIGameFrm | 328 | m_nField_148 | `int` |
| UIGameFrm | 356 | m_nSaveSlot | `int` |
| UIGameFrm | 408 | m_nSceneTransFlag | `int` |
| UIGameFrm | 624 | m_nPlayerMoney | `int` |
| UIGameFrm | 628 | m_nMoneyAdd | `int` |
| UIGameFrm | 632 | m_nMoneySub | `int` |
| UIGameFrm | 636 | m_nStorePriceMod | `int` |
| UIGameFrm | 640 | m_nTodo_280 | `unsigned char` |
| UIGameFrm | 641 | m_nTodo_281 | `unsigned char` |
| UIGameFrm | 642 | m_nTodo_282 | `unsigned char` |
| UIGameFrm | 644 | m_nReputation | `int` |
| UIGameFrm | 648 | m_nSceneLoadParam | `int` |
| UIGameFrm | 652 | m_bSceneLoaded | `char` |
| UIGameFrm | 653 | m_bSceneActive | `unsigned char` |
| UIGameFrm | 656 | m_nGameMode | `int` |
| UIGameFrm | 728 | m_nBattleResult | `int` |
| UIGameFrm | 736 | m_nMissionState | `int` |
| UIGameFrm | 768 | m_nBattleCount | `int` |
| UIGameFrm | 1024 | m_nWinCount | `int` |
| UIGameFrm | 1280 | m_nLossCount | `int` |
| UIGameFrm | 1536 | m_nEscapeCount | `int` |
| UIGameFrm | 1744 | m_fAnimTimer | `float` |
| UIGameFrm | 1748 | m_fAnimSpeed | `float` |
| UIGameFrm | 1788 | m_bAnimPaused | `unsigned char` |
| UIGameFrm | 1840 | m_bAnimLoop | `unsigned char` |
| UIGameFrm | 2220 | m_pItemArray | `int[13]` |
| UIGameFrm | 2304 | m_nKeyItemCount | `int` |
| UIGameFrm | 2480 | m_fBGMVolume | `float` |
| UIGameFrm | 2484 | m_nBGMState | `int` |
| UIGameFrm | 3796 | m_nUIDialogId | `int` |
| UIGameFrm | 3829 | m_bDialogActive | `unsigned char` |
| UIGameFrm | 3904 | m_nRender | `int` |
| UIGameFrm | 3976 | m_nUIFlags | `int` |
| UIGameFrm | 4448 | m_fUIColorR | `float` |
| UIGameFrm | 4452 | m_nUIColorMode | `int` |
| UIGameFrm | 5012 | m_UITitle | `int` |
| UIGameFrm | 5104 | m_fUITransition | `float` |
| UIGameFrm | 5760 | m_fUIFadeAlpha | `float` |
| UIGameFrm | 5764 | m_nUIFadeState | `int` |
| UIGameFrm | 6416 | m_fSceneTimer | `float` |
| UIGameFrm | 6420 | m_nSceneState | `int` |
| UIGameFrm | 7072 | m_fTimerC | `float` |
| UIGameFrm | 7728 | m_fEffectTimer | `float` |
| UIGameFrm | 7732 | m_nEffectState | `int` |
| UIGameFrm | 10352 | m_fScriptTimer | `float` |
| UIGameFrm | 10364 | m_nScriptPhase | `int` |
| UIGameFrm | 11008 | m_fDialogTimer | `float` |
| UIGameFrm | 11012 | m_nDialogState | `int` |
| UIGameFrm | 12992 | m_fUIColorParam | `float` |
| UIGameFrm | 14524 | m_nGameFlags | `int` |
| UIGameFrm | 14528 | m_pDialog | `char *` |
| UIGameFrm | 14532 | m_pSceneObjRef | `SceneObj *` |
| UIGameFrm | 14536 | m_nPrevSceneState | `int` |
| UIGameFrm | 14540 | m_nSceneTransition | `int` |
| UIGameFrm | 14544 | m_aItemData | `int` |
| UIGameFrm | 16424 | m_bGameUpdating | `unsigned char` |
| UIGameFrm | 17104 | m_nPostGame | `int` |
| UIGameFrm | 28176 | m_pGameObj | `char *` |
| UIGameFrm | 28180 | m_nMode | `int` |
| UIGameFrm | 28184 | m_pGameObjB | `char *` |
| UIGameOver | 72 | m_pbktex | `gbTexture *` |
| UIGameOver | 76 | m_Blood | `UIStatic` |
| UIGameOver | 228 | m_fTime | `float` |
| UIGroupCtrl | 0 | m_bkRc | `tagRECT` |
| UIGroupCtrl | 16 | m_isCreat | `BYTE` |
| UIGroupCtrl | 20 | m_ItemNum | `int` |
| UIGroupCtrl | 24 | m_lBTNSel | `int` |
| UIGroupCtrl | 28 | m_rBTNSel | `int` |
| UIGroupCtrl | 32 | m_ItemW | `int` |
| UIGroupCtrl | 36 | m_ItemH | `int` |
| UIGroupCtrl | 40 | pRect | `tagRECT *` |
| UIGroupCtrl | 44 | pKeepRect | `tagRECT *` |
| UIGroupCtrl | 48 | m_color | `gbColorQuad` |
| UIGroupCtrl | 52 | rollSpeed | `float` |
| UIGroupCtrl | 56 | speedstep | `float` |
| UIGroupCtrl | 60 | rollID | `int` |
| UIGroupCtrl | 64 | isCtrl | `BYTE` |
| UIGroupCtrl | 68 | m_PageState | `int` |
| UIGroupCtrl | 72 | m_showNum | `int` |
| UIGroupCtrl | 76 | pEnable | `_BYTE *` |
| UIGroupCtrl | 80 | m_pbk | `gbTexture *` |
| UIGroupCtrl | 84 | m_pbkInfo | `_PlugInfo *` |
| UIHeadDialog | 80 | m_role | `Role *` |
| UIHeadDialog | 84 | m_width | `int` |
| UIHeadDialog | 88 | m_height | `int` |
| UIHeadDialog | 92 | m_bktex | `gbTexture *` |
| UIHeadDialog | 96 | m_text | `char[256]` |
| UIItem | 68 | m_fTimerLimit | `int` |
| UIItem | 72 | m_fTimerAccum | `int` |
| UIItem | 76 | m_nTodo_04C | `int` |
| UIItem | 80 | m_nTodo_050 | `int` |
| UIItem | 84 | m_nTodo_054 | `int` |
| UIItem | 88 | m_nTodo_058 | `int` |
| UIItem | 92 | m_nTodo_05C | `int` |
| UILBColumn | 0 | head | `char[64]` |
| UILBColumn | 64 | items | `PtrArray` |
| UILBColumn | 80 | width | `int` |
| UILBItem | 0 | picon | `gbTexture *` |
| UILBItem | 4 | text | `char[64]` |
| UILBItem | 68 | itemColor | `gbColorQuad` |
| UIListBox | 68 | m_selcolor | `gbColorQuad` |
| UILoadingFrm | 72 | m_LoadProgress | `UIProgressBar` |
| UILoadingFrm | 316 | m_anitime | `float` |
| UILoadingFrm | 320 | m_aniFlag | `int` |
| UILoadingFrm | 324 | m_MaxValue | `float` |
| UILoadingFrm | 328 | m_isOverProgress | `unsigned char` |
| UIMap | 68 | m_mapwidth | `int` |
| UIMap | 72 | m_screenWidth | `int` |
| UIMap | 76 | m_screenHeight | `int` |
| UIMap | 80 | m_xMapNum | `int` |
| UIMap | 84 | m_yMapNum | `int` |
| UIMap | 88 | m_MapNum | `int` |
| UIMap | 92 | m_pSubMap | `_SUBMAP *` |
| UIMap | 96 | m_moveSpeed | `float` |
| UIMap | 100 | m_isMoving | `BYTE` |
| UIMap | 104 | m_offsetx | `float` |
| UIMap | 108 | m_offsety | `float` |
| UIMap | 112 | m_moveoffsetx | `float` |
| UIMap | 116 | m_moveoffsety | `float` |
| UIMap | 120 | m_bCreate | `BYTE` |
| UIMap | 124 | timescale | `float` |
| UIMap | 128 | m_bLock | `BYTE` |
| UINote | 72 | m_static | `UIStaticFlex` |
| UINote | 264 | time | `float` |
| UIPar_Meteor | 68 | m_StartToEnd | `tagRECT` |
| UIPar_Meteor | 84 | m_tmpPt | `tagPOINT` |
| UIPar_Meteor | 92 | m_TailPt | `tagPOINT[16]` |
| UIPar_Meteor | 220 | m_nTailNum | `int` |
| UIPar_Meteor | 224 | m_ntmpTailNum | `int` |
| UIPar_Meteor | 228 | m_nFrameNumBetweenTail | `int` |
| UIPar_Meteor | 232 | m_fVelocityX | `float` |
| UIPar_Meteor | 236 | m_fVelocityY | `float` |
| UIPar_Meteor | 240 | m_passtime | `float` |
| UIPar_Meteor | 244 | m_IsInMeteor | `int` |
| UIPar_Meteor | 248 | m_nNextTime | `int` |
| UIPar_Meteor | 252 | m_nFrame | `int` |
| UIPar_Star | 68 | m_IsFadeRand | `int` |
| UIPar_Star | 72 | m_IsFadeOut | `int` |
| UIPar_Star | 76 | m_nLastTime | `int` |
| UIPar_Star | 80 | m_IsLastTimeRand | `int` |
| UIPar_Star | 84 | m_IsHighPoint | `int` |
| UIPar_Star | 88 | m_IsInFlash | `int` |
| UIPar_Star | 92 | m_nNextTime | `int` |
| UIPar_Star | 96 | m_IsNextTimeRand | `int` |
| UIPar_Star | 100 | m_nFrame | `int` |
| UIPar_TimeCtrl | 0 | newtick | `unsigned int` |
| UIPar_TimeCtrl | 4 | oldtick | `unsigned int` |
| UIPar_TimeCtrl | 8 | bNote | `BYTE` |
| UIParticle | 0 | m_viewRect | `tagRECT` |
| UIParticle | 16 | view_radiusX | `int` |
| UIParticle | 20 | view_radiusY | `int` |
| UIParticle | 24 | par_radiusX | `int` |
| UIParticle | 28 | par_radiusY | `int` |
| UIParticle | 32 | _W | `int` |
| UIParticle | 36 | _H | `int` |
| UIParticle | 40 | m_bGetBottom | `BYTE` |
| UIParticle | 41 | m_bBounceX | `BYTE` |
| UIParticle | 44 | m_HelixAngle | `float` |
| UIParticle | 48 | m_tempx | `float` |
| UIParticle | 52 | m_tempy | `float` |
| UIParticle | 56 | m_helix_rx | `float` |
| UIParticle | 60 | m_helix_ry | `float` |
| UIParticle | 64 | m_isDiffuse | `BYTE` |
| UIParticle | 68 | m_posx | `float` |
| UIParticle | 72 | m_posy | `float` |
| UIParticle | 76 | m_FlareTime | `int` |
| UIParticle | 80 | m_isSubA | `BYTE` |
| UIParticle | 84 | m_rainbowColor | `gbColorQuad` |
| UIParticle | 88 | m_bGetTop | `BYTE` |
| UIParticle | 92 | m_riseY | `float` |
| UIParticle | 96 | m_xflag | `int` |
| UIParticle | 100 | m_state | `int` |
| UIParticle | 104 | m_iscolorfade | `BYTE` |
| UIParticle | 108 | m_time | `UIPar_TimeCtrl` |
| UIParticle | 120 | m_sec | `unsigned int` |
| UIParticle | 124 | m_color | `gbColorQuad` |
| UIParticle | 128 | _isActive | `BYTE` |
| UIParticle | 132 | _fade | `float` |
| UIParticle | 136 | _x | `float` |
| UIParticle | 140 | _y | `float` |
| UIParticle | 144 | _xi | `float` |
| UIParticle | 148 | _yi | `float` |
| UIParticle | 152 | _xg | `float` |
| UIParticle | 156 | _yg | `float` |
| UIParticle | 160 | _texName | `char[256]` |
| UIParticle | 416 | _ptex | `gbTexture *` |
| UIParticle | 420 | _element | `UIStatic` |
| UIParticle | 572 | _sizeX | `int` |
| UIParticle | 576 | _sizeY | `int` |
| UIParticle | 580 | _speed | `float` |
| UIPosMaker | 0 | m_bIsLoaded | `BYTE` |
| UIPosMaker | 4 | m_pUIPos | `_UIPOS *` |
| UIPosMaker | 8 | m_nPosNum | `int` |
| UIProgressBar | 68 | m_mode | `int` |
| UIProgressBar | 72 | m_decorateRc | `tagRECT` |
| UIProgressBar | 88 | m_progress | `int` |
| UIProgressBar | 92 | m_speed | `int` |
| UIProgressBar | 96 | m_SetProgress | `int` |
| UIProgressBar | 100 | m_Lenth | `int` |
| UIProgressBar | 104 | m_MaxVal | `float` |
| UIProgressBar | 108 | m_stepval | `float` |
| UIProgressBar | 112 | m_radius | `int` |
| UIProgressBar | 116 | m_lradius | `int` |
| UIProgressBar | 120 | m_rradius | `int` |
| UIProgressBar | 124 | m_tradius | `float` |
| UIProgressBar | 128 | m_bradius | `float` |
| UIProgressBar | 132 | m_step | `int` |
| UIProgressBar | 136 | m_Val | `float` |
| UIProgressBar | 140 | m_IsGetit | `BYTE` |
| UIProgressBar | 144 | m_bkColor | `gbColorQuad` |
| UIProgressBar | 148 | m_foColor | `gbColorQuad` |
| UIProgressBar | 152 | m_pbk | `gbTexture *` |
| UIProgressBar | 156 | m_pbkInfo | `_PlugInfo *` |
| UIProgressBar | 160 | m_ppic | `gbTexture *` |
| UIProgressBar | 164 | m_ppicInfo | `_PlugInfo *` |
| UIProgressBar | 168 | m_pdecorate | `gbTexture *` |
| UIProgressBar | 172 | m_pdecorateInfo | `_PlugInfo *` |
| UIProgressBar | 176 | m_decorateW | `int` |
| UIProgressBar | 180 | m_decorateH | `int` |
| UIProgressBar | 184 | m_decorateOffsetX | `int` |
| UIProgressBar | 188 | m_decorateOffsetY | `int` |
| UIProgressBar | 192 | m_pgrmode | `PGR_MODE` |
| UIProgressBar | 196 | m_color | `gbColorQuad` |
| UIProgressBar | 200 | m_dstAlpha | `int` |
| UIProgressBar | 204 | m_alpha | `int` |
| UIProgressBar | 208 | m_minAlpha | `int` |
| UIProgressBar | 212 | m_fadespeed | `float` |
| UIProgressBar | 216 | m_isAdd | `BYTE` |
| UIProgressBar | 217 | m_isFlash | `BYTE` |
| UIProgressBar | 218 | m_stop | `BYTE` |
| UIProgressBar | 220 | m_warningval | `int` |
| UIPushButton | 68 | m_isDown | `unsigned char` |
| UIPushButton | 69 | m_isCtrl | `unsigned char` |
| UIPushButton | 70 | m_mouseoff | `unsigned char` |
| UIPushButton | 72 | m_fontcolor | `gbColorQuad` |
| UIPushButton | 76 | m_fonttype | `gbFontType` |
| UIPushButton | 80 | m_state | `UIPUSHBUTTON_STATE` |
| UIPushButton | 84 | m_texarray | `gbTexture *[2]` |
| UIPushButton | 92 | m_texarrayInfo | `_PlugInfo *[2]` |
| UIPushButton | 100 | m_bOn | `unsigned char` |
| UIPushButton | 104 | m_pOnpic | `gbTexture *` |
| UIPushButton | 108 | m_pOnpicInfo | `_PlugInfo *` |
| UIPushButton | 112 | m_pDownpic | `gbTexture *` |
| UIPushButton | 116 | m_pDownpicInfo | `_PlugInfo *` |
| UIPushButton | 120 | m_caption | `char[128]` |
| UIRoleDialog | 80 | _todo_050 | `char[32]` |
| UIRoleDialog | 112 | m_static | `UITextArea` |
| UIRoleDialog | 304 | _todo_130 | `char[152]` |
| UIRoleDialog | 456 | _todo_1c8 | `char[176]` |
| UIRoleDialog | 632 | _todo_278 | `char[344]` |
| UIRoleDialog | 976 | _todo_3d0 | `char[328]` |
| UIRoleDialog | 1304 | byMagicUseTime | `_BYTE[8][6]` |
| UIRoleDialog | 1352 | _todo_548 | `int` |
| UIRoleDialog | 1356 | _todo_54c | `int` |
| UIRoleDialog | 1360 | _todo_550 | `unsigned char` |
| UIRoleDialog | 1361 | _gap_551 | `char[4]` |
| UIRoleDialog | 1365 | _todo_555 | `unsigned char` |
| UIRoleDialog | 1366 | m_nTodo_556 | `char[2]` |
| UIRoleSelect | 80 | m_sel | `int` |
| UIRoleSelect | 84 | m_maxlen | `int` |
| UIRoleSelect | 88 | m_list | `UIListBox` |
| UIRoleSelect | 1296 | m_bk | `UIStaticFlex` |
| UIRoleSelectDialog | 72 | m_state | `int` |
| UIRoleSelectDialog | 76 | m_bk | `UIStaticFlex` |
| UIRoleSelectDialog | 268 | m_ani | `UIAnimateCtrl` |
| UIRoleSelectDialog | 432 | m_face | `UIStaticFlip` |
| UIRoleSelectDialog | 596 | m_static | `UITextArea` |
| UIRoleSelectDialog | 788 | m_texth | `int` |
| UIRoleSelectDialog | 792 | m_list | `UIListBox` |
| UIRoleSelectDialog | 2080 | m_maxlen | `int` |
| UIRoleSelectDialog | 2084 | m_last | `float` |
| UIRoleSelectDialog | 2088 | m_sel | `int` |
| UIRoleSelectDialog | 2092 | m_mode | `int` |
| UIScene | 68 | m_nViewW | `int` |
| UIScene | 72 | m_fScaleY | `float` |
| UIScene | 76 | m_fScaleX | `float` |
| UIScene | 80 | m_nTodo_050 | `unsigned char` |
| UIScene | 84 | m_nScrollState | `int` |
| UIScene | 88 | m_nScrollIdx | `int` |
| UIScene | 92 | m_nShowState | `int` |
| UIScene | 96 | m_pChildWnd | `UIWnd *` |
| UIScene | 100 | m_nClipX | `int` |
| UIScene | 104 | m_nClipY | `int` |
| UIScene | 108 | m_nRectX | `int` |
| UIScene | 112 | m_nRectY | `int` |
| UIScene | 116 | m_nClipW | `int` |
| UIScene | 120 | m_nRectH | `int` |
| UIScene | 124 | m_nRectW | `int` |
| UIScene | 128 | m_nScrollWidget | `int` |
| UIScene | 132 | m_fPosX | `float` |
| UIScene | 136 | m_fPosY | `float` |
| UIScene | 140 | m_nLoadResource | `int` |
| UIScene | 144 | m_nNotifyRender | `int` |
| UIScene | 148 | m_dwColor | `unsigned int` |
| UIScene | 152 | m_hScrollBar | `int` |
| UIScene | 156 | m_nColors | `int` |
| UIScene | 160 | m_bLoadState | `int` |
| UIScene | 164 | m_pChildData | `char *` |
| UIScene | 168 | m_fAngle | `float` |
| UIScene | 172 | m_fCameraOffset | `float` |
| UIScene | 176 | m_bFieldCC | `Parent_Data *` |
| UIScene | 180 | m_nFieldD0 | `int` |
| UIScene | 184 | m_bVisible | `Parent_Data *` |
| UIScene | 188 | m_hFont | `int` |
| UIScene | 192 | m_bEnabled | `Parent_Data *` |
| UIScene | 196 | m_pTexture | `gbTexture *` |
| UIScene | 200 | m_bOverlayRender | `unsigned char` |
| UIScene | 201 | m_nTodo_0C9 | `unsigned char` |
| UIScene | 204 | m_bCursorLeft | `unsigned char` |
| UIScene | 208 | m_hTexture | `int` |
| UISceneFace | 68 | m_hp | `UIProgressBar` |
| UISceneFace | 312 | m_mp | `UIProgressBar` |
| UISceneFace | 556 | m_face | `UIStatic[3]` |
| UISceneFace | 1012 | m_bk | `UIStatic` |
| UISceneFace | 1164 | m_clicktime | `float` |
| UISceneFace | 1168 | m_onclick | `int` |
| UISceneFace | 1172 | m_state | `UIStatic[4]` |
| UISceneFrm | 72 | m_map | `UISceneMap` |
| UISceneFrm | 1084 | m_face | `UISceneFace` |
| UISceneMap | 68 | m_probe | `UIButton` |
| UISceneMap | 412 | m_base | `UIStatic` |
| UISceneMap | 564 | m_compass | `UIStaticEX` |
| UISceneMap | 748 | m_mapbk | `UIStaticFlex` |
| UISceneMap | 940 | m_icons | `UITextureArray` |
| UISceneMap | 1008 | m_state | `int` |
| UIScenePanel | 344 | m_SlotData | `int` |
| UIScenePanel | 348 | m_nTodo_15C | `int` |
| UIScenePanel | 352 | m_nTodo_160 | `int` |
| UIScenePanel | 356 | m_nCategoryIdx | `int` |
| UIScenePanel | 360 | m_Static_360 | `UIStatic` |
| UIScenePanel | 512 | m_pSubPanel | `float` |
| UIScenePanel | 516 | m_nTodo_204 | `int` |
| UIScenePanel | 1158 | m_bPanelActive | `unsigned char` |
| UIScenePanel | 2424 | m_pPanelSlot0 | `int` |
| UIScenePanel | 2576 | m_pPanelSlot1 | `int` |
| UIScenePanel | 2728 | m_pPanelSlot2 | `int` |
| UIScenePanel | 2880 | m_pPanelSlot3 | `int` |
| UIScenePanel | 3032 | m_pPanelSlot4 | `int` |
| UIScenePanel | 3276 | m_pPanelSlot5 | `int` |
| UIScenePanel | 3428 | m_pPanelSlot6 | `int` |
| UIScenePanel | 3580 | m_pPanelSlot7 | `int` |
| UIScenePanel | 3824 | m_pPanelSlot8 | `int` |
| UIScenePanel | 5088 | m_nTodo_13E0 | `void *` |
| UIScenePanel | 8416 | m_nTodo_20E0 | `void *` |
| UIScenePanel | 10496 | m_Static_10496 | `UIStatic` |
| UIScenePanel | 10648 | m_Static_10648 | `UIStatic` |
| UIScenePanel | 10800 | m_Static_10800 | `UIStatic` |
| UIScenePanel | 10952 | m_Static_10952 | `UIStatic` |
| UIScenePanel | 11104 | m_nTodo_2B60 | `int` |
| UIScenePanel | 11108 | m_nTodo_2B64 | `int` |
| UIScenePanel | 11116 | m_nTodo_11116 | `UIWnd` |
| UIScenePanel | 11272 | m_nTodo_2C08 | `int` |
| UIScenePanel | 11276 | m_nTodo_2C0C | `int` |
| UIScenePanel | 11280 | m_nTodo_2C10 | `int` |
| UIScenePanel | 11284 | m_nTodo_2C14 | `int` |
| UIScenePanel | 11288 | m_nTodo_2C18 | `int` |
| UIScenePanel | 11292 | m_nTodo_2C1C | `int` |
| UIScenePanel | 11296 | m_nTodo_2C20 | `int` |
| UIScenePanel | 11308 | m_nTodo_11308 | `UIWnd` |
| UIScenePanel | 11464 | m_nTodo_2CC8 | `int` |
| UIScenePanel | 11468 | m_nTodo_2CCC | `int` |
| UIScenePanel | 11472 | m_nTodo_2CD0 | `int` |
| UIScenePanel | 11476 | m_nTodo_2CD4 | `int` |
| UIScenePanel | 11480 | m_nTodo_2CD8 | `int` |
| UIScenePanel | 11484 | m_nTodo_2CDC | `int` |
| UIScenePanel | 11488 | m_nTodo_2CE0 | `int` |
| UIScenePanel | 11500 | m_SceneA | `UIScene` |
| UIScenePanel | 11892 | m_SceneB | `UIScene` |
| UIScenePanel | 12284 | m_SceneC | `UIScene` |
| UIScenePanel | 12676 | m_SceneD | `UIScene` |
| UIScenePanel | 13068 | m_SceneE | `UIScene` |
| UIScenePanel | 13460 | m_SceneF | `UIScene` |
| UIScenePanel | 13832 | m_nTodo_3608 | `unsigned char` |
| UIScenePanel | 13833 | m_nTodo_3609 | `unsigned char` |
| UIScenePanel | 13836 | m_nTodo_360C | `int` |
| UIScenePanel | 13840 | m_nTodo_3610 | `int` |
| UIScenePanel | 13844 | m_nTodo_3614 | `int` |
| UIScenePanel | 13848 | m_nObjStore | `int` |
| UIScenePanel | 13864 | m_hSettingsUI | `int` |
| UIScenePanel | 13872 | m_bPanelFlagA | `unsigned char` |
| UIScenePanel | 13873 | m_nTodo_3631 | `unsigned char` |
| UIScenePanel | 13874 | m_nTodo_3632 | `unsigned char` |
| UIScenePanel | 13876 | m_nPanelState | `int` |
| UIScenePanel | 13880 | m_bCoverReady | `int` |
| UIScenePanel | 13884 | m_nSceneIdx | `int` |
| UIScenePanel | 13892 | m_bFlags0 | `unsigned char` |
| UIScenePanel | 13893 | m_bFlags1 | `unsigned char` |
| UIScenePanel | 13900 | m_pCoverTexture | `int` |
| UIScenePanel | 13904 | m_Static_13904 | `UIStatic` |
| UIScenePanel | 14056 | m_nCoverLeft | `int` |
| UIScenePanel | 14060 | m_nCoverTop | `int` |
| UIScenePanel | 14064 | m_nCoverRight | `int` |
| UIScenePanel | 14068 | m_nCoverBottom | `int` |
| UIScenePanel | 14072 | m_fAnimRate | `int` |
| UIScenePanel | 14076 | m_fAnimBase | `int` |
| UIScenePanel | 14080 | m_Static_14080 | `UIStatic` |
| UIScrollBar | 68 | m_bPress | `unsigned char` |
| UIScrollBar | 69 | m_bPressed | `unsigned char` |
| UIScrollBar | 72 | m_bk | `UIFlexBar` |
| UIScrollBar | 156 | m_btnH | `int` |
| UIScrollBar | 160 | m_mouseat | `int` |
| UIScrollBar | 164 | m_min | `int` |
| UIScrollBar | 168 | m_max | `int` |
| UIScrollBar | 172 | m_pos | `int` |
| UIScrollBar | 176 | m_lastpos | `float` |
| UIScrollBar | 180 | m_drawpos | `float` |
| UIScrollBar | 184 | m_step | `float` |
| UIScrollBar | 188 | m_pagesize | `int` |
| UIScrollBar | 192 | m_texarray | `UITextureArray` |
| UIScrollBar | 260 | m_texarrayInfo | `_PlugInfo *[10]` |
| UIScrollBar | 300 | m_keytime | `float` |
| UIScrollBar | 304 | m_btnrect | `tagRECT[2]` |
| UIScrollBar | 336 | m_slideroffset | `int` |
| UIScrollBar | 340 | m_slidertboffset | `int` |
| UIScrollBar | 344 | m_sliderw | `int` |
| UIScrollBar | 348 | m_sliderh | `int` |
| UIStatic | 68 | pDebugTex | `gbTexture *` |
| UIStatic | 72 | m_align | `int` |
| UIStatic | 76 | m_ratiow | `float` |
| UIStatic | 80 | m_ratioh | `float` |
| UIStatic | 84 | m_textx | `void *` |
| UIStatic | 88 | m_texty | `void *` |
| UIStatic | 92 | m_fonttype | `Parent_Data *` |
| UIStatic | 96 | m_text | `char[16]` |
| UIStatic | 112 | m_pbk | `gbTexture *` |
| UIStatic | 116 | m_pbkInfo | `_PlugInfo *` |
| UIStatic | 120 | m_ppic | `gbTexture *` |
| UIStatic | 124 | m_ppicInfo | `_PlugInfo *` |
| UIStatic | 128 | m_disablepic | `gbTexture *` |
| UIStatic | 132 | m_disablepicInfo | `_PlugInfo *` |
| UIStatic | 136 | m_pbk2 | `gbTexture *` |
| UIStatic | 140 | m_mouseoff | `unsigned char` |
| UIStatic | 144 | m_FVF | `int` |
| UIStatic | 148 | m_nTextW | `int` |
| UIStaticCB | 152 | m_showct | `int` |
| UIStaticEX | 152 | m_rotate | `float` |
| UIStaticEX | 156 | m_rotmode | `int` |
| UIStaticEX | 160 | m_rotdst | `float` |
| UIStaticEX | 164 | m_rotspeed | `float` |
| UIStaticEX | 168 | m_rotdir | `int` |
| UIStaticEX | 172 | m_isStoped | `unsigned char` |
| UIStaticEX | 176 | m_accelerate | `float` |
| UIStaticEX | 180 | m_notespeed | `float` |
| UIStaticEXA | 184 | center_x | `int` |
| UIStaticEXA | 188 | center_y | `int` |
| UIStaticFlex | 68 | m_currect | `tagRECT` |
| UIStaticFlex | 84 | m_texs | `UITextureArray` |
| UIStaticFlex | 152 | m_state | `UIStaticFlex_State` |
| UIStaticFlex | 156 | m_statetime | `float` |
| UIStaticFlex | 160 | m_fonttype | `gbFontType` |
| UIStaticFlex | 164 | m_tilesize | `int` |
| UIStaticFlex | 168 | m_openstyle | `int` |
| UIStaticFlip | 152 | flipMode | `int` |
| UIStaticRM | 152 | m_color | `gbColorQuad` |
| UIStaticRM | 156 | m_dstAlpha | `int` |
| UIStaticRM | 160 | m_alpha | `int` |
| UIStaticRM | 164 | m_minAlpha | `int` |
| UIStaticRM | 168 | m_fadespeed | `float` |
| UIStaticRM | 172 | m_isAdd | `unsigned char` |
| UIStaticRM | 173 | m_isFlash | `unsigned char` |
| UIStaticRM | 174 | m_stop | `unsigned char` |
| UIStaticRM | 176 | m_mode | `int` |
| UITabBtn | 0 | m_BtnAndID | `char[16]` |
| UITabBtn | 16 | m_SelBtn | `int` |
| UITabBtn | 20 | m_pFather | `UIWnd *` |
| UITabCtrl | 68 | m_itemwidth | `int` |
| UITabCtrl | 72 | m_texarray | `UITextureArray` |
| UITabCtrl | 140 | m_numpage | `int` |
| UITabCtrl | 144 | m_onpage | `int` |
| UITextArea | 68 | m_fFadeDuration | `float` |
| UITextArea | 72 | m_fFadeInit | `float` |
| UITextArea | 76 | m_nFadeElapsed | `int` |
| UITextArea | 80 | m_bFadeActive | `int` |
| UITextArea | 84 | m_nReserved54 | `int` |
| UITextArea | 88 | m_nRectLeft | `int` |
| UITextArea | 92 | m_nRectTop | `int` |
| UITextArea | 96 | m_nRectRight | `int` |
| UITextArea | 100 | m_nRectBottom | `int` |
| UITextArea | 104 | m_todo_68 | `char[68]` |
| UITextArea | 172 | m_nRenderMode | `int` |
| UITextArea | 176 | m_fFadeAlpha | `float` |
| UITextArea | 180 | m_nRenderArg | `int` |
| UITextArea | 184 | m_nFadeThreshold | `int` |
| UITextArea | 188 | m_bFadeReverse | `int` |
| UITextureArray | 0 | m_ptex | `gbTexture *[16]` |
| UITextureArray | 64 | m_num | `int` |
| UITitle | 76 | m_rcWindow | `tagRECT` |
| UITitle | 92 | m_rcWidgetRect | `tagRECT` |
| UITitle | 108 | m_nTodo_06C | `int` |
| UITitle | 112 | m_nTodo_070 | `int` |
| UITitle | 124 | m_nTodo_07C | `UIWnd *` |
| UITitle | 276 | m_nInitRoles | `UIWnd *` |
| UITitle | 428 | m_subObjA | `UIStatic` |
| UITitle | 884 | m_RoleDataA | `CScreenMode *` |
| UITitle | 988 | m_nTodo_3DC | `int` |
| UITitle | 992 | m_nTodo_3E0 | `int` |
| UITitle | 1228 | m_RoleDataB | `CScreenMode *` |
| UITitle | 1332 | m_nTodo_534 | `int` |
| UITitle | 1336 | m_nTodo_538 | `int` |
| UITitle | 1572 | m_RoleDataC | `CScreenMode *` |
| UITitle | 1676 | m_nTodo_68C | `int` |
| UITitle | 1680 | m_nTodo_690 | `int` |
| UITitle | 1916 | m_ItemSlotA | `UIItem` |
| UITitle | 3284 | m_bInitRoles | `unsigned char` |
| UITitle | 3288 | m_hEffect | `int` |
| UITitle | 3292 | m_dwEffectTick | `int` |
| UITitle | 3296 | m_dwTimerTick | `int` |
| UITitle | 3300 | m_bTimerActive | `unsigned char` |
| UITitle | 3304 | m_bTimerDone | `unsigned char` |
| UITitle | 3305 | m_bTimerProcessed | `unsigned char` |
| UITitle | 3308 | m_ItemSlotB | `UIItem` |
| UITitle | 4676 | m_ItemSlotC | `UIItem` |
| UITitle | 6044 | m_ItemSlotD | `UIItem` |
| UITitle | 7412 | m_nTitleStage | `int` |
| UITitle | 7416 | m_bScriptActive | `unsigned char` |
| UITitle | 8460 | m_nTitleScript | `int` |
| UITitle | 9488 | m_nScriptHandleA | `int` |
| UITitle | 9492 | m_nScriptHandleB | `int` |
| UITitle | 9496 | m_nScriptHandleC | `int` |
| UITitle | 9500 | m_nScriptHandleD | `int` |
| UITitle | 9504 | m_nScriptHandleE | `int` |
| UITitle | 9508 | m_nScriptHandleF | `int` |
| UITitle | 9512 | m_bScriptRunning | `unsigned char` |
| UITitle_ArcSave | 72 | m_YesNo | `MUIDialog` |
| UITitle_BBTY | 72 | rc | `tagRECT` |
| UITitle_BBTY | 88 | bkWndX | `int` |
| UITitle_BBTY | 92 | bkWndY | `int` |
| UITitle_BBTY | 96 | i | `int` |
| UITitle_BBTY | 100 | j | `int` |
| UITitle_BBTY | 104 | buf | `char[256]` |
| UITitle_BBTY | 360 | m_background | `UIStatic` |
| UITitle_BBTY | 520 | m_remark | `UIStatic` |
| UITitle_BBTY | 680 | m_btn | `UIButtonEXA[3]` |
| UITitle_BBTY | 1808 | m_exit | `UIButton` |
| UITitle_BBTY | 2152 | m_Name | `UIStatic` |
| UITitle_BBTY | 2312 | m_Left | `UIStatic` |
| UITitle_BBTY | 2472 | m_Right | `UIStatic` |
| UITitle_BBTY | 2632 | m_FlagT | `UIStatic` |
| UITitle_BBTY | 2792 | m_FlagB | `UIStatic` |
| UITitle_BBTY | 2952 | m_Start | `UIButton` |
| UITitle_BBTY | 3296 | m_Notes | `UIButton` |
| UITitle_JDHY | 72 | rc | `tagRECT` |
| UITitle_JDHY | 88 | buf | `char[256]` |
| UITitle_JDHY | 344 | m_OutFrameT | `UIStatic` |
| UITitle_JDHY | 504 | m_OutFrameR | `UIStatic` |
| UITitle_JDHY | 664 | m_OutFrameL | `UIStatic` |
| UITitle_JDHY | 824 | m_OutFrameB | `UIStatic` |
| UITitle_JDHY | 984 | m_background | `UIStatic` |
| UITitle_JDHY | 1144 | m_exit | `UIButton` |
| UITitle_JDHY | 1488 | m_isItemShow | `_BYTE[99]` |
| UITitle_JDHY | 1588 | m_NoteItem | `Note_Item[99]` |
| UITitle_JDHY | 370660 | m_Title_JDHY | `UIStatic` |
| UITitle_JDHY | 370820 | m_TopBar | `UIStatic` |
| UITitle_JDHY | 370980 | m_BottomBar | `UIStatic` |
| UITitle_JDHY | 371140 | m_BackBar | `UIStatic` |
| UITitle_JDHY | 371300 | m_BackBar2 | `UIStatic` |
| UITitle_JDHY | 371460 | m_pbPage | `UIPushButton[10]` |
| UITitle_JDHY | 373980 | m_Scroll | `UIScrollBar` |
| UITitle_JDHY | 374348 | m_CurScrollPos | `int` |
| UITitle_JDHY | 374352 | m_ItemH | `int` |
| UITitle_JDHY | 374356 | m_ItemW | `int` |
| UITitle_JDHY | 374360 | m_firstItem | `int` |
| UITitle_JDHY | 374364 | m_selItem | `int` |
| UITitle_JDHY | 374368 | m_getNote | `int` |
| UITitle_JDHY | 374372 | m_loading | `int` |
| UITitle_JDHY | 374376 | m_passtime | `float` |
| UITitle_JDHY | 374380 | m_LoadBtn | `UIButton` |
| UITitle_JDHY | 374724 | m_DeleteBtn | `UIButton` |
| UITitle_JDHY | 375068 | m_noteState | `NOTE_STATE` |
| UITitle_QCYM | 72 | rc | `tagRECT` |
| UITitle_QCYM | 88 | buf | `char[256]` |
| UITitle_QCYM | 344 | m_OutFrameT | `UIStatic` |
| UITitle_QCYM | 504 | m_OutFrameR | `UIStatic` |
| UITitle_QCYM | 664 | m_OutFrameL | `UIStatic` |
| UITitle_QCYM | 824 | m_OutFrameB | `UIStatic` |
| UITitle_QCYM | 984 | m_background | `UIStatic` |
| UITitle_QCYM | 1144 | m_title | `UIStatic` |
| UITitle_QCYM | 1304 | m_btn | `UIButtonEXA[30]` |
| UITitle_XJTM | 72 | rc | `tagRECT` |
| UITitle_XJTM | 88 | bkWndX | `int` |
| UITitle_XJTM | 92 | bkWndY | `int` |
| UITitle_XJTM | 96 | m_OutFrameT | `UIStatic` |
| UITitle_XJTM | 256 | m_OutFrameR | `UIStatic` |
| UITitle_XJTM | 416 | m_OutFrameL | `UIStatic` |
| UITitle_XJTM | 576 | m_OutFrameB | `UIStatic` |
| UITitle_XJTM | 736 | m_background | `UIStatic` |
| UITitle_XJTM | 896 | m_title | `UIStatic` |
| UITitle_XJTM | 1056 | m_exit | `UIButton` |
| UITitle_XJTM | 1400 | m_IsActive | `unsigned char` |
| UITitle_XJTM | 1404 | m_pMgr | `UICoverFrm *` |
| UITitle_XJTM | 1408 | m_Item | `_Item` |
| UITitle_XJTM | 1456 | m_SelFirstRow | `int` |
| UITitle_XJTM | 1460 | m_SelSecondRow | `int` |
| UITitle_XJTM | 1464 | m_SelFirstChanged | `unsigned char` |
| UITitle_XJTM | 1465 | m_SelSecondChanged | `unsigned char` |
| UITitle_XJTM | 1466 | m_SelZeroChanged | `unsigned char` |
| UITitle_XJTM | 1468 | m_WordBk | `UIStatic` |
| UITitle_XJTM | 1628 | m_BtnBk | `UIStatic` |
| UITitle_XJTM | 1788 | m_BtnFirstRow | `UIButton[4]` |
| UITitle_XJTM | 3164 | m_BtnSecondRow | `UIButton[5]` |
| UITitle_XJTM | 4884 | m_ItemInfo | `UIStatic` |
| UITitle_YXXX | 72 | rc | `tagRECT` |
| UITitle_YXXX | 88 | m_OutFrameT | `UIStatic` |
| UITitle_YXXX | 248 | m_OutFrameR | `UIStatic` |
| UITitle_YXXX | 408 | m_OutFrameL | `UIStatic` |
| UITitle_YXXX | 568 | m_OutFrameB | `UIStatic` |
| UITitle_YXXX | 728 | m_background | `UIStatic` |
| UITitle_YXXX | 888 | m_title | `UIStatic` |
| UITitle_YXXX | 1048 | m_exit | `UIButton` |
| UITitle_YXXX | 1392 | m_ZZRY | `UIButton` |
| UITitle_YXXX | 1736 | m_XGWZ | `UIButton` |
| UITitle_YXXX | 2080 | m_WordBk | `UIStatic` |
| UIWnd | 4 | m_fontcolor | `gbColorQuad` |
| UIWnd | 8 | m_wndcolor | `gbColorQuad` |
| UIWnd | 12 | m_id | `unsigned int` |
| UIWnd | 16 | m_rect | `tagRECT` |
| UIWnd | 32 | m_pfather | `UIWnd *` |
| UIWnd | 36 | m_childs | `PtrArray` |
| UIWnd | 52 | m_bcreateok | `int` |
| UIWnd | 56 | m_bvisible | `int` |
| UIWnd | 60 | m_benable | `int` |
| UIWnd | 64 | m_bfocus | `int` |
| UnderWater | 0 | m_bEnable | `BYTE` |
| UnderWater | 4 | m_pIB | `IDirect3DIndexBuffer9 *` |
| UnderWater | 8 | m_pVB | `IDirect3DVertexBuffer9 *` |
| UnderWater | 12 | m_pBumpmapTex | `IDirect3DTexture9 *` |
| UnderWater | 16 | m_iMode | `int` |
| UnderWater | 20 | m_fTime | `float` |
| UnwindMapEntry | 0 | toState | `int` |
| UnwindMapEntry | 4 | action | `char *` |
| WAVEFORMAT | 0 | wFormatTag | `unsigned __int16` |
| WAVEFORMAT | 2 | nChannels | `unsigned __int16` |
| WAVEFORMAT | 4 | nSamplesPerSec | `unsigned int` |
| WAVEFORMAT | 8 | nAvgBytesPerSec | `unsigned int` |
| WAVEFORMAT | 12 | nBlockAlign | `unsigned __int16` |
| WishPool | 0 | open | `BYTE` |
| WishPool | 4 | money | `int` |
| WishPool | 8 | flower | `BYTE` |
| XJ_Pic | 8 | m_fElapsed | `float` |
| XJ_Pic | 12 | m_bEnd | `BYTE` |
| _ADPCMDATATAG | 0 | blocksize | `unsigned int` |
| _ADPCMDATATAG | 4 | extrasamples | `unsigned int` |
| _ADPCMDATATAG | 8 | blockleft | `unsigned int` |
| _ADPCMDATATAG | 12 | step | `unsigned int` |
| _ADPCMDATATAG | 16 | savesrc | `unsigned int` |
| _ADPCMDATATAG | 20 | sample | `unsigned int` |
| _ADPCMDATATAG | 24 | destend | `unsigned int` |
| _ADPCMDATATAG | 28 | srcend | `unsigned int` |
| _ADPCMDATATAG | 32 | samplesL | `unsigned int` |
| _ADPCMDATATAG | 36 | samplesR | `unsigned int` |
| _ADPCMDATATAG | 40 | moresamples | `unsigned __int16[16]` |
| _Btn_BtnID | 0 | _pBtn | `UIButton *` |
| _Btn_BtnID | 4 | _btnID | `unsigned int` |
| _CLOUD | 0 | _cloud | `UIStatic` |
| _CLOUD | 152 | _cloudRc | `tagRECT` |
| _CLOUD | 168 | _width | `int` |
| _CLOUD | 172 | _height | `int` |
| _CLOUD | 176 | _cloudSpeed | `float` |
| _CLOUD | 180 | _alpha | `float` |
| _CLOUD | 184 | _fade | `float` |
| _CLOUD | 188 | _isfade | `BYTE` |
| _CLOUD | 192 | _up | `int` |
| _CLOUD | 196 | _yPt | `int` |
| _CLOUD | 200 | _fluctuate | `int` |
| _CONTEXT | 0 | ContextFlags | `unsigned int` |
| _CONTEXT | 4 | Dr0 | `unsigned int` |
| _CONTEXT | 8 | Dr1 | `unsigned int` |
| _CONTEXT | 12 | Dr2 | `unsigned int` |
| _CONTEXT | 16 | Dr3 | `unsigned int` |
| _CONTEXT | 20 | Dr6 | `unsigned int` |
| _CONTEXT | 24 | Dr7 | `unsigned int` |
| _CONTEXT | 28 | FloatSave | `_FLOATING_SAVE_AREA` |
| _CONTEXT | 140 | SegGs | `unsigned int` |
| _CONTEXT | 144 | SegFs | `unsigned int` |
| _CONTEXT | 148 | SegEs | `unsigned int` |
| _CONTEXT | 152 | SegDs | `unsigned int` |
| _CONTEXT | 156 | Edi | `unsigned int` |
| _CONTEXT | 160 | Esi | `unsigned int` |
| _CONTEXT | 164 | Ebx | `unsigned int` |
| _CONTEXT | 168 | Edx | `unsigned int` |
| _CONTEXT | 172 | Ecx | `unsigned int` |
| _CONTEXT | 176 | Eax | `unsigned int` |
| _CONTEXT | 180 | Ebp | `unsigned int` |
| _CONTEXT | 184 | Eip | `unsigned int` |
| _CONTEXT | 188 | SegCs | `unsigned int` |
| _CONTEXT | 192 | EFlags | `unsigned int` |
| _CONTEXT | 196 | Esp | `unsigned int` |
| _CONTEXT | 200 | SegSs | `unsigned int` |
| _CONTEXT | 204 | ExtendedRegisters | `_BYTE[512]` |
| _Collvec | 0 | _Hand | `unsigned int` |
| _Collvec | 4 | _Page | `unsigned int` |
| _Console | 0 | m_numcmd | `int` |
| _Console | 4 | m_cmd | `_Console__ConCmd[64]` |
| _Console | 8708 | m_rect | `tagRECT` |
| _Console | 8724 | m_bactive | `int` |
| _Console | 8728 | m_bEnable | `int` |
| _Console | 8732 | m_color | `gbColorQuad` |
| _Console | 8736 | m_inputbuf | `char[100]` |
| _Console | 8836 | m_showbuf | `char[100][17]` |
| _Console | 10536 | m_fontcolor | `gbColorQuad` |
| _Ctypevec | 0 | _Hand | `unsigned int` |
| _Ctypevec | 4 | _Page | `unsigned int` |
| _Ctypevec | 8 | _Table | `signed __int16 *` |
| _Ctypevec | 12 | _Delfl | `int` |
| _Cvtvec | 0 | _Hand | `unsigned int` |
| _Cvtvec | 4 | _Page | `unsigned int` |
| _DIACTIONA | 0 | uAppData | `unsigned int` |
| _DIACTIONA | 4 | dwSemantic | `unsigned int` |
| _DIACTIONA | 8 | dwFlags | `unsigned int` |
| _DIACTIONA | 12 | uResIdString | `unsigned int` |
| _DIACTIONA | 16 | guidInstance | `_GUID` |
| _DIACTIONA | 32 | dwObjID | `unsigned int` |
| _DIACTIONA | 36 | dwHow | `unsigned int` |
| _DIACTIONFORMATA | 0 | dwSize | `unsigned int` |
| _DIACTIONFORMATA | 4 | dwActionSize | `unsigned int` |
| _DIACTIONFORMATA | 8 | dwDataSize | `unsigned int` |
| _DIACTIONFORMATA | 12 | dwNumActions | `unsigned int` |
| _DIACTIONFORMATA | 16 | rgoAction | `_DIACTIONA *` |
| _DIACTIONFORMATA | 20 | guidActionMap | `_GUID` |
| _DIACTIONFORMATA | 36 | dwGenre | `unsigned int` |
| _DIACTIONFORMATA | 40 | dwBufferSize | `unsigned int` |
| _DIACTIONFORMATA | 44 | lAxisMin | `int` |
| _DIACTIONFORMATA | 48 | lAxisMax | `int` |
| _DIACTIONFORMATA | 52 | hInstString | `HINSTANCE__ *` |
| _DIACTIONFORMATA | 56 | ftTimeStamp | `_FILETIME` |
| _DIACTIONFORMATA | 64 | dwCRC | `unsigned int` |
| _DIACTIONFORMATA | 68 | tszActionMap | `char[324]` |
| _DICOLORSET | 0 | dwSize | `unsigned int` |
| _DICOLORSET | 4 | cTextFore | `unsigned int` |
| _DICOLORSET | 8 | cTextHighlight | `unsigned int` |
| _DICOLORSET | 12 | cCalloutLine | `unsigned int` |
| _DICOLORSET | 16 | cCalloutHighlight | `unsigned int` |
| _DICOLORSET | 20 | cBorder | `unsigned int` |
| _DICOLORSET | 24 | cControlFill | `unsigned int` |
| _DICOLORSET | 28 | cHighlightFill | `unsigned int` |
| _DICOLORSET | 32 | cAreaFill | `unsigned int` |
| _DICONFIGUREDEVICESPARAMSA | 0 | dwSize | `unsigned int` |
| _DICONFIGUREDEVICESPARAMSA | 4 | dwcUsers | `unsigned int` |
| _DICONFIGUREDEVICESPARAMSA | 8 | lptszUserNames | `char *` |
| _DICONFIGUREDEVICESPARAMSA | 12 | dwcFormats | `unsigned int` |
| _DICONFIGUREDEVICESPARAMSA | 16 | lprgFormats | `_DIACTIONFORMATA *` |
| _DICONFIGUREDEVICESPARAMSA | 20 | hwnd | `HWND__ *` |
| _DICONFIGUREDEVICESPARAMSA | 24 | dics | `_DICOLORSET` |
| _DICONFIGUREDEVICESPARAMSA | 60 | lpUnkDDSTarget | `IUnknown *` |
| _DIDATAFORMAT | 0 | dwSize | `unsigned int` |
| _DIDATAFORMAT | 4 | dwObjSize | `unsigned int` |
| _DIDATAFORMAT | 8 | dwFlags | `unsigned int` |
| _DIDATAFORMAT | 12 | dwDataSize | `unsigned int` |
| _DIDATAFORMAT | 16 | dwNumObjs | `unsigned int` |
| _DIDATAFORMAT | 20 | rgodf | `_DIOBJECTDATAFORMAT *` |
| _DIDEVICEIMAGEINFOA | 0 | tszImagePath | `char[324]` |
| _DIDEVICEIMAGEINFOA | 324 | dwFlags | `unsigned int` |
| _DIDEVICEIMAGEINFOA | 328 | dwViewID | `unsigned int` |
| _DIDEVICEIMAGEINFOA | 332 | rcOverlay | `tagRECT` |
| _DIDEVICEIMAGEINFOA | 348 | dwObjID | `unsigned int` |
| _DIDEVICEIMAGEINFOA | 352 | dwcValidPts | `unsigned int` |
| _DIDEVICEIMAGEINFOA | 356 | rgptCalloutLine | `tagPOINT[5]` |
| _DIDEVICEIMAGEINFOA | 396 | rcCalloutRect | `tagRECT` |
| _DIDEVICEIMAGEINFOA | 412 | dwTextAlign | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 0 | dwSize | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 4 | dwSizeImageInfo | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 8 | dwcViews | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 12 | dwcButtons | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 16 | dwcAxes | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 20 | dwcPOVs | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 24 | dwBufferSize | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 28 | dwBufferUsed | `unsigned int` |
| _DIDEVICEIMAGEINFOHEADERA | 32 | lprgImageInfoArray | `_DIDEVICEIMAGEINFOA *` |
| _DIG_DRIVER | 0 | tag | `char[4]` |
| _DIG_DRIVER | 4 | backgroundtimer | `int` |
| _DIG_DRIVER | 8 | quiet | `int` |
| _DIG_DRIVER | 12 | n_active_samples | `int` |
| _DIG_DRIVER | 16 | master_volume | `int` |
| _DIG_DRIVER | 20 | DMA_rate | `int` |
| _DIG_DRIVER | 24 | hw_format | `int` |
| _DIG_DRIVER | 28 | hw_mode_flags | `unsigned int` |
| _DIG_DRIVER | 32 | channels_per_sample | `int` |
| _DIG_DRIVER | 36 | bytes_per_channel | `int` |
| _DIG_DRIVER | 40 | channels_per_buffer | `int` |
| _DIG_DRIVER | 44 | samples_per_buffer | `int` |
| _DIG_DRIVER | 48 | playing | `int` |
| _DIG_DRIVER | 52 | samples | `_SAMPLE *` |
| _DIG_DRIVER | 56 | n_samples | `int` |
| _DIG_DRIVER | 60 | build_size | `int` |
| _DIG_DRIVER | 64 | build_buffer | `int *` |
| _DIG_DRIVER | 68 | system_data | `int[8]` |
| _DIG_DRIVER | 100 | buffer_size | `int` |
| _DIG_DRIVER | 104 | hWaveOut | `HWAVEOUT__ *` |
| _DIG_DRIVER | 108 | reset_works | `unsigned int` |
| _DIG_DRIVER | 112 | request_reset | `unsigned int` |
| _DIG_DRIVER | 116 | first | `wavehdr_tag *` |
| _DIG_DRIVER | 120 | n_buffers | `int` |
| _DIG_DRIVER | 124 | return_list | `wavehdr_tag **` |
| _DIG_DRIVER | 128 | return_head | `int` |
| _DIG_DRIVER | 132 | return_tail | `int` |
| _DIG_DRIVER | 136 | deviceid | `unsigned int` |
| _DIG_DRIVER | 140 | wformat | `pcmwaveformat_tag` |
| _DIG_DRIVER | 156 | guid | `unsigned int` |
| _DIG_DRIVER | 160 | pDS | `char *` |
| _DIG_DRIVER | 164 | ds_priority | `unsigned int` |
| _DIG_DRIVER | 168 | emulated_ds | `int` |
| _DIG_DRIVER | 172 | lppdsb | `char *` |
| _DIG_DRIVER | 176 | dsHwnd | `unsigned int` |
| _DIG_DRIVER | 180 | lpbufflist | `char *` |
| _DIG_DRIVER | 184 | samp_list | `_SAMPLE **` |
| _DIG_DRIVER | 188 | sec_format | `int *` |
| _DIG_DRIVER | 192 | max_buffs | `int` |
| _DIG_DRIVER | 196 | released | `int` |
| _DIG_DRIVER | 200 | foreground_timer | `unsigned int` |
| _DIG_DRIVER | 204 | next | `_DIG_DRIVER *` |
| _DIG_DRIVER | 208 | callingCT | `int` |
| _DIG_DRIVER | 212 | callingDS | `int` |
| _DIG_DRIVER | 216 | DS_initialized | `int` |
| _DIG_DRIVER | 220 | DS_sec_buff | `char *` |
| _DIG_DRIVER | 224 | DS_out_buff | `char *` |
| _DIG_DRIVER | 228 | DS_buffer_size | `int` |
| _DIG_DRIVER | 232 | DS_frag_cnt | `int` |
| _DIG_DRIVER | 236 | DS_frag_size | `int` |
| _DIG_DRIVER | 240 | DS_last_frag | `int` |
| _DIG_DRIVER | 244 | DS_last_write | `int` |
| _DIG_DRIVER | 248 | DS_last_timer | `int` |
| _DIG_DRIVER | 252 | DS_skip_time | `int` |
| _DIG_DRIVER | 256 | DS_use_default_format | `int` |
| _DIG_DRIVER | 260 | use_MMX | `int` |
| _DIG_DRIVER | 264 | decode_buffer | `char *` |
| _DIG_DRIVER | 268 | decode_buffer_size | `int` |
| _DIG_DRIVER | 272 | us_count | `unsigned int` |
| _DIG_DRIVER | 276 | ms_count | `unsigned int` |
| _DIG_DRIVER | 280 | last_ms_polled | `unsigned int` |
| _DIG_DRIVER | 284 | last_percent | `unsigned int` |
| _DIG_DRIVER | 288 | pipeline | `DPINFO[4]` |
| _DIG_DRIVER | 704 | reverb_buffer | `int *` |
| _DIG_DRIVER | 708 | reverb_buffer_size | `int` |
| _DIG_DRIVER | 712 | reverb_buffer_position | `int` |
| _DIG_DRIVER | 716 | no_wom_done | `int` |
| _DIG_DRIVER | 720 | wom_done_buffers | `unsigned int` |
| _DIOBJECTDATAFORMAT | 0 | pguid | `_GUID *` |
| _DIOBJECTDATAFORMAT | 4 | dwOfs | `unsigned int` |
| _DIOBJECTDATAFORMAT | 8 | dwType | `unsigned int` |
| _DIOBJECTDATAFORMAT | 12 | dwFlags | `unsigned int` |
| _EH3_EXCEPTION_REGISTRATION | 0 | Next | `_EH3_EXCEPTION_REGISTRATION *` |
| _EH3_EXCEPTION_REGISTRATION | 4 | ExceptionHandler | `PVOID` |
| _EH3_EXCEPTION_REGISTRATION | 8 | ScopeTable | `PSCOPETABLE_ENTRY` |
| _EH3_EXCEPTION_REGISTRATION | 12 | TryLevel | `unsigned int` |
| _EXCEPTION_POINTERS | 0 | ExceptionRecord | `_EXCEPTION_RECORD *` |
| _EXCEPTION_POINTERS | 4 | ContextRecord | `_CONTEXT *` |
| _EXCEPTION_RECORD | 0 | ExceptionCode | `unsigned int` |
| _EXCEPTION_RECORD | 4 | ExceptionFlags | `unsigned int` |
| _EXCEPTION_RECORD | 8 | ExceptionRecord | `_EXCEPTION_RECORD *` |
| _EXCEPTION_RECORD | 12 | ExceptionAddress | `char *` |
| _EXCEPTION_RECORD | 16 | NumberParameters | `unsigned int` |
| _EXCEPTION_RECORD | 20 | ExceptionInformation | `unsigned int[15]` |
| _FLOATING_SAVE_AREA | 0 | ControlWord | `unsigned int` |
| _FLOATING_SAVE_AREA | 4 | StatusWord | `unsigned int` |
| _FLOATING_SAVE_AREA | 8 | TagWord | `unsigned int` |
| _FLOATING_SAVE_AREA | 12 | ErrorOffset | `unsigned int` |
| _FLOATING_SAVE_AREA | 16 | ErrorSelector | `unsigned int` |
| _FLOATING_SAVE_AREA | 20 | DataOffset | `unsigned int` |
| _FLOATING_SAVE_AREA | 24 | DataSelector | `unsigned int` |
| _FLOATING_SAVE_AREA | 28 | RegisterArea | `_BYTE[80]` |
| _FLOATING_SAVE_AREA | 108 | Cr0NpxState | `unsigned int` |
| _FLOORPARAM | 0 | m_GoundPt | `tagPOINT` |
| _FLOORPARAM | 8 | m_Valid | `BYTE` |
| _FLTPROVIDER | 0 | PROVIDER_query_attribute | `char *` |
| _FLTPROVIDER | 4 | startup | `char *` |
| _FLTPROVIDER | 8 | error | `char *` |
| _FLTPROVIDER | 12 | shutdown | `char *` |
| _FLTPROVIDER | 16 | set_provider_preference | `char *` |
| _FLTPROVIDER | 20 | open_driver | `char *` |
| _FLTPROVIDER | 24 | close_driver | `char *` |
| _FLTPROVIDER | 28 | premix_process | `char *` |
| _FLTPROVIDER | 32 | postmix_process | `char *` |
| _FLTPROVIDER | 36 | open_sample | `char *` |
| _FLTPROVIDER | 40 | close_sample | `char *` |
| _FLTPROVIDER | 44 | sample_process | `char *` |
| _FLTPROVIDER | 48 | sample_attribute | `char *` |
| _FLTPROVIDER | 52 | set_sample_preference | `char *` |
| _FLTPROVIDER | 56 | dig | `_DIG_DRIVER *` |
| _FLTPROVIDER | 60 | provider | `unsigned int` |
| _FLTPROVIDER | 64 | driver_state | `int` |
| _FLTPROVIDER | 68 | next | `_FLTPROVIDER *` |
| _IMAGE_DATA_DIRECTORY | 0 | VirtualAddress | `unsigned int` |
| _IMAGE_DATA_DIRECTORY | 4 | Size | `unsigned int` |
| _IMAGE_DOS_HEADER | 0 | e_magic | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 2 | e_cblp | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 4 | e_cp | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 6 | e_crlc | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 8 | e_cparhdr | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 10 | e_minalloc | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 12 | e_maxalloc | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 14 | e_ss | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 16 | e_sp | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 18 | e_csum | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 20 | e_ip | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 22 | e_cs | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 24 | e_lfarlc | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 26 | e_ovno | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 28 | e_res | `unsigned __int16[4]` |
| _IMAGE_DOS_HEADER | 36 | e_oemid | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 38 | e_oeminfo | `unsigned __int16` |
| _IMAGE_DOS_HEADER | 40 | e_res2 | `unsigned __int16[10]` |
| _IMAGE_DOS_HEADER | 60 | e_lfanew | `int` |
| _IMAGE_FILE_HEADER | 0 | Machine | `unsigned __int16` |
| _IMAGE_FILE_HEADER | 2 | NumberOfSections | `unsigned __int16` |
| _IMAGE_FILE_HEADER | 4 | TimeDateStamp | `unsigned int` |
| _IMAGE_FILE_HEADER | 8 | PointerToSymbolTable | `unsigned int` |
| _IMAGE_FILE_HEADER | 12 | NumberOfSymbols | `unsigned int` |
| _IMAGE_FILE_HEADER | 16 | SizeOfOptionalHeader | `unsigned __int16` |
| _IMAGE_FILE_HEADER | 18 | Characteristics | `unsigned __int16` |
| _IMAGE_NT_HEADERS | 0 | Signature | `unsigned int` |
| _IMAGE_NT_HEADERS | 4 | FileHeader | `_IMAGE_FILE_HEADER` |
| _IMAGE_NT_HEADERS | 24 | OptionalHeader | `_IMAGE_OPTIONAL_HEADER` |
| _IMAGE_OPTIONAL_HEADER | 0 | Magic | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 2 | MajorLinkerVersion | `BYTE` |
| _IMAGE_OPTIONAL_HEADER | 3 | MinorLinkerVersion | `BYTE` |
| _IMAGE_OPTIONAL_HEADER | 4 | SizeOfCode | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 8 | SizeOfInitializedData | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 12 | SizeOfUninitializedData | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 16 | AddressOfEntryPoint | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 20 | BaseOfCode | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 24 | BaseOfData | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 28 | ImageBase | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 32 | SectionAlignment | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 36 | FileAlignment | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 40 | MajorOperatingSystemVersion | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 42 | MinorOperatingSystemVersion | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 44 | MajorImageVersion | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 46 | MinorImageVersion | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 48 | MajorSubsystemVersion | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 50 | MinorSubsystemVersion | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 52 | Win32VersionValue | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 56 | SizeOfImage | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 60 | SizeOfHeaders | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 64 | CheckSum | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 68 | Subsystem | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 70 | DllCharacteristics | `unsigned __int16` |
| _IMAGE_OPTIONAL_HEADER | 72 | SizeOfStackReserve | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 76 | SizeOfStackCommit | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 80 | SizeOfHeapReserve | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 84 | SizeOfHeapCommit | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 88 | LoaderFlags | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 92 | NumberOfRvaAndSizes | `unsigned int` |
| _IMAGE_OPTIONAL_HEADER | 96 | DataDirectory | `_IMAGE_DATA_DIRECTORY[16]` |
| _Item | 0 | title | `char[16]` |
| _Item | 16 | info | `char[16]` |
| _Item | 32 | bHasChild | `BYTE` |
| _Item | 36 | nChildNum | `int` |
| _Item | 40 | bIsPic | `BYTE` |
| _Item | 44 | ppChildren | `_Item **` |
| _Item_List_Info | 72 | m_background | `UIStatic` |
| _Item_List_Info | 232 | m_IsActive | `unsigned char` |
| _Item_List_Info | 236 | m_pItem | `_Item *` |
| _Item_List_Info | 240 | m_BtnItem | `UIButton[12]` |
| _Item_List_Info | 4368 | ms_Title | `UIStatic` |
| _Item_List_Info | 4528 | ms_Info | `UIStatic` |
| _Item_List_Info | 4688 | ms_Pic | `UIStatic` |
| _Item_List_Info | 4848 | mb_Prev | `UIButton` |
| _LARGE_INTEGER | 0 | QuadPart | `int` |
| _LARGE_INTEGER | 4 | HighPart | `int` |
| _MapElement | 0 | m_bShow | `BYTE` |
| _MapElement | 1 | m_cango | `BYTE` |
| _MapElement | 4 | m_screenPt | `tagPOINT` |
| _MapElement | 12 | m_btn | `UIButtonEXA` |
| _MapElement | 388 | m_isBtnCreate | `BYTE` |
| _MapElement | 389 | m_show | `BYTE` |
| _PMD | 0 | mdisp | `int` |
| _PMD | 4 | pdisp | `int` |
| _PMD | 8 | vdisp | `int` |
| _PURGE_INFO | 0 | min_wu | `unsigned int` |
| _PURGE_INFO | 4 | max_wu | `unsigned int` |
| _PlugInfo | 0 | filepos | `int` |
| _PlugInfo | 4 | name | `char[256]` |
| _PlugInfo | 260 | crc | `unsigned int` |
| _PlugInfo | 264 | left | `unsigned int` |
| _PlugInfo | 268 | top | `unsigned int` |
| _PlugInfo | 272 | width | `unsigned int` |
| _PlugInfo | 276 | height | `unsigned int` |
| _PlugInfo | 280 | srcWidth | `unsigned int` |
| _PlugInfo | 284 | srcHeight | `unsigned int` |
| _PlugInfo | 288 | libName | `char[256]` |
| _PlugInfo | 544 | libWidth | `unsigned int` |
| _PlugInfo | 548 | libHeight | `unsigned int` |
| _PlugInfo | 552 | _tex_uvLT | `_Texture_uv` |
| _PlugInfo | 560 | _tex_uvLB | `_Texture_uv` |
| _PlugInfo | 568 | _tex_uvRB | `_Texture_uv` |
| _PlugInfo | 576 | _tex_uvRT | `_Texture_uv` |
| _RGNDATA | 0 | rdh | `_RGNDATAHEADER` |
| _RGNDATA | 32 | Buffer | `char[1]` |
| _RGNDATAHEADER | 0 | dwSize | `unsigned int` |
| _RGNDATAHEADER | 4 | iType | `unsigned int` |
| _RGNDATAHEADER | 8 | nCount | `unsigned int` |
| _RGNDATAHEADER | 12 | nRgnSize | `unsigned int` |
| _RGNDATAHEADER | 16 | rcBound | `tagRECT` |
| _SAMPLE | 0 | tag | `char[4]` |
| _SAMPLE | 4 | driver | `_DIG_DRIVER *` |
| _SAMPLE | 8 | status | `unsigned int` |
| _SAMPLE | 12 | start | `char *[2]` |
| _SAMPLE | 20 | len | `unsigned int[2]` |
| _SAMPLE | 28 | pos | `unsigned int[2]` |
| _SAMPLE | 36 | done | `unsigned int[2]` |
| _SAMPLE | 44 | reset_ASI | `int[2]` |
| _SAMPLE | 52 | src_fract | `unsigned int` |
| _SAMPLE | 56 | left_val | `int` |
| _SAMPLE | 60 | right_val | `int` |
| _SAMPLE | 64 | current_buffer | `int` |
| _SAMPLE | 68 | last_buffer | `int` |
| _SAMPLE | 72 | starved | `int` |
| _SAMPLE | 76 | loop_count | `int` |
| _SAMPLE | 80 | loop_start | `int` |
| _SAMPLE | 84 | loop_end | `int` |
| _SAMPLE | 88 | format | `int` |
| _SAMPLE | 92 | flags | `unsigned int` |
| _SAMPLE | 96 | playback_rate | `int` |
| _SAMPLE | 100 | volume | `int` |
| _SAMPLE | 104 | pan | `int` |
| _SAMPLE | 108 | left_scale | `int` |
| _SAMPLE | 112 | right_scale | `int` |
| _SAMPLE | 116 | service_type | `int` |
| _SAMPLE | 120 | SOB | `char *` |
| _SAMPLE | 124 | EOB | `char *` |
| _SAMPLE | 128 | EOS | `char *` |
| _SAMPLE | 132 | user_data | `int[8]` |
| _SAMPLE | 164 | system_data | `int[8]` |
| _SAMPLE | 196 | adpcm | `_ADPCMDATATAG` |
| _SAMPLE | 268 | SOB_IsWin32s | `int` |
| _SAMPLE | 272 | EOB_IsWin32s | `int` |
| _SAMPLE | 276 | EOS_IsWin32s | `int` |
| _SAMPLE | 280 | secondary_buffer | `int` |
| _SAMPLE | 284 | service_interval | `int` |
| _SAMPLE | 288 | service_tick | `int` |
| _SAMPLE | 292 | buffer_segment_size | `int` |
| _SAMPLE | 296 | prev_segment | `int` |
| _SAMPLE | 300 | prev_cursor | `int` |
| _SAMPLE | 304 | bytes_remaining | `int` |
| _SAMPLE | 308 | direct_control | `int` |
| _SAMPLE | 312 | doeob | `int` |
| _SAMPLE | 316 | dosob | `int` |
| _SAMPLE | 320 | doeos | `int` |
| _SAMPLE | 324 | pipeline | `DPINFO[3]` |
| _SAMPLE | 636 | reverb_level | `float` |
| _SAMPLE | 640 | reverb_reflect_time | `float` |
| _SAMPLE | 644 | reverb_decay_time | `float` |
| _SAMPLE | 648 | base_scale | `int` |
| _SCOPETABLE_ENTRY | 0 | EnclosingLevel | `int` |
| _SCOPETABLE_ENTRY | 4 | FilterFunc | `void *` |
| _SCOPETABLE_ENTRY | 8 | HandlerFunc | `void *` |
| _STREAM | 0 | block_oriented | `int` |
| _STREAM | 4 | using_ASI | `int` |
| _STREAM | 8 | ASI | `ASISTAGE *` |
| _STREAM | 12 | samp | `_SAMPLE *` |
| _STREAM | 16 | fileh | `unsigned int` |
| _STREAM | 20 | bufs | `_BYTE *[3]` |
| _STREAM | 32 | bufsizes | `unsigned int[3]` |
| _STREAM | 44 | reset_ASI | `int[3]` |
| _STREAM | 56 | bufstart | `int[3]` |
| _STREAM | 68 | asyncs | `char *[3]` |
| _STREAM | 80 | loadedbufstart | `int[2]` |
| _STREAM | 88 | loadedorder | `int[2]` |
| _STREAM | 96 | loadorder | `int` |
| _STREAM | 100 | bufsize | `int` |
| _STREAM | 104 | readsize | `int` |
| _STREAM | 108 | buf1 | `unsigned int` |
| _STREAM | 112 | size1 | `int` |
| _STREAM | 116 | buf2 | `unsigned int` |
| _STREAM | 120 | size2 | `int` |
| _STREAM | 124 | buf3 | `unsigned int` |
| _STREAM | 128 | size3 | `int` |
| _STREAM | 132 | datarate | `unsigned int` |
| _STREAM | 136 | filerate | `int` |
| _STREAM | 140 | filetype | `int` |
| _STREAM | 144 | fileflags | `unsigned int` |
| _STREAM | 148 | totallen | `int` |
| _STREAM | 152 | substart | `int` |
| _STREAM | 156 | sublen | `int` |
| _STREAM | 160 | subpadding | `int` |
| _STREAM | 164 | blocksize | `unsigned int` |
| _STREAM | 168 | padding | `int` |
| _STREAM | 172 | padded | `int` |
| _STREAM | 176 | loadedsome | `int` |
| _STREAM | 180 | startpos | `unsigned int` |
| _STREAM | 184 | totalread | `unsigned int` |
| _STREAM | 188 | loopsleft | `unsigned int` |
| _STREAM | 192 | error | `unsigned int` |
| _STREAM | 196 | preload | `int` |
| _STREAM | 200 | preloadpos | `unsigned int` |
| _STREAM | 204 | noback | `int` |
| _STREAM | 208 | alldone | `int` |
| _STREAM | 212 | primeamount | `int` |
| _STREAM | 216 | readatleast | `int` |
| _STREAM | 220 | playcontrol | `int` |
| _STREAM | 224 | callback | `char *` |
| _STREAM | 228 | user_data | `int[8]` |
| _STREAM | 260 | next | `char *` |
| _STREAM | 264 | autostreaming | `int` |
| _STREAM | 268 | cb_IsWin32s | `int` |
| _STREAM | 272 | docallback | `int` |
| _SUBMAP | 0 | m_bShow | `BYTE` |
| _SUBMAP | 4 | m_pos | `tagRECT` |
| _SUBMAP | 20 | m_notepos | `tagRECT` |
| _SUBMAP | 36 | m_fposX | `float` |
| _SUBMAP | 40 | m_fposY | `float` |
| _SUBMAP | 44 | m_pMap | `gbTexture *` |
| _SUBMAP | 48 | m_MapLeftToScreenLeft | `int` |
| _SUBMAP | 52 | m_MapLeftToScreenRight | `int` |
| _SUBMAP | 56 | m_MapTopToScreenTop | `int` |
| _SUBMAP | 60 | m_MapTopToScreenBottom | `int` |
| _SUBMAP | 64 | m_NoteLeft | `int` |
| _SUBMAP | 68 | m_NoteRight | `int` |
| _SUBMAP | 72 | m_NoteTop | `int` |
| _SUBMAP | 76 | m_NoteBottom | `int` |
| _Tex_uv | 0 | u | `float` |
| _Tex_uv | 4 | v | `float` |
| _Texture_Info | 0 | _tex_name | `char[512]` |
| _Texture_Info | 512 | _tex_lib | `char[512]` |
| _Texture_Info | 1024 | _tex_libw | `unsigned int` |
| _Texture_Info | 1028 | _tex_libh | `unsigned int` |
| _Texture_Info | 1032 | _tex_origin_x | `unsigned int` |
| _Texture_Info | 1036 | _tex_origin_y | `unsigned int` |
| _Texture_Info | 1040 | _tex_width | `unsigned int` |
| _Texture_Info | 1044 | _tex_height | `unsigned int` |
| _Texture_Info | 1048 | _tex_uvLT | `_Tex_uv` |
| _Texture_Info | 1056 | _tex_uvLB | `_Tex_uv` |
| _Texture_Info | 1064 | _tex_uvRB | `_Tex_uv` |
| _Texture_Info | 1072 | _tex_uvRT | `_Tex_uv` |
| _Texture_Info | 1080 | _tex_mode | `unsigned int` |
| _Texture_Info | 1084 | _tex_valid | `BYTE` |
| _Texture_uv | 0 | u | `float` |
| _Texture_uv | 4 | v | `float` |
| _TimeMgr | 0 | newtick | `unsigned int` |
| _TimeMgr | 4 | oldtick | `unsigned int` |
| _TimeMgr | 8 | bNote | `BYTE` |
| _TypeDescriptor | 0 | pVFTable | `char *` |
| _TypeDescriptor | 4 | spare | `char *` |
| _UDACCEL | 0 | nSec | `unsigned int` |
| _UDACCEL | 4 | nInc | `unsigned int` |
| _UIPOS | 0 | nameCRC | `unsigned int` |
| _UIPOS | 4 | nXPos | `int` |
| _UIPOS | 8 | nYPos | `int` |
| _XCPT_ACTION | 0 | XcptNum | `unsigned int` |
| _XCPT_ACTION | 4 | SigNum | `int` |
| _XCPT_ACTION | 8 | XcptAction | `char *` |
| _better_note | 0 | best_second | `int` |
| _better_note | 4 | best_num | `int` |
| _btnOPTDATA | 0 | pData | `_BYTE *` |
| _btnOPTDATA | 4 | width | `unsigned int` |
| _btnOPTDATA | 8 | height | `unsigned int` |
| _btnOPTDATA | 12 | bpp | `unsigned int` |
| _count_string | 0 | Length | `signed __int16` |
| _count_string | 2 | MaximumLength | `signed __int16` |
| _count_string | 4 | Buffer | `char *` |
| _cpinfo | 0 | MaxCharSize | `unsigned int` |
| _cpinfo | 4 | DefaultChar | `_BYTE[2]` |
| _cpinfo | 6 | LeadByte | `_BYTE[12]` |
| _s__CatchableType | 0 | properties | `unsigned int` |
| _s__CatchableType | 4 | pType | `_TypeDescriptor *` |
| _s__CatchableType | 8 | thisDisplacement | `_PMD` |
| _s__CatchableType | 20 | sizeOrOffset | `int` |
| _s__CatchableType | 24 | copyFunction | `char *` |
| _s__CatchableTypeArray | 0 | nCatchableTypes | `int` |
| _strflt | 0 | sign | `int` |
| _strflt | 4 | decpt | `int` |
| _strflt | 8 | flag | `int` |
| _strflt | 12 | mantissa | `char *` |
| code_page_info | 0 | code_page | `int` |
| code_page_info | 4 | mbulinfo | `unsigned __int16[6]` |
| code_page_info | 16 | rgrange | `_BYTE[8][4]` |
| doubleint | 0 | twoints | `int[2]` |
| errentry | 0 | oscode | `unsigned int` |
| errentry | 4 | errnocode | `int` |
| gbAABBox | 0 | min | `gbVec3D` |
| gbAABBox | 12 | max | `gbVec3D` |
| gbActor | 88 | pBody | `gbActorDef *` |
| gbActor | 92 | curSkin | `int` |
| gbActor | 96 | pMixInfo | `gbMixActInfo *` |
| gbActor | 100 | NumMixInfo | `int` |
| gbActor | 104 | pExpNode | `gbActorExpNode *` |
| gbActor | 108 | nExpNode | `int` |
| gbActor | 112 | MaxExpNode | `int` |
| gbActorDef | 24 | pShadowEffect | `gbRenderEffect *[2]` |
| gbActorDef | 88 | m_nFilledSlot | `int` |
| gbActorExpNode | 0 | name | `unsigned int` |
| gbActorExpNode | 4 | toworld | `gbMatrix4` |
| gbActorExpNode | 68 | cache | `gbMatrix4` |
| gbActorMgr | 0 | AllActorDef | `gbResManager` |
| gbAnimKey | 0 | time | `float` |
| gbAnimKey | 4 | flags | `unsigned int` |
| gbAnimScript | 0 | BeginPos | `int` |
| gbAnimScript | 4 | EndPos | `int` |
| gbAnimScript | 8 | CurPos | `int` |
| gbAnimScript | 12 | Var_Flt | `float[8]` |
| gbAnimScript | 44 | Var_Int | `int[8]` |
| gbAnimScript | 76 | AnimSpeed | `float` |
| gbAnimScript | 80 | Vel | `gbVec3D` |
| gbAnimScript | 92 | Accel | `gbVec3D` |
| gbAnimScript | 104 | Offset | `gbVec3D` |
| gbAnimScript | 116 | IsHide | `int` |
| gbAnimScript | 120 | CurTime | `double` |
| gbAnimScript | 128 | NextTime | `double` |
| gbAudioManager | 0 | hStreamArray | `_STREAM *[3]` |
| gbAudioManager | 12 | StreamStatus | `int[3]` |
| gbAudioManager | 24 | h2DDriver | `_DIG_DRIVER *` |
| gbAudioManager | 28 | h3DProvider | `unsigned int` |
| gbAudioManager | 32 | Attach3D | `SoundAttachObj[10]` |
| gbAudioManager | 152 | Attach2D | `SoundAttachObj[4]` |
| gbAudioManager | 200 | CurTime | `unsigned int` |
| gbAudioManager | 204 | S_3DMasterVol | `float` |
| gbAudioManager | 208 | S_2DMasterVol | `float` |
| gbAudioManager | 212 | MusicMasterVol | `float` |
| gbAudioManager | 216 | hListener | `h3DPOBJECT *` |
| gbAudioManager | 220 | ListenerPos | `gbVec3D` |
| gbAudioManager | 232 | SndDataMgr | `gbResManager` |
| gbAudioMgrDesc | 0 | frequence | `unsigned int` |
| gbAudioMgrDesc | 4 | bits | `unsigned int` |
| gbAudioMgrDesc | 8 | channels | `unsigned int` |
| gbAudioMgrDesc | 12 | provider | `char[256]` |
| gbBaseMesh | 24 | Effect_RefCount | `int` |
| gbBaseMesh | 28 | ObjName | `char[32]` |
| gbBaseMesh | 60 | VertFVF | `unsigned int` |
| gbBaseMesh | 64 | pSections | `gbMeshSection *` |
| gbBaseMesh | 68 | nSection | `int` |
| gbBaseMesh | 72 | MemCache | `gbMeshMemCache` |
| gbBaseMesh | 88 | BoundBox | `gbAABBox` |
| gbBaseMesh | 112 | CurTime | `float` |
| gbBaseMesh | 116 | pGfxMgr | `gbGfxManager *` |
| gbBinkVideo | 4 | m_pos | `tagPOINT` |
| gbBinkVideo | 12 | m_hBink | `BINK *` |
| gbBinkVideo | 16 | m_Cpk | `CPK` |
| gbBinkVideo | 917964 | m_Cpk2 | `CPK` |
| gbCamControler | 8 | pCamera | `gbCamera *` |
| gbCamControler | 16 | CtrlTime | `double` |
| gbCamControler | 24 | CtrlAge | `double` |
| gbCamera | 0 | fov | `float` |
| gbCamera | 4 | OrthoSize | `float` |
| gbCamera | 8 | Wscreen | `float` |
| gbCamera | 12 | Hscreen | `float` |
| gbCamera | 16 | zNear | `float` |
| gbCamera | 20 | zFar | `float` |
| gbCamera | 24 | Viewport | `gbViewPort` |
| gbCamera | 48 | Plane | `float[4][6]` |
| gbCamera | 144 | numPlane | `int` |
| gbCamera | 148 | ViewMatrix | `gbMatrix4` |
| gbCamera | 212 | InvVMatrix | `gbMatrix4` |
| gbCamera | 276 | pControl | `gbCamControler *[16]` |
| gbCamera | 340 | CurCtrl | `int` |
| gbCamera | 344 | pGfxMgr | `gbGfxManager *` |
| gbCamera | 348 | eyeLoc | `gbVec3D` |
| gbCamera | 360 | eyeDir | `gbQuaternion` |
| gbChain1D | 0 | m_Head | `gbChain1DNode *` |
| gbChain1D | 4 | m_Tail | `gbChain1DNode *` |
| gbChain1D | 8 | m_numNode | `int` |
| gbChain1D | 12 | m_Cur | `gbChain1DNode *` |
| gbChain1DNode | 4 | next | `gbChain1DNode *` |
| gbClearParam | 0 | color | `unsigned int` |
| gbClearParam | 4 | depth | `float` |
| gbClearParam | 8 | stencil | `int` |
| gbClearParam | 12 | clearflag | `unsigned int` |
| gbColorFlt | 0 | Red | `float` |
| gbColorFlt | 4 | Green | `float` |
| gbColorFlt | 8 | Blue | `float` |
| gbColorFlt | 12 | Alpha | `float` |
| gbColorQuad | 0 | Color | `unsigned int` |
| gbColorQuadChannels | 0 | Blue | `BYTE` |
| gbColorQuadChannels | 1 | Green | `BYTE` |
| gbColorQuadChannels | 2 | Red | `BYTE` |
| gbColorQuadChannels | 3 | Alpha | `BYTE` |
| gbCursorRes | 24 | m_pSurface | `IDirect3DSurface9 *` |
| gbCursorRes | 28 | m_OriginX | `int` |
| gbCursorRes | 32 | m_OriginY | `int` |
| gbDropDesc | 0 | unitsize | `float` |
| gbDropDesc | 4 | range | `float` |
| gbDropDesc | 8 | emitrate | `int` |
| gbDropDesc | 12 | minlife | `float` |
| gbDropDesc | 16 | maxlife | `float` |
| gbDropDesc | 20 | minvelocity | `float` |
| gbDropDesc | 24 | maxvelocity | `float` |
| gbDropDesc | 28 | minheight | `float` |
| gbDropDesc | 32 | maxheight | `float` |
| gbDropGroup | 8 | m_MaxUnit | `int` |
| gbDropGroup | 12 | m_nAliveUnit | `int` |
| gbDropGroup | 16 | m_UnitSize | `float` |
| gbDropGroup | 20 | m_Range | `float` |
| gbDropGroup | 24 | m_EmitRate | `int` |
| gbDropGroup | 28 | m_MinLife | `float` |
| gbDropGroup | 32 | m_MaxLife | `float` |
| gbDropGroup | 36 | m_MinEmitVel | `float` |
| gbDropGroup | 40 | m_MaxEmitVel | `float` |
| gbDropGroup | 44 | m_MinHeight | `float` |
| gbDropGroup | 48 | m_MaxHeight | `float` |
| gbDropGroup | 56 | m_LastFrameTime | `double` |
| gbDropGroup | 64 | m_LeftTimeAccum | `float` |
| gbDropGroup | 68 | m_pUnits | `gbDropUnit *` |
| gbDropGroup | 72 | m_pTex | `gbTexture *` |
| gbDropGroup | 76 | m_pEffect | `gbRenderEffect *` |
| gbDropUnit | 0 | life | `float` |
| gbDropUnit | 4 | velocity | `gbVec3D` |
| gbDropUnit | 16 | curpos | `gbVec3D` |
| gbDropUnit | 28 | lastpos | `gbVec3D` |
| gbDynVertBuf | 0 | pGfxMgr | `gbGfxManager *` |
| gbDynVertBuf | 4 | Type | `gbPoolType` |
| gbDynVertBuf | 8 | VertNum | `int` |
| gbDynVertBuf | 12 | VertType | `unsigned int` |
| gbDynVertBuf | 16 | Stride | `int` |
| gbDynVertBuf | 20 | BaseIndex | `int` |
| gbDynVertBuf | 24 | LockVertNum | `int` |
| gbDynVertBuf | 28 | pXYZ | `float *` |
| gbDynVertBuf | 32 | pNormal | `float *` |
| gbDynVertBuf | 36 | pColor1 | `gbColorQuad *` |
| gbDynVertBuf | 40 | pColor2 | `gbColorQuad *` |
| gbDynVertBuf | 44 | pUV | `float *[4]` |
| gbEffectMgr | 12 | m_pGfxMgr | `gbGfxManager *` |
| gbEffectMgr | 16 | m_pWhiteTex | `gbTexture *` |
| gbEffectMgr | 20 | m_pGrayTex | `gbTexture *` |
| gbEffectMgr | 24 | m_pDefEffect | `gbRenderEffect *` |
| gbEffectMgr | 28 | m_AllHandle | `int[64]` |
| gbEffectMgr | 2076 | m_nHandle | `int` |
| gbEffectMgr | 2080 | pCurEffect | `gbRenderEffect *` |
| gbEffectMgr | 2084 | bDoPassOutside | `int` |
| gbEmitterData | 0 | curdir | `gbVec3D` |
| gbEmitterData | 12 | elerandvel_max | `float` |
| gbEmitterData | 16 | elerandvel_min | `float` |
| gbEmitterData | 20 | emissionrate_max | `float` |
| gbEmitterData | 24 | emissionrate_min | `float` |
| gbEmitterData | 28 | elelifetime_max | `float` |
| gbEmitterData | 32 | elelifetime_min | `float` |
| gbEmitterData | 40 | accumulate_part | `double` |
| gbEmitterShape | 0 | intervec | `gbVec3D *` |
| gbEmitterShape | 4 | disarray | `float *` |
| gbEmitterShape | 8 | m_iVecnum | `int` |
| gbEmitterShape | 12 | curmat | `gbMatrix4` |
| gbEmitterSphere | 0 | hotspot | `float` |
| gbEmitterSphere | 4 | falloff | `float` |
| gbEmitterSquare | 0 | min | `gbVec3D` |
| gbEmitterSquare | 12 | max | `gbVec3D` |
| gbFogParam | 0 | type | `int` |
| gbFogParam | 4 | color | `unsigned int` |
| gbFogParam | 20 | mode | `int` |
| gbFogParam | 24 | start | `float` |
| gbFogParam | 28 | end | `float` |
| gbFogParam | 32 | density | `float` |
| gbFogParam | 36 | plane | `float[4]` |
| gbGammaRamp | 0 | red | `unsigned __int16[256]` |
| gbGammaRamp | 512 | green | `unsigned __int16[256]` |
| gbGammaRamp | 1024 | blue | `unsigned __int16[256]` |
| gbGeomNode | 88 | CacheToW | `gbMatrix4` |
| gbGeomNode | 152 | OffMat | `gbMatrix4` |
| gbGeomNode | 216 | PosCtrl | `gbKeyControler *` |
| gbGeomNode | 220 | ScaleCtrl | `gbKeyControler *` |
| gbGeomNode | 224 | RotCtrl | `gbKeyControler *` |
| gbGeomNode | 228 | DegScale | `float` |
| gbGeomNode | 232 | UseControl | `int` |
| gbGeomNode | 236 | pScript | `gbAnimScript *` |
| gbGeomNode | 240 | CurTime | `double` |
| gbGeomNode | 248 | AnimMaxTime | `float` |
| gbGeomNode | 252 | nLoop | `int` |
| gbGeomNode | 256 | nLoopPast | `int` |
| gbGeomNode | 260 | bBlade | `int` |
| gbGeomNode | 264 | pMesh | `gbBaseMesh *` |
| gbGeomNode | 268 | pTags | `gbTagNode *` |
| gbGeomNode | 272 | nTag | `int` |
| gbGeomNode | 276 | nXBlade | `int` |
| gbGeomNode | 280 | pXTagBlade | `gbTagXBladeNode *` |
| gbGeomQuad | 0 | vec | `gbVec3D[4]` |
| gbGeomQuad | 48 | su | `float` |
| gbGeomQuad | 52 | sv | `float` |
| gbGeomQuad | 56 | eu | `float` |
| gbGeomQuad | 60 | ev | `float` |
| gbGeomQuad | 64 | color | `unsigned int` |
| gbGfxCaps | 0 | CanWindow | `int` |
| gbGfxCaps | 4 | TexMemSize | `unsigned int` |
| gbGfxCaps | 8 | MaxOnePassTex | `int` |
| gbGfxCaps | 12 | MaxTexWidth | `int` |
| gbGfxCaps | 16 | MaxTexHeight | `int` |
| gbGfxDriverInfo | 0 | type | `int` |
| gbGfxDriverInfo | 4 | subtype | `int` |
| gbGfxDriverInfo | 8 | width | `int` |
| gbGfxDriverInfo | 12 | height | `int` |
| gbGfxDriverInfo | 16 | colorbits | `int` |
| gbGfxDriverInfo | 20 | depthbits | `int` |
| gbGfxDriverInfo | 24 | stensilbits | `int` |
| gbGfxDriverInfo | 28 | nbackbuf | `int` |
| gbGfxDriverInfo | 32 | fullscreen | `int` |
| gbGfxDriverInfo | 36 | refreshrate | `int` |
| gbGfxDriverInfo | 40 | winname | `char[128]` |
| gbGfxDriverInfo | 168 | hinst | `unsigned int` |
| gbGfxDriverInfo | 172 | hgfxwnd | `unsigned int` |
| gbGfxDriverInfo | 176 | newwindow | `int` |
| gbGfxDriverInfo | 180 | waitforverticalblank | `int` |
| gbGfxManager | 8 | hGfxWnd | `unsigned int` |
| gbGfxManager | 12 | DrvInfo | `gbGfxDriverInfo` |
| gbGfxManager | 196 | pVertPoolMgr | `gbVertPoolMgr *` |
| gbGfxManager | 200 | pEffectMgr | `gbEffectMgr *` |
| gbGfxManager | 204 | pTexResMgr | `gbResManager *` |
| gbGfxManager | 208 | pFontMgr | `gbPrintFontMgr *` |
| gbGfxManager | 212 | pMatrixStack | `gbMatrixStack *[4]` |
| gbGfxManager | 228 | ViewMatrix | `gbMatrix4` |
| gbGfxManager | 292 | InvViewMatrix | `gbMatrix4` |
| gbGfxManager | 356 | WorldMatrix | `gbMatrix4` |
| gbGfxManager | 420 | CurZBias | `int` |
| gbGfxManager | 424 | bWireMode | `int` |
| gbGfxManager | 428 | AmbientLight | `gbColorFlt` |
| gbGfxManager | 444 | fSelfIllum | `float` |
| gbGfxManager | 448 | pSceneGraph | `gbSceneGraph *` |
| gbGfxManager | 452 | Viewport | `gbViewPort` |
| gbGfxManager | 476 | ClearParam | `gbClearParam` |
| gbGfxManager | 496 | LastTime | `double` |
| gbGfxManager | 504 | CurTime | `double` |
| gbGfxManager | 512 | LastTick | `unsigned int` |
| gbGfxManager | 516 | CurTick | `unsigned int` |
| gbGfxManager | 520 | Stat | `gbGfxStatistic` |
| gbGfxManager | 568 | AllLight | `gbLight[8]` |
| gbGfxManager | 1400 | LightEnable | `int[8]` |
| gbGfxManager | 1432 | FogParam | `gbFogParam` |
| gbGfxManager | 1484 | m_pCurTexture | `gbTexture *[8]` |
| gbGfxManager_D3D | 1520 | m_d3dEnumeration | `CD3DEnumeration` |
| gbGfxManager_D3D | 1564 | m_bWindowed | `int` |
| gbGfxManager_D3D | 1568 | m_rcWindowClient | `tagRECT` |
| gbGfxManager_D3D | 1584 | m_rcWindowBounds | `tagRECT` |
| gbGfxManager_D3D | 1600 | m_dwWindowStyle | `unsigned int` |
| gbGfxManager_D3D | 1604 | m_hWnd | `HWND__ *` |
| gbGfxManager_D3D | 1608 | m_bMinimized | `unsigned char` |
| gbGfxManager_D3D | 1609 | m_bMaximized | `unsigned char` |
| gbGfxManager_D3D | 1610 | m_bClipCursorWhenFullscreen | `unsigned char` |
| gbGfxManager_D3D | 1611 | m_bShowCursorWhenFullscreen | `unsigned char` |
| gbGfxManager_D3D | 1612 | m_bActive | `unsigned char` |
| gbGfxManager_D3D | 1616 | m_dwCreateFlags | `unsigned int` |
| gbGfxManager_D3D | 1620 | m_DriverBug | `D3DDriverBug` |
| gbGfxManager_D3D | 1624 | m_CursorMgr | `gbResManager` |
| gbGfxManager_D3D | 1636 | m_pActiveCursor | `gbCursorRes *` |
| gbGfxManager_D3D | 1640 | m_bShowCursor | `int` |
| gbGfxManager_D3D | 1644 | m_bSoftVPMode | `int` |
| gbGfxManager_D3D | 1648 | m_d3dSettings | `CD3DSettings` |
| gbGfxManager_D3D | 1756 | m_d3dpp | `_D3DPRESENT_PARAMETERS_` |
| gbGfxManager_D3D | 1812 | m_pD3D | `IDirect3D9 *` |
| gbGfxManager_D3D | 1816 | m_pd3dDevice | `IDirect3DDevice9 *` |
| gbGfxManager_D3D | 1820 | m_d3dCaps | `_D3DCAPS9` |
| gbGfxManager_D3D | 2124 | m_d3dsdBackBuffer | `_D3DSURFACE_DESC` |
| gbGfxManager_D3D | 2156 | m_strDeviceStats | `char[90]` |
| gbGfxManager_D3D | 2248 | m_ErrorCode | `int` |
| gbGfxManager_D3D | 2252 | m_bDeviceLost | `int` |
| gbGfxManager_D3D | 2256 | m_pBackBuffer | `IDirect3DSurface9 *` |
| gbGfxManager_D3D | 2260 | m_DXTSupported | `int[5]` |
| gbGfxManager_D3D | 2280 | m_pCacheVB | `IDirect3DVertexBuffer9 *` |
| gbGfxManager_D3D | 2284 | m_pCacheIB | `IDirect3DIndexBuffer9 *` |
| gbGfxStatistic | 0 | nRFaces | `int` |
| gbGfxStatistic | 4 | nRVerts | `int` |
| gbGfxStatistic | 8 | nStaticVerts | `int` |
| gbGfxStatistic | 12 | nStaticIndex | `int` |
| gbGfxStatistic | 16 | nSrcVerts | `int` |
| gbGfxStatistic | 20 | nSrcIndex | `int` |
| gbGfxStatistic | 24 | nTexSwitch | `int` |
| gbGfxStatistic | 28 | FPS | `float` |
| gbGfxStatistic | 32 | TimeAccum | `double` |
| gbGfxStatistic | 40 | Frame | `unsigned int` |
| gbGfxStatistic | 44 | PrevFrame | `unsigned int` |
| gbImage2D | 0 | ImgInfo | `gbImage2DInfo` |
| gbImage2D | 128 | Width | `int` |
| gbImage2D | 132 | Height | `int` |
| gbImage2D | 136 | PixelFmt | `gbPixelFormat` |
| gbImage2D | 180 | BitCount | `int` |
| gbImage2D | 184 | pBits | `_BYTE *` |
| gbImage2D | 188 | pPalette | `gbColorQuad *` |
| gbImage2D | 192 | numPalEntry | `int` |
| gbImage2D | 196 | ColorKey | `gbColorQuad` |
| gbImage2DInfo | 0 | isdiskinfo | `int` |
| gbImage2DInfo | 4 | goal | `int` |
| gbImage2DInfo | 8 | ngrade | `int` |
| gbImage2DInfo | 12 | detail | `int[8]` |
| gbImage2DInfo | 44 | wdiv | `int[8]` |
| gbImage2DInfo | 76 | hdiv | `int[8]` |
| gbImage2DInfo | 108 | wrap_u | `int` |
| gbImage2DInfo | 112 | wrap_v | `int` |
| gbImage2DInfo | 116 | mipmap | `int` |
| gbImage2DInfo | 120 | minfilter | `int` |
| gbImage2DInfo | 124 | magfilter | `int` |
| gbIndexBubble | 8 | pPool | `gbIndexPool *` |
| gbIndexBubble | 12 | Type | `gbPrimType` |
| gbIndexBubble | 16 | nIndex | `int` |
| gbIndexBubble | 20 | BubSize | `int` |
| gbIndexBubble | 24 | Start | `int` |
| gbIndexBubble | 28 | StartVert | `int` |
| gbIndexBubble | 32 | EndVert | `int` |
| gbIndexPool | 8 | Type | `gbPoolType` |
| gbIndexPool | 12 | EleSize | `int` |
| gbIndexPool | 16 | pMemBuf | `char *` |
| gbIndexPool | 20 | TotalIndex | `int` |
| gbIndexPool | 24 | FreeIndexBub | `gbChain1D` |
| gbIndexPool | 40 | UsedIndexBub | `gbChain1D` |
| gbKeyControler | 4 | pKeys | `char *` |
| gbKeyControler | 8 | KeySize | `int` |
| gbKeyControler | 12 | KeyType | `gbKeyType` |
| gbKeyControler | 16 | nKey | `int` |
| gbLight | 0 | type | `int` |
| gbLight | 4 | diffuse | `gbColorFlt` |
| gbLight | 20 | specular | `gbColorFlt` |
| gbLight | 36 | ambient | `gbColorFlt` |
| gbLight | 52 | position | `gbVec3D` |
| gbLight | 64 | direction | `gbVec3D` |
| gbLight | 76 | range | `float` |
| gbLight | 80 | falloff | `float` |
| gbLight | 84 | attenuation0 | `float` |
| gbLight | 88 | attenuation1 | `float` |
| gbLight | 92 | attenuation2 | `float` |
| gbLight | 96 | theta | `float` |
| gbLight | 100 | phi | `float` |
| gbLightObj | 8 | m_LightType | `int` |
| gbLightObj | 12 | m_Color | `gbColorFlt` |
| gbLightObj | 28 | m_Ambient | `gbColorFlt` |
| gbLightObj | 44 | m_UseDiffuse | `int` |
| gbLightObj | 48 | m_UseSpecular | `int` |
| gbLightObj | 52 | m_NearStart | `float` |
| gbLightObj | 56 | m_NearEnd | `float` |
| gbLightObj | 60 | m_FarStart | `float` |
| gbLightObj | 64 | m_FarEnd | `float` |
| gbLightObj | 68 | m_DecayType | `int` |
| gbLightObj | 72 | m_DecayRadius | `float` |
| gbLightObj | 76 | m_LightShape | `int` |
| gbLightObj | 80 | m_HotSize | `float` |
| gbLightObj | 84 | m_Falloff | `float` |
| gbLightObj | 88 | m_Aspect | `float` |
| gbLightObj | 92 | m_BoundSphere | `gbSphere` |
| gbLightObj | 108 | m_SysLight | `gbLight` |
| gbLightObj | 212 | m_BakedLight | `int` |
| gbMaterial | 0 | diffuse | `gbColorFlt` |
| gbMaterial | 16 | ambient | `gbColorFlt` |
| gbMaterial | 32 | specular | `gbColorFlt` |
| gbMaterial | 48 | emissive | `gbColorFlt` |
| gbMaterial | 64 | power | `float` |
| gbMatrix4 | 4 | xy | `float` |
| gbMatrix4 | 8 | xz | `float` |
| gbMatrix4 | 12 | xw | `float` |
| gbMatrix4 | 16 | yx | `float` |
| gbMatrix4 | 20 | yy | `float` |
| gbMatrix4 | 24 | yz | `float` |
| gbMatrix4 | 28 | yw | `float` |
| gbMatrix4 | 32 | zx | `float` |
| gbMatrix4 | 36 | zy | `float` |
| gbMatrix4 | 40 | zz | `float` |
| gbMatrix4 | 44 | zw | `float` |
| gbMatrix4 | 48 | tx | `float` |
| gbMatrix4 | 52 | ty | `float` |
| gbMatrix4 | 56 | tz | `float` |
| gbMatrix4 | 60 | tw | `float` |
| gbMatrix4Flat | 0 | xx | `float` |
| gbMatrix4Flat | 4 | xy | `float` |
| gbMatrix4Flat | 8 | xz | `float` |
| gbMatrix4Flat | 12 | xw | `float` |
| gbMatrix4Flat | 16 | yx | `float` |
| gbMatrix4Flat | 20 | yy | `float` |
| gbMatrix4Flat | 24 | yz | `float` |
| gbMatrix4Flat | 28 | yw | `float` |
| gbMatrix4Flat | 32 | zx | `float` |
| gbMatrix4Flat | 36 | zy | `float` |
| gbMatrix4Flat | 40 | zz | `float` |
| gbMatrix4Flat | 44 | zw | `float` |
| gbMatrix4Flat | 48 | tx | `float` |
| gbMatrix4Flat | 52 | ty | `float` |
| gbMatrix4Flat | 56 | tz | `float` |
| gbMatrix4Flat | 60 | tw | `float` |
| gbMatrixStack | 0 | pMatBuf | `gbMatrix4 *` |
| gbMatrixStack | 4 | MaxVol | `int` |
| gbMatrixStack | 8 | CurPos | `int` |
| gbMatrixStack | 12 | ValidFlag | `int` |
| gbMeshMemCache | 0 | pVerts | `gbVec3D *` |
| gbMeshMemCache | 4 | nVert | `int` |
| gbMeshMemCache | 8 | pIndices | `unsigned __int16 *` |
| gbMeshMemCache | 12 | nIndex | `int` |
| gbMeshSection | 0 | BlendFlags | `int` |
| gbMeshSection | 4 | bBakedLight | `int` |
| gbMeshSection | 8 | TexArray | `gbTextureArray` |
| gbMeshSection | 76 | Material | `gbMaterial` |
| gbMeshSection | 144 | pIndexBub | `gbIndexBubble *` |
| gbMeshSection | 148 | VertStart | `unsigned int` |
| gbMeshSection | 152 | VertEnd | `unsigned int` |
| gbMeshSection | 156 | Point | `gbVec3D` |
| gbMeshSection | 168 | pCustomEffect | `gbRenderEffect *` |
| gbMeshSection | 172 | TexAnim | `gbTexFlipAnim` |
| gbMixActInfo | 0 | state | `int` |
| gbMixActInfo | 4 | name | `unsigned int` |
| gbMixActInfo | 8 | weight | `float` |
| gbMixActInfo | 12 | time | `unsigned int` |
| gbMixActInfo | 16 | start | `unsigned int` |
| gbMixActInfo | 20 | end | `unsigned int` |
| gbMixActInfo | 24 | duration | `unsigned int` |
| gbMixActInfo | 28 | allbone | `int` |
| gbMixActInfo | 32 | endmsg | `unsigned int` |
| gbNBTreeNode | 8 | pFather | `gbNBTreeNode *` |
| gbNBTreeNode | 12 | children | `gbChain1D` |
| gbNodeMsgObj | 0 | msgid | `int` |
| gbNodeMsgObj | 4 | param | `unsigned int[2]` |
| gbNodeMsgObj | 12 | pfrom | `gbVisNode *` |
| gbNodeMsgPayload | 0 | msgid | `int` |
| gbNodeMsgPayload | 4 | param | `unsigned int[2]` |
| gbNodeMsgPayload | 12 | _pad0C | `int` |
| gbOBBox | 0 | trans | `Matrix4` |
| gbOBBox | 64 | xlen | `float` |
| gbOBBox | 68 | ylen | `float` |
| gbOBBox | 72 | zlen | `float` |
| gbPartEmitter | 0 | name | `char[64]` |
| gbPartEmitter | 64 | relative_position | `gbVec3D` |
| gbPartEmitter | 76 | emission_scope | `gbVec3D` |
| gbPartEmitter | 88 | cs_name | `char[64]` |
| gbPartEmitter | 152 | emitter_shape | `int` |
| gbPartEmitter | 156 | cyclelen_start | `float` |
| gbPartEmitter | 160 | cyclelen_end | `float` |
| gbPartEmitter | 164 | cycle_loop | `int` |
| gbPartEmitter | 168 | lighton | `int` |
| gbPartEmitter | 172 | square | `gbEmitterSquare` |
| gbPartEmitter | 196 | sphere | `gbEmitterSphere` |
| gbPartEmitter | 204 | shape | `gbEmitterShape` |
| gbPartEmitter | 280 | m_fSpeedMulti | `float` |
| gbPartEmitter | 284 | m_fSizeMulti | `float` |
| gbPartEmitter | 288 | DirectionCtrl | `gbPartParamControl` |
| gbPartEmitter | 4868 | RandomVelCtrl | `gbPartParamControl` |
| gbPartEmitter | 9448 | EmitRateCtrl | `gbPartParamControl` |
| gbPartEmitter | 14028 | UnitLifeCtrl | `gbPartParamControl` |
| gbPartEmitter | 18608 | UnitScaleCtrl | `gbPartParamControl` |
| gbPartEmitter | 23188 | UnitRotCtrl | `gbPartParamControl` |
| gbPartGroupParam | 0 | particle_name | `char[32]` |
| gbPartGroupParam | 32 | particle_lighting | `int` |
| gbPartGroupParam | 36 | gravity | `float` |
| gbPartGroupParam | 40 | noresis | `float` |
| gbPartGroupParam | 44 | aresis_velocity | `int` |
| gbPartGroupParam | 48 | aresis_size | `int` |
| gbPartGroupParam | 52 | aresis_constant | `float` |
| gbPartGroupParam | 56 | filename | `char[256]` |
| gbPartGroupParam | 312 | particlesize | `int` |
| gbPartGroupParam | 316 | animation_type | `int` |
| gbPartGroupParam | 320 | animation_fps | `int` |
| gbPartGroupParam | 324 | random_1stframe | `int` |
| gbPartGroupParam | 328 | random_rotstart | `int` |
| gbPartGroupParam | 332 | random_rotend | `int` |
| gbPartGroupParam | 336 | random_rotdir | `int` |
| gbPartGroupParam | 340 | random_mirroringx | `int` |
| gbPartGroupParam | 344 | random_mirroringy | `int` |
| gbPartGroupParam | 348 | chainnum | `int` |
| gbPartGroupParam | 352 | framenum | `int` |
| gbPartGroupParam | 356 | blendmode | `int` |
| gbPartGroupParam | 360 | SizeCtrl | `gbPartParamControl` |
| gbPartGroupParam | 4940 | RotCtrl | `gbPartParamControl` |
| gbPartGroupParam | 9520 | AlphaCtrl | `gbPartParamControl` |
| gbPartGroupParam | 14100 | RGBCtrl | `gbPartParamControl` |
| gbPartGroupParam | 18680 | TexArray | `gbTextureArray` |
| gbPartGroupParam | 18748 | pREffect | `gbRenderEffect *` |
| gbPartParamControl | 0 | nCurve | `int` |
| gbPartParamControl | 4 | nCtrlPt | `int` |
| gbPartParamControl | 8 | Name | `char[64]` |
| gbPartParamControl | 72 | Descript | `char[128]` |
| gbPartParamControl | 200 | MinPt | `gbVec3D` |
| gbPartParamControl | 212 | MaxPt | `gbVec3D` |
| gbPartParamControl | 224 | CtrlPt | `gbVec3D[20][3]` |
| gbPartParamControl | 944 | Segment | `gbVec3D[101][3]` |
| gbParticleEffect | 88 | Name | `char[64]` |
| gbParticleEffect | 152 | nPartGroup | `int` |
| gbParticleEffect | 156 | nGroupParam | `int` |
| gbParticleEffect | 160 | nEmitter | `int` |
| gbParticleEffect | 164 | pPartGroups | `gbParticleGroup *` |
| gbParticleEffect | 168 | pGroupParams | `gbPartGroupParam *` |
| gbParticleEffect | 172 | pEmitters | `gbPartEmitter *` |
| gbParticleEffect | 176 | maxparticle | `int` |
| gbParticleEffect | 180 | emittedto | `int` |
| gbParticleEffect | 184 | npwmr | `int` |
| gbParticleEffect | 188 | pParticles | `gbParticleUnit *` |
| gbParticleEffect | 192 | gravity | `float` |
| gbParticleEffect | 196 | timescale | `float` |
| gbParticleEffect | 200 | maxfps | `int` |
| gbParticleEffect | 204 | camerafollow | `int` |
| gbParticleEffect | 208 | camerafollowdis | `float` |
| gbParticleEffect | 212 | gravityeffect | `int` |
| gbParticleEffect | 216 | frontplane | `float` |
| gbParticleEffect | 220 | backplane | `float` |
| gbParticleEffect | 224 | objectoffset | `gbVec3D` |
| gbParticleEffect | 236 | systemoffset | `gbVec3D` |
| gbParticleEffect | 248 | systemvelocity | `gbVec3D` |
| gbParticleEffect | 264 | CurTime | `double` |
| gbParticleEffect | 272 | ElapseTime | `double` |
| gbParticleEffect | 280 | SpaceScale | `float` |
| gbParticleEffect | 284 | m_ToWorld | `gbMatrix4` |
| gbParticleGroup | 0 | Name | `char[64]` |
| gbParticleGroup | 64 | Life | `double` |
| gbParticleGroup | 72 | EmitterData | `gbEmitterData` |
| gbParticleGroup | 120 | pGroupParam | `gbPartGroupParam *` |
| gbParticleGroup | 124 | pEmitter | `gbPartEmitter *` |
| gbParticleGroup | 128 | pAllUnits | `gbParticleUnit *` |
| gbParticleGroup | 132 | MaxUnits | `int` |
| gbParticleGroup | 136 | nAlivePart | `int` |
| gbParticleGroup | 140 | pParticleEffect | `gbParticleEffect *` |
| gbParticleUnit | 0 | alive | `int` |
| gbParticleUnit | 8 | life | `double` |
| gbParticleUnit | 16 | age | `float` |
| gbParticleUnit | 20 | looptex | `int` |
| gbParticleUnit | 24 | chainindex | `int` |
| gbParticleUnit | 28 | velocity | `gbVec3D` |
| gbParticleUnit | 40 | resistance | `gbVec3D` |
| gbParticleUnit | 52 | curpos | `gbVec3D` |
| gbParticleUnit | 64 | cursize | `float` |
| gbParticleUnit | 68 | curvertexalpha | `float` |
| gbParticleUnit | 72 | currgbcolor | `gbColorQuad` |
| gbParticleUnit | 76 | rotation | `float` |
| gbParticleUnit | 80 | dir | `int` |
| gbPixelFormat | 0 | Type | `gbPixelFmtType` |
| gbPixelFormat | 4 | Bpp | `int` |
| gbPixelFormat | 8 | Pal | `gbColorQuad *` |
| gbPixelFormat | 12 | r_mask | `unsigned int` |
| gbPixelFormat | 16 | g_mask | `unsigned int` |
| gbPixelFormat | 20 | b_mask | `unsigned int` |
| gbPixelFormat | 24 | a_mask | `unsigned int` |
| gbPixelFormat | 28 | r_shift | `unsigned int` |
| gbPixelFormat | 32 | g_shift | `unsigned int` |
| gbPixelFormat | 36 | b_shift | `unsigned int` |
| gbPixelFormat | 40 | a_shift | `unsigned int` |
| gbPrintFont | 0 | pGfxMgr | `gbGfxManager *` |
| gbPrintFont | 4 | ptInfo | `FontPrintInfo *` |
| gbPrintFont | 8 | pSortInfo | `FontSortInfoObj *` |
| gbPrintFont | 12 | maxInfo | `int` |
| gbPrintFont | 16 | numInfo | `int` |
| gbPrintFont | 20 | pt3DInfo | `FontPrint3DInfo *` |
| gbPrintFont | 24 | num3DInfo | `int` |
| gbPrintFont | 28 | max3DInfo | `int` |
| gbPrintFont | 32 | strBuffer | `_BYTE *` |
| gbPrintFont | 36 | maxStrBuffer | `int` |
| gbPrintFont | 40 | curStrLoc | `int` |
| gbPrintFont | 44 | curColor | `gbColorQuad` |
| gbPrintFont | 48 | ScaleX | `float` |
| gbPrintFont | 52 | ScaleY | `float` |
| gbPrintFont | 56 | PitchX | `float` |
| gbPrintFont | 60 | PitchY | `float` |
| gbPrintFont | 64 | ZValue | `float` |
| gbPrintFont | 68 | pEffect | `gbRenderEffect *[2]` |
| gbPrintFontMgr | 0 | pAllFont | `gbPrintFont *[5]` |
| gbQuaternion | 0 | x | `float` |
| gbQuaternion | 4 | y | `float` |
| gbQuaternion | 8 | z | `float` |
| gbQuaternion | 12 | w | `float` |
| gbRay | 0 | Origin | `gbVec3D` |
| gbRay | 12 | Direction | `gbVec3D` |
| gbRefObject | 4 | RefCount | `int` |
| gbRenderEffect | 24 | m_pEffect | `ID3DXEffect *` |
| gbRenderEffect | 28 | m_Flags | `unsigned int` |
| gbRenderEffect | 32 | m_DeclHandle | `IDirect3DVertexDeclaration9 *` |
| gbRenderEffect | 36 | m_ParamHandle | `unsigned int[8]` |
| gbRenderInfoObj | 0 | pNode | `gbVisNode *` |
| gbRenderInfoObj | 4 | Z | `float` |
| gbRenderInfoObj | 8 | Param | `unsigned int` |
| gbRenderInfoObj | 12 | pEffect | `gbRenderEffect *` |
| gbRenderInfoObj | 16 | pTexArray | `gbTextureArray *` |
| gbRenderInfoObj | 20 | Priority | `int` |
| gbRenderInfoObj | 24 | Flags | `unsigned int` |
| gbRenderInfoObj | 28 | EffectFlag | `unsigned int` |
| gbRenderInfoObj | 32 | ViewMat | `gbMatrix4` |
| gbRenderInfoObj | 96 | pAllLight | `gbVolModNode *[2]` |
| gbRenderInfoObj | 104 | pAllFog | `gbVolModNode *[2]` |
| gbResManager | 0 | AllResPt | `char[12]` |
| gbResource | 8 | pName | `char *` |
| gbResource | 12 | NameCrc32 | `unsigned int` |
| gbResource | 16 | IsLoaded | `int` |
| gbResource | 20 | pMgr | `gbResManager *` |
| gbSceneGraph | 0 | pAllRObj | `gbRenderInfoObj *` |
| gbSceneGraph | 4 | index | `int[4096]` |
| gbSceneGraph | 16388 | CurRObjPos | `int` |
| gbSceneGraph | 16392 | pnodebuf | `gbOctreeNode *[4096]` |
| gbSceneGraph | 32776 | pOctree | `gbOctree *` |
| gbSceneGraph | 32780 | pSceneRoot | `gbVisNode *` |
| gbSceneGraph | 32784 | pAllShadowObj | `gbRenderInfoObj[16]` |
| gbSceneGraph | 34576 | nShadowObj | `int` |
| gbSceneGraph | 34580 | pAllVolMod | `gbVolModNode *[256]` |
| gbSceneGraph | 35604 | VolModXform | `gbMatrix4[256]` |
| gbSceneGraph | 51988 | nVolModNode | `int` |
| gbSceneGraph | 51992 | pGfxMgr | `gbGfxManager *` |
| gbSceneGraph | 51996 | pSkyBox | `gbVisNode *` |
| gbSceneGraph | 52000 | pShadowQuadEffect | `gbRenderEffect *` |
| gbSceneGraph | 52004 | pCamera | `gbCamera *` |
| gbSceneGraph | 52008 | pBladeMgr | `gbBladeMgr *` |
| gbSceneGraph | 52012 | m_WaterNode | `gbRenderInfoObj[128]` |
| gbSceneGraph | 66348 | m_nWaterNode | `int` |
| gbSceneGraph | 66352 | m_CVDNode | `gbRenderInfoObj[8]` |
| gbSceneGraph | 67248 | m_nCVDNode | `int` |
| gbSceneGraph | 67252 | m_renderOctree | `unsigned char` |
| gbSceneGraph | 67253 | m_renderWater | `unsigned char` |
| gbSceneGraph | 67254 | m_bAttachSceneWater | `unsigned char` |
| gbSnow | 80 | m_VelXZ | `float` |
| gbSound2DNode | 0 | pAudioMgr | `gbAudioManager *` |
| gbSound2DNode | 4 | hSample | `_SAMPLE *` |
| gbSound2DNode | 8 | nLoop | `int` |
| gbSound2DNode | 12 | Volume | `float` |
| gbSound3DNode | 0 | pAudioMgr | `gbAudioManager *` |
| gbSound3DNode | 4 | hSample | `h3DPOBJECT *` |
| gbSound3DNode | 8 | Position | `gbVec3D` |
| gbSound3DNode | 20 | Velocity | `gbVec3D` |
| gbSound3DNode | 32 | Orientation | `gbVec3D` |
| gbSound3DNode | 44 | EffectType | `int` |
| gbSound3DNode | 48 | Volume | `float` |
| gbSound3DNode | 52 | nLoop | `int` |
| gbSound3DNode | 56 | MinDist | `float` |
| gbSound3DNode | 60 | MaxDist | `float` |
| gbSoundData | 24 | pimage | `char *` |
| gbSphere | 0 | r | `float` |
| gbSphere | 4 | center | `gbVec3D` |
| gbSurfaceDesc | 0 | width | `int` |
| gbSurfaceDesc | 4 | height | `int` |
| gbSurfaceDesc | 8 | format | `gbPixelFmtType` |
| gbSurfaceDesc | 12 | pitch | `int` |
| gbSurfaceDesc | 16 | pbits | `char *` |
| gbTagNode | 0 | name | `char[32]` |
| gbTagNode | 32 | origin | `gbVec3D` |
| gbTagNode | 44 | userdata | `unsigned int` |
| gbTagXBladeNode | 0 | tagNodeA | `gbTagNode` |
| gbTagXBladeNode | 48 | tagNodeB | `gbTagNode` |
| gbTagXBladeNode | 96 | pBladeMgr | `gbBladeMgr *` |
| gbTexFlipAnim | 0 | ppAllTex | `gbTexture **` |
| gbTexFlipAnim | 4 | AnimIndex | `int` |
| gbTexFlipAnim | 8 | nTex | `int` |
| gbTexFlipAnim | 12 | interval | `int` |
| gbTexture | 24 | Width | `int` |
| gbTexture | 28 | Height | `int` |
| gbTexture | 32 | pTexImage | `gbImage2D *` |
| gbTexture | 36 | InFmt | `gbPixelFormat` |
| gbTexture | 80 | nLevels | `int` |
| gbTextureArray | 0 | pTexPt | `gbTexture *[16]` |
| gbTextureArray | 64 | nTex | `int` |
| gbTexture_D3D | 84 | pTex | `IDirect3DBaseTexture9 *` |
| gbTexture_D3D | 88 | pDS | `IDirect3DSurface9 *` |
| gbTexture_D3D | 92 | m_ImgFormat | `unsigned int` |
| gbUIQuad | 0 | sx | `float` |
| gbUIQuad | 4 | sy | `float` |
| gbUIQuad | 8 | ex | `float` |
| gbUIQuad | 12 | ey | `float` |
| gbUIQuad | 16 | su | `float` |
| gbUIQuad | 20 | sv | `float` |
| gbUIQuad | 24 | eu | `float` |
| gbUIQuad | 28 | ev | `float` |
| gbUIQuad | 32 | z | `float` |
| gbUIQuad | 36 | color | `unsigned int` |
| gbVFile1 | 0 | OpenMode | `unsigned int` |
| gbVFile1 | 4 | EntryAddr | `unsigned int` |
| gbVFile1 | 8 | FileSize | `unsigned int` |
| gbVFile1 | 12 | pFilePath | `char[256]` |
| gbVFile1 | 268 | m_NowAddr | `unsigned int` |
| gbVFileSystem | 0 | IsInit | `int` |
| gbVFileSystem | 4 | rtDirectory | `char *` |
| gbVFileSystem | 8 | pFileBuffer | `gbVFile *` |
| gbVFileSystem | 12 | Type | `int` |
| gbVFileSystem | 16 | m_pckfp | `_iobuf *` |
| gbVFileSystem | 20 | m_itemcount | `unsigned int` |
| gbVFileSystem | 24 | m_cpk | `CPK` |
| gbVec2D | 0 | x | `float` |
| gbVec2D | 4 | y | `float` |
| gbVec3D | 0 | x | `float` |
| gbVec3D | 4 | y | `float` |
| gbVec3D | 8 | z | `float` |
| gbVec4D | 0 | x | `float` |
| gbVec4D | 4 | y | `float` |
| gbVec4D | 8 | z | `float` |
| gbVec4D | 12 | w | `float` |
| gbVertPoolMgr | 0 | StaticPool | `gbChain1D[32]` |
| gbVertPoolMgr | 512 | StaticPoolFVF | `unsigned int[32]` |
| gbVertPoolMgr | 640 | StaticIndex | `gbChain1D` |
| gbVertPoolMgr | 656 | pDynPool | `gbDynVertBuf *[32]` |
| gbVertPoolMgr | 784 | DynPoolFVF | `unsigned int[32]` |
| gbVertPoolMgr | 912 | ReadOnlyPool | `gbChain1D[32]` |
| gbVertPoolMgr | 1424 | ReadOnlyPoolFVF | `unsigned int[32]` |
| gbVertPoolMgr | 1552 | VertPoolSize | `int` |
| gbVertPoolMgr | 1556 | IndexPoolSize | `int` |
| gbVertPoolMgr | 1560 | DynVertPoolSize | `int` |
| gbVertPoolMgr | 1564 | ReadOnlyPoolSize | `int` |
| gbVertPoolMgr | 1568 | pGfxMgr | `gbGfxManager *` |
| gbVertexBubble | 8 | pPool | `gbVertexPool *` |
| gbVertexBubble | 12 | Start | `int` |
| gbVertexBubble | 16 | BubSize | `int` |
| gbVertexBubble | 20 | nVerts | `int` |
| gbVertexBubble | 24 | pXYZ | `float *` |
| gbVertexBubble | 28 | pNormal | `float *` |
| gbVertexBubble | 32 | pColor1 | `gbColorQuad *` |
| gbVertexBubble | 36 | pColor2 | `gbColorQuad *` |
| gbVertexBubble | 40 | pUV | `float *[4]` |
| gbVertexElement | 0 | stream | `unsigned __int16` |
| gbVertexElement | 2 | offset | `unsigned __int16` |
| gbVertexElement | 4 | type | `unsigned char` |
| gbVertexElement | 5 | method | `unsigned char` |
| gbVertexElement | 6 | usage | `unsigned char` |
| gbVertexElement | 7 | usageindex | `unsigned char` |
| gbVertexPool | 8 | pGfxMgr | `gbGfxManager *` |
| gbVertexPool | 12 | pMemBuf | `char *` |
| gbVertexPool | 16 | VertNum | `int` |
| gbVertexPool | 20 | VertType | `unsigned int` |
| gbVertexPool | 24 | Stride | `int` |
| gbVertexPool | 28 | FreeVertBub | `gbChain1D` |
| gbVertexPool | 44 | UsedVertBub | `gbChain1D` |
| gbViewPort | 0 | x | `int` |
| gbViewPort | 4 | y | `int` |
| gbViewPort | 8 | width | `int` |
| gbViewPort | 12 | height | `int` |
| gbViewPort | 16 | minz | `float` |
| gbViewPort | 20 | maxz | `float` |
| gbVisNode | 28 | pSceneGraph | `gbSceneGraph *` |
| gbVisNode | 52 | Priority | `int` |
| gbVisNode | 56 | TimeScale | `float` |
| gbVisNode | 60 | bShow | `int` |
| gbVisNode | 64 | bDoShadow | `int` |
| gbVisNode | 68 | pCullObj | `gbOctreeNode *` |
| gbVisNode | 72 | pCullPrev | `gbVisNode *` |
| gbVisNode | 76 | pCullNext | `gbVisNode *` |
| gbVisNode | 80 | BlendParam | `float` |
| gbVisNode | 84 | BlendFlag | `NodeBlend` |
| gbVolModNode | 88 | m_ToWorld | `gbMatrix4` |
| gbVolModNode | 152 | m_ToView | `gbMatrix4` |
| gbVolModNode | 216 | m_pModObj | `float *` |
| graph | 0 | curve_num | `int` |
| graph | 4 | cp_num | `int` |
| graph | 8 | graphname | `char[64]` |
| graph | 72 | describe | `char[128]` |
| graph | 200 | min | `D3DXVECTOR3` |
| graph | 212 | max | `D3DXVECTOR3` |
| graph | 224 | disdata | `D3DXVECTOR3[20][3]` |
| graph | 944 | realdata | `D3DXVECTOR3[20][3]` |
| graph | 1664 | interpolate | `char[256]` |
| h3DPOBJECT | 0 | junk | `unsigned int` |
| ioinfo | 0 | osfhnd | `int` |
| ioinfo | 4 | osfile | `char` |
| ioinfo | 5 | pipech | `char` |
| lconv | 0 | decimal_point | `char *` |
| lconv | 4 | thousands_sep | `char *` |
| lconv | 8 | grouping | `char *` |
| lconv | 12 | int_curr_symbol | `char *` |
| lconv | 16 | currency_symbol | `char *` |
| lconv | 20 | mon_decimal_point | `char *` |
| lconv | 24 | mon_thousands_sep | `char *` |
| lconv | 28 | mon_grouping | `char *` |
| lconv | 32 | positive_sign | `char *` |
| lconv | 36 | negative_sign | `char *` |
| lconv | 40 | int_frac_digits | `char` |
| lconv | 41 | frac_digits | `char` |
| lconv | 42 | p_cs_precedes | `char` |
| lconv | 43 | p_sep_by_space | `char` |
| lconv | 44 | n_cs_precedes | `char` |
| lconv | 45 | n_sep_by_space | `char` |
| lconv | 46 | p_sign_posn | `char` |
| lconv | 47 | n_sign_posn | `char` |
| localVar0 | 0 | l_ebp | `unsigned int` |
| localVar0 | 4 | l_esi | `unsigned int` |
| localVar0 | 8 | l_edi | `unsigned int` |
| localVar1 | 0 | l_absXY | `signed __int64` |
| localVar1 | 8 | l_absZW | `signed __int64` |
| localVar1 | 16 | l_ebp | `unsigned int` |
| localVar1 | 20 | l_esi | `unsigned int` |
| localVar1 | 24 | l_edi | `unsigned int` |
| localVar2 | 0 | l_Matrix | `SSE4xMatrix` |
| localVar2 | 256 | l_ebp | `unsigned int` |
| localVar2 | 260 | l_esi | `unsigned int` |
| localVar2 | 264 | l_edi | `unsigned int` |
| m_RoleState | 0 | m_Headbk | `UIStatic` |
| m_RoleState | 152 | m_Head | `UIButton` |
| m_RoleState | 496 | m_Name | `UIStatic` |
| m_RoleState | 648 | m_Jing | `UIStatic` |
| m_RoleState | 800 | m_JingBar | `UIProgressBar` |
| m_RoleState | 1044 | m_JingVal | `UIStatic` |
| m_RoleState | 1196 | m_Shen | `UIStatic` |
| m_RoleState | 1348 | m_ShenBar | `UIProgressBar` |
| m_RoleState | 1592 | m_ShenVal | `UIStatic` |
| m_RoleState | 1744 | m_Qi | `UIStatic` |
| m_RoleState | 1896 | m_QiBar | `UIProgressBar` |
| m_RoleState | 2140 | m_QiVal | `UIStatic` |
| m_RoleState | 2292 | m_AttFrameHead | `UIStatic` |
| m_RoleState | 2444 | m_F | `UIStatic` |
| m_RoleState | 2596 | m_W | `UIStatic` |
| m_RoleState | 2748 | m_S | `UIStatic` |
| m_RoleState | 2900 | m_Y | `UIStatic` |
| m_RoleState | 3052 | m_Exp | `UIStatic` |
| m_RoleState | 3204 | m_RoleAtt | `UIStatic[5]` |
| m_RoleState | 3964 | m_NeedArrow | `UIStatic` |
| m_RoleState | 4116 | m_NeedRc | `tagRECT` |
| magic_tab | 0 | magic_id | `unsigned int` |
| magic_tab | 4 | min_usetime | `int` |
| magic_tab | 8 | max_usetime | `int` |
| magic_tab | 12 | lv | `int` |
| me_RoleState | 0 | m_Headbk | `UIStatic` |
| me_RoleState | 152 | m_Head | `UIButton` |
| me_RoleState | 496 | m_Name | `UIStatic` |
| me_RoleState | 648 | m_Jing | `UIStatic` |
| me_RoleState | 800 | m_JingBar | `UIProgressBar` |
| me_RoleState | 1044 | m_JingVal | `UIStatic` |
| me_RoleState | 1196 | m_Shen | `UIStatic` |
| me_RoleState | 1348 | m_ShenBar | `UIProgressBar` |
| me_RoleState | 1592 | m_ShenVal | `UIStatic` |
| me_RoleState | 1744 | m_Qi | `UIStatic` |
| me_RoleState | 1896 | m_QiBar | `UIProgressBar` |
| me_RoleState | 2140 | m_QiVal | `UIStatic` |
| me_RoleState | 2292 | m_AttFrameHead | `UIStatic` |
| me_RoleState | 2444 | m_AttFramePose | `UIStatic` |
| me_RoleState | 2596 | m_RoleAtt | `UIStatic[10]` |
| me_RoleState | 4116 | m_RoleAttCng | `UIStatic[10]` |
| me_RoleState | 5636 | m_RoleAttEqual | `UIStatic[10]` |
| me_RoleState | 7156 | m_EquipPic | `UIStatic` |
| me_RoleState | 7308 | m_EquipWeapon | `UIButton` |
| me_RoleState | 7652 | m_EquipHat | `UIButton` |
| me_RoleState | 7996 | m_EquipCloth | `UIButton` |
| me_RoleState | 8340 | m_EquipShoes | `UIButton` |
| me_RoleState | 8684 | m_EquipAdorn1 | `UIButton` |
| me_RoleState | 9028 | m_EquipAdorn2 | `UIButton` |
| p_RoleState | 0 | m_Headbk | `UIStatic` |
| p_RoleState | 152 | m_Head | `UIButton` |
| p_RoleState | 496 | m_Name | `UIStatic` |
| p_RoleState | 648 | m_Jing | `UIStatic` |
| p_RoleState | 800 | m_JingBar | `UIProgressBar` |
| p_RoleState | 1044 | m_JingVal | `UIStatic` |
| p_RoleState | 1196 | m_Shen | `UIStatic` |
| p_RoleState | 1348 | m_ShenBar | `UIProgressBar` |
| p_RoleState | 1592 | m_ShenVal | `UIStatic` |
| p_RoleState | 1744 | m_Qi | `UIStatic` |
| p_RoleState | 1896 | m_QiBar | `UIProgressBar` |
| p_RoleState | 2140 | m_QiVal | `UIStatic` |
| p_RoleState | 2292 | m_AttFrameHead | `UIStatic` |
| p_RoleState | 2444 | m_F | `UIStatic` |
| p_RoleState | 2596 | m_W | `UIStatic` |
| p_RoleState | 2748 | m_S | `UIStatic` |
| p_RoleState | 2900 | m_Y | `UIStatic` |
| p_RoleState | 3052 | m_Exp | `UIStatic` |
| p_RoleState | 3204 | m_RoleAtt | `UIStatic[5]` |
| p_RoleState | 3964 | m_NeedArrow | `UIStatic` |
| p_RoleState | 4116 | m_NeedRc | `tagRECT` |
| pcmwaveformat_tag | 0 | wf | `waveformat_tag` |
| pcmwaveformat_tag | 14 | wBitsPerSample | `unsigned __int16` |
| primitive | 4 | _vertices | `char *[4]` |
| primitive | 20 | _plane | `char *[13]` |
| primitive | 72 | _userFlags | `unsigned int` |
| rterrmsgs | 0 | rterrno | `int` |
| rterrmsgs | 4 | rterrtxt | `char *` |
| sCollision | 0 | collider | `char[4]` |
| sCollision | 4 | collisionPlane | `char[52]` |
| sCollision | 56 | collisionDistance | `float` |
| sCollision | 60 | collisionType | `CollisionType` |
| s_RoleState | 0 | m_Headbk | `UIStatic` |
| s_RoleState | 152 | m_Head | `UIStatic` |
| s_RoleState | 304 | m_Name | `UIStatic` |
| s_RoleState | 456 | m_Jing | `UIStatic` |
| s_RoleState | 608 | m_JingBar | `UIProgressBar` |
| s_RoleState | 852 | m_JingVal | `UIStatic` |
| s_RoleState | 1004 | m_Shen | `UIStatic` |
| s_RoleState | 1156 | m_ShenBar | `UIProgressBar` |
| s_RoleState | 1400 | m_ShenVal | `UIStatic` |
| s_RoleState | 1552 | m_Qi | `UIStatic` |
| s_RoleState | 1704 | m_QiBar | `UIProgressBar` |
| s_RoleState | 1948 | m_QiVal | `UIStatic` |
| s_RoleState | 2100 | m_Shade | `UIStatic` |
| s_RoleState | 2252 | m_Portrait | `UIStatic` |
| s_RoleState | 2404 | m_Level | `UIStatic` |
| s_RoleState | 2556 | m_ExpVal | `UIStatic` |
| s_RoleState | 2708 | m_NextLv | `UIStatic` |
| s_RoleState | 2860 | m_WuLing | `UIStatic[5]` |
| s_RoleState | 3620 | m_FWSY | `UIStatic` |
| s_RoleState | 3772 | m_FWSYrc | `tagRECT` |
| s_SpecialPropItem | 0 | m_ItemId | `unsigned int` |
| s_SpecialPropItem | 4 | m_CanUse | `BYTE` |
| scAsmDecoder | 0 | m_stack | `scVarStack *` |
| scCmdDef | 0 | pfun | `char *` |
| scCmdDef | 4 | paramlist | `_BYTE[8]` |
| scCmdDef | 12 | paramnum | `unsigned __int16` |
| scGlobalUserVar | 8 | name | `char[16]` |
| scSCEFile | 0 | m_fp | `gbVFile *` |
| scSCEFile | 4 | m_blocks | `char[16]` |
| scScriptBlock | 0 | id | `unsigned int` |
| scScriptBlock | 4 | desc | `_BYTE[64]` |
| scScriptBlock | 68 | codesize | `unsigned int` |
| scScriptBlock | 72 | pcodedata | `_BYTE *` |
| scScriptBlock | 76 | uservarnum | `unsigned __int16` |
| scScriptBlock | 80 | uservar | `scUserVarInfo *` |
| scScriptBlock | 84 | ref | `int` |
| scUserVarInfo | 0 | type | `BYTE` |
| scUserVarInfo | 2 | initlen | `unsigned __int16` |
| scUserVarInfo | 4 | initdata | `_BYTE *` |
| scVARIANT | 0 | type | `BYTE` |
| scVARIANT | 2 | len | `unsigned __int16` |
| scVARIANT | 4 | data | `scVARIANT_data` |
| scVARIANT_data | 0 | as_float | `float` |
| scVARIANT_data | 0 | as_int | `float` |
| scVarStack | 0 | m_counter | `int` |
| scVarStack | 4 | m_vararray | `scVARIANT[32]` |
| sg_customshape | 0 | intervec | `D3DXVECTOR3 *` |
| sg_customshape | 4 | disarray | `float *` |
| sg_customshape | 8 | m_iVecnum | `int` |
| sg_customshape | 12 | curmat | `D3DXMATRIX` |
| sg_emission_control | 0 | name | `char[64]` |
| sg_emission_control | 64 | particle_pointer | `int` |
| sg_emission_control | 68 | emitter_pointer | `int` |
| sg_emission_control | 72 | elapsetime | `float` |
| sg_emission_control | 76 | total_elatime | `float` |
| sg_emission_control | 80 | maxparticle | `int` |
| sg_emission_control | 84 | first_time | `int` |
| sg_emission_control | 88 | cyclelength | `float` |
| sg_emission_control | 92 | replacestyle | `int` |
| sg_emission_control | 96 | particle_array | `sg_particle_data[400]` |
| sg_emission_control | 36896 | emitter | `sg_emitter_data` |
| sg_emission_control | 36940 | pparticle | `sg_particle *` |
| sg_emission_control | 36944 | pemitter | `sg_emitter *` |
| sg_emission_control | 36948 | scene_pointer | `sg_particle_scene *` |
| sg_emitter | 0 | name | `char[64]` |
| sg_emitter | 64 | relative_position | `D3DXVECTOR3` |
| sg_emitter | 76 | emission_scope | `D3DXVECTOR3` |
| sg_emitter | 88 | cs_name | `char[64]` |
| sg_emitter | 152 | emitter_shape | `int` |
| sg_emitter | 156 | cyclelen_start | `float` |
| sg_emitter | 160 | cyclelen_end | `float` |
| sg_emitter | 164 | cycle_loop | `int` |
| sg_emitter | 168 | lighton | `int` |
| sg_emitter | 172 | m_fSpeedMulti | `float` |
| sg_emitter | 176 | m_fSizeMulti | `float` |
| sg_emitter | 180 | direction_graph | `direction_emitter_graph` |
| sg_emitter | 5480 | elerandvec_graph | `elerandvec_emitter_graph` |
| sg_emitter | 10780 | emissionrate_graph | `emissionrate_emitter_graph` |
| sg_emitter | 16080 | elelife_graph | `elelife_emitter_graph` |
| sg_emitter | 21380 | sizemulti_graph | `sizemulti_emitter_graph` |
| sg_emitter | 26680 | rotmulti_graph | `rotmulti_emitter_graph` |
| sg_emitter | 31980 | square | `sg_emitter_square` |
| sg_emitter | 32004 | sphere | `sg_emitter_sphere` |
| sg_emitter | 32012 | m_pCS | `sg_customshape` |
| sg_emitter_data | 0 | alive | `int` |
| sg_emitter_data | 4 | tval | `float` |
| sg_emitter_data | 8 | curdir | `D3DXVECTOR3` |
| sg_emitter_data | 20 | elerandvel_max | `float` |
| sg_emitter_data | 24 | elerandvel_min | `float` |
| sg_emitter_data | 28 | emissionrate_max | `int` |
| sg_emitter_data | 32 | emissionrate_min | `int` |
| sg_emitter_data | 36 | elelifetime_max | `float` |
| sg_emitter_data | 40 | elelifetime_min | `float` |
| sg_emitter_sphere | 0 | hotspot | `float` |
| sg_emitter_sphere | 4 | falloff | `float` |
| sg_emitter_square | 0 | min | `D3DXVECTOR3` |
| sg_emitter_square | 12 | max | `D3DXVECTOR3` |
| sg_particle | 0 | particle_name | `char[32]` |
| sg_particle | 32 | particle_lighting | `int` |
| sg_particle | 36 | gravity | `float` |
| sg_particle | 40 | noresis | `float` |
| sg_particle | 44 | aresis_velocity | `int` |
| sg_particle | 48 | aresis_size | `int` |
| sg_particle | 52 | aresis_constant | `float` |
| sg_particle | 56 | filename | `char[256]` |
| sg_particle | 312 | particlesize | `int` |
| sg_particle | 316 | framenums | `int` |
| sg_particle | 320 | framesets | `int` |
| sg_particle | 324 | animation_type | `int` |
| sg_particle | 328 | animation_fps | `int` |
| sg_particle | 332 | random_1stframe | `int` |
| sg_particle | 336 | random_rotstart | `int` |
| sg_particle | 340 | random_rotend | `int` |
| sg_particle | 344 | random_rotdir | `int` |
| sg_particle | 348 | random_mirroringx | `int` |
| sg_particle | 352 | random_mirroringy | `int` |
| sg_particle | 356 | m_fSizeMulti | `float` |
| sg_particle | 360 | chainnum | `int` |
| sg_particle | 364 | framenum | `int` |
| sg_particle | 368 | blendmode | `int` |
| sg_particle | 372 | size_graph | `size_particle_graph` |
| sg_particle | 5672 | rotation_graph | `rotation_particle_graph` |
| sg_particle | 10972 | vertexalpha_graph | `vertexalpha_particle_graph` |
| sg_particle | 16272 | rgbcolor_graph | `rgbcolor_particle_graph` |
| sg_particle_data | 0 | alive | `int` |
| sg_particle_data | 4 | elapsetime | `float` |
| sg_particle_data | 8 | lifetime | `float` |
| sg_particle_data | 12 | tval | `float` |
| sg_particle_data | 16 | looptex | `int` |
| sg_particle_data | 20 | chainindex | `int` |
| sg_particle_data | 24 | velocity | `D3DXVECTOR3` |
| sg_particle_data | 36 | resistance | `D3DXVECTOR3` |
| sg_particle_data | 48 | curpos | `D3DXVECTOR3` |
| sg_particle_data | 60 | cursize | `float` |
| sg_particle_data | 64 | curvertexalpha | `float` |
| sg_particle_data | 68 | currgbcolor | `D3DXCOLOR` |
| sg_particle_data | 84 | rotation | `float` |
| sg_particle_data | 88 | dir | `int` |
| sg_particle_scene | 0 | name | `char[256]` |
| sg_particle_scene | 256 | emission_controlnum | `int` |
| sg_particle_scene | 260 | particle_num | `int` |
| sg_particle_scene | 264 | emitter_num | `int` |
| sg_particle_scene | 268 | active_particle | `int` |
| sg_particle_scene | 272 | active_emitter | `int` |
| sg_particle_scene | 276 | active_emissioncontrol | `int` |
| sg_particle_scene | 280 | econtrol | `sg_emission_control[4]` |
| sg_particle_scene | 148088 | ecenable | `int[4]` |
| sg_particle_scene | 148104 | cur_sel | `int` |
| sg_particle_scene | 148108 | particle | `sg_particle[4]` |
| sg_particle_scene | 234396 | emitter | `sg_emitter[4]` |
| sg_particle_scene | 362748 | maxparticle | `int` |
| sg_particle_scene | 362752 | emittedto | `int` |
| sg_particle_scene | 362756 | npwmr | `int` |
| sg_particle_scene | 362760 | gravity | `float` |
| sg_particle_scene | 362764 | timescale | `float` |
| sg_particle_scene | 362768 | maxfps | `int` |
| sg_particle_scene | 362772 | camerafollow | `int` |
| sg_particle_scene | 362776 | camerafollowdis | `float` |
| sg_particle_scene | 362780 | gravityeffect | `int` |
| sg_particle_scene | 362784 | frontplane | `float` |
| sg_particle_scene | 362788 | backplane | `float` |
| sg_particle_scene | 362792 | objectoffset | `D3DXVECTOR3` |
| sg_particle_scene | 362804 | systemoffset | `D3DXVECTOR3` |
| sg_particle_scene | 362816 | systemvelocity | `D3DXVECTOR3` |
| sg_particle_scene | 362828 | m_fMultisize | `float` |
| skill_tab | 0 | skill_id | `unsigned int` |
| skill_tab | 4 | lv | `int` |
| st_Manager | 0 | m_Type | `BYTE` |
| st_Manager | 1 | m_Dicker | `BYTE` |
| subPARAM | 0 | f1 | `float` |
| subPARAM | 12 | f2 | `float` |
| subPARAM | 24 | f3 | `float` |
| subPARAM | 36 | f4 | `float` |
| subPARAM | 48 | f5 | `float` |
| subPARAM | 60 | f6 | `float` |
| t3DModel | 0 | numOfObjects | `int` |
| t3DModel | 4 | numOfMaterials | `int` |
| t3DModel | 8 | pMaterials | `char[16]` |
| t3DModel | 24 | pObject | `char[16]` |
| t3DObject | 0 | numOfVerts | `int` |
| t3DObject | 4 | numOfFaces | `int` |
| t3DObject | 8 | numTexVertex | `int` |
| t3DObject | 12 | materialID | `int` |
| t3DObject | 16 | bHasTexture | `BYTE` |
| t3DObject | 17 | strName | `char[255]` |
| t3DObject | 272 | pVerts | `D3DXVECTOR3 *` |
| t3DObject | 276 | pNormals | `D3DXVECTOR3 *` |
| t3DObject | 280 | pTexVerts | `D3DXVECTOR2 *` |
| t3DObject | 284 | pFaces | `tFace *` |
| tChunk | 0 | ID | `unsigned __int16` |
| tChunk | 4 | length | `unsigned int` |
| tChunk | 8 | bytesRead | `unsigned int` |
| tFace | 0 | vertIndex | `int[3]` |
| tFace | 12 | coordIndex | `int[3]` |
| tMaterialInfo | 0 | strName | `char[255]` |
| tMaterialInfo | 255 | strFile | `char[255]` |
| tMaterialInfo | 510 | color | `_BYTE[3]` |
| tMaterialInfo | 516 | fColor | `float[3]` |
| tMaterialInfo | 528 | texureId | `int` |
| tMaterialInfo | 532 | uTile | `int` |
| tMaterialInfo | 536 | vTile | `float` |
| tMaterialInfo | 540 | uOffset | `float` |
| tMaterialInfo | 544 | vOffset | `float` |
| tag17A7BData | 0 | m_nEffParamBase | `int[3]` |
| tag17A7BData | 12 | m_nEffParam0 | `int` |
| tag17A7BData | 20 | m_nEffParam14 | `int` |
| tag17A7BData | 24 | m_nEffParam1 | `int` |
| tag17A7BData | 28 | m_nEffParam1C | `int` |
| tag17A7BData | 36 | m_nEffParam24 | `int` |
| tag17A7BData | 40 | m_nEffTypeCode | `int` |
| tag17A7BData | 44 | m_nEffParam2C | `int` |
| tag17A8Data | 0 | m_nEffParamBase | `int[3]` |
| tag17A8Data | 12 | m_nEffParam0 | `float` |
| tag17A8Data | 16 | m_nEffParam10 | `int` |
| tag17A8Data | 20 | m_nEffParam14 | `float` |
| tag17A8Data | 24 | m_nEffParam1 | `int` |
| tag17A8Data | 28 | m_nEffParam1C | `int` |
| tag17A8Data | 32 | m_nEffTypeID | `int` |
| tag17A8Data | 36 | m_nEffParam24 | `int` |
| tag17A8Data | 40 | m_nEffTypeCode | `int` |
| tag17A8Data | 44 | m_nEffParam2C | `int` |
| tag17A8Data | 48 | m_nEffParam30 | `int` |
| tag4DWORD | 0 | f1 | `float` |
| tag4DWORD | 4 | f2 | `float` |
| tag4DWORD | 8 | f3 | `float` |
| tag4DWORD | 12 | f4 | `float` |
| tagActionCommand | 0 | cmdType | `unsigned char` |
| tagActionCommand | 4 | pTargetActor | `Actor *` |
| tagActionCommand | 8 | targetY | `float` |
| tagActionCommand | 12 | targetZ | `float` |
| tagActionCommand | 20 | fSpeed | `float` |
| tagActionCommand | 24 | nCmdParam | `int` |
| tagAnimStateSplit | 0 | _anim0 | `char` |
| tagAnimStateSplit | 1 | m_bActionPause | `unsigned char` |
| tagAttackSequen | 0 | fDeltaTime | `float` |
| tagAttackSequen | 4 | fLastTime | `float` |
| tagAttackSequen | 8 | nIndex | `int` |
| tagAttackSequen | 12 | dwID | `unsigned int` |
| tagAttackSequen | 16 | pPic | `UIStatic *` |
| tagAttackSequen | 20 | nSlot1 | `int` |
| tagAttackSequen | 24 | nSlot2 | `int` |
| tagAttackSequen | 28 | nRound | `int` |
| tagAttackSequen | 32 | bySpeed1 | `BYTE` |
| tagAttackSequen | 33 | bySpeed2 | `BYTE` |
| tagAttackSequen | 34 | bSlot2Running | `BYTE` |
| tagAttackSequen | 35 | bPaused | `BYTE` |
| tagAttackSequen | 36 | bValid | `BYTE` |
| tagC10Data | 0 | m_nEffParamBase | `int[2]` |
| tagC10Data | 12 | m_nEffParam0 | `int` |
| tagC10Data | 16 | m_nEffParam10 | `int` |
| tagC10Data | 20 | m_nEffParam14 | `int` |
| tagC10Data | 24 | m_nEffParam1 | `int` |
| tagC10Data | 28 | m_nEffParam1C | `int` |
| tagC10Data | 32 | m_nEffTypeID | `int` |
| tagC10Data | 36 | m_nEffParam24 | `int` |
| tagC10Data | 40 | m_nEffTypeCode | `int` |
| tagC10Data | 44 | m_nEffParam2C | `int` |
| tagC10Data | 48 | m_nEffParam30 | `int` |
| tagC10Data | 52 | m_nEffParam34 | `int` |
| tagC10Data | 56 | m_nEffParam38 | `int` |
| tagCCBStageData | 0 | m_nEffParamBase0 | `int` |
| tagCCBStageData | 20 | m_nEffParam14 | `int` |
| tagCCBStageData | 28 | m_nEffParam1C | `int` |
| tagCCBStageData | 32 | m_nEffTypeID | `int` |
| tagCCBStageData | 40 | m_nEffTypeCode | `int` |
| tagCCT | 0 | fp | `char *[4]` |
| tagCCT | 16 | dwID | `unsigned int` |
| tagCCT | 20 | bValid | `BYTE` |
| tagCCT | 21 | bExecuted | `BYTE` |
| tagCCT | 22 | bFinished | `BYTE` |
| tagCCT | 23 | bSplice | `BYTE` |
| tagCCT | 24 | fStartTime | `float` |
| tagCCT | 28 | fExpectTime | `float` |
| tagCCT | 32 | StartPos | `tagCam` |
| tagCCT | 56 | EndPos | `tagCam` |
| tagCCT | 80 | nStartCam | `int` |
| tagCCT | 84 | nEndCam | `int` |
| tagCCT | 88 | bStartCamValid | `BYTE` |
| tagCCT | 89 | bEndCamValid | `BYTE` |
| tagCCT | 90 | bTimeValid | `BYTE` |
| tagCCT | 91 | bSpeedValid | `BYTE` |
| tagCCT | 92 | bLineMove | `BYTE` |
| tagCCT | 93 | bCircleMove | `BYTE` |
| tagCCT | 94 | bMechanicsMove | `BYTE` |
| tagCCT | 95 | bTimeRevise | `BYTE` |
| tagCCT | 96 | bAbsoluteTime | `BYTE` |
| tagCCT | 97 | bCounterYaw | `BYTE` |
| tagCCT | 98 | bCounterPitch | `BYTE` |
| tagCCT | 99 | bCounterRoll | `BYTE` |
| tagCCT | 100 | bRandSwing | `BYTE` |
| tagCCT | 101 | bSightTrace | `BYTE` |
| tagCCT | 102 | bPosTrace | `BYTE` |
| tagCCT | 104 | nTraceRole | `int` |
| tagCCT | 108 | fStartSpeed | `float` |
| tagCCT | 112 | fInertia | `float` |
| tagCCT | 116 | fAccelerationTime1 | `float` |
| tagCCT | 120 | fAccelerationTime2 | `float` |
| tagCCT | 124 | fAcceleration1 | `float` |
| tagCCT | 128 | fAcceleration2 | `float` |
| tagCCT | 132 | fCircleAngle | `float` |
| tagCCT | 136 | fAngleSpeed | `float` |
| tagCCT | 140 | fCircleCentreX | `float` |
| tagCCT | 144 | fCircleCentreY | `float` |
| tagCCT | 148 | fCircleCentreZ | `float` |
| tagCCT | 152 | fCircleEndX | `float` |
| tagCCT | 156 | fCircleEndY | `float` |
| tagCCT | 160 | fCircleEndZ | `float` |
| tagCCT | 164 | fSwingFre | `float` |
| tagCCT | 168 | fSwing | `float` |
| tagCCT | 172 | fTimeExpiate | `float` |
| tagCCT | 176 | fStartFOV | `float` |
| tagCCT | 180 | fEndFOV | `float` |
| tagCCT | 184 | fStartTracePosX | `float` |
| tagCCT | 188 | fStartTracePosY | `float` |
| tagCCT | 192 | fStartTracePosZ | `float` |
| tagCCT | 196 | dwReserved | `unsigned int[2]` |
| tagCOPYDATASTRUCT | 0 | dwData | `unsigned int` |
| tagCOPYDATASTRUCT | 4 | cbData | `unsigned int` |
| tagCOPYDATASTRUCT | 8 | lpData | `char *` |
| tagCPKHeader | 0 | dwLable | `unsigned int` |
| tagCPKHeader | 4 | dwVersion | `unsigned int` |
| tagCPKHeader | 8 | dwTableStart | `unsigned int` |
| tagCPKHeader | 12 | dwDataStart | `unsigned int` |
| tagCPKHeader | 16 | dwMaxFileNum | `unsigned int` |
| tagCPKHeader | 20 | dwFileNum | `unsigned int` |
| tagCPKHeader | 24 | dwIsFormatted | `unsigned int` |
| tagCPKHeader | 28 | dwSizeOfHeader | `unsigned int` |
| tagCPKHeader | 32 | dwValidTableNum | `unsigned int` |
| tagCPKHeader | 36 | dwMaxTableNum | `unsigned int` |
| tagCPKHeader | 40 | dwFragmentNum | `unsigned int` |
| tagCPKHeader | 44 | dwPackageSize | `unsigned int` |
| tagCPKHeader | 48 | dwReserved | `unsigned int[20]` |
| tagCPKTable | 0 | dwCRC | `unsigned int` |
| tagCPKTable | 4 | dwFlag | `unsigned int` |
| tagCPKTable | 8 | dwFatherCRC | `unsigned int` |
| tagCPKTable | 12 | dwStartPos | `unsigned int` |
| tagCPKTable | 16 | dwPackedSize | `unsigned int` |
| tagCPKTable | 20 | dwOriginSize | `unsigned int` |
| tagCPKTable | 24 | dwExtraInfoSize | `unsigned int` |
| tagCam | 0 | x | `float` |
| tagCam | 4 | y | `float` |
| tagCam | 8 | z | `float` |
| tagCam | 12 | yaw | `_inline_tagCam_yaw` |
| tagCam | 16 | pit | `float` |
| tagCam | 20 | rol | `float` |
| tagCamTask | 0 | fp | `char *[4]` |
| tagCamTask | 16 | dwID | `unsigned int` |
| tagCamTask | 20 | bValid | `BYTE` |
| tagCamTask | 21 | bExecuted | `BYTE` |
| tagCamTask | 22 | bFinished | `BYTE` |
| tagCamTask | 24 | fStartTime | `float` |
| tagCamTask | 28 | fExpectTime | `float` |
| tagCamTask | 32 | StartPos | `tagCam` |
| tagCamTask | 56 | EndPos | `tagCam` |
| tagCmdData | 0 | dwCmdKind | `unsigned int` |
| tagCmdData | 4 | dwItemID | `unsigned int` |
| tagCmdData | 8 | nSrcRole | `int` |
| tagCmdData | 12 | nDestRole | `int` |
| tagCmdData | 16 | bMultiSrcRole | `BYTE` |
| tagCmdData | 17 | bMultiDestRole | `BYTE` |
| tagCmdData | 18 | bSrcRole | `_BYTE[11]` |
| tagCmdData | 29 | m_destRoleView | `_inline_tagCmdData_m_destRoleView` |
| tagCmdData | 40 | bValid | `BYTE` |
| tagCmdDataDestRoleView | 0 | _pad_7 | `_BYTE[7]` |
| tagCmdDataDestRoleView | 7 | pDestRoleOverlay | `void *` |
| tagCombatTaskData | 0 | m_nEffParamBase | `int[2]` |
| tagCombatTaskData | 12 | m_fEffDirX | `float` |
| tagCombatTaskData | 16 | m_nEffParam10 | `int` |
| tagCombatTaskData | 20 | m_fEffDirZ | `float` |
| tagCombatTaskData | 24 | m_nEffParam1 | `int` |
| tagCombatTaskData | 28 | m_nEffParam1C | `int` |
| tagCombatTaskData | 32 | m_nEffTypeID | `float` |
| tagCombatTaskData | 36 | m_nEffParam24 | `int` |
| tagCombatTaskData | 40 | m_nEffTypeCode | `int` |
| tagCombatTaskData | 64 | m_nEffParam40 | `float` |
| tagCombatTaskData | 68 | m_nEffParam44 | `int` |
| tagCombatTaskData | 72 | m_nEffParam48 | `int` |
| tagCombatTaskData | 76 | m_nEffParam4C | `float` |
| tagCombatTaskData | 80 | m_nEffParam50 | `int` |
| tagCombatTaskData | 84 | m_nEffParam2 | `int` |
| tagCombatTaskData | 88 | m_nEffParam58 | `float` |
| tagCombatTaskData | 92 | m_nEffParam5C | `int` |
| tagCombatTaskData | 96 | m_nEffParam3 | `int` |
| tagCombatTaskData | 100 | m_fCombatTime | `float` |
| tagCombatTaskData | 104 | m_nEffParam4 | `int` |
| tagCombatTaskData | 108 | _todo_06C | `int` |
| tagCombatTaskData | 132 | m_nEffParam7 | `float` |
| tagCombatTaskData | 136 | m_fTargetParam | `float` |
| tagCombatTaskData | 140 | m_nEffParam8 | `int` |
| tagCombatTaskData | 144 | _todo_090 | `float` |
| tagCombatTaskData | 148 | m_nEffParam9 | `int` |
| tagCombatTaskData | 152 | m_nEffParam98 | `int` |
| tagCombatTaskData | 156 | m_nEffParam9C | `float` |
| tagCombatTaskData | 160 | m_nEffParamA0 | `int` |
| tagCombatTaskData | 164 | m_nEffParamA4 | `int` |
| tagCombatTaskData | 168 | m_nEffParamA8 | `float` |
| tagCombatTaskData | 172 | m_nEffParamAC | `int` |
| tagCombatTaskData | 176 | m_nEffParamB0 | `int` |
| tagCombatTaskData | 200 | m_nEffParamC8 | `float` |
| tagCombatTaskData | 204 | m_nEffParamCC | `int` |
| tagCombatTaskData | 208 | m_nEffParamD0 | `int` |
| tagCombatTaskData | 212 | m_nEffParamD4 | `float` |
| tagCombatTaskData | 216 | m_nEffParamD8 | `int` |
| tagCombatTaskData | 220 | m_nEffParamDC | `int` |
| tagCombatTaskData | 224 | m_nEffParamE0 | `float` |
| tagCombatTaskData | 228 | m_nEffParamE4 | `int` |
| tagCombatTaskData | 232 | m_nEffParamE8 | `int` |
| tagCombatTaskData | 236 | m_nEffParamEC | `float` |
| tagCombatTaskData | 240 | m_nEffParamF0 | `int` |
| tagCombatTaskData | 244 | _todo_0F4 | `int` |
| tagCombatTaskData | 268 | _todo_10C | `float` |
| tagCombatTaskData | 272 | _todo_110 | `int` |
| tagCombatTaskData | 276 | _todo_114 | `int` |
| tagCombatTaskData | 280 | _todo_118 | `float` |
| tagCombatTaskData | 284 | _todo_11C | `int` |
| tagCombatTaskData | 288 | _todo_120 | `int` |
| tagCombatTaskData | 292 | _todo_124 | `float` |
| tagCombatTaskData | 296 | _todo_128 | `int` |
| tagCombatTaskData | 300 | _todo_12C | `int` |
| tagCombatTaskData | 304 | _todo_130 | `float` |
| tagCombatTaskData | 308 | _todo_134 | `int` |
| tagCombatTaskData | 312 | _todo_138 | `int` |
| tagCombatTaskData | 336 | _todo_150 | `float` |
| tagCombatTaskData | 340 | _todo_154 | `int` |
| tagCombatTaskData | 344 | _todo_158 | `int` |
| tagCombatTaskData | 348 | _todo_15C | `float` |
| tagCombatTaskData | 352 | m_fFloatParam | `float` |
| tagCombatTaskData | 356 | _todo_164 | `int` |
| tagCombatTaskData | 360 | _todo_168 | `float` |
| tagCombatTaskData | 364 | _todo_16C | `int` |
| tagCombatTaskData | 368 | _todo_170 | `int` |
| tagCombatTaskData | 372 | _todo_174 | `float` |
| tagCombatTaskData | 376 | _todo_178 | `int` |
| tagCombatTaskData | 380 | _todo_17C | `int` |
| tagCombatTimerState | 4 | m_fCBTimer | `float` |
| tagCombatTimerState | 8 | m_nTodo_69C | `int` |
| tagCombatTimerState | 84 | m_nTodo_6E8 | `float` |
| tagCombatTimerState | 88 | m_nTodo_6EC | `float` |
| tagCombatTimerState | 92 | m_nTodo_6F0 | `float` |
| tagCombatTimerState | 104 | m_nTodo_6FC | `float` |
| tagCombatTimerState | 108 | m_nTodo_700 | `float` |
| tagCombatTimerState | 112 | m_nTodo_704 | `float` |
| tagCombatTimerState | 868 | pfVal | `float` |
| tagCombatTimerState | 872 | m_CCBStageCamBuffer | `char` |
| tagControlData | 0 | dwButtonID | `unsigned int` |
| tagControlData | 4 | dwParam1 | `char *` |
| tagControlData | 8 | dwParam2 | `unsigned int` |
| tagControlData | 12 | bValid | `BYTE` |
| tagControlThread | 0 | fp | `char *[4]` |
| tagControlThread | 16 | fpCaller | `char *[4]` |
| tagControlThread | 32 | dwID | `unsigned int` |
| tagControlThread | 36 | dwFlag | `unsigned int` |
| tagControlThread | 40 | dwCmdKind | `unsigned int` |
| tagControlThread | 44 | dwCmdID | `unsigned int` |
| tagControlThread | 48 | dwReturn | `unsigned int` |
| tagControlThread | 52 | nTaskIndex | `int` |
| tagControlThread | 56 | dwTaskID | `unsigned int` |
| tagControlThread | 60 | bValid | `BYTE` |
| tagControlThread | 61 | bExecuted | `BYTE` |
| tagDemand | 0 | nSatisfy | `int` |
| tagDemand | 4 | dwThread | `unsigned int` |
| tagDemand | 8 | bHandle | `char` |
| tagDemand | 12 | eSpecState | `ECBRoleSpecState` |
| tagEffGroup | 0 | nValidObj | `int` |
| tagEffGroup | 4 | dwEffObjTypeCRC | `unsigned int[16]` |
| tagEffGroup | 68 | Task | `char[256]` |
| tagEffLinker | 0 | dwTrickID | `unsigned int` |
| tagEffLinker | 4 | nEffGroup1 | `int` |
| tagEffLinker | 8 | bSrcForceCenter1 | `BYTE` |
| tagEffLinker | 9 | bDestForceCenter1 | `BYTE` |
| tagEffLinker | 10 | bSrcRole1 | `BYTE` |
| tagEffLinker | 11 | bDestRole1 | `BYTE` |
| tagEffLinker | 12 | vecPos1 | `gbVec3D` |
| tagEffLinker | 24 | fWaitTime1 | `float` |
| tagEffLinker | 28 | fWorkTime1 | `float` |
| tagEffLinker | 32 | nEffGroup2 | `int` |
| tagEffLinker | 36 | bSrcForceCenter2 | `BYTE` |
| tagEffLinker | 37 | bDestForceCenter2 | `BYTE` |
| tagEffLinker | 38 | bSrcRole2 | `BYTE` |
| tagEffLinker | 39 | bDestRole2 | `BYTE` |
| tagEffLinker | 40 | vecPos2 | `gbVec3D` |
| tagEffLinker | 52 | fWaitTime2 | `float` |
| tagEffLinker | 56 | fWorkTime2 | `float` |
| tagEffObj | 0 | dwClassNameCRC | `unsigned int` |
| tagEffObj | 4 | dwTypeNameCRC | `unsigned int` |
| tagEffObj | 8 | dwRunGroupID | `unsigned int` |
| tagEffObj | 12 | bValid | `unsigned char` |
| tagEffObj | 13 | bIdle | `unsigned char` |
| tagEffObj | 14 | bClassObj | `unsigned char` |
| tagEffObj | 16 | pEffect | `CEffObj *` |
| tagEffObjType | 0 | dwClassNameCRC | `unsigned int` |
| tagEffObjType | 4 | szTypeName | `char[30]` |
| tagEffObjType | 36 | dwTypeNameCRC | `unsigned int` |
| tagEffObjType | 40 | szTexture | `char[128]` |
| tagEffObjType | 168 | nFramePerRow | `int` |
| tagEffObjType | 172 | nFramePerCol | `int` |
| tagEffObjType | 176 | nFrame | `int` |
| tagEffObjType | 180 | fFramePerSec | `float` |
| tagEffObjType | 184 | fX | `float` |
| tagEffObjType | 188 | fY | `float` |
| tagEffObjType | 192 | fZ | `float` |
| tagEffObjType | 196 | fStartYRot | `float` |
| tagEffObjType | 200 | fSize | `float` |
| tagEffObjType | 204 | dwColor | `unsigned int` |
| tagEffObjType | 208 | nMaxQuad | `int` |
| tagEffObjType | 212 | bValid | `BYTE` |
| tagEffObjType | 213 | bAdditiveBlend | `BYTE` |
| tagEffObjType | 214 | bBillBoard | `BYTE` |
| tagEffObjType | 215 | bNoZTest | `BYTE` |
| tagEffObjType | 216 | fStartXRot | `float` |
| tagEffObjType | 220 | fStartZRot | `float` |
| tagEffObjType | 224 | fSacleX | `float` |
| tagEffObjType | 228 | fSacleY | `float` |
| tagEffObjType | 232 | fSacleZ | `float` |
| tagEffObjType | 236 | fTopShrink | `float` |
| tagEffObjType | 240 | fBottomShrink | `float` |
| tagEffObjType | 244 | fTopRadius | `float` |
| tagEffObjType | 248 | fBottomRadius | `float` |
| tagEffObjType | 252 | fTopRadiusIncSpeed | `float` |
| tagEffObjType | 256 | fBottomRadiusIncSpeed | `float` |
| tagEffObjType | 260 | fTopRiseSpeed | `float` |
| tagEffObjType | 264 | fBottomRiseSpeed | `float` |
| tagEffObjType | 268 | fTextureRepeat | `float` |
| tagEffObjType | 272 | fParam | `float[2]` |
| tagEffSParticleSys | 0 | m_nEffCount | `int` |
| tagEffSParticleSys | 8 | m_vSpawnPos | `float[2]` |
| tagEffSParticleSys | 16 | m_vSpawnOffset | `float[2]` |
| tagEffSParticleSys | 24 | m_nSpawnFlags | `int` |
| tagEffSParticleSys | 28 | m_nSpawnCount | `int` |
| tagEffSParticleSys | 32 | m_fSpawnSize | `float` |
| tagEffSParticleSys | 36 | m_nSpawnLife | `int` |
| tagEffSParticleSys | 40 | m_fSpawnBright | `float` |
| tagEffSParticleSys | 44 | m_nSpawnEffect | `int` |
| tagEffSParticleSys | 48 | m_bSpawnActive | `unsigned char` |
| tagEffSParticleSys | 56 | m_vSpawn2Pos | `float[2]` |
| tagEffSParticleSys | 64 | m_nSpawn2Flags | `int` |
| tagEffSParticleSys | 68 | m_nSpawn2Count | `int` |
| tagEffSParticleSys | 72 | m_fSpawn2Size | `float` |
| tagEffSParticleSys | 76 | m_nSpawn2Color | `int` |
| tagEffSParticleSys | 80 | m_nSpawn2Life | `int` |
| tagEffSParticleSys | 84 | m_nSpawn2Bright | `int` |
| tagEffSParticleSys | 88 | m_nSpawn2Effect | `int` |
| tagEffSParticleSys | 92 | m_nSpawn2Rand | `int` |
| tagEffSParticleSys | 96 | m_bSpawn2Active | `unsigned char` |
| tagEffSParticleSys | 104 | m_vSpawn3Pos | `float[2]` |
| tagEffSParticleSys | 112 | m_vSpawn3Rand | `float[2]` |
| tagEffSParticleSys | 120 | m_nSpawn3Flags | `int` |
| tagEffSParticleSys | 124 | m_nSpawn3Count | `int` |
| tagEffSParticleSys | 128 | m_fSpawn3Size | `float` |
| tagEffSParticleSys | 132 | m_nSpawn3Color | `int` |
| tagEffSParticleSys | 136 | m_fSpawn3Bright | `float` |
| tagEffSParticleSys | 140 | m_nSpawn3Life | `int` |
| tagEffSParticleSys | 144 | m_bSpawn3Active | `unsigned char` |
| tagEffSParticleSys | 800 | m_ptLastSpawn | `int[2]` |
| tagEffTaskParam | 0 | fQuake | `float` |
| tagEffTaskParam | 4 | fTrackSpeed | `float` |
| tagEffTaskParam | 8 | fQuakeFre | `float` |
| tagEffTaskParam | 12 | fSoundStartTime2 | `float` |
| tagEffTaskParam | 16 | fSpeedRot | `float` |
| tagEffTaskParam | 20 | fCallBack3 | `float` |
| tagEffTaskParam | 24 | fCallBack3PX | `float` |
| tagEffTaskParam | 28 | fCallBack3PY | `float` |
| tagEffTaskParam | 32 | fSoundIndex3 | `float` |
| tagEffTaskParam | 36 | fCallBack3PZ | `float` |
| tagEffTaskParam | 40 | fSoundStartTime3 | `float` |
| tagEffTaskParam | 44 | fSoundIndex4 | `float` |
| tagEffTaskParam | 48 | fSoundStartTime4 | `float` |
| tagEffTaskParam | 52 | fRotSpeed | `float` |
| tagEffTaskParam | 56 | fCallBack4 | `float` |
| tagEffTaskParam | 60 | fExplosionTime | `float` |
| tagEffTaskParam | 64 | fCallBack4PY | `float` |
| tagEffTaskParam | 68 | fCallBack4PZ | `float` |
| tagEffTaskParam | 72 | fStartTime | `float` |
| tagEffTaskParam | 76 | fExpectTime | `float` |
| tagEffTaskParam | 80 | nBladeTime | `int` |
| tagEffTaskParam | 84 | fZStretchSpeed | `float` |
| tagEffTaskParam | 88 | bValid | `BYTE` |
| tagEffTaskParam | 89 | bGetBackOldTimeScale | `BYTE` |
| tagEffTaskParam | 90 | bModifyStartTimeScale | `BYTE` |
| tagEffTaskParam | 92 | fTargetRot | `float` |
| tagEffTaskParam | 96 | dwActKey | `unsigned int` |
| tagEffTaskParam | 100 | dwRoleKey | `unsigned int` |
| tagEffTaskParam | 104 | fReseved | `float[5]` |
| tagEntry | 0 | sizeFront | `int` |
| tagEntry | 4 | pEntryNext | `tagEntry *` |
| tagEntry | 8 | pEntryPrev | `tagEntry *` |
| tagEntryEnd | 0 | sizeBack | `int` |
| tagExplosive | 0 | vecSpeed | `gbVec3D` |
| tagExplosive | 12 | vecRot | `gbVec3D` |
| tagFightScriptData | 356 | bLoaded | `char` |
| tagFightScriptData | 360 | pScriptData | `char[152]` |
| tagFormationSceneState | 456 | m_pCurrentScript | `PalScript *` |
| tagFormationSceneState | 460 | m_bFormationReady | `_BYTE` |
| tagFormationSceneState | 461 | m_nSceneTransitionParam | `_BYTE` |
| tagFormationSceneState | 464 | _todo_35c | `int` |
| tagFormationSceneState | 468 | _todo_360 | `int` |
| tagFormationSceneState | 476 | m_fFadeTimer | `float` |
| tagFormationSceneState | 480 | _todo_36c | `int` |
| tagFormationSceneState | 580 | m_szSceneUIText | `char[256]` |
| tagFormationSceneState | 860 | _todo_4e8 | `int` |
| tagGroup | 0 | cntEntries | `int` |
| tagGroup | 4 | listHead | `tagListHead[64]` |
| tagHeader | 0 | bitvEntryHi | `unsigned int` |
| tagHeader | 4 | bitvEntryLo | `unsigned int` |
| tagHeader | 8 | bitvCommit | `unsigned int` |
| tagHeader | 12 | pHeapData | `char *` |
| tagHeader | 16 | pRegion | `tagRegion *` |
| tagImbibeNimbus | 0 | mNimbus | `UIStatic *` |
| tagImbibeNimbus | 4 | mNimbustype | `ECBFiveNimbus` |
| tagImbibeNimbus | 8 | mVelocity | `gbVec3D` |
| tagImbibeNimbus | 20 | mPos | `tagPOINT` |
| tagImbibeNimbus | 28 | bAlive | `BYTE` |
| tagImbibeNimbus | 32 | mAccelerate | `float` |
| tagImbibeNimbus | 36 | mFX | `float` |
| tagImbibeNimbus | 40 | mFY | `float` |
| tagKBDLLHOOKSTRUCT | 0 | vkCode | `unsigned int` |
| tagKBDLLHOOKSTRUCT | 4 | scanCode | `unsigned int` |
| tagKBDLLHOOKSTRUCT | 8 | flags | `unsigned int` |
| tagKBDLLHOOKSTRUCT | 12 | time | `unsigned int` |
| tagKBDLLHOOKSTRUCT | 16 | dwExtraInfo | `unsigned int` |
| tagLVCOLUMNA | 0 | mask | `unsigned int` |
| tagLVCOLUMNA | 4 | fmt | `int` |
| tagLVCOLUMNA | 8 | cx | `int` |
| tagLVCOLUMNA | 12 | pszText | `char *` |
| tagLVCOLUMNA | 16 | cchTextMax | `int` |
| tagLVCOLUMNA | 20 | iSubItem | `int` |
| tagLVCOLUMNA | 24 | iImage | `int` |
| tagLVCOLUMNA | 28 | iOrder | `int` |
| tagLVITEMA | 0 | mask | `unsigned int` |
| tagLVITEMA | 4 | iItem | `int` |
| tagLVITEMA | 8 | iSubItem | `int` |
| tagLVITEMA | 12 | state | `unsigned int` |
| tagLVITEMA | 16 | stateMask | `unsigned int` |
| tagLVITEMA | 20 | pszText | `char *` |
| tagLVITEMA | 24 | cchTextMax | `int` |
| tagLVITEMA | 28 | iImage | `int` |
| tagLVITEMA | 32 | lParam | `int` |
| tagLVITEMA | 36 | iIndent | `int` |
| tagListHead | 0 | pEntryNext | `tagEntry *` |
| tagListHead | 4 | pEntryPrev | `tagEntry *` |
| tagLoggerCallback | 0 | szName | `char[32]` |
| tagLoggerCallback | 32 | szDesc | `char[100]` |
| tagLoggerCallback | 132 | pfn | `int *` |
| tagMeteor | 0 | vecPos | `gbVec3D` |
| tagMeteor | 12 | vecSpeed | `gbVec3D` |
| tagMeteor | 24 | vecASpeed | `gbVec3D` |
| tagMeteor | 36 | vecTarget | `gbVec3D` |
| tagMeteorNode | 0 | vecPos | `gbVec3D` |
| tagMeteorNode | 12 | fLum | `float` |
| tagMeteorNode | 16 | fWidth | `float` |
| tagMeteorNode | 20 | fTime | `float` |
| tagMeteorNode | 24 | bVisible | `BYTE` |
| tagMeteorNode | 28 | pLast | `tagMeteorNode *` |
| tagMeteorNode | 32 | pNext | `tagMeteorNode *` |
| tagNMHDR | 0 | hwndFrom | `HWND__ *` |
| tagNMHDR | 4 | idFrom | `unsigned int` |
| tagNMHDR | 8 | code | `unsigned int` |
| tagNMITEMACTIVATE | 0 | hdr | `tagNMHDR` |
| tagNMITEMACTIVATE | 12 | iItem | `int` |
| tagNMITEMACTIVATE | 16 | iSubItem | `int` |
| tagNMITEMACTIVATE | 20 | uNewState | `unsigned int` |
| tagNMITEMACTIVATE | 24 | uOldState | `unsigned int` |
| tagNMITEMACTIVATE | 28 | uChanged | `unsigned int` |
| tagNMITEMACTIVATE | 32 | ptAction | `tagPOINT` |
| tagNMITEMACTIVATE | 40 | lParam | `int` |
| tagNMITEMACTIVATE | 44 | uKeyFlags | `unsigned int` |
| tagNewItem | 0 | dwItemID | `unsigned int` |
| tagNewItem | 4 | fnHP | `int (__thiscall *)(void *, unsigned int)` |
| tagNewItem | 8 | fnGP | `int (__thiscall *)(void *, unsigned int)` |
| tagNewItem | 12 | fnMP | `float` |
| tagPALETTEENTRY | 0 | peRed | `unsigned char` |
| tagPALETTEENTRY | 1 | peGreen | `unsigned char` |
| tagPALETTEENTRY | 2 | peBlue | `unsigned char` |
| tagPALETTEENTRY | 3 | peFlags | `unsigned char` |
| tagParam | 0 | f1 | `float` |
| tagParam | 4 | f2 | `float` |
| tagParam | 8 | f3 | `float` |
| tagPartical | 0 | pPic | `char *` |
| tagPartical | 4 | nQuadIndex | `int` |
| tagPartical | 8 | bValid | `BYTE` |
| tagPartical | 9 | bVisible | `BYTE` |
| tagPartical | 10 | bAniFrame | `BYTE` |
| tagPartical | 11 | bBillBoard | `BYTE` |
| tagPartical | 12 | byMaxFrame | `BYTE` |
| tagPartical | 13 | byFrameIndex | `BYTE` |
| tagPartical | 14 | byLoops | `BYTE` |
| tagPartical | 15 | byMaxLoops | `BYTE` |
| tagPartical | 16 | fFramePerSec | `float` |
| tagPartical | 20 | fCurFrame | `float` |
| tagPartical | 24 | dwColor | `unsigned int` |
| tagPartical | 28 | fX | `float` |
| tagPartical | 32 | fY | `float` |
| tagPartical | 36 | fZ | `float` |
| tagPartical | 40 | fSize | `float` |
| tagPartical | 44 | byAlpha | `BYTE` |
| tagPartyInitView | 0 | _gap_50814 | `_BYTE[2]` |
| tagPartyInitView | 2 | m_partyInitData | `int[100]` |
| tagPlayerSet | 0 | LastRoleCmd | `tagCmdData` |
| tagPlayerSet | 44 | nMagicDefaultPage | `int` |
| tagPlayerSet | 48 | nItemDefaultPage | `int` |
| tagQuad | 0 | nGeomQuad | `int` |
| tagQuad | 4 | bValid | `BYTE` |
| tagQuad | 5 | bVisible | `BYTE` |
| tagQuad | 6 | byFrame | `BYTE` |
| tagQuad | 7 | byLoops | `BYTE` |
| tagQuad | 8 | fFramePerSec | `float` |
| tagQuad | 12 | fCurFrame | `float` |
| tagQuad | 16 | fX | `float` |
| tagQuad | 20 | fY | `float` |
| tagQuad | 24 | fZ | `float` |
| tagQuad | 28 | fXSize | `float` |
| tagQuad | 32 | fYSize | `float` |
| tagQuad | 36 | fPX | `float` |
| tagQuad | 40 | fPY | `float` |
| tagQuad | 44 | fPZ | `float` |
| tagQuad | 48 | fRotation | `float` |
| tagQuad | 52 | fRotX | `float` |
| tagQuad | 56 | fRotZ | `float` |
| tagQuad | 60 | fAlpha | `float` |
| tagQuad | 64 | fRed | `float` |
| tagQuad | 68 | fGreen | `float` |
| tagQuad | 72 | fBlue | `float` |
| tagQuad | 76 | dwColor | `unsigned int` |
| tagRGBQUAD | 0 | rgbBlue | `BYTE` |
| tagRGBQUAD | 1 | rgbGreen | `BYTE` |
| tagRGBQUAD | 2 | rgbRed | `BYTE` |
| tagRGBQUAD | 3 | rgbReserved | `BYTE` |
| tagRegion | 0 | indGroupUse | `int` |
| tagRegion | 4 | cntRegionSize | `char[64]` |
| tagRegion | 68 | bitvGroupHi | `unsigned int[32]` |
| tagRegion | 196 | bitvGroupLo | `unsigned int[32]` |
| tagRegion | 324 | grpHeadList | `char[256]` |
| tagRoleActionState | 1 | _todo_18D | `_BYTE` |
| tagRoleActionState | 36 | _todo_1B0 | `int` |
| tagRoleActionState | 52 | m_bRoleAction | `int` |
| tagRoleActionState | 72 | m_RoleActionType | `_BYTE` |
| tagRoleActionState | 76 | _todo_1B8 | `float` |
| tagRoleActionState | 84 | _todo_01E0 | `float` |
| tagRoleActionState | 88 | _todo_1C4 | `float` |
| tagRoleActionState | 92 | _todo_1C8 | `float` |
| tagRoleActionState | 96 | _todo_1CC | `float` |
| tagRoleActionState | 100 | _todo_1D0 | `float` |
| tagRoleActionState | 104 | _todo_1F4 | `float` |
| tagRoleActionState | 108 | _todo_1F8 | `float` |
| tagRoleActionState | 112 | _todo_1FC | `float` |
| tagRoleActionState | 116 | m_nLoadFromFile | `int` |
| tagRoleActionState | 120 | m_nLoadState | `int` |
| tagRoleActionState | 124 | m_nNext | `int` |
| tagRoleActionState | 128 | m_DialogTemplate | `int` |
| tagRoleActionState | 132 | m_nConfigIndex | `int` |
| tagRoleActionState | 136 | m_SceneConfig | `int` |
| tagRoleActionState | 140 | m_SceneCfg_flags1 | `int` |
| tagRoleActionState | 144 | m_SceneCfg_fParam0 | `float` |
| tagRoleActionState | 148 | m_SceneCfg_nParam0 | `int` |
| tagRoleActionState | 152 | m_SceneCfg_nParam1 | `int` |
| tagRoleActionState | 156 | m_SceneCfg_nParam2 | `int` |
| tagRoleActionState | 160 | m_SceneCfg_data | `int` |
| tagRoleActionState | 164 | m_fSceneCfg | `float[48]` |
| tagRoleActionState | 384 | m_nDialogData | `signed __int16` |
| tagRoleActionState | 400 | m_nEmoteParam | `int` |
| tagRoleActionState | 404 | m_nScreenWidth | `int` |
| tagRoleActionState | 480 | m_EncampSound | `int` |
| tagRoleActionState | 576 | m_CamFocusData | `int` |
| tagRoleActionState | 644 | m_nDialogResult | `int` |
| tagRoleActionState | 648 | m_DialogByte | `_BYTE` |
| tagRoleActionState | 732 | _todo_468 | `int` |
| tagRoleActionState | 876 | m_nPathState | `int` |
| tagRoleActionState | 880 | m_nOverlapId | `int` |
| tagRoleActionState | 884 | _todo_500 | `int` |
| tagRoleActionState | 892 | _todo_508 | `int` |
| tagRoleSlot | 0 | nRoleID | `unsigned __int16` |
| tagRoleState | 0 | dwID | `unsigned int` |
| tagRoleState | 4 | nIndex | `int` |
| tagRoleState | 8 | sModel | `char[16]` |
| tagRoleState | 24 | byUIIndex | `BYTE` |
| tagRoleState | 25 | bValid | `BYTE` |
| tagRoleState | 26 | bAlive | `BYTE` |
| tagRoleState | 27 | bFriend | `BYTE` |
| tagRoleState | 28 | bBoss | `BYTE` |
| tagRoleState | 29 | bCanAction | `BYTE` |
| tagRoleState | 30 | bWaitForFlee | `BYTE` |
| tagRoleState | 31 | bEnemyFriend | `BYTE` |
| tagRoleState | 32 | nLevel | `int` |
| tagRoleState | 36 | nHP | `int` |
| tagRoleState | 40 | nFullHP | `int` |
| tagRoleState | 44 | nGP | `int` |
| tagRoleState | 48 | pCCBSystem | `CCBSystem *` |
| tagRoleState | 52 | nMP | `CCBStage *` |
| tagRoleState | 56 | nFullMP | `int` |
| tagRoleState | 60 | nAttack | `int` |
| tagRoleState | 64 | nDefence | `int` |
| tagRoleState | 68 | nSpeed | `int` |
| tagRoleState | 72 | nLuck | `int` |
| tagRoleState | 76 | nLove | `int` |
| tagRoleState | 80 | nMoney | `int` |
| tagRoleState | 84 | nProtectRole | `int` |
| tagRoleState | 88 | dwAttackMode | `unsigned int` |
| tagRoleState | 92 | nGPInc | `int` |
| tagRoleState | 96 | byWeaponType | `BYTE` |
| tagRoleState | 97 | bAttackRow | `BYTE` |
| tagRoleState | 98 | bAttackColumn | `BYTE` |
| tagRoleState | 99 | bAttackAll | `BYTE` |
| tagRoleState | 100 | bMagicSword | `BYTE` |
| tagRoleState | 104 | fGPCostDec | `float` |
| tagRoleState | 108 | fMPCostDec | `float` |
| tagRoleState | 112 | fPunchPowerInc | `float` |
| tagRoleState | 116 | fSkillCentInc | `float` |
| tagRoleState | 120 | fHPIncPerRound | `float` |
| tagRoleState | 124 | fGPIncPerRound | `float` |
| tagRoleState | 128 | fGPIncPerRoundBak | `float` |
| tagRoleState | 132 | fMPIncPerRound | `float` |
| tagRoleState | 136 | fEXPIncPerCombat | `float` |
| tagRoleState | 140 | fMoneyIncPerCombat | `float` |
| tagRoleState | 144 | fRecoverItemPowerInc | `float` |
| tagRoleState | 148 | nStealCent | `int` |
| tagRoleState | 152 | bLostMoneyGetLife | `BYTE` |
| tagRoleState | 153 | bMirror | `BYTE` |
| tagRoleState | 156 | nEXP | `int` |
| tagRoleState | 160 | nCombatEXP | `int` |
| tagRoleState | 164 | dwSkillID | `unsigned int[9]` |
| tagRoleState | 200 | bSkillMastered | `_BYTE[9]` |
| tagRoleState | 212 | dwMagicID | `unsigned int[9][6]` |
| tagRoleState | 428 | bMagicMastered | `_BYTE[9][6]` |
| tagRoleState | 482 | byMagicUseTime | `unsigned __int16[9][6]` |
| tagRoleSystemData | 0 | m_nEffParamBase0 | `int` |
| tagRoleSystemData | 20 | m_nEffParam14 | `int` |
| tagRoleSystemData | 40 | m_nEffTypeCode | `int` |
| tagRoleSystemData | 60 | m_nEffParam3C | `int` |
| tagRoleSystemData | 80 | m_nEffParam50 | `int` |
| tagRoleSystemData | 100 | _todo_064 | `int` |
| tagRoleSystemData | 180 | m_nEffParamB4 | `int` |
| tagRoleSystemData | 200 | m_nEffParamC8 | `int` |
| tagRoleSystemData | 220 | m_nEffParamDC | `int` |
| tagRoleSystemData | 240 | m_nEffParamF0 | `int` |
| tagRoleSystemData | 260 | _todo_104 | `float` |
| tagRoleSystemData | 280 | _todo_118 | `float` |
| tagRoleSystemData | 340 | _todo_154 | `int` |
| tagRoleSystemData | 360 | _todo_168 | `int` |
| tagRoleSystemData | 380 | _todo_17C | `int` |
| tagRoleSystemData | 400 | _todo_190 | `int` |
| tagRoleTask | 0 | fp | `char *[4]` |
| tagRoleTask | 16 | vec1 | `_inline_tagRoleTask_vec1` |
| tagRoleTask | 28 | cmd | `tagCmdData` |
| tagRoleTask | 72 | fTemp | `float` |
| tagRoleTask | 76 | fTemp2 | `float` |
| tagRoleTask | 80 | dwID | `unsigned int` |
| tagRoleTask | 84 | eMode | `ECBRoleTaskMode` |
| tagRoleTask | 88 | bValid | `BYTE` |
| tagRoleTask | 89 | bFinished | `BYTE` |
| tagRoleTask | 90 | bExecuted | `BYTE` |
| tagRoleTaskData | 0 | nStatus | `int` |
| tagRoleTaskData | 8 | nActionType | `int` |
| tagRoleTaskData | 16 | pRoleState | `void *` |
| tagRoleTaskData | 24 | _gap_18 | `char[48]` |
| tagRoleTaskSlotsView | 0 | pLayout | `CCBRoleState *` |
| tagRoleTaskSlotsView | 4 | pToggle | `PlayerMgr *` |
| tagRoleTaskSlotsView | 8 | _pad | `float` |
| tagRoleTaskVec3View | 0 | x | `float` |
| tagRoleTaskVec3View | 4 | y | `float` |
| tagRoleTaskVec3View | 8 | z | `float` |
| tagScriptCmd | 0 | cmd_id | `signed __int16` |
| tagScriptCmd | 4 | handler | `int` |
| tagScriptCmd | 8 | param | `int` |
| tagScriptCmd | 12 | flags | `int` |
| tagScriptPtrQuad | 140 | pScriptVtable | `void *` |
| tagScriptPtrQuad | 148 | pScriptPtrA | `void *` |
| tagScriptPtrQuad | 152 | pScriptPtrB | `void *` |
| tagScriptPtrQuad | 160 | pScriptPtrC | `void *` |
| tagShockUnit | 0 | fRequireLoops | `float` |
| tagShockUnit | 4 | fCurFrame | `float` |
| tagShowItem | 0 | eKind | `ECBShowItemKind` |
| tagShowItem | 4 | sTxt | `char[256]` |
| tagShowItem | 260 | color | `tagRGBQUAD` |
| tagShowItem | 264 | fX | `float` |
| tagShowItem | 268 | fY | `float` |
| tagShowItem | 272 | fZ | `float` |
| tagShowItem | 276 | fSize | `float` |
| tagSkillCountBlock | 290 | nSkillCount1 | `int` |
| tagSkillCountBlock | 294 | nSkillCount2 | `int` |
| tagStageRoleData | 0 | m_nEffParamBase0 | `float` |
| tagStageRoleData | 4 | m_nEffParamBase4 | `int` |
| tagStageRoleData | 28 | m_nLoadLinkerParams | `int[4]` |
| tagStageRoleData | 44 | m_nSetAliveParams | `int[4]` |
| tagStageRoleData | 60 | m_nSetVisibleParams | `int[4]` |
| tagStageRoleData | 76 | m_nOnChangeActionParams | `int[4]` |
| tagStageRoleData | 108 | _todo_06C | `float` |
| tagStageRoleData | 112 | m_nEffParam5 | `float` |
| tagStageRoleData | 116 | _todo_074 | `float` |
| tagStageRoleData | 120 | m_nEffParam6 | `float` |
| tagStageRoleData | 132 | m_nEffParam7 | `float` |
| tagStageRoleData | 136 | m_fRoleTargetParam | `int` |
| tagStageRoleData | 140 | m_nEffParam8 | `int` |
| tagStageRoleData | 156 | m_nEffParam9C | `float` |
| tagStageSubTask | 0 | fp | `char *[4]` |
| tagStageSubTask | 16 | eStats | `ECBStageTaskState` |
| tagStageSubTask | 20 | dwID | `unsigned int` |
| tagStageSubTask | 24 | fStartTime | `float` |
| tagStageSubTask | 28 | fWaitTime | `float` |
| tagStageSubTask | 32 | fTime | `float` |
| tagStageSubTask | 36 | dwReturn | `unsigned int` |
| tagStageSubTask | 40 | bValid | `BYTE` |
| tagStageSubTask | 41 | bExecuted | `BYTE` |
| tagStageSubTask | 42 | bAction | `BYTE` |
| tagStageSubTask | 43 | bRequireToEnd | `BYTE` |
| tagStageSubTask | 44 | param | `tagParam` |
| tagStageSubTask | 56 | nEffLinker | `int` |
| tagStageSubTask | 60 | bEff1Started | `BYTE` |
| tagStageSubTask | 61 | bEff2Started | `BYTE` |
| tagStageSubTask | 62 | bEffWorked | `BYTE` |
| tagStageSubTask | 64 | fTemp1 | `float` |
| tagStageSubTask | 68 | fTemp2 | `float` |
| tagStageSubTask | 72 | fTemp3 | `float` |
| tagStageSubTask | 76 | fTemp4 | `float` |
| tagStageTask | 0 | eTask | `ECBStageTask` |
| tagStageTask | 4 | eStats | `ECBStageTaskState` |
| tagStageTask | 8 | nSubTask | `int` |
| tagStageTask | 12 | nReserved | `int` |
| tagStageTask | 16 | SubTask | `tagStageSubTask[32]` |
| tagStageTask | 2576 | dwID | `unsigned int` |
| tagStageTask | 2580 | dwReturn | `unsigned int` |
| tagStageTask | 2584 | cmd | `tagCmdData` |
| tagStageTask | 2628 | bValid | `BYTE` |
| tagStageTask | 2629 | bAutoDel | `BYTE` |
| tagTCITEMA | 0 | mask | `unsigned int` |
| tagTCITEMA | 4 | dwState | `unsigned int` |
| tagTCITEMA | 8 | dwStateMask | `unsigned int` |
| tagTCITEMA | 12 | pszText | `char *` |
| tagTCITEMA | 16 | cchTextMax | `int` |
| tagTCITEMA | 20 | iImage | `int` |
| tagTCITEMA | 24 | lParam | `int` |
| tagTaskLayoutPtrs | 0 | pLayout | `CCBRoleState *` |
| tagTaskLayoutPtrs | 4 | pToggle | `PlayerMgr *` |
| tagTaskLayoutPtrs | 8 | _pad | `float` |
| tagTaskSlotHeader | 0 | pRoleTaskData | `void *` |
| tagTaskSlotHeader | 4 | nTaskCount | `int` |
| tagTaskVecXYZ | 0 | x | `float` |
| tagTaskVecXYZ | 4 | y | `float` |
| tagTaskVecXYZ | 8 | z | `float` |
| tagTeamSlotsBOverlay | 548 | m_nCombatViewMode | `int` |
| tagTeamSlotsBOverlay | 552 | dwInitParam | `HWND` |
| tagTeamSlotsBOverlay | 556 | g_hCombatDlg1 | `HWND` |
| tagTeamSlotsBOverlay | 560 | g_hCombatDlg2 | `HWND` |
| tagTeamSlotsBOverlay | 564 | m_nActorRenderCount | `int` |
| tagTeamSlotsBOverlay | 568 | g_hCBStageCamDlg | `HWND` |
| tagTeamSlotsBOverlay | 574 | m_bWPARAM | `unsigned char` |
| tagTeamSlotsBOverlay | 596 | m_nCCBUISelectedRole | `int` |
| tagTeamSlotsBOverlay | 600 | m_nCCBUIIdx | `int` |
| tagTeamSlotsBOverlay | 606 | m_bCommandEdited | `unsigned char` |
| tagThread | 0 | fp | `char *[4]` |
| tagThread | 16 | dwID | `unsigned int` |
| tagThread | 20 | nTaskIndex | `int` |
| tagThread | 24 | dwTaskID | `unsigned int` |
| tagThread | 28 | dwReturn | `unsigned int` |
| tagThread | 32 | nTemp | `int` |
| tagThread | 36 | bValid | `BYTE` |
| tagThread | 37 | bExecuted | `BYTE` |
| tagThread | 40 | cmd | `tagCmdData` |
| tagUIParam | 0 | pUI | `UIWnd *` |
| tagUIParam | 4 | fFromX | `float` |
| tagUIParam | 8 | fFromY | `float` |
| tagUIParam | 12 | fEndX | `float` |
| tagUIParam | 16 | fEndY | `float` |
| tagUIParam | 20 | fSpeed | `float` |
| tagUIParam | 24 | fEnergy | `int` |
| tagUIParam | 28 | nTimes | `int` |
| tagUITask | 0 | fp | `char *[4]` |
| tagUITask | 16 | bValid | `BYTE` |
| tagUITask | 17 | bExecuted | `BYTE` |
| tagUITask | 18 | bFinished | `BYTE` |
| tagUITask | 20 | dwID | `unsigned int` |
| tagUITask | 24 | fStartTime | `float` |
| tagUITask | 28 | fExpectStartTime | `int` |
| tagUITask | 32 | fExpectEndTime | `float` |
| tagUITask | 36 | param | `tagUIParam` |
| tagUV | 0 | su | `float` |
| tagUV | 4 | sv | `float` |
| tagUV | 8 | eu | `float` |
| tagUV | 12 | ev | `float` |
| tagUVSet | 0 | su | `float` |
| tagUVSet | 4 | sv | `float` |
| tagUVSet | 8 | eu | `float` |
| tagUVSet | 12 | ev | `float` |
| tagVA | 0 | eKind | `ECBVAKind` |
| tagVA | 4 | nSrc | `int` |
| tagVA | 8 | nDest | `int` |
| tagVA | 12 | nStart | `int` |
| tagVA | 16 | nEnd | `int` |
| tagVA | 20 | bValid | `BYTE` |
| tagVAF | 0 | nIndex | `int` |
| tagVAF | 8 | fp | `char *[4]` |
| tagVAF | 24 | bValid | `BYTE` |
| tagVAF | 25 | bDecision | `BYTE` |
| tagVAF | 26 | bResult | `BYTE` |
| tagVAF | 28 | nAddonScore | `int` |
| tagVAO | 0 | dwDataID | `unsigned int` |
| tagVAO | 4 | nDataIndex | `int` |
| tagVAO | 8 | nScore | `int` |
| tagVAO | 12 | bValid | `BYTE` |
| util | 0 | Crc32Table | `unsigned int[256]` |
| util | 1024 | m_dwIDHolder | `unsigned int` |
| util | 1028 | m_nRandHolder | `int` |
| util | 1032 | m_nRandCallCount | `int` |
| util | 1036 | m_pIniReader | `CIniFile *` |
| util | 1040 | m_pLoader3DS | `CLoad3DS *` |
| vert | 0 | _texture | `char *[2]` |
| vert | 8 | _world | `char *[3]` |
| vert | 20 | _screen | `char *` |
| waveformat_tag | 0 | wFormatTag | `unsigned __int16` |
| waveformat_tag | 2 | nChannels | `unsigned __int16` |
| waveformat_tag | 4 | nSamplesPerSec | `unsigned int` |
| waveformat_tag | 8 | nAvgBytesPerSec | `unsigned int` |
| waveformat_tag | 12 | nBlockAlign | `unsigned __int16` |
| wavehdr_tag | 0 | lpData | `char *` |
| wavehdr_tag | 4 | dwBufferLength | `unsigned int` |
| wavehdr_tag | 8 | dwBytesRecorded | `unsigned int` |
| wavehdr_tag | 12 | dwUser | `unsigned int` |
| wavehdr_tag | 16 | dwFlags | `unsigned int` |
| wavehdr_tag | 20 | dwLoops | `unsigned int` |
| wavehdr_tag | 24 | lpNext | `wavehdr_tag *` |
| wavehdr_tag | 28 | reserved | `unsigned int` |

## 4. 类型差异（语义不等）

归一化后仍不同的类型对（往返降级 / 重解释，**真差异**）：

（无）

## 5. 类型拼写归一（语义等价 · 不计差异）

同型异拼（MSVC6 x86 等价：DWORD/UINT/uint=unsigned int、WORD=unsigned __int16、BYTE=_BYTE=unsigned char、long=int、short=signed __int16…），逐拼写族计数：

（无）

## 6. 位面复用（非偏移冲突）

**位面复用 ≠ 偏移冲突**：以下成员是同一存储的多解释视图（dict 形态 inline union/struct · `source:overlap` · 同偏移 `_N` 变体键），IDB 侧同偏移多成员属预期，**不计**缺失/类型差异/冲突。dict 形态的往返形是合成名 `_inline_<类>_<成员>`：

| 形态 | 数量 |
|---|---|
| dict | 14 |
| dict+overlap | 2 |
| overlap | 145 |
| 合计（条目） | 161 |

| 类 | 偏移键 | 成员 | 形态 | 导出 type | 备注 |
|---|---|---|---|---|---|
| Actor | 0x200 | m_pParticleData | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| Actor | 0x2a8 | m_InnerActor | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ArcSceneMonster | 0x130 | m_pSkillList | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ArcSceneMonster | 0x140 | m_pDropItems | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ArcSceneMonster | 0x4 | m_pMonsterData | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBAI | 0xd10 | m_EnemyDemand | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBAI | 0xdb0 | m_FriendDemand | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBCamControl | 0xec | m_nTodo_EC | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBRoleState | 0x84 | m_nState | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBStage | 0x80 | m_fDamageNumPosY | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBStageScene | 0x5c | m_vecInitFiveLineup | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBTaskSlot208 | 0x0 | m_nBase | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBUI | 0x4b8 | m_Task | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CCBUIPanel | 0x50b8 | m_EmbedCaption | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CScreenMode | 0x27c | _embed_UIFrameWnd_816 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CScreenMode | 0x2d8 | _embed_UIFrameWnd_968 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CScreenMode | 0xa30 | m_pGameUI | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| CameraCtrl | 0x7fc | m_nViewBase | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| FightItem | 0x60 | desc | dict | `（导出缺）` | 位面复用成员未见于导出 |
| LineupComp | 0x44 | m_ObjPos | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| Logger | 0x122c | m_szCmdBuf2 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| Logger | 0x1230 | m_szCmdBuf | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| MUIDialog | 0x278 | m_btRc | dict | `（导出缺）` | 位面复用成员未见于导出 |
| MUIDialog | 0x3d0 | pCallbackVtable2 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| PalScript | 0x104 | m_WaitObjList | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| PalScript | 0x18c | m_RoleSlotArray | dict | `（导出缺）` | 位面复用成员未见于导出 |
| PalScript | 0x514 | m_szDialog1 | dict | `（导出缺）` | 位面复用成员未见于导出 |
| PalScript | 0x90 | m_pCurrentTask | dict | `（导出缺）` | 位面复用成员未见于导出 |
| PalScriptDialogOverlay | 0x8c | overlay | dict | `（导出缺）` | 位面复用成员未见于导出 |
| PalScriptRoleSlotOverlay | 0x0 | overlay | dict | `（导出缺）` | 位面复用成员未见于导出 |
| RoleAtt | 0x6 | Remark | dict | `（导出缺）` | 位面复用成员未见于导出 |
| RoleAttRemarkSkills | 0x122 | skillCount | dict | `（导出缺）` | 位面复用成员未见于导出 |
| RoleStatePanel | 0x2afc0 | m_pSubTab2 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| RoleSystem | 0x524 | m_FrameA | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| RoleSystem | 0x624 | m_nTodo_624 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| RoleSystem | 0xae | m_animStateU | dict | `（导出缺）` | 位面复用成员未见于导出 |
| RoleSystem | 0xc00 | m_teamSlotsB | dict | `（导出缺）` | 位面复用成员未见于导出 |
| RoleSystemTeamSlotOverlay | 0x4 | m_teamSlots | dict | `（导出缺）` | 位面复用成员未见于导出 |
| SceneMgr | 0x1610 | m_nTodo_C059A0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| SceneMgr | 0xc67e_0 |  | dict+overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ScriptSystemData | 0x8a8 | m_fTimerA | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ScriptSystemData | 0x908 | g_vRotateAxis | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ScriptSystemData | 0x914 | m_bMapRenderFlags | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ScriptSystemData | 0x918 | m_nScriptCounter0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ScriptSystemData | 0x91c | m_nScriptCounter1 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ScriptSystemData | 0x920 | m_nScriptFlag | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ScriptSystemData | 0xbd8 | m_fTimerB | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| ScriptSystemData | 0xe64 | m_fScriptTileSize2 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| TextureLib | 0x198 | m_pPalette | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| UIGameFrm | 0x1ba0 | m_fTimerC | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| UIGameFrm | 0x32c0 | m_fUIColorParam | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| UIGameFrm | 0x4028 | m_bGameUpdating | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| UIGameFrm | 0x8ac | m_pItemArray | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A7BData | 0x0 | m_nEffParamBase | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A7BData | 0x14 | m_nEffParam14 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A7BData | 0x18 | m_nEffParam1 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A7BData | 0x1c | m_nEffParam1C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A7BData | 0x24 | m_nEffParam24 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A7BData | 0x28 | m_nEffTypeCode | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A7BData | 0x2c | m_nEffParam2C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A7BData | 0xc | m_nEffParam0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x0 | m_nEffParamBase | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x10 | m_nEffParam10 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x14 | m_nEffParam14 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x18 | m_nEffParam1 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x1c | m_nEffParam1C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x20 | m_nEffTypeID | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x24 | m_nEffParam24 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x28 | m_nEffTypeCode | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x2c | m_nEffParam2C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0x30 | m_nEffParam30 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tag17A8Data | 0xc | m_nEffParam0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x0 | m_nEffParamBase | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x10 | m_nEffParam10 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x14 | m_nEffParam14 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x18 | m_nEffParam1 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x1c | m_nEffParam1C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x20 | m_nEffTypeID | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x24 | m_nEffParam24 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x28 | m_nEffTypeCode | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x2c | m_nEffParam2C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x30 | m_nEffParam30 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x34 | m_nEffParam34 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0x38 | m_nEffParam38 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagC10Data | 0xc | m_nEffParam0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCCBStageData | 0x0 | m_nEffParamBase0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCCBStageData | 0x14 | m_nEffParam14 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCCBStageData | 0x1c | m_nEffParam1C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCCBStageData | 0x20 | m_nEffTypeID | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCCBStageData | 0x28 | m_nEffTypeCode | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCam | 0xc | yaw | dict | `（导出缺）` | 位面复用成员未见于导出 |
| tagCmdData | 0x1d | m_destRoleView | dict+overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x0 | m_nEffParamBase | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x10 | m_nEffParam10 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x11c | _todo_11C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x128 | _todo_128 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x134 | _todo_134 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x14 | m_fEffDirZ | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x154 | _todo_154 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x15c | _todo_15C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x164 | _todo_164 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x16c | _todo_16C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x174 | _todo_174 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x17c | _todo_17C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x18 | m_nEffParam1 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x1c | m_nEffParam1C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x20 | m_nEffTypeID | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x24 | m_nEffParam24 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x28 | m_nEffTypeCode | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x40 | m_nEffParam40 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x44 | m_nEffParam44 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x48 | m_nEffParam48 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x4c | m_nEffParam4C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x50 | m_nEffParam50 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x54 | m_nEffParam2 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x58 | m_nEffParam58 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x5c | m_nEffParam5C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x60 | m_nEffParam3 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x68 | m_nEffParam4 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x84 | m_nEffParam7 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x8c | m_nEffParam8 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x94 | m_nEffParam9 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x98 | m_nEffParam98 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0x9c | m_nEffParam9C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xa0 | m_nEffParamA0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xa4 | m_nEffParamA4 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xa8 | m_nEffParamA8 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xac | m_nEffParamAC | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xb0 | m_nEffParamB0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xc | m_fEffDirX | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xc8 | m_nEffParamC8 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xcc | m_nEffParamCC | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xd0 | m_nEffParamD0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xd4 | m_nEffParamD4 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xd8 | m_nEffParamD8 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xdc | m_nEffParamDC | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xe0 | m_nEffParamE0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xe4 | m_nEffParamE4 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xe8 | m_nEffParamE8 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xec | m_nEffParamEC | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagCombatTaskData | 0xf0 | m_nEffParamF0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0x0 | m_nEffParamBase0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0x104 | _todo_104 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0x14 | m_nEffParam14 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0x154 | _todo_154 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0x17c | _todo_17C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0x28 | m_nEffTypeCode | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0x3c | m_nEffParam3C | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0x50 | m_nEffParam50 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0xb4 | m_nEffParamB4 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0xc8 | m_nEffParamC8 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0xdc | m_nEffParamDC | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleSystemData | 0xf0 | m_nEffParamF0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagRoleTask | 0x10 | vec1 | dict | `（导出缺）` | 位面复用成员未见于导出 |
| tagStageRoleData | 0x0 | m_nEffParamBase0 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagStageRoleData | 0x4 | m_nEffParamBase4 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagStageRoleData | 0x70 | m_nEffParam5 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagStageRoleData | 0x78 | m_nEffParam6 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagStageRoleData | 0x84 | m_nEffParam7 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagStageRoleData | 0x8c | m_nEffParam8 | overlap | `（导出缺）` | 位面复用成员未见于导出 |
| tagStageRoleData | 0x9c | m_nEffParam9C | overlap | `（导出缺）` | 位面复用成员未见于导出 |

## 7. `_inline_*` 引用 vs 定义对称性

| 项 | 数量 |
|---|---|
| 引用（成员 type 里的合成名） | 27 |
| 定义（ida_structs 顶层 `_inline_*` 键） | 31 |
| 引用无定义 | 0 |
| 定义未被引用 | 4 |

定义未被引用：

- `_inline_CCBTaskSlot__ovl_20`
- `_inline_CCBTaskSlot__ovl_28`
- `_inline_RoleSystem_`
- `_inline_RoleSystem_m_teamSlotOverlay`

## 8. 逐类差异（成员数 / 偏移 / 类型）

每类一行：成员数（注解/导出）+ 差异计数（拼写/类型/位面/缺口/新增）。

| 类 | 成员数(注解/导出) | 拼写归一 | 类型差异 | 位面复用 | 缺失 | 新增 |
|---|---|---|---|---|---|---|
| ARC_ArcBrief | 4/4 | 0 | 0 | 0 | 4 | 4 |
| ARC_ArcHeader | 14/14 | 0 | 0 | 0 | 14 | 14 |
| ARC_ArcLocaleRole | 2/2 | 0 | 0 | 0 | 2 | 2 |
| ARC_ArcMsic | 17/17 | 0 | 0 | 0 | 17 | 17 |
| ARC_ComboAttack | 12/12 | 0 | 0 | 0 | 12 | 12 |
| ARC_FightItem | 28/28 | 0 | 0 | 0 | 28 | 28 |
| ARC_FightSkill | 28/28 | 0 | 0 | 0 | 28 | 28 |
| ARC_Inventory | 4/4 | 0 | 0 | 0 | 4 | 4 |
| ARC_MonsterStar | 4/4 | 0 | 0 | 0 | 4 | 4 |
| ARC_OutFile | 9/9 | 0 | 0 | 0 | 9 | 9 |
| ARC_PAL_GDB | 7/7 | 0 | 0 | 0 | 7 | 7 |
| ARC_PlayerAtt | 25/25 | 0 | 0 | 0 | 25 | 25 |
| ARC_PlayerItem | 3/3 | 0 | 0 | 0 | 3 | 3 |
| ARC_PlayerMgrInfo | 10/10 | 0 | 0 | 0 | 10 | 10 |
| ARC_Reoccupy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ARC_RoleAtt | 19/19 | 0 | 0 | 0 | 19 | 19 |
| ASISTAGE | 24/24 | 0 | 0 | 0 | 24 | 24 |
| AStarPathFinder | 5/5 | 0 | 0 | 0 | 5 | 5 |
| Actor | 118/118 | 0 | 0 | 2 | 116 | 118 |
| ArcBrief | 4/4 | 0 | 0 | 0 | 4 | 4 |
| ArcHeader | 14/14 | 0 | 0 | 0 | 14 | 14 |
| ArcLocale | 16/16 | 0 | 0 | 0 | 16 | 16 |
| ArcLocaleMusic | 3/3 | 0 | 0 | 0 | 3 | 3 |
| ArcLocaleRole | 5/5 | 0 | 0 | 0 | 5 | 5 |
| ArcMsic | 9/9 | 0 | 0 | 0 | 9 | 9 |
| ArcPastScene | 2/2 | 0 | 0 | 0 | 2 | 2 |
| ArcPosition | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ArcScene | 3/3 | 0 | 0 | 0 | 3 | 3 |
| ArcSceneMonster | 12/12 | 0 | 0 | 3 | 9 | 12 |
| ArcSceneObject | 3/3 | 0 | 0 | 0 | 3 | 3 |
| Archive | 3/3 | 0 | 0 | 0 | 3 | 3 |
| Array | 4/4 | 0 | 0 | 0 | 4 | 4 |
| ArraySlots | 2/2 | 0 | 0 | 0 | 2 | 2 |
| ArtistPlugIn | 8/8 | 0 | 0 | 0 | 8 | 8 |
| AudioContext | 8/8 | 0 | 0 | 0 | 8 | 8 |
| Average | 8/8 | 0 | 0 | 0 | 8 | 8 |
| BARRIER | 6/6 | 0 | 0 | 0 | 6 | 6 |
| BINK | 95/95 | 0 | 0 | 0 | 95 | 95 |
| BINKIO | 20/20 | 0 | 0 | 0 | 20 | 20 |
| BINKRECT | 4/4 | 0 | 0 | 0 | 4 | 4 |
| BINKSND | 17/17 | 0 | 0 | 0 | 17 | 17 |
| BOSSHURT | 6/6 | 0 | 0 | 0 | 6 | 6 |
| BUNDLEPOINTERS | 9/9 | 0 | 0 | 0 | 9 | 9 |
| BillBoardFace | 5/5 | 0 | 0 | 0 | 5 | 5 |
| BtnGroup | 9/9 | 0 | 0 | 0 | 9 | 9 |
| C2DSpark | 20/20 | 0 | 0 | 0 | 20 | 20 |
| C2DSpark_tagSpark | 12/12 | 0 | 0 | 0 | 12 | 12 |
| C3DSpark | 14/14 | 0 | 0 | 0 | 14 | 14 |
| C3DSpark_tagSpark | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CAccelCentripetalPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CAcceleratedMotionPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CArrayList | 5/5 | 0 | 0 | 0 | 5 | 5 |
| CCBAI | 14/14 | 0 | 0 | 2 | 12 | 14 |
| CCBAIWindow | 10/10 | 0 | 0 | 0 | 10 | 10 |
| CCBAttackSequen | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CCBCamControl | 42/42 | 0 | 0 | 1 | 41 | 42 |
| CCBControl | 15/15 | 0 | 0 | 0 | 15 | 15 |
| CCBControlWindow | 13/13 | 0 | 0 | 0 | 13 | 13 |
| CCBDisplayChain | 7/7 | 0 | 0 | 0 | 7 | 7 |
| CCBEditor | 14/14 | 0 | 0 | 0 | 14 | 14 |
| CCBFiveNimbusWindow | 9/9 | 0 | 0 | 0 | 9 | 9 |
| CCBItemWindow | 7/7 | 0 | 0 | 0 | 7 | 7 |
| CCBLineupWindow | 5/5 | 0 | 0 | 0 | 5 | 5 |
| CCBMagicWindow | 12/12 | 0 | 0 | 0 | 12 | 12 |
| CCBPanelSlot | 20/20 | 0 | 0 | 0 | 20 | 20 |
| CCBParabolaWindow | 3/3 | 0 | 0 | 0 | 3 | 3 |
| CCBProtectWindow | 6/6 | 0 | 0 | 0 | 6 | 6 |
| CCBResultWindow | 17/17 | 0 | 0 | 0 | 17 | 17 |
| CCBRoleState | 89/89 | 0 | 0 | 1 | 88 | 89 |
| CCBRoleStatePanel | 21/21 | 0 | 0 | 0 | 21 | 21 |
| CCBRoleStatePanelM | 21/21 | 0 | 0 | 0 | 21 | 21 |
| CCBRoleStatePanelS | 20/20 | 0 | 0 | 0 | 20 | 20 |
| CCBSkillWindow | 3/3 | 0 | 0 | 0 | 3 | 3 |
| CCBStage | 20/20 | 0 | 0 | 1 | 19 | 20 |
| CCBStageCam | 9/9 | 0 | 0 | 0 | 9 | 9 |
| CCBStageEffect | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CCBStageRole | 98/98 | 0 | 0 | 0 | 98 | 98 |
| CCBStageScene | 109/109 | 0 | 0 | 1 | 108 | 109 |
| CCBStageShadow | 7/7 | 0 | 0 | 0 | 7 | 7 |
| CCBSystem | 39/39 | 0 | 0 | 0 | 39 | 39 |
| CCBTaskGroup | 7/7 | 0 | 0 | 0 | 7 | 7 |
| CCBTaskSlot | 13/13 | 0 | 0 | 0 | 13 | 13 |
| CCBTaskSlot208 | 12/12 | 0 | 0 | 1 | 11 | 12 |
| CCBUI | 59/59 | 0 | 0 | 1 | 58 | 59 |
| CCBUICtrl | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CCBUIPanel | 58/58 | 0 | 0 | 1 | 57 | 58 |
| CCBUI_funcptr_t | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CCCTData | 3/3 | 0 | 0 | 0 | 3 | 3 |
| CCentripetalPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CD3DEnumeration | 14/14 | 0 | 0 | 0 | 14 | 14 |
| CD3DSettings | 21/21 | 0 | 0 | 0 | 21 | 21 |
| CDamplyCentripetalPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CEffAction | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CEffAudio | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CEffBase | 11/11 | 0 | 0 | 0 | 11 | 11 |
| CEffBink | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CEffCallBack | 4/4 | 0 | 0 | 0 | 4 | 4 |
| CEffCamera | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffCustomShape | 22/22 | 0 | 0 | 0 | 22 | 22 |
| CEffCylinder | 35/35 | 0 | 0 | 0 | 35 | 35 |
| CEffExplosive | 32/32 | 0 | 0 | 0 | 32 | 32 |
| CEffGrid | 32/32 | 0 | 0 | 0 | 32 | 32 |
| CEffGroupNode | 6/6 | 0 | 0 | 0 | 6 | 6 |
| CEffMeteor | 34/34 | 0 | 0 | 0 | 34 | 34 |
| CEffMgr | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CEffModel | 9/9 | 0 | 0 | 0 | 9 | 9 |
| CEffObj | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CEffQuad | 19/19 | 0 | 0 | 0 | 19 | 19 |
| CEffSParticle | 11/11 | 0 | 0 | 0 | 11 | 11 |
| CEffShock | 29/29 | 0 | 0 | 0 | 29 | 29 |
| CEffTemplate | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffTime | 0/1 | 0 | 0 | 0 | 0 | 1 |
| CEffTrackCustomShape | 7/4 | 0 | 0 | 0 | 7 | 4 |
| CEffTrackCylinder | 7/4 | 0 | 0 | 0 | 7 | 4 |
| CEffTrackGrid | 7/4 | 0 | 0 | 0 | 7 | 4 |
| CEffTrackModel | 7/4 | 0 | 0 | 0 | 7 | 4 |
| CEffTrackQuad | 7/4 | 0 | 0 | 0 | 7 | 4 |
| CEffTrackSParticle | 4/1 | 0 | 0 | 0 | 4 | 1 |
| CEffect | 13/13 | 0 | 0 | 0 | 13 | 13 |
| CEffectBubble | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CEffectSimple | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CEffectSystem | 14/14 | 0 | 0 | 0 | 14 | 14 |
| CEffgbParticle | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CEmitter | 3/3 | 0 | 0 | 0 | 3 | 3 |
| CFadeColorPolicy | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CFadeInAlphaPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CFadeOutAlphaPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CG_Edit | 18/18 | 0 | 0 | 0 | 18 | 18 |
| CG_Entry | 11/11 | 0 | 0 | 0 | 11 | 11 |
| CG_Scene | 34/34 | 0 | 0 | 0 | 34 | 34 |
| CG_Scene_ArrayErase | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CG_UI | 63/63 | 0 | 0 | 0 | 63 | 63 |
| CIniFile | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CJ_FindFile | 7/7 | 0 | 0 | 0 | 7 | 7 |
| CLoad3DS | 5/5 | 0 | 0 | 0 | 5 | 5 |
| CMeteorChain | 14/14 | 0 | 0 | 0 | 14 | 14 |
| COLLIDE_DATA | 4/4 | 0 | 0 | 0 | 4 | 4 |
| CONTEXT | 23/23 | 0 | 0 | 0 | 23 | 23 |
| COnceFramePolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CPK | 10/10 | 0 | 0 | 0 | 10 | 10 |
| CPKFile | 12/12 | 0 | 0 | 0 | 12 | 12 |
| CPPEH_RECORD | 3/3 | 0 | 0 | 0 | 3 | 3 |
| CParticleEffect | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CParticleSystem | 31/31 | 0 | 0 | 0 | 31 | 31 |
| CParticleSystem_ParticleAttribute | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CParticleSystem_ParticleUnit | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CPolicy | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CRandomColorPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CReBackFramePolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CRenderTarget | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CRenderTarget2 | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CResistanceMotionPolicy | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CRotateEmitterPolicy | 3/3 | 0 | 0 | 0 | 3 | 3 |
| CSEHException | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CScreenMode | 70/70 | 0 | 0 | 3 | 67 | 70 |
| CSimpleDirPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CSimplePosPolicy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CTaskTpl | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffAction | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffAudio | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffBink | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffCallBack | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffCamera | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffCustomShape | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffCylinder | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffExplosive | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffGrid | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffMeteor | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffModel | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffQuad | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffQuake | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffSParticle | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffShock | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffTemplate | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffTime | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTaskTpl_tagEffTaskParam_CEffgbParticle | 8/8 | 0 | 0 | 0 | 8 | 8 |
| CTrail | 11/11 | 0 | 0 | 0 | 11 | 11 |
| CUSTOMSHAPEVERTEX | 4/4 | 0 | 0 | 0 | 4 | 4 |
| CUtil | 18/18 | 0 | 0 | 0 | 18 | 18 |
| Camera | 47/47 | 0 | 0 | 0 | 47 | 47 |
| CameraCmd | 2/2 | 0 | 0 | 0 | 2 | 2 |
| CameraCtrl | 88/88 | 0 | 0 | 1 | 87 | 88 |
| CameraParam | 4/4 | 0 | 0 | 0 | 4 | 4 |
| CameraSystem | 1/1 | 0 | 0 | 0 | 1 | 1 |
| CatchableType | 5/5 | 0 | 0 | 0 | 5 | 5 |
| CatchableTypeArray | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ChoseCompose | 12/12 | 0 | 0 | 0 | 12 | 12 |
| ColRet | 5/5 | 0 | 0 | 0 | 5 | 5 |
| Collide_Ray | 8/8 | 0 | 0 | 0 | 8 | 8 |
| Color4ub | 4/4 | 0 | 0 | 0 | 4 | 4 |
| Combat | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ComboAttack | 13/13 | 0 | 0 | 0 | 13 | 13 |
| Comp_Donate | 3/3 | 0 | 0 | 0 | 3 | 3 |
| Comp_DonateUI | 31/31 | 0 | 0 | 0 | 31 | 31 |
| Comp_Donate_Detail | 9/9 | 0 | 0 | 0 | 9 | 9 |
| ComposeUI | 9/9 | 0 | 0 | 0 | 9 | 9 |
| Config | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ConfigFile | 1/1 | 0 | 0 | 0 | 1 | 1 |
| DICOLORSET | 9/9 | 0 | 0 | 0 | 9 | 9 |
| DIDEVCAPS | 11/11 | 0 | 0 | 0 | 11 | 11 |
| DIDEVICEINSTANCEA | 9/9 | 0 | 0 | 0 | 9 | 9 |
| DIDEVICEOBJECTDATA | 5/5 | 0 | 0 | 0 | 5 | 5 |
| DIDEVICEOBJECTINSTANCEA | 15/15 | 0 | 0 | 0 | 15 | 15 |
| DIEFFECT | 14/14 | 0 | 0 | 0 | 14 | 14 |
| DIEFFECTINFOA | 6/6 | 0 | 0 | 0 | 6 | 6 |
| DIEFFESCAPE | 6/6 | 0 | 0 | 0 | 6 | 6 |
| DIENVELOPE | 5/5 | 0 | 0 | 0 | 5 | 5 |
| DIFILEEFFECT | 4/4 | 0 | 0 | 0 | 4 | 4 |
| DIPROPDWORD | 2/2 | 0 | 0 | 0 | 2 | 2 |
| DIPROPHEADER | 4/4 | 0 | 0 | 0 | 4 | 4 |
| DPINFO | 3/3 | 0 | 0 | 0 | 3 | 3 |
| DPINFO___unnamed | 1/1 | 0 | 0 | 0 | 1 | 1 |
| DataConst | 2/2 | 0 | 0 | 0 | 2 | 2 |
| DealData | 7/7 | 0 | 0 | 0 | 7 | 7 |
| DealUI | 23/23 | 0 | 0 | 0 | 23 | 23 |
| DisplayConfig | 4/4 | 0 | 0 | 0 | 4 | 4 |
| ECBRoleSpecState | 1/1 | 0 | 0 | 0 | 1 | 1 |
| EH3_EXCEPTION_REGISTRATION | 4/4 | 0 | 0 | 0 | 4 | 4 |
| EffAudioNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| EffBinkNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| EffCallBackNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| EffModeParam | 3/3 | 0 | 0 | 0 | 3 | 3 |
| EffMultiPassNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| EffObjectPool | 3/3 | 0 | 0 | 0 | 3 | 3 |
| EffTargetPool | 2/2 | 0 | 0 | 0 | 2 | 2 |
| EffectInfo | 4/4 | 0 | 0 | 0 | 4 | 4 |
| EffectItem | 3/3 | 0 | 0 | 0 | 3 | 3 |
| EquipUI | 90/90 | 0 | 0 | 0 | 90 | 90 |
| ExternalStatistics | 1/1 | 0 | 0 | 0 | 1 | 1 |
| FILETIME | 2/2 | 0 | 0 | 0 | 2 | 2 |
| FLOATING_SAVE_AREA | 8/8 | 0 | 0 | 0 | 8 | 8 |
| FLTSTAGE | 2/2 | 0 | 0 | 0 | 2 | 2 |
| FightInfo | 15/15 | 0 | 0 | 0 | 15 | 15 |
| FightItem | 29/29 | 0 | 0 | 1 | 28 | 29 |
| FightItemScriptBlock | 2/2 | 0 | 0 | 0 | 2 | 2 |
| FightSkill | 28/28 | 0 | 0 | 0 | 28 | 28 |
| FindArc | 3/3 | 0 | 0 | 0 | 3 | 3 |
| FontPrint3DInfo | 9/9 | 0 | 0 | 0 | 9 | 9 |
| FontPrintInfo | 11/11 | 0 | 0 | 0 | 11 | 11 |
| FontSortInfoObj | 2/2 | 0 | 0 | 0 | 2 | 2 |
| FrameTex | 1/1 | 0 | 0 | 0 | 1 | 1 |
| FuncInfoV1 | 7/7 | 0 | 0 | 0 | 7 | 7 |
| GRP_KEYREG | 4/4 | 0 | 0 | 0 | 4 | 4 |
| GRPinput | 38/38 | 0 | 0 | 0 | 38 | 38 |
| GameObject | 0/1 | 0 | 0 | 0 | 0 | 1 |
| GeomNode | 7/7 | 0 | 0 | 0 | 7 | 7 |
| GeomNote | 3/3 | 0 | 0 | 0 | 3 | 3 |
| GhostParam | 5/5 | 0 | 0 | 0 | 5 | 5 |
| Glow | 4/4 | 0 | 0 | 0 | 4 | 4 |
| GlowObj | 4/4 | 0 | 0 | 0 | 4 | 4 |
| GrayScale | 2/2 | 0 | 0 | 0 | 2 | 2 |
| HandlerType | 4/4 | 0 | 0 | 0 | 4 | 4 |
| HeadMsg | 5/5 | 0 | 0 | 0 | 5 | 5 |
| IMAGE_DATA_DIRECTORY | 2/2 | 0 | 0 | 0 | 2 | 2 |
| IMAGE_FILE_HEADER | 7/7 | 0 | 0 | 0 | 7 | 7 |
| IMAGE_OPTIONAL_HEADER32 | 30/30 | 0 | 0 | 0 | 30 | 30 |
| InputSystem | 1/1 | 0 | 0 | 0 | 1 | 1 |
| Inventory | 4/4 | 0 | 0 | 0 | 4 | 4 |
| Iostream_init | 1/1 | 0 | 0 | 0 | 1 | 1 |
| JusticeBookUI | 53/53 | 0 | 0 | 0 | 53 | 53 |
| KeyFrame | 9/9 | 0 | 0 | 0 | 9 | 9 |
| LARGE_INTEGER | 4/4 | 0 | 0 | 0 | 4 | 4 |
| LEVELPARAM | 2/2 | 0 | 0 | 0 | 2 | 2 |
| LINEUPINFO | 1/1 | 0 | 0 | 0 | 1 | 1 |
| LINEUP_SEQUENCE | 1/1 | 0 | 0 | 0 | 1 | 1 |
| LayerNode | 4/4 | 0 | 0 | 0 | 4 | 4 |
| LineupComp | 14/14 | 0 | 0 | 1 | 13 | 14 |
| LineupPlank | 4/4 | 0 | 0 | 0 | 4 | 4 |
| LineupUI | 65/65 | 0 | 0 | 0 | 65 | 65 |
| LinkerVersion | 2/2 | 0 | 0 | 0 | 2 | 2 |
| Logger | 12/12 | 0 | 0 | 2 | 10 | 12 |
| MIXSTAGE | 3/3 | 0 | 0 | 0 | 3 | 3 |
| MUIDialog | 11/11 | 0 | 0 | 2 | 9 | 11 |
| MUIDialogMgr | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MU_SortFun | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MXCEft | 4/4 | 0 | 0 | 0 | 4 | 4 |
| MXFire | 8/8 | 0 | 0 | 0 | 8 | 8 |
| MXPoisonFog | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MXSavePoint | 7/7 | 0 | 0 | 0 | 7 | 7 |
| MXTransport | 11/11 | 0 | 0 | 0 | 11 | 11 |
| MagicUI | 76/76 | 0 | 0 | 0 | 76 | 76 |
| MainEquipUI | 76/76 | 0 | 0 | 0 | 76 | 76 |
| MainPropUI | 80/80 | 0 | 0 | 0 | 80 | 80 |
| Math | 1/1 | 0 | 0 | 0 | 1 | 1 |
| Matrix4 | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MatrixStack | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MeshFx | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MeshFxCreator | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MiniGame1 | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MiniGame2Scene | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MiniGame3 | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MonsterStar | 4/4 | 0 | 0 | 0 | 4 | 4 |
| MvcController | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MvcViewport | 1/1 | 0 | 0 | 0 | 1 | 1 |
| MyMdl | 3/3 | 0 | 0 | 0 | 3 | 3 |
| NGHHURT | 6/6 | 0 | 0 | 0 | 6 | 6 |
| NMHDR | 3/3 | 0 | 0 | 0 | 3 | 3 |
| NPC | 19/19 | 0 | 0 | 0 | 19 | 19 |
| NPCInfo | 21/21 | 0 | 0 | 0 | 21 | 21 |
| NameSys | 6/6 | 0 | 0 | 0 | 6 | 6 |
| NameSys_NAMEFLAG | 1/1 | 0 | 0 | 0 | 1 | 1 |
| NavFace | 1/1 | 0 | 0 | 0 | 1 | 1 |
| NavFaceLayer | 5/5 | 0 | 0 | 0 | 5 | 5 |
| NavHeader | 5/5 | 0 | 0 | 0 | 5 | 5 |
| NavTile | 3/3 | 0 | 0 | 0 | 3 | 3 |
| NavTileLayer | 6/6 | 0 | 0 | 0 | 6 | 6 |
| NavTriangle | 3/3 | 0 | 0 | 0 | 3 | 3 |
| NavigationInfo | 3/3 | 0 | 0 | 0 | 3 | 3 |
| Note_Item | 12/12 | 0 | 0 | 0 | 12 | 12 |
| OBJHELPER | 6/6 | 0 | 0 | 0 | 6 | 6 |
| ORect | 2/2 | 0 | 0 | 0 | 2 | 2 |
| ObjLockInput | 3/3 | 0 | 0 | 0 | 3 | 3 |
| ObjParam | 13/13 | 0 | 0 | 0 | 13 | 13 |
| Object | 5/5 | 0 | 0 | 0 | 5 | 5 |
| Object3D | 34/34 | 0 | 0 | 0 | 34 | 34 |
| ObjectCamera | 19/19 | 0 | 0 | 0 | 19 | 19 |
| ObjectInfo | 34/34 | 0 | 0 | 0 | 34 | 34 |
| ObjectInfoBase | 4/4 | 0 | 0 | 0 | 4 | 4 |
| OpenBaseFile | 1/1 | 0 | 0 | 0 | 1 | 1 |
| OpenFNWindow | 3/3 | 0 | 0 | 0 | 3 | 3 |
| OpenNULLFile | 1/1 | 0 | 0 | 0 | 1 | 1 |
| OpenSceneFile | 1/1 | 0 | 0 | 0 | 1 | 1 |
| OutFile | 9/9 | 0 | 0 | 0 | 9 | 9 |
| PAL3 | 43/43 | 0 | 0 | 0 | 43 | 43 |
| PAL_GDB | 6/6 | 0 | 0 | 0 | 6 | 6 |
| PARTICLEVERTEX | 4/4 | 0 | 0 | 0 | 4 | 4 |
| PMD | 3/3 | 0 | 0 | 0 | 3 | 3 |
| PMFN | 1/1 | 0 | 0 | 0 | 1 | 1 |
| PalScript | 44/44 | 0 | 0 | 4 | 40 | 44 |
| PalScriptAnimTimer | 2/2 | 0 | 0 | 0 | 2 | 2 |
| PalScriptBlendTimer | 2/2 | 0 | 0 | 0 | 2 | 2 |
| PalScriptDialogOverlay | 1/1 | 0 | 0 | 1 | 0 | 1 |
| PalScriptFadeInTimer | 2/2 | 0 | 0 | 0 | 2 | 2 |
| PalScriptFadeOutTimer | 2/2 | 0 | 0 | 0 | 2 | 2 |
| PalScriptIdleObj | 2/2 | 0 | 0 | 0 | 2 | 2 |
| PalScriptMgr | 202/202 | 0 | 0 | 0 | 202 | 202 |
| PalScriptProgressTimer | 2/2 | 0 | 0 | 0 | 2 | 2 |
| PalScriptRoleSlotOverlay | 1/1 | 0 | 0 | 1 | 0 | 1 |
| PalScriptSlotStateOverlay | 9/9 | 0 | 0 | 0 | 9 | 9 |
| PalScriptWaitObj | 2/2 | 0 | 0 | 0 | 2 | 2 |
| PalScriptWaitTimer | 2/2 | 0 | 0 | 0 | 2 | 2 |
| ParabolaCalculator | 6/6 | 0 | 0 | 0 | 6 | 6 |
| ParabolaCalculator_PRBL_STATE | 1/1 | 0 | 0 | 0 | 1 | 1 |
| Param0 | 5/5 | 0 | 0 | 0 | 5 | 5 |
| Param1 | 5/5 | 0 | 0 | 0 | 5 | 5 |
| Param2 | 8/8 | 0 | 0 | 0 | 8 | 8 |
| Parent_Data | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ParticleEffect | 3/3 | 0 | 0 | 0 | 3 | 3 |
| ParticleVisNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| PathFinder | 3/3 | 0 | 0 | 0 | 3 | 3 |
| PathObj | 14/14 | 0 | 0 | 0 | 14 | 14 |
| PlayerAtt | 24/24 | 0 | 0 | 0 | 24 | 24 |
| PlayerAtts | 3/3 | 0 | 0 | 0 | 3 | 3 |
| PlayerItem | 3/3 | 0 | 0 | 0 | 3 | 3 |
| PlayerItemSortFun | 1/1 | 0 | 0 | 0 | 1 | 1 |
| PlayerSkill | 4/4 | 0 | 0 | 0 | 4 | 4 |
| PolyLine | 2/2 | 0 | 0 | 0 | 2 | 2 |
| PropUI | 95/95 | 0 | 0 | 0 | 95 | 95 |
| ProtectPanel | 3/3 | 0 | 0 | 0 | 3 | 3 |
| PtrArray | 4/4 | 0 | 0 | 0 | 4 | 4 |
| PtrVec | 4/4 | 0 | 0 | 0 | 4 | 4 |
| PurgeEffect | 6/6 | 0 | 0 | 0 | 6 | 6 |
| RC_ARG | 5/5 | 0 | 0 | 0 | 5 | 5 |
| RELIVEPARAM | 4/4 | 0 | 0 | 0 | 4 | 4 |
| RGNDATAHEADER | 5/5 | 0 | 0 | 0 | 5 | 5 |
| RenderTarget | 39/39 | 0 | 0 | 0 | 39 | 39 |
| RenderTarget2 | 1/1 | 0 | 0 | 0 | 1 | 1 |
| RenderTarget3 | 1/1 | 0 | 0 | 0 | 1 | 1 |
| RenderTarget4 | 1/1 | 0 | 0 | 0 | 1 | 1 |
| RenderTargetNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| Reoccupy | 1/1 | 0 | 0 | 0 | 1 | 1 |
| RestScript | 3/3 | 0 | 0 | 0 | 3 | 3 |
| Role | 47/47 | 0 | 0 | 0 | 47 | 47 |
| RoleAtt | 35/35 | 0 | 0 | 1 | 34 | 35 |
| RoleAttRemarkSkills | 1/1 | 0 | 0 | 1 | 0 | 1 |
| RoleCamera | 42/40 | 0 | 0 | 0 | 42 | 40 |
| RoleCameraCtrl | 1/1 | 0 | 0 | 0 | 1 | 1 |
| RoleCtrl | 7/7 | 0 | 0 | 0 | 7 | 7 |
| RoleFadeIn | 3/3 | 0 | 0 | 0 | 3 | 3 |
| RoleFadeOut | 3/3 | 0 | 0 | 0 | 3 | 3 |
| RoleShadow | 11/11 | 0 | 0 | 0 | 11 | 11 |
| RoleStatePanel | 11/11 | 0 | 0 | 1 | 10 | 11 |
| RoleSystem | 150/150 | 0 | 0 | 4 | 146 | 150 |
| RoleSystemTeamSlotOverlay | 1/1 | 0 | 0 | 1 | 0 | 1 |
| RoleTask | 5/5 | 0 | 0 | 0 | 5 | 5 |
| RoleTaskLine | 4/4 | 0 | 0 | 0 | 4 | 4 |
| RoleTaskPool | 4/4 | 0 | 0 | 0 | 4 | 4 |
| Role_SPECIAL_ACTION | 1/1 | 0 | 0 | 0 | 1 | 1 |
| RotateInvObj | 3/3 | 0 | 0 | 0 | 3 | 3 |
| RotateObj | 5/5 | 0 | 0 | 0 | 5 | 5 |
| SCNFile | 5/5 | 0 | 0 | 0 | 5 | 5 |
| SCNHeader | 6/6 | 0 | 0 | 0 | 6 | 6 |
| SPECIAL_ACTION | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SSE4xMatrix | 16/16 | 0 | 0 | 0 | 16 | 16 |
| S_Distribute | 4/4 | 0 | 0 | 0 | 4 | 4 |
| SaleUI | 62/62 | 0 | 0 | 0 | 62 | 62 |
| SaleUI_SortData | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SaveTask | 3/3 | 0 | 0 | 0 | 3 | 3 |
| SceHeader | 3/3 | 0 | 0 | 0 | 3 | 3 |
| SceIndex | 3/3 | 0 | 0 | 0 | 3 | 3 |
| SceOpcodeEntry | 5/5 | 0 | 0 | 0 | 5 | 5 |
| Scene | 18/18 | 0 | 0 | 0 | 18 | 18 |
| SceneInfo | 12/12 | 0 | 0 | 0 | 12 | 12 |
| SceneMap | 3/3 | 0 | 0 | 0 | 3 | 3 |
| SceneMapObj | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SceneMapPlayer | 10/10 | 0 | 0 | 0 | 10 | 10 |
| SceneMgr | 20/20 | 0 | 0 | 2 | 18 | 20 |
| SceneMgrCamBlock | 14/14 | 0 | 0 | 0 | 14 | 14 |
| SceneObj | 46/46 | 0 | 0 | 0 | 46 | 46 |
| SceneObjParam | 4/4 | 0 | 0 | 0 | 4 | 4 |
| SceneObjScript | 3/3 | 0 | 0 | 0 | 3 | 3 |
| SceneObj_Common_State | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SceneObj_SubObj | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SceneProp | 15/15 | 0 | 0 | 0 | 15 | 15 |
| SceneVisNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ScreenEffect | 4/4 | 0 | 0 | 0 | 4 | 4 |
| ScreenEffectMgr | 16/16 | 0 | 0 | 0 | 16 | 16 |
| ScreenEffectNode | 2/2 | 0 | 0 | 0 | 2 | 2 |
| ScreenFadeIn | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ScriptCounter | 4/4 | 0 | 0 | 0 | 4 | 4 |
| ScriptData | 7/7 | 0 | 0 | 0 | 7 | 7 |
| ScriptHelper | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ScriptObj | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ScriptPoolPage | 5/5 | 0 | 0 | 0 | 5 | 5 |
| ScriptSystem | 58/58 | 0 | 0 | 0 | 58 | 58 |
| ScriptSystemData | 216/216 | 0 | 0 | 8 | 208 | 216 |
| ScriptVM | 26/26 | 0 | 0 | 0 | 26 | 26 |
| ScriptWaitFrm | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SkillData | 2/2 | 0 | 0 | 0 | 2 | 2 |
| SkyBox | 6/6 | 0 | 0 | 0 | 6 | 6 |
| SkyboxEff | 24/24 | 0 | 0 | 0 | 24 | 24 |
| SkyboxEffMgr | 2/2 | 0 | 0 | 0 | 2 | 2 |
| SkyboxEffTex | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SoundAttachObj | 3/3 | 0 | 0 | 0 | 3 | 3 |
| SoundContext | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SoundItem | 2/2 | 0 | 0 | 0 | 2 | 2 |
| SoundMgr | 13/13 | 0 | 0 | 0 | 13 | 13 |
| SoundSystem | 1/1 | 0 | 0 | 0 | 1 | 1 |
| StateUI | 66/66 | 0 | 0 | 0 | 66 | 66 |
| String | 1/1 | 0 | 0 | 0 | 1 | 1 |
| StringTable | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SwitchVariable | 1/1 | 0 | 0 | 0 | 1 | 1 |
| SwordUI | 134/134 | 0 | 0 | 0 | 134 | 134 |
| SystemUI | 64/64 | 0 | 0 | 0 | 64 | 64 |
| TaskBookUI | 46/46 | 0 | 0 | 0 | 46 | 46 |
| TaskMgr | 8/8 | 0 | 0 | 0 | 8 | 8 |
| TaskMgr_SceneObjParam_SceneObj | 1/1 | 0 | 0 | 0 | 1 | 1 |
| TextureLib | 40/40 | 0 | 0 | 1 | 39 | 40 |
| TextureLibDataBase | 7/7 | 0 | 0 | 0 | 7 | 7 |
| TextureLib_Data | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ThrowInfo | 3/3 | 0 | 0 | 0 | 3 | 3 |
| TileMap | 1/1 | 0 | 0 | 0 | 1 | 1 |
| TimeCtl | 3/3 | 0 | 0 | 0 | 3 | 3 |
| Triangle | 2/2 | 0 | 0 | 0 | 2 | 2 |
| TryBlockMapEntry | 5/5 | 0 | 0 | 0 | 5 | 5 |
| TxtFile | 4/4 | 0 | 0 | 0 | 4 | 4 |
| UI3DCtrl | 19/19 | 0 | 0 | 0 | 19 | 19 |
| UI3DModelNode | 8/8 | 0 | 0 | 0 | 8 | 8 |
| UI3DObj | 6/6 | 0 | 0 | 0 | 6 | 6 |
| UIAnimCtrl | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIAnimate | 5/5 | 0 | 0 | 0 | 5 | 5 |
| UIAnimateCtrl | 8/8 | 0 | 0 | 0 | 8 | 8 |
| UIAnimateCtrlEX | 6/6 | 0 | 0 | 0 | 6 | 6 |
| UIBase | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIBigDialog | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIBigMap | 25/25 | 0 | 0 | 0 | 25 | 25 |
| UIButton | 17/17 | 0 | 0 | 0 | 17 | 17 |
| UIButtonEX | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIButtonEXA | 5/5 | 0 | 0 | 0 | 5 | 5 |
| UIButton_UIBUTTON_STATE | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UICamera | 15/15 | 0 | 0 | 0 | 15 | 15 |
| UICaption | 5/5 | 0 | 0 | 0 | 5 | 5 |
| UIChatRest | 38/38 | 0 | 0 | 0 | 38 | 38 |
| UICoverFrm | 51/51 | 0 | 0 | 0 | 51 | 51 |
| UICursor | 6/6 | 0 | 0 | 0 | 6 | 6 |
| UIDialog | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIDragBar | 33/33 | 0 | 0 | 0 | 33 | 33 |
| UIEmote | 6/6 | 0 | 0 | 0 | 6 | 6 |
| UIFlexBar | 4/4 | 0 | 0 | 0 | 4 | 4 |
| UIFrameContainer | 2/2 | 0 | 0 | 0 | 2 | 2 |
| UIFrameWnd | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIGameFrm | 66/66 | 0 | 0 | 4 | 62 | 66 |
| UIGameOver | 3/3 | 0 | 0 | 0 | 3 | 3 |
| UIGroupCtrl | 19/19 | 0 | 0 | 0 | 19 | 19 |
| UIHeadDialog | 6/5 | 0 | 0 | 0 | 6 | 5 |
| UIInventory | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIItem | 7/7 | 0 | 0 | 0 | 7 | 7 |
| UILBColumn | 3/3 | 0 | 0 | 0 | 3 | 3 |
| UILBItem | 3/3 | 0 | 0 | 0 | 3 | 3 |
| UIListBox | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIListView | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UILoadingFrm | 5/5 | 0 | 0 | 0 | 5 | 5 |
| UIManager | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIMap | 16/16 | 0 | 0 | 0 | 16 | 16 |
| UINote | 2/2 | 0 | 0 | 0 | 2 | 2 |
| UIObj | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIPar_Meteor | 12/12 | 0 | 0 | 0 | 12 | 12 |
| UIPar_Star | 9/9 | 0 | 0 | 0 | 9 | 9 |
| UIPar_TimeCtrl | 3/3 | 0 | 0 | 0 | 3 | 3 |
| UIParabolaCtrl | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIParticle | 42/42 | 0 | 0 | 0 | 42 | 42 |
| UIPosMaker | 3/3 | 0 | 0 | 0 | 3 | 3 |
| UIProgressBar | 38/38 | 0 | 0 | 0 | 38 | 38 |
| UIPushButton | 14/14 | 0 | 0 | 0 | 14 | 14 |
| UIQuadManager | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIRenderObj | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIRoleDialog | 14/13 | 0 | 0 | 0 | 13 | 13 |
| UIRoleSelect | 5/4 | 0 | 0 | 0 | 5 | 4 |
| UIRoleSelectDialog | 11/11 | 0 | 0 | 0 | 11 | 11 |
| UIScene | 37/37 | 0 | 0 | 0 | 37 | 37 |
| UISceneFace | 7/7 | 0 | 0 | 0 | 7 | 7 |
| UISceneFrm | 2/2 | 0 | 0 | 0 | 2 | 2 |
| UISceneMap | 6/6 | 0 | 0 | 0 | 6 | 6 |
| UISceneObj | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIScenePanel | 71/71 | 0 | 0 | 0 | 71 | 71 |
| UIScrollBar | 20/20 | 0 | 0 | 0 | 20 | 20 |
| UIScrollBar_SB_AREA | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UISelectDialog | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UISlider | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIStatic | 18/18 | 0 | 0 | 0 | 18 | 18 |
| UIStaticCB | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIStaticEX | 8/8 | 0 | 0 | 0 | 8 | 8 |
| UIStaticEXA | 2/2 | 0 | 0 | 0 | 2 | 2 |
| UIStaticFlex | 7/7 | 0 | 0 | 0 | 7 | 7 |
| UIStaticFlex_State | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIStaticFlip | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UIStaticRM | 9/9 | 0 | 0 | 0 | 9 | 9 |
| UISystem | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UITabBtn | 3/3 | 0 | 0 | 0 | 3 | 3 |
| UITabCtrl | 4/4 | 0 | 0 | 0 | 4 | 4 |
| UITextArea | 15/15 | 0 | 0 | 0 | 15 | 15 |
| UITextureArray | 2/2 | 0 | 0 | 0 | 2 | 2 |
| UITitle | 37/37 | 0 | 0 | 0 | 37 | 37 |
| UITitle_ArcSave | 1/1 | 0 | 0 | 0 | 1 | 1 |
| UITitle_BBTY | 17/17 | 0 | 0 | 0 | 17 | 17 |
| UITitle_JDHY | 28/28 | 0 | 0 | 0 | 28 | 28 |
| UITitle_QCYM | 9/9 | 0 | 0 | 0 | 9 | 9 |
| UITitle_XJTM | 23/23 | 0 | 0 | 0 | 23 | 23 |
| UITitle_YXXX | 11/11 | 0 | 0 | 0 | 11 | 11 |
| UIWnd | 10/10 | 0 | 0 | 0 | 10 | 10 |
| UnderWater | 6/6 | 0 | 0 | 0 | 6 | 6 |
| UnwindMapEntry | 2/2 | 0 | 0 | 0 | 2 | 2 |
| VertPoolMgr | 1/1 | 0 | 0 | 0 | 1 | 1 |
| VideoPlayer | 1/1 | 0 | 0 | 0 | 1 | 1 |
| WAVEFORMAT | 5/5 | 0 | 0 | 0 | 5 | 5 |
| WeatherEffectNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| WishPool | 3/3 | 0 | 0 | 0 | 3 | 3 |
| XJ_Pic | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _ADPCMDATATAG | 11/11 | 0 | 0 | 0 | 11 | 11 |
| _Btn_BtnID | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _CLOUD | 11/11 | 0 | 0 | 0 | 11 | 11 |
| _CONTEXT | 25/25 | 0 | 0 | 0 | 25 | 25 |
| _Collvec | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _Console | 9/9 | 0 | 0 | 0 | 9 | 9 |
| _Console__ConCmd | 1/1 | 0 | 0 | 0 | 1 | 1 |
| _Ctypevec | 4/4 | 0 | 0 | 0 | 4 | 4 |
| _Cvtvec | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _DIACTIONA | 7/7 | 0 | 0 | 0 | 7 | 7 |
| _DIACTIONFORMATA | 14/14 | 0 | 0 | 0 | 14 | 14 |
| _DICOLORSET | 9/9 | 0 | 0 | 0 | 9 | 9 |
| _DICONFIGUREDEVICESPARAMSA | 8/8 | 0 | 0 | 0 | 8 | 8 |
| _DIDATAFORMAT | 6/6 | 0 | 0 | 0 | 6 | 6 |
| _DIDEVICEIMAGEINFOA | 9/9 | 0 | 0 | 0 | 9 | 9 |
| _DIDEVICEIMAGEINFOHEADERA | 9/9 | 0 | 0 | 0 | 9 | 9 |
| _DIG_DRIVER | 68/68 | 0 | 0 | 0 | 68 | 68 |
| _DIOBJECTDATAFORMAT | 4/4 | 0 | 0 | 0 | 4 | 4 |
| _EH3_EXCEPTION_REGISTRATION | 4/4 | 0 | 0 | 0 | 4 | 4 |
| _EXCEPTION_POINTERS | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _EXCEPTION_RECORD | 6/6 | 0 | 0 | 0 | 6 | 6 |
| _FLOATING_SAVE_AREA | 9/9 | 0 | 0 | 0 | 9 | 9 |
| _FLOORPARAM | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _FLTPROVIDER | 18/18 | 0 | 0 | 0 | 18 | 18 |
| _IMAGE_DATA_DIRECTORY | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _IMAGE_DOS_HEADER | 19/19 | 0 | 0 | 0 | 19 | 19 |
| _IMAGE_FILE_HEADER | 7/7 | 0 | 0 | 0 | 7 | 7 |
| _IMAGE_NT_HEADERS | 3/3 | 0 | 0 | 0 | 3 | 3 |
| _IMAGE_OPTIONAL_HEADER | 31/31 | 0 | 0 | 0 | 31 | 31 |
| _Item | 6/6 | 0 | 0 | 0 | 6 | 6 |
| _Item_List_Info | 8/8 | 0 | 0 | 0 | 8 | 8 |
| _LARGE_INTEGER | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _MapElement | 6/6 | 0 | 0 | 0 | 6 | 6 |
| _PMD | 3/3 | 0 | 0 | 0 | 3 | 3 |
| _PURGE_INFO | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _PlugInfo | 16/16 | 0 | 0 | 0 | 16 | 16 |
| _RGNDATA | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _RGNDATAHEADER | 5/5 | 0 | 0 | 0 | 5 | 5 |
| _SAMPLE | 50/50 | 0 | 0 | 0 | 50 | 50 |
| _SCOPETABLE_ENTRY | 3/3 | 0 | 0 | 0 | 3 | 3 |
| _STREAM | 50/50 | 0 | 0 | 0 | 50 | 50 |
| _SUBMAP | 14/14 | 0 | 0 | 0 | 14 | 14 |
| _Tex_uv | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _Texture_Info | 14/14 | 0 | 0 | 0 | 14 | 14 |
| _Texture_uv | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _TimeMgr | 3/3 | 0 | 0 | 0 | 3 | 3 |
| _TypeDescriptor | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _UDACCEL | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _UIPOS | 3/3 | 0 | 0 | 0 | 3 | 3 |
| _XCPT_ACTION | 3/3 | 0 | 0 | 0 | 3 | 3 |
| _better_note | 2/2 | 0 | 0 | 0 | 2 | 2 |
| _btnOPTDATA | 4/4 | 0 | 0 | 0 | 4 | 4 |
| _count_string | 3/3 | 0 | 0 | 0 | 3 | 3 |
| _cpinfo | 3/3 | 0 | 0 | 0 | 3 | 3 |
| _s__CatchableType | 5/5 | 0 | 0 | 0 | 5 | 5 |
| _s__CatchableTypeArray | 1/1 | 0 | 0 | 0 | 1 | 1 |
| _strflt | 4/4 | 0 | 0 | 0 | 4 | 4 |
| code_page_info | 3/3 | 0 | 0 | 0 | 3 | 3 |
| collision | 1/1 | 0 | 0 | 0 | 1 | 1 |
| direction_emitter_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| doubleint | 1/1 | 0 | 0 | 0 | 1 | 1 |
| elelife_emitter_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| elerandvec_emitter_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| emissionrate_emitter_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| errentry | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbAABBox | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbActor | 7/7 | 0 | 0 | 0 | 7 | 7 |
| gbActorDef | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbActorExpNode | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbActorMgr | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbAnimKey | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbAnimScript | 12/12 | 0 | 0 | 0 | 12 | 12 |
| gbAudioManager | 13/13 | 0 | 0 | 0 | 13 | 13 |
| gbAudioMgrDesc | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbBaseMesh | 9/9 | 0 | 0 | 0 | 9 | 9 |
| gbBinkVideo | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbCamControler | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbCamera | 16/16 | 0 | 0 | 0 | 16 | 16 |
| gbChain1D | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbChain1DNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbClearParam | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbColorFlt | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbColorQuad | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbColorQuadChannels | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbCursorRes | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbDropDesc | 9/9 | 0 | 0 | 0 | 9 | 9 |
| gbDropGroup | 16/16 | 0 | 0 | 0 | 16 | 16 |
| gbDropUnit | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbDynVertBuf | 12/12 | 0 | 0 | 0 | 12 | 12 |
| gbEffectMgr | 8/8 | 0 | 0 | 0 | 8 | 8 |
| gbEmitterData | 8/8 | 0 | 0 | 0 | 8 | 8 |
| gbEmitterShape | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbEmitterSphere | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbEmitterSquare | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbFileStream | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbFogParam | 7/7 | 0 | 0 | 0 | 7 | 7 |
| gbGammaRamp | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbGeomNode | 18/18 | 0 | 0 | 0 | 18 | 18 |
| gbGeomQuad | 6/6 | 0 | 0 | 0 | 6 | 6 |
| gbGfxCaps | 5/5 | 0 | 0 | 0 | 5 | 5 |
| gbGfxDriverInfo | 15/15 | 0 | 0 | 0 | 15 | 15 |
| gbGfxManager | 26/26 | 0 | 0 | 0 | 26 | 26 |
| gbGfxManager_D3D | 30/30 | 0 | 0 | 0 | 30 | 30 |
| gbGfxStatistic | 11/11 | 0 | 0 | 0 | 11 | 11 |
| gbImage2D | 9/9 | 0 | 0 | 0 | 9 | 9 |
| gbImage2DInfo | 11/11 | 0 | 0 | 0 | 11 | 11 |
| gbIndexBubble | 7/7 | 0 | 0 | 0 | 7 | 7 |
| gbIndexPool | 6/6 | 0 | 0 | 0 | 6 | 6 |
| gbKeyControler | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbLight | 13/13 | 0 | 0 | 0 | 13 | 13 |
| gbLightObj | 18/18 | 0 | 0 | 0 | 18 | 18 |
| gbMaterial | 5/5 | 0 | 0 | 0 | 5 | 5 |
| gbMatrix4 | 15/15 | 0 | 0 | 0 | 15 | 15 |
| gbMatrix4Flat | 16/16 | 0 | 0 | 0 | 16 | 16 |
| gbMatrixStack | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbMeshData | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbMeshMemCache | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbMeshSection | 10/10 | 0 | 0 | 0 | 10 | 10 |
| gbMixActInfo | 9/9 | 0 | 0 | 0 | 9 | 9 |
| gbNBTreeNode | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbNodeMsgObj | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbNodeMsgPayload | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbOBBox | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbPartEmitter | 20/20 | 0 | 0 | 0 | 20 | 20 |
| gbPartGroupParam | 26/26 | 0 | 0 | 0 | 26 | 26 |
| gbPartParamControl | 8/8 | 0 | 0 | 0 | 8 | 8 |
| gbParticleEffect | 26/26 | 0 | 0 | 0 | 26 | 26 |
| gbParticleGroup | 9/9 | 0 | 0 | 0 | 9 | 9 |
| gbParticleUnit | 13/13 | 0 | 0 | 0 | 13 | 13 |
| gbPixelFormat | 11/11 | 0 | 0 | 0 | 11 | 11 |
| gbPrintFont | 18/18 | 0 | 0 | 0 | 18 | 18 |
| gbPrintFontMgr | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbQuaternion | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbRay | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbRefObject | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbRenderEffect | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbRenderEffect_D3D | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbRenderInfoObj | 11/11 | 0 | 0 | 0 | 11 | 11 |
| gbResManager | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbResource | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbSceneGraph | 23/23 | 0 | 0 | 0 | 23 | 23 |
| gbSceneNode | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbSingleton_gbGfxManager | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbSnow | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbSound2DNode | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbSound3DNode | 10/10 | 0 | 0 | 0 | 10 | 10 |
| gbSoundData | 1/1 | 0 | 0 | 0 | 1 | 1 |
| gbSphere | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbSurfaceDesc | 5/5 | 0 | 0 | 0 | 5 | 5 |
| gbTagNode | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbTagXBladeNode | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbTexFlipAnim | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbTexture | 5/5 | 0 | 0 | 0 | 5 | 5 |
| gbTextureArray | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbTexture_D3D | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbUIQuad | 10/10 | 0 | 0 | 0 | 10 | 10 |
| gbVFile1 | 5/5 | 0 | 0 | 0 | 5 | 5 |
| gbVFileSystem | 7/7 | 0 | 0 | 0 | 7 | 7 |
| gbVec2D | 2/2 | 0 | 0 | 0 | 2 | 2 |
| gbVec3D | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbVec4D | 4/4 | 0 | 0 | 0 | 4 | 4 |
| gbVertPoolMgr | 12/12 | 0 | 0 | 0 | 12 | 12 |
| gbVertexBubble | 9/9 | 0 | 0 | 0 | 9 | 9 |
| gbVertexElement | 6/6 | 0 | 0 | 0 | 6 | 6 |
| gbVertexPool | 7/7 | 0 | 0 | 0 | 7 | 7 |
| gbViewPort | 6/6 | 0 | 0 | 0 | 6 | 6 |
| gbVisNode | 10/10 | 0 | 0 | 0 | 10 | 10 |
| gbVolModNode | 3/3 | 0 | 0 | 0 | 3 | 3 |
| gbVolumeModifier | 1/1 | 0 | 0 | 0 | 1 | 1 |
| graph | 9/9 | 0 | 0 | 0 | 9 | 9 |
| h3DPOBJECT | 1/1 | 0 | 0 | 0 | 1 | 1 |
| ioinfo | 3/3 | 0 | 0 | 0 | 3 | 3 |
| lconv | 18/18 | 0 | 0 | 0 | 18 | 18 |
| localVar0 | 3/3 | 0 | 0 | 0 | 3 | 3 |
| localVar1 | 5/5 | 0 | 0 | 0 | 5 | 5 |
| localVar2 | 4/4 | 0 | 0 | 0 | 4 | 4 |
| m_RoleState | 21/21 | 0 | 0 | 0 | 21 | 21 |
| magic_tab | 4/4 | 0 | 0 | 0 | 4 | 4 |
| me_RoleState | 24/24 | 0 | 0 | 0 | 24 | 24 |
| p_RoleState | 21/21 | 0 | 0 | 0 | 21 | 21 |
| pcmwaveformat_tag | 2/2 | 0 | 0 | 0 | 2 | 2 |
| primitive | 3/3 | 0 | 0 | 0 | 3 | 3 |
| rgbcolor_particle_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| rotation_particle_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| rotmulti_emitter_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| rterrmsgs | 2/2 | 0 | 0 | 0 | 2 | 2 |
| sCollision | 4/4 | 0 | 0 | 0 | 4 | 4 |
| s_RoleState | 20/20 | 0 | 0 | 0 | 20 | 20 |
| s_SpecialPropItem | 2/2 | 0 | 0 | 0 | 2 | 2 |
| scAsmDecoder | 1/1 | 0 | 0 | 0 | 1 | 1 |
| scCmdDef | 3/3 | 0 | 0 | 0 | 3 | 3 |
| scGlobalUserVar | 1/1 | 0 | 0 | 0 | 1 | 1 |
| scSCEFile | 2/2 | 0 | 0 | 0 | 2 | 2 |
| scScriptBlock | 7/7 | 0 | 0 | 0 | 7 | 7 |
| scScriptInstance | 0/1 | 0 | 0 | 0 | 0 | 1 |
| scUserVarInfo | 3/3 | 0 | 0 | 0 | 3 | 3 |
| scVARIANT | 3/3 | 0 | 0 | 0 | 3 | 3 |
| scVARIANT_data | 2/2 | 0 | 0 | 0 | 2 | 2 |
| scVarStack | 2/2 | 0 | 0 | 0 | 2 | 2 |
| sg_customshape | 4/4 | 0 | 0 | 0 | 4 | 4 |
| sg_emission_control | 14/14 | 0 | 0 | 0 | 14 | 14 |
| sg_emitter | 20/20 | 0 | 0 | 0 | 20 | 20 |
| sg_emitter_data | 9/9 | 0 | 0 | 0 | 9 | 9 |
| sg_emitter_sphere | 2/2 | 0 | 0 | 0 | 2 | 2 |
| sg_emitter_square | 2/2 | 0 | 0 | 0 | 2 | 2 |
| sg_particle | 27/27 | 0 | 0 | 0 | 27 | 27 |
| sg_particle_data | 14/14 | 0 | 0 | 0 | 14 | 14 |
| sg_particle_scene | 27/27 | 0 | 0 | 0 | 27 | 27 |
| size_particle_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| sizemulti_emitter_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| skill_tab | 2/2 | 0 | 0 | 0 | 2 | 2 |
| st_Manager | 2/2 | 0 | 0 | 0 | 2 | 2 |
| subPARAM | 6/6 | 0 | 0 | 0 | 6 | 6 |
| t3DModel | 4/4 | 0 | 0 | 0 | 4 | 4 |
| t3DObject | 10/10 | 0 | 0 | 0 | 10 | 10 |
| tChunk | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tFace | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tMaterialInfo | 9/9 | 0 | 0 | 0 | 9 | 9 |
| tag17A7BData | 8/8 | 0 | 0 | 8 | 0 | 8 |
| tag17A8Data | 11/11 | 0 | 0 | 11 | 0 | 11 |
| tag4DWORD | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagActionCommand | 6/6 | 0 | 0 | 0 | 6 | 6 |
| tagAnimStateSplit | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagAttackSequen | 13/13 | 0 | 0 | 0 | 13 | 13 |
| tagC10Data | 13/13 | 0 | 0 | 13 | 0 | 13 |
| tagCCBStageData | 5/5 | 0 | 0 | 5 | 0 | 5 |
| tagCCT | 51/51 | 0 | 0 | 0 | 51 | 51 |
| tagCOPYDATASTRUCT | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagCPKHeader | 13/13 | 0 | 0 | 0 | 13 | 13 |
| tagCPKTable | 7/7 | 0 | 0 | 0 | 7 | 7 |
| tagCam | 6/6 | 0 | 0 | 1 | 5 | 6 |
| tagCamTask | 9/9 | 0 | 0 | 0 | 9 | 9 |
| tagCmdData | 9/9 | 0 | 0 | 1 | 8 | 9 |
| tagCmdDataDestRoleView | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagCombatTaskData | 69/69 | 0 | 0 | 49 | 20 | 69 |
| tagCombatTimerState | 10/10 | 0 | 0 | 0 | 10 | 10 |
| tagControlData | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagControlThread | 11/11 | 0 | 0 | 0 | 11 | 11 |
| tagDemand | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagEffClass | 1/1 | 0 | 0 | 0 | 1 | 1 |
| tagEffGroup | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagEffLinker | 17/17 | 0 | 0 | 0 | 17 | 17 |
| tagEffMgrData | 1/1 | 0 | 0 | 0 | 1 | 1 |
| tagEffObj | 7/7 | 0 | 0 | 0 | 7 | 7 |
| tagEffObjType | 34/34 | 0 | 0 | 0 | 34 | 34 |
| tagEffSParticleSys | 30/30 | 0 | 0 | 0 | 30 | 30 |
| tagEffTaskParam | 29/29 | 0 | 0 | 0 | 29 | 29 |
| tagEntry | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagEntryEnd | 1/1 | 0 | 0 | 0 | 1 | 1 |
| tagExplosive | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagFightScriptData | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagFormationSceneState | 9/9 | 0 | 0 | 0 | 9 | 9 |
| tagGroup | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagHeader | 5/5 | 0 | 0 | 0 | 5 | 5 |
| tagImbibeNimbus | 8/8 | 0 | 0 | 0 | 8 | 8 |
| tagKBDLLHOOKSTRUCT | 5/5 | 0 | 0 | 0 | 5 | 5 |
| tagLVCOLUMNA | 8/8 | 0 | 0 | 0 | 8 | 8 |
| tagLVITEMA | 10/10 | 0 | 0 | 0 | 10 | 10 |
| tagListHead | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagLoggerCallback | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagMeteor | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagMeteorNode | 7/7 | 0 | 0 | 0 | 7 | 7 |
| tagNMHDR | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagNMITEMACTIVATE | 9/9 | 0 | 0 | 0 | 9 | 9 |
| tagNewItem | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagPALETTEENTRY | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagParam | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagPartical | 18/18 | 0 | 0 | 0 | 18 | 18 |
| tagPartyInitView | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagPlayerSet | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagQuad | 23/23 | 0 | 0 | 0 | 23 | 23 |
| tagRGBQUAD | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagRegion | 5/5 | 0 | 0 | 0 | 5 | 5 |
| tagRoleActionState | 38/38 | 0 | 0 | 0 | 38 | 38 |
| tagRoleSlot | 1/1 | 0 | 0 | 0 | 1 | 1 |
| tagRoleState | 53/53 | 0 | 0 | 0 | 53 | 53 |
| tagRoleSystemData | 16/16 | 0 | 0 | 12 | 4 | 16 |
| tagRoleTask | 10/10 | 0 | 0 | 1 | 9 | 10 |
| tagRoleTaskData | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagRoleTaskSlotsView | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagRoleTaskVec3View | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagScriptCmd | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagScriptPtrQuad | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagShockUnit | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagShowItem | 7/7 | 0 | 0 | 0 | 7 | 7 |
| tagSkillCountBlock | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagStageRoleData | 14/14 | 0 | 0 | 7 | 7 | 14 |
| tagStageSubTask | 20/20 | 0 | 0 | 0 | 20 | 20 |
| tagStageTask | 10/10 | 0 | 0 | 0 | 10 | 10 |
| tagTCITEMA | 7/7 | 0 | 0 | 0 | 7 | 7 |
| tagTaskLayoutPtrs | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagTaskSlotHeader | 2/2 | 0 | 0 | 0 | 2 | 2 |
| tagTaskVecXYZ | 3/3 | 0 | 0 | 0 | 3 | 3 |
| tagTeamSlotsBOverlay | 10/10 | 0 | 0 | 0 | 10 | 10 |
| tagThread | 9/9 | 0 | 0 | 0 | 9 | 9 |
| tagUIParam | 8/8 | 0 | 0 | 0 | 8 | 8 |
| tagUITask | 9/9 | 0 | 0 | 0 | 9 | 9 |
| tagUV | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagUVSet | 4/4 | 0 | 0 | 0 | 4 | 4 |
| tagVA | 6/6 | 0 | 0 | 0 | 6 | 6 |
| tagVAF | 6/6 | 0 | 0 | 0 | 6 | 6 |
| tagVAO | 4/4 | 0 | 0 | 0 | 4 | 4 |
| util | 6/6 | 0 | 0 | 0 | 6 | 6 |
| vert | 3/3 | 0 | 0 | 0 | 3 | 3 |
| vertexalpha_particle_graph | 1/1 | 0 | 0 | 0 | 1 | 1 |
| waveformat_tag | 5/5 | 0 | 0 | 0 | 5 | 5 |
| wavehdr_tag | 8/8 | 0 | 0 | 0 | 8 | 8 |

## 9. 结构覆盖（单侧独有）

| 侧 | 数量 | 说明 |
|---|---|---|
| 仅导出（IDB 独有） | 443 | 多为 CRT/系统类型（无注解属预期） |
| 仅注解（导出缺） | 63 | 注解结构未见于导出 ⇒ 整类往返缺口，须查 apply 是否跳过 |

仅注解（导出缺）清单：

- `D3DAdapterInfo`
- `D3DDeviceCombo`
- `D3DDeviceInfo`
- `D3DDriverBug`
- `D3DXCOLOR`
- `D3DXFLOAT16`
- `D3DXMATRIX`
- `D3DXPlane`
- `D3DXVECTOR2`
- `D3DXVECTOR3`
- `D3DXVECTOR4`
- `HBRUSH__`
- `HDC__`
- `HHOOK__`
- `HICON__`
- `HINSTANCE__`
- `HKEY__`
- `HMONITOR__`
- `HWAVEOUT__`
- `HWND__`
- `_D3DADAPTER_IDENTIFIER9`
- `_D3DBOX`
- `_D3DCAPS9`
- `_D3DCLIPSTATUS9`
- `_D3DCOLORVALUE`
- `_D3DDEVICE_CREATION_PARAMETERS`
- `_D3DDISPLAYMODE`
- `_D3DGAMMARAMP`
- `_D3DINDEXBUFFER_DESC`
- `_D3DLIGHT9`
- `_D3DLOCKED_BOX`
- `_D3DLOCKED_RECT`
- `_D3DMATERIAL9`
- `_D3DMATRIX`
- `_D3DPRESENT_PARAMETERS_`
- `_D3DPSHADERCAPS2_0`
- `_D3DRASTER_STATUS`
- `_D3DRECT`
- `_D3DRECTPATCH_INFO`
- `_D3DSURFACE_DESC`
- `_D3DTRIPATCH_INFO`
- `_D3DVECTOR`
- `_D3DVERTEXBUFFER_DESC`
- `_D3DVERTEXELEMENT9`
- `_D3DVIEWPORT9`
- `_D3DVOLUME_DESC`
- `_D3DVSHADERCAPS2_0`
- `_D3DXEFFECT_DESC`
- `_D3DXFUNCTION_DESC`
- `_D3DXPARAMETER_DESC`
- `_D3DXPASS_DESC`
- `_D3DXSEMANTIC`
- `_D3DXTECHNIQUE_DESC`
- `_ThrowInfo`
- `__m64`
- `__old_sbh_page_struct`
- `__unnamed`
- `_s__ThrowInfo`
- `exception`
- `filebuf`
- `std`
- `tagOFNA`
- `tagPOINT`

## 10. 口径附注

- **只读**：本工具不改任何输入；只写本报表。
- **陈旧拒报**：export 时间戳早于注解最新改动 ⇒ 拒报（rc=2），避免拿过期快照当读数（2026-10-19 陈旧验证误判同型坑）。
- **dict 形态识别**：inline union/struct（dict `type`）、`source:overlap`、同偏移 `_N` 变体键 ⇒ 位面复用（非偏移冲突），见 §6。
- **拼写归一只做等价变换**（§5 判据），不抹真实差异（§4）：STL 折叠 `char[N]`、指针级变化、const 丢失等都留在 §4。
- 配对键是 **(基偏移, 成员名)**：同偏移多视图靠名字区分，`12` / `12_1` 同基偏移属位面复用变体。
- 同输入 ⇒ 同输出：全表排序输出，不含 wall-clock。

